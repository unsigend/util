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
#ifndef UTEST_TYPES_H
#define UTEST_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef int8_t              UTEST_INT8_TYPE;
typedef int16_t             UTEST_INT16_TYPE;
typedef int32_t             UTEST_INT32_TYPE;
typedef int64_t             UTEST_INT64_TYPE;

typedef uint8_t             UTEST_UINT8_TYPE;
typedef uint16_t            UTEST_UINT16_TYPE;
typedef uint32_t            UTEST_UINT32_TYPE;
typedef uint64_t            UTEST_UINT64_TYPE;

typedef int64_t             UTEST_INT_TYPE;
typedef uint64_t            UTEST_UINT_TYPE;
typedef float               UTEST_FLOAT_TYPE;
typedef double              UTEST_DOUBLE_TYPE;
typedef bool                UTEST_BOOLEAN_TYPE;
typedef UTEST_UINT_TYPE     UTEST_COUNTER_TYPE;
typedef UTEST_UINT64_TYPE   UTEST_FLAG_TYPE;
typedef const char *        UTEST_STRING_TYPE;
typedef void (*UTEST_GENERAL_FUNC_PTR)(void);

typedef enum{
    UTEST_RESULT_SUCCESS,
    UTEST_RESULT_FAILURE,
    UTEST_RESULT_RUNNING,
} UtestResultType;

typedef enum{
    UTEST_COMPARISON_EQUAL,
    UTEST_COMPARISON_NOT_EQUAL,
    UTEST_COMPARISON_LESS,
    UTEST_COMPARISON_LESS_EQUAL,
    UTEST_COMPARISON_GREATER,
    UTEST_COMPARISON_GREATER_EQUAL,
} UtestComparisonType;

typedef struct{
    UTEST_COUNTER_TYPE  TestPassed;
    UTEST_COUNTER_TYPE  TestFailed;
    UTEST_COUNTER_TYPE  TestTotal;
    UTEST_FLAG_TYPE     TestFlag;
    UTEST_STRING_TYPE   TestCasePrefix;
    UTEST_BOOLEAN_TYPE  TestHasFailed;
} UtestGlobalStatusType;

typedef struct{
    UTEST_STRING_TYPE TestCaseName;
    UtestResultType   TestCaseStatus;
} UtestTestCaseType;

#endif