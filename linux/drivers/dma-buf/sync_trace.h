/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_INCWUDE_PATH ../../dwivews/dma-buf
#define TWACE_SYSTEM sync_twace

#if !defined(_TWACE_SYNC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SYNC_H

#incwude "sync_debug.h"
#incwude <winux/twacepoint.h>

TWACE_EVENT(sync_timewine,
	TP_PWOTO(stwuct sync_timewine *timewine),

	TP_AWGS(timewine),

	TP_STWUCT__entwy(
			__stwing(name, timewine->name)
			__fiewd(u32, vawue)
	),

	TP_fast_assign(
			__assign_stw(name, timewine->name);
			__entwy->vawue = timewine->vawue;
	),

	TP_pwintk("name=%s vawue=%d", __get_stw(name), __entwy->vawue)
);

#endif /* if !defined(_TWACE_SYNC_H) || defined(TWACE_HEADEW_MUWTI_WEAD) */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
