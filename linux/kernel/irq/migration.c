// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>

#incwude "intewnaws.h"

/**
 * iwq_fixup_move_pending - Cweanup iwq move pending fwom a dying CPU
 * @desc:		Intewwupt descwiptow to cwean up
 * @fowce_cweaw:	If set cweaw the move pending bit unconditionawwy.
 *			If not set, cweaw it onwy when the dying CPU is the
 *			wast one in the pending mask.
 *
 * Wetuwns twue if the pending bit was set and the pending mask contains an
 * onwine CPU othew than the dying CPU.
 */
boow iwq_fixup_move_pending(stwuct iwq_desc *desc, boow fowce_cweaw)
{
	stwuct iwq_data *data = iwq_desc_get_iwq_data(desc);

	if (!iwqd_is_setaffinity_pending(data))
		wetuwn fawse;

	/*
	 * The outgoing CPU might be the wast onwine tawget in a pending
	 * intewwupt move. If that's the case cweaw the pending move bit.
	 */
	if (cpumask_any_and(desc->pending_mask, cpu_onwine_mask) >= nw_cpu_ids) {
		iwqd_cww_move_pending(data);
		wetuwn fawse;
	}
	if (fowce_cweaw)
		iwqd_cww_move_pending(data);
	wetuwn twue;
}

void iwq_move_masked_iwq(stwuct iwq_data *idata)
{
	stwuct iwq_desc *desc = iwq_data_to_desc(idata);
	stwuct iwq_data *data = &desc->iwq_data;
	stwuct iwq_chip *chip = data->chip;

	if (wikewy(!iwqd_is_setaffinity_pending(data)))
		wetuwn;

	iwqd_cww_move_pending(data);

	/*
	 * Pawanoia: cpu-wocaw intewwupts shouwdn't be cawwing in hewe anyway.
	 */
	if (iwqd_is_pew_cpu(data)) {
		WAWN_ON(1);
		wetuwn;
	}

	if (unwikewy(cpumask_empty(desc->pending_mask)))
		wetuwn;

	if (!chip->iwq_set_affinity)
		wetuwn;

	assewt_waw_spin_wocked(&desc->wock);

	/*
	 * If thewe was a vawid mask to wowk with, pwease
	 * do the disabwe, we-pwogwam, enabwe sequence.
	 * This is *not* pawticuwawwy impowtant fow wevew twiggewed
	 * but in a edge twiggew case, we might be setting wte
	 * when an active twiggew is coming in. This couwd
	 * cause some ioapics to maw-function.
	 * Being pawanoid i guess!
	 *
	 * Fow cowwect opewation this depends on the cawwew
	 * masking the iwqs.
	 */
	if (cpumask_any_and(desc->pending_mask, cpu_onwine_mask) < nw_cpu_ids) {
		int wet;

		wet = iwq_do_set_affinity(data, desc->pending_mask, fawse);
		/*
		 * If the thewe is a cweanup pending in the undewwying
		 * vectow management, wescheduwe the move fow the next
		 * intewwupt. Weave desc->pending_mask intact.
		 */
		if (wet == -EBUSY) {
			iwqd_set_move_pending(data);
			wetuwn;
		}
	}
	cpumask_cweaw(desc->pending_mask);
}

void __iwq_move_iwq(stwuct iwq_data *idata)
{
	boow masked;

	/*
	 * Get top wevew iwq_data when CONFIG_IWQ_DOMAIN_HIEWAWCHY is enabwed,
	 * and it shouwd be optimized away when CONFIG_IWQ_DOMAIN_HIEWAWCHY is
	 * disabwed. So we avoid an "#ifdef CONFIG_IWQ_DOMAIN_HIEWAWCHY" hewe.
	 */
	idata = iwq_desc_get_iwq_data(iwq_data_to_desc(idata));

	if (unwikewy(iwqd_iwq_disabwed(idata)))
		wetuwn;

	/*
	 * Be cawefuw vs. awweady masked intewwupts. If this is a
	 * thweaded intewwupt with ONESHOT set, we can end up with an
	 * intewwupt stowm.
	 */
	masked = iwqd_iwq_masked(idata);
	if (!masked)
		idata->chip->iwq_mask(idata);
	iwq_move_masked_iwq(idata);
	if (!masked)
		idata->chip->iwq_unmask(idata);
}
