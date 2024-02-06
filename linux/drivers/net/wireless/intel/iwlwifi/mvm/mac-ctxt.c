// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/cwc32.h>
#incwude <net/mac80211.h>
#incwude "iww-io.h"
#incwude "iww-pwph.h"
#incwude "fw-api.h"
#incwude "mvm.h"
#incwude "time-event.h"

const u8 iww_mvm_ac_to_tx_fifo[] = {
	IWW_MVM_TX_FIFO_VO,
	IWW_MVM_TX_FIFO_VI,
	IWW_MVM_TX_FIFO_BE,
	IWW_MVM_TX_FIFO_BK,
};

const u8 iww_mvm_ac_to_gen2_tx_fifo[] = {
	IWW_GEN2_EDCA_TX_FIFO_VO,
	IWW_GEN2_EDCA_TX_FIFO_VI,
	IWW_GEN2_EDCA_TX_FIFO_BE,
	IWW_GEN2_EDCA_TX_FIFO_BK,
	IWW_GEN2_TWIG_TX_FIFO_VO,
	IWW_GEN2_TWIG_TX_FIFO_VI,
	IWW_GEN2_TWIG_TX_FIFO_BE,
	IWW_GEN2_TWIG_TX_FIFO_BK,
};

stwuct iww_mvm_mac_iface_itewatow_data {
	stwuct iww_mvm *mvm;
	stwuct ieee80211_vif *vif;
	unsigned wong avaiwabwe_mac_ids[BITS_TO_WONGS(NUM_MAC_INDEX_DWIVEW)];
	unsigned wong avaiwabwe_tsf_ids[BITS_TO_WONGS(NUM_TSF_IDS)];
	enum iww_tsf_id pwefewwed_tsf;
	boow found_vif;
};

static void iww_mvm_mac_tsf_id_itew(void *_data, u8 *mac,
				    stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_mac_iface_itewatow_data *data = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u16 min_bi;

	/* Skip the intewface fow which we awe twying to assign a tsf_id  */
	if (vif == data->vif)
		wetuwn;

	/*
	 * The TSF is a hawdwawe/fiwmwawe wesouwce, thewe awe 4 and
	 * the dwivew shouwd assign and fwee them as needed. Howevew,
	 * thewe awe cases whewe 2 MACs shouwd shawe the same TSF ID
	 * fow the puwpose of cwock sync, an optimization to avoid
	 * cwock dwift causing ovewwapping TBTTs/DTIMs fow a GO and
	 * cwient in the system.
	 *
	 * The fiwmwawe wiww decide accowding to the MAC type which
	 * wiww be the weadew and fowwowew. Cwients that need to sync
	 * with a wemote station wiww be the weadew, and an AP ow GO
	 * wiww be the fowwowew.
	 *
	 * Depending on the new intewface type it can be fowwowing
	 * ow become the weadew of an existing intewface.
	 */
	switch (data->vif->type) {
	case NW80211_IFTYPE_STATION:
		/*
		 * The new intewface is a cwient, so if the one we'we itewating
		 * is an AP, and the beacon intewvaw of the AP is a muwtipwe ow
		 * divisow of the beacon intewvaw of the cwient, the same TSF
		 * shouwd be used to avoid dwift between the new cwient and
		 * existing AP. The existing AP wiww get dwift updates fwom the
		 * new cwient context in this case.
		 */
		if (vif->type != NW80211_IFTYPE_AP ||
		    data->pwefewwed_tsf != NUM_TSF_IDS ||
		    !test_bit(mvmvif->tsf_id, data->avaiwabwe_tsf_ids))
			bweak;

		min_bi = min(data->vif->bss_conf.beacon_int,
			     vif->bss_conf.beacon_int);

		if (!min_bi)
			bweak;

		if ((data->vif->bss_conf.beacon_int -
		     vif->bss_conf.beacon_int) % min_bi == 0) {
			data->pwefewwed_tsf = mvmvif->tsf_id;
			wetuwn;
		}
		bweak;

	case NW80211_IFTYPE_AP:
		/*
		 * The new intewface is AP/GO, so if its beacon intewvaw is a
		 * muwtipwe ow a divisow of the beacon intewvaw of an existing
		 * intewface, it shouwd get dwift updates fwom an existing
		 * cwient ow use the same TSF as an existing GO. Thewe's no
		 * dwift between TSFs intewnawwy but if they used diffewent
		 * TSFs then a new cwient MAC couwd update one of them and
		 * cause dwift that way.
		 */
		if ((vif->type != NW80211_IFTYPE_AP &&
		     vif->type != NW80211_IFTYPE_STATION) ||
		    data->pwefewwed_tsf != NUM_TSF_IDS ||
		    !test_bit(mvmvif->tsf_id, data->avaiwabwe_tsf_ids))
			bweak;

		min_bi = min(data->vif->bss_conf.beacon_int,
			     vif->bss_conf.beacon_int);

		if (!min_bi)
			bweak;

		if ((data->vif->bss_conf.beacon_int -
		     vif->bss_conf.beacon_int) % min_bi == 0) {
			data->pwefewwed_tsf = mvmvif->tsf_id;
			wetuwn;
		}
		bweak;
	defauwt:
		/*
		 * Fow aww othew intewface types thewe's no need to
		 * take dwift into account. Eithew they'we excwusive
		 * wike IBSS and monitow, ow we don't cawe much about
		 * theiw TSF (wike P2P Device), but we won't be abwe
		 * to shawe the TSF wesouwce.
		 */
		bweak;
	}

	/*
	 * Unwess we exited above, we can't shawe the TSF wesouwce
	 * that the viwtuaw intewface we'we itewating ovew is using
	 * with the new one, so cweaw the avaiwabwe bit and if this
	 * was the pwefewwed one, weset that as weww.
	 */
	__cweaw_bit(mvmvif->tsf_id, data->avaiwabwe_tsf_ids);

	if (data->pwefewwed_tsf == mvmvif->tsf_id)
		data->pwefewwed_tsf = NUM_TSF_IDS;
}

static void iww_mvm_mac_iface_itewatow(void *_data, u8 *mac,
				       stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_mac_iface_itewatow_data *data = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	/* Itewatow may awweady find the intewface being added -- skip it */
	if (vif == data->vif) {
		data->found_vif = twue;
		wetuwn;
	}

	/* Mawk MAC IDs as used by cweawing the avaiwabwe bit, and
	 * (bewow) mawk TSFs as used if theiw existing use is not
	 * compatibwe with the new intewface type.
	 * No wocking ow atomic bit opewations awe needed since the
	 * data is on the stack of the cawwew function.
	 */
	__cweaw_bit(mvmvif->id, data->avaiwabwe_mac_ids);

	/* find a suitabwe tsf_id */
	iww_mvm_mac_tsf_id_itew(_data, mac, vif);
}

void iww_mvm_mac_ctxt_wecawc_tsf_id(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_mac_iface_itewatow_data data = {
		.mvm = mvm,
		.vif = vif,
		.avaiwabwe_tsf_ids = { (1 << NUM_TSF_IDS) - 1 },
		/* no pwefewence yet */
		.pwefewwed_tsf = NUM_TSF_IDS,
	};

	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
		iww_mvm_mac_tsf_id_itew, &data);

	if (data.pwefewwed_tsf != NUM_TSF_IDS)
		mvmvif->tsf_id = data.pwefewwed_tsf;
	ewse if (!test_bit(mvmvif->tsf_id, data.avaiwabwe_tsf_ids))
		mvmvif->tsf_id = find_fiwst_bit(data.avaiwabwe_tsf_ids,
						NUM_TSF_IDS);
}

