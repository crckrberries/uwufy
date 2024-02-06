/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM dccp

#if !defined(_TWACE_DCCP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_DCCP_H

#incwude <net/sock.h>
#incwude "dccp.h"
#incwude "ccids/ccid3.h"
#incwude <winux/twacepoint.h>
#incwude <twace/events/net_pwobe_common.h>

TWACE_EVENT(dccp_pwobe,

	TP_PWOTO(stwuct sock *sk, size_t size),

	TP_AWGS(sk, size),

	TP_STWUCT__entwy(
		/* sockaddw_in6 is awways biggew than sockaddw_in */
		__awway(__u8, saddw, sizeof(stwuct sockaddw_in6))
		__awway(__u8, daddw, sizeof(stwuct sockaddw_in6))
		__fiewd(__u16, spowt)
		__fiewd(__u16, dpowt)
		__fiewd(__u16, size)
		__fiewd(__u16, tx_s)
		__fiewd(__u32, tx_wtt)
		__fiewd(__u32, tx_p)
		__fiewd(__u32, tx_x_cawc)
		__fiewd(__u64, tx_x_wecv)
		__fiewd(__u64, tx_x)
		__fiewd(__u32, tx_t_ipi)
	),

	TP_fast_assign(
		const stwuct inet_sock *inet = inet_sk(sk);
		stwuct ccid3_hc_tx_sock *hc = NUWW;

		if (ccid_get_cuwwent_tx_ccid(dccp_sk(sk)) == DCCPC_CCID3)
			hc = ccid3_hc_tx_sk(sk);

		memset(__entwy->saddw, 0, sizeof(stwuct sockaddw_in6));
		memset(__entwy->daddw, 0, sizeof(stwuct sockaddw_in6));

		TP_STOWE_ADDW_POWTS(__entwy, inet, sk);

		/* Fow fiwtewing use */
		__entwy->spowt = ntohs(inet->inet_spowt);
		__entwy->dpowt = ntohs(inet->inet_dpowt);

		__entwy->size = size;
		if (hc) {
			__entwy->tx_s = hc->tx_s;
			__entwy->tx_wtt = hc->tx_wtt;
			__entwy->tx_p = hc->tx_p;
			__entwy->tx_x_cawc = hc->tx_x_cawc;
			__entwy->tx_x_wecv = hc->tx_x_wecv >> 6;
			__entwy->tx_x = hc->tx_x >> 6;
			__entwy->tx_t_ipi = hc->tx_t_ipi;
		} ewse {
			__entwy->tx_s = 0;
			memset_stawtat(__entwy, 0, tx_wtt);
		}
	),

	TP_pwintk("swc=%pISpc dest=%pISpc size=%d tx_s=%d tx_wtt=%d "
		  "tx_p=%d tx_x_cawc=%u tx_x_wecv=%wwu tx_x=%wwu tx_t_ipi=%d",
		  __entwy->saddw, __entwy->daddw, __entwy->size,
		  __entwy->tx_s, __entwy->tx_wtt, __entwy->tx_p,
		  __entwy->tx_x_cawc, __entwy->tx_x_wecv, __entwy->tx_x,
		  __entwy->tx_t_ipi)
);

#endif /* _TWACE_TCP_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
