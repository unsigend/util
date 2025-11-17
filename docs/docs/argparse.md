---
title: Argparse
description: Command-line argument parser with flexible option handling
---

The `Argparse` module provides a lightweight, flexible command line argument parser for C, designed to make parsing command line arguments simple and expressive. It provides a rich set of options for handling different types of arguments and supports both short and long options.

## Header Files

To use the argparse module in your code, include the header file:

```c
#include <argparse.h>
```

This provides access to all parsing functions and macros for defining command-line options.

## Getting Started

To use argparse, you need to:

1. Define your command-line options using the provided macros
2. Create a description structure for your program
3. Initialize and parse the arguments

The library handles all internal structures automatically - you only need to work with the macros and functions described below.

---

## Macros

### OPTION_END

```c
OPTION_END()
```

Marks the end of the option array. Must be the last element in an option array.

**Example:**

```c
struct argparse_option options[] = {
    OPTION_STRING('f', "file", "input file", &file_path, NULL, 0),
    OPTION_END()
};
```

---

### OPTION_GROUP

```c
OPTION_GROUP(DESCRIPTION)
```

Defines a group of options for organization in help output.

**Parameters:**

- `DESCRIPTION` - The description/name of the group

**Example:**

```c
struct argparse_option options[] = {
    OPTION_GROUP("Basic Options"),
    OPTION_STRING('f', "file", "input file", &file_path, NULL, 0),
    OPTION_GROUP_END(),
    OPTION_END()
};
```

---

### OPTION_GROUP_END

```c
OPTION_GROUP_END()
```

Marks the end of an option group.

**Example:**

```c
struct argparse_option options[] = {
    OPTION_GROUP("Basic Options"),
    OPTION_STRING('f', "file", "input file", &file_path, NULL, 0),
    OPTION_GROUP_END(),
    OPTION_END()
};
```

---

### OPTION_BOOLEAN

```c
OPTION_BOOLEAN(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE, CALLBACK, CALLBACK_DATA)
```

Defines a boolean option (flag) that doesn't take a value.

**Parameters:**

- `SHORT_NAME` - Short option name (single character, use 0 for none)
- `LONG_NAME` - Long option name (string, use NULL for none)
- `DESCRIPTION` - Description shown in help message
- `VALUE` - Pointer to integer variable to store the flag state
- `CALLBACK` - Optional callback function (NULL if not needed)
- `CALLBACK_DATA` - Optional data passed to callback

**Example:**

```c
int verbose = 0;
struct argparse_option options[] = {
    OPTION_BOOLEAN('v', "verbose", "enable verbose output", &verbose, NULL, 0),
    OPTION_END()
};
```

---

### OPTION_STRING

```c
OPTION_STRING(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE, CALLBACK, CALLBACK_DATA)
```

Defines a string option that takes a string value.

**Parameters:**

- `SHORT_NAME` - Short option name (single character, use 0 for none)
- `LONG_NAME` - Long option name (string, use NULL for none)
- `DESCRIPTION` - Description shown in help message
- `VALUE` - Pointer to `const char*` variable to store the string value
- `CALLBACK` - Optional callback function (NULL if not needed)
- `CALLBACK_DATA` - Optional data passed to callback

**Example:**

```c
const char *file_path = NULL;
struct argparse_option options[] = {
    OPTION_STRING('f', "file", "input file path", &file_path, NULL, 0),
    OPTION_END()
};
```

---

### OPTION_INT

```c
OPTION_INT(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE, CALLBACK, CALLBACK_DATA)
```

Defines an integer option that takes an integer value.

**Parameters:**

- `SHORT_NAME` - Short option name (single character, use 0 for none)
- `LONG_NAME` - Long option name (string, use NULL for none)
- `DESCRIPTION` - Description shown in help message
- `VALUE` - Pointer to integer variable to store the value
- `CALLBACK` - Optional callback function (NULL if not needed)
- `CALLBACK_DATA` - Optional data passed to callback

**Example:**

```c
int iterations = 1;
struct argparse_option options[] = {
    OPTION_INT('n', "number", "number of iterations", &iterations, NULL, 0),
    OPTION_END()
};
```

---

### OPTION_DOUBLE

```c
OPTION_DOUBLE(SHORT_NAME, LONG_NAME, DESCRIPTION, VALUE, CALLBACK, CALLBACK_DATA)
```

Defines a double option that takes a floating-point value.

**Parameters:**

- `SHORT_NAME` - Short option name (single character, use 0 for none)
- `LONG_NAME` - Long option name (string, use NULL for none)
- `DESCRIPTION` - Description shown in help message
- `VALUE` - Pointer to double variable to store the value
- `CALLBACK` - Optional callback function (NULL if not needed)
- `CALLBACK_DATA` - Optional data passed to callback

**Example:**

```c
double threshold = 0.5;
struct argparse_option options[] = {
    OPTION_DOUBLE('t', "threshold", "threshold value", &threshold, NULL, 0),
    OPTION_END()
};
```

---

### OPTION_HELP

```c
OPTION_HELP()
```

Adds a built-in help option (`-h`, `--help`) that displays the help message and exits.

**Example:**

```c
struct argparse_option options[] = {
    OPTION_HELP(),
    OPTION_STRING('f', "file", "input file", &file_path, NULL, 0),
    OPTION_END()
};
```

---

## Functions

Public interfaces for argument parsing operations:

### argparse_init

