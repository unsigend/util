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

#ifndef UTEST_CORE_H
#define UTEST_CORE_H

/* Internal implementation of the utest library, current at v1.1*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <string.h>
#include <utest/types.h>

extern UtestStateType gstate;

extern void UtestBegin();
extern void UtestEnd();
extern void UtestRunTestCase(utest_func_ptr caseptr, utest_string name);
extern void UtestRunTestSuite(utest_func_ptr suiteptr, utest_string name);
extern void UtestAssertionError(utest_string file, utest_int line,
                                const char *fmt, ...);

#ifdef __cplusplus
}
#endif

/* Compatibility macros for older version of utest library and keep the overall
   macros consistent standard. */

#define UTEST_UINT_TYPE utest_uint
#define UTEST_INT_TYPE utest_int
#define UTEST_UINT8_TYPE utest_u8
#define UTEST_INT8_TYPE utest_i8
#define UTEST_UINT16_TYPE utest_u16
#define UTEST_INT16_TYPE utest_i16
#define UTEST_UINT32_TYPE utest_u32
#define UTEST_INT32_TYPE utest_i32
#define UTEST_UINT64_TYPE utest_u64
#define UTEST_INT64_TYPE utest_i64
#define UTEST_CHAR_TYPE utest_char
#define UTEST_UCHAR_TYPE utest_uchar

/* utest library version macros */
#define _UTEST_VERSION_MAJOR 1
#define _UTEST_VERSION_MINOR 1

/* utility macros */
#define _UTEST_STRINGIFY(X) #X
#define UTEST_STRINGIFY(X) _UTEST_STRINGIFY(X)
#define UTEST_CONCATENATE(A, B) A##B
#define UTEST_CONCATENATE3(A, B, C)                                            \
  UTEST_CONCATENATE(A, UTEST_CONCATENATE(B, C))

/* flags for utest library */
#undef UTEST_FLAG_NONE
#undef UTEST_FLAG_SHOW_CASE
#undef UTEST_FLAG_SHOW_SUITE
#undef UTEST_FLAG_STYLE_FULL
#undef UTEST_FLAG_STOP_ON_FAILURE
#undef UTEST_FLAG_DEFAULT

#define UTEST_FLAG_NONE 0x00
#define UTEST_FLAG_SHOW_CASE 0x01
#define UTEST_FLAG_SHOW_SUITE 0x02
#define UTEST_FLAG_STYLE_FULL 0x04
#define UTEST_FLAG_STOP_ON_FAILURE 0x08
#define UTEST_FLAG_DEFAULT                                                     \
  (UTEST_FLAG_SHOW_CASE | UTEST_FLAG_SHOW_SUITE | UTEST_FLAG_STYLE_FULL |      \
   UTEST_FLAG_STOP_ON_FAILURE)

#undef UTEST_BEGIN
#undef UTEST_END
#undef UTEST_SET_FLAG
#undef UTEST_CLEAR_FLAG
#undef UTEST_FLAG_RESET
#undef UTEST_TEST_CASE
#undef UTEST_TEST_SUITE
#undef UTEST_RUN_TEST_CASE
#undef UTEST_RUN_TEST_SUITE

#undef UTEST_CASENAME_PREFIX
#undef UTEST_SUITENAME_PREFIX

#define UTEST_CASENAME_PREFIX utest_case_
#define UTEST_SUITENAME_PREFIX utest_suite_

#define UTEST_BEGIN() UtestBegin()
#define UTEST_END() UtestEnd()
#define UTEST_SET_FLAG(UTEST_FLAG) gstate.flag |= (UTEST_FLAG)
#define UTEST_CLEAR_FLAG(UTEST_FLAG) gstate.flag &= ~(UTEST_FLAG)
#define UTEST_FLAG_RESET() gstate.flag = UTEST_FLAG_DEFAULT
#define UTEST_TEST_CASE(TEST_CASE_NAME)                                        \
  static void UTEST_CONCATENATE(UTEST_CASENAME_PREFIX, TEST_CASE_NAME)(void)
#define UTEST_TEST_SUITE(TEST_SUITE_NAME)                                      \
  void UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, TEST_SUITE_NAME)(void)
