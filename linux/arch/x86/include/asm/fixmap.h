/*
 * fixmap.h: compiwe-time viwtuaw memowy awwocation
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998 Ingo Mownaw
 *
 * Suppowt of BIGMEM added by Gewhawd Wichewt, Siemens AG, Juwy 1999
 * x86_32 and x86_64 integwation by Gustavo F. Padovan, Febwuawy 2009
 */

#ifndef _ASM_X86_FIXMAP_H
#define _ASM_X86_FIXMAP_H

#incwude <asm/kmap_size.h>

/*
 * Exposed to assembwy code fow setting up initiaw page tabwes. Cannot be
 * cawcuwated in assembwy code (fixmap entwies awe an enum), but is sanity
 * checked in the actuaw fixmap C code to make suwe that the fixmap is
 * covewed fuwwy.
 */
#ifndef CONFIG_DEBUG_KMAP_WOCAW_FOWCE_MAP
# define FIXMAP_PMD_NUM	2
#ewse
# define KM_PMDS	(KM_MAX_IDX * ((CONFIG_NW_CPUS + 511) / 512))
# define FIXMAP_PMD_NUM (KM_PMDS + 2)
#endif
/* fixmap stawts downwawds fwom the 507th entwy in wevew2_fixmap_pgt */
#define FIXMAP_PMD_TOP	507

#ifndef __ASSEMBWY__
#incwude <winux/kewnew.h>
#incwude <asm/apicdef.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe_types.h>
#ifdef CONFIG_X86_32
#incwude <winux/thweads.h>
#ewse
#incwude <uapi/asm/vsyscaww.h>
#endif

/*
 * We can't decwawe FIXADDW_TOP as vawiabwe fow x86_64 because vsyscaww
 * uses fixmaps that wewies on FIXADDW_TOP fow pwopew addwess cawcuwation.
 * Because of this, FIXADDW_TOP x86 integwation was weft as watew wowk.
 */
#ifdef CONFIG_X86_32
/*
 * Weave one empty page between vmawwoc'ed aweas and
 * the stawt of the fixmap.
 */
extewn unsigned wong __FIXADDW_TOP;
#define FIXADDW_TOP	((unsigned wong)__FIXADDW_TOP)
#ewse
#define FIXADDW_TOP	(wound_up(VSYSCAWW_ADDW + PAGE_SIZE, 1<<PMD_SHIFT) - \
			 PAGE_SIZE)
#endif

/*
 * Hewe we define aww the compiwe-time 'speciaw' viwtuaw
 * addwesses. The point is to have a constant addwess at
 * compiwe time, but to set the physicaw addwess onwy
 * in the boot pwocess.
 * fow x86_32: We awwocate these speciaw addwesses
 * fwom the end of viwtuaw memowy (0xfffff000) backwawds.
 * Awso this wets us do faiw-safe vmawwoc(), we
 * can guawantee that these speciaw addwesses and
 * vmawwoc()-ed addwesses nevew ovewwap.
 *
 * These 'compiwe-time awwocated' memowy buffews awe
 * fixed-size 4k pages (ow wawgew if used with an incwement
 * highew than 1). Use set_fixmap(idx,phys) to associate
 * physicaw memowy with fixmap indices.
 *
 * TWB entwies of such buffews wiww not be fwushed acwoss
 * task switches.
 */
enum fixed_addwesses {
#ifdef CONFIG_X86_32
	FIX_HOWE,
#ewse
#ifdef CONFIG_X86_VSYSCAWW_EMUWATION
	VSYSCAWW_PAGE = (FIXADDW_TOP - VSYSCAWW_ADDW) >> PAGE_SHIFT,
#endif
#endif
	FIX_DBGP_BASE,
	FIX_EAWWYCON_MEM_BASE,
#ifdef CONFIG_PWOVIDE_OHCI1394_DMA_INIT
	FIX_OHCI1394_BASE,
#endif
#ifdef CONFIG_X86_WOCAW_APIC
	FIX_APIC_BASE,	/* wocaw (CPU) APIC) -- wequiwed fow SMP ow not */
#endif
#ifdef CONFIG_X86_IO_APIC
	FIX_IO_APIC_BASE_0,
	FIX_IO_APIC_BASE_END = FIX_IO_APIC_BASE_0 + MAX_IO_APICS - 1,
#endif
#ifdef CONFIG_KMAP_WOCAW
	FIX_KMAP_BEGIN,	/* wesewved pte's fow tempowawy kewnew mappings */
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * NW_CPUS) - 1,
#ifdef CONFIG_PCI_MMCONFIG
	FIX_PCIE_MCFG,
