#include <iniparse.h>
#include <stdio.h>
#include <string.h>
#include <utest.h>

UTEST_CASE(modify)
{
  struct iniFILE *fp = iniparse_open("cases/iniparse/INI/simple.ini");
  EXPECT_NOTNULL(fp);
  EXPECT_EQ_INT(iniparse_parse(fp), 0);

  EXPECT_EQ_INT(iniparse_set(fp, "core", "bare", "true"), 0);
  EXPECT_EQ_STR(iniparse_get(fp, "core", "bare"), "true");

  EXPECT_EQ_INT(iniparse_set(fp, "core", "newkey", "newval"), 0);
  EXPECT_EQ_STR(iniparse_get(fp, "core", "newkey"), "newval");

  EXPECT_EQ_INT(iniparse_set(fp, "newsection", "alpha", "beta"), 0);
  EXPECT_EQ_STR(iniparse_get(fp, "newsection", "alpha"), "beta");

  EXPECT_EQ_INT(iniparse_set(fp, "core", "nullval", NULL), 0);
  EXPECT_NULL(iniparse_get(fp, "core", "nullval"));

  EXPECT_EQ_INT(iniparse_set(fp, "core", "nullval", "restored"), 0);
  EXPECT_EQ_STR(iniparse_get(fp, "core", "nullval"), "restored");

  EXPECT_EQ_INT(iniparse_unset(fp, "core", "bare"), 0);
  EXPECT_NULL(iniparse_get(fp, "core", "bare"));

  EXPECT_EQ_INT(iniparse_unset(fp, "core", "nonexistent"), -1);
  EXPECT_EQ_INT(iniparse_unset(fp, "nosuchsection", "key"), -1);

  EXPECT_EQ_INT(iniparse_set(fp, "core", "bare", "false"), 0);
  EXPECT_EQ_STR(iniparse_get(fp, "core", "bare"), "false");

  EXPECT_EQ_INT(iniparse_unset(fp, "core", "newkey"), 0);
  EXPECT_NULL(iniparse_get(fp, "core", "newkey"));
  EXPECT_EQ_INT(iniparse_unset(fp, "core", "newkey"), -1);

  iniparse_close(fp);
}

UTEST_CASE(create)
{
  EXPECT_NULL(iniparse_create(NULL));

  struct iniFILE *fp = iniparse_create("cases/iniparse/tmp_create.ini");
  EXPECT_NOTNULL(fp);

  EXPECT_EQ_INT(iniparse_parse(fp), 0);

  EXPECT_NULL(iniparse_get(fp, "core", "bare"));

  EXPECT_EQ_INT(iniparse_set(fp, "core", "bare", "false"), 0);
  EXPECT_EQ_INT(iniparse_set(fp, "core", "fileMode", "true"), 0);
  EXPECT_EQ_INT(iniparse_set(fp, "core", "repositoryFormat", "0"), 0);
  EXPECT_EQ_INT(iniparse_set(fp, "remote \"origin\"", "url", "git@github.com"),
                0);
  EXPECT_EQ_INT(iniparse_set(fp, "remote \"origin\"", "fetch", "refs/heads/*"),
                0);

  EXPECT_EQ_STR(iniparse_get(fp, "core", "bare"), "false");
  EXPECT_EQ_STR(iniparse_get(fp, "core", "fileMode"), "true");
  EXPECT_EQ_STR(iniparse_get(fp, "remote \"origin\"", "url"), "git@github.com");

  EXPECT_GT_INT(iniparse_write(fp), 0);
  iniparse_close(fp);

  struct iniFILE *fp2 = iniparse_open("cases/iniparse/tmp_create.ini");
  EXPECT_NOTNULL(fp2);
  EXPECT_EQ_INT(iniparse_parse(fp2), 0);
  EXPECT_EQ_STR(iniparse_get(fp2, "core", "bare"), "false");
  EXPECT_EQ_STR(iniparse_get(fp2, "core", "fileMode"), "true");
  EXPECT_EQ_STR(iniparse_get(fp2, "core", "repositoryFormat"), "0");
  EXPECT_EQ_STR(iniparse_get(fp2, "remote \"origin\"", "url"),
                "git@github.com");
  EXPECT_EQ_STR(iniparse_get(fp2, "remote \"origin\"", "fetch"),
                "refs/heads/*");
  EXPECT_NULL(iniparse_get(fp2, "core", "nonexistent"));
  iniparse_close(fp2);

  remove("cases/iniparse/tmp_create.ini");
}

UTEST_CASE(persist)
{
  struct iniFILE *fp = iniparse_open("cases/iniparse/INI/simple.ini");
  EXPECT_NOTNULL(fp);
  EXPECT_EQ_INT(iniparse_parse(fp), 0);

  EXPECT_EQ_INT(iniparse_set(fp, "core", "bare", "true"), 0);
  EXPECT_EQ_INT(iniparse_set(fp, "core", "added", "yes"), 0);
  EXPECT_EQ_INT(iniparse_unset(fp, "core", "fileMode"), 0);
  EXPECT_EQ_INT(iniparse_set(fp, "new", "key", "val"), 0);

  EXPECT_GT_INT(iniparse_writeto(fp, "cases/iniparse/tmp_persist.ini"), 0);
  iniparse_close(fp);

  struct iniFILE *fp2 = iniparse_open("cases/iniparse/tmp_persist.ini");
  EXPECT_NOTNULL(fp2);
  EXPECT_EQ_INT(iniparse_parse(fp2), 0);

  EXPECT_EQ_STR(iniparse_get(fp2, "core", "bare"), "true");
  EXPECT_EQ_STR(iniparse_get(fp2, "core", "added"), "yes");
  EXPECT_NULL(iniparse_get(fp2, "core", "fileMode"));
  EXPECT_EQ_STR(iniparse_get(fp2, "new", "key"), "val");
  EXPECT_EQ_STR(iniparse_get(fp2, "core", "repositoryFormat"), "0");
  EXPECT_EQ_STR(iniparse_get(fp2, "remote \"origin\"", "url"),
                "git@github.com");
  iniparse_close(fp2);

  remove("cases/iniparse/tmp_persist.ini");
}

UTEST_CASE(dump)
{
  struct iniFILE *fp = iniparse_open("cases/iniparse/INI/simple.ini");
  EXPECT_NOTNULL(fp);
  EXPECT_EQ_INT(iniparse_parse(fp), 0);

  FILE *f = fopen("cases/iniparse/tmp_dump.ini", "w");
  EXPECT_NOTNULL(f);
  EXPECT_GT_INT(iniparse_fprint(fp, f), 0);
  fclose(f);
  remove("cases/iniparse/tmp_dump.ini");

  char buf[4096];
  int n = iniparse_snprint(fp, buf, sizeof(buf));
  EXPECT_GT_INT(n, 0);
  EXPECT_NOTNULL(strstr(buf, "core.repositoryFormat=0"));
  EXPECT_NOTNULL(strstr(buf, "core.bare=false"));
  EXPECT_NOTNULL(strstr(buf, "remote \"origin\".url=git@github.com"));

  char small[8];
  int n2 = iniparse_snprint(fp, small, sizeof(small));
  EXPECT_GT_INT(n2, 0);
  EXPECT_GT_INT(n2, (int)sizeof(small));

  char spbuf[4096];
  int n3 = iniparse_sprint(fp, spbuf);
  EXPECT_GT_INT(n3, 0);
  EXPECT_EQ_INT(n3, n);

  iniparse_close(fp);
}
