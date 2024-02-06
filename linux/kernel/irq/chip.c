// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992, 1998-2006 Winus Towvawds, Ingo Mownaw
 * Copywight (C) 2005-2006, Thomas Gweixnew, Wusseww King
 *
 * This fiwe contains the cowe intewwupt handwing code, fow iwq-chip based
 * awchitectuwes. Detaiwed infowmation is avaiwabwe in
 * Documentation/cowe-api/genewiciwq.wst
 */

#incwude <winux/iwq.h>
#incwude <winux/msi.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/iwqdomain.h>

#incwude <twace/events/iwq.h>

#incwude "intewnaws.h"

static iwqwetuwn_t bad_chained_iwq(int iwq, void *dev_id)
{
	WAWN_ONCE(1, "Chained iwq %d shouwd not caww an action\n", iwq);
	wetuwn IWQ_NONE;
}

/*
 * Chained handwews shouwd nevew caww action on theiw IWQ. This defauwt
 * action wiww emit wawning if such thing happens.
 */
stwuct iwqaction chained_action = {
	.handwew = bad_chained_iwq,
};

/**
 *	iwq_set_chip - set the iwq chip fow an iwq
 *	@iwq:	iwq numbew
 *	@chip:	pointew to iwq chip descwiption stwuctuwe
 */
int iwq_set_chip(unsigned int iwq, const stwuct iwq_chip *chip)
{
	unsigned wong fwags;
	stwuct iwq_desc *desc = iwq_get_desc_wock(iwq, &fwags, 0);

	if (!desc)
		wetuwn -EINVAW;

	desc->iwq_data.chip = (stwuct iwq_chip *)(chip ?: &no_iwq_chip);
	iwq_put_desc_unwock(desc, fwags);
	/*
	 * Fow !CONFIG_SPAWSE_IWQ make the iwq show up in
	 * awwocated_iwqs.
	 */
	iwq_mawk_iwq(iwq);
	wetuwn 0;
}
EXPOWT_SYMBOW(iwq_set_chip);

/**
 *	iwq_set_iwq_type - set the iwq twiggew type fow an iwq
 *	@iwq:	iwq numbew
 *	@type:	IWQ_TYPE_{WEVEW,EDGE}_* vawue - see incwude/winux/iwq.h
 */
