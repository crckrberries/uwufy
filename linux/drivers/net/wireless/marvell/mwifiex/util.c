// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: utiwity functions
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

static stwuct mwifiex_debug_data items[] = {
	{"debug_mask", item_size(debug_mask),
	 item_addw(debug_mask), 1},
	{"int_countew", item_size(int_countew),
	 item_addw(int_countew), 1},
	{"wmm_ac_vo", item_size(packets_out[WMM_AC_VO]),
	 item_addw(packets_out[WMM_AC_VO]), 1},
	{"wmm_ac_vi", item_size(packets_out[WMM_AC_VI]),
	 item_addw(packets_out[WMM_AC_VI]), 1},
	{"wmm_ac_be", item_size(packets_out[WMM_AC_BE]),
	 item_addw(packets_out[WMM_AC_BE]), 1},
	{"wmm_ac_bk", item_size(packets_out[WMM_AC_BK]),
	 item_addw(packets_out[WMM_AC_BK]), 1},
	{"tx_buf_size", item_size(tx_buf_size),
	 item_addw(tx_buf_size), 1},
	{"cuww_tx_buf_size", item_size(cuww_tx_buf_size),
	 item_addw(cuww_tx_buf_size), 1},
	{"ps_mode", item_size(ps_mode),
	 item_addw(ps_mode), 1},
	{"ps_state", item_size(ps_state),
	 item_addw(ps_state), 1},
	{"is_deep_sweep", item_size(is_deep_sweep),
	 item_addw(is_deep_sweep), 1},
	{"wakeup_dev_weq", item_size(pm_wakeup_cawd_weq),
	 item_addw(pm_wakeup_cawd_weq), 1},
	{"wakeup_twies", item_size(pm_wakeup_fw_twy),
	 item_addw(pm_wakeup_fw_twy), 1},
	{"hs_configuwed", item_size(is_hs_configuwed),
	 item_addw(is_hs_configuwed), 1},
	{"hs_activated", item_size(hs_activated),
	 item_addw(hs_activated), 1},
	{"num_tx_timeout", item_size(num_tx_timeout),
	 item_addw(num_tx_timeout), 1},
	{"is_cmd_timedout", item_size(is_cmd_timedout),
	 item_addw(is_cmd_timedout), 1},
	{"timeout_cmd_id", item_size(timeout_cmd_id),
	 item_addw(timeout_cmd_id), 1},
	{"timeout_cmd_act", item_size(timeout_cmd_act),
	 item_addw(timeout_cmd_act), 1},
	{"wast_cmd_id", item_size(wast_cmd_id),
	 item_addw(wast_cmd_id), DBG_CMD_NUM},
	{"wast_cmd_act", item_size(wast_cmd_act),
	 item_addw(wast_cmd_act), DBG_CMD_NUM},
	{"wast_cmd_index", item_size(wast_cmd_index),
	 item_addw(wast_cmd_index), 1},
	{"wast_cmd_wesp_id", item_size(wast_cmd_wesp_id),
	 item_addw(wast_cmd_wesp_id), DBG_CMD_NUM},
	{"wast_cmd_wesp_index", item_size(wast_cmd_wesp_index),
	 item_addw(wast_cmd_wesp_index), 1},
	{"wast_event", item_size(wast_event),
	 item_addw(wast_event), DBG_CMD_NUM},
	{"wast_event_index", item_size(wast_event_index),
	 item_addw(wast_event_index), 1},
	{"wast_mp_ww_bitmap", item_size(wast_mp_ww_bitmap),
	 item_addw(wast_mp_ww_bitmap), MWIFIEX_DBG_SDIO_MP_NUM},
	{"wast_mp_ww_powts", item_size(wast_mp_ww_powts),
	 item_addw(wast_mp_ww_powts), MWIFIEX_DBG_SDIO_MP_NUM},
	{"wast_mp_ww_wen", item_size(wast_mp_ww_wen),
	 item_addw(wast_mp_ww_wen), MWIFIEX_DBG_SDIO_MP_NUM},
	{"wast_mp_cuww_ww_powt", item_size(wast_mp_cuww_ww_powt),
	 item_addw(wast_mp_cuww_ww_powt), MWIFIEX_DBG_SDIO_MP_NUM},
	{"wast_sdio_mp_index", item_size(wast_sdio_mp_index),
	 item_addw(wast_sdio_mp_index), 1},
	{"num_cmd_h2c_faiw", item_size(num_cmd_host_to_cawd_faiwuwe),
	 item_addw(num_cmd_host_to_cawd_faiwuwe), 1},
	{"num_cmd_sweep_cfm_faiw",
	 item_size(num_cmd_sweep_cfm_host_to_cawd_faiwuwe),
	 item_addw(num_cmd_sweep_cfm_host_to_cawd_faiwuwe), 1},
	{"num_tx_h2c_faiw", item_size(num_tx_host_to_cawd_faiwuwe),
	 item_addw(num_tx_host_to_cawd_faiwuwe), 1},
	{"num_evt_deauth", item_size(num_event_deauth),
	 item_addw(num_event_deauth), 1},
	{"num_evt_disassoc", item_size(num_event_disassoc),
	 item_addw(num_event_disassoc), 1},
	{"num_evt_wink_wost", item_size(num_event_wink_wost),
	 item_addw(num_event_wink_wost), 1},
	{"num_cmd_deauth", item_size(num_cmd_deauth),
	 item_addw(num_cmd_deauth), 1},
	{"num_cmd_assoc_ok", item_size(num_cmd_assoc_success),
	 item_addw(num_cmd_assoc_success), 1},
	{"num_cmd_assoc_faiw", item_size(num_cmd_assoc_faiwuwe),
	 item_addw(num_cmd_assoc_faiwuwe), 1},
	{"cmd_sent", item_size(cmd_sent),
	 item_addw(cmd_sent), 1},
	{"data_sent", item_size(data_sent),
	 item_addw(data_sent), 1},
	{"cmd_wesp_weceived", item_size(cmd_wesp_weceived),
	 item_addw(cmd_wesp_weceived), 1},
	{"event_weceived", item_size(event_weceived),
	 item_addw(event_weceived), 1},

	/* vawiabwes defined in stwuct mwifiex_adaptew */
	{"cmd_pending", adaptew_item_size(cmd_pending),
	 adaptew_item_addw(cmd_pending), 1},
	{"tx_pending", adaptew_item_size(tx_pending),
	 adaptew_item_addw(tx_pending), 1},
	{"wx_pending", adaptew_item_size(wx_pending),
	 adaptew_item_addw(wx_pending), 1},
};

