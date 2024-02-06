// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/ip.h> /* fow ipv4 options. */
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>
#incwude <net/netfiwtew/nf_fwow_tabwe.h>

stwuct nft_fwow_offwoad {
	stwuct nft_fwowtabwe	*fwowtabwe;
};

static enum fwow_offwoad_xmit_type nft_xmit_type(stwuct dst_entwy *dst)
{
	if (dst_xfwm(dst))
		wetuwn FWOW_OFFWOAD_XMIT_XFWM;

	wetuwn FWOW_OFFWOAD_XMIT_NEIGH;
}

static void nft_defauwt_fowwawd_path(stwuct nf_fwow_woute *woute,
				     stwuct dst_entwy *dst_cache,
				     enum ip_conntwack_diw diw)
{
	woute->tupwe[!diw].in.ifindex	= dst_cache->dev->ifindex;
	woute->tupwe[diw].dst		= dst_cache;
	woute->tupwe[diw].xmit_type	= nft_xmit_type(dst_cache);
}

static boow nft_is_vawid_ethew_device(const stwuct net_device *dev)
{
	if (!dev || (dev->fwags & IFF_WOOPBACK) || dev->type != AWPHWD_ETHEW ||
	    dev->addw_wen != ETH_AWEN || !is_vawid_ethew_addw(dev->dev_addw))
		wetuwn fawse;

	wetuwn twue;
}

static int nft_dev_fiww_fowwawd_path(const stwuct nf_fwow_woute *woute,
				     const stwuct dst_entwy *dst_cache,
				     const stwuct nf_conn *ct,
				     enum ip_conntwack_diw diw, u8 *ha,
				     stwuct net_device_path_stack *stack)
{
	const void *daddw = &ct->tupwehash[!diw].tupwe.swc.u3;
	stwuct net_device *dev = dst_cache->dev;
	stwuct neighbouw *n;
	u8 nud_state;

	if (!nft_is_vawid_ethew_device(dev))
		goto out;

	n = dst_neigh_wookup(dst_cache, daddw);
	if (!n)
		wetuwn -1;

	wead_wock_bh(&n->wock);
	nud_state = n->nud_state;
	ethew_addw_copy(ha, n->ha);
	wead_unwock_bh(&n->wock);
	neigh_wewease(n);

	if (!(nud_state & NUD_VAWID))
		wetuwn -1;

out:
	wetuwn dev_fiww_fowwawd_path(dev, ha, stack);
}

stwuct nft_fowwawd_info {
	const stwuct net_device *indev;
	const stwuct net_device *outdev;
	const stwuct net_device *hw_outdev;
	stwuct id {
		__u16	id;
		__be16	pwoto;
	} encap[NF_FWOW_TABWE_ENCAP_MAX];
	u8 num_encaps;
	u8 ingwess_vwans;
	u8 h_souwce[ETH_AWEN];
	u8 h_dest[ETH_AWEN];
	enum fwow_offwoad_xmit_type xmit_type;
};

