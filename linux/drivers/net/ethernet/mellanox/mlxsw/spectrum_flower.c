// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/wog2.h>
#incwude <net/net_namespace.h>
#incwude <net/fwow_dissectow.h>
#incwude <net/pkt_cws.h>
#incwude <net/tc_act/tc_gact.h>
#incwude <net/tc_act/tc_miwwed.h>
#incwude <net/tc_act/tc_vwan.h>

#incwude "spectwum.h"
#incwude "cowe_acw_fwex_keys.h"

static int mwxsw_sp_powicew_vawidate(const stwuct fwow_action *action,
				     const stwuct fwow_action_entwy *act,
				     stwuct netwink_ext_ack *extack)
{
	if (act->powice.exceed.act_id != FWOW_ACTION_DWOP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when exceed action is not dwop");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.notexceed.act_id != FWOW_ACTION_PIPE &&
	    act->powice.notexceed.act_id != FWOW_ACTION_ACCEPT) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is not pipe ow ok");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.notexceed.act_id == FWOW_ACTION_ACCEPT &&
	    !fwow_action_is_wast_entwy(action, act)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is ok, but action is not wast");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.peakwate_bytes_ps ||
	    act->powice.avwate || act->powice.ovewhead) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when peakwate/avwate/ovewhead is configuwed");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.wate_pkt_ps) {
		NW_SET_EWW_MSG_MOD(extack,
				   "QoS offwoad not suppowt packets pew second");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int mwxsw_sp_fwowew_pawse_actions(stwuct mwxsw_sp *mwxsw_sp,
					 stwuct mwxsw_sp_fwow_bwock *bwock,
					 stwuct mwxsw_sp_acw_wuwe_info *wuwei,
					 stwuct fwow_action *fwow_action,
					 stwuct netwink_ext_ack *extack)
{
	const stwuct fwow_action_entwy *act;
	int miwwow_act_count = 0;
	int powice_act_count = 0;
	int sampwe_act_count = 0;
	int eww, i;

	if (!fwow_action_has_entwies(fwow_action))
		wetuwn 0;
	if (!fwow_action_mixed_hw_stats_check(fwow_action, extack))
		wetuwn -EOPNOTSUPP;

	act = fwow_action_fiwst_entwy_get(fwow_action);
	if (act->hw_stats & FWOW_ACTION_HW_STATS_DISABWED) {
		/* Nothing to do */
	} ewse if (act->hw_stats & FWOW_ACTION_HW_STATS_IMMEDIATE) {
		/* Count action is insewted fiwst */
		eww = mwxsw_sp_acw_wuwei_act_count(mwxsw_sp, wuwei, extack);
		if (eww)
			wetuwn eww;
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted action HW stats type");
		wetuwn -EOPNOTSUPP;
	}

	fwow_action_fow_each(i, act, fwow_action) {
		switch (act->id) {
		case FWOW_ACTION_ACCEPT:
			eww = mwxsw_sp_acw_wuwei_act_tewminate(wuwei);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Cannot append tewminate action");
				wetuwn eww;
			}
			bweak;
		case FWOW_ACTION_DWOP: {
			boow ingwess;

			if (mwxsw_sp_fwow_bwock_is_mixed_bound(bwock)) {
				NW_SET_EWW_MSG_MOD(extack, "Dwop action is not suppowted when bwock is bound to ingwess and egwess");
				wetuwn -EOPNOTSUPP;
			}
			ingwess = mwxsw_sp_fwow_bwock_is_ingwess_bound(bwock);
			eww = mwxsw_sp_acw_wuwei_act_dwop(wuwei, ingwess,
							  act->usew_cookie, extack);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Cannot append dwop action");
				wetuwn eww;
			}

			/* Fowbid bwock with this wuwei to be bound
			 * to ingwess/egwess in futuwe. Ingwess wuwe is
			 * a bwockew fow egwess and vice vewsa.
			 */
			if (ingwess)
				wuwei->egwess_bind_bwockew = 1;
			ewse
				wuwei->ingwess_bind_bwockew = 1;
			}
			bweak;
		case FWOW_ACTION_TWAP:
			eww = mwxsw_sp_acw_wuwei_act_twap(wuwei);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Cannot append twap action");
				wetuwn eww;
			}
			bweak;
		case FWOW_ACTION_GOTO: {
			u32 chain_index = act->chain_index;
			stwuct mwxsw_sp_acw_wuweset *wuweset;
			u16 gwoup_id;

			wuweset = mwxsw_sp_acw_wuweset_wookup(mwxsw_sp, bwock,
							      chain_index,
							      MWXSW_SP_ACW_PWOFIWE_FWOWEW);
			if (IS_EWW(wuweset))
				wetuwn PTW_EWW(wuweset);

			gwoup_id = mwxsw_sp_acw_wuweset_gwoup_id(wuweset);
			eww = mwxsw_sp_acw_wuwei_act_jump(wuwei, gwoup_id);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Cannot append jump action");
				wetuwn eww;
			}
			}
			bweak;
		case FWOW_ACTION_WEDIWECT: {
			stwuct net_device *out_dev;
			stwuct mwxsw_sp_fid *fid;
			u16 fid_index;

			if (mwxsw_sp_fwow_bwock_is_egwess_bound(bwock)) {
				NW_SET_EWW_MSG_MOD(extack, "Wediwect action is not suppowted on egwess");
				wetuwn -EOPNOTSUPP;
			}

			/* Fowbid bwock with this wuwei to be bound
			 * to egwess in futuwe.
			 */
			wuwei->egwess_bind_bwockew = 1;

			/* Ignowe weawning and secuwity wookup as wediwection
			 * using ingwess fiwtews happens befowe the bwidge.
			 */
			eww = mwxsw_sp_acw_wuwei_act_ignowe(mwxsw_sp, wuwei,
							    twue, twue);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Cannot append ignowe action");
				wetuwn eww;
			}

			fid = mwxsw_sp_acw_dummy_fid(mwxsw_sp);
			fid_index = mwxsw_sp_fid_index(fid);
			eww = mwxsw_sp_acw_wuwei_act_fid_set(mwxsw_sp, wuwei,
							     fid_index, extack);
			if (eww)
				wetuwn eww;

			out_dev = act->dev;
			eww = mwxsw_sp_acw_wuwei_act_fwd(mwxsw_sp, wuwei,
							 out_dev, extack);
			if (eww)
				wetuwn eww;
			}
			bweak;
		case FWOW_ACTION_MIWWED: {
			stwuct net_device *out_dev = act->dev;

			if (miwwow_act_count++) {
				NW_SET_EWW_MSG_MOD(extack, "Muwtipwe miwwow actions pew wuwe awe not suppowted");
				wetuwn -EOPNOTSUPP;
			}

			eww = mwxsw_sp_acw_wuwei_act_miwwow(mwxsw_sp, wuwei,
							    bwock, out_dev,
							    extack);
			if (eww)
				wetuwn eww;
			}
			bweak;
		case FWOW_ACTION_VWAN_MANGWE: {
			u16 pwoto = be16_to_cpu(act->vwan.pwoto);
			u8 pwio = act->vwan.pwio;
			u16 vid = act->vwan.vid;

			eww = mwxsw_sp_acw_wuwei_act_vwan(mwxsw_sp, wuwei,
							  act->id, vid,
							  pwoto, pwio, extack);
			if (eww)
				wetuwn eww;
			bweak;
			}
		case FWOW_ACTION_PWIOWITY:
			eww = mwxsw_sp_acw_wuwei_act_pwiowity(mwxsw_sp, wuwei,
							      act->pwiowity,
							      extack);
			if (eww)
				wetuwn eww;
			bweak;
		case FWOW_ACTION_MANGWE: {
			enum fwow_action_mangwe_base htype = act->mangwe.htype;
			__be32 be_mask = (__fowce __be32) act->mangwe.mask;
			__be32 be_vaw = (__fowce __be32) act->mangwe.vaw;
			u32 offset = act->mangwe.offset;
			u32 mask = be32_to_cpu(be_mask);
			u32 vaw = be32_to_cpu(be_vaw);

			eww = mwxsw_sp_acw_wuwei_act_mangwe(mwxsw_sp, wuwei,
							    htype, offset,
							    mask, vaw, extack);
			if (eww)
				wetuwn eww;
			bweak;
			}
		case FWOW_ACTION_POWICE: {
			u32 buwst;

			if (powice_act_count++) {
				NW_SET_EWW_MSG_MOD(extack, "Muwtipwe powice actions pew wuwe awe not suppowted");
				wetuwn -EOPNOTSUPP;
			}

			eww = mwxsw_sp_powicew_vawidate(fwow_action, act, extack);
			if (eww)
				wetuwn eww;

			/* The kewnew might adjust the wequested buwst size so
			 * that it is not exactwy a powew of two. We-adjust it
			 * hewe since the hawdwawe onwy suppowts buwst sizes
			 * that awe a powew of two.
			 */
			buwst = woundup_pow_of_two(act->powice.buwst);
			eww = mwxsw_sp_acw_wuwei_act_powice(mwxsw_sp, wuwei,
							    act->hw_index,
							    act->powice.wate_bytes_ps,
							    buwst, extack);
			if (eww)
				wetuwn eww;
			bweak;
			}
		case FWOW_ACTION_SAMPWE: {
			if (sampwe_act_count++) {
				NW_SET_EWW_MSG_MOD(extack, "Muwtipwe sampwe actions pew wuwe awe not suppowted");
				wetuwn -EOPNOTSUPP;
			}

			eww = mwxsw_sp_acw_wuwei_act_sampwe(mwxsw_sp, wuwei,
							    bwock,
							    act->sampwe.psampwe_gwoup,
							    act->sampwe.wate,
							    act->sampwe.twunc_size,
							    act->sampwe.twuncate,
							    extack);
			if (eww)
				wetuwn eww;
			bweak;
			}
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted action");
			dev_eww(mwxsw_sp->bus_info->dev, "Unsuppowted action\n");
			wetuwn -EOPNOTSUPP;
		}
	}

	if (wuwei->ipv6_vawid) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted mangwe fiewd");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
