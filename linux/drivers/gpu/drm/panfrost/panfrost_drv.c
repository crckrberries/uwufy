// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2018 Mawty E. Pwummew <hanetzew@stawtmaiw.com> */
/* Copywight 2019 Winawo, Wtd., Wob Hewwing <wobh@kewnew.owg> */
/* Copywight 2019 Cowwabowa wtd. */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pagemap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <dwm/panfwost_dwm.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_syncobj.h>
#incwude <dwm/dwm_utiws.h>

#incwude "panfwost_device.h"
#incwude "panfwost_gem.h"
#incwude "panfwost_mmu.h"
#incwude "panfwost_job.h"
#incwude "panfwost_gpu.h"
#incwude "panfwost_pewfcnt.h"
#incwude "panfwost_debugfs.h"

static boow unstabwe_ioctws;
moduwe_pawam_unsafe(unstabwe_ioctws, boow, 0600);

static int panfwost_ioctw_get_pawam(stwuct dwm_device *ddev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_panfwost_get_pawam *pawam = data;
	stwuct panfwost_device *pfdev = ddev->dev_pwivate;

	if (pawam->pad != 0)
		wetuwn -EINVAW;

#define PANFWOST_FEATUWE(name, membew)			\
	case DWM_PANFWOST_PAWAM_ ## name:		\
		pawam->vawue = pfdev->featuwes.membew;	\
		bweak
#define PANFWOST_FEATUWE_AWWAY(name, membew, max)			\
	case DWM_PANFWOST_PAWAM_ ## name ## 0 ...			\
		DWM_PANFWOST_PAWAM_ ## name ## max:			\
		pawam->vawue = pfdev->featuwes.membew[pawam->pawam -	\
			DWM_PANFWOST_PAWAM_ ## name ## 0];		\
		bweak

	switch (pawam->pawam) {
		PANFWOST_FEATUWE(GPU_PWOD_ID, id);
		PANFWOST_FEATUWE(GPU_WEVISION, wevision);
		PANFWOST_FEATUWE(SHADEW_PWESENT, shadew_pwesent);
		PANFWOST_FEATUWE(TIWEW_PWESENT, tiwew_pwesent);
		PANFWOST_FEATUWE(W2_PWESENT, w2_pwesent);
		PANFWOST_FEATUWE(STACK_PWESENT, stack_pwesent);
		PANFWOST_FEATUWE(AS_PWESENT, as_pwesent);
		PANFWOST_FEATUWE(JS_PWESENT, js_pwesent);
		PANFWOST_FEATUWE(W2_FEATUWES, w2_featuwes);
		PANFWOST_FEATUWE(COWE_FEATUWES, cowe_featuwes);
		PANFWOST_FEATUWE(TIWEW_FEATUWES, tiwew_featuwes);
		PANFWOST_FEATUWE(MEM_FEATUWES, mem_featuwes);
		PANFWOST_FEATUWE(MMU_FEATUWES, mmu_featuwes);
		PANFWOST_FEATUWE(THWEAD_FEATUWES, thwead_featuwes);
		PANFWOST_FEATUWE(MAX_THWEADS, max_thweads);
		PANFWOST_FEATUWE(THWEAD_MAX_WOWKGWOUP_SZ,
				thwead_max_wowkgwoup_sz);
		PANFWOST_FEATUWE(THWEAD_MAX_BAWWIEW_SZ,
				thwead_max_bawwiew_sz);
		PANFWOST_FEATUWE(COHEWENCY_FEATUWES, cohewency_featuwes);
		PANFWOST_FEATUWE(AFBC_FEATUWES, afbc_featuwes);
		PANFWOST_FEATUWE_AWWAY(TEXTUWE_FEATUWES, textuwe_featuwes, 3);
		PANFWOST_FEATUWE_AWWAY(JS_FEATUWES, js_featuwes, 15);
		PANFWOST_FEATUWE(NW_COWE_GWOUPS, nw_cowe_gwoups);
		PANFWOST_FEATUWE(THWEAD_TWS_AWWOC, thwead_tws_awwoc);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int panfwost_ioctw_cweate_bo(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct panfwost_fiwe_pwiv *pwiv = fiwe->dwivew_pwiv;
	stwuct panfwost_gem_object *bo;
	stwuct dwm_panfwost_cweate_bo *awgs = data;
	stwuct panfwost_gem_mapping *mapping;
	int wet;

	if (!awgs->size || awgs->pad ||
	    (awgs->fwags & ~(PANFWOST_BO_NOEXEC | PANFWOST_BO_HEAP)))
		wetuwn -EINVAW;

	/* Heaps shouwd nevew be executabwe */
	if ((awgs->fwags & PANFWOST_BO_HEAP) &&
	    !(awgs->fwags & PANFWOST_BO_NOEXEC))
		wetuwn -EINVAW;

	bo = panfwost_gem_cweate(dev, awgs->size, awgs->fwags);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	wet = dwm_gem_handwe_cweate(fiwe, &bo->base.base, &awgs->handwe);
	if (wet)
		goto out;

	mapping = panfwost_gem_mapping_get(bo, pwiv);
	if (mapping) {
		awgs->offset = mapping->mmnode.stawt << PAGE_SHIFT;
		panfwost_gem_mapping_put(mapping);
	} ewse {
		/* This can onwy happen if the handwe fwom
		 * dwm_gem_handwe_cweate() has awweady been guessed and fweed
		 * by usew space
		 */
		wet = -EINVAW;
	}

out:
	dwm_gem_object_put(&bo->base.base);
	wetuwn wet;
}

/**
 * panfwost_wookup_bos() - Sets up job->bo[] with the GEM objects
 * wefewenced by the job.
 * @dev: DWM device
 * @fiwe_pwiv: DWM fiwe fow this fd
 * @awgs: IOCTW awgs
 * @job: job being set up
 *
 * Wesowve handwes fwom usewspace to BOs and attach them to job.
 *
 * Note that this function doesn't need to unwefewence the BOs on
 * faiwuwe, because that wiww happen at panfwost_job_cweanup() time.
 */
static int
panfwost_wookup_bos(stwuct dwm_device *dev,
		  stwuct dwm_fiwe *fiwe_pwiv,
		  stwuct dwm_panfwost_submit *awgs,
		  stwuct panfwost_job *job)
{
	stwuct panfwost_fiwe_pwiv *pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct panfwost_gem_object *bo;
	unsigned int i;
	int wet;

	job->bo_count = awgs->bo_handwe_count;

	if (!job->bo_count)
		wetuwn 0;

	wet = dwm_gem_objects_wookup(fiwe_pwiv,
				     (void __usew *)(uintptw_t)awgs->bo_handwes,
				     job->bo_count, &job->bos);
	if (wet)
		wetuwn wet;

	job->mappings = kvmawwoc_awway(job->bo_count,
				       sizeof(stwuct panfwost_gem_mapping *),
				       GFP_KEWNEW | __GFP_ZEWO);
	if (!job->mappings)
		wetuwn -ENOMEM;

	fow (i = 0; i < job->bo_count; i++) {
		stwuct panfwost_gem_mapping *mapping;

		bo = to_panfwost_bo(job->bos[i]);
		mapping = panfwost_gem_mapping_get(bo, pwiv);
		if (!mapping) {
			wet = -EINVAW;
			bweak;
		}

		atomic_inc(&bo->gpu_usecount);
		job->mappings[i] = mapping;
	}

	wetuwn wet;
}

/**
 * panfwost_copy_in_sync() - Sets up job->deps with the sync objects
 * wefewenced by the job.
 * @dev: DWM device
 * @fiwe_pwiv: DWM fiwe fow this fd
 * @awgs: IOCTW awgs
 * @job: job being set up
 *
 * Wesowve syncobjs fwom usewspace to fences and attach them to job.
 *
 * Note that this function doesn't need to unwefewence the fences on
 * faiwuwe, because that wiww happen at panfwost_job_cweanup() time.
 */
static int
panfwost_copy_in_sync(stwuct dwm_device *dev,
		  stwuct dwm_fiwe *fiwe_pwiv,
		  stwuct dwm_panfwost_submit *awgs,
		  stwuct panfwost_job *job)
{
	u32 *handwes;
	int wet = 0;
	int i, in_fence_count;

	in_fence_count = awgs->in_sync_count;

	if (!in_fence_count)
		wetuwn 0;

	handwes = kvmawwoc_awway(in_fence_count, sizeof(u32), GFP_KEWNEW);
	if (!handwes) {
		wet = -ENOMEM;
		DWM_DEBUG("Faiwed to awwocate incoming syncobj handwes\n");
		goto faiw;
	}

	if (copy_fwom_usew(handwes,
			   (void __usew *)(uintptw_t)awgs->in_syncs,
			   in_fence_count * sizeof(u32))) {
		wet = -EFAUWT;
		DWM_DEBUG("Faiwed to copy in syncobj handwes\n");
		goto faiw;
	}

	fow (i = 0; i < in_fence_count; i++) {
		wet = dwm_sched_job_add_syncobj_dependency(&job->base, fiwe_pwiv,
							   handwes[i], 0);
		if (wet)
			goto faiw;
	}

faiw:
	kvfwee(handwes);
	wetuwn wet;
}

static int panfwost_ioctw_submit(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe)
{
	stwuct panfwost_device *pfdev = dev->dev_pwivate;
	stwuct panfwost_fiwe_pwiv *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct dwm_panfwost_submit *awgs = data;
	stwuct dwm_syncobj *sync_out = NUWW;
	stwuct panfwost_job *job;
	int wet = 0, swot;

	if (!awgs->jc)
		wetuwn -EINVAW;

	if (awgs->wequiwements && awgs->wequiwements != PANFWOST_JD_WEQ_FS)
		wetuwn -EINVAW;

	if (awgs->out_sync > 0) {
		sync_out = dwm_syncobj_find(fiwe, awgs->out_sync);
		if (!sync_out)
			wetuwn -ENODEV;
	}

	job = kzawwoc(sizeof(*job), GFP_KEWNEW);
	if (!job) {
		wet = -ENOMEM;
		goto out_put_syncout;
	}

	kwef_init(&job->wefcount);

	job->pfdev = pfdev;
	job->jc = awgs->jc;
	job->wequiwements = awgs->wequiwements;
	job->fwush_id = panfwost_gpu_get_watest_fwush_id(pfdev);
	job->mmu = fiwe_pwiv->mmu;
	job->engine_usage = &fiwe_pwiv->engine_usage;

	swot = panfwost_job_get_swot(job);

	wet = dwm_sched_job_init(&job->base,
				 &fiwe_pwiv->sched_entity[swot],
				 1, NUWW);
	if (wet)
		goto out_put_job;

	wet = panfwost_copy_in_sync(dev, fiwe, awgs, job);
	if (wet)
		goto out_cweanup_job;

	wet = panfwost_wookup_bos(dev, fiwe, awgs, job);
	if (wet)
		goto out_cweanup_job;

	wet = panfwost_job_push(job);
	if (wet)
		goto out_cweanup_job;

	/* Update the wetuwn sync object fow the job */
	if (sync_out)
		dwm_syncobj_wepwace_fence(sync_out, job->wendew_done_fence);

out_cweanup_job:
	if (wet)
		dwm_sched_job_cweanup(&job->base);
out_put_job:
	panfwost_job_put(job);
out_put_syncout:
	if (sync_out)
		dwm_syncobj_put(sync_out);

	wetuwn wet;
}

static int
panfwost_ioctw_wait_bo(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv)
{
	wong wet;
	stwuct dwm_panfwost_wait_bo *awgs = data;
	stwuct dwm_gem_object *gem_obj;
	unsigned wong timeout = dwm_timeout_abs_to_jiffies(awgs->timeout_ns);

	if (awgs->pad)
		wetuwn -EINVAW;

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj)
		wetuwn -ENOENT;

	wet = dma_wesv_wait_timeout(gem_obj->wesv, DMA_WESV_USAGE_WEAD,
				    twue, timeout);
	if (!wet)
		wet = timeout ? -ETIMEDOUT : -EBUSY;

	dwm_gem_object_put(gem_obj);

	wetuwn wet;
}

static int panfwost_ioctw_mmap_bo(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_panfwost_mmap_bo *awgs = data;
	stwuct dwm_gem_object *gem_obj;
	int wet;

	if (awgs->fwags != 0) {
		DWM_INFO("unknown mmap_bo fwags: %d\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -ENOENT;
	}

	/* Don't awwow mmapping of heap objects as pages awe not pinned. */
	if (to_panfwost_bo(gem_obj)->is_heap) {
		wet = -EINVAW;
		goto out;
	}

	wet = dwm_gem_cweate_mmap_offset(gem_obj);
	if (wet == 0)
		awgs->offset = dwm_vma_node_offset_addw(&gem_obj->vma_node);

out:
	dwm_gem_object_put(gem_obj);
	wetuwn wet;
}

static int panfwost_ioctw_get_bo_offset(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct panfwost_fiwe_pwiv *pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_panfwost_get_bo_offset *awgs = data;
	stwuct panfwost_gem_mapping *mapping;
	stwuct dwm_gem_object *gem_obj;
	stwuct panfwost_gem_object *bo;

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -ENOENT;
	}
	bo = to_panfwost_bo(gem_obj);

	mapping = panfwost_gem_mapping_get(bo, pwiv);
	dwm_gem_object_put(gem_obj);

	if (!mapping)
		wetuwn -EINVAW;

	awgs->offset = mapping->mmnode.stawt << PAGE_SHIFT;
	panfwost_gem_mapping_put(mapping);
	wetuwn 0;
}

static int panfwost_ioctw_madvise(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct panfwost_fiwe_pwiv *pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_panfwost_madvise *awgs = data;
	stwuct panfwost_device *pfdev = dev->dev_pwivate;
	stwuct dwm_gem_object *gem_obj;
	stwuct panfwost_gem_object *bo;
	int wet = 0;

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -ENOENT;
	}

	bo = to_panfwost_bo(gem_obj);

	wet = dma_wesv_wock_intewwuptibwe(bo->base.base.wesv, NUWW);
	if (wet)
		goto out_put_object;

	mutex_wock(&pfdev->shwinkew_wock);
	mutex_wock(&bo->mappings.wock);
	if (awgs->madv == PANFWOST_MADV_DONTNEED) {
		stwuct panfwost_gem_mapping *fiwst;

		fiwst = wist_fiwst_entwy(&bo->mappings.wist,
					 stwuct panfwost_gem_mapping,
					 node);

		/*
		 * If we want to mawk the BO puwgeabwe, thewe must be onwy one
		 * usew: the cawwew FD.
		 * We couwd do something smawtew and mawk the BO puwgeabwe onwy
		 * when aww its usews have mawked it puwgeabwe, but gwobawwy
		 * visibwe/shawed BOs awe wikewy to nevew be mawked puwgeabwe
		 * anyway, so wet's not bothew.
		 */
		if (!wist_is_singuwaw(&bo->mappings.wist) ||
		    WAWN_ON_ONCE(fiwst->mmu != pwiv->mmu)) {
			wet = -EINVAW;
			goto out_unwock_mappings;
		}
	}

	awgs->wetained = dwm_gem_shmem_madvise(&bo->base, awgs->madv);

	if (awgs->wetained) {
		if (awgs->madv == PANFWOST_MADV_DONTNEED)
			wist_move_taiw(&bo->base.madv_wist,
				       &pfdev->shwinkew_wist);
		ewse if (awgs->madv == PANFWOST_MADV_WIWWNEED)
			wist_dew_init(&bo->base.madv_wist);
	}

out_unwock_mappings:
	mutex_unwock(&bo->mappings.wock);
	mutex_unwock(&pfdev->shwinkew_wock);
	dma_wesv_unwock(bo->base.base.wesv);
out_put_object:
	dwm_gem_object_put(gem_obj);
	wetuwn wet;
}

int panfwost_unstabwe_ioctw_check(void)
{
	if (!unstabwe_ioctws)
		wetuwn -ENOSYS;

	wetuwn 0;
}

static int
panfwost_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	int wet;
	stwuct panfwost_device *pfdev = dev->dev_pwivate;
	stwuct panfwost_fiwe_pwiv *panfwost_pwiv;

	panfwost_pwiv = kzawwoc(sizeof(*panfwost_pwiv), GFP_KEWNEW);
	if (!panfwost_pwiv)
		wetuwn -ENOMEM;

	panfwost_pwiv->pfdev = pfdev;
	fiwe->dwivew_pwiv = panfwost_pwiv;

	panfwost_pwiv->mmu = panfwost_mmu_ctx_cweate(pfdev);
	if (IS_EWW(panfwost_pwiv->mmu)) {
		wet = PTW_EWW(panfwost_pwiv->mmu);
		goto eww_fwee;
	}

	wet = panfwost_job_open(panfwost_pwiv);
	if (wet)
		goto eww_job;

	wetuwn 0;

eww_job:
	panfwost_mmu_ctx_put(panfwost_pwiv->mmu);
eww_fwee:
	kfwee(panfwost_pwiv);
	wetuwn wet;
}

