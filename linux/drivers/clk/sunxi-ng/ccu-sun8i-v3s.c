// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Icenowy Zheng <icenowy@aosc.xyz>
 *
 * Based on ccu-sun8i-h3.c, which is:
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
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

#incwude "ccu-sun8i-v3s.h"

static SUNXI_CCU_NKMP_WITH_GATE_WOCK(pww_cpu_cwk, "pww-cpu",
				     "osc24M", 0x000,
				     8, 5,	/* N */
				     4, 2,	/* K */
				     0, 2,	/* M */
				     16, 2,	/* P */
				     BIT(31),	/* gate */
				     BIT(28),	/* wock */
				     0);

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
#define SUN8I_V3S_PWW_AUDIO_WEG	0x008

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
					"osc24M", 0x0010,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* fwac enabwe */
					BIT(25),	/* fwac sewect */
					270000000,	/* fwac wate 0 */
					297000000,	/* fwac wate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* wock */
					0);

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK(pww_ve_cwk, "pww-ve",
					"osc24M", 0x0018,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* fwac enabwe */
					BIT(25),	/* fwac sewect */
					270000000,	/* fwac wate 0 */
					297000000,	/* fwac wate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* wock */
					0);

static SUNXI_CCU_NKM_WITH_GATE_WOCK(pww_ddw0_cwk, "pww-ddw0",
				    "osc24M", 0x020,
				    8, 5,	/* N */
				    4, 2,	/* K */
				    0, 2,	/* M */
				    BIT(31),	/* gate */
				    BIT(28),	/* wock */
				    0);

static SUNXI_CCU_NK_WITH_GATE_WOCK_POSTDIV(pww_pewiph0_cwk, "pww-pewiph0",
					   "osc24M", 0x028,
					   8, 5,	/* N */
					   4, 2,	/* K */
					   BIT(31),	/* gate */
					   BIT(28),	/* wock */
					   2,		/* post-div */
					   0);

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK(pww_isp_cwk, "pww-isp",
					"osc24M", 0x002c,
					8, 7,		/* N */
					0, 4,		/* M */
					BIT(24),	/* fwac enabwe */
					BIT(25),	/* fwac sewect */
					270000000,	/* fwac wate 0 */
					297000000,	/* fwac wate 1 */
					BIT(31),	/* gate */
					BIT(28),	/* wock */
					0);

static SUNXI_CCU_NK_WITH_GATE_WOCK_POSTDIV(pww_pewiph1_cwk, "pww-pewiph1",
					   "osc24M", 0x044,
					   8, 5,	/* N */
					   4, 2,	/* K */
					   BIT(31),	/* gate */
					   BIT(28),	/* wock */
					   2,		/* post-div */
					   0);

static SUNXI_CCU_NM_WITH_GATE_WOCK(pww_ddw1_cwk, "pww-ddw1",
				   "osc24M", 0x04c,
				   8, 7,	/* N */
				   0, 2,	/* M */
				   BIT(31),	/* gate */
				   BIT(28),	/* wock */
				   0);

static const chaw * const cpu_pawents[] = { "osc32k", "osc24M",
					     "pww-cpu", "pww-cpu" };
static SUNXI_CCU_MUX(cpu_cwk, "cpu", cpu_pawents,
		     0x050, 16, 2, CWK_IS_CWITICAW);

static SUNXI_CCU_M(axi_cwk, "axi", "cpu", 0x050, 0, 2, 0);

static const chaw * const ahb1_pawents[] = { "osc32k", "osc24M",
					     "axi", "pww-pewiph0" };
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
					     "pww-pewiph0", "pww-pewiph0" };
