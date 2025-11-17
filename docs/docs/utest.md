---
title: Utest
description: Lightweight unit testing framework for C
---

The `Utest` module provides a lightweight, modular unit testing framework for C, designed to make writing and running tests simple and expressive. It provides a rich set of macros for defining test cases, test suites, and a variety of assertions for different data types.

## Header Files

To use the utest module in your code, include the header file:

```c
#include <utest.h>
```

This provides access to all test declaration macros, assertion macros, and framework control macros.

---

## Macros

### Test Declaration and Execution

#### UTEST_TEST_CASE

```c
UTEST_TEST_CASE(TEST_CASE_NAME)
```

Declares a test case with the given name.

**Parameters:**

- `TEST_CASE_NAME` - The name of the test case

**Example:**

```c
UTEST_TEST_CASE(MyFirstTest) {
    EXPECT_EQUAL_INT(1 + 1, 2);
    EXPECT_TRUE(5 > 3);
}
```

---

#### UTEST_RUN_TEST_CASE

```c
UTEST_RUN_TEST_CASE(TEST_CASE_NAME)
```

Runs a test case. This macro should be called inside a test suite.

**Parameters:**

- `TEST_CASE_NAME` - The name of the test case to run

**Example:**

```c
UTEST_TEST_SUITE(MySuite) {
    UTEST_RUN_TEST_CASE(MyFirstTest);
    UTEST_RUN_TEST_CASE(MySecondTest);
}
```

---

#### UTEST_TEST_SUITE

```c
UTEST_TEST_SUITE(TEST_SUITE_NAME)
```

Declares a test suite with the given name.

**Parameters:**

- `TEST_SUITE_NAME` - The name of the test suite

**Example:**

```c
UTEST_TEST_SUITE(MySuite) {
    UTEST_RUN_TEST_CASE(MyFirstTest);
    UTEST_RUN_TEST_CASE(MySecondTest);
}
```

---

#### UTEST_RUN_TEST_SUITE

```c
UTEST_RUN_TEST_SUITE(TEST_SUITE_NAME)
```

Runs a test suite. This macro should be called in the main function.

**Parameters:**

- `TEST_SUITE_NAME` - The name of the test suite to run

**Example:**

```c
int main(void) {
    UTEST_BEGIN();
    UTEST_RUN_TEST_SUITE(MySuite);
    UTEST_END();
    return 0;
}
```

---

#### UTEST_BEGIN

```c
UTEST_BEGIN()
```

Initializes the Utest framework. Must be called before running any test suites.

**Example:**

```c
int main(void) {
    UTEST_BEGIN();
    UTEST_RUN_TEST_SUITE(MySuite);
    UTEST_END();
    return 0;
}
```

---

#### UTEST_END

```c
UTEST_END()
```

Finalizes the Utest framework. Must be called after running all test suites.

**Example:**

```c
int main(void) {
    UTEST_BEGIN();
    UTEST_RUN_TEST_SUITE(MySuite);
    UTEST_END();
    return 0;
}
```

---

### Flag Management

#### UTEST_SET_FLAG

```c
UTEST_SET_FLAG(UTEST_FLAG)
```

Sets a flag (bitwise) for the utest library.

**Parameters:**

- `UTEST_FLAG` - The flag to set

**Example:**

```c
UTEST_SET_FLAG(UTEST_FLAG_SHOW_CASE);
```

---

#### UTEST_CLEAR_FLAG

```c
UTEST_CLEAR_FLAG(UTEST_FLAG)
```

Clears a flag (bitwise) for the utest library.

**Parameters:**

- `UTEST_FLAG` - The flag to clear

**Example:**

```c
UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);
```

---

#### UTEST_FLAG_RESET

```c
UTEST_FLAG_RESET()
```

Resets all flags to the default value.

**Example:**

```c
UTEST_FLAG_RESET();
```

---

### Flags

