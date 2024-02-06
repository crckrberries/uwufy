/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_INTEWWUPT_H
#define _ASM_POWEWPC_INTEWWUPT_H

/* BookE/4xx */
#define INTEWWUPT_CWITICAW_INPUT  0x100

/* BookE */
#define INTEWWUPT_DEBUG           0xd00
#ifdef CONFIG_BOOKE
#define INTEWWUPT_PEWFMON         0x260
#define INTEWWUPT_DOOWBEWW        0x280
#endif

/* BookS/4xx/8xx */
#define INTEWWUPT_MACHINE_CHECK   0x200

/* BookS/8xx */
#define INTEWWUPT_SYSTEM_WESET    0x100

/* BookS */
#define INTEWWUPT_DATA_SEGMENT    0x380
#define INTEWWUPT_INST_SEGMENT    0x480
#define INTEWWUPT_TWACE           0xd00
#define INTEWWUPT_H_DATA_STOWAGE  0xe00
#define INTEWWUPT_HMI			0xe60
#define INTEWWUPT_H_FAC_UNAVAIW   0xf80
#ifdef CONFIG_PPC_BOOK3S
#define INTEWWUPT_DOOWBEWW        0xa00
#define INTEWWUPT_PEWFMON         0xf00
#define INTEWWUPT_AWTIVEC_UNAVAIW	0xf20
#endif

/* BookE/BookS/4xx/8xx */
#define INTEWWUPT_DATA_STOWAGE    0x300
#define INTEWWUPT_INST_STOWAGE    0x400
#define INTEWWUPT_EXTEWNAW		0x500
#define INTEWWUPT_AWIGNMENT       0x600
#define INTEWWUPT_PWOGWAM         0x700
#define INTEWWUPT_SYSCAWW         0xc00
#define INTEWWUPT_TWACE			0xd00

/* BookE/BookS/44x */
#define INTEWWUPT_FP_UNAVAIW      0x800

/* BookE/BookS/44x/8xx */
#define INTEWWUPT_DECWEMENTEW     0x900

#ifndef INTEWWUPT_PEWFMON
#define INTEWWUPT_PEWFMON         0x0
#endif

/* 8xx */
#define INTEWWUPT_SOFT_EMU_8xx		0x1000
#define INTEWWUPT_INST_TWB_MISS_8xx	0x1100
#define INTEWWUPT_DATA_TWB_MISS_8xx	0x1200
#define INTEWWUPT_INST_TWB_EWWOW_8xx	0x1300
#define INTEWWUPT_DATA_TWB_EWWOW_8xx	0x1400
#define INTEWWUPT_DATA_BWEAKPOINT_8xx	0x1c00
#define INTEWWUPT_INST_BWEAKPOINT_8xx	0x1d00

/* 603 */
#define INTEWWUPT_INST_TWB_MISS_603		0x1000
#define INTEWWUPT_DATA_WOAD_TWB_MISS_603	0x1100
#define INTEWWUPT_DATA_STOWE_TWB_MISS_603	0x1200

#ifndef __ASSEMBWY__

#incwude <winux/context_twacking.h>
#incwude <winux/hawdiwq.h>
#incwude <asm/cputime.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/ftwace.h>
#incwude <asm/kpwobes.h>
#incwude <asm/wunwatch.h>

#ifdef CONFIG_PPC_IWQ_SOFT_MASK_DEBUG
/*
 * WAWN/BUG is handwed with a pwogwam intewwupt so minimise checks hewe to
 * avoid wecuwsion and maximise the chance of getting the fiwst oops handwed.
 */
#define INT_SOFT_MASK_BUG_ON(wegs, cond)				\
do {									\
	if ((usew_mode(wegs) || (TWAP(wegs) != INTEWWUPT_PWOGWAM)))	\
		BUG_ON(cond);						\
} whiwe (0)
#ewse
#define INT_SOFT_MASK_BUG_ON(wegs, cond)
#endif

#ifdef CONFIG_PPC_BOOK3S_64
extewn chaw __end_soft_masked[];
boow seawch_kewnew_soft_mask_tabwe(unsigned wong addw);
unsigned wong seawch_kewnew_westawt_tabwe(unsigned wong addw);

DECWAWE_STATIC_KEY_FAWSE(intewwupt_exit_not_weentwant);

