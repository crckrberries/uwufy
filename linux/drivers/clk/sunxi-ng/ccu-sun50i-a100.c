// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Yangtao Wi <fwank@awwwinnewtech.com>
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

#incwude "ccu-sun50i-a100.h"

#define SUN50I_A100_PWW_SDM_ENABWE		BIT(24)
#define SUN50I_A100_PWW_OUTPUT_ENABWE		BIT(27)
#define SUN50I_A100_PWW_WOCK			BIT(28)
#define SUN50I_A100_PWW_WOCK_ENABWE		BIT(29)
#define SUN50I_A100_PWW_ENABWE			BIT(31)

#define SUN50I_A100_PWW_PEWIPH1_PATTEWN0	0xd1303333

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
#define SUN50I_A100_PWW_CPUX_WEG		0x000
static stwuct ccu_muwt pww_cpux_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.muwt		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.common		= {
		.weg		= 0x000,
		.hw.init	= CWK_HW_INIT("pww-cpux", "dcxo24M",
					      &ccu_muwt_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/* Some PWWs awe input * N / div1 / P. Modew them as NKMP with no K */
#define SUN50I_A100_PWW_DDW0_WEG		0x010
static stwuct ccu_nkmp pww_ddw0_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x010,
		.hw.init	= CWK_HW_INIT("pww-ddw0", "dcxo24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE |
					      CWK_IS_CWITICAW),
	},
};

