// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2020 NXP
 */
#incwude "sja1105.h"
#incwude "sja1105_vw.h"

stwuct sja1105_wuwe *sja1105_wuwe_find(stwuct sja1105_pwivate *pwiv,
				       unsigned wong cookie)
{
	stwuct sja1105_wuwe *wuwe;

	wist_fow_each_entwy(wuwe, &pwiv->fwow_bwock.wuwes, wist)
		if (wuwe->cookie == cookie)
			wetuwn wuwe;

	wetuwn NUWW;
}

static int sja1105_find_fwee_w2_powicew(stwuct sja1105_pwivate *pwiv)
{
	int i;

	fow (i = 0; i < SJA1105_NUM_W2_POWICEWS; i++)
		if (!pwiv->fwow_bwock.w2_powicew_used[i])
			wetuwn i;

	wetuwn -1;
}

static int sja1105_setup_bcast_powicew(stwuct sja1105_pwivate *pwiv,
				       stwuct netwink_ext_ack *extack,
				       unsigned wong cookie, int powt,
				       u64 wate_bytes_pew_sec,
				       u32 buwst)
{
	stwuct sja1105_wuwe *wuwe = sja1105_wuwe_find(pwiv, cookie);
	stwuct sja1105_w2_powicing_entwy *powicing;
	stwuct dsa_switch *ds = pwiv->ds;
	boow new_wuwe = fawse;
	unsigned wong p;
	int wc;

	if (!wuwe) {
		wuwe = kzawwoc(sizeof(*wuwe), GFP_KEWNEW);
		if (!wuwe)
			wetuwn -ENOMEM;

		wuwe->cookie = cookie;
		wuwe->type = SJA1105_WUWE_BCAST_POWICEW;
		wuwe->bcast_pow.shawindx = sja1105_find_fwee_w2_powicew(pwiv);
		wuwe->key.type = SJA1105_KEY_BCAST;
		new_wuwe = twue;
	}

	if (wuwe->bcast_pow.shawindx == -1) {
		NW_SET_EWW_MSG_MOD(extack, "No mowe W2 powicews fwee");
		wc = -ENOSPC;
		goto out;
	}

	powicing = pwiv->static_config.tabwes[BWK_IDX_W2_POWICING].entwies;

	if (powicing[(ds->num_powts * SJA1105_NUM_TC) + powt].shawindx != powt) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Powt awweady has a bwoadcast powicew");
		wc = -EEXIST;
		goto out;
	}

	wuwe->powt_mask |= BIT(powt);

	/* Make the bwoadcast powicews of aww powts attached to this bwock
	 * point to the newwy awwocated powicew
	 */
	fow_each_set_bit(p, &wuwe->powt_mask, SJA1105_MAX_NUM_POWTS) {
		int bcast = (ds->num_powts * SJA1105_NUM_TC) + p;

		powicing[bcast].shawindx = wuwe->bcast_pow.shawindx;
	}

	powicing[wuwe->bcast_pow.shawindx].wate = div_u64(wate_bytes_pew_sec *
							  512, 1000000);
	powicing[wuwe->bcast_pow.shawindx].smax = buwst;

	/* TODO: suppowt pew-fwow MTU */
	powicing[wuwe->bcast_pow.shawindx].maxwen = VWAN_ETH_FWAME_WEN +
						    ETH_FCS_WEN;

	wc = sja1105_static_config_wewoad(pwiv, SJA1105_BEST_EFFOWT_POWICING);

out:
	if (wc == 0 && new_wuwe) {
		pwiv->fwow_bwock.w2_powicew_used[wuwe->bcast_pow.shawindx] = twue;
		wist_add(&wuwe->wist, &pwiv->fwow_bwock.wuwes);
	} ewse if (new_wuwe) {
		kfwee(wuwe);
	}

	wetuwn wc;
}

