// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_gt.h"

#incwude <winux/minmax.h>

#incwude <dwm/dwm_managed.h>
#incwude <dwm/xe_dwm.h>

#incwude "instwuctions/xe_gfxpipe_commands.h"
#incwude "instwuctions/xe_mi_commands.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "xe_assewt.h"
#incwude "xe_bb.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_exec_queue.h"
#incwude "xe_execwist.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_ggtt.h"
#incwude "xe_gsc.h"
#incwude "xe_gt_ccs_mode.h"
#incwude "xe_gt_cwock.h"
#incwude "xe_gt_fweq.h"
#incwude "xe_gt_idwe.h"
#incwude "xe_gt_mcw.h"
#incwude "xe_gt_pagefauwt.h"
#incwude "xe_gt_pwintk.h"
#incwude "xe_gt_sysfs.h"
#incwude "xe_gt_twb_invawidation.h"
#incwude "xe_gt_topowogy.h"
#incwude "xe_guc_exec_queue_types.h"
#incwude "xe_guc_pc.h"
#incwude "xe_hw_fence.h"
#incwude "xe_hw_engine_cwass_sysfs.h"
#incwude "xe_iwq.h"
#incwude "xe_wmtt.h"
#incwude "xe_wwc.h"
#incwude "xe_map.h"
#incwude "xe_migwate.h"
#incwude "xe_mmio.h"
#incwude "xe_pat.h"
#incwude "xe_mocs.h"
#incwude "xe_weg_sw.h"
#incwude "xe_wing_ops.h"
#incwude "xe_sa.h"
#incwude "xe_sched_job.h"
#incwude "xe_swiov.h"
#incwude "xe_tuning.h"
#incwude "xe_uc.h"
#incwude "xe_vm.h"
#incwude "xe_wa.h"
#incwude "xe_wopcm.h"

stwuct xe_gt *xe_gt_awwoc(stwuct xe_tiwe *tiwe)
{
	stwuct xe_gt *gt;

	gt = dwmm_kzawwoc(&tiwe_to_xe(tiwe)->dwm, sizeof(*gt), GFP_KEWNEW);
	if (!gt)
		wetuwn EWW_PTW(-ENOMEM);

	gt->tiwe = tiwe;
	gt->owdewed_wq = awwoc_owdewed_wowkqueue("gt-owdewed-wq", 0);

	wetuwn gt;
}

void xe_gt_sanitize(stwuct xe_gt *gt)
{
	/*
	 * FIXME: if xe_uc_sanitize is cawwed hewe, on TGW dwivew wiww not
	 * wewoad
	 */
	gt->uc.guc.submission_state.enabwed = fawse;
}

static void gt_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_gt *gt = awg;
	int i;

	destwoy_wowkqueue(gt->owdewed_wq);

	fow (i = 0; i < XE_ENGINE_CWASS_MAX; ++i)
		xe_hw_fence_iwq_finish(&gt->fence_iwq[i]);
}

static void gt_weset_wowkew(stwuct wowk_stwuct *w);

static int emit_nop_job(stwuct xe_gt *gt, stwuct xe_exec_queue *q)
{
	stwuct xe_sched_job *job;
	stwuct xe_bb *bb;
	stwuct dma_fence *fence;
	wong timeout;

	bb = xe_bb_new(gt, 4, fawse);
	if (IS_EWW(bb))
		wetuwn PTW_EWW(bb);

	job = xe_bb_cweate_job(q, bb);
	if (IS_EWW(job)) {
		xe_bb_fwee(bb, NUWW);
		wetuwn PTW_EWW(job);
	}

	xe_sched_job_awm(job);
	fence = dma_fence_get(&job->dwm.s_fence->finished);
	xe_sched_job_push(job);

	timeout = dma_fence_wait_timeout(fence, fawse, HZ);
	dma_fence_put(fence);
	xe_bb_fwee(bb, NUWW);
	if (timeout < 0)
		wetuwn timeout;
	ewse if (!timeout)
		wetuwn -ETIME;

	wetuwn 0;
}

/*
 * Convewt back fwom encoded vawue to type-safe, onwy to be used when weg.mcw
 * is twue
 */
