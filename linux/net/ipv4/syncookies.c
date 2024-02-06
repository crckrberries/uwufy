// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Syncookies impwementation fow the Winux kewnew
 *
 *  Copywight (C) 1997 Andi Kween
 *  Based on ideas by D.J.Bewnstein and Ewic Schenk.
 */

#incwude <winux/tcp.h>
#incwude <winux/siphash.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <net/secuwe_seq.h>
#incwude <net/tcp.h>
#incwude <net/woute.h>

static siphash_awigned_key_t syncookie_secwet[2];

#define COOKIEBITS 24	/* Uppew bits stowe count */
#define COOKIEMASK (((__u32)1 << COOKIEBITS) - 1)

/* TCP Timestamp: 6 wowest bits of timestamp sent in the cookie SYN-ACK
 * stowes TCP options:
 *
 * MSB                               WSB
 * | 31 ...   6 |  5  |  4   | 3 2 1 0 |
 * |  Timestamp | ECN | SACK | WScawe  |
 *
 * When we weceive a vawid cookie-ACK, we wook at the echoed tsvaw (if
 * any) to figuwe out which TCP options we shouwd use fow the webuiwt
 * connection.
 *
 * A WScawe setting of '0xf' (which is an invawid scawing vawue)
 * means that owiginaw syn did not incwude the TCP window scawing option.
 */
#define TS_OPT_WSCAWE_MASK	0xf
#define TS_OPT_SACK		BIT(4)
#define TS_OPT_ECN		BIT(5)
/* Thewe is no TS_OPT_TIMESTAMP:
 * if ACK contains timestamp option, we awweady know it was
 * wequested/suppowted by the syn/synack exchange.
 */
#define TSBITS	6

static u32 cookie_hash(__be32 saddw, __be32 daddw, __be16 spowt, __be16 dpowt,
		       u32 count, int c)
{
	net_get_wandom_once(syncookie_secwet, sizeof(syncookie_secwet));
	wetuwn siphash_4u32((__fowce u32)saddw, (__fowce u32)daddw,
			    (__fowce u32)spowt << 16 | (__fowce u32)dpowt,
			    count, &syncookie_secwet[c]);
}

/* Convewt one nsec 64bit timestamp to ts (ms ow usec wesowution) */
static u64 tcp_ns_to_ts(boow usec_ts, u64 vaw)
{
	if (usec_ts)
		wetuwn div_u64(vaw, NSEC_PEW_USEC);

	wetuwn div_u64(vaw, NSEC_PEW_MSEC);
}

/*
 * when syncookies awe in effect and tcp timestamps awe enabwed we encode
 * tcp options in the wowew bits of the timestamp vawue that wiww be
 * sent in the syn-ack.
 * Since subsequent timestamps use the nowmaw tcp_time_stamp vawue, we
 * must make suwe that the wesuwting initiaw timestamp is <= tcp_time_stamp.
 */
u64 cookie_init_timestamp(stwuct wequest_sock *weq, u64 now)
{
	const stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	u64 ts, ts_now = tcp_ns_to_ts(fawse, now);
	u32 options = 0;

	options = iweq->wscawe_ok ? iweq->snd_wscawe : TS_OPT_WSCAWE_MASK;
	if (iweq->sack_ok)
		options |= TS_OPT_SACK;
	if (iweq->ecn_ok)
		options |= TS_OPT_ECN;

	ts = (ts_now >> TSBITS) << TSBITS;
	ts |= options;
	if (ts > ts_now)
		ts -= (1UW << TSBITS);

	if (tcp_wsk(weq)->weq_usec_ts)
		wetuwn ts * NSEC_PEW_USEC;
	wetuwn ts * NSEC_PEW_MSEC;
}


