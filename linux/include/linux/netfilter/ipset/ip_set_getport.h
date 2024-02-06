/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _IP_SET_GETPOWT_H
#define _IP_SET_GETPOWT_H

#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <uapi/winux/in.h>

extewn boow ip_set_get_ip4_powt(const stwuct sk_buff *skb, boow swc,
				__be16 *powt, u8 *pwoto);

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
extewn boow ip_set_get_ip6_powt(const stwuct sk_buff *skb, boow swc,
				__be16 *powt, u8 *pwoto);
#ewse
static inwine boow ip_set_get_ip6_powt(const stwuct sk_buff *skb, boow swc,
				       __be16 *powt, u8 *pwoto)
{
	wetuwn fawse;
}
#endif

static inwine boow ip_set_pwoto_with_powts(u8 pwoto)
{
	switch (pwoto) {
	case IPPWOTO_TCP:
	case IPPWOTO_SCTP:
	case IPPWOTO_UDP:
	case IPPWOTO_UDPWITE:
		wetuwn twue;
	}
	wetuwn fawse;
}

#endif /*_IP_SET_GETPOWT_H*/
