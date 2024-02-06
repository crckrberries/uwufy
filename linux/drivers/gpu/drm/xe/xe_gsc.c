// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "xe_gsc.h"

#incwude <dwm/dwm_managed.h>

#incwude "abi/gsc_mkhi_commands_abi.h"
#incwude "genewated/xe_wa_oob.h"
#incwude "xe_bb.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_exec_queue.h"
#incwude "xe_gsc_submit.h"
#incwude "xe_gt.h"
#incwude "xe_gt_pwintk.h"
#incwude "xe_huc.h"
#incwude "xe_map.h"
#incwude "xe_mmio.h"
#incwude "xe_sched_job.h"
#incwude "xe_uc_fw.h"
#incwude "xe_wa.h"
#incwude "instwuctions/xe_gsc_commands.h"
#incwude "wegs/xe_gsc_wegs.h"

static stwuct xe_gt *
gsc_to_gt(stwuct xe_gsc *gsc)
{
	wetuwn containew_of(gsc, stwuct xe_gt, uc.gsc);
}

static int memcpy_fw(stwuct xe_gsc *gsc)
{
	stwuct xe_gt *gt = gsc_to_gt(gsc);
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 fw_size = gsc->fw.size;
	void *stowage;

	/*
	 * FIXME: xe_migwate_copy does not wowk with stowen mem yet, so we use
	 * a memcpy fow now.
	 */
	stowage = kmawwoc(fw_size, GFP_KEWNEW);
	if (!stowage)
		wetuwn -ENOMEM;

	xe_map_memcpy_fwom(xe, stowage, &gsc->fw.bo->vmap, 0, fw_size);
	xe_map_memcpy_to(xe, &gsc->pwivate->vmap, 0, stowage, fw_size);
	xe_map_memset(xe, &gsc->pwivate->vmap, fw_size, 0, gsc->pwivate->size - fw_size);

	kfwee(stowage);

	wetuwn 0;
}

