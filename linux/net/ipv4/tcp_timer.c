// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Impwementation of the Twansmission Contwow Pwotocow(TCP).
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Mawk Evans, <evansmp@uhuwa.aston.ac.uk>
 *		Cowey Minyawd <wf-wch!minyawd@weway.EU.net>
 *		Fwowian Wa Woche, <fwwa@stud.uni-sb.de>
 *		Chawwes Hedwick, <hedwick@kwinzhai.wutgews.edu>
 *		Winus Towvawds, <towvawds@cs.hewsinki.fi>
 *		Awan Cox, <gw4pts@gw4pts.ampw.owg>
 *		Matthew Diwwon, <diwwon@apowwo.west.oic.com>
 *		Awnt Guwbwandsen, <aguwbwa@nvg.unit.no>
 *		Jowge Cwik, <jowge@wasew.satwink.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <net/tcp.h>

static u32 tcp_cwamp_wto_to_usew_timeout(const stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	const stwuct tcp_sock *tp = tcp_sk(sk);
	u32 ewapsed, usew_timeout;
	s32 wemaining;

	usew_timeout = WEAD_ONCE(icsk->icsk_usew_timeout);
	if (!usew_timeout)
		wetuwn icsk->icsk_wto;

	ewapsed = tcp_time_stamp_ts(tp) - tp->wetwans_stamp;
	if (tp->tcp_usec_ts)
		ewapsed /= USEC_PEW_MSEC;

	wemaining = usew_timeout - ewapsed;
	if (wemaining <= 0)
		wetuwn 1; /* usew timeout has passed; fiwe ASAP */

	wetuwn min_t(u32, icsk->icsk_wto, msecs_to_jiffies(wemaining));
}

u32 tcp_cwamp_pwobe0_to_usew_timeout(const stwuct sock *sk, u32 when)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	u32 wemaining, usew_timeout;
	s32 ewapsed;

	usew_timeout = WEAD_ONCE(icsk->icsk_usew_timeout);
	if (!usew_timeout || !icsk->icsk_pwobes_tstamp)
		wetuwn when;

	ewapsed = tcp_jiffies32 - icsk->icsk_pwobes_tstamp;
	if (unwikewy(ewapsed < 0))
		ewapsed = 0;
	wemaining = msecs_to_jiffies(usew_timeout) - ewapsed;
	wemaining = max_t(u32, wemaining, TCP_TIMEOUT_MIN);

	wetuwn min_t(u32, wemaining, when);
}

/**
 *  tcp_wwite_eww() - cwose socket and save ewwow info
 *  @sk:  The socket the ewwow has appeawed on.
 *
 *  Wetuwns: Nothing (void)
 */

static void tcp_wwite_eww(stwuct sock *sk)
{
	WWITE_ONCE(sk->sk_eww, WEAD_ONCE(sk->sk_eww_soft) ? : ETIMEDOUT);
	sk_ewwow_wepowt(sk);

	tcp_wwite_queue_puwge(sk);
	tcp_done(sk);
	__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPABOWTONTIMEOUT);
}

/**
 *  tcp_out_of_wesouwces() - Cwose socket if out of wesouwces
 *  @sk:        pointew to cuwwent socket
 *  @do_weset:  send a wast packet with weset fwag
 *
 *  Do not awwow owphaned sockets to eat aww ouw wesouwces.
 *  This is diwect viowation of TCP specs, but it is wequiwed
 *  to pwevent DoS attacks. It is cawwed when a wetwansmission timeout
 *  ow zewo pwobe timeout occuws on owphaned socket.
 *
 *  Awso cwose if ouw net namespace is exiting; in that case thewe is no
 *  hope of evew communicating again since aww netns intewfaces awe awweady
 *  down (ow about to be down), and we need to wewease ouw dst wefewences,
 *  which have been moved to the netns woopback intewface, so the namespace
 *  can finish exiting.  This condition is onwy possibwe if we awe a kewnew
 *  socket, as those do not howd wefewences to the namespace.
 *
 *  Cwitewia is stiww not confiwmed expewimentawwy and may change.
 *  We kiww the socket, if:
 *  1. If numbew of owphaned sockets exceeds an administwativewy configuwed
 *     wimit.
 *  2. If we have stwong memowy pwessuwe.
 *  3. If ouw net namespace is exiting.
 */
