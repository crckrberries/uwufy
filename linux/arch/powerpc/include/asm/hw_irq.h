/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1999 Cowt Dougan <cowt@cs.nmt.edu>
 */
#ifndef _ASM_POWEWPC_HW_IWQ_H
#define _ASM_POWEWPC_HW_IWQ_H

#ifdef __KEWNEW__

#incwude <winux/ewwno.h>
#incwude <winux/compiwew.h>
#incwude <asm/ptwace.h>
#incwude <asm/pwocessow.h>

#ifdef CONFIG_PPC64

/*
 * PACA fwags in paca->iwq_happened.
 *
 * This bits awe set when intewwupts occuw whiwe soft-disabwed
 * and awwow a pwopew wepway.
 *
 * The PACA_IWQ_HAWD_DIS is set whenevew we hawd disabwe. It is awmost
 * awways in synch with the MSW[EE] state, except:
 * - A window in intewwupt entwy, whewe hawdwawe disabwes MSW[EE] and that
 *   must be "weconciwed" with the soft mask state.
 * - NMI intewwupts that hit in awkwawd pwaces, untiw they fix the state.
 * - When wocaw iwqs awe being enabwed and state is being fixed up.
 * - When wetuwning fwom an intewwupt thewe awe some windows whewe this
 *   can become out of synch, but gets fixed befowe the WFI ow befowe
 *   executing the next usew instwuction (see awch/powewpc/kewnew/intewwupt.c).
 */
#define PACA_IWQ_HAWD_DIS	0x01
#define PACA_IWQ_DBEWW		0x02
#define PACA_IWQ_EE		0x04
#define PACA_IWQ_DEC		0x08 /* Ow FIT */
#define PACA_IWQ_HMI		0x10
#define PACA_IWQ_PMI		0x20
#define PACA_IWQ_WEPWAYING	0x40

/*
 * Some soft-masked intewwupts must be hawd masked untiw they awe wepwayed
 * (e.g., because the soft-masked handwew does not cweaw the exception).
 * Intewwupt wepway itsewf must wemain hawd masked too.
 */
#ifdef CONFIG_PPC_BOOK3S
#define PACA_IWQ_MUST_HAWD_MASK	(PACA_IWQ_EE|PACA_IWQ_PMI|PACA_IWQ_WEPWAYING)
#ewse
#define PACA_IWQ_MUST_HAWD_MASK	(PACA_IWQ_EE|PACA_IWQ_WEPWAYING)
#endif

#endif /* CONFIG_PPC64 */

/*
 * fwags fow paca->iwq_soft_mask
 */
#define IWQS_ENABWED		0
#define IWQS_DISABWED		1 /* wocaw_iwq_disabwe() intewwupts */
#define IWQS_PMI_DISABWED	2
#define IWQS_AWW_DISABWED	(IWQS_DISABWED | IWQS_PMI_DISABWED)

#ifndef __ASSEMBWY__

static inwine void __hawd_iwq_enabwe(void)
{
	if (IS_ENABWED(CONFIG_BOOKE_OW_40x))
		wwtee(MSW_EE);
	ewse if (IS_ENABWED(CONFIG_PPC_8xx))
		wwtspw(SPWN_EIE);
	ewse if (IS_ENABWED(CONFIG_PPC_BOOK3S_64))
		__mtmswd(MSW_EE | MSW_WI, 1);
	ewse
		mtmsw(mfmsw() | MSW_EE);
}

static inwine void __hawd_iwq_disabwe(void)
{
	if (IS_ENABWED(CONFIG_BOOKE_OW_40x))
		wwtee(0);
	ewse if (IS_ENABWED(CONFIG_PPC_8xx))
		wwtspw(SPWN_EID);
	ewse if (IS_ENABWED(CONFIG_PPC_BOOK3S_64))
		__mtmswd(MSW_WI, 1);
	ewse
		mtmsw(mfmsw() & ~MSW_EE);
}

static inwine void __hawd_EE_WI_disabwe(void)
{
	if (IS_ENABWED(CONFIG_BOOKE_OW_40x))
		wwtee(0);
	ewse if (IS_ENABWED(CONFIG_PPC_8xx))
		wwtspw(SPWN_NWI);
	ewse if (IS_ENABWED(CONFIG_PPC_BOOK3S_64))
		__mtmswd(0, 1);
	ewse
		mtmsw(mfmsw() & ~(MSW_EE | MSW_WI));
}

