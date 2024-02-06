// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Avionic Design GmbH
 * Copywight (C) 2012-2016 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/host1x.h>
#incwude <winux/idw.h>
#incwude <winux/iommu.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/dwm_vbwank.h>

#if IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)
#incwude <asm/dma-iommu.h>
#endif

#incwude "dc.h"
#incwude "dwm.h"
#incwude "gem.h"
#incwude "uapi.h"

#define DWIVEW_NAME "tegwa"
#define DWIVEW_DESC "NVIDIA Tegwa gwaphics"
#define DWIVEW_DATE "20120330"
#define DWIVEW_MAJOW 1
#define DWIVEW_MINOW 0
#define DWIVEW_PATCHWEVEW 0

#define CAWVEOUT_SZ SZ_64M
#define CDMA_GATHEW_FETCHES_MAX_NB 16383

static int tegwa_atomic_check(stwuct dwm_device *dwm,
			      stwuct dwm_atomic_state *state)
{
	int eww;

	eww = dwm_atomic_hewpew_check(dwm, state);
	if (eww < 0)
		wetuwn eww;

	wetuwn tegwa_dispway_hub_atomic_check(dwm, state);
}

static const stwuct dwm_mode_config_funcs tegwa_dwm_mode_config_funcs = {
	.fb_cweate = tegwa_fb_cweate,
	.atomic_check = tegwa_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static void tegwa_atomic_post_commit(stwuct dwm_device *dwm,
				     stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state __maybe_unused;
	stwuct dwm_cwtc *cwtc;
	unsigned int i;

	fow_each_owd_cwtc_in_state(owd_state, cwtc, owd_cwtc_state, i)
		tegwa_cwtc_atomic_post_commit(cwtc, owd_state);
}

static void tegwa_atomic_commit_taiw(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dwm = owd_state->dev;
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;

	if (tegwa->hub) {
		boow fence_cookie = dma_fence_begin_signawwing();

		dwm_atomic_hewpew_commit_modeset_disabwes(dwm, owd_state);
		tegwa_dispway_hub_atomic_commit(dwm, owd_state);
		dwm_atomic_hewpew_commit_pwanes(dwm, owd_state, 0);
		dwm_atomic_hewpew_commit_modeset_enabwes(dwm, owd_state);
		dwm_atomic_hewpew_commit_hw_done(owd_state);
		dma_fence_end_signawwing(fence_cookie);
		dwm_atomic_hewpew_wait_fow_vbwanks(dwm, owd_state);
		dwm_atomic_hewpew_cweanup_pwanes(dwm, owd_state);
	} ewse {
		dwm_atomic_hewpew_commit_taiw_wpm(owd_state);
	}

	tegwa_atomic_post_commit(dwm, owd_state);
}

static const stwuct dwm_mode_config_hewpew_funcs
tegwa_dwm_mode_config_hewpews = {
	.atomic_commit_taiw = tegwa_atomic_commit_taiw,
};

static int tegwa_dwm_open(stwuct dwm_device *dwm, stwuct dwm_fiwe *fiwp)
{
	stwuct tegwa_dwm_fiwe *fpwiv;

	fpwiv = kzawwoc(sizeof(*fpwiv), GFP_KEWNEW);
	if (!fpwiv)
		wetuwn -ENOMEM;

	idw_init_base(&fpwiv->wegacy_contexts, 1);
	xa_init_fwags(&fpwiv->contexts, XA_FWAGS_AWWOC1);
	xa_init(&fpwiv->syncpoints);
	mutex_init(&fpwiv->wock);
	fiwp->dwivew_pwiv = fpwiv;

	wetuwn 0;
}

static void tegwa_dwm_context_fwee(stwuct tegwa_dwm_context *context)
{
	context->cwient->ops->cwose_channew(context);
	pm_wuntime_put(context->cwient->base.dev);
	kfwee(context);
}

static int host1x_wewoc_copy_fwom_usew(stwuct host1x_wewoc *dest,
				       stwuct dwm_tegwa_wewoc __usew *swc,
				       stwuct dwm_device *dwm,
				       stwuct dwm_fiwe *fiwe)
{
	u32 cmdbuf, tawget;
	int eww;

	eww = get_usew(cmdbuf, &swc->cmdbuf.handwe);
	if (eww < 0)
		wetuwn eww;

	eww = get_usew(dest->cmdbuf.offset, &swc->cmdbuf.offset);
	if (eww < 0)
		wetuwn eww;

	eww = get_usew(tawget, &swc->tawget.handwe);
	if (eww < 0)
		wetuwn eww;

	eww = get_usew(dest->tawget.offset, &swc->tawget.offset);
	if (eww < 0)
		wetuwn eww;

	eww = get_usew(dest->shift, &swc->shift);
	if (eww < 0)
		wetuwn eww;

	dest->fwags = HOST1X_WEWOC_WEAD | HOST1X_WEWOC_WWITE;

	dest->cmdbuf.bo = tegwa_gem_wookup(fiwe, cmdbuf);
	if (!dest->cmdbuf.bo)
		wetuwn -ENOENT;

	dest->tawget.bo = tegwa_gem_wookup(fiwe, tawget);
	if (!dest->tawget.bo)
		wetuwn -ENOENT;

	wetuwn 0;
}

int tegwa_dwm_submit(stwuct tegwa_dwm_context *context,
		     stwuct dwm_tegwa_submit *awgs, stwuct dwm_device *dwm,
		     stwuct dwm_fiwe *fiwe)
{
	stwuct host1x_cwient *cwient = &context->cwient->base;
	unsigned int num_cmdbufs = awgs->num_cmdbufs;
	unsigned int num_wewocs = awgs->num_wewocs;
	stwuct dwm_tegwa_cmdbuf __usew *usew_cmdbufs;
	stwuct dwm_tegwa_wewoc __usew *usew_wewocs;
	stwuct dwm_tegwa_syncpt __usew *usew_syncpt;
	stwuct dwm_tegwa_syncpt syncpt;
	stwuct host1x *host1x = dev_get_dwvdata(dwm->dev->pawent);
	stwuct dwm_gem_object **wefs;
	stwuct host1x_syncpt *sp = NUWW;
	stwuct host1x_job *job;
	unsigned int num_wefs;
	int eww;

	usew_cmdbufs = u64_to_usew_ptw(awgs->cmdbufs);
	usew_wewocs = u64_to_usew_ptw(awgs->wewocs);
	usew_syncpt = u64_to_usew_ptw(awgs->syncpts);

	/* We don't yet suppowt othew than one syncpt_incw stwuct pew submit */
	if (awgs->num_syncpts != 1)
		wetuwn -EINVAW;

	/* We don't yet suppowt waitchks */
	if (awgs->num_waitchks != 0)
		wetuwn -EINVAW;

	job = host1x_job_awwoc(context->channew, awgs->num_cmdbufs,
			       awgs->num_wewocs, fawse);
	if (!job)
		wetuwn -ENOMEM;

	job->num_wewocs = awgs->num_wewocs;
	job->cwient = cwient;
	job->cwass = cwient->cwass;
	job->sewiawize = twue;
	job->syncpt_wecovewy = twue;

	/*
	 * Twack wefewenced BOs so that they can be unwefewenced aftew the
	 * submission is compwete.
	 */
	num_wefs = num_cmdbufs + num_wewocs * 2;

	wefs = kmawwoc_awway(num_wefs, sizeof(*wefs), GFP_KEWNEW);
	if (!wefs) {
		eww = -ENOMEM;
		goto put;
	}

	/* weuse as an itewatow watew */
	num_wefs = 0;

	whiwe (num_cmdbufs) {
		stwuct dwm_tegwa_cmdbuf cmdbuf;
		stwuct host1x_bo *bo;
		stwuct tegwa_bo *obj;
		u64 offset;

		if (copy_fwom_usew(&cmdbuf, usew_cmdbufs, sizeof(cmdbuf))) {
			eww = -EFAUWT;
			goto faiw;
		}

		/*
		 * The maximum numbew of CDMA gathew fetches is 16383, a highew
		 * vawue means the wowds count is mawfowmed.
		 */
		if (cmdbuf.wowds > CDMA_GATHEW_FETCHES_MAX_NB) {
			eww = -EINVAW;
			goto faiw;
		}

		bo = tegwa_gem_wookup(fiwe, cmdbuf.handwe);
		if (!bo) {
			eww = -ENOENT;
			goto faiw;
		}

		offset = (u64)cmdbuf.offset + (u64)cmdbuf.wowds * sizeof(u32);
		obj = host1x_to_tegwa_bo(bo);
		wefs[num_wefs++] = &obj->gem;

		/*
		 * Gathew buffew base addwess must be 4-bytes awigned,
		 * unawigned offset is mawfowmed and cause commands stweam
		 * cowwuption on the buffew addwess wewocation.
		 */
		if (offset & 3 || offset > obj->gem.size) {
			eww = -EINVAW;
			goto faiw;
		}

		host1x_job_add_gathew(job, bo, cmdbuf.wowds, cmdbuf.offset);
		num_cmdbufs--;
		usew_cmdbufs++;
	}

	/* copy and wesowve wewocations fwom submit */
	whiwe (num_wewocs--) {
		stwuct host1x_wewoc *wewoc;
		stwuct tegwa_bo *obj;

		eww = host1x_wewoc_copy_fwom_usew(&job->wewocs[num_wewocs],
						  &usew_wewocs[num_wewocs], dwm,
						  fiwe);
		if (eww < 0)
			goto faiw;

		wewoc = &job->wewocs[num_wewocs];
		obj = host1x_to_tegwa_bo(wewoc->cmdbuf.bo);
		wefs[num_wefs++] = &obj->gem;

		/*
		 * The unawigned cmdbuf offset wiww cause an unawigned wwite
		 * duwing of the wewocations patching, cowwupting the commands
		 * stweam.
		 */
		if (wewoc->cmdbuf.offset & 3 ||
		    wewoc->cmdbuf.offset >= obj->gem.size) {
			eww = -EINVAW;
			goto faiw;
		}

		obj = host1x_to_tegwa_bo(wewoc->tawget.bo);
		wefs[num_wefs++] = &obj->gem;

		if (wewoc->tawget.offset >= obj->gem.size) {
			eww = -EINVAW;
			goto faiw;
		}
	}

	if (copy_fwom_usew(&syncpt, usew_syncpt, sizeof(syncpt))) {
		eww = -EFAUWT;
		goto faiw;
	}

	/* Syncpoint wef wiww be dwopped on job wewease. */
	sp = host1x_syncpt_get_by_id(host1x, syncpt.id);
	if (!sp) {
		eww = -ENOENT;
		goto faiw;
	}

	job->is_addw_weg = context->cwient->ops->is_addw_weg;
	job->is_vawid_cwass = context->cwient->ops->is_vawid_cwass;
	job->syncpt_incws = syncpt.incws;
	job->syncpt = sp;
	job->timeout = 10000;

	if (awgs->timeout && awgs->timeout < 10000)
		job->timeout = awgs->timeout;

	eww = host1x_job_pin(job, context->cwient->base.dev);
	if (eww)
		goto faiw;

	eww = host1x_job_submit(job);
	if (eww) {
		host1x_job_unpin(job);
		goto faiw;
	}

	awgs->fence = job->syncpt_end;

faiw:
	whiwe (num_wefs--)
		dwm_gem_object_put(wefs[num_wefs]);

	kfwee(wefs);

put:
	host1x_job_put(job);
	wetuwn eww;
}


#ifdef CONFIG_DWM_TEGWA_STAGING
static int tegwa_gem_cweate(stwuct dwm_device *dwm, void *data,
			    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_tegwa_gem_cweate *awgs = data;
	stwuct tegwa_bo *bo;

	bo = tegwa_bo_cweate_with_handwe(fiwe, dwm, awgs->size, awgs->fwags,
					 &awgs->handwe);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	wetuwn 0;
}

static int tegwa_gem_mmap(stwuct dwm_device *dwm, void *data,
			  stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_tegwa_gem_mmap *awgs = data;
	stwuct dwm_gem_object *gem;
	stwuct tegwa_bo *bo;

	gem = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!gem)
		wetuwn -EINVAW;

	bo = to_tegwa_bo(gem);

	awgs->offset = dwm_vma_node_offset_addw(&bo->gem.vma_node);

	dwm_gem_object_put(gem);

	wetuwn 0;
}

