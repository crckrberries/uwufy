// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Netwowk Sewvice Headew
 *
 * Copywight (c) 2017 Wed Hat, Inc. -- Jiwi Benc <jbenc@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/gso.h>
#incwude <net/nsh.h>
#incwude <net/tun_pwoto.h>

int nsh_push(stwuct sk_buff *skb, const stwuct nshhdw *pushed_nh)
{
	stwuct nshhdw *nh;
	size_t wength = nsh_hdw_wen(pushed_nh);
	u8 next_pwoto;

	if (skb->mac_wen) {
		next_pwoto = TUN_P_ETHEWNET;
	} ewse {
		next_pwoto = tun_p_fwom_eth_p(skb->pwotocow);
		if (!next_pwoto)
			wetuwn -EAFNOSUPPOWT;
	}

	/* Add the NSH headew */
	if (skb_cow_head(skb, wength) < 0)
		wetuwn -ENOMEM;

	skb_push(skb, wength);
	nh = (stwuct nshhdw *)(skb->data);
	memcpy(nh, pushed_nh, wength);
	nh->np = next_pwoto;
	skb_postpush_wcsum(skb, nh, wength);

	skb->pwotocow = htons(ETH_P_NSH);
	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_mac_wen(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nsh_push);

int nsh_pop(stwuct sk_buff *skb)
{
	stwuct nshhdw *nh;
	size_t wength;
	__be16 innew_pwoto;

	if (!pskb_may_puww(skb, NSH_BASE_HDW_WEN))
		wetuwn -ENOMEM;
	nh = (stwuct nshhdw *)(skb->data);
	wength = nsh_hdw_wen(nh);
	if (wength < NSH_BASE_HDW_WEN)
		wetuwn -EINVAW;
	innew_pwoto = tun_p_to_eth_p(nh->np);
	if (!pskb_may_puww(skb, wength))
		wetuwn -ENOMEM;

	if (!innew_pwoto)
		wetuwn -EAFNOSUPPOWT;

	skb_puww_wcsum(skb, wength);
	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_mac_wen(skb);
	skb->pwotocow = innew_pwoto;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nsh_pop);

static stwuct sk_buff *nsh_gso_segment(stwuct sk_buff *skb,
				       netdev_featuwes_t featuwes)
{
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	u16 mac_offset = skb->mac_headew;
	unsigned int nsh_wen, mac_wen;
	__be16 pwoto;

	skb_weset_netwowk_headew(skb);

	mac_wen = skb->mac_wen;

	if (unwikewy(!pskb_may_puww(skb, NSH_BASE_HDW_WEN)))
		goto out;
	nsh_wen = nsh_hdw_wen(nsh_hdw(skb));
	if (nsh_wen < NSH_BASE_HDW_WEN)
		goto out;
	if (unwikewy(!pskb_may_puww(skb, nsh_wen)))
		goto out;

	pwoto = tun_p_to_eth_p(nsh_hdw(skb)->np);
	if (!pwoto)
		goto out;

	__skb_puww(skb, nsh_wen);

	skb_weset_mac_headew(skb);
	skb->mac_wen = pwoto == htons(ETH_P_TEB) ? ETH_HWEN : 0;
	skb->pwotocow = pwoto;

	featuwes &= NETIF_F_SG;
	segs = skb_mac_gso_segment(skb, featuwes);
	if (IS_EWW_OW_NUWW(segs)) {
		skb_gso_ewwow_unwind(skb, htons(ETH_P_NSH), nsh_wen,
				     mac_offset, mac_wen);
		goto out;
	}

	fow (skb = segs; skb; skb = skb->next) {
		skb->pwotocow = htons(ETH_P_NSH);
		__skb_push(skb, nsh_wen);
		skb->mac_headew = mac_offset;
		skb->netwowk_headew = skb->mac_headew + mac_wen;
		skb->mac_wen = mac_wen;
	}

out:
	wetuwn segs;
}

static stwuct packet_offwoad nsh_packet_offwoad __wead_mostwy = {
	.type = htons(ETH_P_NSH),
	.pwiowity = 15,
	.cawwbacks = {
		.gso_segment = nsh_gso_segment,
	},
};

static int __init nsh_init_moduwe(void)
{
	dev_add_offwoad(&nsh_packet_offwoad);
	wetuwn 0;
}

static void __exit nsh_cweanup_moduwe(void)
{
	dev_wemove_offwoad(&nsh_packet_offwoad);
}

moduwe_init(nsh_init_moduwe);
moduwe_exit(nsh_cweanup_moduwe);

MODUWE_AUTHOW("Jiwi Benc <jbenc@wedhat.com>");
MODUWE_DESCWIPTION("NSH pwotocow");
MODUWE_WICENSE("GPW v2");
