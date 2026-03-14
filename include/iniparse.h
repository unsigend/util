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

#ifndef INIPARSE_H
#define INIPARSE_H

/* This project is part of the util library project, configparse module is used
   to parse INI configuration file, and is designed for easy and simple usage.
   The current implementation do not clone or copy the string. */

#include <stdbool.h>
#include <stdio.h>

/* When the section, key, value is parsed, the callback function will be called,
   ctx is the context pointer. */
typedef void (*iniparse_func)(void *ctx, const char *sec, const char *key,
                              const char *value);

struct iniparse {
  const char *filename; /* filename of INI file */
  FILE *stream;         /* FILE structure pointer */
};

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize the iniparse object */
extern bool iniparse_init(struct iniparse *this, const char *filename);

/* Parse the file line by line, find the value by the section and key, return
   NULL if not found. Low performance for multiple parsing. */
extern char *iniparse_value(struct iniparse *this, const char *sec,
                            const char *key);

/* Parse the file line by line, call the callback function for each key-value
   pair, user should duplicate the section, key and value.*/
extern void iniparse_all(struct iniparse *this, iniparse_func callback,
                         void *ctx);

#ifdef __cplusplus
}
#endif

#endif