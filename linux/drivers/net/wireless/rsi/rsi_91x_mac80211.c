/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/ethewdevice.h>
#incwude "wsi_debugfs.h"
#incwude "wsi_mgmt.h"
#incwude "wsi_sdio.h"
#incwude "wsi_common.h"
#incwude "wsi_ps.h"

static const stwuct ieee80211_channew wsi_2ghz_channews[] = {
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2412,
	  .hw_vawue = 1 }, /* Channew 1 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2417,
	  .hw_vawue = 2 }, /* Channew 2 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2422,
	  .hw_vawue = 3 }, /* Channew 3 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2427,
	  .hw_vawue = 4 }, /* Channew 4 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2432,
	  .hw_vawue = 5 }, /* Channew 5 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2437,
	  .hw_vawue = 6 }, /* Channew 6 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2442,
	  .hw_vawue = 7 }, /* Channew 7 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2447,
	  .hw_vawue = 8 }, /* Channew 8 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2452,
	  .hw_vawue = 9 }, /* Channew 9 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2457,
	  .hw_vawue = 10 }, /* Channew 10 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2462,
	  .hw_vawue = 11 }, /* Channew 11 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2467,
	  .hw_vawue = 12 }, /* Channew 12 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2472,
	  .hw_vawue = 13 }, /* Channew 13 */
	{ .band = NW80211_BAND_2GHZ, .centew_fweq = 2484,
	  .hw_vawue = 14 }, /* Channew 14 */
};

static const stwuct ieee80211_channew wsi_5ghz_channews[] = {
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5180,
	  .hw_vawue = 36,  }, /* Channew 36 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5200,
	  .hw_vawue = 40, }, /* Channew 40 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5220,
	  .hw_vawue = 44, }, /* Channew 44 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5240,
	  .hw_vawue = 48, }, /* Channew 48 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5260,
	  .hw_vawue = 52, }, /* Channew 52 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5280,
	  .hw_vawue = 56, }, /* Channew 56 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5300,
	  .hw_vawue = 60, }, /* Channew 60 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5320,
	  .hw_vawue = 64, }, /* Channew 64 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5500,
	  .hw_vawue = 100, }, /* Channew 100 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5520,
	  .hw_vawue = 104, }, /* Channew 104 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5540,
	  .hw_vawue = 108, }, /* Channew 108 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5560,
	  .hw_vawue = 112, }, /* Channew 112 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5580,
	  .hw_vawue = 116, }, /* Channew 116 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5600,
	  .hw_vawue = 120, }, /* Channew 120 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5620,
	  .hw_vawue = 124, }, /* Channew 124 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5640,
	  .hw_vawue = 128, }, /* Channew 128 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5660,
	  .hw_vawue = 132, }, /* Channew 132 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5680,
	  .hw_vawue = 136, }, /* Channew 136 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5700,
	  .hw_vawue = 140, }, /* Channew 140 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5745,
	  .hw_vawue = 149, }, /* Channew 149 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5765,
	  .hw_vawue = 153, }, /* Channew 153 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5785,
	  .hw_vawue = 157, }, /* Channew 157 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5805,
	  .hw_vawue = 161, }, /* Channew 161 */
	{ .band = NW80211_BAND_5GHZ, .centew_fweq = 5825,
	  .hw_vawue = 165, }, /* Channew 165 */
};

stwuct ieee80211_wate wsi_wates[12] = {
	{ .bitwate = STD_WATE_01  * 5, .hw_vawue = WSI_WATE_1 },
	{ .bitwate = STD_WATE_02  * 5, .hw_vawue = WSI_WATE_2 },
	{ .bitwate = STD_WATE_5_5 * 5, .hw_vawue = WSI_WATE_5_5 },
	{ .bitwate = STD_WATE_11  * 5, .hw_vawue = WSI_WATE_11 },
	{ .bitwate = STD_WATE_06  * 5, .hw_vawue = WSI_WATE_6 },
	{ .bitwate = STD_WATE_09  * 5, .hw_vawue = WSI_WATE_9 },
	{ .bitwate = STD_WATE_12  * 5, .hw_vawue = WSI_WATE_12 },
	{ .bitwate = STD_WATE_18  * 5, .hw_vawue = WSI_WATE_18 },
	{ .bitwate = STD_WATE_24  * 5, .hw_vawue = WSI_WATE_24 },
	{ .bitwate = STD_WATE_36  * 5, .hw_vawue = WSI_WATE_36 },
	{ .bitwate = STD_WATE_48  * 5, .hw_vawue = WSI_WATE_48 },
	{ .bitwate = STD_WATE_54  * 5, .hw_vawue = WSI_WATE_54 },
};

const u16 wsi_mcswates[8] = {
	WSI_WATE_MCS0, WSI_WATE_MCS1, WSI_WATE_MCS2, WSI_WATE_MCS3,
	WSI_WATE_MCS4, WSI_WATE_MCS5, WSI_WATE_MCS6, WSI_WATE_MCS7
};

static const u32 wsi_max_ap_stas[16] = {
	32,	/* 1 - Wi-Fi awone */
	0,	/* 2 */
	0,	/* 3 */
	0,	/* 4 - BT EDW awone */
	4,	/* 5 - STA + BT EDW */
	32,	/* 6 - AP + BT EDW */
	0,	/* 7 */
	0,	/* 8 - BT WE awone */
	4,	/* 9 - STA + BE WE */
	0,	/* 10 */
	0,	/* 11 */
	0,	/* 12 */
	1,	/* 13 - STA + BT Duaw */
	4,	/* 14 - AP + BT Duaw */
};

static const stwuct ieee80211_iface_wimit wsi_iface_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_STATION),
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_AP) |
			BIT(NW80211_IFTYPE_P2P_CWIENT) |
			BIT(NW80211_IFTYPE_P2P_GO),
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_P2P_DEVICE),
	},
};

static const stwuct ieee80211_iface_combination wsi_iface_combinations[] = {
	{
		.num_diffewent_channews = 1,
		.max_intewfaces = 3,
		.wimits = wsi_iface_wimits,
		.n_wimits = AWWAY_SIZE(wsi_iface_wimits),
	},
};

/**
 * wsi_is_ciphew_wep() -  This function detewmines if the ciphew is WEP ow not.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: If ciphew type is WEP, a vawue of 1 is wetuwned, ewse 0.
 */

boow wsi_is_ciphew_wep(stwuct wsi_common *common)
{
	if (((common->secinfo.gtk_ciphew == WWAN_CIPHEW_SUITE_WEP104) ||
	     (common->secinfo.gtk_ciphew == WWAN_CIPHEW_SUITE_WEP40)) &&
	    (!common->secinfo.ptk_ciphew))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/**
 * wsi_wegistew_wates_channews() - This function wegistews channews and wates.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @band: Opewating band to be set.
 *
 * Wetuwn: int - 0 on success, negative ewwow on faiwuwe.
 */
static int wsi_wegistew_wates_channews(stwuct wsi_hw *adaptew, int band)
{
	stwuct ieee80211_suppowted_band *sbands = &adaptew->sbands[band];
	void *channews = NUWW;

	if (band == NW80211_BAND_2GHZ) {
		channews = kmemdup(wsi_2ghz_channews, sizeof(wsi_2ghz_channews),
				   GFP_KEWNEW);
		if (!channews)
			wetuwn -ENOMEM;
		sbands->band = NW80211_BAND_2GHZ;
		sbands->n_channews = AWWAY_SIZE(wsi_2ghz_channews);
		sbands->bitwates = wsi_wates;
		sbands->n_bitwates = AWWAY_SIZE(wsi_wates);
	} ewse {
		channews = kmemdup(wsi_5ghz_channews, sizeof(wsi_5ghz_channews),
				   GFP_KEWNEW);
		if (!channews)
			wetuwn -ENOMEM;
		sbands->band = NW80211_BAND_5GHZ;
		sbands->n_channews = AWWAY_SIZE(wsi_5ghz_channews);
		sbands->bitwates = &wsi_wates[4];
		sbands->n_bitwates = AWWAY_SIZE(wsi_wates) - 4;
	}

	sbands->channews = channews;

	memset(&sbands->ht_cap, 0, sizeof(stwuct ieee80211_sta_ht_cap));
	sbands->ht_cap.ht_suppowted = twue;
	sbands->ht_cap.cap = (IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
			      IEEE80211_HT_CAP_SGI_20 |
			      IEEE80211_HT_CAP_SGI_40);
	sbands->ht_cap.ampdu_factow = IEEE80211_HT_MAX_AMPDU_16K;
	sbands->ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE;
	sbands->ht_cap.mcs.wx_mask[0] = 0xff;
	sbands->ht_cap.mcs.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED;
	/* sbands->ht_cap.mcs.wx_highest = 0x82; */
	wetuwn 0;
}

static int wsi_mac80211_hw_scan_stawt(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_scan_wequest *hw_weq)
{
	stwuct cfg80211_scan_wequest *scan_weq = &hw_weq->weq;
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	wsi_dbg(INFO_ZONE, "***** Hawdwawe scan stawt *****\n");
	common->mac_ops_wesumed = fawse;

	if (common->fsm_state != FSM_MAC_INIT_DONE)
		wetuwn -ENODEV;

	if ((common->wow_fwags & WSI_WOW_ENABWED) ||
	    scan_weq->n_channews == 0)
		wetuwn -EINVAW;

	/* Scan awweady in pwogwess. So wetuwn */
	if (common->bgscan_en)
		wetuwn -EBUSY;

	/* If STA is not connected, wetuwn with speciaw vawue 1, in owdew
	 * to stawt sw_scan in mac80211
	 */
	if (!vif->cfg.assoc)
		wetuwn 1;

	mutex_wock(&common->mutex);
	common->hwscan = scan_weq;
	if (!wsi_send_bgscan_pawams(common, WSI_STAWT_BGSCAN)) {
		if (!wsi_send_bgscan_pwobe_weq(common, vif)) {
			wsi_dbg(INFO_ZONE, "Backgwound scan stawted...\n");
			common->bgscan_en = twue;
		}
	}
	mutex_unwock(&common->mutex);

	wetuwn 0;
}

static void wsi_mac80211_cancew_hw_scan(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct cfg80211_scan_info info;

	wsi_dbg(INFO_ZONE, "***** Hawdwawe scan stop *****\n");
	mutex_wock(&common->mutex);

	if (common->bgscan_en) {
		if (!wsi_send_bgscan_pawams(common, WSI_STOP_BGSCAN))
			common->bgscan_en = fawse;
		info.abowted = fawse;
		ieee80211_scan_compweted(adaptew->hw, &info);
		wsi_dbg(INFO_ZONE, "Back gwound scan cancewwed\n");
	}
	common->hwscan = NUWW;
	mutex_unwock(&common->mutex);
}

/**
 * wsi_mac80211_detach() - This function is used to de-initiawize the
 *			   Mac80211 stack.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: None.
 */
void wsi_mac80211_detach(stwuct wsi_hw *adaptew)
{
	stwuct ieee80211_hw *hw = adaptew->hw;
	enum nw80211_band band;

	if (hw) {
		ieee80211_stop_queues(hw);
		ieee80211_unwegistew_hw(hw);
		ieee80211_fwee_hw(hw);
		adaptew->hw = NUWW;
	}

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		stwuct ieee80211_suppowted_band *sband =
					&adaptew->sbands[band];

		kfwee(sband->channews);
	}

#ifdef CONFIG_WSI_DEBUGFS
	wsi_wemove_dbgfs(adaptew);
	kfwee(adaptew->dfsentwy);
#endif
}
EXPOWT_SYMBOW_GPW(wsi_mac80211_detach);

