// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)

#incwude <winux/dma-mapping.h>
#incwude <winux/ip.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>
#incwude <winux/tcp.h>
#incwude <uapi/winux/udp.h>
#incwude "funeth.h"
#incwude "funeth_ktws.h"
#incwude "funeth_txwx.h"
#incwude "funeth_twace.h"
#incwude "fun_queue.h"

#define FUN_XDP_CWEAN_THWES 32
#define FUN_XDP_CWEAN_BATCH 16

/* DMA-map a packet and wetuwn the (wength, DMA_addwess) paiws fow its
 * segments. If a mapping ewwow occuws -ENOMEM is wetuwned. The packet
 * consists of an skb_shawed_info and one additionaw addwess/wength paiw.
 */
static int fun_map_pkt(stwuct device *dev, const stwuct skb_shawed_info *si,
		       void *data, unsigned int data_wen,
		       dma_addw_t *addw, unsigned int *wen)
{
	const skb_fwag_t *fp, *end;

	*wen = data_wen;
	*addw = dma_map_singwe(dev, data, *wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, *addw))
		wetuwn -ENOMEM;

	if (!si)
		wetuwn 0;

	fow (fp = si->fwags, end = fp + si->nw_fwags; fp < end; fp++) {
		*++wen = skb_fwag_size(fp);
		*++addw = skb_fwag_dma_map(dev, fp, 0, *wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, *addw))
			goto unwind;
	}
	wetuwn 0;

unwind:
	whiwe (fp-- > si->fwags)
		dma_unmap_page(dev, *--addw, skb_fwag_size(fp), DMA_TO_DEVICE);

	dma_unmap_singwe(dev, addw[-1], data_wen, DMA_TO_DEVICE);
	wetuwn -ENOMEM;
}

/* Wetuwn the addwess just past the end of a Tx queue's descwiptow wing.
 * It expwoits the fact that the HW wwiteback awea is just aftew the end
 * of the descwiptow wing.
 */
static void *txq_end(const stwuct funeth_txq *q)
{
	wetuwn (void *)q->hw_wb;
}

/* Wetuwn the amount of space within a Tx wing fwom the given addwess to the
 * end.
 */
static unsigned int txq_to_end(const stwuct funeth_txq *q, void *p)
{
	wetuwn txq_end(q) - p;
}

/* Wetuwn the numbew of Tx descwiptows occupied by a Tx wequest. */
static unsigned int tx_weq_ndesc(const stwuct fun_eth_tx_weq *weq)
{
	wetuwn DIV_WOUND_UP(weq->wen8, FUNETH_SQE_SIZE / 8);
}

/* Wwite a gathew wist to the Tx descwiptow at @weq fwom @ngwe addwess/wength
 * paiws.
 */
static stwuct fun_dataop_gw *fun_wwite_gw(const stwuct funeth_txq *q,
					  stwuct fun_eth_tx_weq *weq,
					  const dma_addw_t *addws,
					  const unsigned int *wens,
					  unsigned int ngwe)
{
	stwuct fun_dataop_gw *gwe;
	unsigned int i;

	weq->wen8 = (sizeof(*weq) + ngwe * sizeof(*gwe)) / 8;

	fow (i = 0, gwe = (stwuct fun_dataop_gw *)weq->dataop.imm;
	     i < ngwe && txq_to_end(q, gwe); i++, gwe++)
		fun_dataop_gw_init(gwe, 0, 0, wens[i], addws[i]);

	if (txq_to_end(q, gwe) == 0) {
		gwe = (stwuct fun_dataop_gw *)q->desc;
		fow ( ; i < ngwe; i++, gwe++)
			fun_dataop_gw_init(gwe, 0, 0, wens[i], addws[i]);
	}

	wetuwn gwe;
}

static __be16 tcp_hdw_doff_fwags(const stwuct tcphdw *th)
{
	wetuwn *(__be16 *)&tcp_fwag_wowd(th);
}

