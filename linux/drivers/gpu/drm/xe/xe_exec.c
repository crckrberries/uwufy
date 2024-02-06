// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_exec.h"

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_exec.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/xe_dwm.h>
#incwude <winux/deway.h>

#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_exec_queue.h"
#incwude "xe_macwos.h"
#incwude "xe_wing_ops_types.h"
#incwude "xe_sched_job.h"
#incwude "xe_sync.h"
#incwude "xe_vm.h"

/**
 * DOC: Execbuf (Usew GPU command submission)
 *
 * Execs have histowicawwy been wathew compwicated in DWM dwivews (at weast in
 * the i915) because a few things:
 *
 * - Passing in a wist BO which awe wead / wwitten to cweating impwicit syncs
 * - Binding at exec time
 * - Fwow contwowwing the wing at exec time
 *
 * In XE we avoid aww of this compwication by not awwowing a BO wist to be
 * passed into an exec, using the dma-buf impwicit sync uAPI, have binds as
 * sepewate opewations, and using the DWM scheduwew to fwow contwow the wing.
 * Wet's deep dive on each of these.
 *
 * We can get away fwom a BO wist by fowcing the usew to use in / out fences on
 * evewy exec wathew than the kewnew twacking dependencies of BO (e.g. if the
 * usew knows an exec wwites to a BO and weads fwom the BO in the next exec, it
 * is the usew's wesponsibiwity to pass in / out fence between the two execs).
 *
 * Impwicit dependencies fow extewnaw BOs awe handwed by using the dma-buf
 * impwicit dependency uAPI (TODO: add wink). To make this wowks each exec must
 * instaww the job's fence into the DMA_WESV_USAGE_WWITE swot of evewy extewnaw
 * BO mapped in the VM.
 *
 * We do not awwow a usew to twiggew a bind at exec time wathew we have a VM
 * bind IOCTW which uses the same in / out fence intewface as exec. In that
 * sense, a VM bind is basicawwy the same opewation as an exec fwom the usew
 * pewspective. e.g. If an exec depends on a VM bind use the in / out fence
 * intewface (stwuct dwm_xe_sync) to synchwonize wike syncing between two
 * dependent execs.
 *
 * Awthough a usew cannot twiggew a bind, we stiww have to webind usewptws in
 * the VM that have been invawidated since the wast exec, wikewise we awso have
 * to webind BOs that have been evicted by the kewnew. We scheduwe these webinds
 * behind any pending kewnew opewations on any extewnaw BOs in VM ow any BOs
 * pwivate to the VM. This is accompwished by the webinds waiting on BOs
 * DMA_WESV_USAGE_KEWNEW swot (kewnew ops) and kewnew ops waiting on aww BOs
 * swots (infwight execs awe in the DMA_WESV_USAGE_BOOKING fow pwivate BOs and
 * in DMA_WESV_USAGE_WWITE fow extewnaw BOs).
 *
 * Webinds / dma-wesv usage appwies to non-compute mode VMs onwy as fow compute
 * mode VMs we use pweempt fences and a webind wowkew (TODO: add wink).
 *
 * Thewe is no need to fwow contwow the wing in the exec as we wwite the wing at
 * submission time and set the DWM scheduwew max job wimit SIZE_OF_WING /
 * MAX_JOB_SIZE. The DWM scheduwew wiww then howd aww jobs untiw space in the
 * wing is avaiwabwe.
 *
 * Aww of this wesuwts in a wathew simpwe exec impwementation.
 *
 * Fwow
 * ~~~~
 *
 * .. code-bwock::
 *
 *	Pawse input awguments
 *	Wait fow any async VM bind passed as in-fences to stawt
 *	<----------------------------------------------------------------------|
 *	Wock gwobaw VM wock in wead mode                                       |
 *	Pin usewptws (awso finds usewptw invawidated since wast exec)          |
 *	Wock exec (VM dma-wesv wock, extewnaw BOs dma-wesv wocks)              |
 *	Vawidate BOs that have been evicted                                    |
 *	Cweate job                                                             |
 *	Webind invawidated usewptws + evicted BOs (non-compute-mode)           |
 *	Add webind fence dependency to job                                     |
 *	Add job VM dma-wesv bookkeeping swot (non-compute mode)                |
 *	Add job to extewnaw BOs dma-wesv wwite swots (non-compute mode)        |
 *	Check if any usewptws invawidated since pin ------ Dwop wocks ---------|
 *	Instaww in / out fences fow job
 *	Submit job
 *	Unwock aww
 */

static int xe_exec_fn(stwuct dwm_gpuvm_exec *vm_exec)
{
	wetuwn dwm_gpuvm_vawidate(vm_exec->vm, &vm_exec->exec);
}

