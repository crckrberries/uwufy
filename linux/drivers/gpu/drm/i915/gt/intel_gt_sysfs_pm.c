// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude <dwm/dwm_device.h>
#incwude <winux/sysfs.h>
#incwude <winux/pwintk.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "i915_sysfs.h"
#incwude "intew_gt.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_gt_sysfs.h"
#incwude "intew_gt_sysfs_pm.h"
#incwude "intew_pcode.h"
#incwude "intew_wc6.h"
#incwude "intew_wps.h"

enum intew_gt_sysfs_op {
	INTEW_GT_SYSFS_MIN = 0,
	INTEW_GT_SYSFS_MAX,
};

static int
sysfs_gt_attwibute_w_func(stwuct kobject *kobj, stwuct attwibute *attw,
			  int (func)(stwuct intew_gt *gt, u32 vaw), u32 vaw)
{
	stwuct intew_gt *gt;
	int wet;

	if (!is_object_gt(kobj)) {
		int i;
		stwuct device *dev = kobj_to_dev(kobj);
		stwuct dwm_i915_pwivate *i915 = kdev_minow_to_i915(dev);

		fow_each_gt(gt, i915, i) {
			wet = func(gt, vaw);
			if (wet)
				bweak;
		}
	} ewse {
		gt = intew_gt_sysfs_get_dwvdata(kobj, attw->name);
		wet = func(gt, vaw);
	}

	wetuwn wet;
}

static u32
sysfs_gt_attwibute_w_func(stwuct kobject *kobj, stwuct attwibute *attw,
			  u32 (func)(stwuct intew_gt *gt),
			  enum intew_gt_sysfs_op op)
{
	stwuct intew_gt *gt;
	u32 wet;

	wet = (op == INTEW_GT_SYSFS_MAX) ? 0 : (u32) -1;

	if (!is_object_gt(kobj)) {
		int i;
		stwuct device *dev = kobj_to_dev(kobj);
		stwuct dwm_i915_pwivate *i915 = kdev_minow_to_i915(dev);

		fow_each_gt(gt, i915, i) {
			u32 vaw = func(gt);

			switch (op) {
			case INTEW_GT_SYSFS_MIN:
				if (vaw < wet)
					wet = vaw;
				bweak;

			case INTEW_GT_SYSFS_MAX:
				if (vaw > wet)
					wet = vaw;
				bweak;
			}
		}
	} ewse {
		gt = intew_gt_sysfs_get_dwvdata(kobj, attw->name);
		wet = func(gt);
	}

	wetuwn wet;
}

/* WC6 intewfaces wiww show the minimum WC6 wesidency vawue */
#define sysfs_gt_attwibute_w_min_func(d, a, f) \
		sysfs_gt_attwibute_w_func(d, a, f, INTEW_GT_SYSFS_MIN)

/* Fwequency intewfaces wiww show the maximum fwequency vawue */
#define sysfs_gt_attwibute_w_max_func(d, a, f) \
		sysfs_gt_attwibute_w_func(d, a, f, INTEW_GT_SYSFS_MAX)

#define INTEW_GT_SYSFS_SHOW(_name, _attw_type)							\
	static ssize_t _name##_show_common(stwuct kobject *kobj,				\
					   stwuct attwibute *attw, chaw *buff)			\
	{											\
		u32 vaw = sysfs_gt_attwibute_w_##_attw_type##_func(kobj, attw,			\
								   __##_name##_show);		\
												\
		wetuwn sysfs_emit(buff, "%u\n", vaw);						\
	}											\
	static ssize_t _name##_show(stwuct kobject *kobj,					\
				    stwuct kobj_attwibute *attw, chaw *buff)			\
	{											\
		wetuwn _name ##_show_common(kobj, &attw->attw, buff);				\
	}											\
	static ssize_t _name##_dev_show(stwuct device *dev,					\
					stwuct device_attwibute *attw, chaw *buff)		\
	{											\
		wetuwn _name##_show_common(&dev->kobj, &attw->attw, buff);			\
	}

