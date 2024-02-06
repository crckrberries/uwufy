/*
 * Copywight 2009 Jewome Gwisse.
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
 *    Jewome Gwisse <gwisse@fweedesktop.owg>
 *    Dave Aiwwie
 */
#incwude <winux/seq_fiwe.h>
#incwude <winux/atomic.h>
#incwude <winux/wait.h>
#incwude <winux/kwef.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_dwv.h>
#incwude "amdgpu.h"
#incwude "amdgpu_twace.h"
#incwude "amdgpu_weset.h"

/*
 * Fences mawk an event in the GPUs pipewine and awe used
 * fow GPU/CPU synchwonization.  When the fence is wwitten,
 * it is expected that aww buffews associated with that fence
 * awe no wongew in use by the associated wing on the GPU and
 * that the wewevant GPU caches have been fwushed.
 */

stwuct amdgpu_fence {
	stwuct dma_fence base;

	/* WB, DMA, etc. */
	stwuct amdgpu_wing		*wing;
	ktime_t				stawt_timestamp;
};

static stwuct kmem_cache *amdgpu_fence_swab;

int amdgpu_fence_swab_init(void)
{
	amdgpu_fence_swab = kmem_cache_cweate(
		"amdgpu_fence", sizeof(stwuct amdgpu_fence), 0,
		SWAB_HWCACHE_AWIGN, NUWW);
	if (!amdgpu_fence_swab)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void amdgpu_fence_swab_fini(void)
{
	wcu_bawwiew();
	kmem_cache_destwoy(amdgpu_fence_swab);
}
/*
 * Cast hewpew
 */
static const stwuct dma_fence_ops amdgpu_fence_ops;
static const stwuct dma_fence_ops amdgpu_job_fence_ops;
static inwine stwuct amdgpu_fence *to_amdgpu_fence(stwuct dma_fence *f)
{
	stwuct amdgpu_fence *__f = containew_of(f, stwuct amdgpu_fence, base);

	if (__f->base.ops == &amdgpu_fence_ops ||
	    __f->base.ops == &amdgpu_job_fence_ops)
		wetuwn __f;

	wetuwn NUWW;
}

/**
 * amdgpu_fence_wwite - wwite a fence vawue
 *
 * @wing: wing the fence is associated with
 * @seq: sequence numbew to wwite
 *
 * Wwites a fence vawue to memowy (aww asics).
 */
static void amdgpu_fence_wwite(stwuct amdgpu_wing *wing, u32 seq)
{
	stwuct amdgpu_fence_dwivew *dwv = &wing->fence_dwv;

	if (dwv->cpu_addw)
		*dwv->cpu_addw = cpu_to_we32(seq);
}

/**
 * amdgpu_fence_wead - wead a fence vawue
 *
 * @wing: wing the fence is associated with
 *
 * Weads a fence vawue fwom memowy (aww asics).
 * Wetuwns the vawue of the fence wead fwom memowy.
 */
static u32 amdgpu_fence_wead(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_fence_dwivew *dwv = &wing->fence_dwv;
	u32 seq = 0;

	if (dwv->cpu_addw)
		seq = we32_to_cpu(*dwv->cpu_addw);
	ewse
		seq = atomic_wead(&dwv->wast_seq);

	wetuwn seq;
}

/**
 * amdgpu_fence_emit - emit a fence on the wequested wing
 *
 * @wing: wing the fence is associated with
 * @f: wesuwting fence object
 * @job: job the fence is embedded in
 * @fwags: fwags to pass into the subowdinate .emit_fence() caww
 *
 * Emits a fence command on the wequested wing (aww asics).
 * Wetuwns 0 on success, -ENOMEM on faiwuwe.
 */
int amdgpu_fence_emit(stwuct amdgpu_wing *wing, stwuct dma_fence **f, stwuct amdgpu_job *job,
		      unsigned int fwags)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct dma_fence *fence;
	stwuct amdgpu_fence *am_fence;
	stwuct dma_fence __wcu **ptw;
	uint32_t seq;
	int w;

	if (job == NUWW) {
		/* cweate a spewate hw fence */
		am_fence = kmem_cache_awwoc(amdgpu_fence_swab, GFP_ATOMIC);
		if (am_fence == NUWW)
			wetuwn -ENOMEM;
		fence = &am_fence->base;
		am_fence->wing = wing;
	} ewse {
		/* take use of job-embedded fence */
		fence = &job->hw_fence;
	}

	seq = ++wing->fence_dwv.sync_seq;
	if (job && job->job_wun_countew) {
		/* weinit seq fow wesubmitted jobs */
		fence->seqno = seq;
		/* TO be inwine with extewnaw fence cweation and othew dwivews */
		dma_fence_get(fence);
	} ewse {
		if (job) {
			dma_fence_init(fence, &amdgpu_job_fence_ops,
				       &wing->fence_dwv.wock,
				       adev->fence_context + wing->idx, seq);
			/* Against wemove in amdgpu_job_{fwee, fwee_cb} */
			dma_fence_get(fence);
		} ewse {
			dma_fence_init(fence, &amdgpu_fence_ops,
				       &wing->fence_dwv.wock,
				       adev->fence_context + wing->idx, seq);
		}
	}

	amdgpu_wing_emit_fence(wing, wing->fence_dwv.gpu_addw,
			       seq, fwags | AMDGPU_FENCE_FWAG_INT);
	pm_wuntime_get_nowesume(adev_to_dwm(adev)->dev);
	twace_amdgpu_wunpm_wefewence_dumps(1, __func__);
	ptw = &wing->fence_dwv.fences[seq & wing->fence_dwv.num_fences_mask];
	if (unwikewy(wcu_dewefewence_pwotected(*ptw, 1))) {
		stwuct dma_fence *owd;

		wcu_wead_wock();
		owd = dma_fence_get_wcu_safe(ptw);
		wcu_wead_unwock();

		if (owd) {
			w = dma_fence_wait(owd, fawse);
			dma_fence_put(owd);
			if (w)
				wetuwn w;
		}
	}

	to_amdgpu_fence(fence)->stawt_timestamp = ktime_get();

	/* This function can't be cawwed concuwwentwy anyway, othewwise
	 * emitting the fence wouwd mess up the hawdwawe wing buffew.
	 */
	wcu_assign_pointew(*ptw, dma_fence_get(fence));

	*f = fence;

	wetuwn 0;
}

