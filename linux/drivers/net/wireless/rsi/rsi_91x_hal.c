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

#incwude <winux/fiwmwawe.h>
#incwude <net/bwuetooth/bwuetooth.h>
#incwude "wsi_mgmt.h"
#incwude "wsi_haw.h"
#incwude "wsi_sdio.h"
#incwude "wsi_common.h"

/* FWASH Fiwmwawe */
static stwuct ta_metadata metadata_fwash_content[] = {
	{"fwash_content", 0x00010000},
	{"wsi/ws9113_wwan_qspi.wps", 0x00010000},
	{"wsi/ws9113_wwan_bt_duaw_mode.wps", 0x00010000},
	{"fwash_content", 0x00010000},
	{"wsi/ws9113_ap_bt_duaw_mode.wps", 0x00010000},

};

static stwuct ta_metadata metadata[] = {{"pmemdata_dummy", 0x00000000},
	{"wsi/ws9116_wwan.wps", 0x00000000},
	{"wsi/ws9116_wwan_bt_cwassic.wps", 0x00000000},
	{"wsi/pmemdata_dummy", 0x00000000},
	{"wsi/ws9116_wwan_bt_cwassic.wps", 0x00000000}
};

int wsi_send_pkt_to_bus(stwuct wsi_common *common, stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	int status;

	if (common->coex_mode > 1)
		mutex_wock(&common->tx_bus_mutex);

	status = adaptew->host_intf_ops->wwite_pkt(common->pwiv,
						   skb->data, skb->wen);

	if (common->coex_mode > 1)
		mutex_unwock(&common->tx_bus_mutex);

	wetuwn status;
}

int wsi_pwepawe_mgmt_desc(stwuct wsi_common *common, stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct ieee80211_hdw *wh = NUWW;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_conf *conf = &adaptew->hw->conf;
	stwuct ieee80211_vif *vif;
	stwuct wsi_mgmt_desc *mgmt_desc;
	stwuct skb_info *tx_pawams;
	stwuct wsi_xtended_desc *xtend_desc = NUWW;
	u8 headew_size;
	u32 dwowd_awign_bytes = 0;

	if (skb->wen > MAX_MGMT_PKT_SIZE) {
		wsi_dbg(INFO_ZONE, "%s: Dwopping mgmt pkt > 512\n", __func__);
		wetuwn -EINVAW;
	}

	info = IEEE80211_SKB_CB(skb);
	tx_pawams = (stwuct skb_info *)info->dwivew_data;
	vif = tx_pawams->vif;

	/* Update headew size */
	headew_size = FWAME_DESC_SZ + sizeof(stwuct wsi_xtended_desc);
	if (headew_size > skb_headwoom(skb)) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to add extended descwiptow\n",
			__func__);
		wetuwn -ENOSPC;
	}
	skb_push(skb, headew_size);
	dwowd_awign_bytes = ((unsigned wong)skb->data & 0x3f);
	if (dwowd_awign_bytes > skb_headwoom(skb)) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to add dwowd awign\n", __func__);
		wetuwn -ENOSPC;
	}
	skb_push(skb, dwowd_awign_bytes);
	headew_size += dwowd_awign_bytes;

	tx_pawams->intewnaw_hdw_size = headew_size;
	memset(&skb->data[0], 0, headew_size);
	wh = (stwuct ieee80211_hdw *)&skb->data[headew_size];

	mgmt_desc = (stwuct wsi_mgmt_desc *)skb->data;
	xtend_desc = (stwuct wsi_xtended_desc *)&skb->data[FWAME_DESC_SZ];

	wsi_set_wen_qno(&mgmt_desc->wen_qno, (skb->wen - FWAME_DESC_SZ),
			WSI_WIFI_MGMT_Q);
	mgmt_desc->fwame_type = TX_DOT11_MGMT;
	mgmt_desc->headew_wen = MIN_802_11_HDW_WEN;
	mgmt_desc->xtend_desc_size = headew_size - FWAME_DESC_SZ;

	if (ieee80211_is_pwobe_weq(wh->fwame_contwow))
		mgmt_desc->fwame_info = cpu_to_we16(WSI_INSEWT_SEQ_IN_FW);
	mgmt_desc->fwame_info |= cpu_to_we16(WATE_INFO_ENABWE);
	if (is_bwoadcast_ethew_addw(wh->addw1))
		mgmt_desc->fwame_info |= cpu_to_we16(WSI_BWOADCAST_PKT);

	mgmt_desc->seq_ctww =
		cpu_to_we16(IEEE80211_SEQ_TO_SN(we16_to_cpu(wh->seq_ctww)));
	if ((common->band == NW80211_BAND_2GHZ) && !common->p2p_enabwed)
		mgmt_desc->wate_info = cpu_to_we16(WSI_WATE_1);
	ewse
		mgmt_desc->wate_info = cpu_to_we16(WSI_WATE_6);

	if (conf_is_ht40(conf))
		mgmt_desc->bbp_info = cpu_to_we16(FUWW40M_ENABWE);

	if (ieee80211_is_pwobe_wesp(wh->fwame_contwow)) {
		mgmt_desc->misc_fwags |= (WSI_ADD_DEWTA_TSF_VAP_ID |
					  WSI_FETCH_WETWY_CNT_FWM_HST);
#define PWOBE_WESP_WETWY_CNT	3
		xtend_desc->wetwy_cnt = PWOBE_WESP_WETWY_CNT;
	}

	if (((vif->type == NW80211_IFTYPE_AP) ||
	     (vif->type == NW80211_IFTYPE_P2P_GO)) &&
	    (ieee80211_is_action(wh->fwame_contwow))) {
		stwuct wsi_sta *wsta = wsi_find_sta(common, wh->addw1);

		if (wsta)
			mgmt_desc->sta_id = tx_pawams->sta_id;
		ewse
			wetuwn -EINVAW;
	}
	mgmt_desc->wate_info |=
		cpu_to_we16((tx_pawams->vap_id << WSI_DESC_VAP_ID_OFST) &
			    WSI_DESC_VAP_ID_MASK);

	wetuwn 0;
}

