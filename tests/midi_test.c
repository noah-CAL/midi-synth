#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "midi.h"

START_TEST(test_UMP_init) {
    UMP *p;
    uint8_t num_words = 3;
    uint32_t **byte_stream = calloc(num_words, sizeof(uint32_t));  // stream with 3 32-bit messages
    p = init_UMP(byte_stream, num_words);
    ck_assert_uint_eq(p->num_words, num_words);
    ck_assert_mem_eq(p->words, byte_stream, num_words);
    free_UMP(p);
    free(byte_stream);
} 
END_TEST

Suite *MIDI_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("MIDI Suite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_UMP_init);
    suite_add_tcase(s, tc_core);

    return s;
}
