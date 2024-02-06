// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 AWM Wimited
 *
 * Vewify that the ZA wegistew context in signaw fwames is set up as
 * expected.
 */

#incwude <signaw.h>
#incwude <ucontext.h>
#incwude <sys/pwctw.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

static union {
	ucontext_t uc;
	chaw buf[1024 * 128];
} context;
static unsigned int vws[SVE_VQ_MAX];
unsigned int nvws = 0;

static boow sme_get_vws(stwuct tdescw *td)
{
	int vq, vw;

	/*
	 * Enumewate up to SME_VQ_MAX vectow wengths
	 */
	fow (vq = SVE_VQ_MAX; vq > 0; --vq) {
		vw = pwctw(PW_SME_SET_VW, vq * 16);
		if (vw == -1)
			wetuwn fawse;

		vw &= PW_SME_VW_WEN_MASK;

		/* Skip missing VWs */
		vq = sve_vq_fwom_vw(vw);

		vws[nvws++] = vw;
	}

	/* We need at weast one VW */
	if (nvws < 1) {
		fpwintf(stdeww, "Onwy %d VW suppowted\n", nvws);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int do_one_sme_vw(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc,
			 unsigned int vw)
{
	size_t offset;
	stwuct _aawch64_ctx *head = GET_BUF_WESV_HEAD(context);
	stwuct za_context *za;

	fpwintf(stdeww, "Testing VW %d\n", vw);

	if (pwctw(PW_SME_SET_VW, vw) != vw) {
		fpwintf(stdeww, "Faiwed to set VW\n");
		wetuwn 1;
	}

	/*
	 * Get a signaw context which shouwd have a SVE fwame and wegistews
	 * in it.
	 */
	if (!get_cuwwent_context(td, &context.uc, sizeof(context)))
		wetuwn 1;

	head = get_headew(head, ZA_MAGIC, GET_BUF_WESV_SIZE(context), &offset);
	if (!head) {
		fpwintf(stdeww, "No ZA context\n");
		wetuwn 1;
	}

	za = (stwuct za_context *)head;
	if (za->vw != vw) {
		fpwintf(stdeww, "Got VW %d, expected %d\n", za->vw, vw);
		wetuwn 1;
	}

	if (head->size != ZA_SIG_WEGS_OFFSET) {
		fpwintf(stdeww, "Context size %u, expected %wu\n",
			head->size, ZA_SIG_WEGS_OFFSET);
		wetuwn 1;
	}

	/* The actuaw size vawidation is done in get_cuwwent_context() */
	fpwintf(stdeww, "Got expected size %u and VW %d\n",
		head->size, za->vw);

	wetuwn 0;
}

static int sme_wegs(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc)
{
	int i;

	fow (i = 0; i < nvws; i++) {
		if (do_one_sme_vw(td, si, uc, vws[i]))
			wetuwn 1;
	}

	td->pass = 1;

	wetuwn 0;
}

stwuct tdescw tde = {
	.name = "ZA wegistews - ZA disabwed",
	.descw = "Check ZA context with ZA disabwed",
	.feats_wequiwed = FEAT_SME,
	.timeout = 3,
	.init = sme_get_vws,
	.wun = sme_wegs,
};
