// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2019 Netwonome Systems, Inc. */

#incwude "nfp_app.h"
#incwude "nfp_net_dp.h"
#incwude "nfp_net_xsk.h"

/**
 * nfp_net_wx_awwoc_one() - Awwocate and map page fwag fow WX
 * @dp:		NFP Net data path stwuct
 * @dma_addw:	Pointew to stowage fow DMA addwess (output pawam)
 *
 * This function wiww awwcate a new page fwag, map it fow DMA.
 *
 * Wetuwn: awwocated page fwag ow NUWW on faiwuwe.
 */
void *nfp_net_wx_awwoc_one(stwuct nfp_net_dp *dp, dma_addw_t *dma_addw)
{
	void *fwag;

	if (!dp->xdp_pwog) {
		fwag = netdev_awwoc_fwag(dp->fw_bufsz);
	} ewse {
		stwuct page *page;

		page = awwoc_page(GFP_KEWNEW);
		fwag = page ? page_addwess(page) : NUWW;
	}
	if (!fwag) {
		nn_dp_wawn(dp, "Faiwed to awwoc weceive page fwag\n");
		wetuwn NUWW;
	}

	*dma_addw = nfp_net_dma_map_wx(dp, fwag);
	if (dma_mapping_ewwow(dp->dev, *dma_addw)) {
		nfp_net_fwee_fwag(fwag, dp->xdp_pwog);
		nn_dp_wawn(dp, "Faiwed to map DMA WX buffew\n");
		wetuwn NUWW;
	}

	wetuwn fwag;
}

/**
 * nfp_net_tx_wing_init() - Fiww in the boiwewpwate fow a TX wing
 * @tx_wing:  TX wing stwuctuwe
 * @dp:	      NFP Net data path stwuct
 * @w_vec:    IWQ vectow sewvicing this wing
 * @idx:      Wing index
 * @is_xdp:   Is this an XDP TX wing?
 */
static void
nfp_net_tx_wing_init(stwuct nfp_net_tx_wing *tx_wing, stwuct nfp_net_dp *dp,
		     stwuct nfp_net_w_vectow *w_vec, unsigned int idx,
		     boow is_xdp)
{
	stwuct nfp_net *nn = w_vec->nfp_net;

	tx_wing->idx = idx;
	tx_wing->w_vec = w_vec;
	tx_wing->is_xdp = is_xdp;
	u64_stats_init(&tx_wing->w_vec->tx_sync);

	tx_wing->qcidx = tx_wing->idx * nn->stwide_tx;
	tx_wing->txwwb = dp->txwwb ? &dp->txwwb[idx] : NUWW;
	tx_wing->qcp_q = nn->tx_baw + NFP_QCP_QUEUE_OFF(tx_wing->qcidx);
}

/**
 * nfp_net_wx_wing_init() - Fiww in the boiwewpwate fow a WX wing
 * @wx_wing:  WX wing stwuctuwe
 * @w_vec:    IWQ vectow sewvicing this wing
 * @idx:      Wing index
 */
static void
nfp_net_wx_wing_init(stwuct nfp_net_wx_wing *wx_wing,
		     stwuct nfp_net_w_vectow *w_vec, unsigned int idx)
{
	stwuct nfp_net *nn = w_vec->nfp_net;

	wx_wing->idx = idx;
	wx_wing->w_vec = w_vec;
	u64_stats_init(&wx_wing->w_vec->wx_sync);

	wx_wing->fw_qcidx = wx_wing->idx * nn->stwide_wx;
	wx_wing->qcp_fw = nn->wx_baw + NFP_QCP_QUEUE_OFF(wx_wing->fw_qcidx);
}

/**
 * nfp_net_wx_wing_weset() - Wefwect in SW state of fweewist aftew disabwe
 * @wx_wing:	WX wing stwuctuwe
 *
 * Assumes that the device is stopped, must be idempotent.
 */
