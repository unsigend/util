#include <utest.h>
#include <stdbool.h>
#include <stdint.h>
// all of the assertions in this file are expected to pass

UTEST_TEST_CASE(boolean_assertion){
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}
UTEST_TEST_CASE(pointer_assertion){
    int data = 0;
    EXPECT_NULL(NULL);
    EXPECT_NOT_NULL(&data);
}
UTEST_TEST_CASE(string_assertion){
    EXPECT_EQUAL_STRING("hello", "hello");
    EXPECT_NOT_EQUAL_STRING("hello", "world");
    EXPECT_GREATER_STRING("hello", "hell");
    EXPECT_GREATER_EQUAL_STRING("hello", "hell");
    EXPECT_LESS_STRING("hell", "hello");
    EXPECT_LESS_EQUAL_STRING("hell", "hello");
}
// UTEST_TEST_CASE(float_assertion){
//     EXPECT_EQUAL_FLOAT(1.0f, 1.0f);
//     EXPECT_NOT_EQUAL_FLOAT(1.0f, 2.0f);
//     EXPECT_GREATER_FLOAT(2.0f, 1.0f);
//     EXPECT_GREATER_EQUAL_FLOAT(2.0f, 1.0f);
//     EXPECT_LESS_FLOAT(1.0f, 2.0f);
//     EXPECT_LESS_EQUAL_FLOAT(1.0f, 2.0f);
// }
// UTEST_TEST_CASE(double_assertion){
//     EXPECT_EQUAL_DOUBLE(1.0, 1.0);
//     EXPECT_NOT_EQUAL_DOUBLE(1.0, 2.0);
//     EXPECT_GREATER_DOUBLE(2.0, 1.0);
//     EXPECT_GREATER_EQUAL_DOUBLE(2.0, 1.0);
//     EXPECT_LESS_DOUBLE(1.0, 2.0);
//     EXPECT_LESS_EQUAL_DOUBLE(1.0, 2.0);
// }

// UTEST_TEST_CASE(unsigned_integer_assertion){
//     EXPECT_EQUAL_UINT(0x00000ffff, 0x00000ffff);
//     EXPECT_EQUAL_UINT8(0xff, 0xff);
//     EXPECT_EQUAL_UINT16(0xffff, 0xffff);
//     EXPECT_EQUAL_UINT32(0xffffffff, 0xffffffff);
//     EXPECT_EQUAL_UINT64(0xffffffffffffffff, 0xffffffffffffffff);

//     EXPECT_NOT_EQUAL_UINT(0x00000ffff, 0x00000fffe);
//     EXPECT_NOT_EQUAL_UINT8(0xff, 0xfe);
//     EXPECT_NOT_EQUAL_UINT16(0xffff, 0xfffe);
//     EXPECT_NOT_EQUAL_UINT32(0xffffffff, 0xfffffffe);
//     EXPECT_NOT_EQUAL_UINT64(0xffffffffffffffff, 0xfffffffffffffffe);

//     EXPECT_GREATER_UINT(0x00000ffff, 0x00000fffe);
//     EXPECT_GREATER_UINT8(0xff, 0xfe);
//     EXPECT_GREATER_UINT16(0xffff, 0xfffe);
//     EXPECT_GREATER_UINT32(0xffffffff, 0xfffffffe);
//     EXPECT_GREATER_UINT64(0xffffffffffffffff, 0xfffffffffffffffe);

//     EXPECT_GREATER_EQUAL_UINT(0x00000ffff, 0x00000fffe);
//     EXPECT_GREATER_EQUAL_UINT8(0xff, 0xfe);
//     EXPECT_GREATER_EQUAL_UINT16(0xffff, 0xfffe);
//     EXPECT_GREATER_EQUAL_UINT32(0xffffffff, 0xfffffffe);
//     EXPECT_GREATER_EQUAL_UINT64(0xffffffffffffffff, 0xfffffffffffffffe);