#define UTEST_RUN_TEST_CASE(TEST_CASE_NAME)                                    \
  UtestRunTestCase(UTEST_CONCATENATE(UTEST_CASENAME_PREFIX, TEST_CASE_NAME),   \
                   UTEST_STRINGIFY(TEST_CASE_NAME))
#define UTEST_RUN_TEST_SUITE(TEST_SUITE_NAME)                                  \
  UtestRunTestSuite(                                                           \
      UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, TEST_SUITE_NAME),              \
      UTEST_STRINGIFY(TEST_SUITE_NAME))

#undef EXPECT_TRUE
#define EXPECT_TRUE(EXPRESSION)                                                \
  if (!(EXPRESSION)) {                                                         \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(EXPRESSION) " was true, actual was false");  \
  }

#undef EXPECT_FALSE
#define EXPECT_FALSE(EXPRESSION)                                               \
  if ((EXPRESSION)) {                                                          \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(EXPRESSION) " was false, actual was true");  \
  }

#undef EXPECT_NULL
#define EXPECT_NULL(POINTER)                                                   \
  if ((POINTER) != NULL) {                                                     \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(POINTER) " was NULL, actual was not NULL");  \
  }

#undef EXPECT_NOT_NULL
#define EXPECT_NOT_NULL(POINTER)                                               \
  if ((POINTER) == NULL) {                                                     \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(POINTER) " was not NULL, actual was NULL");  \
  }

#undef EXPECT_EQUAL_STRING
#define EXPECT_EQUAL_STRING(ACTUAL, EXPECTED)                                  \
  if (strcmp((ACTUAL), (EXPECTED)) != 0) {                                     \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(ACTUAL) " == \"%s\","                        \
                                          " actual was \"%s\"",                \
        EXPECTED, ACTUAL);                                                     \
  }

#undef EXPECT_NOT_EQUAL_STRING
#define EXPECT_NOT_EQUAL_STRING(ACTUAL, EXPECTED)                              \
  if (strcmp((ACTUAL), (EXPECTED)) == 0) {                                     \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(ACTUAL) " != \"%s\","                        \
                                          " actual was \"%s\"",                \
        EXPECTED, ACTUAL);                                                     \
  }

#undef EXPECT_GREATER_STRING
#define EXPECT_GREATER_STRING(ACTUAL, EXPECTED)                                \
  if (strcmp((ACTUAL), (EXPECTED)) <= 0) {                                     \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(ACTUAL) " > \"%s\","                         \
                                          " actual was \"%s\"",                \
        EXPECTED, ACTUAL);                                                     \
  }

#undef EXPECT_GREATER_EQUAL_STRING
#define EXPECT_GREATER_EQUAL_STRING(ACTUAL, EXPECTED)                          \
  if (strcmp((ACTUAL), (EXPECTED)) < 0) {                                      \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(ACTUAL) " >= \"%s\","                        \
                                          " actual was \"%s\"",                \
        EXPECTED, ACTUAL);                                                     \
  }

#undef EXPECT_LESS_STRING
#define EXPECT_LESS_STRING(ACTUAL, EXPECTED)                                   \
  if (strcmp((ACTUAL), (EXPECTED)) >= 0) {                                     \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(ACTUAL) " < \"%s\","                         \
                                          " actual was \"%s\"",                \
        EXPECTED, ACTUAL);                                                     \
  }

#undef EXPECT_LESS_EQUAL_STRING
#define EXPECT_LESS_EQUAL_STRING(ACTUAL, EXPECTED)                             \
  if (strcmp((ACTUAL), (EXPECTED)) > 0) {                                      \
    UtestAssertionError(                                                       \
        __FILE__, __LINE__,                                                    \
        "expect " UTEST_STRINGIFY(ACTUAL) " <= \"%s\","                        \
                                          " actual was \"%s\"",                \
        EXPECTED, ACTUAL);                                                     \
  }

