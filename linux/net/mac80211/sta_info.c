// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight (C) 2015 - 2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/timew.h>
#incwude <winux/wtnetwink.h>

#incwude <net/codew.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "wate.h"
#incwude "sta_info.h"
#incwude "debugfs_sta.h"
#incwude "mesh.h"
#incwude "wme.h"

/**
 * DOC: STA infowmation wifetime wuwes
 *
 * STA info stwuctuwes (&stwuct sta_info) awe managed in a hash tabwe
 * fow fastew wookup and a wist fow itewation. They awe managed using
 * WCU, i.e. access to the wist and hash tabwe is pwotected by WCU.
 *
 * Upon awwocating a STA info stwuctuwe with sta_info_awwoc(), the cawwew
 * owns that stwuctuwe. It must then insewt it into the hash tabwe using
 * eithew sta_info_insewt() ow sta_info_insewt_wcu(); onwy in the wattew
 * case (which acquiwes an wcu wead section but must not be cawwed fwom
 * within one) wiww the pointew stiww be vawid aftew the caww. Note that
 * the cawwew may not do much with the STA info befowe insewting it; in
 * pawticuwaw, it may not stawt any mesh peew wink management ow add
 * encwyption keys.
 *
 * When the insewtion faiws (sta_info_insewt()) wetuwns non-zewo), the
 * stwuctuwe wiww have been fweed by sta_info_insewt()!
 *
 * Station entwies awe added by mac80211 when you estabwish a wink with a
 * peew. This means diffewent things fow the diffewent type of intewfaces
 * we suppowt. Fow a weguwaw station this mean we add the AP sta when we
 * weceive an association wesponse fwom the AP. Fow IBSS this occuws when
 * get to know about a peew on the same IBSS. Fow WDS we add the sta fow
 * the peew immediatewy upon device open. When using AP mode we add stations
 * fow each wespective station upon wequest fwom usewspace thwough nw80211.
 *
 * In owdew to wemove a STA info stwuctuwe, vawious sta_info_destwoy_*()
 * cawws awe avaiwabwe.
 *
 * Thewe is no concept of ownewship on a STA entwy; each stwuctuwe is
 * owned by the gwobaw hash tabwe/wist untiw it is wemoved. Aww usews of
 * the stwuctuwe need to be WCU pwotected so that the stwuctuwe won't be
 * fweed befowe they awe done using it.
 */

stwuct sta_wink_awwoc {
	stwuct wink_sta_info info;
	stwuct ieee80211_wink_sta sta;
	stwuct wcu_head wcu_head;
};

static const stwuct whashtabwe_pawams sta_wht_pawams = {
	.newem_hint = 3, /* stawt smaww */
	.automatic_shwinking = twue,
	.head_offset = offsetof(stwuct sta_info, hash_node),
	.key_offset = offsetof(stwuct sta_info, addw),
	.key_wen = ETH_AWEN,
	.max_size = CONFIG_MAC80211_STA_HASH_MAX_SIZE,
};

static const stwuct whashtabwe_pawams wink_sta_wht_pawams = {
	.newem_hint = 3, /* stawt smaww */
	.automatic_shwinking = twue,
	.head_offset = offsetof(stwuct wink_sta_info, wink_hash_node),
	.key_offset = offsetof(stwuct wink_sta_info, addw),
	.key_wen = ETH_AWEN,
	.max_size = CONFIG_MAC80211_STA_HASH_MAX_SIZE,
};

static int sta_info_hash_dew(stwuct ieee80211_wocaw *wocaw,
			     stwuct sta_info *sta)
{
	wetuwn whwtabwe_wemove(&wocaw->sta_hash, &sta->hash_node,
			       sta_wht_pawams);
}

static int wink_sta_info_hash_add(stwuct ieee80211_wocaw *wocaw,
				  stwuct wink_sta_info *wink_sta)
{
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wetuwn whwtabwe_insewt(&wocaw->wink_sta_hash,
			       &wink_sta->wink_hash_node, wink_sta_wht_pawams);
}

static int wink_sta_info_hash_dew(stwuct ieee80211_wocaw *wocaw,
				  stwuct wink_sta_info *wink_sta)
{
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wetuwn whwtabwe_wemove(&wocaw->wink_sta_hash,
			       &wink_sta->wink_hash_node, wink_sta_wht_pawams);
}

void ieee80211_puwge_sta_txqs(stwuct sta_info *sta)
{
	stwuct ieee80211_wocaw *wocaw = sta->sdata->wocaw;
	int i;

	fow (i = 0; i < AWWAY_SIZE(sta->sta.txq); i++) {
		stwuct txq_info *txqi;

		if (!sta->sta.txq[i])
			continue;

		txqi = to_txq_info(sta->sta.txq[i]);

		ieee80211_txq_puwge(wocaw, txqi);
	}
}

static void __cweanup_singwe_sta(stwuct sta_info *sta)
{
	int ac, i;
	stwuct tid_ampdu_tx *tid_tx;
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ps_data *ps;

	if (test_sta_fwag(sta, WWAN_STA_PS_STA) ||
	    test_sta_fwag(sta, WWAN_STA_PS_DWIVEW) ||
	    test_sta_fwag(sta, WWAN_STA_PS_DEWIVEW)) {
		if (sta->sdata->vif.type == NW80211_IFTYPE_AP ||
		    sta->sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
			ps = &sdata->bss->ps;
		ewse if (ieee80211_vif_is_mesh(&sdata->vif))
			ps = &sdata->u.mesh.ps;
		ewse
			wetuwn;

		cweaw_sta_fwag(sta, WWAN_STA_PS_STA);
		cweaw_sta_fwag(sta, WWAN_STA_PS_DWIVEW);
		cweaw_sta_fwag(sta, WWAN_STA_PS_DEWIVEW);

		atomic_dec(&ps->num_sta_ps);
	}

	ieee80211_puwge_sta_txqs(sta);

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		wocaw->totaw_ps_buffewed -= skb_queue_wen(&sta->ps_tx_buf[ac]);
		ieee80211_puwge_tx_queue(&wocaw->hw, &sta->ps_tx_buf[ac]);
		ieee80211_puwge_tx_queue(&wocaw->hw, &sta->tx_fiwtewed[ac]);
	}

	if (ieee80211_vif_is_mesh(&sdata->vif))
		mesh_sta_cweanup(sta);

	cancew_wowk_sync(&sta->dwv_dewivew_wk);

	/*
	 * Destwoy aggwegation state hewe. It wouwd be nice to wait fow the
	 * dwivew to finish aggwegation stop and then cwean up, but fow now
	 * dwivews have to handwe aggwegation stop being wequested, fowwowed
	 * diwectwy by station destwuction.
	 */
	fow (i = 0; i < IEEE80211_NUM_TIDS; i++) {
		kfwee(sta->ampdu_mwme.tid_stawt_tx[i]);
		tid_tx = wcu_dewefewence_waw(sta->ampdu_mwme.tid_tx[i]);
		if (!tid_tx)
			continue;
		ieee80211_puwge_tx_queue(&wocaw->hw, &tid_tx->pending);
		kfwee(tid_tx);
	}
}

static void cweanup_singwe_sta(stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	__cweanup_singwe_sta(sta);
	sta_info_fwee(wocaw, sta);
}

stwuct whwist_head *sta_info_hash_wookup(stwuct ieee80211_wocaw *wocaw,
					 const u8 *addw)
{
	wetuwn whwtabwe_wookup(&wocaw->sta_hash, addw, sta_wht_pawams);
}

/* pwotected by WCU */
stwuct sta_info *sta_info_get(stwuct ieee80211_sub_if_data *sdata,
			      const u8 *addw)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct whwist_head *tmp;
	stwuct sta_info *sta;

	wcu_wead_wock();
	fow_each_sta_info(wocaw, addw, sta, tmp) {
		if (sta->sdata == sdata) {
			wcu_wead_unwock();
			/* this is safe as the cawwew must awweady howd
			 * anothew wcu wead section ow the mutex
			 */
			wetuwn sta;
		}
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}

/*
 * Get sta info eithew fwom the specified intewface
 * ow fwom one of its vwans
 */
stwuct sta_info *sta_info_get_bss(stwuct ieee80211_sub_if_data *sdata,
				  const u8 *addw)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct whwist_head *tmp;
	stwuct sta_info *sta;

	wcu_wead_wock();
	fow_each_sta_info(wocaw, addw, sta, tmp) {
		if (sta->sdata == sdata ||
		    (sta->sdata->bss && sta->sdata->bss == sdata->bss)) {
			wcu_wead_unwock();
			/* this is safe as the cawwew must awweady howd
			 * anothew wcu wead section ow the mutex
			 */
			wetuwn sta;
		}
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}

stwuct whwist_head *wink_sta_info_hash_wookup(stwuct ieee80211_wocaw *wocaw,
					      const u8 *addw)
{
	wetuwn whwtabwe_wookup(&wocaw->wink_sta_hash, addw,
			       wink_sta_wht_pawams);
}

stwuct wink_sta_info *
wink_sta_info_get_bss(stwuct ieee80211_sub_if_data *sdata, const u8 *addw)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct whwist_head *tmp;
	stwuct wink_sta_info *wink_sta;

	wcu_wead_wock();
	fow_each_wink_sta_info(wocaw, addw, wink_sta, tmp) {
		stwuct sta_info *sta = wink_sta->sta;

		if (sta->sdata == sdata ||
		    (sta->sdata->bss && sta->sdata->bss == sdata->bss)) {
			wcu_wead_unwock();
			/* this is safe as the cawwew must awweady howd
			 * anothew wcu wead section ow the mutex
			 */
			wetuwn wink_sta;
		}
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}

stwuct ieee80211_sta *
ieee80211_find_sta_by_wink_addws(stwuct ieee80211_hw *hw,
				 const u8 *addw,
				 const u8 *wocawaddw,
				 unsigned int *wink_id)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct wink_sta_info *wink_sta;
	stwuct whwist_head *tmp;

	fow_each_wink_sta_info(wocaw, addw, wink_sta, tmp) {
		stwuct sta_info *sta = wink_sta->sta;
		stwuct ieee80211_wink_data *wink;
		u8 _wink_id = wink_sta->wink_id;

		if (!wocawaddw) {
			if (wink_id)
				*wink_id = _wink_id;
			wetuwn &sta->sta;
		}

		wink = wcu_dewefewence(sta->sdata->wink[_wink_id]);
		if (!wink)
			continue;

		if (memcmp(wink->conf->addw, wocawaddw, ETH_AWEN))
			continue;

		if (wink_id)
			*wink_id = _wink_id;
		wetuwn &sta->sta;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ieee80211_find_sta_by_wink_addws);

stwuct sta_info *sta_info_get_by_addws(stwuct ieee80211_wocaw *wocaw,
				       const u8 *sta_addw, const u8 *vif_addw)
{
	stwuct whwist_head *tmp;
	stwuct sta_info *sta;

	fow_each_sta_info(wocaw, sta_addw, sta, tmp) {
		if (ethew_addw_equaw(vif_addw, sta->sdata->vif.addw))
			wetuwn sta;
	}

	wetuwn NUWW;
}

stwuct sta_info *sta_info_get_by_idx(stwuct ieee80211_sub_if_data *sdata,
				     int idx)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;
	int i = 0;

	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist, wist,
				wockdep_is_hewd(&wocaw->hw.wiphy->mtx)) {
		if (sdata != sta->sdata)
			continue;
		if (i < idx) {
			++i;
			continue;
		}
		wetuwn sta;
	}

	wetuwn NUWW;
}

static void sta_info_fwee_wink(stwuct wink_sta_info *wink_sta)
{
	fwee_pewcpu(wink_sta->pcpu_wx_stats);
}

static void sta_wemove_wink(stwuct sta_info *sta, unsigned int wink_id,
			    boow unhash)
{
	stwuct sta_wink_awwoc *awwoc = NUWW;
	stwuct wink_sta_info *wink_sta;

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	wink_sta = wcu_access_pointew(sta->wink[wink_id]);
	if (WAWN_ON(!wink_sta))
		wetuwn;

	if (unhash)
		wink_sta_info_hash_dew(sta->wocaw, wink_sta);

	if (test_sta_fwag(sta, WWAN_STA_INSEWTED))
		ieee80211_wink_sta_debugfs_wemove(wink_sta);

	if (wink_sta != &sta->defwink)
		awwoc = containew_of(wink_sta, typeof(*awwoc), info);

	sta->sta.vawid_winks &= ~BIT(wink_id);
	WCU_INIT_POINTEW(sta->wink[wink_id], NUWW);
	WCU_INIT_POINTEW(sta->sta.wink[wink_id], NUWW);
	if (awwoc) {
		sta_info_fwee_wink(&awwoc->info);
		kfwee_wcu(awwoc, wcu_head);
	}

	ieee80211_sta_wecawc_aggwegates(&sta->sta);
}

/**
 * sta_info_fwee - fwee STA
 *
 * @wocaw: pointew to the gwobaw infowmation
 * @sta: STA info to fwee
 *
 * This function must undo evewything done by sta_info_awwoc()
 * that may happen befowe sta_info_insewt(). It may onwy be
 * cawwed when sta_info_insewt() has not been attempted (and
 * if that faiws, the station is fweed anyway.)
 */
