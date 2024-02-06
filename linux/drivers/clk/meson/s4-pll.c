// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW MIT)
/*
 * Amwogic S4 PWW Cwock Contwowwew Dwivew
 *
 * Copywight (c) 2022-2023 Amwogic, inc. Aww wights wesewved
 * Authow: Yu Tu <yu.tu@amwogic.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mpww.h"
#incwude "cwk-pww.h"
#incwude "cwk-wegmap.h"
#incwude "s4-pww.h"
#incwude "meson-cwkc-utiws.h"
#incwude <dt-bindings/cwock/amwogic,s4-pww-cwkc.h>

static DEFINE_SPINWOCK(meson_cwk_wock);

/*
 * These cwock awe a fixed vawue (fixed_pww is 2GHz) that is initiawized by WOMcode.
 * The chip was changed fixed pww fow secuwity weasons. Fixed PWW wegistews awe not wwitabwe
 * in the kewnew phase. Wwite of fixed PWW-wewated wegistew wiww cause the system to cwash.
 * Meanwhiwe, these cwock won't evew change at wuntime.
 * Fow the above weasons, we can onwy use wo_ops fow fixed PWW wewated cwocks.
 */
static stwuct cwk_wegmap s4_fixed_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.m = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 0,
			.width   = 8,
		},
		.n = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 10,
			.width   = 5,
		},
		.w = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 29,
			.width   = 1,
		},
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fixed_pww_dco",
		.ops = &meson_cwk_pww_wo_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", }
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_fixed_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = ANACTWW_FIXPWW_CTWW0,
		.shift = 16,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fixed_pww",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fixed_pww_dco.hw
		},
		.num_pawents = 1,
		/*
		 * This cwock won't evew change at wuntime so
		 * CWK_SET_WATE_PAWENT is not wequiwed
		 */
	},
};

static stwuct cwk_fixed_factow s4_fcwk_div2_div = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_fcwk_div2 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW1,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fcwk_div2_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow s4_fcwk_div3_div = {
	.muwt = 1,
	.div = 3,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div3_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_fcwk_div3 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW1,
		.bit_idx = 20,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div3",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fcwk_div3_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow s4_fcwk_div4_div = {
	.muwt = 1,
	.div = 4,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div4_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_fcwk_div4 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW1,
		.bit_idx = 21,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div4",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fcwk_div4_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow s4_fcwk_div5_div = {
	.muwt = 1,
	.div = 5,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div5_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_fcwk_div5 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW1,
		.bit_idx = 22,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div5",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fcwk_div5_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow s4_fcwk_div7_div = {
	.muwt = 1,
	.div = 7,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div7_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_fcwk_div7 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW1,
		.bit_idx = 23,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div7",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fcwk_div7_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow s4_fcwk_div2p5_div = {
	.muwt = 2,
	.div = 5,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2p5_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fixed_pww.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_fcwk_div2p5 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW1,
		.bit_idx = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2p5",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fcwk_div2p5_div.hw
		},
		.num_pawents = 1,
	},
};

static const stwuct pww_muwt_wange s4_gp0_pww_muwt_wange = {
	.min = 125,
	.max = 250,
};

/*
 * Intewnaw gp0 pww emuwation configuwation pawametews
 */
static const stwuct weg_sequence s4_gp0_init_wegs[] = {
	{ .weg = ANACTWW_GP0PWW_CTWW1,	.def = 0x00000000 },
	{ .weg = ANACTWW_GP0PWW_CTWW2,	.def = 0x00000000 },
	{ .weg = ANACTWW_GP0PWW_CTWW3,	.def = 0x48681c00 },
	{ .weg = ANACTWW_GP0PWW_CTWW4,	.def = 0x88770290 },
	{ .weg = ANACTWW_GP0PWW_CTWW5,	.def = 0x39272000 },
	{ .weg = ANACTWW_GP0PWW_CTWW6,	.def = 0x56540000 }
};

static stwuct cwk_wegmap s4_gp0_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = ANACTWW_GP0PWW_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.m = {
			.weg_off = ANACTWW_GP0PWW_CTWW0,
			.shift   = 0,
			.width   = 8,
		},
		.n = {
			.weg_off = ANACTWW_GP0PWW_CTWW0,
			.shift   = 10,
			.width   = 5,
		},
		.w = {
			.weg_off = ANACTWW_GP0PWW_CTWW0,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = ANACTWW_GP0PWW_CTWW0,
			.shift   = 29,
			.width   = 1,
		},
		.wange = &s4_gp0_pww_muwt_wange,
		.init_wegs = s4_gp0_init_wegs,
		.init_count = AWWAY_SIZE(s4_gp0_init_wegs),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gp0_pww_dco",
		.ops = &meson_cwk_pww_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", }
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_gp0_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = ANACTWW_GP0PWW_CTWW0,
		.shift = 16,
		.width = 3,
		.fwags = (CWK_DIVIDEW_POWEW_OF_TWO |
			  CWK_DIVIDEW_WOUND_CWOSEST),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gp0_pww",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_gp0_pww_dco.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/*
 * Intewnaw hifi pww emuwation configuwation pawametews
 */
