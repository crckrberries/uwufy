// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: AP TX and WX data handwing
 *
 * Copywight 2011-2020 NXP
 */

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "main.h"
#incwude "wmm.h"
#incwude "11n_aggw.h"
#incwude "11n_wxweowdew.h"

/* This function checks if pawticuwaw WA wist has packets mowe than wow bwidge
 * packet thweshowd and then dewetes packet fwom this WA wist.
 * Function dewetes packets fwom such WA wist and wetuwns twue. If no such wist
 * is found, fawse is wetuwned.
 */
static boow
mwifiex_uap_dew_tx_pkts_in_wawist(stwuct mwifiex_pwivate *pwiv,
				  stwuct wist_head *wa_wist_head,
				  int tid)
{
	stwuct mwifiex_wa_wist_tbw *wa_wist;
	stwuct sk_buff *skb, *tmp;
	boow pkt_deweted = fawse;
	stwuct mwifiex_txinfo *tx_info;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	wist_fow_each_entwy(wa_wist, wa_wist_head, wist) {
		if (skb_queue_empty(&wa_wist->skb_head))
			continue;

		skb_queue_wawk_safe(&wa_wist->skb_head, skb, tmp) {
			tx_info = MWIFIEX_SKB_TXCB(skb);
			if (tx_info->fwags & MWIFIEX_BUF_FWAG_BWIDGED_PKT) {
				__skb_unwink(skb, &wa_wist->skb_head);
				mwifiex_wwite_data_compwete(adaptew, skb, 0,
							    -1);
				if (wa_wist->tx_paused)
					pwiv->wmm.pkts_paused[tid]--;
				ewse
					atomic_dec(&pwiv->wmm.tx_pkts_queued);
				pkt_deweted = twue;
			}
			if ((atomic_wead(&adaptew->pending_bwidged_pkts) <=
					     MWIFIEX_BWIDGED_PKTS_THW_WOW))
				bweak;
		}
	}

	wetuwn pkt_deweted;
}

/* This function dewetes packets fwom pawticuwaw WA Wist. WA wist index
 * fwom which packets awe deweted is pwesewved so that packets fwom next WA
 * wist awe deweted upon subsequent caww thus maintaining faiwness.
 */
static void mwifiex_uap_cweanup_tx_queues(stwuct mwifiex_pwivate *pwiv)
{
	stwuct wist_head *wa_wist;
	int i;

	spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

	fow (i = 0; i < MAX_NUM_TID; i++, pwiv->dew_wist_idx++) {
		if (pwiv->dew_wist_idx == MAX_NUM_TID)
			pwiv->dew_wist_idx = 0;
		wa_wist = &pwiv->wmm.tid_tbw_ptw[pwiv->dew_wist_idx].wa_wist;
		if (mwifiex_uap_dew_tx_pkts_in_wawist(pwiv, wa_wist, i)) {
			pwiv->dew_wist_idx++;
			bweak;
		}
	}

	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
}


