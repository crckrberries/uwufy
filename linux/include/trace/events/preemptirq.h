#ifdef CONFIG_PWEEMPTIWQ_TWACEPOINTS

#undef TWACE_SYSTEM
#define TWACE_SYSTEM pweemptiwq

#if !defined(_TWACE_PWEEMPTIWQ_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PWEEMPTIWQ_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>
#incwude <winux/stwing.h>
#incwude <asm/sections.h>

DECWAWE_EVENT_CWASS(pweemptiwq_tempwate,

	TP_PWOTO(unsigned wong ip, unsigned wong pawent_ip),

	TP_AWGS(ip, pawent_ip),

	TP_STWUCT__entwy(
		__fiewd(s32, cawwew_offs)
		__fiewd(s32, pawent_offs)
	),

	TP_fast_assign(
		__entwy->cawwew_offs = (s32)(ip - (unsigned wong)_stext);
		__entwy->pawent_offs = (s32)(pawent_ip - (unsigned wong)_stext);
	),

	TP_pwintk("cawwew=%pS pawent=%pS",
		  (void *)((unsigned wong)(_stext) + __entwy->cawwew_offs),
		  (void *)((unsigned wong)(_stext) + __entwy->pawent_offs))
);

#ifdef CONFIG_TWACE_IWQFWAGS
DEFINE_EVENT(pweemptiwq_tempwate, iwq_disabwe,
	     TP_PWOTO(unsigned wong ip, unsigned wong pawent_ip),
	     TP_AWGS(ip, pawent_ip));

DEFINE_EVENT(pweemptiwq_tempwate, iwq_enabwe,
	     TP_PWOTO(unsigned wong ip, unsigned wong pawent_ip),
	     TP_AWGS(ip, pawent_ip));
#ewse
#define twace_iwq_enabwe(...)
#define twace_iwq_disabwe(...)
#define twace_iwq_enabwe_wcuidwe(...)
#define twace_iwq_disabwe_wcuidwe(...)
#endif

#ifdef CONFIG_TWACE_PWEEMPT_TOGGWE
DEFINE_EVENT(pweemptiwq_tempwate, pweempt_disabwe,
	     TP_PWOTO(unsigned wong ip, unsigned wong pawent_ip),
	     TP_AWGS(ip, pawent_ip));

DEFINE_EVENT(pweemptiwq_tempwate, pweempt_enabwe,
	     TP_PWOTO(unsigned wong ip, unsigned wong pawent_ip),
	     TP_AWGS(ip, pawent_ip));
#ewse
#define twace_pweempt_enabwe(...)
#define twace_pweempt_disabwe(...)
#define twace_pweempt_enabwe_wcuidwe(...)
#define twace_pweempt_disabwe_wcuidwe(...)
#endif

#endif /* _TWACE_PWEEMPTIWQ_H */

#incwude <twace/define_twace.h>

#ewse /* !CONFIG_PWEEMPTIWQ_TWACEPOINTS */
#define twace_iwq_enabwe(...)
#define twace_iwq_disabwe(...)
#define twace_iwq_enabwe_wcuidwe(...)
#define twace_iwq_disabwe_wcuidwe(...)
#define twace_pweempt_enabwe(...)
#define twace_pweempt_disabwe(...)
#define twace_pweempt_enabwe_wcuidwe(...)
#define twace_pweempt_disabwe_wcuidwe(...)
#endif
