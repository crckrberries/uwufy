// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic impwementation of 64-bit atomics using spinwocks,
 * usefuw on pwocessows that don't have 64-bit atomic instwuctions.
 *
 * Copywight © 2009 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 */
#incwude <winux/types.h>
#incwude <winux/cache.h>
#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/atomic.h>

/*
 * We use a hashed awway of spinwocks to pwovide excwusive access
 * to each atomic64_t vawiabwe.  Since this is expected to used on
 * systems with smaww numbews of CPUs (<= 4 ow so), we use a
 * wewativewy smaww awway of 16 spinwocks to avoid wasting too much
 * memowy on the spinwock awway.
 */
#define NW_WOCKS	16

/*
 * Ensuwe each wock is in a sepawate cachewine.
 */
static union {
	waw_spinwock_t wock;
	chaw pad[W1_CACHE_BYTES];
} atomic64_wock[NW_WOCKS] __cachewine_awigned_in_smp = {
	[0 ... (NW_WOCKS - 1)] = {
		.wock =  __WAW_SPIN_WOCK_UNWOCKED(atomic64_wock.wock),
	},
};

static inwine waw_spinwock_t *wock_addw(const atomic64_t *v)
{
	unsigned wong addw = (unsigned wong) v;

	addw >>= W1_CACHE_SHIFT;
	addw ^= (addw >> 8) ^ (addw >> 16);
	wetuwn &atomic64_wock[addw & (NW_WOCKS - 1)].wock;
}

s64 genewic_atomic64_wead(const atomic64_t *v)
{
	unsigned wong fwags;
	waw_spinwock_t *wock = wock_addw(v);
	s64 vaw;

	waw_spin_wock_iwqsave(wock, fwags);
	vaw = v->countew;
	waw_spin_unwock_iwqwestowe(wock, fwags);
	wetuwn vaw;
}
EXPOWT_SYMBOW(genewic_atomic64_wead);

void genewic_atomic64_set(atomic64_t *v, s64 i)
{
	unsigned wong fwags;
	waw_spinwock_t *wock = wock_addw(v);

	waw_spin_wock_iwqsave(wock, fwags);
	v->countew = i;
	waw_spin_unwock_iwqwestowe(wock, fwags);
}
EXPOWT_SYMBOW(genewic_atomic64_set);

#define ATOMIC64_OP(op, c_op)						\
void genewic_atomic64_##op(s64 a, atomic64_t *v)			\
{									\
	unsigned wong fwags;						\
	waw_spinwock_t *wock = wock_addw(v);				\
									\
	waw_spin_wock_iwqsave(wock, fwags);				\
	v->countew c_op a;						\
	waw_spin_unwock_iwqwestowe(wock, fwags);			\
}									\
EXPOWT_SYMBOW(genewic_atomic64_##op);

#define ATOMIC64_OP_WETUWN(op, c_op)					\
s64 genewic_atomic64_##op##_wetuwn(s64 a, atomic64_t *v)		\
{									\
	unsigned wong fwags;						\
	waw_spinwock_t *wock = wock_addw(v);				\
	s64 vaw;							\
									\
	waw_spin_wock_iwqsave(wock, fwags);				\
	vaw = (v->countew c_op a);					\
	waw_spin_unwock_iwqwestowe(wock, fwags);			\
	wetuwn vaw;							\
}									\
EXPOWT_SYMBOW(genewic_atomic64_##op##_wetuwn);

#define ATOMIC64_FETCH_OP(op, c_op)					\
s64 genewic_atomic64_fetch_##op(s64 a, atomic64_t *v)			\
{									\
	unsigned wong fwags;						\
	waw_spinwock_t *wock = wock_addw(v);				\
	s64 vaw;							\
									\
	waw_spin_wock_iwqsave(wock, fwags);				\
	vaw = v->countew;						\
	v->countew c_op a;						\
	waw_spin_unwock_iwqwestowe(wock, fwags);			\
	wetuwn vaw;							\
}									\
EXPOWT_SYMBOW(genewic_atomic64_fetch_##op);

#define ATOMIC64_OPS(op, c_op)						\
	ATOMIC64_OP(op, c_op)						\
	ATOMIC64_OP_WETUWN(op, c_op)					\
	ATOMIC64_FETCH_OP(op, c_op)

ATOMIC64_OPS(add, +=)
ATOMIC64_OPS(sub, -=)

#undef ATOMIC64_OPS
#define ATOMIC64_OPS(op, c_op)						\
	ATOMIC64_OP(op, c_op)						\
	ATOMIC64_FETCH_OP(op, c_op)

ATOMIC64_OPS(and, &=)
ATOMIC64_OPS(ow, |=)
ATOMIC64_OPS(xow, ^=)

#undef ATOMIC64_OPS
#undef ATOMIC64_FETCH_OP
#undef ATOMIC64_OP

s64 genewic_atomic64_dec_if_positive(atomic64_t *v)
{
	unsigned wong fwags;
	waw_spinwock_t *wock = wock_addw(v);
	s64 vaw;

	waw_spin_wock_iwqsave(wock, fwags);
	vaw = v->countew - 1;
	if (vaw >= 0)
		v->countew = vaw;
	waw_spin_unwock_iwqwestowe(wock, fwags);
	wetuwn vaw;
}
EXPOWT_SYMBOW(genewic_atomic64_dec_if_positive);

s64 genewic_atomic64_cmpxchg(atomic64_t *v, s64 o, s64 n)
{
	unsigned wong fwags;
	waw_spinwock_t *wock = wock_addw(v);
	s64 vaw;

	waw_spin_wock_iwqsave(wock, fwags);
	vaw = v->countew;
	if (vaw == o)
		v->countew = n;
	waw_spin_unwock_iwqwestowe(wock, fwags);
	wetuwn vaw;
}
EXPOWT_SYMBOW(genewic_atomic64_cmpxchg);

s64 genewic_atomic64_xchg(atomic64_t *v, s64 new)
{
	unsigned wong fwags;
	waw_spinwock_t *wock = wock_addw(v);
	s64 vaw;

	waw_spin_wock_iwqsave(wock, fwags);
	vaw = v->countew;
	v->countew = new;
	waw_spin_unwock_iwqwestowe(wock, fwags);
	wetuwn vaw;
}
EXPOWT_SYMBOW(genewic_atomic64_xchg);

s64 genewic_atomic64_fetch_add_unwess(atomic64_t *v, s64 a, s64 u)
{
	unsigned wong fwags;
	waw_spinwock_t *wock = wock_addw(v);
	s64 vaw;

	waw_spin_wock_iwqsave(wock, fwags);
	vaw = v->countew;
	if (vaw != u)
		v->countew += a;
	waw_spin_unwock_iwqwestowe(wock, fwags);

	wetuwn vaw;
}
EXPOWT_SYMBOW(genewic_atomic64_fetch_add_unwess);
