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

CUR_PATH        :=  $(CURDIR)
CONFIG_PATH     :=  ./config
BUILD_PATH		:= 	./build
SCRIPT_PATH		:= 	./script
INSTALL_PATH    :=  ./include
MODULE_PATH		:= 	./module
LIB_PATH		:= 	./lib

# Include the sub-makefile script
include $(CONFIG_PATH)/config.mk

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
GCC_DEPS_FLAGS	+= 	    -MMD -MP -MF

# Flags for Archive
AR_FLAGS		:=
AR_FLAGS		+= 	    -rcs

# Flags for CXX flags
# Compitable with C++ program
CXX_FLAGS		:=
CXX_FLAGS		+= 	    -std=c++17
CXX_FLAGS		+= 	    -Wall -Wextra -Werror -Wshadow

# Cancel Implicit rules
%.o : %.c
%.o: %.cpp
%.o: %.s
%: %.o
%.out: %.o

# Variables for each module

# Variable $(module)_SRC : Module source files
$(foreach module, $(MODULES),$(eval $(module)_SRC := $(wildcard $(MODULE_PATH)/$(module)/src/*.c)))
# Variable $(module)_OBJ : Module object files
$(foreach module, $(MODULES),$(eval $(module)_OBJ := $(patsubst $(MODULE_PATH)/$(module)/src/%.c, \
	$(BUILD_PATH)/$(module)/obj/%.o, $($(module)_SRC))))
# Variable $(module)_INC : Module include files
$(foreach module, $(MODULES),$(eval $(module)_INC := $(wildcard $(MODULE_PATH)/$(module)/include)))
# Variable $(module)_DEP : Module depedency files
$(foreach module, $(MODULES),$(eval $(module)_DEP := $(wildcard $(BUILD_PATH)/$(module)/dep/*.d)))
# Variable ALL_OBJ : All object files
ALL_OBJ			:= $(foreach module, $(MODULES), $($(module)_OBJ))

# Automatically generate targets for each module

# generate rules for directory check 
# $(module)_check_dir:
$(foreach module, $(MODULES), \
$(eval \
$(module)_check_dir:;\
	$(shell mkdir -p $(BUILD_PATH)/$(module)/obj) \
	$(shell mkdir -p $(BUILD_PATH)/$(module)/dep) \
	@echo "Start building module : $(module)"; \
))

# generate rule for module
# $(module): $(module)_OBJ
$(foreach module, $(MODULES), \
$(eval \
$(module): $(module)_check_dir $($(module)_OBJ); \
	@echo "Build Module : $(module)\n"; \
))

# generate rules for build .o files
# $(module)_OBJ: $(module)_check_dir $($(module)_SRC)
$(foreach module, $(MODULES), \
$(eval \
$($(module)_OBJ): $($(module)_SRC); \
	@$(GCC) $(GCC_FLAGS) $(GCC_DEPS_FLAGS)  \
	$$(addprefix $(BUILD_PATH)/$(module)/dep/, $$(patsubst %.o, %.d,$$(notdir $$@))) \
	-I $($(module)_INC) -c $$< -o $$@; \
	echo "  + CC\t$$<" \
))

# generate include the dependency files for each module
# -include $($(module)_DEP)
$(foreach module, $(MODULES), \
$(eval \
-include $($(module)_DEP) \
))

# Targets will defined here #

# Default Goal will be help
.DEFAULT_GOAL	:= 	help
.PHONY:				all clean help always list info lib

# help target
help:
	@echo "Makefile for building the util library"
	@echo "Copyright (c) 2025 QIU YIXIANG"
	@echo "USAGE:"
	@echo "\tmake all\tbuild all modules"
	@echo "\tmake clean\tclean builds"
	@echo "\tmake list\tlist all modules"
	@echo "\tmake help\tshow this help message"
	@echo ""
	@echo "You can change the configuration in config/config.mk"
# info target
info: 
	@echo "Building util library"
	@echo "Selected Module : $(shell echo $(MODULES) | wc -w | xargs)"
	@echo "Building Method : $(LIB_METHOD)\n"

# all target
all: info $(MODULES) lib
	
# clean target
clean:
	@rm -rf $(BUILD_PATH)
	@rm -rf $(LIB_PATH)

# always target
always:
	@:

# lib target
lib: $(ALL_OBJ)
	@mkdir -p $(LIB_PATH)
ifeq ($(LIB_METHOD), static)
	@$(AR) $(AR_FLAGS) $(LIB_PATH)/lib$(LIB_NAME).a $^
	@echo "  + AR\tlib$(LIB_NAME).a"
	@echo "Building $(LIB_METHOD) library : $(LIB_PATH)/lib$(LIB_NAME).a"
else ifeq ($(LIB_METHOD), shared)
	@$(LD) -shared -o $(LIB_PATH)/lib$(LIB_NAME).so $^
	@echo "+ LD\tlib$(LIB_NAME).so"
	@echo "Building $(LIB_METHOD) library : $(LIB_PATH)/lib$(LIB_NAME).so"
else
	@echo "Error: Unknown library method: $(LIB_METHOD)"
endif
	
# list target
list:
	@echo "Module List : "
	@for module in $(MODULES); do \
		echo "  - $$module"; \
	done
	@echo "Total: $(shell echo $(MODULES) | wc -w | xargs) modules"
	