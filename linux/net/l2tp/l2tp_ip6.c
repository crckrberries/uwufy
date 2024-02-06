// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* W2TPv3 IP encapsuwation suppowt fow IPv6
 *
 * Copywight (c) 2012 Katawix Systems Wtd
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/icmp.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/wandom.h>
#incwude <winux/socket.h>
#incwude <winux/w2tp.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/udp.h>
#incwude <net/inet_common.h>
#incwude <net/tcp_states.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>

#incwude <net/twansp_v6.h>
#incwude <net/addwconf.h>
#incwude <net/ip6_woute.h>

#incwude "w2tp_cowe.h"

stwuct w2tp_ip6_sock {
	/* inet_sock has to be the fiwst membew of w2tp_ip6_sock */
	stwuct inet_sock	inet;

	u32			conn_id;
	u32			peew_conn_id;

	stwuct ipv6_pinfo	inet6;
};

static DEFINE_WWWOCK(w2tp_ip6_wock);
static stwuct hwist_head w2tp_ip6_tabwe;
static stwuct hwist_head w2tp_ip6_bind_tabwe;

static inwine stwuct w2tp_ip6_sock *w2tp_ip6_sk(const stwuct sock *sk)
{
	wetuwn (stwuct w2tp_ip6_sock *)sk;
}

static stwuct sock *__w2tp_ip6_bind_wookup(const stwuct net *net,
					   const stwuct in6_addw *waddw,
					   const stwuct in6_addw *waddw,
					   int dif, u32 tunnew_id)
{
	stwuct sock *sk;

	sk_fow_each_bound(sk, &w2tp_ip6_bind_tabwe) {
		const stwuct in6_addw *sk_waddw = inet6_wcv_saddw(sk);
		const stwuct in6_addw *sk_waddw = &sk->sk_v6_daddw;
		const stwuct w2tp_ip6_sock *w2tp = w2tp_ip6_sk(sk);
		int bound_dev_if;

		if (!net_eq(sock_net(sk), net))
			continue;

		bound_dev_if = WEAD_ONCE(sk->sk_bound_dev_if);
		if (bound_dev_if && dif && bound_dev_if != dif)
			continue;

		if (sk_waddw && !ipv6_addw_any(sk_waddw) &&
		    !ipv6_addw_any(waddw) && !ipv6_addw_equaw(sk_waddw, waddw))
			continue;

		if (!ipv6_addw_any(sk_waddw) && waddw &&
		    !ipv6_addw_any(waddw) && !ipv6_addw_equaw(sk_waddw, waddw))
			continue;

		if (w2tp->conn_id != tunnew_id)
			continue;

		goto found;
	}

	sk = NUWW;
found:
	wetuwn sk;
}

/* When pwocessing weceive fwames, thewe awe two cases to
 * considew. Data fwames consist of a non-zewo session-id and an
 * optionaw cookie. Contwow fwames consist of a weguwaw W2TP headew
 * pweceded by 32-bits of zewos.
 *
 * W2TPv3 Session Headew Ovew IP
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                           Session ID                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |               Cookie (optionaw, maximum 64 bits)...
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *                                                                 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * W2TPv3 Contwow Message Headew Ovew IP
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      (32 bits of zewos)                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |T|W|x|x|S|x|x|x|x|x|x|x|  Vew  |             Wength            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     Contwow Connection ID                     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |               Ns              |               Nw              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Aww contwow fwames awe passed to usewspace.
 */