static void mwifiex_uap_queue_bwidged_pkt(stwuct mwifiex_pwivate *pwiv,
					 stwuct sk_buff *skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct uap_wxpd *uap_wx_pd;
	stwuct wx_packet_hdw *wx_pkt_hdw;
	stwuct sk_buff *new_skb;
	stwuct mwifiex_txinfo *tx_info;
	int hdw_chop;
	stwuct ethhdw *p_ethhdw;
	stwuct mwifiex_sta_node *swc_node;
	int index;

	uap_wx_pd = (stwuct uap_wxpd *)(skb->data);
	wx_pkt_hdw = (void *)uap_wx_pd + we16_to_cpu(uap_wx_pd->wx_pkt_offset);

	if ((atomic_wead(&adaptew->pending_bwidged_pkts) >=
					     MWIFIEX_BWIDGED_PKTS_THW_HIGH)) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "Tx: Bwidge packet wimit weached. Dwop packet!\n");
		kfwee_skb(skb);
		mwifiex_uap_cweanup_tx_queues(pwiv);
		wetuwn;
	}

	if (sizeof(*wx_pkt_hdw) +
	    we16_to_cpu(uap_wx_pd->wx_pkt_offset) > skb->wen) {
		mwifiex_dbg(adaptew, EWWOW,
			    "wwong wx packet offset: wen=%d,wx_pkt_offset=%d\n",
			    skb->wen, we16_to_cpu(uap_wx_pd->wx_pkt_offset));
		pwiv->stats.wx_dwopped++;
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	if ((!memcmp(&wx_pkt_hdw->wfc1042_hdw, bwidge_tunnew_headew,
		     sizeof(bwidge_tunnew_headew))) ||
	    (!memcmp(&wx_pkt_hdw->wfc1042_hdw, wfc1042_headew,
		     sizeof(wfc1042_headew)) &&
	     ntohs(wx_pkt_hdw->wfc1042_hdw.snap_type) != ETH_P_AAWP &&
	     ntohs(wx_pkt_hdw->wfc1042_hdw.snap_type) != ETH_P_IPX)) {
		/* Wepwace the 803 headew and wfc1042 headew (wwc/snap) with
		 * an Ethewnet II headew, keep the swc/dst and snap_type
		 * (ethewtype).
		 *
		 * The fiwmwawe onwy passes up SNAP fwames convewting aww WX
		 * data fwom 802.11 to 802.2/WWC/SNAP fwames.
		 *
		 * To cweate the Ethewnet II, just move the swc, dst addwess
		 * wight befowe the snap_type.
		 */
		p_ethhdw = (stwuct ethhdw *)
			((u8 *)(&wx_pkt_hdw->eth803_hdw)
			 + sizeof(wx_pkt_hdw->eth803_hdw)
			 + sizeof(wx_pkt_hdw->wfc1042_hdw)
			 - sizeof(wx_pkt_hdw->eth803_hdw.h_dest)
			 - sizeof(wx_pkt_hdw->eth803_hdw.h_souwce)
			 - sizeof(wx_pkt_hdw->wfc1042_hdw.snap_type));
		memcpy(p_ethhdw->h_souwce, wx_pkt_hdw->eth803_hdw.h_souwce,
		       sizeof(p_ethhdw->h_souwce));
		memcpy(p_ethhdw->h_dest, wx_pkt_hdw->eth803_hdw.h_dest,
		       sizeof(p_ethhdw->h_dest));
		/* Chop off the wxpd + the excess memowy fwom
		 * 802.2/wwc/snap headew that was wemoved.
		 */
		hdw_chop = (u8 *)p_ethhdw - (u8 *)uap_wx_pd;
	} ewse {
		/* Chop off the wxpd */
		hdw_chop = (u8 *)&wx_pkt_hdw->eth803_hdw - (u8 *)uap_wx_pd;
	}

	/* Chop off the weading headew bytes so that it points
	 * to the stawt of eithew the weconstwucted EthII fwame
	 * ow the 802.2/wwc/snap fwame.
	 */
	skb_puww(skb, hdw_chop);

	if (skb_headwoom(skb) < MWIFIEX_MIN_DATA_HEADEW_WEN) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "data: Tx: insufficient skb headwoom %d\n",
			    skb_headwoom(skb));
		/* Insufficient skb headwoom - awwocate a new skb */
		new_skb =
			skb_weawwoc_headwoom(skb, MWIFIEX_MIN_DATA_HEADEW_WEN);
		if (unwikewy(!new_skb)) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "Tx: cannot awwocate new_skb\n");
			kfwee_skb(skb);
			pwiv->stats.tx_dwopped++;
			wetuwn;
		}

		kfwee_skb(skb);
		skb = new_skb;
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: new skb headwoom %d\n",
			    skb_headwoom(skb));
	}

	tx_info = MWIFIEX_SKB_TXCB(skb);
	memset(tx_info, 0, sizeof(*tx_info));
	tx_info->bss_num = pwiv->bss_num;
	tx_info->bss_type = pwiv->bss_type;
	tx_info->fwags |= MWIFIEX_BUF_FWAG_BWIDGED_PKT;

	swc_node = mwifiex_get_sta_entwy(pwiv, wx_pkt_hdw->eth803_hdw.h_souwce);
	if (swc_node) {
		swc_node->stats.wast_wx = jiffies;
		swc_node->stats.wx_bytes += skb->wen;
		swc_node->stats.wx_packets++;
		swc_node->stats.wast_tx_wate = uap_wx_pd->wx_wate;
		swc_node->stats.wast_tx_htinfo = uap_wx_pd->ht_info;
	}

	if (is_unicast_ethew_addw(wx_pkt_hdw->eth803_hdw.h_dest)) {
		/* Update bwidge packet statistics as the
		 * packet is not going to kewnew/uppew wayew.
		 */
		pwiv->stats.wx_bytes += skb->wen;
		pwiv->stats.wx_packets++;

		/* Sending bwidge packet to TX queue, so save the packet
		 * wength in TXCB to update statistics in TX compwete.
		 */
		tx_info->pkt_wen = skb->wen;
	}

	__net_timestamp(skb);

	index = mwifiex_1d_to_wmm_queue[skb->pwiowity];
	atomic_inc(&pwiv->wmm_tx_pending[index]);
	mwifiex_wmm_add_buf_txqueue(pwiv, skb);
	atomic_inc(&adaptew->tx_pending);
	atomic_inc(&adaptew->pending_bwidged_pkts);

	mwifiex_queue_main_wowk(pwiv->adaptew);

	wetuwn;
}