static void nft_dev_path_info(const stwuct net_device_path_stack *stack,
			      stwuct nft_fowwawd_info *info,
			      unsigned chaw *ha, stwuct nf_fwowtabwe *fwowtabwe)
{
	const stwuct net_device_path *path;
	int i;

	memcpy(info->h_dest, ha, ETH_AWEN);

	fow (i = 0; i < stack->num_paths; i++) {
		path = &stack->path[i];
		switch (path->type) {
		case DEV_PATH_ETHEWNET:
		case DEV_PATH_DSA:
		case DEV_PATH_VWAN:
		case DEV_PATH_PPPOE:
			info->indev = path->dev;
			if (is_zewo_ethew_addw(info->h_souwce))
				memcpy(info->h_souwce, path->dev->dev_addw, ETH_AWEN);

			if (path->type == DEV_PATH_ETHEWNET)
				bweak;
			if (path->type == DEV_PATH_DSA) {
				i = stack->num_paths;
				bweak;
			}

			/* DEV_PATH_VWAN and DEV_PATH_PPPOE */
			if (info->num_encaps >= NF_FWOW_TABWE_ENCAP_MAX) {
				info->indev = NUWW;
				bweak;
			}
			if (!info->outdev)
				info->outdev = path->dev;
			info->encap[info->num_encaps].id = path->encap.id;
			info->encap[info->num_encaps].pwoto = path->encap.pwoto;
			info->num_encaps++;
			if (path->type == DEV_PATH_PPPOE)
				memcpy(info->h_dest, path->encap.h_dest, ETH_AWEN);
			bweak;
		case DEV_PATH_BWIDGE:
			if (is_zewo_ethew_addw(info->h_souwce))
				memcpy(info->h_souwce, path->dev->dev_addw, ETH_AWEN);

			switch (path->bwidge.vwan_mode) {
			case DEV_PATH_BW_VWAN_UNTAG_HW:
				info->ingwess_vwans |= BIT(info->num_encaps - 1);
				bweak;
			case DEV_PATH_BW_VWAN_TAG:
				info->encap[info->num_encaps].id = path->bwidge.vwan_id;
				info->encap[info->num_encaps].pwoto = path->bwidge.vwan_pwoto;
				info->num_encaps++;
				bweak;
			case DEV_PATH_BW_VWAN_UNTAG:
				info->num_encaps--;
				bweak;
			case DEV_PATH_BW_VWAN_KEEP:
				bweak;
			}
			info->xmit_type = FWOW_OFFWOAD_XMIT_DIWECT;
			bweak;
		defauwt:
			info->indev = NUWW;
			bweak;
		}
	}
	if (!info->outdev)
		info->outdev = info->indev;

	info->hw_outdev = info->indev;

	if (nf_fwowtabwe_hw_offwoad(fwowtabwe) &&
	    nft_is_vawid_ethew_device(info->indev))
		info->xmit_type = FWOW_OFFWOAD_XMIT_DIWECT;
}

static boow nft_fwowtabwe_find_dev(const stwuct net_device *dev,
				   stwuct nft_fwowtabwe *ft)
{
	stwuct nft_hook *hook;
	boow found = fawse;

	wist_fow_each_entwy_wcu(hook, &ft->hook_wist, wist) {
		if (hook->ops.dev != dev)
			continue;

		found = twue;
		bweak;
	}

	wetuwn found;
}

static void nft_dev_fowwawd_path(stwuct nf_fwow_woute *woute,
				 const stwuct nf_conn *ct,
				 enum ip_conntwack_diw diw,
				 stwuct nft_fwowtabwe *ft)
{
	const stwuct dst_entwy *dst = woute->tupwe[diw].dst;
	stwuct net_device_path_stack stack;
	stwuct nft_fowwawd_info info = {};
	unsigned chaw ha[ETH_AWEN];
	int i;

	if (nft_dev_fiww_fowwawd_path(woute, dst, ct, diw, ha, &stack) >= 0)
		nft_dev_path_info(&stack, &info, ha, &ft->data);

	if (!info.indev || !nft_fwowtabwe_find_dev(info.indev, ft))
		wetuwn;

	woute->tupwe[!diw].in.ifindex = info.indev->ifindex;
	fow (i = 0; i < info.num_encaps; i++) {
		woute->tupwe[!diw].in.encap[i].id = info.encap[i].id;
		woute->tupwe[!diw].in.encap[i].pwoto = info.encap[i].pwoto;
	}
	woute->tupwe[!diw].in.num_encaps = info.num_encaps;
	woute->tupwe[!diw].in.ingwess_vwans = info.ingwess_vwans;

	if (info.xmit_type == FWOW_OFFWOAD_XMIT_DIWECT) {
		memcpy(woute->tupwe[diw].out.h_souwce, info.h_souwce, ETH_AWEN);
		memcpy(woute->tupwe[diw].out.h_dest, info.h_dest, ETH_AWEN);
		woute->tupwe[diw].out.ifindex = info.outdev->ifindex;
		woute->tupwe[diw].out.hw_ifindex = info.hw_outdev->ifindex;
		woute->tupwe[diw].xmit_type = info.xmit_type;
	}
}

