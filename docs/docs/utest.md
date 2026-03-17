## utest – Minimal C Unit Test Framework

`utest` is a small, macro-based unit testing framework for C. It is designed to:

- **Expose only one public header**: `utest.h`
- **Run tests in parallel at suite level** with `UTEST_RUNSUITES_THREAD`
- **Be thread-safe by design**: global statistics and output are synchronized
- **Keep tests simple**: no registration boilerplate beyond a few macros

This document describes only the public API in `include/utest.h`.

---

### Including utest

Add the header and link against `libutil`:

```c
#include <utest.h>
```

---

### Test Lifecycle

- **`UTEST_INIT(flags)`**  
  Initialize the testing framework. `flags` control reporting and stop-on-failure behavior.

- **`UTEST_FINI()`**  
  Finalize the framework, print a summary, and release internal resources.

You normally call these once in `main`:

```c
int main(void)
{
  UTEST_INIT(UTF_DEFAULT);  /* or custom flags */
  /* add suites and run them */
  UTEST_FINI();
  return 0;
}
```

---

### Defining Cases and Suites

- **`UTEST_CASE(name)`**  
  Define a test case function:

```c
UTEST_CASE(example)
{
  EXPECT_TRUE(1 == 1);
}
```

- **`UTEST_SUITE(name)`**  
  Define a suite that calls `UTEST_RUNCASE` for its cases:

```c
UTEST_SUITE(math)
{
  UTEST_RUNCASE(example);
}
```

Suites are the **unit of parallelism**: each suite can be run on a different thread.

---

### Registering and Running Suites

- **`UTEST_ADDSUITE(name)`**  
  Register a suite by name (call this in `main`).

- **`UTEST_RUNSUITE(name)`**  
  Run a single suite by name. Returns `0` on success, `-1` if the suite is not found.

- **`UTEST_RUNSUITES()`**  
  Run all registered suites sequentially in a single thread.

- **`UTEST_RUNSUITES_THREAD(nthreads)`**  
  Run all registered suites using up to `nthreads` threads. Suites are dispatched dynamically, each suite still runs its own cases sequentially.

- **`UTEST_SHOWSUITES()`**  
  Print all registered suite names to stdout in a grid-aligned layout (no tests are run).

Example:

```c
int main(int argc, char **argv)
{
  int nthreads = (argc > 1) ? atoi(argv[1]) : 1;

  UTEST_INIT(0);
  UTEST_ADDSUITE(math);

  if (nthreads <= 1)
    UTEST_RUNSUITES();
  else
    UTEST_RUNSUITES_THREAD(nthreads);

  UTEST_FINI();
  return 0;
}
```

---

### Flags (`utest/flags.h`)

Flags are bitmasks combined and passed to `UTEST_INIT(flags)`.

#### Stop-on-failure behavior

- `UTF_STOPONASS`  
  On first failed assertion **within a case**, stop executing the rest of that case body.

- `UTF_STOPONCASE`  
  On first failed case **within a suite**, skip the remaining cases in that suite.

- `UTF_STOPONSUITE`  
  On first failed suite, skip the remaining suites.

You can combine these:

```c
UTEST_INIT(UTF_STOPONASS | UTF_STOPONCASE | UTF_STOPONSUITE);
```

#### Output style

- `UTF_SHOWCASE` – print per-case begin/end lines.
- `UTF_SHOWSUITE` – print per-suite begin/end lines.

Convenience presets:

- `UTF_FULLSTYLE` – `UTF_SHOWCASE | UTF_SHOWSUITE`
- `UTF_BRIEFSTYLE` – `UTF_SHOWSUITE`
- `UTF_DEFAULT` – `UTF_STOPONASS | UTF_FULLSTYLE`

---

### Assertions

All assertions are macros that operate on the current test case and record:

- pass / fail status for the case
- a detailed message on failure

Assertions are **thread-safe** when used inside `UTEST_CASE` bodies, because each case writes into a per-suite output buffer and global stats are updated under internal synchronization.

#### Booleans

- `EXPECT_TRUE(expr)`
- `EXPECT_FALSE(expr)`

#### Pointers

- `EXPECT_NULL(ptr)`
- `EXPECT_NOTNULL(ptr)`
- `EXPECT_EQ_PTR(actual, expect)`
- `EXPECT_NE_PTR(actual, expect)`
- `EXPECT_GT_PTR(actual, expect)`
- `EXPECT_GE_PTR(actual, expect)`
- `EXPECT_LT_PTR(actual, expect)`
- `EXPECT_LE_PTR(actual, expect)`

#### Integers

- `EXPECT_EQ_INT(actual, expect)`
- `EXPECT_NE_INT(actual, expect)`
- `EXPECT_GT_INT(actual, expect)`
- `EXPECT_GE_INT(actual, expect)`
- `EXPECT_LT_INT(actual, expect)`
- `EXPECT_LE_INT(actual, expect)`

#### Unsigned Integers

- `EXPECT_EQ_UINT(actual, expect)`
- `EXPECT_NE_UINT(actual, expect)`
- `EXPECT_GT_UINT(actual, expect)`
- `EXPECT_GE_UINT(actual, expect)`
- `EXPECT_LT_UINT(actual, expect)`
- `EXPECT_LE_UINT(actual, expect)`

#### Characters

- `EXPECT_EQ_CHAR(actual, expect)`
- `EXPECT_NE_CHAR(actual, expect)`
- `EXPECT_GT_CHAR(actual, expect)`
- `EXPECT_GE_CHAR(actual, expect)`
- `EXPECT_LT_CHAR(actual, expect)`
- `EXPECT_LE_CHAR(actual, expect)`

#### Unsigned Characters

- `EXPECT_EQ_UCHAR(actual, expect)`
- `EXPECT_NE_UCHAR(actual, expect)`
- `EXPECT_GT_UCHAR(actual, expect)`
- `EXPECT_GE_UCHAR(actual, expect)`
- `EXPECT_LT_UCHAR(actual, expect)`
- `EXPECT_LE_UCHAR(actual, expect)`

#### Doubles

- `EXPECT_EQ_DOUBLE(actual, expect)`
- `EXPECT_NE_DOUBLE(actual, expect)`
- `EXPECT_GT_DOUBLE(actual, expect)`
- `EXPECT_GE_DOUBLE(actual, expect)`
- `EXPECT_LT_DOUBLE(actual, expect)`
- `EXPECT_LE_DOUBLE(actual, expect)`

#### Strings (`const char *`)

- `EXPECT_EQ_STR(actual, expect)`
- `EXPECT_NE_STR(actual, expect)`
- `EXPECT_GT_STR(actual, expect)`
- `EXPECT_GE_STR(actual, expect)`
- `EXPECT_LT_STR(actual, expect)`
- `EXPECT_LE_STR(actual, expect)`

---

### Design Summary

- **Single public header**: `utest.h` is the only header you need to include.
- **Macro-based**: Cases and suites are declared via macros, compiled as normal C functions.
- **Suite-based parallelism**: Parallel execution happens at the suite level with `UTEST_RUNSUITES_THREAD`.
- **Thread-safe core**: Internal state and statistics are synchronized, suites do not share mutable state.
- **Structured output**: Each suite accumulates its own output and flushes once, minimizing interleaving even in multi-threaded runs.
