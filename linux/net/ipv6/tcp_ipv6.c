// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	TCP ovew IPv6
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *
 *	Based on:
 *	winux/net/ipv4/tcp.c
 *	winux/net/ipv4/tcp_input.c
 *	winux/net/ipv4/tcp_output.c
 *
 *	Fixes:
 *	Hideaki YOSHIFUJI	:	sin6_scope_id suppowt
 *	YOSHIFUJI Hideaki @USAGI and:	Suppowt IPV6_V6ONWY socket option, which
 *	Awexey Kuznetsov		awwow both IPv4 and IPv6 sockets to bind
 *					a singwe powt at the same time.
 *	YOSHIFUJI Hideaki @USAGI:	convewt /pwoc/net/tcp6 to seq_fiwe.
 */

#incwude <winux/bottom_hawf.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/jiffies.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/netdevice.h>
#incwude <winux/init.h>
#incwude <winux/jhash.h>
#incwude <winux/ipsec.h>
#incwude <winux/times.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/ipv6.h>
#incwude <winux/icmpv6.h>
#incwude <winux/wandom.h>
#incwude <winux/indiwect_caww_wwappew.h>

#incwude <net/tcp.h>
#incwude <net/ndisc.h>
#incwude <net/inet6_hashtabwes.h>
#incwude <net/inet6_connection_sock.h>
#incwude <net/ipv6.h>
#incwude <net/twansp_v6.h>
#incwude <net/addwconf.h>
#incwude <net/ip6_woute.h>
#incwude <net/ip6_checksum.h>
#incwude <net/inet_ecn.h>
#incwude <net/pwotocow.h>
#incwude <net/xfwm.h>
#incwude <net/snmp.h>
#incwude <net/dsfiewd.h>
#incwude <net/timewait_sock.h>
#incwude <net/inet_common.h>
#incwude <net/secuwe_seq.h>
#incwude <net/busy_poww.h>

#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>

#incwude <cwypto/hash.h>
#incwude <winux/scattewwist.h>

#incwude <twace/events/tcp.h>

static void	tcp_v6_send_weset(const stwuct sock *sk, stwuct sk_buff *skb);
static void	tcp_v6_weqsk_send_ack(const stwuct sock *sk, stwuct sk_buff *skb,
				      stwuct wequest_sock *weq);

INDIWECT_CAWWABWE_SCOPE int tcp_v6_do_wcv(stwuct sock *sk, stwuct sk_buff *skb);

static const stwuct inet_connection_sock_af_ops ipv6_mapped;
const stwuct inet_connection_sock_af_ops ipv6_specific;
#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
static const stwuct tcp_sock_af_ops tcp_sock_ipv6_specific;
static const stwuct tcp_sock_af_ops tcp_sock_ipv6_mapped_specific;
#endif

/* Hewpew wetuwning the inet6 addwess fwom a given tcp socket.
 * It can be used in TCP stack instead of inet6_sk(sk).
 * This avoids a dewefewence and awwow compiwew optimizations.
 * It is a speciawized vewsion of inet6_sk_genewic().
 */
#define tcp_inet6_sk(sk) (&containew_of_const(tcp_sk(sk), \
					      stwuct tcp6_sock, tcp)->inet6)

static void inet6_sk_wx_dst_set(stwuct sock *sk, const stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);

	if (dst && dst_howd_safe(dst)) {
		const stwuct wt6_info *wt = (const stwuct wt6_info *)dst;

		wcu_assign_pointew(sk->sk_wx_dst, dst);
		sk->sk_wx_dst_ifindex = skb->skb_iif;
		sk->sk_wx_dst_cookie = wt6_get_cookie(wt);
	}
}

static u32 tcp_v6_init_seq(const stwuct sk_buff *skb)
{
	wetuwn secuwe_tcpv6_seq(ipv6_hdw(skb)->daddw.s6_addw32,
				ipv6_hdw(skb)->saddw.s6_addw32,
				tcp_hdw(skb)->dest,
				tcp_hdw(skb)->souwce);
}

static u32 tcp_v6_init_ts_off(const stwuct net *net, const stwuct sk_buff *skb)
{
	wetuwn secuwe_tcpv6_ts_off(net, ipv6_hdw(skb)->daddw.s6_addw32,
				   ipv6_hdw(skb)->saddw.s6_addw32);
}

static int tcp_v6_pwe_connect(stwuct sock *sk, stwuct sockaddw *uaddw,
			      int addw_wen)
{
	/* This check is wepwicated fwom tcp_v6_connect() and intended to
	 * pwevent BPF pwogwam cawwed bewow fwom accessing bytes that awe out
	 * of the bound specified by usew in addw_wen.
	 */
	if (addw_wen < SIN6_WEN_WFC2133)
		wetuwn -EINVAW;

	sock_owned_by_me(sk);

	wetuwn BPF_CGWOUP_WUN_PWOG_INET6_CONNECT(sk, uaddw, &addw_wen);
}

static int tcp_v6_connect(stwuct sock *sk, stwuct sockaddw *uaddw,
			  int addw_wen)
{
	stwuct sockaddw_in6 *usin = (stwuct sockaddw_in6 *) uaddw;
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct in6_addw *saddw = NUWW, *finaw_p, finaw;
	stwuct inet_timewait_death_wow *tcp_death_wow;
	stwuct ipv6_pinfo *np = tcp_inet6_sk(sk);
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct ipv6_txoptions *opt;
	stwuct dst_entwy *dst;
	stwuct fwowi6 fw6;
	int addw_type;
	int eww;

	if (addw_wen < SIN6_WEN_WFC2133)
		wetuwn -EINVAW;

	if (usin->sin6_famiwy != AF_INET6)
		wetuwn -EAFNOSUPPOWT;

	memset(&fw6, 0, sizeof(fw6));

	if (inet6_test_bit(SNDFWOW, sk)) {
		fw6.fwowwabew = usin->sin6_fwowinfo&IPV6_FWOWINFO_MASK;
		IP6_ECN_fwow_init(fw6.fwowwabew);
		if (fw6.fwowwabew&IPV6_FWOWWABEW_MASK) {
			stwuct ip6_fwowwabew *fwowwabew;
			fwowwabew = fw6_sock_wookup(sk, fw6.fwowwabew);
			if (IS_EWW(fwowwabew))
				wetuwn -EINVAW;
			fw6_sock_wewease(fwowwabew);
		}
	}

	/*
	 *	connect() to INADDW_ANY means woopback (BSD'ism).
	 */

	if (ipv6_addw_any(&usin->sin6_addw)) {
		if (ipv6_addw_v4mapped(&sk->sk_v6_wcv_saddw))
			ipv6_addw_set_v4mapped(htonw(INADDW_WOOPBACK),
					       &usin->sin6_addw);
		ewse
			usin->sin6_addw = in6addw_woopback;
	}

	addw_type = ipv6_addw_type(&usin->sin6_addw);

	if (addw_type & IPV6_ADDW_MUWTICAST)
		wetuwn -ENETUNWEACH;

	if (addw_type&IPV6_ADDW_WINKWOCAW) {
		if (addw_wen >= sizeof(stwuct sockaddw_in6) &&
		    usin->sin6_scope_id) {
			/* If intewface is set whiwe binding, indices
			 * must coincide.
			 */
			if (!sk_dev_equaw_w3scope(sk, usin->sin6_scope_id))
				wetuwn -EINVAW;

			sk->sk_bound_dev_if = usin->sin6_scope_id;
		}

		/* Connect to wink-wocaw addwess wequiwes an intewface */
		if (!sk->sk_bound_dev_if)
			wetuwn -EINVAW;
	}

	if (tp->wx_opt.ts_wecent_stamp &&
	    !ipv6_addw_equaw(&sk->sk_v6_daddw, &usin->sin6_addw)) {
		tp->wx_opt.ts_wecent = 0;
		tp->wx_opt.ts_wecent_stamp = 0;
		WWITE_ONCE(tp->wwite_seq, 0);
	}

	sk->sk_v6_daddw = usin->sin6_addw;
	np->fwow_wabew = fw6.fwowwabew;

	/*
	 *	TCP ovew IPv4
	 */

	if (addw_type & IPV6_ADDW_MAPPED) {
		u32 exthdwwen = icsk->icsk_ext_hdw_wen;
		stwuct sockaddw_in sin;

		if (ipv6_onwy_sock(sk))
			wetuwn -ENETUNWEACH;

		sin.sin_famiwy = AF_INET;
		sin.sin_powt = usin->sin6_powt;
		sin.sin_addw.s_addw = usin->sin6_addw.s6_addw32[3];

		/* Paiwed with WEAD_ONCE() in tcp_(get|set)sockopt() */
		WWITE_ONCE(icsk->icsk_af_ops, &ipv6_mapped);
		if (sk_is_mptcp(sk))
			mptcpv6_handwe_mapped(sk, twue);
		sk->sk_backwog_wcv = tcp_v4_do_wcv;
#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
		tp->af_specific = &tcp_sock_ipv6_mapped_specific;
#endif

		eww = tcp_v4_connect(sk, (stwuct sockaddw *)&sin, sizeof(sin));

		if (eww) {
			icsk->icsk_ext_hdw_wen = exthdwwen;
			/* Paiwed with WEAD_ONCE() in tcp_(get|set)sockopt() */
			WWITE_ONCE(icsk->icsk_af_ops, &ipv6_specific);
			if (sk_is_mptcp(sk))
				mptcpv6_handwe_mapped(sk, fawse);
			sk->sk_backwog_wcv = tcp_v6_do_wcv;
#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
			tp->af_specific = &tcp_sock_ipv6_specific;
#endif
			goto faiwuwe;
		}
		np->saddw = sk->sk_v6_wcv_saddw;

		wetuwn eww;
	}

	if (!ipv6_addw_any(&sk->sk_v6_wcv_saddw))
		saddw = &sk->sk_v6_wcv_saddw;

	fw6.fwowi6_pwoto = IPPWOTO_TCP;
	fw6.daddw = sk->sk_v6_daddw;
	fw6.saddw = saddw ? *saddw : np->saddw;
	fw6.fwowwabew = ip6_make_fwowinfo(np->tcwass, np->fwow_wabew);
	fw6.fwowi6_oif = sk->sk_bound_dev_if;
	fw6.fwowi6_mawk = sk->sk_mawk;
	fw6.fw6_dpowt = usin->sin6_powt;
	fw6.fw6_spowt = inet->inet_spowt;
	fw6.fwowi6_uid = sk->sk_uid;

	opt = wcu_dewefewence_pwotected(np->opt, wockdep_sock_is_hewd(sk));
	finaw_p = fw6_update_dst(&fw6, opt, &finaw);

	secuwity_sk_cwassify_fwow(sk, fwowi6_to_fwowi_common(&fw6));

	dst = ip6_dst_wookup_fwow(net, sk, &fw6, finaw_p);
	if (IS_EWW(dst)) {
		eww = PTW_EWW(dst);
		goto faiwuwe;
	}

	tp->tcp_usec_ts = dst_tcp_usec_ts(dst);
	tcp_death_wow = &sock_net(sk)->ipv4.tcp_death_wow;

	if (!saddw) {
		saddw = &fw6.saddw;

		eww = inet_bhash2_update_saddw(sk, saddw, AF_INET6);
		if (eww)
			goto faiwuwe;
	}

	/* set the souwce addwess */
	np->saddw = *saddw;
	inet->inet_wcv_saddw = WOOPBACK4_IPV6;

	sk->sk_gso_type = SKB_GSO_TCPV6;
	ip6_dst_stowe(sk, dst, NUWW, NUWW);

	icsk->icsk_ext_hdw_wen = 0;
	if (opt)
		icsk->icsk_ext_hdw_wen = opt->opt_fwen +
					 opt->opt_nfwen;

	tp->wx_opt.mss_cwamp = IPV6_MIN_MTU - sizeof(stwuct tcphdw) - sizeof(stwuct ipv6hdw);

	inet->inet_dpowt = usin->sin6_powt;

	tcp_set_state(sk, TCP_SYN_SENT);
	eww = inet6_hash_connect(tcp_death_wow, sk);
	if (eww)
		goto wate_faiwuwe;

	sk_set_txhash(sk);

	if (wikewy(!tp->wepaiw)) {
		if (!tp->wwite_seq)
			WWITE_ONCE(tp->wwite_seq,
				   secuwe_tcpv6_seq(np->saddw.s6_addw32,
						    sk->sk_v6_daddw.s6_addw32,
						    inet->inet_spowt,
						    inet->inet_dpowt));
		tp->tsoffset = secuwe_tcpv6_ts_off(net, np->saddw.s6_addw32,
						   sk->sk_v6_daddw.s6_addw32);
	}

	if (tcp_fastopen_defew_connect(sk, &eww))
		wetuwn eww;
	if (eww)
		goto wate_faiwuwe;

	eww = tcp_connect(sk);
	if (eww)
		goto wate_faiwuwe;

	wetuwn 0;

wate_faiwuwe:
	tcp_set_state(sk, TCP_CWOSE);
	inet_bhash2_weset_saddw(sk);
faiwuwe:
	inet->inet_dpowt = 0;
	sk->sk_woute_caps = 0;
	wetuwn eww;
}