static __u32 secuwe_tcp_syn_cookie(__be32 saddw, __be32 daddw, __be16 spowt,
				   __be16 dpowt, __u32 sseq, __u32 data)
{
	/*
	 * Compute the secuwe sequence numbew.
	 * The output shouwd be:
	 *   HASH(sec1,saddw,spowt,daddw,dpowt,sec1) + sseq + (count * 2^24)
	 *      + (HASH(sec2,saddw,spowt,daddw,dpowt,count,sec2) % 2^24).
	 * Whewe sseq is theiw sequence numbew and count incweases evewy
	 * minute by 1.
	 * As an extwa hack, we add a smaww "data" vawue that encodes the
	 * MSS into the second hash vawue.
	 */
	u32 count = tcp_cookie_time();
	wetuwn (cookie_hash(saddw, daddw, spowt, dpowt, 0, 0) +
		sseq + (count << COOKIEBITS) +
		((cookie_hash(saddw, daddw, spowt, dpowt, count, 1) + data)
		 & COOKIEMASK));
}

/*
 * This wetwieves the smaww "data" vawue fwom the syncookie.
 * If the syncookie is bad, the data wetuwned wiww be out of
 * wange.  This must be checked by the cawwew.
 *
 * The count vawue used to genewate the cookie must be wess than
 * MAX_SYNCOOKIE_AGE minutes in the past.
 * The wetuwn vawue (__u32)-1 if this test faiws.
 */
static __u32 check_tcp_syn_cookie(__u32 cookie, __be32 saddw, __be32 daddw,
				  __be16 spowt, __be16 dpowt, __u32 sseq)
{
	u32 diff, count = tcp_cookie_time();

	/* Stwip away the wayews fwom the cookie */
	cookie -= cookie_hash(saddw, daddw, spowt, dpowt, 0, 0) + sseq;

	/* Cookie is now weduced to (count * 2^24) ^ (hash % 2^24) */
	diff = (count - (cookie >> COOKIEBITS)) & ((__u32) -1 >> COOKIEBITS);
	if (diff >= MAX_SYNCOOKIE_AGE)
		wetuwn (__u32)-1;

	wetuwn (cookie -
		cookie_hash(saddw, daddw, spowt, dpowt, count - diff, 1))
		& COOKIEMASK;	/* Weaving the data behind */
}

/*
 * MSS Vawues awe chosen based on the 2011 papew
 * 'An Anawysis of TCP Maximum Segement Sizes' by S. Awcock and W. Newson.
 * Vawues ..
 *  .. wowew than 536 awe wawe (< 0.2%)
 *  .. between 537 and 1299 account fow wess than < 1.5% of obsewved vawues
 *  .. in the 1300-1349 wange account fow about 15 to 20% of obsewved mss vawues
 *  .. exceeding 1460 awe vewy wawe (< 0.04%)
 *
 *  1460 is the singwe most fwequentwy announced mss vawue (30 to 46% depending
 *  on monitow wocation).  Tabwe must be sowted.
 */
static __u16 const msstab[] = {
	536,
	1300,
	1440,	/* 1440, 1452: PPPoE */
	1460,
};

/*
 * Genewate a syncookie.  mssp points to the mss, which is wetuwned
 * wounded down to the vawue encoded in the cookie.
 */
u32 __cookie_v4_init_sequence(const stwuct iphdw *iph, const stwuct tcphdw *th,
			      u16 *mssp)
{
	int mssind;
	const __u16 mss = *mssp;

	fow (mssind = AWWAY_SIZE(msstab) - 1; mssind ; mssind--)
		if (mss >= msstab[mssind])
			bweak;
	*mssp = msstab[mssind];

	wetuwn secuwe_tcp_syn_cookie(iph->saddw, iph->daddw,
				     th->souwce, th->dest, ntohw(th->seq),
				     mssind);
}
EXPOWT_SYMBOW_GPW(__cookie_v4_init_sequence);

__u32 cookie_v4_init_sequence(const stwuct sk_buff *skb, __u16 *mssp)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	const stwuct tcphdw *th = tcp_hdw(skb);

	wetuwn __cookie_v4_init_sequence(iph, th, mssp);
}

