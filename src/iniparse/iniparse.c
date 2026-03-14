/**
 * MIT License
 *
 * Copyright (c) 2025 QIU YIXIANG
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
#include <iniparse.h>
#include <string.h>

#define BUFSZ 512

#define IS_COMMENT(line) (line[0] == '#' || line[0] == ';')
#define IS_SECTION(line) (line[0] == '[' && line[strlen(line) - 2] == ']')

bool iniparse_init(struct iniparse *this, const char *filename)
{
  if (!this || !filename)
    return false;

  this->filename = filename;
  this->stream = fopen(filename, "r");

  if (!this->stream)
    return false;
  return true;
}

char *iniparse_value(struct iniparse *this, const char *section,
                     const char *key)
{
  if (!this || !section || !key)
    return NULL;

  char linebuf[BUFSZ];
  memset(linebuf, 0, BUFSZ);

  /* Parse the file line by line */
  while (fgets(linebuf, BUFSZ, this->stream)) {
    if (IS_COMMENT(linebuf) || linebuf[0] == '\n')
      continue;

    if (IS_SECTION(linebuf)) {
      if (strncmp(linebuf + 1, section, strlen(section)) == 0) {
        while (fgets(linebuf, BUFSZ, this->stream)) {
          if (IS_COMMENT(linebuf))
            continue;
          if (IS_SECTION(linebuf))
            goto fail;

          char *p = linebuf;
          while (isspace(*p))
            p++;

          if (!strncmp(p, key, strlen(key)) &&
              (p[strlen(key)] == '=' || p[strlen(key)] == ' ')) {
            char *value = strchr(p, '=');

            if (!value)
              goto fail;

            while (*value == '=' || isspace(*value))
              value++;

            if (*value == '\0')
              goto fail;

            if (*(value + strlen(value) - 1) == '\n')
              *(value + strlen(value) - 1) = '\0';

            fseek(this->stream, 0, SEEK_SET);
            return value;
          }
        }
        goto fail;
      }
      continue;
    }
  }
fail:
  fseek(this->stream, 0, SEEK_SET);
  return NULL;
}

void iniparse_all(struct iniparse *this, iniparse_func callback, void *ctx)
{
  if (!this || !callback)
    return;

  char secbuf[BUFSZ];
  char linebuf[BUFSZ];

  memset(linebuf, 0, BUFSZ);
  memset(secbuf, 0, BUFSZ);

  while (fgets(linebuf, BUFSZ, this->stream) != NULL) {
    if (IS_COMMENT(linebuf) || linebuf[0] == '\n')
      continue;

    if (IS_SECTION(linebuf)) {
      strncpy(secbuf, linebuf + 1, strlen(linebuf) - 3);
      secbuf[strlen(linebuf) - 3] = '\0';
      continue;
    }
    char *key = linebuf;
    while (isspace(*key))
      key++;
    char *value = strchr(key, '=');

    if (!value)
      continue;

    if (*(value - 1) == ' ')
      *(value - 1) = '\0';

    do {
      value++;
    } while (isspace(*value));

    if (*(value + strlen(value) - 1) == '\n')
      *(value + strlen(value) - 1) = '\0';

    callback(ctx, secbuf, key, value);
  }

  fseek(this->stream, 0, SEEK_SET);
}