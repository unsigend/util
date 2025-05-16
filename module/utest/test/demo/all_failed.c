#include <utest.h>
#include <stdbool.h>

// all of the assertions in this file are expected to fail

UTEST_TEST_CASE(boolean_assertion){
    bool true_value = true;
    bool false_value = false;
    EXPECT_TRUE(false_value);
    EXPECT_FALSE(true_value);
}
UTEST_TEST_CASE(pointer_assertion){
    int * ptr1 = NULL;
    int value = 0;
    int * ptr2 = &value;
    EXPECT_NULL(ptr2);
    EXPECT_NOT_NULL(ptr1);
}
UTEST_TEST_CASE(string_assertion){
    const char *str1 = "hello world";
    const char *str2 = "hello";
    const char *str3 = "hello world";
    EXPECT_EQUAL_STRING(str1, str2);
    EXPECT_NOT_EQUAL_STRING(str1, str3);
    EXPECT_GREATER_STRING(str2, str1);
    EXPECT_GREATER_EQUAL_STRING(str2, str1);
    EXPECT_LESS_STRING(str3, str2);
    EXPECT_LESS_EQUAL_STRING(str1, str2);
}
UTEST_TEST_CASE(float_assertion){
    float f1 = 1.0f;
    float f2 = 2.0f;
    EXPECT_EQUAL_FLOAT(f1, f2);
    EXPECT_NOT_EQUAL_FLOAT(f1, f1);
    EXPECT_GREATER_FLOAT(f1, f2);
    EXPECT_GREATER_EQUAL_FLOAT(f1, f2);
    EXPECT_LESS_FLOAT(f2, f1);
    EXPECT_LESS_EQUAL_FLOAT(f2, f1);
}
UTEST_TEST_CASE(double_assertion){
    double d1 = 1.0;
    double d2 = 2.0;
    EXPECT_EQUAL_DOUBLE(d1, d2);
    EXPECT_NOT_EQUAL_DOUBLE(d1, d1);
    EXPECT_GREATER_DOUBLE(d1, d2);
    EXPECT_GREATER_EQUAL_DOUBLE(d1, d2);
    EXPECT_LESS_DOUBLE(d2, d1);
    EXPECT_LESS_EQUAL_DOUBLE(d2, d1);
}

