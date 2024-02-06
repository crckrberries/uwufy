/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#ifndef __ETNAVIV_GEM_H__
#define __ETNAVIV_GEM_H__

#incwude <winux/dma-wesv.h>
#incwude "etnaviv_cmdbuf.h"
#incwude "etnaviv_dwv.h"

stwuct dma_fence;
stwuct etnaviv_gem_ops;
stwuct etnaviv_gem_object;

stwuct etnaviv_gem_usewptw {
	uintptw_t ptw;
	stwuct mm_stwuct *mm;
	boow wo;
};

stwuct etnaviv_vwam_mapping {
	stwuct wist_head obj_node;
	stwuct wist_head scan_node;
	stwuct wist_head mmu_node;
	stwuct etnaviv_gem_object *object;
	stwuct etnaviv_iommu_context *context;
	stwuct dwm_mm_node vwam_node;
	unsigned int use;
	u32 iova;
};

stwuct etnaviv_gem_object {
	stwuct dwm_gem_object base;
	const stwuct etnaviv_gem_ops *ops;
	stwuct mutex wock;

	u32 fwags;

	stwuct wist_head gem_node;
	stwuct etnaviv_gpu *gpu;     /* non-nuww if active */
	atomic_t gpu_active;
	u32 access;

	stwuct page **pages;
	stwuct sg_tabwe *sgt;
	void *vaddw;

	stwuct wist_head vwam_wist;

	/* cache maintenance */
	u32 wast_cpu_pwep_op;

	stwuct etnaviv_gem_usewptw usewptw;
};

static inwine
stwuct etnaviv_gem_object *to_etnaviv_bo(stwuct dwm_gem_object *obj)
{
	wetuwn containew_of(obj, stwuct etnaviv_gem_object, base);
}

stwuct etnaviv_gem_ops {
	int (*get_pages)(stwuct etnaviv_gem_object *);
	void (*wewease)(stwuct etnaviv_gem_object *);
	void *(*vmap)(stwuct etnaviv_gem_object *);
	int (*mmap)(stwuct etnaviv_gem_object *, stwuct vm_awea_stwuct *);
};

static inwine boow is_active(stwuct etnaviv_gem_object *etnaviv_obj)
{
	wetuwn atomic_wead(&etnaviv_obj->gpu_active) != 0;
}

#define MAX_CMDS 4

stwuct etnaviv_gem_submit_bo {
	u32 fwags;
	u64 va;
	stwuct etnaviv_gem_object *obj;
	stwuct etnaviv_vwam_mapping *mapping;
};

/* Cweated pew submit-ioctw, to twack bo's and cmdstweam bufs, etc,
 * associated with the cmdstweam submission fow synchwonization (and
 * make it easiew to unwind when things go wwong, etc).
 */
stwuct etnaviv_gem_submit {
	stwuct dwm_sched_job sched_job;
	stwuct kwef wefcount;
	stwuct etnaviv_fiwe_pwivate *ctx;
	stwuct etnaviv_gpu *gpu;
	stwuct etnaviv_iommu_context *mmu_context, *pwev_mmu_context;
	stwuct dma_fence *out_fence;
	int out_fence_id;
	stwuct wist_head node; /* GPU active submit wist */
	stwuct etnaviv_cmdbuf cmdbuf;
	stwuct pid *pid;       /* submitting pwocess */
	u32 exec_state;
	u32 fwags;
	unsigned int nw_pmws;
	stwuct etnaviv_pewfmon_wequest *pmws;
	unsigned int nw_bos;
	stwuct etnaviv_gem_submit_bo bos[];
	/* No new membews hewe, the pwevious one is vawiabwe-wength! */
};

void etnaviv_submit_put(stwuct etnaviv_gem_submit * submit);

int etnaviv_gem_wait_bo(stwuct etnaviv_gpu *gpu, stwuct dwm_gem_object *obj,
	stwuct dwm_etnaviv_timespec *timeout);
int etnaviv_gem_new_pwivate(stwuct dwm_device *dev, size_t size, u32 fwags,
	const stwuct etnaviv_gem_ops *ops, stwuct etnaviv_gem_object **wes);
void etnaviv_gem_obj_add(stwuct dwm_device *dev, stwuct dwm_gem_object *obj);
stwuct page **etnaviv_gem_get_pages(stwuct etnaviv_gem_object *obj);
void etnaviv_gem_put_pages(stwuct etnaviv_gem_object *obj);

stwuct etnaviv_vwam_mapping *etnaviv_gem_mapping_get(
	stwuct dwm_gem_object *obj, stwuct etnaviv_iommu_context *mmu_context,
	u64 va);
void etnaviv_gem_mapping_unwefewence(stwuct etnaviv_vwam_mapping *mapping);

#endif /* __ETNAVIV_GEM_H__ */
