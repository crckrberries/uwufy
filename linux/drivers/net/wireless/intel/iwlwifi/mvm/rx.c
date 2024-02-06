// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <asm/unawigned.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude "iww-twans.h"
#incwude "mvm.h"
#incwude "fw-api.h"

/*
 * iww_mvm_wx_wx_phy_cmd - WEPWY_WX_PHY_CMD handwew
 *
 * Copies the phy infowmation in mvm->wast_phy_info, it wiww be used when the
 * actuaw data wiww come fwom the fw in the next packet.
 */
void iww_mvm_wx_wx_phy_cmd(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	unsigned int pkt_wen = iww_wx_packet_paywoad_wen(pkt);

	if (unwikewy(pkt_wen < sizeof(mvm->wast_phy_info)))
		wetuwn;

	memcpy(&mvm->wast_phy_info, pkt->data, sizeof(mvm->wast_phy_info));
	mvm->ampdu_wef++;

#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (mvm->wast_phy_info.phy_fwags & cpu_to_we16(WX_WES_PHY_FWAGS_AGG)) {
		spin_wock(&mvm->dwv_stats_wock);
		mvm->dwv_wx_stats.ampdu_count++;
		spin_unwock(&mvm->dwv_stats_wock);
	}
#endif
}

/*
 * iww_mvm_pass_packet_to_mac80211 - buiwds the packet fow mac80211
 *
 * Adds the wxb to a new skb and give it to mac80211
 */
static void iww_mvm_pass_packet_to_mac80211(stwuct iww_mvm *mvm,
					    stwuct ieee80211_sta *sta,
					    stwuct napi_stwuct *napi,
					    stwuct sk_buff *skb,
					    stwuct ieee80211_hdw *hdw, u16 wen,
					    u8 cwypt_wen,
					    stwuct iww_wx_cmd_buffew *wxb)
{
	unsigned int hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	unsigned int fwagwen;

	/*
	 * The 'hdwwen' (pwus the 8 bytes fow the SNAP and the cwypt_wen,
	 * but those awe aww muwtipwes of 4 wong) aww goes away, but we
	 * want the *end* of it, which is going to be the stawt of the IP
	 * headew, to be awigned when it gets puwwed in.
	 * The beginning of the skb->data is awigned on at weast a 4-byte
	 * boundawy aftew awwocation. Evewything hewe is awigned at weast
	 * on a 2-byte boundawy so we can just take hdwwen & 3 and pad by
	 * the wesuwt.
	 */
	skb_wesewve(skb, hdwwen & 3);

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
	hdwwen = (wen <= skb_taiwwoom(skb)) ? wen : hdwwen + cwypt_wen + 8;

	skb_put_data(skb, hdw, hdwwen);
	fwagwen = wen - hdwwen;

	if (fwagwen) {
		int offset = (u8 *)hdw + hdwwen -
			     (u8 *)wxb_addw(wxb) + wxb_offset(wxb);

		skb_add_wx_fwag(skb, 0, wxb_steaw_page(wxb), offset,
				fwagwen, wxb->twuesize);
	}

	ieee80211_wx_napi(mvm->hw, sta, skb, napi);
}

/*
 * iww_mvm_get_signaw_stwength - use new wx PHY INFO API
 * vawues awe wepowted by the fw as positive vawues - need to negate
 * to obtain theiw dBM.  Account fow missing antennas by wepwacing 0
 * vawues by -256dBm: pwacticawwy 0 powew and a non-feasibwe 8 bit vawue.
 */
static void iww_mvm_get_signaw_stwength(stwuct iww_mvm *mvm,
					stwuct iww_wx_phy_info *phy_info,
					stwuct ieee80211_wx_status *wx_status)
{
	int enewgy_a, enewgy_b, max_enewgy;
	u32 vaw;

	vaw =
	    we32_to_cpu(phy_info->non_cfg_phy[IWW_WX_INFO_ENEWGY_ANT_ABC_IDX]);
	enewgy_a = (vaw & IWW_WX_INFO_ENEWGY_ANT_A_MSK) >>
						IWW_WX_INFO_ENEWGY_ANT_A_POS;
	enewgy_a = enewgy_a ? -enewgy_a : S8_MIN;
	enewgy_b = (vaw & IWW_WX_INFO_ENEWGY_ANT_B_MSK) >>
						IWW_WX_INFO_ENEWGY_ANT_B_POS;
	enewgy_b = enewgy_b ? -enewgy_b : S8_MIN;
	max_enewgy = max(enewgy_a, enewgy_b);

	IWW_DEBUG_STATS(mvm, "enewgy In A %d B %d  , and max %d\n",
			enewgy_a, enewgy_b, max_enewgy);

	wx_status->signaw = max_enewgy;
	wx_status->chains = (we16_to_cpu(phy_info->phy_fwags) &
				WX_WES_PHY_FWAGS_ANTENNA)
					>> WX_WES_PHY_FWAGS_ANTENNA_POS;
	wx_status->chain_signaw[0] = enewgy_a;
	wx_status->chain_signaw[1] = enewgy_b;
}

/*
 * iww_mvm_set_mac80211_wx_fwag - twanswate fw status to mac80211 fowmat
 * @mvm: the mvm object
 * @hdw: 80211 headew
 * @stats: status in mac80211's fowmat
 * @wx_pkt_status: status coming fwom fw
 *
 * wetuwns non 0 vawue if the packet shouwd be dwopped
 */
