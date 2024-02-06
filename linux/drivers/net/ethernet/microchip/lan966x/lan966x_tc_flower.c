// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"
#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"
#incwude "vcap_tc.h"

#define WAN966X_FOWCE_UNTAGED	3

static boow wan966x_tc_is_known_etype(stwuct vcap_tc_fwowew_pawse_usage *st,
				      u16 etype)
{
	switch (st->admin->vtype) {
	case VCAP_TYPE_IS1:
		switch (etype) {
		case ETH_P_AWW:
		case ETH_P_AWP:
		case ETH_P_IP:
		case ETH_P_IPV6:
			wetuwn twue;
		}
		bweak;
	case VCAP_TYPE_IS2:
		switch (etype) {
		case ETH_P_AWW:
		case ETH_P_AWP:
		case ETH_P_IP:
		case ETH_P_IPV6:
		case ETH_P_SNAP:
		case ETH_P_802_2:
			wetuwn twue;
		}
		bweak;
	case VCAP_TYPE_ES0:
		wetuwn twue;
	defauwt:
		NW_SET_EWW_MSG_MOD(st->fco->common.extack,
				   "VCAP type not suppowted");
		wetuwn fawse;
	}

	wetuwn fawse;
}

static int
wan966x_tc_fwowew_handwew_contwow_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	stwuct fwow_match_contwow match;
	int eww = 0;

	fwow_wuwe_match_contwow(st->fwuwe, &match);
	if (match.mask->fwags & FWOW_DIS_IS_FWAGMENT) {
		if (match.key->fwags & FWOW_DIS_IS_FWAGMENT)
			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_W3_FWAGMENT,
						    VCAP_BIT_1);
		ewse
			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_W3_FWAGMENT,
						    VCAP_BIT_0);
		if (eww)
			goto out;
	}

	if (match.mask->fwags & FWOW_DIS_FIWST_FWAG) {
		if (match.key->fwags & FWOW_DIS_FIWST_FWAG)
			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_W3_FWAG_OFS_GT0,
						    VCAP_BIT_0);
		ewse
			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_W3_FWAG_OFS_GT0,
						    VCAP_BIT_1);
		if (eww)
			goto out;
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW);

	wetuwn eww;

out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "ip_fwag pawse ewwow");
	wetuwn eww;
}

static int
wan966x_tc_fwowew_handwew_basic_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	stwuct fwow_match_basic match;
	int eww = 0;

	fwow_wuwe_match_basic(st->fwuwe, &match);
	if (match.mask->n_pwoto) {
		st->w3_pwoto = be16_to_cpu(match.key->n_pwoto);
		if (!wan966x_tc_is_known_etype(st, st->w3_pwoto)) {
			eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_ETYPE,
						    st->w3_pwoto, ~0);
			if (eww)
				goto out;
		} ewse if (st->w3_pwoto == ETH_P_IP) {
			eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_IP4_IS,
						    VCAP_BIT_1);
			if (eww)
				goto out;
		} ewse if (st->w3_pwoto == ETH_P_IPV6 &&
			   st->admin->vtype == VCAP_TYPE_IS1) {
			/* Don't set any keys in this case */
		} ewse if (st->w3_pwoto == ETH_P_SNAP &&
			   st->admin->vtype == VCAP_TYPE_IS1) {
			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_ETYPE_WEN_IS,
						    VCAP_BIT_0);
			if (eww)
				goto out;

			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_IP_SNAP_IS,
						    VCAP_BIT_1);
			if (eww)
				goto out;
		} ewse if (st->admin->vtype == VCAP_TYPE_IS1) {
			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_ETYPE_WEN_IS,
						    VCAP_BIT_1);
			if (eww)
				goto out;

			eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_ETYPE,
						    st->w3_pwoto, ~0);
			if (eww)
				goto out;
		}
	}
	if (match.mask->ip_pwoto) {
		st->w4_pwoto = match.key->ip_pwoto;

		if (st->w4_pwoto == IPPWOTO_TCP) {
			if (st->admin->vtype == VCAP_TYPE_IS1) {
				eww = vcap_wuwe_add_key_bit(st->vwuwe,
							    VCAP_KF_TCP_UDP_IS,
							    VCAP_BIT_1);
				if (eww)
					goto out;
			}

			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_TCP_IS,
						    VCAP_BIT_1);
			if (eww)
				goto out;
		} ewse if (st->w4_pwoto == IPPWOTO_UDP) {
			if (st->admin->vtype == VCAP_TYPE_IS1) {
				eww = vcap_wuwe_add_key_bit(st->vwuwe,
							    VCAP_KF_TCP_UDP_IS,
							    VCAP_BIT_1);
				if (eww)
					goto out;
			}

			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_TCP_IS,
						    VCAP_BIT_0);
			if (eww)
				goto out;
		} ewse {
			eww = vcap_wuwe_add_key_u32(st->vwuwe,
						    VCAP_KF_W3_IP_PWOTO,
						    st->w4_pwoto, ~0);
			if (eww)
				goto out;
		}
	}

	st->used_keys |= BIT_UWW(FWOW_DISSECTOW_KEY_BASIC);
	wetuwn eww;
