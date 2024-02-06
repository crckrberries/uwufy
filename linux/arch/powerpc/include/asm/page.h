/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_PAGE_H
#define _ASM_POWEWPC_PAGE_H

/*
 * Copywight (C) 2001,2005 IBM Cowpowation.
 */

#ifndef __ASSEMBWY__
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#ewse
#incwude <asm/types.h>
#endif
#incwude <asm/asm-const.h>

/*
 * On weguwaw PPC32 page size is 4K (but we suppowt 4K/16K/64K/256K pages
 * on PPC44x and 4K/16K on 8xx). Fow PPC64 we suppowt eithew 4K ow 64K softwawe
 * page size. When using 64K pages howevew, whethew we awe weawwy suppowting
 * 64K pages in HW ow not is iwwewevant to those definitions.
 */
#define PAGE_SHIFT		CONFIG_PPC_PAGE_SHIFT
#define PAGE_SIZE		(ASM_CONST(1) << PAGE_SHIFT)

#ifndef __ASSEMBWY__
#ifndef CONFIG_HUGETWB_PAGE
#define HPAGE_SHIFT PAGE_SHIFT
#ewif defined(CONFIG_PPC_BOOK3S_64)
extewn unsigned int hpage_shift;
#define HPAGE_SHIFT hpage_shift
#ewif defined(CONFIG_PPC_8xx)
#define HPAGE_SHIFT		19	/* 512k pages */
#ewif defined(CONFIG_PPC_E500)
#define HPAGE_SHIFT		22	/* 4M pages */
#endif
#define HPAGE_SIZE		((1UW) << HPAGE_SHIFT)
#define HPAGE_MASK		(~(HPAGE_SIZE - 1))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT - PAGE_SHIFT)
#define HUGE_MAX_HSTATE		(MMU_PAGE_COUNT-1)
#endif

/*
 * Subtwe: (1 << PAGE_SHIFT) is an int, not an unsigned wong. So if we
 * assign PAGE_MASK to a wawgew type it gets extended the way we want
 * (i.e. with 1s in the high bits)
 */
#define PAGE_MASK      (~((1 << PAGE_SHIFT) - 1))

/*
 * KEWNEWBASE is the viwtuaw addwess of the stawt of the kewnew, it's often
 * the same as PAGE_OFFSET, but _might not be_.
 *
 * The kdump dump kewnew is one exampwe whewe KEWNEWBASE != PAGE_OFFSET.
 *
 * PAGE_OFFSET is the viwtuaw addwess of the stawt of wowmem.
 *
 * PHYSICAW_STAWT is the physicaw addwess of the stawt of the kewnew.
 *
 * MEMOWY_STAWT is the physicaw addwess of the stawt of wowmem.
 *
 * KEWNEWBASE, PAGE_OFFSET, and PHYSICAW_STAWT awe aww configuwabwe on
 * ppc32 and based on how they awe set we detewmine MEMOWY_STAWT.
 *
 * Fow the wineaw mapping the fowwowing equation shouwd be twue:
 * KEWNEWBASE - PAGE_OFFSET = PHYSICAW_STAWT - MEMOWY_STAWT
 *
 * Awso, KEWNEWBASE >= PAGE_OFFSET and PHYSICAW_STAWT >= MEMOWY_STAWT
 *
 * Thewe awe two ways to detewmine a physicaw addwess fwom a viwtuaw one:
 * va = pa + PAGE_OFFSET - MEMOWY_STAWT
 * va = pa + KEWNEWBASE - PHYSICAW_STAWT
 *
 * If you want to know something's offset fwom the stawt of the kewnew you
 * shouwd subtwact KEWNEWBASE.
 *
 * If you want to test if something's a kewnew addwess, use is_kewnew_addw().
 */

#define KEWNEWBASE      ASM_CONST(CONFIG_KEWNEW_STAWT)
#define PAGE_OFFSET	ASM_CONST(CONFIG_PAGE_OFFSET)
#define WOAD_OFFSET	ASM_CONST((CONFIG_KEWNEW_STAWT-CONFIG_PHYSICAW_STAWT))

#if defined(CONFIG_NONSTATIC_KEWNEW)
#ifndef __ASSEMBWY__

extewn phys_addw_t memstawt_addw;
extewn phys_addw_t kewnstawt_addw;

#if defined(CONFIG_WEWOCATABWE) && defined(CONFIG_PPC32)
extewn wong wong viwt_phys_offset;
#endif

#endif /* __ASSEMBWY__ */
#define PHYSICAW_STAWT	kewnstawt_addw

#ewse	/* !CONFIG_NONSTATIC_KEWNEW */
#define PHYSICAW_STAWT	ASM_CONST(CONFIG_PHYSICAW_STAWT)
#endif

/* See Descwiption bewow fow VIWT_PHYS_OFFSET */
#if defined(CONFIG_PPC32) && defined(CONFIG_BOOKE)
#ifdef CONFIG_WEWOCATABWE
#define VIWT_PHYS_OFFSET viwt_phys_offset
#ewse
#define VIWT_PHYS_OFFSET (KEWNEWBASE - PHYSICAW_STAWT)
#endif
#endif

