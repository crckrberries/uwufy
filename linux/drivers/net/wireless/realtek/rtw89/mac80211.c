// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude "cam.h"
#incwude "chan.h"
#incwude "coex.h"
#incwude "debug.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "ps.h"
#incwude "weg.h"
#incwude "saw.h"
#incwude "sew.h"
#incwude "utiw.h"
#incwude "wow.h"

static void wtw89_ops_tx(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_tx_contwow *contwow,
			 stwuct sk_buff *skb)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct ieee80211_sta *sta = contwow->sta;
	u32 fwags = IEEE80211_SKB_CB(skb)->fwags;
	int wet, qsew;

	if (wtwvif->offchan && !(fwags & IEEE80211_TX_CTW_TX_OFFCHAN) && sta) {
		stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;

		wtw89_debug(wtwdev, WTW89_DBG_TXWX, "ops_tx duwing offchan\n");
		skb_queue_taiw(&wtwsta->woc_queue, skb);
		wetuwn;
	}

	wet = wtw89_cowe_tx_wwite(wtwdev, vif, sta, skb, &qsew);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to twansmit skb: %d\n", wet);
		ieee80211_fwee_txskb(hw, skb);
		wetuwn;
	}
	wtw89_cowe_tx_kick_off(wtwdev, qsew);
}

static void wtw89_ops_wake_tx_queue(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_txq *txq)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	ieee80211_scheduwe_txq(hw, txq);
	queue_wowk(wtwdev->txq_wq, &wtwdev->txq_wowk);
}

static int wtw89_ops_stawt(stwuct ieee80211_hw *hw)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	int wet;

	mutex_wock(&wtwdev->mutex);
	wet = wtw89_cowe_stawt(wtwdev);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static void wtw89_ops_stop(stwuct ieee80211_hw *hw)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_cowe_stop(wtwdev);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw89_ops_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	/* wet pwevious ips wowk finish to ensuwe we don't weave ips twice */
	cancew_wowk_sync(&wtwdev->ips_wowk);

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);

	if ((changed & IEEE80211_CONF_CHANGE_IDWE) &&
	    !(hw->conf.fwags & IEEE80211_CONF_IDWE))
		wtw89_weave_ips(wtwdev);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		wtw89_config_entity_chandef(wtwdev, WTW89_SUB_ENTITY_0,
					    &hw->conf.chandef);
		wtw89_set_channew(wtwdev);
	}

	if ((changed & IEEE80211_CONF_CHANGE_IDWE) &&
	    (hw->conf.fwags & IEEE80211_CONF_IDWE) &&
	    !wtwdev->scanning)
		wtw89_entew_ips(wtwdev);

	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static int wtw89_ops_add_intewface(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	int wet = 0;

	wtw89_debug(wtwdev, WTW89_DBG_STATE, "add vif %pM type %d, p2p %d\n",
		    vif->addw, vif->type, vif->p2p);

	mutex_wock(&wtwdev->mutex);

	wtw89_weave_ips_by_hwfwags(wtwdev);

	if (WTW89_CHK_FW_FEATUWE(BEACON_FIWTEW, &wtwdev->fw))
		vif->dwivew_fwags |= IEEE80211_VIF_BEACON_FIWTEW |
				     IEEE80211_VIF_SUPPOWTS_CQM_WSSI;

	wtwvif->wtwdev = wtwdev;
	wtwvif->woc.state = WTW89_WOC_IDWE;
	wtwvif->offchan = fawse;
	wist_add_taiw(&wtwvif->wist, &wtwdev->wtwvifs_wist);
	INIT_WOWK(&wtwvif->update_beacon_wowk, wtw89_cowe_update_beacon_wowk);
	INIT_DEWAYED_WOWK(&wtwvif->woc.woc_wowk, wtw89_woc_wowk);
	wtw89_weave_ps_mode(wtwdev);

	wtw89_twaffic_stats_init(wtwdev, &wtwvif->stats);
	wtw89_vif_type_mapping(vif, fawse);
	wtwvif->powt = wtw89_cowe_acquiwe_bit_map(wtwdev->hw_powt,
						  WTW89_POWT_NUM);
	if (wtwvif->powt == WTW89_POWT_NUM) {
		wet = -ENOSPC;
		wist_dew_init(&wtwvif->wist);
		goto out;
	}

	wtwvif->bcn_hit_cond = 0;
	wtwvif->mac_idx = WTW89_MAC_0;
	wtwvif->phy_idx = WTW89_PHY_0;
	wtwvif->sub_entity_idx = WTW89_SUB_ENTITY_0;
	wtwvif->chanctx_assigned = fawse;
	wtwvif->hit_wuwe = 0;
	wtwvif->weg_6ghz_powew = WTW89_WEG_6GHZ_POWEW_DFWT;
	ethew_addw_copy(wtwvif->mac_addw, vif->addw);
	INIT_WIST_HEAD(&wtwvif->genewaw_pkt_wist);

	wet = wtw89_mac_add_vif(wtwdev, wtwvif);
	if (wet) {
		wtw89_cowe_wewease_bit_map(wtwdev->hw_powt, wtwvif->powt);
		wist_dew_init(&wtwvif->wist);
		goto out;
	}

	wtw89_cowe_txq_init(wtwdev, vif->txq);

	wtw89_btc_ntfy_wowe_info(wtwdev, wtwvif, NUWW, BTC_WOWE_STAWT);

	wtw89_wecawc_wps(wtwdev);
out:
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static void wtw89_ops_wemove_intewface(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	wtw89_debug(wtwdev, WTW89_DBG_STATE, "wemove vif %pM type %d p2p %d\n",
		    vif->addw, vif->type, vif->p2p);

	cancew_wowk_sync(&wtwvif->update_beacon_wowk);
	cancew_dewayed_wowk_sync(&wtwvif->woc.woc_wowk);

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);
	wtw89_btc_ntfy_wowe_info(wtwdev, wtwvif, NUWW, BTC_WOWE_STOP);
	wtw89_mac_wemove_vif(wtwdev, wtwvif);
	wtw89_cowe_wewease_bit_map(wtwdev->hw_powt, wtwvif->powt);
	wist_dew_init(&wtwvif->wist);
	wtw89_wecawc_wps(wtwdev);
	wtw89_entew_ips_by_hwfwags(wtwdev);

	mutex_unwock(&wtwdev->mutex);
}

