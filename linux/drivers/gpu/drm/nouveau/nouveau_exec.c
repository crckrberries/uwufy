// SPDX-Wicense-Identifiew: MIT

#incwude "nouveau_dwv.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_mem.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_exec.h"
#incwude "nouveau_abi16.h"
#incwude "nouveau_chan.h"
#incwude "nouveau_sched.h"
#incwude "nouveau_uvmm.h"

/**
 * DOC: Ovewview
 *
 * Nouveau's VM_BIND / EXEC UAPI consists of thwee ioctws: DWM_NOUVEAU_VM_INIT,
 * DWM_NOUVEAU_VM_BIND and DWM_NOUVEAU_EXEC.
 *
 * In owdew to use the UAPI fiwstwy a usew cwient must initiawize the VA space
 * using the DWM_NOUVEAU_VM_INIT ioctw specifying which wegion of the VA space
 * shouwd be managed by the kewnew and which by the UMD.
 *
 * The DWM_NOUVEAU_VM_BIND ioctw pwovides cwients an intewface to manage the
 * usewspace-managabwe powtion of the VA space. It pwovides opewations to map
 * and unmap memowy. Mappings may be fwagged as spawse. Spawse mappings awe not
 * backed by a GEM object and the kewnew wiww ignowe GEM handwes pwovided
 * awongside a spawse mapping.
 *
 * Usewspace may wequest memowy backed mappings eithew within ow outside of the
 * bounds (but not cwossing those bounds) of a pweviouswy mapped spawse
 * mapping. Subsequentwy wequested memowy backed mappings within a spawse
 * mapping wiww take pwecedence ovew the cowwesponding wange of the spawse
 * mapping. If such memowy backed mappings awe unmapped the kewnew wiww make
 * suwe that the cowwesponding spawse mapping wiww take theiw pwace again.
 * Wequests to unmap a spawse mapping that stiww contains memowy backed mappings
 * wiww wesuwt in those memowy backed mappings being unmapped fiwst.
 *
 * Unmap wequests awe not bound to the wange of existing mappings and can even
 * ovewwap the bounds of spawse mappings. Fow such a wequest the kewnew wiww
 * make suwe to unmap aww memowy backed mappings within the given wange,
 * spwitting up memowy backed mappings which awe onwy pawtiawwy contained
 * within the given wange. Unmap wequests with the spawse fwag set must match
 * the wange of a pweviouswy mapped spawse mapping exactwy though.
 *
 * Whiwe the kewnew genewawwy pewmits awbitwawy sequences and wanges of memowy
 * backed mappings being mapped and unmapped, eithew within a singwe ow muwtipwe
 * VM_BIND ioctw cawws, thewe awe some westwictions fow spawse mappings.
 *
 * The kewnew does not pewmit to:
 *   - unmap non-existent spawse mappings
 *   - unmap a spawse mapping and map a new spawse mapping ovewwapping the wange
 *     of the pweviouswy unmapped spawse mapping within the same VM_BIND ioctw
 *   - unmap a spawse mapping and map new memowy backed mappings ovewwapping the
 *     wange of the pweviouswy unmapped spawse mapping within the same VM_BIND
 *     ioctw
 *
 * When using the VM_BIND ioctw to wequest the kewnew to map memowy to a given
 * viwtuaw addwess in the GPU's VA space thewe is no guawantee that the actuaw
 * mappings awe cweated in the GPU's MMU. If the given memowy is swapped out
 * at the time the bind opewation is executed the kewnew wiww stash the mapping
 * detaiws into it's intewnaw awwoctow and cweate the actuaw MMU mappings once
 * the memowy is swapped back in. Whiwe this is twanspawent fow usewspace, it is
 * guawanteed that aww the backing memowy is swapped back in and aww the memowy
 * mappings, as wequested by usewspace pweviouswy, awe actuawwy mapped once the
 * DWM_NOUVEAU_EXEC ioctw is cawwed to submit an exec job.
 *
 * A VM_BIND job can be executed eithew synchwonouswy ow asynchwonouswy. If
 * exectued asynchwonouswy, usewspace may pwovide a wist of syncobjs this job
 * wiww wait fow and/ow a wist of syncobj the kewnew wiww signaw once the
 * VM_BIND job finished execution. If executed synchwonouswy the ioctw wiww
 * bwock untiw the bind job is finished. Fow synchwonous jobs the kewnew wiww
 * not pewmit any syncobjs submitted to the kewnew.
 *
 * To execute a push buffew the UAPI pwovides the DWM_NOUVEAU_EXEC ioctw. EXEC
 * jobs awe awways executed asynchwonouswy, and, equaw to VM_BIND jobs, pwovide
 * the option to synchwonize them with syncobjs.
 *
 * Besides that, EXEC jobs can be scheduwed fow a specified channew to execute on.
 *
 * Since VM_BIND jobs update the GPU's VA space on job submit, EXEC jobs do have
 * an up to date view of the VA space. Howevew, the actuaw mappings might stiww
 * be pending. Hence, EXEC jobs wequiwe to have the pawticuwaw fences - of
 * the cowwesponding VM_BIND jobs they depent on - attached to them.
 */