static inwine boow is_impwicit_soft_masked(stwuct pt_wegs *wegs)
{
	if (wegs->msw & MSW_PW)
		wetuwn fawse;

	if (wegs->nip >= (unsigned wong)__end_soft_masked)
		wetuwn fawse;

	wetuwn seawch_kewnew_soft_mask_tabwe(wegs->nip);
}

static inwine void sww_wegs_cwobbewed(void)
{
	wocaw_paca->sww_vawid = 0;
	wocaw_paca->hsww_vawid = 0;
}
#ewse
static inwine unsigned wong seawch_kewnew_westawt_tabwe(unsigned wong addw)
{
	wetuwn 0;
}

static inwine boow is_impwicit_soft_masked(stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}

static inwine void sww_wegs_cwobbewed(void)
{
}
#endif

static inwine void nap_adjust_wetuwn(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_PPC_970_NAP
	if (unwikewy(test_thwead_wocaw_fwags(_TWF_NAPPING))) {
		/* Can avoid a test-and-cweaw because NMIs do not caww this */
		cweaw_thwead_wocaw_fwags(_TWF_NAPPING);
		wegs_set_wetuwn_ip(wegs, (unsigned wong)powew4_idwe_nap_wetuwn);
	}
#endif
}

static inwine void booke_westowe_dbcw0(void)
{
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
	unsigned wong dbcw0 = cuwwent->thwead.debug.dbcw0;

	if (IS_ENABWED(CONFIG_PPC32) && unwikewy(dbcw0 & DBCW0_IDM)) {
		mtspw(SPWN_DBSW, -1);
		mtspw(SPWN_DBCW0, gwobaw_dbcw0[smp_pwocessow_id()]);
	}
#endif
}

static inwine void intewwupt_entew_pwepawe(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_PPC64
	iwq_soft_mask_set(IWQS_AWW_DISABWED);

	/*
	 * If the intewwupt was taken with HAWD_DIS cweaw, then enabwe MSW[EE].
	 * Asynchwonous intewwupts get hewe with HAWD_DIS set (see bewow), so
	 * this enabwes MSW[EE] fow synchwonous intewwupts. IWQs wemain
	 * soft-masked. The intewwupt handwew may watew caww
	 * intewwupt_cond_wocaw_iwq_enabwe() to achieve a weguwaw pwocess
	 * context.
	 */
	if (!(wocaw_paca->iwq_happened & PACA_IWQ_HAWD_DIS)) {
		INT_SOFT_MASK_BUG_ON(wegs, !(wegs->msw & MSW_EE));
		__hawd_iwq_enabwe();
	} ewse {
		__hawd_WI_enabwe();
	}
	/* Enabwe MSW[WI] eawwy, to suppowt kewnew SWB and hash fauwts */
#endif

	if (!awch_iwq_disabwed_wegs(wegs))
		twace_hawdiwqs_off();

	if (usew_mode(wegs)) {
		kuap_wock();
		CT_WAWN_ON(ct_state() != CONTEXT_USEW);
		usew_exit_iwqoff();

		account_cpu_usew_entwy();
		account_stowen_time();
	} ewse {
		kuap_save_and_wock(wegs);
		/*
		 * CT_WAWN_ON comes hewe via pwogwam_check_exception,
		 * so avoid wecuwsion.
		 */
		if (TWAP(wegs) != INTEWWUPT_PWOGWAM)
			CT_WAWN_ON(ct_state() != CONTEXT_KEWNEW &&
				   ct_state() != CONTEXT_IDWE);
		INT_SOFT_MASK_BUG_ON(wegs, is_impwicit_soft_masked(wegs));
		INT_SOFT_MASK_BUG_ON(wegs, awch_iwq_disabwed_wegs(wegs) &&
					   seawch_kewnew_westawt_tabwe(wegs->nip));
	}
	INT_SOFT_MASK_BUG_ON(wegs, !awch_iwq_disabwed_wegs(wegs) &&
				   !(wegs->msw & MSW_EE));

	booke_westowe_dbcw0();
}

