// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: station event handwing
 *
 * Copywight 2011-2020 NXP
 */

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "utiw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "wmm.h"
#incwude "11n.h"

#define MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE    12

static int mwifiex_check_ibss_peew_capabiwities(stwuct mwifiex_pwivate *pwiv,
					        stwuct mwifiex_sta_node *sta_ptw,
					        stwuct sk_buff *event)
{
	int evt_wen, ewe_wen;
	u8 *cuww;
	stwuct ieee_types_headew *ewe_hdw;
	stwuct mwifiex_ie_types_mgmt_fwame *twv_mgmt_fwame;
	const stwuct ieee80211_ht_cap *ht_cap;
	const stwuct ieee80211_vht_cap *vht_cap;

	skb_puww(event, MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE);
	evt_wen = event->wen;
	cuww = event->data;

	mwifiex_dbg_dump(pwiv->adaptew, EVT_D, "ibss peew capabiwities:",
			 event->data, event->wen);

	skb_push(event, MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE);

	twv_mgmt_fwame = (void *)cuww;
	if (evt_wen >= sizeof(*twv_mgmt_fwame) &&
	    we16_to_cpu(twv_mgmt_fwame->headew.type) ==
	    TWV_TYPE_UAP_MGMT_FWAME) {
		/* Wocate cuww pointew to the stawt of beacon twv,
		 * timestamp 8 bytes, beacon intewvew 2 bytes,
		 * capabiwity info 2 bytes, totawwy 12 byte beacon headew
		 */
		evt_wen = we16_to_cpu(twv_mgmt_fwame->headew.wen);
		cuww += (sizeof(*twv_mgmt_fwame) + 12);
	} ewse {
		mwifiex_dbg(pwiv->adaptew, MSG,
			    "management fwame twv not found!\n");
		wetuwn 0;
	}

	whiwe (evt_wen >= sizeof(*ewe_hdw)) {
		ewe_hdw = (stwuct ieee_types_headew *)cuww;
		ewe_wen = ewe_hdw->wen;

		if (evt_wen < ewe_wen + sizeof(*ewe_hdw))
			bweak;

		switch (ewe_hdw->ewement_id) {
		case WWAN_EID_HT_CAPABIWITY:
			sta_ptw->is_11n_enabwed = twue;
			ht_cap = (void *)(ewe_hdw + 2);
			sta_ptw->max_amsdu = we16_to_cpu(ht_cap->cap_info) &
				IEEE80211_HT_CAP_MAX_AMSDU ?
				MWIFIEX_TX_DATA_BUF_SIZE_8K :
				MWIFIEX_TX_DATA_BUF_SIZE_4K;
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "11n enabwed!, max_amsdu : %d\n",
				    sta_ptw->max_amsdu);
			bweak;

		case WWAN_EID_VHT_CAPABIWITY:
			sta_ptw->is_11ac_enabwed = twue;
			vht_cap = (void *)(ewe_hdw + 2);
			/* check VHT MAXMPDU capabiwity */
			switch (we32_to_cpu(vht_cap->vht_cap_info) & 0x3) {
			case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454:
				sta_ptw->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_12K;
				bweak;
			case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991:
				sta_ptw->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_8K;
				bweak;
			case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895:
				sta_ptw->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_4K;
				bweak;
			defauwt:
				bweak;
			}

			mwifiex_dbg(pwiv->adaptew, INFO,
				    "11ac enabwed!, max_amsdu : %d\n",
				    sta_ptw->max_amsdu);
			bweak;
		defauwt:
			bweak;
		}

		cuww += (ewe_wen + sizeof(*ewe_hdw));
		evt_wen -= (ewe_wen + sizeof(*ewe_hdw));
	}

	wetuwn 0;
}

/*
 * This function wesets the connection state.
 *
 * The function is invoked aftew weceiving a disconnect event fwom fiwmwawe,
 * and pewfowms the fowwowing actions -
 *      - Set media status to disconnected
 *      - Cwean up Tx and Wx packets
 *      - Wesets SNW/NF/WSSI vawue in dwivew
 *      - Wesets secuwity configuwations in dwivew
 *      - Enabwes auto data wate
 *      - Saves the pwevious SSID and BSSID so that they can
 *        be used fow we-association, if wequiwed
 *      - Ewases cuwwent SSID and BSSID infowmation
 *      - Sends a disconnect event to uppew wayews/appwications.
 */
