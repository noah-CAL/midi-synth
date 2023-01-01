#include <stdbool.h>
#include <stdlib.h>
#include "asserts.h"

/** Returns a TestCase object to add to a test suite. */
TestCase *create_test_case(char *name, void (*test_fn)()) {
    // TODO: create free() methods to prevent memory leaks
    TestCase *t = malloc(sizeof(TestCase));
    if (t == NULL) {
        PRINT_ERROR_MSG("TestCase memory allocation failed");
    }
    t->name = name;
    t->test_fn = test_fn;
    return t;
}

/** Returns a TestSuite object. */
TestSuite *create_test_suite() {
    TestSuite *s = malloc(sizeof(TestSuite));
    if (s == NULL) {
        PRINT_ERROR_MSG("TestSuite memory allocation failed");
    }
    s->num_tests = 0;
    s->tests = NULL;
    return s;
}

/** Returns a TestRunner object. */
TestRunner *create_test_runner() {
    TestRunner *r = malloc(sizeof(TestRunner));
    if (r == NULL) {
        PRINT_ERROR_MSG("TestRunner memory allocation failed");
    }
    r->num_suites = 0;
    return r;
}

/** Adds test case to TestSuite S. */
void add_test_case(TestSuite *s, TestCase *t) {
    uint8_t curr_tests = s->num_tests;
    s->tests = realloc(s->tests, (curr_tests + 1) * sizeof(TestCase *));
    if (s->tests == NULL) {
        PRINT_ERROR_MSG("Memory allocation failed");
    }
    *(s->tests + curr_tests) = t;
    s->num_tests += 1;
}

/** Adds a test suite to TestRunner R. */
void add_test_suite(TestRunner *r, TestSuite *s) {
    uint8_t curr_suites = r->num_suites;
    r->suites = realloc(r->suites, (curr_suites + 1) * sizeof(TestSuite *));
    if (&(r->suites) == NULL) {
        PRINT_ERROR_MSG("Memory allocation failed");
    }
    r->suites[curr_suites] = s;
    r->num_suites += 1;
}

/** Runs all test suites in TestRunner R. */
void run_tests(TestRunner *r) {
    for (int i = 0; i < r->num_suites; i += 1) {
        TestSuite *s = r->suites[i];
        for (int j = 0; j < s->num_tests; j += 1) {
            TestCase *t = s->tests[j];
            t->test_fn();
        }
    }
}

/** Deallocates the memory space for all tests and suites in TestRunner R. */
void dealloc_tests(TestRunner *r) {
    for (int i = 0; i < r->num_suites; i += 1) {
        TestSuite *s = r->suites[i];
        for (int i = 0; i < s->num_tests; i += 1) {
            free(s->tests[i]);
        }
        free(s->tests);
        free(s);
    }
    free(r->suites);
    free(r);
}

/** Runs sample ad_hoc tests for makeshift assertion statements in asserts.h .
void ad_hoc_test() {
    ASSERT_TRUE(1);
    ASSERT_TRUE(0);  // fail

    ASSERT_FALSE(0);
    ASSERT_FALSE(1);  // fail

    ASSERT_EQ(1, 1);
    ASSERT_EQ(1, 2);  // fail
    ASSERT_EQ("a", "a");
    ASSERT_EQ("a", "b");  // fail

    ASSERT_NEQ(1, 2);
    ASSERT_NEQ(1, 1);  // fail
    ASSERT_NEQ("a", "b");
    ASSERT_NEQ("a", "a");  // fail

    int *p = malloc(4);
    ASSERT_NULL(0x00);
    ASSERT_NULL(p);  // fail

    ASSERT_NOT_NULL(p);
    ASSERT_NOT_NULL(0x00);  // fail
    free(p);
}
*/

/* Example implementation of the test runner.
static void midi_basic() {
    ASSERT_EQ(2, 3);
}

static void midi_advanced() {
    ASSERT_NULL(0x01);
}

static void IO_basic() {
    ASSERT_NEQ("4", "4");
}

int main_fn() {
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
*/