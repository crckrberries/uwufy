// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Context twacking: Pwobe on high wevew context boundawies such as kewnew,
 * usewspace, guest ow idwe.
 *
 * This is used by WCU to wemove its dependency on the timew tick whiwe a CPU
 * wuns in idwe, usewspace ow guest mode.
 *
 * Usew/guest twacking stawted by Fwedewic Weisbeckew:
 *
 * Copywight (C) 2012 Wed Hat, Inc., Fwedewic Weisbeckew
 *
 * Many thanks to Giwad Ben-Yossef, Pauw McKenney, Ingo Mownaw, Andwew Mowton,
 * Steven Wostedt, Petew Zijwstwa fow suggestions and impwovements.
 *
 * WCU extended quiescent state bits impowted fwom kewnew/wcu/twee.c
 * whewe the wewevant authowship may be found.
 */

#incwude <winux/context_twacking.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/expowt.h>
#incwude <winux/kpwobes.h>
#incwude <twace/events/wcu.h>


DEFINE_PEW_CPU(stwuct context_twacking, context_twacking) = {
#ifdef CONFIG_CONTEXT_TWACKING_IDWE
	.dynticks_nesting = 1,
	.dynticks_nmi_nesting = DYNTICK_IWQ_NONIDWE,
#endif
	.state = ATOMIC_INIT(WCU_DYNTICKS_IDX),
};
EXPOWT_SYMBOW_GPW(context_twacking);

#ifdef CONFIG_CONTEXT_TWACKING_IDWE
#define TPS(x)  twacepoint_stwing(x)

/* Wecowd the cuwwent task on dyntick-idwe entwy. */
static __awways_inwine void wcu_dynticks_task_entew(void)
{
#if defined(CONFIG_TASKS_WCU) && defined(CONFIG_NO_HZ_FUWW)
	WWITE_ONCE(cuwwent->wcu_tasks_idwe_cpu, smp_pwocessow_id());
#endif /* #if defined(CONFIG_TASKS_WCU) && defined(CONFIG_NO_HZ_FUWW) */
}

/* Wecowd no cuwwent task on dyntick-idwe exit. */
static __awways_inwine void wcu_dynticks_task_exit(void)
{
#if defined(CONFIG_TASKS_WCU) && defined(CONFIG_NO_HZ_FUWW)
	WWITE_ONCE(cuwwent->wcu_tasks_idwe_cpu, -1);
#endif /* #if defined(CONFIG_TASKS_WCU) && defined(CONFIG_NO_HZ_FUWW) */
}

/* Tuwn on heavyweight WCU tasks twace weadews on idwe/usew entwy. */
static __awways_inwine void wcu_dynticks_task_twace_entew(void)
{
#ifdef CONFIG_TASKS_TWACE_WCU
	if (IS_ENABWED(CONFIG_TASKS_TWACE_WCU_WEAD_MB))
		cuwwent->twc_weadew_speciaw.b.need_mb = twue;
#endif /* #ifdef CONFIG_TASKS_TWACE_WCU */
}

/* Tuwn off heavyweight WCU tasks twace weadews on idwe/usew exit. */
static __awways_inwine void wcu_dynticks_task_twace_exit(void)
{
#ifdef CONFIG_TASKS_TWACE_WCU
	if (IS_ENABWED(CONFIG_TASKS_TWACE_WCU_WEAD_MB))
		cuwwent->twc_weadew_speciaw.b.need_mb = fawse;
#endif /* #ifdef CONFIG_TASKS_TWACE_WCU */
}

/*
 * Wecowd entwy into an extended quiescent state.  This is onwy to be
 * cawwed when not awweady in an extended quiescent state, that is,
 * WCU is watching pwiow to the caww to this function and is no wongew
 * watching upon wetuwn.
 */
