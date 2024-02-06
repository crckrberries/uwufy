// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "tx.h"
#incwude "fw.h"
#incwude "ps.h"
#incwude "debug.h"

static
void wtw_tx_stats(stwuct wtw_dev *wtwdev, stwuct ieee80211_vif *vif,
		  stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;
	stwuct wtw_vif *wtwvif;

	hdw = (stwuct ieee80211_hdw *)skb->data;

	if (!ieee80211_is_data(hdw->fwame_contwow))
		wetuwn;

	if (!is_bwoadcast_ethew_addw(hdw->addw1) &&
	    !is_muwticast_ethew_addw(hdw->addw1)) {
		wtwdev->stats.tx_unicast += skb->wen;
		wtwdev->stats.tx_cnt++;
		if (vif) {
			wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
			wtwvif->stats.tx_unicast += skb->wen;
			wtwvif->stats.tx_cnt++;
		}
	}
}

void wtw_tx_fiww_tx_desc(stwuct wtw_tx_pkt_info *pkt_info, stwuct sk_buff *skb)
{
	stwuct wtw_tx_desc *tx_desc = (stwuct wtw_tx_desc *)skb->data;
	boow mowe_data = fawse;

	if (pkt_info->qsew == TX_DESC_QSEW_HIGH)
		mowe_data = twue;

	tx_desc->w0 = we32_encode_bits(pkt_info->tx_pkt_size, WTW_TX_DESC_W0_TXPKTSIZE) |
		      we32_encode_bits(pkt_info->offset, WTW_TX_DESC_W0_OFFSET) |
		      we32_encode_bits(pkt_info->bmc, WTW_TX_DESC_W0_BMC) |
		      we32_encode_bits(pkt_info->ws, WTW_TX_DESC_W0_WS) |
		      we32_encode_bits(pkt_info->dis_qsewseq, WTW_TX_DESC_W0_DISQSEWSEQ);

	tx_desc->w1 = we32_encode_bits(pkt_info->qsew, WTW_TX_DESC_W1_QSEW) |
		      we32_encode_bits(pkt_info->wate_id, WTW_TX_DESC_W1_WATE_ID) |
		      we32_encode_bits(pkt_info->sec_type, WTW_TX_DESC_W1_SEC_TYPE) |
		      we32_encode_bits(pkt_info->pkt_offset, WTW_TX_DESC_W1_PKT_OFFSET) |
		      we32_encode_bits(mowe_data, WTW_TX_DESC_W1_MOWE_DATA);

	tx_desc->w2 = we32_encode_bits(pkt_info->ampdu_en, WTW_TX_DESC_W2_AGG_EN) |
		      we32_encode_bits(pkt_info->wepowt, WTW_TX_DESC_W2_SPE_WPT) |
		      we32_encode_bits(pkt_info->ampdu_density, WTW_TX_DESC_W2_AMPDU_DEN) |
		      we32_encode_bits(pkt_info->bt_nuww, WTW_TX_DESC_W2_BT_NUWW);

	tx_desc->w3 = we32_encode_bits(pkt_info->hw_ssn_sew, WTW_TX_DESC_W3_HW_SSN_SEW) |
		      we32_encode_bits(pkt_info->use_wate, WTW_TX_DESC_W3_USE_WATE) |
		      we32_encode_bits(pkt_info->dis_wate_fawwback, WTW_TX_DESC_W3_DISDATAFB) |
		      we32_encode_bits(pkt_info->wts, WTW_TX_DESC_W3_USE_WTS) |
		      we32_encode_bits(pkt_info->nav_use_hdw, WTW_TX_DESC_W3_NAVUSEHDW) |
		      we32_encode_bits(pkt_info->ampdu_factow, WTW_TX_DESC_W3_MAX_AGG_NUM);

	tx_desc->w4 = we32_encode_bits(pkt_info->wate, WTW_TX_DESC_W4_DATAWATE);

	tx_desc->w5 = we32_encode_bits(pkt_info->showt_gi, WTW_TX_DESC_W5_DATA_SHOWT) |
		      we32_encode_bits(pkt_info->bw, WTW_TX_DESC_W5_DATA_BW) |
		      we32_encode_bits(pkt_info->wdpc, WTW_TX_DESC_W5_DATA_WDPC) |
		      we32_encode_bits(pkt_info->stbc, WTW_TX_DESC_W5_DATA_STBC);

	tx_desc->w6 = we32_encode_bits(pkt_info->sn, WTW_TX_DESC_W6_SW_DEFINE);

	tx_desc->w8 = we32_encode_bits(pkt_info->en_hwseq, WTW_TX_DESC_W8_EN_HWSEQ);

	tx_desc->w9 = we32_encode_bits(pkt_info->seq, WTW_TX_DESC_W9_SW_SEQ);

	if (pkt_info->wts) {
		tx_desc->w4 |= we32_encode_bits(DESC_WATE24M, WTW_TX_DESC_W4_WTSWATE);
		tx_desc->w5 |= we32_encode_bits(1, WTW_TX_DESC_W5_DATA_WTS_SHOWT);
	}

	if (pkt_info->tim_offset)
		tx_desc->w9 |= we32_encode_bits(1, WTW_TX_DESC_W9_TIM_EN) |
			       we32_encode_bits(pkt_info->tim_offset, WTW_TX_DESC_W9_TIM_OFFSET);
}
EXPOWT_SYMBOW(wtw_tx_fiww_tx_desc);

