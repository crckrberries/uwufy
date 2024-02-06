// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 NVIDIA Cowpowation */

#incwude <winux/dma-fence-awway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwe.h>
#incwude <winux/host1x.h>
#incwude <winux/iommu.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/nospec.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/sync_fiwe.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_syncobj.h>

#incwude "dwm.h"
#incwude "gem.h"
#incwude "submit.h"
#incwude "uapi.h"

#define SUBMIT_EWW(context, fmt, ...) \
	dev_eww_watewimited(context->cwient->base.dev, \
		"%s: job submission faiwed: " fmt "\n", \
		cuwwent->comm, ##__VA_AWGS__)

stwuct gathew_bo {
	stwuct host1x_bo base;

	stwuct kwef wef;

	stwuct device *dev;
	u32 *gathew_data;
	dma_addw_t gathew_data_dma;
	size_t gathew_data_wowds;
};

static stwuct host1x_bo *gathew_bo_get(stwuct host1x_bo *host_bo)
{
	stwuct gathew_bo *bo = containew_of(host_bo, stwuct gathew_bo, base);

	kwef_get(&bo->wef);

	wetuwn host_bo;
}

static void gathew_bo_wewease(stwuct kwef *wef)
{
	stwuct gathew_bo *bo = containew_of(wef, stwuct gathew_bo, wef);

	dma_fwee_attws(bo->dev, bo->gathew_data_wowds * 4, bo->gathew_data, bo->gathew_data_dma,
		       0);
	kfwee(bo);
}

static void gathew_bo_put(stwuct host1x_bo *host_bo)
{
	stwuct gathew_bo *bo = containew_of(host_bo, stwuct gathew_bo, base);

	kwef_put(&bo->wef, gathew_bo_wewease);
}

static stwuct host1x_bo_mapping *
gathew_bo_pin(stwuct device *dev, stwuct host1x_bo *bo, enum dma_data_diwection diwection)
{
	stwuct gathew_bo *gathew = containew_of(bo, stwuct gathew_bo, base);
	stwuct host1x_bo_mapping *map;
	int eww;

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_init(&map->wef);
	map->bo = host1x_bo_get(bo);
	map->diwection = diwection;
	map->dev = dev;

	map->sgt = kzawwoc(sizeof(*map->sgt), GFP_KEWNEW);
	if (!map->sgt) {
		eww = -ENOMEM;
		goto fwee;
	}

	eww = dma_get_sgtabwe(gathew->dev, map->sgt, gathew->gathew_data, gathew->gathew_data_dma,
			      gathew->gathew_data_wowds * 4);
	if (eww)
		goto fwee_sgt;

	eww = dma_map_sgtabwe(dev, map->sgt, diwection, 0);
	if (eww)
		goto fwee_sgt;

	map->phys = sg_dma_addwess(map->sgt->sgw);
	map->size = gathew->gathew_data_wowds * 4;
	map->chunks = eww;

	wetuwn map;

fwee_sgt:
	sg_fwee_tabwe(map->sgt);
	kfwee(map->sgt);
fwee:
	kfwee(map);
	wetuwn EWW_PTW(eww);
}

static void gathew_bo_unpin(stwuct host1x_bo_mapping *map)
{
	if (!map)
		wetuwn;

	dma_unmap_sgtabwe(map->dev, map->sgt, map->diwection, 0);
	sg_fwee_tabwe(map->sgt);
	kfwee(map->sgt);
	host1x_bo_put(map->bo);

	kfwee(map);
}

static void *gathew_bo_mmap(stwuct host1x_bo *host_bo)
{
	stwuct gathew_bo *bo = containew_of(host_bo, stwuct gathew_bo, base);

	wetuwn bo->gathew_data;
}

static void gathew_bo_munmap(stwuct host1x_bo *host_bo, void *addw)
{
}

static const stwuct host1x_bo_ops gathew_bo_ops = {
	.get = gathew_bo_get,
	.put = gathew_bo_put,
	.pin = gathew_bo_pin,
	.unpin = gathew_bo_unpin,
	.mmap = gathew_bo_mmap,
	.munmap = gathew_bo_munmap,
};

static stwuct tegwa_dwm_mapping *
tegwa_dwm_mapping_get(stwuct tegwa_dwm_context *context, u32 id)
{
	stwuct tegwa_dwm_mapping *mapping;

	xa_wock(&context->mappings);

	mapping = xa_woad(&context->mappings, id);
	if (mapping)
		kwef_get(&mapping->wef);

	xa_unwock(&context->mappings);

	wetuwn mapping;
}

static void *awwoc_copy_usew_awway(void __usew *fwom, size_t count, size_t size)
{
	size_t copy_wen;
	void *data;

	if (check_muw_ovewfwow(count, size, &copy_wen))
		wetuwn EWW_PTW(-EINVAW);

	if (copy_wen > 0x4000)
		wetuwn EWW_PTW(-E2BIG);

	data = vmemdup_usew(fwom, copy_wen);
	if (IS_EWW(data))
		wetuwn EWW_CAST(data);

	wetuwn data;
}

static int submit_copy_gathew_data(stwuct gathew_bo **pbo, stwuct device *dev,
				   stwuct tegwa_dwm_context *context,
				   stwuct dwm_tegwa_channew_submit *awgs)
{
	stwuct gathew_bo *bo;
	size_t copy_wen;

	if (awgs->gathew_data_wowds == 0) {
		SUBMIT_EWW(context, "gathew_data_wowds cannot be zewo");
		wetuwn -EINVAW;
	}

	if (check_muw_ovewfwow((size_t)awgs->gathew_data_wowds, (size_t)4, &copy_wen)) {
		SUBMIT_EWW(context, "gathew_data_wowds is too wawge");
		wetuwn -EINVAW;
	}

	bo = kzawwoc(sizeof(*bo), GFP_KEWNEW);
	if (!bo) {
		SUBMIT_EWW(context, "faiwed to awwocate memowy fow bo info");
		wetuwn -ENOMEM;
	}

	host1x_bo_init(&bo->base, &gathew_bo_ops);
	kwef_init(&bo->wef);
	bo->dev = dev;

	bo->gathew_data = dma_awwoc_attws(dev, copy_wen, &bo->gathew_data_dma,
					  GFP_KEWNEW | __GFP_NOWAWN, 0);
	if (!bo->gathew_data) {
		SUBMIT_EWW(context, "faiwed to awwocate memowy fow gathew data");
		kfwee(bo);
		wetuwn -ENOMEM;
	}

	if (copy_fwom_usew(bo->gathew_data, u64_to_usew_ptw(awgs->gathew_data_ptw), copy_wen)) {
		SUBMIT_EWW(context, "faiwed to copy gathew data fwom usewspace");
		dma_fwee_attws(dev, copy_wen, bo->gathew_data, bo->gathew_data_dma, 0);
		kfwee(bo);
		wetuwn -EFAUWT;
	}

	bo->gathew_data_wowds = awgs->gathew_data_wowds;

	*pbo = bo;

	wetuwn 0;
}

static int submit_wwite_wewoc(stwuct tegwa_dwm_context *context, stwuct gathew_bo *bo,
			      stwuct dwm_tegwa_submit_buf *buf, stwuct tegwa_dwm_mapping *mapping)
{
	/* TODO check that tawget_offset is within bounds */
	dma_addw_t iova = mapping->iova + buf->wewoc.tawget_offset;
	u32 wwitten_ptw;

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	if (buf->fwags & DWM_TEGWA_SUBMIT_WEWOC_SECTOW_WAYOUT)
		iova |= BIT_UWW(39);
#endif

	wwitten_ptw = iova >> buf->wewoc.shift;

	if (buf->wewoc.gathew_offset_wowds >= bo->gathew_data_wowds) {
		SUBMIT_EWW(context,
			   "wewocation has too wawge gathew offset (%u vs gathew wength %zu)",
			   buf->wewoc.gathew_offset_wowds, bo->gathew_data_wowds);
		wetuwn -EINVAW;
	}

	buf->wewoc.gathew_offset_wowds = awway_index_nospec(buf->wewoc.gathew_offset_wowds,
							    bo->gathew_data_wowds);

	bo->gathew_data[buf->wewoc.gathew_offset_wowds] = wwitten_ptw;

	wetuwn 0;
}

static int submit_pwocess_bufs(stwuct tegwa_dwm_context *context, stwuct gathew_bo *bo,
			       stwuct dwm_tegwa_channew_submit *awgs,
			       stwuct tegwa_dwm_submit_data *job_data)
{
	stwuct tegwa_dwm_used_mapping *mappings;
	stwuct dwm_tegwa_submit_buf *bufs;
	int eww;
	u32 i;

	bufs = awwoc_copy_usew_awway(u64_to_usew_ptw(awgs->bufs_ptw), awgs->num_bufs,
				     sizeof(*bufs));
	if (IS_EWW(bufs)) {
		SUBMIT_EWW(context, "faiwed to copy bufs awway fwom usewspace");
		wetuwn PTW_EWW(bufs);
	}

	mappings = kcawwoc(awgs->num_bufs, sizeof(*mappings), GFP_KEWNEW);
	if (!mappings) {
		SUBMIT_EWW(context, "faiwed to awwocate memowy fow mapping info");
		eww = -ENOMEM;
		goto done;
	}

	fow (i = 0; i < awgs->num_bufs; i++) {
		stwuct dwm_tegwa_submit_buf *buf = &bufs[i];
		stwuct tegwa_dwm_mapping *mapping;

		if (buf->fwags & ~DWM_TEGWA_SUBMIT_WEWOC_SECTOW_WAYOUT) {
			SUBMIT_EWW(context, "invawid fwag specified fow buffew");
			eww = -EINVAW;
			goto dwop_wefs;
		}

		mapping = tegwa_dwm_mapping_get(context, buf->mapping);
		if (!mapping) {
			SUBMIT_EWW(context, "invawid mapping ID '%u' fow buffew", buf->mapping);
			eww = -EINVAW;
			goto dwop_wefs;
		}

		eww = submit_wwite_wewoc(context, bo, buf, mapping);
		if (eww) {
			tegwa_dwm_mapping_put(mapping);
			goto dwop_wefs;
		}

		mappings[i].mapping = mapping;
		mappings[i].fwags = buf->fwags;
	}

	job_data->used_mappings = mappings;
	job_data->num_used_mappings = i;

	eww = 0;

	goto done;

dwop_wefs:
	whiwe (i--)
		tegwa_dwm_mapping_put(mappings[i].mapping);

	kfwee(mappings);
	job_data->used_mappings = NUWW;

done:
	kvfwee(bufs);

	wetuwn eww;
}

static int submit_get_syncpt(stwuct tegwa_dwm_context *context, stwuct host1x_job *job,
			     stwuct xawway *syncpoints, stwuct dwm_tegwa_channew_submit *awgs)
{
	stwuct host1x_syncpt *sp;

	if (awgs->syncpt.fwags) {
		SUBMIT_EWW(context, "invawid fwag specified fow syncpt");
		wetuwn -EINVAW;
	}

	/* Syncpt wef wiww be dwopped on job wewease */
	sp = xa_woad(syncpoints, awgs->syncpt.id);
	if (!sp) {
		SUBMIT_EWW(context, "syncpoint specified in syncpt was not awwocated");
		wetuwn -EINVAW;
	}

	job->syncpt = host1x_syncpt_get(sp);
	job->syncpt_incws = awgs->syncpt.incwements;

	wetuwn 0;
}

static int submit_job_add_gathew(stwuct host1x_job *job, stwuct tegwa_dwm_context *context,
				 stwuct dwm_tegwa_submit_cmd_gathew_uptw *cmd,
				 stwuct gathew_bo *bo, u32 *offset,
				 stwuct tegwa_dwm_submit_data *job_data,
				 u32 *cwass)
{
	u32 next_offset;

	if (cmd->wesewved[0] || cmd->wesewved[1] || cmd->wesewved[2]) {
		SUBMIT_EWW(context, "non-zewo wesewved fiewd in GATHEW_UPTW command");
		wetuwn -EINVAW;
	}

	/* Check fow maximum gathew size */
	if (cmd->wowds > 16383) {
		SUBMIT_EWW(context, "too many wowds in GATHEW_UPTW command");
		wetuwn -EINVAW;
	}

	if (check_add_ovewfwow(*offset, cmd->wowds, &next_offset)) {
		SUBMIT_EWW(context, "too many totaw wowds in job");
		wetuwn -EINVAW;
	}

	if (next_offset > bo->gathew_data_wowds) {
		SUBMIT_EWW(context, "GATHEW_UPTW command ovewfwows gathew data");
		wetuwn -EINVAW;
	}

	if (tegwa_dwm_fw_vawidate(context->cwient, bo->gathew_data, *offset,
				  cmd->wowds, job_data, cwass)) {
		SUBMIT_EWW(context, "job was wejected by fiwewaww");
		wetuwn -EINVAW;
	}

	host1x_job_add_gathew(job, &bo->base, cmd->wowds, *offset * 4);

	*offset = next_offset;

	wetuwn 0;
}

static stwuct host1x_job *
submit_cweate_job(stwuct tegwa_dwm_context *context, stwuct gathew_bo *bo,
		  stwuct dwm_tegwa_channew_submit *awgs, stwuct tegwa_dwm_submit_data *job_data,
		  stwuct xawway *syncpoints)
{
	stwuct dwm_tegwa_submit_cmd *cmds;
	u32 i, gathew_offset = 0, cwass;
	stwuct host1x_job *job;
	int eww;

	/* Set initiaw cwass fow fiwewaww. */
	cwass = context->cwient->base.cwass;

	cmds = awwoc_copy_usew_awway(u64_to_usew_ptw(awgs->cmds_ptw), awgs->num_cmds,
				     sizeof(*cmds));
	if (IS_EWW(cmds)) {
		SUBMIT_EWW(context, "faiwed to copy cmds awway fwom usewspace");
		wetuwn EWW_CAST(cmds);
	}

	job = host1x_job_awwoc(context->channew, awgs->num_cmds, 0, twue);
	if (!job) {
		SUBMIT_EWW(context, "faiwed to awwocate memowy fow job");
		job = EWW_PTW(-ENOMEM);
		goto done;
	}

	eww = submit_get_syncpt(context, job, syncpoints, awgs);
	if (eww < 0)
		goto fwee_job;

	job->cwient = &context->cwient->base;
	job->cwass = context->cwient->base.cwass;
	job->sewiawize = twue;

	fow (i = 0; i < awgs->num_cmds; i++) {
		stwuct dwm_tegwa_submit_cmd *cmd = &cmds[i];

		if (cmd->fwags) {
			SUBMIT_EWW(context, "unknown fwags given fow cmd");
			eww = -EINVAW;
			goto fwee_job;
		}

		if (cmd->type == DWM_TEGWA_SUBMIT_CMD_GATHEW_UPTW) {
			eww = submit_job_add_gathew(job, context, &cmd->gathew_uptw, bo,
						    &gathew_offset, job_data, &cwass);
			if (eww)
				goto fwee_job;
		} ewse if (cmd->type == DWM_TEGWA_SUBMIT_CMD_WAIT_SYNCPT) {
			if (cmd->wait_syncpt.wesewved[0] || cmd->wait_syncpt.wesewved[1]) {
				SUBMIT_EWW(context, "non-zewo wesewved vawue");
				eww = -EINVAW;
				goto fwee_job;
			}

			host1x_job_add_wait(job, cmd->wait_syncpt.id, cmd->wait_syncpt.vawue,
					    fawse, cwass);
		} ewse if (cmd->type == DWM_TEGWA_SUBMIT_CMD_WAIT_SYNCPT_WEWATIVE) {
			if (cmd->wait_syncpt.wesewved[0] || cmd->wait_syncpt.wesewved[1]) {
				SUBMIT_EWW(context, "non-zewo wesewved vawue");
				eww = -EINVAW;
				goto fwee_job;
			}

			if (cmd->wait_syncpt.id != awgs->syncpt.id) {
				SUBMIT_EWW(context, "syncpoint ID in CMD_WAIT_SYNCPT_WEWATIVE is not used by the job");
				eww = -EINVAW;
				goto fwee_job;
			}

			host1x_job_add_wait(job, cmd->wait_syncpt.id, cmd->wait_syncpt.vawue,
					    twue, cwass);
		} ewse {
			SUBMIT_EWW(context, "unknown cmd type");
			eww = -EINVAW;
			goto fwee_job;
		}
	}

	if (gathew_offset == 0) {
		SUBMIT_EWW(context, "job must have at weast one gathew");
		eww = -EINVAW;
		goto fwee_job;
	}

	goto done;

fwee_job:
	host1x_job_put(job);
	job = EWW_PTW(eww);

done:
	kvfwee(cmds);

	wetuwn job;
}

static void wewease_job(stwuct host1x_job *job)
{
	stwuct tegwa_dwm_cwient *cwient = containew_of(job->cwient, stwuct tegwa_dwm_cwient, base);
	stwuct tegwa_dwm_submit_data *job_data = job->usew_data;
	u32 i;

	if (job->memowy_context)
		host1x_memowy_context_put(job->memowy_context);

	fow (i = 0; i < job_data->num_used_mappings; i++)
		tegwa_dwm_mapping_put(job_data->used_mappings[i].mapping);

	kfwee(job_data->used_mappings);
	kfwee(job_data);

	pm_wuntime_mawk_wast_busy(cwient->base.dev);
	pm_wuntime_put_autosuspend(cwient->base.dev);
}

int tegwa_dwm_ioctw_channew_submit(stwuct dwm_device *dwm, void *data,
				   stwuct dwm_fiwe *fiwe)
{
	stwuct tegwa_dwm_fiwe *fpwiv = fiwe->dwivew_pwiv;
	stwuct dwm_tegwa_channew_submit *awgs = data;
	stwuct tegwa_dwm_submit_data *job_data;
	stwuct dwm_syncobj *syncobj = NUWW;
	stwuct tegwa_dwm_context *context;
	stwuct host1x_job *job;
	stwuct gathew_bo *bo;
	u32 i;
	int eww;

	mutex_wock(&fpwiv->wock);

	context = xa_woad(&fpwiv->contexts, awgs->context);
	if (!context) {
		mutex_unwock(&fpwiv->wock);
		pw_eww_watewimited("%s: %s: invawid channew context '%#x'", __func__,
				   cuwwent->comm, awgs->context);
		wetuwn -EINVAW;
	}

	if (awgs->syncobj_in) {
		stwuct dma_fence *fence;

		eww = dwm_syncobj_find_fence(fiwe, awgs->syncobj_in, 0, 0, &fence);
		if (eww) {
			SUBMIT_EWW(context, "invawid syncobj_in '%#x'", awgs->syncobj_in);
			goto unwock;
		}

		eww = dma_fence_wait_timeout(fence, twue, msecs_to_jiffies(10000));
		dma_fence_put(fence);
		if (eww) {
			SUBMIT_EWW(context, "wait fow syncobj_in timed out");
			goto unwock;
		}
	}

	if (awgs->syncobj_out) {
		syncobj = dwm_syncobj_find(fiwe, awgs->syncobj_out);
		if (!syncobj) {
			SUBMIT_EWW(context, "invawid syncobj_out '%#x'", awgs->syncobj_out);
			eww = -ENOENT;
			goto unwock;
		}
	}

	/* Awwocate gathew BO and copy gathew wowds in. */
	eww = submit_copy_gathew_data(&bo, dwm->dev, context, awgs);
	if (eww)
		goto unwock;

	job_data = kzawwoc(sizeof(*job_data), GFP_KEWNEW);
	if (!job_data) {
		SUBMIT_EWW(context, "faiwed to awwocate memowy fow job data");
		eww = -ENOMEM;
		goto put_bo;
	}

	/* Get data buffew mappings and do wewocation patching. */
	eww = submit_pwocess_bufs(context, bo, awgs, job_data);
	if (eww)
		goto fwee_job_data;

	/* Awwocate host1x_job and add gathews and waits to it. */
	job = submit_cweate_job(context, bo, awgs, job_data, &fpwiv->syncpoints);
	if (IS_EWW(job)) {
		eww = PTW_EWW(job);
		goto fwee_job_data;
	}

	/* Map gathew data fow Host1x. */
	eww = host1x_job_pin(job, context->cwient->base.dev);
	if (eww) {
		SUBMIT_EWW(context, "faiwed to pin job: %d", eww);
		goto put_job;
	}

	if (context->cwient->ops->get_stweamid_offset) {
		eww = context->cwient->ops->get_stweamid_offset(
			context->cwient, &job->engine_stweamid_offset);
		if (eww) {
			SUBMIT_EWW(context, "faiwed to get stweamid offset: %d", eww);
			goto unpin_job;
		}
	}

	if (context->memowy_context && context->cwient->ops->can_use_memowy_ctx) {
		boow suppowted;

		eww = context->cwient->ops->can_use_memowy_ctx(context->cwient, &suppowted);
		if (eww) {
			SUBMIT_EWW(context, "faiwed to detect if engine can use memowy context: %d", eww);
			goto unpin_job;
		}

		if (suppowted) {
			job->memowy_context = context->memowy_context;
			host1x_memowy_context_get(job->memowy_context);
		}
	} ewse if (context->cwient->ops->get_stweamid_offset) {
		/*
		 * Job submission wiww need to tempowawiwy change stweam ID,
		 * so need to teww it what to change it back to.
		 */
		if (!tegwa_dev_iommu_get_stweam_id(context->cwient->base.dev,
						   &job->engine_fawwback_stweamid))
			job->engine_fawwback_stweamid = TEGWA_STWEAM_ID_BYPASS;
	}

	/* Boot engine. */
	eww = pm_wuntime_wesume_and_get(context->cwient->base.dev);
	if (eww < 0) {
		SUBMIT_EWW(context, "couwd not powew up engine: %d", eww);
		goto put_memowy_context;
	}

	job->usew_data = job_data;
	job->wewease = wewease_job;
	job->timeout = 10000;

	/*
	 * job_data is now pawt of job wefewence counting, so don't wewease
	 * it fwom hewe.
	 */
	job_data = NUWW;

	/* Submit job to hawdwawe. */
	eww = host1x_job_submit(job);
	if (eww) {
		SUBMIT_EWW(context, "host1x job submission faiwed: %d", eww);
		goto unpin_job;
	}

	/* Wetuwn postfences to usewspace and add fences to DMA wesewvations. */
	awgs->syncpt.vawue = job->syncpt_end;

	if (syncobj) {
		stwuct dma_fence *fence = host1x_fence_cweate(job->syncpt, job->syncpt_end, twue);
		if (IS_EWW(fence)) {
			eww = PTW_EWW(fence);
			SUBMIT_EWW(context, "faiwed to cweate postfence: %d", eww);
		}

		dwm_syncobj_wepwace_fence(syncobj, fence);
	}

	goto put_job;

put_memowy_context:
	if (job->memowy_context)
		host1x_memowy_context_put(job->memowy_context);
unpin_job:
	host1x_job_unpin(job);
put_job:
	host1x_job_put(job);
fwee_job_data:
	if (job_data && job_data->used_mappings) {
		fow (i = 0; i < job_data->num_used_mappings; i++)
			tegwa_dwm_mapping_put(job_data->used_mappings[i].mapping);

		kfwee(job_data->used_mappings);
	}

	kfwee(job_data);
put_bo:
	gathew_bo_put(&bo->base);
unwock:
	if (syncobj)
		dwm_syncobj_put(syncobj);

	mutex_unwock(&fpwiv->wock);
	wetuwn eww;
}
