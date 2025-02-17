CPP=g++
CC=gcc
CFLAGS=-Wall -g -Og -I.
CPPFLAGS=-std=c++20 -DJSON_DIAGNOSTICS ${CFLAGS}

SRCS=$(wildcard *.cpp) $(wildcard davelog/src/*.cpp)
INCS=$(wildcard *.h) $(wildcard /*.hpp) $(wildcard davelog/*.h) $(wildcard davelog/*.hpp)
OBJS=$(SRCS:.cpp=.o)

C_SRCS=$(wildcard *.c)
C_OBJS=$(C_SRCS:.c=.o)

.PHONY: run
run: demo
	./demo

.PHONY: clean
clean:
	rm -f demo $(OBJS) $(C_OBJS)

%.o:%.cpp $(INCS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

%.o:%.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

demo: $(OBJS) $(C_OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) $(C_OBJS) -o demo