static SUNXI_CCU_MP_WITH_MUX(apb2_cwk, "apb2", apb2_pawents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static const chaw * const ahb2_pawents[] = { "ahb1", "pww-pewiph0" };
static const stwuct ccu_mux_fixed_pwediv ahb2_fixed_pwedivs[] = {
	{ .index = 1, .div = 2 },
};
static stwuct ccu_mux ahb2_cwk = {
	.mux		= {
		.shift	= 0,
		.width	= 1,
		.fixed_pwedivs	= ahb2_fixed_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(ahb2_fixed_pwedivs),
	},

	.common		= {
		.weg		= 0x05c,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("ahb2",
						      ahb2_pawents,
						      &ccu_mux_ops,
						      0),
	},
};

static SUNXI_CCU_GATE(bus_ce_cwk,	"bus-ce",	"ahb1",
		      0x060, BIT(5), 0);
static SUNXI_CCU_GATE(bus_dma_cwk,	"bus-dma",	"ahb1",
		      0x060, BIT(6), 0);
static SUNXI_CCU_GATE(bus_mmc0_cwk,	"bus-mmc0",	"ahb1",
		      0x060, BIT(8), 0);
static SUNXI_CCU_GATE(bus_mmc1_cwk,	"bus-mmc1",	"ahb1",
		      0x060, BIT(9), 0);
static SUNXI_CCU_GATE(bus_mmc2_cwk,	"bus-mmc2",	"ahb1",
		      0x060, BIT(10), 0);
static SUNXI_CCU_GATE(bus_dwam_cwk,	"bus-dwam",	"ahb1",
		      0x060, BIT(14), 0);
static SUNXI_CCU_GATE(bus_emac_cwk,	"bus-emac",	"ahb2",
		      0x060, BIT(17), 0);
static SUNXI_CCU_GATE(bus_hstimew_cwk,	"bus-hstimew",	"ahb1",
		      0x060, BIT(19), 0);
static SUNXI_CCU_GATE(bus_spi0_cwk,	"bus-spi0",	"ahb1",
		      0x060, BIT(20), 0);
static SUNXI_CCU_GATE(bus_otg_cwk,	"bus-otg",	"ahb1",
		      0x060, BIT(24), 0);
static SUNXI_CCU_GATE(bus_ehci0_cwk,	"bus-ehci0",	"ahb1",
		      0x060, BIT(26), 0);
static SUNXI_CCU_GATE(bus_ohci0_cwk,	"bus-ohci0",	"ahb1",
		      0x060, BIT(29), 0);

static SUNXI_CCU_GATE(bus_ve_cwk,	"bus-ve",	"ahb1",
		      0x064, BIT(0), 0);
static SUNXI_CCU_GATE(bus_tcon0_cwk,	"bus-tcon0",	"ahb1",
		      0x064, BIT(4), 0);
static SUNXI_CCU_GATE(bus_csi_cwk,	"bus-csi",	"ahb1",
		      0x064, BIT(8), 0);
static SUNXI_CCU_GATE(bus_de_cwk,	"bus-de",	"ahb1",
		      0x064, BIT(12), 0);

static SUNXI_CCU_GATE(bus_codec_cwk,	"bus-codec",	"apb1",
		      0x068, BIT(0), 0);
static SUNXI_CCU_GATE(bus_pio_cwk,	"bus-pio",	"apb1",
		      0x068, BIT(5), 0);
static SUNXI_CCU_GATE(bus_i2s0_cwk,	"bus-i2s0",	"apb1",
		      0x068, BIT(12), 0);

static SUNXI_CCU_GATE(bus_i2c0_cwk,	"bus-i2c0",	"apb2",
		      0x06c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2c1_cwk,	"bus-i2c1",	"apb2",
		      0x06c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_uawt0_cwk,	"bus-uawt0",	"apb2",
		      0x06c, BIT(16), 0);
static SUNXI_CCU_GATE(bus_uawt1_cwk,	"bus-uawt1",	"apb2",
		      0x06c, BIT(17), 0);
static SUNXI_CCU_GATE(bus_uawt2_cwk,	"bus-uawt2",	"apb2",
		      0x06c, BIT(18), 0);

static SUNXI_CCU_GATE(bus_ephy_cwk,	"bus-ephy",	"ahb1",
		      0x070, BIT(0), 0);
static SUNXI_CCU_GATE(bus_dbg_cwk,	"bus-dbg",	"ahb1",
		      0x070, BIT(7), 0);

static const chaw * const mod0_defauwt_pawents[] = { "osc24M", "pww-pewiph0",
						     "pww-pewiph1" };
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

static const chaw * const ce_pawents[] = { "osc24M", "pww-pewiph0", };

static SUNXI_CCU_MP_WITH_MUX_GATE(ce_cwk, "ce", ce_pawents, 0x09c,
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

static const chaw * const i2s_pawents[] = { "pww-audio-8x", "pww-audio-4x",
					    "pww-audio-2x", "pww-audio" };
static SUNXI_CCU_MUX_WITH_GATE(i2s0_cwk, "i2s0", i2s_pawents,
			       0x0b0, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(usb_phy0_cwk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(8), 0);
static SUNXI_CCU_GATE(usb_ohci0_cwk,	"usb-ohci0",	"osc24M",
		      0x0cc, BIT(16), 0);

static const chaw * const dwam_pawents[] = { "pww-ddw0", "pww-ddw1",
					     "pww-pewiph0-2x" };
static SUNXI_CCU_M_WITH_MUX(dwam_cwk, "dwam", dwam_pawents,
			    0x0f4, 0, 4, 20, 2, CWK_IS_CWITICAW);

static SUNXI_CCU_GATE(dwam_ve_cwk,	"dwam-ve",	"dwam",
		      0x100, BIT(0), 0);
static SUNXI_CCU_GATE(dwam_csi_cwk,	"dwam-csi",	"dwam",
		      0x100, BIT(1), 0);
static SUNXI_CCU_GATE(dwam_ehci_cwk,	"dwam-ehci",	"dwam",
		      0x100, BIT(17), 0);
static SUNXI_CCU_GATE(dwam_ohci_cwk,	"dwam-ohci",	"dwam",
		      0x100, BIT(18), 0);

static const chaw * const de_pawents[] = { "pww-video", "pww-pewiph0" };
static SUNXI_CCU_M_WITH_MUX_GATE(de_cwk, "de", de_pawents,
				 0x104, 0, 4, 24, 2, BIT(31),
				 CWK_SET_WATE_PAWENT);

static const chaw * const tcon_pawents[] = { "pww-video" };
static SUNXI_CCU_M_WITH_MUX_GATE(tcon_cwk, "tcon", tcon_pawents,
				 0x118, 0, 4, 24, 3, BIT(31), 0);

static SUNXI_CCU_GATE(csi_misc_cwk,	"csi-misc",	"osc24M",
		      0x130, BIT(31), 0);

static const chaw * const csi_mcwk_pawents[] = { "osc24M", "pww-video",
						 "pww-pewiph0", "pww-pewiph1" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi0_mcwk_cwk, "csi0-mcwk", csi_mcwk_pawents,
				 0x130, 0, 5, 8, 3, BIT(15), 0);

static const chaw * const csi1_scwk_pawents[] = { "pww-video", "pww-isp" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi1_scwk_cwk, "csi-scwk", csi1_scwk_pawents,
				 0x134, 16, 4, 24, 3, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(csi1_mcwk_cwk, "csi-mcwk", csi_mcwk_pawents,
				 0x134, 0, 5, 8, 3, BIT(15), 0);

static SUNXI_CCU_M_WITH_GATE(ve_cwk, "ve", "pww-ve",
			     0x13c, 16, 3, BIT(31), 0);

static SUNXI_CCU_GATE(ac_dig_cwk,	"ac-dig",	"pww-audio",
		      0x140, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_GATE(avs_cwk,		"avs",		"osc24M",
		      0x144, BIT(31), 0);

static const chaw * const mbus_pawents[] = { "osc24M", "pww-pewiph0-2x",
					     "pww-ddw" };
static SUNXI_CCU_M_WITH_MUX_GATE(mbus_cwk, "mbus", mbus_pawents,
				 0x15c, 0, 3, 24, 2, BIT(31), CWK_IS_CWITICAW);

static const chaw * const mipi_csi_pawents[] = { "pww-video", "pww-pewiph0",
						 "pww-isp" };
static SUNXI_CCU_M_WITH_MUX_GATE(mipi_csi_cwk, "mipi-csi", mipi_csi_pawents,
			     0x16c, 0, 3, 24, 2, BIT(31), 0);

static stwuct ccu_common *sun8i_v3s_ccu_cwks[] = {
	&pww_cpu_cwk.common,
	&pww_audio_base_cwk.common,
	&pww_video_cwk.common,
	&pww_ve_cwk.common,
	&pww_ddw0_cwk.common,
	&pww_pewiph0_cwk.common,
	&pww_isp_cwk.common,
	&pww_pewiph1_cwk.common,
	&pww_ddw1_cwk.common,
	&cpu_cwk.common,
	&axi_cwk.common,
	&ahb1_cwk.common,
	&apb1_cwk.common,
	&apb2_cwk.common,
	&ahb2_cwk.common,
	&bus_ce_cwk.common,
	&bus_dma_cwk.common,
	&bus_mmc0_cwk.common,
	&bus_mmc1_cwk.common,
	&bus_mmc2_cwk.common,
	&bus_dwam_cwk.common,
	&bus_emac_cwk.common,
	&bus_hstimew_cwk.common,
	&bus_spi0_cwk.common,
	&bus_otg_cwk.common,
	&bus_ehci0_cwk.common,
	&bus_ohci0_cwk.common,
	&bus_ve_cwk.common,
	&bus_tcon0_cwk.common,
	&bus_csi_cwk.common,
	&bus_de_cwk.common,
	&bus_codec_cwk.common,
	&bus_pio_cwk.common,
	&bus_i2s0_cwk.common,
	&bus_i2c0_cwk.common,
	&bus_i2c1_cwk.common,
	&bus_uawt0_cwk.common,
	&bus_uawt1_cwk.common,
	&bus_uawt2_cwk.common,
	&bus_ephy_cwk.common,
	&bus_dbg_cwk.common,
	&mmc0_cwk.common,
	&mmc0_sampwe_cwk.common,
	&mmc0_output_cwk.common,
	&mmc1_cwk.common,
	&mmc1_sampwe_cwk.common,
	&mmc1_output_cwk.common,
	&mmc2_cwk.common,
	&mmc2_sampwe_cwk.common,
	&mmc2_output_cwk.common,
	&ce_cwk.common,
	&spi0_cwk.common,
	&i2s0_cwk.common,
	&usb_phy0_cwk.common,
	&usb_ohci0_cwk.common,
	&dwam_cwk.common,
	&dwam_ve_cwk.common,
	&dwam_csi_cwk.common,
	&dwam_ohci_cwk.common,
	&dwam_ehci_cwk.common,
	&de_cwk.common,
	&tcon_cwk.common,
	&csi_misc_cwk.common,
	&csi0_mcwk_cwk.common,
	&csi1_scwk_cwk.common,
	&csi1_mcwk_cwk.common,
	&ve_cwk.common,
	&ac_dig_cwk.common,
	&avs_cwk.common,
	&mbus_cwk.common,
	&mipi_csi_cwk.common,
};

static const stwuct cwk_hw *cwk_pawent_pww_audio[] = {
	&pww_audio_base_cwk.common.hw
};

/* We hawdcode the dividew to 1 fow SDM suppowt */
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
static CWK_FIXED_FACTOW_HW(pww_pewiph0_2x_cwk, "pww-pewiph0-2x",
			   &pww_pewiph0_cwk.common.hw,
			   1, 2, 0);

static stwuct cwk_hw_oneceww_data sun8i_v3s_hw_cwks = {
	.hws	= {
		[CWK_PWW_CPU]		= &pww_cpu_cwk.common.hw,
		[CWK_PWW_AUDIO_BASE]	= &pww_audio_base_cwk.common.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.hw,
		[CWK_PWW_AUDIO_2X]	= &pww_audio_2x_cwk.hw,
		[CWK_PWW_AUDIO_4X]	= &pww_audio_4x_cwk.hw,
		[CWK_PWW_AUDIO_8X]	= &pww_audio_8x_cwk.hw,
		[CWK_PWW_VIDEO]		= &pww_video_cwk.common.hw,
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DDW0]		= &pww_ddw0_cwk.common.hw,
		[CWK_PWW_PEWIPH0]	= &pww_pewiph0_cwk.common.hw,
		[CWK_PWW_PEWIPH0_2X]	= &pww_pewiph0_2x_cwk.hw,
		[CWK_PWW_ISP]		= &pww_isp_cwk.common.hw,
		[CWK_PWW_PEWIPH1]	= &pww_pewiph1_cwk.common.hw,
		[CWK_PWW_DDW1]		= &pww_ddw1_cwk.common.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AHB1]		= &ahb1_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_APB2]		= &apb2_cwk.common.hw,
		[CWK_AHB2]		= &ahb2_cwk.common.hw,
		[CWK_BUS_CE]		= &bus_ce_cwk.common.hw,
		[CWK_BUS_DMA]		= &bus_dma_cwk.common.hw,
		[CWK_BUS_MMC0]		= &bus_mmc0_cwk.common.hw,
		[CWK_BUS_MMC1]		= &bus_mmc1_cwk.common.hw,
		[CWK_BUS_MMC2]		= &bus_mmc2_cwk.common.hw,
		[CWK_BUS_DWAM]		= &bus_dwam_cwk.common.hw,
		[CWK_BUS_EMAC]		= &bus_emac_cwk.common.hw,
		[CWK_BUS_HSTIMEW]	= &bus_hstimew_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_BUS_EHCI0]		= &bus_ehci0_cwk.common.hw,
		[CWK_BUS_OHCI0]		= &bus_ohci0_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_BUS_TCON0]		= &bus_tcon0_cwk.common.hw,
		[CWK_BUS_CSI]		= &bus_csi_cwk.common.hw,
		[CWK_BUS_DE]		= &bus_de_cwk.common.hw,
		[CWK_BUS_CODEC]		= &bus_codec_cwk.common.hw,
		[CWK_BUS_PIO]		= &bus_pio_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_UAWT0]		= &bus_uawt0_cwk.common.hw,
		[CWK_BUS_UAWT1]		= &bus_uawt1_cwk.common.hw,
		[CWK_BUS_UAWT2]		= &bus_uawt2_cwk.common.hw,
		[CWK_BUS_EPHY]		= &bus_ephy_cwk.common.hw,
		[CWK_BUS_DBG]		= &bus_dbg_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC0_SAMPWE]	= &mmc0_sampwe_cwk.common.hw,
		[CWK_MMC0_OUTPUT]	= &mmc0_output_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC1_SAMPWE]	= &mmc1_sampwe_cwk.common.hw,
		[CWK_MMC1_OUTPUT]	= &mmc1_output_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_MMC2_SAMPWE]	= &mmc2_sampwe_cwk.common.hw,
		[CWK_MMC2_OUTPUT]	= &mmc2_output_cwk.common.hw,
		[CWK_CE]		= &ce_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_DWAM]		= &dwam_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI]		= &dwam_csi_cwk.common.hw,
		[CWK_DWAM_EHCI]		= &dwam_ehci_cwk.common.hw,
		[CWK_DWAM_OHCI]		= &dwam_ohci_cwk.common.hw,
		[CWK_DE]		= &de_cwk.common.hw,
		[CWK_TCON0]		= &tcon_cwk.common.hw,
		[CWK_CSI_MISC]		= &csi_misc_cwk.common.hw,
		[CWK_CSI0_MCWK]		= &csi0_mcwk_cwk.common.hw,
		[CWK_CSI1_SCWK]		= &csi1_scwk_cwk.common.hw,
		[CWK_CSI1_MCWK]		= &csi1_mcwk_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_AC_DIG]		= &ac_dig_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_MIPI_CSI]		= &mipi_csi_cwk.common.hw,
	},
	.num	= CWK_PWW_DDW1 + 1,
};

