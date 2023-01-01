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

void message_type() {
    uint8_t num_types = 7;
    uint8_t message_code[] = {
        0x0, // UTILITY
        0x1, // SYSTEM_COMMON
        0x1, // SYSTEM_REAL_TIME
        0x2, // MIDI_1_CHNL_VOICE
        0x3, // DATA_64_BIT
        0x4, // MIDI_2_CHNL_VOICE
        0x5, // DATA_128_BIT
    };
    MESSAGE_TYPE message_types[] = {
        UTILITY,
        SYSTEM_COMMON,
        SYSTEM_REAL_TIME,
        MIDI_1_CHNL_VOICE,
        DATA_64_BIT,
        MIDI_2_CHNL_VOICE,
        DATA_128_BIT,
    };
    for (int i = 0; i < num_types; i += 1) {
        uint8_t code = message_code[i];
        MESSAGE_TYPE type = message_types[i];
        UMP_word bytestream[] = { code << 28, 0xF6 };
        if (type == SYSTEM_REAL_TIME) {
            bytestream[1] = 0xF8;
        }
        UMP *packet = init_UMP(bytestream, 2);
        ASSERT_EQ(packet->msg_type, message_types[i]);
        free_UMP(packet);
    }
}

int main() {
    TestRunner *r = create_test_runner();

    TestSuite *midi_tests = create_test_suite();
    add_test_suite(r, midi_tests);
    add_test_case(midi_tests, create_test_case("Midi Init", &midi_init));
    add_test_case(midi_tests, create_test_case("Midi Message Types", &message_type));

    run_tests(r);
    dealloc_tests(r);
    return 0;
}