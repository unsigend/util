/**
 * MIT License
 *
 * Copyright (c) 2025 QIU YIXIANG
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdarg.h>
#include <stdio.h>
#include <utest/core.h>

#define _ASCII_COLOR_RED "\033[31m"
#define _ASCII_COLOR_GREEN "\033[32m"
#define _ASCII_COLOR_YELLOW "\033[33m"
#define _ASCII_COLOR_BLUE "\033[34m"
#define _ASCII_COLOR_MAGENTA "\033[35m"
#define _ASCII_COLOR_CYAN "\033[36m"
#define _ASCII_COLOR_WHITE "\033[37m"
#define _ASCII_COLOR_RESET "\033[0m"
#define _ASCII_COLOR_BOLD "\033[1m"

UtestStateType gstate;

static UtestCaseType currcase;
static UtestSuiteType currsuite;

static void PrintUtestVersion() {
  fprintf(stdout, "Utest version: %d.%d\n", _UTEST_VERSION_MAJOR,
          _UTEST_VERSION_MINOR);
}
static void TestCasePrintResult(UtestResultType result) {
  if (gstate.flag & UTEST_FLAG_SHOW_CASE) {
    if (gstate.flag & UTEST_FLAG_SHOW_SUITE) {
      fprintf(stdout, " |- ");
    }
    if (result == UTEST_RESULT_SUCCESS) {
      fprintf(stdout, "[" _ASCII_COLOR_GREEN "PASSED " _ASCII_COLOR_RESET "]");
    } else if (result == UTEST_RESULT_FAILURE) {
      fprintf(stdout, "[" _ASCII_COLOR_RED "FAILED " _ASCII_COLOR_RESET "]");
    } else if (result == UTEST_RESULT_RUNNING) {
      fprintf(stdout, "[" _ASCII_COLOR_YELLOW "RUNNING" _ASCII_COLOR_RESET "]");
    }
    fprintf(stdout, "  TEST CASE: %s\n", currcase.name);
  }
}
static void TestSuitePrintResult(UtestResultType result) {
  if (gstate.flag & UTEST_FLAG_SHOW_SUITE) {
    if (result == UTEST_RESULT_SUCCESS) {
      fprintf(stdout, "[" _ASCII_COLOR_GREEN "PASSED " _ASCII_COLOR_RESET "]");
    } else if (result == UTEST_RESULT_FAILURE) {
      fprintf(stdout, "[" _ASCII_COLOR_RED "FAILED " _ASCII_COLOR_RESET "]");
    } else if (result == UTEST_RESULT_RUNNING) {
      fprintf(stdout, "[" _ASCII_COLOR_YELLOW "RUNNING" _ASCII_COLOR_RESET "]");
    }
    fprintf(stdout, "  TEST SUITE: %s\n", currsuite.name);
  }
}
static void PrintNextLine() {
  if ((gstate.flag & UTEST_FLAG_SHOW_SUITE) &&
      (gstate.flag & UTEST_FLAG_SHOW_CASE)) {
    fputc('\n', stdout);
  }
}
static void PrintAssertErrorPrefix() {
  fprintf(stdout, "   ");
  if (gstate.flag & UTEST_FLAG_SHOW_CASE) {
    if (gstate.flag & UTEST_FLAG_SHOW_SUITE) {
      fprintf(stdout, " |- ");
    }
  }
}

void UtestBegin() {
  memset(&gstate, 0, sizeof(gstate));
  gstate.flag = UTEST_FLAG_DEFAULT;

  // print the version
  PrintUtestVersion();
}

void UtestEnd() {
  if (gstate.flag & UTEST_FLAG_STYLE_FULL) {
    fprintf(stdout, "====================\n");
    fprintf(stdout, "TOTAL  : %llu\n", gstate.ntotal);
    fprintf(stdout, "PASSED : %llu\n", gstate.npass);
    fprintf(stdout, "FAILED : %llu\n", gstate.nfail);
    fprintf(stdout, "====================\n");
  } else {
    fprintf(stdout, "PASSED : %llu/%llu\n", gstate.npass, gstate.ntotal);
  }
}

void UtestRunTestCase(utest_func_ptr caseptr, utest_string name) {
  currcase.name = name;
  currcase.failed = false;
  caseptr();
  if (currcase.failed) {
    gstate.nfail++;
    currsuite.failed = true;
    TestCasePrintResult(UTEST_RESULT_FAILURE);
  } else {
    gstate.npass++;
    TestCasePrintResult(UTEST_RESULT_SUCCESS);
  }
  gstate.ntotal++;
}

void UtestRunTestSuite(utest_func_ptr suiteptr, utest_string name) {
  currsuite.name = name;
  currsuite.failed = false;

  TestSuitePrintResult(UTEST_RESULT_RUNNING);
  suiteptr();
  if (currsuite.failed) {
    TestSuitePrintResult(UTEST_RESULT_FAILURE);
  } else {
    TestSuitePrintResult(UTEST_RESULT_SUCCESS);
  }
  PrintNextLine();
}
void UtestAssertionError(utest_string file, utest_int line, const char *fmt,
                         ...) {
  if ((!(gstate.flag & UTEST_FLAG_STOP_ON_FAILURE)) || (!(currcase.failed))) {

    TestCasePrintResult(UTEST_RESULT_FAILURE);
    currcase.failed = true;

    PrintAssertErrorPrefix();
    fprintf(stdout, "%s:%lld failure", file, line);
    PrintNextLine();

    PrintAssertErrorPrefix();
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    PrintNextLine();
  }
}