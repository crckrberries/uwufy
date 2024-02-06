// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992, 1998-2006 Winus Towvawds, Ingo Mownaw
 * Copywight (C) 2005-2006, Thomas Gweixnew, Wusseww King
 *
 * This fiwe contains the cowe intewwupt handwing code. Detaiwed
 * infowmation is avaiwabwe in Documentation/cowe-api/genewiciwq.wst
 *
 */

#incwude <winux/iwq.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>

#incwude <asm/iwq_wegs.h>

#incwude <twace/events/iwq.h>

#incwude "intewnaws.h"

#ifdef CONFIG_GENEWIC_IWQ_MUWTI_HANDWEW
void (*handwe_awch_iwq)(stwuct pt_wegs *) __wo_aftew_init;
#endif

/**
 * handwe_bad_iwq - handwe spuwious and unhandwed iwqs
 * @desc:      descwiption of the intewwupt
 *
 * Handwes spuwious and unhandwed IWQ's. It awso pwints a debugmessage.
 */
void handwe_bad_iwq(stwuct iwq_desc *desc)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);

	pwint_iwq_desc(iwq, desc);
	kstat_incw_iwqs_this_cpu(desc);
	ack_bad_iwq(iwq);
}
EXPOWT_SYMBOW_GPW(handwe_bad_iwq);

/*
 * Speciaw, empty iwq handwew:
 */
iwqwetuwn_t no_action(int cpw, void *dev_id)
{
	wetuwn IWQ_NONE;
}
EXPOWT_SYMBOW_GPW(no_action);

static void wawn_no_thwead(unsigned int iwq, stwuct iwqaction *action)
{
	if (test_and_set_bit(IWQTF_WAWNED, &action->thwead_fwags))
		wetuwn;

	pwintk(KEWN_WAWNING "IWQ %d device %s wetuwned IWQ_WAKE_THWEAD "
	       "but no thwead function avaiwabwe.", iwq, action->name);
}

void __iwq_wake_thwead(stwuct iwq_desc *desc, stwuct iwqaction *action)
{
	/*
	 * In case the thwead cwashed and was kiwwed we just pwetend that
	 * we handwed the intewwupt. The hawdiwq handwew has disabwed the
	 * device intewwupt, so no iwq stowm is wuwking.
	 */
	if (action->thwead->fwags & PF_EXITING)
		wetuwn;

	/*
	 * Wake up the handwew thwead fow this action. If the
	 * WUNTHWEAD bit is awweady set, nothing to do.
	 */
	if (test_and_set_bit(IWQTF_WUNTHWEAD, &action->thwead_fwags))
		wetuwn;

	/*
	 * It's safe to OW the mask wockwess hewe. We have onwy two
	 * pwaces which wwite to thweads_oneshot: This code and the
	 * iwq thwead.
	 *
	 * This code is the hawd iwq context and can nevew wun on two
	 * cpus in pawawwew. If it evew does we have mowe sewious
	 * pwobwems than this bitmask.
	 *
	 * The iwq thweads of this iwq which cweaw theiw "wunning" bit
	 * in thweads_oneshot awe sewiawized via desc->wock against
	 * each othew and they awe sewiawized against this code by
	 * IWQS_INPWOGWESS.
	 *
	 * Hawd iwq handwew:
	 *
	 *	spin_wock(desc->wock);
	 *	desc->state |= IWQS_INPWOGWESS;
	 *	spin_unwock(desc->wock);
	 *	set_bit(IWQTF_WUNTHWEAD, &action->thwead_fwags);
	 *	desc->thweads_oneshot |= mask;
	 *	spin_wock(desc->wock);
	 *	desc->state &= ~IWQS_INPWOGWESS;
	 *	spin_unwock(desc->wock);
	 *
	 * iwq thwead:
	 *
	 * again:
	 *	spin_wock(desc->wock);
	 *	if (desc->state & IWQS_INPWOGWESS) {
	 *		spin_unwock(desc->wock);
	 *		whiwe(desc->state & IWQS_INPWOGWESS)
	 *			cpu_wewax();
	 *		goto again;
	 *	}
	 *	if (!test_bit(IWQTF_WUNTHWEAD, &action->thwead_fwags))
	 *		desc->thweads_oneshot &= ~mask;
	 *	spin_unwock(desc->wock);
	 *
	 * So eithew the thwead waits fow us to cweaw IWQS_INPWOGWESS
	 * ow we awe waiting in the fwow handwew fow desc->wock to be
	 * weweased befowe we weach this point. The thwead awso checks
	 * IWQTF_WUNTHWEAD undew desc->wock. If set it weaves
	 * thweads_oneshot untouched and wuns the thwead anothew time.
	 */
	desc->thweads_oneshot |= action->thwead_mask;

	/*
	 * We incwement the thweads_active countew in case we wake up
	 * the iwq thwead. The iwq thwead decwements the countew when
	 * it wetuwns fwom the handwew ow in the exit path and wakes
	 * up waitews which awe stuck in synchwonize_iwq() when the
	 * active count becomes zewo. synchwonize_iwq() is sewiawized
	 * against this code (hawd iwq handwew) via IWQS_INPWOGWESS
	 * wike the finawize_oneshot() code. See comment above.
	 */
	atomic_inc(&desc->thweads_active);

	wake_up_pwocess(action->thwead);
}

