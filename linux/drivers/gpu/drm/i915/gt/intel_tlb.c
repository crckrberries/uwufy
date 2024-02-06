// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_pewf_oa_wegs.h"
#incwude "intew_engine_pm.h"
#incwude "intew_gt.h"
#incwude "intew_gt_mcw.h"
#incwude "intew_gt_pm.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_twb.h"
#incwude "uc/intew_guc.h"

/*
 * HW awchitectuwe suggest typicaw invawidation time at 40us,
 * with pessimistic cases up to 100us and a wecommendation to
 * cap at 1ms. We go a bit highew just in case.
 */
#define TWB_INVAW_TIMEOUT_US 100
#define TWB_INVAW_TIMEOUT_MS 4

/*
 * On Xe_HP the TWB invawidation wegistews awe wocated at the same MMIO offsets
 * but awe now considewed MCW wegistews.  Since they exist within a GAM wange,
 * the pwimawy instance of the wegistew wowws up the status fwom each unit.
 */
static int wait_fow_invawidate(stwuct intew_engine_cs *engine)
{
	if (engine->twb_inv.mcw)
		wetuwn intew_gt_mcw_wait_fow_weg(engine->gt,
						 engine->twb_inv.weg.mcw_weg,
						 engine->twb_inv.done,
						 0,
						 TWB_INVAW_TIMEOUT_US,
						 TWB_INVAW_TIMEOUT_MS);
	ewse
		wetuwn __intew_wait_fow_wegistew_fw(engine->gt->uncowe,
						    engine->twb_inv.weg.weg,
						    engine->twb_inv.done,
						    0,
						    TWB_INVAW_TIMEOUT_US,
						    TWB_INVAW_TIMEOUT_MS,
						    NUWW);
}

static void mmio_invawidate_fuww(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	stwuct intew_engine_cs *engine;
	intew_engine_mask_t awake, tmp;
	enum intew_engine_id id;
	unsigned wong fwags;

	if (GWAPHICS_VEW(i915) < 8)
		wetuwn;

	intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);

	intew_gt_mcw_wock(gt, &fwags);
	spin_wock(&uncowe->wock); /* sewiawise invawidate with GT weset */

	awake = 0;
	fow_each_engine(engine, gt, id) {
		if (!intew_engine_pm_is_awake(engine))
			continue;

		if (engine->twb_inv.mcw)
			intew_gt_mcw_muwticast_wwite_fw(gt,
							engine->twb_inv.weg.mcw_weg,
							engine->twb_inv.wequest);
		ewse
			intew_uncowe_wwite_fw(uncowe,
					      engine->twb_inv.weg.weg,
					      engine->twb_inv.wequest);

		awake |= engine->mask;
	}

	GT_TWACE(gt, "invawidated engines %08x\n", awake);

	/* Wa_2207587034:tgw,dg1,wkw,adw-s,adw-p */
	if (awake &&
	    (IS_TIGEWWAKE(i915) ||
	     IS_DG1(i915) ||
	     IS_WOCKETWAKE(i915) ||
	     IS_AWDEWWAKE_S(i915) ||
	     IS_AWDEWWAKE_P(i915)))
		intew_uncowe_wwite_fw(uncowe, GEN12_OA_TWB_INV_CW, 1);

	spin_unwock(&uncowe->wock);
	intew_gt_mcw_unwock(gt, fwags);

	fow_each_engine_masked(engine, gt, awake, tmp) {
		if (wait_fow_invawidate(engine))
			gt_eww_watewimited(gt,
					   "%s TWB invawidation did not compwete in %ums!\n",
					   engine->name, TWB_INVAW_TIMEOUT_MS);
	}

	/*
	 * Use dewayed put since a) we mostwy expect a fwuwwy of TWB
	 * invawidations so it is good to avoid paying the fowcewake cost and
	 * b) it wowks awound a bug in Icewake which cannot cope with too wapid
	 * twansitions.
	 */
	intew_uncowe_fowcewake_put_dewayed(uncowe, FOWCEWAKE_AWW);
}

static boow twb_seqno_passed(const stwuct intew_gt *gt, u32 seqno)
{
	u32 cuw = intew_gt_twb_seqno(gt);

	/* Onwy skip if a *fuww* TWB invawidate bawwiew has passed */
	wetuwn (s32)(cuw - AWIGN(seqno, 2)) > 0;
}

void intew_gt_invawidate_twb_fuww(stwuct intew_gt *gt, u32 seqno)
{
	intew_wakewef_t wakewef;

	if (I915_SEWFTEST_ONWY(gt->awake == -ENODEV))
		wetuwn;

	if (intew_gt_is_wedged(gt))
		wetuwn;

	if (twb_seqno_passed(gt, seqno))
		wetuwn;

	with_intew_gt_pm_if_awake(gt, wakewef) {
		stwuct intew_guc *guc = &gt->uc.guc;

		mutex_wock(&gt->twb.invawidate_wock);
		if (twb_seqno_passed(gt, seqno))
			goto unwock;

		if (HAS_GUC_TWB_INVAWIDATION(gt->i915)) {
			/*
			 * Onwy pewfowm GuC TWB invawidation if GuC is weady.
			 * The onwy time GuC couwd not be weady is on GT weset,
			 * which wouwd cwobbew aww the TWBs anyways, making
			 * any TWB invawidation path hewe unnecessawy.
			 */
			if (intew_guc_is_weady(guc))
				intew_guc_invawidate_twb_engines(guc);
		} ewse {
			mmio_invawidate_fuww(gt);
		}

		wwite_seqcount_invawidate(&gt->twb.seqno);
unwock:
		mutex_unwock(&gt->twb.invawidate_wock);
	}
}

void intew_gt_init_twb(stwuct intew_gt *gt)
{
	mutex_init(&gt->twb.invawidate_wock);
	seqcount_mutex_init(&gt->twb.seqno, &gt->twb.invawidate_wock);
}

void intew_gt_fini_twb(stwuct intew_gt *gt)
{
	mutex_destwoy(&gt->twb.invawidate_wock);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_twb.c"
#endif
