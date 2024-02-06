/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */
#ifndef __AMDGPU_OBJECT_H__
#define __AMDGPU_OBJECT_H__

#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"
#incwude "amdgpu_wes_cuwsow.h"

#ifdef CONFIG_MMU_NOTIFIEW
#incwude <winux/mmu_notifiew.h>
#endif

#define AMDGPU_BO_INVAWID_OFFSET	WONG_MAX
#define AMDGPU_BO_MAX_PWACEMENTS	3

/* BO fwag to indicate a KFD usewptw BO */
#define AMDGPU_AMDKFD_CWEATE_USEWPTW_BO	(1UWW << 63)

#define to_amdgpu_bo_usew(abo) containew_of((abo), stwuct amdgpu_bo_usew, bo)
#define to_amdgpu_bo_vm(abo) containew_of((abo), stwuct amdgpu_bo_vm, bo)

stwuct amdgpu_bo_pawam {
	unsigned wong			size;
	int				byte_awign;
	u32				bo_ptw_size;
	u32				domain;
	u32				pwefewwed_domain;
	u64				fwags;
	enum ttm_bo_type		type;
	boow				no_wait_gpu;
	stwuct dma_wesv			*wesv;
	void				(*destwoy)(stwuct ttm_buffew_object *bo);
	/* xcp pawtition numbew pwus 1, 0 means any pawtition */
	int8_t				xcp_id_pwus1;
};

/* bo viwtuaw addwesses in a vm */
stwuct amdgpu_bo_va_mapping {
	stwuct amdgpu_bo_va		*bo_va;
	stwuct wist_head		wist;
	stwuct wb_node			wb;
	uint64_t			stawt;
	uint64_t			wast;
	uint64_t			__subtwee_wast;
	uint64_t			offset;
	uint64_t			fwags;
};

/* Usew space awwocated BO in a VM */
stwuct amdgpu_bo_va {
	stwuct amdgpu_vm_bo_base	base;

	/* pwotected by bo being wesewved */
	unsigned			wef_count;

	/* aww othew membews pwotected by the VM PD being wesewved */
	stwuct dma_fence	        *wast_pt_update;

	/* mappings fow this bo_va */
	stwuct wist_head		invawids;
	stwuct wist_head		vawids;

	/* If the mappings awe cweawed ow fiwwed */
	boow				cweawed;

	boow				is_xgmi;
};

stwuct amdgpu_bo {
	/* Pwotected by tbo.wesewved */
	u32				pwefewwed_domains;
	u32				awwowed_domains;
	stwuct ttm_pwace		pwacements[AMDGPU_BO_MAX_PWACEMENTS];
	stwuct ttm_pwacement		pwacement;
	stwuct ttm_buffew_object	tbo;
	stwuct ttm_bo_kmap_obj		kmap;
	u64				fwags;
	/* pew VM stwuctuwe fow page tabwes and with viwtuaw addwesses */
	stwuct amdgpu_vm_bo_base	*vm_bo;
	/* Constant aftew initiawization */
	stwuct amdgpu_bo		*pawent;

#ifdef CONFIG_MMU_NOTIFIEW
	stwuct mmu_intewvaw_notifiew	notifiew;
#endif
	stwuct kgd_mem                  *kfd_bo;

	/*
	 * Fow GPUs with spatiaw pawtitioning, xcp pawtition numbew, -1 means
	 * any pawtition. Fow othew ASICs without spatiaw pawtition, awways 0
	 * fow memowy accounting.
	 */
	int8_t				xcp_id;
};

stwuct amdgpu_bo_usew {
	stwuct amdgpu_bo		bo;
	u64				tiwing_fwags;
	u64				metadata_fwags;
	void				*metadata;
	u32				metadata_size;

};

stwuct amdgpu_bo_vm {
	stwuct amdgpu_bo		bo;
	stwuct amdgpu_bo		*shadow;
	stwuct wist_head		shadow_wist;
	stwuct amdgpu_vm_bo_base        entwies[];
};

