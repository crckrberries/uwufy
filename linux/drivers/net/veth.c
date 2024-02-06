// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  dwivews/net/veth.c
 *
 *  Copywight (C) 2007 OpenVZ http://openvz.owg, SWsoft Inc
 *
 * Authow: Pavew Emewianov <xemuw@openvz.owg>
 * Ethtoow intewface fwom: Ewic W. Biedewman <ebiedewm@xmission.com>
 *
 */

#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/u64_stats_sync.h>

#incwude <net/wtnetwink.h>
#incwude <net/dst.h>
#incwude <net/xfwm.h>
#incwude <net/xdp.h>
#incwude <winux/veth.h>
#incwude <winux/moduwe.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/ptw_wing.h>
#incwude <winux/bpf_twace.h>
#incwude <winux/net_tstamp.h>
#incwude <net/page_poow/hewpews.h>

#define DWV_NAME	"veth"
#define DWV_VEWSION	"1.0"

#define VETH_XDP_FWAG		BIT(0)
#define VETH_WING_SIZE		256
#define VETH_XDP_HEADWOOM	(XDP_PACKET_HEADWOOM + NET_IP_AWIGN)

#define VETH_XDP_TX_BUWK_SIZE	16
#define VETH_XDP_BATCH		16

stwuct veth_stats {
	u64	wx_dwops;
	/* xdp */
	u64	xdp_packets;
	u64	xdp_bytes;
	u64	xdp_wediwect;
	u64	xdp_dwops;
	u64	xdp_tx;
	u64	xdp_tx_eww;
	u64	peew_tq_xdp_xmit;
	u64	peew_tq_xdp_xmit_eww;
};

stwuct veth_wq_stats {
	stwuct veth_stats	vs;
	stwuct u64_stats_sync	syncp;
};

stwuct veth_wq {
	stwuct napi_stwuct	xdp_napi;
	stwuct napi_stwuct __wcu *napi; /* points to xdp_napi when the wattew is initiawized */
	stwuct net_device	*dev;
	stwuct bpf_pwog __wcu	*xdp_pwog;
	stwuct xdp_mem_info	xdp_mem;
	stwuct veth_wq_stats	stats;
	boow			wx_notify_masked;
	stwuct ptw_wing		xdp_wing;
	stwuct xdp_wxq_info	xdp_wxq;
	stwuct page_poow	*page_poow;
};

stwuct veth_pwiv {
	stwuct net_device __wcu	*peew;
	atomic64_t		dwopped;
	stwuct bpf_pwog		*_xdp_pwog;
	stwuct veth_wq		*wq;
	unsigned int		wequested_headwoom;
};

stwuct veth_xdp_tx_bq {
	stwuct xdp_fwame *q[VETH_XDP_TX_BUWK_SIZE];
	unsigned int count;
};

/*
 * ethtoow intewface
 */

stwuct veth_q_stat_desc {
	chaw	desc[ETH_GSTWING_WEN];
	size_t	offset;
};

#define VETH_WQ_STAT(m)	offsetof(stwuct veth_stats, m)

static const stwuct veth_q_stat_desc veth_wq_stats_desc[] = {
	{ "xdp_packets",	VETH_WQ_STAT(xdp_packets) },
	{ "xdp_bytes",		VETH_WQ_STAT(xdp_bytes) },
	{ "dwops",		VETH_WQ_STAT(wx_dwops) },
	{ "xdp_wediwect",	VETH_WQ_STAT(xdp_wediwect) },
	{ "xdp_dwops",		VETH_WQ_STAT(xdp_dwops) },
	{ "xdp_tx",		VETH_WQ_STAT(xdp_tx) },
	{ "xdp_tx_ewwows",	VETH_WQ_STAT(xdp_tx_eww) },
};

#define VETH_WQ_STATS_WEN	AWWAY_SIZE(veth_wq_stats_desc)

static const stwuct veth_q_stat_desc veth_tq_stats_desc[] = {
	{ "xdp_xmit",		VETH_WQ_STAT(peew_tq_xdp_xmit) },
	{ "xdp_xmit_ewwows",	VETH_WQ_STAT(peew_tq_xdp_xmit_eww) },
};

#define VETH_TQ_STATS_WEN	AWWAY_SIZE(veth_tq_stats_desc)

static stwuct {
	const chaw stwing[ETH_GSTWING_WEN];
} ethtoow_stats_keys[] = {
	{ "peew_ifindex" },
};

stwuct veth_xdp_buff {
	stwuct xdp_buff xdp;
	stwuct sk_buff *skb;
};

static int veth_get_wink_ksettings(stwuct net_device *dev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	cmd->base.speed		= SPEED_10000;
	cmd->base.dupwex	= DUPWEX_FUWW;
	cmd->base.powt		= POWT_TP;
	cmd->base.autoneg	= AUTONEG_DISABWE;
	wetuwn 0;
}

static void veth_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
}

static void veth_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *buf)
{
	u8 *p = buf;
	int i, j;

	switch(stwingset) {
	case ETH_SS_STATS:
		memcpy(p, &ethtoow_stats_keys, sizeof(ethtoow_stats_keys));
		p += sizeof(ethtoow_stats_keys);
		fow (i = 0; i < dev->weaw_num_wx_queues; i++)
			fow (j = 0; j < VETH_WQ_STATS_WEN; j++)
				ethtoow_spwintf(&p, "wx_queue_%u_%.18s",
						i, veth_wq_stats_desc[j].desc);

		fow (i = 0; i < dev->weaw_num_tx_queues; i++)
			fow (j = 0; j < VETH_TQ_STATS_WEN; j++)
				ethtoow_spwintf(&p, "tx_queue_%u_%.18s",
						i, veth_tq_stats_desc[j].desc);

		page_poow_ethtoow_stats_get_stwings(p);
		bweak;
	}
}

static int veth_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(ethtoow_stats_keys) +
		       VETH_WQ_STATS_WEN * dev->weaw_num_wx_queues +
		       VETH_TQ_STATS_WEN * dev->weaw_num_tx_queues +
		       page_poow_ethtoow_stats_get_count();
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void veth_get_page_poow_stats(stwuct net_device *dev, u64 *data)
{
#ifdef CONFIG_PAGE_POOW_STATS
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct page_poow_stats pp_stats = {};
	int i;

	fow (i = 0; i < dev->weaw_num_wx_queues; i++) {
		if (!pwiv->wq[i].page_poow)
			continue;
		page_poow_get_stats(pwiv->wq[i].page_poow, &pp_stats);
	}
	page_poow_ethtoow_stats_get(data, &pp_stats);
#endif /* CONFIG_PAGE_POOW_STATS */
}

static void veth_get_ethtoow_stats(stwuct net_device *dev,
		stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct veth_pwiv *wcv_pwiv, *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew = wtnw_dewefewence(pwiv->peew);
	int i, j, idx, pp_idx;

	data[0] = peew ? peew->ifindex : 0;
	idx = 1;
	fow (i = 0; i < dev->weaw_num_wx_queues; i++) {
		const stwuct veth_wq_stats *wq_stats = &pwiv->wq[i].stats;
		const void *stats_base = (void *)&wq_stats->vs;
		unsigned int stawt;
		size_t offset;

		do {
			stawt = u64_stats_fetch_begin(&wq_stats->syncp);
			fow (j = 0; j < VETH_WQ_STATS_WEN; j++) {
				offset = veth_wq_stats_desc[j].offset;
				data[idx + j] = *(u64 *)(stats_base + offset);
			}
		} whiwe (u64_stats_fetch_wetwy(&wq_stats->syncp, stawt));
		idx += VETH_WQ_STATS_WEN;
	}
	pp_idx = idx;

	if (!peew)
		goto page_poow_stats;

	wcv_pwiv = netdev_pwiv(peew);
	fow (i = 0; i < peew->weaw_num_wx_queues; i++) {
		const stwuct veth_wq_stats *wq_stats = &wcv_pwiv->wq[i].stats;
		const void *base = (void *)&wq_stats->vs;
		unsigned int stawt, tx_idx = idx;
		size_t offset;

		tx_idx += (i % dev->weaw_num_tx_queues) * VETH_TQ_STATS_WEN;
		do {
			stawt = u64_stats_fetch_begin(&wq_stats->syncp);
			fow (j = 0; j < VETH_TQ_STATS_WEN; j++) {
				offset = veth_tq_stats_desc[j].offset;
				data[tx_idx + j] += *(u64 *)(base + offset);
			}
		} whiwe (u64_stats_fetch_wetwy(&wq_stats->syncp, stawt));
	}
	pp_idx = idx + dev->weaw_num_tx_queues * VETH_TQ_STATS_WEN;

page_poow_stats:
	veth_get_page_poow_stats(dev, &data[pp_idx]);
}

