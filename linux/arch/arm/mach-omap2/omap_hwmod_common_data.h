/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap_hwmod_common_data.h - OMAP hwmod common macwos and decwawations
 *
 * Copywight (C) 2010-2011 Nokia Cowpowation
 * Copywight (C) 2010-2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 * Benoît Cousson
 */
#ifndef __AWCH_AWM_MACH_OMAP2_OMAP_HWMOD_COMMON_DATA_H
#define __AWCH_AWM_MACH_OMAP2_OMAP_HWMOD_COMMON_DATA_H

#incwude "omap_hwmod.h"

#incwude "common.h"
#incwude "dispway.h"

/* Common IP bwock data acwoss OMAP2xxx */
extewn stwuct omap_hwmod omap2xxx_w3_main_hwmod;
extewn stwuct omap_hwmod omap2xxx_w4_cowe_hwmod;
extewn stwuct omap_hwmod omap2xxx_w4_wkup_hwmod;
extewn stwuct omap_hwmod omap2xxx_mpu_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew3_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew4_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew5_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew6_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew7_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew8_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew9_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew10_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew11_hwmod;
extewn stwuct omap_hwmod omap2xxx_timew12_hwmod;
extewn stwuct omap_hwmod omap2xxx_wd_timew2_hwmod;
extewn stwuct omap_hwmod omap2xxx_uawt1_hwmod;
extewn stwuct omap_hwmod omap2xxx_uawt2_hwmod;
extewn stwuct omap_hwmod omap2xxx_uawt3_hwmod;
extewn stwuct omap_hwmod omap2xxx_dss_cowe_hwmod;
extewn stwuct omap_hwmod omap2xxx_dss_dispc_hwmod;
extewn stwuct omap_hwmod omap2xxx_dss_wfbi_hwmod;
extewn stwuct omap_hwmod omap2xxx_dss_venc_hwmod;
extewn stwuct omap_hwmod omap2xxx_gpio1_hwmod;
extewn stwuct omap_hwmod omap2xxx_gpio2_hwmod;
extewn stwuct omap_hwmod omap2xxx_gpio3_hwmod;
extewn stwuct omap_hwmod omap2xxx_gpio4_hwmod;
extewn stwuct omap_hwmod omap2xxx_mcspi1_hwmod;
extewn stwuct omap_hwmod omap2xxx_mcspi2_hwmod;
extewn stwuct omap_hwmod omap2xxx_gpmc_hwmod;
extewn stwuct omap_hwmod omap2xxx_wng_hwmod;
extewn stwuct omap_hwmod omap2xxx_sham_hwmod;
extewn stwuct omap_hwmod omap2xxx_aes_hwmod;

/* Common intewface data acwoss OMAP2xxx */
extewn stwuct omap_hwmod_ocp_if omap2xxx_w3_main__w4_cowe;
extewn stwuct omap_hwmod_ocp_if omap2xxx_mpu__w3_main;
extewn stwuct omap_hwmod_ocp_if omap2xxx_dss__w3;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__w4_wkup;
extewn stwuct omap_hwmod_ocp_if omap2_w4_cowe__uawt1;
extewn stwuct omap_hwmod_ocp_if omap2_w4_cowe__uawt2;
extewn stwuct omap_hwmod_ocp_if omap2_w4_cowe__uawt3;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__mcspi1;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__mcspi2;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew3;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew4;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew5;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew6;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew7;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew8;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew9;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew10;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew11;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew12;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__dss;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__dss_dispc;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__dss_wfbi;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__dss_venc;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__wng;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__sham;
extewn stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__aes;

/* OMAP hwmod cwasses - fowwawd decwawations */
extewn stwuct omap_hwmod_cwass w3_hwmod_cwass;
extewn stwuct omap_hwmod_cwass w4_hwmod_cwass;
extewn stwuct omap_hwmod_cwass mpu_hwmod_cwass;
extewn stwuct omap_hwmod_cwass iva_hwmod_cwass;
extewn stwuct omap_hwmod_cwass omap2_uawt_cwass;
extewn stwuct omap_hwmod_cwass omap2_dss_hwmod_cwass;
extewn stwuct omap_hwmod_cwass omap2_wfbi_hwmod_cwass;
extewn stwuct omap_hwmod_cwass omap2_venc_hwmod_cwass;
extewn stwuct omap_hwmod_cwass omap2_hdq1w_cwass;

extewn stwuct omap_hwmod_cwass omap2xxx_gpio_hwmod_cwass;
extewn stwuct omap_hwmod_cwass omap2xxx_maiwbox_hwmod_cwass;
extewn stwuct omap_hwmod_cwass omap2xxx_mcspi_cwass;

extewn stwuct omap_dss_dispc_dev_attw omap2_3_dss_dispc_dev_attw;

#endif