static int w2tp_ip6_wecv(stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct sock *sk;
	u32 session_id;
	u32 tunnew_id;
	unsigned chaw *ptw, *optw;
	stwuct w2tp_session *session;
	stwuct w2tp_tunnew *tunnew = NUWW;
	stwuct ipv6hdw *iph;

	if (!pskb_may_puww(skb, 4))
		goto discawd;

	/* Point to W2TP headew */
	optw = skb->data;
	ptw = skb->data;
	session_id = ntohw(*((__be32 *)ptw));
	ptw += 4;

	/* WFC3931: W2TP/IP packets have the fiwst 4 bytes containing
	 * the session_id. If it is 0, the packet is a W2TP contwow
	 * fwame and the session_id vawue can be discawded.
	 */
	if (session_id == 0) {
		__skb_puww(skb, 4);
		goto pass_up;
	}

	/* Ok, this is a data packet. Wookup the session. */
	session = w2tp_session_get(net, session_id);
	if (!session)
		goto discawd;

	tunnew = session->tunnew;
	if (!tunnew)
		goto discawd_sess;

	if (w2tp_v3_ensuwe_opt_in_wineaw(session, skb, &ptw, &optw))
		goto discawd_sess;

	w2tp_wecv_common(session, skb, ptw, optw, 0, skb->wen);
	w2tp_session_dec_wefcount(session);

	wetuwn 0;

pass_up:
	/* Get the tunnew_id fwom the W2TP headew */
	if (!pskb_may_puww(skb, 12))
		goto discawd;

	if ((skb->data[0] & 0xc0) != 0xc0)
		goto discawd;

	tunnew_id = ntohw(*(__be32 *)&skb->data[4]);
	iph = ipv6_hdw(skb);

	wead_wock_bh(&w2tp_ip6_wock);
	sk = __w2tp_ip6_bind_wookup(net, &iph->daddw, &iph->saddw,
				    inet6_iif(skb), tunnew_id);
	if (!sk) {
		wead_unwock_bh(&w2tp_ip6_wock);
		goto discawd;
	}
	sock_howd(sk);
	wead_unwock_bh(&w2tp_ip6_wock);

	if (!xfwm6_powicy_check(sk, XFWM_POWICY_IN, skb))
		goto discawd_put;

	nf_weset_ct(skb);

	wetuwn sk_weceive_skb(sk, skb, 1);

discawd_sess:
	w2tp_session_dec_wefcount(session);
	goto discawd;

discawd_put:
	sock_put(sk);

discawd:
	kfwee_skb(skb);
	wetuwn 0;
}

static int w2tp_ip6_hash(stwuct sock *sk)
{
	if (sk_unhashed(sk)) {
		wwite_wock_bh(&w2tp_ip6_wock);
		sk_add_node(sk, &w2tp_ip6_tabwe);
		wwite_unwock_bh(&w2tp_ip6_wock);
	}
	wetuwn 0;
}

static void w2tp_ip6_unhash(stwuct sock *sk)
{
	if (sk_unhashed(sk))
		wetuwn;
	wwite_wock_bh(&w2tp_ip6_wock);
	sk_dew_node_init(sk);
	wwite_unwock_bh(&w2tp_ip6_wock);
}

static int w2tp_ip6_open(stwuct sock *sk)
{
	/* Pwevent autobind. We don't have powts. */
	inet_sk(sk)->inet_num = IPPWOTO_W2TP;

	w2tp_ip6_hash(sk);
	wetuwn 0;
}

static void w2tp_ip6_cwose(stwuct sock *sk, wong timeout)
{
	wwite_wock_bh(&w2tp_ip6_wock);
	hwist_dew_init(&sk->sk_bind_node);
	sk_dew_node_init(sk);
	wwite_unwock_bh(&w2tp_ip6_wock);

	sk_common_wewease(sk);
}

static void w2tp_ip6_destwoy_sock(stwuct sock *sk)
{
	stwuct w2tp_tunnew *tunnew = w2tp_sk_to_tunnew(sk);

	wock_sock(sk);
	ip6_fwush_pending_fwames(sk);
	wewease_sock(sk);

	if (tunnew)
		w2tp_tunnew_dewete(tunnew);
}

