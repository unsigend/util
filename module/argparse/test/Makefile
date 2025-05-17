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
# filter out the demo.o
OBJS            :=      $(filter-out $(CASE_PATH)/demo.o, $(OBJS))

TARGET          :=      test.out
DEMO            :=      demo.out

.DEFAULT_GOAL	:=      all
.PHONY			:      	all clean

ifeq ($(LIB_METHOD), static)
LIB_DEPS        :=      $(LIB_PATH)/lib$(LIB_NAME).a
else
LIB_DEPS        :=      $(LIB_PATH)/lib$(LIB_NAME).so
endif

# clean the object file and the target file
clean:
	@rm -rf $(CASE_PATH)/*.o
	@rm -rf $(CUR_PATH)/$(TARGET)
	@rm -rf $(CUR_PATH)/$(DEMO)

# generate the object file
$(CASE_PATH)/%.o : $(CASE_PATH)/%.c $(LIB_DEPS)
	@$(GCC) $(GCC_FLAGS) -c $< -o $@

$(CUR_PATH)/$(DEMO) : $(CASE_PATH)/demo.o $(LIB_DEPS)
	@$(LD) $(GCC_FLAGS) -L$(LIB_PATH) -l$(LIB_NAME) $< -o $@

all: $(OBJS) $(DEMO)
	@$(LD) $(GCC_FLAGS) -o $(CUR_PATH)/$(TARGET) $(OBJS) -L$(LIB_PATH) -l$(LIB_NAME) && $(CUR_PATH)/$(TARGET)
