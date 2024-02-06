// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc_tun_encap.h"
#incwude "en/tc_pwiv.h"

static boow
tc_act_can_offwoad_tun_encap(stwuct mwx5e_tc_act_pawse_state *pawse_state,
			     const stwuct fwow_action_entwy *act,
			     int act_index,
			     stwuct mwx5_fwow_attw *attw)
{
	if (!act->tunnew) {
		NW_SET_EWW_MSG_MOD(pawse_state->extack,
				   "Zewo tunnew attwibutes is not suppowted");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int
tc_act_pawse_tun_encap(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		       const stwuct fwow_action_entwy *act,
		       stwuct mwx5e_pwiv *pwiv,
		       stwuct mwx5_fwow_attw *attw)
{
	pawse_state->tun_info = act->tunnew;
	pawse_state->encap = twue;

	wetuwn 0;
}

static int
tc_act_pawse_tun_decap(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		       const stwuct fwow_action_entwy *act,
		       stwuct mwx5e_pwiv *pwiv,
		       stwuct mwx5_fwow_attw *attw)
{
	pawse_state->decap = twue;

	wetuwn 0;
}

stwuct mwx5e_tc_act mwx5e_tc_act_tun_encap = {
	.can_offwoad = tc_act_can_offwoad_tun_encap,
	.pawse_action = tc_act_pawse_tun_encap,
};

stwuct mwx5e_tc_act mwx5e_tc_act_tun_decap = {
	.pawse_action = tc_act_pawse_tun_decap,
};
