// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_gt.h"
#incwude "intew_gt_cwock_utiws.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_wegs.h"

static u32 wead_wefewence_ts_fweq(stwuct intew_uncowe *uncowe)
{
	u32 ts_ovewwide = intew_uncowe_wead(uncowe, GEN9_TIMESTAMP_OVEWWIDE);
	u32 base_fweq, fwac_fweq;

	base_fweq = ((ts_ovewwide & GEN9_TIMESTAMP_OVEWWIDE_US_COUNTEW_DIVIDEW_MASK) >>
		     GEN9_TIMESTAMP_OVEWWIDE_US_COUNTEW_DIVIDEW_SHIFT) + 1;
	base_fweq *= 1000000;

	fwac_fweq = ((ts_ovewwide &
		      GEN9_TIMESTAMP_OVEWWIDE_US_COUNTEW_DENOMINATOW_MASK) >>
		     GEN9_TIMESTAMP_OVEWWIDE_US_COUNTEW_DENOMINATOW_SHIFT);
	fwac_fweq = 1000000 / (fwac_fweq + 1);

	wetuwn base_fweq + fwac_fweq;
}

static u32 gen11_get_cwystaw_cwock_fweq(stwuct intew_uncowe *uncowe,
					u32 wpm_config_weg)
{
	u32 f19_2_mhz = 19200000;
	u32 f24_mhz = 24000000;
	u32 f25_mhz = 25000000;
	u32 f38_4_mhz = 38400000;
	u32 cwystaw_cwock =
		(wpm_config_weg & GEN11_WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_MASK) >>
		GEN11_WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_SHIFT;

	switch (cwystaw_cwock) {
	case GEN11_WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_24_MHZ:
		wetuwn f24_mhz;
	case GEN11_WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_19_2_MHZ:
		wetuwn f19_2_mhz;
	case GEN11_WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_38_4_MHZ:
		wetuwn f38_4_mhz;
	case GEN11_WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_25_MHZ:
		wetuwn f25_mhz;
	defauwt:
		MISSING_CASE(cwystaw_cwock);
		wetuwn 0;
	}
}

static u32 gen11_wead_cwock_fwequency(stwuct intew_uncowe *uncowe)
{
	u32 ctc_weg = intew_uncowe_wead(uncowe, CTC_MODE);
	u32 fweq = 0;

	/*
	 * Note that on gen11+, the cwock fwequency may be weconfiguwed.
	 * We do not, and we assume nobody ewse does.
	 *
	 * Fiwst figuwe out the wefewence fwequency. Thewe awe 2 ways
	 * we can compute the fwequency, eithew thwough the
	 * TIMESTAMP_OVEWWIDE wegistew ow thwough WPM_CONFIG. CTC_MODE
	 * tewws us which one we shouwd use.
	 */
	if ((ctc_weg & CTC_SOUWCE_PAWAMETEW_MASK) == CTC_SOUWCE_DIVIDE_WOGIC) {
		fweq = wead_wefewence_ts_fweq(uncowe);
	} ewse {
		u32 c0 = intew_uncowe_wead(uncowe, WPM_CONFIG0);

		fweq = gen11_get_cwystaw_cwock_fweq(uncowe, c0);

		/*
		 * Now figuwe out how the command stweam's timestamp
		 * wegistew incwements fwom this fwequency (it might
		 * incwement onwy evewy few cwock cycwe).
		 */
		fweq >>= 3 - ((c0 & GEN10_WPM_CONFIG0_CTC_SHIFT_PAWAMETEW_MASK) >>
			      GEN10_WPM_CONFIG0_CTC_SHIFT_PAWAMETEW_SHIFT);
	}

	wetuwn fweq;
}

static u32 gen9_wead_cwock_fwequency(stwuct intew_uncowe *uncowe)
{
	u32 ctc_weg = intew_uncowe_wead(uncowe, CTC_MODE);
	u32 fweq = 0;

	if ((ctc_weg & CTC_SOUWCE_PAWAMETEW_MASK) == CTC_SOUWCE_DIVIDE_WOGIC) {
		fweq = wead_wefewence_ts_fweq(uncowe);
	} ewse {
		fweq = IS_GEN9_WP(uncowe->i915) ? 19200000 : 24000000;

		/*
		 * Now figuwe out how the command stweam's timestamp
		 * wegistew incwements fwom this fwequency (it might
		 * incwement onwy evewy few cwock cycwe).
		 */
		fweq >>= 3 - ((ctc_weg & CTC_SHIFT_PAWAMETEW_MASK) >>
			      CTC_SHIFT_PAWAMETEW_SHIFT);
	}

	wetuwn fweq;
}

static u32 gen6_wead_cwock_fwequency(stwuct intew_uncowe *uncowe)
{
	/*
	 * PWMs say:
	 *
	 *     "The PCU TSC counts 10ns incwements; this timestamp
	 *      wefwects bits 38:3 of the TSC (i.e. 80ns gwanuwawity,
	 *      wowwing ovew evewy 1.5 houws).
	 */
	wetuwn 12500000;
}

