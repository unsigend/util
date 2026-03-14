#include <iniparse.h>
#include <stdio.h>
#include <string.h>
#include <utest.h>

extern const char *simple_filename;
extern const char *complex_filename;

UTEST_TEST_CASE(get_val)
{
  {
    struct iniparse iniparse;
    EXPECT_TRUE(iniparse_init(&iniparse, simple_filename));

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "repositoryFormat"),
                        "0");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "fileMode"), "true");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "bare"), "false");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "global"), "true");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "ignoreCase"),
                        "true");

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "remote \"origin\"", "url"),
                        "git@github.com");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "remote \"origin\"", "fetch"),
                        "refs/heads/");

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "branch \"main\"", "remote"),
                        "origin");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "branch \"main\"", "merge"),
                        "refs/heads/main");
    EXPECT_EQUAL_STRING(
        iniparse_value(&iniparse, "branch \"main\"", "vscode-merge-base"),
        "origin/main");
  }
  {
    struct iniparse iniparse;
    EXPECT_TRUE(iniparse_init(&iniparse, complex_filename));

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "editor"), "vim");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "excludesfile"),
                        "~/.gitignore");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "autocrlf"), "input");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "safecrlf"), "warn");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "quotepath"),
                        "false");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "ignorecase"),
                        "true");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "core", "longpaths"), "true");

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "init", "defaultBranch"),
                        "main");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "init", "templateDir"),
                        "/usr/share/git-core/templates");

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "alias", "st"), "status");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "alias", "co"), "checkout");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "alias", "br"), "branch");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "alias", "ci"), "commit");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "alias", "unstage"),
                        "reset HEAD --");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "alias", "last"),
                        "log -1 HEAD");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "alias", "visual"), "!gitk");

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "color", "ui"), "auto");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "color", "diff"), "auto");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "color", "status"), "auto");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "color", "branch"), "auto");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "color", "interactive"),
                        "auto");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "color", "help"), "auto");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "color", "pager"), "true");

    EXPECT_NULL(iniparse_value(&iniparse, "color", "non-exist"));
    EXPECT_NULL(iniparse_value(&iniparse, "non-exist", "ui"));
    EXPECT_NULL(iniparse_value(&iniparse, "non-exist", "non-exist"));
    EXPECT_NULL(iniparse_value(&iniparse, "non-exist", "non-exist"));

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "remote \"origin\"", "url"),
                        "git@github.com:username/repo.git");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "remote \"origin\"", "fetch"),
                        "+refs/heads/*:refs/remotes/origin/*");
    EXPECT_EQUAL_STRING(
        iniparse_value(&iniparse, "remote \"origin\"", "pushurl"),
        "git@github.com:username/repo.git");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "remote \"origin\"", "push"),
                        "refs/heads/main:refs/heads/main");

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "branch \"main\"", "remote"),
                        "origin");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "branch \"main\"", "merge"),
                        "refs/heads/main");

    EXPECT_EQUAL_STRING(
        iniparse_value(&iniparse, "merge \"custom-merge\"", "name"),
        "Custom Merge Driver");
    EXPECT_EQUAL_STRING(
        iniparse_value(&iniparse, "merge \"custom-merge\"", "driver"),
        "custom-merge-driver %O %A %B");
    EXPECT_EQUAL_STRING(
        iniparse_value(&iniparse, "merge \"custom-merge\"", "recursive"),
        "binary");

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "filter \"lfs\"", "clean"),
                        "git-lfs clean -- %f");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "filter \"lfs\"", "smudge"),
                        "git-lfs smudge -- %f");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "filter \"lfs\"", "process"),
                        "git-lfs filter-process");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "filter \"lfs\"", "required"),
                        "true");

    EXPECT_NULL(iniparse_value(&iniparse, "diff", "algorithm"));
    EXPECT_NULL(iniparse_value(&iniparse, "diff", "tool"));
    EXPECT_NULL(iniparse_value(&iniparse, "diff", "wordRegex"));
    EXPECT_NULL(iniparse_value(&iniparse, "diff", "context"));
    EXPECT_NULL(iniparse_value(&iniparse, "diff", "lineLength"));

    EXPECT_EQUAL_STRING(
        iniparse_value(&iniparse, "url \"git@github.com:\"", "insteadOf"),
        "https://github.com/");
    EXPECT_EQUAL_STRING(
        iniparse_value(&iniparse, "url \"git@github.com:\"", "pushInsteadOf"),
        "git://github.com/");

    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "status", "showStash"),
                        "true");
    EXPECT_EQUAL_STRING(
        iniparse_value(&iniparse, "status", "showUntrackedFiles"), "all");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "status", "showIgnoredFiles"),
                        "true");
    EXPECT_EQUAL_STRING(iniparse_value(&iniparse, "status", "submoduleSummary"),
                        "true");
  }
}