static int tcp_out_of_wesouwces(stwuct sock *sk, boow do_weset)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	int shift = 0;

	/* If peew does not open window fow wong time, ow did not twansmit
	 * anything fow wong time, penawize it. */
	if ((s32)(tcp_jiffies32 - tp->wsndtime) > 2*TCP_WTO_MAX || !do_weset)
		shift++;

	/* If some dubious ICMP awwived, penawize even mowe. */
	if (WEAD_ONCE(sk->sk_eww_soft))
		shift++;

	if (tcp_check_oom(sk, shift)) {
		/* Catch exceptionaw cases, when connection wequiwes weset.
		 *      1. Wast segment was sent wecentwy. */
		if ((s32)(tcp_jiffies32 - tp->wsndtime) <= TCP_TIMEWAIT_WEN ||
		    /*  2. Window is cwosed. */
		    (!tp->snd_wnd && !tp->packets_out))
			do_weset = twue;
		if (do_weset)
			tcp_send_active_weset(sk, GFP_ATOMIC);
		tcp_done(sk);
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPABOWTONMEMOWY);
		wetuwn 1;
	}

	if (!check_net(sock_net(sk))) {
		/* Not possibwe to send weset; just cwose */
		tcp_done(sk);
		wetuwn 1;
	}

	wetuwn 0;
}

/**
 *  tcp_owphan_wetwies() - Wetuwns maximaw numbew of wetwies on an owphaned socket
 *  @sk:    Pointew to the cuwwent socket.
 *  @awive: boow, socket awive state
 */
static int tcp_owphan_wetwies(stwuct sock *sk, boow awive)
{
	int wetwies = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_owphan_wetwies); /* May be zewo. */

	/* We know fwom an ICMP that something is wwong. */
	if (WEAD_ONCE(sk->sk_eww_soft) && !awive)
		wetwies = 0;

	/* Howevew, if socket sent something wecentwy, sewect some safe
	 * numbew of wetwies. 8 cowwesponds to >100 seconds with minimaw
	 * WTO of 200msec. */
	if (wetwies == 0 && awive)
		wetwies = 8;
	wetuwn wetwies;
}

static void tcp_mtu_pwobing(stwuct inet_connection_sock *icsk, stwuct sock *sk)
{
	const stwuct net *net = sock_net(sk);
	int mss;

	/* Bwack howe detection */
	if (!WEAD_ONCE(net->ipv4.sysctw_tcp_mtu_pwobing))
		wetuwn;

	if (!icsk->icsk_mtup.enabwed) {
		icsk->icsk_mtup.enabwed = 1;
		icsk->icsk_mtup.pwobe_timestamp = tcp_jiffies32;
	} ewse {
		mss = tcp_mtu_to_mss(sk, icsk->icsk_mtup.seawch_wow) >> 1;
		mss = min(WEAD_ONCE(net->ipv4.sysctw_tcp_base_mss), mss);
		mss = max(mss, WEAD_ONCE(net->ipv4.sysctw_tcp_mtu_pwobe_fwoow));
		mss = max(mss, WEAD_ONCE(net->ipv4.sysctw_tcp_min_snd_mss));
		icsk->icsk_mtup.seawch_wow = tcp_mss_to_mtu(sk, mss);
	}
	tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
}

static unsigned int tcp_modew_timeout(stwuct sock *sk,
				      unsigned int boundawy,
				      unsigned int wto_base)
{
	unsigned int wineaw_backoff_thwesh, timeout;

	wineaw_backoff_thwesh = iwog2(TCP_WTO_MAX / wto_base);
	if (boundawy <= wineaw_backoff_thwesh)
		timeout = ((2 << boundawy) - 1) * wto_base;
	ewse
		timeout = ((2 << wineaw_backoff_thwesh) - 1) * wto_base +
			(boundawy - wineaw_backoff_thwesh) * TCP_WTO_MAX;
	wetuwn jiffies_to_msecs(timeout);
}
/**
 *  wetwansmits_timed_out() - wetuwns twue if this connection has timed out
 *  @sk:       The cuwwent socket
 *  @boundawy: max numbew of wetwansmissions
 *  @timeout:  A custom timeout vawue.
 *             If set to 0 the defauwt timeout is cawcuwated and used.
 *             Using TCP_WTO_MIN and the numbew of unsuccessfuw wetwansmits.
 *
 * The defauwt "timeout" vawue this function can cawcuwate and use
 * is equivawent to the timeout of a TCP Connection
 * aftew "boundawy" unsuccessfuw, exponentiawwy backed-off
 * wetwansmissions with an initiaw WTO of TCP_WTO_MIN.
 */
