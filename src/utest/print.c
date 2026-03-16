/**
 * MIT License
 *
 * Copyright (c) 2026 YIXIANG QIU
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

#include <stdio.h>
#include <utest/flags.h>
#include <utest/print.h>

#define COLYELLOW "\033[33m"
#define COLBLUE "\033[34m"
#define COLGREEN "\033[32m"
#define COLRED "\033[31m"
#define COLRESET "\033[0m"
#define COLMAGENTA "\033[35m"
#define COLCYAN "\033[36m"

static double elapsedms(struct timespec *start, struct timespec *end)
{
  /* calculate elapsed time in milliseconds */
  return (end->tv_sec - start->tv_sec) * 1000.0 +
         (end->tv_nsec - start->tv_nsec) / 1000000.0;
}

void utprintb(int type, const char *name)
{
  if (type == UT_CASE)
    fprintf(stdout, " |- ");
  fprintf(stdout, "[" COLCYAN "RUNNING" COLRESET "] TEST %s: %s\n",
          type == UT_CASE ? "CASE" : "SUITE", name);
}

void utprinte(int type, const char *name, int stat)
{
  if (type == UT_CASE)
    fprintf(stdout, " |- ");
  fprintf(stdout, "[%s%s%s ] TEST %s: %s\n",
          stat == UT_PASS ? COLGREEN : COLRED,
          stat == UT_PASS ? "PASSED" : "FAILED", COLRESET,
          type == UT_CASE ? "CASE" : "SUITE", name);
}

void utprintstats(struct utest_stats *stats)
{
  size_t cntotal = stats->cnpassed + stats->cnfailed + stats->cnskipped;
  size_t sntotal = stats->snpassed + stats->snfailed + stats->snskipped;
  double elapsed = elapsedms(&stats->start, &stats->end);
  putc('\n', stdout);
  fprintf(stdout,
          "TEST CASE   skipped: %zu/%zu, failed: %zu/%zu, passed: %zu/%zu\n",
          stats->cnskipped, cntotal, stats->cnfailed, cntotal, stats->cnpassed,
          cntotal);
  fprintf(stdout,
          "TEST SUITE  skipped: %zu/%zu, failed: %zu/%zu, passed: %zu/%zu\n",
          stats->snskipped, sntotal, stats->snfailed, sntotal, stats->snpassed,
          sntotal);
  if (elapsed > 1000.0)
    fprintf(stdout, "time:  %.2f s\n", elapsed / 1000.0);
  else
    fprintf(stdout, "time:  %.2f ms\n", elapsed);
}