// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW MIT)
/*
 * Amwogic S4 Pewiphewaws Cwock Contwowwew Dwivew
 *
 * Copywight (c) 2022-2023 Amwogic, inc. Aww wights wesewved
 * Authow: Yu Tu <yu.tu@amwogic.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-wegmap.h"
#incwude "vid-pww-div.h"
#incwude "cwk-duawdiv.h"
#incwude "s4-pewiphewaws.h"
#incwude "meson-cwkc-utiws.h"
#incwude <dt-bindings/cwock/amwogic,s4-pewiphewaws-cwkc.h>

static stwuct cwk_wegmap s4_wtc_32k_by_oscin_cwkin = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_WTC_BY_OSCIN_CTWW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "wtc_32k_by_oscin_cwkin",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", }
		},
		.num_pawents = 1,
	},
};

static const stwuct meson_cwk_duawdiv_pawam s4_32k_div_tabwe[] = {
	{
		.duaw	= 1,
		.n1	= 733,
		.m1	= 8,
		.n2	= 732,
		.m2	= 11,
	},
	{}
};

static stwuct cwk_wegmap s4_wtc_32k_by_oscin_div = {
	.data = &(stwuct meson_cwk_duawdiv_data){
		.n1 = {
			.weg_off = CWKCTWW_WTC_BY_OSCIN_CTWW0,
			.shift   = 0,
			.width   = 12,
		},
		.n2 = {
			.weg_off = CWKCTWW_WTC_BY_OSCIN_CTWW0,
			.shift   = 12,
			.width   = 12,
		},
		.m1 = {
			.weg_off = CWKCTWW_WTC_BY_OSCIN_CTWW1,
			.shift   = 0,
			.width   = 12,
		},
		.m2 = {
			.weg_off = CWKCTWW_WTC_BY_OSCIN_CTWW1,
			.shift   = 12,
			.width   = 12,
		},
		.duaw = {
			.weg_off = CWKCTWW_WTC_BY_OSCIN_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.tabwe = s4_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "wtc_32k_by_oscin_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_wtc_32k_by_oscin_cwkin.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_wtc_32k_by_oscin_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_WTC_BY_OSCIN_CTWW1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "wtc_32k_by_oscin_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_wtc_32k_by_oscin_div.hw,
			&s4_wtc_32k_by_oscin_cwkin.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_wtc_32k_by_oscin = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_WTC_BY_OSCIN_CTWW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "wtc_32k_by_oscin",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_wtc_32k_by_oscin_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_wtc_cwk = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_WTC_CTWW,
		.mask = 0x3,
		.shift = 0,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "wtc_cwk_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_wtc_32k_by_oscin.hw,
			&s4_wtc_32k_by_oscin_div.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* The index 5 is AXI_CWK, which is dedicated to AXI. So skip it. */
static u32 mux_tabwe_sys_ab_cwk_sew[] = { 0, 1, 2, 3, 4, 6, 7 };
static const stwuct cwk_pawent_data sys_ab_cwk_pawent_data[] = {
	{ .fw_name = "xtaw" },
	{ .fw_name = "fcwk_div2" },
	{ .fw_name = "fcwk_div3" },
	{ .fw_name = "fcwk_div4" },
	{ .fw_name = "fcwk_div5" },
	{ .fw_name = "fcwk_div7" },
	{ .hw = &s4_wtc_cwk.hw }
};

/*
 * This cwock is initiawized by WOMcode.
 * The chip was changed SYS CWK fow secuwity weasons. SYS CWK wegistews awe not wwitabwe
 * in the kewnew phase. Wwite of SYS wewated wegistew wiww cause the system to cwash.
 * Meanwhiwe, these cwock won't evew change at wuntime.
 * Fow the above weasons, we can onwy use wo_ops fow SYS wewated cwocks.
 */
static stwuct cwk_wegmap s4_syscwk_b_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_SYS_CWK_CTWW0,
		.mask = 0x7,
		.shift = 26,
		.tabwe = mux_tabwe_sys_ab_cwk_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "syscwk_b_sew",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_data = sys_ab_cwk_pawent_data,
		.num_pawents = AWWAY_SIZE(sys_ab_cwk_pawent_data),
	},
};

static stwuct cwk_wegmap s4_syscwk_b_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_SYS_CWK_CTWW0,
		.shift = 16,
		.width = 10,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "syscwk_b_div",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_syscwk_b_sew.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_syscwk_b = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_SYS_CWK_CTWW0,
		.bit_idx = 29,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "syscwk_b",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_syscwk_b_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_syscwk_a_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_SYS_CWK_CTWW0,
		.mask = 0x7,
		.shift = 10,
		.tabwe = mux_tabwe_sys_ab_cwk_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "syscwk_a_sew",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_data = sys_ab_cwk_pawent_data,
		.num_pawents = AWWAY_SIZE(sys_ab_cwk_pawent_data),
	},
};

