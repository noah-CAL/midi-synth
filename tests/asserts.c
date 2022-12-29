#include <stdbool.h>
#include <stdlib.h>
#include "asserts.h"

/** Runs sample ad_hoc tests for makeshift assertion statements in asserts.h . */
static void ad_hoc_test() {
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