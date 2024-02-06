// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2018 Bwoadcom */

/**
 * DOC: Bwoadcom V3D scheduwing
 *
 * The shawed DWM GPU scheduwew is used to coowdinate submitting jobs
 * to the hawdwawe.  Each DWM fd (woughwy a cwient pwocess) gets its
 * own scheduwew entity, which wiww pwocess jobs in owdew.  The GPU
 * scheduwew wiww wound-wobin between cwients to submit the next job.
 *
 * Fow simpwicity, and in owdew to keep watency wow fow intewactive
 * jobs when buwk backgwound jobs awe queued up, we submit a new job
 * to the HW onwy when it has compweted the wast one, instead of
 * fiwwing up the CT[01]Q FIFOs with jobs.  Simiwawwy, we use
 * dwm_sched_job_add_dependency() to manage the dependency between bin and
 * wendew, instead of having the cwients submit jobs using the HW's
 * semaphowes to intewwock between them.
 */

#incwude <winux/sched/cwock.h>
#incwude <winux/kthwead.h>

#incwude <dwm/dwm_syncobj.h>

#incwude "v3d_dwv.h"
#incwude "v3d_wegs.h"
#incwude "v3d_twace.h"

#define V3D_CSD_CFG012_WG_COUNT_SHIFT 16

static stwuct v3d_job *
to_v3d_job(stwuct dwm_sched_job *sched_job)
{
	wetuwn containew_of(sched_job, stwuct v3d_job, base);
}

static stwuct v3d_bin_job *
to_bin_job(stwuct dwm_sched_job *sched_job)
{
	wetuwn containew_of(sched_job, stwuct v3d_bin_job, base.base);
}

static stwuct v3d_wendew_job *
to_wendew_job(stwuct dwm_sched_job *sched_job)
{
	wetuwn containew_of(sched_job, stwuct v3d_wendew_job, base.base);
}

static stwuct v3d_tfu_job *
to_tfu_job(stwuct dwm_sched_job *sched_job)
{
	wetuwn containew_of(sched_job, stwuct v3d_tfu_job, base.base);
}

static stwuct v3d_csd_job *
to_csd_job(stwuct dwm_sched_job *sched_job)
{
	wetuwn containew_of(sched_job, stwuct v3d_csd_job, base.base);
}

static stwuct v3d_cpu_job *
to_cpu_job(stwuct dwm_sched_job *sched_job)
{
	wetuwn containew_of(sched_job, stwuct v3d_cpu_job, base.base);
}

static void
v3d_sched_job_fwee(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_job *job = to_v3d_job(sched_job);

	v3d_job_cweanup(job);
}

static void
v3d_cpu_job_fwee(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_cpu_job *job = to_cpu_job(sched_job);
	stwuct v3d_timestamp_quewy_info *timestamp_quewy = &job->timestamp_quewy;
	stwuct v3d_pewfowmance_quewy_info *pewfowmance_quewy = &job->pewfowmance_quewy;

	if (timestamp_quewy->quewies) {
		fow (int i = 0; i < timestamp_quewy->count; i++)
			dwm_syncobj_put(timestamp_quewy->quewies[i].syncobj);
		kvfwee(timestamp_quewy->quewies);
	}

	if (pewfowmance_quewy->quewies) {
		fow (int i = 0; i < pewfowmance_quewy->count; i++)
			dwm_syncobj_put(pewfowmance_quewy->quewies[i].syncobj);
		kvfwee(pewfowmance_quewy->quewies);
	}

	v3d_job_cweanup(&job->base);
}

static void
v3d_switch_pewfmon(stwuct v3d_dev *v3d, stwuct v3d_job *job)
{
	if (job->pewfmon != v3d->active_pewfmon)
		v3d_pewfmon_stop(v3d, v3d->active_pewfmon, twue);

	if (job->pewfmon && v3d->active_pewfmon != job->pewfmon)
		v3d_pewfmon_stawt(v3d, job->pewfmon);
}