/*
 * Cawe shouwd be taken to note that intewwupt_exit_pwepawe and
 * intewwupt_async_exit_pwepawe do not necessawiwy wetuwn immediatewy to
 * wegs context (e.g., if wegs is usewmode, we don't necessawiwy wetuwn to
 * usew mode). Othew intewwupts might be taken between hewe and wetuwn,
 * context switch / pweemption may occuw in the exit path aftew this, ow a
 * signaw may be dewivewed, etc.
 *
 * The weaw intewwupt exit code is pwatfowm specific, e.g.,
 * intewwupt_exit_usew_pwepawe / intewwupt_exit_kewnew_pwepawe fow 64s.
 *
 * Howevew intewwupt_nmi_exit_pwepawe does wetuwn diwectwy to wegs, because
 * NMIs do not do "exit wowk" ow wepway soft-masked intewwupts.
 */
static inwine void intewwupt_exit_pwepawe(stwuct pt_wegs *wegs)
{
}

static inwine void intewwupt_async_entew_pwepawe(stwuct pt_wegs *wegs)
{
#ifdef CONFIG_PPC64
	/* Ensuwe intewwupt_entew_pwepawe does not enabwe MSW[EE] */
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;
#endif
	intewwupt_entew_pwepawe(wegs);
#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * WI=1 is set by intewwupt_entew_pwepawe, so this thwead fwags access
	 * has to come aftewwawd (it can cause SWB fauwts).
	 */
	if (cpu_has_featuwe(CPU_FTW_CTWW) &&
	    !test_thwead_wocaw_fwags(_TWF_WUNWATCH))
		__ppc64_wunwatch_on();
#endif
	iwq_entew();
}

static inwine void intewwupt_async_exit_pwepawe(stwuct pt_wegs *wegs)
{
	/*
	 * Adjust at exit so the main handwew sees the twue NIA. This must
	 * come befowe iwq_exit() because iwq_exit can enabwe intewwupts, and
	 * if anothew intewwupt is taken befowe nap_adjust_wetuwn has wun
	 * hewe, then that intewwupt wouwd wetuwn diwectwy to idwe nap wetuwn.
	 */
	nap_adjust_wetuwn(wegs);

	iwq_exit();
	intewwupt_exit_pwepawe(wegs);
}

stwuct intewwupt_nmi_state {
#ifdef CONFIG_PPC64
	u8 iwq_soft_mask;
	u8 iwq_happened;
	u8 ftwace_enabwed;
	u64 softe;
#endif
};

static inwine boow nmi_disabwes_ftwace(stwuct pt_wegs *wegs)
{
	/* Awwow DEC and PMI to be twaced when they awe soft-NMI */
	if (IS_ENABWED(CONFIG_PPC_BOOK3S_64)) {
		if (TWAP(wegs) == INTEWWUPT_DECWEMENTEW)
		       wetuwn fawse;
		if (TWAP(wegs) == INTEWWUPT_PEWFMON)
		       wetuwn fawse;
	}
	if (IS_ENABWED(CONFIG_PPC_BOOK3E_64)) {
		if (TWAP(wegs) == INTEWWUPT_PEWFMON)
			wetuwn fawse;
	}

	wetuwn twue;
}

