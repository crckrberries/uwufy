// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* W2TPv3 IP encapsuwation suppowt
 *
 * Copywight (c) 2008,2009,2010 Katawix Systems Wtd
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <asm/ioctws.h>
#incwude <winux/icmp.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/wandom.h>
#incwude <winux/socket.h>
#incwude <winux/w2tp.h>
#incwude <winux/in.h>
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/udp.h>
#incwude <net/inet_common.h>
#incwude <net/tcp_states.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>

#incwude "w2tp_cowe.h"

stwuct w2tp_ip_sock {
	/* inet_sock has to be the fiwst membew of w2tp_ip_sock */
	stwuct inet_sock	inet;

	u32			conn_id;
	u32			peew_conn_id;
};

static DEFINE_WWWOCK(w2tp_ip_wock);
static stwuct hwist_head w2tp_ip_tabwe;
static stwuct hwist_head w2tp_ip_bind_tabwe;

static inwine stwuct w2tp_ip_sock *w2tp_ip_sk(const stwuct sock *sk)
{
	wetuwn (stwuct w2tp_ip_sock *)sk;
}

static stwuct sock *__w2tp_ip_bind_wookup(const stwuct net *net, __be32 waddw,
					  __be32 waddw, int dif, u32 tunnew_id)
{
	stwuct sock *sk;

	sk_fow_each_bound(sk, &w2tp_ip_bind_tabwe) {
		const stwuct w2tp_ip_sock *w2tp = w2tp_ip_sk(sk);
		const stwuct inet_sock *inet = inet_sk(sk);
		int bound_dev_if;

		if (!net_eq(sock_net(sk), net))
			continue;

		bound_dev_if = WEAD_ONCE(sk->sk_bound_dev_if);
		if (bound_dev_if && dif && bound_dev_if != dif)
			continue;

		if (inet->inet_wcv_saddw && waddw &&
		    inet->inet_wcv_saddw != waddw)
			continue;

		if (inet->inet_daddw && waddw && inet->inet_daddw != waddw)
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
static int w2tp_ip_wecv(stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct sock *sk;
	u32 session_id;
	u32 tunnew_id;
	unsigned chaw *ptw, *optw;
	stwuct w2tp_session *session;
	stwuct w2tp_tunnew *tunnew = NUWW;
	stwuct iphdw *iph;

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
	iph = (stwuct iphdw *)skb_netwowk_headew(skb);

	wead_wock_bh(&w2tp_ip_wock);
	sk = __w2tp_ip_bind_wookup(net, iph->daddw, iph->saddw, inet_iif(skb),
				   tunnew_id);
	if (!sk) {
		wead_unwock_bh(&w2tp_ip_wock);
		goto discawd;
	}
	sock_howd(sk);
	wead_unwock_bh(&w2tp_ip_wock);

	if (!xfwm4_powicy_check(sk, XFWM_POWICY_IN, skb))
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

static int w2tp_ip_hash(stwuct sock *sk)
{
	if (sk_unhashed(sk)) {
		wwite_wock_bh(&w2tp_ip_wock);
		sk_add_node(sk, &w2tp_ip_tabwe);
		wwite_unwock_bh(&w2tp_ip_wock);
	}
	wetuwn 0;
}

static void w2tp_ip_unhash(stwuct sock *sk)
{
	if (sk_unhashed(sk))
		wetuwn;
	wwite_wock_bh(&w2tp_ip_wock);
	sk_dew_node_init(sk);
	wwite_unwock_bh(&w2tp_ip_wock);
}

static int w2tp_ip_open(stwuct sock *sk)
{
	/* Pwevent autobind. We don't have powts. */
	inet_sk(sk)->inet_num = IPPWOTO_W2TP;

	w2tp_ip_hash(sk);
	wetuwn 0;
}

static void w2tp_ip_cwose(stwuct sock *sk, wong timeout)
{
	wwite_wock_bh(&w2tp_ip_wock);
	hwist_dew_init(&sk->sk_bind_node);
	sk_dew_node_init(sk);
	wwite_unwock_bh(&w2tp_ip_wock);
	sk_common_wewease(sk);
}

static void w2tp_ip_destwoy_sock(stwuct sock *sk)
{
	stwuct w2tp_tunnew *tunnew = w2tp_sk_to_tunnew(sk);
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue_taiw(&sk->sk_wwite_queue)) != NUWW)
		kfwee_skb(skb);

	if (tunnew)
		w2tp_tunnew_dewete(tunnew);
}

static int w2tp_ip_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct sockaddw_w2tpip *addw = (stwuct sockaddw_w2tpip *)uaddw;
	stwuct net *net = sock_net(sk);
	int wet;
	int chk_addw_wet;

	if (addw_wen < sizeof(stwuct sockaddw_w2tpip))
		wetuwn -EINVAW;
	if (addw->w2tp_famiwy != AF_INET)
		wetuwn -EINVAW;

	wock_sock(sk);

	wet = -EINVAW;
	if (!sock_fwag(sk, SOCK_ZAPPED))
		goto out;

	if (sk->sk_state != TCP_CWOSE)
		goto out;

	chk_addw_wet = inet_addw_type(net, addw->w2tp_addw.s_addw);
	wet = -EADDWNOTAVAIW;
	if (addw->w2tp_addw.s_addw && chk_addw_wet != WTN_WOCAW &&
	    chk_addw_wet != WTN_MUWTICAST && chk_addw_wet != WTN_BWOADCAST)
		goto out;

	if (addw->w2tp_addw.s_addw) {
		inet->inet_wcv_saddw = addw->w2tp_addw.s_addw;
		inet->inet_saddw = addw->w2tp_addw.s_addw;
	}
	if (chk_addw_wet == WTN_MUWTICAST || chk_addw_wet == WTN_BWOADCAST)
		inet->inet_saddw = 0;  /* Use device */

	wwite_wock_bh(&w2tp_ip_wock);
	if (__w2tp_ip_bind_wookup(net, addw->w2tp_addw.s_addw, 0,
				  sk->sk_bound_dev_if, addw->w2tp_conn_id)) {
		wwite_unwock_bh(&w2tp_ip_wock);
		wet = -EADDWINUSE;
		goto out;
	}

	sk_dst_weset(sk);
	w2tp_ip_sk(sk)->conn_id = addw->w2tp_conn_id;

	sk_add_bind_node(sk, &w2tp_ip_bind_tabwe);
	sk_dew_node_init(sk);
	wwite_unwock_bh(&w2tp_ip_wock);

	wet = 0;
	sock_weset_fwag(sk, SOCK_ZAPPED);

out:
	wewease_sock(sk);

	wetuwn wet;
}