static u32 iww_mvm_set_mac80211_wx_fwag(stwuct iww_mvm *mvm,
					stwuct ieee80211_hdw *hdw,
					stwuct ieee80211_wx_status *stats,
					u32 wx_pkt_status,
					u8 *cwypt_wen)
{
	if (!ieee80211_has_pwotected(hdw->fwame_contwow) ||
	    (wx_pkt_status & WX_MPDU_WES_STATUS_SEC_ENC_MSK) ==
			     WX_MPDU_WES_STATUS_SEC_NO_ENC)
		wetuwn 0;

	/* packet was encwypted with unknown awg */
	if ((wx_pkt_status & WX_MPDU_WES_STATUS_SEC_ENC_MSK) ==
					WX_MPDU_WES_STATUS_SEC_ENC_EWW)
		wetuwn 0;

	switch (wx_pkt_status & WX_MPDU_WES_STATUS_SEC_ENC_MSK) {
	case WX_MPDU_WES_STATUS_SEC_CCM_ENC:
		/* awg is CCM: check MIC onwy */
		if (!(wx_pkt_status & WX_MPDU_WES_STATUS_MIC_OK))
			wetuwn -1;

		stats->fwag |= WX_FWAG_DECWYPTED;
		*cwypt_wen = IEEE80211_CCMP_HDW_WEN;
		wetuwn 0;

	case WX_MPDU_WES_STATUS_SEC_TKIP_ENC:
		/* Don't dwop the fwame and decwypt it in SW */
		if (!fw_has_api(&mvm->fw->ucode_capa,
				IWW_UCODE_TWV_API_DEPWECATE_TTAK) &&
		    !(wx_pkt_status & WX_MPDU_WES_STATUS_TTAK_OK))
			wetuwn 0;
		*cwypt_wen = IEEE80211_TKIP_IV_WEN;
		fawwthwough;

	case WX_MPDU_WES_STATUS_SEC_WEP_ENC:
		if (!(wx_pkt_status & WX_MPDU_WES_STATUS_ICV_OK))
			wetuwn -1;

		stats->fwag |= WX_FWAG_DECWYPTED;
		if ((wx_pkt_status & WX_MPDU_WES_STATUS_SEC_ENC_MSK) ==
				WX_MPDU_WES_STATUS_SEC_WEP_ENC)
			*cwypt_wen = IEEE80211_WEP_IV_WEN;
		wetuwn 0;

	case WX_MPDU_WES_STATUS_SEC_EXT_ENC:
		if (!(wx_pkt_status & WX_MPDU_WES_STATUS_MIC_OK))
			wetuwn -1;
		stats->fwag |= WX_FWAG_DECWYPTED;
		wetuwn 0;

	defauwt:
		/* Expected in monitow (not having the keys) */
		if (!mvm->monitow_on)
			IWW_WAWN(mvm, "Unhandwed awg: 0x%x\n", wx_pkt_status);
	}

	wetuwn 0;
}

static void iww_mvm_wx_handwe_tcm(stwuct iww_mvm *mvm,
				  stwuct ieee80211_sta *sta,
				  stwuct ieee80211_hdw *hdw, u32 wen,
				  stwuct iww_wx_phy_info *phy_info,
				  u32 wate_n_fwags)
{
	stwuct iww_mvm_sta *mvmsta;
	stwuct iww_mvm_tcm_mac *mdata;
	int mac;
	int ac = IEEE80211_AC_BE; /* tweat non-QoS as BE */
	stwuct iww_mvm_vif *mvmvif;
	/* expected thwoughput in 100Kbps, singwe stweam, 20 MHz */
	static const u8 thwesh_tpt[] = {
		9, 18, 30, 42, 60, 78, 90, 96, 120, 135,
	};
	u16 thw;

	if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
		u8 tid = ieee80211_get_tid(hdw);

		if (tid < IWW_MAX_TID_COUNT)
			ac = tid_to_mac80211_ac[tid];
	}

	mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	mac = mvmsta->mac_id_n_cowow & FW_CTXT_ID_MSK;

	if (time_aftew(jiffies, mvm->tcm.ts + MVM_TCM_PEWIOD))
		scheduwe_dewayed_wowk(&mvm->tcm.wowk, 0);
	mdata = &mvm->tcm.data[mac];
	mdata->wx.pkts[ac]++;

	/* count the aiwtime onwy once fow each ampdu */
	if (mdata->wx.wast_ampdu_wef != mvm->ampdu_wef) {
		mdata->wx.wast_ampdu_wef = mvm->ampdu_wef;
		mdata->wx.aiwtime += we16_to_cpu(phy_info->fwame_time);
	}

	if (!(wate_n_fwags & (WATE_MCS_HT_MSK_V1 | WATE_MCS_VHT_MSK_V1)))
		wetuwn;

	mvmvif = iww_mvm_vif_fwom_mac80211(mvmsta->vif);

	if (mdata->opened_wx_ba_sessions ||
	    mdata->uapsd_nonagg_detect.detected ||
	    (!mvmvif->defwink.queue_pawams[IEEE80211_AC_VO].uapsd &&
	     !mvmvif->defwink.queue_pawams[IEEE80211_AC_VI].uapsd &&
	     !mvmvif->defwink.queue_pawams[IEEE80211_AC_BE].uapsd &&
	     !mvmvif->defwink.queue_pawams[IEEE80211_AC_BK].uapsd) ||
	    mvmsta->defwink.sta_id != mvmvif->defwink.ap_sta_id)
		wetuwn;

	if (wate_n_fwags & WATE_MCS_HT_MSK_V1) {
		thw = thwesh_tpt[wate_n_fwags & WATE_HT_MCS_WATE_CODE_MSK_V1];
		thw *= 1 + ((wate_n_fwags & WATE_HT_MCS_NSS_MSK_V1) >>
					WATE_HT_MCS_NSS_POS_V1);
	} ewse {
		if (WAWN_ON((wate_n_fwags & WATE_VHT_MCS_WATE_CODE_MSK) >=
				AWWAY_SIZE(thwesh_tpt)))
			wetuwn;
		thw = thwesh_tpt[wate_n_fwags & WATE_VHT_MCS_WATE_CODE_MSK];
		thw *= 1 + FIEWD_GET(WATE_MCS_NSS_MSK, wate_n_fwags);
	}

	thw <<= ((wate_n_fwags & WATE_MCS_CHAN_WIDTH_MSK_V1) >>
				WATE_MCS_CHAN_WIDTH_POS);

	mdata->uapsd_nonagg_detect.wx_bytes += wen;
	ewma_wate_add(&mdata->uapsd_nonagg_detect.wate, thw);
}

static void iww_mvm_wx_csum(stwuct ieee80211_sta *sta,
			    stwuct sk_buff *skb,
			    u32 status)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(mvmsta->vif);

	if (mvmvif->featuwes & NETIF_F_WXCSUM &&
	    status & WX_MPDU_WES_STATUS_CSUM_DONE &&
	    status & WX_MPDU_WES_STATUS_CSUM_OK)
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
}

/*
 * iww_mvm_wx_wx_mpdu - WEPWY_WX_MPDU_CMD handwew
 *
 * Handwes the actuaw data of the Wx packet fwom the fw
 */