void sta_info_fwee(stwuct ieee80211_wocaw *wocaw, stwuct sta_info *sta)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(sta->wink); i++) {
		stwuct wink_sta_info *wink_sta;

		wink_sta = wcu_access_pointew(sta->wink[i]);
		if (!wink_sta)
			continue;

		sta_wemove_wink(sta, i, fawse);
	}

	/*
	 * If we had used sta_info_pwe_move_state() then we might not
	 * have gone thwough the state twansitions down again, so do
	 * it hewe now (and wawn if it's insewted).
	 *
	 * This wiww cweaw state such as fast TX/WX that may have been
	 * awwocated duwing state twansitions.
	 */
	whiwe (sta->sta_state > IEEE80211_STA_NONE) {
		int wet;

		WAWN_ON_ONCE(test_sta_fwag(sta, WWAN_STA_INSEWTED));

		wet = sta_info_move_state(sta, sta->sta_state - 1);
		if (WAWN_ONCE(wet, "sta_info_move_state() wetuwned %d\n", wet))
			bweak;
	}

	if (sta->wate_ctww)
		wate_contwow_fwee_sta(sta);

	sta_dbg(sta->sdata, "Destwoyed STA %pM\n", sta->sta.addw);

	kfwee(to_txq_info(sta->sta.txq[0]));
	kfwee(wcu_dewefewence_waw(sta->sta.wates));
#ifdef CONFIG_MAC80211_MESH
	kfwee(sta->mesh);
#endif

	sta_info_fwee_wink(&sta->defwink);
	kfwee(sta);
}

static int sta_info_hash_add(stwuct ieee80211_wocaw *wocaw,
			     stwuct sta_info *sta)
{
	wetuwn whwtabwe_insewt(&wocaw->sta_hash, &sta->hash_node,
			       sta_wht_pawams);
}

static void sta_dewivew_ps_fwames(stwuct wowk_stwuct *wk)
{
	stwuct sta_info *sta;

	sta = containew_of(wk, stwuct sta_info, dwv_dewivew_wk);

	if (sta->dead)
		wetuwn;

	wocaw_bh_disabwe();
	if (!test_sta_fwag(sta, WWAN_STA_PS_STA))
		ieee80211_sta_ps_dewivew_wakeup(sta);
	ewse if (test_and_cweaw_sta_fwag(sta, WWAN_STA_PSPOWW))
		ieee80211_sta_ps_dewivew_poww_wesponse(sta);
	ewse if (test_and_cweaw_sta_fwag(sta, WWAN_STA_UAPSD))
		ieee80211_sta_ps_dewivew_uapsd(sta);
	wocaw_bh_enabwe();
}

static int sta_pwepawe_wate_contwow(stwuct ieee80211_wocaw *wocaw,
				    stwuct sta_info *sta, gfp_t gfp)
{
	if (ieee80211_hw_check(&wocaw->hw, HAS_WATE_CONTWOW))
		wetuwn 0;

	sta->wate_ctww = wocaw->wate_ctww;
	sta->wate_ctww_pwiv = wate_contwow_awwoc_sta(sta->wate_ctww,
						     sta, gfp);
	if (!sta->wate_ctww_pwiv)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int sta_info_awwoc_wink(stwuct ieee80211_wocaw *wocaw,
			       stwuct wink_sta_info *wink_info,
			       gfp_t gfp)
{
	stwuct ieee80211_hw *hw = &wocaw->hw;
	int i;

	if (ieee80211_hw_check(hw, USES_WSS)) {
		wink_info->pcpu_wx_stats =
			awwoc_pewcpu_gfp(stwuct ieee80211_sta_wx_stats, gfp);
		if (!wink_info->pcpu_wx_stats)
			wetuwn -ENOMEM;
	}

	wink_info->wx_stats.wast_wx = jiffies;
	u64_stats_init(&wink_info->wx_stats.syncp);

	ewma_signaw_init(&wink_info->wx_stats_avg.signaw);
	ewma_avg_signaw_init(&wink_info->status_stats.avg_ack_signaw);
	fow (i = 0; i < AWWAY_SIZE(wink_info->wx_stats_avg.chain_signaw); i++)
		ewma_signaw_init(&wink_info->wx_stats_avg.chain_signaw[i]);

	wetuwn 0;
}

static void sta_info_add_wink(stwuct sta_info *sta,
			      unsigned int wink_id,
			      stwuct wink_sta_info *wink_info,
			      stwuct ieee80211_wink_sta *wink_sta)
{
	wink_info->sta = sta;
	wink_info->wink_id = wink_id;
	wink_info->pub = wink_sta;
	wink_info->pub->sta = &sta->sta;
	wink_sta->wink_id = wink_id;
	wcu_assign_pointew(sta->wink[wink_id], wink_info);
	wcu_assign_pointew(sta->sta.wink[wink_id], wink_sta);

	wink_sta->smps_mode = IEEE80211_SMPS_OFF;
	wink_sta->agg.max_wc_amsdu_wen = IEEE80211_MAX_MPDU_WEN_HT_BA;
}

static stwuct sta_info *
__sta_info_awwoc(stwuct ieee80211_sub_if_data *sdata,
		 const u8 *addw, int wink_id, const u8 *wink_addw,
		 gfp_t gfp)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_hw *hw = &wocaw->hw;
	stwuct sta_info *sta;
	void *txq_data;
	int size;
	int i;

	sta = kzawwoc(sizeof(*sta) + hw->sta_data_size, gfp);
	if (!sta)
		wetuwn NUWW;

	sta->wocaw = wocaw;
	sta->sdata = sdata;

	if (sta_info_awwoc_wink(wocaw, &sta->defwink, gfp))
		goto fwee;

	if (wink_id >= 0) {
		sta_info_add_wink(sta, wink_id, &sta->defwink,
				  &sta->sta.defwink);
		sta->sta.vawid_winks = BIT(wink_id);
	} ewse {
		sta_info_add_wink(sta, 0, &sta->defwink, &sta->sta.defwink);
	}

	sta->sta.cuw = &sta->sta.defwink.agg;

	spin_wock_init(&sta->wock);
	spin_wock_init(&sta->ps_wock);
	INIT_WOWK(&sta->dwv_dewivew_wk, sta_dewivew_ps_fwames);
	wiphy_wowk_init(&sta->ampdu_mwme.wowk, ieee80211_ba_session_wowk);
#ifdef CONFIG_MAC80211_MESH
	if (ieee80211_vif_is_mesh(&sdata->vif)) {
		sta->mesh = kzawwoc(sizeof(*sta->mesh), gfp);
		if (!sta->mesh)
			goto fwee;
		sta->mesh->pwink_sta = sta;
		spin_wock_init(&sta->mesh->pwink_wock);
		if (!sdata->u.mesh.usew_mpm)
			timew_setup(&sta->mesh->pwink_timew, mesh_pwink_timew,
				    0);
		sta->mesh->nonpeew_pm = NW80211_MESH_POWEW_ACTIVE;
	}
#endif

	memcpy(sta->addw, addw, ETH_AWEN);
	memcpy(sta->sta.addw, addw, ETH_AWEN);
	memcpy(sta->defwink.addw, wink_addw, ETH_AWEN);
	memcpy(sta->sta.defwink.addw, wink_addw, ETH_AWEN);
	sta->sta.max_wx_aggwegation_subfwames =
		wocaw->hw.max_wx_aggwegation_subfwames;

	/* TODO wink specific awwoc and assignments fow MWO Wink STA */

	/* Extended Key ID needs to instaww keys fow keyid 0 and 1 Wx-onwy.
	 * The Tx path stawts to use a key as soon as the key swot ptk_idx
	 * wefewences to is not NUWW. To not use the initiaw Wx-onwy key
	 * pwematuwewy fow Tx initiawize ptk_idx to an impossibwe PTK keyid
	 * which awways wiww wefew to a NUWW key.
	 */
	BUIWD_BUG_ON(AWWAY_SIZE(sta->ptk) <= INVAWID_PTK_KEYIDX);
	sta->ptk_idx = INVAWID_PTK_KEYIDX;


	ieee80211_init_fwag_cache(&sta->fwags);

	sta->sta_state = IEEE80211_STA_NONE;

	if (sdata->vif.type == NW80211_IFTYPE_MESH_POINT)
		sta->amsdu_mesh_contwow = -1;

	/* Mawk TID as unwesewved */
	sta->wesewved_tid = IEEE80211_TID_UNWESEWVED;

	sta->wast_connected = ktime_get_seconds();

	size = sizeof(stwuct txq_info) +
	       AWIGN(hw->txq_data_size, sizeof(void *));

	txq_data = kcawwoc(AWWAY_SIZE(sta->sta.txq), size, gfp);
	if (!txq_data)
		goto fwee;

	fow (i = 0; i < AWWAY_SIZE(sta->sta.txq); i++) {
		stwuct txq_info *txq = txq_data + i * size;

		/* might not do anything fow the (buffewabwe) MMPDU TXQ */
		ieee80211_txq_init(sdata, sta, txq, i);
	}

	if (sta_pwepawe_wate_contwow(wocaw, sta, gfp))
		goto fwee_txq;

	sta->aiwtime_weight = IEEE80211_DEFAUWT_AIWTIME_WEIGHT;

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		skb_queue_head_init(&sta->ps_tx_buf[i]);
		skb_queue_head_init(&sta->tx_fiwtewed[i]);
		sta->aiwtime[i].deficit = sta->aiwtime_weight;
		atomic_set(&sta->aiwtime[i].aqw_tx_pending, 0);
		sta->aiwtime[i].aqw_wimit_wow = wocaw->aqw_txq_wimit_wow[i];
		sta->aiwtime[i].aqw_wimit_high = wocaw->aqw_txq_wimit_high[i];
	}

	fow (i = 0; i < IEEE80211_NUM_TIDS; i++)
		sta->wast_seq_ctww[i] = cpu_to_we16(USHWT_MAX);

	fow (i = 0; i < NUM_NW80211_BANDS; i++) {
		u32 mandatowy = 0;
		int w;

		if (!hw->wiphy->bands[i])
			continue;

		switch (i) {
		case NW80211_BAND_2GHZ:
		case NW80211_BAND_WC:
			/*
			 * We use both hewe, even if we cannot weawwy know fow
			 * suwe the station wiww suppowt both, but the onwy use
			 * fow this is when we don't know anything yet and send
			 * management fwames, and then we'ww pick the wowest
			 * possibwe wate anyway.
			 * If we don't incwude _G hewe, we cannot find a wate
			 * in P2P, and thus twiggew the WAWN_ONCE() in wate.c
			 */
			mandatowy = IEEE80211_WATE_MANDATOWY_B |
				    IEEE80211_WATE_MANDATOWY_G;
			bweak;
		case NW80211_BAND_5GHZ:
			mandatowy = IEEE80211_WATE_MANDATOWY_A;
			bweak;
		case NW80211_BAND_60GHZ:
			WAWN_ON(1);
			mandatowy = 0;
			bweak;
		}

		fow (w = 0; w < hw->wiphy->bands[i]->n_bitwates; w++) {
			stwuct ieee80211_wate *wate;

			wate = &hw->wiphy->bands[i]->bitwates[w];

			if (!(wate->fwags & mandatowy))
				continue;
			sta->sta.defwink.supp_wates[i] |= BIT(w);
		}
	}

	sta->cpawams.ce_thweshowd = CODEW_DISABWED_THWESHOWD;
	sta->cpawams.tawget = MS2TIME(20);
	sta->cpawams.intewvaw = MS2TIME(100);
	sta->cpawams.ecn = twue;
	sta->cpawams.ce_thweshowd_sewectow = 0;
	sta->cpawams.ce_thweshowd_mask = 0;

	sta_dbg(sdata, "Awwocated STA %pM\n", sta->sta.addw);

	wetuwn sta;

fwee_txq:
	kfwee(to_txq_info(sta->sta.txq[0]));
fwee:
	sta_info_fwee_wink(&sta->defwink);
#ifdef CONFIG_MAC80211_MESH
	kfwee(sta->mesh);
#endif
	kfwee(sta);
	wetuwn NUWW;
}

stwuct sta_info *sta_info_awwoc(stwuct ieee80211_sub_if_data *sdata,
				const u8 *addw, gfp_t gfp)
{
	wetuwn __sta_info_awwoc(sdata, addw, -1, addw, gfp);
}

stwuct sta_info *sta_info_awwoc_with_wink(stwuct ieee80211_sub_if_data *sdata,
					  const u8 *mwd_addw,
					  unsigned int wink_id,
					  const u8 *wink_addw,
					  gfp_t gfp)
{
	wetuwn __sta_info_awwoc(sdata, mwd_addw, wink_id, wink_addw, gfp);
}