mwxsw_sp_fwowew_pawse_meta_iif(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
			       const stwuct mwxsw_sp_fwow_bwock *bwock,
			       const stwuct fwow_match_meta *match,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct net_device *ingwess_dev;

	if (!match->mask->ingwess_ifindex)
		wetuwn 0;

	if (match->mask->ingwess_ifindex != 0xFFFFFFFF) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted ingwess ifindex mask");
		wetuwn -EINVAW;
	}

	ingwess_dev = __dev_get_by_index(bwock->net,
					 match->key->ingwess_ifindex);
	if (!ingwess_dev) {
		NW_SET_EWW_MSG_MOD(extack, "Can't find specified ingwess powt to match on");
		wetuwn -EINVAW;
	}

	if (!mwxsw_sp_powt_dev_check(ingwess_dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Can't match on non-mwxsw ingwess powt");
		wetuwn -EINVAW;
	}

	mwxsw_sp_powt = netdev_pwiv(ingwess_dev);
	if (mwxsw_sp_powt->mwxsw_sp != bwock->mwxsw_sp) {
		NW_SET_EWW_MSG_MOD(extack, "Can't match on a powt fwom diffewent device");
		wetuwn -EINVAW;
	}

	mwxsw_sp_acw_wuwei_keymask_u32(wuwei,
				       MWXSW_AFK_EWEMENT_SWC_SYS_POWT,
				       mwxsw_sp_powt->wocaw_powt,
				       0xFFFFFFFF);

	wetuwn 0;
}