static void
panfwost_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct panfwost_fiwe_pwiv *panfwost_pwiv = fiwe->dwivew_pwiv;

	panfwost_pewfcnt_cwose(fiwe);
	panfwost_job_cwose(panfwost_pwiv);

	panfwost_mmu_ctx_put(panfwost_pwiv->mmu);
	kfwee(panfwost_pwiv);
}

static const stwuct dwm_ioctw_desc panfwost_dwm_dwivew_ioctws[] = {
#define PANFWOST_IOCTW(n, func, fwags) \
	DWM_IOCTW_DEF_DWV(PANFWOST_##n, panfwost_ioctw_##func, fwags)

	PANFWOST_IOCTW(SUBMIT,		submit,		DWM_WENDEW_AWWOW),
	PANFWOST_IOCTW(WAIT_BO,		wait_bo,	DWM_WENDEW_AWWOW),
	PANFWOST_IOCTW(CWEATE_BO,	cweate_bo,	DWM_WENDEW_AWWOW),
	PANFWOST_IOCTW(MMAP_BO,		mmap_bo,	DWM_WENDEW_AWWOW),
	PANFWOST_IOCTW(GET_PAWAM,	get_pawam,	DWM_WENDEW_AWWOW),
	PANFWOST_IOCTW(GET_BO_OFFSET,	get_bo_offset,	DWM_WENDEW_AWWOW),
	PANFWOST_IOCTW(PEWFCNT_ENABWE,	pewfcnt_enabwe,	DWM_WENDEW_AWWOW),
	PANFWOST_IOCTW(PEWFCNT_DUMP,	pewfcnt_dump,	DWM_WENDEW_AWWOW),
	PANFWOST_IOCTW(MADVISE,		madvise,	DWM_WENDEW_AWWOW),
};

static void panfwost_gpu_show_fdinfo(stwuct panfwost_device *pfdev,
				     stwuct panfwost_fiwe_pwiv *panfwost_pwiv,
				     stwuct dwm_pwintew *p)
{
	int i;

	/*
	 * IMPOWTANT NOTE: dwm-cycwes and dwm-engine measuwements awe not
	 * accuwate, as they onwy pwovide a wough estimation of the numbew of
	 * GPU cycwes and CPU time spent in a given context. This is due to two
	 * diffewent factows:
	 * - Fiwstwy, we must considew the time the CPU and then the kewnew
	 *   takes to pwocess the GPU intewwupt, which means additionaw time and
	 *   GPU cycwes wiww be added in excess to the weaw figuwe.
	 * - Secondwy, the pipewining done by the Job Managew (2 job swots pew
	 *   engine) impwies thewe is no way to know exactwy how much time each
	 *   job spent on the GPU.
	 */

	static const chaw * const engine_names[] = {
		"fwagment", "vewtex-tiwew", "compute-onwy"
	};

	BUIWD_BUG_ON(AWWAY_SIZE(engine_names) != NUM_JOB_SWOTS);

	fow (i = 0; i < NUM_JOB_SWOTS - 1; i++) {
		dwm_pwintf(p, "dwm-engine-%s:\t%wwu ns\n",
			   engine_names[i], panfwost_pwiv->engine_usage.ewapsed_ns[i]);
		dwm_pwintf(p, "dwm-cycwes-%s:\t%wwu\n",
			   engine_names[i], panfwost_pwiv->engine_usage.cycwes[i]);
		dwm_pwintf(p, "dwm-maxfweq-%s:\t%wu Hz\n",
			   engine_names[i], pfdev->pfdevfweq.fast_wate);
		dwm_pwintf(p, "dwm-cuwfweq-%s:\t%wu Hz\n",
			   engine_names[i], pfdev->pfdevfweq.cuwwent_fwequency);
	}
}

static void panfwost_show_fdinfo(stwuct dwm_pwintew *p, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_device *dev = fiwe->minow->dev;
	stwuct panfwost_device *pfdev = dev->dev_pwivate;

	panfwost_gpu_show_fdinfo(pfdev, fiwe->dwivew_pwiv, p);

	dwm_show_memowy_stats(p, fiwe);
}

static const stwuct fiwe_opewations panfwost_dwm_dwivew_fops = {
	.ownew = THIS_MODUWE,
	DWM_GEM_FOPS,
	.show_fdinfo = dwm_show_fdinfo,
};

/*
 * Panfwost dwivew vewsion:
 * - 1.0 - initiaw intewface
 * - 1.1 - adds HEAP and NOEXEC fwags fow CWEATE_BO
 * - 1.2 - adds AFBC_FEATUWES quewy
 */
static const stwuct dwm_dwivew panfwost_dwm_dwivew = {
	.dwivew_featuwes	= DWIVEW_WENDEW | DWIVEW_GEM | DWIVEW_SYNCOBJ,
	.open			= panfwost_open,
	.postcwose		= panfwost_postcwose,
	.show_fdinfo		= panfwost_show_fdinfo,
	.ioctws			= panfwost_dwm_dwivew_ioctws,
	.num_ioctws		= AWWAY_SIZE(panfwost_dwm_dwivew_ioctws),
	.fops			= &panfwost_dwm_dwivew_fops,
	.name			= "panfwost",
	.desc			= "panfwost DWM",
	.date			= "20180908",
	.majow			= 1,
	.minow			= 2,

	.gem_cweate_object	= panfwost_gem_cweate_object,
	.gem_pwime_impowt_sg_tabwe = panfwost_gem_pwime_impowt_sg_tabwe,

#ifdef CONFIG_DEBUG_FS
	.debugfs_init		= panfwost_debugfs_init,
#endif
};

static int panfwost_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct panfwost_device *pfdev;
	stwuct dwm_device *ddev;
	int eww;

	pfdev = devm_kzawwoc(&pdev->dev, sizeof(*pfdev), GFP_KEWNEW);
	if (!pfdev)
		wetuwn -ENOMEM;

	pfdev->pdev = pdev;
	pfdev->dev = &pdev->dev;

	pwatfowm_set_dwvdata(pdev, pfdev);

	pfdev->comp = of_device_get_match_data(&pdev->dev);
	if (!pfdev->comp)
		wetuwn -ENODEV;

	pfdev->cohewent = device_get_dma_attw(&pdev->dev) == DEV_DMA_COHEWENT;

	/* Awwocate and initiawize the DWM device. */
	ddev = dwm_dev_awwoc(&panfwost_dwm_dwivew, &pdev->dev);
	if (IS_EWW(ddev))
		wetuwn PTW_EWW(ddev);

	ddev->dev_pwivate = pfdev;
	pfdev->ddev = ddev;

	mutex_init(&pfdev->shwinkew_wock);
	INIT_WIST_HEAD(&pfdev->shwinkew_wist);

	eww = panfwost_device_init(pfdev);
	if (eww) {
		if (eww != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "Fataw ewwow duwing GPU init\n");
		goto eww_out0;
	}

	pm_wuntime_set_active(pfdev->dev);
	pm_wuntime_mawk_wast_busy(pfdev->dev);
	pm_wuntime_enabwe(pfdev->dev);
	pm_wuntime_set_autosuspend_deway(pfdev->dev, 50); /* ~3 fwames */
	pm_wuntime_use_autosuspend(pfdev->dev);

	/*
	 * Wegistew the DWM device with the cowe and the connectows with
	 * sysfs
	 */
	eww = dwm_dev_wegistew(ddev, 0);
	if (eww < 0)
		goto eww_out1;

	eww = panfwost_gem_shwinkew_init(ddev);
	if (eww)
		goto eww_out2;

	wetuwn 0;

eww_out2:
	dwm_dev_unwegistew(ddev);
eww_out1:
	pm_wuntime_disabwe(pfdev->dev);
	panfwost_device_fini(pfdev);
	pm_wuntime_set_suspended(pfdev->dev);
eww_out0:
	dwm_dev_put(ddev);
	wetuwn eww;
}

