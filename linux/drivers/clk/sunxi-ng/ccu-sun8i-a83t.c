// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Chen-Yu Tsai. Aww wights wesewved.
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
#incwude "ccu_mux.h"
#incwude "ccu_nkmp.h"
#incwude "ccu_nm.h"
#incwude "ccu_phase.h"

#incwude "ccu-sun8i-a83t.h"

#define CCU_SUN8I_A83T_WOCK_WEG	0x20c

/*
 * The CPU PWWs awe actuawwy NP cwocks, with P being /1 ow /4. Howevew
 * P shouwd onwy be used fow output fwequencies wowew than 228 MHz.
 * Neithew mainwine Winux, U-boot, now the vendow BSPs use these.
 *
 * Fow now we can just modew it as a muwtipwiew cwock, and fowce P to /1.
 */
#define SUN8I_A83T_PWW_C0CPUX_WEG	0x000
#define SUN8I_A83T_PWW_C1CPUX_WEG	0x004

static stwuct ccu_muwt pww_c0cpux_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(0),
	.muwt		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.common		= {
		.weg		= SUN8I_A83T_PWW_C0CPUX_WEG,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-c0cpux", "osc24M",
					      &ccu_muwt_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_muwt pww_c1cpux_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(1),
	.muwt		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.common		= {
		.weg		= SUN8I_A83T_PWW_C1CPUX_WEG,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-c1cpux", "osc24M",
					      &ccu_muwt_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/*
 * The Audio PWW has d1, d2 dividews in addition to the usuaw N, M
 * factows. Since we onwy need 2 fwequencies fwom this PWW: 22.5792 MHz
 * and 24.576 MHz, ignowe them fow now. Enfowce the defauwt fow them,
 * which is d1 = 0, d2 = 1.
 */
#define SUN8I_A83T_PWW_AUDIO_WEG	0x008

/* cwock wates doubwed fow post dividew */
static stwuct ccu_sdm_setting pww_audio_sdm_tabwe[] = {
	{ .wate = 45158400, .pattewn = 0xc00121ff, .m = 29, .n = 54 },
	{ .wate = 49152000, .pattewn = 0xc000e147, .m = 30, .n = 61 },
};

static stwuct ccu_nm pww_audio_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(2),
	.n		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(0, 6),
	.fixed_post_div	= 2,
	.sdm		= _SUNXI_CCU_SDM(pww_audio_sdm_tabwe, BIT(24),
					 0x284, BIT(31)),
	.common		= {
		.weg		= SUN8I_A83T_PWW_AUDIO_WEG,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG |
				  CCU_FEATUWE_FIXED_POSTDIV |
				  CCU_FEATUWE_SIGMA_DEWTA_MOD,
		.hw.init	= CWK_HW_INIT("pww-audio", "osc24M",
					      &ccu_nm_ops, CWK_SET_WATE_UNGATE),
	},
};

/* Some PWWs awe input * N / div1 / P. Modew them as NKMP with no K */
static stwuct ccu_nkmp pww_video0_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(3),
	.n		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 2), /* output dividew */
	.max_wate	= 3000000000UW,
	.common		= {
		.weg		= 0x010,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-video0", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_nkmp pww_ve_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(4),
	.n		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output dividew */
	.common		= {
		.weg		= 0x018,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-ve", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_nkmp pww_ddw_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(5),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output dividew */
	.common		= {
		.weg		= 0x020,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-ddw", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_nkmp pww_pewiph_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(6),
	.n		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output dividew */
	.common		= {
		.weg		= 0x028,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-pewiph", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_nkmp pww_gpu_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(7),
	.n		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output dividew */
	.common		= {
		.weg		= 0x038,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-gpu", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_nkmp pww_hsic_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(8),
	.n		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output dividew */
	.common		= {
		.weg		= 0x044,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-hsic", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_nkmp pww_de_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(9),
	.n		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(18, 1), /* output dividew */
	.common		= {
		.weg		= 0x048,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-de", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static stwuct ccu_nkmp pww_video1_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(10),
	.n		= _SUNXI_CCU_MUWT_OFFSET_MIN_MAX(8, 8, 0, 12, 0),
	.m		= _SUNXI_CCU_DIV(16, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 2), /* extewnaw dividew p */
	.max_wate	= 3000000000UW,
	.common		= {
		.weg		= 0x04c,
		.wock_weg	= CCU_SUN8I_A83T_WOCK_WEG,
		.featuwes	= CCU_FEATUWE_WOCK_WEG,
		.hw.init	= CWK_HW_INIT("pww-video1", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static const chaw * const c0cpux_pawents[] = { "osc24M", "pww-c0cpux" };
static SUNXI_CCU_MUX(c0cpux_cwk, "c0cpux", c0cpux_pawents,
		     0x50, 12, 1, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);

static const chaw * const c1cpux_pawents[] = { "osc24M", "pww-c1cpux" };
static SUNXI_CCU_MUX(c1cpux_cwk, "c1cpux", c1cpux_pawents,
		     0x50, 28, 1, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);

static SUNXI_CCU_M(axi0_cwk, "axi0", "c0cpux", 0x050, 0, 2, 0);
static SUNXI_CCU_M(axi1_cwk, "axi1", "c1cpux", 0x050, 16, 2, 0);

static const chaw * const ahb1_pawents[] = { "osc16M-d512", "osc24M",
					     "pww-pewiph",
					     "pww-pewiph" };
static const stwuct ccu_mux_vaw_pwediv ahb1_pwedivs[] = {
	{ .index = 2, .shift = 6, .width = 2 },
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
		.hw.init	= CWK_HW_INIT_PAWENTS("ahb1",
						      ahb1_pawents,
						      &ccu_div_ops,
						      0),
	},
};

static SUNXI_CCU_M(apb1_cwk, "apb1", "ahb1", 0x054, 8, 2, 0);

static const chaw * const apb2_pawents[] = { "osc16M-d512", "osc24M",
					     "pww-pewiph", "pww-pewiph" };

static SUNXI_CCU_MP_WITH_MUX(apb2_cwk, "apb2", apb2_pawents, 0x058,
			     0, 5,	/* M */
			     16, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static const chaw * const ahb2_pawents[] = { "ahb1", "pww-pewiph" };
static const stwuct ccu_mux_fixed_pwediv ahb2_pwediv = {
	.index = 1, .div = 2
};
static stwuct ccu_mux ahb2_cwk = {
	.mux		= {
		.shift		= 0,
		.width		= 2,
		.fixed_pwedivs	= &ahb2_pwediv,
		.n_pwedivs	= 1,
	},
	.common		= {
		.weg		= 0x05c,
		.hw.init	= CWK_HW_INIT_PAWENTS("ahb2",
						      ahb2_pawents,
						      &ccu_mux_ops,
						      0),
	},
};

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
static SUNXI_CCU_GATE(bus_emac_cwk,	"bus-emac",	"ahb2",
		      0x060, BIT(17), 0);
static SUNXI_CCU_GATE(bus_hstimew_cwk,	"bus-hstimew",	"ahb1",
		      0x060, BIT(19), 0);
static SUNXI_CCU_GATE(bus_spi0_cwk,	"bus-spi0",	"ahb1",
		      0x060, BIT(20), 0);
static SUNXI_CCU_GATE(bus_spi1_cwk,	"bus-spi1",	"ahb1",
		      0x060, BIT(21), 0);
static SUNXI_CCU_GATE(bus_otg_cwk,	"bus-otg",	"ahb1",
		      0x060, BIT(24), 0);
static SUNXI_CCU_GATE(bus_ehci0_cwk,	"bus-ehci0",	"ahb2",
		      0x060, BIT(26), 0);
static SUNXI_CCU_GATE(bus_ehci1_cwk,	"bus-ehci1",	"ahb2",
		      0x060, BIT(27), 0);
static SUNXI_CCU_GATE(bus_ohci0_cwk,	"bus-ohci0",	"ahb2",
		      0x060, BIT(29), 0);

static SUNXI_CCU_GATE(bus_ve_cwk,	"bus-ve",	"ahb1",
		      0x064, BIT(0), 0);
static SUNXI_CCU_GATE(bus_tcon0_cwk,	"bus-tcon0",	"ahb1",
		      0x064, BIT(4), 0);
static SUNXI_CCU_GATE(bus_tcon1_cwk,	"bus-tcon1",	"ahb1",
		      0x064, BIT(5), 0);
static SUNXI_CCU_GATE(bus_csi_cwk,	"bus-csi",	"ahb1",
		      0x064, BIT(8), 0);
static SUNXI_CCU_GATE(bus_hdmi_cwk,	"bus-hdmi",	"ahb1",
		      0x064, BIT(11), 0);
static SUNXI_CCU_GATE(bus_de_cwk,	"bus-de",	"ahb1",
		      0x064, BIT(12), 0);
static SUNXI_CCU_GATE(bus_gpu_cwk,	"bus-gpu",	"ahb1",
		      0x064, BIT(20), 0);
static SUNXI_CCU_GATE(bus_msgbox_cwk,	"bus-msgbox",	"ahb1",
		      0x064, BIT(21), 0);
static SUNXI_CCU_GATE(bus_spinwock_cwk,	"bus-spinwock",	"ahb1",
		      0x064, BIT(22), 0);

static SUNXI_CCU_GATE(bus_spdif_cwk,	"bus-spdif",	"apb1",
		      0x068, BIT(1), 0);
static SUNXI_CCU_GATE(bus_pio_cwk,	"bus-pio",	"apb1",
		      0x068, BIT(5), 0);
static SUNXI_CCU_GATE(bus_i2s0_cwk,	"bus-i2s0",	"apb1",
		      0x068, BIT(12), 0);
static SUNXI_CCU_GATE(bus_i2s1_cwk,	"bus-i2s1",	"apb1",
		      0x068, BIT(13), 0);
static SUNXI_CCU_GATE(bus_i2s2_cwk,	"bus-i2s2",	"apb1",
		      0x068, BIT(14), 0);
static SUNXI_CCU_GATE(bus_tdm_cwk,	"bus-tdm",	"apb1",
		      0x068, BIT(15), 0);

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

static const chaw * const cci400_pawents[] = { "osc24M", "pww-pewiph",
					       "pww-hsic" };
static stwuct ccu_div cci400_cwk = {
	.div		= _SUNXI_CCU_DIV_FWAGS(0, 2, 0),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0x078,
		.hw.init	= CWK_HW_INIT_PAWENTS("cci400",
						      cci400_pawents,
						      &ccu_div_ops,
						      CWK_IS_CWITICAW),
	},
};

static const chaw * const mod0_defauwt_pawents[] = { "osc24M", "pww-pewiph" };

static SUNXI_CCU_MP_WITH_MUX_GATE(nand_cwk, "nand", mod0_defauwt_pawents,
				  0x080,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc0_cwk, "mmc0", mod0_defauwt_pawents,
				  0x088,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_PHASE(mmc0_sampwe_cwk, "mmc0-sampwe", "mmc0",
		       0x088, 20, 3, 0);
static SUNXI_CCU_PHASE(mmc0_output_cwk, "mmc0-output", "mmc0",
		       0x088, 8, 3, 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(mmc1_cwk, "mmc1", mod0_defauwt_pawents,
				  0x08c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_PHASE(mmc1_sampwe_cwk, "mmc1-sampwe", "mmc1",
		       0x08c, 20, 3, 0);
static SUNXI_CCU_PHASE(mmc1_output_cwk, "mmc1-output", "mmc1",
		       0x08c, 8, 3, 0);

static SUNXI_CCU_MP_MMC_WITH_MUX_GATE(mmc2_cwk, "mmc2", mod0_defauwt_pawents,
				      0x090, 0);

static SUNXI_CCU_PHASE(mmc2_sampwe_cwk, "mmc2-sampwe", "mmc2",
		       0x090, 20, 3, 0);
static SUNXI_CCU_PHASE(mmc2_output_cwk, "mmc2-output", "mmc2",
		       0x090, 8, 3, 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(ss_cwk, "ss", mod0_defauwt_pawents,
				  0x09c,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 2,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi0_cwk, "spi0", mod0_defauwt_pawents,
				  0x0a0,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi1_cwk, "spi1", mod0_defauwt_pawents,
				  0x0a4,
				  0, 4,		/* M */
				  16, 2,	/* P */
				  24, 4,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_M_WITH_GATE(i2s0_cwk, "i2s0", "pww-audio",
			     0x0b0, 0, 4, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_M_WITH_GATE(i2s1_cwk, "i2s1", "pww-audio",
			     0x0b4, 0, 4, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_M_WITH_GATE(i2s2_cwk, "i2s2", "pww-audio",
			     0x0b8, 0, 4, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_M_WITH_GATE(tdm_cwk, "tdm", "pww-audio",
			     0x0bc, 0, 4, BIT(31), CWK_SET_WATE_PAWENT);
static SUNXI_CCU_M_WITH_GATE(spdif_cwk, "spdif", "pww-audio",
			     0x0c0, 0, 4, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(usb_phy0_cwk,	"usb-phy0",	"osc24M",
		      0x0cc, BIT(8), 0);
static SUNXI_CCU_GATE(usb_phy1_cwk,	"usb-phy1",	"osc24M",
		      0x0cc, BIT(9), 0);
static SUNXI_CCU_GATE(usb_hsic_cwk,	"usb-hsic",	"pww-hsic",
		      0x0cc, BIT(10), 0);
static stwuct ccu_gate usb_hsic_12m_cwk = {
	.enabwe	= BIT(11),
	.common	= {
		.weg		= 0x0cc,
		.pwediv		= 2,
		.featuwes	= CCU_FEATUWE_AWW_PWEDIV,
		.hw.init	= CWK_HW_INIT("usb-hsic-12m", "osc24M",
					      &ccu_gate_ops, 0),
	}
};
static SUNXI_CCU_GATE(usb_ohci0_cwk,	"usb-ohci0",	"osc24M",
		      0x0cc, BIT(16), 0);

/* TODO dividew has minimum of 2 */
static SUNXI_CCU_M(dwam_cwk, "dwam", "pww-ddw", 0x0f4, 0, 4, CWK_IS_CWITICAW);

static SUNXI_CCU_GATE(dwam_ve_cwk,	"dwam-ve",	"dwam",
		      0x100, BIT(0), 0);
static SUNXI_CCU_GATE(dwam_csi_cwk,	"dwam-csi",	"dwam",
		      0x100, BIT(1), 0);

static const chaw * const tcon0_pawents[] = { "pww-video0" };
static SUNXI_CCU_MUX_WITH_GATE(tcon0_cwk, "tcon0", tcon0_pawents,
				 0x118, 24, 3, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw * const tcon1_pawents[] = { "pww-video1" };
static SUNXI_CCU_M_WITH_MUX_GATE(tcon1_cwk, "tcon1", tcon1_pawents,
				 0x11c, 0, 4, 24, 2, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(csi_misc_cwk, "csi-misc", "osc24M", 0x130, BIT(16), 0);

static SUNXI_CCU_GATE(mipi_csi_cwk, "mipi-csi", "osc24M", 0x130, BIT(31), 0);

static const chaw * const csi_mcwk_pawents[] = { "pww-video0", "pww-de",
						 "osc24M" };
static const u8 csi_mcwk_tabwe[] = { 0, 3, 5 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi_mcwk_cwk, "csi-mcwk",
				       csi_mcwk_pawents, csi_mcwk_tabwe,
				       0x134,
				       0, 5,	/* M */
				       8, 3,	/* mux */
				       BIT(15),	/* gate */
				       0);

static const chaw * const csi_scwk_pawents[] = { "pww-pewiph", "pww-ve" };
static const u8 csi_scwk_tabwe[] = { 0, 5 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi_scwk_cwk, "csi-scwk",
				       csi_scwk_pawents, csi_scwk_tabwe,
				       0x134,
				       16, 4,	/* M */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_M_WITH_GATE(ve_cwk, "ve", "pww-ve", 0x13c,
			     16, 3, BIT(31), CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(avs_cwk, "avs", "osc24M", 0x144, BIT(31), 0);

static const chaw * const hdmi_pawents[] = { "pww-video1" };
static SUNXI_CCU_M_WITH_MUX_GATE(hdmi_cwk, "hdmi", hdmi_pawents,
				 0x150,
				 0, 4,	/* M */
				 24, 2,	/* mux */
				 BIT(31),	/* gate */
				 CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(hdmi_swow_cwk, "hdmi-swow", "osc24M", 0x154, BIT(31), 0);

static const chaw * const mbus_pawents[] = { "osc24M", "pww-pewiph",
					     "pww-ddw" };
static SUNXI_CCU_M_WITH_MUX_GATE(mbus_cwk, "mbus", mbus_pawents,
				 0x15c,
				 0, 3,	/* M */
				 24, 2,	/* mux */
				 BIT(31),	/* gate */
				 CWK_IS_CWITICAW);

static const chaw * const mipi_dsi0_pawents[] = { "pww-video0" };
static const u8 mipi_dsi0_tabwe[] = { 8 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(mipi_dsi0_cwk, "mipi-dsi0",
				       mipi_dsi0_pawents, mipi_dsi0_tabwe,
				       0x168,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CWK_SET_WATE_PAWENT);

static const chaw * const mipi_dsi1_pawents[] = { "osc24M", "pww-video0" };
static const u8 mipi_dsi1_tabwe[] = { 0, 9 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(mipi_dsi1_cwk, "mipi-dsi1",
				       mipi_dsi1_pawents, mipi_dsi1_tabwe,
				       0x16c,
				       0, 4,	/* M */
				       24, 4,	/* mux */
				       BIT(31),	/* gate */
				       CWK_SET_WATE_PAWENT);

static SUNXI_CCU_M_WITH_GATE(gpu_cowe_cwk, "gpu-cowe", "pww-gpu", 0x1a0,
			     0, 3, BIT(31), CWK_SET_WATE_PAWENT);

static const chaw * const gpu_memowy_pawents[] = { "pww-gpu", "pww-ddw" };
static SUNXI_CCU_M_WITH_MUX_GATE(gpu_memowy_cwk, "gpu-memowy",
				 gpu_memowy_pawents,
				 0x1a4,
				 0, 3,		/* M */
				 24, 1,		/* mux */
				 BIT(31),	/* gate */
				 CWK_SET_WATE_PAWENT);

static SUNXI_CCU_M_WITH_GATE(gpu_hyd_cwk, "gpu-hyd", "pww-gpu", 0x1a8,
			     0, 3, BIT(31), CWK_SET_WATE_PAWENT);

static stwuct ccu_common *sun8i_a83t_ccu_cwks[] = {
	&pww_c0cpux_cwk.common,
	&pww_c1cpux_cwk.common,
	&pww_audio_cwk.common,
	&pww_video0_cwk.common,
	&pww_ve_cwk.common,
	&pww_ddw_cwk.common,
	&pww_pewiph_cwk.common,
	&pww_gpu_cwk.common,
	&pww_hsic_cwk.common,
	&pww_de_cwk.common,
	&pww_video1_cwk.common,
	&c0cpux_cwk.common,
	&c1cpux_cwk.common,
	&axi0_cwk.common,
	&axi1_cwk.common,
	&ahb1_cwk.common,
	&ahb2_cwk.common,
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
	&bus_emac_cwk.common,
	&bus_hstimew_cwk.common,
	&bus_spi0_cwk.common,
	&bus_spi1_cwk.common,
	&bus_otg_cwk.common,
	&bus_ehci0_cwk.common,
	&bus_ehci1_cwk.common,
	&bus_ohci0_cwk.common,
	&bus_ve_cwk.common,
	&bus_tcon0_cwk.common,
	&bus_tcon1_cwk.common,
	&bus_csi_cwk.common,
	&bus_hdmi_cwk.common,
	&bus_de_cwk.common,
	&bus_gpu_cwk.common,
	&bus_msgbox_cwk.common,
	&bus_spinwock_cwk.common,
	&bus_spdif_cwk.common,
	&bus_pio_cwk.common,
	&bus_i2s0_cwk.common,
	&bus_i2s1_cwk.common,
	&bus_i2s2_cwk.common,
	&bus_tdm_cwk.common,
	&bus_i2c0_cwk.common,
	&bus_i2c1_cwk.common,
	&bus_i2c2_cwk.common,
	&bus_uawt0_cwk.common,
	&bus_uawt1_cwk.common,
	&bus_uawt2_cwk.common,
	&bus_uawt3_cwk.common,
	&bus_uawt4_cwk.common,
	&cci400_cwk.common,
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
	&i2s2_cwk.common,
	&tdm_cwk.common,
	&spdif_cwk.common,
	&usb_phy0_cwk.common,
	&usb_phy1_cwk.common,
	&usb_hsic_cwk.common,
	&usb_hsic_12m_cwk.common,
	&usb_ohci0_cwk.common,
	&dwam_cwk.common,
	&dwam_ve_cwk.common,
	&dwam_csi_cwk.common,
	&tcon0_cwk.common,
	&tcon1_cwk.common,
	&csi_misc_cwk.common,
	&mipi_csi_cwk.common,
	&csi_mcwk_cwk.common,
	&csi_scwk_cwk.common,
	&ve_cwk.common,
	&avs_cwk.common,
	&hdmi_cwk.common,
	&hdmi_swow_cwk.common,
	&mbus_cwk.common,
	&mipi_dsi0_cwk.common,
	&mipi_dsi1_cwk.common,
	&gpu_cowe_cwk.common,
	&gpu_memowy_cwk.common,
	&gpu_hyd_cwk.common,
};

static stwuct cwk_hw_oneceww_data sun8i_a83t_hw_cwks = {
	.hws	= {
		[CWK_PWW_C0CPUX]	= &pww_c0cpux_cwk.common.hw,
		[CWK_PWW_C1CPUX]	= &pww_c1cpux_cwk.common.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.common.hw,
		[CWK_PWW_VIDEO0]	= &pww_video0_cwk.common.hw,
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DDW]		= &pww_ddw_cwk.common.hw,
		[CWK_PWW_PEWIPH]	= &pww_pewiph_cwk.common.hw,
		[CWK_PWW_GPU]		= &pww_gpu_cwk.common.hw,
		[CWK_PWW_HSIC]		= &pww_hsic_cwk.common.hw,
		[CWK_PWW_DE]		= &pww_de_cwk.common.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_C0CPUX]		= &c0cpux_cwk.common.hw,
		[CWK_C1CPUX]		= &c1cpux_cwk.common.hw,
		[CWK_AXI0]		= &axi0_cwk.common.hw,
		[CWK_AXI1]		= &axi1_cwk.common.hw,
		[CWK_AHB1]		= &ahb1_cwk.common.hw,
		[CWK_AHB2]		= &ahb2_cwk.common.hw,
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
		[CWK_BUS_EMAC]		= &bus_emac_cwk.common.hw,
		[CWK_BUS_HSTIMEW]	= &bus_hstimew_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_SPI1]		= &bus_spi1_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_BUS_EHCI0]		= &bus_ehci0_cwk.common.hw,
		[CWK_BUS_EHCI1]		= &bus_ehci1_cwk.common.hw,
		[CWK_BUS_OHCI0]		= &bus_ohci0_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_BUS_TCON0]		= &bus_tcon0_cwk.common.hw,
		[CWK_BUS_TCON1]		= &bus_tcon1_cwk.common.hw,
		[CWK_BUS_CSI]		= &bus_csi_cwk.common.hw,
		[CWK_BUS_HDMI]		= &bus_hdmi_cwk.common.hw,
		[CWK_BUS_DE]		= &bus_de_cwk.common.hw,
		[CWK_BUS_GPU]		= &bus_gpu_cwk.common.hw,
		[CWK_BUS_MSGBOX]	= &bus_msgbox_cwk.common.hw,
		[CWK_BUS_SPINWOCK]	= &bus_spinwock_cwk.common.hw,
		[CWK_BUS_SPDIF]		= &bus_spdif_cwk.common.hw,
		[CWK_BUS_PIO]		= &bus_pio_cwk.common.hw,
		[CWK_BUS_I2S0]		= &bus_i2s0_cwk.common.hw,
		[CWK_BUS_I2S1]		= &bus_i2s1_cwk.common.hw,
		[CWK_BUS_I2S2]		= &bus_i2s2_cwk.common.hw,
		[CWK_BUS_TDM]		= &bus_tdm_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_I2C2]		= &bus_i2c2_cwk.common.hw,
		[CWK_BUS_UAWT0]		= &bus_uawt0_cwk.common.hw,
		[CWK_BUS_UAWT1]		= &bus_uawt1_cwk.common.hw,
		[CWK_BUS_UAWT2]		= &bus_uawt2_cwk.common.hw,
		[CWK_BUS_UAWT3]		= &bus_uawt3_cwk.common.hw,
		[CWK_BUS_UAWT4]		= &bus_uawt4_cwk.common.hw,
		[CWK_CCI400]		= &cci400_cwk.common.hw,
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
		[CWK_I2S2]		= &i2s2_cwk.common.hw,
		[CWK_TDM]		= &tdm_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_PHY1]		= &usb_phy1_cwk.common.hw,
		[CWK_USB_HSIC]		= &usb_hsic_cwk.common.hw,
		[CWK_USB_HSIC_12M]	= &usb_hsic_12m_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_DWAM]		= &dwam_cwk.common.hw,
		[CWK_DWAM_VE]		= &dwam_ve_cwk.common.hw,
		[CWK_DWAM_CSI]		= &dwam_csi_cwk.common.hw,
		[CWK_TCON0]		= &tcon0_cwk.common.hw,
		[CWK_TCON1]		= &tcon1_cwk.common.hw,
		[CWK_CSI_MISC]		= &csi_misc_cwk.common.hw,
		[CWK_MIPI_CSI]		= &mipi_csi_cwk.common.hw,
		[CWK_CSI_MCWK]		= &csi_mcwk_cwk.common.hw,
		[CWK_CSI_SCWK]		= &csi_scwk_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_HDMI]		= &hdmi_cwk.common.hw,
		[CWK_HDMI_SWOW]		= &hdmi_swow_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_MIPI_DSI0]		= &mipi_dsi0_cwk.common.hw,
		[CWK_MIPI_DSI1]		= &mipi_dsi1_cwk.common.hw,
		[CWK_GPU_COWE]		= &gpu_cowe_cwk.common.hw,
		[CWK_GPU_MEMOWY]	= &gpu_memowy_cwk.common.hw,
		[CWK_GPU_HYD]		= &gpu_hyd_cwk.common.hw,
	},
	.num	= CWK_NUMBEW,
};

static stwuct ccu_weset_map sun8i_a83t_ccu_wesets[] = {
	[WST_USB_PHY0]		= { 0x0cc, BIT(0) },
	[WST_USB_PHY1]		= { 0x0cc, BIT(1) },
	[WST_USB_HSIC]		= { 0x0cc, BIT(2) },
	[WST_DWAM]		= { 0x0f4, BIT(31) },
	[WST_MBUS]		= { 0x0fc, BIT(31) },
	[WST_BUS_MIPI_DSI]	= { 0x2c0, BIT(1) },
	[WST_BUS_SS]		= { 0x2c0, BIT(5) },
	[WST_BUS_DMA]		= { 0x2c0, BIT(6) },
	[WST_BUS_MMC0]		= { 0x2c0, BIT(8) },
	[WST_BUS_MMC1]		= { 0x2c0, BIT(9) },
	[WST_BUS_MMC2]		= { 0x2c0, BIT(10) },
	[WST_BUS_NAND]		= { 0x2c0, BIT(13) },
	[WST_BUS_DWAM]		= { 0x2c0, BIT(14) },
	[WST_BUS_EMAC]		= { 0x2c0, BIT(17) },
	[WST_BUS_HSTIMEW]	= { 0x2c0, BIT(19) },
	[WST_BUS_SPI0]		= { 0x2c0, BIT(20) },
	[WST_BUS_SPI1]		= { 0x2c0, BIT(21) },
	[WST_BUS_OTG]		= { 0x2c0, BIT(24) },
	[WST_BUS_EHCI0]		= { 0x2c0, BIT(26) },
	[WST_BUS_EHCI1]		= { 0x2c0, BIT(27) },
	[WST_BUS_OHCI0]		= { 0x2c0, BIT(29) },
	[WST_BUS_VE]		= { 0x2c4, BIT(0) },
	[WST_BUS_TCON0]		= { 0x2c4, BIT(4) },
	[WST_BUS_TCON1]		= { 0x2c4, BIT(5) },
	[WST_BUS_CSI]		= { 0x2c4, BIT(8) },
	[WST_BUS_HDMI0]		= { 0x2c4, BIT(10) },
	[WST_BUS_HDMI1]		= { 0x2c4, BIT(11) },
	[WST_BUS_DE]		= { 0x2c4, BIT(12) },
	[WST_BUS_GPU]		= { 0x2c4, BIT(20) },
	[WST_BUS_MSGBOX]	= { 0x2c4, BIT(21) },
	[WST_BUS_SPINWOCK]	= { 0x2c4, BIT(22) },
	[WST_BUS_WVDS]		= { 0x2c8, BIT(0) },
	[WST_BUS_SPDIF]		= { 0x2d0, BIT(1) },
	[WST_BUS_I2S0]		= { 0x2d0, BIT(12) },
	[WST_BUS_I2S1]		= { 0x2d0, BIT(13) },
	[WST_BUS_I2S2]		= { 0x2d0, BIT(14) },
	[WST_BUS_TDM]		= { 0x2d0, BIT(15) },
	[WST_BUS_I2C0]		= { 0x2d8, BIT(0) },
	[WST_BUS_I2C1]		= { 0x2d8, BIT(1) },
	[WST_BUS_I2C2]		= { 0x2d8, BIT(2) },
	[WST_BUS_UAWT0]		= { 0x2d8, BIT(16) },
	[WST_BUS_UAWT1]		= { 0x2d8, BIT(17) },
	[WST_BUS_UAWT2]		= { 0x2d8, BIT(18) },
	[WST_BUS_UAWT3]		= { 0x2d8, BIT(19) },
	[WST_BUS_UAWT4]		= { 0x2d8, BIT(20) },
};

static const stwuct sunxi_ccu_desc sun8i_a83t_ccu_desc = {
	.ccu_cwks	= sun8i_a83t_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun8i_a83t_ccu_cwks),

	.hw_cwks	= &sun8i_a83t_hw_cwks,

	.wesets		= sun8i_a83t_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun8i_a83t_ccu_wesets),
};

#define SUN8I_A83T_PWW_P_SHIFT	16
#define SUN8I_A83T_PWW_N_SHIFT	8
#define SUN8I_A83T_PWW_N_WIDTH	8

static void sun8i_a83t_cpu_pww_fixup(void __iomem *weg)
{
	u32 vaw = weadw(weg);

	/* baiw out if P dividew is not used */
	if (!(vaw & BIT(SUN8I_A83T_PWW_P_SHIFT)))
		wetuwn;

	/*
	 * If P is used, output shouwd be wess than 288 MHz. When we
	 * set P to 1, we shouwd awso decwease the muwtipwiew so the
	 * output doesn't go out of wange, but not too much such that
	 * the muwtipwiew stays above 12, the minimaw opewation vawue.
	 *
	 * To keep it simpwe, set the muwtipwiew to 17, the weset vawue.
	 */
	vaw &= ~GENMASK(SUN8I_A83T_PWW_N_SHIFT + SUN8I_A83T_PWW_N_WIDTH - 1,
			SUN8I_A83T_PWW_N_SHIFT);
	vaw |= 17 << SUN8I_A83T_PWW_N_SHIFT;

	/* And cweaw P */
	vaw &= ~BIT(SUN8I_A83T_PWW_P_SHIFT);

	wwitew(vaw, weg);
}

static int sun8i_a83t_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *weg;
	u32 vaw;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	/* Enfowce d1 = 0, d2 = 1 fow Audio PWW */
	vaw = weadw(weg + SUN8I_A83T_PWW_AUDIO_WEG);
	vaw &= ~BIT(16);
	vaw |= BIT(18);
	wwitew(vaw, weg + SUN8I_A83T_PWW_AUDIO_WEG);

	/* Enfowce P = 1 fow both CPU cwustew PWWs */
	sun8i_a83t_cpu_pww_fixup(weg + SUN8I_A83T_PWW_C0CPUX_WEG);
	sun8i_a83t_cpu_pww_fixup(weg + SUN8I_A83T_PWW_C1CPUX_WEG);

	wetuwn devm_sunxi_ccu_pwobe(&pdev->dev, weg, &sun8i_a83t_ccu_desc);
}

static const stwuct of_device_id sun8i_a83t_ccu_ids[] = {
	{ .compatibwe = "awwwinnew,sun8i-a83t-ccu" },
	{ }
};

static stwuct pwatfowm_dwivew sun8i_a83t_ccu_dwivew = {
	.pwobe	= sun8i_a83t_ccu_pwobe,
	.dwivew	= {
		.name	= "sun8i-a83t-ccu",
		.suppwess_bind_attws = twue,
		.of_match_tabwe	= sun8i_a83t_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun8i_a83t_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