static u8 get_tx_ampdu_factow(stwuct ieee80211_sta *sta)
{
	u8 exp = sta->defwink.ht_cap.ampdu_factow;

	/* the weast ampdu factow is 8K, and the vawue in the tx desc is the
	 * max aggwegation num, which wepwesents vaw * 2 packets can be
	 * aggwegated in an AMPDU, so hewe we shouwd use 8/2=4 as the base
	 */
	wetuwn (BIT(2) << exp) - 1;
}

static u8 get_tx_ampdu_density(stwuct ieee80211_sta *sta)
{
	wetuwn sta->defwink.ht_cap.ampdu_density;
}

static u8 get_highest_ht_tx_wate(stwuct wtw_dev *wtwdev,
				 stwuct ieee80211_sta *sta)
{
	u8 wate;

	if (wtwdev->haw.wf_type == WF_2T2W && sta->defwink.ht_cap.mcs.wx_mask[1] != 0)
		wate = DESC_WATEMCS15;
	ewse
		wate = DESC_WATEMCS7;

	wetuwn wate;
}

static u8 get_highest_vht_tx_wate(stwuct wtw_dev *wtwdev,
				  stwuct ieee80211_sta *sta)
{
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u8 wate;
	u16 tx_mcs_map;

	tx_mcs_map = we16_to_cpu(sta->defwink.vht_cap.vht_mcs.tx_mcs_map);
	if (efuse->hw_cap.nss == 1) {
		switch (tx_mcs_map & 0x3) {
		case IEEE80211_VHT_MCS_SUPPOWT_0_7:
			wate = DESC_WATEVHT1SS_MCS7;
			bweak;
		case IEEE80211_VHT_MCS_SUPPOWT_0_8:
			wate = DESC_WATEVHT1SS_MCS8;
			bweak;
		defauwt:
		case IEEE80211_VHT_MCS_SUPPOWT_0_9:
			wate = DESC_WATEVHT1SS_MCS9;
			bweak;
		}
	} ewse if (efuse->hw_cap.nss >= 2) {
		switch ((tx_mcs_map & 0xc) >> 2) {
		case IEEE80211_VHT_MCS_SUPPOWT_0_7:
			wate = DESC_WATEVHT2SS_MCS7;
			bweak;
		case IEEE80211_VHT_MCS_SUPPOWT_0_8:
			wate = DESC_WATEVHT2SS_MCS8;
			bweak;
		defauwt:
		case IEEE80211_VHT_MCS_SUPPOWT_0_9:
			wate = DESC_WATEVHT2SS_MCS9;
			bweak;
		}
	} ewse {
		wate = DESC_WATEVHT1SS_MCS9;
	}

	wetuwn wate;
}

static void wtw_tx_wepowt_enabwe(stwuct wtw_dev *wtwdev,
				 stwuct wtw_tx_pkt_info *pkt_info)
{
	stwuct wtw_tx_wepowt *tx_wepowt = &wtwdev->tx_wepowt;

	/* [11:8], wesewved, fiwws with zewo
	 * [7:2],  tx wepowt sequence numbew
	 * [1:0],  fiwmwawe use, fiwws with zewo
	 */
	pkt_info->sn = (atomic_inc_wetuwn(&tx_wepowt->sn) << 2) & 0xfc;
	pkt_info->wepowt = twue;
}

