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
UtestTestCaseType _CurrentTestCaseStatus;

static UTEST_STRING_TYPE _UtestTestCasePrefix = " |- ";

static void UtestInitStatus(){
    // Initialize the global status
    _UtestGlobalStatus.TestPassed = 0;
    _UtestGlobalStatus.TestFailed = 0;
    _UtestGlobalStatus.TestTotal = 0;
    _UtestGlobalStatus.TestFlag = UTEST_FLAG_DEFAULT;
    _UtestGlobalStatus.TestHasFailed = false;
    
    if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_SHOW_SUITE) {
        _UtestGlobalStatus.TestCasePrefix = _UtestTestCasePrefix;
    }else{
        _UtestGlobalStatus.TestCasePrefix = NULL;
    }

    // Initialize the current test case status
    _CurrentTestCaseStatus.TestCaseName = NULL;
    _CurrentTestCaseStatus.TestCaseStatus = UTEST_RESULT_SUCCESS;
}

static void UtestCaseMessage(UtestResultType result, UTEST_STRING_TYPE case_name){
    if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_SHOW_CASE) {
        if (_UtestGlobalStatus.TestCasePrefix != NULL) {
            fprintf(stdout, "%s", _UtestGlobalStatus.TestCasePrefix);
        }
        if (result == UTEST_RESULT_FAILURE){
            fprintf(stdout, "[" _ASCII_COLOR_RED "FAILED " _ASCII_COLOR_RESET "] ");
        }else{
            fprintf(stdout, "[" _ASCII_COLOR_GREEN "PASSED " _ASCII_COLOR_RESET "] ");
        }
        fprintf(stdout, "TEST CASE: %s\n", case_name);
    };
}

static void UtestSuiteMessage(UtestResultType result, UTEST_STRING_TYPE suite_name){
    if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_SHOW_SUITE) {
        if (result == UTEST_RESULT_FAILURE){
            fprintf(stdout, "[" _ASCII_COLOR_RED "FAILED " _ASCII_COLOR_RESET "] ");
        }else if (result == UTEST_RESULT_RUNNING){
            fprintf(stdout, "[" _ASCII_COLOR_YELLOW "RUNNING" _ASCII_COLOR_RESET "] ");
        }else{
            fprintf(stdout, "[" _ASCII_COLOR_GREEN "PASSED " _ASCII_COLOR_RESET "] ");
        }
        fprintf(stdout, "TEST SUITE: %s\n", suite_name);
    };
}

void UtestRunTestCase(UTEST_GENERAL_FUNC_PTR test_case_func, UTEST_STRING_TYPE case_name){
    // reinitialize the current test case status
    _CurrentTestCaseStatus.TestCaseName = case_name;
    _CurrentTestCaseStatus.TestCaseStatus = UTEST_RESULT_SUCCESS;
    // run the test case
    test_case_func();
    if (_CurrentTestCaseStatus.TestCaseStatus == UTEST_RESULT_SUCCESS){
        _UtestGlobalStatus.TestPassed++;
    }else{
        _UtestGlobalStatus.TestFailed++;
        _UtestGlobalStatus.TestHasFailed = true;
    }
    _UtestGlobalStatus.TestTotal++;
    // print the test case result
    UtestCaseMessage(_CurrentTestCaseStatus.TestCaseStatus, _CurrentTestCaseStatus.TestCaseName);
}
void UtestRunTestSuite(UTEST_GENERAL_FUNC_PTR test_suite_func, UTEST_STRING_TYPE suite_name){
    UtestSuiteMessage(UTEST_RESULT_RUNNING, suite_name);
    test_suite_func();
    if (_UtestGlobalStatus.TestHasFailed == true){
        _UtestGlobalStatus.TestHasFailed = false;
        UtestSuiteMessage(UTEST_RESULT_FAILURE, suite_name);
    }else{
        UtestSuiteMessage(UTEST_RESULT_SUCCESS, suite_name);
    }
}

void UtestBegin(){
    UtestInitStatus();
}
void UtestEnd(void) {
    if (_UtestGlobalStatus.TestFlag != UTEST_FLAG_NONE) {
        if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_STYLE_FULL){
            fprintf(stdout, "----------------------------------------\n");
            fprintf(stdout, "Total : %llu\n", _UtestGlobalStatus.TestTotal);
            fprintf(stdout, "Passed: %llu\n", _UtestGlobalStatus.TestPassed);
            fprintf(stdout, "Failed: %llu\n", _UtestGlobalStatus.TestFailed);
            fprintf(stdout, "----------------------------------------\n");
        }else if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_STYLE_SHORT){
            fprintf(stdout, "Passed: %llu/%llu\n", 
                    _UtestGlobalStatus.TestPassed, _UtestGlobalStatus.TestTotal);
        }
    }
}

void UtestSetFlag(const UTEST_FLAG_TYPE flag){
    _UtestGlobalStatus.TestFlag = flag;
    if (_UtestGlobalStatus.TestFlag & UTEST_FLAG_SHOW_SUITE) {
        _UtestGlobalStatus.TestCasePrefix = _UtestTestCasePrefix;
    }else{
        _UtestGlobalStatus.TestCasePrefix = NULL;
    }
}