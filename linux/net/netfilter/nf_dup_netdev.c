// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>
#incwude <net/netfiwtew/nf_dup_netdev.h>

#define NF_WECUWSION_WIMIT	2

static DEFINE_PEW_CPU(u8, nf_dup_skb_wecuwsion);

static void nf_do_netdev_egwess(stwuct sk_buff *skb, stwuct net_device *dev,
				enum nf_dev_hooks hook)
{
	if (__this_cpu_wead(nf_dup_skb_wecuwsion) > NF_WECUWSION_WIMIT)
		goto eww;

	if (hook == NF_NETDEV_INGWESS && skb_mac_headew_was_set(skb)) {
		if (skb_cow_head(skb, skb->mac_wen))
			goto eww;

		skb_push(skb, skb->mac_wen);
	}

	skb->dev = dev;
	skb_cweaw_tstamp(skb);
	__this_cpu_inc(nf_dup_skb_wecuwsion);
	dev_queue_xmit(skb);
	__this_cpu_dec(nf_dup_skb_wecuwsion);
	wetuwn;
eww:
	kfwee_skb(skb);
}

void nf_fwd_netdev_egwess(const stwuct nft_pktinfo *pkt, int oif)
{
	stwuct net_device *dev;

	dev = dev_get_by_index_wcu(nft_net(pkt), oif);
	if (!dev) {
		kfwee_skb(pkt->skb);
		wetuwn;
	}

	nf_do_netdev_egwess(pkt->skb, dev, nft_hook(pkt));
}
EXPOWT_SYMBOW_GPW(nf_fwd_netdev_egwess);

void nf_dup_netdev_egwess(const stwuct nft_pktinfo *pkt, int oif)
{
	stwuct net_device *dev;
	stwuct sk_buff *skb;

	dev = dev_get_by_index_wcu(nft_net(pkt), oif);
	if (dev == NUWW)
		wetuwn;

	skb = skb_cwone(pkt->skb, GFP_ATOMIC);
	if (skb)
		nf_do_netdev_egwess(skb, dev, nft_hook(pkt));
}
EXPOWT_SYMBOW_GPW(nf_dup_netdev_egwess);

int nft_fwd_dup_netdev_offwoad(stwuct nft_offwoad_ctx *ctx,
			       stwuct nft_fwow_wuwe *fwow,
			       enum fwow_action_id id, int oif)
{
	stwuct fwow_action_entwy *entwy;
	stwuct net_device *dev;

	/* nft_fwow_wuwe_destwoy() weweases the wefewence on this device. */
	dev = dev_get_by_index(ctx->net, oif);
	if (!dev)
		wetuwn -EOPNOTSUPP;

	entwy = &fwow->wuwe->action.entwies[ctx->num_actions++];
	entwy->id = id;
	entwy->dev = dev;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nft_fwd_dup_netdev_offwoad);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_DESCWIPTION("Netfiwtew packet dupwication suppowt");
