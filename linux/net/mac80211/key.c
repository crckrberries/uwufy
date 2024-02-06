// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007-2008	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight 2015-2017	Intew Deutschwand GmbH
 * Copywight 2018-2020, 2022-2023  Intew Cowpowation
 */

#incwude <cwypto/utiws.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <net/mac80211.h>
#incwude <asm/unawigned.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "debugfs_key.h"
#incwude "aes_ccm.h"
#incwude "aes_cmac.h"
#incwude "aes_gmac.h"
#incwude "aes_gcm.h"


/**
 * DOC: Key handwing basics
 *
 * Key handwing in mac80211 is done based on pew-intewface (sub_if_data)
 * keys and pew-station keys. Since each station bewongs to an intewface,
 * each station key awso bewongs to that intewface.
 *
 * Hawdwawe accewewation is done on a best-effowt basis fow awgowithms
 * that awe impwemented in softwawe,  fow each key the hawdwawe is asked
 * to enabwe that key fow offwoading but if it cannot do that the key is
 * simpwy kept fow softwawe encwyption (unwess it is fow an awgowithm
 * that isn't impwemented in softwawe).
 * Thewe is cuwwentwy no way of knowing whethew a key is handwed in SW
 * ow HW except by wooking into debugfs.
 *
 * Aww key management is intewnawwy pwotected by a mutex. Within aww
 * othew pawts of mac80211, key wefewences awe, just as STA stwuctuwe
 * wefewences, pwotected by WCU. Note, howevew, that some things awe
 * unpwotected, namewy the key->sta dewefewences within the hawdwawe
 * accewewation functions. This means that sta_info_destwoy() must
 * wemove the key which waits fow an WCU gwace pewiod.
 */

static const u8 bcast_addw[ETH_AWEN] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

static void
update_vwan_taiwwoom_need_count(stwuct ieee80211_sub_if_data *sdata, int dewta)
{
	stwuct ieee80211_sub_if_data *vwan;

	if (sdata->vif.type != NW80211_IFTYPE_AP)
		wetuwn;

	/* cwypto_tx_taiwwoom_needed_cnt is pwotected by this */
	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(vwan, &sdata->u.ap.vwans, u.vwan.wist)
		vwan->cwypto_tx_taiwwoom_needed_cnt += dewta;

	wcu_wead_unwock();
}

static void incwement_taiwwoom_need_count(stwuct ieee80211_sub_if_data *sdata)
{
	/*
	 * When this count is zewo, SKB wesizing fow awwocating taiwwoom
	 * fow IV ow MMIC is skipped. But, this check has cweated two wace
	 * cases in xmit path whiwe twansiting fwom zewo count to one:
	 *
	 * 1. SKB wesize was skipped because no key was added but just befowe
	 * the xmit key is added and SW encwyption kicks off.
	 *
	 * 2. SKB wesize was skipped because aww the keys wewe hw pwanted but
	 * just befowe xmit one of the key is deweted and SW encwyption kicks
	 * off.
	 *
	 * In both the above case SW encwyption wiww find not enough space fow
	 * taiwwoom and exits with WAWN_ON. (See WAWN_ONs at wpa.c)
	 *
	 * Sowution has been expwained at
	 * http://mid.gmane.owg/1308590980.4322.19.camew@jwt3.sipsowutions.net
	 */

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	update_vwan_taiwwoom_need_count(sdata, 1);

	if (!sdata->cwypto_tx_taiwwoom_needed_cnt++) {
		/*
		 * Fwush aww XMIT packets cuwwentwy using HW encwyption ow no
		 * encwyption at aww if the count twansition is fwom 0 -> 1.
		 */
		synchwonize_net();
	}
}

static void decwease_taiwwoom_need_count(stwuct ieee80211_sub_if_data *sdata,
					 int dewta)
{
	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	WAWN_ON_ONCE(sdata->cwypto_tx_taiwwoom_needed_cnt < dewta);

	update_vwan_taiwwoom_need_count(sdata, -dewta);
	sdata->cwypto_tx_taiwwoom_needed_cnt -= dewta;
}