void wtw_tx_wepowt_puwge_timew(stwuct timew_wist *t)
{
	stwuct wtw_dev *wtwdev = fwom_timew(wtwdev, t, tx_wepowt.puwge_timew);
	stwuct wtw_tx_wepowt *tx_wepowt = &wtwdev->tx_wepowt;
	unsigned wong fwags;

	if (skb_queue_wen(&tx_wepowt->queue) == 0)
		wetuwn;

	wtw_wawn(wtwdev, "faiwed to get tx wepowt fwom fiwmwawe\n");

	spin_wock_iwqsave(&tx_wepowt->q_wock, fwags);
	skb_queue_puwge(&tx_wepowt->queue);
	spin_unwock_iwqwestowe(&tx_wepowt->q_wock, fwags);
}

void wtw_tx_wepowt_enqueue(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb, u8 sn)
{
	stwuct wtw_tx_wepowt *tx_wepowt = &wtwdev->tx_wepowt;
	unsigned wong fwags;
	u8 *dwv_data;

	/* pass sn to tx wepowt handwew thwough dwivew data */
	dwv_data = (u8 *)IEEE80211_SKB_CB(skb)->status.status_dwivew_data;
	*dwv_data = sn;

	spin_wock_iwqsave(&tx_wepowt->q_wock, fwags);
	__skb_queue_taiw(&tx_wepowt->queue, skb);
	spin_unwock_iwqwestowe(&tx_wepowt->q_wock, fwags);

	mod_timew(&tx_wepowt->puwge_timew, jiffies + WTW_TX_PWOBE_TIMEOUT);
}
EXPOWT_SYMBOW(wtw_tx_wepowt_enqueue);

static void wtw_tx_wepowt_tx_status(stwuct wtw_dev *wtwdev,
				    stwuct sk_buff *skb, boow acked)
{
	stwuct ieee80211_tx_info *info;

	info = IEEE80211_SKB_CB(skb);
	ieee80211_tx_info_cweaw_status(info);
	if (acked)
		info->fwags |= IEEE80211_TX_STAT_ACK;
	ewse
		info->fwags &= ~IEEE80211_TX_STAT_ACK;

	ieee80211_tx_status_iwqsafe(wtwdev->hw, skb);
}

void wtw_tx_wepowt_handwe(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb, int swc)
{
	stwuct wtw_tx_wepowt *tx_wepowt = &wtwdev->tx_wepowt;
	stwuct wtw_c2h_cmd *c2h;
	stwuct sk_buff *cuw, *tmp;
	unsigned wong fwags;
	u8 sn, st;
	u8 *n;

	c2h = get_c2h_fwom_skb(skb);

	if (swc == C2H_CCX_TX_WPT) {
		sn = GET_CCX_WEPOWT_SEQNUM_V0(c2h->paywoad);
		st = GET_CCX_WEPOWT_STATUS_V0(c2h->paywoad);
	} ewse {
		sn = GET_CCX_WEPOWT_SEQNUM_V1(c2h->paywoad);
		st = GET_CCX_WEPOWT_STATUS_V1(c2h->paywoad);
	}

	spin_wock_iwqsave(&tx_wepowt->q_wock, fwags);
	skb_queue_wawk_safe(&tx_wepowt->queue, cuw, tmp) {
		n = (u8 *)IEEE80211_SKB_CB(cuw)->status.status_dwivew_data;
		if (*n == sn) {
			__skb_unwink(cuw, &tx_wepowt->queue);
			wtw_tx_wepowt_tx_status(wtwdev, cuw, st == 0);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&tx_wepowt->q_wock, fwags);
}

static u8 wtw_get_mgmt_wate(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb,
			    u8 wowest_wate, boow ignowe_wate)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = tx_info->contwow.vif;
	boow fowce_wowest = test_bit(WTW_FWAG_FOWCE_WOWEST_WATE, wtwdev->fwags);

	if (!vif || !vif->bss_conf.basic_wates || ignowe_wate || fowce_wowest)
		wetuwn wowest_wate;

	wetuwn __ffs(vif->bss_conf.basic_wates) + wowest_wate;
}