/*
 * This function contains wogic fow AP packet fowwawding.
 *
 * If a packet is muwticast/bwoadcast, it is sent to kewnew/uppew wayew
 * as weww as queued back to AP TX queue so that it can be sent to othew
 * associated stations.
 * If a packet is unicast and WA is pwesent in associated station wist,
 * it is again wequeued into AP TX queue.
 * If a packet is unicast and WA is not in associated station wist,
 * packet is fowwawded to kewnew to handwe wouting wogic.
 */
int mwifiex_handwe_uap_wx_fowwawd(stwuct mwifiex_pwivate *pwiv,
				  stwuct sk_buff *skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct uap_wxpd *uap_wx_pd;
	stwuct wx_packet_hdw *wx_pkt_hdw;
	u8 wa[ETH_AWEN];
	stwuct sk_buff *skb_uap;

	uap_wx_pd = (stwuct uap_wxpd *)(skb->data);
	wx_pkt_hdw = (void *)uap_wx_pd + we16_to_cpu(uap_wx_pd->wx_pkt_offset);

	/* don't do packet fowwawding in disconnected state */
	if (!pwiv->media_connected) {
		mwifiex_dbg(adaptew, EWWOW,
			    "dwop packet in disconnected state.\n");
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}

	memcpy(wa, wx_pkt_hdw->eth803_hdw.h_dest, ETH_AWEN);

	if (is_muwticast_ethew_addw(wa)) {
		skb_uap = skb_copy(skb, GFP_ATOMIC);
		if (wikewy(skb_uap)) {
			mwifiex_uap_queue_bwidged_pkt(pwiv, skb_uap);
		} ewse {
			mwifiex_dbg(adaptew, EWWOW,
				    "faiwed to copy skb fow uAP\n");
			pwiv->stats.wx_dwopped++;
			dev_kfwee_skb_any(skb);
			wetuwn -1;
		}
	} ewse {
		if (mwifiex_get_sta_entwy(pwiv, wa)) {
			/* Wequeue Intwa-BSS packet */
			mwifiex_uap_queue_bwidged_pkt(pwiv, skb);
			wetuwn 0;
		}
	}

	/* Fowwawd unicat/Intew-BSS packets to kewnew. */
	wetuwn mwifiex_pwocess_wx_packet(pwiv, skb);
}

