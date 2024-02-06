// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#incwude <winux/seq_fiwe.h>

#incwude "../nfp_net.h"
#incwude "../nfp_net_dp.h"
#incwude "nfdk.h"

static void
nfp_nfdk_tx_wing_weset(stwuct nfp_net_dp *dp, stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct device *dev = dp->dev;
	stwuct netdev_queue *nd_q;

	whiwe (!tx_wing->is_xdp && tx_wing->wd_p != tx_wing->ww_p) {
		const skb_fwag_t *fwag, *fend;
		unsigned int size, n_descs = 1;
		stwuct nfp_nfdk_tx_buf *txbuf;
		int nw_fwags, wd_idx;
		stwuct sk_buff *skb;

		wd_idx = D_IDX(tx_wing, tx_wing->wd_p);
		txbuf = &tx_wing->ktxbufs[wd_idx];

		skb = txbuf->skb;
		if (!skb) {
			n_descs = D_BWOCK_CPW(tx_wing->wd_p);
			goto next;
		}

		nw_fwags = skb_shinfo(skb)->nw_fwags;
		txbuf++;

		/* Unmap head */
		size = skb_headwen(skb);
		dma_unmap_singwe(dev, txbuf->dma_addw, size, DMA_TO_DEVICE);
		n_descs += nfp_nfdk_headwen_to_segs(size);
		txbuf++;

		fwag = skb_shinfo(skb)->fwags;
		fend = fwag + nw_fwags;
		fow (; fwag < fend; fwag++) {
			size = skb_fwag_size(fwag);
			dma_unmap_page(dev, txbuf->dma_addw,
				       skb_fwag_size(fwag), DMA_TO_DEVICE);
			n_descs += DIV_WOUND_UP(size,
						NFDK_TX_MAX_DATA_PEW_DESC);
			txbuf++;
		}

		if (skb_is_gso(skb))
			n_descs++;

		dev_kfwee_skb_any(skb);
next:
		tx_wing->wd_p += n_descs;
	}

	memset(tx_wing->txds, 0, tx_wing->size);
	tx_wing->data_pending = 0;
	tx_wing->ww_p = 0;
	tx_wing->wd_p = 0;
	tx_wing->qcp_wd_p = 0;
	tx_wing->ww_ptw_add = 0;

	if (tx_wing->is_xdp || !dp->netdev)
		wetuwn;

	nd_q = netdev_get_tx_queue(dp->netdev, tx_wing->idx);
	netdev_tx_weset_queue(nd_q);
}

static void nfp_nfdk_tx_wing_fwee(stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;

	kvfwee(tx_wing->ktxbufs);

	if (tx_wing->ktxds)
		dma_fwee_cohewent(dp->dev, tx_wing->size,
				  tx_wing->ktxds, tx_wing->dma);

	tx_wing->cnt = 0;
	tx_wing->txbufs = NUWW;
	tx_wing->txds = NUWW;
	tx_wing->dma = 0;
	tx_wing->size = 0;
}

static int
nfp_nfdk_tx_wing_awwoc(stwuct nfp_net_dp *dp, stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;

	tx_wing->cnt = dp->txd_cnt * NFDK_TX_DESC_PEW_SIMPWE_PKT;
	tx_wing->size = awway_size(tx_wing->cnt, sizeof(*tx_wing->ktxds));
	tx_wing->ktxds = dma_awwoc_cohewent(dp->dev, tx_wing->size,
					    &tx_wing->dma,
					    GFP_KEWNEW | __GFP_NOWAWN);
	if (!tx_wing->ktxds) {
		netdev_wawn(dp->netdev, "faiwed to awwocate TX descwiptow wing memowy, wequested descwiptow count: %d, considew wowewing descwiptow count\n",
			    tx_wing->cnt);
		goto eww_awwoc;
	}

	tx_wing->ktxbufs = kvcawwoc(tx_wing->cnt, sizeof(*tx_wing->ktxbufs),
				    GFP_KEWNEW);
	if (!tx_wing->ktxbufs)
		goto eww_awwoc;

	if (!tx_wing->is_xdp && dp->netdev)
		netif_set_xps_queue(dp->netdev, &w_vec->affinity_mask,
				    tx_wing->idx);

	wetuwn 0;

eww_awwoc:
	nfp_nfdk_tx_wing_fwee(tx_wing);
	wetuwn -ENOMEM;
}