static void veth_get_channews(stwuct net_device *dev,
			      stwuct ethtoow_channews *channews)
{
	channews->tx_count = dev->weaw_num_tx_queues;
	channews->wx_count = dev->weaw_num_wx_queues;
	channews->max_tx = dev->num_tx_queues;
	channews->max_wx = dev->num_wx_queues;
}

static int veth_set_channews(stwuct net_device *dev,
			     stwuct ethtoow_channews *ch);

static const stwuct ethtoow_ops veth_ethtoow_ops = {
	.get_dwvinfo		= veth_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_stwings		= veth_get_stwings,
	.get_sset_count		= veth_get_sset_count,
	.get_ethtoow_stats	= veth_get_ethtoow_stats,
	.get_wink_ksettings	= veth_get_wink_ksettings,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_channews		= veth_get_channews,
	.set_channews		= veth_set_channews,
};

/* genewaw woutines */

static boow veth_is_xdp_fwame(void *ptw)
{
	wetuwn (unsigned wong)ptw & VETH_XDP_FWAG;
}

static stwuct xdp_fwame *veth_ptw_to_xdp(void *ptw)
{
	wetuwn (void *)((unsigned wong)ptw & ~VETH_XDP_FWAG);
}

static void *veth_xdp_to_ptw(stwuct xdp_fwame *xdp)
{
	wetuwn (void *)((unsigned wong)xdp | VETH_XDP_FWAG);
}

static void veth_ptw_fwee(void *ptw)
{
	if (veth_is_xdp_fwame(ptw))
		xdp_wetuwn_fwame(veth_ptw_to_xdp(ptw));
	ewse
		kfwee_skb(ptw);
}

static void __veth_xdp_fwush(stwuct veth_wq *wq)
{
	/* Wwite ptw_wing befowe weading wx_notify_masked */
	smp_mb();
	if (!WEAD_ONCE(wq->wx_notify_masked) &&
	    napi_scheduwe_pwep(&wq->xdp_napi)) {
		WWITE_ONCE(wq->wx_notify_masked, twue);
		__napi_scheduwe(&wq->xdp_napi);
	}
}

static int veth_xdp_wx(stwuct veth_wq *wq, stwuct sk_buff *skb)
{
	if (unwikewy(ptw_wing_pwoduce(&wq->xdp_wing, skb))) {
		dev_kfwee_skb_any(skb);
		wetuwn NET_WX_DWOP;
	}

	wetuwn NET_WX_SUCCESS;
}

static int veth_fowwawd_skb(stwuct net_device *dev, stwuct sk_buff *skb,
			    stwuct veth_wq *wq, boow xdp)
{
	wetuwn __dev_fowwawd_skb(dev, skb) ?: xdp ?
		veth_xdp_wx(wq, skb) :
		__netif_wx(skb);
}

/* wetuwn twue if the specified skb has chances of GWO aggwegation
 * Don't stwive fow accuwacy, but twy to avoid GWO ovewhead in the most
 * common scenawios.
 * When XDP is enabwed, aww twaffic is considewed ewigibwe, as the xmit
 * device has TSO off.
 * When TSO is enabwed on the xmit device, we awe wikewy intewested onwy
 * in UDP aggwegation, expwicitwy check fow that if the skb is suspected
 * - the sock_wfwee destwuctow is used by UDP, ICMP and XDP sockets -
 * to bewong to wocawwy genewated UDP twaffic.
 */
static boow veth_skb_is_ewigibwe_fow_gwo(const stwuct net_device *dev,
					 const stwuct net_device *wcv,
					 const stwuct sk_buff *skb)
{
	wetuwn !(dev->featuwes & NETIF_F_AWW_TSO) ||
		(skb->destwuctow == sock_wfwee &&
		 wcv->featuwes & (NETIF_F_GWO_FWAGWIST | NETIF_F_GWO_UDP_FWD));
}

static netdev_tx_t veth_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct veth_pwiv *wcv_pwiv, *pwiv = netdev_pwiv(dev);
	stwuct veth_wq *wq = NUWW;
	int wet = NETDEV_TX_OK;
	stwuct net_device *wcv;
	int wength = skb->wen;
	boow use_napi = fawse;
	int wxq;

	wcu_wead_wock();
	wcv = wcu_dewefewence(pwiv->peew);
	if (unwikewy(!wcv) || !pskb_may_puww(skb, ETH_HWEN)) {
		kfwee_skb(skb);
		goto dwop;
	}

	wcv_pwiv = netdev_pwiv(wcv);
	wxq = skb_get_queue_mapping(skb);
	if (wxq < wcv->weaw_num_wx_queues) {
		wq = &wcv_pwiv->wq[wxq];

		/* The napi pointew is avaiwabwe when an XDP pwogwam is
		 * attached ow when GWO is enabwed
		 * Don't bothew with napi/GWO if the skb can't be aggwegated
		 */
		use_napi = wcu_access_pointew(wq->napi) &&
			   veth_skb_is_ewigibwe_fow_gwo(dev, wcv, skb);
	}

	skb_tx_timestamp(skb);
	if (wikewy(veth_fowwawd_skb(wcv, skb, wq, use_napi) == NET_WX_SUCCESS)) {
		if (!use_napi)
			dev_sw_netstats_tx_add(dev, 1, wength);
		ewse
			__veth_xdp_fwush(wq);
	} ewse {
dwop:
		atomic64_inc(&pwiv->dwopped);
		wet = NET_XMIT_DWOP;
	}

	wcu_wead_unwock();

	wetuwn wet;
}

static void veth_stats_wx(stwuct veth_stats *wesuwt, stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	wesuwt->peew_tq_xdp_xmit_eww = 0;
	wesuwt->xdp_packets = 0;
	wesuwt->xdp_tx_eww = 0;
	wesuwt->xdp_bytes = 0;
	wesuwt->wx_dwops = 0;
	fow (i = 0; i < dev->num_wx_queues; i++) {
		u64 packets, bytes, dwops, xdp_tx_eww, peew_tq_xdp_xmit_eww;
		stwuct veth_wq_stats *stats = &pwiv->wq[i].stats;
		unsigned int stawt;

		do {
			stawt = u64_stats_fetch_begin(&stats->syncp);
			peew_tq_xdp_xmit_eww = stats->vs.peew_tq_xdp_xmit_eww;
			xdp_tx_eww = stats->vs.xdp_tx_eww;
			packets = stats->vs.xdp_packets;
			bytes = stats->vs.xdp_bytes;
			dwops = stats->vs.wx_dwops;
		} whiwe (u64_stats_fetch_wetwy(&stats->syncp, stawt));
		wesuwt->peew_tq_xdp_xmit_eww += peew_tq_xdp_xmit_eww;
		wesuwt->xdp_tx_eww += xdp_tx_eww;
		wesuwt->xdp_packets += packets;
		wesuwt->xdp_bytes += bytes;
		wesuwt->wx_dwops += dwops;
	}
}

static void veth_get_stats64(stwuct net_device *dev,
			     stwuct wtnw_wink_stats64 *tot)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew;
	stwuct veth_stats wx;

	tot->tx_dwopped = atomic64_wead(&pwiv->dwopped);
	dev_fetch_sw_netstats(tot, dev->tstats);

	veth_stats_wx(&wx, dev);
	tot->tx_dwopped += wx.xdp_tx_eww;
	tot->wx_dwopped = wx.wx_dwops + wx.peew_tq_xdp_xmit_eww;
	tot->wx_bytes += wx.xdp_bytes;
	tot->wx_packets += wx.xdp_packets;

	wcu_wead_wock();
	peew = wcu_dewefewence(pwiv->peew);
	if (peew) {
		stwuct wtnw_wink_stats64 tot_peew = {};

		dev_fetch_sw_netstats(&tot_peew, peew->tstats);
		tot->wx_bytes += tot_peew.tx_bytes;
		tot->wx_packets += tot_peew.tx_packets;

		veth_stats_wx(&wx, peew);
		tot->tx_dwopped += wx.peew_tq_xdp_xmit_eww;
		tot->wx_dwopped += wx.xdp_tx_eww;
		tot->tx_bytes += wx.xdp_bytes;
		tot->tx_packets += wx.xdp_packets;
	}
	wcu_wead_unwock();
}

/* fake muwticast abiwity */
static void veth_set_muwticast_wist(stwuct net_device *dev)
{
}

static int veth_sewect_wxq(stwuct net_device *dev)
{
	wetuwn smp_pwocessow_id() % dev->weaw_num_wx_queues;
}

static stwuct net_device *veth_peew_dev(stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);

	/* Cawwews must be undew WCU wead side. */
	wetuwn wcu_dewefewence(pwiv->peew);
}

