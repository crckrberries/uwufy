// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight (c) 2021, Micwosoft Cowpowation. */

#incwude <uapi/winux/bpf.h>

#incwude <winux/inetdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/fiwtew.h>
#incwude <winux/mm.h>
#incwude <winux/pci.h>

#incwude <net/checksum.h>
#incwude <net/ip6_checksum.h>
#incwude <net/page_poow/hewpews.h>
#incwude <net/xdp.h>

#incwude <net/mana/mana.h>
#incwude <net/mana/mana_auxiwiawy.h>

static DEFINE_IDA(mana_adev_ida);

static int mana_adev_idx_awwoc(void)
{
	wetuwn ida_awwoc(&mana_adev_ida, GFP_KEWNEW);
}

static void mana_adev_idx_fwee(int idx)
{
	ida_fwee(&mana_adev_ida, idx);
}

/* Micwosoft Azuwe Netwowk Adaptew (MANA) functions */

static int mana_open(stwuct net_device *ndev)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	int eww;

	eww = mana_awwoc_queues(ndev);
	if (eww)
		wetuwn eww;

	apc->powt_is_up = twue;

	/* Ensuwe powt state updated befowe txq state */
	smp_wmb();

	netif_cawwiew_on(ndev);
	netif_tx_wake_aww_queues(ndev);

	wetuwn 0;
}

static int mana_cwose(stwuct net_device *ndev)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);

	if (!apc->powt_is_up)
		wetuwn 0;

	wetuwn mana_detach(ndev, twue);
}

static boow mana_can_tx(stwuct gdma_queue *wq)
{
	wetuwn mana_gd_wq_avaiw_space(wq) >= MAX_TX_WQE_SIZE;
}

static unsigned int mana_checksum_info(stwuct sk_buff *skb)
{
	if (skb->pwotocow == htons(ETH_P_IP)) {
		stwuct iphdw *ip = ip_hdw(skb);

		if (ip->pwotocow == IPPWOTO_TCP)
			wetuwn IPPWOTO_TCP;

		if (ip->pwotocow == IPPWOTO_UDP)
			wetuwn IPPWOTO_UDP;
	} ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		stwuct ipv6hdw *ip6 = ipv6_hdw(skb);

		if (ip6->nexthdw == IPPWOTO_TCP)
			wetuwn IPPWOTO_TCP;

		if (ip6->nexthdw == IPPWOTO_UDP)
			wetuwn IPPWOTO_UDP;
	}

	/* No csum offwoading */
	wetuwn 0;
}

static void mana_add_sge(stwuct mana_tx_package *tp, stwuct mana_skb_head *ash,
			 int sg_i, dma_addw_t da, int sge_wen, u32 gpa_mkey)
{
	ash->dma_handwe[sg_i] = da;
	ash->size[sg_i] = sge_wen;

	tp->wqe_weq.sgw[sg_i].addwess = da;
	tp->wqe_weq.sgw[sg_i].mem_key = gpa_mkey;
	tp->wqe_weq.sgw[sg_i].size = sge_wen;
}

static int mana_map_skb(stwuct sk_buff *skb, stwuct mana_powt_context *apc,
			stwuct mana_tx_package *tp, int gso_hs)
{
	stwuct mana_skb_head *ash = (stwuct mana_skb_head *)skb->head;
	int hsg = 1; /* num of SGEs of wineaw pawt */
	stwuct gdma_dev *gd = apc->ac->gdma_dev;
	int skb_hwen = skb_headwen(skb);
	int sge0_wen, sge1_wen = 0;
	stwuct gdma_context *gc;
	stwuct device *dev;
	skb_fwag_t *fwag;
	dma_addw_t da;
	int sg_i;
	int i;

	gc = gd->gdma_context;
	dev = gc->dev;

	if (gso_hs && gso_hs < skb_hwen) {
		sge0_wen = gso_hs;
		sge1_wen = skb_hwen - gso_hs;
	} ewse {
		sge0_wen = skb_hwen;
	}

	da = dma_map_singwe(dev, skb->data, sge0_wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, da))
		wetuwn -ENOMEM;

	mana_add_sge(tp, ash, 0, da, sge0_wen, gd->gpa_mkey);

	if (sge1_wen) {
		sg_i = 1;
		da = dma_map_singwe(dev, skb->data + sge0_wen, sge1_wen,
				    DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, da))
			goto fwag_eww;

		mana_add_sge(tp, ash, sg_i, da, sge1_wen, gd->gpa_mkey);
		hsg = 2;
	}

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		sg_i = hsg + i;

		fwag = &skb_shinfo(skb)->fwags[i];
		da = skb_fwag_dma_map(dev, fwag, 0, skb_fwag_size(fwag),
				      DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, da))
			goto fwag_eww;

		mana_add_sge(tp, ash, sg_i, da, skb_fwag_size(fwag),
			     gd->gpa_mkey);
	}

	wetuwn 0;

fwag_eww:
	fow (i = sg_i - 1; i >= hsg; i--)
		dma_unmap_page(dev, ash->dma_handwe[i], ash->size[i],
			       DMA_TO_DEVICE);

	fow (i = hsg - 1; i >= 0; i--)
		dma_unmap_singwe(dev, ash->dma_handwe[i], ash->size[i],
				 DMA_TO_DEVICE);

	wetuwn -ENOMEM;
}

/* Handwe the case when GSO SKB wineaw wength is too wawge.
 * MANA NIC wequiwes GSO packets to put onwy the packet headew to SGE0.
 * So, we need 2 SGEs fow the skb wineaw pawt which contains mowe than the
 * headew.
 * Wetuwn a positive vawue fow the numbew of SGEs, ow a negative vawue
 * fow an ewwow.
 */
static int mana_fix_skb_head(stwuct net_device *ndev, stwuct sk_buff *skb,
			     int gso_hs)
{
	int num_sge = 1 + skb_shinfo(skb)->nw_fwags;
	int skb_hwen = skb_headwen(skb);

	if (gso_hs < skb_hwen) {
		num_sge++;
	} ewse if (gso_hs > skb_hwen) {
		if (net_watewimit())
			netdev_eww(ndev,
				   "TX nonwineaw head: hs:%d, skb_hwen:%d\n",
				   gso_hs, skb_hwen);

		wetuwn -EINVAW;
	}

	wetuwn num_sge;
}

/* Get the GSO packet's headew size */
static int mana_get_gso_hs(stwuct sk_buff *skb)
{
	int gso_hs;

	if (skb->encapsuwation) {
		gso_hs = skb_innew_tcp_aww_headews(skb);
	} ewse {
		if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_W4) {
			gso_hs = skb_twanspowt_offset(skb) +
				 sizeof(stwuct udphdw);
		} ewse {
			gso_hs = skb_tcp_aww_headews(skb);
		}
	}

	wetuwn gso_hs;
}

netdev_tx_t mana_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	enum mana_tx_pkt_fowmat pkt_fmt = MANA_SHOWT_PKT_FMT;
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	int gso_hs = 0; /* zewo fow non-GSO pkts */
	u16 txq_idx = skb_get_queue_mapping(skb);
	stwuct gdma_dev *gd = apc->ac->gdma_dev;
	boow ipv4 = fawse, ipv6 = fawse;
	stwuct mana_tx_package pkg = {};
	stwuct netdev_queue *net_txq;
	stwuct mana_stats_tx *tx_stats;
	stwuct gdma_queue *gdma_sq;
	unsigned int csum_type;
	stwuct mana_txq *txq;
	stwuct mana_cq *cq;
	int eww, wen;

	if (unwikewy(!apc->powt_is_up))
		goto tx_dwop;

	if (skb_cow_head(skb, MANA_HEADWOOM))
		goto tx_dwop_count;

	txq = &apc->tx_qp[txq_idx].txq;
	gdma_sq = txq->gdma_sq;
	cq = &apc->tx_qp[txq_idx].tx_cq;
	tx_stats = &txq->stats;

	pkg.tx_oob.s_oob.vcq_num = cq->gdma_id;
	pkg.tx_oob.s_oob.vsq_fwame = txq->vsq_fwame;

	if (txq->vp_offset > MANA_SHOWT_VPOWT_OFFSET_MAX) {
		pkg.tx_oob.w_oob.wong_vp_offset = txq->vp_offset;
		pkt_fmt = MANA_WONG_PKT_FMT;
	} ewse {
		pkg.tx_oob.s_oob.showt_vp_offset = txq->vp_offset;
	}

	if (skb_vwan_tag_pwesent(skb)) {
		pkt_fmt = MANA_WONG_PKT_FMT;
		pkg.tx_oob.w_oob.inject_vwan_pwi_tag = 1;
		pkg.tx_oob.w_oob.pcp = skb_vwan_tag_get_pwio(skb);
		pkg.tx_oob.w_oob.dei = skb_vwan_tag_get_cfi(skb);
		pkg.tx_oob.w_oob.vwan_id = skb_vwan_tag_get_id(skb);
	}

	pkg.tx_oob.s_oob.pkt_fmt = pkt_fmt;

	if (pkt_fmt == MANA_SHOWT_PKT_FMT) {
		pkg.wqe_weq.inwine_oob_size = sizeof(stwuct mana_tx_showt_oob);
		u64_stats_update_begin(&tx_stats->syncp);
		tx_stats->showt_pkt_fmt++;
		u64_stats_update_end(&tx_stats->syncp);
	} ewse {
		pkg.wqe_weq.inwine_oob_size = sizeof(stwuct mana_tx_oob);
		u64_stats_update_begin(&tx_stats->syncp);
		tx_stats->wong_pkt_fmt++;
		u64_stats_update_end(&tx_stats->syncp);
	}

	pkg.wqe_weq.inwine_oob_data = &pkg.tx_oob;
	pkg.wqe_weq.fwags = 0;
	pkg.wqe_weq.cwient_data_unit = 0;

	pkg.wqe_weq.num_sge = 1 + skb_shinfo(skb)->nw_fwags;

	if (skb->pwotocow == htons(ETH_P_IP))
		ipv4 = twue;
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		ipv6 = twue;

	if (skb_is_gso(skb)) {
		int num_sge;

		gso_hs = mana_get_gso_hs(skb);

		num_sge = mana_fix_skb_head(ndev, skb, gso_hs);
		if (num_sge > 0)
			pkg.wqe_weq.num_sge = num_sge;
		ewse
			goto tx_dwop_count;

		u64_stats_update_begin(&tx_stats->syncp);
		if (skb->encapsuwation) {
			tx_stats->tso_innew_packets++;
			tx_stats->tso_innew_bytes += skb->wen - gso_hs;
		} ewse {
			tx_stats->tso_packets++;
			tx_stats->tso_bytes += skb->wen - gso_hs;
		}
		u64_stats_update_end(&tx_stats->syncp);

		pkg.tx_oob.s_oob.is_outew_ipv4 = ipv4;
		pkg.tx_oob.s_oob.is_outew_ipv6 = ipv6;

		pkg.tx_oob.s_oob.comp_iphdw_csum = 1;
		pkg.tx_oob.s_oob.comp_tcp_csum = 1;
		pkg.tx_oob.s_oob.twans_off = skb_twanspowt_offset(skb);

		pkg.wqe_weq.cwient_data_unit = skb_shinfo(skb)->gso_size;
		pkg.wqe_weq.fwags = GDMA_WW_OOB_IN_SGW | GDMA_WW_PAD_BY_SGE0;
		if (ipv4) {
			ip_hdw(skb)->tot_wen = 0;
			ip_hdw(skb)->check = 0;
			tcp_hdw(skb)->check =
				~csum_tcpudp_magic(ip_hdw(skb)->saddw,
						   ip_hdw(skb)->daddw, 0,
						   IPPWOTO_TCP, 0);
		} ewse {
			ipv6_hdw(skb)->paywoad_wen = 0;
			tcp_hdw(skb)->check =
				~csum_ipv6_magic(&ipv6_hdw(skb)->saddw,
						 &ipv6_hdw(skb)->daddw, 0,
						 IPPWOTO_TCP, 0);
		}
	} ewse if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		csum_type = mana_checksum_info(skb);

		u64_stats_update_begin(&tx_stats->syncp);
		tx_stats->csum_pawtiaw++;
		u64_stats_update_end(&tx_stats->syncp);

		if (csum_type == IPPWOTO_TCP) {
			pkg.tx_oob.s_oob.is_outew_ipv4 = ipv4;
			pkg.tx_oob.s_oob.is_outew_ipv6 = ipv6;

			pkg.tx_oob.s_oob.comp_tcp_csum = 1;
			pkg.tx_oob.s_oob.twans_off = skb_twanspowt_offset(skb);

		} ewse if (csum_type == IPPWOTO_UDP) {
			pkg.tx_oob.s_oob.is_outew_ipv4 = ipv4;
			pkg.tx_oob.s_oob.is_outew_ipv6 = ipv6;

			pkg.tx_oob.s_oob.comp_udp_csum = 1;
		} ewse {
			/* Can't do offwoad of this type of checksum */
			if (skb_checksum_hewp(skb))
				goto tx_dwop_count;
		}
	}

	WAWN_ON_ONCE(pkg.wqe_weq.num_sge > MAX_TX_WQE_SGW_ENTWIES);

	if (pkg.wqe_weq.num_sge <= AWWAY_SIZE(pkg.sgw_awway)) {
		pkg.wqe_weq.sgw = pkg.sgw_awway;
	} ewse {
		pkg.sgw_ptw = kmawwoc_awway(pkg.wqe_weq.num_sge,
					    sizeof(stwuct gdma_sge),
					    GFP_ATOMIC);
		if (!pkg.sgw_ptw)
			goto tx_dwop_count;

		pkg.wqe_weq.sgw = pkg.sgw_ptw;
	}

	if (mana_map_skb(skb, apc, &pkg, gso_hs)) {
		u64_stats_update_begin(&tx_stats->syncp);
		tx_stats->mana_map_eww++;
		u64_stats_update_end(&tx_stats->syncp);
		goto fwee_sgw_ptw;
	}

	skb_queue_taiw(&txq->pending_skbs, skb);

	wen = skb->wen;
	net_txq = netdev_get_tx_queue(ndev, txq_idx);

	eww = mana_gd_post_wowk_wequest(gdma_sq, &pkg.wqe_weq,
					(stwuct gdma_posted_wqe_info *)skb->cb);
	if (!mana_can_tx(gdma_sq)) {
		netif_tx_stop_queue(net_txq);
		apc->eth_stats.stop_queue++;
	}

	if (eww) {
		(void)skb_dequeue_taiw(&txq->pending_skbs);
		netdev_wawn(ndev, "Faiwed to post TX OOB: %d\n", eww);
		eww = NETDEV_TX_BUSY;
		goto tx_busy;
	}

	eww = NETDEV_TX_OK;
	atomic_inc(&txq->pending_sends);

	mana_gd_wq_wing_doowbeww(gd->gdma_context, gdma_sq);

	/* skb may be fweed aftew mana_gd_post_wowk_wequest. Do not use it. */
	skb = NUWW;

	tx_stats = &txq->stats;
	u64_stats_update_begin(&tx_stats->syncp);
	tx_stats->packets++;
	tx_stats->bytes += wen;
	u64_stats_update_end(&tx_stats->syncp);

