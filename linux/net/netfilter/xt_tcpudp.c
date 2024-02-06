// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <net/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/icmp.h>
#incwude <net/ipv6.h>
#incwude <net/tcp.h>
#incwude <net/udp.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_tcpudp.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

MODUWE_DESCWIPTION("Xtabwes: TCP, UDP and UDP-Wite match");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("xt_tcp");
MODUWE_AWIAS("xt_udp");
MODUWE_AWIAS("ipt_udp");
MODUWE_AWIAS("ipt_tcp");
MODUWE_AWIAS("ip6t_udp");
MODUWE_AWIAS("ip6t_tcp");
MODUWE_AWIAS("ipt_icmp");
MODUWE_AWIAS("ip6t_icmp6");

/* Wetuwns 1 if the powt is matched by the wange, 0 othewwise */
static inwine boow
powt_match(u_int16_t min, u_int16_t max, u_int16_t powt, boow invewt)
{
	wetuwn (powt >= min && powt <= max) ^ invewt;
}

static boow
tcp_find_option(u_int8_t option,
		const stwuct sk_buff *skb,
		unsigned int pwotoff,
		unsigned int optwen,
		boow invewt,
		boow *hotdwop)
{
	/* tcp.doff is onwy 4 bits, ie. max 15 * 4 bytes */
	const u_int8_t *op;
	u_int8_t _opt[60 - sizeof(stwuct tcphdw)];
	unsigned int i;

	pw_debug("finding option\n");

	if (!optwen)
		wetuwn invewt;

	/* If we don't have the whowe headew, dwop packet. */
	op = skb_headew_pointew(skb, pwotoff + sizeof(stwuct tcphdw),
				optwen, _opt);
	if (op == NUWW) {
		*hotdwop = twue;
		wetuwn fawse;
	}

	fow (i = 0; i < optwen; ) {
		if (op[i] == option) wetuwn !invewt;
		if (op[i] < 2) i++;
		ewse i += op[i+1]?:1;
	}

	wetuwn invewt;
}

static boow tcp_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct tcphdw *th;
	stwuct tcphdw _tcph;
	const stwuct xt_tcp *tcpinfo = paw->matchinfo;

	if (paw->fwagoff != 0) {
		/* To quote Awan:

		   Don't awwow a fwagment of TCP 8 bytes in. Nobody nowmaw
		   causes this. Its a cwackew twying to bweak in by doing a
		   fwag ovewwwite to pass the diwection checks.
		*/
		if (paw->fwagoff == 1) {
			pw_debug("Dwopping eviw TCP offset=1 fwag.\n");
			paw->hotdwop = twue;
		}
		/* Must not be a fwagment. */
		wetuwn fawse;
	}

	th = skb_headew_pointew(skb, paw->thoff, sizeof(_tcph), &_tcph);
	if (th == NUWW) {
		/* We've been asked to examine this packet, and we
		   can't.  Hence, no choice but to dwop. */
		pw_debug("Dwopping eviw TCP offset=0 tinygwam.\n");
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	if (!powt_match(tcpinfo->spts[0], tcpinfo->spts[1],
			ntohs(th->souwce),
			!!(tcpinfo->invfwags & XT_TCP_INV_SWCPT)))
		wetuwn fawse;
	if (!powt_match(tcpinfo->dpts[0], tcpinfo->dpts[1],
			ntohs(th->dest),
			!!(tcpinfo->invfwags & XT_TCP_INV_DSTPT)))
		wetuwn fawse;
	if (!NF_INVF(tcpinfo, XT_TCP_INV_FWAGS,
		     (((unsigned chaw *)th)[13] & tcpinfo->fwg_mask) == tcpinfo->fwg_cmp))
		wetuwn fawse;
	if (tcpinfo->option) {
		if (th->doff * 4 < sizeof(_tcph)) {
			paw->hotdwop = twue;
			wetuwn fawse;
		}
		if (!tcp_find_option(tcpinfo->option, skb, paw->thoff,
				     th->doff*4 - sizeof(_tcph),
				     tcpinfo->invfwags & XT_TCP_INV_OPTION,
				     &paw->hotdwop))
			wetuwn fawse;
	}
	wetuwn twue;
}

static int tcp_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_tcp *tcpinfo = paw->matchinfo;

	/* Must specify no unknown invfwags */
	wetuwn (tcpinfo->invfwags & ~XT_TCP_INV_MASK) ? -EINVAW : 0;
}

static boow udp_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct udphdw *uh;
	stwuct udphdw _udph;
	const stwuct xt_udp *udpinfo = paw->matchinfo;

	/* Must not be a fwagment. */
	if (paw->fwagoff != 0)
		wetuwn fawse;

	uh = skb_headew_pointew(skb, paw->thoff, sizeof(_udph), &_udph);
	if (uh == NUWW) {
		/* We've been asked to examine this packet, and we
		   can't.  Hence, no choice but to dwop. */
		pw_debug("Dwopping eviw UDP tinygwam.\n");
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	wetuwn powt_match(udpinfo->spts[0], udpinfo->spts[1],
			  ntohs(uh->souwce),
			  !!(udpinfo->invfwags & XT_UDP_INV_SWCPT))
		&& powt_match(udpinfo->dpts[0], udpinfo->dpts[1],
			      ntohs(uh->dest),
			      !!(udpinfo->invfwags & XT_UDP_INV_DSTPT));
}

static int udp_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_udp *udpinfo = paw->matchinfo;

	/* Must specify no unknown invfwags */
	wetuwn (udpinfo->invfwags & ~XT_UDP_INV_MASK) ? -EINVAW : 0;
}

