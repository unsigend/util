#include <iniparse.h>
#include <string.h>
#include <utest.h>

UTEST_CASE(complex)
{
  struct iniparse_ctx ctx;
  iniparse_init(&ctx, "cases/iniparse/INI/complex.ini");
  iniparse_parse(&ctx);

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "editor"), "vim");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "excludesfile"), "~/.gitignore");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "autocrlf"), "input");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "safecrlf"), "warn");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "quotepath"), "false");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "ignorecase"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "longpaths"), "true");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "init", "defaultBranch"), "main");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "init", "templateDir"),
                "/usr/share/git-core/templates");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "alias", "st"), "status");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "alias", "co"), "checkout");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "alias", "br"), "branch");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "alias", "ci"), "commit");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "alias", "unstage"), "reset HEAD --");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "alias", "last"), "log -1 HEAD");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "alias", "visual"), "!gitk");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color", "ui"), "auto");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color", "diff"), "auto");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color", "status"), "auto");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color", "branch"), "auto");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color", "interactive"), "auto");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color", "help"), "auto");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color", "pager"), "true");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color \"diff\"", "meta"), "yellow bold");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color \"diff\"", "frag"), "magenta bold");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color \"diff\"", "old"), "red bold");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color \"diff\"", "new"), "green bold");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "color \"diff\"", "whitespace"),
                "red reverse");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "push", "default"), "simple");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "push", "followTags"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "push", "matching"), "true");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "remote \"origin\"", "url"),
                "git@github.com:username/repo.git");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "remote \"origin\"", "fetch"),
                "+refs/heads/*:refs/remotes/origin/*");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "remote \"origin\"", "pushurl"),
                "git@github.com:username/repo.git");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "remote \"origin\"", "push"),
                "refs/heads/main:refs/heads/main");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "branch \"main\"", "remote"), "origin");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "branch \"main\"", "merge"),
                "refs/heads/main");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "branch \"main\"", "rebase"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "branch \"main\"", "autostash"), "true");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "merge", "tool"), "vimdiff");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "merge", "conflictstyle"), "diff3");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "merge", "log"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "merge", "maxParents"), "2");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "merge \"custom-merge\"", "name"),
                "Custom Merge Driver");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "merge \"custom-merge\"", "driver"),
                "custom-merge-driver %O %A %B");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "merge \"custom-merge\"", "recursive"),
                "binary");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "filter \"lfs\"", "clean"),
                "git-lfs clean -- %f");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "filter \"lfs\"", "smudge"),
                "git-lfs smudge -- %f");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "filter \"lfs\"", "process"),
                "git-lfs filter-process");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "filter \"lfs\"", "required"), "true");

  EXPECT_NOTNULL(iniparse_getvalue(&ctx, "credential", "helper"));
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "credential", "store"), "true");

  EXPECT_NOTNULL(iniparse_getvalue(&ctx, "include", "path"));

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "user", "name"), "John Doe");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "user", "email"),
                "john.doe@example.com");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "user", "signingkey"), "ABCD1234");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "user", "sign"), "true");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "commit", "template"), "~/.gitmessage");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "commit", "gpgsign"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "commit", "cleanup"), "strip");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "commit", "verbose"), "true");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "status", "showStash"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "status", "showUntrackedFiles"), "all");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "status", "showIgnoredFiles"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "status", "submoduleSummary"), "true");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "url \"git@github.com:\"", "insteadOf"),
                "https://github.com/");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "url \"git@github.com:\"", "pushInsteadOf"),
                "git://github.com/");

  EXPECT_NULL(iniparse_getvalue(&ctx, "core", "nonexistent"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "nosuchsection", "key"));

  iniparse_fini(&ctx);
}
