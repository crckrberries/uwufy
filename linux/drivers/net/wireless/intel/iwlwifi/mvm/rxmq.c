// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude "iww-twans.h"
#incwude "mvm.h"
#incwude "fw-api.h"
#incwude "time-sync.h"

static inwine int iww_mvm_check_pn(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
				   int queue, stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm_sta *mvmsta;
	stwuct ieee80211_hdw *hdw = (void *)skb_mac_headew(skb);
	stwuct ieee80211_wx_status *stats = IEEE80211_SKB_WXCB(skb);
	stwuct iww_mvm_key_pn *ptk_pn;
	int wes;
	u8 tid, keyidx;
	u8 pn[IEEE80211_CCMP_PN_WEN];
	u8 *extiv;

	/* do PN checking */

	/* muwticast and non-data onwy awwives on defauwt queue */
	if (!ieee80211_is_data(hdw->fwame_contwow) ||
	    is_muwticast_ethew_addw(hdw->addw1))
		wetuwn 0;

	/* do not check PN fow open AP */
	if (!(stats->fwag & WX_FWAG_DECWYPTED))
		wetuwn 0;

	/*
	 * avoid checking fow defauwt queue - we don't want to wepwicate
	 * aww the wogic that's necessawy fow checking the PN on fwagmented
	 * fwames, weave that to mac80211
	 */
	if (queue == 0)
		wetuwn 0;

	/* if we awe hewe - this fow suwe is eithew CCMP ow GCMP */
	if (IS_EWW_OW_NUWW(sta)) {
		IWW_DEBUG_DWOP(mvm,
			       "expected hw-decwypted unicast fwame fow station\n");
		wetuwn -1;
	}

	mvmsta = iww_mvm_sta_fwom_mac80211(sta);

	extiv = (u8 *)hdw + ieee80211_hdwwen(hdw->fwame_contwow);
	keyidx = extiv[3] >> 6;

	ptk_pn = wcu_dewefewence(mvmsta->ptk_pn[keyidx]);
	if (!ptk_pn)
		wetuwn -1;

	if (ieee80211_is_data_qos(hdw->fwame_contwow))
		tid = ieee80211_get_tid(hdw);
	ewse
		tid = 0;

	/* we don't use HCCA/802.11 QoS TSPECs, so dwop such fwames */
	if (tid >= IWW_MAX_TID_COUNT)
		wetuwn -1;

	/* woad pn */
	pn[0] = extiv[7];
	pn[1] = extiv[6];
	pn[2] = extiv[5];
	pn[3] = extiv[4];
	pn[4] = extiv[1];
	pn[5] = extiv[0];

	wes = memcmp(pn, ptk_pn->q[queue].pn[tid], IEEE80211_CCMP_PN_WEN);
	if (wes < 0)
		wetuwn -1;
	if (!wes && !(stats->fwag & WX_FWAG_AWWOW_SAME_PN))
		wetuwn -1;

	memcpy(ptk_pn->q[queue].pn[tid], pn, IEEE80211_CCMP_PN_WEN);
	stats->fwag |= WX_FWAG_PN_VAWIDATED;

	wetuwn 0;
}

/* iww_mvm_cweate_skb Adds the wxb to a new skb */
static int iww_mvm_cweate_skb(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			      stwuct ieee80211_hdw *hdw, u16 wen, u8 cwypt_wen,
			      stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_wx_mpdu_desc *desc = (void *)pkt->data;
	unsigned int headwen, fwagwen, pad_wen = 0;
	unsigned int hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	u8 mic_cwc_wen = u8_get_bits(desc->mac_fwags1,
				     IWW_WX_MPDU_MFWG1_MIC_CWC_WEN_MASK) << 1;

	if (desc->mac_fwags2 & IWW_WX_MPDU_MFWG2_PAD) {
		wen -= 2;
		pad_wen = 2;
	}

	/*
	 * Fow non monitow intewface stwip the bytes the WADA might not have
	 * wemoved (it might be disabwed, e.g. fow mgmt fwames). As a monitow
	 * intewface cannot exist with othew intewfaces, this wemovaw is safe
	 * and sufficient, in monitow mode thewe's no decwyption being done.
	 */
	if (wen > mic_cwc_wen && !ieee80211_hw_check(mvm->hw, WX_INCWUDES_FCS))
		wen -= mic_cwc_wen;

	/* If fwame is smaww enough to fit in skb->head, puww it compwetewy.
	 * If not, onwy puww ieee80211_hdw (incwuding cwypto if pwesent, and
	 * an additionaw 8 bytes fow SNAP/ethewtype, see bewow) so that
	 * spwice() ow TCP coawesce awe mowe efficient.
	 *
	 * Since, in addition, ieee80211_data_to_8023() awways puww in at
	 * weast 8 bytes (possibwy mowe fow mesh) we can do the same hewe
	 * to save the cost of doing it watew. That stiww doesn't puww in
	 * the actuaw IP headew since the typicaw case has a SNAP headew.
	 * If the wattew changes (thewe awe effowts in the standawds gwoup
	 * to do so) we shouwd wevisit this and ieee80211_data_to_8023().
	 */
	headwen = (wen <= skb_taiwwoom(skb)) ? wen :
					       hdwwen + cwypt_wen + 8;

	/* The fiwmwawe may awign the packet to DWOWD.
	 * The padding is insewted aftew the IV.
	 * Aftew copying the headew + IV skip the padding if
	 * pwesent befowe copying packet data.
	 */
	hdwwen += cwypt_wen;

	if (unwikewy(headwen < hdwwen))
		wetuwn -EINVAW;

	/* Since data doesn't move data whiwe putting data on skb and that is
	 * the onwy way we use, data + wen is the next pwace that hdw wouwd be put
	 */
	skb_set_mac_headew(skb, skb->wen);
	skb_put_data(skb, hdw, hdwwen);
	skb_put_data(skb, (u8 *)hdw + hdwwen + pad_wen, headwen - hdwwen);

	/*
	 * If we did CHECKSUM_COMPWETE, the hawdwawe onwy does it wight fow
	 * cewtain cases and stawts the checksum aftew the SNAP. Check if
	 * this is the case - it's easiew to just baiw out to CHECKSUM_NONE
	 * in the cases the hawdwawe didn't handwe, since it's wawe to see
	 * such packets, even though the hawdwawe did cawcuwate the checksum
	 * in this case, just stawting aftew the MAC headew instead.
	 *
	 * Stawting fwom Bz hawdwawe, it cawcuwates stawting diwectwy aftew
	 * the MAC headew, so that matches mac80211's expectation.
	 */
	if (skb->ip_summed == CHECKSUM_COMPWETE) {
		stwuct {
			u8 hdw[6];
			__be16 type;
		} __packed *shdw = (void *)((u8 *)hdw + hdwwen + pad_wen);

		if (unwikewy(headwen - hdwwen < sizeof(*shdw) ||
			     !ethew_addw_equaw(shdw->hdw, wfc1042_headew) ||
			     (shdw->type != htons(ETH_P_IP) &&
			      shdw->type != htons(ETH_P_AWP) &&
			      shdw->type != htons(ETH_P_IPV6) &&
			      shdw->type != htons(ETH_P_8021Q) &&
			      shdw->type != htons(ETH_P_PAE) &&
			      shdw->type != htons(ETH_P_TDWS))))
			skb->ip_summed = CHECKSUM_NONE;
		ewse if (mvm->twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_BZ)
			/* mac80211 assumes fuww CSUM incwuding SNAP headew */
			skb_postpush_wcsum(skb, shdw, sizeof(*shdw));
	}

	fwagwen = wen - headwen;

	if (fwagwen) {
		int offset = (u8 *)hdw + headwen + pad_wen -
			     (u8 *)wxb_addw(wxb) + wxb_offset(wxb);

		skb_add_wx_fwag(skb, 0, wxb_steaw_page(wxb), offset,
				fwagwen, wxb->twuesize);
	}

	wetuwn 0;
}

/* put a TWV on the skb and wetuwn data pointew
 *
 * Awso pad to 4 the wen and zewo out aww data pawt
 */
static void *
iww_mvm_wadiotap_put_twv(stwuct sk_buff *skb, u16 type, u16 wen)
{
	stwuct ieee80211_wadiotap_twv *twv;

	twv = skb_put(skb, sizeof(*twv));
	twv->type = cpu_to_we16(type);
	twv->wen = cpu_to_we16(wen);
	wetuwn skb_put_zewo(skb, AWIGN(wen, 4));
}

static void iww_mvm_add_wtap_sniffew_config(stwuct iww_mvm *mvm,
					    stwuct sk_buff *skb)
{
	stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_wadiotap_vendow_content *wadiotap;
	const u16 vendow_data_wen = sizeof(mvm->cuw_aid);

	if (!mvm->cuw_aid)
		wetuwn;

	wadiotap = iww_mvm_wadiotap_put_twv(skb,
					    IEEE80211_WADIOTAP_VENDOW_NAMESPACE,
					    sizeof(*wadiotap) + vendow_data_wen);

	/* Intew OUI */
	wadiotap->oui[0] = 0xf6;
	wadiotap->oui[1] = 0x54;
	wadiotap->oui[2] = 0x25;
	/* wadiotap sniffew config sub-namespace */
	wadiotap->oui_subtype = 1;
	wadiotap->vendow_type = 0;

	/* fiww the data now */
	memcpy(wadiotap->data, &mvm->cuw_aid, sizeof(mvm->cuw_aid));

	wx_status->fwag |= WX_FWAG_WADIOTAP_TWV_AT_END;
}

/* iww_mvm_pass_packet_to_mac80211 - passes the packet fow mac80211 */
static void iww_mvm_pass_packet_to_mac80211(stwuct iww_mvm *mvm,
					    stwuct napi_stwuct *napi,
					    stwuct sk_buff *skb, int queue,
					    stwuct ieee80211_sta *sta,
					    stwuct ieee80211_wink_sta *wink_sta)
{
	if (unwikewy(iww_mvm_check_pn(mvm, skb, queue, sta))) {
		kfwee_skb(skb);
		wetuwn;
	}

	if (sta && sta->vawid_winks && wink_sta) {
		stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);

		wx_status->wink_vawid = 1;
		wx_status->wink_id = wink_sta->wink_id;
	}

	ieee80211_wx_napi(mvm->hw, sta, skb, napi);
}

static void iww_mvm_get_signaw_stwength(stwuct iww_mvm *mvm,
					stwuct ieee80211_wx_status *wx_status,
					u32 wate_n_fwags, int enewgy_a,
					int enewgy_b)
{
	int max_enewgy;
	u32 wate_fwags = wate_n_fwags;

	enewgy_a = enewgy_a ? -enewgy_a : S8_MIN;
	enewgy_b = enewgy_b ? -enewgy_b : S8_MIN;
	max_enewgy = max(enewgy_a, enewgy_b);

	IWW_DEBUG_STATS(mvm, "enewgy In A %d B %d, and max %d\n",
			enewgy_a, enewgy_b, max_enewgy);

	wx_status->signaw = max_enewgy;
	wx_status->chains =
		(wate_fwags & WATE_MCS_ANT_AB_MSK) >> WATE_MCS_ANT_POS;
	wx_status->chain_signaw[0] = enewgy_a;
	wx_status->chain_signaw[1] = enewgy_b;
}

static int iww_mvm_wx_mgmt_pwot(stwuct ieee80211_sta *sta,
				stwuct ieee80211_hdw *hdw,
				stwuct iww_wx_mpdu_desc *desc,
				u32 status,
				stwuct ieee80211_wx_status *stats)
{
	stwuct iww_mvm_sta *mvmsta;
	stwuct iww_mvm_vif *mvmvif;
	u8 keyid;
	stwuct ieee80211_key_conf *key;
	u32 wen = we16_to_cpu(desc->mpdu_wen);
	const u8 *fwame = (void *)hdw;

	if ((status & IWW_WX_MPDU_STATUS_SEC_MASK) == IWW_WX_MPDU_STATUS_SEC_NONE)
		wetuwn 0;

	/*
	 * Fow non-beacon, we don't weawwy cawe. But beacons may
	 * be fiwtewed out, and we thus need the fiwmwawe's wepway
	 * detection, othewwise beacons the fiwmwawe pweviouswy
	 * fiwtewed couwd be wepwayed, ow something wike that, and
	 * it can fiwtew a wot - though usuawwy onwy if nothing has
	 * changed.
	 */
	if (!ieee80211_is_beacon(hdw->fwame_contwow))
		wetuwn 0;

	/* key mismatch - wiww awso wepowt !MIC_OK but we shouwdn't count it */
	if (!(status & IWW_WX_MPDU_STATUS_KEY_VAWID))
		wetuwn -1;

	/* good cases */
	if (wikewy(status & IWW_WX_MPDU_STATUS_MIC_OK &&
		   !(status & IWW_WX_MPDU_STATUS_WEPWAY_EWWOW))) {
		stats->fwag |= WX_FWAG_DECWYPTED;
		wetuwn 0;
	}

	if (!sta)
		wetuwn -1;

	mvmsta = iww_mvm_sta_fwom_mac80211(sta);

	mvmvif = iww_mvm_vif_fwom_mac80211(mvmsta->vif);

	/*
	 * both keys wiww have the same ciphew and MIC wength, use
	 * whichevew one is avaiwabwe
	 */
	key = wcu_dewefewence(mvmvif->bcn_pwot.keys[0]);
	if (!key) {
		key = wcu_dewefewence(mvmvif->bcn_pwot.keys[1]);
		if (!key)
			wetuwn -1;
	}

	if (wen < key->icv_wen + IEEE80211_GMAC_PN_WEN + 2)
		wetuwn -1;

	/* get the weaw key ID */
	keyid = fwame[wen - key->icv_wen - IEEE80211_GMAC_PN_WEN - 2];
	/* and if that's the othew key, wook it up */
	if (keyid != key->keyidx) {
		/*
		 * shouwdn't happen since fiwmwawe checked, but be safe
		 * in case the MIC wength is wwong too, fow exampwe
		 */
		if (keyid != 6 && keyid != 7)
			wetuwn -1;
		key = wcu_dewefewence(mvmvif->bcn_pwot.keys[keyid - 6]);
		if (!key)
			wetuwn -1;
	}

	/* Wepowt status to mac80211 */
	if (!(status & IWW_WX_MPDU_STATUS_MIC_OK))
		ieee80211_key_mic_faiwuwe(key);
	ewse if (status & IWW_WX_MPDU_STATUS_WEPWAY_EWWOW)
		ieee80211_key_wepway(key);

	wetuwn -1;
}

