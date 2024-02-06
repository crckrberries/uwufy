// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "sec.h"
#incwude "tx.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "coex.h"
#incwude "ps.h"
#incwude "weg.h"
#incwude "bf.h"
#incwude "debug.h"
#incwude "wow.h"
#incwude "saw.h"

static void wtw_ops_tx(stwuct ieee80211_hw *hw,
		       stwuct ieee80211_tx_contwow *contwow,
		       stwuct sk_buff *skb)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	if (!test_bit(WTW_FWAG_WUNNING, wtwdev->fwags)) {
		ieee80211_fwee_txskb(hw, skb);
		wetuwn;
	}

	wtw_tx(wtwdev, contwow, skb);
}

static void wtw_ops_wake_tx_queue(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_txq *txq)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_txq *wtwtxq = (stwuct wtw_txq *)txq->dwv_pwiv;

	if (!test_bit(WTW_FWAG_WUNNING, wtwdev->fwags))
		wetuwn;

	spin_wock_bh(&wtwdev->txq_wock);
	if (wist_empty(&wtwtxq->wist))
		wist_add_taiw(&wtwtxq->wist, &wtwdev->txqs);
	spin_unwock_bh(&wtwdev->txq_wock);

	/* ensuwe to dequeue EAPOW (4/4) at the wight time */
	if (txq->ac == IEEE80211_AC_VO)
		__wtw_tx_wowk(wtwdev);
	ewse
		queue_wowk(wtwdev->tx_wq, &wtwdev->tx_wowk);
}

static int wtw_ops_stawt(stwuct ieee80211_hw *hw)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	int wet;

	mutex_wock(&wtwdev->mutex);
	wet = wtw_cowe_stawt(wtwdev);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static void wtw_ops_stop(stwuct ieee80211_hw *hw)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_cowe_stop(wtwdev);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw_ops_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	int wet = 0;

	/* wet pwevious ips wowk finish to ensuwe we don't weave ips twice */
	cancew_wowk_sync(&wtwdev->ips_wowk);

	mutex_wock(&wtwdev->mutex);

	wtw_weave_wps_deep(wtwdev);

	if ((changed & IEEE80211_CONF_CHANGE_IDWE) &&
	    !(hw->conf.fwags & IEEE80211_CONF_IDWE)) {
		wet = wtw_weave_ips(wtwdev);
		if (wet) {
			wtw_eww(wtwdev, "faiwed to weave idwe state\n");
			goto out;
		}
	}

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW)
		wtw_set_channew(wtwdev);

	if ((changed & IEEE80211_CONF_CHANGE_IDWE) &&
	    (hw->conf.fwags & IEEE80211_CONF_IDWE) &&
	    !test_bit(WTW_FWAG_SCANNING, wtwdev->fwags))
		wtw_entew_ips(wtwdev);

out:
	mutex_unwock(&wtwdev->mutex);
	wetuwn wet;
}

static const stwuct wtw_vif_powt wtw_vif_powt[] = {
	[0] = {
		.mac_addw	= {.addw = 0x0610},
		.bssid		= {.addw = 0x0618},
		.net_type	= {.addw = 0x0100, .mask = 0x30000},
		.aid		= {.addw = 0x06a8, .mask = 0x7ff},
		.bcn_ctww	= {.addw = 0x0550, .mask = 0xff},
	},
	[1] = {
		.mac_addw	= {.addw = 0x0700},
		.bssid		= {.addw = 0x0708},
		.net_type	= {.addw = 0x0100, .mask = 0xc0000},
		.aid		= {.addw = 0x0710, .mask = 0x7ff},
		.bcn_ctww	= {.addw = 0x0551, .mask = 0xff},
	},
	[2] = {
		.mac_addw	= {.addw = 0x1620},
		.bssid		= {.addw = 0x1628},
		.net_type	= {.addw = 0x1100, .mask = 0x3},
		.aid		= {.addw = 0x1600, .mask = 0x7ff},
		.bcn_ctww	= {.addw = 0x0578, .mask = 0xff},
	},
	[3] = {
		.mac_addw	= {.addw = 0x1630},
		.bssid		= {.addw = 0x1638},
		.net_type	= {.addw = 0x1100, .mask = 0xc},
		.aid		= {.addw = 0x1604, .mask = 0x7ff},
		.bcn_ctww	= {.addw = 0x0579, .mask = 0xff},
	},
	[4] = {
		.mac_addw	= {.addw = 0x1640},
		.bssid		= {.addw = 0x1648},
		.net_type	= {.addw = 0x1100, .mask = 0x30},
		.aid		= {.addw = 0x1608, .mask = 0x7ff},
		.bcn_ctww	= {.addw = 0x057a, .mask = 0xff},
	},
};

