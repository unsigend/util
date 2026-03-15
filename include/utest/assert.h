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

#ifndef UTEST_ASSERT_H
#define UTEST_ASSERT_H

#undef EXPECT_TRUE
#undef EXPECT_FALSE
#define EXPECT_TRUE(expr)
#define EXPECT_FALSE(expr)

#undef EXPECT_NULL
#undef EXPECT_NOT_NULL
#define EXPECT_NULL(ptr)
#define EXPECT_NOT_NULL(ptr)

#undef EXPECT_EQ_INT
#undef EXPECT_NE_INT
#undef EXPECT_GT_INT
#undef EXPECT_GE_INT
#undef EXPECT_LT_INT
#undef EXPECT_LE_INT
#define EXPECT_EQ_INT(actual, expected)
#define EXPECT_NE_INT(actual, expected)
#define EXPECT_GT_INT(actual, expected)
#define EXPECT_GE_INT(actual, expected)
#define EXPECT_LT_INT(actual, expected)
#define EXPECT_LE_INT(actual, expected)

#undef EXPECT_EQ_UINT
#undef EXPECT_NE_UINT
#undef EXPECT_GT_UINT
#undef EXPECT_GE_UINT
#undef EXPECT_LT_UINT
#undef EXPECT_LE_UINT
#define EXPECT_EQ_UINT(actual, expected)
#define EXPECT_NE_UINT(actual, expected)
#define EXPECT_GT_UINT(actual, expected)
#define EXPECT_GE_UINT(actual, expected)
#define EXPECT_LT_UINT(actual, expected)
#define EXPECT_LE_UINT(actual, expected)

#undef EXPECT_EQ_STR
#undef EXPECT_NE_STR
#undef EXPECT_GT_STR
#undef EXPECT_GE_STR
#undef EXPECT_LT_STR
#undef EXPECT_LE_STR
#define EXPECT_EQ_STR(actual, expected)
#define EXPECT_NE_STR(actual, expected)
#define EXPECT_GT_STR(actual, expected)
#define EXPECT_GE_STR(actual, expected)
#define EXPECT_LT_STR(actual, expected)
#define EXPECT_LE_STR(actual, expected)

#undef EXPECT_EQ_FLOAT
#undef EXPECT_NE_FLOAT
#undef EXPECT_GT_FLOAT
#undef EXPECT_GE_FLOAT
#undef EXPECT_LT_FLOAT
#undef EXPECT_LE_FLOAT
#define EXPECT_EQ_FLOAT(actual, expected)
#define EXPECT_NE_FLOAT(actual, expected)
#define EXPECT_GT_FLOAT(actual, expected)
#define EXPECT_GE_FLOAT(actual, expected)
#define EXPECT_LT_FLOAT(actual, expected)
#define EXPECT_LE_FLOAT(actual, expected)

#undef EXPECT_EQ_CHAR
#undef EXPECT_NE_CHAR
#undef EXPECT_GT_CHAR
#undef EXPECT_GE_CHAR
#undef EXPECT_LT_CHAR
#undef EXPECT_LE_CHAR
#define EXPECT_EQ_CHAR(actual, expected)
#define EXPECT_NE_CHAR(actual, expected)
#define EXPECT_GT_CHAR(actual, expected)
#define EXPECT_GE_CHAR(actual, expected)
#define EXPECT_LT_CHAR(actual, expected)
#define EXPECT_LE_CHAR(actual, expected)

#undef EXPECT_EQ_PTR
#undef EXPECT_NE_PTR
#define EXPECT_EQ_PTR(actual, expected)
#define EXPECT_NE_PTR(actual, expected)

#endif