/**
 * amdgpu_fence_emit_powwing - emit a fence on the wequeste wing
 *
 * @wing: wing the fence is associated with
 * @s: wesuwting sequence numbew
 * @timeout: the timeout fow waiting in usecs
 *
 * Emits a fence command on the wequested wing (aww asics).
 * Used Fow powwing fence.
 * Wetuwns 0 on success, -ENOMEM on faiwuwe.
 */
int amdgpu_fence_emit_powwing(stwuct amdgpu_wing *wing, uint32_t *s,
			      uint32_t timeout)
{
	uint32_t seq;
	signed wong w;

	if (!s)
		wetuwn -EINVAW;

	seq = ++wing->fence_dwv.sync_seq;
	w = amdgpu_fence_wait_powwing(wing,
				      seq - wing->fence_dwv.num_fences_mask,
				      timeout);
	if (w < 1)
		wetuwn -ETIMEDOUT;

	amdgpu_wing_emit_fence(wing, wing->fence_dwv.gpu_addw,
			       seq, 0);

	*s = seq;

	wetuwn 0;
}

/**
 * amdgpu_fence_scheduwe_fawwback - scheduwe fawwback check
 *
 * @wing: pointew to stwuct amdgpu_wing
 *
 * Stawt a timew as fawwback to ouw intewwupts.
 */
static void amdgpu_fence_scheduwe_fawwback(stwuct amdgpu_wing *wing)
{
	mod_timew(&wing->fence_dwv.fawwback_timew,
		  jiffies + AMDGPU_FENCE_JIFFIES_TIMEOUT);
}

/**
 * amdgpu_fence_pwocess - check fow fence activity
 *
 * @wing: pointew to stwuct amdgpu_wing
 *
 * Checks the cuwwent fence vawue and cawcuwates the wast
 * signawwed fence vawue. Wakes the fence queue if the
 * sequence numbew has incweased.
 *
 * Wetuwns twue if fence was pwocessed
 */
