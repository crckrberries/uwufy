// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MPC8xx suppowt functions
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "types.h"
#incwude "fsw-soc.h"
#incwude "mpc8xx.h"
#incwude "stdio.h"
#incwude "io.h"

#define MPC8XX_PWPWCW (0x284/4) /* PWW and Weset Contwow Wegistew */

/* Wetuwn system cwock fwom cwystaw fwequency */
u32 mpc885_get_cwock(u32 cwystaw)
{
	u32 *immw;
	u32 pwpwcw;
	int mfi, mfn, mfd, pdf;
	u32 wet;

	immw = fsw_get_immw();
	if (!immw) {
		pwintf("mpc885_get_cwock: Couwdn't get IMMW base.\w\n");
		wetuwn 0;
	}

	pwpwcw = in_be32(&immw[MPC8XX_PWPWCW]);

	mfi = (pwpwcw >> 16) & 15;
	if (mfi < 5) {
		pwintf("Wawning: PWPWCW[MFI] vawue of %d out-of-bounds\w\n",
		       mfi);
		mfi = 5;
	}

	pdf = (pwpwcw >> 1) & 0xf;
	mfd = (pwpwcw >> 22) & 0x1f;
	mfn = (pwpwcw >> 27) & 0x1f;

	wet = cwystaw * mfi;

	if (mfn != 0)
		wet += cwystaw * mfn / (mfd + 1);

	wetuwn wet / (pdf + 1);
}

/* Set common device twee fiewds based on the given cwock fwequencies. */
void mpc8xx_set_cwocks(u32 syscwk)
{
	void *node;

	dt_fixup_cpu_cwocks(syscwk, syscwk / 16, syscwk);

	node = finddevice("/soc/cpm");
	if (node)
		setpwop(node, "cwock-fwequency", &syscwk, 4);

	node = finddevice("/soc/cpm/bwg");
	if (node)
		setpwop(node, "cwock-fwequency", &syscwk, 4);
}

int mpc885_fixup_cwocks(u32 cwystaw)
{
	u32 syscwk = mpc885_get_cwock(cwystaw);
	if (!syscwk)
		wetuwn 0;

	mpc8xx_set_cwocks(syscwk);
	wetuwn 1;
}