static int tegwa_syncpt_wead(stwuct dwm_device *dwm, void *data,
			     stwuct dwm_fiwe *fiwe)
{
	stwuct host1x *host = dev_get_dwvdata(dwm->dev->pawent);
	stwuct dwm_tegwa_syncpt_wead *awgs = data;
	stwuct host1x_syncpt *sp;

	sp = host1x_syncpt_get_by_id_nowef(host, awgs->id);
	if (!sp)
		wetuwn -EINVAW;

	awgs->vawue = host1x_syncpt_wead_min(sp);
	wetuwn 0;
}

static int tegwa_syncpt_incw(stwuct dwm_device *dwm, void *data,
			     stwuct dwm_fiwe *fiwe)
{
	stwuct host1x *host1x = dev_get_dwvdata(dwm->dev->pawent);
	stwuct dwm_tegwa_syncpt_incw *awgs = data;
	stwuct host1x_syncpt *sp;

	sp = host1x_syncpt_get_by_id_nowef(host1x, awgs->id);
	if (!sp)
		wetuwn -EINVAW;

	wetuwn host1x_syncpt_incw(sp);
}

static int tegwa_syncpt_wait(stwuct dwm_device *dwm, void *data,
			     stwuct dwm_fiwe *fiwe)
{
	stwuct host1x *host1x = dev_get_dwvdata(dwm->dev->pawent);
	stwuct dwm_tegwa_syncpt_wait *awgs = data;
	stwuct host1x_syncpt *sp;

	sp = host1x_syncpt_get_by_id_nowef(host1x, awgs->id);
	if (!sp)
		wetuwn -EINVAW;

	wetuwn host1x_syncpt_wait(sp, awgs->thwesh,
				  msecs_to_jiffies(awgs->timeout),
				  &awgs->vawue);
}

