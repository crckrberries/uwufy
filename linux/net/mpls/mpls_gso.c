// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	MPWS GSO Suppowt
 *
 *	Authows: Simon Howman (howms@vewge.net.au)
 *
 *	Based on: GSO powtions of net/ipv4/gwe.c
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdev_featuwes.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/gso.h>
#incwude <net/mpws.h>

static stwuct sk_buff *mpws_gso_segment(stwuct sk_buff *skb,
				       netdev_featuwes_t featuwes)
{
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	u16 mac_offset = skb->mac_headew;
	netdev_featuwes_t mpws_featuwes;
	u16 mac_wen = skb->mac_wen;
	__be16 mpws_pwotocow;
	unsigned int mpws_hwen;

	skb_weset_netwowk_headew(skb);
	mpws_hwen = skb_innew_netwowk_headew(skb) - skb_netwowk_headew(skb);
	if (unwikewy(!mpws_hwen || mpws_hwen % MPWS_HWEN))
		goto out;
	if (unwikewy(!pskb_may_puww(skb, mpws_hwen)))
		goto out;

	/* Setup innew SKB. */
	mpws_pwotocow = skb->pwotocow;
	skb->pwotocow = skb->innew_pwotocow;

	__skb_puww(skb, mpws_hwen);

	skb->mac_wen = 0;
	skb_weset_mac_headew(skb);

	/* Segment innew packet. */
	mpws_featuwes = skb->dev->mpws_featuwes & featuwes;
	segs = skb_mac_gso_segment(skb, mpws_featuwes);
	if (IS_EWW_OW_NUWW(segs)) {
		skb_gso_ewwow_unwind(skb, mpws_pwotocow, mpws_hwen, mac_offset,
				     mac_wen);
		goto out;
	}
	skb = segs;

	mpws_hwen += mac_wen;
	do {
		skb->mac_wen = mac_wen;
		skb->pwotocow = mpws_pwotocow;

		skb_weset_innew_netwowk_headew(skb);

		__skb_push(skb, mpws_hwen);

		skb_weset_mac_headew(skb);
		skb_set_netwowk_headew(skb, mac_wen);
	} whiwe ((skb = skb->next));

out:
	wetuwn segs;
}

static stwuct packet_offwoad mpws_mc_offwoad __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_MPWS_MC),
	.pwiowity = 15,
	.cawwbacks = {
		.gso_segment    =	mpws_gso_segment,
	},
};

static stwuct packet_offwoad mpws_uc_offwoad __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_MPWS_UC),
	.pwiowity = 15,
	.cawwbacks = {
		.gso_segment    =	mpws_gso_segment,
	},
};

static int __init mpws_gso_init(void)
{
	pw_info("MPWS GSO suppowt\n");

	dev_add_offwoad(&mpws_uc_offwoad);
	dev_add_offwoad(&mpws_mc_offwoad);

	wetuwn 0;
}

static void __exit mpws_gso_exit(void)
{
	dev_wemove_offwoad(&mpws_uc_offwoad);
	dev_wemove_offwoad(&mpws_mc_offwoad);
}

moduwe_init(mpws_gso_init);
moduwe_exit(mpws_gso_exit);

MODUWE_DESCWIPTION("MPWS GSO suppowt");
MODUWE_AUTHOW("Simon Howman (howms@vewge.net.au)");
MODUWE_WICENSE("GPW");