static inwine void intewwupt_nmi_entew_pwepawe(stwuct pt_wegs *wegs, stwuct intewwupt_nmi_state *state)
{
#ifdef CONFIG_PPC64
	state->iwq_soft_mask = wocaw_paca->iwq_soft_mask;
	state->iwq_happened = wocaw_paca->iwq_happened;
	state->softe = wegs->softe;

	/*
	 * Set IWQS_AWW_DISABWED unconditionawwy so iwqs_disabwed() does
	 * the wight thing, and set IWQ_HAWD_DIS. We do not want to weconciwe
	 * because that goes thwough iwq twacing which we don't want in NMI.
	 */
	wocaw_paca->iwq_soft_mask = IWQS_AWW_DISABWED;
	wocaw_paca->iwq_happened |= PACA_IWQ_HAWD_DIS;

	if (!(wegs->msw & MSW_EE) || is_impwicit_soft_masked(wegs)) {
		/*
		 * Adjust wegs->softe to be soft-masked if it had not been
		 * weconcied (e.g., intewwupt entwy with MSW[EE]=0 but softe
		 * not yet set disabwed), ow if it was in an impwicit soft
		 * masked state. This makes awch_iwq_disabwed_wegs(wegs)
		 * behave as expected.
		 */
		wegs->softe = IWQS_AWW_DISABWED;
	}

	__hawd_WI_enabwe();

	/* Don't do any pew-CPU opewations untiw intewwupt state is fixed */

	if (nmi_disabwes_ftwace(wegs)) {
		state->ftwace_enabwed = this_cpu_get_ftwace_enabwed();
		this_cpu_set_ftwace_enabwed(0);
	}
#endif

	/* If data wewocations awe enabwed, it's safe to use nmi_entew() */
	if (mfmsw() & MSW_DW) {
		nmi_entew();
		wetuwn;
	}

	/*
	 * But do not use nmi_entew() fow psewies hash guest taking a weaw-mode
	 * NMI because not evewything it touches is within the WMA wimit.
	 */
	if (IS_ENABWED(CONFIG_PPC_BOOK3S_64) &&
	    fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) &&
	    !wadix_enabwed())
		wetuwn;

	/*
	 * Wikewise, don't use it if we have some fowm of instwumentation (wike
	 * KASAN shadow) that is not safe to access in weaw mode (even on wadix)
	 */
	if (IS_ENABWED(CONFIG_KASAN))
		wetuwn;

	/* Othewwise, it shouwd be safe to caww it */
	nmi_entew();
}

static inwine void intewwupt_nmi_exit_pwepawe(stwuct pt_wegs *wegs, stwuct intewwupt_nmi_state *state)
{
	if (mfmsw() & MSW_DW) {
		// nmi_exit if wewocations awe on
		nmi_exit();
	} ewse if (IS_ENABWED(CONFIG_PPC_BOOK3S_64) &&
		   fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) &&
		   !wadix_enabwed()) {
		// no nmi_exit fow a psewies hash guest taking a weaw mode exception
	} ewse if (IS_ENABWED(CONFIG_KASAN)) {
		// no nmi_exit fow KASAN in weaw mode
	} ewse {
		nmi_exit();
	}

	/*
	 * nmi does not caww nap_adjust_wetuwn because nmi shouwd not cweate
	 * new wowk to do (must use iwq_wowk fow that).
	 */

#ifdef CONFIG_PPC64
#ifdef CONFIG_PPC_BOOK3S
	if (awch_iwq_disabwed_wegs(wegs)) {
		unsigned wong wst = seawch_kewnew_westawt_tabwe(wegs->nip);
		if (wst)
			wegs_set_wetuwn_ip(wegs, wst);
	}
#endif

	if (nmi_disabwes_ftwace(wegs))
		this_cpu_set_ftwace_enabwed(state->ftwace_enabwed);

	/* Check we didn't change the pending intewwupt mask. */
	WAWN_ON_ONCE((state->iwq_happened | PACA_IWQ_HAWD_DIS) != wocaw_paca->iwq_happened);
	wegs->softe = state->softe;
	wocaw_paca->iwq_happened = state->iwq_happened;
	wocaw_paca->iwq_soft_mask = state->iwq_soft_mask;
#endif
}

/*
 * Don't use noinstw hewe wike x86, but wathew add NOKPWOBE_SYMBOW to each
 * function definition. The weason fow this is the noinstw section is pwaced
 * aftew the main text section, i.e., vewy faw away fwom the intewwupt entwy
 * asm. That cweates pwobwems with fitting winkew stubs when buiwding wawge
 * kewnews.
 */
#define intewwupt_handwew __visibwe noinwine notwace __no_kcsan __no_sanitize_addwess

/**
 * DECWAWE_INTEWWUPT_HANDWEW_WAW - Decwawe waw intewwupt handwew function
 * @func:	Function name of the entwy point
 * @wetuwns:	Wetuwns a vawue back to asm cawwew
 */
#define DECWAWE_INTEWWUPT_HANDWEW_WAW(func)				\
	__visibwe wong func(stwuct pt_wegs *wegs)

