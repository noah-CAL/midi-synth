#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "asserts.h"
#include "include/midi.h"

void midi_init() {
    #define NUM_WORDS 2
    UMP_word bytestream[NUM_WORDS] = { 0xDEADBEEF, 0xABCD1234 };
    UMP *packet = init_UMP(bytestream, NUM_WORDS);
    ASSERT_EQ(packet->num_words, 2);
    for (int i = 0; i < NUM_WORDS; i += 1) {
        ASSERT_EQ(packet->words[i], bytestream[i]);
    }
    free_UMP(packet);
    #undef NUM_WORDS
}

int main() {
    TestRunner *r = create_test_runner();

    TestSuite *midi_tests = create_test_suite();
    add_test_suite(r, midi_tests);
    add_test_case(midi_tests, create_test_case("Midi Init", &midi_init));

    run_tests(r);
    dealloc_tests(r);
    return 0;
}