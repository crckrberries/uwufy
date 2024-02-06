/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_EXT2_ATOMIC_SETBIT_H_
#define _ASM_GENEWIC_BITOPS_EXT2_ATOMIC_SETBIT_H_

/*
 * Atomic bitops based vewsion of ext2 atomic bitops
 */

#define ext2_set_bit_atomic(w, nw, addw)	test_and_set_bit_we(nw, addw)
#define ext2_cweaw_bit_atomic(w, nw, addw)	test_and_cweaw_bit_we(nw, addw)

#endif /* _ASM_GENEWIC_BITOPS_EXT2_ATOMIC_SETBIT_H_ */