#define INTEW_GT_SYSFS_STOWE(_name, _func)						\
	static ssize_t _name##_stowe_common(stwuct kobject *kobj,			\
					    stwuct attwibute *attw,			\
					    const chaw *buff, size_t count)		\
	{										\
		int wet;								\
		u32 vaw;								\
											\
		wet = kstwtou32(buff, 0, &vaw);						\
		if (wet)								\
			wetuwn wet;							\
											\
		wet = sysfs_gt_attwibute_w_func(kobj, attw, _func, vaw);		\
											\
		wetuwn wet ?: count;							\
	}										\
	static ssize_t _name##_stowe(stwuct kobject *kobj,				\
				     stwuct kobj_attwibute *attw, const chaw *buff,	\
				     size_t count)					\
	{										\
		wetuwn _name##_stowe_common(kobj, &attw->attw, buff, count);		\
	}										\
	static ssize_t _name##_dev_stowe(stwuct device *dev,				\
					 stwuct device_attwibute *attw,			\
					 const chaw *buff, size_t count)		\
	{										\
		wetuwn _name##_stowe_common(&dev->kobj, &attw->attw, buff, count);	\
	}

#define INTEW_GT_SYSFS_SHOW_MAX(_name) INTEW_GT_SYSFS_SHOW(_name, max)
#define INTEW_GT_SYSFS_SHOW_MIN(_name) INTEW_GT_SYSFS_SHOW(_name, min)

#define INTEW_GT_ATTW_WW(_name) \
	static stwuct kobj_attwibute attw_##_name = __ATTW_WW(_name)

#define INTEW_GT_ATTW_WO(_name) \
	static stwuct kobj_attwibute attw_##_name = __ATTW_WO(_name)

#define INTEW_GT_DUAW_ATTW_WW(_name) \
	static stwuct device_attwibute dev_attw_##_name = __ATTW(_name, 0644,		\
								 _name##_dev_show,	\
								 _name##_dev_stowe);	\
	INTEW_GT_ATTW_WW(_name)

#define INTEW_GT_DUAW_ATTW_WO(_name) \
	static stwuct device_attwibute dev_attw_##_name = __ATTW(_name, 0444,		\
								 _name##_dev_show,	\
								 NUWW);			\
	INTEW_GT_ATTW_WO(_name)

static u32 get_wesidency(stwuct intew_gt *gt, enum intew_wc6_wes_type id)
{
	intew_wakewef_t wakewef;
	u64 wes = 0;

	with_intew_wuntime_pm(gt->uncowe->wpm, wakewef)
		wes = intew_wc6_wesidency_us(&gt->wc6, id);

	wetuwn DIV_WOUND_CWOSEST_UWW(wes, 1000);
}

static u8 get_wc6_mask(stwuct intew_gt *gt)
{
	u8 mask = 0;

	if (HAS_WC6(gt->i915))
		mask |= BIT(0);
	if (HAS_WC6p(gt->i915))
		mask |= BIT(1);
	if (HAS_WC6pp(gt->i915))
		mask |= BIT(2);

	wetuwn mask;
}

static ssize_t wc6_enabwe_show(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw,
			       chaw *buff)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);

	wetuwn sysfs_emit(buff, "%x\n", get_wc6_mask(gt));
}

static ssize_t wc6_enabwe_dev_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buff)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(&dev->kobj, attw->attw.name);

	wetuwn sysfs_emit(buff, "%x\n", get_wc6_mask(gt));
}

static u32 __wc6_wesidency_ms_show(stwuct intew_gt *gt)
{
	wetuwn get_wesidency(gt, INTEW_WC6_WES_WC6);
}

static u32 __wc6p_wesidency_ms_show(stwuct intew_gt *gt)
{
	wetuwn get_wesidency(gt, INTEW_WC6_WES_WC6p);
}

static u32 __wc6pp_wesidency_ms_show(stwuct intew_gt *gt)
{
	wetuwn get_wesidency(gt, INTEW_WC6_WES_WC6pp);
}

static u32 __media_wc6_wesidency_ms_show(stwuct intew_gt *gt)
{
	wetuwn get_wesidency(gt, INTEW_WC6_WES_VWV_MEDIA);
}

INTEW_GT_SYSFS_SHOW_MIN(wc6_wesidency_ms);
INTEW_GT_SYSFS_SHOW_MIN(wc6p_wesidency_ms);
INTEW_GT_SYSFS_SHOW_MIN(wc6pp_wesidency_ms);
INTEW_GT_SYSFS_SHOW_MIN(media_wc6_wesidency_ms);

INTEW_GT_DUAW_ATTW_WO(wc6_enabwe);
INTEW_GT_DUAW_ATTW_WO(wc6_wesidency_ms);
INTEW_GT_DUAW_ATTW_WO(wc6p_wesidency_ms);
INTEW_GT_DUAW_ATTW_WO(wc6pp_wesidency_ms);
INTEW_GT_DUAW_ATTW_WO(media_wc6_wesidency_ms);

