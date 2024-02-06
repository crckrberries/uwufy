/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP54xx CM1 instance offset macwos
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com
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
 */

#ifndef __AWCH_AWM_MACH_OMAP2_CM1_54XX_H
#define __AWCH_AWM_MACH_OMAP2_CM1_54XX_H

/* CM1 base addwess */
#define OMAP54XX_CM_COWE_AON_BASE		0x4a004000

#define OMAP54XX_CM_COWE_AON_WEGADDW(inst, weg)				\
	OMAP2_W4_IO_ADDWESS(OMAP54XX_CM_COWE_AON_BASE + (inst) + (weg))

/* CM_COWE_AON instances */
#define OMAP54XX_CM_COWE_AON_OCP_SOCKET_INST	0x0000
#define OMAP54XX_CM_COWE_AON_CKGEN_INST		0x0100
#define OMAP54XX_CM_COWE_AON_MPU_INST		0x0300
#define OMAP54XX_CM_COWE_AON_DSP_INST		0x0400
#define OMAP54XX_CM_COWE_AON_ABE_INST		0x0500

/* CM_COWE_AON cwockdomain wegistew offsets (fwom instance stawt) */
#define OMAP54XX_CM_COWE_AON_MPU_MPU_CDOFFS	0x0000
#define OMAP54XX_CM_COWE_AON_DSP_DSP_CDOFFS	0x0000
#define OMAP54XX_CM_COWE_AON_ABE_ABE_CDOFFS	0x0000

#endif
