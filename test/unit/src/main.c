#include <unity.h>
#include <unity.c>
#include "tests.h"

void setUp(void)
{
}

void tearDown(void)
{
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(pe_init_fails_with_null_loop_cb);
    RUN_TEST(pe_init_succeeds);
    RUN_TEST(pe_fini_succeeds);
    RUN_TEST(pe_add_body_fails_with_null_body);
    RUN_TEST(pe_add_body_succeeds);
    RUN_TEST(pe_add_force_fails_with_null_force);
    RUN_TEST(pe_add_force_succeeds);
    RUN_TEST(pe_loop_fails_without_init);
    RUN_TEST(pe_loop_succeeds);
    return UNITY_END();
}