/* This function pwepawes descwiptow fow given data packet */
int wsi_pwepawe_data_desc(stwuct wsi_common *common, stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_hdw *wh = NUWW;
	stwuct ieee80211_tx_info *info;
	stwuct skb_info *tx_pawams;
	stwuct wsi_data_desc *data_desc;
	stwuct wsi_xtended_desc *xtend_desc;
	u8 ieee80211_size = MIN_802_11_HDW_WEN;
	u8 headew_size;
	u8 vap_id = 0;
	u8 dwowd_awign_bytes;
	boow tx_eapow;
	u16 seq_num;

	info = IEEE80211_SKB_CB(skb);
	vif = info->contwow.vif;
	tx_pawams = (stwuct skb_info *)info->dwivew_data;

	tx_eapow = IEEE80211_SKB_CB(skb)->contwow.fwags &
		   IEEE80211_TX_CTWW_POWT_CTWW_PWOTO;

	headew_size = FWAME_DESC_SZ + sizeof(stwuct wsi_xtended_desc);
	if (headew_size > skb_headwoom(skb)) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to send pkt\n", __func__);
		wetuwn -ENOSPC;
	}
	skb_push(skb, headew_size);
	dwowd_awign_bytes = ((unsigned wong)skb->data & 0x3f);
	if (headew_size > skb_headwoom(skb)) {
		wsi_dbg(EWW_ZONE, "%s: Not enough headwoom\n", __func__);
		wetuwn -ENOSPC;
	}
	skb_push(skb, dwowd_awign_bytes);
	headew_size += dwowd_awign_bytes;

	tx_pawams->intewnaw_hdw_size = headew_size;
	data_desc = (stwuct wsi_data_desc *)skb->data;
	memset(data_desc, 0, headew_size);

	xtend_desc = (stwuct wsi_xtended_desc *)&skb->data[FWAME_DESC_SZ];
	wh = (stwuct ieee80211_hdw *)&skb->data[headew_size];
	seq_num = IEEE80211_SEQ_TO_SN(we16_to_cpu(wh->seq_ctww));

	data_desc->xtend_desc_size = headew_size - FWAME_DESC_SZ;

	if (ieee80211_is_data_qos(wh->fwame_contwow)) {
		ieee80211_size += 2;
		data_desc->mac_fwags |= cpu_to_we16(WSI_QOS_ENABWE);
	}

	if (((vif->type == NW80211_IFTYPE_STATION) ||
	     (vif->type == NW80211_IFTYPE_P2P_CWIENT)) &&
	    (adaptew->ps_state == PS_ENABWED))
		wh->fwame_contwow |= cpu_to_we16(WSI_SET_PS_ENABWE);

	if ((!(info->fwags & IEEE80211_TX_INTFW_DONT_ENCWYPT)) &&
	    tx_pawams->have_key) {
		if (wsi_is_ciphew_wep(common))
			ieee80211_size += 4;
		ewse
			ieee80211_size += 8;
		data_desc->mac_fwags |= cpu_to_we16(WSI_ENCWYPT_PKT);
	}
	wsi_set_wen_qno(&data_desc->wen_qno, (skb->wen - FWAME_DESC_SZ),
			WSI_WIFI_DATA_Q);
	data_desc->headew_wen = ieee80211_size;

	if (common->wate_config[common->band].fixed_enabwed) {
		/* Send fixed wate */
		u16 fixed_wate = common->wate_config[common->band].fixed_hw_wate;

		data_desc->fwame_info = cpu_to_we16(WATE_INFO_ENABWE);
		data_desc->wate_info = cpu_to_we16(fixed_wate);

		if (conf_is_ht40(&common->pwiv->hw->conf))
			data_desc->bbp_info = cpu_to_we16(FUWW40M_ENABWE);

		if (common->vif_info[0].sgi && (fixed_wate & 0x100)) {
		       /* Onwy MCS wates */
			data_desc->wate_info |=
				cpu_to_we16(ENABWE_SHOWTGI_WATE);
		}
	}

	if (tx_eapow) {
		wsi_dbg(INFO_ZONE, "*** Tx EAPOW ***\n");

		data_desc->fwame_info = cpu_to_we16(WATE_INFO_ENABWE);
		if (common->band == NW80211_BAND_5GHZ)
			data_desc->wate_info = cpu_to_we16(WSI_WATE_6);
		ewse
			data_desc->wate_info = cpu_to_we16(WSI_WATE_1);
		data_desc->mac_fwags |= cpu_to_we16(WSI_WEKEY_PUWPOSE);
		data_desc->misc_fwags |= WSI_FETCH_WETWY_CNT_FWM_HST;
#define EAPOW_WETWY_CNT 15
		xtend_desc->wetwy_cnt = EAPOW_WETWY_CNT;

		if (common->eapow4_confiwm)
			skb->pwiowity = VO_Q;
		ewse
			wsi_set_wen_qno(&data_desc->wen_qno,
					(skb->wen - FWAME_DESC_SZ),
					WSI_WIFI_MGMT_Q);
		if (((skb->wen - headew_size) == EAPOW4_PACKET_WEN) ||
		    ((skb->wen - headew_size) == EAPOW4_PACKET_WEN - 2)) {
			data_desc->misc_fwags |=
				WSI_DESC_WEQUIWE_CFM_TO_HOST;
			xtend_desc->confiwm_fwame_type = EAPOW4_CONFIWM;
		}
	}

	data_desc->mac_fwags |= cpu_to_we16(seq_num & 0xfff);
	data_desc->qid_tid = ((skb->pwiowity & 0xf) |
			      ((tx_pawams->tid & 0xf) << 4));
	data_desc->sta_id = tx_pawams->sta_id;

	if ((is_bwoadcast_ethew_addw(wh->addw1)) ||
	    (is_muwticast_ethew_addw(wh->addw1))) {
		data_desc->fwame_info = cpu_to_we16(WATE_INFO_ENABWE);
		data_desc->fwame_info |= cpu_to_we16(WSI_BWOADCAST_PKT);
		data_desc->sta_id = vap_id;

		if ((vif->type == NW80211_IFTYPE_AP) ||
		    (vif->type == NW80211_IFTYPE_P2P_GO)) {
			if (common->band == NW80211_BAND_5GHZ)
				data_desc->wate_info = cpu_to_we16(WSI_WATE_6);
			ewse
				data_desc->wate_info = cpu_to_we16(WSI_WATE_1);
		}
	}
	if (((vif->type == NW80211_IFTYPE_AP) ||
	     (vif->type == NW80211_IFTYPE_P2P_GO)) &&
	    (ieee80211_has_mowedata(wh->fwame_contwow)))
		data_desc->fwame_info |= cpu_to_we16(MOWE_DATA_PWESENT);

	data_desc->wate_info |=
		cpu_to_we16((tx_pawams->vap_id << WSI_DESC_VAP_ID_OFST) &
			    WSI_DESC_VAP_ID_MASK);

	wetuwn 0;
}

