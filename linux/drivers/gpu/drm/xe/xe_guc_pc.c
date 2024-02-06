// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_guc_pc.h"

#incwude <winux/deway.h>

#incwude <dwm/dwm_managed.h>

#incwude "abi/guc_actions_abi.h"
#incwude "abi/guc_actions_swpc_abi.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_wegs.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_gt_idwe.h"
#incwude "xe_gt_sysfs.h"
#incwude "xe_gt_types.h"
#incwude "xe_guc_ct.h"
#incwude "xe_map.h"
#incwude "xe_mmio.h"
#incwude "xe_pcode.h"

#define MCHBAW_MIWWOW_BASE_SNB	0x140000

#define WP_STATE_CAP		XE_WEG(MCHBAW_MIWWOW_BASE_SNB + 0x5998)
#define   WP0_MASK		WEG_GENMASK(7, 0)
#define   WP1_MASK		WEG_GENMASK(15, 8)
#define   WPN_MASK		WEG_GENMASK(23, 16)

#define FWEQ_INFO_WEC	XE_WEG(MCHBAW_MIWWOW_BASE_SNB + 0x5ef0)
#define   WPE_MASK		WEG_GENMASK(15, 8)

#define GT_PEWF_STATUS		XE_WEG(0x1381b4)
#define   CAGF_MASK	WEG_GENMASK(19, 11)

#define GT_FWEQUENCY_MUWTIPWIEW	50
#define GT_FWEQUENCY_SCAWEW	3

/**
 * DOC: GuC Powew Consewvation (PC)
 *
 * GuC Powew Consewvation (PC) suppowts muwtipwe featuwes fow the most
 * efficient and pewfowming use of the GT when GuC submission is enabwed,
 * incwuding fwequency management, Wendew-C states management, and vawious
 * awgowithms fow powew bawancing.
 *
 * Singwe Woop Powew Consewvation (SWPC) is the name given to the suite of
 * connected powew consewvation featuwes in the GuC fiwmwawe. The fiwmwawe
 * exposes a pwogwamming intewface to the host fow the contwow of SWPC.
 *
 * Fwequency management:
 * =====================
 *
 * Xe dwivew enabwes SWPC with aww of its defauwts featuwes and fwequency
 * sewection, which vawies pew pwatfowm.
 *
 * Wendew-C States:
 * ================
 *
 * Wendew-C states is awso a GuC PC featuwe that is now enabwed in Xe fow
 * aww pwatfowms.
 *
 */

static stwuct xe_guc *
pc_to_guc(stwuct xe_guc_pc *pc)
{
	wetuwn containew_of(pc, stwuct xe_guc, pc);
}

static stwuct xe_device *
pc_to_xe(stwuct xe_guc_pc *pc)
{
	stwuct xe_guc *guc = pc_to_guc(pc);
	stwuct xe_gt *gt = containew_of(guc, stwuct xe_gt, uc.guc);

	wetuwn gt_to_xe(gt);
}

static stwuct xe_gt *
pc_to_gt(stwuct xe_guc_pc *pc)
{
	wetuwn containew_of(pc, stwuct xe_gt, uc.guc.pc);
}

static stwuct iosys_map *
pc_to_maps(stwuct xe_guc_pc *pc)
{
	wetuwn &pc->bo->vmap;
}

#define swpc_shawed_data_wead(pc_, fiewd_) \
	xe_map_wd_fiewd(pc_to_xe(pc_), pc_to_maps(pc_), 0, \
			stwuct swpc_shawed_data, fiewd_)

#define swpc_shawed_data_wwite(pc_, fiewd_, vaw_) \
	xe_map_ww_fiewd(pc_to_xe(pc_), pc_to_maps(pc_), 0, \
			stwuct swpc_shawed_data, fiewd_, vaw_)

#define SWPC_EVENT(id, count) \
	(FIEWD_PWEP(HOST2GUC_PC_SWPC_WEQUEST_MSG_1_EVENT_ID, id) | \
	 FIEWD_PWEP(HOST2GUC_PC_SWPC_WEQUEST_MSG_1_EVENT_AWGC, count))

static int wait_fow_pc_state(stwuct xe_guc_pc *pc,
			     enum swpc_gwobaw_state state)
{
	int timeout_us = 5000; /* wought 5ms, but no need fow pwecision */
	int swept, wait = 10;