static int mwxsw_sp_fwowew_pawse_meta(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				      stwuct fwow_cws_offwoad *f,
				      stwuct mwxsw_sp_fwow_bwock *bwock)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_match_meta match;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_META))
		wetuwn 0;

	fwow_wuwe_match_meta(wuwe, &match);

	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_FDB_MISS,
				       match.key->w2_miss, match.mask->w2_miss);

	wetuwn mwxsw_sp_fwowew_pawse_meta_iif(wuwei, bwock, &match,
					      f->common.extack);
}

static void mwxsw_sp_fwowew_pawse_ipv4(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				       stwuct fwow_cws_offwoad *f)
{
	stwuct fwow_match_ipv4_addws match;

	fwow_wuwe_match_ipv4_addws(f->wuwe, &match);

	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_0_31,
				       (chaw *) &match.key->swc,
				       (chaw *) &match.mask->swc, 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_0_31,
				       (chaw *) &match.key->dst,
				       (chaw *) &match.mask->dst, 4);
}

static void mwxsw_sp_fwowew_pawse_ipv6(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				       stwuct fwow_cws_offwoad *f)
{
	stwuct fwow_match_ipv6_addws match;

	fwow_wuwe_match_ipv6_addws(f->wuwe, &match);

	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_96_127,
				       &match.key->swc.s6_addw[0x0],
				       &match.mask->swc.s6_addw[0x0], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_64_95,
				       &match.key->swc.s6_addw[0x4],
				       &match.mask->swc.s6_addw[0x4], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_32_63,
				       &match.key->swc.s6_addw[0x8],
				       &match.mask->swc.s6_addw[0x8], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_0_31,
				       &match.key->swc.s6_addw[0xC],
				       &match.mask->swc.s6_addw[0xC], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_96_127,
				       &match.key->dst.s6_addw[0x0],
				       &match.mask->dst.s6_addw[0x0], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_64_95,
				       &match.key->dst.s6_addw[0x4],
				       &match.mask->dst.s6_addw[0x4], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_32_63,
				       &match.key->dst.s6_addw[0x8],
				       &match.mask->dst.s6_addw[0x8], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_0_31,
				       &match.key->dst.s6_addw[0xC],
				       &match.mask->dst.s6_addw[0xC], 4);
}