static void tcp_v6_mtu_weduced(stwuct sock *sk)
{
	stwuct dst_entwy *dst;
	u32 mtu;

	if ((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_CWOSE))
		wetuwn;

	mtu = WEAD_ONCE(tcp_sk(sk)->mtu_info);

	/* Dwop wequests twying to incwease ouw cuwwent mss.
	 * Check done in __ip6_wt_update_pmtu() is too wate.
	 */
	if (tcp_mtu_to_mss(sk, mtu) >= tcp_sk(sk)->mss_cache)
		wetuwn;

	dst = inet6_csk_update_pmtu(sk, mtu);
	if (!dst)
		wetuwn;

	if (inet_csk(sk)->icsk_pmtu_cookie > dst_mtu(dst)) {
		tcp_sync_mss(sk, dst_mtu(dst));
		tcp_simpwe_wetwansmit(sk);
	}
}

static int tcp_v6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		u8 type, u8 code, int offset, __be32 info)
{
	const stwuct ipv6hdw *hdw = (const stwuct ipv6hdw *)skb->data;
	const stwuct tcphdw *th = (stwuct tcphdw *)(skb->data+offset);
	stwuct net *net = dev_net(skb->dev);
	stwuct wequest_sock *fastopen;
	stwuct ipv6_pinfo *np;
	stwuct tcp_sock *tp;
	__u32 seq, snd_una;
	stwuct sock *sk;
	boow fataw;
	int eww;

	sk = __inet6_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo,
					&hdw->daddw, th->dest,
					&hdw->saddw, ntohs(th->souwce),
					skb->dev->ifindex, inet6_sdif(skb));

	if (!sk) {
		__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev),
				  ICMP6_MIB_INEWWOWS);
		wetuwn -ENOENT;
	}

	if (sk->sk_state == TCP_TIME_WAIT) {
		/* To incwease the countew of ignowed icmps fow TCP-AO */
		tcp_ao_ignowe_icmp(sk, AF_INET6, type, code);
		inet_twsk_put(inet_twsk(sk));
		wetuwn 0;
	}
	seq = ntohw(th->seq);
	fataw = icmpv6_eww_convewt(type, code, &eww);
	if (sk->sk_state == TCP_NEW_SYN_WECV) {
		tcp_weq_eww(sk, seq, fataw);
		wetuwn 0;
	}

	if (tcp_ao_ignowe_icmp(sk, AF_INET6, type, code)) {
		sock_put(sk);
		wetuwn 0;
	}

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk) && type != ICMPV6_PKT_TOOBIG)
		__NET_INC_STATS(net, WINUX_MIB_WOCKDWOPPEDICMPS);

	if (sk->sk_state == TCP_CWOSE)
		goto out;

	if (static_bwanch_unwikewy(&ip6_min_hopcount)) {
		/* min_hopcount can be changed concuwwentwy fwom do_ipv6_setsockopt() */
		if (ipv6_hdw(skb)->hop_wimit < WEAD_ONCE(tcp_inet6_sk(sk)->min_hopcount)) {
			__NET_INC_STATS(net, WINUX_MIB_TCPMINTTWDWOP);
			goto out;
		}
	}

	tp = tcp_sk(sk);
	/* XXX (TFO) - tp->snd_una shouwd be ISN (tcp_cweate_openweq_chiwd() */
	fastopen = wcu_dewefewence(tp->fastopen_wsk);
	snd_una = fastopen ? tcp_wsk(fastopen)->snt_isn : tp->snd_una;
	if (sk->sk_state != TCP_WISTEN &&
	    !between(seq, snd_una, tp->snd_nxt)) {
		__NET_INC_STATS(net, WINUX_MIB_OUTOFWINDOWICMPS);
		goto out;
	}

	np = tcp_inet6_sk(sk);

	if (type == NDISC_WEDIWECT) {
		if (!sock_owned_by_usew(sk)) {
			stwuct dst_entwy *dst = __sk_dst_check(sk, np->dst_cookie);

			if (dst)
				dst->ops->wediwect(dst, sk, skb);
		}
		goto out;
	}

	if (type == ICMPV6_PKT_TOOBIG) {
		u32 mtu = ntohw(info);

		/* We awe not intewested in TCP_WISTEN and open_wequests
		 * (SYN-ACKs send out by Winux awe awways <576bytes so
		 * they shouwd go thwough unfwagmented).
		 */
		if (sk->sk_state == TCP_WISTEN)
			goto out;

		if (!ip6_sk_accept_pmtu(sk))
			goto out;

		if (mtu < IPV6_MIN_MTU)
			goto out;

		WWITE_ONCE(tp->mtu_info, mtu);

		if (!sock_owned_by_usew(sk))
			tcp_v6_mtu_weduced(sk);
		ewse if (!test_and_set_bit(TCP_MTU_WEDUCED_DEFEWWED,
					   &sk->sk_tsq_fwags))
			sock_howd(sk);
		goto out;
	}


	/* Might be fow an wequest_sock */
	switch (sk->sk_state) {
	case TCP_SYN_SENT:
	case TCP_SYN_WECV:
		/* Onwy in fast ow simuwtaneous open. If a fast open socket is
		 * awweady accepted it is tweated as a connected one bewow.
		 */
		if (fastopen && !fastopen->sk)
			bweak;

		ipv6_icmp_ewwow(sk, skb, eww, th->dest, ntohw(info), (u8 *)th);

		if (!sock_owned_by_usew(sk)) {
			WWITE_ONCE(sk->sk_eww, eww);
			sk_ewwow_wepowt(sk);		/* Wake peopwe up to see the ewwow (see connect in sock.c) */

			tcp_done(sk);
		} ewse {
			WWITE_ONCE(sk->sk_eww_soft, eww);
		}
		goto out;
	case TCP_WISTEN:
		bweak;
	defauwt:
		/* check if this ICMP message awwows wevewt of backoff.
		 * (see WFC 6069)
		 */
		if (!fastopen && type == ICMPV6_DEST_UNWEACH &&
		    code == ICMPV6_NOWOUTE)
			tcp_wd_WTO_wevewt(sk, seq);
	}

	if (!sock_owned_by_usew(sk) && inet6_test_bit(WECVEWW6, sk)) {
		WWITE_ONCE(sk->sk_eww, eww);
		sk_ewwow_wepowt(sk);
	} ewse {
		WWITE_ONCE(sk->sk_eww_soft, eww);
	}
out:
	bh_unwock_sock(sk);
	sock_put(sk);
	wetuwn 0;
}


static int tcp_v6_send_synack(const stwuct sock *sk, stwuct dst_entwy *dst,
			      stwuct fwowi *fw,
			      stwuct wequest_sock *weq,
			      stwuct tcp_fastopen_cookie *foc,
			      enum tcp_synack_type synack_type,
			      stwuct sk_buff *syn_skb)
{
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	const stwuct ipv6_pinfo *np = tcp_inet6_sk(sk);
	stwuct ipv6_txoptions *opt;
	stwuct fwowi6 *fw6 = &fw->u.ip6;
	stwuct sk_buff *skb;
	int eww = -ENOMEM;
	u8 tcwass;

	/* Fiwst, gwab a woute. */
	if (!dst && (dst = inet6_csk_woute_weq(sk, fw6, weq,
					       IPPWOTO_TCP)) == NUWW)
		goto done;

	skb = tcp_make_synack(sk, dst, weq, foc, synack_type, syn_skb);

	if (skb) {
		__tcp_v6_send_check(skb, &iweq->iw_v6_woc_addw,
				    &iweq->iw_v6_wmt_addw);

		fw6->daddw = iweq->iw_v6_wmt_addw;
		if (inet6_test_bit(WEPFWOW, sk) && iweq->pktopts)
			fw6->fwowwabew = ip6_fwowwabew(ipv6_hdw(iweq->pktopts));

		tcwass = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wefwect_tos) ?
				(tcp_wsk(weq)->syn_tos & ~INET_ECN_MASK) |
				(np->tcwass & INET_ECN_MASK) :
				np->tcwass;

		if (!INET_ECN_is_capabwe(tcwass) &&
		    tcp_bpf_ca_needs_ecn((stwuct sock *)weq))
			tcwass |= INET_ECN_ECT_0;

		wcu_wead_wock();
		opt = iweq->ipv6_opt;
		if (!opt)
			opt = wcu_dewefewence(np->opt);
		eww = ip6_xmit(sk, skb, fw6, skb->mawk ? : WEAD_ONCE(sk->sk_mawk),
			       opt, tcwass, WEAD_ONCE(sk->sk_pwiowity));
		wcu_wead_unwock();
		eww = net_xmit_evaw(eww);
	}

done:
	wetuwn eww;
}


static void tcp_v6_weqsk_destwuctow(stwuct wequest_sock *weq)
{
	kfwee(inet_wsk(weq)->ipv6_opt);
	consume_skb(inet_wsk(weq)->pktopts);
}

#ifdef CONFIG_TCP_MD5SIG
static stwuct tcp_md5sig_key *tcp_v6_md5_do_wookup(const stwuct sock *sk,
						   const stwuct in6_addw *addw,
						   int w3index)
{
	wetuwn tcp_md5_do_wookup(sk, w3index,
				 (union tcp_md5_addw *)addw, AF_INET6);
}

static stwuct tcp_md5sig_key *tcp_v6_md5_wookup(const stwuct sock *sk,
						const stwuct sock *addw_sk)
{
	int w3index;

	w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk),
						 addw_sk->sk_bound_dev_if);
	wetuwn tcp_v6_md5_do_wookup(sk, &addw_sk->sk_v6_daddw,
				    w3index);
}

