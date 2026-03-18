# MIT License
#
# Copyright (c) 2026 YIXIANG QIU 
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# paths
CUR_DIR       := .
SRC_PATH     := $(CUR_DIR)/src
INCLUDE_PATH := $(CUR_DIR)/include
CONFIG_PATH  := $(CUR_DIR)/config
BUILD_PATH   := $(CUR_DIR)/build
OBJ_PATH     := $(BUILD_PATH)/obj
DEP_PATH     := $(BUILD_PATH)/dep
LIB_PATH     := $(CUR_DIR)/lib
TEST_PATH    := $(CUR_DIR)/test

include $(CONFIG_PATH)/config.mk

# source and object files
SRCS := $(shell find $(SRC_PATH) -name "*.c")
OBJS := $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))
DEPS := $(patsubst $(SRC_PATH)/%.c, $(DEP_PATH)/%.d, $(SRCS))

# host and tools
HOST_OS := $(shell uname -s)
GCC     := gcc
LD      := $(GCC)
AR      := ar

# compiler flags
GCC_FLAGS := -std=c11 -Wall -Wextra -Werror -Wshadow
GCC_FLAGS += -I$(INCLUDE_PATH)
ifeq ($(HOST_OS), Linux)
GCC_FLAGS += -fPIC
GCC_FLAGS += -D_POSIX_C_SOURCE=200809L
endif
ifeq ($(DEBUG), 1)
GCC_FLAGS += -g -O0
else
GCC_FLAGS += -O2
endif

GCC_DEPS_FLAGS := -MMD -MP -MF
AR_FLAGS       := -rcs

# cancel implicit rules
%.o : %.c
%.o: %.cpp
%.o: %.s
%: %.o
%.out: %.o

# .C
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_PATH)/$*.d)
	@$(GCC) $(GCC_FLAGS) $(GCC_DEPS_FLAGS) $(DEP_PATH)/$*.d -MT $@ -c $< -o $@
	@echo "  + CC	$<"

-include $(DEPS)

.DEFAULT_GOAL := help
.PHONY: all clean help create_build_dir lib list info docs clang format test test-%

create_build_dir:
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(DEP_PATH)
	@mkdir -p $(LIB_PATH)

lib: create_build_dir $(OBJS)
ifeq ($(LIB_METHOD), static)
	@$(AR) $(AR_FLAGS) $(LIB_PATH)/lib$(LIB_NAME).a $(OBJS)
	@echo "  + AR	lib$(LIB_NAME).a"
	@echo "Building static library: $(LIB_PATH)/lib$(LIB_NAME).a"
else ifeq ($(LIB_METHOD), shared)
ifeq ($(HOST_OS), Darwin)
	@$(LD) -shared -o $(LIB_PATH)/lib$(LIB_NAME).dylib $(OBJS)
	@echo "  + LD	lib$(LIB_NAME).dylib"
	@echo "Building shared library: $(LIB_PATH)/lib$(LIB_NAME).dylib"
else
	@$(LD) -shared -o $(LIB_PATH)/lib$(LIB_NAME).so $(OBJS)
	@echo "  + LD	lib$(LIB_NAME).so"
	@echo "Building shared library: $(LIB_PATH)/lib$(LIB_NAME).so"
endif
else
	@echo "Error: Unknown LIB_METHOD: $(LIB_METHOD)"
endif
	@echo ""

all: lib

test: lib
	@$(MAKE) -C $(TEST_PATH) test

test-%: lib
	@$(MAKE) -C $(TEST_PATH) test-$*

clean:
	@rm -rf $(BUILD_PATH)
	@rm -rf $(LIB_PATH)
	@$(MAKE) -C $(TEST_PATH) clean


list:
	@echo "Sources:"
	@echo $(SRCS) | tr ' ' '\n' | sed 's/^/  /'
	@echo "Total: $(words $(SRCS)) files"

info:
	@echo "Build configuration"
	@echo "  LIB_NAME   : $(LIB_NAME)"
	@echo "  LIB_METHOD : $(LIB_METHOD)"
	@echo "  DEBUG      : $(DEBUG)"
	@echo "  HOST_OS    : $(HOST_OS)"
	@echo ""

help:
	@echo "Makefile for util library (c) 2025 QIU YIXIANG"
	@echo "USAGE:"
	@echo "  make all       - build library"
	@echo "  make test      - build and run all tests"
	@echo "  make test-NAME - build and run tests for module NAME"
	@echo "  make clean     - remove build and lib"
	@echo "  make list      - list source files"
	@echo "  make info      - show build configuration"
	@echo "  make docs      - build and serve documentation"
	@echo "  make docker    - build the docker image for util"
	@echo "  make clang     - generate compile_commands.json"
	@echo "  make format    - format .c and .h"
	@echo "  make help      - this message\n"

# generate compile_commands.json
clang:
	@$(MAKE) clean
	@bear -- $(MAKE) test

# format .c and .h
format:
	@find $(INCLUDE_PATH) $(SRC_PATH) $(TEST_PATH) \
		\( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +
	@echo "Format done."

docs:
	@if [ ! -d "docs/venv" ]; then cd docs && python3 -m venv venv; fi
	@if ! docs/venv/bin/python3 -c "import mkdocs_material" 2>/dev/null; then docs/venv/bin/pip install mkdocs-material; fi
	@cd docs && venv/bin/mkdocs build
	@cd docs && venv/bin/mkdocs serve

# @private
deploy:
	@cd docs && venv/bin/mkdocs gh-deploy

export GCC

DOCKER_IMAGE := util
docker:
	@if [ -z "$$(docker images -q $(DOCKER_IMAGE) 2>/dev/null)" ]; then \
		echo "Building Docker image $(DOCKER_IMAGE)..."; \
		docker build -t $(DOCKER_IMAGE) -f Dockerfile .; \
	fi
	@if [ -n "$$(docker ps -aq -f name=$(DOCKER_IMAGE)-container 2>/dev/null)" ]; then \
		docker rm -f $(DOCKER_IMAGE)-container 2>/dev/null || true; \
	fi
	@docker run -it --name $(DOCKER_IMAGE)-container -v $(CUR_DIR):/workspace $(DOCKER_IMAGE) /bin/bash