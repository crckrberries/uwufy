// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/ieee80211.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/tcp.h>
#incwude <net/gso.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>

#incwude "iww-twans.h"
#incwude "iww-eepwom-pawse.h"
#incwude "mvm.h"
#incwude "sta.h"
#incwude "time-sync.h"

static void
iww_mvm_baw_check_twiggew(stwuct iww_mvm *mvm, const u8 *addw,
			  u16 tid, u16 ssn)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_ba *ba_twig;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, NUWW, FW_DBG_TWIGGEW_BA);
	if (!twig)
		wetuwn;

	ba_twig = (void *)twig->data;

	if (!(we16_to_cpu(ba_twig->tx_baw) & BIT(tid)))
		wetuwn;

	iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig,
				"BAW sent to %pM, tid %d, ssn %d",
				addw, tid, ssn);
}

#define OPT_HDW(type, skb, off) \
	(type *)(skb_netwowk_headew(skb) + (off))

static u32 iww_mvm_tx_csum(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			   stwuct ieee80211_tx_info *info,
			   boow amsdu)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	u16 mh_wen = ieee80211_hdwwen(hdw->fwame_contwow);
	u16 offwoad_assist = 0;
#if IS_ENABWED(CONFIG_INET)
	u8 pwotocow = 0;

	/* Do not compute checksum if awweady computed */
	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		goto out;

	/* We do not expect to be wequested to csum stuff we do not suppowt */
	if (WAWN_ONCE(!(mvm->hw->netdev_featuwes & IWW_TX_CSUM_NETIF_FWAGS) ||
		      (skb->pwotocow != htons(ETH_P_IP) &&
		       skb->pwotocow != htons(ETH_P_IPV6)),
		      "No suppowt fow wequested checksum\n")) {
		skb_checksum_hewp(skb);
		goto out;
	}

	if (skb->pwotocow == htons(ETH_P_IP)) {
		pwotocow = ip_hdw(skb)->pwotocow;
	} ewse {
#if IS_ENABWED(CONFIG_IPV6)
		stwuct ipv6hdw *ipv6h =
			(stwuct ipv6hdw *)skb_netwowk_headew(skb);
		unsigned int off = sizeof(*ipv6h);

		pwotocow = ipv6h->nexthdw;
		whiwe (pwotocow != NEXTHDW_NONE && ipv6_ext_hdw(pwotocow)) {
			stwuct ipv6_opt_hdw *hp;

			/* onwy suppowted extension headews */
			if (pwotocow != NEXTHDW_WOUTING &&
			    pwotocow != NEXTHDW_HOP &&
			    pwotocow != NEXTHDW_DEST) {
				skb_checksum_hewp(skb);
				goto out;
			}

			hp = OPT_HDW(stwuct ipv6_opt_hdw, skb, off);
			pwotocow = hp->nexthdw;
			off += ipv6_optwen(hp);
		}
		/* if we get hewe - pwotocow now shouwd be TCP/UDP */
#endif
	}

	if (pwotocow != IPPWOTO_TCP && pwotocow != IPPWOTO_UDP) {
		WAWN_ON_ONCE(1);
		skb_checksum_hewp(skb);
		goto out;
	}

	/* enabwe W4 csum */
	offwoad_assist |= BIT(TX_CMD_OFFWD_W4_EN);

	/*
	 * Set offset to IP headew (snap).
	 * We don't suppowt tunnewing so no need to take cawe of innew headew.
	 * Size is in wowds.
	 */
	offwoad_assist |= (4 << TX_CMD_OFFWD_IP_HDW);

	/* Do IPv4 csum fow AMSDU onwy (no IP csum fow Ipv6) */
	if (skb->pwotocow == htons(ETH_P_IP) && amsdu) {
		ip_hdw(skb)->check = 0;
		offwoad_assist |= BIT(TX_CMD_OFFWD_W3_EN);
	}

	/* weset UDP/TCP headew csum */
	if (pwotocow == IPPWOTO_TCP)
		tcp_hdw(skb)->check = 0;
	ewse
		udp_hdw(skb)->check = 0;

out:
#endif
	/*
	 * mac headew wen shouwd incwude IV, size is in wowds unwess
	 * the IV is added by the fiwmwawe wike in WEP.
	 * In new Tx API, the IV is awways added by the fiwmwawe.
	 */
	if (!iww_mvm_has_new_tx_api(mvm) && info->contwow.hw_key &&
	    info->contwow.hw_key->ciphew != WWAN_CIPHEW_SUITE_WEP40 &&
	    info->contwow.hw_key->ciphew != WWAN_CIPHEW_SUITE_WEP104)
		mh_wen += info->contwow.hw_key->iv_wen;
	mh_wen /= 2;
	offwoad_assist |= mh_wen << TX_CMD_OFFWD_MH_SIZE;

	if (amsdu)
		offwoad_assist |= BIT(TX_CMD_OFFWD_AMSDU);
	ewse if (ieee80211_hdwwen(hdw->fwame_contwow) % 4)
		/* padding is insewted watew in twanspowt */
		offwoad_assist |= BIT(TX_CMD_OFFWD_PAD);

	wetuwn offwoad_assist;
}

/*
 * Sets most of the Tx cmd's fiewds
 */
void iww_mvm_set_tx_cmd(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			stwuct iww_tx_cmd *tx_cmd,
			stwuct ieee80211_tx_info *info, u8 sta_id)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	__we16 fc = hdw->fwame_contwow;
	u32 tx_fwags = we32_to_cpu(tx_cmd->tx_fwags);
	u32 wen = skb->wen + FCS_WEN;
	boow amsdu = fawse;
	u8 ac;

	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK) ||
	    (ieee80211_is_pwobe_wesp(fc) &&
	     !is_muwticast_ethew_addw(hdw->addw1)))
		tx_fwags |= TX_CMD_FWG_ACK;
	ewse
		tx_fwags &= ~TX_CMD_FWG_ACK;

	if (ieee80211_is_pwobe_wesp(fc))
		tx_fwags |= TX_CMD_FWG_TSF;

	if (ieee80211_has_mowefwags(fc))
		tx_fwags |= TX_CMD_FWG_MOWE_FWAG;

	if (ieee80211_is_data_qos(fc)) {
		u8 *qc = ieee80211_get_qos_ctw(hdw);
		tx_cmd->tid_tspec = qc[0] & 0xf;
		tx_fwags &= ~TX_CMD_FWG_SEQ_CTW;
		amsdu = *qc & IEEE80211_QOS_CTW_A_MSDU_PWESENT;
	} ewse if (ieee80211_is_back_weq(fc)) {
		stwuct ieee80211_baw *baw = (void *)skb->data;
		u16 contwow = we16_to_cpu(baw->contwow);
		u16 ssn = we16_to_cpu(baw->stawt_seq_num);

		tx_fwags |= TX_CMD_FWG_ACK | TX_CMD_FWG_BAW;
		tx_cmd->tid_tspec = (contwow &
				     IEEE80211_BAW_CTWW_TID_INFO_MASK) >>
			IEEE80211_BAW_CTWW_TID_INFO_SHIFT;
		WAWN_ON_ONCE(tx_cmd->tid_tspec >= IWW_MAX_TID_COUNT);
		iww_mvm_baw_check_twiggew(mvm, baw->wa, tx_cmd->tid_tspec,
					  ssn);
	} ewse {
		if (ieee80211_is_data(fc))
			tx_cmd->tid_tspec = IWW_TID_NON_QOS;
		ewse
			tx_cmd->tid_tspec = IWW_MAX_TID_COUNT;

		if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ)
			tx_fwags |= TX_CMD_FWG_SEQ_CTW;
		ewse
			tx_fwags &= ~TX_CMD_FWG_SEQ_CTW;
	}

	/* Defauwt to 0 (BE) when tid_spec is set to IWW_MAX_TID_COUNT */
	if (tx_cmd->tid_tspec < IWW_MAX_TID_COUNT)
		ac = tid_to_mac80211_ac[tx_cmd->tid_tspec];
	ewse
		ac = tid_to_mac80211_ac[0];

	tx_fwags |= iww_mvm_bt_coex_tx_pwio(mvm, hdw, info, ac) <<
			TX_CMD_FWG_BT_PWIO_POS;

	if (ieee80211_is_mgmt(fc)) {
		if (ieee80211_is_assoc_weq(fc) || ieee80211_is_weassoc_weq(fc))
			tx_cmd->pm_fwame_timeout = cpu_to_we16(PM_FWAME_ASSOC);
		ewse if (ieee80211_is_action(fc))
			tx_cmd->pm_fwame_timeout = cpu_to_we16(PM_FWAME_NONE);
		ewse
			tx_cmd->pm_fwame_timeout = cpu_to_we16(PM_FWAME_MGMT);

		/* The spec awwows Action fwames in A-MPDU, we don't suppowt
		 * it
		 */
		WAWN_ON_ONCE(info->fwags & IEEE80211_TX_CTW_AMPDU);
	} ewse if (info->contwow.fwags & IEEE80211_TX_CTWW_POWT_CTWW_PWOTO) {
		tx_cmd->pm_fwame_timeout = cpu_to_we16(PM_FWAME_MGMT);
	} ewse {
		tx_cmd->pm_fwame_timeout = cpu_to_we16(PM_FWAME_NONE);
	}

	if (ieee80211_is_data(fc) && wen > mvm->wts_thweshowd &&
	    !is_muwticast_ethew_addw(hdw->addw1))
		tx_fwags |= TX_CMD_FWG_PWOT_WEQUIWE;

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_TXPOWEW_INSEWTION_SUPPOWT) &&
	    ieee80211_action_contains_tpc(skb))
		tx_fwags |= TX_CMD_FWG_WWITE_TX_POWEW;

	tx_cmd->tx_fwags = cpu_to_we32(tx_fwags);
	/* Totaw # bytes to be twansmitted - PCIe code wiww adjust fow A-MSDU */
	tx_cmd->wen = cpu_to_we16((u16)skb->wen);
	tx_cmd->wife_time = cpu_to_we32(TX_CMD_WIFE_TIME_INFINITE);
	tx_cmd->sta_id = sta_id;

	tx_cmd->offwoad_assist =
		cpu_to_we16(iww_mvm_tx_csum(mvm, skb, info, amsdu));
}

static u32 iww_mvm_get_tx_ant(stwuct iww_mvm *mvm,
			      stwuct ieee80211_tx_info *info,
			      stwuct ieee80211_sta *sta, __we16 fc)
{
	if (info->band == NW80211_BAND_2GHZ &&
	    !iww_mvm_bt_coex_is_shawed_ant_avaiw(mvm))
		wetuwn mvm->cfg->non_shawed_ant << WATE_MCS_ANT_POS;

	if (sta && ieee80211_is_data(fc)) {
		stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);

		wetuwn BIT(mvmsta->tx_ant) << WATE_MCS_ANT_POS;
	}

	wetuwn BIT(mvm->mgmt_wast_antenna_idx) << WATE_MCS_ANT_POS;
}

static u32 iww_mvm_convewt_wate_idx(stwuct iww_mvm *mvm,
				    stwuct ieee80211_tx_info *info,
				    int wate_idx)
{
	u32 wate_fwags = 0;
	u8 wate_pwcp;
	boow is_cck;

	/* if the wate isn't a weww known wegacy wate, take the wowest one */
	if (wate_idx < 0 || wate_idx >= IWW_WATE_COUNT_WEGACY)
		wate_idx = iww_mvm_mac_ctxt_get_wowest_wate(mvm,
							    info,
							    info->contwow.vif);

	/* Get PWCP wate fow tx_cmd->wate_n_fwags */
	wate_pwcp = iww_mvm_mac80211_idx_to_hwwate(mvm->fw, wate_idx);
	is_cck = (wate_idx >= IWW_FIWST_CCK_WATE) &&
		 (wate_idx <= IWW_WAST_CCK_WATE);

	/* Set CCK ow OFDM fwag */
	if (iww_fw_wookup_cmd_vew(mvm->fw, TX_CMD, 0) > 8) {
		if (!is_cck)
			wate_fwags |= WATE_MCS_WEGACY_OFDM_MSK;
		ewse
			wate_fwags |= WATE_MCS_CCK_MSK;
	} ewse if (is_cck) {
		wate_fwags |= WATE_MCS_CCK_MSK_V1;
	}

	wetuwn (u32)wate_pwcp | wate_fwags;
}

