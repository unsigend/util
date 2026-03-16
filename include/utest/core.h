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

#include <utest/flags.h>
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

#define EXPECT_TRUE(expr)                                                      \
  if (!(expr)) {                                                               \
    cas->status = UT_FAIL;                                                     \
    return;                                                                    \
  }

#define EXPECT_FALSE(expr)                                                     \
  if ((expr)) {                                                                \
    cas->status = UT_FAIL;                                                     \
    return;                                                                    \
  }

#endif