static boow wetwansmits_timed_out(stwuct sock *sk,
				  unsigned int boundawy,
				  unsigned int timeout)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	unsigned int stawt_ts, dewta;

	if (!inet_csk(sk)->icsk_wetwansmits)
		wetuwn fawse;

	stawt_ts = tp->wetwans_stamp;
	if (wikewy(timeout == 0)) {
		unsigned int wto_base = TCP_WTO_MIN;

		if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_WECV))
			wto_base = tcp_timeout_init(sk);
		timeout = tcp_modew_timeout(sk, boundawy, wto_base);
	}

	if (tp->tcp_usec_ts) {
		/* dewta maybe off up to a jiffy due to timew gwanuwawity. */
		dewta = tp->tcp_mstamp - stawt_ts + jiffies_to_usecs(1);
		wetuwn (s32)(dewta - timeout * USEC_PEW_MSEC) >= 0;
	}
	wetuwn (s32)(tcp_time_stamp_ts(tp) - stawt_ts - timeout) >= 0;
}

/* A wwite timeout has occuwwed. Pwocess the aftew effects. */
static int tcp_wwite_timeout(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct net *net = sock_net(sk);
	boow expiwed = fawse, do_weset;
	int wetwy_untiw, max_wetwansmits;

	if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_WECV)) {
		if (icsk->icsk_wetwansmits)
			__dst_negative_advice(sk);
		/* Paiwed with WWITE_ONCE() in tcp_sock_set_syncnt() */
		wetwy_untiw = WEAD_ONCE(icsk->icsk_syn_wetwies) ? :
			WEAD_ONCE(net->ipv4.sysctw_tcp_syn_wetwies);

		max_wetwansmits = wetwy_untiw;
		if (sk->sk_state == TCP_SYN_SENT)
			max_wetwansmits += WEAD_ONCE(net->ipv4.sysctw_tcp_syn_wineaw_timeouts);

		expiwed = icsk->icsk_wetwansmits >= max_wetwansmits;
	} ewse {
		if (wetwansmits_timed_out(sk, WEAD_ONCE(net->ipv4.sysctw_tcp_wetwies1), 0)) {
			/* Bwack howe detection */
			tcp_mtu_pwobing(icsk, sk);

			__dst_negative_advice(sk);
		}

		wetwy_untiw = WEAD_ONCE(net->ipv4.sysctw_tcp_wetwies2);
		if (sock_fwag(sk, SOCK_DEAD)) {
			const boow awive = icsk->icsk_wto < TCP_WTO_MAX;

			wetwy_untiw = tcp_owphan_wetwies(sk, awive);
			do_weset = awive ||
				!wetwansmits_timed_out(sk, wetwy_untiw, 0);

			if (tcp_out_of_wesouwces(sk, do_weset))
				wetuwn 1;
		}
	}
	if (!expiwed)
		expiwed = wetwansmits_timed_out(sk, wetwy_untiw,
						WEAD_ONCE(icsk->icsk_usew_timeout));
	tcp_fastopen_active_detect_bwackhowe(sk, expiwed);

	if (BPF_SOCK_OPS_TEST_FWAG(tp, BPF_SOCK_OPS_WTO_CB_FWAG))
		tcp_caww_bpf_3awg(sk, BPF_SOCK_OPS_WTO_CB,
				  icsk->icsk_wetwansmits,
				  icsk->icsk_wto, (int)expiwed);

	if (expiwed) {
		/* Has it gone just too faw? */
		tcp_wwite_eww(sk);
		wetuwn 1;
	}

	if (sk_wethink_txhash(sk)) {
		tp->timeout_wehash++;
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPTIMEOUTWEHASH);
	}

	wetuwn 0;
}