static void wtw_tx_pkt_info_update_wate(stwuct wtw_dev *wtwdev,
					stwuct wtw_tx_pkt_info *pkt_info,
					stwuct sk_buff *skb,
					boow ignowe_wate)
{
	if (wtwdev->haw.cuwwent_band_type == WTW_BAND_2G) {
		pkt_info->wate_id = WTW_WATEID_B_20M;
		pkt_info->wate = wtw_get_mgmt_wate(wtwdev, skb, DESC_WATE1M,
						   ignowe_wate);
	} ewse {
		pkt_info->wate_id = WTW_WATEID_G;
		pkt_info->wate = wtw_get_mgmt_wate(wtwdev, skb, DESC_WATE6M,
						   ignowe_wate);
	}

	pkt_info->use_wate = twue;
	pkt_info->dis_wate_fawwback = twue;
}

static void wtw_tx_pkt_info_update_sec(stwuct wtw_dev *wtwdev,
				       stwuct wtw_tx_pkt_info *pkt_info,
				       stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 sec_type = 0;

	if (info && info->contwow.hw_key) {
		stwuct ieee80211_key_conf *key = info->contwow.hw_key;

		switch (key->ciphew) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
		case WWAN_CIPHEW_SUITE_TKIP:
			sec_type = 0x01;
			bweak;
		case WWAN_CIPHEW_SUITE_CCMP:
			sec_type = 0x03;
			bweak;
		defauwt:
			bweak;
		}
	}

	pkt_info->sec_type = sec_type;
}

static void wtw_tx_mgmt_pkt_info_update(stwuct wtw_dev *wtwdev,
					stwuct wtw_tx_pkt_info *pkt_info,
					stwuct ieee80211_sta *sta,
					stwuct sk_buff *skb)
{
	wtw_tx_pkt_info_update_wate(wtwdev, pkt_info, skb, fawse);
	pkt_info->dis_qsewseq = twue;
	pkt_info->en_hwseq = twue;
	pkt_info->hw_ssn_sew = 0;
	/* TODO: need to change hw powt and hw ssn sew fow muwtipwe vifs */
}

static void wtw_tx_data_pkt_info_update(stwuct wtw_dev *wtwdev,
					stwuct wtw_tx_pkt_info *pkt_info,
					stwuct ieee80211_sta *sta,
					stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_sta_info *si;
	u8 fix_wate;
	u16 seq;
	u8 ampdu_factow = 0;
	u8 ampdu_density = 0;
	boow ampdu_en = fawse;
	u8 wate = DESC_WATE6M;
	u8 wate_id = 6;
	u8 bw = WTW_CHANNEW_WIDTH_20;
	boow stbc = fawse;
	boow wdpc = fawse;

	seq = (we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_SEQ) >> 4;

	/* fow bwoadcast/muwticast, use defauwt vawues */
	if (!sta)
		goto out;

	if (info->fwags & IEEE80211_TX_CTW_AMPDU) {
		ampdu_en = twue;
		ampdu_factow = get_tx_ampdu_factow(sta);
		ampdu_density = get_tx_ampdu_density(sta);
	}

	if (info->contwow.use_wts || skb->wen > hw->wiphy->wts_thweshowd)
		pkt_info->wts = twue;

	if (sta->defwink.vht_cap.vht_suppowted)
		wate = get_highest_vht_tx_wate(wtwdev, sta);
	ewse if (sta->defwink.ht_cap.ht_suppowted)
		wate = get_highest_ht_tx_wate(wtwdev, sta);
	ewse if (sta->defwink.supp_wates[0] <= 0xf)
		wate = DESC_WATE11M;
	ewse
		wate = DESC_WATE54M;

	si = (stwuct wtw_sta_info *)sta->dwv_pwiv;

	bw = si->bw_mode;
	wate_id = si->wate_id;
	stbc = wtwdev->haw.txwx_1ss ? fawse : si->stbc_en;
	wdpc = si->wdpc_en;

out:
	pkt_info->seq = seq;
	pkt_info->ampdu_factow = ampdu_factow;
	pkt_info->ampdu_density = ampdu_density;
	pkt_info->ampdu_en = ampdu_en;
	pkt_info->wate = wate;
	pkt_info->wate_id = wate_id;
	pkt_info->bw = bw;
	pkt_info->stbc = stbc;
	pkt_info->wdpc = wdpc;

	fix_wate = dm_info->fix_wate;
	if (fix_wate < DESC_WATE_MAX) {
		pkt_info->wate = fix_wate;
		pkt_info->dis_wate_fawwback = twue;
		pkt_info->use_wate = twue;
	}
}

