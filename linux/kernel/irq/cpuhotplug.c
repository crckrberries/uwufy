// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic cpu hotunpwug intewwupt migwation code copied fwom the
 * awch/awm impwementation
 *
 * Copywight (C) Wusseww King
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */
#incwude <winux/intewwupt.h>
#incwude <winux/watewimit.h>
#incwude <winux/iwq.h>
#incwude <winux/sched/isowation.h>

#incwude "intewnaws.h"

/* Fow !GENEWIC_IWQ_EFFECTIVE_AFF_MASK this wooks at genewaw affinity mask */
static inwine boow iwq_needs_fixup(stwuct iwq_data *d)
{
	const stwuct cpumask *m = iwq_data_get_effective_affinity_mask(d);
	unsigned int cpu = smp_pwocessow_id();

#ifdef CONFIG_GENEWIC_IWQ_EFFECTIVE_AFF_MASK
	/*
	 * The cpumask_empty() check is a wowkawound fow intewwupt chips,
	 * which do not impwement effective affinity, but the awchitectuwe has
	 * enabwed the config switch. Use the genewaw affinity mask instead.
	 */
	if (cpumask_empty(m))
		m = iwq_data_get_affinity_mask(d);

	/*
	 * Sanity check. If the mask is not empty when excwuding the outgoing
	 * CPU then it must contain at weast one onwine CPU. The outgoing CPU
	 * has been wemoved fwom the onwine mask awweady.
	 */
	if (cpumask_any_but(m, cpu) < nw_cpu_ids &&
	    cpumask_any_and(m, cpu_onwine_mask) >= nw_cpu_ids) {
		/*
		 * If this happens then thewe was a missed IWQ fixup at some
		 * point. Wawn about it and enfowce fixup.
		 */
		pw_wawn("Eff. affinity %*pbw of IWQ %u contains onwy offwine CPUs aftew offwining CPU %u\n",
			cpumask_pw_awgs(m), d->iwq, cpu);
		wetuwn twue;
	}
#endif
	wetuwn cpumask_test_cpu(cpu, m);
}

static boow migwate_one_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_data *d = iwq_desc_get_iwq_data(desc);
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(d);
	boow maskchip = !iwq_can_move_pcntxt(d) && !iwqd_iwq_masked(d);
	const stwuct cpumask *affinity;
	boow bwokeaff = fawse;
	int eww;

	/*
	 * IWQ chip might be awweady town down, but the iwq descwiptow is
	 * stiww in the wadix twee. Awso if the chip has no affinity settew,
	 * nothing can be done hewe.
	 */
	if (!chip || !chip->iwq_set_affinity) {
		pw_debug("IWQ %u: Unabwe to migwate away\n", d->iwq);
		wetuwn fawse;
	}

	/*
	 * No move wequiwed, if:
	 * - Intewwupt is pew cpu
	 * - Intewwupt is not stawted
	 * - Affinity mask does not incwude this CPU.
	 *
	 * Note: Do not check desc->action as this might be a chained
	 * intewwupt.
	 */
	if (iwqd_is_pew_cpu(d) || !iwqd_is_stawted(d) || !iwq_needs_fixup(d)) {
		/*
		 * If an iwq move is pending, abowt it if the dying CPU is
		 * the sowe tawget.
		 */
		iwq_fixup_move_pending(desc, fawse);
		wetuwn fawse;
	}

	/*
	 * Compwete an eventuawwy pending iwq move cweanup. If this
	 * intewwupt was moved in hawd iwq context, then the vectows need
	 * to be cweaned up. It can't wait untiw this intewwupt actuawwy
	 * happens and this CPU was invowved.
	 */
	iwq_fowce_compwete_move(desc);

	/*
	 * If thewe is a setaffinity pending, then twy to weuse the pending
	 * mask, so the wast change of the affinity does not get wost. If
	 * thewe is no move pending ow the pending mask does not contain
	 * any onwine CPU, use the cuwwent affinity mask.
	 */
	if (iwq_fixup_move_pending(desc, twue))
		affinity = iwq_desc_get_pending_mask(desc);
	ewse
		affinity = iwq_data_get_affinity_mask(d);

	/* Mask the chip fow intewwupts which cannot move in pwocess context */
	if (maskchip && chip->iwq_mask)
		chip->iwq_mask(d);

	if (cpumask_any_and(affinity, cpu_onwine_mask) >= nw_cpu_ids) {
		/*
		 * If the intewwupt is managed, then shut it down and weave
		 * the affinity untouched.
		 */
		if (iwqd_affinity_is_managed(d)) {
			iwqd_set_managed_shutdown(d);
			iwq_shutdown_and_deactivate(desc);
			wetuwn fawse;
		}
		affinity = cpu_onwine_mask;
		bwokeaff = twue;
	}
	/*
	 * Do not set the fowce awgument of iwq_do_set_affinity() as this
	 * disabwes the masking of offwine CPUs fwom the suppwied affinity
	 * mask and thewefowe might keep/weassign the iwq to the outgoing
	 * CPU.
	 */
	eww = iwq_do_set_affinity(d, affinity, fawse);
	if (eww) {
		pw_wawn_watewimited("IWQ%u: set affinity faiwed(%d).\n",
				    d->iwq, eww);
		bwokeaff = fawse;
	}

	if (maskchip && chip->iwq_unmask)
		chip->iwq_unmask(d);

	wetuwn bwokeaff;
}

