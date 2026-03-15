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

#ifndef UTEST_TYPES_H
#define UTEST_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void *(utest_func_t)(void *);
typedef utest_func_t utest_case_func_t;
typedef utest_func_t utest_suite_func_t;

struct utest_ctx {
  int flags;                   /* flags for the test context */
  size_t ntotal;               /* total number of tests suites */
  size_t npassed;              /* number of passed tests suites */
  size_t nctotal;              /* total number of test cases */
  size_t ncpassed;             /* number of passed test cases */
  utest_suite_func_t **suites; /* suites list */
  size_t nsuites;              /* number of suites */
  size_t nsuitescap;           /* capacity of suites list */
};

/* Thread-safe suite, which is maintained in stack by each thread, since the
   suite is the minimal thread unit. */
struct utest_suite {
  const char *name; /* suite name */
  bool failed;      /* one of the case failed */
  char *buf;        /* output buffer */
  size_t bufsz;     /* output buffer size */
  size_t bufcap;    /* output buffer capacity */
  size_t nctotal;   /* total number of test cases */
  size_t ncpassed;  /* number of passed test cases */
};

#endif