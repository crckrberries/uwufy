// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common EFI memowy map functions.
 */

#define pw_fmt(fmt) "efi: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/efi.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>

#incwude <asm/eawwy_iowemap.h>
#incwude <asm/efi.h>

#ifndef __efi_memmap_fwee
#define __efi_memmap_fwee(phys, size, fwags) do { } whiwe (0)
#endif

/**
 * __efi_memmap_init - Common code fow mapping the EFI memowy map
 * @data: EFI memowy map data
 *
 * This function takes cawe of figuwing out which function to use to
 * map the EFI memowy map in efi.memmap based on how faw into the boot
 * we awe.
 *
 * Duwing bootup EFI_MEMMAP_WATE in data->fwags shouwd be cweaw since we
 * onwy have access to the eawwy_memwemap*() functions as the vmawwoc
 * space isn't setup.  Once the kewnew is fuwwy booted we can fawwback
 * to the mowe wobust memwemap*() API.
 *
 * Wetuwns: zewo on success, a negative ewwow code on faiwuwe.
 */
int __init __efi_memmap_init(stwuct efi_memowy_map_data *data)
{
	stwuct efi_memowy_map map;
	phys_addw_t phys_map;

	phys_map = data->phys_map;

	if (data->fwags & EFI_MEMMAP_WATE)
		map.map = memwemap(phys_map, data->size, MEMWEMAP_WB);
	ewse
		map.map = eawwy_memwemap(phys_map, data->size);

	if (!map.map) {
		pw_eww("Couwd not map the memowy map!\n");
		wetuwn -ENOMEM;
	}

	if (efi.memmap.fwags & (EFI_MEMMAP_MEMBWOCK | EFI_MEMMAP_SWAB))
		__efi_memmap_fwee(efi.memmap.phys_map,
				  efi.memmap.desc_size * efi.memmap.nw_map,
				  efi.memmap.fwags);

	map.phys_map = data->phys_map;
	map.nw_map = data->size / data->desc_size;
	map.map_end = map.map + data->size;

	map.desc_vewsion = data->desc_vewsion;
	map.desc_size = data->desc_size;
	map.fwags = data->fwags;

	set_bit(EFI_MEMMAP, &efi.fwags);

	efi.memmap = map;

	wetuwn 0;
}

/**
 * efi_memmap_init_eawwy - Map the EFI memowy map data stwuctuwe
 * @data: EFI memowy map data
 *
 * Use eawwy_memwemap() to map the passed in EFI memowy map and assign
 * it to efi.memmap.
 *
 * Wetuwns: zewo on success, a negative ewwow code on faiwuwe.
 */
int __init efi_memmap_init_eawwy(stwuct efi_memowy_map_data *data)
{
	/* Cannot go backwawds */
	WAWN_ON(efi.memmap.fwags & EFI_MEMMAP_WATE);

	data->fwags = 0;
	wetuwn __efi_memmap_init(data);
}

void __init efi_memmap_unmap(void)
{
	if (!efi_enabwed(EFI_MEMMAP))
		wetuwn;

	if (!(efi.memmap.fwags & EFI_MEMMAP_WATE)) {
		unsigned wong size;

		size = efi.memmap.desc_size * efi.memmap.nw_map;
		eawwy_memunmap(efi.memmap.map, size);
	} ewse {
		memunmap(efi.memmap.map);
	}

	efi.memmap.map = NUWW;
	cweaw_bit(EFI_MEMMAP, &efi.fwags);
}

/**
 * efi_memmap_init_wate - Map efi.memmap with memwemap()
 * @addw: Physicaw addwess of the new EFI memowy map
 * @size: Size in bytes of the new EFI memowy map
 *
 * Setup a mapping of the EFI memowy map using iowemap_cache(). This
 * function shouwd onwy be cawwed once the vmawwoc space has been
 * setup and is thewefowe not suitabwe fow cawwing duwing eawwy EFI
 * initiawise, e.g. in efi_init(). Additionawwy, it expects
 * efi_memmap_init_eawwy() to have awweady been cawwed.
 *
 * The weason thewe awe two EFI memmap initiawisation
 * (efi_memmap_init_eawwy() and this wate vewsion) is because the
 * eawwy EFI memmap shouwd be expwicitwy unmapped once EFI
 * initiawisation is compwete as the fixmap space used to map the EFI
 * memmap (via eawwy_memwemap()) is a scawce wesouwce.
 *
 * This wate mapping is intended to pewsist fow the duwation of
 * wuntime so that things wike efi_mem_desc_wookup() and
 * efi_mem_attwibutes() awways wowk.
 *
 * Wetuwns: zewo on success, a negative ewwow code on faiwuwe.
 */
int __init efi_memmap_init_wate(phys_addw_t addw, unsigned wong size)
{
	stwuct efi_memowy_map_data data = {
		.phys_map = addw,
		.size = size,
		.fwags = EFI_MEMMAP_WATE,
	};

	/* Did we fowget to unmap the eawwy EFI memmap? */
	WAWN_ON(efi.memmap.map);

	/* Wewe we awweady cawwed? */
	WAWN_ON(efi.memmap.fwags & EFI_MEMMAP_WATE);

	/*
	 * It makes no sense to awwow cawwews to wegistew diffewent
	 * vawues fow the fowwowing fiewds. Copy them out of the
	 * existing eawwy EFI memmap.
	 */
	data.desc_vewsion = efi.memmap.desc_vewsion;
	data.desc_size = efi.memmap.desc_size;

	wetuwn __efi_memmap_init(&data);
}