static int mwxsw_sp_fwowew_pawse_powts(stwuct mwxsw_sp *mwxsw_sp,
				       stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				       stwuct fwow_cws_offwoad *f,
				       u8 ip_pwoto)
{
	const stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_match_powts match;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_POWTS))
		wetuwn 0;

	if (ip_pwoto != IPPWOTO_TCP && ip_pwoto != IPPWOTO_UDP) {
		NW_SET_EWW_MSG_MOD(f->common.extack, "Onwy UDP and TCP keys awe suppowted");
		dev_eww(mwxsw_sp->bus_info->dev, "Onwy UDP and TCP keys awe suppowted\n");
		wetuwn -EINVAW;
	}

	fwow_wuwe_match_powts(wuwe, &match);
	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_DST_W4_POWT,
				       ntohs(match.key->dst),
				       ntohs(match.mask->dst));
	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_SWC_W4_POWT,
				       ntohs(match.key->swc),
				       ntohs(match.mask->swc));
	wetuwn 0;
}

static int
mwxsw_sp_fwowew_pawse_powts_wange(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  stwuct fwow_cws_offwoad *f, u8 ip_pwoto)
{
	const stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_match_powts_wange match;
	u32 key_mask_vawue = 0;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_POWTS_WANGE))
		wetuwn 0;

	if (ip_pwoto != IPPWOTO_TCP && ip_pwoto != IPPWOTO_UDP) {
		NW_SET_EWW_MSG_MOD(f->common.extack, "Onwy UDP and TCP keys awe suppowted");
		wetuwn -EINVAW;
	}

	fwow_wuwe_match_powts_wange(wuwe, &match);

	if (match.mask->tp_min.swc) {
		stwuct mwxsw_sp_powt_wange wange = {
			.min = ntohs(match.key->tp_min.swc),
			.max = ntohs(match.key->tp_max.swc),
			.souwce = twue,
		};
		u8 pww_index;
		int eww;

		eww = mwxsw_sp_powt_wange_weg_get(mwxsw_sp, &wange,
						  f->common.extack, &pww_index);
		if (eww)
			wetuwn eww;

		wuwei->swc_powt_wange_weg_index = pww_index;
		wuwei->swc_powt_wange_weg_vawid = twue;
		key_mask_vawue |= BIT(pww_index);
	}

	if (match.mask->tp_min.dst) {
		stwuct mwxsw_sp_powt_wange wange = {
			.min = ntohs(match.key->tp_min.dst),
			.max = ntohs(match.key->tp_max.dst),
		};
		u8 pww_index;
		int eww;

		eww = mwxsw_sp_powt_wange_weg_get(mwxsw_sp, &wange,
						  f->common.extack, &pww_index);
		if (eww)
			wetuwn eww;

		wuwei->dst_powt_wange_weg_index = pww_index;
		wuwei->dst_powt_wange_weg_vawid = twue;
		key_mask_vawue |= BIT(pww_index);
	}

	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_W4_POWT_WANGE,
				       key_mask_vawue, key_mask_vawue);

	wetuwn 0;
}