#undef EXPECT_EQUAL_FLOAT
#define EXPECT_EQUAL_FLOAT(ACTUAL, EXPECTED)                                   \
  if ((ACTUAL) != (EXPECTED)) {                                                \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " == %f,"            \
                                                          " actual was %f",    \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_NOT_EQUAL_FLOAT
#define EXPECT_NOT_EQUAL_FLOAT(ACTUAL, EXPECTED)                               \
  if ((ACTUAL) == (EXPECTED)) {                                                \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " != %f,"            \
                                                          " actual was %f",    \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_GREATER_FLOAT
#define EXPECT_GREATER_FLOAT(ACTUAL, EXPECTED)                                 \
  if ((ACTUAL) <= (EXPECTED)) {                                                \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " > %f,"             \
                                                          " actual was %f",    \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_GREATER_EQUAL_FLOAT
#define EXPECT_GREATER_EQUAL_FLOAT(ACTUAL, EXPECTED)                           \
  if ((ACTUAL) < (EXPECTED)) {                                                 \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " >= %f,"            \
                                                          " actual was %f",    \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_LESS_FLOAT
#define EXPECT_LESS_FLOAT(ACTUAL, EXPECTED)                                    \
  if ((ACTUAL) >= (EXPECTED)) {                                                \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " < %f,"             \
                                                          " actual was %f",    \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_LESS_EQUAL_FLOAT
#define EXPECT_LESS_EQUAL_FLOAT(ACTUAL, EXPECTED)                              \
  if ((ACTUAL) > (EXPECTED)) {                                                 \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " <= %f,"            \
                                                          " actual was %f",    \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_EQUAL_DOUBLE
#define EXPECT_EQUAL_DOUBLE(ACTUAL, EXPECTED)                                  \
  if ((ACTUAL) != (EXPECTED)) {                                                \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " == %lf,"           \
                                                          " actual was %lf",   \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_NOT_EQUAL_DOUBLE
#define EXPECT_NOT_EQUAL_DOUBLE(ACTUAL, EXPECTED)                              \
  if ((ACTUAL) == (EXPECTED)) {                                                \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " != %lf,"           \
                                                          " actual was %lf",   \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_GREATER_DOUBLE
#define EXPECT_GREATER_DOUBLE(ACTUAL, EXPECTED)                                \
  if ((ACTUAL) <= (EXPECTED)) {                                                \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " > %lf,"            \
                                                          " actual was %lf",   \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_GREATER_EQUAL_DOUBLE
#define EXPECT_GREATER_EQUAL_DOUBLE(ACTUAL, EXPECTED)                          \
  if ((ACTUAL) < (EXPECTED)) {                                                 \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " >= %lf,"           \
                                                          " actual was %lf",   \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_LESS_DOUBLE
#define EXPECT_LESS_DOUBLE(ACTUAL, EXPECTED)                                   \
  if ((ACTUAL) >= (EXPECTED)) {                                                \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " < %lf,"            \
                                                          " actual was %lf",   \
                        EXPECTED, ACTUAL);                                     \
  }

#undef EXPECT_LESS_EQUAL_DOUBLE
#define EXPECT_LESS_EQUAL_DOUBLE(ACTUAL, EXPECTED)                             \
  if ((ACTUAL) > (EXPECTED)) {                                                 \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " <= %lf,"           \
                                                          " actual was %lf",   \
                        EXPECTED, ACTUAL);                                     \
  }

/* Internal macros for type assertion */
#define EXPECT_EQUAL_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                         \
  if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) != (UTEST_UINT_TYPE)(TYPE)(EXPECTED)) {  \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " == %llu,"          \
                                                          " actual was %llu",  \
                        (UTEST_UINT_TYPE)EXPECTED, (UTEST_UINT_TYPE)ACTUAL);   \
  }
#define EXPECT_NOT_EQUAL_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                     \
  if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) == (UTEST_UINT_TYPE)(TYPE)(EXPECTED)) {  \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " != %llu,"          \
                                                          " actual was %llu",  \
                        (UTEST_UINT_TYPE)EXPECTED, (UTEST_UINT_TYPE)ACTUAL);   \
  }
#define EXPECT_GREATER_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                       \
  if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) <= (UTEST_UINT_TYPE)(TYPE)(EXPECTED)) {  \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " > %llu,"           \
                                                          " actual was %llu",  \
                        (UTEST_UINT_TYPE)EXPECTED, (UTEST_UINT_TYPE)ACTUAL);   \
  }
#define EXPECT_GREATER_EQUAL_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                 \
  if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) < (UTEST_UINT_TYPE)(TYPE)(EXPECTED)) {   \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " >= %llu,"          \
                                                          " actual was %llu",  \
                        (UTEST_UINT_TYPE)EXPECTED, (UTEST_UINT_TYPE)ACTUAL);   \
  }
