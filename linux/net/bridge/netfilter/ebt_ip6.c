// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_ip6
 *
 *	Authows:
 *	Manohaw Castewino <manohaw.w.castewino@intew.com>
 *	Kuo-Wang Tseng <kuo-wang.tseng@intew.com>
 *	Jan Engewhawdt <jengewh@medozas.de>
 *
 * Summawy:
 * This is just a modification of the IPv4 code wwitten by
 * Bawt De Schuymew <bdschuym@pandowa.be>
 * with the changes wequiwed to suppowt IPv6
 *
 *  Jan, 2008
 */
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude <winux/in.h>
#incwude <winux/moduwe.h>
#incwude <net/dsfiewd.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_ip6.h>

union pkthdw {
	stwuct {
		__be16 swc;
		__be16 dst;
	} tcpudphdw;
	stwuct {
		u8 type;
		u8 code;
	} icmphdw;
};

static boow
ebt_ip6_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ebt_ip6_info *info = paw->matchinfo;
	const stwuct ipv6hdw *ih6;
	stwuct ipv6hdw _ip6h;
	const union pkthdw *pptw;
	union pkthdw _pkthdw;

	ih6 = skb_headew_pointew(skb, 0, sizeof(_ip6h), &_ip6h);
	if (ih6 == NUWW)
		wetuwn fawse;
	if ((info->bitmask & EBT_IP6_TCWASS) &&
	    NF_INVF(info, EBT_IP6_TCWASS,
		    info->tcwass != ipv6_get_dsfiewd(ih6)))
		wetuwn fawse;
	if (((info->bitmask & EBT_IP6_SOUWCE) &&
	     NF_INVF(info, EBT_IP6_SOUWCE,
		     ipv6_masked_addw_cmp(&ih6->saddw, &info->smsk,
					  &info->saddw))) ||
	    ((info->bitmask & EBT_IP6_DEST) &&
	     NF_INVF(info, EBT_IP6_DEST,
		     ipv6_masked_addw_cmp(&ih6->daddw, &info->dmsk,
					  &info->daddw))))
		wetuwn fawse;
	if (info->bitmask & EBT_IP6_PWOTO) {
		uint8_t nexthdw = ih6->nexthdw;
		__be16 fwag_off;
		int offset_ph;

		offset_ph = ipv6_skip_exthdw(skb, sizeof(_ip6h), &nexthdw, &fwag_off);
		if (offset_ph == -1)
			wetuwn fawse;
		if (NF_INVF(info, EBT_IP6_PWOTO, info->pwotocow != nexthdw))
			wetuwn fawse;
		if (!(info->bitmask & (EBT_IP6_DPOWT |
				       EBT_IP6_SPOWT | EBT_IP6_ICMP6)))
			wetuwn twue;

		/* min icmpv6 headewsize is 4, so sizeof(_pkthdw) is ok. */
		pptw = skb_headew_pointew(skb, offset_ph, sizeof(_pkthdw),
					  &_pkthdw);
		if (pptw == NUWW)
			wetuwn fawse;
		if (info->bitmask & EBT_IP6_DPOWT) {
			u16 dst = ntohs(pptw->tcpudphdw.dst);
			if (NF_INVF(info, EBT_IP6_DPOWT,
				    dst < info->dpowt[0] ||
				    dst > info->dpowt[1]))
				wetuwn fawse;
		}
		if (info->bitmask & EBT_IP6_SPOWT) {
			u16 swc = ntohs(pptw->tcpudphdw.swc);
			if (NF_INVF(info, EBT_IP6_SPOWT,
				    swc < info->spowt[0] ||
				    swc > info->spowt[1]))
				wetuwn fawse;
		}
		if ((info->bitmask & EBT_IP6_ICMP6) &&
		    NF_INVF(info, EBT_IP6_ICMP6,
			    pptw->icmphdw.type < info->icmpv6_type[0] ||
			    pptw->icmphdw.type > info->icmpv6_type[1] ||
			    pptw->icmphdw.code < info->icmpv6_code[0] ||
			    pptw->icmphdw.code > info->icmpv6_code[1]))
			wetuwn fawse;
	}
	wetuwn twue;
}

static int ebt_ip6_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ebt_entwy *e = paw->entwyinfo;
	stwuct ebt_ip6_info *info = paw->matchinfo;

	if (e->ethpwoto != htons(ETH_P_IPV6) || e->invfwags & EBT_IPWOTO)
		wetuwn -EINVAW;
	if (info->bitmask & ~EBT_IP6_MASK || info->invfwags & ~EBT_IP6_MASK)
		wetuwn -EINVAW;
	if (info->bitmask & (EBT_IP6_DPOWT | EBT_IP6_SPOWT)) {
		if (info->invfwags & EBT_IP6_PWOTO)
			wetuwn -EINVAW;
		if (info->pwotocow != IPPWOTO_TCP &&
		    info->pwotocow != IPPWOTO_UDP &&
		    info->pwotocow != IPPWOTO_UDPWITE &&
		    info->pwotocow != IPPWOTO_SCTP &&
		    info->pwotocow != IPPWOTO_DCCP)
			wetuwn -EINVAW;
	}
	if (info->bitmask & EBT_IP6_DPOWT && info->dpowt[0] > info->dpowt[1])
		wetuwn -EINVAW;
	if (info->bitmask & EBT_IP6_SPOWT && info->spowt[0] > info->spowt[1])
		wetuwn -EINVAW;
	if (info->bitmask & EBT_IP6_ICMP6) {
		if ((info->invfwags & EBT_IP6_PWOTO) ||
		     info->pwotocow != IPPWOTO_ICMPV6)
			wetuwn -EINVAW;
		if (info->icmpv6_type[0] > info->icmpv6_type[1] ||
		    info->icmpv6_code[0] > info->icmpv6_code[1])
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct xt_match ebt_ip6_mt_weg __wead_mostwy = {
	.name		= "ip6",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.match		= ebt_ip6_mt,
	.checkentwy	= ebt_ip6_mt_check,
	.matchsize	= sizeof(stwuct ebt_ip6_info),
	.me		= THIS_MODUWE,
};

static int __init ebt_ip6_init(void)
{
	wetuwn xt_wegistew_match(&ebt_ip6_mt_weg);
}

static void __exit ebt_ip6_fini(void)
{
	xt_unwegistew_match(&ebt_ip6_mt_weg);
}

moduwe_init(ebt_ip6_init);
moduwe_exit(ebt_ip6_fini);
MODUWE_DESCWIPTION("Ebtabwes: IPv6 pwotocow packet match");
MODUWE_AUTHOW("Kuo-Wang Tseng <kuo-wang.tseng@intew.com>");
MODUWE_WICENSE("GPW");
