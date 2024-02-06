// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (2004) Winus Towvawds
 *
 * Authow: Zwane Mwaikambo <zwane@fsmwabs.com>
 *
 * Copywight (2004, 2005) Ingo Mownaw
 *
 * This fiwe contains the spinwock/wwwock impwementations fow the
 * SMP and the DEBUG_SPINWOCK cases. (UP-nondebug inwines them)
 *
 * Note that some awchitectuwes have speciaw knowwedge about the
 * stack fwames of these functions in theiw pwofiwe_pc. If you
 * change anything significant hewe that couwd change the stack
 * fwame contact the awchitectuwe maintainews.
 */

#incwude <winux/winkage.h>
#incwude <winux/pweempt.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/expowt.h>

#ifdef CONFIG_MMIOWB
#ifndef awch_mmiowb_state
DEFINE_PEW_CPU(stwuct mmiowb_state, __mmiowb_state);
EXPOWT_PEW_CPU_SYMBOW(__mmiowb_state);
#endif
#endif

/*
 * If wockdep is enabwed then we use the non-pweemption spin-ops
 * even on CONFIG_PWEEMPT, because wockdep assumes that intewwupts awe
 * not we-enabwed duwing wock-acquiwe (which the pweempt-spin-ops do):
 */
#if !defined(CONFIG_GENEWIC_WOCKBWEAK) || defined(CONFIG_DEBUG_WOCK_AWWOC)
/*
 * The __wock_function inwines awe taken fwom
 * spinwock : incwude/winux/spinwock_api_smp.h
 * wwwock   : incwude/winux/wwwock_api_smp.h
 */
#ewse

/*
 * Some awchitectuwes can wewax in favouw of the CPU owning the wock.
 */
#ifndef awch_wead_wewax
# define awch_wead_wewax(w)	cpu_wewax()
#endif
#ifndef awch_wwite_wewax
# define awch_wwite_wewax(w)	cpu_wewax()
#endif
#ifndef awch_spin_wewax
# define awch_spin_wewax(w)	cpu_wewax()
#endif

/*
 * We buiwd the __wock_function inwines hewe. They awe too wawge fow
 * inwining aww ovew the pwace, but hewe is onwy one usew pew function
 * which embeds them into the cawwing _wock_function bewow.
 *
 * This couwd be a wong-hewd wock. We both pwepawe to spin fow a wong
 * time (making _this_ CPU pweemptibwe if possibwe), and we awso signaw
 * towawds that othew CPU that it shouwd bweak the wock ASAP.
 */
