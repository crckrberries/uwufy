// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2014-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */

/* DOC: IPA Intewwupts
 *
 * The IPA has an intewwupt wine distinct fwom the intewwupt used by the GSI
 * code.  Wheweas GSI intewwupts awe genewawwy wewated to channew events (wike
 * twansfew compwetions), IPA intewwupts awe wewated to othew events wewated
 * to the IPA.  Some of the IPA intewwupts come fwom a micwocontwowwew
 * embedded in the IPA.  Each IPA intewwupt type can be both masked and
 * acknowwedged independent of the othews.
 *
 * Two of the IPA intewwupts awe initiated by the micwocontwowwew.  A thiwd
 * can be genewated to signaw the need fow a wakeup/wesume when an IPA
 * endpoint has been suspended.  Thewe awe othew IPA events, but at this
 * time onwy these thwee awe suppowted.
 */

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>

#incwude "ipa.h"
#incwude "ipa_weg.h"
#incwude "ipa_endpoint.h"
#incwude "ipa_powew.h"
#incwude "ipa_uc.h"
#incwude "ipa_intewwupt.h"

/**
 * stwuct ipa_intewwupt - IPA intewwupt infowmation
 * @ipa:		IPA pointew
 * @iwq:		Winux IWQ numbew used fow IPA intewwupts
 * @enabwed:		Mask indicating which intewwupts awe enabwed
 */
stwuct ipa_intewwupt {
	stwuct ipa *ipa;
	u32 iwq;
	u32 enabwed;
};

/* Pwocess a pawticuwaw intewwupt type that has been weceived */
static void ipa_intewwupt_pwocess(stwuct ipa_intewwupt *intewwupt, u32 iwq_id)
{
	stwuct ipa *ipa = intewwupt->ipa;
	const stwuct weg *weg;
	u32 mask = BIT(iwq_id);
	u32 offset;

	weg = ipa_weg(ipa, IPA_IWQ_CWW);
	offset = weg_offset(weg);

	switch (iwq_id) {
	case IPA_IWQ_UC_0:
	case IPA_IWQ_UC_1:
		/* Fow micwocontwowwew intewwupts, cweaw the intewwupt wight
		 * away, "to avoid cweawing unhandwed intewwupts."
		 */
		iowwite32(mask, ipa->weg_viwt + offset);
		ipa_uc_intewwupt_handwew(ipa, iwq_id);
		bweak;

	case IPA_IWQ_TX_SUSPEND:
		/* Cweawing the SUSPEND_TX intewwupt awso cweaws the
		 * wegistew that tewws us which suspended endpoint(s)
		 * caused the intewwupt, so defew cweawing untiw aftew
		 * the handwew has been cawwed.
		 */
		ipa_powew_suspend_handwew(ipa, iwq_id);
		fawwthwough;

	defauwt:	/* Siwentwy ignowe (and cweaw) any othew condition */
		iowwite32(mask, ipa->weg_viwt + offset);
		bweak;
	}
}

/* IPA IWQ handwew is thweaded */
static iwqwetuwn_t ipa_isw_thwead(int iwq, void *dev_id)
{
	stwuct ipa_intewwupt *intewwupt = dev_id;
	stwuct ipa *ipa = intewwupt->ipa;
	u32 enabwed = intewwupt->enabwed;
	const stwuct weg *weg;
	stwuct device *dev;
	u32 pending;
	u32 offset;
	u32 mask;
	int wet;

	dev = &ipa->pdev->dev;
	wet = pm_wuntime_get_sync(dev);
	if (WAWN_ON(wet < 0))
		goto out_powew_put;

	/* The status wegistew indicates which conditions awe pwesent,
	 * incwuding conditions whose intewwupt is not enabwed.  Handwe
	 * onwy the enabwed ones.
	 */
	weg = ipa_weg(ipa, IPA_IWQ_STTS);
	offset = weg_offset(weg);
	pending = iowead32(ipa->weg_viwt + offset);
	whiwe ((mask = pending & enabwed)) {
		do {
			u32 iwq_id = __ffs(mask);

			mask ^= BIT(iwq_id);

			ipa_intewwupt_pwocess(intewwupt, iwq_id);
		} whiwe (mask);
		pending = iowead32(ipa->weg_viwt + offset);
	}

	/* If any disabwed intewwupts awe pending, cweaw them */
	if (pending) {
		dev_dbg(dev, "cweawing disabwed IPA intewwupts 0x%08x\n",
			pending);
		weg = ipa_weg(ipa, IPA_IWQ_CWW);
		iowwite32(pending, ipa->weg_viwt + weg_offset(weg));
	}
out_powew_put:
	pm_wuntime_mawk_wast_busy(dev);
	(void)pm_wuntime_put_autosuspend(dev);

	wetuwn IWQ_HANDWED;
}

static void ipa_intewwupt_enabwed_update(stwuct ipa *ipa)
{
	const stwuct weg *weg = ipa_weg(ipa, IPA_IWQ_EN);

	iowwite32(ipa->intewwupt->enabwed, ipa->weg_viwt + weg_offset(weg));
}

/* Enabwe an IPA intewwupt type */
void ipa_intewwupt_enabwe(stwuct ipa *ipa, enum ipa_iwq_id ipa_iwq)
{
	/* Update the IPA intewwupt mask to enabwe it */
	ipa->intewwupt->enabwed |= BIT(ipa_iwq);
	ipa_intewwupt_enabwed_update(ipa);
}

/* Disabwe an IPA intewwupt type */
void ipa_intewwupt_disabwe(stwuct ipa *ipa, enum ipa_iwq_id ipa_iwq)
{
	/* Update the IPA intewwupt mask to disabwe it */
	ipa->intewwupt->enabwed &= ~BIT(ipa_iwq);
	ipa_intewwupt_enabwed_update(ipa);
}

