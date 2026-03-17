---
title: Introduction
description: Modern, lightweight C utility library
---

<p align="center">
  <img src="assets/logo.png" alt="util logo" width="300"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/license-MIT-green" />
  <img src="https://img.shields.io/badge/version-0.1-blue" />
  <img src="https://img.shields.io/badge/language-C-red" />
</p>

## Overview

Util is a modern, lightweight C utility library that extends the standard C library by providing additional essential modules. Designed with simplicity and modularity in mind, it offers a collection of reusable components that can be easily integrated into any C project.

### Key Features

- **Modular Design**: Each module is independent and can be used separately
- **Header-Only**: Most modules are header-only, making integration simple
- **Cross-Platform**: Works on Linux, macOS, and Windows
- **C++ Compatible**: All modules are compatible with C++ code
- **MIT Licensed**: Free to use in both open-source and commercial projects
- **Zero Dependencies**: No external dependencies required
- **Modern C**: Written in modern C with clean, maintainable code

## Requirements

### Build Dependencies

- **C Compiler**: GCC or Clang with C11 support
- **Make**: GNU Make 3.81 or later
- **Standard C Library**: glibc or compatible

## Quick Start

### 1. Clone the Repository

```bash
git clone https://github.com/unsigend/util.git
cd util
```

### 2. Configure Build

Configure the build in `config/config.mk`. The most important options are:

- `LIB_NAME` – library name (default: `util`)
- `LIB_METHOD` – `static` or `shared`
- `DEBUG` – `0` for optimized builds, `1` for debug builds

### 3. Build and Install

Build the library:

```bash
make all
```

Install headers to the install path:

```bash
make install
```

### 4. Use the Library

Include the headers in your project:

```c
#include <utest.h>   /* unit test framework */
```

Link against the library:

```bash
gcc -I./include your_program.c -L./lib -lutil -o your_program
```

## Build Configuration

The build system is configured via `config/config.mk`:

- **C Standard**: C11
- **Build Method**: `static` or `shared`
- **Library Name**: `util`
- **Debug Mode**: `DEBUG=0` (release) or `DEBUG=1` (debug)

## Available Make Targets

Everything is managed through the top-level `Makefile`. Use `make help` to see detailed commands:

| Target           | Description                                      |
| ---------------- | ------------------------------------------------ |
| `make all`       | Build the library (same as `make lib`)           |
| `make lib`       | Build the library only                           |
| `make test`      | Build the library and run all tests              |
| `make test-NAME` | Build the library and run tests for module NAME  |
| `make clean`     | Remove build artifacts and test outputs          |
| `make list`      | List all source files                            |
| `make info`      | Show current build configuration                 |
| `make install`   | Install headers to `./include`                   |
| `make docs`      | Build and serve documentation                    |
| `make clang`     | Generate `compile_commands.json` for tooling     |
| `make format`    | Run `clang-format` over `include`, `src`, `test` |
| `make help`      | Show the Makefile help message                   |

You can change the configuration in `config/config.mk`.

## Why Util?

- **Simplicity**: Each module is designed to be simple to use while providing powerful features
- **Modularity**: Use only what you need, reducing code bloat
- **Maintainability**: Clean, well-documented code that's easy to understand and modify
- **Reliability**: Thoroughly tested with comprehensive unit tests
- **Community**: Open to contributions and improvements

## Contributing

Contributions are welcome! Whether it's:

- Bug reports
- Feature requests
- Documentation improvements
- Code contributions

Please feel free to:

1. Open an issue to discuss proposed changes
2. Fork the repository
3. Submit a pull request

## Building Documentation

The documentation is built using MkDocs with Material theme.

To build and serve the documentation locally:

```bash
make docs
```

This will:

- Create a Python virtual environment if needed
- Install dependencies automatically
- Build the documentation
- Start a local server at `http://127.0.0.1:8000`

## License

This project is licensed under the MIT License.
Copyright (C) 2025 - 2026 QIU YIXIANG