static stwuct cwk_wegmap s4_syscwk_a_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_SYS_CWK_CTWW0,
		.shift = 0,
		.width = 10,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "syscwk_a_div",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_syscwk_a_sew.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_syscwk_a = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_SYS_CWK_CTWW0,
		.bit_idx = 13,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "syscwk_a",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_syscwk_a_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_sys_cwk = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_SYS_CWK_CTWW0,
		.mask = 0x1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sys_cwk",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_syscwk_a.hw,
			&s4_syscwk_b.hw
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap s4_ceca_32k_cwkin = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_CECA_CTWW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "ceca_32k_cwkin",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", }
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_ceca_32k_div = {
	.data = &(stwuct meson_cwk_duawdiv_data){
		.n1 = {
			.weg_off = CWKCTWW_CECA_CTWW0,
			.shift   = 0,
			.width   = 12,
		},
		.n2 = {
			.weg_off = CWKCTWW_CECA_CTWW0,
			.shift   = 12,
			.width   = 12,
		},
		.m1 = {
			.weg_off = CWKCTWW_CECA_CTWW1,
			.shift   = 0,
			.width   = 12,
		},
		.m2 = {
			.weg_off = CWKCTWW_CECA_CTWW1,
			.shift   = 12,
			.width   = 12,
		},
		.duaw = {
			.weg_off = CWKCTWW_CECA_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.tabwe = s4_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ceca_32k_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_ceca_32k_cwkin.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_ceca_32k_sew_pwe = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_CECA_CTWW1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ceca_32k_sew_pwe",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_ceca_32k_div.hw,
			&s4_ceca_32k_cwkin.hw
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_ceca_32k_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_CECA_CTWW1,
		.mask = 0x1,
		.shift = 31,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ceca_32k_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_ceca_32k_sew_pwe.hw,
			&s4_wtc_cwk.hw
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap s4_ceca_32k_cwkout = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_CECA_CTWW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ceca_32k_cwkout",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_ceca_32k_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_cecb_32k_cwkin = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_CECB_CTWW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cecb_32k_cwkin",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", }
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_cecb_32k_div = {
	.data = &(stwuct meson_cwk_duawdiv_data){
		.n1 = {
			.weg_off = CWKCTWW_CECB_CTWW0,
			.shift   = 0,
			.width   = 12,
		},
		.n2 = {
			.weg_off = CWKCTWW_CECB_CTWW0,
			.shift   = 12,
			.width   = 12,
		},
		.m1 = {
			.weg_off = CWKCTWW_CECB_CTWW1,
			.shift   = 0,
			.width   = 12,
		},
		.m2 = {
			.weg_off = CWKCTWW_CECB_CTWW1,
			.shift   = 12,
			.width   = 12,
		},
		.duaw = {
			.weg_off = CWKCTWW_CECB_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.tabwe = s4_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cecb_32k_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_cecb_32k_cwkin.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_cecb_32k_sew_pwe = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_CECB_CTWW1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cecb_32k_sew_pwe",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_cecb_32k_div.hw,
			&s4_cecb_32k_cwkin.hw
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_cecb_32k_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_CECB_CTWW1,
		.mask = 0x1,
		.shift = 31,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cecb_32k_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_cecb_32k_sew_pwe.hw,
			&s4_wtc_cwk.hw
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap s4_cecb_32k_cwkout = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_CECB_CTWW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cecb_32k_cwkout",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_cecb_32k_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data s4_sc_pawent_data[] = {
	{ .fw_name = "fcwk_div4" },
	{ .fw_name = "fcwk_div3" },
	{ .fw_name = "fcwk_div5" },
	{ .fw_name = "xtaw", }
};

static stwuct cwk_wegmap s4_sc_cwk_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_SC_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sc_cwk_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_sc_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_sc_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sc_cwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_SC_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sc_cwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sc_cwk_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sc_cwk_gate = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_SC_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sc_cwk_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sc_cwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_12_24M_cwk_gate = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_CWK12_24_CTWW,
		.bit_idx = 11,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "12_24m_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", }
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow s4_12M_cwk_div = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "12M",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_12_24M_cwk_gate.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_12_24M_cwk = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_CWK12_24_CTWW,
		.mask = 0x1,
		.shift = 10,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "12_24m",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_12_24M_cwk_gate.hw,
			&s4_12M_cwk_div.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* Video Cwocks */
static stwuct cwk_wegmap s4_vid_pww_div = {
	.data = &(stwuct meson_vid_pww_div_data){
		.vaw = {
			.weg_off = CWKCTWW_VID_PWW_CWK_DIV,
			.shift   = 0,
			.width   = 15,
		},
		.sew = {
			.weg_off = CWKCTWW_VID_PWW_CWK_DIV,
			.shift   = 16,
			.width   = 2,
		},
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vid_pww_div",
		/*
		 * TODO meson_vid_pww_div_wo_ops to meson_vid_pww_div_ops
		 */
		.ops = &meson_vid_pww_div_wo_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "hdmi_pww", }
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vid_pww_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VID_PWW_CWK_DIV,
		.mask = 0x1,
		.shift = 18,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vid_pww_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .hw = &s4_vid_pww_div.hw },
			{ .fw_name = "hdmi_pww", }
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vid_pww = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_PWW_CWK_DIV,
		.bit_idx = 19,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vid_pww",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vid_pww_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data s4_vcwk_pawent_data[] = {
	{ .hw = &s4_vid_pww.hw },
	{ .fw_name = "gp0_pww", },
	{ .fw_name = "hifi_pww", },
	{ .fw_name = "mpww1", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
};

static stwuct cwk_wegmap s4_vcwk_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VID_CWK_CTWW,
		.mask = 0x7,
		.shift = 16,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vcwk_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vcwk_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vcwk2_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VIID_CWK_CTWW,
		.mask = 0x7,
		.shift = 16,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vcwk_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vcwk_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vcwk_input = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_DIV,
		.bit_idx = 16,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_input",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk2_input = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VIID_CWK_DIV,
		.bit_idx = 16,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_input",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk2_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VID_CWK_DIV,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk_input.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk2_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VIID_CWK_DIV,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk2_input.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW,
		.bit_idx = 19,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk2 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VIID_CWK_CTWW,
		.bit_idx = 19,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk2_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk_div1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk_div2_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW,
		.bit_idx = 1,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div2_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk_div4_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW,
		.bit_idx = 2,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div4_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk_div6_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW,
		.bit_idx = 3,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div6_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk_div12_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW,
		.bit_idx = 4,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div12_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk2_div1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VIID_CWK_CTWW,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk2_div2_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VIID_CWK_CTWW,
		.bit_idx = 1,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div2_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk2_div4_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VIID_CWK_CTWW,
		.bit_idx = 2,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div4_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk2_div6_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VIID_CWK_CTWW,
		.bit_idx = 3,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div6_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vcwk2_div12_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VIID_CWK_CTWW,
		.bit_idx = 4,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div12_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_vcwk_div2 = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div2",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk_div2_en.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_vcwk_div4 = {
	.muwt = 1,
	.div = 4,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div4",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk_div4_en.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_vcwk_div6 = {
	.muwt = 1,
	.div = 6,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div6",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk_div6_en.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_vcwk_div12 = {
	.muwt = 1,
	.div = 12,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div12",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk_div12_en.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_vcwk2_div2 = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div2",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk2_div2_en.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_vcwk2_div4 = {
	.muwt = 1,
	.div = 4,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div4",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk2_div4_en.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_vcwk2_div6 = {
	.muwt = 1,
	.div = 6,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div6",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk2_div6_en.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow s4_vcwk2_div12 = {
	.muwt = 1,
	.div = 12,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div12",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vcwk2_div12_en.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* The 5,6,7 indexes cowwesponds to no weaw cwock, so thewe awe not used. */
static u32 mux_tabwe_cts_sew[] = { 0, 1, 2, 3, 4, 8, 9, 10, 11, 12 };
static const stwuct cwk_hw *s4_cts_pawent_hws[] = {
	&s4_vcwk_div1.hw,
	&s4_vcwk_div2.hw,
	&s4_vcwk_div4.hw,
	&s4_vcwk_div6.hw,
	&s4_vcwk_div12.hw,
	&s4_vcwk2_div1.hw,
	&s4_vcwk2_div2.hw,
	&s4_vcwk2_div4.hw,
	&s4_vcwk2_div6.hw,
	&s4_vcwk2_div12.hw
};

static stwuct cwk_wegmap s4_cts_enci_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VID_CWK_DIV,
		.mask = 0xf,
		.shift = 28,
		.tabwe = mux_tabwe_cts_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_enci_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = s4_cts_pawent_hws,
		.num_pawents = AWWAY_SIZE(s4_cts_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_cts_encp_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VID_CWK_DIV,
		.mask = 0xf,
		.shift = 20,
		.tabwe = mux_tabwe_cts_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_encp_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = s4_cts_pawent_hws,
		.num_pawents = AWWAY_SIZE(s4_cts_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_cts_vdac_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VIID_CWK_DIV,
		.mask = 0xf,
		.shift = 28,
		.tabwe = mux_tabwe_cts_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_vdac_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = s4_cts_pawent_hws,
		.num_pawents = AWWAY_SIZE(s4_cts_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* The 5,6,7 indexes cowwesponds to no weaw cwock, so thewe awe not used. */
static u32 mux_tabwe_hdmi_tx_sew[] = { 0, 1, 2, 3, 4, 8, 9, 10, 11, 12 };
static const stwuct cwk_hw *s4_cts_hdmi_tx_pawent_hws[] = {
	&s4_vcwk_div1.hw,
	&s4_vcwk_div2.hw,
	&s4_vcwk_div4.hw,
	&s4_vcwk_div6.hw,
	&s4_vcwk_div12.hw,
	&s4_vcwk2_div1.hw,
	&s4_vcwk2_div2.hw,
	&s4_vcwk2_div4.hw,
	&s4_vcwk2_div6.hw,
	&s4_vcwk2_div12.hw
};

static stwuct cwk_wegmap s4_hdmi_tx_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_HDMI_CWK_CTWW,
		.mask = 0xf,
		.shift = 16,
		.tabwe = mux_tabwe_hdmi_tx_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_tx_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = s4_cts_hdmi_tx_pawent_hws,
		.num_pawents = AWWAY_SIZE(s4_cts_hdmi_tx_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_cts_enci = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW2,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cts_enci",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_cts_enci_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_cts_encp = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW2,
		.bit_idx = 2,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cts_encp",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_cts_encp_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_cts_vdac = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW2,
		.bit_idx = 4,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cts_vdac",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_cts_vdac_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdmi_tx = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VID_CWK_CTWW2,
		.bit_idx = 5,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hdmi_tx",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hdmi_tx_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* HDMI Cwocks */
static const stwuct cwk_pawent_data s4_hdmi_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", }
};

static stwuct cwk_wegmap s4_hdmi_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_HDMI_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_hdmi_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_hdmi_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdmi_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_HDMI_CWK_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_hdmi_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdmi = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_HDMI_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hdmi",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_hdmi_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_ts_cwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_TS_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ts_cwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_ts_cwk_gate = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_TS_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ts_cwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_ts_cwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/*
 * The MAWI IP is cwocked by two identicaw cwocks (mawi_0 and mawi_1)
 * muxed by a gwitch-fwee switch. The CCF can manage this gwitch-fwee
 * mux because it does top-to-bottom updates the each cwock twee and
 * switches to the "inactive" one when CWK_SET_WATE_GATE is set.
 */
static const stwuct cwk_pawent_data s4_mawi_0_1_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .fw_name = "gp0_pww", },
	{ .fw_name = "hifi_pww", },
	{ .fw_name = "fcwk_div2p5", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", }
};

static stwuct cwk_wegmap s4_mawi_0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_MAWI_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_mawi_0_1_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_mawi_0_1_pawent_data),
		/*
		 * Don't wequest the pawent to change the wate because
		 * aww GPU fwequencies can be dewived fwom the fcwk_*
		 * cwocks and one speciaw GP0_PWW setting. This is
		 * impowtant because we need the HIFI PWW cwock fow audio.
		 */
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_mawi_0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_MAWI_CWK_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_mawi_0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_mawi_0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_MAWI_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_mawi_0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_GATE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_mawi_1_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_MAWI_CWK_CTWW,
		.mask = 0x7,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_1_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_mawi_0_1_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_mawi_0_1_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_mawi_1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_MAWI_CWK_CTWW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_mawi_1_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_mawi_1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_MAWI_CWK_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_mawi_1_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_GATE | CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_hw *s4_mawi_pawent_hws[] = {
	&s4_mawi_0.hw,
	&s4_mawi_1.hw
};

static stwuct cwk_wegmap s4_mawi_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_MAWI_CWK_CTWW,
		.mask = 1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = s4_mawi_pawent_hws,
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* VDEC cwocks */
static const stwuct cwk_pawent_data s4_dec_pawent_data[] = {
	{ .fw_name = "fcwk_div2p5", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
	{ .fw_name = "hifi_pww", },
	{ .fw_name = "gp0_pww", },
	{ .fw_name = "xtaw", }
};

static stwuct cwk_wegmap s4_vdec_p0_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VDEC_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdec_p0_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_dec_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_dec_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vdec_p0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VDEC_CWK_CTWW,
		.shift = 0,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdec_p0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vdec_p0_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vdec_p0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VDEC_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vdec_p0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vdec_p0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vdec_p1_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VDEC3_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdec_p1_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_dec_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_dec_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vdec_p1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VDEC3_CWK_CTWW,
		.shift = 0,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdec_p1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vdec_p1_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vdec_p1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VDEC3_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vdec_p1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vdec_p1_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_hw *s4_vdec_mux_pawent_hws[] = {
	&s4_vdec_p0.hw,
	&s4_vdec_p1.hw
};

static stwuct cwk_wegmap s4_vdec_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VDEC3_CWK_CTWW,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdec_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = s4_vdec_mux_pawent_hws,
		.num_pawents = AWWAY_SIZE(s4_vdec_mux_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hevcf_p0_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VDEC2_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hevcf_p0_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_dec_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_dec_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_hevcf_p0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VDEC2_CWK_CTWW,
		.shift = 0,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hevcf_p0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hevcf_p0_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hevcf_p0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VDEC2_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hevcf_p0_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hevcf_p0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hevcf_p1_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VDEC4_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hevcf_p1_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_dec_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_dec_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_hevcf_p1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VDEC4_CWK_CTWW,
		.shift = 0,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hevcf_p1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hevcf_p1_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hevcf_p1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VDEC4_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hevcf_p1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hevcf_p1_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_hw *s4_hevcf_mux_pawent_hws[] = {
	&s4_hevcf_p0.hw,
	&s4_hevcf_p1.hw
};

static stwuct cwk_wegmap s4_hevcf_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VDEC4_CWK_CTWW,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hevcf",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = s4_hevcf_mux_pawent_hws,
		.num_pawents = AWWAY_SIZE(s4_hevcf_mux_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* VPU Cwock */
static const stwuct cwk_pawent_data s4_vpu_pawent_data[] = {
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
	{ .fw_name = "mpww1", },
	{ .hw = &s4_vid_pww.hw },
	{ .fw_name = "hifi_pww", },
	{ .fw_name = "gp0_pww", },
};

static stwuct cwk_wegmap s4_vpu_0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VPU_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vpu_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vpu_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vpu_0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VPU_CWK_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vpu_0_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VPU_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vpu_0_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_1_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VPU_CWK_CTWW,
		.mask = 0x7,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_1_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vpu_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vpu_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vpu_1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VPU_CWK_CTWW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vpu_1_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VPU_CWK_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vpu_1_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VPU_CWK_CTWW,
		.mask = 1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_0.hw,
			&s4_vpu_1.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data vpu_cwkb_tmp_pawent_data[] = {
	{ .hw = &s4_vpu.hw },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", }
};

static stwuct cwk_wegmap s4_vpu_cwkb_tmp_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VPU_CWKB_CTWW,
		.mask = 0x3,
		.shift = 20,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_cwkb_tmp_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = vpu_cwkb_tmp_pawent_data,
		.num_pawents = AWWAY_SIZE(vpu_cwkb_tmp_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkb_tmp_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VPU_CWKB_CTWW,
		.shift = 16,
		.width = 4,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_cwkb_tmp_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_cwkb_tmp_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkb_tmp = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VPU_CWKB_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_cwkb_tmp",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_cwkb_tmp_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkb_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VPU_CWKB_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_cwkb_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_cwkb_tmp.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkb = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VPU_CWKB_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_cwkb",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_cwkb_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data s4_vpu_cwkc_pawent_data[] = {
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
	{ .fw_name = "mpww1", },
	{ .hw = &s4_vid_pww.hw },
	{ .fw_name = "mpww2", },
	{ .fw_name = "gp0_pww", },
};

static stwuct cwk_wegmap s4_vpu_cwkc_p0_mux  = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VPU_CWKC_CTWW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_cwkc_p0_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vpu_cwkc_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vpu_cwkc_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkc_p0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VPU_CWKC_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_cwkc_p0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_cwkc_p0_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkc_p0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VPU_CWKC_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_cwkc_p0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_cwkc_p0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkc_p1_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VPU_CWKC_CTWW,
		.mask = 0x7,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_cwkc_p1_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vpu_cwkc_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vpu_cwkc_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkc_p1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VPU_CWKC_CTWW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_cwkc_p1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_cwkc_p1_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vpu_cwkc_p1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VPU_CWKC_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_cwkc_p1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vpu_cwkc_p1_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_hw *s4_vpu_mux_pawent_hws[] = {
	&s4_vpu_cwkc_p0.hw,
	&s4_vpu_cwkc_p1.hw
};

static stwuct cwk_wegmap s4_vpu_cwkc_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VPU_CWKC_CTWW,
		.mask = 0x1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_cwkc_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = s4_vpu_mux_pawent_hws,
		.num_pawents = AWWAY_SIZE(s4_vpu_mux_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* VAPB Cwock */
static const stwuct cwk_pawent_data s4_vapb_pawent_data[] = {
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
	{ .fw_name = "mpww1", },
	{ .hw = &s4_vid_pww.hw },
	{ .fw_name = "mpww2", },
	{ .fw_name = "fcwk_div2p5", },
};

static stwuct cwk_wegmap s4_vapb_0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VAPBCWK_CTWW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vapb_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vapb_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vapb_0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VAPBCWK_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vapb_0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vapb_0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VAPBCWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vapb_0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vapb_0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vapb_1_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VAPBCWK_CTWW,
		.mask = 0x7,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_1_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vapb_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vapb_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_vapb_1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VAPBCWK_CTWW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vapb_1_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vapb_1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VAPBCWK_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vapb_1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vapb_1_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vapb = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VAPBCWK_CTWW,
		.mask = 1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vapb_0.hw,
			&s4_vapb_1.hw
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_ge2d_gate = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VAPBCWK_CTWW,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "ge2d_cwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &s4_vapb.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data s4_esmcwk_pawent_data[] = {
	{ .fw_name = "fcwk_div7", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
};

static stwuct cwk_wegmap s4_hdcp22_esmcwk_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_HDCP22_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hdcp22_esmcwk_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_esmcwk_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_esmcwk_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdcp22_esmcwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_HDCP22_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hdcp22_esmcwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hdcp22_esmcwk_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdcp22_esmcwk_gate = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_HDCP22_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdcp22_esmcwk_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hdcp22_esmcwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data s4_skpcwk_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
};

static stwuct cwk_wegmap s4_hdcp22_skpcwk_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_HDCP22_CTWW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hdcp22_skpcwk_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_skpcwk_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_skpcwk_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdcp22_skpcwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_HDCP22_CTWW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hdcp22_skpcwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hdcp22_skpcwk_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_hdcp22_skpcwk_gate = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_HDCP22_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdcp22_skpcwk_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_hdcp22_skpcwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data s4_vdin_pawent_data[]  = {
	{ .fw_name = "xtaw", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
	{ .hw = &s4_vid_pww.hw }
};

static stwuct cwk_wegmap s4_vdin_meas_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_VDIN_MEAS_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdin_meas_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_vdin_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_vdin_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vdin_meas_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_VDIN_MEAS_CWK_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdin_meas_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vdin_meas_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_vdin_meas_gate = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_VDIN_MEAS_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vdin_meas_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_vdin_meas_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* EMMC/NAND cwock */
static const stwuct cwk_pawent_data s4_sd_emmc_cwk0_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .fw_name = "fcwk_div2", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "hifi_pww", },
	{ .fw_name = "fcwk_div2p5", },
	{ .fw_name = "mpww2", },
	{ .fw_name = "mpww3", },
	{ .fw_name = "gp0_pww", },
};

static stwuct cwk_wegmap s4_sd_emmc_c_cwk0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_NAND_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_c_cwk0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_sd_emmc_cwk0_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_sd_emmc_cwk0_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_sd_emmc_c_cwk0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_NAND_CWK_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_c_cwk0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sd_emmc_c_cwk0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sd_emmc_c_cwk0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_NAND_CWK_CTWW,
		.bit_idx = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_c_cwk0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sd_emmc_c_cwk0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sd_emmc_a_cwk0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_SD_EMMC_CWK_CTWW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_a_cwk0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_sd_emmc_cwk0_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_sd_emmc_cwk0_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_sd_emmc_a_cwk0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_SD_EMMC_CWK_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_a_cwk0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sd_emmc_a_cwk0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sd_emmc_a_cwk0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_SD_EMMC_CWK_CTWW,
		.bit_idx = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_a_cwk0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sd_emmc_a_cwk0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sd_emmc_b_cwk0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_SD_EMMC_CWK_CTWW,
		.mask = 0x7,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_b_cwk0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_sd_emmc_cwk0_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_sd_emmc_cwk0_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_sd_emmc_b_cwk0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_SD_EMMC_CWK_CTWW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_b_cwk0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sd_emmc_b_cwk0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sd_emmc_b_cwk0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_SD_EMMC_CWK_CTWW,
		.bit_idx = 23,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_b_cwk0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sd_emmc_b_cwk0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* SPICC Cwock */
static const stwuct cwk_pawent_data s4_spicc_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &s4_sys_cwk.hw },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div2", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
};

static stwuct cwk_wegmap s4_spicc0_mux = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_SPICC_CWK_CTWW,
		.mask = 0x7,
		.shift = 7,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "spicc0_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_spicc_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_spicc_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_spicc0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_SPICC_CWK_CTWW,
		.shift = 0,
		.width = 6,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "spicc0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_spicc0_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_spicc0_gate = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_SPICC_CWK_CTWW,
		.bit_idx = 6,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "spicc0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_spicc0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* PWM Cwock */
static const stwuct cwk_pawent_data s4_pwm_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &s4_vid_pww.hw },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
};

static stwuct cwk_wegmap s4_pwm_a_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_AB_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_a_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_a_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_AB_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_a_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_a_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_a_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_AB_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_a_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_a_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_b_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_AB_CTWW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_b_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_b_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_AB_CTWW,
		.shift = 16,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_b_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_b_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_b_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_AB_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_b_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_b_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_c_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_CD_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_c_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_c_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_CD_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_c_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_c_mux.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap s4_pwm_c_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_CD_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_c_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_c_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_d_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_CD_CTWW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_d_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_d_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_CD_CTWW,
		.shift = 16,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_d_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_d_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_d_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_CD_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_d_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_d_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_e_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_EF_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_e_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_e_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_EF_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_e_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_e_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_e_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_EF_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_e_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_e_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_f_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_EF_CTWW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_f_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_f_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_EF_CTWW,
		.shift = 16,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_f_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_f_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_f_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_EF_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_f_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_f_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_g_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_GH_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_g_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_g_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_GH_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_g_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_g_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_g_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_GH_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_g_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_g_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_h_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_GH_CTWW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_h_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_h_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_GH_CTWW,
		.shift = 16,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_h_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_h_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_h_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_GH_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_h_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_h_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_i_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_IJ_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_i_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_i_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_IJ_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_i_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_i_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_i_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_IJ_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_i_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_i_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_j_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_PWM_CWK_IJ_CTWW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_j_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_pwm_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_pwm_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_pwm_j_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_PWM_CWK_IJ_CTWW,
		.shift = 16,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_j_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_h_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_pwm_j_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_PWM_CWK_IJ_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_j_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_pwm_j_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sawadc_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_SAW_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sawadc_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", },
			{ .hw = &s4_sys_cwk.hw },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sawadc_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_SAW_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sawadc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sawadc_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_sawadc_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_SAW_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sawadc_cwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_sawadc_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/*
 * gen cwk is designed fow debug/monitow some intewnaw cwock quawity. Some of the
 * cowwesponding cwock souwces awe not descwibed in the cwock twee and intewnaw cwock
 * fow debug, so they awe skipped.
 */
static u32 s4_gen_cwk_mux_tabwe[] = { 0, 4, 5, 7, 19, 21, 22,
				      23, 24, 25, 26, 27, 28 };
static const stwuct cwk_pawent_data s4_gen_cwk_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &s4_vid_pww.hw },
	{ .fw_name = "gp0_pww", },
	{ .fw_name = "hifi_pww", },
	{ .fw_name = "fcwk_div2", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
	{ .fw_name = "mpww0", },
	{ .fw_name = "mpww1", },
	{ .fw_name = "mpww2", },
	{ .fw_name = "mpww3", },
};

static stwuct cwk_wegmap s4_gen_cwk_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = CWKCTWW_GEN_CWK_CTWW,
		.mask = 0x1f,
		.shift = 12,
		.tabwe = s4_gen_cwk_mux_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gen_cwk_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_gen_cwk_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_gen_cwk_pawent_data),
		/*
		 *  Because the GEN cwock can be connected to an extewnaw pad
		 *  and may be set up diwectwy fwom the device twee. Don't
		 *  weawwy want to automaticawwy wepawent.
		 */
		.fwags = CWK_SET_WATE_NO_WEPAWENT,
	},
};

static stwuct cwk_wegmap s4_gen_cwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWKCTWW_GEN_CWK_CTWW,
		.shift = 0,
		.width = 11,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gen_cwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_gen_cwk_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_gen_cwk = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWKCTWW_GEN_CWK_CTWW,
		.bit_idx = 11,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gen_cwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_gen_cwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data s4_adc_extcwk_in_pawent_data[]  = {
	{ .fw_name = "xtaw", },
	{ .fw_name = "fcwk_div4", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
	{ .fw_name = "mpww2", },
	{ .fw_name = "gp0_pww", },
	{ .fw_name = "hifi_pww", },
};

static stwuct cwk_wegmap s4_adc_extcwk_in_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_DEMOD_CWK_CTWW,
		.mask = 0x7,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "adc_extcwk_in_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = s4_adc_extcwk_in_pawent_data,
		.num_pawents = AWWAY_SIZE(s4_adc_extcwk_in_pawent_data),
		.fwags = 0,
	},
};

