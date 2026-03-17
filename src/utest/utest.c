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
#include <stdlib.h>
#include <string.h>
#include <utest/core.h>
#include <utest/flags.h>
#include <utest/print.h>
#include <utest/types.h>

#define MAX_SUITES 64  /* initial capacity of suites list */
#define SCALE_FACTOR 2 /* scale factor for suites list */
#define BUFSZ 1024

struct utest_ctx utest_ctx;

static void fatal()
{
  perror("utest");
  exit(EXIT_FAILURE);
}

void utest_init(int flags)
{
  memset(&utest_ctx, 0, sizeof(utest_ctx));

  if (!flags)
    utest_ctx.flags = UTF_DEFAULT;
  else
    utest_ctx.flags = flags;
  clock_gettime(CLOCK_MONOTONIC, &utest_ctx.tstart);
  if (pthread_mutex_init(&utest_ctx.lock, NULL))
    fatal();
  /* lazy allocate until first suite is added */
  utest_ctx.nsuitescap = MAX_SUITES;
}

void utest_fini()
{
  clock_gettime(CLOCK_MONOTONIC, &utest_ctx.tend);
  struct utest_stats stats = {
      .start = utest_ctx.tstart,
      .end = utest_ctx.tend,
      .cnpassed = utest_ctx.cnpassed,
      .cnfailed = utest_ctx.cnfailed,
      .cnskipped = utest_ctx.cnskipped,
      .snpassed = utest_ctx.snpassed,
      .snfailed = utest_ctx.snfailed,
      .snskipped = utest_ctx.snskipped,
  };

  struct utbuf buf;
  utbuf_init(&buf, BUFSZ);
  utbuf_printstats(&buf, &stats);
  utbuf_flush(&buf, stdout);
  utbuf_fini(&buf);

  if (pthread_mutex_destroy(&utest_ctx.lock))
    fatal();

  if (utest_ctx.suites) {
    for (size_t i = 0; i < utest_ctx.nsuites; i++)
      utbuf_fini(&utest_ctx.suites[i].buf);
    free(utest_ctx.suites);
  }
}

void utest_addsuite(const char *name, utest_suite_func_t func)
{
  if (utest_ctx.suites) {
    if (utest_ctx.nsuites >= utest_ctx.nsuitescap) {
      utest_ctx.nsuitescap *= SCALE_FACTOR;
      utest_ctx.suites = realloc(
          utest_ctx.suites, utest_ctx.nsuitescap * sizeof(struct utest_suite));
      if (!utest_ctx.suites)
        fatal();
    }
  } else {
    utest_ctx.suites = calloc(MAX_SUITES, sizeof(struct utest_suite));
    if (!utest_ctx.suites)
      fatal();
  }
  memset(&utest_ctx.suites[utest_ctx.nsuites], 0, sizeof(struct utest_suite));
  utest_ctx.suites[utest_ctx.nsuites].name = name;
  utest_ctx.suites[utest_ctx.nsuites].func = func;
  utbuf_init(&utest_ctx.suites[utest_ctx.nsuites].buf, BUFSZ);
  utest_ctx.nsuites++;
}

void utest_runcase(struct utest_suite *suite, const char *name,
                   utest_case_func_t func)
{
  suite->cntotal++;

  if ((utest_ctx.flags & UTF_STOPONCASE) && suite->cnfailed) {
    suite->cnskipped++;
    return;
  }
  struct utest_case cas = {
      .name = name,
      .func = func,
      .status = UT_PASS,
      .buf = &suite->buf,
  };

  if (utest_ctx.flags & UTF_SHOWCASE)
    utbuf_printb(cas.buf, UT_CASE, name);
  func(&cas);

  if (utest_ctx.flags & UTF_SHOWCASE || cas.status == UT_FAIL)
    utbuf_printe(cas.buf, UT_CASE, name, cas.status);

  if (cas.status == UT_PASS)
    suite->cnpassed++;
  else
    suite->cnfailed++;
}

static void runsuite(struct utest_suite *suite)
{
  /* TODO: Add lock for per thread access */
  if (!suite->func)
    fatal();

  if ((utest_ctx.flags & UTF_STOPONSUITE) && utest_ctx.snfailed) {
    utest_ctx.snskipped++;
    return;
  }

  if (utest_ctx.flags & UTF_SHOWSUITE)
    utbuf_printb(&suite->buf, UT_SUITE, suite->name);

  suite->func(suite);

  if (utest_ctx.flags & UTF_SHOWSUITE || suite->cnfailed)
    utbuf_printe(&suite->buf, UT_SUITE, suite->name,
                 suite->cnfailed ? UT_FAIL : UT_PASS);

  utbuf_flush(&suite->buf, stdout);

  if (suite->cnfailed)
    utest_ctx.snfailed++;
  else
    utest_ctx.snpassed++;

  /* update global stats */
  utest_ctx.cnpassed += suite->cnpassed;
  utest_ctx.cnfailed += suite->cnfailed;
  utest_ctx.cnskipped += suite->cnskipped;
}

void utest_runsuites()
{
  for (size_t i = 0; i < utest_ctx.nsuites; i++)
    runsuite(&utest_ctx.suites[i]);
}

void utest_runsuites_thread(int nthreads)
{
  (void)nthreads;
  /* TODO: implement multiple threads */
}