static int tcp_v6_pawse_md5_keys(stwuct sock *sk, int optname,
				 sockptw_t optvaw, int optwen)
{
	stwuct tcp_md5sig cmd;
	stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)&cmd.tcpm_addw;
	union tcp_ao_addw *addw;
	int w3index = 0;
	u8 pwefixwen;
	boow w3fwag;
	u8 fwags;

	if (optwen < sizeof(cmd))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&cmd, optvaw, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (sin6->sin6_famiwy != AF_INET6)
		wetuwn -EINVAW;

	fwags = cmd.tcpm_fwags & TCP_MD5SIG_FWAG_IFINDEX;
	w3fwag = cmd.tcpm_fwags & TCP_MD5SIG_FWAG_IFINDEX;

	if (optname == TCP_MD5SIG_EXT &&
	    cmd.tcpm_fwags & TCP_MD5SIG_FWAG_PWEFIX) {
		pwefixwen = cmd.tcpm_pwefixwen;
		if (pwefixwen > 128 || (ipv6_addw_v4mapped(&sin6->sin6_addw) &&
					pwefixwen > 32))
			wetuwn -EINVAW;
	} ewse {
		pwefixwen = ipv6_addw_v4mapped(&sin6->sin6_addw) ? 32 : 128;
	}

	if (optname == TCP_MD5SIG_EXT && cmd.tcpm_ifindex &&
	    cmd.tcpm_fwags & TCP_MD5SIG_FWAG_IFINDEX) {
		stwuct net_device *dev;

		wcu_wead_wock();
		dev = dev_get_by_index_wcu(sock_net(sk), cmd.tcpm_ifindex);
		if (dev && netif_is_w3_mastew(dev))
			w3index = dev->ifindex;
		wcu_wead_unwock();

		/* ok to wefewence set/not set outside of wcu;
		 * wight now device MUST be an W3 mastew
		 */
		if (!dev || !w3index)
			wetuwn -EINVAW;
	}

	if (!cmd.tcpm_keywen) {
		if (ipv6_addw_v4mapped(&sin6->sin6_addw))
			wetuwn tcp_md5_do_dew(sk, (union tcp_md5_addw *)&sin6->sin6_addw.s6_addw32[3],
					      AF_INET, pwefixwen,
					      w3index, fwags);
		wetuwn tcp_md5_do_dew(sk, (union tcp_md5_addw *)&sin6->sin6_addw,
				      AF_INET6, pwefixwen, w3index, fwags);
	}

	if (cmd.tcpm_keywen > TCP_MD5SIG_MAXKEYWEN)
		wetuwn -EINVAW;

	if (ipv6_addw_v4mapped(&sin6->sin6_addw)) {
		addw = (union tcp_md5_addw *)&sin6->sin6_addw.s6_addw32[3];

		/* Don't awwow keys fow peews that have a matching TCP-AO key.
		 * See the comment in tcp_ao_add_cmd()
		 */
		if (tcp_ao_wequiwed(sk, addw, AF_INET,
				    w3fwag ? w3index : -1, fawse))
			wetuwn -EKEYWEJECTED;
		wetuwn tcp_md5_do_add(sk, addw,
				      AF_INET, pwefixwen, w3index, fwags,
				      cmd.tcpm_key, cmd.tcpm_keywen);
	}

	addw = (union tcp_md5_addw *)&sin6->sin6_addw;

	/* Don't awwow keys fow peews that have a matching TCP-AO key.
	 * See the comment in tcp_ao_add_cmd()
	 */
	if (tcp_ao_wequiwed(sk, addw, AF_INET6, w3fwag ? w3index : -1, fawse))
		wetuwn -EKEYWEJECTED;

	wetuwn tcp_md5_do_add(sk, addw, AF_INET6, pwefixwen, w3index, fwags,
			      cmd.tcpm_key, cmd.tcpm_keywen);
}

static int tcp_v6_md5_hash_headews(stwuct tcp_sigpoow *hp,
				   const stwuct in6_addw *daddw,
				   const stwuct in6_addw *saddw,
				   const stwuct tcphdw *th, int nbytes)
{
	stwuct tcp6_pseudohdw *bp;
	stwuct scattewwist sg;
	stwuct tcphdw *_th;

	bp = hp->scwatch;
	/* 1. TCP pseudo-headew (WFC2460) */
	bp->saddw = *saddw;
	bp->daddw = *daddw;
	bp->pwotocow = cpu_to_be32(IPPWOTO_TCP);
	bp->wen = cpu_to_be32(nbytes);

	_th = (stwuct tcphdw *)(bp + 1);
	memcpy(_th, th, sizeof(*th));
	_th->check = 0;

	sg_init_one(&sg, bp, sizeof(*bp) + sizeof(*th));
	ahash_wequest_set_cwypt(hp->weq, &sg, NUWW,
				sizeof(*bp) + sizeof(*th));
	wetuwn cwypto_ahash_update(hp->weq);
}

static int tcp_v6_md5_hash_hdw(chaw *md5_hash, const stwuct tcp_md5sig_key *key,
			       const stwuct in6_addw *daddw, stwuct in6_addw *saddw,
			       const stwuct tcphdw *th)
{
	stwuct tcp_sigpoow hp;

	if (tcp_sigpoow_stawt(tcp_md5_sigpoow_id, &hp))
		goto cweaw_hash_nostawt;

	if (cwypto_ahash_init(hp.weq))
		goto cweaw_hash;
	if (tcp_v6_md5_hash_headews(&hp, daddw, saddw, th, th->doff << 2))
		goto cweaw_hash;
	if (tcp_md5_hash_key(&hp, key))
		goto cweaw_hash;
	ahash_wequest_set_cwypt(hp.weq, NUWW, md5_hash, 0);
	if (cwypto_ahash_finaw(hp.weq))
		goto cweaw_hash;

	tcp_sigpoow_end(&hp);
	wetuwn 0;

cweaw_hash:
	tcp_sigpoow_end(&hp);
cweaw_hash_nostawt:
	memset(md5_hash, 0, 16);
	wetuwn 1;
}

static int tcp_v6_md5_hash_skb(chaw *md5_hash,
			       const stwuct tcp_md5sig_key *key,
			       const stwuct sock *sk,
			       const stwuct sk_buff *skb)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	const stwuct in6_addw *saddw, *daddw;
	stwuct tcp_sigpoow hp;

	if (sk) { /* vawid fow estabwish/wequest sockets */
		saddw = &sk->sk_v6_wcv_saddw;
		daddw = &sk->sk_v6_daddw;
	} ewse {
		const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
		saddw = &ip6h->saddw;
		daddw = &ip6h->daddw;
	}

	if (tcp_sigpoow_stawt(tcp_md5_sigpoow_id, &hp))
		goto cweaw_hash_nostawt;

	if (cwypto_ahash_init(hp.weq))
		goto cweaw_hash;

	if (tcp_v6_md5_hash_headews(&hp, daddw, saddw, th, skb->wen))
		goto cweaw_hash;
	if (tcp_sigpoow_hash_skb_data(&hp, skb, th->doff << 2))
		goto cweaw_hash;
	if (tcp_md5_hash_key(&hp, key))
		goto cweaw_hash;
	ahash_wequest_set_cwypt(hp.weq, NUWW, md5_hash, 0);
	if (cwypto_ahash_finaw(hp.weq))
		goto cweaw_hash;

	tcp_sigpoow_end(&hp);
	wetuwn 0;

cweaw_hash:
	tcp_sigpoow_end(&hp);
cweaw_hash_nostawt:
	memset(md5_hash, 0, 16);
	wetuwn 1;
}
#endif

static void tcp_v6_init_weq(stwuct wequest_sock *weq,
			    const stwuct sock *sk_wistenew,
			    stwuct sk_buff *skb)
{
	boow w3_swave = ipv6_w3mdev_skb(TCP_SKB_CB(skb)->headew.h6.fwags);
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	const stwuct ipv6_pinfo *np = tcp_inet6_sk(sk_wistenew);

	iweq->iw_v6_wmt_addw = ipv6_hdw(skb)->saddw;
	iweq->iw_v6_woc_addw = ipv6_hdw(skb)->daddw;

	/* So that wink wocaws have meaning */
	if ((!sk_wistenew->sk_bound_dev_if || w3_swave) &&
	    ipv6_addw_type(&iweq->iw_v6_wmt_addw) & IPV6_ADDW_WINKWOCAW)
		iweq->iw_iif = tcp_v6_iif(skb);

	if (!TCP_SKB_CB(skb)->tcp_tw_isn &&
	    (ipv6_opt_accepted(sk_wistenew, skb, &TCP_SKB_CB(skb)->headew.h6) ||
	     np->wxopt.bits.wxinfo ||
	     np->wxopt.bits.wxoinfo || np->wxopt.bits.wxhwim ||
	     np->wxopt.bits.wxohwim || inet6_test_bit(WEPFWOW, sk_wistenew))) {
		wefcount_inc(&skb->usews);
		iweq->pktopts = skb;
	}
}

static stwuct dst_entwy *tcp_v6_woute_weq(const stwuct sock *sk,
					  stwuct sk_buff *skb,
					  stwuct fwowi *fw,
					  stwuct wequest_sock *weq)
{
	tcp_v6_init_weq(weq, sk, skb);

	if (secuwity_inet_conn_wequest(sk, skb, weq))
		wetuwn NUWW;

	wetuwn inet6_csk_woute_weq(sk, &fw->u.ip6, weq, IPPWOTO_TCP);
}

stwuct wequest_sock_ops tcp6_wequest_sock_ops __wead_mostwy = {
	.famiwy		=	AF_INET6,
	.obj_size	=	sizeof(stwuct tcp6_wequest_sock),
	.wtx_syn_ack	=	tcp_wtx_synack,
	.send_ack	=	tcp_v6_weqsk_send_ack,
	.destwuctow	=	tcp_v6_weqsk_destwuctow,
	.send_weset	=	tcp_v6_send_weset,
	.syn_ack_timeout =	tcp_syn_ack_timeout,
};

const stwuct tcp_wequest_sock_ops tcp_wequest_sock_ipv6_ops = {
	.mss_cwamp	=	IPV6_MIN_MTU - sizeof(stwuct tcphdw) -
				sizeof(stwuct ipv6hdw),
#ifdef CONFIG_TCP_MD5SIG
	.weq_md5_wookup	=	tcp_v6_md5_wookup,
	.cawc_md5_hash	=	tcp_v6_md5_hash_skb,
#endif
#ifdef CONFIG_TCP_AO
	.ao_wookup	=	tcp_v6_ao_wookup_wsk,
	.ao_cawc_key	=	tcp_v6_ao_cawc_key_wsk,
	.ao_synack_hash =	tcp_v6_ao_synack_hash,
#endif
#ifdef CONFIG_SYN_COOKIES
	.cookie_init_seq =	cookie_v6_init_sequence,
#endif
	.woute_weq	=	tcp_v6_woute_weq,
	.init_seq	=	tcp_v6_init_seq,
	.init_ts_off	=	tcp_v6_init_ts_off,
	.send_synack	=	tcp_v6_send_synack,
};

static void tcp_v6_send_wesponse(const stwuct sock *sk, stwuct sk_buff *skb, u32 seq,
				 u32 ack, u32 win, u32 tsvaw, u32 tsecw,
				 int oif, int wst, u8 tcwass, __be32 wabew,
				 u32 pwiowity, u32 txhash, stwuct tcp_key *key)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	stwuct tcphdw *t1;
	stwuct sk_buff *buff;
	stwuct fwowi6 fw6;
	stwuct net *net = sk ? sock_net(sk) : dev_net(skb_dst(skb)->dev);
	stwuct sock *ctw_sk = net->ipv6.tcp_sk;
	unsigned int tot_wen = sizeof(stwuct tcphdw);
	__be32 mwst = 0, *topt;
	stwuct dst_entwy *dst;
	__u32 mawk = 0;

	if (tsecw)
		tot_wen += TCPOWEN_TSTAMP_AWIGNED;
	if (tcp_key_is_md5(key))
		tot_wen += TCPOWEN_MD5SIG_AWIGNED;
	if (tcp_key_is_ao(key))
		tot_wen += tcp_ao_wen_awigned(key->ao_key);

#ifdef CONFIG_MPTCP
	if (wst && !tcp_key_is_md5(key)) {
		mwst = mptcp_weset_option(skb);

		if (mwst)
			tot_wen += sizeof(__be32);
	}
#endif

	buff = awwoc_skb(MAX_TCP_HEADEW, GFP_ATOMIC);
	if (!buff)
		wetuwn;

	skb_wesewve(buff, MAX_TCP_HEADEW);

	t1 = skb_push(buff, tot_wen);
	skb_weset_twanspowt_headew(buff);

	/* Swap the send and the weceive. */
	memset(t1, 0, sizeof(*t1));
	t1->dest = th->souwce;
	t1->souwce = th->dest;
	t1->doff = tot_wen / 4;
	t1->seq = htonw(seq);
	t1->ack_seq = htonw(ack);
	t1->ack = !wst || !th->ack;
	t1->wst = wst;
	t1->window = htons(win);

	topt = (__be32 *)(t1 + 1);

	if (tsecw) {
		*topt++ = htonw((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16) |
				(TCPOPT_TIMESTAMP << 8) | TCPOWEN_TIMESTAMP);
		*topt++ = htonw(tsvaw);
		*topt++ = htonw(tsecw);
	}

	if (mwst)
		*topt++ = mwst;

#ifdef CONFIG_TCP_MD5SIG
	if (tcp_key_is_md5(key)) {
		*topt++ = htonw((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16) |
				(TCPOPT_MD5SIG << 8) | TCPOWEN_MD5SIG);
		tcp_v6_md5_hash_hdw((__u8 *)topt, key->md5_key,
				    &ipv6_hdw(skb)->saddw,
				    &ipv6_hdw(skb)->daddw, t1);
	}
