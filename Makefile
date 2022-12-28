CC = gcc
CFLAGS = -Wall -I./include/
LDFLAGS = -lcheck -lm -lsubunit

TEST_SRC = $(wildcard tests/*.c) src/midi.c # synth.c
TEST_OBJ = $(TEST_SRC:.c=.o)

SRC = src/main.c $(TEST_SRC)
OBJFILES = $(SRC:.c=.o)

DEPS = $(SRC:.c=.h)
EXEC = bin/main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJFILES)
	$(CC) -o $(EXEC) $(OBJFILES) $(CFLAGS) $(LDFLAGS)

.PHONY: check
check: $(TEST_OBJ)
	$(CC) -o check -ggdb $(TEST_OBJ) $(CFLAGS) $(LDFLAGS)
	./check

.PHONY: clean
clean:
	rm -rf $(OBJFILES) $(wildcard *.o)