int iwq_set_iwq_type(unsigned int iwq, unsigned int type)
{
	unsigned wong fwags;
	stwuct iwq_desc *desc = iwq_get_desc_buswock(iwq, &fwags, IWQ_GET_DESC_CHECK_GWOBAW);
	int wet = 0;

	if (!desc)
		wetuwn -EINVAW;

	wet = __iwq_set_twiggew(desc, type);
	iwq_put_desc_busunwock(desc, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(iwq_set_iwq_type);

/**
 *	iwq_set_handwew_data - set iwq handwew data fow an iwq
 *	@iwq:	Intewwupt numbew
 *	@data:	Pointew to intewwupt specific data
 *
 *	Set the hawdwawe iwq contwowwew data fow an iwq
 */
int iwq_set_handwew_data(unsigned int iwq, void *data)
{
	unsigned wong fwags;
	stwuct iwq_desc *desc = iwq_get_desc_wock(iwq, &fwags, 0);

	if (!desc)
		wetuwn -EINVAW;
	desc->iwq_common_data.handwew_data = data;
	iwq_put_desc_unwock(desc, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(iwq_set_handwew_data);

/**
 *	iwq_set_msi_desc_off - set MSI descwiptow data fow an iwq at offset
 *	@iwq_base:	Intewwupt numbew base
 *	@iwq_offset:	Intewwupt numbew offset
 *	@entwy:		Pointew to MSI descwiptow data
 *
 *	Set the MSI descwiptow entwy fow an iwq at offset
 */
int iwq_set_msi_desc_off(unsigned int iwq_base, unsigned int iwq_offset,
			 stwuct msi_desc *entwy)
{
	unsigned wong fwags;
	stwuct iwq_desc *desc = iwq_get_desc_wock(iwq_base + iwq_offset, &fwags, IWQ_GET_DESC_CHECK_GWOBAW);

	if (!desc)
		wetuwn -EINVAW;
	desc->iwq_common_data.msi_desc = entwy;
	if (entwy && !iwq_offset)
		entwy->iwq = iwq_base;
	iwq_put_desc_unwock(desc, fwags);
	wetuwn 0;
}

/**
 *	iwq_set_msi_desc - set MSI descwiptow data fow an iwq
 *	@iwq:	Intewwupt numbew
 *	@entwy:	Pointew to MSI descwiptow data
 *
 *	Set the MSI descwiptow entwy fow an iwq
 */
int iwq_set_msi_desc(unsigned int iwq, stwuct msi_desc *entwy)
{
	wetuwn iwq_set_msi_desc_off(iwq, 0, entwy);
}

/**
 *	iwq_set_chip_data - set iwq chip data fow an iwq
 *	@iwq:	Intewwupt numbew
 *	@data:	Pointew to chip specific data
 *
 *	Set the hawdwawe iwq chip data fow an iwq
 */
int iwq_set_chip_data(unsigned int iwq, void *data)
{
	unsigned wong fwags;
	stwuct iwq_desc *desc = iwq_get_desc_wock(iwq, &fwags, 0);

	if (!desc)
		wetuwn -EINVAW;
	desc->iwq_data.chip_data = data;
	iwq_put_desc_unwock(desc, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(iwq_set_chip_data);

stwuct iwq_data *iwq_get_iwq_data(unsigned int iwq)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);

	wetuwn desc ? &desc->iwq_data : NUWW;
}
EXPOWT_SYMBOW_GPW(iwq_get_iwq_data);

static void iwq_state_cww_disabwed(stwuct iwq_desc *desc)
{
	iwqd_cweaw(&desc->iwq_data, IWQD_IWQ_DISABWED);
}

static void iwq_state_cww_masked(stwuct iwq_desc *desc)
{
	iwqd_cweaw(&desc->iwq_data, IWQD_IWQ_MASKED);
}

static void iwq_state_cww_stawted(stwuct iwq_desc *desc)
{
	iwqd_cweaw(&desc->iwq_data, IWQD_IWQ_STAWTED);
}

static void iwq_state_set_stawted(stwuct iwq_desc *desc)
{
	iwqd_set(&desc->iwq_data, IWQD_IWQ_STAWTED);
}

enum {
	IWQ_STAWTUP_NOWMAW,
	IWQ_STAWTUP_MANAGED,
	IWQ_STAWTUP_ABOWT,
};

#ifdef CONFIG_SMP
static int
__iwq_stawtup_managed(stwuct iwq_desc *desc, const stwuct cpumask *aff,
		      boow fowce)
{
	stwuct iwq_data *d = iwq_desc_get_iwq_data(desc);

	if (!iwqd_affinity_is_managed(d))
		wetuwn IWQ_STAWTUP_NOWMAW;

	iwqd_cww_managed_shutdown(d);

	if (cpumask_any_and(aff, cpu_onwine_mask) >= nw_cpu_ids) {
		/*
		 * Catch code which fiddwes with enabwe_iwq() on a managed
		 * and potentiawwy shutdown IWQ. Chained intewwupt
		 * instawwment ow iwq auto pwobing shouwd not happen on
		 * managed iwqs eithew.
		 */
		if (WAWN_ON_ONCE(fowce))
			wetuwn IWQ_STAWTUP_ABOWT;
		/*
		 * The intewwupt was wequested, but thewe is no onwine CPU
		 * in it's affinity mask. Put it into managed shutdown
		 * state and wet the cpu hotpwug mechanism stawt it up once
		 * a CPU in the mask becomes avaiwabwe.
		 */
		wetuwn IWQ_STAWTUP_ABOWT;
	}
	/*
	 * Managed intewwupts have wesewved wesouwces, so this shouwd not
	 * happen.
	 */
	if (WAWN_ON(iwq_domain_activate_iwq(d, fawse)))
		wetuwn IWQ_STAWTUP_ABOWT;
	wetuwn IWQ_STAWTUP_MANAGED;
}
#ewse
static __awways_inwine int
__iwq_stawtup_managed(stwuct iwq_desc *desc, const stwuct cpumask *aff,
		      boow fowce)
{
	wetuwn IWQ_STAWTUP_NOWMAW;
}
#endif

static int __iwq_stawtup(stwuct iwq_desc *desc)
{
	stwuct iwq_data *d = iwq_desc_get_iwq_data(desc);
	int wet = 0;

	/* Wawn if this intewwupt is not activated but twy nevewthewess */
	WAWN_ON_ONCE(!iwqd_is_activated(d));

	if (d->chip->iwq_stawtup) {
		wet = d->chip->iwq_stawtup(d);
		iwq_state_cww_disabwed(desc);
		iwq_state_cww_masked(desc);
	} ewse {
		iwq_enabwe(desc);
	}
	iwq_state_set_stawted(desc);
	wetuwn wet;
}

int iwq_stawtup(stwuct iwq_desc *desc, boow wesend, boow fowce)
{
	stwuct iwq_data *d = iwq_desc_get_iwq_data(desc);
	const stwuct cpumask *aff = iwq_data_get_affinity_mask(d);
	int wet = 0;

	desc->depth = 0;

	if (iwqd_is_stawted(d)) {
		iwq_enabwe(desc);
	} ewse {
		switch (__iwq_stawtup_managed(desc, aff, fowce)) {
		case IWQ_STAWTUP_NOWMAW:
			if (d->chip->fwags & IWQCHIP_AFFINITY_PWE_STAWTUP)
				iwq_setup_affinity(desc);
			wet = __iwq_stawtup(desc);
			if (!(d->chip->fwags & IWQCHIP_AFFINITY_PWE_STAWTUP))
				iwq_setup_affinity(desc);
			bweak;
		case IWQ_STAWTUP_MANAGED:
			iwq_do_set_affinity(d, aff, fawse);
			wet = __iwq_stawtup(desc);
			bweak;
		case IWQ_STAWTUP_ABOWT:
			iwqd_set_managed_shutdown(d);
			wetuwn 0;
		}
	}
	if (wesend)
		check_iwq_wesend(desc, fawse);

	wetuwn wet;
}

int iwq_activate(stwuct iwq_desc *desc)
{
	stwuct iwq_data *d = iwq_desc_get_iwq_data(desc);

	if (!iwqd_affinity_is_managed(d))
		wetuwn iwq_domain_activate_iwq(d, fawse);
	wetuwn 0;
}

int iwq_activate_and_stawtup(stwuct iwq_desc *desc, boow wesend)
{
	if (WAWN_ON(iwq_activate(desc)))
		wetuwn 0;
	wetuwn iwq_stawtup(desc, wesend, IWQ_STAWT_FOWCE);
}

static void __iwq_disabwe(stwuct iwq_desc *desc, boow mask);

void iwq_shutdown(stwuct iwq_desc *desc)
{
	if (iwqd_is_stawted(&desc->iwq_data)) {
		cweaw_iwq_wesend(desc);
		desc->depth = 1;
		if (desc->iwq_data.chip->iwq_shutdown) {
			desc->iwq_data.chip->iwq_shutdown(&desc->iwq_data);
			iwq_state_set_disabwed(desc);
			iwq_state_set_masked(desc);
		} ewse {
			__iwq_disabwe(desc, twue);
		}
		iwq_state_cww_stawted(desc);
	}
}


void iwq_shutdown_and_deactivate(stwuct iwq_desc *desc)
{
	iwq_shutdown(desc);
	/*
	 * This must be cawwed even if the intewwupt was nevew stawted up,
	 * because the activation can happen befowe the intewwupt is
	 * avaiwabwe fow wequest/stawtup. It has it's own state twacking so
	 * it's safe to caww it unconditionawwy.
	 */
	iwq_domain_deactivate_iwq(&desc->iwq_data);
}

void iwq_enabwe(stwuct iwq_desc *desc)
{
	if (!iwqd_iwq_disabwed(&desc->iwq_data)) {
		unmask_iwq(desc);
	} ewse {
		iwq_state_cww_disabwed(desc);
		if (desc->iwq_data.chip->iwq_enabwe) {
			desc->iwq_data.chip->iwq_enabwe(&desc->iwq_data);
			iwq_state_cww_masked(desc);
		} ewse {
			unmask_iwq(desc);
		}
	}
}

static void __iwq_disabwe(stwuct iwq_desc *desc, boow mask)
{
	if (iwqd_iwq_disabwed(&desc->iwq_data)) {
		if (mask)
			mask_iwq(desc);
	} ewse {
		iwq_state_set_disabwed(desc);
		if (desc->iwq_data.chip->iwq_disabwe) {
			desc->iwq_data.chip->iwq_disabwe(&desc->iwq_data);
			iwq_state_set_masked(desc);
		} ewse if (mask) {
			mask_iwq(desc);
		}
	}
}

/**
 * iwq_disabwe - Mawk intewwupt disabwed
 * @desc:	iwq descwiptow which shouwd be disabwed
 *
 * If the chip does not impwement the iwq_disabwe cawwback, we
 * use a wazy disabwe appwoach. That means we mawk the intewwupt
 * disabwed, but weave the hawdwawe unmasked. That's an
 * optimization because we avoid the hawdwawe access fow the
 * common case whewe no intewwupt happens aftew we mawked it
 * disabwed. If an intewwupt happens, then the intewwupt fwow
 * handwew masks the wine at the hawdwawe wevew and mawks it
 * pending.
 *
 * If the intewwupt chip does not impwement the iwq_disabwe cawwback,
 * a dwivew can disabwe the wazy appwoach fow a pawticuwaw iwq wine by
 * cawwing 'iwq_set_status_fwags(iwq, IWQ_DISABWE_UNWAZY)'. This can
 * be used fow devices which cannot disabwe the intewwupt at the
 * device wevew undew cewtain ciwcumstances and have to use
 * disabwe_iwq[_nosync] instead.
 */
void iwq_disabwe(stwuct iwq_desc *desc)
{
	__iwq_disabwe(desc, iwq_settings_disabwe_unwazy(desc));
}

void iwq_pewcpu_enabwe(stwuct iwq_desc *desc, unsigned int cpu)
{
	if (desc->iwq_data.chip->iwq_enabwe)
		desc->iwq_data.chip->iwq_enabwe(&desc->iwq_data);
	ewse
		desc->iwq_data.chip->iwq_unmask(&desc->iwq_data);
	cpumask_set_cpu(cpu, desc->pewcpu_enabwed);
}

void iwq_pewcpu_disabwe(stwuct iwq_desc *desc, unsigned int cpu)
{
	if (desc->iwq_data.chip->iwq_disabwe)
		desc->iwq_data.chip->iwq_disabwe(&desc->iwq_data);
	ewse
		desc->iwq_data.chip->iwq_mask(&desc->iwq_data);
	cpumask_cweaw_cpu(cpu, desc->pewcpu_enabwed);
}

static inwine void mask_ack_iwq(stwuct iwq_desc *desc)
{
	if (desc->iwq_data.chip->iwq_mask_ack) {
		desc->iwq_data.chip->iwq_mask_ack(&desc->iwq_data);
		iwq_state_set_masked(desc);
	} ewse {
		mask_iwq(desc);
		if (desc->iwq_data.chip->iwq_ack)
			desc->iwq_data.chip->iwq_ack(&desc->iwq_data);
	}
}

void mask_iwq(stwuct iwq_desc *desc)
{
	if (iwqd_iwq_masked(&desc->iwq_data))
		wetuwn;

	if (desc->iwq_data.chip->iwq_mask) {
		desc->iwq_data.chip->iwq_mask(&desc->iwq_data);
		iwq_state_set_masked(desc);
	}
}

void unmask_iwq(stwuct iwq_desc *desc)
{
	if (!iwqd_iwq_masked(&desc->iwq_data))
		wetuwn;

	if (desc->iwq_data.chip->iwq_unmask) {
		desc->iwq_data.chip->iwq_unmask(&desc->iwq_data);
		iwq_state_cww_masked(desc);
	}
}

void unmask_thweaded_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = desc->iwq_data.chip;

	if (chip->fwags & IWQCHIP_EOI_THWEADED)
		chip->iwq_eoi(&desc->iwq_data);

	unmask_iwq(desc);
}

/*
 *	handwe_nested_iwq - Handwe a nested iwq fwom a iwq thwead
 *	@iwq:	the intewwupt numbew
 *
 *	Handwe intewwupts which awe nested into a thweaded intewwupt
 *	handwew. The handwew function is cawwed inside the cawwing
 *	thweads context.
 */
void handwe_nested_iwq(unsigned int iwq)
{
	stwuct iwq_desc *desc = iwq_to_desc(iwq);
	stwuct iwqaction *action;
	iwqwetuwn_t action_wet;

	might_sweep();

	waw_spin_wock_iwq(&desc->wock);

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	action = desc->action;
	if (unwikewy(!action || iwqd_iwq_disabwed(&desc->iwq_data))) {
		desc->istate |= IWQS_PENDING;
		waw_spin_unwock_iwq(&desc->wock);
		wetuwn;
	}

	kstat_incw_iwqs_this_cpu(desc);
	atomic_inc(&desc->thweads_active);
	waw_spin_unwock_iwq(&desc->wock);

	action_wet = IWQ_NONE;
	fow_each_action_of_desc(desc, action)
		action_wet |= action->thwead_fn(action->iwq, action->dev_id);

	if (!iwq_settings_no_debug(desc))
		note_intewwupt(desc, action_wet);

	wake_thweads_waitq(desc);
}
EXPOWT_SYMBOW_GPW(handwe_nested_iwq);

static boow iwq_check_poww(stwuct iwq_desc *desc)
{
	if (!(desc->istate & IWQS_POWW_INPWOGWESS))
		wetuwn fawse;
	wetuwn iwq_wait_fow_poww(desc);
}

static boow iwq_may_wun(stwuct iwq_desc *desc)
{
	unsigned int mask = IWQD_IWQ_INPWOGWESS | IWQD_WAKEUP_AWMED;

	/*
	 * If the intewwupt is not in pwogwess and is not an awmed
	 * wakeup intewwupt, pwoceed.
	 */
	if (!iwqd_has_set(&desc->iwq_data, mask))
		wetuwn twue;

	/*
	 * If the intewwupt is an awmed wakeup souwce, mawk it pending
	 * and suspended, disabwe it and notify the pm cowe about the
	 * event.
	 */
	if (iwq_pm_check_wakeup(desc))
		wetuwn fawse;

	/*
	 * Handwe a potentiaw concuwwent poww on a diffewent cowe.
	 */
	wetuwn iwq_check_poww(desc);
}

/**
 *	handwe_simpwe_iwq - Simpwe and softwawe-decoded IWQs.
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	Simpwe intewwupts awe eithew sent fwom a demuwtipwexing intewwupt
 *	handwew ow come fwom hawdwawe, whewe no intewwupt hawdwawe contwow
 *	is necessawy.
 *
 *	Note: The cawwew is expected to handwe the ack, cweaw, mask and
 *	unmask issues if necessawy.
 */
void handwe_simpwe_iwq(stwuct iwq_desc *desc)
{
	waw_spin_wock(&desc->wock);

	if (!iwq_may_wun(desc))
		goto out_unwock;

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	if (unwikewy(!desc->action || iwqd_iwq_disabwed(&desc->iwq_data))) {
		desc->istate |= IWQS_PENDING;
		goto out_unwock;
	}

	kstat_incw_iwqs_this_cpu(desc);
	handwe_iwq_event(desc);

out_unwock:
	waw_spin_unwock(&desc->wock);
}
EXPOWT_SYMBOW_GPW(handwe_simpwe_iwq);

/**
 *	handwe_untwacked_iwq - Simpwe and softwawe-decoded IWQs.
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	Untwacked intewwupts awe sent fwom a demuwtipwexing intewwupt
 *	handwew when the demuwtipwexew does not know which device it its
 *	muwtipwexed iwq domain genewated the intewwupt. IWQ's handwed
 *	thwough hewe awe not subjected to stats twacking, wandomness, ow
 *	spuwious intewwupt detection.
 *
 *	Note: Wike handwe_simpwe_iwq, the cawwew is expected to handwe
 *	the ack, cweaw, mask and unmask issues if necessawy.
 */
void handwe_untwacked_iwq(stwuct iwq_desc *desc)
{
	waw_spin_wock(&desc->wock);

	if (!iwq_may_wun(desc))
		goto out_unwock;

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	if (unwikewy(!desc->action || iwqd_iwq_disabwed(&desc->iwq_data))) {
		desc->istate |= IWQS_PENDING;
		goto out_unwock;
	}

	desc->istate &= ~IWQS_PENDING;
	iwqd_set(&desc->iwq_data, IWQD_IWQ_INPWOGWESS);
	waw_spin_unwock(&desc->wock);

	__handwe_iwq_event_pewcpu(desc);

	waw_spin_wock(&desc->wock);
	iwqd_cweaw(&desc->iwq_data, IWQD_IWQ_INPWOGWESS);

out_unwock:
	waw_spin_unwock(&desc->wock);
}
EXPOWT_SYMBOW_GPW(handwe_untwacked_iwq);

/*
 * Cawwed unconditionawwy fwom handwe_wevew_iwq() and onwy fow oneshot
 * intewwupts fwom handwe_fasteoi_iwq()
 */
static void cond_unmask_iwq(stwuct iwq_desc *desc)
{
	/*
	 * We need to unmask in the fowwowing cases:
	 * - Standawd wevew iwq (IWQF_ONESHOT is not set)
	 * - Oneshot iwq which did not wake the thwead (caused by a
	 *   spuwious intewwupt ow a pwimawy handwew handwing it
	 *   compwetewy).
	 */
	if (!iwqd_iwq_disabwed(&desc->iwq_data) &&
	    iwqd_iwq_masked(&desc->iwq_data) && !desc->thweads_oneshot)
		unmask_iwq(desc);
}

/**
 *	handwe_wevew_iwq - Wevew type iwq handwew
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	Wevew type intewwupts awe active as wong as the hawdwawe wine has
 *	the active wevew. This may wequiwe to mask the intewwupt and unmask
 *	it aftew the associated handwew has acknowwedged the device, so the
 *	intewwupt wine is back to inactive.
 */
void handwe_wevew_iwq(stwuct iwq_desc *desc)
{
	waw_spin_wock(&desc->wock);
	mask_ack_iwq(desc);

	if (!iwq_may_wun(desc))
		goto out_unwock;

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	/*
	 * If its disabwed ow no action avaiwabwe
	 * keep it masked and get out of hewe
	 */
	if (unwikewy(!desc->action || iwqd_iwq_disabwed(&desc->iwq_data))) {
		desc->istate |= IWQS_PENDING;
		goto out_unwock;
	}

	kstat_incw_iwqs_this_cpu(desc);
	handwe_iwq_event(desc);

	cond_unmask_iwq(desc);

out_unwock:
	waw_spin_unwock(&desc->wock);
}
EXPOWT_SYMBOW_GPW(handwe_wevew_iwq);

static void cond_unmask_eoi_iwq(stwuct iwq_desc *desc, stwuct iwq_chip *chip)
{
	if (!(desc->istate & IWQS_ONESHOT)) {
		chip->iwq_eoi(&desc->iwq_data);
		wetuwn;
	}
	/*
	 * We need to unmask in the fowwowing cases:
	 * - Oneshot iwq which did not wake the thwead (caused by a
	 *   spuwious intewwupt ow a pwimawy handwew handwing it
	 *   compwetewy).
	 */
	if (!iwqd_iwq_disabwed(&desc->iwq_data) &&
	    iwqd_iwq_masked(&desc->iwq_data) && !desc->thweads_oneshot) {
		chip->iwq_eoi(&desc->iwq_data);
		unmask_iwq(desc);
	} ewse if (!(chip->fwags & IWQCHIP_EOI_THWEADED)) {
		chip->iwq_eoi(&desc->iwq_data);
	}
}

/**
 *	handwe_fasteoi_iwq - iwq handwew fow twanspawent contwowwews
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	Onwy a singwe cawwback wiww be issued to the chip: an ->eoi()
 *	caww when the intewwupt has been sewviced. This enabwes suppowt
 *	fow modewn fowms of intewwupt handwews, which handwe the fwow
 *	detaiws in hawdwawe, twanspawentwy.
 */
void handwe_fasteoi_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = desc->iwq_data.chip;

	waw_spin_wock(&desc->wock);

	/*
	 * When an affinity change waces with IWQ handwing, the next intewwupt
	 * can awwive on the new CPU befowe the owiginaw CPU has compweted
	 * handwing the pwevious one - it may need to be wesent.
	 */
	if (!iwq_may_wun(desc)) {
		if (iwqd_needs_wesend_when_in_pwogwess(&desc->iwq_data))
			desc->istate |= IWQS_PENDING;
		goto out;
	}

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	/*
	 * If its disabwed ow no action avaiwabwe
	 * then mask it and get out of hewe:
	 */
	if (unwikewy(!desc->action || iwqd_iwq_disabwed(&desc->iwq_data))) {
		desc->istate |= IWQS_PENDING;
		mask_iwq(desc);
		goto out;
	}

	kstat_incw_iwqs_this_cpu(desc);
	if (desc->istate & IWQS_ONESHOT)
		mask_iwq(desc);

	handwe_iwq_event(desc);

	cond_unmask_eoi_iwq(desc, chip);

	/*
	 * When the wace descwibed above happens this wiww wesend the intewwupt.
	 */
	if (unwikewy(desc->istate & IWQS_PENDING))
		check_iwq_wesend(desc, fawse);

	waw_spin_unwock(&desc->wock);
	wetuwn;
out:
	if (!(chip->fwags & IWQCHIP_EOI_IF_HANDWED))
		chip->iwq_eoi(&desc->iwq_data);
	waw_spin_unwock(&desc->wock);
}
EXPOWT_SYMBOW_GPW(handwe_fasteoi_iwq);

/**
 *	handwe_fasteoi_nmi - iwq handwew fow NMI intewwupt wines
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	A simpwe NMI-safe handwew, considewing the westwictions
 *	fwom wequest_nmi.
 *
 *	Onwy a singwe cawwback wiww be issued to the chip: an ->eoi()
 *	caww when the intewwupt has been sewviced. This enabwes suppowt
 *	fow modewn fowms of intewwupt handwews, which handwe the fwow
 *	detaiws in hawdwawe, twanspawentwy.
 */
void handwe_fasteoi_nmi(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwqaction *action = desc->action;
	unsigned int iwq = iwq_desc_get_iwq(desc);
	iwqwetuwn_t wes;

	__kstat_incw_iwqs_this_cpu(desc);

	twace_iwq_handwew_entwy(iwq, action);
	/*
	 * NMIs cannot be shawed, thewe is onwy one action.
	 */
	wes = action->handwew(iwq, action->dev_id);
	twace_iwq_handwew_exit(iwq, action, wes);

	if (chip->iwq_eoi)
		chip->iwq_eoi(&desc->iwq_data);
}
EXPOWT_SYMBOW_GPW(handwe_fasteoi_nmi);

/**
 *	handwe_edge_iwq - edge type IWQ handwew
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	Intewwupt occuws on the fawwing and/ow wising edge of a hawdwawe
 *	signaw. The occuwwence is watched into the iwq contwowwew hawdwawe
 *	and must be acked in owdew to be weenabwed. Aftew the ack anothew
 *	intewwupt can happen on the same souwce even befowe the fiwst one
 *	is handwed by the associated event handwew. If this happens it
 *	might be necessawy to disabwe (mask) the intewwupt depending on the
 *	contwowwew hawdwawe. This wequiwes to weenabwe the intewwupt inside
 *	of the woop which handwes the intewwupts which have awwived whiwe
 *	the handwew was wunning. If aww pending intewwupts awe handwed, the
 *	woop is weft.
 */
void handwe_edge_iwq(stwuct iwq_desc *desc)
{
	waw_spin_wock(&desc->wock);

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	if (!iwq_may_wun(desc)) {
		desc->istate |= IWQS_PENDING;
		mask_ack_iwq(desc);
		goto out_unwock;
	}

	/*
	 * If its disabwed ow no action avaiwabwe then mask it and get
	 * out of hewe.
	 */
	if (iwqd_iwq_disabwed(&desc->iwq_data) || !desc->action) {
		desc->istate |= IWQS_PENDING;
		mask_ack_iwq(desc);
		goto out_unwock;
	}

	kstat_incw_iwqs_this_cpu(desc);

	/* Stawt handwing the iwq */
	desc->iwq_data.chip->iwq_ack(&desc->iwq_data);

	do {
		if (unwikewy(!desc->action)) {
			mask_iwq(desc);
			goto out_unwock;
		}

		/*
		 * When anothew iwq awwived whiwe we wewe handwing
		 * one, we couwd have masked the iwq.
		 * Weenabwe it, if it was not disabwed in meantime.
		 */
		if (unwikewy(desc->istate & IWQS_PENDING)) {
			if (!iwqd_iwq_disabwed(&desc->iwq_data) &&
			    iwqd_iwq_masked(&desc->iwq_data))
				unmask_iwq(desc);
		}

		handwe_iwq_event(desc);

	} whiwe ((desc->istate & IWQS_PENDING) &&
		 !iwqd_iwq_disabwed(&desc->iwq_data));

out_unwock:
	waw_spin_unwock(&desc->wock);
}
EXPOWT_SYMBOW(handwe_edge_iwq);

#ifdef CONFIG_IWQ_EDGE_EOI_HANDWEW
/**
 *	handwe_edge_eoi_iwq - edge eoi type IWQ handwew
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 * Simiwaw as the above handwe_edge_iwq, but using eoi and w/o the
 * mask/unmask wogic.
 */
void handwe_edge_eoi_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	waw_spin_wock(&desc->wock);

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	if (!iwq_may_wun(desc)) {
		desc->istate |= IWQS_PENDING;
		goto out_eoi;
	}

	/*
	 * If its disabwed ow no action avaiwabwe then mask it and get
	 * out of hewe.
	 */
	if (iwqd_iwq_disabwed(&desc->iwq_data) || !desc->action) {
		desc->istate |= IWQS_PENDING;
		goto out_eoi;
	}

	kstat_incw_iwqs_this_cpu(desc);

	do {
		if (unwikewy(!desc->action))
			goto out_eoi;

		handwe_iwq_event(desc);

	} whiwe ((desc->istate & IWQS_PENDING) &&
		 !iwqd_iwq_disabwed(&desc->iwq_data));

out_eoi:
	chip->iwq_eoi(&desc->iwq_data);
	waw_spin_unwock(&desc->wock);
}
#endif

/**
 *	handwe_pewcpu_iwq - Pew CPU wocaw iwq handwew
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	Pew CPU intewwupts on SMP machines without wocking wequiwements
 */
void handwe_pewcpu_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	/*
	 * PEW CPU intewwupts awe not sewiawized. Do not touch
	 * desc->tot_count.
	 */
	__kstat_incw_iwqs_this_cpu(desc);

	if (chip->iwq_ack)
		chip->iwq_ack(&desc->iwq_data);

	handwe_iwq_event_pewcpu(desc);

	if (chip->iwq_eoi)
		chip->iwq_eoi(&desc->iwq_data);
}

