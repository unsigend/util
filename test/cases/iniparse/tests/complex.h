#include <iniparse.h>
#include <string.h>
#include <utest.h>

UTEST_CASE(complex)
{
  struct iniFILE *fp = iniparse_open("cases/iniparse/INI/complex.ini");
  EXPECT_NOTNULL(fp);
  EXPECT_EQ_INT(iniparse_parse(fp), 0);

  EXPECT_EQ_STR(iniparse_get(fp, "core", "editor"), "vim");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "excludesfile"), "~/.gitignore");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "autocrlf"), "input");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "safecrlf"), "warn");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "quotepath"), "false");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "ignorecase"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "longpaths"), "true");

  EXPECT_EQ_STR(iniparse_get(fp, "init", "defaultBranch"), "main");
  EXPECT_EQ_STR(iniparse_get(fp, "init", "templateDir"),
                "/usr/share/git-core/templates");

  EXPECT_EQ_STR(iniparse_get(fp, "alias", "st"), "status");
  EXPECT_EQ_STR(iniparse_get(fp, "alias", "co"), "checkout");
  EXPECT_EQ_STR(iniparse_get(fp, "alias", "br"), "branch");
  EXPECT_EQ_STR(iniparse_get(fp, "alias", "ci"), "commit");
  EXPECT_EQ_STR(iniparse_get(fp, "alias", "unstage"), "reset HEAD --");
  EXPECT_EQ_STR(iniparse_get(fp, "alias", "last"), "log -1 HEAD");
  EXPECT_EQ_STR(iniparse_get(fp, "alias", "visual"), "!gitk");

  EXPECT_EQ_STR(iniparse_get(fp, "color", "ui"), "auto");
  EXPECT_EQ_STR(iniparse_get(fp, "color", "diff"), "auto");
  EXPECT_EQ_STR(iniparse_get(fp, "color", "status"), "auto");
  EXPECT_EQ_STR(iniparse_get(fp, "color", "branch"), "auto");
  EXPECT_EQ_STR(iniparse_get(fp, "color", "interactive"), "auto");
  EXPECT_EQ_STR(iniparse_get(fp, "color", "help"), "auto");
  EXPECT_EQ_STR(iniparse_get(fp, "color", "pager"), "true");

  EXPECT_EQ_STR(iniparse_get(fp, "color \"diff\"", "meta"), "yellow bold");
  EXPECT_EQ_STR(iniparse_get(fp, "color \"diff\"", "frag"), "magenta bold");
  EXPECT_EQ_STR(iniparse_get(fp, "color \"diff\"", "old"), "red bold");
  EXPECT_EQ_STR(iniparse_get(fp, "color \"diff\"", "new"), "green bold");
  EXPECT_EQ_STR(iniparse_get(fp, "color \"diff\"", "whitespace"),
                "red reverse");

  EXPECT_EQ_STR(iniparse_get(fp, "push", "default"), "simple");
  EXPECT_EQ_STR(iniparse_get(fp, "push", "followTags"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "push", "matching"), "true");

  EXPECT_EQ_STR(iniparse_get(fp, "remote \"origin\"", "url"),
                "git@github.com:username/repo.git");
  EXPECT_EQ_STR(iniparse_get(fp, "remote \"origin\"", "fetch"),
                "+refs/heads/*:refs/remotes/origin/*");
  EXPECT_EQ_STR(iniparse_get(fp, "remote \"origin\"", "pushurl"),
                "git@github.com:username/repo.git");
  EXPECT_EQ_STR(iniparse_get(fp, "remote \"origin\"", "push"),
                "refs/heads/main:refs/heads/main");

  EXPECT_EQ_STR(iniparse_get(fp, "branch \"main\"", "remote"), "origin");
  EXPECT_EQ_STR(iniparse_get(fp, "branch \"main\"", "merge"),
                "refs/heads/main");
  EXPECT_EQ_STR(iniparse_get(fp, "branch \"main\"", "rebase"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "branch \"main\"", "autostash"), "true");

  EXPECT_EQ_STR(iniparse_get(fp, "merge", "tool"), "vimdiff");
  EXPECT_EQ_STR(iniparse_get(fp, "merge", "conflictstyle"), "diff3");
  EXPECT_EQ_STR(iniparse_get(fp, "merge", "log"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "merge", "maxParents"), "2");

  EXPECT_EQ_STR(iniparse_get(fp, "merge \"custom-merge\"", "name"),
                "Custom Merge Driver");
  EXPECT_EQ_STR(iniparse_get(fp, "merge \"custom-merge\"", "driver"),
                "custom-merge-driver %O %A %B");
  EXPECT_EQ_STR(iniparse_get(fp, "merge \"custom-merge\"", "recursive"),
                "binary");

  EXPECT_EQ_STR(iniparse_get(fp, "filter \"lfs\"", "clean"),
                "git-lfs clean -- %f");
  EXPECT_EQ_STR(iniparse_get(fp, "filter \"lfs\"", "smudge"),
                "git-lfs smudge -- %f");
  EXPECT_EQ_STR(iniparse_get(fp, "filter \"lfs\"", "process"),
                "git-lfs filter-process");
  EXPECT_EQ_STR(iniparse_get(fp, "filter \"lfs\"", "required"), "true");

  EXPECT_NOTNULL(iniparse_get(fp, "credential", "helper"));
  EXPECT_EQ_STR(iniparse_get(fp, "credential", "store"), "true");

  EXPECT_NOTNULL(iniparse_get(fp, "include", "path"));

  EXPECT_EQ_STR(iniparse_get(fp, "user", "name"), "John Doe");
  EXPECT_EQ_STR(iniparse_get(fp, "user", "email"), "john.doe@example.com");
  EXPECT_EQ_STR(iniparse_get(fp, "user", "signingkey"), "ABCD1234");
  EXPECT_EQ_STR(iniparse_get(fp, "user", "sign"), "true");

  EXPECT_EQ_STR(iniparse_get(fp, "commit", "template"), "~/.gitmessage");
  EXPECT_EQ_STR(iniparse_get(fp, "commit", "gpgsign"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "commit", "cleanup"), "strip");
  EXPECT_EQ_STR(iniparse_get(fp, "commit", "verbose"), "true");

  EXPECT_EQ_STR(iniparse_get(fp, "status", "showStash"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "status", "showUntrackedFiles"), "all");
  EXPECT_EQ_STR(iniparse_get(fp, "status", "showIgnoredFiles"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "status", "submoduleSummary"), "true");

  EXPECT_EQ_STR(iniparse_get(fp, "url \"git@github.com:\"", "insteadOf"),
                "https://github.com/");
  EXPECT_EQ_STR(iniparse_get(fp, "url \"git@github.com:\"", "pushInsteadOf"),
                "git://github.com/");

  EXPECT_NULL(iniparse_get(fp, "core", "nonexistent"));
  EXPECT_NULL(iniparse_get(fp, "nosuchsection", "key"));

  iniparse_close(fp);
}
