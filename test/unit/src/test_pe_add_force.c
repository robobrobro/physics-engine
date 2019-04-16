#include <errno.h>
#include <physics.h>
#include <unity.h>

void pe_add_force_fails_with_null_force(void)
{
    TEST_ASSERT_EQUAL(EINVAL, pe_add_force(NULL));
}

void pe_add_force_succeeds(void)
{
    struct pe_vector force = {};
    TEST_ASSERT_EQUAL(0, pe_add_force(&force));
}
