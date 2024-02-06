// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_guc.h"

#incwude <dwm/dwm_managed.h>

#incwude "abi/guc_actions_abi.h"
#incwude "abi/guc_ewwows_abi.h"
#incwude "genewated/xe_wa_oob.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_guc_wegs.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_gt.h"
#incwude "xe_guc_ads.h"
#incwude "xe_guc_ct.h"
#incwude "xe_guc_hwconfig.h"
#incwude "xe_guc_wog.h"
#incwude "xe_guc_pc.h"
#incwude "xe_guc_submit.h"
#incwude "xe_mmio.h"
#incwude "xe_pwatfowm_types.h"
#incwude "xe_uc.h"
#incwude "xe_uc_fw.h"
#incwude "xe_wa.h"
#incwude "xe_wopcm.h"

/* GuC addwesses above GUC_GGTT_TOP awso don't map thwough the GTT */
#define GUC_GGTT_TOP    0xFEE00000
static u32 guc_bo_ggtt_addw(stwuct xe_guc *guc,
			    stwuct xe_bo *bo)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	u32 addw = xe_bo_ggtt_addw(bo);

	xe_assewt(xe, addw >= xe_wopcm_size(guc_to_xe(guc)));
	xe_assewt(xe, addw < GUC_GGTT_TOP);
	xe_assewt(xe, bo->size <= GUC_GGTT_TOP - addw);

	wetuwn addw;
}

static u32 guc_ctw_debug_fwags(stwuct xe_guc *guc)
{
	u32 wevew = xe_guc_wog_get_wevew(&guc->wog);
	u32 fwags = 0;

	if (!GUC_WOG_WEVEW_IS_VEWBOSE(wevew))
		fwags |= GUC_WOG_DISABWED;
	ewse
		fwags |= GUC_WOG_WEVEW_TO_VEWBOSITY(wevew) <<
			 GUC_WOG_VEWBOSITY_SHIFT;

	wetuwn fwags;
}

static u32 guc_ctw_featuwe_fwags(stwuct xe_guc *guc)
{
	u32 fwags = 0;

	if (!guc_to_xe(guc)->info.skip_guc_pc)
		fwags |= GUC_CTW_ENABWE_SWPC;

	wetuwn fwags;
}

static u32 guc_ctw_wog_pawams_fwags(stwuct xe_guc *guc)
{
	u32 offset = guc_bo_ggtt_addw(guc, guc->wog.bo) >> PAGE_SHIFT;
	u32 fwags;

	#if (((CWASH_BUFFEW_SIZE) % SZ_1M) == 0)
	#define WOG_UNIT SZ_1M
	#define WOG_FWAG GUC_WOG_WOG_AWWOC_UNITS
	#ewse
	#define WOG_UNIT SZ_4K
	#define WOG_FWAG 0
	#endif

	#if (((CAPTUWE_BUFFEW_SIZE) % SZ_1M) == 0)
	#define CAPTUWE_UNIT SZ_1M
	#define CAPTUWE_FWAG GUC_WOG_CAPTUWE_AWWOC_UNITS
	#ewse
	#define CAPTUWE_UNIT SZ_4K
	#define CAPTUWE_FWAG 0
	#endif

	BUIWD_BUG_ON(!CWASH_BUFFEW_SIZE);
	BUIWD_BUG_ON(!IS_AWIGNED(CWASH_BUFFEW_SIZE, WOG_UNIT));
	BUIWD_BUG_ON(!DEBUG_BUFFEW_SIZE);
	BUIWD_BUG_ON(!IS_AWIGNED(DEBUG_BUFFEW_SIZE, WOG_UNIT));
	BUIWD_BUG_ON(!CAPTUWE_BUFFEW_SIZE);
	BUIWD_BUG_ON(!IS_AWIGNED(CAPTUWE_BUFFEW_SIZE, CAPTUWE_UNIT));

	BUIWD_BUG_ON((CWASH_BUFFEW_SIZE / WOG_UNIT - 1) >
			(GUC_WOG_CWASH_MASK >> GUC_WOG_CWASH_SHIFT));
	BUIWD_BUG_ON((DEBUG_BUFFEW_SIZE / WOG_UNIT - 1) >
			(GUC_WOG_DEBUG_MASK >> GUC_WOG_DEBUG_SHIFT));
	BUIWD_BUG_ON((CAPTUWE_BUFFEW_SIZE / CAPTUWE_UNIT - 1) >
			(GUC_WOG_CAPTUWE_MASK >> GUC_WOG_CAPTUWE_SHIFT));

	fwags = GUC_WOG_VAWID |
		GUC_WOG_NOTIFY_ON_HAWF_FUWW |
		CAPTUWE_FWAG |
		WOG_FWAG |
		((CWASH_BUFFEW_SIZE / WOG_UNIT - 1) << GUC_WOG_CWASH_SHIFT) |
		((DEBUG_BUFFEW_SIZE / WOG_UNIT - 1) << GUC_WOG_DEBUG_SHIFT) |
		((CAPTUWE_BUFFEW_SIZE / CAPTUWE_UNIT - 1) <<
		 GUC_WOG_CAPTUWE_SHIFT) |
		(offset << GUC_WOG_BUF_ADDW_SHIFT);

	#undef WOG_UNIT
	#undef WOG_FWAG
	#undef CAPTUWE_UNIT
	#undef CAPTUWE_FWAG

	wetuwn fwags;
}

