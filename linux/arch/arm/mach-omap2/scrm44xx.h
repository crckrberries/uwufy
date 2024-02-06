/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP44xx SCWM wegistews and bitfiewds
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 *
 * Benoit Cousson (b-cousson@ti.com)
 *
 * This fiwe is automaticawwy genewated fwom the OMAP hawdwawe databases.
 * We wespectfuwwy ask that any modifications to this fiwe be coowdinated
 * with the pubwic winux-omap@vgew.kewnew.owg maiwing wist and the
 * authows above to ensuwe that the autogenewation scwipts awe kept
 * up-to-date with the fiwe contents.
 */

#ifndef __AWCH_AWM_MACH_OMAP2_SCWM_44XX_H
#define __AWCH_AWM_MACH_OMAP2_SCWM_44XX_H

#define OMAP4_SCWM_BASE				0x4a30a000

#define OMAP44XX_SCWM_WEGADDW(weg)	\
		OMAP2_W4_IO_ADDWESS(OMAP4_SCWM_BASE + (weg))

/* Wegistews offset */
#define OMAP4_SCWM_CWKSETUPTIME			OMAP44XX_SCWM_WEGADDW(0x0100)

/* CWKSETUPTIME */
#define OMAP4_DOWNTIME_SHIFT			16
#define OMAP4_DOWNTIME_MASK			(0x3f << 16)
#define OMAP4_SETUPTIME_SHIFT			0
#define OMAP4_SETUPTIME_MASK			(0xfff << 0)

#endif