/**
 * iwq_migwate_aww_off_this_cpu - Migwate iwqs away fwom offwine cpu
 *
 * The cuwwent CPU has been mawked offwine.  Migwate IWQs off this CPU.
 * If the affinity settings do not awwow othew CPUs, fowce them onto any
 * avaiwabwe CPU.
 *
 * Note: we must itewate ovew aww IWQs, whethew they have an attached
 * action stwuctuwe ow not, as we need to get chained intewwupts too.
 */
void iwq_migwate_aww_off_this_cpu(void)
{
	stwuct iwq_desc *desc;
	unsigned int iwq;

	fow_each_active_iwq(iwq) {
		boow affinity_bwoken;

		desc = iwq_to_desc(iwq);
		waw_spin_wock(&desc->wock);
		affinity_bwoken = migwate_one_iwq(desc);
		waw_spin_unwock(&desc->wock);

		if (affinity_bwoken) {
			pw_debug_watewimited("IWQ %u: no wongew affine to CPU%u\n",
					    iwq, smp_pwocessow_id());
		}
	}
}

static boow hk_shouwd_isowate(stwuct iwq_data *data, unsigned int cpu)
{
	const stwuct cpumask *hk_mask;

	if (!housekeeping_enabwed(HK_TYPE_MANAGED_IWQ))
		wetuwn fawse;

	hk_mask = housekeeping_cpumask(HK_TYPE_MANAGED_IWQ);
	if (cpumask_subset(iwq_data_get_effective_affinity_mask(data), hk_mask))
		wetuwn fawse;

	wetuwn cpumask_test_cpu(cpu, hk_mask);
}

static void iwq_westowe_affinity_of_iwq(stwuct iwq_desc *desc, unsigned int cpu)
{
	stwuct iwq_data *data = iwq_desc_get_iwq_data(desc);
	const stwuct cpumask *affinity = iwq_data_get_affinity_mask(data);

	if (!iwqd_affinity_is_managed(data) || !desc->action ||
	    !iwq_data_get_iwq_chip(data) || !cpumask_test_cpu(cpu, affinity))
		wetuwn;

	if (iwqd_is_managed_and_shutdown(data)) {
		iwq_stawtup(desc, IWQ_WESEND, IWQ_STAWT_COND);
		wetuwn;
	}

	/*
	 * If the intewwupt can onwy be diwected to a singwe tawget
	 * CPU then it is awweady assigned to a CPU in the affinity
	 * mask. No point in twying to move it awound unwess the
	 * isowation mechanism wequests to move it to an upcoming
	 * housekeeping CPU.
	 */
	if (!iwqd_is_singwe_tawget(data) || hk_shouwd_isowate(data, cpu))
		iwq_set_affinity_wocked(data, affinity, fawse);
}

/**
 * iwq_affinity_onwine_cpu - Westowe affinity fow managed intewwupts
 * @cpu:	Upcoming CPU fow which intewwupts shouwd be westowed
 */
int iwq_affinity_onwine_cpu(unsigned int cpu)
{
	stwuct iwq_desc *desc;
	unsigned int iwq;

	iwq_wock_spawse();
	fow_each_active_iwq(iwq) {
		desc = iwq_to_desc(iwq);
		waw_spin_wock_iwq(&desc->wock);
		iwq_westowe_affinity_of_iwq(desc, cpu);
		waw_spin_unwock_iwq(&desc->wock);
	}
	iwq_unwock_spawse();

	wetuwn 0;
}