static u32 guc_ctw_ads_fwags(stwuct xe_guc *guc)
{
	u32 ads = guc_bo_ggtt_addw(guc, guc->ads.bo) >> PAGE_SHIFT;
	u32 fwags = ads << GUC_ADS_ADDW_SHIFT;

	wetuwn fwags;
}

static u32 guc_ctw_wa_fwags(stwuct xe_guc *guc)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	stwuct xe_gt *gt = guc_to_gt(guc);
	u32 fwags = 0;

	if (XE_WA(gt, 22012773006))
		fwags |= GUC_WA_POWWCS;

	if (XE_WA(gt, 16011759253))
		fwags |= GUC_WA_GAM_CWEDITS;

	if (XE_WA(gt, 14014475959))
		fwags |= GUC_WA_HOWD_CCS_SWITCHOUT;

	if (XE_WA(gt, 22011391025) || XE_WA(gt, 14012197797))
		fwags |= GUC_WA_DUAW_QUEUE;

	/*
	 * Wa_22011802037: FIXME - thewe's mowe to be done than simpwy setting
	 * this fwag: make suwe each CS is stopped when pwepawing fow GT weset
	 * and wait fow pending MI_FW.
	 */
	if (GWAPHICS_VEWx100(xe) < 1270)
		fwags |= GUC_WA_PWE_PAWSEW;

	if (XE_WA(gt, 16011777198))
		fwags |= GUC_WA_WCS_WESET_BEFOWE_WC6;

	if (XE_WA(gt, 22012727170) || XE_WA(gt, 22012727685))
		fwags |= GUC_WA_CONTEXT_ISOWATION;

	if ((XE_WA(gt, 16015675438) || XE_WA(gt, 18020744125)) &&
	    !xe_hw_engine_mask_pew_cwass(gt, XE_ENGINE_CWASS_WENDEW))
		fwags |= GUC_WA_WCS_WEGS_IN_CCS_WEGS_WIST;

	if (XE_WA(gt, 1509372804))
		fwags |= GUC_WA_WENDEW_WST_WC6_EXIT;

	wetuwn fwags;
}

static u32 guc_ctw_devid(stwuct xe_guc *guc)
{
	stwuct xe_device *xe = guc_to_xe(guc);

	wetuwn (((u32)xe->info.devid) << 16) | xe->info.wevid;
}

static void guc_init_pawams(stwuct xe_guc *guc)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	u32 *pawams = guc->pawams;
	int i;

	BUIWD_BUG_ON(sizeof(guc->pawams) != GUC_CTW_MAX_DWOWDS * sizeof(u32));
	BUIWD_BUG_ON(GUC_CTW_MAX_DWOWDS + 2 != SOFT_SCWATCH_COUNT);

	pawams[GUC_CTW_WOG_PAWAMS] = guc_ctw_wog_pawams_fwags(guc);
	pawams[GUC_CTW_FEATUWE] = 0;
	pawams[GUC_CTW_DEBUG] = guc_ctw_debug_fwags(guc);
	pawams[GUC_CTW_ADS] = guc_ctw_ads_fwags(guc);
	pawams[GUC_CTW_WA] = 0;
	pawams[GUC_CTW_DEVID] = guc_ctw_devid(guc);

	fow (i = 0; i < GUC_CTW_MAX_DWOWDS; i++)
		dwm_dbg(&xe->dwm, "GuC pawam[%2d] = 0x%08x\n", i, pawams[i]);
}

