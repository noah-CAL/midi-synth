/** Custom assertion module to provide unit-testing without any additional dependencies. 
ASSERTION MACROS:
ASSERT_TRUE(value)
ASSERT_FALSE(value)
ASSERT_EQ(a, b)
ASSERT_NEQ(a, b)
ASSERT_NULL(a)
ASSERT_NOT_NULL(a)
*/
#ifndef ASSERTS_H
#define ASSERTS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    char *name;
    void (*test_fn)();
} TestCase;

typedef struct {
    uint8_t num_tests;
    TestCase **tests;
} TestSuite;

typedef struct {
    uint8_t num_suites;
    TestSuite **suites;
} TestRunner;

/** Returns a TestCase object to add to a test suite. */
TestCase *create_test_case(char *name, void (*test_fn)());

/** Returns a TestSuite object. */
TestSuite *create_test_suite();

/** Returns a TestRunner object. */
TestRunner *create_test_runner();

/** Adds test case to TestSuite S. */
void add_test_case(TestSuite *s, TestCase *t);

/** Adds a test suite to TestRunner R. */
void add_test_suite(TestRunner *r, TestSuite *s);

// TODO: remove test_case / test_suite? CRUD operations?

/** Runs all test suites in TestRunner R. */
void run_tests(TestRunner *r);

/** Deallocates the memory space for all tests and suites in TestRunner R. */
void dealloc_tests(TestRunner *r);

#define PRINT_ERROR_MSG(msg) fprintf(stderr, "%s:%d: " msg "\n", __FILE__, __LINE__);

#define ASSERT_TRUE(value) \
if (!(value)) { \
    PRINT_ERROR_MSG("Expected true but received false"); \
}

#define ASSERT_FALSE(value) \
if ((value)) { \
    PRINT_ERROR_MSG("Expected false but received true"); \
}

#define ASSERT_EQ(a, b) \
if ((a) != (b)) { \
    PRINT_ERROR_MSG("Expected " #a " to equal " #b); \
}

#define ASSERT_NEQ(a, b) \
if ((a) == (b)) { \
    PRINT_ERROR_MSG("Expected " #a " to not equal " #b); \
}

#define ASSERT_NULL(p) \
if ((p) != 0x00) { \
    PRINT_ERROR_MSG("Expected " #p " to be null"); \
}

#define ASSERT_NOT_NULL(p) \
if ((p) == 0x00) { \
    PRINT_ERROR_MSG("Expected " #p " to not be null"); \
}

#endif