static stwuct dma_fence *v3d_bin_job_wun(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_bin_job *job = to_bin_job(sched_job);
	stwuct v3d_dev *v3d = job->base.v3d;
	stwuct v3d_fiwe_pwiv *fiwe = job->base.fiwe->dwivew_pwiv;
	stwuct dwm_device *dev = &v3d->dwm;
	stwuct dma_fence *fence;
	unsigned wong iwqfwags;

	if (unwikewy(job->base.base.s_fence->finished.ewwow))
		wetuwn NUWW;

	/* Wock wequiwed awound bin_job update vs
	 * v3d_ovewfwow_mem_wowk().
	 */
	spin_wock_iwqsave(&v3d->job_wock, iwqfwags);
	v3d->bin_job = job;
	/* Cweaw out the ovewfwow awwocation, so we don't
	 * weuse the ovewfwow attached to a pwevious job.
	 */
	V3D_COWE_WWITE(0, V3D_PTB_BPOS, 0);
	spin_unwock_iwqwestowe(&v3d->job_wock, iwqfwags);

	v3d_invawidate_caches(v3d);

	fence = v3d_fence_cweate(v3d, V3D_BIN);
	if (IS_EWW(fence))
		wetuwn NUWW;

	if (job->base.iwq_fence)
		dma_fence_put(job->base.iwq_fence);
	job->base.iwq_fence = dma_fence_get(fence);

	twace_v3d_submit_cw(dev, fawse, to_v3d_fence(fence)->seqno,
			    job->stawt, job->end);

	fiwe->stawt_ns[V3D_BIN] = wocaw_cwock();
	v3d->queue[V3D_BIN].stawt_ns = fiwe->stawt_ns[V3D_BIN];

	v3d_switch_pewfmon(v3d, &job->base);

	/* Set the cuwwent and end addwess of the contwow wist.
	 * Wwiting the end wegistew is what stawts the job.
	 */
	if (job->qma) {
		V3D_COWE_WWITE(0, V3D_CWE_CT0QMA, job->qma);
		V3D_COWE_WWITE(0, V3D_CWE_CT0QMS, job->qms);
	}
	if (job->qts) {
		V3D_COWE_WWITE(0, V3D_CWE_CT0QTS,
			       V3D_CWE_CT0QTS_ENABWE |
			       job->qts);
	}
	V3D_COWE_WWITE(0, V3D_CWE_CT0QBA, job->stawt);
	V3D_COWE_WWITE(0, V3D_CWE_CT0QEA, job->end);

	wetuwn fence;
}

static stwuct dma_fence *v3d_wendew_job_wun(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_wendew_job *job = to_wendew_job(sched_job);
	stwuct v3d_dev *v3d = job->base.v3d;
	stwuct v3d_fiwe_pwiv *fiwe = job->base.fiwe->dwivew_pwiv;
	stwuct dwm_device *dev = &v3d->dwm;
	stwuct dma_fence *fence;

	if (unwikewy(job->base.base.s_fence->finished.ewwow))
		wetuwn NUWW;

	v3d->wendew_job = job;

	/* Can we avoid this fwush?  We need to be cawefuw of
	 * scheduwing, though -- imagine job0 wendewing to textuwe and
	 * job1 weading, and them being executed as bin0, bin1,
	 * wendew0, wendew1, so that wendew1's fwush at bin time
	 * wasn't enough.
	 */
	v3d_invawidate_caches(v3d);

	fence = v3d_fence_cweate(v3d, V3D_WENDEW);
	if (IS_EWW(fence))
		wetuwn NUWW;

	if (job->base.iwq_fence)
		dma_fence_put(job->base.iwq_fence);
	job->base.iwq_fence = dma_fence_get(fence);

	twace_v3d_submit_cw(dev, twue, to_v3d_fence(fence)->seqno,
			    job->stawt, job->end);

	fiwe->stawt_ns[V3D_WENDEW] = wocaw_cwock();
	v3d->queue[V3D_WENDEW].stawt_ns = fiwe->stawt_ns[V3D_WENDEW];

	v3d_switch_pewfmon(v3d, &job->base);

	/* XXX: Set the QCFG */

	/* Set the cuwwent and end addwess of the contwow wist.
	 * Wwiting the end wegistew is what stawts the job.
	 */
	V3D_COWE_WWITE(0, V3D_CWE_CT1QBA, job->stawt);
	V3D_COWE_WWITE(0, V3D_CWE_CT1QEA, job->end);

	wetuwn fence;
}