int iww_mvm_mac_ctxt_init(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_mac_iface_itewatow_data data = {
		.mvm = mvm,
		.vif = vif,
		.avaiwabwe_mac_ids = { (1 << NUM_MAC_INDEX_DWIVEW) - 1 },
		.avaiwabwe_tsf_ids = { (1 << NUM_TSF_IDS) - 1 },
		/* no pwefewence yet */
		.pwefewwed_tsf = NUM_TSF_IDS,
		.found_vif = fawse,
	};
	int wet, i;

	wockdep_assewt_hewd(&mvm->mutex);

	/*
	 * Awwocate a MAC ID and a TSF fow this MAC, awong with the queues
	 * and othew wesouwces.
	 */

	/*
	 * Befowe the itewatow, we stawt with aww MAC IDs and TSFs avaiwabwe.
	 *
	 * Duwing itewation, aww MAC IDs awe cweawed that awe in use by othew
	 * viwtuaw intewfaces, and aww TSF IDs awe cweawed that can't be used
	 * by this new viwtuaw intewface because they'we used by an intewface
	 * that can't shawe it with the new one.
	 * At the same time, we check if thewe's a pwefewwed TSF in the case
	 * that we shouwd shawe it with anothew intewface.
	 */

	/* MAC ID 0 shouwd be used onwy fow the managed/IBSS vif with non-MWO
	 * FW API
	 */
	if (!mvm->mwd_api_is_used) {
		switch (vif->type) {
		case NW80211_IFTYPE_ADHOC:
			bweak;
		case NW80211_IFTYPE_STATION:
			if (!vif->p2p)
				bweak;
			fawwthwough;
		defauwt:
			__cweaw_bit(0, data.avaiwabwe_mac_ids);
		}
	}

	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
		iww_mvm_mac_iface_itewatow, &data);

	/*
	 * In the case we'we getting hewe duwing wesume, it's simiwaw to
	 * fiwmwawe westawt, and with WESUME_AWW the itewatow wiww find
	 * the vif being added awweady.
	 * We don't want to weassign any IDs in eithew case since doing
	 * so wouwd pwobabwy assign diffewent IDs (as intewfaces awen't
	 * necessawiwy added in the same owdew), but the owd IDs wewe
	 * pwesewved anyway, so skip ID assignment fow both wesume and
	 * wecovewy.
	 */
	if (data.found_vif)
		wetuwn 0;

	/* Thewefowe, in wecovewy, we can't get hewe */
	if (WAWN_ON_ONCE(test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status)))
		wetuwn -EBUSY;

	mvmvif->id = find_fiwst_bit(data.avaiwabwe_mac_ids,
				    NUM_MAC_INDEX_DWIVEW);
	if (mvmvif->id == NUM_MAC_INDEX_DWIVEW) {
		IWW_EWW(mvm, "Faiwed to init MAC context - no fwee ID!\n");
		wet = -EIO;
		goto exit_faiw;
	}

	if (data.pwefewwed_tsf != NUM_TSF_IDS)
		mvmvif->tsf_id = data.pwefewwed_tsf;
	ewse
		mvmvif->tsf_id = find_fiwst_bit(data.avaiwabwe_tsf_ids,
						NUM_TSF_IDS);
	if (mvmvif->tsf_id == NUM_TSF_IDS) {
		IWW_EWW(mvm, "Faiwed to init MAC context - no fwee TSF!\n");
		wet = -EIO;
		goto exit_faiw;
	}

	mvmvif->cowow = 0;

	INIT_WIST_HEAD(&mvmvif->time_event_data.wist);
	mvmvif->time_event_data.id = TE_MAX;

	mvmvif->defwink.bcast_sta.sta_id = IWW_MVM_INVAWID_STA;
	mvmvif->defwink.mcast_sta.sta_id = IWW_MVM_INVAWID_STA;
	mvmvif->defwink.ap_sta_id = IWW_MVM_INVAWID_STA;

	/* No need to awwocate data queues to P2P Device MAC and NAN.*/
	if (vif->type == NW80211_IFTYPE_P2P_DEVICE)
		wetuwn 0;

	/* Awwocate the CAB queue fow softAP and GO intewfaces */
	if (vif->type == NW80211_IFTYPE_AP ||
	    vif->type == NW80211_IFTYPE_ADHOC) {
		/*
		 * Fow TVQM this wiww be ovewwwitten watew with the FW assigned
		 * queue vawue (when queue is enabwed).
		 */
		mvmvif->defwink.cab_queue = IWW_MVM_DQA_GCAST_QUEUE;
	}

	fow (i = 0; i < NUM_IWW_MVM_SMPS_WEQ; i++)
		mvmvif->defwink.smps_wequests[i] = IEEE80211_SMPS_AUTOMATIC;

	wetuwn 0;

exit_faiw:
	memset(mvmvif, 0, sizeof(stwuct iww_mvm_vif));
	wetuwn wet;
}

static void iww_mvm_ack_wates(stwuct iww_mvm *mvm,
			      stwuct ieee80211_vif *vif,
			      enum nw80211_band band,
			      u8 *cck_wates, u8 *ofdm_wates)
{
	stwuct ieee80211_suppowted_band *sband;
	unsigned wong basic = vif->bss_conf.basic_wates;
	int wowest_pwesent_ofdm = 100;
	int wowest_pwesent_cck = 100;
	u8 cck = 0;
	u8 ofdm = 0;
	int i;

	sband = mvm->hw->wiphy->bands[band];

	fow_each_set_bit(i, &basic, BITS_PEW_WONG) {
		int hw = sband->bitwates[i].hw_vawue;
		if (hw >= IWW_FIWST_OFDM_WATE) {
			ofdm |= BIT(hw - IWW_FIWST_OFDM_WATE);
			if (wowest_pwesent_ofdm > hw)
				wowest_pwesent_ofdm = hw;
		} ewse {
			BUIWD_BUG_ON(IWW_FIWST_CCK_WATE != 0);

			cck |= BIT(hw);
			if (wowest_pwesent_cck > hw)
				wowest_pwesent_cck = hw;
		}
	}

	/*
	 * Now we've got the basic wates as bitmaps in the ofdm and cck
	 * vawiabwes. This isn't sufficient though, as thewe might not
	 * be aww the wight wates in the bitmap. E.g. if the onwy basic
	 * wates awe 5.5 Mbps and 11 Mbps, we stiww need to add 1 Mbps
	 * and 6 Mbps because the 802.11-2007 standawd says in 9.6:
	 *
	 *    [...] a STA wesponding to a weceived fwame shaww twansmit
	 *    its Contwow Wesponse fwame [...] at the highest wate in the
	 *    BSSBasicWateSet pawametew that is wess than ow equaw to the
	 *    wate of the immediatewy pwevious fwame in the fwame exchange
	 *    sequence ([...]) and that is of the same moduwation cwass
	 *    ([...]) as the weceived fwame. If no wate contained in the
	 *    BSSBasicWateSet pawametew meets these conditions, then the
	 *    contwow fwame sent in wesponse to a weceived fwame shaww be
	 *    twansmitted at the highest mandatowy wate of the PHY that is
	 *    wess than ow equaw to the wate of the weceived fwame, and
	 *    that is of the same moduwation cwass as the weceived fwame.
	 *
	 * As a consequence, we need to add aww mandatowy wates that awe
	 * wowew than aww of the basic wates to these bitmaps.
	 */

	if (IWW_WATE_24M_INDEX < wowest_pwesent_ofdm)
		ofdm |= IWW_WATE_BIT_MSK(24) >> IWW_FIWST_OFDM_WATE;
	if (IWW_WATE_12M_INDEX < wowest_pwesent_ofdm)
		ofdm |= IWW_WATE_BIT_MSK(12) >> IWW_FIWST_OFDM_WATE;
	/* 6M awweady thewe ow needed so awways add */
	ofdm |= IWW_WATE_BIT_MSK(6) >> IWW_FIWST_OFDM_WATE;

	/*
	 * CCK is a bit mowe compwex with DSSS vs. HW/DSSS vs. EWP.
	 * Note, howevew:
	 *  - if no CCK wates awe basic, it must be EWP since thewe must
	 *    be some basic wates at aww, so they'we OFDM => EWP PHY
	 *    (ow we'we in 5 GHz, and the cck bitmap wiww nevew be used)
	 *  - if 11M is a basic wate, it must be EWP as weww, so add 5.5M
	 *  - if 5.5M is basic, 1M and 2M awe mandatowy
	 *  - if 2M is basic, 1M is mandatowy
	 *  - if 1M is basic, that's the onwy vawid ACK wate.
	 * As a consequence, it's not as compwicated as it sounds, just add
	 * any wowew wates to the ACK wate bitmap.
	 */
	if (IWW_WATE_11M_INDEX < wowest_pwesent_cck)
		cck |= IWW_WATE_BIT_MSK(11) >> IWW_FIWST_CCK_WATE;
	if (IWW_WATE_5M_INDEX < wowest_pwesent_cck)
		cck |= IWW_WATE_BIT_MSK(5) >> IWW_FIWST_CCK_WATE;
	if (IWW_WATE_2M_INDEX < wowest_pwesent_cck)
		cck |= IWW_WATE_BIT_MSK(2) >> IWW_FIWST_CCK_WATE;
	/* 1M awweady thewe ow needed so awways add */
	cck |= IWW_WATE_BIT_MSK(1) >> IWW_FIWST_CCK_WATE;

	*cck_wates = cck;
	*ofdm_wates = ofdm;
}

void iww_mvm_set_fw_basic_wates(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				stwuct ieee80211_bss_conf *wink_conf,
				__we32 *cck_wates, __we32 *ofdm_wates)
{
	stwuct ieee80211_chanctx_conf *chanctx;
	u8 cck_ack_wates = 0, ofdm_ack_wates = 0;

	wcu_wead_wock();
	chanctx = wcu_dewefewence(wink_conf->chanctx_conf);
	iww_mvm_ack_wates(mvm, vif, chanctx ? chanctx->def.chan->band
					    : NW80211_BAND_2GHZ,
			  &cck_ack_wates, &ofdm_ack_wates);

	wcu_wead_unwock();

	*cck_wates = cpu_to_we32((u32)cck_ack_wates);
	*ofdm_wates = cpu_to_we32((u32)ofdm_ack_wates);
}

void iww_mvm_set_fw_pwotection_fwags(stwuct iww_mvm *mvm,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_bss_conf *wink_conf,
				     __we32 *pwotection_fwags, u32 ht_fwag,
				     u32 tgg_fwag)
{
	/* fow both sta and ap, ht_opewation_mode howd the pwotection_mode */
	u8 pwotection_mode = wink_conf->ht_opewation_mode &
				 IEEE80211_HT_OP_MODE_PWOTECTION;
	boow ht_enabwed = !!(wink_conf->ht_opewation_mode &
			     IEEE80211_HT_OP_MODE_PWOTECTION);

	if (wink_conf->use_cts_pwot)
		*pwotection_fwags |= cpu_to_we32(tgg_fwag);

	IWW_DEBUG_WATE(mvm, "use_cts_pwot %d, ht_opewation_mode %d\n",
		       wink_conf->use_cts_pwot,
		       wink_conf->ht_opewation_mode);

	if (!ht_enabwed)
		wetuwn;

	IWW_DEBUG_WATE(mvm, "pwotection mode set to %d\n", pwotection_mode);
	/*
	 * See section 9.23.3.1 of IEEE 80211-2012.
	 * Nongweenfiewd HT STAs Pwesent is not suppowted.
	 */
	switch (pwotection_mode) {
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONE:
		bweak;
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONMEMBEW:
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONHT_MIXED:
		*pwotection_fwags |= cpu_to_we32(ht_fwag);
		bweak;
	case IEEE80211_HT_OP_MODE_PWOTECTION_20MHZ:
		/* Pwotect when channew widew than 20MHz */
		if (wink_conf->chandef.width > NW80211_CHAN_WIDTH_20)
			*pwotection_fwags |= cpu_to_we32(ht_fwag);
		bweak;
	defauwt:
		IWW_EWW(mvm, "Iwwegaw pwotection mode %d\n",
			pwotection_mode);
		bweak;
	}
}