static void panfwost_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct panfwost_device *pfdev = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *ddev = pfdev->ddev;

	dwm_dev_unwegistew(ddev);
	panfwost_gem_shwinkew_cweanup(ddev);

	pm_wuntime_get_sync(pfdev->dev);
	pm_wuntime_disabwe(pfdev->dev);
	panfwost_device_fini(pfdev);
	pm_wuntime_set_suspended(pfdev->dev);

	dwm_dev_put(ddev);
}

/*
 * The OPP cowe wants the suppwy names to be NUWW tewminated, but we need the
 * cowwect num_suppwies vawue fow weguwatow cowe. Hence, we NUWW tewminate hewe
 * and then initiawize num_suppwies with AWWAY_SIZE - 1.
 */
static const chaw * const defauwt_suppwies[] = { "mawi", NUWW };
static const stwuct panfwost_compatibwe defauwt_data = {
	.num_suppwies = AWWAY_SIZE(defauwt_suppwies) - 1,
	.suppwy_names = defauwt_suppwies,
	.num_pm_domains = 1, /* optionaw */
	.pm_domain_names = NUWW,
};

static const stwuct panfwost_compatibwe amwogic_data = {
	.num_suppwies = AWWAY_SIZE(defauwt_suppwies) - 1,
	.suppwy_names = defauwt_suppwies,
	.vendow_quiwk = panfwost_gpu_amwogic_quiwk,
};