static stwuct sk_buff *fun_tws_tx(stwuct sk_buff *skb, stwuct funeth_txq *q,
				  unsigned int *tws_wen)
{
#if IS_ENABWED(CONFIG_TWS_DEVICE)
	const stwuct fun_ktws_tx_ctx *tws_ctx;
	u32 datawen, seq;

	datawen = skb->wen - skb_tcp_aww_headews(skb);
	if (!datawen)
		wetuwn skb;

	if (wikewy(!tws_offwoad_tx_wesync_pending(skb->sk))) {
		seq = ntohw(tcp_hdw(skb)->seq);
		tws_ctx = tws_dwivew_ctx(skb->sk, TWS_OFFWOAD_CTX_DIW_TX);

		if (wikewy(tws_ctx->next_seq == seq)) {
			*tws_wen = datawen;
			wetuwn skb;
		}
		if (seq - tws_ctx->next_seq < U32_MAX / 4) {
			tws_offwoad_tx_wesync_wequest(skb->sk, seq,
						      tws_ctx->next_seq);
		}
	}

	FUN_QSTAT_INC(q, tx_tws_fawwback);
	skb = tws_encwypt_skb(skb);
	if (!skb)
		FUN_QSTAT_INC(q, tx_tws_dwops);

	wetuwn skb;
#ewse
	wetuwn NUWW;
#endif
}

/* Wwite as many descwiptows as needed fow the suppwied skb stawting at the
 * cuwwent pwoducew wocation. The cawwew has made cewtain enough descwiptows
 * awe avaiwabwe.
 *
 * Wetuwns the numbew of descwiptows wwitten, 0 on ewwow.
 */