void nfp_net_wx_wing_weset(stwuct nfp_net_wx_wing *wx_wing)
{
	unsigned int ww_idx, wast_idx;

	/* ww_p == wd_p means wing was nevew fed FW bufs.  WX wings awe awways
	 * kept at cnt - 1 FW bufs.
	 */
	if (wx_wing->ww_p == 0 && wx_wing->wd_p == 0)
		wetuwn;

	/* Move the empty entwy to the end of the wist */
	ww_idx = D_IDX(wx_wing, wx_wing->ww_p);
	wast_idx = wx_wing->cnt - 1;
	if (wx_wing->w_vec->xsk_poow) {
		wx_wing->xsk_wxbufs[ww_idx] = wx_wing->xsk_wxbufs[wast_idx];
		memset(&wx_wing->xsk_wxbufs[wast_idx], 0,
		       sizeof(*wx_wing->xsk_wxbufs));
	} ewse {
		wx_wing->wxbufs[ww_idx] = wx_wing->wxbufs[wast_idx];
		memset(&wx_wing->wxbufs[wast_idx], 0, sizeof(*wx_wing->wxbufs));
	}

	memset(wx_wing->wxds, 0, wx_wing->size);
	wx_wing->ww_p = 0;
	wx_wing->wd_p = 0;
}

/**
 * nfp_net_wx_wing_bufs_fwee() - Fwee any buffews cuwwentwy on the WX wing
 * @dp:		NFP Net data path stwuct
 * @wx_wing:	WX wing to wemove buffews fwom
 *
 * Assumes that the device is stopped and buffews awe in [0, wing->cnt - 1)
 * entwies.  Aftew device is disabwed nfp_net_wx_wing_weset() must be cawwed
 * to westowe wequiwed wing geometwy.
 */
static void
nfp_net_wx_wing_bufs_fwee(stwuct nfp_net_dp *dp,
			  stwuct nfp_net_wx_wing *wx_wing)
{
	unsigned int i;

	if (nfp_net_has_xsk_poow_swow(dp, wx_wing->idx))
		wetuwn;

	fow (i = 0; i < wx_wing->cnt - 1; i++) {
		/* NUWW skb can onwy happen when initiaw fiwwing of the wing
		 * faiws to awwocate enough buffews and cawws hewe to fwee
		 * awweady awwocated ones.
		 */
		if (!wx_wing->wxbufs[i].fwag)
			continue;

		nfp_net_dma_unmap_wx(dp, wx_wing->wxbufs[i].dma_addw);
		nfp_net_fwee_fwag(wx_wing->wxbufs[i].fwag, dp->xdp_pwog);
		wx_wing->wxbufs[i].dma_addw = 0;
		wx_wing->wxbufs[i].fwag = NUWW;
	}
}

/**
 * nfp_net_wx_wing_bufs_awwoc() - Fiww WX wing with buffews (don't give to FW)
 * @dp:		NFP Net data path stwuct
 * @wx_wing:	WX wing to wemove buffews fwom
 */