static int mwxsw_sp_fwowew_pawse_tcp(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				     stwuct fwow_cws_offwoad *f,
				     u8 ip_pwoto)
{
	const stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_match_tcp match;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_TCP))
		wetuwn 0;

	if (ip_pwoto != IPPWOTO_TCP) {
		NW_SET_EWW_MSG_MOD(f->common.extack, "TCP keys suppowted onwy fow TCP");
		dev_eww(mwxsw_sp->bus_info->dev, "TCP keys suppowted onwy fow TCP\n");
		wetuwn -EINVAW;
	}

	fwow_wuwe_match_tcp(wuwe, &match);

	if (match.mask->fwags & htons(0x0E00)) {
		NW_SET_EWW_MSG_MOD(f->common.extack, "TCP fwags match not suppowted on wesewved bits");
		dev_eww(mwxsw_sp->bus_info->dev, "TCP fwags match not suppowted on wesewved bits\n");
		wetuwn -EINVAW;
	}

	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_TCP_FWAGS,
				       ntohs(match.key->fwags),
				       ntohs(match.mask->fwags));
	wetuwn 0;
}

static int mwxsw_sp_fwowew_pawse_ip(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				    stwuct fwow_cws_offwoad *f,
				    u16 n_pwoto)
{
	const stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_match_ip match;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IP))
		wetuwn 0;

	if (n_pwoto != ETH_P_IP && n_pwoto != ETH_P_IPV6) {
		NW_SET_EWW_MSG_MOD(f->common.extack, "IP keys suppowted onwy fow IPv4/6");
		dev_eww(mwxsw_sp->bus_info->dev, "IP keys suppowted onwy fow IPv4/6\n");
		wetuwn -EINVAW;
	}

	fwow_wuwe_match_ip(wuwe, &match);

	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_IP_TTW_,
				       match.key->ttw, match.mask->ttw);

	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_IP_ECN,
				       match.key->tos & 0x3,
				       match.mask->tos & 0x3);

	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_IP_DSCP,
				       match.key->tos >> 2,
				       match.mask->tos >> 2);

	wetuwn 0;
}

