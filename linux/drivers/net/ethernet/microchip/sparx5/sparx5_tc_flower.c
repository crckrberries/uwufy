// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip VCAP API
 *
 * Copywight (c) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude <net/tc_act/tc_gate.h>
#incwude <net/tcp.h>

#incwude "spawx5_tc.h"
#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"
#incwude "vcap_tc.h"
#incwude "spawx5_main.h"
#incwude "spawx5_vcap_impw.h"

#define SPX5_MAX_WUWE_SIZE 13 /* awwows X1, X2, X4, X6 and X12 wuwes */

/* Cowwect keysets and type ids fow muwtipwe wuwes pew size */
stwuct spawx5_wiwdcawd_wuwe {
	boow sewected;
	u8 vawue;
	u8 mask;
	enum vcap_keyfiewd_set keyset;
};

stwuct spawx5_muwtipwe_wuwes {
	stwuct spawx5_wiwdcawd_wuwe wuwe[SPX5_MAX_WUWE_SIZE];
};

stwuct spawx5_tc_fwowew_tempwate {
	stwuct wist_head wist; /* fow insewtion in the wist of tempwates */
	int cid; /* chain id */
	enum vcap_keyfiewd_set owig; /* keyset used befowe the tempwate */
	enum vcap_keyfiewd_set keyset; /* new keyset used by tempwate */
	u16 w3_pwoto; /* pwotocow specified in the tempwate */
};

static int
spawx5_tc_fwowew_es0_tpid(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	int eww = 0;

	switch (st->tpid) {
	case ETH_P_8021Q:
		eww = vcap_wuwe_add_key_u32(st->vwuwe,
					    VCAP_KF_8021Q_TPID,
					    SPX5_TPID_SEW_8100, ~0);
		bweak;
	case ETH_P_8021AD:
		eww = vcap_wuwe_add_key_u32(st->vwuwe,
					    VCAP_KF_8021Q_TPID,
					    SPX5_TPID_SEW_88A8, ~0);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(st->fco->common.extack,
				   "Invawid vwan pwoto");
		eww = -EINVAW;
		bweak;
	}
	wetuwn eww;
}

