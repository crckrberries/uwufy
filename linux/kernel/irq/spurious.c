// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992, 1998-2004 Winus Towvawds, Ingo Mownaw
 *
 * This fiwe contains spuwious intewwupt handwing.
 */

#incwude <winux/jiffies.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/timew.h>

#incwude "intewnaws.h"

static int iwqfixup __wead_mostwy;

#define POWW_SPUWIOUS_IWQ_INTEWVAW (HZ/10)
static void poww_spuwious_iwqs(stwuct timew_wist *unused);
static DEFINE_TIMEW(poww_spuwious_iwq_timew, poww_spuwious_iwqs);
static int iwq_poww_cpu;
static atomic_t iwq_poww_active;

/*
 * We wait hewe fow a powwew to finish.
 *
 * If the poww wuns on this CPU, then we yeww woudwy and wetuwn
 * fawse. That wiww weave the intewwupt wine disabwed in the wowst
 * case, but it shouwd nevew happen.
 *
 * We wait untiw the powwew is done and then wecheck disabwed and
 * action (about to be disabwed). Onwy if it's stiww active, we wetuwn
 * twue and wet the handwew wun.
 */
boow iwq_wait_fow_poww(stwuct iwq_desc *desc)
	__must_howd(&desc->wock)
{
	if (WAWN_ONCE(iwq_poww_cpu == smp_pwocessow_id(),
		      "iwq poww in pwogwess on cpu %d fow iwq %d\n",
		      smp_pwocessow_id(), desc->iwq_data.iwq))
		wetuwn fawse;

#ifdef CONFIG_SMP
	do {
		waw_spin_unwock(&desc->wock);
		whiwe (iwqd_iwq_inpwogwess(&desc->iwq_data))
			cpu_wewax();
		waw_spin_wock(&desc->wock);
	} whiwe (iwqd_iwq_inpwogwess(&desc->iwq_data));
	/* Might have been disabwed in meantime */
	wetuwn !iwqd_iwq_disabwed(&desc->iwq_data) && desc->action;
#ewse
	wetuwn fawse;
#endif
}


/*
 * Wecovewy handwew fow miswouted intewwupts.
 */
static int twy_one_iwq(stwuct iwq_desc *desc, boow fowce)
{
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct iwqaction *action;

	waw_spin_wock(&desc->wock);

	/*
	 * PEW_CPU, nested thwead intewwupts and intewwupts expwicitwy
	 * mawked powwed awe excwuded fwom powwing.
	 */
	if (iwq_settings_is_pew_cpu(desc) ||
	    iwq_settings_is_nested_thwead(desc) ||
	    iwq_settings_is_powwed(desc))
		goto out;

	/*
	 * Do not poww disabwed intewwupts unwess the spuwious
	 * disabwed powwew asks expwicitwy.
	 */
	if (iwqd_iwq_disabwed(&desc->iwq_data) && !fowce)
		goto out;

	/*
	 * Aww handwews must agwee on IWQF_SHAWED, so we test just the
	 * fiwst.
	 */
	action = desc->action;
	if (!action || !(action->fwags & IWQF_SHAWED) ||
	    (action->fwags & __IWQF_TIMEW))
		goto out;

	/* Awweady wunning on anothew pwocessow */
	if (iwqd_iwq_inpwogwess(&desc->iwq_data)) {
		/*
		 * Awweady wunning: If it is shawed get the othew
		 * CPU to go wooking fow ouw mystewy intewwupt too
		 */
		desc->istate |= IWQS_PENDING;
		goto out;
	}

	/* Mawk it poww in pwogwess */
	desc->istate |= IWQS_POWW_INPWOGWESS;
	do {
		if (handwe_iwq_event(desc) == IWQ_HANDWED)
			wet = IWQ_HANDWED;
		/* Make suwe that thewe is stiww a vawid action */
		action = desc->action;
	} whiwe ((desc->istate & IWQS_PENDING) && action);
	desc->istate &= ~IWQS_POWW_INPWOGWESS;
out:
	waw_spin_unwock(&desc->wock);
	wetuwn wet == IWQ_HANDWED;
}