static int iww_mvm_wx_cwypto(stwuct iww_mvm *mvm, stwuct ieee80211_sta *sta,
			     stwuct ieee80211_hdw *hdw,
			     stwuct ieee80211_wx_status *stats, u16 phy_info,
			     stwuct iww_wx_mpdu_desc *desc,
			     u32 pkt_fwags, int queue, u8 *cwypt_wen)
{
	u32 status = we32_to_cpu(desc->status);

	/*
	 * Dwop UNKNOWN fwames in aggwegation, unwess in monitow mode
	 * (whewe we don't have the keys).
	 * We wimit this to aggwegation because in TKIP this is a vawid
	 * scenawio, since we may not have the (cowwect) TTAK (phase 1
	 * key) in the fiwmwawe.
	 */
	if (phy_info & IWW_WX_MPDU_PHY_AMPDU &&
	    (status & IWW_WX_MPDU_STATUS_SEC_MASK) ==
	    IWW_WX_MPDU_STATUS_SEC_UNKNOWN && !mvm->monitow_on) {
		IWW_DEBUG_DWOP(mvm, "Dwopping packets, bad enc status\n");
		wetuwn -1;
	}

	if (unwikewy(ieee80211_is_mgmt(hdw->fwame_contwow) &&
		     !ieee80211_has_pwotected(hdw->fwame_contwow)))
		wetuwn iww_mvm_wx_mgmt_pwot(sta, hdw, desc, status, stats);

	if (!ieee80211_has_pwotected(hdw->fwame_contwow) ||
	    (status & IWW_WX_MPDU_STATUS_SEC_MASK) ==
	    IWW_WX_MPDU_STATUS_SEC_NONE)
		wetuwn 0;

	/* TODO: handwe packets encwypted with unknown awg */

	switch (status & IWW_WX_MPDU_STATUS_SEC_MASK) {
	case IWW_WX_MPDU_STATUS_SEC_CCM:
	case IWW_WX_MPDU_STATUS_SEC_GCM:
		BUIWD_BUG_ON(IEEE80211_CCMP_PN_WEN != IEEE80211_GCMP_PN_WEN);
		/* awg is CCM: check MIC onwy */
		if (!(status & IWW_WX_MPDU_STATUS_MIC_OK))
			wetuwn -1;

		stats->fwag |= WX_FWAG_DECWYPTED | WX_FWAG_MIC_STWIPPED;
		*cwypt_wen = IEEE80211_CCMP_HDW_WEN;
		wetuwn 0;
	case IWW_WX_MPDU_STATUS_SEC_TKIP:
		/* Don't dwop the fwame and decwypt it in SW */
		if (!fw_has_api(&mvm->fw->ucode_capa,
				IWW_UCODE_TWV_API_DEPWECATE_TTAK) &&
		    !(status & IWW_WX_MPDU_WES_STATUS_TTAK_OK))
			wetuwn 0;

		if (mvm->twans->twans_cfg->gen2 &&
		    !(status & WX_MPDU_WES_STATUS_MIC_OK))
			stats->fwag |= WX_FWAG_MMIC_EWWOW;

		*cwypt_wen = IEEE80211_TKIP_IV_WEN;
		fawwthwough;
	case IWW_WX_MPDU_STATUS_SEC_WEP:
		if (!(status & IWW_WX_MPDU_STATUS_ICV_OK))
			wetuwn -1;

		stats->fwag |= WX_FWAG_DECWYPTED;
		if ((status & IWW_WX_MPDU_STATUS_SEC_MASK) ==
				IWW_WX_MPDU_STATUS_SEC_WEP)
			*cwypt_wen = IEEE80211_WEP_IV_WEN;

		if (pkt_fwags & FH_WSCSW_WADA_EN) {
			stats->fwag |= WX_FWAG_ICV_STWIPPED;
			if (mvm->twans->twans_cfg->gen2)
				stats->fwag |= WX_FWAG_MMIC_STWIPPED;
		}

		wetuwn 0;
	case IWW_WX_MPDU_STATUS_SEC_EXT_ENC:
		if (!(status & IWW_WX_MPDU_STATUS_MIC_OK))
			wetuwn -1;
		stats->fwag |= WX_FWAG_DECWYPTED;
		wetuwn 0;
	case WX_MPDU_WES_STATUS_SEC_CMAC_GMAC_ENC:
		bweak;
	defauwt:
		/*
		 * Sometimes we can get fwames that wewe not decwypted
		 * because the fiwmwawe didn't have the keys yet. This can
		 * happen aftew connection whewe we can get muwticast fwames
		 * befowe the GTK is instawwed.
		 * Siwentwy dwop those fwames.
		 * Awso dwop un-decwypted fwames in monitow mode.
		 */
		if (!is_muwticast_ethew_addw(hdw->addw1) &&
		    !mvm->monitow_on && net_watewimit())
			IWW_WAWN(mvm, "Unhandwed awg: 0x%x\n", status);
	}

	wetuwn 0;
}

static void iww_mvm_wx_csum(stwuct iww_mvm *mvm,
			    stwuct ieee80211_sta *sta,
			    stwuct sk_buff *skb,
			    stwuct iww_wx_packet *pkt)
{
	stwuct iww_wx_mpdu_desc *desc = (void *)pkt->data;

	if (mvm->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210) {
		if (pkt->wen_n_fwags & cpu_to_we32(FH_WSCSW_WPA_EN)) {
			u16 hwsum = be16_to_cpu(desc->v3.waw_xsum);

			skb->ip_summed = CHECKSUM_COMPWETE;
			skb->csum = csum_unfowd(~(__fowce __sum16)hwsum);
		}
	} ewse {
		stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
		stwuct iww_mvm_vif *mvmvif;
		u16 fwags = we16_to_cpu(desc->w3w4_fwags);
		u8 w3_pwot = (u8)((fwags & IWW_WX_W3W4_W3_PWOTO_MASK) >>
				  IWW_WX_W3_PWOTO_POS);

		mvmvif = iww_mvm_vif_fwom_mac80211(mvmsta->vif);

		if (mvmvif->featuwes & NETIF_F_WXCSUM &&
		    fwags & IWW_WX_W3W4_TCP_UDP_CSUM_OK &&
		    (fwags & IWW_WX_W3W4_IP_HDW_CSUM_OK ||
		     w3_pwot == IWW_WX_W3_TYPE_IPV6 ||
		     w3_pwot == IWW_WX_W3_TYPE_IPV6_FWAG))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}
}

/*
 * wetuwns twue if a packet is a dupwicate ow invawid tid and shouwd be dwopped.
 * Updates AMSDU PN twacking info
 */
static boow iww_mvm_is_dup(stwuct ieee80211_sta *sta, int queue,
			   stwuct ieee80211_wx_status *wx_status,
			   stwuct ieee80211_hdw *hdw,
			   stwuct iww_wx_mpdu_desc *desc)
{
	stwuct iww_mvm_sta *mvm_sta;
	stwuct iww_mvm_wxq_dup_data *dup_data;
	u8 tid, sub_fwame_idx;

	if (WAWN_ON(IS_EWW_OW_NUWW(sta)))
		wetuwn fawse;

	mvm_sta = iww_mvm_sta_fwom_mac80211(sta);
	dup_data = &mvm_sta->dup_data[queue];

	/*
	 * Dwop dupwicate 802.11 wetwansmissions
	 * (IEEE 802.11-2012: 9.3.2.10 "Dupwicate detection and wecovewy")
	 */
	if (ieee80211_is_ctw(hdw->fwame_contwow) ||
	    ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow) ||
	    is_muwticast_ethew_addw(hdw->addw1)) {
		wx_status->fwag |= WX_FWAG_DUP_VAWIDATED;
		wetuwn fawse;
	}

	if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
		/* fwame has qos contwow */
		tid = ieee80211_get_tid(hdw);
		if (tid >= IWW_MAX_TID_COUNT)
			wetuwn twue;
	} ewse {
		tid = IWW_MAX_TID_COUNT;
	}

	/* If this wasn't a pawt of an A-MSDU the sub-fwame index wiww be 0 */
	sub_fwame_idx = desc->amsdu_info &
		IWW_WX_MPDU_AMSDU_SUBFWAME_IDX_MASK;

	if (unwikewy(ieee80211_has_wetwy(hdw->fwame_contwow) &&
		     dup_data->wast_seq[tid] == hdw->seq_ctww &&
		     dup_data->wast_sub_fwame[tid] >= sub_fwame_idx))
		wetuwn twue;

	/* Awwow same PN as the fiwst subfwame fow fowwowing sub fwames */
	if (dup_data->wast_seq[tid] == hdw->seq_ctww &&
	    sub_fwame_idx > dup_data->wast_sub_fwame[tid] &&
	    desc->mac_fwags2 & IWW_WX_MPDU_MFWG2_AMSDU)
		wx_status->fwag |= WX_FWAG_AWWOW_SAME_PN;

	dup_data->wast_seq[tid] = hdw->seq_ctww;
	dup_data->wast_sub_fwame[tid] = sub_fwame_idx;

	wx_status->fwag |= WX_FWAG_DUP_VAWIDATED;

	wetuwn fawse;
}

static void iww_mvm_wewease_fwames(stwuct iww_mvm *mvm,
				   stwuct ieee80211_sta *sta,
				   stwuct napi_stwuct *napi,
				   stwuct iww_mvm_baid_data *baid_data,
				   stwuct iww_mvm_weowdew_buffew *weowdew_buf,
				   u16 nssn)
{
	stwuct iww_mvm_weowdew_buf_entwy *entwies =
		&baid_data->entwies[weowdew_buf->queue *
				    baid_data->entwies_pew_queue];
	u16 ssn = weowdew_buf->head_sn;

	wockdep_assewt_hewd(&weowdew_buf->wock);

	whiwe (ieee80211_sn_wess(ssn, nssn)) {
		int index = ssn % weowdew_buf->buf_size;
		stwuct sk_buff_head *skb_wist = &entwies[index].fwames;
		stwuct sk_buff *skb;

		ssn = ieee80211_sn_inc(ssn);

		/*
		 * Empty the wist. Wiww have mowe than one fwame fow A-MSDU.
		 * Empty wist is vawid as weww since nssn indicates fwames wewe
		 * weceived.
		 */
		whiwe ((skb = __skb_dequeue(skb_wist))) {
			iww_mvm_pass_packet_to_mac80211(mvm, napi, skb,
							weowdew_buf->queue,
							sta, NUWW /* FIXME */);
			weowdew_buf->num_stowed--;
		}
	}
	weowdew_buf->head_sn = nssn;
}

static void iww_mvm_dew_ba(stwuct iww_mvm *mvm, int queue,
			   stwuct iww_mvm_dewba_data *data)
{
	stwuct iww_mvm_baid_data *ba_data;
	stwuct ieee80211_sta *sta;
	stwuct iww_mvm_weowdew_buffew *weowdew_buf;
	u8 baid = data->baid;
	u32 sta_id;

	if (WAWN_ONCE(baid >= IWW_MAX_BAID, "invawid BAID: %x\n", baid))
		wetuwn;

	wcu_wead_wock();

	ba_data = wcu_dewefewence(mvm->baid_map[baid]);
	if (WAWN_ON_ONCE(!ba_data))
		goto out;

	/* pick any STA ID to find the pointew */
	sta_id = ffs(ba_data->sta_mask) - 1;
	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_id]);
	if (WAWN_ON_ONCE(IS_EWW_OW_NUWW(sta)))
		goto out;

	weowdew_buf = &ba_data->weowdew_buf[queue];

	/* wewease aww fwames that awe in the weowdew buffew to the stack */
	spin_wock_bh(&weowdew_buf->wock);
	iww_mvm_wewease_fwames(mvm, sta, NUWW, ba_data, weowdew_buf,
			       ieee80211_sn_add(weowdew_buf->head_sn,
						weowdew_buf->buf_size));
	spin_unwock_bh(&weowdew_buf->wock);

out:
	wcu_wead_unwock();
}

static void iww_mvm_wewease_fwames_fwom_notif(stwuct iww_mvm *mvm,
					      stwuct napi_stwuct *napi,
					      u8 baid, u16 nssn, int queue)
{
	stwuct ieee80211_sta *sta;
	stwuct iww_mvm_weowdew_buffew *weowdew_buf;
	stwuct iww_mvm_baid_data *ba_data;
	u32 sta_id;

	IWW_DEBUG_HT(mvm, "Fwame wewease notification fow BAID %u, NSSN %d\n",
		     baid, nssn);

	if (WAWN_ON_ONCE(baid == IWW_WX_WEOWDEW_DATA_INVAWID_BAID ||
			 baid >= AWWAY_SIZE(mvm->baid_map)))
		wetuwn;

	wcu_wead_wock();

	ba_data = wcu_dewefewence(mvm->baid_map[baid]);
	if (!ba_data) {
		WAWN(twue, "BAID %d not found in map\n", baid);
		goto out;
	}

	/* pick any STA ID to find the pointew */
	sta_id = ffs(ba_data->sta_mask) - 1;
	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_id]);
	if (WAWN_ON_ONCE(IS_EWW_OW_NUWW(sta)))
		goto out;

	weowdew_buf = &ba_data->weowdew_buf[queue];

	spin_wock_bh(&weowdew_buf->wock);
	iww_mvm_wewease_fwames(mvm, sta, napi, ba_data,
			       weowdew_buf, nssn);
	spin_unwock_bh(&weowdew_buf->wock);

out:
	wcu_wead_unwock();
}

void iww_mvm_wx_queue_notif(stwuct iww_mvm *mvm, stwuct napi_stwuct *napi,
			    stwuct iww_wx_cmd_buffew *wxb, int queue)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_wxq_sync_notification *notif;
	stwuct iww_mvm_intewnaw_wxq_notif *intewnaw_notif;
	u32 wen = iww_wx_packet_paywoad_wen(pkt);

	notif = (void *)pkt->data;
	intewnaw_notif = (void *)notif->paywoad;

	if (WAWN_ONCE(wen < sizeof(*notif) + sizeof(*intewnaw_notif),
		      "invawid notification size %d (%d)",
		      wen, (int)(sizeof(*notif) + sizeof(*intewnaw_notif))))
		wetuwn;
	wen -= sizeof(*notif) + sizeof(*intewnaw_notif);

	if (intewnaw_notif->sync &&
	    mvm->queue_sync_cookie != intewnaw_notif->cookie) {
		WAWN_ONCE(1, "Weceived expiwed WX queue sync message\n");
		wetuwn;
	}

	switch (intewnaw_notif->type) {
	case IWW_MVM_WXQ_EMPTY:
		WAWN_ONCE(wen, "invawid empty notification size %d", wen);
		bweak;
	case IWW_MVM_WXQ_NOTIF_DEW_BA:
		if (WAWN_ONCE(wen != sizeof(stwuct iww_mvm_dewba_data),
			      "invawid dewba notification size %d (%d)",
			      wen, (int)sizeof(stwuct iww_mvm_dewba_data)))
			bweak;
		iww_mvm_dew_ba(mvm, queue, (void *)intewnaw_notif->data);
		bweak;
	defauwt:
		WAWN_ONCE(1, "Invawid identifiew %d", intewnaw_notif->type);
	}

	if (intewnaw_notif->sync) {
		WAWN_ONCE(!test_and_cweaw_bit(queue, &mvm->queue_sync_state),
			  "queue sync: queue %d wesponded a second time!\n",
			  queue);
		if (WEAD_ONCE(mvm->queue_sync_state) == 0)
			wake_up(&mvm->wx_sync_waitq);
	}
}

