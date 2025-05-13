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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
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

/**
 * The Utest flag is used to control the behavior of the utest library.
 * The default value is UTEST_FLAG_DEFAULT.
 * You can set the flag to UTEST_FLAG_NONE to disable all features
 * through the UTEST_SET_FLAGS macro.
 */

/**
 * @brief the none flag
 */
#define UTEST_FLAG_NONE
/**
 * @brief the default flag
 */
#define UTEST_FLAG_DEFAULT
/**
 * @brief the flag to show the test case message
 */
#define UTEST_FLAG_SHOW_CASE
/**
 * @brief the flag to show the test suite message
 */
#define UTEST_FLAG_SHOW_SUITE

/**
 * @brief declare a test case
 * @param TEST_CASE_NAME The name of the test case
 */
#define UTEST_TEST_CASE(TEST_CASE_NAME)
/**
 * @brief run a test case
 * @param TEST_CASE_NAME The name of the test case
 */
#define UTEST_RUN_TEST_CASE(TEST_CASE_NAME)


/**
 * @brief declare a test suite
 * @param TEST_SUITE_NAME The name of the test suite
 */
#define UTEST_TEST_SUITE(TEST_SUITE_NAME)
/**
 * @brief run a test suite
 * @param TEST_SUITE_NAME The name of the test suite
 */
#define UTEST_RUN_TEST_SUITE(TEST_SUITE_NAME)


/**
 * @brief set the flags for the utest library
 * @param UTEST_FLAG The flag to set
 */
#define UTEST_SET_FLAGS(UTEST_FLAG)


/**
 * @brief expect something to be equal
 * @param EXPECTED The expected value
 * @param ACTUAL The actual value
 */
#define UTEST_EXPECT_EQUAL(EXPECTED, ACTUAL)
/**
 * @brief expect something to not be equal
 * @param EXPECTED The expected value
 * @param ACTUAL The actual value
 */
#define UTEST_EXPECT_NOT_EQUAL(EXPECTED, ACTUAL)
/**
 * @brief expect something to be true
 * @param EXPRESSION The expression to evaluate
 */
#define UTEST_EXPECT_TRUE(EXPRESSION)
/**
 * @brief expect something to be false
 * @param EXPRESSION The expression to evaluate
 */
#define UTEST_EXPECT_FALSE(EXPRESSION)
/**
 * @brief expect the pointer to be null
 * @param POINTER The pointer to evaluate
 */
#define UTEST_EXPECT_NULL(POINTER)
/**
 * @brief expect the pointer to not be null
 * @param POINTER The pointer to evaluate
 */
#define UTEST_EXPECT_NOT_NULL(POINTER)
/**
 * @brief expect something to be greater than
 * @param EXPECTED The expected value
 * @param ACTUAL The actual value
 */
#define UTEST_EXPECT_GREATER(EXPECTED, ACTUAL)
/**
 * @brief expect something to be less than
 * @param EXPECTED The expected value
 * @param ACTUAL The actual value
 */
#define UTEST_EXPECT_LESS(EXPECTED, ACTUAL)
/**
 * @brief expect something to be greater than or equal to
 * @param EXPECTED The expected value
 * @param ACTUAL The actual value
 */
#define UTEST_EXPECT_GREATER_EQUAL(EXPECTED, ACTUAL)
/**
 * @brief expect something to be less than or equal to
 * @param EXPECTED The expected value
 * @param ACTUAL The actual value
 */
#define UTEST_EXPECT_LESS_EQUAL(EXPECTED, ACTUAL)

#include <utest/utest_internals.h>
#endif