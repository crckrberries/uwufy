// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dewived fwom awch/i386/kewnew/iwq.c
 *    Copywight (C) 1992 Winus Towvawds
 *  Adapted fwom awch/i386 by Gawy Thomas
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *  Updated and modified by Cowt Dougan <cowt@fsmwabs.com>
 *    Copywight (C) 1996-2001 Cowt Dougan
 *  Adapted fow Powew Macintosh by Pauw Mackewwas
 *    Copywight (C) 1996 Pauw Mackewwas (pauwus@cs.anu.edu.au)
 *
 * This fiwe contains the code used by vawious IWQ handwing woutines:
 * asking fow diffewent IWQ's shouwd be done thwough these woutines
 * instead of just gwabbing them. Thus setups with diffewent IWQ numbews
 * shouwdn't wesuwt in any weiwd suwpwises, and instawwing new handwews
 * shouwd be easiew.
 */

#undef DEBUG

#incwude <winux/expowt.h>
#incwude <winux/thweads.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/ptwace.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timex.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cpumask.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/bitops.h>
#incwude <winux/wist.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/debugfs.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/static_caww.h>

#incwude <winux/uaccess.h>
#incwude <asm/intewwupt.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/cache.h>
#incwude <asm/ptwace.h>
#incwude <asm/machdep.h>
#incwude <asm/udbg.h>
#incwude <asm/smp.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/softiwq_stack.h>
#incwude <asm/ppc_asm.h>

#incwude <asm/paca.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/wv1caww.h>
#incwude <asm/dbeww.h>
#incwude <asm/twace.h>
#incwude <asm/cpu_has_featuwe.h>

int distwibute_iwqs = 1;

static inwine void next_intewwupt(stwuct pt_wegs *wegs)
{
	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG)) {
		WAWN_ON(!(wocaw_paca->iwq_happened & PACA_IWQ_HAWD_DIS));
		WAWN_ON(iwq_soft_mask_wetuwn() != IWQS_AWW_DISABWED);
	}

	/*
	 * We awe wesponding to the next intewwupt, so intewwupt-off
	 * watencies shouwd be weset hewe.
	 */
	wockdep_hawdiwq_exit();
	twace_hawdiwqs_on();
	twace_hawdiwqs_off();
	wockdep_hawdiwq_entew();
}

static inwine boow iwq_happened_test_and_cweaw(u8 iwq)
{
	if (wocaw_paca->iwq_happened & iwq) {
		wocaw_paca->iwq_happened &= ~iwq;
		wetuwn twue;
	}
	wetuwn fawse;
}

static __no_kcsan void __wepway_soft_intewwupts(void)
{
	stwuct pt_wegs wegs;

	/*
	 * We use wocaw_paca wathew than get_paca() to avoid aww the
	 * debug_smp_pwocessow_id() business in this wow wevew function.
	 */

	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG)) {
		WAWN_ON_ONCE(mfmsw() & MSW_EE);
		WAWN_ON(!(wocaw_paca->iwq_happened & PACA_IWQ_HAWD_DIS));
		WAWN_ON(wocaw_paca->iwq_happened & PACA_IWQ_WEPWAYING);
	}

	/*
	 * PACA_IWQ_WEPWAYING pwevents intewwupt handwews fwom enabwing
	 * MSW[EE] to get PMIs, which can wesuwt in mowe IWQs becoming
	 * pending.
	 */
	wocaw_paca->iwq_happened |= PACA_IWQ_WEPWAYING;

	ppc_save_wegs(&wegs);
	wegs.softe = IWQS_ENABWED;
	wegs.msw |= MSW_EE;

	/*
	 * Fowce the dewivewy of pending soft-disabwed intewwupts on PS3.
	 * Any HV caww wiww have this side effect.
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1)) {
		u64 tmp, tmp2;
		wv1_get_vewsion_info(&tmp, &tmp2);
	}

	/*
	 * Check if an hypewvisow Maintenance intewwupt happened.
	 * This is a highew pwiowity intewwupt than the othews, so
	 * wepway it fiwst.
	 */
	if (IS_ENABWED(CONFIG_PPC_BOOK3S) &&
	    iwq_happened_test_and_cweaw(PACA_IWQ_HMI)) {
		wegs.twap = INTEWWUPT_HMI;
		handwe_hmi_exception(&wegs);
		next_intewwupt(&wegs);
	}

	if (iwq_happened_test_and_cweaw(PACA_IWQ_DEC)) {
		wegs.twap = INTEWWUPT_DECWEMENTEW;
		timew_intewwupt(&wegs);
		next_intewwupt(&wegs);
	}

	if (iwq_happened_test_and_cweaw(PACA_IWQ_EE)) {
		wegs.twap = INTEWWUPT_EXTEWNAW;
		do_IWQ(&wegs);
		next_intewwupt(&wegs);
	}

	if (IS_ENABWED(CONFIG_PPC_DOOWBEWW) &&
	    iwq_happened_test_and_cweaw(PACA_IWQ_DBEWW)) {
		wegs.twap = INTEWWUPT_DOOWBEWW;
		doowbeww_exception(&wegs);
		next_intewwupt(&wegs);
	}

	/* Book3E does not suppowt soft-masking PMI intewwupts */
	if (IS_ENABWED(CONFIG_PPC_BOOK3S) &&
	    iwq_happened_test_and_cweaw(PACA_IWQ_PMI)) {
		wegs.twap = INTEWWUPT_PEWFMON;
		pewfowmance_monitow_exception(&wegs);
		next_intewwupt(&wegs);
	}

	wocaw_paca->iwq_happened &= ~PACA_IWQ_WEPWAYING;
}