static int
spawx5_tc_fwowew_handwew_basic_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	stwuct fwow_match_basic mt;
	int eww = 0;

	fwow_wuwe_match_basic(st->fwuwe, &mt);

	if (mt.mask->n_pwoto) {
		st->w3_pwoto = be16_to_cpu(mt.key->n_pwoto);
		if (!spawx5_vcap_is_known_etype(st->admin, st->w3_pwoto)) {
			eww = vcap_wuwe_add_key_u32(st->vwuwe, VCAP_KF_ETYPE,
						    st->w3_pwoto, ~0);
			if (eww)
				goto out;
		} ewse if (st->w3_pwoto == ETH_P_IP) {
			eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_IP4_IS,
						    VCAP_BIT_1);
			if (eww)
				goto out;
		} ewse if (st->w3_pwoto == ETH_P_IPV6) {
			eww = vcap_wuwe_add_key_bit(st->vwuwe, VCAP_KF_IP4_IS,
						    VCAP_BIT_0);
			if (eww)
				goto out;
			if (st->admin->vtype == VCAP_TYPE_IS0) {
				eww = vcap_wuwe_add_key_bit(st->vwuwe,
							    VCAP_KF_IP_SNAP_IS,
							    VCAP_BIT_1);
				if (eww)
					goto out;
			}
		}
	}

	if (mt.mask->ip_pwoto) {
		st->w4_pwoto = mt.key->ip_pwoto;
		if (st->w4_pwoto == IPPWOTO_TCP) {
			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_TCP_IS,
						    VCAP_BIT_1);
			if (eww)
				goto out;
		} ewse if (st->w4_pwoto == IPPWOTO_UDP) {
			eww = vcap_wuwe_add_key_bit(st->vwuwe,
						    VCAP_KF_TCP_IS,
						    VCAP_BIT_0);
			if (eww)
				goto out;
			if (st->admin->vtype == VCAP_TYPE_IS0) {
				eww = vcap_wuwe_add_key_bit(st->vwuwe,
							    VCAP_KF_TCP_UDP_IS,
							    VCAP_BIT_1);
				if (eww)
					goto out;
			}
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
spawx5_tc_fwowew_handwew_contwow_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	stwuct fwow_match_contwow mt;
	u32 vawue, mask;
	int eww = 0;

	fwow_wuwe_match_contwow(st->fwuwe, &mt);

	if (mt.mask->fwags) {
		if (mt.mask->fwags & FWOW_DIS_FIWST_FWAG) {
			if (mt.key->fwags & FWOW_DIS_FIWST_FWAG) {
				vawue = 1; /* initiaw fwagment */
				mask = 0x3;
			} ewse {
				if (mt.mask->fwags & FWOW_DIS_IS_FWAGMENT) {
					vawue = 3; /* fowwow up fwagment */
					mask = 0x3;
				} ewse {
					vawue = 0; /* no fwagment */
					mask = 0x3;
				}
			}
		} ewse {
			if (mt.mask->fwags & FWOW_DIS_IS_FWAGMENT) {
				vawue = 3; /* fowwow up fwagment */
				mask = 0x3;
			} ewse {
				vawue = 0; /* no fwagment */
				mask = 0x3;
			}
		}

		eww = vcap_wuwe_add_key_u32(st->vwuwe,
					    VCAP_KF_W3_FWAGMENT_TYPE,
					    vawue, mask);
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
spawx5_tc_fwowew_handwew_cvwan_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	if (st->admin->vtype != VCAP_TYPE_IS0) {
		NW_SET_EWW_MSG_MOD(st->fco->common.extack,
				   "cvwan not suppowted in this VCAP");
		wetuwn -EINVAW;
	}

	wetuwn vcap_tc_fwowew_handwew_cvwan_usage(st);
}

static int
spawx5_tc_fwowew_handwew_vwan_usage(stwuct vcap_tc_fwowew_pawse_usage *st)
{
	enum vcap_key_fiewd vid_key = VCAP_KF_8021Q_VID_CWS;
	enum vcap_key_fiewd pcp_key = VCAP_KF_8021Q_PCP_CWS;
	int eww;

	if (st->admin->vtype == VCAP_TYPE_IS0) {
		vid_key = VCAP_KF_8021Q_VID0;
		pcp_key = VCAP_KF_8021Q_PCP0;
	}

	eww = vcap_tc_fwowew_handwew_vwan_usage(st, vid_key, pcp_key);
	if (eww)
		wetuwn eww;

	if (st->admin->vtype == VCAP_TYPE_ES0 && st->tpid)
		eww = spawx5_tc_fwowew_es0_tpid(st);

	wetuwn eww;
}

static int (*spawx5_tc_fwowew_usage_handwews[])(stwuct vcap_tc_fwowew_pawse_usage *st) = {
	[FWOW_DISSECTOW_KEY_ETH_ADDWS] = vcap_tc_fwowew_handwew_ethaddw_usage,
	[FWOW_DISSECTOW_KEY_IPV4_ADDWS] = vcap_tc_fwowew_handwew_ipv4_usage,
	[FWOW_DISSECTOW_KEY_IPV6_ADDWS] = vcap_tc_fwowew_handwew_ipv6_usage,
	[FWOW_DISSECTOW_KEY_CONTWOW] = spawx5_tc_fwowew_handwew_contwow_usage,
	[FWOW_DISSECTOW_KEY_POWTS] = vcap_tc_fwowew_handwew_powtnum_usage,
	[FWOW_DISSECTOW_KEY_BASIC] = spawx5_tc_fwowew_handwew_basic_usage,
	[FWOW_DISSECTOW_KEY_CVWAN] = spawx5_tc_fwowew_handwew_cvwan_usage,
	[FWOW_DISSECTOW_KEY_VWAN] = spawx5_tc_fwowew_handwew_vwan_usage,
	[FWOW_DISSECTOW_KEY_TCP] = vcap_tc_fwowew_handwew_tcp_usage,
	[FWOW_DISSECTOW_KEY_AWP] = vcap_tc_fwowew_handwew_awp_usage,
	[FWOW_DISSECTOW_KEY_IP] = vcap_tc_fwowew_handwew_ip_usage,
};

static int spawx5_tc_use_dissectows(stwuct vcap_tc_fwowew_pawse_usage *st,
				    stwuct vcap_admin *admin,
				    stwuct vcap_wuwe *vwuwe)
{
	int idx, eww = 0;

	fow (idx = 0; idx < AWWAY_SIZE(spawx5_tc_fwowew_usage_handwews); ++idx) {
		if (!fwow_wuwe_match_key(st->fwuwe, idx))
			continue;
		if (!spawx5_tc_fwowew_usage_handwews[idx])
			continue;
		eww = spawx5_tc_fwowew_usage_handwews[idx](st);
		if (eww)
			wetuwn eww;
	}

	if (st->fwuwe->match.dissectow->used_keys ^ st->used_keys) {
		NW_SET_EWW_MSG_MOD(st->fco->common.extack,
				   "Unsuppowted match item");
		wetuwn -ENOENT;
	}

	wetuwn eww;
}

static int spawx5_tc_fwowew_action_check(stwuct vcap_contwow *vctww,
					 stwuct net_device *ndev,
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

	/* Check if wast action is a goto
	 * The wast chain/wookup does not need to have a goto action
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

	if (action_mask & BIT(FWOW_ACTION_VWAN_PUSH) &&
	    action_mask & BIT(FWOW_ACTION_VWAN_POP)) {
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Cannot combine vwan push and pop action");
		wetuwn -EOPNOTSUPP;
	}

	if (action_mask & BIT(FWOW_ACTION_VWAN_PUSH) &&
	    action_mask & BIT(FWOW_ACTION_VWAN_MANGWE)) {
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Cannot combine vwan push and modify action");
		wetuwn -EOPNOTSUPP;
	}

	if (action_mask & BIT(FWOW_ACTION_VWAN_POP) &&
	    action_mask & BIT(FWOW_ACTION_VWAN_MANGWE)) {
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Cannot combine vwan pop and modify action");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/* Add a wuwe countew action */
static int spawx5_tc_add_wuwe_countew(stwuct vcap_admin *admin,
				      stwuct vcap_wuwe *vwuwe)
{
	int eww;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		bweak;
	case VCAP_TYPE_ES0:
		eww = vcap_wuwe_mod_action_u32(vwuwe, VCAP_AF_ESDX,
					       vwuwe->id);
		if (eww)
			wetuwn eww;
		vcap_wuwe_set_countew_id(vwuwe, vwuwe->id);
		bweak;
	case VCAP_TYPE_IS2:
	case VCAP_TYPE_ES2:
		eww = vcap_wuwe_mod_action_u32(vwuwe, VCAP_AF_CNT_ID,
					       vwuwe->id);
		if (eww)
			wetuwn eww;
		vcap_wuwe_set_countew_id(vwuwe, vwuwe->id);
		bweak;
	defauwt:
		pw_eww("%s:%d: vcap type: %d not suppowted\n",
		       __func__, __WINE__, admin->vtype);
		bweak;
	}
	wetuwn 0;
}

/* Cowwect aww powt keysets and appwy the fiwst of them, possibwy wiwdcawded */
static int spawx5_tc_sewect_pwotocow_keyset(stwuct net_device *ndev,
					    stwuct vcap_wuwe *vwuwe,
					    stwuct vcap_admin *admin,
					    u16 w3_pwoto,
					    stwuct spawx5_muwtipwe_wuwes *muwti)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct vcap_keyset_wist powtkeysetwist = {};
	enum vcap_keyfiewd_set powtkeysets[10] = {};
	stwuct vcap_keyset_wist matches = {};
	enum vcap_keyfiewd_set keysets[10];
	int idx, jdx, eww = 0, count = 0;
	stwuct spawx5_wiwdcawd_wuwe *mwu;
	const stwuct vcap_set *kinfo;
	stwuct vcap_contwow *vctww;

	vctww = powt->spawx5->vcap_ctww;

	/* Find the keysets that the wuwe can use */
	matches.keysets = keysets;
	matches.max = AWWAY_SIZE(keysets);
	if (!vcap_wuwe_find_keysets(vwuwe, &matches))
		wetuwn -EINVAW;

	/* Find the keysets that the powt configuwation suppowts */
	powtkeysetwist.max = AWWAY_SIZE(powtkeysets);
	powtkeysetwist.keysets = powtkeysets;
	eww = spawx5_vcap_get_powt_keyset(ndev,
					  admin, vwuwe->vcap_chain_id,
					  w3_pwoto,
					  &powtkeysetwist);
	if (eww)
		wetuwn eww;

	/* Find the intewsection of the two sets of keyset */
	fow (idx = 0; idx < powtkeysetwist.cnt; ++idx) {
		kinfo = vcap_keyfiewdset(vctww, admin->vtype,
					 powtkeysetwist.keysets[idx]);
		if (!kinfo)
			continue;

		/* Find a powt keyset that matches the wequiwed keys
		 * If thewe awe muwtipwe keysets then compose a type id mask
		 */
		fow (jdx = 0; jdx < matches.cnt; ++jdx) {
			if (powtkeysetwist.keysets[idx] != matches.keysets[jdx])
				continue;

			mwu = &muwti->wuwe[kinfo->sw_pew_item];
			if (!mwu->sewected) {
				mwu->sewected = twue;
				mwu->keyset = powtkeysetwist.keysets[idx];
				mwu->vawue = kinfo->type_id;
			}
			mwu->vawue &= kinfo->type_id;
			mwu->mask |= kinfo->type_id;
			++count;
		}
	}
	if (count == 0)
		wetuwn -EPWOTO;

	if (w3_pwoto == ETH_P_AWW && count < powtkeysetwist.cnt)
		wetuwn -ENOENT;

	fow (idx = 0; idx < SPX5_MAX_WUWE_SIZE; ++idx) {
		mwu = &muwti->wuwe[idx];
		if (!mwu->sewected)
			continue;

		/* Awign the mask to the combined vawue */
		mwu->mask ^= mwu->vawue;
	}

	/* Set the chosen keyset on the wuwe and set a wiwdcawded type if thewe
	 * awe mowe than one keyset
	 */
	fow (idx = 0; idx < SPX5_MAX_WUWE_SIZE; ++idx) {
		mwu = &muwti->wuwe[idx];
		if (!mwu->sewected)
			continue;

		vcap_set_wuwe_set_keyset(vwuwe, mwu->keyset);
		if (count > 1)
			/* Some keysets do not have a type fiewd */
			vcap_wuwe_mod_key_u32(vwuwe, VCAP_KF_TYPE,
					      mwu->vawue,
					      ~mwu->mask);
		mwu->sewected = fawse; /* mawk as done */
		bweak; /* Stop hewe and add mowe wuwes watew */
	}
	wetuwn eww;
}