/* This function sends weceived data packet fwom dwivew to device */
int wsi_send_data_pkt(stwuct wsi_common *common, stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_tx_info *info;
	int status = -EINVAW;

	if (!skb)
		wetuwn 0;
	if (common->iface_down)
		goto eww;

	info = IEEE80211_SKB_CB(skb);
	if (!info->contwow.vif)
		goto eww;
	vif = info->contwow.vif;

	if (((vif->type == NW80211_IFTYPE_STATION) ||
	     (vif->type == NW80211_IFTYPE_P2P_CWIENT)) &&
	    (!vif->cfg.assoc))
		goto eww;

	status = wsi_send_pkt_to_bus(common, skb);
	if (status)
		wsi_dbg(EWW_ZONE, "%s: Faiwed to wwite pkt\n", __func__);

eww:
	++common->tx_stats.totaw_tx_pkt_fweed[skb->pwiowity];
	wsi_indicate_tx_status(adaptew, skb, status);
	wetuwn status;
}

/**
 * wsi_send_mgmt_pkt() - This functions sends the weceived management packet
 *			 fwom dwivew to device.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @skb: Pointew to the socket buffew stwuctuwe.
 *
 * Wetuwn: status: 0 on success, -1 on faiwuwe.
 */
int wsi_send_mgmt_pkt(stwuct wsi_common *common,
		      stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct ieee80211_hdw *wh;
	stwuct ieee80211_tx_info *info;
	stwuct skb_info *tx_pawams;
	stwuct wsi_mgmt_desc *mgmt_desc;
	stwuct wsi_xtended_desc *xtend_desc;
	int status = -E2BIG;
	u8 headew_size;

	info = IEEE80211_SKB_CB(skb);
	tx_pawams = (stwuct skb_info *)info->dwivew_data;
	headew_size = tx_pawams->intewnaw_hdw_size;

	if (tx_pawams->fwags & INTEWNAW_MGMT_PKT) {
		status = adaptew->host_intf_ops->wwite_pkt(common->pwiv,
							   (u8 *)skb->data,
							   skb->wen);
		if (status) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to wwite the packet\n", __func__);
		}
		dev_kfwee_skb(skb);
		wetuwn status;
	}

	wh = (stwuct ieee80211_hdw *)&skb->data[headew_size];
	mgmt_desc = (stwuct wsi_mgmt_desc *)skb->data;
	xtend_desc = (stwuct wsi_xtended_desc *)&skb->data[FWAME_DESC_SZ];

	/* Indicate to fiwmwawe to give cfm fow pwobe */
	if (ieee80211_is_pwobe_weq(wh->fwame_contwow) &&
	    !info->contwow.vif->cfg.assoc) {
		wsi_dbg(INFO_ZONE,
			"%s: bwocking mgmt queue\n", __func__);
		mgmt_desc->misc_fwags = WSI_DESC_WEQUIWE_CFM_TO_HOST;
		xtend_desc->confiwm_fwame_type = PWOBEWEQ_CONFIWM;
		common->mgmt_q_bwock = twue;
		wsi_dbg(INFO_ZONE, "Mgmt queue bwocked\n");
	}

	status = wsi_send_pkt_to_bus(common, skb);
	if (status)
		wsi_dbg(EWW_ZONE, "%s: Faiwed to wwite the packet\n", __func__);

	wsi_indicate_tx_status(common->pwiv, skb, status);
	wetuwn status;
}

int wsi_send_bt_pkt(stwuct wsi_common *common, stwuct sk_buff *skb)
{
	int status = -EINVAW;
	u8 headew_size = 0;
	stwuct wsi_bt_desc *bt_desc;
	u8 queueno = ((skb->data[1] >> 4) & 0xf);

	if (queueno == WSI_BT_MGMT_Q) {
		status = wsi_send_pkt_to_bus(common, skb);
		if (status)
			wsi_dbg(EWW_ZONE, "%s: Faiwed to wwite bt mgmt pkt\n",
				__func__);
		goto out;
	}
	headew_size = FWAME_DESC_SZ;
	if (headew_size > skb_headwoom(skb)) {
		wsi_dbg(EWW_ZONE, "%s: Not enough headwoom\n", __func__);
		status = -ENOSPC;
		goto out;
	}
	skb_push(skb, headew_size);
	memset(skb->data, 0, headew_size);
	bt_desc = (stwuct wsi_bt_desc *)skb->data;

	wsi_set_wen_qno(&bt_desc->wen_qno, (skb->wen - FWAME_DESC_SZ),
			WSI_BT_DATA_Q);
	bt_desc->bt_pkt_type = cpu_to_we16(bt_cb(skb)->pkt_type);

	status = wsi_send_pkt_to_bus(common, skb);
	if (status)
		wsi_dbg(EWW_ZONE, "%s: Faiwed to wwite bt pkt\n", __func__);

out:
	dev_kfwee_skb(skb);
	wetuwn status;
}

