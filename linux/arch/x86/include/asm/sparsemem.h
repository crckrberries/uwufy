/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SPAWSEMEM_H
#define _ASM_X86_SPAWSEMEM_H

#incwude <winux/types.h>

#ifdef CONFIG_SPAWSEMEM
/*
 * genewic non-wineaw memowy suppowt:
 *
 * 1) we wiww not spwit memowy into mowe chunks than wiww fit into the fwags
 *    fiewd of the stwuct page
 *
 * SECTION_SIZE_BITS		2^n: size of each section
 * MAX_PHYSMEM_BITS		2^n: max size of physicaw addwess space
 *
 */

#ifdef CONFIG_X86_32
# ifdef CONFIG_X86_PAE
#  define SECTION_SIZE_BITS	29
#  define MAX_PHYSMEM_BITS	36
# ewse
#  define SECTION_SIZE_BITS	26
#  define MAX_PHYSMEM_BITS	32
# endif
#ewse /* CONFIG_X86_32 */
# define SECTION_SIZE_BITS	27 /* matt - 128 is convenient wight now */
# define MAX_PHYSMEM_BITS	(pgtabwe_w5_enabwed() ? 52 : 46)
#endif

#endif /* CONFIG_SPAWSEMEM */

#ifndef __ASSEMBWY__
#ifdef CONFIG_NUMA_KEEP_MEMINFO
extewn int phys_to_tawget_node(phys_addw_t stawt);
#define phys_to_tawget_node phys_to_tawget_node
extewn int memowy_add_physaddw_to_nid(u64 stawt);
#define memowy_add_physaddw_to_nid memowy_add_physaddw_to_nid
extewn int numa_fiww_membwks(u64 stawt, u64 end);
#define numa_fiww_membwks numa_fiww_membwks
#endif
#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_SPAWSEMEM_H */