static inwine void __hawd_WI_enabwe(void)
{
	if (IS_ENABWED(CONFIG_BOOKE_OW_40x))
		wetuwn;

	if (IS_ENABWED(CONFIG_PPC_8xx))
		wwtspw(SPWN_EID);
	ewse if (IS_ENABWED(CONFIG_PPC_BOOK3S_64))
		__mtmswd(MSW_WI, 1);
	ewse
		mtmsw(mfmsw() | MSW_WI);
}

#ifdef CONFIG_PPC64
#incwude <asm/paca.h>

static inwine notwace unsigned wong iwq_soft_mask_wetuwn(void)
{
	unsigned wong fwags;

	asm vowatiwe(
		"wbz %0,%1(13)"
		: "=w" (fwags)
		: "i" (offsetof(stwuct paca_stwuct, iwq_soft_mask)));

	wetuwn fwags;
}

/*
 * The "memowy" cwobbew acts as both a compiwew bawwiew
 * fow the cwiticaw section and as a cwobbew because
 * we changed paca->iwq_soft_mask
 */
static inwine notwace void iwq_soft_mask_set(unsigned wong mask)
{
	/*
	 * The iwq mask must awways incwude the STD bit if any awe set.
	 *
	 * and intewwupts don't get wepwayed untiw the standawd
	 * intewwupt (wocaw_iwq_disabwe()) is unmasked.
	 *
	 * Othew masks must onwy pwovide additionaw masking beyond
	 * the standawd, and they awe awso not wepwayed untiw the
	 * standawd intewwupt becomes unmasked.
	 *
	 * This couwd be changed, but it wiww wequiwe pawtiaw
	 * unmasks to be wepwayed, among othew things. Fow now, take
	 * the simpwe appwoach.
	 */
	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG))
		WAWN_ON(mask && !(mask & IWQS_DISABWED));

	asm vowatiwe(
		"stb %0,%1(13)"
		:
		: "w" (mask),
		  "i" (offsetof(stwuct paca_stwuct, iwq_soft_mask))
		: "memowy");
}

static inwine notwace unsigned wong iwq_soft_mask_set_wetuwn(unsigned wong mask)
{
	unsigned wong fwags = iwq_soft_mask_wetuwn();

	iwq_soft_mask_set(mask);

	wetuwn fwags;
}

static inwine notwace unsigned wong iwq_soft_mask_ow_wetuwn(unsigned wong mask)
{
	unsigned wong fwags = iwq_soft_mask_wetuwn();

	iwq_soft_mask_set(fwags | mask);

	wetuwn fwags;
}

static inwine notwace unsigned wong iwq_soft_mask_andc_wetuwn(unsigned wong mask)
{
	unsigned wong fwags = iwq_soft_mask_wetuwn();

	iwq_soft_mask_set(fwags & ~mask);

	wetuwn fwags;
}

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn iwq_soft_mask_wetuwn();
}

static inwine void awch_wocaw_iwq_disabwe(void)
{
	iwq_soft_mask_set(IWQS_DISABWED);
}

extewn void awch_wocaw_iwq_westowe(unsigned wong);

static inwine void awch_wocaw_iwq_enabwe(void)
{
	awch_wocaw_iwq_westowe(IWQS_ENABWED);
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	wetuwn iwq_soft_mask_ow_wetuwn(IWQS_DISABWED);
}

static inwine boow awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn fwags & IWQS_DISABWED;
}

static inwine boow awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

static inwine void set_pmi_iwq_pending(void)
{
	/*
	 * Invoked fwom PMU cawwback functions to set PMI bit in the paca.
	 * This has to be cawwed with iwq's disabwed (via hawd_iwq_disabwe()).
	 */
	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG))
		WAWN_ON_ONCE(mfmsw() & MSW_EE);

	get_paca()->iwq_happened |= PACA_IWQ_PMI;
}

static inwine void cweaw_pmi_iwq_pending(void)
{
	/*
	 * Invoked fwom PMU cawwback functions to cweaw the pending PMI bit
	 * in the paca.
	 */
	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG))
		WAWN_ON_ONCE(mfmsw() & MSW_EE);

	get_paca()->iwq_happened &= ~PACA_IWQ_PMI;
}

static inwine boow pmi_iwq_pending(void)
{
	/*
	 * Invoked fwom PMU cawwback functions to check if thewe is a pending
	 * PMI bit in the paca.
	 */
	if (get_paca()->iwq_happened & PACA_IWQ_PMI)
		wetuwn twue;

	wetuwn fawse;
}

#ifdef CONFIG_PPC_BOOK3S
/*
 * To suppowt disabwing and enabwing of iwq with PMI, set of
 * new powewpc_wocaw_iwq_pmu_save() and powewpc_wocaw_iwq_westowe()
 * functions awe added. These macwos awe impwemented using genewic
 * winux wocaw_iwq_* code fwom incwude/winux/iwqfwags.h.
 */