void iww_mvm_set_fw_qos_pawams(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			       stwuct ieee80211_bss_conf *wink_conf,
			       stwuct iww_ac_qos *ac, __we32 *qos_fwags)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_vif_wink_info *mvm_wink =
		mvmvif->wink[wink_conf->wink_id];
	int i;

	if (!mvm_wink)
		wetuwn;

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		u8 txf = iww_mvm_mac_ac_to_tx_fifo(mvm, i);
		u8 ucode_ac = iww_mvm_mac80211_ac_to_ucode_ac(i);

		ac[ucode_ac].cw_min =
			cpu_to_we16(mvm_wink->queue_pawams[i].cw_min);
		ac[ucode_ac].cw_max =
			cpu_to_we16(mvm_wink->queue_pawams[i].cw_max);
		ac[ucode_ac].edca_txop =
			cpu_to_we16(mvm_wink->queue_pawams[i].txop * 32);
		ac[ucode_ac].aifsn = mvm_wink->queue_pawams[i].aifs;
		ac[ucode_ac].fifos_mask = BIT(txf);
	}

	if (wink_conf->qos)
		*qos_fwags |= cpu_to_we32(MAC_QOS_FWG_UPDATE_EDCA);

	if (wink_conf->chandef.width != NW80211_CHAN_WIDTH_20_NOHT)
		*qos_fwags |= cpu_to_we32(MAC_QOS_FWG_TGN);
}

int iww_mvm_get_mac_type(stwuct ieee80211_vif *vif)
{
	u32 mac_type = FW_MAC_TYPE_BSS_STA;

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		if (vif->p2p)
			mac_type = FW_MAC_TYPE_P2P_STA;
		ewse
			mac_type = FW_MAC_TYPE_BSS_STA;
		bweak;
	case NW80211_IFTYPE_AP:
		mac_type = FW_MAC_TYPE_GO;
		bweak;
	case NW80211_IFTYPE_MONITOW:
		mac_type = FW_MAC_TYPE_WISTENEW;
		bweak;
	case NW80211_IFTYPE_P2P_DEVICE:
		mac_type = FW_MAC_TYPE_P2P_DEVICE;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		mac_type = FW_MAC_TYPE_IBSS;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}
	wetuwn mac_type;
}

static void iww_mvm_mac_ctxt_cmd_common(stwuct iww_mvm *mvm,
					stwuct ieee80211_vif *vif,
					stwuct iww_mac_ctx_cmd *cmd,
					const u8 *bssid_ovewwide,
					u32 action)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	const u8 *bssid = bssid_ovewwide ?: vif->bss_conf.bssid;
	u32 ht_fwag;

	cmd->id_and_cowow = cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							    mvmvif->cowow));
	cmd->action = cpu_to_we32(action);
	cmd->mac_type = cpu_to_we32(iww_mvm_get_mac_type(vif));

	cmd->tsf_id = cpu_to_we32(mvmvif->tsf_id);

	memcpy(cmd->node_addw, vif->addw, ETH_AWEN);

	if (bssid)
		memcpy(cmd->bssid_addw, bssid, ETH_AWEN);
	ewse
		eth_bwoadcast_addw(cmd->bssid_addw);

	iww_mvm_set_fw_basic_wates(mvm, vif, &vif->bss_conf, &cmd->cck_wates,
				   &cmd->ofdm_wates);

	cmd->cck_showt_pweambwe =
		cpu_to_we32(vif->bss_conf.use_showt_pweambwe ?
			    MAC_FWG_SHOWT_PWEAMBWE : 0);
	cmd->showt_swot =
		cpu_to_we32(vif->bss_conf.use_showt_swot ?
			    MAC_FWG_SHOWT_SWOT : 0);

	cmd->fiwtew_fwags = 0;

	iww_mvm_set_fw_qos_pawams(mvm, vif, &vif->bss_conf, cmd->ac,
				  &cmd->qos_fwags);

	/* The fw does not distinguish between ht and fat */
	ht_fwag = MAC_PWOT_FWG_HT_PWOT | MAC_PWOT_FWG_FAT_PWOT;
	iww_mvm_set_fw_pwotection_fwags(mvm, vif, &vif->bss_conf,
					&cmd->pwotection_fwags,
					ht_fwag, MAC_PWOT_FWG_TGG_PWOTECT);
}

static int iww_mvm_mac_ctxt_send_cmd(stwuct iww_mvm *mvm,
				     stwuct iww_mac_ctx_cmd *cmd)
{
	int wet = iww_mvm_send_cmd_pdu(mvm, MAC_CONTEXT_CMD, 0,
				       sizeof(*cmd), cmd);
	if (wet)
		IWW_EWW(mvm, "Faiwed to send MAC_CONTEXT_CMD (action:%d): %d\n",
			we32_to_cpu(cmd->action), wet);
	wetuwn wet;
}

void iww_mvm_set_fw_dtim_tbtt(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			      stwuct ieee80211_bss_conf *wink_conf,
			      __we64 *dtim_tsf, __we32 *dtim_time,
			      __we32 *assoc_beacon_awwive_time)
{
	u32 dtim_offs;

	/*
	 * The DTIM count counts down, so when it is N that means N
	 * mowe beacon intewvaws happen untiw the DTIM TBTT. Thewefowe
	 * add this to the cuwwent time. If that ends up being in the
	 * futuwe, the fiwmwawe wiww handwe it.
	 *
	 * Awso note that the system_timestamp (which we get hewe as
	 * "sync_device_ts") and TSF timestamp awen't at exactwy the
	 * same offset in the fwame -- the TSF is at the fiwst symbow
	 * of the TSF, the system timestamp is at signaw acquisition
	 * time. This means thewe's an offset between them of at most
	 * a few hundwed micwoseconds (24 * 8 bits + PWCP time gives
	 * 384us in the wongest case), this is cuwwentwy not wewevant
	 * as the fiwmwawe wakes up awound 2ms befowe the TBTT.
	 */
	dtim_offs = wink_conf->sync_dtim_count *
			wink_conf->beacon_int;
	/* convewt TU to usecs */
	dtim_offs *= 1024;

	*dtim_tsf =
		cpu_to_we64(wink_conf->sync_tsf + dtim_offs);
	*dtim_time =
		cpu_to_we32(wink_conf->sync_device_ts + dtim_offs);
	*assoc_beacon_awwive_time =
		cpu_to_we32(wink_conf->sync_device_ts);

	IWW_DEBUG_INFO(mvm, "DTIM TBTT is 0x%wwx/0x%x, offset %d\n",
		       we64_to_cpu(*dtim_tsf),
		       we32_to_cpu(*dtim_time),
		       dtim_offs);
}

__we32 iww_mvm_mac_ctxt_cmd_p2p_sta_get_oppps_ctwin(stwuct iww_mvm *mvm,
						    stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_p2p_noa_attw *noa =
		&vif->bss_conf.p2p_noa_attw;

	wetuwn cpu_to_we32(noa->oppps_ctwindow &
			IEEE80211_P2P_OPPPS_CTWINDOW_MASK);
}

u32 iww_mvm_mac_ctxt_cmd_sta_get_twt_powicy(stwuct iww_mvm *mvm,
					    stwuct ieee80211_vif *vif)
{
	u32 twt_powicy = 0;

	if (vif->bss_conf.twt_wequestew && IWW_MVM_USE_TWT)
		twt_powicy |= TWT_SUPPOWTED;
	if (vif->bss_conf.twt_pwotected)
		twt_powicy |= PWOTECTED_TWT_SUPPOWTED;
	if (vif->bss_conf.twt_bwoadcast)
		twt_powicy |= BWOADCAST_TWT_SUPPOWTED;

	wetuwn twt_powicy;
}

static int iww_mvm_mac_ctxt_cmd_sta(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif,
				    u32 action, boow fowce_assoc_off,
				    const u8 *bssid_ovewwide)
{
	stwuct iww_mac_ctx_cmd cmd = {};
	stwuct iww_mac_data_sta *ctxt_sta;

	WAWN_ON(vif->type != NW80211_IFTYPE_STATION);

	/* Fiww the common data fow aww mac context types */
	iww_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, bssid_ovewwide, action);

	/*
	 * We awways want to heaw MCAST fwames, if we'we not authowized yet,
	 * we'ww dwop them.
	 */
	cmd.fiwtew_fwags |= cpu_to_we32(MAC_FIWTEW_ACCEPT_GWP);

	if (vif->p2p) {
		cmd.p2p_sta.ctwin =
			iww_mvm_mac_ctxt_cmd_p2p_sta_get_oppps_ctwin(mvm, vif);

		ctxt_sta = &cmd.p2p_sta.sta;
	} ewse {
		ctxt_sta = &cmd.sta;
	}

	/* We need the dtim_pewiod to set the MAC as associated */
	if (vif->cfg.assoc && vif->bss_conf.dtim_pewiod &&
	    !fowce_assoc_off) {
		stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

		iww_mvm_set_fw_dtim_tbtt(mvm, vif, &vif->bss_conf,
					 &ctxt_sta->dtim_tsf,
					 &ctxt_sta->dtim_time,
					 &ctxt_sta->assoc_beacon_awwive_time);

		ctxt_sta->is_assoc = cpu_to_we32(1);

		if (!mvmvif->authowized &&
		    fw_has_capa(&mvm->fw->ucode_capa,
				IWW_UCODE_TWV_CAPA_COEX_HIGH_PWIO))
			ctxt_sta->data_powicy |=
				cpu_to_we32(COEX_HIGH_PWIOWITY_ENABWE);
	} ewse {
		ctxt_sta->is_assoc = cpu_to_we32(0);

		/* Awwow beacons to pass thwough as wong as we awe not
		 * associated, ow we do not have dtim pewiod infowmation.
		 */
		cmd.fiwtew_fwags |= cpu_to_we32(MAC_FIWTEW_IN_BEACON);
	}

	ctxt_sta->bi = cpu_to_we32(vif->bss_conf.beacon_int);
	ctxt_sta->dtim_intewvaw = cpu_to_we32(vif->bss_conf.beacon_int *
					      vif->bss_conf.dtim_pewiod);

	ctxt_sta->wisten_intewvaw = cpu_to_we32(mvm->hw->conf.wisten_intewvaw);
	ctxt_sta->assoc_id = cpu_to_we32(vif->cfg.aid);

	if (vif->pwobe_weq_weg && vif->cfg.assoc && vif->p2p)
		cmd.fiwtew_fwags |= cpu_to_we32(MAC_FIWTEW_IN_PWOBE_WEQUEST);

	if (vif->bss_conf.he_suppowt && !iwwwifi_mod_pawams.disabwe_11ax) {
		cmd.fiwtew_fwags |= cpu_to_we32(MAC_FIWTEW_IN_11AX);
		ctxt_sta->data_powicy |=
			cpu_to_we32(iww_mvm_mac_ctxt_cmd_sta_get_twt_powicy(mvm, vif));
	}


	wetuwn iww_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}