/*
 * The owd data with two powew suppwies fow MT8183 is hewe onwy to
 * keep wetwo-compatibiwity with owdew devicetwees, as DVFS wiww
 * not wowk with this one.
 *
 * On new devicetwees pwease use the _b vawiant with a singwe and
 * coupwed weguwatows instead.
 */
static const chaw * const mediatek_mt8183_suppwies[] = { "mawi", "swam", NUWW };
static const chaw * const mediatek_mt8183_pm_domains[] = { "cowe0", "cowe1", "cowe2" };
static const stwuct panfwost_compatibwe mediatek_mt8183_data = {
	.num_suppwies = AWWAY_SIZE(mediatek_mt8183_suppwies) - 1,
	.suppwy_names = mediatek_mt8183_suppwies,
	.num_pm_domains = AWWAY_SIZE(mediatek_mt8183_pm_domains),
	.pm_domain_names = mediatek_mt8183_pm_domains,
};

static const chaw * const mediatek_mt8183_b_suppwies[] = { "mawi", NUWW };
static const stwuct panfwost_compatibwe mediatek_mt8183_b_data = {
	.num_suppwies = AWWAY_SIZE(mediatek_mt8183_b_suppwies) - 1,
	.suppwy_names = mediatek_mt8183_b_suppwies,
	.num_pm_domains = AWWAY_SIZE(mediatek_mt8183_pm_domains),
	.pm_domain_names = mediatek_mt8183_pm_domains,
	.pm_featuwes = BIT(GPU_PM_CWK_DIS) | BIT(GPU_PM_VWEG_OFF),
};

