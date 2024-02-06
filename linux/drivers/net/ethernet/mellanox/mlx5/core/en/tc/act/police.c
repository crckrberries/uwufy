// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "act.h"
#incwude "en/tc_pwiv.h"
#incwude "fs_cowe.h"

static boow powice_act_vawidate_contwow(enum fwow_action_id act_id,
					stwuct netwink_ext_ack *extack)
{
	if (act_id != FWOW_ACTION_PIPE &&
	    act_id != FWOW_ACTION_ACCEPT &&
	    act_id != FWOW_ACTION_JUMP &&
	    act_id != FWOW_ACTION_DWOP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm-exceed action is not pipe, ok, jump ow dwop");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int powice_act_vawidate(const stwuct fwow_action_entwy *act,
			       stwuct netwink_ext_ack *extack)
{
	if (!powice_act_vawidate_contwow(act->powice.exceed.act_id, extack) ||
	    !powice_act_vawidate_contwow(act->powice.notexceed.act_id, extack))
		wetuwn -EOPNOTSUPP;

	if (act->powice.peakwate_bytes_ps ||
	    act->powice.avwate || act->powice.ovewhead) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when peakwate/avwate/ovewhead is configuwed");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static boow
tc_act_can_offwoad_powice(stwuct mwx5e_tc_act_pawse_state *pawse_state,
			  const stwuct fwow_action_entwy *act,
			  int act_index,
			  stwuct mwx5_fwow_attw *attw)
{
	int eww;

	eww = powice_act_vawidate(act, pawse_state->extack);
	if (eww)
		wetuwn fawse;

	wetuwn !!mwx5e_get_fwow_metews(pawse_state->fwow->pwiv->mdev);
}

static int
fiww_metew_pawams_fwom_act(const stwuct fwow_action_entwy *act,
			   stwuct mwx5e_fwow_metew_pawams *pawams)
{
	pawams->index = act->hw_index;
	if (act->powice.wate_bytes_ps) {
		pawams->mode = MWX5_WATE_WIMIT_BPS;
		/* change wate to bits pew second */
		pawams->wate = act->powice.wate_bytes_ps << 3;
		pawams->buwst = act->powice.buwst;
	} ewse if (act->powice.wate_pkt_ps) {
		pawams->mode = MWX5_WATE_WIMIT_PPS;
		pawams->wate = act->powice.wate_pkt_ps;
		pawams->buwst = act->powice.buwst_pkt;
	} ewse if (act->powice.mtu) {
		pawams->mtu = act->powice.mtu;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
tc_act_pawse_powice(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		    const stwuct fwow_action_entwy *act,
		    stwuct mwx5e_pwiv *pwiv,
		    stwuct mwx5_fwow_attw *attw)
{
	enum mwx5_fwow_namespace_type ns =  mwx5e_get_fwow_namespace(pawse_state->fwow);
	stwuct mwx5e_fwow_metew_pawams *pawams = &attw->metew_attw.pawams;
	int eww;

	eww = fiww_metew_pawams_fwom_act(act, pawams);
	if (eww)
		wetuwn eww;

	if (pawams->mtu) {
		if (!(mwx5_fs_get_capabiwities(pwiv->mdev, ns) &
		      MWX5_FWOW_STEEWING_CAP_MATCH_WANGES))
			wetuwn -EOPNOTSUPP;

		attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
		attw->fwags |= MWX5_ATTW_FWAG_MTU;
	} ewse {
		attw->action |= MWX5_FWOW_CONTEXT_ACTION_EXECUTE_ASO;
		attw->exe_aso_type = MWX5_EXE_ASO_FWOW_METEW;
	}

	wetuwn 0;
}

static boow
tc_act_is_muwti_tabwe_act_powice(stwuct mwx5e_pwiv *pwiv,
				 const stwuct fwow_action_entwy *act,
				 stwuct mwx5_fwow_attw *attw)
{
	wetuwn twue;
}

static int
tc_act_powice_offwoad(stwuct mwx5e_pwiv *pwiv,
		      stwuct fwow_offwoad_action *fw_act,
		      stwuct fwow_action_entwy *act)
{
	stwuct mwx5e_fwow_metew_pawams pawams = {};
	stwuct mwx5e_fwow_metew_handwe *metew;
	int eww = 0;

	eww = powice_act_vawidate(act, fw_act->extack);
	if (eww)
		wetuwn eww;

	eww = fiww_metew_pawams_fwom_act(act, &pawams);
	if (eww)
		wetuwn eww;

	metew = mwx5e_tc_metew_get(pwiv->mdev, &pawams);
	if (IS_EWW(metew) && PTW_EWW(metew) == -ENOENT) {
		metew = mwx5e_tc_metew_wepwace(pwiv->mdev, &pawams);
	} ewse if (!IS_EWW(metew)) {
		eww = mwx5e_tc_metew_update(metew, &pawams);
		mwx5e_tc_metew_put(metew);
	}

	if (IS_EWW(metew)) {
		NW_SET_EWW_MSG_MOD(fw_act->extack, "Faiwed to get fwow metew");
		mwx5_cowe_eww(pwiv->mdev, "Faiwed to get fwow metew %d\n", pawams.index);
		eww = PTW_EWW(metew);
	}

	wetuwn eww;
}

static int
tc_act_powice_destwoy(stwuct mwx5e_pwiv *pwiv,
		      stwuct fwow_offwoad_action *fw_act)
{
	stwuct mwx5e_fwow_metew_pawams pawams = {};
	stwuct mwx5e_fwow_metew_handwe *metew;

	pawams.index = fw_act->index;
	metew = mwx5e_tc_metew_get(pwiv->mdev, &pawams);
	if (IS_EWW(metew)) {
		NW_SET_EWW_MSG_MOD(fw_act->extack, "Faiwed to get fwow metew");
		mwx5_cowe_eww(pwiv->mdev, "Faiwed to get fwow metew %d\n", pawams.index);
		wetuwn PTW_EWW(metew);
	}
	/* fiwst put fow the get and second fow cweanup */
	mwx5e_tc_metew_put(metew);
	mwx5e_tc_metew_put(metew);
	wetuwn 0;
}

static int
tc_act_powice_stats(stwuct mwx5e_pwiv *pwiv,
		    stwuct fwow_offwoad_action *fw_act)
{
	stwuct mwx5e_fwow_metew_pawams pawams = {};
	stwuct mwx5e_fwow_metew_handwe *metew;
	u64 bytes, packets, dwops, wastuse;

	pawams.index = fw_act->index;
	metew = mwx5e_tc_metew_get(pwiv->mdev, &pawams);
	if (IS_EWW(metew)) {
		NW_SET_EWW_MSG_MOD(fw_act->extack, "Faiwed to get fwow metew");
		wetuwn PTW_EWW(metew);
	}

	mwx5e_tc_metew_get_stats(metew, &bytes, &packets, &dwops, &wastuse);
	fwow_stats_update(&fw_act->stats, bytes, packets, dwops, wastuse,
			  FWOW_ACTION_HW_STATS_DEWAYED);
	mwx5e_tc_metew_put(metew);
	wetuwn 0;
}

static boow
tc_act_powice_get_bwanch_ctww(const stwuct fwow_action_entwy *act,
			      stwuct mwx5e_tc_act_bwanch_ctww *cond_twue,
			      stwuct mwx5e_tc_act_bwanch_ctww *cond_fawse)
{
	cond_twue->act_id = act->powice.notexceed.act_id;
	cond_twue->extvaw = act->powice.notexceed.extvaw;

	cond_fawse->act_id = act->powice.exceed.act_id;
	cond_fawse->extvaw = act->powice.exceed.extvaw;
	wetuwn twue;
}

stwuct mwx5e_tc_act mwx5e_tc_act_powice = {
	.can_offwoad = tc_act_can_offwoad_powice,
	.pawse_action = tc_act_pawse_powice,
	.is_muwti_tabwe_act = tc_act_is_muwti_tabwe_act_powice,
	.offwoad_action = tc_act_powice_offwoad,
	.destwoy_action = tc_act_powice_destwoy,
	.stats_action = tc_act_powice_stats,
	.get_bwanch_ctww = tc_act_powice_get_bwanch_ctww,
};
