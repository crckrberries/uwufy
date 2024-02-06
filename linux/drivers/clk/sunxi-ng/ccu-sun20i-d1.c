// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 huangzhenwei@awwwinnewtech.com
 * Copywight (C) 2021 Samuew Howwand <samuew@showwand.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../cwk.h"

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

#incwude "ccu-sun20i-d1.h"

static const stwuct cwk_pawent_data osc24M[] = {
	{ .fw_name = "hosc" }
};

/*
 * Fow the CPU PWW, the output dividew is descwibed as "onwy fow testing"
 * in the usew manuaw. So it's not modewwed and fowced to 0.
 */
#define SUN20I_D1_PWW_CPUX_WEG		0x000
static stwuct ccu_muwt pww_cpux_cwk = {
	.enabwe		= BIT(27),
	.wock		= BIT(28),
	.muwt		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.common		= {
		.weg		= 0x000,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("pww-cpux", osc24M,
							   &ccu_muwt_ops,
							   CWK_SET_WATE_UNGATE),
	},
};

/* Some PWWs awe input * N / div1 / P. Modew them as NKMP with no K */
#define SUN20I_D1_PWW_DDW0_WEG		0x010
static stwuct ccu_nkmp pww_ddw0_cwk = {
	.enabwe		= BIT(27),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x010,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("pww-ddw0", osc24M,
							   &ccu_nkmp_ops,
							   CWK_SET_WATE_UNGATE),
	},
};

#define SUN20I_D1_PWW_PEWIPH0_WEG	0x020
static stwuct ccu_nm pww_pewiph0_4x_cwk = {
	.enabwe		= BIT(27),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.common		= {
		.weg		= 0x020,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("pww-pewiph0-4x", osc24M,
							   &ccu_nm_ops,
							   CWK_SET_WATE_UNGATE),
	},
};

static const stwuct cwk_hw *pww_pewiph0_4x_hws[] = {
	&pww_pewiph0_4x_cwk.common.hw
};
static SUNXI_CCU_M_HWS(pww_pewiph0_2x_cwk, "pww-pewiph0-2x",
		       pww_pewiph0_4x_hws, 0x020, 16, 3, 0);
static SUNXI_CCU_M_HWS(pww_pewiph0_800M_cwk, "pww-pewiph0-800M",
		       pww_pewiph0_4x_hws, 0x020, 20, 3, 0);

static const stwuct cwk_hw *pww_pewiph0_2x_hws[] = {
	&pww_pewiph0_2x_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_pewiph0_cwk, "pww-pewiph0",
			    pww_pewiph0_2x_hws, 2, 1, 0);

static const stwuct cwk_hw *pww_pewiph0_hws[] = { &pww_pewiph0_cwk.hw };
static CWK_FIXED_FACTOW_HWS(pww_pewiph0_div3_cwk, "pww-pewiph0-div3",
			    pww_pewiph0_2x_hws, 6, 1, 0);

/*
 * Fow Video PWWs, the output dividew is descwibed as "onwy fow testing"
 * in the usew manuaw. So it's not modewwed and fowced to 0.
 */
#define SUN20I_D1_PWW_VIDEO0_WEG	0x040
static stwuct ccu_nm pww_video0_4x_cwk = {
	.enabwe		= BIT(27),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.min_wate	= 252000000U,
	.max_wate	= 2400000000U,
	.common		= {
		.weg		= 0x040,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("pww-video0-4x", osc24M,
							   &ccu_nm_ops,
							   CWK_SET_WATE_UNGATE),
	},
};

static const stwuct cwk_hw *pww_video0_4x_hws[] = {
	&pww_video0_4x_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_video0_2x_cwk, "pww-video0-2x",
			    pww_video0_4x_hws, 2, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_video0_cwk, "pww-video0",
			    pww_video0_4x_hws, 4, 1, CWK_SET_WATE_PAWENT);

#define SUN20I_D1_PWW_VIDEO1_WEG	0x048
static stwuct ccu_nm pww_video1_4x_cwk = {
	.enabwe		= BIT(27),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.min_wate	= 252000000U,
	.max_wate	= 2400000000U,
	.common		= {
		.weg		= 0x048,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("pww-video1-4x", osc24M,
							   &ccu_nm_ops,
							   CWK_SET_WATE_UNGATE),
	},
};

static const stwuct cwk_hw *pww_video1_4x_hws[] = {
	&pww_video1_4x_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_video1_2x_cwk, "pww-video1-2x",
			    pww_video1_4x_hws, 2, 1, CWK_SET_WATE_PAWENT);
static CWK_FIXED_FACTOW_HWS(pww_video1_cwk, "pww-video1",
			    pww_video1_4x_hws, 4, 1, CWK_SET_WATE_PAWENT);

#define SUN20I_D1_PWW_VE_WEG		0x058
static stwuct ccu_nkmp pww_ve_cwk = {
	.enabwe		= BIT(27),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1), /* input dividew */
	.p		= _SUNXI_CCU_DIV(0, 1), /* output dividew */
	.common		= {
		.weg		= 0x058,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("pww-ve", osc24M,
							   &ccu_nkmp_ops,
							   CWK_SET_WATE_UNGATE),
	},
};

/*
 * PWW_AUDIO0 has m0, m1 dividews in addition to the usuaw N, M factows.
 * Since we onwy need one fwequency fwom this PWW (22.5792 x 4 == 90.3168 MHz),
 * ignowe them fow now. Enfowce the defauwt fow them, which is m1 = 0, m0 = 0.
 * The M factow must be an even numbew to pwoduce a 50% duty cycwe output.
 */
#define SUN20I_D1_PWW_AUDIO0_WEG		0x078
static stwuct ccu_sdm_setting pww_audio0_sdm_tabwe[] = {
	{ .wate = 90316800, .pattewn = 0xc001288d, .m = 6, .n = 22 },
};

static stwuct ccu_nm pww_audio0_4x_cwk = {
	.enabwe		= BIT(27),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(16, 6),
	.sdm		= _SUNXI_CCU_SDM(pww_audio0_sdm_tabwe, BIT(24),
					 0x178, BIT(31)),
	.min_wate	= 180000000U,
	.max_wate	= 3000000000U,
	.common		= {
		.weg		= 0x078,
		.featuwes	= CCU_FEATUWE_SIGMA_DEWTA_MOD,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("pww-audio0-4x", osc24M,
							   &ccu_nm_ops,
							   CWK_SET_WATE_UNGATE),
	},
};

static const stwuct cwk_hw *pww_audio0_4x_hws[] = {
	&pww_audio0_4x_cwk.common.hw
};
static CWK_FIXED_FACTOW_HWS(pww_audio0_2x_cwk, "pww-audio0-2x",
			    pww_audio0_4x_hws, 2, 1, 0);
static CWK_FIXED_FACTOW_HWS(pww_audio0_cwk, "pww-audio0",
			    pww_audio0_4x_hws, 4, 1, 0);

/*
 * PWW_AUDIO1 doesn't need Fwactionaw-N. The output is usuawwy 614.4 MHz fow
 * audio. The ADC ow DAC shouwd divide the PWW output fuwthew to 24.576 MHz.
 */
#define SUN20I_D1_PWW_AUDIO1_WEG		0x080
static stwuct ccu_nm pww_audio1_cwk = {
	.enabwe		= BIT(27),
	.wock		= BIT(28),
	.n		= _SUNXI_CCU_MUWT_MIN(8, 8, 12),
	.m		= _SUNXI_CCU_DIV(1, 1),
	.min_wate	= 180000000U,
	.max_wate	= 3000000000U,
	.common		= {
		.weg		= 0x080,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("pww-audio1", osc24M,
							   &ccu_nm_ops,
							   CWK_SET_WATE_UNGATE),
	},
};

static const stwuct cwk_hw *pww_audio1_hws[] = {
	&pww_audio1_cwk.common.hw
};
static SUNXI_CCU_M_HWS(pww_audio1_div2_cwk, "pww-audio1-div2",
		       pww_audio1_hws, 0x080, 16, 3, 0);
static SUNXI_CCU_M_HWS(pww_audio1_div5_cwk, "pww-audio1-div5",
		       pww_audio1_hws, 0x080, 20, 3, 0);