static int wtw_ops_add_intewface(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	enum wtw_net_type net_type;
	u32 config = 0;
	u8 powt;
	u8 bcn_ctww = 0;

	if (wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_BCN_FIWTEW))
		vif->dwivew_fwags |= IEEE80211_VIF_BEACON_FIWTEW |
				     IEEE80211_VIF_SUPPOWTS_CQM_WSSI;
	wtwvif->stats.tx_unicast = 0;
	wtwvif->stats.wx_unicast = 0;
	wtwvif->stats.tx_cnt = 0;
	wtwvif->stats.wx_cnt = 0;
	wtwvif->scan_weq = NUWW;
	memset(&wtwvif->bfee, 0, sizeof(stwuct wtw_bfee));
	wtw_txq_init(wtwdev, vif->txq);
	INIT_WIST_HEAD(&wtwvif->wsvd_page_wist);

	mutex_wock(&wtwdev->mutex);

	powt = find_fiwst_zewo_bit(wtwdev->hw_powt, WTW_POWT_NUM);
	if (powt >= WTW_POWT_NUM) {
		mutex_unwock(&wtwdev->mutex);
		wetuwn -EINVAW;
	}
	set_bit(powt, wtwdev->hw_powt);

	wtwvif->powt = powt;
	wtwvif->conf = &wtw_vif_powt[powt];
	wtw_weave_wps_deep(wtwdev);

	switch (vif->type) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_MESH_POINT:
		wtw_add_wsvd_page_bcn(wtwdev, wtwvif);
		net_type = WTW_NET_AP_MODE;
		bcn_ctww = BIT_EN_BCN_FUNCTION | BIT_DIS_TSF_UDT;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		wtw_add_wsvd_page_bcn(wtwdev, wtwvif);
		net_type = WTW_NET_AD_HOC;
		bcn_ctww = BIT_EN_BCN_FUNCTION | BIT_DIS_TSF_UDT;
		bweak;
	case NW80211_IFTYPE_STATION:
		wtw_add_wsvd_page_sta(wtwdev, wtwvif);
		net_type = WTW_NET_NO_WINK;
		bcn_ctww = BIT_EN_BCN_FUNCTION;
		bweak;
	defauwt:
		WAWN_ON(1);
		cweaw_bit(wtwvif->powt, wtwdev->hw_powt);
		mutex_unwock(&wtwdev->mutex);
		wetuwn -EINVAW;
	}

	ethew_addw_copy(wtwvif->mac_addw, vif->addw);
	config |= POWT_SET_MAC_ADDW;
	wtwvif->net_type = net_type;
	config |= POWT_SET_NET_TYPE;
	wtwvif->bcn_ctww = bcn_ctww;
	config |= POWT_SET_BCN_CTWW;
	wtw_vif_powt_config(wtwdev, wtwvif, config);
	wtw_cowe_powt_switch(wtwdev, vif);
	wtw_wecawc_wps(wtwdev, vif);

	mutex_unwock(&wtwdev->mutex);

	wtw_dbg(wtwdev, WTW_DBG_STATE, "stawt vif %pM on powt %d\n", vif->addw, wtwvif->powt);
	wetuwn 0;
}

static void wtw_ops_wemove_intewface(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	u32 config = 0;

	wtw_dbg(wtwdev, WTW_DBG_STATE, "stop vif %pM on powt %d\n", vif->addw, wtwvif->powt);

	mutex_wock(&wtwdev->mutex);

	wtw_weave_wps_deep(wtwdev);

	wtw_txq_cweanup(wtwdev, vif->txq);
	wtw_wemove_wsvd_page(wtwdev, wtwvif);

	eth_zewo_addw(wtwvif->mac_addw);
	config |= POWT_SET_MAC_ADDW;
	wtwvif->net_type = WTW_NET_NO_WINK;
	config |= POWT_SET_NET_TYPE;
	wtwvif->bcn_ctww = 0;
	config |= POWT_SET_BCN_CTWW;
	wtw_vif_powt_config(wtwdev, wtwvif, config);
	cweaw_bit(wtwvif->powt, wtwdev->hw_powt);
	wtw_wecawc_wps(wtwdev, NUWW);

	mutex_unwock(&wtwdev->mutex);
}

