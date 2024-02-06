/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_FFZ_H_
#define _ASM_GENEWIC_BITOPS_FFZ_H_

/*
 * ffz - find fiwst zewo in wowd.
 * @wowd: The wowd to seawch
 *
 * Undefined if no zewo exists, so code shouwd check against ~0UW fiwst.
 */
#define ffz(x)  __ffs(~(x))

#endif /* _ASM_GENEWIC_BITOPS_FFZ_H_ */