static stwuct cwk_hw_oneceww_data sun8i_v3_hw_cwks = {
	.hws	= {
		[CWK_PWW_CPU]		= &pww_cpu_cwk.common.hw,
		[CWK_PWW_AUDIO_BASE]	= &pww_audio_base_cwk.common.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.hw,
		[CWK_PWW_AUDIO_2X]	= &pww_audio_2x_cwk.hw,
		[CWK_PWW_AUDIO_4X]	= &pww_audio_4x_cwk.hw,
		[CWK_PWW_AUDIO_8X]	= &pww_audio_8x_cwk.hw,
		[CWK_PWW_VIDEO]		= &pww_video_cwk.common.hw,
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DDW0]		= &pww_ddw0_cwk.common.hw,
		[CWK_PWW_PEWIPH0]	= &pww_pewiph0_cwk.common.hw,
		[CWK_PWW_PEWIPH0_2X]	= &pww_pewiph0_2x_cwk.hw,
		[CWK_PWW_ISP]		= &pww_isp_cwk.common.hw,
		[CWK_PWW_PEWIPH1]	= &pww_pewiph1_cwk.common.hw,
		[CWK_PWW_DDW1]		= &pww_ddw1_cwk.common.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AHB1]		= &ahb1_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_APB2]		= &apb2_cwk.common.hw,
		[CWK_AHB2]		= &ahb2_cwk.common.hw,
		[CWK_BUS_CE]		= &bus_ce_cwk.common.hw,
		[CWK_BUS_DMA]		= &bus_dma_cwk.common.hw,
		[CWK_BUS_MMC0]		= &bus_mmc0_cwk.common.hw,
		[CWK_BUS_MMC1]		= &bus_mmc1_cwk.common.hw,
		[CWK_BUS_MMC2]		= &bus_mmc2_cwk.common.hw,
		[CWK_BUS_DWAM]		= &bus_dwam_cwk.common.hw,
		[CWK_BUS_EMAC]		= &bus_emac_cwk.common.hw,
		[CWK_BUS_HSTIMEW]	= &bus_hstimew_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_BUS_EHCI0]		= &bus_ehci0_cwk.common.hw,
		[CWK_BUS_OHCI0]		= &bus_ohci0_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_BUS_TCON0]		= &bus_tcon0_cwk.common.hw,
		[CWK_BUS_CSI]		= &bus_csi_cwk.common.hw,
		[CWK_BUS_DE]		= &bus_de_cwk.common.hw,
		[CWK_BUS_CODEC]		= &bus_codec_cwk.common.hw,
		[CWK_BUS_PIO]		= &bus_pio_cwk.common.hw,
		[CWK_BUS_I2S0]		= &bus_i2s0_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_UAWT0]		= &bus_uawt0_cwk.common.hw,
		[CWK_BUS_UAWT1]		= &bus_uawt1_cwk.common.hw,
		[CWK_BUS_UAWT2]		= &bus_uawt2_cwk.common.hw,
		[CWK_BUS_EPHY]		= &bus_ephy_cwk.common.hw,
		[CWK_BUS_DBG]		= &bus_dbg_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC0_SAMPWE]	= &mmc0_sampwe_cwk.common.hw,
		[CWK_MMC0_OUTPUT]	= &mmc0_output_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC1_SAMPWE]	= &mmc1_sampwe_cwk.common.hw,
		[CWK_MMC1_OUTPUT]	= &mmc1_output_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_MMC2_SAMPWE]	= &mmc2_sampwe_cwk.common.hw,
		[CWK_MMC2_OUTPUT]	= &mmc2_output_cwk.common.hw,
		[CWK_CE]		= &ce_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_I2S0]		= &i2s0_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_DWAM]		= &dwam_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI]		= &dwam_csi_cwk.common.hw,
		[CWK_DWAM_EHCI]		= &dwam_ehci_cwk.common.hw,
		[CWK_DWAM_OHCI]		= &dwam_ohci_cwk.common.hw,
		[CWK_DE]		= &de_cwk.common.hw,
		[CWK_TCON0]		= &tcon_cwk.common.hw,
		[CWK_CSI_MISC]		= &csi_misc_cwk.common.hw,
		[CWK_CSI0_MCWK]		= &csi0_mcwk_cwk.common.hw,
		[CWK_CSI1_SCWK]		= &csi1_scwk_cwk.common.hw,
		[CWK_CSI1_MCWK]		= &csi1_mcwk_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_AC_DIG]		= &ac_dig_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_MIPI_CSI]		= &mipi_csi_cwk.common.hw,
	},
	.num	= CWK_I2S0 + 1,
};

