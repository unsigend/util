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

typedef uint32_t        UTEST_BOOLEAN_TYPE;
typedef uint32_t        UTEST_FLAG_TYPE;
typedef uint64_t        UTEST_COUNTER_TYPE;
typedef const char *    UTEST_STRING_TYPE;

typedef enum{
    UTEST_RESULT_SUCCESS,
    UTEST_RESULT_FAILURE,
} UtestResultType;


typedef struct{
    UTEST_COUNTER_TYPE  TestPassed;
    UTEST_COUNTER_TYPE  TestFailed;
    UTEST_COUNTER_TYPE  TestTotal;
    UTEST_FLAG_TYPE     TestFlag;
}UtestGlobalStatusType;

typedef struct{
    UTEST_STRING_TYPE TestCaseName;
    UtestResultType   TestCaseStatus;
}UtestTestCaseType;

#endif