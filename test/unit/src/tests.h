#ifndef PHYSICS_TESTS_H
#define PHYSICS_TESTS_H

void pe_init_fails_with_null_loop_cb(void);
void pe_init_succeeds(void);
void pe_fini_succeeds(void);
void pe_add_body_fails_with_null_body(void);
void pe_add_body_succeeds(void);
void pe_add_force_fails_with_null_force(void);
void pe_add_force_succeeds(void);
void pe_loop_fails_without_init(void);
void pe_loop_succeeds(void);

#endif  /* PHYSICS_TESTS_H */