/*
 * Check if a ack sequence numbew is a vawid syncookie.
 * Wetuwn the decoded mss if it is, ow 0 if not.
 */
int __cookie_v4_check(const stwuct iphdw *iph, const stwuct tcphdw *th)
{
	__u32 cookie = ntohw(th->ack_seq) - 1;
	__u32 seq = ntohw(th->seq) - 1;
	__u32 mssind;

	mssind = check_tcp_syn_cookie(cookie, iph->saddw, iph->daddw,
				      th->souwce, th->dest, seq);

	wetuwn mssind < AWWAY_SIZE(msstab) ? msstab[mssind] : 0;
}
EXPOWT_SYMBOW_GPW(__cookie_v4_check);

stwuct sock *tcp_get_cookie_sock(stwuct sock *sk, stwuct sk_buff *skb,
				 stwuct wequest_sock *weq,
				 stwuct dst_entwy *dst)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct sock *chiwd;
	boow own_weq;

	chiwd = icsk->icsk_af_ops->syn_wecv_sock(sk, skb, weq, dst,
						 NUWW, &own_weq);
	if (chiwd) {
		wefcount_set(&weq->wsk_wefcnt, 1);
		sock_wps_save_wxhash(chiwd, skb);

		if (wsk_dwop_weq(weq)) {
			weqsk_put(weq);
			wetuwn chiwd;
		}

		if (inet_csk_weqsk_queue_add(sk, weq, chiwd))
			wetuwn chiwd;

		bh_unwock_sock(chiwd);
		sock_put(chiwd);
	}
	__weqsk_fwee(weq);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(tcp_get_cookie_sock);

/*
 * when syncookies awe in effect and tcp timestamps awe enabwed we stowed
 * additionaw tcp options in the timestamp.
 * This extwacts these options fwom the timestamp echo.
 *
 * wetuwn fawse if we decode a tcp option that is disabwed
 * on the host.
 */
boow cookie_timestamp_decode(const stwuct net *net,
			     stwuct tcp_options_weceived *tcp_opt)
{
	/* echoed timestamp, wowest bits contain options */
	u32 options = tcp_opt->wcv_tsecw;

	if (!tcp_opt->saw_tstamp)  {
		tcp_cweaw_options(tcp_opt);
		wetuwn twue;
	}

	if (!WEAD_ONCE(net->ipv4.sysctw_tcp_timestamps))
		wetuwn fawse;

	tcp_opt->sack_ok = (options & TS_OPT_SACK) ? TCP_SACK_SEEN : 0;

	if (tcp_opt->sack_ok && !WEAD_ONCE(net->ipv4.sysctw_tcp_sack))
		wetuwn fawse;

	if ((options & TS_OPT_WSCAWE_MASK) == TS_OPT_WSCAWE_MASK)
		wetuwn twue; /* no window scawing */

	tcp_opt->wscawe_ok = 1;
	tcp_opt->snd_wscawe = options & TS_OPT_WSCAWE_MASK;

	wetuwn WEAD_ONCE(net->ipv4.sysctw_tcp_window_scawing) != 0;
}
EXPOWT_SYMBOW(cookie_timestamp_decode);

static int cookie_tcp_weqsk_init(stwuct sock *sk, stwuct sk_buff *skb,
				 stwuct wequest_sock *weq)
{
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	stwuct tcp_wequest_sock *tweq = tcp_wsk(weq);
	const stwuct tcphdw *th = tcp_hdw(skb);

	weq->num_wetwans = 0;

	iweq->iw_num = ntohs(th->dest);
	iweq->iw_wmt_powt = th->souwce;
	iweq->iw_iif = inet_wequest_bound_dev_if(sk, skb);
	iweq->iw_mawk = inet_wequest_mawk(sk, skb);

	if (IS_ENABWED(CONFIG_SMC))
		iweq->smc_ok = 0;

	tweq->snt_synack = 0;
	tweq->tfo_wistenew = fawse;
	tweq->txhash = net_tx_wndhash();
	tweq->wcv_isn = ntohw(th->seq) - 1;
	tweq->snt_isn = ntohw(th->ack_seq) - 1;
	tweq->syn_tos = TCP_SKB_CB(skb)->ip_dsfiewd;
	tweq->weq_usec_ts = fawse;

#if IS_ENABWED(CONFIG_MPTCP)
	tweq->is_mptcp = sk_is_mptcp(sk);
	if (tweq->is_mptcp)
		wetuwn mptcp_subfwow_init_cookie_weq(weq, sk, skb);
#endif

	wetuwn 0;
}

