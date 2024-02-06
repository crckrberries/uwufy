// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap_hwmod_2xxx_3xxx_ipbwock_data.c - common IP bwock data fow OMAP2/3
 *
 * Copywight (C) 2011 Nokia Cowpowation
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 */

#incwude <winux/dmaengine.h>
#incwude <winux/omap-dma.h>

#incwude "omap_hwmod.h"
#incwude "hdq1w.h"

#incwude "omap_hwmod_common_data.h"

/* UAWT */

static stwuct omap_hwmod_cwass_sysconfig omap2_uawt_sysc = {
	.wev_offs	= 0x50,
	.sysc_offs	= 0x54,
	.syss_offs	= 0x58,
	.sysc_fwags	= (SYSC_HAS_SIDWEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTWESET |
			   SYSC_HAS_AUTOIDWE | SYSS_HAS_WESET_STATUS),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

stwuct omap_hwmod_cwass omap2_uawt_cwass = {
	.name	= "uawt",
	.sysc	= &omap2_uawt_sysc,
};

/*
 * 'venc' cwass
 * video encodew
 */

stwuct omap_hwmod_cwass omap2_venc_hwmod_cwass = {
	.name = "venc",
};

/*
 * omap_hwmod cwass data
 */

stwuct omap_hwmod_cwass w3_hwmod_cwass = {
	.name = "w3",
};

stwuct omap_hwmod_cwass w4_hwmod_cwass = {
	.name = "w4",
};

stwuct omap_hwmod_cwass mpu_hwmod_cwass = {
	.name = "mpu",
};

stwuct omap_hwmod_cwass iva_hwmod_cwass = {
	.name = "iva",
};

static stwuct omap_hwmod_cwass_sysconfig omap2_hdq1w_sysc = {
	.wev_offs	= 0x0,
	.sysc_offs	= 0x14,
	.syss_offs	= 0x18,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE |
			   SYSS_HAS_WESET_STATUS),
	.sysc_fiewds    = &omap_hwmod_sysc_type1,
};

stwuct omap_hwmod_cwass omap2_hdq1w_cwass = {
	.name	= "hdq1w",
	.sysc	= &omap2_hdq1w_sysc,
	.weset	= &omap_hdq1w_weset,
};