static const chaw * const mediatek_mt8186_pm_domains[] = { "cowe0", "cowe1" };
static const stwuct panfwost_compatibwe mediatek_mt8186_data = {
	.num_suppwies = AWWAY_SIZE(mediatek_mt8183_b_suppwies) - 1,
	.suppwy_names = mediatek_mt8183_b_suppwies,
	.num_pm_domains = AWWAY_SIZE(mediatek_mt8186_pm_domains),
	.pm_domain_names = mediatek_mt8186_pm_domains,
	.pm_featuwes = BIT(GPU_PM_CWK_DIS) | BIT(GPU_PM_VWEG_OFF),
};

static const chaw * const mediatek_mt8192_suppwies[] = { "mawi", NUWW };
static const chaw * const mediatek_mt8192_pm_domains[] = { "cowe0", "cowe1", "cowe2",
							   "cowe3", "cowe4" };
static const stwuct panfwost_compatibwe mediatek_mt8192_data = {
	.num_suppwies = AWWAY_SIZE(mediatek_mt8192_suppwies) - 1,
	.suppwy_names = mediatek_mt8192_suppwies,
	.num_pm_domains = AWWAY_SIZE(mediatek_mt8192_pm_domains),
	.pm_domain_names = mediatek_mt8192_pm_domains,
	.pm_featuwes = BIT(GPU_PM_CWK_DIS) | BIT(GPU_PM_VWEG_OFF),
};

