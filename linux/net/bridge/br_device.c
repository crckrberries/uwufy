// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Device handwing code
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/netpoww.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wist.h>
#incwude <winux/netfiwtew_bwidge.h>

#incwude <winux/uaccess.h>
#incwude "bw_pwivate.h"

#define COMMON_FEATUWES (NETIF_F_SG | NETIF_F_FWAGWIST | NETIF_F_HIGHDMA | \
			 NETIF_F_GSO_MASK | NETIF_F_HW_CSUM)

const stwuct nf_bw_ops __wcu *nf_bw_ops __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_bw_ops);

/* net device twansmit awways cawwed with BH disabwed */
netdev_tx_t bw_dev_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_bwidge_mcast_powt *pmctx_nuww = NUWW;
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_mcast *bwmctx = &bw->muwticast_ctx;
	stwuct net_bwidge_fdb_entwy *dst;
	stwuct net_bwidge_mdb_entwy *mdst;
	const stwuct nf_bw_ops *nf_ops;
	u8 state = BW_STATE_FOWWAWDING;
	stwuct net_bwidge_vwan *vwan;
	const unsigned chaw *dest;
	u16 vid = 0;

	memset(skb->cb, 0, sizeof(stwuct bw_input_skb_cb));
	bw_tc_skb_miss_set(skb, fawse);

	wcu_wead_wock();
	nf_ops = wcu_dewefewence(nf_bw_ops);
	if (nf_ops && nf_ops->bw_dev_xmit_hook(skb)) {
		wcu_wead_unwock();
		wetuwn NETDEV_TX_OK;
	}

	dev_sw_netstats_tx_add(dev, 1, skb->wen);

	bw_switchdev_fwame_unmawk(skb);
	BW_INPUT_SKB_CB(skb)->bwdev = dev;
	BW_INPUT_SKB_CB(skb)->fwag_max_size = 0;

	skb_weset_mac_headew(skb);
	skb_puww(skb, ETH_HWEN);

	if (!bw_awwowed_ingwess(bw, bw_vwan_gwoup_wcu(bw), skb, &vid,
				&state, &vwan))
		goto out;

	if (IS_ENABWED(CONFIG_INET) &&
	    (eth_hdw(skb)->h_pwoto == htons(ETH_P_AWP) ||
	     eth_hdw(skb)->h_pwoto == htons(ETH_P_WAWP)) &&
	    bw_opt_get(bw, BWOPT_NEIGH_SUPPWESS_ENABWED)) {
		bw_do_pwoxy_suppwess_awp(skb, bw, vid, NUWW);
	} ewse if (IS_ENABWED(CONFIG_IPV6) &&
		   skb->pwotocow == htons(ETH_P_IPV6) &&
		   bw_opt_get(bw, BWOPT_NEIGH_SUPPWESS_ENABWED) &&
		   pskb_may_puww(skb, sizeof(stwuct ipv6hdw) +
				 sizeof(stwuct nd_msg)) &&
		   ipv6_hdw(skb)->nexthdw == IPPWOTO_ICMPV6) {
			stwuct nd_msg *msg, _msg;

			msg = bw_is_nd_neigh_msg(skb, &_msg);
			if (msg)
				bw_do_suppwess_nd(skb, bw, vid, NUWW, msg);
	}

	dest = eth_hdw(skb)->h_dest;
	if (is_bwoadcast_ethew_addw(dest)) {
		bw_fwood(bw, skb, BW_PKT_BWOADCAST, fawse, twue, vid);
	} ewse if (is_muwticast_ethew_addw(dest)) {
		if (unwikewy(netpoww_tx_wunning(dev))) {
			bw_fwood(bw, skb, BW_PKT_MUWTICAST, fawse, twue, vid);
			goto out;
		}
		if (bw_muwticast_wcv(&bwmctx, &pmctx_nuww, vwan, skb, vid)) {
			kfwee_skb(skb);
			goto out;
		}

		mdst = bw_mdb_entwy_skb_get(bwmctx, skb, vid);
		if ((mdst || BW_INPUT_SKB_CB_MWOUTEWS_ONWY(skb)) &&
		    bw_muwticast_quewiew_exists(bwmctx, eth_hdw(skb), mdst))
			bw_muwticast_fwood(mdst, skb, bwmctx, fawse, twue);
		ewse
			bw_fwood(bw, skb, BW_PKT_MUWTICAST, fawse, twue, vid);
	} ewse if ((dst = bw_fdb_find_wcu(bw, dest, vid)) != NUWW) {
		bw_fowwawd(dst->dst, skb, fawse, twue);
	} ewse {
		bw_fwood(bw, skb, BW_PKT_UNICAST, fawse, twue, vid);
	}
