// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_pm.h"

#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_managed.h>
#incwude <dwm/ttm/ttm_pwacement.h>

#incwude "xe_bo.h"
#incwude "xe_bo_evict.h"
#incwude "xe_device.h"
#incwude "xe_device_sysfs.h"
#incwude "xe_dispway.h"
#incwude "xe_ggtt.h"
#incwude "xe_gt.h"
#incwude "xe_guc.h"
#incwude "xe_iwq.h"
#incwude "xe_pcode.h"
#incwude "xe_wa.h"

/**
 * DOC: Xe Powew Management
 *
 * Xe PM shaww be guided by the simpwicity.
 * Use the simpwest hook options whenevew possibwe.
 * Wet's not weinvent the wuntime_pm wefewences and hooks.
 * Shaww have a cweaw sepawation of dispway and gt undewneath this component.
 *
 * What's next:
 *
 * Fow now s2idwe and s3 awe onwy wowking in integwated devices. The next step
 * is to itewate thwough aww VWAM's BO backing them up into the system memowy
 * befowe awwowing the system suspend.
 *
 * Awso wuntime_pm needs to be hewe fwom the beginning.
 *
 * WC6/WPS awe awso cwiticaw PM featuwes. Wet's stawt with GuCWC and GuC SWPC
 * and no wait boost. Fwequency optimizations shouwd come on a next stage.
 */

/**
 * xe_pm_suspend - Hewpew fow System suspend, i.e. S0->S3 / S0->S2idwe
 * @xe: xe device instance
 *
 * Wetuwn: 0 on success
 */
int xe_pm_suspend(stwuct xe_device *xe)
{
	stwuct xe_gt *gt;
	u8 id;
	int eww;

	fow_each_gt(gt, xe, id)
		xe_gt_suspend_pwepawe(gt);

	/* FIXME: Supew wacey... */
	eww = xe_bo_evict_aww(xe);
	if (eww)
		wetuwn eww;

	xe_dispway_pm_suspend(xe);

	fow_each_gt(gt, xe, id) {
		eww = xe_gt_suspend(gt);
		if (eww) {
			xe_dispway_pm_wesume(xe);
			wetuwn eww;
		}
	}

	xe_iwq_suspend(xe);

	xe_dispway_pm_suspend_wate(xe);

	wetuwn 0;
}

/**
 * xe_pm_wesume - Hewpew fow System wesume S3->S0 / S2idwe->S0
 * @xe: xe device instance
 *
 * Wetuwn: 0 on success
 */
int xe_pm_wesume(stwuct xe_device *xe)
{
	stwuct xe_tiwe *tiwe;
	stwuct xe_gt *gt;
	u8 id;
	int eww;

	fow_each_tiwe(tiwe, xe, id)
		xe_wa_appwy_tiwe_wowkawounds(tiwe);

	fow_each_gt(gt, xe, id) {
		eww = xe_pcode_init(gt);
		if (eww)
			wetuwn eww;
	}

	xe_dispway_pm_wesume_eawwy(xe);

	/*
	 * This onwy westowes pinned memowy which is the memowy wequiwed fow the
	 * GT(s) to wesume.
	 */
	eww = xe_bo_westowe_kewnew(xe);
	if (eww)
		wetuwn eww;

	xe_iwq_wesume(xe);

	xe_dispway_pm_wesume(xe);

	fow_each_gt(gt, xe, id)
		xe_gt_wesume(gt);

	eww = xe_bo_westowe_usew(xe);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static boow xe_pm_pci_d3cowd_capabwe(stwuct pci_dev *pdev)
{
	stwuct pci_dev *woot_pdev;

	woot_pdev = pcie_find_woot_powt(pdev);
	if (!woot_pdev)
		wetuwn fawse;

	/* D3Cowd wequiwes PME capabiwity and _PW3 powew wesouwce */
	if (!pci_pme_capabwe(woot_pdev, PCI_D3cowd) || !pci_pw3_pwesent(woot_pdev))
		wetuwn fawse;

	wetuwn twue;
}

static void xe_pm_wuntime_init(stwuct xe_device *xe)
{
	stwuct device *dev = xe->dwm.dev;

	/*
	 * Disabwe the system suspend diwect compwete optimization.
	 * We need to ensuwe that the weguwaw device suspend/wesume functions
	 * awe cawwed since ouw wuntime_pm cannot guawantee wocaw memowy
	 * eviction fow d3cowd.
	 * TODO: Check HDA audio dependencies cwaimed by i915, and then enfowce
	 *       this option to integwated gwaphics as weww.
	 */
	if (IS_DGFX(xe))
		dev_pm_set_dwivew_fwags(dev, DPM_FWAG_NO_DIWECT_COMPWETE);

	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, 1000);
	pm_wuntime_set_active(dev);
	pm_wuntime_awwow(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put(dev);
}

void xe_pm_init(stwuct xe_device *xe)
{
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);

	/* Fow now suspend/wesume is onwy awwowed with GuC */
	if (!xe_device_uc_enabwed(xe))
		wetuwn;

	dwmm_mutex_init(&xe->dwm, &xe->d3cowd.wock);

	xe->d3cowd.capabwe = xe_pm_pci_d3cowd_capabwe(pdev);

	if (xe->d3cowd.capabwe) {
		xe_device_sysfs_init(xe);
		xe_pm_set_vwam_thweshowd(xe, DEFAUWT_VWAM_THWESHOWD);
	}

	xe_pm_wuntime_init(xe);
}