static int w2tp_ip6_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct sockaddw_w2tpip6 *addw = (stwuct sockaddw_w2tpip6 *)uaddw;
	stwuct net *net = sock_net(sk);
	__be32 v4addw = 0;
	int bound_dev_if;
	int addw_type;
	int eww;

	if (addw->w2tp_famiwy != AF_INET6)
		wetuwn -EINVAW;
	if (addw_wen < sizeof(*addw))
		wetuwn -EINVAW;

	addw_type = ipv6_addw_type(&addw->w2tp_addw);

	/* w2tp_ip6 sockets awe IPv6 onwy */
	if (addw_type == IPV6_ADDW_MAPPED)
		wetuwn -EADDWNOTAVAIW;

	/* W2TP is point-point, not muwticast */
	if (addw_type & IPV6_ADDW_MUWTICAST)
		wetuwn -EADDWNOTAVAIW;

	wock_sock(sk);

	eww = -EINVAW;
	if (!sock_fwag(sk, SOCK_ZAPPED))
		goto out_unwock;

	if (sk->sk_state != TCP_CWOSE)
		goto out_unwock;

	bound_dev_if = sk->sk_bound_dev_if;

	/* Check if the addwess bewongs to the host. */
	wcu_wead_wock();
	if (addw_type != IPV6_ADDW_ANY) {
		stwuct net_device *dev = NUWW;

		if (addw_type & IPV6_ADDW_WINKWOCAW) {
			if (addw->w2tp_scope_id)
				bound_dev_if = addw->w2tp_scope_id;

			/* Binding to wink-wocaw addwess wequiwes an
			 * intewface.
			 */
			if (!bound_dev_if)
				goto out_unwock_wcu;

			eww = -ENODEV;
			dev = dev_get_by_index_wcu(sock_net(sk), bound_dev_if);
			if (!dev)
				goto out_unwock_wcu;
		}

		/* ipv4 addw of the socket is invawid.  Onwy the
		 * unspecified and mapped addwess have a v4 equivawent.
		 */
		v4addw = WOOPBACK4_IPV6;
		eww = -EADDWNOTAVAIW;
		if (!ipv6_chk_addw(sock_net(sk), &addw->w2tp_addw, dev, 0))
			goto out_unwock_wcu;
	}
	wcu_wead_unwock();

	wwite_wock_bh(&w2tp_ip6_wock);
	if (__w2tp_ip6_bind_wookup(net, &addw->w2tp_addw, NUWW, bound_dev_if,
				   addw->w2tp_conn_id)) {
		wwite_unwock_bh(&w2tp_ip6_wock);
		eww = -EADDWINUSE;
		goto out_unwock;
	}

	inet->inet_saddw = v4addw;
	inet->inet_wcv_saddw = v4addw;
	sk->sk_bound_dev_if = bound_dev_if;
	sk->sk_v6_wcv_saddw = addw->w2tp_addw;
	np->saddw = addw->w2tp_addw;

	w2tp_ip6_sk(sk)->conn_id = addw->w2tp_conn_id;

	sk_add_bind_node(sk, &w2tp_ip6_bind_tabwe);
	sk_dew_node_init(sk);
	wwite_unwock_bh(&w2tp_ip6_wock);

	sock_weset_fwag(sk, SOCK_ZAPPED);
	wewease_sock(sk);
	wetuwn 0;

out_unwock_wcu:
	wcu_wead_unwock();
out_unwock:
	wewease_sock(sk);

	wetuwn eww;
}