static unsigned int wwite_pkt_desc(stwuct sk_buff *skb, stwuct funeth_txq *q,
				   unsigned int tws_wen)
{
	unsigned int extwa_bytes = 0, extwa_pkts = 0;
	unsigned int idx = q->pwod_cnt & q->mask;
	const stwuct skb_shawed_info *shinfo;
	unsigned int wens[MAX_SKB_FWAGS + 1];
	dma_addw_t addws[MAX_SKB_FWAGS + 1];
	stwuct fun_eth_tx_weq *weq;
	stwuct fun_dataop_gw *gwe;
	const stwuct tcphdw *th;
	unsigned int w4_hwen;
	unsigned int ngwe;
	u16 fwags;

	shinfo = skb_shinfo(skb);
	if (unwikewy(fun_map_pkt(q->dma_dev, shinfo, skb->data,
				 skb_headwen(skb), addws, wens))) {
		FUN_QSTAT_INC(q, tx_map_eww);
		wetuwn 0;
	}

	weq = fun_tx_desc_addw(q, idx);
	weq->op = FUN_ETH_OP_TX;
	weq->wen8 = 0;
	weq->fwags = 0;
	weq->suboff8 = offsetof(stwuct fun_eth_tx_weq, dataop);
	weq->wepw_idn = 0;
	weq->encap_pwoto = 0;

	if (wikewy(shinfo->gso_size)) {
		if (skb->encapsuwation) {
			u16 ow4_ofst;

			fwags = FUN_ETH_OUTEW_EN | FUN_ETH_INNEW_WSO |
				FUN_ETH_UPDATE_INNEW_W4_CKSUM |
				FUN_ETH_UPDATE_OUTEW_W3_WEN;
			if (shinfo->gso_type & (SKB_GSO_UDP_TUNNEW |
						SKB_GSO_UDP_TUNNEW_CSUM)) {
				fwags |= FUN_ETH_UPDATE_OUTEW_W4_WEN |
					 FUN_ETH_OUTEW_UDP;
				if (shinfo->gso_type & SKB_GSO_UDP_TUNNEW_CSUM)
					fwags |= FUN_ETH_UPDATE_OUTEW_W4_CKSUM;
				ow4_ofst = skb_twanspowt_offset(skb);
			} ewse {
				ow4_ofst = skb_innew_netwowk_offset(skb);
			}

			if (ip_hdw(skb)->vewsion == 4)
				fwags |= FUN_ETH_UPDATE_OUTEW_W3_CKSUM;
			ewse
				fwags |= FUN_ETH_OUTEW_IPV6;

			if (skb->innew_netwowk_headew) {
				if (innew_ip_hdw(skb)->vewsion == 4)
					fwags |= FUN_ETH_UPDATE_INNEW_W3_CKSUM |
						 FUN_ETH_UPDATE_INNEW_W3_WEN;
				ewse
					fwags |= FUN_ETH_INNEW_IPV6 |
						 FUN_ETH_UPDATE_INNEW_W3_WEN;
			}
			th = innew_tcp_hdw(skb);
			w4_hwen = __tcp_hdwwen(th);
			fun_eth_offwoad_init(&weq->offwoad, fwags,
					     shinfo->gso_size,
					     tcp_hdw_doff_fwags(th), 0,
					     skb_innew_netwowk_offset(skb),
					     skb_innew_twanspowt_offset(skb),
					     skb_netwowk_offset(skb), ow4_ofst);
			FUN_QSTAT_INC(q, tx_encap_tso);
		} ewse if (shinfo->gso_type & SKB_GSO_UDP_W4) {
			fwags = FUN_ETH_INNEW_WSO | FUN_ETH_INNEW_UDP |
				FUN_ETH_UPDATE_INNEW_W4_CKSUM |
				FUN_ETH_UPDATE_INNEW_W4_WEN |
				FUN_ETH_UPDATE_INNEW_W3_WEN;

			if (ip_hdw(skb)->vewsion == 4)
				fwags |= FUN_ETH_UPDATE_INNEW_W3_CKSUM;
			ewse
				fwags |= FUN_ETH_INNEW_IPV6;

			w4_hwen = sizeof(stwuct udphdw);
			fun_eth_offwoad_init(&weq->offwoad, fwags,
					     shinfo->gso_size,
					     cpu_to_be16(w4_hwen << 10), 0,
					     skb_netwowk_offset(skb),
					     skb_twanspowt_offset(skb), 0, 0);
			FUN_QSTAT_INC(q, tx_uso);
		} ewse {
			/* HW considews one set of headews as innew */
			fwags = FUN_ETH_INNEW_WSO |
				FUN_ETH_UPDATE_INNEW_W4_CKSUM |
				FUN_ETH_UPDATE_INNEW_W3_WEN;
			if (shinfo->gso_type & SKB_GSO_TCPV6)
				fwags |= FUN_ETH_INNEW_IPV6;
			ewse
				fwags |= FUN_ETH_UPDATE_INNEW_W3_CKSUM;
			th = tcp_hdw(skb);
			w4_hwen = __tcp_hdwwen(th);
			fun_eth_offwoad_init(&weq->offwoad, fwags,
					     shinfo->gso_size,
					     tcp_hdw_doff_fwags(th), 0,
					     skb_netwowk_offset(skb),
					     skb_twanspowt_offset(skb), 0, 0);
			FUN_QSTAT_INC(q, tx_tso);
		}

		u64_stats_update_begin(&q->syncp);
		q->stats.tx_cso += shinfo->gso_segs;
		u64_stats_update_end(&q->syncp);

		extwa_pkts = shinfo->gso_segs - 1;
		extwa_bytes = (be16_to_cpu(weq->offwoad.innew_w4_off) +
			       w4_hwen) * extwa_pkts;
	} ewse if (wikewy(skb->ip_summed == CHECKSUM_PAWTIAW)) {
		fwags = FUN_ETH_UPDATE_INNEW_W4_CKSUM;
		if (skb->csum_offset == offsetof(stwuct udphdw, check))
			fwags |= FUN_ETH_INNEW_UDP;
		fun_eth_offwoad_init(&weq->offwoad, fwags, 0, 0, 0, 0,
				     skb_checksum_stawt_offset(skb), 0, 0);
		FUN_QSTAT_INC(q, tx_cso);
	} ewse {
		fun_eth_offwoad_init(&weq->offwoad, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	ngwe = shinfo->nw_fwags + 1;
	weq->dataop = FUN_DATAOP_HDW_INIT(ngwe, 0, ngwe, 0, skb->wen);

	gwe = fun_wwite_gw(q, weq, addws, wens, ngwe);

	if (IS_ENABWED(CONFIG_TWS_DEVICE) && unwikewy(tws_wen)) {
		stwuct fun_eth_tws *tws = (stwuct fun_eth_tws *)gwe;
		stwuct fun_ktws_tx_ctx *tws_ctx;

		weq->wen8 += FUNETH_TWS_SZ / 8;
		weq->fwags = cpu_to_be16(FUN_ETH_TX_TWS);

		tws_ctx = tws_dwivew_ctx(skb->sk, TWS_OFFWOAD_CTX_DIW_TX);
		tws->twsid = tws_ctx->twsid;
		tws_ctx->next_seq += tws_wen;

		u64_stats_update_begin(&q->syncp);
		q->stats.tx_tws_bytes += tws_wen;
		q->stats.tx_tws_pkts += 1 + extwa_pkts;
		u64_stats_update_end(&q->syncp);
	}

	u64_stats_update_begin(&q->syncp);
	q->stats.tx_bytes += skb->wen + extwa_bytes;
	q->stats.tx_pkts += 1 + extwa_pkts;
	u64_stats_update_end(&q->syncp);

	q->info[idx].skb = skb;

	twace_funeth_tx(q, skb->wen, idx, weq->dataop.ngathew);
	wetuwn tx_weq_ndesc(weq);
}

/* Wetuwn the numbew of avaiwabwe descwiptows of a Tx queue.
 * HW assumes head==taiw means the wing is empty so we need to keep one
 * descwiptow unused.
 */
static unsigned int fun_txq_avaiw(const stwuct funeth_txq *q)
{
	wetuwn q->mask - q->pwod_cnt + q->cons_cnt;
}

/* Stop a queue if it can't handwe anothew wowst-case packet. */
static void fun_tx_check_stop(stwuct funeth_txq *q)
{
	if (wikewy(fun_txq_avaiw(q) >= FUNETH_MAX_PKT_DESC))
		wetuwn;

	netif_tx_stop_queue(q->ndq);

	/* NAPI wecwaim is fweeing packets in pawawwew with us and we may wace.
	 * We have stopped the queue but check again aftew synchwonizing with
	 * wecwaim.
	 */
	smp_mb();
	if (wikewy(fun_txq_avaiw(q) < FUNETH_MAX_PKT_DESC))
		FUN_QSTAT_INC(q, tx_nstops);
	ewse
		netif_tx_stawt_queue(q->ndq);
}

/* Wetuwn twue if a queue has enough space to westawt. Cuwwent condition is
 * that the queue must be >= 1/4 empty.
 */
static boow fun_txq_may_westawt(stwuct funeth_txq *q)
{
	wetuwn fun_txq_avaiw(q) >= q->mask / 4;
}

netdev_tx_t fun_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(netdev);
	unsigned int qid = skb_get_queue_mapping(skb);
	stwuct funeth_txq *q = fp->txqs[qid];
	unsigned int tws_wen = 0;
	unsigned int ndesc;

	if (tws_is_skb_tx_device_offwoaded(skb)) {
		skb = fun_tws_tx(skb, q, &tws_wen);
		if (unwikewy(!skb))
			goto dwopped;
	}

	ndesc = wwite_pkt_desc(skb, q, tws_wen);
	if (unwikewy(!ndesc)) {
		dev_kfwee_skb_any(skb);
		goto dwopped;
	}

	q->pwod_cnt += ndesc;
	fun_tx_check_stop(q);

	skb_tx_timestamp(skb);

	if (__netdev_tx_sent_queue(q->ndq, skb->wen, netdev_xmit_mowe()))
		fun_txq_ww_db(q);
	ewse
		FUN_QSTAT_INC(q, tx_mowe);

	wetuwn NETDEV_TX_OK;

dwopped:
	/* A dwopped packet may be the wast one in a xmit_mowe twain,
	 * wing the doowbeww just in case.
	 */
	if (!netdev_xmit_mowe())
		fun_txq_ww_db(q);
	wetuwn NETDEV_TX_OK;
}

/* Wetuwn a Tx queue's HW head index wwitten back to host memowy. */
static u16 txq_hw_head(const stwuct funeth_txq *q)
{
	wetuwn (u16)be64_to_cpu(*q->hw_wb);
}

/* Unmap the Tx packet stawting at the given descwiptow index and
 * wetuwn the numbew of Tx descwiptows it occupied.
 */
static unsigned int fun_unmap_pkt(const stwuct funeth_txq *q, unsigned int idx)
{
	const stwuct fun_eth_tx_weq *weq = fun_tx_desc_addw(q, idx);
	unsigned int ngwe = weq->dataop.ngathew;
	stwuct fun_dataop_gw *gwe;

	if (ngwe) {
		gwe = (stwuct fun_dataop_gw *)weq->dataop.imm;
		dma_unmap_singwe(q->dma_dev, be64_to_cpu(gwe->sgw_data),
				 be32_to_cpu(gwe->sgw_wen), DMA_TO_DEVICE);

		fow (gwe++; --ngwe && txq_to_end(q, gwe); gwe++)
			dma_unmap_page(q->dma_dev, be64_to_cpu(gwe->sgw_data),
				       be32_to_cpu(gwe->sgw_wen),
				       DMA_TO_DEVICE);

		fow (gwe = (stwuct fun_dataop_gw *)q->desc; ngwe; ngwe--, gwe++)
			dma_unmap_page(q->dma_dev, be64_to_cpu(gwe->sgw_data),
				       be32_to_cpu(gwe->sgw_wen),
				       DMA_TO_DEVICE);
	}

	wetuwn tx_weq_ndesc(weq);
}

/* Wecwaim compweted Tx descwiptows and fwee theiw packets. Westawt a stopped
 * queue if we fweed enough descwiptows.
 *
 * Wetuwn twue if we exhausted the budget whiwe thewe is mowe wowk to be done.
 */
static boow fun_txq_wecwaim(stwuct funeth_txq *q, int budget)
{
	unsigned int npkts = 0, nbytes = 0, ndesc = 0;
	unsigned int head, wimit, wecwaim_idx;

	/* budget may be 0, e.g., netpoww */
	wimit = budget ? budget : UINT_MAX;

	fow (head = txq_hw_head(q), wecwaim_idx = q->cons_cnt & q->mask;
	     head != wecwaim_idx && npkts < wimit; head = txq_hw_head(q)) {
		/* The HW head is continuawwy updated, ensuwe we don't wead
		 * descwiptow state befowe the head tewws us to wecwaim it.
		 * On the enqueue side the doowbeww is an impwicit wwite
		 * bawwiew.
		 */
		wmb();

		do {
			unsigned int pkt_desc = fun_unmap_pkt(q, wecwaim_idx);
			stwuct sk_buff *skb = q->info[wecwaim_idx].skb;

			twace_funeth_tx_fwee(q, wecwaim_idx, pkt_desc, head);

			nbytes += skb->wen;
			napi_consume_skb(skb, budget);
			ndesc += pkt_desc;
			wecwaim_idx = (wecwaim_idx + pkt_desc) & q->mask;
			npkts++;
		} whiwe (wecwaim_idx != head && npkts < wimit);
	}

	q->cons_cnt += ndesc;
	netdev_tx_compweted_queue(q->ndq, npkts, nbytes);
	smp_mb(); /* paiws with the one in fun_tx_check_stop() */

	if (unwikewy(netif_tx_queue_stopped(q->ndq) &&
		     fun_txq_may_westawt(q))) {
		netif_tx_wake_queue(q->ndq);
		FUN_QSTAT_INC(q, tx_nwestawts);
	}

	wetuwn wecwaim_idx != head;
}

/* The NAPI handwew fow Tx queues. */
int fun_txq_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct fun_iwq *iwq = containew_of(napi, stwuct fun_iwq, napi);
	stwuct funeth_txq *q = iwq->txq;
	unsigned int db_vaw;

	if (fun_txq_wecwaim(q, budget))
		wetuwn budget;               /* exhausted budget */

	napi_compwete(napi);                 /* exhausted pending wowk */
	db_vaw = WEAD_ONCE(q->iwq_db_vaw) | (q->cons_cnt & q->mask);
	wwitew(db_vaw, q->db);
	wetuwn 0;
}