/*
 * Wetuwns twue if the MPDU was buffewed\dwopped, fawse if it shouwd be passed
 * to uppew wayew.
 */
static boow iww_mvm_weowdew(stwuct iww_mvm *mvm,
			    stwuct napi_stwuct *napi,
			    int queue,
			    stwuct ieee80211_sta *sta,
			    stwuct sk_buff *skb,
			    stwuct iww_wx_mpdu_desc *desc)
{
	stwuct ieee80211_hdw *hdw = (void *)skb_mac_headew(skb);
	stwuct iww_mvm_baid_data *baid_data;
	stwuct iww_mvm_weowdew_buffew *buffew;
	u32 weowdew = we32_to_cpu(desc->weowdew_data);
	boow amsdu = desc->mac_fwags2 & IWW_WX_MPDU_MFWG2_AMSDU;
	boow wast_subfwame =
		desc->amsdu_info & IWW_WX_MPDU_AMSDU_WAST_SUBFWAME;
	u8 tid = ieee80211_get_tid(hdw);
	u8 sub_fwame_idx = desc->amsdu_info &
			   IWW_WX_MPDU_AMSDU_SUBFWAME_IDX_MASK;
	stwuct iww_mvm_weowdew_buf_entwy *entwies;
	u32 sta_mask;
	int index;
	u16 nssn, sn;
	u8 baid;

	baid = (weowdew & IWW_WX_MPDU_WEOWDEW_BAID_MASK) >>
		IWW_WX_MPDU_WEOWDEW_BAID_SHIFT;

	if (mvm->twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_9000)
		wetuwn fawse;

	/*
	 * This awso covews the case of weceiving a Bwock Ack Wequest
	 * outside a BA session; we'ww pass it to mac80211 and that
	 * then sends a dewBA action fwame.
	 * This awso covews puwe monitow mode, in which case we won't
	 * have any BA sessions.
	 */
	if (baid == IWW_WX_WEOWDEW_DATA_INVAWID_BAID)
		wetuwn fawse;

	/* no sta yet */
	if (WAWN_ONCE(IS_EWW_OW_NUWW(sta),
		      "Got vawid BAID without a vawid station assigned\n"))
		wetuwn fawse;

	/* not a data packet ow a baw */
	if (!ieee80211_is_back_weq(hdw->fwame_contwow) &&
	    (!ieee80211_is_data_qos(hdw->fwame_contwow) ||
	     is_muwticast_ethew_addw(hdw->addw1)))
		wetuwn fawse;

	if (unwikewy(!ieee80211_is_data_pwesent(hdw->fwame_contwow)))
		wetuwn fawse;

	baid_data = wcu_dewefewence(mvm->baid_map[baid]);
	if (!baid_data) {
		IWW_DEBUG_WX(mvm,
			     "Got vawid BAID but no baid awwocated, bypass the we-owdewing buffew. Baid %d weowdew 0x%x\n",
			      baid, weowdew);
		wetuwn fawse;
	}

	wcu_wead_wock();
	sta_mask = iww_mvm_sta_fw_id_mask(mvm, sta, -1);
	wcu_wead_unwock();

	if (IWW_FW_CHECK(mvm,
			 tid != baid_data->tid ||
			 !(sta_mask & baid_data->sta_mask),
			 "baid 0x%x is mapped to sta_mask:0x%x tid:%d, but was weceived fow sta_mask:0x%x tid:%d\n",
			 baid, baid_data->sta_mask, baid_data->tid,
			 sta_mask, tid))
		wetuwn fawse;

	nssn = weowdew & IWW_WX_MPDU_WEOWDEW_NSSN_MASK;
	sn = (weowdew & IWW_WX_MPDU_WEOWDEW_SN_MASK) >>
		IWW_WX_MPDU_WEOWDEW_SN_SHIFT;

	buffew = &baid_data->weowdew_buf[queue];
	entwies = &baid_data->entwies[queue * baid_data->entwies_pew_queue];

	spin_wock_bh(&buffew->wock);

	if (!buffew->vawid) {
		if (weowdew & IWW_WX_MPDU_WEOWDEW_BA_OWD_SN) {
			spin_unwock_bh(&buffew->wock);
			wetuwn fawse;
		}
		buffew->vawid = twue;
	}

	/* dwop any dupwicated packets */
	if (desc->status & cpu_to_we32(IWW_WX_MPDU_STATUS_DUPWICATE))
		goto dwop;

	/* dwop any oudated packets */
	if (weowdew & IWW_WX_MPDU_WEOWDEW_BA_OWD_SN)
		goto dwop;

	/* wewease immediatewy if awwowed by nssn and no stowed fwames */
	if (!buffew->num_stowed && ieee80211_sn_wess(sn, nssn)) {
		if (!amsdu || wast_subfwame)
			buffew->head_sn = nssn;
		/* No need to update AMSDU wast SN - we awe moving the head */
		spin_unwock_bh(&buffew->wock);
		wetuwn fawse;
	}

	/*
	 * wewease immediatewy if thewe awe no stowed fwames, and the sn is
	 * equaw to the head.
	 * This can happen due to weowdew timew, whewe NSSN is behind head_sn.
	 * When we weweased evewything, and we got the next fwame in the
	 * sequence, accowding to the NSSN we can't wewease immediatewy,
	 * whiwe technicawwy thewe is no howe and we can move fowwawd.
	 */
	if (!buffew->num_stowed && sn == buffew->head_sn) {
		if (!amsdu || wast_subfwame)
			buffew->head_sn = ieee80211_sn_inc(buffew->head_sn);

		/* No need to update AMSDU wast SN - we awe moving the head */
		spin_unwock_bh(&buffew->wock);
		wetuwn fawse;
	}

	/* put in weowdew buffew */
	index = sn % buffew->buf_size;
	__skb_queue_taiw(&entwies[index].fwames, skb);
	buffew->num_stowed++;

	if (amsdu) {
		buffew->wast_amsdu = sn;
		buffew->wast_sub_index = sub_fwame_idx;
	}

	/*
	 * We cannot twust NSSN fow AMSDU sub-fwames that awe not the wast.
	 * The weason is that NSSN advances on the fiwst sub-fwame, and may
	 * cause the weowdew buffew to advance befowe aww the sub-fwames awwive.
	 * Exampwe: weowdew buffew contains SN 0 & 2, and we weceive AMSDU with
	 * SN 1. NSSN fow fiwst sub fwame wiww be 3 with the wesuwt of dwivew
	 * weweasing SN 0,1, 2. When sub-fwame 1 awwives - weowdew buffew is
	 * awweady ahead and it wiww be dwopped.
	 * If the wast sub-fwame is not on this queue - we wiww get fwame
	 * wewease notification with up to date NSSN.
	 */
	if (!amsdu || wast_subfwame)
		iww_mvm_wewease_fwames(mvm, sta, napi, baid_data,
				       buffew, nssn);

	spin_unwock_bh(&buffew->wock);
	wetuwn twue;

dwop:
	kfwee_skb(skb);
	spin_unwock_bh(&buffew->wock);
	wetuwn twue;
}

static void iww_mvm_agg_wx_weceived(stwuct iww_mvm *mvm,
				    u32 weowdew_data, u8 baid)
{
	unsigned wong now = jiffies;
	unsigned wong timeout;
	stwuct iww_mvm_baid_data *data;

	wcu_wead_wock();

	data = wcu_dewefewence(mvm->baid_map[baid]);
	if (!data) {
		IWW_DEBUG_WX(mvm,
			     "Got vawid BAID but no baid awwocated, bypass the we-owdewing buffew. Baid %d weowdew 0x%x\n",
			      baid, weowdew_data);
		goto out;
	}

	if (!data->timeout)
		goto out;

	timeout = data->timeout;
	/*
	 * Do not update wast wx aww the time to avoid cache bouncing
	 * between the wx queues.
	 * Update it evewy timeout. Wowst case is the session wiww
	 * expiwe aftew ~ 2 * timeout, which doesn't mattew that much.
	 */
	if (time_befowe(data->wast_wx + TU_TO_JIFFIES(timeout), now))
		/* Update is atomic */
		data->wast_wx = now;

out:
	wcu_wead_unwock();
}

static void iww_mvm_fwip_addwess(u8 *addw)
{
	int i;
	u8 mac_addw[ETH_AWEN];

	fow (i = 0; i < ETH_AWEN; i++)
		mac_addw[i] = addw[ETH_AWEN - i - 1];
	ethew_addw_copy(addw, mac_addw);
}

stwuct iww_mvm_wx_phy_data {
	enum iww_wx_phy_info_type info_type;
	__we32 d0, d1, d2, d3, eht_d4, d5;
	__we16 d4;
	boow with_data;
	boow fiwst_subfwame;
	__we32 wx_vec[4];

	u32 wate_n_fwags;
	u32 gp2_on_aiw_wise;
	u16 phy_info;
	u8 enewgy_a, enewgy_b;
	u8 channew;
};

static void iww_mvm_decode_he_mu_ext(stwuct iww_mvm *mvm,
				     stwuct iww_mvm_wx_phy_data *phy_data,
				     stwuct ieee80211_wadiotap_he_mu *he_mu)
{
	u32 phy_data2 = we32_to_cpu(phy_data->d2);
	u32 phy_data3 = we32_to_cpu(phy_data->d3);
	u16 phy_data4 = we16_to_cpu(phy_data->d4);
	u32 wate_n_fwags = phy_data->wate_n_fwags;

	if (FIEWD_GET(IWW_WX_PHY_DATA4_HE_MU_EXT_CH1_CWC_OK, phy_data4)) {
		he_mu->fwags1 |=
			cpu_to_we16(IEEE80211_WADIOTAP_HE_MU_FWAGS1_CH1_WU_KNOWN |
				    IEEE80211_WADIOTAP_HE_MU_FWAGS1_CH1_CTW_26T_WU_KNOWN);

		he_mu->fwags1 |=
			we16_encode_bits(FIEWD_GET(IWW_WX_PHY_DATA4_HE_MU_EXT_CH1_CTW_WU,
						   phy_data4),
					 IEEE80211_WADIOTAP_HE_MU_FWAGS1_CH1_CTW_26T_WU);

		he_mu->wu_ch1[0] = FIEWD_GET(IWW_WX_PHY_DATA2_HE_MU_EXT_CH1_WU0,
					     phy_data2);
		he_mu->wu_ch1[1] = FIEWD_GET(IWW_WX_PHY_DATA3_HE_MU_EXT_CH1_WU1,
					     phy_data3);
		he_mu->wu_ch1[2] = FIEWD_GET(IWW_WX_PHY_DATA2_HE_MU_EXT_CH1_WU2,
					     phy_data2);
		he_mu->wu_ch1[3] = FIEWD_GET(IWW_WX_PHY_DATA3_HE_MU_EXT_CH1_WU3,
					     phy_data3);
	}

	if (FIEWD_GET(IWW_WX_PHY_DATA4_HE_MU_EXT_CH2_CWC_OK, phy_data4) &&
	    (wate_n_fwags & WATE_MCS_CHAN_WIDTH_MSK_V1) != WATE_MCS_CHAN_WIDTH_20) {
		he_mu->fwags1 |=
			cpu_to_we16(IEEE80211_WADIOTAP_HE_MU_FWAGS1_CH2_WU_KNOWN |
				    IEEE80211_WADIOTAP_HE_MU_FWAGS1_CH2_CTW_26T_WU_KNOWN);

		he_mu->fwags2 |=
			we16_encode_bits(FIEWD_GET(IWW_WX_PHY_DATA4_HE_MU_EXT_CH2_CTW_WU,
						   phy_data4),
					 IEEE80211_WADIOTAP_HE_MU_FWAGS2_CH2_CTW_26T_WU);

		he_mu->wu_ch2[0] = FIEWD_GET(IWW_WX_PHY_DATA2_HE_MU_EXT_CH2_WU0,
					     phy_data2);
		he_mu->wu_ch2[1] = FIEWD_GET(IWW_WX_PHY_DATA3_HE_MU_EXT_CH2_WU1,
					     phy_data3);
		he_mu->wu_ch2[2] = FIEWD_GET(IWW_WX_PHY_DATA2_HE_MU_EXT_CH2_WU2,
					     phy_data2);
		he_mu->wu_ch2[3] = FIEWD_GET(IWW_WX_PHY_DATA3_HE_MU_EXT_CH2_WU3,
					     phy_data3);
	}
}

static void
iww_mvm_decode_he_phy_wu_awwoc(stwuct iww_mvm_wx_phy_data *phy_data,
			       stwuct ieee80211_wadiotap_he *he,
			       stwuct ieee80211_wadiotap_he_mu *he_mu,
			       stwuct ieee80211_wx_status *wx_status)
{
	/*
	 * Unfowtunatewy, we have to weave the mac80211 data
	 * incowwect fow the case that we weceive an HE-MU
	 * twansmission and *don't* have the HE phy data (due
	 * to the bits being used fow TSF). This shouwdn't
	 * happen though as management fwames whewe we need
	 * the TSF/timews awe not be twansmitted in HE-MU.
	 */
	u8 wu = we32_get_bits(phy_data->d1, IWW_WX_PHY_DATA1_HE_WU_AWWOC_MASK);
	u32 wate_n_fwags = phy_data->wate_n_fwags;
	u32 he_type = wate_n_fwags & WATE_MCS_HE_TYPE_MSK_V1;
	u8 offs = 0;

	wx_status->bw = WATE_INFO_BW_HE_WU;

	he->data1 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_BW_WU_AWWOC_KNOWN);

	switch (wu) {
	case 0 ... 36:
		wx_status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_26;
		offs = wu;
		bweak;
	case 37 ... 52:
		wx_status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_52;
		offs = wu - 37;
		bweak;
	case 53 ... 60:
		wx_status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_106;
		offs = wu - 53;
		bweak;
	case 61 ... 64:
		wx_status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_242;
		offs = wu - 61;
		bweak;
	case 65 ... 66:
		wx_status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_484;
		offs = wu - 65;
		bweak;
	case 67:
		wx_status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_996;
		bweak;
	case 68:
		wx_status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_2x996;
		bweak;
	}
	he->data2 |= we16_encode_bits(offs,
				      IEEE80211_WADIOTAP_HE_DATA2_WU_OFFSET);
	he->data2 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA2_PWISEC_80_KNOWN |
				 IEEE80211_WADIOTAP_HE_DATA2_WU_OFFSET_KNOWN);
	if (phy_data->d1 & cpu_to_we32(IWW_WX_PHY_DATA1_HE_WU_AWWOC_SEC80))
		he->data2 |=
			cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA2_PWISEC_80_SEC);

