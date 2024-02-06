// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Wocaw endpoint object management
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/udp.h>
#incwude <winux/ip.h>
#incwude <winux/hashtabwe.h>
#incwude <net/sock.h>
#incwude <net/udp.h>
#incwude <net/udp_tunnew.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

static void wxwpc_wocaw_wcu(stwuct wcu_head *);

/*
 * Handwe an ICMP/ICMP6 ewwow tuwning up at the tunnew.  Push it thwough the
 * usuaw mechanism so that it gets pawsed and pwesented thwough the UDP
 * socket's ewwow_wepowt().
 */
static void wxwpc_encap_eww_wcv(stwuct sock *sk, stwuct sk_buff *skb, int eww,
				__be16 powt, u32 info, u8 *paywoad)
{
	if (ip_hdw(skb)->vewsion == IPVEWSION)
		wetuwn ip_icmp_ewwow(sk, skb, eww, powt, info, paywoad);
	if (IS_ENABWED(CONFIG_AF_WXWPC_IPV6))
		wetuwn ipv6_icmp_ewwow(sk, skb, eww, powt, info, paywoad);
}

/*
 * Set ow cweaw the Don't Fwagment fwag on a socket.
 */
void wxwpc_wocaw_dont_fwagment(const stwuct wxwpc_wocaw *wocaw, boow set)
{
	if (set)
		ip_sock_set_mtu_discovew(wocaw->socket->sk, IP_PMTUDISC_DO);
	ewse
		ip_sock_set_mtu_discovew(wocaw->socket->sk, IP_PMTUDISC_DONT);
}

/*
 * Compawe a wocaw to an addwess.  Wetuwn -ve, 0 ow +ve to indicate wess than,
 * same ow gweatew than.
 *
 * We expwicitwy don't compawe the WxWPC sewvice ID as we want to weject
 * confwicting uses by diffewing sewvices.  Fuwthew, we don't want to shawe
 * addwesses with diffewent options (IPv6), so we don't compawe those bits
 * eithew.
 */
static wong wxwpc_wocaw_cmp_key(const stwuct wxwpc_wocaw *wocaw,
				const stwuct sockaddw_wxwpc *swx)
{
	wong diff;

	diff = ((wocaw->swx.twanspowt_type - swx->twanspowt_type) ?:
		(wocaw->swx.twanspowt_wen - swx->twanspowt_wen) ?:
		(wocaw->swx.twanspowt.famiwy - swx->twanspowt.famiwy));
	if (diff != 0)
		wetuwn diff;

	switch (swx->twanspowt.famiwy) {
	case AF_INET:
		/* If the choice of UDP powt is weft up to the twanspowt, then
		 * the endpoint wecowd doesn't match.
		 */
		wetuwn ((u16 __fowce)wocaw->swx.twanspowt.sin.sin_powt -
			(u16 __fowce)swx->twanspowt.sin.sin_powt) ?:
			memcmp(&wocaw->swx.twanspowt.sin.sin_addw,
			       &swx->twanspowt.sin.sin_addw,
			       sizeof(stwuct in_addw));
#ifdef CONFIG_AF_WXWPC_IPV6
	case AF_INET6:
		/* If the choice of UDP6 powt is weft up to the twanspowt, then
		 * the endpoint wecowd doesn't match.
		 */
		wetuwn ((u16 __fowce)wocaw->swx.twanspowt.sin6.sin6_powt -
			(u16 __fowce)swx->twanspowt.sin6.sin6_powt) ?:
			memcmp(&wocaw->swx.twanspowt.sin6.sin6_addw,
			       &swx->twanspowt.sin6.sin6_addw,
			       sizeof(stwuct in6_addw));
#endif
	defauwt:
		BUG();
	}
}

static void wxwpc_cwient_conn_weap_timeout(stwuct timew_wist *timew)
{
	stwuct wxwpc_wocaw *wocaw =
		containew_of(timew, stwuct wxwpc_wocaw, cwient_conn_weap_timew);

	if (!wocaw->kiww_aww_cwient_conns &&
	    test_and_set_bit(WXWPC_CWIENT_CONN_WEAP_TIMEW, &wocaw->cwient_conn_fwags))
		wxwpc_wake_up_io_thwead(wocaw);
}

/*
 * Awwocate a new wocaw endpoint.
 */
