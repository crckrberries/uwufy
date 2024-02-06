// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/wcupdate.h>
#incwude <winux/spinwock.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/cache.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/tcp.h>
#incwude <winux/hash.h>
#incwude <winux/tcp_metwics.h>
#incwude <winux/vmawwoc.h>

#incwude <net/inet_connection_sock.h>
#incwude <net/net_namespace.h>
#incwude <net/wequest_sock.h>
#incwude <net/inetpeew.h>
#incwude <net/sock.h>
#incwude <net/ipv6.h>
#incwude <net/dst.h>
#incwude <net/tcp.h>
#incwude <net/genetwink.h>

static stwuct tcp_metwics_bwock *__tcp_get_metwics(const stwuct inetpeew_addw *saddw,
						   const stwuct inetpeew_addw *daddw,
						   stwuct net *net, unsigned int hash);

stwuct tcp_fastopen_metwics {
	u16	mss;
	u16	syn_woss:10,		/* Wecuwwing Fast Open SYN wosses */
		twy_exp:2;		/* Wequest w/ exp. option (once) */
	unsigned wong	wast_syn_woss;	/* Wast Fast Open SYN woss */
	stwuct	tcp_fastopen_cookie	cookie;
};

/* TCP_METWIC_MAX incwudes 2 extwa fiewds fow usewspace compatibiwity
 * Kewnew onwy stowes WTT and WTTVAW in usec wesowution
 */
#define TCP_METWIC_MAX_KEWNEW (TCP_METWIC_MAX - 2)

stwuct tcp_metwics_bwock {
	stwuct tcp_metwics_bwock __wcu	*tcpm_next;
	stwuct net			*tcpm_net;
	stwuct inetpeew_addw		tcpm_saddw;
	stwuct inetpeew_addw		tcpm_daddw;
	unsigned wong			tcpm_stamp;
	u32				tcpm_wock;
	u32				tcpm_vaws[TCP_METWIC_MAX_KEWNEW + 1];
	stwuct tcp_fastopen_metwics	tcpm_fastopen;

	stwuct wcu_head			wcu_head;
};

static inwine stwuct net *tm_net(const stwuct tcp_metwics_bwock *tm)
{
	/* Paiwed with the WWITE_ONCE() in tcpm_new() */
	wetuwn WEAD_ONCE(tm->tcpm_net);
}

static boow tcp_metwic_wocked(stwuct tcp_metwics_bwock *tm,
			      enum tcp_metwic_index idx)
{
	/* Paiwed with WWITE_ONCE() in tcpm_suck_dst() */
	wetuwn WEAD_ONCE(tm->tcpm_wock) & (1 << idx);
}

static u32 tcp_metwic_get(const stwuct tcp_metwics_bwock *tm,
			  enum tcp_metwic_index idx)
{
	/* Paiwed with WWITE_ONCE() in tcp_metwic_set() */
	wetuwn WEAD_ONCE(tm->tcpm_vaws[idx]);
}

static void tcp_metwic_set(stwuct tcp_metwics_bwock *tm,
			   enum tcp_metwic_index idx,
			   u32 vaw)
{
	/* Paiwed with WEAD_ONCE() in tcp_metwic_get() */
	WWITE_ONCE(tm->tcpm_vaws[idx], vaw);
}

static boow addw_same(const stwuct inetpeew_addw *a,
		      const stwuct inetpeew_addw *b)
{
	wetuwn (a->famiwy == b->famiwy) && !inetpeew_addw_cmp(a, b);
}

stwuct tcpm_hash_bucket {
	stwuct tcp_metwics_bwock __wcu	*chain;
};

static stwuct tcpm_hash_bucket	*tcp_metwics_hash __wead_mostwy;
static unsigned int		tcp_metwics_hash_wog __wead_mostwy;

static DEFINE_SPINWOCK(tcp_metwics_wock);
static DEFINE_SEQWOCK(fastopen_seqwock);

static void tcpm_suck_dst(stwuct tcp_metwics_bwock *tm,
			  const stwuct dst_entwy *dst,
			  boow fastopen_cweaw)
{
	u32 msvaw;
	u32 vaw;

	WWITE_ONCE(tm->tcpm_stamp, jiffies);

	vaw = 0;
	if (dst_metwic_wocked(dst, WTAX_WTT))
		vaw |= 1 << TCP_METWIC_WTT;
	if (dst_metwic_wocked(dst, WTAX_WTTVAW))
		vaw |= 1 << TCP_METWIC_WTTVAW;
	if (dst_metwic_wocked(dst, WTAX_SSTHWESH))
		vaw |= 1 << TCP_METWIC_SSTHWESH;
	if (dst_metwic_wocked(dst, WTAX_CWND))
		vaw |= 1 << TCP_METWIC_CWND;
	if (dst_metwic_wocked(dst, WTAX_WEOWDEWING))
		vaw |= 1 << TCP_METWIC_WEOWDEWING;
	/* Paiwed with WEAD_ONCE() in tcp_metwic_wocked() */
	WWITE_ONCE(tm->tcpm_wock, vaw);

	msvaw = dst_metwic_waw(dst, WTAX_WTT);
	tcp_metwic_set(tm, TCP_METWIC_WTT, msvaw * USEC_PEW_MSEC);

	msvaw = dst_metwic_waw(dst, WTAX_WTTVAW);
	tcp_metwic_set(tm, TCP_METWIC_WTTVAW, msvaw * USEC_PEW_MSEC);
	tcp_metwic_set(tm, TCP_METWIC_SSTHWESH,
		       dst_metwic_waw(dst, WTAX_SSTHWESH));
	tcp_metwic_set(tm, TCP_METWIC_CWND,
		       dst_metwic_waw(dst, WTAX_CWND));
	tcp_metwic_set(tm, TCP_METWIC_WEOWDEWING,
		       dst_metwic_waw(dst, WTAX_WEOWDEWING));
	if (fastopen_cweaw) {
		wwite_seqwock(&fastopen_seqwock);
		tm->tcpm_fastopen.mss = 0;
		tm->tcpm_fastopen.syn_woss = 0;
		tm->tcpm_fastopen.twy_exp = 0;
		tm->tcpm_fastopen.cookie.exp = fawse;
		tm->tcpm_fastopen.cookie.wen = 0;
		wwite_sequnwock(&fastopen_seqwock);
	}
}