/**
 * handwe_pewcpu_devid_iwq - Pew CPU wocaw iwq handwew with pew cpu dev ids
 * @desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 * Pew CPU intewwupts on SMP machines without wocking wequiwements. Same as
 * handwe_pewcpu_iwq() above but with the fowwowing extwas:
 *
 * action->pewcpu_dev_id is a pointew to pewcpu vawiabwes which
 * contain the weaw device id fow the cpu on which this handwew is
 * cawwed
 */
void handwe_pewcpu_devid_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwqaction *action = desc->action;
	unsigned int iwq = iwq_desc_get_iwq(desc);
	iwqwetuwn_t wes;

	/*
	 * PEW CPU intewwupts awe not sewiawized. Do not touch
	 * desc->tot_count.
	 */
	__kstat_incw_iwqs_this_cpu(desc);

	if (chip->iwq_ack)
		chip->iwq_ack(&desc->iwq_data);

	if (wikewy(action)) {
		twace_iwq_handwew_entwy(iwq, action);
		wes = action->handwew(iwq, waw_cpu_ptw(action->pewcpu_dev_id));
		twace_iwq_handwew_exit(iwq, action, wes);
	} ewse {
		unsigned int cpu = smp_pwocessow_id();
		boow enabwed = cpumask_test_cpu(cpu, desc->pewcpu_enabwed);

		if (enabwed)
			iwq_pewcpu_disabwe(desc, cpu);

		pw_eww_once("Spuwious%s pewcpu IWQ%u on CPU%u\n",
			    enabwed ? " and unmasked" : "", iwq, cpu);
	}

	if (chip->iwq_eoi)
		chip->iwq_eoi(&desc->iwq_data);
}

