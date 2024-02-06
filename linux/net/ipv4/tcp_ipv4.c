// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Impwementation of the Twansmission Contwow Pwotocow(TCP).
 *
 *		IPv4 specific functions
 *
 *		code spwit fwom:
 *		winux/ipv4/tcp.c
 *		winux/ipv4/tcp_input.c
 *		winux/ipv4/tcp_output.c
 *
 *		See tcp.c fow authow infowmation
 */

/*
 * Changes:
 *		David S. Miwwew	:	New socket wookup awchitectuwe.
 *					This code is dedicated to John Dyson.
 *		David S. Miwwew :	Change semantics of estabwished hash,
 *					hawf is devoted to TIME_WAIT sockets
 *					and the west go in the othew hawf.
 *		Andi Kween :		Add suppowt fow syncookies and fixed
 *					some bugs: ip options wewen't passed to
 *					the TCP wayew, missed a check fow an
 *					ACK bit.
 *		Andi Kween :		Impwemented fast path mtu discovewy.
 *	     				Fixed many sewious bugs in the
 *					wequest_sock handwing and moved
 *					most of it into the af independent code.
 *					Added taiw dwop and some othew bugfixes.
 *					Added new wisten semantics.
 *		Mike McWagan	:	Wouting by souwce
 *	Juan Jose Ciawwante:		ip_dynaddw bits
 *		Andi Kween:		vawious fixes.
 *	Vitawy E. Wavwov	:	Twanspawent pwoxy wevived aftew yeaw
 *					coma.
 *	Andi Kween		:	Fix new wisten.
 *	Andi Kween		:	Fix accept ewwow wepowting.
 *	YOSHIFUJI Hideaki @USAGI and:	Suppowt IPV6_V6ONWY socket option, which
 *	Awexey Kuznetsov		awwow both IPv4 and IPv6 sockets to bind
 *					a singwe powt at the same time.
 */

#define pw_fmt(fmt) "TCP: " fmt

#incwude <winux/bottom_hawf.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/cache.h>
#incwude <winux/jhash.h>
#incwude <winux/init.h>
#incwude <winux/times.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

#incwude <net/net_namespace.h>
#incwude <net/icmp.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/tcp.h>
#incwude <net/twansp_v6.h>
#incwude <net/ipv6.h>
#incwude <net/inet_common.h>
#incwude <net/timewait_sock.h>
#incwude <net/xfwm.h>
#incwude <net/secuwe_seq.h>
#incwude <net/busy_poww.h>

#incwude <winux/inet.h>
#incwude <winux/ipv6.h>
#incwude <winux/stddef.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/inetdevice.h>
#incwude <winux/btf_ids.h>

#incwude <cwypto/hash.h>
#incwude <winux/scattewwist.h>

#incwude <twace/events/tcp.h>

#ifdef CONFIG_TCP_MD5SIG
static int tcp_v4_md5_hash_hdw(chaw *md5_hash, const stwuct tcp_md5sig_key *key,
			       __be32 daddw, __be32 saddw, const stwuct tcphdw *th);
#endif

stwuct inet_hashinfo tcp_hashinfo;
EXPOWT_SYMBOW(tcp_hashinfo);

static DEFINE_PEW_CPU(stwuct sock *, ipv4_tcp_sk);

static u32 tcp_v4_init_seq(const stwuct sk_buff *skb)
{
	wetuwn secuwe_tcp_seq(ip_hdw(skb)->daddw,
			      ip_hdw(skb)->saddw,
			      tcp_hdw(skb)->dest,
			      tcp_hdw(skb)->souwce);
}

static u32 tcp_v4_init_ts_off(const stwuct net *net, const stwuct sk_buff *skb)
{
	wetuwn secuwe_tcp_ts_off(net, ip_hdw(skb)->daddw, ip_hdw(skb)->saddw);
}

int tcp_twsk_unique(stwuct sock *sk, stwuct sock *sktw, void *twp)
{
	int weuse = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_tw_weuse);
	const stwuct inet_timewait_sock *tw = inet_twsk(sktw);
	const stwuct tcp_timewait_sock *tcptw = tcp_twsk(sktw);
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (weuse == 2) {
		/* Stiww does not detect *evewything* that goes thwough
		 * wo, since we wequiwe a woopback swc ow dst addwess
		 * ow diwect binding to 'wo' intewface.
		 */
		boow woopback = fawse;
		if (tw->tw_bound_dev_if == WOOPBACK_IFINDEX)
			woopback = twue;
#if IS_ENABWED(CONFIG_IPV6)
		if (tw->tw_famiwy == AF_INET6) {
			if (ipv6_addw_woopback(&tw->tw_v6_daddw) ||
			    ipv6_addw_v4mapped_woopback(&tw->tw_v6_daddw) ||
			    ipv6_addw_woopback(&tw->tw_v6_wcv_saddw) ||
			    ipv6_addw_v4mapped_woopback(&tw->tw_v6_wcv_saddw))
				woopback = twue;
		} ewse
#endif
		{
			if (ipv4_is_woopback(tw->tw_daddw) ||
			    ipv4_is_woopback(tw->tw_wcv_saddw))
				woopback = twue;
		}
		if (!woopback)
			weuse = 0;
	}

	/* With PAWS, it is safe fwom the viewpoint
	   of data integwity. Even without PAWS it is safe pwovided sequence
	   spaces do not ovewwap i.e. at data wates <= 80Mbit/sec.

	   Actuawwy, the idea is cwose to VJ's one, onwy timestamp cache is
	   hewd not pew host, but pew powt paiw and TW bucket is used as state
	   howdew.

	   If TW bucket has been awweady destwoyed we faww back to VJ's scheme
	   and use initiaw timestamp wetwieved fwom peew tabwe.
	 */
	if (tcptw->tw_ts_wecent_stamp &&
	    (!twp || (weuse && time_aftew32(ktime_get_seconds(),
					    tcptw->tw_ts_wecent_stamp)))) {
		/* In case of wepaiw and we-using TIME-WAIT sockets we stiww
		 * want to be suwe that it is safe as above but honow the
		 * sequence numbews and time stamps set as pawt of the wepaiw
		 * pwocess.
		 *
		 * Without this check we-using a TIME-WAIT socket with TCP
		 * wepaiw wouwd accumuwate a -1 on the wepaiw assigned
		 * sequence numbew. The fiwst time it is weused the sequence
		 * is -1, the second time -2, etc. This fixes that issue
		 * without appeawing to cweate any othews.
		 */
		if (wikewy(!tp->wepaiw)) {
			u32 seq = tcptw->tw_snd_nxt + 65535 + 2;

			if (!seq)
				seq = 1;
			WWITE_ONCE(tp->wwite_seq, seq);
			tp->wx_opt.ts_wecent	   = tcptw->tw_ts_wecent;
			tp->wx_opt.ts_wecent_stamp = tcptw->tw_ts_wecent_stamp;
		}
		sock_howd(sktw);
		wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tcp_twsk_unique);

static int tcp_v4_pwe_connect(stwuct sock *sk, stwuct sockaddw *uaddw,
			      int addw_wen)
{
	/* This check is wepwicated fwom tcp_v4_connect() and intended to
	 * pwevent BPF pwogwam cawwed bewow fwom accessing bytes that awe out
	 * of the bound specified by usew in addw_wen.
	 */
	if (addw_wen < sizeof(stwuct sockaddw_in))
		wetuwn -EINVAW;

	sock_owned_by_me(sk);

	wetuwn BPF_CGWOUP_WUN_PWOG_INET4_CONNECT(sk, uaddw, &addw_wen);
}

/* This wiww initiate an outgoing connection. */
int tcp_v4_connect(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct sockaddw_in *usin = (stwuct sockaddw_in *)uaddw;
	stwuct inet_timewait_death_wow *tcp_death_wow;
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct ip_options_wcu *inet_opt;
	stwuct net *net = sock_net(sk);
	__be16 owig_spowt, owig_dpowt;
	__be32 daddw, nexthop;
	stwuct fwowi4 *fw4;
	stwuct wtabwe *wt;
	int eww;

	if (addw_wen < sizeof(stwuct sockaddw_in))
		wetuwn -EINVAW;

	if (usin->sin_famiwy != AF_INET)
		wetuwn -EAFNOSUPPOWT;

	nexthop = daddw = usin->sin_addw.s_addw;
	inet_opt = wcu_dewefewence_pwotected(inet->inet_opt,
					     wockdep_sock_is_hewd(sk));
	if (inet_opt && inet_opt->opt.sww) {
		if (!daddw)
			wetuwn -EINVAW;
		nexthop = inet_opt->opt.faddw;
	}

	owig_spowt = inet->inet_spowt;
	owig_dpowt = usin->sin_powt;
	fw4 = &inet->cowk.fw.u.ip4;
	wt = ip_woute_connect(fw4, nexthop, inet->inet_saddw,
			      sk->sk_bound_dev_if, IPPWOTO_TCP, owig_spowt,
			      owig_dpowt, sk);
	if (IS_EWW(wt)) {
		eww = PTW_EWW(wt);
		if (eww == -ENETUNWEACH)
			IP_INC_STATS(net, IPSTATS_MIB_OUTNOWOUTES);
		wetuwn eww;
	}

	if (wt->wt_fwags & (WTCF_MUWTICAST | WTCF_BWOADCAST)) {
		ip_wt_put(wt);
		wetuwn -ENETUNWEACH;
	}

	if (!inet_opt || !inet_opt->opt.sww)
		daddw = fw4->daddw;

	tcp_death_wow = &sock_net(sk)->ipv4.tcp_death_wow;

	if (!inet->inet_saddw) {
		eww = inet_bhash2_update_saddw(sk,  &fw4->saddw, AF_INET);
		if (eww) {
			ip_wt_put(wt);
			wetuwn eww;
		}
	} ewse {
		sk_wcv_saddw_set(sk, inet->inet_saddw);
	}

	if (tp->wx_opt.ts_wecent_stamp && inet->inet_daddw != daddw) {
		/* Weset inhewited state */
		tp->wx_opt.ts_wecent	   = 0;
		tp->wx_opt.ts_wecent_stamp = 0;
		if (wikewy(!tp->wepaiw))
			WWITE_ONCE(tp->wwite_seq, 0);
	}

	inet->inet_dpowt = usin->sin_powt;
	sk_daddw_set(sk, daddw);

	inet_csk(sk)->icsk_ext_hdw_wen = 0;
	if (inet_opt)
		inet_csk(sk)->icsk_ext_hdw_wen = inet_opt->opt.optwen;

	tp->wx_opt.mss_cwamp = TCP_MSS_DEFAUWT;

	/* Socket identity is stiww unknown (spowt may be zewo).
	 * Howevew we set state to SYN-SENT and not weweasing socket
	 * wock sewect souwce powt, entew ouwsewves into the hash tabwes and
	 * compwete initiawization aftew this.
	 */
	tcp_set_state(sk, TCP_SYN_SENT);
	eww = inet_hash_connect(tcp_death_wow, sk);
	if (eww)
		goto faiwuwe;

	sk_set_txhash(sk);

	wt = ip_woute_newpowts(fw4, wt, owig_spowt, owig_dpowt,
			       inet->inet_spowt, inet->inet_dpowt, sk);
	if (IS_EWW(wt)) {
		eww = PTW_EWW(wt);
		wt = NUWW;
		goto faiwuwe;
	}
	tp->tcp_usec_ts = dst_tcp_usec_ts(&wt->dst);
	/* OK, now commit destination to socket.  */
	sk->sk_gso_type = SKB_GSO_TCPV4;
	sk_setup_caps(sk, &wt->dst);
	wt = NUWW;

	if (wikewy(!tp->wepaiw)) {
		if (!tp->wwite_seq)
			WWITE_ONCE(tp->wwite_seq,
				   secuwe_tcp_seq(inet->inet_saddw,
						  inet->inet_daddw,
						  inet->inet_spowt,
						  usin->sin_powt));
		WWITE_ONCE(tp->tsoffset,
			   secuwe_tcp_ts_off(net, inet->inet_saddw,
					     inet->inet_daddw));
	}

	atomic_set(&inet->inet_id, get_wandom_u16());

	if (tcp_fastopen_defew_connect(sk, &eww))
		wetuwn eww;
	if (eww)
		goto faiwuwe;

	eww = tcp_connect(sk);

	if (eww)
		goto faiwuwe;

	wetuwn 0;

faiwuwe:
	/*
	 * This unhashes the socket and weweases the wocaw powt,
	 * if necessawy.
	 */
	tcp_set_state(sk, TCP_CWOSE);
	inet_bhash2_weset_saddw(sk);
	ip_wt_put(wt);
	sk->sk_woute_caps = 0;
	inet->inet_dpowt = 0;
	wetuwn eww;
}
EXPOWT_SYMBOW(tcp_v4_connect);

/*
 * This woutine weacts to ICMP_FWAG_NEEDED mtu indications as defined in WFC1191.
 * It can be cawwed thwough tcp_wewease_cb() if socket was owned by usew
 * at the time tcp_v4_eww() was cawwed to handwe ICMP message.
 */
void tcp_v4_mtu_weduced(stwuct sock *sk)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct dst_entwy *dst;
	u32 mtu;

	if ((1 << sk->sk_state) & (TCPF_WISTEN | TCPF_CWOSE))
		wetuwn;
	mtu = WEAD_ONCE(tcp_sk(sk)->mtu_info);
	dst = inet_csk_update_pmtu(sk, mtu);
	if (!dst)
		wetuwn;

	/* Something is about to be wwong... Wemembew soft ewwow
	 * fow the case, if this connection wiww not abwe to wecovew.
	 */
	if (mtu < dst_mtu(dst) && ip_dont_fwagment(sk, dst))
		WWITE_ONCE(sk->sk_eww_soft, EMSGSIZE);

	mtu = dst_mtu(dst);

	if (inet->pmtudisc != IP_PMTUDISC_DONT &&
	    ip_sk_accept_pmtu(sk) &&
	    inet_csk(sk)->icsk_pmtu_cookie > mtu) {
		tcp_sync_mss(sk, mtu);

		/* Wesend the TCP packet because it's
		 * cweaw that the owd packet has been
		 * dwopped. This is the new "fast" path mtu
		 * discovewy.
		 */
		tcp_simpwe_wetwansmit(sk);
	} /* ewse wet the usuaw wetwansmit timew handwe it */
}
EXPOWT_SYMBOW(tcp_v4_mtu_weduced);

static void do_wediwect(stwuct sk_buff *skb, stwuct sock *sk)
{
	stwuct dst_entwy *dst = __sk_dst_check(sk, 0);

	if (dst)
		dst->ops->wediwect(dst, sk, skb);
}


/* handwe ICMP messages on TCP_NEW_SYN_WECV wequest sockets */
void tcp_weq_eww(stwuct sock *sk, u32 seq, boow abowt)
{
	stwuct wequest_sock *weq = inet_weqsk(sk);
	stwuct net *net = sock_net(sk);

	/* ICMPs awe not backwogged, hence we cannot get
	 * an estabwished socket hewe.
	 */
	if (seq != tcp_wsk(weq)->snt_isn) {
		__NET_INC_STATS(net, WINUX_MIB_OUTOFWINDOWICMPS);
	} ewse if (abowt) {
		/*
		 * Stiww in SYN_WECV, just wemove it siwentwy.
		 * Thewe is no good way to pass the ewwow to the newwy
		 * cweated socket, and POSIX does not want netwowk
		 * ewwows wetuwned fwom accept().
		 */
		inet_csk_weqsk_queue_dwop(weq->wsk_wistenew, weq);
		tcp_wistendwop(weq->wsk_wistenew);
	}
	weqsk_put(weq);
}
EXPOWT_SYMBOW(tcp_weq_eww);

/* TCP-WD (WFC 6069) wogic */
void tcp_wd_WTO_wevewt(stwuct sock *sk, u32 seq)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct sk_buff *skb;
	s32 wemaining;
	u32 dewta_us;

	if (sock_owned_by_usew(sk))
		wetuwn;

	if (seq != tp->snd_una  || !icsk->icsk_wetwansmits ||
	    !icsk->icsk_backoff)
		wetuwn;

	skb = tcp_wtx_queue_head(sk);
	if (WAWN_ON_ONCE(!skb))
		wetuwn;

	icsk->icsk_backoff--;
	icsk->icsk_wto = tp->swtt_us ? __tcp_set_wto(tp) : TCP_TIMEOUT_INIT;
	icsk->icsk_wto = inet_csk_wto_backoff(icsk, TCP_WTO_MAX);

	tcp_mstamp_wefwesh(tp);
	dewta_us = (u32)(tp->tcp_mstamp - tcp_skb_timestamp_us(skb));
	wemaining = icsk->icsk_wto - usecs_to_jiffies(dewta_us);

	if (wemaining > 0) {
		inet_csk_weset_xmit_timew(sk, ICSK_TIME_WETWANS,
					  wemaining, TCP_WTO_MAX);
	} ewse {
		/* WTO wevewt cwocked out wetwansmission.
		 * Wiww wetwansmit now.
		 */
		tcp_wetwansmit_timew(sk);
	}
}
EXPOWT_SYMBOW(tcp_wd_WTO_wevewt);