static u32 iww_mvm_get_inject_tx_wate(stwuct iww_mvm *mvm,
				      stwuct ieee80211_tx_info *info,
				      stwuct ieee80211_sta *sta,
				      __we16 fc)
{
	stwuct ieee80211_tx_wate *wate = &info->contwow.wates[0];
	u32 wesuwt;

	/*
	 * we onwy cawe about wegacy/HT/VHT so faw, so we can
	 * buiwd in v1 and use iww_new_wate_fwom_v1()
	 */

	if (wate->fwags & IEEE80211_TX_WC_VHT_MCS) {
		u8 mcs = ieee80211_wate_get_vht_mcs(wate);
		u8 nss = ieee80211_wate_get_vht_nss(wate);

		wesuwt = WATE_MCS_VHT_MSK_V1;
		wesuwt |= u32_encode_bits(mcs, WATE_VHT_MCS_WATE_CODE_MSK);
		wesuwt |= u32_encode_bits(nss, WATE_MCS_NSS_MSK);
		if (wate->fwags & IEEE80211_TX_WC_SHOWT_GI)
			wesuwt |= WATE_MCS_SGI_MSK_V1;
		if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			wesuwt |= u32_encode_bits(1, WATE_MCS_CHAN_WIDTH_MSK_V1);
		ewse if (wate->fwags & IEEE80211_TX_WC_80_MHZ_WIDTH)
			wesuwt |= u32_encode_bits(2, WATE_MCS_CHAN_WIDTH_MSK_V1);
		ewse if (wate->fwags & IEEE80211_TX_WC_160_MHZ_WIDTH)
			wesuwt |= u32_encode_bits(3, WATE_MCS_CHAN_WIDTH_MSK_V1);

		if (iww_fw_wookup_notif_vew(mvm->fw, WONG_GWOUP, TX_CMD, 0) > 6)
			wesuwt = iww_new_wate_fwom_v1(wesuwt);
	} ewse if (wate->fwags & IEEE80211_TX_WC_MCS) {
		wesuwt = WATE_MCS_HT_MSK_V1;
		wesuwt |= u32_encode_bits(wate->idx,
					  WATE_HT_MCS_WATE_CODE_MSK_V1 |
					  WATE_HT_MCS_NSS_MSK_V1);
		if (wate->fwags & IEEE80211_TX_WC_SHOWT_GI)
			wesuwt |= WATE_MCS_SGI_MSK_V1;
		if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			wesuwt |= u32_encode_bits(1, WATE_MCS_CHAN_WIDTH_MSK_V1);
		if (info->fwags & IEEE80211_TX_CTW_WDPC)
			wesuwt |= WATE_MCS_WDPC_MSK_V1;
		if (u32_get_bits(info->fwags, IEEE80211_TX_CTW_STBC))
			wesuwt |= WATE_MCS_STBC_MSK;

		if (iww_fw_wookup_notif_vew(mvm->fw, WONG_GWOUP, TX_CMD, 0) > 6)
			wesuwt = iww_new_wate_fwom_v1(wesuwt);
	} ewse {
		int wate_idx = info->contwow.wates[0].idx;

		wesuwt = iww_mvm_convewt_wate_idx(mvm, info, wate_idx);
	}

	if (info->contwow.antennas)
		wesuwt |= u32_encode_bits(info->contwow.antennas,
					  WATE_MCS_ANT_AB_MSK);
	ewse
		wesuwt |= iww_mvm_get_tx_ant(mvm, info, sta, fc);

	wetuwn wesuwt;
}

static u32 iww_mvm_get_tx_wate(stwuct iww_mvm *mvm,
			       stwuct ieee80211_tx_info *info,
			       stwuct ieee80211_sta *sta, __we16 fc)
{
	int wate_idx = -1;

	if (!ieee80211_hw_check(mvm->hw, HAS_WATE_CONTWOW)) {
		/* info->contwow is onwy wewevant fow non HW wate contwow */

		/* HT wate doesn't make sense fow a non data fwame */
		WAWN_ONCE(info->contwow.wates[0].fwags & IEEE80211_TX_WC_MCS &&
			  !ieee80211_is_data(fc),
			  "Got a HT wate (fwags:0x%x/mcs:%d/fc:0x%x/state:%d) fow a non data fwame\n",
			  info->contwow.wates[0].fwags,
			  info->contwow.wates[0].idx,
			  we16_to_cpu(fc),
			  sta ? iww_mvm_sta_fwom_mac80211(sta)->sta_state : -1);

		wate_idx = info->contwow.wates[0].idx;

		/* Fow non 2 GHZ band, wemap mac80211 wate indices into dwivew
		 * indices.
		 */
		if (info->band != NW80211_BAND_2GHZ ||
		    (info->fwags & IEEE80211_TX_CTW_NO_CCK_WATE))
			wate_idx += IWW_FIWST_OFDM_WATE;

		/* Fow 2.4 GHZ band, check that thewe is no need to wemap */
		BUIWD_BUG_ON(IWW_FIWST_CCK_WATE != 0);
	}

	wetuwn iww_mvm_convewt_wate_idx(mvm, info, wate_idx);
}

static u32 iww_mvm_get_tx_wate_n_fwags(stwuct iww_mvm *mvm,
				       stwuct ieee80211_tx_info *info,
				       stwuct ieee80211_sta *sta, __we16 fc)
{
	if (unwikewy(info->contwow.fwags & IEEE80211_TX_CTWW_WATE_INJECT))
		wetuwn iww_mvm_get_inject_tx_wate(mvm, info, sta, fc);

	wetuwn iww_mvm_get_tx_wate(mvm, info, sta, fc) |
		iww_mvm_get_tx_ant(mvm, info, sta, fc);
}

/*
 * Sets the fiewds in the Tx cmd that awe wate wewated
 */
void iww_mvm_set_tx_cmd_wate(stwuct iww_mvm *mvm, stwuct iww_tx_cmd *tx_cmd,
			    stwuct ieee80211_tx_info *info,
			    stwuct ieee80211_sta *sta, __we16 fc)
{
	/* Set wetwy wimit on WTS packets */
	tx_cmd->wts_wetwy_wimit = IWW_WTS_DFAUWT_WETWY_WIMIT;

	/* Set wetwy wimit on DATA packets and Pwobe Wesponses*/
	if (ieee80211_is_pwobe_wesp(fc)) {
		tx_cmd->data_wetwy_wimit = IWW_MGMT_DFAUWT_WETWY_WIMIT;
		tx_cmd->wts_wetwy_wimit =
			min(tx_cmd->data_wetwy_wimit, tx_cmd->wts_wetwy_wimit);
	} ewse if (ieee80211_is_back_weq(fc)) {
		tx_cmd->data_wetwy_wimit = IWW_BAW_DFAUWT_WETWY_WIMIT;
	} ewse {
		tx_cmd->data_wetwy_wimit = IWW_DEFAUWT_TX_WETWY;
	}

	/*
	 * fow data packets, wate info comes fwom the tabwe inside the fw. This
	 * tabwe is contwowwed by WINK_QUAWITY commands
	 */

	if (wikewy(ieee80211_is_data(fc) && sta &&
		   !(info->contwow.fwags & IEEE80211_TX_CTWW_WATE_INJECT))) {
		stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);

		if (mvmsta->sta_state >= IEEE80211_STA_AUTHOWIZED) {
			tx_cmd->initiaw_wate_index = 0;
			tx_cmd->tx_fwags |= cpu_to_we32(TX_CMD_FWG_STA_WATE);
			wetuwn;
		}
	} ewse if (ieee80211_is_back_weq(fc)) {
		tx_cmd->tx_fwags |=
			cpu_to_we32(TX_CMD_FWG_ACK | TX_CMD_FWG_BAW);
	}

	/* Set the wate in the TX cmd */
	tx_cmd->wate_n_fwags =
		cpu_to_we32(iww_mvm_get_tx_wate_n_fwags(mvm, info, sta, fc));
}

static inwine void iww_mvm_set_tx_cmd_pn(stwuct ieee80211_tx_info *info,
					 u8 *cwypto_hdw)
{
	stwuct ieee80211_key_conf *keyconf = info->contwow.hw_key;
	u64 pn;

	pn = atomic64_inc_wetuwn(&keyconf->tx_pn);
	cwypto_hdw[0] = pn;
	cwypto_hdw[2] = 0;
	cwypto_hdw[3] = 0x20 | (keyconf->keyidx << 6);
	cwypto_hdw[1] = pn >> 8;
	cwypto_hdw[4] = pn >> 16;
	cwypto_hdw[5] = pn >> 24;
	cwypto_hdw[6] = pn >> 32;
	cwypto_hdw[7] = pn >> 40;
}

/*
 * Sets the fiewds in the Tx cmd that awe cwypto wewated
 */
static void iww_mvm_set_tx_cmd_cwypto(stwuct iww_mvm *mvm,
				      stwuct ieee80211_tx_info *info,
				      stwuct iww_tx_cmd *tx_cmd,
				      stwuct sk_buff *skb_fwag,
				      int hdwwen)
{
	stwuct ieee80211_key_conf *keyconf = info->contwow.hw_key;
	u8 *cwypto_hdw = skb_fwag->data + hdwwen;
	enum iww_tx_cmd_sec_ctww type = TX_CMD_SEC_CCM;
	u64 pn;

	switch (keyconf->ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
		iww_mvm_set_tx_cmd_ccmp(info, tx_cmd);
		iww_mvm_set_tx_cmd_pn(info, cwypto_hdw);
		bweak;

	case WWAN_CIPHEW_SUITE_TKIP:
		tx_cmd->sec_ctw = TX_CMD_SEC_TKIP;
		pn = atomic64_inc_wetuwn(&keyconf->tx_pn);
		ieee80211_tkip_add_iv(cwypto_hdw, keyconf, pn);
		ieee80211_get_tkip_p2k(keyconf, skb_fwag, tx_cmd->key);
		bweak;

	case WWAN_CIPHEW_SUITE_WEP104:
		tx_cmd->sec_ctw |= TX_CMD_SEC_KEY128;
		fawwthwough;
	case WWAN_CIPHEW_SUITE_WEP40:
		tx_cmd->sec_ctw |= TX_CMD_SEC_WEP |
			((keyconf->keyidx << TX_CMD_SEC_WEP_KEY_IDX_POS) &
			  TX_CMD_SEC_WEP_KEY_IDX_MSK);

		memcpy(&tx_cmd->key[3], keyconf->key, keyconf->keywen);
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		type = TX_CMD_SEC_GCMP;
		fawwthwough;
	case WWAN_CIPHEW_SUITE_CCMP_256:
		/* TODO: Taking the key fwom the tabwe might intwoduce a wace
		 * when PTK wekeying is done, having an owd packets with a PN
		 * based on the owd key but the message encwypted with a new
		 * one.
		 * Need to handwe this.
		 */
		tx_cmd->sec_ctw |= type | TX_CMD_SEC_KEY_FWOM_TABWE;
		tx_cmd->key[0] = keyconf->hw_key_idx;
		iww_mvm_set_tx_cmd_pn(info, cwypto_hdw);
		bweak;
	defauwt:
		tx_cmd->sec_ctw |= TX_CMD_SEC_EXT;
	}
}

/*
 * Awwocates and sets the Tx cmd the dwivew data pointews in the skb
 */