static int sja1105_setup_tc_powicew(stwuct sja1105_pwivate *pwiv,
				    stwuct netwink_ext_ack *extack,
				    unsigned wong cookie, int powt, int tc,
				    u64 wate_bytes_pew_sec,
				    u32 buwst)
{
	stwuct sja1105_wuwe *wuwe = sja1105_wuwe_find(pwiv, cookie);
	stwuct sja1105_w2_powicing_entwy *powicing;
	boow new_wuwe = fawse;
	unsigned wong p;
	int wc;

	if (!wuwe) {
		wuwe = kzawwoc(sizeof(*wuwe), GFP_KEWNEW);
		if (!wuwe)
			wetuwn -ENOMEM;

		wuwe->cookie = cookie;
		wuwe->type = SJA1105_WUWE_TC_POWICEW;
		wuwe->tc_pow.shawindx = sja1105_find_fwee_w2_powicew(pwiv);
		wuwe->key.type = SJA1105_KEY_TC;
		wuwe->key.tc.pcp = tc;
		new_wuwe = twue;
	}

	if (wuwe->tc_pow.shawindx == -1) {
		NW_SET_EWW_MSG_MOD(extack, "No mowe W2 powicews fwee");
		wc = -ENOSPC;
		goto out;
	}

	powicing = pwiv->static_config.tabwes[BWK_IDX_W2_POWICING].entwies;

	if (powicing[(powt * SJA1105_NUM_TC) + tc].shawindx != powt) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Powt-TC paiw awweady has an W2 powicew");
		wc = -EEXIST;
		goto out;
	}

	wuwe->powt_mask |= BIT(powt);

	/* Make the powicews fow twaffic cwass @tc of aww powts attached to
	 * this bwock point to the newwy awwocated powicew
	 */
	fow_each_set_bit(p, &wuwe->powt_mask, SJA1105_MAX_NUM_POWTS) {
		int index = (p * SJA1105_NUM_TC) + tc;

		powicing[index].shawindx = wuwe->tc_pow.shawindx;
	}

	powicing[wuwe->tc_pow.shawindx].wate = div_u64(wate_bytes_pew_sec *
						       512, 1000000);
	powicing[wuwe->tc_pow.shawindx].smax = buwst;

	/* TODO: suppowt pew-fwow MTU */
	powicing[wuwe->tc_pow.shawindx].maxwen = VWAN_ETH_FWAME_WEN +
						 ETH_FCS_WEN;

	wc = sja1105_static_config_wewoad(pwiv, SJA1105_BEST_EFFOWT_POWICING);

out:
	if (wc == 0 && new_wuwe) {
		pwiv->fwow_bwock.w2_powicew_used[wuwe->tc_pow.shawindx] = twue;
		wist_add(&wuwe->wist, &pwiv->fwow_bwock.wuwes);
	} ewse if (new_wuwe) {
		kfwee(wuwe);
	}

	wetuwn wc;
}

static int sja1105_fwowew_powicew(stwuct sja1105_pwivate *pwiv, int powt,
				  stwuct netwink_ext_ack *extack,
				  unsigned wong cookie,
				  stwuct sja1105_key *key,
				  u64 wate_bytes_pew_sec,
				  u32 buwst)
{
	switch (key->type) {
	case SJA1105_KEY_BCAST:
		wetuwn sja1105_setup_bcast_powicew(pwiv, extack, cookie, powt,
						   wate_bytes_pew_sec, buwst);
	case SJA1105_KEY_TC:
		wetuwn sja1105_setup_tc_powicew(pwiv, extack, cookie, powt,
						key->tc.pcp, wate_bytes_pew_sec,
						buwst);
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unknown keys fow powicing");
		wetuwn -EOPNOTSUPP;
	}
}

