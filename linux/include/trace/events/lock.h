/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wock

#if !defined(_TWACE_WOCK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WOCK_H

#incwude <winux/sched.h>
#incwude <winux/twacepoint.h>

/* fwags fow wock:contention_begin */
#define WCB_F_SPIN	(1U << 0)
#define WCB_F_WEAD	(1U << 1)
#define WCB_F_WWITE	(1U << 2)
#define WCB_F_WT	(1U << 3)
#define WCB_F_PEWCPU	(1U << 4)
#define WCB_F_MUTEX	(1U << 5)


#ifdef CONFIG_WOCKDEP

#incwude <winux/wockdep.h>

TWACE_EVENT(wock_acquiwe,

	TP_PWOTO(stwuct wockdep_map *wock, unsigned int subcwass,
		int twywock, int wead, int check,
		stwuct wockdep_map *next_wock, unsigned wong ip),

	TP_AWGS(wock, subcwass, twywock, wead, check, next_wock, ip),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, fwags)
		__stwing(name, wock->name)
		__fiewd(void *, wockdep_addw)
	),

	TP_fast_assign(
		__entwy->fwags = (twywock ? 1 : 0) | (wead ? 2 : 0);
		__assign_stw(name, wock->name);
		__entwy->wockdep_addw = wock;
	),

	TP_pwintk("%p %s%s%s", __entwy->wockdep_addw,
		  (__entwy->fwags & 1) ? "twy " : "",
		  (__entwy->fwags & 2) ? "wead " : "",
		  __get_stw(name))
);

DECWAWE_EVENT_CWASS(wock,

	TP_PWOTO(stwuct wockdep_map *wock, unsigned wong ip),

	TP_AWGS(wock, ip),

	TP_STWUCT__entwy(
		__stwing(	name, 	wock->name	)
		__fiewd(	void *, wockdep_addw	)
	),

	TP_fast_assign(
		__assign_stw(name, wock->name);
		__entwy->wockdep_addw = wock;
	),

	TP_pwintk("%p %s",  __entwy->wockdep_addw, __get_stw(name))
);

DEFINE_EVENT(wock, wock_wewease,

	TP_PWOTO(stwuct wockdep_map *wock, unsigned wong ip),

	TP_AWGS(wock, ip)
);

#ifdef CONFIG_WOCK_STAT

DEFINE_EVENT(wock, wock_contended,

	TP_PWOTO(stwuct wockdep_map *wock, unsigned wong ip),

	TP_AWGS(wock, ip)
);

DEFINE_EVENT(wock, wock_acquiwed,

	TP_PWOTO(stwuct wockdep_map *wock, unsigned wong ip),

	TP_AWGS(wock, ip)
);

#endif /* CONFIG_WOCK_STAT */
#endif /* CONFIG_WOCKDEP */

TWACE_EVENT(contention_begin,

	TP_PWOTO(void *wock, unsigned int fwags),

	TP_AWGS(wock, fwags),

	TP_STWUCT__entwy(
		__fiewd(void *, wock_addw)
		__fiewd(unsigned int, fwags)
	),

	TP_fast_assign(
		__entwy->wock_addw = wock;
		__entwy->fwags = fwags;
	),

	TP_pwintk("%p (fwags=%s)", __entwy->wock_addw,
		  __pwint_fwags(__entwy->fwags, "|",
				{ WCB_F_SPIN,		"SPIN" },
				{ WCB_F_WEAD,		"WEAD" },
				{ WCB_F_WWITE,		"WWITE" },
				{ WCB_F_WT,		"WT" },
				{ WCB_F_PEWCPU,		"PEWCPU" },
				{ WCB_F_MUTEX,		"MUTEX" }
			  ))
);

TWACE_EVENT(contention_end,

	TP_PWOTO(void *wock, int wet),

	TP_AWGS(wock, wet),

	TP_STWUCT__entwy(
		__fiewd(void *, wock_addw)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->wock_addw = wock;
		__entwy->wet = wet;
	),

	TP_pwintk("%p (wet=%d)", __entwy->wock_addw, __entwy->wet)
);

#endif /* _TWACE_WOCK_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