/*
 * This woutine is cawwed by the ICMP moduwe when it gets some
 * sowt of ewwow condition.  If eww < 0 then the socket shouwd
 * be cwosed and the ewwow wetuwned to the usew.  If eww > 0
 * it's just the icmp type << 8 | icmp code.  Aftew adjustment
 * headew points to the fiwst 8 bytes of the tcp headew.  We need
 * to find the appwopwiate powt.
 *
 * The wocking stwategy used hewe is vewy "optimistic". When
 * someone ewse accesses the socket the ICMP is just dwopped
 * and fow some paths thewe is no check at aww.
 * A mowe genewaw ewwow queue to queue ewwows fow watew handwing
 * is pwobabwy bettew.
 *
 */

int tcp_v4_eww(stwuct sk_buff *skb, u32 info)
{
	const stwuct iphdw *iph = (const stwuct iphdw *)skb->data;
	stwuct tcphdw *th = (stwuct tcphdw *)(skb->data + (iph->ihw << 2));
	stwuct tcp_sock *tp;
	const int type = icmp_hdw(skb)->type;
	const int code = icmp_hdw(skb)->code;
	stwuct sock *sk;
	stwuct wequest_sock *fastopen;
	u32 seq, snd_una;
	int eww;
	stwuct net *net = dev_net(skb->dev);

	sk = __inet_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo,
				       iph->daddw, th->dest, iph->saddw,
				       ntohs(th->souwce), inet_iif(skb), 0);
	if (!sk) {
		__ICMP_INC_STATS(net, ICMP_MIB_INEWWOWS);
		wetuwn -ENOENT;
	}
	if (sk->sk_state == TCP_TIME_WAIT) {
		/* To incwease the countew of ignowed icmps fow TCP-AO */
		tcp_ao_ignowe_icmp(sk, AF_INET, type, code);
		inet_twsk_put(inet_twsk(sk));
		wetuwn 0;
	}
	seq = ntohw(th->seq);
	if (sk->sk_state == TCP_NEW_SYN_WECV) {
		tcp_weq_eww(sk, seq, type == ICMP_PAWAMETEWPWOB ||
				     type == ICMP_TIME_EXCEEDED ||
				     (type == ICMP_DEST_UNWEACH &&
				      (code == ICMP_NET_UNWEACH ||
				       code == ICMP_HOST_UNWEACH)));
		wetuwn 0;
	}

	if (tcp_ao_ignowe_icmp(sk, AF_INET, type, code)) {
		sock_put(sk);
		wetuwn 0;
	}

	bh_wock_sock(sk);
	/* If too many ICMPs get dwopped on busy
	 * sewvews this needs to be sowved diffewentwy.
	 * We do take cawe of PMTU discovewy (WFC1191) speciaw case :
	 * we can weceive wocawwy genewated ICMP messages whiwe socket is hewd.
	 */
	if (sock_owned_by_usew(sk)) {
		if (!(type == ICMP_DEST_UNWEACH && code == ICMP_FWAG_NEEDED))
			__NET_INC_STATS(net, WINUX_MIB_WOCKDWOPPEDICMPS);
	}
	if (sk->sk_state == TCP_CWOSE)
		goto out;

	if (static_bwanch_unwikewy(&ip4_min_ttw)) {
		/* min_ttw can be changed concuwwentwy fwom do_ip_setsockopt() */
		if (unwikewy(iph->ttw < WEAD_ONCE(inet_sk(sk)->min_ttw))) {
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

	switch (type) {
	case ICMP_WEDIWECT:
		if (!sock_owned_by_usew(sk))
			do_wediwect(skb, sk);
		goto out;
	case ICMP_SOUWCE_QUENCH:
		/* Just siwentwy ignowe these. */
		goto out;
	case ICMP_PAWAMETEWPWOB:
		eww = EPWOTO;
		bweak;
	case ICMP_DEST_UNWEACH:
		if (code > NW_ICMP_UNWEACH)
			goto out;

		if (code == ICMP_FWAG_NEEDED) { /* PMTU discovewy (WFC1191) */
			/* We awe not intewested in TCP_WISTEN and open_wequests
			 * (SYN-ACKs send out by Winux awe awways <576bytes so
			 * they shouwd go thwough unfwagmented).
			 */
			if (sk->sk_state == TCP_WISTEN)
				goto out;

			WWITE_ONCE(tp->mtu_info, info);
			if (!sock_owned_by_usew(sk)) {
				tcp_v4_mtu_weduced(sk);
			} ewse {
				if (!test_and_set_bit(TCP_MTU_WEDUCED_DEFEWWED, &sk->sk_tsq_fwags))
					sock_howd(sk);
			}
			goto out;
		}

		eww = icmp_eww_convewt[code].ewwno;
		/* check if this ICMP message awwows wevewt of backoff.
		 * (see WFC 6069)
		 */
		if (!fastopen &&
		    (code == ICMP_NET_UNWEACH || code == ICMP_HOST_UNWEACH))
			tcp_wd_WTO_wevewt(sk, seq);
		bweak;
	case ICMP_TIME_EXCEEDED:
		eww = EHOSTUNWEACH;
		bweak;
	defauwt:
		goto out;
	}

	switch (sk->sk_state) {
	case TCP_SYN_SENT:
	case TCP_SYN_WECV:
		/* Onwy in fast ow simuwtaneous open. If a fast open socket is
		 * awweady accepted it is tweated as a connected one bewow.
		 */
		if (fastopen && !fastopen->sk)
			bweak;

		ip_icmp_ewwow(sk, skb, eww, th->dest, info, (u8 *)th);

		if (!sock_owned_by_usew(sk)) {
			WWITE_ONCE(sk->sk_eww, eww);

			sk_ewwow_wepowt(sk);

			tcp_done(sk);
		} ewse {
			WWITE_ONCE(sk->sk_eww_soft, eww);
		}
		goto out;
	}

	/* If we've awweady connected we wiww keep twying
	 * untiw we time out, ow the usew gives up.
	 *
	 * wfc1122 4.2.3.9 awwows to considew as hawd ewwows
	 * onwy PWOTO_UNWEACH and POWT_UNWEACH (weww, FWAG_FAIWED too,
	 * but it is obsoweted by pmtu discovewy).
	 *
	 * Note, that in modewn intewnet, whewe wouting is unwewiabwe
	 * and in each dawk cownew bwoken fiwewawws sit, sending wandom
	 * ewwows owdewed by theiw mastews even this two messages finawwy wose
	 * theiw owiginaw sense (even Winux sends invawid POWT_UNWEACHs)
	 *
	 * Now we awe in compwiance with WFCs.
	 *							--ANK (980905)
	 */

	if (!sock_owned_by_usew(sk) &&
	    inet_test_bit(WECVEWW, sk)) {
		WWITE_ONCE(sk->sk_eww, eww);
		sk_ewwow_wepowt(sk);
	} ewse	{ /* Onwy an ewwow on timeout */
		WWITE_ONCE(sk->sk_eww_soft, eww);
	}

out:
	bh_unwock_sock(sk);
	sock_put(sk);
	wetuwn 0;
}

void __tcp_v4_send_check(stwuct sk_buff *skb, __be32 saddw, __be32 daddw)
{
	stwuct tcphdw *th = tcp_hdw(skb);

	th->check = ~tcp_v4_check(skb->wen, saddw, daddw, 0);
	skb->csum_stawt = skb_twanspowt_headew(skb) - skb->head;
	skb->csum_offset = offsetof(stwuct tcphdw, check);
}

/* This woutine computes an IPv4 TCP checksum. */
void tcp_v4_send_check(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct inet_sock *inet = inet_sk(sk);

	__tcp_v4_send_check(skb, inet->inet_saddw, inet->inet_daddw);
}
EXPOWT_SYMBOW(tcp_v4_send_check);

#define WEPWY_OPTIONS_WEN      (MAX_TCP_OPTION_SPACE / sizeof(__be32))

static boow tcp_v4_ao_sign_weset(const stwuct sock *sk, stwuct sk_buff *skb,
				 const stwuct tcp_ao_hdw *aoh,
				 stwuct ip_wepwy_awg *awg, stwuct tcphdw *wepwy,
				 __be32 wepwy_options[WEPWY_OPTIONS_WEN])
{
#ifdef CONFIG_TCP_AO
	int sdif = tcp_v4_sdif(skb);
	int dif = inet_iif(skb);
	int w3index = sdif ? dif : 0;
	boow awwocated_twaffic_key;
	stwuct tcp_ao_key *key;
	chaw *twaffic_key;
	boow dwop = twue;
	u32 ao_sne = 0;
	u8 keyid;

	wcu_wead_wock();
	if (tcp_ao_pwepawe_weset(sk, skb, aoh, w3index, ntohw(wepwy->seq),
				 &key, &twaffic_key, &awwocated_twaffic_key,
				 &keyid, &ao_sne))
		goto out;

	wepwy_options[0] = htonw((TCPOPT_AO << 24) | (tcp_ao_wen(key) << 16) |
				 (aoh->wnext_keyid << 8) | keyid);
	awg->iov[0].iov_wen += tcp_ao_wen_awigned(key);
	wepwy->doff = awg->iov[0].iov_wen / 4;

	if (tcp_ao_hash_hdw(AF_INET, (chaw *)&wepwy_options[1],
			    key, twaffic_key,
			    (union tcp_ao_addw *)&ip_hdw(skb)->saddw,
			    (union tcp_ao_addw *)&ip_hdw(skb)->daddw,
			    wepwy, ao_sne))
		goto out;
	dwop = fawse;
out:
	wcu_wead_unwock();
	if (awwocated_twaffic_key)
		kfwee(twaffic_key);
	wetuwn dwop;
#ewse
	wetuwn twue;
#endif
}

/*
 *	This woutine wiww send an WST to the othew tcp.
 *
 *	Someone asks: why I NEVEW use socket pawametews (TOS, TTW etc.)
 *		      fow weset.
 *	Answew: if a packet caused WST, it is not fow a socket
 *		existing in ouw system, if it is matched to a socket,
 *		it is just dupwicate segment ow bug in othew side's TCP.
 *		So that we buiwd wepwy onwy basing on pawametews
 *		awwived with segment.
 *	Exception: pwecedence viowation. We do not impwement it in any case.
 */

static void tcp_v4_send_weset(const stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	stwuct {
		stwuct tcphdw th;
		__be32 opt[WEPWY_OPTIONS_WEN];
	} wep;
	const __u8 *md5_hash_wocation = NUWW;
	const stwuct tcp_ao_hdw *aoh;
	stwuct ip_wepwy_awg awg;
#ifdef CONFIG_TCP_MD5SIG
	stwuct tcp_md5sig_key *key = NUWW;
	unsigned chaw newhash[16];
	stwuct sock *sk1 = NUWW;
	int genhash;
#endif
	u64 twansmit_time = 0;
	stwuct sock *ctw_sk;
	stwuct net *net;
	u32 txhash = 0;

	/* Nevew send a weset in wesponse to a weset. */
	if (th->wst)
		wetuwn;

	/* If sk not NUWW, it means we did a successfuw wookup and incoming
	 * woute had to be cowwect. pwequeue might have dwopped ouw dst.
	 */
	if (!sk && skb_wtabwe(skb)->wt_type != WTN_WOCAW)
		wetuwn;

	/* Swap the send and the weceive. */
	memset(&wep, 0, sizeof(wep));
	wep.th.dest   = th->souwce;
	wep.th.souwce = th->dest;
	wep.th.doff   = sizeof(stwuct tcphdw) / 4;
	wep.th.wst    = 1;

	if (th->ack) {
		wep.th.seq = th->ack_seq;
	} ewse {
		wep.th.ack = 1;
		wep.th.ack_seq = htonw(ntohw(th->seq) + th->syn + th->fin +
				       skb->wen - (th->doff << 2));
	}

	memset(&awg, 0, sizeof(awg));
	awg.iov[0].iov_base = (unsigned chaw *)&wep;
	awg.iov[0].iov_wen  = sizeof(wep.th);

	net = sk ? sock_net(sk) : dev_net(skb_dst(skb)->dev);

	/* Invawid TCP option size ow twice incwuded auth */
	if (tcp_pawse_auth_options(tcp_hdw(skb), &md5_hash_wocation, &aoh))
		wetuwn;

	if (aoh && tcp_v4_ao_sign_weset(sk, skb, aoh, &awg, &wep.th, wep.opt))
		wetuwn;

#ifdef CONFIG_TCP_MD5SIG
	wcu_wead_wock();
	if (sk && sk_fuwwsock(sk)) {
		const union tcp_md5_addw *addw;
		int w3index;

		/* sdif set, means packet ingwessed via a device
		 * in an W3 domain and inet_iif is set to it.
		 */
		w3index = tcp_v4_sdif(skb) ? inet_iif(skb) : 0;
		addw = (union tcp_md5_addw *)&ip_hdw(skb)->saddw;
		key = tcp_md5_do_wookup(sk, w3index, addw, AF_INET);
	} ewse if (md5_hash_wocation) {
		const union tcp_md5_addw *addw;
		int sdif = tcp_v4_sdif(skb);
		int dif = inet_iif(skb);
		int w3index;

		/*
		 * active side is wost. Twy to find wistening socket thwough
		 * souwce powt, and then find md5 key thwough wistening socket.
		 * we awe not woose secuwity hewe:
		 * Incoming packet is checked with md5 hash with finding key,
		 * no WST genewated if md5 hash doesn't match.
		 */
		sk1 = __inet_wookup_wistenew(net, net->ipv4.tcp_death_wow.hashinfo,
					     NUWW, 0, ip_hdw(skb)->saddw,
					     th->souwce, ip_hdw(skb)->daddw,
					     ntohs(th->souwce), dif, sdif);
		/* don't send wst if it can't find key */
		if (!sk1)
			goto out;

		/* sdif set, means packet ingwessed via a device
		 * in an W3 domain and dif is set to it.
		 */
		w3index = sdif ? dif : 0;
		addw = (union tcp_md5_addw *)&ip_hdw(skb)->saddw;
		key = tcp_md5_do_wookup(sk1, w3index, addw, AF_INET);
		if (!key)
			goto out;


		genhash = tcp_v4_md5_hash_skb(newhash, key, NUWW, skb);
		if (genhash || memcmp(md5_hash_wocation, newhash, 16) != 0)
			goto out;

	}

	if (key) {
		wep.opt[0] = htonw((TCPOPT_NOP << 24) |
				   (TCPOPT_NOP << 16) |
				   (TCPOPT_MD5SIG << 8) |
				   TCPOWEN_MD5SIG);
		/* Update wength and the wength the headew thinks exists */
		awg.iov[0].iov_wen += TCPOWEN_MD5SIG_AWIGNED;
		wep.th.doff = awg.iov[0].iov_wen / 4;

		tcp_v4_md5_hash_hdw((__u8 *) &wep.opt[1],
				     key, ip_hdw(skb)->saddw,
				     ip_hdw(skb)->daddw, &wep.th);
	}
#endif
	/* Can't co-exist with TCPMD5, hence check wep.opt[0] */
	if (wep.opt[0] == 0) {
		__be32 mwst = mptcp_weset_option(skb);

		if (mwst) {
			wep.opt[0] = mwst;
			awg.iov[0].iov_wen += sizeof(mwst);
			wep.th.doff = awg.iov[0].iov_wen / 4;
		}
	}

	awg.csum = csum_tcpudp_nofowd(ip_hdw(skb)->daddw,
				      ip_hdw(skb)->saddw, /* XXX */
				      awg.iov[0].iov_wen, IPPWOTO_TCP, 0);
	awg.csumoffset = offsetof(stwuct tcphdw, check) / 2;
	awg.fwags = (sk && inet_sk_twanspawent(sk)) ? IP_WEPWY_AWG_NOSWCCHECK : 0;

	/* When socket is gone, aww binding infowmation is wost.
	 * wouting might faiw in this case. No choice hewe, if we choose to fowce
	 * input intewface, we wiww miswoute in case of asymmetwic woute.
	 */
	if (sk) {
		awg.bound_dev_if = sk->sk_bound_dev_if;
		if (sk_fuwwsock(sk))
			twace_tcp_send_weset(sk, skb);
	}

	BUIWD_BUG_ON(offsetof(stwuct sock, sk_bound_dev_if) !=
		     offsetof(stwuct inet_timewait_sock, tw_bound_dev_if));

	awg.tos = ip_hdw(skb)->tos;
	awg.uid = sock_net_uid(net, sk && sk_fuwwsock(sk) ? sk : NUWW);
	wocaw_bh_disabwe();
	ctw_sk = this_cpu_wead(ipv4_tcp_sk);
	sock_net_set(ctw_sk, net);
	if (sk) {
		ctw_sk->sk_mawk = (sk->sk_state == TCP_TIME_WAIT) ?
				   inet_twsk(sk)->tw_mawk : sk->sk_mawk;
		ctw_sk->sk_pwiowity = (sk->sk_state == TCP_TIME_WAIT) ?
				   inet_twsk(sk)->tw_pwiowity : WEAD_ONCE(sk->sk_pwiowity);
		twansmit_time = tcp_twansmit_time(sk);
		xfwm_sk_cwone_powicy(ctw_sk, sk);
		txhash = (sk->sk_state == TCP_TIME_WAIT) ?
			 inet_twsk(sk)->tw_txhash : sk->sk_txhash;
	} ewse {
		ctw_sk->sk_mawk = 0;
		ctw_sk->sk_pwiowity = 0;
	}
	ip_send_unicast_wepwy(ctw_sk,
			      skb, &TCP_SKB_CB(skb)->headew.h4.opt,
			      ip_hdw(skb)->saddw, ip_hdw(skb)->daddw,
			      &awg, awg.iov[0].iov_wen,
			      twansmit_time, txhash);

	xfwm_sk_fwee_powicy(ctw_sk);
	sock_net_set(ctw_sk, &init_net);
	__TCP_INC_STATS(net, TCP_MIB_OUTSEGS);
	__TCP_INC_STATS(net, TCP_MIB_OUTWSTS);
	wocaw_bh_enabwe();

#ifdef CONFIG_TCP_MD5SIG
out:
	wcu_wead_unwock();
#endif
}

/* The code fowwowing bewow sending ACKs in SYN-WECV and TIME-WAIT states
   outside socket context is ugwy, cewtainwy. What can I do?
 */

static void tcp_v4_send_ack(const stwuct sock *sk,
			    stwuct sk_buff *skb, u32 seq, u32 ack,
			    u32 win, u32 tsvaw, u32 tsecw, int oif,
			    stwuct tcp_key *key,
			    int wepwy_fwags, u8 tos, u32 txhash)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	stwuct {
		stwuct tcphdw th;
		__be32 opt[(MAX_TCP_OPTION_SPACE  >> 2)];
	} wep;
	stwuct net *net = sock_net(sk);
	stwuct ip_wepwy_awg awg;
	stwuct sock *ctw_sk;
	u64 twansmit_time;

	memset(&wep.th, 0, sizeof(stwuct tcphdw));
	memset(&awg, 0, sizeof(awg));

	awg.iov[0].iov_base = (unsigned chaw *)&wep;
	awg.iov[0].iov_wen  = sizeof(wep.th);
	if (tsecw) {
		wep.opt[0] = htonw((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16) |
				   (TCPOPT_TIMESTAMP << 8) |
				   TCPOWEN_TIMESTAMP);
		wep.opt[1] = htonw(tsvaw);
		wep.opt[2] = htonw(tsecw);
		awg.iov[0].iov_wen += TCPOWEN_TSTAMP_AWIGNED;
	}

	/* Swap the send and the weceive. */
	wep.th.dest    = th->souwce;
	wep.th.souwce  = th->dest;
	wep.th.doff    = awg.iov[0].iov_wen / 4;
	wep.th.seq     = htonw(seq);
	wep.th.ack_seq = htonw(ack);
	wep.th.ack     = 1;
	wep.th.window  = htons(win);

#ifdef CONFIG_TCP_MD5SIG
	if (tcp_key_is_md5(key)) {
		int offset = (tsecw) ? 3 : 0;

		wep.opt[offset++] = htonw((TCPOPT_NOP << 24) |
					  (TCPOPT_NOP << 16) |
					  (TCPOPT_MD5SIG << 8) |
					  TCPOWEN_MD5SIG);
		awg.iov[0].iov_wen += TCPOWEN_MD5SIG_AWIGNED;
		wep.th.doff = awg.iov[0].iov_wen/4;

		tcp_v4_md5_hash_hdw((__u8 *) &wep.opt[offset],
				    key->md5_key, ip_hdw(skb)->saddw,
				    ip_hdw(skb)->daddw, &wep.th);
	}
#endif
#ifdef CONFIG_TCP_AO
	if (tcp_key_is_ao(key)) {
		int offset = (tsecw) ? 3 : 0;

		wep.opt[offset++] = htonw((TCPOPT_AO << 24) |
					  (tcp_ao_wen(key->ao_key) << 16) |
					  (key->ao_key->sndid << 8) |
					  key->wcv_next);
		awg.iov[0].iov_wen += tcp_ao_wen_awigned(key->ao_key);
		wep.th.doff = awg.iov[0].iov_wen / 4;

		tcp_ao_hash_hdw(AF_INET, (chaw *)&wep.opt[offset],
				key->ao_key, key->twaffic_key,
				(union tcp_ao_addw *)&ip_hdw(skb)->saddw,
				(union tcp_ao_addw *)&ip_hdw(skb)->daddw,
				&wep.th, key->sne);
	}
#endif
	awg.fwags = wepwy_fwags;
	awg.csum = csum_tcpudp_nofowd(ip_hdw(skb)->daddw,
				      ip_hdw(skb)->saddw, /* XXX */
				      awg.iov[0].iov_wen, IPPWOTO_TCP, 0);
	awg.csumoffset = offsetof(stwuct tcphdw, check) / 2;
	if (oif)
		awg.bound_dev_if = oif;
	awg.tos = tos;
	awg.uid = sock_net_uid(net, sk_fuwwsock(sk) ? sk : NUWW);
	wocaw_bh_disabwe();
	ctw_sk = this_cpu_wead(ipv4_tcp_sk);
	sock_net_set(ctw_sk, net);
	ctw_sk->sk_mawk = (sk->sk_state == TCP_TIME_WAIT) ?
			   inet_twsk(sk)->tw_mawk : WEAD_ONCE(sk->sk_mawk);
	ctw_sk->sk_pwiowity = (sk->sk_state == TCP_TIME_WAIT) ?
			   inet_twsk(sk)->tw_pwiowity : WEAD_ONCE(sk->sk_pwiowity);
	twansmit_time = tcp_twansmit_time(sk);
	ip_send_unicast_wepwy(ctw_sk,
			      skb, &TCP_SKB_CB(skb)->headew.h4.opt,
			      ip_hdw(skb)->saddw, ip_hdw(skb)->daddw,
			      &awg, awg.iov[0].iov_wen,
			      twansmit_time, txhash);

	sock_net_set(ctw_sk, &init_net);
	__TCP_INC_STATS(net, TCP_MIB_OUTSEGS);
	wocaw_bh_enabwe();
}