#define EXPECT_LESS_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                          \
  if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) >= (UTEST_UINT_TYPE)(TYPE)(EXPECTED)) {  \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " < %llu,"           \
                                                          " actual was %llu",  \
                        (UTEST_UINT_TYPE)EXPECTED, (UTEST_UINT_TYPE)ACTUAL);   \
  }
#define EXPECT_LESS_EQUAL_UINT_TYPE(TYPE, ACTUAL, EXPECTED)                    \
  if ((UTEST_UINT_TYPE)(TYPE)(ACTUAL) > (UTEST_UINT_TYPE)(TYPE)(EXPECTED)) {   \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " <= %llu,"          \
                                                          " actual was %llu",  \
                        (UTEST_UINT_TYPE)EXPECTED, (UTEST_UINT_TYPE)ACTUAL);   \
  }

#define EXPECT_EQUAL_INT_TYPE(TYPE, ACTUAL, EXPECTED)                          \
  if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) != (UTEST_INT_TYPE)(TYPE)(EXPECTED)) {    \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " == %lld,"          \
                                                          " actual was %lld",  \
                        (UTEST_INT_TYPE)EXPECTED, (UTEST_INT_TYPE)ACTUAL);     \
  }
#define EXPECT_NOT_EQUAL_INT_TYPE(TYPE, ACTUAL, EXPECTED)                      \
  if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) == (UTEST_INT_TYPE)(TYPE)(EXPECTED)) {    \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " != %lld,"          \
                                                          " actual was %lld",  \
                        (UTEST_INT_TYPE)EXPECTED, (UTEST_INT_TYPE)ACTUAL);     \
  }
#define EXPECT_GREATER_INT_TYPE(TYPE, ACTUAL, EXPECTED)                        \
  if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) <= (UTEST_INT_TYPE)(TYPE)(EXPECTED)) {    \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " > %lld,"           \
                                                          " actual was %lld",  \
                        (UTEST_INT_TYPE)EXPECTED, (UTEST_INT_TYPE)ACTUAL);     \
  }
#define EXPECT_GREATER_EQUAL_INT_TYPE(TYPE, ACTUAL, EXPECTED)                  \
  if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) < (UTEST_INT_TYPE)(TYPE)(EXPECTED)) {     \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " >= %lld,"          \
                                                          " actual was %lld",  \
                        (UTEST_INT_TYPE)EXPECTED, (UTEST_INT_TYPE)ACTUAL);     \
  }
#define EXPECT_LESS_INT_TYPE(TYPE, ACTUAL, EXPECTED)                           \
  if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) >= (UTEST_INT_TYPE)(TYPE)(EXPECTED)) {    \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " < %lld,"           \
                                                          " actual was %lld",  \
                        (UTEST_INT_TYPE)EXPECTED, (UTEST_INT_TYPE)ACTUAL);     \
  }
#define EXPECT_LESS_EQUAL_INT_TYPE(TYPE, ACTUAL, EXPECTED)                     \
  if ((UTEST_INT_TYPE)(TYPE)(ACTUAL) > (UTEST_INT_TYPE)(TYPE)(EXPECTED)) {     \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " <= %lld,"          \
                                                          " actual was %lld",  \
                        (UTEST_INT_TYPE)EXPECTED, (UTEST_INT_TYPE)ACTUAL);     \
  }
#define EXPECT_EQUAL_CHAR_TYPE(TYPE, ACTUAL, EXPECTED)                         \
  if ((TYPE)(ACTUAL) != (TYPE)(EXPECTED)) {                                    \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " == '%c',"          \
                                                          " actual was '%c'",  \
                        (TYPE)EXPECTED, (TYPE)ACTUAL);                         \
  }
#define EXPECT_NOT_EQUAL_CHAR_TYPE(TYPE, ACTUAL, EXPECTED)                     \
  if ((TYPE)(ACTUAL) == (TYPE)(EXPECTED)) {                                    \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " != '%c',"          \
                                                          " actual was '%c'",  \
                        (TYPE)EXPECTED, (TYPE)ACTUAL);                         \
  }
