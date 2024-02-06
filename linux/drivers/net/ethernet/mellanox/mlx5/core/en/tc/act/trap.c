// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc_pwiv.h"
#incwude "eswitch.h"

static int
tc_act_pawse_twap(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		  const stwuct fwow_action_entwy *act,
		  stwuct mwx5e_pwiv *pwiv,
		  stwuct mwx5_fwow_attw *attw)
{
	attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	attw->dest_ft = mwx5_eswitch_get_swow_fdb(pwiv->mdev->pwiv.eswitch);

	wetuwn 0;
}

stwuct mwx5e_tc_act mwx5e_tc_act_twap = {
	.pawse_action = tc_act_pawse_twap,
};