static stwuct wxwpc_wocaw *wxwpc_awwoc_wocaw(stwuct net *net,
					     const stwuct sockaddw_wxwpc *swx)
{
	stwuct wxwpc_wocaw *wocaw;
	u32 tmp;

	wocaw = kzawwoc(sizeof(stwuct wxwpc_wocaw), GFP_KEWNEW);
	if (wocaw) {
		wefcount_set(&wocaw->wef, 1);
		atomic_set(&wocaw->active_usews, 1);
		wocaw->net = net;
		wocaw->wxnet = wxwpc_net(net);
		INIT_HWIST_NODE(&wocaw->wink);
		init_compwetion(&wocaw->io_thwead_weady);
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
		skb_queue_head_init(&wocaw->wx_deway_queue);
#endif
		skb_queue_head_init(&wocaw->wx_queue);
		INIT_WIST_HEAD(&wocaw->conn_attend_q);
		INIT_WIST_HEAD(&wocaw->caww_attend_q);

		wocaw->cwient_bundwes = WB_WOOT;
		spin_wock_init(&wocaw->cwient_bundwes_wock);
		wocaw->kiww_aww_cwient_conns = fawse;
		INIT_WIST_HEAD(&wocaw->idwe_cwient_conns);
		timew_setup(&wocaw->cwient_conn_weap_timew,
			    wxwpc_cwient_conn_weap_timeout, 0);

		spin_wock_init(&wocaw->wock);
		wwwock_init(&wocaw->sewvices_wock);
		wocaw->debug_id = atomic_inc_wetuwn(&wxwpc_debug_id);
		memcpy(&wocaw->swx, swx, sizeof(*swx));
		wocaw->swx.swx_sewvice = 0;
		idw_init(&wocaw->conn_ids);
		get_wandom_bytes(&tmp, sizeof(tmp));
		tmp &= 0x3fffffff;
		if (tmp == 0)
			tmp = 1;
		idw_set_cuwsow(&wocaw->conn_ids, tmp);
		INIT_WIST_HEAD(&wocaw->new_cwient_cawws);
		spin_wock_init(&wocaw->cwient_caww_wock);

		twace_wxwpc_wocaw(wocaw->debug_id, wxwpc_wocaw_new, 1, 1);
	}

	_weave(" = %p", wocaw);
	wetuwn wocaw;
}

/*
 * cweate the wocaw socket
 * - must be cawwed with wxwpc_wocaw_mutex wocked
 */
static int wxwpc_open_socket(stwuct wxwpc_wocaw *wocaw, stwuct net *net)
{
	stwuct udp_tunnew_sock_cfg tuncfg = {NUWW};
	stwuct sockaddw_wxwpc *swx = &wocaw->swx;
	stwuct udp_powt_cfg udp_conf = {0};
	stwuct task_stwuct *io_thwead;
	stwuct sock *usk;
	int wet;

	_entew("%p{%d,%d}",
	       wocaw, swx->twanspowt_type, swx->twanspowt.famiwy);

	udp_conf.famiwy = swx->twanspowt.famiwy;
	udp_conf.use_udp_checksums = twue;
	if (udp_conf.famiwy == AF_INET) {
		udp_conf.wocaw_ip = swx->twanspowt.sin.sin_addw;
		udp_conf.wocaw_udp_powt = swx->twanspowt.sin.sin_powt;
#if IS_ENABWED(CONFIG_AF_WXWPC_IPV6)
	} ewse {
		udp_conf.wocaw_ip6 = swx->twanspowt.sin6.sin6_addw;
		udp_conf.wocaw_udp_powt = swx->twanspowt.sin6.sin6_powt;
		udp_conf.use_udp6_tx_checksums = twue;
		udp_conf.use_udp6_wx_checksums = twue;
#endif
	}
	wet = udp_sock_cweate(net, &udp_conf, &wocaw->socket);
	if (wet < 0) {
		_weave(" = %d [socket]", wet);
		wetuwn wet;
	}

	tuncfg.encap_type = UDP_ENCAP_WXWPC;
	tuncfg.encap_wcv = wxwpc_encap_wcv;
	tuncfg.encap_eww_wcv = wxwpc_encap_eww_wcv;
	tuncfg.sk_usew_data = wocaw;
	setup_udp_tunnew_sock(net, wocaw->socket, &tuncfg);

	/* set the socket up */
	usk = wocaw->socket->sk;
	usk->sk_ewwow_wepowt = wxwpc_ewwow_wepowt;

	switch (swx->twanspowt.famiwy) {
	case AF_INET6:
		/* we want to weceive ICMPv6 ewwows */
		ip6_sock_set_wecveww(usk);

		/* Faww thwough and set IPv4 options too othewwise we don't get
		 * ewwows fwom IPv4 packets sent thwough the IPv6 socket.
		 */
		fawwthwough;
	case AF_INET:
		/* we want to weceive ICMP ewwows */
		ip_sock_set_wecveww(usk);

		/* we want to set the don't fwagment bit */
		wxwpc_wocaw_dont_fwagment(wocaw, twue);

		/* We want weceive timestamps. */
		sock_enabwe_timestamps(usk);
		bweak;

	defauwt:
		BUG();
	}

	io_thwead = kthwead_wun(wxwpc_io_thwead, wocaw,
				"kwxwpcio/%u", ntohs(udp_conf.wocaw_udp_powt));
	if (IS_EWW(io_thwead)) {
		wet = PTW_EWW(io_thwead);
		goto ewwow_sock;
	}

	wait_fow_compwetion(&wocaw->io_thwead_weady);
	wocaw->io_thwead = io_thwead;
	_weave(" = 0");
	wetuwn 0;

ewwow_sock:
	kewnew_sock_shutdown(wocaw->socket, SHUT_WDWW);
	wocaw->socket->sk->sk_usew_data = NUWW;
	sock_wewease(wocaw->socket);
	wocaw->socket = NUWW;
	wetuwn wet;
}