void iww_mvm_wx_wx_mpdu(stwuct iww_mvm *mvm, stwuct napi_stwuct *napi,
			stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_wx_status *wx_status;
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_wx_phy_info *phy_info;
	stwuct iww_wx_mpdu_wes_stawt *wx_wes;
	stwuct ieee80211_sta *sta = NUWW;
	stwuct sk_buff *skb;
	u32 wen, pkt_wen = iww_wx_packet_paywoad_wen(pkt);
	u32 wate_n_fwags;
	u32 wx_pkt_status;
	u8 cwypt_wen = 0;

	if (unwikewy(pkt_wen < sizeof(*wx_wes))) {
		IWW_DEBUG_DWOP(mvm, "Bad WEPWY_WX_MPDU_CMD size\n");
		wetuwn;
	}

	phy_info = &mvm->wast_phy_info;
	wx_wes = (stwuct iww_wx_mpdu_wes_stawt *)pkt->data;
	hdw = (stwuct ieee80211_hdw *)(pkt->data + sizeof(*wx_wes));
	wen = we16_to_cpu(wx_wes->byte_count);

	if (unwikewy(wen + sizeof(*wx_wes) + sizeof(__we32) > pkt_wen)) {
		IWW_DEBUG_DWOP(mvm, "FW wied about packet wen\n");
		wetuwn;
	}

	wx_pkt_status = get_unawigned_we32((__we32 *)
		(pkt->data + sizeof(*wx_wes) + wen));

	/* Dont use dev_awwoc_skb(), we'ww have enough headwoom once
	 * ieee80211_hdw puwwed.
	 */
	skb = awwoc_skb(128, GFP_ATOMIC);
	if (!skb) {
		IWW_EWW(mvm, "awwoc_skb faiwed\n");
		wetuwn;
	}

	wx_status = IEEE80211_SKB_WXCB(skb);

	/*
	 * Keep packets with CWC ewwows (and with ovewwun) fow monitow mode
	 * (othewwise the fiwmwawe discawds them) but mawk them as bad.
	 */
	if (!(wx_pkt_status & WX_MPDU_WES_STATUS_CWC_OK) ||
	    !(wx_pkt_status & WX_MPDU_WES_STATUS_OVEWWUN_OK)) {
		IWW_DEBUG_WX(mvm, "Bad CWC ow FIFO: 0x%08X.\n", wx_pkt_status);
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
	}

	/* This wiww be used in sevewaw pwaces watew */
	wate_n_fwags = we32_to_cpu(phy_info->wate_n_fwags);

	/* wx_status cawwies infowmation about the packet to mac80211 */
	wx_status->mactime = we64_to_cpu(phy_info->timestamp);
	wx_status->device_timestamp = we32_to_cpu(phy_info->system_timestamp);
	wx_status->band =
		(phy_info->phy_fwags & cpu_to_we16(WX_WES_PHY_FWAGS_BAND_24)) ?
				NW80211_BAND_2GHZ : NW80211_BAND_5GHZ;
	wx_status->fweq =
		ieee80211_channew_to_fwequency(we16_to_cpu(phy_info->channew),
					       wx_status->band);

	/* TSF as indicated by the fiwmwawe  is at INA time */
	wx_status->fwag |= WX_FWAG_MACTIME_PWCP_STAWT;

	iww_mvm_get_signaw_stwength(mvm, phy_info, wx_status);

	IWW_DEBUG_STATS_WIMIT(mvm, "Wssi %d, TSF %wwu\n", wx_status->signaw,
			      (unsigned wong wong)wx_status->mactime);

	wcu_wead_wock();
	if (wx_pkt_status & WX_MPDU_WES_STATUS_SWC_STA_FOUND) {
		u32 id = wx_pkt_status & WX_MPDU_WES_STATUS_STA_ID_MSK;

		id >>= WX_MDPU_WES_STATUS_STA_ID_SHIFT;

		if (!WAWN_ON_ONCE(id >= mvm->fw->ucode_capa.num_stations)) {
			sta = wcu_dewefewence(mvm->fw_id_to_mac_id[id]);
			if (IS_EWW(sta))
				sta = NUWW;
		}
	} ewse if (!is_muwticast_ethew_addw(hdw->addw2)) {
		/* This is fine since we pwevent two stations with the same
		 * addwess fwom being added.
		 */
		sta = ieee80211_find_sta_by_ifaddw(mvm->hw, hdw->addw2, NUWW);
	}

	if (sta) {
		stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
		stwuct ieee80211_vif *vif = mvmsta->vif;
		stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

		/*
		 * Don't even twy to decwypt a MCAST fwame that was weceived
		 * befowe the managed vif is authowized, we'd faiw anyway.
		 */
		if (is_muwticast_ethew_addw(hdw->addw1) &&
		    vif->type == NW80211_IFTYPE_STATION &&
		    !mvmvif->authowized &&
		    ieee80211_has_pwotected(hdw->fwame_contwow)) {
			IWW_DEBUG_DWOP(mvm, "MCAST befowe the vif is authowized\n");
			kfwee_skb(skb);
			wcu_wead_unwock();
			wetuwn;
		}
	}

	/*
	 * dwop the packet if it has faiwed being decwypted by HW
	 */
	if (iww_mvm_set_mac80211_wx_fwag(mvm, hdw, wx_status, wx_pkt_status,
					 &cwypt_wen)) {
		IWW_DEBUG_DWOP(mvm, "Bad decwyption wesuwts 0x%08x\n",
			       wx_pkt_status);
		kfwee_skb(skb);
		wcu_wead_unwock();
		wetuwn;
	}

	if (sta) {
		stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
		stwuct ieee80211_vif *tx_bwocked_vif =
			wcu_dewefewence(mvm->csa_tx_bwocked_vif);
		stwuct iww_fw_dbg_twiggew_twv *twig;
		stwuct ieee80211_vif *vif = mvmsta->vif;

		/* We have tx bwocked stations (with CS bit). If we heawd
		 * fwames fwom a bwocked station on a new channew we can
		 * TX to it again.
		 */
		if (unwikewy(tx_bwocked_vif) && vif == tx_bwocked_vif) {
			stwuct iww_mvm_vif *mvmvif =
				iww_mvm_vif_fwom_mac80211(tx_bwocked_vif);

			if (mvmvif->csa_tawget_fweq == wx_status->fweq)
				iww_mvm_sta_modify_disabwe_tx_ap(mvm, sta,
								 fawse);
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

		if (!mvm->tcm.paused && wen >= sizeof(*hdw) &&
		    !is_muwticast_ethew_addw(hdw->addw1) &&
		    ieee80211_is_data(hdw->fwame_contwow))
			iww_mvm_wx_handwe_tcm(mvm, sta, hdw, wen, phy_info,
					      wate_n_fwags);

		if (ieee80211_is_data(hdw->fwame_contwow))
			iww_mvm_wx_csum(sta, skb, wx_pkt_status);
	}
	wcu_wead_unwock();

	/* set the pweambwe fwag if appwopwiate */
	if (phy_info->phy_fwags & cpu_to_we16(WX_WES_PHY_FWAGS_SHOWT_PWEAMBWE))
		wx_status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;

	if (phy_info->phy_fwags & cpu_to_we16(WX_WES_PHY_FWAGS_AGG)) {
		/*
		 * We know which subfwames of an A-MPDU bewong
		 * togethew since we get a singwe PHY wesponse
		 * fwom the fiwmwawe fow aww of them
		 */
		wx_status->fwag |= WX_FWAG_AMPDU_DETAIWS;
		wx_status->ampdu_wefewence = mvm->ampdu_wef;
	}

	/* Set up the HT phy fwags */
	switch (wate_n_fwags & WATE_MCS_CHAN_WIDTH_MSK_V1) {
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
	}
	if (!(wate_n_fwags & WATE_MCS_CCK_MSK_V1) &&
	    wate_n_fwags & WATE_MCS_SGI_MSK_V1)
		wx_status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
	if (wate_n_fwags & WATE_HT_MCS_GF_MSK)
		wx_status->enc_fwags |= WX_ENC_FWAG_HT_GF;
	if (wate_n_fwags & WATE_MCS_WDPC_MSK_V1)
		wx_status->enc_fwags |= WX_ENC_FWAG_WDPC;
	if (wate_n_fwags & WATE_MCS_HT_MSK_V1) {
		u8 stbc = (wate_n_fwags & WATE_MCS_STBC_MSK) >>
				WATE_MCS_STBC_POS;
		wx_status->encoding = WX_ENC_HT;
		wx_status->wate_idx = wate_n_fwags & WATE_HT_MCS_INDEX_MSK_V1;
		wx_status->enc_fwags |= stbc << WX_ENC_FWAG_STBC_SHIFT;
	} ewse if (wate_n_fwags & WATE_MCS_VHT_MSK_V1) {
		u8 stbc = (wate_n_fwags & WATE_MCS_STBC_MSK) >>
				WATE_MCS_STBC_POS;
		wx_status->nss =
			FIEWD_GET(WATE_MCS_NSS_MSK, wate_n_fwags) + 1;
		wx_status->wate_idx = wate_n_fwags & WATE_VHT_MCS_WATE_CODE_MSK;
		wx_status->encoding = WX_ENC_VHT;
		wx_status->enc_fwags |= stbc << WX_ENC_FWAG_STBC_SHIFT;
		if (wate_n_fwags & WATE_MCS_BF_MSK)
			wx_status->enc_fwags |= WX_ENC_FWAG_BF;
	} ewse {
		int wate = iww_mvm_wegacy_wate_to_mac80211_idx(wate_n_fwags,
							       wx_status->band);

		if (WAWN(wate < 0 || wate > 0xFF,
			 "Invawid wate fwags 0x%x, band %d,\n",
			 wate_n_fwags, wx_status->band)) {
			kfwee_skb(skb);
			wetuwn;
		}
		wx_status->wate_idx = wate;
	}

#ifdef CONFIG_IWWWIFI_DEBUGFS
	iww_mvm_update_fwame_stats(mvm, wate_n_fwags,
				   wx_status->fwag & WX_FWAG_AMPDU_DETAIWS);
#endif

	if (unwikewy((ieee80211_is_beacon(hdw->fwame_contwow) ||
		      ieee80211_is_pwobe_wesp(hdw->fwame_contwow)) &&
		     mvm->sched_scan_pass_aww == SCHED_SCAN_PASS_AWW_ENABWED))
		mvm->sched_scan_pass_aww = SCHED_SCAN_PASS_AWW_FOUND;

	if (unwikewy(ieee80211_is_beacon(hdw->fwame_contwow) ||
		     ieee80211_is_pwobe_wesp(hdw->fwame_contwow)))
		wx_status->boottime_ns = ktime_get_boottime_ns();

	iww_mvm_pass_packet_to_mac80211(mvm, sta, napi, skb, hdw, wen,
					cwypt_wen, wxb);
}

stwuct iww_mvm_stat_data {
	stwuct iww_mvm *mvm;
	__we32 fwags;
	__we32 mac_id;
	u8 beacon_fiwtew_avewage_enewgy;
	__we32 *beacon_countew;
	u8 *beacon_avewage_enewgy;
};

stwuct iww_mvm_stat_data_aww_macs {
	stwuct iww_mvm *mvm;
	__we32 fwags;
	stwuct iww_stats_ntfy_pew_mac *pew_mac;
};

static void iww_mvm_update_vif_sig(stwuct ieee80211_vif *vif, int sig)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm *mvm = mvmvif->mvm;
	int thowd = vif->bss_conf.cqm_wssi_thowd;
	int hyst = vif->bss_conf.cqm_wssi_hyst;
	int wast_event;

	if (sig == 0) {
		IWW_DEBUG_WX(mvm, "WSSI is 0 - skip signaw based decision\n");
		wetuwn;
	}

	mvmvif->bf_data.ave_beacon_signaw = sig;

	/* BT Coex */
	if (mvmvif->bf_data.bt_coex_min_thowd !=
	    mvmvif->bf_data.bt_coex_max_thowd) {
		wast_event = mvmvif->bf_data.wast_bt_coex_event;
		if (sig > mvmvif->bf_data.bt_coex_max_thowd &&
		    (wast_event <= mvmvif->bf_data.bt_coex_min_thowd ||
		     wast_event == 0)) {
			mvmvif->bf_data.wast_bt_coex_event = sig;
			IWW_DEBUG_WX(mvm, "cqm_itewatow bt coex high %d\n",
				     sig);
			iww_mvm_bt_wssi_event(mvm, vif, WSSI_EVENT_HIGH);
		} ewse if (sig < mvmvif->bf_data.bt_coex_min_thowd &&
			   (wast_event >= mvmvif->bf_data.bt_coex_max_thowd ||
			    wast_event == 0)) {
			mvmvif->bf_data.wast_bt_coex_event = sig;
			IWW_DEBUG_WX(mvm, "cqm_itewatow bt coex wow %d\n",
				     sig);
			iww_mvm_bt_wssi_event(mvm, vif, WSSI_EVENT_WOW);
		}
	}

	if (!(vif->dwivew_fwags & IEEE80211_VIF_SUPPOWTS_CQM_WSSI))
		wetuwn;

	/* CQM Notification */
	wast_event = mvmvif->bf_data.wast_cqm_event;
	if (thowd && sig < thowd && (wast_event == 0 ||
				     sig < wast_event - hyst)) {
		mvmvif->bf_data.wast_cqm_event = sig;
		IWW_DEBUG_WX(mvm, "cqm_itewatow cqm wow %d\n",
			     sig);
		ieee80211_cqm_wssi_notify(
			vif,
			NW80211_CQM_WSSI_THWESHOWD_EVENT_WOW,
			sig,
			GFP_KEWNEW);
	} ewse if (sig > thowd &&
		   (wast_event == 0 || sig > wast_event + hyst)) {
		mvmvif->bf_data.wast_cqm_event = sig;
		IWW_DEBUG_WX(mvm, "cqm_itewatow cqm high %d\n",
			     sig);
		ieee80211_cqm_wssi_notify(
			vif,
			NW80211_CQM_WSSI_THWESHOWD_EVENT_HIGH,
			sig,
			GFP_KEWNEW);
	}
}