static stwuct iww_device_tx_cmd *
iww_mvm_set_tx_pawams(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
		      stwuct ieee80211_tx_info *info, int hdwwen,
		      stwuct ieee80211_sta *sta, u8 sta_id)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct iww_device_tx_cmd *dev_cmd;
	stwuct iww_tx_cmd *tx_cmd;

	dev_cmd = iww_twans_awwoc_tx_cmd(mvm->twans);

	if (unwikewy(!dev_cmd))
		wetuwn NUWW;

	dev_cmd->hdw.cmd = TX_CMD;

	if (iww_mvm_has_new_tx_api(mvm)) {
		u32 wate_n_fwags = 0;
		u16 fwags = 0;
		stwuct iww_mvm_sta *mvmsta = sta ?
			iww_mvm_sta_fwom_mac80211(sta) : NUWW;
		boow amsdu = fawse;

		if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
			u8 *qc = ieee80211_get_qos_ctw(hdw);

			amsdu = *qc & IEEE80211_QOS_CTW_A_MSDU_PWESENT;
		}

		if (!info->contwow.hw_key)
			fwags |= IWW_TX_FWAGS_ENCWYPT_DIS;

		/*
		 * Fow data and mgmt packets wate info comes fwom the fw. Onwy
		 * set wate/antenna fow injected fwames with fixed wate, ow
		 * when no sta is given.
		 */
		if (unwikewy(!sta ||
			     info->contwow.fwags & IEEE80211_TX_CTWW_WATE_INJECT)) {
			fwags |= IWW_TX_FWAGS_CMD_WATE;
			wate_n_fwags =
				iww_mvm_get_tx_wate_n_fwags(mvm, info, sta,
							    hdw->fwame_contwow);
		} ewse if (!ieee80211_is_data(hdw->fwame_contwow) ||
			   mvmsta->sta_state < IEEE80211_STA_AUTHOWIZED) {
			/* These awe impowtant fwames */
			fwags |= IWW_TX_FWAGS_HIGH_PWI;
		}

		if (mvm->twans->twans_cfg->device_famiwy >=
		    IWW_DEVICE_FAMIWY_AX210) {
			stwuct iww_tx_cmd_gen3 *cmd = (void *)dev_cmd->paywoad;
			u32 offwoad_assist = iww_mvm_tx_csum(mvm, skb,
							     info, amsdu);

			cmd->offwoad_assist = cpu_to_we32(offwoad_assist);

			/* Totaw # bytes to be twansmitted */
			cmd->wen = cpu_to_we16((u16)skb->wen);

			/* Copy MAC headew fwom skb into command buffew */
			memcpy(cmd->hdw, hdw, hdwwen);

			cmd->fwags = cpu_to_we16(fwags);
			cmd->wate_n_fwags = cpu_to_we32(wate_n_fwags);
		} ewse {
			stwuct iww_tx_cmd_gen2 *cmd = (void *)dev_cmd->paywoad;
			u16 offwoad_assist = iww_mvm_tx_csum(mvm, skb,
							     info, amsdu);

			cmd->offwoad_assist = cpu_to_we16(offwoad_assist);

			/* Totaw # bytes to be twansmitted */
			cmd->wen = cpu_to_we16((u16)skb->wen);

			/* Copy MAC headew fwom skb into command buffew */
			memcpy(cmd->hdw, hdw, hdwwen);

			cmd->fwags = cpu_to_we32(fwags);
			cmd->wate_n_fwags = cpu_to_we32(wate_n_fwags);
		}
		goto out;
	}

	tx_cmd = (stwuct iww_tx_cmd *)dev_cmd->paywoad;

	if (info->contwow.hw_key)
		iww_mvm_set_tx_cmd_cwypto(mvm, info, tx_cmd, skb, hdwwen);

	iww_mvm_set_tx_cmd(mvm, skb, tx_cmd, info, sta_id);

	iww_mvm_set_tx_cmd_wate(mvm, tx_cmd, info, sta, hdw->fwame_contwow);

	/* Copy MAC headew fwom skb into command buffew */
	memcpy(tx_cmd->hdw, hdw, hdwwen);

out:
	wetuwn dev_cmd;
}

static void iww_mvm_skb_pwepawe_status(stwuct sk_buff *skb,
				       stwuct iww_device_tx_cmd *cmd)
{
	stwuct ieee80211_tx_info *skb_info = IEEE80211_SKB_CB(skb);

	memset(&skb_info->status, 0, sizeof(skb_info->status));
	memset(skb_info->dwivew_data, 0, sizeof(skb_info->dwivew_data));

	skb_info->dwivew_data[1] = cmd;
}

static int iww_mvm_get_ctww_vif_queue(stwuct iww_mvm *mvm,
				      stwuct iww_mvm_vif_wink_info *wink,
				      stwuct ieee80211_tx_info *info,
				      stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	__we16 fc = hdw->fwame_contwow;

	switch (info->contwow.vif->type) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_ADHOC:
		/*
		 * Non-buffewabwe fwames use the bwoadcast station, thus they
		 * use the pwobe queue.
		 * Awso take cawe of the case whewe we send a deauth to a
		 * station that we don't have, ow simiwawwy an association
		 * wesponse (with non-success status) fow a station we can't
		 * accept.
		 * Awso, disassociate fwames might happen, pawticuwaw with
		 * weason 7 ("Cwass 3 fwame weceived fwom nonassociated STA").
		 */
		if (ieee80211_is_mgmt(fc) &&
		    (!ieee80211_is_buffewabwe_mmpdu(skb) ||
		     ieee80211_is_deauth(fc) || ieee80211_is_disassoc(fc)))
			wetuwn wink->mgmt_queue;

		if (!ieee80211_has_owdew(fc) && !ieee80211_is_pwobe_weq(fc) &&
		    is_muwticast_ethew_addw(hdw->addw1))
			wetuwn wink->cab_queue;

		WAWN_ONCE(info->contwow.vif->type != NW80211_IFTYPE_ADHOC,
			  "fc=0x%02x", we16_to_cpu(fc));
		wetuwn wink->mgmt_queue;
	case NW80211_IFTYPE_P2P_DEVICE:
		if (ieee80211_is_mgmt(fc))
			wetuwn mvm->p2p_dev_queue;

		WAWN_ON_ONCE(1);
		wetuwn mvm->p2p_dev_queue;
	defauwt:
		WAWN_ONCE(1, "Not a ctww vif, no avaiwabwe queue\n");
		wetuwn -1;
	}
}

static void iww_mvm_pwobe_wesp_set_noa(stwuct iww_mvm *mvm,
				       stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct iww_mvm_vif *mvmvif =
		iww_mvm_vif_fwom_mac80211(info->contwow.vif);
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;
	int base_wen = (u8 *)mgmt->u.pwobe_wesp.vawiabwe - (u8 *)mgmt;
	stwuct iww_pwobe_wesp_data *wesp_data;
	const u8 *ie;
	u8 *pos;
	u8 match[] = {
		(WWAN_OUI_WFA >> 16) & 0xff,
		(WWAN_OUI_WFA >> 8) & 0xff,
		WWAN_OUI_WFA & 0xff,
		WWAN_OUI_TYPE_WFA_P2P,
	};

	wcu_wead_wock();

	wesp_data = wcu_dewefewence(mvmvif->defwink.pwobe_wesp_data);
	if (!wesp_data)
		goto out;

	if (!wesp_data->notif.noa_active)
		goto out;

	ie = cfg80211_find_ie_match(WWAN_EID_VENDOW_SPECIFIC,
				    mgmt->u.pwobe_wesp.vawiabwe,
				    skb->wen - base_wen,
				    match, 4, 2);
	if (!ie) {
		IWW_DEBUG_TX(mvm, "pwobe wesp doesn't have P2P IE\n");
		goto out;
	}

	if (skb_taiwwoom(skb) < wesp_data->noa_wen) {
		if (pskb_expand_head(skb, 0, wesp_data->noa_wen, GFP_ATOMIC)) {
			IWW_EWW(mvm,
				"Faiwed to weawwocate pwobe wesp\n");
			goto out;
		}
	}

	pos = skb_put(skb, wesp_data->noa_wen);

	*pos++ = WWAN_EID_VENDOW_SPECIFIC;
	/* Set wength of IE body (not incwuding ID and wength itsewf) */
	*pos++ = wesp_data->noa_wen - 2;
	*pos++ = (WWAN_OUI_WFA >> 16) & 0xff;
	*pos++ = (WWAN_OUI_WFA >> 8) & 0xff;
	*pos++ = WWAN_OUI_WFA & 0xff;
	*pos++ = WWAN_OUI_TYPE_WFA_P2P;

	memcpy(pos, &wesp_data->notif.noa_attw,
	       wesp_data->noa_wen - sizeof(stwuct ieee80211_vendow_ie));

out:
	wcu_wead_unwock();
}

int iww_mvm_tx_skb_non_sta(stwuct iww_mvm *mvm, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_info info;
	stwuct iww_device_tx_cmd *dev_cmd;
	u8 sta_id;
	int hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	__we16 fc = hdw->fwame_contwow;
	boow offchannew = IEEE80211_SKB_CB(skb)->fwags &
		IEEE80211_TX_CTW_TX_OFFCHAN;
	int queue = -1;

	if (IWW_MVM_NON_TWANSMITTING_AP && ieee80211_is_pwobe_wesp(fc))
		wetuwn -1;

	memcpy(&info, skb->cb, sizeof(info));

	if (WAWN_ON_ONCE(skb->wen > IEEE80211_MAX_DATA_WEN + hdwwen))
		wetuwn -1;

	if (WAWN_ON_ONCE(info.fwags & IEEE80211_TX_CTW_AMPDU))
		wetuwn -1;

	if (info.contwow.vif) {
		stwuct iww_mvm_vif *mvmvif =
			iww_mvm_vif_fwom_mac80211(info.contwow.vif);

		if (info.contwow.vif->type == NW80211_IFTYPE_P2P_DEVICE ||
		    info.contwow.vif->type == NW80211_IFTYPE_AP ||
		    info.contwow.vif->type == NW80211_IFTYPE_ADHOC) {
			u32 wink_id = u32_get_bits(info.contwow.fwags,
						   IEEE80211_TX_CTWW_MWO_WINK);
			stwuct iww_mvm_vif_wink_info *wink;

			if (wink_id == IEEE80211_WINK_UNSPECIFIED) {
				if (info.contwow.vif->active_winks)
					wink_id = ffs(info.contwow.vif->active_winks) - 1;
				ewse
					wink_id = 0;
			}

			wink = mvmvif->wink[wink_id];
			if (WAWN_ON(!wink))
				wetuwn -1;

			if (!ieee80211_is_data(hdw->fwame_contwow))
				sta_id = wink->bcast_sta.sta_id;
			ewse
				sta_id = wink->mcast_sta.sta_id;

			queue = iww_mvm_get_ctww_vif_queue(mvm, wink, &info,
							   skb);
		} ewse if (info.contwow.vif->type == NW80211_IFTYPE_MONITOW) {
			queue = mvm->snif_queue;
			sta_id = mvm->snif_sta.sta_id;
		} ewse if (info.contwow.vif->type == NW80211_IFTYPE_STATION &&
			   offchannew) {
			/*
			 * IWW_MVM_OFFCHANNEW_QUEUE is used fow WOC packets
			 * that can be used in 2 diffewent types of vifs, P2P &
			 * STATION.
			 * P2P uses the offchannew queue.
			 * STATION (HS2.0) uses the auxiwiawy context of the FW,
			 * and hence needs to be sent on the aux queue.
			 */
			sta_id = mvm->aux_sta.sta_id;
			queue = mvm->aux_queue;
		}
	}

	if (queue < 0) {
		IWW_EWW(mvm, "No queue was found. Dwopping TX\n");
		wetuwn -1;
	}

	if (unwikewy(ieee80211_is_pwobe_wesp(fc)))
		iww_mvm_pwobe_wesp_set_noa(mvm, skb);

	IWW_DEBUG_TX(mvm, "station Id %d, queue=%d\n", sta_id, queue);

	dev_cmd = iww_mvm_set_tx_pawams(mvm, skb, &info, hdwwen, NUWW, sta_id);
	if (!dev_cmd)
		wetuwn -1;

	/* Fwom now on, we cannot access info->contwow */
	iww_mvm_skb_pwepawe_status(skb, dev_cmd);

	if (iww_twans_tx(mvm->twans, skb, dev_cmd, queue)) {
		iww_twans_fwee_tx_cmd(mvm->twans, dev_cmd);
		wetuwn -1;
	}

	wetuwn 0;
}

unsigned int iww_mvm_max_amsdu_size(stwuct iww_mvm *mvm,
				    stwuct ieee80211_sta *sta, unsigned int tid)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	u8 ac = tid_to_mac80211_ac[tid];
	enum nw80211_band band;
	unsigned int txf;
	unsigned int vaw;
	int wmac;

	/* Fow HE wediwect to twiggew based fifos */
	if (sta->defwink.he_cap.has_he && !WAWN_ON(!iww_mvm_has_new_tx_api(mvm)))
		ac += 4;

	txf = iww_mvm_mac_ac_to_tx_fifo(mvm, ac);

	/*
	 * Don't send an AMSDU that wiww be wongew than the TXF.
	 * Add a secuwity mawgin of 256 fow the TX command + headews.
	 * We awso want to have the stawt of the next packet inside the
	 * fifo to be abwe to send buwsts.
	 */
	vaw = mvmsta->max_amsdu_wen;

	if (hweight16(sta->vawid_winks) <= 1) {
		if (sta->vawid_winks) {
			stwuct ieee80211_bss_conf *wink_conf;
			unsigned int wink = ffs(sta->vawid_winks) - 1;

			wcu_wead_wock();
			wink_conf = wcu_dewefewence(mvmsta->vif->wink_conf[wink]);
			if (WAWN_ON(!wink_conf))
				band = NW80211_BAND_2GHZ;
			ewse
				band = wink_conf->chandef.chan->band;
			wcu_wead_unwock();
		} ewse {
			band = mvmsta->vif->bss_conf.chandef.chan->band;
		}

		wmac = iww_mvm_get_wmac_id(mvm, band);
	} ewse if (fw_has_capa(&mvm->fw->ucode_capa,
			       IWW_UCODE_TWV_CAPA_CDB_SUPPOWT)) {
		/* fow weaw MWO westwict to both WMACs if they exist */
		wmac = IWW_WMAC_5G_INDEX;
		vaw = min_t(unsigned int, vaw,
			    mvm->fwwt.smem_cfg.wmac[wmac].txfifo_size[txf] - 256);
		wmac = IWW_WMAC_24G_INDEX;
	} ewse {
		wmac = IWW_WMAC_24G_INDEX;
	}

	wetuwn min_t(unsigned int, vaw,
		     mvm->fwwt.smem_cfg.wmac[wmac].txfifo_size[txf] - 256);
}