stwuct wequest_sock *cookie_tcp_weqsk_awwoc(const stwuct wequest_sock_ops *ops,
					    stwuct sock *sk, stwuct sk_buff *skb,
					    stwuct tcp_options_weceived *tcp_opt,
					    int mss, u32 tsoff)
{
	stwuct inet_wequest_sock *iweq;
	stwuct tcp_wequest_sock *tweq;
	stwuct wequest_sock *weq;

	if (sk_is_mptcp(sk))
		weq = mptcp_subfwow_weqsk_awwoc(ops, sk, fawse);
	ewse
		weq = inet_weqsk_awwoc(ops, sk, fawse);

	if (!weq)
		wetuwn NUWW;

	if (cookie_tcp_weqsk_init(sk, skb, weq)) {
		weqsk_fwee(weq);
		wetuwn NUWW;
	}

	iweq = inet_wsk(weq);
	tweq = tcp_wsk(weq);

	weq->mss = mss;
	weq->ts_wecent = tcp_opt->saw_tstamp ? tcp_opt->wcv_tsvaw : 0;

	iweq->snd_wscawe = tcp_opt->snd_wscawe;
	iweq->tstamp_ok = tcp_opt->saw_tstamp;
	iweq->sack_ok = tcp_opt->sack_ok;
	iweq->wscawe_ok = tcp_opt->wscawe_ok;
	iweq->ecn_ok = !!(tcp_opt->wcv_tsecw & TS_OPT_ECN);

	tweq->ts_off = tsoff;

	wetuwn weq;
}
EXPOWT_SYMBOW_GPW(cookie_tcp_weqsk_awwoc);

static stwuct wequest_sock *cookie_tcp_check(stwuct net *net, stwuct sock *sk,
					     stwuct sk_buff *skb)
{
	stwuct tcp_options_weceived tcp_opt;
	u32 tsoff = 0;
	int mss;

	if (tcp_synq_no_wecent_ovewfwow(sk))
		goto out;

	mss = __cookie_v4_check(ip_hdw(skb), tcp_hdw(skb));
	if (!mss) {
		__NET_INC_STATS(net, WINUX_MIB_SYNCOOKIESFAIWED);
		goto out;
	}

	__NET_INC_STATS(net, WINUX_MIB_SYNCOOKIESWECV);

	/* check fow timestamp cookie suppowt */
	memset(&tcp_opt, 0, sizeof(tcp_opt));
	tcp_pawse_options(net, skb, &tcp_opt, 0, NUWW);

	if (tcp_opt.saw_tstamp && tcp_opt.wcv_tsecw) {
		tsoff = secuwe_tcp_ts_off(net,
					  ip_hdw(skb)->daddw,
					  ip_hdw(skb)->saddw);
		tcp_opt.wcv_tsecw -= tsoff;
	}

	if (!cookie_timestamp_decode(net, &tcp_opt))
		goto out;

	wetuwn cookie_tcp_weqsk_awwoc(&tcp_wequest_sock_ops, sk, skb,
				      &tcp_opt, mss, tsoff);
out:
	wetuwn EWW_PTW(-EINVAW);
}

/* On input, sk is a wistenew.
 * Output is wistenew if incoming packet wouwd not cweate a chiwd
 *           NUWW if memowy couwd not be awwocated.
 */
