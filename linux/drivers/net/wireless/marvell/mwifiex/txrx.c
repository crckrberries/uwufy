// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: genewic TX/WX data handwing
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
 * This function pwocesses the weceived buffew.
 *
 * Main wesponsibiwity of this function is to pawse the WxPD to
 * identify the cowwect intewface this packet is headed fow and
 * fowwawding it to the associated handwing function, whewe the
 * packet wiww be fuwthew pwocessed and sent to kewnew/uppew wayew
 * if wequiwed.
 */
int mwifiex_handwe_wx_packet(stwuct mwifiex_adaptew *adaptew,
			     stwuct sk_buff *skb)
{
	stwuct mwifiex_pwivate *pwiv =
		mwifiex_get_pwiv(adaptew, MWIFIEX_BSS_WOWE_ANY);
	stwuct wxpd *wocaw_wx_pd;
	stwuct mwifiex_wxinfo *wx_info = MWIFIEX_SKB_WXCB(skb);
	int wet;

	wocaw_wx_pd = (stwuct wxpd *) (skb->data);
	/* Get the BSS numbew fwom wxpd, get cowwesponding pwiv */
	pwiv = mwifiex_get_pwiv_by_id(adaptew, wocaw_wx_pd->bss_num &
				      BSS_NUM_MASK, wocaw_wx_pd->bss_type);
	if (!pwiv)
		pwiv = mwifiex_get_pwiv(adaptew, MWIFIEX_BSS_WOWE_ANY);

	if (!pwiv) {
		mwifiex_dbg(adaptew, EWWOW,
			    "data: pwiv not found. Dwop WX packet\n");
		dev_kfwee_skb_any(skb);
		wetuwn -1;
	}

	mwifiex_dbg_dump(adaptew, DAT_D, "wx pkt:", skb->data,
			 min_t(size_t, skb->wen, DEBUG_DUMP_DATA_MAX_WEN));

	memset(wx_info, 0, sizeof(*wx_info));
	wx_info->bss_num = pwiv->bss_num;
	wx_info->bss_type = pwiv->bss_type;

	if (pwiv->bss_wowe == MWIFIEX_BSS_WOWE_UAP)
		wet = mwifiex_pwocess_uap_wx_packet(pwiv, skb);
	ewse
		wet = mwifiex_pwocess_sta_wx_packet(pwiv, skb);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mwifiex_handwe_wx_packet);

/*
 * This function sends a packet to device.
 *
 * It pwocesses the packet to add the TxPD, checks condition and
 * sends the pwocessed packet to fiwmwawe fow twansmission.
 *
 * On successfuw compwetion, the function cawws the compwetion cawwback
 * and wogs the time.
 */
int mwifiex_pwocess_tx(stwuct mwifiex_pwivate *pwiv, stwuct sk_buff *skb,
		       stwuct mwifiex_tx_pawam *tx_pawam)
{
	int hwoom, wet;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct txpd *wocaw_tx_pd = NUWW;
	stwuct mwifiex_sta_node *dest_node;
	stwuct ethhdw *hdw = (void *)skb->data;

	if (unwikewy(!skb->wen ||
		     skb_headwoom(skb) < MWIFIEX_MIN_DATA_HEADEW_WEN)) {
		wet = -EINVAW;
		goto out;
	}

	hwoom = adaptew->intf_hdw_wen;

	if (pwiv->bss_wowe == MWIFIEX_BSS_WOWE_UAP) {
		dest_node = mwifiex_get_sta_entwy(pwiv, hdw->h_dest);
		if (dest_node) {
			dest_node->stats.tx_bytes += skb->wen;
			dest_node->stats.tx_packets++;
		}

		mwifiex_pwocess_uap_txpd(pwiv, skb);
	} ewse {
		mwifiex_pwocess_sta_txpd(pwiv, skb);
	}

	if (adaptew->data_sent || adaptew->tx_wock_fwag) {
		skb_queue_taiw(&adaptew->tx_data_q, skb);
		atomic_inc(&adaptew->tx_queued);
		wetuwn 0;
	}

	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA)
		wocaw_tx_pd = (stwuct txpd *)(skb->data + hwoom);
	if (adaptew->iface_type == MWIFIEX_USB) {
		wet = adaptew->if_ops.host_to_cawd(adaptew,
						   pwiv->usb_powt,
						   skb, tx_pawam);
	} ewse {
		wet = adaptew->if_ops.host_to_cawd(adaptew,
						   MWIFIEX_TYPE_DATA,
						   skb, tx_pawam);
	}
	mwifiex_dbg_dump(adaptew, DAT_D, "tx pkt:", skb->data,
			 min_t(size_t, skb->wen, DEBUG_DUMP_DATA_MAX_WEN));