UTEST_TEST_CASE(unsigned_integer_assertion){
    EXPECT_EQUAL_UINT(0x00000ffff, 0x00000fffe);
    EXPECT_EQUAL_UINT8(0xff, 0xfe);
    EXPECT_EQUAL_UINT16(0xffff, 0xfffe);
    EXPECT_EQUAL_UINT32(0xffffffff, 0xfffffffe);
    EXPECT_EQUAL_UINT64(0xffffffffffffffff, 0xfffffffffffffffe);

    EXPECT_NOT_EQUAL_UINT(0x00000ffff, 0x00000ffff);
    EXPECT_NOT_EQUAL_UINT8(0xff, 0xff);
    EXPECT_NOT_EQUAL_UINT16(0xffff, 0xffff);
    EXPECT_NOT_EQUAL_UINT32(0xffffffff, 0xffffffff);
    EXPECT_NOT_EQUAL_UINT64(0xffffffffffffffff, 0xffffffffffffffff);

    EXPECT_GREATER_UINT(0x00000fffe, 0x00000ffff);
    EXPECT_GREATER_UINT8(0xfe, 0xff);
    EXPECT_GREATER_UINT16(0xfffe, 0xffff);
    EXPECT_GREATER_UINT32(0xfffffffe, 0xffffffff);
    EXPECT_GREATER_UINT64(0xfffffffffffffffe, 0xffffffffffffffff);

    EXPECT_GREATER_EQUAL_UINT(0x00000fffe, 0x00000ffff);
    EXPECT_GREATER_EQUAL_UINT8(0xfe, 0xff);
    EXPECT_GREATER_EQUAL_UINT16(0xfffe, 0xffff);
    EXPECT_GREATER_EQUAL_UINT32(0xfffffffe, 0xffffffff);
    EXPECT_GREATER_EQUAL_UINT64(0xfffffffffffffffe, 0xffffffffffffffff);

    EXPECT_LESS_UINT(0x00000ffff, 0x00000fffe);
    EXPECT_LESS_UINT8(0xff, 0xfe);
    EXPECT_LESS_UINT16(0xffff, 0xfffe);
    EXPECT_LESS_UINT32(0xffffffff, 0xfffffffe);
    EXPECT_LESS_UINT64(0xffffffffffffffff, 0xfffffffffffffffe);

    EXPECT_LESS_EQUAL_UINT(0x00000ffff, 0x00000fffe);
    EXPECT_LESS_EQUAL_UINT8(0xff, 0xfe);
    EXPECT_LESS_EQUAL_UINT16(0xffff, 0xfffe);
    EXPECT_LESS_EQUAL_UINT32(0xffffffff, 0xfffffffe);
    EXPECT_LESS_EQUAL_UINT64(0xffffffffffffffff, 0xfffffffffffffffe);
}
UTEST_TEST_CASE(signed_integer_assertion){
    EXPECT_EQUAL_INT(INT64_MAX, INT64_MIN);
    EXPECT_EQUAL_INT8(INT8_MAX, INT8_MIN);
    EXPECT_EQUAL_INT16(INT16_MAX, INT16_MIN);
    EXPECT_EQUAL_INT32(INT32_MAX, INT32_MIN);
    EXPECT_EQUAL_INT64(INT64_MAX, INT64_MIN);

    EXPECT_NOT_EQUAL_INT(INT64_MAX, INT64_MAX);
    EXPECT_NOT_EQUAL_INT8(INT8_MAX, INT8_MAX);
    EXPECT_NOT_EQUAL_INT16(INT16_MAX, INT16_MAX);
    EXPECT_NOT_EQUAL_INT32(INT32_MAX, INT32_MAX);
    EXPECT_NOT_EQUAL_INT64(INT64_MAX, INT64_MAX);

    EXPECT_GREATER_INT(INT64_MIN, INT64_MAX);
    EXPECT_GREATER_INT8(INT8_MIN, INT8_MAX);
    EXPECT_GREATER_INT16(INT16_MIN, INT16_MAX);
    EXPECT_GREATER_INT32(INT32_MIN, INT32_MAX);
    EXPECT_GREATER_INT64(INT64_MIN, INT64_MAX);

    EXPECT_GREATER_EQUAL_INT(INT64_MIN, INT64_MAX);
    EXPECT_GREATER_EQUAL_INT8(INT8_MIN, INT8_MAX);
    EXPECT_GREATER_EQUAL_INT16(INT16_MIN, INT16_MAX);
    EXPECT_GREATER_EQUAL_INT32(INT32_MIN, INT32_MAX);
    EXPECT_GREATER_EQUAL_INT64(INT64_MIN, INT64_MAX);

    EXPECT_LESS_INT(INT64_MAX, INT64_MIN);
    EXPECT_LESS_INT8(INT8_MAX, INT8_MIN);
    EXPECT_LESS_INT16(INT16_MAX, INT16_MIN);
    EXPECT_LESS_INT32(INT32_MAX, INT32_MIN);
    EXPECT_LESS_INT64(INT64_MAX, INT64_MIN);

    EXPECT_LESS_EQUAL_INT(INT64_MAX, INT64_MIN);
    EXPECT_LESS_EQUAL_INT8(INT8_MAX, INT8_MIN);
    EXPECT_LESS_EQUAL_INT16(INT16_MAX, INT16_MIN);
    EXPECT_LESS_EQUAL_INT32(INT32_MAX, INT32_MIN);
    EXPECT_LESS_EQUAL_INT64(INT64_MAX, INT64_MIN);
}
UTEST_TEST_SUITE(all_failed_test_suite){
    UTEST_CLEAR_FLAG(UTEST_FLAG_STOP_ON_FAILURE);
    UTEST_RUN_TEST_CASE(boolean_assertion);
    UTEST_RUN_TEST_CASE(pointer_assertion);
    UTEST_RUN_TEST_CASE(string_assertion);
    UTEST_RUN_TEST_CASE(float_assertion);
    UTEST_RUN_TEST_CASE(double_assertion);
    UTEST_RUN_TEST_CASE(unsigned_integer_assertion);
    UTEST_RUN_TEST_CASE(signed_integer_assertion);
    UTEST_SET_FLAG(UTEST_FLAG_STOP_ON_FAILURE);
}