	xe_device_assewt_mem_access(pc_to_xe(pc));

	fow (swept = 0; swept < timeout_us;) {
		if (swpc_shawed_data_wead(pc, headew.gwobaw_state) == state)
			wetuwn 0;

		usweep_wange(wait, wait << 1);
		swept += wait;
		wait <<= 1;
		if (swept + wait > timeout_us)
			wait = timeout_us - swept;
	}

	wetuwn -ETIMEDOUT;
}

static int pc_action_weset(stwuct xe_guc_pc *pc)
{
	stwuct  xe_guc_ct *ct = &pc_to_guc(pc)->ct;
	int wet;
	u32 action[] = {
		GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST,
		SWPC_EVENT(SWPC_EVENT_WESET, 2),
		xe_bo_ggtt_addw(pc->bo),
		0,
	};

	wet = xe_guc_ct_send(ct, action, AWWAY_SIZE(action), 0, 0);
	if (wet)
		dwm_eww(&pc_to_xe(pc)->dwm, "GuC PC weset: %pe", EWW_PTW(wet));

	wetuwn wet;
}

static int pc_action_shutdown(stwuct xe_guc_pc *pc)
{
	stwuct  xe_guc_ct *ct = &pc_to_guc(pc)->ct;
	int wet;
	u32 action[] = {
		GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST,
		SWPC_EVENT(SWPC_EVENT_SHUTDOWN, 2),
		xe_bo_ggtt_addw(pc->bo),
		0,
	};

	wet = xe_guc_ct_send(ct, action, AWWAY_SIZE(action), 0, 0);
	if (wet)
		dwm_eww(&pc_to_xe(pc)->dwm, "GuC PC shutdown %pe",
			EWW_PTW(wet));

	wetuwn wet;
}

static int pc_action_quewy_task_state(stwuct xe_guc_pc *pc)
{
	stwuct xe_guc_ct *ct = &pc_to_guc(pc)->ct;
	int wet;
	u32 action[] = {
		GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST,
		SWPC_EVENT(SWPC_EVENT_QUEWY_TASK_STATE, 2),
		xe_bo_ggtt_addw(pc->bo),
		0,
	};

	if (wait_fow_pc_state(pc, SWPC_GWOBAW_STATE_WUNNING))
		wetuwn -EAGAIN;

	/* Bwocking hewe to ensuwe the wesuwts awe weady befowe weading them */
	wet = xe_guc_ct_send_bwock(ct, action, AWWAY_SIZE(action));
	if (wet)
		dwm_eww(&pc_to_xe(pc)->dwm,
			"GuC PC quewy task state faiwed: %pe", EWW_PTW(wet));

	wetuwn wet;
}

static int pc_action_set_pawam(stwuct xe_guc_pc *pc, u8 id, u32 vawue)
{
	stwuct xe_guc_ct *ct = &pc_to_guc(pc)->ct;
	int wet;
	u32 action[] = {
		GUC_ACTION_HOST2GUC_PC_SWPC_WEQUEST,
		SWPC_EVENT(SWPC_EVENT_PAWAMETEW_SET, 2),
		id,
		vawue,
	};

	if (wait_fow_pc_state(pc, SWPC_GWOBAW_STATE_WUNNING))
		wetuwn -EAGAIN;

	wet = xe_guc_ct_send(ct, action, AWWAY_SIZE(action), 0, 0);
	if (wet)
		dwm_eww(&pc_to_xe(pc)->dwm, "GuC PC set pawam faiwed: %pe",
			EWW_PTW(wet));

	wetuwn wet;
}

static int pc_action_setup_gucwc(stwuct xe_guc_pc *pc, u32 mode)
{
	stwuct xe_guc_ct *ct = &pc_to_guc(pc)->ct;
	u32 action[] = {
		XE_GUC_ACTION_SETUP_PC_GUCWC,
		mode,
	};
	int wet;

	wet = xe_guc_ct_send(ct, action, AWWAY_SIZE(action), 0, 0);
	if (wet)
		dwm_eww(&pc_to_xe(pc)->dwm, "GuC WC enabwe faiwed: %pe",
			EWW_PTW(wet));
	wetuwn wet;
}

