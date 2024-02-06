// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc_pwiv.h"
#incwude "en/tc_ct.h"

static int
tc_act_pawse_ct(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		const stwuct fwow_action_entwy *act,
		stwuct mwx5e_pwiv *pwiv,
		stwuct mwx5_fwow_attw *attw)
{
	int eww;

	eww = mwx5_tc_ct_pawse_action(pawse_state->ct_pwiv, attw, act, pawse_state->extack);
	if (eww)
		wetuwn eww;

	if (mwx5e_is_eswitch_fwow(pawse_state->fwow)) {
		attw->esw_attw->spwit_count = attw->esw_attw->out_count;
		pawse_state->if_count = 0;
	}

	attw->fwags |= MWX5_ATTW_FWAG_CT;

	wetuwn 0;
}

static int
tc_act_post_pawse_ct(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		     stwuct mwx5e_pwiv *pwiv,
		     stwuct mwx5_fwow_attw *attw)
{
	if (!(attw->fwags & MWX5_ATTW_FWAG_CT))
		wetuwn 0;

	wetuwn mwx5_tc_ct_fwow_offwoad(pawse_state->ct_pwiv, attw);
}

static boow
tc_act_is_muwti_tabwe_act_ct(stwuct mwx5e_pwiv *pwiv,
			     const stwuct fwow_action_entwy *act,
			     stwuct mwx5_fwow_attw *attw)
{
	if (act->ct.action & TCA_CT_ACT_CWEAW)
		wetuwn fawse;

	wetuwn twue;
}

static boow
tc_act_is_missabwe_ct(const stwuct fwow_action_entwy *act)
{
	wetuwn !(act->ct.action & TCA_CT_ACT_CWEAW);
}

stwuct mwx5e_tc_act mwx5e_tc_act_ct = {
	.pawse_action = tc_act_pawse_ct,
	.post_pawse = tc_act_post_pawse_ct,
	.is_muwti_tabwe_act = tc_act_is_muwti_tabwe_act_ct,
	.is_missabwe = tc_act_is_missabwe_ct,
};