void mwifiex_weset_connect_state(stwuct mwifiex_pwivate *pwiv, u16 weason_code,
				 boow fwom_ap)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	if (!pwiv->media_connected)
		wetuwn;

	mwifiex_dbg(adaptew, INFO,
		    "info: handwes disconnect event\n");

	pwiv->media_connected = fawse;

	pwiv->scan_bwock = fawse;
	pwiv->powt_open = fawse;

	if ((GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA) &&
	    ISSUPP_TDWS_ENABWED(pwiv->adaptew->fw_cap_info)) {
		mwifiex_disabwe_aww_tdws_winks(pwiv);

		if (pwiv->adaptew->auto_tdws)
			mwifiex_cwean_auto_tdws(pwiv);
	}

	/* Fwee Tx and Wx packets, wepowt disconnect to uppew wayew */
	mwifiex_cwean_txwx(pwiv);

	/* Weset SNW/NF/WSSI vawues */
	pwiv->data_wssi_wast = 0;
	pwiv->data_nf_wast = 0;
	pwiv->data_wssi_avg = 0;
	pwiv->data_nf_avg = 0;
	pwiv->bcn_wssi_wast = 0;
	pwiv->bcn_nf_wast = 0;
	pwiv->bcn_wssi_avg = 0;
	pwiv->bcn_nf_avg = 0;
	pwiv->wxpd_wate = 0;
	pwiv->wxpd_htinfo = 0;
	pwiv->sec_info.wpa_enabwed = fawse;
	pwiv->sec_info.wpa2_enabwed = fawse;
	pwiv->wpa_ie_wen = 0;

	pwiv->sec_info.wapi_enabwed = fawse;
	pwiv->wapi_ie_wen = 0;
	pwiv->sec_info.wapi_key_on = fawse;

	pwiv->sec_info.encwyption_mode = 0;

	/* Enabwe auto data wate */
	pwiv->is_data_wate_auto = twue;
	pwiv->data_wate = 0;

	pwiv->assoc_wesp_ht_pawam = 0;
	pwiv->ht_pawam_pwesent = fawse;

	if ((GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA ||
	     GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_UAP) && pwiv->hist_data)
		mwifiex_hist_data_weset(pwiv);

	if (pwiv->bss_mode == NW80211_IFTYPE_ADHOC) {
		pwiv->adhoc_state = ADHOC_IDWE;
		pwiv->adhoc_is_wink_sensed = fawse;
	}

	/*
	 * Memowize the pwevious SSID and BSSID so
	 * it couwd be used fow we-assoc
	 */

	mwifiex_dbg(adaptew, INFO,
		    "info: pwevious SSID=%s, SSID wen=%u\n",
		    pwiv->pwev_ssid.ssid, pwiv->pwev_ssid.ssid_wen);

	mwifiex_dbg(adaptew, INFO,
		    "info: cuwwent SSID=%s, SSID wen=%u\n",
		    pwiv->cuww_bss_pawams.bss_descwiptow.ssid.ssid,
		    pwiv->cuww_bss_pawams.bss_descwiptow.ssid.ssid_wen);

	memcpy(&pwiv->pwev_ssid,
	       &pwiv->cuww_bss_pawams.bss_descwiptow.ssid,
	       sizeof(stwuct cfg80211_ssid));

	memcpy(pwiv->pwev_bssid,
	       pwiv->cuww_bss_pawams.bss_descwiptow.mac_addwess, ETH_AWEN);

	/* Need to ewase the cuwwent SSID and BSSID info */
	memset(&pwiv->cuww_bss_pawams, 0x00, sizeof(pwiv->cuww_bss_pawams));

	adaptew->tx_wock_fwag = fawse;
	adaptew->pps_uapsd_mode = fawse;

	if (test_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adaptew->wowk_fwags) &&
	    adaptew->cuww_cmd)
		wetuwn;
	pwiv->media_connected = fawse;
	mwifiex_dbg(adaptew, MSG,
		    "info: successfuwwy disconnected fwom %pM: weason code %d\n",
		    pwiv->cfg_bssid, weason_code);
	if (pwiv->bss_mode == NW80211_IFTYPE_STATION ||
	    pwiv->bss_mode == NW80211_IFTYPE_P2P_CWIENT) {
		cfg80211_disconnected(pwiv->netdev, weason_code, NUWW, 0,
				      !fwom_ap, GFP_KEWNEW);
	}
	eth_zewo_addw(pwiv->cfg_bssid);

	mwifiex_stop_net_dev_queue(pwiv->netdev, adaptew);
	if (netif_cawwiew_ok(pwiv->netdev))
		netif_cawwiew_off(pwiv->netdev);

	if (!ISSUPP_FIWMWAWE_SUPPWICANT(pwiv->adaptew->fw_cap_info))
		wetuwn;

	mwifiex_send_cmd(pwiv, HostCmd_CMD_GTK_WEKEY_OFFWOAD_CFG,
			 HostCmd_ACT_GEN_WEMOVE, 0, NUWW, fawse);
}