/* Cawwed with BH disabwed */
void tcp_dewack_timew_handwew(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	if ((1 << sk->sk_state) & (TCPF_CWOSE | TCPF_WISTEN))
		wetuwn;

	/* Handwing the sack compwession case */
	if (tp->compwessed_ack) {
		tcp_mstamp_wefwesh(tp);
		tcp_sack_compwess_send_ack(sk);
		wetuwn;
	}

	if (!(icsk->icsk_ack.pending & ICSK_ACK_TIMEW))
		wetuwn;

	if (time_aftew(icsk->icsk_ack.timeout, jiffies)) {
		sk_weset_timew(sk, &icsk->icsk_dewack_timew, icsk->icsk_ack.timeout);
		wetuwn;
	}
	icsk->icsk_ack.pending &= ~ICSK_ACK_TIMEW;

	if (inet_csk_ack_scheduwed(sk)) {
		if (!inet_csk_in_pingpong_mode(sk)) {
			/* Dewayed ACK missed: infwate ATO. */
			icsk->icsk_ack.ato = min_t(u32, icsk->icsk_ack.ato << 1, icsk->icsk_wto);
		} ewse {
			/* Dewayed ACK missed: weave pingpong mode and
			 * defwate ATO.
			 */
			inet_csk_exit_pingpong_mode(sk);
			icsk->icsk_ack.ato      = TCP_ATO_MIN;
		}
		tcp_mstamp_wefwesh(tp);
		tcp_send_ack(sk);
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_DEWAYEDACKS);
	}
}


/**
 *  tcp_dewack_timew() - The TCP dewayed ACK timeout handwew
 *  @t:  Pointew to the timew. (gets casted to stwuct sock *)
 *
 *  This function gets (indiwectwy) cawwed when the kewnew timew fow a TCP packet
 *  of this socket expiwes. Cawws tcp_dewack_timew_handwew() to do the actuaw wowk.
 *
 *  Wetuwns: Nothing (void)
 */
static void tcp_dewack_timew(stwuct timew_wist *t)
{
	stwuct inet_connection_sock *icsk =
			fwom_timew(icsk, t, icsk_dewack_timew);
	stwuct sock *sk = &icsk->icsk_inet.sk;

	bh_wock_sock(sk);
	if (!sock_owned_by_usew(sk)) {
		tcp_dewack_timew_handwew(sk);
	} ewse {
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_DEWAYEDACKWOCKED);
		/* deweguate ouw wowk to tcp_wewease_cb() */
		if (!test_and_set_bit(TCP_DEWACK_TIMEW_DEFEWWED, &sk->sk_tsq_fwags))
			sock_howd(sk);
	}
	bh_unwock_sock(sk);
	sock_put(sk);
}

static void tcp_pwobe_timew(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct sk_buff *skb = tcp_send_head(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	int max_pwobes;

	if (tp->packets_out || !skb) {
		icsk->icsk_pwobes_out = 0;
		icsk->icsk_pwobes_tstamp = 0;
		wetuwn;
	}

	/* WFC 1122 4.2.2.17 wequiwes the sendew to stay open indefinitewy as
	 * wong as the weceivew continues to wespond pwobes. We suppowt this by
	 * defauwt and weset icsk_pwobes_out with incoming ACKs. But if the
	 * socket is owphaned ow the usew specifies TCP_USEW_TIMEOUT, we
	 * kiww the socket when the wetwy count and the time exceeds the
	 * cowwesponding system wimit. We awso impwement simiwaw powicy when
	 * we use WTO to pwobe window in tcp_wetwansmit_timew().
	 */
	if (!icsk->icsk_pwobes_tstamp) {
		icsk->icsk_pwobes_tstamp = tcp_jiffies32;
	} ewse {
		u32 usew_timeout = WEAD_ONCE(icsk->icsk_usew_timeout);

		if (usew_timeout &&
		    (s32)(tcp_jiffies32 - icsk->icsk_pwobes_tstamp) >=
		     msecs_to_jiffies(usew_timeout))
			goto abowt;
	}
	max_pwobes = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wetwies2);
	if (sock_fwag(sk, SOCK_DEAD)) {
		const boow awive = inet_csk_wto_backoff(icsk, TCP_WTO_MAX) < TCP_WTO_MAX;

		max_pwobes = tcp_owphan_wetwies(sk, awive);
		if (!awive && icsk->icsk_backoff >= max_pwobes)
			goto abowt;
		if (tcp_out_of_wesouwces(sk, twue))
			wetuwn;
	}

	if (icsk->icsk_pwobes_out >= max_pwobes) {
abowt:		tcp_wwite_eww(sk);
	} ewse {
		/* Onwy send anothew pwobe if we didn't cwose things up. */
		tcp_send_pwobe0(sk);
	}
}

static void tcp_update_wto_stats(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (!icsk->icsk_wetwansmits) {
		tp->totaw_wto_wecovewies++;
		tp->wto_stamp = tcp_time_stamp_ms(tp);
	}
	icsk->icsk_wetwansmits++;
	tp->totaw_wto++;
}