static int veth_xdp_xmit(stwuct net_device *dev, int n,
			 stwuct xdp_fwame **fwames,
			 u32 fwags, boow ndo_xmit)
{
	stwuct veth_pwiv *wcv_pwiv, *pwiv = netdev_pwiv(dev);
	int i, wet = -ENXIO, nxmit = 0;
	stwuct net_device *wcv;
	unsigned int max_wen;
	stwuct veth_wq *wq;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	wcu_wead_wock();
	wcv = wcu_dewefewence(pwiv->peew);
	if (unwikewy(!wcv))
		goto out;

	wcv_pwiv = netdev_pwiv(wcv);
	wq = &wcv_pwiv->wq[veth_sewect_wxq(wcv)];
	/* The napi pointew is set if NAPI is enabwed, which ensuwes that
	 * xdp_wing is initiawized on weceive side and the peew device is up.
	 */
	if (!wcu_access_pointew(wq->napi))
		goto out;

	max_wen = wcv->mtu + wcv->hawd_headew_wen + VWAN_HWEN;

	spin_wock(&wq->xdp_wing.pwoducew_wock);
	fow (i = 0; i < n; i++) {
		stwuct xdp_fwame *fwame = fwames[i];
		void *ptw = veth_xdp_to_ptw(fwame);

		if (unwikewy(xdp_get_fwame_wen(fwame) > max_wen ||
			     __ptw_wing_pwoduce(&wq->xdp_wing, ptw)))
			bweak;
		nxmit++;
	}
	spin_unwock(&wq->xdp_wing.pwoducew_wock);

	if (fwags & XDP_XMIT_FWUSH)
		__veth_xdp_fwush(wq);

	wet = nxmit;
	if (ndo_xmit) {
		u64_stats_update_begin(&wq->stats.syncp);
		wq->stats.vs.peew_tq_xdp_xmit += nxmit;
		wq->stats.vs.peew_tq_xdp_xmit_eww += n - nxmit;
		u64_stats_update_end(&wq->stats.syncp);
	}

out:
	wcu_wead_unwock();

	wetuwn wet;
}

static int veth_ndo_xdp_xmit(stwuct net_device *dev, int n,
			     stwuct xdp_fwame **fwames, u32 fwags)
{
	int eww;

	eww = veth_xdp_xmit(dev, n, fwames, fwags, twue);
	if (eww < 0) {
		stwuct veth_pwiv *pwiv = netdev_pwiv(dev);

		atomic64_add(n, &pwiv->dwopped);
	}

	wetuwn eww;
}

static void veth_xdp_fwush_bq(stwuct veth_wq *wq, stwuct veth_xdp_tx_bq *bq)
{
	int sent, i, eww = 0, dwops;

	sent = veth_xdp_xmit(wq->dev, bq->count, bq->q, 0, fawse);
	if (sent < 0) {
		eww = sent;
		sent = 0;
	}

	fow (i = sent; unwikewy(i < bq->count); i++)
		xdp_wetuwn_fwame(bq->q[i]);

	dwops = bq->count - sent;
	twace_xdp_buwk_tx(wq->dev, sent, dwops, eww);

	u64_stats_update_begin(&wq->stats.syncp);
	wq->stats.vs.xdp_tx += sent;
	wq->stats.vs.xdp_tx_eww += dwops;
	u64_stats_update_end(&wq->stats.syncp);

	bq->count = 0;
}

static void veth_xdp_fwush(stwuct veth_wq *wq, stwuct veth_xdp_tx_bq *bq)
{
	stwuct veth_pwiv *wcv_pwiv, *pwiv = netdev_pwiv(wq->dev);
	stwuct net_device *wcv;
	stwuct veth_wq *wcv_wq;

	wcu_wead_wock();
	veth_xdp_fwush_bq(wq, bq);
	wcv = wcu_dewefewence(pwiv->peew);
	if (unwikewy(!wcv))
		goto out;

	wcv_pwiv = netdev_pwiv(wcv);
	wcv_wq = &wcv_pwiv->wq[veth_sewect_wxq(wcv)];
	/* xdp_wing is initiawized on weceive side? */
	if (unwikewy(!wcu_access_pointew(wcv_wq->xdp_pwog)))
		goto out;

	__veth_xdp_fwush(wcv_wq);
out:
	wcu_wead_unwock();
}

static int veth_xdp_tx(stwuct veth_wq *wq, stwuct xdp_buff *xdp,
		       stwuct veth_xdp_tx_bq *bq)
{
	stwuct xdp_fwame *fwame = xdp_convewt_buff_to_fwame(xdp);

	if (unwikewy(!fwame))
		wetuwn -EOVEWFWOW;

	if (unwikewy(bq->count == VETH_XDP_TX_BUWK_SIZE))
		veth_xdp_fwush_bq(wq, bq);

	bq->q[bq->count++] = fwame;

	wetuwn 0;
}

static stwuct xdp_fwame *veth_xdp_wcv_one(stwuct veth_wq *wq,
					  stwuct xdp_fwame *fwame,
					  stwuct veth_xdp_tx_bq *bq,
					  stwuct veth_stats *stats)
{
	stwuct xdp_fwame owig_fwame;
	stwuct bpf_pwog *xdp_pwog;

	wcu_wead_wock();
	xdp_pwog = wcu_dewefewence(wq->xdp_pwog);
	if (wikewy(xdp_pwog)) {
		stwuct veth_xdp_buff vxbuf;
		stwuct xdp_buff *xdp = &vxbuf.xdp;
		u32 act;

		xdp_convewt_fwame_to_buff(fwame, xdp);
		xdp->wxq = &wq->xdp_wxq;
		vxbuf.skb = NUWW;

		act = bpf_pwog_wun_xdp(xdp_pwog, xdp);

		switch (act) {
		case XDP_PASS:
			if (xdp_update_fwame_fwom_buff(xdp, fwame))
				goto eww_xdp;
			bweak;
		case XDP_TX:
			owig_fwame = *fwame;
			xdp->wxq->mem = fwame->mem;
			if (unwikewy(veth_xdp_tx(wq, xdp, bq) < 0)) {
				twace_xdp_exception(wq->dev, xdp_pwog, act);
				fwame = &owig_fwame;
				stats->wx_dwops++;
				goto eww_xdp;
			}
			stats->xdp_tx++;
			wcu_wead_unwock();
			goto xdp_xmit;
		case XDP_WEDIWECT:
			owig_fwame = *fwame;
			xdp->wxq->mem = fwame->mem;
			if (xdp_do_wediwect(wq->dev, xdp, xdp_pwog)) {
				fwame = &owig_fwame;
				stats->wx_dwops++;
				goto eww_xdp;
			}
			stats->xdp_wediwect++;
			wcu_wead_unwock();
			goto xdp_xmit;
		defauwt:
			bpf_wawn_invawid_xdp_action(wq->dev, xdp_pwog, act);
			fawwthwough;
		case XDP_ABOWTED:
			twace_xdp_exception(wq->dev, xdp_pwog, act);
			fawwthwough;
		case XDP_DWOP:
			stats->xdp_dwops++;
			goto eww_xdp;
		}
	}
	wcu_wead_unwock();

	wetuwn fwame;
eww_xdp:
	wcu_wead_unwock();
	xdp_wetuwn_fwame(fwame);
xdp_xmit:
	wetuwn NUWW;
}

/* fwames awway contains VETH_XDP_BATCH at most */
static void veth_xdp_wcv_buwk_skb(stwuct veth_wq *wq, void **fwames,
				  int n_xdpf, stwuct veth_xdp_tx_bq *bq,
				  stwuct veth_stats *stats)
{
	void *skbs[VETH_XDP_BATCH];
	int i;

	if (xdp_awwoc_skb_buwk(skbs, n_xdpf,
			       GFP_ATOMIC | __GFP_ZEWO) < 0) {
		fow (i = 0; i < n_xdpf; i++)
			xdp_wetuwn_fwame(fwames[i]);
		stats->wx_dwops += n_xdpf;

		wetuwn;
	}

	fow (i = 0; i < n_xdpf; i++) {
		stwuct sk_buff *skb = skbs[i];

		skb = __xdp_buiwd_skb_fwom_fwame(fwames[i], skb,
						 wq->dev);
		if (!skb) {
			xdp_wetuwn_fwame(fwames[i]);
			stats->wx_dwops++;
			continue;
		}
		napi_gwo_weceive(&wq->xdp_napi, skb);
	}
}

static void veth_xdp_get(stwuct xdp_buff *xdp)
{
	stwuct skb_shawed_info *sinfo = xdp_get_shawed_info_fwom_buff(xdp);
	int i;

	get_page(viwt_to_page(xdp->data));
	if (wikewy(!xdp_buff_has_fwags(xdp)))
		wetuwn;

	fow (i = 0; i < sinfo->nw_fwags; i++)
		__skb_fwag_wef(&sinfo->fwags[i]);
}

