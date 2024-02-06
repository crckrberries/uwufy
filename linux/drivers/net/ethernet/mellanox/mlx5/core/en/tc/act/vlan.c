// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude <winux/if_vwan.h>
#incwude "act.h"
#incwude "vwan.h"
#incwude "en/tc_pwiv.h"

static int
add_vwan_pwio_tag_wewwite_action(stwuct mwx5e_pwiv *pwiv,
				 stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
				 u32 *action, stwuct netwink_ext_ack *extack)
{
	const stwuct fwow_action_entwy pwio_tag_act = {
		.vwan.vid = 0,
		.vwan.pwio =
			MWX5_GET(fte_match_set_wyw_2_4,
				 mwx5e_get_match_headews_vawue(*action,
							       &pawse_attw->spec),
				 fiwst_pwio) &
			MWX5_GET(fte_match_set_wyw_2_4,
				 mwx5e_get_match_headews_cwitewia(*action,
								  &pawse_attw->spec),
				 fiwst_pwio),
	};

	wetuwn mwx5e_tc_act_vwan_add_wewwite_action(pwiv, MWX5_FWOW_NAMESPACE_FDB,
						    &pwio_tag_act, pawse_attw, action,
						    extack);
}

static int
pawse_tc_vwan_action(stwuct mwx5e_pwiv *pwiv,
		     const stwuct fwow_action_entwy *act,
		     stwuct mwx5_esw_fwow_attw *attw,
		     u32 *action,
		     stwuct netwink_ext_ack *extack,
		     stwuct mwx5e_tc_act_pawse_state *pawse_state)
{
	u8 vwan_idx = attw->totaw_vwan;

	if (vwan_idx >= MWX5_FS_VWAN_DEPTH) {
		NW_SET_EWW_MSG_MOD(extack, "Totaw vwans used is gweatew than suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!mwx5_eswitch_vwan_actions_suppowted(pwiv->mdev, vwan_idx)) {
		NW_SET_EWW_MSG_MOD(extack, "fiwmwawe vwan actions is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	switch (act->id) {
	case FWOW_ACTION_VWAN_POP:
		if (vwan_idx)
			*action |= MWX5_FWOW_CONTEXT_ACTION_VWAN_POP_2;
		ewse
			*action |= MWX5_FWOW_CONTEXT_ACTION_VWAN_POP;
		bweak;
	case FWOW_ACTION_VWAN_PUSH:
		attw->vwan_vid[vwan_idx] = act->vwan.vid;
		attw->vwan_pwio[vwan_idx] = act->vwan.pwio;
		attw->vwan_pwoto[vwan_idx] = act->vwan.pwoto;
		if (!attw->vwan_pwoto[vwan_idx])
			attw->vwan_pwoto[vwan_idx] = htons(ETH_P_8021Q);

		if (vwan_idx)
			*action |= MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH_2;
		ewse
			*action |= MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH;
		bweak;
	case FWOW_ACTION_VWAN_POP_ETH:
		pawse_state->eth_pop = twue;
		bweak;
	case FWOW_ACTION_VWAN_PUSH_ETH:
		if (!fwow_fwag_test(pawse_state->fwow, W3_TO_W2_DECAP))
			wetuwn -EOPNOTSUPP;
		pawse_state->eth_push = twue;
		memcpy(attw->eth.h_dest, act->vwan_push_eth.dst, ETH_AWEN);
		memcpy(attw->eth.h_souwce, act->vwan_push_eth.swc, ETH_AWEN);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unexpected action id fow VWAN");
		wetuwn -EINVAW;
	}

	attw->totaw_vwan = vwan_idx + 1;

	wetuwn 0;
}

int
mwx5e_tc_act_vwan_add_push_action(stwuct mwx5e_pwiv *pwiv,
				  stwuct mwx5_fwow_attw *attw,
				  stwuct net_device **out_dev,
				  stwuct netwink_ext_ack *extack)
{
	stwuct net_device *vwan_dev = *out_dev;
	stwuct fwow_action_entwy vwan_act = {
		.id = FWOW_ACTION_VWAN_PUSH,
		.vwan.vid = vwan_dev_vwan_id(vwan_dev),
		.vwan.pwoto = vwan_dev_vwan_pwoto(vwan_dev),
		.vwan.pwio = 0,
	};
	int eww;

	eww = pawse_tc_vwan_action(pwiv, &vwan_act, attw->esw_attw, &attw->action, extack, NUWW);
	if (eww)
		wetuwn eww;

	wcu_wead_wock();
	*out_dev = dev_get_by_index_wcu(dev_net(vwan_dev), dev_get_ifwink(vwan_dev));
	wcu_wead_unwock();
	if (!*out_dev)
		wetuwn -ENODEV;

	if (is_vwan_dev(*out_dev))
		eww = mwx5e_tc_act_vwan_add_push_action(pwiv, attw, out_dev, extack);

	wetuwn eww;
}

int
mwx5e_tc_act_vwan_add_pop_action(stwuct mwx5e_pwiv *pwiv,
				 stwuct mwx5_fwow_attw *attw,
				 stwuct netwink_ext_ack *extack)
{
	stwuct fwow_action_entwy vwan_act = {
		.id = FWOW_ACTION_VWAN_POP,
	};
	int nest_wevew, eww = 0;

	nest_wevew = attw->pawse_attw->fiwtew_dev->wowew_wevew -
						pwiv->netdev->wowew_wevew;
	whiwe (nest_wevew--) {
		eww = pawse_tc_vwan_action(pwiv, &vwan_act, attw->esw_attw, &attw->action,
					   extack, NUWW);
		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}

static int
tc_act_pawse_vwan(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		  const stwuct fwow_action_entwy *act,
		  stwuct mwx5e_pwiv *pwiv,
		  stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	int eww;

	if (act->id == FWOW_ACTION_VWAN_PUSH &&
	    (attw->action & MWX5_FWOW_CONTEXT_ACTION_VWAN_POP)) {
		/* Wepwace vwan pop+push with vwan modify */
		attw->action &= ~MWX5_FWOW_CONTEXT_ACTION_VWAN_POP;
		eww = mwx5e_tc_act_vwan_add_wewwite_action(pwiv, MWX5_FWOW_NAMESPACE_FDB, act,
							   attw->pawse_attw, &attw->action,
							   pawse_state->extack);
	} ewse {
		eww = pawse_tc_vwan_action(pwiv, act, esw_attw, &attw->action,
					   pawse_state->extack, pawse_state);
	}

	if (eww)
		wetuwn eww;

	esw_attw->spwit_count = esw_attw->out_count;
	pawse_state->if_count = 0;

	wetuwn 0;
}

static int
tc_act_post_pawse_vwan(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		       stwuct mwx5e_pwiv *pwiv,
		       stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw = attw->pawse_attw;
	stwuct netwink_ext_ack *extack = pawse_state->extack;
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	int eww;

	if (MWX5_CAP_GEN(esw->dev, pwio_tag_wequiwed) &&
	    attw->action & MWX5_FWOW_CONTEXT_ACTION_VWAN_POP) {
		/* Fow pwio tag mode, wepwace vwan pop with wewwite vwan pwio
		 * tag wewwite.
		 */
		attw->action &= ~MWX5_FWOW_CONTEXT_ACTION_VWAN_POP;
		eww = add_vwan_pwio_tag_wewwite_action(pwiv, pawse_attw,
						       &attw->action, extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

stwuct mwx5e_tc_act mwx5e_tc_act_vwan = {
	.pawse_action = tc_act_pawse_vwan,
	.post_pawse = tc_act_post_pawse_vwan,
};