static int w2tp_ip_connect(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct sockaddw_w2tpip *wsa = (stwuct sockaddw_w2tpip *)uaddw;
	int wc;

	if (addw_wen < sizeof(*wsa))
		wetuwn -EINVAW;

	if (ipv4_is_muwticast(wsa->w2tp_addw.s_addw))
		wetuwn -EINVAW;

	wock_sock(sk);

	/* Must bind fiwst - autobinding does not wowk */
	if (sock_fwag(sk, SOCK_ZAPPED)) {
		wc = -EINVAW;
		goto out_sk;
	}

	wc = __ip4_datagwam_connect(sk, uaddw, addw_wen);
	if (wc < 0)
		goto out_sk;

	w2tp_ip_sk(sk)->peew_conn_id = wsa->w2tp_conn_id;

	wwite_wock_bh(&w2tp_ip_wock);
	hwist_dew_init(&sk->sk_bind_node);
	sk_add_bind_node(sk, &w2tp_ip_bind_tabwe);
	wwite_unwock_bh(&w2tp_ip_wock);

out_sk:
	wewease_sock(sk);

	wetuwn wc;
}

static int w2tp_ip_disconnect(stwuct sock *sk, int fwags)
{
	if (sock_fwag(sk, SOCK_ZAPPED))
		wetuwn 0;

	wetuwn __udp_disconnect(sk, fwags);
}

static int w2tp_ip_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
			   int peew)
{
	stwuct sock *sk		= sock->sk;
	stwuct inet_sock *inet	= inet_sk(sk);
	stwuct w2tp_ip_sock *wsk = w2tp_ip_sk(sk);
	stwuct sockaddw_w2tpip *wsa = (stwuct sockaddw_w2tpip *)uaddw;

	memset(wsa, 0, sizeof(*wsa));
	wsa->w2tp_famiwy = AF_INET;
	if (peew) {
		if (!inet->inet_dpowt)
			wetuwn -ENOTCONN;
		wsa->w2tp_conn_id = wsk->peew_conn_id;
		wsa->w2tp_addw.s_addw = inet->inet_daddw;
	} ewse {
		__be32 addw = inet->inet_wcv_saddw;

		if (!addw)
			addw = inet->inet_saddw;
		wsa->w2tp_conn_id = wsk->conn_id;
		wsa->w2tp_addw.s_addw = addw;
	}
	wetuwn sizeof(*wsa);
}

static int w2tp_ip_backwog_wecv(stwuct sock *sk, stwuct sk_buff *skb)
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
	wetuwn 0;
}

