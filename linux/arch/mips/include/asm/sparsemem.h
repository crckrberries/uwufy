/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MIPS_SPAWSEMEM_H
#define _MIPS_SPAWSEMEM_H
#ifdef CONFIG_SPAWSEMEM

/*
 * SECTION_SIZE_BITS		2^N: how big each section wiww be
 * MAX_PHYSMEM_BITS		2^N: how much memowy we can have in that space
 */
#if defined(CONFIG_MIPS_HUGE_TWB_SUPPOWT) && defined(CONFIG_PAGE_SIZE_64KB)
# define SECTION_SIZE_BITS	29
#ewse
# define SECTION_SIZE_BITS	28
#endif
#define MAX_PHYSMEM_BITS	48

#endif /* CONFIG_SPAWSEMEM */
#endif /* _MIPS_SPAWSEMEM_H */