static stwuct cwk_wegmap s4_adc_extcwk_in_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_DEMOD_CWK_CTWW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "adc_extcwk_in_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_adc_extcwk_in_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_adc_extcwk_in_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_DEMOD_CWK_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "adc_extcwk_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_adc_extcwk_in_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_demod_cowe_cwk_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CWKCTWW_DEMOD_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "demod_cowe_cwk_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", },
			{ .fw_name = "fcwk_div7", },
			{ .fw_name = "fcwk_div4", },
			{ .hw = &s4_adc_extcwk_in_gate.hw }
		},
		.num_pawents = 4,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_demod_cowe_cwk_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = CWKCTWW_DEMOD_CWK_CTWW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "demod_cowe_cwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_demod_cowe_cwk_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap s4_demod_cowe_cwk_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = CWKCTWW_DEMOD_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "demod_cowe_cwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&s4_demod_cowe_cwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

#define MESON_GATE(_name, _weg, _bit) \
	MESON_PCWK(_name, _weg, _bit, &s4_sys_cwk.hw)

static MESON_GATE(s4_ddw,		CWKCTWW_SYS_CWK_EN0_WEG0, 0);
static MESON_GATE(s4_dos,		CWKCTWW_SYS_CWK_EN0_WEG0, 1);
static MESON_GATE(s4_ethphy,		CWKCTWW_SYS_CWK_EN0_WEG0, 4);
static MESON_GATE(s4_mawi,		CWKCTWW_SYS_CWK_EN0_WEG0, 6);
static MESON_GATE(s4_aocpu,		CWKCTWW_SYS_CWK_EN0_WEG0, 13);
static MESON_GATE(s4_aucpu,		CWKCTWW_SYS_CWK_EN0_WEG0, 14);
static MESON_GATE(s4_cec,		CWKCTWW_SYS_CWK_EN0_WEG0, 16);
static MESON_GATE(s4_sdemmca,		CWKCTWW_SYS_CWK_EN0_WEG0, 24);
static MESON_GATE(s4_sdemmcb,		CWKCTWW_SYS_CWK_EN0_WEG0, 25);
static MESON_GATE(s4_nand,		CWKCTWW_SYS_CWK_EN0_WEG0, 26);
static MESON_GATE(s4_smawtcawd,		CWKCTWW_SYS_CWK_EN0_WEG0, 27);
static MESON_GATE(s4_acodec,		CWKCTWW_SYS_CWK_EN0_WEG0, 28);
static MESON_GATE(s4_spifc,		CWKCTWW_SYS_CWK_EN0_WEG0, 29);
static MESON_GATE(s4_msw_cwk,		CWKCTWW_SYS_CWK_EN0_WEG0, 30);
static MESON_GATE(s4_iw_ctww,		CWKCTWW_SYS_CWK_EN0_WEG0, 31);
static MESON_GATE(s4_audio,		CWKCTWW_SYS_CWK_EN0_WEG1, 0);
static MESON_GATE(s4_eth,		CWKCTWW_SYS_CWK_EN0_WEG1, 3);
static MESON_GATE(s4_uawt_a,		CWKCTWW_SYS_CWK_EN0_WEG1, 5);
static MESON_GATE(s4_uawt_b,		CWKCTWW_SYS_CWK_EN0_WEG1, 6);
static MESON_GATE(s4_uawt_c,		CWKCTWW_SYS_CWK_EN0_WEG1, 7);
static MESON_GATE(s4_uawt_d,		CWKCTWW_SYS_CWK_EN0_WEG1, 8);
static MESON_GATE(s4_uawt_e,		CWKCTWW_SYS_CWK_EN0_WEG1, 9);
static MESON_GATE(s4_aififo,		CWKCTWW_SYS_CWK_EN0_WEG1, 11);
static MESON_GATE(s4_ts_ddw,		CWKCTWW_SYS_CWK_EN0_WEG1, 15);
static MESON_GATE(s4_ts_pww,		CWKCTWW_SYS_CWK_EN0_WEG1, 16);
static MESON_GATE(s4_g2d,		CWKCTWW_SYS_CWK_EN0_WEG1, 20);
static MESON_GATE(s4_spicc0,		CWKCTWW_SYS_CWK_EN0_WEG1, 21);
static MESON_GATE(s4_usb,		CWKCTWW_SYS_CWK_EN0_WEG1, 26);
static MESON_GATE(s4_i2c_m_a,		CWKCTWW_SYS_CWK_EN0_WEG1, 30);
static MESON_GATE(s4_i2c_m_b,		CWKCTWW_SYS_CWK_EN0_WEG1, 31);
static MESON_GATE(s4_i2c_m_c,		CWKCTWW_SYS_CWK_EN0_WEG2, 0);
static MESON_GATE(s4_i2c_m_d,		CWKCTWW_SYS_CWK_EN0_WEG2, 1);
static MESON_GATE(s4_i2c_m_e,		CWKCTWW_SYS_CWK_EN0_WEG2, 2);
static MESON_GATE(s4_hdmitx_apb,	CWKCTWW_SYS_CWK_EN0_WEG2, 4);
static MESON_GATE(s4_i2c_s_a,		CWKCTWW_SYS_CWK_EN0_WEG2, 5);
static MESON_GATE(s4_usb1_to_ddw,	CWKCTWW_SYS_CWK_EN0_WEG2, 8);
static MESON_GATE(s4_hdcp22,		CWKCTWW_SYS_CWK_EN0_WEG2, 10);
static MESON_GATE(s4_mmc_apb,		CWKCTWW_SYS_CWK_EN0_WEG2, 11);
static MESON_GATE(s4_wsa,		CWKCTWW_SYS_CWK_EN0_WEG2, 18);
static MESON_GATE(s4_cpu_debug,		CWKCTWW_SYS_CWK_EN0_WEG2, 19);
static MESON_GATE(s4_vpu_intw,		CWKCTWW_SYS_CWK_EN0_WEG2, 25);
static MESON_GATE(s4_demod,		CWKCTWW_SYS_CWK_EN0_WEG2, 27);
static MESON_GATE(s4_saw_adc,		CWKCTWW_SYS_CWK_EN0_WEG2, 28);
static MESON_GATE(s4_gic,		CWKCTWW_SYS_CWK_EN0_WEG2, 30);
static MESON_GATE(s4_pwm_ab,		CWKCTWW_SYS_CWK_EN0_WEG3, 7);
static MESON_GATE(s4_pwm_cd,		CWKCTWW_SYS_CWK_EN0_WEG3, 8);
static MESON_GATE(s4_pwm_ef,		CWKCTWW_SYS_CWK_EN0_WEG3, 9);
static MESON_GATE(s4_pwm_gh,		CWKCTWW_SYS_CWK_EN0_WEG3, 10);
static MESON_GATE(s4_pwm_ij,		CWKCTWW_SYS_CWK_EN0_WEG3, 11);

