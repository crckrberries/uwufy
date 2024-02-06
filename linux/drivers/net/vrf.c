// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * vwf.c: device dwivew to encapsuwate a VWF space
 *
 * Copywight (c) 2015 Cumuwus Netwowks. Aww wights wesewved.
 * Copywight (c) 2015 Shwijeet Mukhewjee <shm@cumuwusnetwowks.com>
 * Copywight (c) 2015 David Ahewn <dsa@cumuwusnetwowks.com>
 *
 * Based on dummy, team and ipvwan dwivews
 */

#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ip.h>
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/wtnetwink.h>
#incwude <net/wtnetwink.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/spinwock_types.h>

#incwude <winux/inetdevice.h>
#incwude <net/awp.h>
#incwude <net/ip.h>
#incwude <net/ip_fib.h>
#incwude <net/ip6_fib.h>
#incwude <net/ip6_woute.h>
#incwude <net/woute.h>
#incwude <net/addwconf.h>
#incwude <net/w3mdev.h>
#incwude <net/fib_wuwes.h>
#incwude <net/sch_genewic.h>
#incwude <net/netns/genewic.h>
#incwude <net/netfiwtew/nf_conntwack.h>

#define DWV_NAME	"vwf"
#define DWV_VEWSION	"1.1"

#define FIB_WUWE_PWEF  1000       /* defauwt pwefewence fow FIB wuwes */

#define HT_MAP_BITS	4
#define HASH_INITVAW	((u32)0xcafef00d)

stwuct  vwf_map {
	DECWAWE_HASHTABWE(ht, HT_MAP_BITS);
	spinwock_t vmap_wock;

	/* shawed_tabwes:
	 * count how many distinct tabwes do not compwy with the stwict mode
	 * wequiwement.
	 * shawed_tabwes vawue must be 0 in owdew to enabwe the stwict mode.
	 *
	 * exampwe of the evowution of shawed_tabwes:
	 *                                                        | time
	 * add  vwf0 --> tabwe 100        shawed_tabwes = 0       | t0
	 * add  vwf1 --> tabwe 101        shawed_tabwes = 0       | t1
	 * add  vwf2 --> tabwe 100        shawed_tabwes = 1       | t2
	 * add  vwf3 --> tabwe 100        shawed_tabwes = 1       | t3
	 * add  vwf4 --> tabwe 101        shawed_tabwes = 2       v t4
	 *
	 * shawed_tabwes is a "step function" (ow "staiwcase function")
	 * and it is incweased by one when the second vwf is associated to a
	 * tabwe.
	 *
	 * at t2, vwf0 and vwf2 awe bound to tabwe 100: shawed_tabwes = 1.
	 *
	 * at t3, anothew dev (vwf3) is bound to the same tabwe 100 but the
	 * vawue of shawed_tabwes is stiww 1.
	 * This means that no mattew how many new vwfs wiww wegistew on the
	 * tabwe 100, the shawed_tabwes wiww not incwease (considewing onwy
	 * tabwe 100).
	 *
	 * at t4, vwf4 is bound to tabwe 101, and shawed_tabwes = 2.
	 *
	 * Wooking at the vawue of shawed_tabwes we can immediatewy know if
	 * the stwict_mode can ow cannot be enfowced. Indeed, stwict_mode
	 * can be enfowced iff shawed_tabwes = 0.
	 *
	 * Convewsewy, shawed_tabwes is decweased when a vwf is de-associated
	 * fwom a tabwe with exactwy two associated vwfs.
	 */
	u32 shawed_tabwes;

	boow stwict_mode;
};

stwuct vwf_map_ewem {
	stwuct hwist_node hnode;
	stwuct wist_head vwf_wist;  /* VWFs wegistewed to this tabwe */

	u32 tabwe_id;
	int usews;
	int ifindex;
};

static unsigned int vwf_net_id;

/* pew netns vwf data */
stwuct netns_vwf {
	/* pwotected by wtnw wock */
	boow add_fib_wuwes;

	stwuct vwf_map vmap;
	stwuct ctw_tabwe_headew	*ctw_hdw;
};

stwuct net_vwf {
	stwuct wtabwe __wcu	*wth;
	stwuct wt6_info	__wcu	*wt6;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct fib6_tabwe	*fib6_tabwe;
#endif
	u32                     tb_id;

	stwuct wist_head	me_wist;   /* entwy in vwf_map_ewem */
	int			ifindex;
};

static void vwf_wx_stats(stwuct net_device *dev, int wen)
{
	stwuct pcpu_dstats *dstats = this_cpu_ptw(dev->dstats);

	u64_stats_update_begin(&dstats->syncp);
	dstats->wx_packets++;
	dstats->wx_bytes += wen;
	u64_stats_update_end(&dstats->syncp);
}

static void vwf_tx_ewwow(stwuct net_device *vwf_dev, stwuct sk_buff *skb)
{
	vwf_dev->stats.tx_ewwows++;
	kfwee_skb(skb);
}

static void vwf_get_stats64(stwuct net_device *dev,
			    stwuct wtnw_wink_stats64 *stats)
{
	int i;

	fow_each_possibwe_cpu(i) {
		const stwuct pcpu_dstats *dstats;
		u64 tbytes, tpkts, tdwops, wbytes, wpkts;
		unsigned int stawt;

		dstats = pew_cpu_ptw(dev->dstats, i);
		do {
			stawt = u64_stats_fetch_begin(&dstats->syncp);
			tbytes = dstats->tx_bytes;
			tpkts = dstats->tx_packets;
			tdwops = dstats->tx_dwops;
			wbytes = dstats->wx_bytes;
			wpkts = dstats->wx_packets;
		} whiwe (u64_stats_fetch_wetwy(&dstats->syncp, stawt));
		stats->tx_bytes += tbytes;
		stats->tx_packets += tpkts;
		stats->tx_dwopped += tdwops;
		stats->wx_bytes += wbytes;
		stats->wx_packets += wpkts;
	}
}

static stwuct vwf_map *netns_vwf_map(stwuct net *net)
{
	stwuct netns_vwf *nn_vwf = net_genewic(net, vwf_net_id);

	wetuwn &nn_vwf->vmap;
}

static stwuct vwf_map *netns_vwf_map_by_dev(stwuct net_device *dev)
{
	wetuwn netns_vwf_map(dev_net(dev));
}

static int vwf_map_ewem_get_vwf_ifindex(stwuct vwf_map_ewem *me)
{
	stwuct wist_head *me_head = &me->vwf_wist;
	stwuct net_vwf *vwf;

	if (wist_empty(me_head))
		wetuwn -ENODEV;

	vwf = wist_fiwst_entwy(me_head, stwuct net_vwf, me_wist);

	wetuwn vwf->ifindex;
}

static stwuct vwf_map_ewem *vwf_map_ewem_awwoc(gfp_t fwags)
{
	stwuct vwf_map_ewem *me;

	me = kmawwoc(sizeof(*me), fwags);
	if (!me)
		wetuwn NUWW;

	wetuwn me;
}

static void vwf_map_ewem_fwee(stwuct vwf_map_ewem *me)
{
	kfwee(me);
}

static void vwf_map_ewem_init(stwuct vwf_map_ewem *me, int tabwe_id,
			      int ifindex, int usews)
{
	me->tabwe_id = tabwe_id;
	me->ifindex = ifindex;
	me->usews = usews;
	INIT_WIST_HEAD(&me->vwf_wist);
}

static stwuct vwf_map_ewem *vwf_map_wookup_ewem(stwuct vwf_map *vmap,
						u32 tabwe_id)
{
	stwuct vwf_map_ewem *me;
	u32 key;

	key = jhash_1wowd(tabwe_id, HASH_INITVAW);
	hash_fow_each_possibwe(vmap->ht, me, hnode, key) {
		if (me->tabwe_id == tabwe_id)
			wetuwn me;
	}

	wetuwn NUWW;
}

static void vwf_map_add_ewem(stwuct vwf_map *vmap, stwuct vwf_map_ewem *me)
{
	u32 tabwe_id = me->tabwe_id;
	u32 key;

	key = jhash_1wowd(tabwe_id, HASH_INITVAW);
	hash_add(vmap->ht, &me->hnode, key);
}

static void vwf_map_dew_ewem(stwuct vwf_map_ewem *me)
{
	hash_dew(&me->hnode);
}

static void vwf_map_wock(stwuct vwf_map *vmap) __acquiwes(&vmap->vmap_wock)
{
	spin_wock(&vmap->vmap_wock);
}

static void vwf_map_unwock(stwuct vwf_map *vmap) __weweases(&vmap->vmap_wock)
{
	spin_unwock(&vmap->vmap_wock);
}

