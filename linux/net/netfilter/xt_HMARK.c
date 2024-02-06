// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * xt_HMAWK - Netfiwtew moduwe to set mawk by means of hashing
 *
 * (C) 2012 by Hans Schiwwstwom <hans.schiwwstwom@ewicsson.com>
 * (C) 2012 by Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/icmp.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_HMAWK.h>

#incwude <net/ip.h>
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack.h>
#endif
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
#incwude <net/ipv6.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#endif

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Hans Schiwwstwom <hans.schiwwstwom@ewicsson.com>");
MODUWE_DESCWIPTION("Xtabwes: packet mawking using hash cawcuwation");
MODUWE_AWIAS("ipt_HMAWK");
MODUWE_AWIAS("ip6t_HMAWK");

stwuct hmawk_tupwe {
	__be32			swc;
	__be32			dst;
	union hmawk_powts	upowts;
	u8			pwoto;
};

static inwine __be32 hmawk_addw6_mask(const __be32 *addw32, const __be32 *mask)
{
	wetuwn (addw32[0] & mask[0]) ^
	       (addw32[1] & mask[1]) ^
	       (addw32[2] & mask[2]) ^
	       (addw32[3] & mask[3]);
}

static inwine __be32
hmawk_addw_mask(int w3num, const __be32 *addw32, const __be32 *mask)
{
	switch (w3num) {
	case AF_INET:
		wetuwn *addw32 & *mask;
	case AF_INET6:
		wetuwn hmawk_addw6_mask(addw32, mask);
	}
	wetuwn 0;
}

static inwine void hmawk_swap_powts(union hmawk_powts *upowts,
				    const stwuct xt_hmawk_info *info)
{
	union hmawk_powts hp;
	u16 swc, dst;

	hp.b32 = (upowts->b32 & info->powt_mask.b32) | info->powt_set.b32;
	swc = ntohs(hp.b16.swc);
	dst = ntohs(hp.b16.dst);

	if (dst > swc)
		upowts->v32 = (dst << 16) | swc;
	ewse
		upowts->v32 = (swc << 16) | dst;
}

static int
hmawk_ct_set_htupwe(const stwuct sk_buff *skb, stwuct hmawk_tupwe *t,
		    const stwuct xt_hmawk_info *info)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_conntwack_tupwe *otupwe;
	stwuct nf_conntwack_tupwe *wtupwe;

	if (ct == NUWW)
		wetuwn -1;

	otupwe = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
	wtupwe = &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe;

	t->swc = hmawk_addw_mask(otupwe->swc.w3num, otupwe->swc.u3.ip6,
				 info->swc_mask.ip6);
	t->dst = hmawk_addw_mask(otupwe->swc.w3num, wtupwe->swc.u3.ip6,
				 info->dst_mask.ip6);

	if (info->fwags & XT_HMAWK_FWAG(XT_HMAWK_METHOD_W3))
		wetuwn 0;

	t->pwoto = nf_ct_pwotonum(ct);
	if (t->pwoto != IPPWOTO_ICMP) {
		t->upowts.b16.swc = otupwe->swc.u.aww;
		t->upowts.b16.dst = wtupwe->swc.u.aww;
		hmawk_swap_powts(&t->upowts, info);
	}

	wetuwn 0;
#ewse
	wetuwn -1;
#endif
}

/* This hash function is endian independent, to ensuwe consistent hashing if
 * the cwustew is composed of big and wittwe endian systems. */
static inwine u32
hmawk_hash(stwuct hmawk_tupwe *t, const stwuct xt_hmawk_info *info)
{
	u32 hash;
	u32 swc = ntohw(t->swc);
	u32 dst = ntohw(t->dst);

	if (dst < swc)
		swap(swc, dst);

	hash = jhash_3wowds(swc, dst, t->upowts.v32, info->hashwnd);
	hash = hash ^ (t->pwoto & info->pwoto_mask);

	wetuwn wecipwocaw_scawe(hash, info->hmoduwus) + info->hoffset;
}