//     EXPECT_LESS_UINT(0x00000fffe, 0x00000ffff);
//     EXPECT_LESS_UINT8(0xfe, 0xff);
//     EXPECT_LESS_UINT16(0xfffe, 0xffff);
//     EXPECT_LESS_UINT32(0xfffffffe, 0xffffffff);
//     EXPECT_LESS_UINT64(0xfffffffffffffffe, 0xffffffffffffffff);

//     EXPECT_LESS_EQUAL_UINT(0x00000fffe, 0x00000ffff);
//     EXPECT_LESS_EQUAL_UINT8(0xfe, 0xff);
//     EXPECT_LESS_EQUAL_UINT16(0xfffe, 0xffff);
//     EXPECT_LESS_EQUAL_UINT32(0xfffffffe, 0xffffffff);
//     EXPECT_LESS_EQUAL_UINT64(0xfffffffffffffffe, 0xffffffffffffffff);
// }

// UTEST_TEST_CASE(signed_integer_assertion){
//     EXPECT_EQUAL_INT(0x00000ffff, 0x00000ffff);
//     EXPECT_EQUAL_INT8(0xff, 0xff);
//     EXPECT_EQUAL_INT16(0xffff, 0xffff);
//     EXPECT_EQUAL_INT32(0xffffffff, 0xffffffff);
//     EXPECT_EQUAL_INT64(0xffffffffffffffff, 0xffffffffffffffff);

//     EXPECT_NOT_EQUAL_INT(0x00000ffff, 0x00000fffe);
//     EXPECT_NOT_EQUAL_INT8(0xff, 0xfe);
//     EXPECT_NOT_EQUAL_INT16(0xffff, 0xfffe);
//     EXPECT_NOT_EQUAL_INT32(0xffffffff, 0xfffffffe);
//     EXPECT_NOT_EQUAL_INT64(0xffffffffffffffff, 0xfffffffffffffffe);

//     EXPECT_GREATER_INT(INT64_MAX, INT64_MIN);
//     EXPECT_GREATER_INT8(INT8_MAX, INT8_MIN);
//     EXPECT_GREATER_INT16(INT16_MAX, INT16_MIN);
//     EXPECT_GREATER_INT32(INT32_MAX, INT32_MIN);
//     EXPECT_GREATER_INT64(INT64_MAX, INT64_MIN);

//     EXPECT_GREATER_EQUAL_INT(INT64_MAX, INT64_MIN);
//     EXPECT_GREATER_EQUAL_INT8(INT8_MAX, INT8_MIN);
//     EXPECT_GREATER_EQUAL_INT16(INT16_MAX, INT16_MIN);
//     EXPECT_GREATER_EQUAL_INT32(INT32_MAX, INT32_MIN);
//     EXPECT_GREATER_EQUAL_INT64(INT64_MAX, INT64_MIN);

//     EXPECT_LESS_INT(INT64_MIN, INT64_MAX);
//     EXPECT_LESS_INT8(INT8_MIN, INT8_MAX);
//     EXPECT_LESS_INT16(INT16_MIN, INT16_MAX);
//     EXPECT_LESS_INT32(INT32_MIN, INT32_MAX);
//     EXPECT_LESS_INT64(INT64_MIN, INT64_MAX);

//     EXPECT_LESS_EQUAL_INT(INT64_MIN, INT64_MAX);
//     EXPECT_LESS_EQUAL_INT8(INT8_MIN, INT8_MAX);
//     EXPECT_LESS_EQUAL_INT16(INT16_MIN, INT16_MAX);
//     EXPECT_LESS_EQUAL_INT32(INT32_MIN, INT32_MAX);
//     EXPECT_LESS_EQUAL_INT64(INT64_MIN, INT64_MAX);
// }

UTEST_TEST_SUITE(all_passed_test_suite){
    UTEST_RUN_TEST_CASE(boolean_assertion);
    UTEST_RUN_TEST_CASE(pointer_assertion);
    UTEST_RUN_TEST_CASE(string_assertion);
    // UTEST_RUN_TEST_CASE(float_assertion);
    // UTEST_RUN_TEST_CASE(double_assertion);
    // UTEST_RUN_TEST_CASE(unsigned_integer_assertion);
    // UTEST_RUN_TEST_CASE(signed_integer_assertion);

}