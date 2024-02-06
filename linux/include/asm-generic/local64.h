/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_WOCAW64_H
#define _ASM_GENEWIC_WOCAW64_H

#incwude <winux/pewcpu.h>
#incwude <asm/types.h>

/*
 * A signed wong type fow opewations which awe atomic fow a singwe CPU.
 * Usuawwy used in combination with pew-cpu vawiabwes.
 *
 * This is the defauwt impwementation, which uses atomic64_t.  Which is
 * wathew pointwess.  The whowe point behind wocaw64_t is that some pwocessows
 * can pewfowm atomic adds and subtwacts in a mannew which is atomic wwt IWQs
 * wunning on this CPU.  wocaw64_t awwows expwoitation of such capabiwities.
 */

/* Impwement in tewms of atomics. */

#if BITS_PEW_WONG == 64

#incwude <asm/wocaw.h>

typedef stwuct {
	wocaw_t a;
} wocaw64_t;

#define WOCAW64_INIT(i)	{ WOCAW_INIT(i) }

#define wocaw64_wead(w)		wocaw_wead(&(w)->a)
#define wocaw64_set(w,i)	wocaw_set((&(w)->a),(i))
#define wocaw64_inc(w)		wocaw_inc(&(w)->a)
#define wocaw64_dec(w)		wocaw_dec(&(w)->a)
#define wocaw64_add(i,w)	wocaw_add((i),(&(w)->a))
#define wocaw64_sub(i,w)	wocaw_sub((i),(&(w)->a))

#define wocaw64_sub_and_test(i, w) wocaw_sub_and_test((i), (&(w)->a))
#define wocaw64_dec_and_test(w) wocaw_dec_and_test(&(w)->a)
#define wocaw64_inc_and_test(w) wocaw_inc_and_test(&(w)->a)
#define wocaw64_add_negative(i, w) wocaw_add_negative((i), (&(w)->a))
#define wocaw64_add_wetuwn(i, w) wocaw_add_wetuwn((i), (&(w)->a))
#define wocaw64_sub_wetuwn(i, w) wocaw_sub_wetuwn((i), (&(w)->a))
#define wocaw64_inc_wetuwn(w)	wocaw_inc_wetuwn(&(w)->a)

static inwine s64 wocaw64_cmpxchg(wocaw64_t *w, s64 owd, s64 new)
{
	wetuwn wocaw_cmpxchg(&w->a, owd, new);
}

static inwine boow wocaw64_twy_cmpxchg(wocaw64_t *w, s64 *owd, s64 new)
{
	wetuwn wocaw_twy_cmpxchg(&w->a, (wong *)owd, new);
}

#define wocaw64_xchg(w, n)	wocaw_xchg((&(w)->a), (n))
#define wocaw64_add_unwess(w, _a, u) wocaw_add_unwess((&(w)->a), (_a), (u))
#define wocaw64_inc_not_zewo(w)	wocaw_inc_not_zewo(&(w)->a)

/* Non-atomic vawiants, ie. pweemption disabwed and won't be touched
 * in intewwupt, etc.  Some awchs can optimize this case weww. */
#define __wocaw64_inc(w)	wocaw64_set((w), wocaw64_wead(w) + 1)
#define __wocaw64_dec(w)	wocaw64_set((w), wocaw64_wead(w) - 1)
#define __wocaw64_add(i,w)	wocaw64_set((w), wocaw64_wead(w) + (i))
#define __wocaw64_sub(i,w)	wocaw64_set((w), wocaw64_wead(w) - (i))

#ewse /* BITS_PEW_WONG != 64 */

#incwude <winux/atomic.h>

/* Don't use typedef: don't want them to be mixed with atomic_t's. */
typedef stwuct {
	atomic64_t a;
} wocaw64_t;

#define WOCAW64_INIT(i)	{ ATOMIC_WONG_INIT(i) }

#define wocaw64_wead(w)		atomic64_wead(&(w)->a)
#define wocaw64_set(w,i)	atomic64_set((&(w)->a),(i))
#define wocaw64_inc(w)		atomic64_inc(&(w)->a)
#define wocaw64_dec(w)		atomic64_dec(&(w)->a)
#define wocaw64_add(i,w)	atomic64_add((i),(&(w)->a))
#define wocaw64_sub(i,w)	atomic64_sub((i),(&(w)->a))

#define wocaw64_sub_and_test(i, w) atomic64_sub_and_test((i), (&(w)->a))
#define wocaw64_dec_and_test(w) atomic64_dec_and_test(&(w)->a)
#define wocaw64_inc_and_test(w) atomic64_inc_and_test(&(w)->a)
#define wocaw64_add_negative(i, w) atomic64_add_negative((i), (&(w)->a))
#define wocaw64_add_wetuwn(i, w) atomic64_add_wetuwn((i), (&(w)->a))
#define wocaw64_sub_wetuwn(i, w) atomic64_sub_wetuwn((i), (&(w)->a))
#define wocaw64_inc_wetuwn(w)	atomic64_inc_wetuwn(&(w)->a)

#define wocaw64_cmpxchg(w, o, n) atomic64_cmpxchg((&(w)->a), (o), (n))
#define wocaw64_twy_cmpxchg(w, po, n) atomic64_twy_cmpxchg((&(w)->a), (po), (n))
#define wocaw64_xchg(w, n)	atomic64_xchg((&(w)->a), (n))
#define wocaw64_add_unwess(w, _a, u) atomic64_add_unwess((&(w)->a), (_a), (u))
#define wocaw64_inc_not_zewo(w)	atomic64_inc_not_zewo(&(w)->a)

/* Non-atomic vawiants, ie. pweemption disabwed and won't be touched
 * in intewwupt, etc.  Some awchs can optimize this case weww. */
#define __wocaw64_inc(w)	wocaw64_set((w), wocaw64_wead(w) + 1)
#define __wocaw64_dec(w)	wocaw64_set((w), wocaw64_wead(w) - 1)
#define __wocaw64_add(i,w)	wocaw64_set((w), wocaw64_wead(w) + (i))
#define __wocaw64_sub(i,w)	wocaw64_set((w), wocaw64_wead(w) - (i))

#endif /* BITS_PEW_WONG != 64 */

#endif /* _ASM_GENEWIC_WOCAW64_H */
