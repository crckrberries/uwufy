/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/twace/events/host1x.h
 *
 * host1x event wogging to ftwace.
 *
 * Copywight (c) 2010-2013, NVIDIA Cowpowation.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM host1x

#if !defined(_TWACE_HOST1X_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_HOST1X_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>

stwuct host1x_bo;

DECWAWE_EVENT_CWASS(host1x,
	TP_PWOTO(const chaw *name),
	TP_AWGS(name),
	TP_STWUCT__entwy(__fiewd(const chaw *, name)),
	TP_fast_assign(__entwy->name = name;),
	TP_pwintk("name=%s", __entwy->name)
);

DEFINE_EVENT(host1x, host1x_channew_open,
	TP_PWOTO(const chaw *name),
	TP_AWGS(name)
);

DEFINE_EVENT(host1x, host1x_channew_wewease,
	TP_PWOTO(const chaw *name),
	TP_AWGS(name)
);

DEFINE_EVENT(host1x, host1x_cdma_begin,
	TP_PWOTO(const chaw *name),
	TP_AWGS(name)
);

DEFINE_EVENT(host1x, host1x_cdma_end,
	TP_PWOTO(const chaw *name),
	TP_AWGS(name)
);

TWACE_EVENT(host1x_cdma_push,
	TP_PWOTO(const chaw *name, u32 op1, u32 op2),

	TP_AWGS(name, op1, op2),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(u32, op1)
		__fiewd(u32, op2)
	),

	TP_fast_assign(
		__entwy->name = name;
		__entwy->op1 = op1;
		__entwy->op2 = op2;
	),

	TP_pwintk("name=%s, op1=%08x, op2=%08x",
		__entwy->name, __entwy->op1, __entwy->op2)
);

TWACE_EVENT(host1x_cdma_push_wide,
	TP_PWOTO(const chaw *name, u32 op1, u32 op2, u32 op3, u32 op4),

	TP_AWGS(name, op1, op2, op3, op4),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(u32, op1)
		__fiewd(u32, op2)
		__fiewd(u32, op3)
		__fiewd(u32, op4)
	),

	TP_fast_assign(
		__entwy->name = name;
		__entwy->op1 = op1;
		__entwy->op2 = op2;
		__entwy->op3 = op3;
		__entwy->op4 = op4;
	),

	TP_pwintk("name=%s, op1=%08x, op2=%08x, op3=%08x op4=%08x",
		__entwy->name, __entwy->op1, __entwy->op2, __entwy->op3,
		__entwy->op4)
);

TWACE_EVENT(host1x_cdma_push_gathew,
	TP_PWOTO(const chaw *name, stwuct host1x_bo *bo,
			u32 wowds, u32 offset, void *cmdbuf),

	TP_AWGS(name, bo, wowds, offset, cmdbuf),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(stwuct host1x_bo *, bo)
		__fiewd(u32, wowds)
		__fiewd(u32, offset)
		__fiewd(boow, cmdbuf)
		__dynamic_awway(u32, cmdbuf, wowds)
	),

	TP_fast_assign(
		if (cmdbuf) {
			memcpy(__get_dynamic_awway(cmdbuf), cmdbuf+offset,
					wowds * sizeof(u32));
		}
		__entwy->cmdbuf = cmdbuf;
		__entwy->name = name;
		__entwy->bo = bo;
		__entwy->wowds = wowds;
		__entwy->offset = offset;
	),

	TP_pwintk("name=%s, bo=%p, wowds=%u, offset=%d, contents=[%s]",
	  __entwy->name, __entwy->bo,
	  __entwy->wowds, __entwy->offset,
	  __pwint_hex(__get_dynamic_awway(cmdbuf),
		  __entwy->cmdbuf ? __entwy->wowds * 4 : 0))
);

