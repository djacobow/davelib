NPROCS = $(shell grep -c 'processor' /proc/cpuinfo)

MAKEFLAGS += -j$(NPROCS)

compiler_choice=clang19

CFLAGS=-Wall -Werror -Wpedantic -Wno-gnu-zero-variadic-macro-arguments -g -Og -I.

ifeq ($(compiler_choice),clang19)
	CPP=clang++-19
	CC=clang-19
else
	CPP=g++
	CC=gcc
endif

CPPFLAGS=-std=c++20 ${CFLAGS}

CT=clang-tidy-19

MACHINE=$(shell uname -m)

ifeq ($(MACHINE),aarch64)
	CPPFLAGS+=-stdlib=libc++
endif

DEPDIR=./deps

SRCS=$(wildcard *.cpp) $(wildcard dave/src/*/*.cpp)
OBJS=$(SRCS:.cpp=.o)

C_SRCS=$(wildcard *.c)
C_OBJS=$(C_SRCS:.c=.o)

all: run

DEPS  = $(patsubst %.o, $(DEPDIR)/%.d, $(OBJS))
DEPS += $(patsubst %.o, $(DEPDIR)/%.d, $(C_OBJS))

-include $(DEPS)

.PHONY: run
run: demo $(DEPS)
	./demo

.PHONY: tidy
tidy: $(SRCS)
	$(CT) $(SRCS) -- $(CPPFLAGS)


.PHONY: clean
clean:
	rm -f demo $(OBJS) $(C_OBJS)
	rm -rf $(DEPDIR)

demo: $(OBJS) $(C_OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) $(C_OBJS) -o demo

$(DEPDIR)/%.d: %.c $(DEPDIR)
	$(CC) $(CFLAGS) -M $< > $@

$(DEPDIR)/%.d: %.cpp $(DEPDIR)
	$(CPP) $(CPPFLAGS) -M $< > $@

$(DEPDIR):
	mkdir -p $(DEPDIR)/dave/src/async
	mkdir -p $(DEPDIR)/dave/src/err
	mkdir -p $(DEPDIR)/dave/src/event
	mkdir -p $(DEPDIR)/dave/src/log
	mkdir -p $(DEPDIR)/dave/src/util

%.o:%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