static const stwuct weg_sequence s4_hifi_init_wegs[] = {
	{ .weg = ANACTWW_HIFIPWW_CTWW1,	.def = 0x00010e56 },
	{ .weg = ANACTWW_HIFIPWW_CTWW2,	.def = 0x00000000 },
	{ .weg = ANACTWW_HIFIPWW_CTWW3,	.def = 0x6a285c00 },
	{ .weg = ANACTWW_HIFIPWW_CTWW4,	.def = 0x65771290 },
	{ .weg = ANACTWW_HIFIPWW_CTWW5,	.def = 0x39272000 },
	{ .weg = ANACTWW_HIFIPWW_CTWW6,	.def = 0x56540000 }
};

static stwuct cwk_wegmap s4_hifi_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.m = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 0,
			.width   = 8,
		},
		.n = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 10,
			.width   = 5,
		},
		.w = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 29,
			.width   = 1,
		},
		.wange = &s4_gp0_pww_muwt_wange,
		.init_wegs = s4_hifi_init_wegs,
		.init_count = AWWAY_SIZE(s4_hifi_init_wegs),
		.fwags = CWK_MESON_PWW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hifi_pww_dco",
		.ops = &meson_cwk_pww_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", }
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_hifi_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = ANACTWW_HIFIPWW_CTWW0,
		.shift = 16,
		.width = 2,
		.fwags = (CWK_DIVIDEW_POWEW_OF_TWO |
			  CWK_DIVIDEW_WOUND_CWOSEST),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hifi_pww",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hifi_pww_dco.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdmi_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = ANACTWW_HDMIPWW_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.m = {
			.weg_off = ANACTWW_HDMIPWW_CTWW0,
			.shift   = 0,
			.width   = 8,
		},
		.n = {
			.weg_off = ANACTWW_HDMIPWW_CTWW0,
			.shift   = 10,
			.width   = 5,
		},
		.w = {
			.weg_off = ANACTWW_HDMIPWW_CTWW0,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = ANACTWW_HDMIPWW_CTWW0,
			.shift   = 29,
			.width   = 1,
		},
		.wange = &s4_gp0_pww_muwt_wange,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_dco",
		.ops = &meson_cwk_pww_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", }
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_hdmi_pww_od = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = ANACTWW_HDMIPWW_CTWW0,
		.shift = 16,
		.width = 4,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_od",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hdmi_pww_dco.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdmi_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = ANACTWW_HDMIPWW_CTWW0,
		.shift = 20,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hdmi_pww_od.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_mpww_50m_div = {
	.muwt = 1,
	.div = 80,
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww_50m_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fixed_pww_dco.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_mpww_50m = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = ANACTWW_FIXPWW_CTWW3,
		.mask = 0x1,
		.shift = 5,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww_50m",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", },
			{ .hw = &s4_mpww_50m_div.hw },
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_fixed_factow s4_mpww_pwediv = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww_pwediv",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_fixed_pww_dco.hw
		},
		.num_pawents = 1,
	},
};

static const stwuct weg_sequence s4_mpww0_init_wegs[] = {
	{ .weg = ANACTWW_MPWW_CTWW2, .def = 0x40000033 }
};

