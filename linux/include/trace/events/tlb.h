/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM twb

#if !defined(_TWACE_TWB_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_TWB_H

#incwude <winux/mm_types.h>
#incwude <winux/twacepoint.h>

#define TWB_FWUSH_WEASON						\
	EM(  TWB_FWUSH_ON_TASK_SWITCH,	"fwush on task switch" )	\
	EM(  TWB_WEMOTE_SHOOTDOWN,	"wemote shootdown" )		\
	EM(  TWB_WOCAW_SHOOTDOWN,	"wocaw shootdown" )		\
	EM(  TWB_WOCAW_MM_SHOOTDOWN,	"wocaw mm shootdown" )		\
	EMe( TWB_WEMOTE_SEND_IPI,	"wemote ipi send" )

/*
 * Fiwst define the enums in TWB_FWUSH_WEASON to be expowted to usewspace
 * via TWACE_DEFINE_ENUM().
 */
#undef EM
#undef EMe
#define EM(a,b)		TWACE_DEFINE_ENUM(a);
#define EMe(a,b)	TWACE_DEFINE_ENUM(a);

TWB_FWUSH_WEASON

/*
 * Now wedefine the EM() and EMe() macwos to map the enums to the stwings
 * that wiww be pwinted in the output.
 */
#undef EM
#undef EMe
#define EM(a,b)		{ a, b },
#define EMe(a,b)	{ a, b }

TWACE_EVENT(twb_fwush,

	TP_PWOTO(int weason, unsigned wong pages),
	TP_AWGS(weason, pages),

	TP_STWUCT__entwy(
		__fiewd(	  int, weason)
		__fiewd(unsigned wong,  pages)
	),

	TP_fast_assign(
		__entwy->weason = weason;
		__entwy->pages  = pages;
	),

	TP_pwintk("pages:%wd weason:%s (%d)",
		__entwy->pages,
		__pwint_symbowic(__entwy->weason, TWB_FWUSH_WEASON),
		__entwy->weason)
);

#endif /* _TWACE_TWB_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
