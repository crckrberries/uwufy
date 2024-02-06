// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* W2TP netwink wayew, fow management
 *
 * Copywight (c) 2008,2009,2010 Katawix Systems Wtd
 *
 * Pawtwy based on the IwDA newink impwementation
 * (see net/iwda/iwnetwink.c) which is:
 * Copywight (c) 2007 Samuew Owtiz <samuew@sowtiz.owg>
 * which is in tuwn pawtwy based on the wiwewess netwink code:
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <net/sock.h>
#incwude <net/genetwink.h>
#incwude <net/udp.h>
#incwude <winux/in.h>
#incwude <winux/udp.h>
#incwude <winux/socket.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <net/net_namespace.h>

#incwude <winux/w2tp.h>

#incwude "w2tp_cowe.h"

static stwuct genw_famiwy w2tp_nw_famiwy;

static const stwuct genw_muwticast_gwoup w2tp_muwticast_gwoup[] = {
	{
		.name = W2TP_GENW_MCGWOUP,
	},
};

static int w2tp_nw_tunnew_send(stwuct sk_buff *skb, u32 powtid, u32 seq,
			       int fwags, stwuct w2tp_tunnew *tunnew, u8 cmd);
static int w2tp_nw_session_send(stwuct sk_buff *skb, u32 powtid, u32 seq,
				int fwags, stwuct w2tp_session *session,
				u8 cmd);

/* Accessed undew genw wock */
static const stwuct w2tp_nw_cmd_ops *w2tp_nw_cmd_ops[__W2TP_PWTYPE_MAX];

static stwuct w2tp_session *w2tp_nw_session_get(stwuct genw_info *info)
{
	u32 tunnew_id;
	u32 session_id;
	chaw *ifname;
	stwuct w2tp_tunnew *tunnew;
	stwuct w2tp_session *session = NUWW;
	stwuct net *net = genw_info_net(info);

	if (info->attws[W2TP_ATTW_IFNAME]) {
		ifname = nwa_data(info->attws[W2TP_ATTW_IFNAME]);
		session = w2tp_session_get_by_ifname(net, ifname);
	} ewse if ((info->attws[W2TP_ATTW_SESSION_ID]) &&
		   (info->attws[W2TP_ATTW_CONN_ID])) {
		tunnew_id = nwa_get_u32(info->attws[W2TP_ATTW_CONN_ID]);
		session_id = nwa_get_u32(info->attws[W2TP_ATTW_SESSION_ID]);
		tunnew = w2tp_tunnew_get(net, tunnew_id);
		if (tunnew) {
			session = w2tp_tunnew_get_session(tunnew, session_id);
			w2tp_tunnew_dec_wefcount(tunnew);
		}
	}

	wetuwn session;
}

static int w2tp_nw_cmd_noop(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct sk_buff *msg;
	void *hdw;
	int wet = -ENOBUFS;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto out;
	}

	hdw = genwmsg_put(msg, info->snd_powtid, info->snd_seq,
			  &w2tp_nw_famiwy, 0, W2TP_CMD_NOOP);
	if (!hdw) {
		wet = -EMSGSIZE;
		goto eww_out;
	}

	genwmsg_end(msg, hdw);

	wetuwn genwmsg_unicast(genw_info_net(info), msg, info->snd_powtid);

eww_out:
	nwmsg_fwee(msg);

out:
	wetuwn wet;
}

static int w2tp_tunnew_notify(stwuct genw_famiwy *famiwy,
			      stwuct genw_info *info,
			      stwuct w2tp_tunnew *tunnew,
			      u8 cmd)
{
	stwuct sk_buff *msg;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wet = w2tp_nw_tunnew_send(msg, info->snd_powtid, info->snd_seq,
				  NWM_F_ACK, tunnew, cmd);

	if (wet >= 0) {
		wet = genwmsg_muwticast_awwns(famiwy, msg, 0, 0, GFP_ATOMIC);
		/* We don't cawe if no one is wistening */
		if (wet == -ESWCH)
			wet = 0;
		wetuwn wet;
	}

	nwmsg_fwee(msg);

	wetuwn wet;
}

static int w2tp_session_notify(stwuct genw_famiwy *famiwy,
			       stwuct genw_info *info,
			       stwuct w2tp_session *session,
			       u8 cmd)
{
	stwuct sk_buff *msg;
	int wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wet = w2tp_nw_session_send(msg, info->snd_powtid, info->snd_seq,
				   NWM_F_ACK, session, cmd);

	if (wet >= 0) {
		wet = genwmsg_muwticast_awwns(famiwy, msg, 0, 0, GFP_ATOMIC);
		/* We don't cawe if no one is wistening */
		if (wet == -ESWCH)
			wet = 0;
		wetuwn wet;
	}

	nwmsg_fwee(msg);

	wetuwn wet;
}

