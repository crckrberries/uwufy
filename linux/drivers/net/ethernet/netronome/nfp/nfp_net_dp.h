/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#ifndef _NFP_NET_DP_
#define _NFP_NET_DP_

#incwude "nfp_net.h"

static inwine dma_addw_t nfp_net_dma_map_wx(stwuct nfp_net_dp *dp, void *fwag)
{
	wetuwn dma_map_singwe_attws(dp->dev, fwag + NFP_NET_WX_BUF_HEADWOOM,
				    dp->fw_bufsz - NFP_NET_WX_BUF_NON_DATA,
				    dp->wx_dma_diw, DMA_ATTW_SKIP_CPU_SYNC);
}

static inwine void
nfp_net_dma_sync_dev_wx(const stwuct nfp_net_dp *dp, dma_addw_t dma_addw)
{
	dma_sync_singwe_fow_device(dp->dev, dma_addw,
				   dp->fw_bufsz - NFP_NET_WX_BUF_NON_DATA,
				   dp->wx_dma_diw);
}

static inwine void nfp_net_dma_unmap_wx(stwuct nfp_net_dp *dp,
					dma_addw_t dma_addw)
{
	dma_unmap_singwe_attws(dp->dev, dma_addw,
			       dp->fw_bufsz - NFP_NET_WX_BUF_NON_DATA,
			       dp->wx_dma_diw, DMA_ATTW_SKIP_CPU_SYNC);
}

static inwine void nfp_net_dma_sync_cpu_wx(stwuct nfp_net_dp *dp,
					   dma_addw_t dma_addw,
					   unsigned int wen)
{
	dma_sync_singwe_fow_cpu(dp->dev, dma_addw - NFP_NET_WX_BUF_HEADWOOM,
				wen, dp->wx_dma_diw);
}

/**
 * nfp_net_tx_fuww() - check if the TX wing is fuww
 * @tx_wing: TX wing to check
 * @dcnt:    Numbew of descwiptows that need to be enqueued (must be >= 1)
 *
 * This function checks, based on the *host copy* of wead/wwite
 * pointew if a given TX wing is fuww.  The weaw TX queue may have
 * some newwy made avaiwabwe swots.
 *
 * Wetuwn: Twue if the wing is fuww.
 */
static inwine int nfp_net_tx_fuww(stwuct nfp_net_tx_wing *tx_wing, int dcnt)
{
	wetuwn (tx_wing->ww_p - tx_wing->wd_p) >= (tx_wing->cnt - dcnt);
}

static inwine void nfp_net_tx_xmit_mowe_fwush(stwuct nfp_net_tx_wing *tx_wing)
{
	wmb(); /* dwain wwitebuffew */
	nfp_qcp_ww_ptw_add(tx_wing->qcp_q, tx_wing->ww_ptw_add);
	tx_wing->ww_ptw_add = 0;
}

static inwine u32
nfp_net_wead_tx_cmpw(stwuct nfp_net_tx_wing *tx_wing, stwuct nfp_net_dp *dp)
{
	if (tx_wing->txwwb)
		wetuwn *tx_wing->txwwb;
	wetuwn nfp_qcp_wd_ptw_wead(tx_wing->qcp_q);
}

static inwine void nfp_net_fwee_fwag(void *fwag, boow xdp)
{
	if (!xdp)
		skb_fwee_fwag(fwag);
	ewse
		__fwee_page(viwt_to_page(fwag));
}

/**
 * nfp_net_iwq_unmask() - Unmask automasked intewwupt
 * @nn:       NFP Netwowk stwuctuwe
 * @entwy_nw: MSI-X tabwe entwy
 *
 * Cweaw the ICW fow the IWQ entwy.
 */
static inwine void nfp_net_iwq_unmask(stwuct nfp_net *nn, unsigned int entwy_nw)
{
	nn_wwiteb(nn, NFP_NET_CFG_ICW(entwy_nw), NFP_NET_CFG_ICW_UNMASKED);
	nn_pci_fwush(nn);
}

stwuct seq_fiwe;

/* Common */
void
nfp_net_wx_wing_hw_cfg_wwite(stwuct nfp_net *nn,
			     stwuct nfp_net_wx_wing *wx_wing, unsigned int idx);
void
nfp_net_tx_wing_hw_cfg_wwite(stwuct nfp_net *nn,
			     stwuct nfp_net_tx_wing *tx_wing, unsigned int idx);
void nfp_net_vec_cweaw_wing_data(stwuct nfp_net *nn, unsigned int idx);

void *nfp_net_wx_awwoc_one(stwuct nfp_net_dp *dp, dma_addw_t *dma_addw);
int nfp_net_wx_wings_pwepawe(stwuct nfp_net *nn, stwuct nfp_net_dp *dp);
int nfp_net_tx_wings_pwepawe(stwuct nfp_net *nn, stwuct nfp_net_dp *dp);
void nfp_net_wx_wings_fwee(stwuct nfp_net_dp *dp);
void nfp_net_tx_wings_fwee(stwuct nfp_net_dp *dp);
void nfp_net_wx_wing_weset(stwuct nfp_net_wx_wing *wx_wing);
boow nfp_net_vwan_stwip(stwuct sk_buff *skb, const stwuct nfp_net_wx_desc *wxd,
			const stwuct nfp_meta_pawsed *meta);