Utest supports runtime flags to control output and behavior:

| Flag | Description |
|------|-------------|
| `UTEST_FLAG_NONE` | No special behavior |
| `UTEST_FLAG_SHOW_CASE` | Show each test case result |
| `UTEST_FLAG_SHOW_SUITE` | Show each test suite result |
| `UTEST_FLAG_STYLE_FULL` | Use full output style |
| `UTEST_FLAG_STOP_ON_FAILURE` | Stop on first failure |
| `UTEST_FLAG_DEFAULT` | Default flag set |

---

### Integer Assertions

#### Equality Assertions

- `EXPECT_EQUAL_INT(ACTUAL, EXPECTED)` - Expects two integers to be equal
- `EXPECT_EQUAL_INT8(ACTUAL, EXPECTED)` - Expects two 8-bit integers to be equal
- `EXPECT_EQUAL_INT16(ACTUAL, EXPECTED)` - Expects two 16-bit integers to be equal
- `EXPECT_EQUAL_INT32(ACTUAL, EXPECTED)` - Expects two 32-bit integers to be equal
- `EXPECT_EQUAL_INT64(ACTUAL, EXPECTED)` - Expects two 64-bit integers to be equal

**Example:**

```c
UTEST_TEST_CASE(TestAddition) {
    EXPECT_EQUAL_INT(2 + 2, 4);
    EXPECT_EQUAL_INT32(100, 100);
}
```

#### Inequality Assertions

- `EXPECT_NOT_EQUAL_INT(ACTUAL, EXPECTED)` - Expects two integers to be not equal
- `EXPECT_NOT_EQUAL_INT8(ACTUAL, EXPECTED)` - Expects two 8-bit integers to be not equal
- `EXPECT_NOT_EQUAL_INT16(ACTUAL, EXPECTED)` - Expects two 16-bit integers to be not equal
- `EXPECT_NOT_EQUAL_INT32(ACTUAL, EXPECTED)` - Expects two 32-bit integers to be not equal
- `EXPECT_NOT_EQUAL_INT64(ACTUAL, EXPECTED)` - Expects two 64-bit integers to be not equal

**Example:**

```c
UTEST_TEST_CASE(TestInequality) {
    EXPECT_NOT_EQUAL_INT(1, 2);
}
```

#### Greater Than Assertions

- `EXPECT_GREATER_INT(ACTUAL, EXPECTED)` - Expects actual to be greater than expected
- `EXPECT_GREATER_INT8(ACTUAL, EXPECTED)` - Expects actual to be greater than expected (8-bit)
- `EXPECT_GREATER_INT16(ACTUAL, EXPECTED)` - Expects actual to be greater than expected (16-bit)
- `EXPECT_GREATER_INT32(ACTUAL, EXPECTED)` - Expects actual to be greater than expected (32-bit)
- `EXPECT_GREATER_INT64(ACTUAL, EXPECTED)` - Expects actual to be greater than expected (64-bit)

**Example:**

```c
UTEST_TEST_CASE(TestGreater) {
    EXPECT_GREATER_INT(5, 3);
}
```

#### Greater Than or Equal Assertions

- `EXPECT_GREATER_EQUAL_INT(ACTUAL, EXPECTED)` - Expects actual to be greater than or equal to expected
- `EXPECT_GREATER_EQUAL_INT8(ACTUAL, EXPECTED)` - Expects actual to be greater than or equal to expected (8-bit)
- `EXPECT_GREATER_EQUAL_INT16(ACTUAL, EXPECTED)` - Expects actual to be greater than or equal to expected (16-bit)
- `EXPECT_GREATER_EQUAL_INT32(ACTUAL, EXPECTED)` - Expects actual to be greater than or equal to expected (32-bit)
- `EXPECT_GREATER_EQUAL_INT64(ACTUAL, EXPECTED)` - Expects actual to be greater than or equal to expected (64-bit)

**Example:**

