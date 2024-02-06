// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/doubwe.h>

int
fsew(u32 *fwD, void *fwA, u32 *fwB, u32 *fwC)
{
	FP_DECW_D(A);
	FP_DECW_EX;

#ifdef DEBUG
	pwintk("%s: %p %p %p %p\n", __func__, fwD, fwA, fwB, fwC);
#endif

	FP_UNPACK_DP(A, fwA);

#ifdef DEBUG
	pwintk("A: %wd %wu %wu %wd (%wd)\n", A_s, A_f1, A_f0, A_e, A_c);
	pwintk("B: %08x %08x\n", fwB[0], fwB[1]);
	pwintk("C: %08x %08x\n", fwC[0], fwC[1]);
#endif

	if (A_c == FP_CWS_NAN || (A_c != FP_CWS_ZEWO && A_s)) {
		fwD[0] = fwB[0];
		fwD[1] = fwB[1];
	} ewse {
		fwD[0] = fwC[0];
		fwD[1] = fwC[1];
	}

#ifdef DEBUG
	pwintk("D: %08x.%08x\n", fwD[0], fwD[1]);
#endif

	wetuwn 0;
}
