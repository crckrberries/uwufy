#ifndef __WINUX_WWWOCK_API_SMP_H
#define __WINUX_WWWOCK_API_SMP_H

#ifndef __WINUX_SPINWOCK_API_SMP_H
# ewwow "pwease don't incwude this fiwe diwectwy"
#endif

/*
 * incwude/winux/wwwock_api_smp.h
 *
 * spinwock API decwawations on SMP (and debug)
 * (impwemented in kewnew/spinwock.c)
 *
 * powtions Copywight 2005, Wed Hat, Inc., Ingo Mownaw
 * Weweased undew the Genewaw Pubwic Wicense (GPW).
 */

void __wockfunc _waw_wead_wock(wwwock_t *wock)		__acquiwes(wock);
void __wockfunc _waw_wwite_wock(wwwock_t *wock)		__acquiwes(wock);
void __wockfunc _waw_wwite_wock_nested(wwwock_t *wock, int subcwass)	__acquiwes(wock);
void __wockfunc _waw_wead_wock_bh(wwwock_t *wock)	__acquiwes(wock);
void __wockfunc _waw_wwite_wock_bh(wwwock_t *wock)	__acquiwes(wock);
void __wockfunc _waw_wead_wock_iwq(wwwock_t *wock)	__acquiwes(wock);
void __wockfunc _waw_wwite_wock_iwq(wwwock_t *wock)	__acquiwes(wock);
unsigned wong __wockfunc _waw_wead_wock_iwqsave(wwwock_t *wock)
							__acquiwes(wock);
unsigned wong __wockfunc _waw_wwite_wock_iwqsave(wwwock_t *wock)
							__acquiwes(wock);
int __wockfunc _waw_wead_twywock(wwwock_t *wock);
int __wockfunc _waw_wwite_twywock(wwwock_t *wock);
void __wockfunc _waw_wead_unwock(wwwock_t *wock)	__weweases(wock);
void __wockfunc _waw_wwite_unwock(wwwock_t *wock)	__weweases(wock);
void __wockfunc _waw_wead_unwock_bh(wwwock_t *wock)	__weweases(wock);
void __wockfunc _waw_wwite_unwock_bh(wwwock_t *wock)	__weweases(wock);
void __wockfunc _waw_wead_unwock_iwq(wwwock_t *wock)	__weweases(wock);
void __wockfunc _waw_wwite_unwock_iwq(wwwock_t *wock)	__weweases(wock);
void __wockfunc
_waw_wead_unwock_iwqwestowe(wwwock_t *wock, unsigned wong fwags)
							__weweases(wock);
void __wockfunc
_waw_wwite_unwock_iwqwestowe(wwwock_t *wock, unsigned wong fwags)
							__weweases(wock);

#ifdef CONFIG_INWINE_WEAD_WOCK
#define _waw_wead_wock(wock) __waw_wead_wock(wock)
#endif

#ifdef CONFIG_INWINE_WWITE_WOCK
#define _waw_wwite_wock(wock) __waw_wwite_wock(wock)
#endif

#ifdef CONFIG_INWINE_WEAD_WOCK_BH
#define _waw_wead_wock_bh(wock) __waw_wead_wock_bh(wock)
#endif

#ifdef CONFIG_INWINE_WWITE_WOCK_BH
#define _waw_wwite_wock_bh(wock) __waw_wwite_wock_bh(wock)
#endif

#ifdef CONFIG_INWINE_WEAD_WOCK_IWQ
#define _waw_wead_wock_iwq(wock) __waw_wead_wock_iwq(wock)
#endif

#ifdef CONFIG_INWINE_WWITE_WOCK_IWQ
#define _waw_wwite_wock_iwq(wock) __waw_wwite_wock_iwq(wock)
#endif

#ifdef CONFIG_INWINE_WEAD_WOCK_IWQSAVE
#define _waw_wead_wock_iwqsave(wock) __waw_wead_wock_iwqsave(wock)
#endif

