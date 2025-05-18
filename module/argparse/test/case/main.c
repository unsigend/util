#include <utest.h>

extern UTEST_TEST_SUITE(test_type_parse);

int main(int argc, char *argv[]){
    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

    UTEST_RUN_TEST_SUITE(test_type_parse);

    UTEST_END();
    return 0;
}