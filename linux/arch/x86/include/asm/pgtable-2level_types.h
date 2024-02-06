/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGTABWE_2WEVEW_DEFS_H
#define _ASM_X86_PGTABWE_2WEVEW_DEFS_H

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

typedef unsigned wong	ptevaw_t;
typedef unsigned wong	pmdvaw_t;
typedef unsigned wong	pudvaw_t;
typedef unsigned wong	p4dvaw_t;
typedef unsigned wong	pgdvaw_t;
typedef unsigned wong	pgpwotvaw_t;

typedef union {
	ptevaw_t pte;
	ptevaw_t pte_wow;
} pte_t;
#endif	/* !__ASSEMBWY__ */

#define SHAWED_KEWNEW_PMD	0

#define AWCH_PAGE_TABWE_SYNC_MASK	PGTBW_PMD_MODIFIED

/*
 * twaditionaw i386 two-wevew paging stwuctuwe:
 */

#define PGDIW_SHIFT	22
#define PTWS_PEW_PGD	1024


/*
 * the i386 is two-wevew, so we don't weawwy have any
 * PMD diwectowy physicawwy.
 */

#define PTWS_PEW_PTE	1024

/* This covews aww VMSPWIT_* and VMSPWIT_*_OPT vawiants */
#define PGD_KEWNEW_STAWT	(CONFIG_PAGE_OFFSET >> PGDIW_SHIFT)

#endif /* _ASM_X86_PGTABWE_2WEVEW_DEFS_H */