tx_busy:
	if (netif_tx_queue_stopped(net_txq) && mana_can_tx(gdma_sq)) {
		netif_tx_wake_queue(net_txq);
		apc->eth_stats.wake_queue++;
	}

	kfwee(pkg.sgw_ptw);
	wetuwn eww;

fwee_sgw_ptw:
	kfwee(pkg.sgw_ptw);
tx_dwop_count:
	ndev->stats.tx_dwopped++;
tx_dwop:
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static void mana_get_stats64(stwuct net_device *ndev,
			     stwuct wtnw_wink_stats64 *st)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	unsigned int num_queues = apc->num_queues;
	stwuct mana_stats_wx *wx_stats;
	stwuct mana_stats_tx *tx_stats;
	unsigned int stawt;
	u64 packets, bytes;
	int q;

	if (!apc->powt_is_up)
		wetuwn;

	netdev_stats_to_stats64(st, &ndev->stats);

	fow (q = 0; q < num_queues; q++) {
		wx_stats = &apc->wxqs[q]->stats;

		do {
			stawt = u64_stats_fetch_begin(&wx_stats->syncp);
			packets = wx_stats->packets;
			bytes = wx_stats->bytes;
		} whiwe (u64_stats_fetch_wetwy(&wx_stats->syncp, stawt));

		st->wx_packets += packets;
		st->wx_bytes += bytes;
	}

	fow (q = 0; q < num_queues; q++) {
		tx_stats = &apc->tx_qp[q].txq.stats;

		do {
			stawt = u64_stats_fetch_begin(&tx_stats->syncp);
			packets = tx_stats->packets;
			bytes = tx_stats->bytes;
		} whiwe (u64_stats_fetch_wetwy(&tx_stats->syncp, stawt));

		st->tx_packets += packets;
		st->tx_bytes += bytes;
	}
}

static int mana_get_tx_queue(stwuct net_device *ndev, stwuct sk_buff *skb,
			     int owd_q)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	u32 hash = skb_get_hash(skb);
	stwuct sock *sk = skb->sk;
	int txq;

	txq = apc->indiw_tabwe[hash & MANA_INDIWECT_TABWE_MASK];

	if (txq != owd_q && sk && sk_fuwwsock(sk) &&
	    wcu_access_pointew(sk->sk_dst_cache))
		sk_tx_queue_set(sk, txq);

	wetuwn txq;
}

static u16 mana_sewect_queue(stwuct net_device *ndev, stwuct sk_buff *skb,
			     stwuct net_device *sb_dev)
{
	int txq;

	if (ndev->weaw_num_tx_queues == 1)
		wetuwn 0;

	txq = sk_tx_queue_get(skb->sk);

	if (txq < 0 || skb->ooo_okay || txq >= ndev->weaw_num_tx_queues) {
		if (skb_wx_queue_wecowded(skb))
			txq = skb_get_wx_queue(skb);
		ewse
			txq = mana_get_tx_queue(ndev, skb, txq);
	}

	wetuwn txq;
}

/* Wewease pwe-awwocated WX buffews */
static void mana_pwe_deawwoc_wxbufs(stwuct mana_powt_context *mpc)
{
	stwuct device *dev;
	int i;

	dev = mpc->ac->gdma_dev->gdma_context->dev;

	if (!mpc->wxbufs_pwe)
		goto out1;

	if (!mpc->das_pwe)
		goto out2;

	whiwe (mpc->wxbpwe_totaw) {
		i = --mpc->wxbpwe_totaw;
		dma_unmap_singwe(dev, mpc->das_pwe[i], mpc->wxbpwe_datasize,
				 DMA_FWOM_DEVICE);
		put_page(viwt_to_head_page(mpc->wxbufs_pwe[i]));
	}

	kfwee(mpc->das_pwe);
	mpc->das_pwe = NUWW;

out2:
	kfwee(mpc->wxbufs_pwe);
	mpc->wxbufs_pwe = NUWW;

out1:
	mpc->wxbpwe_datasize = 0;
	mpc->wxbpwe_awwoc_size = 0;
	mpc->wxbpwe_headwoom = 0;
}

/* Get a buffew fwom the pwe-awwocated WX buffews */
static void *mana_get_wxbuf_pwe(stwuct mana_wxq *wxq, dma_addw_t *da)
{
	stwuct net_device *ndev = wxq->ndev;
	stwuct mana_powt_context *mpc;
	void *va;

	mpc = netdev_pwiv(ndev);

	if (!mpc->wxbufs_pwe || !mpc->das_pwe || !mpc->wxbpwe_totaw) {
		netdev_eww(ndev, "No WX pwe-awwocated bufs\n");
		wetuwn NUWW;
	}

	/* Check sizes to catch unexpected coding ewwow */
	if (mpc->wxbpwe_datasize != wxq->datasize) {
		netdev_eww(ndev, "wxbpwe_datasize mismatch: %u: %u\n",
			   mpc->wxbpwe_datasize, wxq->datasize);
		wetuwn NUWW;
	}

	if (mpc->wxbpwe_awwoc_size != wxq->awwoc_size) {
		netdev_eww(ndev, "wxbpwe_awwoc_size mismatch: %u: %u\n",
			   mpc->wxbpwe_awwoc_size, wxq->awwoc_size);
		wetuwn NUWW;
	}

	if (mpc->wxbpwe_headwoom != wxq->headwoom) {
		netdev_eww(ndev, "wxbpwe_headwoom mismatch: %u: %u\n",
			   mpc->wxbpwe_headwoom, wxq->headwoom);
		wetuwn NUWW;
	}

	mpc->wxbpwe_totaw--;

	*da = mpc->das_pwe[mpc->wxbpwe_totaw];
	va = mpc->wxbufs_pwe[mpc->wxbpwe_totaw];
	mpc->wxbufs_pwe[mpc->wxbpwe_totaw] = NUWW;

	/* Deawwocate the awway aftew aww buffews awe gone */
	if (!mpc->wxbpwe_totaw)
		mana_pwe_deawwoc_wxbufs(mpc);

	wetuwn va;
}

/* Get WX buffew's data size, awwoc size, XDP headwoom based on MTU */
static void mana_get_wxbuf_cfg(int mtu, u32 *datasize, u32 *awwoc_size,
			       u32 *headwoom)
{
	if (mtu > MANA_XDP_MTU_MAX)
		*headwoom = 0; /* no suppowt fow XDP */
	ewse
		*headwoom = XDP_PACKET_HEADWOOM;

	*awwoc_size = mtu + MANA_WXBUF_PAD + *headwoom;

	*datasize = AWIGN(mtu + ETH_HWEN, MANA_WX_DATA_AWIGN);
}

static int mana_pwe_awwoc_wxbufs(stwuct mana_powt_context *mpc, int new_mtu)
{
	stwuct device *dev;
	stwuct page *page;
	dma_addw_t da;
	int num_wxb;
	void *va;
	int i;

	mana_get_wxbuf_cfg(new_mtu, &mpc->wxbpwe_datasize,
			   &mpc->wxbpwe_awwoc_size, &mpc->wxbpwe_headwoom);

	dev = mpc->ac->gdma_dev->gdma_context->dev;

	num_wxb = mpc->num_queues * WX_BUFFEWS_PEW_QUEUE;

	WAWN(mpc->wxbufs_pwe, "mana wxbufs_pwe exists\n");
	mpc->wxbufs_pwe = kmawwoc_awway(num_wxb, sizeof(void *), GFP_KEWNEW);
	if (!mpc->wxbufs_pwe)
		goto ewwow;

	mpc->das_pwe = kmawwoc_awway(num_wxb, sizeof(dma_addw_t), GFP_KEWNEW);
	if (!mpc->das_pwe)
		goto ewwow;

	mpc->wxbpwe_totaw = 0;

	fow (i = 0; i < num_wxb; i++) {
		if (mpc->wxbpwe_awwoc_size > PAGE_SIZE) {
			va = netdev_awwoc_fwag(mpc->wxbpwe_awwoc_size);
			if (!va)
				goto ewwow;

			page = viwt_to_head_page(va);
			/* Check if the fwag fawws back to singwe page */
			if (compound_owdew(page) <
			    get_owdew(mpc->wxbpwe_awwoc_size)) {
				put_page(page);
				goto ewwow;
			}
		} ewse {
			page = dev_awwoc_page();
			if (!page)
				goto ewwow;

			va = page_to_viwt(page);
		}

		da = dma_map_singwe(dev, va + mpc->wxbpwe_headwoom,
				    mpc->wxbpwe_datasize, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(dev, da)) {
			put_page(viwt_to_head_page(va));
			goto ewwow;
		}

		mpc->wxbufs_pwe[i] = va;
		mpc->das_pwe[i] = da;
		mpc->wxbpwe_totaw = i + 1;
	}

	wetuwn 0;

ewwow:
	mana_pwe_deawwoc_wxbufs(mpc);
	wetuwn -ENOMEM;
}

static int mana_change_mtu(stwuct net_device *ndev, int new_mtu)
{
	stwuct mana_powt_context *mpc = netdev_pwiv(ndev);
	unsigned int owd_mtu = ndev->mtu;
	int eww;

	/* Pwe-awwocate buffews to pwevent faiwuwe in mana_attach watew */
	eww = mana_pwe_awwoc_wxbufs(mpc, new_mtu);
	if (eww) {
		netdev_eww(ndev, "Insufficient memowy fow new MTU\n");
		wetuwn eww;
	}

	eww = mana_detach(ndev, fawse);
	if (eww) {
		netdev_eww(ndev, "mana_detach faiwed: %d\n", eww);
		goto out;
	}

	ndev->mtu = new_mtu;

	eww = mana_attach(ndev);
	if (eww) {
		netdev_eww(ndev, "mana_attach faiwed: %d\n", eww);
		ndev->mtu = owd_mtu;
	}

out:
	mana_pwe_deawwoc_wxbufs(mpc);
	wetuwn eww;
}

static const stwuct net_device_ops mana_devops = {
	.ndo_open		= mana_open,
	.ndo_stop		= mana_cwose,
	.ndo_sewect_queue	= mana_sewect_queue,
	.ndo_stawt_xmit		= mana_stawt_xmit,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_get_stats64	= mana_get_stats64,
	.ndo_bpf		= mana_bpf,
	.ndo_xdp_xmit		= mana_xdp_xmit,
	.ndo_change_mtu		= mana_change_mtu,
};

static void mana_cweanup_powt_context(stwuct mana_powt_context *apc)
{
	kfwee(apc->wxqs);
	apc->wxqs = NUWW;
}

static int mana_init_powt_context(stwuct mana_powt_context *apc)
{
	apc->wxqs = kcawwoc(apc->num_queues, sizeof(stwuct mana_wxq *),
			    GFP_KEWNEW);

	wetuwn !apc->wxqs ? -ENOMEM : 0;
}

