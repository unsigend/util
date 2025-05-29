# Configparse: Lightweight INI Configuration Parser for C

Configparse is a lightweight, modular INI configuration parser for C, designed to make parsing and managing INI-style configuration files simple and efficient. It provides a rich set of functions for reading, parsing, and accessing configuration data from INI files.

Copyright (C) 2025 QIU YIXIANG

Current Version: 1.0

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [1. Include Configparse](#1-include-configparse)
  - [2. Initialize Parser](#2-initialize-parser)
  - [3. Parse Configuration](#3-parse-configuration)
  - [4. Access Configuration Data](#4-access-configuration-data)
  - [5. Cleanup](#5-cleanup)
- [Core API](#core-api)
  - [Data Structures](#data-structures)
  - [Initialization Functions](#initialization-functions)
  - [Parsing Functions](#parsing-functions)
  - [Callback Functions](#callback-functions)
- [Example](#example)
- [License](#license)
- [Notes](#notes)

---

## Features

- **Simple and efficient INI file parsing**
- **Support for sections and subsections**
- **Flexible callback-based parsing**
- **Memory-safe string handling**
- **Support for comments and empty lines**
- **Easy integration into any C project**

---

## Getting Started

### 1. Include Configparse

Add the following include to your source file:

```c
#include <configparse.h>
```

### 2. Initialize Parser

Initialize the parser with a configuration file:

```c
struct configparse configparse;
if (!init_configparse(&configparse, "config.ini")) {
    // Handle initialization error
}
```

### 3. Parse Configuration

Define a callback function to handle parsed data:

```c
void my_callback(void* data, const char* section, const char* key, const char* value) {
    // Process the key-value pair
}
```

Parse the configuration file:

```c
configparse_parse_all(&configparse, my_callback, user_data);
```

### 4. Access Configuration Data

Access the parsed data through your callback function or stored data structure.

### 5. Cleanup

No explicit cleanup needed as the parser doesn't allocate persistent. So the cleanup is unnecessary.

## Core API

### Initialization Functions

| Function | Description |
|----------|-------------|
| `init_configparse(struct configparse* parser, const char* filename)` | Initialize the parser with a configuration file. Returns true on success, false on failure. |

### Parsing Functions

| Function | Description |
|----------|-------------|
| `configparse_parse_all(struct configparse* parser, void (*callback)(void*, const char*, const char*, const char*), void* data)` | Parse the entire configuration file, calling the callback function for each key-value pair. |
|`char * configparse_get_value(struct configparse * this, const char * section, const char * key)`| Get specific value according to the key, not recommended for larger file.|

### Callback Functions

The callback function signature is:

```c
void callback(void* data, const char* section, const char* key, const char* value)
```

Parameters:
- `data`: User-provided data pointer
- `section`: Current section name (including subsections in quotes)
- `key`: Configuration key
- `value`: Configuration value

## Example

```c
#include <configparse.h>
#include <stdio.h>
#include <string.h>

// Callback data structure
typedef struct {
    const char* key;
    const char* value;
} callback_data_t;

// Callback function
static void config_callback(void* data, const char* section, const char* key, const char* value) {
    callback_data_t* callback_data = (callback_data_t*)data;
    printf("Section: %s, Key: %s, Value: %s\n", section, key, value);
}

int main(void) {
    struct configparse parser;
    if (!init_configparse(&parser, "config.ini")) {
        fprintf(stderr, "Failed to initialize parser\n");
        return 1;
    }

    callback_data_t data;
    configparse_parse_all(&parser, config_callback, &data);

    return 0;
}
```

Example INI file (config.ini):
```ini
[core]
    editor = vim
    excludesfile = ~/.gitignore

[remote "origin"]
    url = git@github.com:username/repo.git
    fetch = +refs/heads/*:refs/remotes/origin/*
```

## License
This project is licensed under the [MIT License](https://github.com/unsigend/util/blob/main/LICENSE).
Copyright (C) 2025 - 2026 QIU YIXIANG

## Notes

- The parser supports standard INI file format with sections, subsections, and key-value pairs
- Section names can be quoted to include spaces or special characters
- Comments start with '#' or ';' and continue to the end of the line
- Empty lines are ignored
- The parser is designed to be memory-safe and efficient
- For more advanced usage, see the source and test cases
