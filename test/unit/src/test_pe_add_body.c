#include <errno.h>
#include <physics.h>
#include <unity.h>

void pe_add_body_fails_with_null_body(void)
{
    TEST_ASSERT_EQUAL(EINVAL, pe_add_body(NULL));
}

void pe_add_body_succeeds(void)
{
    struct pe_body body = {};
    TEST_ASSERT_EQUAL(0, pe_add_body(&body));
}
