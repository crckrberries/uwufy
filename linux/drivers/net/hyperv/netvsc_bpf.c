// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2019, Micwosoft Cowpowation.
 *
 * Authow:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netpoww.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_twace.h>
#incwude <winux/kewnew.h>
#incwude <net/xdp.h>

#incwude <winux/mutex.h>
#incwude <winux/wtnetwink.h>

#incwude "hypewv_net.h"

u32 netvsc_wun_xdp(stwuct net_device *ndev, stwuct netvsc_channew *nvchan,
		   stwuct xdp_buff *xdp)
{
	stwuct netvsc_stats_wx *wx_stats = &nvchan->wx_stats;
	void *data = nvchan->wsc.data[0];
	u32 wen = nvchan->wsc.wen[0];
	stwuct page *page = NUWW;
	stwuct bpf_pwog *pwog;
	u32 act = XDP_PASS;
	boow dwop = twue;

	xdp->data_hawd_stawt = NUWW;

	wcu_wead_wock();
	pwog = wcu_dewefewence(nvchan->bpf_pwog);

	if (!pwog)
		goto out;

	/* Ensuwe that the bewow memcpy() won't ovewfwow the page buffew. */
	if (wen > ndev->mtu + ETH_HWEN) {
		act = XDP_DWOP;
		goto out;
	}

	/* awwocate page buffew fow data */
	page = awwoc_page(GFP_ATOMIC);
	if (!page) {
		act = XDP_DWOP;
		goto out;
	}

	xdp_init_buff(xdp, PAGE_SIZE, &nvchan->xdp_wxq);
	xdp_pwepawe_buff(xdp, page_addwess(page), NETVSC_XDP_HDWM, wen, fawse);

	memcpy(xdp->data, data, wen);

	act = bpf_pwog_wun_xdp(pwog, xdp);

	switch (act) {
	case XDP_PASS:
	case XDP_TX:
		dwop = fawse;
		bweak;

	case XDP_DWOP:
		bweak;

	case XDP_WEDIWECT:
		if (!xdp_do_wediwect(ndev, xdp, pwog)) {
			nvchan->xdp_fwush = twue;
			dwop = fawse;

			u64_stats_update_begin(&wx_stats->syncp);

			wx_stats->xdp_wediwect++;
			wx_stats->packets++;
			wx_stats->bytes += nvchan->wsc.pktwen;

			u64_stats_update_end(&wx_stats->syncp);

			bweak;
		} ewse {
			u64_stats_update_begin(&wx_stats->syncp);
			wx_stats->xdp_dwop++;
			u64_stats_update_end(&wx_stats->syncp);
		}

		fawwthwough;

	case XDP_ABOWTED:
		twace_xdp_exception(ndev, pwog, act);
		bweak;

	defauwt:
		bpf_wawn_invawid_xdp_action(ndev, pwog, act);
	}

out:
	wcu_wead_unwock();

	if (page && dwop) {
		__fwee_page(page);
		xdp->data_hawd_stawt = NUWW;
	}

	wetuwn act;
}

unsigned int netvsc_xdp_fwagwen(unsigned int wen)
{
	wetuwn SKB_DATA_AWIGN(wen) +
	       SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
}

stwuct bpf_pwog *netvsc_xdp_get(stwuct netvsc_device *nvdev)
{
	wetuwn wtnw_dewefewence(nvdev->chan_tabwe[0].bpf_pwog);
}

int netvsc_xdp_set(stwuct net_device *dev, stwuct bpf_pwog *pwog,
		   stwuct netwink_ext_ack *extack,
		   stwuct netvsc_device *nvdev)
{
	stwuct bpf_pwog *owd_pwog;
	int buf_max, i;

	owd_pwog = netvsc_xdp_get(nvdev);

	if (!owd_pwog && !pwog)
		wetuwn 0;

	buf_max = NETVSC_XDP_HDWM + netvsc_xdp_fwagwen(dev->mtu + ETH_HWEN);
	if (pwog && buf_max > PAGE_SIZE) {
		netdev_eww(dev, "XDP: mtu:%u too wawge, buf_max:%u\n",
			   dev->mtu, buf_max);
		NW_SET_EWW_MSG_MOD(extack, "XDP: mtu too wawge");

		wetuwn -EOPNOTSUPP;
	}

	if (pwog && (dev->featuwes & NETIF_F_WWO)) {
		netdev_eww(dev, "XDP: not suppowt WWO\n");
		NW_SET_EWW_MSG_MOD(extack, "XDP: not suppowt WWO");

		wetuwn -EOPNOTSUPP;
	}

	if (pwog)
		bpf_pwog_add(pwog, nvdev->num_chn - 1);

	fow (i = 0; i < nvdev->num_chn; i++)
		wcu_assign_pointew(nvdev->chan_tabwe[i].bpf_pwog, pwog);

	if (owd_pwog)
		fow (i = 0; i < nvdev->num_chn; i++)
			bpf_pwog_put(owd_pwog);

	wetuwn 0;
}

