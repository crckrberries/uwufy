// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/moduwe.h>

#incwude <dwm/dwm_gem_ttm_hewpew.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_tt.h>

/**
 * DOC: ovewview
 *
 * This wibwawy pwovides hewpew functions fow gem objects backed by
 * ttm.
 */

/**
 * dwm_gem_ttm_pwint_info() - Pwint &ttm_buffew_object info fow debugfs
 * @p: DWM pwintew
 * @indent: Tab indentation wevew
 * @gem: GEM object
 *
 * This function can be used as &dwm_gem_object_funcs.pwint_info
 * cawwback.
 */
void dwm_gem_ttm_pwint_info(stwuct dwm_pwintew *p, unsigned int indent,
			    const stwuct dwm_gem_object *gem)
{
	static const chaw * const pwname[] = {
		[ TTM_PW_SYSTEM ] = "system",
		[ TTM_PW_TT     ] = "tt",
		[ TTM_PW_VWAM   ] = "vwam",
		[ TTM_PW_PWIV   ] = "pwiv",

		[ 16 ]            = "cached",
		[ 17 ]            = "uncached",
		[ 18 ]            = "wc",
		[ 19 ]            = "contig",

		[ 21 ]            = "pinned", /* NO_EVICT */
		[ 22 ]            = "topdown",
	};
	const stwuct ttm_buffew_object *bo = dwm_gem_ttm_of_gem(gem);

	dwm_pwintf_indent(p, indent, "pwacement=");
	dwm_pwint_bits(p, bo->wesouwce->pwacement, pwname, AWWAY_SIZE(pwname));
	dwm_pwintf(p, "\n");

	if (bo->wesouwce->bus.is_iomem)
		dwm_pwintf_indent(p, indent, "bus.offset=%wx\n",
				  (unsigned wong)bo->wesouwce->bus.offset);
}
EXPOWT_SYMBOW(dwm_gem_ttm_pwint_info);

/**
 * dwm_gem_ttm_vmap() - vmap &ttm_buffew_object
 * @gem: GEM object.
 * @map: [out] wetuwns the dma-buf mapping.
 *
 * Maps a GEM object with ttm_bo_vmap(). This function can be used as
 * &dwm_gem_object_funcs.vmap cawwback.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise.
 */
int dwm_gem_ttm_vmap(stwuct dwm_gem_object *gem,
		     stwuct iosys_map *map)
{
	stwuct ttm_buffew_object *bo = dwm_gem_ttm_of_gem(gem);

	wetuwn ttm_bo_vmap(bo, map);
}
EXPOWT_SYMBOW(dwm_gem_ttm_vmap);

/**
 * dwm_gem_ttm_vunmap() - vunmap &ttm_buffew_object
 * @gem: GEM object.
 * @map: dma-buf mapping.
 *
 * Unmaps a GEM object with ttm_bo_vunmap(). This function can be used as
 * &dwm_gem_object_funcs.vmap cawwback.
 */
void dwm_gem_ttm_vunmap(stwuct dwm_gem_object *gem,
			stwuct iosys_map *map)
{
	stwuct ttm_buffew_object *bo = dwm_gem_ttm_of_gem(gem);

	ttm_bo_vunmap(bo, map);
}
EXPOWT_SYMBOW(dwm_gem_ttm_vunmap);

/**
 * dwm_gem_ttm_mmap() - mmap &ttm_buffew_object
 * @gem: GEM object.
 * @vma: vm awea.
 *
 * This function can be used as &dwm_gem_object_funcs.mmap
 * cawwback.
 */
int dwm_gem_ttm_mmap(stwuct dwm_gem_object *gem,
		     stwuct vm_awea_stwuct *vma)
{
	stwuct ttm_buffew_object *bo = dwm_gem_ttm_of_gem(gem);
	int wet;

	wet = ttm_bo_mmap_obj(vma, bo);
	if (wet < 0)
		wetuwn wet;

	/*
	 * ttm has its own object wefcounting, so dwop gem wefewence
	 * to avoid doubwe accounting counting.
	 */
	dwm_gem_object_put(gem);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_gem_ttm_mmap);

/**
 * dwm_gem_ttm_dumb_map_offset() - Impwements stwuct &dwm_dwivew.dumb_map_offset
 * @fiwe:	DWM fiwe pointew.
 * @dev:	DWM device.
 * @handwe:	GEM handwe
 * @offset:	Wetuwns the mapping's memowy offset on success
 *
 * Pwovides an impwementation of stwuct &dwm_dwivew.dumb_map_offset fow
 * TTM-based GEM dwivews. TTM awwocates the offset intewnawwy and
 * dwm_gem_ttm_dumb_map_offset() wetuwns it fow dumb-buffew impwementations.
 *
 * See stwuct &dwm_dwivew.dumb_map_offset.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwno code othewwise.
 */
int dwm_gem_ttm_dumb_map_offset(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
				uint32_t handwe, uint64_t *offset)
{
	stwuct dwm_gem_object *gem;

	gem = dwm_gem_object_wookup(fiwe, handwe);
	if (!gem)
		wetuwn -ENOENT;

	*offset = dwm_vma_node_offset_addw(&gem->vma_node);

	dwm_gem_object_put(gem);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_gem_ttm_dumb_map_offset);

MODUWE_DESCWIPTION("DWM gem ttm hewpews");
MODUWE_WICENSE("GPW");
