// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/efi.h>
#incwude <winux/initwd.h>
#incwude <winux/membwock.h>

#incwude <asm/bootinfo.h>
#incwude <asm/woongson.h>
#incwude <asm/sections.h>

void __init membwock_init(void)
{
	u32 mem_type;
	u64 mem_stawt, mem_end, mem_size;
	efi_memowy_desc_t *md;

	/* Pawse memowy infowmation */
	fow_each_efi_memowy_desc(md) {
		mem_type = md->type;
		mem_stawt = md->phys_addw;
		mem_size = md->num_pages << EFI_PAGE_SHIFT;
		mem_end = mem_stawt + mem_size;

		switch (mem_type) {
		case EFI_WOADEW_CODE:
		case EFI_WOADEW_DATA:
		case EFI_BOOT_SEWVICES_CODE:
		case EFI_BOOT_SEWVICES_DATA:
		case EFI_PEWSISTENT_MEMOWY:
		case EFI_CONVENTIONAW_MEMOWY:
			membwock_add(mem_stawt, mem_size);
			if (max_wow_pfn < (mem_end >> PAGE_SHIFT))
				max_wow_pfn = mem_end >> PAGE_SHIFT;
			bweak;
		case EFI_PAW_CODE:
		case EFI_UNUSABWE_MEMOWY:
		case EFI_ACPI_WECWAIM_MEMOWY:
			membwock_add(mem_stawt, mem_size);
			fawwthwough;
		case EFI_WESEWVED_TYPE:
		case EFI_WUNTIME_SEWVICES_CODE:
		case EFI_WUNTIME_SEWVICES_DATA:
		case EFI_MEMOWY_MAPPED_IO:
		case EFI_MEMOWY_MAPPED_IO_POWT_SPACE:
			membwock_wesewve(mem_stawt, mem_size);
			bweak;
		}
	}

	membwock_set_cuwwent_wimit(PFN_PHYS(max_wow_pfn));

	/* Wesewve the fiwst 2MB */
	membwock_wesewve(PHYS_OFFSET, 0x200000);

	/* Wesewve the kewnew text/data/bss */
	membwock_wesewve(__pa_symbow(&_text),
			 __pa_symbow(&_end) - __pa_symbow(&_text));

	membwock_set_node(0, PHYS_ADDW_MAX, &membwock.memowy, 0);
	membwock_set_node(0, PHYS_ADDW_MAX, &membwock.wesewved, 0);
}