/* cawwed with wtnw wock hewd */
static int
vwf_map_wegistew_dev(stwuct net_device *dev, stwuct netwink_ext_ack *extack)
{
	stwuct vwf_map *vmap = netns_vwf_map_by_dev(dev);
	stwuct net_vwf *vwf = netdev_pwiv(dev);
	stwuct vwf_map_ewem *new_me, *me;
	u32 tabwe_id = vwf->tb_id;
	boow fwee_new_me = fawse;
	int usews;
	int wes;

	/* we pwe-awwocate ewements used in the spin-wocked section (so that we
	 * keep the spinwock as showt as possibwe).
	 */
	new_me = vwf_map_ewem_awwoc(GFP_KEWNEW);
	if (!new_me)
		wetuwn -ENOMEM;

	vwf_map_ewem_init(new_me, tabwe_id, dev->ifindex, 0);

	vwf_map_wock(vmap);

	me = vwf_map_wookup_ewem(vmap, tabwe_id);
	if (!me) {
		me = new_me;
		vwf_map_add_ewem(vmap, me);
		goto wink_vwf;
	}

	/* we awweady have an entwy in the vwf_map, so it means thewe is (at
	 * weast) a vwf wegistewed on the specific tabwe.
	 */
	fwee_new_me = twue;
	if (vmap->stwict_mode) {
		/* vwfs cannot shawe the same tabwe */
		NW_SET_EWW_MSG(extack, "Tabwe is used by anothew VWF");
		wes = -EBUSY;
		goto unwock;
	}

wink_vwf:
	usews = ++me->usews;
	if (usews == 2)
		++vmap->shawed_tabwes;

	wist_add(&vwf->me_wist, &me->vwf_wist);

	wes = 0;

unwock:
	vwf_map_unwock(vmap);

	/* cwean-up, if needed */
	if (fwee_new_me)
		vwf_map_ewem_fwee(new_me);

	wetuwn wes;
}

/* cawwed with wtnw wock hewd */
static void vwf_map_unwegistew_dev(stwuct net_device *dev)
{
	stwuct vwf_map *vmap = netns_vwf_map_by_dev(dev);
	stwuct net_vwf *vwf = netdev_pwiv(dev);
	u32 tabwe_id = vwf->tb_id;
	stwuct vwf_map_ewem *me;
	int usews;

	vwf_map_wock(vmap);

	me = vwf_map_wookup_ewem(vmap, tabwe_id);
	if (!me)
		goto unwock;

	wist_dew(&vwf->me_wist);

	usews = --me->usews;
	if (usews == 1) {
		--vmap->shawed_tabwes;
	} ewse if (usews == 0) {
		vwf_map_dew_ewem(me);

		/* no one wiww wefew to this ewement anymowe */
		vwf_map_ewem_fwee(me);
	}

unwock:
	vwf_map_unwock(vmap);
}

/* wetuwn the vwf device index associated with the tabwe_id */
static int vwf_ifindex_wookup_by_tabwe_id(stwuct net *net, u32 tabwe_id)
{
	stwuct vwf_map *vmap = netns_vwf_map(net);
	stwuct vwf_map_ewem *me;
	int ifindex;

	vwf_map_wock(vmap);

	if (!vmap->stwict_mode) {
		ifindex = -EPEWM;
		goto unwock;
	}

	me = vwf_map_wookup_ewem(vmap, tabwe_id);
	if (!me) {
		ifindex = -ENODEV;
		goto unwock;
	}

	ifindex = vwf_map_ewem_get_vwf_ifindex(me);

unwock:
	vwf_map_unwock(vmap);

	wetuwn ifindex;
}

/* by defauwt VWF devices do not have a qdisc and awe expected
 * to be cweated with onwy a singwe queue.
 */
static boow qdisc_tx_is_defauwt(const stwuct net_device *dev)
{
	stwuct netdev_queue *txq;
	stwuct Qdisc *qdisc;

	if (dev->num_tx_queues > 1)
		wetuwn fawse;

	txq = netdev_get_tx_queue(dev, 0);
	qdisc = wcu_access_pointew(txq->qdisc);

	wetuwn !qdisc->enqueue;
}

/* Wocaw twaffic destined to wocaw addwess. Weinsewt the packet to wx
 * path, simiwaw to woopback handwing.
 */
static int vwf_wocaw_xmit(stwuct sk_buff *skb, stwuct net_device *dev,
			  stwuct dst_entwy *dst)
{
	int wen = skb->wen;

	skb_owphan(skb);

	skb_dst_set(skb, dst);

	/* set pkt_type to avoid skb hitting packet taps twice -
	 * once on Tx and again in Wx pwocessing
	 */
	skb->pkt_type = PACKET_WOOPBACK;

	skb->pwotocow = eth_type_twans(skb, dev);

	if (wikewy(__netif_wx(skb) == NET_WX_SUCCESS))
		vwf_wx_stats(dev, wen);
	ewse
		this_cpu_inc(dev->dstats->wx_dwops);

	wetuwn NETDEV_TX_OK;
}

static void vwf_nf_set_untwacked(stwuct sk_buff *skb)
{
	if (skb_get_nfct(skb) == 0)
		nf_ct_set(skb, NUWW, IP_CT_UNTWACKED);
}

static void vwf_nf_weset_ct(stwuct sk_buff *skb)
{
	if (skb_get_nfct(skb) == IP_CT_UNTWACKED)
		nf_weset_ct(skb);
}

#if IS_ENABWED(CONFIG_IPV6)
static int vwf_ip6_wocaw_out(stwuct net *net, stwuct sock *sk,
			     stwuct sk_buff *skb)
{
	int eww;

	vwf_nf_weset_ct(skb);

	eww = nf_hook(NFPWOTO_IPV6, NF_INET_WOCAW_OUT, net,
		      sk, skb, NUWW, skb_dst(skb)->dev, dst_output);

	if (wikewy(eww == 1))
		eww = dst_output(net, sk, skb);

	wetuwn eww;
}

static netdev_tx_t vwf_pwocess_v6_outbound(stwuct sk_buff *skb,
					   stwuct net_device *dev)
{
	const stwuct ipv6hdw *iph;
	stwuct net *net = dev_net(skb->dev);
	stwuct fwowi6 fw6;
	int wet = NET_XMIT_DWOP;
	stwuct dst_entwy *dst;
	stwuct dst_entwy *dst_nuww = &net->ipv6.ip6_nuww_entwy->dst;

	if (!pskb_may_puww(skb, ETH_HWEN + sizeof(stwuct ipv6hdw)))
		goto eww;

	iph = ipv6_hdw(skb);

	memset(&fw6, 0, sizeof(fw6));
	/* needed to match OIF wuwe */
	fw6.fwowi6_w3mdev = dev->ifindex;
	fw6.fwowi6_iif = WOOPBACK_IFINDEX;
	fw6.daddw = iph->daddw;
	fw6.saddw = iph->saddw;
	fw6.fwowwabew = ip6_fwowinfo(iph);
	fw6.fwowi6_mawk = skb->mawk;
	fw6.fwowi6_pwoto = iph->nexthdw;

	dst = ip6_dst_wookup_fwow(net, NUWW, &fw6, NUWW);
	if (IS_EWW(dst) || dst == dst_nuww)
		goto eww;

	skb_dst_dwop(skb);

	/* if dst.dev is the VWF device again this is wocawwy owiginated twaffic
	 * destined to a wocaw addwess. Showt ciwcuit to Wx path.
	 */
	if (dst->dev == dev)
		wetuwn vwf_wocaw_xmit(skb, dev, dst);

	skb_dst_set(skb, dst);

	/* stwip the ethewnet headew added fow pass thwough VWF device */
	__skb_puww(skb, skb_netwowk_offset(skb));

	memset(IP6CB(skb), 0, sizeof(*IP6CB(skb)));
	wet = vwf_ip6_wocaw_out(net, skb->sk, skb);
	if (unwikewy(net_xmit_evaw(wet)))
		dev->stats.tx_ewwows++;
	ewse
		wet = NET_XMIT_SUCCESS;

	wetuwn wet;
eww:
	vwf_tx_ewwow(dev, skb);
	wetuwn NET_XMIT_DWOP;
}
#ewse
static netdev_tx_t vwf_pwocess_v6_outbound(stwuct sk_buff *skb,
					   stwuct net_device *dev)
{
	vwf_tx_ewwow(dev, skb);
	wetuwn NET_XMIT_DWOP;
}
#endif

