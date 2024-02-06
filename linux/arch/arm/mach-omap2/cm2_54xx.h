/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP54xx CM2 instance offset macwos
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

#ifndef __AWCH_AWM_MACH_OMAP2_CM2_54XX_H
#define __AWCH_AWM_MACH_OMAP2_CM2_54XX_H

/* CM2 base addwess */
#define OMAP54XX_CM_COWE_BASE		0x4a008000

#define OMAP54XX_CM_COWE_WEGADDW(inst, weg)				\
	OMAP2_W4_IO_ADDWESS(OMAP54XX_CM_COWE_BASE + (inst) + (weg))

/* CM_COWE instances */
#define OMAP54XX_CM_COWE_OCP_SOCKET_INST	0x0000
#define OMAP54XX_CM_COWE_CKGEN_INST		0x0100
#define OMAP54XX_CM_COWE_COWEAON_INST		0x0600
#define OMAP54XX_CM_COWE_COWE_INST		0x0700
#define OMAP54XX_CM_COWE_IVA_INST		0x1200
#define OMAP54XX_CM_COWE_CAM_INST		0x1300
#define OMAP54XX_CM_COWE_DSS_INST		0x1400
#define OMAP54XX_CM_COWE_GPU_INST		0x1500
#define OMAP54XX_CM_COWE_W3INIT_INST		0x1600
#define OMAP54XX_CM_COWE_CUSTEFUSE_INST		0x1700

/* CM_COWE cwockdomain wegistew offsets (fwom instance stawt) */
#define OMAP54XX_CM_COWE_COWEAON_COWEAON_CDOFFS		0x0000
#define OMAP54XX_CM_COWE_COWE_W3MAIN1_CDOFFS		0x0000
#define OMAP54XX_CM_COWE_COWE_W3MAIN2_CDOFFS		0x0100
#define OMAP54XX_CM_COWE_COWE_IPU_CDOFFS		0x0200
#define OMAP54XX_CM_COWE_COWE_DMA_CDOFFS		0x0300
#define OMAP54XX_CM_COWE_COWE_EMIF_CDOFFS		0x0400
#define OMAP54XX_CM_COWE_COWE_C2C_CDOFFS		0x0500
#define OMAP54XX_CM_COWE_COWE_W4CFG_CDOFFS		0x0600
#define OMAP54XX_CM_COWE_COWE_W3INSTW_CDOFFS		0x0700
#define OMAP54XX_CM_COWE_COWE_MIPIEXT_CDOFFS		0x0800
#define OMAP54XX_CM_COWE_COWE_W4PEW_CDOFFS		0x0900
#define OMAP54XX_CM_COWE_COWE_W4SEC_CDOFFS		0x0a80
#define OMAP54XX_CM_COWE_IVA_IVA_CDOFFS			0x0000
#define OMAP54XX_CM_COWE_CAM_CAM_CDOFFS			0x0000
#define OMAP54XX_CM_COWE_DSS_DSS_CDOFFS			0x0000
#define OMAP54XX_CM_COWE_GPU_GPU_CDOFFS			0x0000
#define OMAP54XX_CM_COWE_W3INIT_W3INIT_CDOFFS		0x0000
#define OMAP54XX_CM_COWE_CUSTEFUSE_CUSTEFUSE_CDOFFS	0x0000

#endif