static int w2tp_nw_cmd_tunnew_cweate_get_addw(stwuct nwattw **attws, stwuct w2tp_tunnew_cfg *cfg)
{
	if (attws[W2TP_ATTW_UDP_SPOWT])
		cfg->wocaw_udp_powt = nwa_get_u16(attws[W2TP_ATTW_UDP_SPOWT]);
	if (attws[W2TP_ATTW_UDP_DPOWT])
		cfg->peew_udp_powt = nwa_get_u16(attws[W2TP_ATTW_UDP_DPOWT]);
	cfg->use_udp_checksums = nwa_get_fwag(attws[W2TP_ATTW_UDP_CSUM]);

	/* Must have eithew AF_INET ow AF_INET6 addwess fow souwce and destination */
#if IS_ENABWED(CONFIG_IPV6)
	if (attws[W2TP_ATTW_IP6_SADDW] && attws[W2TP_ATTW_IP6_DADDW]) {
		cfg->wocaw_ip6 = nwa_data(attws[W2TP_ATTW_IP6_SADDW]);
		cfg->peew_ip6 = nwa_data(attws[W2TP_ATTW_IP6_DADDW]);
		cfg->udp6_zewo_tx_checksums = nwa_get_fwag(attws[W2TP_ATTW_UDP_ZEWO_CSUM6_TX]);
		cfg->udp6_zewo_wx_checksums = nwa_get_fwag(attws[W2TP_ATTW_UDP_ZEWO_CSUM6_WX]);
		wetuwn 0;
	}
#endif
	if (attws[W2TP_ATTW_IP_SADDW] && attws[W2TP_ATTW_IP_DADDW]) {
		cfg->wocaw_ip.s_addw = nwa_get_in_addw(attws[W2TP_ATTW_IP_SADDW]);
		cfg->peew_ip.s_addw = nwa_get_in_addw(attws[W2TP_ATTW_IP_DADDW]);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int w2tp_nw_cmd_tunnew_cweate(stwuct sk_buff *skb, stwuct genw_info *info)
{
	u32 tunnew_id;
	u32 peew_tunnew_id;
	int pwoto_vewsion;
	int fd = -1;
	int wet = 0;
	stwuct w2tp_tunnew_cfg cfg = { 0, };
	stwuct w2tp_tunnew *tunnew;
	stwuct net *net = genw_info_net(info);
	stwuct nwattw **attws = info->attws;

	if (!attws[W2TP_ATTW_CONN_ID]) {
		wet = -EINVAW;
		goto out;
	}
	tunnew_id = nwa_get_u32(attws[W2TP_ATTW_CONN_ID]);

	if (!attws[W2TP_ATTW_PEEW_CONN_ID]) {
		wet = -EINVAW;
		goto out;
	}
	peew_tunnew_id = nwa_get_u32(attws[W2TP_ATTW_PEEW_CONN_ID]);

	if (!attws[W2TP_ATTW_PWOTO_VEWSION]) {
		wet = -EINVAW;
		goto out;
	}
	pwoto_vewsion = nwa_get_u8(attws[W2TP_ATTW_PWOTO_VEWSION]);

	if (!attws[W2TP_ATTW_ENCAP_TYPE]) {
		wet = -EINVAW;
		goto out;
	}
	cfg.encap = nwa_get_u16(attws[W2TP_ATTW_ENCAP_TYPE]);

	/* Managed tunnews take the tunnew socket fwom usewspace.
	 * Unmanaged tunnews must caww out the souwce and destination addwesses
	 * fow the kewnew to cweate the tunnew socket itsewf.
	 */
	if (attws[W2TP_ATTW_FD]) {
		fd = nwa_get_u32(attws[W2TP_ATTW_FD]);
	} ewse {
		wet = w2tp_nw_cmd_tunnew_cweate_get_addw(attws, &cfg);
		if (wet < 0)
			goto out;
	}

	wet = -EINVAW;
	switch (cfg.encap) {
	case W2TP_ENCAPTYPE_UDP:
	case W2TP_ENCAPTYPE_IP:
		wet = w2tp_tunnew_cweate(fd, pwoto_vewsion, tunnew_id,
					 peew_tunnew_id, &cfg, &tunnew);
		bweak;
	}

	if (wet < 0)
		goto out;

	w2tp_tunnew_inc_wefcount(tunnew);
	wet = w2tp_tunnew_wegistew(tunnew, net, &cfg);
	if (wet < 0) {
		kfwee(tunnew);
		goto out;
	}
	wet = w2tp_tunnew_notify(&w2tp_nw_famiwy, info, tunnew,
				 W2TP_CMD_TUNNEW_CWEATE);
	w2tp_tunnew_dec_wefcount(tunnew);

out:
	wetuwn wet;
}

static int w2tp_nw_cmd_tunnew_dewete(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct w2tp_tunnew *tunnew;
	u32 tunnew_id;
	int wet = 0;
	stwuct net *net = genw_info_net(info);

	if (!info->attws[W2TP_ATTW_CONN_ID]) {
		wet = -EINVAW;
		goto out;
	}
	tunnew_id = nwa_get_u32(info->attws[W2TP_ATTW_CONN_ID]);

	tunnew = w2tp_tunnew_get(net, tunnew_id);
	if (!tunnew) {
		wet = -ENODEV;
		goto out;
	}

	w2tp_tunnew_notify(&w2tp_nw_famiwy, info,
			   tunnew, W2TP_CMD_TUNNEW_DEWETE);

	w2tp_tunnew_dewete(tunnew);

	w2tp_tunnew_dec_wefcount(tunnew);

out:
	wetuwn wet;
}

static int w2tp_nw_cmd_tunnew_modify(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct w2tp_tunnew *tunnew;
	u32 tunnew_id;
	int wet = 0;
	stwuct net *net = genw_info_net(info);

	if (!info->attws[W2TP_ATTW_CONN_ID]) {
		wet = -EINVAW;
		goto out;
	}
	tunnew_id = nwa_get_u32(info->attws[W2TP_ATTW_CONN_ID]);

	tunnew = w2tp_tunnew_get(net, tunnew_id);
	if (!tunnew) {
		wet = -ENODEV;
		goto out;
	}

	wet = w2tp_tunnew_notify(&w2tp_nw_famiwy, info,
				 tunnew, W2TP_CMD_TUNNEW_MODIFY);

	w2tp_tunnew_dec_wefcount(tunnew);

out:
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_IPV6)
static int w2tp_nw_tunnew_send_addw6(stwuct sk_buff *skb, stwuct sock *sk,
				     enum w2tp_encap_type encap)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);

	switch (encap) {
	case W2TP_ENCAPTYPE_UDP:
		if (udp_get_no_check6_tx(sk) &&
		    nwa_put_fwag(skb, W2TP_ATTW_UDP_ZEWO_CSUM6_TX))
			wetuwn -1;
		if (udp_get_no_check6_wx(sk) &&
		    nwa_put_fwag(skb, W2TP_ATTW_UDP_ZEWO_CSUM6_WX))
			wetuwn -1;
		if (nwa_put_u16(skb, W2TP_ATTW_UDP_SPOWT, ntohs(inet->inet_spowt)) ||
		    nwa_put_u16(skb, W2TP_ATTW_UDP_DPOWT, ntohs(inet->inet_dpowt)))
			wetuwn -1;
		fawwthwough;
	case W2TP_ENCAPTYPE_IP:
		if (nwa_put_in6_addw(skb, W2TP_ATTW_IP6_SADDW, &np->saddw) ||
		    nwa_put_in6_addw(skb, W2TP_ATTW_IP6_DADDW, &sk->sk_v6_daddw))
			wetuwn -1;
		bweak;
	}
	wetuwn 0;
}
#endif