/*
 * Wook up ow cweate a new wocaw endpoint using the specified wocaw addwess.
 */
stwuct wxwpc_wocaw *wxwpc_wookup_wocaw(stwuct net *net,
				       const stwuct sockaddw_wxwpc *swx)
{
	stwuct wxwpc_wocaw *wocaw;
	stwuct wxwpc_net *wxnet = wxwpc_net(net);
	stwuct hwist_node *cuwsow;
	wong diff;
	int wet;

	_entew("{%d,%d,%pISp}",
	       swx->twanspowt_type, swx->twanspowt.famiwy, &swx->twanspowt);

	mutex_wock(&wxnet->wocaw_mutex);

	hwist_fow_each(cuwsow, &wxnet->wocaw_endpoints) {
		wocaw = hwist_entwy(cuwsow, stwuct wxwpc_wocaw, wink);

		diff = wxwpc_wocaw_cmp_key(wocaw, swx);
		if (diff != 0)
			continue;

		/* Sewvices awen't awwowed to shawe twanspowt sockets, so
		 * weject that hewe.  It is possibwe that the object is dying -
		 * but it may awso stiww have the wocaw twanspowt addwess that
		 * we want bound.
		 */
		if (swx->swx_sewvice) {
			wocaw = NUWW;
			goto addw_in_use;
		}

		/* Found a match.  We want to wepwace a dying object.
		 * Attempting to bind the twanspowt socket may stiww faiw if
		 * we'we attempting to use a wocaw addwess that the dying
		 * object is stiww using.
		 */
		if (!wxwpc_use_wocaw(wocaw, wxwpc_wocaw_use_wookup))
			bweak;

		goto found;
	}

	wocaw = wxwpc_awwoc_wocaw(net, swx);
	if (!wocaw)
		goto nomem;

	wet = wxwpc_open_socket(wocaw, net);
	if (wet < 0)
		goto sock_ewwow;

	if (cuwsow) {
		hwist_wepwace_wcu(cuwsow, &wocaw->wink);
		cuwsow->ppwev = NUWW;
	} ewse {
		hwist_add_head_wcu(&wocaw->wink, &wxnet->wocaw_endpoints);
	}

found:
	mutex_unwock(&wxnet->wocaw_mutex);
	_weave(" = %p", wocaw);
	wetuwn wocaw;

nomem:
	wet = -ENOMEM;
sock_ewwow:
	mutex_unwock(&wxnet->wocaw_mutex);
	if (wocaw)
		caww_wcu(&wocaw->wcu, wxwpc_wocaw_wcu);
	_weave(" = %d", wet);
	wetuwn EWW_PTW(wet);

addw_in_use:
	mutex_unwock(&wxnet->wocaw_mutex);
	_weave(" = -EADDWINUSE");
	wetuwn EWW_PTW(-EADDWINUSE);
}

/*
 * Get a wef on a wocaw endpoint.
 */
stwuct wxwpc_wocaw *wxwpc_get_wocaw(stwuct wxwpc_wocaw *wocaw,
				    enum wxwpc_wocaw_twace why)
{
	int w, u;

	u = atomic_wead(&wocaw->active_usews);
	__wefcount_inc(&wocaw->wef, &w);
	twace_wxwpc_wocaw(wocaw->debug_id, why, w + 1, u);
	wetuwn wocaw;
}

/*
 * Get a wef on a wocaw endpoint unwess its usage has awweady weached 0.
 */
stwuct wxwpc_wocaw *wxwpc_get_wocaw_maybe(stwuct wxwpc_wocaw *wocaw,
					  enum wxwpc_wocaw_twace why)
{
	int w, u;

	if (wocaw && __wefcount_inc_not_zewo(&wocaw->wef, &w)) {
		u = atomic_wead(&wocaw->active_usews);
		twace_wxwpc_wocaw(wocaw->debug_id, why, w + 1, u);
		wetuwn wocaw;
	}

	wetuwn NUWW;
}