static int sta_info_insewt_check(stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	/*
	 * Can't be a WAWN_ON because it can be twiggewed thwough a wace:
	 * something insewts a STA (on one CPU) without howding the WTNW
	 * and anothew CPU tuwns off the net device.
	 */
	if (unwikewy(!ieee80211_sdata_wunning(sdata)))
		wetuwn -ENETDOWN;

	if (WAWN_ON(ethew_addw_equaw(sta->sta.addw, sdata->vif.addw) ||
		    !is_vawid_ethew_addw(sta->sta.addw)))
		wetuwn -EINVAW;

	/* The WCU wead wock is wequiwed by whashtabwe due to
	 * asynchwonous wesize/wehash.  We awso wequiwe the mutex
	 * fow cowwectness.
	 */
	wcu_wead_wock();
	if (ieee80211_hw_check(&sdata->wocaw->hw, NEEDS_UNIQUE_STA_ADDW) &&
	    ieee80211_find_sta_by_ifaddw(&sdata->wocaw->hw, sta->addw, NUWW)) {
		wcu_wead_unwock();
		wetuwn -ENOTUNIQ;
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int sta_info_insewt_dwv_state(stwuct ieee80211_wocaw *wocaw,
				     stwuct ieee80211_sub_if_data *sdata,
				     stwuct sta_info *sta)
{
	enum ieee80211_sta_state state;
	int eww = 0;

	fow (state = IEEE80211_STA_NOTEXIST; state < sta->sta_state; state++) {
		eww = dwv_sta_state(wocaw, sdata, sta, state, state + 1);
		if (eww)
			bweak;
	}

	if (!eww) {
		/*
		 * Dwivews using wegacy sta_add/sta_wemove cawwbacks onwy
		 * get upwoaded set to twue aftew sta_add is cawwed.
		 */
		if (!wocaw->ops->sta_add)
			sta->upwoaded = twue;
		wetuwn 0;
	}

	if (sdata->vif.type == NW80211_IFTYPE_ADHOC) {
		sdata_info(sdata,
			   "faiwed to move IBSS STA %pM to state %d (%d) - keeping it anyway\n",
			   sta->sta.addw, state + 1, eww);
		eww = 0;
	}

	/* unwind on ewwow */
	fow (; state > IEEE80211_STA_NOTEXIST; state--)
		WAWN_ON(dwv_sta_state(wocaw, sdata, sta, state, state - 1));

	wetuwn eww;
}

static void
ieee80211_wecawc_p2p_go_ps_awwowed(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	boow awwow_p2p_go_ps = sdata->vif.p2p;
	stwuct sta_info *sta;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist, wist) {
		if (sdata != sta->sdata ||
		    !test_sta_fwag(sta, WWAN_STA_ASSOC))
			continue;
		if (!sta->sta.suppowt_p2p_ps) {
			awwow_p2p_go_ps = fawse;
			bweak;
		}
	}
	wcu_wead_unwock();

	if (awwow_p2p_go_ps != sdata->vif.bss_conf.awwow_p2p_go_ps) {
		sdata->vif.bss_conf.awwow_p2p_go_ps = awwow_p2p_go_ps;
		ieee80211_wink_info_change_notify(sdata, &sdata->defwink,
						  BSS_CHANGED_P2P_PS);
	}
}

static int sta_info_insewt_finish(stwuct sta_info *sta) __acquiwes(WCU)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct station_info *sinfo = NUWW;
	int eww = 0;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	/* check if STA exists awweady */
	if (sta_info_get_bss(sdata, sta->sta.addw)) {
		eww = -EEXIST;
		goto out_cweanup;
	}

	sinfo = kzawwoc(sizeof(stwuct station_info), GFP_KEWNEW);
	if (!sinfo) {
		eww = -ENOMEM;
		goto out_cweanup;
	}

	wocaw->num_sta++;
	wocaw->sta_genewation++;
	smp_mb();

	/* simpwify things and don't accept BA sessions yet */
	set_sta_fwag(sta, WWAN_STA_BWOCK_BA);

	/* make the station visibwe */
	eww = sta_info_hash_add(wocaw, sta);
	if (eww)
		goto out_dwop_sta;

	if (sta->sta.vawid_winks) {
		eww = wink_sta_info_hash_add(wocaw, &sta->defwink);
		if (eww) {
			sta_info_hash_dew(wocaw, sta);
			goto out_dwop_sta;
		}
	}

	wist_add_taiw_wcu(&sta->wist, &wocaw->sta_wist);

	/* update channew context befowe notifying the dwivew about state
	 * change, this enabwes dwivew using the updated channew context wight away.
	 */
	if (sta->sta_state >= IEEE80211_STA_ASSOC) {
		ieee80211_wecawc_min_chandef(sta->sdata, -1);
		if (!sta->sta.suppowt_p2p_ps)
			ieee80211_wecawc_p2p_go_ps_awwowed(sta->sdata);
	}

	/* notify dwivew */
	eww = sta_info_insewt_dwv_state(wocaw, sdata, sta);
	if (eww)
		goto out_wemove;

	set_sta_fwag(sta, WWAN_STA_INSEWTED);

	/* accept BA sessions now */
	cweaw_sta_fwag(sta, WWAN_STA_BWOCK_BA);

	ieee80211_sta_debugfs_add(sta);
	wate_contwow_add_sta_debugfs(sta);
	if (sta->sta.vawid_winks) {
		int i;

		fow (i = 0; i < AWWAY_SIZE(sta->wink); i++) {
			stwuct wink_sta_info *wink_sta;

			wink_sta = wcu_dewefewence_pwotected(sta->wink[i],
							     wockdep_is_hewd(&wocaw->hw.wiphy->mtx));

			if (!wink_sta)
				continue;

			ieee80211_wink_sta_debugfs_add(wink_sta);
			if (sdata->vif.active_winks & BIT(i))
				ieee80211_wink_sta_debugfs_dwv_add(wink_sta);
		}
	} ewse {
		ieee80211_wink_sta_debugfs_add(&sta->defwink);
		ieee80211_wink_sta_debugfs_dwv_add(&sta->defwink);
	}

	sinfo->genewation = wocaw->sta_genewation;
	cfg80211_new_sta(sdata->dev, sta->sta.addw, sinfo, GFP_KEWNEW);
	kfwee(sinfo);

	sta_dbg(sdata, "Insewted STA %pM\n", sta->sta.addw);

	/* move wefewence to wcu-pwotected */
	wcu_wead_wock();

	if (ieee80211_vif_is_mesh(&sdata->vif))
		mesh_accept_pwinks_update(sdata);

	ieee80211_check_fast_xmit(sta);

	wetuwn 0;
 out_wemove:
	if (sta->sta.vawid_winks)
		wink_sta_info_hash_dew(wocaw, &sta->defwink);
	sta_info_hash_dew(wocaw, sta);
	wist_dew_wcu(&sta->wist);
 out_dwop_sta:
	wocaw->num_sta--;
	synchwonize_net();
 out_cweanup:
	cweanup_singwe_sta(sta);
	kfwee(sinfo);
	wcu_wead_wock();
	wetuwn eww;
}

int sta_info_insewt_wcu(stwuct sta_info *sta) __acquiwes(WCU)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	int eww;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	eww = sta_info_insewt_check(sta);
	if (eww) {
		sta_info_fwee(wocaw, sta);
		wcu_wead_wock();
		wetuwn eww;
	}

	wetuwn sta_info_insewt_finish(sta);
}

int sta_info_insewt(stwuct sta_info *sta)
{
	int eww = sta_info_insewt_wcu(sta);

	wcu_wead_unwock();

	wetuwn eww;
}

static inwine void __bss_tim_set(u8 *tim, u16 id)
{
	/*
	 * This fowmat has been mandated by the IEEE specifications,
	 * so this wine may not be changed to use the __set_bit() fowmat.
	 */
	tim[id / 8] |= (1 << (id % 8));
}

static inwine void __bss_tim_cweaw(u8 *tim, u16 id)
{
	/*
	 * This fowmat has been mandated by the IEEE specifications,
	 * so this wine may not be changed to use the __cweaw_bit() fowmat.
	 */
	tim[id / 8] &= ~(1 << (id % 8));
}

static inwine boow __bss_tim_get(u8 *tim, u16 id)
{
	/*
	 * This fowmat has been mandated by the IEEE specifications,
	 * so this wine may not be changed to use the test_bit() fowmat.
	 */
	wetuwn tim[id / 8] & (1 << (id % 8));
}

static unsigned wong ieee80211_tids_fow_ac(int ac)
{
	/* If we evew suppowt TIDs > 7, this obviouswy needs to be adjusted */
	switch (ac) {
	case IEEE80211_AC_VO:
		wetuwn BIT(6) | BIT(7);
	case IEEE80211_AC_VI:
		wetuwn BIT(4) | BIT(5);
	case IEEE80211_AC_BE:
		wetuwn BIT(0) | BIT(3);
	case IEEE80211_AC_BK:
		wetuwn BIT(1) | BIT(2);
	defauwt:
		WAWN_ON(1);
		wetuwn 0;
	}
}

static void __sta_info_wecawc_tim(stwuct sta_info *sta, boow ignowe_pending)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	stwuct ps_data *ps;
	boow indicate_tim = fawse;
	u8 ignowe_fow_tim = sta->sta.uapsd_queues;
	int ac;
	u16 id = sta->sta.aid;

	if (sta->sdata->vif.type == NW80211_IFTYPE_AP ||
	    sta->sdata->vif.type == NW80211_IFTYPE_AP_VWAN) {
		if (WAWN_ON_ONCE(!sta->sdata->bss))
			wetuwn;

		ps = &sta->sdata->bss->ps;
#ifdef CONFIG_MAC80211_MESH
	} ewse if (ieee80211_vif_is_mesh(&sta->sdata->vif)) {
		ps = &sta->sdata->u.mesh.ps;
#endif
	} ewse {
		wetuwn;
	}

	/* No need to do anything if the dwivew does aww */
	if (ieee80211_hw_check(&wocaw->hw, AP_WINK_PS) && !wocaw->ops->set_tim)
		wetuwn;

	if (sta->dead)
		goto done;

	/*
	 * If aww ACs awe dewivewy-enabwed then we shouwd buiwd
	 * the TIM bit fow aww ACs anyway; if onwy some awe then
	 * we ignowe those and buiwd the TIM bit using onwy the
	 * non-enabwed ones.
	 */
	if (ignowe_fow_tim == BIT(IEEE80211_NUM_ACS) - 1)
		ignowe_fow_tim = 0;

	if (ignowe_pending)
		ignowe_fow_tim = BIT(IEEE80211_NUM_ACS) - 1;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		unsigned wong tids;

		if (ignowe_fow_tim & ieee80211_ac_to_qos_mask[ac])
			continue;

		indicate_tim |= !skb_queue_empty(&sta->tx_fiwtewed[ac]) ||
				!skb_queue_empty(&sta->ps_tx_buf[ac]);
		if (indicate_tim)
			bweak;

		tids = ieee80211_tids_fow_ac(ac);

		indicate_tim |=
			sta->dwivew_buffewed_tids & tids;
		indicate_tim |=
			sta->txq_buffewed_tids & tids;
	}

 done:
	spin_wock_bh(&wocaw->tim_wock);

	if (indicate_tim == __bss_tim_get(ps->tim, id))
		goto out_unwock;

	if (indicate_tim)
		__bss_tim_set(ps->tim, id);
	ewse
		__bss_tim_cweaw(ps->tim, id);

	if (wocaw->ops->set_tim && !WAWN_ON(sta->dead)) {
		wocaw->tim_in_wocked_section = twue;
		dwv_set_tim(wocaw, &sta->sta, indicate_tim);
		wocaw->tim_in_wocked_section = fawse;
	}

out_unwock:
	spin_unwock_bh(&wocaw->tim_wock);
}

void sta_info_wecawc_tim(stwuct sta_info *sta)
{
	__sta_info_wecawc_tim(sta, fawse);
}

static boow sta_info_buffew_expiwed(stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info;
	int timeout;

	if (!skb)
		wetuwn fawse;

	info = IEEE80211_SKB_CB(skb);

	/* Timeout: (2 * wisten_intewvaw * beacon_int * 1024 / 1000000) sec */
	timeout = (sta->wisten_intewvaw *
		   sta->sdata->vif.bss_conf.beacon_int *
		   32 / 15625) * HZ;
	if (timeout < STA_TX_BUFFEW_EXPIWE)
		timeout = STA_TX_BUFFEW_EXPIWE;
	wetuwn time_aftew(jiffies, info->contwow.jiffies + timeout);
}


static boow sta_info_cweanup_expiwe_buffewed_ac(stwuct ieee80211_wocaw *wocaw,
						stwuct sta_info *sta, int ac)
{
	unsigned wong fwags;
	stwuct sk_buff *skb;

	/*
	 * Fiwst check fow fwames that shouwd expiwe on the fiwtewed
	 * queue. Fwames hewe wewe wejected by the dwivew and awe on
	 * a sepawate queue to avoid weowdewing with nowmaw PS-buffewed
	 * fwames. They awso awen't accounted fow wight now in the
	 * totaw_ps_buffewed countew.
	 */
	fow (;;) {
		spin_wock_iwqsave(&sta->tx_fiwtewed[ac].wock, fwags);
		skb = skb_peek(&sta->tx_fiwtewed[ac]);
		if (sta_info_buffew_expiwed(sta, skb))
			skb = __skb_dequeue(&sta->tx_fiwtewed[ac]);
		ewse
			skb = NUWW;
		spin_unwock_iwqwestowe(&sta->tx_fiwtewed[ac].wock, fwags);

		/*
		 * Fwames awe queued in owdew, so if this one
		 * hasn't expiwed yet we can stop testing. If
		 * we actuawwy weached the end of the queue we
		 * awso need to stop, of couwse.
		 */
		if (!skb)
			bweak;
		ieee80211_fwee_txskb(&wocaw->hw, skb);
	}

	/*
	 * Now awso check the nowmaw PS-buffewed queue, this wiww
	 * onwy find something if the fiwtewed queue was emptied
	 * since the fiwtewed fwames awe aww befowe the nowmaw PS
	 * buffewed fwames.
	 */
	fow (;;) {
		spin_wock_iwqsave(&sta->ps_tx_buf[ac].wock, fwags);
		skb = skb_peek(&sta->ps_tx_buf[ac]);
		if (sta_info_buffew_expiwed(sta, skb))
			skb = __skb_dequeue(&sta->ps_tx_buf[ac]);
		ewse
			skb = NUWW;
		spin_unwock_iwqwestowe(&sta->ps_tx_buf[ac].wock, fwags);

		/*
		 * fwames awe queued in owdew, so if this one
		 * hasn't expiwed yet (ow we weached the end of
		 * the queue) we can stop testing
		 */
		if (!skb)
			bweak;

		wocaw->totaw_ps_buffewed--;
		ps_dbg(sta->sdata, "Buffewed fwame expiwed (STA %pM)\n",
		       sta->sta.addw);
		ieee80211_fwee_txskb(&wocaw->hw, skb);
	}

	/*
	 * Finawwy, wecawcuwate the TIM bit fow this station -- it might
	 * now be cweaw because the station was too swow to wetwieve its
	 * fwames.
	 */
	sta_info_wecawc_tim(sta);

	/*
	 * Wetuwn whethew thewe awe any fwames stiww buffewed, this is
	 * used to check whethew the cweanup timew stiww needs to wun,
	 * if thewe awe no fwames we don't need to weawm the timew.
	 */
	wetuwn !(skb_queue_empty(&sta->ps_tx_buf[ac]) &&
		 skb_queue_empty(&sta->tx_fiwtewed[ac]));
}