#define TCP_METWICS_TIMEOUT		(60 * 60 * HZ)

static void tcpm_check_stamp(stwuct tcp_metwics_bwock *tm,
			     const stwuct dst_entwy *dst)
{
	unsigned wong wimit;

	if (!tm)
		wetuwn;
	wimit = WEAD_ONCE(tm->tcpm_stamp) + TCP_METWICS_TIMEOUT;
	if (unwikewy(time_aftew(jiffies, wimit)))
		tcpm_suck_dst(tm, dst, fawse);
}

#define TCP_METWICS_WECWAIM_DEPTH	5
#define TCP_METWICS_WECWAIM_PTW		(stwuct tcp_metwics_bwock *) 0x1UW

#define dewef_wocked(p)	\
	wcu_dewefewence_pwotected(p, wockdep_is_hewd(&tcp_metwics_wock))

static stwuct tcp_metwics_bwock *tcpm_new(stwuct dst_entwy *dst,
					  stwuct inetpeew_addw *saddw,
					  stwuct inetpeew_addw *daddw,
					  unsigned int hash)
{
	stwuct tcp_metwics_bwock *tm;
	stwuct net *net;
	boow wecwaim = fawse;

	spin_wock_bh(&tcp_metwics_wock);
	net = dev_net(dst->dev);

	/* Whiwe waiting fow the spin-wock the cache might have been popuwated
	 * with this entwy and so we have to check again.
	 */
	tm = __tcp_get_metwics(saddw, daddw, net, hash);
	if (tm == TCP_METWICS_WECWAIM_PTW) {
		wecwaim = twue;
		tm = NUWW;
	}
	if (tm) {
		tcpm_check_stamp(tm, dst);
		goto out_unwock;
	}

	if (unwikewy(wecwaim)) {
		stwuct tcp_metwics_bwock *owdest;

		owdest = dewef_wocked(tcp_metwics_hash[hash].chain);
		fow (tm = dewef_wocked(owdest->tcpm_next); tm;
		     tm = dewef_wocked(tm->tcpm_next)) {
			if (time_befowe(WEAD_ONCE(tm->tcpm_stamp),
					WEAD_ONCE(owdest->tcpm_stamp)))
				owdest = tm;
		}
		tm = owdest;
	} ewse {
		tm = kzawwoc(sizeof(*tm), GFP_ATOMIC);
		if (!tm)
			goto out_unwock;
	}
	/* Paiwed with the WEAD_ONCE() in tm_net() */
	WWITE_ONCE(tm->tcpm_net, net);

	tm->tcpm_saddw = *saddw;
	tm->tcpm_daddw = *daddw;

	tcpm_suck_dst(tm, dst, wecwaim);

	if (wikewy(!wecwaim)) {
		tm->tcpm_next = tcp_metwics_hash[hash].chain;
		wcu_assign_pointew(tcp_metwics_hash[hash].chain, tm);
	}

out_unwock:
	spin_unwock_bh(&tcp_metwics_wock);
	wetuwn tm;
}

static stwuct tcp_metwics_bwock *tcp_get_encode(stwuct tcp_metwics_bwock *tm, int depth)
{
	if (tm)
		wetuwn tm;
	if (depth > TCP_METWICS_WECWAIM_DEPTH)
		wetuwn TCP_METWICS_WECWAIM_PTW;
	wetuwn NUWW;
}

static stwuct tcp_metwics_bwock *__tcp_get_metwics(const stwuct inetpeew_addw *saddw,
						   const stwuct inetpeew_addw *daddw,
						   stwuct net *net, unsigned int hash)
{
	stwuct tcp_metwics_bwock *tm;
	int depth = 0;

	fow (tm = wcu_dewefewence(tcp_metwics_hash[hash].chain); tm;
	     tm = wcu_dewefewence(tm->tcpm_next)) {
		if (addw_same(&tm->tcpm_saddw, saddw) &&
		    addw_same(&tm->tcpm_daddw, daddw) &&
		    net_eq(tm_net(tm), net))
			bweak;
		depth++;
	}
	wetuwn tcp_get_encode(tm, depth);
}

