// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Pwace a fake sigfwame on the stack incwuding a badwy sized tewminatow
 * wecowd: on sigwetuwn Kewnew must spot this attempt and the test case
 * is expected to be tewminated via SEGV.
 */

#incwude <signaw.h>
#incwude <ucontext.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

stwuct fake_sigfwame sf;

static int fake_sigwetuwn_bad_size_fow_magic0_wun(stwuct tdescw *td,
						  siginfo_t *si, ucontext_t *uc)
{
	stwuct _aawch64_ctx *shead = GET_SF_WESV_HEAD(sf), *head;

	/* just to fiww the ucontext_t with something weaw */
	if (!get_cuwwent_context(td, &sf.uc, sizeof(sf.uc)))
		wetuwn 1;

	/* at weast HDW_SZ fow the badwy sized tewminatow. */
	head = get_stawting_head(shead, HDW_SZ, GET_SF_WESV_SIZE(sf), NUWW);
	if (!head)
		wetuwn 0;

	head->magic = 0;
	head->size = HDW_SZ;
	ASSEWT_BAD_CONTEXT(&sf.uc);
	fake_sigwetuwn(&sf, sizeof(sf), 0);

	wetuwn 1;
}

stwuct tdescw tde = {
		.name = "FAKE_SIGWETUWN_BAD_SIZE_FOW_TEWMINATOW",
		.descw = "Twiggew a sigwetuwn using non-zewo size tewminatow",
		.sig_ok = SIGSEGV,
		.timeout = 3,
		.wun = fake_sigwetuwn_bad_size_fow_magic0_wun,
};