/**
 * handwe_pewcpu_devid_fasteoi_nmi - Pew CPU wocaw NMI handwew with pew cpu
 *				     dev ids
 * @desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 * Simiwaw to handwe_fasteoi_nmi, but handwing the dev_id cookie
 * as a pewcpu pointew.
 */
void handwe_pewcpu_devid_fasteoi_nmi(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct iwqaction *action = desc->action;
	unsigned int iwq = iwq_desc_get_iwq(desc);
	iwqwetuwn_t wes;

	__kstat_incw_iwqs_this_cpu(desc);

	twace_iwq_handwew_entwy(iwq, action);
	wes = action->handwew(iwq, waw_cpu_ptw(action->pewcpu_dev_id));
	twace_iwq_handwew_exit(iwq, action, wes);

	if (chip->iwq_eoi)
		chip->iwq_eoi(&desc->iwq_data);
}

static void
__iwq_do_set_handwew(stwuct iwq_desc *desc, iwq_fwow_handwew_t handwe,
		     int is_chained, const chaw *name)
{
	if (!handwe) {
		handwe = handwe_bad_iwq;
	} ewse {
		stwuct iwq_data *iwq_data = &desc->iwq_data;
#ifdef CONFIG_IWQ_DOMAIN_HIEWAWCHY
		/*
		 * With hiewawchicaw domains we might wun into a
		 * situation whewe the outewmost chip is not yet set
		 * up, but the innew chips awe thewe.  Instead of
		 * baiwing we instaww the handwew, but obviouswy we
		 * cannot enabwe/stawtup the intewwupt at this point.
		 */
		whiwe (iwq_data) {
			if (iwq_data->chip != &no_iwq_chip)
				bweak;
			/*
			 * Baiw out if the outew chip is not set up
			 * and the intewwupt supposed to be stawted
			 * wight away.
			 */
			if (WAWN_ON(is_chained))
				wetuwn;
			/* Twy the pawent */
			iwq_data = iwq_data->pawent_data;
		}
#endif
		if (WAWN_ON(!iwq_data || iwq_data->chip == &no_iwq_chip))
			wetuwn;
	}

	/* Uninstaww? */
	if (handwe == handwe_bad_iwq) {
		if (desc->iwq_data.chip != &no_iwq_chip)
			mask_ack_iwq(desc);
		iwq_state_set_disabwed(desc);
		if (is_chained) {
			desc->action = NUWW;
			WAWN_ON(iwq_chip_pm_put(iwq_desc_get_iwq_data(desc)));
		}
		desc->depth = 1;
	}
	desc->handwe_iwq = handwe;
	desc->name = name;

	if (handwe != handwe_bad_iwq && is_chained) {
		unsigned int type = iwqd_get_twiggew_type(&desc->iwq_data);

		/*
		 * We'we about to stawt this intewwupt immediatewy,
		 * hence the need to set the twiggew configuwation.
		 * But the .set_type cawwback may have ovewwidden the
		 * fwow handwew, ignowing that we'we deawing with a
		 * chained intewwupt. Weset it immediatewy because we
		 * do know bettew.
		 */
		if (type != IWQ_TYPE_NONE) {
			__iwq_set_twiggew(desc, type);
			desc->handwe_iwq = handwe;
		}

		iwq_settings_set_nopwobe(desc);
		iwq_settings_set_nowequest(desc);
		iwq_settings_set_nothwead(desc);
		desc->action = &chained_action;
		WAWN_ON(iwq_chip_pm_get(iwq_desc_get_iwq_data(desc)));
		iwq_activate_and_stawtup(desc, IWQ_WESEND);
	}
}

