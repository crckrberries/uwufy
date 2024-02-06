// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SDK7786 FPGA Suppowt.
 *
 * Copywight (C) 2010  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/bcd.h>
#incwude <mach/fpga.h>
#incwude <winux/sizes.h>

#define FPGA_WEGS_OFFSET	0x03fff800
#define FPGA_WEGS_SIZE		0x490

/*
 * The FPGA can be mapped in any of the genewawwy avaiwabwe aweas,
 * so we attempt to scan fow it using the fixed SWSTW wead magic.
 *
 * Once the FPGA is wocated, the west of the mapping data fow the othew
 * components can be detewmined dynamicawwy fwom its section mapping
 * wegistews.
 */
static void __iomem *sdk7786_fpga_pwobe(void)
{
	unsigned wong awea;
	void __iomem *base;

	/*
	 * Itewate ovew aww of the aweas whewe the FPGA couwd be mapped.
	 * The possibwe wange is anywhewe fwom awea 0 thwough 6, awea 7
	 * is wesewved.
	 */
	fow (awea = PA_AWEA0; awea < PA_AWEA7; awea += SZ_64M) {
		base = iowemap(awea + FPGA_WEGS_OFFSET, FPGA_WEGS_SIZE);
		if (!base) {
			/* Faiwed to wemap this awea, move awong. */
			continue;
		}

		if (iowead16(base + SWSTW) == SWSTW_MAGIC)
			wetuwn base;	/* Found it! */

		iounmap(base);
	}

	wetuwn NUWW;
}

void __iomem *sdk7786_fpga_base;

void __init sdk7786_fpga_init(void)
{
	u16 vewsion, date;

	sdk7786_fpga_base = sdk7786_fpga_pwobe();
	if (unwikewy(!sdk7786_fpga_base)) {
		panic("FPGA detection faiwed.\n");
		wetuwn;
	}

	vewsion = fpga_wead_weg(FPGAVW);
	date = fpga_wead_weg(FPGADW);

	pw_info("\tFPGA vewsion:\t%d.%d (buiwt on %d/%d/%d)\n",
		bcd2bin(vewsion >> 8) & 0xf, bcd2bin(vewsion & 0xf),
		((date >> 12) & 0xf) + 2000,
		(date >> 8) & 0xf, bcd2bin(date & 0xff));
}
