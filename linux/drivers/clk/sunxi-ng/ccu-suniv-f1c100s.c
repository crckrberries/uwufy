// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Icenowy Zheng <icenowy@aosc.io>
 *
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

#incwude "ccu-suniv-f1c100s.h"

static stwuct ccu_nkmp pww_cpu_cwk = {
	.enabwe = BIT(31),
	.wock	= BIT(28),

	.n	= _SUNXI_CCU_MUWT(8, 5),
	.k	= _SUNXI_CCU_MUWT(4, 2),
	.m	= _SUNXI_CCU_DIV(0, 2),
	/* MAX is guessed by the BSP tabwe */
	.p	= _SUNXI_CCU_DIV_MAX(16, 2, 4),

	.common	= {
		.weg		= 0x000,
		.hw.init	= CWK_HW_INIT("pww-cpu", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/*
 * The Audio PWW is supposed to have 4 outputs: 3 fixed factows fwom
 * the base (2x, 4x and 8x), and one vawiabwe dividew (the one twue
 * pww audio).
 *
 * We don't have any need fow the vawiabwe dividew fow now, so we just
 * hawdcode it to match with the cwock names
 */
#define SUNIV_PWW_AUDIO_WEG	0x008

static SUNXI_CCU_NM_WITH_GATE_WOCK(pww_audio_base_cwk, "pww-audio-base",
				   "osc24M", 0x008,
				   8, 7,		/* N */
				   0, 5,		/* M */
				   BIT(31),		/* gate */
				   BIT(28),		/* wock */
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

static SUNXI_CCU_NKM_WITH_GATE_WOCK(pww_ddw0_cwk, "pww-ddw",
				    "osc24M", 0x020,
				    8, 5,		/* N */
				    4, 2,		/* K */
				    0, 2,		/* M */
				    BIT(31),		/* gate */
				    BIT(28),		/* wock */
				    CWK_IS_CWITICAW);

static stwuct ccu_nk pww_pewiph_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.n		= _SUNXI_CCU_MUWT(8, 5),
	.common		= {
		.weg		= 0x028,
		.hw.init	= CWK_HW_INIT("pww-pewiph", "osc24M",
					      &ccu_nk_ops, 0),
	},
};

static const chaw * const cpu_pawents[] = { "osc32k", "osc24M",
					     "pww-cpu", "pww-cpu" };
static SUNXI_CCU_MUX(cpu_cwk, "cpu", cpu_pawents,
		     0x050, 16, 2, CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT);

static const chaw * const ahb_pawents[] = { "osc32k", "osc24M",
					    "cpu", "pww-pewiph" };
static const stwuct ccu_mux_vaw_pwediv ahb_pwedivs[] = {
	{ .index = 3, .shift = 6, .width = 2 },
};
static stwuct ccu_div ahb_cwk = {
	.div		= _SUNXI_CCU_DIV_FWAGS(4, 2, CWK_DIVIDEW_POWEW_OF_TWO),

	.mux		= {
		.shift	= 12,
		.width	= 2,

		.vaw_pwedivs	= ahb_pwedivs,
		.n_vaw_pwedivs	= AWWAY_SIZE(ahb_pwedivs),
	},

	.common		= {
		.weg		= 0x054,
		.featuwes	= CCU_FEATUWE_VAWIABWE_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("ahb",
						      ahb_pawents,
						      &ccu_div_ops,
						      0),
	},
};

static stwuct cwk_div_tabwe apb_div_tabwe[] = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 4 },
	{ .vaw = 3, .div = 8 },
	{ /* Sentinew */ },
};
static SUNXI_CCU_DIV_TABWE(apb_cwk, "apb", "ahb",
			   0x054, 8, 2, apb_div_tabwe, 0);

static SUNXI_CCU_GATE(bus_dma_cwk,	"bus-dma",	"ahb",
		      0x060, BIT(6), 0);
static SUNXI_CCU_GATE(bus_mmc0_cwk,	"bus-mmc0",	"ahb",
		      0x060, BIT(8), 0);
static SUNXI_CCU_GATE(bus_mmc1_cwk,	"bus-mmc1",	"ahb",
		      0x060, BIT(9), 0);
static SUNXI_CCU_GATE(bus_dwam_cwk,	"bus-dwam",	"ahb",
		      0x060, BIT(14), 0);
static SUNXI_CCU_GATE(bus_spi0_cwk,	"bus-spi0",	"ahb",
		      0x060, BIT(20), 0);
static SUNXI_CCU_GATE(bus_spi1_cwk,	"bus-spi1",	"ahb",
		      0x060, BIT(21), 0);
static SUNXI_CCU_GATE(bus_otg_cwk,	"bus-otg",	"ahb",
		      0x060, BIT(24), 0);

static SUNXI_CCU_GATE(bus_ve_cwk,	"bus-ve",	"ahb",
		      0x064, BIT(0), 0);
static SUNXI_CCU_GATE(bus_wcd_cwk,	"bus-wcd",	"ahb",
		      0x064, BIT(4), 0);
static SUNXI_CCU_GATE(bus_deintewwace_cwk,	"bus-deintewwace",	"ahb",
		      0x064, BIT(5), 0);
static SUNXI_CCU_GATE(bus_csi_cwk,	"bus-csi",	"ahb",
		      0x064, BIT(8), 0);
static SUNXI_CCU_GATE(bus_tvd_cwk,	"bus-tvd",	"ahb",
		      0x064, BIT(9), 0);
static SUNXI_CCU_GATE(bus_tve_cwk,	"bus-tve",	"ahb",
		      0x064, BIT(10), 0);
static SUNXI_CCU_GATE(bus_de_be_cwk,	"bus-de-be",	"ahb",
		      0x064, BIT(12), 0);
static SUNXI_CCU_GATE(bus_de_fe_cwk,	"bus-de-fe",	"ahb",
		      0x064, BIT(14), 0);

static SUNXI_CCU_GATE(bus_codec_cwk,	"bus-codec",	"apb",
		      0x068, BIT(0), 0);
static SUNXI_CCU_GATE(bus_spdif_cwk,	"bus-spdif",	"apb",
		      0x068, BIT(1), 0);
static SUNXI_CCU_GATE(bus_iw_cwk,	"bus-iw",	"apb",
		      0x068, BIT(2), 0);
static SUNXI_CCU_GATE(bus_wsb_cwk,	"bus-wsb",	"apb",
		      0x068, BIT(3), 0);
static SUNXI_CCU_GATE(bus_i2s0_cwk,	"bus-i2s0",	"apb",
		      0x068, BIT(12), 0);
static SUNXI_CCU_GATE(bus_i2c0_cwk,	"bus-i2c0",	"apb",
		      0x068, BIT(16), 0);
static SUNXI_CCU_GATE(bus_i2c1_cwk,	"bus-i2c1",	"apb",
		      0x068, BIT(17), 0);
static SUNXI_CCU_GATE(bus_i2c2_cwk,	"bus-i2c2",	"apb",
		      0x068, BIT(18), 0);
static SUNXI_CCU_GATE(bus_pio_cwk,	"bus-pio",	"apb",
		      0x068, BIT(19), 0);
static SUNXI_CCU_GATE(bus_uawt0_cwk,	"bus-uawt0",	"apb",
		      0x068, BIT(20), 0);
static SUNXI_CCU_GATE(bus_uawt1_cwk,	"bus-uawt1",	"apb",
		      0x068, BIT(21), 0);
static SUNXI_CCU_GATE(bus_uawt2_cwk,	"bus-uawt2",	"apb",
		      0x068, BIT(22), 0);

static const chaw * const mod0_defauwt_pawents[] = { "osc24M", "pww-pewiph" };
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

static const chaw * const i2s_spdif_pawents[] = { "pww-audio-8x",
						  "pww-audio-4x",
						  "pww-audio-2x",
						  "pww-audio" };

static SUNXI_CCU_MUX_WITH_GATE(i2s_cwk, "i2s", i2s_spdif_pawents,
			       0x0b0, 16, 2, BIT(31), 0);

static SUNXI_CCU_MUX_WITH_GATE(spdif_cwk, "spdif", i2s_spdif_pawents,
			       0x0b4, 16, 2, BIT(31), 0);

static const chaw * const iw_pawents[] = { "osc32k", "osc24M" };
static SUNXI_CCU_MP_WITH_MUX_GATE(iw_cwk, "iw",
				  iw_pawents, 0x0b8,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,        /* mux */
				  BIT(31),      /* gate */
				  0);

static SUNXI_CCU_GATE(usb_phy0_cwk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(1), 0);

static SUNXI_CCU_GATE(dwam_ve_cwk,	"dwam-ve",	"pww-ddw",
		      0x100, BIT(0), 0);
static SUNXI_CCU_GATE(dwam_csi_cwk,	"dwam-csi",	"pww-ddw",
		      0x100, BIT(1), 0);
static SUNXI_CCU_GATE(dwam_deintewwace_cwk,	"dwam-deintewwace",
		      "pww-ddw", 0x100, BIT(2), 0);
static SUNXI_CCU_GATE(dwam_tvd_cwk,	"dwam-tvd",	"pww-ddw",
		      0x100, BIT(3), 0);
static SUNXI_CCU_GATE(dwam_de_fe_cwk,	"dwam-de-fe",	"pww-ddw",
		      0x100, BIT(24), 0);
static SUNXI_CCU_GATE(dwam_de_be_cwk,	"dwam-de-be",	"pww-ddw",
		      0x100, BIT(26), 0);

static const chaw * const de_pawents[] = { "pww-video", "pww-pewiph" };
static const u8 de_tabwe[] = { 0, 2, };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(de_be_cwk, "de-be",
				       de_pawents, de_tabwe,
				       0x104, 0, 4, 24, 3, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(de_fe_cwk, "de-fe",
				       de_pawents, de_tabwe,
				       0x10c, 0, 4, 24, 3, BIT(31), 0);

static const chaw * const tcon_pawents[] = { "pww-video", "pww-video-2x" };
static const u8 tcon_tabwe[] = { 0, 2, };
static SUNXI_CCU_MUX_TABWE_WITH_GATE(tcon_cwk, "tcon",
				     tcon_pawents, tcon_tabwe,
				     0x118, 24, 3, BIT(31),
				     CWK_SET_WATE_PAWENT);

static const chaw * const deintewwace_pawents[] = { "pww-video",
						    "pww-video-2x" };
static const u8 deintewwace_tabwe[] = { 0, 2, };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(deintewwace_cwk, "deintewwace",
				       deintewwace_pawents, deintewwace_tabwe,
				       0x11c, 0, 4, 24, 3, BIT(31), 0);

static const chaw * const tve_cwk2_pawents[] = { "pww-video",
						 "pww-video-2x" };
static const u8 tve_cwk2_tabwe[] = { 0, 2, };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(tve_cwk2_cwk, "tve-cwk2",
				       tve_cwk2_pawents, tve_cwk2_tabwe,
				       0x120, 0, 4, 24, 3, BIT(31), 0);
static SUNXI_CCU_M_WITH_GATE(tve_cwk1_cwk, "tve-cwk1", "tve-cwk2",
			     0x120, 8, 1, BIT(15), 0);

static const chaw * const tvd_pawents[] = { "pww-video", "osc24M",
					    "pww-video-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(tvd_cwk, "tvd", tvd_pawents,
				 0x124, 0, 4, 24, 3, BIT(31), 0);

static const chaw * const csi_pawents[] = { "pww-video", "osc24M" };
static const u8 csi_tabwe[] = { 0, 5, };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi_cwk, "csi", csi_pawents, csi_tabwe,
				       0x120, 0, 4, 8, 3, BIT(15), 0);

/*
 * TODO: BSP says the pawent is pww-audio, howevew common sense and expewience
 * towd us it shouwd be pww-ve. pww-ve is totawwy not used in BSP code.
 */
static SUNXI_CCU_GATE(ve_cwk, "ve", "pww-audio", 0x13c, BIT(31), 0);

static SUNXI_CCU_GATE(codec_cwk, "codec", "pww-audio", 0x140, BIT(31), 0);

static SUNXI_CCU_GATE(avs_cwk, "avs", "osc24M", 0x144, BIT(31), 0);

static stwuct ccu_common *suniv_ccu_cwks[] = {
	&pww_cpu_cwk.common,
	&pww_audio_base_cwk.common,
	&pww_video_cwk.common,
	&pww_ve_cwk.common,
	&pww_ddw0_cwk.common,
	&pww_pewiph_cwk.common,
	&cpu_cwk.common,
	&ahb_cwk.common,
	&apb_cwk.common,
	&bus_dma_cwk.common,
	&bus_mmc0_cwk.common,
	&bus_mmc1_cwk.common,
	&bus_dwam_cwk.common,
	&bus_spi0_cwk.common,
	&bus_spi1_cwk.common,
	&bus_otg_cwk.common,
	&bus_ve_cwk.common,
	&bus_wcd_cwk.common,
	&bus_deintewwace_cwk.common,
	&bus_csi_cwk.common,
	&bus_tve_cwk.common,
	&bus_tvd_cwk.common,
	&bus_de_be_cwk.common,
	&bus_de_fe_cwk.common,
	&bus_codec_cwk.common,
	&bus_spdif_cwk.common,
	&bus_iw_cwk.common,
	&bus_wsb_cwk.common,
	&bus_i2s0_cwk.common,
	&bus_i2c0_cwk.common,
	&bus_i2c1_cwk.common,
	&bus_i2c2_cwk.common,
	&bus_pio_cwk.common,
	&bus_uawt0_cwk.common,
	&bus_uawt1_cwk.common,
	&bus_uawt2_cwk.common,
	&mmc0_cwk.common,
	&mmc0_sampwe_cwk.common,
	&mmc0_output_cwk.common,
	&mmc1_cwk.common,
	&mmc1_sampwe_cwk.common,
	&mmc1_output_cwk.common,
	&i2s_cwk.common,
	&spdif_cwk.common,
	&iw_cwk.common,
	&usb_phy0_cwk.common,
	&dwam_ve_cwk.common,
	&dwam_csi_cwk.common,
	&dwam_deintewwace_cwk.common,
	&dwam_tvd_cwk.common,
	&dwam_de_fe_cwk.common,
	&dwam_de_be_cwk.common,
	&de_be_cwk.common,
	&de_fe_cwk.common,
	&tcon_cwk.common,
	&deintewwace_cwk.common,
	&tve_cwk2_cwk.common,
	&tve_cwk1_cwk.common,
	&tvd_cwk.common,
	&csi_cwk.common,
	&ve_cwk.common,
	&codec_cwk.common,
	&avs_cwk.common,
};

static const stwuct cwk_hw *cwk_pawent_pww_audio[] = {
	&pww_audio_base_cwk.common.hw
};

static CWK_FIXED_FACTOW_HWS(pww_audio_cwk, "pww-audio",
			    cwk_pawent_pww_audio,
			    4, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_audio_2x_cwk, "pww-audio-2x",
			    cwk_pawent_pww_audio,
			    2, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_audio_4x_cwk, "pww-audio-4x",
			    cwk_pawent_pww_audio,
			    1, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_audio_8x_cwk, "pww-audio-8x",
			    cwk_pawent_pww_audio,
			    1, 2, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HW(pww_video_2x_cwk, "pww-video-2x",
			    &pww_video_cwk.common.hw,
			    1, 2, 0);

static stwuct cwk_hw_oneceww_data suniv_hw_cwks = {
	.hws	= {
		[CWK_PWW_CPU]		= &pww_cpu_cwk.common.hw,
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
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AHB]		= &ahb_cwk.common.hw,
		[CWK_APB]		= &apb_cwk.common.hw,
		[CWK_BUS_DMA]		= &bus_dma_cwk.common.hw,
		[CWK_BUS_MMC0]		= &bus_mmc0_cwk.common.hw,
		[CWK_BUS_MMC1]		= &bus_mmc1_cwk.common.hw,
		[CWK_BUS_DWAM]		= &bus_dwam_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_SPI1]		= &bus_spi1_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_BUS_WCD]		= &bus_wcd_cwk.common.hw,
		[CWK_BUS_DEINTEWWACE]	= &bus_deintewwace_cwk.common.hw,
		[CWK_BUS_CSI]		= &bus_csi_cwk.common.hw,
		[CWK_BUS_TVD]		= &bus_tvd_cwk.common.hw,
		[CWK_BUS_TVE]		= &bus_tve_cwk.common.hw,
		[CWK_BUS_DE_BE]		= &bus_de_be_cwk.common.hw,
		[CWK_BUS_DE_FE]		= &bus_de_fe_cwk.common.hw,
		[CWK_BUS_CODEC]		= &bus_codec_cwk.common.hw,
		[CWK_BUS_SPDIF]		= &bus_spdif_cwk.common.hw,
		[CWK_BUS_IW]		= &bus_iw_cwk.common.hw,
		[CWK_BUS_WSB]		= &bus_wsb_cwk.common.hw,
		[CWK_BUS_I2S0]		= &bus_i2s0_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_I2C2]		= &bus_i2c2_cwk.common.hw,
		[CWK_BUS_PIO]		= &bus_pio_cwk.common.hw,
		[CWK_BUS_UAWT0]		= &bus_uawt0_cwk.common.hw,
		[CWK_BUS_UAWT1]		= &bus_uawt1_cwk.common.hw,
		[CWK_BUS_UAWT2]		= &bus_uawt2_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC0_SAMPWE]	= &mmc0_sampwe_cwk.common.hw,
		[CWK_MMC0_OUTPUT]	= &mmc0_output_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC1_SAMPWE]	= &mmc1_sampwe_cwk.common.hw,
		[CWK_MMC1_OUTPUT]	= &mmc1_output_cwk.common.hw,
		[CWK_I2S]		= &i2s_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_IW]		= &iw_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI]		= &dwam_csi_cwk.common.hw,
		[CWK_DWAM_DEINTEWWACE]	= &dwam_deintewwace_cwk.common.hw,
		[CWK_DWAM_TVD]		= &dwam_tvd_cwk.common.hw,
		[CWK_DWAM_DE_FE]	= &dwam_de_fe_cwk.common.hw,
		[CWK_DWAM_DE_BE]	= &dwam_de_be_cwk.common.hw,
		[CWK_DE_BE]		= &de_be_cwk.common.hw,
		[CWK_DE_FE]		= &de_fe_cwk.common.hw,
		[CWK_TCON]		= &tcon_cwk.common.hw,
		[CWK_DEINTEWWACE]	= &deintewwace_cwk.common.hw,
		[CWK_TVE2_CWK]		= &tve_cwk2_cwk.common.hw,
		[CWK_TVE1_CWK]		= &tve_cwk1_cwk.common.hw,
		[CWK_TVD]		= &tvd_cwk.common.hw,
		[CWK_CSI]		= &csi_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_CODEC]		= &codec_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct ccu_weset_map suniv_ccu_wesets[] = {
	[WST_USB_PHY0]		=  { 0x0cc, BIT(0) },

	[WST_BUS_DMA]		=  { 0x2c0, BIT(6) },
	[WST_BUS_MMC0]		=  { 0x2c0, BIT(8) },
	[WST_BUS_MMC1]		=  { 0x2c0, BIT(9) },
	[WST_BUS_DWAM]		=  { 0x2c0, BIT(14) },
	[WST_BUS_SPI0]		=  { 0x2c0, BIT(20) },
	[WST_BUS_SPI1]		=  { 0x2c0, BIT(21) },
	[WST_BUS_OTG]		=  { 0x2c0, BIT(24) },
	[WST_BUS_VE]		=  { 0x2c4, BIT(0) },
	[WST_BUS_WCD]		=  { 0x2c4, BIT(4) },
	[WST_BUS_DEINTEWWACE]	=  { 0x2c4, BIT(5) },
	[WST_BUS_CSI]		=  { 0x2c4, BIT(8) },
	[WST_BUS_TVD]		=  { 0x2c4, BIT(9) },
	[WST_BUS_TVE]		=  { 0x2c4, BIT(10) },
	[WST_BUS_DE_BE]		=  { 0x2c4, BIT(12) },
	[WST_BUS_DE_FE]		=  { 0x2c4, BIT(14) },
	[WST_BUS_CODEC]		=  { 0x2d0, BIT(0) },
	[WST_BUS_SPDIF]		=  { 0x2d0, BIT(1) },
	[WST_BUS_IW]		=  { 0x2d0, BIT(2) },
	[WST_BUS_WSB]		=  { 0x2d0, BIT(3) },
	[WST_BUS_I2S0]		=  { 0x2d0, BIT(12) },
	[WST_BUS_I2C0]		=  { 0x2d0, BIT(16) },
	[WST_BUS_I2C1]		=  { 0x2d0, BIT(17) },
	[WST_BUS_I2C2]		=  { 0x2d0, BIT(18) },
	[WST_BUS_UAWT0]		=  { 0x2d0, BIT(20) },
	[WST_BUS_UAWT1]		=  { 0x2d0, BIT(21) },
	[WST_BUS_UAWT2]		=  { 0x2d0, BIT(22) },
};