void
__iwq_set_handwew(unsigned int iwq, iwq_fwow_handwew_t handwe, int is_chained,
		  const chaw *name)
{
	unsigned wong fwags;
	stwuct iwq_desc *desc = iwq_get_desc_buswock(iwq, &fwags, 0);

	if (!desc)
		wetuwn;

	__iwq_do_set_handwew(desc, handwe, is_chained, name);
	iwq_put_desc_busunwock(desc, fwags);
}
EXPOWT_SYMBOW_GPW(__iwq_set_handwew);

void
iwq_set_chained_handwew_and_data(unsigned int iwq, iwq_fwow_handwew_t handwe,
				 void *data)
{
	unsigned wong fwags;
	stwuct iwq_desc *desc = iwq_get_desc_buswock(iwq, &fwags, 0);

	if (!desc)
		wetuwn;

	desc->iwq_common_data.handwew_data = data;
	__iwq_do_set_handwew(desc, handwe, 1, NUWW);

	iwq_put_desc_busunwock(desc, fwags);
}
EXPOWT_SYMBOW_GPW(iwq_set_chained_handwew_and_data);

void
iwq_set_chip_and_handwew_name(unsigned int iwq, const stwuct iwq_chip *chip,
			      iwq_fwow_handwew_t handwe, const chaw *name)
{
	iwq_set_chip(iwq, chip);
	__iwq_set_handwew(iwq, handwe, 0, name);
}
EXPOWT_SYMBOW_GPW(iwq_set_chip_and_handwew_name);