#define EXPECT_GREATER_CHAR_TYPE(TYPE, ACTUAL, EXPECTED)                       \
  if ((TYPE)(ACTUAL) <= (TYPE)(EXPECTED)) {                                    \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " > '%c',"           \
                                                          " actual was '%c'",  \
                        (TYPE)EXPECTED, (TYPE)ACTUAL);                         \
  }
#define EXPECT_GREATER_EQUAL_CHAR_TYPE(TYPE, ACTUAL, EXPECTED)                 \
  if ((TYPE)(ACTUAL) < (TYPE)(EXPECTED)) {                                     \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " >= '%c',"          \
                                                          " actual was '%c'",  \
                        (TYPE)EXPECTED, (TYPE)ACTUAL);                         \
  }
#define EXPECT_LESS_CHAR_TYPE(TYPE, ACTUAL, EXPECTED)                          \
  if ((TYPE)(ACTUAL) >= (TYPE)(EXPECTED)) {                                    \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " < '%c',"           \
                                                          " actual was '%c'",  \
                        (TYPE)EXPECTED, (TYPE)ACTUAL);                         \
  }
#define EXPECT_LESS_EQUAL_CHAR_TYPE(TYPE, ACTUAL, EXPECTED)                    \
  if ((TYPE)(ACTUAL) > (TYPE)(EXPECTED)) {                                     \
    UtestAssertionError(__FILE__, __LINE__,                                    \
                        "expect " UTEST_STRINGIFY(ACTUAL) " <= '%c',"          \
                                                          " actual was '%c'",  \
                        (TYPE)EXPECTED, (TYPE)ACTUAL);                         \
  }

#undef EXPECT_EQUAL_UINT
#undef EXPECT_EQUAL_UINT8
#undef EXPECT_EQUAL_UINT16
#undef EXPECT_EQUAL_UINT32
#undef EXPECT_EQUAL_UINT64

#define EXPECT_EQUAL_UINT(ACTUAL, EXPECTED)                                    \
  EXPECT_EQUAL_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_EQUAL_UINT8(ACTUAL, EXPECTED)                                   \
  EXPECT_EQUAL_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_EQUAL_UINT16(ACTUAL, EXPECTED)                                  \
  EXPECT_EQUAL_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_EQUAL_UINT32(ACTUAL, EXPECTED)                                  \
  EXPECT_EQUAL_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_EQUAL_UINT64(ACTUAL, EXPECTED)                                  \
  EXPECT_EQUAL_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_NOT_EQUAL_UINT
#undef EXPECT_NOT_EQUAL_UINT8
#undef EXPECT_NOT_EQUAL_UINT16
#undef EXPECT_NOT_EQUAL_UINT32
#undef EXPECT_NOT_EQUAL_UINT64

#define EXPECT_NOT_EQUAL_UINT(ACTUAL, EXPECTED)                                \
  EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UINT8(ACTUAL, EXPECTED)                               \
  EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UINT16(ACTUAL, EXPECTED)                              \
  EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UINT32(ACTUAL, EXPECTED)                              \
  EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UINT64(ACTUAL, EXPECTED)                              \
  EXPECT_NOT_EQUAL_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_GREATER_UINT
#undef EXPECT_GREATER_UINT8
#undef EXPECT_GREATER_UINT16
#undef EXPECT_GREATER_UINT32
#undef EXPECT_GREATER_UINT64

#define EXPECT_GREATER_UINT(ACTUAL, EXPECTED)                                  \
  EXPECT_GREATER_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_UINT8(ACTUAL, EXPECTED)                                 \
  EXPECT_GREATER_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_UINT16(ACTUAL, EXPECTED)                                \
  EXPECT_GREATER_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_UINT32(ACTUAL, EXPECTED)                                \
  EXPECT_GREATER_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_UINT64(ACTUAL, EXPECTED)                                \
  EXPECT_GREATER_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_GREATER_EQUAL_UINT
#undef EXPECT_GREATER_EQUAL_UINT8
#undef EXPECT_GREATER_EQUAL_UINT16
#undef EXPECT_GREATER_EQUAL_UINT32
#undef EXPECT_GREATER_EQUAL_UINT64

#define EXPECT_GREATER_EQUAL_UINT(ACTUAL, EXPECTED)                            \
  EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UINT8(ACTUAL, EXPECTED)                           \
  EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UINT16(ACTUAL, EXPECTED)                          \
  EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UINT32(ACTUAL, EXPECTED)                          \
  EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UINT64(ACTUAL, EXPECTED)                          \
  EXPECT_GREATER_EQUAL_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_LESS_UINT
