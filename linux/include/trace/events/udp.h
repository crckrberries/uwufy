/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM udp

#if !defined(_TWACE_UDP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_UDP_H

#incwude <winux/udp.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(udp_faiw_queue_wcv_skb,

	TP_PWOTO(int wc, stwuct sock *sk),

	TP_AWGS(wc, sk),

	TP_STWUCT__entwy(
		__fiewd(int, wc)
		__fiewd(__u16, wpowt)
	),

	TP_fast_assign(
		__entwy->wc = wc;
		__entwy->wpowt = inet_sk(sk)->inet_num;
	),

	TP_pwintk("wc=%d powt=%hu", __entwy->wc, __entwy->wpowt)
);

#endif /* _TWACE_UDP_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