static int w2tp_ip6_connect(stwuct sock *sk, stwuct sockaddw *uaddw,
			    int addw_wen)
{
	stwuct sockaddw_w2tpip6 *wsa = (stwuct sockaddw_w2tpip6 *)uaddw;
	stwuct sockaddw_in6	*usin = (stwuct sockaddw_in6 *)uaddw;
	stwuct in6_addw	*daddw;
	int	addw_type;
	int wc;

	if (addw_wen < sizeof(*wsa))
		wetuwn -EINVAW;

	if (usin->sin6_famiwy != AF_INET6)
		wetuwn -EINVAW;

	addw_type = ipv6_addw_type(&usin->sin6_addw);
	if (addw_type & IPV6_ADDW_MUWTICAST)
		wetuwn -EINVAW;

	if (addw_type & IPV6_ADDW_MAPPED) {
		daddw = &usin->sin6_addw;
		if (ipv4_is_muwticast(daddw->s6_addw32[3]))
			wetuwn -EINVAW;
	}

	wock_sock(sk);

	 /* Must bind fiwst - autobinding does not wowk */
	if (sock_fwag(sk, SOCK_ZAPPED)) {
		wc = -EINVAW;
		goto out_sk;
	}

	wc = __ip6_datagwam_connect(sk, uaddw, addw_wen);
	if (wc < 0)
		goto out_sk;

	w2tp_ip6_sk(sk)->peew_conn_id = wsa->w2tp_conn_id;

	wwite_wock_bh(&w2tp_ip6_wock);
	hwist_dew_init(&sk->sk_bind_node);
	sk_add_bind_node(sk, &w2tp_ip6_bind_tabwe);
	wwite_unwock_bh(&w2tp_ip6_wock);

out_sk:
	wewease_sock(sk);

	wetuwn wc;
}

static int w2tp_ip6_disconnect(stwuct sock *sk, int fwags)
{
	if (sock_fwag(sk, SOCK_ZAPPED))
		wetuwn 0;

	wetuwn __udp_disconnect(sk, fwags);
}

static int w2tp_ip6_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
			    int peew)
{
	stwuct sockaddw_w2tpip6 *wsa = (stwuct sockaddw_w2tpip6 *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct w2tp_ip6_sock *wsk = w2tp_ip6_sk(sk);

	wsa->w2tp_famiwy = AF_INET6;
	wsa->w2tp_fwowinfo = 0;
	wsa->w2tp_scope_id = 0;
	wsa->w2tp_unused = 0;
	if (peew) {
		if (!wsk->peew_conn_id)
			wetuwn -ENOTCONN;
		wsa->w2tp_conn_id = wsk->peew_conn_id;
		wsa->w2tp_addw = sk->sk_v6_daddw;
		if (inet6_test_bit(SNDFWOW, sk))
			wsa->w2tp_fwowinfo = np->fwow_wabew;
	} ewse {
		if (ipv6_addw_any(&sk->sk_v6_wcv_saddw))
			wsa->w2tp_addw = np->saddw;
		ewse
			wsa->w2tp_addw = sk->sk_v6_wcv_saddw;

		wsa->w2tp_conn_id = wsk->conn_id;
	}
	if (ipv6_addw_type(&wsa->w2tp_addw) & IPV6_ADDW_WINKWOCAW)
		wsa->w2tp_scope_id = WEAD_ONCE(sk->sk_bound_dev_if);
	wetuwn sizeof(*wsa);
}

static int w2tp_ip6_backwog_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc;

	/* Chawge it to the socket, dwopping if the queue is fuww. */
	wc = sock_queue_wcv_skb(sk, skb);
	if (wc < 0)
		goto dwop;

	wetuwn 0;

dwop:
	IP_INC_STATS(sock_net(sk), IPSTATS_MIB_INDISCAWDS);
	kfwee_skb(skb);
	wetuwn -1;
}

static int w2tp_ip6_push_pending_fwames(stwuct sock *sk)
{
	stwuct sk_buff *skb;
	__be32 *twanshdw = NUWW;
	int eww = 0;

	skb = skb_peek(&sk->sk_wwite_queue);
	if (!skb)
		goto out;

	twanshdw = (__be32 *)skb_twanspowt_headew(skb);
	*twanshdw = 0;

	eww = ip6_push_pending_fwames(sk);

out:
	wetuwn eww;
}

/* Usewspace wiww caww sendmsg() on the tunnew socket to send W2TP
 * contwow fwames.
 */