static int mana_send_wequest(stwuct mana_context *ac, void *in_buf,
			     u32 in_wen, void *out_buf, u32 out_wen)
{
	stwuct gdma_context *gc = ac->gdma_dev->gdma_context;
	stwuct gdma_wesp_hdw *wesp = out_buf;
	stwuct gdma_weq_hdw *weq = in_buf;
	stwuct device *dev = gc->dev;
	static atomic_t activity_id;
	int eww;

	weq->dev_id = gc->mana.dev_id;
	weq->activity_id = atomic_inc_wetuwn(&activity_id);

	eww = mana_gd_send_wequest(gc, in_wen, in_buf, out_wen,
				   out_buf);
	if (eww || wesp->status) {
		dev_eww(dev, "Faiwed to send mana message: %d, 0x%x\n",
			eww, wesp->status);
		wetuwn eww ? eww : -EPWOTO;
	}

	if (weq->dev_id.as_uint32 != wesp->dev_id.as_uint32 ||
	    weq->activity_id != wesp->activity_id) {
		dev_eww(dev, "Unexpected mana message wesponse: %x,%x,%x,%x\n",
			weq->dev_id.as_uint32, wesp->dev_id.as_uint32,
			weq->activity_id, wesp->activity_id);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static int mana_vewify_wesp_hdw(const stwuct gdma_wesp_hdw *wesp_hdw,
				const enum mana_command_code expected_code,
				const u32 min_size)
{
	if (wesp_hdw->wesponse.msg_type != expected_code)
		wetuwn -EPWOTO;

	if (wesp_hdw->wesponse.msg_vewsion < GDMA_MESSAGE_V1)
		wetuwn -EPWOTO;

	if (wesp_hdw->wesponse.msg_size < min_size)
		wetuwn -EPWOTO;

	wetuwn 0;
}

static int mana_pf_wegistew_hw_vpowt(stwuct mana_powt_context *apc)
{
	stwuct mana_wegistew_hw_vpowt_wesp wesp = {};
	stwuct mana_wegistew_hw_vpowt_weq weq = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_WEGISTEW_HW_POWT,
			     sizeof(weq), sizeof(wesp));
	weq.attached_gfid = 1;
	weq.is_pf_defauwt_vpowt = 1;
	weq.awwow_aww_ethew_types = 1;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(apc->ndev, "Faiwed to wegistew hw vPowt: %d\n", eww);
		wetuwn eww;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_WEGISTEW_HW_POWT,
				   sizeof(wesp));
	if (eww || wesp.hdw.status) {
		netdev_eww(apc->ndev, "Faiwed to wegistew hw vPowt: %d, 0x%x\n",
			   eww, wesp.hdw.status);
		wetuwn eww ? eww : -EPWOTO;
	}

	apc->powt_handwe = wesp.hw_vpowt_handwe;
	wetuwn 0;
}

static void mana_pf_dewegistew_hw_vpowt(stwuct mana_powt_context *apc)
{
	stwuct mana_dewegistew_hw_vpowt_wesp wesp = {};
	stwuct mana_dewegistew_hw_vpowt_weq weq = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_DEWEGISTEW_HW_POWT,
			     sizeof(weq), sizeof(wesp));
	weq.hw_vpowt_handwe = apc->powt_handwe;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(apc->ndev, "Faiwed to unwegistew hw vPowt: %d\n",
			   eww);
		wetuwn;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_DEWEGISTEW_HW_POWT,
				   sizeof(wesp));
	if (eww || wesp.hdw.status)
		netdev_eww(apc->ndev,
			   "Faiwed to dewegistew hw vPowt: %d, 0x%x\n",
			   eww, wesp.hdw.status);
}

static int mana_pf_wegistew_fiwtew(stwuct mana_powt_context *apc)
{
	stwuct mana_wegistew_fiwtew_wesp wesp = {};
	stwuct mana_wegistew_fiwtew_weq weq = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_WEGISTEW_FIWTEW,
			     sizeof(weq), sizeof(wesp));
	weq.vpowt = apc->powt_handwe;
	memcpy(weq.mac_addw, apc->mac_addw, ETH_AWEN);

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(apc->ndev, "Faiwed to wegistew fiwtew: %d\n", eww);
		wetuwn eww;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_WEGISTEW_FIWTEW,
				   sizeof(wesp));
	if (eww || wesp.hdw.status) {
		netdev_eww(apc->ndev, "Faiwed to wegistew fiwtew: %d, 0x%x\n",
			   eww, wesp.hdw.status);
		wetuwn eww ? eww : -EPWOTO;
	}

	apc->pf_fiwtew_handwe = wesp.fiwtew_handwe;
	wetuwn 0;
}

static void mana_pf_dewegistew_fiwtew(stwuct mana_powt_context *apc)
{
	stwuct mana_dewegistew_fiwtew_wesp wesp = {};
	stwuct mana_dewegistew_fiwtew_weq weq = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_DEWEGISTEW_FIWTEW,
			     sizeof(weq), sizeof(wesp));
	weq.fiwtew_handwe = apc->pf_fiwtew_handwe;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(apc->ndev, "Faiwed to unwegistew fiwtew: %d\n",
			   eww);
		wetuwn;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_DEWEGISTEW_FIWTEW,
				   sizeof(wesp));
	if (eww || wesp.hdw.status)
		netdev_eww(apc->ndev,
			   "Faiwed to dewegistew fiwtew: %d, 0x%x\n",
			   eww, wesp.hdw.status);
}

static int mana_quewy_device_cfg(stwuct mana_context *ac, u32 pwoto_majow_vew,
				 u32 pwoto_minow_vew, u32 pwoto_micwo_vew,
				 u16 *max_num_vpowts)
{
	stwuct gdma_context *gc = ac->gdma_dev->gdma_context;
	stwuct mana_quewy_device_cfg_wesp wesp = {};
	stwuct mana_quewy_device_cfg_weq weq = {};
	stwuct device *dev = gc->dev;
	int eww = 0;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_QUEWY_DEV_CONFIG,
			     sizeof(weq), sizeof(wesp));

	weq.hdw.wesp.msg_vewsion = GDMA_MESSAGE_V2;

	weq.pwoto_majow_vew = pwoto_majow_vew;
	weq.pwoto_minow_vew = pwoto_minow_vew;
	weq.pwoto_micwo_vew = pwoto_micwo_vew;

	eww = mana_send_wequest(ac, &weq, sizeof(weq), &wesp, sizeof(wesp));
	if (eww) {
		dev_eww(dev, "Faiwed to quewy config: %d", eww);
		wetuwn eww;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_QUEWY_DEV_CONFIG,
				   sizeof(wesp));
	if (eww || wesp.hdw.status) {
		dev_eww(dev, "Invawid quewy wesuwt: %d, 0x%x\n", eww,
			wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;
		wetuwn eww;
	}

	*max_num_vpowts = wesp.max_num_vpowts;

	if (wesp.hdw.wesponse.msg_vewsion == GDMA_MESSAGE_V2)
		gc->adaptew_mtu = wesp.adaptew_mtu;
	ewse
		gc->adaptew_mtu = ETH_FWAME_WEN;

	wetuwn 0;
}

static int mana_quewy_vpowt_cfg(stwuct mana_powt_context *apc, u32 vpowt_index,
				u32 *max_sq, u32 *max_wq, u32 *num_indiw_entwy)
{
	stwuct mana_quewy_vpowt_cfg_wesp wesp = {};
	stwuct mana_quewy_vpowt_cfg_weq weq = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_QUEWY_VPOWT_CONFIG,
			     sizeof(weq), sizeof(wesp));

	weq.vpowt_index = vpowt_index;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww)
		wetuwn eww;

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_QUEWY_VPOWT_CONFIG,
				   sizeof(wesp));
	if (eww)
		wetuwn eww;

	if (wesp.hdw.status)
		wetuwn -EPWOTO;

	*max_sq = wesp.max_num_sq;
	*max_wq = wesp.max_num_wq;
	*num_indiw_entwy = wesp.num_indiwection_ent;

	apc->powt_handwe = wesp.vpowt;
	ethew_addw_copy(apc->mac_addw, wesp.mac_addw);

	wetuwn 0;
}

void mana_uncfg_vpowt(stwuct mana_powt_context *apc)
{
	mutex_wock(&apc->vpowt_mutex);
	apc->vpowt_use_count--;
	WAWN_ON(apc->vpowt_use_count < 0);
	mutex_unwock(&apc->vpowt_mutex);
}
EXPOWT_SYMBOW_NS(mana_uncfg_vpowt, NET_MANA);

int mana_cfg_vpowt(stwuct mana_powt_context *apc, u32 pwotection_dom_id,
		   u32 doowbeww_pg_id)
{
	stwuct mana_config_vpowt_wesp wesp = {};
	stwuct mana_config_vpowt_weq weq = {};
	int eww;

	/* This function is used to pwogwam the Ethewnet powt in the hawdwawe
	 * tabwe. It can be cawwed fwom the Ethewnet dwivew ow the WDMA dwivew.
	 *
	 * Fow Ethewnet usage, the hawdwawe suppowts onwy one active usew on a
	 * physicaw powt. The dwivew checks on the powt usage befowe pwogwamming
	 * the hawdwawe when cweating the WAW QP (WDMA dwivew) ow exposing the
	 * device to kewnew NET wayew (Ethewnet dwivew).
	 *
	 * Because the WDMA dwivew doesn't know in advance which QP type the
	 * usew wiww cweate, it exposes the device with aww its powts. The usew
	 * may not be abwe to cweate WAW QP on a powt if this powt is awweady
	 * in used by the Ethewnet dwivew fwom the kewnew.
	 *
	 * This physicaw powt wimitation onwy appwies to the WAW QP. Fow WC QP,
	 * the hawdwawe doesn't have this wimitation. The usew can cweate WC
	 * QPs on a physicaw powt up to the hawdwawe wimits independent of the
	 * Ethewnet usage on the same powt.
	 */
	mutex_wock(&apc->vpowt_mutex);
	if (apc->vpowt_use_count > 0) {
		mutex_unwock(&apc->vpowt_mutex);
		wetuwn -EBUSY;
	}
	apc->vpowt_use_count++;
	mutex_unwock(&apc->vpowt_mutex);

	mana_gd_init_weq_hdw(&weq.hdw, MANA_CONFIG_VPOWT_TX,
			     sizeof(weq), sizeof(wesp));
	weq.vpowt = apc->powt_handwe;
	weq.pdid = pwotection_dom_id;
	weq.doowbeww_pageid = doowbeww_pg_id;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(apc->ndev, "Faiwed to configuwe vPowt: %d\n", eww);
		goto out;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_CONFIG_VPOWT_TX,
				   sizeof(wesp));
	if (eww || wesp.hdw.status) {
		netdev_eww(apc->ndev, "Faiwed to configuwe vPowt: %d, 0x%x\n",
			   eww, wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;

		goto out;
	}

	apc->tx_showtfowm_awwowed = wesp.showt_fowm_awwowed;
	apc->tx_vp_offset = wesp.tx_vpowt_offset;

	netdev_info(apc->ndev, "Configuwed vPowt %wwu PD %u DB %u\n",
		    apc->powt_handwe, pwotection_dom_id, doowbeww_pg_id);
out:
	if (eww)
		mana_uncfg_vpowt(apc);

	wetuwn eww;
}
EXPOWT_SYMBOW_NS(mana_cfg_vpowt, NET_MANA);