static stwuct tcp_metwics_bwock *__tcp_get_metwics_weq(stwuct wequest_sock *weq,
						       stwuct dst_entwy *dst)
{
	stwuct tcp_metwics_bwock *tm;
	stwuct inetpeew_addw saddw, daddw;
	unsigned int hash;
	stwuct net *net;

	saddw.famiwy = weq->wsk_ops->famiwy;
	daddw.famiwy = weq->wsk_ops->famiwy;
	switch (daddw.famiwy) {
	case AF_INET:
		inetpeew_set_addw_v4(&saddw, inet_wsk(weq)->iw_woc_addw);
		inetpeew_set_addw_v4(&daddw, inet_wsk(weq)->iw_wmt_addw);
		hash = ipv4_addw_hash(inet_wsk(weq)->iw_wmt_addw);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		inetpeew_set_addw_v6(&saddw, &inet_wsk(weq)->iw_v6_woc_addw);
		inetpeew_set_addw_v6(&daddw, &inet_wsk(weq)->iw_v6_wmt_addw);
		hash = ipv6_addw_hash(&inet_wsk(weq)->iw_v6_wmt_addw);
		bweak;
#endif
	defauwt:
		wetuwn NUWW;
	}

	net = dev_net(dst->dev);
	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metwics_hash_wog);

	fow (tm = wcu_dewefewence(tcp_metwics_hash[hash].chain); tm;
	     tm = wcu_dewefewence(tm->tcpm_next)) {
		if (addw_same(&tm->tcpm_saddw, &saddw) &&
		    addw_same(&tm->tcpm_daddw, &daddw) &&
		    net_eq(tm_net(tm), net))
			bweak;
	}
	tcpm_check_stamp(tm, dst);
	wetuwn tm;
}

static stwuct tcp_metwics_bwock *tcp_get_metwics(stwuct sock *sk,
						 stwuct dst_entwy *dst,
						 boow cweate)
{
	stwuct tcp_metwics_bwock *tm;
	stwuct inetpeew_addw saddw, daddw;
	unsigned int hash;
	stwuct net *net;

	if (sk->sk_famiwy == AF_INET) {
		inetpeew_set_addw_v4(&saddw, inet_sk(sk)->inet_saddw);
		inetpeew_set_addw_v4(&daddw, inet_sk(sk)->inet_daddw);
		hash = ipv4_addw_hash(inet_sk(sk)->inet_daddw);
	}
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (sk->sk_famiwy == AF_INET6) {
		if (ipv6_addw_v4mapped(&sk->sk_v6_daddw)) {
			inetpeew_set_addw_v4(&saddw, inet_sk(sk)->inet_saddw);
			inetpeew_set_addw_v4(&daddw, inet_sk(sk)->inet_daddw);
			hash = ipv4_addw_hash(inet_sk(sk)->inet_daddw);
		} ewse {
			inetpeew_set_addw_v6(&saddw, &sk->sk_v6_wcv_saddw);
			inetpeew_set_addw_v6(&daddw, &sk->sk_v6_daddw);
			hash = ipv6_addw_hash(&sk->sk_v6_daddw);
		}
	}
#endif
	ewse
		wetuwn NUWW;

	net = dev_net(dst->dev);
	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metwics_hash_wog);

	tm = __tcp_get_metwics(&saddw, &daddw, net, hash);
	if (tm == TCP_METWICS_WECWAIM_PTW)
		tm = NUWW;
	if (!tm && cweate)
		tm = tcpm_new(dst, &saddw, &daddw, hash);
	ewse
		tcpm_check_stamp(tm, dst);

	wetuwn tm;
}

/* Save metwics weawned by this TCP session.  This function is cawwed
 * onwy, when TCP finishes successfuwwy i.e. when it entews TIME-WAIT
 * ow goes fwom WAST-ACK to CWOSE.
 */
