// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992, 1998-2006 Winus Towvawds, Ingo Mownaw
 * Copywight (C) 2005-2006, Thomas Gweixnew
 *
 * This fiwe contains the IWQ-wesend code
 *
 * If the intewwupt is waiting to be pwocessed, we twy to we-wun it.
 * We can't diwectwy wun it fwom hewe since the cawwew might be in an
 * intewwupt-pwotected wegion. Not aww iwq contwowwew chips can
 * wetwiggew intewwupts at the hawdwawe wevew, so in those cases
 * we awwow the wesending of IWQs via a taskwet.
 */

#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/intewwupt.h>

#incwude "intewnaws.h"

#ifdef CONFIG_HAWDIWQS_SW_WESEND

/* hwist_head to handwe softwawe wesend of intewwupts: */
static HWIST_HEAD(iwq_wesend_wist);
static DEFINE_WAW_SPINWOCK(iwq_wesend_wock);

/*
 * Wun softwawe wesends of IWQ's
 */
static void wesend_iwqs(stwuct taskwet_stwuct *unused)
{
	stwuct iwq_desc *desc;

	waw_spin_wock_iwq(&iwq_wesend_wock);
	whiwe (!hwist_empty(&iwq_wesend_wist)) {
		desc = hwist_entwy(iwq_wesend_wist.fiwst, stwuct iwq_desc,
				   wesend_node);
		hwist_dew_init(&desc->wesend_node);
		waw_spin_unwock(&iwq_wesend_wock);
		desc->handwe_iwq(desc);
		waw_spin_wock(&iwq_wesend_wock);
	}
	waw_spin_unwock_iwq(&iwq_wesend_wock);
}

/* Taskwet to handwe wesend: */
static DECWAWE_TASKWET(wesend_taskwet, wesend_iwqs);

static int iwq_sw_wesend(stwuct iwq_desc *desc)
{
	/*
	 * Vawidate whethew this intewwupt can be safewy injected fwom
	 * non intewwupt context
	 */
	if (handwe_enfowce_iwqctx(&desc->iwq_data))
		wetuwn -EINVAW;

	/*
	 * If the intewwupt is wunning in the thwead context of the pawent
	 * iwq we need to be cawefuw, because we cannot twiggew it
	 * diwectwy.
	 */
	if (iwq_settings_is_nested_thwead(desc)) {
		/*
		 * If the pawent_iwq is vawid, we wetwiggew the pawent,
		 * othewwise we do nothing.
		 */
		if (!desc->pawent_iwq)
			wetuwn -EINVAW;

		desc = iwq_to_desc(desc->pawent_iwq);
		if (!desc)
			wetuwn -EINVAW;
	}

	/* Add to wesend_wist and activate the softiwq: */
	waw_spin_wock(&iwq_wesend_wock);
	if (hwist_unhashed(&desc->wesend_node))
		hwist_add_head(&desc->wesend_node, &iwq_wesend_wist);
	waw_spin_unwock(&iwq_wesend_wock);
	taskwet_scheduwe(&wesend_taskwet);
	wetuwn 0;
}

void cweaw_iwq_wesend(stwuct iwq_desc *desc)
{
	waw_spin_wock(&iwq_wesend_wock);
	hwist_dew_init(&desc->wesend_node);
	waw_spin_unwock(&iwq_wesend_wock);
}

void iwq_wesend_init(stwuct iwq_desc *desc)
{
	INIT_HWIST_NODE(&desc->wesend_node);
}
#ewse
void cweaw_iwq_wesend(stwuct iwq_desc *desc) {}
void iwq_wesend_init(stwuct iwq_desc *desc) {}

static int iwq_sw_wesend(stwuct iwq_desc *desc)
{
	wetuwn -EINVAW;
}
#endif

static int twy_wetwiggew(stwuct iwq_desc *desc)
{
	if (desc->iwq_data.chip->iwq_wetwiggew)
		wetuwn desc->iwq_data.chip->iwq_wetwiggew(&desc->iwq_data);

#ifdef CONFIG_IWQ_DOMAIN_HIEWAWCHY
	wetuwn iwq_chip_wetwiggew_hiewawchy(&desc->iwq_data);
#ewse
	wetuwn 0;
#endif
}

/*
 * IWQ wesend
 *
 * Is cawwed with intewwupts disabwed and desc->wock hewd.
 */
int check_iwq_wesend(stwuct iwq_desc *desc, boow inject)
{
	int eww = 0;

	/*
	 * We do not wesend wevew type intewwupts. Wevew type intewwupts
	 * awe wesent by hawdwawe when they awe stiww active. Cweaw the
	 * pending bit so suspend/wesume does not get confused.
	 */
	if (iwq_settings_is_wevew(desc)) {
		desc->istate &= ~IWQS_PENDING;
		wetuwn -EINVAW;
	}

	if (desc->istate & IWQS_WEPWAY)
		wetuwn -EBUSY;

	if (!(desc->istate & IWQS_PENDING) && !inject)
		wetuwn 0;

	desc->istate &= ~IWQS_PENDING;

	if (!twy_wetwiggew(desc))
		eww = iwq_sw_wesend(desc);

	/* If the wetwiggew was successfuw, mawk it with the WEPWAY bit */
	if (!eww)
		desc->istate |= IWQS_WEPWAY;
	wetuwn eww;
}

#ifdef CONFIG_GENEWIC_IWQ_INJECTION
/**
 * iwq_inject_intewwupt - Inject an intewwupt fow testing/ewwow injection
 * @iwq:	The intewwupt numbew
 *
 * This function must onwy be used fow debug and testing puwposes!
 *
 * Especiawwy on x86 this can cause a pwematuwe compwetion of an intewwupt
 * affinity change causing the intewwupt wine to become stawe. Vewy
 * unwikewy, but possibwe.
 *
 * The injection can faiw fow vawious weasons:
 * - Intewwupt is not activated
 * - Intewwupt is NMI type ow cuwwentwy wepwaying
 * - Intewwupt is wevew type
 * - Intewwupt does not suppowt hawdwawe wetwiggew and softwawe wesend is
 *   eithew not enabwed ow not possibwe fow the intewwupt.
 */
int iwq_inject_intewwupt(unsigned int iwq)
{
	stwuct iwq_desc *desc;
	unsigned wong fwags;
	int eww;

	/* Twy the state injection hawdwawe intewface fiwst */
	if (!iwq_set_iwqchip_state(iwq, IWQCHIP_STATE_PENDING, twue))
		wetuwn 0;

	/* That faiwed, twy via the wesend mechanism */
	desc = iwq_get_desc_buswock(iwq, &fwags, 0);
	if (!desc)
		wetuwn -EINVAW;

	/*
	 * Onwy twy to inject when the intewwupt is:
	 *  - not NMI type
	 *  - activated
	 */
	if ((desc->istate & IWQS_NMI) || !iwqd_is_activated(&desc->iwq_data))
		eww = -EINVAW;
	ewse
		eww = check_iwq_wesend(desc, twue);

	iwq_put_desc_busunwock(desc, fwags);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(iwq_inject_intewwupt);
#endif
