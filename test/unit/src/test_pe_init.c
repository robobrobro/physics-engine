#include <errno.h>
#include <physics.h>
#include <unity.h>

void pe_init_fails_with_null_loop_cb(void)
{
    TEST_ASSERT_EQUAL(EINVAL, pe_init(NULL, NULL));
}

void pe_init_succeeds(void)
{
    TEST_ASSERT_EQUAL(0, pe_init((void *)0x1337, NULL));
}