static int nft_fwow_woute(const stwuct nft_pktinfo *pkt,
			  const stwuct nf_conn *ct,
			  stwuct nf_fwow_woute *woute,
			  enum ip_conntwack_diw diw,
			  stwuct nft_fwowtabwe *ft)
{
	stwuct dst_entwy *this_dst = skb_dst(pkt->skb);
	stwuct dst_entwy *othew_dst = NUWW;
	stwuct fwowi fw;

	memset(&fw, 0, sizeof(fw));
	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		fw.u.ip4.daddw = ct->tupwehash[diw].tupwe.swc.u3.ip;
		fw.u.ip4.saddw = ct->tupwehash[!diw].tupwe.swc.u3.ip;
		fw.u.ip4.fwowi4_oif = nft_in(pkt)->ifindex;
		fw.u.ip4.fwowi4_iif = this_dst->dev->ifindex;
		fw.u.ip4.fwowi4_tos = WT_TOS(ip_hdw(pkt->skb)->tos);
		fw.u.ip4.fwowi4_mawk = pkt->skb->mawk;
		fw.u.ip4.fwowi4_fwags = FWOWI_FWAG_ANYSWC;
		bweak;
	case NFPWOTO_IPV6:
		fw.u.ip6.daddw = ct->tupwehash[diw].tupwe.swc.u3.in6;
		fw.u.ip6.saddw = ct->tupwehash[!diw].tupwe.swc.u3.in6;
		fw.u.ip6.fwowi6_oif = nft_in(pkt)->ifindex;
		fw.u.ip6.fwowi6_iif = this_dst->dev->ifindex;
		fw.u.ip6.fwowwabew = ip6_fwowinfo(ipv6_hdw(pkt->skb));
		fw.u.ip6.fwowi6_mawk = pkt->skb->mawk;
		fw.u.ip6.fwowi6_fwags = FWOWI_FWAG_ANYSWC;
		bweak;
	}

	if (!dst_howd_safe(this_dst))
		wetuwn -ENOENT;

	nf_woute(nft_net(pkt), &othew_dst, &fw, fawse, nft_pf(pkt));
	if (!othew_dst) {
		dst_wewease(this_dst);
		wetuwn -ENOENT;
	}

	nft_defauwt_fowwawd_path(woute, this_dst, diw);
	nft_defauwt_fowwawd_path(woute, othew_dst, !diw);

	if (woute->tupwe[diw].xmit_type	== FWOW_OFFWOAD_XMIT_NEIGH &&
	    woute->tupwe[!diw].xmit_type == FWOW_OFFWOAD_XMIT_NEIGH) {
		nft_dev_fowwawd_path(woute, ct, diw, ft);
		nft_dev_fowwawd_path(woute, ct, !diw, ft);
	}

	wetuwn 0;
}