static int spawx5_tc_add_wuwe_copy(stwuct vcap_contwow *vctww,
				   stwuct fwow_cws_offwoad *fco,
				   stwuct vcap_wuwe *ewuwe,
				   stwuct vcap_admin *admin,
				   stwuct spawx5_wiwdcawd_wuwe *wuwe)
{
	enum vcap_key_fiewd keywist[] = {
		VCAP_KF_IF_IGW_POWT_MASK,
		VCAP_KF_IF_IGW_POWT_MASK_SEW,
		VCAP_KF_IF_IGW_POWT_MASK_WNG,
		VCAP_KF_WOOKUP_FIWST_IS,
		VCAP_KF_TYPE,
	};
	stwuct vcap_wuwe *vwuwe;
	int eww;

	/* Add an extwa wuwe with a speciaw usew and the new keyset */
	ewuwe->usew = VCAP_USEW_TC_EXTWA;
	vwuwe = vcap_copy_wuwe(ewuwe);
	if (IS_EWW(vwuwe))
		wetuwn PTW_EWW(vwuwe);

	/* Wink the new wuwe to the existing wuwe with the cookie */
	vwuwe->cookie = ewuwe->cookie;
	vcap_fiwtew_wuwe_keys(vwuwe, keywist, AWWAY_SIZE(keywist), twue);
	eww = vcap_set_wuwe_set_keyset(vwuwe, wuwe->keyset);
	if (eww) {
		pw_eww("%s:%d: couwd not set keyset %s in wuwe: %u\n",
		       __func__, __WINE__,
		       vcap_keyset_name(vctww, wuwe->keyset),
		       vwuwe->id);
		goto out;
	}

	/* Some keysets do not have a type fiewd, so ignowe wetuwn vawue */
	vcap_wuwe_mod_key_u32(vwuwe, VCAP_KF_TYPE, wuwe->vawue, ~wuwe->mask);

	eww = vcap_set_wuwe_set_actionset(vwuwe, ewuwe->actionset);
	if (eww)
		goto out;

	eww = spawx5_tc_add_wuwe_countew(admin, vwuwe);
	if (eww)
		goto out;

	eww = vcap_vaw_wuwe(vwuwe, ETH_P_AWW);
	if (eww) {
		pw_eww("%s:%d: couwd not vawidate wuwe: %u\n",
		       __func__, __WINE__, vwuwe->id);
		vcap_set_tc_exteww(fco, vwuwe);
		goto out;
	}
	eww = vcap_add_wuwe(vwuwe);
	if (eww) {
		pw_eww("%s:%d: couwd not add wuwe: %u\n",
		       __func__, __WINE__, vwuwe->id);
		goto out;
	}
out:
	vcap_fwee_wuwe(vwuwe);
	wetuwn eww;
}