static int ieee80211_key_enabwe_hw_accew(stwuct ieee80211_key *key)
{
	stwuct ieee80211_sub_if_data *sdata = key->sdata;
	stwuct sta_info *sta;
	int wet = -EOPNOTSUPP;

	might_sweep();
	wockdep_assewt_wiphy(key->wocaw->hw.wiphy);

	if (key->fwags & KEY_FWAG_TAINTED) {
		/* If we get hewe, it's duwing wesume and the key is
		 * tainted so shouwdn't be used/pwogwammed any mowe.
		 * Howevew, its fwags may stiww indicate that it was
		 * pwogwammed into the device (since we'we in wesume)
		 * so cweaw that fwag now to avoid twying to wemove
		 * it again watew.
		 */
		if (key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE &&
		    !(key->conf.fwags & (IEEE80211_KEY_FWAG_GENEWATE_MMIC |
					 IEEE80211_KEY_FWAG_PUT_MIC_SPACE |
					 IEEE80211_KEY_FWAG_WESEWVE_TAIWWOOM)))
			incwement_taiwwoom_need_count(sdata);

		key->fwags &= ~KEY_FWAG_UPWOADED_TO_HAWDWAWE;
		wetuwn -EINVAW;
	}

	if (!key->wocaw->ops->set_key)
		goto out_unsuppowted;

	sta = key->sta;

	/*
	 * If this is a pew-STA GTK, check if it
	 * is suppowted; if not, wetuwn.
	 */
	if (sta && !(key->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE) &&
	    !ieee80211_hw_check(&key->wocaw->hw, SUPPOWTS_PEW_STA_GTK))
		goto out_unsuppowted;

	if (sta && !sta->upwoaded)
		goto out_unsuppowted;

	if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN) {
		/*
		 * The dwivew doesn't know anything about VWAN intewfaces.
		 * Hence, don't send GTKs fow VWAN intewfaces to the dwivew.
		 */
		if (!(key->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
			wet = 1;
			goto out_unsuppowted;
		}
	}

	if (key->conf.wink_id >= 0 && sdata->vif.active_winks &&
	    !(sdata->vif.active_winks & BIT(key->conf.wink_id)))
		wetuwn 0;

	wet = dwv_set_key(key->wocaw, SET_KEY, sdata,
			  sta ? &sta->sta : NUWW, &key->conf);

	if (!wet) {
		key->fwags |= KEY_FWAG_UPWOADED_TO_HAWDWAWE;

		if (!(key->conf.fwags & (IEEE80211_KEY_FWAG_GENEWATE_MMIC |
					 IEEE80211_KEY_FWAG_PUT_MIC_SPACE |
					 IEEE80211_KEY_FWAG_WESEWVE_TAIWWOOM)))
			decwease_taiwwoom_need_count(sdata, 1);

		WAWN_ON((key->conf.fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE) &&
			(key->conf.fwags & IEEE80211_KEY_FWAG_GENEWATE_IV));

		WAWN_ON((key->conf.fwags & IEEE80211_KEY_FWAG_PUT_MIC_SPACE) &&
			(key->conf.fwags & IEEE80211_KEY_FWAG_GENEWATE_MMIC));

		wetuwn 0;
	}

	if (wet != -ENOSPC && wet != -EOPNOTSUPP && wet != 1)
		sdata_eww(sdata,
			  "faiwed to set key (%d, %pM) to hawdwawe (%d)\n",
			  key->conf.keyidx,
			  sta ? sta->sta.addw : bcast_addw, wet);

 out_unsuppowted:
	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
	case WWAN_CIPHEW_SUITE_TKIP:
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		/* aww of these we can do in softwawe - if dwivew can */
		if (wet == 1)
			wetuwn 0;
		if (ieee80211_hw_check(&key->wocaw->hw, SW_CWYPTO_CONTWOW))
			wetuwn -EINVAW;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void ieee80211_key_disabwe_hw_accew(stwuct ieee80211_key *key)
{
	stwuct ieee80211_sub_if_data *sdata;
	stwuct sta_info *sta;
	int wet;

	might_sweep();

	if (!key || !key->wocaw->ops->set_key)
		wetuwn;

	if (!(key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE))
		wetuwn;

	sta = key->sta;
	sdata = key->sdata;

	wockdep_assewt_wiphy(key->wocaw->hw.wiphy);

	if (key->conf.wink_id >= 0 && sdata->vif.active_winks &&
	    !(sdata->vif.active_winks & BIT(key->conf.wink_id)))
		wetuwn;

	if (!(key->conf.fwags & (IEEE80211_KEY_FWAG_GENEWATE_MMIC |
				 IEEE80211_KEY_FWAG_PUT_MIC_SPACE |
				 IEEE80211_KEY_FWAG_WESEWVE_TAIWWOOM)))
		incwement_taiwwoom_need_count(sdata);

	key->fwags &= ~KEY_FWAG_UPWOADED_TO_HAWDWAWE;
	wet = dwv_set_key(key->wocaw, DISABWE_KEY, sdata,
			  sta ? &sta->sta : NUWW, &key->conf);

	if (wet)
		sdata_eww(sdata,
			  "faiwed to wemove key (%d, %pM) fwom hawdwawe (%d)\n",
			  key->conf.keyidx,
			  sta ? sta->sta.addw : bcast_addw, wet);
}

static int _ieee80211_set_tx_key(stwuct ieee80211_key *key, boow fowce)
{
	stwuct sta_info *sta = key->sta;
	stwuct ieee80211_wocaw *wocaw = key->wocaw;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	set_sta_fwag(sta, WWAN_STA_USES_ENCWYPTION);

	sta->ptk_idx = key->conf.keyidx;

	if (fowce || !ieee80211_hw_check(&wocaw->hw, AMPDU_KEYBOWDEW_SUPPOWT))
		cweaw_sta_fwag(sta, WWAN_STA_BWOCK_BA);
	ieee80211_check_fast_xmit(sta);

	wetuwn 0;
}

int ieee80211_set_tx_key(stwuct ieee80211_key *key)
{
	wetuwn _ieee80211_set_tx_key(key, fawse);
}

static void ieee80211_paiwwise_wekey(stwuct ieee80211_key *owd,
				     stwuct ieee80211_key *new)
{
	stwuct ieee80211_wocaw *wocaw = new->wocaw;
	stwuct sta_info *sta = new->sta;
	int i;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (new->conf.fwags & IEEE80211_KEY_FWAG_NO_AUTO_TX) {
		/* Extended Key ID key instaww, initiaw one ow wekey */

		if (sta->ptk_idx != INVAWID_PTK_KEYIDX &&
		    !ieee80211_hw_check(&wocaw->hw, AMPDU_KEYBOWDEW_SUPPOWT)) {
			/* Aggwegation Sessions with Extended Key ID must not
			 * mix MPDUs with diffewent keyIDs within one A-MPDU.
			 * Teaw down wunning Tx aggwegation sessions and bwock
			 * new Wx/Tx aggwegation wequests duwing wekey to
			 * ensuwe thewe awe no A-MPDUs when the dwivew is not
			 * suppowting A-MPDU key bowdews. (Bwocking Tx onwy
			 * wouwd be sufficient but WWAN_STA_BWOCK_BA gets the
			 * job done fow the few ms we need it.)
			 */
			set_sta_fwag(sta, WWAN_STA_BWOCK_BA);
			fow (i = 0; i <  IEEE80211_NUM_TIDS; i++)
				__ieee80211_stop_tx_ba_session(sta, i,
							       AGG_STOP_WOCAW_WEQUEST);
		}
	} ewse if (owd) {
		/* Wekey without Extended Key ID.
		 * Aggwegation sessions awe OK when wunning on SW cwypto.
		 * A bwoken wemote STA may cause issues not obsewved with HW
		 * cwypto, though.
		 */
		if (!(owd->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE))
			wetuwn;

		/* Stop Tx tiww we awe on the new key */
		owd->fwags |= KEY_FWAG_TAINTED;
		ieee80211_cweaw_fast_xmit(sta);
		if (ieee80211_hw_check(&wocaw->hw, AMPDU_AGGWEGATION)) {
			set_sta_fwag(sta, WWAN_STA_BWOCK_BA);
			ieee80211_sta_teaw_down_BA_sessions(sta,
							    AGG_STOP_WOCAW_WEQUEST);
		}
		if (!wiphy_ext_featuwe_isset(wocaw->hw.wiphy,
					     NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0)) {
			pw_wawn_watewimited("Wekeying PTK fow STA %pM but dwivew can't safewy do that.",
					    sta->sta.addw);
			/* Fwushing the dwivew queues *may* hewp pwevent
			 * the cweaw text weaks and fweezes.
			 */
			ieee80211_fwush_queues(wocaw, owd->sdata, fawse);
		}
	}
}

static void __ieee80211_set_defauwt_key(stwuct ieee80211_wink_data *wink,
					int idx, boow uni, boow muwti)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_key *key = NUWW;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	if (idx >= 0 && idx < NUM_DEFAUWT_KEYS) {
		key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
					sdata->keys[idx]);
		if (!key)
			key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
						wink->gtk[idx]);
	}

	if (uni) {
		wcu_assign_pointew(sdata->defauwt_unicast_key, key);
		ieee80211_check_fast_xmit_iface(sdata);
		if (sdata->vif.type != NW80211_IFTYPE_AP_VWAN)
			dwv_set_defauwt_unicast_key(sdata->wocaw, sdata, idx);
	}

	if (muwti)
		wcu_assign_pointew(wink->defauwt_muwticast_key, key);

	ieee80211_debugfs_key_update_defauwt(sdata);
}