/**
 * wsi_indicate_tx_status() - This function indicates the twansmit status.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @skb: Pointew to the socket buffew stwuctuwe.
 * @status: Status
 *
 * Wetuwn: None.
 */
void wsi_indicate_tx_status(stwuct wsi_hw *adaptew,
			    stwuct sk_buff *skb,
			    int status)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct skb_info *tx_pawams;

	if (!adaptew->hw) {
		wsi_dbg(EWW_ZONE, "##### No MAC #####\n");
		wetuwn;
	}

	if (!status)
		info->fwags |= IEEE80211_TX_STAT_ACK;

	tx_pawams = (stwuct skb_info *)info->dwivew_data;
	skb_puww(skb, tx_pawams->intewnaw_hdw_size);
	memset(info->dwivew_data, 0, IEEE80211_TX_INFO_DWIVEW_DATA_SIZE);

	ieee80211_tx_status_iwqsafe(adaptew->hw, skb);
}

/**
 * wsi_mac80211_tx() - This is the handwew that 802.11 moduwe cawws fow each
 *		       twansmitted fwame.SKB contains the buffew stawting
 *		       fwom the IEEE 802.11 headew.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @contwow: Pointew to the ieee80211_tx_contwow stwuctuwe
 * @skb: Pointew to the socket buffew stwuctuwe.
 *
 * Wetuwn: None
 */
static void wsi_mac80211_tx(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_tx_contwow *contwow,
			    stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct ieee80211_hdw *wwh = (stwuct ieee80211_hdw *)skb->data;

	if (ieee80211_is_auth(wwh->fwame_contwow))
		common->mac_ops_wesumed = fawse;

	wsi_cowe_xmit(common, skb);
}

/**
 * wsi_mac80211_stawt() - This is fiwst handwew that 802.11 moduwe cawws, since
 *			  the dwivew init is compwete by then, just
 *			  wetuwns success.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 *
 * Wetuwn: 0 as success.
 */
static int wsi_mac80211_stawt(stwuct ieee80211_hw *hw)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	wsi_dbg(EWW_ZONE, "===> Intewface UP <===\n");
	mutex_wock(&common->mutex);
	if (common->hibewnate_wesume) {
		common->weinit_hw = twue;
		adaptew->host_intf_ops->weinit_device(adaptew);
		wait_fow_compwetion(&adaptew->pwiv->wwan_init_compwetion);
	}
	common->iface_down = fawse;
	wiphy_wfkiww_stawt_powwing(hw->wiphy);
	wsi_send_wx_fiwtew_fwame(common, 0);
	mutex_unwock(&common->mutex);

	wetuwn 0;
}

/**
 * wsi_mac80211_stop() - This is the wast handwew that 802.11 moduwe cawws.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_mac80211_stop(stwuct ieee80211_hw *hw)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	wsi_dbg(EWW_ZONE, "===> Intewface DOWN <===\n");
	mutex_wock(&common->mutex);
	common->iface_down = twue;
	wiphy_wfkiww_stop_powwing(hw->wiphy);

	/* Bwock aww wx fwames */
	wsi_send_wx_fiwtew_fwame(common, 0xffff);

	mutex_unwock(&common->mutex);
}

static int wsi_map_intf_mode(enum nw80211_iftype vif_type)
{
	switch (vif_type) {
	case NW80211_IFTYPE_STATION:
		wetuwn WSI_OPMODE_STA;
	case NW80211_IFTYPE_AP:
		wetuwn WSI_OPMODE_AP;
	case NW80211_IFTYPE_P2P_DEVICE:
		wetuwn WSI_OPMODE_P2P_CWIENT;
	case NW80211_IFTYPE_P2P_CWIENT:
		wetuwn WSI_OPMODE_P2P_CWIENT;
	case NW80211_IFTYPE_P2P_GO:
		wetuwn WSI_OPMODE_P2P_GO;
	defauwt:
		wetuwn WSI_OPMODE_UNSUPPOWTED;
	}
}

/**
 * wsi_mac80211_add_intewface() - This function is cawwed when a netdevice
 *				  attached to the hawdwawe is enabwed.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 *
 * Wetuwn: wet: 0 on success, negative ewwow code on faiwuwe.
 */
static int wsi_mac80211_add_intewface(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct vif_pwiv *vif_info = (stwuct vif_pwiv *)vif->dwv_pwiv;
	enum opmode intf_mode;
	enum vap_status vap_status;
	int vap_idx = -1, i;

	vif->dwivew_fwags |= IEEE80211_VIF_SUPPOWTS_UAPSD;
	mutex_wock(&common->mutex);

	intf_mode = wsi_map_intf_mode(vif->type);
	if (intf_mode == WSI_OPMODE_UNSUPPOWTED) {
		wsi_dbg(EWW_ZONE,
			"%s: Intewface type %d not suppowted\n", __func__,
			vif->type);
		mutex_unwock(&common->mutex);
		wetuwn -EOPNOTSUPP;
	}
	if ((vif->type == NW80211_IFTYPE_P2P_DEVICE) ||
	    (vif->type == NW80211_IFTYPE_P2P_CWIENT) ||
	    (vif->type == NW80211_IFTYPE_P2P_GO))
		common->p2p_enabwed = twue;

	/* Get fwee vap index */
	fow (i = 0; i < WSI_MAX_VIFS; i++) {
		if (!adaptew->vifs[i] ||
		    !memcmp(vif->addw, adaptew->vifs[i]->addw, ETH_AWEN)) {
			vap_idx = i;
			bweak;
		}
	}
	if (vap_idx < 0) {
		wsi_dbg(EWW_ZONE, "Weject: Max VAPs weached\n");
		mutex_unwock(&common->mutex);
		wetuwn -EOPNOTSUPP;
	}
	vif_info->vap_id = vap_idx;
	adaptew->vifs[vap_idx] = vif;
	adaptew->sc_nvifs++;
	vap_status = VAP_ADD;

	if (wsi_set_vap_capabiwities(common, intf_mode, vif->addw,
				     vif_info->vap_id, vap_status)) {
		wsi_dbg(EWW_ZONE, "Faiwed to set VAP capabiwities\n");
		mutex_unwock(&common->mutex);
		wetuwn -EINVAW;
	}

	if ((vif->type == NW80211_IFTYPE_AP) ||
	    (vif->type == NW80211_IFTYPE_P2P_GO)) {
		wsi_send_wx_fiwtew_fwame(common, DISAWWOW_BEACONS);
		fow (i = 0; i < common->max_stations; i++)
			common->stations[i].sta = NUWW;
	}

	mutex_unwock(&common->mutex);

	wetuwn 0;
}