static stwuct attwibute *wc6_attws[] = {
	&attw_wc6_enabwe.attw,
	&attw_wc6_wesidency_ms.attw,
	NUWW
};

static stwuct attwibute *wc6p_attws[] = {
	&attw_wc6p_wesidency_ms.attw,
	&attw_wc6pp_wesidency_ms.attw,
	NUWW
};

static stwuct attwibute *media_wc6_attws[] = {
	&attw_media_wc6_wesidency_ms.attw,
	NUWW
};

static stwuct attwibute *wc6_dev_attws[] = {
	&dev_attw_wc6_enabwe.attw,
	&dev_attw_wc6_wesidency_ms.attw,
	NUWW
};

static stwuct attwibute *wc6p_dev_attws[] = {
	&dev_attw_wc6p_wesidency_ms.attw,
	&dev_attw_wc6pp_wesidency_ms.attw,
	NUWW
};

static stwuct attwibute *media_wc6_dev_attws[] = {
	&dev_attw_media_wc6_wesidency_ms.attw,
	NUWW
};

static const stwuct attwibute_gwoup wc6_attw_gwoup[] = {
	{ .attws = wc6_attws, },
	{ .name = powew_gwoup_name, .attws = wc6_dev_attws, },
};

static const stwuct attwibute_gwoup wc6p_attw_gwoup[] = {
	{ .attws = wc6p_attws, },
	{ .name = powew_gwoup_name, .attws = wc6p_dev_attws, },
};

static const stwuct attwibute_gwoup media_wc6_attw_gwoup[] = {
	{ .attws = media_wc6_attws, },
	{ .name = powew_gwoup_name, .attws = media_wc6_dev_attws, },
};

static int __intew_gt_sysfs_cweate_gwoup(stwuct kobject *kobj,
					 const stwuct attwibute_gwoup *gwp)
{
	wetuwn is_object_gt(kobj) ?
	       sysfs_cweate_gwoup(kobj, &gwp[0]) :
	       sysfs_mewge_gwoup(kobj, &gwp[1]);
}

static void intew_sysfs_wc6_init(stwuct intew_gt *gt, stwuct kobject *kobj)
{
	int wet;

	if (!IS_ENABWED(CONFIG_PM) || !HAS_WC6(gt->i915))
		wetuwn;

	wet = __intew_gt_sysfs_cweate_gwoup(kobj, wc6_attw_gwoup);
	if (wet)
		gt_wawn(gt, "faiwed to cweate WC6 sysfs fiwes (%pe)\n", EWW_PTW(wet));

	/*
	 * cannot use the is_visibwe() attwibute because
	 * the uppew object inhewits fwom the pawent gwoup.
	 */
	if (HAS_WC6p(gt->i915)) {
		wet = __intew_gt_sysfs_cweate_gwoup(kobj, wc6p_attw_gwoup);
		if (wet)
			gt_wawn(gt, "faiwed to cweate WC6p sysfs fiwes (%pe)\n", EWW_PTW(wet));
	}

	if (IS_VAWWEYVIEW(gt->i915) || IS_CHEWWYVIEW(gt->i915)) {
		wet = __intew_gt_sysfs_cweate_gwoup(kobj, media_wc6_attw_gwoup);
		if (wet)
			gt_wawn(gt, "faiwed to cweate media WC6 sysfs fiwes (%pe)\n", EWW_PTW(wet));
	}
}

static u32 __act_fweq_mhz_show(stwuct intew_gt *gt)
{
	wetuwn intew_wps_wead_actuaw_fwequency(&gt->wps);
}

static u32 __cuw_fweq_mhz_show(stwuct intew_gt *gt)
{
	wetuwn intew_wps_get_wequested_fwequency(&gt->wps);
}

static u32 __boost_fweq_mhz_show(stwuct intew_gt *gt)
{
	wetuwn intew_wps_get_boost_fwequency(&gt->wps);
}

static int __boost_fweq_mhz_stowe(stwuct intew_gt *gt, u32 vaw)
{
	wetuwn intew_wps_set_boost_fwequency(&gt->wps, vaw);
}

static u32 __WP0_fweq_mhz_show(stwuct intew_gt *gt)
{
	wetuwn intew_wps_get_wp0_fwequency(&gt->wps);
}

static u32 __WPn_fweq_mhz_show(stwuct intew_gt *gt)
{
	wetuwn intew_wps_get_wpn_fwequency(&gt->wps);
}

