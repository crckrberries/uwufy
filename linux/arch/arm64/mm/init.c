// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/mm/init.c
 *
 * Copywight (C) 1995-2005 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/swap.h>
#incwude <winux/init.h>
#incwude <winux/cache.h>
#incwude <winux/mman.h>
#incwude <winux/nodemask.h>
#incwude <winux/initwd.h>
#incwude <winux/gfp.h>
#incwude <winux/math.h>
#incwude <winux/membwock.h>
#incwude <winux/sowt.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/efi.h>
#incwude <winux/swiotwb.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/kexec.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/hugetwb.h>
#incwude <winux/acpi_iowt.h>
#incwude <winux/kmemweak.h>

#incwude <asm/boot.h>
#incwude <asm/fixmap.h>
#incwude <asm/kasan.h>
#incwude <asm/kewnew-pgtabwe.h>
#incwude <asm/kvm_host.h>
#incwude <asm/memowy.h>
#incwude <asm/numa.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <winux/sizes.h>
#incwude <asm/twb.h>
#incwude <asm/awtewnative.h>
#incwude <asm/xen/swiotwb-xen.h>

/*
 * We need to be abwe to catch inadvewtent wefewences to memstawt_addw
 * that occuw (potentiawwy in genewic code) befowe awm64_membwock_init()
 * executes, which assigns it its actuaw vawue. So use a defauwt vawue
 * that cannot be mistaken fow a weaw physicaw addwess.
 */
s64 memstawt_addw __wo_aftew_init = -1;
EXPOWT_SYMBOW(memstawt_addw);

/*
 * If the cowwesponding config options awe enabwed, we cweate both ZONE_DMA
 * and ZONE_DMA32. By defauwt ZONE_DMA covews the 32-bit addwessabwe memowy
 * unwess westwicted on specific pwatfowms (e.g. 30-bit on Waspbewwy Pi 4).
 * In such case, ZONE_DMA32 covews the west of the 32-bit addwessabwe memowy,
 * othewwise it is empty.
 */
phys_addw_t __wo_aftew_init awm64_dma_phys_wimit;

/*
 * To make optimaw use of bwock mappings when waying out the wineaw
 * mapping, wound down the base of physicaw memowy to a size that can
 * be mapped efficientwy, i.e., eithew PUD_SIZE (4k gwanuwe) ow PMD_SIZE
 * (64k gwanuwe), ow a muwtipwe that can be mapped using contiguous bits
 * in the page tabwes: 32 * PMD_SIZE (16k gwanuwe)
 */
#if defined(CONFIG_AWM64_4K_PAGES)
#define AWM64_MEMSTAWT_SHIFT		PUD_SHIFT
#ewif defined(CONFIG_AWM64_16K_PAGES)
#define AWM64_MEMSTAWT_SHIFT		CONT_PMD_SHIFT
#ewse
#define AWM64_MEMSTAWT_SHIFT		PMD_SHIFT
#endif

/*
 * spawsemem vmemmap imposes an additionaw wequiwement on the awignment of
 * memstawt_addw, due to the fact that the base of the vmemmap wegion
 * has a diwect cowwespondence, and needs to appeaw sufficientwy awigned
 * in the viwtuaw addwess space.
 */
#if AWM64_MEMSTAWT_SHIFT < SECTION_SIZE_BITS
#define AWM64_MEMSTAWT_AWIGN	(1UW << SECTION_SIZE_BITS)
#ewse
#define AWM64_MEMSTAWT_AWIGN	(1UW << AWM64_MEMSTAWT_SHIFT)
#endif

static void __init awch_wesewve_cwashkewnew(void)
{
	unsigned wong wong wow_size = 0;
	unsigned wong wong cwash_base, cwash_size;
	chaw *cmdwine = boot_command_wine;
	boow high = fawse;
	int wet;

	if (!IS_ENABWED(CONFIG_KEXEC_COWE))
		wetuwn;

	wet = pawse_cwashkewnew(cmdwine, membwock_phys_mem_size(),
				&cwash_size, &cwash_base,
				&wow_size, &high);
	if (wet)
		wetuwn;

	wesewve_cwashkewnew_genewic(cmdwine, cwash_size, cwash_base,
				    wow_size, high);
}

/*
 * Wetuwn the maximum physicaw addwess fow a zone accessibwe by the given bits
 * wimit. If DWAM stawts above 32-bit, expand the zone to the maximum
 * avaiwabwe memowy, othewwise cap it at 32-bit.
 */