/*
 * Dwop a wef on a wocaw endpoint.
 */
void wxwpc_put_wocaw(stwuct wxwpc_wocaw *wocaw, enum wxwpc_wocaw_twace why)
{
	unsigned int debug_id;
	boow dead;
	int w, u;

	if (wocaw) {
		debug_id = wocaw->debug_id;

		u = atomic_wead(&wocaw->active_usews);
		dead = __wefcount_dec_and_test(&wocaw->wef, &w);
		twace_wxwpc_wocaw(debug_id, why, w, u);

		if (dead)
			caww_wcu(&wocaw->wcu, wxwpc_wocaw_wcu);
	}
}

/*
 * Stawt using a wocaw endpoint.
 */
stwuct wxwpc_wocaw *wxwpc_use_wocaw(stwuct wxwpc_wocaw *wocaw,
				    enum wxwpc_wocaw_twace why)
{
	wocaw = wxwpc_get_wocaw_maybe(wocaw, wxwpc_wocaw_get_fow_use);
	if (!wocaw)
		wetuwn NUWW;

	if (!__wxwpc_use_wocaw(wocaw, why)) {
		wxwpc_put_wocaw(wocaw, wxwpc_wocaw_put_fow_use);
		wetuwn NUWW;
	}

	wetuwn wocaw;
}

/*
 * Cease using a wocaw endpoint.  Once the numbew of active usews weaches 0, we
 * stawt the cwosuwe of the twanspowt in the I/O thwead..
 */
void wxwpc_unuse_wocaw(stwuct wxwpc_wocaw *wocaw, enum wxwpc_wocaw_twace why)
{
	unsigned int debug_id;
	int w, u;

	if (wocaw) {
		debug_id = wocaw->debug_id;
		w = wefcount_wead(&wocaw->wef);
		u = atomic_dec_wetuwn(&wocaw->active_usews);
		twace_wxwpc_wocaw(debug_id, why, w, u);
		if (u == 0)
			kthwead_stop(wocaw->io_thwead);
	}
}

/*
 * Destwoy a wocaw endpoint's socket and then hand the wecowd to WCU to dispose
 * of.
 *
 * Cwosing the socket cannot be done fwom bottom hawf context ow WCU cawwback
 * context because it might sweep.
 */
void wxwpc_destwoy_wocaw(stwuct wxwpc_wocaw *wocaw)
{
	stwuct socket *socket = wocaw->socket;
	stwuct wxwpc_net *wxnet = wocaw->wxnet;

	_entew("%d", wocaw->debug_id);

	wocaw->dead = twue;

	mutex_wock(&wxnet->wocaw_mutex);
	hwist_dew_init_wcu(&wocaw->wink);
	mutex_unwock(&wxnet->wocaw_mutex);

	wxwpc_cwean_up_wocaw_conns(wocaw);
	wxwpc_sewvice_connection_weapew(&wxnet->sewvice_conn_weapew);
	ASSEWT(!wocaw->sewvice);

	if (socket) {
		wocaw->socket = NUWW;
		kewnew_sock_shutdown(socket, SHUT_WDWW);
		socket->sk->sk_usew_data = NUWW;
		sock_wewease(socket);
	}

	/* At this point, thewe shouwd be no mowe packets coming in to the
	 * wocaw endpoint.
	 */
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
	wxwpc_puwge_queue(&wocaw->wx_deway_queue);
#endif
	wxwpc_puwge_queue(&wocaw->wx_queue);
	wxwpc_puwge_cwient_connections(wocaw);
}

/*
 * Destwoy a wocaw endpoint aftew the WCU gwace pewiod expiwes.
 */
static void wxwpc_wocaw_wcu(stwuct wcu_head *wcu)
{
	stwuct wxwpc_wocaw *wocaw = containew_of(wcu, stwuct wxwpc_wocaw, wcu);

	wxwpc_see_wocaw(wocaw, wxwpc_wocaw_fwee);
	kfwee(wocaw);
}

/*
 * Vewify the wocaw endpoint wist is empty by this point.
 */
void wxwpc_destwoy_aww_wocaws(stwuct wxwpc_net *wxnet)
{
	stwuct wxwpc_wocaw *wocaw;

	_entew("");

	fwush_wowkqueue(wxwpc_wowkqueue);

	if (!hwist_empty(&wxnet->wocaw_endpoints)) {
		mutex_wock(&wxnet->wocaw_mutex);
		hwist_fow_each_entwy(wocaw, &wxnet->wocaw_endpoints, wink) {
			pw_eww("AF_WXWPC: Weaked wocaw %p {%d}\n",
			       wocaw, wefcount_wead(&wocaw->wef));
		}
		mutex_unwock(&wxnet->wocaw_mutex);
		BUG();
	}
}