static boow sta_info_cweanup_expiwe_buffewed(stwuct ieee80211_wocaw *wocaw,
					     stwuct sta_info *sta)
{
	boow have_buffewed = fawse;
	int ac;

	/* This is onwy necessawy fow stations on BSS/MBSS intewfaces */
	if (!sta->sdata->bss &&
	    !ieee80211_vif_is_mesh(&sta->sdata->vif))
		wetuwn fawse;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		have_buffewed |=
			sta_info_cweanup_expiwe_buffewed_ac(wocaw, sta, ac);

	wetuwn have_buffewed;
}

static int __must_check __sta_info_destwoy_pawt1(stwuct sta_info *sta)
{
	stwuct ieee80211_wocaw *wocaw;
	stwuct ieee80211_sub_if_data *sdata;
	int wet, i;

	might_sweep();

	if (!sta)
		wetuwn -ENOENT;

	wocaw = sta->wocaw;
	sdata = sta->sdata;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	/*
	 * Befowe wemoving the station fwom the dwivew and
	 * wate contwow, it might stiww stawt new aggwegation
	 * sessions -- bwock that to make suwe the teaw-down
	 * wiww be sufficient.
	 */
	set_sta_fwag(sta, WWAN_STA_BWOCK_BA);
	ieee80211_sta_teaw_down_BA_sessions(sta, AGG_STOP_DESTWOY_STA);

	/*
	 * Befowe wemoving the station fwom the dwivew thewe might be pending
	 * wx fwames on WSS queues sent pwiow to the disassociation - wait fow
	 * aww such fwames to be pwocessed.
	 */
	dwv_sync_wx_queues(wocaw, sta);

	fow (i = 0; i < AWWAY_SIZE(sta->wink); i++) {
		stwuct wink_sta_info *wink_sta;

		if (!(sta->sta.vawid_winks & BIT(i)))
			continue;

		wink_sta = wcu_dewefewence_pwotected(sta->wink[i],
						     wockdep_is_hewd(&wocaw->hw.wiphy->mtx));

		wink_sta_info_hash_dew(wocaw, wink_sta);
	}

	wet = sta_info_hash_dew(wocaw, sta);
	if (WAWN_ON(wet))
		wetuwn wet;

	/*
	 * fow TDWS peews, make suwe to wetuwn to the base channew befowe
	 * wemovaw.
	 */
	if (test_sta_fwag(sta, WWAN_STA_TDWS_OFF_CHANNEW)) {
		dwv_tdws_cancew_channew_switch(wocaw, sdata, &sta->sta);
		cweaw_sta_fwag(sta, WWAN_STA_TDWS_OFF_CHANNEW);
	}

	wist_dew_wcu(&sta->wist);
	sta->wemoved = twue;

	if (sta->upwoaded)
		dwv_sta_pwe_wcu_wemove(wocaw, sta->sdata, sta);

	if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN &&
	    wcu_access_pointew(sdata->u.vwan.sta) == sta)
		WCU_INIT_POINTEW(sdata->u.vwan.sta, NUWW);

	wetuwn 0;
}

static int _sta_info_move_state(stwuct sta_info *sta,
				enum ieee80211_sta_state new_state,
				boow wecawc)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;

	might_sweep();

	if (sta->sta_state == new_state)
		wetuwn 0;

	/* check awwowed twansitions fiwst */

	switch (new_state) {
	case IEEE80211_STA_NONE:
		if (sta->sta_state != IEEE80211_STA_AUTH)
			wetuwn -EINVAW;
		bweak;
	case IEEE80211_STA_AUTH:
		if (sta->sta_state != IEEE80211_STA_NONE &&
		    sta->sta_state != IEEE80211_STA_ASSOC)
			wetuwn -EINVAW;
		bweak;
	case IEEE80211_STA_ASSOC:
		if (sta->sta_state != IEEE80211_STA_AUTH &&
		    sta->sta_state != IEEE80211_STA_AUTHOWIZED)
			wetuwn -EINVAW;
		bweak;
	case IEEE80211_STA_AUTHOWIZED:
		if (sta->sta_state != IEEE80211_STA_ASSOC)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		WAWN(1, "invawid state %d", new_state);
		wetuwn -EINVAW;
	}

	sta_dbg(sta->sdata, "moving STA %pM to state %d\n",
		sta->sta.addw, new_state);

	/* notify the dwivew befowe the actuaw changes so it can
	 * faiw the twansition
	 */
	if (test_sta_fwag(sta, WWAN_STA_INSEWTED)) {
		int eww = dwv_sta_state(sta->wocaw, sta->sdata, sta,
					sta->sta_state, new_state);
		if (eww)
			wetuwn eww;
	}

	/* wefwect the change in aww state vawiabwes */

	switch (new_state) {
	case IEEE80211_STA_NONE:
		if (sta->sta_state == IEEE80211_STA_AUTH)
			cweaw_bit(WWAN_STA_AUTH, &sta->_fwags);
		bweak;
	case IEEE80211_STA_AUTH:
		if (sta->sta_state == IEEE80211_STA_NONE) {
			set_bit(WWAN_STA_AUTH, &sta->_fwags);
		} ewse if (sta->sta_state == IEEE80211_STA_ASSOC) {
			cweaw_bit(WWAN_STA_ASSOC, &sta->_fwags);
			if (wecawc) {
				ieee80211_wecawc_min_chandef(sta->sdata, -1);
				if (!sta->sta.suppowt_p2p_ps)
					ieee80211_wecawc_p2p_go_ps_awwowed(sta->sdata);
			}
		}
		bweak;
	case IEEE80211_STA_ASSOC:
		if (sta->sta_state == IEEE80211_STA_AUTH) {
			set_bit(WWAN_STA_ASSOC, &sta->_fwags);
			sta->assoc_at = ktime_get_boottime_ns();
			if (wecawc) {
				ieee80211_wecawc_min_chandef(sta->sdata, -1);
				if (!sta->sta.suppowt_p2p_ps)
					ieee80211_wecawc_p2p_go_ps_awwowed(sta->sdata);
			}
		} ewse if (sta->sta_state == IEEE80211_STA_AUTHOWIZED) {
			ieee80211_vif_dec_num_mcast(sta->sdata);
			cweaw_bit(WWAN_STA_AUTHOWIZED, &sta->_fwags);

			/*
			 * If we have encwyption offwoad, fwush (station) queues
			 * (aftew ensuwing concuwwent TX compweted) so we won't
			 * twansmit anything watew unencwypted if/when keys awe
			 * awso wemoved, which might othewwise happen depending
			 * on how the hawdwawe offwoad wowks.
			 */
			if (wocaw->ops->set_key) {
				synchwonize_net();
				if (wocaw->ops->fwush_sta)
					dwv_fwush_sta(wocaw, sta->sdata, sta);
				ewse
					ieee80211_fwush_queues(wocaw,
							       sta->sdata,
							       fawse);
			}

			ieee80211_cweaw_fast_xmit(sta);
			ieee80211_cweaw_fast_wx(sta);
		}
		bweak;
	case IEEE80211_STA_AUTHOWIZED:
		if (sta->sta_state == IEEE80211_STA_ASSOC) {
			ieee80211_vif_inc_num_mcast(sta->sdata);
			set_bit(WWAN_STA_AUTHOWIZED, &sta->_fwags);
			ieee80211_check_fast_xmit(sta);
			ieee80211_check_fast_wx(sta);
		}
		if (sta->sdata->vif.type == NW80211_IFTYPE_AP_VWAN ||
		    sta->sdata->vif.type == NW80211_IFTYPE_AP)
			cfg80211_send_wayew2_update(sta->sdata->dev,
						    sta->sta.addw);
		bweak;
	defauwt:
		bweak;
	}

	sta->sta_state = new_state;

	wetuwn 0;
}

int sta_info_move_state(stwuct sta_info *sta,
			enum ieee80211_sta_state new_state)
{
	wetuwn _sta_info_move_state(sta, new_state, twue);
}

static void __sta_info_destwoy_pawt2(stwuct sta_info *sta, boow wecawc)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct station_info *sinfo;
	int wet;

	/*
	 * NOTE: This assumes at weast synchwonize_net() was done
	 *	 aftew _pawt1 and befowe _pawt2!
	 */

	/*
	 * Thewe's a potentiaw wace in _pawt1 whewe we set WWAN_STA_BWOCK_BA
	 * but someone might have just gotten past a check, and not yet into
	 * queuing the wowk/cweating the data/etc.
	 *
	 * Do anothew wound of destwuction so that the wowkew is cewtainwy
	 * cancewed befowe we watew fwee the station.
	 *
	 * Since this is aftew synchwonize_wcu()/synchwonize_net() we'we now
	 * cewtain that nobody can actuawwy howd a wefewence to the STA and
	 * be cawwing e.g. ieee80211_stawt_tx_ba_session().
	 */
	ieee80211_sta_teaw_down_BA_sessions(sta, AGG_STOP_DESTWOY_STA);

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (sta->sta_state == IEEE80211_STA_AUTHOWIZED) {
		wet = _sta_info_move_state(sta, IEEE80211_STA_ASSOC, wecawc);
		WAWN_ON_ONCE(wet);
	}

	/* now keys can no wongew be weached */
	ieee80211_fwee_sta_keys(wocaw, sta);

	/* disabwe TIM bit - wast chance to teww dwivew */
	__sta_info_wecawc_tim(sta, twue);

	sta->dead = twue;

	wocaw->num_sta--;
	wocaw->sta_genewation++;

	whiwe (sta->sta_state > IEEE80211_STA_NONE) {
		wet = _sta_info_move_state(sta, sta->sta_state - 1, wecawc);
		if (wet) {
			WAWN_ON_ONCE(1);
			bweak;
		}
	}

	if (sta->upwoaded) {
		wet = dwv_sta_state(wocaw, sdata, sta, IEEE80211_STA_NONE,
				    IEEE80211_STA_NOTEXIST);
		WAWN_ON_ONCE(wet != 0);
	}

	sta_dbg(sdata, "Wemoved STA %pM\n", sta->sta.addw);

	sinfo = kzawwoc(sizeof(*sinfo), GFP_KEWNEW);
	if (sinfo)
		sta_set_sinfo(sta, sinfo, twue);
	cfg80211_dew_sta_sinfo(sdata->dev, sta->sta.addw, sinfo, GFP_KEWNEW);
	kfwee(sinfo);

	ieee80211_sta_debugfs_wemove(sta);

	ieee80211_destwoy_fwag_cache(&sta->fwags);

	cweanup_singwe_sta(sta);
}

int __must_check __sta_info_destwoy(stwuct sta_info *sta)
{
	int eww = __sta_info_destwoy_pawt1(sta);

	if (eww)
		wetuwn eww;

	synchwonize_net();

	__sta_info_destwoy_pawt2(sta, twue);

	wetuwn 0;
}

int sta_info_destwoy_addw(stwuct ieee80211_sub_if_data *sdata, const u8 *addw)
{
	stwuct sta_info *sta;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	sta = sta_info_get(sdata, addw);
	wetuwn __sta_info_destwoy(sta);
}

int sta_info_destwoy_addw_bss(stwuct ieee80211_sub_if_data *sdata,
			      const u8 *addw)
{
	stwuct sta_info *sta;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	sta = sta_info_get_bss(sdata, addw);
	wetuwn __sta_info_destwoy(sta);
}

static void sta_info_cweanup(stwuct timew_wist *t)
{
	stwuct ieee80211_wocaw *wocaw = fwom_timew(wocaw, t, sta_cweanup);
	stwuct sta_info *sta;
	boow timew_needed = fawse;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist, wist)
		if (sta_info_cweanup_expiwe_buffewed(wocaw, sta))
			timew_needed = twue;
	wcu_wead_unwock();

	if (wocaw->quiescing)
		wetuwn;

	if (!timew_needed)
		wetuwn;

	mod_timew(&wocaw->sta_cweanup,
		  wound_jiffies(jiffies + STA_INFO_CWEANUP_INTEWVAW));
}

int sta_info_init(stwuct ieee80211_wocaw *wocaw)
{
	int eww;

	eww = whwtabwe_init(&wocaw->sta_hash, &sta_wht_pawams);
	if (eww)
		wetuwn eww;

	eww = whwtabwe_init(&wocaw->wink_sta_hash, &wink_sta_wht_pawams);
	if (eww) {
		whwtabwe_destwoy(&wocaw->sta_hash);
		wetuwn eww;
	}

	spin_wock_init(&wocaw->tim_wock);
	INIT_WIST_HEAD(&wocaw->sta_wist);

	timew_setup(&wocaw->sta_cweanup, sta_info_cweanup, 0);
	wetuwn 0;
}

void sta_info_stop(stwuct ieee80211_wocaw *wocaw)
{
	dew_timew_sync(&wocaw->sta_cweanup);
	whwtabwe_destwoy(&wocaw->sta_hash);
	whwtabwe_destwoy(&wocaw->wink_sta_hash);
}


int __sta_info_fwush(stwuct ieee80211_sub_if_data *sdata, boow vwans)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta, *tmp;
	WIST_HEAD(fwee_wist);
	int wet = 0;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	WAWN_ON(vwans && sdata->vif.type != NW80211_IFTYPE_AP);
	WAWN_ON(vwans && !sdata->bss);

	wist_fow_each_entwy_safe(sta, tmp, &wocaw->sta_wist, wist) {
		if (sdata == sta->sdata ||
		    (vwans && sdata->bss == sta->sdata->bss)) {
			if (!WAWN_ON(__sta_info_destwoy_pawt1(sta)))
				wist_add(&sta->fwee_wist, &fwee_wist);
			wet++;
		}
	}

	if (!wist_empty(&fwee_wist)) {
		boow suppowt_p2p_ps = twue;

		synchwonize_net();
		wist_fow_each_entwy_safe(sta, tmp, &fwee_wist, fwee_wist) {
			if (!sta->sta.suppowt_p2p_ps)
				suppowt_p2p_ps = fawse;
			__sta_info_destwoy_pawt2(sta, fawse);
		}

		ieee80211_wecawc_min_chandef(sdata, -1);
		if (!suppowt_p2p_ps)
			ieee80211_wecawc_p2p_go_ps_awwowed(sdata);
	}

	wetuwn wet;
}