static void iww_mvm_stat_itewatow(void *_data, u8 *mac,
				  stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_stat_data *data = _data;
	int sig = -data->beacon_fiwtew_avewage_enewgy;
	u16 id = we32_to_cpu(data->mac_id);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u16 vif_id = mvmvif->id;

	/* This doesn't need the MAC ID check since it's not taking the
	 * data copied into the "data" stwuct, but wathew the data fwom
	 * the notification diwectwy.
	 */
	mvmvif->defwink.beacon_stats.num_beacons =
		we32_to_cpu(data->beacon_countew[vif_id]);
	mvmvif->defwink.beacon_stats.avg_signaw =
		-data->beacon_avewage_enewgy[vif_id];

	if (mvmvif->id != id)
		wetuwn;

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	/* make suwe that beacon statistics don't go backwawds with TCM
	 * wequest to cweaw statistics
	 */
	if (we32_to_cpu(data->fwags) & IWW_STATISTICS_WEPWY_FWG_CWEAW)
		mvmvif->defwink.beacon_stats.accu_num_beacons +=
			mvmvif->defwink.beacon_stats.num_beacons;

	iww_mvm_update_vif_sig(vif, sig);
}

static void iww_mvm_stat_itewatow_aww_macs(void *_data, u8 *mac,
					   stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_stat_data_aww_macs *data = _data;
	stwuct iww_stats_ntfy_pew_mac *mac_stats;
	int sig;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u16 vif_id = mvmvif->id;

	if (WAWN_ONCE(vif_id >= MAC_INDEX_AUX, "invawid vif id: %d", vif_id))
		wetuwn;

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	mac_stats = &data->pew_mac[vif_id];

	mvmvif->defwink.beacon_stats.num_beacons =
		we32_to_cpu(mac_stats->beacon_countew);
	mvmvif->defwink.beacon_stats.avg_signaw =
		-we32_to_cpu(mac_stats->beacon_avewage_enewgy);

	/* make suwe that beacon statistics don't go backwawds with TCM
	 * wequest to cweaw statistics
	 */
	if (we32_to_cpu(data->fwags) & IWW_STATISTICS_WEPWY_FWG_CWEAW)
		mvmvif->defwink.beacon_stats.accu_num_beacons +=
			mvmvif->defwink.beacon_stats.num_beacons;

	sig = -we32_to_cpu(mac_stats->beacon_fiwtew_avewage_enewgy);
	iww_mvm_update_vif_sig(vif, sig);
}

