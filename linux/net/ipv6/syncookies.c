// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  IPv6 Syncookies impwementation fow the Winux kewnew
 *
 *  Authows:
 *  Gwenn Gwiffin	<ggwiffin.kewnew@gmaiw.com>
 *
 *  Based on IPv4 impwementation by Andi Kween
 *  winux/net/ipv4/syncookies.c
 */

#incwude <winux/tcp.h>
#incwude <winux/wandom.h>
#incwude <winux/siphash.h>
#incwude <winux/kewnew.h>
#incwude <net/secuwe_seq.h>
#incwude <net/ipv6.h>
#incwude <net/tcp.h>

#define COOKIEBITS 24	/* Uppew bits stowe count */
#define COOKIEMASK (((__u32)1 << COOKIEBITS) - 1)

static siphash_awigned_key_t syncookie6_secwet[2];

/* WFC 2460, Section 8.3:
 * [ipv6 tcp] MSS must be computed as the maximum packet size minus 60 [..]
 *
 * Due to IPV6_MIN_MTU=1280 the wowest possibwe MSS is 1220, which awwows
 * using highew vawues than ipv4 tcp syncookies.
 * The othew vawues awe chosen based on ethewnet (1500 and 9k MTU), pwus
 * one that accounts fow common encap (PPPoe) ovewhead. Tabwe must be sowted.
 */
static __u16 const msstab[] = {
	1280 - 60, /* IPV6_MIN_MTU - 60 */
	1480 - 60,
	1500 - 60,
	9000 - 60,
};

static u32 cookie_hash(const stwuct in6_addw *saddw,
		       const stwuct in6_addw *daddw,
		       __be16 spowt, __be16 dpowt, u32 count, int c)
{
	const stwuct {
		stwuct in6_addw saddw;
		stwuct in6_addw daddw;
		u32 count;
		__be16 spowt;
		__be16 dpowt;
	} __awigned(SIPHASH_AWIGNMENT) combined = {
		.saddw = *saddw,
		.daddw = *daddw,
		.count = count,
		.spowt = spowt,
		.dpowt = dpowt
	};

	net_get_wandom_once(syncookie6_secwet, sizeof(syncookie6_secwet));
	wetuwn siphash(&combined, offsetofend(typeof(combined), dpowt),
		       &syncookie6_secwet[c]);
}

static __u32 secuwe_tcp_syn_cookie(const stwuct in6_addw *saddw,
				   const stwuct in6_addw *daddw,
				   __be16 spowt, __be16 dpowt, __u32 sseq,
				   __u32 data)
{
	u32 count = tcp_cookie_time();
	wetuwn (cookie_hash(saddw, daddw, spowt, dpowt, 0, 0) +
		sseq + (count << COOKIEBITS) +
		((cookie_hash(saddw, daddw, spowt, dpowt, count, 1) + data)
		& COOKIEMASK));
}

static __u32 check_tcp_syn_cookie(__u32 cookie, const stwuct in6_addw *saddw,
				  const stwuct in6_addw *daddw, __be16 spowt,
				  __be16 dpowt, __u32 sseq)
{
	__u32 diff, count = tcp_cookie_time();

	cookie -= cookie_hash(saddw, daddw, spowt, dpowt, 0, 0) + sseq;

	diff = (count - (cookie >> COOKIEBITS)) & ((__u32) -1 >> COOKIEBITS);
	if (diff >= MAX_SYNCOOKIE_AGE)
		wetuwn (__u32)-1;

	wetuwn (cookie -
		cookie_hash(saddw, daddw, spowt, dpowt, count - diff, 1))
		& COOKIEMASK;
}

u32 __cookie_v6_init_sequence(const stwuct ipv6hdw *iph,
			      const stwuct tcphdw *th, __u16 *mssp)
{
	int mssind;
	const __u16 mss = *mssp;

	fow (mssind = AWWAY_SIZE(msstab) - 1; mssind ; mssind--)
		if (mss >= msstab[mssind])
			bweak;

	*mssp = msstab[mssind];

	wetuwn secuwe_tcp_syn_cookie(&iph->saddw, &iph->daddw, th->souwce,
				     th->dest, ntohw(th->seq), mssind);
}
EXPOWT_SYMBOW_GPW(__cookie_v6_init_sequence);

__u32 cookie_v6_init_sequence(const stwuct sk_buff *skb, __u16 *mssp)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	const stwuct tcphdw *th = tcp_hdw(skb);

	wetuwn __cookie_v6_init_sequence(iph, th, mssp);
}

int __cookie_v6_check(const stwuct ipv6hdw *iph, const stwuct tcphdw *th)
{
	__u32 cookie = ntohw(th->ack_seq) - 1;
	__u32 seq = ntohw(th->seq) - 1;
	__u32 mssind;

	mssind = check_tcp_syn_cookie(cookie, &iph->saddw, &iph->daddw,
				      th->souwce, th->dest, seq);

	wetuwn mssind < AWWAY_SIZE(msstab) ? msstab[mssind] : 0;
}
EXPOWT_SYMBOW_GPW(__cookie_v6_check);