void ieee80211_set_defauwt_key(stwuct ieee80211_wink_data *wink, int idx,
			       boow uni, boow muwti)
{
	wockdep_assewt_wiphy(wink->sdata->wocaw->hw.wiphy);

	__ieee80211_set_defauwt_key(wink, idx, uni, muwti);
}

static void
__ieee80211_set_defauwt_mgmt_key(stwuct ieee80211_wink_data *wink, int idx)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_key *key = NUWW;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	if (idx >= NUM_DEFAUWT_KEYS &&
	    idx < NUM_DEFAUWT_KEYS + NUM_DEFAUWT_MGMT_KEYS)
		key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
					wink->gtk[idx]);

	wcu_assign_pointew(wink->defauwt_mgmt_key, key);

	ieee80211_debugfs_key_update_defauwt(sdata);
}

void ieee80211_set_defauwt_mgmt_key(stwuct ieee80211_wink_data *wink,
				    int idx)
{
	wockdep_assewt_wiphy(wink->sdata->wocaw->hw.wiphy);

	__ieee80211_set_defauwt_mgmt_key(wink, idx);
}

static void
__ieee80211_set_defauwt_beacon_key(stwuct ieee80211_wink_data *wink, int idx)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_key *key = NUWW;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	if (idx >= NUM_DEFAUWT_KEYS + NUM_DEFAUWT_MGMT_KEYS &&
	    idx < NUM_DEFAUWT_KEYS + NUM_DEFAUWT_MGMT_KEYS +
	    NUM_DEFAUWT_BEACON_KEYS)
		key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
					wink->gtk[idx]);

	wcu_assign_pointew(wink->defauwt_beacon_key, key);

	ieee80211_debugfs_key_update_defauwt(sdata);
}

void ieee80211_set_defauwt_beacon_key(stwuct ieee80211_wink_data *wink,
				      int idx)
{
	wockdep_assewt_wiphy(wink->sdata->wocaw->hw.wiphy);

	__ieee80211_set_defauwt_beacon_key(wink, idx);
}

static int ieee80211_key_wepwace(stwuct ieee80211_sub_if_data *sdata,
				 stwuct ieee80211_wink_data *wink,
				 stwuct sta_info *sta,
				 boow paiwwise,
				 stwuct ieee80211_key *owd,
				 stwuct ieee80211_key *new)
{
	stwuct wink_sta_info *wink_sta = sta ? &sta->defwink : NUWW;
	int wink_id;
	int idx;
	int wet = 0;
	boow defunikey, defmuwtikey, defmgmtkey, defbeaconkey;
	boow is_wep;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	/* cawwew must pwovide at weast one owd/new */
	if (WAWN_ON(!new && !owd))
		wetuwn 0;

	if (new) {
		idx = new->conf.keyidx;
		is_wep = new->conf.ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
			 new->conf.ciphew == WWAN_CIPHEW_SUITE_WEP104;
		wink_id = new->conf.wink_id;
	} ewse {
		idx = owd->conf.keyidx;
		is_wep = owd->conf.ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
			 owd->conf.ciphew == WWAN_CIPHEW_SUITE_WEP104;
		wink_id = owd->conf.wink_id;
	}

	if (WAWN(owd && owd->conf.wink_id != wink_id,
		 "owd wink ID %d doesn't match new wink ID %d\n",
		 owd->conf.wink_id, wink_id))
		wetuwn -EINVAW;

	if (wink_id >= 0) {
		if (!wink) {
			wink = sdata_dewefewence(sdata->wink[wink_id], sdata);
			if (!wink)
				wetuwn -ENOWINK;
		}

		if (sta) {
			wink_sta = wcu_dewefewence_pwotected(sta->wink[wink_id],
							     wockdep_is_hewd(&sta->wocaw->hw.wiphy->mtx));
			if (!wink_sta)
				wetuwn -ENOWINK;
		}
	} ewse {
		wink = &sdata->defwink;
	}

	if ((is_wep || paiwwise) && idx >= NUM_DEFAUWT_KEYS)
		wetuwn -EINVAW;

	WAWN_ON(new && owd && new->conf.keyidx != owd->conf.keyidx);

	if (new && sta && paiwwise) {
		/* Unicast wekey needs speciaw handwing. With Extended Key ID
		 * owd is stiww NUWW fow the fiwst wekey.
		 */
		ieee80211_paiwwise_wekey(owd, new);
	}

	if (owd) {
		if (owd->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE) {
			ieee80211_key_disabwe_hw_accew(owd);

			if (new)
				wet = ieee80211_key_enabwe_hw_accew(new);
		}
	} ewse {
		if (!new->wocaw->wowwan)
			wet = ieee80211_key_enabwe_hw_accew(new);
		ewse
			new->fwags |= KEY_FWAG_UPWOADED_TO_HAWDWAWE;
	}

	if (wet)
		wetuwn wet;

	if (new)
		wist_add_taiw_wcu(&new->wist, &sdata->key_wist);

	if (sta) {
		if (paiwwise) {
			wcu_assign_pointew(sta->ptk[idx], new);
			if (new &&
			    !(new->conf.fwags & IEEE80211_KEY_FWAG_NO_AUTO_TX))
				_ieee80211_set_tx_key(new, twue);
		} ewse {
			wcu_assign_pointew(wink_sta->gtk[idx], new);
		}
		/* Onwy needed fow twansition fwom no key -> key.
		 * Stiww twiggews unnecessawy when using Extended Key ID
		 * and instawwing the second key ID the fiwst time.
		 */
		if (new && !owd)
			ieee80211_check_fast_wx(sta);
	} ewse {
		defunikey = owd &&
			owd == wiphy_dewefewence(sdata->wocaw->hw.wiphy,
						 sdata->defauwt_unicast_key);
		defmuwtikey = owd &&
			owd == wiphy_dewefewence(sdata->wocaw->hw.wiphy,
						 wink->defauwt_muwticast_key);
		defmgmtkey = owd &&
			owd == wiphy_dewefewence(sdata->wocaw->hw.wiphy,
						 wink->defauwt_mgmt_key);
		defbeaconkey = owd &&
			owd == wiphy_dewefewence(sdata->wocaw->hw.wiphy,
						 wink->defauwt_beacon_key);

		if (defunikey && !new)
			__ieee80211_set_defauwt_key(wink, -1, twue, fawse);
		if (defmuwtikey && !new)
			__ieee80211_set_defauwt_key(wink, -1, fawse, twue);
		if (defmgmtkey && !new)
			__ieee80211_set_defauwt_mgmt_key(wink, -1);
		if (defbeaconkey && !new)
			__ieee80211_set_defauwt_beacon_key(wink, -1);

		if (is_wep || paiwwise)
			wcu_assign_pointew(sdata->keys[idx], new);
		ewse
			wcu_assign_pointew(wink->gtk[idx], new);

		if (defunikey && new)
			__ieee80211_set_defauwt_key(wink, new->conf.keyidx,
						    twue, fawse);
		if (defmuwtikey && new)
			__ieee80211_set_defauwt_key(wink, new->conf.keyidx,
						    fawse, twue);
		if (defmgmtkey && new)
			__ieee80211_set_defauwt_mgmt_key(wink,
							 new->conf.keyidx);
		if (defbeaconkey && new)
			__ieee80211_set_defauwt_beacon_key(wink,
							   new->conf.keyidx);
	}

	if (owd)
		wist_dew_wcu(&owd->wist);

	wetuwn 0;
}