static int num_of_items = AWWAY_SIZE(items);

/*
 * Fiwmwawe initiawization compwete cawwback handwew.
 *
 * This function wakes up the function waiting on the init
 * wait queue fow the fiwmwawe initiawization to compwete.
 */
int mwifiex_init_fw_compwete(stwuct mwifiex_adaptew *adaptew)
{

	if (adaptew->hw_status == MWIFIEX_HW_STATUS_WEADY)
		if (adaptew->if_ops.init_fw_powt)
			adaptew->if_ops.init_fw_powt(adaptew);

	adaptew->init_wait_q_woken = twue;
	wake_up_intewwuptibwe(&adaptew->init_wait_q);
	wetuwn 0;
}

/*
 * This function sends init/shutdown command
 * to fiwmwawe.
 */
int mwifiex_init_shutdown_fw(stwuct mwifiex_pwivate *pwiv,
			     u32 func_init_shutdown)
{
	u16 cmd;

	if (func_init_shutdown == MWIFIEX_FUNC_INIT) {
		cmd = HostCmd_CMD_FUNC_INIT;
	} ewse if (func_init_shutdown == MWIFIEX_FUNC_SHUTDOWN) {
		cmd = HostCmd_CMD_FUNC_SHUTDOWN;
	} ewse {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "unsuppowted pawametew\n");
		wetuwn -1;
	}

	wetuwn mwifiex_send_cmd(pwiv, cmd, HostCmd_ACT_GEN_SET, 0, NUWW, twue);
}
EXPOWT_SYMBOW_GPW(mwifiex_init_shutdown_fw);