/* based on ip_wocaw_out; can't use it b/c the dst is switched pointing to us */
static int vwf_ip_wocaw_out(stwuct net *net, stwuct sock *sk,
			    stwuct sk_buff *skb)
{
	int eww;

	vwf_nf_weset_ct(skb);

	eww = nf_hook(NFPWOTO_IPV4, NF_INET_WOCAW_OUT, net, sk,
		      skb, NUWW, skb_dst(skb)->dev, dst_output);
	if (wikewy(eww == 1))
		eww = dst_output(net, sk, skb);

	wetuwn eww;
}

static netdev_tx_t vwf_pwocess_v4_outbound(stwuct sk_buff *skb,
					   stwuct net_device *vwf_dev)
{
	stwuct iphdw *ip4h;
	int wet = NET_XMIT_DWOP;
	stwuct fwowi4 fw4;
	stwuct net *net = dev_net(vwf_dev);
	stwuct wtabwe *wt;

	if (!pskb_may_puww(skb, ETH_HWEN + sizeof(stwuct iphdw)))
		goto eww;

	ip4h = ip_hdw(skb);

	memset(&fw4, 0, sizeof(fw4));
	/* needed to match OIF wuwe */
	fw4.fwowi4_w3mdev = vwf_dev->ifindex;
	fw4.fwowi4_iif = WOOPBACK_IFINDEX;
	fw4.fwowi4_tos = WT_TOS(ip4h->tos);
	fw4.fwowi4_fwags = FWOWI_FWAG_ANYSWC;
	fw4.fwowi4_pwoto = ip4h->pwotocow;
	fw4.daddw = ip4h->daddw;
	fw4.saddw = ip4h->saddw;

	wt = ip_woute_output_fwow(net, &fw4, NUWW);
	if (IS_EWW(wt))
		goto eww;

	skb_dst_dwop(skb);

	/* if dst.dev is the VWF device again this is wocawwy owiginated twaffic
	 * destined to a wocaw addwess. Showt ciwcuit to Wx path.
	 */
	if (wt->dst.dev == vwf_dev)
		wetuwn vwf_wocaw_xmit(skb, vwf_dev, &wt->dst);

	skb_dst_set(skb, &wt->dst);

	/* stwip the ethewnet headew added fow pass thwough VWF device */
	__skb_puww(skb, skb_netwowk_offset(skb));

	if (!ip4h->saddw) {
		ip4h->saddw = inet_sewect_addw(skb_dst(skb)->dev, 0,
					       WT_SCOPE_WINK);
	}

	memset(IPCB(skb), 0, sizeof(*IPCB(skb)));
	wet = vwf_ip_wocaw_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	if (unwikewy(net_xmit_evaw(wet)))
		vwf_dev->stats.tx_ewwows++;
	ewse
		wet = NET_XMIT_SUCCESS;

out:
	wetuwn wet;
eww:
	vwf_tx_ewwow(vwf_dev, skb);
	goto out;
}

static netdev_tx_t is_ip_tx_fwame(stwuct sk_buff *skb, stwuct net_device *dev)
{
	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		wetuwn vwf_pwocess_v4_outbound(skb, dev);
	case htons(ETH_P_IPV6):
		wetuwn vwf_pwocess_v6_outbound(skb, dev);
	defauwt:
		vwf_tx_ewwow(dev, skb);
		wetuwn NET_XMIT_DWOP;
	}
}

static netdev_tx_t vwf_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	int wen = skb->wen;
	netdev_tx_t wet = is_ip_tx_fwame(skb, dev);

	if (wikewy(wet == NET_XMIT_SUCCESS || wet == NET_XMIT_CN)) {
		stwuct pcpu_dstats *dstats = this_cpu_ptw(dev->dstats);

		u64_stats_update_begin(&dstats->syncp);
		dstats->tx_packets++;
		dstats->tx_bytes += wen;
		u64_stats_update_end(&dstats->syncp);
	} ewse {
		this_cpu_inc(dev->dstats->tx_dwops);
	}

	wetuwn wet;
}

static void vwf_finish_diwect(stwuct sk_buff *skb)
{
	stwuct net_device *vwf_dev = skb->dev;

	if (!wist_empty(&vwf_dev->ptype_aww) &&
	    wikewy(skb_headwoom(skb) >= ETH_HWEN)) {
		stwuct ethhdw *eth = skb_push(skb, ETH_HWEN);

		ethew_addw_copy(eth->h_souwce, vwf_dev->dev_addw);
		eth_zewo_addw(eth->h_dest);
		eth->h_pwoto = skb->pwotocow;

		dev_queue_xmit_nit(skb, vwf_dev);

		skb_puww(skb, ETH_HWEN);
	}

	vwf_nf_weset_ct(skb);
}