```c
void argparse_init(struct argparse *this, const struct argparse_option *option_list, 
    const struct argparse_description *description);
```

Initializes an argparse instance with options and description.

**Parameters:**

- `this` - Pointer to the argparse struct to initialize
- `option_list` - Pointer to array of options (must end with `OPTION_END()`)
- `description` - Pointer to description struct (can be NULL)

**Example:**

```c
struct argparse argparse;
struct argparse_description desc = {
    "My Program Description",
    "Additional information at the end of help",
    "Usage: program [options]",
    "program"
};

struct argparse_option options[] = {
    OPTION_HELP(),
    OPTION_STRING('f', "file", "input file", &file_path, NULL, 0),
    OPTION_END()
};

argparse_init(&argparse, options, &desc);
```

---

### argparse_set_flags

```c
void argparse_set_flags(struct argparse *this, argparse_flag flags);
```

Sets the behavior flags for the argparse instance.

**Parameters:**

- `this` - Pointer to the argparse struct
- `flags` - Flags to set (can be combined with bitwise OR)

**Example:**

```c
struct argparse argparse;
argparse_init(&argparse, options, &desc);
argparse_set_flags(&argparse, ARGPARSE_FLAG_IGNORE_UNKNOWN_OPTION);
```

---

### argparse_parse

```c
void argparse_parse(struct argparse *this, int argc, char *argv[]);
```

Parses command line arguments according to the defined options.

**Parameters:**

- `this` - Pointer to the argparse struct
- `argc` - Number of command line arguments
- `argv` - Array of command line argument strings

**Note:** The `argv[0]` from the main function is typically not accepted by argparse. Usually call `argparse_parse(this, argc - 1, argv + 1)` to skip the program name.

**Example:**

```c
int main(int argc, char *argv[]) {
    struct argparse argparse;
    argparse_init(&argparse, options, &desc);
    // Skip the program name
    argparse_parse(&argparse, argc - 1, argv + 1);
    return 0;
}
```

---

## Built-in Callback Functions

### argparse_callback_help

```c
extern void argparse_callback_help(struct argparse* this, const struct argparse_option *option);
```

Built-in callback function for the help option. Automatically added when using `OPTION_HELP()` macro. Prints help message and exits the program.

**Note:** No side effects, just prints the help message.

---

### argparse_callback_multiple_arguments

```c
extern void argparse_callback_multiple_arguments(struct argparse* this, const struct argparse_option *option);
```

Built-in callback function for handling multiple arguments for an option. Used for collecting string type arguments.

**Usage:**

When defining an option that accepts multiple values, pass the callback function and the array size as the callback data.

**Example:**

```c
const char *files[10];
struct argparse_option options[] = {
    OPTION_STRING('f', "file", "input files", files, argparse_callback_multiple_arguments, 10),
    OPTION_END()
};
```

---

## Usage Examples

### Basic Usage

```c
#include <argparse.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    const char *input_file = NULL;
    int iterations = 1;
    int verbose = 0;

    struct argparse_option options[] = {
        OPTION_GROUP("Basic Options"),
        OPTION_HELP(),
        OPTION_STRING('f', "file", "input file path", &input_file, NULL, 0),
        OPTION_INT('n', "number", "number of iterations", &iterations, NULL, 0),
        OPTION_BOOLEAN('v', "verbose", "enable verbose output", &verbose, NULL, 0),
        OPTION_GROUP_END(),
        OPTION_END()
    };

    struct argparse_description desc = {
        "A sample program demonstrating argparse usage",
        "For more information, see the documentation",
        "Usage: sample [options]",
        "sample"
    };

    struct argparse argparse;
    argparse_init(&argparse, options, &desc);
    argparse_parse(&argparse, argc - 1, argv + 1);

    // Use the parsed values
    if (input_file) {
        printf("Processing file: %s\n", input_file);
    }
    printf("Iterations: %d\n", iterations);
    if (verbose) {
        printf("Verbose mode enabled\n");
    }

    return 0;
}
```

### With Custom Callback

```c
#include <argparse.h>
#include <stdio.h>

void my_callback(struct argparse* this, const struct argparse_option *option) {
    printf("Option was parsed\n");
    // Custom handling logic here
}

int main(int argc, char *argv[]) {
    const char *file_path = NULL;

    struct argparse_option options[] = {
        OPTION_STRING('f', "file", "input file", &file_path, my_callback, 0),
        OPTION_END()
    };

    struct argparse_description desc = {
        "My Program",
        NULL,
        "Usage: program [options]",
        "program"
    };

    struct argparse argparse;
    argparse_init(&argparse, options, &desc);
    argparse_parse(&argparse, argc - 1, argv + 1);

    return 0;
}
```

---

## Important Notes

### Memory Management

- The argparse library does not allocate memory for option values
- String values are stored as pointers to the original argument strings
- The user is responsible for managing the lifetime of string values

### Option Parsing

- Options can have both short (`-f`) and long (`--file`) forms
- Boolean options don't require a value
- String, integer, and double options require a value
- Unknown options will stop parsing by default (can be changed with `argparse_set_flags()`)

### Thread Safety

Argparse operations are **not thread-safe**. External synchronization is required for concurrent access.

### Important Usage Notes

- Always end your option array with `OPTION_END()`
- Don't modify option arrays or description structures after initialization
- String values point to the original `argv` strings - ensure they remain valid during use
- Check return values and handle errors appropriately