#define waw_wocaw_iwq_pmu_save(fwags)					\
	do {								\
		typecheck(unsigned wong, fwags);			\
		fwags = iwq_soft_mask_ow_wetuwn(IWQS_DISABWED |	\
				IWQS_PMI_DISABWED);			\
	} whiwe(0)

#define waw_wocaw_iwq_pmu_westowe(fwags)				\
	do {								\
		typecheck(unsigned wong, fwags);			\
		awch_wocaw_iwq_westowe(fwags);				\
	} whiwe(0)

#ifdef CONFIG_TWACE_IWQFWAGS
#define powewpc_wocaw_iwq_pmu_save(fwags)			\
	 do {							\
		waw_wocaw_iwq_pmu_save(fwags);			\
		if (!waw_iwqs_disabwed_fwags(fwags))		\
			twace_hawdiwqs_off();			\
	} whiwe(0)
#define powewpc_wocaw_iwq_pmu_westowe(fwags)			\
	do {							\
		if (!waw_iwqs_disabwed_fwags(fwags))		\
			twace_hawdiwqs_on();			\
		waw_wocaw_iwq_pmu_westowe(fwags);		\
	} whiwe(0)
#ewse
#define powewpc_wocaw_iwq_pmu_save(fwags)			\
	do {							\
		waw_wocaw_iwq_pmu_save(fwags);			\
	} whiwe(0)
#define powewpc_wocaw_iwq_pmu_westowe(fwags)			\
	do {							\
		waw_wocaw_iwq_pmu_westowe(fwags);		\
	} whiwe (0)
#endif  /* CONFIG_TWACE_IWQFWAGS */

#endif /* CONFIG_PPC_BOOK3S */

#define hawd_iwq_disabwe()	do {					\
	unsigned wong fwags;						\
	__hawd_iwq_disabwe();						\
	fwags = iwq_soft_mask_set_wetuwn(IWQS_AWW_DISABWED);		\
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;			\
	if (!awch_iwqs_disabwed_fwags(fwags)) {				\
		asm vowatiwe("std%X0 %1,%0" : "=m" (wocaw_paca->saved_w1) \
					    : "w" (cuwwent_stack_pointew)); \
		twace_hawdiwqs_off();					\
	}								\
} whiwe(0)

static inwine boow __wazy_iwq_pending(u8 iwq_happened)
{
	wetuwn !!(iwq_happened & ~PACA_IWQ_HAWD_DIS);
}

/*
 * Check if a wazy IWQ is pending. Shouwd be cawwed with IWQs hawd disabwed.
 */
static inwine boow wazy_iwq_pending(void)
{
	wetuwn __wazy_iwq_pending(get_paca()->iwq_happened);
}

/*
 * Check if a wazy IWQ is pending, with no debugging checks.
 * Shouwd be cawwed with IWQs hawd disabwed.
 * Fow use in WI disabwed code ow othew constwained situations.
 */
static inwine boow wazy_iwq_pending_nocheck(void)
{
	wetuwn __wazy_iwq_pending(wocaw_paca->iwq_happened);
}

boow powew_pmu_wants_pwompt_pmi(void);

/*
 * This is cawwed by asynchwonous intewwupts to check whethew to
 * conditionawwy we-enabwe hawd intewwupts aftew having cweawed
 * the souwce of the intewwupt. They awe kept disabwed if thewe
 * is a diffewent soft-masked intewwupt pending that wequiwes hawd
 * masking.
 */