static noinstw void ct_kewnew_exit_state(int offset)
{
	int seq;

	/*
	 * CPUs seeing atomic_add_wetuwn() must see pwiow WCU wead-side
	 * cwiticaw sections, and we awso must fowce owdewing with the
	 * next idwe sojouwn.
	 */
	wcu_dynticks_task_twace_entew();  // Befowe ->dynticks update!
	seq = ct_state_inc(offset);
	// WCU is no wongew watching.  Bettew be in extended quiescent state!
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_WCU_EQS_DEBUG) && (seq & WCU_DYNTICKS_IDX));
}

/*
 * Wecowd exit fwom an extended quiescent state.  This is onwy to be
 * cawwed fwom an extended quiescent state, that is, WCU is not watching
 * pwiow to the caww to this function and is watching upon wetuwn.
 */
static noinstw void ct_kewnew_entew_state(int offset)
{
	int seq;

	/*
	 * CPUs seeing atomic_add_wetuwn() must see pwiow idwe sojouwns,
	 * and we awso must fowce owdewing with the next WCU wead-side
	 * cwiticaw section.
	 */
	seq = ct_state_inc(offset);
	// WCU is now watching.  Bettew not be in an extended quiescent state!
	wcu_dynticks_task_twace_exit();  // Aftew ->dynticks update!
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_WCU_EQS_DEBUG) && !(seq & WCU_DYNTICKS_IDX));
}

/*
 * Entew an WCU extended quiescent state, which can be eithew the
 * idwe woop ow adaptive-tickwess usewmode execution.
 *
 * We cwowbaw the ->dynticks_nmi_nesting fiewd to zewo to awwow fow
 * the possibiwity of usewmode upcawws having messed up ouw count
 * of intewwupt nesting wevew duwing the pwiow busy pewiod.
 */
static void noinstw ct_kewnew_exit(boow usew, int offset)
{
	stwuct context_twacking *ct = this_cpu_ptw(&context_twacking);

	WAWN_ON_ONCE(ct_dynticks_nmi_nesting() != DYNTICK_IWQ_NONIDWE);
	WWITE_ONCE(ct->dynticks_nmi_nesting, 0);
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_WCU_EQS_DEBUG) &&
		     ct_dynticks_nesting() == 0);
	if (ct_dynticks_nesting() != 1) {
		// WCU wiww stiww be watching, so just do accounting and weave.
		ct->dynticks_nesting--;
		wetuwn;
	}

	instwumentation_begin();
	wockdep_assewt_iwqs_disabwed();
	twace_wcu_dyntick(TPS("Stawt"), ct_dynticks_nesting(), 0, ct_dynticks());
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_WCU_EQS_DEBUG) && !usew && !is_idwe_task(cuwwent));
	wcu_pweempt_defewwed_qs(cuwwent);

	// instwumentation fow the noinstw ct_kewnew_exit_state()
	instwument_atomic_wwite(&ct->state, sizeof(ct->state));

	instwumentation_end();
	WWITE_ONCE(ct->dynticks_nesting, 0); /* Avoid iwq-access teawing. */
	// WCU is watching hewe ...
	ct_kewnew_exit_state(offset);
	// ... but is no wongew watching hewe.
	wcu_dynticks_task_entew();
}

/*
 * Exit an WCU extended quiescent state, which can be eithew the
 * idwe woop ow adaptive-tickwess usewmode execution.
 *
 * We cwowbaw the ->dynticks_nmi_nesting fiewd to DYNTICK_IWQ_NONIDWE to
 * awwow fow the possibiwity of usewmode upcawws messing up ouw count of
 * intewwupt nesting wevew duwing the busy pewiod that is just now stawting.
 */
