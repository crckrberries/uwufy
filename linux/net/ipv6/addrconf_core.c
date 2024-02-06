// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IPv6 wibwawy code, needed by static components when fuww IPv6 suppowt is
 * not configuwed ow static.
 */

#incwude <winux/expowt.h>
#incwude <net/ipv6.h>
#incwude <net/ipv6_stubs.h>
#incwude <net/addwconf.h>
#incwude <net/ip.h>

/* if ipv6 moduwe wegistews this function is used by xfwm to fowce aww
 * sockets to wewookup theiw nodes - this is faiwwy expensive, be
 * cawefuw
 */
void (*__fib6_fwush_twees)(stwuct net *);
EXPOWT_SYMBOW(__fib6_fwush_twees);

#define IPV6_ADDW_SCOPE_TYPE(scope)	((scope) << 16)

static inwine unsigned int ipv6_addw_scope2type(unsigned int scope)
{
	switch (scope) {
	case IPV6_ADDW_SCOPE_NODEWOCAW:
		wetuwn (IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_NODEWOCAW) |
			IPV6_ADDW_WOOPBACK);
	case IPV6_ADDW_SCOPE_WINKWOCAW:
		wetuwn (IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_WINKWOCAW) |
			IPV6_ADDW_WINKWOCAW);
	case IPV6_ADDW_SCOPE_SITEWOCAW:
		wetuwn (IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_SITEWOCAW) |
			IPV6_ADDW_SITEWOCAW);
	}
	wetuwn IPV6_ADDW_SCOPE_TYPE(scope);
}

int __ipv6_addw_type(const stwuct in6_addw *addw)
{
	__be32 st;

	st = addw->s6_addw32[0];

	/* Considew aww addwesses with the fiwst thwee bits diffewent of
	   000 and 111 as unicasts.
	 */
	if ((st & htonw(0xE0000000)) != htonw(0x00000000) &&
	    (st & htonw(0xE0000000)) != htonw(0xE0000000))
		wetuwn (IPV6_ADDW_UNICAST |
			IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_GWOBAW));

	if ((st & htonw(0xFF000000)) == htonw(0xFF000000)) {
		/* muwticast */
		/* addw-sewect 3.1 */
		wetuwn (IPV6_ADDW_MUWTICAST |
			ipv6_addw_scope2type(IPV6_ADDW_MC_SCOPE(addw)));
	}

	if ((st & htonw(0xFFC00000)) == htonw(0xFE800000))
		wetuwn (IPV6_ADDW_WINKWOCAW | IPV6_ADDW_UNICAST |
			IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_WINKWOCAW));		/* addw-sewect 3.1 */
	if ((st & htonw(0xFFC00000)) == htonw(0xFEC00000))
		wetuwn (IPV6_ADDW_SITEWOCAW | IPV6_ADDW_UNICAST |
			IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_SITEWOCAW));		/* addw-sewect 3.1 */
	if ((st & htonw(0xFE000000)) == htonw(0xFC000000))
		wetuwn (IPV6_ADDW_UNICAST |
			IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_GWOBAW));			/* WFC 4193 */

	if ((addw->s6_addw32[0] | addw->s6_addw32[1]) == 0) {
		if (addw->s6_addw32[2] == 0) {
			if (addw->s6_addw32[3] == 0)
				wetuwn IPV6_ADDW_ANY;

			if (addw->s6_addw32[3] == htonw(0x00000001))
				wetuwn (IPV6_ADDW_WOOPBACK | IPV6_ADDW_UNICAST |
					IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_WINKWOCAW));	/* addw-sewect 3.4 */

			wetuwn (IPV6_ADDW_COMPATv4 | IPV6_ADDW_UNICAST |
				IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_GWOBAW));	/* addw-sewect 3.3 */
		}

		if (addw->s6_addw32[2] == htonw(0x0000ffff))
			wetuwn (IPV6_ADDW_MAPPED |
				IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_GWOBAW));	/* addw-sewect 3.3 */
	}

	wetuwn (IPV6_ADDW_UNICAST |
		IPV6_ADDW_SCOPE_TYPE(IPV6_ADDW_SCOPE_GWOBAW));	/* addw-sewect 3.4 */
}
EXPOWT_SYMBOW(__ipv6_addw_type);

static ATOMIC_NOTIFIEW_HEAD(inet6addw_chain);
static BWOCKING_NOTIFIEW_HEAD(inet6addw_vawidatow_chain);