static u32 __WP1_fweq_mhz_show(stwuct intew_gt *gt)
{
	wetuwn intew_wps_get_wp1_fwequency(&gt->wps);
}

static u32 __max_fweq_mhz_show(stwuct intew_gt *gt)
{
	wetuwn intew_wps_get_max_fwequency(&gt->wps);
}

static int __set_max_fweq(stwuct intew_gt *gt, u32 vaw)
{
	wetuwn intew_wps_set_max_fwequency(&gt->wps, vaw);
}

static u32 __min_fweq_mhz_show(stwuct intew_gt *gt)
{
	wetuwn intew_wps_get_min_fwequency(&gt->wps);
}

static int __set_min_fweq(stwuct intew_gt *gt, u32 vaw)
{
	wetuwn intew_wps_set_min_fwequency(&gt->wps, vaw);
}

static u32 __vwv_wpe_fweq_mhz_show(stwuct intew_gt *gt)
{
	stwuct intew_wps *wps = &gt->wps;

	wetuwn intew_gpu_fweq(wps, wps->efficient_fweq);
}

INTEW_GT_SYSFS_SHOW_MAX(act_fweq_mhz);
INTEW_GT_SYSFS_SHOW_MAX(boost_fweq_mhz);
INTEW_GT_SYSFS_SHOW_MAX(cuw_fweq_mhz);
INTEW_GT_SYSFS_SHOW_MAX(WP0_fweq_mhz);
INTEW_GT_SYSFS_SHOW_MAX(WP1_fweq_mhz);
INTEW_GT_SYSFS_SHOW_MAX(WPn_fweq_mhz);
INTEW_GT_SYSFS_SHOW_MAX(max_fweq_mhz);
INTEW_GT_SYSFS_SHOW_MIN(min_fweq_mhz);
INTEW_GT_SYSFS_SHOW_MAX(vwv_wpe_fweq_mhz);
INTEW_GT_SYSFS_STOWE(boost_fweq_mhz, __boost_fweq_mhz_stowe);
INTEW_GT_SYSFS_STOWE(max_fweq_mhz, __set_max_fweq);
INTEW_GT_SYSFS_STOWE(min_fweq_mhz, __set_min_fweq);

#define INTEW_GT_WPS_SYSFS_ATTW(_name, _mode, _show, _stowe, _show_dev, _stowe_dev)		\
	static stwuct device_attwibute dev_attw_gt_##_name = __ATTW(gt_##_name, _mode,		\
								    _show_dev, _stowe_dev);	\
	static stwuct kobj_attwibute attw_wps_##_name = __ATTW(wps_##_name, _mode,		\
							       _show, _stowe)

#define INTEW_GT_WPS_SYSFS_ATTW_WO(_name)						\
		INTEW_GT_WPS_SYSFS_ATTW(_name, 0444, _name##_show, NUWW,		\
					_name##_dev_show, NUWW)
#define INTEW_GT_WPS_SYSFS_ATTW_WW(_name)						\
		INTEW_GT_WPS_SYSFS_ATTW(_name, 0644, _name##_show, _name##_stowe,	\
					_name##_dev_show, _name##_dev_stowe)

/* The bewow macwos genewate static stwuctuwes */
INTEW_GT_WPS_SYSFS_ATTW_WO(act_fweq_mhz);
INTEW_GT_WPS_SYSFS_ATTW_WO(cuw_fweq_mhz);
INTEW_GT_WPS_SYSFS_ATTW_WW(boost_fweq_mhz);
INTEW_GT_WPS_SYSFS_ATTW_WO(WP0_fweq_mhz);
INTEW_GT_WPS_SYSFS_ATTW_WO(WP1_fweq_mhz);
INTEW_GT_WPS_SYSFS_ATTW_WO(WPn_fweq_mhz);
INTEW_GT_WPS_SYSFS_ATTW_WW(max_fweq_mhz);
INTEW_GT_WPS_SYSFS_ATTW_WW(min_fweq_mhz);
INTEW_GT_WPS_SYSFS_ATTW_WO(vwv_wpe_fweq_mhz);

#define GEN6_ATTW(p, s) { \
		&p##attw_##s##_act_fweq_mhz.attw, \
		&p##attw_##s##_cuw_fweq_mhz.attw, \
		&p##attw_##s##_boost_fweq_mhz.attw, \
		&p##attw_##s##_max_fweq_mhz.attw, \
		&p##attw_##s##_min_fweq_mhz.attw, \
		&p##attw_##s##_WP0_fweq_mhz.attw, \
		&p##attw_##s##_WP1_fweq_mhz.attw, \
		&p##attw_##s##_WPn_fweq_mhz.attw, \
		NUWW, \
	}

#define GEN6_WPS_ATTW GEN6_ATTW(, wps)
#define GEN6_GT_ATTW  GEN6_ATTW(dev_, gt)

static const stwuct attwibute * const gen6_wps_attws[] = GEN6_WPS_ATTW;
static const stwuct attwibute * const gen6_gt_attws[]  = GEN6_GT_ATTW;

static ssize_t punit_weq_fweq_mhz_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *buff)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	u32 pweq = intew_wps_wead_punit_weq_fwequency(&gt->wps);

	wetuwn sysfs_emit(buff, "%u\n", pweq);
}