#undef EXPECT_LESS_UINT8
#undef EXPECT_LESS_UINT16
#undef EXPECT_LESS_UINT32
#undef EXPECT_LESS_UINT64

#define EXPECT_LESS_UINT(ACTUAL, EXPECTED)                                     \
  EXPECT_LESS_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_UINT8(ACTUAL, EXPECTED)                                    \
  EXPECT_LESS_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_UINT16(ACTUAL, EXPECTED)                                   \
  EXPECT_LESS_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_UINT32(ACTUAL, EXPECTED)                                   \
  EXPECT_LESS_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_UINT64(ACTUAL, EXPECTED)                                   \
  EXPECT_LESS_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_LESS_EQUAL_UINT
#undef EXPECT_LESS_EQUAL_UINT8
#undef EXPECT_LESS_EQUAL_UINT16
#undef EXPECT_LESS_EQUAL_UINT32
#undef EXPECT_LESS_EQUAL_UINT64

#define EXPECT_LESS_EQUAL_UINT(ACTUAL, EXPECTED)                               \
  EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_UINT8(ACTUAL, EXPECTED)                              \
  EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_UINT16(ACTUAL, EXPECTED)                             \
  EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_UINT32(ACTUAL, EXPECTED)                             \
  EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_UINT64(ACTUAL, EXPECTED)                             \
  EXPECT_LESS_EQUAL_UINT_TYPE(UTEST_UINT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_EQUAL_INT
#undef EXPECT_EQUAL_INT8
#undef EXPECT_EQUAL_INT16
#undef EXPECT_EQUAL_INT32
#undef EXPECT_EQUAL_INT64

#define EXPECT_EQUAL_INT(ACTUAL, EXPECTED)                                     \
  EXPECT_EQUAL_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_EQUAL_INT8(ACTUAL, EXPECTED)                                    \
  EXPECT_EQUAL_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_EQUAL_INT16(ACTUAL, EXPECTED)                                   \
  EXPECT_EQUAL_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_EQUAL_INT32(ACTUAL, EXPECTED)                                   \
  EXPECT_EQUAL_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_EQUAL_INT64(ACTUAL, EXPECTED)                                   \
  EXPECT_EQUAL_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_NOT_EQUAL_INT
#undef EXPECT_NOT_EQUAL_INT8
#undef EXPECT_NOT_EQUAL_INT16
#undef EXPECT_NOT_EQUAL_INT32
#undef EXPECT_NOT_EQUAL_INT64

#define EXPECT_NOT_EQUAL_INT(ACTUAL, EXPECTED)                                 \
  EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_INT8(ACTUAL, EXPECTED)                                \
  EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_INT16(ACTUAL, EXPECTED)                               \
  EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_INT32(ACTUAL, EXPECTED)                               \
  EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_INT64(ACTUAL, EXPECTED)                               \
  EXPECT_NOT_EQUAL_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_GREATER_INT
#undef EXPECT_GREATER_INT8
#undef EXPECT_GREATER_INT16
#undef EXPECT_GREATER_INT32
#undef EXPECT_GREATER_INT64

#define EXPECT_GREATER_INT(ACTUAL, EXPECTED)                                   \
  EXPECT_GREATER_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_INT8(ACTUAL, EXPECTED)                                  \
  EXPECT_GREATER_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_INT16(ACTUAL, EXPECTED)                                 \
  EXPECT_GREATER_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_INT32(ACTUAL, EXPECTED)                                 \
  EXPECT_GREATER_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_INT64(ACTUAL, EXPECTED)                                 \
  EXPECT_GREATER_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_GREATER_EQUAL_INT
#undef EXPECT_GREATER_EQUAL_INT8
#undef EXPECT_GREATER_EQUAL_INT16
#undef EXPECT_GREATER_EQUAL_INT32
#undef EXPECT_GREATER_EQUAL_INT64

#define EXPECT_GREATER_EQUAL_INT(ACTUAL, EXPECTED)                             \
  EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_INT8(ACTUAL, EXPECTED)                            \
  EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_INT16(ACTUAL, EXPECTED)                           \
  EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_INT32(ACTUAL, EXPECTED)                           \
  EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_INT64(ACTUAL, EXPECTED)                           \
  EXPECT_GREATER_EQUAL_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_LESS_INT
#undef EXPECT_LESS_INT8
#undef EXPECT_LESS_INT16
#undef EXPECT_LESS_INT32
#undef EXPECT_LESS_INT64

#define EXPECT_LESS_INT(ACTUAL, EXPECTED)                                      \
  EXPECT_LESS_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_INT8(ACTUAL, EXPECTED)                                     \
  EXPECT_LESS_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_INT16(ACTUAL, EXPECTED)                                    \
  EXPECT_LESS_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_INT32(ACTUAL, EXPECTED)                                    \
  EXPECT_LESS_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_INT64(ACTUAL, EXPECTED)                                    \
  EXPECT_LESS_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_LESS_EQUAL_INT
#undef EXPECT_LESS_EQUAL_INT8
#undef EXPECT_LESS_EQUAL_INT16
#undef EXPECT_LESS_EQUAL_INT32
#undef EXPECT_LESS_EQUAL_INT64

#define EXPECT_LESS_EQUAL_INT(ACTUAL, EXPECTED)                                \
  EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_INT8(ACTUAL, EXPECTED)                               \
  EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT8_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_INT16(ACTUAL, EXPECTED)                              \
  EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT16_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_INT32(ACTUAL, EXPECTED)                              \
  EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT32_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_INT64(ACTUAL, EXPECTED)                              \
  EXPECT_LESS_EQUAL_INT_TYPE(UTEST_INT64_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_EQUAL_CHAR
#undef EXPECT_NOT_EQUAL_CHAR
#undef EXPECT_GREATER_CHAR
#undef EXPECT_GREATER_EQUAL_CHAR
#undef EXPECT_LESS_CHAR
#undef EXPECT_LESS_EQUAL_CHAR

#define EXPECT_EQUAL_CHAR(ACTUAL, EXPECTED)                                    \
  EXPECT_EQUAL_CHAR_TYPE(UTEST_CHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_CHAR(ACTUAL, EXPECTED)                                \
  EXPECT_NOT_EQUAL_CHAR_TYPE(UTEST_CHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_CHAR(ACTUAL, EXPECTED)                                  \
  EXPECT_GREATER_CHAR_TYPE(UTEST_CHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_CHAR(ACTUAL, EXPECTED)                            \
  EXPECT_GREATER_EQUAL_CHAR_TYPE(UTEST_CHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_CHAR(ACTUAL, EXPECTED)                                     \
  EXPECT_LESS_CHAR_TYPE(UTEST_CHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_CHAR(ACTUAL, EXPECTED)                               \
  EXPECT_LESS_EQUAL_CHAR_TYPE(UTEST_CHAR_TYPE, ACTUAL, EXPECTED)

#undef EXPECT_EQUAL_UCHAR
#undef EXPECT_NOT_EQUAL_UCHAR
#undef EXPECT_GREATER_UCHAR
#undef EXPECT_GREATER_EQUAL_UCHAR
#undef EXPECT_LESS_UCHAR
#undef EXPECT_LESS_EQUAL_UCHAR

#define EXPECT_EQUAL_UCHAR(ACTUAL, EXPECTED)                                   \
  EXPECT_EQUAL_CHAR_TYPE(UTEST_UCHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_NOT_EQUAL_UCHAR(ACTUAL, EXPECTED)                               \
  EXPECT_NOT_EQUAL_CHAR_TYPE(UTEST_UCHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_UCHAR(ACTUAL, EXPECTED)                                 \
  EXPECT_GREATER_CHAR_TYPE(UTEST_UCHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_GREATER_EQUAL_UCHAR(ACTUAL, EXPECTED)                           \
  EXPECT_GREATER_EQUAL_CHAR_TYPE(UTEST_UCHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_UCHAR(ACTUAL, EXPECTED)                                    \
  EXPECT_LESS_CHAR_TYPE(UTEST_UCHAR_TYPE, ACTUAL, EXPECTED)
#define EXPECT_LESS_EQUAL_UCHAR(ACTUAL, EXPECTED)                              \
  EXPECT_LESS_EQUAL_CHAR_TYPE(UTEST_UCHAR_TYPE, ACTUAL, EXPECTED)

#endif