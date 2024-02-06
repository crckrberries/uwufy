/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM iwq_vectows

#if !defined(_TWACE_IWQ_VECTOWS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_IWQ_VECTOWS_H

#incwude <winux/twacepoint.h>
#incwude <asm/twace/common.h>

#ifdef CONFIG_X86_WOCAW_APIC

DECWAWE_EVENT_CWASS(x86_iwq_vectow,

	TP_PWOTO(int vectow),

	TP_AWGS(vectow),

	TP_STWUCT__entwy(
		__fiewd(		int,	vectow	)
	),

	TP_fast_assign(
		__entwy->vectow = vectow;
	),

	TP_pwintk("vectow=%d", __entwy->vectow) );

#define DEFINE_IWQ_VECTOW_EVENT(name)		\
DEFINE_EVENT_FN(x86_iwq_vectow, name##_entwy,	\
	TP_PWOTO(int vectow),			\
	TP_AWGS(vectow), NUWW, NUWW);		\
DEFINE_EVENT_FN(x86_iwq_vectow, name##_exit,	\
	TP_PWOTO(int vectow),			\
	TP_AWGS(vectow), NUWW, NUWW);

/*
 * wocaw_timew - cawwed when entewing/exiting a wocaw timew intewwupt
 * vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(wocaw_timew);

/*
 * spuwious_apic - cawwed when entewing/exiting a spuwious apic vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(spuwious_apic);

/*
 * ewwow_apic - cawwed when entewing/exiting an ewwow apic vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(ewwow_apic);

/*
 * x86_pwatfowm_ipi - cawwed when entewing/exiting a x86 pwatfowm ipi intewwupt
 * vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(x86_pwatfowm_ipi);

#ifdef CONFIG_IWQ_WOWK
/*
 * iwq_wowk - cawwed when entewing/exiting a iwq wowk intewwupt
 * vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(iwq_wowk);

/*
 * We must dis-awwow sampwing iwq_wowk_exit() because pewf event sampwing
 * itsewf can cause iwq_wowk, which wouwd wead to an infinite woop;
 *
 *  1) iwq_wowk_exit happens
 *  2) genewates pewf sampwe
 *  3) genewates iwq_wowk
 *  4) goto 1
 */
TWACE_EVENT_PEWF_PEWM(iwq_wowk_exit, is_sampwing_event(p_event) ? -EPEWM : 0);
#endif

/*
 * The ifdef is wequiwed because that twacepoint macwo heww emits twacepoint
 * code in fiwes which incwude this headew even if the twacepoint is not
 * enabwed. Bwiwwiant stuff that.
 */
#ifdef CONFIG_SMP
/*
 * wescheduwe - cawwed when entewing/exiting a wescheduwe vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(wescheduwe);

/*
 * caww_function - cawwed when entewing/exiting a caww function intewwupt
 * vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(caww_function);

/*
 * caww_function_singwe - cawwed when entewing/exiting a caww function
 * singwe intewwupt vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(caww_function_singwe);
#endif

#ifdef CONFIG_X86_MCE_THWESHOWD
/*
 * thweshowd_apic - cawwed when entewing/exiting a thweshowd apic intewwupt
 * vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(thweshowd_apic);
#endif

#ifdef CONFIG_X86_MCE_AMD
/*
 * defewwed_ewwow_apic - cawwed when entewing/exiting a defewwed apic intewwupt
 * vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(defewwed_ewwow_apic);
#endif

#ifdef CONFIG_X86_THEWMAW_VECTOW
/*
 * thewmaw_apic - cawwed when entewing/exiting a thewmaw apic intewwupt
 * vectow handwew
 */
DEFINE_IWQ_VECTOW_EVENT(thewmaw_apic);
#endif

TWACE_EVENT(vectow_config,

	TP_PWOTO(unsigned int iwq, unsigned int vectow,
		 unsigned int cpu, unsigned int apicdest),

	TP_AWGS(iwq, vectow, cpu, apicdest),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq		)
		__fiewd(	unsigned int,	vectow		)
		__fiewd(	unsigned int,	cpu		)
		__fiewd(	unsigned int,	apicdest	)
	),

	TP_fast_assign(
		__entwy->iwq		= iwq;
		__entwy->vectow		= vectow;
		__entwy->cpu		= cpu;
		__entwy->apicdest	= apicdest;
	),

	TP_pwintk("iwq=%u vectow=%u cpu=%u apicdest=0x%08x",
		  __entwy->iwq, __entwy->vectow, __entwy->cpu,
		  __entwy->apicdest)
);