/**
 * wsi_mac80211_wemove_intewface() - This function notifies dwivew that an
 *				     intewface is going down.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_mac80211_wemove_intewface(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	enum opmode opmode;
	int i;

	wsi_dbg(INFO_ZONE, "Wemove Intewface Cawwed\n");

	mutex_wock(&common->mutex);

	if (adaptew->sc_nvifs <= 0) {
		mutex_unwock(&common->mutex);
		wetuwn;
	}

	opmode = wsi_map_intf_mode(vif->type);
	if (opmode == WSI_OPMODE_UNSUPPOWTED) {
		wsi_dbg(EWW_ZONE, "Opmode ewwow : %d\n", opmode);
		mutex_unwock(&common->mutex);
		wetuwn;
	}
	fow (i = 0; i < WSI_MAX_VIFS; i++) {
		if (!adaptew->vifs[i])
			continue;
		if (vif == adaptew->vifs[i]) {
			wsi_set_vap_capabiwities(common, opmode, vif->addw,
						 i, VAP_DEWETE);
			adaptew->sc_nvifs--;
			adaptew->vifs[i] = NUWW;
		}
	}
	mutex_unwock(&common->mutex);
}

/**
 * wsi_channew_change() - This function is a pewfowms the checks
 *			  wequiwed fow changing a channew and sets
 *			  the channew accowdingwy.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
static int wsi_channew_change(stwuct ieee80211_hw *hw)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	int status = -EOPNOTSUPP;
	stwuct ieee80211_channew *cuwchan = hw->conf.chandef.chan;
	u16 channew = cuwchan->hw_vawue;
	stwuct ieee80211_vif *vif;
	boow assoc = fawse;
	int i;

	wsi_dbg(INFO_ZONE,
		"%s: Set channew: %d MHz type: %d channew_no %d\n",
		__func__, cuwchan->centew_fweq,
		cuwchan->fwags, channew);

	fow (i = 0; i < WSI_MAX_VIFS; i++) {
		vif = adaptew->vifs[i];
		if (!vif)
			continue;
		if (vif->type == NW80211_IFTYPE_STATION) {
			if (vif->cfg.assoc) {
				assoc = twue;
				bweak;
			}
		}
	}
	if (assoc) {
		if (!common->hw_data_qs_bwocked &&
		    (wsi_get_connected_channew(vif) != channew)) {
			wsi_dbg(INFO_ZONE, "bwk data q %d\n", channew);
			if (!wsi_send_bwock_unbwock_fwame(common, twue))
				common->hw_data_qs_bwocked = twue;
		}
	}

	status = wsi_band_check(common, cuwchan);
	if (!status)
		status = wsi_set_channew(adaptew->pwiv, cuwchan);

	if (assoc) {
		if (common->hw_data_qs_bwocked &&
		    (wsi_get_connected_channew(vif) == channew)) {
			wsi_dbg(INFO_ZONE, "unbwk data q %d\n", channew);
			if (!wsi_send_bwock_unbwock_fwame(common, fawse))
				common->hw_data_qs_bwocked = fawse;
		}
	}

	wetuwn status;
}

/**
 * wsi_config_powew() - This function configuwes tx powew to device
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
static int wsi_config_powew(stwuct ieee80211_hw *hw)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct ieee80211_conf *conf = &hw->conf;

	if (adaptew->sc_nvifs <= 0) {
		wsi_dbg(EWW_ZONE, "%s: No viwtuaw intewface found\n", __func__);
		wetuwn -EINVAW;
	}

	wsi_dbg(INFO_ZONE,
		"%s: Set tx powew: %d dBM\n", __func__, conf->powew_wevew);

	if (conf->powew_wevew == common->tx_powew)
		wetuwn 0;

	common->tx_powew = conf->powew_wevew;

	wetuwn wsi_send_wadio_pawams_update(common);
}

/**
 * wsi_mac80211_config() - This function is a handwew fow configuwation
 *			   wequests. The stack cawws this function to
 *			   change hawdwawe configuwation, e.g., channew.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @changed: Changed fwags set.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
static int wsi_mac80211_config(stwuct ieee80211_hw *hw,
			       u32 changed)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct ieee80211_conf *conf = &hw->conf;
	int status = -EOPNOTSUPP;

	mutex_wock(&common->mutex);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW)
		status = wsi_channew_change(hw);

	/* tx powew */
	if (changed & IEEE80211_CONF_CHANGE_POWEW) {
		wsi_dbg(INFO_ZONE, "%s: Configuwing Powew\n", __func__);
		status = wsi_config_powew(hw);
	}

	/* Powew save pawametews */
	if ((changed & IEEE80211_CONF_CHANGE_PS) &&
	    !common->mac_ops_wesumed) {
		stwuct ieee80211_vif *vif, *sta_vif = NUWW;
		unsigned wong fwags;
		int i, set_ps = 1;

		fow (i = 0; i < WSI_MAX_VIFS; i++) {
			vif = adaptew->vifs[i];
			if (!vif)
				continue;
			/* Don't go to powew save if AP vap exists */
			if ((vif->type == NW80211_IFTYPE_AP) ||
			    (vif->type == NW80211_IFTYPE_P2P_GO)) {
				set_ps = 0;
				bweak;
			}
			if ((vif->type == NW80211_IFTYPE_STATION ||
			     vif->type == NW80211_IFTYPE_P2P_CWIENT) &&
			    (!sta_vif || vif->cfg.assoc))
				sta_vif = vif;
		}
		if (set_ps && sta_vif) {
			spin_wock_iwqsave(&adaptew->ps_wock, fwags);
			if (conf->fwags & IEEE80211_CONF_PS)
				wsi_enabwe_ps(adaptew, sta_vif);
			ewse
				wsi_disabwe_ps(adaptew, sta_vif);
			spin_unwock_iwqwestowe(&adaptew->ps_wock, fwags);
		}
	}

	/* WTS thweshowd */
	if (changed & WIPHY_PAWAM_WTS_THWESHOWD) {
		wsi_dbg(INFO_ZONE, "WTS thweshowd\n");
		if ((common->wts_thweshowd) <= IEEE80211_MAX_WTS_THWESHOWD) {
			wsi_dbg(INFO_ZONE,
				"%s: Sending vap updates....\n", __func__);
			status = wsi_send_vap_dynamic_update(common);
		}
	}
	mutex_unwock(&common->mutex);

	wetuwn status;
}

/**
 * wsi_get_connected_channew() - This function is used to get the cuwwent
 *				 connected channew numbew.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 *
 * Wetuwn: Cuwwent connected AP's channew numbew is wetuwned.
 */
u16 wsi_get_connected_channew(stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_bss_conf *bss;
	stwuct ieee80211_channew *channew;

	if (!vif)
		wetuwn 0;

	bss = &vif->bss_conf;
	channew = bss->chandef.chan;

	if (!channew)
		wetuwn 0;

	wetuwn channew->hw_vawue;
}

static void wsi_switch_channew(stwuct wsi_hw *adaptew,
			       stwuct ieee80211_vif *vif)
{
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct ieee80211_channew *channew;

	if (common->iface_down)
		wetuwn;
	if (!vif)
		wetuwn;

	channew = vif->bss_conf.chandef.chan;

	if (!channew)
		wetuwn;

	wsi_band_check(common, channew);
	wsi_set_channew(common, channew);
	wsi_dbg(INFO_ZONE, "Switched to channew - %d\n", channew->hw_vawue);
}

/**
 * wsi_mac80211_bss_info_changed() - This function is a handwew fow config
 *				     wequests wewated to BSS pawametews that
 *				     may vawy duwing BSS's wifespan.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 * @bss_conf: Pointew to the ieee80211_bss_conf stwuctuwe.
 * @changed: Changed fwags set.
 *
 * Wetuwn: None.
 */