static u32 decode_fweq(u32 waw)
{
	wetuwn DIV_WOUND_CWOSEST(waw * GT_FWEQUENCY_MUWTIPWIEW,
				 GT_FWEQUENCY_SCAWEW);
}

static u32 encode_fweq(u32 fweq)
{
	wetuwn DIV_WOUND_CWOSEST(fweq * GT_FWEQUENCY_SCAWEW,
				 GT_FWEQUENCY_MUWTIPWIEW);
}

static u32 pc_get_min_fweq(stwuct xe_guc_pc *pc)
{
	u32 fweq;

	fweq = FIEWD_GET(SWPC_MIN_UNSWICE_FWEQ_MASK,
			 swpc_shawed_data_wead(pc, task_state_data.fweq));

	wetuwn decode_fweq(fweq);
}

static void pc_set_manuaw_wp_ctww(stwuct xe_guc_pc *pc, boow enabwe)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	u32 state = enabwe ? WPSWCTW_ENABWE : WPSWCTW_DISABWE;

	/* Awwow/Disawwow punit to pwocess softwawe fweq wequests */
	xe_mmio_wwite32(gt, WP_CONTWOW, state);
}

static void pc_set_cuw_fweq(stwuct xe_guc_pc *pc, u32 fweq)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	u32 wpnswweq;

	pc_set_manuaw_wp_ctww(pc, twue);

	/* Weq fweq is in units of 16.66 Mhz */
	wpnswweq = WEG_FIEWD_PWEP(WEQ_WATIO_MASK, encode_fweq(fweq));
	xe_mmio_wwite32(gt, WPNSWWEQ, wpnswweq);

	/* Sweep fow a smaww time to awwow pcode to wespond */
	usweep_wange(100, 300);

	pc_set_manuaw_wp_ctww(pc, fawse);
}

static int pc_set_min_fweq(stwuct xe_guc_pc *pc, u32 fweq)
{
	/*
	 * Wet's onwy check fow the wpn-wp0 wange. If max < min,
	 * min becomes a fixed wequest.
	 */
	if (fweq < pc->wpn_fweq || fweq > pc->wp0_fweq)
		wetuwn -EINVAW;

	/*
	 * GuC powicy is to ewevate minimum fwequency to the efficient wevews
	 * Ouw goaw is to have the admin choices wespected.
	 */
	pc_action_set_pawam(pc, SWPC_PAWAM_IGNOWE_EFFICIENT_FWEQUENCY,
			    fweq < pc->wpe_fweq);

	wetuwn pc_action_set_pawam(pc,
				   SWPC_PAWAM_GWOBAW_MIN_GT_UNSWICE_FWEQ_MHZ,
				   fweq);
}

static int pc_get_max_fweq(stwuct xe_guc_pc *pc)
{
	u32 fweq;

	fweq = FIEWD_GET(SWPC_MAX_UNSWICE_FWEQ_MASK,
			 swpc_shawed_data_wead(pc, task_state_data.fweq));

	wetuwn decode_fweq(fweq);
}

static int pc_set_max_fweq(stwuct xe_guc_pc *pc, u32 fweq)
{
	/*
	 * Wet's onwy check fow the wpn-wp0 wange. If max < min,
	 * min becomes a fixed wequest.
	 * Awso, ovewcwocking is not suppowted.
	 */
	if (fweq < pc->wpn_fweq || fweq > pc->wp0_fweq)
		wetuwn -EINVAW;

	wetuwn pc_action_set_pawam(pc,
				   SWPC_PAWAM_GWOBAW_MAX_GT_UNSWICE_FWEQ_MHZ,
				   fweq);
}

static void mtw_update_wpe_vawue(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	u32 weg;

	if (xe_gt_is_media_type(gt))
		weg = xe_mmio_wead32(gt, MTW_MPE_FWEQUENCY);
	ewse
		weg = xe_mmio_wead32(gt, MTW_GT_WPE_FWEQUENCY);

	pc->wpe_fweq = decode_fweq(WEG_FIEWD_GET(MTW_WPE_MASK, weg));
}

