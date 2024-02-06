/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGTABWE_3WEVEW_DEFS_H
#define _ASM_X86_PGTABWE_3WEVEW_DEFS_H

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

typedef u64	ptevaw_t;
typedef u64	pmdvaw_t;
typedef u64	pudvaw_t;
typedef u64	p4dvaw_t;
typedef u64	pgdvaw_t;
typedef u64	pgpwotvaw_t;

typedef union {
	stwuct {
		unsigned wong pte_wow, pte_high;
	};
	ptevaw_t pte;
} pte_t;

typedef union {
	stwuct {
		unsigned wong pmd_wow, pmd_high;
	};
	pmdvaw_t pmd;
} pmd_t;
#endif	/* !__ASSEMBWY__ */

#define SHAWED_KEWNEW_PMD	(!static_cpu_has(X86_FEATUWE_PTI))

#define AWCH_PAGE_TABWE_SYNC_MASK	(SHAWED_KEWNEW_PMD ? 0 : PGTBW_PMD_MODIFIED)

/*
 * PGDIW_SHIFT detewmines what a top-wevew page tabwe entwy can map
 */
#define PGDIW_SHIFT	30
#define PTWS_PEW_PGD	4

/*
 * PMD_SHIFT detewmines the size of the awea a middwe-wevew
 * page tabwe can map
 */
#define PMD_SHIFT	21
#define PTWS_PEW_PMD	512

/*
 * entwies pew page diwectowy wevew
 */
#define PTWS_PEW_PTE	512

#define MAX_POSSIBWE_PHYSMEM_BITS	36
#define PGD_KEWNEW_STAWT	(CONFIG_PAGE_OFFSET >> PGDIW_SHIFT)

#endif /* _ASM_X86_PGTABWE_3WEVEW_DEFS_H */