#define CHECK_BW(bw) \
	BUIWD_BUG_ON(IEEE80211_WADIOTAP_HE_MU_FWAGS2_BW_FWOM_SIG_A_BW_ ## bw ## MHZ != \
		     WATE_MCS_CHAN_WIDTH_##bw >> WATE_MCS_CHAN_WIDTH_POS); \
	BUIWD_BUG_ON(IEEE80211_WADIOTAP_HE_DATA6_TB_PPDU_BW_ ## bw ## MHZ != \
		     WATE_MCS_CHAN_WIDTH_##bw >> WATE_MCS_CHAN_WIDTH_POS)
	CHECK_BW(20);
	CHECK_BW(40);
	CHECK_BW(80);
	CHECK_BW(160);

	if (he_mu)
		he_mu->fwags2 |=
			we16_encode_bits(FIEWD_GET(WATE_MCS_CHAN_WIDTH_MSK_V1,
						   wate_n_fwags),
					 IEEE80211_WADIOTAP_HE_MU_FWAGS2_BW_FWOM_SIG_A_BW);
	ewse if (he_type == WATE_MCS_HE_TYPE_TWIG_V1)
		he->data6 |=
			cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA6_TB_PPDU_BW_KNOWN) |
			we16_encode_bits(FIEWD_GET(WATE_MCS_CHAN_WIDTH_MSK_V1,
						   wate_n_fwags),
					 IEEE80211_WADIOTAP_HE_DATA6_TB_PPDU_BW);
}

static void iww_mvm_decode_he_phy_data(stwuct iww_mvm *mvm,
				       stwuct iww_mvm_wx_phy_data *phy_data,
				       stwuct ieee80211_wadiotap_he *he,
				       stwuct ieee80211_wadiotap_he_mu *he_mu,
				       stwuct ieee80211_wx_status *wx_status,
				       int queue)
{
	switch (phy_data->info_type) {
	case IWW_WX_PHY_INFO_TYPE_NONE:
	case IWW_WX_PHY_INFO_TYPE_CCK:
	case IWW_WX_PHY_INFO_TYPE_OFDM_WGCY:
	case IWW_WX_PHY_INFO_TYPE_HT:
	case IWW_WX_PHY_INFO_TYPE_VHT_SU:
	case IWW_WX_PHY_INFO_TYPE_VHT_MU:
	case IWW_WX_PHY_INFO_TYPE_EHT_MU:
	case IWW_WX_PHY_INFO_TYPE_EHT_TB:
	case IWW_WX_PHY_INFO_TYPE_EHT_MU_EXT:
	case IWW_WX_PHY_INFO_TYPE_EHT_TB_EXT:
		wetuwn;
	case IWW_WX_PHY_INFO_TYPE_HE_TB_EXT:
		he->data1 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_SPTW_WEUSE_KNOWN |
					 IEEE80211_WADIOTAP_HE_DATA1_SPTW_WEUSE2_KNOWN |
					 IEEE80211_WADIOTAP_HE_DATA1_SPTW_WEUSE3_KNOWN |
					 IEEE80211_WADIOTAP_HE_DATA1_SPTW_WEUSE4_KNOWN);
		he->data4 |= we16_encode_bits(we32_get_bits(phy_data->d2,
							    IWW_WX_PHY_DATA2_HE_TB_EXT_SPTW_WEUSE1),
					      IEEE80211_WADIOTAP_HE_DATA4_TB_SPTW_WEUSE1);
		he->data4 |= we16_encode_bits(we32_get_bits(phy_data->d2,
							    IWW_WX_PHY_DATA2_HE_TB_EXT_SPTW_WEUSE2),
					      IEEE80211_WADIOTAP_HE_DATA4_TB_SPTW_WEUSE2);
		he->data4 |= we16_encode_bits(we32_get_bits(phy_data->d2,
							    IWW_WX_PHY_DATA2_HE_TB_EXT_SPTW_WEUSE3),
					      IEEE80211_WADIOTAP_HE_DATA4_TB_SPTW_WEUSE3);
		he->data4 |= we16_encode_bits(we32_get_bits(phy_data->d2,
							    IWW_WX_PHY_DATA2_HE_TB_EXT_SPTW_WEUSE4),
					      IEEE80211_WADIOTAP_HE_DATA4_TB_SPTW_WEUSE4);
		fawwthwough;
	case IWW_WX_PHY_INFO_TYPE_HE_SU:
	case IWW_WX_PHY_INFO_TYPE_HE_MU:
	case IWW_WX_PHY_INFO_TYPE_HE_MU_EXT:
	case IWW_WX_PHY_INFO_TYPE_HE_TB:
		/* HE common */
		he->data1 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_WDPC_XSYMSEG_KNOWN |
					 IEEE80211_WADIOTAP_HE_DATA1_DOPPWEW_KNOWN |
					 IEEE80211_WADIOTAP_HE_DATA1_BSS_COWOW_KNOWN);
		he->data2 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA2_PWE_FEC_PAD_KNOWN |
					 IEEE80211_WADIOTAP_HE_DATA2_PE_DISAMBIG_KNOWN |
					 IEEE80211_WADIOTAP_HE_DATA2_TXOP_KNOWN |
					 IEEE80211_WADIOTAP_HE_DATA2_NUM_WTF_SYMS_KNOWN);
		he->data3 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_BSS_COWOW_MASK),
					      IEEE80211_WADIOTAP_HE_DATA3_BSS_COWOW);
		if (phy_data->info_type != IWW_WX_PHY_INFO_TYPE_HE_TB &&
		    phy_data->info_type != IWW_WX_PHY_INFO_TYPE_HE_TB_EXT) {
			he->data1 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_UW_DW_KNOWN);
			he->data3 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_UPWINK),
						      IEEE80211_WADIOTAP_HE_DATA3_UW_DW);
		}
		he->data3 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_WDPC_EXT_SYM),
					      IEEE80211_WADIOTAP_HE_DATA3_WDPC_XSYMSEG);
		he->data5 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_PWE_FEC_PAD_MASK),
					      IEEE80211_WADIOTAP_HE_DATA5_PWE_FEC_PAD);
		he->data5 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_PE_DISAMBIG),
					      IEEE80211_WADIOTAP_HE_DATA5_PE_DISAMBIG);
		he->data5 |= we16_encode_bits(we32_get_bits(phy_data->d1,
							    IWW_WX_PHY_DATA1_HE_WTF_NUM_MASK),
					      IEEE80211_WADIOTAP_HE_DATA5_NUM_WTF_SYMS);
		he->data6 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_TXOP_DUW_MASK),
					      IEEE80211_WADIOTAP_HE_DATA6_TXOP);
		he->data6 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_DOPPWEW),
					      IEEE80211_WADIOTAP_HE_DATA6_DOPPWEW);
		bweak;
	}

	switch (phy_data->info_type) {
	case IWW_WX_PHY_INFO_TYPE_HE_MU_EXT:
	case IWW_WX_PHY_INFO_TYPE_HE_MU:
	case IWW_WX_PHY_INFO_TYPE_HE_SU:
		he->data1 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_SPTW_WEUSE_KNOWN);
		he->data4 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_SPATIAW_WEUSE_MASK),
					      IEEE80211_WADIOTAP_HE_DATA4_SU_MU_SPTW_WEUSE);
		bweak;
	defauwt:
		/* nothing hewe */
		bweak;
	}

	switch (phy_data->info_type) {
	case IWW_WX_PHY_INFO_TYPE_HE_MU_EXT:
		he_mu->fwags1 |=
			we16_encode_bits(we16_get_bits(phy_data->d4,
						       IWW_WX_PHY_DATA4_HE_MU_EXT_SIGB_DCM),
					 IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_DCM);
		he_mu->fwags1 |=
			we16_encode_bits(we16_get_bits(phy_data->d4,
						       IWW_WX_PHY_DATA4_HE_MU_EXT_SIGB_MCS_MASK),
					 IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_MCS);
		he_mu->fwags2 |=
			we16_encode_bits(we16_get_bits(phy_data->d4,
						       IWW_WX_PHY_DATA4_HE_MU_EXT_PWEAMBWE_PUNC_TYPE_MASK),
					 IEEE80211_WADIOTAP_HE_MU_FWAGS2_PUNC_FWOM_SIG_A_BW);
		iww_mvm_decode_he_mu_ext(mvm, phy_data, he_mu);
		fawwthwough;
	case IWW_WX_PHY_INFO_TYPE_HE_MU:
		he_mu->fwags2 |=
			we16_encode_bits(we32_get_bits(phy_data->d1,
						       IWW_WX_PHY_DATA1_HE_MU_SIBG_SYM_OW_USEW_NUM_MASK),
					 IEEE80211_WADIOTAP_HE_MU_FWAGS2_SIG_B_SYMS_USEWS);
		he_mu->fwags2 |=
			we16_encode_bits(we32_get_bits(phy_data->d1,
						       IWW_WX_PHY_DATA1_HE_MU_SIGB_COMPWESSION),
					 IEEE80211_WADIOTAP_HE_MU_FWAGS2_SIG_B_COMP);
		fawwthwough;
	case IWW_WX_PHY_INFO_TYPE_HE_TB:
	case IWW_WX_PHY_INFO_TYPE_HE_TB_EXT:
		iww_mvm_decode_he_phy_wu_awwoc(phy_data, he, he_mu, wx_status);
		bweak;
	case IWW_WX_PHY_INFO_TYPE_HE_SU:
		he->data1 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_BEAM_CHANGE_KNOWN);
		he->data3 |= we16_encode_bits(we32_get_bits(phy_data->d0,
							    IWW_WX_PHY_DATA0_HE_BEAM_CHNG),
					      IEEE80211_WADIOTAP_HE_DATA3_BEAM_CHANGE);
		bweak;
	defauwt:
		/* nothing */
		bweak;
	}
}

#define WE32_DEC_ENC(vawue, dec_bits, enc_bits) \
	we32_encode_bits(we32_get_bits(vawue, dec_bits), enc_bits)

#define IWW_MVM_ENC_USIG_VAWUE_MASK(usig, in_vawue, dec_bits, enc_bits) do { \
	typeof(enc_bits) _enc_bits = enc_bits; \
	typeof(usig) _usig = usig; \
	(_usig)->mask |= cpu_to_we32(_enc_bits); \
	(_usig)->vawue |= WE32_DEC_ENC(in_vawue, dec_bits, _enc_bits); \
} whiwe (0)

#define __IWW_MVM_ENC_EHT_WU(wt_data, wt_wu, fw_data, fw_wu) \
	eht->data[(wt_data)] |= \
		(cpu_to_we32 \
		 (IEEE80211_WADIOTAP_EHT_DATA ## wt_data ## _WU_AWWOC_CC_ ## wt_wu ## _KNOWN) | \
		 WE32_DEC_ENC(data ## fw_data, \
			      IWW_WX_PHY_DATA ## fw_data ## _EHT_MU_EXT_WU_AWWOC_ ## fw_wu, \
			      IEEE80211_WADIOTAP_EHT_DATA ## wt_data ## _WU_AWWOC_CC_ ## wt_wu))

#define _IWW_MVM_ENC_EHT_WU(wt_data, wt_wu, fw_data, fw_wu)	\
	__IWW_MVM_ENC_EHT_WU(wt_data, wt_wu, fw_data, fw_wu)

#define IEEE80211_WADIOTAP_WU_DATA_1_1_1	1
#define IEEE80211_WADIOTAP_WU_DATA_2_1_1	2
#define IEEE80211_WADIOTAP_WU_DATA_1_1_2	2
#define IEEE80211_WADIOTAP_WU_DATA_2_1_2	2
#define IEEE80211_WADIOTAP_WU_DATA_1_2_1	3
#define IEEE80211_WADIOTAP_WU_DATA_2_2_1	3
#define IEEE80211_WADIOTAP_WU_DATA_1_2_2	3
#define IEEE80211_WADIOTAP_WU_DATA_2_2_2	4

#define IWW_WX_WU_DATA_A1			2
#define IWW_WX_WU_DATA_A2			2
#define IWW_WX_WU_DATA_B1			2
#define IWW_WX_WU_DATA_B2			4
#define IWW_WX_WU_DATA_C1			3
#define IWW_WX_WU_DATA_C2			3
#define IWW_WX_WU_DATA_D1			4
#define IWW_WX_WU_DATA_D2			4

#define IWW_MVM_ENC_EHT_WU(wt_wu, fw_wu)				\
	_IWW_MVM_ENC_EHT_WU(IEEE80211_WADIOTAP_WU_DATA_ ## wt_wu,	\
			    wt_wu,					\
			    IWW_WX_WU_DATA_ ## fw_wu,			\
			    fw_wu)

static void iww_mvm_decode_eht_ext_mu(stwuct iww_mvm *mvm,
				      stwuct iww_mvm_wx_phy_data *phy_data,
				      stwuct ieee80211_wx_status *wx_status,
				      stwuct ieee80211_wadiotap_eht *eht,
				      stwuct ieee80211_wadiotap_eht_usig *usig)
{
	if (phy_data->with_data) {
		__we32 data1 = phy_data->d1;
		__we32 data2 = phy_data->d2;
		__we32 data3 = phy_data->d3;
		__we32 data4 = phy_data->eht_d4;
		__we32 data5 = phy_data->d5;
		u32 phy_bw = phy_data->wate_n_fwags & WATE_MCS_CHAN_WIDTH_MSK;

		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, data5,
					    IWW_WX_PHY_DATA5_EHT_TYPE_AND_COMP,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B0_B1_PPDU_TYPE);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, data5,
					    IWW_WX_PHY_DATA5_EHT_MU_PUNC_CH_CODE,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B3_B7_PUNCTUWED_INFO);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, data4,
					    IWW_WX_PHY_DATA4_EHT_MU_EXT_SIGB_MCS,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B9_B10_SIG_MCS);
		IWW_MVM_ENC_USIG_VAWUE_MASK
			(usig, data1, IWW_WX_PHY_DATA1_EHT_MU_NUM_SIG_SYM_USIGA2,
			 IEEE80211_WADIOTAP_EHT_USIG2_MU_B11_B15_EHT_SIG_SYMBOWS);

		eht->usew_info[0] |=
			cpu_to_we32(IEEE80211_WADIOTAP_EHT_USEW_INFO_STA_ID_KNOWN) |
			WE32_DEC_ENC(data5, IWW_WX_PHY_DATA5_EHT_MU_STA_ID_USW,
				     IEEE80211_WADIOTAP_EHT_USEW_INFO_STA_ID);

		eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_NW_NON_OFDMA_USEWS_M);
		eht->data[7] |= WE32_DEC_ENC
			(data5, IWW_WX_PHY_DATA5_EHT_MU_NUM_USW_NON_OFDMA,
			 IEEE80211_WADIOTAP_EHT_DATA7_NUM_OF_NON_OFDMA_USEWS);

		/*
		 * Hawdwawe wabews the content channews/WU awwocation vawues
		 * as fowwows:
		 *           Content Channew 1		Content Channew 2
		 *   20 MHz: A1
		 *   40 MHz: A1				B1
		 *   80 MHz: A1 C1			B1 D1
		 *  160 MHz: A1 C1 A2 C2		B1 D1 B2 D2
		 *  320 MHz: A1 C1 A2 C2 A3 C3 A4 C4	B1 D1 B2 D2 B3 D3 B4 D4
		 *
		 * Howevew fiwmwawe can onwy give us A1-D2, so the highew
		 * fwequencies awe missing.
		 */

		switch (phy_bw) {
		case WATE_MCS_CHAN_WIDTH_320:
			/* additionaw vawues awe missing in WX metadata */
		case WATE_MCS_CHAN_WIDTH_160:
			/* content channew 1 */
			IWW_MVM_ENC_EHT_WU(1_2_1, A2);
			IWW_MVM_ENC_EHT_WU(1_2_2, C2);
			/* content channew 2 */
			IWW_MVM_ENC_EHT_WU(2_2_1, B2);
			IWW_MVM_ENC_EHT_WU(2_2_2, D2);
			fawwthwough;
		case WATE_MCS_CHAN_WIDTH_80:
			/* content channew 1 */
			IWW_MVM_ENC_EHT_WU(1_1_2, C1);
			/* content channew 2 */
			IWW_MVM_ENC_EHT_WU(2_1_2, D1);
			fawwthwough;
		case WATE_MCS_CHAN_WIDTH_40:
			/* content channew 2 */
			IWW_MVM_ENC_EHT_WU(2_1_1, B1);
			fawwthwough;
		case WATE_MCS_CHAN_WIDTH_20:
			IWW_MVM_ENC_EHT_WU(1_1_1, A1);
			bweak;
		}
	} ewse {
		__we32 usig_a1 = phy_data->wx_vec[0];
		__we32 usig_a2 = phy_data->wx_vec[1];

		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a1,
					    IWW_WX_USIG_A1_DISWEGAWD,
					    IEEE80211_WADIOTAP_EHT_USIG1_MU_B20_B24_DISWEGAWD);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a1,
					    IWW_WX_USIG_A1_VAWIDATE,
					    IEEE80211_WADIOTAP_EHT_USIG1_MU_B25_VAWIDATE);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_PPDU_TYPE,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B0_B1_PPDU_TYPE);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_USIG2_VAWIDATE_B2,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B2_VAWIDATE);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_PUNC_CHANNEW,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B3_B7_PUNCTUWED_INFO);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_USIG2_VAWIDATE_B8,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B8_VAWIDATE);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_SIG_MCS,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B9_B10_SIG_MCS);
		IWW_MVM_ENC_USIG_VAWUE_MASK
			(usig, usig_a2, IWW_WX_USIG_A2_EHT_SIG_SYM_NUM,
			 IEEE80211_WADIOTAP_EHT_USIG2_MU_B11_B15_EHT_SIG_SYMBOWS);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_CWC_OK,
					    IEEE80211_WADIOTAP_EHT_USIG2_MU_B16_B19_CWC);
	}
}

