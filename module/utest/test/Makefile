# Makefile for building the utest library demo
# A simple Makefile 

GCC      		:= 		gcc
LD    			:= 		$(GCC)

ROOT_PATH     	:=	  	..
CUR_PATH      	:=      .
INCLUDE_PATH  	:=      $(ROOT_PATH)/include
LIB_PATH      	:=      $(UTIL_LIBRARY_PATH)
DEMO_PATH     	:=      $(CUR_PATH)/demo

GCC_FLAGS   	:=      -std=gnu11
GCC_FLAGS 		+= 		-Wall -Werror -Wextra -O0
GCC_FLAGS   	+=      -Wno-unused-parameter -Wno-unused-variable
GCC_FLAGS   	+=      -Wno-unused-function -Wno-unused-label
GCC_FLAGS   	+=      -I$(INCLUDE_PATH)

LIB_NAME      	:=      $(UTIL_LIBRARY_NAME)
LIB_FLAGS     	:=      -L$(LIB_PATH) -l$(LIB_NAME)


ifeq ($(LIB_METHOD), shared)
LIB_FLAGS     	+=      -Wl,-rpath,$(LIB_PATH)
endif

SRCS 	  		:=      $(wildcard $(DEMO_PATH)/*.c)
OBJS 	  		:=      $(patsubst %.c, %.o, $(SRCS))
TARGET          :=      test.out

.DEFAULT_GOAL	:=      all
.PHONY			:      	all clean

all: $(OBJS)
	@$(LD) $(GCC_FLAGS) $(LIB_FLAGS) $^ -o $(CUR_PATH)/$(TARGET) && $(CUR_PATH)/$(TARGET)

$(DEMO_PATH)/%.o : $(DEMO_PATH)/%.c 
	@$(GCC) $(GCC_FLAGS) -c $< -o $@

clean:
	@rm -rf $(DEMO_PATH)/*.o
	@rm -rf $(CUR_PATH)/$(TARGET)