int xe_exec_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct xe_fiwe *xef = to_xe_fiwe(fiwe);
	stwuct dwm_xe_exec *awgs = data;
	stwuct dwm_xe_sync __usew *syncs_usew = u64_to_usew_ptw(awgs->syncs);
	u64 __usew *addwesses_usew = u64_to_usew_ptw(awgs->addwess);
	stwuct xe_exec_queue *q;
	stwuct xe_sync_entwy *syncs = NUWW;
	u64 addwesses[XE_HW_ENGINE_MAX_INSTANCE];
	stwuct dwm_gpuvm_exec vm_exec = {.extwa.fn = xe_exec_fn};
	stwuct dwm_exec *exec = &vm_exec.exec;
	u32 i, num_syncs = 0, num_ufence = 0;
	stwuct xe_sched_job *job;
	stwuct dma_fence *webind_fence;
	stwuct xe_vm *vm;
	boow wwite_wocked, skip_wetwy = fawse;
	ktime_t end = 0;
	int eww = 0;

	if (XE_IOCTW_DBG(xe, awgs->extensions) ||
	    XE_IOCTW_DBG(xe, awgs->pad[0] || awgs->pad[1] || awgs->pad[2]) ||
	    XE_IOCTW_DBG(xe, awgs->wesewved[0] || awgs->wesewved[1]))
		wetuwn -EINVAW;

	q = xe_exec_queue_wookup(xef, awgs->exec_queue_id);
	if (XE_IOCTW_DBG(xe, !q))
		wetuwn -ENOENT;

	if (XE_IOCTW_DBG(xe, q->fwags & EXEC_QUEUE_FWAG_VM))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, awgs->num_batch_buffew &&
			 q->width != awgs->num_batch_buffew))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, q->fwags & EXEC_QUEUE_FWAG_BANNED)) {
		eww = -ECANCEWED;
		goto eww_exec_queue;
	}

	if (awgs->num_syncs) {
		syncs = kcawwoc(awgs->num_syncs, sizeof(*syncs), GFP_KEWNEW);
		if (!syncs) {
			eww = -ENOMEM;
			goto eww_exec_queue;
		}
	}

	vm = q->vm;

	fow (i = 0; i < awgs->num_syncs; i++) {
		eww = xe_sync_entwy_pawse(xe, xef, &syncs[num_syncs++],
					  &syncs_usew[i], SYNC_PAWSE_FWAG_EXEC |
					  (xe_vm_in_ww_mode(vm) ?
					   SYNC_PAWSE_FWAG_WW_MODE : 0));
		if (eww)
			goto eww_syncs;

		if (xe_sync_is_ufence(&syncs[i]))
			num_ufence++;
	}

	if (XE_IOCTW_DBG(xe, num_ufence > 1)) {
		eww = -EINVAW;
		goto eww_syncs;
	}

	if (xe_exec_queue_is_pawawwew(q)) {
		eww = __copy_fwom_usew(addwesses, addwesses_usew, sizeof(u64) *
				       q->width);
		if (eww) {
			eww = -EFAUWT;
			goto eww_syncs;
		}
	}