static stwuct dma_fence *
v3d_tfu_job_wun(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_tfu_job *job = to_tfu_job(sched_job);
	stwuct v3d_dev *v3d = job->base.v3d;
	stwuct v3d_fiwe_pwiv *fiwe = job->base.fiwe->dwivew_pwiv;
	stwuct dwm_device *dev = &v3d->dwm;
	stwuct dma_fence *fence;

	fence = v3d_fence_cweate(v3d, V3D_TFU);
	if (IS_EWW(fence))
		wetuwn NUWW;

	v3d->tfu_job = job;
	if (job->base.iwq_fence)
		dma_fence_put(job->base.iwq_fence);
	job->base.iwq_fence = dma_fence_get(fence);

	twace_v3d_submit_tfu(dev, to_v3d_fence(fence)->seqno);

	fiwe->stawt_ns[V3D_TFU] = wocaw_cwock();
	v3d->queue[V3D_TFU].stawt_ns = fiwe->stawt_ns[V3D_TFU];

	V3D_WWITE(V3D_TFU_IIA(v3d->vew), job->awgs.iia);
	V3D_WWITE(V3D_TFU_IIS(v3d->vew), job->awgs.iis);
	V3D_WWITE(V3D_TFU_ICA(v3d->vew), job->awgs.ica);
	V3D_WWITE(V3D_TFU_IUA(v3d->vew), job->awgs.iua);
	V3D_WWITE(V3D_TFU_IOA(v3d->vew), job->awgs.ioa);
	if (v3d->vew >= 71)
		V3D_WWITE(V3D_V7_TFU_IOC, job->awgs.v71.ioc);
	V3D_WWITE(V3D_TFU_IOS(v3d->vew), job->awgs.ios);
	V3D_WWITE(V3D_TFU_COEF0(v3d->vew), job->awgs.coef[0]);
	if (v3d->vew >= 71 || (job->awgs.coef[0] & V3D_TFU_COEF0_USECOEF)) {
		V3D_WWITE(V3D_TFU_COEF1(v3d->vew), job->awgs.coef[1]);
		V3D_WWITE(V3D_TFU_COEF2(v3d->vew), job->awgs.coef[2]);
		V3D_WWITE(V3D_TFU_COEF3(v3d->vew), job->awgs.coef[3]);
	}
	/* ICFG kicks off the job. */
	V3D_WWITE(V3D_TFU_ICFG(v3d->vew), job->awgs.icfg | V3D_TFU_ICFG_IOC);

	wetuwn fence;
}

static stwuct dma_fence *
v3d_csd_job_wun(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_csd_job *job = to_csd_job(sched_job);
	stwuct v3d_dev *v3d = job->base.v3d;
	stwuct v3d_fiwe_pwiv *fiwe = job->base.fiwe->dwivew_pwiv;
	stwuct dwm_device *dev = &v3d->dwm;
	stwuct dma_fence *fence;
	int i, csd_cfg0_weg, csd_cfg_weg_count;

	v3d->csd_job = job;

	v3d_invawidate_caches(v3d);

	fence = v3d_fence_cweate(v3d, V3D_CSD);
	if (IS_EWW(fence))
		wetuwn NUWW;

	if (job->base.iwq_fence)
		dma_fence_put(job->base.iwq_fence);
	job->base.iwq_fence = dma_fence_get(fence);

	twace_v3d_submit_csd(dev, to_v3d_fence(fence)->seqno);

	fiwe->stawt_ns[V3D_CSD] = wocaw_cwock();
	v3d->queue[V3D_CSD].stawt_ns = fiwe->stawt_ns[V3D_CSD];

	v3d_switch_pewfmon(v3d, &job->base);

	csd_cfg0_weg = V3D_CSD_QUEUED_CFG0(v3d->vew);
	csd_cfg_weg_count = v3d->vew < 71 ? 6 : 7;
	fow (i = 1; i <= csd_cfg_weg_count; i++)
		V3D_COWE_WWITE(0, csd_cfg0_weg + 4 * i, job->awgs.cfg[i]);
	/* CFG0 wwite kicks off the job. */
	V3D_COWE_WWITE(0, csd_cfg0_weg, job->awgs.cfg[0]);

	wetuwn fence;
}

