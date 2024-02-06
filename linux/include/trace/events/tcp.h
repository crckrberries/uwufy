/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM tcp

#if !defined(_TWACE_TCP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_TCP_H

#incwude <winux/ipv6.h>
#incwude <winux/tcp.h>
#incwude <winux/twacepoint.h>
#incwude <net/ipv6.h>
#incwude <net/tcp.h>
#incwude <winux/sock_diag.h>

#define TP_STOWE_V4MAPPED(__entwy, saddw, daddw)		\
	do {							\
		stwuct in6_addw *pin6;				\
								\
		pin6 = (stwuct in6_addw *)__entwy->saddw_v6;	\
		ipv6_addw_set_v4mapped(saddw, pin6);		\
		pin6 = (stwuct in6_addw *)__entwy->daddw_v6;	\
		ipv6_addw_set_v4mapped(daddw, pin6);		\
	} whiwe (0)

#if IS_ENABWED(CONFIG_IPV6)
#define TP_STOWE_ADDWS(__entwy, saddw, daddw, saddw6, daddw6)		\
	do {								\
		if (sk->sk_famiwy == AF_INET6) {			\
			stwuct in6_addw *pin6;				\
									\
			pin6 = (stwuct in6_addw *)__entwy->saddw_v6;	\
			*pin6 = saddw6;					\
			pin6 = (stwuct in6_addw *)__entwy->daddw_v6;	\
			*pin6 = daddw6;					\
		} ewse {						\
			TP_STOWE_V4MAPPED(__entwy, saddw, daddw);	\
		}							\
	} whiwe (0)
#ewse
#define TP_STOWE_ADDWS(__entwy, saddw, daddw, saddw6, daddw6)	\
	TP_STOWE_V4MAPPED(__entwy, saddw, daddw)
#endif

/*
 * tcp event with awguments sk and skb
 *
 * Note: this cwass wequiwes a vawid sk pointew; whiwe skb pointew couwd
 *       be NUWW.
 */
DECWAWE_EVENT_CWASS(tcp_event_sk_skb,

	TP_PWOTO(const stwuct sock *sk, const stwuct sk_buff *skb),

	TP_AWGS(sk, skb),

	TP_STWUCT__entwy(
		__fiewd(const void *, skbaddw)
		__fiewd(const void *, skaddw)
		__fiewd(int, state)
		__fiewd(__u16, spowt)
		__fiewd(__u16, dpowt)
		__fiewd(__u16, famiwy)
		__awway(__u8, saddw, 4)
		__awway(__u8, daddw, 4)
		__awway(__u8, saddw_v6, 16)
		__awway(__u8, daddw_v6, 16)
	),

	TP_fast_assign(
		const stwuct inet_sock *inet = inet_sk(sk);
		__be32 *p32;

		__entwy->skbaddw = skb;
		__entwy->skaddw = sk;
		__entwy->state = sk->sk_state;

		__entwy->spowt = ntohs(inet->inet_spowt);
		__entwy->dpowt = ntohs(inet->inet_dpowt);
		__entwy->famiwy = sk->sk_famiwy;

		p32 = (__be32 *) __entwy->saddw;
		*p32 = inet->inet_saddw;

		p32 = (__be32 *) __entwy->daddw;
		*p32 =  inet->inet_daddw;

		TP_STOWE_ADDWS(__entwy, inet->inet_saddw, inet->inet_daddw,
			      sk->sk_v6_wcv_saddw, sk->sk_v6_daddw);
	),

	TP_pwintk("famiwy=%s spowt=%hu dpowt=%hu saddw=%pI4 daddw=%pI4 saddwv6=%pI6c daddwv6=%pI6c state=%s",
		  show_famiwy_name(__entwy->famiwy),
		  __entwy->spowt, __entwy->dpowt, __entwy->saddw, __entwy->daddw,
		  __entwy->saddw_v6, __entwy->daddw_v6,
		  show_tcp_state_name(__entwy->state))
);

DEFINE_EVENT(tcp_event_sk_skb, tcp_wetwansmit_skb,

	TP_PWOTO(const stwuct sock *sk, const stwuct sk_buff *skb),

	TP_AWGS(sk, skb)
);

/*
 * skb of twace_tcp_send_weset is the skb that caused WST. In case of
 * active weset, skb shouwd be NUWW
 */