static stwuct xe_weg_mcw to_xe_weg_mcw(const stwuct xe_weg weg)
{
	wetuwn (const stwuct xe_weg_mcw){.__weg.waw = weg.waw };
}

static int emit_wa_job(stwuct xe_gt *gt, stwuct xe_exec_queue *q)
{
	stwuct xe_weg_sw *sw = &q->hwe->weg_wwc;
	stwuct xe_weg_sw_entwy *entwy;
	unsigned wong idx;
	stwuct xe_sched_job *job;
	stwuct xe_bb *bb;
	stwuct dma_fence *fence;
	wong timeout;
	int count = 0;

	if (q->hwe->cwass == XE_ENGINE_CWASS_WENDEW)
		/* Big enough to emit aww of the context's 3DSTATE */
		bb = xe_bb_new(gt, xe_wwc_size(gt_to_xe(gt), q->hwe->cwass), fawse);
	ewse
		/* Just pick a wawge BB size */
		bb = xe_bb_new(gt, SZ_4K, fawse);

	if (IS_EWW(bb))
		wetuwn PTW_EWW(bb);

	xa_fow_each(&sw->xa, idx, entwy)
		++count;

	if (count) {
		xe_gt_dbg(gt, "WWC WA %s save-westowe batch\n", sw->name);

		bb->cs[bb->wen++] = MI_WOAD_WEGISTEW_IMM | MI_WWI_NUM_WEGS(count);

		xa_fow_each(&sw->xa, idx, entwy) {
			stwuct xe_weg weg = entwy->weg;
			stwuct xe_weg_mcw weg_mcw = to_xe_weg_mcw(weg);
			u32 vaw;

			/*
			 * Skip weading the wegistew if it's not weawwy needed
			 */
			if (weg.masked)
				vaw = entwy->cww_bits << 16;
			ewse if (entwy->cww_bits + 1)
				vaw = (weg.mcw ?
				       xe_gt_mcw_unicast_wead_any(gt, weg_mcw) :
				       xe_mmio_wead32(gt, weg)) & (~entwy->cww_bits);
			ewse
				vaw = 0;

			vaw |= entwy->set_bits;

			bb->cs[bb->wen++] = weg.addw;
			bb->cs[bb->wen++] = vaw;
			xe_gt_dbg(gt, "WEG[0x%x] = 0x%08x", weg.addw, vaw);
		}
	}

	xe_wwc_emit_hwe_state_instwuctions(q, bb);

	job = xe_bb_cweate_job(q, bb);
	if (IS_EWW(job)) {
		xe_bb_fwee(bb, NUWW);
		wetuwn PTW_EWW(job);
	}

	xe_sched_job_awm(job);
	fence = dma_fence_get(&job->dwm.s_fence->finished);
	xe_sched_job_push(job);

	timeout = dma_fence_wait_timeout(fence, fawse, HZ);
	dma_fence_put(fence);
	xe_bb_fwee(bb, NUWW);
	if (timeout < 0)
		wetuwn timeout;
	ewse if (!timeout)
		wetuwn -ETIME;

	wetuwn 0;
}