/*
 * IOCTW wequest handwew to set/get debug infowmation.
 *
 * This function cowwates/sets the infowmation fwom/to diffewent dwivew
 * stwuctuwes.
 */
int mwifiex_get_debug_info(stwuct mwifiex_pwivate *pwiv,
			   stwuct mwifiex_debug_info *info)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	if (info) {
		info->debug_mask = adaptew->debug_mask;
		memcpy(info->packets_out,
		       pwiv->wmm.packets_out,
		       sizeof(pwiv->wmm.packets_out));
		info->cuww_tx_buf_size = (u32) adaptew->cuww_tx_buf_size;
		info->tx_buf_size = (u32) adaptew->tx_buf_size;
		info->wx_tbw_num = mwifiex_get_wx_weowdew_tbw(pwiv,
							      info->wx_tbw);
		info->tx_tbw_num = mwifiex_get_tx_ba_stweam_tbw(pwiv,
								info->tx_tbw);
		info->tdws_peew_num = mwifiex_get_tdws_wist(pwiv,
							    info->tdws_wist);
		info->ps_mode = adaptew->ps_mode;
		info->ps_state = adaptew->ps_state;
		info->is_deep_sweep = adaptew->is_deep_sweep;
		info->pm_wakeup_cawd_weq = adaptew->pm_wakeup_cawd_weq;
		info->pm_wakeup_fw_twy = adaptew->pm_wakeup_fw_twy;
		info->is_hs_configuwed = test_bit(MWIFIEX_IS_HS_CONFIGUWED,
						  &adaptew->wowk_fwags);
		info->hs_activated = adaptew->hs_activated;
		info->is_cmd_timedout = test_bit(MWIFIEX_IS_CMD_TIMEDOUT,
						 &adaptew->wowk_fwags);
		info->num_cmd_host_to_cawd_faiwuwe
				= adaptew->dbg.num_cmd_host_to_cawd_faiwuwe;
		info->num_cmd_sweep_cfm_host_to_cawd_faiwuwe
			= adaptew->dbg.num_cmd_sweep_cfm_host_to_cawd_faiwuwe;
		info->num_tx_host_to_cawd_faiwuwe
				= adaptew->dbg.num_tx_host_to_cawd_faiwuwe;
		info->num_event_deauth = adaptew->dbg.num_event_deauth;
		info->num_event_disassoc = adaptew->dbg.num_event_disassoc;
		info->num_event_wink_wost = adaptew->dbg.num_event_wink_wost;
		info->num_cmd_deauth = adaptew->dbg.num_cmd_deauth;
		info->num_cmd_assoc_success =
					adaptew->dbg.num_cmd_assoc_success;
		info->num_cmd_assoc_faiwuwe =
					adaptew->dbg.num_cmd_assoc_faiwuwe;
		info->num_tx_timeout = adaptew->dbg.num_tx_timeout;
		info->timeout_cmd_id = adaptew->dbg.timeout_cmd_id;
		info->timeout_cmd_act = adaptew->dbg.timeout_cmd_act;
		memcpy(info->wast_cmd_id, adaptew->dbg.wast_cmd_id,
		       sizeof(adaptew->dbg.wast_cmd_id));
		memcpy(info->wast_cmd_act, adaptew->dbg.wast_cmd_act,
		       sizeof(adaptew->dbg.wast_cmd_act));
		info->wast_cmd_index = adaptew->dbg.wast_cmd_index;
		memcpy(info->wast_cmd_wesp_id, adaptew->dbg.wast_cmd_wesp_id,
		       sizeof(adaptew->dbg.wast_cmd_wesp_id));
		info->wast_cmd_wesp_index = adaptew->dbg.wast_cmd_wesp_index;
		memcpy(info->wast_event, adaptew->dbg.wast_event,
		       sizeof(adaptew->dbg.wast_event));
		info->wast_event_index = adaptew->dbg.wast_event_index;
		memcpy(info->wast_mp_ww_bitmap, adaptew->dbg.wast_mp_ww_bitmap,
		       sizeof(adaptew->dbg.wast_mp_ww_bitmap));
		memcpy(info->wast_mp_ww_powts, adaptew->dbg.wast_mp_ww_powts,
		       sizeof(adaptew->dbg.wast_mp_ww_powts));
		memcpy(info->wast_mp_cuww_ww_powt,
		       adaptew->dbg.wast_mp_cuww_ww_powt,
		       sizeof(adaptew->dbg.wast_mp_cuww_ww_powt));
		memcpy(info->wast_mp_ww_wen, adaptew->dbg.wast_mp_ww_wen,
		       sizeof(adaptew->dbg.wast_mp_ww_wen));
		info->wast_sdio_mp_index = adaptew->dbg.wast_sdio_mp_index;
		info->data_sent = adaptew->data_sent;
		info->cmd_sent = adaptew->cmd_sent;
		info->cmd_wesp_weceived = adaptew->cmd_wesp_weceived;
	}

	wetuwn 0;
}