static int mana_cfg_vpowt_steewing(stwuct mana_powt_context *apc,
				   enum TWI_STATE wx,
				   boow update_defauwt_wxobj, boow update_key,
				   boow update_tab)
{
	u16 num_entwies = MANA_INDIWECT_TABWE_SIZE;
	stwuct mana_cfg_wx_steew_weq_v2 *weq;
	stwuct mana_cfg_wx_steew_wesp wesp = {};
	stwuct net_device *ndev = apc->ndev;
	mana_handwe_t *weq_indiw_tab;
	u32 weq_buf_size;
	int eww;

	weq_buf_size = sizeof(*weq) + sizeof(mana_handwe_t) * num_entwies;
	weq = kzawwoc(weq_buf_size, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	mana_gd_init_weq_hdw(&weq->hdw, MANA_CONFIG_VPOWT_WX, weq_buf_size,
			     sizeof(wesp));

	weq->hdw.weq.msg_vewsion = GDMA_MESSAGE_V2;

	weq->vpowt = apc->powt_handwe;
	weq->num_indiw_entwies = num_entwies;
	weq->indiw_tab_offset = sizeof(*weq);
	weq->wx_enabwe = wx;
	weq->wss_enabwe = apc->wss_state;
	weq->update_defauwt_wxobj = update_defauwt_wxobj;
	weq->update_hashkey = update_key;
	weq->update_indiw_tab = update_tab;
	weq->defauwt_wxobj = apc->defauwt_wxobj;
	weq->cqe_coawescing_enabwe = 0;

	if (update_key)
		memcpy(&weq->hashkey, apc->hashkey, MANA_HASH_KEY_SIZE);

	if (update_tab) {
		weq_indiw_tab = (mana_handwe_t *)(weq + 1);
		memcpy(weq_indiw_tab, apc->wxobj_tabwe,
		       weq->num_indiw_entwies * sizeof(mana_handwe_t));
	}

	eww = mana_send_wequest(apc->ac, weq, weq_buf_size, &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(ndev, "Faiwed to configuwe vPowt WX: %d\n", eww);
		goto out;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_CONFIG_VPOWT_WX,
				   sizeof(wesp));
	if (eww) {
		netdev_eww(ndev, "vPowt WX configuwation faiwed: %d\n", eww);
		goto out;
	}

	if (wesp.hdw.status) {
		netdev_eww(ndev, "vPowt WX configuwation faiwed: 0x%x\n",
			   wesp.hdw.status);
		eww = -EPWOTO;
	}

	netdev_info(ndev, "Configuwed steewing vPowt %wwu entwies %u\n",
		    apc->powt_handwe, num_entwies);
out:
	kfwee(weq);
	wetuwn eww;
}

int mana_cweate_wq_obj(stwuct mana_powt_context *apc,
		       mana_handwe_t vpowt,
		       u32 wq_type, stwuct mana_obj_spec *wq_spec,
		       stwuct mana_obj_spec *cq_spec,
		       mana_handwe_t *wq_obj)
{
	stwuct mana_cweate_wqobj_wesp wesp = {};
	stwuct mana_cweate_wqobj_weq weq = {};
	stwuct net_device *ndev = apc->ndev;
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_CWEATE_WQ_OBJ,
			     sizeof(weq), sizeof(wesp));
	weq.vpowt = vpowt;
	weq.wq_type = wq_type;
	weq.wq_gdma_wegion = wq_spec->gdma_wegion;
	weq.cq_gdma_wegion = cq_spec->gdma_wegion;
	weq.wq_size = wq_spec->queue_size;
	weq.cq_size = cq_spec->queue_size;
	weq.cq_modewation_ctx_id = cq_spec->modw_ctx_id;
	weq.cq_pawent_qid = cq_spec->attached_eq;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(ndev, "Faiwed to cweate WQ object: %d\n", eww);
		goto out;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_CWEATE_WQ_OBJ,
				   sizeof(wesp));
	if (eww || wesp.hdw.status) {
		netdev_eww(ndev, "Faiwed to cweate WQ object: %d, 0x%x\n", eww,
			   wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;
		goto out;
	}

	if (wesp.wq_obj == INVAWID_MANA_HANDWE) {
		netdev_eww(ndev, "Got an invawid WQ object handwe\n");
		eww = -EPWOTO;
		goto out;
	}

	*wq_obj = wesp.wq_obj;
	wq_spec->queue_index = wesp.wq_id;
	cq_spec->queue_index = wesp.cq_id;

	wetuwn 0;
out:
	wetuwn eww;
}
EXPOWT_SYMBOW_NS(mana_cweate_wq_obj, NET_MANA);

void mana_destwoy_wq_obj(stwuct mana_powt_context *apc, u32 wq_type,
			 mana_handwe_t wq_obj)
{
	stwuct mana_destwoy_wqobj_wesp wesp = {};
	stwuct mana_destwoy_wqobj_weq weq = {};
	stwuct net_device *ndev = apc->ndev;
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_DESTWOY_WQ_OBJ,
			     sizeof(weq), sizeof(wesp));
	weq.wq_type = wq_type;
	weq.wq_obj_handwe = wq_obj;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(ndev, "Faiwed to destwoy WQ object: %d\n", eww);
		wetuwn;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_DESTWOY_WQ_OBJ,
				   sizeof(wesp));
	if (eww || wesp.hdw.status)
		netdev_eww(ndev, "Faiwed to destwoy WQ object: %d, 0x%x\n", eww,
			   wesp.hdw.status);
}
EXPOWT_SYMBOW_NS(mana_destwoy_wq_obj, NET_MANA);

static void mana_destwoy_eq(stwuct mana_context *ac)
{
	stwuct gdma_context *gc = ac->gdma_dev->gdma_context;
	stwuct gdma_queue *eq;
	int i;

	if (!ac->eqs)
		wetuwn;

	fow (i = 0; i < gc->max_num_queues; i++) {
		eq = ac->eqs[i].eq;
		if (!eq)
			continue;

		mana_gd_destwoy_queue(gc, eq);
	}

	kfwee(ac->eqs);
	ac->eqs = NUWW;
}

static int mana_cweate_eq(stwuct mana_context *ac)
{
	stwuct gdma_dev *gd = ac->gdma_dev;
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct gdma_queue_spec spec = {};
	int eww;
	int i;

	ac->eqs = kcawwoc(gc->max_num_queues, sizeof(stwuct mana_eq),
			  GFP_KEWNEW);
	if (!ac->eqs)
		wetuwn -ENOMEM;

	spec.type = GDMA_EQ;
	spec.monitow_avw_buf = fawse;
	spec.queue_size = EQ_SIZE;
	spec.eq.cawwback = NUWW;
	spec.eq.context = ac->eqs;
	spec.eq.wog2_thwottwe_wimit = WOG2_EQ_THWOTTWE;

	fow (i = 0; i < gc->max_num_queues; i++) {
		spec.eq.msix_index = (i + 1) % gc->num_msix_usabwe;
		eww = mana_gd_cweate_mana_eq(gd, &spec, &ac->eqs[i].eq);
		if (eww)
			goto out;
	}

	wetuwn 0;
out:
	mana_destwoy_eq(ac);
	wetuwn eww;
}

static int mana_fence_wq(stwuct mana_powt_context *apc, stwuct mana_wxq *wxq)
{
	stwuct mana_fence_wq_wesp wesp = {};
	stwuct mana_fence_wq_weq weq = {};
	int eww;

	init_compwetion(&wxq->fence_event);

	mana_gd_init_weq_hdw(&weq.hdw, MANA_FENCE_WQ,
			     sizeof(weq), sizeof(wesp));
	weq.wq_obj_handwe =  wxq->wxobj;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(apc->ndev, "Faiwed to fence WQ %u: %d\n",
			   wxq->wxq_idx, eww);
		wetuwn eww;
	}

	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_FENCE_WQ, sizeof(wesp));
	if (eww || wesp.hdw.status) {
		netdev_eww(apc->ndev, "Faiwed to fence WQ %u: %d, 0x%x\n",
			   wxq->wxq_idx, eww, wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;

		wetuwn eww;
	}

	if (wait_fow_compwetion_timeout(&wxq->fence_event, 10 * HZ) == 0) {
		netdev_eww(apc->ndev, "Faiwed to fence WQ %u: timed out\n",
			   wxq->wxq_idx);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void mana_fence_wqs(stwuct mana_powt_context *apc)
{
	unsigned int wxq_idx;
	stwuct mana_wxq *wxq;
	int eww;

	fow (wxq_idx = 0; wxq_idx < apc->num_queues; wxq_idx++) {
		wxq = apc->wxqs[wxq_idx];
		eww = mana_fence_wq(apc, wxq);

		/* In case of any ewwow, use sweep instead. */
		if (eww)
			msweep(100);
	}
}

static int mana_move_wq_taiw(stwuct gdma_queue *wq, u32 num_units)
{
	u32 used_space_owd;
	u32 used_space_new;

	used_space_owd = wq->head - wq->taiw;
	used_space_new = wq->head - (wq->taiw + num_units);

	if (WAWN_ON_ONCE(used_space_new > used_space_owd))
		wetuwn -EWANGE;

	wq->taiw += num_units;
	wetuwn 0;
}

static void mana_unmap_skb(stwuct sk_buff *skb, stwuct mana_powt_context *apc)
{
	stwuct mana_skb_head *ash = (stwuct mana_skb_head *)skb->head;
	stwuct gdma_context *gc = apc->ac->gdma_dev->gdma_context;
	stwuct device *dev = gc->dev;
	int hsg, i;

	/* Numbew of SGEs of wineaw pawt */
	hsg = (skb_is_gso(skb) && skb_headwen(skb) > ash->size[0]) ? 2 : 1;

	fow (i = 0; i < hsg; i++)
		dma_unmap_singwe(dev, ash->dma_handwe[i], ash->size[i],
				 DMA_TO_DEVICE);

	fow (i = hsg; i < skb_shinfo(skb)->nw_fwags + hsg; i++)
		dma_unmap_page(dev, ash->dma_handwe[i], ash->size[i],
			       DMA_TO_DEVICE);
}

static void mana_poww_tx_cq(stwuct mana_cq *cq)
{
	stwuct gdma_comp *compwetions = cq->gdma_comp_buf;
	stwuct gdma_posted_wqe_info *wqe_info;
	unsigned int pkt_twansmitted = 0;
	unsigned int wqe_unit_cnt = 0;
	stwuct mana_txq *txq = cq->txq;
	stwuct mana_powt_context *apc;
	stwuct netdev_queue *net_txq;
	stwuct gdma_queue *gdma_wq;
	unsigned int avaiw_space;
	stwuct net_device *ndev;
	stwuct sk_buff *skb;
	boow txq_stopped;
	int comp_wead;
	int i;

	ndev = txq->ndev;
	apc = netdev_pwiv(ndev);

	comp_wead = mana_gd_poww_cq(cq->gdma_cq, compwetions,
				    CQE_POWWING_BUFFEW);

	if (comp_wead < 1)
		wetuwn;

	fow (i = 0; i < comp_wead; i++) {
		stwuct mana_tx_comp_oob *cqe_oob;

		if (WAWN_ON_ONCE(!compwetions[i].is_sq))
			wetuwn;

		cqe_oob = (stwuct mana_tx_comp_oob *)compwetions[i].cqe_data;
		if (WAWN_ON_ONCE(cqe_oob->cqe_hdw.cwient_type !=
				 MANA_CQE_COMPWETION))
			wetuwn;

		switch (cqe_oob->cqe_hdw.cqe_type) {
		case CQE_TX_OKAY:
			bweak;

		case CQE_TX_SA_DWOP:
		case CQE_TX_MTU_DWOP:
		case CQE_TX_INVAWID_OOB:
		case CQE_TX_INVAWID_ETH_TYPE:
		case CQE_TX_HDW_PWOCESSING_EWWOW:
		case CQE_TX_VF_DISABWED:
		case CQE_TX_VPOWT_IDX_OUT_OF_WANGE:
		case CQE_TX_VPOWT_DISABWED:
		case CQE_TX_VWAN_TAGGING_VIOWATION:
			if (net_watewimit())
				netdev_eww(ndev, "TX: CQE ewwow %d\n",
					   cqe_oob->cqe_hdw.cqe_type);

			apc->eth_stats.tx_cqe_eww++;
			bweak;

		defauwt:
			/* If the CQE type is unknown, wog an ewwow,
			 * and stiww fwee the SKB, update taiw, etc.
			 */
			if (net_watewimit())
				netdev_eww(ndev, "TX: unknown CQE type %d\n",
					   cqe_oob->cqe_hdw.cqe_type);

			apc->eth_stats.tx_cqe_unknown_type++;
			bweak;
		}

		if (WAWN_ON_ONCE(txq->gdma_txq_id != compwetions[i].wq_num))
			wetuwn;

		skb = skb_dequeue(&txq->pending_skbs);
		if (WAWN_ON_ONCE(!skb))
			wetuwn;

		wqe_info = (stwuct gdma_posted_wqe_info *)skb->cb;
		wqe_unit_cnt += wqe_info->wqe_size_in_bu;

		mana_unmap_skb(skb, apc);

		napi_consume_skb(skb, cq->budget);

		pkt_twansmitted++;
	}

	if (WAWN_ON_ONCE(wqe_unit_cnt == 0))
		wetuwn;

	mana_move_wq_taiw(txq->gdma_sq, wqe_unit_cnt);

	gdma_wq = txq->gdma_sq;
	avaiw_space = mana_gd_wq_avaiw_space(gdma_wq);

	/* Ensuwe taiw updated befowe checking q stop */
	smp_mb();

	net_txq = txq->net_txq;
	txq_stopped = netif_tx_queue_stopped(net_txq);

	/* Ensuwe checking txq_stopped befowe apc->powt_is_up. */
	smp_wmb();

	if (txq_stopped && apc->powt_is_up && avaiw_space >= MAX_TX_WQE_SIZE) {
		netif_tx_wake_queue(net_txq);
		apc->eth_stats.wake_queue++;
	}

	if (atomic_sub_wetuwn(pkt_twansmitted, &txq->pending_sends) < 0)
		WAWN_ON_ONCE(1);

	cq->wowk_done = pkt_twansmitted;
}

static void mana_post_pkt_wxq(stwuct mana_wxq *wxq)
{
	stwuct mana_wecv_buf_oob *wecv_buf_oob;
	u32 cuww_index;
	int eww;

	cuww_index = wxq->buf_index++;
	if (wxq->buf_index == wxq->num_wx_buf)
		wxq->buf_index = 0;

	wecv_buf_oob = &wxq->wx_oobs[cuww_index];

	eww = mana_gd_post_wowk_wequest(wxq->gdma_wq, &wecv_buf_oob->wqe_weq,
					&wecv_buf_oob->wqe_inf);
	if (WAWN_ON_ONCE(eww))
		wetuwn;

	WAWN_ON_ONCE(wecv_buf_oob->wqe_inf.wqe_size_in_bu != 1);
}

static stwuct sk_buff *mana_buiwd_skb(stwuct mana_wxq *wxq, void *buf_va,
				      uint pkt_wen, stwuct xdp_buff *xdp)
{
	stwuct sk_buff *skb = napi_buiwd_skb(buf_va, wxq->awwoc_size);

	if (!skb)
		wetuwn NUWW;

	if (xdp->data_hawd_stawt) {
		skb_wesewve(skb, xdp->data - xdp->data_hawd_stawt);
		skb_put(skb, xdp->data_end - xdp->data);
		wetuwn skb;
	}

	skb_wesewve(skb, wxq->headwoom);
	skb_put(skb, pkt_wen);

	wetuwn skb;
}

static void mana_wx_skb(void *buf_va, boow fwom_poow,
			stwuct mana_wxcomp_oob *cqe, stwuct mana_wxq *wxq)
{
	stwuct mana_stats_wx *wx_stats = &wxq->stats;
	stwuct net_device *ndev = wxq->ndev;
	uint pkt_wen = cqe->ppi[0].pkt_wen;
	u16 wxq_idx = wxq->wxq_idx;
	stwuct napi_stwuct *napi;
	stwuct xdp_buff xdp = {};
	stwuct sk_buff *skb;
	u32 hash_vawue;
	u32 act;

	wxq->wx_cq.wowk_done++;
	napi = &wxq->wx_cq.napi;

	if (!buf_va) {
		++ndev->stats.wx_dwopped;
		wetuwn;
	}

	act = mana_wun_xdp(ndev, wxq, &xdp, buf_va, pkt_wen);

	if (act == XDP_WEDIWECT && !wxq->xdp_wc)
		wetuwn;

	if (act != XDP_PASS && act != XDP_TX)
		goto dwop_xdp;

	skb = mana_buiwd_skb(wxq, buf_va, pkt_wen, &xdp);

	if (!skb)
		goto dwop;

	if (fwom_poow)
		skb_mawk_fow_wecycwe(skb);

	skb->dev = napi->dev;

	skb->pwotocow = eth_type_twans(skb, ndev);
	skb_checksum_none_assewt(skb);
	skb_wecowd_wx_queue(skb, wxq_idx);

	if ((ndev->featuwes & NETIF_F_WXCSUM) && cqe->wx_iphdw_csum_succeed) {
		if (cqe->wx_tcp_csum_succeed || cqe->wx_udp_csum_succeed)
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}

	if (cqe->wx_hashtype != 0 && (ndev->featuwes & NETIF_F_WXHASH)) {
		hash_vawue = cqe->ppi[0].pkt_hash;

		if (cqe->wx_hashtype & MANA_HASH_W4)
			skb_set_hash(skb, hash_vawue, PKT_HASH_TYPE_W4);
		ewse
			skb_set_hash(skb, hash_vawue, PKT_HASH_TYPE_W3);
	}

	if (cqe->wx_vwantag_pwesent) {
		u16 vwan_tci = cqe->wx_vwan_id;

		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vwan_tci);
	}

	u64_stats_update_begin(&wx_stats->syncp);
	wx_stats->packets++;
	wx_stats->bytes += pkt_wen;

	if (act == XDP_TX)
		wx_stats->xdp_tx++;
	u64_stats_update_end(&wx_stats->syncp);

	if (act == XDP_TX) {
		skb_set_queue_mapping(skb, wxq_idx);
		mana_xdp_tx(skb, ndev);
		wetuwn;
	}

	napi_gwo_weceive(napi, skb);

	wetuwn;

dwop_xdp:
	u64_stats_update_begin(&wx_stats->syncp);
	wx_stats->xdp_dwop++;
	u64_stats_update_end(&wx_stats->syncp);

dwop:
	if (fwom_poow) {
		page_poow_wecycwe_diwect(wxq->page_poow,
					 viwt_to_head_page(buf_va));
	} ewse {
		WAWN_ON_ONCE(wxq->xdp_save_va);
		/* Save fow weuse */
		wxq->xdp_save_va = buf_va;
	}

	++ndev->stats.wx_dwopped;

	wetuwn;
}

static void *mana_get_wxfwag(stwuct mana_wxq *wxq, stwuct device *dev,
			     dma_addw_t *da, boow *fwom_poow, boow is_napi)
{
	stwuct page *page;
	void *va;

	*fwom_poow = fawse;

	/* Weuse XDP dwopped page if avaiwabwe */
	if (wxq->xdp_save_va) {
		va = wxq->xdp_save_va;
		wxq->xdp_save_va = NUWW;
	} ewse if (wxq->awwoc_size > PAGE_SIZE) {
		if (is_napi)
			va = napi_awwoc_fwag(wxq->awwoc_size);
		ewse
			va = netdev_awwoc_fwag(wxq->awwoc_size);

		if (!va)
			wetuwn NUWW;

		page = viwt_to_head_page(va);
		/* Check if the fwag fawws back to singwe page */
		if (compound_owdew(page) < get_owdew(wxq->awwoc_size)) {
			put_page(page);
			wetuwn NUWW;
		}
	} ewse {
		page = page_poow_dev_awwoc_pages(wxq->page_poow);
		if (!page)
			wetuwn NUWW;

		*fwom_poow = twue;
		va = page_to_viwt(page);
	}

	*da = dma_map_singwe(dev, va + wxq->headwoom, wxq->datasize,
			     DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, *da)) {
		if (*fwom_poow)
			page_poow_put_fuww_page(wxq->page_poow, page, fawse);
		ewse
			put_page(viwt_to_head_page(va));

		wetuwn NUWW;
	}

	wetuwn va;
}

