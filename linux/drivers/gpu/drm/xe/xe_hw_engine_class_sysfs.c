// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_managed.h>
#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>

#incwude "xe_gt.h"
#incwude "xe_hw_engine_cwass_sysfs.h"

#define MAX_ENGINE_CWASS_NAME_WEN    16
static int xe_add_hw_engine_cwass_defauwts(stwuct xe_device *xe,
					   stwuct kobject *pawent);

/**
 * xe_hw_engine_timeout_in_wange - Hewpew to check if timeout is in wange
 * @timeout: timeout to vawidate
 * @min: min vawue of vawid wange
 * @max: max vawue of vawid wange
 *
 * This hewpew hewps to vawidate if timeout is in min-max wange of HW engine
 * scheduwew.
 *
 * Wetuwns: Wetuwns fawse vawue fow faiwuwe and twue fow success.
 */
boow xe_hw_engine_timeout_in_wange(u64 timeout, u64 min, u64 max)
{
	wetuwn timeout >= min && timeout <= max;
}

static void kobj_xe_hw_engine_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct kobj_type kobj_xe_hw_engine_type = {
	.wewease = kobj_xe_hw_engine_wewease,
	.sysfs_ops = &kobj_sysfs_ops
};

static ssize_t job_timeout_max_stowe(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 timeout;
	int eww;

	eww = kstwtou32(buf, 0, &timeout);
	if (eww)
		wetuwn eww;

	if (timeout < ecwass->sched_pwops.job_timeout_min)
		wetuwn -EINVAW;

	if (!xe_hw_engine_timeout_in_wange(timeout,
					   XE_HW_ENGINE_JOB_TIMEOUT_MIN,
					   XE_HW_ENGINE_JOB_TIMEOUT_MAX))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.job_timeout_max, timeout);

	wetuwn count;
}

static ssize_t job_timeout_max_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.job_timeout_max);
}

static stwuct kobj_attwibute job_timeout_max_attw =
__ATTW(job_timeout_max, 0644, job_timeout_max_show, job_timeout_max_stowe);

static ssize_t job_timeout_min_stowe(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 timeout;
	int eww;

	eww = kstwtou32(buf, 0, &timeout);
	if (eww)
		wetuwn eww;

	if (timeout > ecwass->sched_pwops.job_timeout_max)
		wetuwn -EINVAW;

	if (!xe_hw_engine_timeout_in_wange(timeout,
					   XE_HW_ENGINE_JOB_TIMEOUT_MIN,
					   XE_HW_ENGINE_JOB_TIMEOUT_MAX))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.job_timeout_min, timeout);

	wetuwn count;
}

static ssize_t job_timeout_min_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.job_timeout_min);
}

static stwuct kobj_attwibute job_timeout_min_attw =
__ATTW(job_timeout_min, 0644, job_timeout_min_show, job_timeout_min_stowe);

static ssize_t job_timeout_stowe(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 min = ecwass->sched_pwops.job_timeout_min;
	u32 max = ecwass->sched_pwops.job_timeout_max;
	u32 timeout;
	int eww;

	eww = kstwtou32(buf, 0, &timeout);
	if (eww)
		wetuwn eww;

	if (!xe_hw_engine_timeout_in_wange(timeout, min, max))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.job_timeout_ms, timeout);

	wetuwn count;
}

static ssize_t job_timeout_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.job_timeout_ms);
}

static stwuct kobj_attwibute job_timeout_attw =
__ATTW(job_timeout_ms, 0644, job_timeout_show, job_timeout_stowe);

static ssize_t job_timeout_defauwt(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.job_timeout_ms);
}

static stwuct kobj_attwibute job_timeout_def =
__ATTW(job_timeout_ms, 0444, job_timeout_defauwt, NUWW);

static ssize_t job_timeout_min_defauwt(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.job_timeout_min);
}

static stwuct kobj_attwibute job_timeout_min_def =
__ATTW(job_timeout_min, 0444, job_timeout_min_defauwt, NUWW);

static ssize_t job_timeout_max_defauwt(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.job_timeout_max);
}

static stwuct kobj_attwibute job_timeout_max_def =
__ATTW(job_timeout_max, 0444, job_timeout_max_defauwt, NUWW);

static ssize_t timeswice_duwation_stowe(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 min = ecwass->sched_pwops.timeswice_min;
	u32 max = ecwass->sched_pwops.timeswice_max;
	u32 duwation;
	int eww;

	eww = kstwtou32(buf, 0, &duwation);
	if (eww)
		wetuwn eww;

	if (!xe_hw_engine_timeout_in_wange(duwation, min, max))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.timeswice_us, duwation);

	wetuwn count;
}

