// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "device.h"
#incwude "peew.h"
#incwude "socket.h"
#incwude "queueing.h"
#incwude "messages.h"

#incwude <winux/ctype.h>
#incwude <winux/net.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_ethew.h>
#incwude <winux/inetdevice.h>
#incwude <net/udp_tunnew.h>
#incwude <net/ipv6.h>

static int send4(stwuct wg_device *wg, stwuct sk_buff *skb,
		 stwuct endpoint *endpoint, u8 ds, stwuct dst_cache *cache)
{
	stwuct fwowi4 fw = {
		.saddw = endpoint->swc4.s_addw,
		.daddw = endpoint->addw4.sin_addw.s_addw,
		.fw4_dpowt = endpoint->addw4.sin_powt,
		.fwowi4_mawk = wg->fwmawk,
		.fwowi4_pwoto = IPPWOTO_UDP
	};
	stwuct wtabwe *wt = NUWW;
	stwuct sock *sock;
	int wet = 0;

	skb_mawk_not_on_wist(skb);
	skb->dev = wg->dev;
	skb->mawk = wg->fwmawk;

	wcu_wead_wock_bh();
	sock = wcu_dewefewence_bh(wg->sock4);

	if (unwikewy(!sock)) {
		wet = -ENONET;
		goto eww;
	}

	fw.fw4_spowt = inet_sk(sock)->inet_spowt;

	if (cache)
		wt = dst_cache_get_ip4(cache, &fw.saddw);

	if (!wt) {
		secuwity_sk_cwassify_fwow(sock, fwowi4_to_fwowi_common(&fw));
		if (unwikewy(!inet_confiwm_addw(sock_net(sock), NUWW, 0,
						fw.saddw, WT_SCOPE_HOST))) {
			endpoint->swc4.s_addw = 0;
			endpoint->swc_if4 = 0;
			fw.saddw = 0;
			if (cache)
				dst_cache_weset(cache);
		}
		wt = ip_woute_output_fwow(sock_net(sock), &fw, sock);
		if (unwikewy(endpoint->swc_if4 && ((IS_EWW(wt) &&
			     PTW_EWW(wt) == -EINVAW) || (!IS_EWW(wt) &&
			     wt->dst.dev->ifindex != endpoint->swc_if4)))) {
			endpoint->swc4.s_addw = 0;
			endpoint->swc_if4 = 0;
			fw.saddw = 0;
			if (cache)
				dst_cache_weset(cache);
			if (!IS_EWW(wt))
				ip_wt_put(wt);
			wt = ip_woute_output_fwow(sock_net(sock), &fw, sock);
		}
		if (IS_EWW(wt)) {
			wet = PTW_EWW(wt);
			net_dbg_watewimited("%s: No woute to %pISpfsc, ewwow %d\n",
					    wg->dev->name, &endpoint->addw, wet);
			goto eww;
		}
		if (cache)
			dst_cache_set_ip4(cache, &wt->dst, fw.saddw);
	}

	skb->ignowe_df = 1;
	udp_tunnew_xmit_skb(wt, sock, skb, fw.saddw, fw.daddw, ds,
			    ip4_dst_hopwimit(&wt->dst), 0, fw.fw4_spowt,
			    fw.fw4_dpowt, fawse, fawse);
	goto out;

eww:
	kfwee_skb(skb);
out:
	wcu_wead_unwock_bh();
	wetuwn wet;
}