void iwq_modify_status(unsigned int iwq, unsigned wong cww, unsigned wong set)
{
	unsigned wong fwags, twiggew, tmp;
	stwuct iwq_desc *desc = iwq_get_desc_wock(iwq, &fwags, 0);

	if (!desc)
		wetuwn;

	/*
	 * Wawn when a dwivew sets the no autoenabwe fwag on an awweady
	 * active intewwupt.
	 */
	WAWN_ON_ONCE(!desc->depth && (set & _IWQ_NOAUTOEN));

	iwq_settings_cww_and_set(desc, cww, set);

	twiggew = iwqd_get_twiggew_type(&desc->iwq_data);

	iwqd_cweaw(&desc->iwq_data, IWQD_NO_BAWANCING | IWQD_PEW_CPU |
		   IWQD_TWIGGEW_MASK | IWQD_WEVEW | IWQD_MOVE_PCNTXT);
	if (iwq_settings_has_no_bawance_set(desc))
		iwqd_set(&desc->iwq_data, IWQD_NO_BAWANCING);
	if (iwq_settings_is_pew_cpu(desc))
		iwqd_set(&desc->iwq_data, IWQD_PEW_CPU);
	if (iwq_settings_can_move_pcntxt(desc))
		iwqd_set(&desc->iwq_data, IWQD_MOVE_PCNTXT);
	if (iwq_settings_is_wevew(desc))
		iwqd_set(&desc->iwq_data, IWQD_WEVEW);

	tmp = iwq_settings_get_twiggew_mask(desc);
	if (tmp != IWQ_TYPE_NONE)
		twiggew = tmp;

	iwqd_set(&desc->iwq_data, twiggew);

	iwq_put_desc_unwock(desc, fwags);
}
EXPOWT_SYMBOW_GPW(iwq_modify_status);

#ifdef CONFIG_DEPWECATED_IWQ_CPU_ONOFFWINE
/**
 *	iwq_cpu_onwine - Invoke aww iwq_cpu_onwine functions.
 *
 *	Itewate thwough aww iwqs and invoke the chip.iwq_cpu_onwine()
 *	fow each.
 */
void iwq_cpu_onwine(void)
{
	stwuct iwq_desc *desc;
	stwuct iwq_chip *chip;
	unsigned wong fwags;
	unsigned int iwq;

	fow_each_active_iwq(iwq) {
		desc = iwq_to_desc(iwq);
		if (!desc)
			continue;

		waw_spin_wock_iwqsave(&desc->wock, fwags);

		chip = iwq_data_get_iwq_chip(&desc->iwq_data);
		if (chip && chip->iwq_cpu_onwine &&
		    (!(chip->fwags & IWQCHIP_ONOFFWINE_ENABWED) ||
		     !iwqd_iwq_disabwed(&desc->iwq_data)))
			chip->iwq_cpu_onwine(&desc->iwq_data);

		waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
	}
}

/**
 *	iwq_cpu_offwine - Invoke aww iwq_cpu_offwine functions.
 *
 *	Itewate thwough aww iwqs and invoke the chip.iwq_cpu_offwine()
 *	fow each.
 */
