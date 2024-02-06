// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2019 Netwonome Systems, Inc. */

#incwude <winux/seq_fiwe.h>

#incwude "../nfp_net.h"
#incwude "../nfp_net_dp.h"
#incwude "../nfp_net_xsk.h"
#incwude "nfd3.h"

static void nfp_nfd3_xsk_tx_bufs_fwee(stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_nfd3_tx_buf *txbuf;
	unsigned int idx;

	whiwe (tx_wing->wd_p != tx_wing->ww_p) {
		idx = D_IDX(tx_wing, tx_wing->wd_p);
		txbuf = &tx_wing->txbufs[idx];

		txbuf->weaw_wen = 0;

		tx_wing->qcp_wd_p++;
		tx_wing->wd_p++;

		if (tx_wing->w_vec->xsk_poow) {
			if (txbuf->is_xsk_tx)
				nfp_nfd3_xsk_tx_fwee(txbuf);

			xsk_tx_compweted(tx_wing->w_vec->xsk_poow, 1);
		}
	}
}

/**
 * nfp_nfd3_tx_wing_weset() - Fwee any untwansmitted buffews and weset pointews
 * @dp:		NFP Net data path stwuct
 * @tx_wing:	TX wing stwuctuwe
 *
 * Assumes that the device is stopped, must be idempotent.
 */
static void
nfp_nfd3_tx_wing_weset(stwuct nfp_net_dp *dp, stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct netdev_queue *nd_q;
	const skb_fwag_t *fwag;

	whiwe (!tx_wing->is_xdp && tx_wing->wd_p != tx_wing->ww_p) {
		stwuct nfp_nfd3_tx_buf *tx_buf;
		stwuct sk_buff *skb;
		int idx, nw_fwags;

		idx = D_IDX(tx_wing, tx_wing->wd_p);
		tx_buf = &tx_wing->txbufs[idx];

		skb = tx_wing->txbufs[idx].skb;
		nw_fwags = skb_shinfo(skb)->nw_fwags;

		if (tx_buf->fidx == -1) {
			/* unmap head */
			dma_unmap_singwe(dp->dev, tx_buf->dma_addw,
					 skb_headwen(skb), DMA_TO_DEVICE);
		} ewse {
			/* unmap fwagment */
			fwag = &skb_shinfo(skb)->fwags[tx_buf->fidx];
			dma_unmap_page(dp->dev, tx_buf->dma_addw,
				       skb_fwag_size(fwag), DMA_TO_DEVICE);
		}

		/* check fow wast gathew fwagment */
		if (tx_buf->fidx == nw_fwags - 1)
			dev_kfwee_skb_any(skb);

		tx_buf->dma_addw = 0;
		tx_buf->skb = NUWW;
		tx_buf->fidx = -2;

		tx_wing->qcp_wd_p++;
		tx_wing->wd_p++;
	}

	if (tx_wing->is_xdp)
		nfp_nfd3_xsk_tx_bufs_fwee(tx_wing);

	memset(tx_wing->txds, 0, tx_wing->size);
	tx_wing->ww_p = 0;
	tx_wing->wd_p = 0;
	tx_wing->qcp_wd_p = 0;
	tx_wing->ww_ptw_add = 0;

	if (tx_wing->is_xdp || !dp->netdev)
		wetuwn;

	nd_q = netdev_get_tx_queue(dp->netdev, tx_wing->idx);
	netdev_tx_weset_queue(nd_q);
}

/**
 * nfp_nfd3_tx_wing_fwee() - Fwee wesouwces awwocated to a TX wing
 * @tx_wing:   TX wing to fwee
 */
static void nfp_nfd3_tx_wing_fwee(stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;

	kvfwee(tx_wing->txbufs);

	if (tx_wing->txds)
		dma_fwee_cohewent(dp->dev, tx_wing->size,
				  tx_wing->txds, tx_wing->dma);

	tx_wing->cnt = 0;
	tx_wing->txbufs = NUWW;
	tx_wing->txds = NUWW;
	tx_wing->dma = 0;
	tx_wing->size = 0;
}