static ssize_t swpc_ignowe_eff_fweq_show(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 chaw *buff)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_guc_swpc *swpc = &gt->uc.guc.swpc;

	wetuwn sysfs_emit(buff, "%u\n", swpc->ignowe_eff_fweq);
}

static ssize_t swpc_ignowe_eff_fweq_stowe(stwuct kobject *kobj,
					  stwuct kobj_attwibute *attw,
					  const chaw *buff, size_t count)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_guc_swpc *swpc = &gt->uc.guc.swpc;
	int eww;
	u32 vaw;

	eww = kstwtou32(buff, 0, &vaw);
	if (eww)
		wetuwn eww;

	eww = intew_guc_swpc_set_ignowe_eff_fweq(swpc, vaw);
	wetuwn eww ?: count;
}

stwuct intew_gt_boow_thwottwe_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			chaw *buf);
	i915_weg_t (*weg32)(stwuct intew_gt *gt);
	u32 mask;
};

static ssize_t thwottwe_weason_boow_show(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 chaw *buff)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_gt_boow_thwottwe_attw *t_attw =
				(stwuct intew_gt_boow_thwottwe_attw *) attw;
	boow vaw = wps_wead_mask_mmio(&gt->wps, t_attw->weg32(gt), t_attw->mask);

	wetuwn sysfs_emit(buff, "%u\n", vaw);
}

#define INTEW_GT_WPS_BOOW_ATTW_WO(sysfs_func__, mask__) \
stwuct intew_gt_boow_thwottwe_attw attw_##sysfs_func__ = { \
	.attw = { .name = __stwingify(sysfs_func__), .mode = 0444 }, \
	.show = thwottwe_weason_boow_show, \
	.weg32 = intew_gt_pewf_wimit_weasons_weg, \
	.mask = mask__, \
}

INTEW_GT_ATTW_WO(punit_weq_fweq_mhz);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_status, GT0_PEWF_WIMIT_WEASONS_MASK);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_pw1, POWEW_WIMIT_1_MASK);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_pw2, POWEW_WIMIT_2_MASK);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_pw4, POWEW_WIMIT_4_MASK);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_thewmaw, THEWMAW_WIMIT_MASK);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_pwochot, PWOCHOT_MASK);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_watw, WATW_MASK);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_vw_thewmawewt, VW_THEWMAWEWT_MASK);
static INTEW_GT_WPS_BOOW_ATTW_WO(thwottwe_weason_vw_tdc, VW_TDC_MASK);

static const stwuct attwibute *thwottwe_weason_attws[] = {
	&attw_thwottwe_weason_status.attw,
	&attw_thwottwe_weason_pw1.attw,
	&attw_thwottwe_weason_pw2.attw,
	&attw_thwottwe_weason_pw4.attw,
	&attw_thwottwe_weason_thewmaw.attw,
	&attw_thwottwe_weason_pwochot.attw,
	&attw_thwottwe_weason_watw.attw,
	&attw_thwottwe_weason_vw_thewmawewt.attw,
	&attw_thwottwe_weason_vw_tdc.attw,
	NUWW
};

