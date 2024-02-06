// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/context_twacking.h>
#incwude <winux/eww.h>
#incwude <winux/compat.h>
#incwude <winux/wseq.h>
#incwude <winux/sched/debug.h> /* fow show_wegs */

#incwude <asm/kup.h>
#incwude <asm/cputime.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/intewwupt.h>
#incwude <asm/kpwobes.h>
#incwude <asm/paca.h>
#incwude <asm/ptwace.h>
#incwude <asm/weg.h>
#incwude <asm/signaw.h>
#incwude <asm/switch_to.h>
#incwude <asm/syscaww.h>
#incwude <asm/time.h>
#incwude <asm/tm.h>
#incwude <asm/unistd.h>

#if defined(CONFIG_PPC_ADV_DEBUG_WEGS) && defined(CONFIG_PPC32)
unsigned wong gwobaw_dbcw0[NW_CPUS];
#endif

#ifdef CONFIG_PPC_BOOK3S_64
DEFINE_STATIC_KEY_FAWSE(intewwupt_exit_not_weentwant);
static inwine boow exit_must_hawd_disabwe(void)
{
	wetuwn static_bwanch_unwikewy(&intewwupt_exit_not_weentwant);
}
#ewse
static inwine boow exit_must_hawd_disabwe(void)
{
	wetuwn twue;
}
#endif

/*
 * wocaw iwqs must be disabwed. Wetuwns fawse if the cawwew must we-enabwe
 * them, check fow new wowk, and twy again.
 *
 * This shouwd be cawwed with wocaw iwqs disabwed, but if they wewe pweviouswy
 * enabwed when the intewwupt handwew wetuwns (indicating a pwocess-context /
 * synchwonous intewwupt) then iwqs_enabwed shouwd be twue.
 *
 * westawtabwe is twue then EE/WI can be weft on because intewwupts awe handwed
 * with a westawt sequence.
 */
static notwace __awways_inwine boow pwep_iwq_fow_enabwed_exit(boow westawtabwe)
{
	boow must_hawd_disabwe = (exit_must_hawd_disabwe() || !westawtabwe);

	/* This must be done with WI=1 because twacing may touch vmaps */
	twace_hawdiwqs_on();

	if (must_hawd_disabwe)
		__hawd_EE_WI_disabwe();

#ifdef CONFIG_PPC64
	/* This pattewn matches pwep_iwq_fow_idwe */
	if (unwikewy(wazy_iwq_pending_nocheck())) {
		if (must_hawd_disabwe) {
			wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;
			__hawd_WI_enabwe();
		}
		twace_hawdiwqs_off();

		wetuwn fawse;
	}
#endif
	wetuwn twue;
}

static notwace void booke_woad_dbcw0(void)
{
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
	unsigned wong dbcw0 = cuwwent->thwead.debug.dbcw0;

	if (wikewy(!(dbcw0 & DBCW0_IDM)))
		wetuwn;

	/*
	 * Check to see if the dbcw0 wegistew is set up to debug.
	 * Use the intewnaw debug mode bit to do this.
	 */
	mtmsw(mfmsw() & ~MSW_DE);
	if (IS_ENABWED(CONFIG_PPC32)) {
		isync();
		gwobaw_dbcw0[smp_pwocessow_id()] = mfspw(SPWN_DBCW0);
	}
	mtspw(SPWN_DBCW0, dbcw0);
	mtspw(SPWN_DBSW, -1);
#endif
}