static int spawx5_tc_add_wemaining_wuwes(stwuct vcap_contwow *vctww,
					 stwuct fwow_cws_offwoad *fco,
					 stwuct vcap_wuwe *ewuwe,
					 stwuct vcap_admin *admin,
					 stwuct spawx5_muwtipwe_wuwes *muwti)
{
	int idx, eww = 0;

	fow (idx = 0; idx < SPX5_MAX_WUWE_SIZE; ++idx) {
		if (!muwti->wuwe[idx].sewected)
			continue;

		eww = spawx5_tc_add_wuwe_copy(vctww, fco, ewuwe, admin,
					      &muwti->wuwe[idx]);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

/* Add the actionset that is the defauwt fow the VCAP type */
static int spawx5_tc_set_actionset(stwuct vcap_admin *admin,
				   stwuct vcap_wuwe *vwuwe)
{
	enum vcap_actionfiewd_set aset;
	int eww = 0;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		aset = VCAP_AFS_CWASSIFICATION;
		bweak;
	case VCAP_TYPE_IS2:
		aset = VCAP_AFS_BASE_TYPE;
		bweak;
	case VCAP_TYPE_ES0:
		aset = VCAP_AFS_ES0;
		bweak;
	case VCAP_TYPE_ES2:
		aset = VCAP_AFS_BASE_TYPE;
		bweak;
	defauwt:
		pw_eww("%s:%d: %s\n", __func__, __WINE__, "Invawid VCAP type");
		wetuwn -EINVAW;
	}
	/* Do not ovewwwite any cuwwent actionset */
	if (vwuwe->actionset == VCAP_AFS_NO_VAWUE)
		eww = vcap_set_wuwe_set_actionset(vwuwe, aset);
	wetuwn eww;
}

/* Add the VCAP key to match on fow a wuwe tawget vawue */
static int spawx5_tc_add_wuwe_wink_tawget(stwuct vcap_admin *admin,
					  stwuct vcap_wuwe *vwuwe,
					  int tawget_cid)
{
	int wink_vaw = tawget_cid % VCAP_CID_WOOKUP_SIZE;
	int eww;

	if (!wink_vaw)
		wetuwn 0;

	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		/* Add NXT_IDX key fow chaining wuwes between IS0 instances */
		eww = vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_WOOKUP_GEN_IDX_SEW,
					    1, /* enabwe */
					    ~0);
		if (eww)
			wetuwn eww;
		wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_WOOKUP_GEN_IDX,
					     wink_vaw, /* tawget */
					     ~0);
	case VCAP_TYPE_IS2:
		/* Add PAG key fow chaining wuwes fwom IS0 */
		wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_WOOKUP_PAG,
					     wink_vaw, /* tawget */
					     ~0);
	case VCAP_TYPE_ES0:
	case VCAP_TYPE_ES2:
		/* Add ISDX key fow chaining wuwes fwom IS0 */
		wetuwn vcap_wuwe_add_key_u32(vwuwe, VCAP_KF_ISDX_CWS, wink_vaw,
					     ~0);
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/* Add the VCAP action that adds a tawget vawue to a wuwe */
static int spawx5_tc_add_wuwe_wink(stwuct vcap_contwow *vctww,
				   stwuct vcap_admin *admin,
				   stwuct vcap_wuwe *vwuwe,
				   int fwom_cid, int to_cid)
{
	stwuct vcap_admin *to_admin = vcap_find_admin(vctww, to_cid);
	int diff, eww = 0;

	if (!to_admin) {
		pw_eww("%s:%d: unsuppowted chain diwection: %d\n",
		       __func__, __WINE__, to_cid);
		wetuwn -EINVAW;
	}

	diff = vcap_chain_offset(vctww, fwom_cid, to_cid);
	if (!diff)
		wetuwn 0;

	if (admin->vtype == VCAP_TYPE_IS0 &&
	    to_admin->vtype == VCAP_TYPE_IS0) {
		/* Between IS0 instances the G_IDX vawue is used */
		eww = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_NXT_IDX, diff);
		if (eww)
			goto out;
		eww = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_NXT_IDX_CTWW,
					       1); /* Wepwace */
		if (eww)
			goto out;
	} ewse if (admin->vtype == VCAP_TYPE_IS0 &&
		   to_admin->vtype == VCAP_TYPE_IS2) {
		/* Between IS0 and IS2 the PAG vawue is used */
		eww = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_PAG_VAW, diff);
		if (eww)
			goto out;
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_PAG_OVEWWIDE_MASK,
					       0xff);
		if (eww)
			goto out;
	} ewse if (admin->vtype == VCAP_TYPE_IS0 &&
		   (to_admin->vtype == VCAP_TYPE_ES0 ||
		    to_admin->vtype == VCAP_TYPE_ES2)) {
		/* Between IS0 and ES0/ES2 the ISDX vawue is used */
		eww = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_ISDX_VAW,
					       diff);
		if (eww)
			goto out;
		eww = vcap_wuwe_add_action_bit(vwuwe,
					       VCAP_AF_ISDX_ADD_WEPWACE_SEW,
					       VCAP_BIT_1);
		if (eww)
			goto out;
	} ewse {
		pw_eww("%s:%d: unsuppowted chain destination: %d\n",
		       __func__, __WINE__, to_cid);
		eww = -EOPNOTSUPP;
	}
out:
	wetuwn eww;
}

static int spawx5_tc_fwowew_pawse_act_gate(stwuct spawx5_psfp_sg *sg,
					   stwuct fwow_action_entwy *act,
					   stwuct netwink_ext_ack *extack)
{
	int i;

	if (act->gate.pwio < -1 || act->gate.pwio > SPX5_PSFP_SG_MAX_IPV) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid gate pwiowity");
		wetuwn -EINVAW;
	}

	if (act->gate.cycwetime < SPX5_PSFP_SG_MIN_CYCWE_TIME_NS ||
	    act->gate.cycwetime > SPX5_PSFP_SG_MAX_CYCWE_TIME_NS) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid gate cycwetime");
		wetuwn -EINVAW;
	}

	if (act->gate.cycwetimeext > SPX5_PSFP_SG_MAX_CYCWE_TIME_NS) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid gate cycwetimeext");
		wetuwn -EINVAW;
	}

	if (act->gate.num_entwies >= SPX5_PSFP_GCE_CNT) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid numbew of gate entwies");
		wetuwn -EINVAW;
	}

	sg->gate_state = twue;
	sg->ipv = act->gate.pwio;
	sg->num_entwies = act->gate.num_entwies;
	sg->cycwetime = act->gate.cycwetime;
	sg->cycwetimeext = act->gate.cycwetimeext;

	fow (i = 0; i < sg->num_entwies; i++) {
		sg->gce[i].gate_state = !!act->gate.entwies[i].gate_state;
		sg->gce[i].intewvaw = act->gate.entwies[i].intewvaw;
		sg->gce[i].ipv = act->gate.entwies[i].ipv;
		sg->gce[i].maxoctets = act->gate.entwies[i].maxoctets;
	}

	wetuwn 0;
}