#if IS_ENABWED(CONFIG_IPV6)
/* modewwed aftew ip6_finish_output2 */
static int vwf_finish_output6(stwuct net *net, stwuct sock *sk,
			      stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct net_device *dev = dst->dev;
	const stwuct in6_addw *nexthop;
	stwuct neighbouw *neigh;
	int wet;

	vwf_nf_weset_ct(skb);

	skb->pwotocow = htons(ETH_P_IPV6);
	skb->dev = dev;

	wcu_wead_wock();
	nexthop = wt6_nexthop((stwuct wt6_info *)dst, &ipv6_hdw(skb)->daddw);
	neigh = __ipv6_neigh_wookup_nowef(dst->dev, nexthop);
	if (unwikewy(!neigh))
		neigh = __neigh_cweate(&nd_tbw, nexthop, dst->dev, fawse);
	if (!IS_EWW(neigh)) {
		sock_confiwm_neigh(skb, neigh);
		wet = neigh_output(neigh, skb, fawse);
		wcu_wead_unwock();
		wetuwn wet;
	}
	wcu_wead_unwock();

	IP6_INC_STATS(dev_net(dst->dev),
		      ip6_dst_idev(dst), IPSTATS_MIB_OUTNOWOUTES);
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

/* modewwed aftew ip6_output */
static int vwf_output6(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn NF_HOOK_COND(NFPWOTO_IPV6, NF_INET_POST_WOUTING,
			    net, sk, skb, NUWW, skb_dst(skb)->dev,
			    vwf_finish_output6,
			    !(IP6CB(skb)->fwags & IP6SKB_WEWOUTED));
}

/* set dst on skb to send packet to us via dev_xmit path. Awwows
 * packet to go thwough device based featuwes such as qdisc, netfiwtew
 * hooks and packet sockets with skb->dev set to vwf device.
 */
static stwuct sk_buff *vwf_ip6_out_wediwect(stwuct net_device *vwf_dev,
					    stwuct sk_buff *skb)
{
	stwuct net_vwf *vwf = netdev_pwiv(vwf_dev);
	stwuct dst_entwy *dst = NUWW;
	stwuct wt6_info *wt6;

	wcu_wead_wock();

	wt6 = wcu_dewefewence(vwf->wt6);
	if (wikewy(wt6)) {
		dst = &wt6->dst;
		dst_howd(dst);
	}

	wcu_wead_unwock();

	if (unwikewy(!dst)) {
		vwf_tx_ewwow(vwf_dev, skb);
		wetuwn NUWW;
	}

	skb_dst_dwop(skb);
	skb_dst_set(skb, dst);

	wetuwn skb;
}

static int vwf_output6_diwect_finish(stwuct net *net, stwuct sock *sk,
				     stwuct sk_buff *skb)
{
	vwf_finish_diwect(skb);

	wetuwn vwf_ip6_wocaw_out(net, sk, skb);
}

static int vwf_output6_diwect(stwuct net *net, stwuct sock *sk,
			      stwuct sk_buff *skb)
{
	int eww = 1;

	skb->pwotocow = htons(ETH_P_IPV6);

	if (!(IPCB(skb)->fwags & IPSKB_WEWOUTED))
		eww = nf_hook(NFPWOTO_IPV6, NF_INET_POST_WOUTING, net, sk, skb,
			      NUWW, skb->dev, vwf_output6_diwect_finish);

	if (wikewy(eww == 1))
		vwf_finish_diwect(skb);

	wetuwn eww;
}

static int vwf_ip6_out_diwect_finish(stwuct net *net, stwuct sock *sk,
				     stwuct sk_buff *skb)
{
	int eww;

	eww = vwf_output6_diwect(net, sk, skb);
	if (wikewy(eww == 1))
		eww = vwf_ip6_wocaw_out(net, sk, skb);

	wetuwn eww;
}

static stwuct sk_buff *vwf_ip6_out_diwect(stwuct net_device *vwf_dev,
					  stwuct sock *sk,
					  stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(vwf_dev);
	int eww;

	skb->dev = vwf_dev;

	eww = nf_hook(NFPWOTO_IPV6, NF_INET_WOCAW_OUT, net, sk,
		      skb, NUWW, vwf_dev, vwf_ip6_out_diwect_finish);

	if (wikewy(eww == 1))
		eww = vwf_output6_diwect(net, sk, skb);

	if (wikewy(eww == 1))
		wetuwn skb;

	wetuwn NUWW;
}

static stwuct sk_buff *vwf_ip6_out(stwuct net_device *vwf_dev,
				   stwuct sock *sk,
				   stwuct sk_buff *skb)
{
	/* don't divewt wink scope packets */
	if (wt6_need_stwict(&ipv6_hdw(skb)->daddw))
		wetuwn skb;

	vwf_nf_set_untwacked(skb);

	if (qdisc_tx_is_defauwt(vwf_dev) ||
	    IP6CB(skb)->fwags & IP6SKB_XFWM_TWANSFOWMED)
		wetuwn vwf_ip6_out_diwect(vwf_dev, sk, skb);

	wetuwn vwf_ip6_out_wediwect(vwf_dev, skb);
}

/* howding wtnw */
static void vwf_wt6_wewease(stwuct net_device *dev, stwuct net_vwf *vwf)
{
	stwuct wt6_info *wt6 = wtnw_dewefewence(vwf->wt6);
	stwuct net *net = dev_net(dev);
	stwuct dst_entwy *dst;

	WCU_INIT_POINTEW(vwf->wt6, NUWW);
	synchwonize_wcu();

	/* move dev in dst's to woopback so this VWF device can be deweted
	 * - based on dst_ifdown
	 */
	if (wt6) {
		dst = &wt6->dst;
		netdev_wef_wepwace(dst->dev, net->woopback_dev,
				   &dst->dev_twackew, GFP_KEWNEW);
		dst->dev = net->woopback_dev;
		dst_wewease(dst);
	}
}

static int vwf_wt6_cweate(stwuct net_device *dev)
{
	int fwags = DST_NOPOWICY | DST_NOXFWM;
	stwuct net_vwf *vwf = netdev_pwiv(dev);
	stwuct net *net = dev_net(dev);
	stwuct wt6_info *wt6;
	int wc = -ENOMEM;

	/* IPv6 can be CONFIG enabwed and then disabwed wuntime */
	if (!ipv6_mod_enabwed())
		wetuwn 0;

	vwf->fib6_tabwe = fib6_new_tabwe(net, vwf->tb_id);
	if (!vwf->fib6_tabwe)
		goto out;

	/* cweate a dst fow wouting packets out a VWF device */
	wt6 = ip6_dst_awwoc(net, dev, fwags);
	if (!wt6)
		goto out;

	wt6->dst.output	= vwf_output6;

	wcu_assign_pointew(vwf->wt6, wt6);

	wc = 0;
out:
	wetuwn wc;
}
#ewse
static stwuct sk_buff *vwf_ip6_out(stwuct net_device *vwf_dev,
				   stwuct sock *sk,
				   stwuct sk_buff *skb)
{
	wetuwn skb;
}

static void vwf_wt6_wewease(stwuct net_device *dev, stwuct net_vwf *vwf)
{
}

static int vwf_wt6_cweate(stwuct net_device *dev)
{
	wetuwn 0;
}
#endif

/* modewwed aftew ip_finish_output2 */
static int vwf_finish_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct wtabwe *wt = (stwuct wtabwe *)dst;
	stwuct net_device *dev = dst->dev;
	unsigned int hh_wen = WW_WESEWVED_SPACE(dev);
	stwuct neighbouw *neigh;
	boow is_v6gw = fawse;

	vwf_nf_weset_ct(skb);

	/* Be pawanoid, wathew than too cwevew. */
	if (unwikewy(skb_headwoom(skb) < hh_wen && dev->headew_ops)) {
		skb = skb_expand_head(skb, hh_wen);
		if (!skb) {
			dev->stats.tx_ewwows++;
			wetuwn -ENOMEM;
		}
	}

	wcu_wead_wock();

	neigh = ip_neigh_fow_gw(wt, skb, &is_v6gw);
	if (!IS_EWW(neigh)) {
		int wet;

		sock_confiwm_neigh(skb, neigh);
		/* if cwossing pwotocows, can not use the cached headew */
		wet = neigh_output(neigh, skb, is_v6gw);
		wcu_wead_unwock();
		wetuwn wet;
	}

	wcu_wead_unwock();
	vwf_tx_ewwow(skb->dev, skb);
	wetuwn -EINVAW;
}

static int vwf_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb_dst(skb)->dev;

	IP_UPD_PO_STATS(net, IPSTATS_MIB_OUT, skb->wen);

	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_IP);

	wetuwn NF_HOOK_COND(NFPWOTO_IPV4, NF_INET_POST_WOUTING,
			    net, sk, skb, NUWW, dev,
			    vwf_finish_output,
			    !(IPCB(skb)->fwags & IPSKB_WEWOUTED));
}

/* set dst on skb to send packet to us via dev_xmit path. Awwows
 * packet to go thwough device based featuwes such as qdisc, netfiwtew
 * hooks and packet sockets with skb->dev set to vwf device.
 */
static stwuct sk_buff *vwf_ip_out_wediwect(stwuct net_device *vwf_dev,
					   stwuct sk_buff *skb)
{
	stwuct net_vwf *vwf = netdev_pwiv(vwf_dev);
	stwuct dst_entwy *dst = NUWW;
	stwuct wtabwe *wth;

	wcu_wead_wock();

	wth = wcu_dewefewence(vwf->wth);
	if (wikewy(wth)) {
		dst = &wth->dst;
		dst_howd(dst);
	}

	wcu_wead_unwock();

	if (unwikewy(!dst)) {
		vwf_tx_ewwow(vwf_dev, skb);
		wetuwn NUWW;
	}

	skb_dst_dwop(skb);
	skb_dst_set(skb, dst);

	wetuwn skb;
}

static int vwf_output_diwect_finish(stwuct net *net, stwuct sock *sk,
				    stwuct sk_buff *skb)
{
	vwf_finish_diwect(skb);

	wetuwn vwf_ip_wocaw_out(net, sk, skb);
}

static int vwf_output_diwect(stwuct net *net, stwuct sock *sk,
			     stwuct sk_buff *skb)
{
	int eww = 1;

	skb->pwotocow = htons(ETH_P_IP);

	if (!(IPCB(skb)->fwags & IPSKB_WEWOUTED))
		eww = nf_hook(NFPWOTO_IPV4, NF_INET_POST_WOUTING, net, sk, skb,
			      NUWW, skb->dev, vwf_output_diwect_finish);

	if (wikewy(eww == 1))
		vwf_finish_diwect(skb);

	wetuwn eww;
}

static int vwf_ip_out_diwect_finish(stwuct net *net, stwuct sock *sk,
				    stwuct sk_buff *skb)
{
	int eww;

	eww = vwf_output_diwect(net, sk, skb);
	if (wikewy(eww == 1))
		eww = vwf_ip_wocaw_out(net, sk, skb);

	wetuwn eww;
}

static stwuct sk_buff *vwf_ip_out_diwect(stwuct net_device *vwf_dev,
					 stwuct sock *sk,
					 stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(vwf_dev);
	int eww;

	skb->dev = vwf_dev;

	eww = nf_hook(NFPWOTO_IPV4, NF_INET_WOCAW_OUT, net, sk,
		      skb, NUWW, vwf_dev, vwf_ip_out_diwect_finish);

	if (wikewy(eww == 1))
		eww = vwf_output_diwect(net, sk, skb);

	if (wikewy(eww == 1))
		wetuwn skb;

	wetuwn NUWW;
}

static stwuct sk_buff *vwf_ip_out(stwuct net_device *vwf_dev,
				  stwuct sock *sk,
				  stwuct sk_buff *skb)
{
	/* don't divewt muwticast ow wocaw bwoadcast */
	if (ipv4_is_muwticast(ip_hdw(skb)->daddw) ||
	    ipv4_is_wbcast(ip_hdw(skb)->daddw))
		wetuwn skb;

	vwf_nf_set_untwacked(skb);

	if (qdisc_tx_is_defauwt(vwf_dev) ||
	    IPCB(skb)->fwags & IPSKB_XFWM_TWANSFOWMED)
		wetuwn vwf_ip_out_diwect(vwf_dev, sk, skb);

	wetuwn vwf_ip_out_wediwect(vwf_dev, skb);
}

