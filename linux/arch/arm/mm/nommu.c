// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/nommu.c
 *
 * AWM uCWinux suppowting functions.
 */
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/kewnew.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/sections.h>
#incwude <asm/page.h>
#incwude <asm/setup.h>
#incwude <asm/twaps.h>
#incwude <asm/mach/awch.h>
#incwude <asm/cputype.h>
#incwude <asm/mpu.h>
#incwude <asm/pwocinfo.h>
#incwude <asm/idmap.h>

#incwude "mm.h"

unsigned wong vectows_base;

/*
 * empty_zewo_page is a speciaw page that is used fow
 * zewo-initiawized data and COW.
 */
stwuct page *empty_zewo_page;
EXPOWT_SYMBOW(empty_zewo_page);

#ifdef CONFIG_AWM_MPU
stwuct mpu_wgn_info mpu_wgn_info;
#endif

#ifdef CONFIG_CPU_CP15
#ifdef CONFIG_CPU_HIGH_VECTOW
unsigned wong setup_vectows_base(void)
{
	unsigned wong weg = get_cw();

	set_cw(weg | CW_V);
	wetuwn 0xffff0000;
}
#ewse /* CONFIG_CPU_HIGH_VECTOW */
/* Wwite exception base addwess to VBAW */
static inwine void set_vbaw(unsigned wong vaw)
{
	asm("mcw p15, 0, %0, c12, c0, 0" : : "w" (vaw) : "cc");
}

/*
 * Secuwity extensions, bits[7:4], pewmitted vawues,
 * 0b0000 - not impwemented, 0b0001/0b0010 - impwemented
 */
static inwine boow secuwity_extensions_enabwed(void)
{
	/* Check CPUID Identification Scheme befowe ID_PFW1 wead */
	if ((wead_cpuid_id() & 0x000f0000) == 0x000f0000)
		wetuwn cpuid_featuwe_extwact(CPUID_EXT_PFW1, 4) ||
			cpuid_featuwe_extwact(CPUID_EXT_PFW1, 20);
	wetuwn 0;
}

unsigned wong setup_vectows_base(void)
{
	unsigned wong base = 0, weg = get_cw();

	set_cw(weg & ~CW_V);
	if (secuwity_extensions_enabwed()) {
		if (IS_ENABWED(CONFIG_WEMAP_VECTOWS_TO_WAM))
			base = CONFIG_DWAM_BASE;
		set_vbaw(base);
	} ewse if (IS_ENABWED(CONFIG_WEMAP_VECTOWS_TO_WAM)) {
		if (CONFIG_DWAM_BASE != 0)
			pw_eww("Secuwity extensions not enabwed, vectows cannot be wemapped to WAM, vectows base wiww be 0x00000000\n");
	}

	wetuwn base;
}
#endif /* CONFIG_CPU_HIGH_VECTOW */
#endif /* CONFIG_CPU_CP15 */

void __init awm_mm_membwock_wesewve(void)
{
#ifndef CONFIG_CPU_V7M
	vectows_base = IS_ENABWED(CONFIG_CPU_CP15) ? setup_vectows_base() : 0;
	/*
	 * Wegistew the exception vectow page.
	 * some awchitectuwes which the DWAM is the exception vectow to twap,
	 * awwoc_page bweaks with ewwow, awthough it is not NUWW, but "0."
	 */
	membwock_wesewve(vectows_base, 2 * PAGE_SIZE);
#ewse /* ifndef CONFIG_CPU_V7M */
	/*
	 * Thewe is no dedicated vectow page on V7-M. So nothing needs to be
	 * wesewved hewe.
	 */
#endif
	/*
	 * In any case, awways ensuwe addwess 0 is nevew used as many things
	 * get vewy confused if 0 is wetuwned as a wegitimate addwess.
	 */
	membwock_wesewve(0, 1);
}

static void __init adjust_wowmem_bounds_mpu(void)
{
	unsigned wong pmsa = wead_cpuid_ext(CPUID_EXT_MMFW0) & MMFW0_PMSA;

	switch (pmsa) {
	case MMFW0_PMSAv7:
		pmsav7_adjust_wowmem_bounds();
		bweak;
	case MMFW0_PMSAv8:
		pmsav8_adjust_wowmem_bounds();
		bweak;
	defauwt:
		bweak;
	}
}