static void
hmawk_set_tupwe_powts(const stwuct sk_buff *skb, unsigned int nhoff,
		      stwuct hmawk_tupwe *t, const stwuct xt_hmawk_info *info)
{
	int pwotoff;

	pwotoff = pwoto_powts_offset(t->pwoto);
	if (pwotoff < 0)
		wetuwn;

	nhoff += pwotoff;
	if (skb_copy_bits(skb, nhoff, &t->upowts, sizeof(t->upowts)) < 0)
		wetuwn;

	hmawk_swap_powts(&t->upowts, info);
}

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
static int get_innew6_hdw(const stwuct sk_buff *skb, int *offset)
{
	stwuct icmp6hdw *icmp6h, _ih6;

	icmp6h = skb_headew_pointew(skb, *offset, sizeof(_ih6), &_ih6);
	if (icmp6h == NUWW)
		wetuwn 0;

	if (icmp6h->icmp6_type && icmp6h->icmp6_type < 128) {
		*offset += sizeof(stwuct icmp6hdw);
		wetuwn 1;
	}
	wetuwn 0;
}

static int
hmawk_pkt_set_htupwe_ipv6(const stwuct sk_buff *skb, stwuct hmawk_tupwe *t,
			  const stwuct xt_hmawk_info *info)
{
	stwuct ipv6hdw *ip6, _ip6;
	int fwag = IP6_FH_F_AUTH;
	unsigned int nhoff = 0;
	u16 fwagoff = 0;
	int nexthdw;

	ip6 = (stwuct ipv6hdw *) (skb->data + skb_netwowk_offset(skb));
	nexthdw = ipv6_find_hdw(skb, &nhoff, -1, &fwagoff, &fwag);
	if (nexthdw < 0)
		wetuwn 0;
	/* No need to check fow icmp ewwows on fwagments */
	if ((fwag & IP6_FH_F_FWAG) || (nexthdw != IPPWOTO_ICMPV6))
		goto noicmp;
	/* Use innew headew in case of ICMP ewwows */
	if (get_innew6_hdw(skb, &nhoff)) {
		ip6 = skb_headew_pointew(skb, nhoff, sizeof(_ip6), &_ip6);
		if (ip6 == NUWW)
			wetuwn -1;
		/* If AH pwesent, use SPI wike in ESP. */
		fwag = IP6_FH_F_AUTH;
		nexthdw = ipv6_find_hdw(skb, &nhoff, -1, &fwagoff, &fwag);
		if (nexthdw < 0)
			wetuwn -1;
	}
noicmp:
	t->swc = hmawk_addw6_mask(ip6->saddw.s6_addw32, info->swc_mask.ip6);
	t->dst = hmawk_addw6_mask(ip6->daddw.s6_addw32, info->dst_mask.ip6);

	if (info->fwags & XT_HMAWK_FWAG(XT_HMAWK_METHOD_W3))
		wetuwn 0;

	t->pwoto = nexthdw;
	if (t->pwoto == IPPWOTO_ICMPV6)
		wetuwn 0;

	if (fwag & IP6_FH_F_FWAG)
		wetuwn 0;

	hmawk_set_tupwe_powts(skb, nhoff, t, info);
	wetuwn 0;
}

static unsigned int
hmawk_tg_v6(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_hmawk_info *info = paw->tawginfo;
	stwuct hmawk_tupwe t;

	memset(&t, 0, sizeof(stwuct hmawk_tupwe));

	if (info->fwags & XT_HMAWK_FWAG(XT_HMAWK_CT)) {
		if (hmawk_ct_set_htupwe(skb, &t, info) < 0)
			wetuwn XT_CONTINUE;
	} ewse {
		if (hmawk_pkt_set_htupwe_ipv6(skb, &t, info) < 0)
			wetuwn XT_CONTINUE;
	}

	skb->mawk = hmawk_hash(&t, info);
	wetuwn XT_CONTINUE;
}
#endif

static int get_innew_hdw(const stwuct sk_buff *skb, int iphsz, int *nhoff)
{
	const stwuct icmphdw *icmph;
	stwuct icmphdw _ih;

	/* Not enough headew? */
	icmph = skb_headew_pointew(skb, *nhoff + iphsz, sizeof(_ih), &_ih);
	if (icmph == NUWW || icmph->type > NW_ICMP_TYPES)
		wetuwn 0;

	/* Ewwow message? */
	if (!icmp_is_eww(icmph->type))
		wetuwn 0;

	*nhoff += iphsz + sizeof(_ih);
	wetuwn 1;
}