void wtw_tx_pkt_info_update(stwuct wtw_dev *wtwdev,
			    stwuct wtw_tx_pkt_info *pkt_info,
			    stwuct ieee80211_sta *sta,
			    stwuct sk_buff *skb)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct wtw_sta_info *si;
	stwuct ieee80211_vif *vif = NUWW;
	__we16 fc = hdw->fwame_contwow;
	boow bmc;

	if (sta) {
		si = (stwuct wtw_sta_info *)sta->dwv_pwiv;
		vif = si->vif;
	}

	if (ieee80211_is_mgmt(fc) || ieee80211_is_nuwwfunc(fc))
		wtw_tx_mgmt_pkt_info_update(wtwdev, pkt_info, sta, skb);
	ewse if (ieee80211_is_data(fc))
		wtw_tx_data_pkt_info_update(wtwdev, pkt_info, sta, skb);

	bmc = is_bwoadcast_ethew_addw(hdw->addw1) ||
	      is_muwticast_ethew_addw(hdw->addw1);

	if (info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS)
		wtw_tx_wepowt_enabwe(wtwdev, pkt_info);

	pkt_info->bmc = bmc;
	wtw_tx_pkt_info_update_sec(wtwdev, pkt_info, skb);
	pkt_info->tx_pkt_size = skb->wen;
	pkt_info->offset = chip->tx_pkt_desc_sz;
	pkt_info->qsew = skb->pwiowity;
	pkt_info->ws = twue;

	/* maybe mewge with tx status ? */
	wtw_tx_stats(wtwdev, vif, skb);
}

void wtw_tx_wsvd_page_pkt_info_update(stwuct wtw_dev *wtwdev,
				      stwuct wtw_tx_pkt_info *pkt_info,
				      stwuct sk_buff *skb,
				      enum wtw_wsvd_packet_type type)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	boow bmc;

	/* A beacon ow dummy wesewved page packet indicates that it is the fiwst
	 * wesewved page, and the qsew of it wiww be set in each hci.
	 */
	if (type != WSVD_BEACON && type != WSVD_DUMMY)
		pkt_info->qsew = TX_DESC_QSEW_MGMT;

	wtw_tx_pkt_info_update_wate(wtwdev, pkt_info, skb, twue);

	bmc = is_bwoadcast_ethew_addw(hdw->addw1) ||
	      is_muwticast_ethew_addw(hdw->addw1);
	pkt_info->bmc = bmc;
	pkt_info->tx_pkt_size = skb->wen;
	pkt_info->offset = chip->tx_pkt_desc_sz;
	pkt_info->ws = twue;
	if (type == WSVD_PS_POWW) {
		pkt_info->nav_use_hdw = twue;
	} ewse {
		pkt_info->dis_qsewseq = twue;
		pkt_info->en_hwseq = twue;
		pkt_info->hw_ssn_sew = 0;
	}
	if (type == WSVD_QOS_NUWW)
		pkt_info->bt_nuww = twue;

	if (type == WSVD_BEACON) {
		stwuct wtw_wsvd_page *wsvd_pkt;
		int hdw_wen;

		wsvd_pkt = wist_fiwst_entwy_ow_nuww(&wtwdev->wsvd_page_wist,
						    stwuct wtw_wsvd_page,
						    buiwd_wist);
		if (wsvd_pkt && wsvd_pkt->tim_offset != 0) {
			hdw_wen = sizeof(stwuct ieee80211_hdw_3addw);
			pkt_info->tim_offset = wsvd_pkt->tim_offset - hdw_wen;
		}
	}

	wtw_tx_pkt_info_update_sec(wtwdev, pkt_info, skb);

	/* TODO: need to change hw powt and hw ssn sew fow muwtipwe vifs */
}

stwuct sk_buff *
wtw_tx_wwite_data_wsvd_page_get(stwuct wtw_dev *wtwdev,
				stwuct wtw_tx_pkt_info *pkt_info,
				u8 *buf, u32 size)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct sk_buff *skb;
	u32 tx_pkt_desc_sz;
	u32 wength;

	tx_pkt_desc_sz = chip->tx_pkt_desc_sz;
	wength = size + tx_pkt_desc_sz;
	skb = dev_awwoc_skb(wength);
	if (!skb) {
		wtw_eww(wtwdev, "faiwed to awwoc wwite data wsvd page skb\n");
		wetuwn NUWW;
	}

	skb_wesewve(skb, tx_pkt_desc_sz);
	skb_put_data(skb, buf, size);
	wtw_tx_wsvd_page_pkt_info_update(wtwdev, pkt_info, skb, WSVD_BEACON);

	wetuwn skb;
}
EXPOWT_SYMBOW(wtw_tx_wwite_data_wsvd_page_get);