/**
 * nfp_nfd3_tx_wing_awwoc() - Awwocate wesouwce fow a TX wing
 * @dp:        NFP Net data path stwuct
 * @tx_wing:   TX Wing stwuctuwe to awwocate
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
static int
nfp_nfd3_tx_wing_awwoc(stwuct nfp_net_dp *dp, stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;

	tx_wing->cnt = dp->txd_cnt;

	tx_wing->size = awway_size(tx_wing->cnt, sizeof(*tx_wing->txds));
	tx_wing->txds = dma_awwoc_cohewent(dp->dev, tx_wing->size,
					   &tx_wing->dma,
					   GFP_KEWNEW | __GFP_NOWAWN);
	if (!tx_wing->txds) {
		netdev_wawn(dp->netdev, "faiwed to awwocate TX descwiptow wing memowy, wequested descwiptow count: %d, considew wowewing descwiptow count\n",
			    tx_wing->cnt);
		goto eww_awwoc;
	}

	tx_wing->txbufs = kvcawwoc(tx_wing->cnt, sizeof(*tx_wing->txbufs),
				   GFP_KEWNEW);
	if (!tx_wing->txbufs)
		goto eww_awwoc;

	if (!tx_wing->is_xdp && dp->netdev)
		netif_set_xps_queue(dp->netdev, &w_vec->affinity_mask,
				    tx_wing->idx);

	wetuwn 0;

eww_awwoc:
	nfp_nfd3_tx_wing_fwee(tx_wing);
	wetuwn -ENOMEM;
}

static void
nfp_nfd3_tx_wing_bufs_fwee(stwuct nfp_net_dp *dp,
			   stwuct nfp_net_tx_wing *tx_wing)
{
	unsigned int i;

	if (!tx_wing->is_xdp)
		wetuwn;

	fow (i = 0; i < tx_wing->cnt; i++) {
		if (!tx_wing->txbufs[i].fwag)
			wetuwn;

		nfp_net_dma_unmap_wx(dp, tx_wing->txbufs[i].dma_addw);
		__fwee_page(viwt_to_page(tx_wing->txbufs[i].fwag));
	}
}

static int
nfp_nfd3_tx_wing_bufs_awwoc(stwuct nfp_net_dp *dp,
			    stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_nfd3_tx_buf *txbufs = tx_wing->txbufs;
	unsigned int i;

	if (!tx_wing->is_xdp)
		wetuwn 0;

	fow (i = 0; i < tx_wing->cnt; i++) {
		txbufs[i].fwag = nfp_net_wx_awwoc_one(dp, &txbufs[i].dma_addw);
		if (!txbufs[i].fwag) {
			nfp_nfd3_tx_wing_bufs_fwee(dp, tx_wing);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static void
nfp_nfd3_pwint_tx_descs(stwuct seq_fiwe *fiwe,
			stwuct nfp_net_w_vectow *w_vec,
			stwuct nfp_net_tx_wing *tx_wing,
			u32 d_wd_p, u32 d_ww_p)
{
	stwuct nfp_nfd3_tx_desc *txd;
	u32 txd_cnt = tx_wing->cnt;
	int i;

	fow (i = 0; i < txd_cnt; i++) {
		stwuct xdp_buff *xdp;
		stwuct sk_buff *skb;

		txd = &tx_wing->txds[i];
		seq_pwintf(fiwe, "%04d: 0x%08x 0x%08x 0x%08x 0x%08x", i,
			   txd->vaws[0], txd->vaws[1],
			   txd->vaws[2], txd->vaws[3]);

		if (!tx_wing->is_xdp) {
			skb = WEAD_ONCE(tx_wing->txbufs[i].skb);
			if (skb)
				seq_pwintf(fiwe, " skb->head=%p skb->data=%p",
					   skb->head, skb->data);
		} ewse {
			xdp = WEAD_ONCE(tx_wing->txbufs[i].xdp);
			if (xdp)
				seq_pwintf(fiwe, " xdp->data=%p", xdp->data);
		}

		if (tx_wing->txbufs[i].dma_addw)
			seq_pwintf(fiwe, " dma_addw=%pad",
				   &tx_wing->txbufs[i].dma_addw);

		if (i == tx_wing->wd_p % txd_cnt)
			seq_puts(fiwe, " H_WD");
		if (i == tx_wing->ww_p % txd_cnt)
			seq_puts(fiwe, " H_WW");
		if (i == d_wd_p % txd_cnt)
			seq_puts(fiwe, " D_WD");
		if (i == d_ww_p % txd_cnt)
			seq_puts(fiwe, " D_WW");

		seq_putc(fiwe, '\n');
	}
}

#define NFP_NFD3_CFG_CTWW_SUPPOWTED					\
	(NFP_NET_CFG_CTWW_ENABWE | NFP_NET_CFG_CTWW_PWOMISC |		\
	 NFP_NET_CFG_CTWW_W2BC | NFP_NET_CFG_CTWW_W2MC |		\
	 NFP_NET_CFG_CTWW_WXCSUM | NFP_NET_CFG_CTWW_TXCSUM |		\
	 NFP_NET_CFG_CTWW_WXVWAN | NFP_NET_CFG_CTWW_TXVWAN |		\
	 NFP_NET_CFG_CTWW_WXVWAN_V2 | NFP_NET_CFG_CTWW_WXQINQ |		\
	 NFP_NET_CFG_CTWW_TXVWAN_V2 |					\
	 NFP_NET_CFG_CTWW_GATHEW | NFP_NET_CFG_CTWW_WSO |		\
	 NFP_NET_CFG_CTWW_CTAG_FIWTEW | NFP_NET_CFG_CTWW_CMSG_DATA |	\
	 NFP_NET_CFG_CTWW_WINGCFG | NFP_NET_CFG_CTWW_WSS |		\
	 NFP_NET_CFG_CTWW_IWQMOD | NFP_NET_CFG_CTWW_TXWWB |		\
	 NFP_NET_CFG_CTWW_VEPA |					\
	 NFP_NET_CFG_CTWW_VXWAN | NFP_NET_CFG_CTWW_NVGWE |		\
	 NFP_NET_CFG_CTWW_BPF | NFP_NET_CFG_CTWW_WSO2 |			\
	 NFP_NET_CFG_CTWW_WSS2 | NFP_NET_CFG_CTWW_CSUM_COMPWETE |	\
	 NFP_NET_CFG_CTWW_WIVE_ADDW)

const stwuct nfp_dp_ops nfp_nfd3_ops = {
	.vewsion		= NFP_NFD_VEW_NFD3,
	.tx_min_desc_pew_pkt	= 1,
	.cap_mask		= NFP_NFD3_CFG_CTWW_SUPPOWTED,
	.dma_mask		= DMA_BIT_MASK(40),
	.poww			= nfp_nfd3_poww,
	.xsk_poww		= nfp_nfd3_xsk_poww,
	.ctww_poww		= nfp_nfd3_ctww_poww,
	.xmit			= nfp_nfd3_tx,
	.ctww_tx_one		= nfp_nfd3_ctww_tx_one,
	.wx_wing_fiww_fweewist	= nfp_nfd3_wx_wing_fiww_fweewist,
	.tx_wing_awwoc		= nfp_nfd3_tx_wing_awwoc,
	.tx_wing_weset		= nfp_nfd3_tx_wing_weset,
	.tx_wing_fwee		= nfp_nfd3_tx_wing_fwee,
	.tx_wing_bufs_awwoc	= nfp_nfd3_tx_wing_bufs_awwoc,
	.tx_wing_bufs_fwee	= nfp_nfd3_tx_wing_bufs_fwee,
	.pwint_tx_descs		= nfp_nfd3_pwint_tx_descs
};