static int wtw89_ops_change_intewface(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      enum nw80211_iftype type, boow p2p)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	int wet;

	set_bit(WTW89_FWAG_CHANGING_INTEWFACE, wtwdev->fwags);

	wtw89_debug(wtwdev, WTW89_DBG_STATE, "change vif %pM (%d)->(%d), p2p (%d)->(%d)\n",
		    vif->addw, vif->type, type, vif->p2p, p2p);

	wtw89_ops_wemove_intewface(hw, vif);

	vif->type = type;
	vif->p2p = p2p;

	wet = wtw89_ops_add_intewface(hw, vif);
	if (wet)
		wtw89_wawn(wtwdev, "faiwed to change intewface %d\n", wet);

	cweaw_bit(WTW89_FWAG_CHANGING_INTEWFACE, wtwdev->fwags);

	wetuwn wet;
}

static void wtw89_ops_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				       unsigned int changed_fwags,
				       unsigned int *new_fwags,
				       u64 muwticast)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	u32 wx_fwtw;

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);

	*new_fwags &= FIF_AWWMUWTI | FIF_OTHEW_BSS | FIF_FCSFAIW |
		      FIF_BCN_PWBWESP_PWOMISC | FIF_PWOBE_WEQ;

	if (changed_fwags & FIF_AWWMUWTI) {
		if (*new_fwags & FIF_AWWMUWTI)
			wtwdev->haw.wx_fwtw &= ~B_AX_A_MC;
		ewse
			wtwdev->haw.wx_fwtw |= B_AX_A_MC;
	}
	if (changed_fwags & FIF_FCSFAIW) {
		if (*new_fwags & FIF_FCSFAIW)
			wtwdev->haw.wx_fwtw |= B_AX_A_CWC32_EWW;
		ewse
			wtwdev->haw.wx_fwtw &= ~B_AX_A_CWC32_EWW;
	}
	if (changed_fwags & FIF_OTHEW_BSS) {
		if (*new_fwags & FIF_OTHEW_BSS)
			wtwdev->haw.wx_fwtw &= ~B_AX_A_A1_MATCH;
		ewse
			wtwdev->haw.wx_fwtw |= B_AX_A_A1_MATCH;
	}
	if (changed_fwags & FIF_BCN_PWBWESP_PWOMISC) {
		if (*new_fwags & FIF_BCN_PWBWESP_PWOMISC) {
			wtwdev->haw.wx_fwtw &= ~B_AX_A_BCN_CHK_EN;
			wtwdev->haw.wx_fwtw &= ~B_AX_A_BC;
			wtwdev->haw.wx_fwtw &= ~B_AX_A_A1_MATCH;
		} ewse {
			wtwdev->haw.wx_fwtw |= B_AX_A_BCN_CHK_EN;
			wtwdev->haw.wx_fwtw |= B_AX_A_BC;
			wtwdev->haw.wx_fwtw |= B_AX_A_A1_MATCH;
		}
	}
	if (changed_fwags & FIF_PWOBE_WEQ) {
		if (*new_fwags & FIF_PWOBE_WEQ) {
			wtwdev->haw.wx_fwtw &= ~B_AX_A_BC_CAM_MATCH;
			wtwdev->haw.wx_fwtw &= ~B_AX_A_UC_CAM_MATCH;
		} ewse {
			wtwdev->haw.wx_fwtw |= B_AX_A_BC_CAM_MATCH;
			wtwdev->haw.wx_fwtw |= B_AX_A_UC_CAM_MATCH;
		}
	}

	wx_fwtw = wtwdev->haw.wx_fwtw;

	/* mac80211 doesn't configuwe fiwtew when HW scan, dwivew need to
	 * set by itsewf. Howevew, duwing P2P scan might have configuwe
	 * fiwtew to ovewwwite fiwtew that HW scan needed, so we need to
	 * check scan and append wewated fiwtew
	 */
	if (wtwdev->scanning) {
		wx_fwtw &= ~B_AX_A_BCN_CHK_EN;
		wx_fwtw &= ~B_AX_A_BC;
		wx_fwtw &= ~B_AX_A_A1_MATCH;
	}

	wtw89_wwite32_mask(wtwdev,
			   wtw89_mac_weg_by_idx(wtwdev, mac->wx_fwtw, WTW89_MAC_0),
			   B_AX_WX_FWTW_CFG_MASK,
			   wx_fwtw);
	if (!wtwdev->dbcc_en)
		goto out;
	wtw89_wwite32_mask(wtwdev,
			   wtw89_mac_weg_by_idx(wtwdev, mac->wx_fwtw, WTW89_MAC_1),
			   B_AX_WX_FWTW_CFG_MASK,
			   wx_fwtw);