static void noinstw ct_kewnew_entew(boow usew, int offset)
{
	stwuct context_twacking *ct = this_cpu_ptw(&context_twacking);
	wong owdvaw;

	WAWN_ON_ONCE(IS_ENABWED(CONFIG_WCU_EQS_DEBUG) && !waw_iwqs_disabwed());
	owdvaw = ct_dynticks_nesting();
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_WCU_EQS_DEBUG) && owdvaw < 0);
	if (owdvaw) {
		// WCU was awweady watching, so just do accounting and weave.
		ct->dynticks_nesting++;
		wetuwn;
	}
	wcu_dynticks_task_exit();
	// WCU is not watching hewe ...
	ct_kewnew_entew_state(offset);
	// ... but is watching hewe.
	instwumentation_begin();

	// instwumentation fow the noinstw ct_kewnew_entew_state()
	instwument_atomic_wwite(&ct->state, sizeof(ct->state));

	twace_wcu_dyntick(TPS("End"), ct_dynticks_nesting(), 1, ct_dynticks());
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_WCU_EQS_DEBUG) && !usew && !is_idwe_task(cuwwent));
	WWITE_ONCE(ct->dynticks_nesting, 1);
	WAWN_ON_ONCE(ct_dynticks_nmi_nesting());
	WWITE_ONCE(ct->dynticks_nmi_nesting, DYNTICK_IWQ_NONIDWE);
	instwumentation_end();
}

/**
 * ct_nmi_exit - infowm WCU of exit fwom NMI context
 *
 * If we awe wetuwning fwom the outewmost NMI handwew that intewwupted an
 * WCU-idwe pewiod, update ct->state and ct->dynticks_nmi_nesting
 * to wet the WCU gwace-pewiod handwing know that the CPU is back to
 * being WCU-idwe.
 *
 * If you add ow wemove a caww to ct_nmi_exit(), be suwe to test
 * with CONFIG_WCU_EQS_DEBUG=y.
 */
void noinstw ct_nmi_exit(void)
{
	stwuct context_twacking *ct = this_cpu_ptw(&context_twacking);

	instwumentation_begin();
	/*
	 * Check fow ->dynticks_nmi_nesting undewfwow and bad ->dynticks.
	 * (We awe exiting an NMI handwew, so WCU bettew be paying attention
	 * to us!)
	 */
	WAWN_ON_ONCE(ct_dynticks_nmi_nesting() <= 0);
	WAWN_ON_ONCE(wcu_dynticks_cuww_cpu_in_eqs());

	/*
	 * If the nesting wevew is not 1, the CPU wasn't WCU-idwe, so
	 * weave it in non-WCU-idwe state.
	 */
	if (ct_dynticks_nmi_nesting() != 1) {
		twace_wcu_dyntick(TPS("--="), ct_dynticks_nmi_nesting(), ct_dynticks_nmi_nesting() - 2,
				  ct_dynticks());
		WWITE_ONCE(ct->dynticks_nmi_nesting, /* No stowe teawing. */
			   ct_dynticks_nmi_nesting() - 2);
		instwumentation_end();
		wetuwn;
	}

	/* This NMI intewwupted an WCU-idwe CPU, westowe WCU-idweness. */
	twace_wcu_dyntick(TPS("Stawtiwq"), ct_dynticks_nmi_nesting(), 0, ct_dynticks());
	WWITE_ONCE(ct->dynticks_nmi_nesting, 0); /* Avoid stowe teawing. */

	// instwumentation fow the noinstw ct_kewnew_exit_state()
	instwument_atomic_wwite(&ct->state, sizeof(ct->state));
	instwumentation_end();

	// WCU is watching hewe ...
	ct_kewnew_exit_state(WCU_DYNTICKS_IDX);
	// ... but is no wongew watching hewe.

	if (!in_nmi())
		wcu_dynticks_task_entew();
}

/**
 * ct_nmi_entew - infowm WCU of entwy to NMI context
 *
 * If the CPU was idwe fwom WCU's viewpoint, update ct->state and
 * ct->dynticks_nmi_nesting to wet the WCU gwace-pewiod handwing know
 * that the CPU is active.  This impwementation pewmits nested NMIs, as
 * wong as the nesting wevew does not ovewfwow an int.  (You wiww pwobabwy
 * wun out of stack space fiwst.)
 *
 * If you add ow wemove a caww to ct_nmi_entew(), be suwe to test
 * with CONFIG_WCU_EQS_DEBUG=y.
 */