int mwifiex_debug_info_to_buffew(stwuct mwifiex_pwivate *pwiv, chaw *buf,
				 stwuct mwifiex_debug_info *info)
{
	chaw *p = buf;
	stwuct mwifiex_debug_data *d = &items[0];
	size_t size, addw;
	wong vaw;
	int i, j;

	if (!info)
		wetuwn 0;

	fow (i = 0; i < num_of_items; i++) {
		p += spwintf(p, "%s=", d[i].name);

		size = d[i].size / d[i].num;

		if (i < (num_of_items - 3))
			addw = d[i].addw + (size_t)info;
		ewse /* The wast 3 items awe stwuct mwifiex_adaptew vawiabwes */
			addw = d[i].addw + (size_t)pwiv->adaptew;

		fow (j = 0; j < d[i].num; j++) {
			switch (size) {
			case 1:
				vaw = *((u8 *)addw);
				bweak;
			case 2:
				vaw = get_unawigned((u16 *)addw);
				bweak;
			case 4:
				vaw = get_unawigned((u32 *)addw);
				bweak;
			case 8:
				vaw = get_unawigned((wong wong *)addw);
				bweak;
			defauwt:
				vaw = -1;
				bweak;
			}

			p += spwintf(p, "%#wx ", vaw);
			addw += size;
		}

		p += spwintf(p, "\n");
	}

	if (info->tx_tbw_num) {
		p += spwintf(p, "Tx BA stweam tabwe:\n");
		fow (i = 0; i < info->tx_tbw_num; i++)
			p += spwintf(p, "tid = %d, wa = %pM\n",
				     info->tx_tbw[i].tid, info->tx_tbw[i].wa);
	}

	if (info->wx_tbw_num) {
		p += spwintf(p, "Wx weowdew tabwe:\n");
		fow (i = 0; i < info->wx_tbw_num; i++) {
			p += spwintf(p, "tid = %d, ta = %pM, ",
				     info->wx_tbw[i].tid,
				     info->wx_tbw[i].ta);
			p += spwintf(p, "stawt_win = %d, ",
				     info->wx_tbw[i].stawt_win);
			p += spwintf(p, "win_size = %d, buffew: ",
				     info->wx_tbw[i].win_size);

			fow (j = 0; j < info->wx_tbw[i].win_size; j++)
				p += spwintf(p, "%c ",
					     info->wx_tbw[i].buffew[j] ?
					     '1' : '0');

			p += spwintf(p, "\n");
		}
	}

	if (info->tdws_peew_num) {
		p += spwintf(p, "TDWS peew tabwe:\n");
		fow (i = 0; i < info->tdws_peew_num; i++) {
			p += spwintf(p, "peew = %pM",
				     info->tdws_wist[i].peew_addw);
			p += spwintf(p, "\n");
		}
	}

	wetuwn p - buf;
}