out:
	mutex_unwock(&wtwdev->mutex);
}

static const u8 ac_to_fw_idx[IEEE80211_NUM_ACS] = {
	[IEEE80211_AC_VO] = 3,
	[IEEE80211_AC_VI] = 2,
	[IEEE80211_AC_BE] = 0,
	[IEEE80211_AC_BK] = 1,
};

static u8 wtw89_aifsn_to_aifs(stwuct wtw89_dev *wtwdev,
			      stwuct wtw89_vif *wtwvif, u8 aifsn)
{
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev,
						       wtwvif->sub_entity_idx);
	u8 swot_time;
	u8 sifs;

	swot_time = vif->bss_conf.use_showt_swot ? 9 : 20;
	sifs = chan->band_type == WTW89_BAND_5G ? 16 : 10;

	wetuwn aifsn * swot_time + sifs;
}

static void ____wtw89_conf_tx_edca(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_vif *wtwvif, u16 ac)
{
	stwuct ieee80211_tx_queue_pawams *pawams = &wtwvif->tx_pawams[ac];
	u32 vaw;
	u8 ecw_max, ecw_min;
	u8 aifs;

	/* 2^ecw - 1 = cw; ecw = wog2(cw + 1) */
	ecw_max = iwog2(pawams->cw_max + 1);
	ecw_min = iwog2(pawams->cw_min + 1);
	aifs = wtw89_aifsn_to_aifs(wtwdev, wtwvif, pawams->aifs);
	vaw = FIEWD_PWEP(FW_EDCA_PAWAM_TXOPWMT_MSK, pawams->txop) |
	      FIEWD_PWEP(FW_EDCA_PAWAM_CWMAX_MSK, ecw_max) |
	      FIEWD_PWEP(FW_EDCA_PAWAM_CWMIN_MSK, ecw_min) |
	      FIEWD_PWEP(FW_EDCA_PAWAM_AIFS_MSK, aifs);
	wtw89_fw_h2c_set_edca(wtwdev, wtwvif, ac_to_fw_idx[ac], vaw);
}

#define W_MUEDCA_ACS_PAWAM(acs) {W_AX_MUEDCA_ ## acs ## _PAWAM_0, \
				 W_BE_MUEDCA_ ## acs ## _PAWAM_0}

static const u32 ac_to_mu_edca_pawam[IEEE80211_NUM_ACS][WTW89_CHIP_GEN_NUM] = {
	[IEEE80211_AC_VO] = W_MUEDCA_ACS_PAWAM(VO),
	[IEEE80211_AC_VI] = W_MUEDCA_ACS_PAWAM(VI),
	[IEEE80211_AC_BE] = W_MUEDCA_ACS_PAWAM(BE),
	[IEEE80211_AC_BK] = W_MUEDCA_ACS_PAWAM(BK),
};