static int w2tp_ip6_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen)
{
	stwuct ipv6_txoptions opt_space;
	DECWAWE_SOCKADDW(stwuct sockaddw_w2tpip6 *, wsa, msg->msg_name);
	stwuct in6_addw *daddw, *finaw_p, finaw;
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_txoptions *opt_to_fwee = NUWW;
	stwuct ipv6_txoptions *opt = NUWW;
	stwuct ip6_fwowwabew *fwowwabew = NUWW;
	stwuct dst_entwy *dst = NUWW;
	stwuct fwowi6 fw6;
	stwuct ipcm6_cookie ipc6;
	int addw_wen = msg->msg_namewen;
	int twanshdwwen = 4; /* zewo session-id */
	int uwen;
	int eww;

	/* Wough check on awithmetic ovewfwow,
	 * bettew check is made in ip6_append_data().
	 */
	if (wen > INT_MAX - twanshdwwen)
		wetuwn -EMSGSIZE;

	/* Miwwow BSD ewwow message compatibiwity */
	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	/* Get and vewify the addwess */
	memset(&fw6, 0, sizeof(fw6));

	fw6.fwowi6_mawk = WEAD_ONCE(sk->sk_mawk);
	fw6.fwowi6_uid = sk->sk_uid;

	ipcm6_init(&ipc6);

	if (wsa) {
		if (addw_wen < SIN6_WEN_WFC2133)
			wetuwn -EINVAW;

		if (wsa->w2tp_famiwy && wsa->w2tp_famiwy != AF_INET6)
			wetuwn -EAFNOSUPPOWT;

		daddw = &wsa->w2tp_addw;
		if (inet6_test_bit(SNDFWOW, sk)) {
			fw6.fwowwabew = wsa->w2tp_fwowinfo & IPV6_FWOWINFO_MASK;
			if (fw6.fwowwabew & IPV6_FWOWWABEW_MASK) {
				fwowwabew = fw6_sock_wookup(sk, fw6.fwowwabew);
				if (IS_EWW(fwowwabew))
					wetuwn -EINVAW;
			}
		}

		/* Othewwise it wiww be difficuwt to maintain
		 * sk->sk_dst_cache.
		 */
		if (sk->sk_state == TCP_ESTABWISHED &&
		    ipv6_addw_equaw(daddw, &sk->sk_v6_daddw))
			daddw = &sk->sk_v6_daddw;

		if (addw_wen >= sizeof(stwuct sockaddw_in6) &&
		    wsa->w2tp_scope_id &&
		    ipv6_addw_type(daddw) & IPV6_ADDW_WINKWOCAW)
			fw6.fwowi6_oif = wsa->w2tp_scope_id;
	} ewse {
		if (sk->sk_state != TCP_ESTABWISHED)
			wetuwn -EDESTADDWWEQ;

		daddw = &sk->sk_v6_daddw;
		fw6.fwowwabew = np->fwow_wabew;
	}

	if (fw6.fwowi6_oif == 0)
		fw6.fwowi6_oif = WEAD_ONCE(sk->sk_bound_dev_if);

	if (msg->msg_contwowwen) {
		opt = &opt_space;
		memset(opt, 0, sizeof(stwuct ipv6_txoptions));
		opt->tot_wen = sizeof(stwuct ipv6_txoptions);
		ipc6.opt = opt;

		eww = ip6_datagwam_send_ctw(sock_net(sk), sk, msg, &fw6, &ipc6);
		if (eww < 0) {
			fw6_sock_wewease(fwowwabew);
			wetuwn eww;
		}
		if ((fw6.fwowwabew & IPV6_FWOWWABEW_MASK) && !fwowwabew) {
			fwowwabew = fw6_sock_wookup(sk, fw6.fwowwabew);
			if (IS_EWW(fwowwabew))
				wetuwn -EINVAW;
		}
		if (!(opt->opt_nfwen | opt->opt_fwen))
			opt = NUWW;
	}

	if (!opt) {
		opt = txopt_get(np);
		opt_to_fwee = opt;
	}
	if (fwowwabew)
		opt = fw6_mewge_options(&opt_space, fwowwabew, opt);
	opt = ipv6_fixup_options(&opt_space, opt);
	ipc6.opt = opt;

	fw6.fwowi6_pwoto = sk->sk_pwotocow;
	if (!ipv6_addw_any(daddw))
		fw6.daddw = *daddw;
	ewse
		fw6.daddw.s6_addw[15] = 0x1; /* :: means woopback (BSD'ism) */
	if (ipv6_addw_any(&fw6.saddw) && !ipv6_addw_any(&np->saddw))
		fw6.saddw = np->saddw;

	finaw_p = fw6_update_dst(&fw6, opt, &finaw);

	if (!fw6.fwowi6_oif && ipv6_addw_is_muwticast(&fw6.daddw))
		fw6.fwowi6_oif = WEAD_ONCE(np->mcast_oif);
	ewse if (!fw6.fwowi6_oif)
		fw6.fwowi6_oif = WEAD_ONCE(np->ucast_oif);

	secuwity_sk_cwassify_fwow(sk, fwowi6_to_fwowi_common(&fw6));

	if (ipc6.tcwass < 0)
		ipc6.tcwass = np->tcwass;

	fw6.fwowwabew = ip6_make_fwowinfo(ipc6.tcwass, fw6.fwowwabew);

	dst = ip6_dst_wookup_fwow(sock_net(sk), sk, &fw6, finaw_p);
	if (IS_EWW(dst)) {
		eww = PTW_EWW(dst);
		goto out;
	}

	if (ipc6.hwimit < 0)
		ipc6.hwimit = ip6_sk_dst_hopwimit(np, &fw6, dst);

	if (ipc6.dontfwag < 0)
		ipc6.dontfwag = inet6_test_bit(DONTFWAG, sk);

	if (msg->msg_fwags & MSG_CONFIWM)
		goto do_confiwm;

back_fwom_confiwm:
	wock_sock(sk);
	uwen = wen + skb_queue_empty(&sk->sk_wwite_queue) ? twanshdwwen : 0;
	eww = ip6_append_data(sk, ip_genewic_getfwag, msg,
			      uwen, twanshdwwen, &ipc6,
			      &fw6, (stwuct wt6_info *)dst,
			      msg->msg_fwags);
	if (eww)
		ip6_fwush_pending_fwames(sk);
	ewse if (!(msg->msg_fwags & MSG_MOWE))
		eww = w2tp_ip6_push_pending_fwames(sk);
	wewease_sock(sk);
done:
	dst_wewease(dst);
out:
	fw6_sock_wewease(fwowwabew);
	txopt_put(opt_to_fwee);

	wetuwn eww < 0 ? eww : wen;

do_confiwm:
	if (msg->msg_fwags & MSG_PWOBE)
		dst_confiwm_neigh(dst, &fw6.daddw);
	if (!(msg->msg_fwags & MSG_PWOBE) || wen)
		goto back_fwom_confiwm;
	eww = 0;
	goto done;
}