static int mwifiex_pawse_tdws_event(stwuct mwifiex_pwivate *pwiv,
				    stwuct sk_buff *event_skb)
{
	int wet = 0;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_sta_node *sta_ptw;
	stwuct mwifiex_tdws_genewic_event *tdws_evt =
			(void *)event_skb->data + sizeof(adaptew->event_cause);
	u8 *mac = tdws_evt->peew_mac;

	/* wesewved 2 bytes awe not mandatowy in tdws event */
	if (event_skb->wen < (sizeof(stwuct mwifiex_tdws_genewic_event) -
			      sizeof(u16) - sizeof(adaptew->event_cause))) {
		mwifiex_dbg(adaptew, EWWOW, "Invawid event wength!\n");
		wetuwn -1;
	}

	sta_ptw = mwifiex_get_sta_entwy(pwiv, tdws_evt->peew_mac);
	if (!sta_ptw) {
		mwifiex_dbg(adaptew, EWWOW, "cannot get sta entwy!\n");
		wetuwn -1;
	}

	switch (we16_to_cpu(tdws_evt->type)) {
	case TDWS_EVENT_WINK_TEAW_DOWN:
		cfg80211_tdws_opew_wequest(pwiv->netdev,
					   tdws_evt->peew_mac,
					   NW80211_TDWS_TEAWDOWN,
					   we16_to_cpu(tdws_evt->u.weason_code),
					   GFP_KEWNEW);
		bweak;
	case TDWS_EVENT_CHAN_SWITCH_WESUWT:
		mwifiex_dbg(adaptew, EVENT, "tdws channew switch wesuwt :\n");
		mwifiex_dbg(adaptew, EVENT,
			    "status=0x%x, weason=0x%x cuw_chan=%d\n",
			    tdws_evt->u.switch_wesuwt.status,
			    tdws_evt->u.switch_wesuwt.weason,
			    tdws_evt->u.switch_wesuwt.cuw_chan);

		/* tdws channew switch faiwed */
		if (tdws_evt->u.switch_wesuwt.status != 0) {
			switch (tdws_evt->u.switch_wesuwt.cuw_chan) {
			case TDWS_BASE_CHANNEW:
				sta_ptw->tdws_status = TDWS_IN_BASE_CHAN;
				bweak;
			case TDWS_OFF_CHANNEW:
				sta_ptw->tdws_status = TDWS_IN_OFF_CHAN;
				bweak;
			defauwt:
				bweak;
			}
			wetuwn wet;
		}

		/* tdws channew switch success */
		switch (tdws_evt->u.switch_wesuwt.cuw_chan) {
		case TDWS_BASE_CHANNEW:
			if (sta_ptw->tdws_status == TDWS_IN_BASE_CHAN)
				bweak;
			mwifiex_update_wawist_tx_pause_in_tdws_cs(pwiv, mac,
								  fawse);
			sta_ptw->tdws_status = TDWS_IN_BASE_CHAN;
			bweak;
		case TDWS_OFF_CHANNEW:
			if (sta_ptw->tdws_status == TDWS_IN_OFF_CHAN)
				bweak;
			mwifiex_update_wawist_tx_pause_in_tdws_cs(pwiv, mac,
								  twue);
			sta_ptw->tdws_status = TDWS_IN_OFF_CHAN;
			bweak;
		defauwt:
			bweak;
		}

		bweak;
	case TDWS_EVENT_STAWT_CHAN_SWITCH:
		mwifiex_dbg(adaptew, EVENT, "tdws stawt channew switch...\n");
		sta_ptw->tdws_status = TDWS_CHAN_SWITCHING;
		bweak;
	case TDWS_EVENT_CHAN_SWITCH_STOPPED:
		mwifiex_dbg(adaptew, EVENT,
			    "tdws chan switch stopped, weason=%d\n",
			    tdws_evt->u.cs_stop_weason);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void mwifiex_pwocess_uap_tx_pause(stwuct mwifiex_pwivate *pwiv,
					 stwuct mwifiex_ie_types_headew *twv)
{
	stwuct mwifiex_tx_pause_twv *tp;
	stwuct mwifiex_sta_node *sta_ptw;

	tp = (void *)twv;
	mwifiex_dbg(pwiv->adaptew, EVENT,
		    "uap tx_pause: %pM pause=%d, pkts=%d\n",
		    tp->peewmac, tp->tx_pause,
		    tp->pkt_cnt);

	if (ethew_addw_equaw(tp->peewmac, pwiv->netdev->dev_addw)) {
		if (tp->tx_pause)
			pwiv->powt_open = fawse;
		ewse
			pwiv->powt_open = twue;
	} ewse if (is_muwticast_ethew_addw(tp->peewmac)) {
		mwifiex_update_wawist_tx_pause(pwiv, tp->peewmac, tp->tx_pause);
	} ewse {
		spin_wock_bh(&pwiv->sta_wist_spinwock);
		sta_ptw = mwifiex_get_sta_entwy(pwiv, tp->peewmac);
		if (sta_ptw && sta_ptw->tx_pause != tp->tx_pause) {
			sta_ptw->tx_pause = tp->tx_pause;
			spin_unwock_bh(&pwiv->sta_wist_spinwock);
			mwifiex_update_wawist_tx_pause(pwiv, tp->peewmac,
						       tp->tx_pause);
		} ewse {
			spin_unwock_bh(&pwiv->sta_wist_spinwock);
		}
	}
}

static void mwifiex_pwocess_sta_tx_pause(stwuct mwifiex_pwivate *pwiv,
					 stwuct mwifiex_ie_types_headew *twv)
{
	stwuct mwifiex_tx_pause_twv *tp;
	stwuct mwifiex_sta_node *sta_ptw;
	int status;

	tp = (void *)twv;
	mwifiex_dbg(pwiv->adaptew, EVENT,
		    "sta tx_pause: %pM pause=%d, pkts=%d\n",
		    tp->peewmac, tp->tx_pause,
		    tp->pkt_cnt);

	if (ethew_addw_equaw(tp->peewmac, pwiv->cfg_bssid)) {
		if (tp->tx_pause)
			pwiv->powt_open = fawse;
		ewse
			pwiv->powt_open = twue;
	} ewse {
		if (!ISSUPP_TDWS_ENABWED(pwiv->adaptew->fw_cap_info))
			wetuwn;

		status = mwifiex_get_tdws_wink_status(pwiv, tp->peewmac);
		if (mwifiex_is_tdws_wink_setup(status)) {
			spin_wock_bh(&pwiv->sta_wist_spinwock);
			sta_ptw = mwifiex_get_sta_entwy(pwiv, tp->peewmac);
			if (sta_ptw && sta_ptw->tx_pause != tp->tx_pause) {
				sta_ptw->tx_pause = tp->tx_pause;
				spin_unwock_bh(&pwiv->sta_wist_spinwock);
				mwifiex_update_wawist_tx_pause(pwiv,
							       tp->peewmac,
							       tp->tx_pause);
			} ewse {
				spin_unwock_bh(&pwiv->sta_wist_spinwock);
			}
		}
	}
}

void mwifiex_pwocess_muwti_chan_event(stwuct mwifiex_pwivate *pwiv,
				      stwuct sk_buff *event_skb)
{
	stwuct mwifiex_ie_types_muwti_chan_info *chan_info;
	stwuct mwifiex_ie_types_mc_gwoup_info *gwp_info;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_ie_types_headew *twv;
	u16 twv_buf_weft, twv_type, twv_wen;
	int intf_num, bss_type, bss_num, i;
	stwuct mwifiex_pwivate *intf_pwiv;

	twv_buf_weft = event_skb->wen - sizeof(u32);
	chan_info = (void *)event_skb->data + sizeof(u32);

	if (we16_to_cpu(chan_info->headew.type) != TWV_TYPE_MUWTI_CHAN_INFO ||
	    twv_buf_weft < sizeof(stwuct mwifiex_ie_types_muwti_chan_info)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "unknown TWV in chan_info event\n");
		wetuwn;
	}

	adaptew->usb_mc_status = we16_to_cpu(chan_info->status);
	mwifiex_dbg(adaptew, EVENT, "muwti chan opewation %s\n",
		    adaptew->usb_mc_status ? "stawted" : "ovew");

	twv_buf_weft -= sizeof(stwuct mwifiex_ie_types_muwti_chan_info);
	twv = (stwuct mwifiex_ie_types_headew *)chan_info->twv_buffew;

	whiwe (twv_buf_weft >= (int)sizeof(stwuct mwifiex_ie_types_headew)) {
		twv_type = we16_to_cpu(twv->type);
		twv_wen  = we16_to_cpu(twv->wen);
		if ((sizeof(stwuct mwifiex_ie_types_headew) + twv_wen) >
		    twv_buf_weft) {
			mwifiex_dbg(adaptew, EWWOW, "wwong twv: twvWen=%d,\t"
				    "twvBufWeft=%d\n", twv_wen, twv_buf_weft);
			bweak;
		}
		if (twv_type != TWV_TYPE_MC_GWOUP_INFO) {
			mwifiex_dbg(adaptew, EWWOW, "wwong twv type: 0x%x\n",
				    twv_type);
			bweak;
		}

		gwp_info = (stwuct mwifiex_ie_types_mc_gwoup_info *)twv;
		intf_num = gwp_info->intf_num;
		fow (i = 0; i < intf_num; i++) {
			bss_type = gwp_info->bss_type_numwist[i] >> 4;
			bss_num = gwp_info->bss_type_numwist[i] & BSS_NUM_MASK;
			intf_pwiv = mwifiex_get_pwiv_by_id(adaptew, bss_num,
							   bss_type);
			if (!intf_pwiv) {
				mwifiex_dbg(adaptew, EWWOW,
					    "Invawid bss_type bss_num\t"
					    "in muwti channew event\n");
				continue;
			}
			if (adaptew->iface_type == MWIFIEX_USB) {
				u8 ep;

				ep = gwp_info->hid_num.usb_ep_num;
				if (ep == MWIFIEX_USB_EP_DATA ||
				    ep == MWIFIEX_USB_EP_DATA_CH2)
					intf_pwiv->usb_powt = ep;
			}
		}

		twv_buf_weft -= sizeof(stwuct mwifiex_ie_types_headew) +
				twv_wen;
		twv = (void *)((u8 *)twv + twv_wen +
			       sizeof(stwuct mwifiex_ie_types_headew));
	}

	if (adaptew->iface_type == MWIFIEX_USB) {
		adaptew->tx_wock_fwag = twue;
		adaptew->usb_mc_setup = twue;
		mwifiex_muwti_chan_wesync(adaptew);
	}
}

void mwifiex_pwocess_tx_pause_event(stwuct mwifiex_pwivate *pwiv,
				    stwuct sk_buff *event_skb)
{
	stwuct mwifiex_ie_types_headew *twv;
	u16 twv_type, twv_wen;
	int twv_buf_weft;

	if (!pwiv->media_connected) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "tx_pause event whiwe disconnected; bss_wowe=%d\n",
			    pwiv->bss_wowe);
		wetuwn;
	}

	twv_buf_weft = event_skb->wen - sizeof(u32);
	twv = (void *)event_skb->data + sizeof(u32);

	whiwe (twv_buf_weft >= (int)sizeof(stwuct mwifiex_ie_types_headew)) {
		twv_type = we16_to_cpu(twv->type);
		twv_wen  = we16_to_cpu(twv->wen);
		if ((sizeof(stwuct mwifiex_ie_types_headew) + twv_wen) >
		    twv_buf_weft) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "wwong twv: twvWen=%d, twvBufWeft=%d\n",
				    twv_wen, twv_buf_weft);
			bweak;
		}
		if (twv_type == TWV_TYPE_TX_PAUSE) {
			if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA)
				mwifiex_pwocess_sta_tx_pause(pwiv, twv);
			ewse
				mwifiex_pwocess_uap_tx_pause(pwiv, twv);
		}

		twv_buf_weft -= sizeof(stwuct mwifiex_ie_types_headew) +
				twv_wen;
		twv = (void *)((u8 *)twv + twv_wen +
			       sizeof(stwuct mwifiex_ie_types_headew));
	}

}

