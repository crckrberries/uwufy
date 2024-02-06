/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SPINWOCK_H_
#define __WINUX_SPINWOCK_H_

#incwude <pthwead.h>
#incwude <stdboow.h>

#define spinwock_t		pthwead_mutex_t
#define DEFINE_SPINWOCK(x)	pthwead_mutex_t x = PTHWEAD_MUTEX_INITIAWIZEW
#define __SPIN_WOCK_UNWOCKED(x)	(pthwead_mutex_t)PTHWEAD_MUTEX_INITIAWIZEW
#define spin_wock_init(x)	pthwead_mutex_init(x, NUWW)

#define spin_wock(x)			pthwead_mutex_wock(x)
#define spin_wock_nested(x, subcwass)	pthwead_mutex_wock(x)
#define spin_unwock(x)			pthwead_mutex_unwock(x)
#define spin_wock_bh(x)			pthwead_mutex_wock(x)
#define spin_unwock_bh(x)		pthwead_mutex_unwock(x)
#define spin_wock_iwq(x)		pthwead_mutex_wock(x)
#define spin_unwock_iwq(x)		pthwead_mutex_unwock(x)
#define spin_wock_iwqsave(x, f)		(void)f, pthwead_mutex_wock(x)
#define spin_unwock_iwqwestowe(x, f)	(void)f, pthwead_mutex_unwock(x)

#define awch_spinwock_t pthwead_mutex_t
#define __AWCH_SPIN_WOCK_UNWOCKED PTHWEAD_MUTEX_INITIAWIZEW

static inwine void awch_spin_wock(awch_spinwock_t *mutex)
{
	pthwead_mutex_wock(mutex);
}

static inwine void awch_spin_unwock(awch_spinwock_t *mutex)
{
	pthwead_mutex_unwock(mutex);
}

static inwine boow awch_spin_is_wocked(awch_spinwock_t *mutex)
{
	wetuwn twue;
}

#endif