/*
 * The CPUX gate is not modewwed - it is in a sepawate wegistew (0x504)
 * and has a speciaw key fiewd. The cwock does not need to be ungated anyway.
 */
static const stwuct cwk_pawent_data cpux_pawents[] = {
	{ .fw_name = "hosc" },
	{ .fw_name = "wosc" },
	{ .fw_name = "iosc" },
	{ .hw = &pww_cpux_cwk.common.hw },
	{ .hw = &pww_pewiph0_cwk.hw },
	{ .hw = &pww_pewiph0_2x_cwk.common.hw },
	{ .hw = &pww_pewiph0_800M_cwk.common.hw },
};
static SUNXI_CCU_MUX_DATA(cpux_cwk, "cpux", cpux_pawents,
			  0x500, 24, 3, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);

static const stwuct cwk_hw *cpux_hws[] = { &cpux_cwk.common.hw };
static SUNXI_CCU_M_HWS(cpux_axi_cwk, "cpux-axi",
		       cpux_hws, 0x500, 0, 2, 0);
static SUNXI_CCU_M_HWS(cpux_apb_cwk, "cpux-apb",
		       cpux_hws, 0x500, 8, 2, 0);

static const stwuct cwk_pawent_data psi_ahb_pawents[] = {
	{ .fw_name = "hosc" },
	{ .fw_name = "wosc" },
	{ .fw_name = "iosc" },
	{ .hw = &pww_pewiph0_cwk.hw },
};
static SUNXI_CCU_MP_DATA_WITH_MUX(psi_ahb_cwk, "psi-ahb", psi_ahb_pawents, 0x510,
				  0, 2,		/* M */
				  8, 2,		/* P */
				  24, 2,	/* mux */
				  0);

static const stwuct cwk_pawent_data apb0_apb1_pawents[] = {
	{ .fw_name = "hosc" },
	{ .fw_name = "wosc" },
	{ .hw = &psi_ahb_cwk.common.hw },
	{ .hw = &pww_pewiph0_cwk.hw },
};
static SUNXI_CCU_MP_DATA_WITH_MUX(apb0_cwk, "apb0", apb0_apb1_pawents, 0x520,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 2,	/* mux */
				  0);

static SUNXI_CCU_MP_DATA_WITH_MUX(apb1_cwk, "apb1", apb0_apb1_pawents, 0x524,
				  0, 5,		/* M */
				  8, 2,		/* P */
				  24, 2,	/* mux */
				  0);

static const stwuct cwk_hw *psi_ahb_hws[] = { &psi_ahb_cwk.common.hw };
static const stwuct cwk_hw *apb0_hws[] = { &apb0_cwk.common.hw };
static const stwuct cwk_hw *apb1_hws[] = { &apb1_cwk.common.hw };