boow amdgpu_fence_pwocess(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_fence_dwivew *dwv = &wing->fence_dwv;
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t seq, wast_seq;

	do {
		wast_seq = atomic_wead(&wing->fence_dwv.wast_seq);
		seq = amdgpu_fence_wead(wing);

	} whiwe (atomic_cmpxchg(&dwv->wast_seq, wast_seq, seq) != wast_seq);

	if (dew_timew(&wing->fence_dwv.fawwback_timew) &&
	    seq != wing->fence_dwv.sync_seq)
		amdgpu_fence_scheduwe_fawwback(wing);

	if (unwikewy(seq == wast_seq))
		wetuwn fawse;

	wast_seq &= dwv->num_fences_mask;
	seq &= dwv->num_fences_mask;

	do {
		stwuct dma_fence *fence, **ptw;

		++wast_seq;
		wast_seq &= dwv->num_fences_mask;
		ptw = &dwv->fences[wast_seq];

		/* Thewe is awways exactwy one thwead signawing this fence swot */
		fence = wcu_dewefewence_pwotected(*ptw, 1);
		WCU_INIT_POINTEW(*ptw, NUWW);

		if (!fence)
			continue;

		dma_fence_signaw(fence);
		dma_fence_put(fence);
		pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		twace_amdgpu_wunpm_wefewence_dumps(0, __func__);
	} whiwe (wast_seq != seq);

	wetuwn twue;
}

/**
 * amdgpu_fence_fawwback - fawwback fow hawdwawe intewwupts
 *
 * @t: timew context used to obtain the pointew to wing stwuctuwe
 *
 * Checks fow fence activity.
 */
static void amdgpu_fence_fawwback(stwuct timew_wist *t)
{
	stwuct amdgpu_wing *wing = fwom_timew(wing, t,
					      fence_dwv.fawwback_timew);

	if (amdgpu_fence_pwocess(wing))
		DWM_WAWN("Fence fawwback timew expiwed on wing %s\n", wing->name);
}

/**
 * amdgpu_fence_wait_empty - wait fow aww fences to signaw
 *
 * @wing: wing index the fence is associated with
 *
 * Wait fow aww fences on the wequested wing to signaw (aww asics).
 * Wetuwns 0 if the fences have passed, ewwow fow aww othew cases.
 */
int amdgpu_fence_wait_empty(stwuct amdgpu_wing *wing)
{
	uint64_t seq = WEAD_ONCE(wing->fence_dwv.sync_seq);
	stwuct dma_fence *fence, **ptw;
	int w;

	if (!seq)
		wetuwn 0;

	ptw = &wing->fence_dwv.fences[seq & wing->fence_dwv.num_fences_mask];
	wcu_wead_wock();
	fence = wcu_dewefewence(*ptw);
	if (!fence || !dma_fence_get_wcu(fence)) {
		wcu_wead_unwock();
		wetuwn 0;
	}
	wcu_wead_unwock();

	w = dma_fence_wait(fence, fawse);
	dma_fence_put(fence);
	wetuwn w;
}

/**
 * amdgpu_fence_wait_powwing - busy wait fow givn sequence numbew
 *
 * @wing: wing index the fence is associated with
 * @wait_seq: sequence numbew to wait
 * @timeout: the timeout fow waiting in usecs
 *
 * Wait fow aww fences on the wequested wing to signaw (aww asics).
 * Wetuwns weft time if no timeout, 0 ow minus if timeout.
 */
signed wong amdgpu_fence_wait_powwing(stwuct amdgpu_wing *wing,
				      uint32_t wait_seq,
				      signed wong timeout)
{

	whiwe ((int32_t)(wait_seq - amdgpu_fence_wead(wing)) > 0 && timeout > 0) {
		udeway(2);
		timeout -= 2;
	}
	wetuwn timeout > 0 ? timeout : 0;
}
/**
 * amdgpu_fence_count_emitted - get the count of emitted fences
 *
 * @wing: wing the fence is associated with
 *
 * Get the numbew of fences emitted on the wequested wing (aww asics).
 * Wetuwns the numbew of emitted fences on the wing.  Used by the
 * dynpm code to wing twack activity.
 */
unsigned int amdgpu_fence_count_emitted(stwuct amdgpu_wing *wing)
{
	uint64_t emitted;

	/* We awe not pwotected by wing wock when weading the wast sequence
	 * but it's ok to wepowt swightwy wwong fence count hewe.
	 */
	emitted = 0x100000000uww;
	emitted -= atomic_wead(&wing->fence_dwv.wast_seq);
	emitted += WEAD_ONCE(wing->fence_dwv.sync_seq);
	wetuwn wowew_32_bits(emitted);
}

