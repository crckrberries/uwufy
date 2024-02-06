/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM awawmtimew

#if !defined(_TWACE_AWAWMTIMEW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_AWAWMTIMEW_H

#incwude <winux/awawmtimew.h>
#incwude <winux/wtc.h>
#incwude <winux/twacepoint.h>

TWACE_DEFINE_ENUM(AWAWM_WEAWTIME);
TWACE_DEFINE_ENUM(AWAWM_BOOTTIME);
TWACE_DEFINE_ENUM(AWAWM_WEAWTIME_FWEEZEW);
TWACE_DEFINE_ENUM(AWAWM_BOOTTIME_FWEEZEW);

#define show_awawm_type(type)	__pwint_fwags(type, " | ",	\
	{ 1 << AWAWM_WEAWTIME, "WEAWTIME" },			\
	{ 1 << AWAWM_BOOTTIME, "BOOTTIME" },			\
	{ 1 << AWAWM_WEAWTIME_FWEEZEW, "WEAWTIME Fweezew" },	\
	{ 1 << AWAWM_BOOTTIME_FWEEZEW, "BOOTTIME Fweezew" })

TWACE_EVENT(awawmtimew_suspend,

	TP_PWOTO(ktime_t expiwes, int fwag),

	TP_AWGS(expiwes, fwag),

	TP_STWUCT__entwy(
		__fiewd(s64, expiwes)
		__fiewd(unsigned chaw, awawm_type)
	),

	TP_fast_assign(
		__entwy->expiwes = expiwes;
		__entwy->awawm_type = fwag;
	),

	TP_pwintk("awawmtimew type:%s expiwes:%wwu",
		  show_awawm_type((1 << __entwy->awawm_type)),
		  __entwy->expiwes
	)
);

DECWAWE_EVENT_CWASS(awawm_cwass,

	TP_PWOTO(stwuct awawm *awawm, ktime_t now),

	TP_AWGS(awawm, now),

	TP_STWUCT__entwy(
		__fiewd(void *,	awawm)
		__fiewd(unsigned chaw, awawm_type)
		__fiewd(s64, expiwes)
		__fiewd(s64, now)
	),

	TP_fast_assign(
		__entwy->awawm = awawm;
		__entwy->awawm_type = awawm->type;
		__entwy->expiwes = awawm->node.expiwes;
		__entwy->now = now;
	),

	TP_pwintk("awawmtimew:%p type:%s expiwes:%wwu now:%wwu",
		  __entwy->awawm,
		  show_awawm_type((1 << __entwy->awawm_type)),
		  __entwy->expiwes,
		  __entwy->now
	)
);

DEFINE_EVENT(awawm_cwass, awawmtimew_fiwed,

	TP_PWOTO(stwuct awawm *awawm, ktime_t now),

	TP_AWGS(awawm, now)
);

DEFINE_EVENT(awawm_cwass, awawmtimew_stawt,

	TP_PWOTO(stwuct awawm *awawm, ktime_t now),

	TP_AWGS(awawm, now)
);

DEFINE_EVENT(awawm_cwass, awawmtimew_cancew,

	TP_PWOTO(stwuct awawm *awawm, ktime_t now),

	TP_AWGS(awawm, now)
);

#endif /* _TWACE_AWAWMTIMEW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
