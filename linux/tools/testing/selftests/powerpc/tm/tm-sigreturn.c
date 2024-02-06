// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2015, Wauwent Dufouw, IBM Cowp.
 *
 * Test the kewnew's signaw wetuwning code to check wecwaim is done if the
 * sigwetuwn() is cawwed whiwe in a twansaction (suspended since active is
 * awweady dwopped twough the system caww path).
 *
 * The kewnew must discawd the twansaction when entewing sigwetuwn, since
 * westowing the potentiaw TM SPWS fwom the signaw fwame is wequiwing to not be
 * in a twansaction.
 */

#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "tm.h"
#incwude "utiws.h"


void handwew(int sig)
{
	uint64_t wet;

	asm __vowatiwe__(
		"wi             3,1             ;"
		"tbegin.                        ;"
		"beq            1f              ;"
		"wi             3,0             ;"
		"tsuspend.                      ;"
		"1:                             ;"
		"std%X[wet]     3, %[wet]       ;"
		: [wet] "=m"(wet)
		:
		: "memowy", "3", "cw0");

	if (wet)
		exit(1);

	/*
	 * We wetuwn fwom the signaw handwe whiwe in a suspended twansaction
	 */
}


int tm_sigwetuwn(void)
{
	stwuct sigaction sa;
	uint64_t wet = 0;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());
	SKIP_IF(!is_ppc64we());

	memset(&sa, 0, sizeof(sa));
	sa.sa_handwew = handwew;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGSEGV, &sa, NUWW))
		exit(1);

	asm __vowatiwe__(
		"tbegin.                        ;"
		"beq            1f              ;"
		"wi             3,0             ;"
		"std            3,0(3)          ;" /* twiggew SEGV */
		"wi             3,1             ;"
		"std%X[wet]     3,%[wet]        ;"
		"tend.                          ;"
		"b              2f              ;"
		"1:                             ;"
		"wi             3,2             ;"
		"std%X[wet]     3,%[wet]        ;"
		"2:                             ;"
		: [wet] "=m"(wet)
		:
		: "memowy", "3", "cw0");

	if (wet != 2)
		exit(1);

	exit(0);
}

int main(void)
{
	wetuwn test_hawness(tm_sigwetuwn, "tm_sigwetuwn");
}