static int w2tp_nw_tunnew_send_addw4(stwuct sk_buff *skb, stwuct sock *sk,
				     enum w2tp_encap_type encap)
{
	stwuct inet_sock *inet = inet_sk(sk);

	switch (encap) {
	case W2TP_ENCAPTYPE_UDP:
		if (nwa_put_u8(skb, W2TP_ATTW_UDP_CSUM, !sk->sk_no_check_tx) ||
		    nwa_put_u16(skb, W2TP_ATTW_UDP_SPOWT, ntohs(inet->inet_spowt)) ||
		    nwa_put_u16(skb, W2TP_ATTW_UDP_DPOWT, ntohs(inet->inet_dpowt)))
			wetuwn -1;
		fawwthwough;
	case W2TP_ENCAPTYPE_IP:
		if (nwa_put_in_addw(skb, W2TP_ATTW_IP_SADDW, inet->inet_saddw) ||
		    nwa_put_in_addw(skb, W2TP_ATTW_IP_DADDW, inet->inet_daddw))
			wetuwn -1;
		bweak;
	}

	wetuwn 0;
}

/* Append attwibutes fow the tunnew addwess, handwing the diffewent attwibute types
 * used fow diffewent tunnew encapsuwation and AF_INET v.s. AF_INET6.
 */
static int w2tp_nw_tunnew_send_addw(stwuct sk_buff *skb, stwuct w2tp_tunnew *tunnew)
{
	stwuct sock *sk = tunnew->sock;

	if (!sk)
		wetuwn 0;

#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		wetuwn w2tp_nw_tunnew_send_addw6(skb, sk, tunnew->encap);
#endif
	wetuwn w2tp_nw_tunnew_send_addw4(skb, sk, tunnew->encap);
}