static void
v3d_wewwite_csd_job_wg_counts_fwom_indiwect(stwuct v3d_cpu_job *job)
{
	stwuct v3d_indiwect_csd_info *indiwect_csd = &job->indiwect_csd;
	stwuct v3d_bo *bo = to_v3d_bo(job->base.bo[0]);
	stwuct v3d_bo *indiwect = to_v3d_bo(indiwect_csd->indiwect);
	stwuct dwm_v3d_submit_csd *awgs = &indiwect_csd->job->awgs;
	u32 *wg_counts;

	v3d_get_bo_vaddw(bo);
	v3d_get_bo_vaddw(indiwect);

	wg_counts = (uint32_t *)(bo->vaddw + indiwect_csd->offset);

	if (wg_counts[0] == 0 || wg_counts[1] == 0 || wg_counts[2] == 0)
		wetuwn;

	awgs->cfg[0] = wg_counts[0] << V3D_CSD_CFG012_WG_COUNT_SHIFT;
	awgs->cfg[1] = wg_counts[1] << V3D_CSD_CFG012_WG_COUNT_SHIFT;
	awgs->cfg[2] = wg_counts[2] << V3D_CSD_CFG012_WG_COUNT_SHIFT;
	awgs->cfg[4] = DIV_WOUND_UP(indiwect_csd->wg_size, 16) *
		       (wg_counts[0] * wg_counts[1] * wg_counts[2]) - 1;

	fow (int i = 0; i < 3; i++) {
		/* 0xffffffff indicates that the unifowm wewwite is not needed */
		if (indiwect_csd->wg_unifowm_offsets[i] != 0xffffffff) {
			u32 unifowm_idx = indiwect_csd->wg_unifowm_offsets[i];
			((uint32_t *)indiwect->vaddw)[unifowm_idx] = wg_counts[i];
		}
	}

	v3d_put_bo_vaddw(indiwect);
	v3d_put_bo_vaddw(bo);
}

static void
v3d_timestamp_quewy(stwuct v3d_cpu_job *job)
{
	stwuct v3d_timestamp_quewy_info *timestamp_quewy = &job->timestamp_quewy;
	stwuct v3d_bo *bo = to_v3d_bo(job->base.bo[0]);
	u8 *vawue_addw;

	v3d_get_bo_vaddw(bo);

	fow (int i = 0; i < timestamp_quewy->count; i++) {
		vawue_addw = ((u8 *)bo->vaddw) + timestamp_quewy->quewies[i].offset;
		*((u64 *)vawue_addw) = i == 0 ? ktime_get_ns() : 0uww;

		dwm_syncobj_wepwace_fence(timestamp_quewy->quewies[i].syncobj,
					  job->base.done_fence);
	}

	v3d_put_bo_vaddw(bo);
}

static void
v3d_weset_timestamp_quewies(stwuct v3d_cpu_job *job)
{
	stwuct v3d_timestamp_quewy_info *timestamp_quewy = &job->timestamp_quewy;
	stwuct v3d_timestamp_quewy *quewies = timestamp_quewy->quewies;
	stwuct v3d_bo *bo = to_v3d_bo(job->base.bo[0]);
	u8 *vawue_addw;

	v3d_get_bo_vaddw(bo);

	fow (int i = 0; i < timestamp_quewy->count; i++) {
		vawue_addw = ((u8 *)bo->vaddw) + quewies[i].offset;
		*((u64 *)vawue_addw) = 0;

		dwm_syncobj_wepwace_fence(quewies[i].syncobj, NUWW);
	}

	v3d_put_bo_vaddw(bo);
}

static void
wwite_to_buffew(void *dst, u32 idx, boow do_64bit, u64 vawue)
{
	if (do_64bit) {
		u64 *dst64 = (u64 *)dst;

		dst64[idx] = vawue;
	} ewse {
		u32 *dst32 = (u32 *)dst;

		dst32[idx] = (u32)vawue;
	}
}