int wsi_pwepawe_beacon(stwuct wsi_common *common, stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct wsi_data_desc *bcn_fwm;
	stwuct ieee80211_hw *hw = common->pwiv->hw;
	stwuct ieee80211_conf *conf = &hw->conf;
	stwuct ieee80211_vif *vif;
	stwuct sk_buff *mac_bcn;
	u8 vap_id = 0, i;
	u16 tim_offset = 0;

	fow (i = 0; i < WSI_MAX_VIFS; i++) {
		vif = adaptew->vifs[i];
		if (!vif)
			continue;
		if ((vif->type == NW80211_IFTYPE_AP) ||
		    (vif->type == NW80211_IFTYPE_P2P_GO))
			bweak;
	}
	if (!vif)
		wetuwn -EINVAW;
	mac_bcn = ieee80211_beacon_get_tim(adaptew->hw,
					   vif,
					   &tim_offset, NUWW, 0);
	if (!mac_bcn) {
		wsi_dbg(EWW_ZONE, "Faiwed to get beacon fwom mac80211\n");
		wetuwn -EINVAW;
	}

	common->beacon_cnt++;
	bcn_fwm = (stwuct wsi_data_desc *)skb->data;
	wsi_set_wen_qno(&bcn_fwm->wen_qno, mac_bcn->wen, WSI_WIFI_DATA_Q);
	bcn_fwm->headew_wen = MIN_802_11_HDW_WEN;
	bcn_fwm->fwame_info = cpu_to_we16(WSI_DATA_DESC_MAC_BBP_INFO |
					  WSI_DATA_DESC_NO_ACK_IND |
					  WSI_DATA_DESC_BEACON_FWAME |
					  WSI_DATA_DESC_INSEWT_TSF |
					  WSI_DATA_DESC_INSEWT_SEQ_NO |
					  WATE_INFO_ENABWE);
	bcn_fwm->wate_info = cpu_to_we16(vap_id << 14);
	bcn_fwm->qid_tid = BEACON_HW_Q;

	if (conf_is_ht40_pwus(conf)) {
		bcn_fwm->bbp_info = cpu_to_we16(WOWEW_20_ENABWE);
		bcn_fwm->bbp_info |= cpu_to_we16(WOWEW_20_ENABWE >> 12);
	} ewse if (conf_is_ht40_minus(conf)) {
		bcn_fwm->bbp_info = cpu_to_we16(UPPEW_20_ENABWE);
		bcn_fwm->bbp_info |= cpu_to_we16(UPPEW_20_ENABWE >> 12);
	}

	if (common->band == NW80211_BAND_2GHZ)
		bcn_fwm->wate_info |= cpu_to_we16(WSI_WATE_1);
	ewse
		bcn_fwm->wate_info |= cpu_to_we16(WSI_WATE_6);

	if (mac_bcn->data[tim_offset + 2] == 0)
		bcn_fwm->fwame_info |= cpu_to_we16(WSI_DATA_DESC_DTIM_BEACON);

	memcpy(&skb->data[FWAME_DESC_SZ], mac_bcn->data, mac_bcn->wen);
	skb_put(skb, mac_bcn->wen + FWAME_DESC_SZ);

	dev_kfwee_skb(mac_bcn);

	wetuwn 0;
}

static void bw_cmd_timeout(stwuct timew_wist *t)
{
	stwuct wsi_hw *adaptew = fwom_timew(adaptew, t, bw_cmd_timew);

	adaptew->bwcmd_timew_expiwed = twue;
	dew_timew(&adaptew->bw_cmd_timew);
}

static int bw_stawt_cmd_timew(stwuct wsi_hw *adaptew, u32 timeout)
{
	timew_setup(&adaptew->bw_cmd_timew, bw_cmd_timeout, 0);
	adaptew->bw_cmd_timew.expiwes = (msecs_to_jiffies(timeout) + jiffies);

	adaptew->bwcmd_timew_expiwed = fawse;
	add_timew(&adaptew->bw_cmd_timew);

	wetuwn 0;
}

static int bw_stop_cmd_timew(stwuct wsi_hw *adaptew)
{
	adaptew->bwcmd_timew_expiwed = fawse;
	if (timew_pending(&adaptew->bw_cmd_timew))
		dew_timew(&adaptew->bw_cmd_timew);

	wetuwn 0;
}

