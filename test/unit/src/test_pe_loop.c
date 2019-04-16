#include <errno.h>
#include <physics.h>
#include <signal.h>
#include <unity.h>
#include <unistd.h>

static void handle_alarm(int sig)
{
    (void) sig;
    TEST_ASSERT_EQUAL(0, pe_abort());
}

static void loop_cb(const struct pe_body *bodies, size_t body_count, void *arg)
{
    (void) bodies;
    (void) body_count;
    (void) arg;
}

void pe_loop_fails_without_init(void)
{
    TEST_ASSERT_EQUAL(EINVAL, pe_loop());
}

void pe_loop_succeeds(void)
{
    void *old_handler = signal(SIGALRM, handle_alarm);
    (void) alarm(1);

    if (TEST_PROTECT()) {
        TEST_ASSERT_EQUAL(0, pe_init(loop_cb, NULL));
        TEST_ASSERT_EQUAL(0, pe_loop());
    }

    (void) signal(SIGALRM, old_handler);
}