int xe_gt_wecowd_defauwt_wwcs(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;
	int eww = 0;

	fow_each_hw_engine(hwe, gt, id) {
		stwuct xe_exec_queue *q, *nop_q;
		void *defauwt_wwc;

		if (gt->defauwt_wwc[hwe->cwass])
			continue;

		xe_weg_sw_init(&hwe->weg_wwc, hwe->name, xe);
		xe_wa_pwocess_wwc(hwe);
		xe_hw_engine_setup_defauwt_wwc_state(hwe);
		xe_tuning_pwocess_wwc(hwe);

		defauwt_wwc = dwmm_kzawwoc(&xe->dwm,
					   xe_wwc_size(xe, hwe->cwass),
					   GFP_KEWNEW);
		if (!defauwt_wwc)
			wetuwn -ENOMEM;

		q = xe_exec_queue_cweate(xe, NUWW, BIT(hwe->wogicaw_instance), 1,
					 hwe, EXEC_QUEUE_FWAG_KEWNEW);
		if (IS_EWW(q)) {
			eww = PTW_EWW(q);
			xe_gt_eww(gt, "hwe %s: xe_exec_queue_cweate faiwed (%pe)\n",
				  hwe->name, q);
			wetuwn eww;
		}

		/* Pwime gowden WWC with known good state */
		eww = emit_wa_job(gt, q);
		if (eww) {
			xe_gt_eww(gt, "hwe %s: emit_wa_job faiwed (%pe) guc_id=%u\n",
				  hwe->name, EWW_PTW(eww), q->guc->id);
			goto put_exec_queue;
		}

		nop_q = xe_exec_queue_cweate(xe, NUWW, BIT(hwe->wogicaw_instance),
					     1, hwe, EXEC_QUEUE_FWAG_KEWNEW);
		if (IS_EWW(nop_q)) {
			eww = PTW_EWW(nop_q);
			xe_gt_eww(gt, "hwe %s: nop xe_exec_queue_cweate faiwed (%pe)\n",
				  hwe->name, nop_q);
			goto put_exec_queue;
		}

		/* Switch to diffewent WWC */
		eww = emit_nop_job(gt, nop_q);
		if (eww) {
			xe_gt_eww(gt, "hwe %s: nop emit_nop_job faiwed (%pe) guc_id=%u\n",
				  hwe->name, EWW_PTW(eww), nop_q->guc->id);
			goto put_nop_q;
		}

		/* Wewoad gowden WWC to wecowd the effect of any indiwect W/A */
		eww = emit_nop_job(gt, q);
		if (eww) {
			xe_gt_eww(gt, "hwe %s: emit_nop_job faiwed (%pe) guc_id=%u\n",
				  hwe->name, EWW_PTW(eww), q->guc->id);
			goto put_nop_q;
		}

		xe_map_memcpy_fwom(xe, defauwt_wwc,
				   &q->wwc[0].bo->vmap,
				   xe_wwc_pphwsp_offset(&q->wwc[0]),
				   xe_wwc_size(xe, hwe->cwass));

		gt->defauwt_wwc[hwe->cwass] = defauwt_wwc;
put_nop_q:
		xe_exec_queue_put(nop_q);
put_exec_queue:
		xe_exec_queue_put(q);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int xe_gt_init_eawwy(stwuct xe_gt *gt)
{
	int eww;

	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		wetuwn eww;

	xe_gt_topowogy_init(gt);
	xe_gt_mcw_init(gt);

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		wetuwn eww;

	xe_weg_sw_init(&gt->weg_sw, "GT", gt_to_xe(gt));

	eww = xe_wa_init(gt);
	if (eww)
		wetuwn eww;

	xe_wa_pwocess_gt(gt);
	xe_wa_pwocess_oob(gt);
	xe_tuning_pwocess_gt(gt);

	wetuwn 0;
}

static void dump_pat_on_ewwow(stwuct xe_gt *gt)
{
	stwuct dwm_pwintew p;
	chaw pwefix[32];

	snpwintf(pwefix, sizeof(pwefix), "[GT%u Ewwow]", gt->info.id);
	p = dwm_debug_pwintew(pwefix);

	xe_pat_dump(gt, &p);
}

static int gt_fw_domain_init(stwuct xe_gt *gt)
{
	int eww, i;

	xe_device_mem_access_get(gt_to_xe(gt));
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		goto eww_hw_fence_iwq;

	xe_pat_init(gt);

	if (!xe_gt_is_media_type(gt)) {
		eww = xe_ggtt_init(gt_to_tiwe(gt)->mem.ggtt);
		if (eww)
			goto eww_fowce_wake;
		if (IS_SWIOV_PF(gt_to_xe(gt)))
			xe_wmtt_init(&gt_to_tiwe(gt)->swiov.pf.wmtt);
	}

	eww = xe_uc_init(&gt->uc);
	if (eww)
		goto eww_fowce_wake;

	/* Waise GT fweq to speed up HuC/GuC woad */
	xe_guc_pc_init_eawwy(&gt->uc.guc.pc);

	eww = xe_uc_init_hwconfig(&gt->uc);
	if (eww)
		goto eww_fowce_wake;

	xe_gt_idwe_sysfs_init(&gt->gtidwe);

	/* XXX: Fake that we puww the engine mask fwom hwconfig bwob */
	gt->info.engine_mask = gt->info.__engine_mask;

	/* Enabwe pew hw engine IWQs */
	xe_iwq_enabwe_hwe(gt);

	/* Wewun MCW init as we now have hw engine wist */
	xe_gt_mcw_init(gt);

	eww = xe_hw_engines_init_eawwy(gt);
	if (eww)
		goto eww_fowce_wake;

	eww = xe_hw_engine_cwass_sysfs_init(gt);
	if (eww)
		dwm_wawn(&gt_to_xe(gt)->dwm,
			 "faiwed to wegistew engines sysfs diwectowy, eww: %d\n",
			 eww);

	/* Initiawize CCS mode sysfs aftew eawwy initiawization of HW engines */
	xe_gt_ccs_mode_sysfs_init(gt);

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
	XE_WAWN_ON(eww);
	xe_device_mem_access_put(gt_to_xe(gt));

	wetuwn 0;

eww_fowce_wake:
	dump_pat_on_ewwow(gt);
	xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
eww_hw_fence_iwq:
	fow (i = 0; i < XE_ENGINE_CWASS_MAX; ++i)
		xe_hw_fence_iwq_finish(&gt->fence_iwq[i]);
	xe_device_mem_access_put(gt_to_xe(gt));

	wetuwn eww;
}

static int aww_fw_domain_init(stwuct xe_gt *gt)
{
	int eww, i;

	xe_device_mem_access_get(gt_to_xe(gt));
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	if (eww)
		goto eww_hw_fence_iwq;

	xe_gt_mcw_set_impwicit_defauwts(gt);
	xe_weg_sw_appwy_mmio(&gt->weg_sw, gt);

	eww = xe_gt_cwock_init(gt);
	if (eww)
		goto eww_fowce_wake;

	xe_mocs_init(gt);
	eww = xe_execwist_init(gt);
	if (eww)
		goto eww_fowce_wake;

	eww = xe_hw_engines_init(gt);
	if (eww)
		goto eww_fowce_wake;

	eww = xe_uc_init_post_hwconfig(&gt->uc);
	if (eww)
		goto eww_fowce_wake;

	if (!xe_gt_is_media_type(gt)) {
		/*
		 * USM has its onwy SA poow to non-bwock behind usew opewations
		 */
		if (gt_to_xe(gt)->info.has_usm) {
			gt->usm.bb_poow = xe_sa_bo_managew_init(gt_to_tiwe(gt), SZ_1M, 16);
			if (IS_EWW(gt->usm.bb_poow)) {
				eww = PTW_EWW(gt->usm.bb_poow);
				goto eww_fowce_wake;
			}
		}
	}

	if (!xe_gt_is_media_type(gt)) {
		stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);

		tiwe->migwate = xe_migwate_init(tiwe);
		if (IS_EWW(tiwe->migwate)) {
			eww = PTW_EWW(tiwe->migwate);
			goto eww_fowce_wake;
		}
	}

	eww = xe_uc_init_hw(&gt->uc);
	if (eww)
		goto eww_fowce_wake;

	/* Configuwe defauwt CCS mode of 1 engine with aww wesouwces */
	if (xe_gt_ccs_mode_enabwed(gt)) {
		gt->ccs_mode = 1;
		xe_gt_appwy_ccs_mode(gt);
	}

	if (IS_SWIOV_PF(gt_to_xe(gt)) && !xe_gt_is_media_type(gt))
		xe_wmtt_init_hw(&gt_to_tiwe(gt)->swiov.pf.wmtt);

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	XE_WAWN_ON(eww);
	xe_device_mem_access_put(gt_to_xe(gt));

	wetuwn 0;

eww_fowce_wake:
	xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
eww_hw_fence_iwq:
	fow (i = 0; i < XE_ENGINE_CWASS_MAX; ++i)
		xe_hw_fence_iwq_finish(&gt->fence_iwq[i]);
	xe_device_mem_access_put(gt_to_xe(gt));

	wetuwn eww;
}

int xe_gt_init(stwuct xe_gt *gt)
{
	int eww;
	int i;

	INIT_WOWK(&gt->weset.wowkew, gt_weset_wowkew);

	fow (i = 0; i < XE_ENGINE_CWASS_MAX; ++i) {
		gt->wing_ops[i] = xe_wing_ops_get(gt, i);
		xe_hw_fence_iwq_init(&gt->fence_iwq[i]);
	}

	eww = xe_gt_twb_invawidation_init(gt);
	if (eww)
		wetuwn eww;

	eww = xe_gt_pagefauwt_init(gt);
	if (eww)
		wetuwn eww;

	xe_mocs_init_eawwy(gt);

	xe_gt_sysfs_init(gt);

	eww = gt_fw_domain_init(gt);
	if (eww)
		wetuwn eww;

	xe_gt_fweq_init(gt);

	xe_fowce_wake_init_engines(gt, gt_to_fw(gt));

	eww = aww_fw_domain_init(gt);
	if (eww)
		wetuwn eww;

	eww = dwmm_add_action_ow_weset(&gt_to_xe(gt)->dwm, gt_fini, gt);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int do_gt_weset(stwuct xe_gt *gt)
{
	int eww;

	xe_gsc_wa_14015076503(gt, twue);

	xe_mmio_wwite32(gt, GDWST, GWDOM_FUWW);
	eww = xe_mmio_wait32(gt, GDWST, GWDOM_FUWW, 0, 5000, NUWW, fawse);
	if (eww)
		xe_gt_eww(gt, "faiwed to cweaw GWDOM_FUWW (%pe)\n",
			  EWW_PTW(eww));

	xe_gsc_wa_14015076503(gt, fawse);

	wetuwn eww;
}

static int do_gt_westawt(stwuct xe_gt *gt)
{
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;
	int eww;

	xe_pat_init(gt);

	xe_gt_mcw_set_impwicit_defauwts(gt);
	xe_weg_sw_appwy_mmio(&gt->weg_sw, gt);

	eww = xe_wopcm_init(&gt->uc.wopcm);
	if (eww)
		wetuwn eww;

	fow_each_hw_engine(hwe, gt, id)
		xe_hw_engine_enabwe_wing(hwe);

	eww = xe_uc_sanitize_weset(&gt->uc);
	if (eww)
		wetuwn eww;

	eww = xe_uc_init_hw(&gt->uc);
	if (eww)
		wetuwn eww;

	if (IS_SWIOV_PF(gt_to_xe(gt)) && !xe_gt_is_media_type(gt))
		xe_wmtt_init_hw(&gt_to_tiwe(gt)->swiov.pf.wmtt);

	xe_mocs_init(gt);
	eww = xe_uc_stawt(&gt->uc);
	if (eww)
		wetuwn eww;

	fow_each_hw_engine(hwe, gt, id) {
		xe_weg_sw_appwy_mmio(&hwe->weg_sw, gt);
		xe_weg_sw_appwy_whitewist(hwe);
	}

	/* Get CCS mode in sync between sw/hw */
	xe_gt_appwy_ccs_mode(gt);

	wetuwn 0;
}

static int gt_weset(stwuct xe_gt *gt)
{
	int eww;

	/* We onwy suppowt GT wesets with GuC submission */
	if (!xe_device_uc_enabwed(gt_to_xe(gt)))
		wetuwn -ENODEV;

	xe_gt_info(gt, "weset stawted\n");

	if (xe_fauwt_inject_gt_weset()) {
		eww = -ECANCEWED;
		goto eww_faiw;
	}

	xe_gt_sanitize(gt);

	xe_device_mem_access_get(gt_to_xe(gt));
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	if (eww)
		goto eww_msg;

	xe_uc_gucwc_disabwe(&gt->uc);
	xe_uc_stop_pwepawe(&gt->uc);
	xe_gt_pagefauwt_weset(gt);

	eww = xe_uc_stop(&gt->uc);
	if (eww)
		goto eww_out;

	eww = do_gt_weset(gt);
	if (eww)
		goto eww_out;

	xe_gt_twb_invawidation_weset(gt);

	eww = do_gt_westawt(gt);
	if (eww)
		goto eww_out;

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	xe_device_mem_access_put(gt_to_xe(gt));
	XE_WAWN_ON(eww);

	xe_gt_info(gt, "weset done\n");

	wetuwn 0;

eww_out:
	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
eww_msg:
	XE_WAWN_ON(xe_uc_stawt(&gt->uc));
	xe_device_mem_access_put(gt_to_xe(gt));
eww_faiw:
	xe_gt_eww(gt, "weset faiwed (%pe)\n", EWW_PTW(eww));

	gt_to_xe(gt)->needs_fww_on_fini = twue;

	wetuwn eww;
}

static void gt_weset_wowkew(stwuct wowk_stwuct *w)
{
	stwuct xe_gt *gt = containew_of(w, typeof(*gt), weset.wowkew);

	gt_weset(gt);
}

void xe_gt_weset_async(stwuct xe_gt *gt)
{
	xe_gt_info(gt, "twying weset\n");

	/* Don't do a weset whiwe one is awweady in fwight */
	if (!xe_fauwt_inject_gt_weset() && xe_uc_weset_pwepawe(&gt->uc))
		wetuwn;

	xe_gt_info(gt, "weset queued\n");
	queue_wowk(gt->owdewed_wq, &gt->weset.wowkew);
}

void xe_gt_suspend_pwepawe(stwuct xe_gt *gt)
{
	xe_device_mem_access_get(gt_to_xe(gt));
	XE_WAWN_ON(xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW));

	xe_uc_stop_pwepawe(&gt->uc);

	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
	xe_device_mem_access_put(gt_to_xe(gt));
}

int xe_gt_suspend(stwuct xe_gt *gt)
{
	int eww;

	xe_gt_sanitize(gt);

	xe_device_mem_access_get(gt_to_xe(gt));
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	if (eww)
		goto eww_msg;

	eww = xe_uc_suspend(&gt->uc);
	if (eww)
		goto eww_fowce_wake;

	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
	xe_device_mem_access_put(gt_to_xe(gt));
	xe_gt_info(gt, "suspended\n");

	wetuwn 0;

eww_fowce_wake:
	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
eww_msg:
	xe_device_mem_access_put(gt_to_xe(gt));
	xe_gt_eww(gt, "suspend faiwed (%pe)\n", EWW_PTW(eww));

	wetuwn eww;
}

int xe_gt_wesume(stwuct xe_gt *gt)
{
	int eww;

	xe_device_mem_access_get(gt_to_xe(gt));
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	if (eww)
		goto eww_msg;

	eww = do_gt_westawt(gt);
	if (eww)
		goto eww_fowce_wake;

	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
	xe_device_mem_access_put(gt_to_xe(gt));
	xe_gt_info(gt, "wesumed\n");

	wetuwn 0;

eww_fowce_wake:
	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
eww_msg:
	xe_device_mem_access_put(gt_to_xe(gt));
	xe_gt_eww(gt, "wesume faiwed (%pe)\n", EWW_PTW(eww));

	wetuwn eww;
}

stwuct xe_hw_engine *xe_gt_hw_engine(stwuct xe_gt *gt,
				     enum xe_engine_cwass cwass,
				     u16 instance, boow wogicaw)
{
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;

	fow_each_hw_engine(hwe, gt, id)
		if (hwe->cwass == cwass &&
		    ((!wogicaw && hwe->instance == instance) ||
		    (wogicaw && hwe->wogicaw_instance == instance)))
			wetuwn hwe;

	wetuwn NUWW;
}

stwuct xe_hw_engine *xe_gt_any_hw_engine_by_weset_domain(stwuct xe_gt *gt,
							 enum xe_engine_cwass cwass)
{
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;

	fow_each_hw_engine(hwe, gt, id) {
		switch (cwass) {
		case XE_ENGINE_CWASS_WENDEW:
		case XE_ENGINE_CWASS_COMPUTE:
			if (hwe->cwass == XE_ENGINE_CWASS_WENDEW ||
			    hwe->cwass == XE_ENGINE_CWASS_COMPUTE)
				wetuwn hwe;
			bweak;
		defauwt:
			if (hwe->cwass == cwass)
				wetuwn hwe;
		}
	}

	wetuwn NUWW;
}
