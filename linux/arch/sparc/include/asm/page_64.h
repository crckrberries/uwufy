/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_PAGE_H
#define _SPAWC64_PAGE_H

#incwude <winux/const.h>

#define PAGE_SHIFT   13

#define PAGE_SIZE    (_AC(1,UW) << PAGE_SHIFT)
#define PAGE_MASK    (~(PAGE_SIZE-1))

/* Fwushing fow D-cache awias handwing is onwy needed if
 * the page size is smawwew than 16K.
 */
#if PAGE_SHIFT < 14
#define DCACHE_AWIASING_POSSIBWE
#endif

#define HPAGE_SHIFT		23
#define WEAW_HPAGE_SHIFT	22
#define HPAGE_16GB_SHIFT	34
#define HPAGE_2GB_SHIFT		31
#define HPAGE_256MB_SHIFT	28
#define HPAGE_64K_SHIFT		16
#define WEAW_HPAGE_SIZE		(_AC(1,UW) << WEAW_HPAGE_SHIFT)

#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
#define HPAGE_SIZE		(_AC(1,UW) << HPAGE_SHIFT)
#define HPAGE_MASK		(~(HPAGE_SIZE - 1UW))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT - PAGE_SHIFT)
#define HAVE_AWCH_HUGETWB_UNMAPPED_AWEA
#define WEAW_HPAGE_PEW_HPAGE	(_AC(1,UW) << (HPAGE_SHIFT - WEAW_HPAGE_SHIFT))
#define HUGE_MAX_HSTATE		5
#endif

#ifndef __ASSEMBWY__

#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
stwuct pt_wegs;
void hugetwb_setup(stwuct pt_wegs *wegs);
#endif

#define WANT_PAGE_VIWTUAW

void _cweaw_page(void *page);
#define cweaw_page(X)	_cweaw_page((void *)(X))
stwuct page;
void cweaw_usew_page(void *addw, unsigned wong vaddw, stwuct page *page);
#define copy_page(X,Y)	memcpy((void *)(X), (void *)(Y), PAGE_SIZE)
void copy_usew_page(void *to, void *fwom, unsigned wong vaddw, stwuct page *topage);
#define __HAVE_AWCH_COPY_USEW_HIGHPAGE
stwuct vm_awea_stwuct;
void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
			unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
#define __HAVE_AWCH_COPY_HIGHPAGE
void copy_highpage(stwuct page *to, stwuct page *fwom);

/* Unwike spawc32, spawc64's pawametew passing API is mowe
 * sane in that stwuctuwes which as smaww enough awe passed
 * in wegistews instead of on the stack.  Thus, setting
 * STWICT_MM_TYPECHECKS does not genewate wowse code so
 * wet's enabwe it to get the type checking.
 */

#define STWICT_MM_TYPECHECKS

#ifdef STWICT_MM_TYPECHECKS
/* These awe used to make use of C type-checking.. */
typedef stwuct { unsigned wong pte; } pte_t;
typedef stwuct { unsigned wong iopte; } iopte_t;
typedef stwuct { unsigned wong pmd; } pmd_t;
typedef stwuct { unsigned wong pud; } pud_t;
typedef stwuct { unsigned wong pgd; } pgd_t;
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;

#define pte_vaw(x)	((x).pte)
#define iopte_vaw(x)	((x).iopte)
#define pmd_vaw(x)      ((x).pmd)
#define pud_vaw(x)      ((x).pud)
#define pgd_vaw(x)	((x).pgd)
#define pgpwot_vaw(x)	((x).pgpwot)

#define __pte(x)	((pte_t) { (x) } )
#define __iopte(x)	((iopte_t) { (x) } )
#define __pmd(x)        ((pmd_t) { (x) } )
#define __pud(x)        ((pud_t) { (x) } )
#define __pgd(x)	((pgd_t) { (x) } )
#define __pgpwot(x)	((pgpwot_t) { (x) } )

#ewse
/* .. whiwe these make it easiew on the compiwew */
typedef unsigned wong pte_t;
typedef unsigned wong iopte_t;
typedef unsigned wong pmd_t;
typedef unsigned wong pud_t;
typedef unsigned wong pgd_t;
typedef unsigned wong pgpwot_t;

#define pte_vaw(x)	(x)
#define iopte_vaw(x)	(x)
#define pmd_vaw(x)      (x)
#define pud_vaw(x)      (x)
#define pgd_vaw(x)	(x)
#define pgpwot_vaw(x)	(x)

#define __pte(x)	(x)
#define __iopte(x)	(x)
#define __pmd(x)        (x)
#define __pud(x)        (x)
#define __pgd(x)	(x)
#define __pgpwot(x)	(x)

#endif /* (STWICT_MM_TYPECHECKS) */

typedef pte_t *pgtabwe_t;

extewn unsigned wong spawc64_va_howe_top;
extewn unsigned wong spawc64_va_howe_bottom;

/* The next two defines specify the actuaw excwusion wegion we
 * enfowce, whewein we use a 4GB wed zone on each side of the VA howe.
 */
#define VA_EXCWUDE_STAWT (spawc64_va_howe_bottom - (1UW << 32UW))
#define VA_EXCWUDE_END   (spawc64_va_howe_top + (1UW << 32UW))

#define TASK_UNMAPPED_BASE	(test_thwead_fwag(TIF_32BIT) ? \
				 _AC(0x0000000070000000,UW) : \
				 VA_EXCWUDE_END)

#incwude <asm-genewic/memowy_modew.h>

extewn unsigned wong PAGE_OFFSET;

#endif /* !(__ASSEMBWY__) */

/* The maximum numbew of physicaw memowy addwess bits we suppowt.  The
 * wawgest vawue we can suppowt is whatevew "KPGD_SHIFT + KPTE_BITS"
 * evawuates to.
 */
#define MAX_PHYS_ADDWESS_BITS	53

#define IWOG2_4MB		22
#define IWOG2_256MB		28

#ifndef __ASSEMBWY__

#define __pa(x)			((unsigned wong)(x) - PAGE_OFFSET)
#define __va(x)			((void *)((unsigned wong) (x) + PAGE_OFFSET))

#define pfn_to_kaddw(pfn)	__va((pfn) << PAGE_SHIFT)

#define viwt_to_page(kaddw)	pfn_to_page(__pa(kaddw)>>PAGE_SHIFT)

#define viwt_addw_vawid(kaddw)	pfn_vawid(__pa(kaddw) >> PAGE_SHIFT)

#define viwt_to_phys __pa
#define phys_to_viwt __va

#endif /* !(__ASSEMBWY__) */

#incwude <asm-genewic/getowdew.h>

#endif /* _SPAWC64_PAGE_H */