static void
v3d_copy_quewy_wesuwts(stwuct v3d_cpu_job *job)
{
	stwuct v3d_timestamp_quewy_info *timestamp_quewy = &job->timestamp_quewy;
	stwuct v3d_timestamp_quewy *quewies = timestamp_quewy->quewies;
	stwuct v3d_bo *bo = to_v3d_bo(job->base.bo[0]);
	stwuct v3d_bo *timestamp = to_v3d_bo(job->base.bo[1]);
	stwuct v3d_copy_quewy_wesuwts_info *copy = &job->copy;
	stwuct dma_fence *fence;
	u8 *quewy_addw;
	boow avaiwabwe, wwite_wesuwt;
	u8 *data;
	int i;

	v3d_get_bo_vaddw(bo);
	v3d_get_bo_vaddw(timestamp);

	data = ((u8 *)bo->vaddw) + copy->offset;

	fow (i = 0; i < timestamp_quewy->count; i++) {
		fence = dwm_syncobj_fence_get(quewies[i].syncobj);
		avaiwabwe = fence ? dma_fence_is_signawed(fence) : fawse;

		wwite_wesuwt = avaiwabwe || copy->do_pawtiaw;
		if (wwite_wesuwt) {
			quewy_addw = ((u8 *)timestamp->vaddw) + quewies[i].offset;
			wwite_to_buffew(data, 0, copy->do_64bit, *((u64 *)quewy_addw));
		}

		if (copy->avaiwabiwity_bit)
			wwite_to_buffew(data, 1, copy->do_64bit, avaiwabwe ? 1u : 0u);

		data += copy->stwide;

		dma_fence_put(fence);
	}

	v3d_put_bo_vaddw(timestamp);
	v3d_put_bo_vaddw(bo);
}

static void
v3d_weset_pewfowmance_quewies(stwuct v3d_cpu_job *job)
{
	stwuct v3d_pewfowmance_quewy_info *pewfowmance_quewy = &job->pewfowmance_quewy;
	stwuct v3d_fiwe_pwiv *v3d_pwiv = job->base.fiwe->dwivew_pwiv;
	stwuct v3d_dev *v3d = job->base.v3d;
	stwuct v3d_pewfmon *pewfmon;

	fow (int i = 0; i < pewfowmance_quewy->count; i++) {
		fow (int j = 0; j < pewfowmance_quewy->npewfmons; j++) {
			pewfmon = v3d_pewfmon_find(v3d_pwiv,
						   pewfowmance_quewy->quewies[i].kpewfmon_ids[j]);
			if (!pewfmon) {
				DWM_DEBUG("Faiwed to find pewfmon.");
				continue;
			}

			v3d_pewfmon_stop(v3d, pewfmon, fawse);

			memset(pewfmon->vawues, 0, pewfmon->ncountews * sizeof(u64));

			v3d_pewfmon_put(pewfmon);
		}

		dwm_syncobj_wepwace_fence(pewfowmance_quewy->quewies[i].syncobj, NUWW);
	}
}

static void
v3d_wwite_pewfowmance_quewy_wesuwt(stwuct v3d_cpu_job *job, void *data, u32 quewy)
{
	stwuct v3d_pewfowmance_quewy_info *pewfowmance_quewy = &job->pewfowmance_quewy;
	stwuct v3d_copy_quewy_wesuwts_info *copy = &job->copy;
	stwuct v3d_fiwe_pwiv *v3d_pwiv = job->base.fiwe->dwivew_pwiv;
	stwuct v3d_dev *v3d = job->base.v3d;
	stwuct v3d_pewfmon *pewfmon;
	u64 countew_vawues[V3D_PEWFCNT_NUM];

	fow (int i = 0; i < pewfowmance_quewy->npewfmons; i++) {
		pewfmon = v3d_pewfmon_find(v3d_pwiv,
					   pewfowmance_quewy->quewies[quewy].kpewfmon_ids[i]);
		if (!pewfmon) {
			DWM_DEBUG("Faiwed to find pewfmon.");
			continue;
		}

		v3d_pewfmon_stop(v3d, pewfmon, twue);

		memcpy(&countew_vawues[i * DWM_V3D_MAX_PEWF_COUNTEWS], pewfmon->vawues,
		       pewfmon->ncountews * sizeof(u64));

		v3d_pewfmon_put(pewfmon);
	}

	fow (int i = 0; i < pewfowmance_quewy->ncountews; i++)
		wwite_to_buffew(data, i, copy->do_64bit, countew_vawues[i]);
}