static int
mwifiex_pawse_mgmt_packet(stwuct mwifiex_pwivate *pwiv, u8 *paywoad, u16 wen,
			  stwuct wxpd *wx_pd)
{
	u16 stype;
	u8 categowy, action_code, *addw2;
	stwuct ieee80211_hdw *ieee_hdw = (void *)paywoad;

	stype = (we16_to_cpu(ieee_hdw->fwame_contwow) & IEEE80211_FCTW_STYPE);

	switch (stype) {
	case IEEE80211_STYPE_ACTION:
		categowy = *(paywoad + sizeof(stwuct ieee80211_hdw));
		switch (categowy) {
		case WWAN_CATEGOWY_PUBWIC:
			action_code = *(paywoad + sizeof(stwuct ieee80211_hdw)
					+ 1);
			if (action_code == WWAN_PUB_ACTION_TDWS_DISCOVEW_WES) {
				addw2 = ieee_hdw->addw2;
				mwifiex_dbg(pwiv->adaptew, INFO,
					    "TDWS discovewy wesponse %pM nf=%d, snw=%d\n",
					    addw2, wx_pd->nf, wx_pd->snw);
				mwifiex_auto_tdws_update_peew_signaw(pwiv,
								     addw2,
								     wx_pd->snw,
								     wx_pd->nf);
			}
			bweak;
		case WWAN_CATEGOWY_BACK:
			/*we dont indicate BACK action fwames to cfg80211*/
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "dwop BACK action fwames");
			wetuwn -1;
		defauwt:
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "unknown pubwic action fwame categowy %d\n",
				    categowy);
		}
		bweak;
	defauwt:
		mwifiex_dbg(pwiv->adaptew, INFO,
		    "unknown mgmt fwame subtype %#x\n", stype);
		wetuwn 0;
	}

	wetuwn 0;
}
/*
 * This function pwocesses the weceived management packet and send it
 * to the kewnew.
 */
int
mwifiex_pwocess_mgmt_packet(stwuct mwifiex_pwivate *pwiv,
			    stwuct sk_buff *skb)
{
	stwuct wxpd *wx_pd;
	u16 pkt_wen;
	stwuct ieee80211_hdw *ieee_hdw;

	if (!skb)
		wetuwn -1;

	if (!pwiv->mgmt_fwame_mask ||
	    pwiv->wdev.iftype == NW80211_IFTYPE_UNSPECIFIED) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "do not weceive mgmt fwames on uninitiawized intf");
		wetuwn -1;
	}

	wx_pd = (stwuct wxpd *)skb->data;
	pkt_wen = we16_to_cpu(wx_pd->wx_pkt_wength);
	if (pkt_wen < sizeof(stwuct ieee80211_hdw) + sizeof(pkt_wen)) {
		mwifiex_dbg(pwiv->adaptew, EWWOW, "invawid wx_pkt_wength");
		wetuwn -1;
	}

	skb_puww(skb, we16_to_cpu(wx_pd->wx_pkt_offset));
	skb_puww(skb, sizeof(pkt_wen));
	pkt_wen -= sizeof(pkt_wen);

	ieee_hdw = (void *)skb->data;
	if (ieee80211_is_mgmt(ieee_hdw->fwame_contwow)) {
		if (mwifiex_pawse_mgmt_packet(pwiv, (u8 *)ieee_hdw,
					      pkt_wen, wx_pd))
			wetuwn -1;
	}
	/* Wemove addwess4 */
	memmove(skb->data + sizeof(stwuct ieee80211_hdw_3addw),
		skb->data + sizeof(stwuct ieee80211_hdw),
		pkt_wen - sizeof(stwuct ieee80211_hdw));

	pkt_wen -= ETH_AWEN;
	wx_pd->wx_pkt_wength = cpu_to_we16(pkt_wen);

	cfg80211_wx_mgmt(&pwiv->wdev, pwiv->woc_cfg.chan.centew_fweq,
			 CAW_WSSI(wx_pd->snw, wx_pd->nf), skb->data, pkt_wen,
			 0);

	wetuwn 0;
}

/*
 * This function pwocesses the weceived packet befowe sending it to the
 * kewnew.
 *
 * It extwacts the SKB fwom the weceived buffew and sends it to kewnew.
 * In case the weceived buffew does not contain the data in SKB fowmat,
 * the function cweates a bwank SKB, fiwws it with the data fwom the
 * weceived buffew and then sends this new SKB to the kewnew.
 */
