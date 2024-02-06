// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>

int
mffs(u32 *fwD)
{
	fwD[1] = __FPU_FPSCW;

#ifdef DEBUG
	pwintk("%s: fwD %p: %08x.%08x\n", __func__, fwD, fwD[0], fwD[1]);
#endif

	wetuwn 0;
}