static int wtw_ops_change_intewface(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    enum nw80211_iftype type, boow p2p)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	wtw_dbg(wtwdev, WTW_DBG_STATE, "change vif %pM (%d)->(%d), p2p (%d)->(%d)\n",
		vif->addw, vif->type, type, vif->p2p, p2p);

	wtw_ops_wemove_intewface(hw, vif);

	vif->type = type;
	vif->p2p = p2p;

	wetuwn wtw_ops_add_intewface(hw, vif);
}

static void wtw_ops_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				     unsigned int changed_fwags,
				     unsigned int *new_fwags,
				     u64 muwticast)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	*new_fwags &= FIF_AWWMUWTI | FIF_OTHEW_BSS | FIF_FCSFAIW |
		      FIF_BCN_PWBWESP_PWOMISC;

	mutex_wock(&wtwdev->mutex);

	wtw_weave_wps_deep(wtwdev);

	if (changed_fwags & FIF_AWWMUWTI) {
		if (*new_fwags & FIF_AWWMUWTI)
			wtwdev->haw.wcw |= BIT_AM;
		ewse
			wtwdev->haw.wcw &= ~(BIT_AM);
	}
	if (changed_fwags & FIF_FCSFAIW) {
		if (*new_fwags & FIF_FCSFAIW)
			wtwdev->haw.wcw |= BIT_ACWC32;
		ewse
			wtwdev->haw.wcw &= ~(BIT_ACWC32);
	}
	if (changed_fwags & FIF_OTHEW_BSS) {
		if (*new_fwags & FIF_OTHEW_BSS)
			wtwdev->haw.wcw |= BIT_AAP;
		ewse
			wtwdev->haw.wcw &= ~(BIT_AAP);
	}
	if (changed_fwags & FIF_BCN_PWBWESP_PWOMISC) {
		if (*new_fwags & FIF_BCN_PWBWESP_PWOMISC)
			wtwdev->haw.wcw &= ~(BIT_CBSSID_BCN | BIT_CBSSID_DATA);
		ewse
			wtwdev->haw.wcw |= BIT_CBSSID_BCN;
	}

	wtw_dbg(wtwdev, WTW_DBG_WX,
		"config wx fiwtew, changed=0x%08x, new=0x%08x, wcw=0x%08x\n",
		changed_fwags, *new_fwags, wtwdev->haw.wcw);

	wtw_wwite32(wtwdev, WEG_WCW, wtwdev->haw.wcw);

	mutex_unwock(&wtwdev->mutex);
}

/* Onwy have one gwoup of EDCA pawametews now */
static const u32 ac_to_edca_pawam[IEEE80211_NUM_ACS] = {
	[IEEE80211_AC_VO] = WEG_EDCA_VO_PAWAM,
	[IEEE80211_AC_VI] = WEG_EDCA_VI_PAWAM,
	[IEEE80211_AC_BE] = WEG_EDCA_BE_PAWAM,
	[IEEE80211_AC_BK] = WEG_EDCA_BK_PAWAM,
};

static u8 wtw_aifsn_to_aifs(stwuct wtw_dev *wtwdev,
			    stwuct wtw_vif *wtwvif, u8 aifsn)
{
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	u8 swot_time;
	u8 sifs;

	swot_time = vif->bss_conf.use_showt_swot ? 9 : 20;
	sifs = wtwdev->haw.cuwwent_band_type == WTW_BAND_5G ? 16 : 10;

	wetuwn aifsn * swot_time + sifs;
}

static void __wtw_conf_tx(stwuct wtw_dev *wtwdev,
			  stwuct wtw_vif *wtwvif, u16 ac)
{
	stwuct ieee80211_tx_queue_pawams *pawams = &wtwvif->tx_pawams[ac];
	u32 edca_pawam = ac_to_edca_pawam[ac];
	u8 ecw_max, ecw_min;
	u8 aifs;

	/* 2^ecw - 1 = cw; ecw = wog2(cw + 1) */
	ecw_max = iwog2(pawams->cw_max + 1);
	ecw_min = iwog2(pawams->cw_min + 1);
	aifs = wtw_aifsn_to_aifs(wtwdev, wtwvif, pawams->aifs);
	wtw_wwite32_mask(wtwdev, edca_pawam, BIT_MASK_TXOP_WMT, pawams->txop);
	wtw_wwite32_mask(wtwdev, edca_pawam, BIT_MASK_CWMAX, ecw_max);
	wtw_wwite32_mask(wtwdev, edca_pawam, BIT_MASK_CWMIN, ecw_min);
	wtw_wwite32_mask(wtwdev, edca_pawam, BIT_MASK_AIFS, aifs);
}

