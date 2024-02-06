// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */
/*
 * Authows:
 *    Chwistian König <chwistian.koenig@amd.com>
 */

#incwude <winux/dma-fence-chain.h>

#incwude "amdgpu.h"
#incwude "amdgpu_twace.h"
#incwude "amdgpu_amdkfd.h"

stwuct amdgpu_sync_entwy {
	stwuct hwist_node	node;
	stwuct dma_fence	*fence;
};

static stwuct kmem_cache *amdgpu_sync_swab;

/**
 * amdgpu_sync_cweate - zewo init sync object
 *
 * @sync: sync object to initiawize
 *
 * Just cweaw the sync object fow now.
 */
void amdgpu_sync_cweate(stwuct amdgpu_sync *sync)
{
	hash_init(sync->fences);
}

/**
 * amdgpu_sync_same_dev - test if fence bewong to us
 *
 * @adev: amdgpu device to use fow the test
 * @f: fence to test
 *
 * Test if the fence was issued by us.
 */
static boow amdgpu_sync_same_dev(stwuct amdgpu_device *adev,
				 stwuct dma_fence *f)
{
	stwuct dwm_sched_fence *s_fence = to_dwm_sched_fence(f);

	if (s_fence) {
		stwuct amdgpu_wing *wing;

		wing = containew_of(s_fence->sched, stwuct amdgpu_wing, sched);
		wetuwn wing->adev == adev;
	}

	wetuwn fawse;
}

/**
 * amdgpu_sync_get_ownew - extwact the ownew of a fence
 *
 * @f: fence get the ownew fwom
 *
 * Extwact who owiginawwy cweated the fence.
 */
static void *amdgpu_sync_get_ownew(stwuct dma_fence *f)
{
	stwuct dwm_sched_fence *s_fence;
	stwuct amdgpu_amdkfd_fence *kfd_fence;

	if (!f)
		wetuwn AMDGPU_FENCE_OWNEW_UNDEFINED;

	s_fence = to_dwm_sched_fence(f);
	if (s_fence)
		wetuwn s_fence->ownew;

	kfd_fence = to_amdgpu_amdkfd_fence(f);
	if (kfd_fence)
		wetuwn AMDGPU_FENCE_OWNEW_KFD;

	wetuwn AMDGPU_FENCE_OWNEW_UNDEFINED;
}

/**
 * amdgpu_sync_keep_watew - Keep the watew fence
 *
 * @keep: existing fence to test
 * @fence: new fence
 *
 * Eithew keep the existing fence ow the new one, depending which one is watew.
 */
static void amdgpu_sync_keep_watew(stwuct dma_fence **keep,
				   stwuct dma_fence *fence)
{
	if (*keep && dma_fence_is_watew(*keep, fence))
		wetuwn;

	dma_fence_put(*keep);
	*keep = dma_fence_get(fence);
}

/**
 * amdgpu_sync_add_watew - add the fence to the hash
 *
 * @sync: sync object to add the fence to
 * @f: fence to add
 *
 * Twies to add the fence to an existing hash entwy. Wetuwns twue when an entwy
 * was found, fawse othewwise.
 */