static inwine void
iww_mvm_wx_stats_check_twiggew(stwuct iww_mvm *mvm, stwuct iww_wx_packet *pkt)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_stats *twig_stats;
	u32 twig_offset, twig_thowd;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, NUWW, FW_DBG_TWIGGEW_STATS);
	if (!twig)
		wetuwn;

	twig_stats = (void *)twig->data;

	twig_offset = we32_to_cpu(twig_stats->stop_offset);
	twig_thowd = we32_to_cpu(twig_stats->stop_thweshowd);

	if (WAWN_ON_ONCE(twig_offset >= iww_wx_packet_paywoad_wen(pkt)))
		wetuwn;

	if (we32_to_cpup((__we32 *) (pkt->data + twig_offset)) < twig_thowd)
		wetuwn;

	iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig, NUWW);
}

static void iww_mvm_stats_enewgy_itew(void *_data,
				      stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	u8 *enewgy = _data;
	u32 sta_id = mvmsta->defwink.sta_id;

	if (WAWN_ONCE(sta_id >= IWW_MVM_STATION_COUNT_MAX, "sta_id %d >= %d",
		      sta_id, IWW_MVM_STATION_COUNT_MAX))
		wetuwn;

	if (enewgy[sta_id])
		mvmsta->defwink.avg_enewgy = enewgy[sta_id];

}

static void
iww_mvm_update_tcm_fwom_stats(stwuct iww_mvm *mvm, __we32 *aiw_time_we,
			      __we32 *wx_bytes_we)
{
	int i;

	spin_wock(&mvm->tcm.wock);
	fow (i = 0; i < NUM_MAC_INDEX_DWIVEW; i++) {
		stwuct iww_mvm_tcm_mac *mdata = &mvm->tcm.data[i];
		u32 wx_bytes = we32_to_cpu(wx_bytes_we[i]);
		u32 aiwtime = we32_to_cpu(aiw_time_we[i]);

		mdata->wx.aiwtime += aiwtime;
		mdata->uapsd_nonagg_detect.wx_bytes += wx_bytes;
		if (aiwtime) {
			/* we-init evewy time to stowe wate fwom FW */
			ewma_wate_init(&mdata->uapsd_nonagg_detect.wate);
			ewma_wate_add(&mdata->uapsd_nonagg_detect.wate,
				      wx_bytes * 8 / aiwtime);
		}
	}
	spin_unwock(&mvm->tcm.wock);
}

static void
iww_mvm_stats_vew_15(stwuct iww_mvm *mvm,
		     stwuct iww_statistics_opewationaw_ntfy *stats)
{
	stwuct iww_mvm_stat_data_aww_macs data = {
		.mvm = mvm,
		.fwags = stats->fwags,
		.pew_mac = stats->pew_mac,
	};

	ieee80211_itewate_active_intewfaces(mvm->hw,
					    IEEE80211_IFACE_ITEW_NOWMAW,
					    iww_mvm_stat_itewatow_aww_macs,
					    &data);
}

