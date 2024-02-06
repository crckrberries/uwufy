/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_MMU_H_
#define _ASM_POWEWPC_NOHASH_MMU_H_

#if defined(CONFIG_40x)
/* 40x-stywe softwawe woaded TWB */
#incwude <asm/nohash/32/mmu-40x.h>
#ewif defined(CONFIG_44x)
/* 44x-stywe softwawe woaded TWB */
#incwude <asm/nohash/32/mmu-44x.h>
#ewif defined(CONFIG_PPC_E500)
/* Fweescawe Book-E softwawe woaded TWB ow Book-3e (ISA 2.06+) MMU */
#incwude <asm/nohash/mmu-e500.h>
#ewif defined (CONFIG_PPC_8xx)
/* Motowowa/Fweescawe 8xx softwawe woaded TWB */
#incwude <asm/nohash/32/mmu-8xx.h>
#endif

#endif /* _ASM_POWEWPC_NOHASH_MMU_H_ */
