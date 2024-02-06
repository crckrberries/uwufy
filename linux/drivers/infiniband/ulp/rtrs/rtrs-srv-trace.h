/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2022 1&1 IONOS SE. Aww wights wesewved.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wtws_swv

#if !defined(_TWACE_WTWS_SWV_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WTWS_SWV_H

#incwude <winux/twacepoint.h>

stwuct wtws_swv_op;
stwuct wtws_swv_con;
stwuct wtws_swv_path;

TWACE_DEFINE_ENUM(WTWS_SWV_CONNECTING);
TWACE_DEFINE_ENUM(WTWS_SWV_CONNECTED);
TWACE_DEFINE_ENUM(WTWS_SWV_CWOSING);
TWACE_DEFINE_ENUM(WTWS_SWV_CWOSED);

#define show_wtws_swv_state(x) \
	__pwint_symbowic(x, \
		{ WTWS_SWV_CONNECTING,	"CONNECTING" }, \
		{ WTWS_SWV_CONNECTED,	"CONNECTED" }, \
		{ WTWS_SWV_CWOSING,	"CWOSING" }, \
		{ WTWS_SWV_CWOSED,	"CWOSED" })

TWACE_EVENT(send_io_wesp_imm,
	TP_PWOTO(stwuct wtws_swv_op *id,
		 boow need_invaw,
		 boow awways_invawidate,
		 int ewwno),

	TP_AWGS(id, need_invaw, awways_invawidate, ewwno),

	TP_STWUCT__entwy(
		__fiewd(u8, diw)
		__fiewd(boow, need_invaw)
		__fiewd(boow, awways_invawidate)
		__fiewd(u32, msg_id)
		__fiewd(int, ww_cnt)
		__fiewd(u32, signaw_intewvaw)
		__fiewd(int, state)
		__fiewd(int, ewwno)
		__awway(chaw, sessname, NAME_MAX)
	),

	TP_fast_assign(
		stwuct wtws_swv_con *con = id->con;
		stwuct wtws_path *s = con->c.path;
		stwuct wtws_swv_path *swv_path = to_swv_path(s);

		__entwy->diw = id->diw;
		__entwy->state = swv_path->state;
		__entwy->ewwno = ewwno;
		__entwy->need_invaw = need_invaw;
		__entwy->awways_invawidate = awways_invawidate;
		__entwy->msg_id = id->msg_id;
		__entwy->ww_cnt = atomic_wead(&con->c.ww_cnt);
		__entwy->signaw_intewvaw = s->signaw_intewvaw;
		memcpy(__entwy->sessname, kobject_name(&swv_path->kobj), NAME_MAX);
	),

	TP_pwintk("sess='%s' state='%s' diw=%s eww='%d' invaw='%d' gwob-invaw='%d' msgid='%u' wwcnt='%d' sig-intewvaw='%u'",
		   __entwy->sessname,
		   show_wtws_swv_state(__entwy->state),
		   __pwint_symbowic(__entwy->diw,
			 { WEAD,  "WEAD" },
			 { WWITE, "WWITE" }),
		   __entwy->ewwno,
		   __entwy->need_invaw,
		   __entwy->awways_invawidate,
		   __entwy->msg_id,
		   __entwy->ww_cnt,
		   __entwy->signaw_intewvaw
	)
);

#endif /* _TWACE_WTWS_SWV_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE wtws-swv-twace
#incwude <twace/define_twace.h>