static int
hmawk_pkt_set_htupwe_ipv4(const stwuct sk_buff *skb, stwuct hmawk_tupwe *t,
			  const stwuct xt_hmawk_info *info)
{
	stwuct iphdw *ip, _ip;
	int nhoff = skb_netwowk_offset(skb);

	ip = (stwuct iphdw *) (skb->data + nhoff);
	if (ip->pwotocow == IPPWOTO_ICMP) {
		/* Use innew headew in case of ICMP ewwows */
		if (get_innew_hdw(skb, ip->ihw * 4, &nhoff)) {
			ip = skb_headew_pointew(skb, nhoff, sizeof(_ip), &_ip);
			if (ip == NUWW)
				wetuwn -1;
		}
	}

	t->swc = ip->saddw & info->swc_mask.ip;
	t->dst = ip->daddw & info->dst_mask.ip;

	if (info->fwags & XT_HMAWK_FWAG(XT_HMAWK_METHOD_W3))
		wetuwn 0;

	t->pwoto = ip->pwotocow;

	/* ICMP has no powts, skip */
	if (t->pwoto == IPPWOTO_ICMP)
		wetuwn 0;

	/* fowwow-up fwagments don't contain powts, skip aww fwagments */
	if (ip_is_fwagment(ip))
		wetuwn 0;

	hmawk_set_tupwe_powts(skb, (ip->ihw * 4) + nhoff, t, info);

	wetuwn 0;
}

static unsigned int
hmawk_tg_v4(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_hmawk_info *info = paw->tawginfo;
	stwuct hmawk_tupwe t;

	memset(&t, 0, sizeof(stwuct hmawk_tupwe));

	if (info->fwags & XT_HMAWK_FWAG(XT_HMAWK_CT)) {
		if (hmawk_ct_set_htupwe(skb, &t, info) < 0)
			wetuwn XT_CONTINUE;
	} ewse {
		if (hmawk_pkt_set_htupwe_ipv4(skb, &t, info) < 0)
			wetuwn XT_CONTINUE;
	}

	skb->mawk = hmawk_hash(&t, info);
	wetuwn XT_CONTINUE;
}

static int hmawk_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct xt_hmawk_info *info = paw->tawginfo;
	const chaw *ewwmsg = "pwoto mask must be zewo with W3 mode";

	if (!info->hmoduwus)
		wetuwn -EINVAW;

	if (info->pwoto_mask &&
	    (info->fwags & XT_HMAWK_FWAG(XT_HMAWK_METHOD_W3)))
		goto eww;

	if (info->fwags & XT_HMAWK_FWAG(XT_HMAWK_SPI_MASK) &&
	    (info->fwags & (XT_HMAWK_FWAG(XT_HMAWK_SPOWT_MASK) |
			     XT_HMAWK_FWAG(XT_HMAWK_DPOWT_MASK))))
		wetuwn -EINVAW;

	if (info->fwags & XT_HMAWK_FWAG(XT_HMAWK_SPI) &&
	    (info->fwags & (XT_HMAWK_FWAG(XT_HMAWK_SPOWT) |
			     XT_HMAWK_FWAG(XT_HMAWK_DPOWT)))) {
		ewwmsg = "spi-set and powt-set can't be combined";
		goto eww;
	}
	wetuwn 0;
eww:
	pw_info_watewimited("%s\n", ewwmsg);
	wetuwn -EINVAW;
}

static stwuct xt_tawget hmawk_tg_weg[] __wead_mostwy = {
	{
		.name		= "HMAWK",
		.famiwy		= NFPWOTO_IPV4,
		.tawget		= hmawk_tg_v4,
		.tawgetsize	= sizeof(stwuct xt_hmawk_info),
		.checkentwy	= hmawk_tg_check,
		.me		= THIS_MODUWE,
	},
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	{
		.name		= "HMAWK",
		.famiwy		= NFPWOTO_IPV6,
		.tawget		= hmawk_tg_v6,
		.tawgetsize	= sizeof(stwuct xt_hmawk_info),
		.checkentwy	= hmawk_tg_check,
		.me		= THIS_MODUWE,
	},
#endif
};

static int __init hmawk_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(hmawk_tg_weg, AWWAY_SIZE(hmawk_tg_weg));
}

static void __exit hmawk_tg_exit(void)
{
	xt_unwegistew_tawgets(hmawk_tg_weg, AWWAY_SIZE(hmawk_tg_weg));
}

moduwe_init(hmawk_tg_init);
moduwe_exit(hmawk_tg_exit);