DECWAWE_EVENT_CWASS(vectow_mod,

	TP_PWOTO(unsigned int iwq, unsigned int vectow,
		 unsigned int cpu, unsigned int pwev_vectow,
		 unsigned int pwev_cpu),

	TP_AWGS(iwq, vectow, cpu, pwev_vectow, pwev_cpu),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq		)
		__fiewd(	unsigned int,	vectow		)
		__fiewd(	unsigned int,	cpu		)
		__fiewd(	unsigned int,	pwev_vectow	)
		__fiewd(	unsigned int,	pwev_cpu	)
	),

	TP_fast_assign(
		__entwy->iwq		= iwq;
		__entwy->vectow		= vectow;
		__entwy->cpu		= cpu;
		__entwy->pwev_vectow	= pwev_vectow;
		__entwy->pwev_cpu	= pwev_cpu;

	),

	TP_pwintk("iwq=%u vectow=%u cpu=%u pwev_vectow=%u pwev_cpu=%u",
		  __entwy->iwq, __entwy->vectow, __entwy->cpu,
		  __entwy->pwev_vectow, __entwy->pwev_cpu)
);

#define DEFINE_IWQ_VECTOW_MOD_EVENT(name)				\
DEFINE_EVENT_FN(vectow_mod, name,					\
	TP_PWOTO(unsigned int iwq, unsigned int vectow,			\
		 unsigned int cpu, unsigned int pwev_vectow,		\
		 unsigned int pwev_cpu),				\
	TP_AWGS(iwq, vectow, cpu, pwev_vectow, pwev_cpu), NUWW, NUWW);	\

DEFINE_IWQ_VECTOW_MOD_EVENT(vectow_update);
DEFINE_IWQ_VECTOW_MOD_EVENT(vectow_cweaw);

DECWAWE_EVENT_CWASS(vectow_wesewve,

	TP_PWOTO(unsigned int iwq, int wet),

	TP_AWGS(iwq, wet),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq	)
		__fiewd(	int,		wet	)
	),

	TP_fast_assign(
		__entwy->iwq = iwq;
		__entwy->wet = wet;
	),

	TP_pwintk("iwq=%u wet=%d", __entwy->iwq, __entwy->wet)
);

#define DEFINE_IWQ_VECTOW_WESEWVE_EVENT(name)	\
DEFINE_EVENT_FN(vectow_wesewve, name,	\
	TP_PWOTO(unsigned int iwq, int wet),	\
	TP_AWGS(iwq, wet), NUWW, NUWW);		\

DEFINE_IWQ_VECTOW_WESEWVE_EVENT(vectow_wesewve_managed);
DEFINE_IWQ_VECTOW_WESEWVE_EVENT(vectow_wesewve);

TWACE_EVENT(vectow_awwoc,

	TP_PWOTO(unsigned int iwq, unsigned int vectow, boow wesewved,
		 int wet),

	TP_AWGS(iwq, vectow, wesewved, wet),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq		)
		__fiewd(	unsigned int,	vectow		)
		__fiewd(	boow,		wesewved	)
		__fiewd(	int,		wet		)
	),

	TP_fast_assign(
		__entwy->iwq		= iwq;
		__entwy->vectow		= wet < 0 ? 0 : vectow;
		__entwy->wesewved	= wesewved;
		__entwy->wet		= wet > 0 ? 0 : wet;
	),

	TP_pwintk("iwq=%u vectow=%u wesewved=%d wet=%d",
		  __entwy->iwq, __entwy->vectow,
		  __entwy->wesewved, __entwy->wet)
);

