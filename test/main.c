#include "utest/flags.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <utest.h>

int always_true() { return 1; }
int always_false() { return 0; }
int random_int() { return rand() % 100; }

static uint64_t now_ns(void)
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

static void burn_ms(uint64_t ms)
{
  const uint64_t deadline = now_ns() + ms * 1000000ull;
  volatile uint64_t x = 0;
  while (now_ns() < deadline) {
    x = x * 1315423911u + 0x9e3779b97f4a7c15ull;
  }
  (void)x;
}

#define WORK_MS 30

UTEST_CASE(pass1) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass2) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass3) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass4) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass5) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass6) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass7) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass8) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass9) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass10) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass11) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass12) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass13) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass14) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass15) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass16) { burn_ms(WORK_MS); EXPECT_TRUE(1 == 1); }

UTEST_CASE(fail1)
{
  burn_ms(WORK_MS);
  EXPECT_TRUE(1 == 1);
}

UTEST_CASE(fail2)
{
  burn_ms(WORK_MS);
  EXPECT_TRUE(1 == 1);
}

UTEST_SUITE(passsuite)
{
  UTEST_RUNCASE(pass1);
  UTEST_RUNCASE(pass2);
  UTEST_RUNCASE(pass3);
  UTEST_RUNCASE(pass4);
  UTEST_RUNCASE(pass5);
  UTEST_RUNCASE(pass6);
  UTEST_RUNCASE(pass7);
  UTEST_RUNCASE(pass8);
  UTEST_RUNCASE(pass9);
  UTEST_RUNCASE(pass10);
  UTEST_RUNCASE(pass11);
  UTEST_RUNCASE(pass12);
  UTEST_RUNCASE(pass13);
  UTEST_RUNCASE(pass14);
  UTEST_RUNCASE(pass15);
  UTEST_RUNCASE(pass16);
}

UTEST_SUITE(failsuite)
{
  UTEST_RUNCASE(fail1);
  UTEST_RUNCASE(fail2);
}

UTEST_SUITE(suite1)
{
  UTEST_RUNCASE(pass1);
  UTEST_RUNCASE(pass2);
}
UTEST_SUITE(suite2)
{
  UTEST_RUNCASE(pass3);
  UTEST_RUNCASE(pass4);
}
UTEST_SUITE(suite3)
{
  UTEST_RUNCASE(pass5);
  UTEST_RUNCASE(pass6);
}
UTEST_SUITE(suite4)
{
  UTEST_RUNCASE(pass7);
  UTEST_RUNCASE(pass8);
}
UTEST_SUITE(suite5)
{
  UTEST_RUNCASE(pass9);
  UTEST_RUNCASE(pass10);
}
UTEST_SUITE(suite6)
{
  UTEST_RUNCASE(pass11);
  UTEST_RUNCASE(pass12);
}
UTEST_SUITE(suite7)
{
  UTEST_RUNCASE(pass13);
  UTEST_RUNCASE(pass14);
}
UTEST_SUITE(suite8)
{
  UTEST_RUNCASE(pass15);
  UTEST_RUNCASE(pass16);
}

int main(int argc, char **argv)
{
  int nthreads = 1;
  if (argc >= 2)
    nthreads = atoi(argv[1]);

  /* Parallelism is suite-level; use many suites for speedup. */
  UTEST_INIT(UTF_SHOWSUITE);

  UTEST_ADDSUITE(suite1);
  UTEST_ADDSUITE(suite2);
  UTEST_ADDSUITE(suite3);
  UTEST_ADDSUITE(suite4);
  UTEST_ADDSUITE(suite5);
  UTEST_ADDSUITE(suite6);
  UTEST_ADDSUITE(suite7);
  UTEST_ADDSUITE(suite8);
  UTEST_ADDSUITE(failsuite);
  if (nthreads <= 1)
    UTEST_RUNSUITES();
  else
    UTEST_RUNSUITES_THREAD(nthreads);

  UTEST_FINI();
  return 0;
}