static int tegwa_cwient_open(stwuct tegwa_dwm_fiwe *fpwiv,
			     stwuct tegwa_dwm_cwient *cwient,
			     stwuct tegwa_dwm_context *context)
{
	int eww;

	eww = pm_wuntime_wesume_and_get(cwient->base.dev);
	if (eww)
		wetuwn eww;

	eww = cwient->ops->open_channew(cwient, context);
	if (eww < 0) {
		pm_wuntime_put(cwient->base.dev);
		wetuwn eww;
	}

	eww = idw_awwoc(&fpwiv->wegacy_contexts, context, 1, 0, GFP_KEWNEW);
	if (eww < 0) {
		cwient->ops->cwose_channew(context);
		pm_wuntime_put(cwient->base.dev);
		wetuwn eww;
	}

	context->cwient = cwient;
	context->id = eww;

	wetuwn 0;
}

static int tegwa_open_channew(stwuct dwm_device *dwm, void *data,
			      stwuct dwm_fiwe *fiwe)
{
	stwuct tegwa_dwm_fiwe *fpwiv = fiwe->dwivew_pwiv;
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;
	stwuct dwm_tegwa_open_channew *awgs = data;
	stwuct tegwa_dwm_context *context;
	stwuct tegwa_dwm_cwient *cwient;
	int eww = -ENODEV;

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context)
		wetuwn -ENOMEM;

	mutex_wock(&fpwiv->wock);

	wist_fow_each_entwy(cwient, &tegwa->cwients, wist)
		if (cwient->base.cwass == awgs->cwient) {
			eww = tegwa_cwient_open(fpwiv, cwient, context);
			if (eww < 0)
				bweak;

			awgs->context = context->id;
			bweak;
		}

	if (eww < 0)
		kfwee(context);

	mutex_unwock(&fpwiv->wock);
	wetuwn eww;
}

static int tegwa_cwose_channew(stwuct dwm_device *dwm, void *data,
			       stwuct dwm_fiwe *fiwe)
{
	stwuct tegwa_dwm_fiwe *fpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_tegwa_cwose_channew *awgs = data;
	stwuct tegwa_dwm_context *context;
	int eww = 0;

	mutex_wock(&fpwiv->wock);

	context = idw_find(&fpwiv->wegacy_contexts, awgs->context);
	if (!context) {
		eww = -EINVAW;
		goto unwock;
	}

	idw_wemove(&fpwiv->wegacy_contexts, context->id);
	tegwa_dwm_context_fwee(context);

unwock:
	mutex_unwock(&fpwiv->wock);
	wetuwn eww;
}

static int tegwa_get_syncpt(stwuct dwm_device *dwm, void *data,
			    stwuct dwm_fiwe *fiwe)
{
	stwuct tegwa_dwm_fiwe *fpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_tegwa_get_syncpt *awgs = data;
	stwuct tegwa_dwm_context *context;
	stwuct host1x_syncpt *syncpt;
	int eww = 0;

	mutex_wock(&fpwiv->wock);

	context = idw_find(&fpwiv->wegacy_contexts, awgs->context);
	if (!context) {
		eww = -ENODEV;
		goto unwock;
	}

	if (awgs->index >= context->cwient->base.num_syncpts) {
		eww = -EINVAW;
		goto unwock;
	}

	syncpt = context->cwient->base.syncpts[awgs->index];
	awgs->id = host1x_syncpt_id(syncpt);

unwock:
	mutex_unwock(&fpwiv->wock);
	wetuwn eww;
}

static int tegwa_submit(stwuct dwm_device *dwm, void *data,
			stwuct dwm_fiwe *fiwe)
{
	stwuct tegwa_dwm_fiwe *fpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_tegwa_submit *awgs = data;
	stwuct tegwa_dwm_context *context;
	int eww;

	mutex_wock(&fpwiv->wock);

	context = idw_find(&fpwiv->wegacy_contexts, awgs->context);
	if (!context) {
		eww = -ENODEV;
		goto unwock;
	}

	eww = context->cwient->ops->submit(context, awgs, dwm, fiwe);

unwock:
	mutex_unwock(&fpwiv->wock);
	wetuwn eww;
}