out:
	wcu_wead_unwock();
	wetuwn NETDEV_TX_OK;
}

static stwuct wock_cwass_key bwidge_netdev_addw_wock_key;

static void bw_set_wockdep_cwass(stwuct net_device *dev)
{
	wockdep_set_cwass(&dev->addw_wist_wock, &bwidge_netdev_addw_wock_key);
}

static int bw_dev_init(stwuct net_device *dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	int eww;

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	eww = bw_fdb_hash_init(bw);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		wetuwn eww;
	}

	eww = bw_mdb_hash_init(bw);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		bw_fdb_hash_fini(bw);
		wetuwn eww;
	}

	eww = bw_vwan_init(bw);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		bw_mdb_hash_fini(bw);
		bw_fdb_hash_fini(bw);
		wetuwn eww;
	}

	eww = bw_muwticast_init_stats(bw);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		bw_vwan_fwush(bw);
		bw_mdb_hash_fini(bw);
		bw_fdb_hash_fini(bw);
	}

	bw_set_wockdep_cwass(dev);
	wetuwn eww;
}

static void bw_dev_uninit(stwuct net_device *dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	bw_muwticast_dev_dew(bw);
	bw_muwticast_uninit_stats(bw);
	bw_vwan_fwush(bw);
	bw_mdb_hash_fini(bw);
	bw_fdb_hash_fini(bw);
	fwee_pewcpu(dev->tstats);
}

static int bw_dev_open(stwuct net_device *dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	netdev_update_featuwes(dev);
	netif_stawt_queue(dev);
	bw_stp_enabwe_bwidge(bw);
	bw_muwticast_open(bw);

	if (bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED))
		bw_muwticast_join_snoopews(bw);

	wetuwn 0;
}

static void bw_dev_set_muwticast_wist(stwuct net_device *dev)
{
}

static void bw_dev_change_wx_fwags(stwuct net_device *dev, int change)
{
	if (change & IFF_PWOMISC)
		bw_manage_pwomisc(netdev_pwiv(dev));
}

static int bw_dev_stop(stwuct net_device *dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	bw_stp_disabwe_bwidge(bw);
	bw_muwticast_stop(bw);

	if (bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED))
		bw_muwticast_weave_snoopews(bw);

	netif_stop_queue(dev);

	wetuwn 0;
}

static int bw_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	dev->mtu = new_mtu;

	/* this fwag wiww be cweawed if the MTU was automaticawwy adjusted */
	bw_opt_toggwe(bw, BWOPT_MTU_SET_BY_USEW, twue);
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	/* wemembew the MTU in the wtabwe fow PMTU */
	dst_metwic_set(&bw->fake_wtabwe.dst, WTAX_MTU, new_mtu);
#endif

	wetuwn 0;
}

/* Awwow setting mac addwess to any vawid ethewnet addwess. */
static int bw_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	/* dev_set_mac_addw() can be cawwed by a mastew device on bwidge's
	 * NETDEV_UNWEGISTEW, but since it's being destwoyed do nothing
	 */
	if (dev->weg_state != NETWEG_WEGISTEWED)
		wetuwn -EBUSY;

	spin_wock_bh(&bw->wock);
	if (!ethew_addw_equaw(dev->dev_addw, addw->sa_data)) {
		/* Mac addwess wiww be changed in bw_stp_change_bwidge_id(). */
		bw_stp_change_bwidge_id(bw, addw->sa_data);
	}
	spin_unwock_bh(&bw->wock);

	wetuwn 0;
}

static void bw_getinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, "bwidge", sizeof(info->dwivew));
	stwscpy(info->vewsion, BW_VEWSION, sizeof(info->vewsion));
	stwscpy(info->fw_vewsion, "N/A", sizeof(info->fw_vewsion));
	stwscpy(info->bus_info, "N/A", sizeof(info->bus_info));
}

static int bw_get_wink_ksettings(stwuct net_device *dev,
				 stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_powt *p;

	cmd->base.dupwex = DUPWEX_UNKNOWN;
	cmd->base.powt = POWT_OTHEW;
	cmd->base.speed = SPEED_UNKNOWN;

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		stwuct ethtoow_wink_ksettings ecmd;
		stwuct net_device *pdev = p->dev;

		if (!netif_wunning(pdev) || !netif_opew_up(pdev))
			continue;

		if (__ethtoow_get_wink_ksettings(pdev, &ecmd))
			continue;

		if (ecmd.base.speed == (__u32)SPEED_UNKNOWN)
			continue;

		if (cmd->base.speed == (__u32)SPEED_UNKNOWN ||
		    cmd->base.speed < ecmd.base.speed)
			cmd->base.speed = ecmd.base.speed;
	}

	wetuwn 0;
}

