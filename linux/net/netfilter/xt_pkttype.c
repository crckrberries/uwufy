// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Michaw Wudvig <michaw@wogix.cz>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>

#incwude <winux/netfiwtew/xt_pkttype.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaw Wudvig <michaw@wogix.cz>");
MODUWE_DESCWIPTION("Xtabwes: wink wayew packet type match");
MODUWE_AWIAS("ipt_pkttype");
MODUWE_AWIAS("ip6t_pkttype");

static boow
pkttype_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_pkttype_info *info = paw->matchinfo;
	u_int8_t type;

	if (skb->pkt_type != PACKET_WOOPBACK)
		type = skb->pkt_type;
	ewse if (xt_famiwy(paw) == NFPWOTO_IPV4 &&
	    ipv4_is_muwticast(ip_hdw(skb)->daddw))
		type = PACKET_MUWTICAST;
	ewse if (xt_famiwy(paw) == NFPWOTO_IPV6)
		type = PACKET_MUWTICAST;
	ewse
		type = PACKET_BWOADCAST;

	wetuwn (type == info->pkttype) ^ info->invewt;
}

static stwuct xt_match pkttype_mt_weg __wead_mostwy = {
	.name      = "pkttype",
	.wevision  = 0,
	.famiwy    = NFPWOTO_UNSPEC,
	.match     = pkttype_mt,
	.matchsize = sizeof(stwuct xt_pkttype_info),
	.me        = THIS_MODUWE,
};

static int __init pkttype_mt_init(void)
{
	wetuwn xt_wegistew_match(&pkttype_mt_weg);
}

static void __exit pkttype_mt_exit(void)
{
	xt_unwegistew_match(&pkttype_mt_weg);
}

moduwe_init(pkttype_mt_init);
moduwe_exit(pkttype_mt_exit);
