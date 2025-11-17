---
title: Configparse
description: Lightweight INI configuration parser for C
---

The `Configparse` module provides a lightweight, modular INI configuration parser for C, designed to make parsing and managing INI-style configuration files simple and efficient. It provides a rich set of functions for reading, parsing, and accessing configuration data from INI files.

## Header Files

To use the configparse module in your code, include the header file:

```c
#include <configparse.h>
```

This provides access to all parsing functions for reading INI configuration files.

## Getting Started

To use configparse, you need to:

1. Initialize a parser with a configuration file
2. Parse the file using either a callback function or get specific values
3. The library handles all internal file management automatically

## Callback Function Type

### configparse_callback_t

Callback function type for handling parsed key-value pairs:

```c
typedef void (*configparse_callback_t)(void * data, const char * section, const char * key, const char * value);
```

This function is called for each key-value pair found during parsing.

**Parameters:**

- `data` - User-provided data pointer
- `section` - Current section name (including subsections in quotes)
- `key` - Configuration key
- `value` - Configuration value

---

## Functions

Public interfaces for configuration parsing operations:

### init_configparse

```c
bool init_configparse(struct configparse * this, const char * filename);
```

Initializes a configparse instance with a configuration file.

**Parameters:**

- `this` - Pointer to the configparse object to initialize
- `filename` - The filename of the INI file to parse

**Return Value:**

Returns `true` if successful, `false` otherwise (e.g., file not found or cannot be opened).

**Example:**

```c
struct configparse parser;
if (!init_configparse(&parser, "config.ini")) {
    fprintf(stderr, "Failed to initialize parser\n");
    return 1;
}
```

---

### configparse_get_value

```c
char * configparse_get_value(struct configparse * this, const char * section, const char * key);
```

Gets the value of a specific key in a section.

**Parameters:**

- `this` - Pointer to the configparse object
- `section` - The section name where the key is located
- `key` - The key name

**Return Value:**

Returns a pointer to the value string, or `NULL` if the key is not found.

**Note:** Low performance, only recommended for reading specific keys in small files. When reading multiple keys, use `configparse_parse_all()` function instead.

**Example:**

```c
struct configparse parser;
init_configparse(&parser, "config.ini");

char *value = configparse_get_value(&parser, "core", "editor");
if (value != NULL) {
    printf("Editor: %s\n", value);
}
```

---

### configparse_parse_all

```c
void configparse_parse_all(struct configparse * this, configparse_callback_t callback, void * data);
```

Parses the entire configuration file, calling the callback function for each key-value pair.

**Parameters:**

- `this` - Pointer to the configparse object
- `callback` - Callback function to call for each key-value pair
- `data` - User-provided data pointer passed to the callback function

**Note:** The `value` parameter in the callback is a temporary pointer. If you need to store the value, copy it to a new string using `strdup()` or similar.

**Example:**

```c
void config_callback(void* data, const char* section, const char* key, const char* value) {
    printf("Section: %s, Key: %s, Value: %s\n", section, key, value);
}

struct configparse parser;
init_configparse(&parser, "config.ini");
configparse_parse_all(&parser, config_callback, NULL);
```

---

## Usage Examples

### Basic Usage

```c
#include <configparse.h>
#include <stdio.h>

void config_callback(void* data, const char* section, const char* key, const char* value) {
    printf("Section: %s, Key: %s, Value: %s\n", section, key, value);
}

int main(void) {
    struct configparse parser;
    if (!init_configparse(&parser, "config.ini")) {
        fprintf(stderr, "Failed to initialize parser\n");
        return 1;
    }

    configparse_parse_all(&parser, config_callback, NULL);

    return 0;
}
```

### With Custom Data Structure

```c
#include <configparse.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    const char* key;
    const char* value;
} callback_data_t;

void config_callback(void* data, const char* section, const char* key, const char* value) {
    callback_data_t* callback_data = (callback_data_t*)data;
    printf("Section: %s, Key: %s, Value: %s\n", section, key, value);
    
    // Store values if needed (copy the string)
    if (strcmp(key, callback_data->key) == 0) {
        callback_data->value = strdup(value);
    }
}

int main(void) {
    struct configparse parser;
    if (!init_configparse(&parser, "config.ini")) {
        fprintf(stderr, "Failed to initialize parser\n");
        return 1;
    }

    callback_data_t data = { "editor", NULL };
    configparse_parse_all(&parser, config_callback, &data);
    
    if (data.value != NULL) {
        printf("Found editor: %s\n", data.value);
        free((void*)data.value);
    }

    return 0;
}
```

### Reading Specific Values

```c
#include <configparse.h>
#include <stdio.h>

int main(void) {
    struct configparse parser;
    if (!init_configparse(&parser, "config.ini")) {
        fprintf(stderr, "Failed to initialize parser\n");
        return 1;
    }

    char *editor = configparse_get_value(&parser, "core", "editor");
    char *excludesfile = configparse_get_value(&parser, "core", "excludesfile");
    
    if (editor != NULL) {
        printf("Editor: %s\n", editor);
    }
    if (excludesfile != NULL) {
        printf("Excludes file: %s\n", excludesfile);
    }

    return 0;
}
```

### Example INI File Format

The parser supports standard INI file format with sections, subsections, and key-value pairs:

```ini
[core]
    editor = vim
    excludesfile = ~/.gitignore

[remote "origin"]
    url = git@github.com:username/repo.git
    fetch = +refs/heads/*:refs/remotes/origin/*
```

---

## Important Notes

### File Format Support

- The parser supports standard INI file format with sections, subsections, and key-value pairs
- Section names can be quoted to include spaces or special characters
- Comments start with `#` or `;` and continue to the end of the line
- Empty lines are ignored
- Key-value pairs can be indented

### Memory Management

- The parser manages file operations internally
- String values returned by `configparse_get_value()` are temporary pointers
- If you need to store values, copy them using `strdup()` or similar functions

### Performance Considerations

- `configparse_get_value()` has low performance and should only be used for reading specific keys in small files
- For reading multiple keys or larger files, use `configparse_parse_all()` with a callback function
- The parser reads the file sequentially

### Thread Safety

Configparse operations are **not thread-safe**. External synchronization is required for concurrent access.

### Important Usage Notes

- Always check the return value of `init_configparse()` before using the parser
- Don't modify the configuration file while parsing
- String pointers returned by `configparse_get_value()` are temporary - copy them if you need to store values
- For better performance with multiple keys, use `configparse_parse_all()` instead of multiple `configparse_get_value()` calls

