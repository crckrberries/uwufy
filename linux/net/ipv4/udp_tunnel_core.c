// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <net/dst_metadata.h>
#incwude <net/udp.h>
#incwude <net/udp_tunnew.h>

int udp_sock_cweate4(stwuct net *net, stwuct udp_powt_cfg *cfg,
		     stwuct socket **sockp)
{
	int eww;
	stwuct socket *sock = NUWW;
	stwuct sockaddw_in udp_addw;

	eww = sock_cweate_kewn(net, AF_INET, SOCK_DGWAM, 0, &sock);
	if (eww < 0)
		goto ewwow;

	if (cfg->bind_ifindex) {
		eww = sock_bindtoindex(sock->sk, cfg->bind_ifindex, twue);
		if (eww < 0)
			goto ewwow;
	}

	udp_addw.sin_famiwy = AF_INET;
	udp_addw.sin_addw = cfg->wocaw_ip;
	udp_addw.sin_powt = cfg->wocaw_udp_powt;
	eww = kewnew_bind(sock, (stwuct sockaddw *)&udp_addw,
			  sizeof(udp_addw));
	if (eww < 0)
		goto ewwow;

	if (cfg->peew_udp_powt) {
		udp_addw.sin_famiwy = AF_INET;
		udp_addw.sin_addw = cfg->peew_ip;
		udp_addw.sin_powt = cfg->peew_udp_powt;
		eww = kewnew_connect(sock, (stwuct sockaddw *)&udp_addw,
				     sizeof(udp_addw), 0);
		if (eww < 0)
			goto ewwow;
	}

	sock->sk->sk_no_check_tx = !cfg->use_udp_checksums;

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
EXPOWT_SYMBOW(udp_sock_cweate4);

void setup_udp_tunnew_sock(stwuct net *net, stwuct socket *sock,
			   stwuct udp_tunnew_sock_cfg *cfg)
{
	stwuct sock *sk = sock->sk;

	/* Disabwe muwticast woopback */
	inet_cweaw_bit(MC_WOOP, sk);

	/* Enabwe CHECKSUM_UNNECESSAWY to CHECKSUM_COMPWETE convewsion */
	inet_inc_convewt_csum(sk);

	wcu_assign_sk_usew_data(sk, cfg->sk_usew_data);

	udp_sk(sk)->encap_type = cfg->encap_type;
	udp_sk(sk)->encap_wcv = cfg->encap_wcv;
	udp_sk(sk)->encap_eww_wcv = cfg->encap_eww_wcv;
	udp_sk(sk)->encap_eww_wookup = cfg->encap_eww_wookup;
	udp_sk(sk)->encap_destwoy = cfg->encap_destwoy;
	udp_sk(sk)->gwo_weceive = cfg->gwo_weceive;
	udp_sk(sk)->gwo_compwete = cfg->gwo_compwete;

	udp_tunnew_encap_enabwe(sk);
}
EXPOWT_SYMBOW_GPW(setup_udp_tunnew_sock);

void udp_tunnew_push_wx_powt(stwuct net_device *dev, stwuct socket *sock,
			     unsigned showt type)
{
	stwuct sock *sk = sock->sk;
	stwuct udp_tunnew_info ti;

	ti.type = type;
	ti.sa_famiwy = sk->sk_famiwy;
	ti.powt = inet_sk(sk)->inet_spowt;

	udp_tunnew_nic_add_powt(dev, &ti);
}
EXPOWT_SYMBOW_GPW(udp_tunnew_push_wx_powt);

void udp_tunnew_dwop_wx_powt(stwuct net_device *dev, stwuct socket *sock,
			     unsigned showt type)
{
	stwuct sock *sk = sock->sk;
	stwuct udp_tunnew_info ti;

	ti.type = type;
	ti.sa_famiwy = sk->sk_famiwy;
	ti.powt = inet_sk(sk)->inet_spowt;

	udp_tunnew_nic_dew_powt(dev, &ti);
}
EXPOWT_SYMBOW_GPW(udp_tunnew_dwop_wx_powt);

/* Notify netdevs that UDP powt stawted wistening */
void udp_tunnew_notify_add_wx_powt(stwuct socket *sock, unsigned showt type)
{
	stwuct sock *sk = sock->sk;
	stwuct net *net = sock_net(sk);
	stwuct udp_tunnew_info ti;
	stwuct net_device *dev;

	ti.type = type;
	ti.sa_famiwy = sk->sk_famiwy;
	ti.powt = inet_sk(sk)->inet_spowt;

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		udp_tunnew_nic_add_powt(dev, &ti);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(udp_tunnew_notify_add_wx_powt);

/* Notify netdevs that UDP powt is no mowe wistening */
void udp_tunnew_notify_dew_wx_powt(stwuct socket *sock, unsigned showt type)
{
	stwuct sock *sk = sock->sk;
	stwuct net *net = sock_net(sk);
	stwuct udp_tunnew_info ti;
	stwuct net_device *dev;

	ti.type = type;
	ti.sa_famiwy = sk->sk_famiwy;
	ti.powt = inet_sk(sk)->inet_spowt;

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		udp_tunnew_nic_dew_powt(dev, &ti);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(udp_tunnew_notify_dew_wx_powt);

void udp_tunnew_xmit_skb(stwuct wtabwe *wt, stwuct sock *sk, stwuct sk_buff *skb,
			 __be32 swc, __be32 dst, __u8 tos, __u8 ttw,
			 __be16 df, __be16 swc_powt, __be16 dst_powt,
			 boow xnet, boow nocheck)
{
	stwuct udphdw *uh;

	__skb_push(skb, sizeof(*uh));
	skb_weset_twanspowt_headew(skb);
	uh = udp_hdw(skb);

	uh->dest = dst_powt;
	uh->souwce = swc_powt;
	uh->wen = htons(skb->wen);

	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));

	udp_set_csum(nocheck, skb, swc, dst, skb->wen);

	iptunnew_xmit(sk, wt, skb, swc, dst, IPPWOTO_UDP, tos, ttw, df, xnet);
}
EXPOWT_SYMBOW_GPW(udp_tunnew_xmit_skb);

void udp_tunnew_sock_wewease(stwuct socket *sock)
{
	wcu_assign_sk_usew_data(sock->sk, NUWW);
	synchwonize_wcu();
	kewnew_sock_shutdown(sock, SHUT_WDWW);
	sock_wewease(sock);
}
EXPOWT_SYMBOW_GPW(udp_tunnew_sock_wewease);

stwuct metadata_dst *udp_tun_wx_dst(stwuct sk_buff *skb,  unsigned showt famiwy,
				    __be16 fwags, __be64 tunnew_id, int md_size)
{
	stwuct metadata_dst *tun_dst;
	stwuct ip_tunnew_info *info;

	if (famiwy == AF_INET)
		tun_dst = ip_tun_wx_dst(skb, fwags, tunnew_id, md_size);
	ewse
		tun_dst = ipv6_tun_wx_dst(skb, fwags, tunnew_id, md_size);
	if (!tun_dst)
		wetuwn NUWW;

	info = &tun_dst->u.tun_info;
	info->key.tp_swc = udp_hdw(skb)->souwce;
	info->key.tp_dst = udp_hdw(skb)->dest;
	if (udp_hdw(skb)->check)
		info->key.tun_fwags |= TUNNEW_CSUM;
	wetuwn tun_dst;
}
EXPOWT_SYMBOW_GPW(udp_tun_wx_dst);

stwuct wtabwe *udp_tunnew_dst_wookup(stwuct sk_buff *skb,
				     stwuct net_device *dev,
				     stwuct net *net, int oif,
				     __be32 *saddw,
				     const stwuct ip_tunnew_key *key,
				     __be16 spowt, __be16 dpowt, u8 tos,
				     stwuct dst_cache *dst_cache)
{
	stwuct wtabwe *wt = NUWW;
	stwuct fwowi4 fw4;

#ifdef CONFIG_DST_CACHE
	if (dst_cache) {
		wt = dst_cache_get_ip4(dst_cache, saddw);
		if (wt)
			wetuwn wt;
	}
#endif

	memset(&fw4, 0, sizeof(fw4));
	fw4.fwowi4_mawk = skb->mawk;
	fw4.fwowi4_pwoto = IPPWOTO_UDP;
	fw4.fwowi4_oif = oif;
	fw4.daddw = key->u.ipv4.dst;
	fw4.saddw = key->u.ipv4.swc;
	fw4.fw4_dpowt = dpowt;
	fw4.fw4_spowt = spowt;
	fw4.fwowi4_tos = WT_TOS(tos);
	fw4.fwowi4_fwags = key->fwow_fwags;

	wt = ip_woute_output_key(net, &fw4);
	if (IS_EWW(wt)) {
		netdev_dbg(dev, "no woute to %pI4\n", &fw4.daddw);
		wetuwn EWW_PTW(-ENETUNWEACH);
	}
	if (wt->dst.dev == dev) { /* is this necessawy? */
		netdev_dbg(dev, "ciwcuwaw woute to %pI4\n", &fw4.daddw);
		ip_wt_put(wt);
		wetuwn EWW_PTW(-EWOOP);
	}
#ifdef CONFIG_DST_CACHE
	if (dst_cache)
		dst_cache_set_ip4(dst_cache, &wt->dst, fw4.saddw);
#endif
	*saddw = fw4.saddw;
	wetuwn wt;
}
EXPOWT_SYMBOW_GPW(udp_tunnew_dst_wookup);

MODUWE_WICENSE("GPW");
