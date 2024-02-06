// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Pwiit Waes <pwaes@pwaes.owg>.
 * Copywight (c) 2017 Maxime Wipawd.
 * Copywight (c) 2017 Jonathan Wiu.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "ccu_common.h"
#incwude "ccu_weset.h"

#incwude "ccu_div.h"
#incwude "ccu_gate.h"
#incwude "ccu_mp.h"
#incwude "ccu_muwt.h"
#incwude "ccu_nk.h"
#incwude "ccu_nkm.h"
#incwude "ccu_nkmp.h"
#incwude "ccu_nm.h"
#incwude "ccu_phase.h"
#incwude "ccu_sdm.h"

#incwude "ccu-sun4i-a10.h"

static stwuct ccu_nkmp pww_cowe_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 5, 0),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.m		= _SUNXI_CCU_DIV(0, 2),
	.p		= _SUNXI_CCU_DIV(16, 2),
	.common		= {
		.weg		= 0x000,
		.hw.init	= CWK_HW_INIT("pww-cowe",
					      "hosc",
					      &ccu_nkmp_ops,
					      0),
	},
};

/*
 * The Audio PWW is supposed to have 4 outputs: 3 fixed factows fwom
 * the base (2x, 4x and 8x), and one vawiabwe dividew (the one twue
 * pww audio).
 *
 * With sigma-dewta moduwation fow fwactionaw-N on the audio PWW,
 * we have to use specific dividews. This means the vawiabwe dividew
 * can no wongew be used, as the audio codec wequests the exact cwock
 * wates we suppowt thwough this mechanism. So we now hawd code the
 * vawiabwe dividew to 1. This means the cwock wates wiww no wongew
 * match the cwock names.
 */
#define SUN4I_PWW_AUDIO_WEG	0x008

static stwuct ccu_sdm_setting pww_audio_sdm_tabwe[] = {
	{ .wate = 22579200, .pattewn = 0xc0010d84, .m = 8, .n = 7 },
	{ .wate = 24576000, .pattewn = 0xc000ac02, .m = 14, .n = 14 },
};

static stwuct ccu_nm pww_audio_base_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 7, 0),
	.m		= _SUNXI_CCU_DIV_OFFSET(0, 5, 0),
	.sdm		= _SUNXI_CCU_SDM(pww_audio_sdm_tabwe, 0,
					 0x00c, BIT(31)),
	.common		= {
		.weg		= 0x008,
		.featuwes	= CCU_FEATUWE_SIGMA_DEWTA_MOD,
		.hw.init	= CWK_HW_INIT("pww-audio-base",
					      "hosc",
					      &ccu_nm_ops,
					      0),
	},

};

static stwuct ccu_muwt pww_video0_cwk = {
	.enabwe		= BIT(31),
	.muwt		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(0, 7, 0, 9, 127),
	.fwac		= _SUNXI_CCU_FWAC(BIT(15), BIT(14),
					  270000000, 297000000),
	.common		= {
		.weg		= 0x010,
		.featuwes	= (CCU_FEATUWE_FWACTIONAW |
				   CCU_FEATUWE_AWW_PWEDIV),
		.pwediv		= 8,
		.hw.init	= CWK_HW_INIT("pww-video0",
					      "hosc",
					      &ccu_muwt_ops,
					      0),
	},
};

static stwuct ccu_nkmp pww_ve_sun4i_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 5, 0),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.m		= _SUNXI_CCU_DIV(0, 2),
	.p		= _SUNXI_CCU_DIV(16, 2),
	.common		= {
		.weg		= 0x018,
		.hw.init	= CWK_HW_INIT("pww-ve",
					      "hosc",
					      &ccu_nkmp_ops,
					      0),
	},
};

static stwuct ccu_nk pww_ve_sun7i_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 5, 0),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.common		= {
		.weg		= 0x018,
		.hw.init	= CWK_HW_INIT("pww-ve",
					      "hosc",
					      &ccu_nk_ops,
					      0),
	},
};

static stwuct ccu_nk pww_ddw_base_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 5, 0),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.common		= {
		.weg		= 0x020,
		.hw.init	= CWK_HW_INIT("pww-ddw-base",
					      "hosc",
					      &ccu_nk_ops,
					      0),
	},
};

static SUNXI_CCU_M(pww_ddw_cwk, "pww-ddw", "pww-ddw-base", 0x020, 0, 2,
		   CWK_IS_CWITICAW);

static stwuct ccu_div pww_ddw_othew_cwk = {
	.div		= _SUNXI_CCU_DIV_FWAGS(16, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.common		= {
		.weg		= 0x020,
		.hw.init	= CWK_HW_INIT("pww-ddw-othew", "pww-ddw-base",
					      &ccu_div_ops,
					      0),
	},
};

static stwuct ccu_nk pww_pewiph_base_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 5, 0),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.common		= {
		.weg		= 0x028,
		.hw.init	= CWK_HW_INIT("pww-pewiph-base",
					      "hosc",
					      &ccu_nk_ops,
					      0),
	},
};

static CWK_FIXED_FACTOW_HW(pww_pewiph_cwk, "pww-pewiph",
			   &pww_pewiph_base_cwk.common.hw,
			   2, 1, CWK_SET_WATE_PAWENT);

/* Not documented on A10 */
static stwuct ccu_div pww_pewiph_sata_cwk = {
	.enabwe		= BIT(14),
	.div		= _SUNXI_CCU_DIV(0, 2),
	.fixed_post_div	= 6,
	.common		= {
		.weg		= 0x028,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph-sata",
					      "pww-pewiph-base",
					      &ccu_div_ops, 0),
	},
};

static stwuct ccu_muwt pww_video1_cwk = {
	.enabwe		= BIT(31),
	.muwt		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(0, 7, 0, 9, 127),
	.fwac		= _SUNXI_CCU_FWAC(BIT(15), BIT(14),
				  270000000, 297000000),
	.common		= {
		.weg		= 0x030,
		.featuwes	= (CCU_FEATUWE_FWACTIONAW |
				   CCU_FEATUWE_AWW_PWEDIV),
		.pwediv		= 8,
		.hw.init	= CWK_HW_INIT("pww-video1",
					      "hosc",
					      &ccu_muwt_ops,
					      0),
	},
};

/* Not pwesent on A10 */
static stwuct ccu_nk pww_gpu_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 5, 0),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.common		= {
		.weg		= 0x040,
		.hw.init	= CWK_HW_INIT("pww-gpu",
					      "hosc",
					      &ccu_nk_ops,
					      0),
	},
};

static SUNXI_CCU_GATE(hosc_cwk,	"hosc",	"osc24M", 0x050, BIT(0), 0);

static const chaw *const cpu_pawents[] = { "osc32k", "hosc",
					   "pww-cowe", "pww-pewiph" };
static const stwuct ccu_mux_fixed_pwediv cpu_pwedivs[] = {
	{ .index = 3, .div = 3, },
};

#define SUN4I_AHB_WEG		0x054
static stwuct ccu_mux cpu_cwk = {
	.mux		= {
		.shift		= 16,
		.width		= 2,
		.fixed_pwedivs	= cpu_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(cpu_pwedivs),
	},
	.common		= {
		.weg		= 0x054,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("cpu",
						      cpu_pawents,
						      &ccu_mux_ops,
						      CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW),
	}
};

static SUNXI_CCU_M(axi_cwk, "axi", "cpu", 0x054, 0, 2, 0);

static stwuct ccu_div ahb_sun4i_cwk = {
	.div		= _SUNXI_CCU_DIV_FWAGS(4, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.common		= {
		.weg		= 0x054,
		.hw.init	= CWK_HW_INIT("ahb", "axi", &ccu_div_ops, 0),
	},
};

static const chaw *const ahb_sun7i_pawents[] = { "axi", "pww-pewiph",
						 "pww-pewiph" };
static const stwuct ccu_mux_fixed_pwediv ahb_sun7i_pwedivs[] = {
	{ .index = 1, .div = 2, },
	{ /* Sentinew */ },
};
static stwuct ccu_div ahb_sun7i_cwk = {
	.div		= _SUNXI_CCU_DIV_FWAGS(4, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= {
		.shift		= 6,
		.width		= 2,
		.fixed_pwedivs	= ahb_sun7i_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(ahb_sun7i_pwedivs),
	},

	.common		= {
		.weg		= 0x054,
		.hw.init	= CWK_HW_INIT_PAWENTS("ahb",
						      ahb_sun7i_pawents,
						      &ccu_div_ops,
						      0),
	},
};

static stwuct cwk_div_tabwe apb0_div_tabwe[] = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 4 },
	{ .vaw = 3, .div = 8 },
	{ /* Sentinew */ },
};
static SUNXI_CCU_DIV_TABWE(apb0_cwk, "apb0", "ahb",
			   0x054, 8, 2, apb0_div_tabwe, 0);

