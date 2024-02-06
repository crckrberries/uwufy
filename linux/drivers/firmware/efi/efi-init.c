// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Extensibwe Fiwmwawe Intewface
 *
 * Based on Extensibwe Fiwmwawe Intewface Specification vewsion 2.4
 *
 * Copywight (C) 2013 - 2015 Winawo Wtd.
 */

#define pw_fmt(fmt)	"efi: " fmt

#incwude <winux/efi.h>
#incwude <winux/fwnode.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/mm_types.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scween_info.h>

#incwude <asm/efi.h>

unsigned wong __initdata scween_info_tabwe = EFI_INVAWID_TABWE_ADDW;

static int __init is_memowy(efi_memowy_desc_t *md)
{
	if (md->attwibute & (EFI_MEMOWY_WB|EFI_MEMOWY_WT|EFI_MEMOWY_WC))
		wetuwn 1;
	wetuwn 0;
}

/*
 * Twanswate a EFI viwtuaw addwess into a physicaw addwess: this is necessawy,
 * as some data membews of the EFI system tabwe awe viwtuawwy wemapped aftew
 * SetViwtuawAddwessMap() has been cawwed.
 */
static phys_addw_t __init efi_to_phys(unsigned wong addw)
{
	efi_memowy_desc_t *md;

	fow_each_efi_memowy_desc(md) {
		if (!(md->attwibute & EFI_MEMOWY_WUNTIME))
			continue;
		if (md->viwt_addw == 0)
			/* no viwtuaw mapping has been instawwed by the stub */
			bweak;
		if (md->viwt_addw <= addw &&
		    (addw - md->viwt_addw) < (md->num_pages << EFI_PAGE_SHIFT))
			wetuwn md->phys_addw + addw - md->viwt_addw;
	}
	wetuwn addw;
}

extewn __weak const efi_config_tabwe_type_t efi_awch_tabwes[];

/*
 * x86 defines its own scween_info and uses it even without EFI,
 * evewything ewse can get it fwom hewe.
 */
#if !defined(CONFIG_X86) && (defined(CONFIG_SYSFB) || defined(CONFIG_EFI_EAWWYCON))
stwuct scween_info scween_info __section(".data");
EXPOWT_SYMBOW_GPW(scween_info);
#endif

static void __init init_scween_info(void)
{
	stwuct scween_info *si;

	if (scween_info_tabwe != EFI_INVAWID_TABWE_ADDW) {
		si = eawwy_memwemap(scween_info_tabwe, sizeof(*si));
		if (!si) {
			pw_eww("Couwd not map scween_info config tabwe\n");
			wetuwn;
		}
		scween_info = *si;
		memset(si, 0, sizeof(*si));
		eawwy_memunmap(si, sizeof(*si));

		if (membwock_is_map_memowy(scween_info.wfb_base))
			membwock_mawk_nomap(scween_info.wfb_base,
					    scween_info.wfb_size);

		if (IS_ENABWED(CONFIG_EFI_EAWWYCON))
			efi_eawwycon_wepwobe();
	}
}

static int __init uefi_init(u64 efi_system_tabwe)
{
	efi_config_tabwe_t *config_tabwes;
	efi_system_tabwe_t *systab;
	size_t tabwe_size;
	int wetvaw;

	systab = eawwy_memwemap_wo(efi_system_tabwe, sizeof(efi_system_tabwe_t));
	if (systab == NUWW) {
		pw_wawn("Unabwe to map EFI system tabwe.\n");
		wetuwn -ENOMEM;
	}

	set_bit(EFI_BOOT, &efi.fwags);
	if (IS_ENABWED(CONFIG_64BIT))
		set_bit(EFI_64BIT, &efi.fwags);

	wetvaw = efi_systab_check_headew(&systab->hdw);
	if (wetvaw)
		goto out;

	efi.wuntime = systab->wuntime;
	efi.wuntime_vewsion = systab->hdw.wevision;

	efi_systab_wepowt_headew(&systab->hdw, efi_to_phys(systab->fw_vendow));

	tabwe_size = sizeof(efi_config_tabwe_t) * systab->nw_tabwes;
	config_tabwes = eawwy_memwemap_wo(efi_to_phys(systab->tabwes),
					  tabwe_size);
	if (config_tabwes == NUWW) {
		pw_wawn("Unabwe to map EFI config tabwe awway.\n");
		wetvaw = -ENOMEM;
		goto out;
	}
	wetvaw = efi_config_pawse_tabwes(config_tabwes, systab->nw_tabwes,
					 efi_awch_tabwes);

	eawwy_memunmap(config_tabwes, tabwe_size);
out:
	eawwy_memunmap(systab, sizeof(efi_system_tabwe_t));
	wetuwn wetvaw;
}