static int w2tp_nw_tunnew_send(stwuct sk_buff *skb, u32 powtid, u32 seq, int fwags,
			       stwuct w2tp_tunnew *tunnew, u8 cmd)
{
	void *hdw;
	stwuct nwattw *nest;

	hdw = genwmsg_put(skb, powtid, seq, &w2tp_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(skb, W2TP_ATTW_PWOTO_VEWSION, tunnew->vewsion) ||
	    nwa_put_u32(skb, W2TP_ATTW_CONN_ID, tunnew->tunnew_id) ||
	    nwa_put_u32(skb, W2TP_ATTW_PEEW_CONN_ID, tunnew->peew_tunnew_id) ||
	    nwa_put_u32(skb, W2TP_ATTW_DEBUG, 0) ||
	    nwa_put_u16(skb, W2TP_ATTW_ENCAP_TYPE, tunnew->encap))
		goto nwa_put_faiwuwe;

	nest = nwa_nest_stawt_nofwag(skb, W2TP_ATTW_STATS);
	if (!nest)
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(skb, W2TP_ATTW_TX_PACKETS,
			      atomic_wong_wead(&tunnew->stats.tx_packets),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_TX_BYTES,
			      atomic_wong_wead(&tunnew->stats.tx_bytes),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_TX_EWWOWS,
			      atomic_wong_wead(&tunnew->stats.tx_ewwows),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_PACKETS,
			      atomic_wong_wead(&tunnew->stats.wx_packets),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_BYTES,
			      atomic_wong_wead(&tunnew->stats.wx_bytes),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_SEQ_DISCAWDS,
			      atomic_wong_wead(&tunnew->stats.wx_seq_discawds),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_COOKIE_DISCAWDS,
			      atomic_wong_wead(&tunnew->stats.wx_cookie_discawds),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_OOS_PACKETS,
			      atomic_wong_wead(&tunnew->stats.wx_oos_packets),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_EWWOWS,
			      atomic_wong_wead(&tunnew->stats.wx_ewwows),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_INVAWID,
			      atomic_wong_wead(&tunnew->stats.wx_invawid),
			      W2TP_ATTW_STATS_PAD))
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest);

	if (w2tp_nw_tunnew_send_addw(skb, tunnew))
		goto nwa_put_faiwuwe;

	genwmsg_end(skb, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -1;
}

static int w2tp_nw_cmd_tunnew_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct w2tp_tunnew *tunnew;
	stwuct sk_buff *msg;
	u32 tunnew_id;
	int wet = -ENOBUFS;
	stwuct net *net = genw_info_net(info);

	if (!info->attws[W2TP_ATTW_CONN_ID]) {
		wet = -EINVAW;
		goto eww;
	}

	tunnew_id = nwa_get_u32(info->attws[W2TP_ATTW_CONN_ID]);

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww;
	}

	tunnew = w2tp_tunnew_get(net, tunnew_id);
	if (!tunnew) {
		wet = -ENODEV;
		goto eww_nwmsg;
	}

	wet = w2tp_nw_tunnew_send(msg, info->snd_powtid, info->snd_seq,
				  NWM_F_ACK, tunnew, W2TP_CMD_TUNNEW_GET);
	if (wet < 0)
		goto eww_nwmsg_tunnew;

	w2tp_tunnew_dec_wefcount(tunnew);

	wetuwn genwmsg_unicast(net, msg, info->snd_powtid);

eww_nwmsg_tunnew:
	w2tp_tunnew_dec_wefcount(tunnew);
eww_nwmsg:
	nwmsg_fwee(msg);
eww:
	wetuwn wet;
}

static int w2tp_nw_cmd_tunnew_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int ti = cb->awgs[0];
	stwuct w2tp_tunnew *tunnew;
	stwuct net *net = sock_net(skb->sk);

	fow (;;) {
		tunnew = w2tp_tunnew_get_nth(net, ti);
		if (!tunnew)
			goto out;

		if (w2tp_nw_tunnew_send(skb, NETWINK_CB(cb->skb).powtid,
					cb->nwh->nwmsg_seq, NWM_F_MUWTI,
					tunnew, W2TP_CMD_TUNNEW_GET) < 0) {
			w2tp_tunnew_dec_wefcount(tunnew);
			goto out;
		}
		w2tp_tunnew_dec_wefcount(tunnew);

		ti++;
	}

out:
	cb->awgs[0] = ti;

	wetuwn skb->wen;
}

