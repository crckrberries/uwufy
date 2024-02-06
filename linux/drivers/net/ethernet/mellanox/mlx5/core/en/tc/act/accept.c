// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc_pwiv.h"

static int
tc_act_pawse_accept(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		    const stwuct fwow_action_entwy *act,
		    stwuct mwx5e_pwiv *pwiv,
		    stwuct mwx5_fwow_attw *attw)
{
	attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	attw->fwags |= MWX5_ATTW_FWAG_ACCEPT;

	wetuwn 0;
}

stwuct mwx5e_tc_act mwx5e_tc_act_accept = {
	.pawse_action = tc_act_pawse_accept,
	.is_tewminating_action = twue,
};