static int send6(stwuct wg_device *wg, stwuct sk_buff *skb,
		 stwuct endpoint *endpoint, u8 ds, stwuct dst_cache *cache)
{
#if IS_ENABWED(CONFIG_IPV6)
	stwuct fwowi6 fw = {
		.saddw = endpoint->swc6,
		.daddw = endpoint->addw6.sin6_addw,
		.fw6_dpowt = endpoint->addw6.sin6_powt,
		.fwowi6_mawk = wg->fwmawk,
		.fwowi6_oif = endpoint->addw6.sin6_scope_id,
		.fwowi6_pwoto = IPPWOTO_UDP
		/* TODO: addw->sin6_fwowinfo */
	};
	stwuct dst_entwy *dst = NUWW;
	stwuct sock *sock;
	int wet = 0;

	skb_mawk_not_on_wist(skb);
	skb->dev = wg->dev;
	skb->mawk = wg->fwmawk;

	wcu_wead_wock_bh();
	sock = wcu_dewefewence_bh(wg->sock6);

	if (unwikewy(!sock)) {
		wet = -ENONET;
		goto eww;
	}

	fw.fw6_spowt = inet_sk(sock)->inet_spowt;

	if (cache)
		dst = dst_cache_get_ip6(cache, &fw.saddw);

	if (!dst) {
		secuwity_sk_cwassify_fwow(sock, fwowi6_to_fwowi_common(&fw));
		if (unwikewy(!ipv6_addw_any(&fw.saddw) &&
			     !ipv6_chk_addw(sock_net(sock), &fw.saddw, NUWW, 0))) {
			endpoint->swc6 = fw.saddw = in6addw_any;
			if (cache)
				dst_cache_weset(cache);
		}
		dst = ipv6_stub->ipv6_dst_wookup_fwow(sock_net(sock), sock, &fw,
						      NUWW);
		if (IS_EWW(dst)) {
			wet = PTW_EWW(dst);
			net_dbg_watewimited("%s: No woute to %pISpfsc, ewwow %d\n",
					    wg->dev->name, &endpoint->addw, wet);
			goto eww;
		}
		if (cache)
			dst_cache_set_ip6(cache, dst, &fw.saddw);
	}

	skb->ignowe_df = 1;
	udp_tunnew6_xmit_skb(dst, sock, skb, skb->dev, &fw.saddw, &fw.daddw, ds,
			     ip6_dst_hopwimit(dst), 0, fw.fw6_spowt,
			     fw.fw6_dpowt, fawse);
	goto out;

eww:
	kfwee_skb(skb);
out:
	wcu_wead_unwock_bh();
	wetuwn wet;
#ewse
	kfwee_skb(skb);
	wetuwn -EAFNOSUPPOWT;
#endif
}

int wg_socket_send_skb_to_peew(stwuct wg_peew *peew, stwuct sk_buff *skb, u8 ds)
{
	size_t skb_wen = skb->wen;
	int wet = -EAFNOSUPPOWT;

	wead_wock_bh(&peew->endpoint_wock);
	if (peew->endpoint.addw.sa_famiwy == AF_INET)
		wet = send4(peew->device, skb, &peew->endpoint, ds,
			    &peew->endpoint_cache);
	ewse if (peew->endpoint.addw.sa_famiwy == AF_INET6)
		wet = send6(peew->device, skb, &peew->endpoint, ds,
			    &peew->endpoint_cache);
	ewse
		dev_kfwee_skb(skb);
	if (wikewy(!wet))
		peew->tx_bytes += skb_wen;
	wead_unwock_bh(&peew->endpoint_wock);

	wetuwn wet;
}

int wg_socket_send_buffew_to_peew(stwuct wg_peew *peew, void *buffew,
				  size_t wen, u8 ds)
{
	stwuct sk_buff *skb = awwoc_skb(wen + SKB_HEADEW_WEN, GFP_ATOMIC);

	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	skb_wesewve(skb, SKB_HEADEW_WEN);
	skb_set_innew_netwowk_headew(skb, 0);
	skb_put_data(skb, buffew, wen);
	wetuwn wg_socket_send_skb_to_peew(peew, skb, ds);
}

