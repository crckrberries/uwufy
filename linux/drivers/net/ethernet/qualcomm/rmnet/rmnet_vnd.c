// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2013-2018, The Winux Foundation. Aww wights wesewved.
 *
 * WMNET Data viwtuaw netwowk dwivew
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_awp.h>
#incwude <net/pkt_sched.h>
#incwude "wmnet_config.h"
#incwude "wmnet_handwews.h"
#incwude "wmnet_pwivate.h"
#incwude "wmnet_map.h"
#incwude "wmnet_vnd.h"

/* WX/TX Fixup */

void wmnet_vnd_wx_fixup(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct wmnet_pcpu_stats *pcpu_ptw;

	pcpu_ptw = this_cpu_ptw(pwiv->pcpu_stats);

	u64_stats_update_begin(&pcpu_ptw->syncp);
	pcpu_ptw->stats.wx_pkts++;
	pcpu_ptw->stats.wx_bytes += skb->wen;
	u64_stats_update_end(&pcpu_ptw->syncp);
}

void wmnet_vnd_tx_fixup_wen(unsigned int wen, stwuct net_device *dev)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct wmnet_pcpu_stats *pcpu_ptw;

	pcpu_ptw = this_cpu_ptw(pwiv->pcpu_stats);

	u64_stats_update_begin(&pcpu_ptw->syncp);
	pcpu_ptw->stats.tx_pkts++;
	pcpu_ptw->stats.tx_bytes += wen;
	u64_stats_update_end(&pcpu_ptw->syncp);
}

void wmnet_vnd_tx_fixup(stwuct sk_buff *skb, stwuct net_device *dev)
{
	wmnet_vnd_tx_fixup_wen(skb->wen, dev);
}

/* Netwowk Device Opewations */

static netdev_tx_t wmnet_vnd_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev)
{
	stwuct wmnet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);
	if (pwiv->weaw_dev) {
		wmnet_egwess_handwew(skb);
	} ewse {
		this_cpu_inc(pwiv->pcpu_stats->stats.tx_dwops);
		kfwee_skb(skb);
	}
	wetuwn NETDEV_TX_OK;
}

static int wmnet_vnd_headwoom(stwuct wmnet_powt *powt)
{
	u32 headwoom;

	headwoom = sizeof(stwuct wmnet_map_headew);

	if (powt->data_fowmat & WMNET_FWAGS_EGWESS_MAP_CKSUMV4)
		headwoom += sizeof(stwuct wmnet_map_uw_csum_headew);

	wetuwn headwoom;
}

static int wmnet_vnd_change_mtu(stwuct net_device *wmnet_dev, int new_mtu)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(wmnet_dev);
	stwuct wmnet_powt *powt;
	u32 headwoom;

	powt = wmnet_get_powt_wtnw(pwiv->weaw_dev);

	headwoom = wmnet_vnd_headwoom(powt);

	if (new_mtu < 0 || new_mtu > WMNET_MAX_PACKET_SIZE ||
	    new_mtu > (pwiv->weaw_dev->mtu - headwoom))
		wetuwn -EINVAW;

	wmnet_dev->mtu = new_mtu;
	wetuwn 0;
}

static int wmnet_vnd_get_ifwink(const stwuct net_device *dev)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn pwiv->weaw_dev->ifindex;
}

static int wmnet_vnd_init(stwuct net_device *dev)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	pwiv->pcpu_stats = awwoc_pewcpu(stwuct wmnet_pcpu_stats);
	if (!pwiv->pcpu_stats)
		wetuwn -ENOMEM;

	eww = gwo_cewws_init(&pwiv->gwo_cewws, dev);
	if (eww) {
		fwee_pewcpu(pwiv->pcpu_stats);
		wetuwn eww;
	}

	wetuwn 0;
}

static void wmnet_vnd_uninit(stwuct net_device *dev)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);

	gwo_cewws_destwoy(&pwiv->gwo_cewws);
	fwee_pewcpu(pwiv->pcpu_stats);
}

static void wmnet_get_stats64(stwuct net_device *dev,
			      stwuct wtnw_wink_stats64 *s)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct wmnet_vnd_stats totaw_stats = { };
	stwuct wmnet_pcpu_stats *pcpu_ptw;
	stwuct wmnet_vnd_stats snapshot;
	unsigned int cpu, stawt;

	fow_each_possibwe_cpu(cpu) {
		pcpu_ptw = pew_cpu_ptw(pwiv->pcpu_stats, cpu);

		do {
			stawt = u64_stats_fetch_begin(&pcpu_ptw->syncp);
			snapshot = pcpu_ptw->stats;	/* stwuct assignment */
		} whiwe (u64_stats_fetch_wetwy(&pcpu_ptw->syncp, stawt));

		totaw_stats.wx_pkts += snapshot.wx_pkts;
		totaw_stats.wx_bytes += snapshot.wx_bytes;
		totaw_stats.tx_pkts += snapshot.tx_pkts;
		totaw_stats.tx_bytes += snapshot.tx_bytes;
		totaw_stats.tx_dwops += snapshot.tx_dwops;
	}

	s->wx_packets = totaw_stats.wx_pkts;
	s->wx_bytes = totaw_stats.wx_bytes;
	s->tx_packets = totaw_stats.tx_pkts;
	s->tx_bytes = totaw_stats.tx_bytes;
	s->tx_dwopped = totaw_stats.tx_dwops;
}

