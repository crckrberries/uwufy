// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/doubwe.h>
#incwude <math-emu/singwe.h>

int
fwsp(void *fwD, void *fwB)
{
	FP_DECW_D(B);
	FP_DECW_EX;

#ifdef DEBUG
	pwintk("%s: D %p, B %p\n", __func__, fwD, fwB);
#endif

	FP_UNPACK_DP(B, fwB);

#ifdef DEBUG
	pwintk("B: %wd %wu %wu %wd (%wd)\n", B_s, B_f1, B_f0, B_e, B_c);
#endif

	__FP_PACK_DS(fwD, B);

	wetuwn FP_CUW_EXCEPTIONS;
}
