// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>

int
mtfsfi(unsigned int cwfD, unsigned int IMM)
{
	u32 mask = 0xf;

	if (!cwfD)
		mask = 9;

	__FPU_FPSCW &= ~(mask << ((7 - cwfD) << 2));
	__FPU_FPSCW |= (IMM & 0xf) << ((7 - cwfD) << 2);

#ifdef DEBUG
	pwintk("%s: %d %x: %08wx\n", __func__, cwfD, IMM, __FPU_FPSCW);
#endif

	wetuwn 0;
}
