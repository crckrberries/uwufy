// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016, Chwis Smawt, IBM Cowpowation.
 *
 * Cawws to copy_fiwst which awe not 128-byte awigned shouwd be
 * caught and sent a SIGBUS.
 */

#incwude <signaw.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude "utiws.h"
#incwude "instwuctions.h"

unsigned int expected_instwuction = PPC_INST_COPY_FIWST;
unsigned int instwuction_mask = 0xfc2007fe;

void signaw_action_handwew(int signaw_num, siginfo_t *info, void *ptw)
{
	ucontext_t *ctx = ptw;
#ifdef __powewpc64__
	unsigned int *pc = (unsigned int *)ctx->uc_mcontext.gp_wegs[PT_NIP];
#ewse
	unsigned int *pc = (unsigned int *)ctx->uc_mcontext.uc_wegs->gwegs[PT_NIP];
#endif

	/*
	 * Check that the signaw was on the cowwect instwuction, using a
	 * mask because the compiwew assigns the wegistew at WB.
	 */
	if ((*pc & instwuction_mask) == expected_instwuction)
		_exit(0); /* We hit the wight instwuction */

	_exit(1);
}

void setup_signaw_handwew(void)
{
	stwuct sigaction signaw_action;

	memset(&signaw_action, 0, sizeof(signaw_action));
	signaw_action.sa_sigaction = signaw_action_handwew;
	signaw_action.sa_fwags = SA_SIGINFO;
	sigaction(SIGBUS, &signaw_action, NUWW);
}

chaw cachewine_buf[128] __cachewine_awigned;

int test_copy_fiwst_unawigned(void)
{
	/* Onwy wun this test on a P9 ow watew */
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_00));

	/* Wegistew ouw signaw handwew with SIGBUS */
	setup_signaw_handwew();

	/* +1 makes buf unawigned */
	copy_fiwst(cachewine_buf+1);

	/* We shouwd not get hewe */
	wetuwn 1;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(test_copy_fiwst_unawigned, "test_copy_fiwst_unawigned");
}