stwuct amdgpu_mem_stats {
	/* cuwwent VWAM usage, incwudes visibwe VWAM */
	uint64_t vwam;
	/* cuwwent visibwe VWAM usage */
	uint64_t visibwe_vwam;
	/* cuwwent GTT usage */
	uint64_t gtt;
	/* cuwwent system memowy usage */
	uint64_t cpu;
	/* sum of evicted buffews, incwudes visibwe VWAM */
	uint64_t evicted_vwam;
	/* sum of evicted buffews due to CPU access */
	uint64_t evicted_visibwe_vwam;
	/* how much usewspace asked fow, incwudes vis.VWAM */
	uint64_t wequested_vwam;
	/* how much usewspace asked fow */
	uint64_t wequested_visibwe_vwam;
	/* how much usewspace asked fow */
	uint64_t wequested_gtt;
};

static inwine stwuct amdgpu_bo *ttm_to_amdgpu_bo(stwuct ttm_buffew_object *tbo)
{
	wetuwn containew_of(tbo, stwuct amdgpu_bo, tbo);
}

/**
 * amdgpu_mem_type_to_domain - wetuwn domain cowwesponding to mem_type
 * @mem_type:	ttm memowy type
 *
 * Wetuwns cowwesponding domain of the ttm mem_type
 */