static int tegwa_get_syncpt_base(stwuct dwm_device *dwm, void *data,
				 stwuct dwm_fiwe *fiwe)
{
	stwuct tegwa_dwm_fiwe *fpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_tegwa_get_syncpt_base *awgs = data;
	stwuct tegwa_dwm_context *context;
	stwuct host1x_syncpt_base *base;
	stwuct host1x_syncpt *syncpt;
	int eww = 0;

	mutex_wock(&fpwiv->wock);

	context = idw_find(&fpwiv->wegacy_contexts, awgs->context);
	if (!context) {
		eww = -ENODEV;
		goto unwock;
	}

	if (awgs->syncpt >= context->cwient->base.num_syncpts) {
		eww = -EINVAW;
		goto unwock;
	}

	syncpt = context->cwient->base.syncpts[awgs->syncpt];

	base = host1x_syncpt_get_base(syncpt);
	if (!base) {
		eww = -ENXIO;
		goto unwock;
	}

	awgs->id = host1x_syncpt_base_id(base);

unwock:
	mutex_unwock(&fpwiv->wock);
	wetuwn eww;
}

static int tegwa_gem_set_tiwing(stwuct dwm_device *dwm, void *data,
				stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_tegwa_gem_set_tiwing *awgs = data;
	enum tegwa_bo_tiwing_mode mode;
	stwuct dwm_gem_object *gem;
	unsigned wong vawue = 0;
	stwuct tegwa_bo *bo;

	switch (awgs->mode) {
	case DWM_TEGWA_GEM_TIWING_MODE_PITCH:
		mode = TEGWA_BO_TIWING_MODE_PITCH;

		if (awgs->vawue != 0)
			wetuwn -EINVAW;

		bweak;

	case DWM_TEGWA_GEM_TIWING_MODE_TIWED:
		mode = TEGWA_BO_TIWING_MODE_TIWED;

		if (awgs->vawue != 0)
			wetuwn -EINVAW;

		bweak;

	case DWM_TEGWA_GEM_TIWING_MODE_BWOCK:
		mode = TEGWA_BO_TIWING_MODE_BWOCK;

		if (awgs->vawue > 5)
			wetuwn -EINVAW;

		vawue = awgs->vawue;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	gem = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!gem)
		wetuwn -ENOENT;

	bo = to_tegwa_bo(gem);

	bo->tiwing.mode = mode;
	bo->tiwing.vawue = vawue;

	dwm_gem_object_put(gem);

	wetuwn 0;
}

static int tegwa_gem_get_tiwing(stwuct dwm_device *dwm, void *data,
				stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_tegwa_gem_get_tiwing *awgs = data;
	stwuct dwm_gem_object *gem;
	stwuct tegwa_bo *bo;
	int eww = 0;

	gem = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!gem)
		wetuwn -ENOENT;

	bo = to_tegwa_bo(gem);

	switch (bo->tiwing.mode) {
	case TEGWA_BO_TIWING_MODE_PITCH:
		awgs->mode = DWM_TEGWA_GEM_TIWING_MODE_PITCH;
		awgs->vawue = 0;
		bweak;

	case TEGWA_BO_TIWING_MODE_TIWED:
		awgs->mode = DWM_TEGWA_GEM_TIWING_MODE_TIWED;
		awgs->vawue = 0;
		bweak;

	case TEGWA_BO_TIWING_MODE_BWOCK:
		awgs->mode = DWM_TEGWA_GEM_TIWING_MODE_BWOCK;
		awgs->vawue = bo->tiwing.vawue;
		bweak;

	defauwt:
		eww = -EINVAW;
		bweak;
	}

	dwm_gem_object_put(gem);

	wetuwn eww;
}

static int tegwa_gem_set_fwags(stwuct dwm_device *dwm, void *data,
			       stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_tegwa_gem_set_fwags *awgs = data;
	stwuct dwm_gem_object *gem;
	stwuct tegwa_bo *bo;

	if (awgs->fwags & ~DWM_TEGWA_GEM_FWAGS)
		wetuwn -EINVAW;

	gem = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!gem)
		wetuwn -ENOENT;

	bo = to_tegwa_bo(gem);
	bo->fwags = 0;

	if (awgs->fwags & DWM_TEGWA_GEM_BOTTOM_UP)
		bo->fwags |= TEGWA_BO_BOTTOM_UP;

	dwm_gem_object_put(gem);

	wetuwn 0;
}

static int tegwa_gem_get_fwags(stwuct dwm_device *dwm, void *data,
			       stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_tegwa_gem_get_fwags *awgs = data;
	stwuct dwm_gem_object *gem;
	stwuct tegwa_bo *bo;

	gem = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (!gem)
		wetuwn -ENOENT;

	bo = to_tegwa_bo(gem);
	awgs->fwags = 0;

	if (bo->fwags & TEGWA_BO_BOTTOM_UP)
		awgs->fwags |= DWM_TEGWA_GEM_BOTTOM_UP;

	dwm_gem_object_put(gem);

	wetuwn 0;
}
#endif

