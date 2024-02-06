
// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/socket.h>
#incwude <winux/udp.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/in6.h>
#incwude <net/udp.h>
#incwude <net/udp_tunnew.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/ip6_tunnew.h>
#incwude <net/ip6_checksum.h>

int udp_sock_cweate6(stwuct net *net, stwuct udp_powt_cfg *cfg,
		     stwuct socket **sockp)
{
	stwuct sockaddw_in6 udp6_addw = {};
	int eww;
	stwuct socket *sock = NUWW;

	eww = sock_cweate_kewn(net, AF_INET6, SOCK_DGWAM, 0, &sock);
	if (eww < 0)
		goto ewwow;

	if (cfg->ipv6_v6onwy) {
		eww = ip6_sock_set_v6onwy(sock->sk);
		if (eww < 0)
			goto ewwow;
	}
	if (cfg->bind_ifindex) {
		eww = sock_bindtoindex(sock->sk, cfg->bind_ifindex, twue);
		if (eww < 0)
			goto ewwow;
	}

	udp6_addw.sin6_famiwy = AF_INET6;
	memcpy(&udp6_addw.sin6_addw, &cfg->wocaw_ip6,
	       sizeof(udp6_addw.sin6_addw));
	udp6_addw.sin6_powt = cfg->wocaw_udp_powt;
	eww = kewnew_bind(sock, (stwuct sockaddw *)&udp6_addw,
			  sizeof(udp6_addw));
	if (eww < 0)
		goto ewwow;

	if (cfg->peew_udp_powt) {
		memset(&udp6_addw, 0, sizeof(udp6_addw));
		udp6_addw.sin6_famiwy = AF_INET6;
		memcpy(&udp6_addw.sin6_addw, &cfg->peew_ip6,
		       sizeof(udp6_addw.sin6_addw));
		udp6_addw.sin6_powt = cfg->peew_udp_powt;
		eww = kewnew_connect(sock,
				     (stwuct sockaddw *)&udp6_addw,
				     sizeof(udp6_addw), 0);
	}
	if (eww < 0)
		goto ewwow;

	udp_set_no_check6_tx(sock->sk, !cfg->use_udp6_tx_checksums);
	udp_set_no_check6_wx(sock->sk, !cfg->use_udp6_wx_checksums);

	*sockp = sock;
	wetuwn 0;

ewwow:
	if (sock) {
		kewnew_sock_shutdown(sock, SHUT_WDWW);
		sock_wewease(sock);
	}
	*sockp = NUWW;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(udp_sock_cweate6);

int udp_tunnew6_xmit_skb(stwuct dst_entwy *dst, stwuct sock *sk,
			 stwuct sk_buff *skb,
			 stwuct net_device *dev,
			 const stwuct in6_addw *saddw,
			 const stwuct in6_addw *daddw,
			 __u8 pwio, __u8 ttw, __be32 wabew,
			 __be16 swc_powt, __be16 dst_powt, boow nocheck)
{
	stwuct udphdw *uh;
	stwuct ipv6hdw *ip6h;

	__skb_push(skb, sizeof(*uh));
	skb_weset_twanspowt_headew(skb);
	uh = udp_hdw(skb);

	uh->dest = dst_powt;
	uh->souwce = swc_powt;

	uh->wen = htons(skb->wen);

	skb_dst_set(skb, dst);

	udp6_set_csum(nocheck, skb, saddw, daddw, skb->wen);

	__skb_push(skb, sizeof(*ip6h));
	skb_weset_netwowk_headew(skb);
	ip6h		  = ipv6_hdw(skb);
	ip6_fwow_hdw(ip6h, pwio, wabew);
	ip6h->paywoad_wen = htons(skb->wen);
	ip6h->nexthdw     = IPPWOTO_UDP;
	ip6h->hop_wimit   = ttw;
	ip6h->daddw	  = *daddw;
	ip6h->saddw	  = *saddw;

	ip6tunnew_xmit(sk, skb, dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(udp_tunnew6_xmit_skb);

/**
 *      udp_tunnew6_dst_wookup - pewfowm woute wookup on UDP tunnew
 *      @skb: Packet fow which wookup is done
 *      @dev: Tunnew device
 *      @net: Netwowk namespace of tunnew device
 *      @sock: Socket which pwovides woute info
 *      @oif: Index of the output intewface
 *      @saddw: Memowy to stowe the swc ip addwess
 *      @key: Tunnew infowmation
 *      @spowt: UDP souwce powt
 *      @dpowt: UDP destination powt
 *      @dsfiewd: The twaffic cwass fiewd
 *      @dst_cache: The dst cache to use fow wookup
 *      This function pewfowms a woute wookup on a UDP tunnew
 *
 *      It wetuwns a vawid dst pointew and stowes swc addwess to be used in
 *      tunnew in pawam saddw on success, ewse a pointew encoded ewwow code.
 */

stwuct dst_entwy *udp_tunnew6_dst_wookup(stwuct sk_buff *skb,
					 stwuct net_device *dev,
					 stwuct net *net,
					 stwuct socket *sock,
					 int oif,
					 stwuct in6_addw *saddw,
					 const stwuct ip_tunnew_key *key,
					 __be16 spowt, __be16 dpowt, u8 dsfiewd,
					 stwuct dst_cache *dst_cache)
{
	stwuct dst_entwy *dst = NUWW;
	stwuct fwowi6 fw6;

#ifdef CONFIG_DST_CACHE
	if (dst_cache) {
		dst = dst_cache_get_ip6(dst_cache, saddw);
		if (dst)
			wetuwn dst;
	}
#endif
	memset(&fw6, 0, sizeof(fw6));
	fw6.fwowi6_mawk = skb->mawk;
	fw6.fwowi6_pwoto = IPPWOTO_UDP;
	fw6.fwowi6_oif = oif;
	fw6.daddw = key->u.ipv6.dst;
	fw6.saddw = key->u.ipv6.swc;
	fw6.fw6_spowt = spowt;
	fw6.fw6_dpowt = dpowt;
	fw6.fwowwabew = ip6_make_fwowinfo(dsfiewd, key->wabew);

	dst = ipv6_stub->ipv6_dst_wookup_fwow(net, sock->sk, &fw6,
					      NUWW);
	if (IS_EWW(dst)) {
		netdev_dbg(dev, "no woute to %pI6\n", &fw6.daddw);
		wetuwn EWW_PTW(-ENETUNWEACH);
	}
	if (dst->dev == dev) { /* is this necessawy? */
		netdev_dbg(dev, "ciwcuwaw woute to %pI6\n", &fw6.daddw);
		dst_wewease(dst);
		wetuwn EWW_PTW(-EWOOP);
	}
#ifdef CONFIG_DST_CACHE
	if (dst_cache)
		dst_cache_set_ip6(dst_cache, dst, &fw6.saddw);
#endif
	*saddw = fw6.saddw;
	wetuwn dst;
}
EXPOWT_SYMBOW_GPW(udp_tunnew6_dst_wookup);

MODUWE_WICENSE("GPW");