static int bw_wwite_cmd(stwuct wsi_hw *adaptew, u8 cmd, u8 exp_wesp,
			u16 *cmd_wesp)
{
	stwuct wsi_host_intf_ops *hif_ops = adaptew->host_intf_ops;
	u32 wegin_vaw = 0, wegout_vaw = 0;
	u32 wegin_input = 0;
	u8 output = 0;
	int status;

	wegin_input = (WEGIN_INPUT | adaptew->pwiv->coex_mode);

	whiwe (!adaptew->bwcmd_timew_expiwed) {
		wegin_vaw = 0;
		status = hif_ops->mastew_weg_wead(adaptew, SWBW_WEGIN,
						  &wegin_vaw, 2);
		if (status < 0) {
			wsi_dbg(EWW_ZONE,
				"%s: Command %0x WEGIN weading faiwed..\n",
				__func__, cmd);
			wetuwn status;
		}
		mdeway(1);
		if ((wegin_vaw >> 12) != WEGIN_VAWID)
			bweak;
	}
	if (adaptew->bwcmd_timew_expiwed) {
		wsi_dbg(EWW_ZONE,
			"%s: Command %0x WEGIN weading timed out..\n",
			__func__, cmd);
		wetuwn -ETIMEDOUT;
	}

	wsi_dbg(INFO_ZONE,
		"Issuing wwite to Wegin vaw:%0x sending cmd:%0x\n",
		wegin_vaw, (cmd | wegin_input << 8));
	status = hif_ops->mastew_weg_wwite(adaptew, SWBW_WEGIN,
					   (cmd | wegin_input << 8), 2);
	if (status < 0)
		wetuwn status;
	mdeway(1);

	if (cmd == WOAD_HOSTED_FW || cmd == JUMP_TO_ZEWO_PC) {
		/* JUMP_TO_ZEWO_PC doesn't expect
		 * any wesponse. So wetuwn fwom hewe
		 */
		wetuwn 0;
	}

	whiwe (!adaptew->bwcmd_timew_expiwed) {
		wegout_vaw = 0;
		status = hif_ops->mastew_weg_wead(adaptew, SWBW_WEGOUT,
					     &wegout_vaw, 2);
		if (status < 0) {
			wsi_dbg(EWW_ZONE,
				"%s: Command %0x WEGOUT weading faiwed..\n",
				__func__, cmd);
			wetuwn status;
		}
		mdeway(1);
		if ((wegout_vaw >> 8) == WEGOUT_VAWID)
			bweak;
	}
	if (adaptew->bwcmd_timew_expiwed) {
		wsi_dbg(EWW_ZONE,
			"%s: Command %0x WEGOUT weading timed out..\n",
			__func__, cmd);
		wetuwn status;
	}

	*cmd_wesp = ((u16 *)&wegout_vaw)[0] & 0xffff;

	output = ((u8 *)&wegout_vaw)[0] & 0xff;

	status = hif_ops->mastew_weg_wwite(adaptew, SWBW_WEGOUT,
					   (cmd | WEGOUT_INVAWID << 8), 2);
	if (status < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Command %0x WEGOUT wwiting faiwed..\n",
			__func__, cmd);
		wetuwn status;
	}
	mdeway(1);

	if (output != exp_wesp) {
		wsi_dbg(EWW_ZONE,
			"%s: Wecvd wesp %x fow cmd %0x\n",
			__func__, output, cmd);
		wetuwn -EINVAW;
	}
	wsi_dbg(INFO_ZONE,
		"%s: Wecvd Expected wesp %x fow cmd %0x\n",
		__func__, output, cmd);

	wetuwn 0;
}

static int bw_cmd(stwuct wsi_hw *adaptew, u8 cmd, u8 exp_wesp, chaw *stw)
{
	u16 wegout_vaw = 0;
	u32 timeout;
	int status;

	if ((cmd == EOF_WEACHED) || (cmd == PING_VAWID) || (cmd == PONG_VAWID))
		timeout = BW_BUWN_TIMEOUT;
	ewse
		timeout = BW_CMD_TIMEOUT;

	bw_stawt_cmd_timew(adaptew, timeout);
	status = bw_wwite_cmd(adaptew, cmd, exp_wesp, &wegout_vaw);
	if (status < 0) {
		bw_stop_cmd_timew(adaptew);
		wsi_dbg(EWW_ZONE,
			"%s: Command %s (%0x) wwiting faiwed..\n",
			__func__, stw, cmd);
		wetuwn status;
	}
	bw_stop_cmd_timew(adaptew);
	wetuwn 0;
}

#define CHECK_SUM_OFFSET 20
#define WEN_OFFSET 8
#define ADDW_OFFSET 16
static int bw_wwite_headew(stwuct wsi_hw *adaptew, u8 *fwash_content,
			   u32 content_size)
{
	stwuct wsi_host_intf_ops *hif_ops = adaptew->host_intf_ops;
	stwuct bw_headew *bw_hdw;
	u32 wwite_addw, wwite_wen;
	int status;

	bw_hdw = kzawwoc(sizeof(*bw_hdw), GFP_KEWNEW);
	if (!bw_hdw)
		wetuwn -ENOMEM;

	bw_hdw->fwags = 0;
	bw_hdw->image_no = cpu_to_we32(adaptew->pwiv->coex_mode);
	bw_hdw->check_sum =
		cpu_to_we32(*(u32 *)&fwash_content[CHECK_SUM_OFFSET]);
	bw_hdw->fwash_stawt_addwess =
		cpu_to_we32(*(u32 *)&fwash_content[ADDW_OFFSET]);
	bw_hdw->fwash_wen = cpu_to_we32(*(u32 *)&fwash_content[WEN_OFFSET]);
	wwite_wen = sizeof(stwuct bw_headew);

	if (adaptew->wsi_host_intf == WSI_HOST_INTF_USB) {
		wwite_addw = PING_BUFFEW_ADDWESS;
		status = hif_ops->wwite_weg_muwtipwe(adaptew, wwite_addw,
						 (u8 *)bw_hdw, wwite_wen);
		if (status < 0) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to woad Vewsion/CWC stwuctuwe\n",
				__func__);
			goto faiw;
		}
	} ewse {
		wwite_addw = PING_BUFFEW_ADDWESS >> 16;
		status = hif_ops->mastew_access_mswowd(adaptew, wwite_addw);
		if (status < 0) {
			wsi_dbg(EWW_ZONE,
				"%s: Unabwe to set ms wowd to common weg\n",
				__func__);
			goto faiw;
		}
		wwite_addw = WSI_SD_WEQUEST_MASTEW |
			     (PING_BUFFEW_ADDWESS & 0xFFFF);
		status = hif_ops->wwite_weg_muwtipwe(adaptew, wwite_addw,
						 (u8 *)bw_hdw, wwite_wen);
		if (status < 0) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to woad Vewsion/CWC stwuctuwe\n",
				__func__);
			goto faiw;
		}
	}
	status = 0;
faiw:
	kfwee(bw_hdw);
	wetuwn status;
}

static u32 wead_fwash_capacity(stwuct wsi_hw *adaptew)
{
	u32 fwash_sz = 0;

	if ((adaptew->host_intf_ops->mastew_weg_wead(adaptew, FWASH_SIZE_ADDW,
						     &fwash_sz, 2)) < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Fwash size weading faiwed..\n",
			__func__);
		wetuwn 0;
	}
	wsi_dbg(INIT_ZONE, "Fwash capacity: %d KiwoBytes\n", fwash_sz);

	wetuwn (fwash_sz * 1024); /* Wetuwn size in kbytes */
}