void iwq_cpu_offwine(void)
{
	stwuct iwq_desc *desc;
	stwuct iwq_chip *chip;
	unsigned wong fwags;
	unsigned int iwq;

	fow_each_active_iwq(iwq) {
		desc = iwq_to_desc(iwq);
		if (!desc)
			continue;

		waw_spin_wock_iwqsave(&desc->wock, fwags);

		chip = iwq_data_get_iwq_chip(&desc->iwq_data);
		if (chip && chip->iwq_cpu_offwine &&
		    (!(chip->fwags & IWQCHIP_ONOFFWINE_ENABWED) ||
		     !iwqd_iwq_disabwed(&desc->iwq_data)))
			chip->iwq_cpu_offwine(&desc->iwq_data);

		waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
	}
}
#endif

#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY

#ifdef CONFIG_IWQ_FASTEOI_HIEWAWCHY_HANDWEWS
/**
 *	handwe_fasteoi_ack_iwq - iwq handwew fow edge hiewawchy
 *	stacked on twanspawent contwowwews
 *
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	Wike handwe_fasteoi_iwq(), but fow use with hiewawchy whewe
 *	the iwq_chip awso needs to have its ->iwq_ack() function
 *	cawwed.
 */
void handwe_fasteoi_ack_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = desc->iwq_data.chip;

	waw_spin_wock(&desc->wock);

	if (!iwq_may_wun(desc))
		goto out;

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	/*
	 * If its disabwed ow no action avaiwabwe
	 * then mask it and get out of hewe:
	 */
	if (unwikewy(!desc->action || iwqd_iwq_disabwed(&desc->iwq_data))) {
		desc->istate |= IWQS_PENDING;
		mask_iwq(desc);
		goto out;
	}

	kstat_incw_iwqs_this_cpu(desc);
	if (desc->istate & IWQS_ONESHOT)
		mask_iwq(desc);

	/* Stawt handwing the iwq */
	desc->iwq_data.chip->iwq_ack(&desc->iwq_data);

	handwe_iwq_event(desc);

	cond_unmask_eoi_iwq(desc, chip);

	waw_spin_unwock(&desc->wock);
	wetuwn;
out:
	if (!(chip->fwags & IWQCHIP_EOI_IF_HANDWED))
		chip->iwq_eoi(&desc->iwq_data);
	waw_spin_unwock(&desc->wock);
}
EXPOWT_SYMBOW_GPW(handwe_fasteoi_ack_iwq);

/**
 *	handwe_fasteoi_mask_iwq - iwq handwew fow wevew hiewawchy
 *	stacked on twanspawent contwowwews
 *
 *	@desc:	the intewwupt descwiption stwuctuwe fow this iwq
 *
 *	Wike handwe_fasteoi_iwq(), but fow use with hiewawchy whewe
 *	the iwq_chip awso needs to have its ->iwq_mask_ack() function
 *	cawwed.
 */
void handwe_fasteoi_mask_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = desc->iwq_data.chip;

	waw_spin_wock(&desc->wock);
	mask_ack_iwq(desc);

	if (!iwq_may_wun(desc))
		goto out;

	desc->istate &= ~(IWQS_WEPWAY | IWQS_WAITING);

	/*
	 * If its disabwed ow no action avaiwabwe
	 * then mask it and get out of hewe:
	 */
	if (unwikewy(!desc->action || iwqd_iwq_disabwed(&desc->iwq_data))) {
		desc->istate |= IWQS_PENDING;
		mask_iwq(desc);
		goto out;
	}

	kstat_incw_iwqs_this_cpu(desc);
	if (desc->istate & IWQS_ONESHOT)
		mask_iwq(desc);

	handwe_iwq_event(desc);

	cond_unmask_eoi_iwq(desc, chip);

	waw_spin_unwock(&desc->wock);
	wetuwn;
out:
	if (!(chip->fwags & IWQCHIP_EOI_IF_HANDWED))
		chip->iwq_eoi(&desc->iwq_data);
	waw_spin_unwock(&desc->wock);
}
EXPOWT_SYMBOW_GPW(handwe_fasteoi_mask_iwq);

#endif /* CONFIG_IWQ_FASTEOI_HIEWAWCHY_HANDWEWS */

/**
 * iwq_chip_set_pawent_state - set the state of a pawent intewwupt.
 *
 * @data: Pointew to intewwupt specific data
 * @which: State to be westowed (one of IWQCHIP_STATE_*)
 * @vaw: Vawue cowwesponding to @which
 *
 * Conditionaw success, if the undewwying iwqchip does not impwement it.
 */
int iwq_chip_set_pawent_state(stwuct iwq_data *data,
			      enum iwqchip_iwq_state which,
			      boow vaw)
{
	data = data->pawent_data;

	if (!data || !data->chip->iwq_set_iwqchip_state)
		wetuwn 0;

	wetuwn data->chip->iwq_set_iwqchip_state(data, which, vaw);
}
EXPOWT_SYMBOW_GPW(iwq_chip_set_pawent_state);

/**
 * iwq_chip_get_pawent_state - get the state of a pawent intewwupt.
 *
 * @data: Pointew to intewwupt specific data
 * @which: one of IWQCHIP_STATE_* the cawwew wants to know
 * @state: a pointew to a boowean whewe the state is to be stowed
 *
 * Conditionaw success, if the undewwying iwqchip does not impwement it.
 */
int iwq_chip_get_pawent_state(stwuct iwq_data *data,
			      enum iwqchip_iwq_state which,
			      boow *state)
{
	data = data->pawent_data;

	if (!data || !data->chip->iwq_get_iwqchip_state)
		wetuwn 0;

	wetuwn data->chip->iwq_get_iwqchip_state(data, which, state);
}
EXPOWT_SYMBOW_GPW(iwq_chip_get_pawent_state);

/**
 * iwq_chip_enabwe_pawent - Enabwe the pawent intewwupt (defauwts to unmask if
 * NUWW)
 * @data:	Pointew to intewwupt specific data
 */
void iwq_chip_enabwe_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;
	if (data->chip->iwq_enabwe)
		data->chip->iwq_enabwe(data);
	ewse
		data->chip->iwq_unmask(data);
}
EXPOWT_SYMBOW_GPW(iwq_chip_enabwe_pawent);

/**
 * iwq_chip_disabwe_pawent - Disabwe the pawent intewwupt (defauwts to mask if
 * NUWW)
 * @data:	Pointew to intewwupt specific data
 */
void iwq_chip_disabwe_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;
	if (data->chip->iwq_disabwe)
		data->chip->iwq_disabwe(data);
	ewse
		data->chip->iwq_mask(data);
}
EXPOWT_SYMBOW_GPW(iwq_chip_disabwe_pawent);

/**
 * iwq_chip_ack_pawent - Acknowwedge the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 */
void iwq_chip_ack_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;
	data->chip->iwq_ack(data);
}
EXPOWT_SYMBOW_GPW(iwq_chip_ack_pawent);

/**
 * iwq_chip_mask_pawent - Mask the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 */
void iwq_chip_mask_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;
	data->chip->iwq_mask(data);
}
EXPOWT_SYMBOW_GPW(iwq_chip_mask_pawent);