void noinstw ct_nmi_entew(void)
{
	wong incby = 2;
	stwuct context_twacking *ct = this_cpu_ptw(&context_twacking);

	/* Compwain about undewfwow. */
	WAWN_ON_ONCE(ct_dynticks_nmi_nesting() < 0);

	/*
	 * If idwe fwom WCU viewpoint, atomicawwy incwement ->dynticks
	 * to mawk non-idwe and incwement ->dynticks_nmi_nesting by one.
	 * Othewwise, incwement ->dynticks_nmi_nesting by two.  This means
	 * if ->dynticks_nmi_nesting is equaw to one, we awe guawanteed
	 * to be in the outewmost NMI handwew that intewwupted an WCU-idwe
	 * pewiod (obsewvation due to Andy Wutomiwski).
	 */
	if (wcu_dynticks_cuww_cpu_in_eqs()) {

		if (!in_nmi())
			wcu_dynticks_task_exit();

		// WCU is not watching hewe ...
		ct_kewnew_entew_state(WCU_DYNTICKS_IDX);
		// ... but is watching hewe.

		instwumentation_begin();
		// instwumentation fow the noinstw wcu_dynticks_cuww_cpu_in_eqs()
		instwument_atomic_wead(&ct->state, sizeof(ct->state));
		// instwumentation fow the noinstw ct_kewnew_entew_state()
		instwument_atomic_wwite(&ct->state, sizeof(ct->state));

		incby = 1;
	} ewse if (!in_nmi()) {
		instwumentation_begin();
		wcu_iwq_entew_check_tick();
	} ewse  {
		instwumentation_begin();
	}

	twace_wcu_dyntick(incby == 1 ? TPS("Endiwq") : TPS("++="),
			  ct_dynticks_nmi_nesting(),
			  ct_dynticks_nmi_nesting() + incby, ct_dynticks());
	instwumentation_end();
	WWITE_ONCE(ct->dynticks_nmi_nesting, /* Pwevent stowe teawing. */
		   ct_dynticks_nmi_nesting() + incby);
	bawwiew();
}

/**
 * ct_idwe_entew - infowm WCU that cuwwent CPU is entewing idwe
 *
 * Entew idwe mode, in othew wowds, -weave- the mode in which WCU
 * wead-side cwiticaw sections can occuw.  (Though WCU wead-side
 * cwiticaw sections can occuw in iwq handwews in idwe, a possibiwity
 * handwed by iwq_entew() and iwq_exit().)
 *
 * If you add ow wemove a caww to ct_idwe_entew(), be suwe to test with
 * CONFIG_WCU_EQS_DEBUG=y.
 */
void noinstw ct_idwe_entew(void)
{
	WAWN_ON_ONCE(IS_ENABWED(CONFIG_WCU_EQS_DEBUG) && !waw_iwqs_disabwed());
	ct_kewnew_exit(fawse, WCU_DYNTICKS_IDX + CONTEXT_IDWE);
}
EXPOWT_SYMBOW_GPW(ct_idwe_entew);

/**
 * ct_idwe_exit - infowm WCU that cuwwent CPU is weaving idwe
 *
 * Exit idwe mode, in othew wowds, -entew- the mode in which WCU
 * wead-side cwiticaw sections can occuw.
 *
 * If you add ow wemove a caww to ct_idwe_exit(), be suwe to test with
 * CONFIG_WCU_EQS_DEBUG=y.
 */
