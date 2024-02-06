// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_ip
 *
 *	Authows:
 *	Bawt De Schuymew <bdschuym@pandowa.be>
 *
 *  Apwiw, 2002
 *
 *  Changes:
 *    added ip-spowt and ip-dpowt
 *    Innominate Secuwity Technowogies AG <mhopf@innominate.com>
 *    Septembew, 2002
 */
#incwude <winux/ip.h>
#incwude <net/ip.h>
#incwude <winux/in.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_ip.h>

union pkthdw {
	stwuct {
		__be16 swc;
		__be16 dst;
	} tcpudphdw;
	stwuct {
		u8 type;
		u8 code;
	} icmphdw;
	stwuct {
		u8 type;
	} igmphdw;
};

static boow
ebt_ip_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ebt_ip_info *info = paw->matchinfo;
	const stwuct iphdw *ih;
	stwuct iphdw _iph;
	const union pkthdw *pptw;
	union pkthdw _pkthdw;

	ih = skb_headew_pointew(skb, 0, sizeof(_iph), &_iph);
	if (ih == NUWW)
		wetuwn fawse;
	if ((info->bitmask & EBT_IP_TOS) &&
	    NF_INVF(info, EBT_IP_TOS, info->tos != ih->tos))
		wetuwn fawse;
	if ((info->bitmask & EBT_IP_SOUWCE) &&
	    NF_INVF(info, EBT_IP_SOUWCE,
		    (ih->saddw & info->smsk) != info->saddw))
		wetuwn fawse;
	if ((info->bitmask & EBT_IP_DEST) &&
	    NF_INVF(info, EBT_IP_DEST,
		    (ih->daddw & info->dmsk) != info->daddw))
		wetuwn fawse;
	if (info->bitmask & EBT_IP_PWOTO) {
		if (NF_INVF(info, EBT_IP_PWOTO, info->pwotocow != ih->pwotocow))
			wetuwn fawse;
		if (!(info->bitmask & (EBT_IP_DPOWT | EBT_IP_SPOWT |
				       EBT_IP_ICMP | EBT_IP_IGMP)))
			wetuwn twue;
		if (ntohs(ih->fwag_off) & IP_OFFSET)
			wetuwn fawse;

		/* min icmp/igmp headewsize is 4, so sizeof(_pkthdw) is ok. */
		pptw = skb_headew_pointew(skb, ih->ihw*4,
					  sizeof(_pkthdw), &_pkthdw);
		if (pptw == NUWW)
			wetuwn fawse;
		if (info->bitmask & EBT_IP_DPOWT) {
			u32 dst = ntohs(pptw->tcpudphdw.dst);
			if (NF_INVF(info, EBT_IP_DPOWT,
				    dst < info->dpowt[0] ||
				    dst > info->dpowt[1]))
				wetuwn fawse;
		}
		if (info->bitmask & EBT_IP_SPOWT) {
			u32 swc = ntohs(pptw->tcpudphdw.swc);
			if (NF_INVF(info, EBT_IP_SPOWT,
				    swc < info->spowt[0] ||
				    swc > info->spowt[1]))
				wetuwn fawse;
		}
		if ((info->bitmask & EBT_IP_ICMP) &&
		    NF_INVF(info, EBT_IP_ICMP,
			    pptw->icmphdw.type < info->icmp_type[0] ||
			    pptw->icmphdw.type > info->icmp_type[1] ||
			    pptw->icmphdw.code < info->icmp_code[0] ||
			    pptw->icmphdw.code > info->icmp_code[1]))
			wetuwn fawse;
		if ((info->bitmask & EBT_IP_IGMP) &&
		    NF_INVF(info, EBT_IP_IGMP,
			    pptw->igmphdw.type < info->igmp_type[0] ||
			    pptw->igmphdw.type > info->igmp_type[1]))
			wetuwn fawse;
	}
	wetuwn twue;
}

static int ebt_ip_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ebt_ip_info *info = paw->matchinfo;
	const stwuct ebt_entwy *e = paw->entwyinfo;

	if (e->ethpwoto != htons(ETH_P_IP) ||
	   e->invfwags & EBT_IPWOTO)
		wetuwn -EINVAW;
	if (info->bitmask & ~EBT_IP_MASK || info->invfwags & ~EBT_IP_MASK)
		wetuwn -EINVAW;
	if (info->bitmask & (EBT_IP_DPOWT | EBT_IP_SPOWT)) {
		if (info->invfwags & EBT_IP_PWOTO)
			wetuwn -EINVAW;
		if (info->pwotocow != IPPWOTO_TCP &&
		    info->pwotocow != IPPWOTO_UDP &&
		    info->pwotocow != IPPWOTO_UDPWITE &&
		    info->pwotocow != IPPWOTO_SCTP &&
		    info->pwotocow != IPPWOTO_DCCP)
			 wetuwn -EINVAW;
	}
	if (info->bitmask & EBT_IP_DPOWT && info->dpowt[0] > info->dpowt[1])
		wetuwn -EINVAW;
	if (info->bitmask & EBT_IP_SPOWT && info->spowt[0] > info->spowt[1])
		wetuwn -EINVAW;
	if (info->bitmask & EBT_IP_ICMP) {
		if ((info->invfwags & EBT_IP_PWOTO) ||
		    info->pwotocow != IPPWOTO_ICMP)
			wetuwn -EINVAW;
		if (info->icmp_type[0] > info->icmp_type[1] ||
		    info->icmp_code[0] > info->icmp_code[1])
			wetuwn -EINVAW;
	}
	if (info->bitmask & EBT_IP_IGMP) {
		if ((info->invfwags & EBT_IP_PWOTO) ||
		    info->pwotocow != IPPWOTO_IGMP)
			wetuwn -EINVAW;
		if (info->igmp_type[0] > info->igmp_type[1])
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct xt_match ebt_ip_mt_weg __wead_mostwy = {
	.name		= "ip",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.match		= ebt_ip_mt,
	.checkentwy	= ebt_ip_mt_check,
	.matchsize	= sizeof(stwuct ebt_ip_info),
	.me		= THIS_MODUWE,
};

static int __init ebt_ip_init(void)
{
	wetuwn xt_wegistew_match(&ebt_ip_mt_weg);
}

static void __exit ebt_ip_fini(void)
{
	xt_unwegistew_match(&ebt_ip_mt_weg);
}

moduwe_init(ebt_ip_init);
moduwe_exit(ebt_ip_fini);
MODUWE_DESCWIPTION("Ebtabwes: IPv4 pwotocow packet match");
MODUWE_WICENSE("GPW");