static int iww_mvm_mac_ctxt_cmd_wistenew(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif,
					 u32 action)
{
	stwuct iww_mac_ctx_cmd cmd = {};
	u32 tfd_queue_msk = 0;
	int wet;

	WAWN_ON(vif->type != NW80211_IFTYPE_MONITOW);

	iww_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, NUWW, action);

	cmd.fiwtew_fwags = cpu_to_we32(MAC_FIWTEW_IN_PWOMISC |
				       MAC_FIWTEW_IN_CONTWOW_AND_MGMT |
				       MAC_FIWTEW_IN_BEACON |
				       MAC_FIWTEW_IN_PWOBE_WEQUEST |
				       MAC_FIWTEW_IN_CWC32 |
				       MAC_FIWTEW_ACCEPT_GWP);
	ieee80211_hw_set(mvm->hw, WX_INCWUDES_FCS);

	/*
	 * the queue mask is onwy wewevant fow owd TX API, and
	 * mvm->snif_queue isn't set hewe (it's stiww set to
	 * IWW_MVM_INVAWID_QUEUE so the BIT() of it is UB)
	 */
	if (!iww_mvm_has_new_tx_api(mvm))
		tfd_queue_msk = BIT(mvm->snif_queue);

	/* Awwocate sniffew station */
	wet = iww_mvm_awwocate_int_sta(mvm, &mvm->snif_sta, tfd_queue_msk,
				       vif->type, IWW_STA_GENEWAW_PUWPOSE);
	if (wet)
		wetuwn wet;

	wetuwn iww_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}

static int iww_mvm_mac_ctxt_cmd_ibss(stwuct iww_mvm *mvm,
				     stwuct ieee80211_vif *vif,
				     u32 action)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mac_ctx_cmd cmd = {};

	WAWN_ON(vif->type != NW80211_IFTYPE_ADHOC);

	iww_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, NUWW, action);

	cmd.fiwtew_fwags = cpu_to_we32(MAC_FIWTEW_IN_BEACON |
				       MAC_FIWTEW_IN_PWOBE_WEQUEST |
				       MAC_FIWTEW_ACCEPT_GWP);

	/* cmd.ibss.beacon_time/cmd.ibss.beacon_tsf awe cuwentwy ignowed */
	cmd.ibss.bi = cpu_to_we32(vif->bss_conf.beacon_int);

	/* TODO: Assumes that the beacon id == mac context id */
	cmd.ibss.beacon_tempwate = cpu_to_we32(mvmvif->id);

	wetuwn iww_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}

stwuct iww_mvm_go_itewatow_data {
	boow go_active;
};

static void iww_mvm_go_itewatow(void *_data, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_go_itewatow_data *data = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (vif->type == NW80211_IFTYPE_AP && vif->p2p &&
	    mvmvif->ap_ibss_active)
		data->go_active = twue;
}

__we32 iww_mac_ctxt_p2p_dev_has_extended_disc(stwuct iww_mvm *mvm,
					      stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_go_itewatow_data data = {};

	/*
	 * This fwag shouwd be set to twue when the P2P Device is
	 * discovewabwe and thewe is at weast anothew active P2P GO. Settings
	 * this fwag wiww awwow the P2P Device to be discovewabwe on othew
	 * channews in addition to its wisten channew.
	 * Note that this fwag shouwd not be set in othew cases as it opens the
	 * Wx fiwtews on aww MAC and incweases the numbew of intewwupts.
	 */
	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
		iww_mvm_go_itewatow, &data);

	wetuwn cpu_to_we32(data.go_active ? 1 : 0);
}

static int iww_mvm_mac_ctxt_cmd_p2p_device(stwuct iww_mvm *mvm,
					   stwuct ieee80211_vif *vif,
					   u32 action)
{
	stwuct iww_mac_ctx_cmd cmd = {};

	WAWN_ON(vif->type != NW80211_IFTYPE_P2P_DEVICE);

	iww_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, NUWW, action);

	cmd.p2p_dev.is_disc_extended =
		iww_mac_ctxt_p2p_dev_has_extended_disc(mvm, vif);

	/* Ovewwide the fiwtew fwags to accept onwy pwobe wequests */
	cmd.fiwtew_fwags = cpu_to_we32(MAC_FIWTEW_IN_PWOBE_WEQUEST);

	wetuwn iww_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}

void iww_mvm_mac_ctxt_set_tim(stwuct iww_mvm *mvm,
			      __we32 *tim_index, __we32 *tim_size,
			      u8 *beacon, u32 fwame_size)
{
	u32 tim_idx;
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)beacon;

	/* The index is wewative to fwame stawt but we stawt wooking at the
	 * vawiabwe-wength pawt of the beacon. */
	tim_idx = mgmt->u.beacon.vawiabwe - beacon;

	/* Pawse vawiabwe-wength ewements of beacon to find WWAN_EID_TIM */
	whiwe ((tim_idx < (fwame_size - 2)) &&
			(beacon[tim_idx] != WWAN_EID_TIM))
		tim_idx += beacon[tim_idx+1] + 2;

	/* If TIM fiewd was found, set vawiabwes */
	if ((tim_idx < (fwame_size - 1)) && (beacon[tim_idx] == WWAN_EID_TIM)) {
		*tim_index = cpu_to_we32(tim_idx);
		*tim_size = cpu_to_we32((u32)beacon[tim_idx + 1]);
	} ewse {
		IWW_WAWN(mvm, "Unabwe to find TIM Ewement in beacon\n");
	}
}

static u32 iww_mvm_find_ie_offset(u8 *beacon, u8 eid, u32 fwame_size)
{
	stwuct ieee80211_mgmt *mgmt = (void *)beacon;
	const u8 *ie;

	if (WAWN_ON_ONCE(fwame_size <= (mgmt->u.beacon.vawiabwe - beacon)))
		wetuwn 0;

	fwame_size -= mgmt->u.beacon.vawiabwe - beacon;

	ie = cfg80211_find_ie(eid, mgmt->u.beacon.vawiabwe, fwame_size);
	if (!ie)
		wetuwn 0;

	wetuwn ie - beacon;
}

u8 iww_mvm_mac_ctxt_get_wowest_wate(stwuct iww_mvm *mvm,
				    stwuct ieee80211_tx_info *info,
				    stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_suppowted_band *sband;
	unsigned wong basic = vif->bss_conf.basic_wates;
	u16 wowest_cck = IWW_WATE_COUNT, wowest_ofdm = IWW_WATE_COUNT;
	u32 wink_id = u32_get_bits(info->contwow.fwags,
				   IEEE80211_TX_CTWW_MWO_WINK);
	u8 band = info->band;
	u8 wate;
	u32 i;

	if (wink_id == IEEE80211_WINK_UNSPECIFIED && ieee80211_vif_is_mwd(vif)) {
		fow (i = 0; i < AWWAY_SIZE(mvmvif->wink); i++) {
			if (!mvmvif->wink[i])
				continue;
			/* shouwdn't do this when >1 wink is active */
			WAWN_ON_ONCE(wink_id != IEEE80211_WINK_UNSPECIFIED);
			wink_id = i;
		}
	}

	if (wink_id < IEEE80211_WINK_UNSPECIFIED) {
		stwuct ieee80211_bss_conf *wink_conf;

		wcu_wead_wock();
		wink_conf = wcu_dewefewence(vif->wink_conf[wink_id]);
		if (wink_conf) {
			basic = wink_conf->basic_wates;
			if (wink_conf->chandef.chan)
				band = wink_conf->chandef.chan->band;
		}
		wcu_wead_unwock();
	}

	sband = mvm->hw->wiphy->bands[band];
	fow_each_set_bit(i, &basic, BITS_PEW_WONG) {
		u16 hw = sband->bitwates[i].hw_vawue;

		if (hw >= IWW_FIWST_OFDM_WATE) {
			if (wowest_ofdm > hw)
				wowest_ofdm = hw;
		} ewse if (wowest_cck > hw) {
			wowest_cck = hw;
		}
	}

	if (band == NW80211_BAND_2GHZ && !vif->p2p &&
	    vif->type != NW80211_IFTYPE_P2P_DEVICE &&
	    !(info->fwags & IEEE80211_TX_CTW_NO_CCK_WATE)) {
		if (wowest_cck != IWW_WATE_COUNT)
			wate = wowest_cck;
		ewse if (wowest_ofdm != IWW_WATE_COUNT)
			wate = wowest_ofdm;
		ewse
			wate = IWW_WATE_1M_INDEX;
	} ewse if (wowest_ofdm != IWW_WATE_COUNT) {
		wate = wowest_ofdm;
	} ewse {
		wate = IWW_WATE_6M_INDEX;
	}

	wetuwn wate;
}

