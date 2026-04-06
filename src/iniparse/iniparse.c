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
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define NLIST 64
#define FACTOR 2

/* utility functions */
static inline char *skipline(char *p);
static inline char *skipspace(char *p);

/* parser */
static char *parse_section(char *p, char **sec);
static char *parse_entry(char *p, char **key, char **val);

/* put entry into section and section into ctx */
static int putentry(struct iniparse_sec *sec, char *key, char *val);
static int put(struct iniparse_ctx *ctx, char *sec, char *key, char *val);

/* free */
static inline void freeentry(struct iniparse_entry *entry);
static inline void freesec(struct iniparse_sec *sec);

static inline char *skipline(char *p)
{
  while (*p && *p != '\n')
    p++;
  if (*p == '\n')
    p++;
  return p;
}

static inline char *skipspace(char *p)
{
  while (*p && *p != '\n' && isspace(*p))
    p++;
  return p;
}

int iniparse_init(struct iniparse_ctx *ctx, const char *filename)
{
  int fd;
  off_t sz;
  if (!filename || !ctx)
    return -1;

  memset(ctx, 0, sizeof(*ctx));
  ctx->filename = filename;

  if ((fd = open(filename, O_RDONLY)) == -1)
    return -1;

  sz = lseek(fd, 0, SEEK_END);
  if (sz == -1 || !sz) {
    close(fd);
    return -1;
  }

  char *buf =
      (char *)mmap(NULL, sz + 1, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  close(fd);
  if (buf == MAP_FAILED)
    return -1;
  buf[sz] = '\0'; /* EOF guard */

  ctx->buf = buf;
  ctx->bufsz = (size_t)sz;
  return 0;
}

void iniparse_fini(struct iniparse_ctx *ctx)
{
  if (!ctx)
    return;

  if (ctx->buf)
    munmap((void *)ctx->buf, ctx->bufsz + 1);

  if (ctx->secs) {
    for (size_t i = 0; i < ctx->nsecs; i++)
      freesec(&ctx->secs[i]);
    free(ctx->secs);
  }
}

int iniparse_parse(struct iniparse_ctx *ctx)
{
  char *p = ctx->buf;
  char *sec = NULL, *key = NULL, *val = NULL;

  while (p < ctx->buf + ctx->bufsz) {
    p = skipspace(p);
    switch (*p) {
    case '\0':
      return 0;
    case '\n': /* blank line or comment */
    case ';':
    case '#':
      p = skipline(p);
      break;
    case '[': /* section */
      p = parse_section(p, &sec);
      break;
    default: /* entry */
      p = parse_entry(p, &key, &val);
      if (put(ctx, sec, key, val) == -1)
        return -1;
      break;
    }
  }
  return 0;
}

const char *iniparse_getvalue(struct iniparse_ctx *ctx, const char *sec,
                              const char *key)
{
  for (size_t i = 0; i < ctx->nsecs; i++) {
    if (!strcmp(ctx->secs[i].sec, sec)) {
      for (size_t j = 0; j < ctx->secs[i].nentries; j++) {
        if (!strcmp(ctx->secs[i].entries[j].key, key))
          return ctx->secs[i].entries[j].val;
      }
      break;
    }
  }
  return NULL;
}

static int putentry(struct iniparse_sec *sec, char *key, char *val)
{
  if (sec->nentries >= sec->nentriescap) {
    if (sec->entries) {
      sec->nentriescap *= FACTOR;
      struct iniparse_entry *newentries =
          realloc(sec->entries, sec->nentriescap * sizeof(*sec->entries));
      if (!newentries)
        return -1;
      sec->entries = newentries;
    } else {
      sec->nentriescap = NLIST;
      sec->entries = calloc(sec->nentriescap, sizeof(*sec->entries));
      if (!sec->entries)
        return -1;
    }
  }
  sec->entries[sec->nentries].key = strdup(key);
  if (!sec->entries[sec->nentries].key)
    return -1;
  if (val) {
    sec->entries[sec->nentries].val = strdup(val);
    if (!sec->entries[sec->nentries].val) {
      free((void *)sec->entries[sec->nentries].key);
      return -1;
    }
  } else
    sec->entries[sec->nentries].val = NULL;

  sec->nentries++;
  return 0;
}

static int put(struct iniparse_ctx *ctx, char *sec, char *key, char *val)
{
  if (!sec)
    return -1;
  for (size_t i = 0; i < ctx->nsecs; i++) {
    if (!strcmp(ctx->secs[i].sec, sec)) {
      return putentry(&ctx->secs[i], key, val);
    }
  }
  if (ctx->nsecs >= ctx->nsecscap) {
    if (ctx->secs) {
      ctx->nsecscap *= FACTOR;
      struct iniparse_sec *newsecs =
          realloc(ctx->secs, ctx->nsecscap * sizeof(*ctx->secs));
      if (!newsecs)
        return -1;
      ctx->secs = newsecs;
    } else {
      ctx->nsecscap = NLIST;
      ctx->secs = calloc(ctx->nsecscap, sizeof(*ctx->secs));
      if (!ctx->secs)
        return -1;
    }
  }
  ctx->secs[ctx->nsecs].sec = strdup(sec);
  if (!ctx->secs[ctx->nsecs].sec)
    return -1;
  ctx->secs[ctx->nsecs].entries = NULL;
  ctx->secs[ctx->nsecs].nentries = 0;
  ctx->secs[ctx->nsecs].nentriescap = 0;
  ctx->nsecs++;
  return putentry(&ctx->secs[ctx->nsecs - 1], key, val);
}

static char *parse_section(char *p, char **sec)
{
  ++p; /* skip [ */
  p = skipspace(p);
  *sec = p;

  while (*p && *p != ']' && *p != '\n')
    p++;
  if (*p != ']') {
    *sec = NULL;
    return p + 1;
  }
  char *end = p;

  while (p > *sec && isspace(*(p - 1)))
    --p;
  *p = '\0';

  return skipline(end + 1);
}

static char *parse_entry(char *p, char **key, char **val)
{
  char *next, *s;
  *key = p;
  while (*p && *p != '=' && *p != '\n')
    p++;

  s = p;
  if (*p == '=') {
    p = skipspace(p + 1);
    *val = p;
    while (*p && *p != '\n')
      p++;
    char *r = p;
    while (r > *val && isspace(*(r - 1)))
      --r;
    *r = '\0';
    next = p + 1;
  } else {
    *val = NULL;
    next = skipline(p + 1);
  }
  while (s > *key && isspace(*(s - 1)))
    --s;
  *s = '\0';
  return next;
}

static inline void freeentry(struct iniparse_entry *entry)
{
  if (!entry)
    return;
  if (entry->key)
    free((void *)entry->key);
  if (entry->val)
    free((void *)entry->val);
}

static inline void freesec(struct iniparse_sec *sec)
{
  if (!sec)
    return;
  if (sec->sec)
    free((void *)sec->sec);
  if (sec->entries) {
    for (size_t i = 0; i < sec->nentries; i++)
      freeentry(&sec->entries[i]);
    free(sec->entries);
  }
}