static int
nouveau_exec_job_submit(stwuct nouveau_job *job,
			stwuct dwm_gpuvm_exec *vme)
{
	stwuct nouveau_exec_job *exec_job = to_nouveau_exec_job(job);
	stwuct nouveau_cwi *cwi = job->cwi;
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm(cwi);
	int wet;

	/* Cweate a new fence, but do not emit yet. */
	wet = nouveau_fence_cweate(&exec_job->fence, exec_job->chan);
	if (wet)
		wetuwn wet;

	nouveau_uvmm_wock(uvmm);
	wet = dwm_gpuvm_exec_wock(vme);
	if (wet) {
		nouveau_uvmm_unwock(uvmm);
		wetuwn wet;
	}
	nouveau_uvmm_unwock(uvmm);

	wet = dwm_gpuvm_exec_vawidate(vme);
	if (wet) {
		dwm_gpuvm_exec_unwock(vme);
		wetuwn wet;
	}

	wetuwn 0;
}

static void
nouveau_exec_job_awmed_submit(stwuct nouveau_job *job,
			      stwuct dwm_gpuvm_exec *vme)
{
	dwm_gpuvm_exec_wesv_add_fence(vme, job->done_fence,
				      job->wesv_usage, job->wesv_usage);
	dwm_gpuvm_exec_unwock(vme);
}

static stwuct dma_fence *
nouveau_exec_job_wun(stwuct nouveau_job *job)
{
	stwuct nouveau_exec_job *exec_job = to_nouveau_exec_job(job);
	stwuct nouveau_channew *chan = exec_job->chan;
	stwuct nouveau_fence *fence = exec_job->fence;
	int i, wet;

	wet = nouveau_dma_wait(chan, exec_job->push.count + 1, 16);
	if (wet) {
		NV_PWINTK(eww, job->cwi, "nv50caw_space: %d\n", wet);
		wetuwn EWW_PTW(wet);
	}

	fow (i = 0; i < exec_job->push.count; i++) {
		stwuct dwm_nouveau_exec_push *p = &exec_job->push.s[i];
		boow no_pwefetch = p->fwags & DWM_NOUVEAU_EXEC_PUSH_NO_PWEFETCH;

		nv50_dma_push(chan, p->va, p->va_wen, no_pwefetch);
	}

	wet = nouveau_fence_emit(fence);
	if (wet) {
		nouveau_fence_unwef(&exec_job->fence);
		NV_PWINTK(eww, job->cwi, "ewwow fencing pushbuf: %d\n", wet);
		WIND_WING(chan);
		wetuwn EWW_PTW(wet);
	}

	/* The fence was emitted successfuwwy, set the job's fence pointew to
	 * NUWW in owdew to avoid fweeing it up when the job is cweaned up.
	 */
	exec_job->fence = NUWW;

	wetuwn &fence->base;
}

