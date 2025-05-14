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

extern void UtestCaseMessage(UtestResultType result, UTEST_STRING_TYPE case_name);
extern void UtestSuiteMessage(UtestResultType result, UTEST_STRING_TYPE suite_name);
extern void UtestInitStatus(UTEST_FLAG_TYPE flag);
extern void UtestResetStatus(void);

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
#define UTEST_FLAG_STOP_ON_FAILURE      0x04
#define UTEST_FLAG_CONTINUE_ON_FAILURE  0x08
#define UTEST_FLAG_DEFAULT         (UTEST_FLAG_SHOW_CASE | UTEST_FLAG_SHOW_SUITE \
                                    | UTEST_FLAG_STOP_ON_FAILURE)


#endif