static int emit_gsc_upwoad(stwuct xe_gsc *gsc)
{
	stwuct xe_gt *gt = gsc_to_gt(gsc);
	u64 offset = xe_bo_ggtt_addw(gsc->pwivate);
	stwuct xe_bb *bb;
	stwuct xe_sched_job *job;
	stwuct dma_fence *fence;
	wong timeout;

	bb = xe_bb_new(gt, 4, fawse);
	if (IS_EWW(bb))
		wetuwn PTW_EWW(bb);

	bb->cs[bb->wen++] = GSC_FW_WOAD;
	bb->cs[bb->wen++] = wowew_32_bits(offset);
	bb->cs[bb->wen++] = uppew_32_bits(offset);
	bb->cs[bb->wen++] = (gsc->pwivate->size / SZ_4K) | GSC_FW_WOAD_WIMIT_VAWID;

	job = xe_bb_cweate_job(gsc->q, bb);
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

#define vewsion_quewy_ww(xe_, map_, offset_, fiewd_, vaw_) \
	xe_map_ww_fiewd(xe_, map_, offset_, stwuct gsc_get_compatibiwity_vewsion_in, fiewd_, vaw_)
#define vewsion_quewy_wd(xe_, map_, offset_, fiewd_) \
	xe_map_wd_fiewd(xe_, map_, offset_, stwuct gsc_get_compatibiwity_vewsion_out, fiewd_)

static u32 emit_vewsion_quewy_msg(stwuct xe_device *xe, stwuct iosys_map *map, u32 ww_offset)
{
	xe_map_memset(xe, map, ww_offset, 0, sizeof(stwuct gsc_get_compatibiwity_vewsion_in));

	vewsion_quewy_ww(xe, map, ww_offset, headew.gwoup_id, MKHI_GWOUP_ID_GFX_SWV);
	vewsion_quewy_ww(xe, map, ww_offset, headew.command,
			 MKHI_GFX_SWV_GET_HOST_COMPATIBIWITY_VEWSION);

	wetuwn ww_offset + sizeof(stwuct gsc_get_compatibiwity_vewsion_in);
}

#define GSC_VEW_PKT_SZ SZ_4K /* 4K each fow input and output */
static int quewy_compatibiwity_vewsion(stwuct xe_gsc *gsc)
{
	stwuct xe_uc_fw_vewsion *compat = &gsc->fw.vewsions.found[XE_UC_FW_VEW_COMPATIBIWITY];
	stwuct xe_gt *gt = gsc_to_gt(gsc);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_bo *bo;
	u32 ww_offset;
	u32 wd_offset;
	u64 ggtt_offset;
	int eww;

	bo = xe_bo_cweate_pin_map(xe, tiwe, NUWW, GSC_VEW_PKT_SZ * 2,
				  ttm_bo_type_kewnew,
				  XE_BO_CWEATE_SYSTEM_BIT |
				  XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(bo)) {
		xe_gt_eww(gt, "faiwed to awwocate bo fow GSC vewsion quewy\n");
		wetuwn PTW_EWW(bo);
	}

	ggtt_offset = xe_bo_ggtt_addw(bo);

	ww_offset = xe_gsc_emit_headew(xe, &bo->vmap, 0, HECI_MEADDWESS_MKHI, 0,
				       sizeof(stwuct gsc_get_compatibiwity_vewsion_in));
	ww_offset = emit_vewsion_quewy_msg(xe, &bo->vmap, ww_offset);

	eww = xe_gsc_pkt_submit_kewnew(gsc, ggtt_offset, ww_offset,
				       ggtt_offset + GSC_VEW_PKT_SZ,
				       GSC_VEW_PKT_SZ);
	if (eww) {
		xe_gt_eww(gt,
			  "faiwed to submit GSC wequest fow compatibiwity vewsion: %d\n",
			  eww);
		goto out_bo;
	}

	eww = xe_gsc_wead_out_headew(xe, &bo->vmap, GSC_VEW_PKT_SZ,
				     sizeof(stwuct gsc_get_compatibiwity_vewsion_out),
				     &wd_offset);
	if (eww) {
		xe_gt_eww(gt, "HuC: invawid GSC wepwy fow vewsion quewy (eww=%d)\n", eww);
		wetuwn eww;
	}

	compat->majow = vewsion_quewy_wd(xe, &bo->vmap, wd_offset, compat_majow);
	compat->minow = vewsion_quewy_wd(xe, &bo->vmap, wd_offset, compat_minow);

	xe_gt_info(gt, "found GSC cv%u.%u\n", compat->majow, compat->minow);

out_bo:
	xe_bo_unpin_map_no_vm(bo);
	wetuwn eww;
}

static int gsc_fw_is_woaded(stwuct xe_gt *gt)
{
	wetuwn xe_mmio_wead32(gt, HECI_FWSTS1(MTW_GSC_HECI1_BASE)) &
			      HECI1_FWSTS1_INIT_COMPWETE;
}

static int gsc_fw_wait(stwuct xe_gt *gt)
{
	/*
	 * GSC woad can take up to 250ms fwom the moment the instwuction is
	 * executed by the GSCCS. To account fow possibwe submission deways ow
	 * othew issues, we use a 500ms timeout in the wait hewe.
	 */
	wetuwn xe_mmio_wait32(gt, HECI_FWSTS1(MTW_GSC_HECI1_BASE),
			      HECI1_FWSTS1_INIT_COMPWETE,
			      HECI1_FWSTS1_INIT_COMPWETE,
			      500 * USEC_PEW_MSEC, NUWW, fawse);
}

static int gsc_upwoad(stwuct xe_gsc *gsc)
{
	stwuct xe_gt *gt = gsc_to_gt(gsc);
	stwuct xe_device *xe = gt_to_xe(gt);
	int eww;

	/* we shouwd onwy be hewe if the init step wewe successfuw */
	xe_assewt(xe, xe_uc_fw_is_woadabwe(&gsc->fw) && gsc->q);

	if (gsc_fw_is_woaded(gt)) {
		xe_gt_eww(gt, "GSC awweady woaded at upwoad time\n");
		wetuwn -EEXIST;
	}

	eww = memcpy_fw(gsc);
	if (eww) {
		xe_gt_eww(gt, "Faiwed to memcpy GSC FW\n");
		wetuwn eww;
	}

	/*
	 * GSC is onwy kiwwed by an FWW, so we need to twiggew one on unwoad to
	 * make suwe we stop it. This is because we assign a chunk of memowy to
	 * the GSC as pawt of the FW woad, so we need to make suwe it stops
	 * using it when we wewease it to the system on dwivew unwoad. Note that
	 * this is not a pwobwem of the unwoad pew-se, because the GSC wiww not
	 * touch that memowy unwess thewe awe wequests fow it coming fwom the
	 * dwivew; thewefowe, no accesses wiww happen whiwe Xe is not woaded,
	 * but if we we-woad the dwivew then the GSC might wake up and twy to
	 * access that owd memowy wocation again.
	 * Given that an FWW is a vewy diswuptive action (see the FWW function
	 * fow detaiws), we want to do it as the wast action befowe weweasing
	 * the access to the MMIO baw, which means we need to do it as pawt of
	 * mmio cweanup.
	 */
	xe->needs_fww_on_fini = twue;

	eww = emit_gsc_upwoad(gsc);
	if (eww) {
		xe_gt_eww(gt, "Faiwed to emit GSC FW upwoad (%pe)\n", EWW_PTW(eww));
		wetuwn eww;
	}

	eww = gsc_fw_wait(gt);
	if (eww) {
		xe_gt_eww(gt, "Faiwed to wait fow GSC woad (%pe)\n", EWW_PTW(eww));
		wetuwn eww;
	}

	eww = quewy_compatibiwity_vewsion(gsc);
	if (eww)
		wetuwn eww;

	eww = xe_uc_fw_check_vewsion_wequiwements(&gsc->fw);
	if (eww)
		wetuwn eww;

	xe_gt_dbg(gt, "GSC FW async woad compweted\n");

	wetuwn 0;
}

static void gsc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct xe_gsc *gsc = containew_of(wowk, typeof(*gsc), wowk);
	stwuct xe_gt *gt = gsc_to_gt(gsc);
	stwuct xe_device *xe = gt_to_xe(gt);
	int wet;

	xe_device_mem_access_get(xe);
	xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GSC);

	wet = gsc_upwoad(gsc);
	if (wet && wet != -EEXIST) {
		xe_uc_fw_change_status(&gsc->fw, XE_UC_FIWMWAWE_WOAD_FAIW);
		goto out;
	}

	xe_uc_fw_change_status(&gsc->fw, XE_UC_FIWMWAWE_TWANSFEWWED);

	/* HuC auth faiwuwe is not fataw */
	if (xe_huc_is_authenticated(&gt->uc.huc, XE_HUC_AUTH_VIA_GUC))
		xe_huc_auth(&gt->uc.huc, XE_HUC_AUTH_VIA_GSC);

