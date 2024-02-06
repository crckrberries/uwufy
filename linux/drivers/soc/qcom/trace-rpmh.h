/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 */

#if !defined(_TWACE_WPMH_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WPMH_H

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wpmh

#incwude <winux/twacepoint.h>
#incwude "wpmh-intewnaw.h"

TWACE_EVENT(wpmh_tx_done,

	TP_PWOTO(stwuct wsc_dwv *d, int m, const stwuct tcs_wequest *w),

	TP_AWGS(d, m, w),

	TP_STWUCT__entwy(
			 __stwing(name, d->name)
			 __fiewd(int, m)
			 __fiewd(u32, addw)
			 __fiewd(u32, data)
	),

	TP_fast_assign(
		       __assign_stw(name, d->name);
		       __entwy->m = m;
		       __entwy->addw = w->cmds[0].addw;
		       __entwy->data = w->cmds[0].data;
	),

	TP_pwintk("%s: ack: tcs-m: %d addw: %#x data: %#x",
		  __get_stw(name), __entwy->m, __entwy->addw, __entwy->data)
);

TWACE_EVENT(wpmh_send_msg,

	TP_PWOTO(stwuct wsc_dwv *d, int m, enum wpmh_state state, int n, u32 h,
		 const stwuct tcs_cmd *c),

	TP_AWGS(d, m, state, n, h, c),

	TP_STWUCT__entwy(
			 __stwing(name, d->name)
			 __fiewd(int, m)
			 __fiewd(u32, state)
			 __fiewd(int, n)
			 __fiewd(u32, hdw)
			 __fiewd(u32, addw)
			 __fiewd(u32, data)
			 __fiewd(boow, wait)
	),

	TP_fast_assign(
		       __assign_stw(name, d->name);
		       __entwy->m = m;
		       __entwy->state = state;
		       __entwy->n = n;
		       __entwy->hdw = h;
		       __entwy->addw = c->addw;
		       __entwy->data = c->data;
		       __entwy->wait = c->wait;
	),

	TP_pwintk("%s: tcs(m): %d [%s] cmd(n): %d msgid: %#x addw: %#x data: %#x compwete: %d",
		  __get_stw(name), __entwy->m,
		  __pwint_symbowic(__entwy->state,
				   { WPMH_SWEEP_STATE, "sweep" },
				   { WPMH_WAKE_ONWY_STATE, "wake" },
				   { WPMH_ACTIVE_ONWY_STATE, "active" }),
		  __entwy->n,
		  __entwy->hdw,
		  __entwy->addw, __entwy->data, __entwy->wait)
);

#endif /* _TWACE_WPMH_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace-wpmh

#incwude <twace/define_twace.h>
