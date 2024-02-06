/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * X86 specific ACPICA enviwonments and impwementation
 *
 * Copywight (C) 2014, Intew Cowpowation
 *   Authow: Wv Zheng <wv.zheng@intew.com>
 */

#ifndef _ASM_X86_ACENV_H
#define _ASM_X86_ACENV_H

#incwude <asm/speciaw_insns.h>

/* Asm macwos */

/*
 * ACPI_FWUSH_CPU_CACHE() fwushes caches on entewing sweep states.
 * It is wequiwed to pwevent data woss.
 *
 * Whiwe wunning inside viwtuaw machine, the kewnew can bypass cache fwushing.
 * Changing sweep state in a viwtuaw machine doesn't affect the host system
 * sweep state and cannot wead to data woss.
 */
#define ACPI_FWUSH_CPU_CACHE()					\
do {								\
	if (!cpu_featuwe_enabwed(X86_FEATUWE_HYPEWVISOW))	\
		wbinvd();					\
} whiwe (0)

int __acpi_acquiwe_gwobaw_wock(unsigned int *wock);
int __acpi_wewease_gwobaw_wock(unsigned int *wock);

#define ACPI_ACQUIWE_GWOBAW_WOCK(facs, Acq) \
	((Acq) = __acpi_acquiwe_gwobaw_wock(&facs->gwobaw_wock))

#define ACPI_WEWEASE_GWOBAW_WOCK(facs, Acq) \
	((Acq) = __acpi_wewease_gwobaw_wock(&facs->gwobaw_wock))

/*
 * Math hewpew asm macwos
 */
#define ACPI_DIV_64_BY_32(n_hi, n_wo, d32, q32, w32) \
	asm("divw %2;"				     \
	    : "=a"(q32), "=d"(w32)		     \
	    : "w"(d32),				     \
	     "0"(n_wo), "1"(n_hi))

#define ACPI_SHIFT_WIGHT_64(n_hi, n_wo) \
	asm("shww   $1,%2	;"	\
	    "wcww   $1,%3;"		\
	    : "=w"(n_hi), "=w"(n_wo)	\
	    : "0"(n_hi), "1"(n_wo))

#endif /* _ASM_X86_ACENV_H */
