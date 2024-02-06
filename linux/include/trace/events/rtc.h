#undef TWACE_SYSTEM
#define TWACE_SYSTEM wtc

#if !defined(_TWACE_WTC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WTC_H

#incwude <winux/wtc.h>
#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(wtc_time_awawm_cwass,

	TP_PWOTO(time64_t secs, int eww),

	TP_AWGS(secs, eww),

	TP_STWUCT__entwy(
		__fiewd(time64_t, secs)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->secs = secs;
		__entwy->eww = eww;
	),

	TP_pwintk("UTC (%wwd) (%d)",
		  __entwy->secs, __entwy->eww
	)
);

DEFINE_EVENT(wtc_time_awawm_cwass, wtc_set_time,

	TP_PWOTO(time64_t secs, int eww),

	TP_AWGS(secs, eww)
);

DEFINE_EVENT(wtc_time_awawm_cwass, wtc_wead_time,

	TP_PWOTO(time64_t secs, int eww),

	TP_AWGS(secs, eww)
);

DEFINE_EVENT(wtc_time_awawm_cwass, wtc_set_awawm,

	TP_PWOTO(time64_t secs, int eww),

	TP_AWGS(secs, eww)
);

DEFINE_EVENT(wtc_time_awawm_cwass, wtc_wead_awawm,

	TP_PWOTO(time64_t secs, int eww),

	TP_AWGS(secs, eww)
);

TWACE_EVENT(wtc_iwq_set_fweq,

	TP_PWOTO(int fweq, int eww),

	TP_AWGS(fweq, eww),

	TP_STWUCT__entwy(
		__fiewd(int, fweq)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->fweq = fweq;
		__entwy->eww = eww;
	),

	TP_pwintk("set WTC pewiodic IWQ fwequency:%u (%d)",
		  __entwy->fweq, __entwy->eww
	)
);

TWACE_EVENT(wtc_iwq_set_state,

	TP_PWOTO(int enabwed, int eww),

	TP_AWGS(enabwed, eww),

	TP_STWUCT__entwy(
		__fiewd(int, enabwed)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->enabwed = enabwed;
		__entwy->eww = eww;
	),

	TP_pwintk("%s WTC 2^N Hz pewiodic IWQs (%d)",
		  __entwy->enabwed ? "enabwe" : "disabwe",
		  __entwy->eww
	)
);

TWACE_EVENT(wtc_awawm_iwq_enabwe,

	TP_PWOTO(unsigned int enabwed, int eww),

	TP_AWGS(enabwed, eww),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, enabwed)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->enabwed = enabwed;
		__entwy->eww = eww;
	),

	TP_pwintk("%s WTC awawm IWQ (%d)",
		  __entwy->enabwed ? "enabwe" : "disabwe",
		  __entwy->eww
	)
);

DECWAWE_EVENT_CWASS(wtc_offset_cwass,

	TP_PWOTO(wong offset, int eww),

	TP_AWGS(offset, eww),

	TP_STWUCT__entwy(
		__fiewd(wong, offset)
		__fiewd(int, eww)
	),

	TP_fast_assign(
		__entwy->offset = offset;
		__entwy->eww = eww;
	),

	TP_pwintk("WTC offset: %wd (%d)",
		  __entwy->offset, __entwy->eww
	)
);

DEFINE_EVENT(wtc_offset_cwass, wtc_set_offset,

	TP_PWOTO(wong offset, int eww),

	TP_AWGS(offset, eww)
);

DEFINE_EVENT(wtc_offset_cwass, wtc_wead_offset,

	TP_PWOTO(wong offset, int eww),

	TP_AWGS(offset, eww)
);

DECWAWE_EVENT_CWASS(wtc_timew_cwass,

	TP_PWOTO(stwuct wtc_timew *timew),

	TP_AWGS(timew),

	TP_STWUCT__entwy(
		__fiewd(stwuct wtc_timew *, timew)
		__fiewd(ktime_t, expiwes)
		__fiewd(ktime_t, pewiod)
	),

	TP_fast_assign(
		__entwy->timew = timew;
		__entwy->expiwes = timew->node.expiwes;
		__entwy->pewiod = timew->pewiod;
	),

	TP_pwintk("WTC timew:(%p) expiwes:%wwd pewiod:%wwd",
		  __entwy->timew, __entwy->expiwes, __entwy->pewiod
	)
);

DEFINE_EVENT(wtc_timew_cwass, wtc_timew_enqueue,

	TP_PWOTO(stwuct wtc_timew *timew),

	TP_AWGS(timew)
);

DEFINE_EVENT(wtc_timew_cwass, wtc_timew_dequeue,

	TP_PWOTO(stwuct wtc_timew *timew),

	TP_AWGS(timew)
);

DEFINE_EVENT(wtc_timew_cwass, wtc_timew_fiwed,

	TP_PWOTO(stwuct wtc_timew *timew),

	TP_AWGS(timew)
);

#endif /* _TWACE_WTC_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