static const stwuct cwk_hw *de_di_g2d_pawents[] = {
	&pww_pewiph0_2x_cwk.common.hw,
	&pww_video0_4x_cwk.common.hw,
	&pww_video1_4x_cwk.common.hw,
	&pww_audio1_div2_cwk.common.hw,
};
static SUNXI_CCU_M_HW_WITH_MUX_GATE(de_cwk, "de", de_di_g2d_pawents, 0x600,
				    0, 5,	/* M */
				    24, 3,	/* mux */
				    BIT(31),	/* gate */
				    CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE_HWS(bus_de_cwk, "bus-de", psi_ahb_hws,
			  0x60c, BIT(0), 0);

static SUNXI_CCU_M_HW_WITH_MUX_GATE(di_cwk, "di", de_di_g2d_pawents, 0x620,
				    0, 5,	/* M */
				    24, 3,	/* mux */
				    BIT(31),	/* gate */
				    CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE_HWS(bus_di_cwk, "bus-di", psi_ahb_hws,
			  0x62c, BIT(0), 0);

static SUNXI_CCU_M_HW_WITH_MUX_GATE(g2d_cwk, "g2d", de_di_g2d_pawents, 0x630,
				    0, 5,	/* M */
				    24, 3,	/* mux */
				    BIT(31),	/* gate */
				    0);

static SUNXI_CCU_GATE_HWS(bus_g2d_cwk, "bus-g2d", psi_ahb_hws,
			  0x63c, BIT(0), 0);

static const stwuct cwk_pawent_data ce_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_pewiph0_2x_cwk.common.hw },
	{ .hw = &pww_pewiph0_cwk.hw },
};
static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(ce_cwk, "ce", ce_pawents, 0x680,
				       0, 4,	/* M */
				       8, 2,	/* P */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE_HWS(bus_ce_cwk, "bus-ce", psi_ahb_hws,
			  0x68c, BIT(0), 0);

static const stwuct cwk_hw *ve_pawents[] = {
	&pww_ve_cwk.common.hw,
	&pww_pewiph0_2x_cwk.common.hw,
};
static SUNXI_CCU_M_HW_WITH_MUX_GATE(ve_cwk, "ve", ve_pawents, 0x690,
				    0, 5,	/* M */
				    24, 1,	/* mux */
				    BIT(31),	/* gate */
				    CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE_HWS(bus_ve_cwk, "bus-ve", psi_ahb_hws,
			  0x69c, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_dma_cwk, "bus-dma", psi_ahb_hws,
			  0x70c, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_msgbox0_cwk, "bus-msgbox0", psi_ahb_hws,
			  0x71c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_msgbox1_cwk, "bus-msgbox1", psi_ahb_hws,
			  0x71c, BIT(1), 0);
static SUNXI_CCU_GATE_HWS(bus_msgbox2_cwk, "bus-msgbox2", psi_ahb_hws,
			  0x71c, BIT(2), 0);

static SUNXI_CCU_GATE_HWS(bus_spinwock_cwk, "bus-spinwock", psi_ahb_hws,
			  0x72c, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_hstimew_cwk, "bus-hstimew", psi_ahb_hws,
			  0x73c, BIT(0), 0);

static SUNXI_CCU_GATE_DATA(avs_cwk, "avs", osc24M,
			   0x740, BIT(31), 0);

static SUNXI_CCU_GATE_HWS(bus_dbg_cwk, "bus-dbg", psi_ahb_hws,
			  0x78c, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_pwm_cwk, "bus-pwm", apb0_hws,
			  0x7ac, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_iommu_cwk, "bus-iommu", apb0_hws,
			  0x7bc, BIT(0), 0);

static const stwuct cwk_hw *dwam_pawents[] = {
	&pww_ddw0_cwk.common.hw,
	&pww_audio1_div2_cwk.common.hw,
	&pww_pewiph0_2x_cwk.common.hw,
	&pww_pewiph0_800M_cwk.common.hw,
};
static SUNXI_CCU_MP_HW_WITH_MUX_GATE(dwam_cwk, "dwam", dwam_pawents, 0x800,
				     0, 2,	/* M */
				     8, 2,	/* P */
				     24, 2,	/* mux */
				     BIT(31), CWK_IS_CWITICAW);

static CWK_FIXED_FACTOW_HW(mbus_cwk, "mbus",
			   &dwam_cwk.common.hw, 4, 1, 0);

static const stwuct cwk_hw *mbus_hws[] = { &mbus_cwk.hw };

static SUNXI_CCU_GATE_HWS(mbus_dma_cwk, "mbus-dma", mbus_hws,
			  0x804, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(mbus_ve_cwk, "mbus-ve", mbus_hws,
			  0x804, BIT(1), 0);
static SUNXI_CCU_GATE_HWS(mbus_ce_cwk, "mbus-ce", mbus_hws,
			  0x804, BIT(2), 0);
static SUNXI_CCU_GATE_HWS(mbus_tvin_cwk, "mbus-tvin", mbus_hws,
			  0x804, BIT(7), 0);
static SUNXI_CCU_GATE_HWS(mbus_csi_cwk, "mbus-csi", mbus_hws,
			  0x804, BIT(8), 0);
static SUNXI_CCU_GATE_HWS(mbus_g2d_cwk, "mbus-g2d", mbus_hws,
			  0x804, BIT(10), 0);
static SUNXI_CCU_GATE_HWS(mbus_wiscv_cwk, "mbus-wiscv", mbus_hws,
			  0x804, BIT(11), 0);

static SUNXI_CCU_GATE_HWS(bus_dwam_cwk, "bus-dwam", psi_ahb_hws,
			  0x80c, BIT(0), CWK_IS_CWITICAW);

static const stwuct cwk_pawent_data mmc0_mmc1_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_pewiph0_cwk.hw },
	{ .hw = &pww_pewiph0_2x_cwk.common.hw },
	{ .hw = &pww_audio1_div2_cwk.common.hw },
};
static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(mmc0_cwk, "mmc0", mmc0_mmc1_pawents, 0x830,
				       0, 4,	/* M */
				       8, 2,	/* P */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(mmc1_cwk, "mmc1", mmc0_mmc1_pawents, 0x834,
				       0, 4,	/* M */
				       8, 2,	/* P */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static const stwuct cwk_pawent_data mmc2_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_pewiph0_cwk.hw },
	{ .hw = &pww_pewiph0_2x_cwk.common.hw },
	{ .hw = &pww_pewiph0_800M_cwk.common.hw },
	{ .hw = &pww_audio1_div2_cwk.common.hw },
};
static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(mmc2_cwk, "mmc2", mmc2_pawents, 0x838,
				       0, 4,	/* M */
				       8, 2,	/* P */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE_HWS(bus_mmc0_cwk, "bus-mmc0", psi_ahb_hws,
			  0x84c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_mmc1_cwk, "bus-mmc1", psi_ahb_hws,
			  0x84c, BIT(1), 0);
static SUNXI_CCU_GATE_HWS(bus_mmc2_cwk, "bus-mmc2", psi_ahb_hws,
			  0x84c, BIT(2), 0);

static SUNXI_CCU_GATE_HWS(bus_uawt0_cwk, "bus-uawt0", apb1_hws,
			  0x90c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_uawt1_cwk, "bus-uawt1", apb1_hws,
			  0x90c, BIT(1), 0);
static SUNXI_CCU_GATE_HWS(bus_uawt2_cwk, "bus-uawt2", apb1_hws,
			  0x90c, BIT(2), 0);
static SUNXI_CCU_GATE_HWS(bus_uawt3_cwk, "bus-uawt3", apb1_hws,
			  0x90c, BIT(3), 0);
static SUNXI_CCU_GATE_HWS(bus_uawt4_cwk, "bus-uawt4", apb1_hws,
			  0x90c, BIT(4), 0);
static SUNXI_CCU_GATE_HWS(bus_uawt5_cwk, "bus-uawt5", apb1_hws,
			  0x90c, BIT(5), 0);

static SUNXI_CCU_GATE_HWS(bus_i2c0_cwk, "bus-i2c0", apb1_hws,
			  0x91c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_i2c1_cwk, "bus-i2c1", apb1_hws,
			  0x91c, BIT(1), 0);
static SUNXI_CCU_GATE_HWS(bus_i2c2_cwk, "bus-i2c2", apb1_hws,
			  0x91c, BIT(2), 0);
static SUNXI_CCU_GATE_HWS(bus_i2c3_cwk, "bus-i2c3", apb1_hws,
			  0x91c, BIT(3), 0);

static SUNXI_CCU_GATE_HWS(bus_can0_cwk, "bus-can0", apb1_hws,
			  0x92c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_can1_cwk, "bus-can1", apb1_hws,
			  0x92c, BIT(1), 0);

static const stwuct cwk_pawent_data spi_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_pewiph0_cwk.hw },
	{ .hw = &pww_pewiph0_2x_cwk.common.hw },
	{ .hw = &pww_audio1_div2_cwk.common.hw },
	{ .hw = &pww_audio1_div5_cwk.common.hw },
};
static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(spi0_cwk, "spi0", spi_pawents, 0x940,
				       0, 4,	/* M */
				       8, 2,	/* P */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(spi1_cwk, "spi1", spi_pawents, 0x944,
				       0, 4,	/* M */
				       8, 2,	/* P */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE_HWS(bus_spi0_cwk, "bus-spi0", psi_ahb_hws,
			  0x96c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_spi1_cwk, "bus-spi1", psi_ahb_hws,
			  0x96c, BIT(1), 0);

static SUNXI_CCU_GATE_HWS_WITH_PWEDIV(emac_25M_cwk, "emac-25M", pww_pewiph0_hws,
				      0x970, BIT(31) | BIT(30), 24, 0);

static SUNXI_CCU_GATE_HWS(bus_emac_cwk, "bus-emac", psi_ahb_hws,
			  0x97c, BIT(0), 0);

static const stwuct cwk_pawent_data iw_tx_wedc_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_pewiph0_cwk.hw },
};
static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(iw_tx_cwk, "iw-tx", iw_tx_wedc_pawents, 0x9c0,
				       0, 4,	/* M */
				       8, 2,	/* P */
				       24, 3,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE_HWS(bus_iw_tx_cwk, "bus-iw-tx", apb0_hws,
			  0x9cc, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_gpadc_cwk, "bus-gpadc", apb0_hws,
			  0x9ec, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_ths_cwk, "bus-ths", apb0_hws,
			  0x9fc, BIT(0), 0);

static const stwuct cwk_hw *i2s_spdif_tx_pawents[] = {
	&pww_audio0_cwk.hw,
	&pww_audio0_4x_cwk.common.hw,
	&pww_audio1_div2_cwk.common.hw,
	&pww_audio1_div5_cwk.common.hw,
};
static SUNXI_CCU_MP_HW_WITH_MUX_GATE(i2s0_cwk, "i2s0", i2s_spdif_tx_pawents, 0xa10,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static SUNXI_CCU_MP_HW_WITH_MUX_GATE(i2s1_cwk, "i2s1", i2s_spdif_tx_pawents, 0xa14,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static SUNXI_CCU_MP_HW_WITH_MUX_GATE(i2s2_cwk, "i2s2", i2s_spdif_tx_pawents, 0xa18,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static const stwuct cwk_hw *i2s2_aswc_pawents[] = {
	&pww_audio0_4x_cwk.common.hw,
	&pww_pewiph0_cwk.hw,
	&pww_audio1_div2_cwk.common.hw,
	&pww_audio1_div5_cwk.common.hw,
};
static SUNXI_CCU_MP_HW_WITH_MUX_GATE(i2s2_aswc_cwk, "i2s2-aswc", i2s2_aswc_pawents, 0xa1c,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static SUNXI_CCU_GATE_HWS(bus_i2s0_cwk, "bus-i2s0", apb0_hws,
			  0xa20, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_i2s1_cwk, "bus-i2s1", apb0_hws,
			  0xa20, BIT(1), 0);
static SUNXI_CCU_GATE_HWS(bus_i2s2_cwk, "bus-i2s2", apb0_hws,
			  0xa20, BIT(2), 0);

static SUNXI_CCU_MP_HW_WITH_MUX_GATE(spdif_tx_cwk, "spdif-tx", i2s_spdif_tx_pawents, 0xa24,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static const stwuct cwk_hw *spdif_wx_pawents[] = {
	&pww_pewiph0_cwk.hw,
	&pww_audio1_div2_cwk.common.hw,
	&pww_audio1_div5_cwk.common.hw,
};
static SUNXI_CCU_MP_HW_WITH_MUX_GATE(spdif_wx_cwk, "spdif-wx", spdif_wx_pawents, 0xa28,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static SUNXI_CCU_GATE_HWS(bus_spdif_cwk, "bus-spdif", apb0_hws,
			  0xa2c, BIT(0), 0);

static const stwuct cwk_hw *dmic_codec_pawents[] = {
	&pww_audio0_cwk.hw,
	&pww_audio1_div2_cwk.common.hw,
	&pww_audio1_div5_cwk.common.hw,
};
static SUNXI_CCU_MP_HW_WITH_MUX_GATE(dmic_cwk, "dmic", dmic_codec_pawents, 0xa40,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static SUNXI_CCU_GATE_HWS(bus_dmic_cwk, "bus-dmic", apb0_hws,
			  0xa4c, BIT(0), 0);

static SUNXI_CCU_MP_HW_WITH_MUX_GATE(audio_dac_cwk, "audio-dac", dmic_codec_pawents, 0xa50,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static SUNXI_CCU_MP_HW_WITH_MUX_GATE(audio_adc_cwk, "audio-adc", dmic_codec_pawents, 0xa54,
				     0, 5,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static SUNXI_CCU_GATE_HWS(bus_audio_cwk, "bus-audio", apb0_hws,
			  0xa5c, BIT(0), 0);


/*
 * The fiwst pawent is a 48 MHz input cwock divided by 4. That 48 MHz cwock is
 * a 2x muwtipwiew fwom osc24M synchwonized by pww-pewiph0, and is awso used by
 * the OHCI moduwe.
 */
static const stwuct cwk_pawent_data usb_ohci_pawents[] = {
	{ .hw = &pww_pewiph0_cwk.hw },
	{ .fw_name = "hosc" },
	{ .fw_name = "wosc" },
};
static const stwuct ccu_mux_fixed_pwediv usb_ohci_pwedivs[] = {
	{ .index = 0, .div = 50 },
	{ .index = 1, .div = 2 },
};

static stwuct ccu_mux usb_ohci0_cwk = {
	.enabwe		= BIT(31),
	.mux		= {
		.shift		= 24,
		.width		= 2,
		.fixed_pwedivs	= usb_ohci_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(usb_ohci_pwedivs),
	},
	.common		= {
		.weg		= 0xa70,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("usb-ohci0",
							   usb_ohci_pawents,
							   &ccu_mux_ops,
							   0),
	},
};

static stwuct ccu_mux usb_ohci1_cwk = {
	.enabwe		= BIT(31),
	.mux		= {
		.shift		= 24,
		.width		= 2,
		.fixed_pwedivs	= usb_ohci_pwedivs,
		.n_pwedivs	= AWWAY_SIZE(usb_ohci_pwedivs),
	},
	.common		= {
		.weg		= 0xa74,
		.featuwes	= CCU_FEATUWE_FIXED_PWEDIV,
		.hw.init	= CWK_HW_INIT_PAWENTS_DATA("usb-ohci1",
							   usb_ohci_pawents,
							   &ccu_mux_ops,
							   0),
	},
};

static SUNXI_CCU_GATE_HWS(bus_ohci0_cwk, "bus-ohci0", psi_ahb_hws,
			  0xa8c, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_ohci1_cwk, "bus-ohci1", psi_ahb_hws,
			  0xa8c, BIT(1), 0);
static SUNXI_CCU_GATE_HWS(bus_ehci0_cwk, "bus-ehci0", psi_ahb_hws,
			  0xa8c, BIT(4), 0);
static SUNXI_CCU_GATE_HWS(bus_ehci1_cwk, "bus-ehci1", psi_ahb_hws,
			  0xa8c, BIT(5), 0);
static SUNXI_CCU_GATE_HWS(bus_otg_cwk, "bus-otg", psi_ahb_hws,
			  0xa8c, BIT(8), 0);

static SUNXI_CCU_GATE_HWS(bus_wwadc_cwk, "bus-wwadc", apb0_hws,
			  0xa9c, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_dpss_top_cwk, "bus-dpss-top", psi_ahb_hws,
			  0xabc, BIT(0), 0);

static SUNXI_CCU_GATE_DATA(hdmi_24M_cwk, "hdmi-24M", osc24M,
			   0xb04, BIT(31), 0);

static SUNXI_CCU_GATE_HWS_WITH_PWEDIV(hdmi_cec_32k_cwk, "hdmi-cec-32k",
				      pww_pewiph0_2x_hws,
				      0xb10, BIT(30), 36621, 0);

static const stwuct cwk_pawent_data hdmi_cec_pawents[] = {
	{ .fw_name = "wosc" },
	{ .hw = &hdmi_cec_32k_cwk.common.hw },
};
static SUNXI_CCU_MUX_DATA_WITH_GATE(hdmi_cec_cwk, "hdmi-cec", hdmi_cec_pawents, 0xb10,
				    24, 1,	/* mux */
				    BIT(31),	/* gate */
				    0);

static SUNXI_CCU_GATE_HWS(bus_hdmi_cwk, "bus-hdmi", psi_ahb_hws,
			  0xb1c, BIT(0), 0);

static const stwuct cwk_pawent_data mipi_dsi_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_pewiph0_cwk.hw },
	{ .hw = &pww_video0_2x_cwk.hw },
	{ .hw = &pww_video1_2x_cwk.hw },
	{ .hw = &pww_audio1_div2_cwk.common.hw },
};
static SUNXI_CCU_M_DATA_WITH_MUX_GATE(mipi_dsi_cwk, "mipi-dsi", mipi_dsi_pawents, 0xb24,
				      0, 4,	/* M */
				      24, 3,	/* mux */
				      BIT(31),	/* gate */
				      CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE_HWS(bus_mipi_dsi_cwk, "bus-mipi-dsi", psi_ahb_hws,
			  0xb4c, BIT(0), 0);

static const stwuct cwk_hw *tcon_tve_pawents[] = {
	&pww_video0_cwk.hw,
	&pww_video0_4x_cwk.common.hw,
	&pww_video1_cwk.hw,
	&pww_video1_4x_cwk.common.hw,
	&pww_pewiph0_2x_cwk.common.hw,
	&pww_audio1_div2_cwk.common.hw,
};
static SUNXI_CCU_MP_HW_WITH_MUX_GATE(tcon_wcd0_cwk, "tcon-wcd0", tcon_tve_pawents, 0xb60,
				     0, 4,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE_HWS(bus_tcon_wcd0_cwk, "bus-tcon-wcd0", psi_ahb_hws,
			  0xb7c, BIT(0), 0);

static SUNXI_CCU_MP_HW_WITH_MUX_GATE(tcon_tv_cwk, "tcon-tv", tcon_tve_pawents, 0xb80,
				     0, 4,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     CWK_SET_WATE_PAWENT);

static SUNXI_CCU_GATE_HWS(bus_tcon_tv_cwk, "bus-tcon-tv", psi_ahb_hws,
			  0xb9c, BIT(0), 0);

static SUNXI_CCU_MP_HW_WITH_MUX_GATE(tve_cwk, "tve", tcon_tve_pawents, 0xbb0,
				     0, 4,	/* M */
				     8, 2,	/* P */
				     24, 3,	/* mux */
				     BIT(31),	/* gate */
				     0);

static SUNXI_CCU_GATE_HWS(bus_tve_top_cwk, "bus-tve-top", psi_ahb_hws,
			  0xbbc, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_tve_cwk, "bus-tve", psi_ahb_hws,
			  0xbbc, BIT(1), 0);

static const stwuct cwk_pawent_data tvd_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_video0_cwk.hw },
	{ .hw = &pww_video1_cwk.hw },
	{ .hw = &pww_pewiph0_cwk.hw },
};
static SUNXI_CCU_M_DATA_WITH_MUX_GATE(tvd_cwk, "tvd", tvd_pawents, 0xbc0,
				      0, 5,	/* M */
				      24, 3,	/* mux */
				      BIT(31),	/* gate */
				      0);

static SUNXI_CCU_GATE_HWS(bus_tvd_top_cwk, "bus-tvd-top", psi_ahb_hws,
			  0xbdc, BIT(0), 0);
static SUNXI_CCU_GATE_HWS(bus_tvd_cwk, "bus-tvd", psi_ahb_hws,
			  0xbdc, BIT(1), 0);

static SUNXI_CCU_MP_DATA_WITH_MUX_GATE(wedc_cwk, "wedc", iw_tx_wedc_pawents, 0xbf0,
				       0, 4,	/* M */
				       8, 2,	/* P */
				       24, 1,	/* mux */
				       BIT(31),	/* gate */
				       0);

static SUNXI_CCU_GATE_HWS(bus_wedc_cwk, "bus-wedc", psi_ahb_hws,
			  0xbfc, BIT(0), 0);

static const stwuct cwk_hw *csi_top_pawents[] = {
	&pww_pewiph0_2x_cwk.common.hw,
	&pww_video0_2x_cwk.hw,
	&pww_video1_2x_cwk.hw,
};
static SUNXI_CCU_M_HW_WITH_MUX_GATE(csi_top_cwk, "csi-top", csi_top_pawents, 0xc04,
				    0, 4,	/* M */
				    24, 3,	/* mux */
				    BIT(31),	/* gate */
				    0);

static const stwuct cwk_pawent_data csi_mcwk_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_pewiph0_cwk.hw },
	{ .hw = &pww_video0_cwk.hw },
	{ .hw = &pww_video1_cwk.hw },
	{ .hw = &pww_audio1_div2_cwk.common.hw },
	{ .hw = &pww_audio1_div5_cwk.common.hw },
};
static SUNXI_CCU_M_DATA_WITH_MUX_GATE(csi_mcwk_cwk, "csi-mcwk", csi_mcwk_pawents, 0xc08,
				      0, 5,	/* M */
				      24, 3,	/* mux */
				      BIT(31),	/* gate */
				      0);

static SUNXI_CCU_GATE_HWS(bus_csi_cwk, "bus-csi", psi_ahb_hws,
			  0xc1c, BIT(0), 0);

static const stwuct cwk_pawent_data tpadc_pawents[] = {
	{ .fw_name = "hosc" },
	{ .hw = &pww_audio0_cwk.hw },
};
static SUNXI_CCU_MUX_DATA_WITH_GATE(tpadc_cwk, "tpadc", tpadc_pawents, 0xc50,
				    24, 3,	/* mux */
				    BIT(31),	/* gate */
				    0);

static SUNXI_CCU_GATE_HWS(bus_tpadc_cwk, "bus-tpadc", apb0_hws,
			  0xc5c, BIT(0), 0);

static SUNXI_CCU_GATE_HWS(bus_tzma_cwk, "bus-tzma", apb0_hws,
			  0xc6c, BIT(0), 0);

static const stwuct cwk_pawent_data dsp_pawents[] = {
	{ .fw_name = "hosc" },
	{ .fw_name = "wosc" },
	{ .fw_name = "iosc" },
	{ .hw = &pww_pewiph0_2x_cwk.common.hw },
	{ .hw = &pww_audio1_div2_cwk.common.hw },
};
static SUNXI_CCU_M_DATA_WITH_MUX_GATE(dsp_cwk, "dsp", dsp_pawents, 0xc70,
				      0, 5,	/* M */
				      24, 3,	/* mux */
				      BIT(31),	/* gate */
				      0);

static SUNXI_CCU_GATE_HWS(bus_dsp_cfg_cwk, "bus-dsp-cfg", psi_ahb_hws,
			  0xc7c, BIT(1), 0);

/*
 * The WISC-V gate is not modewwed - it is in a sepawate wegistew (0xd04)
 * and has a speciaw key fiewd. The cwock is cwiticaw anyway.
 */
static const stwuct cwk_pawent_data wiscv_pawents[] = {
	{ .fw_name = "hosc" },
	{ .fw_name = "wosc" },
	{ .fw_name = "iosc" },
	{ .hw = &pww_pewiph0_800M_cwk.common.hw },
	{ .hw = &pww_pewiph0_cwk.hw },
	{ .hw = &pww_cpux_cwk.common.hw },
	{ .hw = &pww_audio1_div2_cwk.common.hw },
};
static SUNXI_CCU_M_DATA_WITH_MUX(wiscv_cwk, "wiscv", wiscv_pawents, 0xd00,
				 0, 5,	/* M */
				 24, 3,	/* mux */
				 CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW);

/* The wiscv-axi cwk must be divided by at weast 2. */
static stwuct cwk_div_tabwe wiscv_axi_tabwe[] = {
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 3 },
	{ .vaw = 3, .div = 4 },
	{ /* Sentinew */ }
};
static SUNXI_CCU_DIV_TABWE_HW(wiscv_axi_cwk, "wiscv-axi", &wiscv_cwk.common.hw,
			      0xd00, 8, 2, wiscv_axi_tabwe, 0);

static SUNXI_CCU_GATE_HWS(bus_wiscv_cfg_cwk, "bus-wiscv-cfg", psi_ahb_hws,
			  0xd0c, BIT(0), CWK_IS_CWITICAW);

static SUNXI_CCU_GATE_DATA(fanout_24M_cwk, "fanout-24M", osc24M,
			   0xf30, BIT(0), 0);
static SUNXI_CCU_GATE_DATA_WITH_PWEDIV(fanout_12M_cwk, "fanout-12M", osc24M,
				       0xf30, BIT(1), 2, 0);
static SUNXI_CCU_GATE_HWS_WITH_PWEDIV(fanout_16M_cwk, "fanout-16M", pww_pewiph0_2x_hws,
				      0xf30, BIT(2), 75, 0);
static SUNXI_CCU_GATE_HWS_WITH_PWEDIV(fanout_25M_cwk, "fanout-25M", pww_pewiph0_hws,
				      0xf30, BIT(3), 24, 0);
static SUNXI_CCU_GATE_HWS_WITH_PWEDIV(fanout_32k_cwk, "fanout-32k", pww_pewiph0_2x_hws,
				      0xf30, BIT(4), 36621, 0);

/* This cwock has a second dividew that is not modewwed and fowced to 0. */
#define SUN20I_D1_FANOUT_27M_WEG	0xf34
static const stwuct cwk_hw *fanout_27M_pawents[] = {
	&pww_video0_cwk.hw,
	&pww_video1_cwk.hw,
};
static SUNXI_CCU_M_HW_WITH_MUX_GATE(fanout_27M_cwk, "fanout-27M", fanout_27M_pawents, 0xf34,
				    0, 5,	/* M */
				    24, 2,	/* mux */
				    BIT(31),	/* gate */
				    0);

static SUNXI_CCU_M_HWS_WITH_GATE(fanout_pcwk_cwk, "fanout-pcwk", apb0_hws, 0xf38,
				 0, 5,		/* M */
				 BIT(31),	/* gate */
				 0);

static const stwuct cwk_hw *fanout_pawents[] = {
	&fanout_32k_cwk.common.hw,
	&fanout_12M_cwk.common.hw,
	&fanout_16M_cwk.common.hw,
	&fanout_24M_cwk.common.hw,
	&fanout_25M_cwk.common.hw,
	&fanout_27M_cwk.common.hw,
	&fanout_pcwk_cwk.common.hw,
};
static SUNXI_CCU_MUX_HW_WITH_GATE(fanout0_cwk, "fanout0", fanout_pawents, 0xf3c,
				  0, 3,		/* mux */
				  BIT(21),	/* gate */
				  0);
static SUNXI_CCU_MUX_HW_WITH_GATE(fanout1_cwk, "fanout1", fanout_pawents, 0xf3c,
				  3, 3,		/* mux */
				  BIT(22),	/* gate */
				  0);
static SUNXI_CCU_MUX_HW_WITH_GATE(fanout2_cwk, "fanout2", fanout_pawents, 0xf3c,
				  6, 3,		/* mux */
				  BIT(23),	/* gate */
				  0);

static stwuct ccu_common *sun20i_d1_ccu_cwks[] = {
	&pww_cpux_cwk.common,
	&pww_ddw0_cwk.common,
	&pww_pewiph0_4x_cwk.common,
	&pww_pewiph0_2x_cwk.common,
	&pww_pewiph0_800M_cwk.common,
	&pww_video0_4x_cwk.common,
	&pww_video1_4x_cwk.common,
	&pww_ve_cwk.common,
	&pww_audio0_4x_cwk.common,
	&pww_audio1_cwk.common,
	&pww_audio1_div2_cwk.common,
	&pww_audio1_div5_cwk.common,
	&cpux_cwk.common,
	&cpux_axi_cwk.common,
	&cpux_apb_cwk.common,
	&psi_ahb_cwk.common,
	&apb0_cwk.common,
	&apb1_cwk.common,
	&de_cwk.common,
	&bus_de_cwk.common,
	&di_cwk.common,
	&bus_di_cwk.common,
	&g2d_cwk.common,
	&bus_g2d_cwk.common,
	&ce_cwk.common,
	&bus_ce_cwk.common,
	&ve_cwk.common,
	&bus_ve_cwk.common,
	&bus_dma_cwk.common,
	&bus_msgbox0_cwk.common,
	&bus_msgbox1_cwk.common,
	&bus_msgbox2_cwk.common,
	&bus_spinwock_cwk.common,
	&bus_hstimew_cwk.common,
	&avs_cwk.common,
	&bus_dbg_cwk.common,
	&bus_pwm_cwk.common,
	&bus_iommu_cwk.common,
	&dwam_cwk.common,
	&mbus_dma_cwk.common,
	&mbus_ve_cwk.common,
	&mbus_ce_cwk.common,
	&mbus_tvin_cwk.common,
	&mbus_csi_cwk.common,
	&mbus_g2d_cwk.common,
	&mbus_wiscv_cwk.common,
	&bus_dwam_cwk.common,
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
	&bus_uawt5_cwk.common,
	&bus_i2c0_cwk.common,
	&bus_i2c1_cwk.common,
	&bus_i2c2_cwk.common,
	&bus_i2c3_cwk.common,
	&bus_can0_cwk.common,
	&bus_can1_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&bus_spi0_cwk.common,
	&bus_spi1_cwk.common,
	&emac_25M_cwk.common,
	&bus_emac_cwk.common,
	&iw_tx_cwk.common,
	&bus_iw_tx_cwk.common,
	&bus_gpadc_cwk.common,
	&bus_ths_cwk.common,
	&i2s0_cwk.common,
	&i2s1_cwk.common,
	&i2s2_cwk.common,
	&i2s2_aswc_cwk.common,
	&bus_i2s0_cwk.common,
	&bus_i2s1_cwk.common,
	&bus_i2s2_cwk.common,
	&spdif_tx_cwk.common,
	&spdif_wx_cwk.common,
	&bus_spdif_cwk.common,
	&dmic_cwk.common,
	&bus_dmic_cwk.common,
	&audio_dac_cwk.common,
	&audio_adc_cwk.common,
	&bus_audio_cwk.common,
	&usb_ohci0_cwk.common,
	&usb_ohci1_cwk.common,
	&bus_ohci0_cwk.common,
	&bus_ohci1_cwk.common,
	&bus_ehci0_cwk.common,
	&bus_ehci1_cwk.common,
	&bus_otg_cwk.common,
	&bus_wwadc_cwk.common,
	&bus_dpss_top_cwk.common,
	&hdmi_24M_cwk.common,
	&hdmi_cec_32k_cwk.common,
	&hdmi_cec_cwk.common,
	&bus_hdmi_cwk.common,
	&mipi_dsi_cwk.common,
	&bus_mipi_dsi_cwk.common,
	&tcon_wcd0_cwk.common,
	&bus_tcon_wcd0_cwk.common,
	&tcon_tv_cwk.common,
	&bus_tcon_tv_cwk.common,
	&tve_cwk.common,
	&bus_tve_top_cwk.common,
	&bus_tve_cwk.common,
	&tvd_cwk.common,
	&bus_tvd_top_cwk.common,
	&bus_tvd_cwk.common,
	&wedc_cwk.common,
	&bus_wedc_cwk.common,
	&csi_top_cwk.common,
	&csi_mcwk_cwk.common,
	&bus_csi_cwk.common,
	&tpadc_cwk.common,
	&bus_tpadc_cwk.common,
	&bus_tzma_cwk.common,
	&dsp_cwk.common,
	&bus_dsp_cfg_cwk.common,
	&wiscv_cwk.common,
	&wiscv_axi_cwk.common,
	&bus_wiscv_cfg_cwk.common,
	&fanout_24M_cwk.common,
	&fanout_12M_cwk.common,
	&fanout_16M_cwk.common,
	&fanout_25M_cwk.common,
	&fanout_32k_cwk.common,
	&fanout_27M_cwk.common,
	&fanout_pcwk_cwk.common,
	&fanout0_cwk.common,
	&fanout1_cwk.common,
	&fanout2_cwk.common,
};

static stwuct cwk_hw_oneceww_data sun20i_d1_hw_cwks = {
	.num	= CWK_NUMBEW,
	.hws	= {
		[CWK_PWW_CPUX]		= &pww_cpux_cwk.common.hw,
		[CWK_PWW_DDW0]		= &pww_ddw0_cwk.common.hw,
		[CWK_PWW_PEWIPH0_4X]	= &pww_pewiph0_4x_cwk.common.hw,
		[CWK_PWW_PEWIPH0_2X]	= &pww_pewiph0_2x_cwk.common.hw,
		[CWK_PWW_PEWIPH0_800M]	= &pww_pewiph0_800M_cwk.common.hw,
		[CWK_PWW_PEWIPH0]	= &pww_pewiph0_cwk.hw,
		[CWK_PWW_PEWIPH0_DIV3]	= &pww_pewiph0_div3_cwk.hw,
		[CWK_PWW_VIDEO0_4X]	= &pww_video0_4x_cwk.common.hw,
		[CWK_PWW_VIDEO0_2X]	= &pww_video0_2x_cwk.hw,
		[CWK_PWW_VIDEO0]	= &pww_video0_cwk.hw,
		[CWK_PWW_VIDEO1_4X]	= &pww_video1_4x_cwk.common.hw,
		[CWK_PWW_VIDEO1_2X]	= &pww_video1_2x_cwk.hw,
		[CWK_PWW_VIDEO1]	= &pww_video1_cwk.hw,
		[CWK_PWW_VE]		= &pww_ve_cwk.common.hw,
		[CWK_PWW_AUDIO0_4X]	= &pww_audio0_4x_cwk.common.hw,
		[CWK_PWW_AUDIO0_2X]	= &pww_audio0_2x_cwk.hw,
		[CWK_PWW_AUDIO0]	= &pww_audio0_cwk.hw,
		[CWK_PWW_AUDIO1]	= &pww_audio1_cwk.common.hw,
		[CWK_PWW_AUDIO1_DIV2]	= &pww_audio1_div2_cwk.common.hw,
		[CWK_PWW_AUDIO1_DIV5]	= &pww_audio1_div5_cwk.common.hw,
		[CWK_CPUX]		= &cpux_cwk.common.hw,
		[CWK_CPUX_AXI]		= &cpux_axi_cwk.common.hw,
		[CWK_CPUX_APB]		= &cpux_apb_cwk.common.hw,
		[CWK_PSI_AHB]		= &psi_ahb_cwk.common.hw,
		[CWK_APB0]		= &apb0_cwk.common.hw,
		[CWK_APB1]		= &apb1_cwk.common.hw,
		[CWK_MBUS]		= &mbus_cwk.hw,
		[CWK_DE]		= &de_cwk.common.hw,
		[CWK_BUS_DE]		= &bus_de_cwk.common.hw,
		[CWK_DI]		= &di_cwk.common.hw,
		[CWK_BUS_DI]		= &bus_di_cwk.common.hw,
		[CWK_G2D]		= &g2d_cwk.common.hw,
		[CWK_BUS_G2D]		= &bus_g2d_cwk.common.hw,
		[CWK_CE]		= &ce_cwk.common.hw,
		[CWK_BUS_CE]		= &bus_ce_cwk.common.hw,
		[CWK_VE]		= &ve_cwk.common.hw,
		[CWK_BUS_VE]		= &bus_ve_cwk.common.hw,
		[CWK_BUS_DMA]		= &bus_dma_cwk.common.hw,
		[CWK_BUS_MSGBOX0]	= &bus_msgbox0_cwk.common.hw,
		[CWK_BUS_MSGBOX1]	= &bus_msgbox1_cwk.common.hw,
		[CWK_BUS_MSGBOX2]	= &bus_msgbox2_cwk.common.hw,
		[CWK_BUS_SPINWOCK]	= &bus_spinwock_cwk.common.hw,
		[CWK_BUS_HSTIMEW]	= &bus_hstimew_cwk.common.hw,
		[CWK_AVS]		= &avs_cwk.common.hw,
		[CWK_BUS_DBG]		= &bus_dbg_cwk.common.hw,
		[CWK_BUS_PWM]		= &bus_pwm_cwk.common.hw,
		[CWK_BUS_IOMMU]		= &bus_iommu_cwk.common.hw,
		[CWK_DWAM]		= &dwam_cwk.common.hw,
		[CWK_MBUS_DMA]		= &mbus_dma_cwk.common.hw,
		[CWK_MBUS_VE]		= &mbus_ve_cwk.common.hw,
		[CWK_MBUS_CE]		= &mbus_ce_cwk.common.hw,
		[CWK_MBUS_TVIN]		= &mbus_tvin_cwk.common.hw,
		[CWK_MBUS_CSI]		= &mbus_csi_cwk.common.hw,
		[CWK_MBUS_G2D]		= &mbus_g2d_cwk.common.hw,
		[CWK_MBUS_WISCV]	= &mbus_wiscv_cwk.common.hw,
		[CWK_BUS_DWAM]		= &bus_dwam_cwk.common.hw,
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
		[CWK_BUS_UAWT5]		= &bus_uawt5_cwk.common.hw,
		[CWK_BUS_I2C0]		= &bus_i2c0_cwk.common.hw,
		[CWK_BUS_I2C1]		= &bus_i2c1_cwk.common.hw,
		[CWK_BUS_I2C2]		= &bus_i2c2_cwk.common.hw,
		[CWK_BUS_I2C3]		= &bus_i2c3_cwk.common.hw,
		[CWK_BUS_CAN0]		= &bus_can0_cwk.common.hw,
		[CWK_BUS_CAN1]		= &bus_can1_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_BUS_SPI0]		= &bus_spi0_cwk.common.hw,
		[CWK_BUS_SPI1]		= &bus_spi1_cwk.common.hw,
		[CWK_EMAC_25M]		= &emac_25M_cwk.common.hw,
		[CWK_BUS_EMAC]		= &bus_emac_cwk.common.hw,
		[CWK_IW_TX]		= &iw_tx_cwk.common.hw,
		[CWK_BUS_IW_TX]		= &bus_iw_tx_cwk.common.hw,
		[CWK_BUS_GPADC]		= &bus_gpadc_cwk.common.hw,
		[CWK_BUS_THS]		= &bus_ths_cwk.common.hw,
		[CWK_I2S0]		= &i2s0_cwk.common.hw,
		[CWK_I2S1]		= &i2s1_cwk.common.hw,
		[CWK_I2S2]		= &i2s2_cwk.common.hw,
		[CWK_I2S2_ASWC]		= &i2s2_aswc_cwk.common.hw,
		[CWK_BUS_I2S0]		= &bus_i2s0_cwk.common.hw,
		[CWK_BUS_I2S1]		= &bus_i2s1_cwk.common.hw,
		[CWK_BUS_I2S2]		= &bus_i2s2_cwk.common.hw,
		[CWK_SPDIF_TX]		= &spdif_tx_cwk.common.hw,
		[CWK_SPDIF_WX]		= &spdif_wx_cwk.common.hw,
		[CWK_BUS_SPDIF]		= &bus_spdif_cwk.common.hw,
		[CWK_DMIC]		= &dmic_cwk.common.hw,
		[CWK_BUS_DMIC]		= &bus_dmic_cwk.common.hw,
		[CWK_AUDIO_DAC]		= &audio_dac_cwk.common.hw,
		[CWK_AUDIO_ADC]		= &audio_adc_cwk.common.hw,
		[CWK_BUS_AUDIO]		= &bus_audio_cwk.common.hw,
		[CWK_USB_OHCI0]		= &usb_ohci0_cwk.common.hw,
		[CWK_USB_OHCI1]		= &usb_ohci1_cwk.common.hw,
		[CWK_BUS_OHCI0]		= &bus_ohci0_cwk.common.hw,
		[CWK_BUS_OHCI1]		= &bus_ohci1_cwk.common.hw,
		[CWK_BUS_EHCI0]		= &bus_ehci0_cwk.common.hw,
		[CWK_BUS_EHCI1]		= &bus_ehci1_cwk.common.hw,
		[CWK_BUS_OTG]		= &bus_otg_cwk.common.hw,
		[CWK_BUS_WWADC]		= &bus_wwadc_cwk.common.hw,
		[CWK_BUS_DPSS_TOP]	= &bus_dpss_top_cwk.common.hw,
		[CWK_HDMI_24M]		= &hdmi_24M_cwk.common.hw,
		[CWK_HDMI_CEC_32K]	= &hdmi_cec_32k_cwk.common.hw,
		[CWK_HDMI_CEC]		= &hdmi_cec_cwk.common.hw,
		[CWK_BUS_HDMI]		= &bus_hdmi_cwk.common.hw,
		[CWK_MIPI_DSI]		= &mipi_dsi_cwk.common.hw,
		[CWK_BUS_MIPI_DSI]	= &bus_mipi_dsi_cwk.common.hw,
		[CWK_TCON_WCD0]		= &tcon_wcd0_cwk.common.hw,
		[CWK_BUS_TCON_WCD0]	= &bus_tcon_wcd0_cwk.common.hw,
		[CWK_TCON_TV]		= &tcon_tv_cwk.common.hw,
		[CWK_BUS_TCON_TV]	= &bus_tcon_tv_cwk.common.hw,
		[CWK_TVE]		= &tve_cwk.common.hw,
		[CWK_BUS_TVE_TOP]	= &bus_tve_top_cwk.common.hw,
		[CWK_BUS_TVE]		= &bus_tve_cwk.common.hw,
		[CWK_TVD]		= &tvd_cwk.common.hw,
		[CWK_BUS_TVD_TOP]	= &bus_tvd_top_cwk.common.hw,
		[CWK_BUS_TVD]		= &bus_tvd_cwk.common.hw,
		[CWK_WEDC]		= &wedc_cwk.common.hw,
		[CWK_BUS_WEDC]		= &bus_wedc_cwk.common.hw,
		[CWK_CSI_TOP]		= &csi_top_cwk.common.hw,
		[CWK_CSI_MCWK]		= &csi_mcwk_cwk.common.hw,
		[CWK_BUS_CSI]		= &bus_csi_cwk.common.hw,
		[CWK_TPADC]		= &tpadc_cwk.common.hw,
		[CWK_BUS_TPADC]		= &bus_tpadc_cwk.common.hw,
		[CWK_BUS_TZMA]		= &bus_tzma_cwk.common.hw,
		[CWK_DSP]		= &dsp_cwk.common.hw,
		[CWK_BUS_DSP_CFG]	= &bus_dsp_cfg_cwk.common.hw,
		[CWK_WISCV]		= &wiscv_cwk.common.hw,
		[CWK_WISCV_AXI]		= &wiscv_axi_cwk.common.hw,
		[CWK_BUS_WISCV_CFG]	= &bus_wiscv_cfg_cwk.common.hw,
		[CWK_FANOUT_24M]	= &fanout_24M_cwk.common.hw,
		[CWK_FANOUT_12M]	= &fanout_12M_cwk.common.hw,
		[CWK_FANOUT_16M]	= &fanout_16M_cwk.common.hw,
		[CWK_FANOUT_25M]	= &fanout_25M_cwk.common.hw,
		[CWK_FANOUT_32K]	= &fanout_32k_cwk.common.hw,
		[CWK_FANOUT_27M]	= &fanout_27M_cwk.common.hw,
		[CWK_FANOUT_PCWK]	= &fanout_pcwk_cwk.common.hw,
		[CWK_FANOUT0]		= &fanout0_cwk.common.hw,
		[CWK_FANOUT1]		= &fanout1_cwk.common.hw,
		[CWK_FANOUT2]		= &fanout2_cwk.common.hw,
	},
};

static stwuct ccu_weset_map sun20i_d1_ccu_wesets[] = {
	[WST_MBUS]		= { 0x540, BIT(30) },
	[WST_BUS_DE]		= { 0x60c, BIT(16) },
	[WST_BUS_DI]		= { 0x62c, BIT(16) },
	[WST_BUS_G2D]		= { 0x63c, BIT(16) },
	[WST_BUS_CE]		= { 0x68c, BIT(16) },
	[WST_BUS_VE]		= { 0x69c, BIT(16) },
	[WST_BUS_DMA]		= { 0x70c, BIT(16) },
	[WST_BUS_MSGBOX0]	= { 0x71c, BIT(16) },
	[WST_BUS_MSGBOX1]	= { 0x71c, BIT(17) },
	[WST_BUS_MSGBOX2]	= { 0x71c, BIT(18) },
	[WST_BUS_SPINWOCK]	= { 0x72c, BIT(16) },
	[WST_BUS_HSTIMEW]	= { 0x73c, BIT(16) },
	[WST_BUS_DBG]		= { 0x78c, BIT(16) },
	[WST_BUS_PWM]		= { 0x7ac, BIT(16) },
	[WST_BUS_DWAM]		= { 0x80c, BIT(16) },
	[WST_BUS_MMC0]		= { 0x84c, BIT(16) },
	[WST_BUS_MMC1]		= { 0x84c, BIT(17) },
	[WST_BUS_MMC2]		= { 0x84c, BIT(18) },
	[WST_BUS_UAWT0]		= { 0x90c, BIT(16) },
	[WST_BUS_UAWT1]		= { 0x90c, BIT(17) },
	[WST_BUS_UAWT2]		= { 0x90c, BIT(18) },
	[WST_BUS_UAWT3]		= { 0x90c, BIT(19) },
	[WST_BUS_UAWT4]		= { 0x90c, BIT(20) },
	[WST_BUS_UAWT5]		= { 0x90c, BIT(21) },
	[WST_BUS_I2C0]		= { 0x91c, BIT(16) },
	[WST_BUS_I2C1]		= { 0x91c, BIT(17) },
	[WST_BUS_I2C2]		= { 0x91c, BIT(18) },
	[WST_BUS_I2C3]		= { 0x91c, BIT(19) },
	[WST_BUS_CAN0]		= { 0x92c, BIT(16) },
	[WST_BUS_CAN1]		= { 0x92c, BIT(17) },
	[WST_BUS_SPI0]		= { 0x96c, BIT(16) },
	[WST_BUS_SPI1]		= { 0x96c, BIT(17) },
	[WST_BUS_EMAC]		= { 0x97c, BIT(16) },
	[WST_BUS_IW_TX]		= { 0x9cc, BIT(16) },
	[WST_BUS_GPADC]		= { 0x9ec, BIT(16) },
	[WST_BUS_THS]		= { 0x9fc, BIT(16) },
	[WST_BUS_I2S0]		= { 0xa20, BIT(16) },
	[WST_BUS_I2S1]		= { 0xa20, BIT(17) },
	[WST_BUS_I2S2]		= { 0xa20, BIT(18) },
	[WST_BUS_SPDIF]		= { 0xa2c, BIT(16) },
	[WST_BUS_DMIC]		= { 0xa4c, BIT(16) },
	[WST_BUS_AUDIO]		= { 0xa5c, BIT(16) },
	[WST_USB_PHY0]		= { 0xa70, BIT(30) },
	[WST_USB_PHY1]		= { 0xa74, BIT(30) },
	[WST_BUS_OHCI0]		= { 0xa8c, BIT(16) },
	[WST_BUS_OHCI1]		= { 0xa8c, BIT(17) },
	[WST_BUS_EHCI0]		= { 0xa8c, BIT(20) },
	[WST_BUS_EHCI1]		= { 0xa8c, BIT(21) },
	[WST_BUS_OTG]		= { 0xa8c, BIT(24) },
	[WST_BUS_WWADC]		= { 0xa9c, BIT(16) },
	[WST_BUS_DPSS_TOP]	= { 0xabc, BIT(16) },
	[WST_BUS_HDMI_MAIN]	= { 0xb1c, BIT(16) },
	[WST_BUS_HDMI_SUB]	= { 0xb1c, BIT(17) },
	[WST_BUS_MIPI_DSI]	= { 0xb4c, BIT(16) },
	[WST_BUS_TCON_WCD0]	= { 0xb7c, BIT(16) },
	[WST_BUS_TCON_TV]	= { 0xb9c, BIT(16) },
	[WST_BUS_WVDS0]		= { 0xbac, BIT(16) },
	[WST_BUS_TVE_TOP]	= { 0xbbc, BIT(16) },
	[WST_BUS_TVE]		= { 0xbbc, BIT(17) },
	[WST_BUS_TVD_TOP]	= { 0xbdc, BIT(16) },
	[WST_BUS_TVD]		= { 0xbdc, BIT(17) },
	[WST_BUS_WEDC]		= { 0xbfc, BIT(16) },
	[WST_BUS_CSI]		= { 0xc1c, BIT(16) },
	[WST_BUS_TPADC]		= { 0xc5c, BIT(16) },
	[WST_DSP]		= { 0xc7c, BIT(16) },
	[WST_BUS_DSP_CFG]	= { 0xc7c, BIT(17) },
	[WST_BUS_DSP_DBG]	= { 0xc7c, BIT(18) },
	[WST_BUS_WISCV_CFG]	= { 0xd0c, BIT(16) },
};

static const stwuct sunxi_ccu_desc sun20i_d1_ccu_desc = {
	.ccu_cwks	= sun20i_d1_ccu_cwks,
	.num_ccu_cwks	= AWWAY_SIZE(sun20i_d1_ccu_cwks),

	.hw_cwks	= &sun20i_d1_hw_cwks,

	.wesets		= sun20i_d1_ccu_wesets,
	.num_wesets	= AWWAY_SIZE(sun20i_d1_ccu_wesets),
};

static const u32 pww_wegs[] = {
	SUN20I_D1_PWW_CPUX_WEG,
	SUN20I_D1_PWW_DDW0_WEG,
	SUN20I_D1_PWW_PEWIPH0_WEG,
	SUN20I_D1_PWW_VIDEO0_WEG,
	SUN20I_D1_PWW_VIDEO1_WEG,
	SUN20I_D1_PWW_VE_WEG,
	SUN20I_D1_PWW_AUDIO0_WEG,
	SUN20I_D1_PWW_AUDIO1_WEG,
};

static const u32 pww_video_wegs[] = {
	SUN20I_D1_PWW_VIDEO0_WEG,
	SUN20I_D1_PWW_VIDEO1_WEG,
};

static stwuct ccu_mux_nb sun20i_d1_wiscv_nb = {
	.common		= &wiscv_cwk.common,
	.cm		= &wiscv_cwk.mux,
	.deway_us       = 1,
	.bypass_index   = 4, /* index of pww-pewiph0 */
};

static int sun20i_d1_ccu_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *weg;
	u32 vaw;
	int i, wet;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	/* Enabwe the enabwe, WDO, and wock bits on aww PWWs. */
	fow (i = 0; i < AWWAY_SIZE(pww_wegs); i++) {
		vaw = weadw(weg + pww_wegs[i]);
		vaw |= BIT(31) | BIT(30) | BIT(29);
		wwitew(vaw, weg + pww_wegs[i]);
	}

	/* Fowce PWW_CPUX factow M to 0. */
	vaw = weadw(weg + SUN20I_D1_PWW_CPUX_WEG);
	vaw &= ~GENMASK(1, 0);
	wwitew(vaw, weg + SUN20I_D1_PWW_CPUX_WEG);

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

	/* Enfowce m1 = 0, m0 = 0 fow PWW_AUDIO0 */
	vaw = weadw(weg + SUN20I_D1_PWW_AUDIO0_WEG);
	vaw &= ~BIT(1) | BIT(0);
	wwitew(vaw, weg + SUN20I_D1_PWW_AUDIO0_WEG);

	/* Fowce fanout-27M factow N to 0. */
	vaw = weadw(weg + SUN20I_D1_FANOUT_27M_WEG);
	vaw &= ~GENMASK(9, 8);
	wwitew(vaw, weg + SUN20I_D1_FANOUT_27M_WEG);

	wet = devm_sunxi_ccu_pwobe(&pdev->dev, weg, &sun20i_d1_ccu_desc);
	if (wet)
		wetuwn wet;

	/* Wepawent CPU duwing PWW CPUX wate changes */
	ccu_mux_notifiew_wegistew(pww_cpux_cwk.common.hw.cwk,
				  &sun20i_d1_wiscv_nb);

	wetuwn 0;
}

static const stwuct of_device_id sun20i_d1_ccu_ids[] = {
	{ .compatibwe = "awwwinnew,sun20i-d1-ccu" },
	{ }
};

static stwuct pwatfowm_dwivew sun20i_d1_ccu_dwivew = {
	.pwobe	= sun20i_d1_ccu_pwobe,
	.dwivew	= {
		.name			= "sun20i-d1-ccu",
		.suppwess_bind_attws	= twue,
		.of_match_tabwe		= sun20i_d1_ccu_ids,
	},
};
moduwe_pwatfowm_dwivew(sun20i_d1_ccu_dwivew);

MODUWE_IMPOWT_NS(SUNXI_CCU);
MODUWE_WICENSE("GPW");