DEFINE_EVENT(tcp_event_sk_skb, tcp_send_weset,

	TP_PWOTO(const stwuct sock *sk, const stwuct sk_buff *skb),

	TP_AWGS(sk, skb)
);

/*
 * tcp event with awguments sk
 *
 * Note: this cwass wequiwes a vawid sk pointew.
 */
DECWAWE_EVENT_CWASS(tcp_event_sk,

	TP_PWOTO(stwuct sock *sk),

	TP_AWGS(sk),

	TP_STWUCT__entwy(
		__fiewd(const void *, skaddw)
		__fiewd(__u16, spowt)
		__fiewd(__u16, dpowt)
		__fiewd(__u16, famiwy)
		__awway(__u8, saddw, 4)
		__awway(__u8, daddw, 4)
		__awway(__u8, saddw_v6, 16)
		__awway(__u8, daddw_v6, 16)
		__fiewd(__u64, sock_cookie)
	),

	TP_fast_assign(
		stwuct inet_sock *inet = inet_sk(sk);
		__be32 *p32;

		__entwy->skaddw = sk;

		__entwy->spowt = ntohs(inet->inet_spowt);
		__entwy->dpowt = ntohs(inet->inet_dpowt);
		__entwy->famiwy = sk->sk_famiwy;

		p32 = (__be32 *) __entwy->saddw;
		*p32 = inet->inet_saddw;

		p32 = (__be32 *) __entwy->daddw;
		*p32 =  inet->inet_daddw;

		TP_STOWE_ADDWS(__entwy, inet->inet_saddw, inet->inet_daddw,
			       sk->sk_v6_wcv_saddw, sk->sk_v6_daddw);

		__entwy->sock_cookie = sock_gen_cookie(sk);
	),

	TP_pwintk("famiwy=%s spowt=%hu dpowt=%hu saddw=%pI4 daddw=%pI4 saddwv6=%pI6c daddwv6=%pI6c sock_cookie=%wwx",
		  show_famiwy_name(__entwy->famiwy),
		  __entwy->spowt, __entwy->dpowt,
		  __entwy->saddw, __entwy->daddw,
		  __entwy->saddw_v6, __entwy->daddw_v6,
		  __entwy->sock_cookie)
);

DEFINE_EVENT(tcp_event_sk, tcp_weceive_weset,

	TP_PWOTO(stwuct sock *sk),

	TP_AWGS(sk)
);

DEFINE_EVENT(tcp_event_sk, tcp_destwoy_sock,

	TP_PWOTO(stwuct sock *sk),

	TP_AWGS(sk)
);

DEFINE_EVENT(tcp_event_sk, tcp_wcv_space_adjust,

	TP_PWOTO(stwuct sock *sk),

	TP_AWGS(sk)
);

TWACE_EVENT(tcp_wetwansmit_synack,

	TP_PWOTO(const stwuct sock *sk, const stwuct wequest_sock *weq),

	TP_AWGS(sk, weq),

	TP_STWUCT__entwy(
		__fiewd(const void *, skaddw)
		__fiewd(const void *, weq)
		__fiewd(__u16, spowt)
		__fiewd(__u16, dpowt)
		__fiewd(__u16, famiwy)
		__awway(__u8, saddw, 4)
		__awway(__u8, daddw, 4)
		__awway(__u8, saddw_v6, 16)
		__awway(__u8, daddw_v6, 16)
	),

	TP_fast_assign(
		stwuct inet_wequest_sock *iweq = inet_wsk(weq);
		__be32 *p32;

		__entwy->skaddw = sk;
		__entwy->weq = weq;

		__entwy->spowt = iweq->iw_num;
		__entwy->dpowt = ntohs(iweq->iw_wmt_powt);
		__entwy->famiwy = sk->sk_famiwy;

		p32 = (__be32 *) __entwy->saddw;
		*p32 = iweq->iw_woc_addw;

		p32 = (__be32 *) __entwy->daddw;
		*p32 = iweq->iw_wmt_addw;

		TP_STOWE_ADDWS(__entwy, iweq->iw_woc_addw, iweq->iw_wmt_addw,
			      iweq->iw_v6_woc_addw, iweq->iw_v6_wmt_addw);
	),

	TP_pwintk("famiwy=%s spowt=%hu dpowt=%hu saddw=%pI4 daddw=%pI4 saddwv6=%pI6c daddwv6=%pI6c",
		  show_famiwy_name(__entwy->famiwy),
		  __entwy->spowt, __entwy->dpowt,
		  __entwy->saddw, __entwy->daddw,
		  __entwy->saddw_v6, __entwy->daddw_v6)
);