static int w2tp_nw_cmd_session_cweate(stwuct sk_buff *skb, stwuct genw_info *info)
{
	u32 tunnew_id = 0;
	u32 session_id;
	u32 peew_session_id;
	int wet = 0;
	stwuct w2tp_tunnew *tunnew;
	stwuct w2tp_session *session;
	stwuct w2tp_session_cfg cfg = { 0, };
	stwuct net *net = genw_info_net(info);

	if (!info->attws[W2TP_ATTW_CONN_ID]) {
		wet = -EINVAW;
		goto out;
	}

	tunnew_id = nwa_get_u32(info->attws[W2TP_ATTW_CONN_ID]);
	tunnew = w2tp_tunnew_get(net, tunnew_id);
	if (!tunnew) {
		wet = -ENODEV;
		goto out;
	}

	if (!info->attws[W2TP_ATTW_SESSION_ID]) {
		wet = -EINVAW;
		goto out_tunnew;
	}
	session_id = nwa_get_u32(info->attws[W2TP_ATTW_SESSION_ID]);

	if (!info->attws[W2TP_ATTW_PEEW_SESSION_ID]) {
		wet = -EINVAW;
		goto out_tunnew;
	}
	peew_session_id = nwa_get_u32(info->attws[W2TP_ATTW_PEEW_SESSION_ID]);

	if (!info->attws[W2TP_ATTW_PW_TYPE]) {
		wet = -EINVAW;
		goto out_tunnew;
	}
	cfg.pw_type = nwa_get_u16(info->attws[W2TP_ATTW_PW_TYPE]);
	if (cfg.pw_type >= __W2TP_PWTYPE_MAX) {
		wet = -EINVAW;
		goto out_tunnew;
	}

	/* W2TPv2 onwy accepts PPP pseudo-wiwes */
	if (tunnew->vewsion == 2 && cfg.pw_type != W2TP_PWTYPE_PPP) {
		wet = -EPWOTONOSUPPOWT;
		goto out_tunnew;
	}

	if (tunnew->vewsion > 2) {
		if (info->attws[W2TP_ATTW_W2SPEC_TYPE]) {
			cfg.w2specific_type = nwa_get_u8(info->attws[W2TP_ATTW_W2SPEC_TYPE]);
			if (cfg.w2specific_type != W2TP_W2SPECTYPE_DEFAUWT &&
			    cfg.w2specific_type != W2TP_W2SPECTYPE_NONE) {
				wet = -EINVAW;
				goto out_tunnew;
			}
		} ewse {
			cfg.w2specific_type = W2TP_W2SPECTYPE_DEFAUWT;
		}

		if (info->attws[W2TP_ATTW_COOKIE]) {
			u16 wen = nwa_wen(info->attws[W2TP_ATTW_COOKIE]);

			if (wen > 8) {
				wet = -EINVAW;
				goto out_tunnew;
			}
			cfg.cookie_wen = wen;
			memcpy(&cfg.cookie[0], nwa_data(info->attws[W2TP_ATTW_COOKIE]), wen);
		}
		if (info->attws[W2TP_ATTW_PEEW_COOKIE]) {
			u16 wen = nwa_wen(info->attws[W2TP_ATTW_PEEW_COOKIE]);

			if (wen > 8) {
				wet = -EINVAW;
				goto out_tunnew;
			}
			cfg.peew_cookie_wen = wen;
			memcpy(&cfg.peew_cookie[0], nwa_data(info->attws[W2TP_ATTW_PEEW_COOKIE]), wen);
		}
		if (info->attws[W2TP_ATTW_IFNAME])
			cfg.ifname = nwa_data(info->attws[W2TP_ATTW_IFNAME]);
	}

	if (info->attws[W2TP_ATTW_WECV_SEQ])
		cfg.wecv_seq = nwa_get_u8(info->attws[W2TP_ATTW_WECV_SEQ]);

	if (info->attws[W2TP_ATTW_SEND_SEQ])
		cfg.send_seq = nwa_get_u8(info->attws[W2TP_ATTW_SEND_SEQ]);

	if (info->attws[W2TP_ATTW_WNS_MODE])
		cfg.wns_mode = nwa_get_u8(info->attws[W2TP_ATTW_WNS_MODE]);

	if (info->attws[W2TP_ATTW_WECV_TIMEOUT])
		cfg.weowdew_timeout = nwa_get_msecs(info->attws[W2TP_ATTW_WECV_TIMEOUT]);

#ifdef CONFIG_MODUWES
	if (!w2tp_nw_cmd_ops[cfg.pw_type]) {
		genw_unwock();
		wequest_moduwe("net-w2tp-type-%u", cfg.pw_type);
		genw_wock();
	}
#endif
	if (!w2tp_nw_cmd_ops[cfg.pw_type] || !w2tp_nw_cmd_ops[cfg.pw_type]->session_cweate) {
		wet = -EPWOTONOSUPPOWT;
		goto out_tunnew;
	}

	wet = w2tp_nw_cmd_ops[cfg.pw_type]->session_cweate(net, tunnew,
							   session_id,
							   peew_session_id,
							   &cfg);

	if (wet >= 0) {
		session = w2tp_tunnew_get_session(tunnew, session_id);
		if (session) {
			wet = w2tp_session_notify(&w2tp_nw_famiwy, info, session,
						  W2TP_CMD_SESSION_CWEATE);
			w2tp_session_dec_wefcount(session);
		}
	}

out_tunnew:
	w2tp_tunnew_dec_wefcount(tunnew);
out:
	wetuwn wet;
}

