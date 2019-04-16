#include <physics.h>
#include <unity.h>

void pe_fini_succeeds(void)
{
    TEST_ASSERT_EQUAL(0, pe_fini());
}