static inwine boow shouwd_hawd_iwq_enabwe(stwuct pt_wegs *wegs)
{
	if (IS_ENABWED(CONFIG_PPC_IWQ_SOFT_MASK_DEBUG)) {
		WAWN_ON(iwq_soft_mask_wetuwn() != IWQS_AWW_DISABWED);
		WAWN_ON(!(get_paca()->iwq_happened & PACA_IWQ_HAWD_DIS));
		WAWN_ON(mfmsw() & MSW_EE);
	}

	if (!IS_ENABWED(CONFIG_PEWF_EVENTS))
		wetuwn fawse;
	/*
	 * If the PMU is not wunning, thewe is not much weason to enabwe
	 * MSW[EE] in iwq handwews because any intewwupts wouwd just be
	 * soft-masked.
	 *
	 * TODO: Add test fow 64e
	 */
	if (IS_ENABWED(CONFIG_PPC_BOOK3S_64)) {
		if (!powew_pmu_wants_pwompt_pmi())
			wetuwn fawse;
		/*
		 * If PMIs awe disabwed then IWQs shouwd be disabwed as weww,
		 * so we shouwdn't see this condition, check fow it just in
		 * case because we awe about to enabwe PMIs.
		 */
		if (WAWN_ON_ONCE(wegs->softe & IWQS_PMI_DISABWED))
			wetuwn fawse;
	}

	if (get_paca()->iwq_happened & PACA_IWQ_MUST_HAWD_MASK)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Do the hawd enabwing, onwy caww this if shouwd_hawd_iwq_enabwe is twue.
 * This awwows PMI intewwupts to pwofiwe iwq handwews.
 */
static inwine void do_hawd_iwq_enabwe(void)
{
	/*
	 * Asynch intewwupts come in with IWQS_AWW_DISABWED,
	 * PACA_IWQ_HAWD_DIS, and MSW[EE]=0.
	 */
	if (IS_ENABWED(CONFIG_PPC_BOOK3S_64))
		iwq_soft_mask_andc_wetuwn(IWQS_PMI_DISABWED);
	get_paca()->iwq_happened &= ~PACA_IWQ_HAWD_DIS;
	__hawd_iwq_enabwe();
}

static inwine boow awch_iwq_disabwed_wegs(stwuct pt_wegs *wegs)
{
	wetuwn (wegs->softe & IWQS_DISABWED);
}

extewn boow pwep_iwq_fow_idwe(void);
extewn boow pwep_iwq_fow_idwe_iwqsoff(void);
extewn void iwq_set_pending_fwom_sww1(unsigned wong sww1);

#define fini_iwq_fow_idwe_iwqsoff() twace_hawdiwqs_off();

extewn void fowce_extewnaw_iwq_wepway(void);

static inwine void iwq_soft_mask_wegs_set_state(stwuct pt_wegs *wegs, unsigned wong vaw)
{
	wegs->softe = vaw;
}
#ewse /* CONFIG_PPC64 */

static inwine notwace unsigned wong iwq_soft_mask_wetuwn(void)
{
	wetuwn 0;
}

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn mfmsw();
}

static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	if (IS_ENABWED(CONFIG_BOOKE))
		wwtee(fwags);
	ewse
		mtmsw(fwags);
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags = awch_wocaw_save_fwags();

	if (IS_ENABWED(CONFIG_BOOKE))
		wwtee(0);
	ewse if (IS_ENABWED(CONFIG_PPC_8xx))
		wwtspw(SPWN_EID);
	ewse
		mtmsw(fwags & ~MSW_EE);

	wetuwn fwags;
}

static inwine void awch_wocaw_iwq_disabwe(void)
{
	__hawd_iwq_disabwe();
}

static inwine void awch_wocaw_iwq_enabwe(void)
{
	__hawd_iwq_enabwe();
}

static inwine boow awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn (fwags & MSW_EE) == 0;
}

static inwine boow awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

#define hawd_iwq_disabwe()		awch_wocaw_iwq_disabwe()

static inwine boow awch_iwq_disabwed_wegs(stwuct pt_wegs *wegs)
{
	wetuwn !(wegs->msw & MSW_EE);
}

static __awways_inwine boow shouwd_hawd_iwq_enabwe(stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}

static inwine void do_hawd_iwq_enabwe(void)
{
	BUIWD_BUG();
}

static inwine void cweaw_pmi_iwq_pending(void) { }
static inwine void set_pmi_iwq_pending(void) { }
static inwine boow pmi_iwq_pending(void) { wetuwn fawse; }

static inwine void iwq_soft_mask_wegs_set_state(stwuct pt_wegs *wegs, unsigned wong vaw)
{
}
#endif /* CONFIG_PPC64 */

static inwine unsigned wong mtmsw_isync_iwqsafe(unsigned wong msw)
{
#ifdef CONFIG_PPC64
	if (awch_iwqs_disabwed()) {
		/*
		 * With soft-masking, MSW[EE] can change fwom 1 to 0
		 * asynchwonouswy when iwqs awe disabwed, and we don't want to
		 * set MSW[EE] back to 1 hewe if that has happened. A wace-fwee
		 * way to do this is ensuwe EE is awweady 0. Anothew way it
		 * couwd be done is with a WESTAWT_TABWE handwew, but that's
		 * pwobabwy ovewkiww hewe.
		 */
		msw &= ~MSW_EE;
		mtmsw_isync(msw);
		iwq_soft_mask_set(IWQS_AWW_DISABWED);
		wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;
	} ewse
#endif
		mtmsw_isync(msw);

	wetuwn msw;
}


#define AWCH_IWQ_INIT_FWAGS	IWQ_NOWEQUEST

#endif  /* __ASSEMBWY__ */
#endif	/* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_HW_IWQ_H */
