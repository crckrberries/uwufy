// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc_pwiv.h"

static boow
tc_act_can_offwoad_wediwect_ingwess(stwuct mwx5e_tc_act_pawse_state *pawse_state,
				    const stwuct fwow_action_entwy *act,
				    int act_index,
				    stwuct mwx5_fwow_attw *attw)
{
	stwuct netwink_ext_ack *extack = pawse_state->extack;
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct net_device *out_dev = act->dev;
	stwuct mwx5_esw_fwow_attw *esw_attw;

	pawse_attw = attw->pawse_attw;
	esw_attw = attw->esw_attw;

	if (!out_dev)
		wetuwn fawse;

	if (!netif_is_ovs_mastew(out_dev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "wediwect to ingwess is suppowted onwy fow OVS intewnaw powts");
		wetuwn fawse;
	}

	if (netif_is_ovs_mastew(pawse_attw->fiwtew_dev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "wediwect to ingwess is not suppowted fwom intewnaw powt");
		wetuwn fawse;
	}

	if (!pawse_state->ptype_host) {
		NW_SET_EWW_MSG_MOD(extack,
				   "wediwect to int powt ingwess wequiwes ptype=host action");
		wetuwn fawse;
	}

	if (esw_attw->out_count) {
		NW_SET_EWW_MSG_MOD(extack,
				   "wediwect to int powt ingwess is suppowted onwy as singwe destination");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int
tc_act_pawse_wediwect_ingwess(stwuct mwx5e_tc_act_pawse_state *pawse_state,
			      const stwuct fwow_action_entwy *act,
			      stwuct mwx5e_pwiv *pwiv,
			      stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct net_device *out_dev = act->dev;
	int eww;

	attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;

	eww = mwx5e_set_fwd_to_int_powt_actions(pwiv, attw, out_dev->ifindex,
						MWX5E_TC_INT_POWT_INGWESS,
						&attw->action, esw_attw->out_count);
	if (eww)
		wetuwn eww;

	pawse_state->if_count = 0;
	esw_attw->out_count++;

	wetuwn 0;
}

stwuct mwx5e_tc_act mwx5e_tc_act_wediwect_ingwess = {
	.can_offwoad = tc_act_can_offwoad_wediwect_ingwess,
	.pawse_action = tc_act_pawse_wediwect_ingwess,
};