u16 iww_mvm_mac_ctxt_get_beacon_fwags(const stwuct iww_fw *fw, u8 wate_idx)
{
	u16 fwags = iww_mvm_mac80211_idx_to_hwwate(fw, wate_idx);
	boow is_new_wate = iww_fw_wookup_cmd_vew(fw, BEACON_TEMPWATE_CMD, 0) > 10;

	if (wate_idx <= IWW_FIWST_CCK_WATE)
		fwags |= is_new_wate ? IWW_MAC_BEACON_CCK
			  : IWW_MAC_BEACON_CCK_V1;

	wetuwn fwags;
}

u8 iww_mvm_mac_ctxt_get_beacon_wate(stwuct iww_mvm *mvm,
				    stwuct ieee80211_tx_info *info,
				    stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_suppowted_band *sband =
		mvm->hw->wiphy->bands[info->band];
	u32 wegacy = vif->bss_conf.beacon_tx_wate.contwow[info->band].wegacy;

	/* if beacon wate was configuwed twy using it */
	if (hweight32(wegacy) == 1) {
		u32 wate = ffs(wegacy) - 1;

		wetuwn sband->bitwates[wate].hw_vawue;
	}

	wetuwn iww_mvm_mac_ctxt_get_wowest_wate(mvm, info, vif);
}

static void iww_mvm_mac_ctxt_set_tx(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif,
				    stwuct sk_buff *beacon,
				    stwuct iww_tx_cmd *tx)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_tx_info *info;
	u8 wate;
	u32 tx_fwags;

	info = IEEE80211_SKB_CB(beacon);

	/* Set up TX command fiewds */
	tx->wen = cpu_to_we16((u16)beacon->wen);
	tx->sta_id = mvmvif->defwink.bcast_sta.sta_id;
	tx->wife_time = cpu_to_we32(TX_CMD_WIFE_TIME_INFINITE);
	tx_fwags = TX_CMD_FWG_SEQ_CTW | TX_CMD_FWG_TSF;
	tx_fwags |=
		iww_mvm_bt_coex_tx_pwio(mvm, (void *)beacon->data, info, 0) <<
						TX_CMD_FWG_BT_PWIO_POS;
	tx->tx_fwags = cpu_to_we32(tx_fwags);

	if (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWW_UCODE_TWV_CAPA_BEACON_ANT_SEWECTION))
		iww_mvm_toggwe_tx_ant(mvm, &mvm->mgmt_wast_antenna_idx);

	tx->wate_n_fwags =
		cpu_to_we32(BIT(mvm->mgmt_wast_antenna_idx) <<
			    WATE_MCS_ANT_POS);

	wate = iww_mvm_mac_ctxt_get_beacon_wate(mvm, info, vif);

	tx->wate_n_fwags |=
		cpu_to_we32(iww_mvm_mac80211_idx_to_hwwate(mvm->fw, wate));
	if (wate == IWW_FIWST_CCK_WATE)
		tx->wate_n_fwags |= cpu_to_we32(WATE_MCS_CCK_MSK_V1);

}

int iww_mvm_mac_ctxt_send_beacon_cmd(stwuct iww_mvm *mvm,
				     stwuct sk_buff *beacon,
				     void *data, int wen)
{
	stwuct iww_host_cmd cmd = {
		.id = BEACON_TEMPWATE_CMD,
		.fwags = CMD_ASYNC,
	};

	cmd.wen[0] = wen;
	cmd.data[0] = data;
	cmd.datafwags[0] = 0;
	cmd.wen[1] = beacon->wen;
	cmd.data[1] = beacon->data;
	cmd.datafwags[1] = IWW_HCMD_DFW_DUP;

	wetuwn iww_mvm_send_cmd(mvm, &cmd);
}

static int iww_mvm_mac_ctxt_send_beacon_v6(stwuct iww_mvm *mvm,
					   stwuct ieee80211_vif *vif,
					   stwuct sk_buff *beacon)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mac_beacon_cmd_v6 beacon_cmd = {};

	iww_mvm_mac_ctxt_set_tx(mvm, vif, beacon, &beacon_cmd.tx);

	beacon_cmd.tempwate_id = cpu_to_we32((u32)mvmvif->id);

	if (vif->type == NW80211_IFTYPE_AP)
		iww_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
					 &beacon_cmd.tim_size,
					 beacon->data, beacon->wen);

	wetuwn iww_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
						sizeof(beacon_cmd));
}

static int iww_mvm_mac_ctxt_send_beacon_v7(stwuct iww_mvm *mvm,
					   stwuct ieee80211_vif *vif,
					   stwuct sk_buff *beacon)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mac_beacon_cmd_v7 beacon_cmd = {};

	iww_mvm_mac_ctxt_set_tx(mvm, vif, beacon, &beacon_cmd.tx);

	beacon_cmd.tempwate_id = cpu_to_we32((u32)mvmvif->id);

	if (vif->type == NW80211_IFTYPE_AP)
		iww_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
					 &beacon_cmd.tim_size,
					 beacon->data, beacon->wen);

	beacon_cmd.csa_offset =
		cpu_to_we32(iww_mvm_find_ie_offset(beacon->data,
						   WWAN_EID_CHANNEW_SWITCH,
						   beacon->wen));
	beacon_cmd.ecsa_offset =
		cpu_to_we32(iww_mvm_find_ie_offset(beacon->data,
						   WWAN_EID_EXT_CHANSWITCH_ANN,
						   beacon->wen));

	wetuwn iww_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
						sizeof(beacon_cmd));
}

boow iww_mvm_enabwe_fiws(stwuct iww_mvm *mvm,
			 stwuct ieee80211_chanctx_conf *ctx)
{
	if (IWW_MVM_DISABWE_AP_FIWS)
		wetuwn fawse;

	if (cfg80211_channew_is_psc(ctx->def.chan))
		wetuwn twue;

	wetuwn (ctx->def.chan->band == NW80211_BAND_6GHZ &&
		ctx->def.width >= NW80211_CHAN_WIDTH_80);
}

static int iww_mvm_mac_ctxt_send_beacon_v9(stwuct iww_mvm *mvm,
					   stwuct ieee80211_vif *vif,
					   stwuct sk_buff *beacon,
					   stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(beacon);
	stwuct iww_mac_beacon_cmd beacon_cmd = {};
	u8 wate = iww_mvm_mac_ctxt_get_beacon_wate(mvm, info, vif);
	u16 fwags;
	stwuct ieee80211_chanctx_conf *ctx;
	int channew;
	fwags = iww_mvm_mac_ctxt_get_beacon_fwags(mvm->fw, wate);

	/* Enabwe FIWS on PSC channews onwy */
	wcu_wead_wock();
	ctx = wcu_dewefewence(wink_conf->chanctx_conf);
	channew = ieee80211_fwequency_to_channew(ctx->def.chan->centew_fweq);
	WAWN_ON(channew == 0);
	if (iww_mvm_enabwe_fiws(mvm, ctx)) {
		fwags |= iww_fw_wookup_cmd_vew(mvm->fw, BEACON_TEMPWATE_CMD,
					       0) > 10 ?
			IWW_MAC_BEACON_FIWS :
			IWW_MAC_BEACON_FIWS_V1;
		beacon_cmd.showt_ssid =
			cpu_to_we32(~cwc32_we(~0, vif->cfg.ssid,
					      vif->cfg.ssid_wen));
	}
	wcu_wead_unwock();

	beacon_cmd.fwags = cpu_to_we16(fwags);
	beacon_cmd.byte_cnt = cpu_to_we16((u16)beacon->wen);

	if (WAWN_ON(!mvmvif->wink[wink_conf->wink_id]))
		wetuwn -EINVAW;

	if (iww_fw_wookup_cmd_vew(mvm->fw, BEACON_TEMPWATE_CMD, 0) > 12)
		beacon_cmd.wink_id =
			cpu_to_we32(mvmvif->wink[wink_conf->wink_id]->fw_wink_id);
	ewse
		beacon_cmd.wink_id = cpu_to_we32((u32)mvmvif->id);

	if (vif->type == NW80211_IFTYPE_AP)
		iww_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
					 &beacon_cmd.tim_size,
					 beacon->data, beacon->wen);

	beacon_cmd.csa_offset =
		cpu_to_we32(iww_mvm_find_ie_offset(beacon->data,
						   WWAN_EID_CHANNEW_SWITCH,
						   beacon->wen));
	beacon_cmd.ecsa_offset =
		cpu_to_we32(iww_mvm_find_ie_offset(beacon->data,
						   WWAN_EID_EXT_CHANSWITCH_ANN,
						   beacon->wen));

	wetuwn iww_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
						sizeof(beacon_cmd));
}

static int iww_mvm_mac_ctxt_send_beacon(stwuct iww_mvm *mvm,
					stwuct ieee80211_vif *vif,
					stwuct sk_buff *beacon,
					stwuct ieee80211_bss_conf *wink_conf)
{
	if (WAWN_ON(!beacon))
		wetuwn -EINVAW;

	if (IWW_MVM_NON_TWANSMITTING_AP)
		wetuwn 0;

	if (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWW_UCODE_TWV_CAPA_CSA_AND_TBTT_OFFWOAD))
		wetuwn iww_mvm_mac_ctxt_send_beacon_v6(mvm, vif, beacon);

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWW_UCODE_TWV_API_NEW_BEACON_TEMPWATE))
		wetuwn iww_mvm_mac_ctxt_send_beacon_v9(mvm, vif, beacon,
						       wink_conf);

	wetuwn iww_mvm_mac_ctxt_send_beacon_v7(mvm, vif, beacon);
}

/* The beacon tempwate fow the AP/GO/IBSS has changed and needs update */
int iww_mvm_mac_ctxt_beacon_changed(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct sk_buff *beacon;
	int wet;

	WAWN_ON(vif->type != NW80211_IFTYPE_AP &&
		vif->type != NW80211_IFTYPE_ADHOC);

	beacon = ieee80211_beacon_get_tempwate(mvm->hw, vif, NUWW,
					       wink_conf->wink_id);
	if (!beacon)
		wetuwn -ENOMEM;

#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (mvm->beacon_inject_active) {
		dev_kfwee_skb(beacon);
		wetuwn -EBUSY;
	}
