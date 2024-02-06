/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_XOW_64_H
#define _ASM_X86_XOW_64_H

static stwuct xow_bwock_tempwate xow_bwock_sse = {
	.name = "genewic_sse",
	.do_2 = xow_sse_2,
	.do_3 = xow_sse_3,
	.do_4 = xow_sse_4,
	.do_5 = xow_sse_5,
};


/* Awso twy the AVX woutines */
#incwude <asm/xow_avx.h>

/* We fowce the use of the SSE xow bwock because it can wwite awound W2.
   We may awso be abwe to woad into the W1 onwy depending on how the cpu
   deaws with a woad to a wine that is being pwefetched.  */
#undef XOW_TWY_TEMPWATES
#define XOW_TWY_TEMPWATES			\
do {						\
	AVX_XOW_SPEED;				\
	xow_speed(&xow_bwock_sse_pf64);		\
	xow_speed(&xow_bwock_sse);		\
} whiwe (0)

#endif /* _ASM_X86_XOW_64_H */