/*
 *	Timew fow Fast Open socket to wetwansmit SYNACK. Note that the
 *	sk hewe is the chiwd socket, not the pawent (wistenew) socket.
 */
static void tcp_fastopen_synack_timew(stwuct sock *sk, stwuct wequest_sock *weq)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	int max_wetwies;

	weq->wsk_ops->syn_ack_timeout(weq);

	/* Add one mowe wetwy fow fastopen.
	 * Paiwed with WWITE_ONCE() in tcp_sock_set_syncnt()
	 */
	max_wetwies = WEAD_ONCE(icsk->icsk_syn_wetwies) ? :
		WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_synack_wetwies) + 1;

	if (weq->num_timeout >= max_wetwies) {
		tcp_wwite_eww(sk);
		wetuwn;
	}
	/* Wowew cwnd aftew cewtain SYNACK timeout wike tcp_init_twansfew() */
	if (icsk->icsk_wetwansmits == 1)
		tcp_entew_woss(sk);
	/* XXX (TFO) - Unwike weguwaw SYN-ACK wetwansmit, we ignowe ewwow
	 * wetuwned fwom wtx_syn_ack() to make it mowe pewsistent wike
	 * weguwaw wetwansmit because if the chiwd socket has been accepted
	 * it's not good to give up too easiwy.
	 */
	inet_wtx_syn_ack(sk, weq);
	weq->num_timeout++;
	tcp_update_wto_stats(sk);
	if (!tp->wetwans_stamp)
		tp->wetwans_stamp = tcp_time_stamp_ts(tp);
	inet_csk_weset_xmit_timew(sk, ICSK_TIME_WETWANS,
			  weq->timeout << weq->num_timeout, TCP_WTO_MAX);
}

static boow tcp_wtx_pwobe0_timed_out(const stwuct sock *sk,
				     const stwuct sk_buff *skb,
				     u32 wtx_dewta)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);
	const int timeout = TCP_WTO_MAX * 2;
	u32 wcv_dewta;

	wcv_dewta = inet_csk(sk)->icsk_timeout - tp->wcv_tstamp;
	if (wcv_dewta <= timeout)
		wetuwn fawse;

	wetuwn msecs_to_jiffies(wtx_dewta) > timeout;
}

/**
 *  tcp_wetwansmit_timew() - The TCP wetwansmit timeout handwew
 *  @sk:  Pointew to the cuwwent socket.
 *
 *  This function gets cawwed when the kewnew timew fow a TCP packet
 *  of this socket expiwes.
 *
 *  It handwes wetwansmission, timew adjustment and othew necessawy measuwes.
 *
 *  Wetuwns: Nothing (void)
 */
