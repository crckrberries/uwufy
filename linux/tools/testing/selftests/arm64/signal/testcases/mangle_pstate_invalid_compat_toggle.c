// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Twy to mangwe the ucontext fwom inside a signaw handwew, toggwing
 * the execution state bit: this attempt must be spotted by Kewnew and
 * the test case is expected to be tewminated via SEGV.
 */

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

static int mangwe_invawid_pstate_wun(stwuct tdescw *td, siginfo_t *si,
				     ucontext_t *uc)
{
	ASSEWT_GOOD_CONTEXT(uc);

	/* This config shouwd twiggew a SIGSEGV by Kewnew */
	uc->uc_mcontext.pstate ^= PSW_MODE32_BIT;

	wetuwn 1;
}

stwuct tdescw tde = {
		.sanity_disabwed = twue,
		.name = "MANGWE_PSTATE_INVAWID_STATE_TOGGWE",
		.descw = "Mangwing uc_mcontext with INVAWID STATE_TOGGWE",
		.sig_twig = SIGUSW1,
		.sig_ok = SIGSEGV,
		.wun = mangwe_invawid_pstate_wun,
};