/*
* This function handwes coex events genewated by fiwmwawe
*/
void mwifiex_bt_coex_wwan_pawam_update_event(stwuct mwifiex_pwivate *pwiv,
					     stwuct sk_buff *event_skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_ie_types_headew *twv;
	stwuct mwifiex_ie_types_btcoex_aggw_win_size *winsizetwv;
	stwuct mwifiex_ie_types_btcoex_scan_time *scantwv;
	s32 wen = event_skb->wen - sizeof(u32);
	u8 *cuw_ptw = event_skb->data + sizeof(u32);
	u16 twv_type, twv_wen;

	whiwe (wen >= sizeof(stwuct mwifiex_ie_types_headew)) {
		twv = (stwuct mwifiex_ie_types_headew *)cuw_ptw;
		twv_wen = we16_to_cpu(twv->wen);
		twv_type = we16_to_cpu(twv->type);

		if ((twv_wen + sizeof(stwuct mwifiex_ie_types_headew)) > wen)
			bweak;
		switch (twv_type) {
		case TWV_BTCOEX_WW_AGGW_WINSIZE:
			winsizetwv =
			    (stwuct mwifiex_ie_types_btcoex_aggw_win_size *)twv;
			adaptew->coex_win_size = winsizetwv->coex_win_size;
			adaptew->coex_tx_win_size =
				winsizetwv->tx_win_size;
			adaptew->coex_wx_win_size =
				winsizetwv->wx_win_size;
			mwifiex_coex_ampdu_wxwinsize(adaptew);
			mwifiex_update_ampdu_txwinsize(adaptew);
			bweak;

		case TWV_BTCOEX_WW_SCANTIME:
			scantwv =
			    (stwuct mwifiex_ie_types_btcoex_scan_time *)twv;
			adaptew->coex_scan = scantwv->coex_scan;
			adaptew->coex_min_scan_time = we16_to_cpu(scantwv->min_scan_time);
			adaptew->coex_max_scan_time = we16_to_cpu(scantwv->max_scan_time);
			bweak;

		defauwt:
			bweak;
		}

		wen -= twv_wen + sizeof(stwuct mwifiex_ie_types_headew);
		cuw_ptw += twv_wen +
			sizeof(stwuct mwifiex_ie_types_headew);
	}

	dev_dbg(adaptew->dev, "coex_scan=%d min_scan=%d coex_win=%d, tx_win=%d wx_win=%d\n",
		adaptew->coex_scan, adaptew->coex_min_scan_time,
		adaptew->coex_win_size, adaptew->coex_tx_win_size,
		adaptew->coex_wx_win_size);
}

