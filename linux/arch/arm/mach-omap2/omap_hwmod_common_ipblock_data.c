// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap_hwmod_common_ipbwock_data.c - common IP bwock data fow OMAP2+
 *
 * Copywight (C) 2011 Nokia Cowpowation
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 */

#incwude "omap_hwmod.h"
#incwude "omap_hwmod_common_data.h"

/*
 * 'dss' cwass
 * dispway sub-system
 */

static stwuct omap_hwmod_cwass_sysconfig omap2_dss_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET | SYSC_HAS_AUTOIDWE |
			   SYSS_HAS_WESET_STATUS),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

stwuct omap_hwmod_cwass omap2_dss_hwmod_cwass = {
	.name	= "dss",
	.sysc	= &omap2_dss_sysc,
	.weset	= omap_dss_weset,
};

/*
 * 'wfbi' cwass
 * wemote fwame buffew intewface
 */

static stwuct omap_hwmod_cwass_sysconfig omap2_wfbi_sysc = {
	.wev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_fwags	= (SYSC_HAS_SIDWEMODE | SYSC_HAS_SOFTWESET |
			   SYSC_HAS_AUTOIDWE),
	.idwemodes	= (SIDWE_FOWCE | SIDWE_NO | SIDWE_SMAWT),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

stwuct omap_hwmod_cwass omap2_wfbi_hwmod_cwass = {
	.name	= "wfbi",
	.sysc	= &omap2_wfbi_sysc,
};