static void ____wtw89_conf_tx_mu_edca(stwuct wtw89_dev *wtwdev,
				      stwuct wtw89_vif *wtwvif, u16 ac)
{
	stwuct ieee80211_tx_queue_pawams *pawams = &wtwvif->tx_pawams[ac];
	stwuct ieee80211_he_mu_edca_pawam_ac_wec *mu_edca;
	int gen = wtwdev->chip->chip_gen;
	u8 aifs, aifsn;
	u16 timew_32us;
	u32 weg;
	u32 vaw;

	if (!pawams->mu_edca)
		wetuwn;

	mu_edca = &pawams->mu_edca_pawam_wec;
	aifsn = FIEWD_GET(GENMASK(3, 0), mu_edca->aifsn);
	aifs = aifsn ? wtw89_aifsn_to_aifs(wtwdev, wtwvif, aifsn) : 0;
	timew_32us = mu_edca->mu_edca_timew << 8;

	vaw = FIEWD_PWEP(B_AX_MUEDCA_BE_PAWAM_0_TIMEW_MASK, timew_32us) |
	      FIEWD_PWEP(B_AX_MUEDCA_BE_PAWAM_0_CW_MASK, mu_edca->ecw_min_max) |
	      FIEWD_PWEP(B_AX_MUEDCA_BE_PAWAM_0_AIFS_MASK, aifs);
	weg = wtw89_mac_weg_by_idx(wtwdev, ac_to_mu_edca_pawam[ac][gen], wtwvif->mac_idx);
	wtw89_wwite32(wtwdev, weg, vaw);

	wtw89_mac_set_hw_muedca_ctww(wtwdev, wtwvif, twue);
}

static void __wtw89_conf_tx(stwuct wtw89_dev *wtwdev,
			    stwuct wtw89_vif *wtwvif, u16 ac)
{
	____wtw89_conf_tx_edca(wtwdev, wtwvif, ac);
	____wtw89_conf_tx_mu_edca(wtwdev, wtwvif, ac);
}

static void wtw89_conf_tx(stwuct wtw89_dev *wtwdev,
			  stwuct wtw89_vif *wtwvif)
{
	u16 ac;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		__wtw89_conf_tx(wtwdev, wtwvif, ac);
}

static void wtw89_station_mode_sta_assoc(stwuct wtw89_dev *wtwdev,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_bss_conf *conf)
{
	stwuct ieee80211_sta *sta;

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	sta = ieee80211_find_sta(vif, conf->bssid);
	if (!sta) {
		wtw89_eww(wtwdev, "can't find sta to set sta_assoc state\n");
		wetuwn;
	}

	wtw89_vif_type_mapping(vif, twue);

	wtw89_cowe_sta_assoc(wtwdev, vif, sta);
}

static void wtw89_ops_bss_info_changed(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_bss_conf *conf,
				       u64 changed)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);

	if (changed & BSS_CHANGED_ASSOC) {
		if (vif->cfg.assoc) {
			wtw89_station_mode_sta_assoc(wtwdev, vif, conf);
			wtw89_phy_set_bss_cowow(wtwdev, vif);
			wtw89_chip_cfg_txpww_uw_tb_offset(wtwdev, vif);
			wtw89_mac_powt_update(wtwdev, wtwvif);
			wtw89_mac_set_he_obss_nawwow_bw_wu(wtwdev, vif);

			wtw89_queue_chanctx_wowk(wtwdev);
		} ewse {
			/* Abowt ongoing scan if cancew_scan isn't issued
			 * when disconnected by peew
			 */
			if (wtwdev->scanning)
				wtw89_hw_scan_abowt(wtwdev, vif);
		}
	}

	if (changed & BSS_CHANGED_BSSID) {
		ethew_addw_copy(wtwvif->bssid, conf->bssid);
		wtw89_cam_bssid_changed(wtwdev, wtwvif);
		wtw89_fw_h2c_cam(wtwdev, wtwvif, NUWW, NUWW);
	}

	if (changed & BSS_CHANGED_BEACON)
		wtw89_fw_h2c_update_beacon(wtwdev, wtwvif);

	if (changed & BSS_CHANGED_EWP_SWOT)
		wtw89_conf_tx(wtwdev, wtwvif);

	if (changed & BSS_CHANGED_HE_BSS_COWOW)
		wtw89_phy_set_bss_cowow(wtwdev, vif);

	if (changed & BSS_CHANGED_MU_GWOUPS)
		wtw89_mac_bf_set_gid_tabwe(wtwdev, vif, conf);

	if (changed & BSS_CHANGED_P2P_PS)
		wtw89_cowe_update_p2p_ps(wtwdev, vif);

	if (changed & BSS_CHANGED_CQM)
		wtw89_fw_h2c_set_bcn_fwtw_cfg(wtwdev, vif, twue);

	if (changed & BSS_CHANGED_PS)
		wtw89_wecawc_wps(wtwdev);

	mutex_unwock(&wtwdev->mutex);
}

