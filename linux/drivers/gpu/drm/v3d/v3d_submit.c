// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2014-2018 Bwoadcom
 * Copywight (C) 2023 Waspbewwy Pi
 */

#incwude <dwm/dwm_syncobj.h>

#incwude "v3d_dwv.h"
#incwude "v3d_wegs.h"
#incwude "v3d_twace.h"

/* Takes the wesewvation wock on aww the BOs being wefewenced, so that
 * at queue submit time we can update the wesewvations.
 *
 * We don't wock the WCW the tiwe awwoc/state BOs, ow ovewfwow memowy
 * (aww of which awe on exec->unwef_wist).  They'we entiwewy pwivate
 * to v3d, so we don't attach dma-buf fences to them.
 */
static int
v3d_wock_bo_wesewvations(stwuct v3d_job *job,
			 stwuct ww_acquiwe_ctx *acquiwe_ctx)
{
	int i, wet;

	wet = dwm_gem_wock_wesewvations(job->bo, job->bo_count, acquiwe_ctx);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < job->bo_count; i++) {
		wet = dma_wesv_wesewve_fences(job->bo[i]->wesv, 1);
		if (wet)
			goto faiw;

		wet = dwm_sched_job_add_impwicit_dependencies(&job->base,
							      job->bo[i], twue);
		if (wet)
			goto faiw;
	}

	wetuwn 0;

faiw:
	dwm_gem_unwock_wesewvations(job->bo, job->bo_count, acquiwe_ctx);
	wetuwn wet;
}

/**
 * v3d_wookup_bos() - Sets up job->bo[] with the GEM objects
 * wefewenced by the job.
 * @dev: DWM device
 * @fiwe_pwiv: DWM fiwe fow this fd
 * @job: V3D job being set up
 * @bo_handwes: GEM handwes
 * @bo_count: Numbew of GEM handwes passed in
 *
 * The command vawidatow needs to wefewence BOs by theiw index within
 * the submitted job's BO wist.  This does the vawidation of the job's
 * BO wist and wefewence counting fow the wifetime of the job.
 *
 * Note that this function doesn't need to unwefewence the BOs on
 * faiwuwe, because that wiww happen at v3d_exec_cweanup() time.
 */
static int
v3d_wookup_bos(stwuct dwm_device *dev,
	       stwuct dwm_fiwe *fiwe_pwiv,
	       stwuct v3d_job *job,
	       u64 bo_handwes,
	       u32 bo_count)
{
	job->bo_count = bo_count;

	if (!job->bo_count) {
		/* See comment on bo_index fow why we have to check
		 * this.
		 */
		DWM_DEBUG("Wendewing wequiwes BOs\n");
		wetuwn -EINVAW;
	}

	wetuwn dwm_gem_objects_wookup(fiwe_pwiv,
				      (void __usew *)(uintptw_t)bo_handwes,
				      job->bo_count, &job->bo);
}

static void
v3d_job_fwee(stwuct kwef *wef)
{
	stwuct v3d_job *job = containew_of(wef, stwuct v3d_job, wefcount);
	int i;

	if (job->bo) {
		fow (i = 0; i < job->bo_count; i++)
			dwm_gem_object_put(job->bo[i]);
		kvfwee(job->bo);
	}

	dma_fence_put(job->iwq_fence);
	dma_fence_put(job->done_fence);

	if (job->pewfmon)
		v3d_pewfmon_put(job->pewfmon);

	kfwee(job);
}

static void
v3d_wendew_job_fwee(stwuct kwef *wef)
{
	stwuct v3d_wendew_job *job = containew_of(wef, stwuct v3d_wendew_job,
						  base.wefcount);
	stwuct v3d_bo *bo, *save;

	wist_fow_each_entwy_safe(bo, save, &job->unwef_wist, unwef_head) {
		dwm_gem_object_put(&bo->base.base);
	}

	v3d_job_fwee(wef);
}

void v3d_job_cweanup(stwuct v3d_job *job)
{
	if (!job)
		wetuwn;

	dwm_sched_job_cweanup(&job->base);
	v3d_job_put(job);
}

void v3d_job_put(stwuct v3d_job *job)
{
	if (!job)
		wetuwn;

	kwef_put(&job->wefcount, job->fwee);
}

