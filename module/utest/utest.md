# Utest: Lightweight Unit Testing Framework for C

Utest is a lightweight, modular unit testing framework for C, designed to make writing and running tests simple and expressive. It provides a rich set of macros for defining test cases, test suites, and a variety of assertions for different data types.

Copyright (C) 2025 QIU YIXIANG

Current Version: 1.0

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [1. Include Utest](#1-include-utest)
  - [2. Writing Test Cases](#2-writing-test-cases)
  - [3. Grouping Test Cases into Suites](#3-grouping-test-cases-into-suites)
  - [4. Running Test Suites](#4-running-test-suites)
- [Core Macros](#core-macros)
- [Flags and Configuration](#flags-and-configuration)
- [Example](#example)
- [License](#license)
- [Notes](#notes)
---

## Features

- **Simple test case and suite declaration macros**
- **Flexible assertion macros for integers, floats, doubles, strings, pointers, and booleans**
- **Configurable runtime flags for output style and behavior**
- **Easy integration into any C project**

---

## Getting Started

### 1. Include Utest

Add the following include to your test source file:

```c
#include <utest.h>
```

### 2. Writing Test Cases
Declare a test case using `UTEST_TEST_CASE`:

```c
UTEST_TEST_CASE(MyFirstTest) {
    EXPECT_EQUAL_INT(1 + 1, 2);
    EXPECT_TRUE(5 > 3);
}
```

### 3. Grouping Test Cases into Suites
Declare a test suite and add test cases to it:
```c
UTEST_TEST_SUITE(MySuite) {
    UTEST_RUN_TEST_CASE(MyFirstTest);
    // Add more test cases here
}
```

### 4. Running Test Suites
In your `main` function, initialize Utest, run your suites, and finalize:
```c
int main(void) {
    UTEST_BEGIN();
    UTEST_RUN_TEST_SUITE(MySuite);
    UTEST_END();
    return 0;
}
```

## Core Macros

Test Declaration and Execution

**Assertion Macros**

| Macro                        | Description                          |
| ---------------------------- | ------------------------------------ |
| `UTEST_TEST_CASE(name)`      | Declare a test case                  |
| `UTEST_RUN_TEST_CASE(name)`  | Run a test case (inside a suite)     |
| `UTEST_TEST_SUITE(name)`     | Declare a test suite                 |
| `UTEST_RUN_TEST_SUITE(name)` | Run a test suite (usually in `main`) |
| `UTEST_BEGIN()`              | Initialize the Utest framework       |
| `UTEST_END()`                | Finalize the Utest framework         |



**Integer Assertions**

- Equality
    - `EXPECT_EQUAL_INT(actual, expected)`
    - `EXPECT_EQUAL_INT8(actual, expected)`
    - `EXPECT_EQUAL_INT16(actual, expected)`
    - `EXPECT_EQUAL_INT32(actual, expected)`
    - `EXPECT_EQUAL_INT64(actual, expected)`
    
- Inequality
    - `EXPECT_NOT_EQUAL_INT(actual, expected)`
    - ... (same variants as above)
    
- Greater/Less Than
    - `EXPECT_GREATER_INT(actual, expected)`
    - `EXPECT_LESS_INT(actual, expected)`
    - ... (same variants as above)
    
- Greater/Less or Equal
    - `EXPECT_GREATER_EQUAL_INT(actual, expected)`
    
    - `EXPECT_LESS_EQUAL_INT(actual, expected)`

    - ... (same variants as above)
    
      

**Unsigned Integer Assertions**

- Same as above, but with `UINT` in macro names.

  

**Floating Point Assertions**

- `EXPECT_EQUAL_FLOAT(actual, expected)`

- `EXPECT_NOT_EQUAL_FLOAT(actual, expected)`

- `EXPECT_GREATER_FLOAT(actual, expected)`

- `EXPECT_GREATER_EQUAL_FLOAT(actual, expected)`

- `EXPECT_LESS_FLOAT(actual, expected)`

- `EXPECT_LESS_EQUAL_FLOAT(actual, expected)`

  

**Double Assertions**
- Same as float, but with `DOUBLE` in macro names.

  

**String Assertions**

- `EXPECT_EQUAL_STRING(actual, expected)`

- `EXPECT_NOT_EQUAL_STRING(actual, expected)`

- `EXPECT_GREATER_STRING(actual, expected)`

- `EXPECT_GREATER_EQUAL_STRING(actual, expected)`

- `EXPECT_LESS_STRING(actual, expected)`

- `EXPECT_LESS_EQUAL_STRING(actual, expected)`

  

**Pointer Assertions**
- `EXPECT_NULL(pointer)`

- `EXPECT_NOT_NULL(pointer)`

  

**Boolean Assertions**
- `EXPECT_TRUE(expression)`

- `EXPECT_FALSE(expression)`

  

## Flags and Configuration
Utest supports runtime flags to control output and behavior:

| Flag                         | Description                 |
| ---------------------------- | --------------------------- |
| `UTEST_FLAG_NONE`            | No special behavior         |
| `UTEST_FLAG_SHOW_CASE`       | Show each test case result  |
| `UTEST_FLAG_SHOW_SUITE`      | Show each test suite result |
| `UTEST_FLAG_STYLE_FULL`      | Use full output style       |
| `UTEST_FLAG_STOP_ON_FAILURE` | Stop on first failure       |
| `UTEST_FLAG_DEFAULT`         | Default flag set            |

You can change the flag any time you want using `UTEST_CLEAR_FLAG` or `UTEST_SET_FLAG` macros:

```c
UTEST_SET_FLAG(UTEST_FLAG);
UTEST_CLEAR_FLAG(UTEST_FLAG);
UTEST_FLAG_RESET(); // Reset to default
```

## Example
```c
#include <utest.h>

UTEST_TEST_CASE(Addition) {
    EXPECT_EQUAL_INT(2 + 2, 4);
}

UTEST_TEST_SUITE(MathTests) {
    UTEST_RUN_TEST_CASE(Addition);
}

int main(void) {
    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);
    UTEST_RUN_TEST_SUITE(MathTests);
    UTEST_END();
    return 0;
}
```

## License
This project is licensed under the [MIT License](https://github.com/unsigend/util/blob/main/LICENSE). 
Copyright (C) 2025 - 2026 QIU YIXIANG

## Notes
- All macros expand to internal implementations prefixed with `_UTEST_` or `_EXPECT_`.
- Utest is designed to be header-only and easy to integrate.
- For more advanced usage, see the source and internal documentation.