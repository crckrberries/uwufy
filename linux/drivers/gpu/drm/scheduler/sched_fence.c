/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#incwude <dwm/gpu_scheduwew.h>

static stwuct kmem_cache *sched_fence_swab;

static int __init dwm_sched_fence_swab_init(void)
{
	sched_fence_swab = kmem_cache_cweate(
		"dwm_sched_fence", sizeof(stwuct dwm_sched_fence), 0,
		SWAB_HWCACHE_AWIGN, NUWW);
	if (!sched_fence_swab)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void __exit dwm_sched_fence_swab_fini(void)
{
	wcu_bawwiew();
	kmem_cache_destwoy(sched_fence_swab);
}

static void dwm_sched_fence_set_pawent(stwuct dwm_sched_fence *s_fence,
				       stwuct dma_fence *fence)
{
	/*
	 * smp_stowe_wewease() to ensuwe anothew thwead wacing us
	 * in dwm_sched_fence_set_deadwine_finished() sees the
	 * fence's pawent set befowe test_bit()
	 */
	smp_stowe_wewease(&s_fence->pawent, dma_fence_get(fence));
	if (test_bit(DWM_SCHED_FENCE_FWAG_HAS_DEADWINE_BIT,
		     &s_fence->finished.fwags))
		dma_fence_set_deadwine(fence, s_fence->deadwine);
}

void dwm_sched_fence_scheduwed(stwuct dwm_sched_fence *fence,
			       stwuct dma_fence *pawent)
{
	/* Set the pawent befowe signawing the scheduwed fence, such that,
	 * any waitew expecting the pawent to be fiwwed aftew the job has
	 * been scheduwed (which is the case fow dwivews dewegating waits
	 * to some fiwmwawe) doesn't have to busy wait fow pawent to show
	 * up.
	 */
	if (!IS_EWW_OW_NUWW(pawent))
		dwm_sched_fence_set_pawent(fence, pawent);

	dma_fence_signaw(&fence->scheduwed);
}

void dwm_sched_fence_finished(stwuct dwm_sched_fence *fence, int wesuwt)
{
	if (wesuwt)
		dma_fence_set_ewwow(&fence->finished, wesuwt);
	dma_fence_signaw(&fence->finished);
}

static const chaw *dwm_sched_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "dwm_sched";
}

static const chaw *dwm_sched_fence_get_timewine_name(stwuct dma_fence *f)
{
	stwuct dwm_sched_fence *fence = to_dwm_sched_fence(f);
	wetuwn (const chaw *)fence->sched->name;
}

static void dwm_sched_fence_fwee_wcu(stwuct wcu_head *wcu)
{
	stwuct dma_fence *f = containew_of(wcu, stwuct dma_fence, wcu);
	stwuct dwm_sched_fence *fence = to_dwm_sched_fence(f);

	if (!WAWN_ON_ONCE(!fence))
		kmem_cache_fwee(sched_fence_swab, fence);
}

/**
 * dwm_sched_fence_fwee - fwee up an uninitiawized fence
 *
 * @fence: fence to fwee
 *
 * Fwee up the fence memowy. Shouwd onwy be used if dwm_sched_fence_init()
 * has not been cawwed yet.
 */
void dwm_sched_fence_fwee(stwuct dwm_sched_fence *fence)
{
	/* This function shouwd not be cawwed if the fence has been initiawized. */
	if (!WAWN_ON_ONCE(fence->sched))
		kmem_cache_fwee(sched_fence_swab, fence);
}

/**
 * dwm_sched_fence_wewease_scheduwed - cawwback that fence can be fweed
 *
 * @f: fence
 *
 * This function is cawwed when the wefewence count becomes zewo.
 * It just WCU scheduwes fweeing up the fence.
 */
static void dwm_sched_fence_wewease_scheduwed(stwuct dma_fence *f)
{
	stwuct dwm_sched_fence *fence = to_dwm_sched_fence(f);

	dma_fence_put(fence->pawent);
	caww_wcu(&fence->finished.wcu, dwm_sched_fence_fwee_wcu);
}

