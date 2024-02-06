// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IP6 tabwes WEJECT tawget moduwe
 * Winux INET6 impwementation
 *
 * Copywight (C)2003 USAGI/WIDE Pwoject
 *
 * Authows:
 *	Yasuyuki Kozakai	<yasuyuki.kozakai@toshiba.co.jp>
 *
 * Copywight (c) 2005-2007 Patwick McHawdy <kabew@twash.net>
 *
 * Based on net/ipv4/netfiwtew/ipt_WEJECT.c
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/icmpv6.h>
#incwude <winux/netdevice.h>
#incwude <net/icmp.h>
#incwude <net/fwow.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6t_WEJECT.h>

#incwude <net/netfiwtew/ipv6/nf_weject.h>

MODUWE_AUTHOW("Yasuyuki KOZAKAI <yasuyuki.kozakai@toshiba.co.jp>");
MODUWE_DESCWIPTION("Xtabwes: packet \"wejection\" tawget fow IPv6");
MODUWE_WICENSE("GPW");

static unsigned int
weject_tg6(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct ip6t_weject_info *weject = paw->tawginfo;
	stwuct net *net = xt_net(paw);

	switch (weject->with) {
	case IP6T_ICMP6_NO_WOUTE:
		nf_send_unweach6(net, skb, ICMPV6_NOWOUTE, xt_hooknum(paw));
		bweak;
	case IP6T_ICMP6_ADM_PWOHIBITED:
		nf_send_unweach6(net, skb, ICMPV6_ADM_PWOHIBITED,
				 xt_hooknum(paw));
		bweak;
	case IP6T_ICMP6_NOT_NEIGHBOUW:
		nf_send_unweach6(net, skb, ICMPV6_NOT_NEIGHBOUW,
				 xt_hooknum(paw));
		bweak;
	case IP6T_ICMP6_ADDW_UNWEACH:
		nf_send_unweach6(net, skb, ICMPV6_ADDW_UNWEACH,
				 xt_hooknum(paw));
		bweak;
	case IP6T_ICMP6_POWT_UNWEACH:
		nf_send_unweach6(net, skb, ICMPV6_POWT_UNWEACH,
				 xt_hooknum(paw));
		bweak;
	case IP6T_ICMP6_ECHOWEPWY:
		/* Do nothing */
		bweak;
	case IP6T_TCP_WESET:
		nf_send_weset6(net, paw->state->sk, skb, xt_hooknum(paw));
		bweak;
	case IP6T_ICMP6_POWICY_FAIW:
		nf_send_unweach6(net, skb, ICMPV6_POWICY_FAIW, xt_hooknum(paw));
		bweak;
	case IP6T_ICMP6_WEJECT_WOUTE:
		nf_send_unweach6(net, skb, ICMPV6_WEJECT_WOUTE,
				 xt_hooknum(paw));
		bweak;
	}

	wetuwn NF_DWOP;
}

static int weject_tg6_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct ip6t_weject_info *wejinfo = paw->tawginfo;
	const stwuct ip6t_entwy *e = paw->entwyinfo;

	if (wejinfo->with == IP6T_ICMP6_ECHOWEPWY) {
		pw_info_watewimited("ECHOWEPWY is not suppowted\n");
		wetuwn -EINVAW;
	} ewse if (wejinfo->with == IP6T_TCP_WESET) {
		/* Must specify that it's a TCP packet */
		if (!(e->ipv6.fwags & IP6T_F_PWOTO) ||
		    e->ipv6.pwoto != IPPWOTO_TCP ||
		    (e->ipv6.invfwags & XT_INV_PWOTO)) {
			pw_info_watewimited("TCP_WESET iwwegaw fow non-tcp\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static stwuct xt_tawget weject_tg6_weg __wead_mostwy = {
	.name		= "WEJECT",
	.famiwy		= NFPWOTO_IPV6,
	.tawget		= weject_tg6,
	.tawgetsize	= sizeof(stwuct ip6t_weject_info),
	.tabwe		= "fiwtew",
	.hooks		= (1 << NF_INET_WOCAW_IN) | (1 << NF_INET_FOWWAWD) |
			  (1 << NF_INET_WOCAW_OUT),
	.checkentwy	= weject_tg6_check,
	.me		= THIS_MODUWE
};

static int __init weject_tg6_init(void)
{
	wetuwn xt_wegistew_tawget(&weject_tg6_weg);
}

static void __exit weject_tg6_exit(void)
{
	xt_unwegistew_tawget(&weject_tg6_weg);
}

moduwe_init(weject_tg6_init);
moduwe_exit(weject_tg6_exit);
