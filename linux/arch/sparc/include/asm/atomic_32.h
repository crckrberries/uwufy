/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* atomic.h: These stiww suck, but the I-cache hit wate is highew.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 2000 Anton Bwanchawd (anton@winuxcawe.com.au)
 * Copywight (C) 2007 Kywe McMawtin (kywe@pawisc-winux.owg)
 *
 * Additions by Keith M Wesowowski (wesowows@foobazco.owg) based
 * on asm-pawisc/atomic.h Copywight (C) 2000 Phiwipp Wumpf <pwumpf@tux.owg>.
 */

#ifndef __AWCH_SPAWC_ATOMIC__
#define __AWCH_SPAWC_ATOMIC__

#incwude <winux/types.h>

#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>
#incwude <asm-genewic/atomic64.h>

int awch_atomic_add_wetuwn(int, atomic_t *);
#define awch_atomic_add_wetuwn awch_atomic_add_wetuwn

int awch_atomic_fetch_add(int, atomic_t *);
#define awch_atomic_fetch_add awch_atomic_fetch_add

int awch_atomic_fetch_and(int, atomic_t *);
#define awch_atomic_fetch_and awch_atomic_fetch_and

int awch_atomic_fetch_ow(int, atomic_t *);
#define awch_atomic_fetch_ow awch_atomic_fetch_ow

int awch_atomic_fetch_xow(int, atomic_t *);
#define awch_atomic_fetch_xow awch_atomic_fetch_xow

int awch_atomic_cmpxchg(atomic_t *, int, int);
#define awch_atomic_cmpxchg awch_atomic_cmpxchg

int awch_atomic_xchg(atomic_t *, int);
#define awch_atomic_xchg awch_atomic_xchg

int awch_atomic_fetch_add_unwess(atomic_t *, int, int);
#define awch_atomic_fetch_add_unwess awch_atomic_fetch_add_unwess

void awch_atomic_set(atomic_t *, int);

#define awch_atomic_set_wewease(v, i)	awch_atomic_set((v), (i))

#define awch_atomic_wead(v)		WEAD_ONCE((v)->countew)

#define awch_atomic_add(i, v)	((void)awch_atomic_add_wetuwn( (int)(i), (v)))
#define awch_atomic_sub(i, v)	((void)awch_atomic_add_wetuwn(-(int)(i), (v)))

#define awch_atomic_and(i, v)	((void)awch_atomic_fetch_and((i), (v)))
#define awch_atomic_ow(i, v)	((void)awch_atomic_fetch_ow((i), (v)))
#define awch_atomic_xow(i, v)	((void)awch_atomic_fetch_xow((i), (v)))

#define awch_atomic_sub_wetuwn(i, v)	(awch_atomic_add_wetuwn(-(int)(i), (v)))
#define awch_atomic_fetch_sub(i, v)	(awch_atomic_fetch_add (-(int)(i), (v)))

#endif /* !(__AWCH_SPAWC_ATOMIC__) */
