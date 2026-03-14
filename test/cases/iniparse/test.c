#include "funcs/file.h"
#include "funcs/get_val.h"
#include "funcs/parse_all.h"
#include <iniparse.h>
#include <stdlib.h>
#include <string.h>
#include <utest.h>

const char *simple_filename = "cases/iniparse/INI/simple.ini";
const char *complex_filename = "cases/iniparse/INI/complex.ini";

int _index = 0;

void simple_callback(void *data, const char *section, const char *key,
                     const char *value)
{
  (void)section;
  simple_callback_data_t *data_list = (simple_callback_data_t *)data;
  data_list[_index].key = strdup(key);
  data_list[_index].value = strdup(value);
  _index++;
}

void complex_callback(void *data, const char *section, const char *key,
                     const char *value)
{
  complex_callback_data_t *data_list = (complex_callback_data_t *)data;
  if ((strcmp(section, "core") == 0) || (strcmp(section, "init") == 0) ||
      (strcmp(section, "color") == 0) ||
      (strcmp(section, "remote \"origin\"") == 0) ||
      (strcmp(section, "merge") == 0) || (strcmp(section, "credential") == 0) ||
      (strcmp(section, "url \"git@github.com:\"") == 0)) {
    data_list[_index].section = strdup(section);
    data_list[_index].key = strdup(key);
    data_list[_index].value = strdup(value);
    _index++;
  }
}

void complex_callback_everything(void *data, const char *section,
                                 const char *key, const char *value)
{
  complex_callback_data_t *data_list = (complex_callback_data_t *)data;
  data_list[_index].section = strdup(section);
  data_list[_index].key = strdup(key);
  data_list[_index].value = strdup(value);
  _index++;
}

UTEST_TEST_SUITE(iniparse)
{
  UTEST_RUN_TEST_CASE(file);
  UTEST_RUN_TEST_CASE(get_val);
  UTEST_RUN_TEST_CASE(parse_all);
}
