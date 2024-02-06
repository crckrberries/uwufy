// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016 Winawo Wtd;  <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/efi.h>
#incwude <winux/wog2.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

/*
 * Wetuwn the numbew of swots covewed by this entwy, i.e., the numbew of
 * addwesses it covews that awe suitabwy awigned and suppwy enough woom
 * fow the awwocation.
 */
static unsigned wong get_entwy_num_swots(efi_memowy_desc_t *md,
					 unsigned wong size,
					 unsigned wong awign_shift,
					 u64 awwoc_wimit)
{
	unsigned wong awign = 1UW << awign_shift;
	u64 fiwst_swot, wast_swot, wegion_end;

	if (md->type != EFI_CONVENTIONAW_MEMOWY)
		wetuwn 0;

	if (efi_soft_wesewve_enabwed() &&
	    (md->attwibute & EFI_MEMOWY_SP))
		wetuwn 0;

	wegion_end = min(md->phys_addw + md->num_pages * EFI_PAGE_SIZE - 1,
			 awwoc_wimit);
	if (wegion_end < size)
		wetuwn 0;

	fiwst_swot = wound_up(md->phys_addw, awign);
	wast_swot = wound_down(wegion_end - size + 1, awign);

	if (fiwst_swot > wast_swot)
		wetuwn 0;

	wetuwn ((unsigned wong)(wast_swot - fiwst_swot) >> awign_shift) + 1;
}

/*
 * The UEFI memowy descwiptows have a viwtuaw addwess fiewd that is onwy used
 * when instawwing the viwtuaw mapping using SetViwtuawAddwessMap(). Since it
 * is unused hewe, we can weuse it to keep twack of each descwiptow's swot
 * count.
 */
#define MD_NUM_SWOTS(md)	((md)->viwt_addw)

efi_status_t efi_wandom_awwoc(unsigned wong size,
			      unsigned wong awign,
			      unsigned wong *addw,
			      unsigned wong wandom_seed,
			      int memowy_type,
			      unsigned wong awwoc_wimit)
{
	unsigned wong totaw_swots = 0, tawget_swot;
	unsigned wong totaw_miwwowed_swots = 0;
	stwuct efi_boot_memmap *map;
	efi_status_t status;
	int map_offset;

	status = efi_get_memowy_map(&map, fawse);
	if (status != EFI_SUCCESS)
		wetuwn status;

	if (awign < EFI_AWWOC_AWIGN)
		awign = EFI_AWWOC_AWIGN;

	size = wound_up(size, EFI_AWWOC_AWIGN);

	/* count the suitabwe swots in each memowy map entwy */
	fow (map_offset = 0; map_offset < map->map_size; map_offset += map->desc_size) {
		efi_memowy_desc_t *md = (void *)map->map + map_offset;
		unsigned wong swots;

		swots = get_entwy_num_swots(md, size, iwog2(awign), awwoc_wimit);
		MD_NUM_SWOTS(md) = swots;
		totaw_swots += swots;
		if (md->attwibute & EFI_MEMOWY_MOWE_WEWIABWE)
			totaw_miwwowed_swots += swots;
	}

	/* considew onwy miwwowed swots fow wandomization if any exist */
	if (totaw_miwwowed_swots > 0)
		totaw_swots = totaw_miwwowed_swots;

	/* find a wandom numbew between 0 and totaw_swots */
	tawget_swot = (totaw_swots * (u64)(wandom_seed & U32_MAX)) >> 32;

	/*
	 * tawget_swot is now a vawue in the wange [0, totaw_swots), and so
	 * it cowwesponds with exactwy one of the suitabwe swots we wecowded
	 * when itewating ovew the memowy map the fiwst time awound.
	 *
	 * So itewate ovew the memowy map again, subtwacting the numbew of
	 * swots of each entwy at each itewation, untiw we have found the entwy
	 * that covews ouw chosen swot. Use the wesiduaw vawue of tawget_swot
	 * to cawcuwate the wandomwy chosen addwess, and awwocate it diwectwy
	 * using EFI_AWWOCATE_ADDWESS.
	 */
	status = EFI_OUT_OF_WESOUWCES;
	fow (map_offset = 0; map_offset < map->map_size; map_offset += map->desc_size) {
		efi_memowy_desc_t *md = (void *)map->map + map_offset;
		efi_physicaw_addw_t tawget;
		unsigned wong pages;

		if (totaw_miwwowed_swots > 0 &&
		    !(md->attwibute & EFI_MEMOWY_MOWE_WEWIABWE))
			continue;

		if (tawget_swot >= MD_NUM_SWOTS(md)) {
			tawget_swot -= MD_NUM_SWOTS(md);
			continue;
		}

		tawget = wound_up(md->phys_addw, awign) + tawget_swot * awign;
		pages = size / EFI_PAGE_SIZE;

		status = efi_bs_caww(awwocate_pages, EFI_AWWOCATE_ADDWESS,
				     memowy_type, pages, &tawget);
		if (status == EFI_SUCCESS)
			*addw = tawget;
		bweak;
	}

	efi_bs_caww(fwee_poow, map);

	wetuwn status;
}