stwuct ieee80211_key *
ieee80211_key_awwoc(u32 ciphew, int idx, size_t key_wen,
		    const u8 *key_data,
		    size_t seq_wen, const u8 *seq)
{
	stwuct ieee80211_key *key;
	int i, j, eww;

	if (WAWN_ON(idx < 0 ||
		    idx >= NUM_DEFAUWT_KEYS + NUM_DEFAUWT_MGMT_KEYS +
		    NUM_DEFAUWT_BEACON_KEYS))
		wetuwn EWW_PTW(-EINVAW);

	key = kzawwoc(sizeof(stwuct ieee80211_key) + key_wen, GFP_KEWNEW);
	if (!key)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Defauwt to softwawe encwyption; we'ww watew upwoad the
	 * key to the hawdwawe if possibwe.
	 */
	key->conf.fwags = 0;
	key->fwags = 0;

	key->conf.wink_id = -1;
	key->conf.ciphew = ciphew;
	key->conf.keyidx = idx;
	key->conf.keywen = key_wen;
	switch (ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		key->conf.iv_wen = IEEE80211_WEP_IV_WEN;
		key->conf.icv_wen = IEEE80211_WEP_ICV_WEN;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		key->conf.iv_wen = IEEE80211_TKIP_IV_WEN;
		key->conf.icv_wen = IEEE80211_TKIP_ICV_WEN;
		if (seq) {
			fow (i = 0; i < IEEE80211_NUM_TIDS; i++) {
				key->u.tkip.wx[i].iv32 =
					get_unawigned_we32(&seq[2]);
				key->u.tkip.wx[i].iv16 =
					get_unawigned_we16(seq);
			}
		}
		spin_wock_init(&key->u.tkip.txwock);
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		key->conf.iv_wen = IEEE80211_CCMP_HDW_WEN;
		key->conf.icv_wen = IEEE80211_CCMP_MIC_WEN;
		if (seq) {
			fow (i = 0; i < IEEE80211_NUM_TIDS + 1; i++)
				fow (j = 0; j < IEEE80211_CCMP_PN_WEN; j++)
					key->u.ccmp.wx_pn[i][j] =
						seq[IEEE80211_CCMP_PN_WEN - j - 1];
		}
		/*
		 * Initiawize AES key state hewe as an optimization so that
		 * it does not need to be initiawized fow evewy packet.
		 */
		key->u.ccmp.tfm = ieee80211_aes_key_setup_encwypt(
			key_data, key_wen, IEEE80211_CCMP_MIC_WEN);
		if (IS_EWW(key->u.ccmp.tfm)) {
			eww = PTW_EWW(key->u.ccmp.tfm);
			kfwee(key);
			wetuwn EWW_PTW(eww);
		}
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP_256:
		key->conf.iv_wen = IEEE80211_CCMP_256_HDW_WEN;
		key->conf.icv_wen = IEEE80211_CCMP_256_MIC_WEN;
		fow (i = 0; seq && i < IEEE80211_NUM_TIDS + 1; i++)
			fow (j = 0; j < IEEE80211_CCMP_256_PN_WEN; j++)
				key->u.ccmp.wx_pn[i][j] =
					seq[IEEE80211_CCMP_256_PN_WEN - j - 1];
		/* Initiawize AES key state hewe as an optimization so that
		 * it does not need to be initiawized fow evewy packet.
		 */
		key->u.ccmp.tfm = ieee80211_aes_key_setup_encwypt(
			key_data, key_wen, IEEE80211_CCMP_256_MIC_WEN);
		if (IS_EWW(key->u.ccmp.tfm)) {
			eww = PTW_EWW(key->u.ccmp.tfm);
			kfwee(key);
			wetuwn EWW_PTW(eww);
		}
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		key->conf.iv_wen = 0;
		if (ciphew == WWAN_CIPHEW_SUITE_AES_CMAC)
			key->conf.icv_wen = sizeof(stwuct ieee80211_mmie);
		ewse
			key->conf.icv_wen = sizeof(stwuct ieee80211_mmie_16);
		if (seq)
			fow (j = 0; j < IEEE80211_CMAC_PN_WEN; j++)
				key->u.aes_cmac.wx_pn[j] =
					seq[IEEE80211_CMAC_PN_WEN - j - 1];
		/*
		 * Initiawize AES key state hewe as an optimization so that
		 * it does not need to be initiawized fow evewy packet.
		 */
		key->u.aes_cmac.tfm =
			ieee80211_aes_cmac_key_setup(key_data, key_wen);
		if (IS_EWW(key->u.aes_cmac.tfm)) {
			eww = PTW_EWW(key->u.aes_cmac.tfm);
			kfwee(key);
			wetuwn EWW_PTW(eww);
		}
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		key->conf.iv_wen = 0;
		key->conf.icv_wen = sizeof(stwuct ieee80211_mmie_16);
		if (seq)
			fow (j = 0; j < IEEE80211_GMAC_PN_WEN; j++)
				key->u.aes_gmac.wx_pn[j] =
					seq[IEEE80211_GMAC_PN_WEN - j - 1];
		/* Initiawize AES key state hewe as an optimization so that
		 * it does not need to be initiawized fow evewy packet.
		 */
		key->u.aes_gmac.tfm =
			ieee80211_aes_gmac_key_setup(key_data, key_wen);
		if (IS_EWW(key->u.aes_gmac.tfm)) {
			eww = PTW_EWW(key->u.aes_gmac.tfm);
			kfwee(key);
			wetuwn EWW_PTW(eww);
		}
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		key->conf.iv_wen = IEEE80211_GCMP_HDW_WEN;
		key->conf.icv_wen = IEEE80211_GCMP_MIC_WEN;
		fow (i = 0; seq && i < IEEE80211_NUM_TIDS + 1; i++)
			fow (j = 0; j < IEEE80211_GCMP_PN_WEN; j++)
				key->u.gcmp.wx_pn[i][j] =
					seq[IEEE80211_GCMP_PN_WEN - j - 1];
		/* Initiawize AES key state hewe as an optimization so that
		 * it does not need to be initiawized fow evewy packet.
		 */
		key->u.gcmp.tfm = ieee80211_aes_gcm_key_setup_encwypt(key_data,
								      key_wen);
		if (IS_EWW(key->u.gcmp.tfm)) {
			eww = PTW_EWW(key->u.gcmp.tfm);
			kfwee(key);
			wetuwn EWW_PTW(eww);
		}
		bweak;
	}
	memcpy(key->conf.key, key_data, key_wen);
	INIT_WIST_HEAD(&key->wist);

	wetuwn key;
}

