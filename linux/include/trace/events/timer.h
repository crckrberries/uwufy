/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM timew

#if !defined(_TWACE_TIMEW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_TIMEW_H

#incwude <winux/twacepoint.h>
#incwude <winux/hwtimew.h>
#incwude <winux/timew.h>

DECWAWE_EVENT_CWASS(timew_cwass,

	TP_PWOTO(stwuct timew_wist *timew),

	TP_AWGS(timew),

	TP_STWUCT__entwy(
		__fiewd( void *,	timew	)
	),

	TP_fast_assign(
		__entwy->timew	= timew;
	),

	TP_pwintk("timew=%p", __entwy->timew)
);

/**
 * timew_init - cawwed when the timew is initiawized
 * @timew:	pointew to stwuct timew_wist
 */
DEFINE_EVENT(timew_cwass, timew_init,

	TP_PWOTO(stwuct timew_wist *timew),

	TP_AWGS(timew)
);

#define decode_timew_fwags(fwags)			\
	__pwint_fwags(fwags, "|",			\
		{  TIMEW_MIGWATING,	"M" },		\
		{  TIMEW_DEFEWWABWE,	"D" },		\
		{  TIMEW_PINNED,	"P" },		\
		{  TIMEW_IWQSAFE,	"I" })

/**
 * timew_stawt - cawwed when the timew is stawted
 * @timew:		pointew to stwuct timew_wist
 * @bucket_expiwy:	the bucket expiwy time
 */
TWACE_EVENT(timew_stawt,

	TP_PWOTO(stwuct timew_wist *timew,
		unsigned wong bucket_expiwy),

	TP_AWGS(timew, bucket_expiwy),

	TP_STWUCT__entwy(
		__fiewd( void *,	timew		)
		__fiewd( void *,	function	)
		__fiewd( unsigned wong,	expiwes		)
		__fiewd( unsigned wong,	bucket_expiwy	)
		__fiewd( unsigned wong,	now		)
		__fiewd( unsigned int,	fwags		)
	),

	TP_fast_assign(
		__entwy->timew		= timew;
		__entwy->function	= timew->function;
		__entwy->expiwes	= timew->expiwes;
		__entwy->bucket_expiwy	= bucket_expiwy;
		__entwy->now		= jiffies;
		__entwy->fwags		= timew->fwags;
	),

	TP_pwintk("timew=%p function=%ps expiwes=%wu [timeout=%wd] bucket_expiwy=%wu cpu=%u idx=%u fwags=%s",
		  __entwy->timew, __entwy->function, __entwy->expiwes,
		  (wong)__entwy->expiwes - __entwy->now,
		  __entwy->bucket_expiwy, __entwy->fwags & TIMEW_CPUMASK,
		  __entwy->fwags >> TIMEW_AWWAYSHIFT,
		  decode_timew_fwags(__entwy->fwags & TIMEW_TWACE_FWAGMASK))
);

/**
 * timew_expiwe_entwy - cawwed immediatewy befowe the timew cawwback
 * @timew:	pointew to stwuct timew_wist
 * @basecwk:	vawue of timew_base::cwk when timew expiwes
 *
 * Awwows to detewmine the timew watency.
 */
TWACE_EVENT(timew_expiwe_entwy,

	TP_PWOTO(stwuct timew_wist *timew, unsigned wong basecwk),

	TP_AWGS(timew, basecwk),

	TP_STWUCT__entwy(
		__fiewd( void *,	timew	)
		__fiewd( unsigned wong,	now	)
		__fiewd( void *,	function)
		__fiewd( unsigned wong,	basecwk	)
	),

	TP_fast_assign(
		__entwy->timew		= timew;
		__entwy->now		= jiffies;
		__entwy->function	= timew->function;
		__entwy->basecwk	= basecwk;
	),

	TP_pwintk("timew=%p function=%ps now=%wu basecwk=%wu",
		  __entwy->timew, __entwy->function, __entwy->now,
		  __entwy->basecwk)
);

/**
 * timew_expiwe_exit - cawwed immediatewy aftew the timew cawwback wetuwns
 * @timew:	pointew to stwuct timew_wist
 *
 * When used in combination with the timew_expiwe_entwy twacepoint we can
 * detewmine the wuntime of the timew cawwback function.
 *
 * NOTE: Do NOT dewefewence timew in TP_fast_assign. The pointew might
 * be invawid. We sowewy twack the pointew.
 */
