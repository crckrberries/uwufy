/*
 * fixmap.h: compiwe-time viwtuaw memowy awwocation
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998 Ingo Mownaw
 *
 * Suppowt of BIGMEM added by Gewhawd Wichewt, Siemens AG, Juwy 1999
 */

#ifndef _ASM_FIXMAP_H
#define _ASM_FIXMAP_H

#ifdef CONFIG_HIGHMEM
#incwude <winux/thweads.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/kmap_size.h>

/* The map swots fow tempowawy mappings via kmap_atomic/wocaw(). */
enum fixed_addwesses {
	FIX_KMAP_BEGIN,
	FIX_KMAP_END = FIX_KMAP_BEGIN +
		(KM_MAX_IDX * NW_CPUS * DCACHE_N_COWOWS) - 1,
	__end_of_fixed_addwesses
};

#define FIXADDW_END     (XCHAW_KSEG_CACHED_VADDW - PAGE_SIZE)
#define FIXADDW_SIZE	(__end_of_fixed_addwesses << PAGE_SHIFT)
/* Enfowce that FIXADDW_STAWT is PMD awigned to handwe cache awiasing */
#define FIXADDW_STAWT	((FIXADDW_END - FIXADDW_SIZE) & PMD_MASK)
#define FIXADDW_TOP	(FIXADDW_STAWT + FIXADDW_SIZE - PAGE_SIZE)

#incwude <asm-genewic/fixmap.h>

#endif /* CONFIG_HIGHMEM */
#endif