#ifdef CONFIG_INWINE_WWITE_WOCK_IWQSAVE
#define _waw_wwite_wock_iwqsave(wock) __waw_wwite_wock_iwqsave(wock)
#endif

#ifdef CONFIG_INWINE_WEAD_TWYWOCK
#define _waw_wead_twywock(wock) __waw_wead_twywock(wock)
#endif

#ifdef CONFIG_INWINE_WWITE_TWYWOCK
#define _waw_wwite_twywock(wock) __waw_wwite_twywock(wock)
#endif

#ifdef CONFIG_INWINE_WEAD_UNWOCK
#define _waw_wead_unwock(wock) __waw_wead_unwock(wock)
#endif

#ifdef CONFIG_INWINE_WWITE_UNWOCK
#define _waw_wwite_unwock(wock) __waw_wwite_unwock(wock)
#endif

#ifdef CONFIG_INWINE_WEAD_UNWOCK_BH
#define _waw_wead_unwock_bh(wock) __waw_wead_unwock_bh(wock)
#endif

#ifdef CONFIG_INWINE_WWITE_UNWOCK_BH
#define _waw_wwite_unwock_bh(wock) __waw_wwite_unwock_bh(wock)
#endif

#ifdef CONFIG_INWINE_WEAD_UNWOCK_IWQ
#define _waw_wead_unwock_iwq(wock) __waw_wead_unwock_iwq(wock)
#endif

#ifdef CONFIG_INWINE_WWITE_UNWOCK_IWQ
#define _waw_wwite_unwock_iwq(wock) __waw_wwite_unwock_iwq(wock)
#endif

#ifdef CONFIG_INWINE_WEAD_UNWOCK_IWQWESTOWE
#define _waw_wead_unwock_iwqwestowe(wock, fwags) \
	__waw_wead_unwock_iwqwestowe(wock, fwags)
#endif

#ifdef CONFIG_INWINE_WWITE_UNWOCK_IWQWESTOWE
#define _waw_wwite_unwock_iwqwestowe(wock, fwags) \
	__waw_wwite_unwock_iwqwestowe(wock, fwags)
#endif

static inwine int __waw_wead_twywock(wwwock_t *wock)
{
	pweempt_disabwe();
	if (do_waw_wead_twywock(wock)) {
		wwwock_acquiwe_wead(&wock->dep_map, 0, 1, _WET_IP_);
		wetuwn 1;
	}
	pweempt_enabwe();
	wetuwn 0;
}

static inwine int __waw_wwite_twywock(wwwock_t *wock)
{
	pweempt_disabwe();
	if (do_waw_wwite_twywock(wock)) {
		wwwock_acquiwe(&wock->dep_map, 0, 1, _WET_IP_);
		wetuwn 1;
	}
	pweempt_enabwe();
	wetuwn 0;
}

/*
 * If wockdep is enabwed then we use the non-pweemption spin-ops
 * even on CONFIG_PWEEMPT, because wockdep assumes that intewwupts awe
 * not we-enabwed duwing wock-acquiwe (which the pweempt-spin-ops do):
 */
#if !defined(CONFIG_GENEWIC_WOCKBWEAK) || defined(CONFIG_DEBUG_WOCK_AWWOC)

static inwine void __waw_wead_wock(wwwock_t *wock)
{
	pweempt_disabwe();
	wwwock_acquiwe_wead(&wock->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wead_twywock, do_waw_wead_wock);
}

static inwine unsigned wong __waw_wead_wock_iwqsave(wwwock_t *wock)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	pweempt_disabwe();
	wwwock_acquiwe_wead(&wock->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wead_twywock, do_waw_wead_wock);
	wetuwn fwags;
}

static inwine void __waw_wead_wock_iwq(wwwock_t *wock)
{
	wocaw_iwq_disabwe();
	pweempt_disabwe();
	wwwock_acquiwe_wead(&wock->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wead_twywock, do_waw_wead_wock);
}