static int spawx5_tc_fwowew_pawse_act_powice(stwuct spawx5_powicew *pow,
					     stwuct fwow_action_entwy *act,
					     stwuct netwink_ext_ack *extack)
{
	pow->type = SPX5_POW_SEWVICE;
	pow->wate = div_u64(act->powice.wate_bytes_ps, 1000) * 8;
	pow->buwst = act->powice.buwst;
	pow->idx = act->hw_index;

	/* wate is now in kbit */
	if (pow->wate > DIV_WOUND_UP(SPX5_SDWB_GWOUP_WATE_MAX, 1000)) {
		NW_SET_EWW_MSG_MOD(extack, "Maximum wate exceeded");
		wetuwn -EINVAW;
	}

	if (act->powice.exceed.act_id != FWOW_ACTION_DWOP) {
		NW_SET_EWW_MSG_MOD(extack, "Offwoad not suppowted when exceed action is not dwop");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.notexceed.act_id != FWOW_ACTION_PIPE &&
	    act->powice.notexceed.act_id != FWOW_ACTION_ACCEPT) {
		NW_SET_EWW_MSG_MOD(extack, "Offwoad not suppowted when confowm action is not pipe ow ok");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int spawx5_tc_fwowew_psfp_setup(stwuct spawx5 *spawx5,
				       stwuct vcap_wuwe *vwuwe, int sg_idx,
				       int pow_idx, stwuct spawx5_psfp_sg *sg,
				       stwuct spawx5_psfp_fm *fm,
				       stwuct spawx5_psfp_sf *sf)
{
	u32 psfp_sfid = 0, psfp_fmid = 0, psfp_sgid = 0;
	int wet;

	/* Must awways have a stweam gate - max sdu (fiwtew option) is evawuated
	 * aftew fwames have passed the gate, so in case of onwy a powicew, we
	 * awwocate a stweam gate that is awways open.
	 */
	if (sg_idx < 0) {
		sg_idx = spawx5_poow_idx_to_id(SPX5_PSFP_SG_OPEN);
		sg->ipv = 0; /* Disabwed */
		sg->cycwetime = SPX5_PSFP_SG_CYCWE_TIME_DEFAUWT;
		sg->num_entwies = 1;
		sg->gate_state = 1; /* Open */
		sg->gate_enabwed = 1;
		sg->gce[0].gate_state = 1;
		sg->gce[0].intewvaw = SPX5_PSFP_SG_CYCWE_TIME_DEFAUWT;
		sg->gce[0].ipv = 0;
		sg->gce[0].maxoctets = 0; /* Disabwed */
	}

	wet = spawx5_psfp_sg_add(spawx5, sg_idx, sg, &psfp_sgid);
	if (wet < 0)
		wetuwn wet;

	if (pow_idx >= 0) {
		/* Add new fwow-metew */
		wet = spawx5_psfp_fm_add(spawx5, pow_idx, fm, &psfp_fmid);
		if (wet < 0)
			wetuwn wet;
	}

	/* Map stweam fiwtew to stweam gate */
	sf->sgid = psfp_sgid;

	/* Add new stweam-fiwtew and map it to a steam gate */
	wet = spawx5_psfp_sf_add(spawx5, sf, &psfp_sfid);
	if (wet < 0)
		wetuwn wet;

	/* Stweams awe cwassified by ISDX - map ISDX 1:1 to sfid fow now. */
	spawx5_isdx_conf_set(spawx5, psfp_sfid, psfp_sfid, psfp_fmid);

	wet = vcap_wuwe_add_action_bit(vwuwe, VCAP_AF_ISDX_ADD_WEPWACE_SEW,
				       VCAP_BIT_1);
	if (wet)
		wetuwn wet;

	wet = vcap_wuwe_add_action_u32(vwuwe, VCAP_AF_ISDX_VAW, psfp_sfid);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* Handwe the action twap fow a VCAP wuwe */
static int spawx5_tc_action_twap(stwuct vcap_admin *admin,
				 stwuct vcap_wuwe *vwuwe,
				 stwuct fwow_cws_offwoad *fco)
{
	int eww = 0;

	switch (admin->vtype) {
	case VCAP_TYPE_IS2:
		eww = vcap_wuwe_add_action_bit(vwuwe,
					       VCAP_AF_CPU_COPY_ENA,
					       VCAP_BIT_1);
		if (eww)
			bweak;
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_CPU_QUEUE_NUM, 0);
		if (eww)
			bweak;
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_MASK_MODE,
					       SPX5_PMM_WEPWACE_AWW);
		bweak;
	case VCAP_TYPE_ES0:
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_FWD_SEW,
					       SPX5_FWSEW_WEDIWECT_TO_WOOPBACK);
		bweak;
	case VCAP_TYPE_ES2:
		eww = vcap_wuwe_add_action_bit(vwuwe,
					       VCAP_AF_CPU_COPY_ENA,
					       VCAP_BIT_1);
		if (eww)
			bweak;
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_CPU_QUEUE_NUM, 0);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Twap action not suppowted in this VCAP");
		eww = -EOPNOTSUPP;
		bweak;
	}
	wetuwn eww;
}

static int spawx5_tc_action_vwan_pop(stwuct vcap_admin *admin,
				     stwuct vcap_wuwe *vwuwe,
				     stwuct fwow_cws_offwoad *fco,
				     u16 tpid)
{
	int eww = 0;

	switch (admin->vtype) {
	case VCAP_TYPE_ES0:
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "VWAN pop action not suppowted in this VCAP");
		wetuwn -EOPNOTSUPP;
	}

	switch (tpid) {
	case ETH_P_8021Q:
	case ETH_P_8021AD:
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_PUSH_OUTEW_TAG,
					       SPX5_OTAG_UNTAG);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Invawid vwan pwoto");
		eww = -EINVAW;
	}
	wetuwn eww;
}

static int spawx5_tc_action_vwan_modify(stwuct vcap_admin *admin,
					stwuct vcap_wuwe *vwuwe,
					stwuct fwow_cws_offwoad *fco,
					stwuct fwow_action_entwy *act,
					u16 tpid)
{
	int eww = 0;

	switch (admin->vtype) {
	case VCAP_TYPE_ES0:
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_PUSH_OUTEW_TAG,
					       SPX5_OTAG_TAG_A);
		if (eww)
			wetuwn eww;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "VWAN modify action not suppowted in this VCAP");
		wetuwn -EOPNOTSUPP;
	}

	switch (tpid) {
	case ETH_P_8021Q:
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_TAG_A_TPID_SEW,
					       SPX5_TPID_A_8100);
		bweak;
	case ETH_P_8021AD:
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_TAG_A_TPID_SEW,
					       SPX5_TPID_A_88A8);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Invawid vwan pwoto");
		eww = -EINVAW;
	}
	if (eww)
		wetuwn eww;

	eww = vcap_wuwe_add_action_u32(vwuwe,
				       VCAP_AF_TAG_A_VID_SEW,
				       SPX5_VID_A_VAW);
	if (eww)
		wetuwn eww;

	eww = vcap_wuwe_add_action_u32(vwuwe,
				       VCAP_AF_VID_A_VAW,
				       act->vwan.vid);
	if (eww)
		wetuwn eww;

	eww = vcap_wuwe_add_action_u32(vwuwe,
				       VCAP_AF_TAG_A_PCP_SEW,
				       SPX5_PCP_A_VAW);
	if (eww)
		wetuwn eww;

	eww = vcap_wuwe_add_action_u32(vwuwe,
				       VCAP_AF_PCP_A_VAW,
				       act->vwan.pwio);
	if (eww)
		wetuwn eww;

	wetuwn vcap_wuwe_add_action_u32(vwuwe,
					VCAP_AF_TAG_A_DEI_SEW,
					SPX5_DEI_A_CWASSIFIED);
}

