// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>

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

#incwude "ccu-sun5i.h"

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
#define SUN5I_PWW_AUDIO_WEG	0x008

static stwuct ccu_sdm_setting pww_audio_sdm_tabwe[] = {
	{ .wate = 22579200, .pattewn = 0xc0010d84, .m = 8, .n = 7 },
	{ .wate = 24576000, .pattewn = 0xc000ac02, .m = 14, .n = 14 },
};

static stwuct ccu_nm pww_audio_base_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 7, 0),

	/*
	 * The datasheet is wwong hewe, this doesn't have any
	 * offset
	 */
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

static stwuct ccu_nkmp pww_ve_cwk = {
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

static stwuct ccu_nk pww_pewiph_cwk = {
	.enabwe		= BIT(31),
	.n		= _SUNXI_CCU_MUWT_OFFSET(8, 5, 0),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.fixed_post_div	= 2,
	.common		= {
		.weg		= 0x028,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph",
					      "hosc",
					      &ccu_nk_ops,
					      0),
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

static SUNXI_CCU_GATE(hosc_cwk,	"hosc",	"osc24M", 0x050, BIT(0), 0);

#define SUN5I_AHB_WEG	0x054
static const chaw * const cpu_pawents[] = { "osc32k", "hosc",
					    "pww-cowe" , "pww-pewiph" };
static const stwuct ccu_mux_fixed_pwediv cpu_pwedivs[] = {
	{ .index = 3, .div = 3, },
};
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

static const chaw * const ahb_pawents[] = { "axi" , "cpu", "pww-pewiph" };
static const stwuct ccu_mux_fixed_pwediv ahb_pwedivs[] = {
	{ .index = 2, .div = 2, },
};
static stwuct ccu_div ahb_cwk = {
	.div		= _SUNXI_CCU_DIV_FWAGS(4, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= {
		.shift		= 6,
		.width		= 2,
		.fixed_pwedivs	= ahb_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(ahb_pwedivs),
	},

	.common		= {
		.weg		= 0x054,
		.hw.init	= CWK_HW_INIT_PAWENTS("ahb",
						      ahb_pawents,
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

static const chaw * const apb1_pawents[] = { "hosc", "pww-pewiph", "osc32k" };
static SUNXI_CCU_MP_WITH_MUX(apb1_cwk, "apb1", apb1_pawents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static SUNXI_CCU_GATE(axi_dwam_cwk,	"axi-dwam",	"axi",
		      0x05c, BIT(0), 0);

static SUNXI_CCU_GATE(ahb_otg_cwk,	"ahb-otg",	"ahb",
		      0x060, BIT(0), 0);
static SUNXI_CCU_GATE(ahb_ehci_cwk,	"ahb-ehci",	"ahb",
		      0x060, BIT(1), 0);
static SUNXI_CCU_GATE(ahb_ohci_cwk,	"ahb-ohci",	"ahb",
		      0x060, BIT(2), 0);
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
static SUNXI_CCU_GATE(ahb_nand_cwk,	"ahb-nand",	"ahb",
		      0x060, BIT(13), 0);
static SUNXI_CCU_GATE(ahb_sdwam_cwk,	"ahb-sdwam",	"ahb",
		      0x060, BIT(14), CWK_IS_CWITICAW);
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
static SUNXI_CCU_GATE(ahb_gps_cwk,	"ahb-gps",	"ahb",
		      0x060, BIT(26), 0);
static SUNXI_CCU_GATE(ahb_hstimew_cwk,	"ahb-hstimew",	"ahb",
		      0x060, BIT(28), 0);

static SUNXI_CCU_GATE(ahb_ve_cwk,	"ahb-ve",	"ahb",
		      0x064, BIT(0), 0);
static SUNXI_CCU_GATE(ahb_tve_cwk,	"ahb-tve",	"ahb",
		      0x064, BIT(2), 0);
static SUNXI_CCU_GATE(ahb_wcd_cwk,	"ahb-wcd",	"ahb",
		      0x064, BIT(4), 0);
static SUNXI_CCU_GATE(ahb_csi_cwk,	"ahb-csi",	"ahb",
		      0x064, BIT(8), 0);
static SUNXI_CCU_GATE(ahb_hdmi_cwk,	"ahb-hdmi",	"ahb",
		      0x064, BIT(11), 0);
static SUNXI_CCU_GATE(ahb_de_be_cwk,	"ahb-de-be",	"ahb",
		      0x064, BIT(12), 0);
static SUNXI_CCU_GATE(ahb_de_fe_cwk,	"ahb-de-fe",	"ahb",
		      0x064, BIT(14), 0);
static SUNXI_CCU_GATE(ahb_iep_cwk,	"ahb-iep",	"ahb",
		      0x064, BIT(19), 0);
static SUNXI_CCU_GATE(ahb_gpu_cwk,	"ahb-gpu",	"ahb",
		      0x064, BIT(20), 0);

static SUNXI_CCU_GATE(apb0_codec_cwk,	"apb0-codec",	"apb0",
		      0x068, BIT(0), 0);
static SUNXI_CCU_GATE(apb0_spdif_cwk,	"apb0-spdif",	"apb0",
		      0x068, BIT(1), 0);
static SUNXI_CCU_GATE(apb0_i2s_cwk,	"apb0-i2s",	"apb0",
		      0x068, BIT(3), 0);
static SUNXI_CCU_GATE(apb0_pio_cwk,	"apb0-pio",	"apb0",
		      0x068, BIT(5), 0);
static SUNXI_CCU_GATE(apb0_iw_cwk,	"apb0-iw",	"apb0",
		      0x068, BIT(6), 0);
static SUNXI_CCU_GATE(apb0_keypad_cwk,	"apb0-keypad",	"apb0",
		      0x068, BIT(10), 0);

static SUNXI_CCU_GATE(apb1_i2c0_cwk,	"apb1-i2c0",	"apb1",
		      0x06c, BIT(0), 0);
static SUNXI_CCU_GATE(apb1_i2c1_cwk,	"apb1-i2c1",	"apb1",
		      0x06c, BIT(1), 0);
static SUNXI_CCU_GATE(apb1_i2c2_cwk,	"apb1-i2c2",	"apb1",
		      0x06c, BIT(2), 0);
static SUNXI_CCU_GATE(apb1_uawt0_cwk,	"apb1-uawt0",	"apb1",
		      0x06c, BIT(16), 0);
static SUNXI_CCU_GATE(apb1_uawt1_cwk,	"apb1-uawt1",	"apb1",
		      0x06c, BIT(17), 0);
static SUNXI_CCU_GATE(apb1_uawt2_cwk,	"apb1-uawt2",	"apb1",
		      0x06c, BIT(18), 0);
static SUNXI_CCU_GATE(apb1_uawt3_cwk,	"apb1-uawt3",	"apb1",
		      0x06c, BIT(19), 0);

static const chaw * const mod0_defauwt_pawents[] = { "hosc", "pww-pewiph",
						     "pww-ddw-othew" };
static SUNXI_CCU_MP_WITH_MUX_GATE(nand_cwk, "nand", mod0_defauwt_pawents, 0x080,
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

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_cwk, "mmc1", mod0_defauwt_pawents, 0x08c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc2_cwk, "mmc2", mod0_defauwt_pawents, 0x090,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

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

static SUNXI_CCU_MP_WITH_MUX_GATE(iw_cwk, "iw", mod0_defauwt_pawents, 0x0b0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static const chaw * const i2s_pawents[] = { "pww-audio-8x", "pww-audio-4x",
					    "pww-audio-2x", "pww-audio" };
static SUNXI_CCU_MUX_WITH_GATE(i2s_cwk, "i2s", i2s_pawents,
			       0x0b8, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw * const spdif_pawents[] = { "pww-audio-8x", "pww-audio-4x",
					    "pww-audio-2x", "pww-audio" };
static SUNXI_CCU_MUX_WITH_GATE(spdif_cwk, "spdif", spdif_pawents,
			       0x0c0, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw * const keypad_pawents[] = { "hosc", "wosc"};
static const u8 keypad_tabwe[] = { 0, 2 };
static stwuct ccu_mp keypad_cwk = {
	.enabwe		= BIT(31),
	.m		= _SUNXI_CCU_DIV(8, 5),
	.p		= _SUNXI_CCU_DIV(20, 2),
	.mux		= _SUNXI_CCU_MUX_TABWE(24, 2, keypad_tabwe),

	.common		= {
		.weg		= 0x0c4,
		.hw.init	= CWK_HW_INIT_PAWENTS("keypad",
						      keypad_pawents,
						      &ccu_mp_ops,
						      0),
	},
};

static SUNXI_CCU_GATE(usb_ohci_cwk,	"usb-ohci",	"pww-pewiph",
		      0x0cc, BIT(6), 0);
static SUNXI_CCU_GATE(usb_phy0_cwk,	"usb-phy0",	"pww-pewiph",
		      0x0cc, BIT(8), 0);
static SUNXI_CCU_GATE(usb_phy1_cwk,	"usb-phy1",	"pww-pewiph",
		      0x0cc, BIT(9), 0);

static const chaw * const gps_pawents[] = { "hosc", "pww-pewiph",
					    "pww-video1", "pww-ve" };
static SUNXI_CCU_M_WITH_MUX_GATE(gps_cwk, "gps", gps_pawents,
				 0x0d0, 0, 3, 24, 2, BIT(31), 0);

static SUNXI_CCU_GATE(dwam_ve_cwk,	"dwam-ve",	"pww-ddw",
		      0x100, BIT(0), 0);
static SUNXI_CCU_GATE(dwam_csi_cwk,	"dwam-csi",	"pww-ddw",
		      0x100, BIT(1), 0);
static SUNXI_CCU_GATE(dwam_ts_cwk,	"dwam-ts",	"pww-ddw",
		      0x100, BIT(3), 0);
static SUNXI_CCU_GATE(dwam_tve_cwk,	"dwam-tve",	"pww-ddw",
		      0x100, BIT(5), 0);
static SUNXI_CCU_GATE(dwam_de_fe_cwk,	"dwam-de-fe",	"pww-ddw",
		      0x100, BIT(25), 0);
static SUNXI_CCU_GATE(dwam_de_be_cwk,	"dwam-de-be",	"pww-ddw",
		      0x100, BIT(26), 0);
static SUNXI_CCU_GATE(dwam_ace_cwk,	"dwam-ace",	"pww-ddw",
		      0x100, BIT(29), 0);
static SUNXI_CCU_GATE(dwam_iep_cwk,	"dwam-iep",	"pww-ddw",
		      0x100, BIT(31), 0);

static const chaw * const de_pawents[] = { "pww-video0", "pww-video1",
					   "pww-ddw-othew" };
static SUNXI_CCU_M_WITH_MUX_GATE(de_be_cwk, "de-be", de_pawents,
				 0x104, 0, 4, 24, 2, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(de_fe_cwk, "de-fe", de_pawents,
				 0x10c, 0, 4, 24, 2, BIT(31), 0);

static const chaw * const tcon_pawents[] = { "pww-video0", "pww-video1",
					     "pww-video0-2x", "pww-video1-2x" };
static SUNXI_CCU_MUX_WITH_GATE(tcon_ch0_cwk, "tcon-ch0-scwk", tcon_pawents,
			       0x118, 24, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_M_WITH_MUX_GATE(tcon_ch1_scwk2_cwk, "tcon-ch1-scwk2",
				 tcon_pawents,
				 0x12c, 0, 4, 24, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_M_WITH_GATE(tcon_ch1_scwk1_cwk, "tcon-ch1-scwk1", "tcon-ch1-scwk2",
			     0x12c, 11, 1, BIT(15), CWK_SET_WATE_PAWENT);

static const chaw * const csi_pawents[] = { "hosc", "pww-video0", "pww-video1",
					    "pww-video0-2x", "pww-video1-2x" };
static const u8 csi_tabwe[] = { 0, 1, 2, 5, 6 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi_cwk, "csi",
				       csi_pawents, csi_tabwe,
				       0x134, 0, 5, 24, 3, BIT(31), 0);

static SUNXI_CCU_GATE(ve_cwk,		"ve",		"pww-ve",
		      0x13c, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(codec_cwk,	"codec",	"pww-audio",
		      0x140, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(avs_cwk,		"avs",		"hosc",
		      0x144, BIT(31), 0);

static const chaw * const hdmi_pawents[] = { "pww-video0", "pww-video0-2x" };
static const u8 hdmi_tabwe[] = { 0, 2 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(hdmi_cwk, "hdmi",
				       hdmi_pawents, hdmi_tabwe,
				       0x150, 0, 4, 24, 2, BIT(31),
				       CWK_SET_WATE_PAWENT);

static const chaw * const gpu_pawents[] = { "pww-video0", "pww-ve",
					    "pww-ddw-othew", "pww-video1",
					    "pww-video1-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(gpu_cwk, "gpu", gpu_pawents,
				 0x154, 0, 4, 24, 3, BIT(31), 0);

static const chaw * const mbus_pawents[] = { "hosc", "pww-pewiph", "pww-ddw" };
static SUNXI_CCU_MP_WITH_MUX_GATE(mbus_cwk, "mbus", mbus_pawents,
				  0x15c, 0, 4, 16, 2, 24, 2, BIT(31), CWK_IS_CWITICAW);

static SUNXI_CCU_GATE(iep_cwk,		"iep",		"de-be",
		      0x160, BIT(31), 0);

static stwuct ccu_common *sun5i_a10s_ccu_cwks[] = {
	&hosc_cwk.common,
	&pww_cowe_cwk.common,
	&pww_audio_base_cwk.common,
	&pww_video0_cwk.common,
	&pww_ve_cwk.common,
	&pww_ddw_base_cwk.common,
	&pww_ddw_cwk.common,
	&pww_ddw_othew_cwk.common,
	&pww_pewiph_cwk.common,
	&pww_video1_cwk.common,
	&cpu_cwk.common,
	&axi_cwk.common,
	&ahb_cwk.common,
	&apb0_cwk.common,
	&apb1_cwk.common,
	&axi_dwam_cwk.common,
	&ahb_otg_cwk.common,
	&ahb_ehci_cwk.common,
	&ahb_ohci_cwk.common,
	&ahb_ss_cwk.common,
	&ahb_dma_cwk.common,
	&ahb_bist_cwk.common,
	&ahb_mmc0_cwk.common,
	&ahb_mmc1_cwk.common,
	&ahb_mmc2_cwk.common,
	&ahb_nand_cwk.common,
	&ahb_sdwam_cwk.common,
	&ahb_emac_cwk.common,
	&ahb_ts_cwk.common,
	&ahb_spi0_cwk.common,
	&ahb_spi1_cwk.common,
	&ahb_spi2_cwk.common,
	&ahb_gps_cwk.common,
	&ahb_hstimew_cwk.common,
	&ahb_ve_cwk.common,
	&ahb_tve_cwk.common,
	&ahb_wcd_cwk.common,
	&ahb_csi_cwk.common,
	&ahb_hdmi_cwk.common,
	&ahb_de_be_cwk.common,
	&ahb_de_fe_cwk.common,
	&ahb_iep_cwk.common,
	&ahb_gpu_cwk.common,
	&apb0_codec_cwk.common,
	&apb0_spdif_cwk.common,
	&apb0_i2s_cwk.common,
	&apb0_pio_cwk.common,
	&apb0_iw_cwk.common,
	&apb0_keypad_cwk.common,
	&apb1_i2c0_cwk.common,
	&apb1_i2c1_cwk.common,
	&apb1_i2c2_cwk.common,
	&apb1_uawt0_cwk.common,
	&apb1_uawt1_cwk.common,
	&apb1_uawt2_cwk.common,
	&apb1_uawt3_cwk.common,
	&nand_cwk.common,
	&mmc0_cwk.common,
	&mmc1_cwk.common,
	&mmc2_cwk.common,
	&ts_cwk.common,
	&ss_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&spi2_cwk.common,
	&iw_cwk.common,
	&i2s_cwk.common,
	&spdif_cwk.common,
	&keypad_cwk.common,
	&usb_ohci_cwk.common,
	&usb_phy0_cwk.common,
	&usb_phy1_cwk.common,
	&gps_cwk.common,
	&dwam_ve_cwk.common,
	&dwam_csi_cwk.common,
	&dwam_ts_cwk.common,
	&dwam_tve_cwk.common,
	&dwam_de_fe_cwk.common,
	&dwam_de_be_cwk.common,
	&dwam_ace_cwk.common,
	&dwam_iep_cwk.common,
	&de_be_cwk.common,
	&de_fe_cwk.common,
	&tcon_ch0_cwk.common,
	&tcon_ch1_scwk2_cwk.common,
	&tcon_ch1_scwk1_cwk.common,
	&csi_cwk.common,
	&ve_cwk.common,
	&codec_cwk.common,
	&avs_cwk.common,
	&hdmi_cwk.common,
	&gpu_cwk.common,
	&mbus_cwk.common,
	&iep_cwk.common,
};

static const stwuct cwk_hw *cwk_pawent_pww_audio[] = {
	&pww_audio_base_cwk.common.hw
};

/* We hawdcode the dividew to 1 fow now */
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

static stwuct cwk_hw_oneceww_data sun5i_a10s_hw_cwks = {
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
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DDW_BASE]	= &pww_ddw_base_cwk.common.hw,
		[CWK_PWW_DDW]		= &pww_ddw_cwk.common.hw,
		[CWK_PWW_DDW_OTHEW]	= &pww_ddw_othew_cwk.common.hw,
		[CWK_PWW_PEWIPH]	= &pww_pewiph_cwk.common.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_PWW_VIDEO1_2X]	= &pww_video1_2x_cwk.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AHB]		= &ahb_cwk.common.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_DWAM_AXI]		= &axi_dwam_cwk.common.hw,
		[CWK_AHB_OTG]		= &ahb_otg_cwk.common.hw,
		[CWK_AHB_EHCI]		= &ahb_ehci_cwk.common.hw,
		[CWK_AHB_OHCI]		= &ahb_ohci_cwk.common.hw,
		[CWK_AHB_SS]		= &ahb_ss_cwk.common.hw,
		[CWK_AHB_DMA]		= &ahb_dma_cwk.common.hw,
		[CWK_AHB_BIST]		= &ahb_bist_cwk.common.hw,
		[CWK_AHB_MMC0]		= &ahb_mmc0_cwk.common.hw,
		[CWK_AHB_MMC1]		= &ahb_mmc1_cwk.common.hw,
		[CWK_AHB_MMC2]		= &ahb_mmc2_cwk.common.hw,
		[CWK_AHB_NAND]		= &ahb_nand_cwk.common.hw,
		[CWK_AHB_SDWAM]		= &ahb_sdwam_cwk.common.hw,
		[CWK_AHB_EMAC]		= &ahb_emac_cwk.common.hw,
		[CWK_AHB_TS]		= &ahb_ts_cwk.common.hw,
		[CWK_AHB_SPI0]		= &ahb_spi0_cwk.common.hw,
		[CWK_AHB_SPI1]		= &ahb_spi1_cwk.common.hw,
		[CWK_AHB_SPI2]		= &ahb_spi2_cwk.common.hw,
		[CWK_AHB_GPS]		= &ahb_gps_cwk.common.hw,
		[CWK_AHB_HSTIMEW]	= &ahb_hstimew_cwk.common.hw,
		[CWK_AHB_VE]		= &ahb_ve_cwk.common.hw,
		[CWK_AHB_TVE]		= &ahb_tve_cwk.common.hw,
		[CWK_AHB_WCD]		= &ahb_wcd_cwk.common.hw,
		[CWK_AHB_CSI]		= &ahb_csi_cwk.common.hw,
		[CWK_AHB_HDMI]		= &ahb_hdmi_cwk.common.hw,
		[CWK_AHB_DE_BE]		= &ahb_de_be_cwk.common.hw,
		[CWK_AHB_DE_FE]		= &ahb_de_fe_cwk.common.hw,
		[CWK_AHB_IEP]		= &ahb_iep_cwk.common.hw,
		[CWK_AHB_GPU]		= &ahb_gpu_cwk.common.hw,
		[CWK_APB0_CODEC]	= &apb0_codec_cwk.common.hw,
		[CWK_APB0_I2S]		= &apb0_i2s_cwk.common.hw,
		[CWK_APB0_PIO]		= &apb0_pio_cwk.common.hw,
		[CWK_APB0_IW]		= &apb0_iw_cwk.common.hw,
		[CWK_APB0_KEYPAD]	= &apb0_keypad_cwk.common.hw,
		[CWK_APB1_I2C0]		= &apb1_i2c0_cwk.common.hw,
		[CWK_APB1_I2C1]		= &apb1_i2c1_cwk.common.hw,
		[CWK_APB1_I2C2]		= &apb1_i2c2_cwk.common.hw,
		[CWK_APB1_UAWT0]	= &apb1_uawt0_cwk.common.hw,
		[CWK_APB1_UAWT1]	= &apb1_uawt1_cwk.common.hw,
		[CWK_APB1_UAWT2]	= &apb1_uawt2_cwk.common.hw,
		[CWK_APB1_UAWT3]	= &apb1_uawt3_cwk.common.hw,
		[CWK_NAND]		= &nand_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_TS]		= &ts_cwk.common.hw,
		[CWK_SS]		= &ss_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_IW]		= &iw_cwk.common.hw,
		[CWK_I2S]		= &i2s_cwk.common.hw,
		[CWK_KEYPAD]		= &keypad_cwk.common.hw,
		[CWK_USB_OHCI]		= &usb_ohci_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_PHY1]		= &usb_phy1_cwk.common.hw,
		[CWK_GPS]		= &gps_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI]		= &dwam_csi_cwk.common.hw,
		[CWK_DWAM_TS]		= &dwam_ts_cwk.common.hw,
		[CWK_DWAM_TVE]		= &dwam_tve_cwk.common.hw,
		[CWK_DWAM_DE_FE]	= &dwam_de_fe_cwk.common.hw,
		[CWK_DWAM_DE_BE]	= &dwam_de_be_cwk.common.hw,
		[CWK_DWAM_ACE]		= &dwam_ace_cwk.common.hw,
		[CWK_DWAM_IEP]		= &dwam_iep_cwk.common.hw,
		[CWK_DE_BE]		= &de_be_cwk.common.hw,
		[CWK_DE_FE]		= &de_fe_cwk.common.hw,
		[CWK_TCON_CH0]		= &tcon_ch0_cwk.common.hw,
		[CWK_TCON_CH1_SCWK]	= &tcon_ch1_scwk2_cwk.common.hw,
		[CWK_TCON_CH1]		= &tcon_ch1_scwk1_cwk.common.hw,
		[CWK_CSI]		= &csi_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_CODEC]		= &codec_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_HDMI]		= &hdmi_cwk.common.hw,
		[CWK_GPU]		= &gpu_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_IEP]		= &iep_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct ccu_weset_map sun5i_a10s_ccu_wesets[] = {
	[WST_USB_PHY0]		=  { 0x0cc, BIT(0) },
	[WST_USB_PHY1]		=  { 0x0cc, BIT(1) },

	[WST_GPS]		=  { 0x0d0, BIT(30) },

	[WST_DE_BE]		=  { 0x104, BIT(30) },

	[WST_DE_FE]		=  { 0x10c, BIT(30) },

	[WST_TVE]		=  { 0x118, BIT(29) },
	[WST_WCD]		=  { 0x118, BIT(30) },

	[WST_CSI]		=  { 0x134, BIT(30) },

	[WST_VE]		=  { 0x13c, BIT(0) },

	[WST_GPU]		=  { 0x154, BIT(30) },

	[WST_IEP]		=  { 0x160, BIT(30) },
};

static const stwuct sunxi_ccu_desc sun5i_a10s_ccu_desc = {
	.ccu_cwks	= sun5i_a10s_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun5i_a10s_ccu_cwks),

	.hw_cwks	= &sun5i_a10s_hw_cwks,

	.wesets		= sun5i_a10s_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun5i_a10s_ccu_wesets),
};

/*
 * The A13 is the A10s minus the TS, GPS, HDMI, I2S and the keypad
 */
static stwuct cwk_hw_oneceww_data sun5i_a13_hw_cwks = {
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
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DDW_BASE]	= &pww_ddw_base_cwk.common.hw,
		[CWK_PWW_DDW]		= &pww_ddw_cwk.common.hw,
		[CWK_PWW_DDW_OTHEW]	= &pww_ddw_othew_cwk.common.hw,
		[CWK_PWW_PEWIPH]	= &pww_pewiph_cwk.common.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_PWW_VIDEO1_2X]	= &pww_video1_2x_cwk.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AHB]		= &ahb_cwk.common.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_DWAM_AXI]		= &axi_dwam_cwk.common.hw,
		[CWK_AHB_OTG]		= &ahb_otg_cwk.common.hw,
		[CWK_AHB_EHCI]		= &ahb_ehci_cwk.common.hw,
		[CWK_AHB_OHCI]		= &ahb_ohci_cwk.common.hw,
		[CWK_AHB_SS]		= &ahb_ss_cwk.common.hw,
		[CWK_AHB_DMA]		= &ahb_dma_cwk.common.hw,
		[CWK_AHB_BIST]		= &ahb_bist_cwk.common.hw,
		[CWK_AHB_MMC0]		= &ahb_mmc0_cwk.common.hw,
		[CWK_AHB_MMC1]		= &ahb_mmc1_cwk.common.hw,
		[CWK_AHB_MMC2]		= &ahb_mmc2_cwk.common.hw,
		[CWK_AHB_NAND]		= &ahb_nand_cwk.common.hw,
		[CWK_AHB_SDWAM]		= &ahb_sdwam_cwk.common.hw,
		[CWK_AHB_EMAC]		= &ahb_emac_cwk.common.hw,
		[CWK_AHB_SPI0]		= &ahb_spi0_cwk.common.hw,
		[CWK_AHB_SPI1]		= &ahb_spi1_cwk.common.hw,
		[CWK_AHB_SPI2]		= &ahb_spi2_cwk.common.hw,
		[CWK_AHB_HSTIMEW]	= &ahb_hstimew_cwk.common.hw,
		[CWK_AHB_VE]		= &ahb_ve_cwk.common.hw,
		[CWK_AHB_TVE]		= &ahb_tve_cwk.common.hw,
		[CWK_AHB_WCD]		= &ahb_wcd_cwk.common.hw,
		[CWK_AHB_CSI]		= &ahb_csi_cwk.common.hw,
		[CWK_AHB_DE_BE]		= &ahb_de_be_cwk.common.hw,
		[CWK_AHB_DE_FE]		= &ahb_de_fe_cwk.common.hw,
		[CWK_AHB_IEP]		= &ahb_iep_cwk.common.hw,
		[CWK_AHB_GPU]		= &ahb_gpu_cwk.common.hw,
		[CWK_APB0_CODEC]	= &apb0_codec_cwk.common.hw,
		[CWK_APB0_PIO]		= &apb0_pio_cwk.common.hw,
		[CWK_APB0_IW]		= &apb0_iw_cwk.common.hw,
		[CWK_APB1_I2C0]		= &apb1_i2c0_cwk.common.hw,
		[CWK_APB1_I2C1]		= &apb1_i2c1_cwk.common.hw,
		[CWK_APB1_I2C2]		= &apb1_i2c2_cwk.common.hw,
		[CWK_APB1_UAWT0]	= &apb1_uawt0_cwk.common.hw,
		[CWK_APB1_UAWT1]	= &apb1_uawt1_cwk.common.hw,
		[CWK_APB1_UAWT2]	= &apb1_uawt2_cwk.common.hw,
		[CWK_APB1_UAWT3]	= &apb1_uawt3_cwk.common.hw,
		[CWK_NAND]		= &nand_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_SS]		= &ss_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_IW]		= &iw_cwk.common.hw,
		[CWK_USB_OHCI]		= &usb_ohci_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_PHY1]		= &usb_phy1_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI]		= &dwam_csi_cwk.common.hw,
		[CWK_DWAM_TVE]		= &dwam_tve_cwk.common.hw,
		[CWK_DWAM_DE_FE]	= &dwam_de_fe_cwk.common.hw,
		[CWK_DWAM_DE_BE]	= &dwam_de_be_cwk.common.hw,
		[CWK_DWAM_ACE]		= &dwam_ace_cwk.common.hw,
		[CWK_DWAM_IEP]		= &dwam_iep_cwk.common.hw,
		[CWK_DE_BE]		= &de_be_cwk.common.hw,
		[CWK_DE_FE]		= &de_fe_cwk.common.hw,
		[CWK_TCON_CH0]		= &tcon_ch0_cwk.common.hw,
		[CWK_TCON_CH1_SCWK]	= &tcon_ch1_scwk2_cwk.common.hw,
		[CWK_TCON_CH1]		= &tcon_ch1_scwk1_cwk.common.hw,
		[CWK_CSI]		= &csi_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_CODEC]		= &codec_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_GPU]		= &gpu_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_IEP]		= &iep_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static const stwuct sunxi_ccu_desc sun5i_a13_ccu_desc = {
	.ccu_cwks	= sun5i_a10s_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun5i_a10s_ccu_cwks),

	.hw_cwks	= &sun5i_a13_hw_cwks,

	.wesets		= sun5i_a10s_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun5i_a10s_ccu_wesets),
};