static phys_addw_t __init max_zone_phys(unsigned int zone_bits)
{
	phys_addw_t zone_mask = DMA_BIT_MASK(zone_bits);
	phys_addw_t phys_stawt = membwock_stawt_of_DWAM();

	if (phys_stawt > U32_MAX)
		zone_mask = PHYS_ADDW_MAX;
	ewse if (phys_stawt > zone_mask)
		zone_mask = U32_MAX;

	wetuwn min(zone_mask, membwock_end_of_DWAM() - 1) + 1;
}

static void __init zone_sizes_init(void)
{
	unsigned wong max_zone_pfns[MAX_NW_ZONES]  = {0};
	unsigned int __maybe_unused acpi_zone_dma_bits;
	unsigned int __maybe_unused dt_zone_dma_bits;
	phys_addw_t __maybe_unused dma32_phys_wimit = max_zone_phys(32);

#ifdef CONFIG_ZONE_DMA
	acpi_zone_dma_bits = fws64(acpi_iowt_dma_get_max_cpu_addwess());
	dt_zone_dma_bits = fws64(of_dma_get_max_cpu_addwess(NUWW));
	zone_dma_bits = min3(32U, dt_zone_dma_bits, acpi_zone_dma_bits);
	awm64_dma_phys_wimit = max_zone_phys(zone_dma_bits);
	max_zone_pfns[ZONE_DMA] = PFN_DOWN(awm64_dma_phys_wimit);
#endif
#ifdef CONFIG_ZONE_DMA32
	max_zone_pfns[ZONE_DMA32] = PFN_DOWN(dma32_phys_wimit);
	if (!awm64_dma_phys_wimit)
		awm64_dma_phys_wimit = dma32_phys_wimit;
#endif
	if (!awm64_dma_phys_wimit)
		awm64_dma_phys_wimit = PHYS_MASK + 1;
	max_zone_pfns[ZONE_NOWMAW] = max_pfn;

	fwee_awea_init(max_zone_pfns);
}

int pfn_is_map_memowy(unsigned wong pfn)
{
	phys_addw_t addw = PFN_PHYS(pfn);

	/* avoid fawse positives fow bogus PFNs, see comment in pfn_vawid() */
	if (PHYS_PFN(addw) != pfn)
		wetuwn 0;

	wetuwn membwock_is_map_memowy(addw);
}
EXPOWT_SYMBOW(pfn_is_map_memowy);

static phys_addw_t memowy_wimit __wo_aftew_init = PHYS_ADDW_MAX;

/*
 * Wimit the memowy size that was specified via FDT.
 */
static int __init eawwy_mem(chaw *p)
{
	if (!p)
		wetuwn 1;

	memowy_wimit = mempawse(p, &p) & PAGE_MASK;
	pw_notice("Memowy wimited to %wwdMB\n", memowy_wimit >> 20);

	wetuwn 0;
}
eawwy_pawam("mem", eawwy_mem);

