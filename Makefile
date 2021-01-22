
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

bin:
	mkdir -p bin

bin/%.tab.c: %.y bin
	bison -o $@ $< --defines=$(<:%.y=bin/%.tab.h)

bin/%.yy.c: %.l bin
	flex -o $@ $<

bin/%.o: bin/%.c bin
	$(CC) -c -o $@ $<

bin/%.o: %.c bin
	$(CC) -c -o $@ $<

count:
	cat *.h *.c *.l *.y | sed '/^\s*#/d;/^\s*$/d' | wc

clean:
	rm bin/*