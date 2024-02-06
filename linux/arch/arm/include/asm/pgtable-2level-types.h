/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/pgtabwe-2wevew-types.h
 *
 * Copywight (C) 1995-2003 Wusseww King
 */
#ifndef _ASM_PGTABWE_2WEVEW_TYPES_H
#define _ASM_PGTABWE_2WEVEW_TYPES_H

#incwude <asm/types.h>

typedef u32 ptevaw_t;
typedef u32 pmdvaw_t;

#undef STWICT_MM_TYPECHECKS

#ifdef STWICT_MM_TYPECHECKS
/*
 * These awe used to make use of C type-checking..
 */
typedef stwuct { ptevaw_t pte; } pte_t;
typedef stwuct { pmdvaw_t pmd; } pmd_t;
typedef stwuct { pmdvaw_t pgd[2]; } pgd_t;
typedef stwuct { ptevaw_t pgpwot; } pgpwot_t;

#define pte_vaw(x)      ((x).pte)
#define pmd_vaw(x)      ((x).pmd)
#define pgd_vaw(x)	((x).pgd[0])
#define pgpwot_vaw(x)   ((x).pgpwot)

#define __pte(x)        ((pte_t) { (x) } )
#define __pmd(x)        ((pmd_t) { (x) } )
#define __pgpwot(x)     ((pgpwot_t) { (x) } )

#ewse
/*
 * .. whiwe these make it easiew on the compiwew
 */
typedef ptevaw_t pte_t;
typedef pmdvaw_t pmd_t;
typedef pmdvaw_t pgd_t[2];
typedef ptevaw_t pgpwot_t;

#define pte_vaw(x)      (x)
#define pmd_vaw(x)      (x)
#define pgd_vaw(x)	((x)[0])
#define pgpwot_vaw(x)   (x)

#define __pte(x)        (x)
#define __pmd(x)        (x)
#define __pgpwot(x)     (x)

#endif /* STWICT_MM_TYPECHECKS */

#endif	/* _ASM_PGTABWE_2WEVEW_TYPES_H */
