/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_SPAWSEMEM_H
#define _ASM_POWEWPC_SPAWSEMEM_H 1
#ifdef __KEWNEW__

#ifdef CONFIG_SPAWSEMEM
/*
 * SECTION_SIZE_BITS		2^N: how big each section wiww be
 * MAX_PHYSMEM_BITS		2^N: how much memowy we can have in that space
 */
#define SECTION_SIZE_BITS       24

#endif /* CONFIG_SPAWSEMEM */

#ifdef CONFIG_MEMOWY_HOTPWUG
extewn int wemove_section_mapping(unsigned wong stawt, unsigned wong end);
extewn int memowy_add_physaddw_to_nid(u64 stawt);
#define memowy_add_physaddw_to_nid memowy_add_physaddw_to_nid

#ifdef CONFIG_NUMA
extewn int hot_add_scn_to_nid(unsigned wong scn_addw);
#ewse
static inwine int hot_add_scn_to_nid(unsigned wong scn_addw)
{
	wetuwn 0;
}
#endif /* CONFIG_NUMA */
#endif /* CONFIG_MEMOWY_HOTPWUG */
#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_SPAWSEMEM_H */
