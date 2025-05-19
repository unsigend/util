# Argparse: Command Line Argument Parser for C

Argparse is a lightweight, flexible command line argument parser for C, designed to make parsing command line arguments simple and expressive. It provides a rich set of options for handling different types of arguments and supports both short and long options.

Copyright (C) 2025 QIU YIXIANG

Current Version: 1.0

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [1. Include Argparse](#1-include-argparse)
  - [2. Define Options](#2-define-options)
  - [3. Initialize and Parse](#3-initialize-and-parse)
- [Core Types and Structures](#core-types-and-structures)
- [Option Types](#option-types)
- [Flags](#flags)
- [Macros](#macros)
- [Callbacks](#callbacks)
- [Example](#example)
- [License](#license)
- [Notes](#notes)

---

## Features

- **Simple and intuitive API for defining command line options**
- **Support for multiple option types (string, integer, double, boolean)**
- **Built-in help option generation**
- **Support for option groups**
- **Callback functions for custom option handling**
- **C++ compatible**

---

## Getting Started

### 1. Include Argparse

Add the following include to your source file:

```c
#include <argparse.h>
```

### 2. Define Options

Define your command line options using the provided macros:

```c
struct argparse_option options[] = {
    OPTION_GROUP("Basic Options"),
    OPTION_HELP(),
    OPTION_STRING('f', "file", "input file path", &file_path, NULL, 0),
    OPTION_INT('n', "number", "number of iterations", &iterations, NULL, 0),
    OPTION_BOOLEAN('v', "verbose", "enable verbose output", &verbose, NULL, 0),
    OPTION_GROUP_END(),
    OPTION_END()
};
```

### 3. Initialize and Parse

Initialize argparse and parse the arguments:

```c
int main(int argc, char *argv[]) {
    struct argparse argparse;
    struct argparse_description desc = {
        "My Program Description",
        "Additional information at the end of help",
        "Usage: program [options]",
        "program"
    };
    
    argparse_init(&argparse, options, &desc);
    // skip the program name
    argparse_parse(&argparse, argc - 1, argv + 1);
    return 0;
}
```

## Core Types and Structures

### Option Types

| Type | Description |
|------|-------------|
| `ARGPARSE_OPTION_TYPE_GROUP` | Defines a group of options |
| `ARGPARSE_OPTION_TYPE_GROUP_END` | Marks the end of a group |
| `ARGPARSE_OPTION_TYPE_STRING` | String option type |
| `ARGPARSE_OPTION_TYPE_INT` | Integer option type |
| `ARGPARSE_OPTION_TYPE_DOUBLE` | Double option type |
| `ARGPARSE_OPTION_TYPE_BOOL` | Boolean option type (no value) |
| `ARGPARSE_OPTION_TYPE_END` | Marks the end of option array |

### Flags

| Flag | Description |
|------|-------------|
| `ARGPARSE_FLAG_IGNORE_UNKNOWN_OPTION` | Ignore unknown options |
| `ARGPARSE_FLAG_STOP_UNKNOWN_OPTION` | Stop parsing on unknown option(default) |

## Macros

### Option Definition Macros

| Macro | Description |
|-------|-------------|
| `OPTION_END()` | Marks the end of options |
| `OPTION_GROUP(DESCRIPTION)` | Defines a group of options |
| `OPTION_GROUP_END()` | Marks the end of a group |
| `OPTION_BOOLEAN(SHORT, LONG, DESC, VALUE, CALLBACK, CALLBACK_DATA)` | Defines a boolean option |
| `OPTION_STRING(SHORT, LONG, DESC, VALUE, CALLBACK, CALLBACK_DATA)` | Defines a string option |
| `OPTION_INT(SHORT, LONG, DESC, VALUE, CALLBACK, CALLBACK_DATA)` | Defines an integer option |
| `OPTION_DOUBLE(SHORT, LONG, DESC, VALUE, CALLBACK, CALLBACK_DATA)` | Defines a double option |
| `OPTION_HELP()` | Adds a help option (-h, --help) |

## Callbacks

### Callback Function Type

The callback function type is defined as:

```c
typedef void (*argparse_callback)(struct argparse* this, const struct argparse_option *option);
```

This function type is used for custom option handling. When an option is parsed, if a callback function is specified, it will be called with:
- `this`: Pointer to the argparse instance
- `option`: Pointer to the option that triggered the callback

### Built-in Callbacks

Argparse provides two built-in callback functions:

1. `argparse_callback_help`
   - Automatically added when using `OPTION_HELP()` macro
   - Prints help message and exits the program
   - No side effects, just prints the help message
   ```c
   extern void argparse_callback_help(struct argparse* this, const struct argparse_option *option);
   ```

2. `argparse_callback_multiple_arguments`
   - Used for handling multiple arguments for an option and collect string type arguments
   - Set the `_value` pointer in the option struct to the data array
   - Set the `_callback_data` to the size of the array
   ```c
   extern void argparse_callback_multiple_arguments(struct argparse* this, const struct argparse_option *option);
   ```

### Using Callbacks

To use a callback function with an option, specify it in the option definition:

```c
void my_callback(struct argparse* this, const struct argparse_option *option) {
    printf("Option %s was parsed\n", option->_long_name);
    // Custom handling logic here
}

struct argparse_option options[] = {
    OPTION_STRING('f', "file", "input file", &file_path, my_callback, 0),
    // ... other options ...
    OPTION_END()
};
```

## Example

```c
#include <argparse.h>

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
See a more detailed [demo](https://github.com/unsigend/util/blob/main/module/argparse/test/demo.c) here.
## License

This project is licensed under the MIT License. Copyright (C) 2025 QIU YIXIANG

## Notes

- The library is designed to be simple to use while providing powerful features
- All options can have both short (-f) and long (--file) forms
- The help option (-h, --help) is automatically added when using OPTION_HELP()
- Callback functions can be used for custom option handling
- The library is compatible with both C and C++ code
- For more advanced usage, see the source and internal documentation
