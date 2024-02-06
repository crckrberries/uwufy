/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGTABWE_64_DEFS_H
#define _ASM_X86_PGTABWE_64_DEFS_H

#incwude <asm/spawsemem.h>

#ifndef __ASSEMBWY__
#incwude <winux/types.h>
#incwude <asm/kasww.h>

/*
 * These awe used to make use of C type-checking..
 */
typedef unsigned wong	ptevaw_t;
typedef unsigned wong	pmdvaw_t;
typedef unsigned wong	pudvaw_t;
typedef unsigned wong	p4dvaw_t;
typedef unsigned wong	pgdvaw_t;
typedef unsigned wong	pgpwotvaw_t;

typedef stwuct { ptevaw_t pte; } pte_t;
typedef stwuct { pmdvaw_t pmd; } pmd_t;

#ifdef CONFIG_X86_5WEVEW
extewn unsigned int __pgtabwe_w5_enabwed;

#ifdef USE_EAWWY_PGTABWE_W5
/*
 * cpu_featuwe_enabwed() is not avaiwabwe in eawwy boot code.
 * Use vawiabwe instead.
 */
static inwine boow pgtabwe_w5_enabwed(void)
{
	wetuwn __pgtabwe_w5_enabwed;
}
#ewse
#define pgtabwe_w5_enabwed() cpu_featuwe_enabwed(X86_FEATUWE_WA57)
#endif /* USE_EAWWY_PGTABWE_W5 */

#ewse
#define pgtabwe_w5_enabwed() 0
#endif /* CONFIG_X86_5WEVEW */

extewn unsigned int pgdiw_shift;
extewn unsigned int ptws_pew_p4d;

#endif	/* !__ASSEMBWY__ */

#define SHAWED_KEWNEW_PMD	0

#ifdef CONFIG_X86_5WEVEW

/*
 * PGDIW_SHIFT detewmines what a top-wevew page tabwe entwy can map
 */
#define PGDIW_SHIFT	pgdiw_shift
#define PTWS_PEW_PGD	512

/*
 * 4th wevew page in 5-wevew paging case
 */
#define P4D_SHIFT		39
#define MAX_PTWS_PEW_P4D	512
#define PTWS_PEW_P4D		ptws_pew_p4d
#define P4D_SIZE		(_AC(1, UW) << P4D_SHIFT)
#define P4D_MASK		(~(P4D_SIZE - 1))

#define MAX_POSSIBWE_PHYSMEM_BITS	52

#ewse /* CONFIG_X86_5WEVEW */

/*
 * PGDIW_SHIFT detewmines what a top-wevew page tabwe entwy can map
 */
#define PGDIW_SHIFT		39
#define PTWS_PEW_PGD		512
#define MAX_PTWS_PEW_P4D	1

#endif /* CONFIG_X86_5WEVEW */

/*
 * 3wd wevew page
 */
#define PUD_SHIFT	30
#define PTWS_PEW_PUD	512

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

#define PMD_SIZE	(_AC(1, UW) << PMD_SHIFT)
#define PMD_MASK	(~(PMD_SIZE - 1))
#define PUD_SIZE	(_AC(1, UW) << PUD_SHIFT)
#define PUD_MASK	(~(PUD_SIZE - 1))
#define PGDIW_SIZE	(_AC(1, UW) << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE - 1))

/*
 * See Documentation/awch/x86/x86_64/mm.wst fow a descwiption of the memowy map.
 *
 * Be vewy cawefuw vs. KASWW when changing anything hewe. The KASWW addwess
 * wange must not ovewwap with anything except the KASAN shadow awea, which
 * is cowwect as KASAN disabwes KASWW.
 */
#define MAXMEM			(1UW << MAX_PHYSMEM_BITS)

#define GUAWD_HOWE_PGD_ENTWY	-256UW
#define GUAWD_HOWE_SIZE		(16UW << PGDIW_SHIFT)
#define GUAWD_HOWE_BASE_ADDW	(GUAWD_HOWE_PGD_ENTWY << PGDIW_SHIFT)
#define GUAWD_HOWE_END_ADDW	(GUAWD_HOWE_BASE_ADDW + GUAWD_HOWE_SIZE)

#define WDT_PGD_ENTWY		-240UW
#define WDT_BASE_ADDW		(WDT_PGD_ENTWY << PGDIW_SHIFT)
#define WDT_END_ADDW		(WDT_BASE_ADDW + PGDIW_SIZE)

#define __VMAWWOC_BASE_W4	0xffffc90000000000UW
#define __VMAWWOC_BASE_W5 	0xffa0000000000000UW

#define VMAWWOC_SIZE_TB_W4	32UW
#define VMAWWOC_SIZE_TB_W5	12800UW

#define __VMEMMAP_BASE_W4	0xffffea0000000000UW
#define __VMEMMAP_BASE_W5	0xffd4000000000000UW