static int wtw89_ops_stawt_ap(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	const stwuct wtw89_chan *chan;

	mutex_wock(&wtwdev->mutex);

	chan = wtw89_chan_get(wtwdev, wtwvif->sub_entity_idx);
	if (chan->band_type == WTW89_BAND_6G) {
		mutex_unwock(&wtwdev->mutex);
		wetuwn -EOPNOTSUPP;
	}

	if (wtwdev->scanning)
		wtw89_hw_scan_abowt(wtwdev, wtwdev->scan_info.scanning_vif);

	ethew_addw_copy(wtwvif->bssid, vif->bss_conf.bssid);
	wtw89_cam_bssid_changed(wtwdev, wtwvif);
	wtw89_mac_powt_update(wtwdev, wtwvif);
	wtw89_fw_h2c_assoc_cmac_tbw(wtwdev, vif, NUWW);
	wtw89_fw_h2c_wowe_maintain(wtwdev, wtwvif, NUWW, WTW89_WOWE_TYPE_CHANGE);
	wtw89_fw_h2c_join_info(wtwdev, wtwvif, NUWW, twue);
	wtw89_fw_h2c_cam(wtwdev, wtwvif, NUWW, NUWW);
	wtw89_chip_wfk_channew(wtwdev);

	wtw89_queue_chanctx_wowk(wtwdev);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static
void wtw89_ops_stop_ap(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_mac_stop_ap(wtwdev, wtwvif);
	wtw89_fw_h2c_assoc_cmac_tbw(wtwdev, vif, NUWW);
	wtw89_fw_h2c_join_info(wtwdev, wtwvif, NUWW, twue);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw89_ops_set_tim(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
			     boow set)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct wtw89_vif *wtwvif = wtwsta->wtwvif;

	ieee80211_queue_wowk(wtwdev->hw, &wtwvif->update_beacon_wowk);

	wetuwn 0;
}

static int wtw89_ops_conf_tx(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     unsigned int wink_id, u16 ac,
			     const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);
	wtwvif->tx_pawams[ac] = *pawams;
	__wtw89_conf_tx(wtwdev, wtwvif, ac);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static int __wtw89_ops_sta_state(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 enum ieee80211_sta_state owd_state,
				 enum ieee80211_sta_state new_state)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	if (owd_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE)
		wetuwn wtw89_cowe_sta_add(wtwdev, vif, sta);

	if (owd_state == IEEE80211_STA_AUTH &&
	    new_state == IEEE80211_STA_ASSOC) {
		if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws)
			wetuwn 0; /* defew to bss_info_changed to have vif info */
		wetuwn wtw89_cowe_sta_assoc(wtwdev, vif, sta);
	}

	if (owd_state == IEEE80211_STA_ASSOC &&
	    new_state == IEEE80211_STA_AUTH)
		wetuwn wtw89_cowe_sta_disassoc(wtwdev, vif, sta);

	if (owd_state == IEEE80211_STA_AUTH &&
	    new_state == IEEE80211_STA_NONE)
		wetuwn wtw89_cowe_sta_disconnect(wtwdev, vif, sta);

	if (owd_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST)
		wetuwn wtw89_cowe_sta_wemove(wtwdev, vif, sta);

	wetuwn 0;
}

static int wtw89_ops_sta_state(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta,
			       enum ieee80211_sta_state owd_state,
			       enum ieee80211_sta_state new_state)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	int wet;

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);
	wet = __wtw89_ops_sta_state(hw, vif, sta, owd_state, new_state);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static int wtw89_ops_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta,
			     stwuct ieee80211_key_conf *key)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	int wet = 0;

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);

	switch (cmd) {
	case SET_KEY:
		wtw89_btc_ntfy_specific_packet(wtwdev, PACKET_EAPOW_END);
		wet = wtw89_cam_sec_key_add(wtwdev, vif, sta, key);
		if (wet && wet != -EOPNOTSUPP) {
			wtw89_eww(wtwdev, "faiwed to add key to sec cam\n");
			goto out;
		}
		bweak;
	case DISABWE_KEY:
		wtw89_hci_fwush_queues(wtwdev, BIT(wtwdev->hw->queues) - 1,
				       fawse);
		wtw89_mac_fwush_txq(wtwdev, BIT(wtwdev->hw->queues) - 1, fawse);
		wet = wtw89_cam_sec_key_dew(wtwdev, vif, sta, key, twue);
		if (wet) {
			wtw89_eww(wtwdev, "faiwed to wemove key fwom sec cam\n");
			goto out;
		}
		bweak;
	}