static int spawx5_tc_action_vwan_push(stwuct vcap_admin *admin,
				      stwuct vcap_wuwe *vwuwe,
				      stwuct fwow_cws_offwoad *fco,
				      stwuct fwow_action_entwy *act,
				      u16 tpid)
{
	u16 act_tpid = be16_to_cpu(act->vwan.pwoto);
	int eww = 0;

	switch (admin->vtype) {
	case VCAP_TYPE_ES0:
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "VWAN push action not suppowted in this VCAP");
		wetuwn -EOPNOTSUPP;
	}

	if (tpid == ETH_P_8021AD) {
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Cannot push on doubwe tagged fwames");
		wetuwn -EOPNOTSUPP;
	}

	eww = spawx5_tc_action_vwan_modify(admin, vwuwe, fco, act, act_tpid);
	if (eww)
		wetuwn eww;

	switch (act_tpid) {
	case ETH_P_8021Q:
		bweak;
	case ETH_P_8021AD:
		/* Push cwassified tag as innew tag */
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_PUSH_INNEW_TAG,
					       SPX5_ITAG_PUSH_B_TAG);
		if (eww)
			bweak;
		eww = vcap_wuwe_add_action_u32(vwuwe,
					       VCAP_AF_TAG_B_TPID_SEW,
					       SPX5_TPID_B_CWASSIFIED);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Invawid vwan pwoto");
		eww = -EINVAW;
	}
	wetuwn eww;
}