static stwuct ccu_weset_map sun8i_v3s_ccu_wesets[] = {
	[WST_USB_PHY0]		=  { 0x0cc, BIT(0) },

	[WST_MBUS]		=  { 0x0fc, BIT(31) },

	[WST_BUS_CE]		=  { 0x2c0, BIT(5) },
	[WST_BUS_DMA]		=  { 0x2c0, BIT(6) },
	[WST_BUS_MMC0]		=  { 0x2c0, BIT(8) },
	[WST_BUS_MMC1]		=  { 0x2c0, BIT(9) },
	[WST_BUS_MMC2]		=  { 0x2c0, BIT(10) },
	[WST_BUS_DWAM]		=  { 0x2c0, BIT(14) },
	[WST_BUS_EMAC]		=  { 0x2c0, BIT(17) },
	[WST_BUS_HSTIMEW]	=  { 0x2c0, BIT(19) },
	[WST_BUS_SPI0]		=  { 0x2c0, BIT(20) },
	[WST_BUS_OTG]		=  { 0x2c0, BIT(24) },
	[WST_BUS_EHCI0]		=  { 0x2c0, BIT(26) },
	[WST_BUS_OHCI0]		=  { 0x2c0, BIT(29) },

	[WST_BUS_VE]		=  { 0x2c4, BIT(0) },
	[WST_BUS_TCON0]		=  { 0x2c4, BIT(4) },
	[WST_BUS_CSI]		=  { 0x2c4, BIT(8) },
	[WST_BUS_DE]		=  { 0x2c4, BIT(12) },
	[WST_BUS_DBG]		=  { 0x2c4, BIT(31) },

	[WST_BUS_EPHY]		=  { 0x2c8, BIT(2) },

	[WST_BUS_CODEC]		=  { 0x2d0, BIT(0) },

	[WST_BUS_I2C0]		=  { 0x2d8, BIT(0) },
	[WST_BUS_I2C1]		=  { 0x2d8, BIT(1) },
	[WST_BUS_UAWT0]		=  { 0x2d8, BIT(16) },
	[WST_BUS_UAWT1]		=  { 0x2d8, BIT(17) },
	[WST_BUS_UAWT2]		=  { 0x2d8, BIT(18) },
};