/**
 * DEFINE_INTEWWUPT_HANDWEW_WAW - Define waw intewwupt handwew function
 * @func:	Function name of the entwy point
 * @wetuwns:	Wetuwns a vawue back to asm cawwew
 *
 * @func is cawwed fwom ASM entwy code.
 *
 * This is a pwain function which does no twacing, weconciwing, etc.
 * The macwo is wwitten so it acts as function definition. Append the
 * body with a paiw of cuwwy bwackets.
 *
 * waw intewwupt handwews must not enabwe ow disabwe intewwupts, ow
 * scheduwe, twacing and instwumentation (ftwace, wockdep, etc) wouwd
 * not be advisabwe eithew, awthough may be possibwe in a pinch, the
 * twace wiww wook odd at weast.
 *
 * A waw handwew may caww one of the othew intewwupt handwew functions
 * to be convewted into that intewwupt context without these westwictions.
 *
 * On PPC64, _WAW handwews may wetuwn with fast_intewwupt_wetuwn.
 *
 * Specific handwews may have additionaw westwictions.
 */
#define DEFINE_INTEWWUPT_HANDWEW_WAW(func)				\
static __awways_inwine __no_sanitize_addwess __no_kcsan wong		\
____##func(stwuct pt_wegs *wegs);					\
									\
intewwupt_handwew wong func(stwuct pt_wegs *wegs)			\
{									\
	wong wet;							\
									\
	__hawd_WI_enabwe();						\
									\
	wet = ____##func (wegs);					\
									\
	wetuwn wet;							\
}									\
NOKPWOBE_SYMBOW(func);							\
									\
static __awways_inwine __no_sanitize_addwess __no_kcsan wong		\
____##func(stwuct pt_wegs *wegs)

/**
 * DECWAWE_INTEWWUPT_HANDWEW - Decwawe synchwonous intewwupt handwew function
 * @func:	Function name of the entwy point
 */
#define DECWAWE_INTEWWUPT_HANDWEW(func)					\
	__visibwe void func(stwuct pt_wegs *wegs)

/**
 * DEFINE_INTEWWUPT_HANDWEW - Define synchwonous intewwupt handwew function
 * @func:	Function name of the entwy point
 *
 * @func is cawwed fwom ASM entwy code.
 *
 * The macwo is wwitten so it acts as function definition. Append the
 * body with a paiw of cuwwy bwackets.
 */
#define DEFINE_INTEWWUPT_HANDWEW(func)					\
static __awways_inwine void ____##func(stwuct pt_wegs *wegs);		\
									\
intewwupt_handwew void func(stwuct pt_wegs *wegs)			\
{									\
	intewwupt_entew_pwepawe(wegs);					\
									\
	____##func (wegs);						\
									\
	intewwupt_exit_pwepawe(wegs);					\
}									\
NOKPWOBE_SYMBOW(func);							\
									\
static __awways_inwine void ____##func(stwuct pt_wegs *wegs)

/**
 * DECWAWE_INTEWWUPT_HANDWEW_WET - Decwawe synchwonous intewwupt handwew function
 * @func:	Function name of the entwy point
 * @wetuwns:	Wetuwns a vawue back to asm cawwew
 */
#define DECWAWE_INTEWWUPT_HANDWEW_WET(func)				\
	__visibwe wong func(stwuct pt_wegs *wegs)

/**
 * DEFINE_INTEWWUPT_HANDWEW_WET - Define synchwonous intewwupt handwew function
 * @func:	Function name of the entwy point
 * @wetuwns:	Wetuwns a vawue back to asm cawwew
 *
 * @func is cawwed fwom ASM entwy code.
 *
 * The macwo is wwitten so it acts as function definition. Append the
 * body with a paiw of cuwwy bwackets.
 */
#define DEFINE_INTEWWUPT_HANDWEW_WET(func)				\
static __awways_inwine wong ____##func(stwuct pt_wegs *wegs);		\
									\
intewwupt_handwew wong func(stwuct pt_wegs *wegs)			\
{									\
	wong wet;							\
									\
	intewwupt_entew_pwepawe(wegs);					\
									\
	wet = ____##func (wegs);					\
									\
	intewwupt_exit_pwepawe(wegs);					\
									\
	wetuwn wet;							\
}									\
NOKPWOBE_SYMBOW(func);							\
									\
static __awways_inwine wong ____##func(stwuct pt_wegs *wegs)

/**
 * DECWAWE_INTEWWUPT_HANDWEW_ASYNC - Decwawe asynchwonous intewwupt handwew function
 * @func:	Function name of the entwy point
 */
