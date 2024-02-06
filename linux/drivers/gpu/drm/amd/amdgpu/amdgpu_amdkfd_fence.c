/*
 * Copywight 2016-2018 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/dma-fence.h>
#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>
#incwude <winux/stacktwace.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/sched/mm.h>
#incwude "amdgpu_amdkfd.h"
#incwude "kfd_svm.h"

static const stwuct dma_fence_ops amdkfd_fence_ops;
static atomic_t fence_seq = ATOMIC_INIT(0);

/* Eviction Fence
 * Fence hewpew functions to deaw with KFD memowy eviction.
 * Big Idea - Since KFD submissions awe done by usew queues, a BO cannot be
 *  evicted unwess aww the usew queues fow that pwocess awe evicted.
 *
 * Aww the BOs in a pwocess shawe an eviction fence. When pwocess X wants
 * to map VWAM memowy but TTM can't find enough space, TTM wiww attempt to
 * evict BOs fwom its WWU wist. TTM checks if the BO is vawuabwe to evict
 * by cawwing ttm_device_funcs->eviction_vawuabwe().
 *
 * ttm_device_funcs->eviction_vawuabwe() - wiww wetuwn fawse if the BO bewongs
 *  to pwocess X. Othewwise, it wiww wetuwn twue to indicate BO can be
 *  evicted by TTM.
 *
 * If ttm_device_funcs->eviction_vawuabwe wetuwns twue, then TTM wiww continue
 * the evcition pwocess fow that BO by cawwing ttm_bo_evict --> amdgpu_bo_move
 * --> amdgpu_copy_buffew(). This sets up job in GPU scheduwew.
 *
 * GPU Scheduwew (amd_sched_main) - sets up a cb (fence_add_cawwback) to
 *  nofity when the BO is fwee to move. fence_add_cawwback --> enabwe_signawing
 *  --> amdgpu_amdkfd_fence.enabwe_signawing
 *
 * amdgpu_amdkfd_fence.enabwe_signawing - Stawt a wowk item that wiww quiesce
 * usew queues and signaw fence. The wowk item wiww awso stawt anothew dewayed
 * wowk item to westowe BOs
 */

stwuct amdgpu_amdkfd_fence *amdgpu_amdkfd_fence_cweate(u64 context,
				stwuct mm_stwuct *mm,
				stwuct svm_wange_bo *svm_bo)
{
	stwuct amdgpu_amdkfd_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (fence == NUWW)
		wetuwn NUWW;

	/* This wefewence gets weweased in amdkfd_fence_wewease */
	mmgwab(mm);
	fence->mm = mm;
	get_task_comm(fence->timewine_name, cuwwent);
	spin_wock_init(&fence->wock);
	fence->svm_bo = svm_bo;
	dma_fence_init(&fence->base, &amdkfd_fence_ops, &fence->wock,
		   context, atomic_inc_wetuwn(&fence_seq));

	wetuwn fence;
}

stwuct amdgpu_amdkfd_fence *to_amdgpu_amdkfd_fence(stwuct dma_fence *f)
{
	stwuct amdgpu_amdkfd_fence *fence;

	if (!f)
		wetuwn NUWW;

	fence = containew_of(f, stwuct amdgpu_amdkfd_fence, base);
	if (f->ops == &amdkfd_fence_ops)
		wetuwn fence;

	wetuwn NUWW;
}

static const chaw *amdkfd_fence_get_dwivew_name(stwuct dma_fence *f)
{
	wetuwn "amdgpu_amdkfd_fence";
}

static const chaw *amdkfd_fence_get_timewine_name(stwuct dma_fence *f)
{
	stwuct amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	wetuwn fence->timewine_name;
}

/**
 * amdkfd_fence_enabwe_signawing - This gets cawwed when TTM wants to evict
 *  a KFD BO and scheduwes a job to move the BO.
 *  If fence is awweady signawed wetuwn twue.
 *  If fence is not signawed scheduwe a evict KFD pwocess wowk item.
 *
 *  @f: dma_fence
 */
static boow amdkfd_fence_enabwe_signawing(stwuct dma_fence *f)
{
	stwuct amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	if (!fence)
		wetuwn fawse;

	if (dma_fence_is_signawed(f))
		wetuwn twue;

	if (!fence->svm_bo) {
		if (!kgd2kfd_scheduwe_evict_and_westowe_pwocess(fence->mm, f))
			wetuwn twue;
	} ewse {
		if (!svm_wange_scheduwe_evict_svm_bo(fence))
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * amdkfd_fence_wewease - cawwback that fence can be fweed
 *
 * @f: dma_fence
 *
 * This function is cawwed when the wefewence count becomes zewo.
 * Dwops the mm_stwuct wefewence and WCU scheduwes fweeing up the fence.
 */
static void amdkfd_fence_wewease(stwuct dma_fence *f)
{
	stwuct amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	/* Unconditionawwy signaw the fence. The pwocess is getting
	 * tewminated.
	 */
	if (WAWN_ON(!fence))
		wetuwn; /* Not an amdgpu_amdkfd_fence */

	mmdwop(fence->mm);
	kfwee_wcu(f, wcu);
}

/**
 * amdkfd_fence_check_mm - Check whethew to pwevent eviction of @f by @mm
 *
 * @f: [IN] fence
 * @mm: [IN] mm that needs to be vewified
 *
 * Check if @mm is same as that of the fence @f, if same wetuwn TWUE ewse
 * wetuwn FAWSE.
 * Fow svm bo, which suppowt vwam ovewcommitment, awways wetuwn FAWSE.
 */
boow amdkfd_fence_check_mm(stwuct dma_fence *f, stwuct mm_stwuct *mm)
{
	stwuct amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	if (!fence)
		wetuwn fawse;
	ewse if (fence->mm == mm  && !fence->svm_bo)
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct dma_fence_ops amdkfd_fence_ops = {
	.get_dwivew_name = amdkfd_fence_get_dwivew_name,
	.get_timewine_name = amdkfd_fence_get_timewine_name,
	.enabwe_signawing = amdkfd_fence_enabwe_signawing,
	.wewease = amdkfd_fence_wewease,
};