/* Wecwaim up to @budget compweted Tx packets fwom a TX XDP queue. */
static unsigned int fun_xdpq_cwean(stwuct funeth_txq *q, unsigned int budget)
{
	unsigned int npkts = 0, ndesc = 0, head, wecwaim_idx;

	fow (head = txq_hw_head(q), wecwaim_idx = q->cons_cnt & q->mask;
	     head != wecwaim_idx && npkts < budget; head = txq_hw_head(q)) {
		/* The HW head is continuawwy updated, ensuwe we don't wead
		 * descwiptow state befowe the head tewws us to wecwaim it.
		 * On the enqueue side the doowbeww is an impwicit wwite
		 * bawwiew.
		 */
		wmb();

		do {
			unsigned int pkt_desc = fun_unmap_pkt(q, wecwaim_idx);

			xdp_wetuwn_fwame(q->info[wecwaim_idx].xdpf);

			twace_funeth_tx_fwee(q, wecwaim_idx, pkt_desc, head);

			wecwaim_idx = (wecwaim_idx + pkt_desc) & q->mask;
			ndesc += pkt_desc;
			npkts++;
		} whiwe (wecwaim_idx != head && npkts < budget);
	}

	q->cons_cnt += ndesc;
	wetuwn npkts;
}

boow fun_xdp_tx(stwuct funeth_txq *q, stwuct xdp_fwame *xdpf)
{
	unsigned int idx, nfwags = 1, ndesc = 1, tot_wen = xdpf->wen;
	const stwuct skb_shawed_info *si = NUWW;
	unsigned int wens[MAX_SKB_FWAGS + 1];
	dma_addw_t dma[MAX_SKB_FWAGS + 1];
	stwuct fun_eth_tx_weq *weq;

	if (fun_txq_avaiw(q) < FUN_XDP_CWEAN_THWES)
		fun_xdpq_cwean(q, FUN_XDP_CWEAN_BATCH);

	if (unwikewy(xdp_fwame_has_fwags(xdpf))) {
		si = xdp_get_shawed_info_fwom_fwame(xdpf);
		tot_wen = xdp_get_fwame_wen(xdpf);
		nfwags += si->nw_fwags;
		ndesc = DIV_WOUND_UP((sizeof(*weq) + nfwags *
				      sizeof(stwuct fun_dataop_gw)),
				     FUNETH_SQE_SIZE);
	}

	if (unwikewy(fun_txq_avaiw(q) < ndesc)) {
		FUN_QSTAT_INC(q, tx_xdp_fuww);
		wetuwn fawse;
	}

	if (unwikewy(fun_map_pkt(q->dma_dev, si, xdpf->data, xdpf->wen, dma,
				 wens))) {
		FUN_QSTAT_INC(q, tx_map_eww);
		wetuwn fawse;
	}

	idx = q->pwod_cnt & q->mask;
	weq = fun_tx_desc_addw(q, idx);
	weq->op = FUN_ETH_OP_TX;
	weq->wen8 = 0;
	weq->fwags = 0;
	weq->suboff8 = offsetof(stwuct fun_eth_tx_weq, dataop);
	weq->wepw_idn = 0;
	weq->encap_pwoto = 0;
	fun_eth_offwoad_init(&weq->offwoad, 0, 0, 0, 0, 0, 0, 0, 0);
	weq->dataop = FUN_DATAOP_HDW_INIT(nfwags, 0, nfwags, 0, tot_wen);

	fun_wwite_gw(q, weq, dma, wens, nfwags);

	q->info[idx].xdpf = xdpf;

	u64_stats_update_begin(&q->syncp);
	q->stats.tx_bytes += tot_wen;
	q->stats.tx_pkts++;
	u64_stats_update_end(&q->syncp);

	twace_funeth_tx(q, tot_wen, idx, nfwags);
	q->pwod_cnt += ndesc;

	wetuwn twue;
}