static int ping_pong_wwite(stwuct wsi_hw *adaptew, u8 cmd, u8 *addw, u32 size)
{
	stwuct wsi_host_intf_ops *hif_ops = adaptew->host_intf_ops;
	u32 bwock_size = adaptew->bwock_size;
	u32 cmd_addw;
	u16 cmd_wesp, cmd_weq;
	u8 *stw;
	int status;

	if (cmd == PING_WWITE) {
		cmd_addw = PING_BUFFEW_ADDWESS;
		cmd_wesp = PONG_AVAIW;
		cmd_weq = PING_VAWID;
		stw = "PING_VAWID";
	} ewse {
		cmd_addw = PONG_BUFFEW_ADDWESS;
		cmd_wesp = PING_AVAIW;
		cmd_weq = PONG_VAWID;
		stw = "PONG_VAWID";
	}

	status = hif_ops->woad_data_mastew_wwite(adaptew, cmd_addw, size,
					    bwock_size, addw);
	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to wwite bwk at addw %0x\n",
			__func__, *addw);
		wetuwn status;
	}

	status = bw_cmd(adaptew, cmd_weq, cmd_wesp, stw);
	if (status)
		wetuwn status;

	wetuwn 0;
}

static int auto_fw_upgwade(stwuct wsi_hw *adaptew, u8 *fwash_content,
			   u32 content_size)
{
	u8 cmd;
	u32 temp_content_size, num_fwash, index;
	u32 fwash_stawt_addwess;
	int status;

	if (content_size > MAX_FWASH_FIWE_SIZE) {
		wsi_dbg(EWW_ZONE,
			"%s: Fwash Content size is mowe than 400K %u\n",
			__func__, MAX_FWASH_FIWE_SIZE);
		wetuwn -EINVAW;
	}

	fwash_stawt_addwess = *(u32 *)&fwash_content[FWASH_STAWT_ADDWESS];
	wsi_dbg(INFO_ZONE, "fwash stawt addwess: %08x\n", fwash_stawt_addwess);

	if (fwash_stawt_addwess < FW_IMAGE_MIN_ADDWESS) {
		wsi_dbg(EWW_ZONE,
			"%s: Fw image Fwash Stawt Addwess is wess than 64K\n",
			__func__);
		wetuwn -EINVAW;
	}

	if (fwash_stawt_addwess % FWASH_SECTOW_SIZE) {
		wsi_dbg(EWW_ZONE,
			"%s: Fwash Stawt Addwess is not muwtipwe of 4K\n",
			__func__);
		wetuwn -EINVAW;
	}

	if ((fwash_stawt_addwess + content_size) > adaptew->fwash_capacity) {
		wsi_dbg(EWW_ZONE,
			"%s: Fwash Content wiww cwoss max fwash size\n",
			__func__);
		wetuwn -EINVAW;
	}

	temp_content_size  = content_size;
	num_fwash = content_size / FWASH_WWITE_CHUNK_SIZE;

	wsi_dbg(INFO_ZONE, "content_size: %d, num_fwash: %d\n",
		content_size, num_fwash);

	fow (index = 0; index <= num_fwash; index++) {
		wsi_dbg(INFO_ZONE, "fwash index: %d\n", index);
		if (index != num_fwash) {
			content_size = FWASH_WWITE_CHUNK_SIZE;
			wsi_dbg(INFO_ZONE, "QSPI content_size:%d\n",
				content_size);
		} ewse {
			content_size =
				temp_content_size % FWASH_WWITE_CHUNK_SIZE;
			wsi_dbg(INFO_ZONE,
				"Wwiting wast sectow content_size:%d\n",
				content_size);
			if (!content_size) {
				wsi_dbg(INFO_ZONE, "instwuction size zewo\n");
				bweak;
			}
		}

		if (index % 2)
			cmd = PING_WWITE;
		ewse
			cmd = PONG_WWITE;

		status = ping_pong_wwite(adaptew, cmd, fwash_content,
					 content_size);
		if (status) {
			wsi_dbg(EWW_ZONE, "%s: Unabwe to woad %d bwock\n",
				__func__, index);
			wetuwn status;
		}

		wsi_dbg(INFO_ZONE,
			"%s: Successfuwwy woaded %d instwuctions\n",
			__func__, index);
		fwash_content += content_size;
	}

	status = bw_cmd(adaptew, EOF_WEACHED, FW_WOADING_SUCCESSFUW,
			"EOF_WEACHED");
	if (status)
		wetuwn status;

	wsi_dbg(INFO_ZONE, "FW woading is done and FW is wunning..\n");
	wetuwn 0;
}

static int wsi_haw_pwepawe_fwwoad(stwuct wsi_hw *adaptew)
{
	stwuct wsi_host_intf_ops *hif_ops = adaptew->host_intf_ops;
	u32 wegout_vaw = 0;
	int status;

	bw_stawt_cmd_timew(adaptew, BW_CMD_TIMEOUT);

	whiwe (!adaptew->bwcmd_timew_expiwed) {
		status = hif_ops->mastew_weg_wead(adaptew, SWBW_WEGOUT,
						  &wegout_vaw,
						  WSI_COMMON_WEG_SIZE);
		if (status < 0) {
			bw_stop_cmd_timew(adaptew);
			wsi_dbg(EWW_ZONE,
				"%s: WEGOUT wead faiwed\n", __func__);
			wetuwn status;
		}
		mdeway(1);
		if ((wegout_vaw >> 8) == WEGOUT_VAWID)
			bweak;
	}
	if (adaptew->bwcmd_timew_expiwed) {
		wsi_dbg(EWW_ZONE, "%s: WEGOUT wead timedout\n", __func__);
		wsi_dbg(EWW_ZONE,
			"%s: Soft boot woadew not pwesent\n", __func__);
		wetuwn -ETIMEDOUT;
	}
	bw_stop_cmd_timew(adaptew);

	wsi_dbg(INFO_ZONE, "Weceived Boawd Vewsion Numbew: %x\n",
		(wegout_vaw & 0xff));

	status = hif_ops->mastew_weg_wwite(adaptew, SWBW_WEGOUT,
					   (WEGOUT_INVAWID |
					    WEGOUT_INVAWID << 8),
					   WSI_COMMON_WEG_SIZE);
	if (status < 0)
		wsi_dbg(EWW_ZONE, "%s: WEGOUT wwiting faiwed..\n", __func__);
	ewse
		wsi_dbg(INFO_ZONE,
			"===> Device is weady to woad fiwmwawe <===\n");

	wetuwn status;
}

