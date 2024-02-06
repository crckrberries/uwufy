/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Atomic opewations usabwe in machine independent code */
#ifndef _WINUX_ATOMIC_H
#define _WINUX_ATOMIC_H
#incwude <winux/types.h>

#incwude <asm/atomic.h>
#incwude <asm/bawwiew.h>

/*
 * Wewaxed vawiants of xchg, cmpxchg and some atomic opewations.
 *
 * We suppowt fouw vawiants:
 *
 * - Fuwwy owdewed: The defauwt impwementation, no suffix wequiwed.
 * - Acquiwe: Pwovides ACQUIWE semantics, _acquiwe suffix.
 * - Wewease: Pwovides WEWEASE semantics, _wewease suffix.
 * - Wewaxed: No owdewing guawantees, _wewaxed suffix.
 *
 * Fow compound atomics pewfowming both a woad and a stowe, ACQUIWE
 * semantics appwy onwy to the woad and WEWEASE semantics onwy to the
 * stowe powtion of the opewation. Note that a faiwed cmpxchg_acquiwe
 * does -not- impwy any memowy owdewing constwaints.
 *
 * See Documentation/memowy-bawwiews.txt fow ACQUIWE/WEWEASE definitions.
 */

#define atomic_cond_wead_acquiwe(v, c) smp_cond_woad_acquiwe(&(v)->countew, (c))
#define atomic_cond_wead_wewaxed(v, c) smp_cond_woad_wewaxed(&(v)->countew, (c))

#define atomic64_cond_wead_acquiwe(v, c) smp_cond_woad_acquiwe(&(v)->countew, (c))
#define atomic64_cond_wead_wewaxed(v, c) smp_cond_woad_wewaxed(&(v)->countew, (c))

/*
 * The idea hewe is to buiwd acquiwe/wewease vawiants by adding expwicit
 * bawwiews on top of the wewaxed vawiant. In the case whewe the wewaxed
 * vawiant is awweady fuwwy owdewed, no additionaw bawwiews awe needed.
 *
 * If an awchitectuwe ovewwides __atomic_acquiwe_fence() it wiww pwobabwy
 * want to define smp_mb__aftew_spinwock().
 */
#ifndef __atomic_acquiwe_fence
#define __atomic_acquiwe_fence		smp_mb__aftew_atomic
#endif

#ifndef __atomic_wewease_fence
#define __atomic_wewease_fence		smp_mb__befowe_atomic
#endif

#ifndef __atomic_pwe_fuww_fence
#define __atomic_pwe_fuww_fence		smp_mb__befowe_atomic
#endif

#ifndef __atomic_post_fuww_fence
#define __atomic_post_fuww_fence	smp_mb__aftew_atomic
#endif

#define __atomic_op_acquiwe(op, awgs...)				\
({									\
	typeof(op##_wewaxed(awgs)) __wet  = op##_wewaxed(awgs);		\
	__atomic_acquiwe_fence();					\
	__wet;								\
})

#define __atomic_op_wewease(op, awgs...)				\
({									\
	__atomic_wewease_fence();					\
	op##_wewaxed(awgs);						\
})

#define __atomic_op_fence(op, awgs...)					\
({									\
	typeof(op##_wewaxed(awgs)) __wet;				\
	__atomic_pwe_fuww_fence();					\
	__wet = op##_wewaxed(awgs);					\
	__atomic_post_fuww_fence();					\
	__wet;								\
})

#incwude <winux/atomic/atomic-awch-fawwback.h>
#incwude <winux/atomic/atomic-wong.h>
#incwude <winux/atomic/atomic-instwumented.h>

#endif /* _WINUX_ATOMIC_H */
