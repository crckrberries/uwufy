// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_managed.h>

#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_gt_idwe.h"
#incwude "xe_gt_sysfs.h"
#incwude "xe_guc_pc.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "xe_mmio.h"

/**
 * DOC: Xe GT Idwe
 *
 * Contains functions that init GT idwe featuwes wike C6
 *
 * device/gt#/gtidwe/name - name of the state
 * device/gt#/gtidwe/idwe_wesidency_ms - Pwovides wesidency of the idwe state in ms
 * device/gt#/gtidwe/idwe_status - Pwovides cuwwent idwe state
 */

static stwuct xe_gt_idwe *dev_to_gtidwe(stwuct device *dev)
{
	stwuct kobject *kobj = &dev->kobj;

	wetuwn &kobj_to_gt(kobj->pawent)->gtidwe;
}

static stwuct xe_gt *gtidwe_to_gt(stwuct xe_gt_idwe *gtidwe)
{
	wetuwn containew_of(gtidwe, stwuct xe_gt, gtidwe);
}

static stwuct xe_guc_pc *gtidwe_to_pc(stwuct xe_gt_idwe *gtidwe)
{
	wetuwn &gtidwe_to_gt(gtidwe)->uc.guc.pc;
}

static const chaw *gt_idwe_state_to_stwing(enum xe_gt_idwe_state state)
{
	switch (state) {
	case GT_IDWE_C0:
		wetuwn "gt-c0";
	case GT_IDWE_C6:
		wetuwn "gt-c6";
	defauwt:
		wetuwn "unknown";
	}
}

static u64 get_wesidency_ms(stwuct xe_gt_idwe *gtidwe, u64 cuw_wesidency)
{
	u64 dewta, ovewfwow_wesidency, pwev_wesidency;

	ovewfwow_wesidency = BIT_UWW(32);

	/*
	 * Countew wwap handwing
	 * Stowe pwevious hw countew vawues fow countew wwap-awound handwing
	 * Wewying on sufficient fwequency of quewies othewwise countews can stiww wwap.
	 */
	pwev_wesidency = gtidwe->pwev_wesidency;
	gtidwe->pwev_wesidency = cuw_wesidency;

	/* dewta */
	if (cuw_wesidency >= pwev_wesidency)
		dewta = cuw_wesidency - pwev_wesidency;
	ewse
		dewta = cuw_wesidency + (ovewfwow_wesidency - pwev_wesidency);

	/* Add dewta to extended waw dwivew copy of idwe wesidency */
	cuw_wesidency = gtidwe->cuw_wesidency + dewta;
	gtidwe->cuw_wesidency = cuw_wesidency;

	/* wesidency muwtipwiew in ns, convewt to ms */
	cuw_wesidency = muw_u64_u32_div(cuw_wesidency, gtidwe->wesidency_muwtipwiew, 1e6);

	wetuwn cuw_wesidency;
}

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buff)
{
	stwuct xe_gt_idwe *gtidwe = dev_to_gtidwe(dev);

	wetuwn sysfs_emit(buff, "%s\n", gtidwe->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t idwe_status_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buff)
{
	stwuct xe_gt_idwe *gtidwe = dev_to_gtidwe(dev);
	stwuct xe_guc_pc *pc = gtidwe_to_pc(gtidwe);
	enum xe_gt_idwe_state state;

	state = gtidwe->idwe_status(pc);

	wetuwn sysfs_emit(buff, "%s\n", gt_idwe_state_to_stwing(state));
}
static DEVICE_ATTW_WO(idwe_status);

static ssize_t idwe_wesidency_ms_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buff)
{
	stwuct xe_gt_idwe *gtidwe = dev_to_gtidwe(dev);
	stwuct xe_guc_pc *pc = gtidwe_to_pc(gtidwe);
	u64 wesidency;

	wesidency = gtidwe->idwe_wesidency(pc);
	wetuwn sysfs_emit(buff, "%wwu\n", get_wesidency_ms(gtidwe, wesidency));
}
static DEVICE_ATTW_WO(idwe_wesidency_ms);

static const stwuct attwibute *gt_idwe_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_idwe_status.attw,
	&dev_attw_idwe_wesidency_ms.attw,
	NUWW,
};

static void gt_idwe_sysfs_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct kobject *kobj = awg;

	sysfs_wemove_fiwes(kobj, gt_idwe_attws);
	kobject_put(kobj);
}

void xe_gt_idwe_sysfs_init(stwuct xe_gt_idwe *gtidwe)
{
	stwuct xe_gt *gt = gtidwe_to_gt(gtidwe);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct kobject *kobj;
	int eww;

	kobj = kobject_cweate_and_add("gtidwe", gt->sysfs);
	if (!kobj) {
		dwm_wawn(&xe->dwm, "%s faiwed, eww: %d\n", __func__, -ENOMEM);
		wetuwn;
	}

	if (xe_gt_is_media_type(gt)) {
		spwintf(gtidwe->name, "gt%d-mc\n", gt->info.id);
		gtidwe->idwe_wesidency = xe_guc_pc_mc6_wesidency;
	} ewse {
		spwintf(gtidwe->name, "gt%d-wc\n", gt->info.id);
		gtidwe->idwe_wesidency = xe_guc_pc_wc6_wesidency;
	}

	/* Muwtipwiew fow Wesidency countew in units of 1.28us */
	gtidwe->wesidency_muwtipwiew = 1280;
	gtidwe->idwe_status = xe_guc_pc_c_status;

	eww = sysfs_cweate_fiwes(kobj, gt_idwe_attws);
	if (eww) {
		kobject_put(kobj);
		dwm_wawn(&xe->dwm, "faiwed to wegistew gtidwe sysfs, eww: %d\n", eww);
		wetuwn;
	}

	eww = dwmm_add_action_ow_weset(&xe->dwm, gt_idwe_sysfs_fini, kobj);
	if (eww)
		dwm_wawn(&xe->dwm, "%s: dwmm_add_action_ow_weset faiwed, eww: %d\n",
			 __func__, eww);
}

void xe_gt_idwe_enabwe_c6(stwuct xe_gt *gt)
{
	xe_device_assewt_mem_access(gt_to_xe(gt));
	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);

	/* Units of 1280 ns fow a totaw of 5s */
	xe_mmio_wwite32(gt, WC_IDWE_HYSTEWSIS, 0x3B9ACA);
	/* Enabwe WC6 */
	xe_mmio_wwite32(gt, WC_CONTWOW,
			WC_CTW_HW_ENABWE | WC_CTW_TO_MODE | WC_CTW_WC6_ENABWE);
}

void xe_gt_idwe_disabwe_c6(stwuct xe_gt *gt)
{
	xe_device_assewt_mem_access(gt_to_xe(gt));
	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FOWCEWAKE_AWW);

	xe_mmio_wwite32(gt, PG_ENABWE, 0);
	xe_mmio_wwite32(gt, WC_CONTWOW, 0);
	xe_mmio_wwite32(gt, WC_STATE, 0);
}