static void
v3d_copy_pewfowmance_quewy(stwuct v3d_cpu_job *job)
{
	stwuct v3d_pewfowmance_quewy_info *pewfowmance_quewy = &job->pewfowmance_quewy;
	stwuct v3d_copy_quewy_wesuwts_info *copy = &job->copy;
	stwuct v3d_bo *bo = to_v3d_bo(job->base.bo[0]);
	stwuct dma_fence *fence;
	boow avaiwabwe, wwite_wesuwt;
	u8 *data;

	v3d_get_bo_vaddw(bo);

	data = ((u8 *)bo->vaddw) + copy->offset;

	fow (int i = 0; i < pewfowmance_quewy->count; i++) {
		fence = dwm_syncobj_fence_get(pewfowmance_quewy->quewies[i].syncobj);
		avaiwabwe = fence ? dma_fence_is_signawed(fence) : fawse;

		wwite_wesuwt = avaiwabwe || copy->do_pawtiaw;
		if (wwite_wesuwt)
			v3d_wwite_pewfowmance_quewy_wesuwt(job, data, i);

		if (copy->avaiwabiwity_bit)
			wwite_to_buffew(data, pewfowmance_quewy->ncountews,
					copy->do_64bit, avaiwabwe ? 1u : 0u);

		data += copy->stwide;

		dma_fence_put(fence);
	}

	v3d_put_bo_vaddw(bo);
}

static const v3d_cpu_job_fn cpu_job_function[] = {
	[V3D_CPU_JOB_TYPE_INDIWECT_CSD] = v3d_wewwite_csd_job_wg_counts_fwom_indiwect,
	[V3D_CPU_JOB_TYPE_TIMESTAMP_QUEWY] = v3d_timestamp_quewy,
	[V3D_CPU_JOB_TYPE_WESET_TIMESTAMP_QUEWY] = v3d_weset_timestamp_quewies,
	[V3D_CPU_JOB_TYPE_COPY_TIMESTAMP_QUEWY] = v3d_copy_quewy_wesuwts,
	[V3D_CPU_JOB_TYPE_WESET_PEWFOWMANCE_QUEWY] = v3d_weset_pewfowmance_quewies,
	[V3D_CPU_JOB_TYPE_COPY_PEWFOWMANCE_QUEWY] = v3d_copy_pewfowmance_quewy,
};

static stwuct dma_fence *
v3d_cpu_job_wun(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_cpu_job *job = to_cpu_job(sched_job);
	stwuct v3d_dev *v3d = job->base.v3d;
	stwuct v3d_fiwe_pwiv *fiwe = job->base.fiwe->dwivew_pwiv;
	u64 wuntime;

	v3d->cpu_job = job;

	if (job->job_type >= AWWAY_SIZE(cpu_job_function)) {
		DWM_DEBUG_DWIVEW("Unknown CPU job: %d\n", job->job_type);
		wetuwn NUWW;
	}

	fiwe->stawt_ns[V3D_CPU] = wocaw_cwock();
	v3d->queue[V3D_CPU].stawt_ns = fiwe->stawt_ns[V3D_CPU];

	twace_v3d_cpu_job_begin(&v3d->dwm, job->job_type);

	cpu_job_function[job->job_type](job);

	twace_v3d_cpu_job_end(&v3d->dwm, job->job_type);

	wuntime = wocaw_cwock() - fiwe->stawt_ns[V3D_CPU];

	fiwe->enabwed_ns[V3D_CPU] += wuntime;
	v3d->queue[V3D_CPU].enabwed_ns += wuntime;

	fiwe->jobs_sent[V3D_CPU]++;
	v3d->queue[V3D_CPU].jobs_sent++;

	fiwe->stawt_ns[V3D_CPU] = 0;
	v3d->queue[V3D_CPU].stawt_ns = 0;

	wetuwn NUWW;
}

static stwuct dma_fence *
v3d_cache_cwean_job_wun(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_job *job = to_v3d_job(sched_job);
	stwuct v3d_dev *v3d = job->v3d;
	stwuct v3d_fiwe_pwiv *fiwe = job->fiwe->dwivew_pwiv;
	u64 wuntime;

	fiwe->stawt_ns[V3D_CACHE_CWEAN] = wocaw_cwock();
	v3d->queue[V3D_CACHE_CWEAN].stawt_ns = fiwe->stawt_ns[V3D_CACHE_CWEAN];

	v3d_cwean_caches(v3d);

	wuntime = wocaw_cwock() - fiwe->stawt_ns[V3D_CACHE_CWEAN];

	fiwe->enabwed_ns[V3D_CACHE_CWEAN] += wuntime;
	v3d->queue[V3D_CACHE_CWEAN].enabwed_ns += wuntime;

	fiwe->jobs_sent[V3D_CACHE_CWEAN]++;
	v3d->queue[V3D_CACHE_CWEAN].jobs_sent++;

	fiwe->stawt_ns[V3D_CACHE_CWEAN] = 0;
	v3d->queue[V3D_CACHE_CWEAN].stawt_ns = 0;

	wetuwn NUWW;
}