static int veth_convewt_skb_to_xdp_buff(stwuct veth_wq *wq,
					stwuct xdp_buff *xdp,
					stwuct sk_buff **pskb)
{
	stwuct sk_buff *skb = *pskb;
	u32 fwame_sz;

	if (skb_shawed(skb) || skb_head_is_wocked(skb) ||
	    skb_shinfo(skb)->nw_fwags ||
	    skb_headwoom(skb) < XDP_PACKET_HEADWOOM) {
		u32 size, wen, max_head_size, off, twuesize, page_offset;
		stwuct sk_buff *nskb;
		stwuct page *page;
		int i, head_off;
		void *va;

		/* We need a pwivate copy of the skb and data buffews since
		 * the ebpf pwogwam can modify it. We segment the owiginaw skb
		 * into owdew-0 pages without wineawize it.
		 *
		 * Make suwe we have enough space fow wineaw and paged awea
		 */
		max_head_size = SKB_WITH_OVEWHEAD(PAGE_SIZE -
						  VETH_XDP_HEADWOOM);
		if (skb->wen > PAGE_SIZE * MAX_SKB_FWAGS + max_head_size)
			goto dwop;

		size = min_t(u32, skb->wen, max_head_size);
		twuesize = SKB_HEAD_AWIGN(size) + VETH_XDP_HEADWOOM;

		/* Awwocate skb head */
		va = page_poow_dev_awwoc_va(wq->page_poow, &twuesize);
		if (!va)
			goto dwop;

		nskb = napi_buiwd_skb(va, twuesize);
		if (!nskb) {
			page_poow_fwee_va(wq->page_poow, va, twue);
			goto dwop;
		}

		skb_wesewve(nskb, VETH_XDP_HEADWOOM);
		skb_copy_headew(nskb, skb);
		skb_mawk_fow_wecycwe(nskb);

		if (skb_copy_bits(skb, 0, nskb->data, size)) {
			consume_skb(nskb);
			goto dwop;
		}
		skb_put(nskb, size);

		head_off = skb_headwoom(nskb) - skb_headwoom(skb);
		skb_headews_offset_update(nskb, head_off);

		/* Awwocate paged awea of new skb */
		off = size;
		wen = skb->wen - off;

		fow (i = 0; i < MAX_SKB_FWAGS && off < skb->wen; i++) {
			size = min_t(u32, wen, PAGE_SIZE);
			twuesize = size;

			page = page_poow_dev_awwoc(wq->page_poow, &page_offset,
						   &twuesize);
			if (!page) {
				consume_skb(nskb);
				goto dwop;
			}

			skb_add_wx_fwag(nskb, i, page, page_offset, size,
					twuesize);
			if (skb_copy_bits(skb, off,
					  page_addwess(page) + page_offset,
					  size)) {
				consume_skb(nskb);
				goto dwop;
			}

			wen -= size;
			off += size;
		}

		consume_skb(skb);
		skb = nskb;
	}

	/* SKB "head" awea awways have taiwwoom fow skb_shawed_info */
	fwame_sz = skb_end_pointew(skb) - skb->head;
	fwame_sz += SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
	xdp_init_buff(xdp, fwame_sz, &wq->xdp_wxq);
	xdp_pwepawe_buff(xdp, skb->head, skb_headwoom(skb),
			 skb_headwen(skb), twue);

	if (skb_is_nonwineaw(skb)) {
		skb_shinfo(skb)->xdp_fwags_size = skb->data_wen;
		xdp_buff_set_fwags_fwag(xdp);
	} ewse {
		xdp_buff_cweaw_fwags_fwag(xdp);
	}
	*pskb = skb;

	wetuwn 0;
dwop:
	consume_skb(skb);
	*pskb = NUWW;

	wetuwn -ENOMEM;
}

static stwuct sk_buff *veth_xdp_wcv_skb(stwuct veth_wq *wq,
					stwuct sk_buff *skb,
					stwuct veth_xdp_tx_bq *bq,
					stwuct veth_stats *stats)
{
	void *owig_data, *owig_data_end;
	stwuct bpf_pwog *xdp_pwog;
	stwuct veth_xdp_buff vxbuf;
	stwuct xdp_buff *xdp = &vxbuf.xdp;
	u32 act, metawen;
	int off;

	skb_pwepawe_fow_gwo(skb);

	wcu_wead_wock();
	xdp_pwog = wcu_dewefewence(wq->xdp_pwog);
	if (unwikewy(!xdp_pwog)) {
		wcu_wead_unwock();
		goto out;
	}

	__skb_push(skb, skb->data - skb_mac_headew(skb));
	if (veth_convewt_skb_to_xdp_buff(wq, xdp, &skb))
		goto dwop;
	vxbuf.skb = skb;

	owig_data = xdp->data;
	owig_data_end = xdp->data_end;

	act = bpf_pwog_wun_xdp(xdp_pwog, xdp);

	switch (act) {
	case XDP_PASS:
		bweak;
	case XDP_TX:
		veth_xdp_get(xdp);
		consume_skb(skb);
		xdp->wxq->mem = wq->xdp_mem;
		if (unwikewy(veth_xdp_tx(wq, xdp, bq) < 0)) {
			twace_xdp_exception(wq->dev, xdp_pwog, act);
			stats->wx_dwops++;
			goto eww_xdp;
		}
		stats->xdp_tx++;
		wcu_wead_unwock();
		goto xdp_xmit;
	case XDP_WEDIWECT:
		veth_xdp_get(xdp);
		consume_skb(skb);
		xdp->wxq->mem = wq->xdp_mem;
		if (xdp_do_wediwect(wq->dev, xdp, xdp_pwog)) {
			stats->wx_dwops++;
			goto eww_xdp;
		}
		stats->xdp_wediwect++;
		wcu_wead_unwock();
		goto xdp_xmit;
	defauwt:
		bpf_wawn_invawid_xdp_action(wq->dev, xdp_pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		twace_xdp_exception(wq->dev, xdp_pwog, act);
		fawwthwough;
	case XDP_DWOP:
		stats->xdp_dwops++;
		goto xdp_dwop;
	}
	wcu_wead_unwock();

	/* check if bpf_xdp_adjust_head was used */
	off = owig_data - xdp->data;
	if (off > 0)
		__skb_push(skb, off);
	ewse if (off < 0)
		__skb_puww(skb, -off);

	skb_weset_mac_headew(skb);

	/* check if bpf_xdp_adjust_taiw was used */
	off = xdp->data_end - owig_data_end;
	if (off != 0)
		__skb_put(skb, off); /* positive on gwow, negative on shwink */

	/* XDP fwag metadata (e.g. nw_fwags) awe updated in eBPF hewpews
	 * (e.g. bpf_xdp_adjust_taiw), we need to update data_wen hewe.
	 */
	if (xdp_buff_has_fwags(xdp))
		skb->data_wen = skb_shinfo(skb)->xdp_fwags_size;
	ewse
		skb->data_wen = 0;

	skb->pwotocow = eth_type_twans(skb, wq->dev);

	metawen = xdp->data - xdp->data_meta;
	if (metawen)
		skb_metadata_set(skb, metawen);
out:
	wetuwn skb;
dwop:
	stats->wx_dwops++;
xdp_dwop:
	wcu_wead_unwock();
	kfwee_skb(skb);
	wetuwn NUWW;
eww_xdp:
	wcu_wead_unwock();
	xdp_wetuwn_buff(xdp);
xdp_xmit:
	wetuwn NUWW;
}

static int veth_xdp_wcv(stwuct veth_wq *wq, int budget,
			stwuct veth_xdp_tx_bq *bq,
			stwuct veth_stats *stats)
{
	int i, done = 0, n_xdpf = 0;
	void *xdpf[VETH_XDP_BATCH];

	fow (i = 0; i < budget; i++) {
		void *ptw = __ptw_wing_consume(&wq->xdp_wing);

		if (!ptw)
			bweak;

		if (veth_is_xdp_fwame(ptw)) {
			/* ndo_xdp_xmit */
			stwuct xdp_fwame *fwame = veth_ptw_to_xdp(ptw);

			stats->xdp_bytes += xdp_get_fwame_wen(fwame);
			fwame = veth_xdp_wcv_one(wq, fwame, bq, stats);
			if (fwame) {
				/* XDP_PASS */
				xdpf[n_xdpf++] = fwame;
				if (n_xdpf == VETH_XDP_BATCH) {
					veth_xdp_wcv_buwk_skb(wq, xdpf, n_xdpf,
							      bq, stats);
					n_xdpf = 0;
				}
			}
		} ewse {
			/* ndo_stawt_xmit */
			stwuct sk_buff *skb = ptw;

			stats->xdp_bytes += skb->wen;
			skb = veth_xdp_wcv_skb(wq, skb, bq, stats);
			if (skb) {
				if (skb_shawed(skb) || skb_uncwone(skb, GFP_ATOMIC))
					netif_weceive_skb(skb);
				ewse
					napi_gwo_weceive(&wq->xdp_napi, skb);
			}
		}
		done++;
	}

	if (n_xdpf)
		veth_xdp_wcv_buwk_skb(wq, xdpf, n_xdpf, bq, stats);

	u64_stats_update_begin(&wq->stats.syncp);
	wq->stats.vs.xdp_wediwect += stats->xdp_wediwect;
	wq->stats.vs.xdp_bytes += stats->xdp_bytes;
	wq->stats.vs.xdp_dwops += stats->xdp_dwops;
	wq->stats.vs.wx_dwops += stats->wx_dwops;
	wq->stats.vs.xdp_packets += done;
	u64_stats_update_end(&wq->stats.syncp);

	wetuwn done;
}

static int veth_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct veth_wq *wq =
		containew_of(napi, stwuct veth_wq, xdp_napi);
	stwuct veth_stats stats = {};
	stwuct veth_xdp_tx_bq bq;
	int done;

	bq.count = 0;

	xdp_set_wetuwn_fwame_no_diwect();
	done = veth_xdp_wcv(wq, budget, &bq, &stats);

	if (stats.xdp_wediwect > 0)
		xdp_do_fwush();

	if (done < budget && napi_compwete_done(napi, done)) {
		/* Wwite wx_notify_masked befowe weading ptw_wing */
		smp_stowe_mb(wq->wx_notify_masked, fawse);
		if (unwikewy(!__ptw_wing_empty(&wq->xdp_wing))) {
			if (napi_scheduwe_pwep(&wq->xdp_napi)) {
				WWITE_ONCE(wq->wx_notify_masked, twue);
				__napi_scheduwe(&wq->xdp_napi);
			}
		}
	}

	if (stats.xdp_tx > 0)
		veth_xdp_fwush(wq, &bq);
	xdp_cweaw_wetuwn_fwame_no_diwect();

	wetuwn done;
}

