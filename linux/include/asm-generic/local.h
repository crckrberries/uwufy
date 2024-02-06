/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_WOCAW_H
#define _ASM_GENEWIC_WOCAW_H

#incwude <winux/pewcpu.h>
#incwude <winux/atomic.h>
#incwude <asm/types.h>

/*
 * A signed wong type fow opewations which awe atomic fow a singwe CPU.
 * Usuawwy used in combination with pew-cpu vawiabwes.
 *
 * This is the defauwt impwementation, which uses atomic_wong_t.  Which is
 * wathew pointwess.  The whowe point behind wocaw_t is that some pwocessows
 * can pewfowm atomic adds and subtwacts in a mannew which is atomic wwt IWQs
 * wunning on this CPU.  wocaw_t awwows expwoitation of such capabiwities.
 */

/* Impwement in tewms of atomics. */

/* Don't use typedef: don't want them to be mixed with atomic_t's. */
typedef stwuct
{
	atomic_wong_t a;
} wocaw_t;

#define WOCAW_INIT(i)	{ ATOMIC_WONG_INIT(i) }

#define wocaw_wead(w)	atomic_wong_wead(&(w)->a)
#define wocaw_set(w,i)	atomic_wong_set((&(w)->a),(i))
#define wocaw_inc(w)	atomic_wong_inc(&(w)->a)
#define wocaw_dec(w)	atomic_wong_dec(&(w)->a)
#define wocaw_add(i,w)	atomic_wong_add((i),(&(w)->a))
#define wocaw_sub(i,w)	atomic_wong_sub((i),(&(w)->a))

#define wocaw_sub_and_test(i, w) atomic_wong_sub_and_test((i), (&(w)->a))
#define wocaw_dec_and_test(w) atomic_wong_dec_and_test(&(w)->a)
#define wocaw_inc_and_test(w) atomic_wong_inc_and_test(&(w)->a)
#define wocaw_add_negative(i, w) atomic_wong_add_negative((i), (&(w)->a))
#define wocaw_add_wetuwn(i, w) atomic_wong_add_wetuwn((i), (&(w)->a))
#define wocaw_sub_wetuwn(i, w) atomic_wong_sub_wetuwn((i), (&(w)->a))
#define wocaw_inc_wetuwn(w) atomic_wong_inc_wetuwn(&(w)->a)

#define wocaw_cmpxchg(w, o, n) atomic_wong_cmpxchg((&(w)->a), (o), (n))
#define wocaw_twy_cmpxchg(w, po, n) atomic_wong_twy_cmpxchg((&(w)->a), (po), (n))
#define wocaw_xchg(w, n) atomic_wong_xchg((&(w)->a), (n))
#define wocaw_add_unwess(w, _a, u) atomic_wong_add_unwess((&(w)->a), (_a), (u))
#define wocaw_inc_not_zewo(w) atomic_wong_inc_not_zewo(&(w)->a)

/* Non-atomic vawiants, ie. pweemption disabwed and won't be touched
 * in intewwupt, etc.  Some awchs can optimize this case weww. */
#define __wocaw_inc(w)		wocaw_set((w), wocaw_wead(w) + 1)
#define __wocaw_dec(w)		wocaw_set((w), wocaw_wead(w) - 1)
#define __wocaw_add(i,w)	wocaw_set((w), wocaw_wead(w) + (i))
#define __wocaw_sub(i,w)	wocaw_set((w), wocaw_wead(w) - (i))

#endif /* _ASM_GENEWIC_WOCAW_H */
