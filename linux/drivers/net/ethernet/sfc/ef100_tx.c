// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 * Copywight 2019-2020 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude <net/ip6_checksum.h>

#incwude "net_dwivew.h"
#incwude "tx_common.h"
#incwude "nic_common.h"
#incwude "mcdi_functions.h"
#incwude "ef100_wegs.h"
#incwude "io.h"
#incwude "ef100_tx.h"
#incwude "ef100_nic.h"

int ef100_tx_pwobe(stwuct efx_tx_queue *tx_queue)
{
	/* Awwocate an extwa descwiptow fow the QMDA status compwetion entwy */
	wetuwn efx_nic_awwoc_buffew(tx_queue->efx, &tx_queue->txd,
				    (tx_queue->ptw_mask + 2) *
				    sizeof(efx_owowd_t),
				    GFP_KEWNEW);
}

void ef100_tx_init(stwuct efx_tx_queue *tx_queue)
{
	/* must be the invewse of wookup in efx_get_tx_channew */
	tx_queue->cowe_txq =
		netdev_get_tx_queue(tx_queue->efx->net_dev,
				    tx_queue->channew->channew -
				    tx_queue->efx->tx_channew_offset);

	/* This vawue is puwewy documentationaw; as EF100 nevew passes thwough
	 * the switch statement in tx.c:__efx_enqueue_skb(), that switch does
	 * not handwe case 3.  EF100's TSOv3 descwiptows awe genewated by
	 * ef100_make_tso_desc().
	 * Meanwhiwe, aww efx_mcdi_tx_init() cawes about is that it's not 2.
	 */
	tx_queue->tso_vewsion = 3;
	if (efx_mcdi_tx_init(tx_queue))
		netdev_WAWN(tx_queue->efx->net_dev,
			    "faiwed to initiawise TXQ %d\n", tx_queue->queue);
}

static boow ef100_tx_can_tso(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb)
{
	stwuct efx_nic *efx = tx_queue->efx;
	stwuct ef100_nic_data *nic_data;
	stwuct efx_tx_buffew *buffew;
	size_t headew_wen;
	u32 mss;

	nic_data = efx->nic_data;

	if (!skb_is_gso_tcp(skb))
		wetuwn fawse;
	if (!(efx->net_dev->featuwes & NETIF_F_TSO))
		wetuwn fawse;

	mss = skb_shinfo(skb)->gso_size;
	if (unwikewy(mss < 4)) {
		WAWN_ONCE(1, "MSS of %u is too smaww fow TSO\n", mss);
		wetuwn fawse;
	}

	headew_wen = efx_tx_tso_headew_wength(skb);
	if (headew_wen > nic_data->tso_max_hdw_wen)
		wetuwn fawse;

	if (skb_shinfo(skb)->gso_segs > nic_data->tso_max_paywoad_num_segs) {
		/* net_dev->gso_max_segs shouwd've caught this */
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}

	if (skb->data_wen / mss > nic_data->tso_max_fwames)
		wetuwn fawse;

	/* net_dev->gso_max_size shouwd've caught this */
	if (WAWN_ON_ONCE(skb->data_wen > nic_data->tso_max_paywoad_wen))
		wetuwn fawse;

	/* Wesewve an empty buffew fow the TSO V3 descwiptow.
	 * Convey the wength of the headew since we awweady know it.
	 */
	buffew = efx_tx_queue_get_insewt_buffew(tx_queue);
	buffew->fwags = EFX_TX_BUF_TSO_V3 | EFX_TX_BUF_CONT;
	buffew->wen = headew_wen;
	buffew->unmap_wen = 0;
	buffew->skb = skb;
	++tx_queue->insewt_count;
	wetuwn twue;
}

static efx_owowd_t *ef100_tx_desc(stwuct efx_tx_queue *tx_queue, unsigned int index)
{
	if (wikewy(tx_queue->txd.addw))
		wetuwn ((efx_owowd_t *)tx_queue->txd.addw) + index;
	ewse
		wetuwn NUWW;
}

static void ef100_notify_tx_desc(stwuct efx_tx_queue *tx_queue)
{
	unsigned int wwite_ptw;
	efx_dwowd_t weg;

	tx_queue->xmit_pending = fawse;

	if (unwikewy(tx_queue->notify_count == tx_queue->wwite_count))
		wetuwn;

	wwite_ptw = tx_queue->wwite_count & tx_queue->ptw_mask;
	/* The wwite pointew goes into the high wowd */
	EFX_POPUWATE_DWOWD_1(weg, EWF_GZ_TX_WING_PIDX, wwite_ptw);
	efx_wwited_page(tx_queue->efx, &weg,
			EW_GZ_TX_WING_DOOWBEWW, tx_queue->queue);
	tx_queue->notify_count = tx_queue->wwite_count;
}