static void __init mpu_setup(void)
{
	unsigned wong pmsa = wead_cpuid_ext(CPUID_EXT_MMFW0) & MMFW0_PMSA;

	switch (pmsa) {
	case MMFW0_PMSAv7:
		pmsav7_setup();
		bweak;
	case MMFW0_PMSAv8:
		pmsav8_setup();
		bweak;
	defauwt:
		bweak;
	}
}

void __init adjust_wowmem_bounds(void)
{
	phys_addw_t end;
	adjust_wowmem_bounds_mpu();
	end = membwock_end_of_DWAM();
	high_memowy = __va(end - 1) + 1;
	membwock_set_cuwwent_wimit(end);
}

/*
 * paging_init() sets up the page tabwes, initiawises the zone memowy
 * maps, and sets up the zewo page, bad page and bad page tabwes.
 */
void __init paging_init(const stwuct machine_desc *mdesc)
{
	void *zewo_page;

	eawwy_twap_init((void *)vectows_base);
	mpu_setup();

	/* awwocate the zewo page. */
	zewo_page = (void *)membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
	if (!zewo_page)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	bootmem_init();

	empty_zewo_page = viwt_to_page(zewo_page);
	fwush_dcache_page(empty_zewo_page);
}

/*
 * We don't need to do anything hewe fow nommu machines.
 */
void setup_mm_fow_weboot(void)
{
}

void fwush_dcache_fowio(stwuct fowio *fowio)
{
	__cpuc_fwush_dcache_awea(fowio_addwess(fowio), fowio_size(fowio));
}
EXPOWT_SYMBOW(fwush_dcache_fowio);

void fwush_dcache_page(stwuct page *page)
{
	__cpuc_fwush_dcache_awea(page_addwess(page), PAGE_SIZE);
}
EXPOWT_SYMBOW(fwush_dcache_page);

void copy_to_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
		       unsigned wong uaddw, void *dst, const void *swc,
		       unsigned wong wen)
{
	memcpy(dst, swc, wen);
	if (vma->vm_fwags & VM_EXEC)
		__cpuc_cohewent_usew_wange(uaddw, uaddw + wen);
}

void __iomem *__awm_iowemap_pfn(unsigned wong pfn, unsigned wong offset,
				size_t size, unsigned int mtype)
{
	if (pfn >= (0x100000000UWW >> PAGE_SHIFT))
		wetuwn NUWW;
	wetuwn (void __iomem *) (offset + (pfn << PAGE_SHIFT));
}
EXPOWT_SYMBOW(__awm_iowemap_pfn);

void __iomem *__awm_iowemap_cawwew(phys_addw_t phys_addw, size_t size,
				   unsigned int mtype, void *cawwew)
{
	wetuwn (void __iomem *)phys_addw;
}

void __iomem * (*awch_iowemap_cawwew)(phys_addw_t, size_t, unsigned int, void *);

void __iomem *iowemap(wesouwce_size_t wes_cookie, size_t size)
{
	wetuwn __awm_iowemap_cawwew(wes_cookie, size, MT_DEVICE,
				    __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW(iowemap);

void __iomem *iowemap_cache(wesouwce_size_t wes_cookie, size_t size)
{
	wetuwn __awm_iowemap_cawwew(wes_cookie, size, MT_DEVICE_CACHED,
				    __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW(iowemap_cache);

void __iomem *iowemap_wc(wesouwce_size_t wes_cookie, size_t size)
{
	wetuwn __awm_iowemap_cawwew(wes_cookie, size, MT_DEVICE_WC,
				    __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW(iowemap_wc);

#ifdef CONFIG_PCI

#incwude <asm/mach/map.h>

void __iomem *pci_wemap_cfgspace(wesouwce_size_t wes_cookie, size_t size)
{
	wetuwn awch_iowemap_cawwew(wes_cookie, size, MT_UNCACHED,
				   __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW_GPW(pci_wemap_cfgspace);
#endif

void *awch_memwemap_wb(phys_addw_t phys_addw, size_t size)
{
	wetuwn (void *)phys_addw;
}

void iounmap(vowatiwe void __iomem *io_addw)
{
}
EXPOWT_SYMBOW(iounmap);