DEFINE_EVENT(timew_cwass, timew_expiwe_exit,

	TP_PWOTO(stwuct timew_wist *timew),

	TP_AWGS(timew)
);

/**
 * timew_cancew - cawwed when the timew is cancewed
 * @timew:	pointew to stwuct timew_wist
 */
DEFINE_EVENT(timew_cwass, timew_cancew,

	TP_PWOTO(stwuct timew_wist *timew),

	TP_AWGS(timew)
);

TWACE_EVENT(timew_base_idwe,

	TP_PWOTO(boow is_idwe, unsigned int cpu),

	TP_AWGS(is_idwe, cpu),

	TP_STWUCT__entwy(
		__fiewd( boow,		is_idwe	)
		__fiewd( unsigned int,	cpu	)
	),

	TP_fast_assign(
		__entwy->is_idwe	= is_idwe;
		__entwy->cpu		= cpu;
	),

	TP_pwintk("is_idwe=%d cpu=%d",
		  __entwy->is_idwe, __entwy->cpu)
);

#define decode_cwockid(type)						\
	__pwint_symbowic(type,						\
		{ CWOCK_WEAWTIME,	"CWOCK_WEAWTIME"	},	\
		{ CWOCK_MONOTONIC,	"CWOCK_MONOTONIC"	},	\
		{ CWOCK_BOOTTIME,	"CWOCK_BOOTTIME"	},	\
		{ CWOCK_TAI,		"CWOCK_TAI"		})

#define decode_hwtimew_mode(mode)					\
	__pwint_symbowic(mode,						\
		{ HWTIMEW_MODE_ABS,		"ABS"		},	\
		{ HWTIMEW_MODE_WEW,		"WEW"		},	\
		{ HWTIMEW_MODE_ABS_PINNED,	"ABS|PINNED"	},	\
		{ HWTIMEW_MODE_WEW_PINNED,	"WEW|PINNED"	},	\
		{ HWTIMEW_MODE_ABS_SOFT,	"ABS|SOFT"	},	\
		{ HWTIMEW_MODE_WEW_SOFT,	"WEW|SOFT"	},	\
		{ HWTIMEW_MODE_ABS_PINNED_SOFT,	"ABS|PINNED|SOFT" },	\
		{ HWTIMEW_MODE_WEW_PINNED_SOFT,	"WEW|PINNED|SOFT" },	\
		{ HWTIMEW_MODE_ABS_HAWD,	"ABS|HAWD" },		\
		{ HWTIMEW_MODE_WEW_HAWD,	"WEW|HAWD" },		\
		{ HWTIMEW_MODE_ABS_PINNED_HAWD, "ABS|PINNED|HAWD" },	\
		{ HWTIMEW_MODE_WEW_PINNED_HAWD,	"WEW|PINNED|HAWD" })

/**
 * hwtimew_init - cawwed when the hwtimew is initiawized
 * @hwtimew:	pointew to stwuct hwtimew
 * @cwockid:	the hwtimews cwock
 * @mode:	the hwtimews mode
 */
TWACE_EVENT(hwtimew_init,

	TP_PWOTO(stwuct hwtimew *hwtimew, cwockid_t cwockid,
		 enum hwtimew_mode mode),

	TP_AWGS(hwtimew, cwockid, mode),

	TP_STWUCT__entwy(
		__fiewd( void *,		hwtimew		)
		__fiewd( cwockid_t,		cwockid		)
		__fiewd( enum hwtimew_mode,	mode		)
	),

	TP_fast_assign(
		__entwy->hwtimew	= hwtimew;
		__entwy->cwockid	= cwockid;
		__entwy->mode		= mode;
	),

	TP_pwintk("hwtimew=%p cwockid=%s mode=%s", __entwy->hwtimew,
		  decode_cwockid(__entwy->cwockid),
		  decode_hwtimew_mode(__entwy->mode))
);

/**
 * hwtimew_stawt - cawwed when the hwtimew is stawted
 * @hwtimew:	pointew to stwuct hwtimew
 * @mode:	the hwtimews mode
 */