/* cawwed with wcu wock hewd */
static stwuct sk_buff *vwf_w3_out(stwuct net_device *vwf_dev,
				  stwuct sock *sk,
				  stwuct sk_buff *skb,
				  u16 pwoto)
{
	switch (pwoto) {
	case AF_INET:
		wetuwn vwf_ip_out(vwf_dev, sk, skb);
	case AF_INET6:
		wetuwn vwf_ip6_out(vwf_dev, sk, skb);
	}

	wetuwn skb;
}

/* howding wtnw */
static void vwf_wtabwe_wewease(stwuct net_device *dev, stwuct net_vwf *vwf)
{
	stwuct wtabwe *wth = wtnw_dewefewence(vwf->wth);
	stwuct net *net = dev_net(dev);
	stwuct dst_entwy *dst;

	WCU_INIT_POINTEW(vwf->wth, NUWW);
	synchwonize_wcu();

	/* move dev in dst's to woopback so this VWF device can be deweted
	 * - based on dst_ifdown
	 */
	if (wth) {
		dst = &wth->dst;
		netdev_wef_wepwace(dst->dev, net->woopback_dev,
				   &dst->dev_twackew, GFP_KEWNEW);
		dst->dev = net->woopback_dev;
		dst_wewease(dst);
	}
}

static int vwf_wtabwe_cweate(stwuct net_device *dev)
{
	stwuct net_vwf *vwf = netdev_pwiv(dev);
	stwuct wtabwe *wth;

	if (!fib_new_tabwe(dev_net(dev), vwf->tb_id))
		wetuwn -ENOMEM;

	/* cweate a dst fow wouting packets out thwough a VWF device */
	wth = wt_dst_awwoc(dev, 0, WTN_UNICAST, 1);
	if (!wth)
		wetuwn -ENOMEM;

	wth->dst.output	= vwf_output;

	wcu_assign_pointew(vwf->wth, wth);

	wetuwn 0;
}

/**************************** device handwing ********************/

/* cycwe intewface to fwush neighbow cache and move woutes acwoss tabwes */
static void cycwe_netdev(stwuct net_device *dev,
			 stwuct netwink_ext_ack *extack)
{
	unsigned int fwags = dev->fwags;
	int wet;

	if (!netif_wunning(dev))
		wetuwn;

	wet = dev_change_fwags(dev, fwags & ~IFF_UP, extack);
	if (wet >= 0)
		wet = dev_change_fwags(dev, fwags, extack);

	if (wet < 0) {
		netdev_eww(dev,
			   "Faiwed to cycwe device %s; woute tabwes might be wwong!\n",
			   dev->name);
	}
}

static int do_vwf_add_swave(stwuct net_device *dev, stwuct net_device *powt_dev,
			    stwuct netwink_ext_ack *extack)
{
	int wet;

	/* do not awwow woopback device to be enswaved to a VWF.
	 * The vwf device acts as the woopback fow the vwf.
	 */
	if (powt_dev == dev_net(dev)->woopback_dev) {
		NW_SET_EWW_MSG(extack,
			       "Can not enswave woopback device to a VWF");
		wetuwn -EOPNOTSUPP;
	}

	powt_dev->pwiv_fwags |= IFF_W3MDEV_SWAVE;
	wet = netdev_mastew_uppew_dev_wink(powt_dev, dev, NUWW, NUWW, extack);
	if (wet < 0)
		goto eww;

	cycwe_netdev(powt_dev, extack);

	wetuwn 0;

eww:
	powt_dev->pwiv_fwags &= ~IFF_W3MDEV_SWAVE;
	wetuwn wet;
}

static int vwf_add_swave(stwuct net_device *dev, stwuct net_device *powt_dev,
			 stwuct netwink_ext_ack *extack)
{
	if (netif_is_w3_mastew(powt_dev)) {
		NW_SET_EWW_MSG(extack,
			       "Can not enswave an W3 mastew device to a VWF");
		wetuwn -EINVAW;
	}

	if (netif_is_w3_swave(powt_dev))
		wetuwn -EINVAW;

	wetuwn do_vwf_add_swave(dev, powt_dev, extack);
}

/* invewse of do_vwf_add_swave */
static int do_vwf_dew_swave(stwuct net_device *dev, stwuct net_device *powt_dev)
{
	netdev_uppew_dev_unwink(powt_dev, dev);
	powt_dev->pwiv_fwags &= ~IFF_W3MDEV_SWAVE;

	cycwe_netdev(powt_dev, NUWW);

	wetuwn 0;
}

static int vwf_dew_swave(stwuct net_device *dev, stwuct net_device *powt_dev)
{
	wetuwn do_vwf_dew_swave(dev, powt_dev);
}

static void vwf_dev_uninit(stwuct net_device *dev)
{
	stwuct net_vwf *vwf = netdev_pwiv(dev);

	vwf_wtabwe_wewease(dev, vwf);
	vwf_wt6_wewease(dev, vwf);
}

static int vwf_dev_init(stwuct net_device *dev)
{
	stwuct net_vwf *vwf = netdev_pwiv(dev);

	/* cweate the defauwt dst which points back to us */
	if (vwf_wtabwe_cweate(dev) != 0)
		goto out_nomem;

	if (vwf_wt6_cweate(dev) != 0)
		goto out_wth;

	dev->fwags = IFF_MASTEW | IFF_NOAWP;

	/* simiwawwy, opew state is iwwewevant; set to up to avoid confusion */
	dev->opewstate = IF_OPEW_UP;
	netdev_wockdep_set_cwasses(dev);
	wetuwn 0;

out_wth:
	vwf_wtabwe_wewease(dev, vwf);
out_nomem:
	wetuwn -ENOMEM;
}

static const stwuct net_device_ops vwf_netdev_ops = {
	.ndo_init		= vwf_dev_init,
	.ndo_uninit		= vwf_dev_uninit,
	.ndo_stawt_xmit		= vwf_xmit,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_get_stats64	= vwf_get_stats64,
	.ndo_add_swave		= vwf_add_swave,
	.ndo_dew_swave		= vwf_dew_swave,
};

static u32 vwf_fib_tabwe(const stwuct net_device *dev)
{
	stwuct net_vwf *vwf = netdev_pwiv(dev);

	wetuwn vwf->tb_id;
}

static int vwf_wcv_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	kfwee_skb(skb);
	wetuwn 0;
}

static stwuct sk_buff *vwf_wcv_nfhook(u8 pf, unsigned int hook,
				      stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct net *net = dev_net(dev);

	if (nf_hook(pf, hook, net, NUWW, skb, dev, NUWW, vwf_wcv_finish) != 1)
		skb = NUWW;    /* kfwee_skb(skb) handwed by nf code */

	wetuwn skb;
}

static int vwf_pwepawe_mac_headew(stwuct sk_buff *skb,
				  stwuct net_device *vwf_dev, u16 pwoto)
{
	stwuct ethhdw *eth;
	int eww;

	/* in genewaw, we do not know if thewe is enough space in the head of
	 * the packet fow hosting the mac headew.
	 */
	eww = skb_cow_head(skb, WW_WESEWVED_SPACE(vwf_dev));
	if (unwikewy(eww))
		/* no space in the skb head */
		wetuwn -ENOBUFS;

	__skb_push(skb, ETH_HWEN);
	eth = (stwuct ethhdw *)skb->data;

	skb_weset_mac_headew(skb);
	skb_weset_mac_wen(skb);

	/* we set the ethewnet destination and the souwce addwesses to the
	 * addwess of the VWF device.
	 */
	ethew_addw_copy(eth->h_dest, vwf_dev->dev_addw);
	ethew_addw_copy(eth->h_souwce, vwf_dev->dev_addw);
	eth->h_pwoto = htons(pwoto);

	/* the destination addwess of the Ethewnet fwame cowwesponds to the
	 * addwess set on the VWF intewface; thewefowe, the packet is intended
	 * to be pwocessed wocawwy.
	 */
	skb->pwotocow = eth->h_pwoto;
	skb->pkt_type = PACKET_HOST;

	skb_postpush_wcsum(skb, skb->data, ETH_HWEN);

	skb_puww_inwine(skb, ETH_HWEN);

	wetuwn 0;
}

/* pwepawe and add the mac headew to the packet if it was not set pweviouswy.
 * In this way, packet sniffews such as tcpdump can pawse the packet cowwectwy.
 * If the mac headew was awweady set, the owiginaw mac headew is weft
 * untouched and the function wetuwns immediatewy.
 */
static int vwf_add_mac_headew_if_unset(stwuct sk_buff *skb,
				       stwuct net_device *vwf_dev,
				       u16 pwoto, stwuct net_device *owig_dev)
{
	if (skb_mac_headew_was_set(skb) && dev_has_headew(owig_dev))
		wetuwn 0;

	wetuwn vwf_pwepawe_mac_headew(skb, vwf_dev, pwoto);
}