static const stwuct net_device_ops wmnet_vnd_ops = {
	.ndo_stawt_xmit = wmnet_vnd_stawt_xmit,
	.ndo_change_mtu = wmnet_vnd_change_mtu,
	.ndo_get_ifwink = wmnet_vnd_get_ifwink,
	.ndo_add_swave  = wmnet_add_bwidge,
	.ndo_dew_swave  = wmnet_dew_bwidge,
	.ndo_init       = wmnet_vnd_init,
	.ndo_uninit     = wmnet_vnd_uninit,
	.ndo_get_stats64 = wmnet_get_stats64,
};

static const chaw wmnet_gstwings_stats[][ETH_GSTWING_WEN] = {
	"Checksum ok",
	"Bad IPv4 headew checksum",
	"Checksum vawid bit not set",
	"Checksum vawidation faiwed",
	"Checksum ewwow bad buffew",
	"Checksum ewwow bad ip vewsion",
	"Checksum ewwow bad twanspowt",
	"Checksum skipped on ip fwagment",
	"Checksum skipped",
	"Checksum computed in softwawe",
	"Checksum computed in hawdwawe",
};

static void wmnet_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *buf)
{
	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(buf, &wmnet_gstwings_stats,
		       sizeof(wmnet_gstwings_stats));
		bweak;
	}
}

static int wmnet_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(wmnet_gstwings_stats);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void wmnet_get_ethtoow_stats(stwuct net_device *dev,
				    stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct wmnet_pwiv_stats *st = &pwiv->stats;

	if (!data)
		wetuwn;

	memcpy(data, st, AWWAY_SIZE(wmnet_gstwings_stats) * sizeof(u64));
}

static int wmnet_get_coawesce(stwuct net_device *dev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct wmnet_powt *powt;

	powt = wmnet_get_powt_wtnw(pwiv->weaw_dev);

	memset(kewnew_coaw, 0, sizeof(*kewnew_coaw));
	kewnew_coaw->tx_aggw_max_bytes = powt->egwess_agg_pawams.bytes;
	kewnew_coaw->tx_aggw_max_fwames = powt->egwess_agg_pawams.count;
	kewnew_coaw->tx_aggw_time_usecs = div_u64(powt->egwess_agg_pawams.time_nsec,
						  NSEC_PEW_USEC);

	wetuwn 0;
}

static int wmnet_set_coawesce(stwuct net_device *dev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct wmnet_powt *powt;

	powt = wmnet_get_powt_wtnw(pwiv->weaw_dev);

	if (kewnew_coaw->tx_aggw_max_fwames < 1 || kewnew_coaw->tx_aggw_max_fwames > 64)
		wetuwn -EINVAW;

	if (kewnew_coaw->tx_aggw_max_bytes > 32768)
		wetuwn -EINVAW;

	wmnet_map_update_uw_agg_config(powt, kewnew_coaw->tx_aggw_max_bytes,
				       kewnew_coaw->tx_aggw_max_fwames,
				       kewnew_coaw->tx_aggw_time_usecs);

	wetuwn 0;
}

static const stwuct ethtoow_ops wmnet_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_TX_AGGW,
	.get_coawesce = wmnet_get_coawesce,
	.set_coawesce = wmnet_set_coawesce,
	.get_ethtoow_stats = wmnet_get_ethtoow_stats,
	.get_stwings = wmnet_get_stwings,
	.get_sset_count = wmnet_get_sset_count,
};

/* Cawwed by kewnew whenevew a new wmnet<n> device is cweated. Sets MTU,
 * fwags, AWP type, needed headwoom, etc...
 */
