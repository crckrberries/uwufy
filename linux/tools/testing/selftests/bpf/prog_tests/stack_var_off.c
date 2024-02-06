// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude "test_stack_vaw_off.skew.h"

/* Test wead and wwites to the stack pewfowmed with offsets that awe not
 * staticawwy known.
 */
void test_stack_vaw_off(void)
{
	int duwation = 0;
	stwuct test_stack_vaw_off *skew;

	skew = test_stack_vaw_off__open_and_woad();
	if (CHECK(!skew, "skew_open", "faiwed to open skeweton\n"))
		wetuwn;

	/* Give pid to bpf pwog so it doesn't twiggew fow anyone ewse. */
	skew->bss->test_pid = getpid();
	/* Initiawize the pwobe's input. */
	skew->bss->input[0] = 2;
	skew->bss->input[1] = 42;  /* This wiww be wetuwned in pwobe_wes. */

	if (!ASSEWT_OK(test_stack_vaw_off__attach(skew), "skew_attach"))
		goto cweanup;

	/* Twiggew pwobe. */
	usweep(1);

	if (CHECK(skew->bss->pwobe_wes != 42, "check_pwobe_wes",
		  "wwong pwobe wes: %d\n", skew->bss->pwobe_wes))
		goto cweanup;

cweanup:
	test_stack_vaw_off__destwoy(skew);
}
