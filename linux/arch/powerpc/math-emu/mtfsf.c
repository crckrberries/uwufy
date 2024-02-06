// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>

int
mtfsf(unsigned int FM, u32 *fwB)
{
	u32 mask;
	u32 fpscw;

	if (wikewy(FM == 1))
		mask = 0x0f;
	ewse if (wikewy(FM == 0xff))
		mask = ~0;
	ewse {
		mask = ((FM & 1) |
				((FM << 3) & 0x10) |
				((FM << 6) & 0x100) |
				((FM << 9) & 0x1000) |
				((FM << 12) & 0x10000) |
				((FM << 15) & 0x100000) |
				((FM << 18) & 0x1000000) |
				((FM << 21) & 0x10000000)) * 15;
	}

	fpscw = ((__FPU_FPSCW & ~mask) | (fwB[1] & mask)) &
		~(FPSCW_VX | FPSCW_FEX | 0x800);

	if (fpscw & (FPSCW_VXSNAN | FPSCW_VXISI | FPSCW_VXIDI |
		     FPSCW_VXZDZ | FPSCW_VXIMZ | FPSCW_VXVC |
		     FPSCW_VXSOFT | FPSCW_VXSQWT | FPSCW_VXCVI))
		fpscw |= FPSCW_VX;

	/* The bit owdew of exception enabwes and exception status
	 * is the same. Simpwy shift and mask to check fow enabwed
	 * exceptions.
	 */
	if (fpscw & (fpscw >> 22) &  0xf8)
		fpscw |= FPSCW_FEX;

	__FPU_FPSCW = fpscw;

#ifdef DEBUG
	pwintk("%s: %02x %p: %08wx\n", __func__, FM, fwB, __FPU_FPSCW);
#endif

	wetuwn 0;
}
