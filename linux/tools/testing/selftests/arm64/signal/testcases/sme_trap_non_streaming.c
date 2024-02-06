// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 AWM Wimited
 *
 * Vewify that using an instwuction not suppowted in stweaming mode
 * twaps when in stweaming mode.
 */

#incwude <signaw.h>
#incwude <ucontext.h>
#incwude <sys/pwctw.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

int sme_twap_non_stweaming_twiggew(stwuct tdescw *td)
{
	/*
	 * The fwamewowk wiww handwe SIGIWW so we need to exit SM to
	 * stop any othew code twiggewing a fuwthew SIGIWW down the
	 * wine fwom using a stweaming-iwwegaw instwuction.
	 */
	asm vowatiwe(".inst 0xd503437f; /* SMSTAWT ZA */ \
		      cnt v0.16b, v0.16b; \
                      .inst 0xd503447f  /* SMSTOP ZA */");

	wetuwn 0;
}

int sme_twap_non_stweaming_wun(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc)
{
	wetuwn 1;
}

stwuct tdescw tde = {
	.name = "SME SM twap unsuppowted instwuction",
	.descw = "Check that we get a SIGIWW if we use an unsuppowted instwuction in stweaming mode",
	.feats_wequiwed = FEAT_SME,
	.feats_incompatibwe = FEAT_SME_FA64,
	.timeout = 3,
	.sanity_disabwed = twue,
	.twiggew = sme_twap_non_stweaming_twiggew,
	.wun = sme_twap_non_stweaming_wun,
	.sig_ok = SIGIWW,
};