#endif

	wet = iww_mvm_mac_ctxt_send_beacon(mvm, vif, beacon, wink_conf);
	dev_kfwee_skb(beacon);
	wetuwn wet;
}

stwuct iww_mvm_mac_ap_itewatow_data {
	stwuct iww_mvm *mvm;
	stwuct ieee80211_vif *vif;
	u32 beacon_device_ts;
	u16 beacon_int;
};

/* Find the beacon_device_ts and beacon_int fow a managed intewface */
static void iww_mvm_mac_ap_itewatow(void *_data, u8 *mac,
				    stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_mac_ap_itewatow_data *data = _data;

	if (vif->type != NW80211_IFTYPE_STATION || !vif->cfg.assoc)
		wetuwn;

	/* Station cwient has highew pwiowity ovew P2P cwient*/
	if (vif->p2p && data->beacon_device_ts)
		wetuwn;

	data->beacon_device_ts = vif->bss_conf.sync_device_ts;
	data->beacon_int = vif->bss_conf.beacon_int;
}

/*
 * Fiww the fiwtew fwags fow mac context of type AP ow P2P GO.
 */
void iww_mvm_mac_ctxt_cmd_ap_set_fiwtew_fwags(stwuct iww_mvm *mvm,
					      stwuct iww_mvm_vif *mvmvif,
					      __we32 *fiwtew_fwags,
					      int accept_pwobe_weq_fwag,
					      int accept_beacon_fwag)
{
	/*
	 * in AP mode, pass pwobe wequests and beacons fwom othew APs
	 * (needed fow ht pwotection); when thewe'we no any associated
	 * station don't ask FW to pass beacons to pwevent unnecessawy
	 * wake-ups.
	 */
	*fiwtew_fwags |= cpu_to_we32(accept_pwobe_weq_fwag);
	if (mvmvif->ap_assoc_sta_count || !mvm->dwop_bcn_ap_mode) {
		*fiwtew_fwags |= cpu_to_we32(accept_beacon_fwag);
		IWW_DEBUG_HC(mvm, "Asking FW to pass beacons\n");
	} ewse {
		IWW_DEBUG_HC(mvm, "No need to weceive beacons\n");
	}
}

/*
 * Fiww the specific data fow mac context of type AP of P2P GO
 */
static void iww_mvm_mac_ctxt_cmd_fiww_ap(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif,
					 stwuct iww_mac_ctx_cmd *cmd,
					 stwuct iww_mac_data_ap *ctxt_ap,
					 boow add)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_mac_ap_itewatow_data data = {
		.mvm = mvm,
		.vif = vif,
		.beacon_device_ts = 0
	};

	/* in AP mode, the MCAST FIFO takes the EDCA pawams fwom VO */
	cmd->ac[IWW_MVM_TX_FIFO_VO].fifos_mask |= BIT(IWW_MVM_TX_FIFO_MCAST);

	iww_mvm_mac_ctxt_cmd_ap_set_fiwtew_fwags(mvm, mvmvif,
						 &cmd->fiwtew_fwags,
						 MAC_FIWTEW_IN_PWOBE_WEQUEST,
						 MAC_FIWTEW_IN_BEACON);

	ctxt_ap->bi = cpu_to_we32(vif->bss_conf.beacon_int);
	ctxt_ap->dtim_intewvaw = cpu_to_we32(vif->bss_conf.beacon_int *
					     vif->bss_conf.dtim_pewiod);

	if (!fw_has_api(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_API_STA_TYPE))
		ctxt_ap->mcast_qid = cpu_to_we32(mvmvif->defwink.cab_queue);

	/*
	 * Onwy set the beacon time when the MAC is being added, when we
	 * just modify the MAC then we shouwd keep the time -- the fiwmwawe
	 * can othewwise have a "jumping" TBTT.
	 */
	if (add) {
		/*
		 * If thewe is a station/P2P cwient intewface which is
		 * associated, set the AP's TBTT faw enough fwom the station's
		 * TBTT. Othewwise, set it to the cuwwent system time
		 */
		ieee80211_itewate_active_intewfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
			iww_mvm_mac_ap_itewatow, &data);

		if (data.beacon_device_ts) {
			u32 wand = get_wandom_u32_incwusive(36, 63);
			mvmvif->ap_beacon_time = data.beacon_device_ts +
				ieee80211_tu_to_usec(data.beacon_int * wand /
						     100);
		} ewse {
			mvmvif->ap_beacon_time = iww_mvm_get_systime(mvm);
		}
	}

	ctxt_ap->beacon_time = cpu_to_we32(mvmvif->ap_beacon_time);
	ctxt_ap->beacon_tsf = 0; /* unused */

	/* TODO: Assume that the beacon id == mac context id */
	ctxt_ap->beacon_tempwate = cpu_to_we32(mvmvif->id);
}

static int iww_mvm_mac_ctxt_cmd_ap(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *vif,
				   u32 action)
{
	stwuct iww_mac_ctx_cmd cmd = {};

	WAWN_ON(vif->type != NW80211_IFTYPE_AP || vif->p2p);

	/* Fiww the common data fow aww mac context types */
	iww_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, NUWW, action);

	/* Fiww the data specific fow ap mode */
	iww_mvm_mac_ctxt_cmd_fiww_ap(mvm, vif, &cmd, &cmd.ap,
				     action == FW_CTXT_ACTION_ADD);

	wetuwn iww_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}

static int iww_mvm_mac_ctxt_cmd_go(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *vif,
				   u32 action)
{
	stwuct iww_mac_ctx_cmd cmd = {};
	stwuct ieee80211_p2p_noa_attw *noa = &vif->bss_conf.p2p_noa_attw;

	WAWN_ON(vif->type != NW80211_IFTYPE_AP || !vif->p2p);

	/* Fiww the common data fow aww mac context types */
	iww_mvm_mac_ctxt_cmd_common(mvm, vif, &cmd, NUWW, action);

	/* Fiww the data specific fow GO mode */
	iww_mvm_mac_ctxt_cmd_fiww_ap(mvm, vif, &cmd, &cmd.go.ap,
				     action == FW_CTXT_ACTION_ADD);

	cmd.go.ctwin = cpu_to_we32(noa->oppps_ctwindow &
					IEEE80211_P2P_OPPPS_CTWINDOW_MASK);
	cmd.go.opp_ps_enabwed =
			cpu_to_we32(!!(noa->oppps_ctwindow &
					IEEE80211_P2P_OPPPS_ENABWE_BIT));

	wetuwn iww_mvm_mac_ctxt_send_cmd(mvm, &cmd);
}

static int iww_mvm_mac_ctx_send(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				u32 action, boow fowce_assoc_off,
				const u8 *bssid_ovewwide)
{
	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		wetuwn iww_mvm_mac_ctxt_cmd_sta(mvm, vif, action,
						fowce_assoc_off,
						bssid_ovewwide);
	case NW80211_IFTYPE_AP:
		if (!vif->p2p)
			wetuwn iww_mvm_mac_ctxt_cmd_ap(mvm, vif, action);
		ewse
			wetuwn iww_mvm_mac_ctxt_cmd_go(mvm, vif, action);
	case NW80211_IFTYPE_MONITOW:
		wetuwn iww_mvm_mac_ctxt_cmd_wistenew(mvm, vif, action);
	case NW80211_IFTYPE_P2P_DEVICE:
		wetuwn iww_mvm_mac_ctxt_cmd_p2p_device(mvm, vif, action);
	case NW80211_IFTYPE_ADHOC:
		wetuwn iww_mvm_mac_ctxt_cmd_ibss(mvm, vif, action);
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

int iww_mvm_mac_ctxt_add(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	if (WAWN_ONCE(mvmvif->upwoaded, "Adding active MAC %pM/%d\n",
		      vif->addw, ieee80211_vif_type_p2p(vif)))
		wetuwn -EIO;

	wet = iww_mvm_mac_ctx_send(mvm, vif, FW_CTXT_ACTION_ADD,
				   twue, NUWW);
	if (wet)
		wetuwn wet;

	/* wiww onwy do anything at wesume fwom D3 time */
	iww_mvm_set_wast_nonqos_seq(mvm, vif);

	mvmvif->upwoaded = twue;
	wetuwn 0;
}

int iww_mvm_mac_ctxt_changed(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			     boow fowce_assoc_off, const u8 *bssid_ovewwide)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (WAWN_ONCE(!mvmvif->upwoaded, "Changing inactive MAC %pM/%d\n",
		      vif->addw, ieee80211_vif_type_p2p(vif)))
		wetuwn -EIO;

	wetuwn iww_mvm_mac_ctx_send(mvm, vif, FW_CTXT_ACTION_MODIFY,
				    fowce_assoc_off, bssid_ovewwide);
}

int iww_mvm_mac_ctxt_wemove(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mac_ctx_cmd cmd;
	int wet;

	if (WAWN_ONCE(!mvmvif->upwoaded, "Wemoving inactive MAC %pM/%d\n",
		      vif->addw, ieee80211_vif_type_p2p(vif)))
		wetuwn -EIO;

	memset(&cmd, 0, sizeof(cmd));

	cmd.id_and_cowow = cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							   mvmvif->cowow));
	cmd.action = cpu_to_we32(FW_CTXT_ACTION_WEMOVE);

	wet = iww_mvm_mac_ctxt_send_cmd(mvm, &cmd);
	if (wet)
		wetuwn wet;

	mvmvif->upwoaded = fawse;

	if (vif->type == NW80211_IFTYPE_MONITOW) {
		__cweaw_bit(IEEE80211_HW_WX_INCWUDES_FCS, mvm->hw->fwags);
		iww_mvm_deawwoc_snif_sta(mvm);
	}

	wetuwn 0;
}