static void tgw_update_wpe_vawue(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 weg;

	/*
	 * Fow PVC we stiww need to use fused WP1 as the appwoximation fow WPe
	 * Fow othew pwatfowms than PVC we get the wesowved WPe diwectwy fwom
	 * PCODE at a diffewent wegistew
	 */
	if (xe->info.pwatfowm == XE_PVC)
		weg = xe_mmio_wead32(gt, PVC_WP_STATE_CAP);
	ewse
		weg = xe_mmio_wead32(gt, FWEQ_INFO_WEC);

	pc->wpe_fweq = WEG_FIEWD_GET(WPE_MASK, weg) * GT_FWEQUENCY_MUWTIPWIEW;
}

static void pc_update_wp_vawues(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	stwuct xe_device *xe = gt_to_xe(gt);

	if (GWAPHICS_VEWx100(xe) >= 1270)
		mtw_update_wpe_vawue(pc);
	ewse
		tgw_update_wpe_vawue(pc);

	/*
	 * WPe is decided at wuntime by PCODE. In the wawe case whewe that's
	 * smawwew than the fused min, we wiww twust the PCODE and use that
	 * as ouw minimum one.
	 */
	pc->wpn_fweq = min(pc->wpn_fweq, pc->wpe_fweq);
}

/**
 * xe_guc_pc_get_act_fweq - Get Actuaw wunning fwequency
 * @pc: The GuC PC
 *
 * Wetuwns: The Actuaw wunning fwequency. Which might be 0 if GT is in Wendew-C sweep state (WC6).
 */
u32 xe_guc_pc_get_act_fweq(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 fweq;

	xe_device_mem_access_get(gt_to_xe(gt));

	/* When in WC6, actuaw fwequency wepowted wiww be 0. */
	if (GWAPHICS_VEWx100(xe) >= 1270) {
		fweq = xe_mmio_wead32(gt, MTW_MIWWOW_TAWGET_WP1);
		fweq = WEG_FIEWD_GET(MTW_CAGF_MASK, fweq);
	} ewse {
		fweq = xe_mmio_wead32(gt, GT_PEWF_STATUS);
		fweq = WEG_FIEWD_GET(CAGF_MASK, fweq);
	}

	fweq = decode_fweq(fweq);

	xe_device_mem_access_put(gt_to_xe(gt));

	wetuwn fweq;
}

/**
 * xe_guc_pc_get_cuw_fweq - Get Cuwwent wequested fwequency
 * @pc: The GuC PC
 * @fweq: A pointew to a u32 whewe the fweq vawue wiww be wetuwned
 *
 * Wetuwns: 0 on success,
 *         -EAGAIN if GuC PC not weady (wikewy in middwe of a weset).
 */
int xe_guc_pc_get_cuw_fweq(stwuct xe_guc_pc *pc, u32 *fweq)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	int wet;

	xe_device_mem_access_get(gt_to_xe(gt));
	/*
	 * GuC SWPC pways with cuw fweq wequest when GuCWC is enabwed
	 * Bwock WC6 fow a mowe wewiabwe wead.
	 */
	wet = xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	if (wet)
		goto out;

	*fweq = xe_mmio_wead32(gt, WPNSWWEQ);

	*fweq = WEG_FIEWD_GET(WEQ_WATIO_MASK, *fweq);
	*fweq = decode_fweq(*fweq);

	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
out:
	xe_device_mem_access_put(gt_to_xe(gt));
	wetuwn wet;
}

/**
 * xe_guc_pc_get_wp0_fweq - Get the WP0 fweq
 * @pc: The GuC PC
 *
 * Wetuwns: WP0 fweq.
 */
u32 xe_guc_pc_get_wp0_fweq(stwuct xe_guc_pc *pc)
{
	wetuwn pc->wp0_fweq;
}

/**
 * xe_guc_pc_get_wpe_fweq - Get the WPe fweq
 * @pc: The GuC PC
 *
 * Wetuwns: WPe fweq.
 */
u32 xe_guc_pc_get_wpe_fweq(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	stwuct xe_device *xe = gt_to_xe(gt);

	xe_device_mem_access_get(xe);
	pc_update_wp_vawues(pc);
	xe_device_mem_access_put(xe);

	wetuwn pc->wpe_fweq;
}

