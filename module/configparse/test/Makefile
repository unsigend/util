# Makefile for the configparse test

# export UTIL_LIBRARY_PATH
# export UTIL_LIBRARY_NAME
# export UTEST_INCLUDE_PATH
# export LIB_METHOD
# export HOST_OS
# export DEBUG

GCC      		:= 		gcc
LD    			:= 		$(GCC)

INCLUDE_PATH    :=      ../include
CASES_PATH      :=      ./cases
LIB_PATH        :=      $(UTIL_LIBRARY_PATH)

LIB_NAME        :=      $(UTIL_LIBRARY_NAME)

GCC_FLAGS   	:=      -std=gnu11
GCC_FLAGS 		+= 		-Wall -Werror -Wextra -O0
GCC_FLAGS   	+=      -Wno-unused-parameter -Wno-unused-variable
GCC_FLAGS   	+=      -Wno-unused-function -Wno-unused-label

ifeq ($(DEBUG), 1)
GCC_FLAGS   	+=      -g -O0
endif

GCC_FLAGS   	+=      -I$(INCLUDE_PATH) -I$(UTEST_INCLUDE_PATH)

LD_FLAGS        :=      -L$(LIB_PATH) -l$(LIB_NAME)

SRCS            :=      $(wildcard $(CASES_PATH)/*.c)
OBJS            :=      $(patsubst %.c, %.o, $(SRCS))

TARGET          :=      test.out

.DEFAULT_GOAL   :=      all
.PHONY          :=      all clean


$(CASES_PATH)/%.o: $(CASES_PATH)/%.c
	@$(GCC) $(GCC_FLAGS) -c $< -o $@

all: $(OBJS)
	@$(LD) $(GCC_FLAGS) $(LD_FLAGS) $(OBJS) -o $(TARGET)
	@echo "Run ./module/configparse/test/$(TARGET) see the test result"

clean:
	@rm -f $(CASES_PATH)/*.o
	@rm -f $(TARGET)