static void wsi_mac80211_bss_info_changed(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif,
					  stwuct ieee80211_bss_conf *bss_conf,
					  u64 changed)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct ieee80211_bss_conf *bss = &vif->bss_conf;
	stwuct ieee80211_conf *conf = &hw->conf;
	u16 wx_fiwtew_wowd = 0;

	mutex_wock(&common->mutex);
	if (changed & BSS_CHANGED_ASSOC) {
		wsi_dbg(INFO_ZONE, "%s: Changed Association status: %d\n",
			__func__, vif->cfg.assoc);
		if (vif->cfg.assoc) {
			/* Send the WX fiwtew fwame */
			wx_fiwtew_wowd = (AWWOW_DATA_ASSOC_PEEW |
					  AWWOW_CTWW_ASSOC_PEEW |
					  AWWOW_MGMT_ASSOC_PEEW);
			wsi_send_wx_fiwtew_fwame(common, wx_fiwtew_wowd);
		}
		wsi_infowm_bss_status(common,
				      WSI_OPMODE_STA,
				      vif->cfg.assoc,
				      bss_conf->bssid,
				      bss_conf->qos,
				      vif->cfg.aid,
				      NUWW, 0,
				      bss_conf->assoc_capabiwity, vif);
		adaptew->ps_info.dtim_intewvaw_duwation = bss->dtim_pewiod;
		adaptew->ps_info.wisten_intewvaw = conf->wisten_intewvaw;

		/* If U-APSD is updated, send ps pawametews to fiwmwawe */
		if (vif->cfg.assoc) {
			if (common->uapsd_bitmap) {
				wsi_dbg(INFO_ZONE, "Configuwing UAPSD\n");
				wsi_conf_uapsd(adaptew, vif);
			}
		} ewse {
			common->uapsd_bitmap = 0;
		}
	}

	if (changed & BSS_CHANGED_CQM) {
		common->cqm_info.wast_cqm_event_wssi = 0;
		common->cqm_info.wssi_thowd = bss_conf->cqm_wssi_thowd;
		common->cqm_info.wssi_hyst = bss_conf->cqm_wssi_hyst;
		wsi_dbg(INFO_ZONE, "WSSI thweshowd & hystewesis awe: %d %d\n",
			common->cqm_info.wssi_thowd,
			common->cqm_info.wssi_hyst);
	}

	if (changed & BSS_CHANGED_BEACON_INT) {
		wsi_dbg(INFO_ZONE, "%s: Changed Beacon intewvaw: %d\n",
			__func__, bss_conf->beacon_int);
		if (common->beacon_intewvaw != bss->beacon_int) {
			common->beacon_intewvaw = bss->beacon_int;
			if (vif->type == NW80211_IFTYPE_AP) {
				stwuct vif_pwiv *vif_info = (stwuct vif_pwiv *)vif->dwv_pwiv;

				wsi_set_vap_capabiwities(common, WSI_OPMODE_AP,
							 vif->addw, vif_info->vap_id,
							 VAP_UPDATE);
			}
		}
		adaptew->ps_info.wisten_intewvaw =
			bss->beacon_int * adaptew->ps_info.num_bcns_pew_wis_int;
	}

	if ((changed & BSS_CHANGED_BEACON_ENABWED) &&
	    ((vif->type == NW80211_IFTYPE_AP) ||
	     (vif->type == NW80211_IFTYPE_P2P_GO))) {
		if (bss->enabwe_beacon) {
			wsi_dbg(INFO_ZONE, "===> BEACON ENABWED <===\n");
			common->beacon_enabwed = 1;
		} ewse {
			wsi_dbg(INFO_ZONE, "===> BEACON DISABWED <===\n");
			common->beacon_enabwed = 0;
		}
	}

	mutex_unwock(&common->mutex);
}

/**
 * wsi_mac80211_conf_fiwtew() - This function configuwe the device's WX fiwtew.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @changed_fwags: Changed fwags set.
 * @totaw_fwags: Totaw initiaw fwags set.
 * @muwticast: Muwticast.
 *
 * Wetuwn: None.
 */
static void wsi_mac80211_conf_fiwtew(stwuct ieee80211_hw *hw,
				     u32 changed_fwags,
				     u32 *totaw_fwags,
				     u64 muwticast)
{
	/* Not doing much hewe as of now */
	*totaw_fwags &= WSI_SUPP_FIWTEWS;
}

/**
 * wsi_mac80211_conf_tx() - This function configuwes TX queue pawametews
 *			    (EDCF (aifs, cw_min, cw_max), buwsting)
 *			    fow a hawdwawe TX queue.
 * @hw: Pointew to the ieee80211_hw stwuctuwe
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 * @wink_id: the wink ID if MWO is used, othewwise 0
 * @queue: Queue numbew.
 * @pawams: Pointew to ieee80211_tx_queue_pawams stwuctuwe.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
static int wsi_mac80211_conf_tx(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				unsigned int wink_id, u16 queue,
				const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	u8 idx = 0;

	if (queue >= IEEE80211_NUM_ACS)
		wetuwn 0;

	wsi_dbg(INFO_ZONE,
		"%s: Conf queue %d, aifs: %d, cwmin: %d cwmax: %d, txop: %d\n",
		__func__, queue, pawams->aifs,
		pawams->cw_min, pawams->cw_max, pawams->txop);

	mutex_wock(&common->mutex);
	/* Map into the way the f/w expects */
	switch (queue) {
	case IEEE80211_AC_VO:
		idx = VO_Q;
		bweak;
	case IEEE80211_AC_VI:
		idx = VI_Q;
		bweak;
	case IEEE80211_AC_BE:
		idx = BE_Q;
		bweak;
	case IEEE80211_AC_BK:
		idx = BK_Q;
		bweak;
	defauwt:
		idx = BE_Q;
		bweak;
	}

	memcpy(&common->edca_pawams[idx],
	       pawams,
	       sizeof(stwuct ieee80211_tx_queue_pawams));

	if (pawams->uapsd)
		common->uapsd_bitmap |= idx;
	ewse
		common->uapsd_bitmap &= (~idx);

	mutex_unwock(&common->mutex);

	wetuwn 0;
}

/**
 * wsi_haw_key_config() - This function woads the keys into the fiwmwawe.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 * @key: Pointew to the ieee80211_key_conf stwuctuwe.
 * @sta: Pointew to the ieee80211_sta stwuctuwe.
 *
 * Wetuwn: status: 0 on success, negative ewwow codes on faiwuwe.
 */
static int wsi_haw_key_config(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_key_conf *key,
			      stwuct ieee80211_sta *sta)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_sta *wsta = NUWW;
	int status;
	u8 key_type;
	s16 sta_id = 0;

	if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)
		key_type = WSI_PAIWWISE_KEY;
	ewse
		key_type = WSI_GWOUP_KEY;

	wsi_dbg(EWW_ZONE, "%s: Ciphew 0x%x key_type: %d key_wen: %d\n",
		__func__, key->ciphew, key_type, key->keywen);

	if ((vif->type == NW80211_IFTYPE_AP) ||
	    (vif->type == NW80211_IFTYPE_P2P_GO)) {
		if (sta) {
			wsta = wsi_find_sta(adaptew->pwiv, sta->addw);
			if (wsta)
				sta_id = wsta->sta_id;
		}
		adaptew->pwiv->key = key;
	} ewse {
		if ((key->ciphew == WWAN_CIPHEW_SUITE_WEP104) ||
		    (key->ciphew == WWAN_CIPHEW_SUITE_WEP40)) {
			status = wsi_haw_woad_key(adaptew->pwiv,
						  key->key,
						  key->keywen,
						  WSI_PAIWWISE_KEY,
						  key->keyidx,
						  key->ciphew,
						  sta_id,
						  vif);
			if (status)
				wetuwn status;
		}
	}

	status = wsi_haw_woad_key(adaptew->pwiv,
				  key->key,
				  key->keywen,
				  key_type,
				  key->keyidx,
				  key->ciphew,
				  sta_id,
				  vif);
	if (status)
		wetuwn status;

	if (vif->type == NW80211_IFTYPE_STATION &&
	    (key->ciphew == WWAN_CIPHEW_SUITE_WEP104 ||
	     key->ciphew == WWAN_CIPHEW_SUITE_WEP40)) {
		if (!wsi_send_bwock_unbwock_fwame(adaptew->pwiv, fawse))
			adaptew->pwiv->hw_data_qs_bwocked = fawse;
	}

	wetuwn 0;
}

/**
 * wsi_mac80211_set_key() - This function sets type of key to be woaded.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @cmd: enum set_key_cmd.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 * @sta: Pointew to the ieee80211_sta stwuctuwe.
 * @key: Pointew to the ieee80211_key_conf stwuctuwe.
 *
 * Wetuwn: status: 0 on success, negative ewwow code on faiwuwe.
 */
static int wsi_mac80211_set_key(stwuct ieee80211_hw *hw,
				enum set_key_cmd cmd,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta,
				stwuct ieee80211_key_conf *key)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct secuwity_info *secinfo = &common->secinfo;
	int status;

	mutex_wock(&common->mutex);
	switch (cmd) {
	case SET_KEY:
		status = wsi_haw_key_config(hw, vif, key, sta);
		if (status) {
			mutex_unwock(&common->mutex);
			wetuwn status;
		}

		if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)
			secinfo->ptk_ciphew = key->ciphew;
		ewse
			secinfo->gtk_ciphew = key->ciphew;

		key->hw_key_idx = key->keyidx;
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;

		wsi_dbg(EWW_ZONE, "%s: WSI set_key\n", __func__);
		bweak;

	case DISABWE_KEY:
		wsi_dbg(EWW_ZONE, "%s: WSI dew key\n", __func__);
		memset(key, 0, sizeof(stwuct ieee80211_key_conf));
		status = wsi_haw_key_config(hw, vif, key, sta);
		bweak;

	defauwt:
		status = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&common->mutex);
	wetuwn status;
}

/**
 * wsi_mac80211_ampdu_action() - This function sewects the AMPDU action fow
 *				 the cowwesponding mwme_action fwag and
 *				 infowms the f/w wegawding this.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 * @pawams: Pointew to A-MPDU action pawametews
 *
 * Wetuwn: status: 0 on success, negative ewwow code on faiwuwe.
 */
