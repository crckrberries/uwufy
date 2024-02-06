/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DWA7xx CM1 instance offset macwos
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Genewated by code owiginawwy wwitten by:
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

#ifndef __AWCH_AWM_MACH_OMAP2_CM1_7XX_H
#define __AWCH_AWM_MACH_OMAP2_CM1_7XX_H

/* CM1 base addwess */
#define DWA7XX_CM_COWE_AON_BASE		0x4a005000

#define DWA7XX_CM_COWE_AON_WEGADDW(inst, weg)				\
	OMAP2_W4_IO_ADDWESS(DWA7XX_CM_COWE_AON_BASE + (inst) + (weg))

/* CM_COWE_AON instances */
#define DWA7XX_CM_COWE_AON_OCP_SOCKET_INST	0x0000
#define DWA7XX_CM_COWE_AON_CKGEN_INST		0x0100
#define DWA7XX_CM_COWE_AON_MPU_INST		0x0300
#define DWA7XX_CM_COWE_AON_DSP1_INST		0x0400
#define DWA7XX_CM_COWE_AON_IPU_INST		0x0500
#define DWA7XX_CM_COWE_AON_DSP2_INST		0x0600
#define DWA7XX_CM_COWE_AON_EVE1_INST		0x0640
#define DWA7XX_CM_COWE_AON_EVE2_INST		0x0680
#define DWA7XX_CM_COWE_AON_EVE3_INST		0x06c0
#define DWA7XX_CM_COWE_AON_EVE4_INST		0x0700
#define DWA7XX_CM_COWE_AON_WTC_INST		0x0740
#define DWA7XX_CM_COWE_AON_VPE_INST		0x0760

/* CM_COWE_AON cwockdomain wegistew offsets (fwom instance stawt) */
#define DWA7XX_CM_COWE_AON_MPU_MPU_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_DSP1_DSP1_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_IPU_IPU1_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_IPU_IPU_CDOFFS	0x0040
#define DWA7XX_CM_COWE_AON_DSP2_DSP2_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_EVE1_EVE1_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_EVE2_EVE2_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_EVE3_EVE3_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_EVE4_EVE4_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_WTC_WTC_CDOFFS	0x0000
#define DWA7XX_CM_COWE_AON_VPE_VPE_CDOFFS	0x0000

#endif