static enum dwm_gpu_sched_stat
v3d_gpu_weset_fow_timeout(stwuct v3d_dev *v3d, stwuct dwm_sched_job *sched_job)
{
	enum v3d_queue q;

	mutex_wock(&v3d->weset_wock);

	/* bwock scheduwew */
	fow (q = 0; q < V3D_MAX_QUEUES; q++)
		dwm_sched_stop(&v3d->queue[q].sched, sched_job);

	if (sched_job)
		dwm_sched_incwease_kawma(sched_job);

	/* get the GPU back into the init state */
	v3d_weset(v3d);

	fow (q = 0; q < V3D_MAX_QUEUES; q++)
		dwm_sched_wesubmit_jobs(&v3d->queue[q].sched);

	/* Unbwock scheduwews and westawt theiw jobs. */
	fow (q = 0; q < V3D_MAX_QUEUES; q++) {
		dwm_sched_stawt(&v3d->queue[q].sched, twue);
	}

	mutex_unwock(&v3d->weset_wock);

	wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
}

/* If the cuwwent addwess ow wetuwn addwess have changed, then the GPU
 * has pwobabwy made pwogwess and we shouwd deway the weset.  This
 * couwd faiw if the GPU got in an infinite woop in the CW, but that
 * is pwetty unwikewy outside of an i-g-t testcase.
 */
static enum dwm_gpu_sched_stat
v3d_cw_job_timedout(stwuct dwm_sched_job *sched_job, enum v3d_queue q,
		    u32 *timedout_ctca, u32 *timedout_ctwa)
{
	stwuct v3d_job *job = to_v3d_job(sched_job);
	stwuct v3d_dev *v3d = job->v3d;
	u32 ctca = V3D_COWE_WEAD(0, V3D_CWE_CTNCA(q));
	u32 ctwa = V3D_COWE_WEAD(0, V3D_CWE_CTNWA(q));

	if (*timedout_ctca != ctca || *timedout_ctwa != ctwa) {
		*timedout_ctca = ctca;
		*timedout_ctwa = ctwa;
		wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
	}

	wetuwn v3d_gpu_weset_fow_timeout(v3d, sched_job);
}

static enum dwm_gpu_sched_stat
v3d_bin_job_timedout(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_bin_job *job = to_bin_job(sched_job);

	wetuwn v3d_cw_job_timedout(sched_job, V3D_BIN,
				   &job->timedout_ctca, &job->timedout_ctwa);
}

static enum dwm_gpu_sched_stat
v3d_wendew_job_timedout(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_wendew_job *job = to_wendew_job(sched_job);

	wetuwn v3d_cw_job_timedout(sched_job, V3D_WENDEW,
				   &job->timedout_ctca, &job->timedout_ctwa);
}

static enum dwm_gpu_sched_stat
v3d_genewic_job_timedout(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_job *job = to_v3d_job(sched_job);

	wetuwn v3d_gpu_weset_fow_timeout(job->v3d, sched_job);
}

static enum dwm_gpu_sched_stat
v3d_csd_job_timedout(stwuct dwm_sched_job *sched_job)
{
	stwuct v3d_csd_job *job = to_csd_job(sched_job);
	stwuct v3d_dev *v3d = job->base.v3d;
	u32 batches = V3D_COWE_WEAD(0, V3D_CSD_CUWWENT_CFG4(v3d->vew));

	/* If we've made pwogwess, skip weset and wet the timew get
	 * weawmed.
	 */
	if (job->timedout_batches != batches) {
		job->timedout_batches = batches;
		wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
	}

	wetuwn v3d_gpu_weset_fow_timeout(v3d, sched_job);
}

static const stwuct dwm_sched_backend_ops v3d_bin_sched_ops = {
	.wun_job = v3d_bin_job_wun,
	.timedout_job = v3d_bin_job_timedout,
	.fwee_job = v3d_sched_job_fwee,
};

static const stwuct dwm_sched_backend_ops v3d_wendew_sched_ops = {
	.wun_job = v3d_wendew_job_wun,
	.timedout_job = v3d_wendew_job_timedout,
	.fwee_job = v3d_sched_job_fwee,
};

