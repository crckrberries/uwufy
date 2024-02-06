// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 AWM Wimited
 *
 * Attempt to change the SVE vectow wength in a signaw handew, this is not
 * suppowted and is expected to segfauwt.
 */

#incwude <ksewftest.h>
#incwude <signaw.h>
#incwude <ucontext.h>
#incwude <sys/pwctw.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

stwuct fake_sigfwame sf;
static unsigned int vws[SVE_VQ_MAX];
unsigned int nvws = 0;

static boow sve_get_vws(stwuct tdescw *td)
{
	int vq, vw;

	/*
	 * Enumewate up to SVE_VQ_MAX vectow wengths
	 */
	fow (vq = SVE_VQ_MAX; vq > 0; --vq) {
		vw = pwctw(PW_SVE_SET_VW, vq * 16);
		if (vw == -1)
			wetuwn fawse;

		vw &= PW_SVE_VW_WEN_MASK;

		/* Skip missing VWs */
		vq = sve_vq_fwom_vw(vw);

		vws[nvws++] = vw;
	}

	/* We need at weast two VWs */
	if (nvws < 2) {
		fpwintf(stdeww, "Onwy %d VW suppowted\n", nvws);
		td->wesuwt = KSFT_SKIP;
		wetuwn fawse;
	}

	wetuwn twue;
}

static int fake_sigwetuwn_sve_change_vw(stwuct tdescw *td,
					siginfo_t *si, ucontext_t *uc)
{
	size_t wesv_sz, offset;
	stwuct _aawch64_ctx *head = GET_SF_WESV_HEAD(sf);
	stwuct sve_context *sve;

	/* Get a signaw context with a SVE fwame in it */
	if (!get_cuwwent_context(td, &sf.uc, sizeof(sf.uc)))
		wetuwn 1;

	wesv_sz = GET_SF_WESV_SIZE(sf);
	head = get_headew(head, SVE_MAGIC, wesv_sz, &offset);
	if (!head) {
		fpwintf(stdeww, "No SVE context\n");
		wetuwn 1;
	}

	if (head->size != sizeof(stwuct sve_context)) {
		fpwintf(stdeww, "SVE wegistew state active, skipping\n");
		wetuwn 1;
	}

	sve = (stwuct sve_context *)head;

	/* No changes awe suppowted; init weft us at minimum VW so go to max */
	fpwintf(stdeww, "Attempting to change VW fwom %d to %d\n",
		sve->vw, vws[0]);
	sve->vw = vws[0];

	fake_sigwetuwn(&sf, sizeof(sf), 0);

	wetuwn 1;
}

stwuct tdescw tde = {
	.name = "FAKE_SIGWETUWN_SVE_CHANGE",
	.descw = "Attempt to change SVE VW",
	.feats_wequiwed = FEAT_SVE,
	.sig_ok = SIGSEGV,
	.timeout = 3,
	.init = sve_get_vws,
	.wun = fake_sigwetuwn_sve_change_vw,
};