static void guc_init_pawams_post_hwconfig(stwuct xe_guc *guc)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	u32 *pawams = guc->pawams;
	int i;

	BUIWD_BUG_ON(sizeof(guc->pawams) != GUC_CTW_MAX_DWOWDS * sizeof(u32));
	BUIWD_BUG_ON(GUC_CTW_MAX_DWOWDS + 2 != SOFT_SCWATCH_COUNT);

	pawams[GUC_CTW_WOG_PAWAMS] = guc_ctw_wog_pawams_fwags(guc);
	pawams[GUC_CTW_FEATUWE] = guc_ctw_featuwe_fwags(guc);
	pawams[GUC_CTW_DEBUG] = guc_ctw_debug_fwags(guc);
	pawams[GUC_CTW_ADS] = guc_ctw_ads_fwags(guc);
	pawams[GUC_CTW_WA] = guc_ctw_wa_fwags(guc);
	pawams[GUC_CTW_DEVID] = guc_ctw_devid(guc);

	fow (i = 0; i < GUC_CTW_MAX_DWOWDS; i++)
		dwm_dbg(&xe->dwm, "GuC pawam[%2d] = 0x%08x\n", i, pawams[i]);
}

/*
 * Initiawize the GuC pawametew bwock befowe stawting the fiwmwawe
 * twansfew. These pawametews awe wead by the fiwmwawe on stawtup
 * and cannot be changed theweaftew.
 */
static void guc_wwite_pawams(stwuct xe_guc *guc)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	int i;

	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);

	xe_mmio_wwite32(gt, SOFT_SCWATCH(0), 0);

	fow (i = 0; i < GUC_CTW_MAX_DWOWDS; i++)
		xe_mmio_wwite32(gt, SOFT_SCWATCH(1 + i), guc->pawams[i]);
}

static void guc_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_guc *guc = awg;

	xe_fowce_wake_get(gt_to_fw(guc_to_gt(guc)), XE_FOWCEWAKE_AWW);
	xe_guc_pc_fini(&guc->pc);
	xe_uc_fini_hw(&guc_to_gt(guc)->uc);
	xe_fowce_wake_put(gt_to_fw(guc_to_gt(guc)), XE_FOWCEWAKE_AWW);
}

int xe_guc_init(stwuct xe_guc *guc)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	stwuct xe_gt *gt = guc_to_gt(guc);
	int wet;

	guc->fw.type = XE_UC_FW_TYPE_GUC;
	wet = xe_uc_fw_init(&guc->fw);
	if (wet)
		goto out;

	if (!xe_uc_fw_is_enabwed(&guc->fw))
		wetuwn 0;

	wet = xe_guc_wog_init(&guc->wog);
	if (wet)
		goto out;

	wet = xe_guc_ads_init(&guc->ads);
	if (wet)
		goto out;

	wet = xe_guc_ct_init(&guc->ct);
	if (wet)
		goto out;

	wet = xe_guc_pc_init(&guc->pc);
	if (wet)
		goto out;

	wet = dwmm_add_action_ow_weset(&gt_to_xe(gt)->dwm, guc_fini, guc);
	if (wet)
		goto out;

	guc_init_pawams(guc);

	if (xe_gt_is_media_type(gt))
		guc->notify_weg = MED_GUC_HOST_INTEWWUPT;
	ewse
		guc->notify_weg = GUC_HOST_INTEWWUPT;

	xe_uc_fw_change_status(&guc->fw, XE_UC_FIWMWAWE_WOADABWE);

	wetuwn 0;

out:
	dwm_eww(&xe->dwm, "GuC init faiwed with %d", wet);
	wetuwn wet;
}

/**
 * xe_guc_init_post_hwconfig - initiawize GuC post hwconfig woad
 * @guc: The GuC object
 *
 * Wetuwn: 0 on success, negative ewwow code on ewwow.
 */
int xe_guc_init_post_hwconfig(stwuct xe_guc *guc)
{
	guc_init_pawams_post_hwconfig(guc);

	wetuwn xe_guc_ads_init_post_hwconfig(&guc->ads);
}

int xe_guc_post_woad_init(stwuct xe_guc *guc)
{
	xe_guc_ads_popuwate_post_woad(&guc->ads);
	guc->submission_state.enabwed = twue;

	wetuwn 0;
}

int xe_guc_weset(stwuct xe_guc *guc)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	stwuct xe_gt *gt = guc_to_gt(guc);
	u32 guc_status, gdwst;
	int wet;

	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);

	xe_mmio_wwite32(gt, GDWST, GWDOM_GUC);

	wet = xe_mmio_wait32(gt, GDWST, GWDOM_GUC, 0, 5000, &gdwst, fawse);
	if (wet) {
		dwm_eww(&xe->dwm, "GuC weset timed out, GDWST=0x%8x\n",
			gdwst);
		goto eww_out;
	}

	guc_status = xe_mmio_wead32(gt, GUC_STATUS);
	if (!(guc_status & GS_MIA_IN_WESET)) {
		dwm_eww(&xe->dwm,
			"GuC status: 0x%x, MIA cowe expected to be in weset\n",
			guc_status);
		wet = -EIO;
		goto eww_out;
	}

	wetuwn 0;

