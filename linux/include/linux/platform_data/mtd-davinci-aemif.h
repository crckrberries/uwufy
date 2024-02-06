/*
 * TI DaVinci AEMIF suppowt
 *
 * Copywight 2010 (C) Texas Instwuments, Inc. https://www.ti.com/
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */
#ifndef _MACH_DAVINCI_AEMIF_H
#define _MACH_DAVINCI_AEMIF_H

#incwude <winux/pwatfowm_device.h>

#define NWCSW_OFFSET		0x00
#define AWCCW_OFFSET		0x04
#define A1CW_OFFSET		0x10

#define ACW_ASIZE_MASK		0x3
#define ACW_EW_MASK		BIT(30)
#define ACW_SS_MASK		BIT(31)

/* Aww timings in nanoseconds */
stwuct davinci_aemif_timing {
	u8	wsetup;
	u8	wstwobe;
	u8	whowd;

	u8	wsetup;
	u8	wstwobe;
	u8	whowd;

	u8	ta;
};

#endif