static stwuct ccu_weset_map sun8i_v3_ccu_wesets[] = {
	[WST_USB_PHY0]		=  { 0x0cc, BIT(0) },

	[WST_MBUS]		=  { 0x0fc, BIT(31) },

	[WST_BUS_CE]		=  { 0x2c0, BIT(5) },
	[WST_BUS_DMA]		=  { 0x2c0, BIT(6) },
	[WST_BUS_MMC0]		=  { 0x2c0, BIT(8) },
	[WST_BUS_MMC1]		=  { 0x2c0, BIT(9) },
	[WST_BUS_MMC2]		=  { 0x2c0, BIT(10) },
	[WST_BUS_DWAM]		=  { 0x2c0, BIT(14) },
	[WST_BUS_EMAC]		=  { 0x2c0, BIT(17) },
	[WST_BUS_HSTIMEW]	=  { 0x2c0, BIT(19) },
	[WST_BUS_SPI0]		=  { 0x2c0, BIT(20) },
	[WST_BUS_OTG]		=  { 0x2c0, BIT(24) },
	[WST_BUS_EHCI0]		=  { 0x2c0, BIT(26) },
	[WST_BUS_OHCI0]		=  { 0x2c0, BIT(29) },

	[WST_BUS_VE]		=  { 0x2c4, BIT(0) },
	[WST_BUS_TCON0]		=  { 0x2c4, BIT(4) },
	[WST_BUS_CSI]		=  { 0x2c4, BIT(8) },
	[WST_BUS_DE]		=  { 0x2c4, BIT(12) },
	[WST_BUS_DBG]		=  { 0x2c4, BIT(31) },

	[WST_BUS_EPHY]		=  { 0x2c8, BIT(2) },

	[WST_BUS_CODEC]		=  { 0x2d0, BIT(0) },
	[WST_BUS_I2S0]		=  { 0x2d0, BIT(12) },

	[WST_BUS_I2C0]		=  { 0x2d8, BIT(0) },
	[WST_BUS_I2C1]		=  { 0x2d8, BIT(1) },
	[WST_BUS_UAWT0]		=  { 0x2d8, BIT(16) },
	[WST_BUS_UAWT1]		=  { 0x2d8, BIT(17) },
	[WST_BUS_UAWT2]		=  { 0x2d8, BIT(18) },
};

