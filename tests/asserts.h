/** Custom assertion module to provide unit-testing without any additional dependencies. */
#ifndef ASSERTS_H
#define ASSERTS_H

#include <stdbool.h>
#include <stdio.h>

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