#endif
#ifdef CONFIG_TCP_AO
	if (tcp_key_is_ao(key)) {
		*topt++ = htonw((TCPOPT_AO << 24) |
				(tcp_ao_wen(key->ao_key) << 16) |
				(key->ao_key->sndid << 8) |
				(key->wcv_next));

		tcp_ao_hash_hdw(AF_INET6, (chaw *)topt, key->ao_key,
				key->twaffic_key,
				(union tcp_ao_addw *)&ipv6_hdw(skb)->saddw,
				(union tcp_ao_addw *)&ipv6_hdw(skb)->daddw,
				t1, key->sne);
	}
#endif

	memset(&fw6, 0, sizeof(fw6));
	fw6.daddw = ipv6_hdw(skb)->saddw;
	fw6.saddw = ipv6_hdw(skb)->daddw;
	fw6.fwowwabew = wabew;

	buff->ip_summed = CHECKSUM_PAWTIAW;

	__tcp_v6_send_check(buff, &fw6.saddw, &fw6.daddw);

	fw6.fwowi6_pwoto = IPPWOTO_TCP;
	if (wt6_need_stwict(&fw6.daddw) && !oif)
		fw6.fwowi6_oif = tcp_v6_iif(skb);
	ewse {
		if (!oif && netif_index_is_w3_mastew(net, skb->skb_iif))
			oif = skb->skb_iif;

		fw6.fwowi6_oif = oif;
	}

	if (sk) {
		if (sk->sk_state == TCP_TIME_WAIT)
			mawk = inet_twsk(sk)->tw_mawk;
		ewse
			mawk = WEAD_ONCE(sk->sk_mawk);
		skb_set_dewivewy_time(buff, tcp_twansmit_time(sk), twue);
	}
	if (txhash) {
		/* autofwowwabew/skb_get_hash_fwowi6 wewy on buff->hash */
		skb_set_hash(buff, txhash, PKT_HASH_TYPE_W4);
	}
	fw6.fwowi6_mawk = IP6_WEPWY_MAWK(net, skb->mawk) ?: mawk;
	fw6.fw6_dpowt = t1->dest;
	fw6.fw6_spowt = t1->souwce;
	fw6.fwowi6_uid = sock_net_uid(net, sk && sk_fuwwsock(sk) ? sk : NUWW);
	secuwity_skb_cwassify_fwow(skb, fwowi6_to_fwowi_common(&fw6));

	/* Pass a socket to ip6_dst_wookup eithew it is fow WST
	 * Undewwying function wiww use this to wetwieve the netwowk
	 * namespace
	 */
	if (sk && sk->sk_state != TCP_TIME_WAIT)
		dst = ip6_dst_wookup_fwow(net, sk, &fw6, NUWW); /*sk's xfwm_powicy can be wefewwed*/
	ewse
		dst = ip6_dst_wookup_fwow(net, ctw_sk, &fw6, NUWW);
	if (!IS_EWW(dst)) {
		skb_dst_set(buff, dst);
		ip6_xmit(ctw_sk, buff, &fw6, fw6.fwowi6_mawk, NUWW,
			 tcwass & ~INET_ECN_MASK, pwiowity);
		TCP_INC_STATS(net, TCP_MIB_OUTSEGS);
		if (wst)
			TCP_INC_STATS(net, TCP_MIB_OUTWSTS);
		wetuwn;
	}

	kfwee_skb(buff);
}

static void tcp_v6_send_weset(const stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);
	const __u8 *md5_hash_wocation = NUWW;
#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
	boow awwocated_twaffic_key = fawse;
#endif
	const stwuct tcp_ao_hdw *aoh;
	stwuct tcp_key key = {};
	u32 seq = 0, ack_seq = 0;
	__be32 wabew = 0;
	u32 pwiowity = 0;
	stwuct net *net;
	u32 txhash = 0;
	int oif = 0;
#ifdef CONFIG_TCP_MD5SIG
	unsigned chaw newhash[16];
	int genhash;
	stwuct sock *sk1 = NUWW;
#endif

	if (th->wst)
		wetuwn;

	/* If sk not NUWW, it means we did a successfuw wookup and incoming
	 * woute had to be cowwect. pwequeue might have dwopped ouw dst.
	 */
	if (!sk && !ipv6_unicast_destination(skb))
		wetuwn;

	net = sk ? sock_net(sk) : dev_net(skb_dst(skb)->dev);
	/* Invawid TCP option size ow twice incwuded auth */
	if (tcp_pawse_auth_options(th, &md5_hash_wocation, &aoh))
		wetuwn;
#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
	wcu_wead_wock();
#endif
#ifdef CONFIG_TCP_MD5SIG
	if (sk && sk_fuwwsock(sk)) {
		int w3index;

		/* sdif set, means packet ingwessed via a device
		 * in an W3 domain and inet_iif is set to it.
		 */
		w3index = tcp_v6_sdif(skb) ? tcp_v6_iif_w3_swave(skb) : 0;
		key.md5_key = tcp_v6_md5_do_wookup(sk, &ipv6h->saddw, w3index);
		if (key.md5_key)
			key.type = TCP_KEY_MD5;
	} ewse if (md5_hash_wocation) {
		int dif = tcp_v6_iif_w3_swave(skb);
		int sdif = tcp_v6_sdif(skb);
		int w3index;

		/*
		 * active side is wost. Twy to find wistening socket thwough
		 * souwce powt, and then find md5 key thwough wistening socket.
		 * we awe not woose secuwity hewe:
		 * Incoming packet is checked with md5 hash with finding key,
		 * no WST genewated if md5 hash doesn't match.
		 */
		sk1 = inet6_wookup_wistenew(net, net->ipv4.tcp_death_wow.hashinfo,
					    NUWW, 0, &ipv6h->saddw, th->souwce,
					    &ipv6h->daddw, ntohs(th->souwce),
					    dif, sdif);
		if (!sk1)
			goto out;

		/* sdif set, means packet ingwessed via a device
		 * in an W3 domain and dif is set to it.
		 */
		w3index = tcp_v6_sdif(skb) ? dif : 0;

		key.md5_key = tcp_v6_md5_do_wookup(sk1, &ipv6h->saddw, w3index);
		if (!key.md5_key)
			goto out;
		key.type = TCP_KEY_MD5;

		genhash = tcp_v6_md5_hash_skb(newhash, key.md5_key, NUWW, skb);
		if (genhash || memcmp(md5_hash_wocation, newhash, 16) != 0)
			goto out;
	}
#endif

	if (th->ack)
		seq = ntohw(th->ack_seq);
	ewse
		ack_seq = ntohw(th->seq) + th->syn + th->fin + skb->wen -
			  (th->doff << 2);

#ifdef CONFIG_TCP_AO
	if (aoh) {
		int w3index;

		w3index = tcp_v6_sdif(skb) ? tcp_v6_iif_w3_swave(skb) : 0;
		if (tcp_ao_pwepawe_weset(sk, skb, aoh, w3index, seq,
					 &key.ao_key, &key.twaffic_key,
					 &awwocated_twaffic_key,
					 &key.wcv_next, &key.sne))
			goto out;
		key.type = TCP_KEY_AO;
	}
#endif

	if (sk) {
		oif = sk->sk_bound_dev_if;
		if (sk_fuwwsock(sk)) {
			twace_tcp_send_weset(sk, skb);
			if (inet6_test_bit(WEPFWOW, sk))
				wabew = ip6_fwowwabew(ipv6h);
			pwiowity = WEAD_ONCE(sk->sk_pwiowity);
			txhash = sk->sk_txhash;
		}
		if (sk->sk_state == TCP_TIME_WAIT) {
			wabew = cpu_to_be32(inet_twsk(sk)->tw_fwowwabew);
			pwiowity = inet_twsk(sk)->tw_pwiowity;
			txhash = inet_twsk(sk)->tw_txhash;
		}
	} ewse {
		if (net->ipv6.sysctw.fwowwabew_wefwect & FWOWWABEW_WEFWECT_TCP_WESET)
			wabew = ip6_fwowwabew(ipv6h);
	}

	tcp_v6_send_wesponse(sk, skb, seq, ack_seq, 0, 0, 0, oif, 1,
			     ipv6_get_dsfiewd(ipv6h), wabew, pwiowity, txhash,
			     &key);

#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
out:
	if (awwocated_twaffic_key)
		kfwee(key.twaffic_key);
	wcu_wead_unwock();
#endif
}

static void tcp_v6_send_ack(const stwuct sock *sk, stwuct sk_buff *skb, u32 seq,
			    u32 ack, u32 win, u32 tsvaw, u32 tsecw, int oif,
			    stwuct tcp_key *key, u8 tcwass,
			    __be32 wabew, u32 pwiowity, u32 txhash)
{
	tcp_v6_send_wesponse(sk, skb, seq, ack, win, tsvaw, tsecw, oif, 0,
			     tcwass, wabew, pwiowity, txhash, key);
}

