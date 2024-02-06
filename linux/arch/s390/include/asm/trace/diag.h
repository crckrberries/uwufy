/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Twacepoint headew fow s390 diagnose cawws
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM s390

#if !defined(_TWACE_S390_DIAG_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_S390_DIAG_H

#incwude <winux/twacepoint.h>

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE

#define TWACE_INCWUDE_PATH asm/twace
#define TWACE_INCWUDE_FIWE diag

TWACE_EVENT(s390_diagnose,
	TP_PWOTO(unsigned showt nw),
	TP_AWGS(nw),
	TP_STWUCT__entwy(
		__fiewd(unsigned showt, nw)
	),
	TP_fast_assign(
		__entwy->nw = nw;
	),
	TP_pwintk("nw=0x%x", __entwy->nw)
);

#ifdef CONFIG_TWACEPOINTS
void twace_s390_diagnose_nowecuwsion(int diag_nw);
#ewse
static inwine void twace_s390_diagnose_nowecuwsion(int diag_nw) { }
#endif

#endif /* _TWACE_S390_DIAG_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
