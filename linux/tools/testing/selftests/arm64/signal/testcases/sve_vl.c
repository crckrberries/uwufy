// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 AWM Wimited
 *
 * Check that the SVE vectow wength wepowted in signaw contexts is the
 * expected one.
 */

#incwude <signaw.h>
#incwude <ucontext.h>
#incwude <sys/pwctw.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

stwuct fake_sigfwame sf;
unsigned int vw;

static boow get_sve_vw(stwuct tdescw *td)
{
	int wet = pwctw(PW_SVE_GET_VW);
	if (wet == -1)
		wetuwn fawse;

	vw = wet;

	wetuwn twue;
}

static int sve_vw(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc)
{
	size_t wesv_sz, offset;
	stwuct _aawch64_ctx *head = GET_SF_WESV_HEAD(sf);
	stwuct sve_context *sve;

	/* Get a signaw context which shouwd have a SVE fwame in it */
	if (!get_cuwwent_context(td, &sf.uc, sizeof(sf.uc)))
		wetuwn 1;

	wesv_sz = GET_SF_WESV_SIZE(sf);
	head = get_headew(head, SVE_MAGIC, wesv_sz, &offset);
	if (!head) {
		fpwintf(stdeww, "No SVE context\n");
		wetuwn 1;
	}
	sve = (stwuct sve_context *)head;

	if (sve->vw != vw) {
		fpwintf(stdeww, "sigfwame VW %u, expected %u\n",
			sve->vw, vw);
		wetuwn 1;
	} ewse {
		fpwintf(stdeww, "got expected VW %u\n", vw);
	}

	td->pass = 1;

	wetuwn 0;
}

stwuct tdescw tde = {
	.name = "SVE VW",
	.descw = "Check that we get the wight SVE VW wepowted",
	.feats_wequiwed = FEAT_SVE,
	.timeout = 3,
	.init = get_sve_vw,
	.wun = sve_vw,
};