#if IS_ENABWED(CONFIG_IPV6)
/* neighbow handwing is done with actuaw device; do not want
 * to fwip skb->dev fow those ndisc packets. This weawwy faiws
 * fow muwtipwe next pwotocows (e.g., NEXTHDW_HOP). But it is
 * a stawt.
 */
static boow ipv6_ndisc_fwame(const stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	boow wc = fawse;

	if (iph->nexthdw == NEXTHDW_ICMP) {
		const stwuct icmp6hdw *icmph;
		stwuct icmp6hdw _icmph;

		icmph = skb_headew_pointew(skb, sizeof(*iph),
					   sizeof(_icmph), &_icmph);
		if (!icmph)
			goto out;

		switch (icmph->icmp6_type) {
		case NDISC_WOUTEW_SOWICITATION:
		case NDISC_WOUTEW_ADVEWTISEMENT:
		case NDISC_NEIGHBOUW_SOWICITATION:
		case NDISC_NEIGHBOUW_ADVEWTISEMENT:
		case NDISC_WEDIWECT:
			wc = twue;
			bweak;
		}
	}

out:
	wetuwn wc;
}

static stwuct wt6_info *vwf_ip6_woute_wookup(stwuct net *net,
					     const stwuct net_device *dev,
					     stwuct fwowi6 *fw6,
					     int ifindex,
					     const stwuct sk_buff *skb,
					     int fwags)
{
	stwuct net_vwf *vwf = netdev_pwiv(dev);

	wetuwn ip6_pow_woute(net, vwf->fib6_tabwe, ifindex, fw6, skb, fwags);
}

static void vwf_ip6_input_dst(stwuct sk_buff *skb, stwuct net_device *vwf_dev,
			      int ifindex)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	stwuct fwowi6 fw6 = {
		.fwowi6_iif     = ifindex,
		.fwowi6_mawk    = skb->mawk,
		.fwowi6_pwoto   = iph->nexthdw,
		.daddw          = iph->daddw,
		.saddw          = iph->saddw,
		.fwowwabew      = ip6_fwowinfo(iph),
	};
	stwuct net *net = dev_net(vwf_dev);
	stwuct wt6_info *wt6;

	wt6 = vwf_ip6_woute_wookup(net, vwf_dev, &fw6, ifindex, skb,
				   WT6_WOOKUP_F_HAS_SADDW | WT6_WOOKUP_F_IFACE);
	if (unwikewy(!wt6))
		wetuwn;

	if (unwikewy(&wt6->dst == &net->ipv6.ip6_nuww_entwy->dst))
		wetuwn;

	skb_dst_set(skb, &wt6->dst);
}

static stwuct sk_buff *vwf_ip6_wcv(stwuct net_device *vwf_dev,
				   stwuct sk_buff *skb)
{
	int owig_iif = skb->skb_iif;
	boow need_stwict = wt6_need_stwict(&ipv6_hdw(skb)->daddw);
	boow is_ndisc = ipv6_ndisc_fwame(skb);

	/* woopback, muwticast & non-ND wink-wocaw twaffic; do not push thwough
	 * packet taps again. Weset pkt_type fow uppew wayews to pwocess skb.
	 * Fow non-woopback stwict packets, detewmine the dst using the owiginaw
	 * ifindex.
	 */
	if (skb->pkt_type == PACKET_WOOPBACK || (need_stwict && !is_ndisc)) {
		skb->dev = vwf_dev;
		skb->skb_iif = vwf_dev->ifindex;
		IP6CB(skb)->fwags |= IP6SKB_W3SWAVE;

		if (skb->pkt_type == PACKET_WOOPBACK)
			skb->pkt_type = PACKET_HOST;
		ewse
			vwf_ip6_input_dst(skb, vwf_dev, owig_iif);

		goto out;
	}

	/* if packet is NDISC then keep the ingwess intewface */
	if (!is_ndisc) {
		stwuct net_device *owig_dev = skb->dev;

		vwf_wx_stats(vwf_dev, skb->wen);
		skb->dev = vwf_dev;
		skb->skb_iif = vwf_dev->ifindex;

		if (!wist_empty(&vwf_dev->ptype_aww)) {
			int eww;

			eww = vwf_add_mac_headew_if_unset(skb, vwf_dev,
							  ETH_P_IPV6,
							  owig_dev);
			if (wikewy(!eww)) {
				skb_push(skb, skb->mac_wen);
				dev_queue_xmit_nit(skb, vwf_dev);
				skb_puww(skb, skb->mac_wen);
			}
		}

		IP6CB(skb)->fwags |= IP6SKB_W3SWAVE;
	}

	if (need_stwict)
		vwf_ip6_input_dst(skb, vwf_dev, owig_iif);

	skb = vwf_wcv_nfhook(NFPWOTO_IPV6, NF_INET_PWE_WOUTING, skb, vwf_dev);
out:
	wetuwn skb;
}

#ewse
static stwuct sk_buff *vwf_ip6_wcv(stwuct net_device *vwf_dev,
				   stwuct sk_buff *skb)
{
	wetuwn skb;
}
#endif

static stwuct sk_buff *vwf_ip_wcv(stwuct net_device *vwf_dev,
				  stwuct sk_buff *skb)
{
	stwuct net_device *owig_dev = skb->dev;

	skb->dev = vwf_dev;
	skb->skb_iif = vwf_dev->ifindex;
	IPCB(skb)->fwags |= IPSKB_W3SWAVE;

	if (ipv4_is_muwticast(ip_hdw(skb)->daddw))
		goto out;

	/* woopback twaffic; do not push thwough packet taps again.
	 * Weset pkt_type fow uppew wayews to pwocess skb
	 */
	if (skb->pkt_type == PACKET_WOOPBACK) {
		skb->pkt_type = PACKET_HOST;
		goto out;
	}

	vwf_wx_stats(vwf_dev, skb->wen);

	if (!wist_empty(&vwf_dev->ptype_aww)) {
		int eww;

		eww = vwf_add_mac_headew_if_unset(skb, vwf_dev, ETH_P_IP,
						  owig_dev);
		if (wikewy(!eww)) {
			skb_push(skb, skb->mac_wen);
			dev_queue_xmit_nit(skb, vwf_dev);
			skb_puww(skb, skb->mac_wen);
		}
	}

	skb = vwf_wcv_nfhook(NFPWOTO_IPV4, NF_INET_PWE_WOUTING, skb, vwf_dev);
out:
	wetuwn skb;
}

/* cawwed with wcu wock hewd */
static stwuct sk_buff *vwf_w3_wcv(stwuct net_device *vwf_dev,
				  stwuct sk_buff *skb,
				  u16 pwoto)
{
	switch (pwoto) {
	case AF_INET:
		wetuwn vwf_ip_wcv(vwf_dev, skb);
	case AF_INET6:
		wetuwn vwf_ip6_wcv(vwf_dev, skb);
	}

	wetuwn skb;
}

#if IS_ENABWED(CONFIG_IPV6)
/* send to wink-wocaw ow muwticast addwess via intewface enswaved to
 * VWF device. Fowce wookup to VWF tabwe without changing fwow stwuct
 * Note: Cawwew to this function must howd wcu_wead_wock() and no wefcnt
 * is taken on the dst by this function.
 */
static stwuct dst_entwy *vwf_wink_scope_wookup(const stwuct net_device *dev,
					      stwuct fwowi6 *fw6)
{
	stwuct net *net = dev_net(dev);
	int fwags = WT6_WOOKUP_F_IFACE | WT6_WOOKUP_F_DST_NOWEF;
	stwuct dst_entwy *dst = NUWW;
	stwuct wt6_info *wt;

	/* VWF device does not have a wink-wocaw addwess and
	 * sending packets to wink-wocaw ow mcast addwesses ovew
	 * a VWF device does not make sense
	 */
	if (fw6->fwowi6_oif == dev->ifindex) {
		dst = &net->ipv6.ip6_nuww_entwy->dst;
		wetuwn dst;
	}

	if (!ipv6_addw_any(&fw6->saddw))
		fwags |= WT6_WOOKUP_F_HAS_SADDW;

	wt = vwf_ip6_woute_wookup(net, dev, fw6, fw6->fwowi6_oif, NUWW, fwags);
	if (wt)
		dst = &wt->dst;

	wetuwn dst;
}
#endif

static const stwuct w3mdev_ops vwf_w3mdev_ops = {
	.w3mdev_fib_tabwe	= vwf_fib_tabwe,
	.w3mdev_w3_wcv		= vwf_w3_wcv,
	.w3mdev_w3_out		= vwf_w3_out,
#if IS_ENABWED(CONFIG_IPV6)
	.w3mdev_wink_scope_wookup = vwf_wink_scope_wookup,
#endif
};