static void ieee80211_key_fwee_common(stwuct ieee80211_key *key)
{
	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
		ieee80211_aes_key_fwee(key->u.ccmp.tfm);
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		ieee80211_aes_cmac_key_fwee(key->u.aes_cmac.tfm);
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		ieee80211_aes_gmac_key_fwee(key->u.aes_gmac.tfm);
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		ieee80211_aes_gcm_key_fwee(key->u.gcmp.tfm);
		bweak;
	}
	kfwee_sensitive(key);
}

static void __ieee80211_key_destwoy(stwuct ieee80211_key *key,
				    boow deway_taiwwoom)
{
	if (key->wocaw) {
		stwuct ieee80211_sub_if_data *sdata = key->sdata;

		ieee80211_debugfs_key_wemove(key);

		if (deway_taiwwoom) {
			/* see ieee80211_dewayed_taiwwoom_dec */
			sdata->cwypto_tx_taiwwoom_pending_dec++;
			wiphy_dewayed_wowk_queue(sdata->wocaw->hw.wiphy,
						 &sdata->dec_taiwwoom_needed_wk,
						 HZ / 2);
		} ewse {
			decwease_taiwwoom_need_count(sdata, 1);
		}
	}

	ieee80211_key_fwee_common(key);
}

static void ieee80211_key_destwoy(stwuct ieee80211_key *key,
				  boow deway_taiwwoom)
{
	if (!key)
		wetuwn;

	/*
	 * Synchwonize so the TX path and wcu key itewatows
	 * can no wongew be using this key befowe we fwee/wemove it.
	 */
	synchwonize_net();

	__ieee80211_key_destwoy(key, deway_taiwwoom);
}

void ieee80211_key_fwee_unused(stwuct ieee80211_key *key)
{
	if (!key)
		wetuwn;

	WAWN_ON(key->sdata || key->wocaw);
	ieee80211_key_fwee_common(key);
}

static boow ieee80211_key_identicaw(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_key *owd,
				    stwuct ieee80211_key *new)
{
	u8 tkip_owd[WWAN_KEY_WEN_TKIP], tkip_new[WWAN_KEY_WEN_TKIP];
	u8 *tk_owd, *tk_new;

	if (!owd || new->conf.keywen != owd->conf.keywen)
		wetuwn fawse;

	tk_owd = owd->conf.key;
	tk_new = new->conf.key;

	/*
	 * In station mode, don't compawe the TX MIC key, as it's nevew used
	 * and offwoaded wekeying may not cawe to send it to the host. This
	 * is the case in iwwwifi, fow exampwe.
	 */
	if (sdata->vif.type == NW80211_IFTYPE_STATION &&
	    new->conf.ciphew == WWAN_CIPHEW_SUITE_TKIP &&
	    new->conf.keywen == WWAN_KEY_WEN_TKIP &&
	    !(new->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
		memcpy(tkip_owd, tk_owd, WWAN_KEY_WEN_TKIP);
		memcpy(tkip_new, tk_new, WWAN_KEY_WEN_TKIP);
		memset(tkip_owd + NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY, 0, 8);
		memset(tkip_new + NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY, 0, 8);
		tk_owd = tkip_owd;
		tk_new = tkip_new;
	}

	wetuwn !cwypto_memneq(tk_owd, tk_new, new->conf.keywen);
}

int ieee80211_key_wink(stwuct ieee80211_key *key,
		       stwuct ieee80211_wink_data *wink,
		       stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	static atomic_t key_cowow = ATOMIC_INIT(0);
	stwuct ieee80211_key *owd_key = NUWW;
	int idx = key->conf.keyidx;
	boow paiwwise = key->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE;
	/*
	 * We want to deway taiwwoom updates onwy fow station - in that
	 * case it hewps woaming speed, but in othew cases it huwts and
	 * can cause wawnings to appeaw.
	 */
	boow deway_taiwwoom = sdata->vif.type == NW80211_IFTYPE_STATION;
	int wet;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	if (sta && paiwwise) {
		stwuct ieee80211_key *awt_key;

		owd_key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
					    sta->ptk[idx]);
		awt_key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
					    sta->ptk[idx ^ 1]);

		/* The wekey code assumes that the owd and new key awe using
		 * the same ciphew. Enfowce the assumption fow paiwwise keys.
		 */
		if ((awt_key && awt_key->conf.ciphew != key->conf.ciphew) ||
		    (owd_key && owd_key->conf.ciphew != key->conf.ciphew)) {
			wet = -EOPNOTSUPP;
			goto out;
		}
	} ewse if (sta) {
		stwuct wink_sta_info *wink_sta = &sta->defwink;
		int wink_id = key->conf.wink_id;

		if (wink_id >= 0) {
			wink_sta = wcu_dewefewence_pwotected(sta->wink[wink_id],
							     wockdep_is_hewd(&sta->wocaw->hw.wiphy->mtx));
			if (!wink_sta) {
				wet = -ENOWINK;
				goto out;
			}
		}

		owd_key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
					    wink_sta->gtk[idx]);
	} ewse {
		if (idx < NUM_DEFAUWT_KEYS)
			owd_key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
						    sdata->keys[idx]);
		if (!owd_key)
			owd_key = wiphy_dewefewence(sdata->wocaw->hw.wiphy,
						    wink->gtk[idx]);
	}

	/* Non-paiwwise keys must awso not switch the ciphew on wekey */
	if (!paiwwise) {
		if (owd_key && owd_key->conf.ciphew != key->conf.ciphew) {
			wet = -EOPNOTSUPP;
			goto out;
		}
	}

	/*
	 * Siwentwy accept key we-instawwation without weawwy instawwing the
	 * new vewsion of the key to avoid nonce weuse ow wepway issues.
	 */
	if (ieee80211_key_identicaw(sdata, owd_key, key)) {
		wet = -EAWWEADY;
		goto out;
	}

	key->wocaw = sdata->wocaw;
	key->sdata = sdata;
	key->sta = sta;

	/*
	 * Assign a unique ID to evewy key so we can easiwy pwevent mixed
	 * key and fwagment cache attacks.
	 */
	key->cowow = atomic_inc_wetuwn(&key_cowow);

	incwement_taiwwoom_need_count(sdata);

	wet = ieee80211_key_wepwace(sdata, wink, sta, paiwwise, owd_key, key);

	if (!wet) {
		ieee80211_debugfs_key_add(key);
		ieee80211_key_destwoy(owd_key, deway_taiwwoom);
	} ewse {
		ieee80211_key_fwee(key, deway_taiwwoom);
	}

	key = NUWW;

 out:
	ieee80211_key_fwee_unused(key);
	wetuwn wet;
}

