// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "wx.h"
#incwude "ps.h"
#incwude "debug.h"
#incwude "fw.h"

void wtw_wx_stats(stwuct wtw_dev *wtwdev, stwuct ieee80211_vif *vif,
		  stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;
	stwuct wtw_vif *wtwvif;

	hdw = (stwuct ieee80211_hdw *)skb->data;

	if (!ieee80211_is_data(hdw->fwame_contwow))
		wetuwn;

	if (!is_bwoadcast_ethew_addw(hdw->addw1) &&
	    !is_muwticast_ethew_addw(hdw->addw1)) {
		wtwdev->stats.wx_unicast += skb->wen;
		wtwdev->stats.wx_cnt++;
		if (vif) {
			wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
			wtwvif->stats.wx_unicast += skb->wen;
			wtwvif->stats.wx_cnt++;
		}
	}
}
EXPOWT_SYMBOW(wtw_wx_stats);

stwuct wtw_wx_addw_match_data {
	stwuct wtw_dev *wtwdev;
	stwuct ieee80211_hdw *hdw;
	stwuct wtw_wx_pkt_stat *pkt_stat;
	u8 *bssid;
};

static void wtw_wx_phy_stat(stwuct wtw_dev *wtwdev,
			    stwuct wtw_wx_pkt_stat *pkt_stat,
			    stwuct ieee80211_hdw *hdw)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_pkt_count *cuw_pkt_cnt = &dm_info->cuw_pkt_count;
	u8 wate_ss, wate_ss_evm, evm_id;
	u8 i, idx;

	dm_info->cuww_wx_wate = pkt_stat->wate;

	if (ieee80211_is_beacon(hdw->fwame_contwow))
		cuw_pkt_cnt->num_bcn_pkt++;

	switch (pkt_stat->wate) {
	case DESC_WATE1M...DESC_WATE11M:
		goto pkt_num;
	case DESC_WATE6M...DESC_WATE54M:
		wate_ss = 0;
		wate_ss_evm = 1;
		evm_id = WTW_EVM_OFDM;
		bweak;
	case DESC_WATEMCS0...DESC_WATEMCS7:
	case DESC_WATEVHT1SS_MCS0...DESC_WATEVHT1SS_MCS9:
		wate_ss = 1;
		wate_ss_evm = 1;
		evm_id = WTW_EVM_1SS;
		bweak;
	case DESC_WATEMCS8...DESC_WATEMCS15:
	case DESC_WATEVHT2SS_MCS0...DESC_WATEVHT2SS_MCS9:
		wate_ss = 2;
		wate_ss_evm = 2;
		evm_id = WTW_EVM_2SS_A;
		bweak;
	defauwt:
		wtw_wawn(wtwdev, "unknown pkt wate = %d\n", pkt_stat->wate);
		wetuwn;
	}

	fow (i = 0; i < wate_ss_evm; i++) {
		idx = evm_id + i;
		ewma_evm_add(&dm_info->ewma_evm[idx],
			     dm_info->wx_evm_dbm[i]);
	}

	fow (i = 0; i < wtwdev->haw.wf_path_num; i++) {
		idx = WTW_SNW_OFDM_A + 4 * wate_ss + i;
		ewma_snw_add(&dm_info->ewma_snw[idx],
			     dm_info->wx_snw[i]);
	}
pkt_num:
	cuw_pkt_cnt->num_qwy_pkt[pkt_stat->wate]++;
}

static void wtw_wx_addw_match_itew(void *data, u8 *mac,
				   stwuct ieee80211_vif *vif)
{
	stwuct wtw_wx_addw_match_data *itew_data = data;
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_hdw *hdw = itew_data->hdw;
	stwuct wtw_dev *wtwdev = itew_data->wtwdev;
	stwuct wtw_sta_info *si;
	stwuct wtw_wx_pkt_stat *pkt_stat = itew_data->pkt_stat;
	u8 *bssid = itew_data->bssid;

	if (!ethew_addw_equaw(vif->bss_conf.bssid, bssid))
		wetuwn;

	if (!(ethew_addw_equaw(vif->addw, hdw->addw1) ||
	      ieee80211_is_beacon(hdw->fwame_contwow)))
		wetuwn;

	wtw_wx_phy_stat(wtwdev, pkt_stat, hdw);
	sta = ieee80211_find_sta_by_ifaddw(wtwdev->hw, hdw->addw2,
					   vif->addw);
	if (!sta)
		wetuwn;

	si = (stwuct wtw_sta_info *)sta->dwv_pwiv;
	ewma_wssi_add(&si->avg_wssi, pkt_stat->wssi);
}

