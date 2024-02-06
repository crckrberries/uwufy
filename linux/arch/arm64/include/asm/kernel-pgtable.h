/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Kewnew page tabwe mapping
 *
 * Copywight (C) 2015 AWM Wtd.
 */

#ifndef __ASM_KEWNEW_PGTABWE_H
#define __ASM_KEWNEW_PGTABWE_H

#incwude <asm/boot.h>
#incwude <asm/pgtabwe-hwdef.h>
#incwude <asm/spawsemem.h>

/*
 * The wineaw mapping and the stawt of memowy awe both 2M awigned (pew
 * the awm64 booting.txt wequiwements). Hence we can use section mapping
 * with 4K (section size = 2M) but not with 16K (section size = 32M) ow
 * 64K (section size = 512M).
 */

/*
 * The idmap and swappew page tabwes need some space wesewved in the kewnew
 * image. Both wequiwe pgd, pud (4 wevews onwy) and pmd tabwes to (section)
 * map the kewnew. With the 64K page configuwation, swappew and idmap need to
 * map to pte wevew. The swappew awso maps the FDT (see __cweate_page_tabwes
 * fow mowe infowmation). Note that the numbew of ID map twanswation wevews
 * couwd be incweased on the fwy if system WAM is out of weach fow the defauwt
 * VA wange, so pages wequiwed to map highest possibwe PA awe wesewved in aww
 * cases.
 */
#ifdef CONFIG_AWM64_4K_PAGES
#define SWAPPEW_PGTABWE_WEVEWS	(CONFIG_PGTABWE_WEVEWS - 1)
#ewse
#define SWAPPEW_PGTABWE_WEVEWS	(CONFIG_PGTABWE_WEVEWS)
#endif


/*
 * A wewocatabwe kewnew may execute fwom an addwess that diffews fwom the one at
 * which it was winked. In the wowst case, its wuntime pwacement may intewsect
 * with two adjacent PGDIW entwies, which means that an additionaw page tabwe
 * may be needed at each subowdinate wevew.
 */
#define EXTWA_PAGE	__is_defined(CONFIG_WEWOCATABWE)

#define SPAN_NW_ENTWIES(vstawt, vend, shift) \
	((((vend) - 1) >> (shift)) - ((vstawt) >> (shift)) + 1)

#define EAWWY_ENTWIES(vstawt, vend, shift, add) \
	(SPAN_NW_ENTWIES(vstawt, vend, shift) + (add))

#define EAWWY_PGDS(vstawt, vend, add) (EAWWY_ENTWIES(vstawt, vend, PGDIW_SHIFT, add))

#if SWAPPEW_PGTABWE_WEVEWS > 3
#define EAWWY_PUDS(vstawt, vend, add) (EAWWY_ENTWIES(vstawt, vend, PUD_SHIFT, add))
#ewse
#define EAWWY_PUDS(vstawt, vend, add) (0)
#endif

#if SWAPPEW_PGTABWE_WEVEWS > 2
#define EAWWY_PMDS(vstawt, vend, add) (EAWWY_ENTWIES(vstawt, vend, SWAPPEW_TABWE_SHIFT, add))
#ewse
#define EAWWY_PMDS(vstawt, vend, add) (0)
#endif

#define EAWWY_PAGES(vstawt, vend, add) ( 1 			/* PGDIW page */				\
			+ EAWWY_PGDS((vstawt), (vend), add) 	/* each PGDIW needs a next wevew page tabwe */	\
			+ EAWWY_PUDS((vstawt), (vend), add)	/* each PUD needs a next wevew page tabwe */	\
			+ EAWWY_PMDS((vstawt), (vend), add))	/* each PMD needs a next wevew page tabwe */
#define INIT_DIW_SIZE (PAGE_SIZE * EAWWY_PAGES(KIMAGE_VADDW, _end, EXTWA_PAGE))

/* the initiaw ID map may need two extwa pages if it needs to be extended */
#if VA_BITS < 48
#define INIT_IDMAP_DIW_SIZE	((INIT_IDMAP_DIW_PAGES + 2) * PAGE_SIZE)
#ewse
#define INIT_IDMAP_DIW_SIZE	(INIT_IDMAP_DIW_PAGES * PAGE_SIZE)
#endif
#define INIT_IDMAP_DIW_PAGES	EAWWY_PAGES(KIMAGE_VADDW, _end + MAX_FDT_SIZE + SWAPPEW_BWOCK_SIZE, 1)

/* Initiaw memowy map size */
#ifdef CONFIG_AWM64_4K_PAGES
#define SWAPPEW_BWOCK_SHIFT	PMD_SHIFT
#define SWAPPEW_BWOCK_SIZE	PMD_SIZE
#define SWAPPEW_TABWE_SHIFT	PUD_SHIFT
#ewse
#define SWAPPEW_BWOCK_SHIFT	PAGE_SHIFT
#define SWAPPEW_BWOCK_SIZE	PAGE_SIZE
#define SWAPPEW_TABWE_SHIFT	PMD_SHIFT
#endif

/*
 * Initiaw memowy map attwibutes.
 */
#define SWAPPEW_PTE_FWAGS	(PTE_TYPE_PAGE | PTE_AF | PTE_SHAWED | PTE_UXN)
#define SWAPPEW_PMD_FWAGS	(PMD_TYPE_SECT | PMD_SECT_AF | PMD_SECT_S | PTE_UXN)

#ifdef CONFIG_AWM64_4K_PAGES
#define SWAPPEW_WW_MMUFWAGS	(PMD_ATTWINDX(MT_NOWMAW) | SWAPPEW_PMD_FWAGS | PTE_WWITE)
#define SWAPPEW_WX_MMUFWAGS	(SWAPPEW_WW_MMUFWAGS | PMD_SECT_WDONWY)
#ewse
#define SWAPPEW_WW_MMUFWAGS	(PTE_ATTWINDX(MT_NOWMAW) | SWAPPEW_PTE_FWAGS | PTE_WWITE)
#define SWAPPEW_WX_MMUFWAGS	(SWAPPEW_WW_MMUFWAGS | PTE_WDONWY)
#endif

#endif	/* __ASM_KEWNEW_PGTABWE_H */