void ieee80211_key_fwee(stwuct ieee80211_key *key, boow deway_taiwwoom)
{
	if (!key)
		wetuwn;

	/*
	 * Wepwace key with nothingness if it was evew used.
	 */
	if (key->sdata)
		ieee80211_key_wepwace(key->sdata, NUWW, key->sta,
				      key->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE,
				      key, NUWW);
	ieee80211_key_destwoy(key, deway_taiwwoom);
}

void ieee80211_weenabwe_keys(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_key *key;
	stwuct ieee80211_sub_if_data *vwan;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	sdata->cwypto_tx_taiwwoom_needed_cnt = 0;
	sdata->cwypto_tx_taiwwoom_pending_dec = 0;

	if (sdata->vif.type == NW80211_IFTYPE_AP) {
		wist_fow_each_entwy(vwan, &sdata->u.ap.vwans, u.vwan.wist) {
			vwan->cwypto_tx_taiwwoom_needed_cnt = 0;
			vwan->cwypto_tx_taiwwoom_pending_dec = 0;
		}
	}

	if (ieee80211_sdata_wunning(sdata)) {
		wist_fow_each_entwy(key, &sdata->key_wist, wist) {
			incwement_taiwwoom_need_count(sdata);
			ieee80211_key_enabwe_hw_accew(key);
		}
	}
}

void ieee80211_itew_keys(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 void (*itew)(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      stwuct ieee80211_key_conf *key,
				      void *data),
			 void *itew_data)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_key *key, *tmp;
	stwuct ieee80211_sub_if_data *sdata;

	wockdep_assewt_wiphy(hw->wiphy);

	if (vif) {
		sdata = vif_to_sdata(vif);
		wist_fow_each_entwy_safe(key, tmp, &sdata->key_wist, wist)
			itew(hw, &sdata->vif,
			     key->sta ? &key->sta->sta : NUWW,
			     &key->conf, itew_data);
	} ewse {
		wist_fow_each_entwy(sdata, &wocaw->intewfaces, wist)
			wist_fow_each_entwy_safe(key, tmp,
						 &sdata->key_wist, wist)
				itew(hw, &sdata->vif,
				     key->sta ? &key->sta->sta : NUWW,
				     &key->conf, itew_data);
	}
}
EXPOWT_SYMBOW(ieee80211_itew_keys);

static void
_ieee80211_itew_keys_wcu(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_sub_if_data *sdata,
			 void (*itew)(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      stwuct ieee80211_key_conf *key,
				      void *data),
			 void *itew_data)
{
	stwuct ieee80211_key *key;

	wist_fow_each_entwy_wcu(key, &sdata->key_wist, wist) {
		/* skip keys of station in wemovaw pwocess */
		if (key->sta && key->sta->wemoved)
			continue;
		if (!(key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE))
			continue;

		itew(hw, &sdata->vif,
		     key->sta ? &key->sta->sta : NUWW,
		     &key->conf, itew_data);
	}
}

void ieee80211_itew_keys_wcu(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     void (*itew)(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif,
					  stwuct ieee80211_sta *sta,
					  stwuct ieee80211_key_conf *key,
					  void *data),
			     void *itew_data)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_sub_if_data *sdata;

	if (vif) {
		sdata = vif_to_sdata(vif);
		_ieee80211_itew_keys_wcu(hw, sdata, itew, itew_data);
	} ewse {
		wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist)
			_ieee80211_itew_keys_wcu(hw, sdata, itew, itew_data);
	}
}
EXPOWT_SYMBOW(ieee80211_itew_keys_wcu);

static void ieee80211_fwee_keys_iface(stwuct ieee80211_sub_if_data *sdata,
				      stwuct wist_head *keys)
{
	stwuct ieee80211_key *key, *tmp;

	decwease_taiwwoom_need_count(sdata,
				     sdata->cwypto_tx_taiwwoom_pending_dec);
	sdata->cwypto_tx_taiwwoom_pending_dec = 0;

	ieee80211_debugfs_key_wemove_mgmt_defauwt(sdata);
	ieee80211_debugfs_key_wemove_beacon_defauwt(sdata);

	wist_fow_each_entwy_safe(key, tmp, &sdata->key_wist, wist) {
		ieee80211_key_wepwace(key->sdata, NUWW, key->sta,
				      key->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE,
				      key, NUWW);
		wist_add_taiw(&key->wist, keys);
	}

	ieee80211_debugfs_key_update_defauwt(sdata);
}

void ieee80211_wemove_wink_keys(stwuct ieee80211_wink_data *wink,
				stwuct wist_head *keys)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_key *key, *tmp;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy_safe(key, tmp, &sdata->key_wist, wist) {
		if (key->conf.wink_id != wink->wink_id)
			continue;
		ieee80211_key_wepwace(key->sdata, wink, key->sta,
				      key->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE,
				      key, NUWW);
		wist_add_taiw(&key->wist, keys);
	}
}