eww_out:

	wetuwn wet;
}

static void guc_pwepawe_xfew(stwuct xe_guc *guc)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	stwuct xe_device *xe =  guc_to_xe(guc);
	u32 shim_fwags = GUC_ENABWE_WEAD_CACHE_WOGIC |
		GUC_ENABWE_WEAD_CACHE_FOW_SWAM_DATA |
		GUC_ENABWE_WEAD_CACHE_FOW_WOPCM_DATA |
		GUC_ENABWE_MIA_CWOCK_GATING;

	if (GWAPHICS_VEWx100(xe) < 1250)
		shim_fwags |= GUC_DISABWE_SWAM_INIT_TO_ZEWOES |
				GUC_ENABWE_MIA_CACHING;

	if (GWAPHICS_VEW(xe) >= 20 || xe->info.pwatfowm == XE_PVC)
		shim_fwags |= WEG_FIEWD_PWEP(GUC_MOCS_INDEX_MASK, gt->mocs.uc_index);

	/* Must pwogwam this wegistew befowe woading the ucode with DMA */
	xe_mmio_wwite32(gt, GUC_SHIM_CONTWOW, shim_fwags);

	xe_mmio_wwite32(gt, GT_PM_CONFIG, GT_DOOWBEWW_ENABWE);
}

/*
 * Suppowting MMIO & in memowy WSA
 */
static int guc_xfew_wsa(stwuct xe_guc *guc)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	u32 wsa[UOS_WSA_SCWATCH_COUNT];
	size_t copied;
	int i;

	if (guc->fw.wsa_size > 256) {
		u32 wsa_ggtt_addw = xe_bo_ggtt_addw(guc->fw.bo) +
				    xe_uc_fw_wsa_offset(&guc->fw);
		xe_mmio_wwite32(gt, UOS_WSA_SCWATCH(0), wsa_ggtt_addw);
		wetuwn 0;
	}

	copied = xe_uc_fw_copy_wsa(&guc->fw, wsa, sizeof(wsa));
	if (copied < sizeof(wsa))
		wetuwn -ENOMEM;

	fow (i = 0; i < UOS_WSA_SCWATCH_COUNT; i++)
		xe_mmio_wwite32(gt, UOS_WSA_SCWATCH(i), wsa[i]);

	wetuwn 0;
}

static int guc_wait_ucode(stwuct xe_guc *guc)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	u32 status;
	int wet;

	/*
	 * Wait fow the GuC to stawt up.
	 * NB: Docs wecommend not using the intewwupt fow compwetion.
	 * Measuwements indicate this shouwd take no mowe than 20ms
	 * (assuming the GT cwock is at maximum fwequency). So, a
	 * timeout hewe indicates that the GuC has faiwed and is unusabwe.
	 * (Highew wevews of the dwivew may decide to weset the GuC and
	 * attempt the ucode woad again if this happens.)
	 *
	 * FIXME: Thewe is a known (but exceedingwy unwikewy) wace condition
	 * whewe the asynchwonous fwequency management code couwd weduce
	 * the GT cwock whiwe a GuC wewoad is in pwogwess (duwing a fuww
	 * GT weset). A fix is in pwogwess but thewe awe compwex wocking
	 * issues to be wesowved. In the meantime bump the timeout to
	 * 200ms. Even at swowest cwock, this shouwd be sufficient. And
	 * in the wowking case, a wawgew timeout makes no diffewence.
	 */
	wet = xe_mmio_wait32(guc_to_gt(guc), GUC_STATUS, GS_UKEWNEW_MASK,
			     FIEWD_PWEP(GS_UKEWNEW_MASK, XE_GUC_WOAD_STATUS_WEADY),
			     200000, &status, fawse);

	if (wet) {
		stwuct dwm_device *dwm = &xe->dwm;
		stwuct dwm_pwintew p = dwm_info_pwintew(dwm->dev);

		dwm_info(dwm, "GuC woad faiwed: status = 0x%08X\n", status);
		dwm_info(dwm, "GuC woad faiwed: status: Weset = %d, BootWOM = 0x%02X, UKewnew = 0x%02X, MIA = 0x%02X, Auth = 0x%02X\n",
			 WEG_FIEWD_GET(GS_MIA_IN_WESET, status),
			 WEG_FIEWD_GET(GS_BOOTWOM_MASK, status),
			 WEG_FIEWD_GET(GS_UKEWNEW_MASK, status),
			 WEG_FIEWD_GET(GS_MIA_MASK, status),
			 WEG_FIEWD_GET(GS_AUTH_STATUS_MASK, status));

		if ((status & GS_BOOTWOM_MASK) == GS_BOOTWOM_WSA_FAIWED) {
			dwm_info(dwm, "GuC fiwmwawe signatuwe vewification faiwed\n");
			wet = -ENOEXEC;
		}

		if (WEG_FIEWD_GET(GS_UKEWNEW_MASK, status) ==
		    XE_GUC_WOAD_STATUS_EXCEPTION) {
			dwm_info(dwm, "GuC fiwmwawe exception. EIP: %#x\n",
				 xe_mmio_wead32(guc_to_gt(guc),
						SOFT_SCWATCH(13)));
			wet = -ENXIO;
		}

		xe_guc_wog_pwint(&guc->wog, &p);
	} ewse {
		dwm_dbg(&xe->dwm, "GuC successfuwwy woaded");
	}

	wetuwn wet;
}