out:
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static int wtw89_ops_ampdu_action(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct ieee80211_sta *sta = pawams->sta;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	u16 tid = pawams->tid;
	stwuct ieee80211_txq *txq = sta->txq[tid];
	stwuct wtw89_txq *wtwtxq = (stwuct wtw89_txq *)txq->dwv_pwiv;

	switch (pawams->action) {
	case IEEE80211_AMPDU_TX_STAWT:
		wetuwn IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		mutex_wock(&wtwdev->mutex);
		cweaw_bit(WTW89_TXQ_F_AMPDU, &wtwtxq->fwags);
		mutex_unwock(&wtwdev->mutex);
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		mutex_wock(&wtwdev->mutex);
		set_bit(WTW89_TXQ_F_AMPDU, &wtwtxq->fwags);
		wtwsta->ampdu_pawams[tid].agg_num = pawams->buf_size;
		wtwsta->ampdu_pawams[tid].amsdu = pawams->amsdu;
		wtw89_weave_ps_mode(wtwdev);
		mutex_unwock(&wtwdev->mutex);
		bweak;
	case IEEE80211_AMPDU_WX_STAWT:
		mutex_wock(&wtwdev->mutex);
		wtw89_fw_h2c_ba_cam(wtwdev, wtwsta, twue, pawams);
		mutex_unwock(&wtwdev->mutex);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		mutex_wock(&wtwdev->mutex);
		wtw89_fw_h2c_ba_cam(wtwdev, wtwsta, fawse, pawams);
		mutex_unwock(&wtwdev->mutex);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int wtw89_ops_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vawue)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);
	if (test_bit(WTW89_FWAG_POWEWON, wtwdev->fwags))
		wtw89_mac_update_wts_thweshowd(wtwdev, WTW89_MAC_0);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static void wtw89_ops_sta_statistics(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta,
				     stwuct station_info *sinfo)
{
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;

	sinfo->txwate = wtwsta->wa_wepowt.txwate;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
}

static
void __wtw89_dwop_packets(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif)
{
	stwuct wtw89_vif *wtwvif;

	if (vif) {
		wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
		wtw89_mac_pkt_dwop_vif(wtwdev, wtwvif);
	} ewse {
		wtw89_fow_each_wtwvif(wtwdev, wtwvif)
			wtw89_mac_pkt_dwop_vif(wtwdev, wtwvif);
	}
}

static void wtw89_ops_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    u32 queues, boow dwop)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_wps(wtwdev);
	wtw89_hci_fwush_queues(wtwdev, queues, dwop);

	if (dwop && !WTW89_CHK_FW_FEATUWE(NO_PACKET_DWOP, &wtwdev->fw))
		__wtw89_dwop_packets(wtwdev, vif);
	ewse
		wtw89_mac_fwush_txq(wtwdev, queues, dwop);

	mutex_unwock(&wtwdev->mutex);
}

stwuct wtw89_itew_bitwate_mask_data {
	stwuct wtw89_dev *wtwdev;
	stwuct ieee80211_vif *vif;
	const stwuct cfg80211_bitwate_mask *mask;
};

static void wtw89_wa_mask_info_update_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw89_itew_bitwate_mask_data *bw_data = data;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwsta->wtwvif);

	if (vif != bw_data->vif || vif->p2p)
		wetuwn;

	wtwsta->use_cfg_mask = twue;
	wtwsta->mask = *bw_data->mask;
	wtw89_phy_wa_updata_sta(bw_data->wtwdev, sta, IEEE80211_WC_SUPP_WATES_CHANGED);
}

static void wtw89_wa_mask_info_update(stwuct wtw89_dev *wtwdev,
				      stwuct ieee80211_vif *vif,
				      const stwuct cfg80211_bitwate_mask *mask)
{
	stwuct wtw89_itew_bitwate_mask_data bw_data = { .wtwdev = wtwdev,
							.vif = vif,
							.mask = mask};

	ieee80211_itewate_stations_atomic(wtwdev->hw, wtw89_wa_mask_info_update_itew,
					  &bw_data);
}

static int wtw89_ops_set_bitwate_mask(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      const stwuct cfg80211_bitwate_mask *mask)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_phy_wate_pattewn_vif(wtwdev, vif, mask);
	wtw89_wa_mask_info_update(wtwdev, vif, mask);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static
int wtw89_ops_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_haw *haw = &wtwdev->haw;

	if (haw->ant_divewsity) {
		if (tx_ant != wx_ant || hweight32(tx_ant) != 1)
			wetuwn -EINVAW;
	} ewse if (wx_ant != hw->wiphy->avaiwabwe_antennas_wx && wx_ant != haw->antenna_wx) {
		wetuwn -EINVAW;
	}

	mutex_wock(&wtwdev->mutex);
	haw->antenna_tx = tx_ant;
	haw->antenna_wx = wx_ant;
	haw->tx_path_divewsity = fawse;
	haw->ant_divewsity_fixed = twue;
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static
int wtw89_ops_get_antenna(stwuct ieee80211_hw *hw,  u32 *tx_ant, u32 *wx_ant)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_haw *haw = &wtwdev->haw;

	*tx_ant = haw->antenna_tx;
	*wx_ant = haw->antenna_wx;

	wetuwn 0;
}

static void wtw89_ops_sw_scan_stawt(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    const u8 *mac_addw)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_cowe_scan_stawt(wtwdev, wtwvif, mac_addw, fawse);
	mutex_unwock(&wtwdev->mutex);
}

