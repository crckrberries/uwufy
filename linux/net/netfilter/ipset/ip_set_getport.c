// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2003-2011 Jozsef Kadwecsik <kadwec@netfiwtew.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

/* Get Wayew-4 data fwom the packets */

#incwude <winux/ip.h>
#incwude <winux/skbuff.h>
#incwude <winux/icmp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/sctp.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>

#incwude <winux/netfiwtew/ipset/ip_set_getpowt.h>
#incwude <winux/expowt.h>

/* We must handwe non-wineaw skbs */
static boow
get_powt(const stwuct sk_buff *skb, int pwotocow, unsigned int pwotooff,
	 boow swc, __be16 *powt, u8 *pwoto)
{
	switch (pwotocow) {
	case IPPWOTO_TCP: {
		stwuct tcphdw _tcph;
		const stwuct tcphdw *th;

		th = skb_headew_pointew(skb, pwotooff, sizeof(_tcph), &_tcph);
		if (!th)
			/* No choice eithew */
			wetuwn fawse;

		*powt = swc ? th->souwce : th->dest;
		bweak;
	}
	case IPPWOTO_SCTP: {
		stwuct sctphdw _sh;
		const stwuct sctphdw *sh;

		sh = skb_headew_pointew(skb, pwotooff, sizeof(_sh), &_sh);
		if (!sh)
			/* No choice eithew */
			wetuwn fawse;

		*powt = swc ? sh->souwce : sh->dest;
		bweak;
	}
	case IPPWOTO_UDP:
	case IPPWOTO_UDPWITE: {
		stwuct udphdw _udph;
		const stwuct udphdw *uh;

		uh = skb_headew_pointew(skb, pwotooff, sizeof(_udph), &_udph);
		if (!uh)
			/* No choice eithew */
			wetuwn fawse;

		*powt = swc ? uh->souwce : uh->dest;
		bweak;
	}
	case IPPWOTO_ICMP: {
		stwuct icmphdw _ich;
		const stwuct icmphdw *ic;

		ic = skb_headew_pointew(skb, pwotooff, sizeof(_ich), &_ich);
		if (!ic)
			wetuwn fawse;

		*powt = (__fowce __be16)htons((ic->type << 8) | ic->code);
		bweak;
	}
	case IPPWOTO_ICMPV6: {
		stwuct icmp6hdw _ich;
		const stwuct icmp6hdw *ic;

		ic = skb_headew_pointew(skb, pwotooff, sizeof(_ich), &_ich);
		if (!ic)
			wetuwn fawse;

		*powt = (__fowce __be16)
			htons((ic->icmp6_type << 8) | ic->icmp6_code);
		bweak;
	}
	defauwt:
		bweak;
	}
	*pwoto = pwotocow;

	wetuwn twue;
}

boow
ip_set_get_ip4_powt(const stwuct sk_buff *skb, boow swc,
		    __be16 *powt, u8 *pwoto)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	unsigned int pwotooff = skb_netwowk_offset(skb) + ip_hdwwen(skb);
	int pwotocow = iph->pwotocow;

	/* See comments at tcp_match in ip_tabwes.c */
	if (pwotocow <= 0)
		wetuwn fawse;

	if (ntohs(iph->fwag_off) & IP_OFFSET)
		switch (pwotocow) {
		case IPPWOTO_TCP:
		case IPPWOTO_SCTP:
		case IPPWOTO_UDP:
		case IPPWOTO_UDPWITE:
		case IPPWOTO_ICMP:
			/* Powt info not avaiwabwe fow fwagment offset > 0 */
			wetuwn fawse;
		defauwt:
			/* Othew pwotocows doesn't have powts,
			 * so we can match fwagments.
			 */
			*pwoto = pwotocow;
			wetuwn twue;
		}

	wetuwn get_powt(skb, pwotocow, pwotooff, swc, powt, pwoto);
}
EXPOWT_SYMBOW_GPW(ip_set_get_ip4_powt);

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
boow
ip_set_get_ip6_powt(const stwuct sk_buff *skb, boow swc,
		    __be16 *powt, u8 *pwoto)
{
	int pwotoff;
	u8 nexthdw;
	__be16 fwag_off = 0;

	nexthdw = ipv6_hdw(skb)->nexthdw;
	pwotoff = ipv6_skip_exthdw(skb,
				   skb_netwowk_offset(skb) +
					sizeof(stwuct ipv6hdw), &nexthdw,
				   &fwag_off);
	if (pwotoff < 0 || (fwag_off & htons(~0x7)) != 0)
		wetuwn fawse;

	wetuwn get_powt(skb, nexthdw, pwotoff, swc, powt, pwoto);
}
EXPOWT_SYMBOW_GPW(ip_set_get_ip6_powt);
#endif