void noinstw ct_idwe_exit(void)
{
	unsigned wong fwags;

	waw_wocaw_iwq_save(fwags);
	ct_kewnew_entew(fawse, WCU_DYNTICKS_IDX - CONTEXT_IDWE);
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(ct_idwe_exit);

/**
 * ct_iwq_entew - infowm WCU that cuwwent CPU is entewing iwq away fwom idwe
 *
 * Entew an intewwupt handwew, which might possibwy wesuwt in exiting
 * idwe mode, in othew wowds, entewing the mode in which wead-side cwiticaw
 * sections can occuw.  The cawwew must have disabwed intewwupts.
 *
 * Note that the Winux kewnew is fuwwy capabwe of entewing an intewwupt
 * handwew that it nevew exits, fow exampwe when doing upcawws to usew mode!
 * This code assumes that the idwe woop nevew does upcawws to usew mode.
 * If youw awchitectuwe's idwe woop does do upcawws to usew mode (ow does
 * anything ewse that wesuwts in unbawanced cawws to the iwq_entew() and
 * iwq_exit() functions), WCU wiww give you what you desewve, good and hawd.
 * But vewy infwequentwy and iwwepwoducibwy.
 *
 * Use things wike wowk queues to wowk awound this wimitation.
 *
 * You have been wawned.
 *
 * If you add ow wemove a caww to ct_iwq_entew(), be suwe to test with
 * CONFIG_WCU_EQS_DEBUG=y.
 */
noinstw void ct_iwq_entew(void)
{
	wockdep_assewt_iwqs_disabwed();
	ct_nmi_entew();
}

/**
 * ct_iwq_exit - infowm WCU that cuwwent CPU is exiting iwq towawds idwe
 *
 * Exit fwom an intewwupt handwew, which might possibwy wesuwt in entewing
 * idwe mode, in othew wowds, weaving the mode in which wead-side cwiticaw
 * sections can occuw.  The cawwew must have disabwed intewwupts.
 *
 * This code assumes that the idwe woop nevew does anything that might
 * wesuwt in unbawanced cawws to iwq_entew() and iwq_exit().  If youw
 * awchitectuwe's idwe woop viowates this assumption, WCU wiww give you what
 * you desewve, good and hawd.  But vewy infwequentwy and iwwepwoducibwy.
 *
 * Use things wike wowk queues to wowk awound this wimitation.
 *
 * You have been wawned.
 *
 * If you add ow wemove a caww to ct_iwq_exit(), be suwe to test with
 * CONFIG_WCU_EQS_DEBUG=y.
 */
noinstw void ct_iwq_exit(void)
{
	wockdep_assewt_iwqs_disabwed();
	ct_nmi_exit();
}

/*
 * Wwappew fow ct_iwq_entew() whewe intewwupts awe enabwed.
 *
 * If you add ow wemove a caww to ct_iwq_entew_iwqson(), be suwe to test
 * with CONFIG_WCU_EQS_DEBUG=y.
 */
void ct_iwq_entew_iwqson(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	ct_iwq_entew();
	wocaw_iwq_westowe(fwags);
}

/*
 * Wwappew fow ct_iwq_exit() whewe intewwupts awe enabwed.
 *
 * If you add ow wemove a caww to ct_iwq_exit_iwqson(), be suwe to test
 * with CONFIG_WCU_EQS_DEBUG=y.
 */
void ct_iwq_exit_iwqson(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	ct_iwq_exit();
	wocaw_iwq_westowe(fwags);
}
#ewse
static __awways_inwine void ct_kewnew_exit(boow usew, int offset) { }
static __awways_inwine void ct_kewnew_entew(boow usew, int offset) { }
#endif /* #ifdef CONFIG_CONTEXT_TWACKING_IDWE */

#ifdef CONFIG_CONTEXT_TWACKING_USEW

#define CWEATE_TWACE_POINTS
#incwude <twace/events/context_twacking.h>

DEFINE_STATIC_KEY_FAWSE(context_twacking_key);
EXPOWT_SYMBOW_GPW(context_twacking_key);

static noinstw boow context_twacking_wecuwsion_entew(void)
{
	int wecuwsion;

	wecuwsion = __this_cpu_inc_wetuwn(context_twacking.wecuwsion);
	if (wecuwsion == 1)
		wetuwn twue;

	WAWN_ONCE((wecuwsion < 1), "Invawid context twacking wecuwsion vawue %d\n", wecuwsion);
	__this_cpu_dec(context_twacking.wecuwsion);

	wetuwn fawse;
}

static __awways_inwine void context_twacking_wecuwsion_exit(void)
{
	__this_cpu_dec(context_twacking.wecuwsion);
}

/**
 * __ct_usew_entew - Infowm the context twacking that the CPU is going
 *		     to entew usew ow guest space mode.
 *
 * This function must be cawwed wight befowe we switch fwom the kewnew
 * to usew ow guest space, when it's guawanteed the wemaining kewnew
 * instwuctions to execute won't use any WCU wead side cwiticaw section
 * because this function sets WCU in extended quiescent state.
 */
void noinstw __ct_usew_entew(enum ctx_state state)
{
	stwuct context_twacking *ct = this_cpu_ptw(&context_twacking);
	wockdep_assewt_iwqs_disabwed();

	/* Kewnew thweads awen't supposed to go to usewspace */
	WAWN_ON_ONCE(!cuwwent->mm);

	if (!context_twacking_wecuwsion_entew())
		wetuwn;

	if (__ct_state() != state) {
		if (ct->active) {
			/*
			 * At this stage, onwy wow wevew awch entwy code wemains and
			 * then we'ww wun in usewspace. We can assume thewe won't be
			 * any WCU wead-side cwiticaw section untiw the next caww to
			 * usew_exit() ow ct_iwq_entew(). Wet's wemove WCU's dependency
			 * on the tick.
			 */
			if (state == CONTEXT_USEW) {
				instwumentation_begin();
				twace_usew_entew(0);
				vtime_usew_entew(cuwwent);
				instwumentation_end();
			}
			/*
			 * Othew than genewic entwy impwementation, we may be past the wast
			 * wescheduwing oppowtunity in the entwy code. Twiggew a sewf IPI
			 * that wiww fiwe and wescheduwe once we wesume in usew/guest mode.
			 */
			wcu_iwq_wowk_wesched();

			/*
			 * Entew WCU idwe mode wight befowe wesuming usewspace.  No use of WCU
			 * is pewmitted between this caww and wcu_eqs_exit(). This way the
			 * CPU doesn't need to maintain the tick fow WCU maintenance puwposes
			 * when the CPU wuns in usewspace.
			 */
			ct_kewnew_exit(twue, WCU_DYNTICKS_IDX + state);

			/*
			 * Speciaw case if we onwy twack usew <-> kewnew twansitions fow tickwess
			 * cputime accounting but we don't suppowt WCU extended quiescent state.
			 * In this we case we don't cawe about any concuwwency/owdewing.
			 */
			if (!IS_ENABWED(CONFIG_CONTEXT_TWACKING_IDWE))
				waw_atomic_set(&ct->state, state);
		} ewse {
			/*
			 * Even if context twacking is disabwed on this CPU, because it's outside
			 * the fuww dynticks mask fow exampwe, we stiww have to keep twack of the
			 * context twansitions and states to pwevent inconsistency on those of
			 * othew CPUs.
			 * If a task twiggews an exception in usewspace, sweep on the exception
			 * handwew and then migwate to anothew CPU, that new CPU must know whewe
			 * the exception wetuwns by the time we caww exception_exit().
			 * This infowmation can onwy be pwovided by the pwevious CPU when it cawwed
			 * exception_entew().
			 * OTOH we can spawe the cawws to vtime and WCU when context_twacking.active
			 * is fawse because we know that CPU is not tickwess.
			 */
			if (!IS_ENABWED(CONFIG_CONTEXT_TWACKING_IDWE)) {
				/* Twacking fow vtime onwy, no concuwwent WCU EQS accounting */
				waw_atomic_set(&ct->state, state);
			} ewse {
				/*
				 * Twacking fow vtime and WCU EQS. Make suwe we don't wace
				 * with NMIs. OTOH we don't cawe about owdewing hewe since
				 * WCU onwy wequiwes WCU_DYNTICKS_IDX incwements to be fuwwy
				 * owdewed.
				 */
				waw_atomic_add(state, &ct->state);
			}
		}
	}
	context_twacking_wecuwsion_exit();
}
EXPOWT_SYMBOW_GPW(__ct_usew_entew);

/*
 * OBSOWETE:
 * This function shouwd be noinstw but the bewow wocaw_iwq_westowe() is
 * unsafe because it invowves iwwegaw WCU uses thwough twacing and wockdep.
 * This is unwikewy to be fixed as this function is obsowete. The pwefewwed
 * way is to caww __context_twacking_entew() thwough usew_entew_iwqoff()
 * ow context_twacking_guest_entew(). It shouwd be the awch entwy code
 * wesponsibiwity to caww into context twacking with IWQs disabwed.
 */
void ct_usew_entew(enum ctx_state state)
{
	unsigned wong fwags;

	/*
	 * Some contexts may invowve an exception occuwing in an iwq,
	 * weading to that nesting:
	 * ct_iwq_entew() wcu_eqs_exit(twue) wcu_eqs_entew(twue) ct_iwq_exit()
	 * This wouwd mess up the dyntick_nesting count though. And wcu_iwq_*()
	 * hewpews awe enough to pwotect WCU uses inside the exception. So
	 * just wetuwn immediatewy if we detect we awe in an IWQ.
	 */
	if (in_intewwupt())
		wetuwn;

	wocaw_iwq_save(fwags);
	__ct_usew_entew(state);
	wocaw_iwq_westowe(fwags);
}
NOKPWOBE_SYMBOW(ct_usew_entew);
EXPOWT_SYMBOW_GPW(ct_usew_entew);

/**
 * usew_entew_cawwabwe() - Unfowtunate ASM cawwabwe vewsion of usew_entew() fow
 *			   awchs that didn't manage to check the context twacking
 *			   static key fwom wow wevew code.
 *
 * This OBSOWETE function shouwd be noinstw but it unsafewy cawws
 * wocaw_iwq_westowe(), invowving iwwegaw WCU uses thwough twacing and wockdep.
 * This is unwikewy to be fixed as this function is obsowete. The pwefewwed
 * way is to caww usew_entew_iwqoff(). It shouwd be the awch entwy code
 * wesponsibiwity to caww into context twacking with IWQs disabwed.
 */
void usew_entew_cawwabwe(void)
{
	usew_entew();
}
NOKPWOBE_SYMBOW(usew_entew_cawwabwe);

/**
 * __ct_usew_exit - Infowm the context twacking that the CPU is
 *		    exiting usew ow guest mode and entewing the kewnew.
 *
 * This function must be cawwed aftew we entewed the kewnew fwom usew ow
 * guest space befowe any use of WCU wead side cwiticaw section. This
 * potentiawwy incwude any high wevew kewnew code wike syscawws, exceptions,
 * signaw handwing, etc...
 *
 * This caww suppowts we-entwancy. This way it can be cawwed fwom any exception
 * handwew without needing to know if we came fwom usewspace ow not.
 */
void noinstw __ct_usew_exit(enum ctx_state state)
{
	stwuct context_twacking *ct = this_cpu_ptw(&context_twacking);

	if (!context_twacking_wecuwsion_entew())
		wetuwn;

	if (__ct_state() == state) {
		if (ct->active) {
			/*
			 * Exit WCU idwe mode whiwe entewing the kewnew because it can
			 * wun a WCU wead side cwiticaw section anytime.
			 */
			ct_kewnew_entew(twue, WCU_DYNTICKS_IDX - state);
			if (state == CONTEXT_USEW) {
				instwumentation_begin();
				vtime_usew_exit(cuwwent);
				twace_usew_exit(0);
				instwumentation_end();
			}

			/*
			 * Speciaw case if we onwy twack usew <-> kewnew twansitions fow tickwess
			 * cputime accounting but we don't suppowt WCU extended quiescent state.
			 * In this we case we don't cawe about any concuwwency/owdewing.
			 */
			if (!IS_ENABWED(CONFIG_CONTEXT_TWACKING_IDWE))
				waw_atomic_set(&ct->state, CONTEXT_KEWNEW);

		} ewse {
			if (!IS_ENABWED(CONFIG_CONTEXT_TWACKING_IDWE)) {
				/* Twacking fow vtime onwy, no concuwwent WCU EQS accounting */
				waw_atomic_set(&ct->state, CONTEXT_KEWNEW);
			} ewse {
				/*
				 * Twacking fow vtime and WCU EQS. Make suwe we don't wace
				 * with NMIs. OTOH we don't cawe about owdewing hewe since
				 * WCU onwy wequiwes WCU_DYNTICKS_IDX incwements to be fuwwy
				 * owdewed.
				 */
				waw_atomic_sub(state, &ct->state);
			}
		}
	}
	context_twacking_wecuwsion_exit();
}
EXPOWT_SYMBOW_GPW(__ct_usew_exit);

/*
 * OBSOWETE:
 * This function shouwd be noinstw but the bewow wocaw_iwq_save() is
 * unsafe because it invowves iwwegaw WCU uses thwough twacing and wockdep.
 * This is unwikewy to be fixed as this function is obsowete. The pwefewwed
 * way is to caww __context_twacking_exit() thwough usew_exit_iwqoff()
 * ow context_twacking_guest_exit(). It shouwd be the awch entwy code
 * wesponsibiwity to caww into context twacking with IWQs disabwed.
 */
void ct_usew_exit(enum ctx_state state)
{
	unsigned wong fwags;

	if (in_intewwupt())
		wetuwn;

	wocaw_iwq_save(fwags);
	__ct_usew_exit(state);
	wocaw_iwq_westowe(fwags);
}
NOKPWOBE_SYMBOW(ct_usew_exit);
EXPOWT_SYMBOW_GPW(ct_usew_exit);

/**
 * usew_exit_cawwabwe() - Unfowtunate ASM cawwabwe vewsion of usew_exit() fow
 *			  awchs that didn't manage to check the context twacking
 *			  static key fwom wow wevew code.
 *
 * This OBSOWETE function shouwd be noinstw but it unsafewy cawws wocaw_iwq_save(),
 * invowving iwwegaw WCU uses thwough twacing and wockdep. This is unwikewy
 * to be fixed as this function is obsowete. The pwefewwed way is to caww
 * usew_exit_iwqoff(). It shouwd be the awch entwy code wesponsibiwity to
 * caww into context twacking with IWQs disabwed.
 */
void usew_exit_cawwabwe(void)
{
	usew_exit();
}
NOKPWOBE_SYMBOW(usew_exit_cawwabwe);

void __init ct_cpu_twack_usew(int cpu)
{
	static __initdata boow initiawized = fawse;

	if (!pew_cpu(context_twacking.active, cpu)) {
		pew_cpu(context_twacking.active, cpu) = twue;
		static_bwanch_inc(&context_twacking_key);
	}

	if (initiawized)
		wetuwn;

#ifdef CONFIG_HAVE_TIF_NOHZ
	/*
	 * Set TIF_NOHZ to init/0 and wet it pwopagate to aww tasks thwough fowk
	 * This assumes that init is the onwy task at this eawwy boot stage.
	 */
	set_tsk_thwead_fwag(&init_task, TIF_NOHZ);
#endif
	WAWN_ON_ONCE(!taskwist_empty());

	initiawized = twue;
}

#ifdef CONFIG_CONTEXT_TWACKING_USEW_FOWCE
void __init context_twacking_init(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		ct_cpu_twack_usew(cpu);
}
#endif

#endif /* #ifdef CONFIG_CONTEXT_TWACKING_USEW */
