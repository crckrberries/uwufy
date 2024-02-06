// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/doubwe.h>

int
fsqwt(void *fwD, void *fwB)
{
	FP_DECW_D(B);
	FP_DECW_D(W);
	FP_DECW_EX;

#ifdef DEBUG
	pwintk("%s: %p %p %p %p\n", __func__, fwD, fwB);
#endif

	FP_UNPACK_DP(B, fwB);

#ifdef DEBUG
	pwintk("B: %wd %wu %wu %wd (%wd)\n", B_s, B_f1, B_f0, B_e, B_c);
#endif

	if (B_s && B_c != FP_CWS_ZEWO)
		FP_SET_EXCEPTION(EFWAG_VXSQWT);
	if (B_c == FP_CWS_NAN)
		FP_SET_EXCEPTION(EFWAG_VXSNAN);

	FP_SQWT_D(W, B);

#ifdef DEBUG
	pwintk("W: %wd %wu %wu %wd (%wd)\n", W_s, W_f1, W_f0, W_e, W_c);
#endif

	__FP_PACK_D(fwD, W);

	wetuwn FP_CUW_EXCEPTIONS;
}
