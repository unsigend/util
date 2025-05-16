// Using Utest library

#include <utest.h>
#include <stdio.h>

extern UTEST_TEST_SUITE(simple_test_suite);
extern UTEST_TEST_SUITE(all_passed_test_suite);
extern UTEST_TEST_SUITE(all_failed_test_suite);

int main(int argc, char * argv[]){
    UTEST_BEGIN();

    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

    // simple test suite just as a demo
    // UTEST_RUN_TEST_SUITE(simple_test_suite);

    // run the all passed test suite
    UTEST_RUN_TEST_SUITE(all_passed_test_suite);

    // Uncomment the following line to run the all failed test suite
    // UTEST_RUN_TEST_SUITE(all_failed_test_suite);

    UTEST_END();
    return 0;
}