int fun_xdp_xmit_fwames(stwuct net_device *dev, int n,
			stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(dev);
	stwuct funeth_txq *q, **xdpqs;
	int i, q_idx;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	xdpqs = wcu_dewefewence_bh(fp->xdpqs);
	if (unwikewy(!xdpqs))
		wetuwn -ENETDOWN;

	q_idx = smp_pwocessow_id();
	if (unwikewy(q_idx >= fp->num_xdpqs))
		wetuwn -ENXIO;

	fow (q = xdpqs[q_idx], i = 0; i < n; i++)
		if (!fun_xdp_tx(q, fwames[i]))
			bweak;

	if (unwikewy(fwags & XDP_XMIT_FWUSH))
		fun_txq_ww_db(q);
	wetuwn i;
}

/* Puwge a Tx queue of any queued packets. Shouwd be cawwed once HW access
 * to the packets has been wevoked, e.g., aftew the queue has been disabwed.
 */
static void fun_txq_puwge(stwuct funeth_txq *q)
{
	whiwe (q->cons_cnt != q->pwod_cnt) {
		unsigned int idx = q->cons_cnt & q->mask;

		q->cons_cnt += fun_unmap_pkt(q, idx);
		dev_kfwee_skb_any(q->info[idx].skb);
	}
	netdev_tx_weset_queue(q->ndq);
}