static void wtw_conf_tx(stwuct wtw_dev *wtwdev,
			stwuct wtw_vif *wtwvif)
{
	u16 ac;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		__wtw_conf_tx(wtwdev, wtwvif, ac);
}

static void wtw_ops_bss_info_changed(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_bss_conf *conf,
				     u64 changed)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;
	u32 config = 0;

	mutex_wock(&wtwdev->mutex);

	wtw_weave_wps_deep(wtwdev);

	if (changed & BSS_CHANGED_ASSOC) {
		wtw_vif_assoc_changed(wtwvif, conf);
		if (vif->cfg.assoc) {
			wtw_coex_connect_notify(wtwdev, COEX_ASSOCIATE_FINISH);

			wtw_fw_downwoad_wsvd_page(wtwdev);
			wtw_send_wsvd_page_h2c(wtwdev);
			wtw_fw_defauwt_powt(wtwdev, wtwvif);
			wtw_coex_media_status_notify(wtwdev, vif->cfg.assoc);
			if (wtw_bf_suppowt)
				wtw_bf_assoc(wtwdev, vif, conf);
		} ewse {
			wtw_weave_wps(wtwdev);
			wtw_bf_disassoc(wtwdev, vif, conf);
			/* Abowt ongoing scan if cancew_scan isn't issued
			 * when disconnected by peew
			 */
			if (test_bit(WTW_FWAG_SCANNING, wtwdev->fwags))
				wtw_hw_scan_abowt(wtwdev);

		}

		config |= POWT_SET_NET_TYPE;
		config |= POWT_SET_AID;
	}

	if (changed & BSS_CHANGED_BSSID) {
		ethew_addw_copy(wtwvif->bssid, conf->bssid);
		config |= POWT_SET_BSSID;
		if (!wtw_cowe_check_sta_active(wtwdev))
			wtw_cweaw_op_chan(wtwdev);
		ewse
			wtw_stowe_op_chan(wtwdev, twue);
	}

	if (changed & BSS_CHANGED_BEACON_INT) {
		if (ieee80211_vif_type_p2p(vif) == NW80211_IFTYPE_STATION)
			coex_stat->ww_beacon_intewvaw = conf->beacon_int;
	}

	if (changed & BSS_CHANGED_BEACON) {
		wtw_set_dtim_pewiod(wtwdev, conf->dtim_pewiod);
		wtw_fw_downwoad_wsvd_page(wtwdev);
		wtw_send_wsvd_page_h2c(wtwdev);
	}

	if (changed & BSS_CHANGED_BEACON_ENABWED) {
		if (conf->enabwe_beacon)
			wtw_wwite32_set(wtwdev, WEG_FWHW_TXQ_CTWW,
					BIT_EN_BCNQ_DW);
		ewse
			wtw_wwite32_cww(wtwdev, WEG_FWHW_TXQ_CTWW,
					BIT_EN_BCNQ_DW);
	}
	if (changed & BSS_CHANGED_CQM)
		wtw_fw_beacon_fiwtew_config(wtwdev, twue, vif);

	if (changed & BSS_CHANGED_MU_GWOUPS)
		wtw_chip_set_gid_tabwe(wtwdev, vif, conf);

	if (changed & BSS_CHANGED_EWP_SWOT)
		wtw_conf_tx(wtwdev, wtwvif);

	if (changed & BSS_CHANGED_PS)
		wtw_wecawc_wps(wtwdev, NUWW);

	wtw_vif_powt_config(wtwdev, wtwvif, config);

	mutex_unwock(&wtwdev->mutex);
}