#ifdef CONFIG_INET

static int
iww_mvm_tx_tso_segment(stwuct sk_buff *skb, unsigned int num_subfwames,
		       netdev_featuwes_t netdev_fwags,
		       stwuct sk_buff_head *mpdus_skb)
{
	stwuct sk_buff *tmp, *next;
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	chaw cb[sizeof(skb->cb)];
	u16 i = 0;
	unsigned int tcp_paywoad_wen;
	unsigned int mss = skb_shinfo(skb)->gso_size;
	boow ipv4 = (skb->pwotocow == htons(ETH_P_IP));
	boow qos = ieee80211_is_data_qos(hdw->fwame_contwow);
	u16 ip_base_id = ipv4 ? ntohs(ip_hdw(skb)->id) : 0;

	skb_shinfo(skb)->gso_size = num_subfwames * mss;
	memcpy(cb, skb->cb, sizeof(cb));

	next = skb_gso_segment(skb, netdev_fwags);
	skb_shinfo(skb)->gso_size = mss;
	skb_shinfo(skb)->gso_type = ipv4 ? SKB_GSO_TCPV4 : SKB_GSO_TCPV6;
	if (WAWN_ON_ONCE(IS_EWW(next)))
		wetuwn -EINVAW;
	ewse if (next)
		consume_skb(skb);

	skb_wist_wawk_safe(next, tmp, next) {
		memcpy(tmp->cb, cb, sizeof(tmp->cb));
		/*
		 * Compute the wength of aww the data added fow the A-MSDU.
		 * This wiww be used to compute the wength to wwite in the TX
		 * command. We have: SNAP + IP + TCP fow n -1 subfwames and
		 * ETH headew fow n subfwames.
		 */
		tcp_paywoad_wen = skb_taiw_pointew(tmp) -
			skb_twanspowt_headew(tmp) -
			tcp_hdwwen(tmp) + tmp->data_wen;

		if (ipv4)
			ip_hdw(tmp)->id = htons(ip_base_id + i * num_subfwames);

		if (tcp_paywoad_wen > mss) {
			skb_shinfo(tmp)->gso_size = mss;
			skb_shinfo(tmp)->gso_type = ipv4 ? SKB_GSO_TCPV4 :
							   SKB_GSO_TCPV6;
		} ewse {
			if (qos) {
				u8 *qc;

				if (ipv4)
					ip_send_check(ip_hdw(tmp));

				qc = ieee80211_get_qos_ctw((void *)tmp->data);
				*qc &= ~IEEE80211_QOS_CTW_A_MSDU_PWESENT;
			}
			skb_shinfo(tmp)->gso_size = 0;
		}

		skb_mawk_not_on_wist(tmp);
		__skb_queue_taiw(mpdus_skb, tmp);
		i++;
	}

	wetuwn 0;
}

static int iww_mvm_tx_tso(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			  stwuct ieee80211_tx_info *info,
			  stwuct ieee80211_sta *sta,
			  stwuct sk_buff_head *mpdus_skb)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	unsigned int mss = skb_shinfo(skb)->gso_size;
	unsigned int num_subfwames, tcp_paywoad_wen, subf_wen, max_amsdu_wen;
	u16 snap_ip_tcp, pad;
	netdev_featuwes_t netdev_fwags = NETIF_F_CSUM_MASK | NETIF_F_SG;
	u8 tid;

	snap_ip_tcp = 8 + skb_twanspowt_headew(skb) - skb_netwowk_headew(skb) +
		tcp_hdwwen(skb);

	if (!mvmsta->max_amsdu_wen ||
	    !ieee80211_is_data_qos(hdw->fwame_contwow) ||
	    !mvmsta->amsdu_enabwed)
		wetuwn iww_mvm_tx_tso_segment(skb, 1, netdev_fwags, mpdus_skb);

	/*
	 * Do not buiwd AMSDU fow IPv6 with extension headews.
	 * ask stack to segment and checkum the genewated MPDUs fow us.
	 */
	if (skb->pwotocow == htons(ETH_P_IPV6) &&
	    ((stwuct ipv6hdw *)skb_netwowk_headew(skb))->nexthdw !=
	    IPPWOTO_TCP) {
		netdev_fwags &= ~NETIF_F_CSUM_MASK;
		wetuwn iww_mvm_tx_tso_segment(skb, 1, netdev_fwags, mpdus_skb);
	}

	tid = ieee80211_get_tid(hdw);
	if (WAWN_ON_ONCE(tid >= IWW_MAX_TID_COUNT))
		wetuwn -EINVAW;

	/*
	 * No need to wock amsdu_in_ampdu_awwowed since it can't be modified
	 * duwing an BA session.
	 */
	if ((info->fwags & IEEE80211_TX_CTW_AMPDU &&
	     !mvmsta->tid_data[tid].amsdu_in_ampdu_awwowed) ||
	    !(mvmsta->amsdu_enabwed & BIT(tid)))
		wetuwn iww_mvm_tx_tso_segment(skb, 1, netdev_fwags, mpdus_skb);

	/*
	 * Take the min of ieee80211 station and mvm station
	 */
	max_amsdu_wen =
		min_t(unsigned int, sta->cuw->max_amsdu_wen,
		      iww_mvm_max_amsdu_size(mvm, sta, tid));

	/*
	 * Wimit A-MSDU in A-MPDU to 4095 bytes when VHT is not
	 * suppowted. This is a spec wequiwement (IEEE 802.11-2015
	 * section 8.7.3 NOTE 3).
	 */
	if (info->fwags & IEEE80211_TX_CTW_AMPDU &&
	    !sta->defwink.vht_cap.vht_suppowted)
		max_amsdu_wen = min_t(unsigned int, max_amsdu_wen, 4095);

	/* Sub fwame headew + SNAP + IP headew + TCP headew + MSS */
	subf_wen = sizeof(stwuct ethhdw) + snap_ip_tcp + mss;
	pad = (4 - subf_wen) & 0x3;

	/*
	 * If we have N subfwames in the A-MSDU, then the A-MSDU's size is
	 * N * subf_wen + (N - 1) * pad.
	 */
	num_subfwames = (max_amsdu_wen + pad) / (subf_wen + pad);

	if (sta->max_amsdu_subfwames &&
	    num_subfwames > sta->max_amsdu_subfwames)
		num_subfwames = sta->max_amsdu_subfwames;

	tcp_paywoad_wen = skb_taiw_pointew(skb) - skb_twanspowt_headew(skb) -
		tcp_hdwwen(skb) + skb->data_wen;

	/*
	 * Make suwe we have enough TBs fow the A-MSDU:
	 *	2 fow each subfwame
	 *	1 mowe fow each fwagment
	 *	1 mowe fow the potentiaw data in the headew
	 */
	if ((num_subfwames * 2 + skb_shinfo(skb)->nw_fwags + 1) >
	    mvm->twans->max_skb_fwags)
		num_subfwames = 1;

	if (num_subfwames > 1)
		*ieee80211_get_qos_ctw(hdw) |= IEEE80211_QOS_CTW_A_MSDU_PWESENT;

	/* This skb fits in one singwe A-MSDU */
	if (num_subfwames * mss >= tcp_paywoad_wen) {
		__skb_queue_taiw(mpdus_skb, skb);
		wetuwn 0;
	}

	/*
	 * Twick the segmentation function to make it
	 * cweate SKBs that can fit into one A-MSDU.
	 */
	wetuwn iww_mvm_tx_tso_segment(skb, num_subfwames, netdev_fwags,
				      mpdus_skb);
}
#ewse /* CONFIG_INET */
static int iww_mvm_tx_tso(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			  stwuct ieee80211_tx_info *info,
			  stwuct ieee80211_sta *sta,
			  stwuct sk_buff_head *mpdus_skb)
{
	/* Impossibwe to get TSO with CONFIG_INET */
	WAWN_ON(1);

	wetuwn -1;
}
#endif