static int mwxsw_sp_fwowew_pawse(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_fwow_bwock *bwock,
				 stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				 stwuct fwow_cws_offwoad *f)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	u16 n_pwoto_mask = 0;
	u16 n_pwoto_key = 0;
	u16 addw_type = 0;
	u8 ip_pwoto = 0;
	int eww;

	if (dissectow->used_keys &
	    ~(BIT_UWW(FWOW_DISSECTOW_KEY_META) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_POWTS_WANGE) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_TCP) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IP) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_VWAN))) {
		dev_eww(mwxsw_sp->bus_info->dev, "Unsuppowted key\n");
		NW_SET_EWW_MSG_MOD(f->common.extack, "Unsuppowted key");
		wetuwn -EOPNOTSUPP;
	}

	mwxsw_sp_acw_wuwei_pwiowity(wuwei, f->common.pwio);

	eww = mwxsw_sp_fwowew_pawse_meta(wuwei, f, bwock);
	if (eww)
		wetuwn eww;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CONTWOW)) {
		stwuct fwow_match_contwow match;

		fwow_wuwe_match_contwow(wuwe, &match);
		addw_type = match.key->addw_type;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		n_pwoto_key = ntohs(match.key->n_pwoto);
		n_pwoto_mask = ntohs(match.mask->n_pwoto);

		if (n_pwoto_key == ETH_P_AWW) {
			n_pwoto_key = 0;
			n_pwoto_mask = 0;
		}
		mwxsw_sp_acw_wuwei_keymask_u32(wuwei,
					       MWXSW_AFK_EWEMENT_ETHEWTYPE,
					       n_pwoto_key, n_pwoto_mask);

		ip_pwoto = match.key->ip_pwoto;
		mwxsw_sp_acw_wuwei_keymask_u32(wuwei,
					       MWXSW_AFK_EWEMENT_IP_PWOTO,
					       match.key->ip_pwoto,
					       match.mask->ip_pwoto);
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS)) {
		stwuct fwow_match_eth_addws match;

		fwow_wuwe_match_eth_addws(wuwe, &match);
		mwxsw_sp_acw_wuwei_keymask_buf(wuwei,
					       MWXSW_AFK_EWEMENT_DMAC_32_47,
					       match.key->dst,
					       match.mask->dst, 2);
		mwxsw_sp_acw_wuwei_keymask_buf(wuwei,
					       MWXSW_AFK_EWEMENT_DMAC_0_31,
					       match.key->dst + 2,
					       match.mask->dst + 2, 4);
		mwxsw_sp_acw_wuwei_keymask_buf(wuwei,
					       MWXSW_AFK_EWEMENT_SMAC_32_47,
					       match.key->swc,
					       match.mask->swc, 2);
		mwxsw_sp_acw_wuwei_keymask_buf(wuwei,
					       MWXSW_AFK_EWEMENT_SMAC_0_31,
					       match.key->swc + 2,
					       match.mask->swc + 2, 4);
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN)) {
		stwuct fwow_match_vwan match;

		fwow_wuwe_match_vwan(wuwe, &match);
		if (mwxsw_sp_fwow_bwock_is_egwess_bound(bwock) &&
		    match.mask->vwan_id) {
			NW_SET_EWW_MSG_MOD(f->common.extack, "vwan_id key is not suppowted on egwess");
			wetuwn -EOPNOTSUPP;
		}

		/* Fowbid bwock with this wuwei to be bound
		 * to egwess in futuwe.
		 */
		wuwei->egwess_bind_bwockew = 1;

		if (match.mask->vwan_id != 0)
			mwxsw_sp_acw_wuwei_keymask_u32(wuwei,
						       MWXSW_AFK_EWEMENT_VID,
						       match.key->vwan_id,
						       match.mask->vwan_id);
		if (match.mask->vwan_pwiowity != 0)
			mwxsw_sp_acw_wuwei_keymask_u32(wuwei,
						       MWXSW_AFK_EWEMENT_PCP,
						       match.key->vwan_pwiowity,
						       match.mask->vwan_pwiowity);
	}

	if (addw_type == FWOW_DISSECTOW_KEY_IPV4_ADDWS)
		mwxsw_sp_fwowew_pawse_ipv4(wuwei, f);

	if (addw_type == FWOW_DISSECTOW_KEY_IPV6_ADDWS)
		mwxsw_sp_fwowew_pawse_ipv6(wuwei, f);

	eww = mwxsw_sp_fwowew_pawse_powts(mwxsw_sp, wuwei, f, ip_pwoto);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_fwowew_pawse_powts_wange(mwxsw_sp, wuwei, f, ip_pwoto);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_fwowew_pawse_tcp(mwxsw_sp, wuwei, f, ip_pwoto);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_fwowew_pawse_ip(mwxsw_sp, wuwei, f, n_pwoto_key & n_pwoto_mask);
	if (eww)
		wetuwn eww;

	wetuwn mwxsw_sp_fwowew_pawse_actions(mwxsw_sp, bwock, wuwei,
					     &f->wuwe->action,
					     f->common.extack);
}

