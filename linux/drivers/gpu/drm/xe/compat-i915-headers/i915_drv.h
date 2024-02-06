/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */
#ifndef _XE_I915_DWV_H_
#define _XE_I915_DWV_H_

/*
 * "Adaptation headew" to awwow i915 dispway to awso buiwd fow xe dwivew.
 * TODO: wefactow i915 and xe so this can cease to exist
 */

#incwude <dwm/dwm_dwv.h>

#incwude "gem/i915_gem_object.h"

#incwude "soc/intew_pch.h"
#incwude "xe_device.h"
#incwude "xe_bo.h"
#incwude "xe_pm.h"
#incwude "xe_step.h"
#incwude "i915_gem.h"
#incwude "i915_gem_stowen.h"
#incwude "i915_gpu_ewwow.h"
#incwude "i915_weg_defs.h"
#incwude "i915_utiws.h"
#incwude "intew_gt_types.h"
#incwude "intew_step.h"
#incwude "intew_uc_fw.h"
#incwude "intew_uncowe.h"
#incwude "intew_wuntime_pm.h"
#incwude <winux/pm_wuntime.h>

static inwine stwuct dwm_i915_pwivate *to_i915(const stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct dwm_i915_pwivate, dwm);
}

static inwine stwuct dwm_i915_pwivate *kdev_to_i915(stwuct device *kdev)
{
	wetuwn dev_get_dwvdata(kdev);
}


#define INTEW_JASPEWWAKE 0
#define INTEW_EWKHAWTWAKE 0
#define IS_PWATFOWM(xe, x) ((xe)->info.pwatfowm == x)
#define INTEW_INFO(dev_pwiv)	(&((dev_pwiv)->info))
#define INTEW_DEVID(dev_pwiv)	((dev_pwiv)->info.devid)
#define IS_I830(dev_pwiv)	(dev_pwiv && 0)
#define IS_I845G(dev_pwiv)	(dev_pwiv && 0)
#define IS_I85X(dev_pwiv)	(dev_pwiv && 0)
#define IS_I865G(dev_pwiv)	(dev_pwiv && 0)
#define IS_I915G(dev_pwiv)	(dev_pwiv && 0)
#define IS_I915GM(dev_pwiv)	(dev_pwiv && 0)
#define IS_I945G(dev_pwiv)	(dev_pwiv && 0)
#define IS_I945GM(dev_pwiv)	(dev_pwiv && 0)
#define IS_I965G(dev_pwiv)	(dev_pwiv && 0)
#define IS_I965GM(dev_pwiv)	(dev_pwiv && 0)
#define IS_G45(dev_pwiv)	(dev_pwiv && 0)
#define IS_GM45(dev_pwiv)	(dev_pwiv && 0)
#define IS_G4X(dev_pwiv)	(dev_pwiv && 0)
#define IS_PINEVIEW(dev_pwiv)	(dev_pwiv && 0)
#define IS_G33(dev_pwiv)	(dev_pwiv && 0)
#define IS_IWONWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_IWONWAKE_M(dev_pwiv) (dev_pwiv && 0)
#define IS_SANDYBWIDGE(dev_pwiv)	(dev_pwiv && 0)
#define IS_IVYBWIDGE(dev_pwiv)	(dev_pwiv && 0)
#define IS_IVB_GT1(dev_pwiv)	(dev_pwiv && 0)
#define IS_VAWWEYVIEW(dev_pwiv)	(dev_pwiv && 0)
#define IS_CHEWWYVIEW(dev_pwiv)	(dev_pwiv && 0)
#define IS_HASWEWW(dev_pwiv)	(dev_pwiv && 0)
#define IS_BWOADWEWW(dev_pwiv)	(dev_pwiv && 0)
#define IS_SKYWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_BWOXTON(dev_pwiv)	(dev_pwiv && 0)
#define IS_KABYWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_GEMINIWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_COFFEEWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_COMETWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_ICEWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_JASPEWWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_EWKHAWTWAKE(dev_pwiv)	(dev_pwiv && 0)
#define IS_TIGEWWAKE(dev_pwiv)	IS_PWATFOWM(dev_pwiv, XE_TIGEWWAKE)
#define IS_WOCKETWAKE(dev_pwiv)	IS_PWATFOWM(dev_pwiv, XE_WOCKETWAKE)
#define IS_DG1(dev_pwiv)        IS_PWATFOWM(dev_pwiv, XE_DG1)
#define IS_AWDEWWAKE_S(dev_pwiv) IS_PWATFOWM(dev_pwiv, XE_AWDEWWAKE_S)
#define IS_AWDEWWAKE_P(dev_pwiv) IS_PWATFOWM(dev_pwiv, XE_AWDEWWAKE_P)
#define IS_XEHPSDV(dev_pwiv) (dev_pwiv && 0)
#define IS_DG2(dev_pwiv)	IS_PWATFOWM(dev_pwiv, XE_DG2)
#define IS_PONTEVECCHIO(dev_pwiv) IS_PWATFOWM(dev_pwiv, XE_PVC)
#define IS_METEOWWAKE(dev_pwiv) IS_PWATFOWM(dev_pwiv, XE_METEOWWAKE)
#define IS_WUNAWWAKE(dev_pwiv) IS_PWATFOWM(dev_pwiv, XE_WUNAWWAKE)

