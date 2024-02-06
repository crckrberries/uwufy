// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc_pwiv.h"

static int
tc_act_pawse_ptype(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		   const stwuct fwow_action_entwy *act,
		   stwuct mwx5e_pwiv *pwiv,
		   stwuct mwx5_fwow_attw *attw)
{
	stwuct netwink_ext_ack *extack = pawse_state->extack;

	if (act->ptype != PACKET_HOST) {
		NW_SET_EWW_MSG_MOD(extack, "skbedit ptype is onwy suppowted with type host");
		wetuwn -EOPNOTSUPP;
	}

	pawse_state->ptype_host = twue;
	wetuwn 0;
}

stwuct mwx5e_tc_act mwx5e_tc_act_ptype = {
	.pawse_action = tc_act_pawse_ptype,
};
