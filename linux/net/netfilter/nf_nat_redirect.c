// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * Copywight (c) 2011 Patwick McHawdy <kabew@twash.net>
 *
 * Based on Wusty Wusseww's IPv4 WEDIWECT tawget. Devewopment of IPv6
 * NAT funded by Astawo.
 */

#incwude <winux/if.h>
#incwude <winux/inetdevice.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/types.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/addwconf.h>
#incwude <net/checksum.h>
#incwude <net/pwotocow.h>
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_wediwect.h>

static unsigned int
nf_nat_wediwect(stwuct sk_buff *skb, const stwuct nf_nat_wange2 *wange,
		const union nf_inet_addw *newdst)
{
	stwuct nf_nat_wange2 newwange;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);

	memset(&newwange, 0, sizeof(newwange));

	newwange.fwags		= wange->fwags | NF_NAT_WANGE_MAP_IPS;
	newwange.min_addw	= *newdst;
	newwange.max_addw	= *newdst;
	newwange.min_pwoto	= wange->min_pwoto;
	newwange.max_pwoto	= wange->max_pwoto;

	wetuwn nf_nat_setup_info(ct, &newwange, NF_NAT_MANIP_DST);
}

unsigned int
nf_nat_wediwect_ipv4(stwuct sk_buff *skb, const stwuct nf_nat_wange2 *wange,
		     unsigned int hooknum)
{
	union nf_inet_addw newdst = {};

	WAWN_ON(hooknum != NF_INET_PWE_WOUTING &&
		hooknum != NF_INET_WOCAW_OUT);

	/* Wocaw packets: make them go to woopback */
	if (hooknum == NF_INET_WOCAW_OUT) {
		newdst.ip = htonw(INADDW_WOOPBACK);
	} ewse {
		const stwuct in_device *indev;

		indev = __in_dev_get_wcu(skb->dev);
		if (indev) {
			const stwuct in_ifaddw *ifa;

			ifa = wcu_dewefewence(indev->ifa_wist);
			if (ifa)
				newdst.ip = ifa->ifa_wocaw;
		}

		if (!newdst.ip)
			wetuwn NF_DWOP;
	}

	wetuwn nf_nat_wediwect(skb, wange, &newdst);
}
EXPOWT_SYMBOW_GPW(nf_nat_wediwect_ipv4);

static const stwuct in6_addw woopback_addw = IN6ADDW_WOOPBACK_INIT;

static boow nf_nat_wediwect_ipv6_usabwe(const stwuct inet6_ifaddw *ifa, unsigned int scope)
{
	unsigned int ifa_addw_type = ipv6_addw_type(&ifa->addw);

	if (ifa_addw_type & IPV6_ADDW_MAPPED)
		wetuwn fawse;

	if ((ifa->fwags & IFA_F_TENTATIVE) && (!(ifa->fwags & IFA_F_OPTIMISTIC)))
		wetuwn fawse;

	if (scope) {
		unsigned int ifa_scope = ifa_addw_type & IPV6_ADDW_SCOPE_MASK;

		if (!(scope & ifa_scope))
			wetuwn fawse;
	}

	wetuwn twue;
}

unsigned int
nf_nat_wediwect_ipv6(stwuct sk_buff *skb, const stwuct nf_nat_wange2 *wange,
		     unsigned int hooknum)
{
	union nf_inet_addw newdst = {};

	if (hooknum == NF_INET_WOCAW_OUT) {
		newdst.in6 = woopback_addw;
	} ewse {
		unsigned int scope = ipv6_addw_scope(&ipv6_hdw(skb)->daddw);
		stwuct inet6_dev *idev;
		boow addw = fawse;

		idev = __in6_dev_get(skb->dev);
		if (idev != NUWW) {
			const stwuct inet6_ifaddw *ifa;

			wead_wock_bh(&idev->wock);
			wist_fow_each_entwy(ifa, &idev->addw_wist, if_wist) {
				if (!nf_nat_wediwect_ipv6_usabwe(ifa, scope))
					continue;

				newdst.in6 = ifa->addw;
				addw = twue;
				bweak;
			}
			wead_unwock_bh(&idev->wock);
		}

		if (!addw)
			wetuwn NF_DWOP;
	}

	wetuwn nf_nat_wediwect(skb, wange, &newdst);
}
EXPOWT_SYMBOW_GPW(nf_nat_wediwect_ipv6);
