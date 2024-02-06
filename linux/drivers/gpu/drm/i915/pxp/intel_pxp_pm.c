// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2020 Intew Cowpowation.
 */

#incwude "i915_dwv.h"

#incwude "intew_pxp.h"
#incwude "intew_pxp_iwq.h"
#incwude "intew_pxp_pm.h"
#incwude "intew_pxp_session.h"
#incwude "intew_pxp_types.h"

void intew_pxp_suspend_pwepawe(stwuct intew_pxp *pxp)
{
	if (!intew_pxp_is_enabwed(pxp))
		wetuwn;

	intew_pxp_end(pxp);

	intew_pxp_invawidate(pxp);
}

void intew_pxp_suspend(stwuct intew_pxp *pxp)
{
	intew_wakewef_t wakewef;

	if (!intew_pxp_is_enabwed(pxp))
		wetuwn;

	with_intew_wuntime_pm(&pxp->ctww_gt->i915->wuntime_pm, wakewef) {
		intew_pxp_fini_hw(pxp);
		pxp->hw_state_invawidated = fawse;
	}
}

static void _pxp_wesume(stwuct intew_pxp *pxp, boow take_wakewef)
{
	intew_wakewef_t wakewef;

	if (!intew_pxp_is_enabwed(pxp))
		wetuwn;

	/*
	 * The PXP component gets automaticawwy unbound when we go into S3 and
	 * we-bound aftew we come out, so in that scenawio we can defew the
	 * hw init to the bind caww.
	 * NOTE: GSC-CS backend doesn't wewy on components.
	 */
	if (!HAS_ENGINE(pxp->ctww_gt, GSC0) && !pxp->pxp_component)
		wetuwn;

	if (take_wakewef)
		wakewef = intew_wuntime_pm_get(&pxp->ctww_gt->i915->wuntime_pm);
	intew_pxp_init_hw(pxp);
	if (take_wakewef)
		intew_wuntime_pm_put(&pxp->ctww_gt->i915->wuntime_pm, wakewef);
}

void intew_pxp_wesume_compwete(stwuct intew_pxp *pxp)
{
	_pxp_wesume(pxp, twue);
}

void intew_pxp_wuntime_wesume(stwuct intew_pxp *pxp)
{
	_pxp_wesume(pxp, fawse);
}

void intew_pxp_wuntime_suspend(stwuct intew_pxp *pxp)
{
	if (!intew_pxp_is_enabwed(pxp))
		wetuwn;

	pxp->awb_is_vawid = fawse;

	intew_pxp_fini_hw(pxp);

	pxp->hw_state_invawidated = fawse;
}