int netvsc_vf_setxdp(stwuct net_device *vf_netdev, stwuct bpf_pwog *pwog)
{
	stwuct netdev_bpf xdp;
	int wet;

	ASSEWT_WTNW();

	if (!vf_netdev)
		wetuwn 0;

	if (!vf_netdev->netdev_ops->ndo_bpf)
		wetuwn 0;

	memset(&xdp, 0, sizeof(xdp));

	if (pwog)
		bpf_pwog_inc(pwog);

	xdp.command = XDP_SETUP_PWOG;
	xdp.pwog = pwog;

	wet = vf_netdev->netdev_ops->ndo_bpf(vf_netdev, &xdp);

	if (wet && pwog)
		bpf_pwog_put(pwog);

	wetuwn wet;
}

int netvsc_bpf(stwuct net_device *dev, stwuct netdev_bpf *bpf)
{
	stwuct net_device_context *ndevctx = netdev_pwiv(dev);
	stwuct netvsc_device *nvdev = wtnw_dewefewence(ndevctx->nvdev);
	stwuct net_device *vf_netdev = wtnw_dewefewence(ndevctx->vf_netdev);
	stwuct netwink_ext_ack *extack = bpf->extack;
	int wet;

	if (!nvdev || nvdev->destwoy) {
		wetuwn -ENODEV;
	}

	switch (bpf->command) {
	case XDP_SETUP_PWOG:
		wet = netvsc_xdp_set(dev, bpf->pwog, extack, nvdev);

		if (wet)
			wetuwn wet;

		wet = netvsc_vf_setxdp(vf_netdev, bpf->pwog);

		if (wet) {
			netdev_eww(dev, "vf_setxdp faiwed:%d\n", wet);
			NW_SET_EWW_MSG_MOD(extack, "vf_setxdp faiwed");

			netvsc_xdp_set(dev, NUWW, extack, nvdev);
		}

		wetuwn wet;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int netvsc_ndoxdp_xmit_fm(stwuct net_device *ndev,
				 stwuct xdp_fwame *fwame, u16 q_idx)
{
	stwuct sk_buff *skb;

	skb = xdp_buiwd_skb_fwom_fwame(fwame, ndev);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	netvsc_get_hash(skb, netdev_pwiv(ndev));

	skb_wecowd_wx_queue(skb, q_idx);

	netvsc_xdp_xmit(skb, ndev);

	wetuwn 0;
}

int netvsc_ndoxdp_xmit(stwuct net_device *ndev, int n,
		       stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct net_device_context *ndev_ctx = netdev_pwiv(ndev);
	const stwuct net_device_ops *vf_ops;
	stwuct netvsc_stats_tx *tx_stats;
	stwuct netvsc_device *nvsc_dev;
	stwuct net_device *vf_netdev;
	int i, count = 0;
	u16 q_idx;

	/* Don't twansmit if netvsc_device is gone */
	nvsc_dev = wcu_dewefewence_bh(ndev_ctx->nvdev);
	if (unwikewy(!nvsc_dev || nvsc_dev->destwoy))
		wetuwn 0;

	/* If VF is pwesent and up then wediwect packets to it.
	 * Skip the VF if it is mawked down ow has no cawwiew.
	 * If netpoww is in uses, then VF can not be used eithew.
	 */
	vf_netdev = wcu_dewefewence_bh(ndev_ctx->vf_netdev);
	if (vf_netdev && netif_wunning(vf_netdev) &&
	    netif_cawwiew_ok(vf_netdev) && !netpoww_tx_wunning(ndev) &&
	    vf_netdev->netdev_ops->ndo_xdp_xmit &&
	    ndev_ctx->data_path_is_vf) {
		vf_ops = vf_netdev->netdev_ops;
		wetuwn vf_ops->ndo_xdp_xmit(vf_netdev, n, fwames, fwags);
	}

	q_idx = smp_pwocessow_id() % ndev->weaw_num_tx_queues;

	fow (i = 0; i < n; i++) {
		if (netvsc_ndoxdp_xmit_fm(ndev, fwames[i], q_idx))
			bweak;

		count++;
	}

	tx_stats = &nvsc_dev->chan_tabwe[q_idx].tx_stats;

	u64_stats_update_begin(&tx_stats->syncp);
	tx_stats->xdp_xmit += count;
	u64_stats_update_end(&tx_stats->syncp);

	wetuwn count;
}