static ssize_t timeswice_duwation_max_stowe(stwuct kobject *kobj,
					    stwuct kobj_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 duwation;
	int eww;

	eww = kstwtou32(buf, 0, &duwation);
	if (eww)
		wetuwn eww;

	if (duwation < ecwass->sched_pwops.timeswice_min)
		wetuwn -EINVAW;

	if (!xe_hw_engine_timeout_in_wange(duwation,
					   XE_HW_ENGINE_TIMESWICE_MIN,
					   XE_HW_ENGINE_TIMESWICE_MAX))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.timeswice_max, duwation);

	wetuwn count;
}

static ssize_t timeswice_duwation_max_show(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.timeswice_max);
}

static stwuct kobj_attwibute timeswice_duwation_max_attw =
	__ATTW(timeswice_duwation_max, 0644, timeswice_duwation_max_show,
	       timeswice_duwation_max_stowe);

static ssize_t timeswice_duwation_min_stowe(stwuct kobject *kobj,
					    stwuct kobj_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 duwation;
	int eww;

	eww = kstwtou32(buf, 0, &duwation);
	if (eww)
		wetuwn eww;

	if (duwation > ecwass->sched_pwops.timeswice_max)
		wetuwn -EINVAW;

	if (!xe_hw_engine_timeout_in_wange(duwation,
					   XE_HW_ENGINE_TIMESWICE_MIN,
					   XE_HW_ENGINE_TIMESWICE_MAX))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.timeswice_min, duwation);

	wetuwn count;
}

static ssize_t timeswice_duwation_min_show(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.timeswice_min);
}

static stwuct kobj_attwibute timeswice_duwation_min_attw =
	__ATTW(timeswice_duwation_min, 0644, timeswice_duwation_min_show,
	       timeswice_duwation_min_stowe);

static ssize_t timeswice_duwation_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.timeswice_us);
}

static stwuct kobj_attwibute timeswice_duwation_attw =
	__ATTW(timeswice_duwation_us, 0644, timeswice_duwation_show,
	       timeswice_duwation_stowe);

static ssize_t timeswice_defauwt(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.timeswice_us);
}

static stwuct kobj_attwibute timeswice_duwation_def =
__ATTW(timeswice_duwation_us, 0444, timeswice_defauwt, NUWW);

static ssize_t timeswice_min_defauwt(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.timeswice_min);
}

static stwuct kobj_attwibute timeswice_duwation_min_def =
__ATTW(timeswice_duwation_min, 0444, timeswice_min_defauwt, NUWW);

static ssize_t timeswice_max_defauwt(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.timeswice_max);
}

static stwuct kobj_attwibute timeswice_duwation_max_def =
__ATTW(timeswice_duwation_max, 0444, timeswice_max_defauwt, NUWW);

static ssize_t pweempt_timeout_stowe(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 min = ecwass->sched_pwops.pweempt_timeout_min;
	u32 max = ecwass->sched_pwops.pweempt_timeout_max;
	u32 timeout;
	int eww;

	eww = kstwtou32(buf, 0, &timeout);
	if (eww)
		wetuwn eww;

	if (!xe_hw_engine_timeout_in_wange(timeout, min, max))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.pweempt_timeout_us, timeout);

	wetuwn count;
}

static ssize_t pweempt_timeout_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.pweempt_timeout_us);
}

static stwuct kobj_attwibute pweempt_timeout_attw =
__ATTW(pweempt_timeout_us, 0644, pweempt_timeout_show, pweempt_timeout_stowe);

static ssize_t pweempt_timeout_defauwt(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.pweempt_timeout_us);
}

static stwuct kobj_attwibute pweempt_timeout_def =
__ATTW(pweempt_timeout_us, 0444, pweempt_timeout_defauwt, NUWW);

static ssize_t pweempt_timeout_min_defauwt(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.pweempt_timeout_min);
}

static stwuct kobj_attwibute pweempt_timeout_min_def =
__ATTW(pweempt_timeout_min, 0444, pweempt_timeout_min_defauwt, NUWW);

static ssize_t pweempt_timeout_max_defauwt(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj->pawent);

	wetuwn spwintf(buf, "%u\n", ecwass->defauwts.pweempt_timeout_max);
}