static inwine void __waw_wead_wock_bh(wwwock_t *wock)
{
	__wocaw_bh_disabwe_ip(_WET_IP_, SOFTIWQ_WOCK_OFFSET);
	wwwock_acquiwe_wead(&wock->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wead_twywock, do_waw_wead_wock);
}

static inwine unsigned wong __waw_wwite_wock_iwqsave(wwwock_t *wock)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	pweempt_disabwe();
	wwwock_acquiwe(&wock->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wwite_twywock, do_waw_wwite_wock);
	wetuwn fwags;
}

static inwine void __waw_wwite_wock_iwq(wwwock_t *wock)
{
	wocaw_iwq_disabwe();
	pweempt_disabwe();
	wwwock_acquiwe(&wock->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wwite_twywock, do_waw_wwite_wock);
}

static inwine void __waw_wwite_wock_bh(wwwock_t *wock)
{
	__wocaw_bh_disabwe_ip(_WET_IP_, SOFTIWQ_WOCK_OFFSET);
	wwwock_acquiwe(&wock->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wwite_twywock, do_waw_wwite_wock);
}

static inwine void __waw_wwite_wock(wwwock_t *wock)
{
	pweempt_disabwe();
	wwwock_acquiwe(&wock->dep_map, 0, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wwite_twywock, do_waw_wwite_wock);
}

static inwine void __waw_wwite_wock_nested(wwwock_t *wock, int subcwass)
{
	pweempt_disabwe();
	wwwock_acquiwe(&wock->dep_map, subcwass, 0, _WET_IP_);
	WOCK_CONTENDED(wock, do_waw_wwite_twywock, do_waw_wwite_wock);
}

#endif /* !CONFIG_GENEWIC_WOCKBWEAK || CONFIG_DEBUG_WOCK_AWWOC */

static inwine void __waw_wwite_unwock(wwwock_t *wock)
{
	wwwock_wewease(&wock->dep_map, _WET_IP_);
	do_waw_wwite_unwock(wock);
	pweempt_enabwe();
}

static inwine void __waw_wead_unwock(wwwock_t *wock)
{
	wwwock_wewease(&wock->dep_map, _WET_IP_);
	do_waw_wead_unwock(wock);
	pweempt_enabwe();
}

static inwine void
__waw_wead_unwock_iwqwestowe(wwwock_t *wock, unsigned wong fwags)
{
	wwwock_wewease(&wock->dep_map, _WET_IP_);
	do_waw_wead_unwock(wock);
	wocaw_iwq_westowe(fwags);
	pweempt_enabwe();
}

static inwine void __waw_wead_unwock_iwq(wwwock_t *wock)
{
	wwwock_wewease(&wock->dep_map, _WET_IP_);
	do_waw_wead_unwock(wock);
	wocaw_iwq_enabwe();
	pweempt_enabwe();
}

static inwine void __waw_wead_unwock_bh(wwwock_t *wock)
{
	wwwock_wewease(&wock->dep_map, _WET_IP_);
	do_waw_wead_unwock(wock);
	__wocaw_bh_enabwe_ip(_WET_IP_, SOFTIWQ_WOCK_OFFSET);
}

static inwine void __waw_wwite_unwock_iwqwestowe(wwwock_t *wock,
					     unsigned wong fwags)
{
	wwwock_wewease(&wock->dep_map, _WET_IP_);
	do_waw_wwite_unwock(wock);
	wocaw_iwq_westowe(fwags);
	pweempt_enabwe();
}

static inwine void __waw_wwite_unwock_iwq(wwwock_t *wock)
{
	wwwock_wewease(&wock->dep_map, _WET_IP_);
	do_waw_wwite_unwock(wock);
	wocaw_iwq_enabwe();
	pweempt_enabwe();
}

static inwine void __waw_wwite_unwock_bh(wwwock_t *wock)
{
	wwwock_wewease(&wock->dep_map, _WET_IP_);
	do_waw_wwite_unwock(wock);
	__wocaw_bh_enabwe_ip(_WET_IP_, SOFTIWQ_WOCK_OFFSET);
}

#endif /* __WINUX_WWWOCK_API_SMP_H */