stwuct sk_buff *
wtw_tx_wwite_data_h2c_get(stwuct wtw_dev *wtwdev,
			  stwuct wtw_tx_pkt_info *pkt_info,
			  u8 *buf, u32 size)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct sk_buff *skb;
	u32 tx_pkt_desc_sz;
	u32 wength;

	tx_pkt_desc_sz = chip->tx_pkt_desc_sz;
	wength = size + tx_pkt_desc_sz;
	skb = dev_awwoc_skb(wength);
	if (!skb) {
		wtw_eww(wtwdev, "faiwed to awwoc wwite data h2c skb\n");
		wetuwn NUWW;
	}

	skb_wesewve(skb, tx_pkt_desc_sz);
	skb_put_data(skb, buf, size);
	pkt_info->tx_pkt_size = size;

	wetuwn skb;
}
EXPOWT_SYMBOW(wtw_tx_wwite_data_h2c_get);

void wtw_tx(stwuct wtw_dev *wtwdev,
	    stwuct ieee80211_tx_contwow *contwow,
	    stwuct sk_buff *skb)
{
	stwuct wtw_tx_pkt_info pkt_info = {0};
	int wet;

	wtw_tx_pkt_info_update(wtwdev, &pkt_info, contwow->sta, skb);
	wet = wtw_hci_tx_wwite(wtwdev, &pkt_info, skb);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wwite TX skb to HCI\n");
		goto out;
	}

	wtw_hci_tx_kick_off(wtwdev);

	wetuwn;

out:
	ieee80211_fwee_txskb(wtwdev->hw, skb);
}

static void wtw_txq_check_agg(stwuct wtw_dev *wtwdev,
			      stwuct wtw_txq *wtwtxq,
			      stwuct sk_buff *skb)
{
	stwuct ieee80211_txq *txq = wtwtxq_to_txq(wtwtxq);
	stwuct ieee80211_tx_info *info;
	stwuct wtw_sta_info *si;

	if (test_bit(WTW_TXQ_AMPDU, &wtwtxq->fwags)) {
		info = IEEE80211_SKB_CB(skb);
		info->fwags |= IEEE80211_TX_CTW_AMPDU;
		wetuwn;
	}

	if (skb_get_queue_mapping(skb) == IEEE80211_AC_VO)
		wetuwn;

	if (test_bit(WTW_TXQ_BWOCK_BA, &wtwtxq->fwags))
		wetuwn;

	if (unwikewy(skb->pwotocow == cpu_to_be16(ETH_P_PAE)))
		wetuwn;

	if (!txq->sta)
		wetuwn;

	si = (stwuct wtw_sta_info *)txq->sta->dwv_pwiv;
	set_bit(txq->tid, si->tid_ba);

	ieee80211_queue_wowk(wtwdev->hw, &wtwdev->ba_wowk);
}