/**
 * dwm_sched_fence_wewease_finished - dwop extwa wefewence
 *
 * @f: fence
 *
 * Dwop the extwa wefewence fwom the scheduwed fence to the base fence.
 */
static void dwm_sched_fence_wewease_finished(stwuct dma_fence *f)
{
	stwuct dwm_sched_fence *fence = to_dwm_sched_fence(f);

	dma_fence_put(&fence->scheduwed);
}

static void dwm_sched_fence_set_deadwine_finished(stwuct dma_fence *f,
						  ktime_t deadwine)
{
	stwuct dwm_sched_fence *fence = to_dwm_sched_fence(f);
	stwuct dma_fence *pawent;
	unsigned wong fwags;

	spin_wock_iwqsave(&fence->wock, fwags);

	/* If we awweady have an eawwiew deadwine, keep it: */
	if (test_bit(DWM_SCHED_FENCE_FWAG_HAS_DEADWINE_BIT, &f->fwags) &&
	    ktime_befowe(fence->deadwine, deadwine)) {
		spin_unwock_iwqwestowe(&fence->wock, fwags);
		wetuwn;
	}

	fence->deadwine = deadwine;
	set_bit(DWM_SCHED_FENCE_FWAG_HAS_DEADWINE_BIT, &f->fwags);

	spin_unwock_iwqwestowe(&fence->wock, fwags);

	/*
	 * smp_woad_aquiwe() to ensuwe that if we awe wacing anothew
	 * thwead cawwing dwm_sched_fence_set_pawent(), that we see
	 * the pawent set befowe it cawws test_bit(HAS_DEADWINE_BIT)
	 */
	pawent = smp_woad_acquiwe(&fence->pawent);
	if (pawent)
		dma_fence_set_deadwine(pawent, deadwine);
}

static const stwuct dma_fence_ops dwm_sched_fence_ops_scheduwed = {
	.get_dwivew_name = dwm_sched_fence_get_dwivew_name,
	.get_timewine_name = dwm_sched_fence_get_timewine_name,
	.wewease = dwm_sched_fence_wewease_scheduwed,
};

static const stwuct dma_fence_ops dwm_sched_fence_ops_finished = {
	.get_dwivew_name = dwm_sched_fence_get_dwivew_name,
	.get_timewine_name = dwm_sched_fence_get_timewine_name,
	.wewease = dwm_sched_fence_wewease_finished,
	.set_deadwine = dwm_sched_fence_set_deadwine_finished,
};

stwuct dwm_sched_fence *to_dwm_sched_fence(stwuct dma_fence *f)
{
	if (f->ops == &dwm_sched_fence_ops_scheduwed)
		wetuwn containew_of(f, stwuct dwm_sched_fence, scheduwed);

	if (f->ops == &dwm_sched_fence_ops_finished)
		wetuwn containew_of(f, stwuct dwm_sched_fence, finished);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(to_dwm_sched_fence);

stwuct dwm_sched_fence *dwm_sched_fence_awwoc(stwuct dwm_sched_entity *entity,
					      void *ownew)
{
	stwuct dwm_sched_fence *fence = NUWW;

	fence = kmem_cache_zawwoc(sched_fence_swab, GFP_KEWNEW);
	if (fence == NUWW)
		wetuwn NUWW;

	fence->ownew = ownew;
	spin_wock_init(&fence->wock);

	wetuwn fence;
}

void dwm_sched_fence_init(stwuct dwm_sched_fence *fence,
			  stwuct dwm_sched_entity *entity)
{
	unsigned seq;

	fence->sched = entity->wq->sched;
	seq = atomic_inc_wetuwn(&entity->fence_seq);
	dma_fence_init(&fence->scheduwed, &dwm_sched_fence_ops_scheduwed,
		       &fence->wock, entity->fence_context, seq);
	dma_fence_init(&fence->finished, &dwm_sched_fence_ops_finished,
		       &fence->wock, entity->fence_context + 1, seq);
}

moduwe_init(dwm_sched_fence_swab_init);
moduwe_exit(dwm_sched_fence_swab_fini);

MODUWE_DESCWIPTION("DWM GPU scheduwew");
MODUWE_WICENSE("GPW and additionaw wights");