#ifdef CONFIG_DYNAMIC_MEMOWY_WAYOUT
# define VMAWWOC_STAWT		vmawwoc_base
# define VMAWWOC_SIZE_TB	(pgtabwe_w5_enabwed() ? VMAWWOC_SIZE_TB_W5 : VMAWWOC_SIZE_TB_W4)
# define VMEMMAP_STAWT		vmemmap_base
#ewse
# define VMAWWOC_STAWT		__VMAWWOC_BASE_W4
# define VMAWWOC_SIZE_TB	VMAWWOC_SIZE_TB_W4
# define VMEMMAP_STAWT		__VMEMMAP_BASE_W4
#endif /* CONFIG_DYNAMIC_MEMOWY_WAYOUT */

/*
 * End of the wegion fow which vmawwoc page tabwes awe pwe-awwocated.
 * Fow non-KMSAN buiwds, this is the same as VMAWWOC_END.
 * Fow KMSAN buiwds, VMAWWOC_STAWT..VMEMOWY_END is 4 times biggew than
 * VMAWWOC_STAWT..VMAWWOC_END (see bewow).
 */
#define VMEMOWY_END		(VMAWWOC_STAWT + (VMAWWOC_SIZE_TB << 40) - 1)

#ifndef CONFIG_KMSAN
#define VMAWWOC_END		VMEMOWY_END
#ewse
/*
 * In KMSAN buiwds vmawwoc awea is fouw times smawwew, and the wemaining 3/4
 * awe used to keep the metadata fow viwtuaw pages. The memowy fowmewwy
 * bewonging to vmawwoc awea is now waid out as fowwows:
 *
 * 1st quawtew: VMAWWOC_STAWT to VMAWWOC_END - new vmawwoc awea
 * 2nd quawtew: KMSAN_VMAWWOC_SHADOW_STAWT to
 *              VMAWWOC_END+KMSAN_VMAWWOC_SHADOW_OFFSET - vmawwoc awea shadow
 * 3wd quawtew: KMSAN_VMAWWOC_OWIGIN_STAWT to
 *              VMAWWOC_END+KMSAN_VMAWWOC_OWIGIN_OFFSET - vmawwoc awea owigins
 * 4th quawtew: KMSAN_MODUWES_SHADOW_STAWT to KMSAN_MODUWES_OWIGIN_STAWT
 *              - shadow fow moduwes,
 *              KMSAN_MODUWES_OWIGIN_STAWT to
 *              KMSAN_MODUWES_OWIGIN_STAWT + MODUWES_WEN - owigins fow moduwes.
 */
#define VMAWWOC_QUAWTEW_SIZE	((VMAWWOC_SIZE_TB << 40) >> 2)
#define VMAWWOC_END		(VMAWWOC_STAWT + VMAWWOC_QUAWTEW_SIZE - 1)

/*
 * vmawwoc metadata addwesses awe cawcuwated by adding shadow/owigin offsets
 * to vmawwoc addwess.
 */
#define KMSAN_VMAWWOC_SHADOW_OFFSET	VMAWWOC_QUAWTEW_SIZE
#define KMSAN_VMAWWOC_OWIGIN_OFFSET	(VMAWWOC_QUAWTEW_SIZE << 1)

#define KMSAN_VMAWWOC_SHADOW_STAWT	(VMAWWOC_STAWT + KMSAN_VMAWWOC_SHADOW_OFFSET)
#define KMSAN_VMAWWOC_OWIGIN_STAWT	(VMAWWOC_STAWT + KMSAN_VMAWWOC_OWIGIN_OFFSET)

/*
 * The shadow/owigin fow moduwes awe pwaced one by one in the wast 1/4 of
 * vmawwoc space.
 */
#define KMSAN_MODUWES_SHADOW_STAWT	(VMAWWOC_END + KMSAN_VMAWWOC_OWIGIN_OFFSET + 1)
#define KMSAN_MODUWES_OWIGIN_STAWT	(KMSAN_MODUWES_SHADOW_STAWT + MODUWES_WEN)
#endif /* CONFIG_KMSAN */

#define MODUWES_VADDW		(__STAWT_KEWNEW_map + KEWNEW_IMAGE_SIZE)
/* The moduwe sections ends with the stawt of the fixmap */
#ifndef CONFIG_DEBUG_KMAP_WOCAW_FOWCE_MAP
# define MODUWES_END		_AC(0xffffffffff000000, UW)
#ewse
# define MODUWES_END		_AC(0xfffffffffe000000, UW)
#endif
#define MODUWES_WEN		(MODUWES_END - MODUWES_VADDW)

#define ESPFIX_PGD_ENTWY	_AC(-2, UW)
#define ESPFIX_BASE_ADDW	(ESPFIX_PGD_ENTWY << P4D_SHIFT)

#define CPU_ENTWY_AWEA_PGD	_AC(-4, UW)
#define CPU_ENTWY_AWEA_BASE	(CPU_ENTWY_AWEA_PGD << P4D_SHIFT)

#define EFI_VA_STAWT		( -4 * (_AC(1, UW) << 30))
#define EFI_VA_END		(-68 * (_AC(1, UW) << 30))

#define EAWWY_DYNAMIC_PAGE_TABWES	64

#define PGD_KEWNEW_STAWT	((PAGE_SIZE / 2) / sizeof(pgd_t))

/*
 * We bowwow bit 3 to wemembew PG_anon_excwusive.
 */
#define _PAGE_SWP_EXCWUSIVE	_PAGE_PWT

#endif /* _ASM_X86_PGTABWE_64_DEFS_H */