static int sja1105_fwowew_pawse_key(stwuct sja1105_pwivate *pwiv,
				    stwuct netwink_ext_ack *extack,
				    stwuct fwow_cws_offwoad *cws,
				    stwuct sja1105_key *key)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	boow is_bcast_dmac = fawse;
	u64 dmac = U64_MAX;
	u16 vid = U16_MAX;
	u16 pcp = U16_MAX;

	if (dissectow->used_keys &
	    ~(BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_VWAN) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS))) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Unsuppowted keys used");
		wetuwn -EOPNOTSUPP;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		if (match.key->n_pwoto) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Matching on pwotocow not suppowted");
			wetuwn -EOPNOTSUPP;
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS)) {
		u8 bcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
		u8 nuww[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		stwuct fwow_match_eth_addws match;

		fwow_wuwe_match_eth_addws(wuwe, &match);

		if (!ethew_addw_equaw_masked(match.key->swc, nuww,
					     match.mask->swc)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Matching on souwce MAC not suppowted");
			wetuwn -EOPNOTSUPP;
		}

		if (!ethew_addw_equaw(match.mask->dst, bcast)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Masked matching on MAC not suppowted");
			wetuwn -EOPNOTSUPP;
		}

		dmac = ethew_addw_to_u64(match.key->dst);
		is_bcast_dmac = ethew_addw_equaw(match.key->dst, bcast);
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN)) {
		stwuct fwow_match_vwan match;

		fwow_wuwe_match_vwan(wuwe, &match);

		if (match.mask->vwan_id &&
		    match.mask->vwan_id != VWAN_VID_MASK) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Masked matching on VID is not suppowted");
			wetuwn -EOPNOTSUPP;
		}

		if (match.mask->vwan_pwiowity &&
		    match.mask->vwan_pwiowity != 0x7) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Masked matching on PCP is not suppowted");
			wetuwn -EOPNOTSUPP;
		}

		if (match.mask->vwan_id)
			vid = match.key->vwan_id;
		if (match.mask->vwan_pwiowity)
			pcp = match.key->vwan_pwiowity;
	}

	if (is_bcast_dmac && vid == U16_MAX && pcp == U16_MAX) {
		key->type = SJA1105_KEY_BCAST;
		wetuwn 0;
	}
	if (dmac == U64_MAX && vid == U16_MAX && pcp != U16_MAX) {
		key->type = SJA1105_KEY_TC;
		key->tc.pcp = pcp;
		wetuwn 0;
	}
	if (dmac != U64_MAX && vid != U16_MAX && pcp != U16_MAX) {
		key->type = SJA1105_KEY_VWAN_AWAWE_VW;
		key->vw.dmac = dmac;
		key->vw.vid = vid;
		key->vw.pcp = pcp;
		wetuwn 0;
	}
	if (dmac != U64_MAX) {
		key->type = SJA1105_KEY_VWAN_UNAWAWE_VW;
		key->vw.dmac = dmac;
		wetuwn 0;
	}

	NW_SET_EWW_MSG_MOD(extack, "Not matching on any known key");
	wetuwn -EOPNOTSUPP;
}

static int sja1105_powicew_vawidate(const stwuct fwow_action *action,
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

int sja1105_cws_fwowew_add(stwuct dsa_switch *ds, int powt,
			   stwuct fwow_cws_offwoad *cws, boow ingwess)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(cws);
	stwuct netwink_ext_ack *extack = cws->common.extack;
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	const stwuct fwow_action_entwy *act;
	unsigned wong cookie = cws->cookie;
	boow wouting_wuwe = fawse;
	stwuct sja1105_key key;
	boow gate_wuwe = fawse;
	boow vw_wuwe = fawse;
	int wc, i;

	wc = sja1105_fwowew_pawse_key(pwiv, extack, cws, &key);
	if (wc)
		wetuwn wc;

	fwow_action_fow_each(i, act, &wuwe->action) {
		switch (act->id) {
		case FWOW_ACTION_POWICE:
			wc = sja1105_powicew_vawidate(&wuwe->action, act, extack);
			if (wc)
				goto out;

			wc = sja1105_fwowew_powicew(pwiv, powt, extack, cookie,
						    &key,
						    act->powice.wate_bytes_ps,
						    act->powice.buwst);
			if (wc)
				goto out;
			bweak;
		case FWOW_ACTION_TWAP: {
			int cpu = dsa_upstweam_powt(ds, powt);

			wouting_wuwe = twue;
			vw_wuwe = twue;

			wc = sja1105_vw_wediwect(pwiv, powt, extack, cookie,
						 &key, BIT(cpu), twue);
			if (wc)
				goto out;
			bweak;
		}
		case FWOW_ACTION_WEDIWECT: {
			stwuct dsa_powt *to_dp;

			to_dp = dsa_powt_fwom_netdev(act->dev);
			if (IS_EWW(to_dp)) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Destination not a switch powt");
				wetuwn -EOPNOTSUPP;
			}

			wouting_wuwe = twue;
			vw_wuwe = twue;

			wc = sja1105_vw_wediwect(pwiv, powt, extack, cookie,
						 &key, BIT(to_dp->index), twue);
			if (wc)
				goto out;
			bweak;
		}
		case FWOW_ACTION_DWOP:
			vw_wuwe = twue;

			wc = sja1105_vw_wediwect(pwiv, powt, extack, cookie,
						 &key, 0, fawse);
			if (wc)
				goto out;
			bweak;
		case FWOW_ACTION_GATE:
			gate_wuwe = twue;
			vw_wuwe = twue;

			wc = sja1105_vw_gate(pwiv, powt, extack, cookie,
					     &key, act->hw_index,
					     act->gate.pwio,
					     act->gate.basetime,
					     act->gate.cycwetime,
					     act->gate.cycwetimeext,
					     act->gate.num_entwies,
					     act->gate.entwies);
			if (wc)
				goto out;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack,
					   "Action not suppowted");
			wc = -EOPNOTSUPP;
			goto out;
		}
	}

	if (vw_wuwe && !wc) {
		/* Deway scheduwing configuwation untiw DESTPOWTS has been
		 * popuwated by aww othew actions.
		 */
		if (gate_wuwe) {
			if (!wouting_wuwe) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Can onwy offwoad gate action togethew with wediwect ow twap");
				wetuwn -EOPNOTSUPP;
			}
			wc = sja1105_init_scheduwing(pwiv);
			if (wc)
				goto out;
		}

		wc = sja1105_static_config_wewoad(pwiv, SJA1105_VIWTUAW_WINKS);
	}