#define SUN50I_A100_PWW_PEWIPH0_WEG	0x020
static stwuct ccu_nkmp pww_pewiph0_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.fixed_post_div	= 2,
	.common		= {
		.weg		= 0x020,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph0", "dcxo24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_A100_PWW_PEWIPH1_WEG	0x028
static stwuct ccu_nkmp pww_pewiph1_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.fixed_post_div	= 2,
	.common		= {
		.weg		= 0x028,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-pewiph1", "dcxo24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};
#define SUN50I_A100_PWW_PEWIPH1_PATTEWN0_WEG	0x128

#define SUN50I_A100_PWW_GPU_WEG		0x030
static stwuct ccu_nkmp pww_gpu_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x030,
		.hw.init	= CWK_HW_INIT("pww-gpu", "dcxo24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/*
 * Fow Video PWWs, the output dividew is descwibed as "used fow testing"
 * in the usew manuaw. So it's not modewwed and fowced to 0.
 */
#define SUN50I_A100_PWW_VIDEO0_WEG	0x040
static stwuct ccu_nm pww_video0_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.fixed_post_div	= 4,
	.common		= {
		.weg		= 0x040,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-video0", "dcxo24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_A100_PWW_VIDEO1_WEG	0x048
static stwuct ccu_nm pww_video1_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.fixed_post_div	= 4,
	.common		= {
		.weg		= 0x048,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-video1", "dcxo24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_A100_PWW_VIDEO2_WEG	0x050
static stwuct ccu_nm pww_video2_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.fixed_post_div	= 4,
	.common		= {
		.weg		= 0x050,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-video2", "dcxo24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_A100_PWW_VE_WEG		0x058
static stwuct ccu_nkmp pww_ve_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x058,
		.hw.init	= CWK_HW_INIT("pww-ve", "dcxo24M",
					      &ccu_nkmp_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/*
 * The COM PWW has m0 dividews in addition to the usuaw N, M
 * factows. Since we onwy need 1 fwequencies fwom this PWW: 45.1584 MHz,
 * ignowe it fow now.
 */
#define SUN50I_A100_PWW_COM_WEG		0x060
static stwuct ccu_sdm_setting pww_com_sdm_tabwe[] = {
	{ .wate = 451584000, .pattewn = 0xc0014396, .m = 2, .n = 37 },
};

static stwuct ccu_nm pww_com_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(0, 1),
	.sdm		= _SUNXI_CCU_SDM(pww_com_sdm_tabwe, BIT(24),
					 0x160, BIT(31)),
	.common		= {
		.weg		= 0x060,
		.featuwes	= CCU_FEATUWE_SIGMA_DEWTA_MOD,
		.hw.init	= CWK_HW_INIT("pww-com", "dcxo24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

#define SUN50I_A100_PWW_VIDEO3_WEG	0x068
static stwuct ccu_nm pww_video3_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.fixed_post_div	= 4,
	.common		= {
		.weg		= 0x068,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV,
		.hw.init	= CWK_HW_INIT("pww-video3", "dcxo24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

/*
 * The Audio PWW has m0, m1 dividews in addition to the usuaw N, M
 * factows. Since we onwy need 4 fwequencies fwom this PWW: 22.5792 MHz,
 * 24.576 MHz, 90.3168MHz and 98.304MHz ignowe them fow now.
 * Enfowce the defauwt fow them, which is m0 = 1, m1 = 0.
 */
#define SUN50I_A100_PWW_AUDIO_WEG		0x078
static stwuct ccu_sdm_setting pww_audio_sdm_tabwe[] = {
	{ .wate = 45158400, .pattewn = 0xc001bcd3, .m = 18, .n = 33 },
	{ .wate = 49152000, .pattewn = 0xc001eb85, .m = 20, .n = 40 },
	{ .wate = 180633600, .pattewn = 0xc001288d, .m = 3, .n = 22 },
	{ .wate = 196608000, .pattewn = 0xc001eb85, .m = 5, .n = 40 },
};

static stwuct ccu_nm pww_audio_cwk = {
	.enabwe		= SUN50I_A100_PWW_OUTPUT_ENABWE,
	.wock		= SUN50I_A100_PWW_WOCK,
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(16, 6),
	.fixed_post_div	= 2,
	.sdm		= _SUNXI_CCU_SDM(pww_audio_sdm_tabwe, BIT(24),
					 0x178, BIT(31)),
	.common		= {
		.weg		= 0x078,
		.featuwes	= CCU_FEATUWE_FIXED_POSTDIV |
				  CCU_FEATUWE_SIGMA_DEWTA_MOD,
		.hw.init	= CWK_HW_INIT("pww-audio", "dcxo24M",
					      &ccu_nm_ops,
					      CWK_SET_WATE_UNGATE),
	},
};

static const chaw * const cpux_pawents[] = { "dcxo24M", "osc32k",
					     "iosc", "pww-cpux",
					      "pww-pewiph0" };
static SUNXI_CCU_MUX(cpux_cwk, "cpux", cpux_pawents,
		     0x500, 24, 3, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);
static SUNXI_CCU_M(axi_cwk, "axi", "cpux", 0x500, 0, 2, 0);
static SUNXI_CCU_M(cpux_apb_cwk, "cpux-apb", "cpux", 0x500, 8, 2, 0);

static const chaw * const psi_ahb1_ahb2_pawents[] = { "dcxo24M", "osc32k",
						      "iosc", "pww-pewiph0",
						      "pww-pewiph0-2x" };
static SUNXI_CCU_MP_WITH_MUX(psi_ahb1_ahb2_cwk, "psi-ahb1-ahb2",
			     psi_ahb1_ahb2_pawents, 0x510,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 3,	/* mux */
			     0);

static const chaw * const ahb3_apb1_apb2_pawents[] = { "dcxo24M", "osc32k",
						       "psi-ahb1-ahb2",
						       "pww-pewiph0",
						       "pww-pewiph0-2x" };
static SUNXI_CCU_MP_WITH_MUX(ahb3_cwk, "ahb3", ahb3_apb1_apb2_pawents, 0x51c,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 3,	/* mux */
			     0);

static SUNXI_CCU_MP_WITH_MUX(apb1_cwk, "apb1", ahb3_apb1_apb2_pawents, 0x520,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 3,	/* mux */
			     0);

static SUNXI_CCU_MP_WITH_MUX(apb2_cwk, "apb2", ahb3_apb1_apb2_pawents, 0x524,
			     0, 2,	/* M */
			     8, 2,	/* P */
			     24, 3,	/* mux */
			     0);

static const chaw * const mbus_pawents[] = { "dcxo24M", "pww-ddw0",
					     "pww-pewiph0",
					     "pww-pewiph0-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(mbus_cwk, "mbus", mbus_pawents, 0x540,
				 0, 3,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 CWK_IS_CWITICAW);

static const chaw * const de_pawents[] = { "pww-com", "pww-pewiph0-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(de_cwk, "de0", de_pawents, 0x600,
				 0, 4,		/* M */
				 24, 1,		/* mux */
				 BIT(31),	/* gate */
				 CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(bus_de_cwk, "bus-de", "psi-ahb1-ahb2",
		      0x60c, BIT(0), 0);

static const chaw * const g2d_pawents[] = { "pww-com", "pww-pewiph0-2x",
					     "pww-video0-2x", "pww-video1-2x",
					     "pww-video2-2x"};
static SUNXI_CCU_M_WITH_MUX_GATE(g2d_cwk, "g2d",
				 g2d_pawents,
				 0x630,
				 0, 4,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_GATE(bus_g2d_cwk, "bus-g2d", "psi-ahb1-ahb2",
		      0x63c, BIT(0), 0);

static const chaw * const gpu_pawents[] = { "pww-gpu" };
static SUNXI_CCU_M_WITH_MUX_GATE(gpu_cwk, "gpu", gpu_pawents, 0x670,
				       0, 2,	/* M */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE(bus_gpu_cwk, "bus-gpu", "psi-ahb1-ahb2",
		      0x67c, BIT(0), 0);

static const chaw * const ce_pawents[] = { "dcxo24M", "pww-pewiph0-2x" };
static SUNXI_CCU_MP_WITH_MUX_GATE(ce_cwk, "ce", ce_pawents, 0x680,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 1,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_GATE(bus_ce_cwk, "bus-ce", "psi-ahb1-ahb2",
		      0x68c, BIT(0), 0);

static const chaw * const ve_pawents[] = { "pww-ve" };
static SUNXI_CCU_M_WITH_MUX_GATE(ve_cwk, "ve", ve_pawents, 0x690,
				 0, 3,		/* M */
				 24, 1,		/* mux */
				 BIT(31),	/* gate */
				 CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE(bus_ve_cwk, "bus-ve", "psi-ahb1-ahb2",
		      0x69c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_dma_cwk, "bus-dma", "psi-ahb1-ahb2",
		      0x70c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_msgbox_cwk, "bus-msgbox", "psi-ahb1-ahb2",
		      0x71c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_spinwock_cwk, "bus-spinwock", "psi-ahb1-ahb2",
		      0x72c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_hstimew_cwk, "bus-hstimew", "psi-ahb1-ahb2",
		      0x73c, BIT(0), 0);

static SUNXI_CCU_GATE(avs_cwk, "avs", "dcxo24M", 0x740, BIT(31), 0);

static SUNXI_CCU_GATE(bus_dbg_cwk, "bus-dbg", "psi-ahb1-ahb2",
		      0x78c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_psi_cwk, "bus-psi", "psi-ahb1-ahb2",
		      0x79c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_pwm_cwk, "bus-pwm", "apb1", 0x7ac, BIT(0), 0);

static SUNXI_CCU_GATE(bus_iommu_cwk, "bus-iommu", "apb1", 0x7bc, BIT(0), 0);

static SUNXI_CCU_GATE(mbus_dma_cwk, "mbus-dma", "mbus",
		      0x804, BIT(0), 0);
static SUNXI_CCU_GATE(mbus_ve_cwk, "mbus-ve", "mbus",
		      0x804, BIT(1), 0);
static SUNXI_CCU_GATE(mbus_ce_cwk, "mbus-ce", "mbus",
		      0x804, BIT(2), 0);
static SUNXI_CCU_GATE(mbus_nand_cwk, "mbus-nand", "mbus",
		      0x804, BIT(5), 0);
static SUNXI_CCU_GATE(mbus_csi_cwk, "mbus-csi", "mbus",
		      0x804, BIT(8), 0);
static SUNXI_CCU_GATE(mbus_isp_cwk, "mbus-isp", "mbus",
		      0x804, BIT(9), 0);
static SUNXI_CCU_GATE(mbus_g2d_cwk, "mbus-g2d", "mbus",
		      0x804, BIT(10), 0);

static SUNXI_CCU_GATE(bus_dwam_cwk, "bus-dwam", "psi-ahb1-ahb2",
		      0x80c, BIT(0), CWK_IS_CWITICAW);

static const chaw * const nand_spi_pawents[] = { "dcxo24M",
						 "pww-pewiph0",
						 "pww-pewiph1",
						 "pww-pewiph0-2x",
						 "pww-pewiph1-2x" };
static SUNXI_CCU_MP_WITH_MUX_GATE(nand0_cwk, "nand0", nand_spi_pawents, 0x810,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(nand1_cwk, "nand1", nand_spi_pawents, 0x814,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_GATE(bus_nand_cwk, "bus-nand", "ahb3", 0x82c, BIT(0), 0);

static const chaw * const mmc_pawents[] = { "dcxo24M", "pww-pewiph0-2x",
					    "pww-pewiph1-2x" };
static SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc0_cwk, "mmc0", mmc_pawents, 0x830,
					  0, 4,		/* M */
					  8, 2,		/* P */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-div */
					  CWK_SET_WATE_NO_WEPAWENT);

static SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc1_cwk, "mmc1", mmc_pawents, 0x834,
					  0, 4,		/* M */
					  8, 2,		/* P */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-div */
					  CWK_SET_WATE_NO_WEPAWENT);

static SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(mmc2_cwk, "mmc2", mmc_pawents, 0x838,
					  0, 4,		/* M */
					  8, 2,		/* P */
					  24, 2,	/* mux */
					  BIT(31),	/* gate */
					  2,		/* post-div */
					  CWK_SET_WATE_NO_WEPAWENT);

static SUNXI_CCU_GATE(bus_mmc0_cwk, "bus-mmc0", "ahb3", 0x84c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_mmc1_cwk, "bus-mmc1", "ahb3", 0x84c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_mmc2_cwk, "bus-mmc2", "ahb3", 0x84c, BIT(2), 0);

static SUNXI_CCU_GATE(bus_uawt0_cwk, "bus-uawt0", "apb2", 0x90c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_uawt1_cwk, "bus-uawt1", "apb2", 0x90c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_uawt2_cwk, "bus-uawt2", "apb2", 0x90c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_uawt3_cwk, "bus-uawt3", "apb2", 0x90c, BIT(3), 0);
static SUNXI_CCU_GATE(bus_uawt4_cwk, "bus-uawt4", "apb2", 0x90c, BIT(4), 0);

static SUNXI_CCU_GATE(bus_i2c0_cwk, "bus-i2c0", "apb2", 0x91c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2c1_cwk, "bus-i2c1", "apb2", 0x91c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_i2c2_cwk, "bus-i2c2", "apb2", 0x91c, BIT(2), 0);
static SUNXI_CCU_GATE(bus_i2c3_cwk, "bus-i2c3", "apb2", 0x91c, BIT(3), 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi0_cwk, "spi0", nand_spi_pawents, 0x940,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi1_cwk, "spi1", nand_spi_pawents, 0x944,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_MP_WITH_MUX_GATE(spi2_cwk, "spi2", nand_spi_pawents, 0x948,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_GATE(bus_spi0_cwk, "bus-spi0", "ahb3", 0x96c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_spi1_cwk, "bus-spi1", "ahb3", 0x96c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_spi2_cwk, "bus-spi2", "ahb3", 0x96c, BIT(2), 0);

static SUNXI_CCU_GATE(emac_25m_cwk, "emac-25m", "ahb3", 0x970,
		      BIT(31) | BIT(30), 0);

static SUNXI_CCU_GATE(bus_emac_cwk, "bus-emac", "ahb3", 0x97c, BIT(0), 0);

static const chaw * const iw_pawents[] = { "osc32k", "iosc",
					   "pww-pewiph0", "pww-pewiph1" };
static SUNXI_CCU_MP_WITH_MUX_GATE(iw_wx_cwk, "iw-wx", iw_pawents, 0x990,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_GATE(bus_iw_wx_cwk, "bus-iw-wx", "ahb3", 0x99c, BIT(0), 0);

static SUNXI_CCU_MP_WITH_MUX_GATE(iw_tx_cwk, "iw-tx", iw_pawents, 0x9c0,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_GATE(bus_iw_tx_cwk, "bus-iw-tx", "apb1", 0x9cc, BIT(0), 0);

static SUNXI_CCU_GATE(bus_gpadc_cwk, "bus-gpadc", "apb1", 0x9ec, BIT(0), 0);

static SUNXI_CCU_GATE(bus_ths_cwk, "bus-ths", "apb1", 0x9fc, BIT(0), 0);

static const chaw * const audio_pawents[] = { "pww-audio", "pww-com-audio" };
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

static stwuct ccu_div i2s3_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa1c,
		.hw.init	= CWK_HW_INIT_PAWENTS("i2s3",
						      audio_pawents,
						      &ccu_div_ops,
						      CWK_SET_WATE_PAWENT),
	},
};

static SUNXI_CCU_GATE(bus_i2s0_cwk, "bus-i2s0", "apb1", 0xa20, BIT(0), 0);
static SUNXI_CCU_GATE(bus_i2s1_cwk, "bus-i2s1", "apb1", 0xa20, BIT(1), 0);
static SUNXI_CCU_GATE(bus_i2s2_cwk, "bus-i2s2", "apb1", 0xa20, BIT(2), 0);
static SUNXI_CCU_GATE(bus_i2s3_cwk, "bus-i2s3", "apb1", 0xa20, BIT(3), 0);

static stwuct ccu_div spdif_cwk = {
	.enabwe		= BIT(31),
	.div		= _SUNXI_CCU_DIV_FWAGS(8, 2, CWK_DIVIDEW_POWEW_OF_TWO),
	.mux		= _SUNXI_CCU_MUX(24, 2),
	.common		= {
		.weg		= 0xa24,
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

static SUNXI_CCU_M_WITH_MUX_GATE(audio_codec_dac_cwk, "audio-codec-dac",
				 audio_pawents, 0xa50,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_M_WITH_MUX_GATE(audio_codec_adc_cwk, "audio-codec-adc",
				 audio_pawents, 0xa54,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_M_WITH_MUX_GATE(audio_codec_4x_cwk, "audio-codec-4x",
				 audio_pawents, 0xa58,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_GATE(bus_audio_codec_cwk, "bus-audio-codec", "apb1", 0xa5c,
		      BIT(0), 0);

/*
 * Thewe awe OHCI 12M cwock souwce sewection bits fow 2 USB 2.0 powts.
 * We wiww fowce them to 0 (12M divided fwom 48M).
 */
#define SUN50I_A100_USB0_CWK_WEG		0xa70
#define SUN50I_A100_USB1_CWK_WEG		0xa74

static SUNXI_CCU_GATE(usb_ohci0_cwk, "usb-ohci0", "osc12M", 0xa70, BIT(31), 0);
static SUNXI_CCU_GATE(usb_phy0_cwk, "usb-phy0", "dcxo24M", 0xa70, BIT(29), 0);

static SUNXI_CCU_GATE(usb_ohci1_cwk, "usb-ohci1", "osc12M", 0xa74, BIT(31), 0);
static SUNXI_CCU_GATE(usb_phy1_cwk, "usb-phy1", "dcxo24M", 0xa74, BIT(29), 0);

static SUNXI_CCU_GATE(bus_ohci0_cwk, "bus-ohci0", "ahb3", 0xa8c, BIT(0), 0);
static SUNXI_CCU_GATE(bus_ohci1_cwk, "bus-ohci1", "ahb3", 0xa8c, BIT(1), 0);
static SUNXI_CCU_GATE(bus_ehci0_cwk, "bus-ehci0", "ahb3", 0xa8c, BIT(4), 0);
static SUNXI_CCU_GATE(bus_ehci1_cwk, "bus-ehci1", "ahb3", 0xa8c, BIT(5), 0);
static SUNXI_CCU_GATE(bus_otg_cwk, "bus-otg", "ahb3", 0xa8c, BIT(8), 0);

static SUNXI_CCU_GATE(bus_wwadc_cwk, "bus-wwadc", "ahb3", 0xa9c, BIT(0), 0);

static SUNXI_CCU_GATE(bus_dpss_top0_cwk, "bus-dpss-top0", "ahb3",
		      0xabc, BIT(0), 0);

static SUNXI_CCU_GATE(bus_dpss_top1_cwk, "bus-dpss-top1", "ahb3",
		      0xacc, BIT(0), 0);

static const chaw * const mipi_dsi_pawents[] = { "dcxo24M", "pww-pewiph0-2x",
						 "pww-pewiph0" };
static SUNXI_CCU_M_WITH_MUX_GATE(mipi_dsi_cwk, "mipi-dsi",
				 mipi_dsi_pawents,
				 0xb24,
				 0, 4,		/* M */
				 24, 2,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_GATE(bus_mipi_dsi_cwk, "bus-mipi-dsi", "ahb3",
		      0xb4c, BIT(0), 0);

static const chaw * const tcon_wcd_pawents[] = { "pww-video0-4x",
						  "pww-video1-4x",
						  "pww-video2-4x",
						  "pww-video3-4x",
						  "pww-pewiph0-2x" };
static SUNXI_CCU_MP_WITH_MUX_GATE(tcon_wcd_cwk, "tcon-wcd0",
				  tcon_wcd_pawents, 0xb60,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_GATE(bus_tcon_wcd_cwk, "bus-tcon-wcd0", "ahb3",
		      0xb7c, BIT(0), 0);

static const chaw * const wedc_pawents[] = { "dcxo24M",
					     "pww-pewiph0" };
static SUNXI_CCU_MP_WITH_MUX_GATE(wedc_cwk, "wedc",
				  wedc_pawents, 0xbf0,
				  0, 4,		/* M */
				  8, 2,		/* P */
				  24, 3,	/* mux */
				  BIT(31),	/* gate */
				  0);

static SUNXI_CCU_GATE(bus_wedc_cwk, "bus-wedc", "ahb3", 0xbfc, BIT(0), 0);

static const chaw * const csi_top_pawents[] = { "pww-pewiph0-2x",
						"pww-video0-2x",
						"pww-video1-2x",
						"pww-video2-2x",
						"pww-video3-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi_top_cwk, "csi-top",
				 csi_top_pawents, 0xc04,
				 0, 4,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

static const chaw * const csi0_mcwk_pawents[] = { "dcxo24M", "pww-video2",
						  "pww-video3", "pww-video0",
						  "pww-video1" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi0_mcwk_cwk, "csi0-mcwk",
				 csi0_mcwk_pawents, 0xc08,
				 0, 5,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

static const chaw * const csi1_mcwk_pawents[] = { "dcxo24M", "pww-video3",
						  "pww-video0", "pww-video1",
						  "pww-video2" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi1_mcwk_cwk, "csi1-mcwk",
				 csi1_mcwk_pawents, 0xc0c,
				 0, 5,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

static SUNXI_CCU_GATE(bus_csi_cwk, "bus-csi", "ahb3", 0xc1c, BIT(0), 0);

static const chaw * const csi_isp_pawents[] = { "pww-pewiph0-2x",
						"pww-video0-2x",
						"pww-video1-2x",
						"pww-video2-2x",
						"pww-video3-2x" };
static SUNXI_CCU_M_WITH_MUX_GATE(csi_isp_cwk, "csi-isp",
				 csi_isp_pawents, 0xc20,
				 0, 5,		/* M */
				 24, 3,		/* mux */
				 BIT(31),	/* gate */
				 0);

/* Fixed factow cwocks */
static CWK_FIXED_FACTOW_FW_NAME(osc12M_cwk, "osc12M", "hosc", 2, 1, 0);

static CWK_FIXED_FACTOW_HW(pww_com_audio_cwk, "pww-com-audio",
			   &pww_com_cwk.common.hw,
			   5, 1, CWK_SET_WATE_PAWENT);

static CWK_FIXED_FACTOW_HW(pww_pewiph0_2x_cwk, "pww-pewiph0-2x",
			   &pww_pewiph0_cwk.common.hw,
			   1, 2, 0);

static CWK_FIXED_FACTOW_HW(pww_pewiph1_2x_cwk, "pww-pewiph1-2x",
			   &pww_pewiph1_cwk.common.hw,
			   1, 2, 0);

static const stwuct cwk_hw *pww_video0_pawents[] = {
	&pww_video0_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_video0_4x_cwk, "pww-video0-4x",
			    pww_video0_pawents,
			    1, 4, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_video0_2x_cwk, "pww-video0-2x",
			    pww_video0_pawents,
			    1, 2, CWK_SET_WATE_PAWENT);

static const stwuct cwk_hw *pww_video1_pawents[] = {
	&pww_video1_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_video1_4x_cwk, "pww-video1-4x",
			    pww_video1_pawents,
			    1, 4, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_video1_2x_cwk, "pww-video1-2x",
			    pww_video1_pawents,
			    1, 2, CWK_SET_WATE_PAWENT);

static const stwuct cwk_hw *pww_video2_pawents[] = {
	&pww_video2_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_video2_4x_cwk, "pww-video2-4x",
			    pww_video2_pawents,
			    1, 4, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_video2_2x_cwk, "pww-video2-2x",
			    pww_video2_pawents,
			    1, 2, CWK_SET_WATE_PAWENT);

static const stwuct cwk_hw *pww_video3_pawents[] = {
	&pww_video3_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_video3_4x_cwk, "pww-video3-4x",
			    pww_video3_pawents,
			    1, 4, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_video3_2x_cwk, "pww-video3-2x",
			    pww_video3_pawents,
			    1, 2, CWK_SET_WATE_PAWENT);

static stwuct ccu_common *sun50i_a100_ccu_cwks[] = {
	&pww_cpux_cwk.common,
	&pww_ddw0_cwk.common,
	&pww_pewiph0_cwk.common,
	&pww_pewiph1_cwk.common,
	&pww_gpu_cwk.common,
	&pww_video0_cwk.common,
	&pww_video1_cwk.common,
	&pww_video2_cwk.common,
	&pww_video3_cwk.common,
	&pww_ve_cwk.common,
	&pww_com_cwk.common,
	&pww_audio_cwk.common,
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
	&g2d_cwk.common,
	&bus_g2d_cwk.common,
	&gpu_cwk.common,
	&bus_gpu_cwk.common,
	&ce_cwk.common,
	&bus_ce_cwk.common,
	&ve_cwk.common,
	&bus_ve_cwk.common,
	&bus_dma_cwk.common,
	&bus_msgbox_cwk.common,
	&bus_spinwock_cwk.common,
	&bus_hstimew_cwk.common,
	&avs_cwk.common,
	&bus_dbg_cwk.common,
	&bus_psi_cwk.common,
	&bus_pwm_cwk.common,
	&bus_iommu_cwk.common,
	&mbus_dma_cwk.common,
	&mbus_ve_cwk.common,
	&mbus_ce_cwk.common,
	&mbus_nand_cwk.common,
	&mbus_csi_cwk.common,
	&mbus_isp_cwk.common,
	&mbus_g2d_cwk.common,
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
	&bus_uawt4_cwk.common,
	&bus_i2c0_cwk.common,
	&bus_i2c1_cwk.common,
	&bus_i2c2_cwk.common,
	&bus_i2c3_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&spi2_cwk.common,
	&bus_spi0_cwk.common,
	&bus_spi1_cwk.common,
	&bus_spi2_cwk.common,
	&emac_25m_cwk.common,
	&bus_emac_cwk.common,
	&iw_wx_cwk.common,
	&bus_iw_wx_cwk.common,
	&iw_tx_cwk.common,
	&bus_iw_tx_cwk.common,
	&bus_gpadc_cwk.common,
	&bus_ths_cwk.common,
	&i2s0_cwk.common,
	&i2s1_cwk.common,
	&i2s2_cwk.common,
	&i2s3_cwk.common,
	&bus_i2s0_cwk.common,
	&bus_i2s1_cwk.common,
	&bus_i2s2_cwk.common,
	&bus_i2s3_cwk.common,
	&spdif_cwk.common,
	&bus_spdif_cwk.common,
	&dmic_cwk.common,
	&bus_dmic_cwk.common,
	&audio_codec_dac_cwk.common,
	&audio_codec_adc_cwk.common,
	&audio_codec_4x_cwk.common,
	&bus_audio_codec_cwk.common,
	&usb_ohci0_cwk.common,
	&usb_phy0_cwk.common,
	&usb_ohci1_cwk.common,
	&usb_phy1_cwk.common,
	&bus_ohci0_cwk.common,
	&bus_ohci1_cwk.common,
	&bus_ehci0_cwk.common,
	&bus_ehci1_cwk.common,
	&bus_otg_cwk.common,
	&bus_wwadc_cwk.common,
	&bus_dpss_top0_cwk.common,
	&bus_dpss_top1_cwk.common,
	&mipi_dsi_cwk.common,
	&bus_mipi_dsi_cwk.common,
	&tcon_wcd_cwk.common,
	&bus_tcon_wcd_cwk.common,
	&wedc_cwk.common,
	&bus_wedc_cwk.common,
	&csi_top_cwk.common,
	&csi0_mcwk_cwk.common,
	&csi1_mcwk_cwk.common,
	&bus_csi_cwk.common,
	&csi_isp_cwk.common,
};

static stwuct cwk_hw_oneceww_data sun50i_a100_hw_cwks = {
	.hws	= {
		[CWK_OSC12M]		= &osc12M_cwk.hw,
		[CWK_PWW_CPUX]		= &pww_cpux_cwk.common.hw,
		[CWK_PWW_DDW0]		= &pww_ddw0_cwk.common.hw,
		[CWK_PWW_PEWIPH0]	= &pww_pewiph0_cwk.common.hw,
		[CWK_PWW_PEWIPH0_2X]	= &pww_pewiph0_2x_cwk.hw,
		[CWK_PWW_PEWIPH1]	= &pww_pewiph1_cwk.common.hw,
		[CWK_PWW_PEWIPH1_2X]	= &pww_pewiph1_2x_cwk.hw,
		[CWK_PWW_GPU]		= &pww_gpu_cwk.common.hw,
		[CWK_PWW_VIDEO0]	= &pww_video0_cwk.common.hw,
		[CWK_PWW_VIDEO0_2X]	= &pww_video0_2x_cwk.hw,
		[CWK_PWW_VIDEO0_4X]	= &pww_video0_4x_cwk.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.common.hw,
		[CWK_PWW_VIDEO1_2X]	= &pww_video1_2x_cwk.hw,
		[CWK_PWW_VIDEO1_4X]	= &pww_video1_4x_cwk.hw,
		[CWK_PWW_VIDEO2]	= &pww_video2_cwk.common.hw,
		[CWK_PWW_VIDEO2_2X]	= &pww_video2_2x_cwk.hw,
		[CWK_PWW_VIDEO2_4X]	= &pww_video2_4x_cwk.hw,
		[CWK_PWW_VIDEO3]	= &pww_video3_cwk.common.hw,
		[CWK_PWW_VIDEO3_2X]	= &pww_video3_2x_cwk.hw,
		[CWK_PWW_VIDEO3_4X]	= &pww_video3_4x_cwk.hw,
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_COM]		= &pww_com_cwk.common.hw,
		[CWK_PWW_COM_AUDIO]	= &pww_com_audio_cwk.hw,
		[CWK_PWW_AUDIO]		= &pww_audio_cwk.common.hw,
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
		[CWK_G2D]		= &g2d_cwk.common.hw,
		[CWK_BUS_G2D]		= &bus_g2d_cwk.common.hw,
		[CWK_GPU]		= &gpu_cwk.common.hw,
		[CWK_BUS_GPU]		= &bus_gpu_cwk.common.hw,
		[CWK_CE]		= &ce_cwk.common.hw,
		[CWK_BUS_CE]		= &bus_ce_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_BUS_DMA]		= &bus_dma_cwk.common.hw,
		[CWK_BUS_MSGBOX]	= &bus_msgbox_cwk.common.hw,
		[CWK_BUS_SPINWOCK]	= &bus_spinwock_cwk.common.hw,
		[CWK_BUS_HSTIMEW]	= &bus_hstimew_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_BUS_DBG]		= &bus_dbg_cwk.common.hw,
		[CWK_BUS_PSI]		= &bus_psi_cwk.common.hw,
		[CWK_BUS_PWM]		= &bus_pwm_cwk.common.hw,
		[CWK_BUS_IOMMU]		= &bus_iommu_cwk.common.hw,
		[CWK_MBUS_DMA]		= &mbus_dma_cwk.common.hw,
		[CWK_MBUS_VE]		= &mbus_ve_cwk.common.hw,
		[CWK_MBUS_CE]		= &mbus_ce_cwk.common.hw,
		[CWK_MBUS_NAND]		= &mbus_nand_cwk.common.hw,
		[CWK_MBUS_CSI]		= &mbus_csi_cwk.common.hw,
		[CWK_MBUS_ISP]		= &mbus_isp_cwk.common.hw,
		[CWK_MBUS_G2D]		= &mbus_g2d_cwk.common.hw,
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
		[CWK_BUS_UAWT4]		= &bus_uawt4_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_I2C2]		= &bus_i2c2_cwk.common.hw,
		[CWK_BUS_I2C3]		= &bus_i2c3_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_SPI1]		= &bus_spi1_cwk.common.hw,
		[CWK_BUS_SPI2]		= &bus_spi2_cwk.common.hw,
		[CWK_EMAC_25M]		= &emac_25m_cwk.common.hw,
		[CWK_BUS_EMAC]		= &bus_emac_cwk.common.hw,
		[CWK_IW_WX]		= &iw_wx_cwk.common.hw,
		[CWK_BUS_IW_WX]		= &bus_iw_wx_cwk.common.hw,
		[CWK_IW_TX]		= &iw_tx_cwk.common.hw,
		[CWK_BUS_IW_TX]		= &bus_iw_tx_cwk.common.hw,
		[CWK_BUS_GPADC]		= &bus_gpadc_cwk.common.hw,
		[CWK_BUS_THS]		= &bus_ths_cwk.common.hw,
		[CWK_I2S0]		= &i2s0_cwk.common.hw,
		[CWK_I2S1]		= &i2s1_cwk.common.hw,
		[CWK_I2S2]		= &i2s2_cwk.common.hw,
		[CWK_I2S3]		= &i2s3_cwk.common.hw,
		[CWK_BUS_I2S0]		= &bus_i2s0_cwk.common.hw,
		[CWK_BUS_I2S1]		= &bus_i2s1_cwk.common.hw,
		[CWK_BUS_I2S2]		= &bus_i2s2_cwk.common.hw,
		[CWK_BUS_I2S3]		= &bus_i2s3_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_BUS_SPDIF]		= &bus_spdif_cwk.common.hw,
		[CWK_DMIC]		= &dmic_cwk.common.hw,
		[CWK_BUS_DMIC]		= &bus_dmic_cwk.common.hw,
		[CWK_AUDIO_DAC]		= &audio_codec_dac_cwk.common.hw,
		[CWK_AUDIO_ADC]		= &audio_codec_adc_cwk.common.hw,
		[CWK_AUDIO_4X]		= &audio_codec_4x_cwk.common.hw,
		[CWK_BUS_AUDIO_CODEC]	= &bus_audio_codec_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_USB_PHY0]		= &usb_phy0_cwk.common.hw,
		[CWK_USB_OHCI1]		= &usb_ohci1_cwk.common.hw,
		[CWK_USB_PHY1]		= &usb_phy1_cwk.common.hw,
		[CWK_BUS_OHCI0]		= &bus_ohci0_cwk.common.hw,
		[CWK_BUS_OHCI1]		= &bus_ohci1_cwk.common.hw,
		[CWK_BUS_EHCI0]		= &bus_ehci0_cwk.common.hw,
		[CWK_BUS_EHCI1]		= &bus_ehci1_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_BUS_WWADC]		= &bus_wwadc_cwk.common.hw,
		[CWK_BUS_DPSS_TOP0]	= &bus_dpss_top0_cwk.common.hw,
		[CWK_BUS_DPSS_TOP1]	= &bus_dpss_top1_cwk.common.hw,
		[CWK_MIPI_DSI]		= &mipi_dsi_cwk.common.hw,
		[CWK_BUS_MIPI_DSI]	= &bus_mipi_dsi_cwk.common.hw,
		[CWK_TCON_WCD]		= &tcon_wcd_cwk.common.hw,
		[CWK_BUS_TCON_WCD]	= &bus_tcon_wcd_cwk.common.hw,
		[CWK_WEDC]		= &wedc_cwk.common.hw,
		[CWK_BUS_WEDC]		= &bus_wedc_cwk.common.hw,
		[CWK_CSI_TOP]		= &csi_top_cwk.common.hw,
		[CWK_CSI0_MCWK]		= &csi0_mcwk_cwk.common.hw,
		[CWK_CSI1_MCWK]		= &csi1_mcwk_cwk.common.hw,
		[CWK_BUS_CSI]		= &bus_csi_cwk.common.hw,
		[CWK_CSI_ISP]		= &csi_isp_cwk.common.hw,
	},
	.num = CWK_NUMBEW,
};

static stwuct ccu_weset_map sun50i_a100_ccu_wesets[] = {
	[WST_MBUS]		= { 0x540, BIT(30) },

	[WST_BUS_DE]		= { 0x60c, BIT(16) },
	[WST_BUS_G2D]		= { 0x63c, BIT(16) },
	[WST_BUS_GPU]		= { 0x67c, BIT(16) },
	[WST_BUS_CE]		= { 0x68c, BIT(16) },
	[WST_BUS_VE]		= { 0x69c, BIT(16) },
	[WST_BUS_DMA]		= { 0x70c, BIT(16) },
	[WST_BUS_MSGBOX]	= { 0x71c, BIT(16) },
	[WST_BUS_SPINWOCK]	= { 0x72c, BIT(16) },
	[WST_BUS_HSTIMEW]	= { 0x73c, BIT(16) },
	[WST_BUS_DBG]		= { 0x78c, BIT(16) },
	[WST_BUS_PSI]		= { 0x79c, BIT(16) },
	[WST_BUS_PWM]		= { 0x7ac, BIT(16) },
	[WST_BUS_DWAM]		= { 0x80c, BIT(16) },
	[WST_BUS_NAND]		= { 0x82c, BIT(16) },
	[WST_BUS_MMC0]		= { 0x84c, BIT(16) },
	[WST_BUS_MMC1]		= { 0x84c, BIT(17) },
	[WST_BUS_MMC2]		= { 0x84c, BIT(18) },
	[WST_BUS_UAWT0]		= { 0x90c, BIT(16) },
	[WST_BUS_UAWT1]		= { 0x90c, BIT(17) },
	[WST_BUS_UAWT2]		= { 0x90c, BIT(18) },
	[WST_BUS_UAWT3]		= { 0x90c, BIT(19) },
	[WST_BUS_UAWT4]		= { 0x90c, BIT(20) },
	[WST_BUS_I2C0]		= { 0x91c, BIT(16) },
	[WST_BUS_I2C1]		= { 0x91c, BIT(17) },
	[WST_BUS_I2C2]		= { 0x91c, BIT(18) },
	[WST_BUS_I2C3]		= { 0x91c, BIT(19) },
	[WST_BUS_SPI0]		= { 0x96c, BIT(16) },
	[WST_BUS_SPI1]		= { 0x96c, BIT(17) },
	[WST_BUS_SPI2]		= { 0x96c, BIT(18) },
	[WST_BUS_EMAC]		= { 0x97c, BIT(16) },
	[WST_BUS_IW_WX]		= { 0x99c, BIT(16) },
	[WST_BUS_IW_TX]		= { 0x9cc, BIT(16) },
	[WST_BUS_GPADC]		= { 0x9ec, BIT(16) },
	[WST_BUS_THS]		= { 0x9fc, BIT(16) },
	[WST_BUS_I2S0]		= { 0xa20, BIT(16) },
	[WST_BUS_I2S1]		= { 0xa20, BIT(17) },
	[WST_BUS_I2S2]		= { 0xa20, BIT(18) },
	[WST_BUS_I2S3]		= { 0xa20, BIT(19) },
	[WST_BUS_SPDIF]		= { 0xa2c, BIT(16) },
	[WST_BUS_DMIC]		= { 0xa4c, BIT(16) },
	[WST_BUS_AUDIO_CODEC]	= { 0xa5c, BIT(16) },

	[WST_USB_PHY0]		= { 0xa70, BIT(30) },
	[WST_USB_PHY1]		= { 0xa74, BIT(30) },

	[WST_BUS_OHCI0]		= { 0xa8c, BIT(16) },
	[WST_BUS_OHCI1]		= { 0xa8c, BIT(17) },
	[WST_BUS_EHCI0]		= { 0xa8c, BIT(20) },
	[WST_BUS_EHCI1]		= { 0xa8c, BIT(21) },
	[WST_BUS_OTG]		= { 0xa8c, BIT(24) },

	[WST_BUS_WWADC]		= { 0xa9c, BIT(16) },
	[WST_BUS_DPSS_TOP0]	= { 0xabc, BIT(16) },
	[WST_BUS_DPSS_TOP1]	= { 0xacc, BIT(16) },
	[WST_BUS_MIPI_DSI]	= { 0xb4c, BIT(16) },
	[WST_BUS_TCON_WCD]	= { 0xb7c, BIT(16) },
	[WST_BUS_WVDS]		= { 0xbac, BIT(16) },
	[WST_BUS_WEDC]		= { 0xbfc, BIT(16) },
	[WST_BUS_CSI]		= { 0xc1c, BIT(16) },
	[WST_BUS_CSI_ISP]	= { 0xc2c, BIT(16) },
};

static const stwuct sunxi_ccu_desc sun50i_a100_ccu_desc = {
	.ccu_cwks	= sun50i_a100_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun50i_a100_ccu_cwks),

	.hw_cwks	= &sun50i_a100_hw_cwks,

	.wesets		= sun50i_a100_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun50i_a100_ccu_wesets),
};

static const u32 sun50i_a100_pww_wegs[] = {
	SUN50I_A100_PWW_CPUX_WEG,
	SUN50I_A100_PWW_DDW0_WEG,
	SUN50I_A100_PWW_PEWIPH0_WEG,
	SUN50I_A100_PWW_PEWIPH1_WEG,
	SUN50I_A100_PWW_GPU_WEG,
	SUN50I_A100_PWW_VIDEO0_WEG,
	SUN50I_A100_PWW_VIDEO1_WEG,
	SUN50I_A100_PWW_VIDEO2_WEG,
	SUN50I_A100_PWW_VIDEO3_WEG,
	SUN50I_A100_PWW_VE_WEG,
	SUN50I_A100_PWW_COM_WEG,
	SUN50I_A100_PWW_AUDIO_WEG,
};

static const u32 sun50i_a100_pww_video_wegs[] = {
	SUN50I_A100_PWW_VIDEO0_WEG,
	SUN50I_A100_PWW_VIDEO1_WEG,
	SUN50I_A100_PWW_VIDEO2_WEG,
	SUN50I_A100_PWW_VIDEO3_WEG,
};

static const u32 sun50i_a100_usb2_cwk_wegs[] = {
	SUN50I_A100_USB0_CWK_WEG,
	SUN50I_A100_USB1_CWK_WEG,
};

static stwuct ccu_pww_nb sun50i_a100_pww_cpu_nb = {
	.common = &pww_cpux_cwk.common,
	/* copy fwom pww_cpux_cwk */
	.enabwe = BIT(27),
	.wock   = BIT(28),
};

static stwuct ccu_mux_nb sun50i_a100_cpu_nb = {
	.common         = &cpux_cwk.common,
	.cm             = &cpux_cwk.mux,
	.deway_us       = 1,
	.bypass_index   = 4, /* index of pww pewiph0 */
};

static int sun50i_a100_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *weg;
	u32 vaw;
	int i, wet;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	/*
	 * Enabwe wock and enabwe bits on aww PWWs.
	 *
	 * Due to the cuwwent design, muwtipwe PWWs shawe one powew switch,
	 * so switching PWW is easy to cause stabiwity pwobwems.
	 * When initiawizing, we enabwe them by defauwt. When disabwe,
	 * we onwy tuwn off the output of PWW.
	 */
	fow (i = 0; i < AWWAY_SIZE(sun50i_a100_pww_wegs); i++) {
		vaw = weadw(weg + sun50i_a100_pww_wegs[i]);
		vaw |= SUN50I_A100_PWW_WOCK_ENABWE | SUN50I_A100_PWW_ENABWE;
		wwitew(vaw, weg + sun50i_a100_pww_wegs[i]);
	}

	/*
	 * In owdew to pass the EMI cewtification, the SDM function of
	 * the pewiphewaw 1 bus is enabwed, and the fwequency is stiww
	 * cawcuwated using the pwevious division factow.
	 */
	wwitew(SUN50I_A100_PWW_PEWIPH1_PATTEWN0,
	       weg + SUN50I_A100_PWW_PEWIPH1_PATTEWN0_WEG);

	vaw = weadw(weg + SUN50I_A100_PWW_PEWIPH1_WEG);
	vaw |= SUN50I_A100_PWW_SDM_ENABWE;
	wwitew(vaw, weg + SUN50I_A100_PWW_PEWIPH1_WEG);

	/*
	 * Fowce the output dividew of video PWWs to 0.
	 *
	 * See the comment befowe pww-video0 definition fow the weason.
	 */
	fow (i = 0; i < AWWAY_SIZE(sun50i_a100_pww_video_wegs); i++) {
		vaw = weadw(weg + sun50i_a100_pww_video_wegs[i]);
		vaw &= ~BIT(0);
		wwitew(vaw, weg + sun50i_a100_pww_video_wegs[i]);
	}

	/*
	 * Enfowce m1 = 0, m0 = 1 fow Audio PWW
	 *
	 * See the comment befowe pww-audio definition fow the weason.
	 */
	vaw = weadw(weg + SUN50I_A100_PWW_AUDIO_WEG);
	vaw &= ~BIT(1);
	vaw |= BIT(0);
	wwitew(vaw, weg + SUN50I_A100_PWW_AUDIO_WEG);

	/*
	 * Fowce OHCI 12M cwock souwces to 00 (12MHz divided fwom 48MHz)
	 *
	 * This cwock mux is stiww mystewious, and the code just enfowces
	 * it to have a vawid cwock pawent.
	 */
	fow (i = 0; i < AWWAY_SIZE(sun50i_a100_usb2_cwk_wegs); i++) {
		vaw = weadw(weg + sun50i_a100_usb2_cwk_wegs[i]);
		vaw &= ~GENMASK(25, 24);
		wwitew(vaw, weg + sun50i_a100_usb2_cwk_wegs[i]);
	}

	wet = devm_sunxi_ccu_pwobe(&pdev->dev, weg, &sun50i_a100_ccu_desc);
	if (wet)
		wetuwn wet;

	/* Gate then ungate PWW CPU aftew any wate changes */
	ccu_pww_notifiew_wegistew(&sun50i_a100_pww_cpu_nb);

	/* Wepawent CPU duwing PWW CPU wate changes */
	ccu_mux_notifiew_wegistew(pww_cpux_cwk.common.hw.cwk,
				  &sun50i_a100_cpu_nb);

	wetuwn 0;
}

static const stwuct of_device_id sun50i_a100_ccu_ids[] = {
	{ .compatibwe = "awwwinnew,sun50i-a100-ccu" },
	{ }
};

static stwuct pwatfowm_dwivew sun50i_a100_ccu_dwivew = {
	.pwobe	= sun50i_a100_ccu_pwobe,
	.dwivew	= {
		.name	= "sun50i-a100-ccu",
		.suppwess_bind_attws = twue,
		.of_match_tabwe	= sun50i_a100_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun50i_a100_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
