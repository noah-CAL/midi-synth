#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "asserts.h"
#include "include/midi.h"

void midi_basic() {
    ASSERT_EQ(2, 3);
}

void midi_advanced() {
    ASSERT_NULL(0x01);
}

void IO_basic() {
    ASSERT_NEQ("4", "4");
}

int main() {
    TestRunner *r = create_test_runner();

    TestSuite *midi_tests = create_test_suite();
    add_test_suite(r, midi_tests);
    add_test_case(midi_tests, create_test_case("Midi Basic", &midi_basic));
    add_test_case(midi_tests, create_test_case("Midi Adv.", &midi_advanced));

    TestSuite *IO_tests = create_test_suite();
    add_test_suite(r, IO_tests);
    add_test_case(IO_tests, create_test_case("IO Basic", &IO_basic));

    run_tests(r);
    dealloc_tests(r);
    return 0;
}