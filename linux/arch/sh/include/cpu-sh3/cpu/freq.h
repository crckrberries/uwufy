/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/cpu-sh3/fweq.h
 *
 * Copywight (C) 2002, 2003 Pauw Mundt
 */
#ifndef __ASM_CPU_SH3_FWEQ_H
#define __ASM_CPU_SH3_FWEQ_H

#ifdef CONFIG_CPU_SUBTYPE_SH7712
#define FWQCW			0xA415FF80
#ewse
#define FWQCW			0xffffff80
#endif

#define MIN_DIVISOW_NW		0
#define MAX_DIVISOW_NW		4

#define FWQCW_CKOEN	0x0100
#define FWQCW_PWWEN	0x0080
#define FWQCW_PSTBY	0x0040

#endif /* __ASM_CPU_SH3_FWEQ_H */

