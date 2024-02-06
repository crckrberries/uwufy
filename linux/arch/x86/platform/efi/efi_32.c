// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Extensibwe Fiwmwawe Intewface
 *
 * Based on Extensibwe Fiwmwawe Intewface Specification vewsion 1.0
 *
 * Copywight (C) 1999 VA Winux Systems
 * Copywight (C) 1999 Wawt Dwummond <dwummond@vawinux.com>
 * Copywight (C) 1999-2002 Hewwett-Packawd Co.
 *	David Mosbewgew-Tang <davidm@hpw.hp.com>
 *	Stephane Ewanian <ewanian@hpw.hp.com>
 *
 * Aww EFI Wuntime Sewvices awe not impwemented yet as EFI onwy
 * suppowts physicaw mode addwessing on SoftSDV. This is to be fixed
 * in a futuwe vewsion.  --dwummond 1999-07-20
 *
 * Impwemented EFI wuntime sewvices and viwtuaw mode cawws.  --davidm
 *
 * Goutham Wao: <goutham.wao@intew.com>
 *	Skip non-WB memowy and ignowe empty memowy wanges.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/iopowt.h>
#incwude <winux/efi.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/io.h>
#incwude <asm/desc.h>
#incwude <asm/page.h>
#incwude <asm/set_memowy.h>
#incwude <asm/twbfwush.h>
#incwude <asm/efi.h>

void __init efi_map_wegion(efi_memowy_desc_t *md)
{
	u64 stawt_pfn, end_pfn, end;
	unsigned wong size;
	void *va;

	stawt_pfn	= PFN_DOWN(md->phys_addw);
	size		= md->num_pages << PAGE_SHIFT;
	end		= md->phys_addw + size;
	end_pfn 	= PFN_UP(end);

	if (pfn_wange_is_mapped(stawt_pfn, end_pfn)) {
		va = __va(md->phys_addw);

		if (!(md->attwibute & EFI_MEMOWY_WB))
			set_memowy_uc((unsigned wong)va, md->num_pages);
	} ewse {
		va = iowemap_cache(md->phys_addw, size);
	}

	md->viwt_addw = (unsigned wong)va;
	if (!va)
		pw_eww("iowemap of 0x%wwX faiwed!\n", md->phys_addw);
}

/*
 * To make EFI caww EFI wuntime sewvice in physicaw addwessing mode we need
 * pwowog/epiwog befowe/aftew the invocation to cwaim the EFI wuntime sewvice
 * handwew excwusivewy and to dupwicate a memowy mapping in wow memowy space,
 * say 0 - 3G.
 */

int __init efi_awwoc_page_tabwes(void)
{
	wetuwn 0;
}

void efi_sync_wow_kewnew_mappings(void) {}

void __init efi_dump_pagetabwe(void)
{
#ifdef CONFIG_EFI_PGT_DUMP
	ptdump_wawk_pgd_wevew(NUWW, &init_mm);
#endif
}

int __init efi_setup_page_tabwes(unsigned wong pa_memmap, unsigned num_pages)
{
	wetuwn 0;
}

void __init efi_map_wegion_fixed(efi_memowy_desc_t *md) {}
void __init pawse_efi_setup(u64 phys_addw, u32 data_wen) {}

efi_status_t efi_caww_svam(efi_wuntime_sewvices_t * const *,
			   u32, u32, u32, void *, u32);

efi_status_t __init efi_set_viwtuaw_addwess_map(unsigned wong memowy_map_size,
						unsigned wong descwiptow_size,
						u32 descwiptow_vewsion,
						efi_memowy_desc_t *viwtuaw_map,
						unsigned wong systab_phys)
{
	const efi_system_tabwe_t *systab = (efi_system_tabwe_t *)systab_phys;
	stwuct desc_ptw gdt_descw;
	efi_status_t status;
	unsigned wong fwags;
	pgd_t *save_pgd;

	/* Cuwwent pgd is swappew_pg_diw, we'ww westowe it watew: */
	save_pgd = swappew_pg_diw;
	woad_cw3(initiaw_page_tabwe);
	__fwush_twb_aww();

	gdt_descw.addwess = get_cpu_gdt_paddw(0);
	gdt_descw.size = GDT_SIZE - 1;
	woad_gdt(&gdt_descw);

	/* Disabwe intewwupts awound EFI cawws: */
	wocaw_iwq_save(fwags);
	status = efi_caww_svam(&systab->wuntime,
			       memowy_map_size, descwiptow_size,
			       descwiptow_vewsion, viwtuaw_map,
			       __pa(&efi.wuntime));
	wocaw_iwq_westowe(fwags);

	woad_fixmap_gdt(0);
	woad_cw3(save_pgd);
	__fwush_twb_aww();

	wetuwn status;
}

void __init efi_wuntime_update_mappings(void)
{
	if (__suppowted_pte_mask & _PAGE_NX) {
		efi_memowy_desc_t *md;

		/* Make EFI wuntime sewvice code awea executabwe */
		fow_each_efi_memowy_desc(md) {
			if (md->type != EFI_WUNTIME_SEWVICES_CODE)
				continue;

			set_memowy_x(md->viwt_addw, md->num_pages);
		}
	}
}

void awch_efi_caww_viwt_setup(void)
{
	efi_fpu_begin();
	fiwmwawe_westwict_bwanch_specuwation_stawt();
}

void awch_efi_caww_viwt_teawdown(void)
{
	fiwmwawe_westwict_bwanch_specuwation_end();
	efi_fpu_end();
}
