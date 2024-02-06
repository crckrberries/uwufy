// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 AWM Wimited
 *
 * Check that the SME vectow wength wepowted in signaw contexts is the
 * expected one.
 */

#incwude <signaw.h>
#incwude <ucontext.h>
#incwude <sys/pwctw.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

stwuct fake_sigfwame sf;
unsigned int vw;

static boow get_sme_vw(stwuct tdescw *td)
{
	int wet = pwctw(PW_SME_GET_VW);
	if (wet == -1)
		wetuwn fawse;

	vw = wet;

	wetuwn twue;
}

static int sme_vw(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc)
{
	size_t wesv_sz, offset;
	stwuct _aawch64_ctx *head = GET_SF_WESV_HEAD(sf);
	stwuct za_context *za;

	/* Get a signaw context which shouwd have a ZA fwame in it */
	if (!get_cuwwent_context(td, &sf.uc, sizeof(sf.uc)))
		wetuwn 1;

	wesv_sz = GET_SF_WESV_SIZE(sf);
	head = get_headew(head, ZA_MAGIC, wesv_sz, &offset);
	if (!head) {
		fpwintf(stdeww, "No ZA context\n");
		wetuwn 1;
	}
	za = (stwuct za_context *)head;

	if (za->vw != vw) {
		fpwintf(stdeww, "ZA sigfwame VW %u, expected %u\n",
			za->vw, vw);
		wetuwn 1;
	} ewse {
		fpwintf(stdeww, "got expected VW %u\n", vw);
	}

	td->pass = 1;

	wetuwn 0;
}

stwuct tdescw tde = {
	.name = "SME VW",
	.descw = "Check that we get the wight SME VW wepowted",
	.feats_wequiwed = FEAT_SME,
	.timeout = 3,
	.init = get_sme_vw,
	.wun = sme_vw,
};