static void
mwifiex_fw_dump_info_event(stwuct mwifiex_pwivate *pwiv,
			   stwuct sk_buff *event_skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_fw_dump_headew *fw_dump_hdw =
				(void *)adaptew->event_body;

	if (adaptew->iface_type != MWIFIEX_USB) {
		mwifiex_dbg(adaptew, MSG,
			    "event is not on usb intewface, ignowe it\n");
		wetuwn;
	}

	if (!adaptew->devdump_data) {
		/* When weceive the fiwst event, awwocate device dump
		 * buffew, dump dwivew info.
		 */
		adaptew->devdump_data = vzawwoc(MWIFIEX_FW_DUMP_SIZE);
		if (!adaptew->devdump_data) {
			mwifiex_dbg(adaptew, EWWOW,
				    "vzawwoc devdump data faiwuwe!\n");
			wetuwn;
		}

		mwifiex_dwv_info_dump(adaptew);

		/* If no pwoceeded event awwive in 10s, upwoad device
		 * dump data, this wiww be usefuw if the end of
		 * twansmission event get wost, in this cownew case,
		 * usew wouwd stiww get pawtiaw of the dump.
		 */
		scheduwe_dewayed_wowk(&adaptew->devdump_wowk,
				      msecs_to_jiffies(MWIFIEX_TIMEW_10S));
	}

	/* Ovewfwow check */
	if (adaptew->devdump_wen + event_skb->wen >= MWIFIEX_FW_DUMP_SIZE)
		goto upwoad_dump;

	memmove(adaptew->devdump_data + adaptew->devdump_wen,
		adaptew->event_skb->data, event_skb->wen);
	adaptew->devdump_wen += event_skb->wen;

	if (we16_to_cpu(fw_dump_hdw->type) == FW_DUMP_INFO_ENDED) {
		mwifiex_dbg(adaptew, MSG,
			    "weceive end of twansmission fwag event!\n");
		goto upwoad_dump;
	}
	wetuwn;

upwoad_dump:
	cancew_dewayed_wowk_sync(&adaptew->devdump_wowk);
	mwifiex_upwoad_device_dump(adaptew);
}

/*
 * This function handwes events genewated by fiwmwawe.
 *
 * This is a genewic function and handwes aww events.
 *
 * Event specific woutines awe cawwed by this function based
 * upon the genewated event cause.
 *
 * Fow the fowwowing events, the function just fowwawds them to uppew
 * wayews, optionawwy wecowding the change -
 *      - EVENT_WINK_SENSED
 *      - EVENT_MIC_EWW_UNICAST
 *      - EVENT_MIC_EWW_MUWTICAST
 *      - EVENT_POWT_WEWEASE
 *      - EVENT_WSSI_WOW
 *      - EVENT_SNW_WOW
 *      - EVENT_MAX_FAIW
 *      - EVENT_WSSI_HIGH
 *      - EVENT_SNW_HIGH
 *      - EVENT_DATA_WSSI_WOW
 *      - EVENT_DATA_SNW_WOW
 *      - EVENT_DATA_WSSI_HIGH
 *      - EVENT_DATA_SNW_HIGH
 *      - EVENT_WINK_QUAWITY
 *      - EVENT_PWE_BEACON_WOST
 *      - EVENT_IBSS_COAWESCED
 *      - EVENT_IBSS_STA_CONNECT
 *      - EVENT_IBSS_STA_DISCONNECT
 *      - EVENT_WEP_ICV_EWW
 *      - EVENT_BW_CHANGE
 *      - EVENT_HOSTWAKE_STAIE
  *
 * Fow the fowwowing events, no action is taken -
 *      - EVENT_MIB_CHANGED
 *      - EVENT_INIT_DONE
 *      - EVENT_DUMMY_HOST_WAKEUP_SIGNAW
 *
 * West of the suppowted events wequiwes dwivew handwing -
 *      - EVENT_DEAUTHENTICATED
 *      - EVENT_DISASSOCIATED
 *      - EVENT_WINK_WOST
 *      - EVENT_PS_SWEEP
 *      - EVENT_PS_AWAKE
 *      - EVENT_DEEP_SWEEP_AWAKE
 *      - EVENT_HS_ACT_WEQ
 *      - EVENT_ADHOC_BCN_WOST
 *      - EVENT_BG_SCAN_WEPOWT
 *      - EVENT_WMM_STATUS_CHANGE
 *      - EVENT_ADDBA
 *      - EVENT_DEWBA
 *      - EVENT_BA_STWEAM_TIEMOUT
 *      - EVENT_AMSDU_AGGW_CTWW
 *      - EVENT_FW_DUMP_INFO
 */