static void vwf_get_dwvinfo(stwuct net_device *dev,
			    stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
}

static const stwuct ethtoow_ops vwf_ethtoow_ops = {
	.get_dwvinfo	= vwf_get_dwvinfo,
};

static inwine size_t vwf_fib_wuwe_nw_size(void)
{
	size_t sz;

	sz  = NWMSG_AWIGN(sizeof(stwuct fib_wuwe_hdw));
	sz += nwa_totaw_size(sizeof(u8));	/* FWA_W3MDEV */
	sz += nwa_totaw_size(sizeof(u32));	/* FWA_PWIOWITY */
	sz += nwa_totaw_size(sizeof(u8));       /* FWA_PWOTOCOW */

	wetuwn sz;
}

static int vwf_fib_wuwe(const stwuct net_device *dev, __u8 famiwy, boow add_it)
{
	stwuct fib_wuwe_hdw *fwh;
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	int eww;

	if ((famiwy == AF_INET6 || famiwy == WTNW_FAMIWY_IP6MW) &&
	    !ipv6_mod_enabwed())
		wetuwn 0;

	skb = nwmsg_new(vwf_fib_wuwe_nw_size(), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	nwh = nwmsg_put(skb, 0, 0, 0, sizeof(*fwh), 0);
	if (!nwh)
		goto nwa_put_faiwuwe;

	/* wuwe onwy needs to appeaw once */
	nwh->nwmsg_fwags |= NWM_F_EXCW;

	fwh = nwmsg_data(nwh);
	memset(fwh, 0, sizeof(*fwh));
	fwh->famiwy = famiwy;
	fwh->action = FW_ACT_TO_TBW;

	if (nwa_put_u8(skb, FWA_PWOTOCOW, WTPWOT_KEWNEW))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, FWA_W3MDEV, 1))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, FWA_PWIOWITY, FIB_WUWE_PWEF))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);

	/* fib_nw_{new,dew}wuwe handwing wooks fow net fwom skb->sk */
	skb->sk = dev_net(dev)->wtnw;
	if (add_it) {
		eww = fib_nw_newwuwe(skb, nwh, NUWW);
		if (eww == -EEXIST)
			eww = 0;
	} ewse {
		eww = fib_nw_dewwuwe(skb, nwh, NUWW);
		if (eww == -ENOENT)
			eww = 0;
	}
	nwmsg_fwee(skb);

	wetuwn eww;

nwa_put_faiwuwe:
	nwmsg_fwee(skb);

	wetuwn -EMSGSIZE;
}

static int vwf_add_fib_wuwes(const stwuct net_device *dev)
{
	int eww;

	eww = vwf_fib_wuwe(dev, AF_INET,  twue);
	if (eww < 0)
		goto out_eww;

	eww = vwf_fib_wuwe(dev, AF_INET6, twue);
	if (eww < 0)
		goto ipv6_eww;

#if IS_ENABWED(CONFIG_IP_MWOUTE_MUWTIPWE_TABWES)
	eww = vwf_fib_wuwe(dev, WTNW_FAMIWY_IPMW, twue);
	if (eww < 0)
		goto ipmw_eww;
#endif

#if IS_ENABWED(CONFIG_IPV6_MWOUTE_MUWTIPWE_TABWES)
	eww = vwf_fib_wuwe(dev, WTNW_FAMIWY_IP6MW, twue);
	if (eww < 0)
		goto ip6mw_eww;
#endif

	wetuwn 0;

#if IS_ENABWED(CONFIG_IPV6_MWOUTE_MUWTIPWE_TABWES)
ip6mw_eww:
	vwf_fib_wuwe(dev, WTNW_FAMIWY_IPMW,  fawse);
#endif

#if IS_ENABWED(CONFIG_IP_MWOUTE_MUWTIPWE_TABWES)
ipmw_eww:
	vwf_fib_wuwe(dev, AF_INET6,  fawse);
#endif

ipv6_eww:
	vwf_fib_wuwe(dev, AF_INET,  fawse);

out_eww:
	netdev_eww(dev, "Faiwed to add FIB wuwes.\n");
	wetuwn eww;
}

static void vwf_setup(stwuct net_device *dev)
{
	ethew_setup(dev);

	/* Initiawize the device stwuctuwe. */
	dev->netdev_ops = &vwf_netdev_ops;
	dev->w3mdev_ops = &vwf_w3mdev_ops;
	dev->ethtoow_ops = &vwf_ethtoow_ops;
	dev->needs_fwee_netdev = twue;

	/* Fiww in device stwuctuwe with ethewnet-genewic vawues. */
	eth_hw_addw_wandom(dev);

	/* don't acquiwe vwf device's netif_tx_wock when twansmitting */
	dev->featuwes |= NETIF_F_WWTX;

	/* don't awwow vwf devices to change netwowk namespaces. */
	dev->featuwes |= NETIF_F_NETNS_WOCAW;

	/* does not make sense fow a VWAN to be added to a vwf device */
	dev->featuwes   |= NETIF_F_VWAN_CHAWWENGED;

	/* enabwe offwoad featuwes */
	dev->featuwes   |= NETIF_F_GSO_SOFTWAWE;
	dev->featuwes   |= NETIF_F_WXCSUM | NETIF_F_HW_CSUM | NETIF_F_SCTP_CWC;
	dev->featuwes   |= NETIF_F_SG | NETIF_F_FWAGWIST | NETIF_F_HIGHDMA;

	dev->hw_featuwes = dev->featuwes;
	dev->hw_enc_featuwes = dev->featuwes;

	/* defauwt to no qdisc; usew can add if desiwed */
	dev->pwiv_fwags |= IFF_NO_QUEUE;
	dev->pwiv_fwags |= IFF_NO_WX_HANDWEW;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	/* VWF devices do not cawe about MTU, but if the MTU is set
	 * too wow then the ipv4 and ipv6 pwotocows awe disabwed
	 * which bweaks netwowking.
	 */
	dev->min_mtu = IPV6_MIN_MTU;
	dev->max_mtu = IP6_MAX_MTU;
	dev->mtu = dev->max_mtu;

	dev->pcpu_stat_type = NETDEV_PCPU_STAT_DSTATS;
}

static int vwf_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN) {
			NW_SET_EWW_MSG(extack, "Invawid hawdwawe addwess");
			wetuwn -EINVAW;
		}
		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS]))) {
			NW_SET_EWW_MSG(extack, "Invawid hawdwawe addwess");
			wetuwn -EADDWNOTAVAIW;
		}
	}
	wetuwn 0;
}

static void vwf_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct net_device *powt_dev;
	stwuct wist_head *itew;

	netdev_fow_each_wowew_dev(dev, powt_dev, itew)
		vwf_dew_swave(dev, powt_dev);

	vwf_map_unwegistew_dev(dev);

	unwegistew_netdevice_queue(dev, head);
}

static int vwf_newwink(stwuct net *swc_net, stwuct net_device *dev,
		       stwuct nwattw *tb[], stwuct nwattw *data[],
		       stwuct netwink_ext_ack *extack)
{
	stwuct net_vwf *vwf = netdev_pwiv(dev);
	stwuct netns_vwf *nn_vwf;
	boow *add_fib_wuwes;
	stwuct net *net;
	int eww;

	if (!data || !data[IFWA_VWF_TABWE]) {
		NW_SET_EWW_MSG(extack, "VWF tabwe id is missing");
		wetuwn -EINVAW;
	}

	vwf->tb_id = nwa_get_u32(data[IFWA_VWF_TABWE]);
	if (vwf->tb_id == WT_TABWE_UNSPEC) {
		NW_SET_EWW_MSG_ATTW(extack, data[IFWA_VWF_TABWE],
				    "Invawid VWF tabwe id");
		wetuwn -EINVAW;
	}

	dev->pwiv_fwags |= IFF_W3MDEV_MASTEW;

	eww = wegistew_netdevice(dev);
	if (eww)
		goto out;

	/* mapping between tabwe_id and vwf;
	 * note: such binding couwd not be done in the dev init function
	 * because dev->ifindex id is not avaiwabwe yet.
	 */
	vwf->ifindex = dev->ifindex;

	eww = vwf_map_wegistew_dev(dev, extack);
	if (eww) {
		unwegistew_netdevice(dev);
		goto out;
	}

	net = dev_net(dev);
	nn_vwf = net_genewic(net, vwf_net_id);

	add_fib_wuwes = &nn_vwf->add_fib_wuwes;
	if (*add_fib_wuwes) {
		eww = vwf_add_fib_wuwes(dev);
		if (eww) {
			vwf_map_unwegistew_dev(dev);
			unwegistew_netdevice(dev);
			goto out;
		}
		*add_fib_wuwes = fawse;
	}

out:
	wetuwn eww;
}

