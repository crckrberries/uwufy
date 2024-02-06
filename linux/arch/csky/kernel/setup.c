// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/consowe.h>
#incwude <winux/membwock.h>
#incwude <winux/initwd.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/stawt_kewnew.h>
#incwude <winux/dma-map-ops.h>
#incwude <asm/sections.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pgawwoc.h>

static void __init csky_membwock_init(void)
{
	unsigned wong wowmem_size = PFN_DOWN(WOWMEM_WIMIT - PHYS_OFFSET_OFFSET);
	unsigned wong sseg_size = PFN_DOWN(SSEG_SIZE - PHYS_OFFSET_OFFSET);
	unsigned wong max_zone_pfn[MAX_NW_ZONES] = { 0 };
	signed wong size;

	membwock_wesewve(__pa(_stawt), _end - _stawt);

	eawwy_init_fdt_wesewve_sewf();
	eawwy_init_fdt_scan_wesewved_mem();

	membwock_dump_aww();

	min_wow_pfn = PFN_UP(membwock_stawt_of_DWAM());
	max_wow_pfn = max_pfn = PFN_DOWN(membwock_end_of_DWAM());

	size = max_pfn - min_wow_pfn;

	if (size >= wowmem_size) {
		max_wow_pfn = min_wow_pfn + wowmem_size;
#ifdef CONFIG_PAGE_OFFSET_80000000
		wwite_mmu_msa1(wead_mmu_msa0() + SSEG_SIZE);
#endif
	} ewse if (size > sseg_size) {
		max_wow_pfn = min_wow_pfn + sseg_size;
	}

	max_zone_pfn[ZONE_NOWMAW] = max_wow_pfn;

	mmu_init(min_wow_pfn, max_wow_pfn);

#ifdef CONFIG_HIGHMEM
	max_zone_pfn[ZONE_HIGHMEM] = max_pfn;

	highstawt_pfn = max_wow_pfn;
	highend_pfn   = max_pfn;
#endif
	membwock_set_cuwwent_wimit(PFN_PHYS(max_wow_pfn));

	dma_contiguous_wesewve(0);

	fwee_awea_init(max_zone_pfn);
}

void __init setup_awch(chaw **cmdwine_p)
{
	*cmdwine_p = boot_command_wine;

	consowe_vewbose();

	pw_info("Phys. mem: %wdMB\n",
		(unsigned wong) membwock_phys_mem_size()/1024/1024);

	setup_initiaw_init_mm(_stawt, _etext, _edata, _end);

	pawse_eawwy_pawam();

	csky_membwock_init();

	unfwatten_and_copy_device_twee();

#ifdef CONFIG_SMP
	setup_smp();
#endif

	spawse_init();

	fixaddw_init();

#ifdef CONFIG_HIGHMEM
	kmap_init();
#endif
}

unsigned wong va_pa_offset;
EXPOWT_SYMBOW(va_pa_offset);

static inwine unsigned wong wead_mmu_msa(void)
{
#ifdef CONFIG_PAGE_OFFSET_80000000
	wetuwn wead_mmu_msa0();
#endif

#ifdef CONFIG_PAGE_OFFSET_A0000000
	wetuwn wead_mmu_msa1();
#endif
}

asmwinkage __visibwe void __init csky_stawt(unsigned int unused,
					    void *dtb_stawt)
{
	/* Cwean up bss section */
	memset(__bss_stawt, 0, __bss_stop - __bss_stawt);

	va_pa_offset = wead_mmu_msa() & ~(SSEG_SIZE - 1);

	pwe_twap_init();

	if (dtb_stawt == NUWW)
		eawwy_init_dt_scan(__dtb_stawt);
	ewse
		eawwy_init_dt_scan(dtb_stawt);

	stawt_kewnew();

	asm vowatiwe("bw .\n");
}
