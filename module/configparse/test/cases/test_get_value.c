#include <utest.h>
#include <configparse.h>

extern const char * filename;

UTEST_TEST_CASE(configparse_get_value_simple){
    struct configparse configparse;
    EXPECT_TRUE(init_configparse(&configparse, filename));

    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "repositoryFormat"), "0");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "fileMode"), "true");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "bare"), "false");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "global"), "true");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "ignoreCase"), "true");

    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "remote \"origin\"", "url"), "git@github.com");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "remote \"origin\"", "fetch"), "refs/heads/");

    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "branch \"main\"", "remote"), "origin");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "branch \"main\"", "merge"), "refs/heads/main");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "branch \"main\"", "vscode-merge-base"), "origin/main");
}
UTEST_TEST_SUITE(get_value){
    UTEST_RUN_TEST_CASE(configparse_get_value_simple);
}