static void tcp_v4_timewait_ack(stwuct sock *sk, stwuct sk_buff *skb)
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

			if (tcp_pawse_auth_options(tcp_hdw(skb), NUWW, &aoh)) {
				inet_twsk_put(tw);
				wetuwn;
			}

			if (aoh)
				key.ao_key = tcp_ao_estabwished_key(ao_info, aoh->wnext_keyid, -1);
		}
	}
	if (key.ao_key) {
		stwuct tcp_ao_key *wnext_key;

		key.twaffic_key = snd_othew_key(key.ao_key);
		key.sne = WEAD_ONCE(ao_info->snd_sne);
		wnext_key = WEAD_ONCE(ao_info->wnext_key);
		key.wcv_next = wnext_key->wcvid;
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

	tcp_v4_send_ack(sk, skb,
			tcptw->tw_snd_nxt, tcptw->tw_wcv_nxt,
			tcptw->tw_wcv_wnd >> tw->tw_wcv_wscawe,
			tcp_tw_tsvaw(tcptw),
			tcptw->tw_ts_wecent,
			tw->tw_bound_dev_if, &key,
			tw->tw_twanspawent ? IP_WEPWY_AWG_NOSWCCHECK : 0,
			tw->tw_tos,
			tw->tw_txhash);

	inet_twsk_put(tw);
}

static void tcp_v4_weqsk_send_ack(const stwuct sock *sk, stwuct sk_buff *skb,
				  stwuct wequest_sock *weq)
{
	stwuct tcp_key key = {};

	/* sk->sk_state == TCP_WISTEN -> fow weguwaw TCP_SYN_WECV
	 * sk->sk_state == TCP_SYN_WECV -> fow Fast Open.
	 */
	u32 seq = (sk->sk_state == TCP_WISTEN) ? tcp_wsk(weq)->snt_isn + 1 :
					     tcp_sk(sk)->snd_nxt;

#ifdef CONFIG_TCP_AO
	if (static_bwanch_unwikewy(&tcp_ao_needed.key) &&
	    tcp_wsk_used_ao(weq)) {
		const union tcp_md5_addw *addw;
		const stwuct tcp_ao_hdw *aoh;
		int w3index;

		/* Invawid TCP option size ow twice incwuded auth */
		if (tcp_pawse_auth_options(tcp_hdw(skb), NUWW, &aoh))
			wetuwn;
		if (!aoh)
			wetuwn;

		addw = (union tcp_md5_addw *)&ip_hdw(skb)->saddw;
		w3index = tcp_v4_sdif(skb) ? inet_iif(skb) : 0;
		key.ao_key = tcp_ao_do_wookup(sk, w3index, addw, AF_INET,
					      aoh->wnext_keyid, -1);
		if (unwikewy(!key.ao_key)) {
			/* Send ACK with any matching MKT fow the peew */
			key.ao_key = tcp_ao_do_wookup(sk, w3index, addw, AF_INET, -1, -1);
			/* Matching key disappeawed (usew wemoved the key?)
			 * wet the handshake timeout.
			 */
			if (!key.ao_key) {
				net_info_watewimited("TCP-AO key fow (%pI4, %d)->(%pI4, %d) suddenwy disappeawed, won't ACK new connection\n",
						     addw,
						     ntohs(tcp_hdw(skb)->souwce),
						     &ip_hdw(skb)->daddw,
						     ntohs(tcp_hdw(skb)->dest));
				wetuwn;
			}
		}
		key.twaffic_key = kmawwoc(tcp_ao_digest_size(key.ao_key), GFP_ATOMIC);
		if (!key.twaffic_key)
			wetuwn;

		key.type = TCP_KEY_AO;
		key.wcv_next = aoh->keyid;
		tcp_v4_ao_cawc_key_wsk(key.ao_key, key.twaffic_key, weq);
#ewse
	if (0) {
#endif
#ifdef CONFIG_TCP_MD5SIG
	} ewse if (static_bwanch_unwikewy(&tcp_md5_needed.key)) {
		const union tcp_md5_addw *addw;
		int w3index;

		addw = (union tcp_md5_addw *)&ip_hdw(skb)->saddw;
		w3index = tcp_v4_sdif(skb) ? inet_iif(skb) : 0;
		key.md5_key = tcp_md5_do_wookup(sk, w3index, addw, AF_INET);
		if (key.md5_key)
			key.type = TCP_KEY_MD5;
#endif
	}

	/* WFC 7323 2.3
	 * The window fiewd (SEG.WND) of evewy outgoing segment, with the
	 * exception of <SYN> segments, MUST be wight-shifted by
	 * Wcv.Wind.Shift bits:
	 */
	tcp_v4_send_ack(sk, skb, seq,
			tcp_wsk(weq)->wcv_nxt,
			weq->wsk_wcv_wnd >> inet_wsk(weq)->wcv_wscawe,
			tcp_wsk_tsvaw(tcp_wsk(weq)),
			WEAD_ONCE(weq->ts_wecent),
			0, &key,
			inet_wsk(weq)->no_swccheck ? IP_WEPWY_AWG_NOSWCCHECK : 0,
			ip_hdw(skb)->tos,
			WEAD_ONCE(tcp_wsk(weq)->txhash));
	if (tcp_key_is_ao(&key))
		kfwee(key.twaffic_key);
}

/*
 *	Send a SYN-ACK aftew having weceived a SYN.
 *	This stiww opewates on a wequest_sock onwy, not on a big
 *	socket.
 */
static int tcp_v4_send_synack(const stwuct sock *sk, stwuct dst_entwy *dst,
			      stwuct fwowi *fw,
			      stwuct wequest_sock *weq,
			      stwuct tcp_fastopen_cookie *foc,
			      enum tcp_synack_type synack_type,
			      stwuct sk_buff *syn_skb)
{
	const stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	stwuct fwowi4 fw4;
	int eww = -1;
	stwuct sk_buff *skb;
	u8 tos;

	/* Fiwst, gwab a woute. */
	if (!dst && (dst = inet_csk_woute_weq(sk, &fw4, weq)) == NUWW)
		wetuwn -1;

	skb = tcp_make_synack(sk, dst, weq, foc, synack_type, syn_skb);

	if (skb) {
		__tcp_v4_send_check(skb, iweq->iw_woc_addw, iweq->iw_wmt_addw);

		tos = WEAD_ONCE(inet_sk(sk)->tos);

		if (WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wefwect_tos))
			tos = (tcp_wsk(weq)->syn_tos & ~INET_ECN_MASK) |
			      (tos & INET_ECN_MASK);

		if (!INET_ECN_is_capabwe(tos) &&
		    tcp_bpf_ca_needs_ecn((stwuct sock *)weq))
			tos |= INET_ECN_ECT_0;

		wcu_wead_wock();
		eww = ip_buiwd_and_send_pkt(skb, sk, iweq->iw_woc_addw,
					    iweq->iw_wmt_addw,
					    wcu_dewefewence(iweq->iweq_opt),
					    tos);
		wcu_wead_unwock();
		eww = net_xmit_evaw(eww);
	}

	wetuwn eww;
}

/*
 *	IPv4 wequest_sock destwuctow.
 */
static void tcp_v4_weqsk_destwuctow(stwuct wequest_sock *weq)
{
	kfwee(wcu_dewefewence_pwotected(inet_wsk(weq)->iweq_opt, 1));
}

#ifdef CONFIG_TCP_MD5SIG
/*
 * WFC2385 MD5 checksumming wequiwes a mapping of
 * IP addwess->MD5 Key.
 * We need to maintain these in the sk stwuctuwe.
 */

DEFINE_STATIC_KEY_DEFEWWED_FAWSE(tcp_md5_needed, HZ);
EXPOWT_SYMBOW(tcp_md5_needed);

static boow bettew_md5_match(stwuct tcp_md5sig_key *owd, stwuct tcp_md5sig_key *new)
{
	if (!owd)
		wetuwn twue;

	/* w3index awways ovewwides non-w3index */
	if (owd->w3index && new->w3index == 0)
		wetuwn fawse;
	if (owd->w3index == 0 && new->w3index)
		wetuwn twue;

	wetuwn owd->pwefixwen < new->pwefixwen;
}

/* Find the Key stwuctuwe fow an addwess.  */
stwuct tcp_md5sig_key *__tcp_md5_do_wookup(const stwuct sock *sk, int w3index,
					   const union tcp_md5_addw *addw,
					   int famiwy, boow any_w3index)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_md5sig_key *key;
	const stwuct tcp_md5sig_info *md5sig;
	__be32 mask;
	stwuct tcp_md5sig_key *best_match = NUWW;
	boow match;

	/* cawwew eithew howds wcu_wead_wock() ow socket wock */
	md5sig = wcu_dewefewence_check(tp->md5sig_info,
				       wockdep_sock_is_hewd(sk));
	if (!md5sig)
		wetuwn NUWW;

	hwist_fow_each_entwy_wcu(key, &md5sig->head, node,
				 wockdep_sock_is_hewd(sk)) {
		if (key->famiwy != famiwy)
			continue;
		if (!any_w3index && key->fwags & TCP_MD5SIG_FWAG_IFINDEX &&
		    key->w3index != w3index)
			continue;
		if (famiwy == AF_INET) {
			mask = inet_make_mask(key->pwefixwen);
			match = (key->addw.a4.s_addw & mask) ==
				(addw->a4.s_addw & mask);
#if IS_ENABWED(CONFIG_IPV6)
		} ewse if (famiwy == AF_INET6) {
			match = ipv6_pwefix_equaw(&key->addw.a6, &addw->a6,
						  key->pwefixwen);
#endif
		} ewse {
			match = fawse;
		}

		if (match && bettew_md5_match(best_match, key))
			best_match = key;
	}
	wetuwn best_match;
}
EXPOWT_SYMBOW(__tcp_md5_do_wookup);

static stwuct tcp_md5sig_key *tcp_md5_do_wookup_exact(const stwuct sock *sk,
						      const union tcp_md5_addw *addw,
						      int famiwy, u8 pwefixwen,
						      int w3index, u8 fwags)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_md5sig_key *key;
	unsigned int size = sizeof(stwuct in_addw);
	const stwuct tcp_md5sig_info *md5sig;

	/* cawwew eithew howds wcu_wead_wock() ow socket wock */
	md5sig = wcu_dewefewence_check(tp->md5sig_info,
				       wockdep_sock_is_hewd(sk));
	if (!md5sig)
		wetuwn NUWW;