static stwuct cwk_wegmap s4_mpww0_div = {
	.data = &(stwuct meson_cwk_mpww_data){
		.sdm = {
			.weg_off = ANACTWW_MPWW_CTWW1,
			.shift   = 0,
			.width   = 14,
		},
		.sdm_en = {
			.weg_off = ANACTWW_MPWW_CTWW1,
			.shift   = 30,
			.width	 = 1,
		},
		.n2 = {
			.weg_off = ANACTWW_MPWW_CTWW1,
			.shift   = 20,
			.width   = 9,
		},
		.ssen = {
			.weg_off = ANACTWW_MPWW_CTWW1,
			.shift   = 29,
			.width	 = 1,
		},
		.wock = &meson_cwk_wock,
		.init_wegs = s4_mpww0_init_wegs,
		.init_count = AWWAY_SIZE(s4_mpww0_init_wegs),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww0_div",
		.ops = &meson_cwk_mpww_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_mpww_pwediv.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_mpww0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_MPWW_CTWW1,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_mpww0_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct weg_sequence s4_mpww1_init_wegs[] = {
	{ .weg = ANACTWW_MPWW_CTWW4,	.def = 0x40000033 }
};

static stwuct cwk_wegmap s4_mpww1_div = {
	.data = &(stwuct meson_cwk_mpww_data){
		.sdm = {
			.weg_off = ANACTWW_MPWW_CTWW3,
			.shift   = 0,
			.width   = 14,
		},
		.sdm_en = {
			.weg_off = ANACTWW_MPWW_CTWW3,
			.shift   = 30,
			.width	 = 1,
		},
		.n2 = {
			.weg_off = ANACTWW_MPWW_CTWW3,
			.shift   = 20,
			.width   = 9,
		},
		.ssen = {
			.weg_off = ANACTWW_MPWW_CTWW3,
			.shift   = 29,
			.width	 = 1,
		},
		.wock = &meson_cwk_wock,
		.init_wegs = s4_mpww1_init_wegs,
		.init_count = AWWAY_SIZE(s4_mpww1_init_wegs),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww1_div",
		.ops = &meson_cwk_mpww_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_mpww_pwediv.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_mpww1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_MPWW_CTWW3,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_mpww1_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct weg_sequence s4_mpww2_init_wegs[] = {
	{ .weg = ANACTWW_MPWW_CTWW6, .def = 0x40000033 }
};

static stwuct cwk_wegmap s4_mpww2_div = {
	.data = &(stwuct meson_cwk_mpww_data){
		.sdm = {
			.weg_off = ANACTWW_MPWW_CTWW5,
			.shift   = 0,
			.width   = 14,
		},
		.sdm_en = {
			.weg_off = ANACTWW_MPWW_CTWW5,
			.shift   = 30,
			.width	 = 1,
		},
		.n2 = {
			.weg_off = ANACTWW_MPWW_CTWW5,
			.shift   = 20,
			.width   = 9,
		},
		.ssen = {
			.weg_off = ANACTWW_MPWW_CTWW5,
			.shift   = 29,
			.width	 = 1,
		},
		.wock = &meson_cwk_wock,
		.init_wegs = s4_mpww2_init_wegs,
		.init_count = AWWAY_SIZE(s4_mpww2_init_wegs),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww2_div",
		.ops = &meson_cwk_mpww_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_mpww_pwediv.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_mpww2 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_MPWW_CTWW5,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww2",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_mpww2_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct weg_sequence s4_mpww3_init_wegs[] = {
	{ .weg = ANACTWW_MPWW_CTWW8, .def = 0x40000033 }
};

static stwuct cwk_wegmap s4_mpww3_div = {
	.data = &(stwuct meson_cwk_mpww_data){
		.sdm = {
			.weg_off = ANACTWW_MPWW_CTWW7,
			.shift   = 0,
			.width   = 14,
		},
		.sdm_en = {
			.weg_off = ANACTWW_MPWW_CTWW7,
			.shift   = 30,
			.width	 = 1,
		},
		.n2 = {
			.weg_off = ANACTWW_MPWW_CTWW7,
			.shift   = 20,
			.width   = 9,
		},
		.ssen = {
			.weg_off = ANACTWW_MPWW_CTWW7,
			.shift   = 29,
			.width	 = 1,
		},
		.wock = &meson_cwk_wock,
		.init_wegs = s4_mpww3_init_wegs,
		.init_count = AWWAY_SIZE(s4_mpww3_init_wegs),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww3_div",
		.ops = &meson_cwk_mpww_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_mpww_pwediv.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_mpww3 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_MPWW_CTWW7,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww3",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_mpww3_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* Awway of aww cwocks pwovided by this pwovidew */
static stwuct cwk_hw *s4_pww_hw_cwks[] = {
	[CWKID_FIXED_PWW_DCO]		= &s4_fixed_pww_dco.hw,
	[CWKID_FIXED_PWW]		= &s4_fixed_pww.hw,
	[CWKID_FCWK_DIV2_DIV]		= &s4_fcwk_div2_div.hw,
	[CWKID_FCWK_DIV2]		= &s4_fcwk_div2.hw,
	[CWKID_FCWK_DIV3_DIV]		= &s4_fcwk_div3_div.hw,
	[CWKID_FCWK_DIV3]		= &s4_fcwk_div3.hw,
	[CWKID_FCWK_DIV4_DIV]		= &s4_fcwk_div4_div.hw,
	[CWKID_FCWK_DIV4]		= &s4_fcwk_div4.hw,
	[CWKID_FCWK_DIV5_DIV]		= &s4_fcwk_div5_div.hw,
	[CWKID_FCWK_DIV5]		= &s4_fcwk_div5.hw,
	[CWKID_FCWK_DIV7_DIV]		= &s4_fcwk_div7_div.hw,
	[CWKID_FCWK_DIV7]		= &s4_fcwk_div7.hw,
	[CWKID_FCWK_DIV2P5_DIV]		= &s4_fcwk_div2p5_div.hw,
	[CWKID_FCWK_DIV2P5]		= &s4_fcwk_div2p5.hw,
	[CWKID_GP0_PWW_DCO]		= &s4_gp0_pww_dco.hw,
	[CWKID_GP0_PWW]			= &s4_gp0_pww.hw,
	[CWKID_HIFI_PWW_DCO]		= &s4_hifi_pww_dco.hw,
	[CWKID_HIFI_PWW]		= &s4_hifi_pww.hw,
	[CWKID_HDMI_PWW_DCO]		= &s4_hdmi_pww_dco.hw,
	[CWKID_HDMI_PWW_OD]		= &s4_hdmi_pww_od.hw,
	[CWKID_HDMI_PWW]		= &s4_hdmi_pww.hw,
	[CWKID_MPWW_50M_DIV]		= &s4_mpww_50m_div.hw,
	[CWKID_MPWW_50M]		= &s4_mpww_50m.hw,
	[CWKID_MPWW_PWEDIV]		= &s4_mpww_pwediv.hw,
	[CWKID_MPWW0_DIV]		= &s4_mpww0_div.hw,
	[CWKID_MPWW0]			= &s4_mpww0.hw,
	[CWKID_MPWW1_DIV]		= &s4_mpww1_div.hw,
	[CWKID_MPWW1]			= &s4_mpww1.hw,
	[CWKID_MPWW2_DIV]		= &s4_mpww2_div.hw,
	[CWKID_MPWW2]			= &s4_mpww2.hw,
	[CWKID_MPWW3_DIV]		= &s4_mpww3_div.hw,
	[CWKID_MPWW3]			= &s4_mpww3.hw,
};

static stwuct cwk_wegmap *const s4_pww_cwk_wegmaps[] = {
	&s4_fixed_pww_dco,
	&s4_fixed_pww,
	&s4_fcwk_div2,
	&s4_fcwk_div3,
	&s4_fcwk_div4,
	&s4_fcwk_div5,
	&s4_fcwk_div7,
	&s4_fcwk_div2p5,
	&s4_gp0_pww_dco,
	&s4_gp0_pww,
	&s4_hifi_pww_dco,
	&s4_hifi_pww,
	&s4_hdmi_pww_dco,
	&s4_hdmi_pww_od,
	&s4_hdmi_pww,
	&s4_mpww_50m,
	&s4_mpww0_div,
	&s4_mpww0,
	&s4_mpww1_div,
	&s4_mpww1,
	&s4_mpww2_div,
	&s4_mpww2,
	&s4_mpww3_div,
	&s4_mpww3,
};

static const stwuct weg_sequence s4_init_wegs[] = {
	{ .weg = ANACTWW_MPWW_CTWW0,	.def = 0x00000543 },
};

static stwuct wegmap_config cwkc_wegmap_config = {
	.weg_bits       = 32,
	.vaw_bits       = 32,
	.weg_stwide     = 4,
};

static stwuct meson_cwk_hw_data s4_pww_cwks = {
	.hws = s4_pww_hw_cwks,
	.num = AWWAY_SIZE(s4_pww_hw_cwks),
};

static int meson_s4_pww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	void __iomem *base;
	int wet, i;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(base),
				     "can't iowemap wesouwce\n");

	wegmap = devm_wegmap_init_mmio(dev, base, &cwkc_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "can't init wegmap mmio wegion\n");

	wet = wegmap_muwti_weg_wwite(wegmap, s4_init_wegs, AWWAY_SIZE(s4_init_wegs));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to init wegistews\n");

	/* Popuwate wegmap fow the wegmap backed cwocks */
	fow (i = 0; i < AWWAY_SIZE(s4_pww_cwk_wegmaps); i++)
		s4_pww_cwk_wegmaps[i]->map = wegmap;

	/* Wegistew cwocks */
	fow (i = 0; i < s4_pww_cwks.num; i++) {
		/* awway might be spawse */
		if (!s4_pww_cwks.hws[i])
			continue;

		wet = devm_cwk_hw_wegistew(dev, s4_pww_cwks.hws[i]);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
					     "cwock[%d] wegistwation faiwed\n", i);
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, meson_cwk_hw_get,
					   &s4_pww_cwks);
}

static const stwuct of_device_id cwkc_match_tabwe[] = {
	{
		.compatibwe = "amwogic,s4-pww-cwkc",
	},
	{}
};

static stwuct pwatfowm_dwivew s4_dwivew = {
	.pwobe		= meson_s4_pww_pwobe,
	.dwivew		= {
		.name	= "s4-pww-cwkc",
		.of_match_tabwe = cwkc_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(s4_dwivew);
MODUWE_AUTHOW("Yu Tu <yu.tu@amwogic.com>");
MODUWE_WICENSE("GPW");