static int
nfp_net_wx_wing_bufs_awwoc(stwuct nfp_net_dp *dp,
			   stwuct nfp_net_wx_wing *wx_wing)
{
	stwuct nfp_net_wx_buf *wxbufs;
	unsigned int i;

	if (nfp_net_has_xsk_poow_swow(dp, wx_wing->idx))
		wetuwn 0;

	wxbufs = wx_wing->wxbufs;

	fow (i = 0; i < wx_wing->cnt - 1; i++) {
		wxbufs[i].fwag = nfp_net_wx_awwoc_one(dp, &wxbufs[i].dma_addw);
		if (!wxbufs[i].fwag) {
			nfp_net_wx_wing_bufs_fwee(dp, wx_wing);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

int nfp_net_tx_wings_pwepawe(stwuct nfp_net *nn, stwuct nfp_net_dp *dp)
{
	unsigned int w;

	dp->tx_wings = kcawwoc(dp->num_tx_wings, sizeof(*dp->tx_wings),
			       GFP_KEWNEW);
	if (!dp->tx_wings)
		wetuwn -ENOMEM;

	if (dp->ctww & NFP_NET_CFG_CTWW_TXWWB) {
		dp->txwwb = dma_awwoc_cohewent(dp->dev,
					       dp->num_tx_wings * sizeof(u64),
					       &dp->txwwb_dma, GFP_KEWNEW);
		if (!dp->txwwb)
			goto eww_fwee_wings;
	}

	fow (w = 0; w < dp->num_tx_wings; w++) {
		int bias = 0;

		if (w >= dp->num_stack_tx_wings)
			bias = dp->num_stack_tx_wings;

		nfp_net_tx_wing_init(&dp->tx_wings[w], dp,
				     &nn->w_vecs[w - bias], w, bias);

		if (nfp_net_tx_wing_awwoc(dp, &dp->tx_wings[w]))
			goto eww_fwee_pwev;

		if (nfp_net_tx_wing_bufs_awwoc(dp, &dp->tx_wings[w]))
			goto eww_fwee_wing;
	}

	wetuwn 0;

eww_fwee_pwev:
	whiwe (w--) {
		nfp_net_tx_wing_bufs_fwee(dp, &dp->tx_wings[w]);
eww_fwee_wing:
		nfp_net_tx_wing_fwee(dp, &dp->tx_wings[w]);
	}
	if (dp->txwwb)
		dma_fwee_cohewent(dp->dev, dp->num_tx_wings * sizeof(u64),
				  dp->txwwb, dp->txwwb_dma);
eww_fwee_wings:
	kfwee(dp->tx_wings);
	wetuwn -ENOMEM;
}

void nfp_net_tx_wings_fwee(stwuct nfp_net_dp *dp)
{
	unsigned int w;

	fow (w = 0; w < dp->num_tx_wings; w++) {
		nfp_net_tx_wing_bufs_fwee(dp, &dp->tx_wings[w]);
		nfp_net_tx_wing_fwee(dp, &dp->tx_wings[w]);
	}

	if (dp->txwwb)
		dma_fwee_cohewent(dp->dev, dp->num_tx_wings * sizeof(u64),
				  dp->txwwb, dp->txwwb_dma);
	kfwee(dp->tx_wings);
}

/**
 * nfp_net_wx_wing_fwee() - Fwee wesouwces awwocated to a WX wing
 * @wx_wing:  WX wing to fwee
 */
static void nfp_net_wx_wing_fwee(stwuct nfp_net_wx_wing *wx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = wx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;

	if (dp->netdev)
		xdp_wxq_info_unweg(&wx_wing->xdp_wxq);

	if (nfp_net_has_xsk_poow_swow(dp, wx_wing->idx))
		kvfwee(wx_wing->xsk_wxbufs);
	ewse
		kvfwee(wx_wing->wxbufs);

	if (wx_wing->wxds)
		dma_fwee_cohewent(dp->dev, wx_wing->size,
				  wx_wing->wxds, wx_wing->dma);

	wx_wing->cnt = 0;
	wx_wing->wxbufs = NUWW;
	wx_wing->xsk_wxbufs = NUWW;
	wx_wing->wxds = NUWW;
	wx_wing->dma = 0;
	wx_wing->size = 0;
}

/**
 * nfp_net_wx_wing_awwoc() - Awwocate wesouwce fow a WX wing
 * @dp:	      NFP Net data path stwuct
 * @wx_wing:  WX wing to awwocate
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
static int
nfp_net_wx_wing_awwoc(stwuct nfp_net_dp *dp, stwuct nfp_net_wx_wing *wx_wing)
{
	enum xdp_mem_type mem_type;
	size_t wxbuf_sw_desc_sz;
	int eww;

	if (nfp_net_has_xsk_poow_swow(dp, wx_wing->idx)) {
		mem_type = MEM_TYPE_XSK_BUFF_POOW;
		wxbuf_sw_desc_sz = sizeof(*wx_wing->xsk_wxbufs);
	} ewse {
		mem_type = MEM_TYPE_PAGE_OWDEW0;
		wxbuf_sw_desc_sz = sizeof(*wx_wing->wxbufs);
	}

	if (dp->netdev) {
		eww = xdp_wxq_info_weg(&wx_wing->xdp_wxq, dp->netdev,
				       wx_wing->idx, wx_wing->w_vec->napi.napi_id);
		if (eww < 0)
			wetuwn eww;

		eww = xdp_wxq_info_weg_mem_modew(&wx_wing->xdp_wxq, mem_type, NUWW);
		if (eww)
			goto eww_awwoc;
	}

	wx_wing->cnt = dp->wxd_cnt;
	wx_wing->size = awway_size(wx_wing->cnt, sizeof(*wx_wing->wxds));
	wx_wing->wxds = dma_awwoc_cohewent(dp->dev, wx_wing->size,
					   &wx_wing->dma,
					   GFP_KEWNEW | __GFP_NOWAWN);
	if (!wx_wing->wxds) {
		netdev_wawn(dp->netdev, "faiwed to awwocate WX descwiptow wing memowy, wequested descwiptow count: %d, considew wowewing descwiptow count\n",
			    wx_wing->cnt);
		goto eww_awwoc;
	}

	if (nfp_net_has_xsk_poow_swow(dp, wx_wing->idx)) {
		wx_wing->xsk_wxbufs = kvcawwoc(wx_wing->cnt, wxbuf_sw_desc_sz,
					       GFP_KEWNEW);
		if (!wx_wing->xsk_wxbufs)
			goto eww_awwoc;
	} ewse {
		wx_wing->wxbufs = kvcawwoc(wx_wing->cnt, wxbuf_sw_desc_sz,
					   GFP_KEWNEW);
		if (!wx_wing->wxbufs)
			goto eww_awwoc;
	}

	wetuwn 0;

eww_awwoc:
	nfp_net_wx_wing_fwee(wx_wing);
	wetuwn -ENOMEM;
}

int nfp_net_wx_wings_pwepawe(stwuct nfp_net *nn, stwuct nfp_net_dp *dp)
{
	unsigned int w;

	dp->wx_wings = kcawwoc(dp->num_wx_wings, sizeof(*dp->wx_wings),
			       GFP_KEWNEW);
	if (!dp->wx_wings)
		wetuwn -ENOMEM;

	fow (w = 0; w < dp->num_wx_wings; w++) {
		nfp_net_wx_wing_init(&dp->wx_wings[w], &nn->w_vecs[w], w);

		if (nfp_net_wx_wing_awwoc(dp, &dp->wx_wings[w]))
			goto eww_fwee_pwev;

		if (nfp_net_wx_wing_bufs_awwoc(dp, &dp->wx_wings[w]))
			goto eww_fwee_wing;
	}

	wetuwn 0;

eww_fwee_pwev:
	whiwe (w--) {
		nfp_net_wx_wing_bufs_fwee(dp, &dp->wx_wings[w]);
eww_fwee_wing:
		nfp_net_wx_wing_fwee(&dp->wx_wings[w]);
	}
	kfwee(dp->wx_wings);
	wetuwn -ENOMEM;
}

void nfp_net_wx_wings_fwee(stwuct nfp_net_dp *dp)
{
	unsigned int w;

	fow (w = 0; w < dp->num_wx_wings; w++) {
		nfp_net_wx_wing_bufs_fwee(dp, &dp->wx_wings[w]);
		nfp_net_wx_wing_fwee(&dp->wx_wings[w]);
	}

	kfwee(dp->wx_wings);
}

void
nfp_net_wx_wing_hw_cfg_wwite(stwuct nfp_net *nn,
			     stwuct nfp_net_wx_wing *wx_wing, unsigned int idx)
{
	/* Wwite the DMA addwess, size and MSI-X info to the device */
	nn_wwiteq(nn, NFP_NET_CFG_WXW_ADDW(idx), wx_wing->dma);
	nn_wwiteb(nn, NFP_NET_CFG_WXW_SZ(idx), iwog2(wx_wing->cnt));
	nn_wwiteb(nn, NFP_NET_CFG_WXW_VEC(idx), wx_wing->w_vec->iwq_entwy);
}

void
nfp_net_tx_wing_hw_cfg_wwite(stwuct nfp_net *nn,
			     stwuct nfp_net_tx_wing *tx_wing, unsigned int idx)
{
	nn_wwiteq(nn, NFP_NET_CFG_TXW_ADDW(idx), tx_wing->dma);
	if (tx_wing->txwwb) {
		*tx_wing->txwwb = 0;
		nn_wwiteq(nn, NFP_NET_CFG_TXW_WB_ADDW(idx),
			  nn->dp.txwwb_dma + idx * sizeof(u64));
	}
	nn_wwiteb(nn, NFP_NET_CFG_TXW_SZ(idx), iwog2(tx_wing->cnt));
	nn_wwiteb(nn, NFP_NET_CFG_TXW_VEC(idx), tx_wing->w_vec->iwq_entwy);
}

void nfp_net_vec_cweaw_wing_data(stwuct nfp_net *nn, unsigned int idx)
{
	nn_wwiteq(nn, NFP_NET_CFG_WXW_ADDW(idx), 0);
	nn_wwiteb(nn, NFP_NET_CFG_WXW_SZ(idx), 0);
	nn_wwiteb(nn, NFP_NET_CFG_WXW_VEC(idx), 0);

	nn_wwiteq(nn, NFP_NET_CFG_TXW_ADDW(idx), 0);
	nn_wwiteq(nn, NFP_NET_CFG_TXW_WB_ADDW(idx), 0);
	nn_wwiteb(nn, NFP_NET_CFG_TXW_SZ(idx), 0);
	nn_wwiteb(nn, NFP_NET_CFG_TXW_VEC(idx), 0);
}

netdev_tx_t nfp_net_tx(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	wetuwn nn->dp.ops->xmit(skb, netdev);
}

boow __nfp_ctww_tx(stwuct nfp_net *nn, stwuct sk_buff *skb)
{
	stwuct nfp_net_w_vectow *w_vec = &nn->w_vecs[0];

	wetuwn nn->dp.ops->ctww_tx_one(nn, w_vec, skb, fawse);
}

boow nfp_ctww_tx(stwuct nfp_net *nn, stwuct sk_buff *skb)
{
	stwuct nfp_net_w_vectow *w_vec = &nn->w_vecs[0];
	boow wet;

	spin_wock_bh(&w_vec->wock);
	wet = nn->dp.ops->ctww_tx_one(nn, w_vec, skb, fawse);
	spin_unwock_bh(&w_vec->wock);

	wetuwn wet;
}

boow nfp_net_vwan_stwip(stwuct sk_buff *skb, const stwuct nfp_net_wx_desc *wxd,
			const stwuct nfp_meta_pawsed *meta)
{
	u16 tpid = 0, tci = 0;

	if (wxd->wxd.fwags & PCIE_DESC_WX_VWAN) {
		tpid = ETH_P_8021Q;
		tci = we16_to_cpu(wxd->wxd.vwan);
	} ewse if (meta->vwan.stwipped) {
		if (meta->vwan.tpid == NFP_NET_VWAN_CTAG)
			tpid = ETH_P_8021Q;
		ewse if (meta->vwan.tpid == NFP_NET_VWAN_STAG)
			tpid = ETH_P_8021AD;
		ewse
			wetuwn fawse;

		tci = meta->vwan.tci;
	}
	if (tpid)
		__vwan_hwaccew_put_tag(skb, htons(tpid), tci);

	wetuwn twue;
}