```c
UTEST_TEST_CASE(TestGreaterEqual) {
    EXPECT_GREATER_EQUAL_INT(5, 5);
    EXPECT_GREATER_EQUAL_INT(6, 5);
}
```

#### Less Than Assertions

- `EXPECT_LESS_INT(ACTUAL, EXPECTED)` - Expects actual to be less than expected
- `EXPECT_LESS_INT8(ACTUAL, EXPECTED)` - Expects actual to be less than expected (8-bit)
- `EXPECT_LESS_INT16(ACTUAL, EXPECTED)` - Expects actual to be less than expected (16-bit)
- `EXPECT_LESS_INT32(ACTUAL, EXPECTED)` - Expects actual to be less than expected (32-bit)
- `EXPECT_LESS_INT64(ACTUAL, EXPECTED)` - Expects actual to be less than expected (64-bit)

**Example:**

```c
UTEST_TEST_CASE(TestLess) {
    EXPECT_LESS_INT(3, 5);
}
```

#### Less Than or Equal Assertions

- `EXPECT_LESS_EQUAL_INT(ACTUAL, EXPECTED)` - Expects actual to be less than or equal to expected
- `EXPECT_LESS_EQUAL_INT8(ACTUAL, EXPECTED)` - Expects actual to be less than or equal to expected (8-bit)
- `EXPECT_LESS_EQUAL_INT16(ACTUAL, EXPECTED)` - Expects actual to be less than or equal to expected (16-bit)
- `EXPECT_LESS_EQUAL_INT32(ACTUAL, EXPECTED)` - Expects actual to be less than or equal to expected (32-bit)
- `EXPECT_LESS_EQUAL_INT64(ACTUAL, EXPECTED)` - Expects actual to be less than or equal to expected (64-bit)

**Example:**

```c
UTEST_TEST_CASE(TestLessEqual) {
    EXPECT_LESS_EQUAL_INT(5, 5);
    EXPECT_LESS_EQUAL_INT(3, 5);
}
```

---

### Unsigned Integer Assertions

All integer assertion macros have unsigned variants with `UINT` in the macro name:

#### Equality Assertions

- `EXPECT_EQUAL_UINT(ACTUAL, EXPECTED)` - Expects two unsigned integers to be equal
- `EXPECT_EQUAL_UINT8(ACTUAL, EXPECTED)` - Expects two 8-bit unsigned integers to be equal
- `EXPECT_EQUAL_UINT16(ACTUAL, EXPECTED)` - Expects two 16-bit unsigned integers to be equal
- `EXPECT_EQUAL_UINT32(ACTUAL, EXPECTED)` - Expects two 32-bit unsigned integers to be equal
- `EXPECT_EQUAL_UINT64(ACTUAL, EXPECTED)` - Expects two 64-bit unsigned integers to be equal

#### Other Unsigned Integer Assertions

- `EXPECT_NOT_EQUAL_UINT(ACTUAL, EXPECTED)` and variants
- `EXPECT_GREATER_UINT(ACTUAL, EXPECTED)` and variants
- `EXPECT_GREATER_EQUAL_UINT(ACTUAL, EXPECTED)` and variants
- `EXPECT_LESS_UINT(ACTUAL, EXPECTED)` and variants
- `EXPECT_LESS_EQUAL_UINT(ACTUAL, EXPECTED)` and variants

**Example:**

```c
UTEST_TEST_CASE(TestUnsigned) {
    EXPECT_EQUAL_UINT(10u, 10u);
    EXPECT_GREATER_UINT(20u, 10u);
}
```

---

### Floating Point Assertions

#### Float Assertions