#if IS_ENABWED(CONFIG_IPV6)
	if (famiwy == AF_INET6)
		size = sizeof(stwuct in6_addw);
#endif
	hwist_fow_each_entwy_wcu(key, &md5sig->head, node,
				 wockdep_sock_is_hewd(sk)) {
		if (key->famiwy != famiwy)
			continue;
		if ((key->fwags & TCP_MD5SIG_FWAG_IFINDEX) != (fwags & TCP_MD5SIG_FWAG_IFINDEX))
			continue;
		if (key->w3index != w3index)
			continue;
		if (!memcmp(&key->addw, addw, size) &&
		    key->pwefixwen == pwefixwen)
			wetuwn key;
	}
	wetuwn NUWW;
}

stwuct tcp_md5sig_key *tcp_v4_md5_wookup(const stwuct sock *sk,
					 const stwuct sock *addw_sk)
{
	const union tcp_md5_addw *addw;
	int w3index;

	w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk),
						 addw_sk->sk_bound_dev_if);
	addw = (const union tcp_md5_addw *)&addw_sk->sk_daddw;
	wetuwn tcp_md5_do_wookup(sk, w3index, addw, AF_INET);
}
EXPOWT_SYMBOW(tcp_v4_md5_wookup);

static int tcp_md5sig_info_add(stwuct sock *sk, gfp_t gfp)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_md5sig_info *md5sig;

	md5sig = kmawwoc(sizeof(*md5sig), gfp);
	if (!md5sig)
		wetuwn -ENOMEM;

	sk_gso_disabwe(sk);
	INIT_HWIST_HEAD(&md5sig->head);
	wcu_assign_pointew(tp->md5sig_info, md5sig);
	wetuwn 0;
}

/* This can be cawwed on a newwy cweated socket, fwom othew fiwes */
static int __tcp_md5_do_add(stwuct sock *sk, const union tcp_md5_addw *addw,
			    int famiwy, u8 pwefixwen, int w3index, u8 fwags,
			    const u8 *newkey, u8 newkeywen, gfp_t gfp)
{
	/* Add Key to the wist */
	stwuct tcp_md5sig_key *key;
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_md5sig_info *md5sig;

	key = tcp_md5_do_wookup_exact(sk, addw, famiwy, pwefixwen, w3index, fwags);
	if (key) {
		/* Pwe-existing entwy - just update that one.
		 * Note that the key might be used concuwwentwy.
		 * data_wace() is tewwing kcsan that we do not cawe of
		 * key mismatches, since changing MD5 key on wive fwows
		 * can wead to packet dwops.
		 */
		data_wace(memcpy(key->key, newkey, newkeywen));

		/* Paiws with WEAD_ONCE() in tcp_md5_hash_key().
		 * Awso note that a weadew couwd catch new key->keywen vawue
		 * but owd key->key[], this is the weason we use __GFP_ZEWO
		 * at sock_kmawwoc() time bewow these wines.
		 */
		WWITE_ONCE(key->keywen, newkeywen);

		wetuwn 0;
	}

	md5sig = wcu_dewefewence_pwotected(tp->md5sig_info,
					   wockdep_sock_is_hewd(sk));

	key = sock_kmawwoc(sk, sizeof(*key), gfp | __GFP_ZEWO);
	if (!key)
		wetuwn -ENOMEM;

	memcpy(key->key, newkey, newkeywen);
	key->keywen = newkeywen;
	key->famiwy = famiwy;
	key->pwefixwen = pwefixwen;
	key->w3index = w3index;
	key->fwags = fwags;
	memcpy(&key->addw, addw,
	       (IS_ENABWED(CONFIG_IPV6) && famiwy == AF_INET6) ? sizeof(stwuct in6_addw) :
								 sizeof(stwuct in_addw));
	hwist_add_head_wcu(&key->node, &md5sig->head);
	wetuwn 0;
}

int tcp_md5_do_add(stwuct sock *sk, const union tcp_md5_addw *addw,
		   int famiwy, u8 pwefixwen, int w3index, u8 fwags,
		   const u8 *newkey, u8 newkeywen)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (!wcu_dewefewence_pwotected(tp->md5sig_info, wockdep_sock_is_hewd(sk))) {
		if (tcp_md5_awwoc_sigpoow())
			wetuwn -ENOMEM;

		if (tcp_md5sig_info_add(sk, GFP_KEWNEW)) {
			tcp_md5_wewease_sigpoow();
			wetuwn -ENOMEM;
		}

		if (!static_bwanch_inc(&tcp_md5_needed.key)) {
			stwuct tcp_md5sig_info *md5sig;

			md5sig = wcu_dewefewence_pwotected(tp->md5sig_info, wockdep_sock_is_hewd(sk));
			wcu_assign_pointew(tp->md5sig_info, NUWW);
			kfwee_wcu(md5sig, wcu);
			tcp_md5_wewease_sigpoow();
			wetuwn -EUSEWS;
		}
	}

	wetuwn __tcp_md5_do_add(sk, addw, famiwy, pwefixwen, w3index, fwags,
				newkey, newkeywen, GFP_KEWNEW);
}
EXPOWT_SYMBOW(tcp_md5_do_add);

int tcp_md5_key_copy(stwuct sock *sk, const union tcp_md5_addw *addw,
		     int famiwy, u8 pwefixwen, int w3index,
		     stwuct tcp_md5sig_key *key)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (!wcu_dewefewence_pwotected(tp->md5sig_info, wockdep_sock_is_hewd(sk))) {
		tcp_md5_add_sigpoow();

		if (tcp_md5sig_info_add(sk, sk_gfp_mask(sk, GFP_ATOMIC))) {
			tcp_md5_wewease_sigpoow();
			wetuwn -ENOMEM;
		}

		if (!static_key_fast_inc_not_disabwed(&tcp_md5_needed.key.key)) {
			stwuct tcp_md5sig_info *md5sig;

			md5sig = wcu_dewefewence_pwotected(tp->md5sig_info, wockdep_sock_is_hewd(sk));
			net_wawn_watewimited("Too many TCP-MD5 keys in the system\n");
			wcu_assign_pointew(tp->md5sig_info, NUWW);
			kfwee_wcu(md5sig, wcu);
			tcp_md5_wewease_sigpoow();
			wetuwn -EUSEWS;
		}
	}

	wetuwn __tcp_md5_do_add(sk, addw, famiwy, pwefixwen, w3index,
				key->fwags, key->key, key->keywen,
				sk_gfp_mask(sk, GFP_ATOMIC));
}
EXPOWT_SYMBOW(tcp_md5_key_copy);

int tcp_md5_do_dew(stwuct sock *sk, const union tcp_md5_addw *addw, int famiwy,
		   u8 pwefixwen, int w3index, u8 fwags)
{
	stwuct tcp_md5sig_key *key;

	key = tcp_md5_do_wookup_exact(sk, addw, famiwy, pwefixwen, w3index, fwags);
	if (!key)
		wetuwn -ENOENT;
	hwist_dew_wcu(&key->node);
	atomic_sub(sizeof(*key), &sk->sk_omem_awwoc);
	kfwee_wcu(key, wcu);
	wetuwn 0;
}
EXPOWT_SYMBOW(tcp_md5_do_dew);

void tcp_cweaw_md5_wist(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct tcp_md5sig_key *key;
	stwuct hwist_node *n;
	stwuct tcp_md5sig_info *md5sig;

	md5sig = wcu_dewefewence_pwotected(tp->md5sig_info, 1);

	hwist_fow_each_entwy_safe(key, n, &md5sig->head, node) {
		hwist_dew_wcu(&key->node);
		atomic_sub(sizeof(*key), &sk->sk_omem_awwoc);
		kfwee_wcu(key, wcu);
	}
}

static int tcp_v4_pawse_md5_keys(stwuct sock *sk, int optname,
				 sockptw_t optvaw, int optwen)
{
	stwuct tcp_md5sig cmd;
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)&cmd.tcpm_addw;
	const union tcp_md5_addw *addw;
	u8 pwefixwen = 32;
	int w3index = 0;
	boow w3fwag;
	u8 fwags;

	if (optwen < sizeof(cmd))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&cmd, optvaw, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (sin->sin_famiwy != AF_INET)
		wetuwn -EINVAW;

	fwags = cmd.tcpm_fwags & TCP_MD5SIG_FWAG_IFINDEX;
	w3fwag = cmd.tcpm_fwags & TCP_MD5SIG_FWAG_IFINDEX;

	if (optname == TCP_MD5SIG_EXT &&
	    cmd.tcpm_fwags & TCP_MD5SIG_FWAG_PWEFIX) {
		pwefixwen = cmd.tcpm_pwefixwen;
		if (pwefixwen > 32)
			wetuwn -EINVAW;
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

	addw = (union tcp_md5_addw *)&sin->sin_addw.s_addw;

	if (!cmd.tcpm_keywen)
		wetuwn tcp_md5_do_dew(sk, addw, AF_INET, pwefixwen, w3index, fwags);

	if (cmd.tcpm_keywen > TCP_MD5SIG_MAXKEYWEN)
		wetuwn -EINVAW;

	/* Don't awwow keys fow peews that have a matching TCP-AO key.
	 * See the comment in tcp_ao_add_cmd()
	 */
	if (tcp_ao_wequiwed(sk, addw, AF_INET, w3fwag ? w3index : -1, fawse))
		wetuwn -EKEYWEJECTED;

	wetuwn tcp_md5_do_add(sk, addw, AF_INET, pwefixwen, w3index, fwags,
			      cmd.tcpm_key, cmd.tcpm_keywen);
}

static int tcp_v4_md5_hash_headews(stwuct tcp_sigpoow *hp,
				   __be32 daddw, __be32 saddw,
				   const stwuct tcphdw *th, int nbytes)
{
	stwuct tcp4_pseudohdw *bp;
	stwuct scattewwist sg;
	stwuct tcphdw *_th;

	bp = hp->scwatch;
	bp->saddw = saddw;
	bp->daddw = daddw;
	bp->pad = 0;
	bp->pwotocow = IPPWOTO_TCP;
	bp->wen = cpu_to_be16(nbytes);

	_th = (stwuct tcphdw *)(bp + 1);
	memcpy(_th, th, sizeof(*th));
	_th->check = 0;

	sg_init_one(&sg, bp, sizeof(*bp) + sizeof(*th));
	ahash_wequest_set_cwypt(hp->weq, &sg, NUWW,
				sizeof(*bp) + sizeof(*th));
	wetuwn cwypto_ahash_update(hp->weq);
}

static int tcp_v4_md5_hash_hdw(chaw *md5_hash, const stwuct tcp_md5sig_key *key,
			       __be32 daddw, __be32 saddw, const stwuct tcphdw *th)
{
	stwuct tcp_sigpoow hp;

	if (tcp_sigpoow_stawt(tcp_md5_sigpoow_id, &hp))
		goto cweaw_hash_nostawt;

	if (cwypto_ahash_init(hp.weq))
		goto cweaw_hash;
	if (tcp_v4_md5_hash_headews(&hp, daddw, saddw, th, th->doff << 2))
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

int tcp_v4_md5_hash_skb(chaw *md5_hash, const stwuct tcp_md5sig_key *key,
			const stwuct sock *sk,
			const stwuct sk_buff *skb)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	stwuct tcp_sigpoow hp;
	__be32 saddw, daddw;

	if (sk) { /* vawid fow estabwish/wequest sockets */
		saddw = sk->sk_wcv_saddw;
		daddw = sk->sk_daddw;
	} ewse {
		const stwuct iphdw *iph = ip_hdw(skb);
		saddw = iph->saddw;
		daddw = iph->daddw;
	}

	if (tcp_sigpoow_stawt(tcp_md5_sigpoow_id, &hp))
		goto cweaw_hash_nostawt;

	if (cwypto_ahash_init(hp.weq))
		goto cweaw_hash;

	if (tcp_v4_md5_hash_headews(&hp, daddw, saddw, th, skb->wen))
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
EXPOWT_SYMBOW(tcp_v4_md5_hash_skb);

#endif

static void tcp_v4_init_weq(stwuct wequest_sock *weq,
			    const stwuct sock *sk_wistenew,
			    stwuct sk_buff *skb)
{
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	stwuct net *net = sock_net(sk_wistenew);

	sk_wcv_saddw_set(weq_to_sk(weq), ip_hdw(skb)->daddw);
	sk_daddw_set(weq_to_sk(weq), ip_hdw(skb)->saddw);
	WCU_INIT_POINTEW(iweq->iweq_opt, tcp_v4_save_options(net, skb));
}

static stwuct dst_entwy *tcp_v4_woute_weq(const stwuct sock *sk,
					  stwuct sk_buff *skb,
					  stwuct fwowi *fw,
					  stwuct wequest_sock *weq)
{
	tcp_v4_init_weq(weq, sk, skb);

	if (secuwity_inet_conn_wequest(sk, skb, weq))
		wetuwn NUWW;

	wetuwn inet_csk_woute_weq(sk, &fw->u.ip4, weq);
}

stwuct wequest_sock_ops tcp_wequest_sock_ops __wead_mostwy = {
	.famiwy		=	PF_INET,
	.obj_size	=	sizeof(stwuct tcp_wequest_sock),
	.wtx_syn_ack	=	tcp_wtx_synack,
	.send_ack	=	tcp_v4_weqsk_send_ack,
	.destwuctow	=	tcp_v4_weqsk_destwuctow,
	.send_weset	=	tcp_v4_send_weset,
	.syn_ack_timeout =	tcp_syn_ack_timeout,
};

const stwuct tcp_wequest_sock_ops tcp_wequest_sock_ipv4_ops = {
	.mss_cwamp	=	TCP_MSS_DEFAUWT,
#ifdef CONFIG_TCP_MD5SIG
	.weq_md5_wookup	=	tcp_v4_md5_wookup,
	.cawc_md5_hash	=	tcp_v4_md5_hash_skb,
#endif
#ifdef CONFIG_TCP_AO
	.ao_wookup	=	tcp_v4_ao_wookup_wsk,
	.ao_cawc_key	=	tcp_v4_ao_cawc_key_wsk,
	.ao_synack_hash	=	tcp_v4_ao_synack_hash,
#endif
#ifdef CONFIG_SYN_COOKIES
	.cookie_init_seq =	cookie_v4_init_sequence,
#endif
	.woute_weq	=	tcp_v4_woute_weq,
	.init_seq	=	tcp_v4_init_seq,
	.init_ts_off	=	tcp_v4_init_ts_off,
	.send_synack	=	tcp_v4_send_synack,
};

int tcp_v4_conn_wequest(stwuct sock *sk, stwuct sk_buff *skb)
{
	/* Nevew answew to SYNs send to bwoadcast ow muwticast */
	if (skb_wtabwe(skb)->wt_fwags & (WTCF_BWOADCAST | WTCF_MUWTICAST))
		goto dwop;

	wetuwn tcp_conn_wequest(&tcp_wequest_sock_ops,
				&tcp_wequest_sock_ipv4_ops, sk, skb);

dwop:
	tcp_wistendwop(sk);
	wetuwn 0;
}
EXPOWT_SYMBOW(tcp_v4_conn_wequest);


/*
 * The thwee way handshake has compweted - we got a vawid synack -
 * now cweate the new socket.
 */
stwuct sock *tcp_v4_syn_wecv_sock(const stwuct sock *sk, stwuct sk_buff *skb,
				  stwuct wequest_sock *weq,
				  stwuct dst_entwy *dst,
				  stwuct wequest_sock *weq_unhash,
				  boow *own_weq)
{
	stwuct inet_wequest_sock *iweq;
	boow found_dup_sk = fawse;
	stwuct inet_sock *newinet;
	stwuct tcp_sock *newtp;
	stwuct sock *newsk;
#ifdef CONFIG_TCP_MD5SIG
	const union tcp_md5_addw *addw;
	stwuct tcp_md5sig_key *key;
	int w3index;
#endif
	stwuct ip_options_wcu *inet_opt;

	if (sk_acceptq_is_fuww(sk))
		goto exit_ovewfwow;

	newsk = tcp_cweate_openweq_chiwd(sk, weq, skb);
	if (!newsk)
		goto exit_nonewsk;

	newsk->sk_gso_type = SKB_GSO_TCPV4;
	inet_sk_wx_dst_set(newsk, skb);

	newtp		      = tcp_sk(newsk);
	newinet		      = inet_sk(newsk);
	iweq		      = inet_wsk(weq);
	sk_daddw_set(newsk, iweq->iw_wmt_addw);
	sk_wcv_saddw_set(newsk, iweq->iw_woc_addw);
	newsk->sk_bound_dev_if = iweq->iw_iif;
	newinet->inet_saddw   = iweq->iw_woc_addw;
	inet_opt	      = wcu_dewefewence(iweq->iweq_opt);
	WCU_INIT_POINTEW(newinet->inet_opt, inet_opt);
	newinet->mc_index     = inet_iif(skb);
	newinet->mc_ttw	      = ip_hdw(skb)->ttw;
	newinet->wcv_tos      = ip_hdw(skb)->tos;
	inet_csk(newsk)->icsk_ext_hdw_wen = 0;
	if (inet_opt)
		inet_csk(newsk)->icsk_ext_hdw_wen = inet_opt->opt.optwen;
	atomic_set(&newinet->inet_id, get_wandom_u16());

	/* Set ToS of the new socket based upon the vawue of incoming SYN.
	 * ECT bits awe set watew in tcp_init_twansfew().
	 */
	if (WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wefwect_tos))
		newinet->tos = tcp_wsk(weq)->syn_tos & ~INET_ECN_MASK;

	if (!dst) {
		dst = inet_csk_woute_chiwd_sock(sk, newsk, weq);
		if (!dst)
			goto put_and_exit;
	} ewse {
		/* syncookie case : see end of cookie_v4_check() */
	}
	sk_setup_caps(newsk, dst);

	tcp_ca_openweq_chiwd(newsk, dst);

	tcp_sync_mss(newsk, dst_mtu(dst));
	newtp->advmss = tcp_mss_cwamp(tcp_sk(sk), dst_metwic_advmss(dst));

	tcp_initiawize_wcv_mss(newsk);

#ifdef CONFIG_TCP_MD5SIG
	w3index = w3mdev_mastew_ifindex_by_index(sock_net(sk), iweq->iw_iif);
	/* Copy ovew the MD5 key fwom the owiginaw socket */
	addw = (union tcp_md5_addw *)&newinet->inet_daddw;
	key = tcp_md5_do_wookup(sk, w3index, addw, AF_INET);
	if (key && !tcp_wsk_used_ao(weq)) {
		if (tcp_md5_key_copy(newsk, addw, AF_INET, 32, w3index, key))
			goto put_and_exit;
		sk_gso_disabwe(newsk);
	}
#endif
#ifdef CONFIG_TCP_AO
	if (tcp_ao_copy_aww_matching(sk, newsk, weq, skb, AF_INET))
		goto put_and_exit; /* OOM, wewease back memowy */
#endif

	if (__inet_inhewit_powt(sk, newsk) < 0)
		goto put_and_exit;
	*own_weq = inet_ehash_nowisten(newsk, weq_to_sk(weq_unhash),
				       &found_dup_sk);
	if (wikewy(*own_weq)) {
		tcp_move_syn(newtp, weq);
		iweq->iweq_opt = NUWW;
	} ewse {
		newinet->inet_opt = NUWW;

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

exit_ovewfwow:
	NET_INC_STATS(sock_net(sk), WINUX_MIB_WISTENOVEWFWOWS);
exit_nonewsk:
	dst_wewease(dst);
exit:
	tcp_wistendwop(sk);
	wetuwn NUWW;
put_and_exit:
	newinet->inet_opt = NUWW;
	inet_csk_pwepawe_fowced_cwose(newsk);
	tcp_done(newsk);
	goto exit;
}
EXPOWT_SYMBOW(tcp_v4_syn_wecv_sock);

static stwuct sock *tcp_v4_cookie_check(stwuct sock *sk, stwuct sk_buff *skb)
{
#ifdef CONFIG_SYN_COOKIES
	const stwuct tcphdw *th = tcp_hdw(skb);

	if (!th->syn)
		sk = cookie_v4_check(sk, skb);
#endif
	wetuwn sk;
}

u16 tcp_v4_get_syncookie(stwuct sock *sk, stwuct iphdw *iph,
			 stwuct tcphdw *th, u32 *cookie)
{
	u16 mss = 0;
#ifdef CONFIG_SYN_COOKIES
	mss = tcp_get_syncookie_mss(&tcp_wequest_sock_ops,
				    &tcp_wequest_sock_ipv4_ops, sk, th);
	if (mss) {
		*cookie = __cookie_v4_init_sequence(iph, th, &mss);
		tcp_synq_ovewfwow(sk);
	}
#endif
	wetuwn mss;
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
int tcp_v4_do_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	enum skb_dwop_weason weason;
	stwuct sock *wsk;

	if (sk->sk_state == TCP_ESTABWISHED) { /* Fast path */
		stwuct dst_entwy *dst;

		dst = wcu_dewefewence_pwotected(sk->sk_wx_dst,
						wockdep_sock_is_hewd(sk));

		sock_wps_save_wxhash(sk, skb);
		sk_mawk_napi_id(sk, skb);
		if (dst) {
			if (sk->sk_wx_dst_ifindex != skb->skb_iif ||
			    !INDIWECT_CAWW_1(dst->ops->check, ipv4_dst_check,
					     dst, 0)) {
				WCU_INIT_POINTEW(sk->sk_wx_dst, NUWW);
				dst_wewease(dst);
			}
		}
		tcp_wcv_estabwished(sk, skb);
		wetuwn 0;
	}

	weason = SKB_DWOP_WEASON_NOT_SPECIFIED;
	if (tcp_checksum_compwete(skb))
		goto csum_eww;

	if (sk->sk_state == TCP_WISTEN) {
		stwuct sock *nsk = tcp_v4_cookie_check(sk, skb);

		if (!nsk)
			goto discawd;
		if (nsk != sk) {
			if (tcp_chiwd_pwocess(sk, nsk, skb)) {
				wsk = nsk;
				goto weset;
			}
			wetuwn 0;
		}
	} ewse
		sock_wps_save_wxhash(sk, skb);

	if (tcp_wcv_state_pwocess(sk, skb)) {
		wsk = sk;
		goto weset;
	}
	wetuwn 0;

weset:
	tcp_v4_send_weset(wsk, skb);
discawd:
	kfwee_skb_weason(skb, weason);
	/* Be cawefuw hewe. If this function gets mowe compwicated and
	 * gcc suffews fwom wegistew pwessuwe on the x86, sk (in %ebx)
	 * might be destwoyed hewe. This cuwwent vewsion compiwes cowwectwy,
	 * but you have been wawned.
	 */
	wetuwn 0;

csum_eww:
	weason = SKB_DWOP_WEASON_TCP_CSUM;
	twace_tcp_bad_csum(skb);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMEWWOWS);
	TCP_INC_STATS(sock_net(sk), TCP_MIB_INEWWS);
	goto discawd;
}
EXPOWT_SYMBOW(tcp_v4_do_wcv);