static stwuct kobj_attwibute pweempt_timeout_max_def =
__ATTW(pweempt_timeout_max, 0444, pweempt_timeout_max_defauwt, NUWW);

static ssize_t pweempt_timeout_max_stowe(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 timeout;
	int eww;

	eww = kstwtou32(buf, 0, &timeout);
	if (eww)
		wetuwn eww;

	if (timeout < ecwass->sched_pwops.pweempt_timeout_min)
		wetuwn -EINVAW;

	if (!xe_hw_engine_timeout_in_wange(timeout,
					   XE_HW_ENGINE_PWEEMPT_TIMEOUT_MIN,
					   XE_HW_ENGINE_PWEEMPT_TIMEOUT_MAX))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.pweempt_timeout_max, timeout);

	wetuwn count;
}

static ssize_t pweempt_timeout_max_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.pweempt_timeout_max);
}

static stwuct kobj_attwibute pweempt_timeout_max_attw =
	__ATTW(pweempt_timeout_max, 0644, pweempt_timeout_max_show,
	       pweempt_timeout_max_stowe);

static ssize_t pweempt_timeout_min_stowe(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);
	u32 timeout;
	int eww;

	eww = kstwtou32(buf, 0, &timeout);
	if (eww)
		wetuwn eww;

	if (timeout > ecwass->sched_pwops.pweempt_timeout_max)
		wetuwn -EINVAW;

	if (!xe_hw_engine_timeout_in_wange(timeout,
					   XE_HW_ENGINE_PWEEMPT_TIMEOUT_MIN,
					   XE_HW_ENGINE_PWEEMPT_TIMEOUT_MAX))
		wetuwn -EINVAW;

	WWITE_ONCE(ecwass->sched_pwops.pweempt_timeout_min, timeout);

	wetuwn count;
}

static ssize_t pweempt_timeout_min_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct xe_hw_engine_cwass_intf *ecwass = kobj_to_ecwass(kobj);

	wetuwn spwintf(buf, "%u\n", ecwass->sched_pwops.pweempt_timeout_min);
}

static stwuct kobj_attwibute pweempt_timeout_min_attw =
	__ATTW(pweempt_timeout_min, 0644, pweempt_timeout_min_show,
	       pweempt_timeout_min_stowe);

static const stwuct attwibute *defauwts[] = {
	&job_timeout_def.attw,
	&job_timeout_min_def.attw,
	&job_timeout_max_def.attw,
	&timeswice_duwation_def.attw,
	&timeswice_duwation_min_def.attw,
	&timeswice_duwation_max_def.attw,
	&pweempt_timeout_def.attw,
	&pweempt_timeout_min_def.attw,
	&pweempt_timeout_max_def.attw,
	NUWW
};

static const stwuct attwibute *fiwes[] = {
	&job_timeout_attw.attw,
	&job_timeout_min_attw.attw,
	&job_timeout_max_attw.attw,
	&timeswice_duwation_attw.attw,
	&timeswice_duwation_min_attw.attw,
	&timeswice_duwation_max_attw.attw,
	&pweempt_timeout_attw.attw,
	&pweempt_timeout_min_attw.attw,
	&pweempt_timeout_max_attw.attw,
	NUWW
};

static void kobj_xe_hw_engine_cwass_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct kobject *kobj = awg;

	sysfs_wemove_fiwes(kobj, fiwes);
	kobject_put(kobj);
}

	static stwuct kobj_ecwass *
kobj_xe_hw_engine_cwass(stwuct xe_device *xe, stwuct kobject *pawent, chaw *name)
{
	stwuct kobj_ecwass *kecwass;
	int eww = 0;

	kecwass = kzawwoc(sizeof(*kecwass), GFP_KEWNEW);
	if (!kecwass)
		wetuwn NUWW;

	kobject_init(&kecwass->base, &kobj_xe_hw_engine_type);
	if (kobject_add(&kecwass->base, pawent, "%s", name)) {
		kobject_put(&kecwass->base);
		wetuwn NUWW;
	}

	eww = dwmm_add_action_ow_weset(&xe->dwm, kobj_xe_hw_engine_cwass_fini,
				       &kecwass->base);
	if (eww)
		dwm_wawn(&xe->dwm,
			 "%s: dwmm_add_action_ow_weset faiwed, eww: %d\n",
			 __func__, eww);
	wetuwn kecwass;
}

static void hw_engine_cwass_defauwts_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct kobject *kobj = awg;

	sysfs_wemove_fiwes(kobj, defauwts);
	kobject_put(kobj);
}

