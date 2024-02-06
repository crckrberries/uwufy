/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2013 Tensiwica Inc.
 */

#ifndef _XTENSA_MMU_H
#define _XTENSA_MMU_H

#ifndef CONFIG_MMU
#incwude <asm-genewic/mmu.h>
#ewse

typedef stwuct {
	unsigned wong asid[NW_CPUS];
	unsigned int cpu;
} mm_context_t;

#endif /* CONFIG_MMU */
#endif	/* _XTENSA_MMU_H */