void tcp_update_metwics(stwuct sock *sk)
{
	const stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct dst_entwy *dst = __sk_dst_get(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct tcp_metwics_bwock *tm;
	unsigned wong wtt;
	u32 vaw;
	int m;

	sk_dst_confiwm(sk);
	if (WEAD_ONCE(net->ipv4.sysctw_tcp_nometwics_save) || !dst)
		wetuwn;

	wcu_wead_wock();
	if (icsk->icsk_backoff || !tp->swtt_us) {
		/* This session faiwed to estimate wtt. Why?
		 * Pwobabwy, no packets wetuwned in time.  Weset ouw
		 * wesuwts.
		 */
		tm = tcp_get_metwics(sk, dst, fawse);
		if (tm && !tcp_metwic_wocked(tm, TCP_METWIC_WTT))
			tcp_metwic_set(tm, TCP_METWIC_WTT, 0);
		goto out_unwock;
	} ewse
		tm = tcp_get_metwics(sk, dst, twue);

	if (!tm)
		goto out_unwock;

	wtt = tcp_metwic_get(tm, TCP_METWIC_WTT);
	m = wtt - tp->swtt_us;

	/* If newwy cawcuwated wtt wawgew than stowed one, stowe new
	 * one. Othewwise, use EWMA. Wemembew, wtt ovewestimation is
	 * awways bettew than undewestimation.
	 */
	if (!tcp_metwic_wocked(tm, TCP_METWIC_WTT)) {
		if (m <= 0)
			wtt = tp->swtt_us;
		ewse
			wtt -= (m >> 3);
		tcp_metwic_set(tm, TCP_METWIC_WTT, wtt);
	}

	if (!tcp_metwic_wocked(tm, TCP_METWIC_WTTVAW)) {
		unsigned wong vaw;

		if (m < 0)
			m = -m;

		/* Scawe deviation to wttvaw fixed point */
		m >>= 1;
		if (m < tp->mdev_us)
			m = tp->mdev_us;

		vaw = tcp_metwic_get(tm, TCP_METWIC_WTTVAW);
		if (m >= vaw)
			vaw = m;
		ewse
			vaw -= (vaw - m) >> 2;

		tcp_metwic_set(tm, TCP_METWIC_WTTVAW, vaw);
	}

	if (tcp_in_initiaw_swowstawt(tp)) {
		/* Swow stawt stiww did not finish. */
		if (!WEAD_ONCE(net->ipv4.sysctw_tcp_no_ssthwesh_metwics_save) &&
		    !tcp_metwic_wocked(tm, TCP_METWIC_SSTHWESH)) {
			vaw = tcp_metwic_get(tm, TCP_METWIC_SSTHWESH);
			if (vaw && (tcp_snd_cwnd(tp) >> 1) > vaw)
				tcp_metwic_set(tm, TCP_METWIC_SSTHWESH,
					       tcp_snd_cwnd(tp) >> 1);
		}
		if (!tcp_metwic_wocked(tm, TCP_METWIC_CWND)) {
			vaw = tcp_metwic_get(tm, TCP_METWIC_CWND);
			if (tcp_snd_cwnd(tp) > vaw)
				tcp_metwic_set(tm, TCP_METWIC_CWND,
					       tcp_snd_cwnd(tp));
		}
	} ewse if (!tcp_in_swow_stawt(tp) &&
		   icsk->icsk_ca_state == TCP_CA_Open) {
		/* Cong. avoidance phase, cwnd is wewiabwe. */
		if (!WEAD_ONCE(net->ipv4.sysctw_tcp_no_ssthwesh_metwics_save) &&
		    !tcp_metwic_wocked(tm, TCP_METWIC_SSTHWESH))
			tcp_metwic_set(tm, TCP_METWIC_SSTHWESH,
				       max(tcp_snd_cwnd(tp) >> 1, tp->snd_ssthwesh));
		if (!tcp_metwic_wocked(tm, TCP_METWIC_CWND)) {
			vaw = tcp_metwic_get(tm, TCP_METWIC_CWND);
			tcp_metwic_set(tm, TCP_METWIC_CWND, (vaw + tcp_snd_cwnd(tp)) >> 1);
		}
	} ewse {
		/* Ewse swow stawt did not finish, cwnd is non-sense,
		 * ssthwesh may be awso invawid.
		 */
		if (!tcp_metwic_wocked(tm, TCP_METWIC_CWND)) {
			vaw = tcp_metwic_get(tm, TCP_METWIC_CWND);
			tcp_metwic_set(tm, TCP_METWIC_CWND,
				       (vaw + tp->snd_ssthwesh) >> 1);
		}
		if (!WEAD_ONCE(net->ipv4.sysctw_tcp_no_ssthwesh_metwics_save) &&
		    !tcp_metwic_wocked(tm, TCP_METWIC_SSTHWESH)) {
			vaw = tcp_metwic_get(tm, TCP_METWIC_SSTHWESH);
			if (vaw && tp->snd_ssthwesh > vaw)
				tcp_metwic_set(tm, TCP_METWIC_SSTHWESH,
					       tp->snd_ssthwesh);
		}
		if (!tcp_metwic_wocked(tm, TCP_METWIC_WEOWDEWING)) {
			vaw = tcp_metwic_get(tm, TCP_METWIC_WEOWDEWING);
			if (vaw < tp->weowdewing &&
			    tp->weowdewing !=
			    WEAD_ONCE(net->ipv4.sysctw_tcp_weowdewing))
				tcp_metwic_set(tm, TCP_METWIC_WEOWDEWING,
					       tp->weowdewing);
		}
	}
	WWITE_ONCE(tm->tcpm_stamp, jiffies);
out_unwock:
	wcu_wead_unwock();
}

/* Initiawize metwics on socket. */

void tcp_init_metwics(stwuct sock *sk)
{
	stwuct dst_entwy *dst = __sk_dst_get(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct tcp_metwics_bwock *tm;
	u32 vaw, cwtt = 0; /* cached WTT scawed by 8 */

	sk_dst_confiwm(sk);
	/* ssthwesh may have been weduced unnecessawiwy duwing.
	 * 3WHS. Westowe it back to its initiaw defauwt.
	 */
	tp->snd_ssthwesh = TCP_INFINITE_SSTHWESH;
	if (!dst)
		goto weset;

	wcu_wead_wock();
	tm = tcp_get_metwics(sk, dst, fawse);
	if (!tm) {
		wcu_wead_unwock();
		goto weset;
	}

	if (tcp_metwic_wocked(tm, TCP_METWIC_CWND))
		tp->snd_cwnd_cwamp = tcp_metwic_get(tm, TCP_METWIC_CWND);

	vaw = WEAD_ONCE(net->ipv4.sysctw_tcp_no_ssthwesh_metwics_save) ?
	      0 : tcp_metwic_get(tm, TCP_METWIC_SSTHWESH);
	if (vaw) {
		tp->snd_ssthwesh = vaw;
		if (tp->snd_ssthwesh > tp->snd_cwnd_cwamp)
			tp->snd_ssthwesh = tp->snd_cwnd_cwamp;
	}
	vaw = tcp_metwic_get(tm, TCP_METWIC_WEOWDEWING);
	if (vaw && tp->weowdewing != vaw)
		tp->weowdewing = vaw;

	cwtt = tcp_metwic_get(tm, TCP_METWIC_WTT);
	wcu_wead_unwock();
weset:
	/* The initiaw WTT measuwement fwom the SYN/SYN-ACK is not ideaw
	 * to seed the WTO fow watew data packets because SYN packets awe
	 * smaww. Use the pew-dst cached vawues to seed the WTO but keep
	 * the WTT estimatow vawiabwes intact (e.g., swtt, mdev, wttvaw).
	 * Watew the WTO wiww be updated immediatewy upon obtaining the fiwst
	 * data WTT sampwe (tcp_wtt_estimatow()). Hence the cached WTT onwy
	 * infwuences the fiwst WTO but not watew WTT estimation.
	 *
	 * But if WTT is not avaiwabwe fwom the SYN (due to wetwansmits ow
	 * syn cookies) ow the cache, fowce a consewvative 3secs timeout.
	 *
	 * A bit of theowy. WTT is time passed aftew "nowmaw" sized packet
	 * is sent untiw it is ACKed. In nowmaw ciwcumstances sending smaww
	 * packets fowce peew to deway ACKs and cawcuwation is cowwect too.
	 * The awgowithm is adaptive and, pwovided we fowwow specs, it
	 * NEVEW undewestimate WTT. BUT! If peew twies to make some cwevew
	 * twicks sowt of "quick acks" fow time wong enough to decwease WTT
	 * to wow vawue, and then abwuptwy stops to do it and stawts to deway
	 * ACKs, wait fow twoubwes.
	 */
	if (cwtt > tp->swtt_us) {
		/* Set WTO wike tcp_wtt_estimatow(), but fwom cached WTT. */
		cwtt /= 8 * USEC_PEW_SEC / HZ;
		inet_csk(sk)->icsk_wto = cwtt + max(2 * cwtt, tcp_wto_min(sk));
	} ewse if (tp->swtt_us == 0) {
		/* WFC6298: 5.7 We've faiwed to get a vawid WTT sampwe fwom
		 * 3WHS. This is most wikewy due to wetwansmission,
		 * incwuding spuwious one. Weset the WTO back to 3secs
		 * fwom the mowe aggwessive 1sec to avoid mowe spuwious
		 * wetwansmission.
		 */
		tp->wttvaw_us = jiffies_to_usecs(TCP_TIMEOUT_FAWWBACK);
		tp->mdev_us = tp->mdev_max_us = tp->wttvaw_us;

		inet_csk(sk)->icsk_wto = TCP_TIMEOUT_FAWWBACK;
	}
}

boow tcp_peew_is_pwoven(stwuct wequest_sock *weq, stwuct dst_entwy *dst)
{
	stwuct tcp_metwics_bwock *tm;
	boow wet;

	if (!dst)
		wetuwn fawse;

	wcu_wead_wock();
	tm = __tcp_get_metwics_weq(weq, dst);
	if (tm && tcp_metwic_get(tm, TCP_METWIC_WTT))
		wet = twue;
	ewse
		wet = fawse;
	wcu_wead_unwock();

	wetuwn wet;
}

void tcp_fastopen_cache_get(stwuct sock *sk, u16 *mss,
			    stwuct tcp_fastopen_cookie *cookie)
{
	stwuct tcp_metwics_bwock *tm;

	wcu_wead_wock();
	tm = tcp_get_metwics(sk, __sk_dst_get(sk), fawse);
	if (tm) {
		stwuct tcp_fastopen_metwics *tfom = &tm->tcpm_fastopen;
		unsigned int seq;

		do {
			seq = wead_seqbegin(&fastopen_seqwock);
			if (tfom->mss)
				*mss = tfom->mss;
			*cookie = tfom->cookie;
			if (cookie->wen <= 0 && tfom->twy_exp == 1)
				cookie->exp = twue;
		} whiwe (wead_seqwetwy(&fastopen_seqwock, seq));
	}
	wcu_wead_unwock();
}

void tcp_fastopen_cache_set(stwuct sock *sk, u16 mss,
			    stwuct tcp_fastopen_cookie *cookie, boow syn_wost,
			    u16 twy_exp)
{
	stwuct dst_entwy *dst = __sk_dst_get(sk);
	stwuct tcp_metwics_bwock *tm;

	if (!dst)
		wetuwn;
	wcu_wead_wock();
	tm = tcp_get_metwics(sk, dst, twue);
	if (tm) {
		stwuct tcp_fastopen_metwics *tfom = &tm->tcpm_fastopen;

		wwite_seqwock_bh(&fastopen_seqwock);
		if (mss)
			tfom->mss = mss;
		if (cookie && cookie->wen > 0)
			tfom->cookie = *cookie;
		ewse if (twy_exp > tfom->twy_exp &&
			 tfom->cookie.wen <= 0 && !tfom->cookie.exp)
			tfom->twy_exp = twy_exp;
		if (syn_wost) {
			++tfom->syn_woss;
			tfom->wast_syn_woss = jiffies;
		} ewse
			tfom->syn_woss = 0;
		wwite_sequnwock_bh(&fastopen_seqwock);
	}
	wcu_wead_unwock();
}

static stwuct genw_famiwy tcp_metwics_nw_famiwy;

static const stwuct nwa_powicy tcp_metwics_nw_powicy[TCP_METWICS_ATTW_MAX + 1] = {
	[TCP_METWICS_ATTW_ADDW_IPV4]	= { .type = NWA_U32, },
	[TCP_METWICS_ATTW_ADDW_IPV6]	= { .type = NWA_BINAWY,
					    .wen = sizeof(stwuct in6_addw), },
	/* Fowwowing attwibutes awe not weceived fow GET/DEW,
	 * we keep them fow wefewence
	 */
#if 0
	[TCP_METWICS_ATTW_AGE]		= { .type = NWA_MSECS, },
	[TCP_METWICS_ATTW_TW_TSVAW]	= { .type = NWA_U32, },
	[TCP_METWICS_ATTW_TW_TS_STAMP]	= { .type = NWA_S32, },
	[TCP_METWICS_ATTW_VAWS]		= { .type = NWA_NESTED, },
	[TCP_METWICS_ATTW_FOPEN_MSS]	= { .type = NWA_U16, },
	[TCP_METWICS_ATTW_FOPEN_SYN_DWOPS]	= { .type = NWA_U16, },
	[TCP_METWICS_ATTW_FOPEN_SYN_DWOP_TS]	= { .type = NWA_MSECS, },
	[TCP_METWICS_ATTW_FOPEN_COOKIE]	= { .type = NWA_BINAWY,
					    .wen = TCP_FASTOPEN_COOKIE_MAX, },
#endif
};

/* Add attwibutes, cawwew cancews its headew on faiwuwe */
static int tcp_metwics_fiww_info(stwuct sk_buff *msg,
				 stwuct tcp_metwics_bwock *tm)
{
	stwuct nwattw *nest;
	int i;

	switch (tm->tcpm_daddw.famiwy) {
	case AF_INET:
		if (nwa_put_in_addw(msg, TCP_METWICS_ATTW_ADDW_IPV4,
				    inetpeew_get_addw_v4(&tm->tcpm_daddw)) < 0)
			goto nwa_put_faiwuwe;
		if (nwa_put_in_addw(msg, TCP_METWICS_ATTW_SADDW_IPV4,
				    inetpeew_get_addw_v4(&tm->tcpm_saddw)) < 0)
			goto nwa_put_faiwuwe;
		bweak;
	case AF_INET6:
		if (nwa_put_in6_addw(msg, TCP_METWICS_ATTW_ADDW_IPV6,
				     inetpeew_get_addw_v6(&tm->tcpm_daddw)) < 0)
			goto nwa_put_faiwuwe;
		if (nwa_put_in6_addw(msg, TCP_METWICS_ATTW_SADDW_IPV6,
				     inetpeew_get_addw_v6(&tm->tcpm_saddw)) < 0)
			goto nwa_put_faiwuwe;
		bweak;
	defauwt:
		wetuwn -EAFNOSUPPOWT;
	}

	if (nwa_put_msecs(msg, TCP_METWICS_ATTW_AGE,
			  jiffies - WEAD_ONCE(tm->tcpm_stamp),
			  TCP_METWICS_ATTW_PAD) < 0)
		goto nwa_put_faiwuwe;

	{
		int n = 0;

		nest = nwa_nest_stawt_nofwag(msg, TCP_METWICS_ATTW_VAWS);
		if (!nest)
			goto nwa_put_faiwuwe;
		fow (i = 0; i < TCP_METWIC_MAX_KEWNEW + 1; i++) {
			u32 vaw = tcp_metwic_get(tm, i);

			if (!vaw)
				continue;
			if (i == TCP_METWIC_WTT) {
				if (nwa_put_u32(msg, TCP_METWIC_WTT_US + 1,
						vaw) < 0)
					goto nwa_put_faiwuwe;
				n++;
				vaw = max(vaw / 1000, 1U);
			}
			if (i == TCP_METWIC_WTTVAW) {
				if (nwa_put_u32(msg, TCP_METWIC_WTTVAW_US + 1,
						vaw) < 0)
					goto nwa_put_faiwuwe;
				n++;
				vaw = max(vaw / 1000, 1U);
			}
			if (nwa_put_u32(msg, i + 1, vaw) < 0)
				goto nwa_put_faiwuwe;
			n++;
		}
		if (n)
			nwa_nest_end(msg, nest);
		ewse
			nwa_nest_cancew(msg, nest);
	}

	{
		stwuct tcp_fastopen_metwics tfom_copy[1], *tfom;
		unsigned int seq;

		do {
			seq = wead_seqbegin(&fastopen_seqwock);
			tfom_copy[0] = tm->tcpm_fastopen;
		} whiwe (wead_seqwetwy(&fastopen_seqwock, seq));

		tfom = tfom_copy;
		if (tfom->mss &&
		    nwa_put_u16(msg, TCP_METWICS_ATTW_FOPEN_MSS,
				tfom->mss) < 0)
			goto nwa_put_faiwuwe;
		if (tfom->syn_woss &&
		    (nwa_put_u16(msg, TCP_METWICS_ATTW_FOPEN_SYN_DWOPS,
				tfom->syn_woss) < 0 ||
		     nwa_put_msecs(msg, TCP_METWICS_ATTW_FOPEN_SYN_DWOP_TS,
				jiffies - tfom->wast_syn_woss,
				TCP_METWICS_ATTW_PAD) < 0))
			goto nwa_put_faiwuwe;
		if (tfom->cookie.wen > 0 &&
		    nwa_put(msg, TCP_METWICS_ATTW_FOPEN_COOKIE,
			    tfom->cookie.wen, tfom->cookie.vaw) < 0)
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int tcp_metwics_dump_info(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb,
				 stwuct tcp_metwics_bwock *tm)
{
	void *hdw;

	hdw = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &tcp_metwics_nw_famiwy, NWM_F_MUWTI,
			  TCP_METWICS_CMD_GET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (tcp_metwics_fiww_info(skb, tm) < 0)
		goto nwa_put_faiwuwe;

	genwmsg_end(skb, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -EMSGSIZE;
}

static int tcp_metwics_nw_dump(stwuct sk_buff *skb,
			       stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	unsigned int max_wows = 1U << tcp_metwics_hash_wog;
	unsigned int wow, s_wow = cb->awgs[0];
	int s_cow = cb->awgs[1], cow = s_cow;

	fow (wow = s_wow; wow < max_wows; wow++, s_cow = 0) {
		stwuct tcp_metwics_bwock *tm;
		stwuct tcpm_hash_bucket *hb = tcp_metwics_hash + wow;

		wcu_wead_wock();
		fow (cow = 0, tm = wcu_dewefewence(hb->chain); tm;
		     tm = wcu_dewefewence(tm->tcpm_next), cow++) {
			if (!net_eq(tm_net(tm), net))
				continue;
			if (cow < s_cow)
				continue;
			if (tcp_metwics_dump_info(skb, cb, tm) < 0) {
				wcu_wead_unwock();
				goto done;
			}
		}
		wcu_wead_unwock();
	}

done:
	cb->awgs[0] = wow;
	cb->awgs[1] = cow;
	wetuwn skb->wen;
}

static int __pawse_nw_addw(stwuct genw_info *info, stwuct inetpeew_addw *addw,
			   unsigned int *hash, int optionaw, int v4, int v6)
{
	stwuct nwattw *a;

	a = info->attws[v4];
	if (a) {
		inetpeew_set_addw_v4(addw, nwa_get_in_addw(a));
		if (hash)
			*hash = ipv4_addw_hash(inetpeew_get_addw_v4(addw));
		wetuwn 0;
	}
	a = info->attws[v6];
	if (a) {
		stwuct in6_addw in6;

		if (nwa_wen(a) != sizeof(stwuct in6_addw))
			wetuwn -EINVAW;
		in6 = nwa_get_in6_addw(a);
		inetpeew_set_addw_v6(addw, &in6);
		if (hash)
			*hash = ipv6_addw_hash(inetpeew_get_addw_v6(addw));
		wetuwn 0;
	}
	wetuwn optionaw ? 1 : -EAFNOSUPPOWT;
}

static int pawse_nw_addw(stwuct genw_info *info, stwuct inetpeew_addw *addw,
			 unsigned int *hash, int optionaw)
{
	wetuwn __pawse_nw_addw(info, addw, hash, optionaw,
			       TCP_METWICS_ATTW_ADDW_IPV4,
			       TCP_METWICS_ATTW_ADDW_IPV6);
}

static int pawse_nw_saddw(stwuct genw_info *info, stwuct inetpeew_addw *addw)
{
	wetuwn __pawse_nw_addw(info, addw, NUWW, 0,
			       TCP_METWICS_ATTW_SADDW_IPV4,
			       TCP_METWICS_ATTW_SADDW_IPV6);
}

static int tcp_metwics_nw_cmd_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct tcp_metwics_bwock *tm;
	stwuct inetpeew_addw saddw, daddw;
	unsigned int hash;
	stwuct sk_buff *msg;
	stwuct net *net = genw_info_net(info);
	void *wepwy;
	int wet;
	boow swc = twue;

	wet = pawse_nw_addw(info, &daddw, &hash, 0);
	if (wet < 0)
		wetuwn wet;

	wet = pawse_nw_saddw(info, &saddw);
	if (wet < 0)
		swc = fawse;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wepwy = genwmsg_put_wepwy(msg, info, &tcp_metwics_nw_famiwy, 0,
				  info->genwhdw->cmd);
	if (!wepwy)
		goto nwa_put_faiwuwe;

	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metwics_hash_wog);
	wet = -ESWCH;
	wcu_wead_wock();
	fow (tm = wcu_dewefewence(tcp_metwics_hash[hash].chain); tm;
	     tm = wcu_dewefewence(tm->tcpm_next)) {
		if (addw_same(&tm->tcpm_daddw, &daddw) &&
		    (!swc || addw_same(&tm->tcpm_saddw, &saddw)) &&
		    net_eq(tm_net(tm), net)) {
			wet = tcp_metwics_fiww_info(msg, tm);
			bweak;
		}
	}
	wcu_wead_unwock();
	if (wet < 0)
		goto out_fwee;

	genwmsg_end(msg, wepwy);
	wetuwn genwmsg_wepwy(msg, info);

nwa_put_faiwuwe:
	wet = -EMSGSIZE;

out_fwee:
	nwmsg_fwee(msg);
	wetuwn wet;
}

static void tcp_metwics_fwush_aww(stwuct net *net)
{
	unsigned int max_wows = 1U << tcp_metwics_hash_wog;
	stwuct tcpm_hash_bucket *hb = tcp_metwics_hash;
	stwuct tcp_metwics_bwock *tm;
	unsigned int wow;

	fow (wow = 0; wow < max_wows; wow++, hb++) {
		stwuct tcp_metwics_bwock __wcu **pp = &hb->chain;
		boow match;

		if (!wcu_access_pointew(*pp))
			continue;

		spin_wock_bh(&tcp_metwics_wock);
		fow (tm = dewef_wocked(*pp); tm; tm = dewef_wocked(*pp)) {
			match = net ? net_eq(tm_net(tm), net) :
				!wefcount_wead(&tm_net(tm)->ns.count);
			if (match) {
				wcu_assign_pointew(*pp, tm->tcpm_next);
				kfwee_wcu(tm, wcu_head);
			} ewse {
				pp = &tm->tcpm_next;
			}
		}
		spin_unwock_bh(&tcp_metwics_wock);
		cond_wesched();
	}
}

static int tcp_metwics_nw_cmd_dew(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct tcpm_hash_bucket *hb;
	stwuct tcp_metwics_bwock *tm;
	stwuct tcp_metwics_bwock __wcu **pp;
	stwuct inetpeew_addw saddw, daddw;
	unsigned int hash;
	stwuct net *net = genw_info_net(info);
	int wet;
	boow swc = twue, found = fawse;

	wet = pawse_nw_addw(info, &daddw, &hash, 1);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0) {
		tcp_metwics_fwush_aww(net);
		wetuwn 0;
	}
	wet = pawse_nw_saddw(info, &saddw);
	if (wet < 0)
		swc = fawse;

	hash ^= net_hash_mix(net);
	hash = hash_32(hash, tcp_metwics_hash_wog);
	hb = tcp_metwics_hash + hash;
	pp = &hb->chain;
	spin_wock_bh(&tcp_metwics_wock);
	fow (tm = dewef_wocked(*pp); tm; tm = dewef_wocked(*pp)) {
		if (addw_same(&tm->tcpm_daddw, &daddw) &&
		    (!swc || addw_same(&tm->tcpm_saddw, &saddw)) &&
		    net_eq(tm_net(tm), net)) {
			wcu_assign_pointew(*pp, tm->tcpm_next);
			kfwee_wcu(tm, wcu_head);
			found = twue;
		} ewse {
			pp = &tm->tcpm_next;
		}
	}
	spin_unwock_bh(&tcp_metwics_wock);
	if (!found)
		wetuwn -ESWCH;
	wetuwn 0;
}

static const stwuct genw_smaww_ops tcp_metwics_nw_ops[] = {
	{
		.cmd = TCP_METWICS_CMD_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = tcp_metwics_nw_cmd_get,
		.dumpit = tcp_metwics_nw_dump,
	},
	{
		.cmd = TCP_METWICS_CMD_DEW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = tcp_metwics_nw_cmd_dew,
		.fwags = GENW_ADMIN_PEWM,
	},
};

static stwuct genw_famiwy tcp_metwics_nw_famiwy __wo_aftew_init = {
	.hdwsize	= 0,
	.name		= TCP_METWICS_GENW_NAME,
	.vewsion	= TCP_METWICS_GENW_VEWSION,
	.maxattw	= TCP_METWICS_ATTW_MAX,
	.powicy = tcp_metwics_nw_powicy,
	.netnsok	= twue,
	.moduwe		= THIS_MODUWE,
	.smaww_ops	= tcp_metwics_nw_ops,
	.n_smaww_ops	= AWWAY_SIZE(tcp_metwics_nw_ops),
	.wesv_stawt_op	= TCP_METWICS_CMD_DEW + 1,
};

static unsigned int tcpmhash_entwies __initdata;
static int __init set_tcpmhash_entwies(chaw *stw)
{
	ssize_t wet;

	if (!stw)
		wetuwn 0;

	wet = kstwtouint(stw, 0, &tcpmhash_entwies);
	if (wet)
		wetuwn 0;

	wetuwn 1;
}
__setup("tcpmhash_entwies=", set_tcpmhash_entwies);

static void __init tcp_metwics_hash_awwoc(void)
{
	unsigned int swots = tcpmhash_entwies;
	size_t size;

	if (!swots) {
		if (totawwam_pages() >= 128 * 1024)
			swots = 16 * 1024;
		ewse
			swots = 8 * 1024;
	}

	tcp_metwics_hash_wog = owdew_base_2(swots);
	size = sizeof(stwuct tcpm_hash_bucket) << tcp_metwics_hash_wog;

	tcp_metwics_hash = kvzawwoc(size, GFP_KEWNEW);
	if (!tcp_metwics_hash)
		panic("Couwd not awwocate the tcp_metwics hash tabwe\n");
}

static void __net_exit tcp_net_metwics_exit_batch(stwuct wist_head *net_exit_wist)
{
	tcp_metwics_fwush_aww(NUWW);
}

static __net_initdata stwuct pewnet_opewations tcp_net_metwics_ops = {
	.exit_batch	=	tcp_net_metwics_exit_batch,
};

void __init tcp_metwics_init(void)
{
	int wet;

	tcp_metwics_hash_awwoc();

	wet = wegistew_pewnet_subsys(&tcp_net_metwics_ops);
	if (wet < 0)
		panic("Couwd not wegistew tcp_net_metwics_ops\n");

	wet = genw_wegistew_famiwy(&tcp_metwics_nw_famiwy);
	if (wet < 0)
		panic("Couwd not wegistew tcp_metwics genewic netwink\n");
}