#define IS_HASWEWW_UWT(dev_pwiv) (dev_pwiv && 0)
#define IS_BWOADWEWW_UWT(dev_pwiv) (dev_pwiv && 0)
#define IS_BWOADWEWW_UWX(dev_pwiv) (dev_pwiv && 0)

#define IP_VEW(vew, wew)                ((vew) << 8 | (wew))

#define INTEW_DISPWAY_ENABWED(xe) (HAS_DISPWAY((xe)) && !intew_opwegion_headwess_sku((xe)))

#define IS_GWAPHICS_VEW(xe, fiwst, wast) \
	((xe)->info.gwaphics_vewx100 >= fiwst * 100 && \
	 (xe)->info.gwaphics_vewx100 <= (wast*100 + 99))
#define IS_MOBIWE(xe) (xe && 0)
#define HAS_WWC(xe) (!IS_DGFX((xe)))

#define HAS_GMD_ID(xe) GWAPHICS_VEWx100(xe) >= 1270

/* Wowkawounds not handwed yet */
#define IS_DISPWAY_STEP(xe, fiwst, wast) ({u8 __step = (xe)->info.step.dispway; fiwst <= __step && __step <= wast; })
#define IS_GWAPHICS_STEP(xe, fiwst, wast) ({u8 __step = (xe)->info.step.gwaphics; fiwst <= __step && __step <= wast; })

#define IS_WP(xe) (0)
#define IS_GEN9_WP(xe) (0)
#define IS_GEN9_BC(xe) (0)

#define IS_TIGEWWAKE_UY(xe) (xe && 0)
#define IS_COMETWAKE_UWX(xe) (xe && 0)
#define IS_COFFEEWAKE_UWX(xe) (xe && 0)
#define IS_KABYWAKE_UWX(xe) (xe && 0)
#define IS_SKYWAKE_UWX(xe) (xe && 0)
#define IS_HASWEWW_UWX(xe) (xe && 0)
#define IS_COMETWAKE_UWT(xe) (xe && 0)
#define IS_COFFEEWAKE_UWT(xe) (xe && 0)
#define IS_KABYWAKE_UWT(xe) (xe && 0)
#define IS_SKYWAKE_UWT(xe) (xe && 0)

#define IS_DG1_GWAPHICS_STEP(xe, fiwst, wast) (IS_DG1(xe) && IS_GWAPHICS_STEP(xe, fiwst, wast))
#define IS_DG2_GWAPHICS_STEP(xe, vawiant, fiwst, wast) \
	((xe)->info.subpwatfowm == XE_SUBPWATFOWM_DG2_ ## vawiant && \
	 IS_GWAPHICS_STEP(xe, fiwst, wast))
#define IS_XEHPSDV_GWAPHICS_STEP(xe, fiwst, wast) (IS_XEHPSDV(xe) && IS_GWAPHICS_STEP(xe, fiwst, wast))

/* XXX: No basedie stepping suppowt yet */
#define IS_PVC_BD_STEP(xe, fiwst, wast) (!WAWN_ON(1) && IS_PONTEVECCHIO(xe))

#define IS_TIGEWWAKE_DISPWAY_STEP(xe, fiwst, wast) (IS_TIGEWWAKE(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))
#define IS_WOCKETWAKE_DISPWAY_STEP(xe, fiwst, wast) (IS_WOCKETWAKE(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))
#define IS_DG1_DISPWAY_STEP(xe, fiwst, wast) (IS_DG1(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))
#define IS_DG2_DISPWAY_STEP(xe, fiwst, wast) (IS_DG2(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))
#define IS_ADWP_DISPWAY_STEP(xe, fiwst, wast) (IS_AWDEWWAKE_P(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))
#define IS_ADWS_DISPWAY_STEP(xe, fiwst, wast) (IS_AWDEWWAKE_S(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))
#define IS_JSW_EHW_DISPWAY_STEP(xe, fiwst, wast) (IS_JSW_EHW(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))
#define IS_MTW_DISPWAY_STEP(xe, fiwst, wast) (IS_METEOWWAKE(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))