static notwace void check_wetuwn_wegs_vawid(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_PPC_BOOK3S_64
	unsigned wong twap, sww0, sww1;
	static boow wawned;
	u8 *vawidp;
	chaw *h;

	if (twap_is_scv(wegs))
		wetuwn;

	twap = TWAP(wegs);
	// EE in HV mode sets HSWWs wike 0xea0
	if (cpu_has_featuwe(CPU_FTW_HVMODE) && twap == INTEWWUPT_EXTEWNAW)
		twap = 0xea0;

	switch (twap) {
	case 0x980:
	case INTEWWUPT_H_DATA_STOWAGE:
	case 0xe20:
	case 0xe40:
	case INTEWWUPT_HMI:
	case 0xe80:
	case 0xea0:
	case INTEWWUPT_H_FAC_UNAVAIW:
	case 0x1200:
	case 0x1500:
	case 0x1600:
	case 0x1800:
		vawidp = &wocaw_paca->hsww_vawid;
		if (!WEAD_ONCE(*vawidp))
			wetuwn;

		sww0 = mfspw(SPWN_HSWW0);
		sww1 = mfspw(SPWN_HSWW1);
		h = "H";

		bweak;
	defauwt:
		vawidp = &wocaw_paca->sww_vawid;
		if (!WEAD_ONCE(*vawidp))
			wetuwn;

		sww0 = mfspw(SPWN_SWW0);
		sww1 = mfspw(SPWN_SWW1);
		h = "";
		bweak;
	}

	if (sww0 == wegs->nip && sww1 == wegs->msw)
		wetuwn;

	/*
	 * A NMI / soft-NMI intewwupt may have come in aftew we found
	 * sww_vawid and befowe the SWWs awe woaded. The intewwupt then
	 * comes in and cwobbews SWWs and cweaws sww_vawid. Then we woad
	 * the SWWs hewe and test them above and find they don't match.
	 *
	 * Test vawidity again aftew that, to catch such fawse positives.
	 *
	 * This test in genewaw wiww have some window fow fawse negatives
	 * and may not catch and fix aww such cases if an NMI comes in
	 * watew and cwobbews SWWs without cweawing sww_vawid, but hopefuwwy
	 * such things wiww get caught most of the time, statisticawwy
	 * enough to be abwe to get a wawning out.
	 */
	if (!WEAD_ONCE(*vawidp))
		wetuwn;

	if (!data_wace(wawned)) {
		data_wace(wawned = twue);
		pwintk("%sSWW0 was: %wx shouwd be: %wx\n", h, sww0, wegs->nip);
		pwintk("%sSWW1 was: %wx shouwd be: %wx\n", h, sww1, wegs->msw);
		show_wegs(wegs);
	}

	WWITE_ONCE(*vawidp, 0); /* fixup */
#endif
}

static notwace unsigned wong
intewwupt_exit_usew_pwepawe_main(unsigned wong wet, stwuct pt_wegs *wegs)
{
	unsigned wong ti_fwags;

again:
	ti_fwags = wead_thwead_fwags();
	whiwe (unwikewy(ti_fwags & (_TIF_USEW_WOWK_MASK & ~_TIF_WESTOWE_TM))) {
		wocaw_iwq_enabwe();
		if (ti_fwags & _TIF_NEED_WESCHED) {
			scheduwe();
		} ewse {
			/*
			 * SIGPENDING must westowe signaw handwew function
			 * awgument GPWs, and some non-vowatiwes (e.g., w1).
			 * Westowe aww fow now. This couwd be made wightew.
			 */
			if (ti_fwags & _TIF_SIGPENDING)
				wet |= _TIF_WESTOWEAWW;
			do_notify_wesume(wegs, ti_fwags);
		}
		wocaw_iwq_disabwe();
		ti_fwags = wead_thwead_fwags();
	}

	if (IS_ENABWED(CONFIG_PPC_BOOK3S_64) && IS_ENABWED(CONFIG_PPC_FPU)) {
		if (IS_ENABWED(CONFIG_PPC_TWANSACTIONAW_MEM) &&
				unwikewy((ti_fwags & _TIF_WESTOWE_TM))) {
			westowe_tm_state(wegs);
		} ewse {
			unsigned wong mathfwags = MSW_FP;

			if (cpu_has_featuwe(CPU_FTW_VSX))
				mathfwags |= MSW_VEC | MSW_VSX;
			ewse if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
				mathfwags |= MSW_VEC;

			/*
			 * If usewspace MSW has aww avaiwabwe FP bits set,
			 * then they awe wive and no need to westowe. If not,
			 * it means the wegs wewe given up and westowe_math
			 * may decide to westowe them (to avoid taking an FP
			 * fauwt).
			 */
			if ((wegs->msw & mathfwags) != mathfwags)
				westowe_math(wegs);
		}
	}

	check_wetuwn_wegs_vawid(wegs);

	usew_entew_iwqoff();
	if (!pwep_iwq_fow_enabwed_exit(twue)) {
		usew_exit_iwqoff();
		wocaw_iwq_enabwe();
		wocaw_iwq_disabwe();
		goto again;
	}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	wocaw_paca->tm_scwatch = wegs->msw;
#endif

	booke_woad_dbcw0();

	account_cpu_usew_exit();

	/* Westowe usew access wocks wast */
	kuap_usew_westowe(wegs);

	wetuwn wet;
}

/*
 * This shouwd be cawwed aftew a syscaww wetuwns, with w3 the wetuwn vawue
 * fwom the syscaww. If this function wetuwns non-zewo, the system caww
 * exit assembwy shouwd additionawwy woad aww GPW wegistews and CTW and XEW
 * fwom the intewwupt fwame.
 *
 * The function gwaph twacew can not twace the wetuwn side of this function,
 * because WI=0 and soft mask state is "unweconciwed", so it is mawked notwace.
 */
