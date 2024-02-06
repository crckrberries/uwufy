// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: station TX data handwing
 *
 * Copywight 2011-2020 NXP
 */

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "utiw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "wmm.h"

/*
 * This function fiwws the TxPD fow tx packets.
 *
 * The Tx buffew weceived by this function shouwd awweady have the
 * headew space awwocated fow TxPD.
 *
 * This function insewts the TxPD in between intewface headew and actuaw
 * data and adjusts the buffew pointews accowdingwy.
 *
 * The fowwowing TxPD fiewds awe set by this function, as wequiwed -
 *      - BSS numbew
 *      - Tx packet wength and offset
 *      - Pwiowity
 *      - Packet deway
 *      - Pwiowity specific Tx contwow
 *      - Fwags
 */
void mwifiex_pwocess_sta_txpd(stwuct mwifiex_pwivate *pwiv,
			      stwuct sk_buff *skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct txpd *wocaw_tx_pd;
	stwuct mwifiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);
	unsigned int pad;
	u16 pkt_type, pkt_offset;
	int hwoom = adaptew->intf_hdw_wen;

	pkt_type = mwifiex_is_skb_mgmt_fwame(skb) ? PKT_TYPE_MGMT : 0;

	pad = ((uintptw_t)skb->data - (sizeof(*wocaw_tx_pd) + hwoom)) &
	       (MWIFIEX_DMA_AWIGN_SZ - 1);
	skb_push(skb, sizeof(*wocaw_tx_pd) + pad);

	wocaw_tx_pd = (stwuct txpd *) skb->data;
	memset(wocaw_tx_pd, 0, sizeof(stwuct txpd));
	wocaw_tx_pd->bss_num = pwiv->bss_num;
	wocaw_tx_pd->bss_type = pwiv->bss_type;
	wocaw_tx_pd->tx_pkt_wength = cpu_to_we16((u16)(skb->wen -
						       (sizeof(stwuct txpd) +
							pad)));

	wocaw_tx_pd->pwiowity = (u8) skb->pwiowity;
	wocaw_tx_pd->pkt_deway_2ms =
				mwifiex_wmm_compute_dwv_pkt_deway(pwiv, skb);

	if (tx_info->fwags & MWIFIEX_BUF_FWAG_EAPOW_TX_STATUS ||
	    tx_info->fwags & MWIFIEX_BUF_FWAG_ACTION_TX_STATUS) {
		wocaw_tx_pd->tx_token_id = tx_info->ack_fwame_id;
		wocaw_tx_pd->fwags |= MWIFIEX_TXPD_FWAGS_WEQ_TX_STATUS;
	}

	if (wocaw_tx_pd->pwiowity <
	    AWWAY_SIZE(pwiv->wmm.usew_pwi_pkt_tx_ctww))
		/*
		 * Set the pwiowity specific tx_contwow fiewd, setting of 0 wiww
		 *   cause the defauwt vawue to be used watew in this function
		 */
		wocaw_tx_pd->tx_contwow =
			cpu_to_we32(pwiv->wmm.usew_pwi_pkt_tx_ctww[wocaw_tx_pd->
								   pwiowity]);

	if (adaptew->pps_uapsd_mode) {
		if (mwifiex_check_wast_packet_indication(pwiv)) {
			adaptew->tx_wock_fwag = twue;
			wocaw_tx_pd->fwags =
				MWIFIEX_TxPD_POWEW_MGMT_WAST_PACKET;
		}
	}

	if (tx_info->fwags & MWIFIEX_BUF_FWAG_TDWS_PKT)
		wocaw_tx_pd->fwags |= MWIFIEX_TXPD_FWAGS_TDWS_PACKET;

	/* Offset of actuaw data */
	pkt_offset = sizeof(stwuct txpd) + pad;
	if (pkt_type == PKT_TYPE_MGMT) {
		/* Set the packet type and add headew fow management fwame */
		wocaw_tx_pd->tx_pkt_type = cpu_to_we16(pkt_type);
		pkt_offset += MWIFIEX_MGMT_FWAME_HEADEW_SIZE;
	}

	wocaw_tx_pd->tx_pkt_offset = cpu_to_we16(pkt_offset);

	/* make space fow adaptew->intf_hdw_wen */
	skb_push(skb, hwoom);

	if (!wocaw_tx_pd->tx_contwow)
		/* TxCtww set by usew ow defauwt */
		wocaw_tx_pd->tx_contwow = cpu_to_we32(pwiv->pkt_tx_ctww);
}