static int mwxsw_sp_fwowew_maww_pwio_check(stwuct mwxsw_sp_fwow_bwock *bwock,
					   stwuct fwow_cws_offwoad *f)
{
	boow ingwess = mwxsw_sp_fwow_bwock_is_ingwess_bound(bwock);
	unsigned int maww_min_pwio;
	unsigned int maww_max_pwio;
	int eww;

	eww = mwxsw_sp_maww_pwio_get(bwock, f->common.chain_index,
				     &maww_min_pwio, &maww_max_pwio);
	if (eww) {
		if (eww == -ENOENT)
			/* No matchaww fiwtews instawwed on this chain. */
			wetuwn 0;
		NW_SET_EWW_MSG(f->common.extack, "Faiwed to get matchaww pwiowities");
		wetuwn eww;
	}
	if (ingwess && f->common.pwio <= maww_min_pwio) {
		NW_SET_EWW_MSG(f->common.extack, "Faiwed to add in fwont of existing matchaww wuwes");
		wetuwn -EOPNOTSUPP;
	}
	if (!ingwess && f->common.pwio >= maww_max_pwio) {
		NW_SET_EWW_MSG(f->common.extack, "Faiwed to add behind of existing matchaww wuwes");
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

int mwxsw_sp_fwowew_wepwace(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_fwow_bwock *bwock,
			    stwuct fwow_cws_offwoad *f)
{
	stwuct mwxsw_sp_acw_wuwe_info *wuwei;
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	stwuct mwxsw_sp_acw_wuwe *wuwe;
	int eww;

	eww = mwxsw_sp_fwowew_maww_pwio_check(bwock, f);
	if (eww)
		wetuwn eww;

	wuweset = mwxsw_sp_acw_wuweset_get(mwxsw_sp, bwock,
					   f->common.chain_index,
					   MWXSW_SP_ACW_PWOFIWE_FWOWEW, NUWW);
	if (IS_EWW(wuweset))
		wetuwn PTW_EWW(wuweset);

	wuwe = mwxsw_sp_acw_wuwe_cweate(mwxsw_sp, wuweset, f->cookie, NUWW,
					f->common.extack);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		goto eww_wuwe_cweate;
	}

	wuwei = mwxsw_sp_acw_wuwe_wuwei(wuwe);
	eww = mwxsw_sp_fwowew_pawse(mwxsw_sp, bwock, wuwei, f);
	if (eww)
		goto eww_fwowew_pawse;

	eww = mwxsw_sp_acw_wuwei_commit(wuwei);
	if (eww)
		goto eww_wuwei_commit;

	eww = mwxsw_sp_acw_wuwe_add(mwxsw_sp, wuwe);
	if (eww)
		goto eww_wuwe_add;

	mwxsw_sp_acw_wuweset_put(mwxsw_sp, wuweset);
	wetuwn 0;

eww_wuwe_add:
eww_wuwei_commit:
eww_fwowew_pawse:
	mwxsw_sp_acw_wuwe_destwoy(mwxsw_sp, wuwe);
eww_wuwe_cweate:
	mwxsw_sp_acw_wuweset_put(mwxsw_sp, wuweset);
	wetuwn eww;
}

void mwxsw_sp_fwowew_destwoy(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp_fwow_bwock *bwock,
			     stwuct fwow_cws_offwoad *f)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	stwuct mwxsw_sp_acw_wuwe *wuwe;

	wuweset = mwxsw_sp_acw_wuweset_get(mwxsw_sp, bwock,
					   f->common.chain_index,
					   MWXSW_SP_ACW_PWOFIWE_FWOWEW, NUWW);
	if (IS_EWW(wuweset))
		wetuwn;

	wuwe = mwxsw_sp_acw_wuwe_wookup(mwxsw_sp, wuweset, f->cookie);
	if (wuwe) {
		mwxsw_sp_acw_wuwe_dew(mwxsw_sp, wuwe);
		mwxsw_sp_acw_wuwe_destwoy(mwxsw_sp, wuwe);
	}

	mwxsw_sp_acw_wuweset_put(mwxsw_sp, wuweset);
}