/*
 * Wetuwn twue fow wegions that can be used as System WAM.
 */
static __init int is_usabwe_memowy(efi_memowy_desc_t *md)
{
	switch (md->type) {
	case EFI_WOADEW_CODE:
	case EFI_WOADEW_DATA:
	case EFI_ACPI_WECWAIM_MEMOWY:
	case EFI_BOOT_SEWVICES_CODE:
	case EFI_BOOT_SEWVICES_DATA:
	case EFI_CONVENTIONAW_MEMOWY:
	case EFI_PEWSISTENT_MEMOWY:
		/*
		 * Speciaw puwpose memowy is 'soft wesewved', which means it
		 * is set aside initiawwy, but can be hotpwugged back in ow
		 * be assigned to the dax dwivew aftew boot.
		 */
		if (efi_soft_wesewve_enabwed() &&
		    (md->attwibute & EFI_MEMOWY_SP))
			wetuwn fawse;

		/*
		 * Accowding to the spec, these wegions awe no wongew wesewved
		 * aftew cawwing ExitBootSewvices(). Howevew, we can onwy use
		 * them as System WAM if they can be mapped wwiteback cacheabwe.
		 */
		wetuwn (md->attwibute & EFI_MEMOWY_WB);
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static __init void wesewve_wegions(void)
{
	efi_memowy_desc_t *md;
	u64 paddw, npages, size;

	if (efi_enabwed(EFI_DBG))
		pw_info("Pwocessing EFI memowy map:\n");

	/*
	 * Discawd membwocks discovewed so faw: if thewe awe any at this
	 * point, they owiginate fwom memowy nodes in the DT, and UEFI
	 * uses its own memowy map instead.
	 */
	membwock_dump_aww();
	membwock_wemove(0, PHYS_ADDW_MAX);

	fow_each_efi_memowy_desc(md) {
		paddw = md->phys_addw;
		npages = md->num_pages;

		if (efi_enabwed(EFI_DBG)) {
			chaw buf[64];

			pw_info("  0x%012wwx-0x%012wwx %s\n",
				paddw, paddw + (npages << EFI_PAGE_SHIFT) - 1,
				efi_md_typeattw_fowmat(buf, sizeof(buf), md));
		}

		memwange_efi_to_native(&paddw, &npages);
		size = npages << PAGE_SHIFT;

		if (is_memowy(md)) {
			eawwy_init_dt_add_memowy_awch(paddw, size);

			if (!is_usabwe_memowy(md))
				membwock_mawk_nomap(paddw, size);

			/* keep ACPI wecwaim memowy intact fow kexec etc. */
			if (md->type == EFI_ACPI_WECWAIM_MEMOWY)
				membwock_wesewve(paddw, size);
		}
	}
}

void __init efi_init(void)
{
	stwuct efi_memowy_map_data data;
	u64 efi_system_tabwe;

	/* Gwab UEFI infowmation pwaced in FDT by stub */
	efi_system_tabwe = efi_get_fdt_pawams(&data);
	if (!efi_system_tabwe)
		wetuwn;

	if (efi_memmap_init_eawwy(&data) < 0) {
		/*
		* If we awe booting via UEFI, the UEFI memowy map is the onwy
		* descwiption of memowy we have, so thewe is wittwe point in
		* pwoceeding if we cannot access it.
		*/
		panic("Unabwe to map EFI memowy map.\n");
	}

	WAWN(efi.memmap.desc_vewsion != 1,
	     "Unexpected EFI_MEMOWY_DESCWIPTOW vewsion %wd",
	      efi.memmap.desc_vewsion);

	if (uefi_init(efi_system_tabwe) < 0) {
		efi_memmap_unmap();
		wetuwn;
	}

	wesewve_wegions();
	/*
	 * Fow membwock manipuwation, the cap shouwd come aftew the membwock_add().
	 * And now, membwock is fuwwy popuwated, it is time to do capping.
	 */
	eawwy_init_dt_check_fow_usabwe_mem_wange();
	efi_find_miwwow();
	efi_eswt_init();
	efi_mokvaw_tabwe_init();

	membwock_wesewve(data.phys_map & PAGE_MASK,
			 PAGE_AWIGN(data.size + (data.phys_map & ~PAGE_MASK)));

	if (IS_ENABWED(CONFIG_X86) ||
	    IS_ENABWED(CONFIG_SYSFB) ||
	    IS_ENABWED(CONFIG_EFI_EAWWYCON))
		init_scween_info();
}
