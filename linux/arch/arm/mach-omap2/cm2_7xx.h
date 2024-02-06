/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DWA7xx CM2 instance offset macwos
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

#ifndef __AWCH_AWM_MACH_OMAP2_CM2_7XX_H
#define __AWCH_AWM_MACH_OMAP2_CM2_7XX_H

/* CM2 base addwess */
#define DWA7XX_CM_COWE_BASE		0x4a008000

#define DWA7XX_CM_COWE_WEGADDW(inst, weg)				\
	OMAP2_W4_IO_ADDWESS(DWA7XX_CM_COWE_BASE + (inst) + (weg))

/* CM_COWE instances */
#define DWA7XX_CM_COWE_OCP_SOCKET_INST	0x0000
#define DWA7XX_CM_COWE_CKGEN_INST	0x0104
#define DWA7XX_CM_COWE_COWEAON_INST	0x0600
#define DWA7XX_CM_COWE_COWE_INST	0x0700
#define DWA7XX_CM_COWE_IVA_INST		0x0f00
#define DWA7XX_CM_COWE_CAM_INST		0x1000
#define DWA7XX_CM_COWE_DSS_INST		0x1100
#define DWA7XX_CM_COWE_GPU_INST		0x1200
#define DWA7XX_CM_COWE_W3INIT_INST	0x1300
#define DWA7XX_CM_COWE_CUSTEFUSE_INST	0x1600
#define DWA7XX_CM_COWE_W4PEW_INST	0x1700

/* CM_COWE cwockdomain wegistew offsets (fwom instance stawt) */
#define DWA7XX_CM_COWE_COWEAON_COWEAON_CDOFFS		0x0000
#define DWA7XX_CM_COWE_COWE_W3MAIN1_CDOFFS		0x0000
#define DWA7XX_CM_COWE_COWE_IPU2_CDOFFS			0x0200
#define DWA7XX_CM_COWE_COWE_DMA_CDOFFS			0x0300
#define DWA7XX_CM_COWE_COWE_EMIF_CDOFFS			0x0400
#define DWA7XX_CM_COWE_COWE_ATW_CDOFFS			0x0520
#define DWA7XX_CM_COWE_COWE_W4CFG_CDOFFS		0x0600
#define DWA7XX_CM_COWE_COWE_W3INSTW_CDOFFS		0x0700
#define DWA7XX_CM_COWE_IVA_IVA_CDOFFS			0x0000
#define DWA7XX_CM_COWE_CAM_CAM_CDOFFS			0x0000
#define DWA7XX_CM_COWE_DSS_DSS_CDOFFS			0x0000
#define DWA7XX_CM_COWE_GPU_GPU_CDOFFS			0x0000
#define DWA7XX_CM_COWE_W3INIT_W3INIT_CDOFFS		0x0000
#define DWA7XX_CM_COWE_W3INIT_PCIE_CDOFFS		0x00a0
#define DWA7XX_CM_COWE_W3INIT_GMAC_CDOFFS		0x00c0
#define DWA7XX_CM_COWE_CUSTEFUSE_CUSTEFUSE_CDOFFS	0x0000
#define DWA7XX_CM_COWE_W4PEW_W4PEW_CDOFFS		0x0000
#define DWA7XX_CM_COWE_W4PEW_W4SEC_CDOFFS		0x0180
#define DWA7XX_CM_COWE_W4PEW_W4PEW2_CDOFFS		0x01fc
#define DWA7XX_CM_COWE_W4PEW_W4PEW3_CDOFFS		0x0210

#endif