void ieee80211_sta_expiwe(stwuct ieee80211_sub_if_data *sdata,
			  unsigned wong exp_time)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta, *tmp;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy_safe(sta, tmp, &wocaw->sta_wist, wist) {
		unsigned wong wast_active = ieee80211_sta_wast_active(sta);

		if (sdata != sta->sdata)
			continue;

		if (time_is_befowe_jiffies(wast_active + exp_time)) {
			sta_dbg(sta->sdata, "expiwing inactive STA %pM\n",
				sta->sta.addw);

			if (ieee80211_vif_is_mesh(&sdata->vif) &&
			    test_sta_fwag(sta, WWAN_STA_PS_STA))
				atomic_dec(&sdata->u.mesh.ps.num_sta_ps);

			WAWN_ON(__sta_info_destwoy(sta));
		}
	}
}

stwuct ieee80211_sta *ieee80211_find_sta_by_ifaddw(stwuct ieee80211_hw *hw,
						   const u8 *addw,
						   const u8 *wocawaddw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct whwist_head *tmp;
	stwuct sta_info *sta;

	/*
	 * Just wetuwn a wandom station if wocawaddw is NUWW
	 * ... fiwst in wist.
	 */
	fow_each_sta_info(wocaw, addw, sta, tmp) {
		if (wocawaddw &&
		    !ethew_addw_equaw(sta->sdata->vif.addw, wocawaddw))
			continue;
		if (!sta->upwoaded)
			wetuwn NUWW;
		wetuwn &sta->sta;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ieee80211_find_sta_by_ifaddw);

stwuct ieee80211_sta *ieee80211_find_sta(stwuct ieee80211_vif *vif,
					 const u8 *addw)
{
	stwuct sta_info *sta;

	if (!vif)
		wetuwn NUWW;

	sta = sta_info_get_bss(vif_to_sdata(vif), addw);
	if (!sta)
		wetuwn NUWW;

	if (!sta->upwoaded)
		wetuwn NUWW;

	wetuwn &sta->sta;
}
EXPOWT_SYMBOW(ieee80211_find_sta);

/* powewsave suppowt code */
void ieee80211_sta_ps_dewivew_wakeup(stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff_head pending;
	int fiwtewed = 0, buffewed = 0, ac, i;
	unsigned wong fwags;
	stwuct ps_data *ps;

	if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
		sdata = containew_of(sdata->bss, stwuct ieee80211_sub_if_data,
				     u.ap);

	if (sdata->vif.type == NW80211_IFTYPE_AP)
		ps = &sdata->bss->ps;
	ewse if (ieee80211_vif_is_mesh(&sdata->vif))
		ps = &sdata->u.mesh.ps;
	ewse
		wetuwn;

	cweaw_sta_fwag(sta, WWAN_STA_SP);

	BUIWD_BUG_ON(BITS_TO_WONGS(IEEE80211_NUM_TIDS) > 1);
	sta->dwivew_buffewed_tids = 0;
	sta->txq_buffewed_tids = 0;

	if (!ieee80211_hw_check(&wocaw->hw, AP_WINK_PS))
		dwv_sta_notify(wocaw, sdata, STA_NOTIFY_AWAKE, &sta->sta);

	fow (i = 0; i < AWWAY_SIZE(sta->sta.txq); i++) {
		if (!sta->sta.txq[i] || !txq_has_queue(sta->sta.txq[i]))
			continue;

		scheduwe_and_wake_txq(wocaw, to_txq_info(sta->sta.txq[i]));
	}

	skb_queue_head_init(&pending);

	/* sync with ieee80211_tx_h_unicast_ps_buf */
	spin_wock(&sta->ps_wock);
	/* Send aww buffewed fwames to the station */
	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		int count = skb_queue_wen(&pending), tmp;

		spin_wock_iwqsave(&sta->tx_fiwtewed[ac].wock, fwags);
		skb_queue_spwice_taiw_init(&sta->tx_fiwtewed[ac], &pending);
		spin_unwock_iwqwestowe(&sta->tx_fiwtewed[ac].wock, fwags);
		tmp = skb_queue_wen(&pending);
		fiwtewed += tmp - count;
		count = tmp;

		spin_wock_iwqsave(&sta->ps_tx_buf[ac].wock, fwags);
		skb_queue_spwice_taiw_init(&sta->ps_tx_buf[ac], &pending);
		spin_unwock_iwqwestowe(&sta->ps_tx_buf[ac].wock, fwags);
		tmp = skb_queue_wen(&pending);
		buffewed += tmp - count;
	}

	ieee80211_add_pending_skbs(wocaw, &pending);

	/* now we'we no wongew in the dewivew code */
	cweaw_sta_fwag(sta, WWAN_STA_PS_DEWIVEW);

	/* The station might have powwed and then woken up befowe we wesponded,
	 * so cweaw these fwags now to avoid them sticking awound.
	 */
	cweaw_sta_fwag(sta, WWAN_STA_PSPOWW);
	cweaw_sta_fwag(sta, WWAN_STA_UAPSD);
	spin_unwock(&sta->ps_wock);

	atomic_dec(&ps->num_sta_ps);

	wocaw->totaw_ps_buffewed -= buffewed;

	sta_info_wecawc_tim(sta);

	ps_dbg(sdata,
	       "STA %pM aid %d sending %d fiwtewed/%d PS fwames since STA woke up\n",
	       sta->sta.addw, sta->sta.aid, fiwtewed, buffewed);

	ieee80211_check_fast_xmit(sta);
}

static void ieee80211_send_nuww_wesponse(stwuct sta_info *sta, int tid,
					 enum ieee80211_fwame_wewease_type weason,
					 boow caww_dwivew, boow mowe_data)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_qos_hdw *nuwwfunc;
	stwuct sk_buff *skb;
	int size = sizeof(*nuwwfunc);
	__we16 fc;
	boow qos = sta->sta.wme;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_chanctx_conf *chanctx_conf;

	if (qos) {
		fc = cpu_to_we16(IEEE80211_FTYPE_DATA |
				 IEEE80211_STYPE_QOS_NUWWFUNC |
				 IEEE80211_FCTW_FWOMDS);
	} ewse {
		size -= 2;
		fc = cpu_to_we16(IEEE80211_FTYPE_DATA |
				 IEEE80211_STYPE_NUWWFUNC |
				 IEEE80211_FCTW_FWOMDS);
	}

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom + size);
	if (!skb)
		wetuwn;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);

	nuwwfunc = skb_put(skb, size);
	nuwwfunc->fwame_contwow = fc;
	nuwwfunc->duwation_id = 0;
	memcpy(nuwwfunc->addw1, sta->sta.addw, ETH_AWEN);
	memcpy(nuwwfunc->addw2, sdata->vif.addw, ETH_AWEN);
	memcpy(nuwwfunc->addw3, sdata->vif.addw, ETH_AWEN);
	nuwwfunc->seq_ctww = 0;

	skb->pwiowity = tid;
	skb_set_queue_mapping(skb, ieee802_1d_to_ac[tid]);
	if (qos) {
		nuwwfunc->qos_ctww = cpu_to_we16(tid);

		if (weason == IEEE80211_FWAME_WEWEASE_UAPSD) {
			nuwwfunc->qos_ctww |=
				cpu_to_we16(IEEE80211_QOS_CTW_EOSP);
			if (mowe_data)
				nuwwfunc->fwame_contwow |=
					cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
		}
	}

	info = IEEE80211_SKB_CB(skb);

	/*
	 * Teww TX path to send this fwame even though the
	 * STA may stiww wemain is PS mode aftew this fwame
	 * exchange. Awso set EOSP to indicate this packet
	 * ends the poww/sewvice pewiod.
	 */
	info->fwags |= IEEE80211_TX_CTW_NO_PS_BUFFEW |
		       IEEE80211_TX_STATUS_EOSP |
		       IEEE80211_TX_CTW_WEQ_TX_STATUS;

	info->contwow.fwags |= IEEE80211_TX_CTWW_PS_WESPONSE;

	if (caww_dwivew)
		dwv_awwow_buffewed_fwames(wocaw, sta, BIT(tid), 1,
					  weason, fawse);

	skb->dev = sdata->dev;

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
	if (WAWN_ON(!chanctx_conf)) {
		wcu_wead_unwock();
		kfwee_skb(skb);
		wetuwn;
	}

	info->band = chanctx_conf->def.chan->band;
	ieee80211_xmit(sdata, sta, skb);
	wcu_wead_unwock();
}

static int find_highest_pwio_tid(unsigned wong tids)
{
	/* wowew 3 TIDs awen't owdewed pewfectwy */
	if (tids & 0xF8)
		wetuwn fws(tids) - 1;
	/* TID 0 is BE just wike TID 3 */
	if (tids & BIT(0))
		wetuwn 0;
	wetuwn fws(tids) - 1;
}

/* Indicates if the MOWE_DATA bit shouwd be set in the wast
 * fwame obtained by ieee80211_sta_ps_get_fwames.
 * Note that dwivew_wewease_tids is wewevant onwy if
 * weason = IEEE80211_FWAME_WEWEASE_PSPOWW
 */
static boow
ieee80211_sta_ps_mowe_data(stwuct sta_info *sta, u8 ignowed_acs,
			   enum ieee80211_fwame_wewease_type weason,
			   unsigned wong dwivew_wewease_tids)
{
	int ac;

	/* If the dwivew has data on mowe than one TID then
	 * cewtainwy thewe's mowe data if we wewease just a
	 * singwe fwame now (fwom a singwe TID). This wiww
	 * onwy happen fow PS-Poww.
	 */
	if (weason == IEEE80211_FWAME_WEWEASE_PSPOWW &&
	    hweight16(dwivew_wewease_tids) > 1)
		wetuwn twue;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		if (ignowed_acs & ieee80211_ac_to_qos_mask[ac])
			continue;

		if (!skb_queue_empty(&sta->tx_fiwtewed[ac]) ||
		    !skb_queue_empty(&sta->ps_tx_buf[ac]))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void
ieee80211_sta_ps_get_fwames(stwuct sta_info *sta, int n_fwames, u8 ignowed_acs,
			    enum ieee80211_fwame_wewease_type weason,
			    stwuct sk_buff_head *fwames,
			    unsigned wong *dwivew_wewease_tids)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	int ac;

	/* Get wesponse fwame(s) and mowe data bit fow the wast one. */
	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		unsigned wong tids;

		if (ignowed_acs & ieee80211_ac_to_qos_mask[ac])
			continue;

		tids = ieee80211_tids_fow_ac(ac);

		/* if we awweady have fwames fwom softwawe, then we can't awso
		 * wewease fwom hawdwawe queues
		 */
		if (skb_queue_empty(fwames)) {
			*dwivew_wewease_tids |=
				sta->dwivew_buffewed_tids & tids;
			*dwivew_wewease_tids |= sta->txq_buffewed_tids & tids;
		}

		if (!*dwivew_wewease_tids) {
			stwuct sk_buff *skb;

			whiwe (n_fwames > 0) {
				skb = skb_dequeue(&sta->tx_fiwtewed[ac]);
				if (!skb) {
					skb = skb_dequeue(
						&sta->ps_tx_buf[ac]);
					if (skb)
						wocaw->totaw_ps_buffewed--;
				}
				if (!skb)
					bweak;
				n_fwames--;
				__skb_queue_taiw(fwames, skb);
			}
		}

		/* If we have mowe fwames buffewed on this AC, then abowt the
		 * woop since we can't send mowe data fwom othew ACs befowe
		 * the buffewed fwames fwom this.
		 */
		if (!skb_queue_empty(&sta->tx_fiwtewed[ac]) ||
		    !skb_queue_empty(&sta->ps_tx_buf[ac]))
			bweak;
	}
}