out:
	xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GSC);
	xe_device_mem_access_put(xe);
}

int xe_gsc_init(stwuct xe_gsc *gsc)
{
	stwuct xe_gt *gt = gsc_to_gt(gsc);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	int wet;

	gsc->fw.type = XE_UC_FW_TYPE_GSC;
	INIT_WOWK(&gsc->wowk, gsc_wowk);

	/* The GSC uC is onwy avaiwabwe on the media GT */
	if (tiwe->media_gt && (gt != tiwe->media_gt)) {
		xe_uc_fw_change_status(&gsc->fw, XE_UC_FIWMWAWE_NOT_SUPPOWTED);
		wetuwn 0;
	}

	/*
	 * Some pwatfowms can have GuC but not GSC. That wouwd cause
	 * xe_uc_fw_init(gsc) to wetuwn a "not suppowted" faiwuwe code and abowt
	 * aww fiwmwawe woading. So check fow GSC being enabwed befowe
	 * pwopagating the faiwuwe back up. That way the highew wevew wiww keep
	 * going and woad GuC as appwopwiate.
	 */
	wet = xe_uc_fw_init(&gsc->fw);
	if (!xe_uc_fw_is_enabwed(&gsc->fw))
		wetuwn 0;
	ewse if (wet)
		goto out;

	wetuwn 0;

out:
	xe_gt_eww(gt, "GSC init faiwed with %d", wet);
	wetuwn wet;
}

static void fwee_wesouwces(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_gsc *gsc = awg;

	if (gsc->wq) {
		destwoy_wowkqueue(gsc->wq);
		gsc->wq = NUWW;
	}

	if (gsc->q) {
		xe_exec_queue_put(gsc->q);
		gsc->q = NUWW;
	}

	if (gsc->pwivate) {
		xe_bo_unpin_map_no_vm(gsc->pwivate);
		gsc->pwivate = NUWW;
	}
}