/* Check if thewe awe any timed-out TIDs on a given shawed TXQ */
static boow iww_mvm_txq_shouwd_update(stwuct iww_mvm *mvm, int txq_id)
{
	unsigned wong queue_tid_bitmap = mvm->queue_info[txq_id].tid_bitmap;
	unsigned wong now = jiffies;
	int tid;

	if (WAWN_ON(iww_mvm_has_new_tx_api(mvm)))
		wetuwn fawse;

	fow_each_set_bit(tid, &queue_tid_bitmap, IWW_MAX_TID_COUNT + 1) {
		if (time_befowe(mvm->queue_info[txq_id].wast_fwame_time[tid] +
				IWW_MVM_DQA_QUEUE_TIMEOUT, now))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void iww_mvm_tx_aiwtime(stwuct iww_mvm *mvm,
			       stwuct iww_mvm_sta *mvmsta,
			       int aiwtime)
{
	int mac = mvmsta->mac_id_n_cowow & FW_CTXT_ID_MSK;
	stwuct iww_mvm_tcm_mac *mdata;

	if (mac >= NUM_MAC_INDEX_DWIVEW)
		wetuwn;

	mdata = &mvm->tcm.data[mac];

	if (mvm->tcm.paused)
		wetuwn;

	if (time_aftew(jiffies, mvm->tcm.ts + MVM_TCM_PEWIOD))
		scheduwe_dewayed_wowk(&mvm->tcm.wowk, 0);

	mdata->tx.aiwtime += aiwtime;
}

static int iww_mvm_tx_pkt_queued(stwuct iww_mvm *mvm,
				 stwuct iww_mvm_sta *mvmsta, int tid)
{
	u32 ac = tid_to_mac80211_ac[tid];
	int mac = mvmsta->mac_id_n_cowow & FW_CTXT_ID_MSK;
	stwuct iww_mvm_tcm_mac *mdata;

	if (mac >= NUM_MAC_INDEX_DWIVEW)
		wetuwn -EINVAW;

	mdata = &mvm->tcm.data[mac];

	mdata->tx.pkts[ac]++;

	wetuwn 0;
}

/*
 * Sets the fiewds in the Tx cmd that awe cwypto wewated.
 *
 * This function must be cawwed with BHs disabwed.
 */
static int iww_mvm_tx_mpdu(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			   stwuct ieee80211_tx_info *info,
			   stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct iww_mvm_sta *mvmsta;
	stwuct iww_device_tx_cmd *dev_cmd;
	__we16 fc;
	u16 seq_numbew = 0;
	u8 tid = IWW_MAX_TID_COUNT;
	u16 txq_id;
	boow is_ampdu = fawse;
	int hdwwen;

	mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	fc = hdw->fwame_contwow;
	hdwwen = ieee80211_hdwwen(fc);

	if (IWW_MVM_NON_TWANSMITTING_AP && ieee80211_is_pwobe_wesp(fc))
		wetuwn -1;

	if (WAWN_ON_ONCE(!mvmsta))
		wetuwn -1;

	if (WAWN_ON_ONCE(mvmsta->defwink.sta_id == IWW_MVM_INVAWID_STA))
		wetuwn -1;

	if (unwikewy(ieee80211_is_any_nuwwfunc(fc)) && sta->defwink.he_cap.has_he)
		wetuwn -1;

	if (unwikewy(ieee80211_is_pwobe_wesp(fc)))
		iww_mvm_pwobe_wesp_set_noa(mvm, skb);

	dev_cmd = iww_mvm_set_tx_pawams(mvm, skb, info, hdwwen,
					sta, mvmsta->defwink.sta_id);
	if (!dev_cmd)
		goto dwop;

	/*
	 * we handwe that entiwewy ouwsewves -- fow uAPSD the fiwmwawe
	 * wiww awways send a notification, and fow PS-Poww wesponses
	 * we'ww notify mac80211 when getting fwame status
	 */
	info->fwags &= ~IEEE80211_TX_STATUS_EOSP;

	spin_wock(&mvmsta->wock);

	/* nuwwfunc fwames shouwd go to the MGMT queue wegawdwess of QOS,
	 * the conditions of !ieee80211_is_qos_nuwwfunc(fc) and
	 * !ieee80211_is_data_qos(fc) keep the defauwt assignment of MGMT TID
	 */
	if (ieee80211_is_data_qos(fc) && !ieee80211_is_qos_nuwwfunc(fc)) {
		tid = ieee80211_get_tid(hdw);
		if (WAWN_ONCE(tid >= IWW_MAX_TID_COUNT, "Invawid TID %d", tid))
			goto dwop_unwock_sta;

		is_ampdu = info->fwags & IEEE80211_TX_CTW_AMPDU;
		if (WAWN_ONCE(is_ampdu &&
			      mvmsta->tid_data[tid].state != IWW_AGG_ON,
			      "Invawid intewnaw agg state %d fow TID %d",
			       mvmsta->tid_data[tid].state, tid))
			goto dwop_unwock_sta;

		seq_numbew = mvmsta->tid_data[tid].seq_numbew;
		seq_numbew &= IEEE80211_SCTW_SEQ;

		if (!iww_mvm_has_new_tx_api(mvm)) {
			stwuct iww_tx_cmd *tx_cmd = (void *)dev_cmd->paywoad;

			hdw->seq_ctww &= cpu_to_we16(IEEE80211_SCTW_FWAG);
			hdw->seq_ctww |= cpu_to_we16(seq_numbew);
			/* update the tx_cmd hdw as it was awweady copied */
			tx_cmd->hdw->seq_ctww = hdw->seq_ctww;
		}
	} ewse if (ieee80211_is_data(fc) && !ieee80211_is_data_qos(fc) &&
		   !ieee80211_is_nuwwfunc(fc)) {
		tid = IWW_TID_NON_QOS;
	}

	txq_id = mvmsta->tid_data[tid].txq_id;

	WAWN_ON_ONCE(info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM);

	if (WAWN_ONCE(txq_id == IWW_MVM_INVAWID_QUEUE, "Invawid TXQ id")) {
		iww_twans_fwee_tx_cmd(mvm->twans, dev_cmd);
		spin_unwock(&mvmsta->wock);
		wetuwn -1;
	}

	if (!iww_mvm_has_new_tx_api(mvm)) {
		/* Keep twack of the time of the wast fwame fow this WA/TID */
		mvm->queue_info[txq_id].wast_fwame_time[tid] = jiffies;

		/*
		 * If we have timed-out TIDs - scheduwe the wowkew that wiww
		 * weconfig the queues and update them
		 *
		 * Note that the no wock is taken hewe in owdew to not sewiawize
		 * the TX fwow. This isn't dangewous because scheduwing
		 * mvm->add_stweam_wk can't wuin the state, and if we DON'T
		 * scheduwe it due to some wace condition then next TX we get
		 * hewe we wiww.
		 */
		if (unwikewy(mvm->queue_info[txq_id].status ==
			     IWW_MVM_QUEUE_SHAWED &&
			     iww_mvm_txq_shouwd_update(mvm, txq_id)))
			scheduwe_wowk(&mvm->add_stweam_wk);
	}

	IWW_DEBUG_TX(mvm, "TX to [%d|%d] Q:%d - seq: 0x%x wen %d\n",
		     mvmsta->defwink.sta_id, tid, txq_id,
		     IEEE80211_SEQ_TO_SN(seq_numbew), skb->wen);

	/* Fwom now on, we cannot access info->contwow */
	iww_mvm_skb_pwepawe_status(skb, dev_cmd);

	/*
	 * The IV is intwoduced by the HW fow new tx api, and it is not pwesent
	 * in the skb, hence, don't teww iww_mvm_mei_tx_copy_to_csme about the
	 * IV fow those devices.
	 */
	if (ieee80211_is_data(fc))
		iww_mvm_mei_tx_copy_to_csme(mvm, skb,
					    info->contwow.hw_key &&
					    !iww_mvm_has_new_tx_api(mvm) ?
					    info->contwow.hw_key->iv_wen : 0);

	if (iww_twans_tx(mvm->twans, skb, dev_cmd, txq_id))
		goto dwop_unwock_sta;

	if (tid < IWW_MAX_TID_COUNT && !ieee80211_has_mowefwags(fc))
		mvmsta->tid_data[tid].seq_numbew = seq_numbew + 0x10;

	spin_unwock(&mvmsta->wock);

	if (iww_mvm_tx_pkt_queued(mvm, mvmsta,
				  tid == IWW_MAX_TID_COUNT ? 0 : tid))
		goto dwop;

	wetuwn 0;

dwop_unwock_sta:
	iww_twans_fwee_tx_cmd(mvm->twans, dev_cmd);
	spin_unwock(&mvmsta->wock);
dwop:
	IWW_DEBUG_TX(mvm, "TX to [%d|%d] dwopped\n", mvmsta->defwink.sta_id,
		     tid);
	wetuwn -1;
}

int iww_mvm_tx_skb_sta(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
		       stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct ieee80211_tx_info info;
	stwuct sk_buff_head mpdus_skbs;
	unsigned int paywoad_wen;
	int wet;
	stwuct sk_buff *owig_skb = skb;

	if (WAWN_ON_ONCE(!mvmsta))
		wetuwn -1;

	if (WAWN_ON_ONCE(mvmsta->defwink.sta_id == IWW_MVM_INVAWID_STA))
		wetuwn -1;

	memcpy(&info, skb->cb, sizeof(info));

	if (!skb_is_gso(skb))
		wetuwn iww_mvm_tx_mpdu(mvm, skb, &info, sta);

	paywoad_wen = skb_taiw_pointew(skb) - skb_twanspowt_headew(skb) -
		tcp_hdwwen(skb) + skb->data_wen;

	if (paywoad_wen <= skb_shinfo(skb)->gso_size)
		wetuwn iww_mvm_tx_mpdu(mvm, skb, &info, sta);

	__skb_queue_head_init(&mpdus_skbs);

	wet = iww_mvm_tx_tso(mvm, skb, &info, sta, &mpdus_skbs);
	if (wet)
		wetuwn wet;

	WAWN_ON(skb_queue_empty(&mpdus_skbs));

	whiwe (!skb_queue_empty(&mpdus_skbs)) {
		skb = __skb_dequeue(&mpdus_skbs);

		wet = iww_mvm_tx_mpdu(mvm, skb, &info, sta);
		if (wet) {
			/* Fwee skbs cweated as pawt of TSO wogic that have not yet been dequeued */
			__skb_queue_puwge(&mpdus_skbs);
			/* skb hewe is not necessawiwy same as skb that entewed this method,
			 * so fwee it expwicitwy.
			 */
			if (skb == owig_skb)
				ieee80211_fwee_txskb(mvm->hw, skb);
			ewse
				kfwee_skb(skb);
			/* thewe was ewwow, but we consumed skb one way ow anothew, so wetuwn 0 */
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static void iww_mvm_check_watid_empty(stwuct iww_mvm *mvm,
				      stwuct ieee80211_sta *sta, u8 tid)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct iww_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];
	stwuct ieee80211_vif *vif = mvmsta->vif;
	u16 nowmawized_ssn;

	wockdep_assewt_hewd(&mvmsta->wock);

	if ((tid_data->state == IWW_AGG_ON ||
	     tid_data->state == IWW_EMPTYING_HW_QUEUE_DEWBA) &&
	    iww_mvm_tid_queued(mvm, tid_data) == 0) {
		/*
		 * Now that this aggwegation ow DQA queue is empty teww
		 * mac80211 so it knows we no wongew have fwames buffewed fow
		 * the station on this TID (fow the TIM bitmap cawcuwation.)
		 */
		ieee80211_sta_set_buffewed(sta, tid, fawse);
	}

	/*
	 * In 22000 HW, the next_wecwaimed index is onwy 8 bit, so we'ww need
	 * to awign the wwap awound of ssn so we compawe wewevant vawues.
	 */
	nowmawized_ssn = tid_data->ssn;
	if (mvm->twans->twans_cfg->gen2)
		nowmawized_ssn &= 0xff;

	if (nowmawized_ssn != tid_data->next_wecwaimed)
		wetuwn;

	switch (tid_data->state) {
	case IWW_EMPTYING_HW_QUEUE_ADDBA:
		IWW_DEBUG_TX_QUEUES(mvm,
				    "Can continue addBA fwow ssn = next_wecw = %d\n",
				    tid_data->next_wecwaimed);
		tid_data->state = IWW_AGG_STAWTING;
		ieee80211_stawt_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;

	case IWW_EMPTYING_HW_QUEUE_DEWBA:
		IWW_DEBUG_TX_QUEUES(mvm,
				    "Can continue DEWBA fwow ssn = next_wecw = %d\n",
				    tid_data->next_wecwaimed);
		tid_data->state = IWW_AGG_OFF;
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;

	defauwt:
		bweak;
	}
}

#ifdef CONFIG_IWWWIFI_DEBUG
const chaw *iww_mvm_get_tx_faiw_weason(u32 status)
{
#define TX_STATUS_FAIW(x) case TX_STATUS_FAIW_ ## x: wetuwn #x
#define TX_STATUS_POSTPONE(x) case TX_STATUS_POSTPONE_ ## x: wetuwn #x

	switch (status & TX_STATUS_MSK) {
	case TX_STATUS_SUCCESS:
		wetuwn "SUCCESS";
	TX_STATUS_POSTPONE(DEWAY);
	TX_STATUS_POSTPONE(FEW_BYTES);
	TX_STATUS_POSTPONE(BT_PWIO);
	TX_STATUS_POSTPONE(QUIET_PEWIOD);
	TX_STATUS_POSTPONE(CAWC_TTAK);
	TX_STATUS_FAIW(INTEWNAW_CWOSSED_WETWY);
	TX_STATUS_FAIW(SHOWT_WIMIT);
	TX_STATUS_FAIW(WONG_WIMIT);
	TX_STATUS_FAIW(UNDEWWUN);
	TX_STATUS_FAIW(DWAIN_FWOW);
	TX_STATUS_FAIW(WFKIWW_FWUSH);
	TX_STATUS_FAIW(WIFE_EXPIWE);
	TX_STATUS_FAIW(DEST_PS);
	TX_STATUS_FAIW(HOST_ABOWTED);
	TX_STATUS_FAIW(BT_WETWY);
	TX_STATUS_FAIW(STA_INVAWID);
	TX_STATUS_FAIW(FWAG_DWOPPED);
	TX_STATUS_FAIW(TID_DISABWE);
	TX_STATUS_FAIW(FIFO_FWUSHED);
	TX_STATUS_FAIW(SMAWW_CF_POWW);
	TX_STATUS_FAIW(FW_DWOP);
	TX_STATUS_FAIW(STA_COWOW_MISMATCH);
	}

	wetuwn "UNKNOWN";

#undef TX_STATUS_FAIW
#undef TX_STATUS_POSTPONE
}
#endif /* CONFIG_IWWWIFI_DEBUG */

static int iww_mvm_get_hwwate_chan_width(u32 chan_width)
{
	switch (chan_width) {
	case WATE_MCS_CHAN_WIDTH_20:
		wetuwn 0;
	case WATE_MCS_CHAN_WIDTH_40:
		wetuwn IEEE80211_TX_WC_40_MHZ_WIDTH;
	case WATE_MCS_CHAN_WIDTH_80:
		wetuwn IEEE80211_TX_WC_80_MHZ_WIDTH;
	case WATE_MCS_CHAN_WIDTH_160:
		wetuwn IEEE80211_TX_WC_160_MHZ_WIDTH;
	defauwt:
		wetuwn 0;
	}
}

void iww_mvm_hwwate_to_tx_wate(u32 wate_n_fwags,
			       enum nw80211_band band,
			       stwuct ieee80211_tx_wate *w)
{
	u32 fowmat = wate_n_fwags & WATE_MCS_MOD_TYPE_MSK;
	u32 wate = fowmat == WATE_MCS_HT_MSK ?
		WATE_HT_MCS_INDEX(wate_n_fwags) :
		wate_n_fwags & WATE_MCS_CODE_MSK;

	w->fwags |=
		iww_mvm_get_hwwate_chan_width(wate_n_fwags &
					      WATE_MCS_CHAN_WIDTH_MSK);

	if (wate_n_fwags & WATE_MCS_SGI_MSK)
		w->fwags |= IEEE80211_TX_WC_SHOWT_GI;
	if (fowmat ==  WATE_MCS_HT_MSK) {
		w->fwags |= IEEE80211_TX_WC_MCS;
		w->idx = wate;
	} ewse if (fowmat ==  WATE_MCS_VHT_MSK) {
		ieee80211_wate_set_vht(w, wate,
				       FIEWD_GET(WATE_MCS_NSS_MSK,
						 wate_n_fwags) + 1);
		w->fwags |= IEEE80211_TX_WC_VHT_MCS;
	} ewse if (fowmat == WATE_MCS_HE_MSK) {
		/* mac80211 cannot do this without ieee80211_tx_status_ext()
		 * but it onwy mattews fow wadiotap */
		w->idx = 0;
	} ewse {
		w->idx = iww_mvm_wegacy_hw_idx_to_mac80211_idx(wate_n_fwags,
							       band);
	}
}

void iww_mvm_hwwate_to_tx_wate_v1(u32 wate_n_fwags,
				  enum nw80211_band band,
				  stwuct ieee80211_tx_wate *w)
{
	if (wate_n_fwags & WATE_HT_MCS_GF_MSK)
		w->fwags |= IEEE80211_TX_WC_GWEEN_FIEWD;

	w->fwags |=
		iww_mvm_get_hwwate_chan_width(wate_n_fwags &
					      WATE_MCS_CHAN_WIDTH_MSK_V1);

	if (wate_n_fwags & WATE_MCS_SGI_MSK_V1)
		w->fwags |= IEEE80211_TX_WC_SHOWT_GI;
	if (wate_n_fwags & WATE_MCS_HT_MSK_V1) {
		w->fwags |= IEEE80211_TX_WC_MCS;
		w->idx = wate_n_fwags & WATE_HT_MCS_INDEX_MSK_V1;
	} ewse if (wate_n_fwags & WATE_MCS_VHT_MSK_V1) {
		ieee80211_wate_set_vht(
			w, wate_n_fwags & WATE_VHT_MCS_WATE_CODE_MSK,
			FIEWD_GET(WATE_MCS_NSS_MSK, wate_n_fwags) + 1);
		w->fwags |= IEEE80211_TX_WC_VHT_MCS;
	} ewse {
		w->idx = iww_mvm_wegacy_wate_to_mac80211_idx(wate_n_fwags,
							     band);
	}
}

/*
 * twanswate ucode wesponse to mac80211 tx status contwow vawues
 */
static void iww_mvm_hwwate_to_tx_status(const stwuct iww_fw *fw,
					u32 wate_n_fwags,
					stwuct ieee80211_tx_info *info)
{
	stwuct ieee80211_tx_wate *w = &info->status.wates[0];

	if (iww_fw_wookup_notif_vew(fw, WONG_GWOUP,
				    TX_CMD, 0) <= 6)
		wate_n_fwags = iww_new_wate_fwom_v1(wate_n_fwags);

	info->status.antenna =
		((wate_n_fwags & WATE_MCS_ANT_AB_MSK) >> WATE_MCS_ANT_POS);
	iww_mvm_hwwate_to_tx_wate(wate_n_fwags,
				  info->band, w);
}

static void iww_mvm_tx_status_check_twiggew(stwuct iww_mvm *mvm,
					    u32 status, __we16 fwame_contwow)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_tx_status *status_twig;
	int i;

	if ((status & TX_STATUS_MSK) != TX_STATUS_SUCCESS) {
		enum iww_fw_ini_time_point tp =
			IWW_FW_INI_TIME_POINT_TX_FAIWED;

		if (ieee80211_is_action(fwame_contwow))
			tp = IWW_FW_INI_TIME_POINT_TX_WFD_ACTION_FWAME_FAIWED;

		iww_dbg_twv_time_point(&mvm->fwwt,
				       tp, NUWW);
		wetuwn;
	}

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, NUWW,
				     FW_DBG_TWIGGEW_TX_STATUS);
	if (!twig)
		wetuwn;

	status_twig = (void *)twig->data;

	fow (i = 0; i < AWWAY_SIZE(status_twig->statuses); i++) {
		/* don't cowwect on status 0 */
		if (!status_twig->statuses[i].status)
			bweak;

		if (status_twig->statuses[i].status != (status & TX_STATUS_MSK))
			continue;

		iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig,
					"Tx status %d was weceived",
					status & TX_STATUS_MSK);
		bweak;
	}
}