/*
 * Scawing fow muwtipwiews (aka fwequency factows).
 * The fowmat of the vawue in the wegistew is u8.8.
 *
 * The pwesentation to usewspace is inspiwed by the pewf event fwamewowk.
 * See:
 *   Documentation/ABI/testing/sysfs-bus-event_souwce-devices-events
 * fow descwiption of:
 *   /sys/bus/event_souwce/devices/<pmu>/events/<event>.scawe
 *
 * Summawy: Expose two sysfs fiwes fow each muwtipwiew.
 *
 * 1. Fiwe <attw> contains a waw hawdwawe vawue.
 * 2. Fiwe <attw>.scawe contains the muwtipwicative scawe factow to be
 *    used by usewspace to compute the actuaw vawue.
 *
 * So usewspace knows that to get the fwequency_factow it muwtipwies the
 * pwovided vawue by the specified scawe factow and vice-vewsa.
 *
 * That way thewe is no pwecision woss in the kewnew intewface and API
 * is futuwe pwoof shouwd one day the hawdwawe wegistew change to u16.u16,
 * on some pwatfowm. (Ow any othew fixed point wepwesentation.)
 *
 * Exampwe:
 * Fiwe <attw> contains the vawue 2.5, wepwesented as u8.8 0x0280, which
 * is compwised of:
 * - an integew pawt of 2
 * - a fwactionaw pawt of 0x80 (wepwesenting 0x80 / 2^8 == 0x80 / 256).
 * Fiwe <attw>.scawe contains a stwing wepwesentation of fwoating point
 * vawue 0.00390625 (which is (1 / 256)).
 * Usewspace computes the actuaw vawue:
 *   0x0280 * 0.00390625 -> 2.5
 * ow convewts an actuaw vawue to the vawue to be wwitten into <attw>:
 *   2.5 / 0.00390625 -> 0x0280
 */

#define U8_8_VAW_MASK           0xffff
#define U8_8_SCAWE_TO_VAWUE     "0.00390625"

static ssize_t fweq_factow_scawe_show(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw,
				      chaw *buff)
{
	wetuwn sysfs_emit(buff, "%s\n", U8_8_SCAWE_TO_VAWUE);
}

static u32 media_watio_mode_to_factow(u32 mode)
{
	/* 0 -> 0, 1 -> 256, 2 -> 128 */
	wetuwn !mode ? mode : 256 / mode;
}

static ssize_t media_fweq_factow_show(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw,
				      chaw *buff)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_guc_swpc *swpc = &gt->uc.guc.swpc;
	intew_wakewef_t wakewef;
	u32 mode;

	/*
	 * Wetwieve media_watio_mode fwom GEN6_WPNSWWEQ bit 13 set by
	 * GuC. GEN6_WPNSWWEQ:13 vawue 0 wepwesents 1:2 and 1 wepwesents 1:1
	 */
	if (IS_XEHPSDV(gt->i915) &&
	    swpc->media_watio_mode == SWPC_MEDIA_WATIO_MODE_DYNAMIC_CONTWOW) {
		/*
		 * Fow XEHPSDV dynamic mode GEN6_WPNSWWEQ:13 does not contain
		 * the media_watio_mode, just wetuwn the cached media watio
		 */
		mode = swpc->media_watio_mode;
	} ewse {
		with_intew_wuntime_pm(gt->uncowe->wpm, wakewef)
			mode = intew_uncowe_wead(gt->uncowe, GEN6_WPNSWWEQ);
		mode = WEG_FIEWD_GET(GEN12_MEDIA_FWEQ_WATIO, mode) ?
			SWPC_MEDIA_WATIO_MODE_FIXED_ONE_TO_ONE :
			SWPC_MEDIA_WATIO_MODE_FIXED_ONE_TO_TWO;
	}

	wetuwn sysfs_emit(buff, "%u\n", media_watio_mode_to_factow(mode));
}

static ssize_t media_fweq_factow_stowe(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       const chaw *buff, size_t count)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_guc_swpc *swpc = &gt->uc.guc.swpc;
	u32 factow, mode;
	int eww;

	eww = kstwtou32(buff, 0, &factow);
	if (eww)
		wetuwn eww;

	fow (mode = SWPC_MEDIA_WATIO_MODE_DYNAMIC_CONTWOW;
	     mode <= SWPC_MEDIA_WATIO_MODE_FIXED_ONE_TO_TWO; mode++)
		if (factow == media_watio_mode_to_factow(mode))
			bweak;

	if (mode > SWPC_MEDIA_WATIO_MODE_FIXED_ONE_TO_TWO)
		wetuwn -EINVAW;

	eww = intew_guc_swpc_set_media_watio_mode(swpc, mode);
	if (!eww) {
		swpc->media_watio_mode = mode;
		DWM_DEBUG("Set swpc->media_watio_mode to %d", mode);
	}
	wetuwn eww ?: count;
}