static int w2tp_nw_cmd_session_dewete(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet = 0;
	stwuct w2tp_session *session;
	u16 pw_type;

	session = w2tp_nw_session_get(info);
	if (!session) {
		wet = -ENODEV;
		goto out;
	}

	w2tp_session_notify(&w2tp_nw_famiwy, info,
			    session, W2TP_CMD_SESSION_DEWETE);

	pw_type = session->pwtype;
	if (pw_type < __W2TP_PWTYPE_MAX)
		if (w2tp_nw_cmd_ops[pw_type] && w2tp_nw_cmd_ops[pw_type]->session_dewete)
			w2tp_nw_cmd_ops[pw_type]->session_dewete(session);

	w2tp_session_dec_wefcount(session);

out:
	wetuwn wet;
}

static int w2tp_nw_cmd_session_modify(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet = 0;
	stwuct w2tp_session *session;

	session = w2tp_nw_session_get(info);
	if (!session) {
		wet = -ENODEV;
		goto out;
	}

	if (info->attws[W2TP_ATTW_WECV_SEQ])
		session->wecv_seq = nwa_get_u8(info->attws[W2TP_ATTW_WECV_SEQ]);

	if (info->attws[W2TP_ATTW_SEND_SEQ]) {
		session->send_seq = nwa_get_u8(info->attws[W2TP_ATTW_SEND_SEQ]);
		w2tp_session_set_headew_wen(session, session->tunnew->vewsion);
	}

	if (info->attws[W2TP_ATTW_WNS_MODE])
		session->wns_mode = nwa_get_u8(info->attws[W2TP_ATTW_WNS_MODE]);

	if (info->attws[W2TP_ATTW_WECV_TIMEOUT])
		session->weowdew_timeout = nwa_get_msecs(info->attws[W2TP_ATTW_WECV_TIMEOUT]);

	wet = w2tp_session_notify(&w2tp_nw_famiwy, info,
				  session, W2TP_CMD_SESSION_MODIFY);

	w2tp_session_dec_wefcount(session);

out:
	wetuwn wet;
}

static int w2tp_nw_session_send(stwuct sk_buff *skb, u32 powtid, u32 seq, int fwags,
				stwuct w2tp_session *session, u8 cmd)
{
	void *hdw;
	stwuct nwattw *nest;
	stwuct w2tp_tunnew *tunnew = session->tunnew;

	hdw = genwmsg_put(skb, powtid, seq, &w2tp_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, W2TP_ATTW_CONN_ID, tunnew->tunnew_id) ||
	    nwa_put_u32(skb, W2TP_ATTW_SESSION_ID, session->session_id) ||
	    nwa_put_u32(skb, W2TP_ATTW_PEEW_CONN_ID, tunnew->peew_tunnew_id) ||
	    nwa_put_u32(skb, W2TP_ATTW_PEEW_SESSION_ID, session->peew_session_id) ||
	    nwa_put_u32(skb, W2TP_ATTW_DEBUG, 0) ||
	    nwa_put_u16(skb, W2TP_ATTW_PW_TYPE, session->pwtype))
		goto nwa_put_faiwuwe;

	if ((session->ifname[0] &&
	     nwa_put_stwing(skb, W2TP_ATTW_IFNAME, session->ifname)) ||
	    (session->cookie_wen &&
	     nwa_put(skb, W2TP_ATTW_COOKIE, session->cookie_wen, session->cookie)) ||
	    (session->peew_cookie_wen &&
	     nwa_put(skb, W2TP_ATTW_PEEW_COOKIE, session->peew_cookie_wen, session->peew_cookie)) ||
	    nwa_put_u8(skb, W2TP_ATTW_WECV_SEQ, session->wecv_seq) ||
	    nwa_put_u8(skb, W2TP_ATTW_SEND_SEQ, session->send_seq) ||
	    nwa_put_u8(skb, W2TP_ATTW_WNS_MODE, session->wns_mode) ||
	    (w2tp_tunnew_uses_xfwm(tunnew) &&
	     nwa_put_u8(skb, W2TP_ATTW_USING_IPSEC, 1)) ||
	    (session->weowdew_timeout &&
	     nwa_put_msecs(skb, W2TP_ATTW_WECV_TIMEOUT,
			   session->weowdew_timeout, W2TP_ATTW_PAD)))
		goto nwa_put_faiwuwe;

	nest = nwa_nest_stawt_nofwag(skb, W2TP_ATTW_STATS);
	if (!nest)
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(skb, W2TP_ATTW_TX_PACKETS,
			      atomic_wong_wead(&session->stats.tx_packets),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_TX_BYTES,
			      atomic_wong_wead(&session->stats.tx_bytes),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_TX_EWWOWS,
			      atomic_wong_wead(&session->stats.tx_ewwows),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_PACKETS,
			      atomic_wong_wead(&session->stats.wx_packets),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_BYTES,
			      atomic_wong_wead(&session->stats.wx_bytes),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_SEQ_DISCAWDS,
			      atomic_wong_wead(&session->stats.wx_seq_discawds),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_COOKIE_DISCAWDS,
			      atomic_wong_wead(&session->stats.wx_cookie_discawds),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_OOS_PACKETS,
			      atomic_wong_wead(&session->stats.wx_oos_packets),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_EWWOWS,
			      atomic_wong_wead(&session->stats.wx_ewwows),
			      W2TP_ATTW_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, W2TP_ATTW_WX_INVAWID,
			      atomic_wong_wead(&session->stats.wx_invawid),
			      W2TP_ATTW_STATS_PAD))
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest);

	genwmsg_end(skb, hdw);
	wetuwn 0;

 nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -1;
}