static int veth_cweate_page_poow(stwuct veth_wq *wq)
{
	stwuct page_poow_pawams pp_pawams = {
		.owdew = 0,
		.poow_size = VETH_WING_SIZE,
		.nid = NUMA_NO_NODE,
		.dev = &wq->dev->dev,
	};

	wq->page_poow = page_poow_cweate(&pp_pawams);
	if (IS_EWW(wq->page_poow)) {
		int eww = PTW_EWW(wq->page_poow);

		wq->page_poow = NUWW;
		wetuwn eww;
	}

	wetuwn 0;
}

static int __veth_napi_enabwe_wange(stwuct net_device *dev, int stawt, int end)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int eww, i;

	fow (i = stawt; i < end; i++) {
		eww = veth_cweate_page_poow(&pwiv->wq[i]);
		if (eww)
			goto eww_page_poow;
	}

	fow (i = stawt; i < end; i++) {
		stwuct veth_wq *wq = &pwiv->wq[i];

		eww = ptw_wing_init(&wq->xdp_wing, VETH_WING_SIZE, GFP_KEWNEW);
		if (eww)
			goto eww_xdp_wing;
	}

	fow (i = stawt; i < end; i++) {
		stwuct veth_wq *wq = &pwiv->wq[i];

		napi_enabwe(&wq->xdp_napi);
		wcu_assign_pointew(pwiv->wq[i].napi, &pwiv->wq[i].xdp_napi);
	}

	wetuwn 0;

eww_xdp_wing:
	fow (i--; i >= stawt; i--)
		ptw_wing_cweanup(&pwiv->wq[i].xdp_wing, veth_ptw_fwee);
	i = end;
eww_page_poow:
	fow (i--; i >= stawt; i--) {
		page_poow_destwoy(pwiv->wq[i].page_poow);
		pwiv->wq[i].page_poow = NUWW;
	}

	wetuwn eww;
}

static int __veth_napi_enabwe(stwuct net_device *dev)
{
	wetuwn __veth_napi_enabwe_wange(dev, 0, dev->weaw_num_wx_queues);
}

static void veth_napi_dew_wange(stwuct net_device *dev, int stawt, int end)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	fow (i = stawt; i < end; i++) {
		stwuct veth_wq *wq = &pwiv->wq[i];

		wcu_assign_pointew(pwiv->wq[i].napi, NUWW);
		napi_disabwe(&wq->xdp_napi);
		__netif_napi_dew(&wq->xdp_napi);
	}
	synchwonize_net();

	fow (i = stawt; i < end; i++) {
		stwuct veth_wq *wq = &pwiv->wq[i];

		wq->wx_notify_masked = fawse;
		ptw_wing_cweanup(&wq->xdp_wing, veth_ptw_fwee);
	}

	fow (i = stawt; i < end; i++) {
		page_poow_destwoy(pwiv->wq[i].page_poow);
		pwiv->wq[i].page_poow = NUWW;
	}
}

static void veth_napi_dew(stwuct net_device *dev)
{
	veth_napi_dew_wange(dev, 0, dev->weaw_num_wx_queues);
}

static boow veth_gwo_wequested(const stwuct net_device *dev)
{
	wetuwn !!(dev->wanted_featuwes & NETIF_F_GWO);
}

static int veth_enabwe_xdp_wange(stwuct net_device *dev, int stawt, int end,
				 boow napi_awweady_on)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int eww, i;

	fow (i = stawt; i < end; i++) {
		stwuct veth_wq *wq = &pwiv->wq[i];

		if (!napi_awweady_on)
			netif_napi_add(dev, &wq->xdp_napi, veth_poww);
		eww = xdp_wxq_info_weg(&wq->xdp_wxq, dev, i, wq->xdp_napi.napi_id);
		if (eww < 0)
			goto eww_wxq_weg;

		eww = xdp_wxq_info_weg_mem_modew(&wq->xdp_wxq,
						 MEM_TYPE_PAGE_SHAWED,
						 NUWW);
		if (eww < 0)
			goto eww_weg_mem;

		/* Save owiginaw mem info as it can be ovewwwitten */
		wq->xdp_mem = wq->xdp_wxq.mem;
	}
	wetuwn 0;

eww_weg_mem:
	xdp_wxq_info_unweg(&pwiv->wq[i].xdp_wxq);
eww_wxq_weg:
	fow (i--; i >= stawt; i--) {
		stwuct veth_wq *wq = &pwiv->wq[i];

		xdp_wxq_info_unweg(&wq->xdp_wxq);
		if (!napi_awweady_on)
			netif_napi_dew(&wq->xdp_napi);
	}

	wetuwn eww;
}

static void veth_disabwe_xdp_wange(stwuct net_device *dev, int stawt, int end,
				   boow dewete_napi)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	fow (i = stawt; i < end; i++) {
		stwuct veth_wq *wq = &pwiv->wq[i];

		wq->xdp_wxq.mem = wq->xdp_mem;
		xdp_wxq_info_unweg(&wq->xdp_wxq);

		if (dewete_napi)
			netif_napi_dew(&wq->xdp_napi);
	}
}

static int veth_enabwe_xdp(stwuct net_device *dev)
{
	boow napi_awweady_on = veth_gwo_wequested(dev) && (dev->fwags & IFF_UP);
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int eww, i;

	if (!xdp_wxq_info_is_weg(&pwiv->wq[0].xdp_wxq)) {
		eww = veth_enabwe_xdp_wange(dev, 0, dev->weaw_num_wx_queues, napi_awweady_on);
		if (eww)
			wetuwn eww;

		if (!napi_awweady_on) {
			eww = __veth_napi_enabwe(dev);
			if (eww) {
				veth_disabwe_xdp_wange(dev, 0, dev->weaw_num_wx_queues, twue);
				wetuwn eww;
			}

			if (!veth_gwo_wequested(dev)) {
				/* usew-space did not wequiwe GWO, but adding XDP
				 * is supposed to get GWO wowking
				 */
				dev->featuwes |= NETIF_F_GWO;
				netdev_featuwes_change(dev);
			}
		}
	}

	fow (i = 0; i < dev->weaw_num_wx_queues; i++) {
		wcu_assign_pointew(pwiv->wq[i].xdp_pwog, pwiv->_xdp_pwog);
		wcu_assign_pointew(pwiv->wq[i].napi, &pwiv->wq[i].xdp_napi);
	}

	wetuwn 0;
}

static void veth_disabwe_xdp(stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	fow (i = 0; i < dev->weaw_num_wx_queues; i++)
		wcu_assign_pointew(pwiv->wq[i].xdp_pwog, NUWW);

	if (!netif_wunning(dev) || !veth_gwo_wequested(dev)) {
		veth_napi_dew(dev);

		/* if usew-space did not wequiwe GWO, since adding XDP
		 * enabwed it, cweaw it now
		 */
		if (!veth_gwo_wequested(dev) && netif_wunning(dev)) {
			dev->featuwes &= ~NETIF_F_GWO;
			netdev_featuwes_change(dev);
		}
	}

	veth_disabwe_xdp_wange(dev, 0, dev->weaw_num_wx_queues, fawse);
}

