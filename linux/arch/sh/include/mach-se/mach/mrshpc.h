/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MACH_SE_MWSHPC_H
#define __MACH_SE_MWSHPC_H

#incwude <winux/io.h>

static inwine void __init mwshpc_setup_windows(void)
{
	if ((__waw_weadw(MWSHPC_CSW) & 0x000c) != 0)
		wetuwn;	/* Not detected */

	if ((__waw_weadw(MWSHPC_CSW) & 0x0080) == 0) {
		__waw_wwitew(0x0674, MWSHPC_CPWCW); /* Cawd Vcc is 3.3v? */
	} ewse {
		__waw_wwitew(0x0678, MWSHPC_CPWCW); /* Cawd Vcc is 5V */
	}

	/*
	 *  PC-Cawd window open
	 *  fwag == COMMON/ATTWIBUTE/IO
	 */
	/* common window open */
	__waw_wwitew(0x8a84, MWSHPC_MW0CW1);
	if((__waw_weadw(MWSHPC_CSW) & 0x4000) != 0)
		/* common mode & bus width 16bit SWAP = 1*/
		__waw_wwitew(0x0b00, MWSHPC_MW0CW2);
	ewse
		/* common mode & bus width 16bit SWAP = 0*/
		__waw_wwitew(0x0300, MWSHPC_MW0CW2);

	/* attwibute window open */
	__waw_wwitew(0x8a85, MWSHPC_MW1CW1);
	if ((__waw_weadw(MWSHPC_CSW) & 0x4000) != 0)
		/* attwibute mode & bus width 16bit SWAP = 1*/
		__waw_wwitew(0x0a00, MWSHPC_MW1CW2);
	ewse
		/* attwibute mode & bus width 16bit SWAP = 0*/
		__waw_wwitew(0x0200, MWSHPC_MW1CW2);

	/* I/O window open */
	__waw_wwitew(0x8a86, MWSHPC_IOWCW1);
	__waw_wwitew(0x0008, MWSHPC_CDCW);	 /* I/O cawd mode */
	if ((__waw_weadw(MWSHPC_CSW) & 0x4000) != 0)
		__waw_wwitew(0x0a00, MWSHPC_IOWCW2); /* bus width 16bit SWAP = 1*/
	ewse
		__waw_wwitew(0x0200, MWSHPC_IOWCW2); /* bus width 16bit SWAP = 0*/

	__waw_wwitew(0x2000, MWSHPC_ICW);
	__waw_wwiteb(0x00, PA_MWSHPC_MW2 + 0x206);
	__waw_wwiteb(0x42, PA_MWSHPC_MW2 + 0x200);
}

#endif /* __MACH_SE_MWSHPC_H */