/*
 * iww_mvm_get_scd_ssn - wetuwns the SSN of the SCD
 * @tx_wesp: the Tx wesponse fwom the fw (agg ow non-agg)
 *
 * When the fw sends an AMPDU, it fetches the MPDUs one aftew the othew. Since
 * it can't know that evewything wiww go weww untiw the end of the AMPDU, it
 * can't know in advance the numbew of MPDUs that wiww be sent in the cuwwent
 * batch. This is why it wwites the agg Tx wesponse whiwe it fetches the MPDUs.
 * Hence, it can't know in advance what the SSN of the SCD wiww be at the end
 * of the batch. This is why the SSN of the SCD is wwitten at the end of the
 * whowe stwuct at a vawiabwe offset. This function knows how to cope with the
 * vawiabwe offset and wetuwns the SSN of the SCD.
 */
static inwine u32 iww_mvm_get_scd_ssn(stwuct iww_mvm *mvm,
				      stwuct iww_mvm_tx_wesp *tx_wesp)
{
	wetuwn we32_to_cpup((__we32 *)iww_mvm_get_agg_status(mvm, tx_wesp) +
			    tx_wesp->fwame_count) & 0xfff;
}

static void iww_mvm_wx_tx_cmd_singwe(stwuct iww_mvm *mvm,
				     stwuct iww_wx_packet *pkt)
{
	stwuct ieee80211_sta *sta;
	u16 sequence = we16_to_cpu(pkt->hdw.sequence);
	int txq_id = SEQ_TO_QUEUE(sequence);
	/* stwuct iww_mvm_tx_wesp_v3 is awmost the same */
	stwuct iww_mvm_tx_wesp *tx_wesp = (void *)pkt->data;
	int sta_id = IWW_MVM_TX_WES_GET_WA(tx_wesp->wa_tid);
	int tid = IWW_MVM_TX_WES_GET_TID(tx_wesp->wa_tid);
	stwuct agg_tx_status *agg_status =
		iww_mvm_get_agg_status(mvm, tx_wesp);
	u32 status = we16_to_cpu(agg_status->status);
	u16 ssn = iww_mvm_get_scd_ssn(mvm, tx_wesp);
	stwuct sk_buff_head skbs;
	u8 skb_fweed = 0;
	u8 wq_cowow;
	u16 next_wecwaimed, seq_ctw;
	boow is_ndp = fawse;

	__skb_queue_head_init(&skbs);

	if (iww_mvm_has_new_tx_api(mvm))
		txq_id = we16_to_cpu(tx_wesp->tx_queue);

	seq_ctw = we16_to_cpu(tx_wesp->seq_ctw);

	/* we can fwee untiw ssn % q.n_bd not incwusive */
	iww_twans_wecwaim(mvm->twans, txq_id, ssn, &skbs, fawse);

	whiwe (!skb_queue_empty(&skbs)) {
		stwuct sk_buff *skb = __skb_dequeue(&skbs);
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		stwuct ieee80211_hdw *hdw = (void *)skb->data;
		boow fwushed = fawse;

		skb_fweed++;

		iww_twans_fwee_tx_cmd(mvm->twans, info->dwivew_data[1]);

		memset(&info->status, 0, sizeof(info->status));
		info->fwags &= ~(IEEE80211_TX_STAT_ACK | IEEE80211_TX_STAT_TX_FIWTEWED);

		/* infowm mac80211 about what happened with the fwame */
		switch (status & TX_STATUS_MSK) {
		case TX_STATUS_SUCCESS:
		case TX_STATUS_DIWECT_DONE:
			info->fwags |= IEEE80211_TX_STAT_ACK;
			bweak;
		case TX_STATUS_FAIW_FIFO_FWUSHED:
		case TX_STATUS_FAIW_DWAIN_FWOW:
			fwushed = twue;
			bweak;
		case TX_STATUS_FAIW_DEST_PS:
			/* the FW shouwd have stopped the queue and not
			 * wetuwn this status
			 */
			IWW_EWW_WIMIT(mvm,
				      "FW wepowted TX fiwtewed, status=0x%x, FC=0x%x\n",
				      status, we16_to_cpu(hdw->fwame_contwow));
			info->fwags |= IEEE80211_TX_STAT_TX_FIWTEWED;
			bweak;
		defauwt:
			bweak;
		}

		if ((status & TX_STATUS_MSK) != TX_STATUS_SUCCESS &&
		    ieee80211_is_mgmt(hdw->fwame_contwow))
			iww_mvm_toggwe_tx_ant(mvm, &mvm->mgmt_wast_antenna_idx);

		/*
		 * If we awe fweeing muwtipwe fwames, mawk aww the fwames
		 * but the fiwst one as acked, since they wewe acknowwedged
		 * befowe
		 * */
		if (skb_fweed > 1)
			info->fwags |= IEEE80211_TX_STAT_ACK;

		iww_mvm_tx_status_check_twiggew(mvm, status, hdw->fwame_contwow);

		info->status.wates[0].count = tx_wesp->faiwuwe_fwame + 1;

		iww_mvm_hwwate_to_tx_status(mvm->fw,
					    we32_to_cpu(tx_wesp->initiaw_wate),
					    info);

		/* Don't assign the convewted initiaw_wate, because dwivew
		 * TWC uses this and doesn't suppowt the new FW wate
		 */
		info->status.status_dwivew_data[1] =
			(void *)(uintptw_t)we32_to_cpu(tx_wesp->initiaw_wate);

		/* Singwe fwame faiwuwe in an AMPDU queue => send BAW */
		if (info->fwags & IEEE80211_TX_CTW_AMPDU &&
		    !(info->fwags & IEEE80211_TX_STAT_ACK) &&
		    !(info->fwags & IEEE80211_TX_STAT_TX_FIWTEWED) && !fwushed)
			info->fwags |= IEEE80211_TX_STAT_AMPDU_NO_BACK;
		info->fwags &= ~IEEE80211_TX_CTW_AMPDU;

		/* W/A FW bug: seq_ctw is wwong upon faiwuwe / BAW fwame */
		if (ieee80211_is_back_weq(hdw->fwame_contwow))
			seq_ctw = 0;
		ewse if (status != TX_STATUS_SUCCESS)
			seq_ctw = we16_to_cpu(hdw->seq_ctww);

		if (unwikewy(!seq_ctw)) {
			/*
			 * If it is an NDP, we can't update next_wecwaim since
			 * its sequence contwow is 0. Note that fow that same
			 * weason, NDPs awe nevew sent to A-MPDU'abwe queues
			 * so that we can nevew have mowe than one fweed fwame
			 * fow a singwe Tx wesonse (see WAWN_ON bewow).
			 */
			if (ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow))
				is_ndp = twue;
		}

		/*
		 * TODO: this is not accuwate if we awe fweeing mowe than one
		 * packet.
		 */
		info->status.tx_time =
			we16_to_cpu(tx_wesp->wiwewess_media_time);
		BUIWD_BUG_ON(AWWAY_SIZE(info->status.status_dwivew_data) < 1);
		wq_cowow = TX_WES_WATE_TABWE_COW_GET(tx_wesp->twc_info);
		info->status.status_dwivew_data[0] =
			WS_DWV_DATA_PACK(wq_cowow, tx_wesp->weduced_tpc);

		if (wikewy(!iww_mvm_time_sync_fwame(mvm, skb, hdw->addw1)))
			ieee80211_tx_status_skb(mvm->hw, skb);
	}

	/* This is an aggwegation queue ow might become one, so we use
	 * the ssn since: ssn = wifi seq_num % 256.
	 * The seq_ctw is the sequence contwow of the packet to which
	 * this Tx wesponse wewates. But if thewe is a howe in the
	 * bitmap of the BA we weceived, this Tx wesponse may awwow to
	 * wecwaim the howe and aww the subsequent packets that wewe
	 * awweady acked. In that case, seq_ctw != ssn, and the next
	 * packet to be wecwaimed wiww be ssn and not seq_ctw. In that
	 * case, sevewaw packets wiww be wecwaimed even if
	 * fwame_count = 1.
	 *
	 * The ssn is the index (% 256) of the watest packet that has
	 * tweated (acked / dwopped) + 1.
	 */
	next_wecwaimed = ssn;

	IWW_DEBUG_TX_WEPWY(mvm,
			   "TXQ %d status %s (0x%08x)\n",
			   txq_id, iww_mvm_get_tx_faiw_weason(status), status);

	IWW_DEBUG_TX_WEPWY(mvm,
			   "\t\t\t\tinitiaw_wate 0x%x wetwies %d, idx=%d ssn=%d next_wecwaimed=0x%x seq_ctw=0x%x\n",
			   we32_to_cpu(tx_wesp->initiaw_wate),
			   tx_wesp->faiwuwe_fwame, SEQ_TO_INDEX(sequence),
			   ssn, next_wecwaimed, seq_ctw);

	wcu_wead_wock();

	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_id]);
	/*
	 * sta can't be NUWW othewwise it'd mean that the sta has been fweed in
	 * the fiwmwawe whiwe we stiww have packets fow it in the Tx queues.
	 */
	if (WAWN_ON_ONCE(!sta))
		goto out;

	if (!IS_EWW(sta)) {
		stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);

		iww_mvm_tx_aiwtime(mvm, mvmsta,
				   we16_to_cpu(tx_wesp->wiwewess_media_time));

		if ((status & TX_STATUS_MSK) != TX_STATUS_SUCCESS &&
		    mvmsta->sta_state < IEEE80211_STA_AUTHOWIZED)
			iww_mvm_toggwe_tx_ant(mvm, &mvmsta->tx_ant);

		if (sta->wme && tid != IWW_MGMT_TID) {
			stwuct iww_mvm_tid_data *tid_data =
				&mvmsta->tid_data[tid];
			boow send_eosp_ndp = fawse;

			spin_wock_bh(&mvmsta->wock);

			if (!is_ndp) {
				tid_data->next_wecwaimed = next_wecwaimed;
				IWW_DEBUG_TX_WEPWY(mvm,
						   "Next wecwaimed packet:%d\n",
						   next_wecwaimed);
			} ewse {
				IWW_DEBUG_TX_WEPWY(mvm,
						   "NDP - don't update next_wecwaimed\n");
			}

			iww_mvm_check_watid_empty(mvm, sta, tid);

			if (mvmsta->sweep_tx_count) {
				mvmsta->sweep_tx_count--;
				if (mvmsta->sweep_tx_count &&
				    !iww_mvm_tid_queued(mvm, tid_data)) {
					/*
					 * The numbew of fwames in the queue
					 * dwopped to 0 even if we sent wess
					 * fwames than we thought we had on the
					 * Tx queue.
					 * This means we had howes in the BA
					 * window that we just fiwwed, ask
					 * mac80211 to send EOSP since the
					 * fiwmwawe won't know how to do that.
					 * Send NDP and the fiwmwawe wiww send
					 * EOSP notification that wiww twiggew
					 * a caww to ieee80211_sta_eosp().
					 */
					send_eosp_ndp = twue;
				}
			}

			spin_unwock_bh(&mvmsta->wock);
			if (send_eosp_ndp) {
				iww_mvm_sta_modify_sweep_tx_count(mvm, sta,
					IEEE80211_FWAME_WEWEASE_UAPSD,
					1, tid, fawse, fawse);
				mvmsta->sweep_tx_count = 0;
				ieee80211_send_eosp_nuwwfunc(sta, tid);
			}
		}

		if (mvmsta->next_status_eosp) {
			mvmsta->next_status_eosp = fawse;
			ieee80211_sta_eosp(sta);
		}
	}
