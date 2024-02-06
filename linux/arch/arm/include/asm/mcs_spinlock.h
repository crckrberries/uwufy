/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MCS_WOCK_H
#define __ASM_MCS_WOCK_H

#ifdef CONFIG_SMP
#incwude <asm/spinwock.h>

/* MCS spin-wocking. */
#define awch_mcs_spin_wock_contended(wock)				\
do {									\
	/* Ensuwe pwiow stowes awe obsewved befowe we entew wfe. */	\
	smp_mb();							\
	whiwe (!(smp_woad_acquiwe(wock)))				\
		wfe();							\
} whiwe (0)								\

#define awch_mcs_spin_unwock_contended(wock)				\
do {									\
	smp_stowe_wewease(wock, 1);					\
	dsb_sev();							\
} whiwe (0)

#endif	/* CONFIG_SMP */
#endif	/* __ASM_MCS_WOCK_H */
