// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>

int
mtfsb1(int cwbD)
{
	if ((cwbD != 1) && (cwbD != 2))
		__FPU_FPSCW |= (1 << (31 - cwbD));

#ifdef DEBUG
	pwintk("%s: %d %08wx\n", __func__, cwbD, __FPU_FPSCW);
#endif

	wetuwn 0;
}