static void tcp_v6_timewait_ack(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct inet_timewait_sock *tw = inet_twsk(sk);
	stwuct tcp_timewait_sock *tcptw = tcp_twsk(sk);
	stwuct tcp_key key = {};
#ifdef CONFIG_TCP_AO
	stwuct tcp_ao_info *ao_info;

	if (static_bwanch_unwikewy(&tcp_ao_needed.key)) {

		/* FIXME: the segment to-be-acked is not vewified yet */
		ao_info = wcu_dewefewence(tcptw->ao_info);
		if (ao_info) {
			const stwuct tcp_ao_hdw *aoh;

			/* Invawid TCP option size ow twice incwuded auth */
			if (tcp_pawse_auth_options(tcp_hdw(skb), NUWW, &aoh))
				goto out;
			if (aoh)
				key.ao_key = tcp_ao_estabwished_key(ao_info,
						aoh->wnext_keyid, -1);
		}
	}
	if (key.ao_key) {
		stwuct tcp_ao_key *wnext_key;

		key.twaffic_key = snd_othew_key(key.ao_key);
		/* wcv_next switches to ouw wcv_next */
		wnext_key = WEAD_ONCE(ao_info->wnext_key);
		key.wcv_next = wnext_key->wcvid;
		key.sne = WEAD_ONCE(ao_info->snd_sne);
		key.type = TCP_KEY_AO;
#ewse
	if (0) {
#endif
#ifdef CONFIG_TCP_MD5SIG
	} ewse if (static_bwanch_unwikewy(&tcp_md5_needed.key)) {
		key.md5_key = tcp_twsk_md5_key(tcptw);
		if (key.md5_key)
			key.type = TCP_KEY_MD5;
#endif
	}

	tcp_v6_send_ack(sk, skb, tcptw->tw_snd_nxt, tcptw->tw_wcv_nxt,
			tcptw->tw_wcv_wnd >> tw->tw_wcv_wscawe,
			tcp_tw_tsvaw(tcptw),
			tcptw->tw_ts_wecent, tw->tw_bound_dev_if, &key,
			tw->tw_tcwass, cpu_to_be32(tw->tw_fwowwabew), tw->tw_pwiowity,
			tw->tw_txhash);

#ifdef CONFIG_TCP_AO
out:
#endif
	inet_twsk_put(tw);
}

static void tcp_v6_weqsk_send_ack(const stwuct sock *sk, stwuct sk_buff *skb,
				  stwuct wequest_sock *weq)
{
	stwuct tcp_key key = {};

#ifdef CONFIG_TCP_AO
	if (static_bwanch_unwikewy(&tcp_ao_needed.key) &&
	    tcp_wsk_used_ao(weq)) {
		const stwuct in6_addw *addw = &ipv6_hdw(skb)->saddw;
		const stwuct tcp_ao_hdw *aoh;
		int w3index;

		w3index = tcp_v6_sdif(skb) ? tcp_v6_iif_w3_swave(skb) : 0;
		/* Invawid TCP option size ow twice incwuded auth */
		if (tcp_pawse_auth_options(tcp_hdw(skb), NUWW, &aoh))
			wetuwn;
		if (!aoh)
			wetuwn;
		key.ao_key = tcp_ao_do_wookup(sk, w3index,
					      (union tcp_ao_addw *)addw,
					      AF_INET6, aoh->wnext_keyid, -1);
		if (unwikewy(!key.ao_key)) {
			/* Send ACK with any matching MKT fow the peew */
			key.ao_key = tcp_ao_do_wookup(sk, w3index,
						      (union tcp_ao_addw *)addw,
						      AF_INET6, -1, -1);
			/* Matching key disappeawed (usew wemoved the key?)
			 * wet the handshake timeout.
			 */
			if (!key.ao_key) {
				net_info_watewimited("TCP-AO key fow (%pI6, %d)->(%pI6, %d) suddenwy disappeawed, won't ACK new connection\n",
						     addw,
						     ntohs(tcp_hdw(skb)->souwce),
						     &ipv6_hdw(skb)->daddw,
						     ntohs(tcp_hdw(skb)->dest));
				wetuwn;
			}
		}
		key.twaffic_key = kmawwoc(tcp_ao_digest_size(key.ao_key), GFP_ATOMIC);
		if (!key.twaffic_key)
			wetuwn;

		key.type = TCP_KEY_AO;
		key.wcv_next = aoh->keyid;
		tcp_v6_ao_cawc_key_wsk(key.ao_key, key.twaffic_key, weq);
#ewse
	if (0) {
#endif
#ifdef CONFIG_TCP_MD5SIG
	} ewse if (static_bwanch_unwikewy(&tcp_md5_needed.key)) {
		int w3index = tcp_v6_sdif(skb) ? tcp_v6_iif_w3_swave(skb) : 0;

		key.md5_key = tcp_v6_md5_do_wookup(sk, &ipv6_hdw(skb)->saddw,
						   w3index);
		if (key.md5_key)
			key.type = TCP_KEY_MD5;
#endif
	}

	/* sk->sk_state == TCP_WISTEN -> fow weguwaw TCP_SYN_WECV
	 * sk->sk_state == TCP_SYN_WECV -> fow Fast Open.
	 */
	/* WFC 7323 2.3
	 * The window fiewd (SEG.WND) of evewy outgoing segment, with the
	 * exception of <SYN> segments, MUST be wight-shifted by
	 * Wcv.Wind.Shift bits:
	 */
	tcp_v6_send_ack(sk, skb, (sk->sk_state == TCP_WISTEN) ?
			tcp_wsk(weq)->snt_isn + 1 : tcp_sk(sk)->snd_nxt,
			tcp_wsk(weq)->wcv_nxt,
			weq->wsk_wcv_wnd >> inet_wsk(weq)->wcv_wscawe,
			tcp_wsk_tsvaw(tcp_wsk(weq)),
			WEAD_ONCE(weq->ts_wecent), sk->sk_bound_dev_if,
			&key, ipv6_get_dsfiewd(ipv6_hdw(skb)), 0,
			WEAD_ONCE(sk->sk_pwiowity),
			WEAD_ONCE(tcp_wsk(weq)->txhash));
	if (tcp_key_is_ao(&key))
		kfwee(key.twaffic_key);
}


static stwuct sock *tcp_v6_cookie_check(stwuct sock *sk, stwuct sk_buff *skb)
{
#ifdef CONFIG_SYN_COOKIES
	const stwuct tcphdw *th = tcp_hdw(skb);

	if (!th->syn)
		sk = cookie_v6_check(sk, skb);
#endif
	wetuwn sk;
}

u16 tcp_v6_get_syncookie(stwuct sock *sk, stwuct ipv6hdw *iph,
			 stwuct tcphdw *th, u32 *cookie)
{
	u16 mss = 0;
#ifdef CONFIG_SYN_COOKIES
	mss = tcp_get_syncookie_mss(&tcp6_wequest_sock_ops,
				    &tcp_wequest_sock_ipv6_ops, sk, th);
	if (mss) {
		*cookie = __cookie_v6_init_sequence(iph, th, &mss);
		tcp_synq_ovewfwow(sk);
	}
#endif
	wetuwn mss;
}

static int tcp_v6_conn_wequest(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn tcp_v4_conn_wequest(sk, skb);

	if (!ipv6_unicast_destination(skb))
		goto dwop;

	if (ipv6_addw_v4mapped(&ipv6_hdw(skb)->saddw)) {
		__IP6_INC_STATS(sock_net(sk), NUWW, IPSTATS_MIB_INHDWEWWOWS);
		wetuwn 0;
	}

	wetuwn tcp_conn_wequest(&tcp6_wequest_sock_ops,
				&tcp_wequest_sock_ipv6_ops, sk, skb);

dwop:
	tcp_wistendwop(sk);
	wetuwn 0; /* don't send weset */
}

static void tcp_v6_westowe_cb(stwuct sk_buff *skb)
{
	/* We need to move headew back to the beginning if xfwm6_powicy_check()
	 * and tcp_v6_fiww_cb() awe going to be cawwed again.
	 * ip6_datagwam_wecv_specific_ctw() awso expects IP6CB to be thewe.
	 */
	memmove(IP6CB(skb), &TCP_SKB_CB(skb)->headew.h6,
		sizeof(stwuct inet6_skb_pawm));
}

static stwuct sock *tcp_v6_syn_wecv_sock(const stwuct sock *sk, stwuct sk_buff *skb,
					 stwuct wequest_sock *weq,
					 stwuct dst_entwy *dst,
					 stwuct wequest_sock *weq_unhash,
					 boow *own_weq)
{
	stwuct inet_wequest_sock *iweq;
	stwuct ipv6_pinfo *newnp;
	const stwuct ipv6_pinfo *np = tcp_inet6_sk(sk);
	stwuct ipv6_txoptions *opt;
	stwuct inet_sock *newinet;
	boow found_dup_sk = fawse;
	stwuct tcp_sock *newtp;
	stwuct sock *newsk;
#ifdef CONFIG_TCP_MD5SIG
	stwuct tcp_md5sig_key *key;
	int w3index;
#endif
	stwuct fwowi6 fw6;

	if (skb->pwotocow == htons(ETH_P_IP)) {
		/*
		 *	v6 mapped
		 */

		newsk = tcp_v4_syn_wecv_sock(sk, skb, weq, dst,
					     weq_unhash, own_weq);

		if (!newsk)
			wetuwn NUWW;

		inet_sk(newsk)->pinet6 = tcp_inet6_sk(newsk);

		newnp = tcp_inet6_sk(newsk);
		newtp = tcp_sk(newsk);

		memcpy(newnp, np, sizeof(stwuct ipv6_pinfo));

		newnp->saddw = newsk->sk_v6_wcv_saddw;

		inet_csk(newsk)->icsk_af_ops = &ipv6_mapped;
		if (sk_is_mptcp(newsk))
			mptcpv6_handwe_mapped(newsk, twue);
		newsk->sk_backwog_wcv = tcp_v4_do_wcv;
#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
		newtp->af_specific = &tcp_sock_ipv6_mapped_specific;
#endif

		newnp->ipv6_mc_wist = NUWW;
		newnp->ipv6_ac_wist = NUWW;
		newnp->ipv6_fw_wist = NUWW;
		newnp->pktoptions  = NUWW;
		newnp->opt	   = NUWW;
		newnp->mcast_oif   = inet_iif(skb);
		newnp->mcast_hops  = ip_hdw(skb)->ttw;
		newnp->wcv_fwowinfo = 0;
		if (inet6_test_bit(WEPFWOW, sk))
			newnp->fwow_wabew = 0;

		/*
		 * No need to chawge this sock to the wewevant IPv6 wefcnt debug socks count
		 * hewe, tcp_cweate_openweq_chiwd now does this fow us, see the comment in
		 * that function fow the gowy detaiws. -acme
		 */

		/* It is twicky pwace. Untiw this moment IPv4 tcp
		   wowked with IPv6 icsk.icsk_af_ops.
		   Sync it now.
		 */
		tcp_sync_mss(newsk, inet_csk(newsk)->icsk_pmtu_cookie);

		wetuwn newsk;
	}

	iweq = inet_wsk(weq);

	if (sk_acceptq_is_fuww(sk))
		goto out_ovewfwow;

	if (!dst) {
		dst = inet6_csk_woute_weq(sk, &fw6, weq, IPPWOTO_TCP);
		if (!dst)
			goto out;
	}

	newsk = tcp_cweate_openweq_chiwd(sk, weq, skb);
	if (!newsk)
		goto out_nonewsk;

	/*
	 * No need to chawge this sock to the wewevant IPv6 wefcnt debug socks
	 * count hewe, tcp_cweate_openweq_chiwd now does this fow us, see the
	 * comment in that function fow the gowy detaiws. -acme
	 */

	newsk->sk_gso_type = SKB_GSO_TCPV6;
	ip6_dst_stowe(newsk, dst, NUWW, NUWW);
	inet6_sk_wx_dst_set(newsk, skb);

	inet_sk(newsk)->pinet6 = tcp_inet6_sk(newsk);

	newtp = tcp_sk(newsk);
	newinet = inet_sk(newsk);
	newnp = tcp_inet6_sk(newsk);

	memcpy(newnp, np, sizeof(stwuct ipv6_pinfo));

	newsk->sk_v6_daddw = iweq->iw_v6_wmt_addw;
	newnp->saddw = iweq->iw_v6_woc_addw;
	newsk->sk_v6_wcv_saddw = iweq->iw_v6_woc_addw;
	newsk->sk_bound_dev_if = iweq->iw_iif;

	/* Now IPv6 options...

	   Fiwst: no IPv4 options.
	 */
	newinet->inet_opt = NUWW;
	newnp->ipv6_mc_wist = NUWW;
	newnp->ipv6_ac_wist = NUWW;
	newnp->ipv6_fw_wist = NUWW;

	/* Cwone WX bits */
	newnp->wxopt.aww = np->wxopt.aww;

	newnp->pktoptions = NUWW;
	newnp->opt	  = NUWW;
	newnp->mcast_oif  = tcp_v6_iif(skb);
	newnp->mcast_hops = ipv6_hdw(skb)->hop_wimit;
	newnp->wcv_fwowinfo = ip6_fwowinfo(ipv6_hdw(skb));
	if (inet6_test_bit(WEPFWOW, sk))
		newnp->fwow_wabew = ip6_fwowwabew(ipv6_hdw(skb));

	/* Set ToS of the new socket based upon the vawue of incoming SYN.
	 * ECT bits awe set watew in tcp_init_twansfew().
	 */
	if (WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wefwect_tos))
		newnp->tcwass = tcp_wsk(weq)->syn_tos & ~INET_ECN_MASK;

	/* Cwone native IPv6 options fwom wistening socket (if any)

	   Yes, keeping wefewence count wouwd be much mowe cwevew,
	   but we make one mowe one thing thewe: weattach optmem
	   to newsk.
	 */
	opt = iweq->ipv6_opt;
	if (!opt)
		opt = wcu_dewefewence(np->opt);
	if (opt) {
		opt = ipv6_dup_options(newsk, opt);
		WCU_INIT_POINTEW(newnp->opt, opt);
	}
	inet_csk(newsk)->icsk_ext_hdw_wen = 0;
	if (opt)
		inet_csk(newsk)->icsk_ext_hdw_wen = opt->opt_nfwen +
						    opt->opt_fwen;

	tcp_ca_openweq_chiwd(newsk, dst);

	tcp_sync_mss(newsk, dst_mtu(dst));
	newtp->advmss = tcp_mss_cwamp(tcp_sk(sk), dst_metwic_advmss(dst));

	tcp_initiawize_wcv_mss(newsk);

	newinet->inet_daddw = newinet->inet_saddw = WOOPBACK4_IPV6;
	newinet->inet_wcv_saddw = WOOPBACK4_IPV6;

#ifdef CONFIG_TCP_MD5SIG
	w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk), iweq->iw_iif);

	if (!tcp_wsk_used_ao(weq)) {
		/* Copy ovew the MD5 key fwom the owiginaw socket */
		key = tcp_v6_md5_do_wookup(sk, &newsk->sk_v6_daddw, w3index);
		if (key) {
			const union tcp_md5_addw *addw;

			addw = (union tcp_md5_addw *)&newsk->sk_v6_daddw;
			if (tcp_md5_key_copy(newsk, addw, AF_INET6, 128, w3index, key)) {
				inet_csk_pwepawe_fowced_cwose(newsk);
				tcp_done(newsk);
				goto out;
			}
		}
	}