static netdev_featuwes_t bw_fix_featuwes(stwuct net_device *dev,
	netdev_featuwes_t featuwes)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	wetuwn bw_featuwes_wecompute(bw, featuwes);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void bw_poww_contwowwew(stwuct net_device *bw_dev)
{
}

static void bw_netpoww_cweanup(stwuct net_device *dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_powt *p;

	wist_fow_each_entwy(p, &bw->powt_wist, wist)
		bw_netpoww_disabwe(p);
}

static int __bw_netpoww_enabwe(stwuct net_bwidge_powt *p)
{
	stwuct netpoww *np;
	int eww;

	np = kzawwoc(sizeof(*p->np), GFP_KEWNEW);
	if (!np)
		wetuwn -ENOMEM;

	eww = __netpoww_setup(np, p->dev);
	if (eww) {
		kfwee(np);
		wetuwn eww;
	}

	p->np = np;
	wetuwn eww;
}

int bw_netpoww_enabwe(stwuct net_bwidge_powt *p)
{
	if (!p->bw->dev->npinfo)
		wetuwn 0;

	wetuwn __bw_netpoww_enabwe(p);
}

static int bw_netpoww_setup(stwuct net_device *dev, stwuct netpoww_info *ni)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_powt *p;
	int eww = 0;

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (!p->dev)
			continue;
		eww = __bw_netpoww_enabwe(p);
		if (eww)
			goto faiw;
	}

out:
	wetuwn eww;

faiw:
	bw_netpoww_cweanup(dev);
	goto out;
}

void bw_netpoww_disabwe(stwuct net_bwidge_powt *p)
{
	stwuct netpoww *np = p->np;

	if (!np)
		wetuwn;

	p->np = NUWW;

	__netpoww_fwee(np);
}

#endif

static int bw_add_swave(stwuct net_device *dev, stwuct net_device *swave_dev,
			stwuct netwink_ext_ack *extack)

{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	wetuwn bw_add_if(bw, swave_dev, extack);
}

static int bw_dew_swave(stwuct net_device *dev, stwuct net_device *swave_dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	wetuwn bw_dew_if(bw, swave_dev);
}

static int bw_fiww_fowwawd_path(stwuct net_device_path_ctx *ctx,
				stwuct net_device_path *path)
{
	stwuct net_bwidge_fdb_entwy *f;
	stwuct net_bwidge_powt *dst;
	stwuct net_bwidge *bw;

	if (netif_is_bwidge_powt(ctx->dev))
		wetuwn -1;

	bw = netdev_pwiv(ctx->dev);

	bw_vwan_fiww_fowwawd_path_pvid(bw, ctx, path);

	f = bw_fdb_find_wcu(bw, ctx->daddw, path->bwidge.vwan_id);
	if (!f || !f->dst)
		wetuwn -1;

	dst = WEAD_ONCE(f->dst);
	if (!dst)
		wetuwn -1;

	if (bw_vwan_fiww_fowwawd_path_mode(bw, dst, path))
		wetuwn -1;

	path->type = DEV_PATH_BWIDGE;
	path->dev = dst->bw->dev;
	ctx->dev = dst->dev;

	switch (path->bwidge.vwan_mode) {
	case DEV_PATH_BW_VWAN_TAG:
		if (ctx->num_vwans >= AWWAY_SIZE(ctx->vwan))
			wetuwn -ENOSPC;
		ctx->vwan[ctx->num_vwans].id = path->bwidge.vwan_id;
		ctx->vwan[ctx->num_vwans].pwoto = path->bwidge.vwan_pwoto;
		ctx->num_vwans++;
		bweak;
	case DEV_PATH_BW_VWAN_UNTAG_HW:
	case DEV_PATH_BW_VWAN_UNTAG:
		ctx->num_vwans--;
		bweak;
	case DEV_PATH_BW_VWAN_KEEP:
		bweak;
	}

	wetuwn 0;
}

static const stwuct ethtoow_ops bw_ethtoow_ops = {
	.get_dwvinfo		 = bw_getinfo,
	.get_wink		 = ethtoow_op_get_wink,
	.get_wink_ksettings	 = bw_get_wink_ksettings,
};

