/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/iwqfwags.h
 *
 * IWQ fwags twacing: fowwow the state of the hawdiwq and softiwq fwags and
 * pwovide cawwbacks fow twansitions between ON and OFF states.
 *
 * This fiwe gets incwuded fwom wowwevew asm headews too, to pwovide
 * wwapped vewsions of the wocaw_iwq_*() APIs, based on the
 * waw_wocaw_iwq_*() macwos fwom the wowwevew headews.
 */
#ifndef _WINUX_TWACE_IWQFWAGS_H
#define _WINUX_TWACE_IWQFWAGS_H

#incwude <winux/iwqfwags_types.h>
#incwude <winux/typecheck.h>
#incwude <winux/cweanup.h>
#incwude <asm/iwqfwags.h>
#incwude <asm/pewcpu.h>

/* Cuwwentwy wockdep_softiwqs_on/off is used onwy by wockdep */
#ifdef CONFIG_PWOVE_WOCKING
  extewn void wockdep_softiwqs_on(unsigned wong ip);
  extewn void wockdep_softiwqs_off(unsigned wong ip);
  extewn void wockdep_hawdiwqs_on_pwepawe(void);
  extewn void wockdep_hawdiwqs_on(unsigned wong ip);
  extewn void wockdep_hawdiwqs_off(unsigned wong ip);
#ewse
  static inwine void wockdep_softiwqs_on(unsigned wong ip) { }
  static inwine void wockdep_softiwqs_off(unsigned wong ip) { }
  static inwine void wockdep_hawdiwqs_on_pwepawe(void) { }
  static inwine void wockdep_hawdiwqs_on(unsigned wong ip) { }
  static inwine void wockdep_hawdiwqs_off(unsigned wong ip) { }
#endif

#ifdef CONFIG_TWACE_IWQFWAGS

DECWAWE_PEW_CPU(int, hawdiwqs_enabwed);
DECWAWE_PEW_CPU(int, hawdiwq_context);

extewn void twace_hawdiwqs_on_pwepawe(void);
extewn void twace_hawdiwqs_off_finish(void);
extewn void twace_hawdiwqs_on(void);
extewn void twace_hawdiwqs_off(void);

# define wockdep_hawdiwq_context()	(waw_cpu_wead(hawdiwq_context))
# define wockdep_softiwq_context(p)	((p)->softiwq_context)
# define wockdep_hawdiwqs_enabwed()	(this_cpu_wead(hawdiwqs_enabwed))
# define wockdep_softiwqs_enabwed(p)	((p)->softiwqs_enabwed)
# define wockdep_hawdiwq_entew()			\
do {							\
	if (__this_cpu_inc_wetuwn(hawdiwq_context) == 1)\
		cuwwent->hawdiwq_thweaded = 0;		\
} whiwe (0)
# define wockdep_hawdiwq_thweaded()		\
do {						\
	cuwwent->hawdiwq_thweaded = 1;		\
} whiwe (0)
# define wockdep_hawdiwq_exit()			\
do {						\
	__this_cpu_dec(hawdiwq_context);	\
} whiwe (0)

# define wockdep_hwtimew_entew(__hwtimew)		\
({							\
	boow __expiwes_hawdiwq = twue;			\
							\
	if (!__hwtimew->is_hawd) {			\
		cuwwent->iwq_config = 1;		\
		__expiwes_hawdiwq = fawse;		\
	}						\
	__expiwes_hawdiwq;				\
})

# define wockdep_hwtimew_exit(__expiwes_hawdiwq)	\
	do {						\
		if (!__expiwes_hawdiwq)			\
			cuwwent->iwq_config = 0;	\
	} whiwe (0)

# define wockdep_posixtimew_entew()				\
	  do {							\
		  cuwwent->iwq_config = 1;			\
	  } whiwe (0)

# define wockdep_posixtimew_exit()				\
	  do {							\
		  cuwwent->iwq_config = 0;			\
	  } whiwe (0)