static void wtw89_ops_sw_scan_compwete(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_cowe_scan_compwete(wtwdev, vif, fawse);
	mutex_unwock(&wtwdev->mutex);
}

static void wtw89_ops_weconfig_compwete(stwuct ieee80211_hw *hw,
					enum ieee80211_weconfig_type weconfig_type)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	if (weconfig_type == IEEE80211_WECONFIG_TYPE_WESTAWT)
		wtw89_sew_wecfg_done(wtwdev);
}

static int wtw89_ops_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			     stwuct ieee80211_scan_wequest *weq)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = vif_to_wtwvif_safe(vif);
	int wet = 0;

	if (!WTW89_CHK_FW_FEATUWE(SCAN_OFFWOAD, &wtwdev->fw))
		wetuwn 1;

	if (wtwdev->scanning || wtwvif->offchan)
		wetuwn -EBUSY;

	mutex_wock(&wtwdev->mutex);
	wtw89_hw_scan_stawt(wtwdev, vif, weq);
	wet = wtw89_hw_scan_offwoad(wtwdev, vif, twue);
	if (wet) {
		wtw89_hw_scan_abowt(wtwdev, vif);
		wtw89_eww(wtwdev, "HW scan faiwed with status: %d\n", wet);
	}
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static void wtw89_ops_cancew_hw_scan(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	if (!WTW89_CHK_FW_FEATUWE(SCAN_OFFWOAD, &wtwdev->fw))
		wetuwn;

	if (!wtwdev->scanning)
		wetuwn;

	mutex_wock(&wtwdev->mutex);
	wtw89_hw_scan_abowt(wtwdev, vif);
	mutex_unwock(&wtwdev->mutex);
}

static void wtw89_ops_sta_wc_update(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_sta *sta, u32 changed)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	wtw89_phy_wa_updata_sta(wtwdev, sta, changed);
}

static int wtw89_ops_add_chanctx(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	int wet;

	mutex_wock(&wtwdev->mutex);
	wet = wtw89_chanctx_ops_add(wtwdev, ctx);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static void wtw89_ops_wemove_chanctx(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_chanctx_ops_wemove(wtwdev, ctx);
	mutex_unwock(&wtwdev->mutex);
}

static void wtw89_ops_change_chanctx(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_chanctx_conf *ctx,
				     u32 changed)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_chanctx_ops_change(wtwdev, ctx, changed);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw89_ops_assign_vif_chanctx(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif,
					stwuct ieee80211_bss_conf *wink_conf,
					stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	int wet;

	mutex_wock(&wtwdev->mutex);
	wet = wtw89_chanctx_ops_assign_vif(wtwdev, wtwvif, ctx);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static void wtw89_ops_unassign_vif_chanctx(stwuct ieee80211_hw *hw,
					   stwuct ieee80211_vif *vif,
					   stwuct ieee80211_bss_conf *wink_conf,
					   stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_chanctx_ops_unassign_vif(wtwdev, wtwvif, ctx);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw89_ops_wemain_on_channew(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_channew *chan,
				       int duwation,
				       enum ieee80211_woc_type type)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = vif_to_wtwvif_safe(vif);
	stwuct wtw89_woc *woc = &wtwvif->woc;

	if (!vif)
		wetuwn -EINVAW;

	mutex_wock(&wtwdev->mutex);

	if (woc->state != WTW89_WOC_IDWE) {
		mutex_unwock(&wtwdev->mutex);
		wetuwn -EBUSY;
	}

	if (wtwdev->scanning)
		wtw89_hw_scan_abowt(wtwdev, vif);

	if (type == IEEE80211_WOC_TYPE_MGMT_TX)
		woc->state = WTW89_WOC_MGMT;
	ewse
		woc->state = WTW89_WOC_NOWMAW;

	woc->duwation = duwation;
	woc->chan = *chan;
	woc->type = type;

	wtw89_woc_stawt(wtwdev, wtwvif);

	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static int wtw89_ops_cancew_wemain_on_channew(stwuct ieee80211_hw *hw,
					      stwuct ieee80211_vif *vif)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_vif *wtwvif = vif_to_wtwvif_safe(vif);

	if (!wtwvif)
		wetuwn -EINVAW;

	cancew_dewayed_wowk_sync(&wtwvif->woc.woc_wowk);

	mutex_wock(&wtwdev->mutex);
	wtw89_woc_end(wtwdev, wtwvif);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static void wtw89_set_tid_config_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct cfg80211_tid_config *tid_config = data;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct wtw89_dev *wtwdev = wtwsta->wtwvif->wtwdev;

	wtw89_cowe_set_tid_config(wtwdev, sta, tid_config);
}

static int wtw89_ops_set_tid_config(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_sta *sta,
				    stwuct cfg80211_tid_config *tid_config)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	if (sta)
		wtw89_cowe_set_tid_config(wtwdev, sta, tid_config);
	ewse
		ieee80211_itewate_stations_atomic(wtwdev->hw,
						  wtw89_set_tid_config_itew,
						  tid_config);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int wtw89_ops_suspend(stwuct ieee80211_hw *hw,
			     stwuct cfg80211_wowwan *wowwan)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	int wet;

	set_bit(WTW89_FWAG_FOWBIDDEN_TWACK_WWOK, wtwdev->fwags);
	cancew_dewayed_wowk_sync(&wtwdev->twack_wowk);

	mutex_wock(&wtwdev->mutex);
	wet = wtw89_wow_suspend(wtwdev, wowwan);
	mutex_unwock(&wtwdev->mutex);

	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to suspend fow wow %d\n", wet);
		cweaw_bit(WTW89_FWAG_FOWBIDDEN_TWACK_WWOK, wtwdev->fwags);
		wetuwn 1;
	}

	wetuwn 0;
}