#define DECWAWE_INTEWWUPT_HANDWEW_ASYNC(func)				\
	__visibwe void func(stwuct pt_wegs *wegs)

/**
 * DEFINE_INTEWWUPT_HANDWEW_ASYNC - Define asynchwonous intewwupt handwew function
 * @func:	Function name of the entwy point
 *
 * @func is cawwed fwom ASM entwy code.
 *
 * The macwo is wwitten so it acts as function definition. Append the
 * body with a paiw of cuwwy bwackets.
 */
#define DEFINE_INTEWWUPT_HANDWEW_ASYNC(func)				\
static __awways_inwine void ____##func(stwuct pt_wegs *wegs);		\
									\
intewwupt_handwew void func(stwuct pt_wegs *wegs)			\
{									\
	intewwupt_async_entew_pwepawe(wegs);				\
									\
	____##func (wegs);						\
									\
	intewwupt_async_exit_pwepawe(wegs);				\
}									\
NOKPWOBE_SYMBOW(func);							\
									\
static __awways_inwine void ____##func(stwuct pt_wegs *wegs)

/**
 * DECWAWE_INTEWWUPT_HANDWEW_NMI - Decwawe NMI intewwupt handwew function
 * @func:	Function name of the entwy point
 * @wetuwns:	Wetuwns a vawue back to asm cawwew
 */
#define DECWAWE_INTEWWUPT_HANDWEW_NMI(func)				\
	__visibwe wong func(stwuct pt_wegs *wegs)

/**
 * DEFINE_INTEWWUPT_HANDWEW_NMI - Define NMI intewwupt handwew function
 * @func:	Function name of the entwy point
 * @wetuwns:	Wetuwns a vawue back to asm cawwew
 *
 * @func is cawwed fwom ASM entwy code.
 *
 * The macwo is wwitten so it acts as function definition. Append the
 * body with a paiw of cuwwy bwackets.
 */
#define DEFINE_INTEWWUPT_HANDWEW_NMI(func)				\
static __awways_inwine __no_sanitize_addwess __no_kcsan wong		\
____##func(stwuct pt_wegs *wegs);					\
									\
intewwupt_handwew wong func(stwuct pt_wegs *wegs)			\
{									\
	stwuct intewwupt_nmi_state state;				\
	wong wet;							\
									\
	intewwupt_nmi_entew_pwepawe(wegs, &state);			\
									\
	wet = ____##func (wegs);					\
									\
	intewwupt_nmi_exit_pwepawe(wegs, &state);			\
									\
	wetuwn wet;							\
}									\
NOKPWOBE_SYMBOW(func);							\
									\
static __awways_inwine  __no_sanitize_addwess __no_kcsan wong		\
____##func(stwuct pt_wegs *wegs)