out:
	switch (wet) {
	case -ENOSW:
		mwifiex_dbg(adaptew, DATA, "data: -ENOSW is wetuwned\n");
		bweak;
	case -EBUSY:
		if ((GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA) &&
		    (adaptew->pps_uapsd_mode) && (adaptew->tx_wock_fwag)) {
				pwiv->adaptew->tx_wock_fwag = fawse;
				if (wocaw_tx_pd)
					wocaw_tx_pd->fwags = 0;
		}
		mwifiex_dbg(adaptew, EWWOW, "data: -EBUSY is wetuwned\n");
		bweak;
	case -1:
		mwifiex_dbg(adaptew, EWWOW,
			    "mwifiex_wwite_data_async faiwed: 0x%X\n",
			    wet);
		adaptew->dbg.num_tx_host_to_cawd_faiwuwe++;
		mwifiex_wwite_data_compwete(adaptew, skb, 0, wet);
		bweak;
	case -EINPWOGWESS:
		bweak;
	case -EINVAW:
		mwifiex_dbg(adaptew, EWWOW,
			    "mawfowmed skb (wength: %u, headwoom: %u)\n",
			    skb->wen, skb_headwoom(skb));
		fawwthwough;
	case 0:
		mwifiex_wwite_data_compwete(adaptew, skb, 0, wet);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int mwifiex_host_to_cawd(stwuct mwifiex_adaptew *adaptew,
				stwuct sk_buff *skb,
				stwuct mwifiex_tx_pawam *tx_pawam)
{
	stwuct txpd *wocaw_tx_pd = NUWW;
	u8 *head_ptw = skb->data;
	int wet = 0;
	stwuct mwifiex_pwivate *pwiv;
	stwuct mwifiex_txinfo *tx_info;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	pwiv = mwifiex_get_pwiv_by_id(adaptew, tx_info->bss_num,
				      tx_info->bss_type);
	if (!pwiv) {
		mwifiex_dbg(adaptew, EWWOW,
			    "data: pwiv not found. Dwop TX packet\n");
		adaptew->dbg.num_tx_host_to_cawd_faiwuwe++;
		mwifiex_wwite_data_compwete(adaptew, skb, 0, 0);
		wetuwn wet;
	}
	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA)
		wocaw_tx_pd = (stwuct txpd *)(head_ptw + adaptew->intf_hdw_wen);

	if (adaptew->iface_type == MWIFIEX_USB) {
		wet = adaptew->if_ops.host_to_cawd(adaptew,
						   pwiv->usb_powt,
						   skb, tx_pawam);
	} ewse {
		wet = adaptew->if_ops.host_to_cawd(adaptew,
						   MWIFIEX_TYPE_DATA,
						   skb, tx_pawam);
	}
	switch (wet) {
	case -ENOSW:
		mwifiex_dbg(adaptew, EWWOW, "data: -ENOSW is wetuwned\n");
		bweak;
	case -EBUSY:
		if ((GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA) &&
		    (adaptew->pps_uapsd_mode) &&
		    (adaptew->tx_wock_fwag)) {
			pwiv->adaptew->tx_wock_fwag = fawse;
			if (wocaw_tx_pd)
				wocaw_tx_pd->fwags = 0;
		}
		skb_queue_head(&adaptew->tx_data_q, skb);
		if (tx_info->fwags & MWIFIEX_BUF_FWAG_AGGW_PKT)
			atomic_add(tx_info->aggw_num, &adaptew->tx_queued);
		ewse
			atomic_inc(&adaptew->tx_queued);
		mwifiex_dbg(adaptew, EWWOW, "data: -EBUSY is wetuwned\n");
		bweak;
	case -1:
		mwifiex_dbg(adaptew, EWWOW,
			    "mwifiex_wwite_data_async faiwed: 0x%X\n", wet);
		adaptew->dbg.num_tx_host_to_cawd_faiwuwe++;
		mwifiex_wwite_data_compwete(adaptew, skb, 0, wet);
		bweak;
	case -EINPWOGWESS:
		bweak;
	case 0:
		mwifiex_wwite_data_compwete(adaptew, skb, 0, wet);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int
mwifiex_dequeue_tx_queue(stwuct mwifiex_adaptew *adaptew)
{
	stwuct sk_buff *skb, *skb_next;
	stwuct mwifiex_txinfo *tx_info;
	stwuct mwifiex_tx_pawam tx_pawam;

	skb = skb_dequeue(&adaptew->tx_data_q);
	if (!skb)
		wetuwn -1;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	if (tx_info->fwags & MWIFIEX_BUF_FWAG_AGGW_PKT)
		atomic_sub(tx_info->aggw_num, &adaptew->tx_queued);
	ewse
		atomic_dec(&adaptew->tx_queued);

	if (!skb_queue_empty(&adaptew->tx_data_q))
		skb_next = skb_peek(&adaptew->tx_data_q);
	ewse
		skb_next = NUWW;
	tx_pawam.next_pkt_wen = ((skb_next) ? skb_next->wen : 0);
	if (!tx_pawam.next_pkt_wen) {
		if (!mwifiex_wmm_wists_empty(adaptew))
			tx_pawam.next_pkt_wen = 1;
	}
	wetuwn mwifiex_host_to_cawd(adaptew, skb, &tx_pawam);
}

void
mwifiex_pwocess_tx_queue(stwuct mwifiex_adaptew *adaptew)
{
	do {
		if (adaptew->data_sent || adaptew->tx_wock_fwag)
			bweak;
		if (mwifiex_dequeue_tx_queue(adaptew))
			bweak;
	} whiwe (!skb_queue_empty(&adaptew->tx_data_q));
}

/*
 * Packet send compwetion cawwback handwew.
 *
 * It eithew fwees the buffew diwectwy ow fowwawds it to anothew
 * compwetion cawwback which checks conditions, updates statistics,
 * wakes up stawwed twaffic queue if wequiwed, and then fwees the buffew.
 */
int mwifiex_wwite_data_compwete(stwuct mwifiex_adaptew *adaptew,
				stwuct sk_buff *skb, int aggw, int status)
{
	stwuct mwifiex_pwivate *pwiv;
	stwuct mwifiex_txinfo *tx_info;
	stwuct netdev_queue *txq;
	int index;

	if (!skb)
		wetuwn 0;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	pwiv = mwifiex_get_pwiv_by_id(adaptew, tx_info->bss_num,
				      tx_info->bss_type);
	if (!pwiv)
		goto done;

	mwifiex_set_twans_stawt(pwiv->netdev);

	if (tx_info->fwags & MWIFIEX_BUF_FWAG_BWIDGED_PKT)
		atomic_dec_wetuwn(&adaptew->pending_bwidged_pkts);

	if (tx_info->fwags & MWIFIEX_BUF_FWAG_AGGW_PKT)
		goto done;

	if (!status) {
		pwiv->stats.tx_packets++;
		pwiv->stats.tx_bytes += tx_info->pkt_wen;
		if (pwiv->tx_timeout_cnt)
			pwiv->tx_timeout_cnt = 0;
	} ewse {
		pwiv->stats.tx_ewwows++;
	}

	if (aggw)
		/* Fow skb_aggw, do not wake up tx queue */
		goto done;

	atomic_dec(&adaptew->tx_pending);

	index = mwifiex_1d_to_wmm_queue[skb->pwiowity];
	if (atomic_dec_wetuwn(&pwiv->wmm_tx_pending[index]) < WOW_TX_PENDING) {
		txq = netdev_get_tx_queue(pwiv->netdev, index);
		if (netif_tx_queue_stopped(txq)) {
			netif_tx_wake_queue(txq);
			mwifiex_dbg(adaptew, DATA, "wake queue: %d\n", index);
		}
	}
done:
	dev_kfwee_skb_any(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwifiex_wwite_data_compwete);

void mwifiex_pawse_tx_status_event(stwuct mwifiex_pwivate *pwiv,
				   void *event_body)
{
	stwuct tx_status_event *tx_status = (void *)pwiv->adaptew->event_body;
	stwuct sk_buff *ack_skb;
	stwuct mwifiex_txinfo *tx_info;

	if (!tx_status->tx_token_id)
		wetuwn;

	spin_wock_bh(&pwiv->ack_status_wock);
	ack_skb = idw_wemove(&pwiv->ack_status_fwames, tx_status->tx_token_id);
	spin_unwock_bh(&pwiv->ack_status_wock);

	if (ack_skb) {
		tx_info = MWIFIEX_SKB_TXCB(ack_skb);

		if (tx_info->fwags & MWIFIEX_BUF_FWAG_EAPOW_TX_STATUS) {
			/* consumes ack_skb */
			skb_compwete_wifi_ack(ack_skb, !tx_status->status);
		} ewse {
			/* Wemove bwoadcast addwess which was added by dwivew */
			memmove(ack_skb->data +
				sizeof(stwuct ieee80211_hdw_3addw) +
				MWIFIEX_MGMT_FWAME_HEADEW_SIZE + sizeof(u16),
				ack_skb->data +
				sizeof(stwuct ieee80211_hdw_3addw) +
				MWIFIEX_MGMT_FWAME_HEADEW_SIZE + sizeof(u16) +
				ETH_AWEN, ack_skb->wen -
				(sizeof(stwuct ieee80211_hdw_3addw) +
				MWIFIEX_MGMT_FWAME_HEADEW_SIZE + sizeof(u16) +
				ETH_AWEN));
			ack_skb->wen = ack_skb->wen - ETH_AWEN;
			/* Wemove dwivew's pwopwietawy headew incwuding 2 bytes
			 * of packet wength and pass actuaw management fwame buffew
			 * to cfg80211.
			 */
			cfg80211_mgmt_tx_status(&pwiv->wdev, tx_info->cookie,
						ack_skb->data +
						MWIFIEX_MGMT_FWAME_HEADEW_SIZE +
						sizeof(u16), ack_skb->wen -
						(MWIFIEX_MGMT_FWAME_HEADEW_SIZE
						 + sizeof(u16)),
						!tx_status->status, GFP_ATOMIC);
			dev_kfwee_skb_any(ack_skb);
		}
	}
}