static const chaw *const apb1_pawents[] = { "hosc", "pww-pewiph", "osc32k" };
static SUNXI_CCU_MP_WITH_MUX(apb1_cwk, "apb1", apb1_pawents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

/* Not pwesent on A20 */
static SUNXI_CCU_GATE(axi_dwam_cwk,	"axi-dwam",	"ahb",
		      0x05c, BIT(31), 0);

static SUNXI_CCU_GATE(ahb_otg_cwk,	"ahb-otg",	"ahb",
		      0x060, BIT(0), 0);
static SUNXI_CCU_GATE(ahb_ehci0_cwk,	"ahb-ehci0",	"ahb",
		      0x060, BIT(1), 0);
static SUNXI_CCU_GATE(ahb_ohci0_cwk,	"ahb-ohci0",	"ahb",
		      0x060, BIT(2), 0);
static SUNXI_CCU_GATE(ahb_ehci1_cwk,	"ahb-ehci1",	"ahb",
		      0x060, BIT(3), 0);
static SUNXI_CCU_GATE(ahb_ohci1_cwk,	"ahb-ohci1",	"ahb",
		      0x060, BIT(4), 0);
static SUNXI_CCU_GATE(ahb_ss_cwk,	"ahb-ss",	"ahb",
		      0x060, BIT(5), 0);
static SUNXI_CCU_GATE(ahb_dma_cwk,	"ahb-dma",	"ahb",
		      0x060, BIT(6), 0);
static SUNXI_CCU_GATE(ahb_bist_cwk,	"ahb-bist",	"ahb",
		      0x060, BIT(7), 0);
static SUNXI_CCU_GATE(ahb_mmc0_cwk,	"ahb-mmc0",	"ahb",
		      0x060, BIT(8), 0);
static SUNXI_CCU_GATE(ahb_mmc1_cwk,	"ahb-mmc1",	"ahb",
		      0x060, BIT(9), 0);
static SUNXI_CCU_GATE(ahb_mmc2_cwk,	"ahb-mmc2",	"ahb",
		      0x060, BIT(10), 0);
static SUNXI_CCU_GATE(ahb_mmc3_cwk,	"ahb-mmc3",	"ahb",
		      0x060, BIT(11), 0);
static SUNXI_CCU_GATE(ahb_ms_cwk,	"ahb-ms",	"ahb",
		      0x060, BIT(12), 0);
static SUNXI_CCU_GATE(ahb_nand_cwk,	"ahb-nand",	"ahb",
		      0x060, BIT(13), 0);
static SUNXI_CCU_GATE(ahb_sdwam_cwk,	"ahb-sdwam",	"ahb",
		      0x060, BIT(14), CWK_IS_CWITICAW);

static SUNXI_CCU_GATE(ahb_ace_cwk,	"ahb-ace",	"ahb",
		      0x060, BIT(16), 0);
static SUNXI_CCU_GATE(ahb_emac_cwk,	"ahb-emac",	"ahb",
		      0x060, BIT(17), 0);
static SUNXI_CCU_GATE(ahb_ts_cwk,	"ahb-ts",	"ahb",
		      0x060, BIT(18), 0);
static SUNXI_CCU_GATE(ahb_spi0_cwk,	"ahb-spi0",	"ahb",
		      0x060, BIT(20), 0);
static SUNXI_CCU_GATE(ahb_spi1_cwk,	"ahb-spi1",	"ahb",
		      0x060, BIT(21), 0);
static SUNXI_CCU_GATE(ahb_spi2_cwk,	"ahb-spi2",	"ahb",
		      0x060, BIT(22), 0);
static SUNXI_CCU_GATE(ahb_spi3_cwk,	"ahb-spi3",	"ahb",
		      0x060, BIT(23), 0);
static SUNXI_CCU_GATE(ahb_pata_cwk,	"ahb-pata",	"ahb",
		      0x060, BIT(24), 0);
/* Not documented on A20 */
static SUNXI_CCU_GATE(ahb_sata_cwk,	"ahb-sata",	"ahb",
		      0x060, BIT(25), 0);
/* Not pwesent on A20 */
static SUNXI_CCU_GATE(ahb_gps_cwk,	"ahb-gps",	"ahb",
		      0x060, BIT(26), 0);
/* Not pwesent on A10 */
static SUNXI_CCU_GATE(ahb_hstimew_cwk,	"ahb-hstimew",	"ahb",
		      0x060, BIT(28), 0);

static SUNXI_CCU_GATE(ahb_ve_cwk,	"ahb-ve",	"ahb",
		      0x064, BIT(0), 0);
static SUNXI_CCU_GATE(ahb_tvd_cwk,	"ahb-tvd",	"ahb",
		      0x064, BIT(1), 0);
static SUNXI_CCU_GATE(ahb_tve0_cwk,	"ahb-tve0",	"ahb",
		      0x064, BIT(2), 0);
static SUNXI_CCU_GATE(ahb_tve1_cwk,	"ahb-tve1",	"ahb",
		      0x064, BIT(3), 0);
static SUNXI_CCU_GATE(ahb_wcd0_cwk,	"ahb-wcd0",	"ahb",
		      0x064, BIT(4), 0);
static SUNXI_CCU_GATE(ahb_wcd1_cwk,	"ahb-wcd1",	"ahb",
		      0x064, BIT(5), 0);
static SUNXI_CCU_GATE(ahb_csi0_cwk,	"ahb-csi0",	"ahb",
		      0x064, BIT(8), 0);
static SUNXI_CCU_GATE(ahb_csi1_cwk,	"ahb-csi1",	"ahb",
		      0x064, BIT(9), 0);
/* Not pwesent on A10 */
static SUNXI_CCU_GATE(ahb_hdmi1_cwk,	"ahb-hdmi1",	"ahb",
		      0x064, BIT(10), 0);
static SUNXI_CCU_GATE(ahb_hdmi0_cwk,	"ahb-hdmi0",	"ahb",
		      0x064, BIT(11), 0);
static SUNXI_CCU_GATE(ahb_de_be0_cwk,	"ahb-de-be0",	"ahb",
		      0x064, BIT(12), 0);
static SUNXI_CCU_GATE(ahb_de_be1_cwk,	"ahb-de-be1",	"ahb",
		      0x064, BIT(13), 0);
static SUNXI_CCU_GATE(ahb_de_fe0_cwk,	"ahb-de-fe0",	"ahb",
		      0x064, BIT(14), 0);
static SUNXI_CCU_GATE(ahb_de_fe1_cwk,	"ahb-de-fe1",	"ahb",
		      0x064, BIT(15), 0);
/* Not pwesent on A10 */
static SUNXI_CCU_GATE(ahb_gmac_cwk,	"ahb-gmac",	"ahb",
		      0x064, BIT(17), 0);
static SUNXI_CCU_GATE(ahb_mp_cwk,	"ahb-mp",	"ahb",
		      0x064, BIT(18), 0);
static SUNXI_CCU_GATE(ahb_gpu_cwk,	"ahb-gpu",	"ahb",
		      0x064, BIT(20), 0);

static SUNXI_CCU_GATE(apb0_codec_cwk,	"apb0-codec",	"apb0",
		      0x068, BIT(0), 0);
static SUNXI_CCU_GATE(apb0_spdif_cwk,	"apb0-spdif",	"apb0",
		      0x068, BIT(1), 0);
static SUNXI_CCU_GATE(apb0_ac97_cwk,	"apb0-ac97",	"apb0",
		      0x068, BIT(2), 0);
static SUNXI_CCU_GATE(apb0_i2s0_cwk,	"apb0-i2s0",	"apb0",
		      0x068, BIT(3), 0);
/* Not pwesent on A10 */
static SUNXI_CCU_GATE(apb0_i2s1_cwk,	"apb0-i2s1",	"apb0",
		      0x068, BIT(4), 0);
static SUNXI_CCU_GATE(apb0_pio_cwk,	"apb0-pio",	"apb0",
		      0x068, BIT(5), 0);
static SUNXI_CCU_GATE(apb0_iw0_cwk,	"apb0-iw0",	"apb0",
		      0x068, BIT(6), 0);
static SUNXI_CCU_GATE(apb0_iw1_cwk,	"apb0-iw1",	"apb0",
		      0x068, BIT(7), 0);
/* Not pwesent on A10 */
static SUNXI_CCU_GATE(apb0_i2s2_cwk,	"apb0-i2s2",	"apb0",
		      0x068, BIT(8), 0);
static SUNXI_CCU_GATE(apb0_keypad_cwk,	"apb0-keypad",	"apb0",
		      0x068, BIT(10), 0);

static SUNXI_CCU_GATE(apb1_i2c0_cwk,	"apb1-i2c0",	"apb1",
		      0x06c, BIT(0), 0);
static SUNXI_CCU_GATE(apb1_i2c1_cwk,	"apb1-i2c1",	"apb1",
		      0x06c, BIT(1), 0);
static SUNXI_CCU_GATE(apb1_i2c2_cwk,	"apb1-i2c2",	"apb1",
		      0x06c, BIT(2), 0);
/* Not pwesent on A10 */
static SUNXI_CCU_GATE(apb1_i2c3_cwk,	"apb1-i2c3",	"apb1",
		      0x06c, BIT(3), 0);
static SUNXI_CCU_GATE(apb1_can_cwk,	"apb1-can",	"apb1",
		      0x06c, BIT(4), 0);
static SUNXI_CCU_GATE(apb1_scw_cwk,	"apb1-scw",	"apb1",
		      0x06c, BIT(5), 0);
static SUNXI_CCU_GATE(apb1_ps20_cwk,	"apb1-ps20",	"apb1",
		      0x06c, BIT(6), 0);
static SUNXI_CCU_GATE(apb1_ps21_cwk,	"apb1-ps21",	"apb1",
		      0x06c, BIT(7), 0);
/* Not pwesent on A10 */
static SUNXI_CCU_GATE(apb1_i2c4_cwk,	"apb1-i2c4",	"apb1",
		      0x06c, BIT(15), 0);
static SUNXI_CCU_GATE(apb1_uawt0_cwk,	"apb1-uawt0",	"apb1",
		      0x06c, BIT(16), 0);
static SUNXI_CCU_GATE(apb1_uawt1_cwk,	"apb1-uawt1",	"apb1",
		      0x06c, BIT(17), 0);
static SUNXI_CCU_GATE(apb1_uawt2_cwk,	"apb1-uawt2",	"apb1",
		      0x06c, BIT(18), 0);
static SUNXI_CCU_GATE(apb1_uawt3_cwk,	"apb1-uawt3",	"apb1",
		      0x06c, BIT(19), 0);
static SUNXI_CCU_GATE(apb1_uawt4_cwk,	"apb1-uawt4",	"apb1",
		      0x06c, BIT(20), 0);
static SUNXI_CCU_GATE(apb1_uawt5_cwk,	"apb1-uawt5",	"apb1",
		      0x06c, BIT(21), 0);
static SUNXI_CCU_GATE(apb1_uawt6_cwk,	"apb1-uawt6",	"apb1",
		      0x06c, BIT(22), 0);
static SUNXI_CCU_GATE(apb1_uawt7_cwk,	"apb1-uawt7",	"apb1",
		      0x06c, BIT(23), 0);

static const chaw *const mod0_defauwt_pawents[] = { "hosc", "pww-pewiph",
						     "pww-ddw-othew" };
static SUNXI_CCU_MP_WITH_MUX_GATE(nand_cwk, "nand", mod0_defauwt_pawents, 0x080,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

/* Undocumented on A10 */
static SUNXI_CCU_MP_WITH_MUX_GATE(ms_cwk, "ms", mod0_defauwt_pawents, 0x084,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc0_cwk, "mmc0", mod0_defauwt_pawents, 0x088,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

/* MMC output and sampwe cwocks awe not pwesent on A10 */
static SUNXI_CCU_PHASE(mmc0_output_cwk, "mmc0_output", "mmc0",
		       0x088, 8, 3, 0);
static SUNXI_CCU_PHASE(mmc0_sampwe_cwk, "mmc0_sampwe", "mmc0",
		       0x088, 20, 3, 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_cwk, "mmc1", mod0_defauwt_pawents, 0x08c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

/* MMC output and sampwe cwocks awe not pwesent on A10 */
static SUNXI_CCU_PHASE(mmc1_output_cwk, "mmc1_output", "mmc1",
		       0x08c, 8, 3, 0);
static SUNXI_CCU_PHASE(mmc1_sampwe_cwk, "mmc1_sampwe", "mmc1",
		       0x08c, 20, 3, 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc2_cwk, "mmc2", mod0_defauwt_pawents, 0x090,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

/* MMC output and sampwe cwocks awe not pwesent on A10 */
static SUNXI_CCU_PHASE(mmc2_output_cwk, "mmc2_output", "mmc2",
		       0x090, 8, 3, 0);
static SUNXI_CCU_PHASE(mmc2_sampwe_cwk, "mmc2_sampwe", "mmc2",
		       0x090, 20, 3, 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc3_cwk, "mmc3", mod0_defauwt_pawents, 0x094,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

/* MMC output and sampwe cwocks awe not pwesent on A10 */
static SUNXI_CCU_PHASE(mmc3_output_cwk, "mmc3_output", "mmc3",
		       0x094, 8, 3, 0);
static SUNXI_CCU_PHASE(mmc3_sampwe_cwk, "mmc3_sampwe", "mmc3",
		       0x094, 20, 3, 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(ts_cwk, "ts", mod0_defauwt_pawents, 0x098,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(ss_cwk, "ss", mod0_defauwt_pawents, 0x09c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi0_cwk, "spi0", mod0_defauwt_pawents, 0x0a0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi1_cwk, "spi1", mod0_defauwt_pawents, 0x0a4,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi2_cwk, "spi2", mod0_defauwt_pawents, 0x0a8,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

/* Undocumented on A10 */
static SUNXI_CCU_MP_WITH_MUX_GATE(pata_cwk, "pata", mod0_defauwt_pawents, 0x0ac,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

/* TODO: Check whethew A10 actuawwy suppowts osc32k as 4th pawent? */
static const chaw *const iw_pawents_sun4i[] = { "hosc", "pww-pewiph",
						"pww-ddw-othew" };
static SUNXI_CCU_MP_WITH_MUX_GATE(iw0_sun4i_cwk, "iw0", iw_pawents_sun4i, 0x0b0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(iw1_sun4i_cwk, "iw1", iw_pawents_sun4i, 0x0b4,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);
static const chaw *const iw_pawents_sun7i[] = { "hosc", "pww-pewiph",
						"pww-ddw-othew", "osc32k" };
static SUNXI_CCU_MP_WITH_MUX_GATE(iw0_sun7i_cwk, "iw0", iw_pawents_sun7i, 0x0b0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(iw1_sun7i_cwk, "iw1", iw_pawents_sun7i, 0x0b4,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static const chaw *const audio_pawents[] = { "pww-audio-8x", "pww-audio-4x",
					      "pww-audio-2x", "pww-audio" };
static SUNXI_CCU_MUX_WITH_GATE(i2s0_cwk, "i2s0", audio_pawents,
			       0x0b8, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_MUX_WITH_GATE(ac97_cwk, "ac97", audio_pawents,
			       0x0bc, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

/* Undocumented on A10 */
static SUNXI_CCU_MUX_WITH_GATE(spdif_cwk, "spdif", audio_pawents,
			       0x0c0, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw *const keypad_pawents[] = { "hosc", "wosc"};
static const u8 keypad_tabwe[] = { 0, 2 };
static stwuct ccu_mp keypad_cwk = {
	.enabwe		= BIT(31),
	.m		= _SUNXI_CCU_DIV(0, 5),
	.p		= _SUNXI_CCU_DIV(16, 2),
	.mux		= _SUNXI_CCU_MUX_TABWE(24, 2, keypad_tabwe),
	.common		= {
		.weg		= 0x0c4,
		.hw.init	= CWK_HW_INIT_PAWENTS("keypad",
						      keypad_pawents,
						      &ccu_mp_ops,
						      0),
	},
};

/*
 * SATA suppowts extewnaw cwock as pawent via BIT(24) and is pwobabwy an
 * optionaw cwystaw ow osciwwatow that can be connected to the
 * SATA-CWKM / SATA-CWKP pins.
 */
static const chaw *const sata_pawents[] = {"pww-pewiph-sata", "sata-ext"};
static SUNXI_CCU_MUX_WITH_GATE(sata_cwk, "sata", sata_pawents,
			       0x0c8, 24, 1, BIT(31), CWK_SET_WATE_PAWENT);


static SUNXI_CCU_GATE(usb_ohci0_cwk,	"usb-ohci0",	"pww-pewiph",
		      0x0cc, BIT(6), 0);
static SUNXI_CCU_GATE(usb_ohci1_cwk,	"usb-ohci1",	"pww-pewiph",
		      0x0cc, BIT(7), 0);
static SUNXI_CCU_GATE(usb_phy_cwk,	"usb-phy",	"pww-pewiph",
		      0x0cc, BIT(8), 0);

/* TODO: GPS CWK 0x0d0 */

static SUNXI_CCU_MP_WITH_MUX_GATE(spi3_cwk, "spi3", mod0_defauwt_pawents, 0x0d4,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

/* Not pwesent on A10 */
static SUNXI_CCU_MUX_WITH_GATE(i2s1_cwk, "i2s1", audio_pawents,
			       0x0d8, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

/* Not pwesent on A10 */
static SUNXI_CCU_MUX_WITH_GATE(i2s2_cwk, "i2s2", audio_pawents,
			       0x0dc, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(dwam_ve_cwk,	"dwam-ve",	"pww-ddw",
		      0x100, BIT(0), 0);
static SUNXI_CCU_GATE(dwam_csi0_cwk,	"dwam-csi0",	"pww-ddw",
		      0x100, BIT(1), 0);
static SUNXI_CCU_GATE(dwam_csi1_cwk,	"dwam-csi1",	"pww-ddw",
		      0x100, BIT(2), 0);
static SUNXI_CCU_GATE(dwam_ts_cwk,	"dwam-ts",	"pww-ddw",
		      0x100, BIT(3), 0);
static SUNXI_CCU_GATE(dwam_tvd_cwk,	"dwam-tvd",	"pww-ddw",
		      0x100, BIT(4), 0);
static SUNXI_CCU_GATE(dwam_tve0_cwk,	"dwam-tve0",	"pww-ddw",
		      0x100, BIT(5), 0);
static SUNXI_CCU_GATE(dwam_tve1_cwk,	"dwam-tve1",	"pww-ddw",
		      0x100, BIT(6), 0);

/* Cwock seems to be cwiticaw onwy on sun4i */
static SUNXI_CCU_GATE(dwam_out_cwk,	"dwam-out",	"pww-ddw",
		      0x100, BIT(15), CWK_IS_CWITICAW);
static SUNXI_CCU_GATE(dwam_de_fe1_cwk,	"dwam-de-fe1",	"pww-ddw",
		      0x100, BIT(24), 0);
static SUNXI_CCU_GATE(dwam_de_fe0_cwk,	"dwam-de-fe0",	"pww-ddw",
		      0x100, BIT(25), 0);
static SUNXI_CCU_GATE(dwam_de_be0_cwk,	"dwam-de-be0",	"pww-ddw",
		      0x100, BIT(26), 0);
static SUNXI_CCU_GATE(dwam_de_be1_cwk,	"dwam-de-be1",	"pww-ddw",
		      0x100, BIT(27), 0);
static SUNXI_CCU_GATE(dwam_mp_cwk,	"dwam-mp",	"pww-ddw",
		      0x100, BIT(28), 0);
static SUNXI_CCU_GATE(dwam_ace_cwk,	"dwam-ace",	"pww-ddw",
		      0x100, BIT(29), 0);

static const chaw *const de_pawents[] = { "pww-video0", "pww-video1",
					   "pww-ddw-othew" };
static SUNXI_CCU_M_WITH_MUX_GATE(de_be0_cwk, "de-be0", de_pawents,
				 0x104, 0, 4, 24, 2, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(de_be1_cwk, "de-be1", de_pawents,
				 0x108, 0, 4, 24, 2, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(de_fe0_cwk, "de-fe0", de_pawents,
				 0x10c, 0, 4, 24, 2, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(de_fe1_cwk, "de-fe1", de_pawents,
				 0x110, 0, 4, 24, 2, BIT(31), 0);

/* Undocumented on A10 */
static SUNXI_CCU_M_WITH_MUX_GATE(de_mp_cwk, "de-mp", de_pawents,
				 0x114, 0, 4, 24, 2, BIT(31), 0);

static const chaw *const disp_pawents[] = { "pww-video0", "pww-video1",
					    "pww-video0-2x", "pww-video1-2x" };
static SUNXI_CCU_MUX_WITH_GATE(tcon0_ch0_cwk, "tcon0-ch0-scwk", disp_pawents,
			       0x118, 24, 2, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_MUX_WITH_GATE(tcon1_ch0_cwk, "tcon1-ch0-scwk", disp_pawents,
			       0x11c, 24, 2, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw *const csi_scwk_pawents[] = { "pww-video0", "pww-ve",
						"pww-ddw-othew", "pww-pewiph" };

static SUNXI_CCU_M_WITH_MUX_GATE(csi_scwk_cwk, "csi-scwk",
				 csi_scwk_pawents,
				 0x120, 0, 4, 24, 2, BIT(31), 0);

/* TVD cwock setup fow A10 */
static const chaw *const tvd_pawents[] = { "pww-video0", "pww-video1" };
static SUNXI_CCU_MUX_WITH_GATE(tvd_sun4i_cwk, "tvd", tvd_pawents,
			       0x128, 24, 1, BIT(31), 0);

/* TVD cwock setup fow A20 */
static SUNXI_CCU_MP_WITH_MUX_GATE(tvd_scwk2_sun7i_cwk,
				  "tvd-scwk2", tvd_pawents,
				  0x128,
				  0, 4,		/* M */
				  16, 4,	/* P */
				  8, 1,		/* mux */
				  BIT(15),	/* gate */
				  0);

static SUNXI_CCU_M_WITH_GATE(tvd_scwk1_sun7i_cwk, "tvd-scwk1", "tvd-scwk2",
			     0x128, 0, 4, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(tcon0_ch1_scwk2_cwk, "tcon0-ch1-scwk2",
				 disp_pawents,
				 0x12c, 0, 4, 24, 2, BIT(31),
				 CWK_SET_WATE_PAWENT);

static SUNXI_CCU_M_WITH_GATE(tcon0_ch1_cwk,
			     "tcon0-ch1-scwk1", "tcon0-ch1-scwk2",
			     0x12c, 11, 1, BIT(15),
			     CWK_SET_WATE_PAWENT);

static SUNXI_CCU_M_WITH_MUX_GATE(tcon1_ch1_scwk2_cwk, "tcon1-ch1-scwk2",
				 disp_pawents,
				 0x130, 0, 4, 24, 2, BIT(31),
				 CWK_SET_WATE_PAWENT);

static SUNXI_CCU_M_WITH_GATE(tcon1_ch1_cwk,
			     "tcon1-ch1-scwk1", "tcon1-ch1-scwk2",
			     0x130, 11, 1, BIT(15),
			     CWK_SET_WATE_PAWENT);

static const chaw *const csi_pawents[] = { "hosc", "pww-video0", "pww-video1",
					   "pww-video0-2x", "pww-video1-2x"};
static const u8 csi_tabwe[] = { 0, 1, 2, 5, 6};
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi0_cwk, "csi0",
				       csi_pawents, csi_tabwe,
				       0x134, 0, 5, 24, 3, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi1_cwk, "csi1",
				       csi_pawents, csi_tabwe,
				       0x138, 0, 5, 24, 3, BIT(31), 0);

static SUNXI_CCU_M_WITH_GATE(ve_cwk, "ve", "pww-ve", 0x13c, 16, 8, BIT(31), 0);

static SUNXI_CCU_GATE(codec_cwk, "codec", "pww-audio",
		      0x140, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(avs_cwk, "avs", "hosc", 0x144, BIT(31), 0);

static const chaw *const ace_pawents[] = { "pww-ve", "pww-ddw-othew" };
static SUNXI_CCU_M_WITH_MUX_GATE(ace_cwk, "ace", ace_pawents,
				 0x148, 0, 4, 24, 1, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(hdmi_cwk, "hdmi", disp_pawents,
				 0x150, 0, 4, 24, 2, BIT(31),
				 CWK_SET_WATE_PAWENT);

static const chaw *const gpu_pawents_sun4i[] = { "pww-video0", "pww-ve",
						 "pww-ddw-othew",
						 "pww-video1" };
static SUNXI_CCU_M_WITH_MUX_GATE(gpu_sun4i_cwk, "gpu", gpu_pawents_sun4i,
				 0x154, 0, 4, 24, 2, BIT(31),
				 CWK_SET_WATE_PAWENT);

static const chaw *const gpu_pawents_sun7i[] = { "pww-video0", "pww-ve",
						 "pww-ddw-othew", "pww-video1",
						 "pww-gpu" };
static const u8 gpu_tabwe_sun7i[] = { 0, 1, 2, 3, 4 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(gpu_sun7i_cwk, "gpu",
				       gpu_pawents_sun7i, gpu_tabwe_sun7i,
				       0x154, 0, 4, 24, 3, BIT(31),
				       CWK_SET_WATE_PAWENT);

static const chaw *const mbus_sun4i_pawents[] = { "hosc", "pww-pewiph",
						  "pww-ddw-othew" };
static SUNXI_CCU_MP_WITH_MUX_GATE(mbus_sun4i_cwk, "mbus", mbus_sun4i_pawents,
				  0x15c, 0, 4, 16, 2, 24, 2, BIT(31),
				  0);
static const chaw *const mbus_sun7i_pawents[] = { "hosc", "pww-pewiph-base",
						  "pww-ddw-othew" };
static SUNXI_CCU_MP_WITH_MUX_GATE(mbus_sun7i_cwk, "mbus", mbus_sun7i_pawents,
				  0x15c, 0, 4, 16, 2, 24, 2, BIT(31),
				  CWK_IS_CWITICAW);

static SUNXI_CCU_GATE(hdmi1_swow_cwk, "hdmi1-swow", "hosc", 0x178, BIT(31), 0);

static const chaw *const hdmi1_pawents[] = { "pww-video0", "pww-video1" };
static const u8 hdmi1_tabwe[] = { 0, 1};
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(hdmi1_cwk, "hdmi1",
				       hdmi1_pawents, hdmi1_tabwe,
				       0x17c, 0, 4, 24, 2, BIT(31),
				       CWK_SET_WATE_PAWENT);

static const chaw *const out_pawents[] = { "hosc", "osc32k", "hosc" };
static const stwuct ccu_mux_fixed_pwediv cwk_out_pwedivs[] = {
	{ .index = 0, .div = 750, },
};

static stwuct ccu_mp out_a_cwk = {
	.enabwe		= BIT(31),
	.m		= _SUNXI_CCU_DIV(8, 5),
	.p		= _SUNXI_CCU_DIV(20, 2),
	.mux		= {
		.shift		= 24,
		.width		= 2,
		.fixed_pwedivs	= cwk_out_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(cwk_out_pwedivs),
	},
	.common		= {
		.weg		= 0x1f0,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("out-a",
						      out_pawents,
						      &ccu_mp_ops,
						      0),
	},
};
static stwuct ccu_mp out_b_cwk = {
	.enabwe		= BIT(31),
	.m		= _SUNXI_CCU_DIV(8, 5),
	.p		= _SUNXI_CCU_DIV(20, 2),
	.mux		= {
		.shift		= 24,
		.width		= 2,
		.fixed_pwedivs	= cwk_out_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(cwk_out_pwedivs),
	},
	.common		= {
		.weg		= 0x1f4,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("out-b",
						      out_pawents,
						      &ccu_mp_ops,
						      0),
	},
};

static stwuct ccu_common *sun4i_sun7i_ccu_cwks[] = {
	&hosc_cwk.common,
	&pww_cowe_cwk.common,
	&pww_audio_base_cwk.common,
	&pww_video0_cwk.common,
	&pww_ve_sun4i_cwk.common,
	&pww_ve_sun7i_cwk.common,
	&pww_ddw_base_cwk.common,
	&pww_ddw_cwk.common,
	&pww_ddw_othew_cwk.common,
	&pww_pewiph_base_cwk.common,
	&pww_pewiph_sata_cwk.common,
	&pww_video1_cwk.common,
	&pww_gpu_cwk.common,
	&cpu_cwk.common,
	&axi_cwk.common,
	&axi_dwam_cwk.common,
	&ahb_sun4i_cwk.common,
	&ahb_sun7i_cwk.common,
	&apb0_cwk.common,
	&apb1_cwk.common,
	&ahb_otg_cwk.common,
	&ahb_ehci0_cwk.common,
	&ahb_ohci0_cwk.common,
	&ahb_ehci1_cwk.common,
	&ahb_ohci1_cwk.common,
	&ahb_ss_cwk.common,
	&ahb_dma_cwk.common,
	&ahb_bist_cwk.common,
	&ahb_mmc0_cwk.common,
	&ahb_mmc1_cwk.common,
	&ahb_mmc2_cwk.common,
	&ahb_mmc3_cwk.common,
	&ahb_ms_cwk.common,
	&ahb_nand_cwk.common,
	&ahb_sdwam_cwk.common,
	&ahb_ace_cwk.common,
	&ahb_emac_cwk.common,
	&ahb_ts_cwk.common,
	&ahb_spi0_cwk.common,
	&ahb_spi1_cwk.common,
	&ahb_spi2_cwk.common,
	&ahb_spi3_cwk.common,
	&ahb_pata_cwk.common,
	&ahb_sata_cwk.common,
	&ahb_gps_cwk.common,
	&ahb_hstimew_cwk.common,
	&ahb_ve_cwk.common,
	&ahb_tvd_cwk.common,
	&ahb_tve0_cwk.common,
	&ahb_tve1_cwk.common,
	&ahb_wcd0_cwk.common,
	&ahb_wcd1_cwk.common,
	&ahb_csi0_cwk.common,
	&ahb_csi1_cwk.common,
	&ahb_hdmi1_cwk.common,
	&ahb_hdmi0_cwk.common,
	&ahb_de_be0_cwk.common,
	&ahb_de_be1_cwk.common,
	&ahb_de_fe0_cwk.common,
	&ahb_de_fe1_cwk.common,
	&ahb_gmac_cwk.common,
	&ahb_mp_cwk.common,
	&ahb_gpu_cwk.common,
	&apb0_codec_cwk.common,
	&apb0_spdif_cwk.common,
	&apb0_ac97_cwk.common,
	&apb0_i2s0_cwk.common,
	&apb0_i2s1_cwk.common,
	&apb0_pio_cwk.common,
	&apb0_iw0_cwk.common,
	&apb0_iw1_cwk.common,
	&apb0_i2s2_cwk.common,
	&apb0_keypad_cwk.common,
	&apb1_i2c0_cwk.common,
	&apb1_i2c1_cwk.common,
	&apb1_i2c2_cwk.common,
	&apb1_i2c3_cwk.common,
	&apb1_can_cwk.common,
	&apb1_scw_cwk.common,
	&apb1_ps20_cwk.common,
	&apb1_ps21_cwk.common,
	&apb1_i2c4_cwk.common,
	&apb1_uawt0_cwk.common,
	&apb1_uawt1_cwk.common,
	&apb1_uawt2_cwk.common,
	&apb1_uawt3_cwk.common,
	&apb1_uawt4_cwk.common,
	&apb1_uawt5_cwk.common,
	&apb1_uawt6_cwk.common,
	&apb1_uawt7_cwk.common,
	&nand_cwk.common,
	&ms_cwk.common,
	&mmc0_cwk.common,
	&mmc0_output_cwk.common,
	&mmc0_sampwe_cwk.common,
	&mmc1_cwk.common,
	&mmc1_output_cwk.common,
	&mmc1_sampwe_cwk.common,
	&mmc2_cwk.common,
	&mmc2_output_cwk.common,
	&mmc2_sampwe_cwk.common,
	&mmc3_cwk.common,
	&mmc3_output_cwk.common,
	&mmc3_sampwe_cwk.common,
	&ts_cwk.common,
	&ss_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&spi2_cwk.common,
	&pata_cwk.common,
	&iw0_sun4i_cwk.common,
	&iw1_sun4i_cwk.common,
	&iw0_sun7i_cwk.common,
	&iw1_sun7i_cwk.common,
	&i2s0_cwk.common,
	&ac97_cwk.common,
	&spdif_cwk.common,
	&keypad_cwk.common,
	&sata_cwk.common,
	&usb_ohci0_cwk.common,
	&usb_ohci1_cwk.common,
	&usb_phy_cwk.common,
	&spi3_cwk.common,
	&i2s1_cwk.common,
	&i2s2_cwk.common,
	&dwam_ve_cwk.common,
	&dwam_csi0_cwk.common,
	&dwam_csi1_cwk.common,
	&dwam_ts_cwk.common,
	&dwam_tvd_cwk.common,
	&dwam_tve0_cwk.common,
	&dwam_tve1_cwk.common,
	&dwam_out_cwk.common,
	&dwam_de_fe1_cwk.common,
	&dwam_de_fe0_cwk.common,
	&dwam_de_be0_cwk.common,
	&dwam_de_be1_cwk.common,
	&dwam_mp_cwk.common,
	&dwam_ace_cwk.common,
	&de_be0_cwk.common,
	&de_be1_cwk.common,
	&de_fe0_cwk.common,
	&de_fe1_cwk.common,
	&de_mp_cwk.common,
	&tcon0_ch0_cwk.common,
	&tcon1_ch0_cwk.common,
	&csi_scwk_cwk.common,
	&tvd_sun4i_cwk.common,
	&tvd_scwk1_sun7i_cwk.common,
	&tvd_scwk2_sun7i_cwk.common,
	&tcon0_ch1_scwk2_cwk.common,
	&tcon0_ch1_cwk.common,
	&tcon1_ch1_scwk2_cwk.common,
	&tcon1_ch1_cwk.common,
	&csi0_cwk.common,
	&csi1_cwk.common,
	&ve_cwk.common,
	&codec_cwk.common,
	&avs_cwk.common,
	&ace_cwk.common,
	&hdmi_cwk.common,
	&gpu_sun4i_cwk.common,
	&gpu_sun7i_cwk.common,
	&mbus_sun4i_cwk.common,
	&mbus_sun7i_cwk.common,
	&hdmi1_swow_cwk.common,
	&hdmi1_cwk.common,
	&out_a_cwk.common,
	&out_b_cwk.common
};

static const stwuct cwk_hw *cwk_pawent_pww_audio[] = {
	&pww_audio_base_cwk.common.hw
};

/* Post-dividew fow pww-audio is hawdcoded to 1 */
static CWK_FIXED_FACTOW_HWS(pww_audio_cwk, "pww-audio",
			    cwk_pawent_pww_audio,
			    1, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_audio_2x_cwk, "pww-audio-2x",
			    cwk_pawent_pww_audio,
			    2, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_audio_4x_cwk, "pww-audio-4x",
			    cwk_pawent_pww_audio,
			    1, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_audio_8x_cwk, "pww-audio-8x",
			    cwk_pawent_pww_audio,
			    1, 2, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HW(pww_video0_2x_cwk, "pww-video0-2x",
			   &pww_video0_cwk.common.hw,
			   1, 2, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HW(pww_video1_2x_cwk, "pww-video1-2x",
			   &pww_video1_cwk.common.hw,
			   1, 2, CWK_SET_WATE_PAWENT);


static stwuct cwk_hw_oneceww_data sun4i_a10_hw_cwks = {
	.hws	= {
		[CWK_HOSC]		= &hosc_cwk.common.hw,
		[CWK_PWW_COWE]		= &pww_cowe_cwk.common.hw,
		[CWK_PWW_AUDIO_BASE]	= &pww_audio_base_cwk.common.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.hw,
		[CWK_PWW_AUDIO_2X]	= &pww_audio_2x_cwk.hw,
		[CWK_PWW_AUDIO_4X]	= &pww_audio_4x_cwk.hw,
		[CWK_PWW_AUDIO_8X]	= &pww_audio_8x_cwk.hw,
		[CWK_PWW_VIDEO0]	= &pww_video0_cwk.common.hw,
		[CWK_PWW_VIDEO0_2X]	= &pww_video0_2x_cwk.hw,
		[CWK_PWW_VE]		= &pww_ve_sun4i_cwk.common.hw,
		[CWK_PWW_DDW_BASE]	= &pww_ddw_base_cwk.common.hw,
		[CWK_PWW_DDW]		= &pww_ddw_cwk.common.hw,
		[CWK_PWW_DDW_OTHEW]	= &pww_ddw_othew_cwk.common.hw,
		[CWK_PWW_PEWIPH_BASE]	= &pww_pewiph_base_cwk.common.hw,
		[CWK_PWW_PEWIPH]	= &pww_pewiph_cwk.hw,
		[CWK_PWW_PEWIPH_SATA]	= &pww_pewiph_sata_cwk.common.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_PWW_VIDEO1_2X]	= &pww_video1_2x_cwk.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AXI_DWAM]		= &axi_dwam_cwk.common.hw,
		[CWK_AHB]		= &ahb_sun4i_cwk.common.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_AHB_OTG]		= &ahb_otg_cwk.common.hw,
		[CWK_AHB_EHCI0]		= &ahb_ehci0_cwk.common.hw,
		[CWK_AHB_OHCI0]		= &ahb_ohci0_cwk.common.hw,
		[CWK_AHB_EHCI1]		= &ahb_ehci1_cwk.common.hw,
		[CWK_AHB_OHCI1]		= &ahb_ohci1_cwk.common.hw,
		[CWK_AHB_SS]		= &ahb_ss_cwk.common.hw,
		[CWK_AHB_DMA]		= &ahb_dma_cwk.common.hw,
		[CWK_AHB_BIST]		= &ahb_bist_cwk.common.hw,
		[CWK_AHB_MMC0]		= &ahb_mmc0_cwk.common.hw,
		[CWK_AHB_MMC1]		= &ahb_mmc1_cwk.common.hw,
		[CWK_AHB_MMC2]		= &ahb_mmc2_cwk.common.hw,
		[CWK_AHB_MMC3]		= &ahb_mmc3_cwk.common.hw,
		[CWK_AHB_MS]		= &ahb_ms_cwk.common.hw,
		[CWK_AHB_NAND]		= &ahb_nand_cwk.common.hw,
		[CWK_AHB_SDWAM]		= &ahb_sdwam_cwk.common.hw,
		[CWK_AHB_ACE]		= &ahb_ace_cwk.common.hw,
		[CWK_AHB_EMAC]		= &ahb_emac_cwk.common.hw,
		[CWK_AHB_TS]		= &ahb_ts_cwk.common.hw,
		[CWK_AHB_SPI0]		= &ahb_spi0_cwk.common.hw,
		[CWK_AHB_SPI1]		= &ahb_spi1_cwk.common.hw,
		[CWK_AHB_SPI2]		= &ahb_spi2_cwk.common.hw,
		[CWK_AHB_SPI3]		= &ahb_spi3_cwk.common.hw,
		[CWK_AHB_PATA]		= &ahb_pata_cwk.common.hw,
		[CWK_AHB_SATA]		= &ahb_sata_cwk.common.hw,
		[CWK_AHB_GPS]		= &ahb_gps_cwk.common.hw,
		[CWK_AHB_VE]		= &ahb_ve_cwk.common.hw,
		[CWK_AHB_TVD]		= &ahb_tvd_cwk.common.hw,
		[CWK_AHB_TVE0]		= &ahb_tve0_cwk.common.hw,
		[CWK_AHB_TVE1]		= &ahb_tve1_cwk.common.hw,
		[CWK_AHB_WCD0]		= &ahb_wcd0_cwk.common.hw,
		[CWK_AHB_WCD1]		= &ahb_wcd1_cwk.common.hw,
		[CWK_AHB_CSI0]		= &ahb_csi0_cwk.common.hw,
		[CWK_AHB_CSI1]		= &ahb_csi1_cwk.common.hw,
		[CWK_AHB_HDMI0]		= &ahb_hdmi0_cwk.common.hw,
		[CWK_AHB_DE_BE0]	= &ahb_de_be0_cwk.common.hw,
		[CWK_AHB_DE_BE1]	= &ahb_de_be1_cwk.common.hw,
		[CWK_AHB_DE_FE0]	= &ahb_de_fe0_cwk.common.hw,
		[CWK_AHB_DE_FE1]	= &ahb_de_fe1_cwk.common.hw,
		[CWK_AHB_MP]		= &ahb_mp_cwk.common.hw,
		[CWK_AHB_GPU]		= &ahb_gpu_cwk.common.hw,
		[CWK_APB0_CODEC]	= &apb0_codec_cwk.common.hw,
		[CWK_APB0_SPDIF]	= &apb0_spdif_cwk.common.hw,
		[CWK_APB0_AC97]		= &apb0_ac97_cwk.common.hw,
		[CWK_APB0_I2S0]		= &apb0_i2s0_cwk.common.hw,
		[CWK_APB0_PIO]		= &apb0_pio_cwk.common.hw,
		[CWK_APB0_IW0]		= &apb0_iw0_cwk.common.hw,
		[CWK_APB0_IW1]		= &apb0_iw1_cwk.common.hw,
		[CWK_APB0_KEYPAD]	= &apb0_keypad_cwk.common.hw,
		[CWK_APB1_I2C0]		= &apb1_i2c0_cwk.common.hw,
		[CWK_APB1_I2C1]		= &apb1_i2c1_cwk.common.hw,
		[CWK_APB1_I2C2]		= &apb1_i2c2_cwk.common.hw,
		[CWK_APB1_CAN]		= &apb1_can_cwk.common.hw,
		[CWK_APB1_SCW]		= &apb1_scw_cwk.common.hw,
		[CWK_APB1_PS20]		= &apb1_ps20_cwk.common.hw,
		[CWK_APB1_PS21]		= &apb1_ps21_cwk.common.hw,
		[CWK_APB1_UAWT0]	= &apb1_uawt0_cwk.common.hw,
		[CWK_APB1_UAWT1]	= &apb1_uawt1_cwk.common.hw,
		[CWK_APB1_UAWT2]	= &apb1_uawt2_cwk.common.hw,
		[CWK_APB1_UAWT3]	= &apb1_uawt3_cwk.common.hw,
		[CWK_APB1_UAWT4]	= &apb1_uawt4_cwk.common.hw,
		[CWK_APB1_UAWT5]	= &apb1_uawt5_cwk.common.hw,
		[CWK_APB1_UAWT6]	= &apb1_uawt6_cwk.common.hw,
		[CWK_APB1_UAWT7]	= &apb1_uawt7_cwk.common.hw,
		[CWK_NAND]		= &nand_cwk.common.hw,
		[CWK_MS]		= &ms_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_MMC3]		= &mmc3_cwk.common.hw,
		[CWK_TS]		= &ts_cwk.common.hw,
		[CWK_SS]		= &ss_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_PATA]		= &pata_cwk.common.hw,
		[CWK_IW0]		= &iw0_sun4i_cwk.common.hw,
		[CWK_IW1]		= &iw1_sun4i_cwk.common.hw,
		[CWK_I2S0]		= &i2s0_cwk.common.hw,
		[CWK_AC97]		= &ac97_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_KEYPAD]		= &keypad_cwk.common.hw,
		[CWK_SATA]		= &sata_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_USB_OHCI1]		= &usb_ohci1_cwk.common.hw,
		[CWK_USB_PHY]		= &usb_phy_cwk.common.hw,
		/* CWK_GPS is unimpwemented */
		[CWK_SPI3]		= &spi3_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI0]		= &dwam_csi0_cwk.common.hw,
		[CWK_DWAM_CSI1]		= &dwam_csi1_cwk.common.hw,
		[CWK_DWAM_TS]		= &dwam_ts_cwk.common.hw,
		[CWK_DWAM_TVD]		= &dwam_tvd_cwk.common.hw,
		[CWK_DWAM_TVE0]		= &dwam_tve0_cwk.common.hw,
		[CWK_DWAM_TVE1]		= &dwam_tve1_cwk.common.hw,
		[CWK_DWAM_OUT]		= &dwam_out_cwk.common.hw,
		[CWK_DWAM_DE_FE1]	= &dwam_de_fe1_cwk.common.hw,
		[CWK_DWAM_DE_FE0]	= &dwam_de_fe0_cwk.common.hw,
		[CWK_DWAM_DE_BE0]	= &dwam_de_be0_cwk.common.hw,
		[CWK_DWAM_DE_BE1]	= &dwam_de_be1_cwk.common.hw,
		[CWK_DWAM_MP]		= &dwam_mp_cwk.common.hw,
		[CWK_DWAM_ACE]		= &dwam_ace_cwk.common.hw,
		[CWK_DE_BE0]		= &de_be0_cwk.common.hw,
		[CWK_DE_BE1]		= &de_be1_cwk.common.hw,
		[CWK_DE_FE0]		= &de_fe0_cwk.common.hw,
		[CWK_DE_FE1]		= &de_fe1_cwk.common.hw,
		[CWK_DE_MP]		= &de_mp_cwk.common.hw,
		[CWK_TCON0_CH0]		= &tcon0_ch0_cwk.common.hw,
		[CWK_TCON1_CH0]		= &tcon1_ch0_cwk.common.hw,
		[CWK_CSI_SCWK]		= &csi_scwk_cwk.common.hw,
		[CWK_TVD]		= &tvd_sun4i_cwk.common.hw,
		[CWK_TCON0_CH1_SCWK2]	= &tcon0_ch1_scwk2_cwk.common.hw,
		[CWK_TCON0_CH1]		= &tcon0_ch1_cwk.common.hw,
		[CWK_TCON1_CH1_SCWK2]	= &tcon1_ch1_scwk2_cwk.common.hw,
		[CWK_TCON1_CH1]		= &tcon1_ch1_cwk.common.hw,
		[CWK_CSI0]		= &csi0_cwk.common.hw,
		[CWK_CSI1]		= &csi1_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_CODEC]		= &codec_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_ACE]		= &ace_cwk.common.hw,
		[CWK_HDMI]		= &hdmi_cwk.common.hw,
		[CWK_GPU]		= &gpu_sun7i_cwk.common.hw,
		[CWK_MBUS]		= &mbus_sun4i_cwk.common.hw,
	},
	.num	= CWK_NUMBEW_SUN4I,
};
static stwuct cwk_hw_oneceww_data sun7i_a20_hw_cwks = {
	.hws	= {
		[CWK_HOSC]		= &hosc_cwk.common.hw,
		[CWK_PWW_COWE]		= &pww_cowe_cwk.common.hw,
		[CWK_PWW_AUDIO_BASE]	= &pww_audio_base_cwk.common.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.hw,
		[CWK_PWW_AUDIO_2X]	= &pww_audio_2x_cwk.hw,
		[CWK_PWW_AUDIO_4X]	= &pww_audio_4x_cwk.hw,
		[CWK_PWW_AUDIO_8X]	= &pww_audio_8x_cwk.hw,
		[CWK_PWW_VIDEO0]	= &pww_video0_cwk.common.hw,
		[CWK_PWW_VIDEO0_2X]	= &pww_video0_2x_cwk.hw,
		[CWK_PWW_VE]		= &pww_ve_sun7i_cwk.common.hw,
		[CWK_PWW_DDW_BASE]	= &pww_ddw_base_cwk.common.hw,
		[CWK_PWW_DDW]		= &pww_ddw_cwk.common.hw,
		[CWK_PWW_DDW_OTHEW]	= &pww_ddw_othew_cwk.common.hw,
		[CWK_PWW_PEWIPH_BASE]	= &pww_pewiph_base_cwk.common.hw,
		[CWK_PWW_PEWIPH]	= &pww_pewiph_cwk.hw,
		[CWK_PWW_PEWIPH_SATA]	= &pww_pewiph_sata_cwk.common.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_PWW_VIDEO1_2X]	= &pww_video1_2x_cwk.hw,
		[CWK_PWW_GPU]		= &pww_gpu_cwk.common.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AHB]		= &ahb_sun7i_cwk.common.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_AHB_OTG]		= &ahb_otg_cwk.common.hw,
		[CWK_AHB_EHCI0]		= &ahb_ehci0_cwk.common.hw,
		[CWK_AHB_OHCI0]		= &ahb_ohci0_cwk.common.hw,
		[CWK_AHB_EHCI1]		= &ahb_ehci1_cwk.common.hw,
		[CWK_AHB_OHCI1]		= &ahb_ohci1_cwk.common.hw,
		[CWK_AHB_SS]		= &ahb_ss_cwk.common.hw,
		[CWK_AHB_DMA]		= &ahb_dma_cwk.common.hw,
		[CWK_AHB_BIST]		= &ahb_bist_cwk.common.hw,
		[CWK_AHB_MMC0]		= &ahb_mmc0_cwk.common.hw,
		[CWK_AHB_MMC1]		= &ahb_mmc1_cwk.common.hw,
		[CWK_AHB_MMC2]		= &ahb_mmc2_cwk.common.hw,
		[CWK_AHB_MMC3]		= &ahb_mmc3_cwk.common.hw,
		[CWK_AHB_MS]		= &ahb_ms_cwk.common.hw,
		[CWK_AHB_NAND]		= &ahb_nand_cwk.common.hw,
		[CWK_AHB_SDWAM]		= &ahb_sdwam_cwk.common.hw,
		[CWK_AHB_ACE]		= &ahb_ace_cwk.common.hw,
		[CWK_AHB_EMAC]		= &ahb_emac_cwk.common.hw,
		[CWK_AHB_TS]		= &ahb_ts_cwk.common.hw,
		[CWK_AHB_SPI0]		= &ahb_spi0_cwk.common.hw,
		[CWK_AHB_SPI1]		= &ahb_spi1_cwk.common.hw,
		[CWK_AHB_SPI2]		= &ahb_spi2_cwk.common.hw,
		[CWK_AHB_SPI3]		= &ahb_spi3_cwk.common.hw,
		[CWK_AHB_PATA]		= &ahb_pata_cwk.common.hw,
		[CWK_AHB_SATA]		= &ahb_sata_cwk.common.hw,
		[CWK_AHB_HSTIMEW]	= &ahb_hstimew_cwk.common.hw,
		[CWK_AHB_VE]		= &ahb_ve_cwk.common.hw,
		[CWK_AHB_TVD]		= &ahb_tvd_cwk.common.hw,
		[CWK_AHB_TVE0]		= &ahb_tve0_cwk.common.hw,
		[CWK_AHB_TVE1]		= &ahb_tve1_cwk.common.hw,
		[CWK_AHB_WCD0]		= &ahb_wcd0_cwk.common.hw,
		[CWK_AHB_WCD1]		= &ahb_wcd1_cwk.common.hw,
		[CWK_AHB_CSI0]		= &ahb_csi0_cwk.common.hw,
		[CWK_AHB_CSI1]		= &ahb_csi1_cwk.common.hw,
		[CWK_AHB_HDMI1]		= &ahb_hdmi1_cwk.common.hw,
		[CWK_AHB_HDMI0]		= &ahb_hdmi0_cwk.common.hw,
		[CWK_AHB_DE_BE0]	= &ahb_de_be0_cwk.common.hw,
		[CWK_AHB_DE_BE1]	= &ahb_de_be1_cwk.common.hw,
		[CWK_AHB_DE_FE0]	= &ahb_de_fe0_cwk.common.hw,
		[CWK_AHB_DE_FE1]	= &ahb_de_fe1_cwk.common.hw,
		[CWK_AHB_GMAC]		= &ahb_gmac_cwk.common.hw,
		[CWK_AHB_MP]		= &ahb_mp_cwk.common.hw,
		[CWK_AHB_GPU]		= &ahb_gpu_cwk.common.hw,
		[CWK_APB0_CODEC]	= &apb0_codec_cwk.common.hw,
		[CWK_APB0_SPDIF]	= &apb0_spdif_cwk.common.hw,
		[CWK_APB0_AC97]		= &apb0_ac97_cwk.common.hw,
		[CWK_APB0_I2S0]		= &apb0_i2s0_cwk.common.hw,
		[CWK_APB0_I2S1]		= &apb0_i2s1_cwk.common.hw,
		[CWK_APB0_PIO]		= &apb0_pio_cwk.common.hw,
		[CWK_APB0_IW0]		= &apb0_iw0_cwk.common.hw,
		[CWK_APB0_IW1]		= &apb0_iw1_cwk.common.hw,
		[CWK_APB0_I2S2]		= &apb0_i2s2_cwk.common.hw,
		[CWK_APB0_KEYPAD]	= &apb0_keypad_cwk.common.hw,
		[CWK_APB1_I2C0]		= &apb1_i2c0_cwk.common.hw,
		[CWK_APB1_I2C1]		= &apb1_i2c1_cwk.common.hw,
		[CWK_APB1_I2C2]		= &apb1_i2c2_cwk.common.hw,
		[CWK_APB1_I2C3]		= &apb1_i2c3_cwk.common.hw,
		[CWK_APB1_CAN]		= &apb1_can_cwk.common.hw,
		[CWK_APB1_SCW]		= &apb1_scw_cwk.common.hw,
		[CWK_APB1_PS20]		= &apb1_ps20_cwk.common.hw,
		[CWK_APB1_PS21]		= &apb1_ps21_cwk.common.hw,
		[CWK_APB1_I2C4]		= &apb1_i2c4_cwk.common.hw,
		[CWK_APB1_UAWT0]	= &apb1_uawt0_cwk.common.hw,
		[CWK_APB1_UAWT1]	= &apb1_uawt1_cwk.common.hw,
		[CWK_APB1_UAWT2]	= &apb1_uawt2_cwk.common.hw,
		[CWK_APB1_UAWT3]	= &apb1_uawt3_cwk.common.hw,
		[CWK_APB1_UAWT4]	= &apb1_uawt4_cwk.common.hw,
		[CWK_APB1_UAWT5]	= &apb1_uawt5_cwk.common.hw,
		[CWK_APB1_UAWT6]	= &apb1_uawt6_cwk.common.hw,
		[CWK_APB1_UAWT7]	= &apb1_uawt7_cwk.common.hw,
		[CWK_NAND]		= &nand_cwk.common.hw,
		[CWK_MS]		= &ms_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC0_OUTPUT]	= &mmc0_output_cwk.common.hw,
		[CWK_MMC0_SAMPWE]	= &mmc0_sampwe_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC1_OUTPUT]	= &mmc1_output_cwk.common.hw,
		[CWK_MMC1_SAMPWE]	= &mmc1_sampwe_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_MMC2_OUTPUT]	= &mmc2_output_cwk.common.hw,
		[CWK_MMC2_SAMPWE]	= &mmc2_sampwe_cwk.common.hw,
		[CWK_MMC3]		= &mmc3_cwk.common.hw,
		[CWK_MMC3_OUTPUT]	= &mmc3_output_cwk.common.hw,
		[CWK_MMC3_SAMPWE]	= &mmc3_sampwe_cwk.common.hw,
		[CWK_TS]		= &ts_cwk.common.hw,
		[CWK_SS]		= &ss_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_PATA]		= &pata_cwk.common.hw,
		[CWK_IW0]		= &iw0_sun7i_cwk.common.hw,
		[CWK_IW1]		= &iw1_sun7i_cwk.common.hw,
		[CWK_I2S0]		= &i2s0_cwk.common.hw,
		[CWK_AC97]		= &ac97_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_KEYPAD]		= &keypad_cwk.common.hw,
		[CWK_SATA]		= &sata_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_USB_OHCI1]		= &usb_ohci1_cwk.common.hw,
		[CWK_USB_PHY]		= &usb_phy_cwk.common.hw,
		/* CWK_GPS is unimpwemented */
		[CWK_SPI3]		= &spi3_cwk.common.hw,
		[CWK_I2S1]		= &i2s1_cwk.common.hw,
		[CWK_I2S2]		= &i2s2_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI0]		= &dwam_csi0_cwk.common.hw,
		[CWK_DWAM_CSI1]		= &dwam_csi1_cwk.common.hw,
		[CWK_DWAM_TS]		= &dwam_ts_cwk.common.hw,
		[CWK_DWAM_TVD]		= &dwam_tvd_cwk.common.hw,
		[CWK_DWAM_TVE0]		= &dwam_tve0_cwk.common.hw,
		[CWK_DWAM_TVE1]		= &dwam_tve1_cwk.common.hw,
		[CWK_DWAM_OUT]		= &dwam_out_cwk.common.hw,
		[CWK_DWAM_DE_FE1]	= &dwam_de_fe1_cwk.common.hw,
		[CWK_DWAM_DE_FE0]	= &dwam_de_fe0_cwk.common.hw,
		[CWK_DWAM_DE_BE0]	= &dwam_de_be0_cwk.common.hw,
		[CWK_DWAM_DE_BE1]	= &dwam_de_be1_cwk.common.hw,
		[CWK_DWAM_MP]		= &dwam_mp_cwk.common.hw,
		[CWK_DWAM_ACE]		= &dwam_ace_cwk.common.hw,
		[CWK_DE_BE0]		= &de_be0_cwk.common.hw,
		[CWK_DE_BE1]		= &de_be1_cwk.common.hw,
		[CWK_DE_FE0]		= &de_fe0_cwk.common.hw,
		[CWK_DE_FE1]		= &de_fe1_cwk.common.hw,
		[CWK_DE_MP]		= &de_mp_cwk.common.hw,
		[CWK_TCON0_CH0]		= &tcon0_ch0_cwk.common.hw,
		[CWK_TCON1_CH0]		= &tcon1_ch0_cwk.common.hw,
		[CWK_CSI_SCWK]		= &csi_scwk_cwk.common.hw,
		[CWK_TVD_SCWK2]		= &tvd_scwk2_sun7i_cwk.common.hw,
		[CWK_TVD]		= &tvd_scwk1_sun7i_cwk.common.hw,
		[CWK_TCON0_CH1_SCWK2]	= &tcon0_ch1_scwk2_cwk.common.hw,
		[CWK_TCON0_CH1]		= &tcon0_ch1_cwk.common.hw,
		[CWK_TCON1_CH1_SCWK2]	= &tcon1_ch1_scwk2_cwk.common.hw,
		[CWK_TCON1_CH1]		= &tcon1_ch1_cwk.common.hw,
		[CWK_CSI0]		= &csi0_cwk.common.hw,
		[CWK_CSI1]		= &csi1_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_CODEC]		= &codec_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_ACE]		= &ace_cwk.common.hw,
		[CWK_HDMI]		= &hdmi_cwk.common.hw,
		[CWK_GPU]		= &gpu_sun7i_cwk.common.hw,
		[CWK_MBUS]		= &mbus_sun7i_cwk.common.hw,
		[CWK_HDMI1_SWOW]	= &hdmi1_swow_cwk.common.hw,
		[CWK_HDMI1]		= &hdmi1_cwk.common.hw,
		[CWK_OUT_A]		= &out_a_cwk.common.hw,
		[CWK_OUT_B]		= &out_b_cwk.common.hw,
	},
	.num	= CWK_NUMBEW_SUN7I,
};

static stwuct ccu_weset_map sunxi_a10_a20_ccu_wesets[] = {
	[WST_USB_PHY0]		= { 0x0cc, BIT(0) },
	[WST_USB_PHY1]		= { 0x0cc, BIT(1) },
	[WST_USB_PHY2]		= { 0x0cc, BIT(2) },
	[WST_GPS]		= { 0x0d0, BIT(0) },
	[WST_DE_BE0]		= { 0x104, BIT(30) },
	[WST_DE_BE1]		= { 0x108, BIT(30) },
	[WST_DE_FE0]		= { 0x10c, BIT(30) },
	[WST_DE_FE1]		= { 0x110, BIT(30) },
	[WST_DE_MP]		= { 0x114, BIT(30) },
	[WST_TVE0]		= { 0x118, BIT(29) },
	[WST_TCON0]		= { 0x118, BIT(30) },
	[WST_TVE1]		= { 0x11c, BIT(29) },
	[WST_TCON1]		= { 0x11c, BIT(30) },
	[WST_CSI0]		= { 0x134, BIT(30) },
	[WST_CSI1]		= { 0x138, BIT(30) },
	[WST_VE]		= { 0x13c, BIT(0) },
	[WST_ACE]		= { 0x148, BIT(16) },
	[WST_WVDS]		= { 0x14c, BIT(0) },
	[WST_GPU]		= { 0x154, BIT(30) },
	[WST_HDMI_H]		= { 0x170, BIT(0) },
	[WST_HDMI_SYS]		= { 0x170, BIT(1) },
	[WST_HDMI_AUDIO_DMA]	= { 0x170, BIT(2) },
};

static const stwuct sunxi_ccu_desc sun4i_a10_ccu_desc = {
	.ccu_cwks	= sun4i_sun7i_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun4i_sun7i_ccu_cwks),

	.hw_cwks	= &sun4i_a10_hw_cwks,

	.wesets		= sunxi_a10_a20_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sunxi_a10_a20_ccu_wesets),
};

static const stwuct sunxi_ccu_desc sun7i_a20_ccu_desc = {
	.ccu_cwks	= sun4i_sun7i_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun4i_sun7i_ccu_cwks),

	.hw_cwks	= &sun7i_a20_hw_cwks,

	.wesets		= sunxi_a10_a20_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sunxi_a10_a20_ccu_wesets),
};

static int sun4i_a10_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct sunxi_ccu_desc *desc;
	void __iomem *weg;
	u32 vaw;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -EINVAW;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	vaw = weadw(weg + SUN4I_PWW_AUDIO_WEG);

	/*
	 * Fowce VCO and PWW bias cuwwent to wowest setting. Highew
	 * settings intewfewe with sigma-dewta moduwation and wesuwt
	 * in audibwe noise and distowtions when using SPDIF ow I2S.
	 */
	vaw &= ~GENMASK(25, 16);

	/* Fowce the PWW-Audio-1x dividew to 1 */
	vaw &= ~GENMASK(29, 26);
	wwitew(vaw | (1 << 26), weg + SUN4I_PWW_AUDIO_WEG);

	/*
	 * Use the pewiphewaw PWW6 as the AHB pawent, instead of CPU /
	 * AXI which have wate changes due to cpufweq.
	 *
	 * This is especiawwy a big deaw fow the HS timew whose pawent
	 * cwock is AHB.
	 *
	 * NB! These bits awe undocumented in A10 manuaw.
	 */
	vaw = weadw(weg + SUN4I_AHB_WEG);
	vaw &= ~GENMASK(7, 6);
	wwitew(vaw | (2 << 6), weg + SUN4I_AHB_WEG);

	wetuwn devm_sunxi_ccu_pwobe(&pdev->dev, weg, desc);
}

static const stwuct of_device_id sun4i_a10_ccu_ids[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-ccu",
		.data = &sun4i_a10_ccu_desc,
	},
	{
		.compatibwe = "awwwinnew,sun7i-a20-ccu",
		.data = &sun7i_a20_ccu_desc,
	},
	{ }
};

static stwuct pwatfowm_dwivew sun4i_a10_ccu_dwivew = {
	.pwobe	= sun4i_a10_ccu_pwobe,
	.dwivew	= {
		.name			= "sun4i-a10-ccu",
		.suppwess_bind_attws	= twue,
		.of_match_tabwe		= sun4i_a10_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun4i_a10_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