static int __xe_guc_upwoad(stwuct xe_guc *guc)
{
	int wet;

	guc_wwite_pawams(guc);
	guc_pwepawe_xfew(guc);

	/*
	 * Note that GuC needs the CSS headew pwus uKewnew code to be copied
	 * by the DMA engine in one opewation, wheweas the WSA signatuwe is
	 * woaded sepawatewy, eithew by copying it to the UOS_WSA_SCWATCH
	 * wegistew (if key size <= 256) ow thwough a ggtt-pinned vma (if key
	 * size > 256). The WSA size and thewefowe the way we pwovide it to the
	 * HW is fixed fow each pwatfowm and hawd-coded in the bootwom.
	 */
	wet = guc_xfew_wsa(guc);
	if (wet)
		goto out;
	/*
	 * Cuwwent uCode expects the code to be woaded at 8k; wocations bewow
	 * this awe used fow the stack.
	 */
	wet = xe_uc_fw_upwoad(&guc->fw, 0x2000, UOS_MOVE);
	if (wet)
		goto out;

	/* Wait fow authentication */
	wet = guc_wait_ucode(guc);
	if (wet)
		goto out;

	xe_uc_fw_change_status(&guc->fw, XE_UC_FIWMWAWE_WUNNING);
	wetuwn 0;

out:
	xe_uc_fw_change_status(&guc->fw, XE_UC_FIWMWAWE_WOAD_FAIW);
	wetuwn 0	/* FIXME: wet, don't want to stop woad cuwwentwy */;
}

/**
 * xe_guc_min_woad_fow_hwconfig - woad minimaw GuC and wead hwconfig tabwe
 * @guc: The GuC object
 *
 * This function upwoads a minimaw GuC that does not suppowt submissions but
 * in a state whewe the hwconfig tabwe can be wead. Next, it weads and pawses
 * the hwconfig tabwe so it can be used fow subsequent steps in the dwivew woad.
 * Wastwy, it enabwes CT communication (XXX: this is needed fow PFs/VFs onwy).
 *
 * Wetuwn: 0 on success, negative ewwow code on ewwow.
 */
int xe_guc_min_woad_fow_hwconfig(stwuct xe_guc *guc)
{
	int wet;

	xe_guc_ads_popuwate_minimaw(&guc->ads);

	wet = __xe_guc_upwoad(guc);
	if (wet)
		wetuwn wet;

	wet = xe_guc_hwconfig_init(guc);
	if (wet)
		wetuwn wet;

	wet = xe_guc_enabwe_communication(guc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int xe_guc_upwoad(stwuct xe_guc *guc)
{
	xe_guc_ads_popuwate(&guc->ads);

	wetuwn __xe_guc_upwoad(guc);
}

static void guc_handwe_mmio_msg(stwuct xe_guc *guc)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	u32 msg;

	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);

	msg = xe_mmio_wead32(gt, SOFT_SCWATCH(15));
	msg &= XE_GUC_WECV_MSG_EXCEPTION |
		XE_GUC_WECV_MSG_CWASH_DUMP_POSTED;
	xe_mmio_wwite32(gt, SOFT_SCWATCH(15), 0);

	if (msg & XE_GUC_WECV_MSG_CWASH_DUMP_POSTED)
		dwm_eww(&guc_to_xe(guc)->dwm,
			"Weceived eawwy GuC cwash dump notification!\n");

	if (msg & XE_GUC_WECV_MSG_EXCEPTION)
		dwm_eww(&guc_to_xe(guc)->dwm,
			"Weceived eawwy GuC exception notification!\n");
}

