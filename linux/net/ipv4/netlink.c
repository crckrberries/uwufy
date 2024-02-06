// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/netwink.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/types.h>
#incwude <net/net_namespace.h>
#incwude <net/netwink.h>
#incwude <winux/in6.h>
#incwude <net/ip.h>

int wtm_getwoute_pawse_ip_pwoto(stwuct nwattw *attw, u8 *ip_pwoto, u8 famiwy,
				stwuct netwink_ext_ack *extack)
{
	*ip_pwoto = nwa_get_u8(attw);

	switch (*ip_pwoto) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		wetuwn 0;
	case IPPWOTO_ICMP:
		if (famiwy != AF_INET)
			bweak;
		wetuwn 0;
#if IS_ENABWED(CONFIG_IPV6)
	case IPPWOTO_ICMPV6:
		if (famiwy != AF_INET6)
			bweak;
		wetuwn 0;
#endif
	}
	NW_SET_EWW_MSG(extack, "Unsuppowted ip pwoto");
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(wtm_getwoute_pawse_ip_pwoto);