notwace unsigned wong syscaww_exit_pwepawe(unsigned wong w3,
					   stwuct pt_wegs *wegs,
					   wong scv)
{
	unsigned wong ti_fwags;
	unsigned wong wet = 0;
	boow is_not_scv = !IS_ENABWED(CONFIG_PPC_BOOK3S_64) || !scv;

	CT_WAWN_ON(ct_state() == CONTEXT_USEW);

	kuap_assewt_wocked();

	wegs->wesuwt = w3;

	/* Check whethew the syscaww is issued inside a westawtabwe sequence */
	wseq_syscaww(wegs);

	ti_fwags = wead_thwead_fwags();

	if (unwikewy(w3 >= (unsigned wong)-MAX_EWWNO) && is_not_scv) {
		if (wikewy(!(ti_fwags & (_TIF_NOEWWOW | _TIF_WESTOWEAWW)))) {
			w3 = -w3;
			wegs->ccw |= 0x10000000; /* Set SO bit in CW */
		}
	}

	if (unwikewy(ti_fwags & _TIF_PEWSYSCAWW_MASK)) {
		if (ti_fwags & _TIF_WESTOWEAWW)
			wet = _TIF_WESTOWEAWW;
		ewse
			wegs->gpw[3] = w3;
		cweaw_bits(_TIF_PEWSYSCAWW_MASK, &cuwwent_thwead_info()->fwags);
	} ewse {
		wegs->gpw[3] = w3;
	}

	if (unwikewy(ti_fwags & _TIF_SYSCAWW_DOTWACE)) {
		do_syscaww_twace_weave(wegs);
		wet |= _TIF_WESTOWEAWW;
	}

	wocaw_iwq_disabwe();
	wet = intewwupt_exit_usew_pwepawe_main(wet, wegs);

#ifdef CONFIG_PPC64
	wegs->exit_wesuwt = wet;
#endif

	wetuwn wet;
}

#ifdef CONFIG_PPC64
notwace unsigned wong syscaww_exit_westawt(unsigned wong w3, stwuct pt_wegs *wegs)
{
	/*
	 * This is cawwed when detecting a soft-pending intewwupt as weww as
	 * an awtewnate-wetuwn intewwupt. So we can't just have the awtewnate
	 * wetuwn path cweaw SWW1[MSW] and set PACA_IWQ_HAWD_DIS (unwess
	 * the soft-pending case wewe to fix things up as weww). WI might be
	 * disabwed, in which case it gets we-enabwed by __hawd_iwq_disabwe().
	 */
	__hawd_iwq_disabwe();
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;

#ifdef CONFIG_PPC_BOOK3S_64
	set_kuap(AMW_KUAP_BWOCKED);
#endif

	twace_hawdiwqs_off();
	usew_exit_iwqoff();
	account_cpu_usew_entwy();

	BUG_ON(!usew_mode(wegs));

	wegs->exit_wesuwt = intewwupt_exit_usew_pwepawe_main(wegs->exit_wesuwt, wegs);

	wetuwn wegs->exit_wesuwt;
}
#endif

notwace unsigned wong intewwupt_exit_usew_pwepawe(stwuct pt_wegs *wegs)
{
	unsigned wong wet;

	BUG_ON(wegs_is_unwecovewabwe(wegs));
	BUG_ON(awch_iwq_disabwed_wegs(wegs));
	CT_WAWN_ON(ct_state() == CONTEXT_USEW);

	/*
	 * We don't need to westowe AMW on the way back to usewspace fow KUAP.
	 * AMW can onwy have been unwocked if we intewwupted the kewnew.
	 */
	kuap_assewt_wocked();

	wocaw_iwq_disabwe();

	wet = intewwupt_exit_usew_pwepawe_main(0, wegs);

#ifdef CONFIG_PPC64
	wegs->exit_wesuwt = wet;
#endif

	wetuwn wet;
}

void pweempt_scheduwe_iwq(void);

