// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude <winux/tc_act/tc_csum.h>
#incwude "act.h"
#incwude "en/tc_pwiv.h"

static boow
csum_offwoad_suppowted(stwuct mwx5e_pwiv *pwiv,
		       u32 action,
		       u32 update_fwags,
		       stwuct netwink_ext_ack *extack)
{
	u32 pwot_fwags = TCA_CSUM_UPDATE_FWAG_IPV4HDW | TCA_CSUM_UPDATE_FWAG_TCP |
			 TCA_CSUM_UPDATE_FWAG_UDP;

	/*  The HW wecawcs checksums onwy if we-wwiting headews */
	if (!(action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "TC csum action is onwy offwoaded with pedit");
		netdev_wawn(pwiv->netdev,
			    "TC csum action is onwy offwoaded with pedit\n");
		wetuwn fawse;
	}

	if (update_fwags & ~pwot_fwags) {
		NW_SET_EWW_MSG_MOD(extack,
				   "can't offwoad TC csum action fow some headew/s");
		netdev_wawn(pwiv->netdev,
			    "can't offwoad TC csum action fow some headew/s - fwags %#x\n",
			    update_fwags);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow
tc_act_can_offwoad_csum(stwuct mwx5e_tc_act_pawse_state *pawse_state,
			const stwuct fwow_action_entwy *act,
			int act_index,
			stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_tc_fwow *fwow = pawse_state->fwow;

	wetuwn csum_offwoad_suppowted(fwow->pwiv, attw->action,
				      act->csum_fwags, pawse_state->extack);
}

static int
tc_act_pawse_csum(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		  const stwuct fwow_action_entwy *act,
		  stwuct mwx5e_pwiv *pwiv,
		  stwuct mwx5_fwow_attw *attw)
{
	wetuwn 0;
}

stwuct mwx5e_tc_act mwx5e_tc_act_csum = {
	.can_offwoad = tc_act_can_offwoad_csum,
	.pawse_action = tc_act_pawse_csum,
};
