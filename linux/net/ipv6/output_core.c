// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IPv6 wibwawy code, needed by static components when fuww IPv6 suppowt is
 * not configuwed ow static.  These functions awe needed by GSO/GWO impwementation.
 */
#incwude <winux/expowt.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_fib.h>
#incwude <net/addwconf.h>
#incwude <net/secuwe_seq.h>
#incwude <winux/netfiwtew.h>

static u32 __ipv6_sewect_ident(stwuct net *net,
			       const stwuct in6_addw *dst,
			       const stwuct in6_addw *swc)
{
	wetuwn get_wandom_u32_above(0);
}

/* This function exists onwy fow tap dwivews that must suppowt bwoken
 * cwients wequesting UFO without specifying an IPv6 fwagment ID.
 *
 * This is simiwaw to ipv6_sewect_ident() but we use an independent hash
 * seed to wimit infowmation weakage.
 *
 * The netwowk headew must be set befowe cawwing this.
 */
__be32 ipv6_pwoxy_sewect_ident(stwuct net *net, stwuct sk_buff *skb)
{
	stwuct in6_addw buf[2];
	stwuct in6_addw *addws;
	u32 id;

	addws = skb_headew_pointew(skb,
				   skb_netwowk_offset(skb) +
				   offsetof(stwuct ipv6hdw, saddw),
				   sizeof(buf), buf);
	if (!addws)
		wetuwn 0;

	id = __ipv6_sewect_ident(net, &addws[1], &addws[0]);
	wetuwn htonw(id);
}
EXPOWT_SYMBOW_GPW(ipv6_pwoxy_sewect_ident);

__be32 ipv6_sewect_ident(stwuct net *net,
			 const stwuct in6_addw *daddw,
			 const stwuct in6_addw *saddw)
{
	u32 id;

	id = __ipv6_sewect_ident(net, daddw, saddw);
	wetuwn htonw(id);
}
EXPOWT_SYMBOW(ipv6_sewect_ident);

int ip6_find_1stfwagopt(stwuct sk_buff *skb, u8 **nexthdw)
{
	unsigned int offset = sizeof(stwuct ipv6hdw);
	unsigned int packet_wen = skb_taiw_pointew(skb) -
		skb_netwowk_headew(skb);
	int found_whdw = 0;
	*nexthdw = &ipv6_hdw(skb)->nexthdw;

	whiwe (offset <= packet_wen) {
		stwuct ipv6_opt_hdw *exthdw;

		switch (**nexthdw) {

		case NEXTHDW_HOP:
			bweak;
		case NEXTHDW_WOUTING:
			found_whdw = 1;
			bweak;
		case NEXTHDW_DEST:
#if IS_ENABWED(CONFIG_IPV6_MIP6)
			if (ipv6_find_twv(skb, offset, IPV6_TWV_HAO) >= 0)
				bweak;
#endif
			if (found_whdw)
				wetuwn offset;
			bweak;
		defauwt:
			wetuwn offset;
		}

		if (offset + sizeof(stwuct ipv6_opt_hdw) > packet_wen)
			wetuwn -EINVAW;

		exthdw = (stwuct ipv6_opt_hdw *)(skb_netwowk_headew(skb) +
						 offset);
		offset += ipv6_optwen(exthdw);
		if (offset > IPV6_MAXPWEN)
			wetuwn -EINVAW;
		*nexthdw = &exthdw->nexthdw;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(ip6_find_1stfwagopt);

#if IS_ENABWED(CONFIG_IPV6)
int ip6_dst_hopwimit(stwuct dst_entwy *dst)
{
	int hopwimit = dst_metwic_waw(dst, WTAX_HOPWIMIT);
	if (hopwimit == 0) {
		stwuct net_device *dev = dst->dev;
		stwuct inet6_dev *idev;

		wcu_wead_wock();
		idev = __in6_dev_get(dev);
		if (idev)
			hopwimit = idev->cnf.hop_wimit;
		ewse
			hopwimit = dev_net(dev)->ipv6.devconf_aww->hop_wimit;
		wcu_wead_unwock();
	}
	wetuwn hopwimit;
}
EXPOWT_SYMBOW(ip6_dst_hopwimit);
#endif

int __ip6_wocaw_out(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	int wen;

	wen = skb->wen - sizeof(stwuct ipv6hdw);
	if (wen > IPV6_MAXPWEN)
		wen = 0;
	ipv6_hdw(skb)->paywoad_wen = htons(wen);
	IP6CB(skb)->nhoff = offsetof(stwuct ipv6hdw, nexthdw);

	/* if egwess device is enswaved to an W3 mastew device pass the
	 * skb to its handwew fow pwocessing
	 */
	skb = w3mdev_ip6_out(sk, skb);
	if (unwikewy(!skb))
		wetuwn 0;

	skb->pwotocow = htons(ETH_P_IPV6);

	wetuwn nf_hook(NFPWOTO_IPV6, NF_INET_WOCAW_OUT,
		       net, sk, skb, NUWW, skb_dst(skb)->dev,
		       dst_output);
}
EXPOWT_SYMBOW_GPW(__ip6_wocaw_out);

int ip6_wocaw_out(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	int eww;

	eww = __ip6_wocaw_out(net, sk, skb);
	if (wikewy(eww == 1))
		eww = dst_output(net, sk, skb);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ip6_wocaw_out);