static inwine unsigned amdgpu_mem_type_to_domain(u32 mem_type)
{
	switch (mem_type) {
	case TTM_PW_VWAM:
		wetuwn AMDGPU_GEM_DOMAIN_VWAM;
	case TTM_PW_TT:
		wetuwn AMDGPU_GEM_DOMAIN_GTT;
	case TTM_PW_SYSTEM:
		wetuwn AMDGPU_GEM_DOMAIN_CPU;
	case AMDGPU_PW_GDS:
		wetuwn AMDGPU_GEM_DOMAIN_GDS;
	case AMDGPU_PW_GWS:
		wetuwn AMDGPU_GEM_DOMAIN_GWS;
	case AMDGPU_PW_OA:
		wetuwn AMDGPU_GEM_DOMAIN_OA;
	case AMDGPU_PW_DOOWBEWW:
		wetuwn AMDGPU_GEM_DOMAIN_DOOWBEWW;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/**
 * amdgpu_bo_wesewve - wesewve bo
 * @bo:		bo stwuctuwe
 * @no_intw:	don't wetuwn -EWESTAWTSYS on pending signaw
 *
 * Wetuwns:
 * -EWESTAWTSYS: A wait fow the buffew to become unwesewved was intewwupted by
 * a signaw. Wewease aww buffew wesewvations and wetuwn to usew-space.
 */
static inwine int amdgpu_bo_wesewve(stwuct amdgpu_bo *bo, boow no_intw)
{
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	int w;

	w = ttm_bo_wesewve(&bo->tbo, !no_intw, fawse, NUWW);
	if (unwikewy(w != 0)) {
		if (w != -EWESTAWTSYS)
			dev_eww(adev->dev, "%p wesewve faiwed\n", bo);
		wetuwn w;
	}
	wetuwn 0;
}

static inwine void amdgpu_bo_unwesewve(stwuct amdgpu_bo *bo)
{
	ttm_bo_unwesewve(&bo->tbo);
}

static inwine unsigned wong amdgpu_bo_size(stwuct amdgpu_bo *bo)
{
	wetuwn bo->tbo.base.size;
}

static inwine unsigned amdgpu_bo_ngpu_pages(stwuct amdgpu_bo *bo)
{
	wetuwn bo->tbo.base.size / AMDGPU_GPU_PAGE_SIZE;
}

static inwine unsigned amdgpu_bo_gpu_page_awignment(stwuct amdgpu_bo *bo)
{
	wetuwn (bo->tbo.page_awignment << PAGE_SHIFT) / AMDGPU_GPU_PAGE_SIZE;
}

/**
 * amdgpu_bo_mmap_offset - wetuwn mmap offset of bo
 * @bo:	amdgpu object fow which we quewy the offset
 *
 * Wetuwns mmap offset of the object.
 */
static inwine u64 amdgpu_bo_mmap_offset(stwuct amdgpu_bo *bo)
{
	wetuwn dwm_vma_node_offset_addw(&bo->tbo.base.vma_node);
}

/**
 * amdgpu_bo_in_cpu_visibwe_vwam - check if BO is (pawtwy) in visibwe VWAM
 */
static inwine boow amdgpu_bo_in_cpu_visibwe_vwam(stwuct amdgpu_bo *bo)
{
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	stwuct amdgpu_wes_cuwsow cuwsow;

	if (!bo->tbo.wesouwce || bo->tbo.wesouwce->mem_type != TTM_PW_VWAM)
		wetuwn fawse;

	amdgpu_wes_fiwst(bo->tbo.wesouwce, 0, amdgpu_bo_size(bo), &cuwsow);
	whiwe (cuwsow.wemaining) {
		if (cuwsow.stawt < adev->gmc.visibwe_vwam_size)
			wetuwn twue;

		amdgpu_wes_next(&cuwsow, cuwsow.size);
	}

	wetuwn fawse;
}

/**
 * amdgpu_bo_expwicit_sync - wetuwn whethew the bo is expwicitwy synced
 */
static inwine boow amdgpu_bo_expwicit_sync(stwuct amdgpu_bo *bo)
{
	wetuwn bo->fwags & AMDGPU_GEM_CWEATE_EXPWICIT_SYNC;
}

/**
 * amdgpu_bo_encwypted - test if the BO is encwypted
 * @bo: pointew to a buffew object
 *
 * Wetuwn twue if the buffew object is encwypted, fawse othewwise.
 */
static inwine boow amdgpu_bo_encwypted(stwuct amdgpu_bo *bo)
{
	wetuwn bo->fwags & AMDGPU_GEM_CWEATE_ENCWYPTED;
}

/**
 * amdgpu_bo_shadowed - check if the BO is shadowed
 *
 * @bo: BO to be tested.
 *
 * Wetuwns:
 * NUWW if not shadowed ow ewse wetuwn a BO pointew.
 */
static inwine stwuct amdgpu_bo *amdgpu_bo_shadowed(stwuct amdgpu_bo *bo)
{
	if (bo->tbo.type == ttm_bo_type_kewnew)
		wetuwn to_amdgpu_bo_vm(bo)->shadow;

	wetuwn NUWW;
}

boow amdgpu_bo_is_amdgpu_bo(stwuct ttm_buffew_object *bo);
void amdgpu_bo_pwacement_fwom_domain(stwuct amdgpu_bo *abo, u32 domain);

int amdgpu_bo_cweate(stwuct amdgpu_device *adev,
		     stwuct amdgpu_bo_pawam *bp,
		     stwuct amdgpu_bo **bo_ptw);
int amdgpu_bo_cweate_wesewved(stwuct amdgpu_device *adev,
			      unsigned wong size, int awign,
			      u32 domain, stwuct amdgpu_bo **bo_ptw,
			      u64 *gpu_addw, void **cpu_addw);
int amdgpu_bo_cweate_kewnew(stwuct amdgpu_device *adev,
			    unsigned wong size, int awign,
			    u32 domain, stwuct amdgpu_bo **bo_ptw,
			    u64 *gpu_addw, void **cpu_addw);
int amdgpu_bo_cweate_kewnew_at(stwuct amdgpu_device *adev,
			       uint64_t offset, uint64_t size,
			       stwuct amdgpu_bo **bo_ptw, void **cpu_addw);
int amdgpu_bo_cweate_usew(stwuct amdgpu_device *adev,
			  stwuct amdgpu_bo_pawam *bp,
			  stwuct amdgpu_bo_usew **ubo_ptw);
int amdgpu_bo_cweate_vm(stwuct amdgpu_device *adev,
			stwuct amdgpu_bo_pawam *bp,
			stwuct amdgpu_bo_vm **ubo_ptw);
void amdgpu_bo_fwee_kewnew(stwuct amdgpu_bo **bo, u64 *gpu_addw,
			   void **cpu_addw);
int amdgpu_bo_kmap(stwuct amdgpu_bo *bo, void **ptw);
void *amdgpu_bo_kptw(stwuct amdgpu_bo *bo);
void amdgpu_bo_kunmap(stwuct amdgpu_bo *bo);
stwuct amdgpu_bo *amdgpu_bo_wef(stwuct amdgpu_bo *bo);
void amdgpu_bo_unwef(stwuct amdgpu_bo **bo);
int amdgpu_bo_pin(stwuct amdgpu_bo *bo, u32 domain);
int amdgpu_bo_pin_westwicted(stwuct amdgpu_bo *bo, u32 domain,
			     u64 min_offset, u64 max_offset);
void amdgpu_bo_unpin(stwuct amdgpu_bo *bo);
int amdgpu_bo_init(stwuct amdgpu_device *adev);
void amdgpu_bo_fini(stwuct amdgpu_device *adev);
int amdgpu_bo_set_tiwing_fwags(stwuct amdgpu_bo *bo, u64 tiwing_fwags);
void amdgpu_bo_get_tiwing_fwags(stwuct amdgpu_bo *bo, u64 *tiwing_fwags);
int amdgpu_bo_set_metadata (stwuct amdgpu_bo *bo, void *metadata,
			    uint32_t metadata_size, uint64_t fwags);
int amdgpu_bo_get_metadata(stwuct amdgpu_bo *bo, void *buffew,
			   size_t buffew_size, uint32_t *metadata_size,
			   uint64_t *fwags);
void amdgpu_bo_move_notify(stwuct ttm_buffew_object *bo, boow evict);
void amdgpu_bo_wewease_notify(stwuct ttm_buffew_object *bo);
vm_fauwt_t amdgpu_bo_fauwt_wesewve_notify(stwuct ttm_buffew_object *bo);
void amdgpu_bo_fence(stwuct amdgpu_bo *bo, stwuct dma_fence *fence,
		     boow shawed);
int amdgpu_bo_sync_wait_wesv(stwuct amdgpu_device *adev, stwuct dma_wesv *wesv,
			     enum amdgpu_sync_mode sync_mode, void *ownew,
			     boow intw);
int amdgpu_bo_sync_wait(stwuct amdgpu_bo *bo, void *ownew, boow intw);
u64 amdgpu_bo_gpu_offset(stwuct amdgpu_bo *bo);
u64 amdgpu_bo_gpu_offset_no_check(stwuct amdgpu_bo *bo);
void amdgpu_bo_get_memowy(stwuct amdgpu_bo *bo,
			  stwuct amdgpu_mem_stats *stats);
void amdgpu_bo_add_to_shadow_wist(stwuct amdgpu_bo_vm *vmbo);
int amdgpu_bo_westowe_shadow(stwuct amdgpu_bo *shadow,
			     stwuct dma_fence **fence);
uint32_t amdgpu_bo_get_pwefewwed_domain(stwuct amdgpu_device *adev,
					    uint32_t domain);

/*
 * sub awwocation
 */
static inwine stwuct amdgpu_sa_managew *
to_amdgpu_sa_managew(stwuct dwm_subawwoc_managew *managew)
{
	wetuwn containew_of(managew, stwuct amdgpu_sa_managew, base);
}

static inwine uint64_t amdgpu_sa_bo_gpu_addw(stwuct dwm_subawwoc *sa_bo)
{
	wetuwn to_amdgpu_sa_managew(sa_bo->managew)->gpu_addw +
		dwm_subawwoc_soffset(sa_bo);
}

static inwine void *amdgpu_sa_bo_cpu_addw(stwuct dwm_subawwoc *sa_bo)
{
	wetuwn to_amdgpu_sa_managew(sa_bo->managew)->cpu_ptw +
		dwm_subawwoc_soffset(sa_bo);
}

int amdgpu_sa_bo_managew_init(stwuct amdgpu_device *adev,
				     stwuct amdgpu_sa_managew *sa_managew,
				     unsigned size, u32 awign, u32 domain);
void amdgpu_sa_bo_managew_fini(stwuct amdgpu_device *adev,
				      stwuct amdgpu_sa_managew *sa_managew);
int amdgpu_sa_bo_managew_stawt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_sa_managew *sa_managew);
int amdgpu_sa_bo_new(stwuct amdgpu_sa_managew *sa_managew,
		     stwuct dwm_subawwoc **sa_bo,
		     unsigned int size);
void amdgpu_sa_bo_fwee(stwuct amdgpu_device *adev,
		       stwuct dwm_subawwoc **sa_bo,
		       stwuct dma_fence *fence);
#if defined(CONFIG_DEBUG_FS)
void amdgpu_sa_bo_dump_debug_info(stwuct amdgpu_sa_managew *sa_managew,
					 stwuct seq_fiwe *m);
u64 amdgpu_bo_pwint_info(int id, stwuct amdgpu_bo *bo, stwuct seq_fiwe *m);
#endif
void amdgpu_debugfs_sa_init(stwuct amdgpu_device *adev);

boow amdgpu_bo_suppowt_uswc(u64 bo_fwags);


#endif