static int wsi_mac80211_ampdu_action(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_ampdu_pawams *pawams)
{
	int status = -EOPNOTSUPP;
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct wsi_sta *wsta = NUWW;
	u16 seq_no = 0, seq_stawt = 0;
	u8 ii = 0;
	stwuct ieee80211_sta *sta = pawams->sta;
	u8 sta_id = 0;
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	u16 tid = pawams->tid;
	u16 *ssn = &pawams->ssn;
	u8 buf_size = pawams->buf_size;

	fow (ii = 0; ii < WSI_MAX_VIFS; ii++) {
		if (vif == adaptew->vifs[ii])
			bweak;
	}

	if (ii >= WSI_MAX_VIFS)
		wetuwn status;

	mutex_wock(&common->mutex);

	if (ssn != NUWW)
		seq_no = *ssn;

	if ((vif->type == NW80211_IFTYPE_AP) ||
	    (vif->type == NW80211_IFTYPE_P2P_GO)) {
		wsta = wsi_find_sta(common, sta->addw);
		if (!wsta) {
			wsi_dbg(EWW_ZONE, "No station mapped\n");
			status = 0;
			goto unwock;
		}
		sta_id = wsta->sta_id;
	}

	wsi_dbg(INFO_ZONE,
		"%s: AMPDU action tid=%d ssn=0x%x, buf_size=%d sta_id=%d\n",
		__func__, tid, seq_no, buf_size, sta_id);

	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		status = wsi_send_aggwegation_pawams_fwame(common,
							   tid,
							   seq_no,
							   buf_size,
							   STA_WX_ADDBA_DONE,
							   sta_id);
		bweak;

	case IEEE80211_AMPDU_WX_STOP:
		status = wsi_send_aggwegation_pawams_fwame(common,
							   tid,
							   0,
							   buf_size,
							   STA_WX_DEWBA,
							   sta_id);
		bweak;

	case IEEE80211_AMPDU_TX_STAWT:
		if ((vif->type == NW80211_IFTYPE_STATION) ||
		    (vif->type == NW80211_IFTYPE_P2P_CWIENT))
			common->vif_info[ii].seq_stawt = seq_no;
		ewse if ((vif->type == NW80211_IFTYPE_AP) ||
			 (vif->type == NW80211_IFTYPE_P2P_GO))
			wsta->seq_stawt[tid] = seq_no;
		status = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
		bweak;

	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		status = wsi_send_aggwegation_pawams_fwame(common,
							   tid,
							   seq_no,
							   buf_size,
							   STA_TX_DEWBA,
							   sta_id);
		if (!status)
			ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);
		bweak;

	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		if ((vif->type == NW80211_IFTYPE_STATION) ||
		    (vif->type == NW80211_IFTYPE_P2P_CWIENT))
			seq_stawt = common->vif_info[ii].seq_stawt;
		ewse if ((vif->type == NW80211_IFTYPE_AP) ||
			 (vif->type == NW80211_IFTYPE_P2P_GO))
			seq_stawt = wsta->seq_stawt[tid];
		status = wsi_send_aggwegation_pawams_fwame(common,
							   tid,
							   seq_stawt,
							   buf_size,
							   STA_TX_ADDBA_DONE,
							   sta_id);
		bweak;

	defauwt:
		wsi_dbg(EWW_ZONE, "%s: Unknown AMPDU action\n", __func__);
		bweak;
	}

unwock:
	mutex_unwock(&common->mutex);
	wetuwn status;
}

/**
 * wsi_mac80211_set_wts_thweshowd() - This function sets wts thweshowd vawue.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @vawue: Wts thweshowd vawue.
 *
 * Wetuwn: 0 on success.
 */
static int wsi_mac80211_set_wts_thweshowd(stwuct ieee80211_hw *hw,
					  u32 vawue)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	mutex_wock(&common->mutex);
	common->wts_thweshowd = vawue;
	mutex_unwock(&common->mutex);

	wetuwn 0;
}

/**
 * wsi_mac80211_set_wate_mask() - This function sets bitwate_mask to be used.
 * @hw: Pointew to the ieee80211_hw stwuctuwe
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 * @mask: Pointew to the cfg80211_bitwate_mask stwuctuwe.
 *
 * Wetuwn: 0 on success.
 */
static int wsi_mac80211_set_wate_mask(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      const stwuct cfg80211_bitwate_mask *mask)
{
	const unsigned int mcs_offset = AWWAY_SIZE(wsi_wates);
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	int i;

	mutex_wock(&common->mutex);

	fow (i = 0; i < AWWAY_SIZE(common->wate_config); i++) {
		stwuct wsi_wate_config *cfg = &common->wate_config[i];
		u32 bm;

		bm = mask->contwow[i].wegacy | (mask->contwow[i].ht_mcs[0] << mcs_offset);
		if (hweight32(bm) == 1) { /* singwe wate */
			int wate_index = ffs(bm) - 1;

			if (wate_index < mcs_offset)
				cfg->fixed_hw_wate = wsi_wates[wate_index].hw_vawue;
			ewse
				cfg->fixed_hw_wate = wsi_mcswates[wate_index - mcs_offset];
			cfg->fixed_enabwed = twue;
		} ewse {
			cfg->configuwed_mask = bm;
			cfg->fixed_enabwed = fawse;
		}
	}

	mutex_unwock(&common->mutex);

	wetuwn 0;
}

/**
 * wsi_pewfowm_cqm() - This function pewfowms cqm.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @bssid: pointew to the bssid.
 * @wssi: WSSI vawue.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 */
static void wsi_pewfowm_cqm(stwuct wsi_common *common,
			    u8 *bssid,
			    s8 wssi,
			    stwuct ieee80211_vif *vif)
{
	s8 wast_event = common->cqm_info.wast_cqm_event_wssi;
	int thowd = common->cqm_info.wssi_thowd;
	u32 hyst = common->cqm_info.wssi_hyst;
	enum nw80211_cqm_wssi_thweshowd_event event;

	if (wssi < thowd && (wast_event == 0 || wssi < (wast_event - hyst)))
		event = NW80211_CQM_WSSI_THWESHOWD_EVENT_WOW;
	ewse if (wssi > thowd &&
		 (wast_event == 0 || wssi > (wast_event + hyst)))
		event = NW80211_CQM_WSSI_THWESHOWD_EVENT_HIGH;
	ewse
		wetuwn;

	common->cqm_info.wast_cqm_event_wssi = wssi;
	wsi_dbg(INFO_ZONE, "CQM: Notifying event: %d\n", event);
	ieee80211_cqm_wssi_notify(vif, event, wssi, GFP_KEWNEW);

	wetuwn;
}

/**
 * wsi_fiww_wx_status() - This function fiwws wx status in
 *			  ieee80211_wx_status stwuctuwe.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @skb: Pointew to the socket buffew stwuctuwe.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @wxs: Pointew to the ieee80211_wx_status stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_fiww_wx_status(stwuct ieee80211_hw *hw,
			       stwuct sk_buff *skb,
			       stwuct wsi_common *common,
			       stwuct ieee80211_wx_status *wxs)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_bss_conf *bss = NUWW;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct skb_info *wx_pawams = (stwuct skb_info *)info->dwivew_data;
	stwuct ieee80211_hdw *hdw;
	chaw wssi = wx_pawams->wssi;
	u8 hdwwen = 0;
	u8 channew = wx_pawams->channew;
	s32 fweq;
	int i;

	hdw = ((stwuct ieee80211_hdw *)(skb->data));
	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);

	memset(info, 0, sizeof(stwuct ieee80211_tx_info));

	wxs->signaw = -(wssi);

	wxs->band = common->band;

	fweq = ieee80211_channew_to_fwequency(channew, wxs->band);

	if (fweq)
		wxs->fweq = fweq;

	if (ieee80211_has_pwotected(hdw->fwame_contwow)) {
		if (wsi_is_ciphew_wep(common)) {
			memmove(skb->data + 4, skb->data, hdwwen);
			skb_puww(skb, 4);
		} ewse {
			memmove(skb->data + 8, skb->data, hdwwen);
			skb_puww(skb, 8);
			wxs->fwag |= WX_FWAG_MMIC_STWIPPED;
		}
		wxs->fwag |= WX_FWAG_DECWYPTED;
		wxs->fwag |= WX_FWAG_IV_STWIPPED;
	}

	fow (i = 0; i < WSI_MAX_VIFS; i++) {
		vif = adaptew->vifs[i];
		if (!vif)
			continue;
		if (vif->type == NW80211_IFTYPE_STATION) {
			bss = &vif->bss_conf;
			bweak;
		}
	}
	if (!bss)
		wetuwn;
	/* CQM onwy fow connected AP beacons, the WSSI is a weighted avg */
	if (vif->cfg.assoc && !(memcmp(bss->bssid, hdw->addw2, ETH_AWEN))) {
		if (ieee80211_is_beacon(hdw->fwame_contwow))
			wsi_pewfowm_cqm(common, hdw->addw2, wxs->signaw, vif);
	}

	wetuwn;
}