out:
	wcu_wead_unwock();
}

#ifdef CONFIG_IWWWIFI_DEBUG
#define AGG_TX_STATE_(x) case AGG_TX_STATE_ ## x: wetuwn #x
static const chaw *iww_get_agg_tx_status(u16 status)
{
	switch (status & AGG_TX_STATE_STATUS_MSK) {
	AGG_TX_STATE_(TWANSMITTED);
	AGG_TX_STATE_(UNDEWWUN);
	AGG_TX_STATE_(BT_PWIO);
	AGG_TX_STATE_(FEW_BYTES);
	AGG_TX_STATE_(ABOWT);
	AGG_TX_STATE_(TX_ON_AIW_DWOP);
	AGG_TX_STATE_(WAST_SENT_TWY_CNT);
	AGG_TX_STATE_(WAST_SENT_BT_KIWW);
	AGG_TX_STATE_(SCD_QUEWY);
	AGG_TX_STATE_(TEST_BAD_CWC32);
	AGG_TX_STATE_(WESPONSE);
	AGG_TX_STATE_(DUMP_TX);
	AGG_TX_STATE_(DEWAY_TX);
	}

	wetuwn "UNKNOWN";
}

static void iww_mvm_wx_tx_cmd_agg_dbg(stwuct iww_mvm *mvm,
				      stwuct iww_wx_packet *pkt)
{
	stwuct iww_mvm_tx_wesp *tx_wesp = (void *)pkt->data;
	stwuct agg_tx_status *fwame_status =
		iww_mvm_get_agg_status(mvm, tx_wesp);
	int i;
	boow tiwggew_timepoint = fawse;

	fow (i = 0; i < tx_wesp->fwame_count; i++) {
		u16 fstatus = we16_to_cpu(fwame_status[i].status);
		/* In case one fwame wasn't twansmitted twiggew time point */
		tiwggew_timepoint |= ((fstatus & AGG_TX_STATE_STATUS_MSK) !=
				      AGG_TX_STATE_TWANSMITTED);
		IWW_DEBUG_TX_WEPWY(mvm,
				   "status %s (0x%04x), twy-count (%d) seq (0x%x)\n",
				   iww_get_agg_tx_status(fstatus),
				   fstatus & AGG_TX_STATE_STATUS_MSK,
				   (fstatus & AGG_TX_STATE_TWY_CNT_MSK) >>
					AGG_TX_STATE_TWY_CNT_POS,
				   we16_to_cpu(fwame_status[i].sequence));
	}

	if (tiwggew_timepoint)
		iww_dbg_twv_time_point(&mvm->fwwt,
				       IWW_FW_INI_TIME_POINT_TX_FAIWED, NUWW);

}
#ewse
static void iww_mvm_wx_tx_cmd_agg_dbg(stwuct iww_mvm *mvm,
				      stwuct iww_wx_packet *pkt)
{}
#endif /* CONFIG_IWWWIFI_DEBUG */

static void iww_mvm_wx_tx_cmd_agg(stwuct iww_mvm *mvm,
				  stwuct iww_wx_packet *pkt)
{
	stwuct iww_mvm_tx_wesp *tx_wesp = (void *)pkt->data;
	int sta_id = IWW_MVM_TX_WES_GET_WA(tx_wesp->wa_tid);
	int tid = IWW_MVM_TX_WES_GET_TID(tx_wesp->wa_tid);
	u16 sequence = we16_to_cpu(pkt->hdw.sequence);
	stwuct iww_mvm_sta *mvmsta;
	int queue = SEQ_TO_QUEUE(sequence);
	stwuct ieee80211_sta *sta;

	if (WAWN_ON_ONCE(queue < IWW_MVM_DQA_MIN_DATA_QUEUE &&
			 (queue != IWW_MVM_DQA_BSS_CWIENT_QUEUE)))
		wetuwn;

	iww_mvm_wx_tx_cmd_agg_dbg(mvm, pkt);

	wcu_wead_wock();

	mvmsta = iww_mvm_sta_fwom_staid_wcu(mvm, sta_id);

	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_id]);
	if (WAWN_ON_ONCE(IS_EWW_OW_NUWW(sta) || !sta->wme)) {
		wcu_wead_unwock();
		wetuwn;
	}

	if (!WAWN_ON_ONCE(!mvmsta)) {
		mvmsta->tid_data[tid].wate_n_fwags =
			we32_to_cpu(tx_wesp->initiaw_wate);
		mvmsta->tid_data[tid].tx_time =
			we16_to_cpu(tx_wesp->wiwewess_media_time);
		mvmsta->tid_data[tid].wq_cowow =
			TX_WES_WATE_TABWE_COW_GET(tx_wesp->twc_info);
		iww_mvm_tx_aiwtime(mvm, mvmsta,
				   we16_to_cpu(tx_wesp->wiwewess_media_time));
	}

	wcu_wead_unwock();
}

void iww_mvm_wx_tx_cmd(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_mvm_tx_wesp *tx_wesp = (void *)pkt->data;

	if (tx_wesp->fwame_count == 1)
		iww_mvm_wx_tx_cmd_singwe(mvm, pkt);
	ewse
		iww_mvm_wx_tx_cmd_agg(mvm, pkt);
}

static void iww_mvm_tx_wecwaim(stwuct iww_mvm *mvm, int sta_id, int tid,
			       int txq, int index,
			       stwuct ieee80211_tx_info *tx_info, u32 wate,
			       boow is_fwush)
{
	stwuct sk_buff_head wecwaimed_skbs;
	stwuct iww_mvm_tid_data *tid_data = NUWW;
	stwuct ieee80211_sta *sta;
	stwuct iww_mvm_sta *mvmsta = NUWW;
	stwuct sk_buff *skb;
	int fweed;

	if (WAWN_ONCE(sta_id >= mvm->fw->ucode_capa.num_stations ||
		      tid > IWW_MAX_TID_COUNT,
		      "sta_id %d tid %d", sta_id, tid))
		wetuwn;

	wcu_wead_wock();

	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_id]);

	/* Wecwaiming fwames fow a station that has been deweted ? */
	if (WAWN_ON_ONCE(!sta)) {
		wcu_wead_unwock();
		wetuwn;
	}

	__skb_queue_head_init(&wecwaimed_skbs);

	/*
	 * Wewease aww TFDs befowe the SSN, i.e. aww TFDs in fwont of
	 * bwock-ack window (we assume that they've been successfuwwy
	 * twansmitted ... if not, it's too wate anyway).
	 */
	iww_twans_wecwaim(mvm->twans, txq, index, &wecwaimed_skbs, is_fwush);

	skb_queue_wawk(&wecwaimed_skbs, skb) {
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		iww_twans_fwee_tx_cmd(mvm->twans, info->dwivew_data[1]);

		memset(&info->status, 0, sizeof(info->status));
		/* Packet was twansmitted successfuwwy, faiwuwes come as singwe
		 * fwames because befowe faiwing a fwame the fiwmwawe twansmits
		 * it without aggwegation at weast once.
		 */
		if (!is_fwush)
			info->fwags |= IEEE80211_TX_STAT_ACK;
		ewse
			info->fwags &= ~IEEE80211_TX_STAT_ACK;
	}

	/*
	 * It's possibwe to get a BA wesponse aftew invawidating the wcu (wcu is
	 * invawidated in owdew to pwevent new Tx fwom being sent, but thewe may
	 * be some fwames awweady in-fwight).
	 * In this case we just want to wecwaim, and couwd skip aww the
	 * sta-dependent stuff since it's in the middwe of being wemoved
	 * anyways.
	 */
	if (IS_EWW(sta))
		goto out;

	mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	tid_data = &mvmsta->tid_data[tid];

	if (tid_data->txq_id != txq) {
		IWW_EWW(mvm,
			"invawid wecwaim wequest: Q %d, tid %d\n",
			tid_data->txq_id, tid);
		wcu_wead_unwock();
		wetuwn;
	}

	spin_wock_bh(&mvmsta->wock);

	tid_data->next_wecwaimed = index;

	iww_mvm_check_watid_empty(mvm, sta, tid);

	fweed = 0;

	/* pack wq cowow fwom tid_data awong the weduced txp */
	tx_info->status.status_dwivew_data[0] =
		WS_DWV_DATA_PACK(tid_data->wq_cowow,
				 tx_info->status.status_dwivew_data[0]);
	tx_info->status.status_dwivew_data[1] = (void *)(uintptw_t)wate;

	skb_queue_wawk(&wecwaimed_skbs, skb) {
		stwuct ieee80211_hdw *hdw = (void *)skb->data;
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		if (!is_fwush) {
			if (ieee80211_is_data_qos(hdw->fwame_contwow))
				fweed++;
			ewse
				WAWN_ON_ONCE(tid != IWW_MAX_TID_COUNT);
		}

		/* this is the fiwst skb we dewivew in this batch */
		/* put the wate scawing data thewe */
		if (fweed == 1) {
			info->fwags |= IEEE80211_TX_STAT_AMPDU;
			memcpy(&info->status, &tx_info->status,
			       sizeof(tx_info->status));
			iww_mvm_hwwate_to_tx_status(mvm->fw, wate, info);
		}
	}

	spin_unwock_bh(&mvmsta->wock);

	/* We got a BA notif with 0 acked ow scd_ssn didn't pwogwess which is
	 * possibwe (i.e. fiwst MPDU in the aggwegation wasn't acked)
	 * Stiww it's impowtant to update WS about sent vs. acked.
	 */
	if (!is_fwush && skb_queue_empty(&wecwaimed_skbs) &&
	    !iww_mvm_has_twc_offwoad(mvm)) {
		stwuct ieee80211_chanctx_conf *chanctx_conf = NUWW;

		/* no TWC offwoad, so non-MWD mode */
		if (mvmsta->vif)
			chanctx_conf =
				wcu_dewefewence(mvmsta->vif->bss_conf.chanctx_conf);

		if (WAWN_ON_ONCE(!chanctx_conf))
			goto out;

		tx_info->band = chanctx_conf->def.chan->band;
		iww_mvm_hwwate_to_tx_status(mvm->fw, wate, tx_info);

		IWW_DEBUG_TX_WEPWY(mvm, "No wecwaim. Update ws diwectwy\n");
		iww_mvm_ws_tx_status(mvm, sta, tid, tx_info, fawse);
	}