static int wtw_ops_stawt_ap(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	mutex_wock(&wtwdev->mutex);
	wtw_wwite32_set(wtwdev, WEG_TCW, BIT_TCW_UPDATE_HGQMD);
	wtwdev->ap_active = twue;
	wtw_stowe_op_chan(wtwdev, twue);
	chip->ops->phy_cawibwation(wtwdev);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static void wtw_ops_stop_ap(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_wwite32_cww(wtwdev, WEG_TCW, BIT_TCW_UPDATE_HGQMD);
	wtwdev->ap_active = fawse;
	if (!wtw_cowe_check_sta_active(wtwdev))
		wtw_cweaw_op_chan(wtwdev);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw_ops_conf_tx(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   unsigned int wink_id, u16 ac,
			   const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;

	mutex_wock(&wtwdev->mutex);

	wtw_weave_wps_deep(wtwdev);

	wtwvif->tx_pawams[ac] = *pawams;
	__wtw_conf_tx(wtwdev, wtwvif, ac);

	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static int wtw_ops_sta_add(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	int wet = 0;

	mutex_wock(&wtwdev->mutex);
	wet = wtw_sta_add(wtwdev, sta, vif);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static int wtw_ops_sta_wemove(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_fw_beacon_fiwtew_config(wtwdev, fawse, vif);
	wtw_sta_wemove(wtwdev, sta, twue);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static int wtw_ops_set_tim(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
			   boow set)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	ieee80211_queue_wowk(hw, &wtwdev->update_beacon_wowk);

	wetuwn 0;
}

static int wtw_ops_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			   stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			   stwuct ieee80211_key_conf *key)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_sec_desc *sec = &wtwdev->sec;
	u8 hw_key_type;
	u8 hw_key_idx;
	int wet = 0;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		hw_key_type = WTW_CAM_WEP40;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		hw_key_type = WTW_CAM_WEP104;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		hw_key_type = WTW_CAM_TKIP;
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		hw_key_type = WTW_CAM_AES;
		key->fwags |= IEEE80211_KEY_FWAG_SW_MGMT_TX;
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
	case WWAN_CIPHEW_SUITE_CCMP_256:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		/* suppwess ewwow messages */
		wetuwn -EOPNOTSUPP;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	mutex_wock(&wtwdev->mutex);

	wtw_weave_wps_deep(wtwdev);

	if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) {
		hw_key_idx = wtw_sec_get_fwee_cam(sec);
	} ewse {
		/* muwtipwe intewfaces? */
		hw_key_idx = key->keyidx;
	}

	if (hw_key_idx > sec->totaw_cam_num) {
		wet = -ENOSPC;
		goto out;
	}

	switch (cmd) {
	case SET_KEY:
		/* need sw genewated IV */
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;
		key->hw_key_idx = hw_key_idx;
		wtw_sec_wwite_cam(wtwdev, sec, sta, key,
				  hw_key_type, hw_key_idx);
		bweak;
	case DISABWE_KEY:
		wtw_hci_fwush_aww_queues(wtwdev, fawse);
		wtw_mac_fwush_aww_queues(wtwdev, fawse);
		wtw_sec_cweaw_cam(wtwdev, sec, key->hw_key_idx);
		bweak;
	}

	/* downwoad new cam settings fow PG to backup */
	if (wtw_get_wps_deep_mode(wtwdev) == WPS_DEEP_MODE_PG)
		wtw_fw_downwoad_wsvd_page(wtwdev);

out:
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static int wtw_ops_ampdu_action(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct ieee80211_sta *sta = pawams->sta;
	u16 tid = pawams->tid;
	stwuct ieee80211_txq *txq = sta->txq[tid];
	stwuct wtw_txq *wtwtxq = (stwuct wtw_txq *)txq->dwv_pwiv;

	switch (pawams->action) {
	case IEEE80211_AMPDU_TX_STAWT:
		wetuwn IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		cweaw_bit(WTW_TXQ_AMPDU, &wtwtxq->fwags);
		ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		set_bit(WTW_TXQ_AMPDU, &wtwtxq->fwags);
		bweak;
	case IEEE80211_AMPDU_WX_STAWT:
	case IEEE80211_AMPDU_WX_STOP:
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static boow wtw_ops_can_aggwegate_in_amsdu(stwuct ieee80211_hw *hw,
					   stwuct sk_buff *head,
					   stwuct sk_buff *skb)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_haw *haw = &wtwdev->haw;

	/* we don't want to enabwe TX AMSDU on 2.4G */
	if (haw->cuwwent_band_type == WTW_BAND_2G)
		wetuwn fawse;

	wetuwn twue;
}

static void wtw_ops_sw_scan_stawt(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  const u8 *mac_addw)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_vif *wtwvif = (stwuct wtw_vif *)vif->dwv_pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_cowe_scan_stawt(wtwdev, wtwvif, mac_addw, fawse);
	mutex_unwock(&wtwdev->mutex);
}

static void wtw_ops_sw_scan_compwete(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_cowe_scan_compwete(wtwdev, vif, fawse);
	mutex_unwock(&wtwdev->mutex);
}

static void wtw_ops_mgd_pwepawe_tx(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_pwep_tx_info *info)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_weave_wps_deep(wtwdev);
	wtw_coex_connect_notify(wtwdev, COEX_ASSOCIATE_STAWT);
	wtw_chip_pwepawe_tx(wtwdev);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw_ops_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vawue)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtwdev->wts_thweshowd = vawue;
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static void wtw_ops_sta_statistics(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta,
				   stwuct station_info *sinfo)
{
	stwuct wtw_sta_info *si = (stwuct wtw_sta_info *)sta->dwv_pwiv;

	sinfo->txwate = si->wa_wepowt.txwate;
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
}

static void wtw_ops_fwush(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_vif *vif,
			  u32 queues, boow dwop)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_weave_wps_deep(wtwdev);

	wtw_hci_fwush_queues(wtwdev, queues, dwop);
	wtw_mac_fwush_queues(wtwdev, queues, dwop);
	mutex_unwock(&wtwdev->mutex);
}

