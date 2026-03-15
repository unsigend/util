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

#ifndef UTEST_H
#define UTEST_H

/* Utest: Clean and Simple Test Framework, Public API header. */

#define UTF_STOPONFIRST /* stop on first failure */
#define UTF_IGNORE      /* ignore failures */
#define UTF_STOPONSUITE /* stop on first suite failure */
#define UTF_STFULL      /* full output style */
#define UTF_STSHORT     /* short output style */

#define UTEST_INIT(flags) /* initialize the test framework */
#define UTEST_UNINIT()    /* uninitialize the test framework */

#define UTEST_CASE(name)     /* declare a test case */
#define UTEST_RUN_CASE(name) /* run a test case */

#define UTEST_SUITE(name)     /* declare a test suite*/
#define UTEST_SUITE_BEGIN()   /* begin a test suite */
#define UTEST_SUITE_END()     /* end a test suite */
#define UTEST_SUITE_ADD(name) /* add a test suite to list */
#define UTEST_RUN_SUITE(name) /* run a test suite */
#define UTEST_RUN_SUITES(ctx) /* run all test suites */
#ifndef UTEST_NOTHREADS
#define UTEST_RUN_SUITES_TH(                                                   \
    ctx, threads) /* run all test suites in multiple threads */
#endif

/* assertion macros */
#define EXPECT_TRUE(expr)
#define EXPECT_FALSE(expr)

#define EXPECT_NULL(ptr)
#define EXPECT_NOT_NULL(ptr)

#define EXPECT_EQ_INT(actual, expected)
#define EXPECT_NE_INT(actual, expected)
#define EXPECT_GT_INT(actual, expected)
#define EXPECT_GE_INT(actual, expected)
#define EXPECT_LT_INT(actual, expected)
#define EXPECT_LE_INT(actual, expected)

#define EXPECT_EQ_UINT(actual, expected)
#define EXPECT_NE_UINT(actual, expected)
#define EXPECT_GT_UINT(actual, expected)
#define EXPECT_GE_UINT(actual, expected)
#define EXPECT_LT_UINT(actual, expected)
#define EXPECT_LE_UINT(actual, expected)

#define EXPECT_EQ_STR(actual, expected)
#define EXPECT_NE_STR(actual, expected)
#define EXPECT_GT_STR(actual, expected)
#define EXPECT_GE_STR(actual, expected)
#define EXPECT_LT_STR(actual, expected)
#define EXPECT_LE_STR(actual, expected)

#define EXPECT_EQ_FLOAT(actual, expected)
#define EXPECT_NE_FLOAT(actual, expected)
#define EXPECT_GT_FLOAT(actual, expected)
#define EXPECT_GE_FLOAT(actual, expected)
#define EXPECT_LT_FLOAT(actual, expected)
#define EXPECT_LE_FLOAT(actual, expected)

#define EXPECT_EQ_CHAR(actual, expected)
#define EXPECT_NE_CHAR(actual, expected)
#define EXPECT_GT_CHAR(actual, expected)
#define EXPECT_GE_CHAR(actual, expected)
#define EXPECT_LT_CHAR(actual, expected)
#define EXPECT_LE_CHAR(actual, expected)

#define EXPECT_EQ_PTR(actual, expected)
#define EXPECT_NE_PTR(actual, expected)

#include <utest/assert.h>
#include <utest/core.h>
#include <utest/types.h>

#endif