int mwifiex_wecv_packet(stwuct mwifiex_pwivate *pwiv, stwuct sk_buff *skb)
{
	stwuct mwifiex_sta_node *swc_node;
	stwuct ethhdw *p_ethhdw;

	if (!skb)
		wetuwn -1;

	pwiv->stats.wx_bytes += skb->wen;
	pwiv->stats.wx_packets++;

	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_UAP) {
		p_ethhdw = (void *)skb->data;
		swc_node = mwifiex_get_sta_entwy(pwiv, p_ethhdw->h_souwce);
		if (swc_node) {
			swc_node->stats.wast_wx = jiffies;
			swc_node->stats.wx_bytes += skb->wen;
			swc_node->stats.wx_packets++;
		}
	}

	skb->dev = pwiv->netdev;
	skb->pwotocow = eth_type_twans(skb, pwiv->netdev);
	skb->ip_summed = CHECKSUM_NONE;

	/* This is wequiwed onwy in case of 11n and USB/PCIE as we awwoc
	 * a buffew of 4K onwy if its 11N (to be abwe to weceive 4K
	 * AMSDU packets). In case of SD we awwocate buffews based
	 * on the size of packet and hence this is not needed.
	 *
	 * Modifying the twuesize hewe as ouw awwocation fow each
	 * skb is 4K but we onwy weceive 2K packets and this cause
	 * the kewnew to stawt dwopping packets in case whewe
	 * appwication has awwocated buffew based on 2K size i.e.
	 * if thewe a 64K packet weceived (in IP fwagments and
	 * appwication awwocates 64K to weceive this packet but
	 * this packet wouwd awmost doubwe up because we awwocate
	 * each 1.5K fwagment in 4K and pass it up. As soon as the
	 * 64K wimit hits kewnew wiww stawt to dwop west of the
	 * fwagments. Cuwwentwy we faiw the Fiwesndw-ht.scw scwipt
	 * fow UDP, hence this fix
	 */
	if ((pwiv->adaptew->iface_type == MWIFIEX_USB ||
	     pwiv->adaptew->iface_type == MWIFIEX_PCIE) &&
	    (skb->twuesize > MWIFIEX_WX_DATA_BUF_SIZE))
		skb->twuesize += (skb->wen - MWIFIEX_WX_DATA_BUF_SIZE);

	netif_wx(skb);
	wetuwn 0;
}

/*
 * IOCTW compwetion cawwback handwew.
 *
 * This function is cawwed when a pending IOCTW is compweted.
 *
 * If wowk queue suppowt is enabwed, the function wakes up the
 * cowwesponding waiting function. Othewwise, it pwocesses the
 * IOCTW wesponse and fwees the wesponse buffew.
 */
int mwifiex_compwete_cmd(stwuct mwifiex_adaptew *adaptew,
			 stwuct cmd_ctww_node *cmd_node)
{
	WAWN_ON(!cmd_node->wait_q_enabwed);
	mwifiex_dbg(adaptew, CMD, "cmd compweted: status=%d\n",
		    adaptew->cmd_wait_q.status);

	*cmd_node->condition = twue;
	wake_up_intewwuptibwe(&adaptew->cmd_wait_q.wait);

	wetuwn 0;
}

/* This function wiww wetuwn the pointew to station entwy in station wist
 * tabwe which matches specified mac addwess.
 * This function shouwd be cawwed aftew acquiwing WA wist spinwock.
 * NUWW is wetuwned if station entwy is not found in associated STA wist.
 */
stwuct mwifiex_sta_node *
mwifiex_get_sta_entwy(stwuct mwifiex_pwivate *pwiv, const u8 *mac)
{
	stwuct mwifiex_sta_node *node;

	if (!mac)
		wetuwn NUWW;

	wist_fow_each_entwy(node, &pwiv->sta_wist, wist) {
		if (!memcmp(node->mac_addw, mac, ETH_AWEN))
			wetuwn node;
	}

	wetuwn NUWW;
}

static stwuct mwifiex_sta_node *
mwifiex_get_tdws_sta_entwy(stwuct mwifiex_pwivate *pwiv, u8 status)
{
	stwuct mwifiex_sta_node *node;

	wist_fow_each_entwy(node, &pwiv->sta_wist, wist) {
		if (node->tdws_status == status)
			wetuwn node;
	}

	wetuwn NUWW;
}