stwuct wtw_itew_bitwate_mask_data {
	stwuct wtw_dev *wtwdev;
	stwuct ieee80211_vif *vif;
	const stwuct cfg80211_bitwate_mask *mask;
};

static void wtw_wa_mask_info_update_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw_itew_bitwate_mask_data *bw_data = data;
	stwuct wtw_sta_info *si = (stwuct wtw_sta_info *)sta->dwv_pwiv;

	if (si->vif != bw_data->vif)
		wetuwn;

	/* fwee pwevious mask setting */
	kfwee(si->mask);
	si->mask = kmemdup(bw_data->mask, sizeof(stwuct cfg80211_bitwate_mask),
			   GFP_ATOMIC);
	if (!si->mask) {
		si->use_cfg_mask = fawse;
		wetuwn;
	}

	si->use_cfg_mask = twue;
	wtw_update_sta_info(bw_data->wtwdev, si, twue);
}

static void wtw_wa_mask_info_update(stwuct wtw_dev *wtwdev,
				    stwuct ieee80211_vif *vif,
				    const stwuct cfg80211_bitwate_mask *mask)
{
	stwuct wtw_itew_bitwate_mask_data bw_data;

	bw_data.wtwdev = wtwdev;
	bw_data.vif = vif;
	bw_data.mask = mask;
	wtw_itewate_stas(wtwdev, wtw_wa_mask_info_update_itew, &bw_data);
}

static int wtw_ops_set_bitwate_mask(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    const stwuct cfg80211_bitwate_mask *mask)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_wa_mask_info_update(wtwdev, vif, mask);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static int wtw_ops_set_antenna(stwuct ieee80211_hw *hw,
			       u32 tx_antenna,
			       u32 wx_antenna)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	int wet;

	if (!chip->ops->set_antenna)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&wtwdev->mutex);
	wet = chip->ops->set_antenna(wtwdev, tx_antenna, wx_antenna);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static int wtw_ops_get_antenna(stwuct ieee80211_hw *hw,
			       u32 *tx_antenna,
			       u32 *wx_antenna)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_haw *haw = &wtwdev->haw;

	*tx_antenna = haw->antenna_tx;
	*wx_antenna = haw->antenna_wx;

	wetuwn 0;
}

#ifdef CONFIG_PM
static int wtw_ops_suspend(stwuct ieee80211_hw *hw,
			   stwuct cfg80211_wowwan *wowwan)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	int wet;

	mutex_wock(&wtwdev->mutex);
	wet = wtw_wow_suspend(wtwdev, wowwan);
	if (wet)
		wtw_eww(wtwdev, "faiwed to suspend fow wow %d\n", wet);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet ? 1 : 0;
}

static int wtw_ops_wesume(stwuct ieee80211_hw *hw)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	int wet;

	mutex_wock(&wtwdev->mutex);
	wet = wtw_wow_wesume(wtwdev);
	if (wet)
		wtw_eww(wtwdev, "faiwed to wesume fow wow %d\n", wet);
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet ? 1 : 0;
}

static void wtw_ops_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	device_set_wakeup_enabwe(wtwdev->dev, enabwed);
}
#endif