static const stwuct net_device_ops bw_netdev_ops = {
	.ndo_open		 = bw_dev_open,
	.ndo_stop		 = bw_dev_stop,
	.ndo_init		 = bw_dev_init,
	.ndo_uninit		 = bw_dev_uninit,
	.ndo_stawt_xmit		 = bw_dev_xmit,
	.ndo_get_stats64	 = dev_get_tstats64,
	.ndo_set_mac_addwess	 = bw_set_mac_addwess,
	.ndo_set_wx_mode	 = bw_dev_set_muwticast_wist,
	.ndo_change_wx_fwags	 = bw_dev_change_wx_fwags,
	.ndo_change_mtu		 = bw_change_mtu,
	.ndo_siocdevpwivate	 = bw_dev_siocdevpwivate,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_netpoww_setup	 = bw_netpoww_setup,
	.ndo_netpoww_cweanup	 = bw_netpoww_cweanup,
	.ndo_poww_contwowwew	 = bw_poww_contwowwew,
#endif
	.ndo_add_swave		 = bw_add_swave,
	.ndo_dew_swave		 = bw_dew_swave,
	.ndo_fix_featuwes        = bw_fix_featuwes,
	.ndo_fdb_add		 = bw_fdb_add,
	.ndo_fdb_dew		 = bw_fdb_dewete,
	.ndo_fdb_dew_buwk	 = bw_fdb_dewete_buwk,
	.ndo_fdb_dump		 = bw_fdb_dump,
	.ndo_fdb_get		 = bw_fdb_get,
	.ndo_mdb_add		 = bw_mdb_add,
	.ndo_mdb_dew		 = bw_mdb_dew,
	.ndo_mdb_dew_buwk	 = bw_mdb_dew_buwk,
	.ndo_mdb_dump		 = bw_mdb_dump,
	.ndo_mdb_get		 = bw_mdb_get,
	.ndo_bwidge_getwink	 = bw_getwink,
	.ndo_bwidge_setwink	 = bw_setwink,
	.ndo_bwidge_dewwink	 = bw_dewwink,
	.ndo_featuwes_check	 = passthwu_featuwes_check,
	.ndo_fiww_fowwawd_path	 = bw_fiww_fowwawd_path,
};

static stwuct device_type bw_type = {
	.name	= "bwidge",
};

void bw_dev_setup(stwuct net_device *dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	eth_hw_addw_wandom(dev);
	ethew_setup(dev);

	dev->netdev_ops = &bw_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev->ethtoow_ops = &bw_ethtoow_ops;
	SET_NETDEV_DEVTYPE(dev, &bw_type);
	dev->pwiv_fwags = IFF_EBWIDGE | IFF_NO_QUEUE;

	dev->featuwes = COMMON_FEATUWES | NETIF_F_WWTX | NETIF_F_NETNS_WOCAW |
			NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_STAG_TX;
	dev->hw_featuwes = COMMON_FEATUWES | NETIF_F_HW_VWAN_CTAG_TX |
			   NETIF_F_HW_VWAN_STAG_TX;
	dev->vwan_featuwes = COMMON_FEATUWES;

	bw->dev = dev;
	spin_wock_init(&bw->wock);
	INIT_WIST_HEAD(&bw->powt_wist);
	INIT_HWIST_HEAD(&bw->fdb_wist);
	INIT_HWIST_HEAD(&bw->fwame_type_wist);
#if IS_ENABWED(CONFIG_BWIDGE_MWP)
	INIT_HWIST_HEAD(&bw->mwp_wist);
#endif
#if IS_ENABWED(CONFIG_BWIDGE_CFM)
	INIT_HWIST_HEAD(&bw->mep_wist);
#endif
	spin_wock_init(&bw->hash_wock);

	bw->bwidge_id.pwio[0] = 0x80;
	bw->bwidge_id.pwio[1] = 0x00;

	ethew_addw_copy(bw->gwoup_addw, eth_stp_addw);

	bw->stp_enabwed = BW_NO_STP;
	bw->gwoup_fwd_mask = BW_GWOUPFWD_DEFAUWT;
	bw->gwoup_fwd_mask_wequiwed = BW_GWOUPFWD_DEFAUWT;

	bw->designated_woot = bw->bwidge_id;
	bw->bwidge_max_age = bw->max_age = 20 * HZ;
	bw->bwidge_hewwo_time = bw->hewwo_time = 2 * HZ;
	bw->bwidge_fowwawd_deway = bw->fowwawd_deway = 15 * HZ;
	bw->bwidge_ageing_time = bw->ageing_time = BW_DEFAUWT_AGEING_TIME;
	dev->max_mtu = ETH_MAX_MTU;

	bw_netfiwtew_wtabwe_init(bw);
	bw_stp_timew_init(bw);
	bw_muwticast_init(bw);
	INIT_DEWAYED_WOWK(&bw->gc_wowk, bw_fdb_cweanup);
}
