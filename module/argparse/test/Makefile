# Makefile for building the argparse library
# Test for argparse library

GCC      		:= 		gcc
LD    			:= 		$(GCC)

ROOT_PATH     	:=	  	..
CUR_PATH      	:=      .
INCLUDE_PATH  	:=      $(ROOT_PATH)/include
LIB_PATH      	:=      $(UTIL_LIBRARY_PATH)
CASE_PATH     	:=      $(CUR_PATH)/case

GCC_FLAGS   	:=      -std=gnu11
GCC_FLAGS 		+= 		-Wall -Werror -Wextra -O0
GCC_FLAGS   	+=      -Wno-unused-parameter -Wno-unused-variable
GCC_FLAGS   	+=      -Wno-unused-function -Wno-unused-label
GCC_FLAGS   	+=      -I$(INCLUDE_PATH) -I$(UTEST_INCLUDE_PATH)

ifeq ($(DEBUG), 1)
GCC_FLAGS   	+=      -g
GCC_FLAGS   	+=      -O0
else
GCC_FLAGS   	+=      -O2
endif

LIB_NAME      	:=      $(UTIL_LIBRARY_NAME)

SRCS 	  		:=      $(wildcard $(CASE_PATH)/*.c)
OBJS 	  		:=      $(patsubst %.c, %.o, $(SRCS))

TARGET          :=      test.out
DEMO            :=      demo.out

.DEFAULT_GOAL	:=      all
.PHONY			:      	all clean

ifeq ($(LIB_METHOD), static)
LIB_DEPS        :=      $(LIB_PATH)/lib$(LIB_NAME).a
else
ifeq ($(HOST_OS), Darwin)
LIB_DEPS        :=      $(LIB_PATH)/lib$(LIB_NAME).dylib
else
LIB_DEPS        :=      $(LIB_PATH)/lib$(LIB_NAME).so
endif
endif

ifeq ($(LIB_METHOD), shared)
LIB_FLAGS       +=      -Wl,-rpath,$(LIB_PATH)
endif

# clean the object file and the target file
clean:
	@rm -f $(CASE_PATH)/*.o
	@rm -f $(CUR_PATH)/*.o
	@rm -rf $(CUR_PATH)/$(TARGET)
	@rm -rf $(CUR_PATH)/$(DEMO)

# generate the object file in case/
$(CASE_PATH)/%.o : $(CASE_PATH)/%.c $(LIB_DEPS)
	@$(GCC) $(GCC_FLAGS) -c $< -o $@

%.o: %.c $(LIB_DEPS)
	@$(GCC) $(GCC_FLAGS) -c $< -o $@

$(TARGET) : $(OBJS) main.o
	@$(LD) $(GCC_FLAGS) $^ -L$(LIB_PATH) -l$(LIB_NAME) -o $@
	@echo "Run ./module/argparse/test/$(TARGET) see the test result"

$(DEMO) : demo.o
	@$(LD) $(GCC_FLAGS) $^ -L$(LIB_PATH) -l$(LIB_NAME) -o $@
	@echo "Run ./module/argparse/test/$(DEMO) see the demo"

all: $(TARGET) $(DEMO)