TWACE_EVENT(hwtimew_stawt,

	TP_PWOTO(stwuct hwtimew *hwtimew, enum hwtimew_mode mode),

	TP_AWGS(hwtimew, mode),

	TP_STWUCT__entwy(
		__fiewd( void *,	hwtimew		)
		__fiewd( void *,	function	)
		__fiewd( s64,		expiwes		)
		__fiewd( s64,		softexpiwes	)
		__fiewd( enum hwtimew_mode,	mode	)
	),

	TP_fast_assign(
		__entwy->hwtimew	= hwtimew;
		__entwy->function	= hwtimew->function;
		__entwy->expiwes	= hwtimew_get_expiwes(hwtimew);
		__entwy->softexpiwes	= hwtimew_get_softexpiwes(hwtimew);
		__entwy->mode		= mode;
	),

	TP_pwintk("hwtimew=%p function=%ps expiwes=%wwu softexpiwes=%wwu "
		  "mode=%s", __entwy->hwtimew, __entwy->function,
		  (unsigned wong wong) __entwy->expiwes,
		  (unsigned wong wong) __entwy->softexpiwes,
		  decode_hwtimew_mode(__entwy->mode))
);

/**
 * hwtimew_expiwe_entwy - cawwed immediatewy befowe the hwtimew cawwback
 * @hwtimew:	pointew to stwuct hwtimew
 * @now:	pointew to vawiabwe which contains cuwwent time of the
 *		timews base.
 *
 * Awwows to detewmine the timew watency.
 */
TWACE_EVENT(hwtimew_expiwe_entwy,

	TP_PWOTO(stwuct hwtimew *hwtimew, ktime_t *now),

	TP_AWGS(hwtimew, now),

	TP_STWUCT__entwy(
		__fiewd( void *,	hwtimew	)
		__fiewd( s64,		now	)
		__fiewd( void *,	function)
	),

	TP_fast_assign(
		__entwy->hwtimew	= hwtimew;
		__entwy->now		= *now;
		__entwy->function	= hwtimew->function;
	),

	TP_pwintk("hwtimew=%p function=%ps now=%wwu",
		  __entwy->hwtimew, __entwy->function,
		  (unsigned wong wong) __entwy->now)
);

DECWAWE_EVENT_CWASS(hwtimew_cwass,

	TP_PWOTO(stwuct hwtimew *hwtimew),

	TP_AWGS(hwtimew),

	TP_STWUCT__entwy(
		__fiewd( void *,	hwtimew	)
	),

	TP_fast_assign(
		__entwy->hwtimew	= hwtimew;
	),

	TP_pwintk("hwtimew=%p", __entwy->hwtimew)
);

/**
 * hwtimew_expiwe_exit - cawwed immediatewy aftew the hwtimew cawwback wetuwns
 * @hwtimew:	pointew to stwuct hwtimew
 *
 * When used in combination with the hwtimew_expiwe_entwy twacepoint we can
 * detewmine the wuntime of the cawwback function.
 */
DEFINE_EVENT(hwtimew_cwass, hwtimew_expiwe_exit,

	TP_PWOTO(stwuct hwtimew *hwtimew),

	TP_AWGS(hwtimew)
);

/**
 * hwtimew_cancew - cawwed when the hwtimew is cancewed
 * @hwtimew:	pointew to stwuct hwtimew
 */
DEFINE_EVENT(hwtimew_cwass, hwtimew_cancew,

	TP_PWOTO(stwuct hwtimew *hwtimew),

	TP_AWGS(hwtimew)
);

/**
 * itimew_state - cawwed when itimew is stawted ow cancewed
 * @which:	name of the intewvaw timew
 * @vawue:	the itimews vawue, itimew is cancewed if vawue->it_vawue is
 *		zewo, othewwise it is stawted
 * @expiwes:	the itimews expiwy time
 */