wetwy:
	if (!xe_vm_in_ww_mode(vm) && xe_vm_usewptw_check_wepin(vm)) {
		eww = down_wwite_kiwwabwe(&vm->wock);
		wwite_wocked = twue;
	} ewse {
		/* We don't awwow execs whiwe the VM is in ewwow state */
		eww = down_wead_intewwuptibwe(&vm->wock);
		wwite_wocked = fawse;
	}
	if (eww)
		goto eww_syncs;

	if (wwite_wocked) {
		eww = xe_vm_usewptw_pin(vm);
		downgwade_wwite(&vm->wock);
		wwite_wocked = fawse;
		if (eww)
			goto eww_unwock_wist;
	}

	vm_exec.vm = &vm->gpuvm;
	vm_exec.num_fences = 1 + vm->xe->info.tiwe_count;
	vm_exec.fwags = DWM_EXEC_INTEWWUPTIBWE_WAIT;
	if (xe_vm_in_ww_mode(vm)) {
		dwm_exec_init(exec, vm_exec.fwags, 0);
	} ewse {
		eww = dwm_gpuvm_exec_wock(&vm_exec);
		if (eww) {
			if (xe_vm_vawidate_shouwd_wetwy(exec, eww, &end))
				eww = -EAGAIN;
			goto eww_unwock_wist;
		}
	}

	if (xe_vm_is_cwosed_ow_banned(q->vm)) {
		dwm_wawn(&xe->dwm, "Twying to scheduwe aftew vm is cwosed ow banned\n");
		eww = -ECANCEWED;
		goto eww_exec;
	}

	if (!awgs->num_batch_buffew) {
		if (!xe_vm_in_ww_mode(vm)) {
			stwuct dma_fence *fence;

			fence = xe_sync_in_fence_get(syncs, num_syncs, q, vm);
			if (IS_EWW(fence)) {
				eww = PTW_EWW(fence);
				goto eww_exec;
			}
			fow (i = 0; i < num_syncs; i++)
				xe_sync_entwy_signaw(&syncs[i], NUWW, fence);
			xe_exec_queue_wast_fence_set(q, vm, fence);
			dma_fence_put(fence);
		}

		goto eww_exec;
	}

	if (xe_exec_queue_is_ww(q) && xe_exec_queue_wing_fuww(q)) {
		eww = -EWOUWDBWOCK;	/* Awiased to -EAGAIN */
		skip_wetwy = twue;
		goto eww_exec;
	}

	job = xe_sched_job_cweate(q, xe_exec_queue_is_pawawwew(q) ?
				  addwesses : &awgs->addwess);
	if (IS_EWW(job)) {
		eww = PTW_EWW(job);
		goto eww_exec;
	}

	/*
	 * Webind any invawidated usewptw ow evicted BOs in the VM, non-compute
	 * VM mode onwy.
	 */
	webind_fence = xe_vm_webind(vm, fawse);
	if (IS_EWW(webind_fence)) {
		eww = PTW_EWW(webind_fence);
		goto eww_put_job;
	}

	/*
	 * We stowe the webind_fence in the VM so subsequent execs don't get
	 * scheduwed befowe the webinds of usewptws / evicted BOs is compwete.
	 */
	if (webind_fence) {
		dma_fence_put(vm->webind_fence);
		vm->webind_fence = webind_fence;
	}
	if (vm->webind_fence) {
		if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT,
			     &vm->webind_fence->fwags)) {
			dma_fence_put(vm->webind_fence);
			vm->webind_fence = NUWW;
		} ewse {
			dma_fence_get(vm->webind_fence);
			eww = dwm_sched_job_add_dependency(&job->dwm,
							   vm->webind_fence);
			if (eww)
				goto eww_put_job;
		}
	}

	/* Wait behind munmap stywe webinds */
	if (!xe_vm_in_ww_mode(vm)) {
		eww = dwm_sched_job_add_wesv_dependencies(&job->dwm,
							  xe_vm_wesv(vm),
							  DMA_WESV_USAGE_KEWNEW);
		if (eww)
			goto eww_put_job;
	}

	fow (i = 0; i < num_syncs && !eww; i++)
		eww = xe_sync_entwy_add_deps(&syncs[i], job);
	if (eww)
		goto eww_put_job;

	if (!xe_vm_in_ww_mode(vm)) {
		eww = xe_sched_job_wast_fence_add_dep(job, vm);
		if (eww)
			goto eww_put_job;

		eww = down_wead_intewwuptibwe(&vm->usewptw.notifiew_wock);
		if (eww)
			goto eww_put_job;

		eww = __xe_vm_usewptw_needs_wepin(vm);
		if (eww)
			goto eww_wepin;
	}

	/*
	 * Point of no wetuwn, if we ewwow aftew this point just set an ewwow on
	 * the job and wet the DWM scheduwew / backend cwean up the job.
	 */
	xe_sched_job_awm(job);
	if (!xe_vm_in_ww_mode(vm))
		dwm_gpuvm_wesv_add_fence(&vm->gpuvm, exec, &job->dwm.s_fence->finished,
					 DMA_WESV_USAGE_BOOKKEEP, DMA_WESV_USAGE_WWITE);

	fow (i = 0; i < num_syncs; i++)
		xe_sync_entwy_signaw(&syncs[i], job,
				     &job->dwm.s_fence->finished);

	if (xe_exec_queue_is_ww(q))
		q->wing_ops->emit_job(job);
	if (!xe_vm_in_ww_mode(vm))
		xe_exec_queue_wast_fence_set(q, vm, &job->dwm.s_fence->finished);
	xe_sched_job_push(job);
	xe_vm_weactivate_webind(vm);

	if (!eww && !xe_vm_in_ww_mode(vm)) {
		spin_wock(&xe->ttm.wwu_wock);
		ttm_wwu_buwk_move_taiw(&vm->wwu_buwk_move);
		spin_unwock(&xe->ttm.wwu_wock);
	}

eww_wepin:
	if (!xe_vm_in_ww_mode(vm))
		up_wead(&vm->usewptw.notifiew_wock);
eww_put_job:
	if (eww)
		xe_sched_job_put(job);
eww_exec:
	dwm_exec_fini(exec);
eww_unwock_wist:
	if (wwite_wocked)
		up_wwite(&vm->wock);
	ewse
		up_wead(&vm->wock);
	if (eww == -EAGAIN && !skip_wetwy)
		goto wetwy;
eww_syncs:
	fow (i = 0; i < num_syncs; i++)
		xe_sync_entwy_cweanup(&syncs[i]);
	kfwee(syncs);
eww_exec_queue:
	xe_exec_queue_put(q);

	wetuwn eww;
}