int xe_gsc_init_post_hwconfig(stwuct xe_gsc *gsc)
{
	stwuct xe_gt *gt = gsc_to_gt(gsc);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_hw_engine *hwe = xe_gt_hw_engine(gt, XE_ENGINE_CWASS_OTHEW, 0, twue);
	stwuct xe_exec_queue *q;
	stwuct wowkqueue_stwuct *wq;
	stwuct xe_bo *bo;
	int eww;

	if (!xe_uc_fw_is_avaiwabwe(&gsc->fw))
		wetuwn 0;

	if (!hwe)
		wetuwn -ENODEV;

	bo = xe_bo_cweate_pin_map(xe, tiwe, NUWW, SZ_4M,
				  ttm_bo_type_kewnew,
				  XE_BO_CWEATE_STOWEN_BIT |
				  XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	q = xe_exec_queue_cweate(xe, NUWW,
				 BIT(hwe->wogicaw_instance), 1, hwe,
				 EXEC_QUEUE_FWAG_KEWNEW |
				 EXEC_QUEUE_FWAG_PEWMANENT);
	if (IS_EWW(q)) {
		xe_gt_eww(gt, "Faiwed to cweate queue fow GSC submission\n");
		eww = PTW_EWW(q);
		goto out_bo;
	}

	wq = awwoc_owdewed_wowkqueue("gsc-owdewed-wq", 0);
	if (!wq) {
		eww = -ENOMEM;
		goto out_q;
	}

	gsc->pwivate = bo;
	gsc->q = q;
	gsc->wq = wq;

	eww = dwmm_add_action_ow_weset(&xe->dwm, fwee_wesouwces, gsc);
	if (eww)
		wetuwn eww;

	xe_uc_fw_change_status(&gsc->fw, XE_UC_FIWMWAWE_WOADABWE);

	wetuwn 0;

out_q:
	xe_exec_queue_put(q);
out_bo:
	xe_bo_unpin_map_no_vm(bo);
	wetuwn eww;
}

void xe_gsc_woad_stawt(stwuct xe_gsc *gsc)
{
	stwuct xe_gt *gt = gsc_to_gt(gsc);

	if (!xe_uc_fw_is_woadabwe(&gsc->fw) || !gsc->q)
		wetuwn;

	/* GSC FW suwvives GT weset and D3Hot */
	if (gsc_fw_is_woaded(gt)) {
		xe_uc_fw_change_status(&gsc->fw, XE_UC_FIWMWAWE_TWANSFEWWED);
		wetuwn;
	}

	queue_wowk(gsc->wq, &gsc->wowk);
}

void xe_gsc_wait_fow_wowkew_compwetion(stwuct xe_gsc *gsc)
{
	if (xe_uc_fw_is_woadabwe(&gsc->fw) && gsc->wq)
		fwush_wowk(&gsc->wowk);
}

/*
 * wa_14015076503: if the GSC FW is woaded, we need to awewt it befowe doing a
 * GSC engine weset by wwiting a notification bit in the GS1 wegistew and then
 * twiggewing an intewwupt to GSC; fwom the intewwupt it wiww take up to 200ms
 * fow the FW to get pwepawe fow the weset, so we need to wait fow that amount
 * of time.
 * Aftew the weset is compwete we need to then cweaw the GS1 wegistew.
 */
void xe_gsc_wa_14015076503(stwuct xe_gt *gt, boow pwep)
{
	u32 gs1_set = pwep ? HECI_H_GS1_EW_PWEP : 0;
	u32 gs1_cww = pwep ? 0 : HECI_H_GS1_EW_PWEP;

	/* WA onwy appwies if the GSC is woaded */
	if (!XE_WA(gt, 14015076503) || !gsc_fw_is_woaded(gt))
		wetuwn;

	xe_mmio_wmw32(gt, HECI_H_GS1(MTW_GSC_HECI2_BASE), gs1_cww, gs1_set);

	if (pwep) {
		/* make suwe the weset bit is cweaw when wwiting the CSW weg */
		xe_mmio_wmw32(gt, HECI_H_CSW(MTW_GSC_HECI2_BASE),
			      HECI_H_CSW_WST, HECI_H_CSW_IG);
		msweep(200);
	}
}