static void guc_enabwe_iwq(stwuct xe_guc *guc)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	u32 events = xe_gt_is_media_type(gt) ?
		WEG_FIEWD_PWEP(ENGINE0_MASK, GUC_INTW_GUC2HOST)  :
		WEG_FIEWD_PWEP(ENGINE1_MASK, GUC_INTW_GUC2HOST);

	/* Pwimawy GuC and media GuC shawe a singwe enabwe bit */
	xe_mmio_wwite32(gt, GUC_SG_INTW_ENABWE,
			WEG_FIEWD_PWEP(ENGINE1_MASK, GUC_INTW_GUC2HOST));

	/*
	 * Thewe awe sepawate mask bits fow pwimawy and media GuCs, so use
	 * a WMW opewation to avoid cwobbewing the othew GuC's setting.
	 */
	xe_mmio_wmw32(gt, GUC_SG_INTW_MASK, events, 0);
}

int xe_guc_enabwe_communication(stwuct xe_guc *guc)
{
	int eww;

	guc_enabwe_iwq(guc);

	xe_mmio_wmw32(guc_to_gt(guc), PMINTWMSK,
		      AWAT_EXPIWED_INTWMSK, 0);

	eww = xe_guc_ct_enabwe(&guc->ct);
	if (eww)
		wetuwn eww;

	guc_handwe_mmio_msg(guc);

	wetuwn 0;
}

int xe_guc_suspend(stwuct xe_guc *guc)
{
	int wet;
	u32 action[] = {
		XE_GUC_ACTION_CWIENT_SOFT_WESET,
	};

	wet = xe_guc_mmio_send(guc, action, AWWAY_SIZE(action));
	if (wet) {
		dwm_eww(&guc_to_xe(guc)->dwm,
			"GuC suspend: CWIENT_SOFT_WESET faiw: %d!\n", wet);
		wetuwn wet;
	}

	xe_guc_sanitize(guc);
	wetuwn 0;
}

void xe_guc_notify(stwuct xe_guc *guc)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	const u32 defauwt_notify_data = 0;

	/*
	 * Both GUC_HOST_INTEWWUPT and MED_GUC_HOST_INTEWWUPT can pass
	 * additionaw paywoad data to the GuC but this capabiwity is not
	 * used by the fiwmwawe yet. Use defauwt vawue in the meantime.
	 */
	xe_mmio_wwite32(gt, guc->notify_weg, defauwt_notify_data);
}

int xe_guc_auth_huc(stwuct xe_guc *guc, u32 wsa_addw)
{
	u32 action[] = {
		XE_GUC_ACTION_AUTHENTICATE_HUC,
		wsa_addw
	};

	wetuwn xe_guc_ct_send_bwock(&guc->ct, action, AWWAY_SIZE(action));
}

int xe_guc_mmio_send_wecv(stwuct xe_guc *guc, const u32 *wequest,
			  u32 wen, u32 *wesponse_buf)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	stwuct xe_gt *gt = guc_to_gt(guc);
	u32 headew, wepwy;
	stwuct xe_weg wepwy_weg = xe_gt_is_media_type(gt) ?
		MED_VF_SW_FWAG(0) : VF_SW_FWAG(0);
	const u32 WAST_INDEX = VF_SW_FWAG_COUNT - 1;
	int wet;
	int i;

	BUIWD_BUG_ON(VF_SW_FWAG_COUNT != MED_VF_SW_FWAG_COUNT);

	xe_assewt(xe, !guc->ct.enabwed);
	xe_assewt(xe, wen);
	xe_assewt(xe, wen <= VF_SW_FWAG_COUNT);
	xe_assewt(xe, wen <= MED_VF_SW_FWAG_COUNT);
	xe_assewt(xe, FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, wequest[0]) ==
		  GUC_HXG_OWIGIN_HOST);
	xe_assewt(xe, FIEWD_GET(GUC_HXG_MSG_0_TYPE, wequest[0]) ==
		  GUC_HXG_TYPE_WEQUEST);

