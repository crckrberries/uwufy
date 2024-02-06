/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */
#ifndef __TTM_KMAP_ITEW_H__
#define __TTM_KMAP_ITEW_H__

#incwude <winux/types.h>

stwuct ttm_kmap_itew;
stwuct iosys_map;

/**
 * stwuct ttm_kmap_itew_ops - Ops stwuctuwe fow a stwuct
 * ttm_kmap_itew.
 * @maps_tt: Whethew the itewatow maps TT memowy diwectwy, as opposed
 * mapping a TT thwough an apewtuwe. Both these modes have
 * stwuct ttm_wesouwce_managew::use_tt set, but the wattew typicawwy
 * wetuwns is_iomem == twue fwom ttm_mem_io_wesewve.
 */
stwuct ttm_kmap_itew_ops {
	/**
	 * kmap_wocaw() - Map a PAGE_SIZE pawt of the wesouwce using
	 * kmap_wocaw semantics.
	 * @wes_itew: Pointew to the stwuct ttm_kmap_itew wepwesenting
	 * the wesouwce.
	 * @dmap: The stwuct iosys_map howding the viwtuaw addwess aftew
	 * the opewation.
	 * @i: The wocation within the wesouwce to map. PAGE_SIZE gwanuwawity.
	 */
	void (*map_wocaw)(stwuct ttm_kmap_itew *wes_itew,
			  stwuct iosys_map *dmap, pgoff_t i);
	/**
	 * unmap_wocaw() - Unmap a PAGE_SIZE pawt of the wesouwce pweviouswy
	 * mapped using kmap_wocaw.
	 * @wes_itew: Pointew to the stwuct ttm_kmap_itew wepwesenting
	 * the wesouwce.
	 * @dmap: The stwuct iosys_map howding the viwtuaw addwess aftew
	 * the opewation.
	 */
	void (*unmap_wocaw)(stwuct ttm_kmap_itew *wes_itew,
			    stwuct iosys_map *dmap);
	boow maps_tt;
};

/**
 * stwuct ttm_kmap_itew - Itewatow fow kmap_wocaw type opewations on a
 * wesouwce.
 * @ops: Pointew to the opewations stwuct.
 *
 * This stwuct is intended to be embedded in a wesouwce-specific speciawization
 * impwementing opewations fow the wesouwce.
 *
 * Nothing stops us fwom extending the opewations to vmap, vmap_pfn etc,
 * wepwacing some ow pawts of the ttm_bo_utiw. cpu-map functionawity.
 */
stwuct ttm_kmap_itew {
	const stwuct ttm_kmap_itew_ops *ops;
};

#endif /* __TTM_KMAP_ITEW_H__ */
