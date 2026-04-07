#include <iniparse.h>
#include <string.h>
#include <utest.h>

UTEST_CASE(simple)
{
  struct iniFILE *fp = iniparse_open("cases/iniparse/INI/simple.ini");
  EXPECT_NOTNULL(fp);
  EXPECT_EQ_INT(iniparse_parse(fp), 0);

  EXPECT_NOTNULL(iniparse_get(fp, "core", "repositoryFormat"));
  EXPECT_EQ_STR(iniparse_get(fp, "core", "repositoryFormat"), "0");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "fileMode"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "bare"), "false");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "global"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "ignoreCase"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "unicode"), "true");

  EXPECT_NOTNULL(iniparse_get(fp, "remote \"origin\"", "url"));
  EXPECT_EQ_STR(iniparse_get(fp, "remote \"origin\"", "url"),
                "git@github.com");
  EXPECT_EQ_STR(iniparse_get(fp, "remote \"origin\"", "fetch"),
                "refs/heads/");

  EXPECT_EQ_STR(iniparse_get(fp, "branch \"main\"", "remote"), "origin");
  EXPECT_EQ_STR(iniparse_get(fp, "branch \"main\"", "merge"),
                "refs/heads/main");
  EXPECT_EQ_STR(iniparse_get(fp, "branch \"main\"", "vscode-merge-base"),
                "origin/main");

  EXPECT_NULL(iniparse_get(fp, "core", "nonexistent"));
  EXPECT_NULL(iniparse_get(fp, "nosuchsection", "key"));

  iniparse_close(fp);
}