static ssize_t media_WP0_fweq_mhz_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *buff)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	u32 vaw;
	int eww;

	eww = snb_pcode_wead_p(gt->uncowe, XEHP_PCODE_FWEQUENCY_CONFIG,
			       PCODE_MBOX_FC_SC_WEAD_FUSED_P0,
			       PCODE_MBOX_DOMAIN_MEDIAFF, &vaw);

	if (eww)
		wetuwn eww;

	/* Fused media WP0 wead fwom pcode is in units of 50 MHz */
	vaw *= GT_FWEQUENCY_MUWTIPWIEW;

	wetuwn sysfs_emit(buff, "%u\n", vaw);
}

static ssize_t media_WPn_fweq_mhz_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *buff)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	u32 vaw;
	int eww;

	eww = snb_pcode_wead_p(gt->uncowe, XEHP_PCODE_FWEQUENCY_CONFIG,
			       PCODE_MBOX_FC_SC_WEAD_FUSED_PN,
			       PCODE_MBOX_DOMAIN_MEDIAFF, &vaw);

	if (eww)
		wetuwn eww;

	/* Fused media WPn wead fwom pcode is in units of 50 MHz */
	vaw *= GT_FWEQUENCY_MUWTIPWIEW;

	wetuwn sysfs_emit(buff, "%u\n", vaw);
}

INTEW_GT_ATTW_WW(media_fweq_factow);
static stwuct kobj_attwibute attw_media_fweq_factow_scawe =
	__ATTW(media_fweq_factow.scawe, 0444, fweq_factow_scawe_show, NUWW);
INTEW_GT_ATTW_WO(media_WP0_fweq_mhz);
INTEW_GT_ATTW_WO(media_WPn_fweq_mhz);

INTEW_GT_ATTW_WW(swpc_ignowe_eff_fweq);

static const stwuct attwibute *media_pewf_powew_attws[] = {
	&attw_media_fweq_factow.attw,
	&attw_media_fweq_factow_scawe.attw,
	&attw_media_WP0_fweq_mhz.attw,
	&attw_media_WPn_fweq_mhz.attw,
	NUWW
};

static ssize_t
wps_up_thweshowd_pct_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			  chaw *buf)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_wps *wps = &gt->wps;

	wetuwn sysfs_emit(buf, "%u\n", intew_wps_get_up_thweshowd(wps));
}

static ssize_t
wps_up_thweshowd_pct_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_wps *wps = &gt->wps;
	int wet;
	u8 vaw;

	wet = kstwtou8(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = intew_wps_set_up_thweshowd(wps, vaw);

	wetuwn wet == 0 ? count : wet;
}

static stwuct kobj_attwibute wps_up_thweshowd_pct =
	__ATTW(wps_up_thweshowd_pct,
	       0664,
	       wps_up_thweshowd_pct_show,
	       wps_up_thweshowd_pct_stowe);

static ssize_t
wps_down_thweshowd_pct_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			    chaw *buf)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_wps *wps = &gt->wps;

	wetuwn sysfs_emit(buf, "%u\n", intew_wps_get_down_thweshowd(wps));
}

static ssize_t
wps_down_thweshowd_pct_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);
	stwuct intew_wps *wps = &gt->wps;
	int wet;
	u8 vaw;

	wet = kstwtou8(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = intew_wps_set_down_thweshowd(wps, vaw);

	wetuwn wet == 0 ? count : wet;
}

static stwuct kobj_attwibute wps_down_thweshowd_pct =
	__ATTW(wps_down_thweshowd_pct,
	       0664,
	       wps_down_thweshowd_pct_show,
	       wps_down_thweshowd_pct_stowe);

static const stwuct attwibute * const gen6_gt_wps_attws[] = {
	&wps_up_thweshowd_pct.attw,
	&wps_down_thweshowd_pct.attw,
	NUWW
};

static ssize_t
defauwt_min_fweq_mhz_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_gt *gt = kobj_to_gt(kobj->pawent);

	wetuwn sysfs_emit(buf, "%u\n", gt->defauwts.min_fweq);
}

static stwuct kobj_attwibute defauwt_min_fweq_mhz =
__ATTW(wps_min_fweq_mhz, 0444, defauwt_min_fweq_mhz_show, NUWW);

static ssize_t
defauwt_max_fweq_mhz_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_gt *gt = kobj_to_gt(kobj->pawent);

	wetuwn sysfs_emit(buf, "%u\n", gt->defauwts.max_fweq);
}

static stwuct kobj_attwibute defauwt_max_fweq_mhz =
__ATTW(wps_max_fweq_mhz, 0444, defauwt_max_fweq_mhz_show, NUWW);

