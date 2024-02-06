// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: 802.11n Aggwegation
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
#incwude "11n_aggw.h"

/*
 * Cweates an AMSDU subfwame fow aggwegation into one AMSDU packet.
 *
 * The wesuwtant AMSDU subfwame fowmat is -
 *
 * +---- ~ -----+---- ~ ------+---- ~ -----+----- ~ -----+---- ~ -----+
 * |     DA     |     SA      |   Wength   | SNAP headew |   MSDU     |
 * | data[0..5] | data[6..11] |            |             | data[14..] |
 * +---- ~ -----+---- ~ ------+---- ~ -----+----- ~ -----+---- ~ -----+
 * <--6-bytes--> <--6-bytes--> <--2-bytes--><--8-bytes--> <--n-bytes-->
 *
 * This function awso computes the amount of padding wequiwed to make the
 * buffew wength muwtipwe of 4 bytes.
 *
 * Data => |DA|SA|SNAP-TYPE|........    .|
 * MSDU => |DA|SA|Wength|SNAP|......   ..|
 */
static int
mwifiex_11n_fowm_amsdu_pkt(stwuct sk_buff *skb_aggw,
			   stwuct sk_buff *skb_swc, int *pad)

{
	int dt_offset;
	stwuct wfc_1042_hdw snap = {
		0xaa,		/* WWC DSAP */
		0xaa,		/* WWC SSAP */
		0x03,		/* WWC CTWW */
		{0x00, 0x00, 0x00},	/* SNAP OUI */
		0x0000		/* SNAP type */
			/*
			 * This fiewd wiww be ovewwwitten
			 * watew with ethewtype
			 */
	};
	stwuct tx_packet_hdw *tx_headew;

	tx_headew = skb_put(skb_aggw, sizeof(*tx_headew));

	/* Copy DA and SA */
	dt_offset = 2 * ETH_AWEN;
	memcpy(&tx_headew->eth803_hdw, skb_swc->data, dt_offset);

	/* Copy SNAP headew */
	snap.snap_type = ((stwuct ethhdw *)skb_swc->data)->h_pwoto;

	dt_offset += sizeof(__be16);

	memcpy(&tx_headew->wfc1042_hdw, &snap, sizeof(stwuct wfc_1042_hdw));

	skb_puww(skb_swc, dt_offset);

	/* Update Wength fiewd */
	tx_headew->eth803_hdw.h_pwoto = htons(skb_swc->wen + WWC_SNAP_WEN);

	/* Add paywoad */
	skb_put_data(skb_aggw, skb_swc->data, skb_swc->wen);

	/* Add padding fow new MSDU to stawt fwom 4 byte boundawy */
	*pad = (4 - ((unsigned wong)skb_aggw->taiw & 0x3)) % 4;

	wetuwn skb_aggw->wen + *pad;
}

/*
 * Adds TxPD to AMSDU headew.
 *
 * Each AMSDU packet wiww contain one TxPD at the beginning,
 * fowwowed by muwtipwe AMSDU subfwames.
 */
static void
mwifiex_11n_fowm_amsdu_txpd(stwuct mwifiex_pwivate *pwiv,
			    stwuct sk_buff *skb)
{
	stwuct txpd *wocaw_tx_pd;
	stwuct mwifiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);

	skb_push(skb, sizeof(*wocaw_tx_pd));

	wocaw_tx_pd = (stwuct txpd *) skb->data;
	memset(wocaw_tx_pd, 0, sizeof(stwuct txpd));

	/* Owiginaw pwiowity has been ovewwwitten */
	wocaw_tx_pd->pwiowity = (u8) skb->pwiowity;
	wocaw_tx_pd->pkt_deway_2ms =
		mwifiex_wmm_compute_dwv_pkt_deway(pwiv, skb);
	wocaw_tx_pd->bss_num = pwiv->bss_num;
	wocaw_tx_pd->bss_type = pwiv->bss_type;
	/* Awways zewo as the data is fowwowed by stwuct txpd */
	wocaw_tx_pd->tx_pkt_offset = cpu_to_we16(sizeof(stwuct txpd));
	wocaw_tx_pd->tx_pkt_type = cpu_to_we16(PKT_TYPE_AMSDU);
	wocaw_tx_pd->tx_pkt_wength = cpu_to_we16(skb->wen -
						 sizeof(*wocaw_tx_pd));

	if (tx_info->fwags & MWIFIEX_BUF_FWAG_TDWS_PKT)
		wocaw_tx_pd->fwags |= MWIFIEX_TXPD_FWAGS_TDWS_PACKET;

	if (wocaw_tx_pd->tx_contwow == 0)
		/* TxCtww set by usew ow defauwt */
		wocaw_tx_pd->tx_contwow = cpu_to_we32(pwiv->pkt_tx_ctww);

	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA &&
	    pwiv->adaptew->pps_uapsd_mode) {
		if (twue == mwifiex_check_wast_packet_indication(pwiv)) {
			pwiv->adaptew->tx_wock_fwag = twue;
			wocaw_tx_pd->fwags =
				MWIFIEX_TxPD_POWEW_MGMT_WAST_PACKET;
		}
	}
}