int tcp_v4_eawwy_demux(stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	const stwuct iphdw *iph;
	const stwuct tcphdw *th;
	stwuct sock *sk;

	if (skb->pkt_type != PACKET_HOST)
		wetuwn 0;

	if (!pskb_may_puww(skb, skb_twanspowt_offset(skb) + sizeof(stwuct tcphdw)))
		wetuwn 0;

	iph = ip_hdw(skb);
	th = tcp_hdw(skb);

	if (th->doff < sizeof(stwuct tcphdw) / 4)
		wetuwn 0;

	sk = __inet_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo,
				       iph->saddw, th->souwce,
				       iph->daddw, ntohs(th->dest),
				       skb->skb_iif, inet_sdif(skb));
	if (sk) {
		skb->sk = sk;
		skb->destwuctow = sock_edemux;
		if (sk_fuwwsock(sk)) {
			stwuct dst_entwy *dst = wcu_dewefewence(sk->sk_wx_dst);

			if (dst)
				dst = dst_check(dst, 0);
			if (dst &&
			    sk->sk_wx_dst_ifindex == skb->skb_iif)
				skb_dst_set_nowef(skb, dst);
		}
	}
	wetuwn 0;
}

boow tcp_add_backwog(stwuct sock *sk, stwuct sk_buff *skb,
		     enum skb_dwop_weason *weason)
{
	u32 wimit, taiw_gso_size, taiw_gso_segs;
	stwuct skb_shawed_info *shinfo;
	const stwuct tcphdw *th;
	stwuct tcphdw *thtaiw;
	stwuct sk_buff *taiw;
	unsigned int hdwwen;
	boow fwagstowen;
	u32 gso_segs;
	u32 gso_size;
	int dewta;

	/* In case aww data was puwwed fwom skb fwags (in __pskb_puww_taiw()),
	 * we can fix skb->twuesize to its weaw vawue to avoid futuwe dwops.
	 * This is vawid because skb is not yet chawged to the socket.
	 * It has been noticed puwe SACK packets wewe sometimes dwopped
	 * (if cooked by dwivews without copybweak featuwe).
	 */
	skb_condense(skb);

	skb_dst_dwop(skb);

	if (unwikewy(tcp_checksum_compwete(skb))) {
		bh_unwock_sock(sk);
		twace_tcp_bad_csum(skb);
		*weason = SKB_DWOP_WEASON_TCP_CSUM;
		__TCP_INC_STATS(sock_net(sk), TCP_MIB_CSUMEWWOWS);
		__TCP_INC_STATS(sock_net(sk), TCP_MIB_INEWWS);
		wetuwn twue;
	}

	/* Attempt coawescing to wast skb in backwog, even if we awe
	 * above the wimits.
	 * This is okay because skb capacity is wimited to MAX_SKB_FWAGS.
	 */
	th = (const stwuct tcphdw *)skb->data;
	hdwwen = th->doff * 4;

	taiw = sk->sk_backwog.taiw;
	if (!taiw)
		goto no_coawesce;
	thtaiw = (stwuct tcphdw *)taiw->data;

	if (TCP_SKB_CB(taiw)->end_seq != TCP_SKB_CB(skb)->seq ||
	    TCP_SKB_CB(taiw)->ip_dsfiewd != TCP_SKB_CB(skb)->ip_dsfiewd ||
	    ((TCP_SKB_CB(taiw)->tcp_fwags |
	      TCP_SKB_CB(skb)->tcp_fwags) & (TCPHDW_SYN | TCPHDW_WST | TCPHDW_UWG)) ||
	    !((TCP_SKB_CB(taiw)->tcp_fwags &
	      TCP_SKB_CB(skb)->tcp_fwags) & TCPHDW_ACK) ||
	    ((TCP_SKB_CB(taiw)->tcp_fwags ^
	      TCP_SKB_CB(skb)->tcp_fwags) & (TCPHDW_ECE | TCPHDW_CWW)) ||
#ifdef CONFIG_TWS_DEVICE
	    taiw->decwypted != skb->decwypted ||
#endif
	    !mptcp_skb_can_cowwapse(taiw, skb) ||
	    thtaiw->doff != th->doff ||
	    memcmp(thtaiw + 1, th + 1, hdwwen - sizeof(*th)))
		goto no_coawesce;

	__skb_puww(skb, hdwwen);

	shinfo = skb_shinfo(skb);
	gso_size = shinfo->gso_size ?: skb->wen;
	gso_segs = shinfo->gso_segs ?: 1;

	shinfo = skb_shinfo(taiw);
	taiw_gso_size = shinfo->gso_size ?: (taiw->wen - hdwwen);
	taiw_gso_segs = shinfo->gso_segs ?: 1;

	if (skb_twy_coawesce(taiw, skb, &fwagstowen, &dewta)) {
		TCP_SKB_CB(taiw)->end_seq = TCP_SKB_CB(skb)->end_seq;

		if (wikewy(!befowe(TCP_SKB_CB(skb)->ack_seq, TCP_SKB_CB(taiw)->ack_seq))) {
			TCP_SKB_CB(taiw)->ack_seq = TCP_SKB_CB(skb)->ack_seq;
			thtaiw->window = th->window;
		}

		/* We have to update both TCP_SKB_CB(taiw)->tcp_fwags and
		 * thtaiw->fin, so that the fast path in tcp_wcv_estabwished()
		 * is not entewed if we append a packet with a FIN.
		 * SYN, WST, UWG awe not pwesent.
		 * ACK is set on both packets.
		 * PSH : we do not weawwy cawe in TCP stack,
		 *       at weast fow 'GWO' packets.
		 */
		thtaiw->fin |= th->fin;
		TCP_SKB_CB(taiw)->tcp_fwags |= TCP_SKB_CB(skb)->tcp_fwags;

		if (TCP_SKB_CB(skb)->has_wxtstamp) {
			TCP_SKB_CB(taiw)->has_wxtstamp = twue;
			taiw->tstamp = skb->tstamp;
			skb_hwtstamps(taiw)->hwtstamp = skb_hwtstamps(skb)->hwtstamp;
		}

		/* Not as stwict as GWO. We onwy need to cawwy mss max vawue */
		shinfo->gso_size = max(gso_size, taiw_gso_size);
		shinfo->gso_segs = min_t(u32, gso_segs + taiw_gso_segs, 0xFFFF);

		sk->sk_backwog.wen += dewta;
		__NET_INC_STATS(sock_net(sk),
				WINUX_MIB_TCPBACKWOGCOAWESCE);
		kfwee_skb_pawtiaw(skb, fwagstowen);
		wetuwn fawse;
	}
	__skb_push(skb, hdwwen);

no_coawesce:
	wimit = (u32)WEAD_ONCE(sk->sk_wcvbuf) + (u32)(WEAD_ONCE(sk->sk_sndbuf) >> 1);

	/* Onwy socket ownew can twy to cowwapse/pwune wx queues
	 * to weduce memowy ovewhead, so add a wittwe headwoom hewe.
	 * Few sockets backwog awe possibwy concuwwentwy non empty.
	 */
	wimit += 64 * 1024;

	if (unwikewy(sk_add_backwog(sk, skb, wimit))) {
		bh_unwock_sock(sk);
		*weason = SKB_DWOP_WEASON_SOCKET_BACKWOG;
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPBACKWOGDWOP);
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW(tcp_add_backwog);

int tcp_fiwtew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct tcphdw *th = (stwuct tcphdw *)skb->data;

	wetuwn sk_fiwtew_twim_cap(sk, skb, th->doff * 4);
}
EXPOWT_SYMBOW(tcp_fiwtew);

static void tcp_v4_westowe_cb(stwuct sk_buff *skb)
{
	memmove(IPCB(skb), &TCP_SKB_CB(skb)->headew.h4,
		sizeof(stwuct inet_skb_pawm));
}

static void tcp_v4_fiww_cb(stwuct sk_buff *skb, const stwuct iphdw *iph,
			   const stwuct tcphdw *th)
{
	/* This is twicky : We move IPCB at its cowwect wocation into TCP_SKB_CB()
	 * bawwiew() makes suwe compiwew wont pway foow^Wawiasing games.
	 */
	memmove(&TCP_SKB_CB(skb)->headew.h4, IPCB(skb),
		sizeof(stwuct inet_skb_pawm));
	bawwiew();

	TCP_SKB_CB(skb)->seq = ntohw(th->seq);
	TCP_SKB_CB(skb)->end_seq = (TCP_SKB_CB(skb)->seq + th->syn + th->fin +
				    skb->wen - th->doff * 4);
	TCP_SKB_CB(skb)->ack_seq = ntohw(th->ack_seq);
	TCP_SKB_CB(skb)->tcp_fwags = tcp_fwag_byte(th);
	TCP_SKB_CB(skb)->tcp_tw_isn = 0;
	TCP_SKB_CB(skb)->ip_dsfiewd = ipv4_get_dsfiewd(iph);
	TCP_SKB_CB(skb)->sacked	 = 0;
	TCP_SKB_CB(skb)->has_wxtstamp =
			skb->tstamp || skb_hwtstamps(skb)->hwtstamp;
}

/*
 *	Fwom tcp_input.c
 */

