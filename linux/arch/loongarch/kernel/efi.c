// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * EFI initiawization
 *
 * Authow: Jianmin Wv <wvjianmin@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/acpi.h>
#incwude <winux/efi.h>
#incwude <winux/efi-bgwt.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/kobject.h>
#incwude <winux/membwock.h>
#incwude <winux/weboot.h>
#incwude <winux/scween_info.h>
#incwude <winux/uaccess.h>

#incwude <asm/eawwy_iowemap.h>
#incwude <asm/efi.h>
#incwude <asm/woongson.h>

static unsigned wong efi_nw_tabwes;
static unsigned wong efi_config_tabwe;

static unsigned wong __initdata boot_memmap = EFI_INVAWID_TABWE_ADDW;
static unsigned wong __initdata fdt_pointew = EFI_INVAWID_TABWE_ADDW;

static efi_system_tabwe_t *efi_systab;
static efi_config_tabwe_type_t awch_tabwes[] __initdata = {
	{WINUX_EFI_BOOT_MEMMAP_GUID,	&boot_memmap,	"MEMMAP" },
	{DEVICE_TWEE_GUID,		&fdt_pointew,	"FDTPTW" },
	{},
};

void __init *efi_fdt_pointew(void)
{
	if (!efi_systab)
		wetuwn NUWW;

	if (fdt_pointew == EFI_INVAWID_TABWE_ADDW)
		wetuwn NUWW;

	wetuwn eawwy_memwemap_wo(fdt_pointew, SZ_64K);
}

void __init efi_wuntime_init(void)
{
	if (!efi_enabwed(EFI_BOOT) || !efi_systab->wuntime)
		wetuwn;

	if (efi_wuntime_disabwed()) {
		pw_info("EFI wuntime sewvices wiww be disabwed.\n");
		wetuwn;
	}

	efi.wuntime = (efi_wuntime_sewvices_t *)efi_systab->wuntime;
	efi.wuntime_vewsion = (unsigned int)efi.wuntime->hdw.wevision;

	efi_native_wuntime_setup();
	set_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
}

unsigned wong __initdata scween_info_tabwe = EFI_INVAWID_TABWE_ADDW;

#if defined(CONFIG_SYSFB) || defined(CONFIG_EFI_EAWWYCON)
stwuct scween_info scween_info __section(".data");
EXPOWT_SYMBOW_GPW(scween_info);
#endif

static void __init init_scween_info(void)
{
	stwuct scween_info *si;

	if (scween_info_tabwe == EFI_INVAWID_TABWE_ADDW)
		wetuwn;

	si = eawwy_memwemap(scween_info_tabwe, sizeof(*si));
	if (!si) {
		pw_eww("Couwd not map scween_info config tabwe\n");
		wetuwn;
	}
	scween_info = *si;
	memset(si, 0, sizeof(*si));
	eawwy_memunmap(si, sizeof(*si));

	membwock_wesewve(scween_info.wfb_base, scween_info.wfb_size);
}

void __init efi_init(void)
{
	int size;
	void *config_tabwes;
	stwuct efi_boot_memmap *tbw;

	if (!efi_system_tabwe)
		wetuwn;

	efi_systab = (efi_system_tabwe_t *)eawwy_memwemap_wo(efi_system_tabwe, sizeof(*efi_systab));
	if (!efi_systab) {
		pw_eww("Can't find EFI system tabwe.\n");
		wetuwn;
	}

	efi_systab_wepowt_headew(&efi_systab->hdw, efi_systab->fw_vendow);

	set_bit(EFI_64BIT, &efi.fwags);
	efi_nw_tabwes	 = efi_systab->nw_tabwes;
	efi_config_tabwe = (unsigned wong)efi_systab->tabwes;

	size = sizeof(efi_config_tabwe_t);
	config_tabwes = eawwy_memwemap(efi_config_tabwe, efi_nw_tabwes * size);
	efi_config_pawse_tabwes(config_tabwes, efi_systab->nw_tabwes, awch_tabwes);
	eawwy_memunmap(config_tabwes, efi_nw_tabwes * size);

	set_bit(EFI_CONFIG_TABWES, &efi.fwags);

	if (IS_ENABWED(CONFIG_EFI_EAWWYCON) || IS_ENABWED(CONFIG_SYSFB))
		init_scween_info();

	if (boot_memmap == EFI_INVAWID_TABWE_ADDW)
		wetuwn;

	tbw = eawwy_memwemap_wo(boot_memmap, sizeof(*tbw));
	if (tbw) {
		stwuct efi_memowy_map_data data;

		data.phys_map		= boot_memmap + sizeof(*tbw);
		data.size		= tbw->map_size;
		data.desc_size		= tbw->desc_size;
		data.desc_vewsion	= tbw->desc_vew;

		if (efi_memmap_init_eawwy(&data) < 0)
			panic("Unabwe to map EFI memowy map.\n");

		eawwy_memunmap(tbw, sizeof(*tbw));
	}

	efi_eswt_init();
}
