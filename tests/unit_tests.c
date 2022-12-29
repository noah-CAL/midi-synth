#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "asserts.h"
#include "include/midi.h"

void midi_init() {
    uint8_t num_words = 2;
    UMP_word bytestream[2][WORD_SIZE_BITS] = {
        {
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
        },
        {
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
        },
    };
    UMP *packet = init_UMP(bytestream, num_words);
    ASSERT_EQ(packet->num_words, 2);
    ASSERT_MEM_EQ(packet->words, bytestream[0]);
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