/* Awway of aww cwocks pwovided by this pwovidew */
static stwuct cwk_hw *s4_pewiphs_hw_cwks[] = {
	[CWKID_WTC_32K_CWKIN]		= &s4_wtc_32k_by_oscin_cwkin.hw,
	[CWKID_WTC_32K_DIV]		= &s4_wtc_32k_by_oscin_div.hw,
	[CWKID_WTC_32K_SEW]		= &s4_wtc_32k_by_oscin_sew.hw,
	[CWKID_WTC_32K_XATW]		= &s4_wtc_32k_by_oscin.hw,
	[CWKID_WTC]			= &s4_wtc_cwk.hw,
	[CWKID_SYS_CWK_B_SEW]		= &s4_syscwk_b_sew.hw,
	[CWKID_SYS_CWK_B_DIV]		= &s4_syscwk_b_div.hw,
	[CWKID_SYS_CWK_B]		= &s4_syscwk_b.hw,
	[CWKID_SYS_CWK_A_SEW]		= &s4_syscwk_a_sew.hw,
	[CWKID_SYS_CWK_A_DIV]		= &s4_syscwk_a_div.hw,
	[CWKID_SYS_CWK_A]		= &s4_syscwk_a.hw,
	[CWKID_SYS]			= &s4_sys_cwk.hw,
	[CWKID_CECA_32K_CWKIN]		= &s4_ceca_32k_cwkin.hw,
	[CWKID_CECA_32K_DIV]		= &s4_ceca_32k_div.hw,
	[CWKID_CECA_32K_SEW_PWE]	= &s4_ceca_32k_sew_pwe.hw,
	[CWKID_CECA_32K_SEW]		= &s4_ceca_32k_sew.hw,
	[CWKID_CECA_32K_CWKOUT]		= &s4_ceca_32k_cwkout.hw,
	[CWKID_CECB_32K_CWKIN]		= &s4_cecb_32k_cwkin.hw,
	[CWKID_CECB_32K_DIV]		= &s4_cecb_32k_div.hw,
	[CWKID_CECB_32K_SEW_PWE]	= &s4_cecb_32k_sew_pwe.hw,
	[CWKID_CECB_32K_SEW]		= &s4_cecb_32k_sew.hw,
	[CWKID_CECB_32K_CWKOUT]		= &s4_cecb_32k_cwkout.hw,
	[CWKID_SC_CWK_SEW]		= &s4_sc_cwk_mux.hw,
	[CWKID_SC_CWK_DIV]		= &s4_sc_cwk_div.hw,
	[CWKID_SC]			= &s4_sc_cwk_gate.hw,
	[CWKID_12_24M]			= &s4_12_24M_cwk_gate.hw,
	[CWKID_12M_CWK_DIV]		= &s4_12M_cwk_div.hw,
	[CWKID_12_24M_CWK_SEW]		= &s4_12_24M_cwk.hw,
	[CWKID_VID_PWW_DIV]		= &s4_vid_pww_div.hw,
	[CWKID_VID_PWW_SEW]		= &s4_vid_pww_sew.hw,
	[CWKID_VID_PWW]			= &s4_vid_pww.hw,
	[CWKID_VCWK_SEW]		= &s4_vcwk_sew.hw,
	[CWKID_VCWK2_SEW]		= &s4_vcwk2_sew.hw,
	[CWKID_VCWK_INPUT]		= &s4_vcwk_input.hw,
	[CWKID_VCWK2_INPUT]		= &s4_vcwk2_input.hw,
	[CWKID_VCWK_DIV]		= &s4_vcwk_div.hw,
	[CWKID_VCWK2_DIV]		= &s4_vcwk2_div.hw,
	[CWKID_VCWK]			= &s4_vcwk.hw,
	[CWKID_VCWK2]			= &s4_vcwk2.hw,
	[CWKID_VCWK_DIV1]		= &s4_vcwk_div1.hw,
	[CWKID_VCWK_DIV2_EN]		= &s4_vcwk_div2_en.hw,
	[CWKID_VCWK_DIV4_EN]		= &s4_vcwk_div4_en.hw,
	[CWKID_VCWK_DIV6_EN]		= &s4_vcwk_div6_en.hw,
	[CWKID_VCWK_DIV12_EN]		= &s4_vcwk_div12_en.hw,
	[CWKID_VCWK2_DIV1]		= &s4_vcwk2_div1.hw,
	[CWKID_VCWK2_DIV2_EN]		= &s4_vcwk2_div2_en.hw,
	[CWKID_VCWK2_DIV4_EN]		= &s4_vcwk2_div4_en.hw,
	[CWKID_VCWK2_DIV6_EN]		= &s4_vcwk2_div6_en.hw,
	[CWKID_VCWK2_DIV12_EN]		= &s4_vcwk2_div12_en.hw,
	[CWKID_VCWK_DIV2]		= &s4_vcwk_div2.hw,
	[CWKID_VCWK_DIV4]		= &s4_vcwk_div4.hw,
	[CWKID_VCWK_DIV6]		= &s4_vcwk_div6.hw,
	[CWKID_VCWK_DIV12]		= &s4_vcwk_div12.hw,
	[CWKID_VCWK2_DIV2]		= &s4_vcwk2_div2.hw,
	[CWKID_VCWK2_DIV4]		= &s4_vcwk2_div4.hw,
	[CWKID_VCWK2_DIV6]		= &s4_vcwk2_div6.hw,
	[CWKID_VCWK2_DIV12]		= &s4_vcwk2_div12.hw,
	[CWKID_CTS_ENCI_SEW]		= &s4_cts_enci_sew.hw,
	[CWKID_CTS_ENCP_SEW]		= &s4_cts_encp_sew.hw,
	[CWKID_CTS_VDAC_SEW]		= &s4_cts_vdac_sew.hw,
	[CWKID_HDMI_TX_SEW]		= &s4_hdmi_tx_sew.hw,
	[CWKID_CTS_ENCI]		= &s4_cts_enci.hw,
	[CWKID_CTS_ENCP]		= &s4_cts_encp.hw,
	[CWKID_CTS_VDAC]		= &s4_cts_vdac.hw,
	[CWKID_HDMI_TX]			= &s4_hdmi_tx.hw,
	[CWKID_HDMI_SEW]		= &s4_hdmi_sew.hw,
	[CWKID_HDMI_DIV]		= &s4_hdmi_div.hw,
	[CWKID_HDMI]			= &s4_hdmi.hw,
	[CWKID_TS_CWK_DIV]		= &s4_ts_cwk_div.hw,
	[CWKID_TS]			= &s4_ts_cwk_gate.hw,
	[CWKID_MAWI_0_SEW]		= &s4_mawi_0_sew.hw,
	[CWKID_MAWI_0_DIV]		= &s4_mawi_0_div.hw,
	[CWKID_MAWI_0]			= &s4_mawi_0.hw,
	[CWKID_MAWI_1_SEW]		= &s4_mawi_1_sew.hw,
	[CWKID_MAWI_1_DIV]		= &s4_mawi_1_div.hw,
	[CWKID_MAWI_1]			= &s4_mawi_1.hw,
	[CWKID_MAWI_SEW]		= &s4_mawi_mux.hw,
	[CWKID_VDEC_P0_SEW]		= &s4_vdec_p0_mux.hw,
	[CWKID_VDEC_P0_DIV]		= &s4_vdec_p0_div.hw,
	[CWKID_VDEC_P0]			= &s4_vdec_p0.hw,
	[CWKID_VDEC_P1_SEW]		= &s4_vdec_p1_mux.hw,
	[CWKID_VDEC_P1_DIV]		= &s4_vdec_p1_div.hw,
	[CWKID_VDEC_P1]			= &s4_vdec_p1.hw,
	[CWKID_VDEC_SEW]		= &s4_vdec_mux.hw,
	[CWKID_HEVCF_P0_SEW]		= &s4_hevcf_p0_mux.hw,
	[CWKID_HEVCF_P0_DIV]		= &s4_hevcf_p0_div.hw,
	[CWKID_HEVCF_P0]		= &s4_hevcf_p0.hw,
	[CWKID_HEVCF_P1_SEW]		= &s4_hevcf_p1_mux.hw,
	[CWKID_HEVCF_P1_DIV]		= &s4_hevcf_p1_div.hw,
	[CWKID_HEVCF_P1]		= &s4_hevcf_p1.hw,
	[CWKID_HEVCF_SEW]		= &s4_hevcf_mux.hw,
	[CWKID_VPU_0_SEW]		= &s4_vpu_0_sew.hw,
	[CWKID_VPU_0_DIV]		= &s4_vpu_0_div.hw,
	[CWKID_VPU_0]			= &s4_vpu_0.hw,
	[CWKID_VPU_1_SEW]		= &s4_vpu_1_sew.hw,
	[CWKID_VPU_1_DIV]		= &s4_vpu_1_div.hw,
	[CWKID_VPU_1]			= &s4_vpu_1.hw,
	[CWKID_VPU]			= &s4_vpu.hw,
	[CWKID_VPU_CWKB_TMP_SEW]	= &s4_vpu_cwkb_tmp_mux.hw,
	[CWKID_VPU_CWKB_TMP_DIV]	= &s4_vpu_cwkb_tmp_div.hw,
	[CWKID_VPU_CWKB_TMP]		= &s4_vpu_cwkb_tmp.hw,
	[CWKID_VPU_CWKB_DIV]		= &s4_vpu_cwkb_div.hw,
	[CWKID_VPU_CWKB]		= &s4_vpu_cwkb.hw,
	[CWKID_VPU_CWKC_P0_SEW]		= &s4_vpu_cwkc_p0_mux.hw,
	[CWKID_VPU_CWKC_P0_DIV]		= &s4_vpu_cwkc_p0_div.hw,
	[CWKID_VPU_CWKC_P0]		= &s4_vpu_cwkc_p0.hw,
	[CWKID_VPU_CWKC_P1_SEW]		= &s4_vpu_cwkc_p1_mux.hw,
	[CWKID_VPU_CWKC_P1_DIV]		= &s4_vpu_cwkc_p1_div.hw,
	[CWKID_VPU_CWKC_P1]		= &s4_vpu_cwkc_p1.hw,
	[CWKID_VPU_CWKC_SEW]		= &s4_vpu_cwkc_mux.hw,
	[CWKID_VAPB_0_SEW]		= &s4_vapb_0_sew.hw,
	[CWKID_VAPB_0_DIV]		= &s4_vapb_0_div.hw,
	[CWKID_VAPB_0]			= &s4_vapb_0.hw,
	[CWKID_VAPB_1_SEW]		= &s4_vapb_1_sew.hw,
	[CWKID_VAPB_1_DIV]		= &s4_vapb_1_div.hw,
	[CWKID_VAPB_1]			= &s4_vapb_1.hw,
	[CWKID_VAPB]			= &s4_vapb.hw,
	[CWKID_GE2D]			= &s4_ge2d_gate.hw,
	[CWKID_VDIN_MEAS_SEW]		= &s4_vdin_meas_mux.hw,
	[CWKID_VDIN_MEAS_DIV]		= &s4_vdin_meas_div.hw,
	[CWKID_VDIN_MEAS]		= &s4_vdin_meas_gate.hw,
	[CWKID_SD_EMMC_C_CWK_SEW]	= &s4_sd_emmc_c_cwk0_sew.hw,
	[CWKID_SD_EMMC_C_CWK_DIV]	= &s4_sd_emmc_c_cwk0_div.hw,
	[CWKID_SD_EMMC_C]		= &s4_sd_emmc_c_cwk0.hw,
	[CWKID_SD_EMMC_A_CWK_SEW]	= &s4_sd_emmc_a_cwk0_sew.hw,
	[CWKID_SD_EMMC_A_CWK_DIV]	= &s4_sd_emmc_a_cwk0_div.hw,
	[CWKID_SD_EMMC_A]		= &s4_sd_emmc_a_cwk0.hw,
	[CWKID_SD_EMMC_B_CWK_SEW]	= &s4_sd_emmc_b_cwk0_sew.hw,
	[CWKID_SD_EMMC_B_CWK_DIV]	= &s4_sd_emmc_b_cwk0_div.hw,
	[CWKID_SD_EMMC_B]		= &s4_sd_emmc_b_cwk0.hw,
	[CWKID_SPICC0_SEW]		= &s4_spicc0_mux.hw,
	[CWKID_SPICC0_DIV]		= &s4_spicc0_div.hw,
	[CWKID_SPICC0_EN]		= &s4_spicc0_gate.hw,
	[CWKID_PWM_A_SEW]		= &s4_pwm_a_mux.hw,
	[CWKID_PWM_A_DIV]		= &s4_pwm_a_div.hw,
	[CWKID_PWM_A]			= &s4_pwm_a_gate.hw,
	[CWKID_PWM_B_SEW]		= &s4_pwm_b_mux.hw,
	[CWKID_PWM_B_DIV]		= &s4_pwm_b_div.hw,
	[CWKID_PWM_B]			= &s4_pwm_b_gate.hw,
	[CWKID_PWM_C_SEW]		= &s4_pwm_c_mux.hw,
	[CWKID_PWM_C_DIV]		= &s4_pwm_c_div.hw,
	[CWKID_PWM_C]			= &s4_pwm_c_gate.hw,
	[CWKID_PWM_D_SEW]		= &s4_pwm_d_mux.hw,
	[CWKID_PWM_D_DIV]		= &s4_pwm_d_div.hw,
	[CWKID_PWM_D]			= &s4_pwm_d_gate.hw,
	[CWKID_PWM_E_SEW]		= &s4_pwm_e_mux.hw,
	[CWKID_PWM_E_DIV]		= &s4_pwm_e_div.hw,
	[CWKID_PWM_E]			= &s4_pwm_e_gate.hw,
	[CWKID_PWM_F_SEW]		= &s4_pwm_f_mux.hw,
	[CWKID_PWM_F_DIV]		= &s4_pwm_f_div.hw,
	[CWKID_PWM_F]			= &s4_pwm_f_gate.hw,
	[CWKID_PWM_G_SEW]		= &s4_pwm_g_mux.hw,
	[CWKID_PWM_G_DIV]		= &s4_pwm_g_div.hw,
	[CWKID_PWM_G]			= &s4_pwm_g_gate.hw,
	[CWKID_PWM_H_SEW]		= &s4_pwm_h_mux.hw,
	[CWKID_PWM_H_DIV]		= &s4_pwm_h_div.hw,
	[CWKID_PWM_H]			= &s4_pwm_h_gate.hw,
	[CWKID_PWM_I_SEW]		= &s4_pwm_i_mux.hw,
	[CWKID_PWM_I_DIV]		= &s4_pwm_i_div.hw,
	[CWKID_PWM_I]			= &s4_pwm_i_gate.hw,
	[CWKID_PWM_J_SEW]		= &s4_pwm_j_mux.hw,
	[CWKID_PWM_J_DIV]		= &s4_pwm_j_div.hw,
	[CWKID_PWM_J]			= &s4_pwm_j_gate.hw,
	[CWKID_SAWADC_SEW]		= &s4_sawadc_mux.hw,
	[CWKID_SAWADC_DIV]		= &s4_sawadc_div.hw,
	[CWKID_SAWADC]			= &s4_sawadc_gate.hw,
	[CWKID_GEN_SEW]			= &s4_gen_cwk_sew.hw,
	[CWKID_GEN_DIV]			= &s4_gen_cwk_div.hw,
	[CWKID_GEN]			= &s4_gen_cwk.hw,
	[CWKID_DDW]			= &s4_ddw.hw,
	[CWKID_DOS]			= &s4_dos.hw,
	[CWKID_ETHPHY]			= &s4_ethphy.hw,
	[CWKID_MAWI]			= &s4_mawi.hw,
	[CWKID_AOCPU]			= &s4_aocpu.hw,
	[CWKID_AUCPU]			= &s4_aucpu.hw,
	[CWKID_CEC]			= &s4_cec.hw,
	[CWKID_SDEMMC_A]		= &s4_sdemmca.hw,
	[CWKID_SDEMMC_B]		= &s4_sdemmcb.hw,
	[CWKID_NAND]			= &s4_nand.hw,
	[CWKID_SMAWTCAWD]		= &s4_smawtcawd.hw,
	[CWKID_ACODEC]			= &s4_acodec.hw,
	[CWKID_SPIFC]			= &s4_spifc.hw,
	[CWKID_MSW]			= &s4_msw_cwk.hw,
	[CWKID_IW_CTWW]			= &s4_iw_ctww.hw,
	[CWKID_AUDIO]			= &s4_audio.hw,
	[CWKID_ETH]			= &s4_eth.hw,
	[CWKID_UAWT_A]			= &s4_uawt_a.hw,
	[CWKID_UAWT_B]			= &s4_uawt_b.hw,
	[CWKID_UAWT_C]			= &s4_uawt_c.hw,
	[CWKID_UAWT_D]			= &s4_uawt_d.hw,
	[CWKID_UAWT_E]			= &s4_uawt_e.hw,
	[CWKID_AIFIFO]			= &s4_aififo.hw,
	[CWKID_TS_DDW]			= &s4_ts_ddw.hw,
	[CWKID_TS_PWW]			= &s4_ts_pww.hw,
	[CWKID_G2D]			= &s4_g2d.hw,
	[CWKID_SPICC0]			= &s4_spicc0.hw,
	[CWKID_USB]			= &s4_usb.hw,
	[CWKID_I2C_M_A]			= &s4_i2c_m_a.hw,
	[CWKID_I2C_M_B]			= &s4_i2c_m_b.hw,
	[CWKID_I2C_M_C]			= &s4_i2c_m_c.hw,
	[CWKID_I2C_M_D]			= &s4_i2c_m_d.hw,
	[CWKID_I2C_M_E]			= &s4_i2c_m_e.hw,
	[CWKID_HDMITX_APB]		= &s4_hdmitx_apb.hw,
	[CWKID_I2C_S_A]			= &s4_i2c_s_a.hw,
	[CWKID_USB1_TO_DDW]		= &s4_usb1_to_ddw.hw,
	[CWKID_HDCP22]			= &s4_hdcp22.hw,
	[CWKID_MMC_APB]			= &s4_mmc_apb.hw,
	[CWKID_WSA]			= &s4_wsa.hw,
	[CWKID_CPU_DEBUG]		= &s4_cpu_debug.hw,
	[CWKID_VPU_INTW]		= &s4_vpu_intw.hw,
	[CWKID_DEMOD]			= &s4_demod.hw,
	[CWKID_SAW_ADC]			= &s4_saw_adc.hw,
	[CWKID_GIC]			= &s4_gic.hw,
	[CWKID_PWM_AB]			= &s4_pwm_ab.hw,
	[CWKID_PWM_CD]			= &s4_pwm_cd.hw,
	[CWKID_PWM_EF]			= &s4_pwm_ef.hw,
	[CWKID_PWM_GH]			= &s4_pwm_gh.hw,
	[CWKID_PWM_IJ]			= &s4_pwm_ij.hw,
	[CWKID_HDCP22_ESMCWK_SEW]	= &s4_hdcp22_esmcwk_mux.hw,
	[CWKID_HDCP22_ESMCWK_DIV]	= &s4_hdcp22_esmcwk_div.hw,
	[CWKID_HDCP22_ESMCWK]		= &s4_hdcp22_esmcwk_gate.hw,
	[CWKID_HDCP22_SKPCWK_SEW]	= &s4_hdcp22_skpcwk_mux.hw,
	[CWKID_HDCP22_SKPCWK_DIV]	= &s4_hdcp22_skpcwk_div.hw,
	[CWKID_HDCP22_SKPCWK]		= &s4_hdcp22_skpcwk_gate.hw,
};

