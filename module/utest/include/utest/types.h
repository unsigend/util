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
#ifndef UTEST_TYPES_H
#define UTEST_TYPES_H

#include <stdbool.h>

typedef signed char utest_i8;
typedef signed short utest_i16;
typedef signed int utest_i32;
typedef signed long long utest_i64;

typedef unsigned char utest_u8;
typedef unsigned short utest_u16;
typedef unsigned int utest_u32;
typedef unsigned long long utest_u64;

typedef utest_i64 utest_int;
typedef utest_u64 utest_uint;
typedef float utest_float;
typedef double utest_double;
typedef bool utest_bool;
typedef utest_uint utest_counter;
typedef utest_uint utest_flag;
typedef const char *utest_string;
typedef char utest_char;
typedef unsigned char utest_uchar;

typedef void (*utest_func_ptr)(void);

typedef enum {
  UTEST_RESULT_SUCCESS,
  UTEST_RESULT_FAILURE,
  UTEST_RESULT_RUNNING,
} UtestResultType;

typedef enum {
  UTEST_CMP_EQUAL,
  UTEST_CMP_NOT_EQUAL,
  UTEST_CMP_GREATER,
  UTEST_CMP_GREATER_EQUAL,
  UTEST_CMP_LESS,
  UTEST_CMP_LESS_EQUAL,
  UTEST_CMP_NULL,
  UTEST_CMP_NOT_NULL,
} UtestCompareType;

typedef struct {
  utest_string name;
  utest_bool failed;
} UtestSuiteType;

typedef struct {
  utest_string name;
  utest_bool failed;
} UtestCaseType;

typedef struct {
  utest_counter npass;
  utest_counter nfail;
  utest_counter ntotal;
  utest_flag flag;
} UtestStateType;

#endif