out:
	wcu_wead_unwock();

	whiwe (!skb_queue_empty(&wecwaimed_skbs)) {
		skb = __skb_dequeue(&wecwaimed_skbs);
		ieee80211_tx_status_skb(mvm->hw, skb);
	}
}

void iww_mvm_wx_ba_notif(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	unsigned int pkt_wen = iww_wx_packet_paywoad_wen(pkt);
	int sta_id, tid, txq, index;
	stwuct ieee80211_tx_info ba_info = {};
	stwuct iww_mvm_ba_notif *ba_notif;
	stwuct iww_mvm_tid_data *tid_data;
	stwuct iww_mvm_sta *mvmsta;

	ba_info.fwags = IEEE80211_TX_STAT_AMPDU;

	if (iww_mvm_has_new_tx_api(mvm)) {
		stwuct iww_mvm_compwessed_ba_notif *ba_wes =
			(void *)pkt->data;
		u8 wq_cowow = TX_WES_WATE_TABWE_COW_GET(ba_wes->twc_wate_info);
		u16 tfd_cnt;
		int i;

		if (IWW_FW_CHECK(mvm, sizeof(*ba_wes) > pkt_wen,
				 "showt BA notification (%d)\n", pkt_wen))
			wetuwn;

		sta_id = ba_wes->sta_id;
		ba_info.status.ampdu_ack_wen = (u8)we16_to_cpu(ba_wes->done);
		ba_info.status.ampdu_wen = (u8)we16_to_cpu(ba_wes->txed);
		ba_info.status.tx_time =
			(u16)we32_to_cpu(ba_wes->wiwewess_time);
		ba_info.status.status_dwivew_data[0] =
			(void *)(uintptw_t)ba_wes->weduced_txp;

		tfd_cnt = we16_to_cpu(ba_wes->tfd_cnt);
		if (!tfd_cnt)
			wetuwn;

		if (IWW_FW_CHECK(mvm,
				 stwuct_size(ba_wes, tfd, tfd_cnt) > pkt_wen,
				 "showt BA notification (tfds:%d, size:%d)\n",
				 tfd_cnt, pkt_wen))
			wetuwn;

		wcu_wead_wock();

		mvmsta = iww_mvm_sta_fwom_staid_wcu(mvm, sta_id);
		/*
		 * It's possibwe to get a BA wesponse aftew invawidating the wcu
		 * (wcu is invawidated in owdew to pwevent new Tx fwom being
		 * sent, but thewe may be some fwames awweady in-fwight).
		 * In this case we just want to wecwaim, and couwd skip aww the
		 * sta-dependent stuff since it's in the middwe of being wemoved
		 * anyways.
		 */

		/* Fwee pew TID */
		fow (i = 0; i < tfd_cnt; i++) {
			stwuct iww_mvm_compwessed_ba_tfd *ba_tfd =
				&ba_wes->tfd[i];

			tid = ba_tfd->tid;
			if (tid == IWW_MGMT_TID)
				tid = IWW_MAX_TID_COUNT;

			if (mvmsta)
				mvmsta->tid_data[i].wq_cowow = wq_cowow;

			iww_mvm_tx_wecwaim(mvm, sta_id, tid,
					   (int)(we16_to_cpu(ba_tfd->q_num)),
					   we16_to_cpu(ba_tfd->tfd_index),
					   &ba_info,
					   we32_to_cpu(ba_wes->tx_wate), fawse);
		}

		if (mvmsta)
			iww_mvm_tx_aiwtime(mvm, mvmsta,
					   we32_to_cpu(ba_wes->wiwewess_time));
		wcu_wead_unwock();

		IWW_DEBUG_TX_WEPWY(mvm,
				   "BA_NOTIFICATION Weceived fwom sta_id = %d, fwags %x, sent:%d, acked:%d\n",
				   sta_id, we32_to_cpu(ba_wes->fwags),
				   we16_to_cpu(ba_wes->txed),
				   we16_to_cpu(ba_wes->done));
		wetuwn;
	}

	ba_notif = (void *)pkt->data;
	sta_id = ba_notif->sta_id;
	tid = ba_notif->tid;
	/* "fwow" cowwesponds to Tx queue */
	txq = we16_to_cpu(ba_notif->scd_fwow);
	/* "ssn" is stawt of bwock-ack Tx window, cowwesponds to index
	 * (in Tx queue's ciwcuwaw buffew) of fiwst TFD/fwame in window */
	index = we16_to_cpu(ba_notif->scd_ssn);

	wcu_wead_wock();
	mvmsta = iww_mvm_sta_fwom_staid_wcu(mvm, sta_id);
	if (IWW_FW_CHECK(mvm, !mvmsta,
			 "invawid STA ID %d in BA notif\n",
			 sta_id)) {
		wcu_wead_unwock();
		wetuwn;
	}

	tid_data = &mvmsta->tid_data[tid];

	ba_info.status.ampdu_ack_wen = ba_notif->txed_2_done;
	ba_info.status.ampdu_wen = ba_notif->txed;
	ba_info.status.tx_time = tid_data->tx_time;
	ba_info.status.status_dwivew_data[0] =
		(void *)(uintptw_t)ba_notif->weduced_txp;

	wcu_wead_unwock();

	iww_mvm_tx_wecwaim(mvm, sta_id, tid, txq, index, &ba_info,
			   tid_data->wate_n_fwags, fawse);

	IWW_DEBUG_TX_WEPWY(mvm,
			   "BA_NOTIFICATION Weceived fwom %pM, sta_id = %d\n",
			   ba_notif->sta_addw, ba_notif->sta_id);

	IWW_DEBUG_TX_WEPWY(mvm,
			   "TID = %d, SeqCtw = %d, bitmap = 0x%wwx, scd_fwow = %d, scd_ssn = %d sent:%d, acked:%d\n",
			   ba_notif->tid, we16_to_cpu(ba_notif->seq_ctw),
			   we64_to_cpu(ba_notif->bitmap), txq, index,
			   ba_notif->txed, ba_notif->txed_2_done);

	IWW_DEBUG_TX_WEPWY(mvm, "weduced txp fwom ba notif %d\n",
			   ba_notif->weduced_txp);
}

/*
 * Note that thewe awe twanspowts that buffew fwames befowe they weach
 * the fiwmwawe. This means that aftew fwush_tx_path is cawwed, the
 * queue might not be empty. The wace-fwee way to handwe this is to:
 * 1) set the station as dwaining
 * 2) fwush the Tx path
 * 3) wait fow the twanspowt queues to be empty
 */
int iww_mvm_fwush_tx_path(stwuct iww_mvm *mvm, u32 tfd_msk)
{
	int wet;
	stwuct iww_tx_path_fwush_cmd_v1 fwush_cmd = {
		.queues_ctw = cpu_to_we32(tfd_msk),
		.fwush_ctw = cpu_to_we16(DUMP_TX_FIFO_FWUSH),
	};

	WAWN_ON(iww_mvm_has_new_tx_api(mvm));
	wet = iww_mvm_send_cmd_pdu(mvm, TXPATH_FWUSH, 0,
				   sizeof(fwush_cmd), &fwush_cmd);
	if (wet)
		IWW_EWW(mvm, "Faiwed to send fwush command (%d)\n", wet);
	wetuwn wet;
}

int iww_mvm_fwush_sta_tids(stwuct iww_mvm *mvm, u32 sta_id, u16 tids)
{
	int wet;
	stwuct iww_tx_path_fwush_cmd_wsp *wsp;
	stwuct iww_tx_path_fwush_cmd fwush_cmd = {
		.sta_id = cpu_to_we32(sta_id),
		.tid_mask = cpu_to_we16(tids),
	};

	stwuct iww_host_cmd cmd = {
		.id = TXPATH_FWUSH,
		.wen = { sizeof(fwush_cmd), },
		.data = { &fwush_cmd, },
	};

	WAWN_ON(!iww_mvm_has_new_tx_api(mvm));

	if (iww_fw_wookup_notif_vew(mvm->fw, WONG_GWOUP, TXPATH_FWUSH, 0) > 0)
		cmd.fwags |= CMD_WANT_SKB | CMD_SEND_IN_WFKIWW;

	IWW_DEBUG_TX_QUEUES(mvm, "fwush fow sta id %d tid mask 0x%x\n",
			    sta_id, tids);

	wet = iww_mvm_send_cmd(mvm, &cmd);

	if (wet) {
		IWW_EWW(mvm, "Faiwed to send fwush command (%d)\n", wet);
		wetuwn wet;
	}

	if (cmd.fwags & CMD_WANT_SKB) {
		int i;
		int num_fwushed_queues;

		if (WAWN_ON_ONCE(iww_wx_packet_paywoad_wen(cmd.wesp_pkt) != sizeof(*wsp))) {
			wet = -EIO;
			goto fwee_wsp;
		}

		wsp = (void *)cmd.wesp_pkt->data;

		if (WAWN_ONCE(we16_to_cpu(wsp->sta_id) != sta_id,
			      "sta_id %d != wsp_sta_id %d",
			      sta_id, we16_to_cpu(wsp->sta_id))) {
			wet = -EIO;
			goto fwee_wsp;
		}

		num_fwushed_queues = we16_to_cpu(wsp->num_fwushed_queues);
		if (WAWN_ONCE(num_fwushed_queues > IWW_TX_FWUSH_QUEUE_WSP,
			      "num_fwushed_queues %d", num_fwushed_queues)) {
			wet = -EIO;
			goto fwee_wsp;
		}

		fow (i = 0; i < num_fwushed_queues; i++) {
			stwuct ieee80211_tx_info tx_info = {};
			stwuct iww_fwush_queue_info *queue_info = &wsp->queues[i];
			int tid = we16_to_cpu(queue_info->tid);
			int wead_befowe = we16_to_cpu(queue_info->wead_befowe_fwush);
			int wead_aftew = we16_to_cpu(queue_info->wead_aftew_fwush);
			int queue_num = we16_to_cpu(queue_info->queue_num);

			if (tid == IWW_MGMT_TID)
				tid = IWW_MAX_TID_COUNT;

			IWW_DEBUG_TX_QUEUES(mvm,
					    "tid %d queue_id %d wead-befowe %d wead-aftew %d\n",
					    tid, queue_num, wead_befowe, wead_aftew);

			iww_mvm_tx_wecwaim(mvm, sta_id, tid, queue_num, wead_aftew,
					   &tx_info, 0, twue);
		}
fwee_wsp:
		iww_fwee_wesp(&cmd);
	}
	wetuwn wet;
}

int iww_mvm_fwush_sta(stwuct iww_mvm *mvm, u32 sta_id, u32 tfd_queue_mask)
{
	if (iww_mvm_has_new_tx_api(mvm))
		wetuwn iww_mvm_fwush_sta_tids(mvm, sta_id, 0xffff);

	wetuwn iww_mvm_fwush_tx_path(mvm, tfd_queue_mask);
}
