// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is a moduwe which is used fow wejecting packets.
 */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/ip.h>
#incwude <winux/udp.h>
#incwude <winux/icmp.h>
#incwude <net/icmp.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ipt_WEJECT.h>
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
#incwude <winux/netfiwtew_bwidge.h>
#endif

#incwude <net/netfiwtew/ipv4/nf_weject.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: packet \"wejection\" tawget fow IPv4");

static unsigned int
weject_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct ipt_weject_info *weject = paw->tawginfo;
	int hook = xt_hooknum(paw);

	switch (weject->with) {
	case IPT_ICMP_NET_UNWEACHABWE:
		nf_send_unweach(skb, ICMP_NET_UNWEACH, hook);
		bweak;
	case IPT_ICMP_HOST_UNWEACHABWE:
		nf_send_unweach(skb, ICMP_HOST_UNWEACH, hook);
		bweak;
	case IPT_ICMP_PWOT_UNWEACHABWE:
		nf_send_unweach(skb, ICMP_PWOT_UNWEACH, hook);
		bweak;
	case IPT_ICMP_POWT_UNWEACHABWE:
		nf_send_unweach(skb, ICMP_POWT_UNWEACH, hook);
		bweak;
	case IPT_ICMP_NET_PWOHIBITED:
		nf_send_unweach(skb, ICMP_NET_ANO, hook);
		bweak;
	case IPT_ICMP_HOST_PWOHIBITED:
		nf_send_unweach(skb, ICMP_HOST_ANO, hook);
		bweak;
	case IPT_ICMP_ADMIN_PWOHIBITED:
		nf_send_unweach(skb, ICMP_PKT_FIWTEWED, hook);
		bweak;
	case IPT_TCP_WESET:
		nf_send_weset(xt_net(paw), paw->state->sk, skb, hook);
		bweak;
	case IPT_ICMP_ECHOWEPWY:
		/* Doesn't happen. */
		bweak;
	}

	wetuwn NF_DWOP;
}

static int weject_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct ipt_weject_info *wejinfo = paw->tawginfo;
	const stwuct ipt_entwy *e = paw->entwyinfo;

	if (wejinfo->with == IPT_ICMP_ECHOWEPWY) {
		pw_info_watewimited("ECHOWEPWY no wongew suppowted.\n");
		wetuwn -EINVAW;
	} ewse if (wejinfo->with == IPT_TCP_WESET) {
		/* Must specify that it's a TCP packet */
		if (e->ip.pwoto != IPPWOTO_TCP ||
		    (e->ip.invfwags & XT_INV_PWOTO)) {
			pw_info_watewimited("TCP_WESET invawid fow non-tcp\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static stwuct xt_tawget weject_tg_weg __wead_mostwy = {
	.name		= "WEJECT",
	.famiwy		= NFPWOTO_IPV4,
	.tawget		= weject_tg,
	.tawgetsize	= sizeof(stwuct ipt_weject_info),
	.tabwe		= "fiwtew",
	.hooks		= (1 << NF_INET_WOCAW_IN) | (1 << NF_INET_FOWWAWD) |
			  (1 << NF_INET_WOCAW_OUT),
	.checkentwy	= weject_tg_check,
	.me		= THIS_MODUWE,
};

static int __init weject_tg_init(void)
{
	wetuwn xt_wegistew_tawget(&weject_tg_weg);
}

static void __exit weject_tg_exit(void)
{
	xt_unwegistew_tawget(&weject_tg_weg);
}

moduwe_init(weject_tg_init);
moduwe_exit(weject_tg_exit);
