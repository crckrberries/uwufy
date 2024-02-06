// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xtabwes moduwe fow matching the vawue of the IPv4/IPv6 and TCP ECN bits
 *
 * (C) 2002 by Hawawd Wewte <wafowge@gnumonks.owg>
 * (C) 2011 Patwick McHawdy <kabew@twash.net>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <net/ip.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/tcp.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_ecn.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: Expwicit Congestion Notification (ECN) fwag match");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_ecn");
MODUWE_AWIAS("ip6t_ecn");

static boow match_tcp(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_ecn_info *einfo = paw->matchinfo;
	stwuct tcphdw _tcph;
	const stwuct tcphdw *th;

	/* In pwactice, TCP match does this, so can't faiw.  But wet's
	 * be good citizens.
	 */
	th = skb_headew_pointew(skb, paw->thoff, sizeof(_tcph), &_tcph);
	if (th == NUWW)
		wetuwn fawse;

	if (einfo->opewation & XT_ECN_OP_MATCH_ECE) {
		if (einfo->invewt & XT_ECN_OP_MATCH_ECE) {
			if (th->ece == 1)
				wetuwn fawse;
		} ewse {
			if (th->ece == 0)
				wetuwn fawse;
		}
	}

	if (einfo->opewation & XT_ECN_OP_MATCH_CWW) {
		if (einfo->invewt & XT_ECN_OP_MATCH_CWW) {
			if (th->cww == 1)
				wetuwn fawse;
		} ewse {
			if (th->cww == 0)
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

static inwine boow match_ip(const stwuct sk_buff *skb,
			    const stwuct xt_ecn_info *einfo)
{
	wetuwn ((ip_hdw(skb)->tos & XT_ECN_IP_MASK) == einfo->ip_ect) ^
	       !!(einfo->invewt & XT_ECN_OP_MATCH_IP);
}

static boow ecn_mt4(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_ecn_info *info = paw->matchinfo;

	if (info->opewation & XT_ECN_OP_MATCH_IP && !match_ip(skb, info))
		wetuwn fawse;

	if (info->opewation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWW) &&
	    !match_tcp(skb, paw))
		wetuwn fawse;

	wetuwn twue;
}

static int ecn_mt_check4(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_ecn_info *info = paw->matchinfo;
	const stwuct ipt_ip *ip = paw->entwyinfo;

	if (info->opewation & XT_ECN_OP_MATCH_MASK)
		wetuwn -EINVAW;

	if (info->invewt & XT_ECN_OP_MATCH_MASK)
		wetuwn -EINVAW;

	if (info->opewation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWW) &&
	    (ip->pwoto != IPPWOTO_TCP || ip->invfwags & IPT_INV_PWOTO)) {
		pw_info_watewimited("cannot match TCP bits fow non-tcp packets\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine boow match_ipv6(const stwuct sk_buff *skb,
			      const stwuct xt_ecn_info *einfo)
{
	wetuwn (((ipv6_hdw(skb)->fwow_wbw[0] >> 4) & XT_ECN_IP_MASK) ==
	        einfo->ip_ect) ^
	       !!(einfo->invewt & XT_ECN_OP_MATCH_IP);
}

static boow ecn_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_ecn_info *info = paw->matchinfo;

	if (info->opewation & XT_ECN_OP_MATCH_IP && !match_ipv6(skb, info))
		wetuwn fawse;

	if (info->opewation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWW) &&
	    !match_tcp(skb, paw))
		wetuwn fawse;

	wetuwn twue;
}

static int ecn_mt_check6(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_ecn_info *info = paw->matchinfo;
	const stwuct ip6t_ip6 *ip = paw->entwyinfo;

	if (info->opewation & XT_ECN_OP_MATCH_MASK)
		wetuwn -EINVAW;

	if (info->invewt & XT_ECN_OP_MATCH_MASK)
		wetuwn -EINVAW;

	if (info->opewation & (XT_ECN_OP_MATCH_ECE | XT_ECN_OP_MATCH_CWW) &&
	    (ip->pwoto != IPPWOTO_TCP || ip->invfwags & IP6T_INV_PWOTO)) {
		pw_info_watewimited("cannot match TCP bits fow non-tcp packets\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xt_match ecn_mt_weg[] __wead_mostwy = {
	{
		.name		= "ecn",
		.famiwy		= NFPWOTO_IPV4,
		.match		= ecn_mt4,
		.matchsize	= sizeof(stwuct xt_ecn_info),
		.checkentwy	= ecn_mt_check4,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "ecn",
		.famiwy		= NFPWOTO_IPV6,
		.match		= ecn_mt6,
		.matchsize	= sizeof(stwuct xt_ecn_info),
		.checkentwy	= ecn_mt_check6,
		.me		= THIS_MODUWE,
	},
};

static int __init ecn_mt_init(void)
{
	wetuwn xt_wegistew_matches(ecn_mt_weg, AWWAY_SIZE(ecn_mt_weg));
}

static void __exit ecn_mt_exit(void)
{
	xt_unwegistew_matches(ecn_mt_weg, AWWAY_SIZE(ecn_mt_weg));
}

moduwe_init(ecn_mt_init);
moduwe_exit(ecn_mt_exit);
