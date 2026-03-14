# MIT License
#
# Copyright (c) 2025 QIU YIXIANG
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

# Makefile for util test suite

include ../config/config.mk

# paths
CUR_DIR       := .
BUILD_PATH   := $(CUR_DIR)/build
OBJ_PATH     := $(BUILD_PATH)/obj
DEP_PATH     := $(BUILD_PATH)/dep
CASES_PATH   := $(CUR_DIR)/cases
UTIL_INCLUDE := ../include
UTIL_LIB_PATH := ../lib

# util library
HOST_OS := $(shell uname -s)
GCC     ?= gcc
ifndef LIB_NAME
LIB_NAME := util
endif
ifeq ($(LIB_METHOD), static)
UTIL_LIB_POSTFIX := .a
else
ifeq ($(HOST_OS), Darwin)
UTIL_LIB_POSTFIX := .dylib
else
UTIL_LIB_POSTFIX := .so
endif
endif
UTIL_LIB_DEPS := $(UTIL_LIB_PATH)/lib$(LIB_NAME)$(UTIL_LIB_POSTFIX)

# source and object files
SRCS := $(shell find $(CASES_PATH) -name "*.c")
OBJS := $(patsubst $(CASES_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))
DEPS := $(patsubst $(OBJ_PATH)/%.o, $(DEP_PATH)/%.d, $(OBJS))

# tools
CC := $(GCC)
LD := $(CC)

# compiler flags
CC_FLAGS := -std=c11 -Wall -Wextra -Werror
CC_FLAGS += -I$(UTIL_INCLUDE)
ifeq ($(DEBUG), 1)
CC_FLAGS += -g -O0
else
CC_FLAGS += -O2
endif

CC_DEPS_FLAGS := -MMD -MP -MF
LD_FLAGS      := -L$(UTIL_LIB_PATH) -l$(LIB_NAME)

# .C
$(OBJ_PATH)/%.o: $(CASES_PATH)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_PATH)/$*.d)
	@$(CC) $(CC_FLAGS) $(CC_DEPS_FLAGS) $(DEP_PATH)/$*.d -MT $@ -c $< -o $@
	@echo "  + CC	$<"

-include $(DEPS)

.SECONDARY: $(DEPS)

.DEFAULT_GOAL := test
.PHONY: all test test-% clean check-dep

check-dep:
	@mkdir -p $(DEP_PATH)

all: check-dep $(OBJS)
	@mkdir -p $(BUILD_PATH)
	@$(LD) $(OBJS) $(LD_FLAGS) -o $(BUILD_PATH)/test
	@echo "  + LD	$(BUILD_PATH)/test"
	@echo "Build test binary: $(BUILD_PATH)/test"
	@echo ""

test: all
	@$(BUILD_PATH)/test

test-%: all
	@$(BUILD_PATH)/test $*

clean:
	@rm -rf $(BUILD_PATH)