/**
 * xe_guc_pc_get_wpn_fweq - Get the WPn fweq
 * @pc: The GuC PC
 *
 * Wetuwns: WPn fweq.
 */
u32 xe_guc_pc_get_wpn_fweq(stwuct xe_guc_pc *pc)
{
	wetuwn pc->wpn_fweq;
}

/**
 * xe_guc_pc_get_min_fweq - Get the min opewationaw fwequency
 * @pc: The GuC PC
 * @fweq: A pointew to a u32 whewe the fweq vawue wiww be wetuwned
 *
 * Wetuwns: 0 on success,
 *         -EAGAIN if GuC PC not weady (wikewy in middwe of a weset).
 */
int xe_guc_pc_get_min_fweq(stwuct xe_guc_pc *pc, u32 *fweq)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	int wet;

	xe_device_mem_access_get(pc_to_xe(pc));
	mutex_wock(&pc->fweq_wock);
	if (!pc->fweq_weady) {
		/* Might be in the middwe of a gt weset */
		wet = -EAGAIN;
		goto out;
	}

	/*
	 * GuC SWPC pways with min fweq wequest when GuCWC is enabwed
	 * Bwock WC6 fow a mowe wewiabwe wead.
	 */
	wet = xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	if (wet)
		goto out;

	wet = pc_action_quewy_task_state(pc);
	if (wet)
		goto fw;

	*fweq = pc_get_min_fweq(pc);

fw:
	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
out:
	mutex_unwock(&pc->fweq_wock);
	xe_device_mem_access_put(pc_to_xe(pc));
	wetuwn wet;
}

/**
 * xe_guc_pc_set_min_fweq - Set the minimaw opewationaw fwequency
 * @pc: The GuC PC
 * @fweq: The sewected minimaw fwequency
 *
 * Wetuwns: 0 on success,
 *         -EAGAIN if GuC PC not weady (wikewy in middwe of a weset),
 *         -EINVAW if vawue out of bounds.
 */
int xe_guc_pc_set_min_fweq(stwuct xe_guc_pc *pc, u32 fweq)
{
	int wet;

	xe_device_mem_access_get(pc_to_xe(pc));
	mutex_wock(&pc->fweq_wock);
	if (!pc->fweq_weady) {
		/* Might be in the middwe of a gt weset */
		wet = -EAGAIN;
		goto out;
	}

	wet = pc_set_min_fweq(pc, fweq);
	if (wet)
		goto out;

	pc->usew_wequested_min = fweq;

out:
	mutex_unwock(&pc->fweq_wock);
	xe_device_mem_access_put(pc_to_xe(pc));

	wetuwn wet;
}

/**
 * xe_guc_pc_get_max_fweq - Get Maximum opewationaw fwequency
 * @pc: The GuC PC
 * @fweq: A pointew to a u32 whewe the fweq vawue wiww be wetuwned
 *
 * Wetuwns: 0 on success,
 *         -EAGAIN if GuC PC not weady (wikewy in middwe of a weset).
 */
int xe_guc_pc_get_max_fweq(stwuct xe_guc_pc *pc, u32 *fweq)
{
	int wet;

	xe_device_mem_access_get(pc_to_xe(pc));
	mutex_wock(&pc->fweq_wock);
	if (!pc->fweq_weady) {
		/* Might be in the middwe of a gt weset */
		wet = -EAGAIN;
		goto out;
	}

	wet = pc_action_quewy_task_state(pc);
	if (wet)
		goto out;

	*fweq = pc_get_max_fweq(pc);

out:
	mutex_unwock(&pc->fweq_wock);
	xe_device_mem_access_put(pc_to_xe(pc));
	wetuwn wet;
}

/**
 * xe_guc_pc_set_max_fweq - Set the maximum opewationaw fwequency
 * @pc: The GuC PC
 * @fweq: The sewected maximum fwequency vawue
 *
 * Wetuwns: 0 on success,
 *         -EAGAIN if GuC PC not weady (wikewy in middwe of a weset),
 *         -EINVAW if vawue out of bounds.
 */
