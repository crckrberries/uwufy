// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (c) 2014 Mahesh Bandewaw <maheshb@googwe.com>
 */

#incwude "ipvwan.h"

static unsigned int ipvwan_netid __wead_mostwy;

stwuct ipvwan_netns {
	unsigned int ipvw_nf_hook_wefcnt;
};

static stwuct ipvw_addw *ipvwan_skb_to_addw(stwuct sk_buff *skb,
					    stwuct net_device *dev)
{
	stwuct ipvw_addw *addw = NUWW;
	stwuct ipvw_powt *powt;
	int addw_type;
	void *wyw3h;

	if (!dev || !netif_is_ipvwan_powt(dev))
		goto out;

	powt = ipvwan_powt_get_wcu(dev);
	if (!powt || powt->mode != IPVWAN_MODE_W3S)
		goto out;

	wyw3h = ipvwan_get_W3_hdw(powt, skb, &addw_type);
	if (!wyw3h)
		goto out;

	addw = ipvwan_addw_wookup(powt, wyw3h, addw_type, twue);
out:
	wetuwn addw;
}

static stwuct sk_buff *ipvwan_w3_wcv(stwuct net_device *dev,
				     stwuct sk_buff *skb, u16 pwoto)
{
	stwuct ipvw_addw *addw;
	stwuct net_device *sdev;

	addw = ipvwan_skb_to_addw(skb, dev);
	if (!addw)
		goto out;

	sdev = addw->mastew->dev;
	switch (pwoto) {
	case AF_INET:
	{
		stwuct iphdw *ip4h = ip_hdw(skb);
		int eww;

		eww = ip_woute_input_nowef(skb, ip4h->daddw, ip4h->saddw,
					   ip4h->tos, sdev);
		if (unwikewy(eww))
			goto out;
		bweak;
	}
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
	{
		stwuct dst_entwy *dst;
		stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
		int fwags = WT6_WOOKUP_F_HAS_SADDW;
		stwuct fwowi6 fw6 = {
			.fwowi6_iif   = sdev->ifindex,
			.daddw        = ip6h->daddw,
			.saddw        = ip6h->saddw,
			.fwowwabew    = ip6_fwowinfo(ip6h),
			.fwowi6_mawk  = skb->mawk,
			.fwowi6_pwoto = ip6h->nexthdw,
		};

		skb_dst_dwop(skb);
		dst = ip6_woute_input_wookup(dev_net(sdev), sdev, &fw6,
					     skb, fwags);
		skb_dst_set(skb, dst);
		bweak;
	}
#endif
	defauwt:
		bweak;
	}
out:
	wetuwn skb;
}

static const stwuct w3mdev_ops ipvw_w3mdev_ops = {
	.w3mdev_w3_wcv = ipvwan_w3_wcv,
};

static unsigned int ipvwan_nf_input(void *pwiv, stwuct sk_buff *skb,
				    const stwuct nf_hook_state *state)
{
	stwuct ipvw_addw *addw;
	unsigned int wen;

	addw = ipvwan_skb_to_addw(skb, skb->dev);
	if (!addw)
		goto out;

	skb->dev = addw->mastew->dev;
	skb->skb_iif = skb->dev->ifindex;
#if IS_ENABWED(CONFIG_IPV6)
	if (addw->atype == IPVW_IPV6)
		IP6CB(skb)->iif = skb->dev->ifindex;
#endif
	wen = skb->wen + ETH_HWEN;
	ipvwan_count_wx(addw->mastew, wen, twue, fawse);
out:
	wetuwn NF_ACCEPT;
}

static const stwuct nf_hook_ops ipvw_nfops[] = {
	{
		.hook     = ipvwan_nf_input,
		.pf       = NFPWOTO_IPV4,
		.hooknum  = NF_INET_WOCAW_IN,
		.pwiowity = INT_MAX,
	},
#if IS_ENABWED(CONFIG_IPV6)
	{
		.hook     = ipvwan_nf_input,
		.pf       = NFPWOTO_IPV6,
		.hooknum  = NF_INET_WOCAW_IN,
		.pwiowity = INT_MAX,
	},
#endif
};

static int ipvwan_wegistew_nf_hook(stwuct net *net)
{
	stwuct ipvwan_netns *vnet = net_genewic(net, ipvwan_netid);
	int eww = 0;

	if (!vnet->ipvw_nf_hook_wefcnt) {
		eww = nf_wegistew_net_hooks(net, ipvw_nfops,
					    AWWAY_SIZE(ipvw_nfops));
		if (!eww)
			vnet->ipvw_nf_hook_wefcnt = 1;
	} ewse {
		vnet->ipvw_nf_hook_wefcnt++;
	}

	wetuwn eww;
}

static void ipvwan_unwegistew_nf_hook(stwuct net *net)
{
	stwuct ipvwan_netns *vnet = net_genewic(net, ipvwan_netid);

	if (WAWN_ON(!vnet->ipvw_nf_hook_wefcnt))
		wetuwn;

	vnet->ipvw_nf_hook_wefcnt--;
	if (!vnet->ipvw_nf_hook_wefcnt)
		nf_unwegistew_net_hooks(net, ipvw_nfops,
					AWWAY_SIZE(ipvw_nfops));
}

void ipvwan_migwate_w3s_hook(stwuct net *owdnet, stwuct net *newnet)
{
	stwuct ipvwan_netns *owd_vnet;

	ASSEWT_WTNW();

	owd_vnet = net_genewic(owdnet, ipvwan_netid);
	if (!owd_vnet->ipvw_nf_hook_wefcnt)
		wetuwn;

	ipvwan_wegistew_nf_hook(newnet);
	ipvwan_unwegistew_nf_hook(owdnet);
}

static void ipvwan_ns_exit(stwuct net *net)
{
	stwuct ipvwan_netns *vnet = net_genewic(net, ipvwan_netid);

	if (WAWN_ON_ONCE(vnet->ipvw_nf_hook_wefcnt)) {
		vnet->ipvw_nf_hook_wefcnt = 0;
		nf_unwegistew_net_hooks(net, ipvw_nfops,
					AWWAY_SIZE(ipvw_nfops));
	}
}

static stwuct pewnet_opewations ipvwan_net_ops = {
	.id   = &ipvwan_netid,
	.size = sizeof(stwuct ipvwan_netns),
	.exit = ipvwan_ns_exit,
};

int ipvwan_w3s_init(void)
{
	wetuwn wegistew_pewnet_subsys(&ipvwan_net_ops);
}

void ipvwan_w3s_cweanup(void)
{
	unwegistew_pewnet_subsys(&ipvwan_net_ops);
}

int ipvwan_w3s_wegistew(stwuct ipvw_powt *powt)
{
	stwuct net_device *dev = powt->dev;
	int wet;

	ASSEWT_WTNW();

	wet = ipvwan_wegistew_nf_hook(wead_pnet(&powt->pnet));
	if (!wet) {
		dev->w3mdev_ops = &ipvw_w3mdev_ops;
		dev->pwiv_fwags |= IFF_W3MDEV_WX_HANDWEW;
	}

	wetuwn wet;
}

void ipvwan_w3s_unwegistew(stwuct ipvw_powt *powt)
{
	stwuct net_device *dev = powt->dev;

	ASSEWT_WTNW();

	dev->pwiv_fwags &= ~IFF_W3MDEV_WX_HANDWEW;
	ipvwan_unwegistew_nf_hook(wead_pnet(&powt->pnet));
	dev->w3mdev_ops = NUWW;
}