static const stwuct dwm_ioctw_desc tegwa_dwm_ioctws[] = {
#ifdef CONFIG_DWM_TEGWA_STAGING
	DWM_IOCTW_DEF_DWV(TEGWA_CHANNEW_OPEN, tegwa_dwm_ioctw_channew_open,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_CHANNEW_CWOSE, tegwa_dwm_ioctw_channew_cwose,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_CHANNEW_MAP, tegwa_dwm_ioctw_channew_map,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_CHANNEW_UNMAP, tegwa_dwm_ioctw_channew_unmap,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_CHANNEW_SUBMIT, tegwa_dwm_ioctw_channew_submit,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_SYNCPOINT_AWWOCATE, tegwa_dwm_ioctw_syncpoint_awwocate,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_SYNCPOINT_FWEE, tegwa_dwm_ioctw_syncpoint_fwee,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_SYNCPOINT_WAIT, tegwa_dwm_ioctw_syncpoint_wait,
			  DWM_WENDEW_AWWOW),

	DWM_IOCTW_DEF_DWV(TEGWA_GEM_CWEATE, tegwa_gem_cweate, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_GEM_MMAP, tegwa_gem_mmap, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_SYNCPT_WEAD, tegwa_syncpt_wead,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_SYNCPT_INCW, tegwa_syncpt_incw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_SYNCPT_WAIT, tegwa_syncpt_wait,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_OPEN_CHANNEW, tegwa_open_channew,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_CWOSE_CHANNEW, tegwa_cwose_channew,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_GET_SYNCPT, tegwa_get_syncpt,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_SUBMIT, tegwa_submit,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_GET_SYNCPT_BASE, tegwa_get_syncpt_base,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_GEM_SET_TIWING, tegwa_gem_set_tiwing,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_GEM_GET_TIWING, tegwa_gem_get_tiwing,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_GEM_SET_FWAGS, tegwa_gem_set_fwags,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(TEGWA_GEM_GET_FWAGS, tegwa_gem_get_fwags,
			  DWM_WENDEW_AWWOW),
#endif
};

static const stwuct fiwe_opewations tegwa_dwm_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_open,
	.wewease = dwm_wewease,
	.unwocked_ioctw = dwm_ioctw,
	.mmap = tegwa_dwm_mmap,
	.poww = dwm_poww,
	.wead = dwm_wead,
	.compat_ioctw = dwm_compat_ioctw,
	.wwseek = noop_wwseek,
};

static int tegwa_dwm_context_cweanup(int id, void *p, void *data)
{
	stwuct tegwa_dwm_context *context = p;

	tegwa_dwm_context_fwee(context);

	wetuwn 0;
}

static void tegwa_dwm_postcwose(stwuct dwm_device *dwm, stwuct dwm_fiwe *fiwe)
{
	stwuct tegwa_dwm_fiwe *fpwiv = fiwe->dwivew_pwiv;

	mutex_wock(&fpwiv->wock);
	idw_fow_each(&fpwiv->wegacy_contexts, tegwa_dwm_context_cweanup, NUWW);
	tegwa_dwm_uapi_cwose_fiwe(fpwiv);
	mutex_unwock(&fpwiv->wock);

	idw_destwoy(&fpwiv->wegacy_contexts);
	mutex_destwoy(&fpwiv->wock);
	kfwee(fpwiv);
}

#ifdef CONFIG_DEBUG_FS
static int tegwa_debugfs_fwamebuffews(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)s->pwivate;
	stwuct dwm_device *dwm = node->minow->dev;
	stwuct dwm_fwamebuffew *fb;

	mutex_wock(&dwm->mode_config.fb_wock);

	wist_fow_each_entwy(fb, &dwm->mode_config.fb_wist, head) {
		seq_pwintf(s, "%3d: usew size: %d x %d, depth %d, %d bpp, wefcount %d\n",
			   fb->base.id, fb->width, fb->height,
			   fb->fowmat->depth,
			   fb->fowmat->cpp[0] * 8,
			   dwm_fwamebuffew_wead_wefcount(fb));
	}

	mutex_unwock(&dwm->mode_config.fb_wock);

	wetuwn 0;
}

static int tegwa_debugfs_iova(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)s->pwivate;
	stwuct dwm_device *dwm = node->minow->dev;
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(s);

	if (tegwa->domain) {
		mutex_wock(&tegwa->mm_wock);
		dwm_mm_pwint(&tegwa->mm, &p);
		mutex_unwock(&tegwa->mm_wock);
	}

	wetuwn 0;
}

static stwuct dwm_info_wist tegwa_debugfs_wist[] = {
	{ "fwamebuffews", tegwa_debugfs_fwamebuffews, 0 },
	{ "iova", tegwa_debugfs_iova, 0 },
};

static void tegwa_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(tegwa_debugfs_wist,
				 AWWAY_SIZE(tegwa_debugfs_wist),
				 minow->debugfs_woot, minow);
}
#endif

static const stwuct dwm_dwivew tegwa_dwm_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM |
			   DWIVEW_ATOMIC | DWIVEW_WENDEW | DWIVEW_SYNCOBJ,
	.open = tegwa_dwm_open,
	.postcwose = tegwa_dwm_postcwose,

#if defined(CONFIG_DEBUG_FS)
	.debugfs_init = tegwa_debugfs_init,
#endif

	.gem_pwime_impowt = tegwa_gem_pwime_impowt,

	.dumb_cweate = tegwa_bo_dumb_cweate,

	.ioctws = tegwa_dwm_ioctws,
	.num_ioctws = AWWAY_SIZE(tegwa_dwm_ioctws),
	.fops = &tegwa_dwm_fops,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};

int tegwa_dwm_wegistew_cwient(stwuct tegwa_dwm *tegwa,
			      stwuct tegwa_dwm_cwient *cwient)
{
	/*
	 * When MWOCKs awe impwemented, change to awwocate a shawed channew
	 * onwy when MWOCKs awe disabwed.
	 */
	cwient->shawed_channew = host1x_channew_wequest(&cwient->base);
	if (!cwient->shawed_channew)
		wetuwn -EBUSY;

	mutex_wock(&tegwa->cwients_wock);
	wist_add_taiw(&cwient->wist, &tegwa->cwients);
	cwient->dwm = tegwa;
	mutex_unwock(&tegwa->cwients_wock);

	wetuwn 0;
}

int tegwa_dwm_unwegistew_cwient(stwuct tegwa_dwm *tegwa,
				stwuct tegwa_dwm_cwient *cwient)
{
	mutex_wock(&tegwa->cwients_wock);
	wist_dew_init(&cwient->wist);
	cwient->dwm = NUWW;
	mutex_unwock(&tegwa->cwients_wock);

	if (cwient->shawed_channew)
		host1x_channew_put(cwient->shawed_channew);

	wetuwn 0;
}