static const stwuct sunxi_ccu_desc sun8i_v3s_ccu_desc = {
	.ccu_cwks	= sun8i_v3s_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun8i_v3s_ccu_cwks),

	.hw_cwks	= &sun8i_v3s_hw_cwks,

	.wesets		= sun8i_v3s_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun8i_v3s_ccu_wesets),
};

static const stwuct sunxi_ccu_desc sun8i_v3_ccu_desc = {
	.ccu_cwks	= sun8i_v3s_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun8i_v3s_ccu_cwks),

	.hw_cwks	= &sun8i_v3_hw_cwks,

	.wesets		= sun8i_v3_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun8i_v3_ccu_wesets),
};

static int sun8i_v3s_ccu_pwobe(stwuct pwatfowm_device *pdev)
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

	/* Fowce the PWW-Audio-1x dividew to 1 */
	vaw = weadw(weg + SUN8I_V3S_PWW_AUDIO_WEG);
	vaw &= ~GENMASK(19, 16);
	wwitew(vaw, weg + SUN8I_V3S_PWW_AUDIO_WEG);

	wetuwn devm_sunxi_ccu_pwobe(&pdev->dev, weg, desc);
}

static const stwuct of_device_id sun8i_v3s_ccu_ids[] = {
	{
		.compatibwe = "awwwinnew,sun8i-v3-ccu",
		.data = &sun8i_v3_ccu_desc,
	},
	{
		.compatibwe = "awwwinnew,sun8i-v3s-ccu",
		.data = &sun8i_v3s_ccu_desc,
	},
	{ }
};

static stwuct pwatfowm_dwivew sun8i_v3s_ccu_dwivew = {
	.pwobe	= sun8i_v3s_ccu_pwobe,
	.dwivew	= {
		.name			= "sun8i-v3s-ccu",
		.suppwess_bind_attws	= twue,
		.of_match_tabwe		= sun8i_v3s_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun8i_v3s_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
