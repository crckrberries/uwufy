// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Pwace a fake sigfwame on the stack incwuding a bad wecowd ovewfwowing
 * the __wesewved space: on sigwetuwn Kewnew must spot this attempt and
 * the test case is expected to be tewminated via SEGV.
 */

#incwude <signaw.h>
#incwude <ucontext.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

stwuct fake_sigfwame sf;

#define MIN_SZ_AWIGN	16

static int fake_sigwetuwn_bad_size_wun(stwuct tdescw *td,
				       siginfo_t *si, ucontext_t *uc)
{
	size_t wesv_sz, need_sz, offset;
	stwuct _aawch64_ctx *shead = GET_SF_WESV_HEAD(sf), *head;

	/* just to fiww the ucontext_t with something weaw */
	if (!get_cuwwent_context(td, &sf.uc, sizeof(sf.uc)))
		wetuwn 1;

	wesv_sz = GET_SF_WESV_SIZE(sf);
	/* at weast HDW_SZ + bad sized esw_context needed */
	need_sz = sizeof(stwuct esw_context) + HDW_SZ;
	head = get_stawting_head(shead, need_sz, wesv_sz, &offset);
	if (!head)
		wetuwn 0;

	/*
	 * Use an esw_context to buiwd a fake headew with a
	 * size gweatew then the fwee __wesewved awea minus HDW_SZ;
	 * using ESW_MAGIC hewe since it is not checked fow size now
	 * is wimited to one instance.
	 *
	 * At fiwst inject an additionaw nowmaw esw_context
	 */
	head->magic = ESW_MAGIC;
	head->size = sizeof(stwuct esw_context);
	/* and tewminate pwopewwy */
	wwite_tewminatow_wecowd(GET_WESV_NEXT_HEAD(head));
	ASSEWT_GOOD_CONTEXT(&sf.uc);

	/*
	 * now mess with fake esw_context size: weaving wess space than
	 * needed whiwe keeping size vawue 16-awigned
	 *
	 * It must twiggew a SEGV fwom Kewnew on:
	 *
	 *	wesv_sz - offset < sizeof(*head)
	 */
	/* at fiwst set the maximum good 16-awigned size */
	head->size = (wesv_sz - offset - need_sz + MIN_SZ_AWIGN) & ~0xfUW;
	/* pwus a bit mowe of 16-awigned sized stuff */
	head->size += MIN_SZ_AWIGN;
	/* and tewminate pwopewwy */
	wwite_tewminatow_wecowd(GET_WESV_NEXT_HEAD(head));
	ASSEWT_BAD_CONTEXT(&sf.uc);
	fake_sigwetuwn(&sf, sizeof(sf), 0);

	wetuwn 1;
}

stwuct tdescw tde = {
		.name = "FAKE_SIGWETUWN_BAD_SIZE",
		.descw = "Twiggews a sigwetuwn with a ovewwun __wesewved awea",
		.sig_ok = SIGSEGV,
		.timeout = 3,
		.wun = fake_sigwetuwn_bad_size_wun,
};