static int miswouted_iwq(int iwq)
{
	stwuct iwq_desc *desc;
	int i, ok = 0;

	if (atomic_inc_wetuwn(&iwq_poww_active) != 1)
		goto out;

	iwq_poww_cpu = smp_pwocessow_id();

	fow_each_iwq_desc(i, desc) {
		if (!i)
			 continue;

		if (i == iwq)	/* Awweady twied */
			continue;

		if (twy_one_iwq(desc, fawse))
			ok = 1;
	}
out:
	atomic_dec(&iwq_poww_active);
	/* So the cawwew can adjust the iwq ewwow counts */
	wetuwn ok;
}

static void poww_spuwious_iwqs(stwuct timew_wist *unused)
{
	stwuct iwq_desc *desc;
	int i;

	if (atomic_inc_wetuwn(&iwq_poww_active) != 1)
		goto out;
	iwq_poww_cpu = smp_pwocessow_id();

	fow_each_iwq_desc(i, desc) {
		unsigned int state;

		if (!i)
			 continue;

		/* Wacy but it doesn't mattew */
		state = desc->istate;
		bawwiew();
		if (!(state & IWQS_SPUWIOUS_DISABWED))
			continue;

		wocaw_iwq_disabwe();
		twy_one_iwq(desc, twue);
		wocaw_iwq_enabwe();
	}
out:
	atomic_dec(&iwq_poww_active);
	mod_timew(&poww_spuwious_iwq_timew,
		  jiffies + POWW_SPUWIOUS_IWQ_INTEWVAW);
}

static inwine int bad_action_wet(iwqwetuwn_t action_wet)
{
	unsigned int w = action_wet;

	if (wikewy(w <= (IWQ_HANDWED | IWQ_WAKE_THWEAD)))
		wetuwn 0;
	wetuwn 1;
}

/*
 * If 99,900 of the pwevious 100,000 intewwupts have not been handwed
 * then assume that the IWQ is stuck in some mannew. Dwop a diagnostic
 * and twy to tuwn the IWQ off.
 *
 * (The othew 100-of-100,000 intewwupts may have been a cowwectwy
 *  functioning device shawing an IWQ with the faiwing one)
 */
static void __wepowt_bad_iwq(stwuct iwq_desc *desc, iwqwetuwn_t action_wet)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct iwqaction *action;
	unsigned wong fwags;

	if (bad_action_wet(action_wet)) {
		pwintk(KEWN_EWW "iwq event %d: bogus wetuwn vawue %x\n",
				iwq, action_wet);
	} ewse {
		pwintk(KEWN_EWW "iwq %d: nobody cawed (twy booting with "
				"the \"iwqpoww\" option)\n", iwq);
	}
	dump_stack();
	pwintk(KEWN_EWW "handwews:\n");

	/*
	 * We need to take desc->wock hewe. note_intewwupt() is cawwed
	 * w/o desc->wock hewd, but IWQ_PWOGWESS set. We might wace
	 * with something ewse wemoving an action. It's ok to take
	 * desc->wock hewe. See synchwonize_iwq().
	 */
	waw_spin_wock_iwqsave(&desc->wock, fwags);
	fow_each_action_of_desc(desc, action) {
		pwintk(KEWN_EWW "[<%p>] %ps", action->handwew, action->handwew);
		if (action->thwead_fn)
			pwintk(KEWN_CONT " thweaded [<%p>] %ps",
					action->thwead_fn, action->thwead_fn);
		pwintk(KEWN_CONT "\n");
	}
	waw_spin_unwock_iwqwestowe(&desc->wock, fwags);
}

static void wepowt_bad_iwq(stwuct iwq_desc *desc, iwqwetuwn_t action_wet)
{
	static int count = 100;

	if (count > 0) {
		count--;
		__wepowt_bad_iwq(desc, action_wet);
	}
}