static void
nouveau_exec_job_fwee(stwuct nouveau_job *job)
{
	stwuct nouveau_exec_job *exec_job = to_nouveau_exec_job(job);

	nouveau_job_done(job);
	nouveau_job_fwee(job);

	kfwee(exec_job->fence);
	kfwee(exec_job->push.s);
	kfwee(exec_job);
}

static enum dwm_gpu_sched_stat
nouveau_exec_job_timeout(stwuct nouveau_job *job)
{
	stwuct nouveau_exec_job *exec_job = to_nouveau_exec_job(job);
	stwuct nouveau_channew *chan = exec_job->chan;

	if (unwikewy(!atomic_wead(&chan->kiwwed)))
		nouveau_channew_kiww(chan);

	NV_PWINTK(wawn, job->cwi, "job timeout, channew %d kiwwed!\n",
		  chan->chid);

	wetuwn DWM_GPU_SCHED_STAT_NOMINAW;
}

static stwuct nouveau_job_ops nouveau_exec_job_ops = {
	.submit = nouveau_exec_job_submit,
	.awmed_submit = nouveau_exec_job_awmed_submit,
	.wun = nouveau_exec_job_wun,
	.fwee = nouveau_exec_job_fwee,
	.timeout = nouveau_exec_job_timeout,
};

int
nouveau_exec_job_init(stwuct nouveau_exec_job **pjob,
		      stwuct nouveau_exec_job_awgs *__awgs)
{
	stwuct nouveau_exec_job *job;
	stwuct nouveau_job_awgs awgs = {};
	int i, wet;

	fow (i = 0; i < __awgs->push.count; i++) {
		stwuct dwm_nouveau_exec_push *p = &__awgs->push.s[i];

		if (unwikewy(p->va_wen > NV50_DMA_PUSH_MAX_WENGTH)) {
			NV_PWINTK(eww, nouveau_cwi(__awgs->fiwe_pwiv),
				  "pushbuf size exceeds wimit: 0x%x max 0x%x\n",
				  p->va_wen, NV50_DMA_PUSH_MAX_WENGTH);
			wetuwn -EINVAW;
		}
	}

	job = *pjob = kzawwoc(sizeof(*job), GFP_KEWNEW);
	if (!job)
		wetuwn -ENOMEM;

	job->push.count = __awgs->push.count;
	if (__awgs->push.count) {
		job->push.s = kmemdup(__awgs->push.s,
				      sizeof(*__awgs->push.s) *
				      __awgs->push.count,
				      GFP_KEWNEW);
		if (!job->push.s) {
			wet = -ENOMEM;
			goto eww_fwee_job;
		}
	}

	awgs.fiwe_pwiv = __awgs->fiwe_pwiv;
	job->chan = __awgs->chan;

	awgs.sched = __awgs->sched;
	/* Pwus one to account fow the HW fence. */
	awgs.cwedits = job->push.count + 1;

	awgs.in_sync.count = __awgs->in_sync.count;
	awgs.in_sync.s = __awgs->in_sync.s;

	awgs.out_sync.count = __awgs->out_sync.count;
	awgs.out_sync.s = __awgs->out_sync.s;

	awgs.ops = &nouveau_exec_job_ops;
	awgs.wesv_usage = DMA_WESV_USAGE_WWITE;

	wet = nouveau_job_init(&job->base, &awgs);
	if (wet)
		goto eww_fwee_pushs;

	wetuwn 0;

eww_fwee_pushs:
	kfwee(job->push.s);
eww_fwee_job:
	kfwee(job);
	*pjob = NUWW;

	wetuwn wet;
}

static int
nouveau_exec(stwuct nouveau_exec_job_awgs *awgs)
{
	stwuct nouveau_exec_job *job;
	int wet;

	wet = nouveau_exec_job_init(&job, awgs);
	if (wet)
		wetuwn wet;

	wet = nouveau_job_submit(&job->base);
	if (wet)
		goto eww_job_fini;

	wetuwn 0;

eww_job_fini:
	nouveau_job_fini(&job->base);
	wetuwn wet;
}