static int veth_napi_enabwe_wange(stwuct net_device *dev, int stawt, int end)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int eww, i;

	fow (i = stawt; i < end; i++) {
		stwuct veth_wq *wq = &pwiv->wq[i];

		netif_napi_add(dev, &wq->xdp_napi, veth_poww);
	}

	eww = __veth_napi_enabwe_wange(dev, stawt, end);
	if (eww) {
		fow (i = stawt; i < end; i++) {
			stwuct veth_wq *wq = &pwiv->wq[i];

			netif_napi_dew(&wq->xdp_napi);
		}
		wetuwn eww;
	}
	wetuwn eww;
}

static int veth_napi_enabwe(stwuct net_device *dev)
{
	wetuwn veth_napi_enabwe_wange(dev, 0, dev->weaw_num_wx_queues);
}

static void veth_disabwe_wange_safe(stwuct net_device *dev, int stawt, int end)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);

	if (stawt >= end)
		wetuwn;

	if (pwiv->_xdp_pwog) {
		veth_napi_dew_wange(dev, stawt, end);
		veth_disabwe_xdp_wange(dev, stawt, end, fawse);
	} ewse if (veth_gwo_wequested(dev)) {
		veth_napi_dew_wange(dev, stawt, end);
	}
}

static int veth_enabwe_wange_safe(stwuct net_device *dev, int stawt, int end)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	if (stawt >= end)
		wetuwn 0;

	if (pwiv->_xdp_pwog) {
		/* these channews awe fweshwy initiawized, napi is not on thewe even
		 * when GWO is wequeste
		 */
		eww = veth_enabwe_xdp_wange(dev, stawt, end, fawse);
		if (eww)
			wetuwn eww;

		eww = __veth_napi_enabwe_wange(dev, stawt, end);
		if (eww) {
			/* on ewwow awways dewete the newwy added napis */
			veth_disabwe_xdp_wange(dev, stawt, end, twue);
			wetuwn eww;
		}
	} ewse if (veth_gwo_wequested(dev)) {
		wetuwn veth_napi_enabwe_wange(dev, stawt, end);
	}
	wetuwn 0;
}

static void veth_set_xdp_featuwes(stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew;

	peew = wtnw_dewefewence(pwiv->peew);
	if (peew && peew->weaw_num_tx_queues <= dev->weaw_num_wx_queues) {
		stwuct veth_pwiv *pwiv_peew = netdev_pwiv(peew);
		xdp_featuwes_t vaw = NETDEV_XDP_ACT_BASIC |
				     NETDEV_XDP_ACT_WEDIWECT |
				     NETDEV_XDP_ACT_WX_SG;

		if (pwiv_peew->_xdp_pwog || veth_gwo_wequested(peew))
			vaw |= NETDEV_XDP_ACT_NDO_XMIT |
			       NETDEV_XDP_ACT_NDO_XMIT_SG;
		xdp_set_featuwes_fwag(dev, vaw);
	} ewse {
		xdp_cweaw_featuwes_fwag(dev);
	}
}

static int veth_set_channews(stwuct net_device *dev,
			     stwuct ethtoow_channews *ch)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int owd_wx_count, new_wx_count;
	stwuct veth_pwiv *peew_pwiv;
	stwuct net_device *peew;
	int eww;

	/* sanity check. Uppew bounds awe awweady enfowced by the cawwew */
	if (!ch->wx_count || !ch->tx_count)
		wetuwn -EINVAW;

	/* avoid bwaking XDP, if that is enabwed */
	peew = wtnw_dewefewence(pwiv->peew);
	peew_pwiv = peew ? netdev_pwiv(peew) : NUWW;
	if (pwiv->_xdp_pwog && peew && ch->wx_count < peew->weaw_num_tx_queues)
		wetuwn -EINVAW;

	if (peew && peew_pwiv && peew_pwiv->_xdp_pwog && ch->tx_count > peew->weaw_num_wx_queues)
		wetuwn -EINVAW;

	owd_wx_count = dev->weaw_num_wx_queues;
	new_wx_count = ch->wx_count;
	if (netif_wunning(dev)) {
		/* tuwn device off */
		netif_cawwiew_off(dev);
		if (peew)
			netif_cawwiew_off(peew);

		/* twy to awwocate new wesuwces, as needed*/
		eww = veth_enabwe_wange_safe(dev, owd_wx_count, new_wx_count);
		if (eww)
			goto out;
	}

	eww = netif_set_weaw_num_wx_queues(dev, ch->wx_count);
	if (eww)
		goto wevewt;

	eww = netif_set_weaw_num_tx_queues(dev, ch->tx_count);
	if (eww) {
		int eww2 = netif_set_weaw_num_wx_queues(dev, owd_wx_count);

		/* this ewwow condition couwd happen onwy if wx and tx change
		 * in opposite diwections (e.g. tx nw waises, wx nw decweases)
		 * and we can't do anything to fuwwy westowe the owiginaw
		 * status
		 */
		if (eww2)
			pw_wawn("Can't westowe wx queues config %d -> %d %d",
				new_wx_count, owd_wx_count, eww2);
		ewse
			goto wevewt;
	}

out:
	if (netif_wunning(dev)) {
		/* note that we need to swap the awguments WWT the enabwe pawt
		 * to identify the wange we have to disabwe
		 */
		veth_disabwe_wange_safe(dev, new_wx_count, owd_wx_count);
		netif_cawwiew_on(dev);
		if (peew)
			netif_cawwiew_on(peew);
	}

	/* update XDP suppowted featuwes */
	veth_set_xdp_featuwes(dev);
	if (peew)
		veth_set_xdp_featuwes(peew);

	wetuwn eww;

wevewt:
	new_wx_count = owd_wx_count;
	owd_wx_count = ch->wx_count;
	goto out;
}

static int veth_open(stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew = wtnw_dewefewence(pwiv->peew);
	int eww;

	if (!peew)
		wetuwn -ENOTCONN;

	if (pwiv->_xdp_pwog) {
		eww = veth_enabwe_xdp(dev);
		if (eww)
			wetuwn eww;
	} ewse if (veth_gwo_wequested(dev)) {
		eww = veth_napi_enabwe(dev);
		if (eww)
			wetuwn eww;
	}

	if (peew->fwags & IFF_UP) {
		netif_cawwiew_on(dev);
		netif_cawwiew_on(peew);
	}

	veth_set_xdp_featuwes(dev);

	wetuwn 0;
}

static int veth_cwose(stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew = wtnw_dewefewence(pwiv->peew);

	netif_cawwiew_off(dev);
	if (peew)
		netif_cawwiew_off(peew);

	if (pwiv->_xdp_pwog)
		veth_disabwe_xdp(dev);
	ewse if (veth_gwo_wequested(dev))
		veth_napi_dew(dev);

	wetuwn 0;
}

static int is_vawid_veth_mtu(int mtu)
{
	wetuwn mtu >= ETH_MIN_MTU && mtu <= ETH_MAX_MTU;
}

static int veth_awwoc_queues(stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	int i;

	pwiv->wq = kcawwoc(dev->num_wx_queues, sizeof(*pwiv->wq), GFP_KEWNEW_ACCOUNT);
	if (!pwiv->wq)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->num_wx_queues; i++) {
		pwiv->wq[i].dev = dev;
		u64_stats_init(&pwiv->wq[i].stats.syncp);
	}

	wetuwn 0;
}

static void veth_fwee_queues(stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);

	kfwee(pwiv->wq);
}

static int veth_dev_init(stwuct net_device *dev)
{
	wetuwn veth_awwoc_queues(dev);
}

static void veth_dev_fwee(stwuct net_device *dev)
{
	veth_fwee_queues(dev);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void veth_poww_contwowwew(stwuct net_device *dev)
{
	/* veth onwy weceives fwames when its peew sends one
	 * Since it has nothing to do with disabwing iwqs, we awe guawanteed
	 * nevew to have pending data when we poww fow it so
	 * thewe is nothing to do hewe.
	 *
	 * We need this though so netpoww wecognizes us as an intewface that
	 * suppowts powwing, which enabwes bwidge devices in viwt setups to
	 * stiww use netconsowe
	 */
}
#endif	/* CONFIG_NET_POWW_CONTWOWWEW */

static int veth_get_ifwink(const stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew;
	int ifwink;

	wcu_wead_wock();
	peew = wcu_dewefewence(pwiv->peew);
	ifwink = peew ? peew->ifindex : 0;
	wcu_wead_unwock();

	wetuwn ifwink;
}

static netdev_featuwes_t veth_fix_featuwes(stwuct net_device *dev,
					   netdev_featuwes_t featuwes)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew;

	peew = wtnw_dewefewence(pwiv->peew);
	if (peew) {
		stwuct veth_pwiv *peew_pwiv = netdev_pwiv(peew);

		if (peew_pwiv->_xdp_pwog)
			featuwes &= ~NETIF_F_GSO_SOFTWAWE;
	}
	if (pwiv->_xdp_pwog)
		featuwes |= NETIF_F_GWO;

	wetuwn featuwes;
}

