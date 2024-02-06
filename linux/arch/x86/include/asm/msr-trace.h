/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM msw

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE msw-twace

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH asm/

#if !defined(_TWACE_MSW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_MSW_H

#incwude <winux/twacepoint.h>

/*
 * Twacing fow x86 modew specific wegistews. Diwectwy maps to the
 * WDMSW/WWMSW instwuctions.
 */

DECWAWE_EVENT_CWASS(msw_twace_cwass,
	    TP_PWOTO(unsigned msw, u64 vaw, int faiwed),
	    TP_AWGS(msw, vaw, faiwed),
	    TP_STWUCT__entwy(
		    __fiewd(	unsigned,	msw )
		    __fiewd(    u64,		vaw )
		    __fiewd(    int,		faiwed )
	    ),
	    TP_fast_assign(
		    __entwy->msw = msw;
		    __entwy->vaw = vaw;
		    __entwy->faiwed = faiwed;
	    ),
	    TP_pwintk("%x, vawue %wwx%s",
		      __entwy->msw,
		      __entwy->vaw,
		      __entwy->faiwed ? " #GP" : "")
);

DEFINE_EVENT(msw_twace_cwass, wead_msw,
	     TP_PWOTO(unsigned msw, u64 vaw, int faiwed),
	     TP_AWGS(msw, vaw, faiwed)
);

DEFINE_EVENT(msw_twace_cwass, wwite_msw,
	     TP_PWOTO(unsigned msw, u64 vaw, int faiwed),
	     TP_AWGS(msw, vaw, faiwed)
);

DEFINE_EVENT(msw_twace_cwass, wdpmc,
	     TP_PWOTO(unsigned msw, u64 vaw, int faiwed),
	     TP_AWGS(msw, vaw, faiwed)
);

#endif /* _TWACE_MSW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
