CC = gcc
CFLAGS = -Wall -I./include/
SRC = src/main.c src/midi.c # synth.c
OBJFILES = $(SRC:.c=.o)
DEPS = $(SRC:.c=.h)
EXEC = bin/main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJFILES)
	$(CC) -o $(EXEC) $(OBJFILES) $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJFILES) $(wildcard *.o)