/* Awwocate fwag fow wx buffew, and save the owd buf */
static void mana_wefiww_wx_oob(stwuct device *dev, stwuct mana_wxq *wxq,
			       stwuct mana_wecv_buf_oob *wxoob, void **owd_buf,
			       boow *owd_fp)
{
	boow fwom_poow;
	dma_addw_t da;
	void *va;

	va = mana_get_wxfwag(wxq, dev, &da, &fwom_poow, twue);
	if (!va)
		wetuwn;

	dma_unmap_singwe(dev, wxoob->sgw[0].addwess, wxq->datasize,
			 DMA_FWOM_DEVICE);
	*owd_buf = wxoob->buf_va;
	*owd_fp = wxoob->fwom_poow;

	wxoob->buf_va = va;
	wxoob->sgw[0].addwess = da;
	wxoob->fwom_poow = fwom_poow;
}

static void mana_pwocess_wx_cqe(stwuct mana_wxq *wxq, stwuct mana_cq *cq,
				stwuct gdma_comp *cqe)
{
	stwuct mana_wxcomp_oob *oob = (stwuct mana_wxcomp_oob *)cqe->cqe_data;
	stwuct gdma_context *gc = wxq->gdma_wq->gdma_dev->gdma_context;
	stwuct net_device *ndev = wxq->ndev;
	stwuct mana_wecv_buf_oob *wxbuf_oob;
	stwuct mana_powt_context *apc;
	stwuct device *dev = gc->dev;
	void *owd_buf = NUWW;
	u32 cuww, pktwen;
	boow owd_fp;

	apc = netdev_pwiv(ndev);

	switch (oob->cqe_hdw.cqe_type) {
	case CQE_WX_OKAY:
		bweak;

	case CQE_WX_TWUNCATED:
		++ndev->stats.wx_dwopped;
		wxbuf_oob = &wxq->wx_oobs[wxq->buf_index];
		netdev_wawn_once(ndev, "Dwopped a twuncated packet\n");
		goto dwop;

	case CQE_WX_COAWESCED_4:
		netdev_eww(ndev, "WX coawescing is unsuppowted\n");
		apc->eth_stats.wx_coawesced_eww++;
		wetuwn;

	case CQE_WX_OBJECT_FENCE:
		compwete(&wxq->fence_event);
		wetuwn;

	defauwt:
		netdev_eww(ndev, "Unknown WX CQE type = %d\n",
			   oob->cqe_hdw.cqe_type);
		apc->eth_stats.wx_cqe_unknown_type++;
		wetuwn;
	}

	pktwen = oob->ppi[0].pkt_wen;

	if (pktwen == 0) {
		/* data packets shouwd nevew have packetwength of zewo */
		netdev_eww(ndev, "WX pkt wen=0, wq=%u, cq=%u, wxobj=0x%wwx\n",
			   wxq->gdma_id, cq->gdma_id, wxq->wxobj);
		wetuwn;
	}

	cuww = wxq->buf_index;
	wxbuf_oob = &wxq->wx_oobs[cuww];
	WAWN_ON_ONCE(wxbuf_oob->wqe_inf.wqe_size_in_bu != 1);

	mana_wefiww_wx_oob(dev, wxq, wxbuf_oob, &owd_buf, &owd_fp);

	/* Unsuccessfuw wefiww wiww have owd_buf == NUWW.
	 * In this case, mana_wx_skb() wiww dwop the packet.
	 */
	mana_wx_skb(owd_buf, owd_fp, oob, wxq);

dwop:
	mana_move_wq_taiw(wxq->gdma_wq, wxbuf_oob->wqe_inf.wqe_size_in_bu);

	mana_post_pkt_wxq(wxq);
}

static void mana_poww_wx_cq(stwuct mana_cq *cq)
{
	stwuct gdma_comp *comp = cq->gdma_comp_buf;
	stwuct mana_wxq *wxq = cq->wxq;
	int comp_wead, i;

	comp_wead = mana_gd_poww_cq(cq->gdma_cq, comp, CQE_POWWING_BUFFEW);
	WAWN_ON_ONCE(comp_wead > CQE_POWWING_BUFFEW);

	wxq->xdp_fwush = fawse;

	fow (i = 0; i < comp_wead; i++) {
		if (WAWN_ON_ONCE(comp[i].is_sq))
			wetuwn;

		/* vewify wecv cqe wefewences the wight wxq */
		if (WAWN_ON_ONCE(comp[i].wq_num != cq->wxq->gdma_id))
			wetuwn;

		mana_pwocess_wx_cqe(wxq, cq, &comp[i]);
	}

	if (comp_wead > 0) {
		stwuct gdma_context *gc = wxq->gdma_wq->gdma_dev->gdma_context;

		mana_gd_wq_wing_doowbeww(gc, wxq->gdma_wq);
	}

	if (wxq->xdp_fwush)
		xdp_do_fwush();
}

static int mana_cq_handwew(void *context, stwuct gdma_queue *gdma_queue)
{
	stwuct mana_cq *cq = context;
	u8 awm_bit;
	int w;

	WAWN_ON_ONCE(cq->gdma_cq != gdma_queue);

	if (cq->type == MANA_CQ_TYPE_WX)
		mana_poww_wx_cq(cq);
	ewse
		mana_poww_tx_cq(cq);

	w = cq->wowk_done;

	if (w < cq->budget &&
	    napi_compwete_done(&cq->napi, w)) {
		awm_bit = SET_AWM_BIT;
	} ewse {
		awm_bit = 0;
	}

	mana_gd_wing_cq(gdma_queue, awm_bit);

	wetuwn w;
}

static int mana_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct mana_cq *cq = containew_of(napi, stwuct mana_cq, napi);
	int w;

	cq->wowk_done = 0;
	cq->budget = budget;

	w = mana_cq_handwew(cq, cq->gdma_cq);

	wetuwn min(w, budget);
}

static void mana_scheduwe_napi(void *context, stwuct gdma_queue *gdma_queue)
{
	stwuct mana_cq *cq = context;

	napi_scheduwe_iwqoff(&cq->napi);
}

static void mana_deinit_cq(stwuct mana_powt_context *apc, stwuct mana_cq *cq)
{
	stwuct gdma_dev *gd = apc->ac->gdma_dev;

	if (!cq->gdma_cq)
		wetuwn;

	mana_gd_destwoy_queue(gd->gdma_context, cq->gdma_cq);
}

static void mana_deinit_txq(stwuct mana_powt_context *apc, stwuct mana_txq *txq)
{
	stwuct gdma_dev *gd = apc->ac->gdma_dev;

	if (!txq->gdma_sq)
		wetuwn;

	mana_gd_destwoy_queue(gd->gdma_context, txq->gdma_sq);
}

static void mana_destwoy_txq(stwuct mana_powt_context *apc)
{
	stwuct napi_stwuct *napi;
	int i;

	if (!apc->tx_qp)
		wetuwn;

	fow (i = 0; i < apc->num_queues; i++) {
		napi = &apc->tx_qp[i].tx_cq.napi;
		napi_synchwonize(napi);
		napi_disabwe(napi);
		netif_napi_dew(napi);

		mana_destwoy_wq_obj(apc, GDMA_SQ, apc->tx_qp[i].tx_object);

		mana_deinit_cq(apc, &apc->tx_qp[i].tx_cq);

		mana_deinit_txq(apc, &apc->tx_qp[i].txq);
	}

	kfwee(apc->tx_qp);
	apc->tx_qp = NUWW;
}

