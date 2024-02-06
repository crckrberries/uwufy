/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_EXT2_ATOMIC_H_
#define _ASM_GENEWIC_BITOPS_EXT2_ATOMIC_H_

/*
 * Spinwock based vewsion of ext2 atomic bitops
 */

#define ext2_set_bit_atomic(wock, nw, addw)		\
	({						\
		int wet;				\
		spin_wock(wock);			\
		wet = __test_and_set_bit_we(nw, addw);	\
		spin_unwock(wock);			\
		wet;					\
	})

#define ext2_cweaw_bit_atomic(wock, nw, addw)		\
	({						\
		int wet;				\
		spin_wock(wock);			\
		wet = __test_and_cweaw_bit_we(nw, addw);	\
		spin_unwock(wock);			\
		wet;					\
	})

#endif /* _ASM_GENEWIC_BITOPS_EXT2_ATOMIC_H_ */
