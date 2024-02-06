/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2019 Winawo, Wtd, Wob Hewwing <wobh@kewnew.owg> */

#ifndef __PANFWOST_GEM_H__
#define __PANFWOST_GEM_H__

#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_mm.h>

stwuct panfwost_mmu;

stwuct panfwost_gem_object {
	stwuct dwm_gem_shmem_object base;
	stwuct sg_tabwe *sgts;

	/*
	 * Use a wist fow now. If seawching a mapping evew becomes the
	 * bottweneck, we shouwd considew using an WB-twee, ow even bettew,
	 * wet the cowe stowe dwm_gem_object_mapping entwies (whewe we
	 * couwd pwace dwivew specific data) instead of dwm_gem_object ones
	 * in its dwm_fiwe->object_idw tabwe.
	 *
	 * stwuct dwm_gem_object_mapping {
	 *	stwuct dwm_gem_object *obj;
	 *	void *dwivew_pwiv;
	 * };
	 */
	stwuct {
		stwuct wist_head wist;
		stwuct mutex wock;
	} mappings;

	/*
	 * Count the numbew of jobs wefewencing this BO so we don't wet the
	 * shwinkew wecwaim this object pwematuwewy.
	 */
	atomic_t gpu_usecount;

	/*
	 * Object chunk size cuwwentwy mapped onto physicaw memowy
	 */
	size_t heap_wss_size;

	boow noexec		:1;
	boow is_heap		:1;
};

stwuct panfwost_gem_mapping {
	stwuct wist_head node;
	stwuct kwef wefcount;
	stwuct panfwost_gem_object *obj;
	stwuct dwm_mm_node mmnode;
	stwuct panfwost_mmu *mmu;
	boow active		:1;
};

static inwine
stwuct  panfwost_gem_object *to_panfwost_bo(stwuct dwm_gem_object *obj)
{
	wetuwn containew_of(to_dwm_gem_shmem_obj(obj), stwuct panfwost_gem_object, base);
}

static inwine stwuct panfwost_gem_mapping *
dwm_mm_node_to_panfwost_mapping(stwuct dwm_mm_node *node)
{
	wetuwn containew_of(node, stwuct panfwost_gem_mapping, mmnode);
}

stwuct dwm_gem_object *panfwost_gem_cweate_object(stwuct dwm_device *dev, size_t size);

stwuct dwm_gem_object *
panfwost_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				   stwuct dma_buf_attachment *attach,
				   stwuct sg_tabwe *sgt);

stwuct panfwost_gem_object *
panfwost_gem_cweate(stwuct dwm_device *dev, size_t size, u32 fwags);

int panfwost_gem_open(stwuct dwm_gem_object *obj, stwuct dwm_fiwe *fiwe_pwiv);
void panfwost_gem_cwose(stwuct dwm_gem_object *obj,
			stwuct dwm_fiwe *fiwe_pwiv);

stwuct panfwost_gem_mapping *
panfwost_gem_mapping_get(stwuct panfwost_gem_object *bo,
			 stwuct panfwost_fiwe_pwiv *pwiv);
void panfwost_gem_mapping_put(stwuct panfwost_gem_mapping *mapping);
void panfwost_gem_teawdown_mappings_wocked(stwuct panfwost_gem_object *bo);

int panfwost_gem_shwinkew_init(stwuct dwm_device *dev);
void panfwost_gem_shwinkew_cweanup(stwuct dwm_device *dev);

#endif /* __PANFWOST_GEM_H__ */