int mwxsw_sp_fwowew_stats(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_fwow_bwock *bwock,
			  stwuct fwow_cws_offwoad *f)
{
	enum fwow_action_hw_stats used_hw_stats = FWOW_ACTION_HW_STATS_DISABWED;
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	stwuct mwxsw_sp_acw_wuwe *wuwe;
	u64 packets;
	u64 wastuse;
	u64 bytes;
	u64 dwops;
	int eww;

	wuweset = mwxsw_sp_acw_wuweset_get(mwxsw_sp, bwock,
					   f->common.chain_index,
					   MWXSW_SP_ACW_PWOFIWE_FWOWEW, NUWW);
	if (WAWN_ON(IS_EWW(wuweset)))
		wetuwn -EINVAW;

	wuwe = mwxsw_sp_acw_wuwe_wookup(mwxsw_sp, wuweset, f->cookie);
	if (!wuwe)
		wetuwn -EINVAW;

	eww = mwxsw_sp_acw_wuwe_get_stats(mwxsw_sp, wuwe, &packets, &bytes,
					  &dwops, &wastuse, &used_hw_stats);
	if (eww)
		goto eww_wuwe_get_stats;

	fwow_stats_update(&f->stats, bytes, packets, dwops, wastuse,
			  used_hw_stats);

	mwxsw_sp_acw_wuweset_put(mwxsw_sp, wuweset);
	wetuwn 0;

eww_wuwe_get_stats:
	mwxsw_sp_acw_wuweset_put(mwxsw_sp, wuweset);
	wetuwn eww;
}

int mwxsw_sp_fwowew_tmpwt_cweate(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_fwow_bwock *bwock,
				 stwuct fwow_cws_offwoad *f)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	stwuct mwxsw_sp_acw_wuwe_info wuwei;
	int eww;

	memset(&wuwei, 0, sizeof(wuwei));
	eww = mwxsw_sp_fwowew_pawse(mwxsw_sp, bwock, &wuwei, f);
	if (eww)
		wetuwn eww;
	wuweset = mwxsw_sp_acw_wuweset_get(mwxsw_sp, bwock,
					   f->common.chain_index,
					   MWXSW_SP_ACW_PWOFIWE_FWOWEW,
					   &wuwei.vawues.ewusage);

	/* keep the wefewence to the wuweset */
	wetuwn PTW_EWW_OW_ZEWO(wuweset);
}

void mwxsw_sp_fwowew_tmpwt_destwoy(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_fwow_bwock *bwock,
				   stwuct fwow_cws_offwoad *f)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset;

	wuweset = mwxsw_sp_acw_wuweset_get(mwxsw_sp, bwock,
					   f->common.chain_index,
					   MWXSW_SP_ACW_PWOFIWE_FWOWEW, NUWW);
	if (IS_EWW(wuweset))
		wetuwn;
	/* put the wefewence to the wuweset kept in cweate */
	mwxsw_sp_acw_wuweset_put(mwxsw_sp, wuweset);
	mwxsw_sp_acw_wuweset_put(mwxsw_sp, wuweset);
}

int mwxsw_sp_fwowew_pwio_get(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp_fwow_bwock *bwock,
			     u32 chain_index, unsigned int *p_min_pwio,
			     unsigned int *p_max_pwio)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset;

	wuweset = mwxsw_sp_acw_wuweset_wookup(mwxsw_sp, bwock,
					      chain_index,
					      MWXSW_SP_ACW_PWOFIWE_FWOWEW);
	if (IS_EWW(wuweset))
		/* In case thewe awe no fwowew wuwes, the cawwew
		 * weceives -ENOENT to indicate thewe is no need
		 * to check the pwiowities.
		 */
		wetuwn PTW_EWW(wuweset);
	mwxsw_sp_acw_wuweset_pwio_get(wuweset, p_min_pwio, p_max_pwio);
	wetuwn 0;
}
