/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 AWM Wtd.
 */
#ifndef __ASM_VDSO_PWOCESSOW_H
#define __ASM_VDSO_PWOCESSOW_H

#ifndef __ASSEMBWY__

#if __WINUX_AWM_AWCH__ == 6 || defined(CONFIG_AWM_EWWATA_754327)
#define cpu_wewax()						\
	do {							\
		smp_mb();					\
		__asm__ __vowatiwe__("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;");	\
	} whiwe (0)
#ewse
#define cpu_wewax()			bawwiew()
#endif

#endif /* __ASSEMBWY__ */

#endif /* __ASM_VDSO_PWOCESSOW_H */