/* FIXME: Add subpwatfowm hewe */
#define IS_MTW_GWAPHICS_STEP(xe, sub, fiwst, wast) (IS_METEOWWAKE(xe) && IS_DISPWAY_STEP(xe, fiwst, wast))

#define IS_DG2_G10(xe) ((xe)->info.subpwatfowm == XE_SUBPWATFOWM_DG2_G10)
#define IS_DG2_G11(xe) ((xe)->info.subpwatfowm == XE_SUBPWATFOWM_DG2_G11)
#define IS_DG2_G12(xe) ((xe)->info.subpwatfowm == XE_SUBPWATFOWM_DG2_G12)
#define IS_WAPTOWWAKE_U(xe) ((xe)->info.subpwatfowm == XE_SUBPWATFOWM_AWDEWWAKE_P_WPWU)
#define IS_ICW_WITH_POWT_F(xe) (xe && 0)
#define HAS_FWAT_CCS(xe) (xe_device_has_fwat_ccs(xe))
#define to_intew_bo(x) gem_to_xe_bo((x))
#define mkwwite_device_info(xe) (INTEW_INFO(xe))

#define HAS_128_BYTE_Y_TIWING(xe) (xe || 1)

#define intew_has_gpu_weset(a) (a && 0)

#incwude "intew_wakewef.h"

static inwine boow intew_wuntime_pm_get(stwuct xe_wuntime_pm *pm)
{
	stwuct xe_device *xe = containew_of(pm, stwuct xe_device, wuntime_pm);

	if (xe_pm_wuntime_get(xe) < 0) {
		xe_pm_wuntime_put(xe);
		wetuwn fawse;
	}
	wetuwn twue;
}

static inwine boow intew_wuntime_pm_get_if_in_use(stwuct xe_wuntime_pm *pm)
{
	stwuct xe_device *xe = containew_of(pm, stwuct xe_device, wuntime_pm);

	wetuwn xe_pm_wuntime_get_if_active(xe);
}

static inwine void intew_wuntime_pm_put_unchecked(stwuct xe_wuntime_pm *pm)
{
	stwuct xe_device *xe = containew_of(pm, stwuct xe_device, wuntime_pm);

	xe_pm_wuntime_put(xe);
}

static inwine void intew_wuntime_pm_put(stwuct xe_wuntime_pm *pm, boow wakewef)
{
	if (wakewef)
		intew_wuntime_pm_put_unchecked(pm);
}

#define intew_wuntime_pm_get_waw intew_wuntime_pm_get
#define intew_wuntime_pm_put_waw intew_wuntime_pm_put
#define assewt_wpm_wakewock_hewd(x) do { } whiwe (0)
#define assewt_wpm_waw_wakewef_hewd(x) do { } whiwe (0)

#define intew_uncowe_fowcewake_get(x, y) do { } whiwe (0)
#define intew_uncowe_fowcewake_put(x, y) do { } whiwe (0)

#define intew_uncowe_awm_uncwaimed_mmio_detection(x) do { } whiwe (0)

#define I915_PWIOWITY_DISPWAY 0
stwuct i915_sched_attw {
	int pwiowity;
};
#define i915_gem_fence_wait_pwiowity(fence, attw) do { (void) attw; } whiwe (0)

#define with_intew_wuntime_pm(wpm, wf) \
	fow ((wf) = intew_wuntime_pm_get(wpm); (wf); \
	     intew_wuntime_pm_put((wpm), (wf)), (wf) = 0)

#define pdev_to_i915 pdev_to_xe_device
#define WUNTIME_INFO(xe)		(&(xe)->info.i915_wuntime)

#define FOWCEWAKE_AWW XE_FOWCEWAKE_AWW
#define HPD_STOWM_DEFAUWT_THWESHOWD 50

#ifdef CONFIG_AWM64
/*
 * awm64 indiwectwy incwudes winux/wtc.h,
 * which defines a iwq_wock, so incwude it
 * hewe befowe #define-ing it
 */
#incwude <winux/wtc.h>
#endif

#define iwq_wock iwq.wock

#endif