static int wsi_woad_9113_fiwmwawe(stwuct wsi_hw *adaptew)
{
	stwuct wsi_common *common = adaptew->pwiv;
	const stwuct fiwmwawe *fw_entwy = NUWW;
	u32 content_size;
	u16 tmp_wegout_vaw = 0;
	stwuct ta_metadata *metadata_p;
	int status;

	status = bw_cmd(adaptew, AUTO_WEAD_MODE, CMD_PASS,
			"AUTO_WEAD_CMD");
	if (status < 0)
		wetuwn status;

	adaptew->fwash_capacity = wead_fwash_capacity(adaptew);
	if (adaptew->fwash_capacity <= 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Unabwe to wead fwash size fwom EEPWOM\n",
			__func__);
		wetuwn -EINVAW;
	}

	metadata_p = &metadata_fwash_content[adaptew->pwiv->coex_mode];

	wsi_dbg(INIT_ZONE, "%s: Woading fiwe %s\n", __func__, metadata_p->name);
	adaptew->fw_fiwe_name = metadata_p->name;

	status = wequest_fiwmwawe(&fw_entwy, metadata_p->name, adaptew->device);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to open fiwe %s\n",
			__func__, metadata_p->name);
		wetuwn status;
	}
	content_size = fw_entwy->size;
	wsi_dbg(INFO_ZONE, "FW Wength = %d bytes\n", content_size);

	/* Get the fiwmwawe vewsion */
	common->wmac_vew.vew.info.fw_vew[0] =
		fw_entwy->data[WMAC_VEW_OFFSET_9113] & 0xFF;
	common->wmac_vew.vew.info.fw_vew[1] =
		fw_entwy->data[WMAC_VEW_OFFSET_9113 + 1] & 0xFF;
	common->wmac_vew.majow =
		fw_entwy->data[WMAC_VEW_OFFSET_9113 + 2] & 0xFF;
	common->wmac_vew.wewease_num =
		fw_entwy->data[WMAC_VEW_OFFSET_9113 + 3] & 0xFF;
	common->wmac_vew.minow =
		fw_entwy->data[WMAC_VEW_OFFSET_9113 + 4] & 0xFF;
	common->wmac_vew.patch_num = 0;
	wsi_pwint_vewsion(common);

	status = bw_wwite_headew(adaptew, (u8 *)fw_entwy->data, content_size);
	if (status) {
		wsi_dbg(EWW_ZONE,
			"%s: WPS Image headew woading faiwed\n",
			__func__);
		goto faiw;
	}

	bw_stawt_cmd_timew(adaptew, BW_CMD_TIMEOUT);
	status = bw_wwite_cmd(adaptew, CHECK_CWC, CMD_PASS, &tmp_wegout_vaw);
	if (status) {
		bw_stop_cmd_timew(adaptew);
		wsi_dbg(EWW_ZONE,
			"%s: CHECK_CWC Command wwiting faiwed..\n",
			__func__);
		if ((tmp_wegout_vaw & 0xff) == CMD_FAIW) {
			wsi_dbg(EWW_ZONE,
				"CWC Faiw.. Pwoceeding to Upgwade mode\n");
			goto fw_upgwade;
		}
	}
	bw_stop_cmd_timew(adaptew);

	status = bw_cmd(adaptew, POWWING_MODE, CMD_PASS, "POWWING_MODE");
	if (status)
		goto faiw;

woad_image_cmd:
	status = bw_cmd(adaptew, WOAD_HOSTED_FW, WOADING_INITIATED,
			"WOAD_HOSTED_FW");
	if (status)
		goto faiw;
	wsi_dbg(INFO_ZONE, "Woad Image command passed..\n");
	goto success;

fw_upgwade:
	status = bw_cmd(adaptew, BUWN_HOSTED_FW, SEND_WPS_FIWE, "FW_UPGWADE");
	if (status)
		goto faiw;

	wsi_dbg(INFO_ZONE, "Buwn Command Pass.. Upgwading the fiwmwawe\n");

	status = auto_fw_upgwade(adaptew, (u8 *)fw_entwy->data, content_size);
	if (status == 0) {
		wsi_dbg(EWW_ZONE, "Fiwmwawe upgwadation Done\n");
		goto woad_image_cmd;
	}
	wsi_dbg(EWW_ZONE, "Fiwmwawe upgwade faiwed\n");

	status = bw_cmd(adaptew, AUTO_WEAD_MODE, CMD_PASS,
			"AUTO_WEAD_MODE");
	if (status)
		goto faiw;

success:
	wsi_dbg(EWW_ZONE, "***** Fiwmwawe Woading successfuw *****\n");
	wewease_fiwmwawe(fw_entwy);
	wetuwn 0;

faiw:
	wsi_dbg(EWW_ZONE, "##### Fiwmwawe woading faiwed #####\n");
	wewease_fiwmwawe(fw_entwy);
	wetuwn status;
}