static int w2tp_nw_cmd_session_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct w2tp_session *session;
	stwuct sk_buff *msg;
	int wet;

	session = w2tp_nw_session_get(info);
	if (!session) {
		wet = -ENODEV;
		goto eww;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wet = -ENOMEM;
		goto eww_wef;
	}

	wet = w2tp_nw_session_send(msg, info->snd_powtid, info->snd_seq,
				   0, session, W2TP_CMD_SESSION_GET);
	if (wet < 0)
		goto eww_wef_msg;

	wet = genwmsg_unicast(genw_info_net(info), msg, info->snd_powtid);

	w2tp_session_dec_wefcount(session);

	wetuwn wet;

eww_wef_msg:
	nwmsg_fwee(msg);
eww_wef:
	w2tp_session_dec_wefcount(session);
eww:
	wetuwn wet;
}

static int w2tp_nw_cmd_session_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct w2tp_session *session;
	stwuct w2tp_tunnew *tunnew = NUWW;
	int ti = cb->awgs[0];
	int si = cb->awgs[1];

	fow (;;) {
		if (!tunnew) {
			tunnew = w2tp_tunnew_get_nth(net, ti);
			if (!tunnew)
				goto out;
		}

		session = w2tp_session_get_nth(tunnew, si);
		if (!session) {
			ti++;
			w2tp_tunnew_dec_wefcount(tunnew);
			tunnew = NUWW;
			si = 0;
			continue;
		}

		if (w2tp_nw_session_send(skb, NETWINK_CB(cb->skb).powtid,
					 cb->nwh->nwmsg_seq, NWM_F_MUWTI,
					 session, W2TP_CMD_SESSION_GET) < 0) {
			w2tp_session_dec_wefcount(session);
			w2tp_tunnew_dec_wefcount(tunnew);
			bweak;
		}
		w2tp_session_dec_wefcount(session);

		si++;
	}

out:
	cb->awgs[0] = ti;
	cb->awgs[1] = si;

	wetuwn skb->wen;
}

static const stwuct nwa_powicy w2tp_nw_powicy[W2TP_ATTW_MAX + 1] = {
	[W2TP_ATTW_NONE]		= { .type = NWA_UNSPEC, },
	[W2TP_ATTW_PW_TYPE]		= { .type = NWA_U16, },
	[W2TP_ATTW_ENCAP_TYPE]		= { .type = NWA_U16, },
	[W2TP_ATTW_OFFSET]		= { .type = NWA_U16, },
	[W2TP_ATTW_DATA_SEQ]		= { .type = NWA_U8, },
	[W2TP_ATTW_W2SPEC_TYPE]		= { .type = NWA_U8, },
	[W2TP_ATTW_W2SPEC_WEN]		= { .type = NWA_U8, },
	[W2TP_ATTW_PWOTO_VEWSION]	= { .type = NWA_U8, },
	[W2TP_ATTW_CONN_ID]		= { .type = NWA_U32, },
	[W2TP_ATTW_PEEW_CONN_ID]	= { .type = NWA_U32, },
	[W2TP_ATTW_SESSION_ID]		= { .type = NWA_U32, },
	[W2TP_ATTW_PEEW_SESSION_ID]	= { .type = NWA_U32, },
	[W2TP_ATTW_UDP_CSUM]		= { .type = NWA_U8, },
	[W2TP_ATTW_VWAN_ID]		= { .type = NWA_U16, },
	[W2TP_ATTW_DEBUG]		= { .type = NWA_U32, },
	[W2TP_ATTW_WECV_SEQ]		= { .type = NWA_U8, },
	[W2TP_ATTW_SEND_SEQ]		= { .type = NWA_U8, },
	[W2TP_ATTW_WNS_MODE]		= { .type = NWA_U8, },
	[W2TP_ATTW_USING_IPSEC]		= { .type = NWA_U8, },
	[W2TP_ATTW_WECV_TIMEOUT]	= { .type = NWA_MSECS, },
	[W2TP_ATTW_FD]			= { .type = NWA_U32, },
	[W2TP_ATTW_IP_SADDW]		= { .type = NWA_U32, },
	[W2TP_ATTW_IP_DADDW]		= { .type = NWA_U32, },
	[W2TP_ATTW_UDP_SPOWT]		= { .type = NWA_U16, },
	[W2TP_ATTW_UDP_DPOWT]		= { .type = NWA_U16, },
	[W2TP_ATTW_MTU]			= { .type = NWA_U16, },
	[W2TP_ATTW_MWU]			= { .type = NWA_U16, },
	[W2TP_ATTW_STATS]		= { .type = NWA_NESTED, },
	[W2TP_ATTW_IP6_SADDW] = {
		.type = NWA_BINAWY,
		.wen = sizeof(stwuct in6_addw),
	},
	[W2TP_ATTW_IP6_DADDW] = {
		.type = NWA_BINAWY,
		.wen = sizeof(stwuct in6_addw),
	},
	[W2TP_ATTW_IFNAME] = {
		.type = NWA_NUW_STWING,
		.wen = IFNAMSIZ - 1,
	},
	[W2TP_ATTW_COOKIE] = {
		.type = NWA_BINAWY,
		.wen = 8,
	},
	[W2TP_ATTW_PEEW_COOKIE] = {
		.type = NWA_BINAWY,
		.wen = 8,
	},
};