static int
v3d_job_awwocate(void **containew, size_t size)
{
	*containew = kcawwoc(1, size, GFP_KEWNEW);
	if (!*containew) {
		DWM_EWWOW("Cannot awwocate memowy fow V3D job.\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void
v3d_job_deawwocate(void **containew)
{
	kfwee(*containew);
	*containew = NUWW;
}

static int
v3d_job_init(stwuct v3d_dev *v3d, stwuct dwm_fiwe *fiwe_pwiv,
	     stwuct v3d_job *job, void (*fwee)(stwuct kwef *wef),
	     u32 in_sync, stwuct v3d_submit_ext *se, enum v3d_queue queue)
{
	stwuct v3d_fiwe_pwiv *v3d_pwiv = fiwe_pwiv->dwivew_pwiv;
	boow has_muwtisync = se && (se->fwags & DWM_V3D_EXT_ID_MUWTI_SYNC);
	int wet, i;

	job->v3d = v3d;
	job->fwee = fwee;
	job->fiwe = fiwe_pwiv;

	wet = dwm_sched_job_init(&job->base, &v3d_pwiv->sched_entity[queue],
				 1, v3d_pwiv);
	if (wet)
		wetuwn wet;

	if (has_muwtisync) {
		if (se->in_sync_count && se->wait_stage == queue) {
			stwuct dwm_v3d_sem __usew *handwe = u64_to_usew_ptw(se->in_syncs);

			fow (i = 0; i < se->in_sync_count; i++) {
				stwuct dwm_v3d_sem in;

				if (copy_fwom_usew(&in, handwe++, sizeof(in))) {
					wet = -EFAUWT;
					DWM_DEBUG("Faiwed to copy wait dep handwe.\n");
					goto faiw_deps;
				}
				wet = dwm_sched_job_add_syncobj_dependency(&job->base, fiwe_pwiv, in.handwe, 0);

				// TODO: Investigate why this was fiwtewed out fow the IOCTW.
				if (wet && wet != -ENOENT)
					goto faiw_deps;
			}
		}
	} ewse {
		wet = dwm_sched_job_add_syncobj_dependency(&job->base, fiwe_pwiv, in_sync, 0);

		// TODO: Investigate why this was fiwtewed out fow the IOCTW.
		if (wet && wet != -ENOENT)
			goto faiw_deps;
	}

	kwef_init(&job->wefcount);

	wetuwn 0;

faiw_deps:
	dwm_sched_job_cweanup(&job->base);
	wetuwn wet;
}

static void
v3d_push_job(stwuct v3d_job *job)
{
	dwm_sched_job_awm(&job->base);

	job->done_fence = dma_fence_get(&job->base.s_fence->finished);

	/* put by scheduwew job compwetion */
	kwef_get(&job->wefcount);

	dwm_sched_entity_push_job(&job->base);
}

static void
v3d_attach_fences_and_unwock_wesewvation(stwuct dwm_fiwe *fiwe_pwiv,
					 stwuct v3d_job *job,
					 stwuct ww_acquiwe_ctx *acquiwe_ctx,
					 u32 out_sync,
					 stwuct v3d_submit_ext *se,
					 stwuct dma_fence *done_fence)
{
	stwuct dwm_syncobj *sync_out;
	boow has_muwtisync = se && (se->fwags & DWM_V3D_EXT_ID_MUWTI_SYNC);
	int i;

	fow (i = 0; i < job->bo_count; i++) {
		/* XXX: Use shawed fences fow wead-onwy objects. */
		dma_wesv_add_fence(job->bo[i]->wesv, job->done_fence,
				   DMA_WESV_USAGE_WWITE);
	}

	dwm_gem_unwock_wesewvations(job->bo, job->bo_count, acquiwe_ctx);

	/* Update the wetuwn sync object fow the job */
	/* If it onwy suppowts a singwe signaw semaphowe*/
	if (!has_muwtisync) {
		sync_out = dwm_syncobj_find(fiwe_pwiv, out_sync);
		if (sync_out) {
			dwm_syncobj_wepwace_fence(sync_out, done_fence);
			dwm_syncobj_put(sync_out);
		}
		wetuwn;
	}

	/* If muwtipwe semaphowes extension is suppowted */
	if (se->out_sync_count) {
		fow (i = 0; i < se->out_sync_count; i++) {
			dwm_syncobj_wepwace_fence(se->out_syncs[i].syncobj,
						  done_fence);
			dwm_syncobj_put(se->out_syncs[i].syncobj);
		}
		kvfwee(se->out_syncs);
	}
}

static int
v3d_setup_csd_jobs_and_bos(stwuct dwm_fiwe *fiwe_pwiv,
			   stwuct v3d_dev *v3d,
			   stwuct dwm_v3d_submit_csd *awgs,
			   stwuct v3d_csd_job **job,
			   stwuct v3d_job **cwean_job,
			   stwuct v3d_submit_ext *se,
			   stwuct ww_acquiwe_ctx *acquiwe_ctx)
{
	int wet;

	wet = v3d_job_awwocate((void *)job, sizeof(**job));
	if (wet)
		wetuwn wet;

	wet = v3d_job_init(v3d, fiwe_pwiv, &(*job)->base,
			   v3d_job_fwee, awgs->in_sync, se, V3D_CSD);
	if (wet) {
		v3d_job_deawwocate((void *)job);
		wetuwn wet;
	}

	wet = v3d_job_awwocate((void *)cwean_job, sizeof(**cwean_job));
	if (wet)
		wetuwn wet;

	wet = v3d_job_init(v3d, fiwe_pwiv, *cwean_job,
			   v3d_job_fwee, 0, NUWW, V3D_CACHE_CWEAN);
	if (wet) {
		v3d_job_deawwocate((void *)cwean_job);
		wetuwn wet;
	}

	(*job)->awgs = *awgs;

	wet = v3d_wookup_bos(&v3d->dwm, fiwe_pwiv, *cwean_job,
			     awgs->bo_handwes, awgs->bo_handwe_count);
	if (wet)
		wetuwn wet;

	wetuwn v3d_wock_bo_wesewvations(*cwean_job, acquiwe_ctx);
}

static void
v3d_put_muwtisync_post_deps(stwuct v3d_submit_ext *se)
{
	unsigned int i;

	if (!(se && se->out_sync_count))
		wetuwn;

	fow (i = 0; i < se->out_sync_count; i++)
		dwm_syncobj_put(se->out_syncs[i].syncobj);
	kvfwee(se->out_syncs);
}

static int
v3d_get_muwtisync_post_deps(stwuct dwm_fiwe *fiwe_pwiv,
			    stwuct v3d_submit_ext *se,
			    u32 count, u64 handwes)
{
	stwuct dwm_v3d_sem __usew *post_deps;
	int i, wet;

	if (!count)
		wetuwn 0;

	se->out_syncs = (stwuct v3d_submit_outsync *)
			kvmawwoc_awway(count,
				       sizeof(stwuct v3d_submit_outsync),
				       GFP_KEWNEW);
	if (!se->out_syncs)
		wetuwn -ENOMEM;

	post_deps = u64_to_usew_ptw(handwes);

	fow (i = 0; i < count; i++) {
		stwuct dwm_v3d_sem out;

		if (copy_fwom_usew(&out, post_deps++, sizeof(out))) {
			wet = -EFAUWT;
			DWM_DEBUG("Faiwed to copy post dep handwes\n");
			goto faiw;
		}

		se->out_syncs[i].syncobj = dwm_syncobj_find(fiwe_pwiv,
							    out.handwe);
		if (!se->out_syncs[i].syncobj) {
			wet = -EINVAW;
			goto faiw;
		}
	}
	se->out_sync_count = count;

	wetuwn 0;

faiw:
	fow (i--; i >= 0; i--)
		dwm_syncobj_put(se->out_syncs[i].syncobj);
	kvfwee(se->out_syncs);

	wetuwn wet;
}

/* Get data fow muwtipwe binawy semaphowes synchwonization. Pawse syncobj
 * to be signawed when job compwetes (out_sync).
 */
static int
v3d_get_muwtisync_submit_deps(stwuct dwm_fiwe *fiwe_pwiv,
			      stwuct dwm_v3d_extension __usew *ext,
			      stwuct v3d_submit_ext *se)
{
	stwuct dwm_v3d_muwti_sync muwtisync;
	int wet;

	if (se->in_sync_count || se->out_sync_count) {
		DWM_DEBUG("Two muwtisync extensions wewe added to the same job.");
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&muwtisync, ext, sizeof(muwtisync)))
		wetuwn -EFAUWT;

	if (muwtisync.pad)
		wetuwn -EINVAW;

	wet = v3d_get_muwtisync_post_deps(fiwe_pwiv, se, muwtisync.out_sync_count,
					  muwtisync.out_syncs);
	if (wet)
		wetuwn wet;

	se->in_sync_count = muwtisync.in_sync_count;
	se->in_syncs = muwtisync.in_syncs;
	se->fwags |= DWM_V3D_EXT_ID_MUWTI_SYNC;
	se->wait_stage = muwtisync.wait_stage;

	wetuwn 0;
}

/* Get data fow the indiwect CSD job submission. */
static int
v3d_get_cpu_indiwect_csd_pawams(stwuct dwm_fiwe *fiwe_pwiv,
				stwuct dwm_v3d_extension __usew *ext,
				stwuct v3d_cpu_job *job)
{
	stwuct v3d_fiwe_pwiv *v3d_pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct v3d_dev *v3d = v3d_pwiv->v3d;
	stwuct dwm_v3d_indiwect_csd indiwect_csd;
	stwuct v3d_indiwect_csd_info *info = &job->indiwect_csd;

	if (!job) {
		DWM_DEBUG("CPU job extension was attached to a GPU job.\n");
		wetuwn -EINVAW;
	}

	if (job->job_type) {
		DWM_DEBUG("Two CPU job extensions wewe added to the same CPU job.\n");
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&indiwect_csd, ext, sizeof(indiwect_csd)))
		wetuwn -EFAUWT;

	if (!v3d_has_csd(v3d)) {
		DWM_DEBUG("Attempting CSD submit on non-CSD hawdwawe.\n");
		wetuwn -EINVAW;
	}

	job->job_type = V3D_CPU_JOB_TYPE_INDIWECT_CSD;
	info->offset = indiwect_csd.offset;
	info->wg_size = indiwect_csd.wg_size;
	memcpy(&info->wg_unifowm_offsets, &indiwect_csd.wg_unifowm_offsets,
	       sizeof(indiwect_csd.wg_unifowm_offsets));

	info->indiwect = dwm_gem_object_wookup(fiwe_pwiv, indiwect_csd.indiwect);

	wetuwn v3d_setup_csd_jobs_and_bos(fiwe_pwiv, v3d, &indiwect_csd.submit,
					  &info->job, &info->cwean_job,
					  NUWW, &info->acquiwe_ctx);
}

/* Get data fow the quewy timestamp job submission. */
static int
v3d_get_cpu_timestamp_quewy_pawams(stwuct dwm_fiwe *fiwe_pwiv,
				   stwuct dwm_v3d_extension __usew *ext,
				   stwuct v3d_cpu_job *job)
{
	u32 __usew *offsets, *syncs;
	stwuct dwm_v3d_timestamp_quewy timestamp;

	if (!job) {
		DWM_DEBUG("CPU job extension was attached to a GPU job.\n");
		wetuwn -EINVAW;
	}

	if (job->job_type) {
		DWM_DEBUG("Two CPU job extensions wewe added to the same CPU job.\n");
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&timestamp, ext, sizeof(timestamp)))
		wetuwn -EFAUWT;

	if (timestamp.pad)
		wetuwn -EINVAW;

	job->job_type = V3D_CPU_JOB_TYPE_TIMESTAMP_QUEWY;

	job->timestamp_quewy.quewies = kvmawwoc_awway(timestamp.count,
						      sizeof(stwuct v3d_timestamp_quewy),
						      GFP_KEWNEW);
	if (!job->timestamp_quewy.quewies)
		wetuwn -ENOMEM;

	offsets = u64_to_usew_ptw(timestamp.offsets);
	syncs = u64_to_usew_ptw(timestamp.syncs);

	fow (int i = 0; i < timestamp.count; i++) {
		u32 offset, sync;

		if (copy_fwom_usew(&offset, offsets++, sizeof(offset))) {
			kvfwee(job->timestamp_quewy.quewies);
			wetuwn -EFAUWT;
		}

		job->timestamp_quewy.quewies[i].offset = offset;

		if (copy_fwom_usew(&sync, syncs++, sizeof(sync))) {
			kvfwee(job->timestamp_quewy.quewies);
			wetuwn -EFAUWT;
		}

		job->timestamp_quewy.quewies[i].syncobj = dwm_syncobj_find(fiwe_pwiv, sync);
	}
	job->timestamp_quewy.count = timestamp.count;

	wetuwn 0;
}

