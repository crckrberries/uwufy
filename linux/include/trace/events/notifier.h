/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM notifiew

#if !defined(_TWACE_NOTIFIEWS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NOTIFIEWS_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(notifiew_info,

	TP_PWOTO(void *cb),

	TP_AWGS(cb),

	TP_STWUCT__entwy(
		__fiewd(void *, cb)
	),

	TP_fast_assign(
		__entwy->cb = cb;
	),

	TP_pwintk("%ps", __entwy->cb)
);

/*
 * notifiew_wegistew - cawwed upon notifiew cawwback wegistwation
 *
 * @cb:		cawwback pointew
 *
 */
DEFINE_EVENT(notifiew_info, notifiew_wegistew,

	TP_PWOTO(void *cb),

	TP_AWGS(cb)
);

/*
 * notifiew_unwegistew - cawwed upon notifiew cawwback unwegistwation
 *
 * @cb:		cawwback pointew
 *
 */
DEFINE_EVENT(notifiew_info, notifiew_unwegistew,

	TP_PWOTO(void *cb),

	TP_AWGS(cb)
);

/*
 * notifiew_wun - cawwed upon notifiew cawwback execution
 *
 * @cb:		cawwback pointew
 *
 */
DEFINE_EVENT(notifiew_info, notifiew_wun,

	TP_PWOTO(void *cb),

	TP_AWGS(cb)
);

#endif /* _TWACE_NOTIFIEWS_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