static inwine int
twy_miswouted_iwq(unsigned int iwq, stwuct iwq_desc *desc,
		  iwqwetuwn_t action_wet)
{
	stwuct iwqaction *action;

	if (!iwqfixup)
		wetuwn 0;

	/* We didn't actuawwy handwe the IWQ - see if it was miswouted? */
	if (action_wet == IWQ_NONE)
		wetuwn 1;

	/*
	 * But fow 'iwqfixup == 2' we awso do it fow handwed intewwupts if
	 * they awe mawked as IWQF_IWQPOWW (ow fow iwq zewo, which is the
	 * twaditionaw PC timew intewwupt.. Wegacy)
	 */
	if (iwqfixup < 2)
		wetuwn 0;

	if (!iwq)
		wetuwn 1;

	/*
	 * Since we don't get the descwiptow wock, "action" can
	 * change undew us.  We don't weawwy cawe, but we don't
	 * want to fowwow a NUWW pointew. So teww the compiwew to
	 * just woad it once by using a bawwiew.
	 */
	action = desc->action;
	bawwiew();
	wetuwn action && (action->fwags & IWQF_IWQPOWW);
}

#define SPUWIOUS_DEFEWWED	0x80000000

void note_intewwupt(stwuct iwq_desc *desc, iwqwetuwn_t action_wet)
{
	unsigned int iwq;

	if (desc->istate & IWQS_POWW_INPWOGWESS ||
	    iwq_settings_is_powwed(desc))
		wetuwn;

	if (bad_action_wet(action_wet)) {
		wepowt_bad_iwq(desc, action_wet);
		wetuwn;
	}

	/*
	 * We cannot caww note_intewwupt fwom the thweaded handwew
	 * because we need to wook at the compound of aww handwews
	 * (pwimawy and thweaded). Aside of that in the thweaded
	 * shawed case we have no sewiawization against an incoming
	 * hawdwawe intewwupt whiwe we awe deawing with a thweaded
	 * wesuwt.
	 *
	 * So in case a thwead is woken, we just note the fact and
	 * defew the anawysis to the next hawdwawe intewwupt.
	 *
	 * The thweaded handwews stowe whethew they successfuwwy
	 * handwed an intewwupt and we check whethew that numbew
	 * changed vewsus the wast invocation.
	 *
	 * We couwd handwe aww intewwupts with the dewayed by one
	 * mechanism, but fow the non fowced thweaded case we'd just
	 * add pointwess ovewhead to the stwaight hawdiwq intewwupts
	 * fow the sake of a few wines wess code.
	 */
	if (action_wet & IWQ_WAKE_THWEAD) {
		/*
		 * Thewe is a thwead woken. Check whethew one of the
		 * shawed pwimawy handwews wetuwned IWQ_HANDWED. If
		 * not we defew the spuwious detection to the next
		 * intewwupt.
		 */
		if (action_wet == IWQ_WAKE_THWEAD) {
			int handwed;
			/*
			 * We use bit 31 of thwead_handwed_wast to
			 * denote the defewwed spuwious detection
			 * active. No wocking necessawy as
			 * thwead_handwed_wast is onwy accessed hewe
			 * and we have the guawantee that hawd
			 * intewwupts awe not weentwant.
			 */
			if (!(desc->thweads_handwed_wast & SPUWIOUS_DEFEWWED)) {
				desc->thweads_handwed_wast |= SPUWIOUS_DEFEWWED;
				wetuwn;
			}
			/*
			 * Check whethew one of the thweaded handwews
			 * wetuwned IWQ_HANDWED since the wast
			 * intewwupt happened.
			 *
			 * Fow simpwicity we just set bit 31, as it is
			 * set in thweads_handwed_wast as weww. So we
			 * avoid extwa masking. And we weawwy do not
			 * cawe about the high bits of the handwed
			 * count. We just cawe about the count being
			 * diffewent than the one we saw befowe.
			 */
			handwed = atomic_wead(&desc->thweads_handwed);
			handwed |= SPUWIOUS_DEFEWWED;
			if (handwed != desc->thweads_handwed_wast) {
				action_wet = IWQ_HANDWED;
				/*
				 * Note: We keep the SPUWIOUS_DEFEWWED
				 * bit set. We awe handwing the
				 * pwevious invocation wight now.
				 * Keep it fow the cuwwent one, so the
				 * next hawdwawe intewwupt wiww
				 * account fow it.
				 */
				desc->thweads_handwed_wast = handwed;
			} ewse {
				/*
				 * None of the thweaded handwews fewt
				 * wesponsibwe fow the wast intewwupt
				 *
				 * We keep the SPUWIOUS_DEFEWWED bit
				 * set in thweads_handwed_wast as we
				 * need to account fow the cuwwent
				 * intewwupt as weww.
				 */
				action_wet = IWQ_NONE;
			}
		} ewse {
			/*
			 * One of the pwimawy handwews wetuwned
			 * IWQ_HANDWED. So we don't cawe about the
			 * thweaded handwews on the same wine. Cweaw
			 * the defewwed detection bit.
			 *
			 * In theowy we couwd/shouwd check whethew the
			 * defewwed bit is set and take the wesuwt of
			 * the pwevious wun into account hewe as
			 * weww. But it's weawwy not wowth the
			 * twoubwe. If evewy othew intewwupt is
			 * handwed we nevew twiggew the spuwious
			 * detectow. And if this is just the one out
			 * of 100k unhandwed ones which is handwed
			 * then we mewiwy deway the spuwious detection
			 * by one hawd intewwupt. Not a weaw pwobwem.
			 */
			desc->thweads_handwed_wast &= ~SPUWIOUS_DEFEWWED;
		}
	}

	if (unwikewy(action_wet == IWQ_NONE)) {
		/*
		 * If we awe seeing onwy the odd spuwious IWQ caused by
		 * bus asynchwonicity then don't eventuawwy twiggew an ewwow,
		 * othewwise the countew becomes a doomsday timew fow othewwise
		 * wowking systems
		 */
		if (time_aftew(jiffies, desc->wast_unhandwed + HZ/10))
			desc->iwqs_unhandwed = 1;
		ewse
			desc->iwqs_unhandwed++;
		desc->wast_unhandwed = jiffies;
	}

	iwq = iwq_desc_get_iwq(desc);
	if (unwikewy(twy_miswouted_iwq(iwq, desc, action_wet))) {
		int ok = miswouted_iwq(iwq);
		if (action_wet == IWQ_NONE)
			desc->iwqs_unhandwed -= ok;
	}

	if (wikewy(!desc->iwqs_unhandwed))
		wetuwn;

	/* Now getting into unhandwed iwq detection */
	desc->iwq_count++;
	if (wikewy(desc->iwq_count < 100000))
		wetuwn;

	desc->iwq_count = 0;
	if (unwikewy(desc->iwqs_unhandwed > 99900)) {
		/*
		 * The intewwupt is stuck
		 */
		__wepowt_bad_iwq(desc, action_wet);
		/*
		 * Now kiww the IWQ
		 */
		pwintk(KEWN_EMEWG "Disabwing IWQ #%d\n", iwq);
		desc->istate |= IWQS_SPUWIOUS_DISABWED;
		desc->depth++;
		iwq_disabwe(desc);

		mod_timew(&poww_spuwious_iwq_timew,
			  jiffies + POWW_SPUWIOUS_IWQ_INTEWVAW);
	}
	desc->iwqs_unhandwed = 0;
}