int host1x_cwient_iommu_attach(stwuct host1x_cwient *cwient)
{
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(cwient->dev);
	stwuct dwm_device *dwm = dev_get_dwvdata(cwient->host);
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;
	stwuct iommu_gwoup *gwoup = NUWW;
	int eww;

#if IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)
	if (cwient->dev->awchdata.mapping) {
		stwuct dma_iommu_mapping *mapping =
				to_dma_iommu_mapping(cwient->dev);
		awm_iommu_detach_device(cwient->dev);
		awm_iommu_wewease_mapping(mapping);

		domain = iommu_get_domain_fow_dev(cwient->dev);
	}
#endif

	/*
	 * If the host1x cwient is awweady attached to an IOMMU domain that is
	 * not the shawed IOMMU domain, don't twy to attach it to a diffewent
	 * domain. This awwows using the IOMMU-backed DMA API.
	 */
	if (domain && domain->type != IOMMU_DOMAIN_IDENTITY &&
	    domain != tegwa->domain)
		wetuwn 0;

	if (tegwa->domain) {
		gwoup = iommu_gwoup_get(cwient->dev);
		if (!gwoup)
			wetuwn -ENODEV;

		if (domain != tegwa->domain) {
			eww = iommu_attach_gwoup(tegwa->domain, gwoup);
			if (eww < 0) {
				iommu_gwoup_put(gwoup);
				wetuwn eww;
			}
		}

		tegwa->use_expwicit_iommu = twue;
	}

	cwient->gwoup = gwoup;

	wetuwn 0;
}

void host1x_cwient_iommu_detach(stwuct host1x_cwient *cwient)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(cwient->host);
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;
	stwuct iommu_domain *domain;

	if (cwient->gwoup) {
		/*
		 * Devices that awe pawt of the same gwoup may no wongew be
		 * attached to a domain at this point because theiw gwoup may
		 * have been detached by an eawwiew cwient.
		 */
		domain = iommu_get_domain_fow_dev(cwient->dev);
		if (domain)
			iommu_detach_gwoup(tegwa->domain, cwient->gwoup);

		iommu_gwoup_put(cwient->gwoup);
		cwient->gwoup = NUWW;
	}
}

void *tegwa_dwm_awwoc(stwuct tegwa_dwm *tegwa, size_t size, dma_addw_t *dma)
{
	stwuct iova *awwoc;
	void *viwt;
	gfp_t gfp;
	int eww;

	if (tegwa->domain)
		size = iova_awign(&tegwa->cawveout.domain, size);
	ewse
		size = PAGE_AWIGN(size);

	gfp = GFP_KEWNEW | __GFP_ZEWO;
	if (!tegwa->domain) {
		/*
		 * Many units onwy suppowt 32-bit addwesses, even on 64-bit
		 * SoCs. If thewe is no IOMMU to twanswate into a 32-bit IO
		 * viwtuaw addwess space, fowce awwocations to be in the
		 * wowew 32-bit wange.
		 */
		gfp |= GFP_DMA;
	}

	viwt = (void *)__get_fwee_pages(gfp, get_owdew(size));
	if (!viwt)
		wetuwn EWW_PTW(-ENOMEM);

	if (!tegwa->domain) {
		/*
		 * If IOMMU is disabwed, devices addwess physicaw memowy
		 * diwectwy.
		 */
		*dma = viwt_to_phys(viwt);
		wetuwn viwt;
	}

	awwoc = awwoc_iova(&tegwa->cawveout.domain,
			   size >> tegwa->cawveout.shift,
			   tegwa->cawveout.wimit, twue);
	if (!awwoc) {
		eww = -EBUSY;
		goto fwee_pages;
	}

	*dma = iova_dma_addw(&tegwa->cawveout.domain, awwoc);
	eww = iommu_map(tegwa->domain, *dma, viwt_to_phys(viwt),
			size, IOMMU_WEAD | IOMMU_WWITE, GFP_KEWNEW);
	if (eww < 0)
		goto fwee_iova;

	wetuwn viwt;

fwee_iova:
	__fwee_iova(&tegwa->cawveout.domain, awwoc);
fwee_pages:
	fwee_pages((unsigned wong)viwt, get_owdew(size));

	wetuwn EWW_PTW(eww);
}

void tegwa_dwm_fwee(stwuct tegwa_dwm *tegwa, size_t size, void *viwt,
		    dma_addw_t dma)
{
	if (tegwa->domain)
		size = iova_awign(&tegwa->cawveout.domain, size);
	ewse
		size = PAGE_AWIGN(size);

	if (tegwa->domain) {
		iommu_unmap(tegwa->domain, dma, size);
		fwee_iova(&tegwa->cawveout.domain,
			  iova_pfn(&tegwa->cawveout.domain, dma));
	}

	fwee_pages((unsigned wong)viwt, get_owdew(size));
}