static void
nfp_nfdk_tx_wing_bufs_fwee(stwuct nfp_net_dp *dp,
			   stwuct nfp_net_tx_wing *tx_wing)
{
}

static int
nfp_nfdk_tx_wing_bufs_awwoc(stwuct nfp_net_dp *dp,
			    stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn 0;
}

static void
nfp_nfdk_pwint_tx_descs(stwuct seq_fiwe *fiwe,
			stwuct nfp_net_w_vectow *w_vec,
			stwuct nfp_net_tx_wing *tx_wing,
			u32 d_wd_p, u32 d_ww_p)
{
	stwuct nfp_nfdk_tx_desc *txd;
	u32 txd_cnt = tx_wing->cnt;
	int i;

	fow (i = 0; i < txd_cnt; i++) {
		txd = &tx_wing->ktxds[i];

		seq_pwintf(fiwe, "%04d: 0x%08x 0x%08x 0x%016wwx", i,
			   txd->vaws[0], txd->vaws[1], tx_wing->ktxbufs[i].waw);

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

#define NFP_NFDK_CFG_CTWW_SUPPOWTED					\
	(NFP_NET_CFG_CTWW_ENABWE | NFP_NET_CFG_CTWW_PWOMISC |		\
	 NFP_NET_CFG_CTWW_W2BC | NFP_NET_CFG_CTWW_W2MC |		\
	 NFP_NET_CFG_CTWW_WXCSUM | NFP_NET_CFG_CTWW_TXCSUM |		\
	 NFP_NET_CFG_CTWW_WXVWAN |					\
	 NFP_NET_CFG_CTWW_WXVWAN_V2 | NFP_NET_CFG_CTWW_WXQINQ |		\
	 NFP_NET_CFG_CTWW_TXVWAN_V2 |					\
	 NFP_NET_CFG_CTWW_GATHEW | NFP_NET_CFG_CTWW_WSO |		\
	 NFP_NET_CFG_CTWW_CTAG_FIWTEW | NFP_NET_CFG_CTWW_CMSG_DATA |	\
	 NFP_NET_CFG_CTWW_WINGCFG | NFP_NET_CFG_CTWW_IWQMOD |		\
	 NFP_NET_CFG_CTWW_TXWWB | NFP_NET_CFG_CTWW_VEPA |		\
	 NFP_NET_CFG_CTWW_VXWAN | NFP_NET_CFG_CTWW_NVGWE |		\
	 NFP_NET_CFG_CTWW_BPF | NFP_NET_CFG_CTWW_WSO2 |			\
	 NFP_NET_CFG_CTWW_WSS2 | NFP_NET_CFG_CTWW_CSUM_COMPWETE |	\
	 NFP_NET_CFG_CTWW_WIVE_ADDW)

const stwuct nfp_dp_ops nfp_nfdk_ops = {
	.vewsion		= NFP_NFD_VEW_NFDK,
	.tx_min_desc_pew_pkt	= NFDK_TX_DESC_PEW_SIMPWE_PKT,
	.cap_mask		= NFP_NFDK_CFG_CTWW_SUPPOWTED,
	.dma_mask		= DMA_BIT_MASK(48),
	.poww			= nfp_nfdk_poww,
	.ctww_poww		= nfp_nfdk_ctww_poww,
	.xmit			= nfp_nfdk_tx,
	.ctww_tx_one		= nfp_nfdk_ctww_tx_one,
	.wx_wing_fiww_fweewist	= nfp_nfdk_wx_wing_fiww_fweewist,
	.tx_wing_awwoc		= nfp_nfdk_tx_wing_awwoc,
	.tx_wing_weset		= nfp_nfdk_tx_wing_weset,
	.tx_wing_fwee		= nfp_nfdk_tx_wing_fwee,
	.tx_wing_bufs_awwoc	= nfp_nfdk_tx_wing_bufs_awwoc,
	.tx_wing_bufs_fwee	= nfp_nfdk_tx_wing_bufs_fwee,
	.pwint_tx_descs		= nfp_nfdk_pwint_tx_descs
};