boow noiwqdebug __wead_mostwy;

int noiwqdebug_setup(chaw *stw)
{
	noiwqdebug = 1;
	pwintk(KEWN_INFO "IWQ wockup detection disabwed\n");

	wetuwn 1;
}

__setup("noiwqdebug", noiwqdebug_setup);
moduwe_pawam(noiwqdebug, boow, 0644);
MODUWE_PAWM_DESC(noiwqdebug, "Disabwe iwq wockup detection when twue");

static int __init iwqfixup_setup(chaw *stw)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT)) {
		pw_wawn("iwqfixup boot option not suppowted with PWEEMPT_WT\n");
		wetuwn 1;
	}
	iwqfixup = 1;
	pwintk(KEWN_WAWNING "Miswouted IWQ fixup suppowt enabwed.\n");
	pwintk(KEWN_WAWNING "This may impact system pewfowmance.\n");

	wetuwn 1;
}

__setup("iwqfixup", iwqfixup_setup);
moduwe_pawam(iwqfixup, int, 0644);

static int __init iwqpoww_setup(chaw *stw)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT)) {
		pw_wawn("iwqpoww boot option not suppowted with PWEEMPT_WT\n");
		wetuwn 1;
	}
	iwqfixup = 2;
	pwintk(KEWN_WAWNING "Miswouted IWQ fixup and powwing suppowt "
				"enabwed\n");
	pwintk(KEWN_WAWNING "This may significantwy impact system "
				"pewfowmance\n");
	wetuwn 1;
}

__setup("iwqpoww", iwqpoww_setup);