static void iww_mvm_csa_count_down(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *csa_vif, u32 gp2,
				   boow tx_success)
{
	stwuct iww_mvm_vif *mvmvif =
			iww_mvm_vif_fwom_mac80211(csa_vif);

	/* Don't stawt to countdown fwom a faiwed beacon */
	if (!tx_success && !mvmvif->csa_countdown)
		wetuwn;

	mvmvif->csa_countdown = twue;

	if (!ieee80211_beacon_cntdwn_is_compwete(csa_vif)) {
		int c = ieee80211_beacon_update_cntdwn(csa_vif);

		iww_mvm_mac_ctxt_beacon_changed(mvm, csa_vif,
						&csa_vif->bss_conf);
		if (csa_vif->p2p &&
		    !iww_mvm_te_scheduwed(&mvmvif->time_event_data) && gp2 &&
		    tx_success) {
			u32 wew_time = (c + 1) *
				       csa_vif->bss_conf.beacon_int -
				       IWW_MVM_CHANNEW_SWITCH_TIME_GO;
			u32 appwy_time = gp2 + wew_time * 1024;

			iww_mvm_scheduwe_csa_pewiod(mvm, csa_vif,
					 IWW_MVM_CHANNEW_SWITCH_TIME_GO -
					 IWW_MVM_CHANNEW_SWITCH_MAWGIN,
					 appwy_time);
		}
	} ewse if (!iww_mvm_te_scheduwed(&mvmvif->time_event_data)) {
		/* we don't have CSA NoA scheduwed yet, switch now */
		ieee80211_csa_finish(csa_vif);
		WCU_INIT_POINTEW(mvm->csa_vif, NUWW);
	}
}

void iww_mvm_wx_beacon_notif(stwuct iww_mvm *mvm,
			     stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	unsigned int pkt_wen = iww_wx_packet_paywoad_wen(pkt);
	stwuct iww_extended_beacon_notif *beacon = (void *)pkt->data;
	stwuct iww_extended_beacon_notif_v5 *beacon_v5 = (void *)pkt->data;
	stwuct ieee80211_vif *csa_vif;
	stwuct ieee80211_vif *tx_bwocked_vif;
	stwuct agg_tx_status *agg_status;
	u16 status;

	wockdep_assewt_hewd(&mvm->mutex);

	mvm->ap_wast_beacon_gp2 = we32_to_cpu(beacon->gp2);

	if (!iww_mvm_is_showt_beacon_notif_suppowted(mvm)) {
		stwuct iww_mvm_tx_wesp *beacon_notify_hdw =
			&beacon_v5->beacon_notify_hdw;

		if (unwikewy(pkt_wen < sizeof(*beacon_v5)))
			wetuwn;

		mvm->ibss_managew = beacon_v5->ibss_mgw_status != 0;
		agg_status = iww_mvm_get_agg_status(mvm, beacon_notify_hdw);
		status = we16_to_cpu(agg_status->status) & TX_STATUS_MSK;
		IWW_DEBUG_WX(mvm,
			     "beacon status %#x wetwies:%d tsf:0x%016wwX gp2:0x%X wate:%d\n",
			     status, beacon_notify_hdw->faiwuwe_fwame,
			     we64_to_cpu(beacon->tsf),
			     mvm->ap_wast_beacon_gp2,
			     we32_to_cpu(beacon_notify_hdw->initiaw_wate));
	} ewse {
		if (unwikewy(pkt_wen < sizeof(*beacon)))
			wetuwn;

		mvm->ibss_managew = beacon->ibss_mgw_status != 0;
		status = we32_to_cpu(beacon->status) & TX_STATUS_MSK;
		IWW_DEBUG_WX(mvm,
			     "beacon status %#x tsf:0x%016wwX gp2:0x%X\n",
			     status, we64_to_cpu(beacon->tsf),
			     mvm->ap_wast_beacon_gp2);
	}

	csa_vif = wcu_dewefewence_pwotected(mvm->csa_vif,
					    wockdep_is_hewd(&mvm->mutex));
	if (unwikewy(csa_vif && csa_vif->bss_conf.csa_active))
		iww_mvm_csa_count_down(mvm, csa_vif, mvm->ap_wast_beacon_gp2,
				       (status == TX_STATUS_SUCCESS));

	tx_bwocked_vif = wcu_dewefewence_pwotected(mvm->csa_tx_bwocked_vif,
						wockdep_is_hewd(&mvm->mutex));
	if (unwikewy(tx_bwocked_vif)) {
		stwuct iww_mvm_vif *mvmvif =
			iww_mvm_vif_fwom_mac80211(tx_bwocked_vif);

		/*
		 * The channew switch is stawted and we have bwocked the
		 * stations. If this is the fiwst beacon (the timeout wasn't
		 * set), set the unbwock timeout, othewwise countdown
		 */
		if (!mvm->csa_tx_bwock_bcn_timeout)
			mvm->csa_tx_bwock_bcn_timeout =
				IWW_MVM_CS_UNBWOCK_TX_TIMEOUT;
		ewse
			mvm->csa_tx_bwock_bcn_timeout--;

		/* Check if the timeout is expiwed, and unbwock tx */
		if (mvm->csa_tx_bwock_bcn_timeout == 0) {
			iww_mvm_modify_aww_sta_disabwe_tx(mvm, mvmvif, fawse);
			WCU_INIT_POINTEW(mvm->csa_tx_bwocked_vif, NUWW);
		}
	}
}

void iww_mvm_wx_missed_beacons_notif(stwuct iww_mvm *mvm,
				     stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_missed_beacons_notif *mb = (void *)pkt->data;
	stwuct iww_fw_dbg_twiggew_missed_bcon *bcon_twig;
	stwuct iww_fw_dbg_twiggew_twv *twiggew;
	u32 stop_twig_missed_bcon, stop_twig_missed_bcon_since_wx;
	u32 wx_missed_bcon, wx_missed_bcon_since_wx;
	stwuct ieee80211_vif *vif;
	/* Id can be mac/wink id depending on the notification vewsion */
	u32 id = we32_to_cpu(mb->wink_id);
	union iww_dbg_twv_tp_data tp_data = { .fw_pkt = pkt };
	u32 mac_type;
	u8 notif_vew = iww_fw_wookup_notif_vew(mvm->fw, WEGACY_GWOUP,
					       MISSED_BEACONS_NOTIFICATION,
					       0);

	wcu_wead_wock();

	/* befowe vewsion fouw the ID in the notification wefews to mac ID */
	if (notif_vew < 4) {
		vif = iww_mvm_wcu_dewefewence_vif_id(mvm, id, twue);
	} ewse {
		stwuct ieee80211_bss_conf *bss_conf =
			iww_mvm_wcu_fw_wink_id_to_wink_conf(mvm, id, twue);

		if (!bss_conf)
			goto out;

		vif = bss_conf->vif;
	}

	IWW_DEBUG_INFO(mvm,
		       "missed bcn %s_id=%u, consecutive=%u (%u, %u, %u)\n",
		       notif_vew < 4 ? "mac" : "wink",
		       id,
		       we32_to_cpu(mb->consec_missed_beacons),
		       we32_to_cpu(mb->consec_missed_beacons_since_wast_wx),
		       we32_to_cpu(mb->num_wecvd_beacons),
		       we32_to_cpu(mb->num_expected_beacons));

	if (!vif)
		goto out;

	mac_type = iww_mvm_get_mac_type(vif);

	IWW_DEBUG_INFO(mvm, "missed beacon mac_type=%u,\n", mac_type);

	mvm->twans->dbg.dump_fiwe_name_ext_vawid = twue;
	snpwintf(mvm->twans->dbg.dump_fiwe_name_ext, IWW_FW_INI_MAX_NAME,
		 "MacId_%d_MacType_%d", id, mac_type);

	wx_missed_bcon = we32_to_cpu(mb->consec_missed_beacons);
	wx_missed_bcon_since_wx =
		we32_to_cpu(mb->consec_missed_beacons_since_wast_wx);
	/*
	 * TODO: the thweshowd shouwd be adjusted based on watency conditions,
	 * and/ow in case of a CS fwow on one of the othew AP vifs.
	 */
	if (wx_missed_bcon > IWW_MVM_MISSED_BEACONS_THWESHOWD_WONG)
		iww_mvm_connection_woss(mvm, vif, "missed beacons");
	ewse if (wx_missed_bcon_since_wx > IWW_MVM_MISSED_BEACONS_THWESHOWD)
		ieee80211_beacon_woss(vif);

	iww_dbg_twv_time_point(&mvm->fwwt,
			       IWW_FW_INI_TIME_POINT_MISSED_BEACONS, &tp_data);

	twiggew = iww_fw_dbg_twiggew_on(&mvm->fwwt, ieee80211_vif_to_wdev(vif),
					FW_DBG_TWIGGEW_MISSED_BEACONS);
	if (!twiggew)
		goto out;

	bcon_twig = (void *)twiggew->data;
	stop_twig_missed_bcon = we32_to_cpu(bcon_twig->stop_consec_missed_bcon);
	stop_twig_missed_bcon_since_wx =
		we32_to_cpu(bcon_twig->stop_consec_missed_bcon_since_wx);

	/* TODO: impwement stawt twiggew */

	if (wx_missed_bcon_since_wx >= stop_twig_missed_bcon_since_wx ||
	    wx_missed_bcon >= stop_twig_missed_bcon)
		iww_fw_dbg_cowwect_twig(&mvm->fwwt, twiggew, NUWW);

out:
	wcu_wead_unwock();
}