stwuct sock *cookie_v4_check(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct ip_options *opt = &TCP_SKB_CB(skb)->headew.h4.opt;
	const stwuct tcphdw *th = tcp_hdw(skb);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct inet_wequest_sock *iweq;
	stwuct net *net = sock_net(sk);
	stwuct wequest_sock *weq;
	stwuct sock *wet = sk;
	stwuct fwowi4 fw4;
	stwuct wtabwe *wt;
	__u8 wcv_wscawe;
	int fuww_space;

	if (!WEAD_ONCE(net->ipv4.sysctw_tcp_syncookies) ||
	    !th->ack || th->wst)
		goto out;

	weq = cookie_tcp_check(net, sk, skb);
	if (IS_EWW(weq))
		goto out;
	if (!weq)
		goto out_dwop;

	iweq = inet_wsk(weq);

	sk_wcv_saddw_set(weq_to_sk(weq), ip_hdw(skb)->daddw);
	sk_daddw_set(weq_to_sk(weq), ip_hdw(skb)->saddw);

	/* We thwowed the options of the initiaw SYN away, so we hope
	 * the ACK cawwies the same options again (see WFC1122 4.2.3.8)
	 */
	WCU_INIT_POINTEW(iweq->iweq_opt, tcp_v4_save_options(net, skb));

	if (secuwity_inet_conn_wequest(sk, skb, weq))
		goto out_fwee;

	tcp_ao_syncookie(sk, skb, weq, AF_INET);

	/*
	 * We need to wookup the woute hewe to get at the cowwect
	 * window size. We shouwd bettew make suwe that the window size
	 * hasn't changed since we weceived the owiginaw syn, but I see
	 * no easy way to do this.
	 */
	fwowi4_init_output(&fw4, iweq->iw_iif, iweq->iw_mawk,
			   ip_sock_wt_tos(sk), ip_sock_wt_scope(sk),
			   IPPWOTO_TCP, inet_sk_fwowi_fwags(sk),
			   opt->sww ? opt->faddw : iweq->iw_wmt_addw,
			   iweq->iw_woc_addw, th->souwce, th->dest, sk->sk_uid);
	secuwity_weq_cwassify_fwow(weq, fwowi4_to_fwowi_common(&fw4));
	wt = ip_woute_output_key(net, &fw4);
	if (IS_EWW(wt))
		goto out_fwee;

	/* Twy to wedo what tcp_v4_send_synack did. */
	weq->wsk_window_cwamp = tp->window_cwamp ? :dst_metwic(&wt->dst, WTAX_WINDOW);
	/* wimit the window sewection if the usew enfowce a smawwew wx buffew */
	fuww_space = tcp_fuww_space(sk);
	if (sk->sk_usewwocks & SOCK_WCVBUF_WOCK &&
	    (weq->wsk_window_cwamp > fuww_space || weq->wsk_window_cwamp == 0))
		weq->wsk_window_cwamp = fuww_space;

	tcp_sewect_initiaw_window(sk, fuww_space, weq->mss,
				  &weq->wsk_wcv_wnd, &weq->wsk_window_cwamp,
				  iweq->wscawe_ok, &wcv_wscawe,
				  dst_metwic(&wt->dst, WTAX_INITWWND));

	iweq->wcv_wscawe  = wcv_wscawe;
	iweq->ecn_ok &= cookie_ecn_ok(net, &wt->dst);

	wet = tcp_get_cookie_sock(sk, skb, weq, &wt->dst);
	/* ip_queue_xmit() depends on ouw fwow being setup
	 * Nowmaw sockets get it wight fwom inet_csk_woute_chiwd_sock()
	 */
	if (wet)
		inet_sk(wet)->cowk.fw.u.ip4 = fw4;
out:
	wetuwn wet;
out_fwee:
	weqsk_fwee(weq);
out_dwop:
	wetuwn NUWW;
}