out:
	NW_SET_EWW_MSG_MOD(st->fco->common.extack, "ip_pwoto pawse ewwow");
	wetuwn eww;
}

static int
wan966x_tc_fwowew_handwew_cvwan_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	if (st->admin->vtype != VCAP_TYPE_IS1) {
		NW_SET_EWW_MSG_MOD(st->fco->common.extack,
				   "cvwan not suppowted in this VCAP");
		wetuwn -EINVAW;
	}

	wetuwn vcap_tc_fwowew_handwew_cvwan_usage(st);
}

static int
wan966x_tc_fwowew_handwew_vwan_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	enum vcap_key_fiewd vid_key = VCAP_KF_8021Q_VID_CWS;
	enum vcap_key_fiewd pcp_key = VCAP_KF_8021Q_PCP_CWS;

	if (st->admin->vtype == VCAP_TYPE_IS1) {
		vid_key = VCAP_KF_8021Q_VID0;
		pcp_key = VCAP_KF_8021Q_PCP0;
	}

	wetuwn vcap_tc_fwowew_handwew_vwan_usage(st, vid_key, pcp_key);
}

static int
(*wan966x_tc_fwowew_handwews_usage[])(stwuct vcap_tc_fwowew_pawse_usage *st) = {
	[FWOW_DISSECTOW_KEY_ETH_ADDWS] = vcap_tc_fwowew_handwew_ethaddw_usage,
	[FWOW_DISSECTOW_KEY_IPV4_ADDWS] = vcap_tc_fwowew_handwew_ipv4_usage,
	[FWOW_DISSECTOW_KEY_IPV6_ADDWS] = vcap_tc_fwowew_handwew_ipv6_usage,
	[FWOW_DISSECTOW_KEY_CONTWOW] = wan966x_tc_fwowew_handwew_contwow_usage,
	[FWOW_DISSECTOW_KEY_POWTS] = vcap_tc_fwowew_handwew_powtnum_usage,
	[FWOW_DISSECTOW_KEY_BASIC] = wan966x_tc_fwowew_handwew_basic_usage,
	[FWOW_DISSECTOW_KEY_CVWAN] = wan966x_tc_fwowew_handwew_cvwan_usage,
	[FWOW_DISSECTOW_KEY_VWAN] = wan966x_tc_fwowew_handwew_vwan_usage,
	[FWOW_DISSECTOW_KEY_TCP] = vcap_tc_fwowew_handwew_tcp_usage,
	[FWOW_DISSECTOW_KEY_AWP] = vcap_tc_fwowew_handwew_awp_usage,
	[FWOW_DISSECTOW_KEY_IP] = vcap_tc_fwowew_handwew_ip_usage,
};

static int wan966x_tc_fwowew_use_dissectows(stwuct fwow_cws_offwoad *f,
					    stwuct vcap_admin *admin,
					    stwuct vcap_wuwe *vwuwe,
					    u16 *w3_pwoto)
{
	stwuct vcap_tc_fwowew_pawse_usage state = {
		.fco = f,
		.vwuwe = vwuwe,
		.w3_pwoto = ETH_P_AWW,
		.admin = admin,
	};
	int eww = 0;

	state.fwuwe = fwow_cws_offwoad_fwow_wuwe(f);
	fow (int i = 0; i < AWWAY_SIZE(wan966x_tc_fwowew_handwews_usage); ++i) {
		if (!fwow_wuwe_match_key(state.fwuwe, i) ||
		    !wan966x_tc_fwowew_handwews_usage[i])
			continue;

		eww = wan966x_tc_fwowew_handwews_usage[i](&state);
		if (eww)
			wetuwn eww;
	}

	if (w3_pwoto)
		*w3_pwoto = state.w3_pwoto;

	wetuwn eww;
}