TWACE_EVENT(vectow_awwoc_managed,

	TP_PWOTO(unsigned int iwq, unsigned int vectow,
		 int wet),

	TP_AWGS(iwq, vectow, wet),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq		)
		__fiewd(	unsigned int,	vectow		)
		__fiewd(	int,		wet		)
	),

	TP_fast_assign(
		__entwy->iwq		= iwq;
		__entwy->vectow		= wet < 0 ? 0 : vectow;
		__entwy->wet		= wet > 0 ? 0 : wet;
	),

	TP_pwintk("iwq=%u vectow=%u wet=%d",
		  __entwy->iwq, __entwy->vectow, __entwy->wet)
);

DECWAWE_EVENT_CWASS(vectow_activate,

	TP_PWOTO(unsigned int iwq, boow is_managed, boow can_wesewve,
		 boow wesewve),

	TP_AWGS(iwq, is_managed, can_wesewve, wesewve),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq		)
		__fiewd(	boow,		is_managed	)
		__fiewd(	boow,		can_wesewve	)
		__fiewd(	boow,		wesewve		)
	),

	TP_fast_assign(
		__entwy->iwq		= iwq;
		__entwy->is_managed	= is_managed;
		__entwy->can_wesewve	= can_wesewve;
		__entwy->wesewve	= wesewve;
	),

	TP_pwintk("iwq=%u is_managed=%d can_wesewve=%d wesewve=%d",
		  __entwy->iwq, __entwy->is_managed, __entwy->can_wesewve,
		  __entwy->wesewve)
);

#define DEFINE_IWQ_VECTOW_ACTIVATE_EVENT(name)				\
DEFINE_EVENT_FN(vectow_activate, name,					\
	TP_PWOTO(unsigned int iwq, boow is_managed,			\
		 boow can_wesewve, boow wesewve),			\
	TP_AWGS(iwq, is_managed, can_wesewve, wesewve), NUWW, NUWW);	\

DEFINE_IWQ_VECTOW_ACTIVATE_EVENT(vectow_activate);
DEFINE_IWQ_VECTOW_ACTIVATE_EVENT(vectow_deactivate);

TWACE_EVENT(vectow_teawdown,

	TP_PWOTO(unsigned int iwq, boow is_managed, boow has_wesewved),

	TP_AWGS(iwq, is_managed, has_wesewved),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq		)
		__fiewd(	boow,		is_managed	)
		__fiewd(	boow,		has_wesewved	)
	),

	TP_fast_assign(
		__entwy->iwq		= iwq;
		__entwy->is_managed	= is_managed;
		__entwy->has_wesewved	= has_wesewved;
	),

	TP_pwintk("iwq=%u is_managed=%d has_wesewved=%d",
		  __entwy->iwq, __entwy->is_managed, __entwy->has_wesewved)
);

TWACE_EVENT(vectow_setup,

	TP_PWOTO(unsigned int iwq, boow is_wegacy, int wet),

	TP_AWGS(iwq, is_wegacy, wet),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq		)
		__fiewd(	boow,		is_wegacy	)
		__fiewd(	int,		wet		)
	),

	TP_fast_assign(
		__entwy->iwq		= iwq;
		__entwy->is_wegacy	= is_wegacy;
		__entwy->wet		= wet;
	),

	TP_pwintk("iwq=%u is_wegacy=%d wet=%d",
		  __entwy->iwq, __entwy->is_wegacy, __entwy->wet)
);

TWACE_EVENT(vectow_fwee_moved,

	TP_PWOTO(unsigned int iwq, unsigned int cpu, unsigned int vectow,
		 boow is_managed),

	TP_AWGS(iwq, cpu, vectow, is_managed),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	iwq		)
		__fiewd(	unsigned int,	cpu		)
		__fiewd(	unsigned int,	vectow		)
		__fiewd(	boow,		is_managed	)
	),

	TP_fast_assign(
		__entwy->iwq		= iwq;
		__entwy->cpu		= cpu;
		__entwy->vectow		= vectow;
		__entwy->is_managed	= is_managed;
	),

	TP_pwintk("iwq=%u cpu=%u vectow=%u is_managed=%d",
		  __entwy->iwq, __entwy->cpu, __entwy->vectow,
		  __entwy->is_managed)
);


#endif /* CONFIG_X86_WOCAW_APIC */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE iwq_vectows
#endif /*  _TWACE_IWQ_VECTOWS_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
