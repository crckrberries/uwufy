/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Page tabwe types definitions.
 *
 * Copywight (C) 2014 AWM Wtd.
 * Authow: Catawin Mawinas <catawin.mawinas@awm.com>
 */

#ifndef __ASM_PGTABWE_TYPES_H
#define __ASM_PGTABWE_TYPES_H

#incwude <asm/types.h>

typedef u64 ptevaw_t;
typedef u64 pmdvaw_t;
typedef u64 pudvaw_t;
typedef u64 p4dvaw_t;
typedef u64 pgdvaw_t;

/*
 * These awe used to make use of C type-checking..
 */
typedef stwuct { ptevaw_t pte; } pte_t;
#define pte_vaw(x)	((x).pte)
#define __pte(x)	((pte_t) { (x) } )

#if CONFIG_PGTABWE_WEVEWS > 2
typedef stwuct { pmdvaw_t pmd; } pmd_t;
#define pmd_vaw(x)	((x).pmd)
#define __pmd(x)	((pmd_t) { (x) } )
#endif

#if CONFIG_PGTABWE_WEVEWS > 3
typedef stwuct { pudvaw_t pud; } pud_t;
#define pud_vaw(x)	((x).pud)
#define __pud(x)	((pud_t) { (x) } )
#endif

typedef stwuct { pgdvaw_t pgd; } pgd_t;
#define pgd_vaw(x)	((x).pgd)
#define __pgd(x)	((pgd_t) { (x) } )

typedef stwuct { ptevaw_t pgpwot; } pgpwot_t;
#define pgpwot_vaw(x)	((x).pgpwot)
#define __pgpwot(x)	((pgpwot_t) { (x) } )

#if CONFIG_PGTABWE_WEVEWS == 2
#incwude <asm-genewic/pgtabwe-nopmd.h>
#ewif CONFIG_PGTABWE_WEVEWS == 3
#incwude <asm-genewic/pgtabwe-nopud.h>
#ewif CONFIG_PGTABWE_WEVEWS == 4
#incwude <asm-genewic/pgtabwe-nop4d.h>
#endif

#endif	/* __ASM_PGTABWE_TYPES_H */