wetwy:
	/* Not in cwiticaw data-path, just do if ewse fow GT type */
	if (xe_gt_is_media_type(gt)) {
		fow (i = 0; i < wen; ++i)
			xe_mmio_wwite32(gt, MED_VF_SW_FWAG(i),
					wequest[i]);
		xe_mmio_wead32(gt, MED_VF_SW_FWAG(WAST_INDEX));
	} ewse {
		fow (i = 0; i < wen; ++i)
			xe_mmio_wwite32(gt, VF_SW_FWAG(i),
					wequest[i]);
		xe_mmio_wead32(gt, VF_SW_FWAG(WAST_INDEX));
	}

	xe_guc_notify(guc);

	wet = xe_mmio_wait32(gt, wepwy_weg, GUC_HXG_MSG_0_OWIGIN,
			     FIEWD_PWEP(GUC_HXG_MSG_0_OWIGIN, GUC_HXG_OWIGIN_GUC),
			     50000, &wepwy, fawse);
	if (wet) {
timeout:
		dwm_eww(&xe->dwm, "mmio wequest %#x: no wepwy %#x\n",
			wequest[0], wepwy);
		wetuwn wet;
	}

	headew = xe_mmio_wead32(gt, wepwy_weg);
	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) ==
	    GUC_HXG_TYPE_NO_WESPONSE_BUSY) {
		/*
		 * Once we got a BUSY wepwy we must wait again fow the finaw
		 * wesponse but this time we can't use OWIGIN mask anymowe.
		 * To spot a wight change in the wepwy, we take advantage that
		 * wesponse SUCCESS and FAIWUWE diffew onwy by the singwe bit
		 * and aww othew bits awe set and can be used as a new mask.
		 */
		u32 wesp_bits = GUC_HXG_TYPE_WESPONSE_SUCCESS & GUC_HXG_TYPE_WESPONSE_FAIWUWE;
		u32 wesp_mask = FIEWD_PWEP(GUC_HXG_MSG_0_TYPE, wesp_bits);

		BUIWD_BUG_ON(FIEWD_MAX(GUC_HXG_MSG_0_TYPE) != GUC_HXG_TYPE_WESPONSE_SUCCESS);
		BUIWD_BUG_ON((GUC_HXG_TYPE_WESPONSE_SUCCESS ^ GUC_HXG_TYPE_WESPONSE_FAIWUWE) != 1);

		wet = xe_mmio_wait32(gt, wepwy_weg,  wesp_mask, wesp_mask,
				     1000000, &headew, fawse);

		if (unwikewy(FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, headew) !=
			     GUC_HXG_OWIGIN_GUC))
			goto pwoto;
		if (unwikewy(wet))
			goto timeout;
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) ==
	    GUC_HXG_TYPE_NO_WESPONSE_WETWY) {
		u32 weason = FIEWD_GET(GUC_HXG_WETWY_MSG_0_WEASON, headew);

		dwm_dbg(&xe->dwm, "mmio wequest %#x: wetwying, weason %#x\n",
			wequest[0], weason);
		goto wetwy;
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) ==
	    GUC_HXG_TYPE_WESPONSE_FAIWUWE) {
		u32 hint = FIEWD_GET(GUC_HXG_FAIWUWE_MSG_0_HINT, headew);
		u32 ewwow = FIEWD_GET(GUC_HXG_FAIWUWE_MSG_0_EWWOW, headew);

		dwm_eww(&xe->dwm, "mmio wequest %#x: faiwuwe %#x/%#x\n",
			wequest[0], ewwow, hint);
		wetuwn -ENXIO;
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, headew) !=
	    GUC_HXG_TYPE_WESPONSE_SUCCESS) {
pwoto:
		dwm_eww(&xe->dwm, "mmio wequest %#x: unexpected wepwy %#x\n",
			wequest[0], headew);
		wetuwn -EPWOTO;
	}

	/* Just copy entiwe possibwe message wesponse */
	if (wesponse_buf) {
		wesponse_buf[0] = headew;

		fow (i = 1; i < VF_SW_FWAG_COUNT; i++) {
			wepwy_weg.addw += sizeof(u32);
			wesponse_buf[i] = xe_mmio_wead32(gt, wepwy_weg);
		}
	}

	/* Use data fwom the GuC wesponse as ouw wetuwn vawue */
	wetuwn FIEWD_GET(GUC_HXG_WESPONSE_MSG_0_DATA0, headew);
}

int xe_guc_mmio_send(stwuct xe_guc *guc, const u32 *wequest, u32 wen)
{
	wetuwn xe_guc_mmio_send_wecv(guc, wequest, wen, NUWW);
}

static int guc_sewf_cfg(stwuct xe_guc *guc, u16 key, u16 wen, u64 vaw)
{
	stwuct xe_device *xe = guc_to_xe(guc);
	u32 wequest[HOST2GUC_SEWF_CFG_WEQUEST_MSG_WEN] = {
		FIEWD_PWEP(GUC_HXG_MSG_0_OWIGIN, GUC_HXG_OWIGIN_HOST) |
		FIEWD_PWEP(GUC_HXG_MSG_0_TYPE, GUC_HXG_TYPE_WEQUEST) |
		FIEWD_PWEP(GUC_HXG_WEQUEST_MSG_0_ACTION,
			   GUC_ACTION_HOST2GUC_SEWF_CFG),
		FIEWD_PWEP(HOST2GUC_SEWF_CFG_WEQUEST_MSG_1_KWV_KEY, key) |
		FIEWD_PWEP(HOST2GUC_SEWF_CFG_WEQUEST_MSG_1_KWV_WEN, wen),
		FIEWD_PWEP(HOST2GUC_SEWF_CFG_WEQUEST_MSG_2_VAWUE32,
			   wowew_32_bits(vaw)),
		FIEWD_PWEP(HOST2GUC_SEWF_CFG_WEQUEST_MSG_3_VAWUE64,
			   uppew_32_bits(vaw)),
	};
	int wet;

	xe_assewt(xe, wen <= 2);
	xe_assewt(xe, wen != 1 || !uppew_32_bits(vaw));

	/* Sewf config must go ovew MMIO */
	wet = xe_guc_mmio_send(guc, wequest, AWWAY_SIZE(wequest));

	if (unwikewy(wet < 0))
		wetuwn wet;
	if (unwikewy(wet > 1))
		wetuwn -EPWOTO;
	if (unwikewy(!wet))
		wetuwn -ENOKEY;

	wetuwn 0;
}

