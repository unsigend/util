#include <iniparse.h>
#include <string.h>
#include <utest.h>

UTEST_CASE(edge)
{
  struct iniFILE *fp = iniparse_open("cases/iniparse/INI/edge.ini");
  EXPECT_NOTNULL(fp);
  EXPECT_EQ_INT(iniparse_parse(fp), 0);

  EXPECT_EQ_STR(iniparse_get(fp, "space in value", "key"),
                "value with spaces inside");
  EXPECT_EQ_STR(iniparse_get(fp, "space in value", "trimmed"),
                "leading and trailing spaces");

  EXPECT_EQ_STR(iniparse_get(fp, "section", "inside"),
                "section name has spaces in brackets");
  EXPECT_EQ_STR(iniparse_get(fp, "section", "no_space"),
                "same section name without spaces in brackets");

  EXPECT_NOTNULL(iniparse_get(fp, "empty", "empty_value"));
  EXPECT_EQ_STR(iniparse_get(fp, "empty", "empty_value"), "");

  EXPECT_EQ_STR(iniparse_get(fp, "extra", "pair"), "key=value");
  EXPECT_EQ_STR(iniparse_get(fp, "extra", "with_hash"), "value#not_comment");
  EXPECT_EQ_STR(iniparse_get(fp, "extra", "semicolon"), "value;not_comment");

  EXPECT_NULL(iniparse_get(fp, "only_section", "any"));
  EXPECT_NULL(iniparse_get(fp, "last_section_no_entry", "any"));

  EXPECT_EQ_STR(iniparse_get(fp, "blank_lines", "first"), "one");
  EXPECT_EQ_STR(iniparse_get(fp, "blank_lines", "second"), "two");
  EXPECT_EQ_STR(iniparse_get(fp, "blank_lines", "third"), "three");

  EXPECT_EQ_STR(iniparse_get(fp, "comments", "real"), "value");
  EXPECT_EQ_STR(iniparse_get(fp, "comments", "another"), "here");

  EXPECT_EQ_STR(iniparse_get(fp, "tab_key", "indented"), "tab before key");

  EXPECT_EQ_STR(iniparse_get(fp, "subsection", "with_quotes"),
                "section \"has\" quotes");

  EXPECT_EQ_STR(iniparse_get(fp, "spaces_after_value", "trailing"), "value");
  EXPECT_EQ_STR(iniparse_get(fp, "spaces_after_value", "many_trailing"), "x");
  EXPECT_EQ_STR(iniparse_get(fp, "spaces_after_value", "mixed"), "value");

  EXPECT_EQ_STR(iniparse_get(fp, "spaces_around_equals", "loose"), "val");
  EXPECT_EQ_STR(iniparse_get(fp, "spaces_around_equals", "wide"), "val");
  EXPECT_EQ_STR(iniparse_get(fp, "spaces_around_equals", "tab_after_val"),
                "v");

  EXPECT_EQ_STR(iniparse_get(fp, "leading_spaces_value", "normal"), "value");
  EXPECT_EQ_STR(iniparse_get(fp, "leading_spaces_value", "spaced"), "value");

  EXPECT_NOTNULL(iniparse_get(fp, "whitespace_only_value", "key"));
  EXPECT_EQ_STR(iniparse_get(fp, "whitespace_only_value", "key"), "");
  EXPECT_NOTNULL(iniparse_get(fp, "whitespace_only_value", "key2"));
  EXPECT_EQ_STR(iniparse_get(fp, "whitespace_only_value", "key2"), "");

  EXPECT_NULL(iniparse_get(fp, "nonexistent_section", "key"));
  EXPECT_NULL(iniparse_get(fp, "section", "nonexistent_key"));

  EXPECT_NULL(iniparse_get(fp, "NoSuchSection", "key"));
  EXPECT_NULL(iniparse_get(fp, "space in value", "nonexistent_key"));
  EXPECT_NULL(iniparse_get(fp, "extra", "missing"));
  EXPECT_NULL(iniparse_get(fp, "blank_lines", "fourth"));
  EXPECT_NULL(iniparse_get(fp, "comments", "absent"));
  EXPECT_NULL(iniparse_get(fp, "tab_key", "other"));
  EXPECT_NULL(iniparse_get(fp, "subsection", "other_key"));
  EXPECT_NULL(iniparse_get(fp, "spaces_after_value", "absent"));
  EXPECT_NULL(iniparse_get(fp, "spaces_around_equals", "missing"));
  EXPECT_NULL(iniparse_get(fp, "leading_spaces_value", "other"));
  EXPECT_NULL(iniparse_get(fp, "whitespace_only_value", "key3"));

  EXPECT_NULL(iniparse_get(fp, "", "key"));
  EXPECT_NULL(iniparse_get(fp, "section", ""));
  EXPECT_NULL(iniparse_get(fp, "wrong_section", "inside"));
  EXPECT_NULL(iniparse_get(fp, "section ", "no_space"));
  EXPECT_NULL(iniparse_get(fp, " section", "inside"));

  iniparse_close(fp);
}