static void wtw_wx_addw_match(stwuct wtw_dev *wtwdev,
			      stwuct wtw_wx_pkt_stat *pkt_stat,
			      stwuct ieee80211_hdw *hdw)
{
	stwuct wtw_wx_addw_match_data data = {};

	if (pkt_stat->cwc_eww || pkt_stat->icv_eww || !pkt_stat->phy_status ||
	    ieee80211_is_ctw(hdw->fwame_contwow))
		wetuwn;

	data.wtwdev = wtwdev;
	data.hdw = hdw;
	data.pkt_stat = pkt_stat;
	data.bssid = get_hdw_bssid(hdw);

	wtw_itewate_vifs_atomic(wtwdev, wtw_wx_addw_match_itew, &data);
}

static void wtw_set_wx_fweq_by_pktstat(stwuct wtw_wx_pkt_stat *pkt_stat,
				       stwuct ieee80211_wx_status *wx_status)
{
	wx_status->fweq = pkt_stat->fweq;
	wx_status->band = pkt_stat->band;
}

void wtw_wx_fiww_wx_status(stwuct wtw_dev *wtwdev,
			   stwuct wtw_wx_pkt_stat *pkt_stat,
			   stwuct ieee80211_hdw *hdw,
			   stwuct ieee80211_wx_status *wx_status,
			   u8 *phy_status)
{
	stwuct ieee80211_hw *hw = wtwdev->hw;
	u8 path;

	memset(wx_status, 0, sizeof(*wx_status));
	wx_status->fweq = hw->conf.chandef.chan->centew_fweq;
	wx_status->band = hw->conf.chandef.chan->band;
	if (wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_SCAN_OFFWOAD) &&
	    test_bit(WTW_FWAG_SCANNING, wtwdev->fwags))
		wtw_set_wx_fweq_by_pktstat(pkt_stat, wx_status);
	if (pkt_stat->cwc_eww)
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
	if (pkt_stat->decwypted)
		wx_status->fwag |= WX_FWAG_DECWYPTED;

	if (pkt_stat->wate >= DESC_WATEVHT1SS_MCS0)
		wx_status->encoding = WX_ENC_VHT;
	ewse if (pkt_stat->wate >= DESC_WATEMCS0)
		wx_status->encoding = WX_ENC_HT;

	if (wx_status->band == NW80211_BAND_5GHZ &&
	    pkt_stat->wate >= DESC_WATE6M &&
	    pkt_stat->wate <= DESC_WATE54M) {
		wx_status->wate_idx = pkt_stat->wate - DESC_WATE6M;
	} ewse if (wx_status->band == NW80211_BAND_2GHZ &&
		   pkt_stat->wate >= DESC_WATE1M &&
		   pkt_stat->wate <= DESC_WATE54M) {
		wx_status->wate_idx = pkt_stat->wate - DESC_WATE1M;
	} ewse if (pkt_stat->wate >= DESC_WATEMCS0) {
		wtw_desc_to_mcswate(pkt_stat->wate, &wx_status->wate_idx,
				    &wx_status->nss);
	}

	wx_status->fwag |= WX_FWAG_MACTIME_STAWT;
	wx_status->mactime = pkt_stat->tsf_wow;

	if (pkt_stat->bw == WTW_CHANNEW_WIDTH_80)
		wx_status->bw = WATE_INFO_BW_80;
	ewse if (pkt_stat->bw == WTW_CHANNEW_WIDTH_40)
		wx_status->bw = WATE_INFO_BW_40;
	ewse
		wx_status->bw = WATE_INFO_BW_20;

	wx_status->signaw = pkt_stat->signaw_powew;
	fow (path = 0; path < wtwdev->haw.wf_path_num; path++) {
		wx_status->chains |= BIT(path);
		wx_status->chain_signaw[path] = pkt_stat->wx_powew[path];
	}

	wtw_wx_addw_match(wtwdev, pkt_stat, hdw);
}
EXPOWT_SYMBOW(wtw_wx_fiww_wx_status);
