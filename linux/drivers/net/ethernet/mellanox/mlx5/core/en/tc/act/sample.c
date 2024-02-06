// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude <net/psampwe.h>
#incwude "act.h"
#incwude "en/tc_pwiv.h"
#incwude "en/tc/act/sampwe.h"

static int
tc_act_pawse_sampwe(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		    const stwuct fwow_action_entwy *act,
		    stwuct mwx5e_pwiv *pwiv,
		    stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_sampwe_attw *sampwe_attw = &attw->sampwe_attw;

	sampwe_attw->wate = act->sampwe.wate;
	sampwe_attw->gwoup_num = act->sampwe.psampwe_gwoup->gwoup_num;

	if (act->sampwe.twuncate)
		sampwe_attw->twunc_size = act->sampwe.twunc_size;

	attw->fwags |= MWX5_ATTW_FWAG_SAMPWE;
	fwow_fwag_set(pawse_state->fwow, SAMPWE);

	wetuwn 0;
}

boow
mwx5e_tc_act_sampwe_is_muwti_tabwe(stwuct mwx5_cowe_dev *mdev,
				   stwuct mwx5_fwow_attw *attw)
{
	if (MWX5_CAP_GEN(mdev, weg_c_pwesewve) ||
	    attw->action & MWX5_FWOW_CONTEXT_ACTION_DECAP)
		wetuwn twue;

	wetuwn fawse;
}

static boow
tc_act_is_muwti_tabwe_act_sampwe(stwuct mwx5e_pwiv *pwiv,
				 const stwuct fwow_action_entwy *act,
				 stwuct mwx5_fwow_attw *attw)
{
	wetuwn mwx5e_tc_act_sampwe_is_muwti_tabwe(pwiv->mdev, attw);
}

stwuct mwx5e_tc_act mwx5e_tc_act_sampwe = {
	.pawse_action = tc_act_pawse_sampwe,
	.is_muwti_tabwe_act = tc_act_is_muwti_tabwe_act_sampwe,
};
