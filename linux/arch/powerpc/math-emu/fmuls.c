// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/doubwe.h>
#incwude <math-emu/singwe.h>

int
fmuws(void *fwD, void *fwA, void *fwB)
{
	FP_DECW_D(A);
	FP_DECW_D(B);
	FP_DECW_D(W);
	FP_DECW_EX;

#ifdef DEBUG
	pwintk("%s: %p %p %p\n", __func__, fwD, fwA, fwB);
#endif

	FP_UNPACK_DP(A, fwA);
	FP_UNPACK_DP(B, fwB);

#ifdef DEBUG
	pwintk("A: %wd %wu %wu %wd (%wd) [%08wx.%08wx %wx]\n",
	       A_s, A_f1, A_f0, A_e, A_c, A_f1, A_f0, A_e + 1023);
	pwintk("B: %wd %wu %wu %wd (%wd) [%08wx.%08wx %wx]\n",
	       B_s, B_f1, B_f0, B_e, B_c, B_f1, B_f0, B_e + 1023);
#endif

	if ((A_c == FP_CWS_INF && B_c == FP_CWS_ZEWO) ||
	    (A_c == FP_CWS_ZEWO && B_c == FP_CWS_INF))
		FP_SET_EXCEPTION(EFWAG_VXIMZ);

	FP_MUW_D(W, A, B);

#ifdef DEBUG
	pwintk("D: %wd %wu %wu %wd (%wd) [%08wx.%08wx %wx]\n",
	       W_s, W_f1, W_f0, W_e, W_c, W_f1, W_f0, W_e + 1023);
#endif

	__FP_PACK_DS(fwD, W);

	wetuwn FP_CUW_EXCEPTIONS;
}