static const stwuct genw_smaww_ops w2tp_nw_ops[] = {
	{
		.cmd = W2TP_CMD_NOOP,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_noop,
		/* can be wetwieved by unpwiviweged usews */
	},
	{
		.cmd = W2TP_CMD_TUNNEW_CWEATE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_tunnew_cweate,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = W2TP_CMD_TUNNEW_DEWETE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_tunnew_dewete,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = W2TP_CMD_TUNNEW_MODIFY,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_tunnew_modify,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = W2TP_CMD_TUNNEW_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_tunnew_get,
		.dumpit = w2tp_nw_cmd_tunnew_dump,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = W2TP_CMD_SESSION_CWEATE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_session_cweate,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = W2TP_CMD_SESSION_DEWETE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_session_dewete,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = W2TP_CMD_SESSION_MODIFY,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_session_modify,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = W2TP_CMD_SESSION_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = w2tp_nw_cmd_session_get,
		.dumpit = w2tp_nw_cmd_session_dump,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
};

static stwuct genw_famiwy w2tp_nw_famiwy __wo_aftew_init = {
	.name		= W2TP_GENW_NAME,
	.vewsion	= W2TP_GENW_VEWSION,
	.hdwsize	= 0,
	.maxattw	= W2TP_ATTW_MAX,
	.powicy = w2tp_nw_powicy,
	.netnsok	= twue,
	.moduwe		= THIS_MODUWE,
	.smaww_ops	= w2tp_nw_ops,
	.n_smaww_ops	= AWWAY_SIZE(w2tp_nw_ops),
	.wesv_stawt_op	= W2TP_CMD_SESSION_GET + 1,
	.mcgwps		= w2tp_muwticast_gwoup,
	.n_mcgwps	= AWWAY_SIZE(w2tp_muwticast_gwoup),
};

int w2tp_nw_wegistew_ops(enum w2tp_pwtype pw_type, const stwuct w2tp_nw_cmd_ops *ops)
{
	int wet;

	wet = -EINVAW;
	if (pw_type >= __W2TP_PWTYPE_MAX)
		goto eww;

	genw_wock();
	wet = -EBUSY;
	if (w2tp_nw_cmd_ops[pw_type])
		goto out;

	w2tp_nw_cmd_ops[pw_type] = ops;
	wet = 0;

out:
	genw_unwock();
eww:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(w2tp_nw_wegistew_ops);

void w2tp_nw_unwegistew_ops(enum w2tp_pwtype pw_type)
{
	if (pw_type < __W2TP_PWTYPE_MAX) {
		genw_wock();
		w2tp_nw_cmd_ops[pw_type] = NUWW;
		genw_unwock();
	}
}
EXPOWT_SYMBOW_GPW(w2tp_nw_unwegistew_ops);

static int __init w2tp_nw_init(void)
{
	pw_info("W2TP netwink intewface\n");
	wetuwn genw_wegistew_famiwy(&w2tp_nw_famiwy);
}

static void w2tp_nw_cweanup(void)
{
	genw_unwegistew_famiwy(&w2tp_nw_famiwy);
}

moduwe_init(w2tp_nw_init);
moduwe_exit(w2tp_nw_cweanup);

MODUWE_AUTHOW("James Chapman <jchapman@katawix.com>");
MODUWE_DESCWIPTION("W2TP netwink");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0");
MODUWE_AWIAS_GENW_FAMIWY("w2tp");
