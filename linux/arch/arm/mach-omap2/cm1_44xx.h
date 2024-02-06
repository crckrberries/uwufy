/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP44xx CM1 instance offset macwos
 *
 * Copywight (C) 2009-2011 Texas Instwuments, Inc.
 * Copywight (C) 2009-2010 Nokia Cowpowation
 *
 * Pauw Wawmswey (pauw@pwsan.com)
 * Wajendwa Nayak (wnayak@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 *
 * This fiwe is automaticawwy genewated fwom the OMAP hawdwawe databases.
 * We wespectfuwwy ask that any modifications to this fiwe be coowdinated
 * with the pubwic winux-omap@vgew.kewnew.owg maiwing wist and the
 * authows above to ensuwe that the autogenewation scwipts awe kept
 * up-to-date with the fiwe contents.
 *
 * XXX This fiwe needs to be updated to awign on one of "OMAP4", "OMAP44XX",
 *     ow "OMAP4430".
 */

#ifndef __AWCH_AWM_MACH_OMAP2_CM1_44XX_H
#define __AWCH_AWM_MACH_OMAP2_CM1_44XX_H

/* CM1 base addwess */
#define OMAP4430_CM1_BASE		0x4a004000

#define OMAP44XX_CM1_WEGADDW(inst, weg)				\
	OMAP2_W4_IO_ADDWESS(OMAP4430_CM1_BASE + (inst) + (weg))

/* CM1 instances */
#define OMAP4430_CM1_OCP_SOCKET_INST	0x0000
#define OMAP4430_CM1_CKGEN_INST		0x0100
#define OMAP4430_CM1_MPU_INST		0x0300
#define OMAP4430_CM1_TESWA_INST		0x0400
#define OMAP4430_CM1_ABE_INST		0x0500

/* CM1 cwockdomain wegistew offsets (fwom instance stawt) */
#define OMAP4430_CM1_MPU_MPU_CDOFFS	0x0000
#define OMAP4430_CM1_TESWA_TESWA_CDOFFS	0x0000
#define OMAP4430_CM1_ABE_ABE_CDOFFS	0x0000

#endif