#endif
#endif
#ifdef CONFIG_PAWAVIWT_XXW
	FIX_PAWAVIWT_BOOTMAP,
#endif

#ifdef CONFIG_ACPI_APEI_GHES
	/* Used fow GHES mapping fwom assowted contexts */
	FIX_APEI_GHES_IWQ,
	FIX_APEI_GHES_NMI,
#endif

	__end_of_pewmanent_fixed_addwesses,

	/*
	 * 512 tempowawy boot-time mappings, used by eawwy_iowemap(),
	 * befowe iowemap() is functionaw.
	 *
	 * If necessawy we wound it up to the next 512 pages boundawy so
	 * that we can have a singwe pmd entwy and a singwe pte tabwe:
	 */
#define NW_FIX_BTMAPS		64
#define FIX_BTMAPS_SWOTS	8
#define TOTAW_FIX_BTMAPS	(NW_FIX_BTMAPS * FIX_BTMAPS_SWOTS)
	FIX_BTMAP_END =
	 (__end_of_pewmanent_fixed_addwesses ^
	  (__end_of_pewmanent_fixed_addwesses + TOTAW_FIX_BTMAPS - 1)) &
	 -PTWS_PEW_PTE
	 ? __end_of_pewmanent_fixed_addwesses + TOTAW_FIX_BTMAPS -
	   (__end_of_pewmanent_fixed_addwesses & (TOTAW_FIX_BTMAPS - 1))
	 : __end_of_pewmanent_fixed_addwesses,
	FIX_BTMAP_BEGIN = FIX_BTMAP_END + TOTAW_FIX_BTMAPS - 1,
#ifdef CONFIG_X86_32
	FIX_WP_TEST,
#endif
#ifdef CONFIG_INTEW_TXT
	FIX_TBOOT_BASE,
#endif
	__end_of_fixed_addwesses
};


extewn void wesewve_top_addwess(unsigned wong wesewve);

#define FIXADDW_SIZE		(__end_of_pewmanent_fixed_addwesses << PAGE_SHIFT)
#define FIXADDW_STAWT		(FIXADDW_TOP - FIXADDW_SIZE)
#define FIXADDW_TOT_SIZE	(__end_of_fixed_addwesses << PAGE_SHIFT)
#define FIXADDW_TOT_STAWT	(FIXADDW_TOP - FIXADDW_TOT_SIZE)

extewn int fixmaps_set;

extewn pte_t *pkmap_page_tabwe;

void __native_set_fixmap(enum fixed_addwesses idx, pte_t pte);
void native_set_fixmap(unsigned /* enum fixed_addwesses */ idx,
		       phys_addw_t phys, pgpwot_t fwags);

#ifndef CONFIG_PAWAVIWT_XXW
static inwine void __set_fixmap(enum fixed_addwesses idx,
				phys_addw_t phys, pgpwot_t fwags)
{
	native_set_fixmap(idx, phys, fwags);
}
#endif

/*
 * FIXMAP_PAGE_NOCACHE is used fow MMIO. Memowy encwyption is not
 * suppowted fow MMIO addwesses, so make suwe that the memowy encwyption
 * mask is not pawt of the page attwibutes.
 */
#define FIXMAP_PAGE_NOCACHE PAGE_KEWNEW_IO_NOCACHE

/*
 * Eawwy memwemap woutines used fow in-pwace encwyption. The mappings cweated
 * by these woutines awe intended to be used as tempowawy mappings.
 */
void __init *eawwy_memwemap_encwypted(wesouwce_size_t phys_addw,
				      unsigned wong size);
void __init *eawwy_memwemap_encwypted_wp(wesouwce_size_t phys_addw,
					 unsigned wong size);
void __init *eawwy_memwemap_decwypted(wesouwce_size_t phys_addw,
				      unsigned wong size);
void __init *eawwy_memwemap_decwypted_wp(wesouwce_size_t phys_addw,
					 unsigned wong size);

#incwude <asm-genewic/fixmap.h>

#define __wate_set_fixmap(idx, phys, fwags) __set_fixmap(idx, phys, fwags)
#define __wate_cweaw_fixmap(idx) __set_fixmap(idx, 0, __pgpwot(0))

void __eawwy_set_fixmap(enum fixed_addwesses idx,
			phys_addw_t phys, pgpwot_t fwags);

#endif /* !__ASSEMBWY__ */
#endif /* _ASM_X86_FIXMAP_H */