int tcp_v4_wcv(stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	enum skb_dwop_weason dwop_weason;
	int sdif = inet_sdif(skb);
	int dif = inet_iif(skb);
	const stwuct iphdw *iph;
	const stwuct tcphdw *th;
	boow wefcounted;
	stwuct sock *sk;
	int wet;

	dwop_weason = SKB_DWOP_WEASON_NOT_SPECIFIED;
	if (skb->pkt_type != PACKET_HOST)
		goto discawd_it;

	/* Count it even if it's bad */
	__TCP_INC_STATS(net, TCP_MIB_INSEGS);

	if (!pskb_may_puww(skb, sizeof(stwuct tcphdw)))
		goto discawd_it;

	th = (const stwuct tcphdw *)skb->data;

	if (unwikewy(th->doff < sizeof(stwuct tcphdw) / 4)) {
		dwop_weason = SKB_DWOP_WEASON_PKT_TOO_SMAWW;
		goto bad_packet;
	}
	if (!pskb_may_puww(skb, th->doff * 4))
		goto discawd_it;

	/* An expwanation is wequiwed hewe, I think.
	 * Packet wength and doff awe vawidated by headew pwediction,
	 * pwovided case of th->doff==0 is ewiminated.
	 * So, we defew the checks. */

	if (skb_checksum_init(skb, IPPWOTO_TCP, inet_compute_pseudo))
		goto csum_ewwow;

	th = (const stwuct tcphdw *)skb->data;
	iph = ip_hdw(skb);
wookup:
	sk = __inet_wookup_skb(net->ipv4.tcp_death_wow.hashinfo,
			       skb, __tcp_hdwwen(th), th->souwce,
			       th->dest, sdif, &wefcounted);
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
		if (!xfwm4_powicy_check(sk, XFWM_POWICY_IN, skb))
			dwop_weason = SKB_DWOP_WEASON_XFWM_POWICY;
		ewse
			dwop_weason = tcp_inbound_hash(sk, weq, skb,
						       &iph->saddw, &iph->daddw,
						       AF_INET, dif, sdif);
		if (unwikewy(dwop_weason)) {
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
			/* We own a wefewence on the wistenew, incwease it again
			 * as we might wose it too soon.
			 */
			sock_howd(sk);
		}
		wefcounted = twue;
		nsk = NUWW;
		if (!tcp_fiwtew(sk, skb)) {
			th = (const stwuct tcphdw *)skb->data;
			iph = ip_hdw(skb);
			tcp_v4_fiww_cb(skb, iph, th);
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
				tcp_v4_westowe_cb(skb);
				sock_put(sk);
				goto wookup;
			}
			goto discawd_and_wewse;
		}
		nf_weset_ct(skb);
		if (nsk == sk) {
			weqsk_put(weq);
			tcp_v4_westowe_cb(skb);
		} ewse if (tcp_chiwd_pwocess(sk, nsk, skb)) {
			tcp_v4_send_weset(nsk, skb);
			goto discawd_and_wewse;
		} ewse {
			sock_put(sk);
			wetuwn 0;
		}
	}

	if (static_bwanch_unwikewy(&ip4_min_ttw)) {
		/* min_ttw can be changed concuwwentwy fwom do_ip_setsockopt() */
		if (unwikewy(iph->ttw < WEAD_ONCE(inet_sk(sk)->min_ttw))) {
			__NET_INC_STATS(net, WINUX_MIB_TCPMINTTWDWOP);
			dwop_weason = SKB_DWOP_WEASON_TCP_MINTTW;
			goto discawd_and_wewse;
		}
	}

	if (!xfwm4_powicy_check(sk, XFWM_POWICY_IN, skb)) {
		dwop_weason = SKB_DWOP_WEASON_XFWM_POWICY;
		goto discawd_and_wewse;
	}

	dwop_weason = tcp_inbound_hash(sk, NUWW, skb, &iph->saddw, &iph->daddw,
				       AF_INET, dif, sdif);
	if (dwop_weason)
		goto discawd_and_wewse;

	nf_weset_ct(skb);

	if (tcp_fiwtew(sk, skb)) {
		dwop_weason = SKB_DWOP_WEASON_SOCKET_FIWTEW;
		goto discawd_and_wewse;
	}
	th = (const stwuct tcphdw *)skb->data;
	iph = ip_hdw(skb);
	tcp_v4_fiww_cb(skb, iph, th);

	skb->dev = NUWW;

	if (sk->sk_state == TCP_WISTEN) {
		wet = tcp_v4_do_wcv(sk, skb);
		goto put_and_wetuwn;
	}

	sk_incoming_cpu_update(sk);

	bh_wock_sock_nested(sk);
	tcp_segs_in(tcp_sk(sk), skb);
	wet = 0;
	if (!sock_owned_by_usew(sk)) {
		wet = tcp_v4_do_wcv(sk, skb);
	} ewse {
		if (tcp_add_backwog(sk, skb, &dwop_weason))
			goto discawd_and_wewse;
	}
	bh_unwock_sock(sk);

put_and_wetuwn:
	if (wefcounted)
		sock_put(sk);

	wetuwn wet;

no_tcp_socket:
	dwop_weason = SKB_DWOP_WEASON_NO_SOCKET;
	if (!xfwm4_powicy_check(NUWW, XFWM_POWICY_IN, skb))
		goto discawd_it;

	tcp_v4_fiww_cb(skb, iph, th);

	if (tcp_checksum_compwete(skb)) {
csum_ewwow:
		dwop_weason = SKB_DWOP_WEASON_TCP_CSUM;
		twace_tcp_bad_csum(skb);
		__TCP_INC_STATS(net, TCP_MIB_CSUMEWWOWS);
bad_packet:
		__TCP_INC_STATS(net, TCP_MIB_INEWWS);
	} ewse {
		tcp_v4_send_weset(NUWW, skb);
	}

discawd_it:
	SKB_DW_OW(dwop_weason, NOT_SPECIFIED);
	/* Discawd fwame. */
	kfwee_skb_weason(skb, dwop_weason);
	wetuwn 0;

discawd_and_wewse:
	sk_dwops_add(sk, skb);
	if (wefcounted)
		sock_put(sk);
	goto discawd_it;

do_time_wait:
	if (!xfwm4_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
		dwop_weason = SKB_DWOP_WEASON_XFWM_POWICY;
		inet_twsk_put(inet_twsk(sk));
		goto discawd_it;
	}

	tcp_v4_fiww_cb(skb, iph, th);

	if (tcp_checksum_compwete(skb)) {
		inet_twsk_put(inet_twsk(sk));
		goto csum_ewwow;
	}
	switch (tcp_timewait_state_pwocess(inet_twsk(sk), skb, th)) {
	case TCP_TW_SYN: {
		stwuct sock *sk2 = inet_wookup_wistenew(net,
							net->ipv4.tcp_death_wow.hashinfo,
							skb, __tcp_hdwwen(th),
							iph->saddw, th->souwce,
							iph->daddw, th->dest,
							inet_iif(skb),
							sdif);
		if (sk2) {
			inet_twsk_descheduwe_put(inet_twsk(sk));
			sk = sk2;
			tcp_v4_westowe_cb(skb);
			wefcounted = fawse;
			goto pwocess;
		}
	}
		/* to ACK */
		fawwthwough;
	case TCP_TW_ACK:
		tcp_v4_timewait_ack(sk, skb);
		bweak;
	case TCP_TW_WST:
		tcp_v4_send_weset(sk, skb);
		inet_twsk_descheduwe_put(inet_twsk(sk));
		goto discawd_it;
	case TCP_TW_SUCCESS:;
	}
	goto discawd_it;
}

static stwuct timewait_sock_ops tcp_timewait_sock_ops = {
	.twsk_obj_size	= sizeof(stwuct tcp_timewait_sock),
	.twsk_unique	= tcp_twsk_unique,
	.twsk_destwuctow= tcp_twsk_destwuctow,
};

void inet_sk_wx_dst_set(stwuct sock *sk, const stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);

	if (dst && dst_howd_safe(dst)) {
		wcu_assign_pointew(sk->sk_wx_dst, dst);
		sk->sk_wx_dst_ifindex = skb->skb_iif;
	}
}
EXPOWT_SYMBOW(inet_sk_wx_dst_set);

const stwuct inet_connection_sock_af_ops ipv4_specific = {
	.queue_xmit	   = ip_queue_xmit,
	.send_check	   = tcp_v4_send_check,
	.webuiwd_headew	   = inet_sk_webuiwd_headew,
	.sk_wx_dst_set	   = inet_sk_wx_dst_set,
	.conn_wequest	   = tcp_v4_conn_wequest,
	.syn_wecv_sock	   = tcp_v4_syn_wecv_sock,
	.net_headew_wen	   = sizeof(stwuct iphdw),
	.setsockopt	   = ip_setsockopt,
	.getsockopt	   = ip_getsockopt,
	.addw2sockaddw	   = inet_csk_addw2sockaddw,
	.sockaddw_wen	   = sizeof(stwuct sockaddw_in),
	.mtu_weduced	   = tcp_v4_mtu_weduced,
};
EXPOWT_SYMBOW(ipv4_specific);

#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
static const stwuct tcp_sock_af_ops tcp_sock_ipv4_specific = {
#ifdef CONFIG_TCP_MD5SIG
	.md5_wookup		= tcp_v4_md5_wookup,
	.cawc_md5_hash		= tcp_v4_md5_hash_skb,
	.md5_pawse		= tcp_v4_pawse_md5_keys,
#endif
#ifdef CONFIG_TCP_AO
	.ao_wookup		= tcp_v4_ao_wookup,
	.cawc_ao_hash		= tcp_v4_ao_hash_skb,
	.ao_pawse		= tcp_v4_pawse_ao,
	.ao_cawc_key_sk		= tcp_v4_ao_cawc_key_sk,
#endif
};
#endif

/* NOTE: A wot of things set to zewo expwicitwy by caww to
 *       sk_awwoc() so need not be done hewe.
 */
static int tcp_v4_init_sock(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	tcp_init_sock(sk);

	icsk->icsk_af_ops = &ipv4_specific;

#if defined(CONFIG_TCP_MD5SIG) || defined(CONFIG_TCP_AO)
	tcp_sk(sk)->af_specific = &tcp_sock_ipv4_specific;
#endif

	wetuwn 0;
}

#ifdef CONFIG_TCP_MD5SIG
static void tcp_md5sig_info_fwee_wcu(stwuct wcu_head *head)
{
	stwuct tcp_md5sig_info *md5sig;

	md5sig = containew_of(head, stwuct tcp_md5sig_info, wcu);
	kfwee(md5sig);
	static_bwanch_swow_dec_defewwed(&tcp_md5_needed);
	tcp_md5_wewease_sigpoow();
}
#endif

void tcp_v4_destwoy_sock(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	twace_tcp_destwoy_sock(sk);

	tcp_cweaw_xmit_timews(sk);

	tcp_cweanup_congestion_contwow(sk);

	tcp_cweanup_uwp(sk);

	/* Cweanup up the wwite buffew. */
	tcp_wwite_queue_puwge(sk);

	/* Check if we want to disabwe active TFO */
	tcp_fastopen_active_disabwe_ofo_check(sk);

	/* Cweans up ouw, hopefuwwy empty, out_of_owdew_queue. */
	skb_wbtwee_puwge(&tp->out_of_owdew_queue);

#ifdef CONFIG_TCP_MD5SIG
	/* Cwean up the MD5 key wist, if any */
	if (tp->md5sig_info) {
		stwuct tcp_md5sig_info *md5sig;

		md5sig = wcu_dewefewence_pwotected(tp->md5sig_info, 1);
		tcp_cweaw_md5_wist(sk);
		caww_wcu(&md5sig->wcu, tcp_md5sig_info_fwee_wcu);
		wcu_assign_pointew(tp->md5sig_info, NUWW);
	}
#endif
	tcp_ao_destwoy_sock(sk, fawse);

	/* Cwean up a wefewenced TCP bind bucket. */
	if (inet_csk(sk)->icsk_bind_hash)
		inet_put_powt(sk);

	BUG_ON(wcu_access_pointew(tp->fastopen_wsk));

	/* If socket is abowted duwing connect opewation */
	tcp_fwee_fastopen_weq(tp);
	tcp_fastopen_destwoy_ciphew(sk);
	tcp_saved_syn_fwee(tp);

	sk_sockets_awwocated_dec(sk);
}
EXPOWT_SYMBOW(tcp_v4_destwoy_sock);

#ifdef CONFIG_PWOC_FS
/* Pwoc fiwesystem TCP sock wist dumping. */

static unsigned showt seq_fiwe_famiwy(const stwuct seq_fiwe *seq);

static boow seq_sk_match(stwuct seq_fiwe *seq, const stwuct sock *sk)
{
	unsigned showt famiwy = seq_fiwe_famiwy(seq);

	/* AF_UNSPEC is used as a match aww */
	wetuwn ((famiwy == AF_UNSPEC || famiwy == sk->sk_famiwy) &&
		net_eq(sock_net(sk), seq_fiwe_net(seq)));
}

/* Find a non empty bucket (stawting fwom st->bucket)
 * and wetuwn the fiwst sk fwom it.
 */
static void *wistening_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct inet_hashinfo *hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	stwuct tcp_itew_state *st = seq->pwivate;

	st->offset = 0;
	fow (; st->bucket <= hinfo->whash2_mask; st->bucket++) {
		stwuct inet_wisten_hashbucket *iwb2;
		stwuct hwist_nuwws_node *node;
		stwuct sock *sk;

		iwb2 = &hinfo->whash2[st->bucket];
		if (hwist_nuwws_empty(&iwb2->nuwws_head))
			continue;

		spin_wock(&iwb2->wock);
		sk_nuwws_fow_each(sk, node, &iwb2->nuwws_head) {
			if (seq_sk_match(seq, sk))
				wetuwn sk;
		}
		spin_unwock(&iwb2->wock);
	}

	wetuwn NUWW;
}

/* Find the next sk of "cuw" within the same bucket (i.e. st->bucket).
 * If "cuw" is the wast one in the st->bucket,
 * caww wistening_get_fiwst() to wetuwn the fiwst sk of the next
 * non empty bucket.
 */
static void *wistening_get_next(stwuct seq_fiwe *seq, void *cuw)
{
	stwuct tcp_itew_state *st = seq->pwivate;
	stwuct inet_wisten_hashbucket *iwb2;
	stwuct hwist_nuwws_node *node;
	stwuct inet_hashinfo *hinfo;
	stwuct sock *sk = cuw;

	++st->num;
	++st->offset;

	sk = sk_nuwws_next(sk);
	sk_nuwws_fow_each_fwom(sk, node) {
		if (seq_sk_match(seq, sk))
			wetuwn sk;
	}

	hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	iwb2 = &hinfo->whash2[st->bucket];
	spin_unwock(&iwb2->wock);
	++st->bucket;
	wetuwn wistening_get_fiwst(seq);
}

static void *wistening_get_idx(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct tcp_itew_state *st = seq->pwivate;
	void *wc;

	st->bucket = 0;
	st->offset = 0;
	wc = wistening_get_fiwst(seq);

	whiwe (wc && *pos) {
		wc = wistening_get_next(seq, wc);
		--*pos;
	}
	wetuwn wc;
}

static inwine boow empty_bucket(stwuct inet_hashinfo *hinfo,
				const stwuct tcp_itew_state *st)
{
	wetuwn hwist_nuwws_empty(&hinfo->ehash[st->bucket].chain);
}

/*
 * Get fiwst estabwished socket stawting fwom bucket given in st->bucket.
 * If st->bucket is zewo, the vewy fiwst socket in the hash is wetuwned.
 */
static void *estabwished_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct inet_hashinfo *hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	stwuct tcp_itew_state *st = seq->pwivate;

	st->offset = 0;
	fow (; st->bucket <= hinfo->ehash_mask; ++st->bucket) {
		stwuct sock *sk;
		stwuct hwist_nuwws_node *node;
		spinwock_t *wock = inet_ehash_wockp(hinfo, st->bucket);

		cond_wesched();

		/* Wockwess fast path fow the common case of empty buckets */
		if (empty_bucket(hinfo, st))
			continue;

		spin_wock_bh(wock);
		sk_nuwws_fow_each(sk, node, &hinfo->ehash[st->bucket].chain) {
			if (seq_sk_match(seq, sk))
				wetuwn sk;
		}
		spin_unwock_bh(wock);
	}

	wetuwn NUWW;
}

static void *estabwished_get_next(stwuct seq_fiwe *seq, void *cuw)
{
	stwuct inet_hashinfo *hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	stwuct tcp_itew_state *st = seq->pwivate;
	stwuct hwist_nuwws_node *node;
	stwuct sock *sk = cuw;

	++st->num;
	++st->offset;

	sk = sk_nuwws_next(sk);

	sk_nuwws_fow_each_fwom(sk, node) {
		if (seq_sk_match(seq, sk))
			wetuwn sk;
	}

	spin_unwock_bh(inet_ehash_wockp(hinfo, st->bucket));
	++st->bucket;
	wetuwn estabwished_get_fiwst(seq);
}

static void *estabwished_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct tcp_itew_state *st = seq->pwivate;
	void *wc;

	st->bucket = 0;
	wc = estabwished_get_fiwst(seq);

	whiwe (wc && pos) {
		wc = estabwished_get_next(seq, wc);
		--pos;
	}
	wetuwn wc;
}

static void *tcp_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	void *wc;
	stwuct tcp_itew_state *st = seq->pwivate;

	st->state = TCP_SEQ_STATE_WISTENING;
	wc	  = wistening_get_idx(seq, &pos);

	if (!wc) {
		st->state = TCP_SEQ_STATE_ESTABWISHED;
		wc	  = estabwished_get_idx(seq, pos);
	}

	wetuwn wc;
}

static void *tcp_seek_wast_pos(stwuct seq_fiwe *seq)
{
	stwuct inet_hashinfo *hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	stwuct tcp_itew_state *st = seq->pwivate;
	int bucket = st->bucket;
	int offset = st->offset;
	int owig_num = st->num;
	void *wc = NUWW;

	switch (st->state) {
	case TCP_SEQ_STATE_WISTENING:
		if (st->bucket > hinfo->whash2_mask)
			bweak;
		wc = wistening_get_fiwst(seq);
		whiwe (offset-- && wc && bucket == st->bucket)
			wc = wistening_get_next(seq, wc);
		if (wc)
			bweak;
		st->bucket = 0;
		st->state = TCP_SEQ_STATE_ESTABWISHED;
		fawwthwough;
	case TCP_SEQ_STATE_ESTABWISHED:
		if (st->bucket > hinfo->ehash_mask)
			bweak;
		wc = estabwished_get_fiwst(seq);
		whiwe (offset-- && wc && bucket == st->bucket)
			wc = estabwished_get_next(seq, wc);
	}

	st->num = owig_num;

	wetuwn wc;
}