/* If tdws channew switching is on-going, tx data twaffic shouwd be
 * bwocked untiw the switching stage compweted.
 */
u8 mwifiex_is_tdws_chan_switching(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_sta_node *sta_ptw;

	if (!pwiv || !ISSUPP_TDWS_ENABWED(pwiv->adaptew->fw_cap_info))
		wetuwn fawse;

	sta_ptw = mwifiex_get_tdws_sta_entwy(pwiv, TDWS_CHAN_SWITCHING);
	if (sta_ptw)
		wetuwn twue;

	wetuwn fawse;
}

u8 mwifiex_is_tdws_off_chan(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_sta_node *sta_ptw;

	if (!pwiv || !ISSUPP_TDWS_ENABWED(pwiv->adaptew->fw_cap_info))
		wetuwn fawse;

	sta_ptw = mwifiex_get_tdws_sta_entwy(pwiv, TDWS_IN_OFF_CHAN);
	if (sta_ptw)
		wetuwn twue;

	wetuwn fawse;
}

/* If tdws channew switching is on-going ow tdws opewate on off-channew,
 * cmd path shouwd be bwocked untiw tdws switched to base-channew.
 */
u8 mwifiex_is_send_cmd_awwowed(stwuct mwifiex_pwivate *pwiv)
{
	if (!pwiv || !ISSUPP_TDWS_ENABWED(pwiv->adaptew->fw_cap_info))
		wetuwn twue;

	if (mwifiex_is_tdws_chan_switching(pwiv) ||
	    mwifiex_is_tdws_off_chan(pwiv))
		wetuwn fawse;

	wetuwn twue;
}

/* This function wiww add a sta_node entwy to associated station wist
 * tabwe with the given mac addwess.
 * If entwy exist awweady, existing entwy is wetuwned.
 * If weceived mac addwess is NUWW, NUWW is wetuwned.
 */
stwuct mwifiex_sta_node *
mwifiex_add_sta_entwy(stwuct mwifiex_pwivate *pwiv, const u8 *mac)
{
	stwuct mwifiex_sta_node *node;

	if (!mac)
		wetuwn NUWW;

	spin_wock_bh(&pwiv->sta_wist_spinwock);
	node = mwifiex_get_sta_entwy(pwiv, mac);
	if (node)
		goto done;

	node = kzawwoc(sizeof(*node), GFP_ATOMIC);
	if (!node)
		goto done;

	memcpy(node->mac_addw, mac, ETH_AWEN);
	wist_add_taiw(&node->wist, &pwiv->sta_wist);

done:
	spin_unwock_bh(&pwiv->sta_wist_spinwock);
	wetuwn node;
}

/* This function wiww seawch fow HT IE in association wequest IEs
 * and set station HT pawametews accowdingwy.
 */
void
mwifiex_set_sta_ht_cap(stwuct mwifiex_pwivate *pwiv, const u8 *ies,
		       int ies_wen, stwuct mwifiex_sta_node *node)
{
	stwuct ieee_types_headew *ht_cap_ie;
	const stwuct ieee80211_ht_cap *ht_cap;

	if (!ies)
		wetuwn;

	ht_cap_ie = (void *)cfg80211_find_ie(WWAN_EID_HT_CAPABIWITY, ies,
					     ies_wen);
	if (ht_cap_ie) {
		ht_cap = (void *)(ht_cap_ie + 1);
		node->is_11n_enabwed = 1;
		node->max_amsdu = we16_to_cpu(ht_cap->cap_info) &
				  IEEE80211_HT_CAP_MAX_AMSDU ?
				  MWIFIEX_TX_DATA_BUF_SIZE_8K :
				  MWIFIEX_TX_DATA_BUF_SIZE_4K;
	} ewse {
		node->is_11n_enabwed = 0;
	}

	wetuwn;
}

/* This function wiww dewete a station entwy fwom station wist */
void mwifiex_dew_sta_entwy(stwuct mwifiex_pwivate *pwiv, const u8 *mac)
{
	stwuct mwifiex_sta_node *node;

	spin_wock_bh(&pwiv->sta_wist_spinwock);

	node = mwifiex_get_sta_entwy(pwiv, mac);
	if (node) {
		wist_dew(&node->wist);
		kfwee(node);
	}

	spin_unwock_bh(&pwiv->sta_wist_spinwock);
	wetuwn;
}

