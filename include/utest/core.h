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

#ifndef UTEST_CORE_H
#define UTEST_CORE_H

#include <stdint.h>
#include <string.h>
#include <utest/flags.h>
#include <utest/print.h>
#include <utest/types.h>

extern struct utest_ctx utest_ctx;

#ifdef __cplusplus
extern "C" {
#endif

extern void utest_init(int flags);
extern void utest_fini();
extern void utest_addsuite(const char *name, utest_suite_func_t func);
extern void utest_runcase(struct utest_suite *suite, const char *name,
                          utest_case_func_t func);
extern void utest_runsuites();
extern void utest_runsuites_thread(int nthreads);

#ifdef __cplusplus
}
#endif

#define _CONCAT(x, y) x##y
#define CONCAT(x, y) _CONCAT(x, y)
#define CASEPREFIX __utest_case_
#define SUITEPREFIX __utest_suite_

#define UTEST_INIT(flags) utest_init(flags)
#define UTEST_FINI() utest_fini()

#define UTEST_CASE(name)                                                       \
  static void CONCAT(CASEPREFIX, name)(struct utest_case * cas)
#define UTEST_SUITE(name)                                                      \
  void CONCAT(SUITEPREFIX, name)(struct utest_suite * suite)

#define UTEST_RUNCASE(name)                                                    \
  utest_runcase(suite, #name, CONCAT(CASEPREFIX, name))
#define UTEST_ADDSUITE(name) utest_addsuite(#name, CONCAT(SUITEPREFIX, name))
#define UTEST_RUNSUITES() utest_runsuites()
#define UTEST_RUNSUITES_THREAD(nthreads) utest_runsuites_thread(nthreads)

#define _UTASSERT(expr, fmt, ...)                                              \
  do {                                                                         \
    if (!(expr)) {                                                             \
      (cas)->status = UT_FAIL;                                                 \
      utbuf_printassert((cas)->buf, __LINE__, __FILE__, fmt, ##__VA_ARGS__);   \
      if (utest_ctx.flags & UTF_STOPONASS)                                     \
        return;                                                                \
    }                                                                          \
  } while (0)

/* boolean */
#define EXPECT_TRUE(expr)                                                      \
  _UTASSERT((expr), "expect " #expr " was true, actual was false");
#define EXPECT_FALSE(expr)                                                     \
  _UTASSERT(!(expr), "expect " #expr " was false, actual was true");

/* pointer */
#define EXPECT_NULL(ptr)                                                       \
  _UTASSERT(((uintptr_t)(ptr)) == (uintptr_t)NULL,                             \
            "expect " #ptr " was NULL, actual was not NULL");
#define EXPECT_NOTNULL(ptr)                                                    \
  _UTASSERT(((uintptr_t)(ptr)) != (uintptr_t)NULL,                             \
            "expect " #ptr " was not NULL, actual was NULL");
#define EXPECT_EQ_PTR(actual, expect)                                          \
  _UTASSERT(((uintptr_t)(actual)) == ((uintptr_t)(expect)),                    \
            "expect " #actual " == " #expect ", actual was %p", (actual));
#define EXPECT_NE_PTR(actual, expect)                                          \
  _UTASSERT(((uintptr_t)(actual)) != ((uintptr_t)(expect)),                    \
            "expect " #actual " != " #expect ", actual was %p", (actual));
#define EXPECT_GT_PTR(actual, expect)                                          \
  _UTASSERT(((uintptr_t)(actual)) > ((uintptr_t)(expect)),                     \
            "expect " #actual " > " #expect ", actual was %p", (actual));
#define EXPECT_GE_PTR(actual, expect)                                          \
  _UTASSERT(((uintptr_t)(actual)) >= ((uintptr_t)(expect)),                    \
            "expect " #actual " >= " #expect ", actual was %p", (actual));
#define EXPECT_LT_PTR(actual, expect)                                          \
  _UTASSERT(((uintptr_t)(actual)) < ((uintptr_t)(expect)),                     \
            "expect " #actual " < " #expect ", actual was %p", (actual));
#define EXPECT_LE_PTR(actual, expect)                                          \
  _UTASSERT(((uintptr_t)(actual)) <= ((uintptr_t)(expect)),                    \
            "expect " #actual " <= " #expect ", actual was %p", (actual));

/* integer */
#define EXPECT_EQ_INT(actual, expect)                                          \
  _UTASSERT(((int64_t)(actual)) == ((int64_t)(expect)),                        \
            "expect " #actual " == " #expect ", actual was %lld",              \
            (int64_t)(actual));
#define EXPECT_NE_INT(actual, expect)                                          \
  _UTASSERT(((int64_t)(actual)) != ((int64_t)(expect)),                        \
            "expect " #actual " != " #expect ", actual was %lld",              \
            (int64_t)(actual));
#define EXPECT_GT_INT(actual, expect)                                          \
  _UTASSERT(((int64_t)(actual)) > ((int64_t)(expect)),                         \
            "expect " #actual " > " #expect ", actual was %lld",               \
            (int64_t)(actual));
#define EXPECT_GE_INT(actual, expect)                                          \
  _UTASSERT(((int64_t)(actual)) >= ((int64_t)(expect)),                        \
            "expect " #actual " >= " #expect ", actual was %lld",              \
            (int64_t)(actual));
#define EXPECT_LT_INT(actual, expect)                                          \
  _UTASSERT(((int64_t)(actual)) < ((int64_t)(expect)),                         \
            "expect " #actual " < " #expect ", actual was %lld",               \
            (int64_t)(actual));
#define EXPECT_LE_INT(actual, expect)                                          \
  _UTASSERT(((int64_t)(actual)) <= ((int64_t)(expect)),                        \
            "expect " #actual " <= " #expect ", actual was %lld",              \
            (int64_t)(actual));

/* unsigned integer */
#define EXPECT_EQ_UINT(actual, expect)                                         \
  _UTASSERT(((uint64_t)(actual)) == ((uint64_t)(expect)),                      \
            "expect " #actual " == " #expect ", actual was %llu",              \
            (uint64_t)(actual));
#define EXPECT_NE_UINT(actual, expect)                                         \
  _UTASSERT(((uint64_t)(actual)) != ((uint64_t)(expect)),                      \
            "expect " #actual " != " #expect ", actual was %llu",              \
            (uint64_t)(actual));
#define EXPECT_GT_UINT(actual, expect)                                         \
  _UTASSERT(((uint64_t)(actual)) > ((uint64_t)(expect)),                       \
            "expect " #actual " > " #expect ", actual was %llu",               \
            (uint64_t)(actual));
#define EXPECT_GE_UINT(actual, expect)                                         \
  _UTASSERT(((uint64_t)(actual)) >= ((uint64_t)(expect)),                      \
            "expect " #actual " >= " #expect ", actual was %llu",              \
            (uint64_t)(actual));
#define EXPECT_LT_UINT(actual, expect)                                         \
  _UTASSERT(((uint64_t)(actual)) < ((uint64_t)(expect)),                       \
            "expect " #actual " < " #expect ", actual was %llu",               \
            (uint64_t)(actual));
#define EXPECT_LE_UINT(actual, expect)                                         \
  _UTASSERT(((uint64_t)(actual)) <= ((uint64_t)(expect)),                      \
            "expect " #actual " <= " #expect ", actual was %llu",              \
            (uint64_t)(actual));

/* character */
#define EXPECT_EQ_CHAR(actual, expect)                                         \
  _UTASSERT(((char)(actual)) == ((char)(expect)),                              \
            "expect " #actual " == " #expect ", actual was '%c'",              \
            (char)(actual));
#define EXPECT_NE_CHAR(actual, expect)                                         \
  _UTASSERT(((char)(actual)) != ((char)(expect)),                              \
            "expect " #actual " != " #expect ", actual was '%c'",              \
            (char)(actual));
#define EXPECT_GT_CHAR(actual, expect)                                         \
  _UTASSERT(((char)(actual)) > ((char)(expect)),                               \
            "expect " #actual " > " #expect ", actual was '%c'",               \
            (char)(actual));
#define EXPECT_GE_CHAR(actual, expect)                                         \
  _UTASSERT(((char)(actual)) >= ((char)(expect)),                              \
            "expect " #actual " >= " #expect ", actual was '%c'",              \
            (char)(actual));
#define EXPECT_LT_CHAR(actual, expect)                                         \
  _UTASSERT(((char)(actual)) < ((char)(expect)),                               \
            "expect " #actual " < " #expect ", actual was '%c'",               \
            (char)(actual));
#define EXPECT_LE_CHAR(actual, expect)                                         \
  _UTASSERT(((char)(actual)) <= ((char)(expect)),                              \
            "expect " #actual " <= " #expect ", actual was '%c'",              \
            (char)(actual));

/* unsigned character */
#define EXPECT_EQ_UCHAR(actual, expect)                                        \
  _UTASSERT(((unsigned char)(actual)) == ((unsigned char)(expect)),            \
            "expect " #actual " == " #expect ", actual was '%c'",              \
            (unsigned char)(actual));
#define EXPECT_NE_UCHAR(actual, expect)                                        \
  _UTASSERT(((unsigned char)(actual)) != ((unsigned char)(expect)),            \
            "expect " #actual " != " #expect ", actual was '%c'",              \
            (unsigned char)(actual));
#define EXPECT_GT_UCHAR(actual, expect)                                        \
  _UTASSERT(((unsigned char)(actual)) > ((unsigned char)(expect)),             \
            "expect " #actual " > " #expect ", actual was '%c'",               \
            (unsigned char)(actual));
#define EXPECT_GE_UCHAR(actual, expect)                                        \
  _UTASSERT(((unsigned char)(actual)) >= ((unsigned char)(expect)),            \
            "expect " #actual " >= " #expect ", actual was '%c'",              \
            (unsigned char)(actual));
#define EXPECT_LT_UCHAR(actual, expect)                                        \
  _UTASSERT(((unsigned char)(actual)) < ((unsigned char)(expect)),             \
            "expect " #actual " < " #expect ", actual was '%c'",               \
            (unsigned char)(actual));
#define EXPECT_LE_UCHAR(actual, expect)                                        \
  _UTASSERT(((unsigned char)(actual)) <= ((unsigned char)(expect)),            \
            "expect " #actual " <= " #expect ", actual was '%c'",              \
            (unsigned char)(actual));

/* double */
#define EXPECT_EQ_DOUBLE(actual, expect)                                       \
  _UTASSERT(((double)(actual)) == ((double)(expect)),                          \
            "expect " #actual " == " #expect ", actual was %f",                \
            (double)(actual));
#define EXPECT_NE_DOUBLE(actual, expect)                                       \
  _UTASSERT(((double)(actual)) != ((double)(expect)),                          \
            "expect " #actual " != " #expect ", actual was %f",                \
            (double)(actual));
#define EXPECT_GT_DOUBLE(actual, expect)                                       \
  _UTASSERT(((double)(actual)) > ((double)(expect)),                           \
            "expect " #actual " > " #expect ", actual was %f",                 \
            (double)(actual));
#define EXPECT_GE_DOUBLE(actual, expect)                                       \
  _UTASSERT(((double)(actual)) >= ((double)(expect)),                          \
            "expect " #actual " >= " #expect ", actual was %f",                \
            (double)(actual));
#define EXPECT_LT_DOUBLE(actual, expect)                                       \
  _UTASSERT(((double)(actual)) < ((double)(expect)),                           \
            "expect " #actual " < " #expect ", actual was %f",                 \
            (double)(actual));
#define EXPECT_LE_DOUBLE(actual, expect)                                       \
  _UTASSERT(((double)(actual)) <= ((double)(expect)),                          \
            "expect " #actual " <= " #expect ", actual was %f",                \
            (double)(actual));

/* string */
#define EXPECT_EQ_STR(actual, expect)                                          \
  _UTASSERT(strcmp((actual), (expect)) == 0,                                   \
            "expect " #actual " == " #expect ", actual was \"%s\"", (actual));
#define EXPECT_NE_STR(actual, expect)                                          \
  _UTASSERT(strcmp((actual), (expect)) != 0,                                   \
            "expect " #actual " != " #expect ", actual was \"%s\"", (actual));
#define EXPECT_GT_STR(actual, expect)                                          \
  _UTASSERT(strcmp((actual), (expect)) > 0,                                    \
            "expect " #actual " > " #expect ", actual was \"%s\"", (actual));
#define EXPECT_GE_STR(actual, expect)                                          \
  _UTASSERT(strcmp((actual), (expect)) >= 0,                                   \
            "expect " #actual " >= " #expect ", actual was \"%s\"", (actual));
#define EXPECT_LT_STR(actual, expect)                                          \
  _UTASSERT(strcmp((actual), (expect)) < 0,                                    \
            "expect " #actual " < " #expect ", actual was \"%s\"", (actual));
#define EXPECT_LE_STR(actual, expect)                                          \
  _UTASSERT(strcmp((actual), (expect)) <= 0,                                   \
            "expect " #actual " <= " #expect ", actual was \"%s\"", (actual));

#endif