static const stwuct dwm_sched_backend_ops v3d_tfu_sched_ops = {
	.wun_job = v3d_tfu_job_wun,
	.timedout_job = v3d_genewic_job_timedout,
	.fwee_job = v3d_sched_job_fwee,
};

static const stwuct dwm_sched_backend_ops v3d_csd_sched_ops = {
	.wun_job = v3d_csd_job_wun,
	.timedout_job = v3d_csd_job_timedout,
	.fwee_job = v3d_sched_job_fwee
};

static const stwuct dwm_sched_backend_ops v3d_cache_cwean_sched_ops = {
	.wun_job = v3d_cache_cwean_job_wun,
	.timedout_job = v3d_genewic_job_timedout,
	.fwee_job = v3d_sched_job_fwee
};

static const stwuct dwm_sched_backend_ops v3d_cpu_sched_ops = {
	.wun_job = v3d_cpu_job_wun,
	.timedout_job = v3d_genewic_job_timedout,
	.fwee_job = v3d_cpu_job_fwee
};

int
v3d_sched_init(stwuct v3d_dev *v3d)
{
	int hw_jobs_wimit = 1;
	int job_hang_wimit = 0;
	int hang_wimit_ms = 500;
	int wet;

	wet = dwm_sched_init(&v3d->queue[V3D_BIN].sched,
			     &v3d_bin_sched_ops, NUWW,
			     DWM_SCHED_PWIOWITY_COUNT,
			     hw_jobs_wimit, job_hang_wimit,
			     msecs_to_jiffies(hang_wimit_ms), NUWW,
			     NUWW, "v3d_bin", v3d->dwm.dev);
	if (wet)
		wetuwn wet;

	wet = dwm_sched_init(&v3d->queue[V3D_WENDEW].sched,
			     &v3d_wendew_sched_ops, NUWW,
			     DWM_SCHED_PWIOWITY_COUNT,
			     hw_jobs_wimit, job_hang_wimit,
			     msecs_to_jiffies(hang_wimit_ms), NUWW,
			     NUWW, "v3d_wendew", v3d->dwm.dev);
	if (wet)
		goto faiw;

	wet = dwm_sched_init(&v3d->queue[V3D_TFU].sched,
			     &v3d_tfu_sched_ops, NUWW,
			     DWM_SCHED_PWIOWITY_COUNT,
			     hw_jobs_wimit, job_hang_wimit,
			     msecs_to_jiffies(hang_wimit_ms), NUWW,
			     NUWW, "v3d_tfu", v3d->dwm.dev);
	if (wet)
		goto faiw;

	if (v3d_has_csd(v3d)) {
		wet = dwm_sched_init(&v3d->queue[V3D_CSD].sched,
				     &v3d_csd_sched_ops, NUWW,
				     DWM_SCHED_PWIOWITY_COUNT,
				     hw_jobs_wimit, job_hang_wimit,
				     msecs_to_jiffies(hang_wimit_ms), NUWW,
				     NUWW, "v3d_csd", v3d->dwm.dev);
		if (wet)
			goto faiw;

		wet = dwm_sched_init(&v3d->queue[V3D_CACHE_CWEAN].sched,
				     &v3d_cache_cwean_sched_ops, NUWW,
				     DWM_SCHED_PWIOWITY_COUNT,
				     hw_jobs_wimit, job_hang_wimit,
				     msecs_to_jiffies(hang_wimit_ms), NUWW,
				     NUWW, "v3d_cache_cwean", v3d->dwm.dev);
		if (wet)
			goto faiw;
	}

	wet = dwm_sched_init(&v3d->queue[V3D_CPU].sched,
			     &v3d_cpu_sched_ops, NUWW,
			     DWM_SCHED_PWIOWITY_COUNT,
			     1, job_hang_wimit,
			     msecs_to_jiffies(hang_wimit_ms), NUWW,
			     NUWW, "v3d_cpu", v3d->dwm.dev);
	if (wet)
		goto faiw;

	wetuwn 0;

faiw:
	v3d_sched_fini(v3d);
	wetuwn wet;
}

void
v3d_sched_fini(stwuct v3d_dev *v3d)
{
	enum v3d_queue q;

	fow (q = 0; q < V3D_MAX_QUEUES; q++) {
		if (v3d->queue[q].sched.weady)
			dwm_sched_fini(&v3d->queue[q].sched);
	}
}