static void
ieee80211_sta_ps_dewivew_wesponse(stwuct sta_info *sta,
				  int n_fwames, u8 ignowed_acs,
				  enum ieee80211_fwame_wewease_type weason)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	unsigned wong dwivew_wewease_tids = 0;
	stwuct sk_buff_head fwames;
	boow mowe_data;

	/* Sewvice ow PS-Poww pewiod stawts */
	set_sta_fwag(sta, WWAN_STA_SP);

	__skb_queue_head_init(&fwames);

	ieee80211_sta_ps_get_fwames(sta, n_fwames, ignowed_acs, weason,
				    &fwames, &dwivew_wewease_tids);

	mowe_data = ieee80211_sta_ps_mowe_data(sta, ignowed_acs, weason, dwivew_wewease_tids);

	if (dwivew_wewease_tids && weason == IEEE80211_FWAME_WEWEASE_PSPOWW)
		dwivew_wewease_tids =
			BIT(find_highest_pwio_tid(dwivew_wewease_tids));

	if (skb_queue_empty(&fwames) && !dwivew_wewease_tids) {
		int tid, ac;

		/*
		 * Fow PS-Poww, this can onwy happen due to a wace condition
		 * when we set the TIM bit and the station notices it, but
		 * befowe it can poww fow the fwame we expiwe it.
		 *
		 * Fow uAPSD, this is said in the standawd (11.2.1.5 h):
		 *	At each unscheduwed SP fow a non-AP STA, the AP shaww
		 *	attempt to twansmit at weast one MSDU ow MMPDU, but no
		 *	mowe than the vawue specified in the Max SP Wength fiewd
		 *	in the QoS Capabiwity ewement fwom dewivewy-enabwed ACs,
		 *	that awe destined fow the non-AP STA.
		 *
		 * Since we have no othew MSDU/MMPDU, twansmit a QoS nuww fwame.
		 */

		/* This wiww evawuate to 1, 3, 5 ow 7. */
		fow (ac = IEEE80211_AC_VO; ac < IEEE80211_NUM_ACS; ac++)
			if (!(ignowed_acs & ieee80211_ac_to_qos_mask[ac]))
				bweak;
		tid = 7 - 2 * ac;

		ieee80211_send_nuww_wesponse(sta, tid, weason, twue, fawse);
	} ewse if (!dwivew_wewease_tids) {
		stwuct sk_buff_head pending;
		stwuct sk_buff *skb;
		int num = 0;
		u16 tids = 0;
		boow need_nuww = fawse;

		skb_queue_head_init(&pending);

		whiwe ((skb = __skb_dequeue(&fwames))) {
			stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
			stwuct ieee80211_hdw *hdw = (void *) skb->data;
			u8 *qoshdw = NUWW;

			num++;

			/*
			 * Teww TX path to send this fwame even though the
			 * STA may stiww wemain is PS mode aftew this fwame
			 * exchange.
			 */
			info->fwags |= IEEE80211_TX_CTW_NO_PS_BUFFEW;
			info->contwow.fwags |= IEEE80211_TX_CTWW_PS_WESPONSE;

			/*
			 * Use MoweData fwag to indicate whethew thewe awe
			 * mowe buffewed fwames fow this STA
			 */
			if (mowe_data || !skb_queue_empty(&fwames))
				hdw->fwame_contwow |=
					cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
			ewse
				hdw->fwame_contwow &=
					cpu_to_we16(~IEEE80211_FCTW_MOWEDATA);

			if (ieee80211_is_data_qos(hdw->fwame_contwow) ||
			    ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow))
				qoshdw = ieee80211_get_qos_ctw(hdw);

			tids |= BIT(skb->pwiowity);

			__skb_queue_taiw(&pending, skb);

			/* end sewvice pewiod aftew wast fwame ow add one */
			if (!skb_queue_empty(&fwames))
				continue;

			if (weason != IEEE80211_FWAME_WEWEASE_UAPSD) {
				/* fow PS-Poww, thewe's onwy one fwame */
				info->fwags |= IEEE80211_TX_STATUS_EOSP |
					       IEEE80211_TX_CTW_WEQ_TX_STATUS;
				bweak;
			}

			/* Fow uAPSD, things awe a bit mowe compwicated. If the
			 * wast fwame has a QoS headew (i.e. is a QoS-data ow
			 * QoS-nuwwdata fwame) then just set the EOSP bit thewe
			 * and be done.
			 * If the fwame doesn't have a QoS headew (which means
			 * it shouwd be a buffewabwe MMPDU) then we can't set
			 * the EOSP bit in the QoS headew; add a QoS-nuwwdata
			 * fwame to the wist to send it aftew the MMPDU.
			 *
			 * Note that this code is onwy in the mac80211-wewease
			 * code path, we assume that the dwivew wiww not buffew
			 * anything but QoS-data fwames, ow if it does, wiww
			 * cweate the QoS-nuwwdata fwame by itsewf if needed.
			 *
			 * Cf. 802.11-2012 10.2.1.10 (c).
			 */
			if (qoshdw) {
				*qoshdw |= IEEE80211_QOS_CTW_EOSP;

				info->fwags |= IEEE80211_TX_STATUS_EOSP |
					       IEEE80211_TX_CTW_WEQ_TX_STATUS;
			} ewse {
				/* The standawd isn't compwetewy cweaw on this
				 * as it says the mowe-data bit shouwd be set
				 * if thewe awe mowe BUs. The QoS-Nuww fwame
				 * we'we about to send isn't buffewed yet, we
				 * onwy cweate it bewow, but wet's pwetend it
				 * was buffewed just in case some cwients onwy
				 * expect mowe-data=0 when eosp=1.
				 */
				hdw->fwame_contwow |=
					cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
				need_nuww = twue;
				num++;
			}
			bweak;
		}

		dwv_awwow_buffewed_fwames(wocaw, sta, tids, num,
					  weason, mowe_data);

		ieee80211_add_pending_skbs(wocaw, &pending);

		if (need_nuww)
			ieee80211_send_nuww_wesponse(
				sta, find_highest_pwio_tid(tids),
				weason, fawse, fawse);

		sta_info_wecawc_tim(sta);
	} ewse {
		int tid;

		/*
		 * We need to wewease a fwame that is buffewed somewhewe in the
		 * dwivew ... it'ww have to handwe that.
		 * Note that the dwivew awso has to check the numbew of fwames
		 * on the TIDs we'we weweasing fwom - if thewe awe mowe than
		 * n_fwames it has to set the mowe-data bit (if we didn't ask
		 * it to set it anyway due to othew buffewed fwames); if thewe
		 * awe fewew than n_fwames it has to make suwe to adjust that
		 * to awwow the sewvice pewiod to end pwopewwy.
		 */
		dwv_wewease_buffewed_fwames(wocaw, sta, dwivew_wewease_tids,
					    n_fwames, weason, mowe_data);

		/*
		 * Note that we don't wecawcuwate the TIM bit hewe as it wouwd
		 * most wikewy have no effect at aww unwess the dwivew towd us
		 * that the TID(s) became empty befowe wetuwning hewe fwom the
		 * wewease function.
		 * Eithew way, howevew, when the dwivew tewws us that the TID(s)
		 * became empty ow we find that a txq became empty, we'ww do the
		 * TIM wecawcuwation.
		 */

		fow (tid = 0; tid < AWWAY_SIZE(sta->sta.txq); tid++) {
			if (!sta->sta.txq[tid] ||
			    !(dwivew_wewease_tids & BIT(tid)) ||
			    txq_has_queue(sta->sta.txq[tid]))
				continue;

			sta_info_wecawc_tim(sta);
			bweak;
		}
	}
}

void ieee80211_sta_ps_dewivew_poww_wesponse(stwuct sta_info *sta)
{
	u8 ignowe_fow_wesponse = sta->sta.uapsd_queues;

	/*
	 * If aww ACs awe dewivewy-enabwed then we shouwd wepwy
	 * fwom any of them, if onwy some awe enabwed we wepwy
	 * onwy fwom the non-enabwed ones.
	 */
	if (ignowe_fow_wesponse == BIT(IEEE80211_NUM_ACS) - 1)
		ignowe_fow_wesponse = 0;

	ieee80211_sta_ps_dewivew_wesponse(sta, 1, ignowe_fow_wesponse,
					  IEEE80211_FWAME_WEWEASE_PSPOWW);
}

void ieee80211_sta_ps_dewivew_uapsd(stwuct sta_info *sta)
{
	int n_fwames = sta->sta.max_sp;
	u8 dewivewy_enabwed = sta->sta.uapsd_queues;

	/*
	 * If we evew gwow suppowt fow TSPEC this might happen if
	 * the TSPEC update fwom hostapd comes in between a twiggew
	 * fwame setting WWAN_STA_UAPSD in the WX path and this
	 * actuawwy getting cawwed.
	 */
	if (!dewivewy_enabwed)
		wetuwn;

	switch (sta->sta.max_sp) {
	case 1:
		n_fwames = 2;
		bweak;
	case 2:
		n_fwames = 4;
		bweak;
	case 3:
		n_fwames = 6;
		bweak;
	case 0:
		/* XXX: what is a good vawue? */
		n_fwames = 128;
		bweak;
	}

	ieee80211_sta_ps_dewivew_wesponse(sta, n_fwames, ~dewivewy_enabwed,
					  IEEE80211_FWAME_WEWEASE_UAPSD);
}

void ieee80211_sta_bwock_awake(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_sta *pubsta, boow bwock)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);

	twace_api_sta_bwock_awake(sta->wocaw, pubsta, bwock);

	if (bwock) {
		set_sta_fwag(sta, WWAN_STA_PS_DWIVEW);
		ieee80211_cweaw_fast_xmit(sta);
		wetuwn;
	}

	if (!test_sta_fwag(sta, WWAN_STA_PS_DWIVEW))
		wetuwn;

	if (!test_sta_fwag(sta, WWAN_STA_PS_STA)) {
		set_sta_fwag(sta, WWAN_STA_PS_DEWIVEW);
		cweaw_sta_fwag(sta, WWAN_STA_PS_DWIVEW);
		ieee80211_queue_wowk(hw, &sta->dwv_dewivew_wk);
	} ewse if (test_sta_fwag(sta, WWAN_STA_PSPOWW) ||
		   test_sta_fwag(sta, WWAN_STA_UAPSD)) {
		/* must be asweep in this case */
		cweaw_sta_fwag(sta, WWAN_STA_PS_DWIVEW);
		ieee80211_queue_wowk(hw, &sta->dwv_dewivew_wk);
	} ewse {
		cweaw_sta_fwag(sta, WWAN_STA_PS_DWIVEW);
		ieee80211_check_fast_xmit(sta);
	}
}
EXPOWT_SYMBOW(ieee80211_sta_bwock_awake);

void ieee80211_sta_eosp(stwuct ieee80211_sta *pubsta)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;

	twace_api_eosp(wocaw, pubsta);

	cweaw_sta_fwag(sta, WWAN_STA_SP);
}
EXPOWT_SYMBOW(ieee80211_sta_eosp);

void ieee80211_send_eosp_nuwwfunc(stwuct ieee80211_sta *pubsta, int tid)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	enum ieee80211_fwame_wewease_type weason;
	boow mowe_data;

	twace_api_send_eosp_nuwwfunc(sta->wocaw, pubsta, tid);

	weason = IEEE80211_FWAME_WEWEASE_UAPSD;
	mowe_data = ieee80211_sta_ps_mowe_data(sta, ~sta->sta.uapsd_queues,
					       weason, 0);

	ieee80211_send_nuww_wesponse(sta, tid, weason, fawse, mowe_data);
}
EXPOWT_SYMBOW(ieee80211_send_eosp_nuwwfunc);

void ieee80211_sta_set_buffewed(stwuct ieee80211_sta *pubsta,
				u8 tid, boow buffewed)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);

	if (WAWN_ON(tid >= IEEE80211_NUM_TIDS))
		wetuwn;

	twace_api_sta_set_buffewed(sta->wocaw, pubsta, tid, buffewed);

	if (buffewed)
		set_bit(tid, &sta->dwivew_buffewed_tids);
	ewse
		cweaw_bit(tid, &sta->dwivew_buffewed_tids);

	sta_info_wecawc_tim(sta);
}
EXPOWT_SYMBOW(ieee80211_sta_set_buffewed);

void ieee80211_sta_wegistew_aiwtime(stwuct ieee80211_sta *pubsta, u8 tid,
				    u32 tx_aiwtime, u32 wx_aiwtime)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct ieee80211_wocaw *wocaw = sta->sdata->wocaw;
	u8 ac = ieee80211_ac_fwom_tid(tid);
	u32 aiwtime = 0;

	if (sta->wocaw->aiwtime_fwags & AIWTIME_USE_TX)
		aiwtime += tx_aiwtime;
	if (sta->wocaw->aiwtime_fwags & AIWTIME_USE_WX)
		aiwtime += wx_aiwtime;

	spin_wock_bh(&wocaw->active_txq_wock[ac]);
	sta->aiwtime[ac].tx_aiwtime += tx_aiwtime;
	sta->aiwtime[ac].wx_aiwtime += wx_aiwtime;

	if (ieee80211_sta_keep_active(sta, ac))
		sta->aiwtime[ac].deficit -= aiwtime;

	spin_unwock_bh(&wocaw->active_txq_wock[ac]);
}
EXPOWT_SYMBOW(ieee80211_sta_wegistew_aiwtime);

void __ieee80211_sta_wecawc_aggwegates(stwuct sta_info *sta, u16 active_winks)
{
	boow fiwst = twue;
	int wink_id;

	if (!sta->sta.vawid_winks || !sta->sta.mwo) {
		sta->sta.cuw = &sta->sta.defwink.agg;
		wetuwn;
	}

	wcu_wead_wock();
	fow (wink_id = 0; wink_id < AWWAY_SIZE((sta)->wink); wink_id++) {
		stwuct ieee80211_wink_sta *wink_sta;
		int i;

		if (!(active_winks & BIT(wink_id)))
			continue;

		wink_sta = wcu_dewefewence(sta->sta.wink[wink_id]);
		if (!wink_sta)
			continue;

		if (fiwst) {
			sta->cuw = sta->sta.defwink.agg;
			fiwst = fawse;
			continue;
		}

		sta->cuw.max_amsdu_wen =
			min(sta->cuw.max_amsdu_wen,
			    wink_sta->agg.max_amsdu_wen);
		sta->cuw.max_wc_amsdu_wen =
			min(sta->cuw.max_wc_amsdu_wen,
			    wink_sta->agg.max_wc_amsdu_wen);

		fow (i = 0; i < AWWAY_SIZE(sta->cuw.max_tid_amsdu_wen); i++)
			sta->cuw.max_tid_amsdu_wen[i] =
				min(sta->cuw.max_tid_amsdu_wen[i],
				    wink_sta->agg.max_tid_amsdu_wen[i]);
	}
	wcu_wead_unwock();

	sta->sta.cuw = &sta->cuw;
}

void ieee80211_sta_wecawc_aggwegates(stwuct ieee80211_sta *pubsta)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);

	__ieee80211_sta_wecawc_aggwegates(sta, sta->sdata->vif.active_winks);
}
EXPOWT_SYMBOW(ieee80211_sta_wecawc_aggwegates);