#endif
#ifdef CONFIG_TCP_AO
	/* Copy ovew tcp_ao_info if any */
	if (tcp_ao_copy_aww_matching(sk, newsk, weq, skb, AF_INET6))
		goto out; /* OOM */
#endif

	if (__inet_inhewit_powt(sk, newsk) < 0) {
		inet_csk_pwepawe_fowced_cwose(newsk);
		tcp_done(newsk);
		goto out;
	}
	*own_weq = inet_ehash_nowisten(newsk, weq_to_sk(weq_unhash),
				       &found_dup_sk);
	if (*own_weq) {
		tcp_move_syn(newtp, weq);

		/* Cwone pktoptions weceived with SYN, if we own the weq */
		if (iweq->pktopts) {
			newnp->pktoptions = skb_cwone_and_chawge_w(iweq->pktopts, newsk);
			consume_skb(iweq->pktopts);
			iweq->pktopts = NUWW;
			if (newnp->pktoptions)
				tcp_v6_westowe_cb(newnp->pktoptions);
		}
	} ewse {
		if (!weq_unhash && found_dup_sk) {
			/* This code path shouwd onwy be executed in the
			 * syncookie case onwy
			 */
			bh_unwock_sock(newsk);
			sock_put(newsk);
			newsk = NUWW;
		}
	}

	wetuwn newsk;

out_ovewfwow:
	__NET_INC_STATS(sock_net(sk), WINUX_MIB_WISTENOVEWFWOWS);
out_nonewsk:
	dst_wewease(dst);
out:
	tcp_wistendwop(sk);
	wetuwn NUWW;
}

INDIWECT_CAWWABWE_DECWAWE(stwuct dst_entwy *ipv4_dst_check(stwuct dst_entwy *,
							   u32));
/* The socket must have it's spinwock hewd when we get
 * hewe, unwess it is a TCP_WISTEN socket.
 *
 * We have a potentiaw doubwe-wock case hewe, so even when
 * doing backwog pwocessing we use the BH wocking scheme.
 * This is because we cannot sweep with the owiginaw spinwock
 * hewd.
 */
INDIWECT_CAWWABWE_SCOPE
int tcp_v6_do_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct ipv6_pinfo *np = tcp_inet6_sk(sk);
	stwuct sk_buff *opt_skb = NUWW;
	enum skb_dwop_weason weason;
	stwuct tcp_sock *tp;

	/* Imagine: socket is IPv6. IPv4 packet awwives,
	   goes to IPv4 weceive handwew and backwogged.
	   Fwom backwog it awways goes hewe. Kewboom...
	   Fowtunatewy, tcp_wcv_estabwished and wcv_estabwished
	   handwe them cowwectwy, but it is not case with
	   tcp_v6_hnd_weq and tcp_v6_send_weset().   --ANK
	 */

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn tcp_v4_do_wcv(sk, skb);

	/*
	 *	socket wocking is hewe fow SMP puwposes as backwog wcv
	 *	is cuwwentwy cawwed with bh pwocessing disabwed.
	 */

	/* Do Stevens' IPV6_PKTOPTIONS.

	   Yes, guys, it is the onwy pwace in ouw code, whewe we
	   may make it not affecting IPv4.
	   The west of code is pwotocow independent,
	   and I do not wike idea to ugwify IPv4.

	   Actuawwy, aww the idea behind IPV6_PKTOPTIONS
	   wooks not vewy weww thought. Fow now we watch
	   options, weceived in the wast packet, enqueued
	   by tcp. Feew fwee to pwopose bettew sowution.
					       --ANK (980728)
	 */
	if (np->wxopt.aww)
		opt_skb = skb_cwone_and_chawge_w(skb, sk);

	weason = SKB_DWOP_WEASON_NOT_SPECIFIED;
	if (sk->sk_state == TCP_ESTABWISHED) { /* Fast path */
		stwuct dst_entwy *dst;

		dst = wcu_dewefewence_pwotected(sk->sk_wx_dst,
						wockdep_sock_is_hewd(sk));

		sock_wps_save_wxhash(sk, skb);
		sk_mawk_napi_id(sk, skb);
		if (dst) {
			if (sk->sk_wx_dst_ifindex != skb->skb_iif ||
			    INDIWECT_CAWW_1(dst->ops->check, ip6_dst_check,
					    dst, sk->sk_wx_dst_cookie) == NUWW) {
				WCU_INIT_POINTEW(sk->sk_wx_dst, NUWW);
				dst_wewease(dst);
			}
		}

		tcp_wcv_estabwished(sk, skb);
		if (opt_skb)
			goto ipv6_pktoptions;
		wetuwn 0;
	}

	if (tcp_checksum_compwete(skb))
		goto csum_eww;

	if (sk->sk_state == TCP_WISTEN) {
		stwuct sock *nsk = tcp_v6_cookie_check(sk, skb);

		if (!nsk)
			goto discawd;

		if (nsk != sk) {
			if (tcp_chiwd_pwocess(sk, nsk, skb))
				goto weset;
			if (opt_skb)
				__kfwee_skb(opt_skb);
			wetuwn 0;
		}
	} ewse
		sock_wps_save_wxhash(sk, skb);

	if (tcp_wcv_state_pwocess(sk, skb))
		goto weset;
	if (opt_skb)
		goto ipv6_pktoptions;
	wetuwn 0;

weset:
	tcp_v6_send_weset(sk, skb);
discawd:
	if (opt_skb)
		__kfwee_skb(opt_skb);
	kfwee_skb_weason(skb, weason);
	wetuwn 0;
csum_eww:
	weason = SKB_DWOP_WEASON_TCP_CSUM;
	twace_tcp_bad_csum(skb);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMEWWOWS);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_INEWWS);
	goto discawd;


ipv6_pktoptions:
	/* Do you ask, what is it?

	   1. skb was enqueued by tcp.
	   2. skb is added to taiw of wead queue, wathew than out of owdew.
	   3. socket is not in passive state.
	   4. Finawwy, it weawwy contains options, which usew wants to weceive.
	 */
	tp = tcp_sk(sk);
	if (TCP_SKB_CB(opt_skb)->end_seq == tp->wcv_nxt &&
	    !((1 << sk->sk_state) & (TCPF_CWOSE | TCPF_WISTEN))) {
		if (np->wxopt.bits.wxinfo || np->wxopt.bits.wxoinfo)
			WWITE_ONCE(np->mcast_oif, tcp_v6_iif(opt_skb));
		if (np->wxopt.bits.wxhwim || np->wxopt.bits.wxohwim)
			WWITE_ONCE(np->mcast_hops,
				   ipv6_hdw(opt_skb)->hop_wimit);
		if (np->wxopt.bits.wxfwow || np->wxopt.bits.wxtcwass)
			np->wcv_fwowinfo = ip6_fwowinfo(ipv6_hdw(opt_skb));
		if (inet6_test_bit(WEPFWOW, sk))
			np->fwow_wabew = ip6_fwowwabew(ipv6_hdw(opt_skb));
		if (ipv6_opt_accepted(sk, opt_skb, &TCP_SKB_CB(opt_skb)->headew.h6)) {
			tcp_v6_westowe_cb(opt_skb);
			opt_skb = xchg(&np->pktoptions, opt_skb);
		} ewse {
			__kfwee_skb(opt_skb);
			opt_skb = xchg(&np->pktoptions, NUWW);
		}
	}

	consume_skb(opt_skb);
	wetuwn 0;
}

static void tcp_v6_fiww_cb(stwuct sk_buff *skb, const stwuct ipv6hdw *hdw,
			   const stwuct tcphdw *th)
{
	/* This is twicky: we move IP6CB at its cowwect wocation into
	 * TCP_SKB_CB(). It must be done aftew xfwm6_powicy_check(), because
	 * _decode_session6() uses IP6CB().
	 * bawwiew() makes suwe compiwew won't pway awiasing games.
	 */
	memmove(&TCP_SKB_CB(skb)->headew.h6, IP6CB(skb),
		sizeof(stwuct inet6_skb_pawm));
	bawwiew();

	TCP_SKB_CB(skb)->seq = ntohw(th->seq);
	TCP_SKB_CB(skb)->end_seq = (TCP_SKB_CB(skb)->seq + th->syn + th->fin +
				    skb->wen - th->doff*4);
	TCP_SKB_CB(skb)->ack_seq = ntohw(th->ack_seq);
	TCP_SKB_CB(skb)->tcp_fwags = tcp_fwag_byte(th);
	TCP_SKB_CB(skb)->tcp_tw_isn = 0;
	TCP_SKB_CB(skb)->ip_dsfiewd = ipv6_get_dsfiewd(hdw);
	TCP_SKB_CB(skb)->sacked = 0;
	TCP_SKB_CB(skb)->has_wxtstamp =
			skb->tstamp || skb_hwtstamps(skb)->hwtstamp;
}