- `EXPECT_EQUAL_FLOAT(ACTUAL, EXPECTED)` - Expects two floats to be equal
- `EXPECT_NOT_EQUAL_FLOAT(ACTUAL, EXPECTED)` - Expects two floats to be not equal
- `EXPECT_GREATER_FLOAT(ACTUAL, EXPECTED)` - Expects actual float to be greater than expected
- `EXPECT_GREATER_EQUAL_FLOAT(ACTUAL, EXPECTED)` - Expects actual float to be greater than or equal to expected
- `EXPECT_LESS_FLOAT(ACTUAL, EXPECTED)` - Expects actual float to be less than expected
- `EXPECT_LESS_EQUAL_FLOAT(ACTUAL, EXPECTED)` - Expects actual float to be less than or equal to expected

**Example:**

```c
UTEST_TEST_CASE(TestFloat) {
    EXPECT_EQUAL_FLOAT(3.14f, 3.14f);
    EXPECT_GREATER_FLOAT(5.0f, 3.0f);
}
```

---

### Double Assertions

- `EXPECT_EQUAL_DOUBLE(ACTUAL, EXPECTED)` - Expects two doubles to be equal
- `EXPECT_NOT_EQUAL_DOUBLE(ACTUAL, EXPECTED)` - Expects two doubles to be not equal
- `EXPECT_GREATER_DOUBLE(ACTUAL, EXPECTED)` - Expects actual double to be greater than expected
- `EXPECT_GREATER_EQUAL_DOUBLE(ACTUAL, EXPECTED)` - Expects actual double to be greater than or equal to expected
- `EXPECT_LESS_DOUBLE(ACTUAL, EXPECTED)` - Expects actual double to be less than expected
- `EXPECT_LESS_EQUAL_DOUBLE(ACTUAL, EXPECTED)` - Expects actual double to be less than or equal to expected

**Example:**

```c
UTEST_TEST_CASE(TestDouble) {
    EXPECT_EQUAL_DOUBLE(3.14159, 3.14159);
    EXPECT_LESS_DOUBLE(2.5, 3.0);
}
```

---

### String Assertions

- `EXPECT_EQUAL_STRING(ACTUAL, EXPECTED)` - Expects two strings to be equal
- `EXPECT_NOT_EQUAL_STRING(ACTUAL, EXPECTED)` - Expects two strings to be not equal
- `EXPECT_GREATER_STRING(ACTUAL, EXPECTED)` - Expects actual string to be greater than expected (lexicographically)
- `EXPECT_GREATER_EQUAL_STRING(ACTUAL, EXPECTED)` - Expects actual string to be greater than or equal to expected
- `EXPECT_LESS_STRING(ACTUAL, EXPECTED)` - Expects actual string to be less than expected (lexicographically)
- `EXPECT_LESS_EQUAL_STRING(ACTUAL, EXPECTED)` - Expects actual string to be less than or equal to expected

**Example:**

```c
UTEST_TEST_CASE(TestString) {
    EXPECT_EQUAL_STRING("hello", "hello");
    EXPECT_NOT_EQUAL_STRING("hello", "world");
    EXPECT_LESS_STRING("apple", "banana");
}
```

---

### Pointer Assertions

- `EXPECT_NULL(POINTER)` - Expects pointer to be NULL
- `EXPECT_NOT_NULL(POINTER)` - Expects pointer to be not NULL

**Example:**

```c
UTEST_TEST_CASE(TestPointer) {
    void *ptr = NULL;
    EXPECT_NULL(ptr);
    
    int value = 42;
    void *ptr2 = &value;
    EXPECT_NOT_NULL(ptr2);
}
```

---

### Boolean Assertions

- `EXPECT_TRUE(EXPRESSION)` - Expects expression to be true (non-zero)
- `EXPECT_FALSE(EXPRESSION)` - Expects expression to be false (zero)

**Example:**

```c
UTEST_TEST_CASE(TestBoolean) {
    EXPECT_TRUE(5 > 3);
    EXPECT_FALSE(3 > 5);
    EXPECT_TRUE(1);
    EXPECT_FALSE(0);
}
```

---

## Usage Examples