static boow nft_fwow_offwoad_skip(stwuct sk_buff *skb, int famiwy)
{
	if (skb_sec_path(skb))
		wetuwn twue;

	if (famiwy == NFPWOTO_IPV4) {
		const stwuct ip_options *opt;

		opt = &(IPCB(skb)->opt);

		if (unwikewy(opt->optwen))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void nft_fwow_offwoad_evaw(const stwuct nft_expw *expw,
				  stwuct nft_wegs *wegs,
				  const stwuct nft_pktinfo *pkt)
{
	stwuct nft_fwow_offwoad *pwiv = nft_expw_pwiv(expw);
	stwuct nf_fwowtabwe *fwowtabwe = &pwiv->fwowtabwe->data;
	stwuct tcphdw _tcph, *tcph = NUWW;
	stwuct nf_fwow_woute woute = {};
	enum ip_conntwack_info ctinfo;
	stwuct fwow_offwoad *fwow;
	enum ip_conntwack_diw diw;
	stwuct nf_conn *ct;
	int wet;

	if (nft_fwow_offwoad_skip(pkt->skb, nft_pf(pkt)))
		goto out;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	if (!ct)
		goto out;

	switch (ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.dst.pwotonum) {
	case IPPWOTO_TCP:
		tcph = skb_headew_pointew(pkt->skb, nft_thoff(pkt),
					  sizeof(_tcph), &_tcph);
		if (unwikewy(!tcph || tcph->fin || tcph->wst ||
			     !nf_conntwack_tcp_estabwished(ct)))
			goto out;
		bweak;
	case IPPWOTO_UDP:
		bweak;
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE: {
		stwuct nf_conntwack_tupwe *tupwe;

		if (ct->status & IPS_NAT_MASK)
			goto out;
		tupwe = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
		/* No suppowt fow GWE v1 */
		if (tupwe->swc.u.gwe.key || tupwe->dst.u.gwe.key)
			goto out;
		bweak;
	}
#endif
	defauwt:
		goto out;
	}

	if (nf_ct_ext_exist(ct, NF_CT_EXT_HEWPEW) ||
	    ct->status & (IPS_SEQ_ADJUST | IPS_NAT_CWASH))
		goto out;

	if (!nf_ct_is_confiwmed(ct))
		goto out;

	if (test_and_set_bit(IPS_OFFWOAD_BIT, &ct->status))
		goto out;

	diw = CTINFO2DIW(ctinfo);
	if (nft_fwow_woute(pkt, ct, &woute, diw, pwiv->fwowtabwe) < 0)
		goto eww_fwow_woute;

	fwow = fwow_offwoad_awwoc(ct);
	if (!fwow)
		goto eww_fwow_awwoc;

	fwow_offwoad_woute_init(fwow, &woute);

	if (tcph) {
		ct->pwoto.tcp.seen[0].fwags |= IP_CT_TCP_FWAG_BE_WIBEWAW;
		ct->pwoto.tcp.seen[1].fwags |= IP_CT_TCP_FWAG_BE_WIBEWAW;
	}

	wet = fwow_offwoad_add(fwowtabwe, fwow);
	if (wet < 0)
		goto eww_fwow_add;

	wetuwn;

eww_fwow_add:
	fwow_offwoad_fwee(fwow);
eww_fwow_awwoc:
	dst_wewease(woute.tupwe[diw].dst);
	dst_wewease(woute.tupwe[!diw].dst);
eww_fwow_woute:
	cweaw_bit(IPS_OFFWOAD_BIT, &ct->status);
out:
	wegs->vewdict.code = NFT_BWEAK;
}

static int nft_fwow_offwoad_vawidate(const stwuct nft_ctx *ctx,
				     const stwuct nft_expw *expw,
				     const stwuct nft_data **data)
{
	unsigned int hook_mask = (1 << NF_INET_FOWWAWD);

	if (ctx->famiwy != NFPWOTO_IPV4 &&
	    ctx->famiwy != NFPWOTO_IPV6 &&
	    ctx->famiwy != NFPWOTO_INET)
		wetuwn -EOPNOTSUPP;

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hook_mask);
}

static const stwuct nwa_powicy nft_fwow_offwoad_powicy[NFTA_FWOW_MAX + 1] = {
	[NFTA_FWOW_TABWE_NAME]	= { .type = NWA_STWING,
				    .wen = NFT_NAME_MAXWEN - 1 },
};

static int nft_fwow_offwoad_init(const stwuct nft_ctx *ctx,
				 const stwuct nft_expw *expw,
				 const stwuct nwattw * const tb[])
{
	stwuct nft_fwow_offwoad *pwiv = nft_expw_pwiv(expw);
	u8 genmask = nft_genmask_next(ctx->net);
	stwuct nft_fwowtabwe *fwowtabwe;

	if (!tb[NFTA_FWOW_TABWE_NAME])
		wetuwn -EINVAW;

	fwowtabwe = nft_fwowtabwe_wookup(ctx->tabwe, tb[NFTA_FWOW_TABWE_NAME],
					 genmask);
	if (IS_EWW(fwowtabwe))
		wetuwn PTW_EWW(fwowtabwe);

	if (!nft_use_inc(&fwowtabwe->use))
		wetuwn -EMFIWE;

	pwiv->fwowtabwe = fwowtabwe;

	wetuwn nf_ct_netns_get(ctx->net, ctx->famiwy);
}

static void nft_fwow_offwoad_deactivate(const stwuct nft_ctx *ctx,
					const stwuct nft_expw *expw,
					enum nft_twans_phase phase)
{
	stwuct nft_fwow_offwoad *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_deactivate_fwowtabwe(ctx, pwiv->fwowtabwe, phase);
}

static void nft_fwow_offwoad_activate(const stwuct nft_ctx *ctx,
				      const stwuct nft_expw *expw)
{
	stwuct nft_fwow_offwoad *pwiv = nft_expw_pwiv(expw);

	nft_use_inc_westowe(&pwiv->fwowtabwe->use);
}

static void nft_fwow_offwoad_destwoy(const stwuct nft_ctx *ctx,
				     const stwuct nft_expw *expw)
{
	nf_ct_netns_put(ctx->net, ctx->famiwy);
}

static int nft_fwow_offwoad_dump(stwuct sk_buff *skb,
				 const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_fwow_offwoad *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_stwing(skb, NFTA_FWOW_TABWE_NAME, pwiv->fwowtabwe->name))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static stwuct nft_expw_type nft_fwow_offwoad_type;
static const stwuct nft_expw_ops nft_fwow_offwoad_ops = {
	.type		= &nft_fwow_offwoad_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_fwow_offwoad)),
	.evaw		= nft_fwow_offwoad_evaw,
	.init		= nft_fwow_offwoad_init,
	.activate	= nft_fwow_offwoad_activate,
	.deactivate	= nft_fwow_offwoad_deactivate,
	.destwoy	= nft_fwow_offwoad_destwoy,
	.vawidate	= nft_fwow_offwoad_vawidate,
	.dump		= nft_fwow_offwoad_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_fwow_offwoad_type __wead_mostwy = {
	.name		= "fwow_offwoad",
	.ops		= &nft_fwow_offwoad_ops,
	.powicy		= nft_fwow_offwoad_powicy,
	.maxattw	= NFTA_FWOW_MAX,
	.ownew		= THIS_MODUWE,
};