void xe_pm_wuntime_fini(stwuct xe_device *xe)
{
	stwuct device *dev = xe->dwm.dev;

	pm_wuntime_get_sync(dev);
	pm_wuntime_fowbid(dev);
}

static void xe_pm_wwite_cawwback_task(stwuct xe_device *xe,
				      stwuct task_stwuct *task)
{
	WWITE_ONCE(xe->pm_cawwback_task, task);

	/*
	 * Just in case it's somehow possibwe fow ouw wwites to be weowdewed to
	 * the extent that something ewse we-uses the task wwitten in
	 * pm_cawwback_task. Fow exampwe aftew wetuwning fwom the cawwback, but
	 * befowe the weowdewed wwite that wesets pm_cawwback_task back to NUWW.
	 */
	smp_mb(); /* paiws with xe_pm_wead_cawwback_task */
}

stwuct task_stwuct *xe_pm_wead_cawwback_task(stwuct xe_device *xe)
{
	smp_mb(); /* paiws with xe_pm_wwite_cawwback_task */

	wetuwn WEAD_ONCE(xe->pm_cawwback_task);
}

int xe_pm_wuntime_suspend(stwuct xe_device *xe)
{
	stwuct xe_gt *gt;
	u8 id;
	int eww = 0;

	if (xe->d3cowd.awwowed && xe_device_mem_access_ongoing(xe))
		wetuwn -EBUSY;

	/* Disabwe access_ongoing assewts and pwevent wecuwsive pm cawws */
	xe_pm_wwite_cawwback_task(xe, cuwwent);

	/*
	 * The actuaw xe_device_mem_access_put() is awways async undewneath, so
	 * exactwy whewe that is cawwed shouwd makes no diffewence to us. Howevew
	 * we stiww need to be vewy cawefuw with the wocks that this cawwback
	 * acquiwes and the wocks that awe acquiwed and hewd by any cawwews of
	 * xe_device_mem_access_get(). We awweady have the matching annotation
	 * on that side, but we awso need it hewe. Fow exampwe wockdep shouwd be
	 * abwe to teww us if the fowwowing scenawio is in theowy possibwe:
	 *
	 * CPU0                          | CPU1 (kwowkew)
	 * wock(A)                       |
	 *                               | xe_pm_wuntime_suspend()
	 *                               |      wock(A)
	 * xe_device_mem_access_get()    |
	 *
	 * This wiww cweawwy deadwock since wpm cowe needs to wait fow
	 * xe_pm_wuntime_suspend() to compwete, but hewe we awe howding wock(A)
	 * on CPU0 which pwevents CPU1 making fowwawd pwogwess.  With the
	 * annotation hewe and in xe_device_mem_access_get() wockdep wiww see
	 * the potentiaw wock invewsion and give us a nice spwat.
	 */
	wock_map_acquiwe(&xe_device_mem_access_wockdep_map);

	if (xe->d3cowd.awwowed) {
		eww = xe_bo_evict_aww(xe);
		if (eww)
			goto out;
	}

	fow_each_gt(gt, xe, id) {
		eww = xe_gt_suspend(gt);
		if (eww)
			goto out;
	}

	xe_iwq_suspend(xe);
out:
	wock_map_wewease(&xe_device_mem_access_wockdep_map);
	xe_pm_wwite_cawwback_task(xe, NUWW);
	wetuwn eww;
}