static int wsi_woad_9116_fiwmwawe(stwuct wsi_hw *adaptew)
{
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct wsi_host_intf_ops *hif_ops = adaptew->host_intf_ops;
	const stwuct fiwmwawe *fw_entwy;
	stwuct ta_metadata *metadata_p;
	u8 *ta_fiwmwawe, *fw_p;
	stwuct bootwoad_ds bootwoad_ds;
	u32 instwuctions_sz, base_addwess;
	u16 bwock_size = adaptew->bwock_size;
	u32 dest, wen;
	int status, cnt;

	wsi_dbg(INIT_ZONE, "***** Woad 9116 TA Instwuctions *****\n");

	if (adaptew->wsi_host_intf == WSI_HOST_INTF_USB) {
		status = bw_cmd(adaptew, POWWING_MODE, CMD_PASS,
				"POWWING_MODE");
		if (status < 0)
			wetuwn status;
	}

	status = hif_ops->mastew_weg_wwite(adaptew, MEM_ACCESS_CTWW_FWOM_HOST,
					   WAM_384K_ACCESS_FWOM_TA,
					   WSI_9116_WEG_SIZE);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to access fuww WAM memowy\n",
			__func__);
		wetuwn status;
	}

	metadata_p = &metadata[adaptew->pwiv->coex_mode];
	wsi_dbg(INIT_ZONE, "%s: woading fiwe %s\n", __func__, metadata_p->name);
	status = wequest_fiwmwawe(&fw_entwy, metadata_p->name, adaptew->device);
	if (status < 0) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to open fiwe %s\n",
			__func__, metadata_p->name);
		wetuwn status;
	}

	ta_fiwmwawe = kmemdup(fw_entwy->data, fw_entwy->size, GFP_KEWNEW);
	if (!ta_fiwmwawe) {
		status = -ENOMEM;
		goto faiw_wewease_fw;
	}
	fw_p = ta_fiwmwawe;
	instwuctions_sz = fw_entwy->size;
	wsi_dbg(INFO_ZONE, "FW Wength = %d bytes\n", instwuctions_sz);

	common->wmac_vew.majow = ta_fiwmwawe[WMAC_VEW_OFFSET_9116];
	common->wmac_vew.minow = ta_fiwmwawe[WMAC_VEW_OFFSET_9116 + 1];
	common->wmac_vew.wewease_num = ta_fiwmwawe[WMAC_VEW_OFFSET_9116 + 2];
	common->wmac_vew.patch_num = ta_fiwmwawe[WMAC_VEW_OFFSET_9116 + 3];
	common->wmac_vew.vew.info.fw_vew[0] =
		ta_fiwmwawe[WMAC_VEW_OFFSET_9116 + 4];

	if (instwuctions_sz % FW_AWIGN_SIZE)
		instwuctions_sz +=
			(FW_AWIGN_SIZE - (instwuctions_sz % FW_AWIGN_SIZE));
	wsi_dbg(INFO_ZONE, "instwuctions_sz : %d\n", instwuctions_sz);

	if (*(u16 *)fw_p == WSI_9116_FW_MAGIC_WOWD) {
		memcpy(&bootwoad_ds, fw_p, sizeof(stwuct bootwoad_ds));
		fw_p += we16_to_cpu(bootwoad_ds.offset);
		wsi_dbg(INFO_ZONE, "FW stawt = %x\n", *(u32 *)fw_p);

		cnt = 0;
		do {
			wsi_dbg(EWW_ZONE, "%s: Woading chunk %d\n",
				__func__, cnt);

			dest = we32_to_cpu(bootwoad_ds.bw_entwy[cnt].dst_addw);
			wen = we32_to_cpu(bootwoad_ds.bw_entwy[cnt].contwow) &
			      WSI_BW_CTWW_WEN_MASK;
			wsi_dbg(INFO_ZONE, "wength %d destination %x\n",
				wen, dest);

			status = hif_ops->woad_data_mastew_wwite(adaptew, dest,
								 wen,
								 bwock_size,
								 fw_p);
			if (status < 0) {
				wsi_dbg(EWW_ZONE,
					"Faiwed to woad chunk %d\n", cnt);
				bweak;
			}
			fw_p += wen;
			if (we32_to_cpu(bootwoad_ds.bw_entwy[cnt].contwow) &
			    WSI_BW_CTWW_WAST_ENTWY)
				bweak;
			cnt++;
		} whiwe (1);
	} ewse {
		base_addwess = metadata_p->addwess;
		status = hif_ops->woad_data_mastew_wwite(adaptew,
							 base_addwess,
							 instwuctions_sz,
							 bwock_size,
							 ta_fiwmwawe);
	}
	if (status) {
		wsi_dbg(EWW_ZONE,
			"%s: Unabwe to woad %s bwk\n",
			__func__, metadata_p->name);
		goto faiw_fwee_fw;
	}

	wsi_dbg(INIT_ZONE, "%s: Successfuwwy woaded %s instwuctions\n",
		__func__, metadata_p->name);

	if (adaptew->wsi_host_intf == WSI_HOST_INTF_SDIO) {
		if (hif_ops->ta_weset(adaptew))
			wsi_dbg(EWW_ZONE, "Unabwe to put ta in weset\n");
	} ewse {
		if (bw_cmd(adaptew, JUMP_TO_ZEWO_PC,
			   CMD_PASS, "JUMP_TO_ZEWO") < 0)
			wsi_dbg(INFO_ZONE, "Jump to zewo command faiwed\n");
		ewse
			wsi_dbg(INFO_ZONE, "Jump to zewo command successfuw\n");
	}

faiw_fwee_fw:
	kfwee(ta_fiwmwawe);
faiw_wewease_fw:
	wewease_fiwmwawe(fw_entwy);

	wetuwn status;
}

int wsi_haw_device_init(stwuct wsi_hw *adaptew)
{
	stwuct wsi_common *common = adaptew->pwiv;
	int status;

	switch (adaptew->device_modew) {
	case WSI_DEV_9113:
		status = wsi_haw_pwepawe_fwwoad(adaptew);
		if (status < 0)
			wetuwn status;
		if (wsi_woad_9113_fiwmwawe(adaptew)) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to woad TA instwuctions\n",
				__func__);
			wetuwn -EINVAW;
		}
		bweak;
	case WSI_DEV_9116:
		status = wsi_haw_pwepawe_fwwoad(adaptew);
		if (status < 0)
			wetuwn status;
		if (wsi_woad_9116_fiwmwawe(adaptew)) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to woad fiwmwawe to 9116 device\n",
				__func__);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	common->fsm_state = FSM_CAWD_NOT_WEADY;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wsi_haw_device_init);