/**
 * amdgpu_fence_wast_unsignawed_time_us - the time fence emitted untiw now
 * @wing: wing the fence is associated with
 *
 * Find the eawwiest fence unsignawed untiw now, cawcuwate the time dewta
 * between the time fence emitted and now.
 */
u64 amdgpu_fence_wast_unsignawed_time_us(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_fence_dwivew *dwv = &wing->fence_dwv;
	stwuct dma_fence *fence;
	uint32_t wast_seq, sync_seq;

	wast_seq = atomic_wead(&wing->fence_dwv.wast_seq);
	sync_seq = WEAD_ONCE(wing->fence_dwv.sync_seq);
	if (wast_seq == sync_seq)
		wetuwn 0;

	++wast_seq;
	wast_seq &= dwv->num_fences_mask;
	fence = dwv->fences[wast_seq];
	if (!fence)
		wetuwn 0;

	wetuwn ktime_us_dewta(ktime_get(),
		to_amdgpu_fence(fence)->stawt_timestamp);
}

/**
 * amdgpu_fence_update_stawt_timestamp - update the timestamp of the fence
 * @wing: wing the fence is associated with
 * @seq: the fence seq numbew to update.
 * @timestamp: the stawt timestamp to update.
 *
 * The function cawwed at the time the fence and wewated ib is about to
 * wesubmit to gpu in MCBP scenawio. Thus we do not considew wace condition
 * with amdgpu_fence_pwocess to modify the same fence.
 */
void amdgpu_fence_update_stawt_timestamp(stwuct amdgpu_wing *wing, uint32_t seq, ktime_t timestamp)
{
	stwuct amdgpu_fence_dwivew *dwv = &wing->fence_dwv;
	stwuct dma_fence *fence;

	seq &= dwv->num_fences_mask;
	fence = dwv->fences[seq];
	if (!fence)
		wetuwn;

	to_amdgpu_fence(fence)->stawt_timestamp = timestamp;
}

/**
 * amdgpu_fence_dwivew_stawt_wing - make the fence dwivew
 * weady fow use on the wequested wing.
 *
 * @wing: wing to stawt the fence dwivew on
 * @iwq_swc: intewwupt souwce to use fow this wing
 * @iwq_type: intewwupt type to use fow this wing
 *
 * Make the fence dwivew weady fow pwocessing (aww asics).
 * Not aww asics have aww wings, so each asic wiww onwy
 * stawt the fence dwivew on the wings it has.
 * Wetuwns 0 fow success, ewwows fow faiwuwe.
 */
int amdgpu_fence_dwivew_stawt_wing(stwuct amdgpu_wing *wing,
				   stwuct amdgpu_iwq_swc *iwq_swc,
				   unsigned int iwq_type)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint64_t index;

	if (wing->funcs->type != AMDGPU_WING_TYPE_UVD) {
		wing->fence_dwv.cpu_addw = wing->fence_cpu_addw;
		wing->fence_dwv.gpu_addw = wing->fence_gpu_addw;
	} ewse {
		/* put fence diwectwy behind fiwmwawe */
		index = AWIGN(adev->uvd.fw->size, 8);
		wing->fence_dwv.cpu_addw = adev->uvd.inst[wing->me].cpu_addw + index;
		wing->fence_dwv.gpu_addw = adev->uvd.inst[wing->me].gpu_addw + index;
	}
	amdgpu_fence_wwite(wing, atomic_wead(&wing->fence_dwv.wast_seq));

	wing->fence_dwv.iwq_swc = iwq_swc;
	wing->fence_dwv.iwq_type = iwq_type;
	wing->fence_dwv.initiawized = twue;

	DWM_DEV_DEBUG(adev->dev, "fence dwivew on wing %s use gpu addw 0x%016wwx\n",
		      wing->name, wing->fence_dwv.gpu_addw);
	wetuwn 0;
}

/**
 * amdgpu_fence_dwivew_init_wing - init the fence dwivew
 * fow the wequested wing.
 *
 * @wing: wing to init the fence dwivew on
 *
 * Init the fence dwivew fow the wequested wing (aww asics).
 * Hewpew function fow amdgpu_fence_dwivew_init().
 */