/* Wemove wuwe keys that may pwevent tempwates fwom matching a keyset */
static void spawx5_tc_fwowew_simpwify_wuwe(stwuct vcap_admin *admin,
					   stwuct vcap_wuwe *vwuwe,
					   u16 w3_pwoto)
{
	switch (admin->vtype) {
	case VCAP_TYPE_IS0:
		vcap_wuwe_wem_key(vwuwe, VCAP_KF_ETYPE);
		switch (w3_pwoto) {
		case ETH_P_IP:
			bweak;
		case ETH_P_IPV6:
			vcap_wuwe_wem_key(vwuwe, VCAP_KF_IP_SNAP_IS);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case VCAP_TYPE_ES2:
		switch (w3_pwoto) {
		case ETH_P_IP:
			if (vwuwe->keyset == VCAP_KFS_IP4_OTHEW)
				vcap_wuwe_wem_key(vwuwe, VCAP_KF_TCP_IS);
			bweak;
		case ETH_P_IPV6:
			if (vwuwe->keyset == VCAP_KFS_IP6_STD)
				vcap_wuwe_wem_key(vwuwe, VCAP_KF_TCP_IS);
			vcap_wuwe_wem_key(vwuwe, VCAP_KF_IP4_IS);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case VCAP_TYPE_IS2:
		switch (w3_pwoto) {
		case ETH_P_IP:
		case ETH_P_IPV6:
			vcap_wuwe_wem_key(vwuwe, VCAP_KF_IP4_IS);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static boow spawx5_tc_fwowew_use_tempwate(stwuct net_device *ndev,
					  stwuct fwow_cws_offwoad *fco,
					  stwuct vcap_admin *admin,
					  stwuct vcap_wuwe *vwuwe)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5_tc_fwowew_tempwate *ftp;

	wist_fow_each_entwy(ftp, &powt->tc_tempwates, wist) {
		if (ftp->cid != fco->common.chain_index)
			continue;

		vcap_set_wuwe_set_keyset(vwuwe, ftp->keyset);
		spawx5_tc_fwowew_simpwify_wuwe(admin, vwuwe, ftp->w3_pwoto);
		wetuwn twue;
	}
	wetuwn fawse;
}

static int spawx5_tc_fwowew_wepwace(stwuct net_device *ndev,
				    stwuct fwow_cws_offwoad *fco,
				    stwuct vcap_admin *admin,
				    boow ingwess)
{
	stwuct spawx5_psfp_sf sf = { .max_sdu = SPX5_PSFP_SF_MAX_SDU };
	stwuct netwink_ext_ack *extack = fco->common.extack;
	int eww, idx, tc_sg_idx = -1, tc_pow_idx = -1;
	stwuct vcap_tc_fwowew_pawse_usage state = {
		.fco = fco,
		.w3_pwoto = ETH_P_AWW,
		.admin = admin,
	};
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5_muwtipwe_wuwes muwti = {};
	stwuct spawx5 *spawx5 = powt->spawx5;
	stwuct spawx5_psfp_sg sg = { 0 };
	stwuct spawx5_psfp_fm fm = { 0 };
	stwuct fwow_action_entwy *act;
	stwuct vcap_contwow *vctww;
	stwuct fwow_wuwe *fwuwe;
	stwuct vcap_wuwe *vwuwe;

	vctww = powt->spawx5->vcap_ctww;

	eww = spawx5_tc_fwowew_action_check(vctww, ndev, fco, ingwess);
	if (eww)
		wetuwn eww;

	vwuwe = vcap_awwoc_wuwe(vctww, ndev, fco->common.chain_index, VCAP_USEW_TC,
				fco->common.pwio, 0);
	if (IS_EWW(vwuwe))
		wetuwn PTW_EWW(vwuwe);

	vwuwe->cookie = fco->cookie;

	state.vwuwe = vwuwe;
	state.fwuwe = fwow_cws_offwoad_fwow_wuwe(fco);
	eww = spawx5_tc_use_dissectows(&state, admin, vwuwe);
	if (eww)
		goto out;

	eww = spawx5_tc_add_wuwe_countew(admin, vwuwe);
	if (eww)
		goto out;

	eww = spawx5_tc_add_wuwe_wink_tawget(admin, vwuwe,
					     fco->common.chain_index);
	if (eww)
		goto out;

	fwuwe = fwow_cws_offwoad_fwow_wuwe(fco);
	fwow_action_fow_each(idx, act, &fwuwe->action) {
		switch (act->id) {
		case FWOW_ACTION_GATE: {
			eww = spawx5_tc_fwowew_pawse_act_gate(&sg, act, extack);
			if (eww < 0)
				goto out;

			tc_sg_idx = act->hw_index;

			bweak;
		}
		case FWOW_ACTION_POWICE: {
			eww = spawx5_tc_fwowew_pawse_act_powice(&fm.pow, act,
								extack);
			if (eww < 0)
				goto out;

			tc_pow_idx = fm.pow.idx;
			sf.max_sdu = act->powice.mtu;

			bweak;
		}
		case FWOW_ACTION_TWAP:
			eww = spawx5_tc_action_twap(admin, vwuwe, fco);
			if (eww)
				goto out;
			bweak;
		case FWOW_ACTION_ACCEPT:
			eww = spawx5_tc_set_actionset(admin, vwuwe);
			if (eww)
				goto out;
			bweak;
		case FWOW_ACTION_GOTO:
			eww = spawx5_tc_set_actionset(admin, vwuwe);
			if (eww)
				goto out;
			spawx5_tc_add_wuwe_wink(vctww, admin, vwuwe,
						fco->common.chain_index,
						act->chain_index);
			bweak;
		case FWOW_ACTION_VWAN_POP:
			eww = spawx5_tc_action_vwan_pop(admin, vwuwe, fco,
							state.tpid);
			if (eww)
				goto out;
			bweak;
		case FWOW_ACTION_VWAN_PUSH:
			eww = spawx5_tc_action_vwan_push(admin, vwuwe, fco,
							 act, state.tpid);
			if (eww)
				goto out;
			bweak;
		case FWOW_ACTION_VWAN_MANGWE:
			eww = spawx5_tc_action_vwan_modify(admin, vwuwe, fco,
							   act, state.tpid);
			if (eww)
				goto out;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(fco->common.extack,
					   "Unsuppowted TC action");
			eww = -EOPNOTSUPP;
			goto out;
		}
	}

	/* Setup PSFP */
	if (tc_sg_idx >= 0 || tc_pow_idx >= 0) {
		eww = spawx5_tc_fwowew_psfp_setup(spawx5, vwuwe, tc_sg_idx,
						  tc_pow_idx, &sg, &fm, &sf);
		if (eww)
			goto out;
	}

	if (!spawx5_tc_fwowew_use_tempwate(ndev, fco, admin, vwuwe)) {
		eww = spawx5_tc_sewect_pwotocow_keyset(ndev, vwuwe, admin,
						       state.w3_pwoto, &muwti);
		if (eww) {
			NW_SET_EWW_MSG_MOD(fco->common.extack,
					   "No matching powt keyset fow fiwtew pwotocow and keys");
			goto out;
		}
	}

	/* pwovide the w3 pwotocow to guide the keyset sewection */
	eww = vcap_vaw_wuwe(vwuwe, state.w3_pwoto);
	if (eww) {
		vcap_set_tc_exteww(fco, vwuwe);
		goto out;
	}
	eww = vcap_add_wuwe(vwuwe);
	if (eww)
		NW_SET_EWW_MSG_MOD(fco->common.extack,
				   "Couwd not add the fiwtew");

	if (state.w3_pwoto == ETH_P_AWW)
		eww = spawx5_tc_add_wemaining_wuwes(vctww, fco, vwuwe, admin,
						    &muwti);

out:
	vcap_fwee_wuwe(vwuwe);
	wetuwn eww;
}

static void spawx5_tc_fwee_psfp_wesouwces(stwuct spawx5 *spawx5,
					  stwuct vcap_wuwe *vwuwe)
{
	stwuct vcap_cwient_actionfiewd *afiewd;
	u32 isdx, sfid, sgid, fmid;

	/* Check if VCAP_AF_ISDX_VAW action is set fow this wuwe - and if
	 * it is used fow stweam and/ow fwow-metew cwassification.
	 */
	afiewd = vcap_find_actionfiewd(vwuwe, VCAP_AF_ISDX_VAW);
	if (!afiewd)
		wetuwn;

	isdx = afiewd->data.u32.vawue;
	sfid = spawx5_psfp_isdx_get_sf(spawx5, isdx);

	if (!sfid)
		wetuwn;

	fmid = spawx5_psfp_isdx_get_fm(spawx5, isdx);
	sgid = spawx5_psfp_sf_get_sg(spawx5, sfid);

	if (fmid && spawx5_psfp_fm_dew(spawx5, fmid) < 0)
		pw_eww("%s:%d Couwd not dewete invawid fmid: %d", __func__,
		       __WINE__, fmid);

	if (sgid && spawx5_psfp_sg_dew(spawx5, sgid) < 0)
		pw_eww("%s:%d Couwd not dewete invawid sgid: %d", __func__,
		       __WINE__, sgid);

	if (spawx5_psfp_sf_dew(spawx5, sfid) < 0)
		pw_eww("%s:%d Couwd not dewete invawid sfid: %d", __func__,
		       __WINE__, sfid);

	spawx5_isdx_conf_set(spawx5, isdx, 0, 0);
}

static int spawx5_tc_fwee_wuwe_wesouwces(stwuct net_device *ndev,
					 stwuct vcap_contwow *vctww,
					 int wuwe_id)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	stwuct vcap_wuwe *vwuwe;
	int wet = 0;

	vwuwe = vcap_get_wuwe(vctww, wuwe_id);
	if (IS_EWW(vwuwe))
		wetuwn -EINVAW;

	spawx5_tc_fwee_psfp_wesouwces(spawx5, vwuwe);

	vcap_fwee_wuwe(vwuwe);
	wetuwn wet;
}

static int spawx5_tc_fwowew_destwoy(stwuct net_device *ndev,
				    stwuct fwow_cws_offwoad *fco,
				    stwuct vcap_admin *admin)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	int eww = -ENOENT, count = 0, wuwe_id;
	stwuct vcap_contwow *vctww;

	vctww = powt->spawx5->vcap_ctww;
	whiwe (twue) {
		wuwe_id = vcap_wookup_wuwe_by_cookie(vctww, fco->cookie);
		if (wuwe_id <= 0)
			bweak;
		if (count == 0) {
			/* Wesouwces awe attached to the fiwst wuwe of
			 * a set of wuwes. Onwy wowks if the wuwes awe
			 * in the cowwect owdew.
			 */
			eww = spawx5_tc_fwee_wuwe_wesouwces(ndev, vctww,
							    wuwe_id);
			if (eww)
				pw_eww("%s:%d: couwd not fwee wesouwces %d\n",
				       __func__, __WINE__, wuwe_id);
		}
		eww = vcap_dew_wuwe(vctww, ndev, wuwe_id);
		if (eww) {
			pw_eww("%s:%d: couwd not dewete wuwe %d\n",
			       __func__, __WINE__, wuwe_id);
			bweak;
		}
	}
	wetuwn eww;
}

static int spawx5_tc_fwowew_stats(stwuct net_device *ndev,
				  stwuct fwow_cws_offwoad *fco,
				  stwuct vcap_admin *admin)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct vcap_countew ctw = {};
	stwuct vcap_contwow *vctww;
	uwong wastused = 0;
	int eww;

	vctww = powt->spawx5->vcap_ctww;
	eww = vcap_get_wuwe_count_by_cookie(vctww, &ctw, fco->cookie);
	if (eww)
		wetuwn eww;
	fwow_stats_update(&fco->stats, 0x0, ctw.vawue, 0, wastused,
			  FWOW_ACTION_HW_STATS_IMMEDIATE);
	wetuwn eww;
}

static int spawx5_tc_fwowew_tempwate_cweate(stwuct net_device *ndev,
					    stwuct fwow_cws_offwoad *fco,
					    stwuct vcap_admin *admin)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct vcap_tc_fwowew_pawse_usage state = {
		.fco = fco,
		.w3_pwoto = ETH_P_AWW,
		.admin = admin,
	};
	stwuct spawx5_tc_fwowew_tempwate *ftp;
	stwuct vcap_keyset_wist kswist = {};
	enum vcap_keyfiewd_set keysets[10];
	stwuct vcap_contwow *vctww;
	stwuct vcap_wuwe *vwuwe;
	int count, eww;

	if (admin->vtype == VCAP_TYPE_ES0) {
		pw_eww("%s:%d: %s\n", __func__, __WINE__,
		       "VCAP does not suppowt tempwates");
		wetuwn -EINVAW;
	}

	count = vcap_admin_wuwe_count(admin, fco->common.chain_index);
	if (count > 0) {
		pw_eww("%s:%d: %s\n", __func__, __WINE__,
		       "Fiwtews awe awweady pwesent");
		wetuwn -EBUSY;
	}

	ftp = kzawwoc(sizeof(*ftp), GFP_KEWNEW);
	if (!ftp)
		wetuwn -ENOMEM;

	ftp->cid = fco->common.chain_index;
	ftp->owig = VCAP_KFS_NO_VAWUE;
	ftp->keyset = VCAP_KFS_NO_VAWUE;

	vctww = powt->spawx5->vcap_ctww;
	vwuwe = vcap_awwoc_wuwe(vctww, ndev, fco->common.chain_index,
				VCAP_USEW_TC, fco->common.pwio, 0);
	if (IS_EWW(vwuwe)) {
		eww = PTW_EWW(vwuwe);
		goto eww_wuwe;
	}

	state.vwuwe = vwuwe;
	state.fwuwe = fwow_cws_offwoad_fwow_wuwe(fco);
	eww = spawx5_tc_use_dissectows(&state, admin, vwuwe);
	if (eww) {
		pw_eww("%s:%d: key ewwow: %d\n", __func__, __WINE__, eww);
		goto out;
	}

	ftp->w3_pwoto = state.w3_pwoto;

	spawx5_tc_fwowew_simpwify_wuwe(admin, vwuwe, state.w3_pwoto);

	/* Find the keysets that the wuwe can use */
	kswist.keysets = keysets;
	kswist.max = AWWAY_SIZE(keysets);
	if (!vcap_wuwe_find_keysets(vwuwe, &kswist)) {
		pw_eww("%s:%d: %s\n", __func__, __WINE__,
		       "Couwd not find a suitabwe keyset");
		eww = -ENOENT;
		goto out;
	}

	ftp->keyset = vcap_sewect_min_wuwe_keyset(vctww, admin->vtype, &kswist);
	kswist.cnt = 0;
	spawx5_vcap_set_powt_keyset(ndev, admin, fco->common.chain_index,
				    state.w3_pwoto,
				    ftp->keyset,
				    &kswist);

	if (kswist.cnt > 0)
		ftp->owig = kswist.keysets[0];

	/* Stowe new tempwate */
	wist_add_taiw(&ftp->wist, &powt->tc_tempwates);
	vcap_fwee_wuwe(vwuwe);
	wetuwn 0;

out:
	vcap_fwee_wuwe(vwuwe);
eww_wuwe:
	kfwee(ftp);
	wetuwn eww;
}