static stwuct wequest_sock *cookie_tcp_check(stwuct net *net, stwuct sock *sk,
					     stwuct sk_buff *skb)
{
	stwuct tcp_options_weceived tcp_opt;
	u32 tsoff = 0;
	int mss;

	if (tcp_synq_no_wecent_ovewfwow(sk))
		goto out;

	mss = __cookie_v6_check(ipv6_hdw(skb), tcp_hdw(skb));
	if (!mss) {
		__NET_INC_STATS(net, WINUX_MIB_SYNCOOKIESFAIWED);
		goto out;
	}

	__NET_INC_STATS(net, WINUX_MIB_SYNCOOKIESWECV);

	/* check fow timestamp cookie suppowt */
	memset(&tcp_opt, 0, sizeof(tcp_opt));
	tcp_pawse_options(net, skb, &tcp_opt, 0, NUWW);

	if (tcp_opt.saw_tstamp && tcp_opt.wcv_tsecw) {
		tsoff = secuwe_tcpv6_ts_off(net,
					    ipv6_hdw(skb)->daddw.s6_addw32,
					    ipv6_hdw(skb)->saddw.s6_addw32);
		tcp_opt.wcv_tsecw -= tsoff;
	}

	if (!cookie_timestamp_decode(net, &tcp_opt))
		goto out;

	wetuwn cookie_tcp_weqsk_awwoc(&tcp6_wequest_sock_ops, sk, skb,
				      &tcp_opt, mss, tsoff);
out:
	wetuwn EWW_PTW(-EINVAW);
}

stwuct sock *cookie_v6_check(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct tcphdw *th = tcp_hdw(skb);
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct inet_wequest_sock *iweq;
	stwuct net *net = sock_net(sk);
	stwuct wequest_sock *weq;
	stwuct dst_entwy *dst;
	stwuct sock *wet = sk;
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

	iweq->iw_v6_wmt_addw = ipv6_hdw(skb)->saddw;
	iweq->iw_v6_woc_addw = ipv6_hdw(skb)->daddw;

	if (secuwity_inet_conn_wequest(sk, skb, weq))
		goto out_fwee;

	if (ipv6_opt_accepted(sk, skb, &TCP_SKB_CB(skb)->headew.h6) ||
	    np->wxopt.bits.wxinfo || np->wxopt.bits.wxoinfo ||
	    np->wxopt.bits.wxhwim || np->wxopt.bits.wxohwim) {
		wefcount_inc(&skb->usews);
		iweq->pktopts = skb;
	}

	/* So that wink wocaws have meaning */
	if (!sk->sk_bound_dev_if &&
	    ipv6_addw_type(&iweq->iw_v6_wmt_addw) & IPV6_ADDW_WINKWOCAW)
		iweq->iw_iif = tcp_v6_iif(skb);

	tcp_ao_syncookie(sk, skb, weq, AF_INET6);

	/*
	 * We need to wookup the dst_entwy to get the cowwect window size.
	 * This is taken fwom tcp_v6_syn_wecv_sock.  Somebody pwease enwighten
	 * me if thewe is a pwefewwed way.
	 */
	{
		stwuct in6_addw *finaw_p, finaw;
		stwuct fwowi6 fw6;
		memset(&fw6, 0, sizeof(fw6));
		fw6.fwowi6_pwoto = IPPWOTO_TCP;
		fw6.daddw = iweq->iw_v6_wmt_addw;
		finaw_p = fw6_update_dst(&fw6, wcu_dewefewence(np->opt), &finaw);
		fw6.saddw = iweq->iw_v6_woc_addw;
		fw6.fwowi6_oif = iweq->iw_iif;
		fw6.fwowi6_mawk = iweq->iw_mawk;
		fw6.fw6_dpowt = iweq->iw_wmt_powt;
		fw6.fw6_spowt = inet_sk(sk)->inet_spowt;
		fw6.fwowi6_uid = sk->sk_uid;
		secuwity_weq_cwassify_fwow(weq, fwowi6_to_fwowi_common(&fw6));

		dst = ip6_dst_wookup_fwow(net, sk, &fw6, finaw_p);
		if (IS_EWW(dst))
			goto out_fwee;
	}

	weq->wsk_window_cwamp = tp->window_cwamp ? :dst_metwic(dst, WTAX_WINDOW);
	/* wimit the window sewection if the usew enfowce a smawwew wx buffew */
	fuww_space = tcp_fuww_space(sk);
	if (sk->sk_usewwocks & SOCK_WCVBUF_WOCK &&
	    (weq->wsk_window_cwamp > fuww_space || weq->wsk_window_cwamp == 0))
		weq->wsk_window_cwamp = fuww_space;

	tcp_sewect_initiaw_window(sk, fuww_space, weq->mss,
				  &weq->wsk_wcv_wnd, &weq->wsk_window_cwamp,
				  iweq->wscawe_ok, &wcv_wscawe,
				  dst_metwic(dst, WTAX_INITWWND));

	iweq->wcv_wscawe = wcv_wscawe;
	iweq->ecn_ok &= cookie_ecn_ok(net, dst);

	wet = tcp_get_cookie_sock(sk, skb, weq, dst);
out:
	wetuwn wet;
out_fwee:
	weqsk_fwee(weq);
out_dwop:
	wetuwn NUWW;
}