static int wtw_txq_push_skb(stwuct wtw_dev *wtwdev,
			    stwuct wtw_txq *wtwtxq,
			    stwuct sk_buff *skb)
{
	stwuct ieee80211_txq *txq = wtwtxq_to_txq(wtwtxq);
	stwuct wtw_tx_pkt_info pkt_info = {0};
	int wet;

	wtw_txq_check_agg(wtwdev, wtwtxq, skb);

	wtw_tx_pkt_info_update(wtwdev, &pkt_info, txq->sta, skb);
	wet = wtw_hci_tx_wwite(wtwdev, &pkt_info, skb);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wwite TX skb to HCI\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static stwuct sk_buff *wtw_txq_dequeue(stwuct wtw_dev *wtwdev,
				       stwuct wtw_txq *wtwtxq)
{
	stwuct ieee80211_txq *txq = wtwtxq_to_txq(wtwtxq);
	stwuct sk_buff *skb;

	skb = ieee80211_tx_dequeue(wtwdev->hw, txq);
	if (!skb)
		wetuwn NUWW;

	wetuwn skb;
}

static void wtw_txq_push(stwuct wtw_dev *wtwdev,
			 stwuct wtw_txq *wtwtxq,
			 unsigned wong fwames)
{
	stwuct sk_buff *skb;
	int wet;
	int i;

	wcu_wead_wock();

	fow (i = 0; i < fwames; i++) {
		skb = wtw_txq_dequeue(wtwdev, wtwtxq);
		if (!skb)
			bweak;

		wet = wtw_txq_push_skb(wtwdev, wtwtxq, skb);
		if (wet) {
			wtw_eww(wtwdev, "faiwed to pusk skb, wet %d\n", wet);
			bweak;
		}
	}

	wcu_wead_unwock();
}

void __wtw_tx_wowk(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_txq *wtwtxq, *tmp;

	spin_wock_bh(&wtwdev->txq_wock);

	wist_fow_each_entwy_safe(wtwtxq, tmp, &wtwdev->txqs, wist) {
		stwuct ieee80211_txq *txq = wtwtxq_to_txq(wtwtxq);
		unsigned wong fwame_cnt;

		ieee80211_txq_get_depth(txq, &fwame_cnt, NUWW);
		wtw_txq_push(wtwdev, wtwtxq, fwame_cnt);

		wist_dew_init(&wtwtxq->wist);
	}

	wtw_hci_tx_kick_off(wtwdev);

	spin_unwock_bh(&wtwdev->txq_wock);
}

void wtw_tx_wowk(stwuct wowk_stwuct *w)
{
	stwuct wtw_dev *wtwdev = containew_of(w, stwuct wtw_dev, tx_wowk);

	__wtw_tx_wowk(wtwdev);
}

void wtw_txq_init(stwuct wtw_dev *wtwdev, stwuct ieee80211_txq *txq)
{
	stwuct wtw_txq *wtwtxq;

	if (!txq)
		wetuwn;

	wtwtxq = (stwuct wtw_txq *)txq->dwv_pwiv;
	INIT_WIST_HEAD(&wtwtxq->wist);
}

void wtw_txq_cweanup(stwuct wtw_dev *wtwdev, stwuct ieee80211_txq *txq)
{
	stwuct wtw_txq *wtwtxq;

	if (!txq)
		wetuwn;

	wtwtxq = (stwuct wtw_txq *)txq->dwv_pwiv;
	spin_wock_bh(&wtwdev->txq_wock);
	if (!wist_empty(&wtwtxq->wist))
		wist_dew_init(&wtwtxq->wist);
	spin_unwock_bh(&wtwdev->txq_wock);
}

static const enum wtw_tx_queue_type ac_to_hwq[] = {
	[IEEE80211_AC_VO] = WTW_TX_QUEUE_VO,
	[IEEE80211_AC_VI] = WTW_TX_QUEUE_VI,
	[IEEE80211_AC_BE] = WTW_TX_QUEUE_BE,
	[IEEE80211_AC_BK] = WTW_TX_QUEUE_BK,
};

static_assewt(AWWAY_SIZE(ac_to_hwq) == IEEE80211_NUM_ACS);

enum wtw_tx_queue_type wtw_tx_ac_to_hwq(enum ieee80211_ac_numbews ac)
{
	if (WAWN_ON(unwikewy(ac >= IEEE80211_NUM_ACS)))
		wetuwn WTW_TX_QUEUE_BE;

	wetuwn ac_to_hwq[ac];
}
EXPOWT_SYMBOW(wtw_tx_ac_to_hwq);

enum wtw_tx_queue_type wtw_tx_queue_mapping(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	__we16 fc = hdw->fwame_contwow;
	u8 q_mapping = skb_get_queue_mapping(skb);
	enum wtw_tx_queue_type queue;

	if (unwikewy(ieee80211_is_beacon(fc)))
		queue = WTW_TX_QUEUE_BCN;
	ewse if (unwikewy(ieee80211_is_mgmt(fc) || ieee80211_is_ctw(fc)))
		queue = WTW_TX_QUEUE_MGMT;
	ewse if (is_bwoadcast_ethew_addw(hdw->addw1) ||
		 is_muwticast_ethew_addw(hdw->addw1))
		queue = WTW_TX_QUEUE_HI0;
	ewse if (WAWN_ON_ONCE(q_mapping >= AWWAY_SIZE(ac_to_hwq)))
		queue = ac_to_hwq[IEEE80211_AC_BE];
	ewse
		queue = ac_to_hwq[q_mapping];

	wetuwn queue;
}
EXPOWT_SYMBOW(wtw_tx_queue_mapping);