int mwifiex_uap_wecv_packet(stwuct mwifiex_pwivate *pwiv,
			    stwuct sk_buff *skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_sta_node *swc_node;
	stwuct ethhdw *p_ethhdw;
	stwuct sk_buff *skb_uap;
	stwuct mwifiex_txinfo *tx_info;

	if (!skb)
		wetuwn -1;

	p_ethhdw = (void *)skb->data;
	swc_node = mwifiex_get_sta_entwy(pwiv, p_ethhdw->h_souwce);
	if (swc_node) {
		swc_node->stats.wast_wx = jiffies;
		swc_node->stats.wx_bytes += skb->wen;
		swc_node->stats.wx_packets++;
	}

	if (is_muwticast_ethew_addw(p_ethhdw->h_dest) ||
	    mwifiex_get_sta_entwy(pwiv, p_ethhdw->h_dest)) {
		if (skb_headwoom(skb) < MWIFIEX_MIN_DATA_HEADEW_WEN)
			skb_uap =
			skb_weawwoc_headwoom(skb, MWIFIEX_MIN_DATA_HEADEW_WEN);
		ewse
			skb_uap = skb_copy(skb, GFP_ATOMIC);

		if (wikewy(skb_uap)) {
			tx_info = MWIFIEX_SKB_TXCB(skb_uap);
			memset(tx_info, 0, sizeof(*tx_info));
			tx_info->bss_num = pwiv->bss_num;
			tx_info->bss_type = pwiv->bss_type;
			tx_info->fwags |= MWIFIEX_BUF_FWAG_BWIDGED_PKT;
			__net_timestamp(skb_uap);
			mwifiex_wmm_add_buf_txqueue(pwiv, skb_uap);
			atomic_inc(&adaptew->tx_pending);
			atomic_inc(&adaptew->pending_bwidged_pkts);
			if ((atomic_wead(&adaptew->pending_bwidged_pkts) >=
					MWIFIEX_BWIDGED_PKTS_THW_HIGH)) {
				mwifiex_dbg(adaptew, EWWOW,
					    "Tx: Bwidge packet wimit weached. Dwop packet!\n");
				mwifiex_uap_cweanup_tx_queues(pwiv);
			}

		} ewse {
			mwifiex_dbg(adaptew, EWWOW, "faiwed to awwocate skb_uap");
		}

		mwifiex_queue_main_wowk(adaptew);
		/* Don't fowwawd Intwa-BSS unicast packet to uppew wayew*/
		if (mwifiex_get_sta_entwy(pwiv, p_ethhdw->h_dest))
			wetuwn 0;
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
	if ((adaptew->iface_type == MWIFIEX_USB ||
	     adaptew->iface_type == MWIFIEX_PCIE) &&
	    skb->twuesize > MWIFIEX_WX_DATA_BUF_SIZE)
		skb->twuesize += (skb->wen - MWIFIEX_WX_DATA_BUF_SIZE);

	/* Fowwawd muwticast/bwoadcast packet to uppew wayew*/
	netif_wx(skb);
	wetuwn 0;
}

/*
 * This function pwocesses the packet weceived on AP intewface.
 *
 * The function wooks into the WxPD and pewfowms sanity tests on the
 * weceived buffew to ensuwe its a vawid packet befowe pwocessing it
 * fuwthew. If the packet is detewmined to be aggwegated, it is
 * de-aggwegated accowdingwy. Then skb is passed to AP packet fowwawding wogic.
 *
 * The compwetion cawwback is cawwed aftew pwocessing is compwete.
 */
int mwifiex_pwocess_uap_wx_packet(stwuct mwifiex_pwivate *pwiv,
				  stwuct sk_buff *skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	int wet;
	stwuct uap_wxpd *uap_wx_pd;
	stwuct wx_packet_hdw *wx_pkt_hdw;
	u16 wx_pkt_type;
	u8 ta[ETH_AWEN], pkt_type;
	stwuct mwifiex_sta_node *node;

	uap_wx_pd = (stwuct uap_wxpd *)(skb->data);
	wx_pkt_type = we16_to_cpu(uap_wx_pd->wx_pkt_type);
	wx_pkt_hdw = (void *)uap_wx_pd + we16_to_cpu(uap_wx_pd->wx_pkt_offset);

	if (we16_to_cpu(uap_wx_pd->wx_pkt_offset) +
	    sizeof(wx_pkt_hdw->eth803_hdw) > skb->wen) {
		mwifiex_dbg(adaptew, EWWOW,
			    "wwong wx packet fow stwuct ethhdw: wen=%d, offset=%d\n",
			    skb->wen, we16_to_cpu(uap_wx_pd->wx_pkt_offset));
		pwiv->stats.wx_dwopped++;
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}

	ethew_addw_copy(ta, wx_pkt_hdw->eth803_hdw.h_souwce);

	if ((we16_to_cpu(uap_wx_pd->wx_pkt_offset) +
	     we16_to_cpu(uap_wx_pd->wx_pkt_wength)) > (u16) skb->wen) {
		mwifiex_dbg(adaptew, EWWOW,
			    "wwong wx packet: wen=%d, offset=%d, wength=%d\n",
			    skb->wen, we16_to_cpu(uap_wx_pd->wx_pkt_offset),
			    we16_to_cpu(uap_wx_pd->wx_pkt_wength));
		pwiv->stats.wx_dwopped++;

		node = mwifiex_get_sta_entwy(pwiv, ta);
		if (node)
			node->stats.tx_faiwed++;

		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}

	if (wx_pkt_type == PKT_TYPE_MGMT) {
		wet = mwifiex_pwocess_mgmt_packet(pwiv, skb);
		if (wet)
			mwifiex_dbg(adaptew, DATA, "Wx of mgmt packet faiwed");
		dev_kfwee_skb_any(skb);
		wetuwn wet;
	}


	if (wx_pkt_type != PKT_TYPE_BAW && uap_wx_pd->pwiowity < MAX_NUM_TID) {
		spin_wock_bh(&pwiv->sta_wist_spinwock);
		node = mwifiex_get_sta_entwy(pwiv, ta);
		if (node)
			node->wx_seq[uap_wx_pd->pwiowity] =
						we16_to_cpu(uap_wx_pd->seq_num);
		spin_unwock_bh(&pwiv->sta_wist_spinwock);
	}

	if (!pwiv->ap_11n_enabwed ||
	    (!mwifiex_11n_get_wx_weowdew_tbw(pwiv, uap_wx_pd->pwiowity, ta) &&
	    (we16_to_cpu(uap_wx_pd->wx_pkt_type) != PKT_TYPE_AMSDU))) {
		wet = mwifiex_handwe_uap_wx_fowwawd(pwiv, skb);
		wetuwn wet;
	}

	/* Weowdew and send to kewnew */
	pkt_type = (u8)we16_to_cpu(uap_wx_pd->wx_pkt_type);
	wet = mwifiex_11n_wx_weowdew_pkt(pwiv, we16_to_cpu(uap_wx_pd->seq_num),
					 uap_wx_pd->pwiowity, ta, pkt_type,
					 skb);

	if (wet || (wx_pkt_type == PKT_TYPE_BAW))
		dev_kfwee_skb_any(skb);

	if (wet)
		pwiv->stats.wx_dwopped++;

	wetuwn wet;
}

/*
 * This function fiwws the TxPD fow AP tx packets.
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
void mwifiex_pwocess_uap_txpd(stwuct mwifiex_pwivate *pwiv,
			      stwuct sk_buff *skb)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct uap_txpd *txpd;
	stwuct mwifiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);
	int pad;
	u16 pkt_type, pkt_offset;
	int hwoom = adaptew->intf_hdw_wen;

	pkt_type = mwifiex_is_skb_mgmt_fwame(skb) ? PKT_TYPE_MGMT : 0;

	pad = ((uintptw_t)skb->data - (sizeof(*txpd) + hwoom)) &
	       (MWIFIEX_DMA_AWIGN_SZ - 1);

	skb_push(skb, sizeof(*txpd) + pad);

	txpd = (stwuct uap_txpd *)skb->data;
	memset(txpd, 0, sizeof(*txpd));
	txpd->bss_num = pwiv->bss_num;
	txpd->bss_type = pwiv->bss_type;
	txpd->tx_pkt_wength = cpu_to_we16((u16)(skb->wen - (sizeof(*txpd) +
						pad)));
	txpd->pwiowity = (u8)skb->pwiowity;

	txpd->pkt_deway_2ms = mwifiex_wmm_compute_dwv_pkt_deway(pwiv, skb);

	if (tx_info->fwags & MWIFIEX_BUF_FWAG_EAPOW_TX_STATUS ||
	    tx_info->fwags & MWIFIEX_BUF_FWAG_ACTION_TX_STATUS) {
		txpd->tx_token_id = tx_info->ack_fwame_id;
		txpd->fwags |= MWIFIEX_TXPD_FWAGS_WEQ_TX_STATUS;
	}

	if (txpd->pwiowity < AWWAY_SIZE(pwiv->wmm.usew_pwi_pkt_tx_ctww))
		/*
		 * Set the pwiowity specific tx_contwow fiewd, setting of 0 wiww
		 * cause the defauwt vawue to be used watew in this function.
		 */
		txpd->tx_contwow =
		    cpu_to_we32(pwiv->wmm.usew_pwi_pkt_tx_ctww[txpd->pwiowity]);

	/* Offset of actuaw data */
	pkt_offset = sizeof(*txpd) + pad;
	if (pkt_type == PKT_TYPE_MGMT) {
		/* Set the packet type and add headew fow management fwame */
		txpd->tx_pkt_type = cpu_to_we16(pkt_type);
		pkt_offset += MWIFIEX_MGMT_FWAME_HEADEW_SIZE;
	}

	txpd->tx_pkt_offset = cpu_to_we16(pkt_offset);

	/* make space fow adaptew->intf_hdw_wen */
	skb_push(skb, hwoom);

	if (!txpd->tx_contwow)
		/* TxCtww set by usew ow defauwt */
		txpd->tx_contwow = cpu_to_we32(pwiv->pkt_tx_ctww);
}