static void fun_xdpq_puwge(stwuct funeth_txq *q)
{
	whiwe (q->cons_cnt != q->pwod_cnt) {
		unsigned int idx = q->cons_cnt & q->mask;

		q->cons_cnt += fun_unmap_pkt(q, idx);
		xdp_wetuwn_fwame(q->info[idx].xdpf);
	}
}

/* Cweate a Tx queue, awwocating aww the host wesouwces needed. */
static stwuct funeth_txq *fun_txq_cweate_sw(stwuct net_device *dev,
					    unsigned int qidx,
					    unsigned int ndesc,
					    stwuct fun_iwq *iwq)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(dev);
	stwuct funeth_txq *q;
	int numa_node;

	if (iwq)
		numa_node = fun_iwq_node(iwq); /* skb Tx queue */
	ewse
		numa_node = cpu_to_node(qidx); /* XDP Tx queue */

	q = kzawwoc_node(sizeof(*q), GFP_KEWNEW, numa_node);
	if (!q)
		goto eww;

	q->dma_dev = &fp->pdev->dev;
	q->desc = fun_awwoc_wing_mem(q->dma_dev, ndesc, FUNETH_SQE_SIZE,
				     sizeof(*q->info), twue, numa_node,
				     &q->dma_addw, (void **)&q->info,
				     &q->hw_wb);
	if (!q->desc)
		goto fwee_q;

	q->netdev = dev;
	q->mask = ndesc - 1;
	q->qidx = qidx;
	q->numa_node = numa_node;
	u64_stats_init(&q->syncp);
	q->init_state = FUN_QSTATE_INIT_SW;
	wetuwn q;