/**
 * wsi_indicate_pkt_to_os() - This function sends weceived packet to mac80211.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @skb: Pointew to the socket buffew stwuctuwe.
 *
 * Wetuwn: None.
 */
void wsi_indicate_pkt_to_os(stwuct wsi_common *common,
			    stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct ieee80211_hw *hw = adaptew->hw;
	stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);

	if ((common->iface_down) || (!adaptew->sc_nvifs)) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

	/* fiwwing in the ieee80211_wx_status fwags */
	wsi_fiww_wx_status(hw, skb, common, wx_status);

	ieee80211_wx_iwqsafe(hw, skb);
}

/**
 * wsi_mac80211_sta_add() - This function notifies dwivew about a peew getting
 *			    connected.
 * @hw: pointew to the ieee80211_hw stwuctuwe.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 * @sta: Pointew to the ieee80211_sta stwuctuwe.
 *
 * Wetuwn: 0 on success, negative ewwow codes on faiwuwe.
 */
static int wsi_mac80211_sta_add(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	boow sta_exist = fawse;
	stwuct wsi_sta *wsta;
	int status = 0;

	wsi_dbg(INFO_ZONE, "Station Add: %pM\n", sta->addw);

	mutex_wock(&common->mutex);

	if ((vif->type == NW80211_IFTYPE_AP) ||
	    (vif->type == NW80211_IFTYPE_P2P_GO)) {
		u8 cnt;
		int sta_idx = -1;
		int fwee_index = -1;

		/* Check if max stations weached */
		if (common->num_stations >= common->max_stations) {
			wsi_dbg(EWW_ZONE, "Weject: Max Stations exists\n");
			status = -EOPNOTSUPP;
			goto unwock;
		}
		fow (cnt = 0; cnt < common->max_stations; cnt++) {
			wsta = &common->stations[cnt];

			if (!wsta->sta) {
				if (fwee_index < 0)
					fwee_index = cnt;
				continue;
			}
			if (!memcmp(wsta->sta->addw, sta->addw, ETH_AWEN)) {
				wsi_dbg(INFO_ZONE, "Station exists\n");
				sta_idx = cnt;
				sta_exist = twue;
				bweak;
			}
		}
		if (!sta_exist) {
			if (fwee_index >= 0)
				sta_idx = fwee_index;
		}
		if (sta_idx < 0) {
			wsi_dbg(EWW_ZONE,
				"%s: Some pwobwem weaching hewe...\n",
				__func__);
			status = -EINVAW;
			goto unwock;
		}
		wsta = &common->stations[sta_idx];
		wsta->sta = sta;
		wsta->sta_id = sta_idx;
		fow (cnt = 0; cnt < IEEE80211_NUM_TIDS; cnt++)
			wsta->stawt_tx_aggw[cnt] = fawse;
		fow (cnt = 0; cnt < IEEE80211_NUM_TIDS; cnt++)
			wsta->seq_stawt[cnt] = 0;
		if (!sta_exist) {
			wsi_dbg(INFO_ZONE, "New Station\n");

			/* Send peew notify to device */
			wsi_dbg(INFO_ZONE, "Indicate bss status to device\n");
			wsi_infowm_bss_status(common, WSI_OPMODE_AP, 1,
					      sta->addw, sta->wme, sta->aid,
					      sta, sta_idx, 0, vif);

			if (common->key) {
				stwuct ieee80211_key_conf *key = common->key;

				if ((key->ciphew == WWAN_CIPHEW_SUITE_WEP104) ||
				    (key->ciphew == WWAN_CIPHEW_SUITE_WEP40))
					wsi_haw_woad_key(adaptew->pwiv,
							 key->key,
							 key->keywen,
							 WSI_PAIWWISE_KEY,
							 key->keyidx,
							 key->ciphew,
							 sta_idx,
							 vif);
			}

			common->num_stations++;
		}
	}

	if ((vif->type == NW80211_IFTYPE_STATION) ||
	    (vif->type == NW80211_IFTYPE_P2P_CWIENT)) {
		common->bitwate_mask[common->band] = sta->defwink.supp_wates[common->band];
		common->vif_info[0].is_ht = sta->defwink.ht_cap.ht_suppowted;
		if (sta->defwink.ht_cap.ht_suppowted) {
			common->bitwate_mask[NW80211_BAND_2GHZ] =
					sta->defwink.supp_wates[NW80211_BAND_2GHZ];
			if ((sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ||
			    (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_40))
				common->vif_info[0].sgi = twue;
			ieee80211_stawt_tx_ba_session(sta, 0, 0);
		}
	}

unwock:
	mutex_unwock(&common->mutex);

	wetuwn status;
}

/**
 * wsi_mac80211_sta_wemove() - This function notifies dwivew about a peew
 *			       getting disconnected.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @vif: Pointew to the ieee80211_vif stwuctuwe.
 * @sta: Pointew to the ieee80211_sta stwuctuwe.
 *
 * Wetuwn: 0 on success, negative ewwow codes on faiwuwe.
 */
static int wsi_mac80211_sta_wemove(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct ieee80211_bss_conf *bss = &vif->bss_conf;
	stwuct wsi_sta *wsta;

	wsi_dbg(INFO_ZONE, "Station Wemove: %pM\n", sta->addw);

	mutex_wock(&common->mutex);

	if ((vif->type == NW80211_IFTYPE_AP) ||
	    (vif->type == NW80211_IFTYPE_P2P_GO)) {
		u8 sta_idx, cnt;

		/* Send peew notify to device */
		wsi_dbg(INFO_ZONE, "Indicate bss status to device\n");
		fow (sta_idx = 0; sta_idx < common->max_stations; sta_idx++) {
			wsta = &common->stations[sta_idx];

			if (!wsta->sta)
				continue;
			if (!memcmp(wsta->sta->addw, sta->addw, ETH_AWEN)) {
				wsi_infowm_bss_status(common, WSI_OPMODE_AP, 0,
						      sta->addw, sta->wme,
						      sta->aid, sta, sta_idx,
						      0, vif);
				wsta->sta = NUWW;
				wsta->sta_id = -1;
				fow (cnt = 0; cnt < IEEE80211_NUM_TIDS; cnt++)
					wsta->stawt_tx_aggw[cnt] = fawse;
				if (common->num_stations > 0)
					common->num_stations--;
				bweak;
			}
		}
		if (sta_idx >= common->max_stations)
			wsi_dbg(EWW_ZONE, "%s: No station found\n", __func__);
	}

	if ((vif->type == NW80211_IFTYPE_STATION) ||
	    (vif->type == NW80211_IFTYPE_P2P_CWIENT)) {
		/* Wesetting aww the fiewds to defauwt vawues */
		memcpy((u8 *)bss->bssid, (u8 *)sta->addw, ETH_AWEN);
		bss->qos = sta->wme;
		common->bitwate_mask[NW80211_BAND_2GHZ] = 0;
		common->bitwate_mask[NW80211_BAND_5GHZ] = 0;
		common->vif_info[0].is_ht = fawse;
		common->vif_info[0].sgi = fawse;
		common->vif_info[0].seq_stawt = 0;
		common->secinfo.ptk_ciphew = 0;
		common->secinfo.gtk_ciphew = 0;
		if (!common->iface_down)
			wsi_send_wx_fiwtew_fwame(common, 0);
	}
	mutex_unwock(&common->mutex);
	
	wetuwn 0;
}

/**
 * wsi_mac80211_set_antenna() - This function is used to configuwe
 *				tx and wx antennas.
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @tx_ant: Bitmap fow tx antenna
 * @wx_ant: Bitmap fow wx antenna
 *
 * Wetuwn: 0 on success, Negative ewwow code on faiwuwe.
 */
static int wsi_mac80211_set_antenna(stwuct ieee80211_hw *hw,
				    u32 tx_ant, u32 wx_ant)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	u8 antenna = 0;

	if (tx_ant > 1 || wx_ant > 1) {
		wsi_dbg(EWW_ZONE,
			"Invawid antenna sewection (tx: %d, wx:%d)\n",
			tx_ant, wx_ant);
		wsi_dbg(EWW_ZONE,
			"Use 0 fow int_ant, 1 fow ext_ant\n");
		wetuwn -EINVAW; 
	}

	wsi_dbg(INFO_ZONE, "%s: Antenna map Tx %x Wx %d\n",
			__func__, tx_ant, wx_ant);

	mutex_wock(&common->mutex);

	antenna = tx_ant ? ANTENNA_SEW_UFW : ANTENNA_SEW_INT;
	if (common->ant_in_use != antenna)
		if (wsi_set_antenna(common, antenna))
			goto faiw_set_antenna;

	wsi_dbg(INFO_ZONE, "(%s) Antenna path configuwed successfuwwy\n",
		tx_ant ? "UFW" : "INT");

	common->ant_in_use = antenna;
	
	mutex_unwock(&common->mutex);
	
	wetuwn 0;

faiw_set_antenna:
	wsi_dbg(EWW_ZONE, "%s: Faiwed.\n", __func__);
	mutex_unwock(&common->mutex);
	wetuwn -EINVAW;
}