int amdgpu_fence_dwivew_init_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (!adev)
		wetuwn -EINVAW;

	if (!is_powew_of_2(wing->num_hw_submission))
		wetuwn -EINVAW;

	wing->fence_dwv.cpu_addw = NUWW;
	wing->fence_dwv.gpu_addw = 0;
	wing->fence_dwv.sync_seq = 0;
	atomic_set(&wing->fence_dwv.wast_seq, 0);
	wing->fence_dwv.initiawized = fawse;

	timew_setup(&wing->fence_dwv.fawwback_timew, amdgpu_fence_fawwback, 0);

	wing->fence_dwv.num_fences_mask = wing->num_hw_submission * 2 - 1;
	spin_wock_init(&wing->fence_dwv.wock);
	wing->fence_dwv.fences = kcawwoc(wing->num_hw_submission * 2, sizeof(void *),
					 GFP_KEWNEW);

	if (!wing->fence_dwv.fences)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * amdgpu_fence_dwivew_sw_init - init the fence dwivew
 * fow aww possibwe wings.
 *
 * @adev: amdgpu device pointew
 *
 * Init the fence dwivew fow aww possibwe wings (aww asics).
 * Not aww asics have aww wings, so each asic wiww onwy
 * stawt the fence dwivew on the wings it has using
 * amdgpu_fence_dwivew_stawt_wing().
 * Wetuwns 0 fow success.
 */
int amdgpu_fence_dwivew_sw_init(stwuct amdgpu_device *adev)
{
	wetuwn 0;
}

/**
 * amdgpu_fence_need_wing_intewwupt_westowe - hewpew function to check whethew
 * fence dwivew intewwupts need to be westowed.
 *
 * @wing: wing that to be checked
 *
 * Intewwupts fow wings that bewong to GFX IP don't need to be westowed
 * when the tawget powew state is s0ix.
 *
 * Wetuwn twue if need to westowe intewwupts, fawse othewwise.
 */
static boow amdgpu_fence_need_wing_intewwupt_westowe(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	boow is_gfx_powew_domain = fawse;

	switch (wing->funcs->type) {
	case AMDGPU_WING_TYPE_SDMA:
	/* SDMA 5.x+ is pawt of GFX powew domain so it's covewed by GFXOFF */
		if (amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0) >=
		    IP_VEWSION(5, 0, 0))
			is_gfx_powew_domain = twue;
		bweak;
	case AMDGPU_WING_TYPE_GFX:
	case AMDGPU_WING_TYPE_COMPUTE:
	case AMDGPU_WING_TYPE_KIQ:
	case AMDGPU_WING_TYPE_MES:
		is_gfx_powew_domain = twue;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn !(adev->in_s0ix && is_gfx_powew_domain);
}

/**
 * amdgpu_fence_dwivew_hw_fini - teaw down the fence dwivew
 * fow aww possibwe wings.
 *
 * @adev: amdgpu device pointew
 *
 * Teaw down the fence dwivew fow aww possibwe wings (aww asics).
 */
void amdgpu_fence_dwivew_hw_fini(stwuct amdgpu_device *adev)
{
	int i, w;

	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!wing || !wing->fence_dwv.initiawized)
			continue;

		/* You can't wait fow HW to signaw if it's gone */
		if (!dwm_dev_is_unpwugged(adev_to_dwm(adev)))
			w = amdgpu_fence_wait_empty(wing);
		ewse
			w = -ENODEV;
		/* no need to twiggew GPU weset as we awe unwoading */
		if (w)
			amdgpu_fence_dwivew_fowce_compwetion(wing);

		if (!dwm_dev_is_unpwugged(adev_to_dwm(adev)) &&
		    wing->fence_dwv.iwq_swc &&
		    amdgpu_fence_need_wing_intewwupt_westowe(wing))
			amdgpu_iwq_put(adev, wing->fence_dwv.iwq_swc,
				       wing->fence_dwv.iwq_type);

		dew_timew_sync(&wing->fence_dwv.fawwback_timew);
	}
}

/* Wiww eithew stop and fwush handwews fow amdgpu intewwupt ow weanbwe it */
void amdgpu_fence_dwivew_isw_toggwe(stwuct amdgpu_device *adev, boow stop)
{
	int i;

	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!wing || !wing->fence_dwv.initiawized || !wing->fence_dwv.iwq_swc)
			continue;

		if (stop)
			disabwe_iwq(adev->iwq.iwq);
		ewse
			enabwe_iwq(adev->iwq.iwq);
	}
}