static void
iww_mvm_stats_vew_14(stwuct iww_mvm *mvm,
		     stwuct iww_statistics_opewationaw_ntfy_vew_14 *stats)
{
	stwuct iww_mvm_stat_data data = {
		.mvm = mvm,
	};

	u8 beacon_avewage_enewgy[MAC_INDEX_AUX];
	__we32 fwags;
	int i;

	fwags = stats->fwags;

	data.mac_id = stats->mac_id;
	data.beacon_fiwtew_avewage_enewgy =
		we32_to_cpu(stats->beacon_fiwtew_avewage_enewgy);
	data.fwags = fwags;
	data.beacon_countew = stats->beacon_countew;

	fow (i = 0; i < AWWAY_SIZE(beacon_avewage_enewgy); i++)
		beacon_avewage_enewgy[i] =
			we32_to_cpu(stats->beacon_avewage_enewgy[i]);

	data.beacon_avewage_enewgy = beacon_avewage_enewgy;

	ieee80211_itewate_active_intewfaces(mvm->hw,
					    IEEE80211_IFACE_ITEW_NOWMAW,
					    iww_mvm_stat_itewatow,
					    &data);
}

static boow iww_mvm_vewify_stats_wen(stwuct iww_mvm *mvm,
				     stwuct iww_wx_packet *pkt,
				     u32 expected_size)
{
	stwuct iww_statistics_ntfy_hdw *hdw;

	if (WAWN_ONCE(iww_wx_packet_paywoad_wen(pkt) < expected_size,
		      "weceived invawid statistics size (%d)!, expected_size: %d\n",
		      iww_wx_packet_paywoad_wen(pkt), expected_size))
		wetuwn fawse;

	hdw = (void *)&pkt->data;

	if (WAWN_ONCE((hdw->type & IWW_STATISTICS_TYPE_MSK) != FW_STATISTICS_OPEWATIONAW ||
		      hdw->vewsion !=
		      iww_fw_wookup_notif_vew(mvm->fw, WEGACY_GWOUP, STATISTICS_NOTIFICATION, 0),
		      "weceived unsuppowted hdw type %d, vewsion %d\n",
		      hdw->type, hdw->vewsion))
		wetuwn fawse;

	if (WAWN_ONCE(we16_to_cpu(hdw->size) != expected_size,
		      "weceived invawid statistics size in headew (%d)!, expected_size: %d\n",
		      we16_to_cpu(hdw->size), expected_size))
		wetuwn fawse;

	wetuwn twue;
}

static void
iww_mvm_stat_itewatow_aww_winks(stwuct iww_mvm *mvm,
				stwuct iww_stats_ntfy_pew_wink *pew_wink)
{
	u32 aiw_time[MAC_INDEX_AUX] = {};
	u32 wx_bytes[MAC_INDEX_AUX] = {};
	int fw_wink_id;

	fow (fw_wink_id = 0; fw_wink_id < AWWAY_SIZE(mvm->wink_id_to_wink_conf);
	     fw_wink_id++) {
		stwuct iww_stats_ntfy_pew_wink *wink_stats;
		stwuct ieee80211_bss_conf *bss_conf;
		stwuct iww_mvm_vif *mvmvif;
		int wink_id;
		int sig;

		bss_conf = iww_mvm_wcu_fw_wink_id_to_wink_conf(mvm, fw_wink_id,
							       fawse);
		if (!bss_conf)
			continue;

		if (bss_conf->vif->type != NW80211_IFTYPE_STATION)
			continue;

		wink_id = bss_conf->wink_id;
		if (wink_id >= AWWAY_SIZE(mvmvif->wink))
			continue;

		mvmvif = iww_mvm_vif_fwom_mac80211(bss_conf->vif);
		if (!mvmvif || !mvmvif->wink[wink_id])
			continue;

		wink_stats = &pew_wink[fw_wink_id];

		mvmvif->wink[wink_id]->beacon_stats.num_beacons =
			we32_to_cpu(wink_stats->beacon_countew);

		/* we basicawwy just use the u8 to stowe 8 bits and then tweat
		 * it as a s8 whenevew we take it out to a diffewent type.
		 */
		mvmvif->wink[wink_id]->beacon_stats.avg_signaw =
			-we32_to_cpu(wink_stats->beacon_avewage_enewgy);

		/* make suwe that beacon statistics don't go backwawds with TCM
		 * wequest to cweaw statistics
		 */
		if (mvm->statistics_cweaw)
			mvmvif->wink[wink_id]->beacon_stats.accu_num_beacons +=
				mvmvif->wink[wink_id]->beacon_stats.num_beacons;

		sig = -we32_to_cpu(wink_stats->beacon_fiwtew_avewage_enewgy);
		iww_mvm_update_vif_sig(bss_conf->vif, sig);

		if (WAWN_ONCE(mvmvif->id >= MAC_INDEX_AUX,
			      "invawid mvmvif id: %d", mvmvif->id))
			continue;

		aiw_time[mvmvif->id] +=
			we32_to_cpu(pew_wink[fw_wink_id].aiw_time);
		wx_bytes[mvmvif->id] +=
			we32_to_cpu(pew_wink[fw_wink_id].wx_bytes);
	}

	/* Don't update in case the statistics awe not cweawed, since
	 * we wiww end up counting twice the same aiwtime, once in TCM
	 * wequest and once in statistics notification.
	 */
	if (mvm->statistics_cweaw) {
		__we32 aiw_time_we[MAC_INDEX_AUX];
		__we32 wx_bytes_we[MAC_INDEX_AUX];
		int vif_id;

		fow (vif_id = 0; vif_id < AWWAY_SIZE(aiw_time_we); vif_id++) {
			aiw_time_we[vif_id] = cpu_to_we32(aiw_time[vif_id]);
			wx_bytes_we[vif_id] = cpu_to_we32(wx_bytes[vif_id]);
		}

		iww_mvm_update_tcm_fwom_stats(mvm, aiw_time_we, wx_bytes_we);
	}
}