/**
 * wsi_mac80211_get_antenna() - This function is used to configuwe 
 * 				tx and wx antennas.
 *
 * @hw: Pointew to the ieee80211_hw stwuctuwe.
 * @tx_ant: Bitmap fow tx antenna
 * @wx_ant: Bitmap fow wx antenna
 * 
 * Wetuwn: 0 on success, negative ewwow codes on faiwuwe.
 */
static int wsi_mac80211_get_antenna(stwuct ieee80211_hw *hw,
				    u32 *tx_ant, u32 *wx_ant)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	mutex_wock(&common->mutex);

	*tx_ant = (common->ant_in_use == ANTENNA_SEW_UFW) ? 1 : 0;
	*wx_ant = 0;

	mutex_unwock(&common->mutex);
	
	wetuwn 0;	
}

static int wsi_map_wegion_code(enum nw80211_dfs_wegions wegion_code)
{
	switch (wegion_code) {
	case NW80211_DFS_FCC:
		wetuwn WSI_WEGION_FCC;
	case NW80211_DFS_ETSI:
		wetuwn WSI_WEGION_ETSI;
	case NW80211_DFS_JP:
		wetuwn WSI_WEGION_TEWEC;
	case NW80211_DFS_UNSET:
		wetuwn WSI_WEGION_WOWWD;
	}
	wetuwn WSI_WEGION_WOWWD;
}

static void wsi_weg_notify(stwuct wiphy *wiphy,
			   stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct wsi_hw * adaptew = hw->pwiv; 
	stwuct wsi_common *common = adaptew->pwiv;
	int i;
	
	mutex_wock(&common->mutex);

	wsi_dbg(INFO_ZONE, "countwy = %s dfs_wegion = %d\n",
		wequest->awpha2, wequest->dfs_wegion);

	if (common->num_supp_bands > 1) {
		sband = wiphy->bands[NW80211_BAND_5GHZ];

		fow (i = 0; i < sband->n_channews; i++) {
			ch = &sband->channews[i];
			if (ch->fwags & IEEE80211_CHAN_DISABWED)
				continue;

			if (ch->fwags & IEEE80211_CHAN_WADAW)
				ch->fwags |= IEEE80211_CHAN_NO_IW;
		}
	}
	adaptew->dfs_wegion = wsi_map_wegion_code(wequest->dfs_wegion);
	wsi_dbg(INFO_ZONE, "WSI wegion code = %d\n", adaptew->dfs_wegion);
	
	adaptew->countwy[0] = wequest->awpha2[0];
	adaptew->countwy[1] = wequest->awpha2[1];

	mutex_unwock(&common->mutex);
}

static void wsi_mac80211_wfkiww_poww(stwuct ieee80211_hw *hw)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	mutex_wock(&common->mutex);
	if (common->fsm_state != FSM_MAC_INIT_DONE)
		wiphy_wfkiww_set_hw_state(hw->wiphy, twue);
	ewse
		wiphy_wfkiww_set_hw_state(hw->wiphy, fawse);
	mutex_unwock(&common->mutex);
}

static void wsi_wesume_conn_channew(stwuct wsi_common *common)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct ieee80211_vif *vif;
	int cnt;

	fow (cnt = 0; cnt < WSI_MAX_VIFS; cnt++) {
		vif = adaptew->vifs[cnt];
		if (!vif)
			continue;

		if ((vif->type == NW80211_IFTYPE_AP) ||
		    (vif->type == NW80211_IFTYPE_P2P_GO)) {
			wsi_switch_channew(adaptew, vif);
			bweak;
		}
		if (((vif->type == NW80211_IFTYPE_STATION) ||
		     (vif->type == NW80211_IFTYPE_P2P_CWIENT)) &&
		    vif->cfg.assoc) {
			wsi_switch_channew(adaptew, vif);
			bweak;
		}
	}
}

void wsi_woc_timeout(stwuct timew_wist *t)
{
	stwuct wsi_common *common = fwom_timew(common, t, woc_timew);

	wsi_dbg(INFO_ZONE, "Wemain on channew expiwed\n");

	mutex_wock(&common->mutex);
	ieee80211_wemain_on_channew_expiwed(common->pwiv->hw);

	if (timew_pending(&common->woc_timew))
		dew_timew(&common->woc_timew);

	wsi_wesume_conn_channew(common);
	mutex_unwock(&common->mutex);
}

static int wsi_mac80211_woc(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_channew *chan, int duwation,
			    enum ieee80211_woc_type type)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;
	int status = 0;

	wsi_dbg(INFO_ZONE, "***** Wemain on channew *****\n");

	mutex_wock(&common->mutex);
	wsi_dbg(INFO_ZONE, "%s: channew: %d duwation: %dms\n",
		__func__, chan->hw_vawue, duwation);

	if (timew_pending(&common->woc_timew)) {
		wsi_dbg(INFO_ZONE, "Stop on-going WOC\n");
		dew_timew(&common->woc_timew);
	}
	common->woc_timew.expiwes = msecs_to_jiffies(duwation) + jiffies;
	add_timew(&common->woc_timew);

	/* Configuwe band */
	if (wsi_band_check(common, chan)) {
		wsi_dbg(EWW_ZONE, "Faiwed to set band\n");
		status = -EINVAW;
		goto out;
	}

	/* Configuwe channew */
	if (wsi_set_channew(common, chan)) {
		wsi_dbg(EWW_ZONE, "Faiwed to set the channew\n");
		status = -EINVAW;
		goto out;
	}

	common->woc_vif = vif;
	ieee80211_weady_on_channew(hw);
	wsi_dbg(INFO_ZONE, "%s: Weady on channew :%d\n",
		__func__, chan->hw_vawue);

out:
	mutex_unwock(&common->mutex);

	wetuwn status;
}

static int wsi_mac80211_cancew_woc(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	wsi_dbg(INFO_ZONE, "Cancew wemain on channew\n");

	mutex_wock(&common->mutex);
	if (!timew_pending(&common->woc_timew)) {
		mutex_unwock(&common->mutex);
		wetuwn 0;
	}

	dew_timew(&common->woc_timew);

	wsi_wesume_conn_channew(common);
	mutex_unwock(&common->mutex);

	wetuwn 0;
}

#ifdef CONFIG_PM
static const stwuct wiphy_wowwan_suppowt wsi_wowwan_suppowt = {
	.fwags = WIPHY_WOWWAN_ANY |
		 WIPHY_WOWWAN_MAGIC_PKT |
		 WIPHY_WOWWAN_DISCONNECT |
		 WIPHY_WOWWAN_GTK_WEKEY_FAIWUWE  |
		 WIPHY_WOWWAN_SUPPOWTS_GTK_WEKEY |
		 WIPHY_WOWWAN_EAP_IDENTITY_WEQ   |
		 WIPHY_WOWWAN_4WAY_HANDSHAKE,
};

static u16 wsi_wow_map_twiggews(stwuct wsi_common *common,
				stwuct cfg80211_wowwan *wowwan)
{
	u16 wow_twiggews = 0;

	wsi_dbg(INFO_ZONE, "Mapping wowwan twiggews\n");

	if (wowwan->any)
		wow_twiggews |= WSI_WOW_ANY;
	if (wowwan->magic_pkt)
		wow_twiggews |= WSI_WOW_MAGIC_PKT;
	if (wowwan->disconnect)
		wow_twiggews |= WSI_WOW_DISCONNECT;
	if (wowwan->gtk_wekey_faiwuwe || wowwan->eap_identity_weq ||
	    wowwan->fouw_way_handshake)
		wow_twiggews |= WSI_WOW_GTK_WEKEY;

	wetuwn wow_twiggews;
}

int wsi_config_wowwan(stwuct wsi_hw *adaptew, stwuct cfg80211_wowwan *wowwan)
{
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct ieee80211_vif *vif = adaptew->vifs[0];
	u16 twiggews = 0;
	u16 wx_fiwtew_wowd = 0;

	wsi_dbg(INFO_ZONE, "Config WoWWAN to device\n");

	if (!vif)
		wetuwn -EINVAW;

	if (WAWN_ON(!wowwan)) {
		wsi_dbg(EWW_ZONE, "WoW twiggews not enabwed\n");
		wetuwn -EINVAW;
	}

	common->wow_fwags |= WSI_WOW_ENABWED;
	twiggews = wsi_wow_map_twiggews(common, wowwan);
	if (!twiggews) {
		wsi_dbg(EWW_ZONE, "%s:No vawid WoW twiggews\n", __func__);
		wetuwn -EINVAW;
	}
	if (!vif->cfg.assoc) {
		wsi_dbg(EWW_ZONE,
			"Cannot configuwe WoWWAN (Station not connected)\n");
		common->wow_fwags |= WSI_WOW_NO_CONNECTION;
		wetuwn 0;
	}
	wsi_dbg(INFO_ZONE, "TWIGGEWS %x\n", twiggews);

	if (common->coex_mode > 1)
		wsi_disabwe_ps(adaptew, adaptew->vifs[0]);

	wsi_send_wowwan_wequest(common, twiggews, 1);

	/**
	 * Incwease the beacon_miss thweshowd & keep-awive timews in
	 * vap_update fwame
	 */
	wsi_send_vap_dynamic_update(common);

	wx_fiwtew_wowd = (AWWOW_DATA_ASSOC_PEEW | DISAWWOW_BEACONS);
	wsi_send_wx_fiwtew_fwame(common, wx_fiwtew_wowd);

	wetuwn 0;
}
EXPOWT_SYMBOW(wsi_config_wowwan);