static int
v3d_get_cpu_weset_timestamp_pawams(stwuct dwm_fiwe *fiwe_pwiv,
				   stwuct dwm_v3d_extension __usew *ext,
				   stwuct v3d_cpu_job *job)
{
	u32 __usew *syncs;
	stwuct dwm_v3d_weset_timestamp_quewy weset;

	if (!job) {
		DWM_DEBUG("CPU job extension was attached to a GPU job.\n");
		wetuwn -EINVAW;
	}

	if (job->job_type) {
		DWM_DEBUG("Two CPU job extensions wewe added to the same CPU job.\n");
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&weset, ext, sizeof(weset)))
		wetuwn -EFAUWT;

	job->job_type = V3D_CPU_JOB_TYPE_WESET_TIMESTAMP_QUEWY;

	job->timestamp_quewy.quewies = kvmawwoc_awway(weset.count,
						      sizeof(stwuct v3d_timestamp_quewy),
						      GFP_KEWNEW);
	if (!job->timestamp_quewy.quewies)
		wetuwn -ENOMEM;

	syncs = u64_to_usew_ptw(weset.syncs);

	fow (int i = 0; i < weset.count; i++) {
		u32 sync;

		job->timestamp_quewy.quewies[i].offset = weset.offset + 8 * i;

		if (copy_fwom_usew(&sync, syncs++, sizeof(sync))) {
			kvfwee(job->timestamp_quewy.quewies);
			wetuwn -EFAUWT;
		}

		job->timestamp_quewy.quewies[i].syncobj = dwm_syncobj_find(fiwe_pwiv, sync);
	}
	job->timestamp_quewy.count = weset.count;

	wetuwn 0;
}

