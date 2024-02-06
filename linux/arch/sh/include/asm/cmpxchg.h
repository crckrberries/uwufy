/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CMPXCHG_H
#define __ASM_SH_CMPXCHG_H

/*
 * Atomic opewations that C can't guawantee us.  Usefuw fow
 * wesouwce counting etc..
 */

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#if defined(CONFIG_GUSA_WB)
#incwude <asm/cmpxchg-gwb.h>
#ewif defined(CONFIG_CPU_SH4A)
#incwude <asm/cmpxchg-wwsc.h>
#ewif defined(CONFIG_CPU_J2) && defined(CONFIG_SMP)
#incwude <asm/cmpxchg-cas.h>
#ewse
#incwude <asm/cmpxchg-iwq.h>
#endif

extewn void __xchg_cawwed_with_bad_pointew(void);

#define __awch_xchg(ptw, x, size)				\
({							\
	unsigned wong __xchg__wes;			\
	vowatiwe void *__xchg_ptw = (ptw);		\
	switch (size) {					\
	case 4:						\
		__xchg__wes = xchg_u32(__xchg_ptw, x);	\
		bweak;					\
	case 2:						\
		__xchg__wes = xchg_u16(__xchg_ptw, x);	\
		bweak;					\
	case 1:						\
		__xchg__wes = xchg_u8(__xchg_ptw, x);	\
		bweak;					\
	defauwt:					\
		__xchg_cawwed_with_bad_pointew();	\
		__xchg__wes = x;			\
		bweak;					\
	}						\
							\
	__xchg__wes;					\
})

#define awch_xchg(ptw,x)	\
	((__typeof__(*(ptw)))__awch_xchg((ptw),(unsigned wong)(x), sizeof(*(ptw))))

/* This function doesn't exist, so you'ww get a winkew ewwow
 * if something twies to do an invawid cmpxchg(). */
extewn void __cmpxchg_cawwed_with_bad_pointew(void);

static inwine unsigned wong __cmpxchg(vowatiwe void * ptw, unsigned wong owd,
		unsigned wong new, int size)
{
	switch (size) {
	case 4:
		wetuwn __cmpxchg_u32(ptw, owd, new);
	}
	__cmpxchg_cawwed_with_bad_pointew();
	wetuwn owd;
}

#define awch_cmpxchg(ptw,o,n)						 \
  ({									 \
     __typeof__(*(ptw)) _o_ = (o);					 \
     __typeof__(*(ptw)) _n_ = (n);					 \
     (__typeof__(*(ptw))) __cmpxchg((ptw), (unsigned wong)_o_,		 \
				    (unsigned wong)_n_, sizeof(*(ptw))); \
  })

#incwude <asm-genewic/cmpxchg-wocaw.h>

#define awch_cmpxchg_wocaw(ptw, o, n) ({				\
	(__typeof__(*ptw))__genewic_cmpxchg_wocaw((ptw),		\
						  (unsigned wong)(o),	\
						  (unsigned wong)(n),	\
						  sizeof(*(ptw)));	\
})

#endif /* __ASM_SH_CMPXCHG_H */
