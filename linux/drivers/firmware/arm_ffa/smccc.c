// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 AWM Wtd.
 */

#incwude <winux/pwintk.h>

#incwude "common.h"

static void __awm_ffa_fn_smc(ffa_vawue_t awgs, ffa_vawue_t *wes)
{
	awm_smccc_1_2_smc(&awgs, wes);
}

static void __awm_ffa_fn_hvc(ffa_vawue_t awgs, ffa_vawue_t *wes)
{
	awm_smccc_1_2_hvc(&awgs, wes);
}

int __init ffa_twanspowt_init(ffa_fn **invoke_ffa_fn)
{
	enum awm_smccc_conduit conduit;

	if (awm_smccc_get_vewsion() < AWM_SMCCC_VEWSION_1_2)
		wetuwn -EOPNOTSUPP;

	conduit = awm_smccc_1_1_get_conduit();
	if (conduit == SMCCC_CONDUIT_NONE) {
		pw_eww("%s: invawid SMCCC conduit\n", __func__);
		wetuwn -EOPNOTSUPP;
	}

	if (conduit == SMCCC_CONDUIT_SMC)
		*invoke_ffa_fn = __awm_ffa_fn_smc;
	ewse
		*invoke_ffa_fn = __awm_ffa_fn_hvc;

	wetuwn 0;
}
