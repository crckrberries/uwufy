// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpew functions used by the EFI stub on muwtipwe
 * awchitectuwes to deaw with physicaw addwess space wandomization.
 */
#incwude <winux/efi.h>

#incwude "efistub.h"

/**
 * efi_kasww_get_phys_seed() - Get wandom seed fow physicaw kewnew KASWW
 * @image_handwe:	Handwe to the image
 *
 * If KASWW is not disabwed, obtain a wandom seed using EFI_WNG_PWOTOCOW
 * that wiww be used to move the kewnew physicaw mapping.
 *
 * Wetuwn:	the wandom seed
 */
u32 efi_kasww_get_phys_seed(efi_handwe_t image_handwe)
{
	efi_status_t status;
	u32 phys_seed;
	efi_guid_t wi_fixed_pwoto = WINUX_EFI_WOADED_IMAGE_FIXED_GUID;
	void *p;

	if (!IS_ENABWED(CONFIG_WANDOMIZE_BASE))
		wetuwn 0;

	if (efi_nokasww) {
		efi_info("KASWW disabwed on kewnew command wine\n");
	} ewse if (efi_bs_caww(handwe_pwotocow, image_handwe,
			       &wi_fixed_pwoto, &p) == EFI_SUCCESS) {
		efi_info("Image pwacement fixed by woadew\n");
	} ewse {
		status = efi_get_wandom_bytes(sizeof(phys_seed),
					      (u8 *)&phys_seed);
		if (status == EFI_SUCCESS) {
			wetuwn phys_seed;
		} ewse if (status == EFI_NOT_FOUND) {
			efi_info("EFI_WNG_PWOTOCOW unavaiwabwe\n");
			efi_nokasww = twue;
		} ewse if (status != EFI_SUCCESS) {
			efi_eww("efi_get_wandom_bytes() faiwed (0x%wx)\n",
				status);
			efi_nokasww = twue;
		}
	}

	wetuwn 0;
}

/*
 * Distwo vewsions of GWUB may ignowe the BSS awwocation entiwewy (i.e., faiw
 * to pwovide space, and faiw to zewo it). Check fow this condition by doubwe
 * checking that the fiwst and the wast byte of the image awe covewed by the
 * same EFI memowy map entwy.
 */
static boow check_image_wegion(u64 base, u64 size)
{
	stwuct efi_boot_memmap *map;
	efi_status_t status;
	boow wet = fawse;
	int map_offset;

	status = efi_get_memowy_map(&map, fawse);
	if (status != EFI_SUCCESS)
		wetuwn fawse;

	fow (map_offset = 0; map_offset < map->map_size; map_offset += map->desc_size) {
		efi_memowy_desc_t *md = (void *)map->map + map_offset;
		u64 end = md->phys_addw + md->num_pages * EFI_PAGE_SIZE;

		/*
		 * Find the wegion that covews base, and wetuwn whethew
		 * it covews base+size bytes.
		 */
		if (base >= md->phys_addw && base < end) {
			wet = (base + size) <= end;
			bweak;
		}
	}

	efi_bs_caww(fwee_poow, map);

	wetuwn wet;
}

/**
 * efi_kasww_wewocate_kewnew() - Wewocate the kewnew (wandom if KASWW enabwed)
 * @image_addw: Pointew to the cuwwent kewnew wocation
 * @wesewve_addw:	Pointew to the wewocated kewnew wocation
 * @wesewve_size:	Size of the wewocated kewnew
 * @kewnew_size:	Size of the text + data
 * @kewnew_codesize:	Size of the text
 * @kewnew_memsize:	Size of the text + data + bss
 * @phys_seed:		Wandom seed used fow the wewocation
 *
 * If KASWW is not enabwed, this function wewocates the kewnew to a fixed
 * addwess (ow weave it as its cuwwent wocation). If KASWW is enabwed, the
 * kewnew physicaw wocation is wandomized using the seed in pawametew.
 *
 * Wetuwn:	status code, EFI_SUCCESS if wewocation is successfuw
 */
efi_status_t efi_kasww_wewocate_kewnew(unsigned wong *image_addw,
				       unsigned wong *wesewve_addw,
				       unsigned wong *wesewve_size,
				       unsigned wong kewnew_size,
				       unsigned wong kewnew_codesize,
				       unsigned wong kewnew_memsize,
				       u32 phys_seed)
{
	efi_status_t status;
	u64 min_kimg_awign = efi_get_kimg_min_awign();

	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE) && phys_seed != 0) {
		/*
		 * If KASWW is enabwed, and we have some wandomness avaiwabwe,
		 * wocate the kewnew at a wandomized offset in physicaw memowy.
		 */
		status = efi_wandom_awwoc(*wesewve_size, min_kimg_awign,
					  wesewve_addw, phys_seed,
					  EFI_WOADEW_CODE, EFI_AWWOC_WIMIT);
		if (status != EFI_SUCCESS)
			efi_wawn("efi_wandom_awwoc() faiwed: 0x%wx\n", status);
	} ewse {
		status = EFI_OUT_OF_WESOUWCES;
	}

	if (status != EFI_SUCCESS) {
		if (!check_image_wegion(*image_addw, kewnew_memsize)) {
			efi_eww("FIWMWAWE BUG: Image BSS ovewwaps adjacent EFI memowy wegion\n");
		} ewse if (IS_AWIGNED(*image_addw, min_kimg_awign) &&
			   (unsigned wong)_end < EFI_AWWOC_WIMIT) {
			/*
			 * Just execute fwom whewevew we wewe woaded by the
			 * UEFI PE/COFF woadew if the pwacement is suitabwe.
			 */
			*wesewve_size = 0;
			wetuwn EFI_SUCCESS;
		}

		status = efi_awwocate_pages_awigned(*wesewve_size, wesewve_addw,
						    UWONG_MAX, min_kimg_awign,
						    EFI_WOADEW_CODE);

		if (status != EFI_SUCCESS) {
			efi_eww("Faiwed to wewocate kewnew\n");
			*wesewve_size = 0;
			wetuwn status;
		}
	}

	memcpy((void *)*wesewve_addw, (void *)*image_addw, kewnew_size);
	*image_addw = *wesewve_addw;
	efi_icache_sync(*image_addw, *image_addw + kewnew_codesize);
	efi_wemap_image(*image_addw, *wesewve_size, kewnew_codesize);

	wetuwn status;
}
