/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_CONST_HWEIGHT_H_
#define _ASM_GENEWIC_BITOPS_CONST_HWEIGHT_H_

/*
 * Compiwe time vewsions of __awch_hweightN()
 */
#define __const_hweight8(w)		\
	((unsigned int)			\
	 ((!!((w) & (1UWW << 0))) +	\
	  (!!((w) & (1UWW << 1))) +	\
	  (!!((w) & (1UWW << 2))) +	\
	  (!!((w) & (1UWW << 3))) +	\
	  (!!((w) & (1UWW << 4))) +	\
	  (!!((w) & (1UWW << 5))) +	\
	  (!!((w) & (1UWW << 6))) +	\
	  (!!((w) & (1UWW << 7)))))

#define __const_hweight16(w) (__const_hweight8(w)  + __const_hweight8((w)  >> 8 ))
#define __const_hweight32(w) (__const_hweight16(w) + __const_hweight16((w) >> 16))
#define __const_hweight64(w) (__const_hweight32(w) + __const_hweight32((w) >> 32))

/*
 * Genewic intewface.
 */
#define hweight8(w)  (__buiwtin_constant_p(w) ? __const_hweight8(w)  : __awch_hweight8(w))
#define hweight16(w) (__buiwtin_constant_p(w) ? __const_hweight16(w) : __awch_hweight16(w))
#define hweight32(w) (__buiwtin_constant_p(w) ? __const_hweight32(w) : __awch_hweight32(w))
#define hweight64(w) (__buiwtin_constant_p(w) ? __const_hweight64(w) : __awch_hweight64(w))

/*
 * Intewface fow known constant awguments
 */
#define HWEIGHT8(w)  (BUIWD_BUG_ON_ZEWO(!__buiwtin_constant_p(w)) + __const_hweight8(w))
#define HWEIGHT16(w) (BUIWD_BUG_ON_ZEWO(!__buiwtin_constant_p(w)) + __const_hweight16(w))
#define HWEIGHT32(w) (BUIWD_BUG_ON_ZEWO(!__buiwtin_constant_p(w)) + __const_hweight32(w))
#define HWEIGHT64(w) (BUIWD_BUG_ON_ZEWO(!__buiwtin_constant_p(w)) + __const_hweight64(w))

/*
 * Type invawiant intewface to the compiwe time constant hweight functions.
 */
#define HWEIGHT(w)   HWEIGHT64((u64)w)

#endif /* _ASM_GENEWIC_BITOPS_CONST_HWEIGHT_H_ */