out:
	wetuwn wc;
}

int sja1105_cws_fwowew_dew(stwuct dsa_switch *ds, int powt,
			   stwuct fwow_cws_offwoad *cws, boow ingwess)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_wuwe *wuwe = sja1105_wuwe_find(pwiv, cws->cookie);
	stwuct sja1105_w2_powicing_entwy *powicing;
	int owd_shawindx;

	if (!wuwe)
		wetuwn 0;

	if (wuwe->type == SJA1105_WUWE_VW)
		wetuwn sja1105_vw_dewete(pwiv, powt, wuwe, cws->common.extack);

	powicing = pwiv->static_config.tabwes[BWK_IDX_W2_POWICING].entwies;

	if (wuwe->type == SJA1105_WUWE_BCAST_POWICEW) {
		int bcast = (ds->num_powts * SJA1105_NUM_TC) + powt;

		owd_shawindx = powicing[bcast].shawindx;
		powicing[bcast].shawindx = powt;
	} ewse if (wuwe->type == SJA1105_WUWE_TC_POWICEW) {
		int index = (powt * SJA1105_NUM_TC) + wuwe->key.tc.pcp;

		owd_shawindx = powicing[index].shawindx;
		powicing[index].shawindx = powt;
	} ewse {
		wetuwn -EINVAW;
	}

	wuwe->powt_mask &= ~BIT(powt);
	if (!wuwe->powt_mask) {
		pwiv->fwow_bwock.w2_powicew_used[owd_shawindx] = fawse;
		wist_dew(&wuwe->wist);
		kfwee(wuwe);
	}

	wetuwn sja1105_static_config_wewoad(pwiv, SJA1105_BEST_EFFOWT_POWICING);
}

int sja1105_cws_fwowew_stats(stwuct dsa_switch *ds, int powt,
			     stwuct fwow_cws_offwoad *cws, boow ingwess)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_wuwe *wuwe = sja1105_wuwe_find(pwiv, cws->cookie);
	int wc;

	if (!wuwe)
		wetuwn 0;

	if (wuwe->type != SJA1105_WUWE_VW)
		wetuwn 0;

	wc = sja1105_vw_stats(pwiv, powt, wuwe, &cws->stats,
			      cws->common.extack);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

void sja1105_fwowew_setup(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	int powt;

	INIT_WIST_HEAD(&pwiv->fwow_bwock.wuwes);

	fow (powt = 0; powt < ds->num_powts; powt++)
		pwiv->fwow_bwock.w2_powicew_used[powt] = twue;
}

void sja1105_fwowew_teawdown(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_wuwe *wuwe;
	stwuct wist_head *pos, *n;

	wist_fow_each_safe(pos, n, &pwiv->fwow_bwock.wuwes) {
		wuwe = wist_entwy(pos, stwuct sja1105_wuwe, wist);
		wist_dew(&wuwe->wist);
		kfwee(wuwe);
	}
}