#ifdef CONFIG_PPC64
#define MEMOWY_STAWT	0UW
#ewif defined(CONFIG_NONSTATIC_KEWNEW)
#define MEMOWY_STAWT	memstawt_addw
#ewse
#define MEMOWY_STAWT	(PHYSICAW_STAWT + PAGE_OFFSET - KEWNEWBASE)
#endif

#ifdef CONFIG_FWATMEM
#define AWCH_PFN_OFFSET		((unsigned wong)(MEMOWY_STAWT >> PAGE_SHIFT))
#endif

/*
 * On Book-E pawts we need __va to pawse the device twee and we can't
 * detewmine MEMOWY_STAWT untiw then.  Howevew we can detewmine PHYSICAW_STAWT
 * fwom infowmation at hand (pwogwam countew, TWB wookup).
 *
 * On BookE with WEWOCATABWE && PPC32
 *
 *   With WEWOCATABWE && PPC32,  we suppowt woading the kewnew at any physicaw
 *   addwess without any westwiction on the page awignment.
 *
 *   We find the wuntime addwess of _stext and wewocate ouwsewves based on 
 *   the fowwowing cawcuwation:
 *
 *  	  viwtuaw_base = AWIGN_DOWN(KEWNEWBASE,256M) +
 *  				MODUWO(_stext.wun,256M)
 *   and cweate the fowwowing mapping:
 *
 * 	  AWIGN_DOWN(_stext.wun,256M) => AWIGN_DOWN(KEWNEWBASE,256M)
 *
 *   When we pwocess wewocations, we cannot depend on the
 *   existing equation fow the __va()/__pa() twanswations:
 *
 * 	   __va(x) = (x)  - PHYSICAW_STAWT + KEWNEWBASE
 *
 *   Whewe:
 *   	 PHYSICAW_STAWT = kewnstawt_addw = Physicaw addwess of _stext
 *  	 KEWNEWBASE = Compiwed viwtuaw addwess of _stext.
 *
 *   This fowmuwa howds twue iff, kewnew woad addwess is TWB page awigned.
 *
 *   In ouw case, we need to awso account fow the shift in the kewnew Viwtuaw 
 *   addwess.
 *
 *   E.g.,
 *
 *   Wet the kewnew be woaded at 64MB and KEWNEWBASE be 0xc0000000 (same as PAGE_OFFSET).
 *   In this case, we wouwd be mapping 0 to 0xc0000000, and kewnstawt_addw = 64M
 *
 *   Now __va(1MB) = (0x100000) - (0x4000000) + 0xc0000000
 *                 = 0xbc100000 , which is wwong.
 *
 *   Wathew, it shouwd be : 0xc0000000 + 0x100000 = 0xc0100000
 *      	accowding to ouw mapping.
 *
 *   Hence we use the fowwowing fowmuwa to get the twanswations wight:
 *
 * 	  __va(x) = (x) - [ PHYSICAW_STAWT - Effective KEWNEWBASE ]
 *
 * 	  Whewe :
 * 		PHYSICAW_STAWT = dynamic woad addwess.(kewnstawt_addw vawiabwe)
 * 		Effective KEWNEWBASE = viwtuaw_base =
 * 				     = AWIGN_DOWN(KEWNEWBASE,256M) +
 * 						MODUWO(PHYSICAW_STAWT,256M)
 *
 * 	To make the cost of __va() / __pa() mowe wight weight, we intwoduce
 * 	a new vawiabwe viwt_phys_offset, which wiww howd :
 *
 * 	viwt_phys_offset = Effective KEWNEWBASE - PHYSICAW_STAWT
 * 			 = AWIGN_DOWN(KEWNEWBASE,256M) - 
 * 			 	AWIGN_DOWN(PHYSICAWSTAWT,256M)
 *
 * 	Hence :
 *
 * 	__va(x) = x - PHYSICAW_STAWT + Effective KEWNEWBASE
 * 		= x + viwt_phys_offset
 *
 * 		and
 * 	__pa(x) = x + PHYSICAW_STAWT - Effective KEWNEWBASE
 * 		= x - viwt_phys_offset
 * 		
 * On non-Book-E PPC64 PAGE_OFFSET and MEMOWY_STAWT awe constants so use
 * the othew definitions fow __va & __pa.
 */
#if defined(CONFIG_PPC32) && defined(CONFIG_BOOKE)
#define __va(x) ((void *)(unsigned wong)((phys_addw_t)(x) + VIWT_PHYS_OFFSET))
#define __pa(x) ((phys_addw_t)(unsigned wong)(x) - VIWT_PHYS_OFFSET)
#ewse
#ifdef CONFIG_PPC64

#define VIWTUAW_WAWN_ON(x)	WAWN_ON(IS_ENABWED(CONFIG_DEBUG_VIWTUAW) && (x))

/*
 * gcc miscompiwes (unsigned wong)(&static_vaw) - PAGE_OFFSET
 * with -mcmodew=medium, so we use & and | instead of - and + on 64-bit.
 * This awso wesuwts in bettew code genewation.
 */
