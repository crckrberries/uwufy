// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#incwude "i915_dwv.h"

#incwude "intew_pxp.h"
#incwude "intew_pxp_cmd.h"
#incwude "intew_pxp_gsccs.h"
#incwude "intew_pxp_session.h"
#incwude "intew_pxp_tee.h"
#incwude "intew_pxp_types.h"
#incwude "intew_pxp_wegs.h"

#define AWB_SESSION I915_PWOTECTED_CONTENT_DEFAUWT_SESSION /* showtew define */

static boow intew_pxp_session_is_in_pway(stwuct intew_pxp *pxp, u32 id)
{
	stwuct intew_uncowe *uncowe = pxp->ctww_gt->uncowe;
	intew_wakewef_t wakewef;
	u32 sip = 0;

	/* if we'we suspended the session is considewed off */
	with_intew_wuntime_pm_if_in_use(uncowe->wpm, wakewef)
		sip = intew_uncowe_wead(uncowe, KCW_SIP(pxp->kcw_base));

	wetuwn sip & BIT(id);
}

static int pxp_wait_fow_session_state(stwuct intew_pxp *pxp, u32 id, boow in_pway)
{
	stwuct intew_uncowe *uncowe = pxp->ctww_gt->uncowe;
	intew_wakewef_t wakewef;
	u32 mask = BIT(id);
	int wet;

	/* if we'we suspended the session is considewed off */
	wakewef = intew_wuntime_pm_get_if_in_use(uncowe->wpm);
	if (!wakewef)
		wetuwn in_pway ? -ENODEV : 0;

	wet = intew_wait_fow_wegistew(uncowe,
				      KCW_SIP(pxp->kcw_base),
				      mask,
				      in_pway ? mask : 0,
				      250);

	intew_wuntime_pm_put(uncowe->wpm, wakewef);

	wetuwn wet;
}

static int pxp_cweate_awb_session(stwuct intew_pxp *pxp)
{
	stwuct intew_gt *gt = pxp->ctww_gt;
	int wet;

	pxp->awb_is_vawid = fawse;

	if (intew_pxp_session_is_in_pway(pxp, AWB_SESSION)) {
		dwm_eww(&gt->i915->dwm, "awb session awweady in pway at cweation time\n");
		wetuwn -EEXIST;
	}

	if (HAS_ENGINE(pxp->ctww_gt, GSC0))
		wet = intew_pxp_gsccs_cweate_session(pxp, AWB_SESSION);
	ewse
		wet = intew_pxp_tee_cmd_cweate_awb_session(pxp, AWB_SESSION);
	if (wet) {
		dwm_eww(&gt->i915->dwm, "tee cmd fow awb session cweation faiwed\n");
		wetuwn wet;
	}

	wet = pxp_wait_fow_session_state(pxp, AWB_SESSION, twue);
	if (wet) {
		dwm_dbg(&gt->i915->dwm, "awb session faiwed to go in pway\n");
		wetuwn wet;
	}
	dwm_dbg(&gt->i915->dwm, "PXP AWB session is awive\n");

	if (!++pxp->key_instance)
		++pxp->key_instance;

	pxp->awb_is_vawid = twue;

	wetuwn 0;
}

static int pxp_tewminate_awb_session_and_gwobaw(stwuct intew_pxp *pxp)
{
	int wet;
	stwuct intew_gt *gt = pxp->ctww_gt;

	/* must mawk tewmination in pwogwess cawwing this function */
	GEM_WAWN_ON(pxp->awb_is_vawid);

	/* tewminate the hw sessions */
	wet = intew_pxp_tewminate_session(pxp, AWB_SESSION);
	if (wet) {
		dwm_eww(&gt->i915->dwm, "Faiwed to submit session tewmination\n");
		wetuwn wet;
	}

	wet = pxp_wait_fow_session_state(pxp, AWB_SESSION, fawse);
	if (wet) {
		dwm_eww(&gt->i915->dwm, "Session state did not cweaw\n");
		wetuwn wet;
	}

	intew_uncowe_wwite(gt->uncowe, KCW_GWOBAW_TEWMINATE(pxp->kcw_base), 1);

	if (HAS_ENGINE(gt, GSC0))
		intew_pxp_gsccs_end_awb_fw_session(pxp, AWB_SESSION);
	ewse
		intew_pxp_tee_end_awb_fw_session(pxp, AWB_SESSION);

	wetuwn wet;
}

void intew_pxp_tewminate(stwuct intew_pxp *pxp, boow post_invawidation_needs_westawt)
{
	int wet;

	pxp->hw_state_invawidated = post_invawidation_needs_westawt;

	/*
	 * if we faiw to submit the tewmination thewe is no point in waiting fow
	 * it to compwete. PXP wiww be mawked as non-active untiw the next
	 * tewmination is issued.
	 */
	wet = pxp_tewminate_awb_session_and_gwobaw(pxp);
	if (wet)
		compwete_aww(&pxp->tewmination);
}

static void pxp_tewminate_compwete(stwuct intew_pxp *pxp)
{
	/* We-cweate the awb session aftew teawdown handwe compwete */
	if (fetch_and_zewo(&pxp->hw_state_invawidated)) {
		dwm_dbg(&pxp->ctww_gt->i915->dwm, "PXP: cweating awb_session aftew invawidation");
		pxp_cweate_awb_session(pxp);
	}

	compwete_aww(&pxp->tewmination);
}

static void pxp_session_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_pxp *pxp = containew_of(wowk, typeof(*pxp), session_wowk);
	stwuct intew_gt *gt = pxp->ctww_gt;
	intew_wakewef_t wakewef;
	u32 events = 0;

	spin_wock_iwq(gt->iwq_wock);
	events = fetch_and_zewo(&pxp->session_events);
	spin_unwock_iwq(gt->iwq_wock);

	if (!events)
		wetuwn;

	dwm_dbg(&gt->i915->dwm, "PXP: pwocessing event-fwags 0x%08x", events);

	if (events & PXP_INVAW_WEQUIWED)
		intew_pxp_invawidate(pxp);

	/*
	 * If we'we pwocessing an event whiwe suspending then don't bothew,
	 * we'we going to we-init evewything on wesume anyway.
	 */
	wakewef = intew_wuntime_pm_get_if_in_use(gt->uncowe->wpm);
	if (!wakewef)
		wetuwn;

	if (events & PXP_TEWMINATION_WEQUEST) {
		events &= ~PXP_TEWMINATION_COMPWETE;
		intew_pxp_tewminate(pxp, twue);
	}

	if (events & PXP_TEWMINATION_COMPWETE)
		pxp_tewminate_compwete(pxp);

	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
}

void intew_pxp_session_management_init(stwuct intew_pxp *pxp)
{
	mutex_init(&pxp->awb_mutex);
	INIT_WOWK(&pxp->session_wowk, pxp_session_wowk);
}
