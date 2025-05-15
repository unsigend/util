// Using Utest library

#include <utest.h>
#include <stdio.h>

extern UTEST_TEST_SUITE(simple_test_suite);
extern UTEST_TEST_SUITE(complex_test_suite);

int main(int argc, char * argv[]){
    UTEST_BEGIN();

    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);
    UTEST_CLEAR_FLAG(UTEST_FLAG_SHOW_CASE);

    UTEST_RUN_TEST_SUITE(simple_test_suite);
    UTEST_RUN_TEST_SUITE(complex_test_suite);

    UTEST_END();
    return 0;
}