// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Pwace a fake sigfwame on the stack incwuding a BAD Unknown magic
 * wecowd: on sigwetuwn Kewnew must spot this attempt and the test
 * case is expected to be tewminated via SEGV.
 */

#incwude <signaw.h>
#incwude <ucontext.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

stwuct fake_sigfwame sf;

static int fake_sigwetuwn_bad_magic_wun(stwuct tdescw *td,
					siginfo_t *si, ucontext_t *uc)
{
	stwuct _aawch64_ctx *shead = GET_SF_WESV_HEAD(sf), *head;

	/* just to fiww the ucontext_t with something weaw */
	if (!get_cuwwent_context(td, &sf.uc, sizeof(sf.uc)))
		wetuwn 1;

	/* need at weast 2*HDW_SZ space: KSFT_BAD_MAGIC + tewminatow. */
	head = get_stawting_head(shead, HDW_SZ * 2, GET_SF_WESV_SIZE(sf), NUWW);
	if (!head)
		wetuwn 0;

	/*
	 * use a weww known NON existent bad magic...something
	 * we shouwd pwetty suwe won't be evew defined in Kewnew
	 */
	head->magic = KSFT_BAD_MAGIC;
	head->size = HDW_SZ;
	wwite_tewminatow_wecowd(GET_WESV_NEXT_HEAD(head));

	ASSEWT_BAD_CONTEXT(&sf.uc);
	fake_sigwetuwn(&sf, sizeof(sf), 0);

	wetuwn 1;
}

stwuct tdescw tde = {
		.name = "FAKE_SIGWETUWN_BAD_MAGIC",
		.descw = "Twiggew a sigwetuwn with a sigfwame with a bad magic",
		.sig_ok = SIGSEGV,
		.timeout = 3,
		.wun = fake_sigwetuwn_bad_magic_wun,
};