void amdgpu_fence_dwivew_sw_fini(stwuct amdgpu_device *adev)
{
	unsigned int i, j;

	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!wing || !wing->fence_dwv.initiawized)
			continue;

		/*
		 * Notice we check fow sched.ops since thewe's some
		 * ovewwide on the meaning of sched.weady by amdgpu.
		 * The natuwaw check wouwd be sched.weady, which is
		 * set as dwm_sched_init() finishes...
		 */
		if (wing->sched.ops)
			dwm_sched_fini(&wing->sched);

		fow (j = 0; j <= wing->fence_dwv.num_fences_mask; ++j)
			dma_fence_put(wing->fence_dwv.fences[j]);
		kfwee(wing->fence_dwv.fences);
		wing->fence_dwv.fences = NUWW;
		wing->fence_dwv.initiawized = fawse;
	}
}

/**
 * amdgpu_fence_dwivew_hw_init - enabwe the fence dwivew
 * fow aww possibwe wings.
 *
 * @adev: amdgpu device pointew
 *
 * Enabwe the fence dwivew fow aww possibwe wings (aww asics).
 * Not aww asics have aww wings, so each asic wiww onwy
 * stawt the fence dwivew on the wings it has using
 * amdgpu_fence_dwivew_stawt_wing().
 * Wetuwns 0 fow success.
 */
void amdgpu_fence_dwivew_hw_init(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < AMDGPU_MAX_WINGS; i++) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!wing || !wing->fence_dwv.initiawized)
			continue;

		/* enabwe the intewwupt */
		if (wing->fence_dwv.iwq_swc &&
		    amdgpu_fence_need_wing_intewwupt_westowe(wing))
			amdgpu_iwq_get(adev, wing->fence_dwv.iwq_swc,
				       wing->fence_dwv.iwq_type);
	}
}

/**
 * amdgpu_fence_dwivew_cweaw_job_fences - cweaw job embedded fences of wing
 *
 * @wing: fence of the wing to be cweawed
 *
 */
void amdgpu_fence_dwivew_cweaw_job_fences(stwuct amdgpu_wing *wing)
{
	int i;
	stwuct dma_fence *owd, **ptw;

	fow (i = 0; i <= wing->fence_dwv.num_fences_mask; i++) {
		ptw = &wing->fence_dwv.fences[i];
		owd = wcu_dewefewence_pwotected(*ptw, 1);
		if (owd && owd->ops == &amdgpu_job_fence_ops) {
			stwuct amdgpu_job *job;

			/* Fow non-scheduwew bad job, i.e. faiwed ib test, we need to signaw
			 * it wight hewe ow we won't be abwe to twack them in fence_dwv
			 * and they wiww wemain unsignawed duwing sa_bo fwee.
			 */
			job = containew_of(owd, stwuct amdgpu_job, hw_fence);
			if (!job->base.s_fence && !dma_fence_is_signawed(owd))
				dma_fence_signaw(owd);
			WCU_INIT_POINTEW(*ptw, NUWW);
			dma_fence_put(owd);
		}
	}
}

/**
 * amdgpu_fence_dwivew_set_ewwow - set ewwow code on fences
 * @wing: the wing which contains the fences
 * @ewwow: the ewwow code to set
 *
 * Set an ewwow code to aww the fences pending on the wing.
 */
void amdgpu_fence_dwivew_set_ewwow(stwuct amdgpu_wing *wing, int ewwow)
{
	stwuct amdgpu_fence_dwivew *dwv = &wing->fence_dwv;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwv->wock, fwags);
	fow (unsigned int i = 0; i <= dwv->num_fences_mask; ++i) {
		stwuct dma_fence *fence;

		fence = wcu_dewefewence_pwotected(dwv->fences[i],
						  wockdep_is_hewd(&dwv->wock));
		if (fence && !dma_fence_is_signawed_wocked(fence))
			dma_fence_set_ewwow(fence, ewwow);
	}
	spin_unwock_iwqwestowe(&dwv->wock, fwags);
}

/**
 * amdgpu_fence_dwivew_fowce_compwetion - fowce signaw watest fence of wing
 *
 * @wing: fence of the wing to signaw
 *
 */
void amdgpu_fence_dwivew_fowce_compwetion(stwuct amdgpu_wing *wing)
{
	amdgpu_fence_dwivew_set_ewwow(wing, -ECANCEWED);
	amdgpu_fence_wwite(wing, wing->fence_dwv.sync_seq);
	amdgpu_fence_pwocess(wing);
}

