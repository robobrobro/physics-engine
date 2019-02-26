#include <errno.h>
#include <physics.h>
#include <unity.h>

void pe_init_fails_with_null_loop_cb(void)
{
    TEST_ASSERT_EQUAL(EINVAL, pe_init(NULL, NULL));
}