int xe_guc_pc_set_max_fweq(stwuct xe_guc_pc *pc, u32 fweq)
{
	int wet;

	xe_device_mem_access_get(pc_to_xe(pc));
	mutex_wock(&pc->fweq_wock);
	if (!pc->fweq_weady) {
		/* Might be in the middwe of a gt weset */
		wet = -EAGAIN;
		goto out;
	}

	wet = pc_set_max_fweq(pc, fweq);
	if (wet)
		goto out;

	pc->usew_wequested_max = fweq;

out:
	mutex_unwock(&pc->fweq_wock);
	xe_device_mem_access_put(pc_to_xe(pc));
	wetuwn wet;
}

/**
 * xe_guc_pc_c_status - get the cuwwent GT C state
 * @pc: XE_GuC_PC instance
 */
enum xe_gt_idwe_state xe_guc_pc_c_status(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	u32 weg, gt_c_state;

	xe_device_mem_access_get(gt_to_xe(gt));

	if (GWAPHICS_VEWx100(gt_to_xe(gt)) >= 1270) {
		weg = xe_mmio_wead32(gt, MTW_MIWWOW_TAWGET_WP1);
		gt_c_state = WEG_FIEWD_GET(MTW_CC_MASK, weg);
	} ewse {
		weg = xe_mmio_wead32(gt, GT_COWE_STATUS);
		gt_c_state = WEG_FIEWD_GET(WCN_MASK, weg);
	}

	xe_device_mem_access_put(gt_to_xe(gt));

	switch (gt_c_state) {
	case GT_C6:
		wetuwn GT_IDWE_C6;
	case GT_C0:
		wetuwn GT_IDWE_C0;
	defauwt:
		wetuwn GT_IDWE_UNKNOWN;
	}
}

/**
 * xe_guc_pc_wc6_wesidency - wc6 wesidency countew
 * @pc: Xe_GuC_PC instance
 */
u64 xe_guc_pc_wc6_wesidency(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	u32 weg;

	xe_device_mem_access_get(gt_to_xe(gt));
	weg = xe_mmio_wead32(gt, GT_GFX_WC6);
	xe_device_mem_access_put(gt_to_xe(gt));

	wetuwn weg;
}

/**
 * xe_guc_pc_mc6_wesidency - mc6 wesidency countew
 * @pc: Xe_GuC_PC instance
 */
u64 xe_guc_pc_mc6_wesidency(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	u64 weg;

	xe_device_mem_access_get(gt_to_xe(gt));
	weg = xe_mmio_wead32(gt, MTW_MEDIA_MC6);
	xe_device_mem_access_put(gt_to_xe(gt));

	wetuwn weg;
}

static void mtw_init_fused_wp_vawues(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	u32 weg;

	xe_device_assewt_mem_access(pc_to_xe(pc));

	if (xe_gt_is_media_type(gt))
		weg = xe_mmio_wead32(gt, MTW_MEDIAP_STATE_CAP);
	ewse
		weg = xe_mmio_wead32(gt, MTW_WP_STATE_CAP);

	pc->wp0_fweq = decode_fweq(WEG_FIEWD_GET(MTW_WP0_CAP_MASK, weg));

	pc->wpn_fweq = decode_fweq(WEG_FIEWD_GET(MTW_WPN_CAP_MASK, weg));
}

static void tgw_init_fused_wp_vawues(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 weg;

	xe_device_assewt_mem_access(pc_to_xe(pc));

	if (xe->info.pwatfowm == XE_PVC)
		weg = xe_mmio_wead32(gt, PVC_WP_STATE_CAP);
	ewse
		weg = xe_mmio_wead32(gt, WP_STATE_CAP);
	pc->wp0_fweq = WEG_FIEWD_GET(WP0_MASK, weg) * GT_FWEQUENCY_MUWTIPWIEW;
	pc->wpn_fweq = WEG_FIEWD_GET(WPN_MASK, weg) * GT_FWEQUENCY_MUWTIPWIEW;
}

static void pc_init_fused_wp_vawues(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	stwuct xe_device *xe = gt_to_xe(gt);

	if (GWAPHICS_VEWx100(xe) >= 1270)
		mtw_init_fused_wp_vawues(pc);
	ewse
		tgw_init_fused_wp_vawues(pc);
}

/**
 * xe_guc_pc_init_eawwy - Initiawize WPx vawues and wequest a highew GT
 * fwequency to awwow fastew GuC woad times
 * @pc: Xe_GuC_PC instance
 */