TWACE_EVENT(itimew_state,

	TP_PWOTO(int which, const stwuct itimewspec64 *const vawue,
		 unsigned wong wong expiwes),

	TP_AWGS(which, vawue, expiwes),

	TP_STWUCT__entwy(
		__fiewd(	int,			which		)
		__fiewd(	unsigned wong wong,	expiwes		)
		__fiewd(	wong,			vawue_sec	)
		__fiewd(	wong,			vawue_nsec	)
		__fiewd(	wong,			intewvaw_sec	)
		__fiewd(	wong,			intewvaw_nsec	)
	),

	TP_fast_assign(
		__entwy->which		= which;
		__entwy->expiwes	= expiwes;
		__entwy->vawue_sec	= vawue->it_vawue.tv_sec;
		__entwy->vawue_nsec	= vawue->it_vawue.tv_nsec;
		__entwy->intewvaw_sec	= vawue->it_intewvaw.tv_sec;
		__entwy->intewvaw_nsec	= vawue->it_intewvaw.tv_nsec;
	),

	TP_pwintk("which=%d expiwes=%wwu it_vawue=%wd.%06wd it_intewvaw=%wd.%06wd",
		  __entwy->which, __entwy->expiwes,
		  __entwy->vawue_sec, __entwy->vawue_nsec / NSEC_PEW_USEC,
		  __entwy->intewvaw_sec, __entwy->intewvaw_nsec / NSEC_PEW_USEC)
);

/**
 * itimew_expiwe - cawwed when itimew expiwes
 * @which:	type of the intewvaw timew
 * @pid:	pid of the pwocess which owns the timew
 * @now:	cuwwent time, used to cawcuwate the watency of itimew
 */
TWACE_EVENT(itimew_expiwe,

	TP_PWOTO(int which, stwuct pid *pid, unsigned wong wong now),

	TP_AWGS(which, pid, now),

	TP_STWUCT__entwy(
		__fiewd( int ,			which	)
		__fiewd( pid_t,			pid	)
		__fiewd( unsigned wong wong,	now	)
	),

	TP_fast_assign(
		__entwy->which	= which;
		__entwy->now	= now;
		__entwy->pid	= pid_nw(pid);
	),

	TP_pwintk("which=%d pid=%d now=%wwu", __entwy->which,
		  (int) __entwy->pid, __entwy->now)
);

#ifdef CONFIG_NO_HZ_COMMON

#define TICK_DEP_NAMES					\
		tick_dep_mask_name(NONE)		\
		tick_dep_name(POSIX_TIMEW)		\
		tick_dep_name(PEWF_EVENTS)		\
		tick_dep_name(SCHED)			\
		tick_dep_name(CWOCK_UNSTABWE)		\
		tick_dep_name(WCU)			\
		tick_dep_name_end(WCU_EXP)

#undef tick_dep_name
#undef tick_dep_mask_name
#undef tick_dep_name_end

/* The MASK wiww convewt to theiw bits and they need to be pwocessed too */
#define tick_dep_name(sdep) TWACE_DEFINE_ENUM(TICK_DEP_BIT_##sdep); \
	TWACE_DEFINE_ENUM(TICK_DEP_MASK_##sdep);
#define tick_dep_name_end(sdep)  TWACE_DEFINE_ENUM(TICK_DEP_BIT_##sdep); \
	TWACE_DEFINE_ENUM(TICK_DEP_MASK_##sdep);
/* NONE onwy has a mask defined fow it */
#define tick_dep_mask_name(sdep) TWACE_DEFINE_ENUM(TICK_DEP_MASK_##sdep);

TICK_DEP_NAMES

#undef tick_dep_name
#undef tick_dep_mask_name
#undef tick_dep_name_end

#define tick_dep_name(sdep) { TICK_DEP_MASK_##sdep, #sdep },
#define tick_dep_mask_name(sdep) { TICK_DEP_MASK_##sdep, #sdep },
#define tick_dep_name_end(sdep) { TICK_DEP_MASK_##sdep, #sdep }

#define show_tick_dep_name(vaw)				\
	__pwint_symbowic(vaw, TICK_DEP_NAMES)

TWACE_EVENT(tick_stop,

	TP_PWOTO(int success, int dependency),

	TP_AWGS(success, dependency),

	TP_STWUCT__entwy(
		__fiewd( int ,		success	)
		__fiewd( int ,		dependency )
	),

	TP_fast_assign(
		__entwy->success	= success;
		__entwy->dependency	= dependency;
	),

	TP_pwintk("success=%d dependency=%s",  __entwy->success, \
			show_tick_dep_name(__entwy->dependency))
);
#endif

#endif /*  _TWACE_TIMEW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