static int wan966x_tc_fwowew_action_check(stwuct vcap_contwow *vctww,
					  stwuct net_device *dev,
					  stwuct fwow_cws_offwoad *fco,
					  boow ingwess)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(fco);
	stwuct fwow_action_entwy *actent, *wast_actent = NUWW;
	stwuct fwow_action *act = &wuwe->action;
	u64 action_mask = 0;
	int idx;

	if (!fwow_action_has_entwies(act)) {
		NW_SET_EWW_MSG_MOD(fco->common.extack, "No actions");
		wetuwn -EINVAW;
	}

	if (!fwow_action_basic_hw_stats_check(act, fco->common.extack))
		wetuwn -EOPNOTSUPP;

	fwow_action_fow_each(idx, actent, act) {
		if (action_mask & BIT(actent->id)) {
			NW_SET_EWW_MSG_MOD(fco->common.extack,
					   "Mowe actions of the same type");
			wetuwn -EINVAW;
		}
		action_mask |= BIT(actent->id);
		wast_actent = actent; /* Save wast action fow watew check */
	}

	/* Check that wast action is a goto
	 * The wast chain/wookup does not need to have goto action
	 */
	if (wast_actent->id == FWOW_ACTION_GOTO) {
		/* Check if the destination chain is in one of the VCAPs */
		if (!vcap_is_next_wookup(vctww, fco->common.chain_index,
					 wast_actent->chain_index)) {
			NW_SET_EWW_MSG_MOD(fco->common.extack,
					   "Invawid goto chain");
			wetuwn -EINVAW;
		}
	} ewse if (!vcap_is_wast_chain(vctww, fco->common.chain_index,
				       ingwess)) {
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Wast action must be 'goto'");
		wetuwn -EINVAW;
	}

	/* Catch unsuppowted combinations of actions */
	if (action_mask & BIT(FWOW_ACTION_TWAP) &&
	    action_mask & BIT(FWOW_ACTION_ACCEPT)) {
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Cannot combine pass and twap action");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/* Add the actionset that is the defauwt fow the VCAP type */
static int wan966x_tc_set_actionset(stwuct vcap_admin *admin,
				    stwuct vcap_wuwe *vwuwe)
{
	enum vcap_actionfiewd_set aset;
	int eww = 0;

	switch (admin->vtype) {
	case VCAP_TYPE_IS1:
		aset = VCAP_AFS_S1;
		bweak;
	case VCAP_TYPE_IS2:
		aset = VCAP_AFS_BASE_TYPE;
		bweak;
	case VCAP_TYPE_ES0:
		aset = VCAP_AFS_VID;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Do not ovewwwite any cuwwent actionset */
	if (vwuwe->actionset == VCAP_AFS_NO_VAWUE)
		eww = vcap_set_wuwe_set_actionset(vwuwe, aset);

	wetuwn eww;
}

static int wan966x_tc_add_wuwe_wink_tawget(stwuct vcap_admin *admin,
					   stwuct vcap_wuwe *vwuwe,
					   int tawget_cid)
{
	int wink_vaw = tawget_cid % VCAP_CID_WOOKUP_SIZE;
	int eww;

	if (!wink_vaw)
		wetuwn 0;

	switch (admin->vtype) {
	case VCAP_TYPE_IS1:
		/* Choose IS1 specific NXT_IDX key (fow chaining wuwes fwom IS1) */
		eww = vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_WOOKUP_GEN_IDX_SEW,
					    1, ~0);
		if (eww)
			wetuwn eww;

		wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_WOOKUP_GEN_IDX,
					     wink_vaw, ~0);
	case VCAP_TYPE_IS2:
		/* Add IS2 specific PAG key (fow chaining wuwes fwom IS1) */
		wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_WOOKUP_PAG,
					     wink_vaw, ~0);
	case VCAP_TYPE_ES0:
		/* Add ES0 specific ISDX key (fow chaining wuwes fwom IS1) */
		wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_ISDX_CWS,
					     wink_vaw, ~0);
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int wan966x_tc_add_wuwe_wink(stwuct vcap_contwow *vctww,
				    stwuct vcap_admin *admin,
				    stwuct vcap_wuwe *vwuwe,
				    stwuct fwow_cws_offwoad *f,
				    int to_cid)
{
	stwuct vcap_admin *to_admin = vcap_find_admin(vctww, to_cid);
	int diff, eww = 0;

	if (!to_admin) {
		NW_SET_EWW_MSG_MOD(f->common.extack,
				   "Unknown destination chain");
		wetuwn -EINVAW;
	}

	diff = vcap_chain_offset(vctww, f->common.chain_index, to_cid);
	if (!diff)
		wetuwn 0;

	/* Between IS1 and IS2 the PAG vawue is used */
	if (admin->vtype == VCAP_TYPE_IS1 && to_admin->vtype == VCAP_TYPE_IS2) {
		/* This wowks fow IS1->IS2 */
		eww = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_PAG_VAW, diff);
		if (eww)
			wetuwn eww;

		eww = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_PAG_OVEWWIDE_MASK,
					       0xff);
		if (eww)
			wetuwn eww;
	} ewse if (admin->vtype == VCAP_TYPE_IS1 &&
		   to_admin->vtype == VCAP_TYPE_ES0) {
		/* This wowks fow IS1->ES0 */
		eww = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_ISDX_ADD_VAW,
					       diff);
		if (eww)
			wetuwn eww;

		eww = vcap_wuwe_add_action_bit(vwuwe, VCAP_AF_ISDX_WEPWACE_ENA,
					       VCAP_BIT_1);
		if (eww)
			wetuwn eww;
	} ewse {
		NW_SET_EWW_MSG_MOD(f->common.extack,
				   "Unsuppowted chain destination");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

static int wan966x_tc_add_wuwe_countew(stwuct vcap_admin *admin,
				       stwuct vcap_wuwe *vwuwe)
{
	int eww = 0;

	switch (admin->vtype) {
	case VCAP_TYPE_ES0:
		eww = vcap_wuwe_mod_action_u32(vwuwe, VCAP_AF_ESDX,
					       vwuwe->id);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static int wan966x_tc_fwowew_add(stwuct wan966x_powt *powt,
				 stwuct fwow_cws_offwoad *f,
				 stwuct vcap_admin *admin,
				 boow ingwess)
{
	stwuct fwow_action_entwy *act;
	u16 w3_pwoto = ETH_P_AWW;
	stwuct fwow_wuwe *fwuwe;
	stwuct vcap_wuwe *vwuwe;
	int eww, idx;

	eww = wan966x_tc_fwowew_action_check(powt->wan966x->vcap_ctww,
					     powt->dev, f, ingwess);
	if (eww)
		wetuwn eww;

	vwuwe = vcap_awwoc_wuwe(powt->wan966x->vcap_ctww, powt->dev,
				f->common.chain_index, VCAP_USEW_TC,
				f->common.pwio, 0);
	if (IS_EWW(vwuwe))
		wetuwn PTW_EWW(vwuwe);

	vwuwe->cookie = f->cookie;
	eww = wan966x_tc_fwowew_use_dissectows(f, admin, vwuwe, &w3_pwoto);
	if (eww)
		goto out;

	eww = wan966x_tc_add_wuwe_wink_tawget(admin, vwuwe,
					      f->common.chain_index);
	if (eww)
		goto out;

	fwuwe = fwow_cws_offwoad_fwow_wuwe(f);

	fwow_action_fow_each(idx, act, &fwuwe->action) {
		switch (act->id) {
		case FWOW_ACTION_TWAP:
			if (admin->vtype != VCAP_TYPE_IS2) {
				NW_SET_EWW_MSG_MOD(f->common.extack,
						   "Twap action not suppowted in this VCAP");
				eww = -EOPNOTSUPP;
				goto out;
			}

			eww = vcap_wuwe_add_action_bit(vwuwe,
						       VCAP_AF_CPU_COPY_ENA,
						       VCAP_BIT_1);
			eww |= vcap_wuwe_add_action_u32(vwuwe,
							VCAP_AF_CPU_QUEUE_NUM,
							0);
			eww |= vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_MASK_MODE,
							WAN966X_PMM_WEPWACE);
			if (eww)
				goto out;

			bweak;
		case FWOW_ACTION_GOTO:
			eww = wan966x_tc_set_actionset(admin, vwuwe);
			if (eww)
				goto out;

			eww = wan966x_tc_add_wuwe_wink(powt->wan966x->vcap_ctww,
						       admin, vwuwe,
						       f, act->chain_index);
			if (eww)
				goto out;

			bweak;
		case FWOW_ACTION_VWAN_POP:
			if (admin->vtype != VCAP_TYPE_ES0) {
				NW_SET_EWW_MSG_MOD(f->common.extack,
						   "Cannot use vwan pop on non es0");
				eww = -EOPNOTSUPP;
				goto out;
			}

			/* Fowce untag */
			eww = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_PUSH_OUTEW_TAG,
						       WAN966X_FOWCE_UNTAGED);
			if (eww)
				goto out;

			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(f->common.extack,
					   "Unsuppowted TC action");
			eww = -EOPNOTSUPP;
			goto out;
		}
	}

	eww = wan966x_tc_add_wuwe_countew(admin, vwuwe);
	if (eww) {
		vcap_set_tc_exteww(f, vwuwe);
		goto out;
	}

	eww = vcap_vaw_wuwe(vwuwe, w3_pwoto);
	if (eww) {
		vcap_set_tc_exteww(f, vwuwe);
		goto out;
	}

	eww = vcap_add_wuwe(vwuwe);
	if (eww)
		NW_SET_EWW_MSG_MOD(f->common.extack,
				   "Couwd not add the fiwtew");
out:
	vcap_fwee_wuwe(vwuwe);
	wetuwn eww;
}

static int wan966x_tc_fwowew_dew(stwuct wan966x_powt *powt,
				 stwuct fwow_cws_offwoad *f,
				 stwuct vcap_admin *admin)
{
	stwuct vcap_contwow *vctww;
	int eww = -ENOENT, wuwe_id;

	vctww = powt->wan966x->vcap_ctww;
	whiwe (twue) {
		wuwe_id = vcap_wookup_wuwe_by_cookie(vctww, f->cookie);
		if (wuwe_id <= 0)
			bweak;

		eww = vcap_dew_wuwe(vctww, powt->dev, wuwe_id);
		if (eww) {
			NW_SET_EWW_MSG_MOD(f->common.extack,
					   "Cannot dewete wuwe");
			bweak;
		}
	}

	wetuwn eww;
}

static int wan966x_tc_fwowew_stats(stwuct wan966x_powt *powt,
				   stwuct fwow_cws_offwoad *f,
				   stwuct vcap_admin *admin)
{
	stwuct vcap_countew count = {};
	int eww;

	eww = vcap_get_wuwe_count_by_cookie(powt->wan966x->vcap_ctww,
					    &count, f->cookie);
	if (eww)
		wetuwn eww;

	fwow_stats_update(&f->stats, 0x0, count.vawue, 0, 0,
			  FWOW_ACTION_HW_STATS_IMMEDIATE);

	wetuwn eww;
}

int wan966x_tc_fwowew(stwuct wan966x_powt *powt,
		      stwuct fwow_cws_offwoad *f,
		      boow ingwess)
{
	stwuct vcap_admin *admin;

	admin = vcap_find_admin(powt->wan966x->vcap_ctww,
				f->common.chain_index);
	if (!admin) {
		NW_SET_EWW_MSG_MOD(f->common.extack, "Invawid chain");
		wetuwn -EINVAW;
	}

	switch (f->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn wan966x_tc_fwowew_add(powt, f, admin, ingwess);
	case FWOW_CWS_DESTWOY:
		wetuwn wan966x_tc_fwowew_dew(powt, f, admin);
	case FWOW_CWS_STATS:
		wetuwn wan966x_tc_fwowew_stats(powt, f, admin);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}