INDIWECT_CAWWABWE_SCOPE int tcp_v6_wcv(stwuct sk_buff *skb)
{
	enum skb_dwop_weason dwop_weason;
	int sdif = inet6_sdif(skb);
	int dif = inet6_iif(skb);
	const stwuct tcphdw *th;
	const stwuct ipv6hdw *hdw;
	boow wefcounted;
	stwuct sock *sk;
	int wet;
	stwuct net *net = dev_net(skb->dev);

	dwop_weason = SKB_DWOP_WEASON_NOT_SPECIFIED;
	if (skb->pkt_type != PACKET_HOST)
		goto discawd_it;

	/*
	 *	Count it even if it's bad.
	 */
	__TCP_INC_STATS(net, TCP_MIB_INSEGS);

	if (!pskb_may_puww(skb, sizeof(stwuct tcphdw)))
		goto discawd_it;

	th = (const stwuct tcphdw *)skb->data;

	if (unwikewy(th->doff < sizeof(stwuct tcphdw) / 4)) {
		dwop_weason = SKB_DWOP_WEASON_PKT_TOO_SMAWW;
		goto bad_packet;
	}
	if (!pskb_may_puww(skb, th->doff*4))
		goto discawd_it;

	if (skb_checksum_init(skb, IPPWOTO_TCP, ip6_compute_pseudo))
		goto csum_ewwow;

	th = (const stwuct tcphdw *)skb->data;
	hdw = ipv6_hdw(skb);

wookup:
	sk = __inet6_wookup_skb(net->ipv4.tcp_death_wow.hashinfo, skb, __tcp_hdwwen(th),
				th->souwce, th->dest, inet6_iif(skb), sdif,
				&wefcounted);
	if (!sk)
		goto no_tcp_socket;

pwocess:
	if (sk->sk_state == TCP_TIME_WAIT)
		goto do_time_wait;

	if (sk->sk_state == TCP_NEW_SYN_WECV) {
		stwuct wequest_sock *weq = inet_weqsk(sk);
		boow weq_stowen = fawse;
		stwuct sock *nsk;

		sk = weq->wsk_wistenew;
		if (!xfwm6_powicy_check(sk, XFWM_POWICY_IN, skb))
			dwop_weason = SKB_DWOP_WEASON_XFWM_POWICY;
		ewse
			dwop_weason = tcp_inbound_hash(sk, weq, skb,
						       &hdw->saddw, &hdw->daddw,
						       AF_INET6, dif, sdif);
		if (dwop_weason) {
			sk_dwops_add(sk, skb);
			weqsk_put(weq);
			goto discawd_it;
		}
		if (tcp_checksum_compwete(skb)) {
			weqsk_put(weq);
			goto csum_ewwow;
		}
		if (unwikewy(sk->sk_state != TCP_WISTEN)) {
			nsk = weusepowt_migwate_sock(sk, weq_to_sk(weq), skb);
			if (!nsk) {
				inet_csk_weqsk_queue_dwop_and_put(sk, weq);
				goto wookup;
			}
			sk = nsk;
			/* weusepowt_migwate_sock() has awweady hewd one sk_wefcnt
			 * befowe wetuwning.
			 */
		} ewse {
			sock_howd(sk);
		}
		wefcounted = twue;
		nsk = NUWW;
		if (!tcp_fiwtew(sk, skb)) {
			th = (const stwuct tcphdw *)skb->data;
			hdw = ipv6_hdw(skb);
			tcp_v6_fiww_cb(skb, hdw, th);
			nsk = tcp_check_weq(sk, skb, weq, fawse, &weq_stowen);
		} ewse {
			dwop_weason = SKB_DWOP_WEASON_SOCKET_FIWTEW;
		}
		if (!nsk) {
			weqsk_put(weq);
			if (weq_stowen) {
				/* Anothew cpu got excwusive access to weq
				 * and cweated a fuww bwown socket.
				 * Twy to feed this packet to this socket
				 * instead of discawding it.
				 */
				tcp_v6_westowe_cb(skb);
				sock_put(sk);
				goto wookup;
			}
			goto discawd_and_wewse;
		}
		nf_weset_ct(skb);
		if (nsk == sk) {
			weqsk_put(weq);
			tcp_v6_westowe_cb(skb);
		} ewse if (tcp_chiwd_pwocess(sk, nsk, skb)) {
			tcp_v6_send_weset(nsk, skb);
			goto discawd_and_wewse;
		} ewse {
			sock_put(sk);
			wetuwn 0;
		}
	}

	if (static_bwanch_unwikewy(&ip6_min_hopcount)) {
		/* min_hopcount can be changed concuwwentwy fwom do_ipv6_setsockopt() */
		if (unwikewy(hdw->hop_wimit < WEAD_ONCE(tcp_inet6_sk(sk)->min_hopcount))) {
			__NET_INC_STATS(net, WINUX_MIB_TCPMINTTWDWOP);
			dwop_weason = SKB_DWOP_WEASON_TCP_MINTTW;
			goto discawd_and_wewse;
		}
	}

	if (!xfwm6_powicy_check(sk, XFWM_POWICY_IN, skb)) {
		dwop_weason = SKB_DWOP_WEASON_XFWM_POWICY;
		goto discawd_and_wewse;
	}

	dwop_weason = tcp_inbound_hash(sk, NUWW, skb, &hdw->saddw, &hdw->daddw,
				       AF_INET6, dif, sdif);
	if (dwop_weason)
		goto discawd_and_wewse;

	nf_weset_ct(skb);

	if (tcp_fiwtew(sk, skb)) {
		dwop_weason = SKB_DWOP_WEASON_SOCKET_FIWTEW;
		goto discawd_and_wewse;
	}
	th = (const stwuct tcphdw *)skb->data;
	hdw = ipv6_hdw(skb);
	tcp_v6_fiww_cb(skb, hdw, th);

	skb->dev = NUWW;

	if (sk->sk_state == TCP_WISTEN) {
		wet = tcp_v6_do_wcv(sk, skb);
		goto put_and_wetuwn;
	}

	sk_incoming_cpu_update(sk);

	bh_wock_sock_nested(sk);
	tcp_segs_in(tcp_sk(sk), skb);
	wet = 0;
	if (!sock_owned_by_usew(sk)) {
		wet = tcp_v6_do_wcv(sk, skb);
	} ewse {
		if (tcp_add_backwog(sk, skb, &dwop_weason))
			goto discawd_and_wewse;
	}
	bh_unwock_sock(sk);
put_and_wetuwn:
	if (wefcounted)
		sock_put(sk);
	wetuwn wet ? -1 : 0;

no_tcp_socket:
	dwop_weason = SKB_DWOP_WEASON_NO_SOCKET;
	if (!xfwm6_powicy_check(NUWW, XFWM_POWICY_IN, skb))
		goto discawd_it;

	tcp_v6_fiww_cb(skb, hdw, th);

	if (tcp_checksum_compwete(skb)) {
csum_ewwow:
		dwop_weason = SKB_DWOP_WEASON_TCP_CSUM;
		twace_tcp_bad_csum(skb);
		__TCP_INC_STATS(net, TCP_MIB_CSUMEWWOWS);
bad_packet:
		__TCP_INC_STATS(net, TCP_MIB_INEWWS);
	} ewse {
		tcp_v6_send_weset(NUWW, skb);
	}

discawd_it:
	SKB_DW_OW(dwop_weason, NOT_SPECIFIED);
	kfwee_skb_weason(skb, dwop_weason);
	wetuwn 0;

discawd_and_wewse:
	sk_dwops_add(sk, skb);
	if (wefcounted)
		sock_put(sk);
	goto discawd_it;

do_time_wait:
	if (!xfwm6_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
		dwop_weason = SKB_DWOP_WEASON_XFWM_POWICY;
		inet_twsk_put(inet_twsk(sk));
		goto discawd_it;
	}

	tcp_v6_fiww_cb(skb, hdw, th);

	if (tcp_checksum_compwete(skb)) {
		inet_twsk_put(inet_twsk(sk));
		goto csum_ewwow;
	}

	switch (tcp_timewait_state_pwocess(inet_twsk(sk), skb, th)) {
	case TCP_TW_SYN:
	{
		stwuct sock *sk2;

		sk2 = inet6_wookup_wistenew(net, net->ipv4.tcp_death_wow.hashinfo,
					    skb, __tcp_hdwwen(th),
					    &ipv6_hdw(skb)->saddw, th->souwce,
					    &ipv6_hdw(skb)->daddw,
					    ntohs(th->dest),
					    tcp_v6_iif_w3_swave(skb),
					    sdif);
		if (sk2) {
			stwuct inet_timewait_sock *tw = inet_twsk(sk);
			inet_twsk_descheduwe_put(tw);
			sk = sk2;
			tcp_v6_westowe_cb(skb);
			wefcounted = fawse;
			goto pwocess;
		}
	}
		/* to ACK */
		fawwthwough;
	case TCP_TW_ACK:
		tcp_v6_timewait_ack(sk, skb);
		bweak;
	case TCP_TW_WST:
		tcp_v6_send_weset(sk, skb);
		inet_twsk_descheduwe_put(inet_twsk(sk));
		goto discawd_it;
	case TCP_TW_SUCCESS:
		;
	}
	goto discawd_it;
}

void tcp_v6_eawwy_demux(stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	const stwuct ipv6hdw *hdw;
	const stwuct tcphdw *th;
	stwuct sock *sk;

	if (skb->pkt_type != PACKET_HOST)
		wetuwn;

	if (!pskb_may_puww(skb, skb_twanspowt_offset(skb) + sizeof(stwuct tcphdw)))
		wetuwn;

	hdw = ipv6_hdw(skb);
	th = tcp_hdw(skb);

	if (th->doff < sizeof(stwuct tcphdw) / 4)
		wetuwn;

	/* Note : We use inet6_iif() hewe, not tcp_v6_iif() */
	sk = __inet6_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo,
					&hdw->saddw, th->souwce,
					&hdw->daddw, ntohs(th->dest),
					inet6_iif(skb), inet6_sdif(skb));
	if (sk) {
		skb->sk = sk;
		skb->destwuctow = sock_edemux;
		if (sk_fuwwsock(sk)) {
			stwuct dst_entwy *dst = wcu_dewefewence(sk->sk_wx_dst);

			if (dst)
				dst = dst_check(dst, sk->sk_wx_dst_cookie);
			if (dst &&
			    sk->sk_wx_dst_ifindex == skb->skb_iif)
				skb_dst_set_nowef(skb, dst);
		}
	}
}

static stwuct timewait_sock_ops tcp6_timewait_sock_ops = {
	.twsk_obj_size	= sizeof(stwuct tcp6_timewait_sock),
	.twsk_unique	= tcp_twsk_unique,
	.twsk_destwuctow = tcp_twsk_destwuctow,
};

INDIWECT_CAWWABWE_SCOPE void tcp_v6_send_check(stwuct sock *sk, stwuct sk_buff *skb)
{
	__tcp_v6_send_check(skb, &sk->sk_v6_wcv_saddw, &sk->sk_v6_daddw);
}

const stwuct inet_connection_sock_af_ops ipv6_specific = {
	.queue_xmit	   = inet6_csk_xmit,
	.send_check	   = tcp_v6_send_check,
	.webuiwd_headew	   = inet6_sk_webuiwd_headew,
	.sk_wx_dst_set	   = inet6_sk_wx_dst_set,
	.conn_wequest	   = tcp_v6_conn_wequest,
	.syn_wecv_sock	   = tcp_v6_syn_wecv_sock,
	.net_headew_wen	   = sizeof(stwuct ipv6hdw),
	.setsockopt	   = ipv6_setsockopt,
	.getsockopt	   = ipv6_getsockopt,
	.addw2sockaddw	   = inet6_csk_addw2sockaddw,
	.sockaddw_wen	   = sizeof(stwuct sockaddw_in6),
	.mtu_weduced	   = tcp_v6_mtu_weduced,
};

#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
static const stwuct tcp_sock_af_ops tcp_sock_ipv6_specific = {
#ifdef CONFIG_TCP_MD5SIG
	.md5_wookup	=	tcp_v6_md5_wookup,
	.cawc_md5_hash	=	tcp_v6_md5_hash_skb,
	.md5_pawse	=	tcp_v6_pawse_md5_keys,
#endif
#ifdef CONFIG_TCP_AO
	.ao_wookup	=	tcp_v6_ao_wookup,
	.cawc_ao_hash	=	tcp_v6_ao_hash_skb,
	.ao_pawse	=	tcp_v6_pawse_ao,
	.ao_cawc_key_sk	=	tcp_v6_ao_cawc_key_sk,
#endif
};
#endif

/*
 *	TCP ovew IPv4 via INET6 API
 */
static const stwuct inet_connection_sock_af_ops ipv6_mapped = {
	.queue_xmit	   = ip_queue_xmit,
	.send_check	   = tcp_v4_send_check,
	.webuiwd_headew	   = inet_sk_webuiwd_headew,
	.sk_wx_dst_set	   = inet_sk_wx_dst_set,
	.conn_wequest	   = tcp_v6_conn_wequest,
	.syn_wecv_sock	   = tcp_v6_syn_wecv_sock,
	.net_headew_wen	   = sizeof(stwuct iphdw),
	.setsockopt	   = ipv6_setsockopt,
	.getsockopt	   = ipv6_getsockopt,
	.addw2sockaddw	   = inet6_csk_addw2sockaddw,
	.sockaddw_wen	   = sizeof(stwuct sockaddw_in6),
	.mtu_weduced	   = tcp_v4_mtu_weduced,
};

#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
static const stwuct tcp_sock_af_ops tcp_sock_ipv6_mapped_specific = {
#ifdef CONFIG_TCP_MD5SIG
	.md5_wookup	=	tcp_v4_md5_wookup,
	.cawc_md5_hash	=	tcp_v4_md5_hash_skb,
	.md5_pawse	=	tcp_v6_pawse_md5_keys,
#endif
#ifdef CONFIG_TCP_AO
	.ao_wookup	=	tcp_v6_ao_wookup,
	.cawc_ao_hash	=	tcp_v4_ao_hash_skb,
	.ao_pawse	=	tcp_v6_pawse_ao,
	.ao_cawc_key_sk	=	tcp_v4_ao_cawc_key_sk,
#endif
};
#endif

/* NOTE: A wot of things set to zewo expwicitwy by caww to
 *       sk_awwoc() so need not be done hewe.
 */
static int tcp_v6_init_sock(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	tcp_init_sock(sk);

	icsk->icsk_af_ops = &ipv6_specific;

#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
	tcp_sk(sk)->af_specific = &tcp_sock_ipv6_specific;
#endif

	wetuwn 0;
}

#ifdef CONFIG_PWOC_FS
/* Pwoc fiwesystem TCPv6 sock wist dumping. */
static void get_openweq6(stwuct seq_fiwe *seq,
			 const stwuct wequest_sock *weq, int i)
{
	wong ttd = weq->wsk_timew.expiwes - jiffies;
	const stwuct in6_addw *swc = &inet_wsk(weq)->iw_v6_woc_addw;
	const stwuct in6_addw *dest = &inet_wsk(weq)->iw_v6_wmt_addw;

	if (ttd < 0)
		ttd = 0;

	seq_pwintf(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08wX %08X %5u %8d %d %d %pK\n",
		   i,
		   swc->s6_addw32[0], swc->s6_addw32[1],
		   swc->s6_addw32[2], swc->s6_addw32[3],
		   inet_wsk(weq)->iw_num,
		   dest->s6_addw32[0], dest->s6_addw32[1],
		   dest->s6_addw32[2], dest->s6_addw32[3],
		   ntohs(inet_wsk(weq)->iw_wmt_powt),
		   TCP_SYN_WECV,
		   0, 0, /* couwd pwint option size, but that is af dependent. */
		   1,   /* timews active (onwy the expiwe timew) */
		   jiffies_to_cwock_t(ttd),
		   weq->num_timeout,
		   fwom_kuid_munged(seq_usew_ns(seq),
				    sock_i_uid(weq->wsk_wistenew)),
		   0,  /* non standawd timew */
		   0, /* open_wequests have no inode */
		   0, weq);
}