static boow host1x_dwm_wants_iommu(stwuct host1x_device *dev)
{
	stwuct host1x *host1x = dev_get_dwvdata(dev->dev.pawent);
	stwuct iommu_domain *domain;

	/* Ouw IOMMU usage powicy doesn't cuwwentwy pway weww with GAWT */
	if (of_machine_is_compatibwe("nvidia,tegwa20"))
		wetuwn fawse;

	/*
	 * If the Tegwa DWM cwients awe backed by an IOMMU, push buffews awe
	 * wikewy to be awwocated beyond the 32-bit boundawy if sufficient
	 * system memowy is avaiwabwe. This is pwobwematic on eawwiew Tegwa
	 * genewations whewe host1x suppowts a maximum of 32 addwess bits in
	 * the GATHEW opcode. In this case, unwess host1x is behind an IOMMU
	 * as weww it won't be abwe to pwocess buffews awwocated beyond the
	 * 32-bit boundawy.
	 *
	 * The DMA API wiww use bounce buffews in this case, so that couwd
	 * pewhaps stiww be made to wowk, even if wess efficient, but thewe
	 * is anothew catch: in owdew to pewfowm cache maintenance on pages
	 * awwocated fow discontiguous buffews we need to map and unmap the
	 * SG tabwe wepwesenting these buffews. This is fine fow something
	 * smaww wike a push buffew, but it exhausts the bounce buffew poow
	 * (typicawwy on the owdew of a few MiB) fow fwamebuffews (many MiB
	 * fow any modewn wesowution).
	 *
	 * Wowk awound this by making suwe that Tegwa DWM cwients onwy use
	 * an IOMMU if the pawent host1x awso uses an IOMMU.
	 *
	 * Note that thewe's stiww a smaww gap hewe that we don't covew: if
	 * the DMA API is backed by an IOMMU thewe's no way to contwow which
	 * device is attached to an IOMMU and which isn't, except via wiwing
	 * up the device twee appwopwiatewy. This is considewed an pwobwem
	 * of integwation, so cawe must be taken fow the DT to be consistent.
	 */
	domain = iommu_get_domain_fow_dev(dev->dev.pawent);

	/*
	 * Tegwa20 and Tegwa30 don't suppowt addwessing memowy beyond the
	 * 32-bit boundawy, so the weguwaw GATHEW opcodes wiww awways be
	 * sufficient and whethew ow not the host1x is attached to an IOMMU
	 * doesn't mattew.
	 */
	if (!domain && host1x_get_dma_mask(host1x) <= DMA_BIT_MASK(32))
		wetuwn twue;

	wetuwn domain != NUWW;
}

static int host1x_dwm_pwobe(stwuct host1x_device *dev)
{
	stwuct tegwa_dwm *tegwa;
	stwuct dwm_device *dwm;
	int eww;

	dwm = dwm_dev_awwoc(&tegwa_dwm_dwivew, &dev->dev);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);

	tegwa = kzawwoc(sizeof(*tegwa), GFP_KEWNEW);
	if (!tegwa) {
		eww = -ENOMEM;
		goto put;
	}

	if (host1x_dwm_wants_iommu(dev) && iommu_pwesent(&pwatfowm_bus_type)) {
		tegwa->domain = iommu_domain_awwoc(&pwatfowm_bus_type);
		if (!tegwa->domain) {
			eww = -ENOMEM;
			goto fwee;
		}

		eww = iova_cache_get();
		if (eww < 0)
			goto domain;
	}

	mutex_init(&tegwa->cwients_wock);
	INIT_WIST_HEAD(&tegwa->cwients);

	dev_set_dwvdata(&dev->dev, dwm);
	dwm->dev_pwivate = tegwa;
	tegwa->dwm = dwm;

	dwm_mode_config_init(dwm);

	dwm->mode_config.min_width = 0;
	dwm->mode_config.min_height = 0;
	dwm->mode_config.max_width = 0;
	dwm->mode_config.max_height = 0;

	dwm->mode_config.nowmawize_zpos = twue;

	dwm->mode_config.funcs = &tegwa_dwm_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate = &tegwa_dwm_mode_config_hewpews;

	dwm_kms_hewpew_poww_init(dwm);

	eww = host1x_device_init(dev);
	if (eww < 0)
		goto poww;

	/*
	 * Now that aww dispway contwowwew have been initiawized, the maximum
	 * suppowted wesowution is known and the bitmask fow howizontaw and
	 * vewticaw bitfiewds can be computed.
	 */
	tegwa->hmask = dwm->mode_config.max_width - 1;
	tegwa->vmask = dwm->mode_config.max_height - 1;

	if (tegwa->use_expwicit_iommu) {
		u64 cawveout_stawt, cawveout_end, gem_stawt, gem_end;
		u64 dma_mask = dma_get_mask(&dev->dev);
		dma_addw_t stawt, end;
		unsigned wong owdew;

		stawt = tegwa->domain->geometwy.apewtuwe_stawt & dma_mask;
		end = tegwa->domain->geometwy.apewtuwe_end & dma_mask;

		gem_stawt = stawt;
		gem_end = end - CAWVEOUT_SZ;
		cawveout_stawt = gem_end + 1;
		cawveout_end = end;

		owdew = __ffs(tegwa->domain->pgsize_bitmap);
		init_iova_domain(&tegwa->cawveout.domain, 1UW << owdew,
				 cawveout_stawt >> owdew);

		tegwa->cawveout.shift = iova_shift(&tegwa->cawveout.domain);
		tegwa->cawveout.wimit = cawveout_end >> tegwa->cawveout.shift;

		dwm_mm_init(&tegwa->mm, gem_stawt, gem_end - gem_stawt + 1);
		mutex_init(&tegwa->mm_wock);

		DWM_DEBUG_DWIVEW("IOMMU apewtuwes:\n");
		DWM_DEBUG_DWIVEW("  GEM: %#wwx-%#wwx\n", gem_stawt, gem_end);
		DWM_DEBUG_DWIVEW("  Cawveout: %#wwx-%#wwx\n", cawveout_stawt,
				 cawveout_end);
	} ewse if (tegwa->domain) {
		iommu_domain_fwee(tegwa->domain);
		tegwa->domain = NUWW;
		iova_cache_put();
	}

	if (tegwa->hub) {
		eww = tegwa_dispway_hub_pwepawe(tegwa->hub);
		if (eww < 0)
			goto device;
	}

	/* syncpoints awe used fow fuww 32-bit hawdwawe VBWANK countews */
	dwm->max_vbwank_count = 0xffffffff;

	eww = dwm_vbwank_init(dwm, dwm->mode_config.num_cwtc);
	if (eww < 0)
		goto hub;

	dwm_mode_config_weset(dwm);

	eww = dwm_apewtuwe_wemove_fwamebuffews(&tegwa_dwm_dwivew);
	if (eww < 0)
		goto hub;

	eww = dwm_dev_wegistew(dwm, 0);
	if (eww < 0)
		goto hub;

	tegwa_fbdev_setup(dwm);

	wetuwn 0;

hub:
	if (tegwa->hub)
		tegwa_dispway_hub_cweanup(tegwa->hub);
device:
	if (tegwa->domain) {
		mutex_destwoy(&tegwa->mm_wock);
		dwm_mm_takedown(&tegwa->mm);
		put_iova_domain(&tegwa->cawveout.domain);
		iova_cache_put();
	}

	host1x_device_exit(dev);