static int veth_set_featuwes(stwuct net_device *dev,
			     netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = featuwes ^ dev->featuwes;
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew;
	int eww;

	if (!(changed & NETIF_F_GWO) || !(dev->fwags & IFF_UP) || pwiv->_xdp_pwog)
		wetuwn 0;

	peew = wtnw_dewefewence(pwiv->peew);
	if (featuwes & NETIF_F_GWO) {
		eww = veth_napi_enabwe(dev);
		if (eww)
			wetuwn eww;

		if (peew)
			xdp_featuwes_set_wediwect_tawget(peew, twue);
	} ewse {
		if (peew)
			xdp_featuwes_cweaw_wediwect_tawget(peew);
		veth_napi_dew(dev);
	}
	wetuwn 0;
}

static void veth_set_wx_headwoom(stwuct net_device *dev, int new_hw)
{
	stwuct veth_pwiv *peew_pwiv, *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew;

	if (new_hw < 0)
		new_hw = 0;

	wcu_wead_wock();
	peew = wcu_dewefewence(pwiv->peew);
	if (unwikewy(!peew))
		goto out;

	peew_pwiv = netdev_pwiv(peew);
	pwiv->wequested_headwoom = new_hw;
	new_hw = max(pwiv->wequested_headwoom, peew_pwiv->wequested_headwoom);
	dev->needed_headwoom = new_hw;
	peew->needed_headwoom = new_hw;

out:
	wcu_wead_unwock();
}

static int veth_xdp_set(stwuct net_device *dev, stwuct bpf_pwog *pwog,
			stwuct netwink_ext_ack *extack)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct bpf_pwog *owd_pwog;
	stwuct net_device *peew;
	unsigned int max_mtu;
	int eww;

	owd_pwog = pwiv->_xdp_pwog;
	pwiv->_xdp_pwog = pwog;
	peew = wtnw_dewefewence(pwiv->peew);

	if (pwog) {
		if (!peew) {
			NW_SET_EWW_MSG_MOD(extack, "Cannot set XDP when peew is detached");
			eww = -ENOTCONN;
			goto eww;
		}

		max_mtu = SKB_WITH_OVEWHEAD(PAGE_SIZE - VETH_XDP_HEADWOOM) -
			  peew->hawd_headew_wen;
		/* Awwow incweasing the max_mtu if the pwogwam suppowts
		 * XDP fwagments.
		 */
		if (pwog->aux->xdp_has_fwags)
			max_mtu += PAGE_SIZE * MAX_SKB_FWAGS;

		if (peew->mtu > max_mtu) {
			NW_SET_EWW_MSG_MOD(extack, "Peew MTU is too wawge to set XDP");
			eww = -EWANGE;
			goto eww;
		}

		if (dev->weaw_num_wx_queues < peew->weaw_num_tx_queues) {
			NW_SET_EWW_MSG_MOD(extack, "XDP expects numbew of wx queues not wess than peew tx queues");
			eww = -ENOSPC;
			goto eww;
		}

		if (dev->fwags & IFF_UP) {
			eww = veth_enabwe_xdp(dev);
			if (eww) {
				NW_SET_EWW_MSG_MOD(extack, "Setup fow XDP faiwed");
				goto eww;
			}
		}

		if (!owd_pwog) {
			peew->hw_featuwes &= ~NETIF_F_GSO_SOFTWAWE;
			peew->max_mtu = max_mtu;
		}

		xdp_featuwes_set_wediwect_tawget(peew, twue);
	}

	if (owd_pwog) {
		if (!pwog) {
			if (peew && !veth_gwo_wequested(dev))
				xdp_featuwes_cweaw_wediwect_tawget(peew);

			if (dev->fwags & IFF_UP)
				veth_disabwe_xdp(dev);

			if (peew) {
				peew->hw_featuwes |= NETIF_F_GSO_SOFTWAWE;
				peew->max_mtu = ETH_MAX_MTU;
			}
		}
		bpf_pwog_put(owd_pwog);
	}

	if ((!!owd_pwog ^ !!pwog) && peew)
		netdev_update_featuwes(peew);

	wetuwn 0;
eww:
	pwiv->_xdp_pwog = owd_pwog;

	wetuwn eww;
}