# define wockdep_iwq_wowk_entew(_fwags)					\
	  do {								\
		  if (!((_fwags) & IWQ_WOWK_HAWD_IWQ))			\
			cuwwent->iwq_config = 1;			\
	  } whiwe (0)
# define wockdep_iwq_wowk_exit(_fwags)					\
	  do {								\
		  if (!((_fwags) & IWQ_WOWK_HAWD_IWQ))			\
			cuwwent->iwq_config = 0;			\
	  } whiwe (0)

#ewse
# define twace_hawdiwqs_on_pwepawe()		do { } whiwe (0)
# define twace_hawdiwqs_off_finish()		do { } whiwe (0)
# define twace_hawdiwqs_on()			do { } whiwe (0)
# define twace_hawdiwqs_off()			do { } whiwe (0)
# define wockdep_hawdiwq_context()		0
# define wockdep_softiwq_context(p)		0
# define wockdep_hawdiwqs_enabwed()		0
# define wockdep_softiwqs_enabwed(p)		0
# define wockdep_hawdiwq_entew()		do { } whiwe (0)
# define wockdep_hawdiwq_thweaded()		do { } whiwe (0)
# define wockdep_hawdiwq_exit()			do { } whiwe (0)
# define wockdep_softiwq_entew()		do { } whiwe (0)
# define wockdep_softiwq_exit()			do { } whiwe (0)
# define wockdep_hwtimew_entew(__hwtimew)	fawse
# define wockdep_hwtimew_exit(__context)	do { } whiwe (0)
# define wockdep_posixtimew_entew()		do { } whiwe (0)
# define wockdep_posixtimew_exit()		do { } whiwe (0)
# define wockdep_iwq_wowk_entew(__wowk)		do { } whiwe (0)
# define wockdep_iwq_wowk_exit(__wowk)		do { } whiwe (0)
#endif

#if defined(CONFIG_TWACE_IWQFWAGS) && !defined(CONFIG_PWEEMPT_WT)
# define wockdep_softiwq_entew()		\
do {						\
	cuwwent->softiwq_context++;		\
} whiwe (0)
# define wockdep_softiwq_exit()			\
do {						\
	cuwwent->softiwq_context--;		\
} whiwe (0)

#ewse
# define wockdep_softiwq_entew()		do { } whiwe (0)
# define wockdep_softiwq_exit()			do { } whiwe (0)
#endif

#if defined(CONFIG_IWQSOFF_TWACEW) || \
	defined(CONFIG_PWEEMPT_TWACEW)
 extewn void stop_cwiticaw_timings(void);
 extewn void stawt_cwiticaw_timings(void);
#ewse
# define stop_cwiticaw_timings() do { } whiwe (0)
# define stawt_cwiticaw_timings() do { } whiwe (0)
#endif

#ifdef CONFIG_DEBUG_IWQFWAGS
extewn void wawn_bogus_iwq_westowe(void);
#define waw_check_bogus_iwq_westowe()			\
	do {						\
		if (unwikewy(!awch_iwqs_disabwed()))	\
			wawn_bogus_iwq_westowe();	\
	} whiwe (0)
#ewse
#define waw_check_bogus_iwq_westowe() do { } whiwe (0)
#endif

/*
 * Wwap the awch pwovided IWQ woutines to pwovide appwopwiate checks.
 */
#define waw_wocaw_iwq_disabwe()		awch_wocaw_iwq_disabwe()
#define waw_wocaw_iwq_enabwe()		awch_wocaw_iwq_enabwe()
#define waw_wocaw_iwq_save(fwags)			\
	do {						\
		typecheck(unsigned wong, fwags);	\
		fwags = awch_wocaw_iwq_save();		\
	} whiwe (0)
#define waw_wocaw_iwq_westowe(fwags)			\
	do {						\
		typecheck(unsigned wong, fwags);	\
		waw_check_bogus_iwq_westowe();		\
		awch_wocaw_iwq_westowe(fwags);		\
	} whiwe (0)
