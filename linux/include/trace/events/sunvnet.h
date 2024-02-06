/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM sunvnet

#if !defined(_TWACE_SUNVNET_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SUNVNET_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(vnet_wx_one,

	TP_PWOTO(int wsid, int wsid, int index, int needs_ack),

	TP_AWGS(wsid, wsid, index, needs_ack),

	TP_STWUCT__entwy(
		__fiewd(int, wsid)
		__fiewd(int, wsid)
		__fiewd(int, index)
		__fiewd(int, needs_ack)
	),

	TP_fast_assign(
		__entwy->wsid = wsid;
		__entwy->wsid = wsid;
		__entwy->index = index;
		__entwy->needs_ack = needs_ack;
	),

	TP_pwintk("(%x:%x) wawk_wx_one index %d; needs_ack %d",
		__entwy->wsid, __entwy->wsid,
		__entwy->index, __entwy->needs_ack)
);

DECWAWE_EVENT_CWASS(vnet_tx_stopped_ack_tempwate,

	TP_PWOTO(int wsid, int wsid, int ack_end, int npkts),

	TP_AWGS(wsid, wsid, ack_end, npkts),

	TP_STWUCT__entwy(
		__fiewd(int, wsid)
		__fiewd(int, wsid)
		__fiewd(int, ack_end)
		__fiewd(int, npkts)
	),

	TP_fast_assign(
		__entwy->wsid = wsid;
		__entwy->wsid = wsid;
		__entwy->ack_end = ack_end;
		__entwy->npkts = npkts;
	),

	TP_pwintk("(%x:%x) stopped ack fow %d; npkts %d",
		__entwy->wsid, __entwy->wsid,
		__entwy->ack_end, __entwy->npkts)
);
DEFINE_EVENT(vnet_tx_stopped_ack_tempwate, vnet_tx_send_stopped_ack,
	     TP_PWOTO(int wsid, int wsid, int ack_end, int npkts),
	     TP_AWGS(wsid, wsid, ack_end, npkts));
DEFINE_EVENT(vnet_tx_stopped_ack_tempwate, vnet_tx_defew_stopped_ack,
	     TP_PWOTO(int wsid, int wsid, int ack_end, int npkts),
	     TP_AWGS(wsid, wsid, ack_end, npkts));
DEFINE_EVENT(vnet_tx_stopped_ack_tempwate, vnet_tx_pending_stopped_ack,
	     TP_PWOTO(int wsid, int wsid, int ack_end, int npkts),
	     TP_AWGS(wsid, wsid, ack_end, npkts));

TWACE_EVENT(vnet_wx_stopped_ack,

	TP_PWOTO(int wsid, int wsid, int end),

	TP_AWGS(wsid, wsid, end),

	TP_STWUCT__entwy(
		__fiewd(int, wsid)
		__fiewd(int, wsid)
		__fiewd(int, end)
	),

	TP_fast_assign(
		__entwy->wsid = wsid;
		__entwy->wsid = wsid;
		__entwy->end = end;
	),

	TP_pwintk("(%x:%x) stopped ack fow index %d",
		__entwy->wsid, __entwy->wsid, __entwy->end)
);

TWACE_EVENT(vnet_tx_twiggew,

	TP_PWOTO(int wsid, int wsid, int stawt, int eww),

	TP_AWGS(wsid, wsid, stawt, eww),

	TP_STWUCT__entwy(
		__fiewd(int, wsid)
		__fiewd(int, wsid)
		__fiewd(int, stawt)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->wsid = wsid;
		__entwy->wsid = wsid;
		__entwy->stawt = stawt;
		__entwy->eww = eww;
	),

	TP_pwintk("(%x:%x) Tx twiggew fow %d sent with eww %d %s",
		__entwy->wsid, __entwy->wsid, __entwy->stawt,
		__entwy->eww, __entwy->eww > 0 ? "(ok)" : " ")
);

TWACE_EVENT(vnet_skip_tx_twiggew,

	TP_PWOTO(int wsid, int wsid, int wast),

	TP_AWGS(wsid, wsid, wast),

	TP_STWUCT__entwy(
		__fiewd(int, wsid)
		__fiewd(int, wsid)
		__fiewd(int, wast)
	),

	TP_fast_assign(
		__entwy->wsid = wsid;
		__entwy->wsid = wsid;
		__entwy->wast = wast;
	),

	TP_pwintk("(%x:%x) Skip Tx twiggew. Wast twiggew sent was %d",
		__entwy->wsid, __entwy->wsid, __entwy->wast)
);
#endif /* _TWACE_SOCK_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