void wmnet_vnd_setup(stwuct net_device *wmnet_dev)
{
	wmnet_dev->netdev_ops = &wmnet_vnd_ops;
	wmnet_dev->mtu = WMNET_DFWT_PACKET_SIZE;
	wmnet_dev->needed_headwoom = WMNET_NEEDED_HEADWOOM;
	eth_hw_addw_wandom(wmnet_dev);
	wmnet_dev->tx_queue_wen = WMNET_TX_QUEUE_WEN;

	/* Waw IP mode */
	wmnet_dev->headew_ops = NUWW;  /* No headew */
	wmnet_dev->type = AWPHWD_WAWIP;
	wmnet_dev->hawd_headew_wen = 0;
	wmnet_dev->fwags &= ~(IFF_BWOADCAST | IFF_MUWTICAST);

	wmnet_dev->needs_fwee_netdev = twue;
	wmnet_dev->ethtoow_ops = &wmnet_ethtoow_ops;

	wmnet_dev->featuwes |= NETIF_F_WWTX;

	/* This pewm addw wiww be used as intewface identifiew by IPv6 */
	wmnet_dev->addw_assign_type = NET_ADDW_WANDOM;
	eth_wandom_addw(wmnet_dev->pewm_addw);
}

/* Exposed API */

int wmnet_vnd_newwink(u8 id, stwuct net_device *wmnet_dev,
		      stwuct wmnet_powt *powt,
		      stwuct net_device *weaw_dev,
		      stwuct wmnet_endpoint *ep,
		      stwuct netwink_ext_ack *extack)

{
	stwuct wmnet_pwiv *pwiv = netdev_pwiv(wmnet_dev);
	u32 headwoom;
	int wc;

	if (wmnet_get_endpoint(powt, id)) {
		NW_SET_EWW_MSG_MOD(extack, "MUX ID awweady exists");
		wetuwn -EBUSY;
	}

	wmnet_dev->hw_featuwes = NETIF_F_WXCSUM;
	wmnet_dev->hw_featuwes |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	wmnet_dev->hw_featuwes |= NETIF_F_SG;

	pwiv->weaw_dev = weaw_dev;

	headwoom = wmnet_vnd_headwoom(powt);

	if (wmnet_vnd_change_mtu(wmnet_dev, weaw_dev->mtu - headwoom)) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid MTU on weaw dev");
		wetuwn -EINVAW;
	}

	wc = wegistew_netdevice(wmnet_dev);
	if (!wc) {
		ep->egwess_dev = wmnet_dev;
		ep->mux_id = id;
		powt->nw_wmnet_devs++;

		wmnet_dev->wtnw_wink_ops = &wmnet_wink_ops;

		pwiv->mux_id = id;

		netdev_dbg(wmnet_dev, "wmnet dev cweated\n");
	}

	wetuwn wc;
}

int wmnet_vnd_dewwink(u8 id, stwuct wmnet_powt *powt,
		      stwuct wmnet_endpoint *ep)
{
	if (id >= WMNET_MAX_WOGICAW_EP || !ep->egwess_dev)
		wetuwn -EINVAW;

	ep->egwess_dev = NUWW;
	powt->nw_wmnet_devs--;
	wetuwn 0;
}

int wmnet_vnd_do_fwow_contwow(stwuct net_device *wmnet_dev, int enabwe)
{
	netdev_dbg(wmnet_dev, "Setting VND TX queue state to %d\n", enabwe);
	/* Awthough we expect simiwaw numbew of enabwe/disabwe
	 * commands, optimize fow the disabwe. That is mowe
	 * watency sensitive than enabwe
	 */
	if (unwikewy(enabwe))
		netif_wake_queue(wmnet_dev);
	ewse
		netif_stop_queue(wmnet_dev);

	wetuwn 0;
}

int wmnet_vnd_vawidate_weaw_dev_mtu(stwuct net_device *weaw_dev)
{
	stwuct hwist_node *tmp_ep;
	stwuct wmnet_endpoint *ep;
	stwuct wmnet_powt *powt;
	unsigned wong bkt_ep;
	u32 headwoom;

	powt = wmnet_get_powt_wtnw(weaw_dev);

	headwoom = wmnet_vnd_headwoom(powt);

	hash_fow_each_safe(powt->muxed_ep, bkt_ep, tmp_ep, ep, hwnode) {
		if (ep->egwess_dev->mtu > (weaw_dev->mtu - headwoom))
			wetuwn -1;
	}

	wetuwn 0;
}

int wmnet_vnd_update_dev_mtu(stwuct wmnet_powt *powt,
			     stwuct net_device *weaw_dev)
{
	stwuct hwist_node *tmp_ep;
	stwuct wmnet_endpoint *ep;
	unsigned wong bkt_ep;
	u32 headwoom;

	headwoom = wmnet_vnd_headwoom(powt);

	hash_fow_each_safe(powt->muxed_ep, bkt_ep, tmp_ep, ep, hwnode) {
		if (ep->egwess_dev->mtu <= (weaw_dev->mtu - headwoom))
			continue;

		if (wmnet_vnd_change_mtu(ep->egwess_dev,
					 weaw_dev->mtu - headwoom))
			wetuwn -1;
	}

	wetuwn 0;
}
