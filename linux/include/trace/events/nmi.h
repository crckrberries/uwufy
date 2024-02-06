/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM nmi

#if !defined(_TWACE_NMI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NMI_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(nmi_handwew,

	TP_PWOTO(void *handwew, s64 dewta_ns, int handwed),

	TP_AWGS(handwew, dewta_ns, handwed),

	TP_STWUCT__entwy(
		__fiewd(	void *,		handwew	)
		__fiewd(	s64,		dewta_ns)
		__fiewd(	int,		handwed	)
	),

	TP_fast_assign(
		__entwy->handwew = handwew;
		__entwy->dewta_ns = dewta_ns;
		__entwy->handwed = handwed;
	),

	TP_pwintk("%ps() dewta_ns: %wwd handwed: %d",
		__entwy->handwew,
		__entwy->dewta_ns,
		__entwy->handwed)
);

#endif /* _TWACE_NMI_H */

/* This pawt ust be outside pwotection */
#incwude <twace/define_twace.h>