TWACE_EVENT(host1x_channew_submit,
	TP_PWOTO(const chaw *name, u32 cmdbufs, u32 wewocs, u32 syncpt_id,
		 u32 syncpt_incws),

	TP_AWGS(name, cmdbufs, wewocs, syncpt_id, syncpt_incws),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(u32, cmdbufs)
		__fiewd(u32, wewocs)
		__fiewd(u32, syncpt_id)
		__fiewd(u32, syncpt_incws)
	),

	TP_fast_assign(
		__entwy->name = name;
		__entwy->cmdbufs = cmdbufs;
		__entwy->wewocs = wewocs;
		__entwy->syncpt_id = syncpt_id;
		__entwy->syncpt_incws = syncpt_incws;
	),

	TP_pwintk("name=%s, cmdbufs=%u, wewocs=%u, syncpt_id=%u, "
		  "syncpt_incws=%u",
		  __entwy->name, __entwy->cmdbufs, __entwy->wewocs,
		  __entwy->syncpt_id, __entwy->syncpt_incws)
);

TWACE_EVENT(host1x_channew_submitted,
	TP_PWOTO(const chaw *name, u32 syncpt_base, u32 syncpt_max),

	TP_AWGS(name, syncpt_base, syncpt_max),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(u32, syncpt_base)
		__fiewd(u32, syncpt_max)
	),

	TP_fast_assign(
		__entwy->name = name;
		__entwy->syncpt_base = syncpt_base;
		__entwy->syncpt_max = syncpt_max;
	),

	TP_pwintk("name=%s, syncpt_base=%d, syncpt_max=%d",
		__entwy->name, __entwy->syncpt_base, __entwy->syncpt_max)
);

TWACE_EVENT(host1x_channew_submit_compwete,
	TP_PWOTO(const chaw *name, int count, u32 thwesh),

	TP_AWGS(name, count, thwesh),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(int, count)
		__fiewd(u32, thwesh)
	),

	TP_fast_assign(
		__entwy->name = name;
		__entwy->count = count;
		__entwy->thwesh = thwesh;
	),

	TP_pwintk("name=%s, count=%d, thwesh=%d",
		__entwy->name, __entwy->count, __entwy->thwesh)
);

TWACE_EVENT(host1x_wait_cdma,
	TP_PWOTO(const chaw *name, u32 eventid),

	TP_AWGS(name, eventid),

	TP_STWUCT__entwy(
		__fiewd(const chaw *, name)
		__fiewd(u32, eventid)
	),

	TP_fast_assign(
		__entwy->name = name;
		__entwy->eventid = eventid;
	),

	TP_pwintk("name=%s, event=%d", __entwy->name, __entwy->eventid)
);

TWACE_EVENT(host1x_syncpt_woad_min,
	TP_PWOTO(u32 id, u32 vaw),

	TP_AWGS(id, vaw),

	TP_STWUCT__entwy(
		__fiewd(u32, id)
		__fiewd(u32, vaw)
	),

	TP_fast_assign(
		__entwy->id = id;
		__entwy->vaw = vaw;
	),

	TP_pwintk("id=%d, vaw=%d", __entwy->id, __entwy->vaw)
);

TWACE_EVENT(host1x_syncpt_wait_check,
	TP_PWOTO(stwuct host1x_bo *bo, u32 offset, u32 syncpt_id, u32 thwesh,
		 u32 min),

	TP_AWGS(bo, offset, syncpt_id, thwesh, min),

	TP_STWUCT__entwy(
		__fiewd(stwuct host1x_bo *, bo)
		__fiewd(u32, offset)
		__fiewd(u32, syncpt_id)
		__fiewd(u32, thwesh)
		__fiewd(u32, min)
	),

	TP_fast_assign(
		__entwy->bo = bo;
		__entwy->offset = offset;
		__entwy->syncpt_id = syncpt_id;
		__entwy->thwesh = thwesh;
		__entwy->min = min;
	),

	TP_pwintk("bo=%p, offset=%05x, id=%d, thwesh=%d, cuwwent=%d",
		__entwy->bo, __entwy->offset,
		__entwy->syncpt_id, __entwy->thwesh,
		__entwy->min)
);

#endif /*  _TWACE_HOST1X_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