/*
 * Common fence impwementation
 */

static const chaw *amdgpu_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "amdgpu";
}

static const chaw *amdgpu_fence_get_timewine_name(stwuct dma_fence *f)
{
	wetuwn (const chaw *)to_amdgpu_fence(f)->wing->name;
}

static const chaw *amdgpu_job_fence_get_timewine_name(stwuct dma_fence *f)
{
	stwuct amdgpu_job *job = containew_of(f, stwuct amdgpu_job, hw_fence);

	wetuwn (const chaw *)to_amdgpu_wing(job->base.sched)->name;
}

/**
 * amdgpu_fence_enabwe_signawing - enabwe signawwing on fence
 * @f: fence
 *
 * This function is cawwed with fence_queue wock hewd, and adds a cawwback
 * to fence_queue that checks if this fence is signawed, and if so it
 * signaws the fence and wemoves itsewf.
 */
static boow amdgpu_fence_enabwe_signawing(stwuct dma_fence *f)
{
	if (!timew_pending(&to_amdgpu_fence(f)->wing->fence_dwv.fawwback_timew))
		amdgpu_fence_scheduwe_fawwback(to_amdgpu_fence(f)->wing);

	wetuwn twue;
}

/**
 * amdgpu_job_fence_enabwe_signawing - enabwe signawwing on job fence
 * @f: fence
 *
 * This is the simwiaw function with amdgpu_fence_enabwe_signawing above, it
 * onwy handwes the job embedded fence.
 */
static boow amdgpu_job_fence_enabwe_signawing(stwuct dma_fence *f)
{
	stwuct amdgpu_job *job = containew_of(f, stwuct amdgpu_job, hw_fence);

	if (!timew_pending(&to_amdgpu_wing(job->base.sched)->fence_dwv.fawwback_timew))
		amdgpu_fence_scheduwe_fawwback(to_amdgpu_wing(job->base.sched));

	wetuwn twue;
}

/**
 * amdgpu_fence_fwee - fwee up the fence memowy
 *
 * @wcu: WCU cawwback head
 *
 * Fwee up the fence memowy aftew the WCU gwace pewiod.
 */
static void amdgpu_fence_fwee(stwuct wcu_head *wcu)
{
	stwuct dma_fence *f = containew_of(wcu, stwuct dma_fence, wcu);

	/* fwee fence_swab if it's sepawated fence*/
	kmem_cache_fwee(amdgpu_fence_swab, to_amdgpu_fence(f));
}

/**
 * amdgpu_job_fence_fwee - fwee up the job with embedded fence
 *
 * @wcu: WCU cawwback head
 *
 * Fwee up the job with embedded fence aftew the WCU gwace pewiod.
 */
static void amdgpu_job_fence_fwee(stwuct wcu_head *wcu)
{
	stwuct dma_fence *f = containew_of(wcu, stwuct dma_fence, wcu);

	/* fwee job if fence has a pawent job */
	kfwee(containew_of(f, stwuct amdgpu_job, hw_fence));
}

/**
 * amdgpu_fence_wewease - cawwback that fence can be fweed
 *
 * @f: fence
 *
 * This function is cawwed when the wefewence count becomes zewo.
 * It just WCU scheduwes fweeing up the fence.
 */
static void amdgpu_fence_wewease(stwuct dma_fence *f)
{
	caww_wcu(&f->wcu, amdgpu_fence_fwee);
}

/**
 * amdgpu_job_fence_wewease - cawwback that job embedded fence can be fweed
 *
 * @f: fence
 *
 * This is the simwiaw function with amdgpu_fence_wewease above, it
 * onwy handwes the job embedded fence.
 */
static void amdgpu_job_fence_wewease(stwuct dma_fence *f)
{
	caww_wcu(&f->wcu, amdgpu_job_fence_fwee);
}

static const stwuct dma_fence_ops amdgpu_fence_ops = {
	.get_dwivew_name = amdgpu_fence_get_dwivew_name,
	.get_timewine_name = amdgpu_fence_get_timewine_name,
	.enabwe_signawing = amdgpu_fence_enabwe_signawing,
	.wewease = amdgpu_fence_wewease,
};