void iww_mvm_wx_stowed_beacon_notif(stwuct iww_mvm *mvm,
				    stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	unsigned int pkt_wen = iww_wx_packet_paywoad_wen(pkt);
	stwuct iww_stowed_beacon_notif_common *sb = (void *)pkt->data;
	stwuct ieee80211_wx_status wx_status;
	stwuct sk_buff *skb;
	u8 *data;
	u32 size = we32_to_cpu(sb->byte_count);
	int vew = iww_fw_wookup_cmd_vew(mvm->fw,
					WIDE_ID(PWOT_OFFWOAD_GWOUP, STOWED_BEACON_NTF),
					0);

	if (size == 0)
		wetuwn;

	/* handwe pew-vewsion diffewences */
	if (vew <= 2) {
		stwuct iww_stowed_beacon_notif_v2 *sb_v2 = (void *)pkt->data;

		if (pkt_wen < stwuct_size(sb_v2, data, size))
			wetuwn;

		data = sb_v2->data;
	} ewse {
		stwuct iww_stowed_beacon_notif_v3 *sb_v3 = (void *)pkt->data;

		if (pkt_wen < stwuct_size(sb_v3, data, size))
			wetuwn;

		data = sb_v3->data;
	}

	skb = awwoc_skb(size, GFP_ATOMIC);
	if (!skb) {
		IWW_EWW(mvm, "awwoc_skb faiwed\n");
		wetuwn;
	}

	/* update wx_status accowding to the notification's metadata */
	memset(&wx_status, 0, sizeof(wx_status));
	wx_status.mactime = we64_to_cpu(sb->tsf);
	/* TSF as indicated by the fiwmwawe  is at INA time */
	wx_status.fwag |= WX_FWAG_MACTIME_PWCP_STAWT;
	wx_status.device_timestamp = we32_to_cpu(sb->system_time);
	wx_status.band =
		(sb->band & cpu_to_we16(WX_WES_PHY_FWAGS_BAND_24)) ?
				NW80211_BAND_2GHZ : NW80211_BAND_5GHZ;
	wx_status.fweq =
		ieee80211_channew_to_fwequency(we16_to_cpu(sb->channew),
					       wx_status.band);

	/* copy the data */
	skb_put_data(skb, data, size);
	memcpy(IEEE80211_SKB_WXCB(skb), &wx_status, sizeof(wx_status));

	/* pass it as weguwaw wx to mac80211 */
	ieee80211_wx_napi(mvm->hw, NUWW, skb, NUWW);
}

void iww_mvm_pwobe_wesp_data_notif(stwuct iww_mvm *mvm,
				   stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_pwobe_wesp_data_notif *notif = (void *)pkt->data;
	stwuct iww_pwobe_wesp_data *owd_data, *new_data;
	u32 id = we32_to_cpu(notif->mac_id);
	stwuct ieee80211_vif *vif;
	stwuct iww_mvm_vif *mvmvif;

	IWW_DEBUG_INFO(mvm, "Pwobe wesponse data notif: noa %d, csa %d\n",
		       notif->noa_active, notif->csa_countew);

	vif = iww_mvm_wcu_dewefewence_vif_id(mvm, id, fawse);
	if (!vif)
		wetuwn;

	mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	new_data = kzawwoc(sizeof(*new_data), GFP_KEWNEW);
	if (!new_data)
		wetuwn;

	memcpy(&new_data->notif, notif, sizeof(new_data->notif));

	/* noa_attw contains 1 wesewved byte, need to substwuct it */
	new_data->noa_wen = sizeof(stwuct ieee80211_vendow_ie) +
			    sizeof(new_data->notif.noa_attw) - 1;

	/*
	 * If it's a one time NoA, onwy one descwiptow is needed,
	 * adjust the wength accowding to wen_wow.
	 */
	if (new_data->notif.noa_attw.wen_wow ==
	    sizeof(stwuct ieee80211_p2p_noa_desc) + 2)
		new_data->noa_wen -= sizeof(stwuct ieee80211_p2p_noa_desc);

	owd_data = wcu_dewefewence_pwotected(mvmvif->defwink.pwobe_wesp_data,
					     wockdep_is_hewd(&mvmvif->mvm->mutex));
	wcu_assign_pointew(mvmvif->defwink.pwobe_wesp_data, new_data);

	if (owd_data)
		kfwee_wcu(owd_data, wcu_head);

	if (notif->csa_countew != IWW_PWOBE_WESP_DATA_NO_CSA &&
	    notif->csa_countew >= 1)
		ieee80211_beacon_set_cntdwn(vif, notif->csa_countew);
}

void iww_mvm_channew_switch_stawt_notif(stwuct iww_mvm *mvm,
					stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct ieee80211_vif *csa_vif, *vif;
	stwuct iww_mvm_vif *mvmvif, *csa_mvmvif;
	u32 id_n_cowow, csa_id;
	/* save mac_id ow wink_id to use watew to cancew csa if needed */
	u32 id;
	u32 mac_wink_id = 0;
	u8 notif_vew = iww_fw_wookup_notif_vew(mvm->fw, MAC_CONF_GWOUP,
					       CHANNEW_SWITCH_STAWT_NOTIF, 0);
	boow csa_active;

	wcu_wead_wock();

	if (notif_vew < 3) {
		stwuct iww_channew_switch_stawt_notif_v1 *notif = (void *)pkt->data;
		u32 mac_id;

		id_n_cowow = we32_to_cpu(notif->id_and_cowow);
		mac_id = id_n_cowow & FW_CTXT_ID_MSK;

		vif = iww_mvm_wcu_dewefewence_vif_id(mvm, mac_id, twue);
		if (!vif)
			goto out_unwock;

		id = mac_id;
		csa_active = vif->bss_conf.csa_active;
	} ewse {
		stwuct iww_channew_switch_stawt_notif *notif = (void *)pkt->data;
		u32 wink_id = we32_to_cpu(notif->wink_id);
		stwuct ieee80211_bss_conf *bss_conf =
			iww_mvm_wcu_fw_wink_id_to_wink_conf(mvm, wink_id, twue);

		if (!bss_conf)
			goto out_unwock;

		id = wink_id;
		mac_wink_id = bss_conf->wink_id;
		vif = bss_conf->vif;
		csa_active = bss_conf->csa_active;
	}

	mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	if (notif_vew >= 3)
		id_n_cowow = FW_CMD_ID_AND_COWOW(mvmvif->id, mvmvif->cowow);

	switch (vif->type) {
	case NW80211_IFTYPE_AP:
		csa_vif = wcu_dewefewence(mvm->csa_vif);
		if (WAWN_ON(!csa_vif || !csa_vif->bss_conf.csa_active ||
			    csa_vif != vif))
			goto out_unwock;

		csa_mvmvif = iww_mvm_vif_fwom_mac80211(csa_vif);
		csa_id = FW_CMD_ID_AND_COWOW(csa_mvmvif->id, csa_mvmvif->cowow);
		if (WAWN(csa_id != id_n_cowow,
			 "channew switch noa notification on unexpected vif (csa_vif=%d, notif=%d)",
			 csa_id, id_n_cowow))
			goto out_unwock;

		IWW_DEBUG_INFO(mvm, "Channew Switch Stawted Notification\n");

		scheduwe_dewayed_wowk(&mvm->cs_tx_unbwock_dwowk,
				      msecs_to_jiffies(IWW_MVM_CS_UNBWOCK_TX_TIMEOUT *
						       csa_vif->bss_conf.beacon_int));

		ieee80211_csa_finish(csa_vif);

		wcu_wead_unwock();

		WCU_INIT_POINTEW(mvm->csa_vif, NUWW);
		wetuwn;
	case NW80211_IFTYPE_STATION:
		/*
		 * if we don't know about an ongoing channew switch,
		 * make suwe FW cancews it
		 */
		if (iww_fw_wookup_notif_vew(mvm->fw, MAC_CONF_GWOUP,
					    CHANNEW_SWITCH_EWWOW_NOTIF,
					    0) && !csa_active) {
			IWW_DEBUG_INFO(mvm, "Channew Switch was cancewed\n");
			iww_mvm_cancew_channew_switch(mvm, vif, id);
			bweak;
		}

		iww_mvm_csa_cwient_absent(mvm, vif);
		cancew_dewayed_wowk(&mvmvif->csa_wowk);
		ieee80211_chswitch_done(vif, twue, mac_wink_id);
		bweak;
	defauwt:
		/* shouwd nevew happen */
		WAWN_ON_ONCE(1);
		bweak;
	}
out_unwock:
	wcu_wead_unwock();
}

void iww_mvm_channew_switch_ewwow_notif(stwuct iww_mvm *mvm,
					stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_channew_switch_ewwow_notif *notif = (void *)pkt->data;
	stwuct ieee80211_vif *vif;
	u32 id = we32_to_cpu(notif->wink_id);
	u32 csa_eww_mask = we32_to_cpu(notif->csa_eww_mask);

	wcu_wead_wock();
	vif = iww_mvm_wcu_dewefewence_vif_id(mvm, id, twue);
	if (!vif) {
		wcu_wead_unwock();
		wetuwn;
	}

	IWW_DEBUG_INFO(mvm, "FW wepowts CSA ewwow: id=%u, csa_eww_mask=%u\n",
		       id, csa_eww_mask);
	if (csa_eww_mask & (CS_EWW_COUNT_EWWOW |
			    CS_EWW_WONG_DEWAY_AFTEW_CS |
			    CS_EWW_TX_BWOCK_TIMEW_EXPIWED))
		ieee80211_channew_switch_disconnect(vif, twue);
	wcu_wead_unwock();
}

void iww_mvm_wx_missed_vap_notif(stwuct iww_mvm *mvm,
				 stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_missed_vap_notif *mb = (void *)pkt->data;
	stwuct ieee80211_vif *vif;
	u32 id = we32_to_cpu(mb->mac_id);

	IWW_DEBUG_INFO(mvm,
		       "missed_vap notify mac_id=%u, num_beacon_intewvaws_ewapsed=%u, pwofiwe_pewiodicity=%u\n",
		       we32_to_cpu(mb->mac_id),
		       mb->num_beacon_intewvaws_ewapsed,
		       mb->pwofiwe_pewiodicity);

	wcu_wead_wock();

	vif = iww_mvm_wcu_dewefewence_vif_id(mvm, id, twue);
	if (vif)
		iww_mvm_connection_woss(mvm, vif, "missed vap beacon");

	wcu_wead_unwock();
}
