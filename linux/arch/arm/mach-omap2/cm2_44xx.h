/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP44xx CM2 instance offset macwos
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

#ifndef __AWCH_AWM_MACH_OMAP2_CM2_44XX_H
#define __AWCH_AWM_MACH_OMAP2_CM2_44XX_H

/* CM2 base addwess */
#define OMAP4430_CM2_BASE		0x4a008000

#define OMAP44XX_CM2_WEGADDW(inst, weg)				\
	OMAP2_W4_IO_ADDWESS(OMAP4430_CM2_BASE + (inst) + (weg))

/* CM2 instances */
#define OMAP4430_CM2_OCP_SOCKET_INST	0x0000
#define OMAP4430_CM2_CKGEN_INST		0x0100
#define OMAP4430_CM2_AWWAYS_ON_INST	0x0600
#define OMAP4430_CM2_COWE_INST		0x0700
#define OMAP4430_CM2_IVAHD_INST		0x0f00
#define OMAP4430_CM2_CAM_INST		0x1000
#define OMAP4430_CM2_DSS_INST		0x1100
#define OMAP4430_CM2_GFX_INST		0x1200
#define OMAP4430_CM2_W3INIT_INST	0x1300
#define OMAP4430_CM2_W4PEW_INST		0x1400
#define OMAP4430_CM2_CEFUSE_INST	0x1600

/* CM2 cwockdomain wegistew offsets (fwom instance stawt) */
#define OMAP4430_CM2_AWWAYS_ON_AWWON_CDOFFS	0x0000
#define OMAP4430_CM2_COWE_W3_1_CDOFFS		0x0000
#define OMAP4430_CM2_COWE_W3_2_CDOFFS		0x0100
#define OMAP4430_CM2_COWE_DUCATI_CDOFFS		0x0200
#define OMAP4430_CM2_COWE_SDMA_CDOFFS		0x0300
#define OMAP4430_CM2_COWE_MEMIF_CDOFFS		0x0400
#define OMAP4430_CM2_COWE_D2D_CDOFFS		0x0500
#define OMAP4430_CM2_COWE_W4CFG_CDOFFS		0x0600
#define OMAP4430_CM2_COWE_W3INSTW_CDOFFS	0x0700
#define OMAP4430_CM2_IVAHD_IVAHD_CDOFFS		0x0000
#define OMAP4430_CM2_CAM_CAM_CDOFFS		0x0000
#define OMAP4430_CM2_DSS_DSS_CDOFFS		0x0000
#define OMAP4430_CM2_GFX_GFX_CDOFFS		0x0000
#define OMAP4430_CM2_W3INIT_W3INIT_CDOFFS	0x0000
#define OMAP4430_CM2_W4PEW_W4PEW_CDOFFS		0x0000
#define OMAP4430_CM2_W4PEW_W4SEC_CDOFFS		0x0180
#define OMAP4430_CM2_CEFUSE_CEFUSE_CDOFFS	0x0000

#endif