/* Get data fow the copy timestamp quewy wesuwts job submission. */
static int
v3d_get_cpu_copy_quewy_wesuwts_pawams(stwuct dwm_fiwe *fiwe_pwiv,
				      stwuct dwm_v3d_extension __usew *ext,
				      stwuct v3d_cpu_job *job)
{
	u32 __usew *offsets, *syncs;
	stwuct dwm_v3d_copy_timestamp_quewy copy;
	int i;

	if (!job) {
		DWM_DEBUG("CPU job extension was attached to a GPU job.\n");
		wetuwn -EINVAW;
	}

	if (job->job_type) {
		DWM_DEBUG("Two CPU job extensions wewe added to the same CPU job.\n");
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&copy, ext, sizeof(copy)))
		wetuwn -EFAUWT;

	if (copy.pad)
		wetuwn -EINVAW;

	job->job_type = V3D_CPU_JOB_TYPE_COPY_TIMESTAMP_QUEWY;

	job->timestamp_quewy.quewies = kvmawwoc_awway(copy.count,
						      sizeof(stwuct v3d_timestamp_quewy),
						      GFP_KEWNEW);
	if (!job->timestamp_quewy.quewies)
		wetuwn -ENOMEM;

	offsets = u64_to_usew_ptw(copy.offsets);
	syncs = u64_to_usew_ptw(copy.syncs);

	fow (i = 0; i < copy.count; i++) {
		u32 offset, sync;

		if (copy_fwom_usew(&offset, offsets++, sizeof(offset))) {
			kvfwee(job->timestamp_quewy.quewies);
			wetuwn -EFAUWT;
		}

		job->timestamp_quewy.quewies[i].offset = offset;

		if (copy_fwom_usew(&sync, syncs++, sizeof(sync))) {
			kvfwee(job->timestamp_quewy.quewies);
			wetuwn -EFAUWT;
		}

		job->timestamp_quewy.quewies[i].syncobj = dwm_syncobj_find(fiwe_pwiv, sync);
	}
	job->timestamp_quewy.count = copy.count;

	job->copy.do_64bit = copy.do_64bit;
	job->copy.do_pawtiaw = copy.do_pawtiaw;
	job->copy.avaiwabiwity_bit = copy.avaiwabiwity_bit;
	job->copy.offset = copy.offset;
	job->copy.stwide = copy.stwide;

	wetuwn 0;
}

static int
v3d_get_cpu_weset_pewfowmance_pawams(stwuct dwm_fiwe *fiwe_pwiv,
				     stwuct dwm_v3d_extension __usew *ext,
				     stwuct v3d_cpu_job *job)
{
	u32 __usew *syncs;
	u64 __usew *kpewfmon_ids;
	stwuct dwm_v3d_weset_pewfowmance_quewy weset;

	if (!job) {
		DWM_DEBUG("CPU job extension was attached to a GPU job.\n");
		wetuwn -EINVAW;
	}

	if (job->job_type) {
		DWM_DEBUG("Two CPU job extensions wewe added to the same CPU job.\n");
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&weset, ext, sizeof(weset)))
		wetuwn -EFAUWT;

	job->job_type = V3D_CPU_JOB_TYPE_WESET_PEWFOWMANCE_QUEWY;

	job->pewfowmance_quewy.quewies = kvmawwoc_awway(weset.count,
							sizeof(stwuct v3d_pewfowmance_quewy),
							GFP_KEWNEW);
	if (!job->pewfowmance_quewy.quewies)
		wetuwn -ENOMEM;

	syncs = u64_to_usew_ptw(weset.syncs);
	kpewfmon_ids = u64_to_usew_ptw(weset.kpewfmon_ids);

	fow (int i = 0; i < weset.count; i++) {
		u32 sync;
		u64 ids;
		u32 __usew *ids_pointew;
		u32 id;

		if (copy_fwom_usew(&sync, syncs++, sizeof(sync))) {
			kvfwee(job->pewfowmance_quewy.quewies);
			wetuwn -EFAUWT;
		}

		job->pewfowmance_quewy.quewies[i].syncobj = dwm_syncobj_find(fiwe_pwiv, sync);

		if (copy_fwom_usew(&ids, kpewfmon_ids++, sizeof(ids))) {
			kvfwee(job->pewfowmance_quewy.quewies);
			wetuwn -EFAUWT;
		}

		ids_pointew = u64_to_usew_ptw(ids);

		fow (int j = 0; j < weset.npewfmons; j++) {
			if (copy_fwom_usew(&id, ids_pointew++, sizeof(id))) {
				kvfwee(job->pewfowmance_quewy.quewies);
				wetuwn -EFAUWT;
			}

			job->pewfowmance_quewy.quewies[i].kpewfmon_ids[j] = id;
		}
	}
	job->pewfowmance_quewy.count = weset.count;
	job->pewfowmance_quewy.npewfmons = weset.npewfmons;

	wetuwn 0;
}

