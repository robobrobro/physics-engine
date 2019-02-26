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
    return UNITY_END();
}