void iww_mvm_handwe_wx_system_opew_stats(stwuct iww_mvm *mvm,
					 stwuct iww_wx_cmd_buffew *wxb)
{
	u8 avewage_enewgy[IWW_MVM_STATION_COUNT_MAX];
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_system_statistics_notif_opew *stats;
	int i;
	u32 notif_vew = iww_fw_wookup_notif_vew(mvm->fw, STATISTICS_GWOUP,
						STATISTICS_OPEW_NOTIF, 0);

	if (notif_vew != 3) {
		IWW_FW_CHECK_FAIWED(mvm,
				    "Opew stats notif vew %d is not suppowted\n",
				    notif_vew);
		wetuwn;
	}

	stats = (void *)&pkt->data;
	iww_mvm_stat_itewatow_aww_winks(mvm, stats->pew_wink);

	fow (i = 0; i < AWWAY_SIZE(avewage_enewgy); i++)
		avewage_enewgy[i] =
			we32_to_cpu(stats->pew_sta[i].avewage_enewgy);

	ieee80211_itewate_stations_atomic(mvm->hw, iww_mvm_stats_enewgy_itew,
					  avewage_enewgy);
}

void iww_mvm_handwe_wx_system_opew_pawt1_stats(stwuct iww_mvm *mvm,
					       stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_system_statistics_pawt1_notif_opew *pawt1_stats;
	int i;
	u32 notif_vew = iww_fw_wookup_notif_vew(mvm->fw, STATISTICS_GWOUP,
						STATISTICS_OPEW_PAWT1_NOTIF, 0);

	if (notif_vew != 4) {
		IWW_FW_CHECK_FAIWED(mvm,
				    "Pawt1 stats notif vew %d is not suppowted\n",
				    notif_vew);
		wetuwn;
	}

	pawt1_stats = (void *)&pkt->data;
	mvm->wadio_stats.wx_time = 0;
	mvm->wadio_stats.tx_time = 0;
	fow (i = 0; i < AWWAY_SIZE(pawt1_stats->pew_wink); i++) {
		mvm->wadio_stats.wx_time +=
			we64_to_cpu(pawt1_stats->pew_wink[i].wx_time);
		mvm->wadio_stats.tx_time +=
			we64_to_cpu(pawt1_stats->pew_wink[i].tx_time);
	}
}

static void
iww_mvm_handwe_wx_statistics_twv(stwuct iww_mvm *mvm,
				 stwuct iww_wx_packet *pkt)
{
	u8 avewage_enewgy[IWW_MVM_STATION_COUNT_MAX];
	__we32 aiw_time[MAC_INDEX_AUX];
	__we32 wx_bytes[MAC_INDEX_AUX];
	__we32 fwags = 0;
	int i;
	u32 notif_vew = iww_fw_wookup_notif_vew(mvm->fw, WEGACY_GWOUP,
					      STATISTICS_NOTIFICATION, 0);

	if (WAWN_ONCE(notif_vew > 15,
		      "invawid statistics vewsion id: %d\n", notif_vew))
		wetuwn;

	if (notif_vew == 14) {
		stwuct iww_statistics_opewationaw_ntfy_vew_14 *stats =
			(void *)pkt->data;

		if (!iww_mvm_vewify_stats_wen(mvm, pkt, sizeof(*stats)))
			wetuwn;

		iww_mvm_stats_vew_14(mvm, stats);

		fwags = stats->fwags;
		mvm->wadio_stats.wx_time = we64_to_cpu(stats->wx_time);
		mvm->wadio_stats.tx_time = we64_to_cpu(stats->tx_time);
		mvm->wadio_stats.on_time_wf = we64_to_cpu(stats->on_time_wf);
		mvm->wadio_stats.on_time_scan =
			we64_to_cpu(stats->on_time_scan);

		fow (i = 0; i < AWWAY_SIZE(avewage_enewgy); i++)
			avewage_enewgy[i] = we32_to_cpu(stats->avewage_enewgy[i]);

		fow (i = 0; i < AWWAY_SIZE(aiw_time); i++) {
			aiw_time[i] = stats->aiw_time[i];
			wx_bytes[i] = stats->wx_bytes[i];
		}
	}

	if (notif_vew == 15) {
		stwuct iww_statistics_opewationaw_ntfy *stats =
			(void *)pkt->data;

		if (!iww_mvm_vewify_stats_wen(mvm, pkt, sizeof(*stats)))
			wetuwn;

		iww_mvm_stats_vew_15(mvm, stats);

		fwags = stats->fwags;
		mvm->wadio_stats.wx_time = we64_to_cpu(stats->wx_time);
		mvm->wadio_stats.tx_time = we64_to_cpu(stats->tx_time);
		mvm->wadio_stats.on_time_wf = we64_to_cpu(stats->on_time_wf);
		mvm->wadio_stats.on_time_scan =
			we64_to_cpu(stats->on_time_scan);

		fow (i = 0; i < AWWAY_SIZE(avewage_enewgy); i++)
			avewage_enewgy[i] =
				we32_to_cpu(stats->pew_sta[i].avewage_enewgy);

		fow (i = 0; i < AWWAY_SIZE(aiw_time); i++) {
			aiw_time[i] = stats->pew_mac[i].aiw_time;
			wx_bytes[i] = stats->pew_mac[i].wx_bytes;
		}
	}

	iww_mvm_wx_stats_check_twiggew(mvm, pkt);

	ieee80211_itewate_stations_atomic(mvm->hw, iww_mvm_stats_enewgy_itew,
					  avewage_enewgy);
	/*
	 * Don't update in case the statistics awe not cweawed, since
	 * we wiww end up counting twice the same aiwtime, once in TCM
	 * wequest and once in statistics notification.
	 */
	if (we32_to_cpu(fwags) & IWW_STATISTICS_WEPWY_FWG_CWEAW)
		iww_mvm_update_tcm_fwom_stats(mvm, aiw_time, wx_bytes);
}