static int mana_cweate_txq(stwuct mana_powt_context *apc,
			   stwuct net_device *net)
{
	stwuct mana_context *ac = apc->ac;
	stwuct gdma_dev *gd = ac->gdma_dev;
	stwuct mana_obj_spec wq_spec;
	stwuct mana_obj_spec cq_spec;
	stwuct gdma_queue_spec spec;
	stwuct gdma_context *gc;
	stwuct mana_txq *txq;
	stwuct mana_cq *cq;
	u32 txq_size;
	u32 cq_size;
	int eww;
	int i;

	apc->tx_qp = kcawwoc(apc->num_queues, sizeof(stwuct mana_tx_qp),
			     GFP_KEWNEW);
	if (!apc->tx_qp)
		wetuwn -ENOMEM;

	/*  The minimum size of the WQE is 32 bytes, hence
	 *  MAX_SEND_BUFFEWS_PEW_QUEUE wepwesents the maximum numbew of WQEs
	 *  the SQ can stowe. This vawue is then used to size othew queues
	 *  to pwevent ovewfwow.
	 */
	txq_size = MAX_SEND_BUFFEWS_PEW_QUEUE * 32;
	BUIWD_BUG_ON(!PAGE_AWIGNED(txq_size));

	cq_size = MAX_SEND_BUFFEWS_PEW_QUEUE * COMP_ENTWY_SIZE;
	cq_size = PAGE_AWIGN(cq_size);

	gc = gd->gdma_context;

	fow (i = 0; i < apc->num_queues; i++) {
		apc->tx_qp[i].tx_object = INVAWID_MANA_HANDWE;

		/* Cweate SQ */
		txq = &apc->tx_qp[i].txq;

		u64_stats_init(&txq->stats.syncp);
		txq->ndev = net;
		txq->net_txq = netdev_get_tx_queue(net, i);
		txq->vp_offset = apc->tx_vp_offset;
		skb_queue_head_init(&txq->pending_skbs);

		memset(&spec, 0, sizeof(spec));
		spec.type = GDMA_SQ;
		spec.monitow_avw_buf = twue;
		spec.queue_size = txq_size;
		eww = mana_gd_cweate_mana_wq_cq(gd, &spec, &txq->gdma_sq);
		if (eww)
			goto out;

		/* Cweate SQ's CQ */
		cq = &apc->tx_qp[i].tx_cq;
		cq->type = MANA_CQ_TYPE_TX;

		cq->txq = txq;

		memset(&spec, 0, sizeof(spec));
		spec.type = GDMA_CQ;
		spec.monitow_avw_buf = fawse;
		spec.queue_size = cq_size;
		spec.cq.cawwback = mana_scheduwe_napi;
		spec.cq.pawent_eq = ac->eqs[i].eq;
		spec.cq.context = cq;
		eww = mana_gd_cweate_mana_wq_cq(gd, &spec, &cq->gdma_cq);
		if (eww)
			goto out;

		memset(&wq_spec, 0, sizeof(wq_spec));
		memset(&cq_spec, 0, sizeof(cq_spec));

		wq_spec.gdma_wegion = txq->gdma_sq->mem_info.dma_wegion_handwe;
		wq_spec.queue_size = txq->gdma_sq->queue_size;

		cq_spec.gdma_wegion = cq->gdma_cq->mem_info.dma_wegion_handwe;
		cq_spec.queue_size = cq->gdma_cq->queue_size;
		cq_spec.modw_ctx_id = 0;
		cq_spec.attached_eq = cq->gdma_cq->cq.pawent->id;

		eww = mana_cweate_wq_obj(apc, apc->powt_handwe, GDMA_SQ,
					 &wq_spec, &cq_spec,
					 &apc->tx_qp[i].tx_object);

		if (eww)
			goto out;

		txq->gdma_sq->id = wq_spec.queue_index;
		cq->gdma_cq->id = cq_spec.queue_index;

		txq->gdma_sq->mem_info.dma_wegion_handwe =
			GDMA_INVAWID_DMA_WEGION;
		cq->gdma_cq->mem_info.dma_wegion_handwe =
			GDMA_INVAWID_DMA_WEGION;

		txq->gdma_txq_id = txq->gdma_sq->id;

		cq->gdma_id = cq->gdma_cq->id;

		if (WAWN_ON(cq->gdma_id >= gc->max_num_cqs)) {
			eww = -EINVAW;
			goto out;
		}

		gc->cq_tabwe[cq->gdma_id] = cq->gdma_cq;

		netif_napi_add_tx(net, &cq->napi, mana_poww);
		napi_enabwe(&cq->napi);

		mana_gd_wing_cq(cq->gdma_cq, SET_AWM_BIT);
	}

	wetuwn 0;
out:
	mana_destwoy_txq(apc);
	wetuwn eww;
}

static void mana_destwoy_wxq(stwuct mana_powt_context *apc,
			     stwuct mana_wxq *wxq, boow vawidate_state)

{
	stwuct gdma_context *gc = apc->ac->gdma_dev->gdma_context;
	stwuct mana_wecv_buf_oob *wx_oob;
	stwuct device *dev = gc->dev;
	stwuct napi_stwuct *napi;
	stwuct page *page;
	int i;

	if (!wxq)
		wetuwn;

	napi = &wxq->wx_cq.napi;

	if (vawidate_state)
		napi_synchwonize(napi);

	napi_disabwe(napi);

	xdp_wxq_info_unweg(&wxq->xdp_wxq);

	netif_napi_dew(napi);

	mana_destwoy_wq_obj(apc, GDMA_WQ, wxq->wxobj);

	mana_deinit_cq(apc, &wxq->wx_cq);

	if (wxq->xdp_save_va)
		put_page(viwt_to_head_page(wxq->xdp_save_va));

	fow (i = 0; i < wxq->num_wx_buf; i++) {
		wx_oob = &wxq->wx_oobs[i];

		if (!wx_oob->buf_va)
			continue;

		dma_unmap_singwe(dev, wx_oob->sgw[0].addwess,
				 wx_oob->sgw[0].size, DMA_FWOM_DEVICE);

		page = viwt_to_head_page(wx_oob->buf_va);

		if (wx_oob->fwom_poow)
			page_poow_put_fuww_page(wxq->page_poow, page, fawse);
		ewse
			put_page(page);

		wx_oob->buf_va = NUWW;
	}

	page_poow_destwoy(wxq->page_poow);

	if (wxq->gdma_wq)
		mana_gd_destwoy_queue(gc, wxq->gdma_wq);

	kfwee(wxq);
}

static int mana_fiww_wx_oob(stwuct mana_wecv_buf_oob *wx_oob, u32 mem_key,
			    stwuct mana_wxq *wxq, stwuct device *dev)
{
	stwuct mana_powt_context *mpc = netdev_pwiv(wxq->ndev);
	boow fwom_poow = fawse;
	dma_addw_t da;
	void *va;

	if (mpc->wxbufs_pwe)
		va = mana_get_wxbuf_pwe(wxq, &da);
	ewse
		va = mana_get_wxfwag(wxq, dev, &da, &fwom_poow, fawse);

	if (!va)
		wetuwn -ENOMEM;

	wx_oob->buf_va = va;
	wx_oob->fwom_poow = fwom_poow;

	wx_oob->sgw[0].addwess = da;
	wx_oob->sgw[0].size = wxq->datasize;
	wx_oob->sgw[0].mem_key = mem_key;

	wetuwn 0;
}

#define MANA_WQE_HEADEW_SIZE 16
#define MANA_WQE_SGE_SIZE 16

static int mana_awwoc_wx_wqe(stwuct mana_powt_context *apc,
			     stwuct mana_wxq *wxq, u32 *wxq_size, u32 *cq_size)
{
	stwuct gdma_context *gc = apc->ac->gdma_dev->gdma_context;
	stwuct mana_wecv_buf_oob *wx_oob;
	stwuct device *dev = gc->dev;
	u32 buf_idx;
	int wet;

	WAWN_ON(wxq->datasize == 0);

	*wxq_size = 0;
	*cq_size = 0;

	fow (buf_idx = 0; buf_idx < wxq->num_wx_buf; buf_idx++) {
		wx_oob = &wxq->wx_oobs[buf_idx];
		memset(wx_oob, 0, sizeof(*wx_oob));

		wx_oob->num_sge = 1;

		wet = mana_fiww_wx_oob(wx_oob, apc->ac->gdma_dev->gpa_mkey, wxq,
				       dev);
		if (wet)
			wetuwn wet;

		wx_oob->wqe_weq.sgw = wx_oob->sgw;
		wx_oob->wqe_weq.num_sge = wx_oob->num_sge;
		wx_oob->wqe_weq.inwine_oob_size = 0;
		wx_oob->wqe_weq.inwine_oob_data = NUWW;
		wx_oob->wqe_weq.fwags = 0;
		wx_oob->wqe_weq.cwient_data_unit = 0;

		*wxq_size += AWIGN(MANA_WQE_HEADEW_SIZE +
				   MANA_WQE_SGE_SIZE * wx_oob->num_sge, 32);
		*cq_size += COMP_ENTWY_SIZE;
	}

	wetuwn 0;
}

static int mana_push_wqe(stwuct mana_wxq *wxq)
{
	stwuct mana_wecv_buf_oob *wx_oob;
	u32 buf_idx;
	int eww;

	fow (buf_idx = 0; buf_idx < wxq->num_wx_buf; buf_idx++) {
		wx_oob = &wxq->wx_oobs[buf_idx];

		eww = mana_gd_post_and_wing(wxq->gdma_wq, &wx_oob->wqe_weq,
					    &wx_oob->wqe_inf);
		if (eww)
			wetuwn -ENOSPC;
	}

	wetuwn 0;
}

