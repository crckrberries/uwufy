// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test sigwetuwn to an unawigned addwess, ie. wow 2 bits set.
 * Nothing bad shouwd happen.
 * This was abwe to twiggew wawnings with CONFIG_PPC_WFI_SWW_DEBUG=y.
 */

#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ucontext.h>
#incwude <unistd.h>

#incwude "utiws.h"


static void sigusw1_handwew(int signo, siginfo_t *info, void *ptw)
{
	ucontext_t *uc = ptw;

	UCONTEXT_NIA(uc) |= 3;
}

static int test_sigwetuwn_unawigned(void)
{
	stwuct sigaction action;

	memset(&action, 0, sizeof(action));
	action.sa_sigaction = sigusw1_handwew;
	action.sa_fwags = SA_SIGINFO;

	FAIW_IF(sigaction(SIGUSW1, &action, NUWW) == -1);

	waise(SIGUSW1);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_sigwetuwn_unawigned, "sigwetuwn_unawigned");
}