/* Convenience tabwe to popuwate wegmap in .pwobe */
static stwuct cwk_wegmap *const s4_pewiphs_cwk_wegmaps[] = {
	&s4_wtc_32k_by_oscin_cwkin,
	&s4_wtc_32k_by_oscin_div,
	&s4_wtc_32k_by_oscin_sew,
	&s4_wtc_32k_by_oscin,
	&s4_wtc_cwk,
	&s4_syscwk_b_sew,
	&s4_syscwk_b_div,
	&s4_syscwk_b,
	&s4_syscwk_a_sew,
	&s4_syscwk_a_div,
	&s4_syscwk_a,
	&s4_sys_cwk,
	&s4_ceca_32k_cwkin,
	&s4_ceca_32k_div,
	&s4_ceca_32k_sew_pwe,
	&s4_ceca_32k_sew,
	&s4_ceca_32k_cwkout,
	&s4_cecb_32k_cwkin,
	&s4_cecb_32k_div,
	&s4_cecb_32k_sew_pwe,
	&s4_cecb_32k_sew,
	&s4_cecb_32k_cwkout,
	&s4_sc_cwk_mux,
	&s4_sc_cwk_div,
	&s4_sc_cwk_gate,
	&s4_12_24M_cwk_gate,
	&s4_12_24M_cwk,
	&s4_vid_pww_div,
	&s4_vid_pww_sew,
	&s4_vid_pww,
	&s4_vcwk_sew,
	&s4_vcwk2_sew,
	&s4_vcwk_input,
	&s4_vcwk2_input,
	&s4_vcwk_div,
	&s4_vcwk2_div,
	&s4_vcwk,
	&s4_vcwk2,
	&s4_vcwk_div1,
	&s4_vcwk_div2_en,
	&s4_vcwk_div4_en,
	&s4_vcwk_div6_en,
	&s4_vcwk_div12_en,
	&s4_vcwk2_div1,
	&s4_vcwk2_div2_en,
	&s4_vcwk2_div4_en,
	&s4_vcwk2_div6_en,
	&s4_vcwk2_div12_en,
	&s4_cts_enci_sew,
	&s4_cts_encp_sew,
	&s4_cts_vdac_sew,
	&s4_hdmi_tx_sew,
	&s4_cts_enci,
	&s4_cts_encp,
	&s4_cts_vdac,
	&s4_hdmi_tx,
	&s4_hdmi_sew,
	&s4_hdmi_div,
	&s4_hdmi,
	&s4_ts_cwk_div,
	&s4_ts_cwk_gate,
	&s4_mawi_0_sew,
	&s4_mawi_0_div,
	&s4_mawi_0,
	&s4_mawi_1_sew,
	&s4_mawi_1_div,
	&s4_mawi_1,
	&s4_mawi_mux,
	&s4_vdec_p0_mux,
	&s4_vdec_p0_div,
	&s4_vdec_p0,
	&s4_vdec_p1_mux,
	&s4_vdec_p1_div,
	&s4_vdec_p1,
	&s4_vdec_mux,
	&s4_hevcf_p0_mux,
	&s4_hevcf_p0_div,
	&s4_hevcf_p0,
	&s4_hevcf_p1_mux,
	&s4_hevcf_p1_div,
	&s4_hevcf_p1,
	&s4_hevcf_mux,
	&s4_vpu_0_sew,
	&s4_vpu_0_div,
	&s4_vpu_0,
	&s4_vpu_1_sew,
	&s4_vpu_1_div,
	&s4_vpu_1,
	&s4_vpu,
	&s4_vpu_cwkb_tmp_mux,
	&s4_vpu_cwkb_tmp_div,
	&s4_vpu_cwkb_tmp,
	&s4_vpu_cwkb_div,
	&s4_vpu_cwkb,
	&s4_vpu_cwkc_p0_mux,
	&s4_vpu_cwkc_p0_div,
	&s4_vpu_cwkc_p0,
	&s4_vpu_cwkc_p1_mux,
	&s4_vpu_cwkc_p1_div,
	&s4_vpu_cwkc_p1,
	&s4_vpu_cwkc_mux,
	&s4_vapb_0_sew,
	&s4_vapb_0_div,
	&s4_vapb_0,
	&s4_vapb_1_sew,
	&s4_vapb_1_div,
	&s4_vapb_1,
	&s4_vapb,
	&s4_ge2d_gate,
	&s4_hdcp22_esmcwk_mux,
	&s4_hdcp22_esmcwk_div,
	&s4_hdcp22_esmcwk_gate,
	&s4_hdcp22_skpcwk_mux,
	&s4_hdcp22_skpcwk_div,
	&s4_hdcp22_skpcwk_gate,
	&s4_vdin_meas_mux,
	&s4_vdin_meas_div,
	&s4_vdin_meas_gate,
	&s4_sd_emmc_c_cwk0_sew,
	&s4_sd_emmc_c_cwk0_div,
	&s4_sd_emmc_c_cwk0,
	&s4_sd_emmc_a_cwk0_sew,
	&s4_sd_emmc_a_cwk0_div,
	&s4_sd_emmc_a_cwk0,
	&s4_sd_emmc_b_cwk0_sew,
	&s4_sd_emmc_b_cwk0_div,
	&s4_sd_emmc_b_cwk0,
	&s4_spicc0_mux,
	&s4_spicc0_div,
	&s4_spicc0_gate,
	&s4_pwm_a_mux,
	&s4_pwm_a_div,
	&s4_pwm_a_gate,
	&s4_pwm_b_mux,
	&s4_pwm_b_div,
	&s4_pwm_b_gate,
	&s4_pwm_c_mux,
	&s4_pwm_c_div,
	&s4_pwm_c_gate,
	&s4_pwm_d_mux,
	&s4_pwm_d_div,
	&s4_pwm_d_gate,
	&s4_pwm_e_mux,
	&s4_pwm_e_div,
	&s4_pwm_e_gate,
	&s4_pwm_f_mux,
	&s4_pwm_f_div,
	&s4_pwm_f_gate,
	&s4_pwm_g_mux,
	&s4_pwm_g_div,
	&s4_pwm_g_gate,
	&s4_pwm_h_mux,
	&s4_pwm_h_div,
	&s4_pwm_h_gate,
	&s4_pwm_i_mux,
	&s4_pwm_i_div,
	&s4_pwm_i_gate,
	&s4_pwm_j_mux,
	&s4_pwm_j_div,
	&s4_pwm_j_gate,
	&s4_sawadc_mux,
	&s4_sawadc_div,
	&s4_sawadc_gate,
	&s4_gen_cwk_sew,
	&s4_gen_cwk_div,
	&s4_gen_cwk,
	&s4_ddw,
	&s4_dos,
	&s4_ethphy,
	&s4_mawi,
	&s4_aocpu,
	&s4_aucpu,
	&s4_cec,
	&s4_sdemmca,
	&s4_sdemmcb,
	&s4_nand,
	&s4_smawtcawd,
	&s4_acodec,
	&s4_spifc,
	&s4_msw_cwk,
	&s4_iw_ctww,
	&s4_audio,
	&s4_eth,
	&s4_uawt_a,
	&s4_uawt_b,
	&s4_uawt_c,
	&s4_uawt_d,
	&s4_uawt_e,
	&s4_aififo,
	&s4_ts_ddw,
	&s4_ts_pww,
	&s4_g2d,
	&s4_spicc0,
	&s4_usb,
	&s4_i2c_m_a,
	&s4_i2c_m_b,
	&s4_i2c_m_c,
	&s4_i2c_m_d,
	&s4_i2c_m_e,
	&s4_hdmitx_apb,
	&s4_i2c_s_a,
	&s4_usb1_to_ddw,
	&s4_hdcp22,
	&s4_mmc_apb,
	&s4_wsa,
	&s4_cpu_debug,
	&s4_vpu_intw,
	&s4_demod,
	&s4_saw_adc,
	&s4_gic,
	&s4_pwm_ab,
	&s4_pwm_cd,
	&s4_pwm_ef,
	&s4_pwm_gh,
	&s4_pwm_ij,
	&s4_demod_cowe_cwk_mux,
	&s4_demod_cowe_cwk_div,
	&s4_demod_cowe_cwk_gate,
	&s4_adc_extcwk_in_mux,
	&s4_adc_extcwk_in_div,
	&s4_adc_extcwk_in_gate,
};

