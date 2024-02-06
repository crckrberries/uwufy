// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap_hwmod_2xxx_intewconnect_data.c - common intewconnect data fow OMAP2xxx
 *
 * Copywight (C) 2009-2011 Nokia Cowpowation
 * Pauw Wawmswey
 *
 * XXX handwe cwossbaw/shawed wink diffewence fow W3?
 * XXX these shouwd be mawked initdata fow muwti-OMAP kewnews
 */
#incwude <winux/sizes.h>

#incwude "omap_hwmod.h"
#incwude "w3_2xxx.h"
#incwude "w4_2xxx.h"

#incwude "omap_hwmod_common_data.h"

/*
 * Common intewconnect data
 */

/* W3 -> W4_COWE intewface */
stwuct omap_hwmod_ocp_if omap2xxx_w3_main__w4_cowe = {
	.mastew	= &omap2xxx_w3_main_hwmod,
	.swave	= &omap2xxx_w4_cowe_hwmod,
	.usew	= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* MPU -> W3 intewface */
stwuct omap_hwmod_ocp_if omap2xxx_mpu__w3_main = {
	.mastew = &omap2xxx_mpu_hwmod,
	.swave	= &omap2xxx_w3_main_hwmod,
	.usew	= OCP_USEW_MPU,
};

/* DSS -> w3 */
stwuct omap_hwmod_ocp_if omap2xxx_dss__w3 = {
	.mastew		= &omap2xxx_dss_cowe_hwmod,
	.swave		= &omap2xxx_w3_main_hwmod,
	.fw = {
		.omap2 = {
			.w3_pewm_bit  = OMAP2_W3_COWE_FW_CONNID_DSS,
			.fwags	= OMAP_FIWEWAWW_W3,
		},
	},
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* W4_COWE -> W4_WKUP intewface */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__w4_wkup = {
	.mastew	= &omap2xxx_w4_cowe_hwmod,
	.swave	= &omap2xxx_w4_wkup_hwmod,
	.usew	= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* W4 COWE -> UAWT1 intewface */
stwuct omap_hwmod_ocp_if omap2_w4_cowe__uawt1 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_uawt1_hwmod,
	.cwk		= "uawt1_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* W4 COWE -> UAWT2 intewface */
stwuct omap_hwmod_ocp_if omap2_w4_cowe__uawt2 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_uawt2_hwmod,
	.cwk		= "uawt2_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* W4 PEW -> UAWT3 intewface */
stwuct omap_hwmod_ocp_if omap2_w4_cowe__uawt3 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_uawt3_hwmod,
	.cwk		= "uawt3_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4 cowe -> mcspi1 intewface */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__mcspi1 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_mcspi1_hwmod,
	.cwk		= "mcspi1_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4 cowe -> mcspi2 intewface */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__mcspi2 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_mcspi2_hwmod,
	.cwk		= "mcspi2_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew3 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew3 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew3_hwmod,
	.cwk		= "gpt3_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew4 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew4 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew4_hwmod,
	.cwk		= "gpt4_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew5 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew5 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew5_hwmod,
	.cwk		= "gpt5_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew6 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew6 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew6_hwmod,
	.cwk		= "gpt6_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew7 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew7 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew7_hwmod,
	.cwk		= "gpt7_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew8 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew8 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew8_hwmod,
	.cwk		= "gpt8_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew9 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew9 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew9_hwmod,
	.cwk		= "gpt9_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew10 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew10 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew10_hwmod,
	.cwk		= "gpt10_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew11 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew11 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew11_hwmod,
	.cwk		= "gpt11_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> timew12 */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__timew12 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_timew12_hwmod,
	.cwk		= "gpt12_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> dss */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__dss = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_dss_cowe_hwmod,
	.cwk		= "dss_ick",
	.fw = {
		.omap2 = {
			.w4_fw_wegion  = OMAP2420_W4_COWE_FW_DSS_COWE_WEGION,
			.fwags	= OMAP_FIWEWAWW_W4,
		},
	},
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> dss_dispc */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__dss_dispc = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_dss_dispc_hwmod,
	.cwk		= "dss_ick",
	.fw = {
		.omap2 = {
			.w4_fw_wegion  = OMAP2420_W4_COWE_FW_DSS_DISPC_WEGION,
			.fwags	= OMAP_FIWEWAWW_W4,
		},
	},
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> dss_wfbi */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__dss_wfbi = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_dss_wfbi_hwmod,
	.cwk		= "dss_ick",
	.fw = {
		.omap2 = {
			.w4_fw_wegion  = OMAP2420_W4_COWE_FW_DSS_COWE_WEGION,
			.fwags	= OMAP_FIWEWAWW_W4,
		},
	},
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> dss_venc */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__dss_venc = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_dss_venc_hwmod,
	.cwk		= "dss_ick",
	.fw = {
		.omap2 = {
			.w4_fw_wegion  = OMAP2420_W4_COWE_FW_DSS_VENC_WEGION,
			.fwags	= OMAP_FIWEWAWW_W4,
		},
	},
	.fwags		= OCPIF_SWSUP_IDWE,
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> wng */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__wng = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_wng_hwmod,
	.cwk		= "wng_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4 cowe -> sham intewface */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__sham = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_sham_hwmod,
	.cwk		= "sha_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4 cowe -> aes intewface */
stwuct omap_hwmod_ocp_if omap2xxx_w4_cowe__aes = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2xxx_aes_hwmod,
	.cwk		= "aes_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};