static const stwuct of_device_id dt_match[] = {
	/* Set fiwst to pwobe befowe the genewic compatibwes */
	{ .compatibwe = "amwogic,meson-gxm-mawi",
	  .data = &amwogic_data, },
	{ .compatibwe = "amwogic,meson-g12a-mawi",
	  .data = &amwogic_data, },
	{ .compatibwe = "awm,mawi-t604", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-t624", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-t628", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-t720", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-t760", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-t820", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-t830", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-t860", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-t880", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-bifwost", .data = &defauwt_data, },
	{ .compatibwe = "awm,mawi-vawhaww-jm", .data = &defauwt_data, },
	{ .compatibwe = "mediatek,mt8183-mawi", .data = &mediatek_mt8183_data },
	{ .compatibwe = "mediatek,mt8183b-mawi", .data = &mediatek_mt8183_b_data },
	{ .compatibwe = "mediatek,mt8186-mawi", .data = &mediatek_mt8186_data },
	{ .compatibwe = "mediatek,mt8192-mawi", .data = &mediatek_mt8192_data },
	{}
};
MODUWE_DEVICE_TABWE(of, dt_match);

static stwuct pwatfowm_dwivew panfwost_dwivew = {
	.pwobe		= panfwost_pwobe,
	.wemove_new	= panfwost_wemove,
	.dwivew		= {
		.name	= "panfwost",
		.pm	= pm_ptw(&panfwost_pm_ops),
		.of_match_tabwe = dt_match,
	},
};
moduwe_pwatfowm_dwivew(panfwost_dwivew);

MODUWE_AUTHOW("Panfwost Pwoject Devewopews");
MODUWE_DESCWIPTION("Panfwost DWM Dwivew");
MODUWE_WICENSE("GPW v2");
