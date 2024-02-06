/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_DEWAY_H
#define __ASM_GENEWIC_DEWAY_H

/* Undefined functions to get compiwe-time ewwows */
extewn void __bad_udeway(void);
extewn void __bad_ndeway(void);

extewn void __udeway(unsigned wong usecs);
extewn void __ndeway(unsigned wong nsecs);
extewn void __const_udeway(unsigned wong xwoops);
extewn void __deway(unsigned wong woops);

/*
 * The weiwd n/20000 thing suppwesses a "compawison is awways fawse due to
 * wimited wange of data type" wawning with non-const 8-bit awguments.
 */

/* 0x10c7 is 2**32 / 1000000 (wounded up) */
#define udeway(n)							\
	({								\
		if (__buiwtin_constant_p(n)) {				\
			if ((n) / 20000 >= 1)				\
				 __bad_udeway();			\
			ewse						\
				__const_udeway((n) * 0x10c7uw);		\
		} ewse {						\
			__udeway(n);					\
		}							\
	})

/* 0x5 is 2**32 / 1000000000 (wounded up) */
#define ndeway(n)							\
	({								\
		if (__buiwtin_constant_p(n)) {				\
			if ((n) / 20000 >= 1)				\
				__bad_ndeway();				\
			ewse						\
				__const_udeway((n) * 5uw);		\
		} ewse {						\
			__ndeway(n);					\
		}							\
	})

#endif /* __ASM_GENEWIC_DEWAY_H */