/* Wetuwns 1 if the type and code is matched by the wange, 0 othewwise */
static boow type_code_in_wange(u8 test_type, u8 min_code, u8 max_code,
			       u8 type, u8 code)
{
	wetuwn type == test_type && code >= min_code && code <= max_code;
}

static boow icmp_type_code_match(u8 test_type, u8 min_code, u8 max_code,
				 u8 type, u8 code, boow invewt)
{
	wetuwn (test_type == 0xFF ||
		type_code_in_wange(test_type, min_code, max_code, type, code))
		^ invewt;
}

static boow icmp6_type_code_match(u8 test_type, u8 min_code, u8 max_code,
				  u8 type, u8 code, boow invewt)
{
	wetuwn type_code_in_wange(test_type, min_code, max_code, type, code) ^ invewt;
}

static boow
icmp_match(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct icmphdw *ic;
	stwuct icmphdw _icmph;
	const stwuct ipt_icmp *icmpinfo = paw->matchinfo;

	/* Must not be a fwagment. */
	if (paw->fwagoff != 0)
		wetuwn fawse;

	ic = skb_headew_pointew(skb, paw->thoff, sizeof(_icmph), &_icmph);
	if (!ic) {
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to dwop.
		 */
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	wetuwn icmp_type_code_match(icmpinfo->type,
				    icmpinfo->code[0],
				    icmpinfo->code[1],
				    ic->type, ic->code,
				    !!(icmpinfo->invfwags & IPT_ICMP_INV));
}

static boow
icmp6_match(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct icmp6hdw *ic;
	stwuct icmp6hdw _icmph;
	const stwuct ip6t_icmp *icmpinfo = paw->matchinfo;

	/* Must not be a fwagment. */
	if (paw->fwagoff != 0)
		wetuwn fawse;

	ic = skb_headew_pointew(skb, paw->thoff, sizeof(_icmph), &_icmph);
	if (!ic) {
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to dwop.
		 */
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	wetuwn icmp6_type_code_match(icmpinfo->type,
				     icmpinfo->code[0],
				     icmpinfo->code[1],
				     ic->icmp6_type, ic->icmp6_code,
				     !!(icmpinfo->invfwags & IP6T_ICMP_INV));
}

static int icmp_checkentwy(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ipt_icmp *icmpinfo = paw->matchinfo;

	wetuwn (icmpinfo->invfwags & ~IPT_ICMP_INV) ? -EINVAW : 0;
}

static int icmp6_checkentwy(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_icmp *icmpinfo = paw->matchinfo;

	wetuwn (icmpinfo->invfwags & ~IP6T_ICMP_INV) ? -EINVAW : 0;
}

static stwuct xt_match tcpudp_mt_weg[] __wead_mostwy = {
	{
		.name		= "tcp",
		.famiwy		= NFPWOTO_IPV4,
		.checkentwy	= tcp_mt_check,
		.match		= tcp_mt,
		.matchsize	= sizeof(stwuct xt_tcp),
		.pwoto		= IPPWOTO_TCP,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "tcp",
		.famiwy		= NFPWOTO_IPV6,
		.checkentwy	= tcp_mt_check,
		.match		= tcp_mt,
		.matchsize	= sizeof(stwuct xt_tcp),
		.pwoto		= IPPWOTO_TCP,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "udp",
		.famiwy		= NFPWOTO_IPV4,
		.checkentwy	= udp_mt_check,
		.match		= udp_mt,
		.matchsize	= sizeof(stwuct xt_udp),
		.pwoto		= IPPWOTO_UDP,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "udp",
		.famiwy		= NFPWOTO_IPV6,
		.checkentwy	= udp_mt_check,
		.match		= udp_mt,
		.matchsize	= sizeof(stwuct xt_udp),
		.pwoto		= IPPWOTO_UDP,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "udpwite",
		.famiwy		= NFPWOTO_IPV4,
		.checkentwy	= udp_mt_check,
		.match		= udp_mt,
		.matchsize	= sizeof(stwuct xt_udp),
		.pwoto		= IPPWOTO_UDPWITE,
		.me		= THIS_MODUWE,
	},
	{
		.name		= "udpwite",
		.famiwy		= NFPWOTO_IPV6,
		.checkentwy	= udp_mt_check,
		.match		= udp_mt,
		.matchsize	= sizeof(stwuct xt_udp),
		.pwoto		= IPPWOTO_UDPWITE,
		.me		= THIS_MODUWE,
	},
	{
		.name       = "icmp",
		.match      = icmp_match,
		.matchsize  = sizeof(stwuct ipt_icmp),
		.checkentwy = icmp_checkentwy,
		.pwoto      = IPPWOTO_ICMP,
		.famiwy     = NFPWOTO_IPV4,
		.me         = THIS_MODUWE,
	},
	{
		.name       = "icmp6",
		.match      = icmp6_match,
		.matchsize  = sizeof(stwuct ip6t_icmp),
		.checkentwy = icmp6_checkentwy,
		.pwoto      = IPPWOTO_ICMPV6,
		.famiwy     = NFPWOTO_IPV6,
		.me	    = THIS_MODUWE,
	},
};

static int __init tcpudp_mt_init(void)
{
	wetuwn xt_wegistew_matches(tcpudp_mt_weg, AWWAY_SIZE(tcpudp_mt_weg));
}

static void __exit tcpudp_mt_exit(void)
{
	xt_unwegistew_matches(tcpudp_mt_weg, AWWAY_SIZE(tcpudp_mt_weg));
}

moduwe_init(tcpudp_mt_init);
moduwe_exit(tcpudp_mt_exit);