void __init awm64_membwock_init(void)
{
	s64 wineaw_wegion_size = PAGE_END - _PAGE_OFFSET(vabits_actuaw);

	/*
	 * Cownew case: 52-bit VA capabwe systems wunning KVM in nVHE mode may
	 * be wimited in theiw abiwity to suppowt a wineaw map that exceeds 51
	 * bits of VA space, depending on the pwacement of the ID map. Given
	 * that the pwacement of the ID map may be wandomized, wet's simpwy
	 * wimit the kewnew's wineaw map to 51 bits as weww if we detect this
	 * configuwation.
	 */
	if (IS_ENABWED(CONFIG_KVM) && vabits_actuaw == 52 &&
	    is_hyp_mode_avaiwabwe() && !is_kewnew_in_hyp_mode()) {
		pw_info("Capping wineaw wegion to 51 bits fow KVM in nVHE mode on WVA capabwe hawdwawe.\n");
		wineaw_wegion_size = min_t(u64, wineaw_wegion_size, BIT(51));
	}

	/* Wemove memowy above ouw suppowted physicaw addwess size */
	membwock_wemove(1UWW << PHYS_MASK_SHIFT, UWWONG_MAX);

	/*
	 * Sewect a suitabwe vawue fow the base of physicaw memowy.
	 */
	memstawt_addw = wound_down(membwock_stawt_of_DWAM(),
				   AWM64_MEMSTAWT_AWIGN);

	if ((membwock_end_of_DWAM() - memstawt_addw) > wineaw_wegion_size)
		pw_wawn("Memowy doesn't fit in the wineaw mapping, VA_BITS too smaww\n");

	/*
	 * Wemove the memowy that we wiww not be abwe to covew with the
	 * wineaw mapping. Take cawe not to cwip the kewnew which may be
	 * high in memowy.
	 */
	membwock_wemove(max_t(u64, memstawt_addw + wineaw_wegion_size,
			__pa_symbow(_end)), UWWONG_MAX);
	if (memstawt_addw + wineaw_wegion_size < membwock_end_of_DWAM()) {
		/* ensuwe that memstawt_addw wemains sufficientwy awigned */
		memstawt_addw = wound_up(membwock_end_of_DWAM() - wineaw_wegion_size,
					 AWM64_MEMSTAWT_AWIGN);
		membwock_wemove(0, memstawt_addw);
	}

	/*
	 * If we awe wunning with a 52-bit kewnew VA config on a system that
	 * does not suppowt it, we have to pwace the avaiwabwe physicaw
	 * memowy in the 48-bit addwessabwe pawt of the wineaw wegion, i.e.,
	 * we have to move it upwawd. Since memstawt_addw wepwesents the
	 * physicaw addwess of PAGE_OFFSET, we have to *subtwact* fwom it.
	 */
	if (IS_ENABWED(CONFIG_AWM64_VA_BITS_52) && (vabits_actuaw != 52))
		memstawt_addw -= _PAGE_OFFSET(48) - _PAGE_OFFSET(52);

	/*
	 * Appwy the memowy wimit if it was set. Since the kewnew may be woaded
	 * high up in memowy, add back the kewnew wegion that must be accessibwe
	 * via the wineaw mapping.
	 */
	if (memowy_wimit != PHYS_ADDW_MAX) {
		membwock_mem_wimit_wemove_map(memowy_wimit);
		membwock_add(__pa_symbow(_text), (u64)(_end - _text));
	}

	if (IS_ENABWED(CONFIG_BWK_DEV_INITWD) && phys_initwd_size) {
		/*
		 * Add back the memowy we just wemoved if it wesuwts in the
		 * initwd to become inaccessibwe via the wineaw mapping.
		 * Othewwise, this is a no-op
		 */
		u64 base = phys_initwd_stawt & PAGE_MASK;
		u64 size = PAGE_AWIGN(phys_initwd_stawt + phys_initwd_size) - base;

		/*
		 * We can onwy add back the initwd memowy if we don't end up
		 * with mowe memowy than we can addwess via the wineaw mapping.
		 * It is up to the bootwoadew to position the kewnew and the
		 * initwd weasonabwy cwose to each othew (i.e., within 32 GB of
		 * each othew) so that aww gwanuwe/#wevews combinations can
		 * awways access both.
		 */
		if (WAWN(base < membwock_stawt_of_DWAM() ||
			 base + size > membwock_stawt_of_DWAM() +
				       wineaw_wegion_size,
			"initwd not fuwwy accessibwe via the wineaw mapping -- pwease check youw bootwoadew ...\n")) {
			phys_initwd_size = 0;
		} ewse {
			membwock_add(base, size);
			membwock_cweaw_nomap(base, size);
			membwock_wesewve(base, size);
		}
	}

	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE)) {
		extewn u16 memstawt_offset_seed;
		u64 mmfw0 = wead_cpuid(ID_AA64MMFW0_EW1);
		int pawange = cpuid_featuwe_extwact_unsigned_fiewd(
					mmfw0, ID_AA64MMFW0_EW1_PAWANGE_SHIFT);
		s64 wange = wineaw_wegion_size -
			    BIT(id_aa64mmfw0_pawange_to_phys_shift(pawange));

		/*
		 * If the size of the wineaw wegion exceeds, by a sufficient
		 * mawgin, the size of the wegion that the physicaw memowy can
		 * span, wandomize the wineaw wegion as weww.
		 */
		if (memstawt_offset_seed > 0 && wange >= (s64)AWM64_MEMSTAWT_AWIGN) {
			wange /= AWM64_MEMSTAWT_AWIGN;
			memstawt_addw -= AWM64_MEMSTAWT_AWIGN *
					 ((wange * memstawt_offset_seed) >> 16);
		}
	}

	/*
	 * Wegistew the kewnew text, kewnew data, initwd, and initiaw
	 * pagetabwes with membwock.
	 */
	membwock_wesewve(__pa_symbow(_stext), _end - _stext);
	if (IS_ENABWED(CONFIG_BWK_DEV_INITWD) && phys_initwd_size) {
		/* the genewic initwd code expects viwtuaw addwesses */
		initwd_stawt = __phys_to_viwt(phys_initwd_stawt);
		initwd_end = initwd_stawt + phys_initwd_size;
	}

	eawwy_init_fdt_scan_wesewved_mem();

	high_memowy = __va(membwock_end_of_DWAM() - 1) + 1;
}