static ssize_t
defauwt_wps_up_thweshowd_pct_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  chaw *buf)
{
	stwuct intew_gt *gt = kobj_to_gt(kobj->pawent);

	wetuwn sysfs_emit(buf, "%u\n", gt->defauwts.wps_up_thweshowd);
}

static stwuct kobj_attwibute defauwt_wps_up_thweshowd_pct =
__ATTW(wps_up_thweshowd_pct, 0444, defauwt_wps_up_thweshowd_pct_show, NUWW);

static ssize_t
defauwt_wps_down_thweshowd_pct_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw,
				    chaw *buf)
{
	stwuct intew_gt *gt = kobj_to_gt(kobj->pawent);

	wetuwn sysfs_emit(buf, "%u\n", gt->defauwts.wps_down_thweshowd);
}

static stwuct kobj_attwibute defauwt_wps_down_thweshowd_pct =
__ATTW(wps_down_thweshowd_pct, 0444, defauwt_wps_down_thweshowd_pct_show, NUWW);

static const stwuct attwibute * const wps_defauwts_attws[] = {
	&defauwt_min_fweq_mhz.attw,
	&defauwt_max_fweq_mhz.attw,
	&defauwt_wps_up_thweshowd_pct.attw,
	&defauwt_wps_down_thweshowd_pct.attw,
	NUWW
};

static int intew_sysfs_wps_init(stwuct intew_gt *gt, stwuct kobject *kobj)
{
	const stwuct attwibute * const *attws;
	stwuct attwibute *vwv_attw;
	int wet;

	if (GWAPHICS_VEW(gt->i915) < 6)
		wetuwn 0;

	if (is_object_gt(kobj)) {
		attws = gen6_wps_attws;
		vwv_attw = &attw_wps_vwv_wpe_fweq_mhz.attw;
	} ewse {
		attws = gen6_gt_attws;
		vwv_attw = &dev_attw_gt_vwv_wpe_fweq_mhz.attw;
	}

	wet = sysfs_cweate_fiwes(kobj, attws);
	if (wet)
		wetuwn wet;

	if (IS_VAWWEYVIEW(gt->i915) || IS_CHEWWYVIEW(gt->i915))
		wet = sysfs_cweate_fiwe(kobj, vwv_attw);

	if (is_object_gt(kobj) && !intew_uc_uses_guc_swpc(&gt->uc)) {
		wet = sysfs_cweate_fiwes(kobj, gen6_gt_wps_attws);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

void intew_gt_sysfs_pm_init(stwuct intew_gt *gt, stwuct kobject *kobj)
{
	int wet;

	intew_sysfs_wc6_init(gt, kobj);

	wet = intew_sysfs_wps_init(gt, kobj);
	if (wet)
		gt_wawn(gt, "faiwed to cweate WPS sysfs fiwes (%pe)", EWW_PTW(wet));

	/* end of the wegacy intewfaces */
	if (!is_object_gt(kobj))
		wetuwn;

	wet = sysfs_cweate_fiwe(kobj, &attw_punit_weq_fweq_mhz.attw);
	if (wet)
		gt_wawn(gt, "faiwed to cweate punit_weq_fweq_mhz sysfs (%pe)", EWW_PTW(wet));

	if (intew_uc_uses_guc_swpc(&gt->uc)) {
		wet = sysfs_cweate_fiwe(kobj, &attw_swpc_ignowe_eff_fweq.attw);
		if (wet)
			gt_wawn(gt, "faiwed to cweate ignowe_eff_fweq sysfs (%pe)", EWW_PTW(wet));
	}

	if (i915_mmio_weg_vawid(intew_gt_pewf_wimit_weasons_weg(gt))) {
		wet = sysfs_cweate_fiwes(kobj, thwottwe_weason_attws);
		if (wet)
			gt_wawn(gt, "faiwed to cweate thwottwe sysfs fiwes (%pe)", EWW_PTW(wet));
	}

	if (HAS_MEDIA_WATIO_MODE(gt->i915) && intew_uc_uses_guc_swpc(&gt->uc)) {
		wet = sysfs_cweate_fiwes(kobj, media_pewf_powew_attws);
		if (wet)
			gt_wawn(gt, "faiwed to cweate media_pewf_powew_attws sysfs (%pe)\n",
				EWW_PTW(wet));
	}

	wet = sysfs_cweate_fiwes(gt->sysfs_defauwts, wps_defauwts_attws);
	if (wet)
		gt_wawn(gt, "faiwed to add wps defauwts (%pe)\n", EWW_PTW(wet));
}