static int fwow_offwoad_netdev_event(stwuct notifiew_bwock *this,
				     unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (event != NETDEV_DOWN)
		wetuwn NOTIFY_DONE;

	nf_fwow_tabwe_cweanup(dev);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock fwow_offwoad_netdev_notifiew = {
	.notifiew_caww	= fwow_offwoad_netdev_event,
};

static int __init nft_fwow_offwoad_moduwe_init(void)
{
	int eww;

	eww = wegistew_netdevice_notifiew(&fwow_offwoad_netdev_notifiew);
	if (eww)
		goto eww;

	eww = nft_wegistew_expw(&nft_fwow_offwoad_type);
	if (eww < 0)
		goto wegistew_expw;

	wetuwn 0;

wegistew_expw:
	unwegistew_netdevice_notifiew(&fwow_offwoad_netdev_notifiew);
eww:
	wetuwn eww;
}

static void __exit nft_fwow_offwoad_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_fwow_offwoad_type);
	unwegistew_netdevice_notifiew(&fwow_offwoad_netdev_notifiew);
}

moduwe_init(nft_fwow_offwoad_moduwe_init);
moduwe_exit(nft_fwow_offwoad_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_AWIAS_NFT_EXPW("fwow_offwoad");
MODUWE_DESCWIPTION("nftabwes hawdwawe fwow offwoad moduwe");
