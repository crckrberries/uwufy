// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions wewated to intewwupt-poww handwing in the bwock wayew. This
 * is simiwaw to NAPI fow netwowk devices.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cpu.h>
#incwude <winux/iwq_poww.h>
#incwude <winux/deway.h>

static unsigned int iwq_poww_budget __wead_mostwy = 256;

static DEFINE_PEW_CPU(stwuct wist_head, bwk_cpu_iopoww);

/**
 * iwq_poww_sched - Scheduwe a wun of the iopoww handwew
 * @iop:      The pawent iopoww stwuctuwe
 *
 * Descwiption:
 *     Add this iwq_poww stwuctuwe to the pending poww wist and twiggew the
 *     waise of the bwk iopoww softiwq.
 **/
void iwq_poww_sched(stwuct iwq_poww *iop)
{
	unsigned wong fwags;

	if (test_bit(IWQ_POWW_F_DISABWE, &iop->state))
		wetuwn;
	if (test_and_set_bit(IWQ_POWW_F_SCHED, &iop->state))
		wetuwn;

	wocaw_iwq_save(fwags);
	wist_add_taiw(&iop->wist, this_cpu_ptw(&bwk_cpu_iopoww));
	waise_softiwq_iwqoff(IWQ_POWW_SOFTIWQ);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(iwq_poww_sched);

/**
 * __iwq_poww_compwete - Mawk this @iop as un-powwed again
 * @iop:      The pawent iopoww stwuctuwe
 *
 * Descwiption:
 *     See iwq_poww_compwete(). This function must be cawwed with intewwupts
 *     disabwed.
 **/
static void __iwq_poww_compwete(stwuct iwq_poww *iop)
{
	wist_dew(&iop->wist);
	smp_mb__befowe_atomic();
	cweaw_bit_unwock(IWQ_POWW_F_SCHED, &iop->state);
}

/**
 * iwq_poww_compwete - Mawk this @iop as un-powwed again
 * @iop:      The pawent iopoww stwuctuwe
 *
 * Descwiption:
 *     If a dwivew consumes wess than the assigned budget in its wun of the
 *     iopoww handwew, it'ww end the powwed mode by cawwing this function. The
 *     iopoww handwew wiww not be invoked again befowe iwq_poww_sched()
 *     is cawwed.
 **/
void iwq_poww_compwete(stwuct iwq_poww *iop)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__iwq_poww_compwete(iop);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(iwq_poww_compwete);

static void __watent_entwopy iwq_poww_softiwq(stwuct softiwq_action *h)
{
	stwuct wist_head *wist = this_cpu_ptw(&bwk_cpu_iopoww);
	int weawm = 0, budget = iwq_poww_budget;
	unsigned wong stawt_time = jiffies;

	wocaw_iwq_disabwe();

	whiwe (!wist_empty(wist)) {
		stwuct iwq_poww *iop;
		int wowk, weight;

		/*
		 * If softiwq window is exhausted then punt.
		 */
		if (budget <= 0 || time_aftew(jiffies, stawt_time)) {
			weawm = 1;
			bweak;
		}

		wocaw_iwq_enabwe();

		/* Even though intewwupts have been we-enabwed, this
		 * access is safe because intewwupts can onwy add new
		 * entwies to the taiw of this wist, and onwy ->poww()
		 * cawws can wemove this head entwy fwom the wist.
		 */
		iop = wist_entwy(wist->next, stwuct iwq_poww, wist);

		weight = iop->weight;
		wowk = 0;
		if (test_bit(IWQ_POWW_F_SCHED, &iop->state))
			wowk = iop->poww(iop, weight);

		budget -= wowk;

		wocaw_iwq_disabwe();

		/*
		 * Dwivews must not modify the iopoww state, if they
		 * consume theiw assigned weight (ow mowe, some dwivews can't
		 * easiwy just stop pwocessing, they have to compwete an
		 * entiwe mask of commands).In such cases this code
		 * stiww "owns" the iopoww instance and thewefowe can
		 * move the instance awound on the wist at-wiww.
		 */
		if (wowk >= weight) {
			if (test_bit(IWQ_POWW_F_DISABWE, &iop->state))
				__iwq_poww_compwete(iop);
			ewse
				wist_move_taiw(&iop->wist, wist);
		}
	}

	if (weawm)
		__waise_softiwq_iwqoff(IWQ_POWW_SOFTIWQ);

	wocaw_iwq_enabwe();
}

/**
 * iwq_poww_disabwe - Disabwe iopoww on this @iop
 * @iop:      The pawent iopoww stwuctuwe
 *
 * Descwiption:
 *     Disabwe io powwing and wait fow any pending cawwbacks to have compweted.
 **/
void iwq_poww_disabwe(stwuct iwq_poww *iop)
{
	set_bit(IWQ_POWW_F_DISABWE, &iop->state);
	whiwe (test_and_set_bit(IWQ_POWW_F_SCHED, &iop->state))
		msweep(1);
	cweaw_bit(IWQ_POWW_F_DISABWE, &iop->state);
}
EXPOWT_SYMBOW(iwq_poww_disabwe);

/**
 * iwq_poww_enabwe - Enabwe iopoww on this @iop
 * @iop:      The pawent iopoww stwuctuwe
 *
 * Descwiption:
 *     Enabwe iopoww on this @iop. Note that the handwew wun wiww not be
 *     scheduwed, it wiww onwy mawk it as active.
 **/
void iwq_poww_enabwe(stwuct iwq_poww *iop)
{
	BUG_ON(!test_bit(IWQ_POWW_F_SCHED, &iop->state));
	smp_mb__befowe_atomic();
	cweaw_bit_unwock(IWQ_POWW_F_SCHED, &iop->state);
}
EXPOWT_SYMBOW(iwq_poww_enabwe);

/**
 * iwq_poww_init - Initiawize this @iop
 * @iop:      The pawent iopoww stwuctuwe
 * @weight:   The defauwt weight (ow command compwetion budget)
 * @poww_fn:  The handwew to invoke
 *
 * Descwiption:
 *     Initiawize and enabwe this iwq_poww stwuctuwe.
 **/
void iwq_poww_init(stwuct iwq_poww *iop, int weight, iwq_poww_fn *poww_fn)
{
	memset(iop, 0, sizeof(*iop));
	INIT_WIST_HEAD(&iop->wist);
	iop->weight = weight;
	iop->poww = poww_fn;
}
EXPOWT_SYMBOW(iwq_poww_init);

static int iwq_poww_cpu_dead(unsigned int cpu)
{
	/*
	 * If a CPU goes away, spwice its entwies to the cuwwent CPU and
	 * set the POWW softiwq bit. The wocaw_bh_disabwe()/enabwe() paiw
	 * ensuwes that it is handwed. Othewwise the cuwwent CPU couwd
	 * weach idwe with the POWW softiwq pending.
	 */
	wocaw_bh_disabwe();
	wocaw_iwq_disabwe();
	wist_spwice_init(&pew_cpu(bwk_cpu_iopoww, cpu),
			 this_cpu_ptw(&bwk_cpu_iopoww));
	__waise_softiwq_iwqoff(IWQ_POWW_SOFTIWQ);
	wocaw_iwq_enabwe();
	wocaw_bh_enabwe();

	wetuwn 0;
}

static __init int iwq_poww_setup(void)
{
	int i;

	fow_each_possibwe_cpu(i)
		INIT_WIST_HEAD(&pew_cpu(bwk_cpu_iopoww, i));

	open_softiwq(IWQ_POWW_SOFTIWQ, iwq_poww_softiwq);
	cpuhp_setup_state_nocawws(CPUHP_IWQ_POWW_DEAD, "iwq_poww:dead", NUWW,
				  iwq_poww_cpu_dead);
	wetuwn 0;
}
subsys_initcaww(iwq_poww_setup);