### Basic Usage

```c
#include <utest.h>

UTEST_TEST_CASE(Addition) {
    EXPECT_EQUAL_INT(2 + 2, 4);
}

UTEST_TEST_CASE(Subtraction) {
    EXPECT_EQUAL_INT(5 - 3, 2);
}

UTEST_TEST_SUITE(MathTests) {
    UTEST_RUN_TEST_CASE(Addition);
    UTEST_RUN_TEST_CASE(Subtraction);
}

int main(void) {
    UTEST_BEGIN();
    UTEST_RUN_TEST_SUITE(MathTests);
    UTEST_END();
    return 0;
}
```

### With Flags

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
    UTEST_SET_FLAG(UTEST_FLAG_SHOW_CASE);
    UTEST_RUN_TEST_SUITE(MathTests);
    UTEST_END();
    return 0;
}
```

### Multiple Test Suites

```c
#include <utest.h>

UTEST_TEST_CASE(Test1) {
    EXPECT_EQUAL_INT(1, 1);
}

UTEST_TEST_CASE(Test2) {
    EXPECT_EQUAL_STRING("hello", "hello");
}

UTEST_TEST_SUITE(Suite1) {
    UTEST_RUN_TEST_CASE(Test1);
}

UTEST_TEST_SUITE(Suite2) {
    UTEST_RUN_TEST_CASE(Test2);
}

int main(void) {
    UTEST_BEGIN();
    UTEST_RUN_TEST_SUITE(Suite1);
    UTEST_RUN_TEST_SUITE(Suite2);
    UTEST_END();
    return 0;
}
```

### Comprehensive Example

```c
#include <utest.h>
#include <string.h>
#include <stdlib.h>

UTEST_TEST_CASE(TestIntegers) {
    EXPECT_EQUAL_INT(10, 10);
    EXPECT_NOT_EQUAL_INT(10, 20);
    EXPECT_GREATER_INT(20, 10);
    EXPECT_LESS_INT(10, 20);
}

UTEST_TEST_CASE(TestStrings) {
    EXPECT_EQUAL_STRING("test", "test");
    EXPECT_NOT_EQUAL_STRING("test", "fail");
}

UTEST_TEST_CASE(TestPointers) {
    int value = 42;
    int *ptr = &value;
    EXPECT_NOT_NULL(ptr);
    EXPECT_NULL(NULL);
}

UTEST_TEST_CASE(TestBooleans) {
    EXPECT_TRUE(1);
    EXPECT_FALSE(0);
    EXPECT_TRUE(5 > 3);
}

UTEST_TEST_SUITE(AllTests) {
    UTEST_RUN_TEST_CASE(TestIntegers);
    UTEST_RUN_TEST_CASE(TestStrings);
    UTEST_RUN_TEST_CASE(TestPointers);
    UTEST_RUN_TEST_CASE(TestBooleans);
}

int main(void) {
    UTEST_BEGIN();
    UTEST_RUN_TEST_SUITE(AllTests);
    UTEST_END();
    return 0;
}
```

---

## Important Notes

### Test Organization

- Test cases must be declared before they are used in test suites
- Test suites can contain multiple test cases
- Multiple test suites can be run in a single program
- Always call `UTEST_BEGIN()` before running tests and `UTEST_END()` after

### Assertion Behavior

- Assertions do not stop execution on failure by default
- Use `UTEST_FLAG_STOP_ON_FAILURE` flag to stop on first failure
- Failed assertions are reported in the test output
- All assertions in a test case are evaluated unless stopped by flags

### Thread Safety

Utest operations are **not thread-safe**. External synchronization is required for concurrent test execution.

### Undefined Behavior

Avoid the following:

- Calling test macros outside of proper test case/suite contexts
- Not calling `UTEST_BEGIN()` before running tests
- Not calling `UTEST_END()` after running tests
- Using test case names that conflict with C keywords or other identifiers