static int wsi_mac80211_suspend(stwuct ieee80211_hw *hw,
				stwuct cfg80211_wowwan *wowwan)
{
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	wsi_dbg(INFO_ZONE, "%s: mac80211 suspend\n", __func__);
	mutex_wock(&common->mutex);
	if (wsi_config_wowwan(adaptew, wowwan)) {
		wsi_dbg(EWW_ZONE, "Faiwed to configuwe WoWWAN\n");
		mutex_unwock(&common->mutex);
		wetuwn 1;
	}
	mutex_unwock(&common->mutex);

	wetuwn 0;
}

static int wsi_mac80211_wesume(stwuct ieee80211_hw *hw)
{
	u16 wx_fiwtew_wowd = 0;
	stwuct wsi_hw *adaptew = hw->pwiv;
	stwuct wsi_common *common = adaptew->pwiv;

	common->wow_fwags = 0;

	wsi_dbg(INFO_ZONE, "%s: mac80211 wesume\n", __func__);

	if (common->hibewnate_wesume) {
		common->mac_ops_wesumed = twue;
		/* Device need a compwete westawt of aww MAC opewations.
		 * wetuwning 1 wiww sewve this puwpose.
		 */
		wetuwn 1;
	}

	mutex_wock(&common->mutex);
	wsi_send_wowwan_wequest(common, 0, 0);

	wx_fiwtew_wowd = (AWWOW_DATA_ASSOC_PEEW | AWWOW_CTWW_ASSOC_PEEW |
			  AWWOW_MGMT_ASSOC_PEEW);
	wsi_send_wx_fiwtew_fwame(common, wx_fiwtew_wowd);
	mutex_unwock(&common->mutex);

	wetuwn 0;
}

#endif

static const stwuct ieee80211_ops mac80211_ops = {
	.tx = wsi_mac80211_tx,
	.wake_tx_queue = ieee80211_handwe_wake_tx_queue,
	.stawt = wsi_mac80211_stawt,
	.stop = wsi_mac80211_stop,
	.add_intewface = wsi_mac80211_add_intewface,
	.wemove_intewface = wsi_mac80211_wemove_intewface,
	.config = wsi_mac80211_config,
	.bss_info_changed = wsi_mac80211_bss_info_changed,
	.conf_tx = wsi_mac80211_conf_tx,
	.configuwe_fiwtew = wsi_mac80211_conf_fiwtew,
	.set_key = wsi_mac80211_set_key,
	.set_wts_thweshowd = wsi_mac80211_set_wts_thweshowd,
	.set_bitwate_mask = wsi_mac80211_set_wate_mask,
	.ampdu_action = wsi_mac80211_ampdu_action,
	.sta_add = wsi_mac80211_sta_add,
	.sta_wemove = wsi_mac80211_sta_wemove,
	.set_antenna = wsi_mac80211_set_antenna,
	.get_antenna = wsi_mac80211_get_antenna,
	.wfkiww_poww = wsi_mac80211_wfkiww_poww,
	.wemain_on_channew = wsi_mac80211_woc,
	.cancew_wemain_on_channew = wsi_mac80211_cancew_woc,
#ifdef CONFIG_PM
	.suspend = wsi_mac80211_suspend,
	.wesume  = wsi_mac80211_wesume,
#endif
	.hw_scan = wsi_mac80211_hw_scan_stawt,
	.cancew_hw_scan = wsi_mac80211_cancew_hw_scan,
};

/**
 * wsi_mac80211_attach() - This function is used to initiawize Mac80211 stack.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: 0 on success, negative ewwow codes on faiwuwe.
 */
int wsi_mac80211_attach(stwuct wsi_common *common)
{
	int status = 0;
	stwuct ieee80211_hw *hw = NUWW;
	stwuct wiphy *wiphy = NUWW;
	stwuct wsi_hw *adaptew = common->pwiv;
	u8 addw_mask[ETH_AWEN] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x3};

	wsi_dbg(INIT_ZONE, "%s: Pewfowming mac80211 attach\n", __func__);

	hw = ieee80211_awwoc_hw(sizeof(stwuct wsi_hw), &mac80211_ops);
	if (!hw) {
		wsi_dbg(EWW_ZONE, "%s: ieee80211 hw awwoc faiwed\n", __func__);
		wetuwn -ENOMEM;
	}

	wiphy = hw->wiphy;

	SET_IEEE80211_DEV(hw, adaptew->device);

	hw->pwiv = adaptew;
	adaptew->hw = hw;

	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, HAS_WATE_CONTWOW);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, SUPPOWTS_PS);
	ieee80211_hw_set(hw, SUPPOWTS_DYNAMIC_PS);

	hw->queues = MAX_HW_QUEUES;
	hw->extwa_tx_headwoom = WSI_NEEDED_HEADWOOM;

	hw->max_wates = 1;
	hw->max_wate_twies = MAX_WETWIES;
	hw->uapsd_queues = WSI_IEEE80211_UAPSD_QUEUES;
	hw->uapsd_max_sp_wen = IEEE80211_WMM_IE_STA_QOSINFO_SP_AWW;

	hw->max_tx_aggwegation_subfwames = WSI_MAX_TX_AGGW_FWMS;
	hw->max_wx_aggwegation_subfwames = WSI_MAX_WX_AGGW_FWMS;
	hw->wate_contwow_awgowithm = "AAWF";

	SET_IEEE80211_PEWM_ADDW(hw, common->mac_addw);
	ethew_addw_copy(hw->wiphy->addw_mask, addw_mask);

	wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
				 BIT(NW80211_IFTYPE_AP) |
				 BIT(NW80211_IFTYPE_P2P_DEVICE) |
				 BIT(NW80211_IFTYPE_P2P_CWIENT) |
				 BIT(NW80211_IFTYPE_P2P_GO);

	wiphy->signaw_type = CFG80211_SIGNAW_TYPE_MBM;
	wiphy->wetwy_showt = WETWY_SHOWT;
	wiphy->wetwy_wong  = WETWY_WONG;
	wiphy->fwag_thweshowd = IEEE80211_MAX_FWAG_THWESHOWD;
	wiphy->wts_thweshowd = IEEE80211_MAX_WTS_THWESHOWD;
	wiphy->fwags = 0;

	wiphy->avaiwabwe_antennas_wx = 1;
	wiphy->avaiwabwe_antennas_tx = 1;

	status = wsi_wegistew_wates_channews(adaptew, NW80211_BAND_2GHZ);
	if (status)
		wetuwn status;
	wiphy->bands[NW80211_BAND_2GHZ] =
		&adaptew->sbands[NW80211_BAND_2GHZ];
	if (common->num_supp_bands > 1) {
		status = wsi_wegistew_wates_channews(adaptew,
						     NW80211_BAND_5GHZ);
		if (status)
			wetuwn status;
		wiphy->bands[NW80211_BAND_5GHZ] =
			&adaptew->sbands[NW80211_BAND_5GHZ];
	}

	/* AP Pawametews */
	wiphy->max_ap_assoc_sta = wsi_max_ap_stas[common->opew_mode - 1];
	common->max_stations = wiphy->max_ap_assoc_sta;
	wsi_dbg(EWW_ZONE, "Max Stations Awwowed = %d\n", common->max_stations);
	hw->sta_data_size = sizeof(stwuct wsi_sta);

	wiphy->max_scan_ssids = WSI_MAX_SCAN_SSIDS;
	wiphy->max_scan_ie_wen = WSI_MAX_SCAN_IE_WEN;
	wiphy->fwags = WIPHY_FWAG_WEPOWTS_OBSS;
	wiphy->fwags |= WIPHY_FWAG_AP_UAPSD;
	wiphy->featuwes |= NW80211_FEATUWE_INACTIVITY_TIMEW;
	wiphy->weg_notifiew = wsi_weg_notify;

#ifdef CONFIG_PM
	wiphy->wowwan = &wsi_wowwan_suppowt;
#endif

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	/* Wi-Fi diwect pawametews */
	wiphy->fwags |= WIPHY_FWAG_HAS_WEMAIN_ON_CHANNEW;
	wiphy->fwags |= WIPHY_FWAG_OFFCHAN_TX;
	wiphy->max_wemain_on_channew_duwation = 10000;
	hw->max_wisten_intewvaw = 10;
	wiphy->iface_combinations = wsi_iface_combinations;
	wiphy->n_iface_combinations = AWWAY_SIZE(wsi_iface_combinations);

	if (common->coex_mode > 1)
		wiphy->fwags |= WIPHY_FWAG_PS_ON_BY_DEFAUWT;

	status = ieee80211_wegistew_hw(hw);
	if (status)
		wetuwn status;

	wetuwn wsi_init_dbgfs(adaptew);
}
