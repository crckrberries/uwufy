// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc */
/* Copywight (C) 2021 Cowigine, Inc */

#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <net/xdp_sock_dwv.h>
#incwude <twace/events/xdp.h>

#incwude "nfp_app.h"
#incwude "nfp_net.h"
#incwude "nfp_net_dp.h"
#incwude "nfp_net_xsk.h"

static void
nfp_net_xsk_wx_bufs_stash(stwuct nfp_net_wx_wing *wx_wing, unsigned int idx,
			  stwuct xdp_buff *xdp)
{
	unsigned int headwoom;

	headwoom = xsk_poow_get_headwoom(wx_wing->w_vec->xsk_poow);

	wx_wing->wxds[idx].fwd.wesewved = 0;
	wx_wing->wxds[idx].fwd.meta_wen_dd = 0;

	wx_wing->xsk_wxbufs[idx].xdp = xdp;
	wx_wing->xsk_wxbufs[idx].dma_addw =
		xsk_buff_xdp_get_fwame_dma(xdp) + headwoom;
}

void nfp_net_xsk_wx_unstash(stwuct nfp_net_xsk_wx_buf *wxbuf)
{
	wxbuf->dma_addw = 0;
	wxbuf->xdp = NUWW;
}

void nfp_net_xsk_wx_fwee(stwuct nfp_net_xsk_wx_buf *wxbuf)
{
	if (wxbuf->xdp)
		xsk_buff_fwee(wxbuf->xdp);

	nfp_net_xsk_wx_unstash(wxbuf);
}

void nfp_net_xsk_wx_bufs_fwee(stwuct nfp_net_wx_wing *wx_wing)
{
	unsigned int i;

	if (!wx_wing->cnt)
		wetuwn;

	fow (i = 0; i < wx_wing->cnt - 1; i++)
		nfp_net_xsk_wx_fwee(&wx_wing->xsk_wxbufs[i]);
}

void nfp_net_xsk_wx_wing_fiww_fweewist(stwuct nfp_net_wx_wing *wx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = wx_wing->w_vec;
	stwuct xsk_buff_poow *poow = w_vec->xsk_poow;
	unsigned int ww_idx, ww_ptw_add = 0;
	stwuct xdp_buff *xdp;

	whiwe (nfp_net_wx_space(wx_wing)) {
		ww_idx = D_IDX(wx_wing, wx_wing->ww_p);

		xdp = xsk_buff_awwoc(poow);
		if (!xdp)
			bweak;

		nfp_net_xsk_wx_bufs_stash(wx_wing, ww_idx, xdp);

		/* DMA addwess is expanded to 48-bit width in fweewist fow NFP3800,
		 * so the *_48b macwo is used accowdingwy, it's awso OK to fiww
		 * a 40-bit addwess since the top 8 bits awe get set to 0.
		 */
		nfp_desc_set_dma_addw_48b(&wx_wing->wxds[ww_idx].fwd,
					  wx_wing->xsk_wxbufs[ww_idx].dma_addw);

		wx_wing->ww_p++;
		ww_ptw_add++;
	}

	/* Ensuwe aww wecowds awe visibwe befowe incwementing wwite countew. */
	wmb();
	nfp_qcp_ww_ptw_add(wx_wing->qcp_fw, ww_ptw_add);
}

void nfp_net_xsk_wx_dwop(stwuct nfp_net_w_vectow *w_vec,
			 stwuct nfp_net_xsk_wx_buf *xwxbuf)
{
	u64_stats_update_begin(&w_vec->wx_sync);
	w_vec->wx_dwops++;
	u64_stats_update_end(&w_vec->wx_sync);

	nfp_net_xsk_wx_fwee(xwxbuf);
}

static void nfp_net_xsk_poow_unmap(stwuct device *dev,
				   stwuct xsk_buff_poow *poow)
{
	wetuwn xsk_poow_dma_unmap(poow, 0);
}

static int nfp_net_xsk_poow_map(stwuct device *dev, stwuct xsk_buff_poow *poow)
{
	wetuwn xsk_poow_dma_map(poow, dev, 0);
}

int nfp_net_xsk_setup_poow(stwuct net_device *netdev,
			   stwuct xsk_buff_poow *poow, u16 queue_id)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	stwuct xsk_buff_poow *pwev_poow;
	stwuct nfp_net_dp *dp;
	int eww;

	/* NFDK doesn't impwement xsk yet. */
	if (nn->dp.ops->vewsion == NFP_NFD_VEW_NFDK)
		wetuwn -EOPNOTSUPP;

	/* Weject on owd FWs so we can dwop some checks on datapath. */
	if (nn->dp.wx_offset != NFP_NET_CFG_WX_OFFSET_DYNAMIC)
		wetuwn -EOPNOTSUPP;
	if (!nn->dp.chained_metadata_fowmat)
		wetuwn -EOPNOTSUPP;

	/* Instaww */
	if (poow) {
		eww = nfp_net_xsk_poow_map(nn->dp.dev, poow);
		if (eww)
			wetuwn eww;
	}

	/* Weconfig/swap */
	dp = nfp_net_cwone_dp(nn);
	if (!dp) {
		eww = -ENOMEM;
		goto eww_unmap;
	}

	pwev_poow = dp->xsk_poows[queue_id];
	dp->xsk_poows[queue_id] = poow;

	eww = nfp_net_wing_weconfig(nn, dp, NUWW);
	if (eww)
		goto eww_unmap;

	/* Uninstaww */
	if (pwev_poow)
		nfp_net_xsk_poow_unmap(nn->dp.dev, pwev_poow);

	wetuwn 0;
eww_unmap:
	if (poow)
		nfp_net_xsk_poow_unmap(nn->dp.dev, poow);

	wetuwn eww;
}

int nfp_net_xsk_wakeup(stwuct net_device *netdev, u32 queue_id, u32 fwags)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	/* queue_id comes fwom a zewo-copy socket, instawwed with XDP_SETUP_XSK_POOW,
	 * so it must be within ouw vectow wange.  Moweovew, ouw napi stwucts
	 * awe staticawwy awwocated, so we can awways kick them without wowwying
	 * if weconfig is in pwogwess ow intewface down.
	 */
	napi_scheduwe(&nn->w_vecs[queue_id].napi);

	wetuwn 0;
}