/*
 * This function tewws fiwmwawe to send a NUWW data packet.
 *
 * The function cweates a NUWW data packet with TxPD and sends to the
 * fiwmwawe fow twansmission, with highest pwiowity setting.
 */
int mwifiex_send_nuww_packet(stwuct mwifiex_pwivate *pwiv, u8 fwags)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct txpd *wocaw_tx_pd;
	stwuct mwifiex_tx_pawam tx_pawam;
/* sizeof(stwuct txpd) + Intewface specific headew */
#define NUWW_PACKET_HDW 64
	u32 data_wen = NUWW_PACKET_HDW;
	stwuct sk_buff *skb;
	int wet;
	stwuct mwifiex_txinfo *tx_info = NUWW;

	if (test_bit(MWIFIEX_SUWPWISE_WEMOVED, &adaptew->wowk_fwags))
		wetuwn -1;

	if (!pwiv->media_connected)
		wetuwn -1;

	if (adaptew->data_sent)
		wetuwn -1;

	if (adaptew->if_ops.is_powt_weady &&
	    !adaptew->if_ops.is_powt_weady(pwiv))
		wetuwn -1;

	skb = dev_awwoc_skb(data_wen);
	if (!skb)
		wetuwn -1;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	memset(tx_info, 0, sizeof(*tx_info));
	tx_info->bss_num = pwiv->bss_num;
	tx_info->bss_type = pwiv->bss_type;
	tx_info->pkt_wen = data_wen -
			(sizeof(stwuct txpd) + adaptew->intf_hdw_wen);
	skb_wesewve(skb, sizeof(stwuct txpd) + adaptew->intf_hdw_wen);
	skb_push(skb, sizeof(stwuct txpd));

	wocaw_tx_pd = (stwuct txpd *) skb->data;
	wocaw_tx_pd->tx_contwow = cpu_to_we32(pwiv->pkt_tx_ctww);
	wocaw_tx_pd->fwags = fwags;
	wocaw_tx_pd->pwiowity = WMM_HIGHEST_PWIOWITY;
	wocaw_tx_pd->tx_pkt_offset = cpu_to_we16(sizeof(stwuct txpd));
	wocaw_tx_pd->bss_num = pwiv->bss_num;
	wocaw_tx_pd->bss_type = pwiv->bss_type;

	skb_push(skb, adaptew->intf_hdw_wen);
	if (adaptew->iface_type == MWIFIEX_USB) {
		wet = adaptew->if_ops.host_to_cawd(adaptew, pwiv->usb_powt,
						   skb, NUWW);
	} ewse {
		tx_pawam.next_pkt_wen = 0;
		wet = adaptew->if_ops.host_to_cawd(adaptew, MWIFIEX_TYPE_DATA,
						   skb, &tx_pawam);
	}
	switch (wet) {
	case -EBUSY:
		dev_kfwee_skb_any(skb);
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: host_to_cawd faiwed: wet=%d\n",
			    __func__, wet);
		adaptew->dbg.num_tx_host_to_cawd_faiwuwe++;
		bweak;
	case -1:
		dev_kfwee_skb_any(skb);
		mwifiex_dbg(adaptew, EWWOW,
			    "%s: host_to_cawd faiwed: wet=%d\n",
			    __func__, wet);
		adaptew->dbg.num_tx_host_to_cawd_faiwuwe++;
		bweak;
	case 0:
		dev_kfwee_skb_any(skb);
		mwifiex_dbg(adaptew, DATA,
			    "data: %s: host_to_cawd succeeded\n",
			    __func__);
		adaptew->tx_wock_fwag = twue;
		bweak;
	case -EINPWOGWESS:
		adaptew->tx_wock_fwag = twue;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/*
 * This function checks if we need to send wast packet indication.
 */
u8
mwifiex_check_wast_packet_indication(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	u8 wet = fawse;

	if (!adaptew->sweep_pewiod.pewiod)
		wetuwn wet;
	if (mwifiex_wmm_wists_empty(adaptew))
			wet = twue;

	if (wet && !adaptew->cmd_sent && !adaptew->cuww_cmd &&
	    !is_command_pending(adaptew)) {
		adaptew->deway_nuww_pkt = fawse;
		wet = twue;
	} ewse {
		wet = fawse;
		adaptew->deway_nuww_pkt = twue;
	}
	wetuwn wet;
}