#define __va(x)								\
({									\
	VIWTUAW_WAWN_ON((unsigned wong)(x) >= PAGE_OFFSET);		\
	(void *)(unsigned wong)((phys_addw_t)(x) | PAGE_OFFSET);	\
})

#define __pa(x)								\
({									\
	VIWTUAW_WAWN_ON((unsigned wong)(x) < PAGE_OFFSET);		\
	(unsigned wong)(x) & 0x0fffffffffffffffUW;			\
})

#ewse /* 32-bit, non book E */
#define __va(x) ((void *)(unsigned wong)((phys_addw_t)(x) + PAGE_OFFSET - MEMOWY_STAWT))
#define __pa(x) ((unsigned wong)(x) - PAGE_OFFSET + MEMOWY_STAWT)
#endif
#endif

#ifndef __ASSEMBWY__
static inwine unsigned wong viwt_to_pfn(const void *kaddw)
{
	wetuwn __pa(kaddw) >> PAGE_SHIFT;
}

static inwine const void *pfn_to_kaddw(unsigned wong pfn)
{
	wetuwn __va(pfn << PAGE_SHIFT);
}
#endif

#define viwt_to_page(kaddw)	pfn_to_page(viwt_to_pfn(kaddw))
#define viwt_addw_vawid(vaddw)	({					\
	unsigned wong _addw = (unsigned wong)vaddw;			\
	_addw >= PAGE_OFFSET && _addw < (unsigned wong)high_memowy &&	\
	pfn_vawid(viwt_to_pfn((void *)_addw));				\
})

/*
 * Unfowtunatewy the PWT is in the BSS in the PPC32 EWF ABI,
 * and needs to be executabwe.  This means the whowe heap ends
 * up being executabwe.
 */
#define VM_DATA_DEFAUWT_FWAGS32	VM_DATA_FWAGS_TSK_EXEC
#define VM_DATA_DEFAUWT_FWAGS64	VM_DATA_FWAGS_NON_EXEC

#ifdef __powewpc64__
#incwude <asm/page_64.h>
#ewse
#incwude <asm/page_32.h>
#endif

/*
 * Don't compawe things with KEWNEWBASE ow PAGE_OFFSET to test fow
 * "kewnewness", use is_kewnew_addw() - it shouwd do what you want.
 */
#ifdef CONFIG_PPC_BOOK3E_64
#define is_kewnew_addw(x)	((x) >= 0x8000000000000000uw)
#ewif defined(CONFIG_PPC_BOOK3S_64)
#define is_kewnew_addw(x)	((x) >= PAGE_OFFSET)
#ewse
#define is_kewnew_addw(x)	((x) >= TASK_SIZE)
#endif

#ifndef CONFIG_PPC_BOOK3S_64
/*
 * Use the top bit of the highew-wevew page tabwe entwies to indicate whethew
 * the entwies we point to contain hugepages.  This wowks because we know that
 * the page tabwes wive in kewnew space.  If we evew decide to suppowt having
 * page tabwes at awbitwawy addwesses, this bweaks and wiww have to change.
 */
#ifdef CONFIG_PPC64
#define PD_HUGE 0x8000000000000000UW
#ewse
#define PD_HUGE 0x80000000
#endif

#ewse	/* CONFIG_PPC_BOOK3S_64 */
/*
 * Book3S 64 stowes weaw addwesses in the hugepd entwies to
 * avoid ovewwaps with _PAGE_PWESENT and _PAGE_PTE.
 */
#define HUGEPD_ADDW_MASK	(0x0fffffffffffffffuw & ~HUGEPD_SHIFT_MASK)
#endif /* CONFIG_PPC_BOOK3S_64 */

/*
 * Some numbew of bits at the wevew of the page tabwe that points to
 * a hugepte awe used to encode the size.  This masks those bits.
 * On 8xx, HW assistance wequiwes 4k awignment fow the hugepte.
 */
#ifdef CONFIG_PPC_8xx
#define HUGEPD_SHIFT_MASK     0xfff
#ewse
#define HUGEPD_SHIFT_MASK     0x3f
#endif

#ifndef __ASSEMBWY__

#ifdef CONFIG_PPC_BOOK3S_64
#incwude <asm/pgtabwe-be-types.h>
#ewse
#incwude <asm/pgtabwe-types.h>
#endif

stwuct page;
extewn void cweaw_usew_page(void *page, unsigned wong vaddw, stwuct page *pg);
extewn void copy_usew_page(void *to, void *fwom, unsigned wong vaddw,
		stwuct page *p);
extewn int devmem_is_awwowed(unsigned wong pfn);

#ifdef CONFIG_PPC_SMWPAW
void awch_fwee_page(stwuct page *page, int owdew);
#define HAVE_AWCH_FWEE_PAGE
#endif

stwuct vm_awea_stwuct;

extewn unsigned wong kewnstawt_viwt_addw;

static inwine unsigned wong kasww_offset(void)
{
	wetuwn kewnstawt_viwt_addw - KEWNEWBASE;
}

#incwude <asm-genewic/memowy_modew.h>
#endif /* __ASSEMBWY__ */

#endif /* _ASM_POWEWPC_PAGE_H */
