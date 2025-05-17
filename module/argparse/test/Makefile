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

LIB_NAME      	:=      $(UTIL_LIBRARY_NAME)

SRCS 	  		:=      $(wildcard $(CASE_PATH)/*.c)
OBJS 	  		:=      $(patsubst %.c, %.o, $(SRCS))
TARGET          :=      test.out

.DEFAULT_GOAL	:=      all
.PHONY			:      	all clean

# clean the object file and the target file
clean:
	@rm -rf $(CASE_PATH)/*.o
	@rm -rf $(CUR_PATH)/$(TARGET)

# generate the object file
$(CASE_PATH)/%.o : $(CASE_PATH)/%.c 
	@$(GCC) $(GCC_FLAGS) -c $< -o $@

all: $(OBJS)
	@$(LD) $(GCC_FLAGS) -o $(CUR_PATH)/$(TARGET) $^ -L$(LIB_PATH) -l$(LIB_NAME) && $(CUR_PATH)/$(TARGET)