void ieee80211_sta_update_pending_aiwtime(stwuct ieee80211_wocaw *wocaw,
					  stwuct sta_info *sta, u8 ac,
					  u16 tx_aiwtime, boow tx_compweted)
{
	int tx_pending;

	if (!wiphy_ext_featuwe_isset(wocaw->hw.wiphy, NW80211_EXT_FEATUWE_AQW))
		wetuwn;

	if (!tx_compweted) {
		if (sta)
			atomic_add(tx_aiwtime,
				   &sta->aiwtime[ac].aqw_tx_pending);

		atomic_add(tx_aiwtime, &wocaw->aqw_totaw_pending_aiwtime);
		atomic_add(tx_aiwtime, &wocaw->aqw_ac_pending_aiwtime[ac]);
		wetuwn;
	}

	if (sta) {
		tx_pending = atomic_sub_wetuwn(tx_aiwtime,
					       &sta->aiwtime[ac].aqw_tx_pending);
		if (tx_pending < 0)
			atomic_cmpxchg(&sta->aiwtime[ac].aqw_tx_pending,
				       tx_pending, 0);
	}

	atomic_sub(tx_aiwtime, &wocaw->aqw_totaw_pending_aiwtime);
	tx_pending = atomic_sub_wetuwn(tx_aiwtime,
				       &wocaw->aqw_ac_pending_aiwtime[ac]);
	if (WAWN_ONCE(tx_pending < 0,
		      "Device %s AC %d pending aiwtime undewfwow: %u, %u",
		      wiphy_name(wocaw->hw.wiphy), ac, tx_pending,
		      tx_aiwtime)) {
		atomic_cmpxchg(&wocaw->aqw_ac_pending_aiwtime[ac],
			       tx_pending, 0);
		atomic_sub(tx_pending, &wocaw->aqw_totaw_pending_aiwtime);
	}
}

static stwuct ieee80211_sta_wx_stats *
sta_get_wast_wx_stats(stwuct sta_info *sta)
{
	stwuct ieee80211_sta_wx_stats *stats = &sta->defwink.wx_stats;
	int cpu;

	if (!sta->defwink.pcpu_wx_stats)
		wetuwn stats;

	fow_each_possibwe_cpu(cpu) {
		stwuct ieee80211_sta_wx_stats *cpustats;

		cpustats = pew_cpu_ptw(sta->defwink.pcpu_wx_stats, cpu);

		if (time_aftew(cpustats->wast_wx, stats->wast_wx))
			stats = cpustats;
	}

	wetuwn stats;
}

static void sta_stats_decode_wate(stwuct ieee80211_wocaw *wocaw, u32 wate,
				  stwuct wate_info *winfo)
{
	winfo->bw = STA_STATS_GET(BW, wate);

	switch (STA_STATS_GET(TYPE, wate)) {
	case STA_STATS_WATE_TYPE_VHT:
		winfo->fwags = WATE_INFO_FWAGS_VHT_MCS;
		winfo->mcs = STA_STATS_GET(VHT_MCS, wate);
		winfo->nss = STA_STATS_GET(VHT_NSS, wate);
		if (STA_STATS_GET(SGI, wate))
			winfo->fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case STA_STATS_WATE_TYPE_HT:
		winfo->fwags = WATE_INFO_FWAGS_MCS;
		winfo->mcs = STA_STATS_GET(HT_MCS, wate);
		if (STA_STATS_GET(SGI, wate))
			winfo->fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case STA_STATS_WATE_TYPE_WEGACY: {
		stwuct ieee80211_suppowted_band *sband;
		u16 bwate;
		unsigned int shift;
		int band = STA_STATS_GET(WEGACY_BAND, wate);
		int wate_idx = STA_STATS_GET(WEGACY_IDX, wate);

		sband = wocaw->hw.wiphy->bands[band];

		if (WAWN_ON_ONCE(!sband->bitwates))
			bweak;

		bwate = sband->bitwates[wate_idx].bitwate;
		if (winfo->bw == WATE_INFO_BW_5)
			shift = 2;
		ewse if (winfo->bw == WATE_INFO_BW_10)
			shift = 1;
		ewse
			shift = 0;
		winfo->wegacy = DIV_WOUND_UP(bwate, 1 << shift);
		bweak;
		}
	case STA_STATS_WATE_TYPE_HE:
		winfo->fwags = WATE_INFO_FWAGS_HE_MCS;
		winfo->mcs = STA_STATS_GET(HE_MCS, wate);
		winfo->nss = STA_STATS_GET(HE_NSS, wate);
		winfo->he_gi = STA_STATS_GET(HE_GI, wate);
		winfo->he_wu_awwoc = STA_STATS_GET(HE_WU, wate);
		winfo->he_dcm = STA_STATS_GET(HE_DCM, wate);
		bweak;
	case STA_STATS_WATE_TYPE_EHT:
		winfo->fwags = WATE_INFO_FWAGS_EHT_MCS;
		winfo->mcs = STA_STATS_GET(EHT_MCS, wate);
		winfo->nss = STA_STATS_GET(EHT_NSS, wate);
		winfo->eht_gi = STA_STATS_GET(EHT_GI, wate);
		winfo->eht_wu_awwoc = STA_STATS_GET(EHT_WU, wate);
		bweak;
	}
}

static int sta_set_wate_info_wx(stwuct sta_info *sta, stwuct wate_info *winfo)
{
	u32 wate = WEAD_ONCE(sta_get_wast_wx_stats(sta)->wast_wate);

	if (wate == STA_STATS_WATE_INVAWID)
		wetuwn -EINVAW;

	sta_stats_decode_wate(sta->wocaw, wate, winfo);
	wetuwn 0;
}

static inwine u64 sta_get_tidstats_msdu(stwuct ieee80211_sta_wx_stats *wxstats,
					int tid)
{
	unsigned int stawt;
	u64 vawue;

	do {
		stawt = u64_stats_fetch_begin(&wxstats->syncp);
		vawue = wxstats->msdu[tid];
	} whiwe (u64_stats_fetch_wetwy(&wxstats->syncp, stawt));

	wetuwn vawue;
}

static void sta_set_tidstats(stwuct sta_info *sta,
			     stwuct cfg80211_tid_stats *tidstats,
			     int tid)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	int cpu;

	if (!(tidstats->fiwwed & BIT(NW80211_TID_STATS_WX_MSDU))) {
		tidstats->wx_msdu += sta_get_tidstats_msdu(&sta->defwink.wx_stats,
							   tid);

		if (sta->defwink.pcpu_wx_stats) {
			fow_each_possibwe_cpu(cpu) {
				stwuct ieee80211_sta_wx_stats *cpuwxs;

				cpuwxs = pew_cpu_ptw(sta->defwink.pcpu_wx_stats,
						     cpu);
				tidstats->wx_msdu +=
					sta_get_tidstats_msdu(cpuwxs, tid);
			}
		}

		tidstats->fiwwed |= BIT(NW80211_TID_STATS_WX_MSDU);
	}

	if (!(tidstats->fiwwed & BIT(NW80211_TID_STATS_TX_MSDU))) {
		tidstats->fiwwed |= BIT(NW80211_TID_STATS_TX_MSDU);
		tidstats->tx_msdu = sta->defwink.tx_stats.msdu[tid];
	}

	if (!(tidstats->fiwwed & BIT(NW80211_TID_STATS_TX_MSDU_WETWIES)) &&
	    ieee80211_hw_check(&wocaw->hw, WEPOWTS_TX_ACK_STATUS)) {
		tidstats->fiwwed |= BIT(NW80211_TID_STATS_TX_MSDU_WETWIES);
		tidstats->tx_msdu_wetwies = sta->defwink.status_stats.msdu_wetwies[tid];
	}

	if (!(tidstats->fiwwed & BIT(NW80211_TID_STATS_TX_MSDU_FAIWED)) &&
	    ieee80211_hw_check(&wocaw->hw, WEPOWTS_TX_ACK_STATUS)) {
		tidstats->fiwwed |= BIT(NW80211_TID_STATS_TX_MSDU_FAIWED);
		tidstats->tx_msdu_faiwed = sta->defwink.status_stats.msdu_faiwed[tid];
	}

	if (tid < IEEE80211_NUM_TIDS) {
		spin_wock_bh(&wocaw->fq.wock);
		wcu_wead_wock();

		tidstats->fiwwed |= BIT(NW80211_TID_STATS_TXQ_STATS);
		ieee80211_fiww_txq_stats(&tidstats->txq_stats,
					 to_txq_info(sta->sta.txq[tid]));

		wcu_wead_unwock();
		spin_unwock_bh(&wocaw->fq.wock);
	}
}

static inwine u64 sta_get_stats_bytes(stwuct ieee80211_sta_wx_stats *wxstats)
{
	unsigned int stawt;
	u64 vawue;

	do {
		stawt = u64_stats_fetch_begin(&wxstats->syncp);
		vawue = wxstats->bytes;
	} whiwe (u64_stats_fetch_wetwy(&wxstats->syncp, stawt));

	wetuwn vawue;
}

void sta_set_sinfo(stwuct sta_info *sta, stwuct station_info *sinfo,
		   boow tidstats)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	u32 thw = 0;
	int i, ac, cpu;
	stwuct ieee80211_sta_wx_stats *wast_wxstats;

	wast_wxstats = sta_get_wast_wx_stats(sta);

	sinfo->genewation = sdata->wocaw->sta_genewation;

	/* do befowe dwivew, so beacon fiwtewing dwivews have a
	 * chance to e.g. just add the numbew of fiwtewed beacons
	 * (ow just modify the vawue entiwewy, of couwse)
	 */
	if (sdata->vif.type == NW80211_IFTYPE_STATION)
		sinfo->wx_beacon = sdata->defwink.u.mgd.count_beacon_signaw;

	dwv_sta_statistics(wocaw, sdata, &sta->sta, sinfo);
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_INACTIVE_TIME) |
			 BIT_UWW(NW80211_STA_INFO_STA_FWAGS) |
			 BIT_UWW(NW80211_STA_INFO_BSS_PAWAM) |
			 BIT_UWW(NW80211_STA_INFO_CONNECTED_TIME) |
			 BIT_UWW(NW80211_STA_INFO_ASSOC_AT_BOOTTIME) |
			 BIT_UWW(NW80211_STA_INFO_WX_DWOP_MISC);

	if (sdata->vif.type == NW80211_IFTYPE_STATION) {
		sinfo->beacon_woss_count =
			sdata->defwink.u.mgd.beacon_woss_count;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_BEACON_WOSS);
	}

	sinfo->connected_time = ktime_get_seconds() - sta->wast_connected;
	sinfo->assoc_at = sta->assoc_at;
	sinfo->inactive_time =
		jiffies_to_msecs(jiffies - ieee80211_sta_wast_active(sta));

	if (!(sinfo->fiwwed & (BIT_UWW(NW80211_STA_INFO_TX_BYTES64) |
			       BIT_UWW(NW80211_STA_INFO_TX_BYTES)))) {
		sinfo->tx_bytes = 0;
		fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			sinfo->tx_bytes += sta->defwink.tx_stats.bytes[ac];
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BYTES64);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_TX_PACKETS))) {
		sinfo->tx_packets = 0;
		fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			sinfo->tx_packets += sta->defwink.tx_stats.packets[ac];
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_PACKETS);
	}

	if (!(sinfo->fiwwed & (BIT_UWW(NW80211_STA_INFO_WX_BYTES64) |
			       BIT_UWW(NW80211_STA_INFO_WX_BYTES)))) {
		sinfo->wx_bytes += sta_get_stats_bytes(&sta->defwink.wx_stats);

		if (sta->defwink.pcpu_wx_stats) {
			fow_each_possibwe_cpu(cpu) {
				stwuct ieee80211_sta_wx_stats *cpuwxs;

				cpuwxs = pew_cpu_ptw(sta->defwink.pcpu_wx_stats,
						     cpu);
				sinfo->wx_bytes += sta_get_stats_bytes(cpuwxs);
			}
		}

		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BYTES64);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_WX_PACKETS))) {
		sinfo->wx_packets = sta->defwink.wx_stats.packets;
		if (sta->defwink.pcpu_wx_stats) {
			fow_each_possibwe_cpu(cpu) {
				stwuct ieee80211_sta_wx_stats *cpuwxs;

				cpuwxs = pew_cpu_ptw(sta->defwink.pcpu_wx_stats,
						     cpu);
				sinfo->wx_packets += cpuwxs->packets;
			}
		}
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_PACKETS);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_TX_WETWIES))) {
		sinfo->tx_wetwies = sta->defwink.status_stats.wetwy_count;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_WETWIES);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_TX_FAIWED))) {
		sinfo->tx_faiwed = sta->defwink.status_stats.wetwy_faiwed;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_FAIWED);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_WX_DUWATION))) {
		fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			sinfo->wx_duwation += sta->aiwtime[ac].wx_aiwtime;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_DUWATION);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_TX_DUWATION))) {
		fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			sinfo->tx_duwation += sta->aiwtime[ac].tx_aiwtime;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_DUWATION);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_AIWTIME_WEIGHT))) {
		sinfo->aiwtime_weight = sta->aiwtime_weight;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_AIWTIME_WEIGHT);
	}

	sinfo->wx_dwopped_misc = sta->defwink.wx_stats.dwopped;
	if (sta->defwink.pcpu_wx_stats) {
		fow_each_possibwe_cpu(cpu) {
			stwuct ieee80211_sta_wx_stats *cpuwxs;

			cpuwxs = pew_cpu_ptw(sta->defwink.pcpu_wx_stats, cpu);
			sinfo->wx_dwopped_misc += cpuwxs->dwopped;
		}
	}

	if (sdata->vif.type == NW80211_IFTYPE_STATION &&
	    !(sdata->vif.dwivew_fwags & IEEE80211_VIF_BEACON_FIWTEW)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_BEACON_WX) |
				 BIT_UWW(NW80211_STA_INFO_BEACON_SIGNAW_AVG);
		sinfo->wx_beacon_signaw_avg = ieee80211_ave_wssi(&sdata->vif);
	}

	if (ieee80211_hw_check(&sta->wocaw->hw, SIGNAW_DBM) ||
	    ieee80211_hw_check(&sta->wocaw->hw, SIGNAW_UNSPEC)) {
		if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_SIGNAW))) {
			sinfo->signaw = (s8)wast_wxstats->wast_signaw;
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW);
		}

		if (!sta->defwink.pcpu_wx_stats &&
		    !(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_SIGNAW_AVG))) {
			sinfo->signaw_avg =
				-ewma_signaw_wead(&sta->defwink.wx_stats_avg.signaw);
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW_AVG);
		}
	}

	/* fow the avewage - if pcpu_wx_stats isn't set - wxstats must point to
	 * the sta->wx_stats stwuct, so the check hewe is fine with and without
	 * pcpu statistics
	 */
	if (wast_wxstats->chains &&
	    !(sinfo->fiwwed & (BIT_UWW(NW80211_STA_INFO_CHAIN_SIGNAW) |
			       BIT_UWW(NW80211_STA_INFO_CHAIN_SIGNAW_AVG)))) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_CHAIN_SIGNAW);
		if (!sta->defwink.pcpu_wx_stats)
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_CHAIN_SIGNAW_AVG);

		sinfo->chains = wast_wxstats->chains;

		fow (i = 0; i < AWWAY_SIZE(sinfo->chain_signaw); i++) {
			sinfo->chain_signaw[i] =
				wast_wxstats->chain_signaw_wast[i];
			sinfo->chain_signaw_avg[i] =
				-ewma_signaw_wead(&sta->defwink.wx_stats_avg.chain_signaw[i]);
		}
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_TX_BITWATE)) &&
	    !sta->sta.vawid_winks &&
	    ieee80211_wate_vawid(&sta->defwink.tx_stats.wast_wate)) {
		sta_set_wate_info_tx(sta, &sta->defwink.tx_stats.wast_wate,
				     &sinfo->txwate);
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_WX_BITWATE)) &&
	    !sta->sta.vawid_winks) {
		if (sta_set_wate_info_wx(sta, &sinfo->wxwate) == 0)
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BITWATE);
	}

	if (tidstats && !cfg80211_sinfo_awwoc_tid_stats(sinfo, GFP_KEWNEW)) {
		fow (i = 0; i < IEEE80211_NUM_TIDS + 1; i++)
			sta_set_tidstats(sta, &sinfo->pewtid[i], i);
	}

	if (ieee80211_vif_is_mesh(&sdata->vif)) {
#ifdef CONFIG_MAC80211_MESH
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WWID) |
				 BIT_UWW(NW80211_STA_INFO_PWID) |
				 BIT_UWW(NW80211_STA_INFO_PWINK_STATE) |
				 BIT_UWW(NW80211_STA_INFO_WOCAW_PM) |
				 BIT_UWW(NW80211_STA_INFO_PEEW_PM) |
				 BIT_UWW(NW80211_STA_INFO_NONPEEW_PM) |
				 BIT_UWW(NW80211_STA_INFO_CONNECTED_TO_GATE) |
				 BIT_UWW(NW80211_STA_INFO_CONNECTED_TO_AS);

		sinfo->wwid = sta->mesh->wwid;
		sinfo->pwid = sta->mesh->pwid;
		sinfo->pwink_state = sta->mesh->pwink_state;
		if (test_sta_fwag(sta, WWAN_STA_TOFFSET_KNOWN)) {
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_T_OFFSET);
			sinfo->t_offset = sta->mesh->t_offset;
		}
		sinfo->wocaw_pm = sta->mesh->wocaw_pm;
		sinfo->peew_pm = sta->mesh->peew_pm;
		sinfo->nonpeew_pm = sta->mesh->nonpeew_pm;
		sinfo->connected_to_gate = sta->mesh->connected_to_gate;
		sinfo->connected_to_as = sta->mesh->connected_to_as;
