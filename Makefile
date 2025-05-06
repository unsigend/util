# MIT License

# Copyright (c) 2025 QIU YIXIANG

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Makefile for building and running test in util

BUILD_PATH		:= 	./build
SCRIPT_PATH		:= 	./script
INSTALL_PATH    :=  ./include
MODULE_PATH		:= 	./module

# Include the sub-makefile script
include $(SCRIPT_PATH)/config.mk

# Automatically detect all modules in the module path
ifndef $(MODULES)
MODULES			:= 		$(wildcard $(MODULE_PATH)/*)
MODULES   		:= 		$(notdir $(MODULES))
endif
MODULES 		:= 		$(sort $(MODULES))

ifdef $(V)
VERBOSE         := 		$(V)
endif

# Flags for tools
GCC     		:=  	gcc
CXX     		:=  	g++
LD 				:=  	$(GCC)
AR 				:=  	ar

# Flags for GCC flags
GCC_FLAGS		:=  	
GCC_FLAGS		+= 	    -std=c11
GCC_FLAGS		+= 	    -Wall -Wextra -Werror -Wshadow

GCC_DEPS_FLAGS	:=
GCC_DEPS_FLAGS	+= 	    -MMD -MF -MP

# Flags for Archive
AR_FLAGS		:=
AR_FLAGS		+= 	    -rcs

# Flags for CXX flags
# Compitable with C++ program
CXX_FLAGS		:=
CXX_FLAGS		+= 	    -std=c++17
CXX_FLAGS		+= 	    -Wall -Wextra -Werror -Wshadow


# Variables for each module


# Targets will defined here #

# Default Goal will be help
.DEFAULT_GOAL	:= 	help
.PHONY:				all clean help always list

# help target
help:
	@echo "Makefile for building the util library"
	@echo "Copyright (c) 2025 QIU YIXIANG"
	@echo "USAGE:"
	@echo "\tmake all\tbuild all modules"
	@echo "\tmake clean\tclean builds"
	@echo "\tmake list\tlist all modules"
	@echo "\tmake help\tshow this help message"
	
# all target
all:

# clean target
clean:
	@rm -rf $(BUILD_PATH)

# always target
always:
	@:

# list target
list:
	@echo "Module List : "
	@for module in $(MODULES); do \
		echo "  - $$module"; \
	done
	@echo "Total: $(shell echo $(MODULES) | wc -w | xargs) modules"
	