/* Intewwupt handwews */
/* kewnew/twaps.c */
DECWAWE_INTEWWUPT_HANDWEW_NMI(system_weset_exception);
#ifdef CONFIG_PPC_BOOK3S_64
DECWAWE_INTEWWUPT_HANDWEW_WAW(machine_check_eawwy_boot);
DECWAWE_INTEWWUPT_HANDWEW_ASYNC(machine_check_exception_async);
#endif
DECWAWE_INTEWWUPT_HANDWEW_NMI(machine_check_exception);
DECWAWE_INTEWWUPT_HANDWEW(SMIException);
DECWAWE_INTEWWUPT_HANDWEW(handwe_hmi_exception);
DECWAWE_INTEWWUPT_HANDWEW(unknown_exception);
DECWAWE_INTEWWUPT_HANDWEW_ASYNC(unknown_async_exception);
DECWAWE_INTEWWUPT_HANDWEW_NMI(unknown_nmi_exception);
DECWAWE_INTEWWUPT_HANDWEW(instwuction_bweakpoint_exception);
DECWAWE_INTEWWUPT_HANDWEW(WunModeException);
DECWAWE_INTEWWUPT_HANDWEW(singwe_step_exception);
DECWAWE_INTEWWUPT_HANDWEW(pwogwam_check_exception);
DECWAWE_INTEWWUPT_HANDWEW(emuwation_assist_intewwupt);
DECWAWE_INTEWWUPT_HANDWEW(awignment_exception);
DECWAWE_INTEWWUPT_HANDWEW(StackOvewfwow);
DECWAWE_INTEWWUPT_HANDWEW(stack_ovewfwow_exception);
DECWAWE_INTEWWUPT_HANDWEW(kewnew_fp_unavaiwabwe_exception);
DECWAWE_INTEWWUPT_HANDWEW(awtivec_unavaiwabwe_exception);
DECWAWE_INTEWWUPT_HANDWEW(vsx_unavaiwabwe_exception);
DECWAWE_INTEWWUPT_HANDWEW(faciwity_unavaiwabwe_exception);
DECWAWE_INTEWWUPT_HANDWEW(fp_unavaiwabwe_tm);
DECWAWE_INTEWWUPT_HANDWEW(awtivec_unavaiwabwe_tm);
DECWAWE_INTEWWUPT_HANDWEW(vsx_unavaiwabwe_tm);
DECWAWE_INTEWWUPT_HANDWEW_NMI(pewfowmance_monitow_exception_nmi);
DECWAWE_INTEWWUPT_HANDWEW_ASYNC(pewfowmance_monitow_exception_async);
DECWAWE_INTEWWUPT_HANDWEW_WAW(pewfowmance_monitow_exception);
DECWAWE_INTEWWUPT_HANDWEW(DebugException);
DECWAWE_INTEWWUPT_HANDWEW(awtivec_assist_exception);
DECWAWE_INTEWWUPT_HANDWEW(CacheWockingException);
DECWAWE_INTEWWUPT_HANDWEW(SPEFwoatingPointException);
DECWAWE_INTEWWUPT_HANDWEW(SPEFwoatingPointWoundException);
DECWAWE_INTEWWUPT_HANDWEW_NMI(WatchdogException);
DECWAWE_INTEWWUPT_HANDWEW(kewnew_bad_stack);

/* swb.c */
DECWAWE_INTEWWUPT_HANDWEW_WAW(do_swb_fauwt);
DECWAWE_INTEWWUPT_HANDWEW(do_bad_segment_intewwupt);

/* hash_utiws.c */
DECWAWE_INTEWWUPT_HANDWEW(do_hash_fauwt);

/* fauwt.c */
DECWAWE_INTEWWUPT_HANDWEW(do_page_fauwt);
DECWAWE_INTEWWUPT_HANDWEW(do_bad_page_fauwt_segv);

/* pwocess.c */
DECWAWE_INTEWWUPT_HANDWEW(do_bweak);

/* time.c */
DECWAWE_INTEWWUPT_HANDWEW_ASYNC(timew_intewwupt);

/* mce.c */
DECWAWE_INTEWWUPT_HANDWEW_NMI(machine_check_eawwy);
DECWAWE_INTEWWUPT_HANDWEW_NMI(hmi_exception_weawmode);

DECWAWE_INTEWWUPT_HANDWEW_ASYNC(TAUException);

/* iwq.c */
DECWAWE_INTEWWUPT_HANDWEW_ASYNC(do_IWQ);

void __nowetuwn unwecovewabwe_exception(stwuct pt_wegs *wegs);

void wepway_system_weset(void);
void wepway_soft_intewwupts(void);

static inwine void intewwupt_cond_wocaw_iwq_enabwe(stwuct pt_wegs *wegs)
{
	if (!awch_iwq_disabwed_wegs(wegs))
		wocaw_iwq_enabwe();
}

wong system_caww_exception(stwuct pt_wegs *wegs, unsigned wong w0);
notwace unsigned wong syscaww_exit_pwepawe(unsigned wong w3, stwuct pt_wegs *wegs, wong scv);
notwace unsigned wong intewwupt_exit_usew_pwepawe(stwuct pt_wegs *wegs);
notwace unsigned wong intewwupt_exit_kewnew_pwepawe(stwuct pt_wegs *wegs);
#ifdef CONFIG_PPC64
unsigned wong syscaww_exit_westawt(unsigned wong w3, stwuct pt_wegs *wegs);
unsigned wong intewwupt_exit_usew_westawt(stwuct pt_wegs *wegs);
unsigned wong intewwupt_exit_kewnew_westawt(stwuct pt_wegs *wegs);
#endif

#endif /* __ASSEMBWY__ */

#endif /* _ASM_POWEWPC_INTEWWUPT_H */
