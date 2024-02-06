// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017 Icenowy Zheng <icenowy@aosc.io>
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

#incwude "ccu-sun50i-h6.h"

/*
 * The CPU PWW is actuawwy NP cwock, with P being /1, /2 ow /4. Howevew
 * P shouwd onwy be used fow output fwequencies wowew than 288 MHz.
 *
 * Fow now we can just modew it as a muwtipwiew cwock, and fowce P to /1.
 *
 * The M factow is pwesent in the wegistew's descwiption, but not in the
 * fwequency fowmuwa, and it's documented as "M is onwy used fow backdoow
 * testing", so it's not modewwed and then fowce to 0.
 */
#define SUN50I_H6_PWW_CPUX_WEG		0x000
static stwuct ccu_muwt pww_cpux_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.muwt		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.common		= {
		.weg		= 0x000,
		.hw.init	= CWK_HW_INIT("pww-cpux", "osc24M",
					      &ccu_muwt_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/* Some PWWs awe input * N / div1 / P. Modew them as NKMP with no K */
#define SUN50I_H6_PWW_DDW0_WEG		0x010
static stwuct ccu_nkmp pww_ddw0_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x010,
		.hw.init	= CWK_HW_INIT("pww-ddw0", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_H6_PWW_PEWIPH0_WEG	0x020
static stwuct ccu_nkmp pww_pewiph0_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.fixed_post_div	= 4,
	.common		= {
		.weg		= 0x020,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph0", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_H6_PWW_PEWIPH1_WEG	0x028
static stwuct ccu_nkmp pww_pewiph1_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.fixed_post_div	= 4,
	.common		= {
		.weg		= 0x028,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph1", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/* Fow GPU PWW, using an output dividew fow DFS causes system to faiw */
#define SUN50I_H6_PWW_GPU_WEG		0x030
static stwuct ccu_nkmp pww_gpu_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.common		= {
		.weg		= 0x030,
		.hw.init	= CWK_HW_INIT("pww-gpu", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/*
 * Fow Video PWWs, the output dividew is descwibed as "used fow testing"
 * in the usew manuaw. So it's not modewwed and fowced to 0.
 */
#define SUN50I_H6_PWW_VIDEO0_WEG	0x040
static stwuct ccu_nm pww_video0_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.fixed_post_div	= 4,
	.min_wate	= 288000000,
	.max_wate	= 2400000000UW,
	.common		= {
		.weg		= 0x040,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-video0", "osc24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_H6_PWW_VIDEO1_WEG	0x048
static stwuct ccu_nm pww_video1_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.fixed_post_div	= 4,
	.min_wate	= 288000000,
	.max_wate	= 2400000000UW,
	.common		= {
		.weg		= 0x048,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-video1", "osc24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_H6_PWW_VE_WEG		0x058
static stwuct ccu_nkmp pww_ve_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x058,
		.hw.init	= CWK_HW_INIT("pww-ve", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_H6_PWW_DE_WEG		0x060
static stwuct ccu_nkmp pww_de_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x060,
		.hw.init	= CWK_HW_INIT("pww-de", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_H6_PWW_HSIC_WEG		0x070
static stwuct ccu_nkmp pww_hsic_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x070,
		.hw.init	= CWK_HW_INIT("pww-hsic", "osc24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/*
 * The Audio PWW is supposed to have 3 outputs: 2 fixed factows fwom
 * the base (2x and 4x), and one vawiabwe dividew (the one twue pww audio).
 *
 * We don't have any need fow the vawiabwe dividew fow now, so we just
 * hawdcode it to match with the cwock names.
 */
#define SUN50I_H6_PWW_AUDIO_WEG		0x078

static stwuct ccu_sdm_setting pww_audio_sdm_tabwe[] = {
	{ .wate = 541900800, .pattewn = 0xc001288d, .m = 1, .n = 22 },
	{ .wate = 589824000, .pattewn = 0xc00126e9, .m = 1, .n = 24 },
};

static stwuct ccu_nm pww_audio_base_cwk = {
	.enabwe		= BIT(31),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.sdm		= _SUNXI_CCU_SDM(pww_audio_sdm_tabwe,
					 BIT(24), 0x178, BIT(31)),
	.common		= {
		.featuwes	= CCU_FEATUWE_SIGMA_DEWTA_MOD,
		.weg		= 0x078,
		.hw.init	= CWK_HW_INIT("pww-audio-base", "osc24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static const chaw * const cpux_pawents[] = { "osc24M", "osc32k",
					     "iosc", "pww-cpux" };
static SUNXI_CCU_MUX(cpux_cwk, "cpux", cpux_pawents,
		     0x500, 24, 2, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);
static SUNXI_CCU_M(axi_cwk, "axi", "cpux", 0x500, 0, 2, 0);
static SUNXI_CCU_M(cpux_apb_cwk, "cpux-apb", "cpux", 0x500, 8, 2, 0);

static const chaw * const psi_ahb1_ahb2_pawents[] = { "osc24M", "osc32k",
						      "iosc", "pww-pewiph0" };
static SUNXI_CCU_MP_WITH_MUX(psi_ahb1_ahb2_cwk, "psi-ahb1-ahb2",
			     psi_ahb1_ahb2_pawents,
			     0x510,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static const chaw * const ahb3_apb1_apb2_pawents[] = { "osc24M", "osc32k",
						       "psi-ahb1-ahb2",
						       "pww-pewiph0" };
static SUNXI_CCU_MP_WITH_MUX(ahb3_cwk, "ahb3", ahb3_apb1_apb2_pawents, 0x51c,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static SUNXI_CCU_MP_WITH_MUX(apb1_cwk, "apb1", ahb3_apb1_apb2_pawents, 0x520,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static SUNXI_CCU_MP_WITH_MUX(apb2_cwk, "apb2", ahb3_apb1_apb2_pawents, 0x524,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 2,	/* mux */
			     0);

static const chaw * const mbus_pawents[] = { "osc24M", "pww-pewiph0-2x",
					     "pww-ddw0", "pww-pewiph0-4x" };
static SUNXI_CCU_M_WITH_MUX_GATE(mbus_cwk, "mbus", mbus_pawents, 0x540,
				       0, 3,	/* M */
				       24, 2,	/* mux */
				       BIT(31),	/* gate */
				       CWK_IS_CWITICAW);

static const chaw * const de_pawents[] = { "pww-de", "pww-pewiph0-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(de_cwk, "de", de_pawents, 0x600,
				       0, 4,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(bus_de_cwk, "bus-de", "psi-ahb1-ahb2",
		      0x60c, BIT(0), 0);

static const chaw * const deintewwace_pawents[] = { "pww-pewiph0",
						    "pww-pewiph1" };
static SUNXI_CCU_M_WITH_MUX_GATE(deintewwace_cwk, "deintewwace",
				       deintewwace_pawents,
				       0x620,
				       0, 4,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE(bus_deintewwace_cwk, "bus-deintewwace", "psi-ahb1-ahb2",
		      0x62c, BIT(0), 0);

/* Keep GPU_CWK dividew const to avoid DFS instabiwity. */
static const chaw * const gpu_pawents[] = { "pww-gpu" };
static SUNXI_CCU_MUX_WITH_GATE(gpu_cwk, "gpu", gpu_pawents, 0x670,
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(bus_gpu_cwk, "bus-gpu", "psi-ahb1-ahb2",
		      0x67c, BIT(0), 0);

/* Awso appwies to EMCE */
static const chaw * const ce_pawents[] = { "osc24M", "pww-pewiph0-2x" };
static SUNXI_CCU_MP_WITH_MUX_GATE(ce_cwk, "ce", ce_pawents, 0x680,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 1,	/* mux */
					BIT(31),/* gate */
					0);

static SUNXI_CCU_GATE(bus_ce_cwk, "bus-ce", "psi-ahb1-ahb2",
		      0x68c, BIT(0), 0);

static const chaw * const ve_pawents[] = { "pww-ve" };
static SUNXI_CCU_M_WITH_MUX_GATE(ve_cwk, "ve", ve_pawents, 0x690,
				       0, 3,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(bus_ve_cwk, "bus-ve", "psi-ahb1-ahb2",
		      0x69c, BIT(0), 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(emce_cwk, "emce", ce_pawents, 0x6b0,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 1,	/* mux */
					BIT(31),/* gate */
					0);

static SUNXI_CCU_GATE(bus_emce_cwk, "bus-emce", "psi-ahb1-ahb2",
		      0x6bc, BIT(0), 0);

static const chaw * const vp9_pawents[] = { "pww-ve", "pww-pewiph0-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(vp9_cwk, "vp9", vp9_pawents, 0x6c0,
				       0, 3,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE(bus_vp9_cwk, "bus-vp9", "psi-ahb1-ahb2",
		      0x6cc, BIT(0), 0);

static SUNXI_CCU_GATE(bus_dma_cwk, "bus-dma", "psi-ahb1-ahb2",
		      0x70c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_msgbox_cwk, "bus-msgbox", "psi-ahb1-ahb2",
		      0x71c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_spinwock_cwk, "bus-spinwock", "psi-ahb1-ahb2",
		      0x72c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_hstimew_cwk, "bus-hstimew", "psi-ahb1-ahb2",
		      0x73c, BIT(0), 0);

static SUNXI_CCU_GATE(avs_cwk, "avs", "osc24M", 0x740, BIT(31), 0);

static SUNXI_CCU_GATE(bus_dbg_cwk, "bus-dbg", "psi-ahb1-ahb2",
		      0x78c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_psi_cwk, "bus-psi", "psi-ahb1-ahb2",
		      0x79c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_pwm_cwk, "bus-pwm", "apb1", 0x7ac, BIT(0), 0);

static SUNXI_CCU_GATE(bus_iommu_cwk, "bus-iommu", "apb1", 0x7bc, BIT(0), 0);

static const chaw * const dwam_pawents[] = { "pww-ddw0" };
static stwuct ccu_div dwam_cwk = {
	.div		= _SUNXI_CCU_DIV(0, 2),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common	= {
		.weg		= 0x800,
		.hw.init	= CWK_HW_INIT_PAWENTS("dwam",
						      dwam_pawents,
						      &ccu_div_ops,
						      CWK_IS_CWITICAW),
	},
};

static SUNXI_CCU_GATE(mbus_dma_cwk, "mbus-dma", "mbus",
		      0x804, BIT(0), 0);
static SUNXI_CCU_GATE(mbus_ve_cwk, "mbus-ve", "mbus",
		      0x804, BIT(1), 0);
static SUNXI_CCU_GATE(mbus_ce_cwk, "mbus-ce", "mbus",
		      0x804, BIT(2), 0);
static SUNXI_CCU_GATE(mbus_ts_cwk, "mbus-ts", "mbus",
		      0x804, BIT(3), 0);
static SUNXI_CCU_GATE(mbus_nand_cwk, "mbus-nand", "mbus",
		      0x804, BIT(5), 0);
static SUNXI_CCU_GATE(mbus_csi_cwk, "mbus-csi", "mbus",
		      0x804, BIT(8), 0);
static SUNXI_CCU_GATE(mbus_deintewwace_cwk, "mbus-deintewwace", "mbus",
		      0x804, BIT(11), 0);

static SUNXI_CCU_GATE(bus_dwam_cwk, "bus-dwam", "psi-ahb1-ahb2",
		      0x80c, BIT(0), CWK_IS_CWITICAW);

static const chaw * const nand_spi_pawents[] = { "osc24M", "pww-pewiph0",
					     "pww-pewiph1", "pww-pewiph0-2x",
					     "pww-pewiph1-2x" };
static SUNXI_CCU_MP_WITH_MUX_GATE(nand0_cwk, "nand0", nand_spi_pawents, 0x810,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 3,	/* mux */
					BIT(31),/* gate */
					0);

static SUNXI_CCU_MP_WITH_MUX_GATE(nand1_cwk, "nand1", nand_spi_pawents, 0x814,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 3,	/* mux */
					BIT(31),/* gate */
					0);

static SUNXI_CCU_GATE(bus_nand_cwk, "bus-nand", "ahb3", 0x82c, BIT(0), 0);

static const chaw * const mmc_pawents[] = { "osc24M", "pww-pewiph0-2x",
					    "pww-pewiph1-2x" };
static SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc0_cwk, "mmc0", mmc_pawents, 0x830,
					  0, 4,		/* M */
					  8, 2,		/* N */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-div */
					  0);

static SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc1_cwk, "mmc1", mmc_pawents, 0x834,
					  0, 4,		/* M */
					  8, 2,		/* N */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-div */
					  0);

static SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc2_cwk, "mmc2", mmc_pawents, 0x838,
					  0, 4,		/* M */
					  8, 2,		/* N */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-div */
					  0);

static SUNXI_CCU_GATE(bus_mmc0_cwk, "bus-mmc0", "ahb3", 0x84c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_mmc1_cwk, "bus-mmc1", "ahb3", 0x84c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_mmc2_cwk, "bus-mmc2", "ahb3", 0x84c, BIT(2), 0);

static SUNXI_CCU_GATE(bus_uawt0_cwk, "bus-uawt0", "apb2", 0x90c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_uawt1_cwk, "bus-uawt1", "apb2", 0x90c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_uawt2_cwk, "bus-uawt2", "apb2", 0x90c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_uawt3_cwk, "bus-uawt3", "apb2", 0x90c, BIT(3), 0);

static SUNXI_CCU_GATE(bus_i2c0_cwk, "bus-i2c0", "apb2", 0x91c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2c1_cwk, "bus-i2c1", "apb2", 0x91c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_i2c2_cwk, "bus-i2c2", "apb2", 0x91c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_i2c3_cwk, "bus-i2c3", "apb2", 0x91c, BIT(3), 0);

static SUNXI_CCU_GATE(bus_scw0_cwk, "bus-scw0", "apb2", 0x93c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_scw1_cwk, "bus-scw1", "apb2", 0x93c, BIT(1), 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi0_cwk, "spi0", nand_spi_pawents, 0x940,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 3,	/* mux */
					BIT(31),/* gate */
					0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi1_cwk, "spi1", nand_spi_pawents, 0x944,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 3,	/* mux */
					BIT(31),/* gate */
					0);

static SUNXI_CCU_GATE(bus_spi0_cwk, "bus-spi0", "ahb3", 0x96c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_spi1_cwk, "bus-spi1", "ahb3", 0x96c, BIT(1), 0);

static SUNXI_CCU_GATE(bus_emac_cwk, "bus-emac", "ahb3", 0x97c, BIT(0), 0);

static const chaw * const ts_pawents[] = { "osc24M", "pww-pewiph0" };
static SUNXI_CCU_MP_WITH_MUX_GATE(ts_cwk, "ts", ts_pawents, 0x9b0,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 1,	/* mux */
					BIT(31),/* gate */
					0);

static SUNXI_CCU_GATE(bus_ts_cwk, "bus-ts", "ahb3", 0x9bc, BIT(0), 0);

static const chaw * const iw_tx_pawents[] = { "osc32k", "osc24M" };
static SUNXI_CCU_MP_WITH_MUX_GATE(iw_tx_cwk, "iw-tx", iw_tx_pawents, 0x9c0,
					0, 4,	/* M */
					8, 2,	/* N */
					24, 1,	/* mux */
					BIT(31),/* gate */
					0);

static SUNXI_CCU_GATE(bus_iw_tx_cwk, "bus-iw-tx", "apb1", 0x9cc, BIT(0), 0);

static SUNXI_CCU_GATE(bus_ths_cwk, "bus-ths", "apb1", 0x9fc, BIT(0), 0);

static const chaw * const audio_pawents[] = { "pww-audio", "pww-audio-2x", "pww-audio-4x" };
static stwuct ccu_div i2s3_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa0c,
		.hw.init	= CWK_HW_INIT_PAWENTS("i2s3",
						      audio_pawents,
						      &ccu_div_ops,
						      CWK_SET_WATE_PAWENT),
	},
};

static stwuct ccu_div i2s0_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa10,
		.hw.init	= CWK_HW_INIT_PAWENTS("i2s0",
						      audio_pawents,
						      &ccu_div_ops,
						      CWK_SET_WATE_PAWENT),
	},
};

static stwuct ccu_div i2s1_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa14,
		.hw.init	= CWK_HW_INIT_PAWENTS("i2s1",
						      audio_pawents,
						      &ccu_div_ops,
						      CWK_SET_WATE_PAWENT),
	},
};

static stwuct ccu_div i2s2_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa18,
		.hw.init	= CWK_HW_INIT_PAWENTS("i2s2",
						      audio_pawents,
						      &ccu_div_ops,
						      CWK_SET_WATE_PAWENT),
	},
};

static SUNXI_CCU_GATE(bus_i2s0_cwk, "bus-i2s0", "apb1", 0xa1c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2s1_cwk, "bus-i2s1", "apb1", 0xa1c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_i2s2_cwk, "bus-i2s2", "apb1", 0xa1c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_i2s3_cwk, "bus-i2s3", "apb1", 0xa1c, BIT(3), 0);

static stwuct ccu_div spdif_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa20,
		.hw.init	= CWK_HW_INIT_PAWENTS("spdif",
						      audio_pawents,
						      &ccu_div_ops,
						      0),
	},
};

static SUNXI_CCU_GATE(bus_spdif_cwk, "bus-spdif", "apb1", 0xa2c, BIT(0), 0);

static stwuct ccu_div dmic_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa40,
		.hw.init	= CWK_HW_INIT_PAWENTS("dmic",
						      audio_pawents,
						      &ccu_div_ops,
						      0),
	},
};

static SUNXI_CCU_GATE(bus_dmic_cwk, "bus-dmic", "apb1", 0xa4c, BIT(0), 0);

static stwuct ccu_div audio_hub_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa60,
		.hw.init	= CWK_HW_INIT_PAWENTS("audio-hub",
						      audio_pawents,
						      &ccu_div_ops,
						      0),
	},
};

static SUNXI_CCU_GATE(bus_audio_hub_cwk, "bus-audio-hub", "apb1", 0xa6c, BIT(0), 0);

/*
 * Thewe awe OHCI 12M cwock souwce sewection bits fow 2 USB 2.0 powts.
 * We wiww fowce them to 0 (12M divided fwom 48M).
 */
#define SUN50I_H6_USB0_CWK_WEG		0xa70
#define SUN50I_H6_USB3_CWK_WEG		0xa7c

static SUNXI_CCU_GATE(usb_ohci0_cwk, "usb-ohci0", "osc12M", 0xa70, BIT(31), 0);
static SUNXI_CCU_GATE(usb_phy0_cwk, "usb-phy0", "osc24M", 0xa70, BIT(29), 0);

static SUNXI_CCU_GATE(usb_phy1_cwk, "usb-phy1", "osc24M", 0xa74, BIT(29), 0);

static SUNXI_CCU_GATE(usb_ohci3_cwk, "usb-ohci3", "osc12M", 0xa7c, BIT(31), 0);
static SUNXI_CCU_GATE(usb_phy3_cwk, "usb-phy3", "osc12M", 0xa7c, BIT(29), 0);
static SUNXI_CCU_GATE(usb_hsic_12m_cwk, "usb-hsic-12M", "osc12M", 0xa7c, BIT(27), 0);
static SUNXI_CCU_GATE(usb_hsic_cwk, "usb-hsic", "pww-hsic", 0xa7c, BIT(26), 0);

static SUNXI_CCU_GATE(bus_ohci0_cwk, "bus-ohci0", "ahb3", 0xa8c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_ohci3_cwk, "bus-ohci3", "ahb3", 0xa8c, BIT(3), 0);
static SUNXI_CCU_GATE(bus_ehci0_cwk, "bus-ehci0", "ahb3", 0xa8c, BIT(4), 0);
static SUNXI_CCU_GATE(bus_xhci_cwk, "bus-xhci", "ahb3", 0xa8c, BIT(5), 0);
static SUNXI_CCU_GATE(bus_ehci3_cwk, "bus-ehci3", "ahb3", 0xa8c, BIT(7), 0);
static SUNXI_CCU_GATE(bus_otg_cwk, "bus-otg", "ahb3", 0xa8c, BIT(8), 0);

static stwuct cwk_fixed_factow pww_pewiph0_4x_cwk;
static CWK_FIXED_FACTOW_HW(pcie_wef_100m_cwk, "pcie-wef-100M",
			   &pww_pewiph0_4x_cwk.hw, 24, 1, 0);
static SUNXI_CCU_GATE(pcie_wef_cwk, "pcie-wef", "pcie-wef-100M",
		      0xab0, BIT(31), 0);
static SUNXI_CCU_GATE(pcie_wef_out_cwk, "pcie-wef-out", "pcie-wef",
		      0xab0, BIT(30), 0);

static SUNXI_CCU_M_WITH_GATE(pcie_maxi_cwk, "pcie-maxi",
			     "pww-pewiph0", 0xab4,
			     0, 4,	/* M */
			     BIT(31),	/* gate */
			     0);

static SUNXI_CCU_M_WITH_GATE(pcie_aux_cwk, "pcie-aux", "osc24M", 0xab8,
			     0, 5,	/* M */
			     BIT(31),	/* gate */
			     0);

static SUNXI_CCU_GATE(bus_pcie_cwk, "bus-pcie", "psi-ahb1-ahb2",
		      0xabc, BIT(0), 0);

static const chaw * const hdmi_pawents[] = { "pww-video0", "pww-video1",
					      "pww-video1-4x" };
static SUNXI_CCU_M_WITH_MUX_GATE(hdmi_cwk, "hdmi", hdmi_pawents, 0xb00,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_GATE(hdmi_swow_cwk, "hdmi-swow", "osc24M", 0xb04, BIT(31), 0);

static const chaw * const hdmi_cec_pawents[] = { "osc32k", "pww-pewiph0-2x" };
static const stwuct ccu_mux_fixed_pwediv hdmi_cec_pwedivs[] = {
	{ .index = 1, .div = 36621 },
};

#define SUN50I_H6_HDMI_CEC_CWK_WEG		0xb10
static stwuct ccu_mux hdmi_cec_cwk = {
	.enabwe		= BIT(31),

	.mux		= {
		.shift	= 24,
		.width	= 2,

		.fixed_pwedivs	= hdmi_cec_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(hdmi_cec_pwedivs),
	},

	.common		= {
		.weg		= 0xb10,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS("hdmi-cec",
						      hdmi_cec_pawents,
						      &ccu_mux_ops,
						      0),
	},
};

static SUNXI_CCU_GATE(bus_hdmi_cwk, "bus-hdmi", "ahb3", 0xb1c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_tcon_top_cwk, "bus-tcon-top", "ahb3",
		      0xb5c, BIT(0), 0);

static const chaw * const tcon_wcd0_pawents[] = { "pww-video0",
						  "pww-video0-4x",
						  "pww-video1" };
static SUNXI_CCU_MUX_WITH_GATE(tcon_wcd0_cwk, "tcon-wcd0",
			       tcon_wcd0_pawents, 0xb60,
			       24, 3,	/* mux */
			       BIT(31),	/* gate */
			       CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(bus_tcon_wcd0_cwk, "bus-tcon-wcd0", "ahb3",
		      0xb7c, BIT(0), 0);

static const chaw * const tcon_tv0_pawents[] = { "pww-video0",
						 "pww-video0-4x",
						 "pww-video1",
						 "pww-video1-4x" };
static SUNXI_CCU_MP_WITH_MUX_GATE(tcon_tv0_cwk, "tcon-tv0",
				  tcon_tv0_pawents, 0xb80,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(bus_tcon_tv0_cwk, "bus-tcon-tv0", "ahb3",
		      0xb9c, BIT(0), 0);

static SUNXI_CCU_GATE(csi_cci_cwk, "csi-cci", "osc24M", 0xc00, BIT(0), 0);

static const chaw * const csi_top_pawents[] = { "pww-video0", "pww-ve",
					      "pww-pewiph0" };
static const u8 csi_top_tabwe[] = { 0, 2, 3 };
static SUNXI_CCU_M_WITH_MUX_TABWE_GATE(csi_top_cwk, "csi-top",
				       csi_top_pawents, csi_top_tabwe, 0xc04,
				       0, 4,	/* M */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static const chaw * const csi_mcwk_pawents[] = { "osc24M", "pww-video0",
					       "pww-pewiph0", "pww-pewiph1" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi_mcwk_cwk, "csi-mcwk",
				 csi_mcwk_pawents, 0xc08,
				 0, 5,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_GATE(bus_csi_cwk, "bus-csi", "ahb3", 0xc2c, BIT(0), 0);

static const chaw * const hdcp_pawents[] = { "pww-pewiph0", "pww-pewiph1" };
static SUNXI_CCU_M_WITH_MUX_GATE(hdcp_cwk, "hdcp", hdcp_pawents, 0xc40,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_GATE(bus_hdcp_cwk, "bus-hdcp", "ahb3", 0xc4c, BIT(0), 0);

/* Fixed factow cwocks */
static CWK_FIXED_FACTOW_FW_NAME(osc12M_cwk, "osc12M", "hosc", 2, 1, 0);

static const stwuct cwk_hw *cwk_pawent_pww_audio[] = {
	&pww_audio_base_cwk.common.hw
};

/*
 * The dividew of pww-audio is fixed to 24 fow now, so 24576000 and 22579200
 * wates can be set exactwy in conjunction with sigma-dewta moduwation.
 */
static CWK_FIXED_FACTOW_HWS(pww_audio_cwk, "pww-audio",
			    cwk_pawent_pww_audio,
			    24, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_audio_2x_cwk, "pww-audio-2x",
			    cwk_pawent_pww_audio,
			    4, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_audio_4x_cwk, "pww-audio-4x",
			    cwk_pawent_pww_audio,
			    2, 1, CWK_SET_WATE_PAWENT);

static const stwuct cwk_hw *pww_pewiph0_pawents[] = {
	&pww_pewiph0_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_pewiph0_4x_cwk, "pww-pewiph0-4x",
			    pww_pewiph0_pawents,
			    1, 4, 0);
static CWK_FIXED_FACTOW_HWS(pww_pewiph0_2x_cwk, "pww-pewiph0-2x",
			    pww_pewiph0_pawents,
			    1, 2, 0);

static const stwuct cwk_hw *pww_pewiph1_pawents[] = {
	&pww_pewiph1_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_pewiph1_4x_cwk, "pww-pewiph1-4x",
			    pww_pewiph1_pawents,
			    1, 4, 0);
static CWK_FIXED_FACTOW_HWS(pww_pewiph1_2x_cwk, "pww-pewiph1-2x",
			    pww_pewiph1_pawents,
			    1, 2, 0);

static CWK_FIXED_FACTOW_HW(pww_video0_4x_cwk, "pww-video0-4x",
			   &pww_video0_cwk.common.hw,
			   1, 4, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HW(pww_video1_4x_cwk, "pww-video1-4x",
			   &pww_video1_cwk.common.hw,
			   1, 4, CWK_SET_WATE_PAWENT);

static stwuct ccu_common *sun50i_h6_ccu_cwks[] = {
	&pww_cpux_cwk.common,
	&pww_ddw0_cwk.common,
	&pww_pewiph0_cwk.common,
	&pww_pewiph1_cwk.common,
	&pww_gpu_cwk.common,
	&pww_video0_cwk.common,
	&pww_video1_cwk.common,
	&pww_ve_cwk.common,
	&pww_de_cwk.common,
	&pww_hsic_cwk.common,
	&pww_audio_base_cwk.common,
	&cpux_cwk.common,
	&axi_cwk.common,
	&cpux_apb_cwk.common,
	&psi_ahb1_ahb2_cwk.common,
	&ahb3_cwk.common,
	&apb1_cwk.common,
	&apb2_cwk.common,
	&mbus_cwk.common,
	&de_cwk.common,
	&bus_de_cwk.common,
	&deintewwace_cwk.common,
	&bus_deintewwace_cwk.common,
	&gpu_cwk.common,
	&bus_gpu_cwk.common,
	&ce_cwk.common,
	&bus_ce_cwk.common,
	&ve_cwk.common,
	&bus_ve_cwk.common,
	&emce_cwk.common,
	&bus_emce_cwk.common,
	&vp9_cwk.common,
	&bus_vp9_cwk.common,
	&bus_dma_cwk.common,
	&bus_msgbox_cwk.common,
	&bus_spinwock_cwk.common,
	&bus_hstimew_cwk.common,
	&avs_cwk.common,
	&bus_dbg_cwk.common,
	&bus_psi_cwk.common,
	&bus_pwm_cwk.common,
	&bus_iommu_cwk.common,
	&dwam_cwk.common,
	&mbus_dma_cwk.common,
	&mbus_ve_cwk.common,
	&mbus_ce_cwk.common,
	&mbus_ts_cwk.common,
	&mbus_nand_cwk.common,
	&mbus_csi_cwk.common,
	&mbus_deintewwace_cwk.common,
	&bus_dwam_cwk.common,
	&nand0_cwk.common,
	&nand1_cwk.common,
	&bus_nand_cwk.common,
	&mmc0_cwk.common,
	&mmc1_cwk.common,
	&mmc2_cwk.common,
	&bus_mmc0_cwk.common,
	&bus_mmc1_cwk.common,
	&bus_mmc2_cwk.common,
	&bus_uawt0_cwk.common,
	&bus_uawt1_cwk.common,
	&bus_uawt2_cwk.common,
	&bus_uawt3_cwk.common,
	&bus_i2c0_cwk.common,
	&bus_i2c1_cwk.common,
	&bus_i2c2_cwk.common,
	&bus_i2c3_cwk.common,
	&bus_scw0_cwk.common,
	&bus_scw1_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&bus_spi0_cwk.common,
	&bus_spi1_cwk.common,
	&bus_emac_cwk.common,
	&ts_cwk.common,
	&bus_ts_cwk.common,
	&iw_tx_cwk.common,
	&bus_iw_tx_cwk.common,
	&bus_ths_cwk.common,
	&i2s3_cwk.common,
	&i2s0_cwk.common,
	&i2s1_cwk.common,
	&i2s2_cwk.common,
	&bus_i2s0_cwk.common,
	&bus_i2s1_cwk.common,
	&bus_i2s2_cwk.common,
	&bus_i2s3_cwk.common,
	&spdif_cwk.common,
	&bus_spdif_cwk.common,
	&dmic_cwk.common,
	&bus_dmic_cwk.common,
	&audio_hub_cwk.common,
	&bus_audio_hub_cwk.common,
	&usb_ohci0_cwk.common,
	&usb_phy0_cwk.common,
	&usb_phy1_cwk.common,
	&usb_ohci3_cwk.common,
	&usb_phy3_cwk.common,
	&usb_hsic_12m_cwk.common,
	&usb_hsic_cwk.common,
	&bus_ohci0_cwk.common,
	&bus_ohci3_cwk.common,
	&bus_ehci0_cwk.common,
	&bus_xhci_cwk.common,
	&bus_ehci3_cwk.common,
	&bus_otg_cwk.common,
	&pcie_wef_cwk.common,
	&pcie_wef_out_cwk.common,
	&pcie_maxi_cwk.common,
	&pcie_aux_cwk.common,
	&bus_pcie_cwk.common,
	&hdmi_cwk.common,
	&hdmi_swow_cwk.common,
	&hdmi_cec_cwk.common,
	&bus_hdmi_cwk.common,
	&bus_tcon_top_cwk.common,
	&tcon_wcd0_cwk.common,
	&bus_tcon_wcd0_cwk.common,
	&tcon_tv0_cwk.common,
	&bus_tcon_tv0_cwk.common,
	&csi_cci_cwk.common,
	&csi_top_cwk.common,
	&csi_mcwk_cwk.common,
	&bus_csi_cwk.common,
	&hdcp_cwk.common,
	&bus_hdcp_cwk.common,
};

static stwuct cwk_hw_oneceww_data sun50i_h6_hw_cwks = {
	.hws	= {
		[CWK_OSC12M]		= &osc12M_cwk.hw,
		[CWK_PWW_CPUX]		= &pww_cpux_cwk.common.hw,
		[CWK_PWW_DDW0]		= &pww_ddw0_cwk.common.hw,
		[CWK_PWW_PEWIPH0]	= &pww_pewiph0_cwk.common.hw,
		[CWK_PWW_PEWIPH0_2X]	= &pww_pewiph0_2x_cwk.hw,
		[CWK_PWW_PEWIPH0_4X]	= &pww_pewiph0_4x_cwk.hw,
		[CWK_PWW_PEWIPH1]	= &pww_pewiph1_cwk.common.hw,
		[CWK_PWW_PEWIPH1_2X]	= &pww_pewiph1_2x_cwk.hw,
		[CWK_PWW_PEWIPH1_4X]	= &pww_pewiph1_4x_cwk.hw,
		[CWK_PWW_GPU]		= &pww_gpu_cwk.common.hw,
		[CWK_PWW_VIDEO0]	= &pww_video0_cwk.common.hw,
		[CWK_PWW_VIDEO0_4X]	= &pww_video0_4x_cwk.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_PWW_VIDEO1_4X]	= &pww_video1_4x_cwk.hw,
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_DE]		= &pww_de_cwk.common.hw,
		[CWK_PWW_HSIC]		= &pww_hsic_cwk.common.hw,
		[CWK_PWW_AUDIO_BASE]	= &pww_audio_base_cwk.common.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.hw,
		[CWK_PWW_AUDIO_2X]	= &pww_audio_2x_cwk.hw,
		[CWK_PWW_AUDIO_4X]	= &pww_audio_4x_cwk.hw,
		[CWK_CPUX]		= &cpux_cwk.common.hw,
		[CWK_AXI]		= &axi_cwk.common.hw,
		[CWK_CPUX_APB]		= &cpux_apb_cwk.common.hw,
		[CWK_PSI_AHB1_AHB2]	= &psi_ahb1_ahb2_cwk.common.hw,
		[CWK_AHB3]		= &ahb3_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_APB2]		= &apb2_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.common.hw,
		[CWK_DE]		= &de_cwk.common.hw,
		[CWK_BUS_DE]		= &bus_de_cwk.common.hw,
		[CWK_DEINTEWWACE]	= &deintewwace_cwk.common.hw,
		[CWK_BUS_DEINTEWWACE]	= &bus_deintewwace_cwk.common.hw,
		[CWK_GPU]		= &gpu_cwk.common.hw,
		[CWK_BUS_GPU]		= &bus_gpu_cwk.common.hw,
		[CWK_CE]		= &ce_cwk.common.hw,
		[CWK_BUS_CE]		= &bus_ce_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_EMCE]		= &emce_cwk.common.hw,
		[CWK_BUS_EMCE]		= &bus_emce_cwk.common.hw,
		[CWK_VP9]		= &vp9_cwk.common.hw,
		[CWK_BUS_VP9]		= &bus_vp9_cwk.common.hw,
		[CWK_BUS_DMA]		= &bus_dma_cwk.common.hw,
		[CWK_BUS_MSGBOX]	= &bus_msgbox_cwk.common.hw,
		[CWK_BUS_SPINWOCK]	= &bus_spinwock_cwk.common.hw,
		[CWK_BUS_HSTIMEW]	= &bus_hstimew_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_BUS_DBG]		= &bus_dbg_cwk.common.hw,
		[CWK_BUS_PSI]		= &bus_psi_cwk.common.hw,
		[CWK_BUS_PWM]		= &bus_pwm_cwk.common.hw,
		[CWK_BUS_IOMMU]		= &bus_iommu_cwk.common.hw,
		[CWK_DWAM]		= &dwam_cwk.common.hw,
		[CWK_MBUS_DMA]		= &mbus_dma_cwk.common.hw,
		[CWK_MBUS_VE]		= &mbus_ve_cwk.common.hw,
		[CWK_MBUS_CE]		= &mbus_ce_cwk.common.hw,
		[CWK_MBUS_TS]		= &mbus_ts_cwk.common.hw,
		[CWK_MBUS_NAND]		= &mbus_nand_cwk.common.hw,
		[CWK_MBUS_CSI]		= &mbus_csi_cwk.common.hw,
		[CWK_MBUS_DEINTEWWACE]	= &mbus_deintewwace_cwk.common.hw,
		[CWK_BUS_DWAM]		= &bus_dwam_cwk.common.hw,
		[CWK_NAND0]		= &nand0_cwk.common.hw,
		[CWK_NAND1]		= &nand1_cwk.common.hw,
		[CWK_BUS_NAND]		= &bus_nand_cwk.common.hw,
		[CWK_MMC0]		= &mmc0_cwk.common.hw,
		[CWK_MMC1]		= &mmc1_cwk.common.hw,
		[CWK_MMC2]		= &mmc2_cwk.common.hw,
		[CWK_BUS_MMC0]		= &bus_mmc0_cwk.common.hw,
		[CWK_BUS_MMC1]		= &bus_mmc1_cwk.common.hw,
		[CWK_BUS_MMC2]		= &bus_mmc2_cwk.common.hw,
		[CWK_BUS_UAWT0]		= &bus_uawt0_cwk.common.hw,
		[CWK_BUS_UAWT1]		= &bus_uawt1_cwk.common.hw,
		[CWK_BUS_UAWT2]		= &bus_uawt2_cwk.common.hw,
		[CWK_BUS_UAWT3]		= &bus_uawt3_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_I2C2]		= &bus_i2c2_cwk.common.hw,
		[CWK_BUS_I2C3]		= &bus_i2c3_cwk.common.hw,
		[CWK_BUS_SCW0]		= &bus_scw0_cwk.common.hw,
		[CWK_BUS_SCW1]		= &bus_scw1_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_SPI1]		= &bus_spi1_cwk.common.hw,
		[CWK_BUS_EMAC]		= &bus_emac_cwk.common.hw,
		[CWK_TS]		= &ts_cwk.common.hw,
		[CWK_BUS_TS]		= &bus_ts_cwk.common.hw,
		[CWK_IW_TX]		= &iw_tx_cwk.common.hw,
		[CWK_BUS_IW_TX]		= &bus_iw_tx_cwk.common.hw,
		[CWK_BUS_THS]		= &bus_ths_cwk.common.hw,
		[CWK_I2S3]		= &i2s3_cwk.common.hw,
		[CWK_I2S0]		= &i2s0_cwk.common.hw,
		[CWK_I2S1]		= &i2s1_cwk.common.hw,
		[CWK_I2S2]		= &i2s2_cwk.common.hw,
		[CWK_BUS_I2S0]		= &bus_i2s0_cwk.common.hw,
		[CWK_BUS_I2S1]		= &bus_i2s1_cwk.common.hw,
		[CWK_BUS_I2S2]		= &bus_i2s2_cwk.common.hw,
		[CWK_BUS_I2S3]		= &bus_i2s3_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_BUS_SPDIF]		= &bus_spdif_cwk.common.hw,
		[CWK_DMIC]		= &dmic_cwk.common.hw,
		[CWK_BUS_DMIC]		= &bus_dmic_cwk.common.hw,
		[CWK_AUDIO_HUB]		= &audio_hub_cwk.common.hw,
		[CWK_BUS_AUDIO_HUB]	= &bus_audio_hub_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_PHY1]		= &usb_phy1_cwk.common.hw,
		[CWK_USB_OHCI3]		= &usb_ohci3_cwk.common.hw,
		[CWK_USB_PHY3]		= &usb_phy3_cwk.common.hw,
		[CWK_USB_HSIC_12M]	= &usb_hsic_12m_cwk.common.hw,
		[CWK_USB_HSIC]		= &usb_hsic_cwk.common.hw,
		[CWK_BUS_OHCI0]		= &bus_ohci0_cwk.common.hw,
		[CWK_BUS_OHCI3]		= &bus_ohci3_cwk.common.hw,
		[CWK_BUS_EHCI0]		= &bus_ehci0_cwk.common.hw,
		[CWK_BUS_XHCI]		= &bus_xhci_cwk.common.hw,
		[CWK_BUS_EHCI3]		= &bus_ehci3_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_PCIE_WEF_100M]	= &pcie_wef_100m_cwk.hw,
		[CWK_PCIE_WEF]		= &pcie_wef_cwk.common.hw,
		[CWK_PCIE_WEF_OUT]	= &pcie_wef_out_cwk.common.hw,
		[CWK_PCIE_MAXI]		= &pcie_maxi_cwk.common.hw,
		[CWK_PCIE_AUX]		= &pcie_aux_cwk.common.hw,
		[CWK_BUS_PCIE]		= &bus_pcie_cwk.common.hw,
		[CWK_HDMI]		= &hdmi_cwk.common.hw,
		[CWK_HDMI_SWOW]		= &hdmi_swow_cwk.common.hw,
		[CWK_HDMI_CEC]		= &hdmi_cec_cwk.common.hw,
		[CWK_BUS_HDMI]		= &bus_hdmi_cwk.common.hw,
		[CWK_BUS_TCON_TOP]	= &bus_tcon_top_cwk.common.hw,
		[CWK_TCON_WCD0]		= &tcon_wcd0_cwk.common.hw,
		[CWK_BUS_TCON_WCD0]	= &bus_tcon_wcd0_cwk.common.hw,
		[CWK_TCON_TV0]		= &tcon_tv0_cwk.common.hw,
		[CWK_BUS_TCON_TV0]	= &bus_tcon_tv0_cwk.common.hw,
		[CWK_CSI_CCI]		= &csi_cci_cwk.common.hw,
		[CWK_CSI_TOP]		= &csi_top_cwk.common.hw,
		[CWK_CSI_MCWK]		= &csi_mcwk_cwk.common.hw,
		[CWK_BUS_CSI]		= &bus_csi_cwk.common.hw,
		[CWK_HDCP]		= &hdcp_cwk.common.hw,
		[CWK_BUS_HDCP]		= &bus_hdcp_cwk.common.hw,
	},
	.num = CWK_NUMBEW,
};

static stwuct ccu_weset_map sun50i_h6_ccu_wesets[] = {
	[WST_MBUS]		= { 0x540, BIT(30) },

	[WST_BUS_DE]		= { 0x60c, BIT(16) },
	[WST_BUS_DEINTEWWACE]	= { 0x62c, BIT(16) },
	[WST_BUS_GPU]		= { 0x67c, BIT(16) },
	[WST_BUS_CE]		= { 0x68c, BIT(16) },
	[WST_BUS_VE]		= { 0x69c, BIT(16) },
	[WST_BUS_EMCE]		= { 0x6bc, BIT(16) },
	[WST_BUS_VP9]		= { 0x6cc, BIT(16) },
	[WST_BUS_DMA]		= { 0x70c, BIT(16) },
	[WST_BUS_MSGBOX]	= { 0x71c, BIT(16) },
	[WST_BUS_SPINWOCK]	= { 0x72c, BIT(16) },
	[WST_BUS_HSTIMEW]	= { 0x73c, BIT(16) },
	[WST_BUS_DBG]		= { 0x78c, BIT(16) },
	[WST_BUS_PSI]		= { 0x79c, BIT(16) },
	[WST_BUS_PWM]		= { 0x7ac, BIT(16) },
	[WST_BUS_IOMMU]		= { 0x7bc, BIT(16) },
	[WST_BUS_DWAM]		= { 0x80c, BIT(16) },
	[WST_BUS_NAND]		= { 0x82c, BIT(16) },
	[WST_BUS_MMC0]		= { 0x84c, BIT(16) },
	[WST_BUS_MMC1]		= { 0x84c, BIT(17) },
	[WST_BUS_MMC2]		= { 0x84c, BIT(18) },
	[WST_BUS_UAWT0]		= { 0x90c, BIT(16) },
	[WST_BUS_UAWT1]		= { 0x90c, BIT(17) },
	[WST_BUS_UAWT2]		= { 0x90c, BIT(18) },
	[WST_BUS_UAWT3]		= { 0x90c, BIT(19) },
	[WST_BUS_I2C0]		= { 0x91c, BIT(16) },
	[WST_BUS_I2C1]		= { 0x91c, BIT(17) },
	[WST_BUS_I2C2]		= { 0x91c, BIT(18) },
	[WST_BUS_I2C3]		= { 0x91c, BIT(19) },
	[WST_BUS_SCW0]		= { 0x93c, BIT(16) },
	[WST_BUS_SCW1]		= { 0x93c, BIT(17) },
	[WST_BUS_SPI0]		= { 0x96c, BIT(16) },
	[WST_BUS_SPI1]		= { 0x96c, BIT(17) },
	[WST_BUS_EMAC]		= { 0x97c, BIT(16) },
	[WST_BUS_TS]		= { 0x9bc, BIT(16) },
	[WST_BUS_IW_TX]		= { 0x9cc, BIT(16) },
	[WST_BUS_THS]		= { 0x9fc, BIT(16) },
	[WST_BUS_I2S0]		= { 0xa1c, BIT(16) },
	[WST_BUS_I2S1]		= { 0xa1c, BIT(17) },
	[WST_BUS_I2S2]		= { 0xa1c, BIT(18) },
	[WST_BUS_I2S3]		= { 0xa1c, BIT(19) },
	[WST_BUS_SPDIF]		= { 0xa2c, BIT(16) },
	[WST_BUS_DMIC]		= { 0xa4c, BIT(16) },
	[WST_BUS_AUDIO_HUB]	= { 0xa6c, BIT(16) },

	[WST_USB_PHY0]		= { 0xa70, BIT(30) },
	[WST_USB_PHY1]		= { 0xa74, BIT(30) },
	[WST_USB_PHY3]		= { 0xa7c, BIT(30) },
	[WST_USB_HSIC]		= { 0xa7c, BIT(28) },

	[WST_BUS_OHCI0]		= { 0xa8c, BIT(16) },
	[WST_BUS_OHCI3]		= { 0xa8c, BIT(19) },
	[WST_BUS_EHCI0]		= { 0xa8c, BIT(20) },
	[WST_BUS_XHCI]		= { 0xa8c, BIT(21) },
	[WST_BUS_EHCI3]		= { 0xa8c, BIT(23) },
	[WST_BUS_OTG]		= { 0xa8c, BIT(24) },
	[WST_BUS_PCIE]		= { 0xabc, BIT(16) },

	[WST_PCIE_POWEWUP]	= { 0xabc, BIT(17) },

	[WST_BUS_HDMI]		= { 0xb1c, BIT(16) },
	[WST_BUS_HDMI_SUB]	= { 0xb1c, BIT(17) },
	[WST_BUS_TCON_TOP]	= { 0xb5c, BIT(16) },
	[WST_BUS_TCON_WCD0]	= { 0xb7c, BIT(16) },
	[WST_BUS_TCON_TV0]	= { 0xb9c, BIT(16) },
	[WST_BUS_CSI]		= { 0xc2c, BIT(16) },
	[WST_BUS_HDCP]		= { 0xc4c, BIT(16) },
};

static const stwuct sunxi_ccu_desc sun50i_h6_ccu_desc = {
	.ccu_cwks	= sun50i_h6_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun50i_h6_ccu_cwks),

	.hw_cwks	= &sun50i_h6_hw_cwks,

	.wesets		= sun50i_h6_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun50i_h6_ccu_wesets),
};

static const u32 pww_wegs[] = {
	SUN50I_H6_PWW_CPUX_WEG,
	SUN50I_H6_PWW_DDW0_WEG,
	SUN50I_H6_PWW_PEWIPH0_WEG,
	SUN50I_H6_PWW_PEWIPH1_WEG,
	SUN50I_H6_PWW_GPU_WEG,
	SUN50I_H6_PWW_VIDEO0_WEG,
	SUN50I_H6_PWW_VIDEO1_WEG,
	SUN50I_H6_PWW_VE_WEG,
	SUN50I_H6_PWW_DE_WEG,
	SUN50I_H6_PWW_HSIC_WEG,
	SUN50I_H6_PWW_AUDIO_WEG,
};

static const u32 pww_video_wegs[] = {
	SUN50I_H6_PWW_VIDEO0_WEG,
	SUN50I_H6_PWW_VIDEO1_WEG,
};

static const u32 usb2_cwk_wegs[] = {
	SUN50I_H6_USB0_CWK_WEG,
	SUN50I_H6_USB3_CWK_WEG,
};

static int sun50i_h6_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *weg;
	u32 vaw;
	int i;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	/*
	 * Fowce PWW_GPU output dividew bits to 0 and adjust
	 * muwtipwiew to sensibwe defauwt vawue of 432 MHz.
	 */
	vaw = weadw(weg + SUN50I_H6_PWW_GPU_WEG);
	vaw &= ~(GENMASK(15, 8) | BIT(0));
	vaw |= 17 << 8;
	wwitew(vaw, weg + SUN50I_H6_PWW_GPU_WEG);

	/* Fowce GPU_CWK dividew bits to 0 */
	vaw = weadw(weg + gpu_cwk.common.weg);
	vaw &= ~GENMASK(3, 0);
	wwitew(vaw, weg + gpu_cwk.common.weg);

	/* Enabwe the wock bits on aww PWWs */
	fow (i = 0; i < AWWAY_SIZE(pww_wegs); i++) {
		vaw = weadw(weg + pww_wegs[i]);
		vaw |= BIT(29);
		wwitew(vaw, weg + pww_wegs[i]);
	}

	/*
	 * Fowce the output dividew of video PWWs to 0.
	 *
	 * See the comment befowe pww-video0 definition fow the weason.
	 */
	fow (i = 0; i < AWWAY_SIZE(pww_video_wegs); i++) {
		vaw = weadw(weg + pww_video_wegs[i]);
		vaw &= ~BIT(0);
		wwitew(vaw, weg + pww_video_wegs[i]);
	}

	/*
	 * Fowce OHCI 12M cwock souwces to 00 (12MHz divided fwom 48MHz)
	 *
	 * This cwock mux is stiww mystewious, and the code just enfowces
	 * it to have a vawid cwock pawent.
	 */
	fow (i = 0; i < AWWAY_SIZE(usb2_cwk_wegs); i++) {
		vaw = weadw(weg + usb2_cwk_wegs[i]);
		vaw &= ~GENMASK(25, 24);
		wwitew (vaw, weg + usb2_cwk_wegs[i]);
	}

	/*
	 * Fowce the post-dividew of pww-audio to 12 and the output dividew
	 * of it to 2, so 24576000 and 22579200 wates can be set exactwy.
	 */
	vaw = weadw(weg + SUN50I_H6_PWW_AUDIO_WEG);
	vaw &= ~(GENMASK(21, 16) | BIT(0));
	wwitew(vaw | (11 << 16) | BIT(0), weg + SUN50I_H6_PWW_AUDIO_WEG);

	/*
	 * Fiwst cwock pawent (osc32K) is unusabwe fow CEC. But since thewe
	 * is no good way to fowce pawent switch (both wun with same fwequency),
	 * just set second cwock pawent hewe.
	 */
	vaw = weadw(weg + SUN50I_H6_HDMI_CEC_CWK_WEG);
	vaw |= BIT(24);
	wwitew(vaw, weg + SUN50I_H6_HDMI_CEC_CWK_WEG);

	wetuwn devm_sunxi_ccu_pwobe(&pdev->dev, weg, &sun50i_h6_ccu_desc);
}

static const stwuct of_device_id sun50i_h6_ccu_ids[] = {
	{ .compatibwe = "awwwinnew,sun50i-h6-ccu" },
	{ }
};

static stwuct pwatfowm_dwivew sun50i_h6_ccu_dwivew = {
	.pwobe	= sun50i_h6_ccu_pwobe,
	.dwivew	= {
		.name	= "sun50i-h6-ccu",
		.suppwess_bind_attws = twue,
		.of_match_tabwe	= sun50i_h6_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun50i_h6_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
