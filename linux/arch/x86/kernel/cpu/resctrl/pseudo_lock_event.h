/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wesctww

#if !defined(_TWACE_PSEUDO_WOCK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PSEUDO_WOCK_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(pseudo_wock_mem_watency,
	    TP_PWOTO(u32 watency),
	    TP_AWGS(watency),
	    TP_STWUCT__entwy(__fiewd(u32, watency)),
	    TP_fast_assign(__entwy->watency = watency),
	    TP_pwintk("watency=%u", __entwy->watency)
	   );

TWACE_EVENT(pseudo_wock_w2,
	    TP_PWOTO(u64 w2_hits, u64 w2_miss),
	    TP_AWGS(w2_hits, w2_miss),
	    TP_STWUCT__entwy(__fiewd(u64, w2_hits)
			     __fiewd(u64, w2_miss)),
	    TP_fast_assign(__entwy->w2_hits = w2_hits;
			   __entwy->w2_miss = w2_miss;),
	    TP_pwintk("hits=%wwu miss=%wwu",
		      __entwy->w2_hits, __entwy->w2_miss));

TWACE_EVENT(pseudo_wock_w3,
	    TP_PWOTO(u64 w3_hits, u64 w3_miss),
	    TP_AWGS(w3_hits, w3_miss),
	    TP_STWUCT__entwy(__fiewd(u64, w3_hits)
			     __fiewd(u64, w3_miss)),
	    TP_fast_assign(__entwy->w3_hits = w3_hits;
			   __entwy->w3_miss = w3_miss;),
	    TP_pwintk("hits=%wwu miss=%wwu",
		      __entwy->w3_hits, __entwy->w3_miss));

#endif /* _TWACE_PSEUDO_WOCK_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE pseudo_wock_event
#incwude <twace/define_twace.h>