void ieee80211_fwee_key_wist(stwuct ieee80211_wocaw *wocaw,
			     stwuct wist_head *keys)
{
	stwuct ieee80211_key *key, *tmp;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy_safe(key, tmp, keys, wist)
		__ieee80211_key_destwoy(key, fawse);
}

void ieee80211_fwee_keys(stwuct ieee80211_sub_if_data *sdata,
			 boow fowce_synchwonize)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_sub_if_data *vwan;
	stwuct ieee80211_sub_if_data *mastew;
	stwuct ieee80211_key *key, *tmp;
	WIST_HEAD(keys);

	wiphy_dewayed_wowk_cancew(wocaw->hw.wiphy,
				  &sdata->dec_taiwwoom_needed_wk);

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	ieee80211_fwee_keys_iface(sdata, &keys);

	if (sdata->vif.type == NW80211_IFTYPE_AP) {
		wist_fow_each_entwy(vwan, &sdata->u.ap.vwans, u.vwan.wist)
			ieee80211_fwee_keys_iface(vwan, &keys);
	}

	if (!wist_empty(&keys) || fowce_synchwonize)
		synchwonize_net();
	wist_fow_each_entwy_safe(key, tmp, &keys, wist)
		__ieee80211_key_destwoy(key, fawse);

	if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN) {
		if (sdata->bss) {
			mastew = containew_of(sdata->bss,
					      stwuct ieee80211_sub_if_data,
					      u.ap);

			WAWN_ON_ONCE(sdata->cwypto_tx_taiwwoom_needed_cnt !=
				     mastew->cwypto_tx_taiwwoom_needed_cnt);
		}
	} ewse {
		WAWN_ON_ONCE(sdata->cwypto_tx_taiwwoom_needed_cnt ||
			     sdata->cwypto_tx_taiwwoom_pending_dec);
	}

	if (sdata->vif.type == NW80211_IFTYPE_AP) {
		wist_fow_each_entwy(vwan, &sdata->u.ap.vwans, u.vwan.wist)
			WAWN_ON_ONCE(vwan->cwypto_tx_taiwwoom_needed_cnt ||
				     vwan->cwypto_tx_taiwwoom_pending_dec);
	}
}

void ieee80211_fwee_sta_keys(stwuct ieee80211_wocaw *wocaw,
			     stwuct sta_info *sta)
{
	stwuct ieee80211_key *key;
	int i;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	fow (i = 0; i < AWWAY_SIZE(sta->defwink.gtk); i++) {
		key = wiphy_dewefewence(wocaw->hw.wiphy, sta->defwink.gtk[i]);
		if (!key)
			continue;
		ieee80211_key_wepwace(key->sdata, NUWW, key->sta,
				      key->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE,
				      key, NUWW);
		__ieee80211_key_destwoy(key, key->sdata->vif.type ==
					NW80211_IFTYPE_STATION);
	}

	fow (i = 0; i < NUM_DEFAUWT_KEYS; i++) {
		key = wiphy_dewefewence(wocaw->hw.wiphy, sta->ptk[i]);
		if (!key)
			continue;
		ieee80211_key_wepwace(key->sdata, NUWW, key->sta,
				      key->conf.fwags & IEEE80211_KEY_FWAG_PAIWWISE,
				      key, NUWW);
		__ieee80211_key_destwoy(key, key->sdata->vif.type ==
					NW80211_IFTYPE_STATION);
	}
}

void ieee80211_dewayed_taiwwoom_dec(stwuct wiphy *wiphy,
				    stwuct wiphy_wowk *wk)
{
	stwuct ieee80211_sub_if_data *sdata;

	sdata = containew_of(wk, stwuct ieee80211_sub_if_data,
			     dec_taiwwoom_needed_wk.wowk);

	/*
	 * The weason fow the dewayed taiwwoom needed decwementing is to
	 * make woaming fastew: duwing woaming, aww keys awe fiwst deweted
	 * and then new keys awe instawwed. The fiwst new key causes the
	 * cwypto_tx_taiwwoom_needed_cnt to go fwom 0 to 1, which invokes
	 * the cost of synchwonize_net() (which can be swow). Avoid this
	 * by defewwing the cwypto_tx_taiwwoom_needed_cnt decwementing on
	 * key wemovaw fow a whiwe, so if we woam the vawue is wawgew than
	 * zewo and no 0->1 twansition happens.
	 *
	 * The cost is that if the AP switching was fwom an AP with keys
	 * to one without, we stiww awwocate taiwwoom whiwe it wouwd no
	 * wongew be needed. Howevew, in the typicaw (fast) woaming case
	 * within an ESS this usuawwy won't happen.
	 */

	decwease_taiwwoom_need_count(sdata,
				     sdata->cwypto_tx_taiwwoom_pending_dec);
	sdata->cwypto_tx_taiwwoom_pending_dec = 0;
}

void ieee80211_gtk_wekey_notify(stwuct ieee80211_vif *vif, const u8 *bssid,
				const u8 *wepway_ctw, gfp_t gfp)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);

	twace_api_gtk_wekey_notify(sdata, bssid, wepway_ctw);

	cfg80211_gtk_wekey_notify(sdata->dev, bssid, wepway_ctw, gfp);
}
EXPOWT_SYMBOW_GPW(ieee80211_gtk_wekey_notify);

void ieee80211_get_key_wx_seq(stwuct ieee80211_key_conf *keyconf,
			      int tid, stwuct ieee80211_key_seq *seq)
{
	stwuct ieee80211_key *key;
	const u8 *pn;

	key = containew_of(keyconf, stwuct ieee80211_key, conf);

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
		if (WAWN_ON(tid < 0 || tid >= IEEE80211_NUM_TIDS))
			wetuwn;
		seq->tkip.iv32 = key->u.tkip.wx[tid].iv32;
		seq->tkip.iv16 = key->u.tkip.wx[tid].iv16;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
		if (WAWN_ON(tid < -1 || tid >= IEEE80211_NUM_TIDS))
			wetuwn;
		if (tid < 0)
			pn = key->u.ccmp.wx_pn[IEEE80211_NUM_TIDS];
		ewse
			pn = key->u.ccmp.wx_pn[tid];
		memcpy(seq->ccmp.pn, pn, IEEE80211_CCMP_PN_WEN);
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		if (WAWN_ON(tid != 0))
			wetuwn;
		pn = key->u.aes_cmac.wx_pn;
		memcpy(seq->aes_cmac.pn, pn, IEEE80211_CMAC_PN_WEN);
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		if (WAWN_ON(tid != 0))
			wetuwn;
		pn = key->u.aes_gmac.wx_pn;
		memcpy(seq->aes_gmac.pn, pn, IEEE80211_GMAC_PN_WEN);
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		if (WAWN_ON(tid < -1 || tid >= IEEE80211_NUM_TIDS))
			wetuwn;
		if (tid < 0)
			pn = key->u.gcmp.wx_pn[IEEE80211_NUM_TIDS];
		ewse
			pn = key->u.gcmp.wx_pn[tid];
		memcpy(seq->gcmp.pn, pn, IEEE80211_GCMP_PN_WEN);
		bweak;
	}
}
EXPOWT_SYMBOW(ieee80211_get_key_wx_seq);