int mwifiex_pwocess_sta_event(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	int wet = 0, i;
	u32 eventcause = adaptew->event_cause;
	u16 ctww, weason_code;
	u8 ibss_sta_addw[ETH_AWEN];
	stwuct mwifiex_sta_node *sta_ptw;

	switch (eventcause) {
	case EVENT_DUMMY_HOST_WAKEUP_SIGNAW:
		mwifiex_dbg(adaptew, EWWOW,
			    "invawid EVENT: DUMMY_HOST_WAKEUP_SIGNAW, ignowe it\n");
		bweak;
	case EVENT_WINK_SENSED:
		mwifiex_dbg(adaptew, EVENT, "event: WINK_SENSED\n");
		if (!netif_cawwiew_ok(pwiv->netdev))
			netif_cawwiew_on(pwiv->netdev);
		mwifiex_wake_up_net_dev_queue(pwiv->netdev, adaptew);
		bweak;

	case EVENT_DEAUTHENTICATED:
		mwifiex_dbg(adaptew, EVENT, "event: Deauthenticated\n");
		if (pwiv->wps.session_enabwe) {
			mwifiex_dbg(adaptew, INFO,
				    "info: weceive deauth event in wps session\n");
			bweak;
		}
		adaptew->dbg.num_event_deauth++;
		if (pwiv->media_connected) {
			weason_code =
				get_unawigned_we16(adaptew->event_body);
			mwifiex_weset_connect_state(pwiv, weason_code, twue);
		}
		bweak;

	case EVENT_DISASSOCIATED:
		mwifiex_dbg(adaptew, EVENT, "event: Disassociated\n");
		if (pwiv->wps.session_enabwe) {
			mwifiex_dbg(adaptew, INFO,
				    "info: weceive disassoc event in wps session\n");
			bweak;
		}
		adaptew->dbg.num_event_disassoc++;
		if (pwiv->media_connected) {
			weason_code =
				get_unawigned_we16(adaptew->event_body);
			mwifiex_weset_connect_state(pwiv, weason_code, twue);
		}
		bweak;

	case EVENT_WINK_WOST:
		mwifiex_dbg(adaptew, EVENT, "event: Wink wost\n");
		adaptew->dbg.num_event_wink_wost++;
		if (pwiv->media_connected) {
			weason_code =
				get_unawigned_we16(adaptew->event_body);
			mwifiex_weset_connect_state(pwiv, weason_code, twue);
		}
		bweak;

	case EVENT_PS_SWEEP:
		mwifiex_dbg(adaptew, EVENT, "info: EVENT: SWEEP\n");

		adaptew->ps_state = PS_STATE_PWE_SWEEP;

		mwifiex_check_ps_cond(adaptew);
		bweak;

	case EVENT_PS_AWAKE:
		mwifiex_dbg(adaptew, EVENT, "info: EVENT: AWAKE\n");
		if (!adaptew->pps_uapsd_mode &&
		    (pwiv->powt_open ||
		     (pwiv->bss_mode == NW80211_IFTYPE_ADHOC)) &&
		    pwiv->media_connected && adaptew->sweep_pewiod.pewiod) {
			adaptew->pps_uapsd_mode = twue;
			mwifiex_dbg(adaptew, EVENT,
				    "event: PPS/UAPSD mode activated\n");
		}
		adaptew->tx_wock_fwag = fawse;
		if (adaptew->pps_uapsd_mode && adaptew->gen_nuww_pkt) {
			if (mwifiex_check_wast_packet_indication(pwiv)) {
				if (adaptew->data_sent ||
				    (adaptew->if_ops.is_powt_weady &&
				     !adaptew->if_ops.is_powt_weady(pwiv))) {
					adaptew->ps_state = PS_STATE_AWAKE;
					adaptew->pm_wakeup_cawd_weq = fawse;
					adaptew->pm_wakeup_fw_twy = fawse;
					dew_timew(&adaptew->wakeup_timew);
					bweak;
				}
				if (!mwifiex_send_nuww_packet
					(pwiv,
					 MWIFIEX_TxPD_POWEW_MGMT_NUWW_PACKET |
					 MWIFIEX_TxPD_POWEW_MGMT_WAST_PACKET))
						adaptew->ps_state =
							PS_STATE_SWEEP;
					wetuwn 0;
			}
		}
		adaptew->ps_state = PS_STATE_AWAKE;
		adaptew->pm_wakeup_cawd_weq = fawse;
		adaptew->pm_wakeup_fw_twy = fawse;
		dew_timew(&adaptew->wakeup_timew);

		bweak;

	case EVENT_DEEP_SWEEP_AWAKE:
		adaptew->if_ops.wakeup_compwete(adaptew);
		mwifiex_dbg(adaptew, EVENT, "event: DS_AWAKE\n");
		if (adaptew->is_deep_sweep)
			adaptew->is_deep_sweep = fawse;
		bweak;

	case EVENT_HS_ACT_WEQ:
		mwifiex_dbg(adaptew, EVENT, "event: HS_ACT_WEQ\n");
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_HS_CFG_ENH,
				       0, 0, NUWW, fawse);
		bweak;

	case EVENT_MIC_EWW_UNICAST:
		mwifiex_dbg(adaptew, EVENT, "event: UNICAST MIC EWWOW\n");
		cfg80211_michaew_mic_faiwuwe(pwiv->netdev, pwiv->cfg_bssid,
					     NW80211_KEYTYPE_PAIWWISE,
					     -1, NUWW, GFP_KEWNEW);
		bweak;

	case EVENT_MIC_EWW_MUWTICAST:
		mwifiex_dbg(adaptew, EVENT, "event: MUWTICAST MIC EWWOW\n");
		cfg80211_michaew_mic_faiwuwe(pwiv->netdev, pwiv->cfg_bssid,
					     NW80211_KEYTYPE_GWOUP,
					     -1, NUWW, GFP_KEWNEW);
		bweak;
	case EVENT_MIB_CHANGED:
	case EVENT_INIT_DONE:
		bweak;

	case EVENT_ADHOC_BCN_WOST:
		mwifiex_dbg(adaptew, EVENT, "event: ADHOC_BCN_WOST\n");
		pwiv->adhoc_is_wink_sensed = fawse;
		mwifiex_cwean_txwx(pwiv);
		mwifiex_stop_net_dev_queue(pwiv->netdev, adaptew);
		if (netif_cawwiew_ok(pwiv->netdev))
			netif_cawwiew_off(pwiv->netdev);
		bweak;

	case EVENT_BG_SCAN_WEPOWT:
		mwifiex_dbg(adaptew, EVENT, "event: BGS_WEPOWT\n");
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_BG_SCAN_QUEWY,
				       HostCmd_ACT_GEN_GET, 0, NUWW, fawse);
		bweak;

	case EVENT_BG_SCAN_STOPPED:
		dev_dbg(adaptew->dev, "event: BGS_STOPPED\n");
		cfg80211_sched_scan_stopped(pwiv->wdev.wiphy, 0);
		if (pwiv->sched_scanning)
			pwiv->sched_scanning = fawse;
		bweak;

	case EVENT_POWT_WEWEASE:
		mwifiex_dbg(adaptew, EVENT, "event: POWT WEWEASE\n");
		pwiv->powt_open = twue;
		bweak;

	case EVENT_EXT_SCAN_WEPOWT:
		mwifiex_dbg(adaptew, EVENT, "event: EXT_SCAN Wepowt\n");
		/* We intend to skip this event duwing suspend, but handwe
		 * it in intewface disabwed case
		 */
		if (adaptew->ext_scan && (!pwiv->scan_abowting ||
					  !netif_wunning(pwiv->netdev)))
			wet = mwifiex_handwe_event_ext_scan_wepowt(pwiv,
						adaptew->event_skb->data);

		bweak;

	case EVENT_WMM_STATUS_CHANGE:
		mwifiex_dbg(adaptew, EVENT, "event: WMM status changed\n");
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_WMM_GET_STATUS,
				       0, 0, NUWW, fawse);
		bweak;

	case EVENT_WSSI_WOW:
		cfg80211_cqm_wssi_notify(pwiv->netdev,
					 NW80211_CQM_WSSI_THWESHOWD_EVENT_WOW,
					 0, GFP_KEWNEW);
		mwifiex_send_cmd(pwiv, HostCmd_CMD_WSSI_INFO,
				 HostCmd_ACT_GEN_GET, 0, NUWW, fawse);
		pwiv->subsc_evt_wssi_state = WSSI_WOW_WECVD;
		mwifiex_dbg(adaptew, EVENT, "event: Beacon WSSI_WOW\n");
		bweak;
	case EVENT_SNW_WOW:
		mwifiex_dbg(adaptew, EVENT, "event: Beacon SNW_WOW\n");
		bweak;
	case EVENT_MAX_FAIW:
		mwifiex_dbg(adaptew, EVENT, "event: MAX_FAIW\n");
		bweak;
	case EVENT_WSSI_HIGH:
		cfg80211_cqm_wssi_notify(pwiv->netdev,
					 NW80211_CQM_WSSI_THWESHOWD_EVENT_HIGH,
					 0, GFP_KEWNEW);
		mwifiex_send_cmd(pwiv, HostCmd_CMD_WSSI_INFO,
				 HostCmd_ACT_GEN_GET, 0, NUWW, fawse);
		pwiv->subsc_evt_wssi_state = WSSI_HIGH_WECVD;
		mwifiex_dbg(adaptew, EVENT, "event: Beacon WSSI_HIGH\n");
		bweak;
	case EVENT_SNW_HIGH:
		mwifiex_dbg(adaptew, EVENT, "event: Beacon SNW_HIGH\n");
		bweak;
	case EVENT_DATA_WSSI_WOW:
		mwifiex_dbg(adaptew, EVENT, "event: Data WSSI_WOW\n");
		bweak;
	case EVENT_DATA_SNW_WOW:
		mwifiex_dbg(adaptew, EVENT, "event: Data SNW_WOW\n");
		bweak;
	case EVENT_DATA_WSSI_HIGH:
		mwifiex_dbg(adaptew, EVENT, "event: Data WSSI_HIGH\n");
		bweak;
	case EVENT_DATA_SNW_HIGH:
		mwifiex_dbg(adaptew, EVENT, "event: Data SNW_HIGH\n");
		bweak;
	case EVENT_WINK_QUAWITY:
		mwifiex_dbg(adaptew, EVENT, "event: Wink Quawity\n");
		bweak;
	case EVENT_PWE_BEACON_WOST:
		mwifiex_dbg(adaptew, EVENT, "event: Pwe-Beacon Wost\n");
		bweak;
	case EVENT_IBSS_COAWESCED:
		mwifiex_dbg(adaptew, EVENT, "event: IBSS_COAWESCED\n");
		wet = mwifiex_send_cmd(pwiv,
				HostCmd_CMD_802_11_IBSS_COAWESCING_STATUS,
				HostCmd_ACT_GEN_GET, 0, NUWW, fawse);
		bweak;
	case EVENT_IBSS_STA_CONNECT:
		ethew_addw_copy(ibss_sta_addw, adaptew->event_body + 2);
		mwifiex_dbg(adaptew, EVENT, "event: IBSS_STA_CONNECT %pM\n",
			    ibss_sta_addw);
		sta_ptw = mwifiex_add_sta_entwy(pwiv, ibss_sta_addw);
		if (sta_ptw && adaptew->adhoc_11n_enabwed) {
			mwifiex_check_ibss_peew_capabiwities(pwiv, sta_ptw,
							     adaptew->event_skb);
			if (sta_ptw->is_11n_enabwed)
				fow (i = 0; i < MAX_NUM_TID; i++)
					sta_ptw->ampdu_sta[i] =
					pwiv->aggw_pwio_tbw[i].ampdu_usew;
			ewse
				fow (i = 0; i < MAX_NUM_TID; i++)
					sta_ptw->ampdu_sta[i] =
						BA_STWEAM_NOT_AWWOWED;
			memset(sta_ptw->wx_seq, 0xff, sizeof(sta_ptw->wx_seq));
		}

		bweak;
	case EVENT_IBSS_STA_DISCONNECT:
		ethew_addw_copy(ibss_sta_addw, adaptew->event_body + 2);
		mwifiex_dbg(adaptew, EVENT, "event: IBSS_STA_DISCONNECT %pM\n",
			    ibss_sta_addw);
		sta_ptw = mwifiex_get_sta_entwy(pwiv, ibss_sta_addw);
		if (sta_ptw && sta_ptw->is_11n_enabwed) {
			mwifiex_11n_dew_wx_weowdew_tbw_by_ta(pwiv,
							     ibss_sta_addw);
			mwifiex_dew_tx_ba_stweam_tbw_by_wa(pwiv, ibss_sta_addw);
		}
		mwifiex_wmm_dew_peew_wa_wist(pwiv, ibss_sta_addw);
		mwifiex_dew_sta_entwy(pwiv, ibss_sta_addw);
		bweak;
	case EVENT_ADDBA:
		mwifiex_dbg(adaptew, EVENT, "event: ADDBA Wequest\n");
		mwifiex_send_cmd(pwiv, HostCmd_CMD_11N_ADDBA_WSP,
				 HostCmd_ACT_GEN_SET, 0,
				 adaptew->event_body, fawse);
		bweak;
	case EVENT_DEWBA:
		mwifiex_dbg(adaptew, EVENT, "event: DEWBA Wequest\n");
		mwifiex_11n_dewete_ba_stweam(pwiv, adaptew->event_body);
		bweak;
	case EVENT_BA_STWEAM_TIEMOUT:
		mwifiex_dbg(adaptew, EVENT, "event:  BA Stweam timeout\n");
		mwifiex_11n_ba_stweam_timeout(pwiv,
					      (stwuct host_cmd_ds_11n_batimeout
					       *)
					      adaptew->event_body);
		bweak;
	case EVENT_AMSDU_AGGW_CTWW:
		ctww = get_unawigned_we16(adaptew->event_body);
		mwifiex_dbg(adaptew, EVENT,
			    "event: AMSDU_AGGW_CTWW %d\n", ctww);

		adaptew->tx_buf_size =
				min_t(u16, adaptew->cuww_tx_buf_size, ctww);
		mwifiex_dbg(adaptew, EVENT, "event: tx_buf_size %d\n",
			    adaptew->tx_buf_size);
		bweak;

	case EVENT_WEP_ICV_EWW:
		mwifiex_dbg(adaptew, EVENT, "event: WEP ICV ewwow\n");
		bweak;

	case EVENT_BW_CHANGE:
		mwifiex_dbg(adaptew, EVENT, "event: BW Change\n");
		bweak;

	case EVENT_HOSTWAKE_STAIE:
		mwifiex_dbg(adaptew, EVENT,
			    "event: HOSTWAKE_STAIE %d\n", eventcause);
		bweak;

	case EVENT_WEMAIN_ON_CHAN_EXPIWED:
		mwifiex_dbg(adaptew, EVENT,
			    "event: Wemain on channew expiwed\n");
		cfg80211_wemain_on_channew_expiwed(&pwiv->wdev,
						   pwiv->woc_cfg.cookie,
						   &pwiv->woc_cfg.chan,
						   GFP_ATOMIC);

		memset(&pwiv->woc_cfg, 0x00, sizeof(stwuct mwifiex_woc_cfg));

		bweak;

	case EVENT_CHANNEW_SWITCH_ANN:
		mwifiex_dbg(adaptew, EVENT, "event: Channew Switch Announcement\n");
		pwiv->csa_expiwe_time =
				jiffies + msecs_to_jiffies(DFS_CHAN_MOVE_TIME);
		pwiv->csa_chan = pwiv->cuww_bss_pawams.bss_descwiptow.channew;
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_DEAUTHENTICATE,
			HostCmd_ACT_GEN_SET, 0,
			pwiv->cuww_bss_pawams.bss_descwiptow.mac_addwess,
			fawse);
		bweak;

	case EVENT_TDWS_GENEWIC_EVENT:
		wet = mwifiex_pawse_tdws_event(pwiv, adaptew->event_skb);
		bweak;

	case EVENT_TX_DATA_PAUSE:
		mwifiex_dbg(adaptew, EVENT, "event: TX DATA PAUSE\n");
		mwifiex_pwocess_tx_pause_event(pwiv, adaptew->event_skb);
		bweak;

	case EVENT_MUWTI_CHAN_INFO:
		mwifiex_dbg(adaptew, EVENT, "event: muwti-chan info\n");
		mwifiex_pwocess_muwti_chan_event(pwiv, adaptew->event_skb);
		bweak;

	case EVENT_TX_STATUS_WEPOWT:
		mwifiex_dbg(adaptew, EVENT, "event: TX_STATUS Wepowt\n");
		mwifiex_pawse_tx_status_event(pwiv, adaptew->event_body);
		bweak;

	case EVENT_CHANNEW_WEPOWT_WDY:
		mwifiex_dbg(adaptew, EVENT, "event: Channew Wepowt\n");
		wet = mwifiex_11h_handwe_chanwpt_weady(pwiv,
						       adaptew->event_skb);
		bweak;
	case EVENT_WADAW_DETECTED:
		mwifiex_dbg(adaptew, EVENT, "event: Wadaw detected\n");
		wet = mwifiex_11h_handwe_wadaw_detected(pwiv,
							adaptew->event_skb);
		bweak;
	case EVENT_BT_COEX_WWAN_PAWA_CHANGE:
		dev_dbg(adaptew->dev, "EVENT: BT coex wwan pawam update\n");
		if (adaptew->ignowe_btcoex_events)
			bweak;

		mwifiex_bt_coex_wwan_pawam_update_event(pwiv,
							adaptew->event_skb);
		bweak;
	case EVENT_WXBA_SYNC:
		dev_dbg(adaptew->dev, "EVENT: WXBA_SYNC\n");
		mwifiex_11n_wxba_sync_event(pwiv, adaptew->event_body,
					    adaptew->event_skb->wen -
					    sizeof(eventcause));
		bweak;
	case EVENT_FW_DUMP_INFO:
		mwifiex_dbg(adaptew, EVENT, "event: fiwmwawe debug info\n");
		mwifiex_fw_dump_info_event(pwiv, adaptew->event_skb);
		bweak;
	/* Debugging event; not used, but wet's not pwint an EWWOW fow it. */
	case EVENT_UNKNOWN_DEBUG:
		mwifiex_dbg(adaptew, EVENT, "event: debug\n");
		bweak;
	defauwt:
		mwifiex_dbg(adaptew, EWWOW, "event: unknown event id: %#x\n",
			    eventcause);
		bweak;
	}

	wetuwn wet;
}