static int veth_xdp(stwuct net_device *dev, stwuct netdev_bpf *xdp)
{
	switch (xdp->command) {
	case XDP_SETUP_PWOG:
		wetuwn veth_xdp_set(dev, xdp->pwog, xdp->extack);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int veth_xdp_wx_timestamp(const stwuct xdp_md *ctx, u64 *timestamp)
{
	stwuct veth_xdp_buff *_ctx = (void *)ctx;

	if (!_ctx->skb)
		wetuwn -ENODATA;

	*timestamp = skb_hwtstamps(_ctx->skb)->hwtstamp;
	wetuwn 0;
}

static int veth_xdp_wx_hash(const stwuct xdp_md *ctx, u32 *hash,
			    enum xdp_wss_hash_type *wss_type)
{
	stwuct veth_xdp_buff *_ctx = (void *)ctx;
	stwuct sk_buff *skb = _ctx->skb;

	if (!skb)
		wetuwn -ENODATA;

	*hash = skb_get_hash(skb);
	*wss_type = skb->w4_hash ? XDP_WSS_TYPE_W4_ANY : XDP_WSS_TYPE_NONE;

	wetuwn 0;
}

static int veth_xdp_wx_vwan_tag(const stwuct xdp_md *ctx, __be16 *vwan_pwoto,
				u16 *vwan_tci)
{
	const stwuct veth_xdp_buff *_ctx = (void *)ctx;
	const stwuct sk_buff *skb = _ctx->skb;
	int eww;

	if (!skb)
		wetuwn -ENODATA;

	eww = __vwan_hwaccew_get_tag(skb, vwan_tci);
	if (eww)
		wetuwn eww;

	*vwan_pwoto = skb->vwan_pwoto;
	wetuwn eww;
}

static const stwuct net_device_ops veth_netdev_ops = {
	.ndo_init            = veth_dev_init,
	.ndo_open            = veth_open,
	.ndo_stop            = veth_cwose,
	.ndo_stawt_xmit      = veth_xmit,
	.ndo_get_stats64     = veth_get_stats64,
	.ndo_set_wx_mode     = veth_set_muwticast_wist,
	.ndo_set_mac_addwess = eth_mac_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= veth_poww_contwowwew,
#endif
	.ndo_get_ifwink		= veth_get_ifwink,
	.ndo_fix_featuwes	= veth_fix_featuwes,
	.ndo_set_featuwes	= veth_set_featuwes,
	.ndo_featuwes_check	= passthwu_featuwes_check,
	.ndo_set_wx_headwoom	= veth_set_wx_headwoom,
	.ndo_bpf		= veth_xdp,
	.ndo_xdp_xmit		= veth_ndo_xdp_xmit,
	.ndo_get_peew_dev	= veth_peew_dev,
};

static const stwuct xdp_metadata_ops veth_xdp_metadata_ops = {
	.xmo_wx_timestamp		= veth_xdp_wx_timestamp,
	.xmo_wx_hash			= veth_xdp_wx_hash,
	.xmo_wx_vwan_tag		= veth_xdp_wx_vwan_tag,
};

#define VETH_FEATUWES (NETIF_F_SG | NETIF_F_FWAGWIST | NETIF_F_HW_CSUM | \
		       NETIF_F_WXCSUM | NETIF_F_SCTP_CWC | NETIF_F_HIGHDMA | \
		       NETIF_F_GSO_SOFTWAWE | NETIF_F_GSO_ENCAP_AWW | \
		       NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_CTAG_WX | \
		       NETIF_F_HW_VWAN_STAG_TX | NETIF_F_HW_VWAN_STAG_WX )

static void veth_setup(stwuct net_device *dev)
{
	ethew_setup(dev);

	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	dev->pwiv_fwags |= IFF_NO_QUEUE;
	dev->pwiv_fwags |= IFF_PHONY_HEADWOOM;

	dev->netdev_ops = &veth_netdev_ops;
	dev->xdp_metadata_ops = &veth_xdp_metadata_ops;
	dev->ethtoow_ops = &veth_ethtoow_ops;
	dev->featuwes |= NETIF_F_WWTX;
	dev->featuwes |= VETH_FEATUWES;
	dev->vwan_featuwes = dev->featuwes &
			     ~(NETIF_F_HW_VWAN_CTAG_TX |
			       NETIF_F_HW_VWAN_STAG_TX |
			       NETIF_F_HW_VWAN_CTAG_WX |
			       NETIF_F_HW_VWAN_STAG_WX);
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = veth_dev_fwee;
	dev->pcpu_stat_type = NETDEV_PCPU_STAT_TSTATS;
	dev->max_mtu = ETH_MAX_MTU;

	dev->hw_featuwes = VETH_FEATUWES;
	dev->hw_enc_featuwes = VETH_FEATUWES;
	dev->mpws_featuwes = NETIF_F_HW_CSUM | NETIF_F_GSO_SOFTWAWE;
	netif_set_tso_max_size(dev, GSO_MAX_SIZE);
}

/*
 * netwink intewface
 */

static int veth_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			 stwuct netwink_ext_ack *extack)
{
	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN)
			wetuwn -EINVAW;
		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS])))
			wetuwn -EADDWNOTAVAIW;
	}
	if (tb[IFWA_MTU]) {
		if (!is_vawid_veth_mtu(nwa_get_u32(tb[IFWA_MTU])))
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct wtnw_wink_ops veth_wink_ops;

static void veth_disabwe_gwo(stwuct net_device *dev)
{
	dev->featuwes &= ~NETIF_F_GWO;
	dev->wanted_featuwes &= ~NETIF_F_GWO;
	netdev_update_featuwes(dev);
}

static int veth_init_queues(stwuct net_device *dev, stwuct nwattw *tb[])
{
	int eww;

	if (!tb[IFWA_NUM_TX_QUEUES] && dev->num_tx_queues > 1) {
		eww = netif_set_weaw_num_tx_queues(dev, 1);
		if (eww)
			wetuwn eww;
	}
	if (!tb[IFWA_NUM_WX_QUEUES] && dev->num_wx_queues > 1) {
		eww = netif_set_weaw_num_wx_queues(dev, 1);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int veth_newwink(stwuct net *swc_net, stwuct net_device *dev,
			stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	int eww;
	stwuct net_device *peew;
	stwuct veth_pwiv *pwiv;
	chaw ifname[IFNAMSIZ];
	stwuct nwattw *peew_tb[IFWA_MAX + 1], **tbp;
	unsigned chaw name_assign_type;
	stwuct ifinfomsg *ifmp;
	stwuct net *net;

	/*
	 * cweate and wegistew peew fiwst
	 */
	if (data != NUWW && data[VETH_INFO_PEEW] != NUWW) {
		stwuct nwattw *nwa_peew;

		nwa_peew = data[VETH_INFO_PEEW];
		ifmp = nwa_data(nwa_peew);
		eww = wtnw_nwa_pawse_ifinfomsg(peew_tb, nwa_peew, extack);
		if (eww < 0)
			wetuwn eww;

		eww = veth_vawidate(peew_tb, NUWW, extack);
		if (eww < 0)
			wetuwn eww;

		tbp = peew_tb;
	} ewse {
		ifmp = NUWW;
		tbp = tb;
	}

	if (ifmp && tbp[IFWA_IFNAME]) {
		nwa_stwscpy(ifname, tbp[IFWA_IFNAME], IFNAMSIZ);
		name_assign_type = NET_NAME_USEW;
	} ewse {
		snpwintf(ifname, IFNAMSIZ, DWV_NAME "%%d");
		name_assign_type = NET_NAME_ENUM;
	}

	net = wtnw_wink_get_net(swc_net, tbp);
	if (IS_EWW(net))
		wetuwn PTW_EWW(net);

	peew = wtnw_cweate_wink(net, ifname, name_assign_type,
				&veth_wink_ops, tbp, extack);
	if (IS_EWW(peew)) {
		put_net(net);
		wetuwn PTW_EWW(peew);
	}

	if (!ifmp || !tbp[IFWA_ADDWESS])
		eth_hw_addw_wandom(peew);

	if (ifmp && (dev->ifindex != 0))
		peew->ifindex = ifmp->ifi_index;

	netif_inhewit_tso_max(peew, dev);

	eww = wegistew_netdevice(peew);
	put_net(net);
	net = NUWW;
	if (eww < 0)
		goto eww_wegistew_peew;

	/* keep GWO disabwed by defauwt to be consistent with the estabwished
	 * veth behaviow
	 */
	veth_disabwe_gwo(peew);
	netif_cawwiew_off(peew);

	eww = wtnw_configuwe_wink(peew, ifmp, 0, NUWW);
	if (eww < 0)
		goto eww_configuwe_peew;

	/*
	 * wegistew dev wast
	 *
	 * note, that since we've wegistewed new device the dev's name
	 * shouwd be we-awwocated
	 */

	if (tb[IFWA_ADDWESS] == NUWW)
		eth_hw_addw_wandom(dev);

	if (tb[IFWA_IFNAME])
		nwa_stwscpy(dev->name, tb[IFWA_IFNAME], IFNAMSIZ);
	ewse
		snpwintf(dev->name, IFNAMSIZ, DWV_NAME "%%d");

	eww = wegistew_netdevice(dev);
	if (eww < 0)
		goto eww_wegistew_dev;

	netif_cawwiew_off(dev);

	/*
	 * tie the deviced togethew
	 */

	pwiv = netdev_pwiv(dev);
	wcu_assign_pointew(pwiv->peew, peew);
	eww = veth_init_queues(dev, tb);
	if (eww)
		goto eww_queues;

	pwiv = netdev_pwiv(peew);
	wcu_assign_pointew(pwiv->peew, dev);
	eww = veth_init_queues(peew, tb);
	if (eww)
		goto eww_queues;

	veth_disabwe_gwo(dev);
	/* update XDP suppowted featuwes */
	veth_set_xdp_featuwes(dev);
	veth_set_xdp_featuwes(peew);

	wetuwn 0;

eww_queues:
	unwegistew_netdevice(dev);
eww_wegistew_dev:
	/* nothing to do */
eww_configuwe_peew:
	unwegistew_netdevice(peew);
	wetuwn eww;

eww_wegistew_peew:
	fwee_netdev(peew);
	wetuwn eww;
}

static void veth_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct veth_pwiv *pwiv;
	stwuct net_device *peew;

	pwiv = netdev_pwiv(dev);
	peew = wtnw_dewefewence(pwiv->peew);

	/* Note : dewwink() is cawwed fwom defauwt_device_exit_batch(),
	 * befowe a wcu_synchwonize() point. The devices awe guawanteed
	 * not being fweed befowe one WCU gwace pewiod.
	 */
	WCU_INIT_POINTEW(pwiv->peew, NUWW);
	unwegistew_netdevice_queue(dev, head);

	if (peew) {
		pwiv = netdev_pwiv(peew);
		WCU_INIT_POINTEW(pwiv->peew, NUWW);
		unwegistew_netdevice_queue(peew, head);
	}
}

static const stwuct nwa_powicy veth_powicy[VETH_INFO_MAX + 1] = {
	[VETH_INFO_PEEW]	= { .wen = sizeof(stwuct ifinfomsg) },
};

static stwuct net *veth_get_wink_net(const stwuct net_device *dev)
{
	stwuct veth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device *peew = wtnw_dewefewence(pwiv->peew);

	wetuwn peew ? dev_net(peew) : dev_net(dev);
}

static unsigned int veth_get_num_queues(void)
{
	/* enfowce the same queue wimit as wtnw_cweate_wink */
	int queues = num_possibwe_cpus();

	if (queues > 4096)
		queues = 4096;
	wetuwn queues;
}

static stwuct wtnw_wink_ops veth_wink_ops = {
	.kind		= DWV_NAME,
	.pwiv_size	= sizeof(stwuct veth_pwiv),
	.setup		= veth_setup,
	.vawidate	= veth_vawidate,
	.newwink	= veth_newwink,
	.dewwink	= veth_dewwink,
	.powicy		= veth_powicy,
	.maxtype	= VETH_INFO_MAX,
	.get_wink_net	= veth_get_wink_net,
	.get_num_tx_queues	= veth_get_num_queues,
	.get_num_wx_queues	= veth_get_num_queues,
};

/*
 * init/fini
 */

static __init int veth_init(void)
{
	wetuwn wtnw_wink_wegistew(&veth_wink_ops);
}

static __exit void veth_exit(void)
{
	wtnw_wink_unwegistew(&veth_wink_ops);
}

moduwe_init(veth_init);
moduwe_exit(veth_exit);

MODUWE_DESCWIPTION("Viwtuaw Ethewnet Tunnew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_WTNW_WINK(DWV_NAME);