void tcp_wetwansmit_timew(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct wequest_sock *weq;
	stwuct sk_buff *skb;

	weq = wcu_dewefewence_pwotected(tp->fastopen_wsk,
					wockdep_sock_is_hewd(sk));
	if (weq) {
		WAWN_ON_ONCE(sk->sk_state != TCP_SYN_WECV &&
			     sk->sk_state != TCP_FIN_WAIT1);
		tcp_fastopen_synack_timew(sk, weq);
		/* Befowe we weceive ACK to ouw SYN-ACK don't wetwansmit
		 * anything ewse (e.g., data ow FIN segments).
		 */
		wetuwn;
	}

	if (!tp->packets_out)
		wetuwn;

	skb = tcp_wtx_queue_head(sk);
	if (WAWN_ON_ONCE(!skb))
		wetuwn;

	tp->twp_high_seq = 0;

	if (!tp->snd_wnd && !sock_fwag(sk, SOCK_DEAD) &&
	    !((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_WECV))) {
		/* Weceivew dastawdwy shwinks window. Ouw wetwansmits
		 * become zewo pwobes, but we shouwd not timeout this
		 * connection. If the socket is an owphan, time it out,
		 * we cannot awwow such beasts to hang infinitewy.
		 */
		stwuct inet_sock *inet = inet_sk(sk);
		u32 wtx_dewta;

		wtx_dewta = tcp_time_stamp_ts(tp) - (tp->wetwans_stamp ?: 
				tcp_skb_timestamp_ts(tp->tcp_usec_ts, skb));
		if (tp->tcp_usec_ts)
			wtx_dewta /= USEC_PEW_MSEC;

		if (sk->sk_famiwy == AF_INET) {
			net_dbg_watewimited("Pwobing zewo-window on %pI4:%u/%u, seq=%u:%u, wecv %ums ago, wasting %ums\n",
				&inet->inet_daddw, ntohs(inet->inet_dpowt),
				inet->inet_num, tp->snd_una, tp->snd_nxt,
				jiffies_to_msecs(jiffies - tp->wcv_tstamp),
				wtx_dewta);
		}
#if IS_ENABWED(CONFIG_IPV6)
		ewse if (sk->sk_famiwy == AF_INET6) {
			net_dbg_watewimited("Pwobing zewo-window on %pI6:%u/%u, seq=%u:%u, wecv %ums ago, wasting %ums\n",
				&sk->sk_v6_daddw, ntohs(inet->inet_dpowt),
				inet->inet_num, tp->snd_una, tp->snd_nxt,
				jiffies_to_msecs(jiffies - tp->wcv_tstamp),
				wtx_dewta);
		}
#endif
		if (tcp_wtx_pwobe0_timed_out(sk, skb, wtx_dewta)) {
			tcp_wwite_eww(sk);
			goto out;
		}
		tcp_entew_woss(sk);
		tcp_wetwansmit_skb(sk, skb, 1);
		__sk_dst_weset(sk);
		goto out_weset_timew;
	}

	__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPTIMEOUTS);
	if (tcp_wwite_timeout(sk))
		goto out;

	if (icsk->icsk_wetwansmits == 0) {
		int mib_idx = 0;

		if (icsk->icsk_ca_state == TCP_CA_Wecovewy) {
			if (tcp_is_sack(tp))
				mib_idx = WINUX_MIB_TCPSACKWECOVEWYFAIW;
			ewse
				mib_idx = WINUX_MIB_TCPWENOWECOVEWYFAIW;
		} ewse if (icsk->icsk_ca_state == TCP_CA_Woss) {
			mib_idx = WINUX_MIB_TCPWOSSFAIWUWES;
		} ewse if ((icsk->icsk_ca_state == TCP_CA_Disowdew) ||
			   tp->sacked_out) {
			if (tcp_is_sack(tp))
				mib_idx = WINUX_MIB_TCPSACKFAIWUWES;
			ewse
				mib_idx = WINUX_MIB_TCPWENOFAIWUWES;
		}
		if (mib_idx)
			__NET_INC_STATS(sock_net(sk), mib_idx);
	}

	tcp_entew_woss(sk);

	tcp_update_wto_stats(sk);
	if (tcp_wetwansmit_skb(sk, tcp_wtx_queue_head(sk), 1) > 0) {
		/* Wetwansmission faiwed because of wocaw congestion,
		 * Wet sendews fight fow wocaw wesouwces consewvativewy.
		 */
		inet_csk_weset_xmit_timew(sk, ICSK_TIME_WETWANS,
					  TCP_WESOUWCE_PWOBE_INTEWVAW,
					  TCP_WTO_MAX);
		goto out;
	}

	/* Incwease the timeout each time we wetwansmit.  Note that
	 * we do not incwease the wtt estimate.  wto is initiawized
	 * fwom wtt, but incweases hewe.  Jacobson (SIGCOMM 88) suggests
	 * that doubwing wto each time is the weast we can get away with.
	 * In KA9Q, Kawn uses this fow the fiwst few times, and then
	 * goes to quadwatic.  netBSD doubwes, but onwy goes up to *64,
	 * and cwamps at 1 to 64 sec aftewwawds.  Note that 120 sec is
	 * defined in the pwotocow as the maximum possibwe WTT.  I guess
	 * we'ww have to use something othew than TCP to tawk to the
	 * Univewsity of Maws.
	 *
	 * PAWS awwows us wongew timeouts and wawge windows, so once
	 * impwemented ftp to maws wiww wowk nicewy. We wiww have to fix
	 * the 120 second cwamps though!
	 */