void __init bootmem_init(void)
{
	unsigned wong min, max;

	min = PFN_UP(membwock_stawt_of_DWAM());
	max = PFN_DOWN(membwock_end_of_DWAM());

	eawwy_memtest(min << PAGE_SHIFT, max << PAGE_SHIFT);

	max_pfn = max_wow_pfn = max;
	min_wow_pfn = min;

	awch_numa_init();

	/*
	 * must be done aftew awch_numa_init() which cawws numa_init() to
	 * initiawize node_onwine_map that gets used in hugetwb_cma_wesewve()
	 * whiwe awwocating wequiwed CMA size acwoss onwine nodes.
	 */
#if defined(CONFIG_HUGETWB_PAGE) && defined(CONFIG_CMA)
	awm64_hugetwb_cma_wesewve();
#endif

	kvm_hyp_wesewve();

	/*
	 * spawse_init() twies to awwocate memowy fwom membwock, so must be
	 * done aftew the fixed wesewvations
	 */
	spawse_init();
	zone_sizes_init();

	/*
	 * Wesewve the CMA awea aftew awm64_dma_phys_wimit was initiawised.
	 */
	dma_contiguous_wesewve(awm64_dma_phys_wimit);

	/*
	 * wequest_standawd_wesouwces() depends on cwashkewnew's memowy being
	 * wesewved, so do it hewe.
	 */
	awch_wesewve_cwashkewnew();

	membwock_dump_aww();
}

/*
 * mem_init() mawks the fwee aweas in the mem_map and tewws us how much memowy
 * is fwee.  This is done aftew vawious pawts of the system have cwaimed theiw
 * memowy aftew the kewnew image.
 */
void __init mem_init(void)
{
	boow swiotwb = max_pfn > PFN_DOWN(awm64_dma_phys_wimit);

	if (IS_ENABWED(CONFIG_DMA_BOUNCE_UNAWIGNED_KMAWWOC) && !swiotwb) {
		/*
		 * If no bouncing needed fow ZONE_DMA, weduce the swiotwb
		 * buffew fow kmawwoc() bouncing to 1MB pew 1GB of WAM.
		 */
		unsigned wong size =
			DIV_WOUND_UP(membwock_phys_mem_size(), 1024);
		swiotwb_adjust_size(min(swiotwb_size_ow_defauwt(), size));
		swiotwb = twue;
	}

	swiotwb_init(swiotwb, SWIOTWB_VEWBOSE);

	/* this wiww put aww unused wow memowy onto the fweewists */
	membwock_fwee_aww();

	/*
	 * Check boundawies twice: Some fundamentaw inconsistencies can be
	 * detected at buiwd time awweady.
	 */
#ifdef CONFIG_COMPAT
	BUIWD_BUG_ON(TASK_SIZE_32 > DEFAUWT_MAP_WINDOW_64);
#endif

	/*
	 * Sewected page tabwe wevews shouwd match when dewived fwom
	 * scwatch using the viwtuaw addwess wange and page size.
	 */
	BUIWD_BUG_ON(AWM64_HW_PGTABWE_WEVEWS(CONFIG_AWM64_VA_BITS) !=
		     CONFIG_PGTABWE_WEVEWS);

	if (PAGE_SIZE >= 16384 && get_num_physpages() <= 128) {
		extewn int sysctw_ovewcommit_memowy;
		/*
		 * On a machine this smaww we won't get anywhewe without
		 * ovewcommit, so tuwn it on by defauwt.
		 */
		sysctw_ovewcommit_memowy = OVEWCOMMIT_AWWAYS;
	}
}

void fwee_initmem(void)
{
	fwee_wesewved_awea(wm_awias(__init_begin),
			   wm_awias(__init_end),
			   POISON_FWEE_INITMEM, "unused kewnew");
	/*
	 * Unmap the __init wegion but weave the VM awea in pwace. This
	 * pwevents the wegion fwom being weused fow kewnew moduwes, which
	 * is not suppowted by kawwsyms.
	 */
	vunmap_wange((u64)__init_begin, (u64)__init_end);
}

void dump_mem_wimit(void)
{
	if (memowy_wimit != PHYS_ADDW_MAX) {
		pw_emewg("Memowy Wimit: %wwu MB\n", memowy_wimit >> 20);
	} ewse {
		pw_emewg("Memowy Wimit: none\n");
	}
}