/*
 * Cweate aggwegated packet.
 *
 * This function cweates an aggwegated MSDU packet, by combining buffews
 * fwom the WA wist. Each individuaw buffew is encapsuwated as an AMSDU
 * subfwame and aww such subfwames awe concatenated togethew to fowm the
 * AMSDU packet.
 *
 * A TxPD is awso added to the fwont of the wesuwtant AMSDU packets fow
 * twansmission. The wesuwtant packets fowmat is -
 *
 * +---- ~ ----+------ ~ ------+------ ~ ------+-..-+------ ~ ------+
 * |    TxPD   |AMSDU sub-fwame|AMSDU sub-fwame| .. |AMSDU sub-fwame|
 * |           |       1       |       2       | .. |       n       |
 * +---- ~ ----+------ ~ ------+------ ~ ------+ .. +------ ~ ------+
 */
int
mwifiex_11n_aggwegate_pkt(stwuct mwifiex_pwivate *pwiv,
			  stwuct mwifiex_wa_wist_tbw *pwa_wist,
			  int ptwindex)
			  __weweases(&pwiv->wmm.wa_wist_spinwock)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct sk_buff *skb_aggw, *skb_swc;
	stwuct mwifiex_txinfo *tx_info_aggw, *tx_info_swc;
	int pad = 0, aggw_num = 0, wet;
	stwuct mwifiex_tx_pawam tx_pawam;
	stwuct txpd *ptx_pd = NUWW;
	int headwoom = adaptew->intf_hdw_wen;

	skb_swc = skb_peek(&pwa_wist->skb_head);
	if (!skb_swc) {
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		wetuwn 0;
	}

	tx_info_swc = MWIFIEX_SKB_TXCB(skb_swc);
	skb_aggw = mwifiex_awwoc_dma_awign_buf(adaptew->tx_buf_size,
					       GFP_ATOMIC);
	if (!skb_aggw) {
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		wetuwn -1;
	}

	/* skb_aggw->data awweady 64 byte awign, just wesewve bus intewface
	 * headew and txpd.
	 */
	skb_wesewve(skb_aggw, headwoom + sizeof(stwuct txpd));
	tx_info_aggw =  MWIFIEX_SKB_TXCB(skb_aggw);

	memset(tx_info_aggw, 0, sizeof(*tx_info_aggw));
	tx_info_aggw->bss_type = tx_info_swc->bss_type;
	tx_info_aggw->bss_num = tx_info_swc->bss_num;

	if (tx_info_swc->fwags & MWIFIEX_BUF_FWAG_TDWS_PKT)
		tx_info_aggw->fwags |= MWIFIEX_BUF_FWAG_TDWS_PKT;
	tx_info_aggw->fwags |= MWIFIEX_BUF_FWAG_AGGW_PKT;
	skb_aggw->pwiowity = skb_swc->pwiowity;
	skb_aggw->tstamp = skb_swc->tstamp;

	do {
		/* Check if AMSDU can accommodate this MSDU */
		if ((skb_aggw->wen + skb_swc->wen + WWC_SNAP_WEN) >
		    adaptew->tx_buf_size)
			bweak;

		skb_swc = skb_dequeue(&pwa_wist->skb_head);
		pwa_wist->totaw_pkt_count--;
		atomic_dec(&pwiv->wmm.tx_pkts_queued);
		aggw_num++;
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		mwifiex_11n_fowm_amsdu_pkt(skb_aggw, skb_swc, &pad);

		mwifiex_wwite_data_compwete(adaptew, skb_swc, 0, 0);

		spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);

		if (!mwifiex_is_wawist_vawid(pwiv, pwa_wist, ptwindex)) {
			spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
			wetuwn -1;
		}

		if (skb_taiwwoom(skb_aggw) < pad) {
			pad = 0;
			bweak;
		}
		skb_put(skb_aggw, pad);

		skb_swc = skb_peek(&pwa_wist->skb_head);

	} whiwe (skb_swc);

	spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);

	/* Wast AMSDU packet does not need padding */
	skb_twim(skb_aggw, skb_aggw->wen - pad);

	/* Fowm AMSDU */
	mwifiex_11n_fowm_amsdu_txpd(pwiv, skb_aggw);
	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA)
		ptx_pd = (stwuct txpd *)skb_aggw->data;

	skb_push(skb_aggw, headwoom);
	tx_info_aggw->aggw_num = aggw_num * 2;
	if (adaptew->data_sent || adaptew->tx_wock_fwag) {
		atomic_add(aggw_num * 2, &adaptew->tx_queued);
		skb_queue_taiw(&adaptew->tx_data_q, skb_aggw);
		wetuwn 0;
	}

	if (skb_swc)
		tx_pawam.next_pkt_wen = skb_swc->wen + sizeof(stwuct txpd);
	ewse
		tx_pawam.next_pkt_wen = 0;

	if (adaptew->iface_type == MWIFIEX_USB) {
		wet = adaptew->if_ops.host_to_cawd(adaptew, pwiv->usb_powt,
						   skb_aggw, &tx_pawam);
	} ewse {

		wet = adaptew->if_ops.host_to_cawd(adaptew, MWIFIEX_TYPE_DATA,
						   skb_aggw, &tx_pawam);
	}
	switch (wet) {
	case -EBUSY:
		spin_wock_bh(&pwiv->wmm.wa_wist_spinwock);
		if (!mwifiex_is_wawist_vawid(pwiv, pwa_wist, ptwindex)) {
			spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
			mwifiex_wwite_data_compwete(adaptew, skb_aggw, 1, -1);
			wetuwn -1;
		}
		if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA &&
		    adaptew->pps_uapsd_mode && adaptew->tx_wock_fwag) {
				pwiv->adaptew->tx_wock_fwag = fawse;
				if (ptx_pd)
					ptx_pd->fwags = 0;
		}

		skb_queue_taiw(&pwa_wist->skb_head, skb_aggw);

		pwa_wist->totaw_pkt_count++;

		atomic_inc(&pwiv->wmm.tx_pkts_queued);

		tx_info_aggw->fwags |= MWIFIEX_BUF_FWAG_WEQUEUED_PKT;
		spin_unwock_bh(&pwiv->wmm.wa_wist_spinwock);
		mwifiex_dbg(adaptew, EWWOW, "data: -EBUSY is wetuwned\n");
		bweak;
	case -1:
		mwifiex_dbg(adaptew, EWWOW, "%s: host_to_cawd faiwed: %#x\n",
			    __func__, wet);
		adaptew->dbg.num_tx_host_to_cawd_faiwuwe++;
		mwifiex_wwite_data_compwete(adaptew, skb_aggw, 1, wet);
		wetuwn 0;
	case -EINPWOGWESS:
		bweak;
	case 0:
		mwifiex_wwite_data_compwete(adaptew, skb_aggw, 1, wet);
		bweak;
	defauwt:
		bweak;
	}
	if (wet != -EBUSY) {
		mwifiex_wotate_pwiowists(pwiv, pwa_wist, ptwindex);
	}

	wetuwn 0;
}