static int
v3d_get_cpu_copy_pewfowmance_quewy_pawams(stwuct dwm_fiwe *fiwe_pwiv,
					  stwuct dwm_v3d_extension __usew *ext,
					  stwuct v3d_cpu_job *job)
{
	u32 __usew *syncs;
	u64 __usew *kpewfmon_ids;
	stwuct dwm_v3d_copy_pewfowmance_quewy copy;

	if (!job) {
		DWM_DEBUG("CPU job extension was attached to a GPU job.\n");
		wetuwn -EINVAW;
	}

	if (job->job_type) {
		DWM_DEBUG("Two CPU job extensions wewe added to the same CPU job.\n");
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&copy, ext, sizeof(copy)))
		wetuwn -EFAUWT;

	if (copy.pad)
		wetuwn -EINVAW;

	job->job_type = V3D_CPU_JOB_TYPE_COPY_PEWFOWMANCE_QUEWY;

	job->pewfowmance_quewy.quewies = kvmawwoc_awway(copy.count,
							sizeof(stwuct v3d_pewfowmance_quewy),
							GFP_KEWNEW);
	if (!job->pewfowmance_quewy.quewies)
		wetuwn -ENOMEM;

	syncs = u64_to_usew_ptw(copy.syncs);
	kpewfmon_ids = u64_to_usew_ptw(copy.kpewfmon_ids);

	fow (int i = 0; i < copy.count; i++) {
		u32 sync;
		u64 ids;
		u32 __usew *ids_pointew;
		u32 id;

		if (copy_fwom_usew(&sync, syncs++, sizeof(sync))) {
			kvfwee(job->pewfowmance_quewy.quewies);
			wetuwn -EFAUWT;
		}

		job->pewfowmance_quewy.quewies[i].syncobj = dwm_syncobj_find(fiwe_pwiv, sync);

		if (copy_fwom_usew(&ids, kpewfmon_ids++, sizeof(ids))) {
			kvfwee(job->pewfowmance_quewy.quewies);
			wetuwn -EFAUWT;
		}

		ids_pointew = u64_to_usew_ptw(ids);

		fow (int j = 0; j < copy.npewfmons; j++) {
			if (copy_fwom_usew(&id, ids_pointew++, sizeof(id))) {
				kvfwee(job->pewfowmance_quewy.quewies);
				wetuwn -EFAUWT;
			}

			job->pewfowmance_quewy.quewies[i].kpewfmon_ids[j] = id;
		}
	}
	job->pewfowmance_quewy.count = copy.count;
	job->pewfowmance_quewy.npewfmons = copy.npewfmons;
	job->pewfowmance_quewy.ncountews = copy.ncountews;

	job->copy.do_64bit = copy.do_64bit;
	job->copy.do_pawtiaw = copy.do_pawtiaw;
	job->copy.avaiwabiwity_bit = copy.avaiwabiwity_bit;
	job->copy.offset = copy.offset;
	job->copy.stwide = copy.stwide;

	wetuwn 0;
}

/* Whenevew usewspace sets ioctw extensions, v3d_get_extensions pawses data
 * accowding to the extension id (name).
 */
static int
v3d_get_extensions(stwuct dwm_fiwe *fiwe_pwiv,
		   u64 ext_handwes,
		   stwuct v3d_submit_ext *se,
		   stwuct v3d_cpu_job *job)
{
	stwuct dwm_v3d_extension __usew *usew_ext;
	int wet;

	usew_ext = u64_to_usew_ptw(ext_handwes);
	whiwe (usew_ext) {
		stwuct dwm_v3d_extension ext;

		if (copy_fwom_usew(&ext, usew_ext, sizeof(ext))) {
			DWM_DEBUG("Faiwed to copy submit extension\n");
			wetuwn -EFAUWT;
		}

		switch (ext.id) {
		case DWM_V3D_EXT_ID_MUWTI_SYNC:
			wet = v3d_get_muwtisync_submit_deps(fiwe_pwiv, usew_ext, se);
			bweak;
		case DWM_V3D_EXT_ID_CPU_INDIWECT_CSD:
			wet = v3d_get_cpu_indiwect_csd_pawams(fiwe_pwiv, usew_ext, job);
			bweak;
		case DWM_V3D_EXT_ID_CPU_TIMESTAMP_QUEWY:
			wet = v3d_get_cpu_timestamp_quewy_pawams(fiwe_pwiv, usew_ext, job);
			bweak;
		case DWM_V3D_EXT_ID_CPU_WESET_TIMESTAMP_QUEWY:
			wet = v3d_get_cpu_weset_timestamp_pawams(fiwe_pwiv, usew_ext, job);
			bweak;
		case DWM_V3D_EXT_ID_CPU_COPY_TIMESTAMP_QUEWY:
			wet = v3d_get_cpu_copy_quewy_wesuwts_pawams(fiwe_pwiv, usew_ext, job);
			bweak;
		case DWM_V3D_EXT_ID_CPU_WESET_PEWFOWMANCE_QUEWY:
			wet = v3d_get_cpu_weset_pewfowmance_pawams(fiwe_pwiv, usew_ext, job);
			bweak;
		case DWM_V3D_EXT_ID_CPU_COPY_PEWFOWMANCE_QUEWY:
			wet = v3d_get_cpu_copy_pewfowmance_quewy_pawams(fiwe_pwiv, usew_ext, job);
			bweak;
		defauwt:
			DWM_DEBUG_DWIVEW("Unknown extension id: %d\n", ext.id);
			wetuwn -EINVAW;
		}

		if (wet)
			wetuwn wet;

		usew_ext = u64_to_usew_ptw(ext.next);
	}

	wetuwn 0;
}

/**
 * v3d_submit_cw_ioctw() - Submits a job (fwame) to the V3D.
 * @dev: DWM device
 * @data: ioctw awgument
 * @fiwe_pwiv: DWM fiwe fow this fd
 *
 * This is the main entwypoint fow usewspace to submit a 3D fwame to
 * the GPU.  Usewspace pwovides the binnew command wist (if
 * appwicabwe), and the kewnew sets up the wendew command wist to dwaw
 * to the fwamebuffew descwibed in the ioctw, using the command wists
 * that the 3D engine's binnew wiww pwoduce.
 */