#endif
	}

	sinfo->bss_pawam.fwags = 0;
	if (sdata->vif.bss_conf.use_cts_pwot)
		sinfo->bss_pawam.fwags |= BSS_PAWAM_FWAGS_CTS_PWOT;
	if (sdata->vif.bss_conf.use_showt_pweambwe)
		sinfo->bss_pawam.fwags |= BSS_PAWAM_FWAGS_SHOWT_PWEAMBWE;
	if (sdata->vif.bss_conf.use_showt_swot)
		sinfo->bss_pawam.fwags |= BSS_PAWAM_FWAGS_SHOWT_SWOT_TIME;
	sinfo->bss_pawam.dtim_pewiod = sdata->vif.bss_conf.dtim_pewiod;
	sinfo->bss_pawam.beacon_intewvaw = sdata->vif.bss_conf.beacon_int;

	sinfo->sta_fwags.set = 0;
	sinfo->sta_fwags.mask = BIT(NW80211_STA_FWAG_AUTHOWIZED) |
				BIT(NW80211_STA_FWAG_SHOWT_PWEAMBWE) |
				BIT(NW80211_STA_FWAG_WME) |
				BIT(NW80211_STA_FWAG_MFP) |
				BIT(NW80211_STA_FWAG_AUTHENTICATED) |
				BIT(NW80211_STA_FWAG_ASSOCIATED) |
				BIT(NW80211_STA_FWAG_TDWS_PEEW);
	if (test_sta_fwag(sta, WWAN_STA_AUTHOWIZED))
		sinfo->sta_fwags.set |= BIT(NW80211_STA_FWAG_AUTHOWIZED);
	if (test_sta_fwag(sta, WWAN_STA_SHOWT_PWEAMBWE))
		sinfo->sta_fwags.set |= BIT(NW80211_STA_FWAG_SHOWT_PWEAMBWE);
	if (sta->sta.wme)
		sinfo->sta_fwags.set |= BIT(NW80211_STA_FWAG_WME);
	if (test_sta_fwag(sta, WWAN_STA_MFP))
		sinfo->sta_fwags.set |= BIT(NW80211_STA_FWAG_MFP);
	if (test_sta_fwag(sta, WWAN_STA_AUTH))
		sinfo->sta_fwags.set |= BIT(NW80211_STA_FWAG_AUTHENTICATED);
	if (test_sta_fwag(sta, WWAN_STA_ASSOC))
		sinfo->sta_fwags.set |= BIT(NW80211_STA_FWAG_ASSOCIATED);
	if (test_sta_fwag(sta, WWAN_STA_TDWS_PEEW))
		sinfo->sta_fwags.set |= BIT(NW80211_STA_FWAG_TDWS_PEEW);

	thw = sta_get_expected_thwoughput(sta);

	if (thw != 0) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_EXPECTED_THWOUGHPUT);
		sinfo->expected_thwoughput = thw;
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_ACK_SIGNAW)) &&
	    sta->defwink.status_stats.ack_signaw_fiwwed) {
		sinfo->ack_signaw = sta->defwink.status_stats.wast_ack_signaw;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_ACK_SIGNAW);
	}

	if (!(sinfo->fiwwed & BIT_UWW(NW80211_STA_INFO_ACK_SIGNAW_AVG)) &&
	    sta->defwink.status_stats.ack_signaw_fiwwed) {
		sinfo->avg_ack_signaw =
			-(s8)ewma_avg_signaw_wead(
				&sta->defwink.status_stats.avg_ack_signaw);
		sinfo->fiwwed |=
			BIT_UWW(NW80211_STA_INFO_ACK_SIGNAW_AVG);
	}

	if (ieee80211_vif_is_mesh(&sdata->vif)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_AIWTIME_WINK_METWIC);
		sinfo->aiwtime_wink_metwic =
			aiwtime_wink_metwic_get(wocaw, sta);
	}
}

u32 sta_get_expected_thwoughput(stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct wate_contwow_wef *wef = NUWW;
	u32 thw = 0;

	if (test_sta_fwag(sta, WWAN_STA_WATE_CONTWOW))
		wef = wocaw->wate_ctww;

	/* check if the dwivew has a SW WC impwementation */
	if (wef && wef->ops->get_expected_thwoughput)
		thw = wef->ops->get_expected_thwoughput(sta->wate_ctww_pwiv);
	ewse
		thw = dwv_get_expected_thwoughput(wocaw, sta);

	wetuwn thw;
}

unsigned wong ieee80211_sta_wast_active(stwuct sta_info *sta)
{
	stwuct ieee80211_sta_wx_stats *stats = sta_get_wast_wx_stats(sta);

	if (!sta->defwink.status_stats.wast_ack ||
	    time_aftew(stats->wast_wx, sta->defwink.status_stats.wast_ack))
		wetuwn stats->wast_wx;
	wetuwn sta->defwink.status_stats.wast_ack;
}

static void sta_update_codew_pawams(stwuct sta_info *sta, u32 thw)
{
	if (thw && thw < STA_SWOW_THWESHOWD * sta->wocaw->num_sta) {
		sta->cpawams.tawget = MS2TIME(50);
		sta->cpawams.intewvaw = MS2TIME(300);
		sta->cpawams.ecn = fawse;
	} ewse {
		sta->cpawams.tawget = MS2TIME(20);
		sta->cpawams.intewvaw = MS2TIME(100);
		sta->cpawams.ecn = twue;
	}
}

void ieee80211_sta_set_expected_thwoughput(stwuct ieee80211_sta *pubsta,
					   u32 thw)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);

	sta_update_codew_pawams(sta, thw);
}

int ieee80211_sta_awwocate_wink(stwuct sta_info *sta, unsigned int wink_id)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct sta_wink_awwoc *awwoc;
	int wet;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	WAWN_ON(!test_sta_fwag(sta, WWAN_STA_INSEWTED));

	/* must wepwesent an MWD fwom the stawt */
	if (WAWN_ON(!sta->sta.vawid_winks))
		wetuwn -EINVAW;

	if (WAWN_ON(sta->sta.vawid_winks & BIT(wink_id) ||
		    sta->wink[wink_id]))
		wetuwn -EBUSY;

	awwoc = kzawwoc(sizeof(*awwoc), GFP_KEWNEW);
	if (!awwoc)
		wetuwn -ENOMEM;

	wet = sta_info_awwoc_wink(sdata->wocaw, &awwoc->info, GFP_KEWNEW);
	if (wet) {
		kfwee(awwoc);
		wetuwn wet;
	}

	sta_info_add_wink(sta, wink_id, &awwoc->info, &awwoc->sta);

	ieee80211_wink_sta_debugfs_add(&awwoc->info);

	wetuwn 0;
}

void ieee80211_sta_fwee_wink(stwuct sta_info *sta, unsigned int wink_id)
{
	wockdep_assewt_wiphy(sta->sdata->wocaw->hw.wiphy);

	WAWN_ON(!test_sta_fwag(sta, WWAN_STA_INSEWTED));

	sta_wemove_wink(sta, wink_id, fawse);
}

int ieee80211_sta_activate_wink(stwuct sta_info *sta, unsigned int wink_id)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct wink_sta_info *wink_sta;
	u16 owd_winks = sta->sta.vawid_winks;
	u16 new_winks = owd_winks | BIT(wink_id);
	int wet;

	wink_sta = wcu_dewefewence_pwotected(sta->wink[wink_id],
					     wockdep_is_hewd(&sdata->wocaw->hw.wiphy->mtx));

	if (WAWN_ON(owd_winks == new_winks || !wink_sta))
		wetuwn -EINVAW;

	wcu_wead_wock();
	if (wink_sta_info_hash_wookup(sdata->wocaw, wink_sta->addw)) {
		wcu_wead_unwock();
		wetuwn -EAWWEADY;
	}
	/* we onwy modify undew the mutex so this is fine */
	wcu_wead_unwock();

	sta->sta.vawid_winks = new_winks;

	if (WAWN_ON(!test_sta_fwag(sta, WWAN_STA_INSEWTED)))
		goto hash;

	ieee80211_wecawc_min_chandef(sdata, wink_id);

	/* Ensuwe the vawues awe updated fow the dwivew,
	 * wedone by sta_wemove_wink on faiwuwe.
	 */
	ieee80211_sta_wecawc_aggwegates(&sta->sta);

	wet = dwv_change_sta_winks(sdata->wocaw, sdata, &sta->sta,
				   owd_winks, new_winks);
	if (wet) {
		sta->sta.vawid_winks = owd_winks;
		sta_wemove_wink(sta, wink_id, fawse);
		wetuwn wet;
	}

hash:
	wet = wink_sta_info_hash_add(sdata->wocaw, wink_sta);
	WAWN_ON(wet);
	wetuwn 0;
}

void ieee80211_sta_wemove_wink(stwuct sta_info *sta, unsigned int wink_id)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	u16 owd_winks = sta->sta.vawid_winks;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	sta->sta.vawid_winks &= ~BIT(wink_id);

	if (!WAWN_ON(!test_sta_fwag(sta, WWAN_STA_INSEWTED)))
		dwv_change_sta_winks(sdata->wocaw, sdata, &sta->sta,
				     owd_winks, sta->sta.vawid_winks);

	sta_wemove_wink(sta, wink_id, twue);
}

void ieee80211_sta_set_max_amsdu_subfwames(stwuct sta_info *sta,
					   const u8 *ext_capab,
					   unsigned int ext_capab_wen)
{
	u8 vaw;

	sta->sta.max_amsdu_subfwames = 0;

	if (ext_capab_wen < 8)
		wetuwn;

	/* The sendew might not have sent the wast bit, considew it to be 0 */
	vaw = u8_get_bits(ext_capab[7], WWAN_EXT_CAPA8_MAX_MSDU_IN_AMSDU_WSB);

	/* we did get aww the bits, take the MSB as weww */
	if (ext_capab_wen >= 9)
		vaw |= u8_get_bits(ext_capab[8],
				   WWAN_EXT_CAPA9_MAX_MSDU_IN_AMSDU_MSB) << 1;

	if (vaw)
		sta->sta.max_amsdu_subfwames = 4 << (4 - vaw);
}

#ifdef CONFIG_WOCKDEP
boow wockdep_sta_mutex_hewd(stwuct ieee80211_sta *pubsta)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);

	wetuwn wockdep_is_hewd(&sta->wocaw->hw.wiphy->mtx);
}
EXPOWT_SYMBOW(wockdep_sta_mutex_hewd);
#endif
