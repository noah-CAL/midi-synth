# Makefile format modeled after CS 61C Project 1 - Snek Makefile
CC = gcc
CFLAGS = -Wall -std=c99 -I. -g
LDFLAGS = 
SYNTH_DEPS = #src/main.o src/midi.o
UNIT_TEST_DEPS = tests/unit_tests.o tests/asserts.o  tests/asserts.h include/midi.h src/midi.o 
# UNIT_TEST_DEPS += tests/unit_tests.h
# INT_TEST_DEPS = main.o integration_tests.o asserts.o

help:
	@echo Usage:
	@echo make synth: Compiles the SYNTH executable to process input.
	@echo make unit-tests: Compiles the unit tests.
	@echo make run-unit-tests: Compiles and runs unit tests.
	@echo make debug-unit-tests: Compiles unit tests and starts the debugger.
	@echo make clean: Removes executables and input files. IMPLEMENT
# @echo make integration-tests: Compiles the integration tests.
# @echo make run-integration-tests: Compiles and runs integration tests.
# @echo make debug-integration-tests: Compiles integration tests and starts the debugger.

synth: $(SYNTH_DEPS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

unit-tests: $(UNIT_TEST_DEPS)
	$(CC) -o unit-test $^ $(CFLAGS) $(LDFLAGS)

.PHONY: run-unit-tests
run-unit-tests: unit-tests
	./unit-test

tests/asserts.h:
	@echo here

%.o: %.c tests/asserts.h (wildcard include/*.h)
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

%.h: %.c
	make unit-tests
	
.PHONY: debug-unit-tests
debug-unit-tests: unit-tests
	cgdb ./unit-test

.PHONY: clean
clean:
	rm -r $(wildcard tests/*.o)