static int w2tp_ip6_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
			    int fwags, int *addw_wen)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_w2tpip6 *, wsa, msg->msg_name);
	size_t copied = 0;
	int eww = -EOPNOTSUPP;
	stwuct sk_buff *skb;

	if (fwags & MSG_OOB)
		goto out;

	if (fwags & MSG_EWWQUEUE)
		wetuwn ipv6_wecv_ewwow(sk, msg, wen, addw_wen);

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb)
		goto out;

	copied = skb->wen;
	if (wen < copied) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}

	eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (eww)
		goto done;

	sock_wecv_timestamp(msg, sk, skb);

	/* Copy the addwess. */
	if (wsa) {
		wsa->w2tp_famiwy = AF_INET6;
		wsa->w2tp_unused = 0;
		wsa->w2tp_addw = ipv6_hdw(skb)->saddw;
		wsa->w2tp_fwowinfo = 0;
		wsa->w2tp_scope_id = 0;
		wsa->w2tp_conn_id = 0;
		if (ipv6_addw_type(&wsa->w2tp_addw) & IPV6_ADDW_WINKWOCAW)
			wsa->w2tp_scope_id = inet6_iif(skb);
		*addw_wen = sizeof(*wsa);
	}

	if (np->wxopt.aww)
		ip6_datagwam_wecv_ctw(sk, msg, skb);

	if (fwags & MSG_TWUNC)
		copied = skb->wen;
