#include <utest.h>

extern UTEST_TEST_SUITE(file_reading);
extern UTEST_TEST_SUITE(get_value);

// relative path to the util project
const char * filename = "module/configparse/test/cases/INI/simple.ini";

int main(int argc, char * argv[]){
    (void)argc;
    (void)argv;

    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

    UTEST_RUN_TEST_SUITE(file_reading);
    UTEST_RUN_TEST_SUITE(get_value);

    UTEST_END();
    return 0;
}