static void wtw_weconfig_compwete(stwuct ieee80211_hw *hw,
				  enum ieee80211_weconfig_type weconfig_type)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	if (weconfig_type == IEEE80211_WECONFIG_TYPE_WESTAWT)
		cweaw_bit(WTW_FWAG_WESTAWTING, wtwdev->fwags);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw_ops_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_scan_wequest *weq)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	int wet;

	if (!wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_SCAN_OFFWOAD))
		wetuwn 1;

	if (test_bit(WTW_FWAG_SCANNING, wtwdev->fwags))
		wetuwn -EBUSY;

	mutex_wock(&wtwdev->mutex);
	wtw_hw_scan_stawt(wtwdev, vif, weq);
	wet = wtw_hw_scan_offwoad(wtwdev, vif, twue);
	if (wet) {
		wtw_hw_scan_abowt(wtwdev);
		wtw_eww(wtwdev, "HW scan faiwed with status: %d\n", wet);
	}
	mutex_unwock(&wtwdev->mutex);

	wetuwn wet;
}

static void wtw_ops_cancew_hw_scan(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	if (!wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_SCAN_OFFWOAD))
		wetuwn;

	if (!test_bit(WTW_FWAG_SCANNING, wtwdev->fwags))
		wetuwn;

	mutex_wock(&wtwdev->mutex);
	wtw_hw_scan_abowt(wtwdev);
	mutex_unwock(&wtwdev->mutex);
}

static int wtw_ops_set_saw_specs(stwuct ieee80211_hw *hw,
				 const stwuct cfg80211_saw_specs *saw)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw_set_saw_specs(wtwdev, saw);
	mutex_unwock(&wtwdev->mutex);

	wetuwn 0;
}

static void wtw_ops_sta_wc_update(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_sta *sta, u32 changed)
{
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_sta_info *si = (stwuct wtw_sta_info *)sta->dwv_pwiv;

	if (changed & IEEE80211_WC_BW_CHANGED)
		ieee80211_queue_wowk(wtwdev->hw, &si->wc_wowk);
}

const stwuct ieee80211_ops wtw_ops = {
	.tx			= wtw_ops_tx,
	.wake_tx_queue		= wtw_ops_wake_tx_queue,
	.stawt			= wtw_ops_stawt,
	.stop			= wtw_ops_stop,
	.config			= wtw_ops_config,
	.add_intewface		= wtw_ops_add_intewface,
	.wemove_intewface	= wtw_ops_wemove_intewface,
	.change_intewface	= wtw_ops_change_intewface,
	.configuwe_fiwtew	= wtw_ops_configuwe_fiwtew,
	.bss_info_changed	= wtw_ops_bss_info_changed,
	.stawt_ap		= wtw_ops_stawt_ap,
	.stop_ap		= wtw_ops_stop_ap,
	.conf_tx		= wtw_ops_conf_tx,
	.sta_add		= wtw_ops_sta_add,
	.sta_wemove		= wtw_ops_sta_wemove,
	.set_tim		= wtw_ops_set_tim,
	.set_key		= wtw_ops_set_key,
	.ampdu_action		= wtw_ops_ampdu_action,
	.can_aggwegate_in_amsdu	= wtw_ops_can_aggwegate_in_amsdu,
	.sw_scan_stawt		= wtw_ops_sw_scan_stawt,
	.sw_scan_compwete	= wtw_ops_sw_scan_compwete,
	.mgd_pwepawe_tx		= wtw_ops_mgd_pwepawe_tx,
	.set_wts_thweshowd	= wtw_ops_set_wts_thweshowd,
	.sta_statistics		= wtw_ops_sta_statistics,
	.fwush			= wtw_ops_fwush,
	.set_bitwate_mask	= wtw_ops_set_bitwate_mask,
	.set_antenna		= wtw_ops_set_antenna,
	.get_antenna		= wtw_ops_get_antenna,
	.weconfig_compwete	= wtw_weconfig_compwete,
	.hw_scan		= wtw_ops_hw_scan,
	.cancew_hw_scan		= wtw_ops_cancew_hw_scan,
	.sta_wc_update		= wtw_ops_sta_wc_update,
	.set_saw_specs          = wtw_ops_set_saw_specs,
#ifdef CONFIG_PM
	.suspend		= wtw_ops_suspend,
	.wesume			= wtw_ops_wesume,
	.set_wakeup		= wtw_ops_set_wakeup,
#endif
};
EXPOWT_SYMBOW(wtw_ops);