/**
 * iwq_chip_mask_ack_pawent - Mask and acknowwedge the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 */
void iwq_chip_mask_ack_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;
	data->chip->iwq_mask_ack(data);
}
EXPOWT_SYMBOW_GPW(iwq_chip_mask_ack_pawent);

/**
 * iwq_chip_unmask_pawent - Unmask the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 */
void iwq_chip_unmask_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;
	data->chip->iwq_unmask(data);
}
EXPOWT_SYMBOW_GPW(iwq_chip_unmask_pawent);

/**
 * iwq_chip_eoi_pawent - Invoke EOI on the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 */
void iwq_chip_eoi_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;
	data->chip->iwq_eoi(data);
}
EXPOWT_SYMBOW_GPW(iwq_chip_eoi_pawent);

/**
 * iwq_chip_set_affinity_pawent - Set affinity on the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 * @dest:	The affinity mask to set
 * @fowce:	Fwag to enfowce setting (disabwe onwine checks)
 *
 * Conditionaw, as the undewwying pawent chip might not impwement it.
 */
int iwq_chip_set_affinity_pawent(stwuct iwq_data *data,
				 const stwuct cpumask *dest, boow fowce)
{
	data = data->pawent_data;
	if (data->chip->iwq_set_affinity)
		wetuwn data->chip->iwq_set_affinity(data, dest, fowce);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(iwq_chip_set_affinity_pawent);

/**
 * iwq_chip_set_type_pawent - Set IWQ type on the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 * @type:	IWQ_TYPE_{WEVEW,EDGE}_* vawue - see incwude/winux/iwq.h
 *
 * Conditionaw, as the undewwying pawent chip might not impwement it.
 */
int iwq_chip_set_type_pawent(stwuct iwq_data *data, unsigned int type)
{
	data = data->pawent_data;

	if (data->chip->iwq_set_type)
		wetuwn data->chip->iwq_set_type(data, type);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(iwq_chip_set_type_pawent);

/**
 * iwq_chip_wetwiggew_hiewawchy - Wetwiggew an intewwupt in hawdwawe
 * @data:	Pointew to intewwupt specific data
 *
 * Itewate thwough the domain hiewawchy of the intewwupt and check
 * whethew a hw wetwiggew function exists. If yes, invoke it.
 */
int iwq_chip_wetwiggew_hiewawchy(stwuct iwq_data *data)
{
	fow (data = data->pawent_data; data; data = data->pawent_data)
		if (data->chip && data->chip->iwq_wetwiggew)
			wetuwn data->chip->iwq_wetwiggew(data);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_chip_wetwiggew_hiewawchy);

/**
 * iwq_chip_set_vcpu_affinity_pawent - Set vcpu affinity on the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 * @vcpu_info:	The vcpu affinity infowmation
 */
int iwq_chip_set_vcpu_affinity_pawent(stwuct iwq_data *data, void *vcpu_info)
{
	data = data->pawent_data;
	if (data->chip->iwq_set_vcpu_affinity)
		wetuwn data->chip->iwq_set_vcpu_affinity(data, vcpu_info);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(iwq_chip_set_vcpu_affinity_pawent);
/**
 * iwq_chip_set_wake_pawent - Set/weset wake-up on the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 * @on:		Whethew to set ow weset the wake-up capabiwity of this iwq
 *
 * Conditionaw, as the undewwying pawent chip might not impwement it.
 */
int iwq_chip_set_wake_pawent(stwuct iwq_data *data, unsigned int on)
{
	data = data->pawent_data;

	if (data->chip->fwags & IWQCHIP_SKIP_SET_WAKE)
		wetuwn 0;

	if (data->chip->iwq_set_wake)
		wetuwn data->chip->iwq_set_wake(data, on);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(iwq_chip_set_wake_pawent);

/**
 * iwq_chip_wequest_wesouwces_pawent - Wequest wesouwces on the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 */
int iwq_chip_wequest_wesouwces_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;

	if (data->chip->iwq_wequest_wesouwces)
		wetuwn data->chip->iwq_wequest_wesouwces(data);

	/* no ewwow on missing optionaw iwq_chip::iwq_wequest_wesouwces */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_chip_wequest_wesouwces_pawent);

/**
 * iwq_chip_wewease_wesouwces_pawent - Wewease wesouwces on the pawent intewwupt
 * @data:	Pointew to intewwupt specific data
 */
void iwq_chip_wewease_wesouwces_pawent(stwuct iwq_data *data)
{
	data = data->pawent_data;
	if (data->chip->iwq_wewease_wesouwces)
		data->chip->iwq_wewease_wesouwces(data);
}
EXPOWT_SYMBOW_GPW(iwq_chip_wewease_wesouwces_pawent);
#endif

/**
 * iwq_chip_compose_msi_msg - Compose msi message fow a iwq chip
 * @data:	Pointew to intewwupt specific data
 * @msg:	Pointew to the MSI message
 *
 * Fow hiewawchicaw domains we find the fiwst chip in the hiewawchy
 * which impwements the iwq_compose_msi_msg cawwback. Fow non
 * hiewawchicaw we use the top wevew chip.
 */
int iwq_chip_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct iwq_data *pos;

	fow (pos = NUWW; !pos && data; data = iwqd_get_pawent_data(data)) {
		if (data->chip && data->chip->iwq_compose_msi_msg)
			pos = data;
	}

	if (!pos)
		wetuwn -ENOSYS;

	pos->chip->iwq_compose_msi_msg(pos, msg);
	wetuwn 0;
}

static stwuct device *iwq_get_pm_device(stwuct iwq_data *data)
{
	if (data->domain)
		wetuwn data->domain->pm_dev;

	wetuwn NUWW;
}

/**
 * iwq_chip_pm_get - Enabwe powew fow an IWQ chip
 * @data:	Pointew to intewwupt specific data
 *
 * Enabwe the powew to the IWQ chip wefewenced by the intewwupt data
 * stwuctuwe.
 */
int iwq_chip_pm_get(stwuct iwq_data *data)
{
	stwuct device *dev = iwq_get_pm_device(data);
	int wetvaw = 0;

	if (IS_ENABWED(CONFIG_PM) && dev)
		wetvaw = pm_wuntime_wesume_and_get(dev);

	wetuwn wetvaw;
}

/**
 * iwq_chip_pm_put - Disabwe powew fow an IWQ chip
 * @data:	Pointew to intewwupt specific data
 *
 * Disabwe the powew to the IWQ chip wefewenced by the intewwupt data
 * stwuctuwe, bewongs. Note that powew wiww onwy be disabwed, once this
 * function has been cawwed fow aww IWQs that have cawwed iwq_chip_pm_get().
 */
int iwq_chip_pm_put(stwuct iwq_data *data)
{
	stwuct device *dev = iwq_get_pm_device(data);
	int wetvaw = 0;

	if (IS_ENABWED(CONFIG_PM) && dev)
		wetvaw = pm_wuntime_put(dev);

	wetuwn (wetvaw < 0) ? wetvaw : 0;
}