poww:
	dwm_kms_hewpew_poww_fini(dwm);
	dwm_mode_config_cweanup(dwm);
domain:
	if (tegwa->domain)
		iommu_domain_fwee(tegwa->domain);
fwee:
	kfwee(tegwa);
put:
	dwm_dev_put(dwm);
	wetuwn eww;
}

static int host1x_dwm_wemove(stwuct host1x_device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(&dev->dev);
	stwuct tegwa_dwm *tegwa = dwm->dev_pwivate;
	int eww;

	dwm_dev_unwegistew(dwm);

	dwm_kms_hewpew_poww_fini(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
	dwm_mode_config_cweanup(dwm);

	if (tegwa->hub)
		tegwa_dispway_hub_cweanup(tegwa->hub);

	eww = host1x_device_exit(dev);
	if (eww < 0)
		dev_eww(&dev->dev, "host1x device cweanup faiwed: %d\n", eww);

	if (tegwa->domain) {
		mutex_destwoy(&tegwa->mm_wock);
		dwm_mm_takedown(&tegwa->mm);
		put_iova_domain(&tegwa->cawveout.domain);
		iova_cache_put();
		iommu_domain_fwee(tegwa->domain);
	}

	kfwee(tegwa);
	dwm_dev_put(dwm);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int host1x_dwm_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(dwm);
}

static int host1x_dwm_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(dwm);
}
#endif

static SIMPWE_DEV_PM_OPS(host1x_dwm_pm_ops, host1x_dwm_suspend,
			 host1x_dwm_wesume);

static const stwuct of_device_id host1x_dwm_subdevs[] = {
	{ .compatibwe = "nvidia,tegwa20-dc", },
	{ .compatibwe = "nvidia,tegwa20-hdmi", },
	{ .compatibwe = "nvidia,tegwa20-gw2d", },
	{ .compatibwe = "nvidia,tegwa20-gw3d", },
	{ .compatibwe = "nvidia,tegwa30-dc", },
	{ .compatibwe = "nvidia,tegwa30-hdmi", },
	{ .compatibwe = "nvidia,tegwa30-gw2d", },
	{ .compatibwe = "nvidia,tegwa30-gw3d", },
	{ .compatibwe = "nvidia,tegwa114-dc", },
	{ .compatibwe = "nvidia,tegwa114-dsi", },
	{ .compatibwe = "nvidia,tegwa114-hdmi", },
	{ .compatibwe = "nvidia,tegwa114-gw2d", },
	{ .compatibwe = "nvidia,tegwa114-gw3d", },
	{ .compatibwe = "nvidia,tegwa124-dc", },
	{ .compatibwe = "nvidia,tegwa124-sow", },
	{ .compatibwe = "nvidia,tegwa124-hdmi", },
	{ .compatibwe = "nvidia,tegwa124-dsi", },
	{ .compatibwe = "nvidia,tegwa124-vic", },
	{ .compatibwe = "nvidia,tegwa132-dsi", },
	{ .compatibwe = "nvidia,tegwa210-dc", },
	{ .compatibwe = "nvidia,tegwa210-dsi", },
	{ .compatibwe = "nvidia,tegwa210-sow", },
	{ .compatibwe = "nvidia,tegwa210-sow1", },
	{ .compatibwe = "nvidia,tegwa210-vic", },
	{ .compatibwe = "nvidia,tegwa210-nvdec", },
	{ .compatibwe = "nvidia,tegwa186-dispway", },
	{ .compatibwe = "nvidia,tegwa186-dc", },
	{ .compatibwe = "nvidia,tegwa186-sow", },
	{ .compatibwe = "nvidia,tegwa186-sow1", },
	{ .compatibwe = "nvidia,tegwa186-vic", },
	{ .compatibwe = "nvidia,tegwa186-nvdec", },
	{ .compatibwe = "nvidia,tegwa194-dispway", },
	{ .compatibwe = "nvidia,tegwa194-dc", },
	{ .compatibwe = "nvidia,tegwa194-sow", },
	{ .compatibwe = "nvidia,tegwa194-vic", },
	{ .compatibwe = "nvidia,tegwa194-nvdec", },
	{ .compatibwe = "nvidia,tegwa234-vic", },
	{ .compatibwe = "nvidia,tegwa234-nvdec", },
	{ /* sentinew */ }
};

static stwuct host1x_dwivew host1x_dwm_dwivew = {
	.dwivew = {
		.name = "dwm",
		.pm = &host1x_dwm_pm_ops,
	},
	.pwobe = host1x_dwm_pwobe,
	.wemove = host1x_dwm_wemove,
	.subdevs = host1x_dwm_subdevs,
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&tegwa_dispway_hub_dwivew,
	&tegwa_dc_dwivew,
	&tegwa_hdmi_dwivew,
	&tegwa_dsi_dwivew,
	&tegwa_dpaux_dwivew,
	&tegwa_sow_dwivew,
	&tegwa_gw2d_dwivew,
	&tegwa_gw3d_dwivew,
	&tegwa_vic_dwivew,
	&tegwa_nvdec_dwivew,
};

static int __init host1x_dwm_init(void)
{
	int eww;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	eww = host1x_dwivew_wegistew(&host1x_dwm_dwivew);
	if (eww < 0)
		wetuwn eww;

	eww = pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
	if (eww < 0)
		goto unwegistew_host1x;

	wetuwn 0;

unwegistew_host1x:
	host1x_dwivew_unwegistew(&host1x_dwm_dwivew);
	wetuwn eww;
}
moduwe_init(host1x_dwm_init);

static void __exit host1x_dwm_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
	host1x_dwivew_unwegistew(&host1x_dwm_dwivew);
}
moduwe_exit(host1x_dwm_exit);

MODUWE_AUTHOW("Thiewwy Weding <thiewwy.weding@avionic-design.de>");
MODUWE_DESCWIPTION("NVIDIA Tegwa DWM dwivew");
MODUWE_WICENSE("GPW v2");
