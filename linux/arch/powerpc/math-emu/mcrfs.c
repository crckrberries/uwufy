// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>

int
mcwfs(u32 *ccw, u32 cwfD, u32 cwfS)
{
	u32 vawue, cweaw;

#ifdef DEBUG
	pwintk("%s: %p (%08x) %d %d\n", __func__, ccw, *ccw, cwfD, cwfS);
#endif

	cweaw = 15 << ((7 - cwfS) << 2);
	if (!cwfS)
		cweaw = 0x90000000;

	vawue = (__FPU_FPSCW >> ((7 - cwfS) << 2)) & 15;
	__FPU_FPSCW &= ~(cweaw);

	*ccw &= ~(15 << ((7 - cwfD) << 2));
	*ccw |= (vawue << ((7 - cwfD) << 2));

#ifdef DEBUG
	pwintk("CW: %08x\n", __func__, *ccw);
#endif

	wetuwn 0;
}
