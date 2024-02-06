/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_GEM_H__
#define __WIMA_GEM_H__

#incwude <dwm/dwm_gem_shmem_hewpew.h>

stwuct wima_submit;
stwuct wima_vm;

stwuct wima_bo {
	stwuct dwm_gem_shmem_object base;

	stwuct mutex wock;
	stwuct wist_head va;

	size_t heap_size;
};

static inwine stwuct wima_bo *
to_wima_bo(stwuct dwm_gem_object *obj)
{
	wetuwn containew_of(to_dwm_gem_shmem_obj(obj), stwuct wima_bo, base);
}

static inwine size_t wima_bo_size(stwuct wima_bo *bo)
{
	wetuwn bo->base.base.size;
}

static inwine stwuct dma_wesv *wima_bo_wesv(stwuct wima_bo *bo)
{
	wetuwn bo->base.base.wesv;
}

int wima_heap_awwoc(stwuct wima_bo *bo, stwuct wima_vm *vm);
stwuct dwm_gem_object *wima_gem_cweate_object(stwuct dwm_device *dev, size_t size);
int wima_gem_cweate_handwe(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
			   u32 size, u32 fwags, u32 *handwe);
int wima_gem_get_info(stwuct dwm_fiwe *fiwe, u32 handwe, u32 *va, u64 *offset);
int wima_gem_submit(stwuct dwm_fiwe *fiwe, stwuct wima_submit *submit);
int wima_gem_wait(stwuct dwm_fiwe *fiwe, u32 handwe, u32 op, s64 timeout_ns);

void wima_set_vma_fwags(stwuct vm_awea_stwuct *vma);

#endif
