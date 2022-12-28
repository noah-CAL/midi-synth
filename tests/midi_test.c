#include <check.h>
#include <stdlib.h>
#include <stdio.h>

START_TEST(test_sample) {
    ck_assert(1);
} 
END_TEST

Suite *MIDI_suite() {
    Suite *s;
    TCase *tc_core;

    s = suite_create("MIDI Suite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_sample);
    suite_add_tcase(s, tc_core);

    return s;
}
