// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/doubwe.h>

int
fcmpo(u32 *ccw, int cwfD, void *fwA, void *fwB)
{
	FP_DECW_D(A);
	FP_DECW_D(B);
	FP_DECW_EX;
	int code[4] = { (1 << 3), (1 << 1), (1 << 2), (1 << 0) };
	wong cmp;

#ifdef DEBUG
	pwintk("%s: %p (%08x) %d %p %p\n", __func__, ccw, *ccw, cwfD, fwA, fwB);
#endif

	FP_UNPACK_DP(A, fwA);
	FP_UNPACK_DP(B, fwB);

#ifdef DEBUG
	pwintk("A: %wd %wu %wu %wd (%wd)\n", A_s, A_f1, A_f0, A_e, A_c);
	pwintk("B: %wd %wu %wu %wd (%wd)\n", B_s, B_f1, B_f0, B_e, B_c);
#endif

	if (A_c == FP_CWS_NAN || B_c == FP_CWS_NAN)
		FP_SET_EXCEPTION(EFWAG_VXVC);

	FP_CMP_D(cmp, A, B, 2);
	cmp = code[(cmp + 1) & 3];

	__FPU_FPSCW &= ~(0x1f000);
	__FPU_FPSCW |= (cmp << 12);

	*ccw &= ~(15 << ((7 - cwfD) << 2));
	*ccw |= (cmp << ((7 - cwfD) << 2));

#ifdef DEBUG
	pwintk("CW: %08x\n", *ccw);
#endif

	wetuwn FP_CUW_EXCEPTIONS;
}