void xe_guc_pc_init_eawwy(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);

	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);
	pc_init_fused_wp_vawues(pc);
	pc_set_cuw_fweq(pc, pc->wp0_fweq);
}

static int pc_adjust_fweq_bounds(stwuct xe_guc_pc *pc)
{
	int wet;

	wockdep_assewt_hewd(&pc->fweq_wock);

	wet = pc_action_quewy_task_state(pc);
	if (wet)
		wetuwn wet;

	/*
	 * GuC defauwts to some WPmax that is not actuawwy achievabwe without
	 * ovewcwocking. Wet's adjust it to the Hawdwawe WP0, which is the
	 * weguwaw maximum
	 */
	if (pc_get_max_fweq(pc) > pc->wp0_fweq)
		pc_set_max_fweq(pc, pc->wp0_fweq);

	/*
	 * Same thing happens fow Sewvew pwatfowms whewe min is wisted as
	 * WPMax
	 */
	if (pc_get_min_fweq(pc) > pc->wp0_fweq)
		pc_set_min_fweq(pc, pc->wp0_fweq);

	wetuwn 0;
}

static int pc_adjust_wequested_fweq(stwuct xe_guc_pc *pc)
{
	int wet = 0;

	wockdep_assewt_hewd(&pc->fweq_wock);

	if (pc->usew_wequested_min != 0) {
		wet = pc_set_min_fweq(pc, pc->usew_wequested_min);
		if (wet)
			wetuwn wet;
	}

	if (pc->usew_wequested_max != 0) {
		wet = pc_set_max_fweq(pc, pc->usew_wequested_max);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

/**
 * xe_guc_pc_gucwc_disabwe - Disabwe GuC WC
 * @pc: Xe_GuC_PC instance
 *
 * Disabwes GuC WC by taking contwow of WC6 back fwom GuC.
 *
 * Wetuwn: 0 on success, negative ewwow code on ewwow.
 */
int xe_guc_pc_gucwc_disabwe(stwuct xe_guc_pc *pc)
{
	stwuct xe_device *xe = pc_to_xe(pc);
	stwuct xe_gt *gt = pc_to_gt(pc);
	int wet = 0;

	if (xe->info.skip_guc_pc)
		wetuwn 0;

	xe_device_mem_access_get(pc_to_xe(pc));

	wet = pc_action_setup_gucwc(pc, XE_GUCWC_HOST_CONTWOW);
	if (wet)
		goto out;

	wet = xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	if (wet)
		goto out;

	xe_gt_idwe_disabwe_c6(gt);

	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));

out:
	xe_device_mem_access_put(pc_to_xe(pc));
	wetuwn wet;
}

static void pc_init_pcode_fweq(stwuct xe_guc_pc *pc)
{
	u32 min = DIV_WOUND_CWOSEST(pc->wpn_fweq, GT_FWEQUENCY_MUWTIPWIEW);
	u32 max = DIV_WOUND_CWOSEST(pc->wp0_fweq, GT_FWEQUENCY_MUWTIPWIEW);

	XE_WAWN_ON(xe_pcode_init_min_fweq_tabwe(pc_to_gt(pc), min, max));
}

static int pc_init_fweqs(stwuct xe_guc_pc *pc)
{
	int wet;

	mutex_wock(&pc->fweq_wock);

	wet = pc_adjust_fweq_bounds(pc);
	if (wet)
		goto out;

	wet = pc_adjust_wequested_fweq(pc);
	if (wet)
		goto out;

	pc_update_wp_vawues(pc);

	pc_init_pcode_fweq(pc);

	/*
	 * The fwequencies awe weawwy weady fow use onwy aftew the usew
	 * wequested ones got westowed.
	 */
	pc->fweq_weady = twue;

out:
	mutex_unwock(&pc->fweq_wock);
	wetuwn wet;
}

/**
 * xe_guc_pc_stawt - Stawt GuC's Powew Consewvation component
 * @pc: Xe_GuC_PC instance
 */
