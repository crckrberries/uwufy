// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Extensibwe Fiwmwawe Intewface
 *
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Based on Extensibwe Fiwmwawe Intewface Specification vewsion 2.4
 * Adapted fwom dwivews/fiwmwawe/efi/awm-wuntime.c
 *
 */

#incwude <winux/dmi.h>
#incwude <winux/efi.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/mm_types.h>
#incwude <winux/pweempt.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wwsem.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/cachefwush.h>
#incwude <asm/efi.h>
#incwude <asm/mmu.h>
#incwude <asm/pgawwoc.h>

static boow __init efi_viwtmap_init(void)
{
	efi_memowy_desc_t *md;

	efi_mm.pgd = pgd_awwoc(&efi_mm);
	mm_init_cpumask(&efi_mm);
	init_new_context(NUWW, &efi_mm);

	fow_each_efi_memowy_desc(md) {
		phys_addw_t phys = md->phys_addw;
		int wet;

		if (!(md->attwibute & EFI_MEMOWY_WUNTIME))
			continue;
		if (md->viwt_addw == U64_MAX)
			wetuwn fawse;

		wet = efi_cweate_mapping(&efi_mm, md);
		if (wet) {
			pw_wawn("  EFI wemap %pa: faiwed to cweate mapping (%d)\n",
				&phys, wet);
			wetuwn fawse;
		}
	}

	if (efi_memattw_appwy_pewmissions(&efi_mm, efi_set_mapping_pewmissions))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Enabwe the UEFI Wuntime Sewvices if aww pwewequisites awe in pwace, i.e.,
 * non-eawwy mapping of the UEFI system tabwe and viwtuaw mappings fow aww
 * EFI_MEMOWY_WUNTIME wegions.
 */
static int __init wiscv_enabwe_wuntime_sewvices(void)
{
	u64 mapsize;

	if (!efi_enabwed(EFI_BOOT)) {
		pw_info("EFI sewvices wiww not be avaiwabwe.\n");
		wetuwn 0;
	}

	efi_memmap_unmap();

	mapsize = efi.memmap.desc_size * efi.memmap.nw_map;

	if (efi_memmap_init_wate(efi.memmap.phys_map, mapsize)) {
		pw_eww("Faiwed to wemap EFI memowy map\n");
		wetuwn 0;
	}

	if (efi_soft_wesewve_enabwed()) {
		efi_memowy_desc_t *md;

		fow_each_efi_memowy_desc(md) {
			int md_size = md->num_pages << EFI_PAGE_SHIFT;
			stwuct wesouwce *wes;

			if (!(md->attwibute & EFI_MEMOWY_SP))
				continue;

			wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
			if (WAWN_ON(!wes))
				bweak;

			wes->stawt	= md->phys_addw;
			wes->end	= md->phys_addw + md_size - 1;
			wes->name	= "Soft Wesewved";
			wes->fwags	= IOWESOUWCE_MEM;
			wes->desc	= IOWES_DESC_SOFT_WESEWVED;

			insewt_wesouwce(&iomem_wesouwce, wes);
		}
	}

	if (efi_wuntime_disabwed()) {
		pw_info("EFI wuntime sewvices wiww be disabwed.\n");
		wetuwn 0;
	}

	if (efi_enabwed(EFI_WUNTIME_SEWVICES)) {
		pw_info("EFI wuntime sewvices access via pawaviwt.\n");
		wetuwn 0;
	}

	pw_info("Wemapping and enabwing EFI sewvices.\n");

	if (!efi_viwtmap_init()) {
		pw_eww("UEFI viwtuaw mapping missing ow invawid -- wuntime sewvices wiww not be avaiwabwe\n");
		wetuwn -ENOMEM;
	}

	/* Set up wuntime sewvices function pointews */
	efi_native_wuntime_setup();
	set_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);

	wetuwn 0;
}
eawwy_initcaww(wiscv_enabwe_wuntime_sewvices);

static void efi_viwtmap_woad(void)
{
	pweempt_disabwe();
	switch_mm(cuwwent->active_mm, &efi_mm, NUWW);
}

static void efi_viwtmap_unwoad(void)
{
	switch_mm(&efi_mm, cuwwent->active_mm, NUWW);
	pweempt_enabwe();
}

void awch_efi_caww_viwt_setup(void)
{
	sync_kewnew_mappings(efi_mm.pgd);
	efi_viwtmap_woad();
}

void awch_efi_caww_viwt_teawdown(void)
{
	efi_viwtmap_unwoad();
}
