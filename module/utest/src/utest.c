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

/**
 * This file is part of the utest library.
 * Implement the core logic of the utest library.
 */

#include <stdio.h>
#include <utest/utest_internals.h>

#define _ASCII_COLOR_RED        "\033[31m"
#define _ASCII_COLOR_GREEN      "\033[32m"
#define _ASCII_COLOR_YELLOW     "\033[33m"
#define _ASCII_COLOR_BLUE       "\033[34m"
#define _ASCII_COLOR_MAGENTA    "\033[35m"
#define _ASCII_COLOR_CYAN       "\033[36m"
#define _ASCII_COLOR_WHITE      "\033[37m"
#define _ASCII_COLOR_RESET      "\033[0m"
#define _ASCII_COLOR_BOLD       "\033[1m"

UtestGlobalStatusType _UtestGlobalStatus;

void UtestInitStatus(UTEST_FLAG_TYPE flag){
    _UtestGlobalStatus.TestPassed = 0;
    _UtestGlobalStatus.TestFailed = 0;
    _UtestGlobalStatus.TestTotal = 0;
    _UtestGlobalStatus.TestFlag = flag;
}
void UtestResetStatus(void){
    _UtestGlobalStatus.TestPassed = 0;
    _UtestGlobalStatus.TestFailed = 0;
    _UtestGlobalStatus.TestTotal = 0;
}
void UtestCaseMessage(UtestResultType result, UTEST_STRING_TYPE case_name){
    if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_SHOW_CASE) {
        if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_SHOW_SUITE){
            fprintf(stdout, " |- ");
        }
        if (result == UTEST_RESULT_FAILURE){
            fprintf(stdout, "[" _ASCII_COLOR_RED "FAILED" _ASCII_COLOR_RESET "] ");
        }else{
            fprintf(stdout, "[" _ASCII_COLOR_GREEN "PASSED" _ASCII_COLOR_RESET "] ");
        }
        fprintf(stdout, "TEST CASE: %s\n", case_name);
    };
}

void UtestSuiteMessage(UtestResultType result, UTEST_STRING_TYPE suite_name){
    if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_SHOW_SUITE) {
        if (result == UTEST_RESULT_FAILURE){
            fprintf(stdout, "[" _ASCII_COLOR_RED "FAILED" _ASCII_COLOR_RESET "] ");
        }else{
            fprintf(stdout, "[" _ASCII_COLOR_GREEN "PASSED" _ASCII_COLOR_RESET "] ");
        }
        fprintf(stdout, "TEST SUITE: %s\n", suite_name);
    };
}

void UtestAssertErrorMessage(UTEST_STRING_TYPE expected, UTEST_STRING_TYPE actual,
    UTEST_STRING_TYPE filename, UTEST_COUNTER_TYPE line){
    if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_SHOW_CASE) {
        fprintf(stdout, " |- ");
    }
}