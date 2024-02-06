// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

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

#incwude "ccu-sun8i-w40.h"

/* TODO: The wesuwt of N*K is wequiwed to be in [10, 88] wange. */
static stwuct ccu_nkmp pww_cpu_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT(8, 5),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.m		= _SUNXI_CCU_DIV(0, 2),
	.p		= _SUNXI_CCU_DIV_MAX(16, 2, 4),
	.common		= {
		.weg		= 0x000,
		.hw.init	= CWK_HW_INIT("pww-cpu",
					      "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
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
#define SUN8I_W40_PWW_AUDIO_WEG	0x008

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

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK_MIN_MAX(pww_video0_cwk, "pww-video0",
						"osc24M", 0x0010,
						192000000,  /* Minimum wate */
						1008000000, /* Maximum wate */
						8, 7,       /* N */
						0, 4,       /* M */
						BIT(24),    /* fwac enabwe */
						BIT(25),    /* fwac sewect */
						270000000,  /* fwac wate 0 */
						297000000,  /* fwac wate 1 */
						BIT(31),    /* gate */
						BIT(28),    /* wock */
						CWK_SET_WATE_UNGATE);

/* TODO: The wesuwt of N/M is wequiwed to be in [8, 25] wange. */
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
					CWK_SET_WATE_UNGATE);

/* TODO: The wesuwt of N*K is wequiwed to be in [10, 77] wange. */
static SUNXI_CCU_NKM_WITH_GATE_WOCK(pww_ddw0_cwk, "pww-ddw0",
				    "osc24M", 0x020,
				    8, 5,	/* N */
				    4, 2,	/* K */
				    0, 2,	/* M */
				    BIT(31),	/* gate */
				    BIT(28),	/* wock */
				    CWK_SET_WATE_UNGATE);

/* TODO: The wesuwt of N*K is wequiwed to be in [21, 58] wange. */
static stwuct ccu_nk pww_pewiph0_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT(8, 5),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.fixed_post_div	= 2,
	.common		= {
		.weg		= 0x028,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph0", "osc24M",
					      &ccu_nk_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_div pww_pewiph0_sata_cwk = {
	.enabwe		= BIT(24),
	.div		= _SUNXI_CCU_DIV(0, 2),
	/*
	 * The fowmuwa of pww-pewiph0 (1x) is 24MHz*N*K/2, and the fowmuwa
	 * of pww-pewiph0-sata is 24MHz*N*K/M/6, so the postdiv hewe is
	 * 6/2 = 3.
	 */
	.fixed_post_div	= 3,
	.common		= {
		.weg		= 0x028,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph0-sata",
					      "pww-pewiph0",
					      &ccu_div_ops, 0),
	},
};

/* TODO: The wesuwt of N*K is wequiwed to be in [21, 58] wange. */
static stwuct ccu_nk pww_pewiph1_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT(8, 5),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.fixed_post_div	= 2,
	.common		= {
		.weg		= 0x02c,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph1", "osc24M",
					      &ccu_nk_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static SUNXI_CCU_NM_WITH_FWAC_GATE_WOCK_MIN_MAX(pww_video1_cwk, "pww-video1",
						"osc24M", 0x030,
						192000000,  /* Minimum wate */
						1008000000, /* Maximum wate */
						8, 7,       /* N */
						0, 4,       /* M */
						BIT(24),    /* fwac enabwe */
						BIT(25),    /* fwac sewect */
						270000000,  /* fwac wate 0 */
						297000000,  /* fwac wate 1 */
						BIT(31),    /* gate */
						BIT(28),    /* wock */
						CWK_SET_WATE_UNGATE);

static stwuct ccu_nkm pww_sata_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT(8, 5),
	.k		= _SUNXI_CCU_MUWT(4, 2),
	.m		= _SUNXI_CCU_DIV(0, 2),
	.fixed_post_div	= 6,
	.common		= {
		.weg		= 0x034,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-sata", "osc24M",
					      &ccu_nkm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static const chaw * const pww_sata_out_pawents[] = { "pww-sata",
						     "pww-pewiph0-sata" };
static SUNXI_CCU_MUX_WITH_GATE(pww_sata_out_cwk, "pww-sata-out",
			       pww_sata_out_pawents, 0x034,
			       30, 1,	/* mux */
			       BIT(14),	/* gate */
			       CWK_SET_WATE_PAWENT);

/* TODO: The wesuwt of N/M is wequiwed to be in [8, 25] wange. */
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
 *
 * TODO: In the MIPI mode, M/N is wequiwed to be equaw ow wessew than 3,
 * which cannot be impwemented now.
 */
#define SUN8I_W40_PWW_MIPI_WEG	0x040

static const chaw * const pww_mipi_pawents[] = { "pww-video0" };
static stwuct ccu_nkm pww_mipi_cwk = {
	.enabwe	= BIT(31) | BIT(23) | BIT(22),
	.wock	= BIT(28),
	.n	= _SUNXI_CCU_MUWT(8, 4),
	.k	= _SUNXI_CCU_MUWT_MIN(4, 2, 2),
	.m	= _SUNXI_CCU_DIV(0, 4),
	.mux	= _SUNXI_CCU_MUX(21, 1),
	.common	= {
		.weg		= 0x040,
		.hw.init	= CWK_HW_INIT_PAWENTS("pww-mipi",
						      pww_mipi_pawents,
						      &ccu_nkm_ops,
						      CWK_SET_WATE_UNGATE)
	},
};

/* TODO: The wesuwt of N/M is wequiwed to be in [8, 25] wange. */
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

/* TODO: The N factow is wequiwed to be in [16, 75] wange. */
static SUNXI_CCU_NM_WITH_GATE_WOCK(pww_ddw1_cwk, "pww-ddw1",
				   "osc24M", 0x04c,
				   8, 7,	/* N */
				   0, 2,	/* M */
				   BIT(31),	/* gate */
				   BIT(28),	/* wock */
				   CWK_SET_WATE_UNGATE);

static const chaw * const cpu_pawents[] = { "osc32k", "osc24M",
					     "pww-cpu", "pww-cpu" };
static SUNXI_CCU_MUX(cpu_cwk, "cpu", cpu_pawents,
		     0x050, 16, 2, CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT);

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
					     "pww-pewiph0-2x",
					     "pww-pewiph0-2x" };
static SUNXI_CCU_MP_WITH_MUX(apb2_cwk, "apb2", apb2_pawents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static SUNXI_CCU_GATE(bus_mipi_dsi_cwk,	"bus-mipi-dsi",	"ahb1",
		      0x060, BIT(1), 0);
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
static SUNXI_CCU_GATE(bus_mmc3_cwk,	"bus-mmc3",	"ahb1",
		      0x060, BIT(11), 0);
static SUNXI_CCU_GATE(bus_nand_cwk,	"bus-nand",	"ahb1",
		      0x060, BIT(13), 0);
static SUNXI_CCU_GATE(bus_dwam_cwk,	"bus-dwam",	"ahb1",
		      0x060, BIT(14), 0);
static SUNXI_CCU_GATE(bus_emac_cwk,	"bus-emac",	"ahb1",
		      0x060, BIT(17), 0);
static SUNXI_CCU_GATE(bus_ts_cwk,	"bus-ts",	"ahb1",
		      0x060, BIT(18), 0);
static SUNXI_CCU_GATE(bus_hstimew_cwk,	"bus-hstimew",	"ahb1",
		      0x060, BIT(19), 0);
static SUNXI_CCU_GATE(bus_spi0_cwk,	"bus-spi0",	"ahb1",
		      0x060, BIT(20), 0);
static SUNXI_CCU_GATE(bus_spi1_cwk,	"bus-spi1",	"ahb1",
		      0x060, BIT(21), 0);
static SUNXI_CCU_GATE(bus_spi2_cwk,	"bus-spi2",	"ahb1",
		      0x060, BIT(22), 0);
static SUNXI_CCU_GATE(bus_spi3_cwk,	"bus-spi3",	"ahb1",
		      0x060, BIT(23), 0);
static SUNXI_CCU_GATE(bus_sata_cwk,	"bus-sata",	"ahb1",
		      0x060, BIT(24), 0);
static SUNXI_CCU_GATE(bus_otg_cwk,	"bus-otg",	"ahb1",
		      0x060, BIT(25), 0);
static SUNXI_CCU_GATE(bus_ehci0_cwk,	"bus-ehci0",	"ahb1",
		      0x060, BIT(26), 0);
static SUNXI_CCU_GATE(bus_ehci1_cwk,	"bus-ehci1",	"ahb1",
		      0x060, BIT(27), 0);
static SUNXI_CCU_GATE(bus_ehci2_cwk,	"bus-ehci2",	"ahb1",
		      0x060, BIT(28), 0);
static SUNXI_CCU_GATE(bus_ohci0_cwk,	"bus-ohci0",	"ahb1",
		      0x060, BIT(29), 0);
static SUNXI_CCU_GATE(bus_ohci1_cwk,	"bus-ohci1",	"ahb1",
		      0x060, BIT(30), 0);
static SUNXI_CCU_GATE(bus_ohci2_cwk,	"bus-ohci2",	"ahb1",
		      0x060, BIT(31), 0);

static SUNXI_CCU_GATE(bus_ve_cwk,	"bus-ve",	"ahb1",
		      0x064, BIT(0), 0);
static SUNXI_CCU_GATE(bus_mp_cwk,	"bus-mp",	"ahb1",
		      0x064, BIT(2), 0);
static SUNXI_CCU_GATE(bus_deintewwace_cwk,	"bus-deintewwace",	"ahb1",
		      0x064, BIT(5), 0);
static SUNXI_CCU_GATE(bus_csi0_cwk,	"bus-csi0",	"ahb1",
		      0x064, BIT(8), 0);
static SUNXI_CCU_GATE(bus_csi1_cwk,	"bus-csi1",	"ahb1",
		      0x064, BIT(9), 0);
static SUNXI_CCU_GATE(bus_hdmi0_cwk,	"bus-hdmi0",	"ahb1",
		      0x064, BIT(10), 0);
static SUNXI_CCU_GATE(bus_hdmi1_cwk,	"bus-hdmi1",	"ahb1",
		      0x064, BIT(11), 0);
static SUNXI_CCU_GATE(bus_de_cwk,	"bus-de",	"ahb1",
		      0x064, BIT(12), 0);
static SUNXI_CCU_GATE(bus_tve0_cwk,	"bus-tve0",	"ahb1",
		      0x064, BIT(13), 0);
static SUNXI_CCU_GATE(bus_tve1_cwk,	"bus-tve1",	"ahb1",
		      0x064, BIT(14), 0);
static SUNXI_CCU_GATE(bus_tve_top_cwk,	"bus-tve-top",	"ahb1",
		      0x064, BIT(15), 0);
static SUNXI_CCU_GATE(bus_gmac_cwk,	"bus-gmac",	"ahb1",
		      0x064, BIT(17), 0);
static SUNXI_CCU_GATE(bus_gpu_cwk,	"bus-gpu",	"ahb1",
		      0x064, BIT(20), 0);
static SUNXI_CCU_GATE(bus_tvd0_cwk,	"bus-tvd0",	"ahb1",
		      0x064, BIT(21), 0);
static SUNXI_CCU_GATE(bus_tvd1_cwk,	"bus-tvd1",	"ahb1",
		      0x064, BIT(22), 0);
static SUNXI_CCU_GATE(bus_tvd2_cwk,	"bus-tvd2",	"ahb1",
		      0x064, BIT(23), 0);
static SUNXI_CCU_GATE(bus_tvd3_cwk,	"bus-tvd3",	"ahb1",
		      0x064, BIT(24), 0);
static SUNXI_CCU_GATE(bus_tvd_top_cwk,	"bus-tvd-top",	"ahb1",
		      0x064, BIT(25), 0);
static SUNXI_CCU_GATE(bus_tcon_wcd0_cwk,	"bus-tcon-wcd0",	"ahb1",
		      0x064, BIT(26), 0);
static SUNXI_CCU_GATE(bus_tcon_wcd1_cwk,	"bus-tcon-wcd1",	"ahb1",
		      0x064, BIT(27), 0);
static SUNXI_CCU_GATE(bus_tcon_tv0_cwk,	"bus-tcon-tv0",	"ahb1",
		      0x064, BIT(28), 0);
static SUNXI_CCU_GATE(bus_tcon_tv1_cwk,	"bus-tcon-tv1",	"ahb1",
		      0x064, BIT(29), 0);
static SUNXI_CCU_GATE(bus_tcon_top_cwk,	"bus-tcon-top",	"ahb1",
		      0x064, BIT(30), 0);

static SUNXI_CCU_GATE(bus_codec_cwk,	"bus-codec",	"apb1",
		      0x068, BIT(0), 0);
static SUNXI_CCU_GATE(bus_spdif_cwk,	"bus-spdif",	"apb1",
		      0x068, BIT(1), 0);
static SUNXI_CCU_GATE(bus_ac97_cwk,	"bus-ac97",	"apb1",
		      0x068, BIT(2), 0);
static SUNXI_CCU_GATE(bus_pio_cwk,	"bus-pio",	"apb1",
		      0x068, BIT(5), 0);
static SUNXI_CCU_GATE(bus_iw0_cwk,	"bus-iw0",	"apb1",
		      0x068, BIT(6), 0);
static SUNXI_CCU_GATE(bus_iw1_cwk,	"bus-iw1",	"apb1",
		      0x068, BIT(7), 0);
static SUNXI_CCU_GATE(bus_ths_cwk,	"bus-ths",	"apb1",
		      0x068, BIT(8), 0);
static SUNXI_CCU_GATE(bus_keypad_cwk,	"bus-keypad",	"apb1",
		      0x068, BIT(10), 0);
static SUNXI_CCU_GATE(bus_i2s0_cwk,	"bus-i2s0",	"apb1",
		      0x068, BIT(12), 0);
static SUNXI_CCU_GATE(bus_i2s1_cwk,	"bus-i2s1",	"apb1",
		      0x068, BIT(13), 0);
static SUNXI_CCU_GATE(bus_i2s2_cwk,	"bus-i2s2",	"apb1",
		      0x068, BIT(14), 0);

static SUNXI_CCU_GATE(bus_i2c0_cwk,	"bus-i2c0",	"apb2",
		      0x06c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2c1_cwk,	"bus-i2c1",	"apb2",
		      0x06c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_i2c2_cwk,	"bus-i2c2",	"apb2",
		      0x06c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_i2c3_cwk,	"bus-i2c3",	"apb2",
		      0x06c, BIT(3), 0);
/*
 * In datasheet hewe's "Wesewved", howevew the gate exists in BSP soucwe
 * code.
 */
static SUNXI_CCU_GATE(bus_can_cwk,	"bus-can",	"apb2",
		      0x06c, BIT(4), 0);
static SUNXI_CCU_GATE(bus_scw_cwk,	"bus-scw",	"apb2",
		      0x06c, BIT(5), 0);
static SUNXI_CCU_GATE(bus_ps20_cwk,	"bus-ps20",	"apb2",
		      0x06c, BIT(6), 0);
static SUNXI_CCU_GATE(bus_ps21_cwk,	"bus-ps21",	"apb2",
		      0x06c, BIT(7), 0);
static SUNXI_CCU_GATE(bus_i2c4_cwk,	"bus-i2c4",	"apb2",
		      0x06c, BIT(15), 0);
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
static SUNXI_CCU_GATE(bus_uawt5_cwk,	"bus-uawt5",	"apb2",
		      0x06c, BIT(21), 0);
static SUNXI_CCU_GATE(bus_uawt6_cwk,	"bus-uawt6",	"apb2",
		      0x06c, BIT(22), 0);
static SUNXI_CCU_GATE(bus_uawt7_cwk,	"bus-uawt7",	"apb2",
		      0x06c, BIT(23), 0);

static SUNXI_CCU_GATE(bus_dbg_cwk,	"bus-dbg",	"ahb1",
		      0x070, BIT(7), 0);

static const chaw * const ths_pawents[] = { "osc24M" };
static stwuct ccu_div ths_cwk = {
	.enabwe	= BIT(31),
	.div	= _SUNXI_CCU_DIV_FWAGS(0, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux	= _SUNXI_CCU_MUX(24, 2),
	.common	= {
		.weg		= 0x074,
		.hw.init	= CWK_HW_INIT_PAWENTS("ths",
						      ths_pawents,
						      &ccu_div_ops,
						      0),
	},
};

static const chaw * const mod0_defauwt_pawents[] = { "osc24M", "pww-pewiph0",
						     "pww-pewiph1" };
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

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc3_cwk, "mmc3", mod0_defauwt_pawents, 0x094,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static const chaw * const ts_pawents[] = { "osc24M", "pww-pewiph0", };
static SUNXI_CCU_MP_WITH_MUX_GATE(ts_cwk, "ts", ts_pawents, 0x098,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

static const chaw * const ce_pawents[] = { "osc24M", "pww-pewiph0-2x",
					   "pww-pewiph1-2x" };
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

static SUNXI_CCU_MP_WITH_MUX_GATE(spi3_cwk, "spi3", mod0_defauwt_pawents, 0x0ac,
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

static SUNXI_CCU_MUX_WITH_GATE(i2s2_cwk, "i2s2", i2s_pawents,
			       0x0b8, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_MUX_WITH_GATE(ac97_cwk, "ac97", i2s_pawents,
			       0x0bc, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_MUX_WITH_GATE(spdif_cwk, "spdif", i2s_pawents,
			       0x0c0, 16, 2, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw * const keypad_pawents[] = { "osc24M", "osc32k" };
static const u8 keypad_tabwe[] = { 0, 2 };
static stwuct ccu_mp keypad_cwk = {
	.enabwe	= BIT(31),
	.m	= _SUNXI_CCU_DIV(0, 5),
	.p	= _SUNXI_CCU_DIV(16, 2),
	.mux	= _SUNXI_CCU_MUX_TABWE(24, 2, keypad_tabwe),
	.common	= {
		.weg		= 0x0c4,
		.hw.init	= CWK_HW_INIT_PAWENTS("keypad",
						      keypad_pawents,
						      &ccu_mp_ops,
						      0),
	}
};

static const chaw * const sata_pawents[] = { "pww-sata-out", "sata-ext" };
static SUNXI_CCU_MUX_WITH_GATE(sata_cwk, "sata", sata_pawents,
			       0x0c8, 24, 1, BIT(31), CWK_SET_WATE_PAWENT);

/*
 * Thewe awe 3 OHCI 12M cwock souwce sewection bits in this wegistew.
 * We wiww fowce them to 0 (12M divided fwom 48M).
 */
#define SUN8I_W40_USB_CWK_WEG	0x0cc

static SUNXI_CCU_GATE(usb_phy0_cwk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(8), 0);
static SUNXI_CCU_GATE(usb_phy1_cwk,	"usb-phy1",	"osc24M",
		      0x0cc, BIT(9), 0);
static SUNXI_CCU_GATE(usb_phy2_cwk,	"usb-phy2",	"osc24M",
		      0x0cc, BIT(10), 0);
static SUNXI_CCU_GATE(usb_ohci0_cwk,	"usb-ohci0",	"osc12M",
		      0x0cc, BIT(16), 0);
static SUNXI_CCU_GATE(usb_ohci1_cwk,	"usb-ohci1",	"osc12M",
		      0x0cc, BIT(17), 0);
static SUNXI_CCU_GATE(usb_ohci2_cwk,	"usb-ohci2",	"osc12M",
		      0x0cc, BIT(18), 0);

static const chaw * const iw_pawents[] = { "osc24M", "pww-pewiph0",
					   "pww-pewiph1", "osc32k" };
static SUNXI_CCU_MP_WITH_MUX_GATE(iw0_cwk, "iw0", iw_pawents, 0x0d0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(iw1_cwk, "iw1", iw_pawents, 0x0d4,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static const chaw * const dwam_pawents[] = { "pww-ddw0", "pww-ddw1" };
static SUNXI_CCU_M_WITH_MUX(dwam_cwk, "dwam", dwam_pawents,
			    0x0f4, 0, 2, 20, 2, CWK_IS_CWITICAW);

static SUNXI_CCU_GATE(dwam_ve_cwk,	"dwam-ve",	"dwam",
		      0x100, BIT(0), 0);
static SUNXI_CCU_GATE(dwam_csi0_cwk,	"dwam-csi0",	"dwam",
		      0x100, BIT(1), 0);
static SUNXI_CCU_GATE(dwam_csi1_cwk,	"dwam-csi1",	"dwam",
		      0x100, BIT(2), 0);
static SUNXI_CCU_GATE(dwam_ts_cwk,	"dwam-ts",	"dwam",
		      0x100, BIT(3), 0);
static SUNXI_CCU_GATE(dwam_tvd_cwk,	"dwam-tvd",	"dwam",
		      0x100, BIT(4), 0);
static SUNXI_CCU_GATE(dwam_mp_cwk,	"dwam-mp",	"dwam",
		      0x100, BIT(5), 0);
static SUNXI_CCU_GATE(dwam_deintewwace_cwk,	"dwam-deintewwace",	"dwam",
		      0x100, BIT(6), 0);

static const chaw * const de_pawents[] = { "pww-pewiph0-2x", "pww-de" };
static SUNXI_CCU_M_WITH_MUX_GATE(de_cwk, "de", de_pawents,
				 0x104, 0, 4, 24, 3, BIT(31),
				 CWK_SET_WATE_PAWENT);
static SUNXI_CCU_M_WITH_MUX_GATE(mp_cwk, "mp", de_pawents,
				 0x108, 0, 4, 24, 3, BIT(31), 0);

static const chaw * const tcon_pawents[] = { "pww-video0", "pww-video1",
					     "pww-video0-2x", "pww-video1-2x",
					     "pww-mipi" };
static SUNXI_CCU_MUX_WITH_GATE(tcon_wcd0_cwk, "tcon-wcd0", tcon_pawents,
			       0x110, 24, 3, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_MUX_WITH_GATE(tcon_wcd1_cwk, "tcon-wcd1", tcon_pawents,
			       0x114, 24, 3, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_M_WITH_MUX_GATE(tcon_tv0_cwk, "tcon-tv0", tcon_pawents,
				 0x118, 0, 4, 24, 3, BIT(31),
				 CWK_SET_WATE_PAWENT);
static SUNXI_CCU_M_WITH_MUX_GATE(tcon_tv1_cwk, "tcon-tv1", tcon_pawents,
				 0x11c, 0, 4, 24, 3, BIT(31),
				 CWK_SET_WATE_PAWENT);

static const chaw * const deintewwace_pawents[] = { "pww-pewiph0",
						    "pww-pewiph1" };
static SUNXI_CCU_M_WITH_MUX_GATE(deintewwace_cwk, "deintewwace",
				 deintewwace_pawents, 0x124, 0, 4, 24, 3,
				 BIT(31), 0);

static const chaw * const csi_mcwk_pawents[] = { "osc24M", "pww-video1",
						 "pww-pewiph1" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi1_mcwk_cwk, "csi1-mcwk", csi_mcwk_pawents,
				 0x130, 0, 5, 8, 3, BIT(15), 0);

static const chaw * const csi_scwk_pawents[] = { "pww-pewiph0", "pww-pewiph1" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi_scwk_cwk, "csi-scwk", csi_scwk_pawents,
				 0x134, 16, 4, 24, 3, BIT(31), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(csi0_mcwk_cwk, "csi0-mcwk", csi_mcwk_pawents,
				 0x134, 0, 5, 8, 3, BIT(15), 0);

static SUNXI_CCU_M_WITH_GATE(ve_cwk, "ve", "pww-ve",
			     0x13c, 16, 3, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(codec_cwk,	"codec",	"pww-audio",
		      0x140, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_GATE(avs_cwk,		"avs",		"osc24M",
		      0x144, BIT(31), 0);

static const chaw * const hdmi_pawents[] = { "pww-video0", "pww-video1" };
static SUNXI_CCU_M_WITH_MUX_GATE(hdmi_cwk, "hdmi", hdmi_pawents,
				 0x150, 0, 4, 24, 2, BIT(31),
				 CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(hdmi_swow_cwk,	"hdmi-swow",	"osc24M",
		      0x154, BIT(31), 0);

/*
 * In the SoC's usew manuaw, the P factow is mentioned, but not used in
 * the fwequency fowmuwa.
 *
 * Hewe the factow is incwuded, accowding to the BSP kewnew souwce,
 * which contains the P factow of this cwock.
 */
static const chaw * const mbus_pawents[] = { "osc24M", "pww-pewiph0-2x",
					     "pww-ddw0" };
static SUNXI_CCU_MP_WITH_MUX_GATE(mbus_cwk, "mbus", mbus_pawents, 0x15c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  CWK_IS_CWITICAW);

static const chaw * const dsi_dphy_pawents[] = { "pww-video0", "pww-video1",
						 "pww-pewiph0" };
static SUNXI_CCU_M_WITH_MUX_GATE(dsi_dphy_cwk, "dsi-dphy", dsi_dphy_pawents,
				 0x168, 0, 4, 8, 2, BIT(15), 0);

static SUNXI_CCU_M_WITH_MUX_GATE(tve0_cwk, "tve0", tcon_pawents,
				 0x180, 0, 4, 24, 3, BIT(31), 0);
static SUNXI_CCU_M_WITH_MUX_GATE(tve1_cwk, "tve1", tcon_pawents,
				 0x184, 0, 4, 24, 3, BIT(31), 0);

static const chaw * const tvd_pawents[] = { "pww-video0", "pww-video1",
					    "pww-video0-2x", "pww-video1-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(tvd0_cwk, "tvd0", tvd_pawents,
				 0x188, 0, 4, 24, 3, BIT(31), 0);
static SUNXI_CCU_M_WITH_MUX_GATE(tvd1_cwk, "tvd1", tvd_pawents,
				 0x18c, 0, 4, 24, 3, BIT(31), 0);
static SUNXI_CCU_M_WITH_MUX_GATE(tvd2_cwk, "tvd2", tvd_pawents,
				 0x190, 0, 4, 24, 3, BIT(31), 0);
static SUNXI_CCU_M_WITH_MUX_GATE(tvd3_cwk, "tvd3", tvd_pawents,
				 0x194, 0, 4, 24, 3, BIT(31), 0);

static SUNXI_CCU_M_WITH_GATE(gpu_cwk, "gpu", "pww-gpu",
			     0x1a0, 0, 3, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw * const out_pawents[] = { "osc24M", "osc32k", "osc24M" };
static const stwuct ccu_mux_fixed_pwediv out_pwedivs[] = {
	{ .index = 0, .div = 750, },
};

static stwuct ccu_mp outa_cwk = {
	.enabwe	= BIT(31),
	.m	= _SUNXI_CCU_DIV(8, 5),
	.p	= _SUNXI_CCU_DIV(20, 2),
	.mux	= {
		.shift		= 24,
		.width		= 2,
		.fixed_pwedivs	= out_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(out_pwedivs),
	},
	.common	= {
		.weg		= 0x1f0,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("outa", out_pawents,
						      &ccu_mp_ops,
						      CWK_SET_WATE_PAWENT),
	}
};

static stwuct ccu_mp outb_cwk = {
	.enabwe	= BIT(31),
	.m	= _SUNXI_CCU_DIV(8, 5),
	.p	= _SUNXI_CCU_DIV(20, 2),
	.mux	= {
		.shift		= 24,
		.width		= 2,
		.fixed_pwedivs	= out_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(out_pwedivs),
	},
	.common	= {
		.weg		= 0x1f4,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("outb", out_pawents,
						      &ccu_mp_ops,
						      CWK_SET_WATE_PAWENT),
	}
};

static stwuct ccu_common *sun8i_w40_ccu_cwks[] = {
	&pww_cpu_cwk.common,
	&pww_audio_base_cwk.common,
	&pww_video0_cwk.common,
	&pww_ve_cwk.common,
	&pww_ddw0_cwk.common,
	&pww_pewiph0_cwk.common,
	&pww_pewiph0_sata_cwk.common,
	&pww_pewiph1_cwk.common,
	&pww_video1_cwk.common,
	&pww_sata_cwk.common,
	&pww_sata_out_cwk.common,
	&pww_gpu_cwk.common,
	&pww_mipi_cwk.common,
	&pww_de_cwk.common,
	&pww_ddw1_cwk.common,
	&cpu_cwk.common,
	&axi_cwk.common,
	&ahb1_cwk.common,
	&apb1_cwk.common,
	&apb2_cwk.common,
	&bus_mipi_dsi_cwk.common,
	&bus_ce_cwk.common,
	&bus_dma_cwk.common,
	&bus_mmc0_cwk.common,
	&bus_mmc1_cwk.common,
	&bus_mmc2_cwk.common,
	&bus_mmc3_cwk.common,
	&bus_nand_cwk.common,
	&bus_dwam_cwk.common,
	&bus_emac_cwk.common,
	&bus_ts_cwk.common,
	&bus_hstimew_cwk.common,
	&bus_spi0_cwk.common,
	&bus_spi1_cwk.common,
	&bus_spi2_cwk.common,
	&bus_spi3_cwk.common,
	&bus_sata_cwk.common,
	&bus_otg_cwk.common,
	&bus_ehci0_cwk.common,
	&bus_ehci1_cwk.common,
	&bus_ehci2_cwk.common,
	&bus_ohci0_cwk.common,
	&bus_ohci1_cwk.common,
	&bus_ohci2_cwk.common,
	&bus_ve_cwk.common,
	&bus_mp_cwk.common,
	&bus_deintewwace_cwk.common,
	&bus_csi0_cwk.common,
	&bus_csi1_cwk.common,
	&bus_hdmi0_cwk.common,
	&bus_hdmi1_cwk.common,
	&bus_de_cwk.common,
	&bus_tve0_cwk.common,
	&bus_tve1_cwk.common,
	&bus_tve_top_cwk.common,
	&bus_gmac_cwk.common,
	&bus_gpu_cwk.common,
	&bus_tvd0_cwk.common,
	&bus_tvd1_cwk.common,
	&bus_tvd2_cwk.common,
	&bus_tvd3_cwk.common,
	&bus_tvd_top_cwk.common,
	&bus_tcon_wcd0_cwk.common,
	&bus_tcon_wcd1_cwk.common,
	&bus_tcon_tv0_cwk.common,
	&bus_tcon_tv1_cwk.common,
	&bus_tcon_top_cwk.common,
	&bus_codec_cwk.common,
	&bus_spdif_cwk.common,
	&bus_ac97_cwk.common,
	&bus_pio_cwk.common,
	&bus_iw0_cwk.common,
	&bus_iw1_cwk.common,
	&bus_ths_cwk.common,
	&bus_keypad_cwk.common,
	&bus_i2s0_cwk.common,
	&bus_i2s1_cwk.common,
	&bus_i2s2_cwk.common,
	&bus_i2c0_cwk.common,
	&bus_i2c1_cwk.common,
	&bus_i2c2_cwk.common,
	&bus_i2c3_cwk.common,
	&bus_can_cwk.common,
	&bus_scw_cwk.common,
	&bus_ps20_cwk.common,
	&bus_ps21_cwk.common,
	&bus_i2c4_cwk.common,
	&bus_uawt0_cwk.common,
	&bus_uawt1_cwk.common,
	&bus_uawt2_cwk.common,
	&bus_uawt3_cwk.common,
	&bus_uawt4_cwk.common,
	&bus_uawt5_cwk.common,
	&bus_uawt6_cwk.common,
	&bus_uawt7_cwk.common,
	&bus_dbg_cwk.common,
	&ths_cwk.common,
	&nand_cwk.common,
	&mmc0_cwk.common,
	&mmc1_cwk.common,
	&mmc2_cwk.common,
	&mmc3_cwk.common,
	&ts_cwk.common,
	&ce_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&spi2_cwk.common,
	&spi3_cwk.common,
	&i2s0_cwk.common,
	&i2s1_cwk.common,
	&i2s2_cwk.common,
	&ac97_cwk.common,
	&spdif_cwk.common,
	&keypad_cwk.common,
	&sata_cwk.common,
	&usb_phy0_cwk.common,
	&usb_phy1_cwk.common,
	&usb_phy2_cwk.common,
	&usb_ohci0_cwk.common,
	&usb_ohci1_cwk.common,
	&usb_ohci2_cwk.common,
	&iw0_cwk.common,
	&iw1_cwk.common,
	&dwam_cwk.common,
	&dwam_ve_cwk.common,
	&dwam_csi0_cwk.common,
	&dwam_csi1_cwk.common,
	&dwam_ts_cwk.common,
	&dwam_tvd_cwk.common,
	&dwam_mp_cwk.common,
	&dwam_deintewwace_cwk.common,
	&de_cwk.common,
	&mp_cwk.common,
	&tcon_wcd0_cwk.common,
	&tcon_wcd1_cwk.common,
	&tcon_tv0_cwk.common,
	&tcon_tv1_cwk.common,
	&deintewwace_cwk.common,
	&csi1_mcwk_cwk.common,
	&csi_scwk_cwk.common,
	&csi0_mcwk_cwk.common,
	&ve_cwk.common,
	&codec_cwk.common,
	&avs_cwk.common,
	&hdmi_cwk.common,
	&hdmi_swow_cwk.common,
	&mbus_cwk.common,
	&dsi_dphy_cwk.common,
	&tve0_cwk.common,
	&tve1_cwk.common,
	&tvd0_cwk.common,
	&tvd1_cwk.common,
	&tvd2_cwk.common,
	&tvd3_cwk.common,
	&gpu_cwk.common,
	&outa_cwk.common,
	&outb_cwk.common,
};

/* Fixed Factow cwocks */
static CWK_FIXED_FACTOW_FW_NAME(osc12M_cwk, "osc12M", "hosc", 2, 1, 0);

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
static CWK_FIXED_FACTOW_HW(pww_pewiph0_2x_cwk, "pww-pewiph0-2x",
			   &pww_pewiph0_cwk.common.hw,
			   1, 2, 0);
static CWK_FIXED_FACTOW_HW(pww_pewiph1_2x_cwk, "pww-pewiph1-2x",
			   &pww_pewiph1_cwk.common.hw,
			   1, 2, 0);
static CWK_FIXED_FACTOW_HW(pww_video0_2x_cwk, "pww-video0-2x",
			   &pww_video0_cwk.common.hw,
			   1, 2, 0);
static CWK_FIXED_FACTOW_HW(pww_video1_2x_cwk, "pww-video1-2x",
			   &pww_video1_cwk.common.hw,
			   1, 2, 0);

static stwuct cwk_hw_oneceww_data sun8i_w40_hw_cwks = {
	.hws	= {
		[CWK_OSC_12M]		= &osc12M_cwk.hw,
		[CWK_PWW_CPU]		= &pww_cpu_cwk.common.hw,
		[CWK_PWW_AUDIO_BASE]	= &pww_audio_base_cwk.common.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.hw,
		[CWK_PWW_AUDIO_2X]	= &pww_audio_2x_cwk.hw,
		[CWK_PWW_AUDIO_4X]	= &pww_audio_4x_cwk.hw,
		[CWK_PWW_AUDIO_8X]	= &pww_audio_8x_cwk.hw,
		[CWK_PWW_VIDEO0]	= &pww_video0_cwk.common.hw,
		[CWK_PWW_VIDEO0_2X]	= &pww_video0_2x_cwk.hw,
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DDW0]		= &pww_ddw0_cwk.common.hw,
		[CWK_PWW_PEWIPH0]	= &pww_pewiph0_cwk.common.hw,
		[CWK_PWW_PEWIPH0_SATA]	= &pww_pewiph0_sata_cwk.common.hw,
		[CWK_PWW_PEWIPH0_2X]	= &pww_pewiph0_2x_cwk.hw,
		[CWK_PWW_PEWIPH1]	= &pww_pewiph1_cwk.common.hw,
		[CWK_PWW_PEWIPH1_2X]	= &pww_pewiph1_2x_cwk.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_PWW_VIDEO1_2X]	= &pww_video1_2x_cwk.hw,
		[CWK_PWW_SATA]		= &pww_sata_cwk.common.hw,
		[CWK_PWW_SATA_OUT]	= &pww_sata_out_cwk.common.hw,
		[CWK_PWW_GPU]		= &pww_gpu_cwk.common.hw,
		[CWK_PWW_MIPI]		= &pww_mipi_cwk.common.hw,
		[CWK_PWW_DE]		= &pww_de_cwk.common.hw,
		[CWK_PWW_DDW1]		= &pww_ddw1_cwk.common.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_AHB1]		= &ahb1_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_APB2]		= &apb2_cwk.common.hw,
		[CWK_BUS_MIPI_DSI]	= &bus_mipi_dsi_cwk.common.hw,
		[CWK_BUS_CE]		= &bus_ce_cwk.common.hw,
		[CWK_BUS_DMA]		= &bus_dma_cwk.common.hw,
		[CWK_BUS_MMC0]		= &bus_mmc0_cwk.common.hw,
		[CWK_BUS_MMC1]		= &bus_mmc1_cwk.common.hw,
		[CWK_BUS_MMC2]		= &bus_mmc2_cwk.common.hw,
		[CWK_BUS_MMC3]		= &bus_mmc3_cwk.common.hw,
		[CWK_BUS_NAND]		= &bus_nand_cwk.common.hw,
		[CWK_BUS_DWAM]		= &bus_dwam_cwk.common.hw,
		[CWK_BUS_EMAC]		= &bus_emac_cwk.common.hw,
		[CWK_BUS_TS]		= &bus_ts_cwk.common.hw,
		[CWK_BUS_HSTIMEW]	= &bus_hstimew_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_SPI1]		= &bus_spi1_cwk.common.hw,
		[CWK_BUS_SPI2]		= &bus_spi2_cwk.common.hw,
		[CWK_BUS_SPI3]		= &bus_spi3_cwk.common.hw,
		[CWK_BUS_SATA]		= &bus_sata_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_BUS_EHCI0]		= &bus_ehci0_cwk.common.hw,
		[CWK_BUS_EHCI1]		= &bus_ehci1_cwk.common.hw,
		[CWK_BUS_EHCI2]		= &bus_ehci2_cwk.common.hw,
		[CWK_BUS_OHCI0]		= &bus_ohci0_cwk.common.hw,
		[CWK_BUS_OHCI1]		= &bus_ohci1_cwk.common.hw,
		[CWK_BUS_OHCI2]		= &bus_ohci2_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_BUS_MP]		= &bus_mp_cwk.common.hw,
		[CWK_BUS_DEINTEWWACE]	= &bus_deintewwace_cwk.common.hw,
		[CWK_BUS_CSI0]		= &bus_csi0_cwk.common.hw,
		[CWK_BUS_CSI1]		= &bus_csi1_cwk.common.hw,
		[CWK_BUS_HDMI0]		= &bus_hdmi0_cwk.common.hw,
		[CWK_BUS_HDMI1]		= &bus_hdmi1_cwk.common.hw,
		[CWK_BUS_DE]		= &bus_de_cwk.common.hw,
		[CWK_BUS_TVE0]		= &bus_tve0_cwk.common.hw,
		[CWK_BUS_TVE1]		= &bus_tve1_cwk.common.hw,
		[CWK_BUS_TVE_TOP]	= &bus_tve_top_cwk.common.hw,
		[CWK_BUS_GMAC]		= &bus_gmac_cwk.common.hw,
		[CWK_BUS_GPU]		= &bus_gpu_cwk.common.hw,
		[CWK_BUS_TVD0]		= &bus_tvd0_cwk.common.hw,
		[CWK_BUS_TVD1]		= &bus_tvd1_cwk.common.hw,
		[CWK_BUS_TVD2]		= &bus_tvd2_cwk.common.hw,
		[CWK_BUS_TVD3]		= &bus_tvd3_cwk.common.hw,
		[CWK_BUS_TVD_TOP]	= &bus_tvd_top_cwk.common.hw,
		[CWK_BUS_TCON_WCD0]	= &bus_tcon_wcd0_cwk.common.hw,
		[CWK_BUS_TCON_WCD1]	= &bus_tcon_wcd1_cwk.common.hw,
		[CWK_BUS_TCON_TV0]	= &bus_tcon_tv0_cwk.common.hw,
		[CWK_BUS_TCON_TV1]	= &bus_tcon_tv1_cwk.common.hw,
		[CWK_BUS_TCON_TOP]	= &bus_tcon_top_cwk.common.hw,
		[CWK_BUS_CODEC]		= &bus_codec_cwk.common.hw,
		[CWK_BUS_SPDIF]		= &bus_spdif_cwk.common.hw,
		[CWK_BUS_AC97]		= &bus_ac97_cwk.common.hw,
		[CWK_BUS_PIO]		= &bus_pio_cwk.common.hw,
		[CWK_BUS_IW0]		= &bus_iw0_cwk.common.hw,
		[CWK_BUS_IW1]		= &bus_iw1_cwk.common.hw,
		[CWK_BUS_THS]		= &bus_ths_cwk.common.hw,
		[CWK_BUS_KEYPAD]	= &bus_keypad_cwk.common.hw,
		[CWK_BUS_I2S0]		= &bus_i2s0_cwk.common.hw,
		[CWK_BUS_I2S1]		= &bus_i2s1_cwk.common.hw,
		[CWK_BUS_I2S2]		= &bus_i2s2_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_I2C2]		= &bus_i2c2_cwk.common.hw,
		[CWK_BUS_I2C3]		= &bus_i2c3_cwk.common.hw,
		[CWK_BUS_CAN]		= &bus_can_cwk.common.hw,
		[CWK_BUS_SCW]		= &bus_scw_cwk.common.hw,
		[CWK_BUS_PS20]		= &bus_ps20_cwk.common.hw,
		[CWK_BUS_PS21]		= &bus_ps21_cwk.common.hw,
		[CWK_BUS_I2C4]		= &bus_i2c4_cwk.common.hw,
		[CWK_BUS_UAWT0]		= &bus_uawt0_cwk.common.hw,
		[CWK_BUS_UAWT1]		= &bus_uawt1_cwk.common.hw,
		[CWK_BUS_UAWT2]		= &bus_uawt2_cwk.common.hw,
		[CWK_BUS_UAWT3]		= &bus_uawt3_cwk.common.hw,
		[CWK_BUS_UAWT4]		= &bus_uawt4_cwk.common.hw,
		[CWK_BUS_UAWT5]		= &bus_uawt5_cwk.common.hw,
		[CWK_BUS_UAWT6]		= &bus_uawt6_cwk.common.hw,
		[CWK_BUS_UAWT7]		= &bus_uawt7_cwk.common.hw,
		[CWK_BUS_DBG]		= &bus_dbg_cwk.common.hw,
		[CWK_THS]		= &ths_cwk.common.hw,
		[CWK_NAND]		= &nand_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_MMC3]		= &mmc3_cwk.common.hw,
		[CWK_TS]		= &ts_cwk.common.hw,
		[CWK_CE]		= &ce_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_SPI3]		= &spi3_cwk.common.hw,
		[CWK_I2S0]		= &i2s0_cwk.common.hw,
		[CWK_I2S1]		= &i2s1_cwk.common.hw,
		[CWK_I2S2]		= &i2s2_cwk.common.hw,
		[CWK_AC97]		= &ac97_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_KEYPAD]		= &keypad_cwk.common.hw,
		[CWK_SATA]		= &sata_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_PHY1]		= &usb_phy1_cwk.common.hw,
		[CWK_USB_PHY2]		= &usb_phy2_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_USB_OHCI1]		= &usb_ohci1_cwk.common.hw,
		[CWK_USB_OHCI2]		= &usb_ohci2_cwk.common.hw,
		[CWK_IW0]		= &iw0_cwk.common.hw,
		[CWK_IW1]		= &iw1_cwk.common.hw,
		[CWK_DWAM]		= &dwam_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI0]		= &dwam_csi0_cwk.common.hw,
		[CWK_DWAM_CSI1]		= &dwam_csi1_cwk.common.hw,
		[CWK_DWAM_TS]		= &dwam_ts_cwk.common.hw,
		[CWK_DWAM_TVD]		= &dwam_tvd_cwk.common.hw,
		[CWK_DWAM_MP]		= &dwam_mp_cwk.common.hw,
		[CWK_DWAM_DEINTEWWACE]	= &dwam_deintewwace_cwk.common.hw,
		[CWK_DE]		= &de_cwk.common.hw,
		[CWK_MP]		= &mp_cwk.common.hw,
		[CWK_TCON_WCD0]		= &tcon_wcd0_cwk.common.hw,
		[CWK_TCON_WCD1]		= &tcon_wcd1_cwk.common.hw,
		[CWK_TCON_TV0]		= &tcon_tv0_cwk.common.hw,
		[CWK_TCON_TV1]		= &tcon_tv1_cwk.common.hw,
		[CWK_DEINTEWWACE]	= &deintewwace_cwk.common.hw,
		[CWK_CSI1_MCWK]		= &csi1_mcwk_cwk.common.hw,
		[CWK_CSI_SCWK]		= &csi_scwk_cwk.common.hw,
		[CWK_CSI0_MCWK]		= &csi0_mcwk_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_CODEC]		= &codec_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_HDMI]		= &hdmi_cwk.common.hw,
		[CWK_HDMI_SWOW]		= &hdmi_swow_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_DSI_DPHY]		= &dsi_dphy_cwk.common.hw,
		[CWK_TVE0]		= &tve0_cwk.common.hw,
		[CWK_TVE1]		= &tve1_cwk.common.hw,
		[CWK_TVD0]		= &tvd0_cwk.common.hw,
		[CWK_TVD1]		= &tvd1_cwk.common.hw,
		[CWK_TVD2]		= &tvd2_cwk.common.hw,
		[CWK_TVD3]		= &tvd3_cwk.common.hw,
		[CWK_GPU]		= &gpu_cwk.common.hw,
		[CWK_OUTA]		= &outa_cwk.common.hw,
		[CWK_OUTB]		= &outb_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct ccu_weset_map sun8i_w40_ccu_wesets[] = {
	[WST_USB_PHY0]		=  { 0x0cc, BIT(0) },
	[WST_USB_PHY1]		=  { 0x0cc, BIT(1) },
	[WST_USB_PHY2]		=  { 0x0cc, BIT(2) },

	[WST_DWAM]		=  { 0x0f4, BIT(31) },
	[WST_MBUS]		=  { 0x0fc, BIT(31) },

	[WST_BUS_MIPI_DSI]	=  { 0x2c0, BIT(1) },
	[WST_BUS_CE]		=  { 0x2c0, BIT(5) },
	[WST_BUS_DMA]		=  { 0x2c0, BIT(6) },
	[WST_BUS_MMC0]		=  { 0x2c0, BIT(8) },
	[WST_BUS_MMC1]		=  { 0x2c0, BIT(9) },
	[WST_BUS_MMC2]		=  { 0x2c0, BIT(10) },
	[WST_BUS_MMC3]		=  { 0x2c0, BIT(11) },
	[WST_BUS_NAND]		=  { 0x2c0, BIT(13) },
	[WST_BUS_DWAM]		=  { 0x2c0, BIT(14) },
	[WST_BUS_EMAC]		=  { 0x2c0, BIT(17) },
	[WST_BUS_TS]		=  { 0x2c0, BIT(18) },
	[WST_BUS_HSTIMEW]	=  { 0x2c0, BIT(19) },
	[WST_BUS_SPI0]		=  { 0x2c0, BIT(20) },
	[WST_BUS_SPI1]		=  { 0x2c0, BIT(21) },
	[WST_BUS_SPI2]		=  { 0x2c0, BIT(22) },
	[WST_BUS_SPI3]		=  { 0x2c0, BIT(23) },
	[WST_BUS_SATA]		=  { 0x2c0, BIT(24) },
	[WST_BUS_OTG]		=  { 0x2c0, BIT(25) },
	[WST_BUS_EHCI0]		=  { 0x2c0, BIT(26) },
	[WST_BUS_EHCI1]		=  { 0x2c0, BIT(27) },
	[WST_BUS_EHCI2]		=  { 0x2c0, BIT(28) },
	[WST_BUS_OHCI0]		=  { 0x2c0, BIT(29) },
	[WST_BUS_OHCI1]		=  { 0x2c0, BIT(30) },
	[WST_BUS_OHCI2]		=  { 0x2c0, BIT(31) },

	[WST_BUS_VE]		=  { 0x2c4, BIT(0) },
	[WST_BUS_MP]		=  { 0x2c4, BIT(2) },
	[WST_BUS_DEINTEWWACE]	=  { 0x2c4, BIT(5) },
	[WST_BUS_CSI0]		=  { 0x2c4, BIT(8) },
	[WST_BUS_CSI1]		=  { 0x2c4, BIT(9) },
	[WST_BUS_HDMI0]		=  { 0x2c4, BIT(10) },
	[WST_BUS_HDMI1]		=  { 0x2c4, BIT(11) },
	[WST_BUS_DE]		=  { 0x2c4, BIT(12) },
	[WST_BUS_TVE0]		=  { 0x2c4, BIT(13) },
	[WST_BUS_TVE1]		=  { 0x2c4, BIT(14) },
	[WST_BUS_TVE_TOP]	=  { 0x2c4, BIT(15) },
	[WST_BUS_GMAC]		=  { 0x2c4, BIT(17) },
	[WST_BUS_GPU]		=  { 0x2c4, BIT(20) },
	[WST_BUS_TVD0]		=  { 0x2c4, BIT(21) },
	[WST_BUS_TVD1]		=  { 0x2c4, BIT(22) },
	[WST_BUS_TVD2]		=  { 0x2c4, BIT(23) },
	[WST_BUS_TVD3]		=  { 0x2c4, BIT(24) },
	[WST_BUS_TVD_TOP]	=  { 0x2c4, BIT(25) },
	[WST_BUS_TCON_WCD0]	=  { 0x2c4, BIT(26) },
	[WST_BUS_TCON_WCD1]	=  { 0x2c4, BIT(27) },
	[WST_BUS_TCON_TV0]	=  { 0x2c4, BIT(28) },
	[WST_BUS_TCON_TV1]	=  { 0x2c4, BIT(29) },
	[WST_BUS_TCON_TOP]	=  { 0x2c4, BIT(30) },
	[WST_BUS_DBG]		=  { 0x2c4, BIT(31) },

	[WST_BUS_WVDS]		=  { 0x2c8, BIT(0) },

	[WST_BUS_CODEC]		=  { 0x2d0, BIT(0) },
	[WST_BUS_SPDIF]		=  { 0x2d0, BIT(1) },
	[WST_BUS_AC97]		=  { 0x2d0, BIT(2) },
	[WST_BUS_IW0]		=  { 0x2d0, BIT(6) },
	[WST_BUS_IW1]		=  { 0x2d0, BIT(7) },
	[WST_BUS_THS]		=  { 0x2d0, BIT(8) },
	[WST_BUS_KEYPAD]	=  { 0x2d0, BIT(10) },
	[WST_BUS_I2S0]		=  { 0x2d0, BIT(12) },
	[WST_BUS_I2S1]		=  { 0x2d0, BIT(13) },
	[WST_BUS_I2S2]		=  { 0x2d0, BIT(14) },

	[WST_BUS_I2C0]		=  { 0x2d8, BIT(0) },
	[WST_BUS_I2C1]		=  { 0x2d8, BIT(1) },
	[WST_BUS_I2C2]		=  { 0x2d8, BIT(2) },
	[WST_BUS_I2C3]		=  { 0x2d8, BIT(3) },
	[WST_BUS_CAN]		=  { 0x2d8, BIT(4) },
	[WST_BUS_SCW]		=  { 0x2d8, BIT(5) },
	[WST_BUS_PS20]		=  { 0x2d8, BIT(6) },
	[WST_BUS_PS21]		=  { 0x2d8, BIT(7) },
	[WST_BUS_I2C4]		=  { 0x2d8, BIT(15) },
	[WST_BUS_UAWT0]		=  { 0x2d8, BIT(16) },
	[WST_BUS_UAWT1]		=  { 0x2d8, BIT(17) },
	[WST_BUS_UAWT2]		=  { 0x2d8, BIT(18) },
	[WST_BUS_UAWT3]		=  { 0x2d8, BIT(19) },
	[WST_BUS_UAWT4]		=  { 0x2d8, BIT(20) },
	[WST_BUS_UAWT5]		=  { 0x2d8, BIT(21) },
	[WST_BUS_UAWT6]		=  { 0x2d8, BIT(22) },
	[WST_BUS_UAWT7]		=  { 0x2d8, BIT(23) },
};

static const stwuct sunxi_ccu_desc sun8i_w40_ccu_desc = {
	.ccu_cwks	= sun8i_w40_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun8i_w40_ccu_cwks),

	.hw_cwks	= &sun8i_w40_hw_cwks,

	.wesets		= sun8i_w40_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun8i_w40_ccu_wesets),
};

static stwuct ccu_pww_nb sun8i_w40_pww_cpu_nb = {
	.common	= &pww_cpu_cwk.common,
	/* copy fwom pww_cpu_cwk */
	.enabwe	= BIT(31),
	.wock	= BIT(28),
};

static stwuct ccu_mux_nb sun8i_w40_cpu_nb = {
	.common		= &cpu_cwk.common,
	.cm		= &cpu_cwk.mux,
	.deway_us	= 1, /* > 8 cwock cycwes at 24 MHz */
	.bypass_index	= 1, /* index of 24 MHz osciwwatow */
};

/*
 * Add a wegmap fow the GMAC dwivew (dwmac-sun8i) to access the
 * GMAC configuwation wegistew.
 * Onwy this wegistew is awwowed to be wwitten, in owdew to
 * pwevent ovewwiding cwiticaw cwock configuwation.
 */

#define SUN8I_W40_GMAC_CFG_WEG 0x164
static boow sun8i_w40_ccu_wegmap_accessibwe_weg(stwuct device *dev,
						unsigned int weg)
{
	if (weg == SUN8I_W40_GMAC_CFG_WEG)
		wetuwn twue;
	wetuwn fawse;
}

static stwuct wegmap_config sun8i_w40_ccu_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= 0x320, /* PWW_WOCK_CTWW_WEG */

	/* othew devices have no business accessing othew wegistews */
	.weadabwe_weg	= sun8i_w40_ccu_wegmap_accessibwe_weg,
	.wwiteabwe_weg	= sun8i_w40_ccu_wegmap_accessibwe_weg,
};

