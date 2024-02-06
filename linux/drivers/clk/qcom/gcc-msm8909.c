// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Kewnkonzept GmbH.
 *
 * Based on gcc-msm8916.c:
 *   Copywight 2015 Winawo Wimited
 * adapted with data fwom cwock-gcc-8909.c in Quawcomm's msm-3.18 wewease:
 *   Copywight (c) 2014-2016, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,gcc-msm8909.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

/* Need to match the owdew of cwocks in DT binding */
enum {
	DT_XO,
	DT_SWEEP_CWK,
	DT_DSI0PWW,
	DT_DSI0PWW_BYTE,
};

enum {
	P_XO,
	P_SWEEP_CWK,
	P_GPWW0,
	P_GPWW1,
	P_GPWW2,
	P_BIMC,
	P_DSI0PWW,
	P_DSI0PWW_BYTE,
};

static const stwuct pawent_map gcc_xo_map[] = {
	{ P_XO, 0 },
};

static const stwuct cwk_pawent_data gcc_xo_data[] = {
	{ .index = DT_XO },
};

static const stwuct cwk_pawent_data gcc_sweep_cwk_data[] = {
	{ .index = DT_SWEEP_CWK },
};

static stwuct cwk_awpha_pww gpww0_eawwy = {
	.offset = 0x21000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x45000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gpww0_eawwy",
			.pawent_data = gcc_xo_data,
			.num_pawents = AWWAY_SIZE(gcc_xo_data),
			/* Avoid wate changes fow shawed cwock */
			.ops = &cwk_awpha_pww_fixed_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gpww0 = {
	.offset = 0x21000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gpww0",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gpww0_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		/* Avoid wate changes fow shawed cwock */
		.ops = &cwk_awpha_pww_postdiv_wo_ops,
	},
};

static stwuct cwk_pww gpww1 = {
	.w_weg = 0x20004,
	.m_weg = 0x20008,
	.n_weg = 0x2000c,
	.config_weg = 0x20010,
	.mode_weg = 0x20000,
	.status_weg = 0x2001c,
	.status_bit = 17,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gpww1",
		.pawent_data = gcc_xo_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_data),
		.ops = &cwk_pww_ops,
	},
};

static stwuct cwk_wegmap gpww1_vote = {
	.enabwe_weg = 0x45000,
	.enabwe_mask = BIT(1),
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gpww1_vote",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gpww1.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_pww_vote_ops,
	},
};

static stwuct cwk_awpha_pww gpww2_eawwy = {
	.offset = 0x25000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x45000,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gpww2_eawwy",
			.pawent_data = gcc_xo_data,
			.num_pawents = AWWAY_SIZE(gcc_xo_data),
			/* Avoid wate changes fow shawed cwock */
			.ops = &cwk_awpha_pww_fixed_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gpww2 = {
	.offset = 0x25000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gpww2",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gpww2_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		/* Avoid wate changes fow shawed cwock */
		.ops = &cwk_awpha_pww_postdiv_wo_ops,
	},
};

static stwuct cwk_awpha_pww bimc_pww_eawwy = {
	.offset = 0x23000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x45000,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "bimc_pww_eawwy",
			.pawent_data = gcc_xo_data,
			.num_pawents = AWWAY_SIZE(gcc_xo_data),
			/* Avoid wate changes fow shawed cwock */
			.ops = &cwk_awpha_pww_fixed_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv bimc_pww = {
	.offset = 0x23000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bimc_pww",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&bimc_pww_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		/* Avoid wate changes fow shawed cwock */
		.ops = &cwk_awpha_pww_postdiv_wo_ops,
	},
};

static const stwuct pawent_map gcc_xo_gpww0_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
};

static const stwuct cwk_pawent_data gcc_xo_gpww0_data[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
};

static const stwuct pawent_map gcc_xo_gpww0_bimc_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_BIMC, 2 },
};

static const stwuct cwk_pawent_data gcc_xo_gpww0_bimc_data[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &bimc_pww.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_apss_ahb_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPWW0, 16, 0, 0),
	F(100000000, P_GPWW0, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 apss_ahb_cwk_swc = {
	.cmd_wcgw = 0x46000,
	.hid_width = 5,
	.fweq_tbw = ftbw_apss_ahb_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "apss_ahb_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bimc_ddw_cwk_swc = {
	.cmd_wcgw = 0x32004,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_bimc_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bimc_ddw_cwk_swc",
		.pawent_data = gcc_xo_gpww0_bimc_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_bimc_data),
		.ops = &cwk_wcg2_ops,
		.fwags = CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wcg2 bimc_gpu_cwk_swc = {
	.cmd_wcgw = 0x31028,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_bimc_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bimc_gpu_cwk_swc",
		.pawent_data = gcc_xo_gpww0_bimc_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_bimc_data),
		.ops = &cwk_wcg2_ops,
		.fwags = CWK_GET_WATE_NOCACHE,
	},
};

