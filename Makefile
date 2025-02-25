NPROCS = $(shell grep -c 'processor' /proc/cpuinfo)
MAKEFLAGS += -j$(NPROCS)
CPP=g++
CC=gcc
CFLAGS=-Wall -Werror -Wpedantic -g -Og -I.
CPPFLAGS=-std=c++20 ${CFLAGS}
DEPDIR=./deps

SRCS=$(wildcard *.cpp) $(wildcard dave/src/*.cpp)
OBJS=$(SRCS:.cpp=.o)

C_SRCS=$(wildcard *.c)
C_OBJS=$(C_SRCS:.c=.o)

all: run

DEPS  = $(patsubst %.o, $(DEPDIR)/%.d, $(OBJS))
DEPS += $(patsubst %.o, $(DEPDIR)/%.d, $(C_OBJS))
-include $(DEPS)

.PHONY: run
run: demo
	./demo

.PHONY: tidy
tidy: $(SRCS)
	clang-tidy $(SRCS) -- $(CPPFLAGS)


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
	@[ ! -d $(DEPDIR)/dave/src ] && mkdir -p $(DEPDIR)/dave/src

%.o:%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