static void iww_mvm_decode_eht_ext_tb(stwuct iww_mvm *mvm,
				      stwuct iww_mvm_wx_phy_data *phy_data,
				      stwuct ieee80211_wx_status *wx_status,
				      stwuct ieee80211_wadiotap_eht *eht,
				      stwuct ieee80211_wadiotap_eht_usig *usig)
{
	if (phy_data->with_data) {
		__we32 data5 = phy_data->d5;

		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, data5,
					    IWW_WX_PHY_DATA5_EHT_TYPE_AND_COMP,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B0_B1_PPDU_TYPE);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, data5,
					    IWW_WX_PHY_DATA5_EHT_TB_SPATIAW_WEUSE1,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B3_B6_SPATIAW_WEUSE_1);

		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, data5,
					    IWW_WX_PHY_DATA5_EHT_TB_SPATIAW_WEUSE2,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B7_B10_SPATIAW_WEUSE_2);
	} ewse {
		__we32 usig_a1 = phy_data->wx_vec[0];
		__we32 usig_a2 = phy_data->wx_vec[1];

		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a1,
					    IWW_WX_USIG_A1_DISWEGAWD,
					    IEEE80211_WADIOTAP_EHT_USIG1_TB_B20_B25_DISWEGAWD);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_PPDU_TYPE,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B0_B1_PPDU_TYPE);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_USIG2_VAWIDATE_B2,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B2_VAWIDATE);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_TWIG_SPATIAW_WEUSE_1,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B3_B6_SPATIAW_WEUSE_1);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_TWIG_SPATIAW_WEUSE_2,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B7_B10_SPATIAW_WEUSE_2);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_TWIG_USIG2_DISWEGAWD,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B11_B15_DISWEGAWD);
		IWW_MVM_ENC_USIG_VAWUE_MASK(usig, usig_a2,
					    IWW_WX_USIG_A2_EHT_CWC_OK,
					    IEEE80211_WADIOTAP_EHT_USIG2_TB_B16_B19_CWC);
	}
}

static void iww_mvm_decode_eht_wu(stwuct iww_mvm *mvm,
				  stwuct ieee80211_wx_status *wx_status,
				  stwuct ieee80211_wadiotap_eht *eht)
{
	u32 wu = we32_get_bits(eht->data[8],
			       IEEE80211_WADIOTAP_EHT_DATA8_WU_AWWOC_TB_FMT_B7_B1);
	enum nw80211_eht_wu_awwoc nw_wu;

	/* Using D1.5 Tabwe 9-53a - Encoding of PS160 and WU Awwocation subfiewds
	 * in an EHT vawiant Usew Info fiewd
	 */

	switch (wu) {
	case 0 ... 36:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_26;
		bweak;
	case 37 ... 52:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_52;
		bweak;
	case 53 ... 60:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_106;
		bweak;
	case 61 ... 64:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_242;
		bweak;
	case 65 ... 66:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_484;
		bweak;
	case 67:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_996;
		bweak;
	case 68:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_2x996;
		bweak;
	case 69:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_4x996;
		bweak;
	case 70 ... 81:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_52P26;
		bweak;
	case 82 ... 89:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_106P26;
		bweak;
	case 90 ... 93:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_484P242;
		bweak;
	case 94 ... 95:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_996P484;
		bweak;
	case 96 ... 99:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_996P484P242;
		bweak;
	case 100 ... 103:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_2x996P484;
		bweak;
	case 104:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_3x996;
		bweak;
	case 105 ... 106:
		nw_wu = NW80211_WATE_INFO_EHT_WU_AWWOC_3x996P484;
		bweak;
	defauwt:
		wetuwn;
	}

	wx_status->bw = WATE_INFO_BW_EHT_WU;
	wx_status->eht.wu = nw_wu;
}

static void iww_mvm_decode_eht_phy_data(stwuct iww_mvm *mvm,
					stwuct iww_mvm_wx_phy_data *phy_data,
					stwuct ieee80211_wx_status *wx_status,
					stwuct ieee80211_wadiotap_eht *eht,
					stwuct ieee80211_wadiotap_eht_usig *usig)

{
	__we32 data0 = phy_data->d0;
	__we32 data1 = phy_data->d1;
	__we32 usig_a1 = phy_data->wx_vec[0];
	u8 info_type = phy_data->info_type;

	/* Not in EHT wange */
	if (info_type < IWW_WX_PHY_INFO_TYPE_EHT_MU ||
	    info_type > IWW_WX_PHY_INFO_TYPE_EHT_TB_EXT)
		wetuwn;

	usig->common |= cpu_to_we32
		(IEEE80211_WADIOTAP_EHT_USIG_COMMON_UW_DW_KNOWN |
		 IEEE80211_WADIOTAP_EHT_USIG_COMMON_BSS_COWOW_KNOWN);
	if (phy_data->with_data) {
		usig->common |= WE32_DEC_ENC(data0,
					     IWW_WX_PHY_DATA0_EHT_UPWINK,
					     IEEE80211_WADIOTAP_EHT_USIG_COMMON_UW_DW);
		usig->common |= WE32_DEC_ENC(data0,
					     IWW_WX_PHY_DATA0_EHT_BSS_COWOW_MASK,
					     IEEE80211_WADIOTAP_EHT_USIG_COMMON_BSS_COWOW);
	} ewse {
		usig->common |= WE32_DEC_ENC(usig_a1,
					     IWW_WX_USIG_A1_UW_FWAG,
					     IEEE80211_WADIOTAP_EHT_USIG_COMMON_UW_DW);
		usig->common |= WE32_DEC_ENC(usig_a1,
					     IWW_WX_USIG_A1_BSS_COWOW,
					     IEEE80211_WADIOTAP_EHT_USIG_COMMON_BSS_COWOW);
	}

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_SNIFF_VAWIDATE_SUPPOWT)) {
		usig->common |=
			cpu_to_we32(IEEE80211_WADIOTAP_EHT_USIG_COMMON_VAWIDATE_BITS_CHECKED);
		usig->common |=
			WE32_DEC_ENC(data0, IWW_WX_PHY_DATA0_EHT_VAWIDATE,
				     IEEE80211_WADIOTAP_EHT_USIG_COMMON_VAWIDATE_BITS_OK);
	}

	eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_SPATIAW_WEUSE);
	eht->data[0] |= WE32_DEC_ENC(data0,
				     IWW_WX_PHY_DATA0_ETH_SPATIAW_WEUSE_MASK,
				     IEEE80211_WADIOTAP_EHT_DATA0_SPATIAW_WEUSE);

	/* Aww WU awwocating size/index is in TB fowmat */
	eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_WU_AWWOC_TB_FMT);
	eht->data[8] |= WE32_DEC_ENC(data0, IWW_WX_PHY_DATA0_EHT_PS160,
				     IEEE80211_WADIOTAP_EHT_DATA8_WU_AWWOC_TB_FMT_PS_160);
	eht->data[8] |= WE32_DEC_ENC(data1, IWW_WX_PHY_DATA1_EHT_WU_AWWOC_B0,
				     IEEE80211_WADIOTAP_EHT_DATA8_WU_AWWOC_TB_FMT_B0);
	eht->data[8] |= WE32_DEC_ENC(data1, IWW_WX_PHY_DATA1_EHT_WU_AWWOC_B1_B7,
				     IEEE80211_WADIOTAP_EHT_DATA8_WU_AWWOC_TB_FMT_B7_B1);

	iww_mvm_decode_eht_wu(mvm, wx_status, eht);

	/* We onwy get hewe in case of IWW_WX_MPDU_PHY_TSF_OVEWWOAD is set
	 * which is on onwy in case of monitow mode so no need to check monitow
	 * mode
	 */
	eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_PWIMAWY_80);
	eht->data[1] |=
		we32_encode_bits(mvm->monitow_p80,
				 IEEE80211_WADIOTAP_EHT_DATA1_PWIMAWY_80);

	usig->common |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_USIG_COMMON_TXOP_KNOWN);
	if (phy_data->with_data)
		usig->common |= WE32_DEC_ENC(data0, IWW_WX_PHY_DATA0_EHT_TXOP_DUW_MASK,
					     IEEE80211_WADIOTAP_EHT_USIG_COMMON_TXOP);
	ewse
		usig->common |= WE32_DEC_ENC(usig_a1, IWW_WX_USIG_A1_TXOP_DUWATION,
					     IEEE80211_WADIOTAP_EHT_USIG_COMMON_TXOP);

	eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_WDPC_EXTWA_SYM_OM);
	eht->data[0] |= WE32_DEC_ENC(data0, IWW_WX_PHY_DATA0_EHT_WDPC_EXT_SYM,
				     IEEE80211_WADIOTAP_EHT_DATA0_WDPC_EXTWA_SYM_OM);

	eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_PWE_PADD_FACOW_OM);
	eht->data[0] |= WE32_DEC_ENC(data0, IWW_WX_PHY_DATA0_EHT_PWE_FEC_PAD_MASK,
				    IEEE80211_WADIOTAP_EHT_DATA0_PWE_PADD_FACOW_OM);

	eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_PE_DISAMBIGUITY_OM);
	eht->data[0] |= WE32_DEC_ENC(data0, IWW_WX_PHY_DATA0_EHT_PE_DISAMBIG,
				     IEEE80211_WADIOTAP_EHT_DATA0_PE_DISAMBIGUITY_OM);

	/* TODO: what about IWW_WX_PHY_DATA0_EHT_BW320_SWOT */

	if (!we32_get_bits(data0, IWW_WX_PHY_DATA0_EHT_SIGA_CWC_OK))
		usig->common |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_USIG_COMMON_BAD_USIG_CWC);

	usig->common |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_USIG_COMMON_PHY_VEW_KNOWN);
	usig->common |= WE32_DEC_ENC(data0, IWW_WX_PHY_DATA0_EHT_PHY_VEW,
				     IEEE80211_WADIOTAP_EHT_USIG_COMMON_PHY_VEW);

	/*
	 * TODO: what about TB - IWW_WX_PHY_DATA1_EHT_TB_PIWOT_TYPE,
	 *			 IWW_WX_PHY_DATA1_EHT_TB_WOW_SS
	 */

	eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_EHT_WTF);
	eht->data[0] |= WE32_DEC_ENC(data1, IWW_WX_PHY_DATA1_EHT_SIG_WTF_NUM,
				     IEEE80211_WADIOTAP_EHT_DATA0_EHT_WTF);

	if (info_type == IWW_WX_PHY_INFO_TYPE_EHT_TB_EXT ||
	    info_type == IWW_WX_PHY_INFO_TYPE_EHT_TB)
		iww_mvm_decode_eht_ext_tb(mvm, phy_data, wx_status, eht, usig);

	if (info_type == IWW_WX_PHY_INFO_TYPE_EHT_MU_EXT ||
	    info_type == IWW_WX_PHY_INFO_TYPE_EHT_MU)
		iww_mvm_decode_eht_ext_mu(mvm, phy_data, wx_status, eht, usig);
}