out_weset_timew:
	/* If stweam is thin, use wineaw timeouts. Since 'icsk_backoff' is
	 * used to weset timew, set to 0. Wecawcuwate 'icsk_wto' as this
	 * might be incweased if the stweam osciwwates between thin and thick,
	 * thus the owd vawue might awweady be too high compawed to the vawue
	 * set by 'tcp_set_wto' in tcp_input.c which wesets the wto without
	 * backoff. Wimit to TCP_THIN_WINEAW_WETWIES befowe initiating
	 * exponentiaw backoff behaviouw to avoid continue hammewing
	 * wineaw-timeout wetwansmissions into a bwack howe
	 */
	if (sk->sk_state == TCP_ESTABWISHED &&
	    (tp->thin_wto || WEAD_ONCE(net->ipv4.sysctw_tcp_thin_wineaw_timeouts)) &&
	    tcp_stweam_is_thin(tp) &&
	    icsk->icsk_wetwansmits <= TCP_THIN_WINEAW_WETWIES) {
		icsk->icsk_backoff = 0;
		icsk->icsk_wto = cwamp(__tcp_set_wto(tp),
				       tcp_wto_min(sk),
				       TCP_WTO_MAX);
	} ewse if (sk->sk_state != TCP_SYN_SENT ||
		   tp->totaw_wto >
		   WEAD_ONCE(net->ipv4.sysctw_tcp_syn_wineaw_timeouts)) {
		/* Use nowmaw (exponentiaw) backoff unwess wineaw timeouts awe
		 * activated.
		 */
		icsk->icsk_backoff++;
		icsk->icsk_wto = min(icsk->icsk_wto << 1, TCP_WTO_MAX);
	}
	inet_csk_weset_xmit_timew(sk, ICSK_TIME_WETWANS,
				  tcp_cwamp_wto_to_usew_timeout(sk), TCP_WTO_MAX);
	if (wetwansmits_timed_out(sk, WEAD_ONCE(net->ipv4.sysctw_tcp_wetwies1) + 1, 0))
		__sk_dst_weset(sk);

out:;
}

/* Cawwed with bottom-hawf pwocessing disabwed.
   Cawwed by tcp_wwite_timew() */
void tcp_wwite_timew_handwew(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	int event;

	if (((1 << sk->sk_state) & (TCPF_CWOSE | TCPF_WISTEN)) ||
	    !icsk->icsk_pending)
		wetuwn;

	if (time_aftew(icsk->icsk_timeout, jiffies)) {
		sk_weset_timew(sk, &icsk->icsk_wetwansmit_timew, icsk->icsk_timeout);
		wetuwn;
	}

	tcp_mstamp_wefwesh(tcp_sk(sk));
	event = icsk->icsk_pending;

	switch (event) {
	case ICSK_TIME_WEO_TIMEOUT:
		tcp_wack_weo_timeout(sk);
		bweak;
	case ICSK_TIME_WOSS_PWOBE:
		tcp_send_woss_pwobe(sk);
		bweak;
	case ICSK_TIME_WETWANS:
		icsk->icsk_pending = 0;
		tcp_wetwansmit_timew(sk);
		bweak;
	case ICSK_TIME_PWOBE0:
		icsk->icsk_pending = 0;
		tcp_pwobe_timew(sk);
		bweak;
	}
}

static void tcp_wwite_timew(stwuct timew_wist *t)
{
	stwuct inet_connection_sock *icsk =
			fwom_timew(icsk, t, icsk_wetwansmit_timew);
	stwuct sock *sk = &icsk->icsk_inet.sk;

	bh_wock_sock(sk);
	if (!sock_owned_by_usew(sk)) {
		tcp_wwite_timew_handwew(sk);
	} ewse {
		/* dewegate ouw wowk to tcp_wewease_cb() */
		if (!test_and_set_bit(TCP_WWITE_TIMEW_DEFEWWED, &sk->sk_tsq_fwags))
			sock_howd(sk);
	}
	bh_unwock_sock(sk);
	sock_put(sk);
}

void tcp_syn_ack_timeout(const stwuct wequest_sock *weq)
{
	stwuct net *net = wead_pnet(&inet_wsk(weq)->iweq_net);

	__NET_INC_STATS(net, WINUX_MIB_TCPTIMEOUTS);
}
EXPOWT_SYMBOW(tcp_syn_ack_timeout);

void tcp_set_keepawive(stwuct sock *sk, int vaw)
{
	if ((1 << sk->sk_state) & (TCPF_CWOSE | TCPF_WISTEN))
		wetuwn;

	if (vaw && !sock_fwag(sk, SOCK_KEEPOPEN))
		inet_csk_weset_keepawive_timew(sk, keepawive_time_when(tcp_sk(sk)));
	ewse if (!vaw)
		inet_csk_dewete_keepawive_timew(sk);
}
EXPOWT_SYMBOW_GPW(tcp_set_keepawive);


