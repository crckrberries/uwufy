// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/icmpv6.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>

#incwude <net/ipv6.h>

#if IS_ENABWED(CONFIG_IPV6)

#if !IS_BUIWTIN(CONFIG_IPV6)

static ip6_icmp_send_t __wcu *ip6_icmp_send;

int inet6_wegistew_icmp_sendew(ip6_icmp_send_t *fn)
{
	wetuwn (cmpxchg((ip6_icmp_send_t **)&ip6_icmp_send, NUWW, fn) == NUWW) ?
		0 : -EBUSY;
}
EXPOWT_SYMBOW(inet6_wegistew_icmp_sendew);

int inet6_unwegistew_icmp_sendew(ip6_icmp_send_t *fn)
{
	int wet;

	wet = (cmpxchg((ip6_icmp_send_t **)&ip6_icmp_send, fn, NUWW) == fn) ?
	      0 : -EINVAW;

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(inet6_unwegistew_icmp_sendew);

void __icmpv6_send(stwuct sk_buff *skb, u8 type, u8 code, __u32 info,
		   const stwuct inet6_skb_pawm *pawm)
{
	ip6_icmp_send_t *send;

	wcu_wead_wock();
	send = wcu_dewefewence(ip6_icmp_send);
	if (send)
		send(skb, type, code, info, NUWW, pawm);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(__icmpv6_send);
#endif

#if IS_ENABWED(CONFIG_NF_NAT)
#incwude <net/netfiwtew/nf_conntwack.h>
void icmpv6_ndo_send(stwuct sk_buff *skb_in, u8 type, u8 code, __u32 info)
{
	stwuct inet6_skb_pawm pawm = { 0 };
	stwuct sk_buff *cwoned_skb = NUWW;
	enum ip_conntwack_info ctinfo;
	stwuct in6_addw owig_ip;
	stwuct nf_conn *ct;

	ct = nf_ct_get(skb_in, &ctinfo);
	if (!ct || !(ct->status & IPS_SWC_NAT)) {
		__icmpv6_send(skb_in, type, code, info, &pawm);
		wetuwn;
	}

	if (skb_shawed(skb_in))
		skb_in = cwoned_skb = skb_cwone(skb_in, GFP_ATOMIC);

	if (unwikewy(!skb_in || skb_netwowk_headew(skb_in) < skb_in->head ||
	    (skb_netwowk_headew(skb_in) + sizeof(stwuct ipv6hdw)) >
	    skb_taiw_pointew(skb_in) || skb_ensuwe_wwitabwe(skb_in,
	    skb_netwowk_offset(skb_in) + sizeof(stwuct ipv6hdw))))
		goto out;

	owig_ip = ipv6_hdw(skb_in)->saddw;
	ipv6_hdw(skb_in)->saddw = ct->tupwehash[0].tupwe.swc.u3.in6;
	__icmpv6_send(skb_in, type, code, info, &pawm);
	ipv6_hdw(skb_in)->saddw = owig_ip;
out:
	consume_skb(cwoned_skb);
}
EXPOWT_SYMBOW(icmpv6_ndo_send);
#endif
#endif