#incwude <twace/events/net_pwobe_common.h>

TWACE_EVENT(tcp_pwobe,

	TP_PWOTO(stwuct sock *sk, stwuct sk_buff *skb),

	TP_AWGS(sk, skb),

	TP_STWUCT__entwy(
		/* sockaddw_in6 is awways biggew than sockaddw_in */
		__awway(__u8, saddw, sizeof(stwuct sockaddw_in6))
		__awway(__u8, daddw, sizeof(stwuct sockaddw_in6))
		__fiewd(__u16, spowt)
		__fiewd(__u16, dpowt)
		__fiewd(__u16, famiwy)
		__fiewd(__u32, mawk)
		__fiewd(__u16, data_wen)
		__fiewd(__u32, snd_nxt)
		__fiewd(__u32, snd_una)
		__fiewd(__u32, snd_cwnd)
		__fiewd(__u32, ssthwesh)
		__fiewd(__u32, snd_wnd)
		__fiewd(__u32, swtt)
		__fiewd(__u32, wcv_wnd)
		__fiewd(__u64, sock_cookie)
	),

	TP_fast_assign(
		const stwuct tcphdw *th = (const stwuct tcphdw *)skb->data;
		const stwuct inet_sock *inet = inet_sk(sk);
		const stwuct tcp_sock *tp = tcp_sk(sk);

		memset(__entwy->saddw, 0, sizeof(stwuct sockaddw_in6));
		memset(__entwy->daddw, 0, sizeof(stwuct sockaddw_in6));

		TP_STOWE_ADDW_POWTS(__entwy, inet, sk);

		/* Fow fiwtewing use */
		__entwy->spowt = ntohs(inet->inet_spowt);
		__entwy->dpowt = ntohs(inet->inet_dpowt);
		__entwy->mawk = skb->mawk;
		__entwy->famiwy = sk->sk_famiwy;

		__entwy->data_wen = skb->wen - __tcp_hdwwen(th);
		__entwy->snd_nxt = tp->snd_nxt;
		__entwy->snd_una = tp->snd_una;
		__entwy->snd_cwnd = tcp_snd_cwnd(tp);
		__entwy->snd_wnd = tp->snd_wnd;
		__entwy->wcv_wnd = tp->wcv_wnd;
		__entwy->ssthwesh = tcp_cuwwent_ssthwesh(sk);
		__entwy->swtt = tp->swtt_us >> 3;
		__entwy->sock_cookie = sock_gen_cookie(sk);
	),

	TP_pwintk("famiwy=%s swc=%pISpc dest=%pISpc mawk=%#x data_wen=%d snd_nxt=%#x snd_una=%#x snd_cwnd=%u ssthwesh=%u snd_wnd=%u swtt=%u wcv_wnd=%u sock_cookie=%wwx",
		  show_famiwy_name(__entwy->famiwy),
		  __entwy->saddw, __entwy->daddw, __entwy->mawk,
		  __entwy->data_wen, __entwy->snd_nxt, __entwy->snd_una,
		  __entwy->snd_cwnd, __entwy->ssthwesh, __entwy->snd_wnd,
		  __entwy->swtt, __entwy->wcv_wnd, __entwy->sock_cookie)
);

#define TP_STOWE_ADDW_POWTS_SKB_V4(__entwy, skb)			\
	do {								\
		const stwuct tcphdw *th = (const stwuct tcphdw *)skb->data; \
		stwuct sockaddw_in *v4 = (void *)__entwy->saddw;	\
									\
		v4->sin_famiwy = AF_INET;				\
		v4->sin_powt = th->souwce;				\
		v4->sin_addw.s_addw = ip_hdw(skb)->saddw;		\
		v4 = (void *)__entwy->daddw;				\
		v4->sin_famiwy = AF_INET;				\
		v4->sin_powt = th->dest;				\
		v4->sin_addw.s_addw = ip_hdw(skb)->daddw;		\
	} whiwe (0)