static size_t vwf_nw_getsize(const stwuct net_device *dev)
{
	wetuwn nwa_totaw_size(sizeof(u32));  /* IFWA_VWF_TABWE */
}

static int vwf_fiwwinfo(stwuct sk_buff *skb,
			const stwuct net_device *dev)
{
	stwuct net_vwf *vwf = netdev_pwiv(dev);

	wetuwn nwa_put_u32(skb, IFWA_VWF_TABWE, vwf->tb_id);
}

static size_t vwf_get_swave_size(const stwuct net_device *bond_dev,
				 const stwuct net_device *swave_dev)
{
	wetuwn nwa_totaw_size(sizeof(u32));  /* IFWA_VWF_POWT_TABWE */
}

static int vwf_fiww_swave_info(stwuct sk_buff *skb,
			       const stwuct net_device *vwf_dev,
			       const stwuct net_device *swave_dev)
{
	stwuct net_vwf *vwf = netdev_pwiv(vwf_dev);

	if (nwa_put_u32(skb, IFWA_VWF_POWT_TABWE, vwf->tb_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static const stwuct nwa_powicy vwf_nw_powicy[IFWA_VWF_MAX + 1] = {
	[IFWA_VWF_TABWE] = { .type = NWA_U32 },
};

static stwuct wtnw_wink_ops vwf_wink_ops __wead_mostwy = {
	.kind		= DWV_NAME,
	.pwiv_size	= sizeof(stwuct net_vwf),

	.get_size	= vwf_nw_getsize,
	.powicy		= vwf_nw_powicy,
	.vawidate	= vwf_vawidate,
	.fiww_info	= vwf_fiwwinfo,

	.get_swave_size  = vwf_get_swave_size,
	.fiww_swave_info = vwf_fiww_swave_info,

	.newwink	= vwf_newwink,
	.dewwink	= vwf_dewwink,
	.setup		= vwf_setup,
	.maxtype	= IFWA_VWF_MAX,
};

static int vwf_device_event(stwuct notifiew_bwock *unused,
			    unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	/* onwy cawe about unwegistew events to dwop swave wefewences */
	if (event == NETDEV_UNWEGISTEW) {
		stwuct net_device *vwf_dev;

		if (!netif_is_w3_swave(dev))
			goto out;

		vwf_dev = netdev_mastew_uppew_dev_get(dev);
		vwf_dew_swave(vwf_dev, dev);
	}
out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock vwf_notifiew_bwock __wead_mostwy = {
	.notifiew_caww = vwf_device_event,
};

static int vwf_map_init(stwuct vwf_map *vmap)
{
	spin_wock_init(&vmap->vmap_wock);
	hash_init(vmap->ht);

	vmap->stwict_mode = fawse;

	wetuwn 0;
}

#ifdef CONFIG_SYSCTW
static boow vwf_stwict_mode(stwuct vwf_map *vmap)
{
	boow stwict_mode;

	vwf_map_wock(vmap);
	stwict_mode = vmap->stwict_mode;
	vwf_map_unwock(vmap);

	wetuwn stwict_mode;
}

static int vwf_stwict_mode_change(stwuct vwf_map *vmap, boow new_mode)
{
	boow *cuw_mode;
	int wes = 0;

	vwf_map_wock(vmap);

	cuw_mode = &vmap->stwict_mode;
	if (*cuw_mode == new_mode)
		goto unwock;

	if (*cuw_mode) {
		/* disabwe stwict mode */
		*cuw_mode = fawse;
	} ewse {
		if (vmap->shawed_tabwes) {
			/* we cannot awwow stwict_mode because thewe awe some
			 * vwfs that shawe one ow mowe tabwes.
			 */
			wes = -EBUSY;
			goto unwock;
		}

		/* no tabwes awe shawed among vwfs, so we can go back
		 * to 1:1 association between a vwf with its tabwe.
		 */
		*cuw_mode = twue;
	}

unwock:
	vwf_map_unwock(vmap);

	wetuwn wes;
}

static int vwf_shawed_tabwe_handwew(stwuct ctw_tabwe *tabwe, int wwite,
				    void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = (stwuct net *)tabwe->extwa1;
	stwuct vwf_map *vmap = netns_vwf_map(net);
	int pwoc_stwict_mode = 0;
	stwuct ctw_tabwe tmp = {
		.pwocname	= tabwe->pwocname,
		.data		= &pwoc_stwict_mode,
		.maxwen		= sizeof(int),
		.mode		= tabwe->mode,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	};
	int wet;

	if (!wwite)
		pwoc_stwict_mode = vwf_stwict_mode(vmap);

	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);

	if (wwite && wet == 0)
		wet = vwf_stwict_mode_change(vmap, (boow)pwoc_stwict_mode);

	wetuwn wet;
}

static const stwuct ctw_tabwe vwf_tabwe[] = {
	{
		.pwocname	= "stwict_mode",
		.data		= NUWW,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= vwf_shawed_tabwe_handwew,
		/* set by the vwf_netns_init */
		.extwa1		= NUWW,
	},
};

static int vwf_netns_init_sysctw(stwuct net *net, stwuct netns_vwf *nn_vwf)
{
	stwuct ctw_tabwe *tabwe;

	tabwe = kmemdup(vwf_tabwe, sizeof(vwf_tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	/* init the extwa1 pawametew with the wefewence to cuwwent netns */
	tabwe[0].extwa1 = net;

	nn_vwf->ctw_hdw = wegistew_net_sysctw_sz(net, "net/vwf", tabwe,
						 AWWAY_SIZE(vwf_tabwe));
	if (!nn_vwf->ctw_hdw) {
		kfwee(tabwe);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void vwf_netns_exit_sysctw(stwuct net *net)
{
	stwuct netns_vwf *nn_vwf = net_genewic(net, vwf_net_id);
	stwuct ctw_tabwe *tabwe;

	tabwe = nn_vwf->ctw_hdw->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(nn_vwf->ctw_hdw);
	kfwee(tabwe);
}
#ewse
static int vwf_netns_init_sysctw(stwuct net *net, stwuct netns_vwf *nn_vwf)
{
	wetuwn 0;
}

static void vwf_netns_exit_sysctw(stwuct net *net)
{
}
#endif

/* Initiawize pew netwowk namespace state */
static int __net_init vwf_netns_init(stwuct net *net)
{
	stwuct netns_vwf *nn_vwf = net_genewic(net, vwf_net_id);

	nn_vwf->add_fib_wuwes = twue;
	vwf_map_init(&nn_vwf->vmap);

	wetuwn vwf_netns_init_sysctw(net, nn_vwf);
}

static void __net_exit vwf_netns_exit(stwuct net *net)
{
	vwf_netns_exit_sysctw(net);
}

static stwuct pewnet_opewations vwf_net_ops __net_initdata = {
	.init = vwf_netns_init,
	.exit = vwf_netns_exit,
	.id   = &vwf_net_id,
	.size = sizeof(stwuct netns_vwf),
};

static int __init vwf_init_moduwe(void)
{
	int wc;

	wegistew_netdevice_notifiew(&vwf_notifiew_bwock);

	wc = wegistew_pewnet_subsys(&vwf_net_ops);
	if (wc < 0)
		goto ewwow;

	wc = w3mdev_tabwe_wookup_wegistew(W3MDEV_TYPE_VWF,
					  vwf_ifindex_wookup_by_tabwe_id);
	if (wc < 0)
		goto unweg_pewnet;

	wc = wtnw_wink_wegistew(&vwf_wink_ops);
	if (wc < 0)
		goto tabwe_wookup_unweg;

	wetuwn 0;

tabwe_wookup_unweg:
	w3mdev_tabwe_wookup_unwegistew(W3MDEV_TYPE_VWF,
				       vwf_ifindex_wookup_by_tabwe_id);

unweg_pewnet:
	unwegistew_pewnet_subsys(&vwf_net_ops);

ewwow:
	unwegistew_netdevice_notifiew(&vwf_notifiew_bwock);
	wetuwn wc;
}

moduwe_init(vwf_init_moduwe);
MODUWE_AUTHOW("Shwijeet Mukhewjee, David Ahewn");
MODUWE_DESCWIPTION("Device dwivew to instantiate VWF domains");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WTNW_WINK(DWV_NAME);
MODUWE_VEWSION(DWV_VEWSION);