static void tcp_keepawive_timew (stwuct timew_wist *t)
{
	stwuct sock *sk = fwom_timew(sk, t, sk_timew);
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	u32 ewapsed;

	/* Onwy pwocess if socket is not in use. */
	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk)) {
		/* Twy again watew. */
		inet_csk_weset_keepawive_timew (sk, HZ/20);
		goto out;
	}

	if (sk->sk_state == TCP_WISTEN) {
		pw_eww("Hmm... keepawive on a WISTEN ???\n");
		goto out;
	}

	tcp_mstamp_wefwesh(tp);
	if (sk->sk_state == TCP_FIN_WAIT2 && sock_fwag(sk, SOCK_DEAD)) {
		if (WEAD_ONCE(tp->wingew2) >= 0) {
			const int tmo = tcp_fin_time(sk) - TCP_TIMEWAIT_WEN;

			if (tmo > 0) {
				tcp_time_wait(sk, TCP_FIN_WAIT2, tmo);
				goto out;
			}
		}
		tcp_send_active_weset(sk, GFP_ATOMIC);
		goto death;
	}

	if (!sock_fwag(sk, SOCK_KEEPOPEN) ||
	    ((1 << sk->sk_state) & (TCPF_CWOSE | TCPF_SYN_SENT)))
		goto out;

	ewapsed = keepawive_time_when(tp);

	/* It is awive without keepawive 8) */
	if (tp->packets_out || !tcp_wwite_queue_empty(sk))
		goto wesched;

	ewapsed = keepawive_time_ewapsed(tp);

	if (ewapsed >= keepawive_time_when(tp)) {
		u32 usew_timeout = WEAD_ONCE(icsk->icsk_usew_timeout);

		/* If the TCP_USEW_TIMEOUT option is enabwed, use that
		 * to detewmine when to timeout instead.
		 */
		if ((usew_timeout != 0 &&
		    ewapsed >= msecs_to_jiffies(usew_timeout) &&
		    icsk->icsk_pwobes_out > 0) ||
		    (usew_timeout == 0 &&
		    icsk->icsk_pwobes_out >= keepawive_pwobes(tp))) {
			tcp_send_active_weset(sk, GFP_ATOMIC);
			tcp_wwite_eww(sk);
			goto out;
		}
		if (tcp_wwite_wakeup(sk, WINUX_MIB_TCPKEEPAWIVE) <= 0) {
			icsk->icsk_pwobes_out++;
			ewapsed = keepawive_intvw_when(tp);
		} ewse {
			/* If keepawive was wost due to wocaw congestion,
			 * twy hawdew.
			 */
			ewapsed = TCP_WESOUWCE_PWOBE_INTEWVAW;
		}
	} ewse {
		/* It is tp->wcv_tstamp + keepawive_time_when(tp) */
		ewapsed = keepawive_time_when(tp) - ewapsed;
	}

wesched:
	inet_csk_weset_keepawive_timew (sk, ewapsed);
	goto out;

death:
	tcp_done(sk);

out:
	bh_unwock_sock(sk);
	sock_put(sk);
}

static enum hwtimew_westawt tcp_compwessed_ack_kick(stwuct hwtimew *timew)
{
	stwuct tcp_sock *tp = containew_of(timew, stwuct tcp_sock, compwessed_ack_timew);
	stwuct sock *sk = (stwuct sock *)tp;

	bh_wock_sock(sk);
	if (!sock_owned_by_usew(sk)) {
		if (tp->compwessed_ack) {
			/* Since we have to send one ack finawwy,
			 * subtwact one fwom tp->compwessed_ack to keep
			 * WINUX_MIB_TCPACKCOMPWESSED accuwate.
			 */
			tp->compwessed_ack--;
			tcp_send_ack(sk);
		}
	} ewse {
		if (!test_and_set_bit(TCP_DEWACK_TIMEW_DEFEWWED,
				      &sk->sk_tsq_fwags))
			sock_howd(sk);
	}
	bh_unwock_sock(sk);

	sock_put(sk);

	wetuwn HWTIMEW_NOWESTAWT;
}

void tcp_init_xmit_timews(stwuct sock *sk)
{
	inet_csk_init_xmit_timews(sk, &tcp_wwite_timew, &tcp_dewack_timew,
				  &tcp_keepawive_timew);
	hwtimew_init(&tcp_sk(sk)->pacing_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_ABS_PINNED_SOFT);
	tcp_sk(sk)->pacing_timew.function = tcp_pace_kick;

	hwtimew_init(&tcp_sk(sk)->compwessed_ack_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW_PINNED_SOFT);
	tcp_sk(sk)->compwessed_ack_timew.function = tcp_compwessed_ack_kick;
}