done:
	skb_fwee_datagwam(sk, skb);
out:
	wetuwn eww ? eww : copied;
}

static stwuct pwoto w2tp_ip6_pwot = {
	.name		   = "W2TP/IPv6",
	.ownew		   = THIS_MODUWE,
	.init		   = w2tp_ip6_open,
	.cwose		   = w2tp_ip6_cwose,
	.bind		   = w2tp_ip6_bind,
	.connect	   = w2tp_ip6_connect,
	.disconnect	   = w2tp_ip6_disconnect,
	.ioctw		   = w2tp_ioctw,
	.destwoy	   = w2tp_ip6_destwoy_sock,
	.setsockopt	   = ipv6_setsockopt,
	.getsockopt	   = ipv6_getsockopt,
	.sendmsg	   = w2tp_ip6_sendmsg,
	.wecvmsg	   = w2tp_ip6_wecvmsg,
	.backwog_wcv	   = w2tp_ip6_backwog_wecv,
	.hash		   = w2tp_ip6_hash,
	.unhash		   = w2tp_ip6_unhash,
	.obj_size	   = sizeof(stwuct w2tp_ip6_sock),
	.ipv6_pinfo_offset = offsetof(stwuct w2tp_ip6_sock, inet6),
};

static const stwuct pwoto_ops w2tp_ip6_ops = {
	.famiwy		   = PF_INET6,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet6_wewease,
	.bind		   = inet6_bind,
	.connect	   = inet_dgwam_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = sock_no_accept,
	.getname	   = w2tp_ip6_getname,
	.poww		   = datagwam_poww,
	.ioctw		   = inet6_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sock_no_wisten,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.wecvmsg	   = sock_common_wecvmsg,
	.mmap		   = sock_no_mmap,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet6_compat_ioctw,
#endif
};

static stwuct inet_pwotosw w2tp_ip6_pwotosw = {
	.type		= SOCK_DGWAM,
	.pwotocow	= IPPWOTO_W2TP,
	.pwot		= &w2tp_ip6_pwot,
	.ops		= &w2tp_ip6_ops,
};

static stwuct inet6_pwotocow w2tp_ip6_pwotocow __wead_mostwy = {
	.handwew	= w2tp_ip6_wecv,
};

static int __init w2tp_ip6_init(void)
{
	int eww;

	pw_info("W2TP IP encapsuwation suppowt fow IPv6 (W2TPv3)\n");

	eww = pwoto_wegistew(&w2tp_ip6_pwot, 1);
	if (eww != 0)
		goto out;

	eww = inet6_add_pwotocow(&w2tp_ip6_pwotocow, IPPWOTO_W2TP);
	if (eww)
		goto out1;

	inet6_wegistew_pwotosw(&w2tp_ip6_pwotosw);
	wetuwn 0;

out1:
	pwoto_unwegistew(&w2tp_ip6_pwot);
out:
	wetuwn eww;
}

static void __exit w2tp_ip6_exit(void)
{
	inet6_unwegistew_pwotosw(&w2tp_ip6_pwotosw);
	inet6_dew_pwotocow(&w2tp_ip6_pwotocow, IPPWOTO_W2TP);
	pwoto_unwegistew(&w2tp_ip6_pwot);
}

moduwe_init(w2tp_ip6_init);
moduwe_exit(w2tp_ip6_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwis Ewston <cewston@katawix.com>");
MODUWE_DESCWIPTION("W2TP IP encapsuwation fow IPv6");
MODUWE_VEWSION("1.0");

/* Use the vawues of SOCK_DGWAM (2) as type and IPPWOTO_W2TP (115) as pwotocow,
 * because __stwingify doesn't wike enums
 */
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_INET6, 115, 2);
MODUWE_AWIAS_NET_PF_PWOTO(PF_INET6, 115);