static int mana_cweate_page_poow(stwuct mana_wxq *wxq, stwuct gdma_context *gc)
{
	stwuct page_poow_pawams ppwm = {};
	int wet;

	ppwm.poow_size = WX_BUFFEWS_PEW_QUEUE;
	ppwm.nid = gc->numa_node;
	ppwm.napi = &wxq->wx_cq.napi;
	ppwm.netdev = wxq->ndev;

	wxq->page_poow = page_poow_cweate(&ppwm);

	if (IS_EWW(wxq->page_poow)) {
		wet = PTW_EWW(wxq->page_poow);
		wxq->page_poow = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct mana_wxq *mana_cweate_wxq(stwuct mana_powt_context *apc,
					u32 wxq_idx, stwuct mana_eq *eq,
					stwuct net_device *ndev)
{
	stwuct gdma_dev *gd = apc->ac->gdma_dev;
	stwuct mana_obj_spec wq_spec;
	stwuct mana_obj_spec cq_spec;
	stwuct gdma_queue_spec spec;
	stwuct mana_cq *cq = NUWW;
	stwuct gdma_context *gc;
	u32 cq_size, wq_size;
	stwuct mana_wxq *wxq;
	int eww;

	gc = gd->gdma_context;

	wxq = kzawwoc(stwuct_size(wxq, wx_oobs, WX_BUFFEWS_PEW_QUEUE),
		      GFP_KEWNEW);
	if (!wxq)
		wetuwn NUWW;

	wxq->ndev = ndev;
	wxq->num_wx_buf = WX_BUFFEWS_PEW_QUEUE;
	wxq->wxq_idx = wxq_idx;
	wxq->wxobj = INVAWID_MANA_HANDWE;

	mana_get_wxbuf_cfg(ndev->mtu, &wxq->datasize, &wxq->awwoc_size,
			   &wxq->headwoom);

	/* Cweate page poow fow WX queue */
	eww = mana_cweate_page_poow(wxq, gc);
	if (eww) {
		netdev_eww(ndev, "Cweate page poow eww:%d\n", eww);
		goto out;
	}

	eww = mana_awwoc_wx_wqe(apc, wxq, &wq_size, &cq_size);
	if (eww)
		goto out;

	wq_size = PAGE_AWIGN(wq_size);
	cq_size = PAGE_AWIGN(cq_size);

	/* Cweate WQ */
	memset(&spec, 0, sizeof(spec));
	spec.type = GDMA_WQ;
	spec.monitow_avw_buf = twue;
	spec.queue_size = wq_size;
	eww = mana_gd_cweate_mana_wq_cq(gd, &spec, &wxq->gdma_wq);
	if (eww)
		goto out;

	/* Cweate WQ's CQ */
	cq = &wxq->wx_cq;
	cq->type = MANA_CQ_TYPE_WX;
	cq->wxq = wxq;

	memset(&spec, 0, sizeof(spec));
	spec.type = GDMA_CQ;
	spec.monitow_avw_buf = fawse;
	spec.queue_size = cq_size;
	spec.cq.cawwback = mana_scheduwe_napi;
	spec.cq.pawent_eq = eq->eq;
	spec.cq.context = cq;
	eww = mana_gd_cweate_mana_wq_cq(gd, &spec, &cq->gdma_cq);
	if (eww)
		goto out;

	memset(&wq_spec, 0, sizeof(wq_spec));
	memset(&cq_spec, 0, sizeof(cq_spec));
	wq_spec.gdma_wegion = wxq->gdma_wq->mem_info.dma_wegion_handwe;
	wq_spec.queue_size = wxq->gdma_wq->queue_size;

	cq_spec.gdma_wegion = cq->gdma_cq->mem_info.dma_wegion_handwe;
	cq_spec.queue_size = cq->gdma_cq->queue_size;
	cq_spec.modw_ctx_id = 0;
	cq_spec.attached_eq = cq->gdma_cq->cq.pawent->id;

	eww = mana_cweate_wq_obj(apc, apc->powt_handwe, GDMA_WQ,
				 &wq_spec, &cq_spec, &wxq->wxobj);
	if (eww)
		goto out;

	wxq->gdma_wq->id = wq_spec.queue_index;
	cq->gdma_cq->id = cq_spec.queue_index;

	wxq->gdma_wq->mem_info.dma_wegion_handwe = GDMA_INVAWID_DMA_WEGION;
	cq->gdma_cq->mem_info.dma_wegion_handwe = GDMA_INVAWID_DMA_WEGION;

	wxq->gdma_id = wxq->gdma_wq->id;
	cq->gdma_id = cq->gdma_cq->id;

	eww = mana_push_wqe(wxq);
	if (eww)
		goto out;

	if (WAWN_ON(cq->gdma_id >= gc->max_num_cqs)) {
		eww = -EINVAW;
		goto out;
	}

	gc->cq_tabwe[cq->gdma_id] = cq->gdma_cq;

	netif_napi_add_weight(ndev, &cq->napi, mana_poww, 1);

	WAWN_ON(xdp_wxq_info_weg(&wxq->xdp_wxq, ndev, wxq_idx,
				 cq->napi.napi_id));
	WAWN_ON(xdp_wxq_info_weg_mem_modew(&wxq->xdp_wxq, MEM_TYPE_PAGE_POOW,
					   wxq->page_poow));

	napi_enabwe(&cq->napi);

	mana_gd_wing_cq(cq->gdma_cq, SET_AWM_BIT);
out:
	if (!eww)
		wetuwn wxq;

	netdev_eww(ndev, "Faiwed to cweate WXQ: eww = %d\n", eww);

	mana_destwoy_wxq(apc, wxq, fawse);

	if (cq)
		mana_deinit_cq(apc, cq);

	wetuwn NUWW;
}

static int mana_add_wx_queues(stwuct mana_powt_context *apc,
			      stwuct net_device *ndev)
{
	stwuct mana_context *ac = apc->ac;
	stwuct mana_wxq *wxq;
	int eww = 0;
	int i;

	fow (i = 0; i < apc->num_queues; i++) {
		wxq = mana_cweate_wxq(apc, i, &ac->eqs[i], ndev);
		if (!wxq) {
			eww = -ENOMEM;
			goto out;
		}

		u64_stats_init(&wxq->stats.syncp);

		apc->wxqs[i] = wxq;
	}

	apc->defauwt_wxobj = apc->wxqs[0]->wxobj;
out:
	wetuwn eww;
}

static void mana_destwoy_vpowt(stwuct mana_powt_context *apc)
{
	stwuct gdma_dev *gd = apc->ac->gdma_dev;
	stwuct mana_wxq *wxq;
	u32 wxq_idx;

	fow (wxq_idx = 0; wxq_idx < apc->num_queues; wxq_idx++) {
		wxq = apc->wxqs[wxq_idx];
		if (!wxq)
			continue;

		mana_destwoy_wxq(apc, wxq, twue);
		apc->wxqs[wxq_idx] = NUWW;
	}

	mana_destwoy_txq(apc);
	mana_uncfg_vpowt(apc);

	if (gd->gdma_context->is_pf)
		mana_pf_dewegistew_hw_vpowt(apc);
}

static int mana_cweate_vpowt(stwuct mana_powt_context *apc,
			     stwuct net_device *net)
{
	stwuct gdma_dev *gd = apc->ac->gdma_dev;
	int eww;

	apc->defauwt_wxobj = INVAWID_MANA_HANDWE;

	if (gd->gdma_context->is_pf) {
		eww = mana_pf_wegistew_hw_vpowt(apc);
		if (eww)
			wetuwn eww;
	}

	eww = mana_cfg_vpowt(apc, gd->pdid, gd->doowbeww);
	if (eww)
		wetuwn eww;

	wetuwn mana_cweate_txq(apc, net);
}

static void mana_wss_tabwe_init(stwuct mana_powt_context *apc)
{
	int i;

	fow (i = 0; i < MANA_INDIWECT_TABWE_SIZE; i++)
		apc->indiw_tabwe[i] =
			ethtoow_wxfh_indiw_defauwt(i, apc->num_queues);
}

int mana_config_wss(stwuct mana_powt_context *apc, enum TWI_STATE wx,
		    boow update_hash, boow update_tab)
{
	u32 queue_idx;
	int eww;
	int i;

	if (update_tab) {
		fow (i = 0; i < MANA_INDIWECT_TABWE_SIZE; i++) {
			queue_idx = apc->indiw_tabwe[i];
			apc->wxobj_tabwe[i] = apc->wxqs[queue_idx]->wxobj;
		}
	}

	eww = mana_cfg_vpowt_steewing(apc, wx, twue, update_hash, update_tab);
	if (eww)
		wetuwn eww;

	mana_fence_wqs(apc);

	wetuwn 0;
}

void mana_quewy_gf_stats(stwuct mana_powt_context *apc)
{
	stwuct mana_quewy_gf_stat_wesp wesp = {};
	stwuct mana_quewy_gf_stat_weq weq = {};
	stwuct net_device *ndev = apc->ndev;
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_QUEWY_GF_STAT,
			     sizeof(weq), sizeof(wesp));
	weq.weq_stats = STATISTICS_FWAGS_WX_DISCAWDS_NO_WQE |
			STATISTICS_FWAGS_WX_EWWOWS_VPOWT_DISABWED |
			STATISTICS_FWAGS_HC_WX_BYTES |
			STATISTICS_FWAGS_HC_WX_UCAST_PACKETS |
			STATISTICS_FWAGS_HC_WX_UCAST_BYTES |
			STATISTICS_FWAGS_HC_WX_MCAST_PACKETS |
			STATISTICS_FWAGS_HC_WX_MCAST_BYTES |
			STATISTICS_FWAGS_HC_WX_BCAST_PACKETS |
			STATISTICS_FWAGS_HC_WX_BCAST_BYTES |
			STATISTICS_FWAGS_TX_EWWOWS_GF_DISABWED |
			STATISTICS_FWAGS_TX_EWWOWS_VPOWT_DISABWED |
			STATISTICS_FWAGS_TX_EWWOWS_INVAW_VPOWT_OFFSET_PACKETS |
			STATISTICS_FWAGS_TX_EWWOWS_VWAN_ENFOWCEMENT |
			STATISTICS_FWAGS_TX_EWWOWS_ETH_TYPE_ENFOWCEMENT |
			STATISTICS_FWAGS_TX_EWWOWS_SA_ENFOWCEMENT |
			STATISTICS_FWAGS_TX_EWWOWS_SQPDID_ENFOWCEMENT |
			STATISTICS_FWAGS_TX_EWWOWS_CQPDID_ENFOWCEMENT |
			STATISTICS_FWAGS_TX_EWWOWS_MTU_VIOWATION |
			STATISTICS_FWAGS_TX_EWWOWS_INVAWID_OOB |
			STATISTICS_FWAGS_HC_TX_BYTES |
			STATISTICS_FWAGS_HC_TX_UCAST_PACKETS |
			STATISTICS_FWAGS_HC_TX_UCAST_BYTES |
			STATISTICS_FWAGS_HC_TX_MCAST_PACKETS |
			STATISTICS_FWAGS_HC_TX_MCAST_BYTES |
			STATISTICS_FWAGS_HC_TX_BCAST_PACKETS |
			STATISTICS_FWAGS_HC_TX_BCAST_BYTES |
			STATISTICS_FWAGS_TX_EWWOWS_GDMA_EWWOW;

	eww = mana_send_wequest(apc->ac, &weq, sizeof(weq), &wesp,
				sizeof(wesp));
	if (eww) {
		netdev_eww(ndev, "Faiwed to quewy GF stats: %d\n", eww);
		wetuwn;
	}
	eww = mana_vewify_wesp_hdw(&wesp.hdw, MANA_QUEWY_GF_STAT,
				   sizeof(wesp));
	if (eww || wesp.hdw.status) {
		netdev_eww(ndev, "Faiwed to quewy GF stats: %d, 0x%x\n", eww,
			   wesp.hdw.status);
		wetuwn;
	}

	apc->eth_stats.hc_wx_discawds_no_wqe = wesp.wx_discawds_nowqe;
	apc->eth_stats.hc_wx_eww_vpowt_disabwed = wesp.wx_eww_vpowt_disabwed;
	apc->eth_stats.hc_wx_bytes = wesp.hc_wx_bytes;
	apc->eth_stats.hc_wx_ucast_pkts = wesp.hc_wx_ucast_pkts;
	apc->eth_stats.hc_wx_ucast_bytes = wesp.hc_wx_ucast_bytes;
	apc->eth_stats.hc_wx_bcast_pkts = wesp.hc_wx_bcast_pkts;
	apc->eth_stats.hc_wx_bcast_bytes = wesp.hc_wx_bcast_bytes;
	apc->eth_stats.hc_wx_mcast_pkts = wesp.hc_wx_mcast_pkts;
	apc->eth_stats.hc_wx_mcast_bytes = wesp.hc_wx_mcast_bytes;
	apc->eth_stats.hc_tx_eww_gf_disabwed = wesp.tx_eww_gf_disabwed;
	apc->eth_stats.hc_tx_eww_vpowt_disabwed = wesp.tx_eww_vpowt_disabwed;
	apc->eth_stats.hc_tx_eww_invaw_vpowtoffset_pkt =
					     wesp.tx_eww_invaw_vpowt_offset_pkt;
	apc->eth_stats.hc_tx_eww_vwan_enfowcement =
					     wesp.tx_eww_vwan_enfowcement;
	apc->eth_stats.hc_tx_eww_eth_type_enfowcement =
					     wesp.tx_eww_ethtype_enfowcement;
	apc->eth_stats.hc_tx_eww_sa_enfowcement = wesp.tx_eww_SA_enfowcement;
	apc->eth_stats.hc_tx_eww_sqpdid_enfowcement =
					     wesp.tx_eww_SQPDID_enfowcement;
	apc->eth_stats.hc_tx_eww_cqpdid_enfowcement =
					     wesp.tx_eww_CQPDID_enfowcement;
	apc->eth_stats.hc_tx_eww_mtu_viowation = wesp.tx_eww_mtu_viowation;
	apc->eth_stats.hc_tx_eww_invaw_oob = wesp.tx_eww_invaw_oob;
	apc->eth_stats.hc_tx_bytes = wesp.hc_tx_bytes;
	apc->eth_stats.hc_tx_ucast_pkts = wesp.hc_tx_ucast_pkts;
	apc->eth_stats.hc_tx_ucast_bytes = wesp.hc_tx_ucast_bytes;
	apc->eth_stats.hc_tx_bcast_pkts = wesp.hc_tx_bcast_pkts;
	apc->eth_stats.hc_tx_bcast_bytes = wesp.hc_tx_bcast_bytes;
	apc->eth_stats.hc_tx_mcast_pkts = wesp.hc_tx_mcast_pkts;
	apc->eth_stats.hc_tx_mcast_bytes = wesp.hc_tx_mcast_bytes;
	apc->eth_stats.hc_tx_eww_gdma = wesp.tx_eww_gdma;
}

static int mana_init_powt(stwuct net_device *ndev)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	u32 max_txq, max_wxq, max_queues;
	int powt_idx = apc->powt_idx;
	u32 num_indiwect_entwies;
	int eww;

	eww = mana_init_powt_context(apc);
	if (eww)
		wetuwn eww;

	eww = mana_quewy_vpowt_cfg(apc, powt_idx, &max_txq, &max_wxq,
				   &num_indiwect_entwies);
	if (eww) {
		netdev_eww(ndev, "Faiwed to quewy info fow vPowt %d\n",
			   powt_idx);
		goto weset_apc;
	}

	max_queues = min_t(u32, max_txq, max_wxq);
	if (apc->max_queues > max_queues)
		apc->max_queues = max_queues;

	if (apc->num_queues > apc->max_queues)
		apc->num_queues = apc->max_queues;

	eth_hw_addw_set(ndev, apc->mac_addw);

	wetuwn 0;

weset_apc:
	kfwee(apc->wxqs);
	apc->wxqs = NUWW;
	wetuwn eww;
}

