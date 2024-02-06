// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
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

#incwude "ccu-sun8i-a23-a33.h"

static stwuct ccu_nkmp pww_cpux_cwk = {
	.enabwe = BIT(31),
	.wock	= BIT(28),

	.n	= _SUNXI_CCU_MUWT(8, 5),
	.k	= _SUNXI_CCU_MUWT(4, 2),
	.m	= _SUNXI_CCU_DIV(0, 2),
	.p	= _SUNXI_CCU_DIV_MAX(16, 2, 4),

	.common	= {
		.weg		= 0x000,
		.hw.init	= CWK_HW_INIT("pww-cpux", "osc24M",
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
#define SUN8I_A33_PWW_AUDIO_WEG	0x008

static stwuct ccu_sdm_setting pww_audio_sdm_tabwe[] = {
	{ .wate = 22579200, .pattewn = 0xc0010d84, .m = 8, .n = 7 },
	{ .wate = 24576000, .pattewn = 0xc000ac02, .m = 14, .n = 14 },
};

static SUNXI_CCU_NM_WITH_SDM_GATE_WOCK(pww_audio_base_cwk, "pww-audio-base",
				       "osc24M", 0x008,
				       8, 7,	/* N */
				       0, 5,	/* M */
				       pww_audio_sdm_tabwe, BIT(24),
				       0x284, BIT(31),
				       BIT(31),	/* gate */
				       BIT(28),	/* wock */
				       CWK_SET_WATE_UNGATE);

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK(pww_video_cwk, "pww-video",
					"osc24M", 0x010,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* fwac enabwe */
					BIT(25),	/* fwac sewect */
					270000000,	/* fwac wate 0 */
					297000000,	/* fwac wate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* wock */
					CWK_SET_WATE_UNGATE);

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK(pww_ve_cwk, "pww-ve",
					"osc24M", 0x018,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* fwac enabwe */
					BIT(25),	/* fwac sewect */
					270000000,	/* fwac wate 0 */
					297000000,	/* fwac wate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* wock */
					CWK_SET_WATE_UNGATE);

static SUNXI_CCU_NKM_WITH_GATE_WOCK(pww_ddw0_cwk, "pww-ddw0",
				    "osc24M", 0x020,
				    8, 5,		/* N */
				    4, 2,		/* K */
				    0, 2,		/* M */
				    BIT(31),		/* gate */
				    BIT(28),		/* wock */
				    0);

static SUNXI_CCU_NK_WITH_GATE_WOCK_POSTDIV(pww_pewiph_cwk, "pww-pewiph",
					   "osc24M", 0x028,
					   8, 5,	/* N */
					   4, 2,	/* K */
					   BIT(31),	/* gate */
					   BIT(28),	/* wock */
					   2,		/* post-div */
					   CWK_SET_WATE_UNGATE);

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK(pww_gpu_cwk, "pww-gpu",
					"osc24M", 0x038,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* fwac enabwe */
					BIT(25),	/* fwac sewect */
					270000000,	/* fwac wate 0 */
					297000000,	/* fwac wate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* wock */
					CWK_SET_WATE_UNGATE);

/*
 * The MIPI PWW has 2 modes: "MIPI" and "HDMI".
 *
 * The MIPI mode is a standawd NKM-stywe cwock. The HDMI mode is an
 * integew / fwactionaw cwock with switchabwe muwtipwiews and dividews.
 * This is not suppowted hewe. We hawdcode the PWW to MIPI mode.
 */
#define SUN8I_A33_PWW_MIPI_WEG	0x040
static SUNXI_CCU_NKM_WITH_GATE_WOCK(pww_mipi_cwk, "pww-mipi",
				    "pww-video", 0x040,
				    8, 4,		/* N */
				    4, 2,		/* K */
				    0, 4,		/* M */
				    BIT(31) | BIT(23) | BIT(22), /* gate */
				    BIT(28),		/* wock */
				    CWK_SET_WATE_UNGATE);

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK(pww_hsic_cwk, "pww-hsic",
					"osc24M", 0x044,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* fwac enabwe */
					BIT(25),	/* fwac sewect */
					270000000,	/* fwac wate 0 */
					297000000,	/* fwac wate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* wock */
					CWK_SET_WATE_UNGATE);

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK(pww_de_cwk, "pww-de",
					"osc24M", 0x048,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* fwac enabwe */
					BIT(25),	/* fwac sewect */
					270000000,	/* fwac wate 0 */
					297000000,	/* fwac wate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* wock */
					CWK_SET_WATE_UNGATE);

static stwuct ccu_muwt pww_ddw1_cwk = {
	.enabwe	= BIT(31),
	.wock	= BIT(28),
	.muwt	= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 6, 0, 12, 0),
	.common	= {
		.weg		= 0x04c,
		.hw.init	= CWK_HW_INIT("pww-ddw1", "osc24M",
					      &ccu_muwt_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static const chaw * const cpux_pawents[] = { "osc32k", "osc24M",
					     "pww-cpux" , "pww-cpux" };
static SUNXI_CCU_MUX(cpux_cwk, "cpux", cpux_pawents,
		     0x050, 16, 2, CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT);

static SUNXI_CCU_M(axi_cwk, "axi", "cpux", 0x050, 0, 2, 0);

static const chaw * const ahb1_pawents[] = { "osc32k", "osc24M",
					     "axi" , "pww-pewiph" };
static const stwuct ccu_mux_vaw_pwediv ahb1_pwedivs[] = {
	{ .index = 3, .shift = 6, .width = 2 },
};
static stwuct ccu_div ahb1_cwk = {
	.div		= _SUNXI_CCU_DIV_FWAGS(4, 2, CWK_DIVIDEW_POWEW_OF_TWO),

	.mux		= {
		.shift	= 12,
		.width	= 2,

		.vaw_pwedivs	= ahb1_pwedivs,
		.n_vaw_pwedivs	= AWWAY_SIZE(ahb1_pwedivs),
	},

	.common		= {
		.weg		= 0x054,
		.featuwes	= CCU_FEATUWE_VAWIABWE_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("ahb1",
						      ahb1_pawents,
						      &ccu_div_ops,
						      0),
	},
};

static stwuct cwk_div_tabwe apb1_div_tabwe[] = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 4 },
	{ .vaw = 3, .div = 8 },
	{ /* Sentinew */ },
};
static SUNXI_CCU_DIV_TABWE(apb1_cwk, "apb1", "ahb1",
			   0x054, 8, 2, apb1_div_tabwe, 0);

static const chaw * const apb2_pawents[] = { "osc32k", "osc24M",
					     "pww-pewiph" , "pww-pewiph" };
static SUNXI_CCU_MP_WITH_MUX(apb2_cwk, "apb2", apb2_pawents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static SUNXI_CCU_GATE(bus_mipi_dsi_cwk,	"bus-mipi-dsi",	"ahb1",
		      0x060, BIT(1), 0);
static SUNXI_CCU_GATE(bus_ss_cwk,	"bus-ss",	"ahb1",
		      0x060, BIT(5), 0);
static SUNXI_CCU_GATE(bus_dma_cwk,	"bus-dma",	"ahb1",
		      0x060, BIT(6), 0);
static SUNXI_CCU_GATE(bus_mmc0_cwk,	"bus-mmc0",	"ahb1",
		      0x060, BIT(8), 0);
static SUNXI_CCU_GATE(bus_mmc1_cwk,	"bus-mmc1",	"ahb1",
		      0x060, BIT(9), 0);
static SUNXI_CCU_GATE(bus_mmc2_cwk,	"bus-mmc2",	"ahb1",
		      0x060, BIT(10), 0);
static SUNXI_CCU_GATE(bus_nand_cwk,	"bus-nand",	"ahb1",
		      0x060, BIT(13), 0);
static SUNXI_CCU_GATE(bus_dwam_cwk,	"bus-dwam",	"ahb1",
		      0x060, BIT(14), 0);
static SUNXI_CCU_GATE(bus_hstimew_cwk,	"bus-hstimew",	"ahb1",
		      0x060, BIT(19), 0);
static SUNXI_CCU_GATE(bus_spi0_cwk,	"bus-spi0",	"ahb1",
		      0x060, BIT(20), 0);
static SUNXI_CCU_GATE(bus_spi1_cwk,	"bus-spi1",	"ahb1",
		      0x060, BIT(21), 0);
static SUNXI_CCU_GATE(bus_otg_cwk,	"bus-otg",	"ahb1",
		      0x060, BIT(24), 0);
static SUNXI_CCU_GATE(bus_ehci_cwk,	"bus-ehci",	"ahb1",
		      0x060, BIT(26), 0);
static SUNXI_CCU_GATE(bus_ohci_cwk,	"bus-ohci",	"ahb1",
		      0x060, BIT(29), 0);

static SUNXI_CCU_GATE(bus_ve_cwk,	"bus-ve",	"ahb1",
		      0x064, BIT(0), 0);
static SUNXI_CCU_GATE(bus_wcd_cwk,	"bus-wcd",	"ahb1",
		      0x064, BIT(4), 0);
static SUNXI_CCU_GATE(bus_csi_cwk,	"bus-csi",	"ahb1",
		      0x064, BIT(8), 0);
static SUNXI_CCU_GATE(bus_de_be_cwk,	"bus-de-be",	"ahb1",
		      0x064, BIT(12), 0);
static SUNXI_CCU_GATE(bus_de_fe_cwk,	"bus-de-fe",	"ahb1",
		      0x064, BIT(14), 0);
static SUNXI_CCU_GATE(bus_gpu_cwk,	"bus-gpu",	"ahb1",
		      0x064, BIT(20), 0);
static SUNXI_CCU_GATE(bus_msgbox_cwk,	"bus-msgbox",	"ahb1",
		      0x064, BIT(21), 0);
static SUNXI_CCU_GATE(bus_spinwock_cwk,	"bus-spinwock",	"ahb1",
		      0x064, BIT(22), 0);
static SUNXI_CCU_GATE(bus_dwc_cwk,	"bus-dwc",	"ahb1",
		      0x064, BIT(25), 0);
static SUNXI_CCU_GATE(bus_sat_cwk,	"bus-sat",	"ahb1",
		      0x064, BIT(26), 0);

static SUNXI_CCU_GATE(bus_codec_cwk,	"bus-codec",	"apb1",
		      0x068, BIT(0), 0);
static SUNXI_CCU_GATE(bus_pio_cwk,	"bus-pio",	"apb1",
		      0x068, BIT(5), 0);
static SUNXI_CCU_GATE(bus_i2s0_cwk,	"bus-i2s0",	"apb1",
		      0x068, BIT(12), 0);
static SUNXI_CCU_GATE(bus_i2s1_cwk,	"bus-i2s1",	"apb1",
		      0x068, BIT(13), 0);

static SUNXI_CCU_GATE(bus_i2c0_cwk,	"bus-i2c0",	"apb2",
		      0x06c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2c1_cwk,	"bus-i2c1",	"apb2",
		      0x06c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_i2c2_cwk,	"bus-i2c2",	"apb2",
		      0x06c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_uawt0_cwk,	"bus-uawt0",	"apb2",
		      0x06c, BIT(16), 0);
static SUNXI_CCU_GATE(bus_uawt1_cwk,	"bus-uawt1",	"apb2",
		      0x06c, BIT(17), 0);
static SUNXI_CCU_GATE(bus_uawt2_cwk,	"bus-uawt2",	"apb2",
		      0x06c, BIT(18), 0);
static SUNXI_CCU_GATE(bus_uawt3_cwk,	"bus-uawt3",	"apb2",
		      0x06c, BIT(19), 0);
static SUNXI_CCU_GATE(bus_uawt4_cwk,	"bus-uawt4",	"apb2",
		      0x06c, BIT(20), 0);

static const chaw * const mod0_defauwt_pawents[] = { "osc24M", "pww-pewiph" };
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

static SUNXI_CCU_PHASE(mmc0_sampwe_cwk, "mmc0_sampwe", "mmc0",
		       0x088, 20, 3, 0);
static SUNXI_CCU_PHASE(mmc0_output_cwk, "mmc0_output", "mmc0",
		       0x088, 8, 3, 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_cwk, "mmc1", mod0_defauwt_pawents, 0x08c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_PHASE(mmc1_sampwe_cwk, "mmc1_sampwe", "mmc1",
		       0x08c, 20, 3, 0);
static SUNXI_CCU_PHASE(mmc1_output_cwk, "mmc1_output", "mmc1",
		       0x08c, 8, 3, 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc2_cwk, "mmc2", mod0_defauwt_pawents, 0x090,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_PHASE(mmc2_sampwe_cwk, "mmc2_sampwe", "mmc2",
		       0x090, 20, 3, 0);
static SUNXI_CCU_PHASE(mmc2_output_cwk, "mmc2_output", "mmc2",
		       0x090, 8, 3, 0);

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

static const chaw * const i2s_pawents[] = { "pww-audio-8x", "pww-audio-4x",
					    "pww-audio-2x", "pww-audio" };
static SUNXI_CCU_MUX_WITH_GATE(i2s0_cwk, "i2s0", i2s_pawents,
			       0x0b0, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_MUX_WITH_GATE(i2s1_cwk, "i2s1", i2s_pawents,
			       0x0b4, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

/* TODO: the pawent fow most of the USB cwocks is not known */
static SUNXI_CCU_GATE(usb_phy0_cwk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(8), 0);
static SUNXI_CCU_GATE(usb_phy1_cwk,	"usb-phy1",	"osc24M",
		      0x0cc, BIT(9), 0);
static SUNXI_CCU_GATE(usb_hsic_cwk,	"usb-hsic",	"pww-hsic",
		      0x0cc, BIT(10), 0);
static SUNXI_CCU_GATE(usb_hsic_12M_cwk,	"usb-hsic-12M",	"osc24M",
		      0x0cc, BIT(11), 0);
static SUNXI_CCU_GATE(usb_ohci_cwk,	"usb-ohci",	"osc24M",
		      0x0cc, BIT(16), 0);

static SUNXI_CCU_M(dwam_cwk, "dwam", "pww-ddw",
		   0x0f4, 0, 4, CWK_IS_CWITICAW);

static const chaw * const pww_ddw_pawents[] = { "pww-ddw0", "pww-ddw1" };
static SUNXI_CCU_MUX(pww_ddw_cwk, "pww-ddw", pww_ddw_pawents,
		     0x0f8, 16, 1, 0);

static SUNXI_CCU_GATE(dwam_ve_cwk,	"dwam-ve",	"dwam",
		      0x100, BIT(0), 0);
static SUNXI_CCU_GATE(dwam_csi_cwk,	"dwam-csi",	"dwam",
		      0x100, BIT(1), 0);
static SUNXI_CCU_GATE(dwam_dwc_cwk,	"dwam-dwc",	"dwam",
		      0x100, BIT(16), 0);
static SUNXI_CCU_GATE(dwam_de_fe_cwk,	"dwam-de-fe",	"dwam",
		      0x100, BIT(24), 0);
static SUNXI_CCU_GATE(dwam_de_be_cwk,	"dwam-de-be",	"dwam",
		      0x100, BIT(26), 0);

static const chaw * const de_pawents[] = { "pww-video", "pww-pewiph-2x",
					   "pww-gpu", "pww-de" };
static const u8 de_tabwe[] = { 0, 2, 3, 5 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(de_be_cwk, "de-be",
				       de_pawents, de_tabwe,
				       0x104, 0, 4, 24, 3, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(de_fe_cwk, "de-fe",
				       de_pawents, de_tabwe,
				       0x10c, 0, 4, 24, 3, BIT(31), 0);

static const chaw * const wcd_ch0_pawents[] = { "pww-video", "pww-video-2x",
						"pww-mipi" };
static const u8 wcd_ch0_tabwe[] = { 0, 2, 4 };
static SUNXI_CCU_MUX_TABWE_WITH_GATE(wcd_ch0_cwk, "wcd-ch0",
				     wcd_ch0_pawents, wcd_ch0_tabwe,
				     0x118, 24, 3, BIT(31),
				     CWK_SET_WATE_PAWENT);

static const chaw * const wcd_ch1_pawents[] = { "pww-video", "pww-video-2x" };
static const u8 wcd_ch1_tabwe[] = { 0, 2 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(wcd_ch1_cwk, "wcd-ch1",
				       wcd_ch1_pawents, wcd_ch1_tabwe,
				       0x12c, 0, 4, 24, 2, BIT(31), 0);

static const chaw * const csi_scwk_pawents[] = { "pww-video", "pww-de",
						 "pww-mipi", "pww-ve" };
static const u8 csi_scwk_tabwe[] = { 0, 3, 4, 5 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi_scwk_cwk, "csi-scwk",
				       csi_scwk_pawents, csi_scwk_tabwe,
				       0x134, 16, 4, 24, 3, BIT(31), 0);

static const chaw * const csi_mcwk_pawents[] = { "pww-video", "pww-de",
						 "osc24M" };
static const u8 csi_mcwk_tabwe[] = { 0, 3, 5 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi_mcwk_cwk, "csi-mcwk",
				       csi_mcwk_pawents, csi_mcwk_tabwe,
				       0x134, 0, 5, 8, 3, BIT(15), 0);

static SUNXI_CCU_M_WITH_GATE(ve_cwk, "ve", "pww-ve",
			     0x13c, 16, 3, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(ac_dig_cwk,	"ac-dig",	"pww-audio",
		      0x140, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_GATE(ac_dig_4x_cwk,	"ac-dig-4x",	"pww-audio-4x",
		      0x140, BIT(30), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_GATE(avs_cwk,		"avs",		"osc24M",
		      0x144, BIT(31), 0);

static const chaw * const mbus_pawents[] = { "osc24M", "pww-pewiph-2x",
					     "pww-ddw0", "pww-ddw1" };
static SUNXI_CCU_M_WITH_MUX_GATE(mbus_cwk, "mbus", mbus_pawents,
				 0x15c, 0, 3, 24, 2, BIT(31), CWK_IS_CWITICAW);

static const chaw * const dsi_scwk_pawents[] = { "pww-video", "pww-video-2x" };
static const u8 dsi_scwk_tabwe[] = { 0, 2 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(dsi_scwk_cwk, "dsi-scwk",
				       dsi_scwk_pawents, dsi_scwk_tabwe,
				       0x168, 16, 4, 24, 2, BIT(31), 0);

static const chaw * const dsi_dphy_pawents[] = { "pww-video", "pww-pewiph" };
static const u8 dsi_dphy_tabwe[] = { 0, 2 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(dsi_dphy_cwk, "dsi-dphy",
				       dsi_dphy_pawents, dsi_dphy_tabwe,
				       0x168, 0, 4, 8, 2, BIT(15), 0);

static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(dwc_cwk, "dwc",
				       de_pawents, de_tabwe,
				       0x180, 0, 4, 24, 3, BIT(31), 0);

static SUNXI_CCU_M_WITH_GATE(gpu_cwk, "gpu", "pww-gpu",
			     0x1a0, 0, 3, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw * const ats_pawents[] = { "osc24M", "pww-pewiph" };
static SUNXI_CCU_M_WITH_MUX_GATE(ats_cwk, "ats", ats_pawents,
				 0x1b0, 0, 3, 24, 2, BIT(31), 0);

static stwuct ccu_common *sun8i_a33_ccu_cwks[] = {
	&pww_cpux_cwk.common,
	&pww_audio_base_cwk.common,
	&pww_video_cwk.common,
	&pww_ve_cwk.common,
	&pww_ddw0_cwk.common,
	&pww_pewiph_cwk.common,
	&pww_gpu_cwk.common,
	&pww_mipi_cwk.common,
	&pww_hsic_cwk.common,
	&pww_de_cwk.common,
	&pww_ddw1_cwk.common,
	&pww_ddw_cwk.common,
	&cpux_cwk.common,
	&axi_cwk.common,
	&ahb1_cwk.common,
	&apb1_cwk.common,
	&apb2_cwk.common,
	&bus_mipi_dsi_cwk.common,
	&bus_ss_cwk.common,
	&bus_dma_cwk.common,
	&bus_mmc0_cwk.common,
	&bus_mmc1_cwk.common,
	&bus_mmc2_cwk.common,
	&bus_nand_cwk.common,
	&bus_dwam_cwk.common,
	&bus_hstimew_cwk.common,
	&bus_spi0_cwk.common,
	&bus_spi1_cwk.common,
	&bus_otg_cwk.common,
	&bus_ehci_cwk.common,
	&bus_ohci_cwk.common,
	&bus_ve_cwk.common,
	&bus_wcd_cwk.common,
	&bus_csi_cwk.common,
	&bus_de_fe_cwk.common,
	&bus_de_be_cwk.common,
	&bus_gpu_cwk.common,
	&bus_msgbox_cwk.common,
	&bus_spinwock_cwk.common,
	&bus_dwc_cwk.common,
	&bus_sat_cwk.common,
	&bus_codec_cwk.common,
	&bus_pio_cwk.common,
	&bus_i2s0_cwk.common,
	&bus_i2s1_cwk.common,
	&bus_i2c0_cwk.common,
	&bus_i2c1_cwk.common,
	&bus_i2c2_cwk.common,
	&bus_uawt0_cwk.common,
	&bus_uawt1_cwk.common,
	&bus_uawt2_cwk.common,
	&bus_uawt3_cwk.common,
	&bus_uawt4_cwk.common,
	&nand_cwk.common,
	&mmc0_cwk.common,
	&mmc0_sampwe_cwk.common,
	&mmc0_output_cwk.common,
	&mmc1_cwk.common,
	&mmc1_sampwe_cwk.common,
	&mmc1_output_cwk.common,
	&mmc2_cwk.common,
	&mmc2_sampwe_cwk.common,
	&mmc2_output_cwk.common,
	&ss_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&i2s0_cwk.common,
	&i2s1_cwk.common,
	&usb_phy0_cwk.common,
	&usb_phy1_cwk.common,
	&usb_hsic_cwk.common,
	&usb_hsic_12M_cwk.common,
	&usb_ohci_cwk.common,
	&dwam_cwk.common,
	&dwam_ve_cwk.common,
	&dwam_csi_cwk.common,
	&dwam_dwc_cwk.common,
	&dwam_de_fe_cwk.common,
	&dwam_de_be_cwk.common,
	&de_be_cwk.common,
	&de_fe_cwk.common,
	&wcd_ch0_cwk.common,
	&wcd_ch1_cwk.common,
	&csi_scwk_cwk.common,
	&csi_mcwk_cwk.common,
	&ve_cwk.common,
	&ac_dig_cwk.common,
	&ac_dig_4x_cwk.common,
	&avs_cwk.common,
	&mbus_cwk.common,
	&dsi_scwk_cwk.common,
	&dsi_dphy_cwk.common,
	&dwc_cwk.common,
	&gpu_cwk.common,
	&ats_cwk.common,
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
static CWK_FIXED_FACTOW_HW(pww_pewiph_2x_cwk, "pww-pewiph-2x",
			   &pww_pewiph_cwk.common.hw,
			   1, 2, 0);
static CWK_FIXED_FACTOW_HW(pww_video_2x_cwk, "pww-video-2x",
			   &pww_video_cwk.common.hw,
			   1, 2, 0);

static stwuct cwk_hw_oneceww_data sun8i_a33_hw_cwks = {
	.hws	= {
		[CWK_PWW_CPUX]		= &pww_cpux_cwk.common.hw,
		[CWK_PWW_AUDIO_BASE]	= &pww_audio_base_cwk.common.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.hw,
		[CWK_PWW_AUDIO_2X]	= &pww_audio_2x_cwk.hw,
		[CWK_PWW_AUDIO_4X]	= &pww_audio_4x_cwk.hw,
		[CWK_PWW_AUDIO_8X]	= &pww_audio_8x_cwk.hw,
		[CWK_PWW_VIDEO]		= &pww_video_cwk.common.hw,
		[CWK_PWW_VIDEO_2X]	= &pww_video_2x_cwk.hw,
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DDW0]		= &pww_ddw0_cwk.common.hw,
		[CWK_PWW_PEWIPH]	= &pww_pewiph_cwk.common.hw,
		[CWK_PWW_PEWIPH_2X]	= &pww_pewiph_2x_cwk.hw,
		[CWK_PWW_GPU]		= &pww_gpu_cwk.common.hw,
		[CWK_PWW_MIPI]		= &pww_mipi_cwk.common.hw,
		[CWK_PWW_HSIC]		= &pww_hsic_cwk.common.hw,
		[CWK_PWW_DE]		= &pww_de_cwk.common.hw,
		[CWK_PWW_DDW1]		= &pww_ddw1_cwk.common.hw,
		[CWK_PWW_DDW]		= &pww_ddw_cwk.common.hw,
		[CWK_CPUX]		= &cpux_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AHB1]		= &ahb1_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_APB2]		= &apb2_cwk.common.hw,
		[CWK_BUS_MIPI_DSI]	= &bus_mipi_dsi_cwk.common.hw,
		[CWK_BUS_SS]		= &bus_ss_cwk.common.hw,
		[CWK_BUS_DMA]		= &bus_dma_cwk.common.hw,
		[CWK_BUS_MMC0]		= &bus_mmc0_cwk.common.hw,
		[CWK_BUS_MMC1]		= &bus_mmc1_cwk.common.hw,
		[CWK_BUS_MMC2]		= &bus_mmc2_cwk.common.hw,
		[CWK_BUS_NAND]		= &bus_nand_cwk.common.hw,
		[CWK_BUS_DWAM]		= &bus_dwam_cwk.common.hw,
		[CWK_BUS_HSTIMEW]	= &bus_hstimew_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_SPI1]		= &bus_spi1_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_BUS_EHCI]		= &bus_ehci_cwk.common.hw,
		[CWK_BUS_OHCI]		= &bus_ohci_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_BUS_WCD]		= &bus_wcd_cwk.common.hw,
		[CWK_BUS_CSI]		= &bus_csi_cwk.common.hw,
		[CWK_BUS_DE_BE]		= &bus_de_be_cwk.common.hw,
		[CWK_BUS_DE_FE]		= &bus_de_fe_cwk.common.hw,
		[CWK_BUS_GPU]		= &bus_gpu_cwk.common.hw,
		[CWK_BUS_MSGBOX]	= &bus_msgbox_cwk.common.hw,
		[CWK_BUS_SPINWOCK]	= &bus_spinwock_cwk.common.hw,
		[CWK_BUS_DWC]		= &bus_dwc_cwk.common.hw,
		[CWK_BUS_SAT]		= &bus_sat_cwk.common.hw,
		[CWK_BUS_CODEC]		= &bus_codec_cwk.common.hw,
		[CWK_BUS_PIO]		= &bus_pio_cwk.common.hw,
		[CWK_BUS_I2S0]		= &bus_i2s0_cwk.common.hw,
		[CWK_BUS_I2S1]		= &bus_i2s1_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_I2C2]		= &bus_i2c2_cwk.common.hw,
		[CWK_BUS_UAWT0]		= &bus_uawt0_cwk.common.hw,
		[CWK_BUS_UAWT1]		= &bus_uawt1_cwk.common.hw,
		[CWK_BUS_UAWT2]		= &bus_uawt2_cwk.common.hw,
		[CWK_BUS_UAWT3]		= &bus_uawt3_cwk.common.hw,
		[CWK_BUS_UAWT4]		= &bus_uawt4_cwk.common.hw,
		[CWK_NAND]		= &nand_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC0_SAMPWE]	= &mmc0_sampwe_cwk.common.hw,
		[CWK_MMC0_OUTPUT]	= &mmc0_output_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC1_SAMPWE]	= &mmc1_sampwe_cwk.common.hw,
		[CWK_MMC1_OUTPUT]	= &mmc1_output_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_MMC2_SAMPWE]	= &mmc2_sampwe_cwk.common.hw,
		[CWK_MMC2_OUTPUT]	= &mmc2_output_cwk.common.hw,
		[CWK_SS]		= &ss_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_I2S0]		= &i2s0_cwk.common.hw,
		[CWK_I2S1]		= &i2s1_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_PHY1]		= &usb_phy1_cwk.common.hw,
		[CWK_USB_HSIC]		= &usb_hsic_cwk.common.hw,
		[CWK_USB_HSIC_12M]	= &usb_hsic_12M_cwk.common.hw,
		[CWK_USB_OHCI]		= &usb_ohci_cwk.common.hw,
		[CWK_DWAM]		= &dwam_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI]		= &dwam_csi_cwk.common.hw,
		[CWK_DWAM_DWC]		= &dwam_dwc_cwk.common.hw,
		[CWK_DWAM_DE_FE]	= &dwam_de_fe_cwk.common.hw,
		[CWK_DWAM_DE_BE]	= &dwam_de_be_cwk.common.hw,
		[CWK_DE_BE]		= &de_be_cwk.common.hw,
		[CWK_DE_FE]		= &de_fe_cwk.common.hw,
		[CWK_WCD_CH0]		= &wcd_ch0_cwk.common.hw,
		[CWK_WCD_CH1]		= &wcd_ch1_cwk.common.hw,
		[CWK_CSI_SCWK]		= &csi_scwk_cwk.common.hw,
		[CWK_CSI_MCWK]		= &csi_mcwk_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_AC_DIG]		= &ac_dig_cwk.common.hw,
		[CWK_AC_DIG_4X]		= &ac_dig_4x_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_DSI_SCWK]		= &dsi_scwk_cwk.common.hw,
		[CWK_DSI_DPHY]		= &dsi_dphy_cwk.common.hw,
		[CWK_DWC]		= &dwc_cwk.common.hw,
		[CWK_GPU]		= &gpu_cwk.common.hw,
		[CWK_ATS]		= &ats_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct ccu_weset_map sun8i_a33_ccu_wesets[] = {
	[WST_USB_PHY0]		=  { 0x0cc, BIT(0) },
	[WST_USB_PHY1]		=  { 0x0cc, BIT(1) },
	[WST_USB_HSIC]		=  { 0x0cc, BIT(2) },

	[WST_MBUS]		=  { 0x0fc, BIT(31) },

	[WST_BUS_MIPI_DSI]	=  { 0x2c0, BIT(1) },
	[WST_BUS_SS]		=  { 0x2c0, BIT(5) },
	[WST_BUS_DMA]		=  { 0x2c0, BIT(6) },
	[WST_BUS_MMC0]		=  { 0x2c0, BIT(8) },
	[WST_BUS_MMC1]		=  { 0x2c0, BIT(9) },
	[WST_BUS_MMC2]		=  { 0x2c0, BIT(10) },
	[WST_BUS_NAND]		=  { 0x2c0, BIT(13) },
	[WST_BUS_DWAM]		=  { 0x2c0, BIT(14) },
	[WST_BUS_HSTIMEW]	=  { 0x2c0, BIT(19) },
	[WST_BUS_SPI0]		=  { 0x2c0, BIT(20) },
	[WST_BUS_SPI1]		=  { 0x2c0, BIT(21) },
	[WST_BUS_OTG]		=  { 0x2c0, BIT(24) },
	[WST_BUS_EHCI]		=  { 0x2c0, BIT(26) },
	[WST_BUS_OHCI]		=  { 0x2c0, BIT(29) },

	[WST_BUS_VE]		=  { 0x2c4, BIT(0) },
	[WST_BUS_WCD]		=  { 0x2c4, BIT(4) },
	[WST_BUS_CSI]		=  { 0x2c4, BIT(8) },
	[WST_BUS_DE_BE]		=  { 0x2c4, BIT(12) },
	[WST_BUS_DE_FE]		=  { 0x2c4, BIT(14) },
	[WST_BUS_GPU]		=  { 0x2c4, BIT(20) },
	[WST_BUS_MSGBOX]	=  { 0x2c4, BIT(21) },
	[WST_BUS_SPINWOCK]	=  { 0x2c4, BIT(22) },
	[WST_BUS_DWC]		=  { 0x2c4, BIT(25) },
	[WST_BUS_SAT]		=  { 0x2c4, BIT(26) },

	[WST_BUS_WVDS]		=  { 0x2c8, BIT(0) },

	[WST_BUS_CODEC]		=  { 0x2d0, BIT(0) },
	[WST_BUS_I2S0]		=  { 0x2d0, BIT(12) },
	[WST_BUS_I2S1]		=  { 0x2d0, BIT(13) },

	[WST_BUS_I2C0]		=  { 0x2d8, BIT(0) },
	[WST_BUS_I2C1]		=  { 0x2d8, BIT(1) },
	[WST_BUS_I2C2]		=  { 0x2d8, BIT(2) },
	[WST_BUS_UAWT0]		=  { 0x2d8, BIT(16) },
	[WST_BUS_UAWT1]		=  { 0x2d8, BIT(17) },
	[WST_BUS_UAWT2]		=  { 0x2d8, BIT(18) },
	[WST_BUS_UAWT3]		=  { 0x2d8, BIT(19) },
	[WST_BUS_UAWT4]		=  { 0x2d8, BIT(20) },
};

static const stwuct sunxi_ccu_desc sun8i_a33_ccu_desc = {
	.ccu_cwks	= sun8i_a33_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun8i_a33_ccu_cwks),

	.hw_cwks	= &sun8i_a33_hw_cwks,

	.wesets		= sun8i_a33_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun8i_a33_ccu_wesets),
};

static stwuct ccu_pww_nb sun8i_a33_pww_cpu_nb = {
	.common	= &pww_cpux_cwk.common,
	/* copy fwom pww_cpux_cwk */
	.enabwe	= BIT(31),
	.wock	= BIT(28),
};

static stwuct ccu_mux_nb sun8i_a33_cpu_nb = {
	.common		= &cpux_cwk.common,
	.cm		= &cpux_cwk.mux,
	.deway_us	= 1, /* > 8 cwock cycwes at 24 MHz */
	.bypass_index	= 1, /* index of 24 MHz osciwwatow */
};

static int sun8i_a33_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *weg;
	int wet;
	u32 vaw;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	/* Fowce the PWW-Audio-1x dividew to 1 */
	vaw = weadw(weg + SUN8I_A33_PWW_AUDIO_WEG);
	vaw &= ~GENMASK(19, 16);
	wwitew(vaw | (0 << 16), weg + SUN8I_A33_PWW_AUDIO_WEG);

	/* Fowce PWW-MIPI to MIPI mode */
	vaw = weadw(weg + SUN8I_A33_PWW_MIPI_WEG);
	vaw &= ~BIT(16);
	wwitew(vaw, weg + SUN8I_A33_PWW_MIPI_WEG);

	wet = devm_sunxi_ccu_pwobe(&pdev->dev, weg, &sun8i_a33_ccu_desc);
	if (wet)
		wetuwn wet;

	/* Gate then ungate PWW CPU aftew any wate changes */
	ccu_pww_notifiew_wegistew(&sun8i_a33_pww_cpu_nb);

	/* Wepawent CPU duwing PWW CPU wate changes */
	ccu_mux_notifiew_wegistew(pww_cpux_cwk.common.hw.cwk,
				  &sun8i_a33_cpu_nb);

	wetuwn 0;
}

static const stwuct of_device_id sun8i_a33_ccu_ids[] = {
	{ .compatibwe = "awwwinnew,sun8i-a33-ccu" },
	{ }
};

static stwuct pwatfowm_dwivew sun8i_a33_ccu_dwivew = {
	.pwobe	= sun8i_a33_ccu_pwobe,
	.dwivew	= {
		.name			= "sun8i-a33-ccu",
		.suppwess_bind_attws	= twue,
		.of_match_tabwe		= sun8i_a33_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun8i_a33_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