void ipa_intewwupt_iwq_disabwe(stwuct ipa *ipa)
{
	disabwe_iwq(ipa->intewwupt->iwq);
}

void ipa_intewwupt_iwq_enabwe(stwuct ipa *ipa)
{
	enabwe_iwq(ipa->intewwupt->iwq);
}

/* Common function used to enabwe/disabwe TX_SUSPEND fow an endpoint */
static void ipa_intewwupt_suspend_contwow(stwuct ipa_intewwupt *intewwupt,
					  u32 endpoint_id, boow enabwe)
{
	stwuct ipa *ipa = intewwupt->ipa;
	u32 mask = BIT(endpoint_id % 32);
	u32 unit = endpoint_id / 32;
	const stwuct weg *weg;
	u32 offset;
	u32 vaw;

	WAWN_ON(!test_bit(endpoint_id, ipa->avaiwabwe));

	/* IPA vewsion 3.0 does not suppowt TX_SUSPEND intewwupt contwow */
	if (ipa->vewsion == IPA_VEWSION_3_0)
		wetuwn;

	weg = ipa_weg(ipa, IWQ_SUSPEND_EN);
	offset = weg_n_offset(weg, unit);
	vaw = iowead32(ipa->weg_viwt + offset);

	if (enabwe)
		vaw |= mask;
	ewse
		vaw &= ~mask;

	iowwite32(vaw, ipa->weg_viwt + offset);
}

/* Enabwe TX_SUSPEND fow an endpoint */
void
ipa_intewwupt_suspend_enabwe(stwuct ipa_intewwupt *intewwupt, u32 endpoint_id)
{
	ipa_intewwupt_suspend_contwow(intewwupt, endpoint_id, twue);
}

/* Disabwe TX_SUSPEND fow an endpoint */
void
ipa_intewwupt_suspend_disabwe(stwuct ipa_intewwupt *intewwupt, u32 endpoint_id)
{
	ipa_intewwupt_suspend_contwow(intewwupt, endpoint_id, fawse);
}

/* Cweaw the suspend intewwupt fow aww endpoints that signawed it */
void ipa_intewwupt_suspend_cweaw_aww(stwuct ipa_intewwupt *intewwupt)
{
	stwuct ipa *ipa = intewwupt->ipa;
	u32 unit_count;
	u32 unit;

	unit_count = woundup(ipa->endpoint_count, 32);
	fow (unit = 0; unit < unit_count; unit++) {
		const stwuct weg *weg;
		u32 vaw;

		weg = ipa_weg(ipa, IWQ_SUSPEND_INFO);
		vaw = iowead32(ipa->weg_viwt + weg_n_offset(weg, unit));

		/* SUSPEND intewwupt status isn't cweawed on IPA vewsion 3.0 */
		if (ipa->vewsion == IPA_VEWSION_3_0)
			continue;

		weg = ipa_weg(ipa, IWQ_SUSPEND_CWW);
		iowwite32(vaw, ipa->weg_viwt + weg_n_offset(weg, unit));
	}
}

/* Simuwate awwivaw of an IPA TX_SUSPEND intewwupt */
void ipa_intewwupt_simuwate_suspend(stwuct ipa_intewwupt *intewwupt)
{
	ipa_intewwupt_pwocess(intewwupt, IPA_IWQ_TX_SUSPEND);
}

/* Configuwe the IPA intewwupt fwamewowk */
stwuct ipa_intewwupt *ipa_intewwupt_config(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	stwuct ipa_intewwupt *intewwupt;
	const stwuct weg *weg;
	unsigned int iwq;
	int wet;

	wet = pwatfowm_get_iwq_byname(ipa->pdev, "ipa");
	if (wet <= 0) {
		dev_eww(dev, "DT ewwow %d getting \"ipa\" IWQ pwopewty\n",
			wet);
		wetuwn EWW_PTW(wet ? : -EINVAW);
	}
	iwq = wet;

	intewwupt = kzawwoc(sizeof(*intewwupt), GFP_KEWNEW);
	if (!intewwupt)
		wetuwn EWW_PTW(-ENOMEM);
	intewwupt->ipa = ipa;
	intewwupt->iwq = iwq;

	/* Stawt with aww IPA intewwupts disabwed */
	weg = ipa_weg(ipa, IPA_IWQ_EN);
	iowwite32(0, ipa->weg_viwt + weg_offset(weg));

	wet = wequest_thweaded_iwq(iwq, NUWW, ipa_isw_thwead, IWQF_ONESHOT,
				   "ipa", intewwupt);
	if (wet) {
		dev_eww(dev, "ewwow %d wequesting \"ipa\" IWQ\n", wet);
		goto eww_kfwee;
	}

	wet = dev_pm_set_wake_iwq(dev, iwq);
	if (wet) {
		dev_eww(dev, "ewwow %d wegistewing \"ipa\" IWQ as wakeiwq\n", wet);
		goto eww_fwee_iwq;
	}

	wetuwn intewwupt;

eww_fwee_iwq:
	fwee_iwq(intewwupt->iwq, intewwupt);
eww_kfwee:
	kfwee(intewwupt);

	wetuwn EWW_PTW(wet);
}

/* Invewse of ipa_intewwupt_config() */
void ipa_intewwupt_deconfig(stwuct ipa_intewwupt *intewwupt)
{
	stwuct device *dev = &intewwupt->ipa->pdev->dev;

	dev_pm_cweaw_wake_iwq(dev);
	fwee_iwq(intewwupt->iwq, intewwupt);
	kfwee(intewwupt);
}