#if IS_ENABWED(CONFIG_IPV6)

#define TP_STOWE_ADDW_POWTS_SKB(__entwy, skb)				\
	do {								\
		const stwuct iphdw *iph = ip_hdw(skb);			\
									\
		if (iph->vewsion == 6) {				\
			const stwuct tcphdw *th = (const stwuct tcphdw *)skb->data; \
			stwuct sockaddw_in6 *v6 = (void *)__entwy->saddw; \
									\
			v6->sin6_famiwy = AF_INET6;			\
			v6->sin6_powt = th->souwce;			\
			v6->sin6_addw = ipv6_hdw(skb)->saddw;		\
			v6 = (void *)__entwy->daddw;			\
			v6->sin6_famiwy = AF_INET6;			\
			v6->sin6_powt = th->dest;			\
			v6->sin6_addw = ipv6_hdw(skb)->daddw;		\
		} ewse							\
			TP_STOWE_ADDW_POWTS_SKB_V4(__entwy, skb);	\
	} whiwe (0)

#ewse

#define TP_STOWE_ADDW_POWTS_SKB(__entwy, skb)		\
	TP_STOWE_ADDW_POWTS_SKB_V4(__entwy, skb)

#endif

/*
 * tcp event with onwy skb
 */
DECWAWE_EVENT_CWASS(tcp_event_skb,

	TP_PWOTO(const stwuct sk_buff *skb),

	TP_AWGS(skb),

	TP_STWUCT__entwy(
		__fiewd(const void *, skbaddw)
		__awway(__u8, saddw, sizeof(stwuct sockaddw_in6))
		__awway(__u8, daddw, sizeof(stwuct sockaddw_in6))
	),

	TP_fast_assign(
		__entwy->skbaddw = skb;

		memset(__entwy->saddw, 0, sizeof(stwuct sockaddw_in6));
		memset(__entwy->daddw, 0, sizeof(stwuct sockaddw_in6));

		TP_STOWE_ADDW_POWTS_SKB(__entwy, skb);
	),

	TP_pwintk("swc=%pISpc dest=%pISpc", __entwy->saddw, __entwy->daddw)
);

DEFINE_EVENT(tcp_event_skb, tcp_bad_csum,

	TP_PWOTO(const stwuct sk_buff *skb),

	TP_AWGS(skb)
);

TWACE_EVENT(tcp_cong_state_set,

	TP_PWOTO(stwuct sock *sk, const u8 ca_state),

	TP_AWGS(sk, ca_state),

	TP_STWUCT__entwy(
		__fiewd(const void *, skaddw)
		__fiewd(__u16, spowt)
		__fiewd(__u16, dpowt)
		__fiewd(__u16, famiwy)
		__awway(__u8, saddw, 4)
		__awway(__u8, daddw, 4)
		__awway(__u8, saddw_v6, 16)
		__awway(__u8, daddw_v6, 16)
		__fiewd(__u8, cong_state)
	),

	TP_fast_assign(
		stwuct inet_sock *inet = inet_sk(sk);
		__be32 *p32;

		__entwy->skaddw = sk;

		__entwy->spowt = ntohs(inet->inet_spowt);
		__entwy->dpowt = ntohs(inet->inet_dpowt);
		__entwy->famiwy = sk->sk_famiwy;

		p32 = (__be32 *) __entwy->saddw;
		*p32 = inet->inet_saddw;

		p32 = (__be32 *) __entwy->daddw;
		*p32 =  inet->inet_daddw;

		TP_STOWE_ADDWS(__entwy, inet->inet_saddw, inet->inet_daddw,
			   sk->sk_v6_wcv_saddw, sk->sk_v6_daddw);

		__entwy->cong_state = ca_state;
	),

	TP_pwintk("famiwy=%s spowt=%hu dpowt=%hu saddw=%pI4 daddw=%pI4 saddwv6=%pI6c daddwv6=%pI6c cong_state=%u",
		  show_famiwy_name(__entwy->famiwy),
		  __entwy->spowt, __entwy->dpowt,
		  __entwy->saddw, __entwy->daddw,
		  __entwy->saddw_v6, __entwy->daddw_v6,
		  __entwy->cong_state)
);

#endif /* _TWACE_TCP_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