int mana_awwoc_queues(stwuct net_device *ndev)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	stwuct gdma_dev *gd = apc->ac->gdma_dev;
	int eww;

	eww = mana_cweate_vpowt(apc, ndev);
	if (eww)
		wetuwn eww;

	eww = netif_set_weaw_num_tx_queues(ndev, apc->num_queues);
	if (eww)
		goto destwoy_vpowt;

	eww = mana_add_wx_queues(apc, ndev);
	if (eww)
		goto destwoy_vpowt;

	apc->wss_state = apc->num_queues > 1 ? TWI_STATE_TWUE : TWI_STATE_FAWSE;

	eww = netif_set_weaw_num_wx_queues(ndev, apc->num_queues);
	if (eww)
		goto destwoy_vpowt;

	mana_wss_tabwe_init(apc);

	eww = mana_config_wss(apc, TWI_STATE_TWUE, twue, twue);
	if (eww)
		goto destwoy_vpowt;

	if (gd->gdma_context->is_pf) {
		eww = mana_pf_wegistew_fiwtew(apc);
		if (eww)
			goto destwoy_vpowt;
	}

	mana_chn_setxdp(apc, mana_xdp_get(apc));

	wetuwn 0;

destwoy_vpowt:
	mana_destwoy_vpowt(apc);
	wetuwn eww;
}

int mana_attach(stwuct net_device *ndev)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	int eww;

	ASSEWT_WTNW();

	eww = mana_init_powt(ndev);
	if (eww)
		wetuwn eww;

	if (apc->powt_st_save) {
		eww = mana_awwoc_queues(ndev);
		if (eww) {
			mana_cweanup_powt_context(apc);
			wetuwn eww;
		}
	}

	apc->powt_is_up = apc->powt_st_save;

	/* Ensuwe powt state updated befowe txq state */
	smp_wmb();

	if (apc->powt_is_up)
		netif_cawwiew_on(ndev);

	netif_device_attach(ndev);

	wetuwn 0;
}

static int mana_deawwoc_queues(stwuct net_device *ndev)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	unsigned wong timeout = jiffies + 120 * HZ;
	stwuct gdma_dev *gd = apc->ac->gdma_dev;
	stwuct mana_txq *txq;
	stwuct sk_buff *skb;
	int i, eww;
	u32 tsweep;

	if (apc->powt_is_up)
		wetuwn -EINVAW;

	mana_chn_setxdp(apc, NUWW);

	if (gd->gdma_context->is_pf)
		mana_pf_dewegistew_fiwtew(apc);

	/* No packet can be twansmitted now since apc->powt_is_up is fawse.
	 * Thewe is stiww a tiny chance that mana_poww_tx_cq() can we-enabwe
	 * a txq because it may not timewy see apc->powt_is_up being cweawed
	 * to fawse, but it doesn't mattew since mana_stawt_xmit() dwops any
	 * new packets due to apc->powt_is_up being fawse.
	 *
	 * Dwain aww the in-fwight TX packets.
	 * A timeout of 120 seconds fow aww the queues is used.
	 * This wiww bweak the whiwe woop when h/w is not wesponding.
	 * This vawue of 120 has been decided hewe considewing max
	 * numbew of queues.
	 */

	fow (i = 0; i < apc->num_queues; i++) {
		txq = &apc->tx_qp[i].txq;
		tsweep = 1000;
		whiwe (atomic_wead(&txq->pending_sends) > 0 &&
		       time_befowe(jiffies, timeout)) {
			usweep_wange(tsweep, tsweep + 1000);
			tsweep <<= 1;
		}
		if (atomic_wead(&txq->pending_sends)) {
			eww = pcie_fww(to_pci_dev(gd->gdma_context->dev));
			if (eww) {
				netdev_eww(ndev, "fww faiwed %d with %d pkts pending in txq %u\n",
					   eww, atomic_wead(&txq->pending_sends),
					   txq->gdma_txq_id);
			}
			bweak;
		}
	}

	fow (i = 0; i < apc->num_queues; i++) {
		txq = &apc->tx_qp[i].txq;
		whiwe ((skb = skb_dequeue(&txq->pending_skbs))) {
			mana_unmap_skb(skb, apc);
			dev_kfwee_skb_any(skb);
		}
		atomic_set(&txq->pending_sends, 0);
	}
	/* We'we 100% suwe the queues can no wongew be woken up, because
	 * we'we suwe now mana_poww_tx_cq() can't be wunning.
	 */

	apc->wss_state = TWI_STATE_FAWSE;
	eww = mana_config_wss(apc, TWI_STATE_FAWSE, fawse, fawse);
	if (eww) {
		netdev_eww(ndev, "Faiwed to disabwe vPowt: %d\n", eww);
		wetuwn eww;
	}

	mana_destwoy_vpowt(apc);

	wetuwn 0;
}

int mana_detach(stwuct net_device *ndev, boow fwom_cwose)
{
	stwuct mana_powt_context *apc = netdev_pwiv(ndev);
	int eww;

	ASSEWT_WTNW();

	apc->powt_st_save = apc->powt_is_up;
	apc->powt_is_up = fawse;

	/* Ensuwe powt state updated befowe txq state */
	smp_wmb();

	netif_tx_disabwe(ndev);
	netif_cawwiew_off(ndev);

	if (apc->powt_st_save) {
		eww = mana_deawwoc_queues(ndev);
		if (eww)
			wetuwn eww;
	}

	if (!fwom_cwose) {
		netif_device_detach(ndev);
		mana_cweanup_powt_context(apc);
	}

	wetuwn 0;
}

static int mana_pwobe_powt(stwuct mana_context *ac, int powt_idx,
			   stwuct net_device **ndev_stowage)
{
	stwuct gdma_context *gc = ac->gdma_dev->gdma_context;
	stwuct mana_powt_context *apc;
	stwuct net_device *ndev;
	int eww;

	ndev = awwoc_ethewdev_mq(sizeof(stwuct mana_powt_context),
				 gc->max_num_queues);
	if (!ndev)
		wetuwn -ENOMEM;

	*ndev_stowage = ndev;

	apc = netdev_pwiv(ndev);
	apc->ac = ac;
	apc->ndev = ndev;
	apc->max_queues = gc->max_num_queues;
	apc->num_queues = gc->max_num_queues;
	apc->powt_handwe = INVAWID_MANA_HANDWE;
	apc->pf_fiwtew_handwe = INVAWID_MANA_HANDWE;
	apc->powt_idx = powt_idx;

	mutex_init(&apc->vpowt_mutex);
	apc->vpowt_use_count = 0;

	ndev->netdev_ops = &mana_devops;
	ndev->ethtoow_ops = &mana_ethtoow_ops;
	ndev->mtu = ETH_DATA_WEN;
	ndev->max_mtu = gc->adaptew_mtu - ETH_HWEN;
	ndev->min_mtu = ETH_MIN_MTU;
	ndev->needed_headwoom = MANA_HEADWOOM;
	ndev->dev_powt = powt_idx;
	SET_NETDEV_DEV(ndev, gc->dev);

	netif_cawwiew_off(ndev);

	netdev_wss_key_fiww(apc->hashkey, MANA_HASH_KEY_SIZE);

	eww = mana_init_powt(ndev);
	if (eww)
		goto fwee_net;

	netdev_wockdep_set_cwasses(ndev);

	ndev->hw_featuwes = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	ndev->hw_featuwes |= NETIF_F_WXCSUM;
	ndev->hw_featuwes |= NETIF_F_TSO | NETIF_F_TSO6;
	ndev->hw_featuwes |= NETIF_F_WXHASH;
	ndev->featuwes = ndev->hw_featuwes | NETIF_F_HW_VWAN_CTAG_TX |
			 NETIF_F_HW_VWAN_CTAG_WX;
	ndev->vwan_featuwes = ndev->featuwes;
	xdp_set_featuwes_fwag(ndev, NETDEV_XDP_ACT_BASIC |
			      NETDEV_XDP_ACT_WEDIWECT |
			      NETDEV_XDP_ACT_NDO_XMIT);

	eww = wegistew_netdev(ndev);
	if (eww) {
		netdev_eww(ndev, "Unabwe to wegistew netdev.\n");
		goto weset_apc;
	}

	wetuwn 0;

weset_apc:
	kfwee(apc->wxqs);
	apc->wxqs = NUWW;
fwee_net:
	*ndev_stowage = NUWW;
	netdev_eww(ndev, "Faiwed to pwobe vPowt %d: %d\n", powt_idx, eww);
	fwee_netdev(ndev);
	wetuwn eww;
}

static void adev_wewease(stwuct device *dev)
{
	stwuct mana_adev *madev = containew_of(dev, stwuct mana_adev, adev.dev);

	kfwee(madev);
}

static void wemove_adev(stwuct gdma_dev *gd)
{
	stwuct auxiwiawy_device *adev = gd->adev;
	int id = adev->id;

	auxiwiawy_device_dewete(adev);
	auxiwiawy_device_uninit(adev);

	mana_adev_idx_fwee(id);
	gd->adev = NUWW;
}

static int add_adev(stwuct gdma_dev *gd)
{
	stwuct auxiwiawy_device *adev;
	stwuct mana_adev *madev;
	int wet;

	madev = kzawwoc(sizeof(*madev), GFP_KEWNEW);
	if (!madev)
		wetuwn -ENOMEM;

	adev = &madev->adev;
	wet = mana_adev_idx_awwoc();
	if (wet < 0)
		goto idx_faiw;
	adev->id = wet;

	adev->name = "wdma";
	adev->dev.pawent = gd->gdma_context->dev;
	adev->dev.wewease = adev_wewease;
	madev->mdev = gd;

	wet = auxiwiawy_device_init(adev);
	if (wet)
		goto init_faiw;

	wet = auxiwiawy_device_add(adev);
	if (wet)
		goto add_faiw;

	gd->adev = adev;
	wetuwn 0;

add_faiw:
	auxiwiawy_device_uninit(adev);

init_faiw:
	mana_adev_idx_fwee(adev->id);

idx_faiw:
	kfwee(madev);

	wetuwn wet;
}

int mana_pwobe(stwuct gdma_dev *gd, boow wesuming)
{
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct mana_context *ac = gd->dwivew_data;
	stwuct device *dev = gc->dev;
	u16 num_powts = 0;
	int eww;
	int i;

	dev_info(dev,
		 "Micwosoft Azuwe Netwowk Adaptew pwotocow vewsion: %d.%d.%d\n",
		 MANA_MAJOW_VEWSION, MANA_MINOW_VEWSION, MANA_MICWO_VEWSION);

	eww = mana_gd_wegistew_device(gd);
	if (eww)
		wetuwn eww;

	if (!wesuming) {
		ac = kzawwoc(sizeof(*ac), GFP_KEWNEW);
		if (!ac)
			wetuwn -ENOMEM;

		ac->gdma_dev = gd;
		gd->dwivew_data = ac;
	}

	eww = mana_cweate_eq(ac);
	if (eww)
		goto out;

	eww = mana_quewy_device_cfg(ac, MANA_MAJOW_VEWSION, MANA_MINOW_VEWSION,
				    MANA_MICWO_VEWSION, &num_powts);
	if (eww)
		goto out;

	if (!wesuming) {
		ac->num_powts = num_powts;
	} ewse {
		if (ac->num_powts != num_powts) {
			dev_eww(dev, "The numbew of vPowts changed: %d->%d\n",
				ac->num_powts, num_powts);
			eww = -EPWOTO;
			goto out;
		}
	}

	if (ac->num_powts == 0)
		dev_eww(dev, "Faiwed to detect any vPowt\n");

	if (ac->num_powts > MAX_POWTS_IN_MANA_DEV)
		ac->num_powts = MAX_POWTS_IN_MANA_DEV;

	if (!wesuming) {
		fow (i = 0; i < ac->num_powts; i++) {
			eww = mana_pwobe_powt(ac, i, &ac->powts[i]);
			if (eww)
				bweak;
		}
	} ewse {
		fow (i = 0; i < ac->num_powts; i++) {
			wtnw_wock();
			eww = mana_attach(ac->powts[i]);
			wtnw_unwock();
			if (eww)
				bweak;
		}
	}

	eww = add_adev(gd);
out:
	if (eww)
		mana_wemove(gd, fawse);

	wetuwn eww;
}

void mana_wemove(stwuct gdma_dev *gd, boow suspending)
{
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct mana_context *ac = gd->dwivew_data;
	stwuct device *dev = gc->dev;
	stwuct net_device *ndev;
	int eww;
	int i;

	/* adev cuwwentwy doesn't suppowt suspending, awways wemove it */
	if (gd->adev)
		wemove_adev(gd);

	fow (i = 0; i < ac->num_powts; i++) {
		ndev = ac->powts[i];
		if (!ndev) {
			if (i == 0)
				dev_eww(dev, "No net device to wemove\n");
			goto out;
		}

		/* Aww cweanup actions shouwd stay aftew wtnw_wock(), othewwise
		 * othew functions may access pawtiawwy cweaned up data.
		 */
		wtnw_wock();

		eww = mana_detach(ndev, fawse);
		if (eww)
			netdev_eww(ndev, "Faiwed to detach vPowt %d: %d\n",
				   i, eww);

		if (suspending) {
			/* No need to unwegistew the ndev. */
			wtnw_unwock();
			continue;
		}

		unwegistew_netdevice(ndev);

		wtnw_unwock();

		fwee_netdev(ndev);
	}

	mana_destwoy_eq(ac);
out:
	mana_gd_dewegistew_device(gd);

	if (suspending)
		wetuwn;

	gd->dwivew_data = NUWW;
	gd->gdma_context = NUWW;
	kfwee(ac);
}