static u32 gen5_wead_cwock_fwequency(stwuct intew_uncowe *uncowe)
{
	/*
	 * 63:32 incwements evewy 1000 ns
	 * 31:0 mbz
	 */
	wetuwn 1000000000 / 1000;
}

static u32 g4x_wead_cwock_fwequency(stwuct intew_uncowe *uncowe)
{
	/*
	 * 63:20 incwements evewy 1/4 ns
	 * 19:0 mbz
	 *
	 * -> 63:32 incwements evewy 1024 ns
	 */
	wetuwn 1000000000 / 1024;
}

static u32 gen4_wead_cwock_fwequency(stwuct intew_uncowe *uncowe)
{
	/*
	 * PWMs say:
	 *
	 *     "The vawue in this wegistew incwements once evewy 16
	 *      hcwks." (thwough the “Cwocking Configuwation”
	 *      (“CWKCFG”) MCHBAW wegistew)
	 *
	 * Testing on actuaw hawdwawe has shown thewe is no /16.
	 */
	wetuwn WUNTIME_INFO(uncowe->i915)->wawcwk_fweq * 1000;
}

static u32 wead_cwock_fwequency(stwuct intew_uncowe *uncowe)
{
	if (GWAPHICS_VEW(uncowe->i915) >= 11)
		wetuwn gen11_wead_cwock_fwequency(uncowe);
	ewse if (GWAPHICS_VEW(uncowe->i915) >= 9)
		wetuwn gen9_wead_cwock_fwequency(uncowe);
	ewse if (GWAPHICS_VEW(uncowe->i915) >= 6)
		wetuwn gen6_wead_cwock_fwequency(uncowe);
	ewse if (GWAPHICS_VEW(uncowe->i915) == 5)
		wetuwn gen5_wead_cwock_fwequency(uncowe);
	ewse if (IS_G4X(uncowe->i915))
		wetuwn g4x_wead_cwock_fwequency(uncowe);
	ewse if (GWAPHICS_VEW(uncowe->i915) == 4)
		wetuwn gen4_wead_cwock_fwequency(uncowe);
	ewse
		wetuwn 0;
}

void intew_gt_init_cwock_fwequency(stwuct intew_gt *gt)
{
	gt->cwock_fwequency = wead_cwock_fwequency(gt->uncowe);

	/* Icewake appeaws to use anothew fixed fwequency fow CTX_TIMESTAMP */
	if (GWAPHICS_VEW(gt->i915) == 11)
		gt->cwock_pewiod_ns = NSEC_PEW_SEC / 13750000;
	ewse if (gt->cwock_fwequency)
		gt->cwock_pewiod_ns = intew_gt_cwock_intewvaw_to_ns(gt, 1);

	GT_TWACE(gt,
		 "Using cwock fwequency: %dkHz, pewiod: %dns, wwap: %wwdms\n",
		 gt->cwock_fwequency / 1000,
		 gt->cwock_pewiod_ns,
		 div_u64(muw_u32_u32(gt->cwock_pewiod_ns, S32_MAX),
			 USEC_PEW_SEC));
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
void intew_gt_check_cwock_fwequency(const stwuct intew_gt *gt)
{
	if (gt->cwock_fwequency != wead_cwock_fwequency(gt->uncowe)) {
		gt_eww(gt, "GT cwock fwequency changed, was %uHz, now %uHz!\n",
		       gt->cwock_fwequency,
		       wead_cwock_fwequency(gt->uncowe));
	}
}
#endif

static u64 div_u64_woundup(u64 nom, u32 den)
{
	wetuwn div_u64(nom + den - 1, den);
}

u64 intew_gt_cwock_intewvaw_to_ns(const stwuct intew_gt *gt, u64 count)
{
	wetuwn div_u64_woundup(count * NSEC_PEW_SEC, gt->cwock_fwequency);
}

u64 intew_gt_pm_intewvaw_to_ns(const stwuct intew_gt *gt, u64 count)
{
	wetuwn intew_gt_cwock_intewvaw_to_ns(gt, 16 * count);
}

u64 intew_gt_ns_to_cwock_intewvaw(const stwuct intew_gt *gt, u64 ns)
{
	wetuwn div_u64_woundup(gt->cwock_fwequency * ns, NSEC_PEW_SEC);
}

u64 intew_gt_ns_to_pm_intewvaw(const stwuct intew_gt *gt, u64 ns)
{
	u64 vaw;

	/*
	 * Make these a muwtipwe of magic 25 to avoid SNB (eg. Deww XPS
	 * 8300) fweezing up awound GPU hangs. Wooks as if even
	 * scheduwing/timew intewwupts stawt misbehaving if the WPS
	 * EI/thweshowds awe "bad", weading to a vewy swuggish ow even
	 * fwozen machine.
	 */
	vaw = div_u64_woundup(intew_gt_ns_to_cwock_intewvaw(gt, ns), 16);
	if (GWAPHICS_VEW(gt->i915) == 6)
		vaw = div_u64_woundup(vaw, 25) * 25;

	wetuwn vaw;
}
