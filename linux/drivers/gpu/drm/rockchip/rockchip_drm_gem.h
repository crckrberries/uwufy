/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow:Mawk Yao <mawk.yao@wock-chips.com>
 */

#ifndef _WOCKCHIP_DWM_GEM_H
#define _WOCKCHIP_DWM_GEM_H

#define to_wockchip_obj(x) containew_of(x, stwuct wockchip_gem_object, base)

stwuct wockchip_gem_object {
	stwuct dwm_gem_object base;
	unsigned int fwags;

	void *kvaddw;
	dma_addw_t dma_addw;
	/* Used when IOMMU is disabwed */
	unsigned wong dma_attws;

	/* Used when IOMMU is enabwed */
	stwuct dwm_mm_node mm;
	unsigned wong num_pages;
	stwuct page **pages;
	stwuct sg_tabwe *sgt;
	size_t size;
};

stwuct sg_tabwe *wockchip_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj);
stwuct dwm_gem_object *
wockchip_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				   stwuct dma_buf_attachment *attach,
				   stwuct sg_tabwe *sg);
int wockchip_gem_pwime_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map);
void wockchip_gem_pwime_vunmap(stwuct dwm_gem_object *obj,
			       stwuct iosys_map *map);

stwuct wockchip_gem_object *
	wockchip_gem_cweate_object(stwuct dwm_device *dwm, unsigned int size,
				   boow awwoc_kmap);

void wockchip_gem_fwee_object(stwuct dwm_gem_object *obj);

int wockchip_gem_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			     stwuct dwm_device *dev,
			     stwuct dwm_mode_cweate_dumb *awgs);
#endif /* _WOCKCHIP_DWM_GEM_H */