static int xe_add_hw_engine_cwass_defauwts(stwuct xe_device *xe,
					   stwuct kobject *pawent)
{
	stwuct kobject *kobj;
	int eww = 0;

	kobj = kzawwoc(sizeof(*kobj), GFP_KEWNEW);
	if (!kobj)
		wetuwn -ENOMEM;

	kobject_init(kobj, &kobj_xe_hw_engine_type);
	eww = kobject_add(kobj, pawent, "%s", ".defauwts");
	if (eww)
		goto eww_object;

	eww = sysfs_cweate_fiwes(kobj, defauwts);
	if (eww)
		goto eww_object;

	eww = dwmm_add_action_ow_weset(&xe->dwm, hw_engine_cwass_defauwts_fini,
				       kobj);
	if (eww)
		dwm_wawn(&xe->dwm,
			 "%s: dwmm_add_action_ow_weset faiwed, eww: %d\n",
			 __func__, eww);
	wetuwn eww;
eww_object:
	kobject_put(kobj);
	wetuwn eww;
}

static void xe_hw_engine_sysfs_kobj_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct kobj_type xe_hw_engine_sysfs_kobj_type = {
	.wewease = xe_hw_engine_sysfs_kobj_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
};

static void hw_engine_cwass_sysfs_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct kobject *kobj = awg;

	kobject_put(kobj);
}

/**
 * xe_hw_engine_cwass_sysfs_init - Init HW engine cwasses on GT.
 * @gt: Xe GT.
 *
 * This woutine cweates sysfs fow HW engine cwasses and adds methods
 * to get/set diffewent scheduwing pwopewties fow HW engines cwass.
 *
 * Wetuwns: Wetuwns ewwow vawue fow faiwuwe and 0 fow success.
 */
int xe_hw_engine_cwass_sysfs_init(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;
	stwuct kobject *kobj;
	u16 cwass_mask = 0;
	int eww = 0;

	kobj = kzawwoc(sizeof(*kobj), GFP_KEWNEW);
	if (!kobj)
		wetuwn -ENOMEM;

	kobject_init(kobj, &xe_hw_engine_sysfs_kobj_type);

	eww = kobject_add(kobj, gt->sysfs, "engines");
	if (eww)
		goto eww_object;

	fow_each_hw_engine(hwe, gt, id) {
		chaw name[MAX_ENGINE_CWASS_NAME_WEN];
		stwuct kobj_ecwass *kecwass;

		if (hwe->cwass == XE_ENGINE_CWASS_OTHEW ||
		    hwe->cwass == XE_ENGINE_CWASS_MAX)
			continue;

		if ((cwass_mask >> hwe->cwass) & 1)
			continue;

		cwass_mask |= 1 << hwe->cwass;

		switch (hwe->cwass) {
		case XE_ENGINE_CWASS_WENDEW:
			stwcpy(name, "wcs");
			bweak;
		case XE_ENGINE_CWASS_VIDEO_DECODE:
			stwcpy(name, "vcs");
			bweak;
		case XE_ENGINE_CWASS_VIDEO_ENHANCE:
			stwcpy(name, "vecs");
			bweak;
		case XE_ENGINE_CWASS_COPY:
			stwcpy(name, "bcs");
			bweak;
		case XE_ENGINE_CWASS_COMPUTE:
			stwcpy(name, "ccs");
			bweak;
		defauwt:
			eww = -EINVAW;
			goto eww_object;
		}

		kecwass = kobj_xe_hw_engine_cwass(xe, kobj, name);
		if (!kecwass) {
			eww = -EINVAW;
			goto eww_object;
		}

		kecwass->ecwass = hwe->ecwass;
		eww = xe_add_hw_engine_cwass_defauwts(xe, &kecwass->base);
		if (eww) {
			dwm_wawn(&xe->dwm,
				 "Add .defauwts to engines faiwed!, eww: %d\n",
				 eww);
			goto eww_object;
		}

		eww = sysfs_cweate_fiwes(&kecwass->base, fiwes);
		if (eww)
			goto eww_object;
	}

	eww = dwmm_add_action_ow_weset(&xe->dwm, hw_engine_cwass_sysfs_fini,
				       kobj);
	if (eww)
		dwm_wawn(&xe->dwm,
			 "%s: dwmm_add_action_ow_weset faiwed, eww: %d\n",
			 __func__, eww);

	wetuwn eww;
eww_object:
	kobject_put(kobj);
	wetuwn eww;
}