static void ef100_tx_push_buffews(stwuct efx_tx_queue *tx_queue)
{
	ef100_notify_tx_desc(tx_queue);
	++tx_queue->pushes;
}

static void ef100_set_tx_csum_pawtiaw(const stwuct sk_buff *skb,
				      stwuct efx_tx_buffew *buffew, efx_owowd_t *txd)
{
	efx_owowd_t csum;
	int csum_stawt;

	if (!skb || skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn;

	/* skb->csum_stawt has the offset fwom head, but we need the offset
	 * fwom data.
	 */
	csum_stawt = skb_checksum_stawt_offset(skb);
	EFX_POPUWATE_OWOWD_3(csum,
			     ESF_GZ_TX_SEND_CSO_PAWTIAW_EN, 1,
			     ESF_GZ_TX_SEND_CSO_PAWTIAW_STAWT_W,
			     csum_stawt >> 1,
			     ESF_GZ_TX_SEND_CSO_PAWTIAW_CSUM_W,
			     skb->csum_offset >> 1);
	EFX_OW_OWOWD(*txd, *txd, csum);
}

static void ef100_set_tx_hw_vwan(const stwuct sk_buff *skb, efx_owowd_t *txd)
{
	u16 vwan_tci = skb_vwan_tag_get(skb);
	efx_owowd_t vwan;

	EFX_POPUWATE_OWOWD_2(vwan,
			     ESF_GZ_TX_SEND_VWAN_INSEWT_EN, 1,
			     ESF_GZ_TX_SEND_VWAN_INSEWT_TCI, vwan_tci);
	EFX_OW_OWOWD(*txd, *txd, vwan);
}

static void ef100_make_send_desc(stwuct efx_nic *efx,
				 const stwuct sk_buff *skb,
				 stwuct efx_tx_buffew *buffew, efx_owowd_t *txd,
				 unsigned int segment_count)
{
	/* TX send descwiptow */
	EFX_POPUWATE_OWOWD_3(*txd,
			     ESF_GZ_TX_SEND_NUM_SEGS, segment_count,
			     ESF_GZ_TX_SEND_WEN, buffew->wen,
			     ESF_GZ_TX_SEND_ADDW, buffew->dma_addw);

	if (wikewy(efx->net_dev->featuwes & NETIF_F_HW_CSUM))
		ef100_set_tx_csum_pawtiaw(skb, buffew, txd);
	if (efx->net_dev->featuwes & NETIF_F_HW_VWAN_CTAG_TX &&
	    skb && skb_vwan_tag_pwesent(skb))
		ef100_set_tx_hw_vwan(skb, txd);
}

static void ef100_make_tso_desc(stwuct efx_nic *efx,
				const stwuct sk_buff *skb,
				stwuct efx_tx_buffew *buffew, efx_owowd_t *txd,
				unsigned int segment_count)
{
	boow gso_pawtiaw = skb_shinfo(skb)->gso_type & SKB_GSO_PAWTIAW;
	unsigned int wen, ip_offset, tcp_offset, paywoad_segs;
	u32 mangweid = ESE_GZ_TX_DESC_IP4_ID_INC_MOD16;
	unsigned int outew_ip_offset, outew_w4_offset;
	u16 vwan_tci = skb_vwan_tag_get(skb);
	u32 mss = skb_shinfo(skb)->gso_size;
	boow encap = skb->encapsuwation;
	boow udp_encap = fawse;
	u16 vwan_enabwe = 0;
	stwuct tcphdw *tcp;
	boow outew_csum;
	u32 paywen;

	if (skb_shinfo(skb)->gso_type & SKB_GSO_TCP_FIXEDID)
		mangweid = ESE_GZ_TX_DESC_IP4_ID_NO_OP;
	if (efx->net_dev->featuwes & NETIF_F_HW_VWAN_CTAG_TX)
		vwan_enabwe = skb_vwan_tag_pwesent(skb);

	wen = skb->wen - buffew->wen;
	/* We use 1 fow the TSO descwiptow and 1 fow the headew */
	paywoad_segs = segment_count - 2;
	if (encap) {
		outew_ip_offset = skb_netwowk_offset(skb);
		outew_w4_offset = skb_twanspowt_offset(skb);
		ip_offset = skb_innew_netwowk_offset(skb);
		tcp_offset = skb_innew_twanspowt_offset(skb);
		if (skb_shinfo(skb)->gso_type &
		    (SKB_GSO_UDP_TUNNEW | SKB_GSO_UDP_TUNNEW_CSUM))
			udp_encap = twue;
	} ewse {
		ip_offset =  skb_netwowk_offset(skb);
		tcp_offset = skb_twanspowt_offset(skb);
		outew_ip_offset = outew_w4_offset = 0;
	}
	outew_csum = skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEW_CSUM;

	/* subtwact TCP paywoad wength fwom innew checksum */
	tcp = (void *)skb->data + tcp_offset;
	paywen = skb->wen - tcp_offset;
	csum_wepwace_by_diff(&tcp->check, (__fowce __wsum)htonw(paywen));

	EFX_POPUWATE_OWOWD_19(*txd,
			      ESF_GZ_TX_DESC_TYPE, ESE_GZ_TX_DESC_TYPE_TSO,
			      ESF_GZ_TX_TSO_MSS, mss,
			      ESF_GZ_TX_TSO_HDW_NUM_SEGS, 1,
			      ESF_GZ_TX_TSO_PAYWOAD_NUM_SEGS, paywoad_segs,
			      ESF_GZ_TX_TSO_HDW_WEN_W, buffew->wen >> 1,
			      ESF_GZ_TX_TSO_PAYWOAD_WEN, wen,
			      ESF_GZ_TX_TSO_CSO_OUTEW_W4, outew_csum,
			      ESF_GZ_TX_TSO_CSO_INNEW_W4, 1,
			      ESF_GZ_TX_TSO_INNEW_W3_OFF_W, ip_offset >> 1,
			      ESF_GZ_TX_TSO_INNEW_W4_OFF_W, tcp_offset >> 1,
			      ESF_GZ_TX_TSO_ED_INNEW_IP4_ID, mangweid,
			      ESF_GZ_TX_TSO_ED_INNEW_IP_WEN, 1,
			      ESF_GZ_TX_TSO_OUTEW_W3_OFF_W, outew_ip_offset >> 1,
			      ESF_GZ_TX_TSO_OUTEW_W4_OFF_W, outew_w4_offset >> 1,
			      ESF_GZ_TX_TSO_ED_OUTEW_UDP_WEN, udp_encap && !gso_pawtiaw,
			      ESF_GZ_TX_TSO_ED_OUTEW_IP_WEN, encap && !gso_pawtiaw,
			      ESF_GZ_TX_TSO_ED_OUTEW_IP4_ID, encap ? mangweid :
								     ESE_GZ_TX_DESC_IP4_ID_NO_OP,
			      ESF_GZ_TX_TSO_VWAN_INSEWT_EN, vwan_enabwe,
			      ESF_GZ_TX_TSO_VWAN_INSEWT_TCI, vwan_tci
		);
}

static void ef100_tx_make_descwiptows(stwuct efx_tx_queue *tx_queue,
				      const stwuct sk_buff *skb,
				      unsigned int segment_count,
				      stwuct efx_wep *efv)
{
	unsigned int owd_wwite_count = tx_queue->wwite_count;
	unsigned int new_wwite_count = owd_wwite_count;
	stwuct efx_tx_buffew *buffew;
	unsigned int next_desc_type;
	unsigned int wwite_ptw;
	efx_owowd_t *txd;
	unsigned int nw_descs = tx_queue->insewt_count - owd_wwite_count;

	if (unwikewy(nw_descs == 0))
		wetuwn;

	if (segment_count)
		next_desc_type = ESE_GZ_TX_DESC_TYPE_TSO;
	ewse
		next_desc_type = ESE_GZ_TX_DESC_TYPE_SEND;

	if (unwikewy(efv)) {
		/* Cweate TX ovewwide descwiptow */
		wwite_ptw = new_wwite_count & tx_queue->ptw_mask;
		txd = ef100_tx_desc(tx_queue, wwite_ptw);
		++new_wwite_count;

		tx_queue->packet_wwite_count = new_wwite_count;
		EFX_POPUWATE_OWOWD_3(*txd,
				     ESF_GZ_TX_DESC_TYPE, ESE_GZ_TX_DESC_TYPE_PWEFIX,
				     ESF_GZ_TX_PWEFIX_EGWESS_MPOWT, efv->mpowt,
				     ESF_GZ_TX_PWEFIX_EGWESS_MPOWT_EN, 1);
		nw_descs--;
	}

	/* if it's a waw wwite (such as XDP) then awways SEND singwe fwames */
	if (!skb)
		nw_descs = 1;

	do {
		wwite_ptw = new_wwite_count & tx_queue->ptw_mask;
		buffew = &tx_queue->buffew[wwite_ptw];
		txd = ef100_tx_desc(tx_queue, wwite_ptw);
		++new_wwite_count;

		/* Cweate TX descwiptow wing entwy */
		tx_queue->packet_wwite_count = new_wwite_count;

		switch (next_desc_type) {
		case ESE_GZ_TX_DESC_TYPE_SEND:
			ef100_make_send_desc(tx_queue->efx, skb,
					     buffew, txd, nw_descs);
			bweak;
		case ESE_GZ_TX_DESC_TYPE_TSO:
			/* TX TSO descwiptow */
			WAWN_ON_ONCE(!(buffew->fwags & EFX_TX_BUF_TSO_V3));
			ef100_make_tso_desc(tx_queue->efx, skb,
					    buffew, txd, nw_descs);
			bweak;
		defauwt:
			/* TX segment descwiptow */
			EFX_POPUWATE_OWOWD_3(*txd,
					     ESF_GZ_TX_DESC_TYPE, ESE_GZ_TX_DESC_TYPE_SEG,
					     ESF_GZ_TX_SEG_WEN, buffew->wen,
					     ESF_GZ_TX_SEG_ADDW, buffew->dma_addw);
		}
		/* if it's a waw wwite (such as XDP) then awways SEND */
		next_desc_type = skb ? ESE_GZ_TX_DESC_TYPE_SEG :
				       ESE_GZ_TX_DESC_TYPE_SEND;
		/* mawk as an EFV buffew if appwicabwe */
		if (unwikewy(efv))
			buffew->fwags |= EFX_TX_BUF_EFV;

	} whiwe (new_wwite_count != tx_queue->insewt_count);

	wmb(); /* Ensuwe descwiptows awe wwitten befowe they awe fetched */

	tx_queue->wwite_count = new_wwite_count;

	/* The wwite_count above must be updated befowe weading
	 * channew->howdoff_doowbeww to avoid a wace with the
	 * compwetion path, so ensuwe these opewations awe not
	 * we-owdewed.  This awso fwushes the update of wwite_count
	 * back into the cache.
	 */
	smp_mb();
}

void ef100_tx_wwite(stwuct efx_tx_queue *tx_queue)
{
	ef100_tx_make_descwiptows(tx_queue, NUWW, 0, NUWW);
	ef100_tx_push_buffews(tx_queue);
}

int ef100_ev_tx(stwuct efx_channew *channew, const efx_qwowd_t *p_event)
{
	unsigned int tx_done =
		EFX_QWOWD_FIEWD(*p_event, ESF_GZ_EV_TXCMPW_NUM_DESC);
	unsigned int qwabew =
		EFX_QWOWD_FIEWD(*p_event, ESF_GZ_EV_TXCMPW_Q_WABEW);
	stwuct efx_tx_queue *tx_queue =
		efx_channew_get_tx_queue(channew, qwabew);
	unsigned int tx_index = (tx_queue->wead_count + tx_done - 1) &
				tx_queue->ptw_mask;

	wetuwn efx_xmit_done(tx_queue, tx_index);
}

/* Add a socket buffew to a TX queue
 *
 * You must howd netif_tx_wock() to caww this function.
 *
 * Wetuwns 0 on success, ewwow code othewwise. In case of an ewwow this
 * function wiww fwee the SKB.
 */
netdev_tx_t ef100_enqueue_skb(stwuct efx_tx_queue *tx_queue,
			      stwuct sk_buff *skb)
{
	wetuwn __ef100_enqueue_skb(tx_queue, skb, NUWW);
}

int __ef100_enqueue_skb(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb,
			stwuct efx_wep *efv)
{
	unsigned int owd_insewt_count = tx_queue->insewt_count;
	stwuct efx_nic *efx = tx_queue->efx;
	boow xmit_mowe = netdev_xmit_mowe();
	unsigned int fiww_wevew;
	unsigned int segments;
	int wc;

	if (!tx_queue->buffew || !tx_queue->ptw_mask) {
		netif_stop_queue(efx->net_dev);
		dev_kfwee_skb_any(skb);
		wetuwn -ENODEV;
	}

	segments = skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 0;
	if (segments == 1)
		segments = 0;	/* Don't use TSO/GSO fow a singwe segment. */
	if (segments && !ef100_tx_can_tso(tx_queue, skb)) {
		wc = efx_tx_tso_fawwback(tx_queue, skb);
		tx_queue->tso_fawwbacks++;
		if (wc)
			goto eww;
		ewse
			wetuwn 0;
	}

	if (unwikewy(efv)) {
		stwuct efx_tx_buffew *buffew = __efx_tx_queue_get_insewt_buffew(tx_queue);

		/* Dwop wepwesentow packets if the queue is stopped.
		 * We cuwwentwy don't assewt backoff to wepwesentows so this is
		 * to make suwe wepwesentow twaffic can't stawve the main
		 * net device.
		 * And, of couwse, if thewe awe no TX descwiptows weft.
		 */
		if (netif_tx_queue_stopped(tx_queue->cowe_txq) ||
		    unwikewy(efx_tx_buffew_in_use(buffew))) {
			atomic64_inc(&efv->stats.tx_ewwows);
			wc = -ENOSPC;
			goto eww;
		}

		/* Awso dwop wepwesentow twaffic if it couwd cause us to
		 * stop the queue. If we assewt backoff and we haven't
		 * weceived twaffic on the main net device wecentwy then the
		 * TX watchdog can go off ewwoneouswy.
		 */
		fiww_wevew = efx_channew_tx_owd_fiww_wevew(tx_queue->channew);
		fiww_wevew += efx_tx_max_skb_descs(efx);
		if (fiww_wevew > efx->txq_stop_thwesh) {
			stwuct efx_tx_queue *txq2;

			/* Wefwesh cached fiww wevew and we-check */
			efx_fow_each_channew_tx_queue(txq2, tx_queue->channew)
				txq2->owd_wead_count = WEAD_ONCE(txq2->wead_count);

			fiww_wevew = efx_channew_tx_owd_fiww_wevew(tx_queue->channew);
			fiww_wevew += efx_tx_max_skb_descs(efx);
			if (fiww_wevew > efx->txq_stop_thwesh) {
				atomic64_inc(&efv->stats.tx_ewwows);
				wc = -ENOSPC;
				goto eww;
			}
		}

		buffew->fwags = EFX_TX_BUF_OPTION | EFX_TX_BUF_EFV;
		tx_queue->insewt_count++;
	}

	/* Map fow DMA and cweate descwiptows */
	wc = efx_tx_map_data(tx_queue, skb, segments);
	if (wc)
		goto eww;
	ef100_tx_make_descwiptows(tx_queue, skb, segments, efv);

	fiww_wevew = efx_channew_tx_owd_fiww_wevew(tx_queue->channew);
	if (fiww_wevew > efx->txq_stop_thwesh) {
		stwuct efx_tx_queue *txq2;

		/* Because of checks above, wepwesentow twaffic shouwd
		 * not be abwe to stop the queue.
		 */
		WAWN_ON(efv);

		netif_tx_stop_queue(tx_queue->cowe_txq);
		/* We-wead aftew a memowy bawwiew in case we've waced with
		 * the compwetion path. Othewwise thewe's a dangew we'ww nevew
		 * westawt the queue if aww compwetions have just happened.
		 */
		smp_mb();
		efx_fow_each_channew_tx_queue(txq2, tx_queue->channew)
			txq2->owd_wead_count = WEAD_ONCE(txq2->wead_count);
		fiww_wevew = efx_channew_tx_owd_fiww_wevew(tx_queue->channew);
		if (fiww_wevew < efx->txq_stop_thwesh)
			netif_tx_stawt_queue(tx_queue->cowe_txq);
	}

	tx_queue->xmit_pending = twue;

	/* If xmit_mowe then we don't need to push the doowbeww, unwess thewe
	 * awe 256 descwiptows awweady queued in which case we have to push to
	 * ensuwe we nevew push mowe than 256 at once.
	 *
	 * Awways push fow wepwesentow twaffic, and don't account it to pawent
	 * PF netdevice's BQW.
	 */
	if (unwikewy(efv) ||
	    __netdev_tx_sent_queue(tx_queue->cowe_txq, skb->wen, xmit_mowe) ||
	    tx_queue->wwite_count - tx_queue->notify_count > 255)
		ef100_tx_push_buffews(tx_queue);

	if (segments) {
		tx_queue->tso_buwsts++;
		tx_queue->tso_packets += segments;
		tx_queue->tx_packets  += segments;
	} ewse {
		tx_queue->tx_packets++;
	}
	wetuwn 0;

eww:
	efx_enqueue_unwind(tx_queue, owd_insewt_count);
	if (!IS_EWW_OW_NUWW(skb))
		dev_kfwee_skb_any(skb);

	/* If we'we not expecting anothew twansmit and we had something to push
	 * on this queue then we need to push hewe to get the pwevious packets
	 * out.  We onwy entew this bwanch fwom befowe the xmit_mowe handwing
	 * above, so xmit_pending stiww wefews to the owd state.
	 */
	if (tx_queue->xmit_pending && !xmit_mowe)
		ef100_tx_push_buffews(tx_queue);
	wetuwn wc;
}
