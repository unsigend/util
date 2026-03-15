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

#ifndef UTEST_CORE_H
#define UTEST_CORE_H

#undef UTF_STOPONFIRST
#undef UTF_IGNORE
#undef UTF_STOPONSUITE
#undef UTF_STFULL
#undef UTF_STSHORT

#define UTF_STOPONFIRST 0x01
#define UTF_IGNORE 0x02
#define UTF_STOPONSUITE 0x04
#define UTF_STFULL 0x08
#define UTF_STSHORT 0x10

#undef UTEST_INIT
#undef UTEST_UNINIT

#define UTEST_INIT(flags)
#define UTEST_UNINIT()

#undef UTEST_CASE
#undef UTEST_RUN_CASE

#define UTEST_CASE(name)
#define UTEST_RUN_CASE(name)

#undef UTEST_SUITE
#undef UTEST_SUITE_BEGIN
#undef UTEST_SUITE_END
#undef UTEST_SUITE_ADD
#undef UTEST_RUN_SUITE
#undef UTEST_RUN_SUITES
#ifndef UTEST_NOTHREADS
#undef UTEST_RUN_SUITES_TH
#endif

#define UTEST_SUITE(name)
#define UTEST_SUITE_BEGIN()
#define UTEST_SUITE_END()
#define UTEST_SUITE_ADD(name)
#define UTEST_RUN_SUITE(name)
#define UTEST_RUN_SUITES(ctx)

#ifndef UTEST_NOTHREADS
#define UTEST_RUN_SUITES_TH(ctx, threads)
#endif

#endif