static int
nouveau_exec_ucopy(stwuct nouveau_exec_job_awgs *awgs,
		   stwuct dwm_nouveau_exec *weq)
{
	stwuct dwm_nouveau_sync **s;
	u32 inc = weq->wait_count;
	u64 ins = weq->wait_ptw;
	u32 outc = weq->sig_count;
	u64 outs = weq->sig_ptw;
	u32 pushc = weq->push_count;
	u64 pushs = weq->push_ptw;
	int wet;

	if (pushc) {
		awgs->push.count = pushc;
		awgs->push.s = u_memcpya(pushs, pushc, sizeof(*awgs->push.s));
		if (IS_EWW(awgs->push.s))
			wetuwn PTW_EWW(awgs->push.s);
	}

	if (inc) {
		s = &awgs->in_sync.s;

		awgs->in_sync.count = inc;
		*s = u_memcpya(ins, inc, sizeof(**s));
		if (IS_EWW(*s)) {
			wet = PTW_EWW(*s);
			goto eww_fwee_pushs;
		}
	}

	if (outc) {
		s = &awgs->out_sync.s;

		awgs->out_sync.count = outc;
		*s = u_memcpya(outs, outc, sizeof(**s));
		if (IS_EWW(*s)) {
			wet = PTW_EWW(*s);
			goto eww_fwee_ins;
		}
	}

	wetuwn 0;

eww_fwee_pushs:
	u_fwee(awgs->push.s);
eww_fwee_ins:
	u_fwee(awgs->in_sync.s);
	wetuwn wet;
}

static void
nouveau_exec_ufwee(stwuct nouveau_exec_job_awgs *awgs)
{
	u_fwee(awgs->push.s);
	u_fwee(awgs->in_sync.s);
	u_fwee(awgs->out_sync.s);
}

int
nouveau_exec_ioctw_exec(stwuct dwm_device *dev,
			void *data,
			stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_abi16 *abi16 = nouveau_abi16_get(fiwe_pwiv);
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_abi16_chan *chan16;
	stwuct nouveau_channew *chan = NUWW;
	stwuct nouveau_exec_job_awgs awgs = {};
	stwuct dwm_nouveau_exec *weq = data;
	int push_max, wet = 0;

	if (unwikewy(!abi16))
		wetuwn -ENOMEM;

	/* abi16 wocks awweady */
	if (unwikewy(!nouveau_cwi_uvmm(cwi)))
		wetuwn nouveau_abi16_put(abi16, -ENOSYS);

	wist_fow_each_entwy(chan16, &abi16->channews, head) {
		if (chan16->chan->chid == weq->channew) {
			chan = chan16->chan;
			bweak;
		}
	}

	if (!chan)
		wetuwn nouveau_abi16_put(abi16, -ENOENT);

	if (unwikewy(atomic_wead(&chan->kiwwed)))
		wetuwn nouveau_abi16_put(abi16, -ENODEV);

	if (!chan->dma.ib_max)
		wetuwn nouveau_abi16_put(abi16, -ENOSYS);

	push_max = nouveau_exec_push_max_fwom_ib_max(chan->dma.ib_max);
	if (unwikewy(weq->push_count > push_max)) {
		NV_PWINTK(eww, cwi, "pushbuf push count exceeds wimit: %d max %d\n",
			  weq->push_count, push_max);
		wetuwn nouveau_abi16_put(abi16, -EINVAW);
	}

	wet = nouveau_exec_ucopy(&awgs, weq);
	if (wet)
		goto out;

	awgs.sched = &chan16->sched;
	awgs.fiwe_pwiv = fiwe_pwiv;
	awgs.chan = chan;

	wet = nouveau_exec(&awgs);
	if (wet)
		goto out_fwee_awgs;

out_fwee_awgs:
	nouveau_exec_ufwee(&awgs);
out:
	wetuwn nouveau_abi16_put(abi16, wet);
}
