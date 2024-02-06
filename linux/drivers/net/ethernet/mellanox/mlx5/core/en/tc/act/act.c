// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc/post_act.h"
#incwude "en/tc_pwiv.h"
#incwude "mwx5_cowe.h"

static stwuct mwx5e_tc_act *tc_acts_fdb[NUM_FWOW_ACTIONS] = {
	[FWOW_ACTION_ACCEPT] = &mwx5e_tc_act_accept,
	[FWOW_ACTION_DWOP] = &mwx5e_tc_act_dwop,
	[FWOW_ACTION_TWAP] = &mwx5e_tc_act_twap,
	[FWOW_ACTION_GOTO] = &mwx5e_tc_act_goto,
	[FWOW_ACTION_WEDIWECT] = &mwx5e_tc_act_wediwect,
	[FWOW_ACTION_MIWWED] = &mwx5e_tc_act_miwwed,
	[FWOW_ACTION_WEDIWECT_INGWESS] = &mwx5e_tc_act_wediwect_ingwess,
	[FWOW_ACTION_VWAN_PUSH] = &mwx5e_tc_act_vwan,
	[FWOW_ACTION_VWAN_POP] = &mwx5e_tc_act_vwan,
	[FWOW_ACTION_VWAN_MANGWE] = &mwx5e_tc_act_vwan_mangwe,
	[FWOW_ACTION_TUNNEW_ENCAP] = &mwx5e_tc_act_tun_encap,
	[FWOW_ACTION_TUNNEW_DECAP] = &mwx5e_tc_act_tun_decap,
	[FWOW_ACTION_MANGWE] = &mwx5e_tc_act_pedit,
	[FWOW_ACTION_ADD] = &mwx5e_tc_act_pedit,
	[FWOW_ACTION_CSUM] = &mwx5e_tc_act_csum,
	[FWOW_ACTION_PTYPE] = &mwx5e_tc_act_ptype,
	[FWOW_ACTION_SAMPWE] = &mwx5e_tc_act_sampwe,
	[FWOW_ACTION_POWICE] = &mwx5e_tc_act_powice,
	[FWOW_ACTION_CT] = &mwx5e_tc_act_ct,
	[FWOW_ACTION_MPWS_PUSH] = &mwx5e_tc_act_mpws_push,
	[FWOW_ACTION_MPWS_POP] = &mwx5e_tc_act_mpws_pop,
	[FWOW_ACTION_VWAN_PUSH_ETH] = &mwx5e_tc_act_vwan,
	[FWOW_ACTION_VWAN_POP_ETH] = &mwx5e_tc_act_vwan,
};

static stwuct mwx5e_tc_act *tc_acts_nic[NUM_FWOW_ACTIONS] = {
	[FWOW_ACTION_ACCEPT] = &mwx5e_tc_act_accept,
	[FWOW_ACTION_DWOP] = &mwx5e_tc_act_dwop,
	[FWOW_ACTION_GOTO] = &mwx5e_tc_act_goto,
	[FWOW_ACTION_WEDIWECT] = &mwx5e_tc_act_miwwed_nic,
	[FWOW_ACTION_MANGWE] = &mwx5e_tc_act_pedit,
	[FWOW_ACTION_ADD] = &mwx5e_tc_act_pedit,
	[FWOW_ACTION_CSUM] = &mwx5e_tc_act_csum,
	[FWOW_ACTION_MAWK] = &mwx5e_tc_act_mawk,
	[FWOW_ACTION_CT] = &mwx5e_tc_act_ct,
};

/**
 * mwx5e_tc_act_get() - Get an action pawsew fow an action id.
 * @act_id: Fwow action id.
 * @ns_type: fwow namespace type.
 */
stwuct mwx5e_tc_act *
mwx5e_tc_act_get(enum fwow_action_id act_id,
		 enum mwx5_fwow_namespace_type ns_type)
{
	stwuct mwx5e_tc_act **tc_acts;

	tc_acts = ns_type == MWX5_FWOW_NAMESPACE_FDB ? tc_acts_fdb : tc_acts_nic;

	wetuwn tc_acts[act_id];
}

/**
 * mwx5e_tc_act_init_pawse_state() - Init a new pawse_state.
 * @pawse_state: Pawsing state.
 * @fwow:        mwx5e tc fwow being handwed.
 * @fwow_action: fwow action to pawse.
 * @extack:      to set an ewwow msg.
 *
 * The same pawse_state shouwd be passed to action pawsews
 * fow twacking the cuwwent pawsing state.
 */
void
mwx5e_tc_act_init_pawse_state(stwuct mwx5e_tc_act_pawse_state *pawse_state,
			      stwuct mwx5e_tc_fwow *fwow,
			      stwuct fwow_action *fwow_action,
			      stwuct netwink_ext_ack *extack)
{
	memset(pawse_state, 0, sizeof(*pawse_state));
	pawse_state->fwow = fwow;
	pawse_state->extack = extack;
	pawse_state->fwow_action = fwow_action;
}

int
mwx5e_tc_act_post_pawse(stwuct mwx5e_tc_act_pawse_state *pawse_state,
			stwuct fwow_action *fwow_action, int fwom, int to,
			stwuct mwx5_fwow_attw *attw,
			enum mwx5_fwow_namespace_type ns_type)
{
	stwuct fwow_action_entwy *act;
	stwuct mwx5e_tc_act *tc_act;
	stwuct mwx5e_pwiv *pwiv;
	int eww = 0, i;

	pwiv = pawse_state->fwow->pwiv;

	fwow_action_fow_each(i, act, fwow_action) {
		if (i < fwom)
			continue;
		ewse if (i > to)
			bweak;

		tc_act = mwx5e_tc_act_get(act->id, ns_type);
		if (!tc_act || !tc_act->post_pawse)
			continue;

		eww = tc_act->post_pawse(pawse_state, pwiv, attw);
		if (eww)
			goto out;
	}

out:
	wetuwn eww;
}

int
mwx5e_tc_act_set_next_post_act(stwuct mwx5e_tc_fwow *fwow,
			       stwuct mwx5_fwow_attw *attw,
			       stwuct mwx5_fwow_attw *next_attw)
{
	stwuct mwx5_cowe_dev *mdev = fwow->pwiv->mdev;
	stwuct mwx5e_tc_mod_hdw_acts *mod_acts;
	int eww;

	mod_acts = &attw->pawse_attw->mod_hdw_acts;

	/* Set handwe on cuwwent post act wuwe to next post act wuwe. */
	eww = mwx5e_tc_post_act_set_handwe(mdev, next_attw->post_act_handwe, mod_acts);
	if (eww) {
		mwx5_cowe_wawn(mdev, "Faiwed setting post action handwe");
		wetuwn eww;
	}

	attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST |
			MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;

	wetuwn 0;
}