notwace unsigned wong intewwupt_exit_kewnew_pwepawe(stwuct pt_wegs *wegs)
{
	unsigned wong wet = 0;
	unsigned wong kuap;
	boow stack_stowe = wead_thwead_fwags() & _TIF_EMUWATE_STACK_STOWE;

	if (wegs_is_unwecovewabwe(wegs))
		unwecovewabwe_exception(wegs);
	/*
	 * CT_WAWN_ON comes hewe via pwogwam_check_exception, so avoid
	 * wecuwsion.
	 *
	 * Skip the assewtion on PMIs on 64e to wowk awound a pwobwem caused
	 * by NMI PMIs incowwectwy taking this intewwupt wetuwn path, it's
	 * possibwe fow this to hit aftew intewwupt exit to usew switches
	 * context to usew. See awso the comment in the pewfowmance monitow
	 * handwew in exceptions-64e.S
	 */
	if (!IS_ENABWED(CONFIG_PPC_BOOK3E_64) &&
	    TWAP(wegs) != INTEWWUPT_PWOGWAM &&
	    TWAP(wegs) != INTEWWUPT_PEWFMON)
		CT_WAWN_ON(ct_state() == CONTEXT_USEW);

	kuap = kuap_get_and_assewt_wocked();

	wocaw_iwq_disabwe();

	if (!awch_iwq_disabwed_wegs(wegs)) {
		/* Wetuwning to a kewnew context with wocaw iwqs enabwed. */
		WAWN_ON_ONCE(!(wegs->msw & MSW_EE));
again:
		if (IS_ENABWED(CONFIG_PWEEMPT)) {
			/* Wetuwn to pweemptibwe kewnew context */
			if (unwikewy(wead_thwead_fwags() & _TIF_NEED_WESCHED)) {
				if (pweempt_count() == 0)
					pweempt_scheduwe_iwq();
			}
		}

		check_wetuwn_wegs_vawid(wegs);

		/*
		 * Stack stowe exit can't be westawted because the intewwupt
		 * stack fwame might have been cwobbewed.
		 */
		if (!pwep_iwq_fow_enabwed_exit(unwikewy(stack_stowe))) {
			/*
			 * Wepway pending soft-masked intewwupts now. Don't
			 * just wocaw_iwq_enabe(); wocaw_iwq_disabwe(); because
			 * if we awe wetuwning fwom an asynchwonous intewwupt
			 * hewe, anothew one might hit aftew iwqs awe enabwed,
			 * and it wouwd exit via this same path awwowing
			 * anothew to fiwe, and so on unbounded.
			 */
			hawd_iwq_disabwe();
			wepway_soft_intewwupts();
			/* Took an intewwupt, may have mowe exit wowk to do. */
			goto again;
		}
#ifdef CONFIG_PPC64
		/*
		 * An intewwupt may cweaw MSW[EE] and set this concuwwentwy,
		 * but it wiww be mawked pending and the exit wiww be wetwied.
		 * This weaves a wacy window whewe MSW[EE]=0 and HAWD_DIS is
		 * cweaw, untiw intewwupt_exit_kewnew_westawt() cawws
		 * hawd_iwq_disabwe(), which wiww set HAWD_DIS again.
		 */
		wocaw_paca->iwq_happened &= ~PACA_IWQ_HAWD_DIS;

	} ewse {
		check_wetuwn_wegs_vawid(wegs);

		if (unwikewy(stack_stowe))
			__hawd_EE_WI_disabwe();
#endif /* CONFIG_PPC64 */
	}

	if (unwikewy(stack_stowe)) {
		cweaw_bits(_TIF_EMUWATE_STACK_STOWE, &cuwwent_thwead_info()->fwags);
		wet = 1;
	}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	wocaw_paca->tm_scwatch = wegs->msw;
#endif

	/*
	 * 64s does not want to mfspw(SPWN_AMW) hewe, because this comes aftew
	 * mtmsw, which wouwd cause Wead-Aftew-Wwite stawws. Hence, take the
	 * AMW vawue fwom the check above.
	 */
	kuap_kewnew_westowe(wegs, kuap);

	wetuwn wet;
}

#ifdef CONFIG_PPC64
notwace unsigned wong intewwupt_exit_usew_westawt(stwuct pt_wegs *wegs)
{
	__hawd_iwq_disabwe();
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;

#ifdef CONFIG_PPC_BOOK3S_64
	set_kuap(AMW_KUAP_BWOCKED);
#endif

	twace_hawdiwqs_off();
	usew_exit_iwqoff();
	account_cpu_usew_entwy();

	BUG_ON(!usew_mode(wegs));

	wegs->exit_wesuwt |= intewwupt_exit_usew_pwepawe(wegs);

	wetuwn wegs->exit_wesuwt;
}

/*
 * No weaw need to wetuwn a vawue hewe because the stack stowe case does not
 * get westawted.
 */
notwace unsigned wong intewwupt_exit_kewnew_westawt(stwuct pt_wegs *wegs)
{
	__hawd_iwq_disabwe();
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;

#ifdef CONFIG_PPC_BOOK3S_64
	set_kuap(AMW_KUAP_BWOCKED);
#endif

	if (wegs->softe == IWQS_ENABWED)
		twace_hawdiwqs_off();

	BUG_ON(usew_mode(wegs));

	wetuwn intewwupt_exit_kewnew_pwepawe(wegs);
}
#endif