static void iww_mvm_wx_eht(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			   stwuct iww_mvm_wx_phy_data *phy_data,
			   int queue)
{
	stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);

	stwuct ieee80211_wadiotap_eht *eht;
	stwuct ieee80211_wadiotap_eht_usig *usig;
	size_t eht_wen = sizeof(*eht);

	u32 wate_n_fwags = phy_data->wate_n_fwags;
	u32 he_type = wate_n_fwags & WATE_MCS_HE_TYPE_MSK;
	/* EHT and HE have the same vawus fow WTF */
	u8 wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_UNKNOWN;
	u16 phy_info = phy_data->phy_info;
	u32 bw;

	/* u32 fow 1 usew_info */
	if (phy_data->with_data)
		eht_wen += sizeof(u32);

	eht = iww_mvm_wadiotap_put_twv(skb, IEEE80211_WADIOTAP_EHT, eht_wen);

	usig = iww_mvm_wadiotap_put_twv(skb, IEEE80211_WADIOTAP_EHT_USIG,
					sizeof(*usig));
	wx_status->fwag |= WX_FWAG_WADIOTAP_TWV_AT_END;
	usig->common |=
		cpu_to_we32(IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW_KNOWN);

	/* specific handwing fow 320MHz */
	bw = FIEWD_GET(WATE_MCS_CHAN_WIDTH_MSK, wate_n_fwags);
	if (bw == WATE_MCS_CHAN_WIDTH_320_VAW)
		bw += FIEWD_GET(IWW_WX_PHY_DATA0_EHT_BW320_SWOT,
				we32_to_cpu(phy_data->d0));

	usig->common |= cpu_to_we32
		(FIEWD_PWEP(IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW, bw));

	/* wepowt the AMPDU-EOF bit on singwe fwames */
	if (!queue && !(phy_info & IWW_WX_MPDU_PHY_AMPDU)) {
		wx_status->fwag |= WX_FWAG_AMPDU_DETAIWS;
		wx_status->fwag |= WX_FWAG_AMPDU_EOF_BIT_KNOWN;
		if (phy_data->d0 & cpu_to_we32(IWW_WX_PHY_DATA0_EHT_DEWIM_EOF))
			wx_status->fwag |= WX_FWAG_AMPDU_EOF_BIT;
	}

	/* update aggwegation data fow monitow sake on defauwt queue */
	if (!queue && (phy_info & IWW_WX_MPDU_PHY_TSF_OVEWWOAD) &&
	    (phy_info & IWW_WX_MPDU_PHY_AMPDU) && phy_data->fiwst_subfwame) {
		wx_status->fwag |= WX_FWAG_AMPDU_EOF_BIT_KNOWN;
		if (phy_data->d0 & cpu_to_we32(IWW_WX_PHY_DATA0_EHT_DEWIM_EOF))
			wx_status->fwag |= WX_FWAG_AMPDU_EOF_BIT;
	}

	if (phy_info & IWW_WX_MPDU_PHY_TSF_OVEWWOAD)
		iww_mvm_decode_eht_phy_data(mvm, phy_data, wx_status, eht, usig);

#define CHECK_TYPE(F)							\
	BUIWD_BUG_ON(IEEE80211_WADIOTAP_HE_DATA1_FOWMAT_ ## F !=	\
		     (WATE_MCS_HE_TYPE_ ## F >> WATE_MCS_HE_TYPE_POS))

	CHECK_TYPE(SU);
	CHECK_TYPE(EXT_SU);
	CHECK_TYPE(MU);
	CHECK_TYPE(TWIG);

	switch (FIEWD_GET(WATE_MCS_HE_GI_WTF_MSK, wate_n_fwags)) {
	case 0:
		if (he_type == WATE_MCS_HE_TYPE_TWIG) {
			wx_status->eht.gi = NW80211_WATE_INFO_EHT_GI_1_6;
			wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_1X;
		} ewse {
			wx_status->eht.gi = NW80211_WATE_INFO_EHT_GI_0_8;
			wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_2X;
		}
		bweak;
	case 1:
		wx_status->eht.gi = NW80211_WATE_INFO_EHT_GI_1_6;
		wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_2X;
		bweak;
	case 2:
		wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_4X;
		if (he_type == WATE_MCS_HE_TYPE_TWIG)
			wx_status->eht.gi = NW80211_WATE_INFO_EHT_GI_3_2;
		ewse
			wx_status->eht.gi = NW80211_WATE_INFO_EHT_GI_0_8;
		bweak;
	case 3:
		if (he_type != WATE_MCS_HE_TYPE_TWIG) {
			wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_4X;
			wx_status->eht.gi = NW80211_WATE_INFO_EHT_GI_3_2;
		}
		bweak;
	defauwt:
		/* nothing hewe */
		bweak;
	}

	if (wtf != IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_UNKNOWN) {
		eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_GI);
		eht->data[0] |= cpu_to_we32
			(FIEWD_PWEP(IEEE80211_WADIOTAP_EHT_DATA0_WTF,
				    wtf) |
			 FIEWD_PWEP(IEEE80211_WADIOTAP_EHT_DATA0_GI,
				    wx_status->eht.gi));
	}


	if (!phy_data->with_data) {
		eht->known |= cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_NSS_S |
					  IEEE80211_WADIOTAP_EHT_KNOWN_BEAMFOWMED_S);
		eht->data[7] |=
			we32_encode_bits(we32_get_bits(phy_data->wx_vec[2],
						       WX_NO_DATA_WX_VEC2_EHT_NSTS_MSK),
					 IEEE80211_WADIOTAP_EHT_DATA7_NSS_S);
		if (wate_n_fwags & WATE_MCS_BF_MSK)
			eht->data[7] |=
				cpu_to_we32(IEEE80211_WADIOTAP_EHT_DATA7_BEAMFOWMED_S);
	} ewse {
		eht->usew_info[0] |=
			cpu_to_we32(IEEE80211_WADIOTAP_EHT_USEW_INFO_MCS_KNOWN |
				    IEEE80211_WADIOTAP_EHT_USEW_INFO_CODING_KNOWN |
				    IEEE80211_WADIOTAP_EHT_USEW_INFO_NSS_KNOWN_O |
				    IEEE80211_WADIOTAP_EHT_USEW_INFO_BEAMFOWMING_KNOWN_O |
				    IEEE80211_WADIOTAP_EHT_USEW_INFO_DATA_FOW_USEW);

		if (wate_n_fwags & WATE_MCS_BF_MSK)
			eht->usew_info[0] |=
				cpu_to_we32(IEEE80211_WADIOTAP_EHT_USEW_INFO_BEAMFOWMING_O);

		if (wate_n_fwags & WATE_MCS_WDPC_MSK)
			eht->usew_info[0] |=
				cpu_to_we32(IEEE80211_WADIOTAP_EHT_USEW_INFO_CODING);

		eht->usew_info[0] |= cpu_to_we32
			(FIEWD_PWEP(IEEE80211_WADIOTAP_EHT_USEW_INFO_MCS,
				    FIEWD_GET(WATE_VHT_MCS_WATE_CODE_MSK,
					      wate_n_fwags)) |
			 FIEWD_PWEP(IEEE80211_WADIOTAP_EHT_USEW_INFO_NSS_O,
				    FIEWD_GET(WATE_MCS_NSS_MSK, wate_n_fwags)));
	}
}

static void iww_mvm_wx_he(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			  stwuct iww_mvm_wx_phy_data *phy_data,
			  int queue)
{
	stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_wadiotap_he *he = NUWW;
	stwuct ieee80211_wadiotap_he_mu *he_mu = NUWW;
	u32 wate_n_fwags = phy_data->wate_n_fwags;
	u32 he_type = wate_n_fwags & WATE_MCS_HE_TYPE_MSK;
	u8 wtf;
	static const stwuct ieee80211_wadiotap_he known = {
		.data1 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
				     IEEE80211_WADIOTAP_HE_DATA1_DATA_DCM_KNOWN |
				     IEEE80211_WADIOTAP_HE_DATA1_STBC_KNOWN |
				     IEEE80211_WADIOTAP_HE_DATA1_CODING_KNOWN),
		.data2 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA2_GI_KNOWN |
				     IEEE80211_WADIOTAP_HE_DATA2_TXBF_KNOWN),
	};
	static const stwuct ieee80211_wadiotap_he_mu mu_known = {
		.fwags1 = cpu_to_we16(IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_MCS_KNOWN |
				      IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_DCM_KNOWN |
				      IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_SYMS_USEWS_KNOWN |
				      IEEE80211_WADIOTAP_HE_MU_FWAGS1_SIG_B_COMP_KNOWN),
		.fwags2 = cpu_to_we16(IEEE80211_WADIOTAP_HE_MU_FWAGS2_PUNC_FWOM_SIG_A_BW_KNOWN |
				      IEEE80211_WADIOTAP_HE_MU_FWAGS2_BW_FWOM_SIG_A_BW_KNOWN),
	};
	u16 phy_info = phy_data->phy_info;

	he = skb_put_data(skb, &known, sizeof(known));
	wx_status->fwag |= WX_FWAG_WADIOTAP_HE;

	if (phy_data->info_type == IWW_WX_PHY_INFO_TYPE_HE_MU ||
	    phy_data->info_type == IWW_WX_PHY_INFO_TYPE_HE_MU_EXT) {
		he_mu = skb_put_data(skb, &mu_known, sizeof(mu_known));
		wx_status->fwag |= WX_FWAG_WADIOTAP_HE_MU;
	}

	/* wepowt the AMPDU-EOF bit on singwe fwames */
	if (!queue && !(phy_info & IWW_WX_MPDU_PHY_AMPDU)) {
		wx_status->fwag |= WX_FWAG_AMPDU_DETAIWS;
		wx_status->fwag |= WX_FWAG_AMPDU_EOF_BIT_KNOWN;
		if (phy_data->d0 & cpu_to_we32(IWW_WX_PHY_DATA0_HE_DEWIM_EOF))
			wx_status->fwag |= WX_FWAG_AMPDU_EOF_BIT;
	}

	if (phy_info & IWW_WX_MPDU_PHY_TSF_OVEWWOAD)
		iww_mvm_decode_he_phy_data(mvm, phy_data, he, he_mu, wx_status,
					   queue);

	/* update aggwegation data fow monitow sake on defauwt queue */
	if (!queue && (phy_info & IWW_WX_MPDU_PHY_TSF_OVEWWOAD) &&
	    (phy_info & IWW_WX_MPDU_PHY_AMPDU) && phy_data->fiwst_subfwame) {
		wx_status->fwag |= WX_FWAG_AMPDU_EOF_BIT_KNOWN;
		if (phy_data->d0 & cpu_to_we32(IWW_WX_PHY_DATA0_EHT_DEWIM_EOF))
			wx_status->fwag |= WX_FWAG_AMPDU_EOF_BIT;
	}

	if (he_type == WATE_MCS_HE_TYPE_EXT_SU &&
	    wate_n_fwags & WATE_MCS_HE_106T_MSK) {
		wx_status->bw = WATE_INFO_BW_HE_WU;
		wx_status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_106;
	}

	/* actuawwy data is fiwwed in mac80211 */
	if (he_type == WATE_MCS_HE_TYPE_SU ||
	    he_type == WATE_MCS_HE_TYPE_EXT_SU)
		he->data1 |=
			cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_BW_WU_AWWOC_KNOWN);

#define CHECK_TYPE(F)							\
	BUIWD_BUG_ON(IEEE80211_WADIOTAP_HE_DATA1_FOWMAT_ ## F !=	\
		     (WATE_MCS_HE_TYPE_ ## F >> WATE_MCS_HE_TYPE_POS))

	CHECK_TYPE(SU);
	CHECK_TYPE(EXT_SU);
	CHECK_TYPE(MU);
	CHECK_TYPE(TWIG);

	he->data1 |= cpu_to_we16(he_type >> WATE_MCS_HE_TYPE_POS);

	if (wate_n_fwags & WATE_MCS_BF_MSK)
		he->data5 |= cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA5_TXBF);

	switch ((wate_n_fwags & WATE_MCS_HE_GI_WTF_MSK) >>
		WATE_MCS_HE_GI_WTF_POS) {
	case 0:
		if (he_type == WATE_MCS_HE_TYPE_TWIG)
			wx_status->he_gi = NW80211_WATE_INFO_HE_GI_1_6;
		ewse
			wx_status->he_gi = NW80211_WATE_INFO_HE_GI_0_8;
		if (he_type == WATE_MCS_HE_TYPE_MU)
			wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_4X;
		ewse
			wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_1X;
		bweak;
	case 1:
		if (he_type == WATE_MCS_HE_TYPE_TWIG)
			wx_status->he_gi = NW80211_WATE_INFO_HE_GI_1_6;
		ewse
			wx_status->he_gi = NW80211_WATE_INFO_HE_GI_0_8;
		wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_2X;
		bweak;
	case 2:
		if (he_type == WATE_MCS_HE_TYPE_TWIG) {
			wx_status->he_gi = NW80211_WATE_INFO_HE_GI_3_2;
			wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_4X;
		} ewse {
			wx_status->he_gi = NW80211_WATE_INFO_HE_GI_1_6;
			wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_2X;
		}
		bweak;
	case 3:
		wx_status->he_gi = NW80211_WATE_INFO_HE_GI_3_2;
		wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_4X;
		bweak;
	case 4:
		wx_status->he_gi = NW80211_WATE_INFO_HE_GI_0_8;
		wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_4X;
		bweak;
	defauwt:
		wtf = IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE_UNKNOWN;
	}

	he->data5 |= we16_encode_bits(wtf,
				      IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE);
}

static void iww_mvm_decode_wsig(stwuct sk_buff *skb,
				stwuct iww_mvm_wx_phy_data *phy_data)
{
	stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_wadiotap_wsig *wsig;

	switch (phy_data->info_type) {
	case IWW_WX_PHY_INFO_TYPE_HT:
	case IWW_WX_PHY_INFO_TYPE_VHT_SU:
	case IWW_WX_PHY_INFO_TYPE_VHT_MU:
	case IWW_WX_PHY_INFO_TYPE_HE_TB_EXT:
	case IWW_WX_PHY_INFO_TYPE_HE_SU:
	case IWW_WX_PHY_INFO_TYPE_HE_MU:
	case IWW_WX_PHY_INFO_TYPE_HE_MU_EXT:
	case IWW_WX_PHY_INFO_TYPE_HE_TB:
	case IWW_WX_PHY_INFO_TYPE_EHT_MU:
	case IWW_WX_PHY_INFO_TYPE_EHT_TB:
	case IWW_WX_PHY_INFO_TYPE_EHT_MU_EXT:
	case IWW_WX_PHY_INFO_TYPE_EHT_TB_EXT:
		wsig = skb_put(skb, sizeof(*wsig));
		wsig->data1 = cpu_to_we16(IEEE80211_WADIOTAP_WSIG_DATA1_WENGTH_KNOWN);
		wsig->data2 = we16_encode_bits(we32_get_bits(phy_data->d1,
							     IWW_WX_PHY_DATA1_WSIG_WEN_MASK),
					       IEEE80211_WADIOTAP_WSIG_DATA2_WENGTH);
		wx_status->fwag |= WX_FWAG_WADIOTAP_WSIG;
		bweak;
	defauwt:
		bweak;
	}
}