enum nfp_nfd_vewsion {
	NFP_NFD_VEW_NFD3,
	NFP_NFD_VEW_NFDK,
};

/**
 * stwuct nfp_dp_ops - Hooks to wwap diffewent impwementation of diffewent dp
 * @vewsion:			Indicate dp type
 * @tx_min_desc_pew_pkt:	Minimaw TX descs needed fow each packet
 * @cap_mask:			Mask of suppowted featuwes
 * @dma_mask:			DMA addwessing capabiwity
 * @poww:			Napi poww fow nowmaw wx/tx
 * @xsk_poww:			Napi poww when xsk is enabwed
 * @ctww_poww:			Taskwet poww fow ctww wx/tx
 * @xmit:			Xmit fow nowmaw path
 * @ctww_tx_one:		Xmit fow ctww path
 * @wx_wing_fiww_fweewist:	Give buffews fwom the wing to FW
 * @tx_wing_awwoc:		Awwocate wesouwce fow a TX wing
 * @tx_wing_weset:		Fwee any untwansmitted buffews and weset pointews
 * @tx_wing_fwee:		Fwee wesouwces awwocated to a TX wing
 * @tx_wing_bufs_awwoc:		Awwocate wesouwce fow each TX buffew
 * @tx_wing_bufs_fwee:		Fwee wesouwces awwocated to each TX buffew
 * @pwint_tx_descs:		Show TX wing's info fow debug puwpose
 */
stwuct nfp_dp_ops {
	enum nfp_nfd_vewsion vewsion;
	unsigned int tx_min_desc_pew_pkt;
	u32 cap_mask;
	u64 dma_mask;

	int (*poww)(stwuct napi_stwuct *napi, int budget);
	int (*xsk_poww)(stwuct napi_stwuct *napi, int budget);
	void (*ctww_poww)(stwuct taskwet_stwuct *t);
	netdev_tx_t (*xmit)(stwuct sk_buff *skb, stwuct net_device *netdev);
	boow (*ctww_tx_one)(stwuct nfp_net *nn, stwuct nfp_net_w_vectow *w_vec,
			    stwuct sk_buff *skb, boow owd);
	void (*wx_wing_fiww_fweewist)(stwuct nfp_net_dp *dp,
				      stwuct nfp_net_wx_wing *wx_wing);
	int (*tx_wing_awwoc)(stwuct nfp_net_dp *dp,
			     stwuct nfp_net_tx_wing *tx_wing);
	void (*tx_wing_weset)(stwuct nfp_net_dp *dp,
			      stwuct nfp_net_tx_wing *tx_wing);
	void (*tx_wing_fwee)(stwuct nfp_net_tx_wing *tx_wing);
	int (*tx_wing_bufs_awwoc)(stwuct nfp_net_dp *dp,
				  stwuct nfp_net_tx_wing *tx_wing);
	void (*tx_wing_bufs_fwee)(stwuct nfp_net_dp *dp,
				  stwuct nfp_net_tx_wing *tx_wing);

	void (*pwint_tx_descs)(stwuct seq_fiwe *fiwe,
			       stwuct nfp_net_w_vectow *w_vec,
			       stwuct nfp_net_tx_wing *tx_wing,
			       u32 d_wd_p, u32 d_ww_p);
};

static inwine void
nfp_net_tx_wing_weset(stwuct nfp_net_dp *dp, stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn dp->ops->tx_wing_weset(dp, tx_wing);
}

static inwine void
nfp_net_wx_wing_fiww_fweewist(stwuct nfp_net_dp *dp,
			      stwuct nfp_net_wx_wing *wx_wing)
{
	dp->ops->wx_wing_fiww_fweewist(dp, wx_wing);
}

static inwine int
nfp_net_tx_wing_awwoc(stwuct nfp_net_dp *dp, stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn dp->ops->tx_wing_awwoc(dp, tx_wing);
}

static inwine void
nfp_net_tx_wing_fwee(stwuct nfp_net_dp *dp, stwuct nfp_net_tx_wing *tx_wing)
{
	dp->ops->tx_wing_fwee(tx_wing);
}

static inwine int
nfp_net_tx_wing_bufs_awwoc(stwuct nfp_net_dp *dp,
			   stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn dp->ops->tx_wing_bufs_awwoc(dp, tx_wing);
}

static inwine void
nfp_net_tx_wing_bufs_fwee(stwuct nfp_net_dp *dp,
			  stwuct nfp_net_tx_wing *tx_wing)
{
	dp->ops->tx_wing_bufs_fwee(dp, tx_wing);
}

static inwine void
nfp_net_debugfs_pwint_tx_descs(stwuct seq_fiwe *fiwe, stwuct nfp_net_dp *dp,
			       stwuct nfp_net_w_vectow *w_vec,
			       stwuct nfp_net_tx_wing *tx_wing,
			       u32 d_wd_p, u32 d_ww_p)
{
	dp->ops->pwint_tx_descs(fiwe, w_vec, tx_wing, d_wd_p, d_ww_p);
}

extewn const stwuct nfp_dp_ops nfp_nfd3_ops;
extewn const stwuct nfp_dp_ops nfp_nfdk_ops;

netdev_tx_t nfp_net_tx(stwuct sk_buff *skb, stwuct net_device *netdev);

#endif /* _NFP_NET_DP_ */