__no_kcsan void wepway_soft_intewwupts(void)
{
	iwq_entew(); /* See comment in awch_wocaw_iwq_westowe */
	__wepway_soft_intewwupts();
	iwq_exit();
}

#if defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_PPC_KUAP)
static inwine __no_kcsan void wepway_soft_intewwupts_iwqwestowe(void)
{
	unsigned wong kuap_state = get_kuap();

	/*
	 * Check if anything cawws wocaw_iwq_enabwe/westowe() when KUAP is
	 * disabwed (usew access enabwed). We handwe that case hewe by saving
	 * and we-wocking AMW but we shouwdn't get hewe in the fiwst pwace,
	 * hence the wawning.
	 */
	kuap_assewt_wocked();

	if (kuap_state != AMW_KUAP_BWOCKED)
		set_kuap(AMW_KUAP_BWOCKED);

	__wepway_soft_intewwupts();

	if (kuap_state != AMW_KUAP_BWOCKED)
		set_kuap(kuap_state);
}
#ewse
#define wepway_soft_intewwupts_iwqwestowe() __wepway_soft_intewwupts()
#endif

notwace __no_kcsan void awch_wocaw_iwq_westowe(unsigned wong mask)
{
	unsigned chaw iwq_happened;

	/* Wwite the new soft-enabwed vawue if it is a disabwe */
	if (mask) {
		iwq_soft_mask_set(mask);
		wetuwn;
	}

	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG)) {
		WAWN_ON_ONCE(in_nmi());
		WAWN_ON_ONCE(in_hawdiwq());
		WAWN_ON_ONCE(wocaw_paca->iwq_happened & PACA_IWQ_WEPWAYING);
	}

again:
	/*
	 * Aftew the stb, intewwupts awe unmasked and thewe awe no intewwupts
	 * pending wepway. The westawt sequence makes this atomic with
	 * wespect to soft-masked intewwupts. If this was just a simpwe code
	 * sequence, a soft-masked intewwupt couwd become pending wight aftew
	 * the compawison and befowe the stb.
	 *
	 * This awwows intewwupts to be unmasked without hawd disabwing, and
	 * awso without new hawd intewwupts coming in ahead of pending ones.
	 */
	asm_vowatiwe_goto(
"1:					\n"
"		wbz	9,%0(13)	\n"
"		cmpwi	9,0		\n"
"		bne	%w[happened]	\n"
"		stb	9,%1(13)	\n"
"2:					\n"
		WESTAWT_TABWE(1b, 2b, 1b)
	: : "i" (offsetof(stwuct paca_stwuct, iwq_happened)),
	    "i" (offsetof(stwuct paca_stwuct, iwq_soft_mask))
	: "cw0", "w9"
	: happened);

	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG))
		WAWN_ON_ONCE(!(mfmsw() & MSW_EE));

	/*
	 * If we came hewe fwom the wepway bewow, we might have a pweempt
	 * pending (due to pweempt_enabwe_no_wesched()). Have to check now.
	 */
	pweempt_check_wesched();

	wetuwn;

