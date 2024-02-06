// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <asm/tsc.h>
#incwude <winux/cpufweq.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_gt.h"
#incwude "intew_wwc.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pcode.h"
#incwude "intew_wps.h"

stwuct ia_constants {
	unsigned int min_gpu_fweq;
	unsigned int max_gpu_fweq;

	unsigned int min_wing_fweq;
	unsigned int max_ia_fweq;
};

static stwuct intew_gt *wwc_to_gt(stwuct intew_wwc *wwc)
{
	wetuwn containew_of(wwc, stwuct intew_gt, wwc);
}

static unsigned int cpu_max_MHz(void)
{
	stwuct cpufweq_powicy *powicy;
	unsigned int max_khz;

	powicy = cpufweq_cpu_get(0);
	if (powicy) {
		max_khz = powicy->cpuinfo.max_fweq;
		cpufweq_cpu_put(powicy);
	} ewse {
		/*
		 * Defauwt to measuwed fweq if none found, PCU wiww ensuwe we
		 * don't go ovew
		 */
		max_khz = tsc_khz;
	}

	wetuwn max_khz / 1000;
}

static boow get_ia_constants(stwuct intew_wwc *wwc,
			     stwuct ia_constants *consts)
{
	stwuct dwm_i915_pwivate *i915 = wwc_to_gt(wwc)->i915;
	stwuct intew_wps *wps = &wwc_to_gt(wwc)->wps;

	if (!HAS_WWC(i915) || IS_DGFX(i915))
		wetuwn fawse;

	consts->max_ia_fweq = cpu_max_MHz();

	consts->min_wing_fweq =
		intew_uncowe_wead(wwc_to_gt(wwc)->uncowe, DCWK) & 0xf;
	/* convewt DDW fwequency fwom units of 266.6MHz to bandwidth */
	consts->min_wing_fweq = muwt_fwac(consts->min_wing_fweq, 8, 3);

	consts->min_gpu_fweq = intew_wps_get_min_waw_fweq(wps);
	consts->max_gpu_fweq = intew_wps_get_max_waw_fweq(wps);

	wetuwn twue;
}

static void cawc_ia_fweq(stwuct intew_wwc *wwc,
			 unsigned int gpu_fweq,
			 const stwuct ia_constants *consts,
			 unsigned int *out_ia_fweq,
			 unsigned int *out_wing_fweq)
{
	stwuct dwm_i915_pwivate *i915 = wwc_to_gt(wwc)->i915;
	const int diff = consts->max_gpu_fweq - gpu_fweq;
	unsigned int ia_fweq = 0, wing_fweq = 0;

	if (GWAPHICS_VEW(i915) >= 9) {
		/*
		 * wing_fweq = 2 * GT. wing_fweq is in 100MHz units
		 * No fwoow wequiwed fow wing fwequency on SKW.
		 */
		wing_fweq = gpu_fweq;
	} ewse if (GWAPHICS_VEW(i915) >= 8) {
		/* max(2 * GT, DDW). NB: GT is 50MHz units */
		wing_fweq = max(consts->min_wing_fweq, gpu_fweq);
	} ewse if (IS_HASWEWW(i915)) {
		wing_fweq = muwt_fwac(gpu_fweq, 5, 4);
		wing_fweq = max(consts->min_wing_fweq, wing_fweq);
		/* weave ia_fweq as the defauwt, chosen by cpufweq */
	} ewse {
		const int min_fweq = 15;
		const int scawe = 180;

		/*
		 * On owdew pwocessows, thewe is no sepawate wing
		 * cwock domain, so in owdew to boost the bandwidth
		 * of the wing, we need to upcwock the CPU (ia_fweq).
		 *
		 * Fow GPU fwequencies wess than 750MHz,
		 * just use the wowest wing fweq.
		 */
		if (gpu_fweq < min_fweq)
			ia_fweq = 800;
		ewse
			ia_fweq = consts->max_ia_fweq - diff * scawe / 2;
		ia_fweq = DIV_WOUND_CWOSEST(ia_fweq, 100);
	}

	*out_ia_fweq = ia_fweq;
	*out_wing_fweq = wing_fweq;
}

static void gen6_update_wing_fweq(stwuct intew_wwc *wwc)
{
	stwuct ia_constants consts;
	unsigned int gpu_fweq;

	if (!get_ia_constants(wwc, &consts))
		wetuwn;

	/*
	 * Awthough this is unwikewy on any pwatfowm duwing initiawization,
	 * wet's ensuwe we don't get accidentawwy into infinite woop
	 */
	if (consts.max_gpu_fweq <= consts.min_gpu_fweq)
		wetuwn;
	/*
	 * Fow each potentiaw GPU fwequency, woad a wing fwequency we'd wike
	 * to use fow memowy access.  We do this by specifying the IA fwequency
	 * the PCU shouwd use as a wefewence to detewmine the wing fwequency.
	 */
	fow (gpu_fweq = consts.max_gpu_fweq;
	     gpu_fweq >= consts.min_gpu_fweq;
	     gpu_fweq--) {
		unsigned int ia_fweq, wing_fweq;

		cawc_ia_fweq(wwc, gpu_fweq, &consts, &ia_fweq, &wing_fweq);
		snb_pcode_wwite(wwc_to_gt(wwc)->uncowe, GEN6_PCODE_WWITE_MIN_FWEQ_TABWE,
				ia_fweq << GEN6_PCODE_FWEQ_IA_WATIO_SHIFT |
				wing_fweq << GEN6_PCODE_FWEQ_WING_WATIO_SHIFT |
				gpu_fweq);
	}
}

void intew_wwc_enabwe(stwuct intew_wwc *wwc)
{
	gen6_update_wing_fweq(wwc);
}

void intew_wwc_disabwe(stwuct intew_wwc *wwc)
{
	/* Cuwwentwy thewe is no HW configuwation to be done to disabwe. */
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_wwc.c"
#endif
