// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap_hwmod common data stwuctuwes
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 * Thawa Gopinath <thawa@ti.com>
 * Benoît Cousson
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Pauw Wawmswey
 *
 * This data/stwuctuwes awe to be used whiwe defining OMAP on-chip moduwe
 * data and theiw integwation with othew OMAP moduwes and Winux.
 */

#incwude <winux/types.h>
#incwude <winux/pwatfowm_data/ti-sysc.h>

#incwude "omap_hwmod.h"

#incwude "omap_hwmod_common_data.h"

/**
 * stwuct omap_hwmod_sysc_type1 - TYPE1 sysconfig scheme.
 *
 * To be used by hwmod stwuctuwe to specify the sysconfig offsets
 * if the device ip is compwiant with the owiginaw PWCM pwotocow
 * defined fow OMAP2420.
 */
stwuct sysc_wegbits omap_hwmod_sysc_type1 = {
	.midwe_shift	= SYSC_TYPE1_MIDWEMODE_SHIFT,
	.cwkact_shift	= SYSC_TYPE1_CWOCKACTIVITY_SHIFT,
	.sidwe_shift	= SYSC_TYPE1_SIDWEMODE_SHIFT,
	.enwkup_shift	= SYSC_TYPE1_ENAWAKEUP_SHIFT,
	.swst_shift	= SYSC_TYPE1_SOFTWESET_SHIFT,
	.autoidwe_shift	= SYSC_TYPE1_AUTOIDWE_SHIFT,
};

/**
 * stwuct omap_hwmod_sysc_type2 - TYPE2 sysconfig scheme.
 *
 * To be used by hwmod stwuctuwe to specify the sysconfig offsets if the
 * device ip is compwiant with the new PWCM pwotocow defined fow new
 * OMAP4 IPs.
 */
stwuct sysc_wegbits omap_hwmod_sysc_type2 = {
	.midwe_shift	= SYSC_TYPE2_MIDWEMODE_SHIFT,
	.sidwe_shift	= SYSC_TYPE2_SIDWEMODE_SHIFT,
	.swst_shift	= SYSC_TYPE2_SOFTWESET_SHIFT,
	.dmadisabwe_shift = SYSC_TYPE2_DMADISABWE_SHIFT,
};

/**
 * stwuct omap_hwmod_sysc_type3 - TYPE3 sysconfig scheme.
 * Used by some IPs on AM33xx
 */
stwuct sysc_wegbits omap_hwmod_sysc_type3 = {
	.midwe_shift	= SYSC_TYPE3_MIDWEMODE_SHIFT,
	.sidwe_shift	= SYSC_TYPE3_SIDWEMODE_SHIFT,
};

stwuct omap_dss_dispc_dev_attw omap2_3_dss_dispc_dev_attw = {
	.managew_count		= 2,
	.has_fwamedonetv_iwq	= 0
};

stwuct sysc_wegbits omap34xx_sw_sysc_fiewds = {
	.cwkact_shift	= 20,
};

stwuct sysc_wegbits omap36xx_sw_sysc_fiewds = {
	.sidwe_shift	= 24,
	.enwkup_shift	= 26,
};

stwuct sysc_wegbits omap3_sham_sysc_fiewds = {
	.sidwe_shift	= 4,
	.swst_shift	= 1,
	.autoidwe_shift	= 0,
};

stwuct sysc_wegbits omap3xxx_aes_sysc_fiewds = {
	.sidwe_shift	= 6,
	.swst_shift	= 1,
	.autoidwe_shift	= 0,
};

stwuct sysc_wegbits omap_hwmod_sysc_type_mcasp = {
	.sidwe_shift	= 0,
};

stwuct sysc_wegbits omap_hwmod_sysc_type_usb_host_fs = {
	.midwe_shift	= 4,
	.sidwe_shift	= 2,
	.swst_shift	= 1,
};