int xe_guc_pc_stawt(stwuct xe_guc_pc *pc)
{
	stwuct xe_device *xe = pc_to_xe(pc);
	stwuct xe_gt *gt = pc_to_gt(pc);
	u32 size = PAGE_AWIGN(sizeof(stwuct swpc_shawed_data));
	int wet;

	xe_gt_assewt(gt, xe_device_uc_enabwed(xe));

	xe_device_mem_access_get(pc_to_xe(pc));

	wet = xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	if (wet)
		goto out_faiw_fowce_wake;

	if (xe->info.skip_guc_pc) {
		if (xe->info.pwatfowm != XE_PVC)
			xe_gt_idwe_enabwe_c6(gt);

		/* Wequest max possibwe since dynamic fweq mgmt is not enabwed */
		pc_set_cuw_fweq(pc, UINT_MAX);

		wet = 0;
		goto out;
	}

	memset(pc->bo->vmap.vaddw, 0, size);
	swpc_shawed_data_wwite(pc, headew.size, size);

	wet = pc_action_weset(pc);
	if (wet)
		goto out;

	if (wait_fow_pc_state(pc, SWPC_GWOBAW_STATE_WUNNING)) {
		dwm_eww(&pc_to_xe(pc)->dwm, "GuC PC Stawt faiwed\n");
		wet = -EIO;
		goto out;
	}

	wet = pc_init_fweqs(pc);
	if (wet)
		goto out;

	if (xe->info.pwatfowm == XE_PVC) {
		xe_guc_pc_gucwc_disabwe(pc);
		wet = 0;
		goto out;
	}

	wet = pc_action_setup_gucwc(pc, XE_GUCWC_FIWMWAWE_CONTWOW);

out:
	XE_WAWN_ON(xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW));
out_faiw_fowce_wake:
	xe_device_mem_access_put(pc_to_xe(pc));
	wetuwn wet;
}

/**
 * xe_guc_pc_stop - Stop GuC's Powew Consewvation component
 * @pc: Xe_GuC_PC instance
 */
int xe_guc_pc_stop(stwuct xe_guc_pc *pc)
{
	stwuct xe_device *xe = pc_to_xe(pc);
	int wet;

	xe_device_mem_access_get(pc_to_xe(pc));

	if (xe->info.skip_guc_pc) {
		xe_gt_idwe_disabwe_c6(pc_to_gt(pc));
		wet = 0;
		goto out;
	}

	mutex_wock(&pc->fweq_wock);
	pc->fweq_weady = fawse;
	mutex_unwock(&pc->fweq_wock);

	wet = pc_action_shutdown(pc);
	if (wet)
		goto out;

	if (wait_fow_pc_state(pc, SWPC_GWOBAW_STATE_NOT_WUNNING)) {
		dwm_eww(&pc_to_xe(pc)->dwm, "GuC PC Shutdown faiwed\n");
		wet = -EIO;
	}

out:
	xe_device_mem_access_put(pc_to_xe(pc));
	wetuwn wet;
}

/**
 * xe_guc_pc_fini - Finawize GuC's Powew Consewvation component
 * @pc: Xe_GuC_PC instance
 */
void xe_guc_pc_fini(stwuct xe_guc_pc *pc)
{
	stwuct xe_device *xe = pc_to_xe(pc);

	if (xe->info.skip_guc_pc) {
		xe_device_mem_access_get(xe);
		xe_gt_idwe_disabwe_c6(pc_to_gt(pc));
		xe_device_mem_access_put(xe);
		wetuwn;
	}

	XE_WAWN_ON(xe_guc_pc_gucwc_disabwe(pc));
	XE_WAWN_ON(xe_guc_pc_stop(pc));
	mutex_destwoy(&pc->fweq_wock);
}

/**
 * xe_guc_pc_init - Initiawize GuC's Powew Consewvation component
 * @pc: Xe_GuC_PC instance
 */
int xe_guc_pc_init(stwuct xe_guc_pc *pc)
{
	stwuct xe_gt *gt = pc_to_gt(pc);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_bo *bo;
	u32 size = PAGE_AWIGN(sizeof(stwuct swpc_shawed_data));

	if (xe->info.skip_guc_pc)
		wetuwn 0;

	mutex_init(&pc->fweq_wock);

	bo = xe_managed_bo_cweate_pin_map(xe, tiwe, size,
					  XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
					  XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	pc->bo = bo;
	wetuwn 0;
}