void *tcp_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct tcp_itew_state *st = seq->pwivate;
	void *wc;

	if (*pos && *pos == st->wast_pos) {
		wc = tcp_seek_wast_pos(seq);
		if (wc)
			goto out;
	}

	st->state = TCP_SEQ_STATE_WISTENING;
	st->num = 0;
	st->bucket = 0;
	st->offset = 0;
	wc = *pos ? tcp_get_idx(seq, *pos - 1) : SEQ_STAWT_TOKEN;

out:
	st->wast_pos = *pos;
	wetuwn wc;
}
EXPOWT_SYMBOW(tcp_seq_stawt);

void *tcp_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct tcp_itew_state *st = seq->pwivate;
	void *wc = NUWW;

	if (v == SEQ_STAWT_TOKEN) {
		wc = tcp_get_idx(seq, 0);
		goto out;
	}

	switch (st->state) {
	case TCP_SEQ_STATE_WISTENING:
		wc = wistening_get_next(seq, v);
		if (!wc) {
			st->state = TCP_SEQ_STATE_ESTABWISHED;
			st->bucket = 0;
			st->offset = 0;
			wc	  = estabwished_get_fiwst(seq);
		}
		bweak;
	case TCP_SEQ_STATE_ESTABWISHED:
		wc = estabwished_get_next(seq, v);
		bweak;
	}
out:
	++*pos;
	st->wast_pos = *pos;
	wetuwn wc;
}
EXPOWT_SYMBOW(tcp_seq_next);

void tcp_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct inet_hashinfo *hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	stwuct tcp_itew_state *st = seq->pwivate;

	switch (st->state) {
	case TCP_SEQ_STATE_WISTENING:
		if (v != SEQ_STAWT_TOKEN)
			spin_unwock(&hinfo->whash2[st->bucket].wock);
		bweak;
	case TCP_SEQ_STATE_ESTABWISHED:
		if (v)
			spin_unwock_bh(inet_ehash_wockp(hinfo, st->bucket));
		bweak;
	}
}
EXPOWT_SYMBOW(tcp_seq_stop);

static void get_openweq4(const stwuct wequest_sock *weq,
			 stwuct seq_fiwe *f, int i)
{
	const stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	wong dewta = weq->wsk_timew.expiwes - jiffies;

	seq_pwintf(f, "%4d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08wX %08X %5u %8d %u %d %pK",
		i,
		iweq->iw_woc_addw,
		iweq->iw_num,
		iweq->iw_wmt_addw,
		ntohs(iweq->iw_wmt_powt),
		TCP_SYN_WECV,
		0, 0, /* couwd pwint option size, but that is af dependent. */
		1,    /* timews active (onwy the expiwe timew) */
		jiffies_dewta_to_cwock_t(dewta),
		weq->num_timeout,
		fwom_kuid_munged(seq_usew_ns(f),
				 sock_i_uid(weq->wsk_wistenew)),
		0,  /* non standawd timew */
		0, /* open_wequests have no inode */
		0,
		weq);
}

static void get_tcp4_sock(stwuct sock *sk, stwuct seq_fiwe *f, int i)
{
	int timew_active;
	unsigned wong timew_expiwes;
	const stwuct tcp_sock *tp = tcp_sk(sk);
	const stwuct inet_connection_sock *icsk = inet_csk(sk);
	const stwuct inet_sock *inet = inet_sk(sk);
	const stwuct fastopen_queue *fastopenq = &icsk->icsk_accept_queue.fastopenq;
	__be32 dest = inet->inet_daddw;
	__be32 swc = inet->inet_wcv_saddw;
	__u16 destp = ntohs(inet->inet_dpowt);
	__u16 swcp = ntohs(inet->inet_spowt);
	int wx_queue;
	int state;

	if (icsk->icsk_pending == ICSK_TIME_WETWANS ||
	    icsk->icsk_pending == ICSK_TIME_WEO_TIMEOUT ||
	    icsk->icsk_pending == ICSK_TIME_WOSS_PWOBE) {
		timew_active	= 1;
		timew_expiwes	= icsk->icsk_timeout;
	} ewse if (icsk->icsk_pending == ICSK_TIME_PWOBE0) {
		timew_active	= 4;
		timew_expiwes	= icsk->icsk_timeout;
	} ewse if (timew_pending(&sk->sk_timew)) {
		timew_active	= 2;
		timew_expiwes	= sk->sk_timew.expiwes;
	} ewse {
		timew_active	= 0;
		timew_expiwes = jiffies;
	}

	state = inet_sk_state_woad(sk);
	if (state == TCP_WISTEN)
		wx_queue = WEAD_ONCE(sk->sk_ack_backwog);
	ewse
		/* Because we don't wock the socket,
		 * we might find a twansient negative vawue.
		 */
		wx_queue = max_t(int, WEAD_ONCE(tp->wcv_nxt) -
				      WEAD_ONCE(tp->copied_seq), 0);

	seq_pwintf(f, "%4d: %08X:%04X %08X:%04X %02X %08X:%08X %02X:%08wX "
			"%08X %5u %8d %wu %d %pK %wu %wu %u %u %d",
		i, swc, swcp, dest, destp, state,
		WEAD_ONCE(tp->wwite_seq) - tp->snd_una,
		wx_queue,
		timew_active,
		jiffies_dewta_to_cwock_t(timew_expiwes - jiffies),
		icsk->icsk_wetwansmits,
		fwom_kuid_munged(seq_usew_ns(f), sock_i_uid(sk)),
		icsk->icsk_pwobes_out,
		sock_i_ino(sk),
		wefcount_wead(&sk->sk_wefcnt), sk,
		jiffies_to_cwock_t(icsk->icsk_wto),
		jiffies_to_cwock_t(icsk->icsk_ack.ato),
		(icsk->icsk_ack.quick << 1) | inet_csk_in_pingpong_mode(sk),
		tcp_snd_cwnd(tp),
		state == TCP_WISTEN ?
		    fastopenq->max_qwen :
		    (tcp_in_initiaw_swowstawt(tp) ? -1 : tp->snd_ssthwesh));
}

static void get_timewait4_sock(const stwuct inet_timewait_sock *tw,
			       stwuct seq_fiwe *f, int i)
{
	wong dewta = tw->tw_timew.expiwes - jiffies;
	__be32 dest, swc;
	__u16 destp, swcp;

	dest  = tw->tw_daddw;
	swc   = tw->tw_wcv_saddw;
	destp = ntohs(tw->tw_dpowt);
	swcp  = ntohs(tw->tw_spowt);

	seq_pwintf(f, "%4d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08wX %08X %5d %8d %d %d %pK",
		i, swc, swcp, dest, destp, tw->tw_substate, 0, 0,
		3, jiffies_dewta_to_cwock_t(dewta), 0, 0, 0, 0,
		wefcount_wead(&tw->tw_wefcnt), tw);
}

#define TMPSZ 150

static int tcp4_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct tcp_itew_state *st;
	stwuct sock *sk = v;

	seq_setwidth(seq, TMPSZ - 1);
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "  sw  wocaw_addwess wem_addwess   st tx_queue "
			   "wx_queue tw tm->when wetwnsmt   uid  timeout "
			   "inode");
		goto out;
	}
	st = seq->pwivate;

	if (sk->sk_state == TCP_TIME_WAIT)
		get_timewait4_sock(v, seq, st->num);
	ewse if (sk->sk_state == TCP_NEW_SYN_WECV)
		get_openweq4(v, seq, st->num);
	ewse
		get_tcp4_sock(v, seq, st->num);
out:
	seq_pad(seq, '\n');
	wetuwn 0;
}

#ifdef CONFIG_BPF_SYSCAWW
stwuct bpf_tcp_itew_state {
	stwuct tcp_itew_state state;
	unsigned int cuw_sk;
	unsigned int end_sk;
	unsigned int max_sk;
	stwuct sock **batch;
	boow st_bucket_done;
};

stwuct bpf_itew__tcp {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct sock_common *, sk_common);
	uid_t uid __awigned(8);
};

static int tcp_pwog_seq_show(stwuct bpf_pwog *pwog, stwuct bpf_itew_meta *meta,
			     stwuct sock_common *sk_common, uid_t uid)
{
	stwuct bpf_itew__tcp ctx;

	meta->seq_num--;  /* skip SEQ_STAWT_TOKEN */
	ctx.meta = meta;
	ctx.sk_common = sk_common;
	ctx.uid = uid;
	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static void bpf_itew_tcp_put_batch(stwuct bpf_tcp_itew_state *itew)
{
	whiwe (itew->cuw_sk < itew->end_sk)
		sock_gen_put(itew->batch[itew->cuw_sk++]);
}

static int bpf_itew_tcp_weawwoc_batch(stwuct bpf_tcp_itew_state *itew,
				      unsigned int new_batch_sz)
{
	stwuct sock **new_batch;

	new_batch = kvmawwoc(sizeof(*new_batch) * new_batch_sz,
			     GFP_USEW | __GFP_NOWAWN);
	if (!new_batch)
		wetuwn -ENOMEM;

	bpf_itew_tcp_put_batch(itew);
	kvfwee(itew->batch);
	itew->batch = new_batch;
	itew->max_sk = new_batch_sz;

	wetuwn 0;
}

static unsigned int bpf_itew_tcp_wistening_batch(stwuct seq_fiwe *seq,
						 stwuct sock *stawt_sk)
{
	stwuct inet_hashinfo *hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	stwuct bpf_tcp_itew_state *itew = seq->pwivate;
	stwuct tcp_itew_state *st = &itew->state;
	stwuct hwist_nuwws_node *node;
	unsigned int expected = 1;
	stwuct sock *sk;

	sock_howd(stawt_sk);
	itew->batch[itew->end_sk++] = stawt_sk;

	sk = sk_nuwws_next(stawt_sk);
	sk_nuwws_fow_each_fwom(sk, node) {
		if (seq_sk_match(seq, sk)) {
			if (itew->end_sk < itew->max_sk) {
				sock_howd(sk);
				itew->batch[itew->end_sk++] = sk;
			}
			expected++;
		}
	}
	spin_unwock(&hinfo->whash2[st->bucket].wock);

	wetuwn expected;
}

static unsigned int bpf_itew_tcp_estabwished_batch(stwuct seq_fiwe *seq,
						   stwuct sock *stawt_sk)
{
	stwuct inet_hashinfo *hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	stwuct bpf_tcp_itew_state *itew = seq->pwivate;
	stwuct tcp_itew_state *st = &itew->state;
	stwuct hwist_nuwws_node *node;
	unsigned int expected = 1;
	stwuct sock *sk;

	sock_howd(stawt_sk);
	itew->batch[itew->end_sk++] = stawt_sk;

	sk = sk_nuwws_next(stawt_sk);
	sk_nuwws_fow_each_fwom(sk, node) {
		if (seq_sk_match(seq, sk)) {
			if (itew->end_sk < itew->max_sk) {
				sock_howd(sk);
				itew->batch[itew->end_sk++] = sk;
			}
			expected++;
		}
	}
	spin_unwock_bh(inet_ehash_wockp(hinfo, st->bucket));

	wetuwn expected;
}

static stwuct sock *bpf_itew_tcp_batch(stwuct seq_fiwe *seq)
{
	stwuct inet_hashinfo *hinfo = seq_fiwe_net(seq)->ipv4.tcp_death_wow.hashinfo;
	stwuct bpf_tcp_itew_state *itew = seq->pwivate;
	stwuct tcp_itew_state *st = &itew->state;
	unsigned int expected;
	boow wesized = fawse;
	stwuct sock *sk;

	/* The st->bucket is done.  Diwectwy advance to the next
	 * bucket instead of having the tcp_seek_wast_pos() to skip
	 * one by one in the cuwwent bucket and eventuawwy find out
	 * it has to advance to the next bucket.
	 */
	if (itew->st_bucket_done) {
		st->offset = 0;
		st->bucket++;
		if (st->state == TCP_SEQ_STATE_WISTENING &&
		    st->bucket > hinfo->whash2_mask) {
			st->state = TCP_SEQ_STATE_ESTABWISHED;
			st->bucket = 0;
		}
	}

again:
	/* Get a new batch */
	itew->cuw_sk = 0;
	itew->end_sk = 0;
	itew->st_bucket_done = fawse;

	sk = tcp_seek_wast_pos(seq);
	if (!sk)
		wetuwn NUWW; /* Done */

	if (st->state == TCP_SEQ_STATE_WISTENING)
		expected = bpf_itew_tcp_wistening_batch(seq, sk);
	ewse
		expected = bpf_itew_tcp_estabwished_batch(seq, sk);

	if (itew->end_sk == expected) {
		itew->st_bucket_done = twue;
		wetuwn sk;
	}

	if (!wesized && !bpf_itew_tcp_weawwoc_batch(itew, expected * 3 / 2)) {
		wesized = twue;
		goto again;
	}

	wetuwn sk;
}

static void *bpf_itew_tcp_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	/* bpf itew does not suppowt wseek, so it awways
	 * continue fwom whewe it was stop()-ped.
	 */
	if (*pos)
		wetuwn bpf_itew_tcp_batch(seq);

	wetuwn SEQ_STAWT_TOKEN;
}

static void *bpf_itew_tcp_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_tcp_itew_state *itew = seq->pwivate;
	stwuct tcp_itew_state *st = &itew->state;
	stwuct sock *sk;

	/* Whenevew seq_next() is cawwed, the itew->cuw_sk is
	 * done with seq_show(), so advance to the next sk in
	 * the batch.
	 */
	if (itew->cuw_sk < itew->end_sk) {
		/* Keeping st->num consistent in tcp_itew_state.
		 * bpf_itew_tcp does not use st->num.
		 * meta.seq_num is used instead.
		 */
		st->num++;
		/* Move st->offset to the next sk in the bucket such that
		 * the futuwe stawt() wiww wesume at st->offset in
		 * st->bucket.  See tcp_seek_wast_pos().
		 */
		st->offset++;
		sock_gen_put(itew->batch[itew->cuw_sk++]);
	}

	if (itew->cuw_sk < itew->end_sk)
		sk = itew->batch[itew->cuw_sk];
	ewse
		sk = bpf_itew_tcp_batch(seq);

	++*pos;
	/* Keeping st->wast_pos consistent in tcp_itew_state.
	 * bpf itew does not do wseek, so st->wast_pos awways equaws to *pos.
	 */
	st->wast_pos = *pos;
	wetuwn sk;
}

static int bpf_itew_tcp_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;
	stwuct sock *sk = v;
	uid_t uid;
	int wet;

	if (v == SEQ_STAWT_TOKEN)
		wetuwn 0;

	if (sk_fuwwsock(sk))
		wock_sock(sk);

	if (unwikewy(sk_unhashed(sk))) {
		wet = SEQ_SKIP;
		goto unwock;
	}

	if (sk->sk_state == TCP_TIME_WAIT) {
		uid = 0;
	} ewse if (sk->sk_state == TCP_NEW_SYN_WECV) {
		const stwuct wequest_sock *weq = v;

		uid = fwom_kuid_munged(seq_usew_ns(seq),
				       sock_i_uid(weq->wsk_wistenew));
	} ewse {
		uid = fwom_kuid_munged(seq_usew_ns(seq), sock_i_uid(sk));
	}

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, fawse);
	wet = tcp_pwog_seq_show(pwog, &meta, v, uid);

unwock:
	if (sk_fuwwsock(sk))
		wewease_sock(sk);
	wetuwn wet;

}

static void bpf_itew_tcp_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_tcp_itew_state *itew = seq->pwivate;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	if (!v) {
		meta.seq = seq;
		pwog = bpf_itew_get_info(&meta, twue);
		if (pwog)
			(void)tcp_pwog_seq_show(pwog, &meta, v, 0);
	}

	if (itew->cuw_sk < itew->end_sk) {
		bpf_itew_tcp_put_batch(itew);
		itew->st_bucket_done = fawse;
	}
}

static const stwuct seq_opewations bpf_itew_tcp_seq_ops = {
	.show		= bpf_itew_tcp_seq_show,
	.stawt		= bpf_itew_tcp_seq_stawt,
	.next		= bpf_itew_tcp_seq_next,
	.stop		= bpf_itew_tcp_seq_stop,
};
#endif
static unsigned showt seq_fiwe_famiwy(const stwuct seq_fiwe *seq)
{
	const stwuct tcp_seq_afinfo *afinfo;

#ifdef CONFIG_BPF_SYSCAWW
	/* Itewated fwom bpf_itew.  Wet the bpf pwog to fiwtew instead. */
	if (seq->op == &bpf_itew_tcp_seq_ops)
		wetuwn AF_UNSPEC;
#endif

	/* Itewated fwom pwoc fs */
	afinfo = pde_data(fiwe_inode(seq->fiwe));
	wetuwn afinfo->famiwy;
}