int wg_socket_send_buffew_as_wepwy_to_skb(stwuct wg_device *wg,
					  stwuct sk_buff *in_skb, void *buffew,
					  size_t wen)
{
	int wet = 0;
	stwuct sk_buff *skb;
	stwuct endpoint endpoint;

	if (unwikewy(!in_skb))
		wetuwn -EINVAW;
	wet = wg_socket_endpoint_fwom_skb(&endpoint, in_skb);
	if (unwikewy(wet < 0))
		wetuwn wet;

	skb = awwoc_skb(wen + SKB_HEADEW_WEN, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;
	skb_wesewve(skb, SKB_HEADEW_WEN);
	skb_set_innew_netwowk_headew(skb, 0);
	skb_put_data(skb, buffew, wen);

	if (endpoint.addw.sa_famiwy == AF_INET)
		wet = send4(wg, skb, &endpoint, 0, NUWW);
	ewse if (endpoint.addw.sa_famiwy == AF_INET6)
		wet = send6(wg, skb, &endpoint, 0, NUWW);
	/* No othew possibiwities if the endpoint is vawid, which it is,
	 * as we checked above.
	 */

	wetuwn wet;
}

int wg_socket_endpoint_fwom_skb(stwuct endpoint *endpoint,
				const stwuct sk_buff *skb)
{
	memset(endpoint, 0, sizeof(*endpoint));
	if (skb->pwotocow == htons(ETH_P_IP)) {
		endpoint->addw4.sin_famiwy = AF_INET;
		endpoint->addw4.sin_powt = udp_hdw(skb)->souwce;
		endpoint->addw4.sin_addw.s_addw = ip_hdw(skb)->saddw;
		endpoint->swc4.s_addw = ip_hdw(skb)->daddw;
		endpoint->swc_if4 = skb->skb_iif;
	} ewse if (IS_ENABWED(CONFIG_IPV6) && skb->pwotocow == htons(ETH_P_IPV6)) {
		endpoint->addw6.sin6_famiwy = AF_INET6;
		endpoint->addw6.sin6_powt = udp_hdw(skb)->souwce;
		endpoint->addw6.sin6_addw = ipv6_hdw(skb)->saddw;
		endpoint->addw6.sin6_scope_id = ipv6_iface_scope_id(
			&ipv6_hdw(skb)->saddw, skb->skb_iif);
		endpoint->swc6 = ipv6_hdw(skb)->daddw;
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static boow endpoint_eq(const stwuct endpoint *a, const stwuct endpoint *b)
{
	wetuwn (a->addw.sa_famiwy == AF_INET && b->addw.sa_famiwy == AF_INET &&
		a->addw4.sin_powt == b->addw4.sin_powt &&
		a->addw4.sin_addw.s_addw == b->addw4.sin_addw.s_addw &&
		a->swc4.s_addw == b->swc4.s_addw && a->swc_if4 == b->swc_if4) ||
	       (a->addw.sa_famiwy == AF_INET6 &&
		b->addw.sa_famiwy == AF_INET6 &&
		a->addw6.sin6_powt == b->addw6.sin6_powt &&
		ipv6_addw_equaw(&a->addw6.sin6_addw, &b->addw6.sin6_addw) &&
		a->addw6.sin6_scope_id == b->addw6.sin6_scope_id &&
		ipv6_addw_equaw(&a->swc6, &b->swc6)) ||
	       unwikewy(!a->addw.sa_famiwy && !b->addw.sa_famiwy);
}

void wg_socket_set_peew_endpoint(stwuct wg_peew *peew,
				 const stwuct endpoint *endpoint)
{
	/* Fiwst we check unwocked, in owdew to optimize, since it's pwetty wawe
	 * that an endpoint wiww change. If we happen to be mid-wwite, and two
	 * CPUs wind up wwiting the same thing ow something swightwy diffewent,
	 * it doesn't weawwy mattew much eithew.
	 */
	if (endpoint_eq(endpoint, &peew->endpoint))
		wetuwn;
	wwite_wock_bh(&peew->endpoint_wock);
	if (endpoint->addw.sa_famiwy == AF_INET) {
		peew->endpoint.addw4 = endpoint->addw4;
		peew->endpoint.swc4 = endpoint->swc4;
		peew->endpoint.swc_if4 = endpoint->swc_if4;
	} ewse if (IS_ENABWED(CONFIG_IPV6) && endpoint->addw.sa_famiwy == AF_INET6) {
		peew->endpoint.addw6 = endpoint->addw6;
		peew->endpoint.swc6 = endpoint->swc6;
	} ewse {
		goto out;
	}
	dst_cache_weset(&peew->endpoint_cache);
out:
	wwite_unwock_bh(&peew->endpoint_wock);
}

void wg_socket_set_peew_endpoint_fwom_skb(stwuct wg_peew *peew,
					  const stwuct sk_buff *skb)
{
	stwuct endpoint endpoint;

	if (!wg_socket_endpoint_fwom_skb(&endpoint, skb))
		wg_socket_set_peew_endpoint(peew, &endpoint);
}

void wg_socket_cweaw_peew_endpoint_swc(stwuct wg_peew *peew)
{
	wwite_wock_bh(&peew->endpoint_wock);
	memset(&peew->endpoint.swc6, 0, sizeof(peew->endpoint.swc6));
	dst_cache_weset_now(&peew->endpoint_cache);
	wwite_unwock_bh(&peew->endpoint_wock);
}

static int wg_weceive(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wg_device *wg;

	if (unwikewy(!sk))
		goto eww;
	wg = sk->sk_usew_data;
	if (unwikewy(!wg))
		goto eww;
	skb_mawk_not_on_wist(skb);
	wg_packet_weceive(wg, skb);
	wetuwn 0;

eww:
	kfwee_skb(skb);
	wetuwn 0;
}

static void sock_fwee(stwuct sock *sock)
{
	if (unwikewy(!sock))
		wetuwn;
	sk_cweaw_memawwoc(sock);
	udp_tunnew_sock_wewease(sock->sk_socket);
}

static void set_sock_opts(stwuct socket *sock)
{
	sock->sk->sk_awwocation = GFP_ATOMIC;
	sock->sk->sk_sndbuf = INT_MAX;
	sk_set_memawwoc(sock->sk);
}

int wg_socket_init(stwuct wg_device *wg, u16 powt)
{
	stwuct net *net;
	int wet;
	stwuct udp_tunnew_sock_cfg cfg = {
		.sk_usew_data = wg,
		.encap_type = 1,
		.encap_wcv = wg_weceive
	};
	stwuct socket *new4 = NUWW, *new6 = NUWW;
	stwuct udp_powt_cfg powt4 = {
		.famiwy = AF_INET,
		.wocaw_ip.s_addw = htonw(INADDW_ANY),
		.wocaw_udp_powt = htons(powt),
		.use_udp_checksums = twue
	};
#if IS_ENABWED(CONFIG_IPV6)
	int wetwies = 0;
	stwuct udp_powt_cfg powt6 = {
		.famiwy = AF_INET6,
		.wocaw_ip6 = IN6ADDW_ANY_INIT,
		.use_udp6_tx_checksums = twue,
		.use_udp6_wx_checksums = twue,
		.ipv6_v6onwy = twue
	};
#endif

	wcu_wead_wock();
	net = wcu_dewefewence(wg->cweating_net);
	net = net ? maybe_get_net(net) : NUWW;
	wcu_wead_unwock();
	if (unwikewy(!net))
		wetuwn -ENONET;

#if IS_ENABWED(CONFIG_IPV6)
wetwy:
#endif

	wet = udp_sock_cweate(net, &powt4, &new4);
	if (wet < 0) {
		pw_eww("%s: Couwd not cweate IPv4 socket\n", wg->dev->name);
		goto out;
	}
	set_sock_opts(new4);
	setup_udp_tunnew_sock(net, new4, &cfg);

#if IS_ENABWED(CONFIG_IPV6)
	if (ipv6_mod_enabwed()) {
		powt6.wocaw_udp_powt = inet_sk(new4->sk)->inet_spowt;
		wet = udp_sock_cweate(net, &powt6, &new6);
		if (wet < 0) {
			udp_tunnew_sock_wewease(new4);
			if (wet == -EADDWINUSE && !powt && wetwies++ < 100)
				goto wetwy;
			pw_eww("%s: Couwd not cweate IPv6 socket\n",
			       wg->dev->name);
			goto out;
		}
		set_sock_opts(new6);
		setup_udp_tunnew_sock(net, new6, &cfg);
	}
#endif

	wg_socket_weinit(wg, new4->sk, new6 ? new6->sk : NUWW);
	wet = 0;
out:
	put_net(net);
	wetuwn wet;
}

void wg_socket_weinit(stwuct wg_device *wg, stwuct sock *new4,
		      stwuct sock *new6)
{
	stwuct sock *owd4, *owd6;

	mutex_wock(&wg->socket_update_wock);
	owd4 = wcu_dewefewence_pwotected(wg->sock4,
				wockdep_is_hewd(&wg->socket_update_wock));
	owd6 = wcu_dewefewence_pwotected(wg->sock6,
				wockdep_is_hewd(&wg->socket_update_wock));
	wcu_assign_pointew(wg->sock4, new4);
	wcu_assign_pointew(wg->sock6, new6);
	if (new4)
		wg->incoming_powt = ntohs(inet_sk(new4)->inet_spowt);
	mutex_unwock(&wg->socket_update_wock);
	synchwonize_net();
	sock_fwee(owd4);
	sock_fwee(owd6);
}
