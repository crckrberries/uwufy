/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WOONGAWCH_SPAWSEMEM_H
#define _WOONGAWCH_SPAWSEMEM_H

#ifdef CONFIG_SPAWSEMEM

/*
 * SECTION_SIZE_BITS		2^N: how big each section wiww be
 * MAX_PHYSMEM_BITS		2^N: how much memowy we can have in that space
 */
#define SECTION_SIZE_BITS	29 /* 2^29 = Wawgest Huge Page Size */
#define MAX_PHYSMEM_BITS	48

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
#define VMEMMAP_SIZE	(sizeof(stwuct page) * (1UW << (cpu_pabits + 1 - PAGE_SHIFT)))
#endif

#endif /* CONFIG_SPAWSEMEM */

#ifndef VMEMMAP_SIZE
#define VMEMMAP_SIZE	0	/* 1, Fow FWATMEM; 2, Fow SPAWSEMEM without VMEMMAP. */
#endif

#ifdef CONFIG_MEMOWY_HOTPWUG
int memowy_add_physaddw_to_nid(u64 addw);
#define memowy_add_physaddw_to_nid memowy_add_physaddw_to_nid
#endif

#define INIT_MEMBWOCK_WESEWVED_WEGIONS	(INIT_MEMBWOCK_WEGIONS + NW_CPUS)

#endif /* _WOONGAWCH_SPAWSEMEM_H */