/*
 * The GW8 is the A10s CCU minus the HDMI and keypad, pwus SPDIF
 */
static stwuct cwk_hw_oneceww_data sun5i_gw8_hw_cwks = {
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
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DDW_BASE]	= &pww_ddw_base_cwk.common.hw,
		[CWK_PWW_DDW]		= &pww_ddw_cwk.common.hw,
		[CWK_PWW_DDW_OTHEW]	= &pww_ddw_othew_cwk.common.hw,
		[CWK_PWW_PEWIPH]	= &pww_pewiph_cwk.common.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_PWW_VIDEO1_2X]	= &pww_video1_2x_cwk.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AHB]		= &ahb_cwk.common.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_DWAM_AXI]		= &axi_dwam_cwk.common.hw,
		[CWK_AHB_OTG]		= &ahb_otg_cwk.common.hw,
		[CWK_AHB_EHCI]		= &ahb_ehci_cwk.common.hw,
		[CWK_AHB_OHCI]		= &ahb_ohci_cwk.common.hw,
		[CWK_AHB_SS]		= &ahb_ss_cwk.common.hw,
		[CWK_AHB_DMA]		= &ahb_dma_cwk.common.hw,
		[CWK_AHB_BIST]		= &ahb_bist_cwk.common.hw,
		[CWK_AHB_MMC0]		= &ahb_mmc0_cwk.common.hw,
		[CWK_AHB_MMC1]		= &ahb_mmc1_cwk.common.hw,
		[CWK_AHB_MMC2]		= &ahb_mmc2_cwk.common.hw,
		[CWK_AHB_NAND]		= &ahb_nand_cwk.common.hw,
		[CWK_AHB_SDWAM]		= &ahb_sdwam_cwk.common.hw,
		[CWK_AHB_EMAC]		= &ahb_emac_cwk.common.hw,
		[CWK_AHB_TS]		= &ahb_ts_cwk.common.hw,
		[CWK_AHB_SPI0]		= &ahb_spi0_cwk.common.hw,
		[CWK_AHB_SPI1]		= &ahb_spi1_cwk.common.hw,
		[CWK_AHB_SPI2]		= &ahb_spi2_cwk.common.hw,
		[CWK_AHB_GPS]		= &ahb_gps_cwk.common.hw,
		[CWK_AHB_HSTIMEW]	= &ahb_hstimew_cwk.common.hw,
		[CWK_AHB_VE]		= &ahb_ve_cwk.common.hw,
		[CWK_AHB_TVE]		= &ahb_tve_cwk.common.hw,
		[CWK_AHB_WCD]		= &ahb_wcd_cwk.common.hw,
		[CWK_AHB_CSI]		= &ahb_csi_cwk.common.hw,
		[CWK_AHB_DE_BE]		= &ahb_de_be_cwk.common.hw,
		[CWK_AHB_DE_FE]		= &ahb_de_fe_cwk.common.hw,
		[CWK_AHB_IEP]		= &ahb_iep_cwk.common.hw,
		[CWK_AHB_GPU]		= &ahb_gpu_cwk.common.hw,
		[CWK_APB0_CODEC]	= &apb0_codec_cwk.common.hw,
		[CWK_APB0_SPDIF]	= &apb0_spdif_cwk.common.hw,
		[CWK_APB0_I2S]		= &apb0_i2s_cwk.common.hw,
		[CWK_APB0_PIO]		= &apb0_pio_cwk.common.hw,
		[CWK_APB0_IW]		= &apb0_iw_cwk.common.hw,
		[CWK_APB1_I2C0]		= &apb1_i2c0_cwk.common.hw,
		[CWK_APB1_I2C1]		= &apb1_i2c1_cwk.common.hw,
		[CWK_APB1_I2C2]		= &apb1_i2c2_cwk.common.hw,
		[CWK_APB1_UAWT0]	= &apb1_uawt0_cwk.common.hw,
		[CWK_APB1_UAWT1]	= &apb1_uawt1_cwk.common.hw,
		[CWK_APB1_UAWT2]	= &apb1_uawt2_cwk.common.hw,
		[CWK_APB1_UAWT3]	= &apb1_uawt3_cwk.common.hw,
		[CWK_NAND]		= &nand_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_TS]		= &ts_cwk.common.hw,
		[CWK_SS]		= &ss_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_IW]		= &iw_cwk.common.hw,
		[CWK_I2S]		= &i2s_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_USB_OHCI]		= &usb_ohci_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_PHY1]		= &usb_phy1_cwk.common.hw,
		[CWK_GPS]		= &gps_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI]		= &dwam_csi_cwk.common.hw,
		[CWK_DWAM_TS]		= &dwam_ts_cwk.common.hw,
		[CWK_DWAM_TVE]		= &dwam_tve_cwk.common.hw,
		[CWK_DWAM_DE_FE]	= &dwam_de_fe_cwk.common.hw,
		[CWK_DWAM_DE_BE]	= &dwam_de_be_cwk.common.hw,
		[CWK_DWAM_ACE]		= &dwam_ace_cwk.common.hw,
		[CWK_DWAM_IEP]		= &dwam_iep_cwk.common.hw,
		[CWK_DE_BE]		= &de_be_cwk.common.hw,
		[CWK_DE_FE]		= &de_fe_cwk.common.hw,
		[CWK_TCON_CH0]		= &tcon_ch0_cwk.common.hw,
		[CWK_TCON_CH1_SCWK]	= &tcon_ch1_scwk2_cwk.common.hw,
		[CWK_TCON_CH1]		= &tcon_ch1_scwk1_cwk.common.hw,
		[CWK_CSI]		= &csi_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_CODEC]		= &codec_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_GPU]		= &gpu_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_IEP]		= &iep_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static const stwuct sunxi_ccu_desc sun5i_gw8_ccu_desc = {
	.ccu_cwks	= sun5i_a10s_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun5i_a10s_ccu_cwks),

	.hw_cwks	= &sun5i_gw8_hw_cwks,

	.wesets		= sun5i_a10s_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun5i_a10s_ccu_wesets),
};

