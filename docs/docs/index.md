---
title: Introduction
description: Modern, lightweight C utility library
---

<p align="center">
  <img src="assets/logo.png" alt="util logo" width="300"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/license-MIT-green" />
  <img src="https://img.shields.io/badge/version-1.1.0-blue" />
  <img src="https://img.shields.io/badge/language-C-red" />
</p>

## Overview

Util is a modern, lightweight C utility library that extends the standard C library with a collection of independent, reusable modules. Each module can be used on its own with no external dependencies.

- **Modular Design**: Each module is independent and can be used separately
- **Cross-Platform**: Works Unix System like Linux, macOS.
- **C++ Compatible**: All modules are compatible with C++ code
- **MIT Licensed**: Free to use in both open-source and commercial projects
- **Zero Dependencies**: No external dependencies required
- **Modern C**: Written in modern C with clean, maintainable code

## Requirements

- GCC or Clang with C11 support
- GNU Make 3.81 or later
- glibc or compatible standard C library

## Quick Start

### 1. Clone

```bash
git clone https://github.com/unsigned/util.git
cd util
```

### 2. Configure

Edit `config/config.mk`. The key options are:

- `LIB_NAME` — library name, default `util`
- `LIB_METHOD` — `static` or `shared`
- `DEBUG` — `0` for release, `1` for debug with sanitizers

### 3. Build

```bash
make all
```

Headers are in `include/`, the built library is in `lib/`.

### 4. Link

```bash
gcc -I./include your_program.c -L./lib -lutil -o your_program
```

## Make Targets

```makefile
make all        # build the library
make test       # build and run all tests
make test-NAME  # build and run tests for module NAME
make clean      # remove build artifacts and lib output
make list       # list all source files
make info       # show current build configuration
make docs       # build and serve documentation locally
make clang      # generate compile_commands.json for tooling
make format     # run clang-format over include, src, test
make docker     # build and enter the Docker container
make help       # show the help message
```

## Documentation

Documentation is built with MkDocs Material. Running `make docs` will create a virtual environment if needed, install dependencies, build the site, and start a local server at `http://127.0.0.1:8000`.

## License

MIT License, Copyright (C) 2025 - 2026 Yixiang Qiu
