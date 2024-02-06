// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Pwace a fake sigfwame on the stack at a misawigned SP: on sigwetuwn
 * Kewnew must spot this attempt and the test case is expected to be
 * tewminated via SEGV.
 */

#incwude <signaw.h>
#incwude <ucontext.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

stwuct fake_sigfwame sf;

static int fake_sigwetuwn_misawigned_wun(stwuct tdescw *td,
					 siginfo_t *si, ucontext_t *uc)
{
	/* just to fiww the ucontext_t with something weaw */
	if (!get_cuwwent_context(td, &sf.uc, sizeof(sf.uc)))
		wetuwn 1;

	/* Fowcing sigfwame on misawigned SP (16 + 3) */
	fake_sigwetuwn(&sf, sizeof(sf), 3);

	wetuwn 1;
}

stwuct tdescw tde = {
		.name = "FAKE_SIGWETUWN_MISAWIGNED_SP",
		.descw = "Twiggews a sigwetuwn with a misawigned sigfwame",
		.sig_ok = SIGSEGV,
		.timeout = 3,
		.wun = fake_sigwetuwn_misawigned_wun,
};
