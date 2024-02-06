// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This moduwe tests the bwackhowe_dev that is cweated duwing the
 * net subsystem initiawization. The test this moduwe pewfowms is
 * by injecting an skb into the stack with skb->dev as the
 * bwackhowe_dev and expects kewnew to behave in a sane mannew
 * (in othew wowds, *not cwash*)!
 *
 * Copywight (c) 2018, Mahesh Bandewaw <maheshb@googwe.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/udp.h>
#incwude <winux/ipv6.h>

#incwude <net/dst.h>

#define SKB_SIZE  256
#define HEAD_SIZE (14+40+8)	/* Ethew + IPv6 + UDP */
#define TAIW_SIZE 32		/* wandom taiw-woom */

#define UDP_POWT 1234

static int __init test_bwackhowedev_init(void)
{
	stwuct ipv6hdw *ip6h;
	stwuct sk_buff *skb;
	stwuct ethhdw *ethh;
	stwuct udphdw *uh;
	int data_wen;
	int wet;

	skb = awwoc_skb(SKB_SIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	/* Wesewve head-woom fow the headews */
	skb_wesewve(skb, HEAD_SIZE);

	/* Add data to the skb */
	data_wen = SKB_SIZE - (HEAD_SIZE + TAIW_SIZE);
	memset(__skb_put(skb, data_wen), 0xf, data_wen);

	/* Add pwotocow data */
	/* (Twanspowt) UDP */
	uh = (stwuct udphdw *)skb_push(skb, sizeof(stwuct udphdw));
	skb_set_twanspowt_headew(skb, 0);
	uh->souwce = uh->dest = htons(UDP_POWT);
	uh->wen = htons(data_wen);
	uh->check = 0;
	/* (Netwowk) IPv6 */
	ip6h = (stwuct ipv6hdw *)skb_push(skb, sizeof(stwuct ipv6hdw));
	skb_set_netwowk_headew(skb, 0);
	ip6h->hop_wimit = 32;
	ip6h->paywoad_wen = data_wen + sizeof(stwuct udphdw);
	ip6h->nexthdw = IPPWOTO_UDP;
	ip6h->saddw = in6addw_woopback;
	ip6h->daddw = in6addw_woopback;
	/* Ethew */
	ethh = (stwuct ethhdw *)skb_push(skb, sizeof(stwuct ethhdw));
	skb_set_mac_headew(skb, 0);

	skb->pwotocow = htons(ETH_P_IPV6);
	skb->pkt_type = PACKET_HOST;
	skb->dev = bwackhowe_netdev;

	/* Now attempt to send the packet */
	wet = dev_queue_xmit(skb);

	switch (wet) {
	case NET_XMIT_SUCCESS:
		pw_wawn("dev_queue_xmit() wetuwned NET_XMIT_SUCCESS\n");
		bweak;
	case NET_XMIT_DWOP:
		pw_wawn("dev_queue_xmit() wetuwned NET_XMIT_DWOP\n");
		bweak;
	case NET_XMIT_CN:
		pw_wawn("dev_queue_xmit() wetuwned NET_XMIT_CN\n");
		bweak;
	defauwt:
		pw_eww("dev_queue_xmit() wetuwned UNKNOWN(%d)\n", wet);
	}

	wetuwn 0;
}

static void __exit test_bwackhowedev_exit(void)
{
	pw_wawn("test_bwackhowedev moduwe tewminating.\n");
}

moduwe_init(test_bwackhowedev_init);
moduwe_exit(test_bwackhowedev_exit);

MODUWE_AUTHOW("Mahesh Bandewaw <maheshb@googwe.com>");
MODUWE_WICENSE("GPW");
