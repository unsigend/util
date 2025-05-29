#include <utest.h>
#include <configparse.h>

extern const char * simple_filename;
extern const char * complex_filename;

UTEST_TEST_CASE(configparse_get_value_simple){
    struct configparse configparse;
    EXPECT_TRUE(init_configparse(&configparse, simple_filename));

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

UTEST_TEST_CASE(configparse_get_value_complex){
    struct configparse configparse;
    EXPECT_TRUE(init_configparse(&configparse, complex_filename));

    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "editor"), "vim");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "excludesfile"), "~/.gitignore");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "autocrlf"), "input");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "safecrlf"), "warn");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "quotepath"), "false");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "ignorecase"), "true");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "core", "longpaths"), "true");

    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "init", "defaultBranch"), "main");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "init", "templateDir"), "/usr/share/git-core/templates");

    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "alias", "st"), "status");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "alias", "co"), "checkout");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "alias", "br"), "branch");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "alias", "ci"), "commit");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "alias", "unstage"), "reset HEAD --");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "alias", "last"), "log -1 HEAD");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "alias", "visual"), "!gitk");

    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "color", "ui"), "auto");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "color", "diff"), "auto");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "color", "status"), "auto");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "color", "branch"), "auto");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "color", "interactive"), "auto");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "color", "help"), "auto");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "color", "pager"), "true");

    EXPECT_NULL(configparse_get_value(&configparse, "color", "non-exist"));
    EXPECT_NULL(configparse_get_value(&configparse, "non-exist", "ui"));
    EXPECT_NULL(configparse_get_value(&configparse, "non-exist", "non-exist"));
    EXPECT_NULL(configparse_get_value(&configparse, "non-exist", "non-exist"));


    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "remote \"origin\"", "url"), "git@github.com:username/repo.git");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "remote \"origin\"", "fetch"), "+refs/heads/*:refs/remotes/origin/*");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "remote \"origin\"", "pushurl"), "git@github.com:username/repo.git");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "remote \"origin\"", "push"), "refs/heads/main:refs/heads/main");

    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "branch \"main\"", "remote"), "origin");
    EXPECT_EQUAL_STRING(configparse_get_value(&configparse, "branch \"main\"", "merge"), "refs/heads/main");

    
}
UTEST_TEST_SUITE(get_value){
    UTEST_RUN_TEST_CASE(configparse_get_value_simple);
    UTEST_RUN_TEST_CASE(configparse_get_value_complex);
}

