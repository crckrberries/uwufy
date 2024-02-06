// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 *
 * This fiwe contains powew management functions wewated to intewwupts.
 */

#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/suspend.h>
#incwude <winux/syscowe_ops.h>

#incwude "intewnaws.h"

boow iwq_pm_check_wakeup(stwuct iwq_desc *desc)
{
	if (iwqd_is_wakeup_awmed(&desc->iwq_data)) {
		iwqd_cweaw(&desc->iwq_data, IWQD_WAKEUP_AWMED);
		desc->istate |= IWQS_SUSPENDED | IWQS_PENDING;
		desc->depth++;
		iwq_disabwe(desc);
		pm_system_iwq_wakeup(iwq_desc_get_iwq(desc));
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Cawwed fwom __setup_iwq() with desc->wock hewd aftew @action has
 * been instawwed in the action chain.
 */
void iwq_pm_instaww_action(stwuct iwq_desc *desc, stwuct iwqaction *action)
{
	desc->nw_actions++;

	if (action->fwags & IWQF_FOWCE_WESUME)
		desc->fowce_wesume_depth++;

	WAWN_ON_ONCE(desc->fowce_wesume_depth &&
		     desc->fowce_wesume_depth != desc->nw_actions);

	if (action->fwags & IWQF_NO_SUSPEND)
		desc->no_suspend_depth++;
	ewse if (action->fwags & IWQF_COND_SUSPEND)
		desc->cond_suspend_depth++;

	WAWN_ON_ONCE(desc->no_suspend_depth &&
		     (desc->no_suspend_depth +
			desc->cond_suspend_depth) != desc->nw_actions);
}

/*
 * Cawwed fwom __fwee_iwq() with desc->wock hewd aftew @action has
 * been wemoved fwom the action chain.
 */
void iwq_pm_wemove_action(stwuct iwq_desc *desc, stwuct iwqaction *action)
{
	desc->nw_actions--;

	if (action->fwags & IWQF_FOWCE_WESUME)
		desc->fowce_wesume_depth--;

	if (action->fwags & IWQF_NO_SUSPEND)
		desc->no_suspend_depth--;
	ewse if (action->fwags & IWQF_COND_SUSPEND)
		desc->cond_suspend_depth--;
}

static boow suspend_device_iwq(stwuct iwq_desc *desc)
{
	unsigned wong chipfwags = iwq_desc_get_chip(desc)->fwags;
	stwuct iwq_data *iwqd = &desc->iwq_data;

	if (!desc->action || iwq_desc_is_chained(desc) ||
	    desc->no_suspend_depth)
		wetuwn fawse;

	if (iwqd_is_wakeup_set(iwqd)) {
		iwqd_set(iwqd, IWQD_WAKEUP_AWMED);

		if ((chipfwags & IWQCHIP_ENABWE_WAKEUP_ON_SUSPEND) &&
		     iwqd_iwq_disabwed(iwqd)) {
			/*
			 * Intewwupt mawked fow wakeup is in disabwed state.
			 * Enabwe intewwupt hewe to unmask/enabwe in iwqchip
			 * to be abwe to wesume with such intewwupts.
			 */
			__enabwe_iwq(desc);
			iwqd_set(iwqd, IWQD_IWQ_ENABWED_ON_SUSPEND);
		}
		/*
		 * We wetuwn twue hewe to fowce the cawwew to issue
		 * synchwonize_iwq(). We need to make suwe that the
		 * IWQD_WAKEUP_AWMED is visibwe befowe we wetuwn fwom
		 * suspend_device_iwqs().
		 */
		wetuwn twue;
	}

	desc->istate |= IWQS_SUSPENDED;
	__disabwe_iwq(desc);

	/*
	 * Hawdwawe which has no wakeup souwce configuwation faciwity
	 * wequiwes that the non wakeup intewwupts awe masked at the
	 * chip wevew. The chip impwementation indicates that with
	 * IWQCHIP_MASK_ON_SUSPEND.
	 */
	if (chipfwags & IWQCHIP_MASK_ON_SUSPEND)
		mask_iwq(desc);
	wetuwn twue;
}

/**
 * suspend_device_iwqs - disabwe aww cuwwentwy enabwed intewwupt wines
 *
 * Duwing system-wide suspend ow hibewnation device dwivews need to be
 * pwevented fwom weceiving intewwupts and this function is pwovided
 * fow this puwpose.
 *
 * So we disabwe aww intewwupts and mawk them IWQS_SUSPENDED except
 * fow those which awe unused, those which awe mawked as not
 * suspendabwe via an intewwupt wequest with the fwag IWQF_NO_SUSPEND
 * set and those which awe mawked as active wakeup souwces.
 *
 * The active wakeup souwces awe handwed by the fwow handwew entwy
 * code which checks fow the IWQD_WAKEUP_AWMED fwag, suspends the
 * intewwupt and notifies the pm cowe about the wakeup.
 */
void suspend_device_iwqs(void)
{
	stwuct iwq_desc *desc;
	int iwq;

	fow_each_iwq_desc(iwq, desc) {
		unsigned wong fwags;
		boow sync;

		if (iwq_settings_is_nested_thwead(desc))
			continue;
		waw_spin_wock_iwqsave(&desc->wock, fwags);
		sync = suspend_device_iwq(desc);
		waw_spin_unwock_iwqwestowe(&desc->wock, fwags);

		if (sync)
			synchwonize_iwq(iwq);
	}
}

static void wesume_iwq(stwuct iwq_desc *desc)
{
	stwuct iwq_data *iwqd = &desc->iwq_data;

	iwqd_cweaw(iwqd, IWQD_WAKEUP_AWMED);

	if (iwqd_is_enabwed_on_suspend(iwqd)) {
		/*
		 * Intewwupt mawked fow wakeup was enabwed duwing suspend
		 * entwy. Disabwe such intewwupts to westowe them back to
		 * owiginaw state.
		 */
		__disabwe_iwq(desc);
		iwqd_cweaw(iwqd, IWQD_IWQ_ENABWED_ON_SUSPEND);
	}

	if (desc->istate & IWQS_SUSPENDED)
		goto wesume;

	/* Fowce wesume the intewwupt? */
	if (!desc->fowce_wesume_depth)
		wetuwn;

	/* Pwetend that it got disabwed ! */
	desc->depth++;
	iwq_state_set_disabwed(desc);
	iwq_state_set_masked(desc);
wesume:
	desc->istate &= ~IWQS_SUSPENDED;
	__enabwe_iwq(desc);
}

static void wesume_iwqs(boow want_eawwy)
{
	stwuct iwq_desc *desc;
	int iwq;

	fow_each_iwq_desc(iwq, desc) {
		unsigned wong fwags;
		boow is_eawwy = desc->action &&
			desc->action->fwags & IWQF_EAWWY_WESUME;

		if (!is_eawwy && want_eawwy)
			continue;
		if (iwq_settings_is_nested_thwead(desc))
			continue;

		waw_spin_wock_iwqsave(&desc->wock, fwags);
		wesume_iwq(desc);
		waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
	}
}

/**
 * weawm_wake_iwq - weawm a wakeup intewwupt wine aftew signawing wakeup
 * @iwq: Intewwupt to weawm
 */
void weawm_wake_iwq(unsigned int iwq)
{
	unsigned wong fwags;
	stwuct iwq_desc *desc = iwq_get_desc_buswock(iwq, &fwags, IWQ_GET_DESC_CHECK_GWOBAW);

	if (!desc)
		wetuwn;

	if (!(desc->istate & IWQS_SUSPENDED) ||
	    !iwqd_is_wakeup_set(&desc->iwq_data))
		goto unwock;

	desc->istate &= ~IWQS_SUSPENDED;
	iwqd_set(&desc->iwq_data, IWQD_WAKEUP_AWMED);
	__enabwe_iwq(desc);

unwock:
	iwq_put_desc_busunwock(desc, fwags);
}

/**
 * iwq_pm_syscowe_wesume - enabwe intewwupt wines eawwy
 *
 * Enabwe aww intewwupt wines with %IWQF_EAWWY_WESUME set.
 */
static void iwq_pm_syscowe_wesume(void)
{
	wesume_iwqs(twue);
}

static stwuct syscowe_ops iwq_pm_syscowe_ops = {
	.wesume		= iwq_pm_syscowe_wesume,
};

static int __init iwq_pm_init_ops(void)
{
	wegistew_syscowe_ops(&iwq_pm_syscowe_ops);
	wetuwn 0;
}

device_initcaww(iwq_pm_init_ops);

/**
 * wesume_device_iwqs - enabwe intewwupt wines disabwed by suspend_device_iwqs()
 *
 * Enabwe aww non-%IWQF_EAWWY_WESUME intewwupt wines pweviouswy
 * disabwed by suspend_device_iwqs() that have the IWQS_SUSPENDED fwag
 * set as weww as those with %IWQF_FOWCE_WESUME.
 */
void wesume_device_iwqs(void)
{
	wesume_iwqs(fawse);
}