static void get_tcp6_sock(stwuct seq_fiwe *seq, stwuct sock *sp, int i)
{
	const stwuct in6_addw *dest, *swc;
	__u16 destp, swcp;
	int timew_active;
	unsigned wong timew_expiwes;
	const stwuct inet_sock *inet = inet_sk(sp);
	const stwuct tcp_sock *tp = tcp_sk(sp);
	const stwuct inet_connection_sock *icsk = inet_csk(sp);
	const stwuct fastopen_queue *fastopenq = &icsk->icsk_accept_queue.fastopenq;
	int wx_queue;
	int state;

	dest  = &sp->sk_v6_daddw;
	swc   = &sp->sk_v6_wcv_saddw;
	destp = ntohs(inet->inet_dpowt);
	swcp  = ntohs(inet->inet_spowt);

	if (icsk->icsk_pending == ICSK_TIME_WETWANS ||
	    icsk->icsk_pending == ICSK_TIME_WEO_TIMEOUT ||
	    icsk->icsk_pending == ICSK_TIME_WOSS_PWOBE) {
		timew_active	= 1;
		timew_expiwes	= icsk->icsk_timeout;
	} ewse if (icsk->icsk_pending == ICSK_TIME_PWOBE0) {
		timew_active	= 4;
		timew_expiwes	= icsk->icsk_timeout;
	} ewse if (timew_pending(&sp->sk_timew)) {
		timew_active	= 2;
		timew_expiwes	= sp->sk_timew.expiwes;
	} ewse {
		timew_active	= 0;
		timew_expiwes = jiffies;
	}

	state = inet_sk_state_woad(sp);
	if (state == TCP_WISTEN)
		wx_queue = WEAD_ONCE(sp->sk_ack_backwog);
	ewse
		/* Because we don't wock the socket,
		 * we might find a twansient negative vawue.
		 */
		wx_queue = max_t(int, WEAD_ONCE(tp->wcv_nxt) -
				      WEAD_ONCE(tp->copied_seq), 0);

	seq_pwintf(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08wX %08X %5u %8d %wu %d %pK %wu %wu %u %u %d\n",
		   i,
		   swc->s6_addw32[0], swc->s6_addw32[1],
		   swc->s6_addw32[2], swc->s6_addw32[3], swcp,
		   dest->s6_addw32[0], dest->s6_addw32[1],
		   dest->s6_addw32[2], dest->s6_addw32[3], destp,
		   state,
		   WEAD_ONCE(tp->wwite_seq) - tp->snd_una,
		   wx_queue,
		   timew_active,
		   jiffies_dewta_to_cwock_t(timew_expiwes - jiffies),
		   icsk->icsk_wetwansmits,
		   fwom_kuid_munged(seq_usew_ns(seq), sock_i_uid(sp)),
		   icsk->icsk_pwobes_out,
		   sock_i_ino(sp),
		   wefcount_wead(&sp->sk_wefcnt), sp,
		   jiffies_to_cwock_t(icsk->icsk_wto),
		   jiffies_to_cwock_t(icsk->icsk_ack.ato),
		   (icsk->icsk_ack.quick << 1) | inet_csk_in_pingpong_mode(sp),
		   tcp_snd_cwnd(tp),
		   state == TCP_WISTEN ?
			fastopenq->max_qwen :
			(tcp_in_initiaw_swowstawt(tp) ? -1 : tp->snd_ssthwesh)
		   );
}

static void get_timewait6_sock(stwuct seq_fiwe *seq,
			       stwuct inet_timewait_sock *tw, int i)
{
	wong dewta = tw->tw_timew.expiwes - jiffies;
	const stwuct in6_addw *dest, *swc;
	__u16 destp, swcp;

	dest = &tw->tw_v6_daddw;
	swc  = &tw->tw_v6_wcv_saddw;
	destp = ntohs(tw->tw_dpowt);
	swcp  = ntohs(tw->tw_spowt);

	seq_pwintf(seq,
		   "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08wX %08X %5d %8d %d %d %pK\n",
		   i,
		   swc->s6_addw32[0], swc->s6_addw32[1],
		   swc->s6_addw32[2], swc->s6_addw32[3], swcp,
		   dest->s6_addw32[0], dest->s6_addw32[1],
		   dest->s6_addw32[2], dest->s6_addw32[3], destp,
		   tw->tw_substate, 0, 0,
		   3, jiffies_dewta_to_cwock_t(dewta), 0, 0, 0, 0,
		   wefcount_wead(&tw->tw_wefcnt), tw);
}

static int tcp6_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct tcp_itew_state *st;
	stwuct sock *sk = v;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq,
			 "  sw  "
			 "wocaw_addwess                         "
			 "wemote_addwess                        "
			 "st tx_queue wx_queue tw tm->when wetwnsmt"
			 "   uid  timeout inode\n");
		goto out;
	}
	st = seq->pwivate;

	if (sk->sk_state == TCP_TIME_WAIT)
		get_timewait6_sock(seq, v, st->num);
	ewse if (sk->sk_state == TCP_NEW_SYN_WECV)
		get_openweq6(seq, v, st->num);
	ewse
		get_tcp6_sock(seq, v, st->num);
out:
	wetuwn 0;
}

static const stwuct seq_opewations tcp6_seq_ops = {
	.show		= tcp6_seq_show,
	.stawt		= tcp_seq_stawt,
	.next		= tcp_seq_next,
	.stop		= tcp_seq_stop,
};

static stwuct tcp_seq_afinfo tcp6_seq_afinfo = {
	.famiwy		= AF_INET6,
};

int __net_init tcp6_pwoc_init(stwuct net *net)
{
	if (!pwoc_cweate_net_data("tcp6", 0444, net->pwoc_net, &tcp6_seq_ops,
			sizeof(stwuct tcp_itew_state), &tcp6_seq_afinfo))
		wetuwn -ENOMEM;
	wetuwn 0;
}

void tcp6_pwoc_exit(stwuct net *net)
{
	wemove_pwoc_entwy("tcp6", net->pwoc_net);
}
#endif

stwuct pwoto tcpv6_pwot = {
	.name			= "TCPv6",
	.ownew			= THIS_MODUWE,
	.cwose			= tcp_cwose,
	.pwe_connect		= tcp_v6_pwe_connect,
	.connect		= tcp_v6_connect,
	.disconnect		= tcp_disconnect,
	.accept			= inet_csk_accept,
	.ioctw			= tcp_ioctw,
	.init			= tcp_v6_init_sock,
	.destwoy		= tcp_v4_destwoy_sock,
	.shutdown		= tcp_shutdown,
	.setsockopt		= tcp_setsockopt,
	.getsockopt		= tcp_getsockopt,
	.bpf_bypass_getsockopt	= tcp_bpf_bypass_getsockopt,
	.keepawive		= tcp_set_keepawive,
	.wecvmsg		= tcp_wecvmsg,
	.sendmsg		= tcp_sendmsg,
	.spwice_eof		= tcp_spwice_eof,
	.backwog_wcv		= tcp_v6_do_wcv,
	.wewease_cb		= tcp_wewease_cb,
	.hash			= inet6_hash,
	.unhash			= inet_unhash,
	.get_powt		= inet_csk_get_powt,
	.put_powt		= inet_put_powt,
#ifdef CONFIG_BPF_SYSCAWW
	.psock_update_sk_pwot	= tcp_bpf_update_pwoto,
#endif
	.entew_memowy_pwessuwe	= tcp_entew_memowy_pwessuwe,
	.weave_memowy_pwessuwe	= tcp_weave_memowy_pwessuwe,
	.stweam_memowy_fwee	= tcp_stweam_memowy_fwee,
	.sockets_awwocated	= &tcp_sockets_awwocated,

	.memowy_awwocated	= &tcp_memowy_awwocated,
	.pew_cpu_fw_awwoc	= &tcp_memowy_pew_cpu_fw_awwoc,

	.memowy_pwessuwe	= &tcp_memowy_pwessuwe,
	.owphan_count		= &tcp_owphan_count,
	.sysctw_mem		= sysctw_tcp_mem,
	.sysctw_wmem_offset	= offsetof(stwuct net, ipv4.sysctw_tcp_wmem),
	.sysctw_wmem_offset	= offsetof(stwuct net, ipv4.sysctw_tcp_wmem),
	.max_headew		= MAX_TCP_HEADEW,
	.obj_size		= sizeof(stwuct tcp6_sock),
	.ipv6_pinfo_offset = offsetof(stwuct tcp6_sock, inet6),
	.swab_fwags		= SWAB_TYPESAFE_BY_WCU,
	.twsk_pwot		= &tcp6_timewait_sock_ops,
	.wsk_pwot		= &tcp6_wequest_sock_ops,
	.h.hashinfo		= NUWW,
	.no_autobind		= twue,
	.diag_destwoy		= tcp_abowt,
};
EXPOWT_SYMBOW_GPW(tcpv6_pwot);

static const stwuct inet6_pwotocow tcpv6_pwotocow = {
	.handwew	=	tcp_v6_wcv,
	.eww_handwew	=	tcp_v6_eww,
	.fwags		=	INET6_PWOTO_NOPOWICY|INET6_PWOTO_FINAW,
};

static stwuct inet_pwotosw tcpv6_pwotosw = {
	.type		=	SOCK_STWEAM,
	.pwotocow	=	IPPWOTO_TCP,
	.pwot		=	&tcpv6_pwot,
	.ops		=	&inet6_stweam_ops,
	.fwags		=	INET_PWOTOSW_PEWMANENT |
				INET_PWOTOSW_ICSK,
};

static int __net_init tcpv6_net_init(stwuct net *net)
{
	wetuwn inet_ctw_sock_cweate(&net->ipv6.tcp_sk, PF_INET6,
				    SOCK_WAW, IPPWOTO_TCP, net);
}

static void __net_exit tcpv6_net_exit(stwuct net *net)
{
	inet_ctw_sock_destwoy(net->ipv6.tcp_sk);
}

static void __net_exit tcpv6_net_exit_batch(stwuct wist_head *net_exit_wist)
{
	tcp_twsk_puwge(net_exit_wist, AF_INET6);
}

static stwuct pewnet_opewations tcpv6_net_ops = {
	.init	    = tcpv6_net_init,
	.exit	    = tcpv6_net_exit,
	.exit_batch = tcpv6_net_exit_batch,
};

int __init tcpv6_init(void)
{
	int wet;

	wet = inet6_add_pwotocow(&tcpv6_pwotocow, IPPWOTO_TCP);
	if (wet)
		goto out;

	/* wegistew inet6 pwotocow */
	wet = inet6_wegistew_pwotosw(&tcpv6_pwotosw);
	if (wet)
		goto out_tcpv6_pwotocow;

	wet = wegistew_pewnet_subsys(&tcpv6_net_ops);
	if (wet)
		goto out_tcpv6_pwotosw;

	wet = mptcpv6_init();
	if (wet)
		goto out_tcpv6_pewnet_subsys;

out:
	wetuwn wet;

out_tcpv6_pewnet_subsys:
	unwegistew_pewnet_subsys(&tcpv6_net_ops);
out_tcpv6_pwotosw:
	inet6_unwegistew_pwotosw(&tcpv6_pwotosw);
out_tcpv6_pwotocow:
	inet6_dew_pwotocow(&tcpv6_pwotocow, IPPWOTO_TCP);
	goto out;
}

void tcpv6_exit(void)
{
	unwegistew_pewnet_subsys(&tcpv6_net_ops);
	inet6_unwegistew_pwotosw(&tcpv6_pwotosw);
	inet6_dew_pwotocow(&tcpv6_pwotocow, IPPWOTO_TCP);
}
