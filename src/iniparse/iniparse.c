/**
 * MIT License
 *
 * Copyright (c) 2026 YIXIANG QIU
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <ctype.h>
#include <fcntl.h>
#include <iniparse.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define MAX_ENTRIES 64 /* initial capacity of entries list */
#define SCALE_FACTOR 2 /* scale factor for entries list */

/* utility functions */
static char *skipline(char *p);
static char *skipspace(char *p);

/* parser */
static char *parse_section(char *p, struct iniparse_entry *entry);
static char *parse_entry(char *p, struct iniparse_entry *entry);

/* put entry into ctx */
static void put(struct iniparse_ctx *ctx, const char *section, const char *key,
                const char *value);

/* error handling */
static void fatal();
static void error(const char *msg);

static void fatal()
{
  perror("iniparse");
  exit(EXIT_FAILURE);
}

static void error(const char *msg)
{
  fprintf(stderr, "iniparse: %s\n", msg);
  exit(EXIT_FAILURE);
}

static char *skipline(char *p)
{
  while (*p && *p != '\n')
    p++;
  if (*p == '\n')
    p++;
  return p;
}

static char *skipspace(char *p)
{
  while (*p && *p != '\n' && isspace(*p))
    p++;
  return p;
}

void iniparse_init(struct iniparse_ctx *ctx, const char *filename)
{
  int fd;
  off_t sz;
  if (!filename || !ctx)
    error("invalid arguments");

  memset(ctx, 0, sizeof(*ctx));
  ctx->filename = filename;

  if ((fd = open(filename, O_RDONLY)) == -1)
    fatal();

  sz = lseek(fd, 0, SEEK_END);
  if (sz == -1)
    fatal();
  if (!sz) {
    close(fd);
    error("empty file");
  }

  char *buf =
      (char *)mmap(NULL, sz + 1, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (buf == MAP_FAILED)
    fatal();
  close(fd);
  buf[sz] = '\0'; /* EOF guard */

  ctx->buf = buf;
  ctx->bufsz = (size_t)sz;
}

void iniparse_fini(struct iniparse_ctx *ctx)
{
  if (ctx->buf)
    munmap((void *)ctx->buf, ctx->bufsz + 1);
  if (ctx->entries)
    free(ctx->entries);
}

void iniparse_parse(struct iniparse_ctx *ctx)
{
  char *p = ctx->buf;
  struct iniparse_entry entry = {0};

  while (p < ctx->buf + ctx->bufsz) {
    p = skipspace(p);
    switch (*p) {
    case '\0':
      return;
    case '\n': /* blank line or comment */
    case ';':
    case '#':
      p = skipline(p);
      break;
    case '[': /* section */
      p = parse_section(p, &entry);
      break;
    default: /* entry */
      p = parse_entry(p, &entry);
      put(ctx, entry.sec, entry.key, entry.val);
      break;
    }
  }
}

const char *iniparse_getvalue(struct iniparse_ctx *ctx, const char *section,
                              const char *key)
{
  for (size_t i = 0; i < ctx->nentries; i++) {
    if (!strcmp(ctx->entries[i].sec, section) &&
        !strcmp(ctx->entries[i].key, key))
      return ctx->entries[i].val;
  }
  return NULL;
}

static void put(struct iniparse_ctx *ctx, const char *section, const char *key,
                const char *value)
{
  if (ctx->nentries >= ctx->nentriescap) {
    if (ctx->entries) {
      ctx->nentriescap *= SCALE_FACTOR;
      ctx->entries =
          realloc(ctx->entries, ctx->nentriescap * sizeof(*ctx->entries));
      if (!ctx->entries)
        fatal();
    } else {
      /* first allocation */
      ctx->nentriescap = MAX_ENTRIES;
      ctx->entries = calloc(ctx->nentriescap, sizeof(*ctx->entries));
      if (!ctx->entries)
        fatal();
    }
  }
  ctx->entries[ctx->nentries].sec = section;
  ctx->entries[ctx->nentries].key = key;
  ctx->entries[ctx->nentries].val = value;
  ctx->nentries++;
}

static char *parse_section(char *p, struct iniparse_entry *entry)
{
  ++p; /* skip [ */
  p = skipspace(p);
  entry->sec = p;

  while (*p && *p != ']')
    p++;
  if (*p != ']')
    error("invalid section");
  char *end = p;

  while (p > entry->sec && isspace(*(p - 1)))
    --p;
  *p = '\0';

  return skipline(end + 1);
}

static char *parse_entry(char *p, struct iniparse_entry *entry)
{
  char *next, *s;
  entry->key = p;
  while (*p && *p != '=' && *p != '\n')
    p++;

  s = p;
  if (*p == '=') {
    p = skipspace(p + 1);
    entry->val = p;
    while (*p && *p != '\n')
      p++;
    char *r = p;
    while (r > entry->val && isspace(*(r - 1)))
      --r;
    *r = '\0';
    next = p + 1;
  } else {
    entry->val = NULL;
    next = skipline(p + 1);
  }
  while (s > entry->key && isspace(*(s - 1)))
    --s;
  *s = '\0';
  return next;
}