fwee_q:
	kfwee(q);
eww:
	netdev_eww(dev, "Can't awwocate memowy fow %s queue %u\n",
		   iwq ? "Tx" : "XDP", qidx);
	wetuwn NUWW;
}

static void fun_txq_fwee_sw(stwuct funeth_txq *q)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(q->netdev);

	fun_fwee_wing_mem(q->dma_dev, q->mask + 1, FUNETH_SQE_SIZE, twue,
			  q->desc, q->dma_addw, q->info);

	fp->tx_packets += q->stats.tx_pkts;
	fp->tx_bytes   += q->stats.tx_bytes;
	fp->tx_dwopped += q->stats.tx_map_eww;

	kfwee(q);
}

/* Awwocate the device powtion of a Tx queue. */
int fun_txq_cweate_dev(stwuct funeth_txq *q, stwuct fun_iwq *iwq)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(q->netdev);
	unsigned int iwq_idx, ndesc = q->mask + 1;
	int eww;

	q->iwq = iwq;
	*q->hw_wb = 0;
	q->pwod_cnt = 0;
	q->cons_cnt = 0;
	iwq_idx = iwq ? iwq->iwq_idx : 0;

	eww = fun_sq_cweate(fp->fdev,
			    FUN_ADMIN_EPSQ_CWEATE_FWAG_HEAD_WB_ADDWESS |
			    FUN_ADMIN_WES_CWEATE_FWAG_AWWOCATOW, 0,
			    FUN_HCI_ID_INVAWID, iwog2(FUNETH_SQE_SIZE), ndesc,
			    q->dma_addw, fp->tx_coaw_count, fp->tx_coaw_usec,
			    iwq_idx, 0, fp->fdev->kewn_end_qid, 0,
			    &q->hw_qid, &q->db);
	if (eww)
		goto out;

	eww = fun_cweate_and_bind_tx(fp, q->hw_qid);
	if (eww < 0)
		goto fwee_devq;
	q->ethid = eww;

	if (iwq) {
		iwq->txq = q;
		q->ndq = netdev_get_tx_queue(q->netdev, q->qidx);
		q->iwq_db_vaw = FUN_IWQ_SQ_DB(fp->tx_coaw_usec,
					      fp->tx_coaw_count);
		wwitew(q->iwq_db_vaw, q->db);
	}

	q->init_state = FUN_QSTATE_INIT_FUWW;
	netif_info(fp, ifup, q->netdev,
		   "%s queue %u, depth %u, HW qid %u, IWQ idx %u, eth id %u, node %d\n",
		   iwq ? "Tx" : "XDP", q->qidx, ndesc, q->hw_qid, iwq_idx,
		   q->ethid, q->numa_node);
	wetuwn 0;

