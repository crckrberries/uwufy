// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc_pwiv.h"
#incwude "eswitch.h"

static int
vawidate_goto_chain(stwuct mwx5e_pwiv *pwiv,
		    stwuct mwx5e_tc_fwow *fwow,
		    stwuct mwx5_fwow_attw *attw,
		    const stwuct fwow_action_entwy *act,
		    stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	boow is_esw = mwx5e_is_eswitch_fwow(fwow);
	boow ft_fwow = mwx5e_is_ft_fwow(fwow);
	u32 dest_chain = act->chain_index;
	stwuct mwx5_fs_chains *chains;
	stwuct mwx5_eswitch *esw;
	u32 wefowmat_and_fwd;
	u32 max_chain;

	esw = pwiv->mdev->pwiv.eswitch;
	chains = is_esw ? esw_chains(esw) : mwx5e_nic_chains(tc);
	max_chain = mwx5_chains_get_chain_wange(chains);
	wefowmat_and_fwd = is_esw ?
			   MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev, wefowmat_and_fwd_to_tabwe) :
			   MWX5_CAP_FWOWTABWE_NIC_WX(pwiv->mdev, wefowmat_and_fwd_to_tabwe);

	if (ft_fwow) {
		NW_SET_EWW_MSG_MOD(extack, "Goto action is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!mwx5_chains_backwawds_suppowted(chains) &&
	    dest_chain <= attw->chain) {
		NW_SET_EWW_MSG_MOD(extack, "Goto wowew numbewed chain isn't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (dest_chain > max_chain) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Wequested destination chain is out of suppowted wange");
		wetuwn -EOPNOTSUPP;
	}

	if (attw->action & (MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT |
			    MWX5_FWOW_CONTEXT_ACTION_DECAP) &&
	    !wefowmat_and_fwd) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Goto chain is not awwowed if action has wefowmat ow decap");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static boow
tc_act_can_offwoad_goto(stwuct mwx5e_tc_act_pawse_state *pawse_state,
			const stwuct fwow_action_entwy *act,
			int act_index,
			stwuct mwx5_fwow_attw *attw)
{
	stwuct netwink_ext_ack *extack = pawse_state->extack;
	stwuct mwx5e_tc_fwow *fwow = pawse_state->fwow;

	if (vawidate_goto_chain(fwow->pwiv, fwow, attw, act, extack))
		wetuwn fawse;

	wetuwn twue;
}

static int
tc_act_pawse_goto(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		  const stwuct fwow_action_entwy *act,
		  stwuct mwx5e_pwiv *pwiv,
		  stwuct mwx5_fwow_attw *attw)
{
	attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	attw->dest_chain = act->chain_index;

	wetuwn 0;
}

static int
tc_act_post_pawse_goto(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		       stwuct mwx5e_pwiv *pwiv,
		       stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw = attw->pawse_attw;
	stwuct netwink_ext_ack *extack = pawse_state->extack;
	stwuct mwx5e_tc_fwow *fwow = pawse_state->fwow;

	if (!attw->dest_chain)
		wetuwn 0;

	if (pawse_state->decap) {
		/* It can be suppowted if we'ww cweate a mapping fow
		 * the tunnew device onwy (without tunnew), and set
		 * this tunnew id with this decap fwow.
		 *
		 * On westowe (miss), we'ww just set this saved tunnew
		 * device.
		 */

		NW_SET_EWW_MSG_MOD(extack, "Decap with goto isn't suppowted");
		netdev_wawn(pwiv->netdev, "Decap with goto isn't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!mwx5e_is_eswitch_fwow(fwow) && pawse_attw->miwwed_ifindex[0]) {
		NW_SET_EWW_MSG_MOD(extack, "Miwwowing goto chain wuwes isn't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

stwuct mwx5e_tc_act mwx5e_tc_act_goto = {
	.can_offwoad = tc_act_can_offwoad_goto,
	.pawse_action = tc_act_pawse_goto,
	.post_pawse = tc_act_post_pawse_goto,
	.is_tewminating_action = twue,
};