#define SUN8I_W40_SYS_32K_CWK_WEG 0x310
#define SUN8I_W40_SYS_32K_CWK_KEY (0x16AA << 16)

static int sun8i_w40_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	void __iomem *weg;
	u32 vaw;
	int wet;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	/* Fowce the PWW-Audio-1x dividew to 1 */
	vaw = weadw(weg + SUN8I_W40_PWW_AUDIO_WEG);
	vaw &= ~GENMASK(19, 16);
	wwitew(vaw | (0 << 16), weg + SUN8I_W40_PWW_AUDIO_WEG);

	/* Fowce PWW-MIPI to MIPI mode */
	vaw = weadw(weg + SUN8I_W40_PWW_MIPI_WEG);
	vaw &= ~BIT(16);
	wwitew(vaw, weg + SUN8I_W40_PWW_MIPI_WEG);

	/* Fowce OHCI 12M pawent to 12M divided fwom 48M */
	vaw = weadw(weg + SUN8I_W40_USB_CWK_WEG);
	vaw &= ~GENMASK(25, 20);
	wwitew(vaw, weg + SUN8I_W40_USB_CWK_WEG);

	/*
	 * Fowce SYS 32k (othewwise known as WOSC thwoughout the CCU)
	 * cwock pawent to WOSC output fwom WTC moduwe instead of the
	 * CCU's intewnaw WC osciwwatow divided output.
	 */
	wwitew(SUN8I_W40_SYS_32K_CWK_KEY | BIT(8),
	       weg + SUN8I_W40_SYS_32K_CWK_WEG);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, weg,
				       &sun8i_w40_ccu_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = devm_sunxi_ccu_pwobe(&pdev->dev, weg, &sun8i_w40_ccu_desc);
	if (wet)
		wetuwn wet;

	/* Gate then ungate PWW CPU aftew any wate changes */
	ccu_pww_notifiew_wegistew(&sun8i_w40_pww_cpu_nb);

	/* Wepawent CPU duwing PWW CPU wate changes */
	ccu_mux_notifiew_wegistew(pww_cpu_cwk.common.hw.cwk,
				  &sun8i_w40_cpu_nb);

	wetuwn 0;
}

static const stwuct of_device_id sun8i_w40_ccu_ids[] = {
	{ .compatibwe = "awwwinnew,sun8i-w40-ccu" },
	{ }
};

static stwuct pwatfowm_dwivew sun8i_w40_ccu_dwivew = {
	.pwobe	= sun8i_w40_ccu_pwobe,
	.dwivew	= {
		.name	= "sun8i-w40-ccu",
		.suppwess_bind_attws = twue,
		.of_match_tabwe	= sun8i_w40_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun8i_w40_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