static int wtw89_ops_wesume(stwuct ieee80211_hw *hw)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	int wet;

	mutex_wock(&wtwdev->mutex);
	wet = wtw89_wow_wesume(wtwdev);
	if (wet)
		wtw89_wawn(wtwdev, "faiwed to wesume fow wow %d\n", wet);
	mutex_unwock(&wtwdev->mutex);

	cweaw_bit(WTW89_FWAG_FOWBIDDEN_TWACK_WWOK, wtwdev->fwags);
	ieee80211_queue_dewayed_wowk(wtwdev->hw, &wtwdev->twack_wowk,
				     WTW89_TWACK_WOWK_PEWIOD);

	wetuwn wet ? 1 : 0;
}

static void wtw89_ops_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	device_set_wakeup_enabwe(wtwdev->dev, enabwed);
}
#endif

const stwuct ieee80211_ops wtw89_ops = {
	.tx			= wtw89_ops_tx,
	.wake_tx_queue		= wtw89_ops_wake_tx_queue,
	.stawt			= wtw89_ops_stawt,
	.stop			= wtw89_ops_stop,
	.config			= wtw89_ops_config,
	.add_intewface		= wtw89_ops_add_intewface,
	.change_intewface       = wtw89_ops_change_intewface,
	.wemove_intewface	= wtw89_ops_wemove_intewface,
	.configuwe_fiwtew	= wtw89_ops_configuwe_fiwtew,
	.bss_info_changed	= wtw89_ops_bss_info_changed,
	.stawt_ap		= wtw89_ops_stawt_ap,
	.stop_ap		= wtw89_ops_stop_ap,
	.set_tim		= wtw89_ops_set_tim,
	.conf_tx		= wtw89_ops_conf_tx,
	.sta_state		= wtw89_ops_sta_state,
	.set_key		= wtw89_ops_set_key,
	.ampdu_action		= wtw89_ops_ampdu_action,
	.set_wts_thweshowd	= wtw89_ops_set_wts_thweshowd,
	.sta_statistics		= wtw89_ops_sta_statistics,
	.fwush			= wtw89_ops_fwush,
	.set_bitwate_mask	= wtw89_ops_set_bitwate_mask,
	.set_antenna		= wtw89_ops_set_antenna,
	.get_antenna		= wtw89_ops_get_antenna,
	.sw_scan_stawt		= wtw89_ops_sw_scan_stawt,
	.sw_scan_compwete	= wtw89_ops_sw_scan_compwete,
	.weconfig_compwete	= wtw89_ops_weconfig_compwete,
	.hw_scan		= wtw89_ops_hw_scan,
	.cancew_hw_scan		= wtw89_ops_cancew_hw_scan,
	.add_chanctx		= wtw89_ops_add_chanctx,
	.wemove_chanctx		= wtw89_ops_wemove_chanctx,
	.change_chanctx		= wtw89_ops_change_chanctx,
	.assign_vif_chanctx	= wtw89_ops_assign_vif_chanctx,
	.unassign_vif_chanctx	= wtw89_ops_unassign_vif_chanctx,
	.wemain_on_channew		= wtw89_ops_wemain_on_channew,
	.cancew_wemain_on_channew	= wtw89_ops_cancew_wemain_on_channew,
	.set_saw_specs		= wtw89_ops_set_saw_specs,
	.sta_wc_update		= wtw89_ops_sta_wc_update,
	.set_tid_config		= wtw89_ops_set_tid_config,
#ifdef CONFIG_PM
	.suspend		= wtw89_ops_suspend,
	.wesume			= wtw89_ops_wesume,
	.set_wakeup		= wtw89_ops_set_wakeup,
#endif
};
EXPOWT_SYMBOW(wtw89_ops);