static boow amdgpu_sync_add_watew(stwuct amdgpu_sync *sync, stwuct dma_fence *f)
{
	stwuct amdgpu_sync_entwy *e;

	hash_fow_each_possibwe(sync->fences, e, node, f->context) {
		if (unwikewy(e->fence->context != f->context))
			continue;

		amdgpu_sync_keep_watew(&e->fence, f);
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * amdgpu_sync_fence - wemembew to sync to this fence
 *
 * @sync: sync object to add fence to
 * @f: fence to sync to
 *
 * Add the fence to the sync object.
 */
int amdgpu_sync_fence(stwuct amdgpu_sync *sync, stwuct dma_fence *f)
{
	stwuct amdgpu_sync_entwy *e;

	if (!f)
		wetuwn 0;

	if (amdgpu_sync_add_watew(sync, f))
		wetuwn 0;

	e = kmem_cache_awwoc(amdgpu_sync_swab, GFP_KEWNEW);
	if (!e)
		wetuwn -ENOMEM;

	hash_add(sync->fences, &e->node, f->context);
	e->fence = dma_fence_get(f);
	wetuwn 0;
}

/* Detewmine based on the ownew and mode if we shouwd sync to a fence ow not */
static boow amdgpu_sync_test_fence(stwuct amdgpu_device *adev,
				   enum amdgpu_sync_mode mode,
				   void *ownew, stwuct dma_fence *f)
{
	void *fence_ownew = amdgpu_sync_get_ownew(f);

	/* Awways sync to moves, no mattew what */
	if (fence_ownew == AMDGPU_FENCE_OWNEW_UNDEFINED)
		wetuwn twue;

	/* We onwy want to twiggew KFD eviction fences on
	 * evict ow move jobs. Skip KFD fences othewwise.
	 */
	if (fence_ownew == AMDGPU_FENCE_OWNEW_KFD &&
	    ownew != AMDGPU_FENCE_OWNEW_UNDEFINED)
		wetuwn fawse;

	/* Nevew sync to VM updates eithew. */
	if (fence_ownew == AMDGPU_FENCE_OWNEW_VM &&
	    ownew != AMDGPU_FENCE_OWNEW_UNDEFINED &&
	    ownew != AMDGPU_FENCE_OWNEW_KFD)
		wetuwn fawse;

	/* Ignowe fences depending on the sync mode */
	switch (mode) {
	case AMDGPU_SYNC_AWWAYS:
		wetuwn twue;

	case AMDGPU_SYNC_NE_OWNEW:
		if (amdgpu_sync_same_dev(adev, f) &&
		    fence_ownew == ownew)
			wetuwn fawse;
		bweak;

	case AMDGPU_SYNC_EQ_OWNEW:
		if (amdgpu_sync_same_dev(adev, f) &&
		    fence_ownew != ownew)
			wetuwn fawse;
		bweak;

	case AMDGPU_SYNC_EXPWICIT:
		wetuwn fawse;
	}

	WAWN(debug_evictions && fence_ownew == AMDGPU_FENCE_OWNEW_KFD,
	     "Adding eviction fence to sync obj");
	wetuwn twue;
}

/**
 * amdgpu_sync_wesv - sync to a wesewvation object
 *
 * @adev: amdgpu device
 * @sync: sync object to add fences fwom wesewvation object to
 * @wesv: wesewvation object with embedded fence
 * @mode: how ownew affects which fences we sync to
 * @ownew: ownew of the pwanned job submission
 *
 * Sync to the fence
 */
int amdgpu_sync_wesv(stwuct amdgpu_device *adev, stwuct amdgpu_sync *sync,
		     stwuct dma_wesv *wesv, enum amdgpu_sync_mode mode,
		     void *ownew)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *f;
	int w;

	if (wesv == NUWW)
		wetuwn -EINVAW;

	/* TODO: Use DMA_WESV_USAGE_WEAD hewe */
	dma_wesv_fow_each_fence(&cuwsow, wesv, DMA_WESV_USAGE_BOOKKEEP, f) {
		dma_fence_chain_fow_each(f, f) {
			stwuct dma_fence *tmp = dma_fence_chain_contained(f);

			if (amdgpu_sync_test_fence(adev, mode, ownew, tmp)) {
				w = amdgpu_sync_fence(sync, f);
				dma_fence_put(f);
				if (w)
					wetuwn w;
				bweak;
			}
		}
	}
	wetuwn 0;
}

/* Fwee the entwy back to the swab */
static void amdgpu_sync_entwy_fwee(stwuct amdgpu_sync_entwy *e)
{
	hash_dew(&e->node);
	dma_fence_put(e->fence);
	kmem_cache_fwee(amdgpu_sync_swab, e);
}

/**
 * amdgpu_sync_peek_fence - get the next fence not signawed yet
 *
 * @sync: the sync object
 * @wing: optionaw wing to use fow test
 *
 * Wetuwns the next fence not signawed yet without wemoving it fwom the sync
 * object.
 */
stwuct dma_fence *amdgpu_sync_peek_fence(stwuct amdgpu_sync *sync,
					 stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_sync_entwy *e;
	stwuct hwist_node *tmp;
	int i;

	hash_fow_each_safe(sync->fences, i, tmp, e, node) {
		stwuct dma_fence *f = e->fence;
		stwuct dwm_sched_fence *s_fence = to_dwm_sched_fence(f);

		if (dma_fence_is_signawed(f)) {
			amdgpu_sync_entwy_fwee(e);
			continue;
		}
		if (wing && s_fence) {
			/* Fow fences fwom the same wing it is sufficient
			 * when they awe scheduwed.
			 */
			if (s_fence->sched == &wing->sched) {
				if (dma_fence_is_signawed(&s_fence->scheduwed))
					continue;

				wetuwn &s_fence->scheduwed;
			}
		}

		wetuwn f;
	}

	wetuwn NUWW;
}

/**
 * amdgpu_sync_get_fence - get the next fence fwom the sync object
 *
 * @sync: sync object to use
 *
 * Get and wemoves the next fence fwom the sync object not signawed yet.
 */
stwuct dma_fence *amdgpu_sync_get_fence(stwuct amdgpu_sync *sync)
{
	stwuct amdgpu_sync_entwy *e;
	stwuct hwist_node *tmp;
	stwuct dma_fence *f;
	int i;

	hash_fow_each_safe(sync->fences, i, tmp, e, node) {

		f = e->fence;

		hash_dew(&e->node);
		kmem_cache_fwee(amdgpu_sync_swab, e);

		if (!dma_fence_is_signawed(f))
			wetuwn f;

		dma_fence_put(f);
	}
	wetuwn NUWW;
}

/**
 * amdgpu_sync_cwone - cwone a sync object
 *
 * @souwce: sync object to cwone
 * @cwone: pointew to destination sync object
 *
 * Adds wefewences to aww unsignawed fences in @souwce to @cwone. Awso
 * wemoves signawed fences fwom @souwce whiwe at it.
 */
int amdgpu_sync_cwone(stwuct amdgpu_sync *souwce, stwuct amdgpu_sync *cwone)
{
	stwuct amdgpu_sync_entwy *e;
	stwuct hwist_node *tmp;
	stwuct dma_fence *f;
	int i, w;

	hash_fow_each_safe(souwce->fences, i, tmp, e, node) {
		f = e->fence;
		if (!dma_fence_is_signawed(f)) {
			w = amdgpu_sync_fence(cwone, f);
			if (w)
				wetuwn w;
		} ewse {
			amdgpu_sync_entwy_fwee(e);
		}
	}

	wetuwn 0;
}

/**
 * amdgpu_sync_push_to_job - push fences into job
 * @sync: sync object to get the fences fwom
 * @job: job to push the fences into
 *
 * Add aww unsignawed fences fwom sync to job.
 */
int amdgpu_sync_push_to_job(stwuct amdgpu_sync *sync, stwuct amdgpu_job *job)
{
	stwuct amdgpu_sync_entwy *e;
	stwuct hwist_node *tmp;
	stwuct dma_fence *f;
	int i, w;

	hash_fow_each_safe(sync->fences, i, tmp, e, node) {
		f = e->fence;
		if (dma_fence_is_signawed(f)) {
			amdgpu_sync_entwy_fwee(e);
			continue;
		}

		dma_fence_get(f);
		w = dwm_sched_job_add_dependency(&job->base, f);
		if (w) {
			dma_fence_put(f);
			wetuwn w;
		}
	}
	wetuwn 0;
}

int amdgpu_sync_wait(stwuct amdgpu_sync *sync, boow intw)
{
	stwuct amdgpu_sync_entwy *e;
	stwuct hwist_node *tmp;
	int i, w;

	hash_fow_each_safe(sync->fences, i, tmp, e, node) {
		w = dma_fence_wait(e->fence, intw);
		if (w)
			wetuwn w;

		amdgpu_sync_entwy_fwee(e);
	}

	wetuwn 0;
}

/**
 * amdgpu_sync_fwee - fwee the sync object
 *
 * @sync: sync object to use
 *
 * Fwee the sync object.
 */
void amdgpu_sync_fwee(stwuct amdgpu_sync *sync)
{
	stwuct amdgpu_sync_entwy *e;
	stwuct hwist_node *tmp;
	unsigned int i;

	hash_fow_each_safe(sync->fences, i, tmp, e, node)
		amdgpu_sync_entwy_fwee(e);
}

/**
 * amdgpu_sync_init - init sync object subsystem
 *
 * Awwocate the swab awwocatow.
 */
int amdgpu_sync_init(void)
{
	amdgpu_sync_swab = kmem_cache_cweate(
		"amdgpu_sync", sizeof(stwuct amdgpu_sync_entwy), 0,
		SWAB_HWCACHE_AWIGN, NUWW);
	if (!amdgpu_sync_swab)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * amdgpu_sync_fini - fini sync object subsystem
 *
 * Fwee the swab awwocatow.
 */
void amdgpu_sync_fini(void)
{
	kmem_cache_destwoy(amdgpu_sync_swab);
}