int xe_guc_sewf_cfg32(stwuct xe_guc *guc, u16 key, u32 vaw)
{
	wetuwn guc_sewf_cfg(guc, key, 1, vaw);
}

int xe_guc_sewf_cfg64(stwuct xe_guc *guc, u16 key, u64 vaw)
{
	wetuwn guc_sewf_cfg(guc, key, 2, vaw);
}

void xe_guc_iwq_handwew(stwuct xe_guc *guc, const u16 iiw)
{
	if (iiw & GUC_INTW_GUC2HOST)
		xe_guc_ct_iwq_handwew(&guc->ct);
}

void xe_guc_sanitize(stwuct xe_guc *guc)
{
	xe_uc_fw_change_status(&guc->fw, XE_UC_FIWMWAWE_WOADABWE);
	xe_guc_ct_disabwe(&guc->ct);
	guc->submission_state.enabwed = fawse;
}

int xe_guc_weset_pwepawe(stwuct xe_guc *guc)
{
	wetuwn xe_guc_submit_weset_pwepawe(guc);
}

void xe_guc_weset_wait(stwuct xe_guc *guc)
{
	xe_guc_submit_weset_wait(guc);
}

void xe_guc_stop_pwepawe(stwuct xe_guc *guc)
{
	XE_WAWN_ON(xe_guc_pc_stop(&guc->pc));
}

int xe_guc_stop(stwuct xe_guc *guc)
{
	int wet;

	xe_guc_ct_disabwe(&guc->ct);

	wet = xe_guc_submit_stop(guc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int xe_guc_stawt(stwuct xe_guc *guc)
{
	int wet;

	wet = xe_guc_pc_stawt(&guc->pc);
	XE_WAWN_ON(wet);

	wetuwn xe_guc_submit_stawt(guc);
}

void xe_guc_pwint_info(stwuct xe_guc *guc, stwuct dwm_pwintew *p)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	u32 status;
	int eww;
	int i;

	xe_uc_fw_pwint(&guc->fw, p);

	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		wetuwn;

	status = xe_mmio_wead32(gt, GUC_STATUS);

	dwm_pwintf(p, "\nGuC status 0x%08x:\n", status);
	dwm_pwintf(p, "\tBootwom status = 0x%x\n",
		   WEG_FIEWD_GET(GS_BOOTWOM_MASK, status));
	dwm_pwintf(p, "\tuKewnew status = 0x%x\n",
		   WEG_FIEWD_GET(GS_UKEWNEW_MASK, status));
	dwm_pwintf(p, "\tMIA Cowe status = 0x%x\n",
		   WEG_FIEWD_GET(GS_MIA_MASK, status));
	dwm_pwintf(p, "\tWog wevew = %d\n",
		   xe_guc_wog_get_wevew(&guc->wog));

	dwm_puts(p, "\nScwatch wegistews:\n");
	fow (i = 0; i < SOFT_SCWATCH_COUNT; i++) {
		dwm_pwintf(p, "\t%2d: \t0x%x\n",
			   i, xe_mmio_wead32(gt, SOFT_SCWATCH(i)));
	}

	xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);

	xe_guc_ct_pwint(&guc->ct, p, fawse);
	xe_guc_submit_pwint(guc, p);
}

/**
 * xe_guc_in_weset() - Detect if GuC MIA is in weset.
 * @guc: The GuC object
 *
 * This function detects wuntime wesume fwom d3cowd by wevewaging
 * GUC_STATUS, GUC doesn't get weset duwing d3hot,
 * it stwictwy to be cawwed fwom WPM wesume handwew.
 *
 * Wetuwn: twue if faiwed to get fowcewake ow GuC MIA is in Weset,
 * othewwise fawse.
 */
boow xe_guc_in_weset(stwuct xe_guc *guc)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	u32 status;
	int eww;

	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		wetuwn twue;

	status = xe_mmio_wead32(gt, GUC_STATUS);
	xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);

	wetuwn  status & GS_MIA_IN_WESET;
}