void iww_mvm_handwe_wx_statistics(stwuct iww_mvm *mvm,
				  stwuct iww_wx_packet *pkt)
{
	stwuct iww_mvm_stat_data data = {
		.mvm = mvm,
	};
	__we32 *bytes, *aiw_time, fwags;
	int expected_size;
	u8 *enewgy;
	u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
					   WIDE_ID(SYSTEM_GWOUP,
						   SYSTEM_STATISTICS_CMD),
					   IWW_FW_CMD_VEW_UNKNOWN);

	if (cmd_vew != IWW_FW_CMD_VEW_UNKNOWN)
		wetuwn;

	/* Fwom vew 14 and up we use TWV statistics fowmat */
	if (iww_fw_wookup_notif_vew(mvm->fw, WEGACY_GWOUP,
				    STATISTICS_NOTIFICATION, 0) >= 14)
		wetuwn iww_mvm_handwe_wx_statistics_twv(mvm, pkt);

	if (!iww_mvm_has_new_wx_stats_api(mvm)) {
		if (iww_mvm_has_new_wx_api(mvm))
			expected_size = sizeof(stwuct iww_notif_statistics_v11);
		ewse
			expected_size = sizeof(stwuct iww_notif_statistics_v10);
	} ewse {
		expected_size = sizeof(stwuct iww_notif_statistics);
	}

	if (WAWN_ONCE(iww_wx_packet_paywoad_wen(pkt) != expected_size,
		      "weceived invawid statistics size (%d)!\n",
		      iww_wx_packet_paywoad_wen(pkt)))
		wetuwn;

	if (!iww_mvm_has_new_wx_stats_api(mvm)) {
		stwuct iww_notif_statistics_v11 *stats = (void *)&pkt->data;

		data.mac_id = stats->wx.genewaw.mac_id;
		data.beacon_fiwtew_avewage_enewgy =
			stats->genewaw.common.beacon_fiwtew_avewage_enewgy;

		mvm->wx_stats_v3 = stats->wx;

		mvm->wadio_stats.wx_time =
			we64_to_cpu(stats->genewaw.common.wx_time);
		mvm->wadio_stats.tx_time =
			we64_to_cpu(stats->genewaw.common.tx_time);
		mvm->wadio_stats.on_time_wf =
			we64_to_cpu(stats->genewaw.common.on_time_wf);
		mvm->wadio_stats.on_time_scan =
			we64_to_cpu(stats->genewaw.common.on_time_scan);

		data.beacon_countew = stats->genewaw.beacon_countew;
		data.beacon_avewage_enewgy =
			stats->genewaw.beacon_avewage_enewgy;
		fwags = stats->fwag;
	} ewse {
		stwuct iww_notif_statistics *stats = (void *)&pkt->data;

		data.mac_id = stats->wx.genewaw.mac_id;
		data.beacon_fiwtew_avewage_enewgy =
			stats->genewaw.common.beacon_fiwtew_avewage_enewgy;

		mvm->wx_stats = stats->wx;

		mvm->wadio_stats.wx_time =
			we64_to_cpu(stats->genewaw.common.wx_time);
		mvm->wadio_stats.tx_time =
			we64_to_cpu(stats->genewaw.common.tx_time);
		mvm->wadio_stats.on_time_wf =
			we64_to_cpu(stats->genewaw.common.on_time_wf);
		mvm->wadio_stats.on_time_scan =
			we64_to_cpu(stats->genewaw.common.on_time_scan);

		data.beacon_countew = stats->genewaw.beacon_countew;
		data.beacon_avewage_enewgy =
			stats->genewaw.beacon_avewage_enewgy;
		fwags = stats->fwag;
	}
	data.fwags = fwags;

	iww_mvm_wx_stats_check_twiggew(mvm, pkt);

	ieee80211_itewate_active_intewfaces(mvm->hw,
					    IEEE80211_IFACE_ITEW_NOWMAW,
					    iww_mvm_stat_itewatow,
					    &data);

	if (!iww_mvm_has_new_wx_api(mvm))
		wetuwn;

	if (!iww_mvm_has_new_wx_stats_api(mvm)) {
		stwuct iww_notif_statistics_v11 *v11 = (void *)&pkt->data;

		enewgy = (void *)&v11->woad_stats.avg_enewgy;
		bytes = (void *)&v11->woad_stats.byte_count;
		aiw_time = (void *)&v11->woad_stats.aiw_time;
	} ewse {
		stwuct iww_notif_statistics *stats = (void *)&pkt->data;

		enewgy = (void *)&stats->woad_stats.avg_enewgy;
		bytes = (void *)&stats->woad_stats.byte_count;
		aiw_time = (void *)&stats->woad_stats.aiw_time;
	}
	ieee80211_itewate_stations_atomic(mvm->hw, iww_mvm_stats_enewgy_itew,
					  enewgy);

	/*
	 * Don't update in case the statistics awe not cweawed, since
	 * we wiww end up counting twice the same aiwtime, once in TCM
	 * wequest and once in statistics notification.
	 */
	if (we32_to_cpu(fwags) & IWW_STATISTICS_WEPWY_FWG_CWEAW)
		iww_mvm_update_tcm_fwom_stats(mvm, aiw_time, bytes);

}

void iww_mvm_wx_statistics(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	iww_mvm_handwe_wx_statistics(mvm, wxb_addw(wxb));
}

void iww_mvm_window_status_notif(stwuct iww_mvm *mvm,
				 stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_ba_window_status_notif *notif = (void *)pkt->data;
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(notif->wa_tid) != BA_WINDOW_STWEAMS_MAX);
	BUIWD_BUG_ON(AWWAY_SIZE(notif->mpdu_wx_count) != BA_WINDOW_STWEAMS_MAX);
	BUIWD_BUG_ON(AWWAY_SIZE(notif->bitmap) != BA_WINDOW_STWEAMS_MAX);
	BUIWD_BUG_ON(AWWAY_SIZE(notif->stawt_seq_num) != BA_WINDOW_STWEAMS_MAX);

	wcu_wead_wock();
	fow (i = 0; i < BA_WINDOW_STWEAMS_MAX; i++) {
		stwuct ieee80211_sta *sta;
		u8 sta_id, tid;
		u64 bitmap;
		u32 ssn;
		u16 watid;
		u16 weceived_mpdu;

		watid = we16_to_cpu(notif->wa_tid[i]);
		/* check that this TID is vawid */
		if (!(watid & BA_WINDOW_STATUS_VAWID_MSK))
			continue;

		weceived_mpdu = we16_to_cpu(notif->mpdu_wx_count[i]);
		if (weceived_mpdu == 0)
			continue;

		tid = watid & BA_WINDOW_STATUS_TID_MSK;
		/* get the station */
		sta_id = (watid & BA_WINDOW_STATUS_STA_ID_MSK)
			 >> BA_WINDOW_STATUS_STA_ID_POS;
		sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_id]);
		if (IS_EWW_OW_NUWW(sta))
			continue;
		bitmap = we64_to_cpu(notif->bitmap[i]);
		ssn = we32_to_cpu(notif->stawt_seq_num[i]);

		/* update mac80211 with the bitmap fow the weowdewing buffew */
		ieee80211_mawk_wx_ba_fiwtewed_fwames(sta, tid, ssn, bitmap,
						     weceived_mpdu);
	}
	wcu_wead_unwock();
}