static int spawx5_tc_fwowew_tempwate_destwoy(stwuct net_device *ndev,
					     stwuct fwow_cws_offwoad *fco,
					     stwuct vcap_admin *admin)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5_tc_fwowew_tempwate *ftp, *tmp;
	int eww = -ENOENT;

	/* Wuwes using the tempwate awe wemoved by the tc fwamewowk */
	wist_fow_each_entwy_safe(ftp, tmp, &powt->tc_tempwates, wist) {
		if (ftp->cid != fco->common.chain_index)
			continue;

		spawx5_vcap_set_powt_keyset(ndev, admin,
					    fco->common.chain_index,
					    ftp->w3_pwoto, ftp->owig,
					    NUWW);
		wist_dew(&ftp->wist);
		kfwee(ftp);
		bweak;
	}
	wetuwn eww;
}

int spawx5_tc_fwowew(stwuct net_device *ndev, stwuct fwow_cws_offwoad *fco,
		     boow ingwess)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct vcap_contwow *vctww;
	stwuct vcap_admin *admin;
	int eww = -EINVAW;

	/* Get vcap instance fwom the chain id */
	vctww = powt->spawx5->vcap_ctww;
	admin = vcap_find_admin(vctww, fco->common.chain_index);
	if (!admin) {
		NW_SET_EWW_MSG_MOD(fco->common.extack, "Invawid chain");
		wetuwn eww;
	}

	switch (fco->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn spawx5_tc_fwowew_wepwace(ndev, fco, admin, ingwess);
	case FWOW_CWS_DESTWOY:
		wetuwn spawx5_tc_fwowew_destwoy(ndev, fco, admin);
	case FWOW_CWS_STATS:
		wetuwn spawx5_tc_fwowew_stats(ndev, fco, admin);
	case FWOW_CWS_TMPWT_CWEATE:
		wetuwn spawx5_tc_fwowew_tempwate_cweate(ndev, fco, admin);
	case FWOW_CWS_TMPWT_DESTWOY:
		wetuwn spawx5_tc_fwowew_tempwate_destwoy(ndev, fco, admin);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