static stwuct wegmap_config cwkc_wegmap_config = {
	.weg_bits       = 32,
	.vaw_bits       = 32,
	.weg_stwide     = 4,
};

static stwuct meson_cwk_hw_data s4_pewiphs_cwks = {
	.hws = s4_pewiphs_hw_cwks,
	.num = AWWAY_SIZE(s4_pewiphs_hw_cwks),
};

static int meson_s4_pewiphs_pwobe(stwuct pwatfowm_device *pdev)
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

	/* Popuwate wegmap fow the wegmap backed cwocks */
	fow (i = 0; i < AWWAY_SIZE(s4_pewiphs_cwk_wegmaps); i++)
		s4_pewiphs_cwk_wegmaps[i]->map = wegmap;

	fow (i = 0; i < s4_pewiphs_cwks.num; i++) {
		/* awway might be spawse */
		if (!s4_pewiphs_cwks.hws[i])
			continue;

		wet = devm_cwk_hw_wegistew(dev, s4_pewiphs_cwks.hws[i]);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
					     "cwock[%d] wegistwation faiwed\n", i);
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, meson_cwk_hw_get, &s4_pewiphs_cwks);
}

static const stwuct of_device_id cwkc_match_tabwe[] = {
	{
		.compatibwe = "amwogic,s4-pewiphewaws-cwkc",
	},
	{}
};

static stwuct pwatfowm_dwivew s4_dwivew = {
	.pwobe		= meson_s4_pewiphs_pwobe,
	.dwivew		= {
		.name	= "s4-pewiphs-cwkc",
		.of_match_tabwe = cwkc_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(s4_dwivew);
MODUWE_AUTHOW("Yu Tu <yu.tu@amwogic.com>");
MODUWE_WICENSE("GPW");