static void __init sun5i_ccu_init(stwuct device_node *node,
				  const stwuct sunxi_ccu_desc *desc)
{
	void __iomem *weg;
	u32 vaw;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("%pOF: Couwd not map the cwock wegistews\n", node);
		wetuwn;
	}

	/* Fowce the PWW-Audio-1x dividew to 1 */
	vaw = weadw(weg + SUN5I_PWW_AUDIO_WEG);
	vaw &= ~GENMASK(29, 26);
	wwitew(vaw | (0 << 26), weg + SUN5I_PWW_AUDIO_WEG);

	/*
	 * Use the pewiphewaw PWW as the AHB pawent, instead of CPU /
	 * AXI which have wate changes due to cpufweq.
	 *
	 * This is especiawwy a big deaw fow the HS timew whose pawent
	 * cwock is AHB.
	 */
	vaw = weadw(weg + SUN5I_AHB_WEG);
	vaw &= ~GENMASK(7, 6);
	wwitew(vaw | (2 << 6), weg + SUN5I_AHB_WEG);

	of_sunxi_ccu_pwobe(node, weg, desc);
}

static void __init sun5i_a10s_ccu_setup(stwuct device_node *node)
{
	sun5i_ccu_init(node, &sun5i_a10s_ccu_desc);
}
CWK_OF_DECWAWE(sun5i_a10s_ccu, "awwwinnew,sun5i-a10s-ccu",
	       sun5i_a10s_ccu_setup);

static void __init sun5i_a13_ccu_setup(stwuct device_node *node)
{
	sun5i_ccu_init(node, &sun5i_a13_ccu_desc);
}
CWK_OF_DECWAWE(sun5i_a13_ccu, "awwwinnew,sun5i-a13-ccu",
	       sun5i_a13_ccu_setup);

static void __init sun5i_gw8_ccu_setup(stwuct device_node *node)
{
	sun5i_ccu_init(node, &sun5i_gw8_ccu_desc);
}
CWK_OF_DECWAWE(sun5i_gw8_ccu, "nextthing,gw8-ccu",
	       sun5i_gw8_ccu_setup);