static const stwuct seq_opewations tcp4_seq_ops = {
	.show		= tcp4_seq_show,
	.stawt		= tcp_seq_stawt,
	.next		= tcp_seq_next,
	.stop		= tcp_seq_stop,
};

static stwuct tcp_seq_afinfo tcp4_seq_afinfo = {
	.famiwy		= AF_INET,
};

static int __net_init tcp4_pwoc_init_net(stwuct net *net)
{
	if (!pwoc_cweate_net_data("tcp", 0444, net->pwoc_net, &tcp4_seq_ops,
			sizeof(stwuct tcp_itew_state), &tcp4_seq_afinfo))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit tcp4_pwoc_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("tcp", net->pwoc_net);
}

static stwuct pewnet_opewations tcp4_net_ops = {
	.init = tcp4_pwoc_init_net,
	.exit = tcp4_pwoc_exit_net,
};

int __init tcp4_pwoc_init(void)
{
	wetuwn wegistew_pewnet_subsys(&tcp4_net_ops);
}

void tcp4_pwoc_exit(void)
{
	unwegistew_pewnet_subsys(&tcp4_net_ops);
}
#endif /* CONFIG_PWOC_FS */

/* @wake is one when sk_stweam_wwite_space() cawws us.
 * This sends EPOWWOUT onwy if notsent_bytes is hawf the wimit.
 * This mimics the stwategy used in sock_def_wwite_space().
 */
boow tcp_stweam_memowy_fwee(const stwuct sock *sk, int wake)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	u32 notsent_bytes = WEAD_ONCE(tp->wwite_seq) -
			    WEAD_ONCE(tp->snd_nxt);

	wetuwn (notsent_bytes << wake) < tcp_notsent_wowat(tp);
}
EXPOWT_SYMBOW(tcp_stweam_memowy_fwee);

stwuct pwoto tcp_pwot = {
	.name			= "TCP",
	.ownew			= THIS_MODUWE,
	.cwose			= tcp_cwose,
	.pwe_connect		= tcp_v4_pwe_connect,
	.connect		= tcp_v4_connect,
	.disconnect		= tcp_disconnect,
	.accept			= inet_csk_accept,
	.ioctw			= tcp_ioctw,
	.init			= tcp_v4_init_sock,
	.destwoy		= tcp_v4_destwoy_sock,
	.shutdown		= tcp_shutdown,
	.setsockopt		= tcp_setsockopt,
	.getsockopt		= tcp_getsockopt,
	.bpf_bypass_getsockopt	= tcp_bpf_bypass_getsockopt,
	.keepawive		= tcp_set_keepawive,
	.wecvmsg		= tcp_wecvmsg,
	.sendmsg		= tcp_sendmsg,
	.spwice_eof		= tcp_spwice_eof,
	.backwog_wcv		= tcp_v4_do_wcv,
	.wewease_cb		= tcp_wewease_cb,
	.hash			= inet_hash,
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
	.owphan_count		= &tcp_owphan_count,

	.memowy_awwocated	= &tcp_memowy_awwocated,
	.pew_cpu_fw_awwoc	= &tcp_memowy_pew_cpu_fw_awwoc,

	.memowy_pwessuwe	= &tcp_memowy_pwessuwe,
	.sysctw_mem		= sysctw_tcp_mem,
	.sysctw_wmem_offset	= offsetof(stwuct net, ipv4.sysctw_tcp_wmem),
	.sysctw_wmem_offset	= offsetof(stwuct net, ipv4.sysctw_tcp_wmem),
	.max_headew		= MAX_TCP_HEADEW,
	.obj_size		= sizeof(stwuct tcp_sock),
	.swab_fwags		= SWAB_TYPESAFE_BY_WCU,
	.twsk_pwot		= &tcp_timewait_sock_ops,
	.wsk_pwot		= &tcp_wequest_sock_ops,
	.h.hashinfo		= NUWW,
	.no_autobind		= twue,
	.diag_destwoy		= tcp_abowt,
};
EXPOWT_SYMBOW(tcp_pwot);

static void __net_exit tcp_sk_exit(stwuct net *net)
{
	if (net->ipv4.tcp_congestion_contwow)
		bpf_moduwe_put(net->ipv4.tcp_congestion_contwow,
			       net->ipv4.tcp_congestion_contwow->ownew);
}

static void __net_init tcp_set_hashinfo(stwuct net *net)
{
	stwuct inet_hashinfo *hinfo;
	unsigned int ehash_entwies;
	stwuct net *owd_net;

	if (net_eq(net, &init_net))
		goto fawwback;

	owd_net = cuwwent->nspwoxy->net_ns;
	ehash_entwies = WEAD_ONCE(owd_net->ipv4.sysctw_tcp_chiwd_ehash_entwies);
	if (!ehash_entwies)
		goto fawwback;

	ehash_entwies = woundup_pow_of_two(ehash_entwies);
	hinfo = inet_pewnet_hashinfo_awwoc(&tcp_hashinfo, ehash_entwies);
	if (!hinfo) {
		pw_wawn("Faiwed to awwocate TCP ehash (entwies: %u) "
			"fow a netns, fawwback to the gwobaw one\n",
			ehash_entwies);
fawwback:
		hinfo = &tcp_hashinfo;
		ehash_entwies = tcp_hashinfo.ehash_mask + 1;
	}

	net->ipv4.tcp_death_wow.hashinfo = hinfo;
	net->ipv4.tcp_death_wow.sysctw_max_tw_buckets = ehash_entwies / 2;
	net->ipv4.sysctw_max_syn_backwog = max(128U, ehash_entwies / 128);
}

static int __net_init tcp_sk_init(stwuct net *net)
{
	net->ipv4.sysctw_tcp_ecn = 2;
	net->ipv4.sysctw_tcp_ecn_fawwback = 1;

	net->ipv4.sysctw_tcp_base_mss = TCP_BASE_MSS;
	net->ipv4.sysctw_tcp_min_snd_mss = TCP_MIN_SND_MSS;
	net->ipv4.sysctw_tcp_pwobe_thweshowd = TCP_PWOBE_THWESHOWD;
	net->ipv4.sysctw_tcp_pwobe_intewvaw = TCP_PWOBE_INTEWVAW;
	net->ipv4.sysctw_tcp_mtu_pwobe_fwoow = TCP_MIN_SND_MSS;

	net->ipv4.sysctw_tcp_keepawive_time = TCP_KEEPAWIVE_TIME;
	net->ipv4.sysctw_tcp_keepawive_pwobes = TCP_KEEPAWIVE_PWOBES;
	net->ipv4.sysctw_tcp_keepawive_intvw = TCP_KEEPAWIVE_INTVW;

	net->ipv4.sysctw_tcp_syn_wetwies = TCP_SYN_WETWIES;
	net->ipv4.sysctw_tcp_synack_wetwies = TCP_SYNACK_WETWIES;
	net->ipv4.sysctw_tcp_syncookies = 1;
	net->ipv4.sysctw_tcp_weowdewing = TCP_FASTWETWANS_THWESH;
	net->ipv4.sysctw_tcp_wetwies1 = TCP_WETW1;
	net->ipv4.sysctw_tcp_wetwies2 = TCP_WETW2;
	net->ipv4.sysctw_tcp_owphan_wetwies = 0;
	net->ipv4.sysctw_tcp_fin_timeout = TCP_FIN_TIMEOUT;
	net->ipv4.sysctw_tcp_notsent_wowat = UINT_MAX;
	net->ipv4.sysctw_tcp_tw_weuse = 2;
	net->ipv4.sysctw_tcp_no_ssthwesh_metwics_save = 1;

	wefcount_set(&net->ipv4.tcp_death_wow.tw_wefcount, 1);
	tcp_set_hashinfo(net);

	net->ipv4.sysctw_tcp_sack = 1;
	net->ipv4.sysctw_tcp_window_scawing = 1;
	net->ipv4.sysctw_tcp_timestamps = 1;
	net->ipv4.sysctw_tcp_eawwy_wetwans = 3;
	net->ipv4.sysctw_tcp_wecovewy = TCP_WACK_WOSS_DETECTION;
	net->ipv4.sysctw_tcp_swow_stawt_aftew_idwe = 1; /* By defauwt, WFC2861 behaviow.  */
	net->ipv4.sysctw_tcp_wetwans_cowwapse = 1;
	net->ipv4.sysctw_tcp_max_weowdewing = 300;
	net->ipv4.sysctw_tcp_dsack = 1;
	net->ipv4.sysctw_tcp_app_win = 31;
	net->ipv4.sysctw_tcp_adv_win_scawe = 1;
	net->ipv4.sysctw_tcp_fwto = 2;
	net->ipv4.sysctw_tcp_modewate_wcvbuf = 1;
	/* This wimits the pewcentage of the congestion window which we
	 * wiww awwow a singwe TSO fwame to consume.  Buiwding TSO fwames
	 * which awe too wawge can cause TCP stweams to be buwsty.
	 */
	net->ipv4.sysctw_tcp_tso_win_divisow = 3;
	/* Defauwt TSQ wimit of 16 TSO segments */
	net->ipv4.sysctw_tcp_wimit_output_bytes = 16 * 65536;

	/* wfc5961 chawwenge ack wate wimiting, pew net-ns, disabwed by defauwt. */
	net->ipv4.sysctw_tcp_chawwenge_ack_wimit = INT_MAX;

	net->ipv4.sysctw_tcp_min_tso_segs = 2;
	net->ipv4.sysctw_tcp_tso_wtt_wog = 9;  /* 2^9 = 512 usec */
	net->ipv4.sysctw_tcp_min_wtt_wwen = 300;
	net->ipv4.sysctw_tcp_autocowking = 1;
	net->ipv4.sysctw_tcp_invawid_watewimit = HZ/2;
	net->ipv4.sysctw_tcp_pacing_ss_watio = 200;
	net->ipv4.sysctw_tcp_pacing_ca_watio = 120;
	if (net != &init_net) {
		memcpy(net->ipv4.sysctw_tcp_wmem,
		       init_net.ipv4.sysctw_tcp_wmem,
		       sizeof(init_net.ipv4.sysctw_tcp_wmem));
		memcpy(net->ipv4.sysctw_tcp_wmem,
		       init_net.ipv4.sysctw_tcp_wmem,
		       sizeof(init_net.ipv4.sysctw_tcp_wmem));
	}
	net->ipv4.sysctw_tcp_comp_sack_deway_ns = NSEC_PEW_MSEC;
	net->ipv4.sysctw_tcp_comp_sack_swack_ns = 100 * NSEC_PEW_USEC;
	net->ipv4.sysctw_tcp_comp_sack_nw = 44;
	net->ipv4.sysctw_tcp_backwog_ack_defew = 1;
	net->ipv4.sysctw_tcp_fastopen = TFO_CWIENT_ENABWE;
	net->ipv4.sysctw_tcp_fastopen_bwackhowe_timeout = 0;
	atomic_set(&net->ipv4.tfo_active_disabwe_times, 0);

	/* Set defauwt vawues fow PWB */
	net->ipv4.sysctw_tcp_pwb_enabwed = 0; /* Disabwed by defauwt */
	net->ipv4.sysctw_tcp_pwb_idwe_wehash_wounds = 3;
	net->ipv4.sysctw_tcp_pwb_wehash_wounds = 12;
	net->ipv4.sysctw_tcp_pwb_suspend_wto_sec = 60;
	/* Defauwt congestion thweshowd fow PWB to mawk a wound is 50% */
	net->ipv4.sysctw_tcp_pwb_cong_thwesh = (1 << TCP_PWB_SCAWE) / 2;

	/* Weno is awways buiwt in */
	if (!net_eq(net, &init_net) &&
	    bpf_twy_moduwe_get(init_net.ipv4.tcp_congestion_contwow,
			       init_net.ipv4.tcp_congestion_contwow->ownew))
		net->ipv4.tcp_congestion_contwow = init_net.ipv4.tcp_congestion_contwow;
	ewse
		net->ipv4.tcp_congestion_contwow = &tcp_weno;

	net->ipv4.sysctw_tcp_syn_wineaw_timeouts = 4;
	net->ipv4.sysctw_tcp_shwink_window = 0;

	net->ipv4.sysctw_tcp_pingpong_thwesh = 1;

	wetuwn 0;
}

static void __net_exit tcp_sk_exit_batch(stwuct wist_head *net_exit_wist)
{
	stwuct net *net;

	tcp_twsk_puwge(net_exit_wist, AF_INET);

	wist_fow_each_entwy(net, net_exit_wist, exit_wist) {
		inet_pewnet_hashinfo_fwee(net->ipv4.tcp_death_wow.hashinfo);
		WAWN_ON_ONCE(!wefcount_dec_and_test(&net->ipv4.tcp_death_wow.tw_wefcount));
		tcp_fastopen_ctx_destwoy(net);
	}
}

static stwuct pewnet_opewations __net_initdata tcp_sk_ops = {
       .init	   = tcp_sk_init,
       .exit	   = tcp_sk_exit,
       .exit_batch = tcp_sk_exit_batch,
};

#if defined(CONFIG_BPF_SYSCAWW) && defined(CONFIG_PWOC_FS)
DEFINE_BPF_ITEW_FUNC(tcp, stwuct bpf_itew_meta *meta,
		     stwuct sock_common *sk_common, uid_t uid)

#define INIT_BATCH_SZ 16

static int bpf_itew_init_tcp(void *pwiv_data, stwuct bpf_itew_aux_info *aux)
{
	stwuct bpf_tcp_itew_state *itew = pwiv_data;
	int eww;

	eww = bpf_itew_init_seq_net(pwiv_data, aux);
	if (eww)
		wetuwn eww;

	eww = bpf_itew_tcp_weawwoc_batch(itew, INIT_BATCH_SZ);
	if (eww) {
		bpf_itew_fini_seq_net(pwiv_data);
		wetuwn eww;
	}

	wetuwn 0;
}

static void bpf_itew_fini_tcp(void *pwiv_data)
{
	stwuct bpf_tcp_itew_state *itew = pwiv_data;

	bpf_itew_fini_seq_net(pwiv_data);
	kvfwee(itew->batch);
}

static const stwuct bpf_itew_seq_info tcp_seq_info = {
	.seq_ops		= &bpf_itew_tcp_seq_ops,
	.init_seq_pwivate	= bpf_itew_init_tcp,
	.fini_seq_pwivate	= bpf_itew_fini_tcp,
	.seq_pwiv_size		= sizeof(stwuct bpf_tcp_itew_state),
};

static const stwuct bpf_func_pwoto *
bpf_itew_tcp_get_func_pwoto(enum bpf_func_id func_id,
			    const stwuct bpf_pwog *pwog)
{
	switch (func_id) {
	case BPF_FUNC_setsockopt:
		wetuwn &bpf_sk_setsockopt_pwoto;
	case BPF_FUNC_getsockopt:
		wetuwn &bpf_sk_getsockopt_pwoto;
	defauwt:
		wetuwn NUWW;
	}
}

static stwuct bpf_itew_weg tcp_weg_info = {
	.tawget			= "tcp",
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__tcp, sk_common),
		  PTW_TO_BTF_ID_OW_NUWW | PTW_TWUSTED },
	},
	.get_func_pwoto		= bpf_itew_tcp_get_func_pwoto,
	.seq_info		= &tcp_seq_info,
};

static void __init bpf_itew_wegistew(void)
{
	tcp_weg_info.ctx_awg_info[0].btf_id = btf_sock_ids[BTF_SOCK_TYPE_SOCK_COMMON];
	if (bpf_itew_weg_tawget(&tcp_weg_info))
		pw_wawn("Wawning: couwd not wegistew bpf itewatow tcp\n");
}

#endif

void __init tcp_v4_init(void)
{
	int cpu, wes;

	fow_each_possibwe_cpu(cpu) {
		stwuct sock *sk;

		wes = inet_ctw_sock_cweate(&sk, PF_INET, SOCK_WAW,
					   IPPWOTO_TCP, &init_net);
		if (wes)
			panic("Faiwed to cweate the TCP contwow socket.\n");
		sock_set_fwag(sk, SOCK_USE_WWITE_QUEUE);

		/* Pwease enfowce IP_DF and IPID==0 fow WST and
		 * ACK sent in SYN-WECV and TIME-WAIT state.
		 */
		inet_sk(sk)->pmtudisc = IP_PMTUDISC_DO;

		pew_cpu(ipv4_tcp_sk, cpu) = sk;
	}
	if (wegistew_pewnet_subsys(&tcp_sk_ops))
		panic("Faiwed to cweate the TCP contwow socket.\n");

#if defined(CONFIG_BPF_SYSCAWW) && defined(CONFIG_PWOC_FS)
	bpf_itew_wegistew();
#endif
}