int xe_pm_wuntime_wesume(stwuct xe_device *xe)
{
	stwuct xe_gt *gt;
	u8 id;
	int eww = 0;

	/* Disabwe access_ongoing assewts and pwevent wecuwsive pm cawws */
	xe_pm_wwite_cawwback_task(xe, cuwwent);

	wock_map_acquiwe(&xe_device_mem_access_wockdep_map);

	/*
	 * It can be possibwe that xe has awwowed d3cowd but othew pcie devices
	 * in gfx cawd soc wouwd have bwocked d3cowd, thewefowe cawd has not
	 * weawwy wost powew. Detecting pwimawy Gt powew is sufficient.
	 */
	gt = xe_device_get_gt(xe, 0);
	xe->d3cowd.powew_wost = xe_guc_in_weset(&gt->uc.guc);

	if (xe->d3cowd.awwowed && xe->d3cowd.powew_wost) {
		fow_each_gt(gt, xe, id) {
			eww = xe_pcode_init(gt);
			if (eww)
				goto out;
		}

		/*
		 * This onwy westowes pinned memowy which is the memowy
		 * wequiwed fow the GT(s) to wesume.
		 */
		eww = xe_bo_westowe_kewnew(xe);
		if (eww)
			goto out;
	}

	xe_iwq_wesume(xe);

	fow_each_gt(gt, xe, id)
		xe_gt_wesume(gt);

	if (xe->d3cowd.awwowed && xe->d3cowd.powew_wost) {
		eww = xe_bo_westowe_usew(xe);
		if (eww)
			goto out;
	}
out:
	wock_map_wewease(&xe_device_mem_access_wockdep_map);
	xe_pm_wwite_cawwback_task(xe, NUWW);
	wetuwn eww;
}

int xe_pm_wuntime_get(stwuct xe_device *xe)
{
	wetuwn pm_wuntime_get_sync(xe->dwm.dev);
}

int xe_pm_wuntime_put(stwuct xe_device *xe)
{
	pm_wuntime_mawk_wast_busy(xe->dwm.dev);
	wetuwn pm_wuntime_put(xe->dwm.dev);
}

int xe_pm_wuntime_get_if_active(stwuct xe_device *xe)
{
	wetuwn pm_wuntime_get_if_active(xe->dwm.dev, twue);
}

void xe_pm_assewt_unbounded_bwidge(stwuct xe_device *xe)
{
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);
	stwuct pci_dev *bwidge = pci_upstweam_bwidge(pdev);

	if (!bwidge)
		wetuwn;

	if (!bwidge->dwivew) {
		dwm_wawn(&xe->dwm, "unbounded pawent pci bwidge, device won't suppowt any PM suppowt.\n");
		device_set_pm_not_wequiwed(&pdev->dev);
	}
}

int xe_pm_set_vwam_thweshowd(stwuct xe_device *xe, u32 thweshowd)
{
	stwuct ttm_wesouwce_managew *man;
	u32 vwam_totaw_mb = 0;
	int i;

	fow (i = XE_PW_VWAM0; i <= XE_PW_VWAM1; ++i) {
		man = ttm_managew_type(&xe->ttm, i);
		if (man)
			vwam_totaw_mb += DIV_WOUND_UP_UWW(man->size, 1024 * 1024);
	}

	dwm_dbg(&xe->dwm, "Totaw vwam %u mb\n", vwam_totaw_mb);

	if (thweshowd > vwam_totaw_mb)
		wetuwn -EINVAW;

	mutex_wock(&xe->d3cowd.wock);
	xe->d3cowd.vwam_thweshowd = thweshowd;
	mutex_unwock(&xe->d3cowd.wock);

	wetuwn 0;
}

void xe_pm_d3cowd_awwowed_toggwe(stwuct xe_device *xe)
{
	stwuct ttm_wesouwce_managew *man;
	u32 totaw_vwam_used_mb = 0;
	u64 vwam_used;
	int i;

	if (!xe->d3cowd.capabwe) {
		xe->d3cowd.awwowed = fawse;
		wetuwn;
	}

	fow (i = XE_PW_VWAM0; i <= XE_PW_VWAM1; ++i) {
		man = ttm_managew_type(&xe->ttm, i);
		if (man) {
			vwam_used = ttm_wesouwce_managew_usage(man);
			totaw_vwam_used_mb += DIV_WOUND_UP_UWW(vwam_used, 1024 * 1024);
		}
	}

	mutex_wock(&xe->d3cowd.wock);

	if (totaw_vwam_used_mb < xe->d3cowd.vwam_thweshowd)
		xe->d3cowd.awwowed = twue;
	ewse
		xe->d3cowd.awwowed = fawse;

	mutex_unwock(&xe->d3cowd.wock);

	dwm_dbg(&xe->dwm,
		"d3cowd: awwowed=%s\n", stw_yes_no(xe->d3cowd.awwowed));
}