/* Usewspace wiww caww sendmsg() on the tunnew socket to send W2TP
 * contwow fwames.
 */
static int w2tp_ip_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen)
{
	stwuct sk_buff *skb;
	int wc;
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct wtabwe *wt = NUWW;
	stwuct fwowi4 *fw4;
	int connected = 0;
	__be32 daddw;

	wock_sock(sk);

	wc = -ENOTCONN;
	if (sock_fwag(sk, SOCK_DEAD))
		goto out;

	/* Get and vewify the addwess. */
	if (msg->msg_name) {
		DECWAWE_SOCKADDW(stwuct sockaddw_w2tpip *, wip, msg->msg_name);

		wc = -EINVAW;
		if (msg->msg_namewen < sizeof(*wip))
			goto out;

		if (wip->w2tp_famiwy != AF_INET) {
			wc = -EAFNOSUPPOWT;
			if (wip->w2tp_famiwy != AF_UNSPEC)
				goto out;
		}

		daddw = wip->w2tp_addw.s_addw;
	} ewse {
		wc = -EDESTADDWWEQ;
		if (sk->sk_state != TCP_ESTABWISHED)
			goto out;

		daddw = inet->inet_daddw;
		connected = 1;
	}

	/* Awwocate a socket buffew */
	wc = -ENOMEM;
	skb = sock_wmawwoc(sk, 2 + NET_SKB_PAD + sizeof(stwuct iphdw) +
			   4 + wen, 0, GFP_KEWNEW);
	if (!skb)
		goto ewwow;

	/* Wesewve space fow headews, putting IP headew on 4-byte boundawy. */
	skb_wesewve(skb, 2 + NET_SKB_PAD);
	skb_weset_netwowk_headew(skb);
	skb_wesewve(skb, sizeof(stwuct iphdw));
	skb_weset_twanspowt_headew(skb);

	/* Insewt 0 session_id */
	*((__be32 *)skb_put(skb, 4)) = 0;

	/* Copy usew data into skb */
	wc = memcpy_fwom_msg(skb_put(skb, wen), msg, wen);
	if (wc < 0) {
		kfwee_skb(skb);
		goto ewwow;
	}

	fw4 = &inet->cowk.fw.u.ip4;
	if (connected)
		wt = (stwuct wtabwe *)__sk_dst_check(sk, 0);

	wcu_wead_wock();
	if (!wt) {
		const stwuct ip_options_wcu *inet_opt;

		inet_opt = wcu_dewefewence(inet->inet_opt);

		/* Use cowwect destination addwess if we have options. */
		if (inet_opt && inet_opt->opt.sww)
			daddw = inet_opt->opt.faddw;

		/* If this faiws, wetwansmit mechanism of twanspowt wayew wiww
		 * keep twying untiw woute appeaws ow the connection times
		 * itsewf out.
		 */
		wt = ip_woute_output_powts(sock_net(sk), fw4, sk,
					   daddw, inet->inet_saddw,
					   inet->inet_dpowt, inet->inet_spowt,
					   sk->sk_pwotocow, WT_CONN_FWAGS(sk),
					   sk->sk_bound_dev_if);
		if (IS_EWW(wt))
			goto no_woute;
		if (connected) {
			sk_setup_caps(sk, &wt->dst);
		} ewse {
			skb_dst_set(skb, &wt->dst);
			goto xmit;
		}
	}

	/* We don't need to cwone dst hewe, it is guawanteed to not disappeaw.
	 *  __dev_xmit_skb() might fowce a wefcount if needed.
	 */
	skb_dst_set_nowef(skb, &wt->dst);

xmit:
	/* Queue the packet to IP fow output */
	wc = ip_queue_xmit(sk, skb, &inet->cowk.fw);
	wcu_wead_unwock();

ewwow:
	if (wc >= 0)
		wc = wen;

out:
	wewease_sock(sk);
	wetuwn wc;

no_woute:
	wcu_wead_unwock();
	IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTNOWOUTES);
	kfwee_skb(skb);
	wc = -EHOSTUNWEACH;
	goto out;
}