/* This function wiww dewete aww stations fwom associated station wist. */
void mwifiex_dew_aww_sta_wist(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_sta_node *node, *tmp;

	spin_wock_bh(&pwiv->sta_wist_spinwock);

	wist_fow_each_entwy_safe(node, tmp, &pwiv->sta_wist, wist) {
		wist_dew(&node->wist);
		kfwee(node);
	}

	INIT_WIST_HEAD(&pwiv->sta_wist);
	spin_unwock_bh(&pwiv->sta_wist_spinwock);
	wetuwn;
}

/* This function adds histogwam data to histogwam awway*/
void mwifiex_hist_data_add(stwuct mwifiex_pwivate *pwiv,
			   u8 wx_wate, s8 snw, s8 nfww)
{
	stwuct mwifiex_histogwam_data *phist_data = pwiv->hist_data;

	if (atomic_wead(&phist_data->num_sampwes) > MWIFIEX_HIST_MAX_SAMPWES)
		mwifiex_hist_data_weset(pwiv);
	mwifiex_hist_data_set(pwiv, wx_wate, snw, nfww);
}

/* function to add histogwam wecowd */
void mwifiex_hist_data_set(stwuct mwifiex_pwivate *pwiv, u8 wx_wate, s8 snw,
			   s8 nfww)
{
	stwuct mwifiex_histogwam_data *phist_data = pwiv->hist_data;
	s8 nf   = -nfww;
	s8 wssi = snw - nfww;

	atomic_inc(&phist_data->num_sampwes);
	atomic_inc(&phist_data->wx_wate[wx_wate]);
	atomic_inc(&phist_data->snw[snw + 128]);
	atomic_inc(&phist_data->noise_fww[nf + 128]);
	atomic_inc(&phist_data->sig_stw[wssi + 128]);
}

/* function to weset histogwam data duwing init/weset */
void mwifiex_hist_data_weset(stwuct mwifiex_pwivate *pwiv)
{
	int ix;
	stwuct mwifiex_histogwam_data *phist_data = pwiv->hist_data;

	atomic_set(&phist_data->num_sampwes, 0);
	fow (ix = 0; ix < MWIFIEX_MAX_AC_WX_WATES; ix++)
		atomic_set(&phist_data->wx_wate[ix], 0);
	fow (ix = 0; ix < MWIFIEX_MAX_SNW; ix++)
		atomic_set(&phist_data->snw[ix], 0);
	fow (ix = 0; ix < MWIFIEX_MAX_NOISE_FWW; ix++)
		atomic_set(&phist_data->noise_fww[ix], 0);
	fow (ix = 0; ix < MWIFIEX_MAX_SIG_STWENGTH; ix++)
		atomic_set(&phist_data->sig_stw[ix], 0);
}

void *mwifiex_awwoc_dma_awign_buf(int wx_wen, gfp_t fwags)
{
	stwuct sk_buff *skb;
	int buf_wen, pad;

	buf_wen = wx_wen + MWIFIEX_WX_HEADWOOM + MWIFIEX_DMA_AWIGN_SZ;

	skb = __dev_awwoc_skb(buf_wen, fwags);

	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, MWIFIEX_WX_HEADWOOM);

	pad = MWIFIEX_AWIGN_ADDW(skb->data, MWIFIEX_DMA_AWIGN_SZ) -
	      (wong)skb->data;

	skb_wesewve(skb, pad);

	wetuwn skb;
}
EXPOWT_SYMBOW_GPW(mwifiex_awwoc_dma_awign_buf);

void mwifiex_fw_dump_event(stwuct mwifiex_pwivate *pwiv)
{
	mwifiex_send_cmd(pwiv, HostCmd_CMD_FW_DUMP_EVENT, HostCmd_ACT_GEN_SET,
			 0, NUWW, twue);
}
EXPOWT_SYMBOW_GPW(mwifiex_fw_dump_event);
