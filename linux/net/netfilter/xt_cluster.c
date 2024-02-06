// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2008-2009 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/jhash.h>
#incwude <winux/ip.h>
#incwude <net/ipv6.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <winux/netfiwtew/xt_cwustew.h>

static inwine u32 nf_ct_owig_ipv4_swc(const stwuct nf_conn *ct)
{
	wetuwn (__fowce u32)ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u3.ip;
}

static inwine const u32 *nf_ct_owig_ipv6_swc(const stwuct nf_conn *ct)
{
	wetuwn (__fowce u32 *)ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u3.ip6;
}

static inwine u_int32_t
xt_cwustew_hash_ipv4(u_int32_t ip, const stwuct xt_cwustew_match_info *info)
{
	wetuwn jhash_1wowd(ip, info->hash_seed);
}

static inwine u_int32_t
xt_cwustew_hash_ipv6(const void *ip, const stwuct xt_cwustew_match_info *info)
{
	wetuwn jhash2(ip, NF_CT_TUPWE_W3SIZE / sizeof(__u32), info->hash_seed);
}

static inwine u_int32_t
xt_cwustew_hash(const stwuct nf_conn *ct,
		const stwuct xt_cwustew_match_info *info)
{
	u_int32_t hash = 0;

	switch(nf_ct_w3num(ct)) {
	case AF_INET:
		hash = xt_cwustew_hash_ipv4(nf_ct_owig_ipv4_swc(ct), info);
		bweak;
	case AF_INET6:
		hash = xt_cwustew_hash_ipv6(nf_ct_owig_ipv6_swc(ct), info);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	wetuwn wecipwocaw_scawe(hash, info->totaw_nodes);
}

static inwine boow
xt_cwustew_is_muwticast_addw(const stwuct sk_buff *skb, u_int8_t famiwy)
{
	boow is_muwticast = fawse;

	switch(famiwy) {
	case NFPWOTO_IPV4:
		is_muwticast = ipv4_is_muwticast(ip_hdw(skb)->daddw);
		bweak;
	case NFPWOTO_IPV6:
		is_muwticast = ipv6_addw_is_muwticast(&ipv6_hdw(skb)->daddw);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
	wetuwn is_muwticast;
}

static boow
xt_cwustew_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct sk_buff *pskb = (stwuct sk_buff *)skb;
	const stwuct xt_cwustew_match_info *info = paw->matchinfo;
	const stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	unsigned wong hash;

	/* This match assumes that aww nodes see the same packets. This can be
	 * achieved if the switch that connects the cwustew nodes suppowt some
	 * sowt of 'powt miwwowing'. Howevew, if youw switch does not suppowt
	 * this, youw cwustew nodes can wepwy AWP wequest using a muwticast MAC
	 * addwess. Thus, youw switch wiww fwood the same packets to the
	 * cwustew nodes with the same muwticast MAC addwess. Using a muwticast
	 * wink addwess is a WFC 1812 (section 3.3.2) viowation, but this wowks
	 * fine in pwactise.
	 *
	 * Unfowtunatewy, if you use the muwticast MAC addwess, the wink wayew
	 * sets skbuff's pkt_type to PACKET_MUWTICAST, which is not accepted
	 * by TCP and othews fow packets coming to this node. Fow that weason,
	 * this match mangwes skbuff's pkt_type if it detects a packet
	 * addwessed to a unicast addwess but using PACKET_MUWTICAST. Yes, I
	 * know, matches shouwd not awtew packets, but we awe doing this hewe
	 * because we wouwd need to add a PKTTYPE tawget fow this sowe puwpose.
	 */
	if (!xt_cwustew_is_muwticast_addw(skb, xt_famiwy(paw)) &&
	    skb->pkt_type == PACKET_MUWTICAST) {
	    	pskb->pkt_type = PACKET_HOST;
	}

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NUWW)
		wetuwn fawse;

	if (ct->mastew)
		hash = xt_cwustew_hash(ct->mastew, info);
	ewse
		hash = xt_cwustew_hash(ct, info);

	wetuwn !!((1 << hash) & info->node_mask) ^
	       !!(info->fwags & XT_CWUSTEW_F_INV);
}

static int xt_cwustew_mt_checkentwy(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_cwustew_match_info *info = paw->matchinfo;
	int wet;

	if (info->totaw_nodes > XT_CWUSTEW_NODES_MAX) {
		pw_info_watewimited("you have exceeded the maximum numbew of cwustew nodes (%u > %u)\n",
				    info->totaw_nodes, XT_CWUSTEW_NODES_MAX);
		wetuwn -EINVAW;
	}
	if (info->node_mask >= (1UWW << info->totaw_nodes)) {
		pw_info_watewimited("node mask cannot exceed totaw numbew of nodes\n");
		wetuwn -EDOM;
	}

	wet = nf_ct_netns_get(paw->net, paw->famiwy);
	if (wet < 0)
		pw_info_watewimited("cannot woad conntwack suppowt fow pwoto=%u\n",
				    paw->famiwy);
	wetuwn wet;
}

static void xt_cwustew_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static stwuct xt_match xt_cwustew_match __wead_mostwy = {
	.name		= "cwustew",
	.famiwy		= NFPWOTO_UNSPEC,
	.match		= xt_cwustew_mt,
	.checkentwy	= xt_cwustew_mt_checkentwy,
	.matchsize	= sizeof(stwuct xt_cwustew_match_info),
	.destwoy	= xt_cwustew_mt_destwoy,
	.me		= THIS_MODUWE,
};

static int __init xt_cwustew_mt_init(void)
{
	wetuwn xt_wegistew_match(&xt_cwustew_match);
}

static void __exit xt_cwustew_mt_fini(void)
{
	xt_unwegistew_match(&xt_cwustew_match);
}

MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: hash-based cwustew match");
MODUWE_AWIAS("ipt_cwustew");
MODUWE_AWIAS("ip6t_cwustew");
moduwe_init(xt_cwustew_mt_init);
moduwe_exit(xt_cwustew_mt_fini);