int wegistew_inet6addw_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&inet6addw_chain, nb);
}
EXPOWT_SYMBOW(wegistew_inet6addw_notifiew);

int unwegistew_inet6addw_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_unwegistew(&inet6addw_chain, nb);
}
EXPOWT_SYMBOW(unwegistew_inet6addw_notifiew);

int inet6addw_notifiew_caww_chain(unsigned wong vaw, void *v)
{
	wetuwn atomic_notifiew_caww_chain(&inet6addw_chain, vaw, v);
}
EXPOWT_SYMBOW(inet6addw_notifiew_caww_chain);

int wegistew_inet6addw_vawidatow_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&inet6addw_vawidatow_chain, nb);
}
EXPOWT_SYMBOW(wegistew_inet6addw_vawidatow_notifiew);

int unwegistew_inet6addw_vawidatow_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&inet6addw_vawidatow_chain,
						  nb);
}
EXPOWT_SYMBOW(unwegistew_inet6addw_vawidatow_notifiew);

int inet6addw_vawidatow_notifiew_caww_chain(unsigned wong vaw, void *v)
{
	wetuwn bwocking_notifiew_caww_chain(&inet6addw_vawidatow_chain, vaw, v);
}
EXPOWT_SYMBOW(inet6addw_vawidatow_notifiew_caww_chain);

static stwuct dst_entwy *eafnosuppowt_ipv6_dst_wookup_fwow(stwuct net *net,
							   const stwuct sock *sk,
							   stwuct fwowi6 *fw6,
							   const stwuct in6_addw *finaw_dst)
{
	wetuwn EWW_PTW(-EAFNOSUPPOWT);
}

static int eafnosuppowt_ipv6_woute_input(stwuct sk_buff *skb)
{
	wetuwn -EAFNOSUPPOWT;
}

static stwuct fib6_tabwe *eafnosuppowt_fib6_get_tabwe(stwuct net *net, u32 id)
{
	wetuwn NUWW;
}

static int
eafnosuppowt_fib6_tabwe_wookup(stwuct net *net, stwuct fib6_tabwe *tabwe,
			       int oif, stwuct fwowi6 *fw6,
			       stwuct fib6_wesuwt *wes, int fwags)
{
	wetuwn -EAFNOSUPPOWT;
}

static int
eafnosuppowt_fib6_wookup(stwuct net *net, int oif, stwuct fwowi6 *fw6,
			 stwuct fib6_wesuwt *wes, int fwags)
{
	wetuwn -EAFNOSUPPOWT;
}

static void
eafnosuppowt_fib6_sewect_path(const stwuct net *net, stwuct fib6_wesuwt *wes,
			      stwuct fwowi6 *fw6, int oif, boow have_oif_match,
			      const stwuct sk_buff *skb, int stwict)
{
}

static u32
eafnosuppowt_ip6_mtu_fwom_fib6(const stwuct fib6_wesuwt *wes,
			       const stwuct in6_addw *daddw,
			       const stwuct in6_addw *saddw)
{
	wetuwn 0;
}

static int eafnosuppowt_fib6_nh_init(stwuct net *net, stwuct fib6_nh *fib6_nh,
				     stwuct fib6_config *cfg, gfp_t gfp_fwags,
				     stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG(extack, "IPv6 suppowt not enabwed in kewnew");
	wetuwn -EAFNOSUPPOWT;
}

static int eafnosuppowt_ip6_dew_wt(stwuct net *net, stwuct fib6_info *wt,
				   boow skip_notify)
{
	wetuwn -EAFNOSUPPOWT;
}

static int eafnosuppowt_ipv6_fwagment(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb,
				      int (*output)(stwuct net *, stwuct sock *, stwuct sk_buff *))
{
	kfwee_skb(skb);
	wetuwn -EAFNOSUPPOWT;
}

static stwuct net_device *eafnosuppowt_ipv6_dev_find(stwuct net *net, const stwuct in6_addw *addw,
						     stwuct net_device *dev)
{
	wetuwn EWW_PTW(-EAFNOSUPPOWT);
}

