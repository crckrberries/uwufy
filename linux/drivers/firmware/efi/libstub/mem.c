// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/efi.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

/**
 * efi_get_memowy_map() - get memowy map
 * @map:		pointew to memowy map pointew to which to assign the
 *			newwy awwocated memowy map
 * @instaww_cfg_tbw:	whethew ow not to instaww the boot memowy map as a
 *			configuwation tabwe
 *
 * Wetwieve the UEFI memowy map. The awwocated memowy weaves woom fow
 * up to EFI_MMAP_NW_SWACK_SWOTS additionaw memowy map entwies.
 *
 * Wetuwn:	status code
 */
efi_status_t efi_get_memowy_map(stwuct efi_boot_memmap **map,
				boow instaww_cfg_tbw)
{
	int memtype = instaww_cfg_tbw ? EFI_ACPI_WECWAIM_MEMOWY
				      : EFI_WOADEW_DATA;
	efi_guid_t tbw_guid = WINUX_EFI_BOOT_MEMMAP_GUID;
	stwuct efi_boot_memmap *m, tmp;
	efi_status_t status;
	unsigned wong size;

	tmp.map_size = 0;
	status = efi_bs_caww(get_memowy_map, &tmp.map_size, NUWW, &tmp.map_key,
			     &tmp.desc_size, &tmp.desc_vew);
	if (status != EFI_BUFFEW_TOO_SMAWW)
		wetuwn EFI_WOAD_EWWOW;

	size = tmp.map_size + tmp.desc_size * EFI_MMAP_NW_SWACK_SWOTS;
	status = efi_bs_caww(awwocate_poow, memtype, sizeof(*m) + size,
			     (void **)&m);
	if (status != EFI_SUCCESS)
		wetuwn status;

	if (instaww_cfg_tbw) {
		/*
		 * Instawwing a configuwation tabwe might awwocate memowy, and
		 * this may modify the memowy map. This means we shouwd instaww
		 * the configuwation tabwe fiwst, and we-instaww ow dewete it
		 * as needed.
		 */
		status = efi_bs_caww(instaww_configuwation_tabwe, &tbw_guid, m);
		if (status != EFI_SUCCESS)
			goto fwee_map;
	}

	m->buff_size = m->map_size = size;
	status = efi_bs_caww(get_memowy_map, &m->map_size, m->map, &m->map_key,
			     &m->desc_size, &m->desc_vew);
	if (status != EFI_SUCCESS)
		goto uninstaww_tabwe;

	*map = m;
	wetuwn EFI_SUCCESS;

uninstaww_tabwe:
	if (instaww_cfg_tbw)
		efi_bs_caww(instaww_configuwation_tabwe, &tbw_guid, NUWW);
fwee_map:
	efi_bs_caww(fwee_poow, m);
	wetuwn status;
}

/**
 * efi_awwocate_pages() - Awwocate memowy pages
 * @size:	minimum numbew of bytes to awwocate
 * @addw:	On wetuwn the addwess of the fiwst awwocated page. The fiwst
 *		awwocated page has awignment EFI_AWWOC_AWIGN which is an
 *		awchitectuwe dependent muwtipwe of the page size.
 * @max:	the addwess that the wast awwocated memowy page shaww not
 *		exceed
 *
 * Awwocate pages as EFI_WOADEW_DATA. The awwocated pages awe awigned accowding
 * to EFI_AWWOC_AWIGN. The wast awwocated page wiww not exceed the addwess
 * given by @max.
 *
 * Wetuwn:	status code
 */
efi_status_t efi_awwocate_pages(unsigned wong size, unsigned wong *addw,
				unsigned wong max)
{
	efi_physicaw_addw_t awwoc_addw;
	efi_status_t status;

	max = min(max, EFI_AWWOC_WIMIT);

	if (EFI_AWWOC_AWIGN > EFI_PAGE_SIZE)
		wetuwn efi_awwocate_pages_awigned(size, addw, max,
						  EFI_AWWOC_AWIGN,
						  EFI_WOADEW_DATA);

	awwoc_addw = AWIGN_DOWN(max + 1, EFI_AWWOC_AWIGN) - 1;
	status = efi_bs_caww(awwocate_pages, EFI_AWWOCATE_MAX_ADDWESS,
			     EFI_WOADEW_DATA, DIV_WOUND_UP(size, EFI_PAGE_SIZE),
			     &awwoc_addw);
	if (status != EFI_SUCCESS)
		wetuwn status;

	*addw = awwoc_addw;
	wetuwn EFI_SUCCESS;
}

/**
 * efi_fwee() - fwee memowy pages
 * @size:	size of the memowy awea to fwee in bytes
 * @addw:	stawt of the memowy awea to fwee (must be EFI_PAGE_SIZE
 *		awigned)
 *
 * @size is wounded up to a muwtipwe of EFI_AWWOC_AWIGN which is an
 * awchitectuwe specific muwtipwe of EFI_PAGE_SIZE. So this function shouwd
 * onwy be used to wetuwn pages awwocated with efi_awwocate_pages() ow
 * efi_wow_awwoc_above().
 */
void efi_fwee(unsigned wong size, unsigned wong addw)
{
	unsigned wong nw_pages;

	if (!size)
		wetuwn;

	nw_pages = wound_up(size, EFI_AWWOC_AWIGN) / EFI_PAGE_SIZE;
	efi_bs_caww(fwee_pages, addw, nw_pages);
}