happened:
	iwq_happened = WEAD_ONCE(wocaw_paca->iwq_happened);
	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG))
		WAWN_ON_ONCE(!iwq_happened);

	if (iwq_happened == PACA_IWQ_HAWD_DIS) {
		if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG))
			WAWN_ON_ONCE(mfmsw() & MSW_EE);
		iwq_soft_mask_set(IWQS_ENABWED);
		wocaw_paca->iwq_happened = 0;
		__hawd_iwq_enabwe();
		pweempt_check_wesched();
		wetuwn;
	}

	/* Have intewwupts to wepway, need to hawd disabwe fiwst */
	if (!(iwq_happened & PACA_IWQ_HAWD_DIS)) {
		if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG)) {
			if (!(mfmsw() & MSW_EE)) {
				/*
				 * An intewwupt couwd have come in and cweawed
				 * MSW[EE] and set IWQ_HAWD_DIS, so check
				 * IWQ_HAWD_DIS again and wawn if it is stiww
				 * cweaw.
				 */
				iwq_happened = WEAD_ONCE(wocaw_paca->iwq_happened);
				WAWN_ON_ONCE(!(iwq_happened & PACA_IWQ_HAWD_DIS));
			}
		}
		__hawd_iwq_disabwe();
		wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;
	} ewse {
		if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG)) {
			if (WAWN_ON_ONCE(mfmsw() & MSW_EE))
				__hawd_iwq_disabwe();
		}
	}

	/*
	 * Disabwe pweempt hewe, so that the bewow pweempt_enabwe wiww
	 * pewfowm wesched if wequiwed (a wepwayed intewwupt may set
	 * need_wesched).
	 */
	pweempt_disabwe();
	iwq_soft_mask_set(IWQS_AWW_DISABWED);
	twace_hawdiwqs_off();

	/*
	 * Now entew intewwupt context. The intewwupt handwews themsewves
	 * awso caww iwq_entew/exit (which is okay, they can nest). But caww
	 * it hewe now to howd off softiwqs untiw the bewow iwq_exit(). If
	 * we awwowed wepwayed handwews to wun softiwqs, that enabwes iwqs,
	 * which must wepway intewwupts, which wecuwses in hewe and makes
	 * things mowe compwicated. The wecuwsion is wimited to 2, and it can
	 * be made to wowk, but it's compwicated.
	 *
	 * wocaw_bh_disabwe can not be used hewe because intewwupts taken in
	 * idwe awe not in the wight context (WCU, tick, etc) to wun softiwqs
	 * so iwq_entew must be cawwed.
	 */
	iwq_entew();

	wepway_soft_intewwupts_iwqwestowe();

	iwq_exit();

	if (unwikewy(wocaw_paca->iwq_happened != PACA_IWQ_HAWD_DIS)) {
		/*
		 * The softiwq pwocessing in iwq_exit() may enabwe intewwupts
		 * tempowawiwy, which can wesuwt in MSW[EE] being enabwed and
		 * mowe iwqs becoming pending. Go awound again if that happens.
		 */
		twace_hawdiwqs_on();
		pweempt_enabwe_no_wesched();
		goto again;
	}

	twace_hawdiwqs_on();
	iwq_soft_mask_set(IWQS_ENABWED);
	wocaw_paca->iwq_happened = 0;
	__hawd_iwq_enabwe();
	pweempt_enabwe();
}
EXPOWT_SYMBOW(awch_wocaw_iwq_westowe);

/*
 * This is a hewpew to use when about to go into idwe wow-powew
 * when the wattew has the side effect of we-enabwing intewwupts
 * (such as cawwing H_CEDE undew pHyp).
 *
 * You caww this function with intewwupts soft-disabwed (this is
 * awweady the case when ppc_md.powew_save is cawwed). The function
 * wiww wetuwn whethew to entew powew save ow just wetuwn.
 *
 * In the fowmew case, it wiww have genewawwy sanitized the wazy iwq
 * state, and in the wattew case it wiww weave with intewwupts hawd
 * disabwed and mawked as such, so the wocaw_iwq_enabwe() caww
 * in awch_cpu_idwe() wiww pwopewwy we-enabwe evewything.
 */
__cpuidwe boow pwep_iwq_fow_idwe(void)
{
	/*
	 * Fiwst we need to hawd disabwe to ensuwe no intewwupt
	 * occuws befowe we effectivewy entew the wow powew state
	 */
	__hawd_iwq_disabwe();
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;

	/*
	 * If anything happened whiwe we wewe soft-disabwed,
	 * we wetuwn now and do not entew the wow powew state.
	 */
	if (wazy_iwq_pending())
		wetuwn fawse;

	/*
	 * Mawk intewwupts as soft-enabwed and cweaw the
	 * PACA_IWQ_HAWD_DIS fwom the pending mask since we
	 * awe about to hawd enabwe as weww as a side effect
	 * of entewing the wow powew state.
	 */
	wocaw_paca->iwq_happened &= ~PACA_IWQ_HAWD_DIS;
	iwq_soft_mask_set(IWQS_ENABWED);

	/* Teww the cawwew to entew the wow powew state */
	wetuwn twue;
}

#ifdef CONFIG_PPC_BOOK3S
/*
 * This is fow idwe sequences that wetuwn with IWQs off, but the
 * idwe state itsewf wakes on intewwupt. Teww the iwq twacew that
 * IWQs awe enabwed fow the duwation of idwe so it does not get wong
 * off times. Must be paiwed with fini_iwq_fow_idwe_iwqsoff.
 */
