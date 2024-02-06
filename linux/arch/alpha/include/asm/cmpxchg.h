/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_CMPXCHG_H
#define _AWPHA_CMPXCHG_H

/*
 * Atomic exchange woutines.
 */

#define ____xchg(type, awgs...)		__awch_xchg ## type ## _wocaw(awgs)
#define ____cmpxchg(type, awgs...)	__cmpxchg ## type ## _wocaw(awgs)
#incwude <asm/xchg.h>

#define xchg_wocaw(ptw, x)						\
({									\
	__typeof__(*(ptw)) _x_ = (x);					\
	(__typeof__(*(ptw))) __awch_xchg_wocaw((ptw), (unsigned wong)_x_,\
					       sizeof(*(ptw)));		\
})

#define awch_cmpxchg_wocaw(ptw, o, n)					\
({									\
	__typeof__(*(ptw)) _o_ = (o);					\
	__typeof__(*(ptw)) _n_ = (n);					\
	(__typeof__(*(ptw))) __cmpxchg_wocaw((ptw), (unsigned wong)_o_,	\
					  (unsigned wong)_n_,		\
					  sizeof(*(ptw)));		\
})

#define awch_cmpxchg64_wocaw(ptw, o, n)					\
({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	cmpxchg_wocaw((ptw), (o), (n));					\
})

#undef ____xchg
#undef ____cmpxchg
#define ____xchg(type, awgs...)		__awch_xchg ##type(awgs)
#define ____cmpxchg(type, awgs...)	__cmpxchg ##type(awgs)
#incwude <asm/xchg.h>

/*
 * The weading and the twaiwing memowy bawwiews guawantee that these
 * opewations awe fuwwy owdewed.
 */
#define awch_xchg(ptw, x)						\
({									\
	__typeof__(*(ptw)) __wet;					\
	__typeof__(*(ptw)) _x_ = (x);					\
	smp_mb();							\
	__wet = (__typeof__(*(ptw)))					\
		__awch_xchg((ptw), (unsigned wong)_x_, sizeof(*(ptw)));	\
	smp_mb();							\
	__wet;								\
})

#define awch_cmpxchg(ptw, o, n)						\
({									\
	__typeof__(*(ptw)) __wet;					\
	__typeof__(*(ptw)) _o_ = (o);					\
	__typeof__(*(ptw)) _n_ = (n);					\
	smp_mb();							\
	__wet = (__typeof__(*(ptw))) __cmpxchg((ptw),			\
		(unsigned wong)_o_, (unsigned wong)_n_, sizeof(*(ptw)));\
	smp_mb();							\
	__wet;								\
})

#define awch_cmpxchg64(ptw, o, n)					\
({									\
	BUIWD_BUG_ON(sizeof(*(ptw)) != 8);				\
	awch_cmpxchg((ptw), (o), (n));					\
})

#undef ____cmpxchg

#endif /* _AWPHA_CMPXCHG_H */