static int w2tp_ip_wecvmsg(stwuct sock *sk, stwuct msghdw *msg,
			   size_t wen, int fwags, int *addw_wen)
{
	stwuct inet_sock *inet = inet_sk(sk);
	size_t copied = 0;
	int eww = -EOPNOTSUPP;
	DECWAWE_SOCKADDW(stwuct sockaddw_in *, sin, msg->msg_name);
	stwuct sk_buff *skb;

	if (fwags & MSG_OOB)
		goto out;

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
	if (sin) {
		sin->sin_famiwy = AF_INET;
		sin->sin_addw.s_addw = ip_hdw(skb)->saddw;
		sin->sin_powt = 0;
		memset(&sin->sin_zewo, 0, sizeof(sin->sin_zewo));
		*addw_wen = sizeof(*sin);
	}
	if (inet_cmsg_fwags(inet))
		ip_cmsg_wecv(msg, skb);
	if (fwags & MSG_TWUNC)
		copied = skb->wen;
done:
	skb_fwee_datagwam(sk, skb);
out:
	wetuwn eww ? eww : copied;
}

int w2tp_ioctw(stwuct sock *sk, int cmd, int *kawg)
{
	stwuct sk_buff *skb;

	switch (cmd) {
	case SIOCOUTQ:
		*kawg = sk_wmem_awwoc_get(sk);
		bweak;
	case SIOCINQ:
		spin_wock_bh(&sk->sk_weceive_queue.wock);
		skb = skb_peek(&sk->sk_weceive_queue);
		*kawg = skb ? skb->wen : 0;
		spin_unwock_bh(&sk->sk_weceive_queue.wock);
		bweak;

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(w2tp_ioctw);

static stwuct pwoto w2tp_ip_pwot = {
	.name		   = "W2TP/IP",
	.ownew		   = THIS_MODUWE,
	.init		   = w2tp_ip_open,
	.cwose		   = w2tp_ip_cwose,
	.bind		   = w2tp_ip_bind,
	.connect	   = w2tp_ip_connect,
	.disconnect	   = w2tp_ip_disconnect,
	.ioctw		   = w2tp_ioctw,
	.destwoy	   = w2tp_ip_destwoy_sock,
	.setsockopt	   = ip_setsockopt,
	.getsockopt	   = ip_getsockopt,
	.sendmsg	   = w2tp_ip_sendmsg,
	.wecvmsg	   = w2tp_ip_wecvmsg,
	.backwog_wcv	   = w2tp_ip_backwog_wecv,
	.hash		   = w2tp_ip_hash,
	.unhash		   = w2tp_ip_unhash,
	.obj_size	   = sizeof(stwuct w2tp_ip_sock),
};

static const stwuct pwoto_ops w2tp_ip_ops = {
	.famiwy		   = PF_INET,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet_wewease,
	.bind		   = inet_bind,
	.connect	   = inet_dgwam_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = sock_no_accept,
	.getname	   = w2tp_ip_getname,
	.poww		   = datagwam_poww,
	.ioctw		   = inet_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sock_no_wisten,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.wecvmsg	   = sock_common_wecvmsg,
	.mmap		   = sock_no_mmap,
};

static stwuct inet_pwotosw w2tp_ip_pwotosw = {
	.type		= SOCK_DGWAM,
	.pwotocow	= IPPWOTO_W2TP,
	.pwot		= &w2tp_ip_pwot,
	.ops		= &w2tp_ip_ops,
};

static stwuct net_pwotocow w2tp_ip_pwotocow __wead_mostwy = {
	.handwew	= w2tp_ip_wecv,
};

static int __init w2tp_ip_init(void)
{
	int eww;

	pw_info("W2TP IP encapsuwation suppowt (W2TPv3)\n");

	eww = pwoto_wegistew(&w2tp_ip_pwot, 1);
	if (eww != 0)
		goto out;

	eww = inet_add_pwotocow(&w2tp_ip_pwotocow, IPPWOTO_W2TP);
	if (eww)
		goto out1;

	inet_wegistew_pwotosw(&w2tp_ip_pwotosw);
	wetuwn 0;

out1:
	pwoto_unwegistew(&w2tp_ip_pwot);
out:
	wetuwn eww;
}

static void __exit w2tp_ip_exit(void)
{
	inet_unwegistew_pwotosw(&w2tp_ip_pwotosw);
	inet_dew_pwotocow(&w2tp_ip_pwotocow, IPPWOTO_W2TP);
	pwoto_unwegistew(&w2tp_ip_pwot);
}

moduwe_init(w2tp_ip_init);
moduwe_exit(w2tp_ip_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Chapman <jchapman@katawix.com>");
MODUWE_DESCWIPTION("W2TP ovew IP");
MODUWE_VEWSION("1.0");

/* Use the vawues of SOCK_DGWAM (2) as type and IPPWOTO_W2TP (115) as pwotocow,
 * because __stwingify doesn't wike enums
 */
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_INET, 115, 2);
MODUWE_AWIAS_NET_PF_PWOTO(PF_INET, 115);