static const stwuct fweq_tbw ftbw_bwsp_i2c_apps_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPWW0, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup1_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x0200c,
	.hid_width = 5,
	.fweq_tbw = ftbw_bwsp_i2c_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup1_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup2_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x03000,
	.hid_width = 5,
	.fweq_tbw = ftbw_bwsp_i2c_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup2_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup3_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x04000,
	.hid_width = 5,
	.fweq_tbw = ftbw_bwsp_i2c_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup3_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup4_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x05000,
	.hid_width = 5,
	.fweq_tbw = ftbw_bwsp_i2c_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup4_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup5_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x06000,
	.hid_width = 5,
	.fweq_tbw = ftbw_bwsp_i2c_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup5_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup6_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x07000,
	.hid_width = 5,
	.fweq_tbw = ftbw_bwsp_i2c_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup6_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_bwsp_spi_apps_cwk_swc[] = {
	F(960000, P_XO, 10, 1, 2),
	F(4800000, P_XO, 4, 0, 0),
	F(9600000, P_XO, 2, 0, 0),
	F(16000000, P_GPWW0, 10, 1, 5),
	F(19200000, P_XO, 1, 0, 0),
	F(25000000, P_GPWW0, 16, 1, 2),
	F(50000000, P_GPWW0, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup1_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x02024,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_bwsp_spi_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup1_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup2_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x03014,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_bwsp_spi_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup2_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup3_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x04024,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_bwsp_spi_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup3_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup4_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x05024,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_bwsp_spi_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup4_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup5_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x06024,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_bwsp_spi_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup5_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_qup6_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x07024,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_bwsp_spi_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_qup6_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_bwsp_uawt_apps_cwk_swc[] = {
	F(3686400, P_GPWW0, 1, 72, 15625),
	F(7372800, P_GPWW0, 1, 144, 15625),
	F(14745600, P_GPWW0, 1, 288, 15625),
	F(16000000, P_GPWW0, 10, 1, 5),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_GPWW0, 1, 3, 100),
	F(25000000, P_GPWW0, 16, 1, 2),
	F(32000000, P_GPWW0, 1, 1, 25),
	F(40000000, P_GPWW0, 1, 1, 20),
	F(46400000, P_GPWW0, 1, 29, 500),
	F(48000000, P_GPWW0, 1, 3, 50),
	F(51200000, P_GPWW0, 1, 8, 125),
	F(56000000, P_GPWW0, 1, 7, 100),
	F(58982400, P_GPWW0, 1, 1152, 15625),
	F(60000000, P_GPWW0, 1, 3, 40),
	{ }
};

static stwuct cwk_wcg2 bwsp1_uawt1_apps_cwk_swc = {
	.cmd_wcgw = 0x02044,
	.hid_width = 5,
	.mnd_width = 16,
	.fweq_tbw = ftbw_bwsp_uawt_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_uawt1_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 bwsp1_uawt2_apps_cwk_swc = {
	.cmd_wcgw = 0x03034,
	.hid_width = 5,
	.mnd_width = 16,
	.fweq_tbw = ftbw_bwsp_uawt_apps_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "bwsp1_uawt2_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct pawent_map gcc_byte0_map[] = {
	{ P_XO, 0 },
	{ P_DSI0PWW_BYTE, 1 },
};

static const stwuct cwk_pawent_data gcc_byte_data[] = {
	{ .index = DT_XO },
	{ .index = DT_DSI0PWW_BYTE },
};

static stwuct cwk_wcg2 byte0_cwk_swc = {
	.cmd_wcgw = 0x4d044,
	.hid_width = 5,
	.pawent_map = gcc_byte0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "byte0_cwk_swc",
		.pawent_data = gcc_byte_data,
		.num_pawents = AWWAY_SIZE(gcc_byte_data),
		.ops = &cwk_byte2_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	}
};

static const stwuct fweq_tbw ftbw_camss_gp_cwk_swc[] = {
	F(100000000, P_GPWW0, 8, 0, 0),
	F(200000000, P_GPWW0, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camss_gp0_cwk_swc = {
	.cmd_wcgw = 0x54000,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_camss_gp_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "camss_gp0_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 camss_gp1_cwk_swc = {
	.cmd_wcgw = 0x55000,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_camss_gp_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "camss_gp1_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_camss_top_ahb_cwk_swc[] = {
	F(40000000, P_GPWW0, 10, 1, 2),
	F(80000000, P_GPWW0, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camss_top_ahb_cwk_swc = {
	.cmd_wcgw = 0x5a000,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_camss_top_ahb_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "camss_top_ahb_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_cwypto_cwk_swc[] = {
	F(50000000, P_GPWW0, 16, 0, 0),
	F(80000000, P_GPWW0, 10, 0, 0),
	F(100000000, P_GPWW0, 8, 0, 0),
	F(160000000, P_GPWW0, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cwypto_cwk_swc = {
	.cmd_wcgw = 0x16004,
	.hid_width = 5,
	.fweq_tbw = ftbw_cwypto_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "cwypto_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_csi_cwk_swc[] = {
	F(100000000, P_GPWW0, 8, 0, 0),
	F(200000000, P_GPWW0, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 csi0_cwk_swc = {
	.cmd_wcgw = 0x4e020,
	.hid_width = 5,
	.fweq_tbw = ftbw_csi_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "csi0_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_map),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 csi1_cwk_swc = {
	.cmd_wcgw = 0x4f020,
	.hid_width = 5,
	.fweq_tbw = ftbw_csi_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "csi1_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_csi_phytimew_cwk_swc[] = {
	F(100000000, P_GPWW0, 8, 0, 0),
	F(200000000, P_GPWW0, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x4e000,
	.hid_width = 5,
	.fweq_tbw = ftbw_csi_phytimew_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "csi0phytimew_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_esc0_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 esc0_cwk_swc = {
	.cmd_wcgw = 0x4d05c,
	.hid_width = 5,
	.fweq_tbw = ftbw_esc0_cwk_swc,
	.pawent_map = gcc_xo_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "esc0_cwk_swc",
		.pawent_data = gcc_xo_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct pawent_map gcc_gfx3d_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_GPWW1, 2 },
};

static const stwuct cwk_pawent_data gcc_gfx3d_data[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww1_vote.hw },
};

static const stwuct fweq_tbw ftbw_gfx3d_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPWW0, 16, 0, 0),
	F(80000000, P_GPWW0, 10, 0, 0),
	F(100000000, P_GPWW0, 8, 0, 0),
	F(160000000, P_GPWW0, 5, 0, 0),
	F(177780000, P_GPWW0, 4.5, 0, 0),
	F(200000000, P_GPWW0, 4, 0, 0),
	F(266670000, P_GPWW0, 3, 0, 0),
	F(307200000, P_GPWW1, 4, 0, 0),
	F(409600000, P_GPWW1, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gfx3d_cwk_swc = {
	.cmd_wcgw = 0x59000,
	.hid_width = 5,
	.fweq_tbw = ftbw_gfx3d_cwk_swc,
	.pawent_map = gcc_gfx3d_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gfx3d_cwk_swc",
		.pawent_data = gcc_gfx3d_data,
		.num_pawents = AWWAY_SIZE(gcc_gfx3d_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_gp_cwk_swc[] = {
	F(150000, P_XO, 1, 1, 128),
	F(19200000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gp1_cwk_swc = {
	.cmd_wcgw = 0x08004,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_gp_cwk_swc,
	.pawent_map = gcc_xo_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gp1_cwk_swc",
		.pawent_data = gcc_xo_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 gp2_cwk_swc = {
	.cmd_wcgw = 0x09004,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_gp_cwk_swc,
	.pawent_map = gcc_xo_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gp2_cwk_swc",
		.pawent_data = gcc_xo_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 gp3_cwk_swc = {
	.cmd_wcgw = 0x0a004,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_gp_cwk_swc,
	.pawent_map = gcc_xo_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "gp3_cwk_swc",
		.pawent_data = gcc_xo_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct pawent_map gcc_mcwk_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_GPWW2, 3 },
};

static const stwuct cwk_pawent_data gcc_mcwk_data[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww2.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_mcwk_cwk_swc[] = {
	F(24000000, P_GPWW2, 1, 1, 33),
	F(66667000, P_GPWW0, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 mcwk0_cwk_swc = {
	.cmd_wcgw = 0x52000,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_mcwk_cwk_swc,
	.pawent_map = gcc_mcwk_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "mcwk0_cwk_swc",
		.pawent_data = gcc_mcwk_data,
		.num_pawents = AWWAY_SIZE(gcc_mcwk_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_wcg2 mcwk1_cwk_swc = {
	.cmd_wcgw = 0x53000,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_mcwk_cwk_swc,
	.pawent_map = gcc_mcwk_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "mcwk1_cwk_swc",
		.pawent_data = gcc_mcwk_data,
		.num_pawents = AWWAY_SIZE(gcc_mcwk_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct pawent_map gcc_mdp_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_GPWW1, 3 },
};

static const stwuct cwk_pawent_data gcc_mdp_data[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww1_vote.hw },
};

static const stwuct fweq_tbw ftbw_mdp_cwk_swc[] = {
	F(50000000, P_GPWW0, 16, 0, 0),
	F(80000000, P_GPWW0, 10, 0, 0),
	F(100000000, P_GPWW0, 8, 0, 0),
	F(160000000, P_GPWW0, 5, 0, 0),
	F(177780000, P_GPWW0, 4.5, 0, 0),
	F(200000000, P_GPWW0, 4, 0, 0),
	F(266670000, P_GPWW0, 3, 0, 0),
	F(307200000, P_GPWW1, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 mdp_cwk_swc = {
	.cmd_wcgw = 0x4d014,
	.hid_width = 5,
	.fweq_tbw = ftbw_mdp_cwk_swc,
	.pawent_map = gcc_mdp_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "mdp_cwk_swc",
		.pawent_data = gcc_mdp_data,
		.num_pawents = AWWAY_SIZE(gcc_mdp_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct pawent_map gcc_pcwk0_map[] = {
	{ P_XO, 0 },
	{ P_DSI0PWW, 1 },
};

static const stwuct cwk_pawent_data gcc_pcwk_data[] = {
	{ .index = DT_XO },
	{ .index = DT_DSI0PWW },
};

static stwuct cwk_wcg2 pcwk0_cwk_swc = {
	.cmd_wcgw = 0x4d000,
	.hid_width = 5,
	.mnd_width = 8,
	.pawent_map = gcc_pcwk0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pcwk0_cwk_swc",
		.pawent_data = gcc_pcwk_data,
		.num_pawents = AWWAY_SIZE(gcc_pcwk_data),
		.ops = &cwk_pixew_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	}
};

static stwuct cwk_wcg2 pcnoc_bfdcd_cwk_swc = {
	.cmd_wcgw = 0x27000,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_bimc_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pcnoc_bfdcd_cwk_swc",
		.pawent_data = gcc_xo_gpww0_bimc_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_bimc_data),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_pdm2_cwk_swc[] = {
	F(64000000, P_GPWW0, 12.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 pdm2_cwk_swc = {
	.cmd_wcgw = 0x44010,
	.hid_width = 5,
	.fweq_tbw = ftbw_pdm2_cwk_swc,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "pdm2_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_gcc_sdcc1_2_apps_cwk[] = {
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPWW0, 10, 1, 4),
	F(25000000, P_GPWW0, 16, 1, 2),
	F(50000000, P_GPWW0, 16, 0, 0),
	F(100000000, P_GPWW0, 8, 0, 0),
	F(177770000, P_GPWW0, 4.5, 0, 0),
	F(200000000, P_GPWW0, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x42004,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_gcc_sdcc1_2_apps_cwk,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "sdcc1_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_fwoow_ops,
	}
};

static stwuct cwk_wcg2 sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x43004,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_gcc_sdcc1_2_apps_cwk,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "sdcc2_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_fwoow_ops,
	}
};

static stwuct cwk_wcg2 system_noc_bfdcd_cwk_swc = {
	.cmd_wcgw = 0x26004,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_bimc_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "system_noc_bfdcd_cwk_swc",
		.pawent_data = gcc_xo_gpww0_bimc_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_bimc_data),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gcc_usb_hs_system_cwk[] = {
	F(57140000, P_GPWW0, 14, 0, 0),
	F(80000000, P_GPWW0, 10, 0, 0),
	F(100000000, P_GPWW0, 8, 0, 0),
	{ }
};

static stwuct cwk_wcg2 usb_hs_system_cwk_swc = {
	.cmd_wcgw = 0x41010,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_usb_hs_system_cwk,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "usb_hs_system_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct pawent_map gcc_vcodec0_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_GPWW1, 3 },
};

static const stwuct cwk_pawent_data gcc_vcodec0_data[] = {
	{ .index = DT_XO },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww1_vote.hw },
};

static const stwuct fweq_tbw ftbw_vcodec0_cwk_swc[] = {
	F(133330000, P_GPWW0, 6, 0, 0),
	F(266670000, P_GPWW0, 3, 0, 0),
	F(307200000, P_GPWW1, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 vcodec0_cwk_swc = {
	.cmd_wcgw = 0x4c000,
	.hid_width = 5,
	.mnd_width = 8,
	.fweq_tbw = ftbw_vcodec0_cwk_swc,
	.pawent_map = gcc_vcodec0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "vcodec0_cwk_swc",
		.pawent_data = gcc_vcodec0_data,
		.num_pawents = AWWAY_SIZE(gcc_vcodec0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_gcc_camss_vfe0_cwk[] = {
	F(50000000, P_GPWW0, 16, 0, 0),
	F(80000000, P_GPWW0, 10, 0, 0),
	F(100000000, P_GPWW0, 8, 0, 0),
	F(133330000, P_GPWW0, 6, 0, 0),
	F(160000000, P_GPWW0, 5, 0, 0),
	F(177780000, P_GPWW0, 4.5, 0, 0),
	F(200000000, P_GPWW0, 4, 0, 0),
	F(266670000, P_GPWW0, 3, 0, 0),
	F(320000000, P_GPWW0, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 vfe0_cwk_swc = {
	.cmd_wcgw = 0x58000,
	.hid_width = 5,
	.fweq_tbw = ftbw_gcc_camss_vfe0_cwk,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "vfe0_cwk_swc",
		.pawent_data = gcc_xo_gpww0_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_data),
		.ops = &cwk_wcg2_ops,
	}
};

static const stwuct fweq_tbw ftbw_vsync_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 vsync_cwk_swc = {
	.cmd_wcgw = 0x4d02c,
	.hid_width = 5,
	.fweq_tbw = ftbw_vsync_cwk_swc,
	.pawent_map = gcc_xo_map,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "vsync_cwk_swc",
		.pawent_data = gcc_xo_data,
		.num_pawents = AWWAY_SIZE(gcc_xo_data),
		.ops = &cwk_wcg2_ops,
	}
};

static stwuct cwk_bwanch gcc_apss_tcu_cwk = {
	.hawt_weg = 0x12018,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_apss_tcu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bimc_ddw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_ahb_cwk = {
	.hawt_weg = 0x01008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_sweep_cwk = {
	.hawt_weg = 0x01004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_sweep_cwk",
			.pawent_data = gcc_sweep_cwk_data,
			.num_pawents = AWWAY_SIZE(gcc_sweep_cwk_data),
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x1300c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_boot_wom_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_cwypto_cwk = {
	.hawt_weg = 0x1601c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cwypto_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_cwypto_ahb_cwk = {
	.hawt_weg = 0x16024,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_cwypto_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_cwypto_axi_cwk = {
	.hawt_weg = 0x16020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_cwypto_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_gfx_tbu_cwk = {
	.hawt_weg = 0x12010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_gfx_tbu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bimc_ddw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_gfx_tcu_cwk = {
	.hawt_weg = 0x12020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_gfx_tcu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bimc_ddw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_gtcu_ahb_cwk = {
	.hawt_weg = 0x12044,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_gtcu_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_mdp_tbu_cwk = {
	.hawt_weg = 0x1201c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mdp_tbu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_pwng_ahb_cwk = {
	.hawt_weg = 0x13004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x45004,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pwng_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_smmu_cfg_cwk = {
	.hawt_weg = 0x12038,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(12),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_smmu_cfg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_venus_tbu_cwk = {
	.hawt_weg = 0x12014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_venus_tbu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_vfe_tbu_cwk = {
	.hawt_weg = 0x1203c,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x4500c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_vfe_tbu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_bimc_gfx_cwk = {
	.hawt_weg = 0x31024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bimc_gfx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bimc_gpu_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_bimc_gpu_cwk = {
	.hawt_weg = 0x31040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bimc_gpu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bimc_gpu_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_i2c_apps_cwk = {
	.hawt_weg = 0x02008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x02008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup1_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup1_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_i2c_apps_cwk = {
	.hawt_weg = 0x03010,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x03010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup2_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup2_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_i2c_apps_cwk = {
	.hawt_weg = 0x04020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x04020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup3_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup3_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_i2c_apps_cwk = {
	.hawt_weg = 0x05020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x05020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup4_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup4_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup5_i2c_apps_cwk = {
	.hawt_weg = 0x06020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x06020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup5_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup5_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup6_i2c_apps_cwk = {
	.hawt_weg = 0x07020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x07020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup6_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup6_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_spi_apps_cwk = {
	.hawt_weg = 0x02004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x02004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup1_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup1_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_spi_apps_cwk = {
	.hawt_weg = 0x0300c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0300c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup2_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup2_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_spi_apps_cwk = {
	.hawt_weg = 0x0401c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0401c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup3_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup3_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_spi_apps_cwk = {
	.hawt_weg = 0x0501c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup4_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup4_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup5_spi_apps_cwk = {
	.hawt_weg = 0x0601c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0601c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup5_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup5_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_qup6_spi_apps_cwk = {
	.hawt_weg = 0x0701c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0701c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_qup6_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_qup6_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_uawt1_apps_cwk = {
	.hawt_weg = 0x0203c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0203c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_uawt1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_uawt1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_bwsp1_uawt2_apps_cwk = {
	.hawt_weg = 0x0302c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0302c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_bwsp1_uawt2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bwsp1_uawt2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_ahb_cwk = {
	.hawt_weg = 0x5a014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5a014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi0_cwk = {
	.hawt_weg = 0x4e03c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi0_ahb_cwk = {
	.hawt_weg = 0x4e040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&camss_top_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi0phy_cwk = {
	.hawt_weg = 0x4e048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi0phy_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi0phytimew_cwk = {
	.hawt_weg = 0x4e01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi0phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi0pix_cwk = {
	.hawt_weg = 0x4e058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi0pix_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi0wdi_cwk = {
	.hawt_weg = 0x4e050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4e050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi0wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi1_cwk = {
	.hawt_weg = 0x4f03c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4f03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi1_ahb_cwk = {
	.hawt_weg = 0x4f040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4f040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&camss_top_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi1phy_cwk = {
	.hawt_weg = 0x4f048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4f048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi1phy_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi1pix_cwk = {
	.hawt_weg = 0x4f058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4f058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi1pix_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi1wdi_cwk = {
	.hawt_weg = 0x4f050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4f050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi1wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&csi1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_csi_vfe0_cwk = {
	.hawt_weg = 0x58050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x58050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_csi_vfe0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&vfe0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_gp0_cwk = {
	.hawt_weg = 0x54018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x54018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_gp0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&camss_gp0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_gp1_cwk = {
	.hawt_weg = 0x55018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x55018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&camss_gp1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_ispif_ahb_cwk = {
	.hawt_weg = 0x50004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x50004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_ispif_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&camss_top_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_mcwk0_cwk = {
	.hawt_weg = 0x52018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x52018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&mcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_mcwk1_cwk = {
	.hawt_weg = 0x53018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x53018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&mcwk1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_top_ahb_cwk = {
	.hawt_weg = 0x56004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x56004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_top_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&camss_top_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_vfe0_cwk = {
	.hawt_weg = 0x58038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x58038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_vfe0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&vfe0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_vfe_ahb_cwk = {
	.hawt_weg = 0x58044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x58044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_vfe_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&camss_top_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_camss_vfe_axi_cwk = {
	.hawt_weg = 0x58048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x58048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_camss_vfe_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x08000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x08000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gp1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_gp2_cwk = {
	.hawt_weg = 0x09000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x09000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_gp2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gp2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_gp3_cwk = {
	.hawt_weg = 0x0a000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x0a000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_gp3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gp3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_mdss_ahb_cwk = {
	.hawt_weg = 0x4d07c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mdss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_mdss_axi_cwk = {
	.hawt_weg = 0x4d080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mdss_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_mdss_byte0_cwk = {
	.hawt_weg = 0x4d094,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d094,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mdss_byte0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&byte0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_mdss_esc0_cwk = {
	.hawt_weg = 0x4d098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mdss_esc0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&esc0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_mdss_mdp_cwk = {
	.hawt_weg = 0x4d088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mdss_mdp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&mdp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_mdss_pcwk0_cwk = {
	.hawt_weg = 0x4d084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mdss_pcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_mdss_vsync_cwk = {
	.hawt_weg = 0x4d090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4d090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mdss_vsync_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&vsync_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_mss_cfg_ahb_cwk = {
	.hawt_weg = 0x49000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mss_cfg_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_mss_q6_bimc_axi_cwk = {
	.hawt_weg = 0x49004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x49004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_mss_q6_bimc_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&bimc_ddw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_oxiwi_ahb_cwk = {
	.hawt_weg = 0x59028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_oxiwi_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_oxiwi_gfx3d_cwk = {
	.hawt_weg = 0x59020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x59020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_oxiwi_gfx3d_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_pdm2_cwk = {
	.hawt_weg = 0x4400c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4400c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pdm2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pdm2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_pdm_ahb_cwk = {
	.hawt_weg = 0x44004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x44004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_pdm_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x4201c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4201c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_sdcc1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x42018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x42018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_sdcc1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&sdcc1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_sdcc2_ahb_cwk = {
	.hawt_weg = 0x4301c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4301c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_sdcc2_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_sdcc2_apps_cwk = {
	.hawt_weg = 0x43018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x43018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_sdcc2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&sdcc2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_usb2a_phy_sweep_cwk = {
	.hawt_weg = 0x4102c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4102c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_usb2a_phy_sweep_cwk",
			.pawent_data = gcc_sweep_cwk_data,
			.num_pawents = AWWAY_SIZE(gcc_sweep_cwk_data),
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_usb_hs_ahb_cwk = {
	.hawt_weg = 0x41008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x41008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_usb_hs_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_usb_hs_phy_cfg_ahb_cwk = {
	.hawt_weg = 0x41030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x41030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_usb_hs_phy_cfg_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_usb_hs_system_cwk = {
	.hawt_weg = 0x41004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x41004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_usb_hs_system_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&usb_hs_system_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_venus0_ahb_cwk = {
	.hawt_weg = 0x4c020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4c020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_venus0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&pcnoc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_venus0_axi_cwk = {
	.hawt_weg = 0x4c024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4c024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_venus0_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&system_noc_bfdcd_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		}
	}
};

static stwuct cwk_bwanch gcc_venus0_cowe0_vcodec0_cwk = {
	.hawt_weg = 0x4c02c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4c02c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_venus0_cowe0_vcodec0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&vcodec0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct cwk_bwanch gcc_venus0_vcodec0_cwk = {
	.hawt_weg = 0x4c01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x4c01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data) {
			.name = "gcc_venus0_vcodec0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&vcodec0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		}
	}
};

static stwuct gdsc mdss_gdsc = {
	.gdscw = 0x4d078,
	.cxcs = (unsigned int []) { 0x4d080, 0x4d088 },
	.cxc_count = 2,
	.pd = {
		.name = "mdss_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc oxiwi_gdsc = {
	.gdscw = 0x5901c,
	.cxcs = (unsigned int []) { 0x59020 },
	.cxc_count = 1,
	.pd = {
		.name = "oxiwi_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc venus_gdsc = {
	.gdscw = 0x4c018,
	.cxcs = (unsigned int []) { 0x4c024, 0x4c01c },
	.cxc_count = 2,
	.pd = {
		.name = "venus_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc venus_cowe0_gdsc = {
	.gdscw = 0x4c028,
	.cxcs = (unsigned int []) { 0x4c02c },
	.cxc_count = 1,
	.pd = {
		.name = "venus_cowe0_gdsc",
	},
	.fwags = HW_CTWW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc vfe_gdsc = {
	.gdscw = 0x58034,
	.cxcs = (unsigned int []) { 0x58038, 0x58048, 0x58050 },
	.cxc_count = 3,
	.pd = {
		.name = "vfe_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *gcc_msm8909_cwocks[] = {
	[GPWW0_EAWWY] = &gpww0_eawwy.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW1] = &gpww1.cwkw,
	[GPWW1_VOTE] = &gpww1_vote,
	[GPWW2_EAWWY] = &gpww2_eawwy.cwkw,
	[GPWW2] = &gpww2.cwkw,
	[BIMC_PWW_EAWWY] = &bimc_pww_eawwy.cwkw,
	[BIMC_PWW] = &bimc_pww.cwkw,
	[APSS_AHB_CWK_SWC] = &apss_ahb_cwk_swc.cwkw,
	[BIMC_DDW_CWK_SWC] = &bimc_ddw_cwk_swc.cwkw,
	[BIMC_GPU_CWK_SWC] = &bimc_gpu_cwk_swc.cwkw,
	[BWSP1_QUP1_I2C_APPS_CWK_SWC] = &bwsp1_qup1_i2c_apps_cwk_swc.cwkw,
	[BWSP1_QUP1_SPI_APPS_CWK_SWC] = &bwsp1_qup1_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP2_I2C_APPS_CWK_SWC] = &bwsp1_qup2_i2c_apps_cwk_swc.cwkw,
	[BWSP1_QUP2_SPI_APPS_CWK_SWC] = &bwsp1_qup2_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP3_I2C_APPS_CWK_SWC] = &bwsp1_qup3_i2c_apps_cwk_swc.cwkw,
	[BWSP1_QUP3_SPI_APPS_CWK_SWC] = &bwsp1_qup3_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP4_I2C_APPS_CWK_SWC] = &bwsp1_qup4_i2c_apps_cwk_swc.cwkw,
	[BWSP1_QUP4_SPI_APPS_CWK_SWC] = &bwsp1_qup4_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP5_I2C_APPS_CWK_SWC] = &bwsp1_qup5_i2c_apps_cwk_swc.cwkw,
	[BWSP1_QUP5_SPI_APPS_CWK_SWC] = &bwsp1_qup5_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP6_I2C_APPS_CWK_SWC] = &bwsp1_qup6_i2c_apps_cwk_swc.cwkw,
	[BWSP1_QUP6_SPI_APPS_CWK_SWC] = &bwsp1_qup6_spi_apps_cwk_swc.cwkw,
	[BWSP1_UAWT1_APPS_CWK_SWC] = &bwsp1_uawt1_apps_cwk_swc.cwkw,
	[BWSP1_UAWT2_APPS_CWK_SWC] = &bwsp1_uawt2_apps_cwk_swc.cwkw,
	[BYTE0_CWK_SWC] = &byte0_cwk_swc.cwkw,
	[CAMSS_GP0_CWK_SWC] = &camss_gp0_cwk_swc.cwkw,
	[CAMSS_GP1_CWK_SWC] = &camss_gp1_cwk_swc.cwkw,
	[CAMSS_TOP_AHB_CWK_SWC] = &camss_top_ahb_cwk_swc.cwkw,
	[CWYPTO_CWK_SWC] = &cwypto_cwk_swc.cwkw,
	[CSI0_CWK_SWC] = &csi0_cwk_swc.cwkw,
	[CSI0PHYTIMEW_CWK_SWC] = &csi0phytimew_cwk_swc.cwkw,
	[CSI1_CWK_SWC] = &csi1_cwk_swc.cwkw,
	[ESC0_CWK_SWC] = &esc0_cwk_swc.cwkw,
	[GFX3D_CWK_SWC] = &gfx3d_cwk_swc.cwkw,
	[GP1_CWK_SWC] = &gp1_cwk_swc.cwkw,
	[GP2_CWK_SWC] = &gp2_cwk_swc.cwkw,
	[GP3_CWK_SWC] = &gp3_cwk_swc.cwkw,
	[MCWK0_CWK_SWC] = &mcwk0_cwk_swc.cwkw,
	[MCWK1_CWK_SWC] = &mcwk1_cwk_swc.cwkw,
	[MDP_CWK_SWC] = &mdp_cwk_swc.cwkw,
	[PCWK0_CWK_SWC] = &pcwk0_cwk_swc.cwkw,
	[PCNOC_BFDCD_CWK_SWC] = &pcnoc_bfdcd_cwk_swc.cwkw,
	[PDM2_CWK_SWC] = &pdm2_cwk_swc.cwkw,
	[SDCC1_APPS_CWK_SWC] = &sdcc1_apps_cwk_swc.cwkw,
	[SDCC2_APPS_CWK_SWC] = &sdcc2_apps_cwk_swc.cwkw,
	[SYSTEM_NOC_BFDCD_CWK_SWC] = &system_noc_bfdcd_cwk_swc.cwkw,
	[USB_HS_SYSTEM_CWK_SWC] = &usb_hs_system_cwk_swc.cwkw,
	[VCODEC0_CWK_SWC] = &vcodec0_cwk_swc.cwkw,
	[VFE0_CWK_SWC] = &vfe0_cwk_swc.cwkw,
	[VSYNC_CWK_SWC] = &vsync_cwk_swc.cwkw,
	[GCC_APSS_TCU_CWK] = &gcc_apss_tcu_cwk.cwkw,
	[GCC_BWSP1_AHB_CWK] = &gcc_bwsp1_ahb_cwk.cwkw,
	[GCC_BWSP1_SWEEP_CWK] = &gcc_bwsp1_sweep_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_CWYPTO_CWK] = &gcc_cwypto_cwk.cwkw,
	[GCC_CWYPTO_AHB_CWK] = &gcc_cwypto_ahb_cwk.cwkw,
	[GCC_CWYPTO_AXI_CWK] = &gcc_cwypto_axi_cwk.cwkw,
	[GCC_GFX_TBU_CWK] = &gcc_gfx_tbu_cwk.cwkw,
	[GCC_GFX_TCU_CWK] = &gcc_gfx_tcu_cwk.cwkw,
	[GCC_GTCU_AHB_CWK] = &gcc_gtcu_ahb_cwk.cwkw,
	[GCC_MDP_TBU_CWK] = &gcc_mdp_tbu_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_SMMU_CFG_CWK] = &gcc_smmu_cfg_cwk.cwkw,
	[GCC_VENUS_TBU_CWK] = &gcc_venus_tbu_cwk.cwkw,
	[GCC_VFE_TBU_CWK] = &gcc_vfe_tbu_cwk.cwkw,
	[GCC_BIMC_GFX_CWK] = &gcc_bimc_gfx_cwk.cwkw,
	[GCC_BIMC_GPU_CWK] = &gcc_bimc_gpu_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK] = &gcc_bwsp1_qup1_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK] = &gcc_bwsp1_qup1_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK] = &gcc_bwsp1_qup2_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK] = &gcc_bwsp1_qup2_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK] = &gcc_bwsp1_qup3_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK] = &gcc_bwsp1_qup3_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_I2C_APPS_CWK] = &gcc_bwsp1_qup4_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_SPI_APPS_CWK] = &gcc_bwsp1_qup4_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP5_I2C_APPS_CWK] = &gcc_bwsp1_qup5_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP5_SPI_APPS_CWK] = &gcc_bwsp1_qup5_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP6_I2C_APPS_CWK] = &gcc_bwsp1_qup6_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_QUP6_SPI_APPS_CWK] = &gcc_bwsp1_qup6_spi_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK] = &gcc_bwsp1_uawt1_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK] = &gcc_bwsp1_uawt2_apps_cwk.cwkw,
	[GCC_CAMSS_AHB_CWK] = &gcc_camss_ahb_cwk.cwkw,
	[GCC_CAMSS_CSI0_CWK] = &gcc_camss_csi0_cwk.cwkw,
	[GCC_CAMSS_CSI0_AHB_CWK] = &gcc_camss_csi0_ahb_cwk.cwkw,
	[GCC_CAMSS_CSI0PHY_CWK] = &gcc_camss_csi0phy_cwk.cwkw,
	[GCC_CAMSS_CSI0PHYTIMEW_CWK] = &gcc_camss_csi0phytimew_cwk.cwkw,
	[GCC_CAMSS_CSI0PIX_CWK] = &gcc_camss_csi0pix_cwk.cwkw,
	[GCC_CAMSS_CSI0WDI_CWK] = &gcc_camss_csi0wdi_cwk.cwkw,
	[GCC_CAMSS_CSI1_CWK] = &gcc_camss_csi1_cwk.cwkw,
	[GCC_CAMSS_CSI1_AHB_CWK] = &gcc_camss_csi1_ahb_cwk.cwkw,
	[GCC_CAMSS_CSI1PHY_CWK] = &gcc_camss_csi1phy_cwk.cwkw,
	[GCC_CAMSS_CSI1PIX_CWK] = &gcc_camss_csi1pix_cwk.cwkw,
	[GCC_CAMSS_CSI1WDI_CWK] = &gcc_camss_csi1wdi_cwk.cwkw,
	[GCC_CAMSS_CSI_VFE0_CWK] = &gcc_camss_csi_vfe0_cwk.cwkw,
	[GCC_CAMSS_GP0_CWK] = &gcc_camss_gp0_cwk.cwkw,
	[GCC_CAMSS_GP1_CWK] = &gcc_camss_gp1_cwk.cwkw,
	[GCC_CAMSS_ISPIF_AHB_CWK] = &gcc_camss_ispif_ahb_cwk.cwkw,
	[GCC_CAMSS_MCWK0_CWK] = &gcc_camss_mcwk0_cwk.cwkw,
	[GCC_CAMSS_MCWK1_CWK] = &gcc_camss_mcwk1_cwk.cwkw,
	[GCC_CAMSS_TOP_AHB_CWK] = &gcc_camss_top_ahb_cwk.cwkw,
	[GCC_CAMSS_VFE0_CWK] = &gcc_camss_vfe0_cwk.cwkw,
	[GCC_CAMSS_VFE_AHB_CWK] = &gcc_camss_vfe_ahb_cwk.cwkw,
	[GCC_CAMSS_VFE_AXI_CWK] = &gcc_camss_vfe_axi_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_MDSS_AHB_CWK] = &gcc_mdss_ahb_cwk.cwkw,
	[GCC_MDSS_AXI_CWK] = &gcc_mdss_axi_cwk.cwkw,
	[GCC_MDSS_BYTE0_CWK] = &gcc_mdss_byte0_cwk.cwkw,
	[GCC_MDSS_ESC0_CWK] = &gcc_mdss_esc0_cwk.cwkw,
	[GCC_MDSS_MDP_CWK] = &gcc_mdss_mdp_cwk.cwkw,
	[GCC_MDSS_PCWK0_CWK] = &gcc_mdss_pcwk0_cwk.cwkw,
	[GCC_MDSS_VSYNC_CWK] = &gcc_mdss_vsync_cwk.cwkw,
	[GCC_MSS_CFG_AHB_CWK] = &gcc_mss_cfg_ahb_cwk.cwkw,
	[GCC_MSS_Q6_BIMC_AXI_CWK] = &gcc_mss_q6_bimc_axi_cwk.cwkw,
	[GCC_OXIWI_AHB_CWK] = &gcc_oxiwi_ahb_cwk.cwkw,
	[GCC_OXIWI_GFX3D_CWK] = &gcc_oxiwi_gfx3d_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_SDCC2_AHB_CWK] = &gcc_sdcc2_ahb_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK] = &gcc_sdcc2_apps_cwk.cwkw,
	[GCC_USB2A_PHY_SWEEP_CWK] = &gcc_usb2a_phy_sweep_cwk.cwkw,
	[GCC_USB_HS_AHB_CWK] = &gcc_usb_hs_ahb_cwk.cwkw,
	[GCC_USB_HS_PHY_CFG_AHB_CWK] = &gcc_usb_hs_phy_cfg_ahb_cwk.cwkw,
	[GCC_USB_HS_SYSTEM_CWK] = &gcc_usb_hs_system_cwk.cwkw,
	[GCC_VENUS0_AHB_CWK] = &gcc_venus0_ahb_cwk.cwkw,
	[GCC_VENUS0_AXI_CWK] = &gcc_venus0_axi_cwk.cwkw,
	[GCC_VENUS0_COWE0_VCODEC0_CWK] = &gcc_venus0_cowe0_vcodec0_cwk.cwkw,
	[GCC_VENUS0_VCODEC0_CWK] = &gcc_venus0_vcodec0_cwk.cwkw,
};

static stwuct gdsc *gcc_msm8909_gdscs[] = {
	[MDSS_GDSC] = &mdss_gdsc,
	[OXIWI_GDSC] = &oxiwi_gdsc,
	[VENUS_GDSC] = &venus_gdsc,
	[VENUS_COWE0_GDSC] = &venus_cowe0_gdsc,
	[VFE_GDSC] = &vfe_gdsc,
};

static const stwuct qcom_weset_map gcc_msm8909_wesets[] = {
	[GCC_AUDIO_COWE_BCW] = { 0x1c008 },
	[GCC_BWSP1_BCW] = { 0x01000 },
	[GCC_BWSP1_QUP1_BCW] = { 0x02000 },
	[GCC_BWSP1_QUP2_BCW] = { 0x03008 },
	[GCC_BWSP1_QUP3_BCW] = { 0x04018 },
	[GCC_BWSP1_QUP4_BCW] = { 0x05018 },
	[GCC_BWSP1_QUP5_BCW] = { 0x06018 },
	[GCC_BWSP1_QUP6_BCW] = { 0x07018 },
	[GCC_BWSP1_UAWT1_BCW] = { 0x02038 },
	[GCC_BWSP1_UAWT2_BCW] = { 0x03028 },
	[GCC_CAMSS_CSI0_BCW] = { 0x4e038 },
	[GCC_CAMSS_CSI0PHY_BCW] = { 0x4e044 },
	[GCC_CAMSS_CSI0PIX_BCW] = { 0x4e054 },
	[GCC_CAMSS_CSI0WDI_BCW] = { 0x4e04c },
	[GCC_CAMSS_CSI1_BCW] = { 0x4f038 },
	[GCC_CAMSS_CSI1PHY_BCW] = { 0x4f044 },
	[GCC_CAMSS_CSI1PIX_BCW] = { 0x4f054 },
	[GCC_CAMSS_CSI1WDI_BCW] = { 0x4f04c },
	[GCC_CAMSS_CSI_VFE0_BCW] = { 0x5804c },
	[GCC_CAMSS_GP0_BCW] = { 0x54014 },
	[GCC_CAMSS_GP1_BCW] = { 0x55014 },
	[GCC_CAMSS_ISPIF_BCW] = { 0x50000 },
	[GCC_CAMSS_MCWK0_BCW] = { 0x52014 },
	[GCC_CAMSS_MCWK1_BCW] = { 0x53014 },
	[GCC_CAMSS_PHY0_BCW] = { 0x4e018 },
	[GCC_CAMSS_TOP_BCW] = { 0x56000 },
	[GCC_CAMSS_TOP_AHB_BCW] = { 0x5a018 },
	[GCC_CAMSS_VFE_BCW] = { 0x58030 },
	[GCC_CWYPTO_BCW] = { 0x16000 },
	[GCC_MDSS_BCW] = { 0x4d074 },
	[GCC_OXIWI_BCW] = { 0x59018 },
	[GCC_PDM_BCW] = { 0x44000 },
	[GCC_PWNG_BCW] = { 0x13000 },
	[GCC_QUSB2_PHY_BCW] = { 0x4103c },
	[GCC_SDCC1_BCW] = { 0x42000 },
	[GCC_SDCC2_BCW] = { 0x43000 },
	[GCC_UWT_AUDIO_BCW] = { 0x1c0b4 },
	[GCC_USB2A_PHY_BCW] = { 0x41028 },
	[GCC_USB2_HS_PHY_ONWY_BCW] = { .weg = 0x41034, .udeway = 15 },
	[GCC_USB_HS_BCW] = { 0x41000 },
	[GCC_VENUS0_BCW] = { 0x4c014 },
	/* Subsystem Westawt */
	[GCC_MSS_WESTAWT] = { 0x3e000 },
};

static const stwuct wegmap_config gcc_msm8909_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x80000,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gcc_msm8909_desc = {
	.config = &gcc_msm8909_wegmap_config,
	.cwks = gcc_msm8909_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_msm8909_cwocks),
	.wesets = gcc_msm8909_wesets,
	.num_wesets = AWWAY_SIZE(gcc_msm8909_wesets),
	.gdscs = gcc_msm8909_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_msm8909_gdscs),
};

static const stwuct of_device_id gcc_msm8909_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-msm8909" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_msm8909_match_tabwe);

static int gcc_msm8909_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn qcom_cc_pwobe(pdev, &gcc_msm8909_desc);
}

static stwuct pwatfowm_dwivew gcc_msm8909_dwivew = {
	.pwobe		= gcc_msm8909_pwobe,
	.dwivew		= {
		.name	= "gcc-msm8909",
		.of_match_tabwe = gcc_msm8909_match_tabwe,
	},
};

static int __init gcc_msm8909_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_msm8909_dwivew);
}
cowe_initcaww(gcc_msm8909_init);

static void __exit gcc_msm8909_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_msm8909_dwivew);
}
moduwe_exit(gcc_msm8909_exit);

MODUWE_DESCWIPTION("Quawcomm GCC MSM8909 Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:gcc-msm8909");