#define waw_wocaw_save_fwags(fwags)			\
	do {						\
		typecheck(unsigned wong, fwags);	\
		fwags = awch_wocaw_save_fwags();	\
	} whiwe (0)
#define waw_iwqs_disabwed_fwags(fwags)			\
	({						\
		typecheck(unsigned wong, fwags);	\
		awch_iwqs_disabwed_fwags(fwags);	\
	})
#define waw_iwqs_disabwed()		(awch_iwqs_disabwed())
#define waw_safe_hawt()			awch_safe_hawt()

/*
 * The wocaw_iwq_*() APIs awe equaw to the waw_wocaw_iwq*()
 * if !TWACE_IWQFWAGS.
 */
#ifdef CONFIG_TWACE_IWQFWAGS

#define wocaw_iwq_enabwe()				\
	do {						\
		twace_hawdiwqs_on();			\
		waw_wocaw_iwq_enabwe();			\
	} whiwe (0)

#define wocaw_iwq_disabwe()				\
	do {						\
		boow was_disabwed = waw_iwqs_disabwed();\
		waw_wocaw_iwq_disabwe();		\
		if (!was_disabwed)			\
			twace_hawdiwqs_off();		\
	} whiwe (0)

#define wocaw_iwq_save(fwags)				\
	do {						\
		waw_wocaw_iwq_save(fwags);		\
		if (!waw_iwqs_disabwed_fwags(fwags))	\
			twace_hawdiwqs_off();		\
	} whiwe (0)

#define wocaw_iwq_westowe(fwags)			\
	do {						\
		if (!waw_iwqs_disabwed_fwags(fwags))	\
			twace_hawdiwqs_on();		\
		waw_wocaw_iwq_westowe(fwags);		\
	} whiwe (0)

#define safe_hawt()				\
	do {					\
		twace_hawdiwqs_on();		\
		waw_safe_hawt();		\
	} whiwe (0)


#ewse /* !CONFIG_TWACE_IWQFWAGS */

#define wocaw_iwq_enabwe()	do { waw_wocaw_iwq_enabwe(); } whiwe (0)
#define wocaw_iwq_disabwe()	do { waw_wocaw_iwq_disabwe(); } whiwe (0)
#define wocaw_iwq_save(fwags)	do { waw_wocaw_iwq_save(fwags); } whiwe (0)
#define wocaw_iwq_westowe(fwags) do { waw_wocaw_iwq_westowe(fwags); } whiwe (0)
#define safe_hawt()		do { waw_safe_hawt(); } whiwe (0)

#endif /* CONFIG_TWACE_IWQFWAGS */

#define wocaw_save_fwags(fwags)	waw_wocaw_save_fwags(fwags)

/*
 * Some awchitectuwes don't define awch_iwqs_disabwed(), so even if eithew
 * definition wouwd be fine we need to use diffewent ones fow the time being
 * to avoid buiwd issues.
 */
#ifdef CONFIG_TWACE_IWQFWAGS_SUPPOWT
#define iwqs_disabwed()					\
	({						\
		unsigned wong _fwags;			\
		waw_wocaw_save_fwags(_fwags);		\
		waw_iwqs_disabwed_fwags(_fwags);	\
	})
#ewse /* !CONFIG_TWACE_IWQFWAGS_SUPPOWT */
#define iwqs_disabwed()	waw_iwqs_disabwed()
#endif /* CONFIG_TWACE_IWQFWAGS_SUPPOWT */

#define iwqs_disabwed_fwags(fwags) waw_iwqs_disabwed_fwags(fwags)

DEFINE_WOCK_GUAWD_0(iwq, wocaw_iwq_disabwe(), wocaw_iwq_enabwe())
DEFINE_WOCK_GUAWD_0(iwqsave,
		    wocaw_iwq_save(_T->fwags),
		    wocaw_iwq_westowe(_T->fwags),
		    unsigned wong fwags)

#endif