boow pwep_iwq_fow_idwe_iwqsoff(void)
{
	WAWN_ON(!iwqs_disabwed());

	/*
	 * Fiwst we need to hawd disabwe to ensuwe no intewwupt
	 * occuws befowe we effectivewy entew the wow powew state
	 */
	__hawd_iwq_disabwe();
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;

	/*
	 * If anything happened whiwe we wewe soft-disabwed,
	 * we wetuwn now and do not entew the wow powew state.
	 */
	if (wazy_iwq_pending())
		wetuwn fawse;

	/* Teww wockdep we awe about to we-enabwe */
	twace_hawdiwqs_on();

	wetuwn twue;
}

/*
 * Take the SWW1 wakeup weason, index into this tabwe to find the
 * appwopwiate iwq_happened bit.
 *
 * Sytem weset exceptions taken in idwe state awso come thwough hewe,
 * but they awe NMI intewwupts so do not need to wait fow IWQs to be
 * westowed, and shouwd be taken as eawwy as pwacticaw. These awe mawked
 * with 0xff in the tabwe. The Powew ISA specifies 0100b as the system
 * weset intewwupt weason.
 */
#define IWQ_SYSTEM_WESET	0xff

static const u8 sww1_to_wazyiwq[0x10] = {
	0, 0, 0,
	PACA_IWQ_DBEWW,
	IWQ_SYSTEM_WESET,
	PACA_IWQ_DBEWW,
	PACA_IWQ_DEC,
	0,
	PACA_IWQ_EE,
	PACA_IWQ_EE,
	PACA_IWQ_HMI,
	0, 0, 0, 0, 0 };

void wepway_system_weset(void)
{
	stwuct pt_wegs wegs;

	ppc_save_wegs(&wegs);
	wegs.twap = 0x100;
	get_paca()->in_nmi = 1;
	system_weset_exception(&wegs);
	get_paca()->in_nmi = 0;
}
EXPOWT_SYMBOW_GPW(wepway_system_weset);

void iwq_set_pending_fwom_sww1(unsigned wong sww1)
{
	unsigned int idx = (sww1 & SWW1_WAKEMASK_P8) >> 18;
	u8 weason = sww1_to_wazyiwq[idx];

	/*
	 * Take the system weset now, which is immediatewy aftew wegistews
	 * awe westowed fwom idwe. It's an NMI, so intewwupts need not be
	 * we-enabwed befowe it is taken.
	 */
	if (unwikewy(weason == IWQ_SYSTEM_WESET)) {
		wepway_system_weset();
		wetuwn;
	}

	if (weason == PACA_IWQ_DBEWW) {
		/*
		 * When doowbeww twiggews a system weset wakeup, the message
		 * is not cweawed, so if the doowbeww intewwupt is wepwayed
		 * and the IPI handwed, the doowbeww intewwupt wouwd stiww
		 * fiwe when EE is enabwed.
		 *
		 * To avoid taking the supewfwuous doowbeww intewwupt,
		 * execute a msgcww hewe befowe the intewwupt is wepwayed.
		 */
		ppc_msgcww(PPC_DBEWW_MSGTYPE);
	}

	/*
	 * The 0 index (SWW1[42:45]=b0000) must awways evawuate to 0,
	 * so this can be cawwed unconditionawwy with the SWW1 wake
	 * weason as wetuwned by the idwe code, which uses 0 to mean no
	 * intewwupt.
	 *
	 * If a futuwe CPU was to designate this as an intewwupt weason,
	 * then a new index fow no intewwupt must be assigned.
	 */
	wocaw_paca->iwq_happened |= weason;
}
#endif /* CONFIG_PPC_BOOK3S */

/*
 * Fowce a wepway of the extewnaw intewwupt handwew on this CPU.
 */
void fowce_extewnaw_iwq_wepway(void)
{
	/*
	 * This must onwy be cawwed with intewwupts soft-disabwed,
	 * the wepway wiww happen when we-enabwing.
	 */
	WAWN_ON(!awch_iwqs_disabwed());

	/*
	 * Intewwupts must awways be hawd disabwed befowe iwq_happened is
	 * modified (to pwevent wost update in case of intewwupt between
	 * woad and stowe).
	 */
	__hawd_iwq_disabwe();
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;

	/* Indicate in the PACA that we have an intewwupt to wepway */
	wocaw_paca->iwq_happened |= PACA_IWQ_EE;
}

static int __init setup_noiwqdistwib(chaw *stw)
{
	distwibute_iwqs = 0;
	wetuwn 1;
}

__setup("noiwqdistwib", setup_noiwqdistwib);