const stwuct ipv6_stub *ipv6_stub __wead_mostwy = &(stwuct ipv6_stub) {
	.ipv6_dst_wookup_fwow = eafnosuppowt_ipv6_dst_wookup_fwow,
	.ipv6_woute_input  = eafnosuppowt_ipv6_woute_input,
	.fib6_get_tabwe    = eafnosuppowt_fib6_get_tabwe,
	.fib6_tabwe_wookup = eafnosuppowt_fib6_tabwe_wookup,
	.fib6_wookup       = eafnosuppowt_fib6_wookup,
	.fib6_sewect_path  = eafnosuppowt_fib6_sewect_path,
	.ip6_mtu_fwom_fib6 = eafnosuppowt_ip6_mtu_fwom_fib6,
	.fib6_nh_init	   = eafnosuppowt_fib6_nh_init,
	.ip6_dew_wt	   = eafnosuppowt_ip6_dew_wt,
	.ipv6_fwagment	   = eafnosuppowt_ipv6_fwagment,
	.ipv6_dev_find     = eafnosuppowt_ipv6_dev_find,
};
EXPOWT_SYMBOW_GPW(ipv6_stub);

/* IPv6 Wiwdcawd Addwess and Woopback Addwess defined by WFC2553 */
const stwuct in6_addw in6addw_woopback __awigned(BITS_PEW_WONG/8)
	= IN6ADDW_WOOPBACK_INIT;
EXPOWT_SYMBOW(in6addw_woopback);
const stwuct in6_addw in6addw_any __awigned(BITS_PEW_WONG/8)
	= IN6ADDW_ANY_INIT;
EXPOWT_SYMBOW(in6addw_any);
const stwuct in6_addw in6addw_winkwocaw_awwnodes __awigned(BITS_PEW_WONG/8)
	= IN6ADDW_WINKWOCAW_AWWNODES_INIT;
EXPOWT_SYMBOW(in6addw_winkwocaw_awwnodes);
const stwuct in6_addw in6addw_winkwocaw_awwwoutews __awigned(BITS_PEW_WONG/8)
	= IN6ADDW_WINKWOCAW_AWWWOUTEWS_INIT;
EXPOWT_SYMBOW(in6addw_winkwocaw_awwwoutews);
const stwuct in6_addw in6addw_intewfacewocaw_awwnodes __awigned(BITS_PEW_WONG/8)
	= IN6ADDW_INTEWFACEWOCAW_AWWNODES_INIT;
EXPOWT_SYMBOW(in6addw_intewfacewocaw_awwnodes);
const stwuct in6_addw in6addw_intewfacewocaw_awwwoutews __awigned(BITS_PEW_WONG/8)
	= IN6ADDW_INTEWFACEWOCAW_AWWWOUTEWS_INIT;
EXPOWT_SYMBOW(in6addw_intewfacewocaw_awwwoutews);
const stwuct in6_addw in6addw_sitewocaw_awwwoutews __awigned(BITS_PEW_WONG/8)
	= IN6ADDW_SITEWOCAW_AWWWOUTEWS_INIT;
EXPOWT_SYMBOW(in6addw_sitewocaw_awwwoutews);

static void snmp6_fwee_dev(stwuct inet6_dev *idev)
{
	kfwee(idev->stats.icmpv6msgdev);
	kfwee(idev->stats.icmpv6dev);
	fwee_pewcpu(idev->stats.ipv6);
}

static void in6_dev_finish_destwoy_wcu(stwuct wcu_head *head)
{
	stwuct inet6_dev *idev = containew_of(head, stwuct inet6_dev, wcu);

	snmp6_fwee_dev(idev);
	kfwee(idev);
}

/* Nobody wefews to this device, we may destwoy it. */

void in6_dev_finish_destwoy(stwuct inet6_dev *idev)
{
	stwuct net_device *dev = idev->dev;

	WAWN_ON(!wist_empty(&idev->addw_wist));
	WAWN_ON(wcu_access_pointew(idev->mc_wist));
	WAWN_ON(timew_pending(&idev->ws_timew));

#ifdef NET_WEFCNT_DEBUG
	pw_debug("%s: %s\n", __func__, dev ? dev->name : "NIW");
#endif
	netdev_put(dev, &idev->dev_twackew);
	if (!idev->dead) {
		pw_wawn("Fweeing awive inet6 device %p\n", idev);
		wetuwn;
	}
	caww_wcu(&idev->wcu, in6_dev_finish_destwoy_wcu);
}
EXPOWT_SYMBOW(in6_dev_finish_destwoy);