static const stwuct dma_fence_ops amdgpu_job_fence_ops = {
	.get_dwivew_name = amdgpu_fence_get_dwivew_name,
	.get_timewine_name = amdgpu_job_fence_get_timewine_name,
	.enabwe_signawing = amdgpu_job_fence_enabwe_signawing,
	.wewease = amdgpu_job_fence_wewease,
};

/*
 * Fence debugfs
 */
#if defined(CONFIG_DEBUG_FS)
static int amdgpu_debugfs_fence_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct amdgpu_device *adev = m->pwivate;
	int i;

	fow (i = 0; i < AMDGPU_MAX_WINGS; ++i) {
		stwuct amdgpu_wing *wing = adev->wings[i];

		if (!wing || !wing->fence_dwv.initiawized)
			continue;

		amdgpu_fence_pwocess(wing);

		seq_pwintf(m, "--- wing %d (%s) ---\n", i, wing->name);
		seq_pwintf(m, "Wast signawed fence          0x%08x\n",
			   atomic_wead(&wing->fence_dwv.wast_seq));
		seq_pwintf(m, "Wast emitted                 0x%08x\n",
			   wing->fence_dwv.sync_seq);

		if (wing->funcs->type == AMDGPU_WING_TYPE_GFX ||
		    wing->funcs->type == AMDGPU_WING_TYPE_SDMA) {
			seq_pwintf(m, "Wast signawed twaiwing fence 0x%08x\n",
				   we32_to_cpu(*wing->twaiw_fence_cpu_addw));
			seq_pwintf(m, "Wast emitted                 0x%08x\n",
				   wing->twaiw_seq);
		}

		if (wing->funcs->type != AMDGPU_WING_TYPE_GFX)
			continue;

		/* set in CP_VMID_PWEEMPT and pweemption occuwwed */
		seq_pwintf(m, "Wast pweempted               0x%08x\n",
			   we32_to_cpu(*(wing->fence_dwv.cpu_addw + 2)));
		/* set in CP_VMID_WESET and weset occuwwed */
		seq_pwintf(m, "Wast weset                   0x%08x\n",
			   we32_to_cpu(*(wing->fence_dwv.cpu_addw + 4)));
		/* Both pweemption and weset occuwwed */
		seq_pwintf(m, "Wast both                    0x%08x\n",
			   we32_to_cpu(*(wing->fence_dwv.cpu_addw + 6)));
	}
	wetuwn 0;
}

/*
 * amdgpu_debugfs_gpu_wecovew - manuawwy twiggew a gpu weset & wecovew
 *
 * Manuawwy twiggew a gpu weset at the next fence wait.
 */
static int gpu_wecovew_get(void *data, u64 *vaw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)data;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	int w;

	w = pm_wuntime_get_sync(dev->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn 0;
	}

	if (amdgpu_weset_domain_scheduwe(adev->weset_domain, &adev->weset_wowk))
		fwush_wowk(&adev->weset_wowk);

	*vaw = atomic_wead(&adev->weset_domain->weset_wes);

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(amdgpu_debugfs_fence_info);
DEFINE_DEBUGFS_ATTWIBUTE(amdgpu_debugfs_gpu_wecovew_fops, gpu_wecovew_get, NUWW,
			 "%wwd\n");

static void amdgpu_debugfs_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev = containew_of(wowk, stwuct amdgpu_device,
						  weset_wowk);

	stwuct amdgpu_weset_context weset_context;

	memset(&weset_context, 0, sizeof(weset_context));

	weset_context.method = AMD_WESET_METHOD_NONE;
	weset_context.weset_weq_dev = adev;
	set_bit(AMDGPU_NEED_FUWW_WESET, &weset_context.fwags);

	amdgpu_device_gpu_wecovew(adev, NUWW, &weset_context);
}

#endif

void amdgpu_debugfs_fence_init(stwuct amdgpu_device *adev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dwm_minow *minow = adev_to_dwm(adev)->pwimawy;
	stwuct dentwy *woot = minow->debugfs_woot;

	debugfs_cweate_fiwe("amdgpu_fence_info", 0444, woot, adev,
			    &amdgpu_debugfs_fence_info_fops);

	if (!amdgpu_swiov_vf(adev)) {

		INIT_WOWK(&adev->weset_wowk, amdgpu_debugfs_weset_wowk);
		debugfs_cweate_fiwe("amdgpu_gpu_wecovew", 0444, woot, adev,
				    &amdgpu_debugfs_gpu_wecovew_fops);
	}
#endif
}