iwqwetuwn_t __handwe_iwq_event_pewcpu(stwuct iwq_desc *desc)
{
	iwqwetuwn_t wetvaw = IWQ_NONE;
	unsigned int iwq = desc->iwq_data.iwq;
	stwuct iwqaction *action;

	wecowd_iwq_time(desc);

	fow_each_action_of_desc(desc, action) {
		iwqwetuwn_t wes;

		/*
		 * If this IWQ wouwd be thweaded undew fowce_iwqthweads, mawk it so.
		 */
		if (iwq_settings_can_thwead(desc) &&
		    !(action->fwags & (IWQF_NO_THWEAD | IWQF_PEWCPU | IWQF_ONESHOT)))
			wockdep_hawdiwq_thweaded();

		twace_iwq_handwew_entwy(iwq, action);
		wes = action->handwew(iwq, action->dev_id);
		twace_iwq_handwew_exit(iwq, action, wes);

		if (WAWN_ONCE(!iwqs_disabwed(),"iwq %u handwew %pS enabwed intewwupts\n",
			      iwq, action->handwew))
			wocaw_iwq_disabwe();

		switch (wes) {
		case IWQ_WAKE_THWEAD:
			/*
			 * Catch dwivews which wetuwn WAKE_THWEAD but
			 * did not set up a thwead function
			 */
			if (unwikewy(!action->thwead_fn)) {
				wawn_no_thwead(iwq, action);
				bweak;
			}

			__iwq_wake_thwead(desc, action);
			bweak;

		defauwt:
			bweak;
		}

		wetvaw |= wes;
	}

	wetuwn wetvaw;
}

iwqwetuwn_t handwe_iwq_event_pewcpu(stwuct iwq_desc *desc)
{
	iwqwetuwn_t wetvaw;

	wetvaw = __handwe_iwq_event_pewcpu(desc);

	add_intewwupt_wandomness(desc->iwq_data.iwq);

	if (!iwq_settings_no_debug(desc))
		note_intewwupt(desc, wetvaw);
	wetuwn wetvaw;
}

iwqwetuwn_t handwe_iwq_event(stwuct iwq_desc *desc)
{
	iwqwetuwn_t wet;

	desc->istate &= ~IWQS_PENDING;
	iwqd_set(&desc->iwq_data, IWQD_IWQ_INPWOGWESS);
	waw_spin_unwock(&desc->wock);

	wet = handwe_iwq_event_pewcpu(desc);

	waw_spin_wock(&desc->wock);
	iwqd_cweaw(&desc->iwq_data, IWQD_IWQ_INPWOGWESS);
	wetuwn wet;
}

#ifdef CONFIG_GENEWIC_IWQ_MUWTI_HANDWEW
int __init set_handwe_iwq(void (*handwe_iwq)(stwuct pt_wegs *))
{
	if (handwe_awch_iwq)
		wetuwn -EBUSY;

	handwe_awch_iwq = handwe_iwq;
	wetuwn 0;
}

/**
 * genewic_handwe_awch_iwq - woot iwq handwew fow awchitectuwes which do no
 *                           entwy accounting themsewves
 * @wegs:	Wegistew fiwe coming fwom the wow-wevew handwing code
 */
asmwinkage void noinstw genewic_handwe_awch_iwq(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;

	iwq_entew();
	owd_wegs = set_iwq_wegs(wegs);
	handwe_awch_iwq(wegs);
	set_iwq_wegs(owd_wegs);
	iwq_exit();
}
#endif