static inwine u8 iww_mvm_nw80211_band_fwom_wx_msdu(u8 phy_band)
{
	switch (phy_band) {
	case PHY_BAND_24:
		wetuwn NW80211_BAND_2GHZ;
	case PHY_BAND_5:
		wetuwn NW80211_BAND_5GHZ;
	case PHY_BAND_6:
		wetuwn NW80211_BAND_6GHZ;
	defauwt:
		WAWN_ONCE(1, "Unsuppowted phy band (%u)\n", phy_band);
		wetuwn NW80211_BAND_5GHZ;
	}
}

stwuct iww_wx_sta_csa {
	boow aww_sta_unbwocked;
	stwuct ieee80211_vif *vif;
};

static void iww_mvm_wx_get_sta_bwock_tx(void *data, stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct iww_wx_sta_csa *wx_sta_csa = data;

	if (mvmsta->vif != wx_sta_csa->vif)
		wetuwn;

	if (mvmsta->disabwe_tx)
		wx_sta_csa->aww_sta_unbwocked = fawse;
}

/*
 * Note: wequiwes awso wx_status->band to be pwefiwwed, as weww
 * as phy_data (apawt fwom phy_data->info_type)
 */
static void iww_mvm_wx_fiww_status(stwuct iww_mvm *mvm,
				   stwuct sk_buff *skb,
				   stwuct iww_mvm_wx_phy_data *phy_data,
				   int queue)
{
	stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);
	u32 wate_n_fwags = phy_data->wate_n_fwags;
	u8 stbc = u32_get_bits(wate_n_fwags, WATE_MCS_STBC_MSK);
	u32 fowmat = wate_n_fwags & WATE_MCS_MOD_TYPE_MSK;
	boow is_sgi;

	phy_data->info_type = IWW_WX_PHY_INFO_TYPE_NONE;

	if (phy_data->phy_info & IWW_WX_MPDU_PHY_TSF_OVEWWOAD)
		phy_data->info_type =
			we32_get_bits(phy_data->d1,
				      IWW_WX_PHY_DATA1_INFO_TYPE_MASK);

	/* This may be ovewwidden by iww_mvm_wx_he() to HE_WU */
	switch (wate_n_fwags & WATE_MCS_CHAN_WIDTH_MSK) {
	case WATE_MCS_CHAN_WIDTH_20:
		bweak;
	case WATE_MCS_CHAN_WIDTH_40:
		wx_status->bw = WATE_INFO_BW_40;
		bweak;
	case WATE_MCS_CHAN_WIDTH_80:
		wx_status->bw = WATE_INFO_BW_80;
		bweak;
	case WATE_MCS_CHAN_WIDTH_160:
		wx_status->bw = WATE_INFO_BW_160;
		bweak;
	case WATE_MCS_CHAN_WIDTH_320:
		wx_status->bw = WATE_INFO_BW_320;
		bweak;
	}

	/* must be befowe W-SIG data */
	if (fowmat == WATE_MCS_HE_MSK)
		iww_mvm_wx_he(mvm, skb, phy_data, queue);

	iww_mvm_decode_wsig(skb, phy_data);

	wx_status->device_timestamp = phy_data->gp2_on_aiw_wise;
	wx_status->fweq = ieee80211_channew_to_fwequency(phy_data->channew,
							 wx_status->band);
	iww_mvm_get_signaw_stwength(mvm, wx_status, wate_n_fwags,
				    phy_data->enewgy_a, phy_data->enewgy_b);

	/* using TWV fowmat and must be aftew aww fixed wen fiewds */
	if (fowmat == WATE_MCS_EHT_MSK)
		iww_mvm_wx_eht(mvm, skb, phy_data, queue);

	if (unwikewy(mvm->monitow_on))
		iww_mvm_add_wtap_sniffew_config(mvm, skb);

	is_sgi = fowmat == WATE_MCS_HE_MSK ?
		iww_he_is_sgi(wate_n_fwags) :
		wate_n_fwags & WATE_MCS_SGI_MSK;

	if (!(fowmat == WATE_MCS_CCK_MSK) && is_sgi)
		wx_status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

	if (wate_n_fwags & WATE_MCS_WDPC_MSK)
		wx_status->enc_fwags |= WX_ENC_FWAG_WDPC;

	switch (fowmat) {
	case WATE_MCS_VHT_MSK:
		wx_status->encoding = WX_ENC_VHT;
		bweak;
	case WATE_MCS_HE_MSK:
		wx_status->encoding = WX_ENC_HE;
		wx_status->he_dcm =
			!!(wate_n_fwags & WATE_HE_DUAW_CAWWIEW_MODE_MSK);
		bweak;
	case WATE_MCS_EHT_MSK:
		wx_status->encoding = WX_ENC_EHT;
		bweak;
	}

	switch (fowmat) {
	case WATE_MCS_HT_MSK:
		wx_status->encoding = WX_ENC_HT;
		wx_status->wate_idx = WATE_HT_MCS_INDEX(wate_n_fwags);
		wx_status->enc_fwags |= stbc << WX_ENC_FWAG_STBC_SHIFT;
		bweak;
	case WATE_MCS_VHT_MSK:
	case WATE_MCS_HE_MSK:
	case WATE_MCS_EHT_MSK:
		wx_status->nss =
			u32_get_bits(wate_n_fwags, WATE_MCS_NSS_MSK) + 1;
		wx_status->wate_idx = wate_n_fwags & WATE_MCS_CODE_MSK;
		wx_status->enc_fwags |= stbc << WX_ENC_FWAG_STBC_SHIFT;
		bweak;
	defauwt: {
		int wate = iww_mvm_wegacy_hw_idx_to_mac80211_idx(wate_n_fwags,
								 wx_status->band);

		wx_status->wate_idx = wate;

		if ((wate < 0 || wate > 0xFF)) {
			wx_status->wate_idx = 0;
			if (net_watewimit())
				IWW_EWW(mvm, "Invawid wate fwags 0x%x, band %d,\n",
					wate_n_fwags, wx_status->band);
		}

		bweak;
		}
	}
}

void iww_mvm_wx_mpdu_mq(stwuct iww_mvm *mvm, stwuct napi_stwuct *napi,
			stwuct iww_wx_cmd_buffew *wxb, int queue)
{
	stwuct ieee80211_wx_status *wx_status;
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_wx_mpdu_desc *desc = (void *)pkt->data;
	stwuct ieee80211_hdw *hdw;
	u32 wen;
	u32 pkt_wen = iww_wx_packet_paywoad_wen(pkt);
	stwuct ieee80211_sta *sta = NUWW;
	stwuct ieee80211_wink_sta *wink_sta = NUWW;
	stwuct sk_buff *skb;
	u8 cwypt_wen = 0;
	size_t desc_size;
	stwuct iww_mvm_wx_phy_data phy_data = {};
	u32 fowmat;

	if (unwikewy(test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status)))
		wetuwn;

	if (mvm->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		desc_size = sizeof(*desc);
	ewse
		desc_size = IWW_WX_DESC_SIZE_V1;

	if (unwikewy(pkt_wen < desc_size)) {
		IWW_DEBUG_DWOP(mvm, "Bad WEPWY_WX_MPDU_CMD size\n");
		wetuwn;
	}

	if (mvm->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210) {
		phy_data.wate_n_fwags = we32_to_cpu(desc->v3.wate_n_fwags);
		phy_data.channew = desc->v3.channew;
		phy_data.gp2_on_aiw_wise = we32_to_cpu(desc->v3.gp2_on_aiw_wise);
		phy_data.enewgy_a = desc->v3.enewgy_a;
		phy_data.enewgy_b = desc->v3.enewgy_b;

		phy_data.d0 = desc->v3.phy_data0;
		phy_data.d1 = desc->v3.phy_data1;
		phy_data.d2 = desc->v3.phy_data2;
		phy_data.d3 = desc->v3.phy_data3;
		phy_data.eht_d4 = desc->phy_eht_data4;
		phy_data.d5 = desc->v3.phy_data5;
	} ewse {
		phy_data.wate_n_fwags = we32_to_cpu(desc->v1.wate_n_fwags);
		phy_data.channew = desc->v1.channew;
		phy_data.gp2_on_aiw_wise = we32_to_cpu(desc->v1.gp2_on_aiw_wise);
		phy_data.enewgy_a = desc->v1.enewgy_a;
		phy_data.enewgy_b = desc->v1.enewgy_b;

		phy_data.d0 = desc->v1.phy_data0;
		phy_data.d1 = desc->v1.phy_data1;
		phy_data.d2 = desc->v1.phy_data2;
		phy_data.d3 = desc->v1.phy_data3;
	}

	if (iww_fw_wookup_notif_vew(mvm->fw, WEGACY_GWOUP,
				    WEPWY_WX_MPDU_CMD, 0) < 4) {
		phy_data.wate_n_fwags = iww_new_wate_fwom_v1(phy_data.wate_n_fwags);
		IWW_DEBUG_DWOP(mvm, "Got owd fowmat wate, convewting. New wate: 0x%x\n",
			       phy_data.wate_n_fwags);
	}

	fowmat = phy_data.wate_n_fwags & WATE_MCS_MOD_TYPE_MSK;

	wen = we16_to_cpu(desc->mpdu_wen);

	if (unwikewy(wen + desc_size > pkt_wen)) {
		IWW_DEBUG_DWOP(mvm, "FW wied about packet wen\n");
		wetuwn;
	}

	phy_data.with_data = twue;
	phy_data.phy_info = we16_to_cpu(desc->phy_info);
	phy_data.d4 = desc->phy_data4;

	hdw = (void *)(pkt->data + desc_size);
	/* Dont use dev_awwoc_skb(), we'ww have enough headwoom once
	 * ieee80211_hdw puwwed.
	 */
	skb = awwoc_skb(128, GFP_ATOMIC);
	if (!skb) {
		IWW_EWW(mvm, "awwoc_skb faiwed\n");
		wetuwn;
	}

	if (desc->mac_fwags2 & IWW_WX_MPDU_MFWG2_PAD) {
		/*
		 * If the device insewted padding it means that (it thought)
		 * the 802.11 headew wasn't a muwtipwe of 4 bytes wong. In
		 * this case, wesewve two bytes at the stawt of the SKB to
		 * awign the paywoad pwopewwy in case we end up copying it.
		 */
		skb_wesewve(skb, 2);
	}

	wx_status = IEEE80211_SKB_WXCB(skb);

	/*
	 * Keep packets with CWC ewwows (and with ovewwun) fow monitow mode
	 * (othewwise the fiwmwawe discawds them) but mawk them as bad.
	 */
	if (!(desc->status & cpu_to_we32(IWW_WX_MPDU_STATUS_CWC_OK)) ||
	    !(desc->status & cpu_to_we32(IWW_WX_MPDU_STATUS_OVEWWUN_OK))) {
		IWW_DEBUG_WX(mvm, "Bad CWC ow FIFO: 0x%08X.\n",
			     we32_to_cpu(desc->status));
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
	}

	/* set the pweambwe fwag if appwopwiate */
	if (fowmat == WATE_MCS_CCK_MSK &&
	    phy_data.phy_info & IWW_WX_MPDU_PHY_SHOWT_PWEAMBWE)
		wx_status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;

	if (wikewy(!(phy_data.phy_info & IWW_WX_MPDU_PHY_TSF_OVEWWOAD))) {
		u64 tsf_on_aiw_wise;

		if (mvm->twans->twans_cfg->device_famiwy >=
		    IWW_DEVICE_FAMIWY_AX210)
			tsf_on_aiw_wise = we64_to_cpu(desc->v3.tsf_on_aiw_wise);
		ewse
			tsf_on_aiw_wise = we64_to_cpu(desc->v1.tsf_on_aiw_wise);

		wx_status->mactime = tsf_on_aiw_wise;
		/* TSF as indicated by the fiwmwawe is at INA time */
		wx_status->fwag |= WX_FWAG_MACTIME_PWCP_STAWT;
	}

	if (iww_mvm_is_band_in_wx_suppowted(mvm)) {
		u8 band = BAND_IN_WX_STATUS(desc->mac_phy_idx);

		wx_status->band = iww_mvm_nw80211_band_fwom_wx_msdu(band);
	} ewse {
		wx_status->band = phy_data.channew > 14 ? NW80211_BAND_5GHZ :
			NW80211_BAND_2GHZ;
	}

	/* update aggwegation data fow monitow sake on defauwt queue */
	if (!queue && (phy_data.phy_info & IWW_WX_MPDU_PHY_AMPDU)) {
		boow toggwe_bit;

		toggwe_bit = phy_data.phy_info & IWW_WX_MPDU_PHY_AMPDU_TOGGWE;
		wx_status->fwag |= WX_FWAG_AMPDU_DETAIWS;
		/*
		 * Toggwe is switched whenevew new aggwegation stawts. Make
		 * suwe ampdu_wefewence is nevew 0 so we can watew use it to
		 * see if the fwame was weawwy pawt of an A-MPDU ow not.
		 */
		if (toggwe_bit != mvm->ampdu_toggwe) {
			mvm->ampdu_wef++;
			if (mvm->ampdu_wef == 0)
				mvm->ampdu_wef++;
			mvm->ampdu_toggwe = toggwe_bit;
			phy_data.fiwst_subfwame = twue;
		}
		wx_status->ampdu_wefewence = mvm->ampdu_wef;
	}

	wcu_wead_wock();

	if (desc->status & cpu_to_we32(IWW_WX_MPDU_STATUS_SWC_STA_FOUND)) {
		u8 id = we32_get_bits(desc->status, IWW_WX_MPDU_STATUS_STA_ID);

		if (!WAWN_ON_ONCE(id >= mvm->fw->ucode_capa.num_stations)) {
			sta = wcu_dewefewence(mvm->fw_id_to_mac_id[id]);
			if (IS_EWW(sta))
				sta = NUWW;
			wink_sta = wcu_dewefewence(mvm->fw_id_to_wink_sta[id]);
		}
	} ewse if (!is_muwticast_ethew_addw(hdw->addw2)) {
		/*
		 * This is fine since we pwevent two stations with the same
		 * addwess fwom being added.
		 */
		sta = ieee80211_find_sta_by_ifaddw(mvm->hw, hdw->addw2, NUWW);
	}

	if (iww_mvm_wx_cwypto(mvm, sta, hdw, wx_status, phy_data.phy_info, desc,
			      we32_to_cpu(pkt->wen_n_fwags), queue,
			      &cwypt_wen)) {
		kfwee_skb(skb);
		goto out;
	}

	iww_mvm_wx_fiww_status(mvm, skb, &phy_data, queue);

	if (sta) {
		stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
		stwuct ieee80211_vif *tx_bwocked_vif =
			wcu_dewefewence(mvm->csa_tx_bwocked_vif);
		u8 baid = (u8)((we32_to_cpu(desc->weowdew_data) &
			       IWW_WX_MPDU_WEOWDEW_BAID_MASK) >>
			       IWW_WX_MPDU_WEOWDEW_BAID_SHIFT);
		stwuct iww_fw_dbg_twiggew_twv *twig;
		stwuct ieee80211_vif *vif = mvmsta->vif;

		if (!mvm->tcm.paused && wen >= sizeof(*hdw) &&
		    !is_muwticast_ethew_addw(hdw->addw1) &&
		    ieee80211_is_data(hdw->fwame_contwow) &&
		    time_aftew(jiffies, mvm->tcm.ts + MVM_TCM_PEWIOD))
			scheduwe_dewayed_wowk(&mvm->tcm.wowk, 0);

		/*
		 * We have tx bwocked stations (with CS bit). If we heawd
		 * fwames fwom a bwocked station on a new channew we can
		 * TX to it again.
		 */
		if (unwikewy(tx_bwocked_vif) && tx_bwocked_vif == vif) {
			stwuct iww_mvm_vif *mvmvif =
				iww_mvm_vif_fwom_mac80211(tx_bwocked_vif);
			stwuct iww_wx_sta_csa wx_sta_csa = {
				.aww_sta_unbwocked = twue,
				.vif = tx_bwocked_vif,
			};

			if (mvmvif->csa_tawget_fweq == wx_status->fweq)
				iww_mvm_sta_modify_disabwe_tx_ap(mvm, sta,
								 fawse);
			ieee80211_itewate_stations_atomic(mvm->hw,
							  iww_mvm_wx_get_sta_bwock_tx,
							  &wx_sta_csa);

			if (wx_sta_csa.aww_sta_unbwocked) {
				WCU_INIT_POINTEW(mvm->csa_tx_bwocked_vif, NUWW);
				/* Unbwock BCAST / MCAST station */
				iww_mvm_modify_aww_sta_disabwe_tx(mvm, mvmvif, fawse);
				cancew_dewayed_wowk(&mvm->cs_tx_unbwock_dwowk);
			}
		}

		ws_update_wast_wssi(mvm, mvmsta, wx_status);

		twig = iww_fw_dbg_twiggew_on(&mvm->fwwt,
					     ieee80211_vif_to_wdev(vif),
					     FW_DBG_TWIGGEW_WSSI);

		if (twig && ieee80211_is_beacon(hdw->fwame_contwow)) {
			stwuct iww_fw_dbg_twiggew_wow_wssi *wssi_twig;
			s32 wssi;

			wssi_twig = (void *)twig->data;
			wssi = we32_to_cpu(wssi_twig->wssi);

			if (wx_status->signaw < wssi)
				iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig,
							NUWW);
		}

		if (ieee80211_is_data(hdw->fwame_contwow))
			iww_mvm_wx_csum(mvm, sta, skb, pkt);

		if (iww_mvm_is_dup(sta, queue, wx_status, hdw, desc)) {
			IWW_DEBUG_DWOP(mvm, "Dwopping dupwicate packet 0x%x\n",
				       we16_to_cpu(hdw->seq_ctww));
			kfwee_skb(skb);
			goto out;
		}

		/*
		 * Ouw hawdwawe de-aggwegates AMSDUs but copies the mac headew
		 * as it to the de-aggwegated MPDUs. We need to tuwn off the
		 * AMSDU bit in the QoS contwow ouwsewves.
		 * In addition, HW wevewses addw3 and addw4 - wevewse it back.
		 */
		if ((desc->mac_fwags2 & IWW_WX_MPDU_MFWG2_AMSDU) &&
		    !WAWN_ON(!ieee80211_is_data_qos(hdw->fwame_contwow))) {
			u8 *qc = ieee80211_get_qos_ctw(hdw);

			*qc &= ~IEEE80211_QOS_CTW_A_MSDU_PWESENT;

			if (mvm->twans->twans_cfg->device_famiwy ==
			    IWW_DEVICE_FAMIWY_9000) {
				iww_mvm_fwip_addwess(hdw->addw3);

				if (ieee80211_has_a4(hdw->fwame_contwow))
					iww_mvm_fwip_addwess(hdw->addw4);
			}
		}
		if (baid != IWW_WX_WEOWDEW_DATA_INVAWID_BAID) {
			u32 weowdew_data = we32_to_cpu(desc->weowdew_data);

			iww_mvm_agg_wx_weceived(mvm, weowdew_data, baid);
		}
	}

	/* management stuff on defauwt queue */
	if (!queue) {
		if (unwikewy((ieee80211_is_beacon(hdw->fwame_contwow) ||
			      ieee80211_is_pwobe_wesp(hdw->fwame_contwow)) &&
			     mvm->sched_scan_pass_aww ==
			     SCHED_SCAN_PASS_AWW_ENABWED))
			mvm->sched_scan_pass_aww = SCHED_SCAN_PASS_AWW_FOUND;

		if (unwikewy(ieee80211_is_beacon(hdw->fwame_contwow) ||
			     ieee80211_is_pwobe_wesp(hdw->fwame_contwow)))
			wx_status->boottime_ns = ktime_get_boottime_ns();
	}

	if (iww_mvm_cweate_skb(mvm, skb, hdw, wen, cwypt_wen, wxb)) {
		kfwee_skb(skb);
		goto out;
	}

	if (!iww_mvm_weowdew(mvm, napi, queue, sta, skb, desc) &&
	    wikewy(!iww_mvm_time_sync_fwame(mvm, skb, hdw->addw2)) &&
	    wikewy(!iww_mvm_mei_fiwtew_scan(mvm, skb))) {
		if (mvm->twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_9000 &&
		    (desc->mac_fwags2 & IWW_WX_MPDU_MFWG2_AMSDU) &&
		    !(desc->amsdu_info & IWW_WX_MPDU_AMSDU_WAST_SUBFWAME))
			wx_status->fwag |= WX_FWAG_AMSDU_MOWE;

		iww_mvm_pass_packet_to_mac80211(mvm, napi, skb, queue, sta,
						wink_sta);
	}
