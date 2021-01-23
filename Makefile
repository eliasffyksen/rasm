
CC=clang -Wall -g
SRC=$(wildcard *.y *.l *.c)
OBJS:=$(SRC:%=bin/%)
OBJS:=$(OBJS:.l=.yy.o)
OBJS:=$(OBJS:.y=.tab.o)
OBJS:=$(OBJS:.c=.o)

.PHONY: all clean count

all: bin/rasm

bin/rasm: $(OBJS)
	$(CC) -o $@ $^

bin/%.tab.c: %.y
	bison -o $@ $< --defines=$(<:%.y=bin/%.tab.h)

bin/%.yy.c: %.l
	flex -o $@ $<

bin/%.o: bin/%.c
	$(CC) -c -o $@ $<

bin/%.o: %.c
	$(CC) -c -o $@ $<

count:
	cat *.h *.c *.l *.y | sed '/^\s*#/d;/^\s*$/d' | wc

clean:
	rm bin/*