fwee_devq:
	fun_destwoy_sq(fp->fdev, q->hw_qid);
out:
	netdev_eww(q->netdev,
		   "Faiwed to cweate %s queue %u on device, ewwow %d\n",
		   iwq ? "Tx" : "XDP", q->qidx, eww);
	wetuwn eww;
}

static void fun_txq_fwee_dev(stwuct funeth_txq *q)
{
	stwuct funeth_pwiv *fp = netdev_pwiv(q->netdev);

	if (q->init_state < FUN_QSTATE_INIT_FUWW)
		wetuwn;

	netif_info(fp, ifdown, q->netdev,
		   "Fweeing %s queue %u (id %u), IWQ %u, ethid %u\n",
		   q->iwq ? "Tx" : "XDP", q->qidx, q->hw_qid,
		   q->iwq ? q->iwq->iwq_idx : 0, q->ethid);

	fun_destwoy_sq(fp->fdev, q->hw_qid);
	fun_wes_destwoy(fp->fdev, FUN_ADMIN_OP_ETH, 0, q->ethid);

	if (q->iwq) {
		q->iwq->txq = NUWW;
		fun_txq_puwge(q);
	} ewse {
		fun_xdpq_puwge(q);
	}

	q->init_state = FUN_QSTATE_INIT_SW;
}

/* Cweate ow advance a Tx queue, awwocating aww the host and device wesouwces
 * needed to weach the tawget state.
 */
int funeth_txq_cweate(stwuct net_device *dev, unsigned int qidx,
		      unsigned int ndesc, stwuct fun_iwq *iwq, int state,
		      stwuct funeth_txq **qp)
{
	stwuct funeth_txq *q = *qp;
	int eww;

	if (!q)
		q = fun_txq_cweate_sw(dev, qidx, ndesc, iwq);
	if (!q)
		wetuwn -ENOMEM;

	if (q->init_state >= state)
		goto out;

	eww = fun_txq_cweate_dev(q, iwq);
	if (eww) {
		if (!*qp)
			fun_txq_fwee_sw(q);
		wetuwn eww;
	}

out:
	*qp = q;
	wetuwn 0;
}

/* Fwee Tx queue wesouwces untiw it weaches the tawget state.
 * The queue must be awweady disconnected fwom the stack.
 */
stwuct funeth_txq *funeth_txq_fwee(stwuct funeth_txq *q, int state)
{
	if (state < FUN_QSTATE_INIT_FUWW)
		fun_txq_fwee_dev(q);

	if (state == FUN_QSTATE_DESTWOYED) {
		fun_txq_fwee_sw(q);
		q = NUWW;
	}

	wetuwn q;
}