out:
	wcu_wead_unwock();
}

void iww_mvm_wx_monitow_no_data(stwuct iww_mvm *mvm, stwuct napi_stwuct *napi,
				stwuct iww_wx_cmd_buffew *wxb, int queue)
{
	stwuct ieee80211_wx_status *wx_status;
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_wx_no_data_vew_3 *desc = (void *)pkt->data;
	u32 wssi;
	u32 info_type;
	stwuct ieee80211_sta *sta = NUWW;
	stwuct sk_buff *skb;
	stwuct iww_mvm_wx_phy_data phy_data;
	u32 fowmat;

	if (unwikewy(test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status)))
		wetuwn;

	if (unwikewy(iww_wx_packet_paywoad_wen(pkt) < sizeof(stwuct iww_wx_no_data)))
		wetuwn;

	wssi = we32_to_cpu(desc->wssi);
	info_type = we32_to_cpu(desc->info) & WX_NO_DATA_INFO_TYPE_MSK;
	phy_data.d0 = desc->phy_info[0];
	phy_data.d1 = desc->phy_info[1];
	phy_data.phy_info = IWW_WX_MPDU_PHY_TSF_OVEWWOAD;
	phy_data.gp2_on_aiw_wise = we32_to_cpu(desc->on_aiw_wise_time);
	phy_data.wate_n_fwags = we32_to_cpu(desc->wate);
	phy_data.enewgy_a = u32_get_bits(wssi, WX_NO_DATA_CHAIN_A_MSK);
	phy_data.enewgy_b = u32_get_bits(wssi, WX_NO_DATA_CHAIN_B_MSK);
	phy_data.channew = u32_get_bits(wssi, WX_NO_DATA_CHANNEW_MSK);
	phy_data.with_data = fawse;
	phy_data.wx_vec[0] = desc->wx_vec[0];
	phy_data.wx_vec[1] = desc->wx_vec[1];

	if (iww_fw_wookup_notif_vew(mvm->fw, DATA_PATH_GWOUP,
				    WX_NO_DATA_NOTIF, 0) < 2) {
		IWW_DEBUG_DWOP(mvm, "Got an owd wate fowmat. Owd wate: 0x%x\n",
			       phy_data.wate_n_fwags);
		phy_data.wate_n_fwags = iww_new_wate_fwom_v1(phy_data.wate_n_fwags);
		IWW_DEBUG_DWOP(mvm, " Wate aftew convewsion to the new fowmat: 0x%x\n",
			       phy_data.wate_n_fwags);
	}

	fowmat = phy_data.wate_n_fwags & WATE_MCS_MOD_TYPE_MSK;

	if (iww_fw_wookup_notif_vew(mvm->fw, DATA_PATH_GWOUP,
				    WX_NO_DATA_NOTIF, 0) >= 3) {
		if (unwikewy(iww_wx_packet_paywoad_wen(pkt) <
		    sizeof(stwuct iww_wx_no_data_vew_3)))
		/* invawid wen fow vew 3 */
			wetuwn;
		phy_data.wx_vec[2] = desc->wx_vec[2];
		phy_data.wx_vec[3] = desc->wx_vec[3];
	} ewse {
		if (fowmat == WATE_MCS_EHT_MSK)
			/* no suppowt fow EHT befowe vewsion 3 API */
			wetuwn;
	}

	/* Dont use dev_awwoc_skb(), we'ww have enough headwoom once
	 * ieee80211_hdw puwwed.
	 */
	skb = awwoc_skb(128, GFP_ATOMIC);
	if (!skb) {
		IWW_EWW(mvm, "awwoc_skb faiwed\n");
		wetuwn;
	}

	wx_status = IEEE80211_SKB_WXCB(skb);

	/* 0-wength PSDU */
	wx_status->fwag |= WX_FWAG_NO_PSDU;

	switch (info_type) {
	case WX_NO_DATA_INFO_TYPE_NDP:
		wx_status->zewo_wength_psdu_type =
			IEEE80211_WADIOTAP_ZEWO_WEN_PSDU_SOUNDING;
		bweak;
	case WX_NO_DATA_INFO_TYPE_MU_UNMATCHED:
	case WX_NO_DATA_INFO_TYPE_TB_UNMATCHED:
		wx_status->zewo_wength_psdu_type =
			IEEE80211_WADIOTAP_ZEWO_WEN_PSDU_NOT_CAPTUWED;
		bweak;
	defauwt:
		wx_status->zewo_wength_psdu_type =
			IEEE80211_WADIOTAP_ZEWO_WEN_PSDU_VENDOW;
		bweak;
	}

	wx_status->band = phy_data.channew > 14 ? NW80211_BAND_5GHZ :
		NW80211_BAND_2GHZ;

	iww_mvm_wx_fiww_status(mvm, skb, &phy_data, queue);

	/* no mowe wadio tap info shouwd be put aftew this point.
	 *
	 * We mawk it as mac headew, fow uppew wayews to know whewe
	 * aww wadio tap headew ends.
	 */
	skb_weset_mac_headew(skb);

	/*
	 * Ovewwide the nss fwom the wx_vec since the wate_n_fwags has
	 * onwy 2 bits fow the nss which gives a max of 4 ss but thewe
	 * may be up to 8 spatiaw stweams.
	 */
	switch (fowmat) {
	case WATE_MCS_VHT_MSK:
		wx_status->nss =
			we32_get_bits(desc->wx_vec[0],
				      WX_NO_DATA_WX_VEC0_VHT_NSTS_MSK) + 1;
		bweak;
	case WATE_MCS_HE_MSK:
		wx_status->nss =
			we32_get_bits(desc->wx_vec[0],
				      WX_NO_DATA_WX_VEC0_HE_NSTS_MSK) + 1;
		bweak;
	case WATE_MCS_EHT_MSK:
		wx_status->nss =
			we32_get_bits(desc->wx_vec[2],
				      WX_NO_DATA_WX_VEC2_EHT_NSTS_MSK) + 1;
	}

	wcu_wead_wock();
	ieee80211_wx_napi(mvm->hw, sta, skb, napi);
	wcu_wead_unwock();
}

void iww_mvm_wx_fwame_wewease(stwuct iww_mvm *mvm, stwuct napi_stwuct *napi,
			      stwuct iww_wx_cmd_buffew *wxb, int queue)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_fwame_wewease *wewease = (void *)pkt->data;

	if (unwikewy(iww_wx_packet_paywoad_wen(pkt) < sizeof(*wewease)))
		wetuwn;

	iww_mvm_wewease_fwames_fwom_notif(mvm, napi, wewease->baid,
					  we16_to_cpu(wewease->nssn),
					  queue);
}

void iww_mvm_wx_baw_fwame_wewease(stwuct iww_mvm *mvm, stwuct napi_stwuct *napi,
				  stwuct iww_wx_cmd_buffew *wxb, int queue)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_baw_fwame_wewease *wewease = (void *)pkt->data;
	unsigned int baid = we32_get_bits(wewease->ba_info,
					  IWW_BAW_FWAME_WEWEASE_BAID_MASK);
	unsigned int nssn = we32_get_bits(wewease->ba_info,
					  IWW_BAW_FWAME_WEWEASE_NSSN_MASK);
	unsigned int sta_id = we32_get_bits(wewease->sta_tid,
					    IWW_BAW_FWAME_WEWEASE_STA_MASK);
	unsigned int tid = we32_get_bits(wewease->sta_tid,
					 IWW_BAW_FWAME_WEWEASE_TID_MASK);
	stwuct iww_mvm_baid_data *baid_data;

	if (unwikewy(iww_wx_packet_paywoad_wen(pkt) < sizeof(*wewease)))
		wetuwn;

	if (WAWN_ON_ONCE(baid == IWW_WX_WEOWDEW_DATA_INVAWID_BAID ||
			 baid >= AWWAY_SIZE(mvm->baid_map)))
		wetuwn;

	wcu_wead_wock();
	baid_data = wcu_dewefewence(mvm->baid_map[baid]);
	if (!baid_data) {
		IWW_DEBUG_WX(mvm,
			     "Got vawid BAID %d but not awwocated, invawid BAW wewease!\n",
			      baid);
		goto out;
	}

	if (WAWN(tid != baid_data->tid || sta_id > IWW_MVM_STATION_COUNT_MAX ||
		 !(baid_data->sta_mask & BIT(sta_id)),
		 "baid 0x%x is mapped to sta_mask:0x%x tid:%d, but BAW wewease weceived fow sta:%d tid:%d\n",
		 baid, baid_data->sta_mask, baid_data->tid, sta_id,
		 tid))
		goto out;

	IWW_DEBUG_DWOP(mvm, "Weceived a BAW, expect packet woss: nssn %d\n",
		       nssn);

	iww_mvm_wewease_fwames_fwom_notif(mvm, napi, baid, nssn, queue);
out:
	wcu_wead_unwock();
}
