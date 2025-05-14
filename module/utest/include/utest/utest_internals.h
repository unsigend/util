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

#ifndef UTEST_INTERNALS_H
#define UTEST_INTERNALS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <utest/utest_types.h>

extern void UtestRunTestCase(UTEST_GENERAL_FUNC_PTR test_case_func, UTEST_STRING_TYPE case_name);
extern void UtestRunTestSuite(UTEST_GENERAL_FUNC_PTR test_suite_func, UTEST_STRING_TYPE suite_name);
extern void UtestSetFlag(const UTEST_FLAG_TYPE flag);
extern void UtestBegin();
extern void UtestEnd(void);

extern UtestGlobalStatusType _UtestGlobalStatus;

#ifdef __cplusplus
}  
#endif

#define _UTEST_STRINGIFY(X)         # X
#define UTEST_STRINGIFY(X)          _UTEST_STRINGIFY(X)
#define UTEST_CONCATENATE(A, B)     A ## B
#define UTEST_CONCATENATE3(A, B, C) UTEST_CONCATENATE(A, UTEST_CONCATENATE(B, C))

// flags for utest library
#undef UTEST_FLAG_NONE
#undef UTEST_FLAG_SHOW_CASE
#undef UTEST_FLAG_SHOW_SUITE
#undef UTEST_FLAG_STOP_ON_FAILURE
#undef UTEST_FLAG_CONTINUE_ON_FAILURE
#undef UTEST_FLAG_DEFAULT

#define UTEST_FLAG_NONE                 0x00
#define UTEST_FLAG_SHOW_CASE            0x01
#define UTEST_FLAG_SHOW_SUITE           0x02
#define UTEST_FLAG_STYLE_FULL           0x04
#define UTEST_FLAG_STYLE_SHORT          0x08
#define UTEST_FLAG_DEFAULT              (UTEST_FLAG_SHOW_CASE | UTEST_FLAG_SHOW_SUITE \
                                        | UTEST_FLAG_STYLE_FULL)

#define _UTEST_BEGIN()                              UtestBegin()
#define _UTEST_END()                                UtestEnd()
#define _UTEST_SET_FLAG(UTEST_FLAG)                 UtestSetFlag(UTEST_FLAG)
#define _UTEST_TEST_CASE(TEST_CASE_NAME)            static void UTEST_CONCATENATE(utest_case_, TEST_CASE_NAME)(void)
#define _UTEST_TEST_SUITE(TEST_SUITE_NAME)          void UTEST_CONCATENATE(utest_suite_, TEST_SUITE_NAME)(void)
#define _UTEST_RUN_TEST_CASE(TEST_CASE_NAME)        UtestRunTestCase(UTEST_CONCATENATE(utest_case_, TEST_CASE_NAME), \
                                                    UTEST_STRINGIFY(TEST_CASE_NAME))
#define _UTEST_RUN_TEST_SUITE(TEST_SUITE_NAME)      UtestRunTestSuite(UTEST_CONCATENATE(utest_suite_, TEST_SUITE_NAME), \
                                                    UTEST_STRINGIFY(TEST_SUITE_NAME))


#endif