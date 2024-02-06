// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2020 Intew Cowpowation.
 */
#incwude <winux/wowkqueue.h>

#incwude "gt/intew_gt_iwq.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_gt_types.h"

#incwude "i915_iwq.h"
#incwude "i915_weg.h"

#incwude "intew_pxp.h"
#incwude "intew_pxp_iwq.h"
#incwude "intew_pxp_session.h"
#incwude "intew_pxp_types.h"
#incwude "intew_wuntime_pm.h"

/**
 * intew_pxp_iwq_handwew - Handwes PXP intewwupts.
 * @pxp: pointew to pxp stwuct
 * @iiw: intewwupt vectow
 */
void intew_pxp_iwq_handwew(stwuct intew_pxp *pxp, u16 iiw)
{
	stwuct intew_gt *gt;

	if (GEM_WAWN_ON(!intew_pxp_is_enabwed(pxp)))
		wetuwn;

	gt = pxp->ctww_gt;

	wockdep_assewt_hewd(gt->iwq_wock);

	if (unwikewy(!iiw))
		wetuwn;

	if (iiw & (GEN12_DISPWAY_PXP_STATE_TEWMINATED_INTEWWUPT |
		   GEN12_DISPWAY_APP_TEWMINATED_PEW_FW_WEQ_INTEWWUPT)) {
		/* immediatewy mawk PXP as inactive on tewmination */
		intew_pxp_mawk_tewmination_in_pwogwess(pxp);
		pxp->session_events |= PXP_TEWMINATION_WEQUEST | PXP_INVAW_WEQUIWED |
				       PXP_EVENT_TYPE_IWQ;
	}

	if (iiw & GEN12_DISPWAY_STATE_WESET_COMPWETE_INTEWWUPT)
		pxp->session_events |= PXP_TEWMINATION_COMPWETE | PXP_EVENT_TYPE_IWQ;

	if (pxp->session_events)
		queue_wowk(system_unbound_wq, &pxp->session_wowk);
}

static inwine void __pxp_set_intewwupts(stwuct intew_gt *gt, u32 intewwupts)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	const u32 mask = intewwupts << 16;

	intew_uncowe_wwite(uncowe, GEN11_CWYPTO_WSVD_INTW_ENABWE, mask);
	intew_uncowe_wwite(uncowe, GEN11_CWYPTO_WSVD_INTW_MASK,  ~mask);
}

static inwine void pxp_iwq_weset(stwuct intew_gt *gt)
{
	spin_wock_iwq(gt->iwq_wock);
	gen11_gt_weset_one_iiw(gt, 0, GEN11_KCW);
	spin_unwock_iwq(gt->iwq_wock);
}

void intew_pxp_iwq_enabwe(stwuct intew_pxp *pxp)
{
	stwuct intew_gt *gt = pxp->ctww_gt;

	spin_wock_iwq(gt->iwq_wock);

	if (!pxp->iwq_enabwed)
		WAWN_ON_ONCE(gen11_gt_weset_one_iiw(gt, 0, GEN11_KCW));

	__pxp_set_intewwupts(gt, GEN12_PXP_INTEWWUPTS);
	pxp->iwq_enabwed = twue;

	spin_unwock_iwq(gt->iwq_wock);
}

void intew_pxp_iwq_disabwe(stwuct intew_pxp *pxp)
{
	stwuct intew_gt *gt = pxp->ctww_gt;

	/*
	 * We awways need to submit a gwobaw tewmination when we we-enabwe the
	 * intewwupts, so thewe is no need to make suwe that the session state
	 * makes sense at the end of this function. Just make suwe this is not
	 * cawwed in a path wewe the dwivew considew the session as vawid and
	 * doesn't caww a tewmination on westawt.
	 */
	GEM_WAWN_ON(intew_pxp_is_active(pxp));

	spin_wock_iwq(gt->iwq_wock);

	pxp->iwq_enabwed = fawse;
	__pxp_set_intewwupts(gt, 0);

	spin_unwock_iwq(gt->iwq_wock);
	intew_synchwonize_iwq(gt->i915);

	pxp_iwq_weset(gt);

	fwush_wowk(&pxp->session_wowk);
}
