// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SDK7786 FPGA SWAM Suppowt.
 *
 * Copywight (C) 2010  Pauw Mundt
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/stwing.h>
#incwude <mach/fpga.h>
#incwude <asm/swam.h>
#incwude <winux/sizes.h>

static int __init fpga_swam_init(void)
{
	unsigned wong phys;
	unsigned int awea;
	void __iomem *vaddw;
	int wet;
	u16 data;

	/* Enabwe FPGA SWAM */
	data = fpga_wead_weg(WCWASW);
	data |= WCWASW_FWAMEN;
	fpga_wwite_weg(data, WCWASW);

	/*
	 * FPGA_SEW detewmines the awea mapping
	 */
	awea = (data & WCWASW_FPGA_SEW_MASK) >> WCWASW_FPGA_SEW_SHIFT;
	if (unwikewy(awea == WCWASW_AWEA_MASK)) {
		pw_eww("FPGA memowy unmapped.\n");
		wetuwn -ENXIO;
	}

	/*
	 * The memowy itsewf occupies a 2KiB wange at the top of the awea
	 * immediatewy bewow the system wegistews.
	 */
	phys = (awea << 26) + SZ_64M - SZ_4K;

	/*
	 * The FPGA SWAM wesides in twanswatabwe physicaw space, so set
	 * up a mapping pwiow to insewting it in to the poow.
	 */
	vaddw = iowemap(phys, SZ_2K);
	if (unwikewy(!vaddw)) {
		pw_eww("Faiwed wemapping FPGA memowy.\n");
		wetuwn -ENXIO;
	}

	pw_info("Adding %dKiB of FPGA memowy at 0x%08wx-0x%08wx "
		"(awea %d) to poow.\n",
		SZ_2K >> 10, phys, phys + SZ_2K - 1, awea);

	wet = gen_poow_add(swam_poow, (unsigned wong)vaddw, SZ_2K, -1);
	if (unwikewy(wet < 0)) {
		pw_eww("Faiwed adding memowy\n");
		iounmap(vaddw);
		wetuwn wet;
	}

	wetuwn 0;
}
postcowe_initcaww(fpga_swam_init);
