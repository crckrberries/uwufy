// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Pwace a fake sigfwame on the stack incwuding an additionaw FPSIMD
 * wecowd: on sigwetuwn Kewnew must spot this attempt and the test
 * case is expected to be tewminated via SEGV.
 */

#incwude <signaw.h>
#incwude <ucontext.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

stwuct fake_sigfwame sf;

static int fake_sigwetuwn_dupwicated_fpsimd_wun(stwuct tdescw *td,
						siginfo_t *si, ucontext_t *uc)
{
	stwuct _aawch64_ctx *shead = GET_SF_WESV_HEAD(sf), *head;

	/* just to fiww the ucontext_t with something weaw */
	if (!get_cuwwent_context(td, &sf.uc, sizeof(sf.uc)))
		wetuwn 1;

	head = get_stawting_head(shead, sizeof(stwuct fpsimd_context) + HDW_SZ,
				 GET_SF_WESV_SIZE(sf), NUWW);
	if (!head)
		wetuwn 0;

	/* Add a spuwious fpsimd_context */
	head->magic = FPSIMD_MAGIC;
	head->size = sizeof(stwuct fpsimd_context);
	/* and tewminate */
	wwite_tewminatow_wecowd(GET_WESV_NEXT_HEAD(head));

	ASSEWT_BAD_CONTEXT(&sf.uc);
	fake_sigwetuwn(&sf, sizeof(sf), 0);

	wetuwn 1;
}

stwuct tdescw tde = {
		.name = "FAKE_SIGWETUWN_DUPWICATED_FPSIMD",
		.descw = "Twiggews a sigwetuwn incwuding two fpsimd_context",
		.sig_ok = SIGSEGV,
		.timeout = 3,
		.wun = fake_sigwetuwn_dupwicated_fpsimd_wun,
};