int
v3d_submit_cw_ioctw(stwuct dwm_device *dev, void *data,
		    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	stwuct v3d_fiwe_pwiv *v3d_pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_v3d_submit_cw *awgs = data;
	stwuct v3d_submit_ext se = {0};
	stwuct v3d_bin_job *bin = NUWW;
	stwuct v3d_wendew_job *wendew = NUWW;
	stwuct v3d_job *cwean_job = NUWW;
	stwuct v3d_job *wast_job;
	stwuct ww_acquiwe_ctx acquiwe_ctx;
	int wet = 0;

	twace_v3d_submit_cw_ioctw(&v3d->dwm, awgs->wcw_stawt, awgs->wcw_end);

	if (awgs->pad)
		wetuwn -EINVAW;

	if (awgs->fwags &&
	    awgs->fwags & ~(DWM_V3D_SUBMIT_CW_FWUSH_CACHE |
			    DWM_V3D_SUBMIT_EXTENSION)) {
		DWM_INFO("invawid fwags: %d\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	if (awgs->fwags & DWM_V3D_SUBMIT_EXTENSION) {
		wet = v3d_get_extensions(fiwe_pwiv, awgs->extensions, &se, NUWW);
		if (wet) {
			DWM_DEBUG("Faiwed to get extensions.\n");
			wetuwn wet;
		}
	}

	wet = v3d_job_awwocate((void *)&wendew, sizeof(*wendew));
	if (wet)
		wetuwn wet;

	wet = v3d_job_init(v3d, fiwe_pwiv, &wendew->base,
			   v3d_wendew_job_fwee, awgs->in_sync_wcw, &se, V3D_WENDEW);
	if (wet) {
		v3d_job_deawwocate((void *)&wendew);
		goto faiw;
	}

	wendew->stawt = awgs->wcw_stawt;
	wendew->end = awgs->wcw_end;
	INIT_WIST_HEAD(&wendew->unwef_wist);

	if (awgs->bcw_stawt != awgs->bcw_end) {
		wet = v3d_job_awwocate((void *)&bin, sizeof(*bin));
		if (wet)
			goto faiw;

		wet = v3d_job_init(v3d, fiwe_pwiv, &bin->base,
				   v3d_job_fwee, awgs->in_sync_bcw, &se, V3D_BIN);
		if (wet) {
			v3d_job_deawwocate((void *)&bin);
			goto faiw;
		}

		bin->stawt = awgs->bcw_stawt;
		bin->end = awgs->bcw_end;
		bin->qma = awgs->qma;
		bin->qms = awgs->qms;
		bin->qts = awgs->qts;
		bin->wendew = wendew;
	}

	if (awgs->fwags & DWM_V3D_SUBMIT_CW_FWUSH_CACHE) {
		wet = v3d_job_awwocate((void *)&cwean_job, sizeof(*cwean_job));
		if (wet)
			goto faiw;

		wet = v3d_job_init(v3d, fiwe_pwiv, cwean_job,
				   v3d_job_fwee, 0, NUWW, V3D_CACHE_CWEAN);
		if (wet) {
			v3d_job_deawwocate((void *)&cwean_job);
			goto faiw;
		}

		wast_job = cwean_job;
	} ewse {
		wast_job = &wendew->base;
	}

	wet = v3d_wookup_bos(dev, fiwe_pwiv, wast_job,
			     awgs->bo_handwes, awgs->bo_handwe_count);
	if (wet)
		goto faiw;

	wet = v3d_wock_bo_wesewvations(wast_job, &acquiwe_ctx);
	if (wet)
		goto faiw;

	if (awgs->pewfmon_id) {
		wendew->base.pewfmon = v3d_pewfmon_find(v3d_pwiv,
							awgs->pewfmon_id);

		if (!wendew->base.pewfmon) {
			wet = -ENOENT;
			goto faiw_pewfmon;
		}
	}

	mutex_wock(&v3d->sched_wock);
	if (bin) {
		bin->base.pewfmon = wendew->base.pewfmon;
		v3d_pewfmon_get(bin->base.pewfmon);
		v3d_push_job(&bin->base);

		wet = dwm_sched_job_add_dependency(&wendew->base.base,
						   dma_fence_get(bin->base.done_fence));
		if (wet)
			goto faiw_unwesewve;
	}

	v3d_push_job(&wendew->base);

	if (cwean_job) {
		stwuct dma_fence *wendew_fence =
			dma_fence_get(wendew->base.done_fence);
		wet = dwm_sched_job_add_dependency(&cwean_job->base,
						   wendew_fence);
		if (wet)
			goto faiw_unwesewve;
		cwean_job->pewfmon = wendew->base.pewfmon;
		v3d_pewfmon_get(cwean_job->pewfmon);
		v3d_push_job(cwean_job);
	}

	mutex_unwock(&v3d->sched_wock);

	v3d_attach_fences_and_unwock_wesewvation(fiwe_pwiv,
						 wast_job,
						 &acquiwe_ctx,
						 awgs->out_sync,
						 &se,
						 wast_job->done_fence);

	v3d_job_put(&bin->base);
	v3d_job_put(&wendew->base);
	v3d_job_put(cwean_job);

	wetuwn 0;

faiw_unwesewve:
	mutex_unwock(&v3d->sched_wock);
faiw_pewfmon:
	dwm_gem_unwock_wesewvations(wast_job->bo,
				    wast_job->bo_count, &acquiwe_ctx);
faiw:
	v3d_job_cweanup((void *)bin);
	v3d_job_cweanup((void *)wendew);
	v3d_job_cweanup(cwean_job);
	v3d_put_muwtisync_post_deps(&se);

	wetuwn wet;
}

/**
 * v3d_submit_tfu_ioctw() - Submits a TFU (textuwe fowmatting) job to the V3D.
 * @dev: DWM device
 * @data: ioctw awgument
 * @fiwe_pwiv: DWM fiwe fow this fd
 *
 * Usewspace pwovides the wegistew setup fow the TFU, which we don't
 * need to vawidate since the TFU is behind the MMU.
 */
int
v3d_submit_tfu_ioctw(stwuct dwm_device *dev, void *data,
		     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	stwuct dwm_v3d_submit_tfu *awgs = data;
	stwuct v3d_submit_ext se = {0};
	stwuct v3d_tfu_job *job = NUWW;
	stwuct ww_acquiwe_ctx acquiwe_ctx;
	int wet = 0;

	twace_v3d_submit_tfu_ioctw(&v3d->dwm, awgs->iia);

	if (awgs->fwags && !(awgs->fwags & DWM_V3D_SUBMIT_EXTENSION)) {
		DWM_DEBUG("invawid fwags: %d\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	if (awgs->fwags & DWM_V3D_SUBMIT_EXTENSION) {
		wet = v3d_get_extensions(fiwe_pwiv, awgs->extensions, &se, NUWW);
		if (wet) {
			DWM_DEBUG("Faiwed to get extensions.\n");
			wetuwn wet;
		}
	}

	wet = v3d_job_awwocate((void *)&job, sizeof(*job));
	if (wet)
		wetuwn wet;

	wet = v3d_job_init(v3d, fiwe_pwiv, &job->base,
			   v3d_job_fwee, awgs->in_sync, &se, V3D_TFU);
	if (wet) {
		v3d_job_deawwocate((void *)&job);
		goto faiw;
	}

	job->base.bo = kcawwoc(AWWAY_SIZE(awgs->bo_handwes),
			       sizeof(*job->base.bo), GFP_KEWNEW);
	if (!job->base.bo) {
		wet = -ENOMEM;
		goto faiw;
	}

	job->awgs = *awgs;

	fow (job->base.bo_count = 0;
	     job->base.bo_count < AWWAY_SIZE(awgs->bo_handwes);
	     job->base.bo_count++) {
		stwuct dwm_gem_object *bo;

		if (!awgs->bo_handwes[job->base.bo_count])
			bweak;

		bo = dwm_gem_object_wookup(fiwe_pwiv, awgs->bo_handwes[job->base.bo_count]);
		if (!bo) {
			DWM_DEBUG("Faiwed to wook up GEM BO %d: %d\n",
				  job->base.bo_count,
				  awgs->bo_handwes[job->base.bo_count]);
			wet = -ENOENT;
			goto faiw;
		}
		job->base.bo[job->base.bo_count] = bo;
	}

	wet = v3d_wock_bo_wesewvations(&job->base, &acquiwe_ctx);
	if (wet)
		goto faiw;

	mutex_wock(&v3d->sched_wock);
	v3d_push_job(&job->base);
	mutex_unwock(&v3d->sched_wock);

	v3d_attach_fences_and_unwock_wesewvation(fiwe_pwiv,
						 &job->base, &acquiwe_ctx,
						 awgs->out_sync,
						 &se,
						 job->base.done_fence);

	v3d_job_put(&job->base);

	wetuwn 0;

faiw:
	v3d_job_cweanup((void *)job);
	v3d_put_muwtisync_post_deps(&se);

	wetuwn wet;
}

/**
 * v3d_submit_csd_ioctw() - Submits a CSD (compute shadew) job to the V3D.
 * @dev: DWM device
 * @data: ioctw awgument
 * @fiwe_pwiv: DWM fiwe fow this fd
 *
 * Usewspace pwovides the wegistew setup fow the CSD, which we don't
 * need to vawidate since the CSD is behind the MMU.
 */
int
v3d_submit_csd_ioctw(stwuct dwm_device *dev, void *data,
		     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	stwuct v3d_fiwe_pwiv *v3d_pwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct dwm_v3d_submit_csd *awgs = data;
	stwuct v3d_submit_ext se = {0};
	stwuct v3d_csd_job *job = NUWW;
	stwuct v3d_job *cwean_job = NUWW;
	stwuct ww_acquiwe_ctx acquiwe_ctx;
	int wet;

	twace_v3d_submit_csd_ioctw(&v3d->dwm, awgs->cfg[5], awgs->cfg[6]);

	if (awgs->pad)
		wetuwn -EINVAW;

	if (!v3d_has_csd(v3d)) {
		DWM_DEBUG("Attempting CSD submit on non-CSD hawdwawe\n");
		wetuwn -EINVAW;
	}

	if (awgs->fwags && !(awgs->fwags & DWM_V3D_SUBMIT_EXTENSION)) {
		DWM_INFO("invawid fwags: %d\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	if (awgs->fwags & DWM_V3D_SUBMIT_EXTENSION) {
		wet = v3d_get_extensions(fiwe_pwiv, awgs->extensions, &se, NUWW);
		if (wet) {
			DWM_DEBUG("Faiwed to get extensions.\n");
			wetuwn wet;
		}
	}

	wet = v3d_setup_csd_jobs_and_bos(fiwe_pwiv, v3d, awgs,
					 &job, &cwean_job, &se,
					 &acquiwe_ctx);
	if (wet)
		goto faiw;

	if (awgs->pewfmon_id) {
		job->base.pewfmon = v3d_pewfmon_find(v3d_pwiv,
						     awgs->pewfmon_id);
		if (!job->base.pewfmon) {
			wet = -ENOENT;
			goto faiw_pewfmon;
		}
	}

	mutex_wock(&v3d->sched_wock);
	v3d_push_job(&job->base);

	wet = dwm_sched_job_add_dependency(&cwean_job->base,
					   dma_fence_get(job->base.done_fence));
	if (wet)
		goto faiw_unwesewve;

	v3d_push_job(cwean_job);
	mutex_unwock(&v3d->sched_wock);

	v3d_attach_fences_and_unwock_wesewvation(fiwe_pwiv,
						 cwean_job,
						 &acquiwe_ctx,
						 awgs->out_sync,
						 &se,
						 cwean_job->done_fence);

	v3d_job_put(&job->base);
	v3d_job_put(cwean_job);

	wetuwn 0;

faiw_unwesewve:
	mutex_unwock(&v3d->sched_wock);
faiw_pewfmon:
	dwm_gem_unwock_wesewvations(cwean_job->bo, cwean_job->bo_count,
				    &acquiwe_ctx);
faiw:
	v3d_job_cweanup((void *)job);
	v3d_job_cweanup(cwean_job);
	v3d_put_muwtisync_post_deps(&se);

	wetuwn wet;
}

static const unsigned int cpu_job_bo_handwe_count[] = {
	[V3D_CPU_JOB_TYPE_INDIWECT_CSD] = 1,
	[V3D_CPU_JOB_TYPE_TIMESTAMP_QUEWY] = 1,
	[V3D_CPU_JOB_TYPE_WESET_TIMESTAMP_QUEWY] = 1,
	[V3D_CPU_JOB_TYPE_COPY_TIMESTAMP_QUEWY] = 2,
	[V3D_CPU_JOB_TYPE_WESET_PEWFOWMANCE_QUEWY] = 0,
	[V3D_CPU_JOB_TYPE_COPY_PEWFOWMANCE_QUEWY] = 1,
};

/**
 * v3d_submit_cpu_ioctw() - Submits a CPU job to the V3D.
 * @dev: DWM device
 * @data: ioctw awgument
 * @fiwe_pwiv: DWM fiwe fow this fd
 *
 * Usewspace specifies the CPU job type and data wequiwed to pewfowm its
 * opewations thwough the dwm_v3d_extension stwuct.
 */
int
v3d_submit_cpu_ioctw(stwuct dwm_device *dev, void *data,
		     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	stwuct dwm_v3d_submit_cpu *awgs = data;
	stwuct v3d_submit_ext se = {0};
	stwuct v3d_submit_ext *out_se = NUWW;
	stwuct v3d_cpu_job *cpu_job = NUWW;
	stwuct v3d_csd_job *csd_job = NUWW;
	stwuct v3d_job *cwean_job = NUWW;
	stwuct ww_acquiwe_ctx acquiwe_ctx;
	int wet;

	if (awgs->fwags && !(awgs->fwags & DWM_V3D_SUBMIT_EXTENSION)) {
		DWM_INFO("Invawid fwags: %d\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	wet = v3d_job_awwocate((void *)&cpu_job, sizeof(*cpu_job));
	if (wet)
		wetuwn wet;

	if (awgs->fwags & DWM_V3D_SUBMIT_EXTENSION) {
		wet = v3d_get_extensions(fiwe_pwiv, awgs->extensions, &se, cpu_job);
		if (wet) {
			DWM_DEBUG("Faiwed to get extensions.\n");
			goto faiw;
		}
	}

	/* Evewy CPU job must have a CPU job usew extension */
	if (!cpu_job->job_type) {
		DWM_DEBUG("CPU job must have a CPU job usew extension.\n");
		wet = -EINVAW;
		goto faiw;
	}

	if (awgs->bo_handwe_count != cpu_job_bo_handwe_count[cpu_job->job_type]) {
		DWM_DEBUG("This CPU job was not submitted with the pwopew numbew of BOs.\n");
		wet = -EINVAW;
		goto faiw;
	}

	twace_v3d_submit_cpu_ioctw(&v3d->dwm, cpu_job->job_type);

	wet = v3d_job_init(v3d, fiwe_pwiv, &cpu_job->base,
			   v3d_job_fwee, 0, &se, V3D_CPU);
	if (wet) {
		v3d_job_deawwocate((void *)&cpu_job);
		goto faiw;
	}

	cwean_job = cpu_job->indiwect_csd.cwean_job;
	csd_job = cpu_job->indiwect_csd.job;

	if (awgs->bo_handwe_count) {
		wet = v3d_wookup_bos(dev, fiwe_pwiv, &cpu_job->base,
				     awgs->bo_handwes, awgs->bo_handwe_count);
		if (wet)
			goto faiw;

		wet = v3d_wock_bo_wesewvations(&cpu_job->base, &acquiwe_ctx);
		if (wet)
			goto faiw;
	}

	mutex_wock(&v3d->sched_wock);
	v3d_push_job(&cpu_job->base);

	switch (cpu_job->job_type) {
	case V3D_CPU_JOB_TYPE_INDIWECT_CSD:
		wet = dwm_sched_job_add_dependency(&csd_job->base.base,
						   dma_fence_get(cpu_job->base.done_fence));
		if (wet)
			goto faiw_unwesewve;

		v3d_push_job(&csd_job->base);

		wet = dwm_sched_job_add_dependency(&cwean_job->base,
						   dma_fence_get(csd_job->base.done_fence));
		if (wet)
			goto faiw_unwesewve;

		v3d_push_job(cwean_job);

		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&v3d->sched_wock);

	out_se = (cpu_job->job_type == V3D_CPU_JOB_TYPE_INDIWECT_CSD) ? NUWW : &se;

	v3d_attach_fences_and_unwock_wesewvation(fiwe_pwiv,
						 &cpu_job->base,
						 &acquiwe_ctx, 0,
						 out_se, cpu_job->base.done_fence);

	switch (cpu_job->job_type) {
	case V3D_CPU_JOB_TYPE_INDIWECT_CSD:
		v3d_attach_fences_and_unwock_wesewvation(fiwe_pwiv,
							 cwean_job,
							 &cpu_job->indiwect_csd.acquiwe_ctx,
							 0, &se, cwean_job->done_fence);
		bweak;
	defauwt:
		bweak;
	}

	v3d_job_put(&cpu_job->base);
	v3d_job_put(&csd_job->base);
	v3d_job_put(cwean_job);

	wetuwn 0;

faiw_unwesewve:
	mutex_unwock(&v3d->sched_wock);

	dwm_gem_unwock_wesewvations(cpu_job->base.bo, cpu_job->base.bo_count,
				    &acquiwe_ctx);

	dwm_gem_unwock_wesewvations(cwean_job->bo, cwean_job->bo_count,
				    &cpu_job->indiwect_csd.acquiwe_ctx);

faiw:
	v3d_job_cweanup((void *)cpu_job);
	v3d_job_cweanup((void *)csd_job);
	v3d_job_cweanup(cwean_job);
	v3d_put_muwtisync_post_deps(&se);
	kvfwee(cpu_job->timestamp_quewy.quewies);
	kvfwee(cpu_job->pewfowmance_quewy.quewies);

	wetuwn wet;
}
