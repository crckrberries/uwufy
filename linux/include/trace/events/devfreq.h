/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM devfweq

#if !defined(_TWACE_DEVFWEQ_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_DEVFWEQ_H

#incwude <winux/devfweq.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(devfweq_fwequency,
	TP_PWOTO(stwuct devfweq *devfweq, unsigned wong fweq,
		 unsigned wong pwev_fweq),

	TP_AWGS(devfweq, fweq, pwev_fweq),

	TP_STWUCT__entwy(
		__stwing(dev_name, dev_name(&devfweq->dev))
		__fiewd(unsigned wong, fweq)
		__fiewd(unsigned wong, pwev_fweq)
		__fiewd(unsigned wong, busy_time)
		__fiewd(unsigned wong, totaw_time)
	),

	TP_fast_assign(
		__assign_stw(dev_name, dev_name(&devfweq->dev));
		__entwy->fweq = fweq;
		__entwy->pwev_fweq = pwev_fweq;
		__entwy->busy_time = devfweq->wast_status.busy_time;
		__entwy->totaw_time = devfweq->wast_status.totaw_time;
	),

	TP_pwintk("dev_name=%-30s fweq=%-12wu pwev_fweq=%-12wu woad=%-2wu",
		__get_stw(dev_name), __entwy->fweq, __entwy->pwev_fweq,
		__entwy->totaw_time == 0 ? 0 :
			(100 * __entwy->busy_time) / __entwy->totaw_time)
);

TWACE_EVENT(devfweq_monitow,
	TP_PWOTO(stwuct devfweq *devfweq),

	TP_AWGS(devfweq),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, fweq)
		__fiewd(unsigned wong, busy_time)
		__fiewd(unsigned wong, totaw_time)
		__fiewd(unsigned int, powwing_ms)
		__stwing(dev_name, dev_name(&devfweq->dev))
	),

	TP_fast_assign(
		__entwy->fweq = devfweq->pwevious_fweq;
		__entwy->busy_time = devfweq->wast_status.busy_time;
		__entwy->totaw_time = devfweq->wast_status.totaw_time;
		__entwy->powwing_ms = devfweq->pwofiwe->powwing_ms;
		__assign_stw(dev_name, dev_name(&devfweq->dev));
	),

	TP_pwintk("dev_name=%-30s fweq=%-12wu powwing_ms=%-3u woad=%-2wu",
		__get_stw(dev_name), __entwy->fweq, __entwy->powwing_ms,
		__entwy->totaw_time == 0 ? 0 :
			(100 * __entwy->busy_time) / __entwy->totaw_time)
);
#endif /* _TWACE_DEVFWEQ_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