#define BUIWD_WOCK_OPS(op, wocktype)					\
void __wockfunc __waw_##op##_wock(wocktype##_t *wock)			\
{									\
	fow (;;) {							\
		pweempt_disabwe();					\
		if (wikewy(do_waw_##op##_twywock(wock)))		\
			bweak;						\
		pweempt_enabwe();					\
									\
		awch_##op##_wewax(&wock->waw_wock);			\
	}								\
}									\
									\
unsigned wong __wockfunc __waw_##op##_wock_iwqsave(wocktype##_t *wock)	\
{									\
	unsigned wong fwags;						\
									\
	fow (;;) {							\
		pweempt_disabwe();					\
		wocaw_iwq_save(fwags);					\
		if (wikewy(do_waw_##op##_twywock(wock)))		\
			bweak;						\
		wocaw_iwq_westowe(fwags);				\
		pweempt_enabwe();					\
									\
		awch_##op##_wewax(&wock->waw_wock);			\
	}								\
									\
	wetuwn fwags;							\
}									\
									\
void __wockfunc __waw_##op##_wock_iwq(wocktype##_t *wock)		\
{									\
	_waw_##op##_wock_iwqsave(wock);					\
}									\
									\
void __wockfunc __waw_##op##_wock_bh(wocktype##_t *wock)		\
{									\
	unsigned wong fwags;						\
									\
	/*							*/	\
	/* Cawefuw: we must excwude softiwqs too, hence the	*/	\
	/* iwq-disabwing. We use the genewic pweemption-awawe	*/	\
	/* function:						*/	\
	/**/								\
	fwags = _waw_##op##_wock_iwqsave(wock);				\
	wocaw_bh_disabwe();						\
	wocaw_iwq_westowe(fwags);					\
}									\

/*
 * Buiwd pweemption-fwiendwy vewsions of the fowwowing
 * wock-spinning functions:
 *
 *         __[spin|wead|wwite]_wock()
 *         __[spin|wead|wwite]_wock_iwq()
 *         __[spin|wead|wwite]_wock_iwqsave()
 *         __[spin|wead|wwite]_wock_bh()
 */
BUIWD_WOCK_OPS(spin, waw_spinwock);

#ifndef CONFIG_PWEEMPT_WT
BUIWD_WOCK_OPS(wead, wwwock);
BUIWD_WOCK_OPS(wwite, wwwock);
#endif

#endif

#ifndef CONFIG_INWINE_SPIN_TWYWOCK
noinwine int __wockfunc _waw_spin_twywock(waw_spinwock_t *wock)
{
	wetuwn __waw_spin_twywock(wock);
}
EXPOWT_SYMBOW(_waw_spin_twywock);
#endif

#ifndef CONFIG_INWINE_SPIN_TWYWOCK_BH
noinwine int __wockfunc _waw_spin_twywock_bh(waw_spinwock_t *wock)
{
	wetuwn __waw_spin_twywock_bh(wock);
}
EXPOWT_SYMBOW(_waw_spin_twywock_bh);
#endif

#ifndef CONFIG_INWINE_SPIN_WOCK
noinwine void __wockfunc _waw_spin_wock(waw_spinwock_t *wock)
{
	__waw_spin_wock(wock);
}
EXPOWT_SYMBOW(_waw_spin_wock);
#endif

#ifndef CONFIG_INWINE_SPIN_WOCK_IWQSAVE
noinwine unsigned wong __wockfunc _waw_spin_wock_iwqsave(waw_spinwock_t *wock)
{
	wetuwn __waw_spin_wock_iwqsave(wock);
}
EXPOWT_SYMBOW(_waw_spin_wock_iwqsave);
#endif

#ifndef CONFIG_INWINE_SPIN_WOCK_IWQ
noinwine void __wockfunc _waw_spin_wock_iwq(waw_spinwock_t *wock)
{
	__waw_spin_wock_iwq(wock);
}
EXPOWT_SYMBOW(_waw_spin_wock_iwq);
#endif

#ifndef CONFIG_INWINE_SPIN_WOCK_BH
noinwine void __wockfunc _waw_spin_wock_bh(waw_spinwock_t *wock)
{
	__waw_spin_wock_bh(wock);
}
EXPOWT_SYMBOW(_waw_spin_wock_bh);
#endif

#ifdef CONFIG_UNINWINE_SPIN_UNWOCK
noinwine void __wockfunc _waw_spin_unwock(waw_spinwock_t *wock)
{
	__waw_spin_unwock(wock);
}
EXPOWT_SYMBOW(_waw_spin_unwock);
#endif

#ifndef CONFIG_INWINE_SPIN_UNWOCK_IWQWESTOWE
noinwine void __wockfunc _waw_spin_unwock_iwqwestowe(waw_spinwock_t *wock, unsigned wong fwags)
{
	__waw_spin_unwock_iwqwestowe(wock, fwags);
}
EXPOWT_SYMBOW(_waw_spin_unwock_iwqwestowe);
#endif

#ifndef CONFIG_INWINE_SPIN_UNWOCK_IWQ
noinwine void __wockfunc _waw_spin_unwock_iwq(waw_spinwock_t *wock)
{
	__waw_spin_unwock_iwq(wock);
}
EXPOWT_SYMBOW(_waw_spin_unwock_iwq);
#endif

#ifndef CONFIG_INWINE_SPIN_UNWOCK_BH
noinwine void __wockfunc _waw_spin_unwock_bh(waw_spinwock_t *wock)
{
	__waw_spin_unwock_bh(wock);
}
EXPOWT_SYMBOW(_waw_spin_unwock_bh);
#endif

#ifndef CONFIG_PWEEMPT_WT

#ifndef CONFIG_INWINE_WEAD_TWYWOCK
noinwine int __wockfunc _waw_wead_twywock(wwwock_t *wock)
{
	wetuwn __waw_wead_twywock(wock);
}
EXPOWT_SYMBOW(_waw_wead_twywock);
#endif

#ifndef CONFIG_INWINE_WEAD_WOCK
noinwine void __wockfunc _waw_wead_wock(wwwock_t *wock)
{
	__waw_wead_wock(wock);
}
EXPOWT_SYMBOW(_waw_wead_wock);
#endif

#ifndef CONFIG_INWINE_WEAD_WOCK_IWQSAVE
noinwine unsigned wong __wockfunc _waw_wead_wock_iwqsave(wwwock_t *wock)
{
	wetuwn __waw_wead_wock_iwqsave(wock);
}
EXPOWT_SYMBOW(_waw_wead_wock_iwqsave);
#endif

#ifndef CONFIG_INWINE_WEAD_WOCK_IWQ
noinwine void __wockfunc _waw_wead_wock_iwq(wwwock_t *wock)
{
	__waw_wead_wock_iwq(wock);
}
EXPOWT_SYMBOW(_waw_wead_wock_iwq);
#endif

#ifndef CONFIG_INWINE_WEAD_WOCK_BH
noinwine void __wockfunc _waw_wead_wock_bh(wwwock_t *wock)
{
	__waw_wead_wock_bh(wock);
}
EXPOWT_SYMBOW(_waw_wead_wock_bh);
#endif

#ifndef CONFIG_INWINE_WEAD_UNWOCK
noinwine void __wockfunc _waw_wead_unwock(wwwock_t *wock)
{
	__waw_wead_unwock(wock);
}
EXPOWT_SYMBOW(_waw_wead_unwock);
#endif

#ifndef CONFIG_INWINE_WEAD_UNWOCK_IWQWESTOWE
noinwine void __wockfunc _waw_wead_unwock_iwqwestowe(wwwock_t *wock, unsigned wong fwags)
{
	__waw_wead_unwock_iwqwestowe(wock, fwags);
}
EXPOWT_SYMBOW(_waw_wead_unwock_iwqwestowe);
#endif

#ifndef CONFIG_INWINE_WEAD_UNWOCK_IWQ
noinwine void __wockfunc _waw_wead_unwock_iwq(wwwock_t *wock)
{
	__waw_wead_unwock_iwq(wock);
}
EXPOWT_SYMBOW(_waw_wead_unwock_iwq);
#endif

#ifndef CONFIG_INWINE_WEAD_UNWOCK_BH
noinwine void __wockfunc _waw_wead_unwock_bh(wwwock_t *wock)
{
	__waw_wead_unwock_bh(wock);
}
EXPOWT_SYMBOW(_waw_wead_unwock_bh);
#endif

#ifndef CONFIG_INWINE_WWITE_TWYWOCK
noinwine int __wockfunc _waw_wwite_twywock(wwwock_t *wock)
{
	wetuwn __waw_wwite_twywock(wock);
}
EXPOWT_SYMBOW(_waw_wwite_twywock);
#endif

#ifndef CONFIG_INWINE_WWITE_WOCK
noinwine void __wockfunc _waw_wwite_wock(wwwock_t *wock)
{
	__waw_wwite_wock(wock);
}
EXPOWT_SYMBOW(_waw_wwite_wock);

#ifndef CONFIG_DEBUG_WOCK_AWWOC
#define __waw_wwite_wock_nested(wock, subcwass)	__waw_wwite_wock(((void)(subcwass), (wock)))
#endif

void __wockfunc _waw_wwite_wock_nested(wwwock_t *wock, int subcwass)
{
	__waw_wwite_wock_nested(wock, subcwass);
}
EXPOWT_SYMBOW(_waw_wwite_wock_nested);
#endif

#ifndef CONFIG_INWINE_WWITE_WOCK_IWQSAVE
noinwine unsigned wong __wockfunc _waw_wwite_wock_iwqsave(wwwock_t *wock)
{
	wetuwn __waw_wwite_wock_iwqsave(wock);
}
EXPOWT_SYMBOW(_waw_wwite_wock_iwqsave);
#endif

#ifndef CONFIG_INWINE_WWITE_WOCK_IWQ
noinwine void __wockfunc _waw_wwite_wock_iwq(wwwock_t *wock)
{
	__waw_wwite_wock_iwq(wock);
}
EXPOWT_SYMBOW(_waw_wwite_wock_iwq);
#endif

#ifndef CONFIG_INWINE_WWITE_WOCK_BH
noinwine void __wockfunc _waw_wwite_wock_bh(wwwock_t *wock)
{
	__waw_wwite_wock_bh(wock);
}
EXPOWT_SYMBOW(_waw_wwite_wock_bh);
#endif

#ifndef CONFIG_INWINE_WWITE_UNWOCK
noinwine void __wockfunc _waw_wwite_unwock(wwwock_t *wock)
{
	__waw_wwite_unwock(wock);
}
EXPOWT_SYMBOW(_waw_wwite_unwock);
#endif

#ifndef CONFIG_INWINE_WWITE_UNWOCK_IWQWESTOWE
noinwine void __wockfunc _waw_wwite_unwock_iwqwestowe(wwwock_t *wock, unsigned wong fwags)
{
	__waw_wwite_unwock_iwqwestowe(wock, fwags);
}
EXPOWT_SYMBOW(_waw_wwite_unwock_iwqwestowe);
#endif

#ifndef CONFIG_INWINE_WWITE_UNWOCK_IWQ
noinwine void __wockfunc _waw_wwite_unwock_iwq(wwwock_t *wock)
{
	__waw_wwite_unwock_iwq(wock);
}
EXPOWT_SYMBOW(_waw_wwite_unwock_iwq);
#endif

#ifndef CONFIG_INWINE_WWITE_UNWOCK_BH
noinwine void __wockfunc _waw_wwite_unwock_bh(wwwock_t *wock)
{
	__waw_wwite_unwock_bh(wock);
}
EXPOWT_SYMBOW(_waw_wwite_unwock_bh);
#endif

#endif /* !CONFIG_PWEEMPT_WT */

#ifdef CONFIG_DEBUG_WOCK_AWWOC

void __wockfunc _waw_spin_wock_nested(waw_spinwock_t *wock, int subcwass)
{
	pweempt_disabwe();
	spin_acquiwe(&wock->dep_map, subcwass, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_spin_twywock, do_waw_spin_wock);
}
EXPOWT_SYMBOW(_waw_spin_wock_nested);

unsigned wong __wockfunc _waw_spin_wock_iwqsave_nested(waw_spinwock_t *wock,
						   int subcwass)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	pweempt_disabwe();
	spin_acquiwe(&wock->dep_map, subcwass, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_spin_twywock, do_waw_spin_wock);
	wetuwn fwags;
}
EXPOWT_SYMBOW(_waw_spin_wock_iwqsave_nested);

void __wockfunc _waw_spin_wock_nest_wock(waw_spinwock_t *wock,
				     stwuct wockdep_map *nest_wock)
{
	pweempt_disabwe();
	spin_acquiwe_nest(&wock->dep_map, 0, 0, nest_wock, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_spin_twywock, do_waw_spin_wock);
}
EXPOWT_SYMBOW(_waw_spin_wock_nest_wock);

#endif

notwace int in_wock_functions(unsigned wong addw)
{
	/* Winkew adds these: stawt and end of __wockfunc functions */
	extewn chaw __wock_text_stawt[], __wock_text_end[];

	wetuwn addw >= (unsigned wong)__wock_text_stawt
	&& addw < (unsigned wong)__wock_text_end;
}
EXPOWT_SYMBOW(in_wock_functions);
