#include <iniparse.h>
#include <string.h>
#include <utest.h>

UTEST_CASE(simple)
{
  struct iniparse_ctx ctx;
  EXPECT_EQ_INT(iniparse_init(&ctx, "cases/iniparse/INI/simple.ini"), 0);
  EXPECT_EQ_INT(iniparse_parse(&ctx), 0);

  EXPECT_NOTNULL(iniparse_getvalue(&ctx, "core", "repositoryFormat"));
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "repositoryFormat"), "0");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "fileMode"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "bare"), "false");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "global"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "ignoreCase"), "true");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "core", "unicode"), "true");

  EXPECT_NOTNULL(iniparse_getvalue(&ctx, "remote \"origin\"", "url"));
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "remote \"origin\"", "url"),
                "git@github.com");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "remote \"origin\"", "fetch"),
                "refs/heads/");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "branch \"main\"", "remote"), "origin");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "branch \"main\"", "merge"),
                "refs/heads/main");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "branch \"main\"", "vscode-merge-base"),
                "origin/main");

  EXPECT_NULL(iniparse_getvalue(&ctx, "core", "nonexistent"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "nosuchsection", "key"));

  iniparse_fini(&ctx);
}