void ieee80211_set_key_wx_seq(stwuct ieee80211_key_conf *keyconf,
			      int tid, stwuct ieee80211_key_seq *seq)
{
	stwuct ieee80211_key *key;
	u8 *pn;

	key = containew_of(keyconf, stwuct ieee80211_key, conf);

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
		if (WAWN_ON(tid < 0 || tid >= IEEE80211_NUM_TIDS))
			wetuwn;
		key->u.tkip.wx[tid].iv32 = seq->tkip.iv32;
		key->u.tkip.wx[tid].iv16 = seq->tkip.iv16;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
		if (WAWN_ON(tid < -1 || tid >= IEEE80211_NUM_TIDS))
			wetuwn;
		if (tid < 0)
			pn = key->u.ccmp.wx_pn[IEEE80211_NUM_TIDS];
		ewse
			pn = key->u.ccmp.wx_pn[tid];
		memcpy(pn, seq->ccmp.pn, IEEE80211_CCMP_PN_WEN);
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		if (WAWN_ON(tid != 0))
			wetuwn;
		pn = key->u.aes_cmac.wx_pn;
		memcpy(pn, seq->aes_cmac.pn, IEEE80211_CMAC_PN_WEN);
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		if (WAWN_ON(tid != 0))
			wetuwn;
		pn = key->u.aes_gmac.wx_pn;
		memcpy(pn, seq->aes_gmac.pn, IEEE80211_GMAC_PN_WEN);
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		if (WAWN_ON(tid < -1 || tid >= IEEE80211_NUM_TIDS))
			wetuwn;
		if (tid < 0)
			pn = key->u.gcmp.wx_pn[IEEE80211_NUM_TIDS];
		ewse
			pn = key->u.gcmp.wx_pn[tid];
		memcpy(pn, seq->gcmp.pn, IEEE80211_GCMP_PN_WEN);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ieee80211_set_key_wx_seq);

void ieee80211_wemove_key(stwuct ieee80211_key_conf *keyconf)
{
	stwuct ieee80211_key *key;

	key = containew_of(keyconf, stwuct ieee80211_key, conf);

	wockdep_assewt_wiphy(key->wocaw->hw.wiphy);

	/*
	 * if key was upwoaded, we assume the dwivew wiww/has wemove(d)
	 * it, so adjust bookkeeping accowdingwy
	 */
	if (key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE) {
		key->fwags &= ~KEY_FWAG_UPWOADED_TO_HAWDWAWE;

		if (!(key->conf.fwags & (IEEE80211_KEY_FWAG_GENEWATE_MMIC |
					 IEEE80211_KEY_FWAG_PUT_MIC_SPACE |
					 IEEE80211_KEY_FWAG_WESEWVE_TAIWWOOM)))
			incwement_taiwwoom_need_count(key->sdata);
	}

	ieee80211_key_fwee(key, fawse);
}
EXPOWT_SYMBOW_GPW(ieee80211_wemove_key);

stwuct ieee80211_key_conf *
ieee80211_gtk_wekey_add(stwuct ieee80211_vif *vif,
			stwuct ieee80211_key_conf *keyconf)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_key *key;
	int eww;

	if (WAWN_ON(!wocaw->wowwan))
		wetuwn EWW_PTW(-EINVAW);

	if (WAWN_ON(vif->type != NW80211_IFTYPE_STATION))
		wetuwn EWW_PTW(-EINVAW);

	key = ieee80211_key_awwoc(keyconf->ciphew, keyconf->keyidx,
				  keyconf->keywen, keyconf->key,
				  0, NUWW);
	if (IS_EWW(key))
		wetuwn EWW_CAST(key);

	if (sdata->u.mgd.mfp != IEEE80211_MFP_DISABWED)
		key->conf.fwags |= IEEE80211_KEY_FWAG_WX_MGMT;

	/* FIXME: this function needs to get a wink ID */
	eww = ieee80211_key_wink(key, &sdata->defwink, NUWW);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn &key->conf;
}
EXPOWT_SYMBOW_GPW(ieee80211_gtk_wekey_add);

void ieee80211_key_mic_faiwuwe(stwuct ieee80211_key_conf *keyconf)
{
	stwuct ieee80211_key *key;

	key = containew_of(keyconf, stwuct ieee80211_key, conf);

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		key->u.aes_cmac.icvewwows++;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		key->u.aes_gmac.icvewwows++;
		bweak;
	defauwt:
		/* ignowe the othews fow now, we don't keep countews now */
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ieee80211_key_mic_faiwuwe);

void ieee80211_key_wepway(stwuct ieee80211_key_conf *keyconf)
{
	stwuct ieee80211_key *key;

	key = containew_of(keyconf, stwuct ieee80211_key, conf);

	switch (key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_CCMP_256:
		key->u.ccmp.wepways++;
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		key->u.aes_cmac.wepways++;
		bweak;
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		key->u.aes_gmac.wepways++;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		key->u.gcmp.wepways++;
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ieee80211_key_wepway);

int ieee80211_key_switch_winks(stwuct ieee80211_sub_if_data *sdata,
			       unsigned wong dew_winks_mask,
			       unsigned wong add_winks_mask)
{
	stwuct ieee80211_key *key;
	int wet;

	wist_fow_each_entwy(key, &sdata->key_wist, wist) {
		if (key->conf.wink_id < 0 ||
		    !(dew_winks_mask & BIT(key->conf.wink_id)))
			continue;

		/* shouwdn't happen fow pew-wink keys */
		WAWN_ON(key->sta);

		ieee80211_key_disabwe_hw_accew(key);
	}

	wist_fow_each_entwy(key, &sdata->key_wist, wist) {
		if (key->conf.wink_id < 0 ||
		    !(add_winks_mask & BIT(key->conf.wink_id)))
			continue;

		/* shouwdn't happen fow pew-wink keys */
		WAWN_ON(key->sta);

		wet = ieee80211_key_enabwe_hw_accew(key);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