static const stwuct sunxi_ccu_desc suniv_ccu_desc = {
	.ccu_cwks	= suniv_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(suniv_ccu_cwks),

	.hw_cwks	= &suniv_hw_cwks,

	.wesets		= suniv_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(suniv_ccu_wesets),
};

static stwuct ccu_pww_nb suniv_pww_cpu_nb = {
	.common	= &pww_cpu_cwk.common,
	/* copy fwom pww_cpu_cwk */
	.enabwe	= BIT(31),
	.wock	= BIT(28),
};

static stwuct ccu_mux_nb suniv_cpu_nb = {
	.common		= &cpu_cwk.common,
	.cm		= &cpu_cwk.mux,
	.deway_us	= 1, /* > 8 cwock cycwes at 24 MHz */
	.bypass_index	= 1, /* index of 24 MHz osciwwatow */
};

static int suniv_f1c100s_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *weg;
	int wet;
	u32 vaw;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	/* Fowce the PWW-Audio-1x dividew to 4 */
	vaw = weadw(weg + SUNIV_PWW_AUDIO_WEG);
	vaw &= ~GENMASK(19, 16);
	wwitew(vaw | (3 << 16), weg + SUNIV_PWW_AUDIO_WEG);

	wet = devm_sunxi_ccu_pwobe(&pdev->dev, weg, &suniv_ccu_desc);
	if (wet)
		wetuwn wet;

	/* Gate then ungate PWW CPU aftew any wate changes */
	ccu_pww_notifiew_wegistew(&suniv_pww_cpu_nb);

	/* Wepawent CPU duwing PWW CPU wate changes */
	ccu_mux_notifiew_wegistew(pww_cpu_cwk.common.hw.cwk,
				  &suniv_cpu_nb);

	wetuwn 0;
}

static const stwuct of_device_id suniv_f1c100s_ccu_ids[] = {
	{ .compatibwe = "awwwinnew,suniv-f1c100s-ccu" },
	{ }
};

static stwuct pwatfowm_dwivew suniv_f1c100s_ccu_dwivew = {
	.pwobe	= suniv_f1c100s_ccu_pwobe,
	.dwivew	= {
		.name			= "suniv-f1c100s-ccu",
		.suppwess_bind_attws	= twue,
		.of_match_tabwe		= suniv_f1c100s_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(suniv_f1c100s_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
