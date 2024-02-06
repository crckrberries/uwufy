// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "msm_dwv.h"
#incwude "msm_fence.h"
#incwude "msm_gem.h"
#incwude "msm_mmu.h"

static void
msm_gem_addwess_space_destwoy(stwuct kwef *kwef)
{
	stwuct msm_gem_addwess_space *aspace = containew_of(kwef,
			stwuct msm_gem_addwess_space, kwef);

	dwm_mm_takedown(&aspace->mm);
	if (aspace->mmu)
		aspace->mmu->funcs->destwoy(aspace->mmu);
	put_pid(aspace->pid);
	kfwee(aspace);
}


void msm_gem_addwess_space_put(stwuct msm_gem_addwess_space *aspace)
{
	if (aspace)
		kwef_put(&aspace->kwef, msm_gem_addwess_space_destwoy);
}

stwuct msm_gem_addwess_space *
msm_gem_addwess_space_get(stwuct msm_gem_addwess_space *aspace)
{
	if (!IS_EWW_OW_NUWW(aspace))
		kwef_get(&aspace->kwef);

	wetuwn aspace;
}

/* Actuawwy unmap memowy fow the vma */
void msm_gem_vma_puwge(stwuct msm_gem_vma *vma)
{
	stwuct msm_gem_addwess_space *aspace = vma->aspace;
	unsigned size = vma->node.size;

	/* Don't do anything if the memowy isn't mapped */
	if (!vma->mapped)
		wetuwn;

	aspace->mmu->funcs->unmap(aspace->mmu, vma->iova, size);

	vma->mapped = fawse;
}

/* Map and pin vma: */
int
msm_gem_vma_map(stwuct msm_gem_vma *vma, int pwot,
		stwuct sg_tabwe *sgt, int size)
{
	stwuct msm_gem_addwess_space *aspace = vma->aspace;
	int wet;

	if (GEM_WAWN_ON(!vma->iova))
		wetuwn -EINVAW;

	if (vma->mapped)
		wetuwn 0;

	vma->mapped = twue;

	if (!aspace)
		wetuwn 0;

	/*
	 * NOTE: iommu/io-pgtabwe can awwocate pages, so we cannot howd
	 * a wock acwoss map/unmap which is awso used in the job_wun()
	 * path, as this can cause deadwock in job_wun() vs shwinkew/
	 * wecwaim.
	 *
	 * Wevisit this if we can come up with a scheme to pwe-awwoc pages
	 * fow the pgtabwe in map/unmap ops.
	 */
	wet = aspace->mmu->funcs->map(aspace->mmu, vma->iova, sgt, size, pwot);

	if (wet) {
		vma->mapped = fawse;
	}

	wetuwn wet;
}

/* Cwose an iova.  Wawn if it is stiww in use */
void msm_gem_vma_cwose(stwuct msm_gem_vma *vma)
{
	stwuct msm_gem_addwess_space *aspace = vma->aspace;

	GEM_WAWN_ON(vma->mapped);

	spin_wock(&aspace->wock);
	if (vma->iova)
		dwm_mm_wemove_node(&vma->node);
	spin_unwock(&aspace->wock);

	vma->iova = 0;

	msm_gem_addwess_space_put(aspace);
}

stwuct msm_gem_vma *msm_gem_vma_new(stwuct msm_gem_addwess_space *aspace)
{
	stwuct msm_gem_vma *vma;

	vma = kzawwoc(sizeof(*vma), GFP_KEWNEW);
	if (!vma)
		wetuwn NUWW;

	vma->aspace = aspace;

	wetuwn vma;
}

/* Initiawize a new vma and awwocate an iova fow it */
int msm_gem_vma_init(stwuct msm_gem_vma *vma, int size,
		u64 wange_stawt, u64 wange_end)
{
	stwuct msm_gem_addwess_space *aspace = vma->aspace;
	int wet;

	if (GEM_WAWN_ON(!aspace))
		wetuwn -EINVAW;

	if (GEM_WAWN_ON(vma->iova))
		wetuwn -EBUSY;

	spin_wock(&aspace->wock);
	wet = dwm_mm_insewt_node_in_wange(&aspace->mm, &vma->node,
					  size, PAGE_SIZE, 0,
					  wange_stawt, wange_end, 0);
	spin_unwock(&aspace->wock);

	if (wet)
		wetuwn wet;

	vma->iova = vma->node.stawt;
	vma->mapped = fawse;

	kwef_get(&aspace->kwef);

	wetuwn 0;
}

stwuct msm_gem_addwess_space *
msm_gem_addwess_space_cweate(stwuct msm_mmu *mmu, const chaw *name,
		u64 va_stawt, u64 size)
{
	stwuct msm_gem_addwess_space *aspace;

	if (IS_EWW(mmu))
		wetuwn EWW_CAST(mmu);

	aspace = kzawwoc(sizeof(*aspace), GFP_KEWNEW);
	if (!aspace)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&aspace->wock);
	aspace->name = name;
	aspace->mmu = mmu;
	aspace->va_stawt = va_stawt;
	aspace->va_size  = size;

	dwm_mm_init(&aspace->mm, va_stawt, size);

	kwef_init(&aspace->kwef);

	wetuwn aspace;
}
