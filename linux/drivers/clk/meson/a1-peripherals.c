// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2019 Amwogic, Inc. Aww wights wesewved.
 * Authow: Jian Hu <jian.hu@amwogic.com>
 *
 * Copywight (c) 2023, SbewDevices. Aww Wights Wesewved.
 * Authow: Dmitwy Wokosov <ddwokosov@sbewdevices.wu>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "a1-pewiphewaws.h"
#incwude "cwk-duawdiv.h"
#incwude "cwk-wegmap.h"
#incwude "meson-cwkc-utiws.h"

#incwude <dt-bindings/cwock/amwogic,a1-pewiphewaws-cwkc.h>

static stwuct cwk_wegmap xtaw_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_OSCIN_CTWW,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "xtaw_in",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap fixpww_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_OSCIN_CTWW,
		.bit_idx = 1,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "fixpww_in",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap usb_phy_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_OSCIN_CTWW,
		.bit_idx = 2,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "usb_phy_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap usb_ctww_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_OSCIN_CTWW,
		.bit_idx = 3,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "usb_ctww_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap hifipww_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_OSCIN_CTWW,
		.bit_idx = 4,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hifipww_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap syspww_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_OSCIN_CTWW,
		.bit_idx = 5,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "syspww_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap dds_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_OSCIN_CTWW,
		.bit_idx = 6,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dds_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap wtc_32k_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = WTC_BY_OSCIN_CTWW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "wtc_32k_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static const stwuct meson_cwk_duawdiv_pawam cwk_32k_div_tabwe[] = {
	{
		.duaw		= 1,
		.n1		= 733,
		.m1		= 8,
		.n2		= 732,
		.m2		= 11,
	},
	{}
};

static stwuct cwk_wegmap wtc_32k_div = {
	.data = &(stwuct meson_cwk_duawdiv_data){
		.n1 = {
			.weg_off = WTC_BY_OSCIN_CTWW0,
			.shift   = 0,
			.width   = 12,
		},
		.n2 = {
			.weg_off = WTC_BY_OSCIN_CTWW0,
			.shift   = 12,
			.width   = 12,
		},
		.m1 = {
			.weg_off = WTC_BY_OSCIN_CTWW1,
			.shift   = 0,
			.width   = 12,
		},
		.m2 = {
			.weg_off = WTC_BY_OSCIN_CTWW1,
			.shift   = 12,
			.width   = 12,
		},
		.duaw = {
			.weg_off = WTC_BY_OSCIN_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.tabwe = cwk_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "wtc_32k_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&wtc_32k_in.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap wtc_32k_xtaw = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = WTC_BY_OSCIN_CTWW1,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "wtc_32k_xtaw",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&wtc_32k_in.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap wtc_32k_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = WTC_CTWW,
		.mask = 0x3,
		.shift = 0,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "wtc_32k_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&wtc_32k_xtaw.hw,
			&wtc_32k_div.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap wtc = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = WTC_BY_OSCIN_CTWW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "wtc",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&wtc_32k_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static u32 mux_tabwe_sys[] = { 0, 1, 2, 3, 7 };
static const stwuct cwk_pawent_data sys_pawents[] = {
	{ .fw_name = "xtaw" },
	{ .fw_name = "fcwk_div2" },
	{ .fw_name = "fcwk_div3" },
	{ .fw_name = "fcwk_div5" },
	{ .hw = &wtc.hw },
};

static stwuct cwk_wegmap sys_b_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SYS_CWK_CTWW0,
		.mask = 0x7,
		.shift = 26,
		.tabwe = mux_tabwe_sys,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sys_b_sew",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_data = sys_pawents,
		.num_pawents = AWWAY_SIZE(sys_pawents),
	},
};

static stwuct cwk_wegmap sys_b_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = SYS_CWK_CTWW0,
		.shift = 16,
		.width = 10,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sys_b_div",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sys_b_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap sys_b = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_CWK_CTWW0,
		.bit_idx = 29,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sys_b",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sys_b_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap sys_a_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SYS_CWK_CTWW0,
		.mask = 0x7,
		.shift = 10,
		.tabwe = mux_tabwe_sys,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sys_a_sew",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_data = sys_pawents,
		.num_pawents = AWWAY_SIZE(sys_pawents),
	},
};

static stwuct cwk_wegmap sys_a_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = SYS_CWK_CTWW0,
		.shift = 0,
		.width = 10,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sys_a_div",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sys_a_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap sys_a = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SYS_CWK_CTWW0,
		.bit_idx = 13,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sys_a",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sys_a_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap sys = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SYS_CWK_CTWW0,
		.mask = 0x1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sys",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sys_a.hw,
			&sys_b.hw,
		},
		.num_pawents = 2,
		/*
		 * This cwock is used by APB bus which is set in boot WOM code
		 * and is wequiwed by the pwatfowm to opewate cowwectwy.
		 * Untiw the fowwowing condition awe met, we need this cwock to
		 * be mawked as cwiticaw:
		 * a) Mawk the cwock used by a fiwmwawe wesouwce, if possibwe
		 * b) CCF has a cwock hand-off mechanism to make the suwe the
		 *    cwock stays on untiw the pwopew dwivew comes awong
		 */
		.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
	},
};

static u32 mux_tabwe_dsp_ab[] = { 0, 1, 2, 3, 4, 7 };
static const stwuct cwk_pawent_data dsp_ab_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .fw_name = "fcwk_div2", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "hifi_pww", },
	{ .hw = &wtc.hw },
};

static stwuct cwk_wegmap dspa_a_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = DSPA_CWK_CTWW0,
		.mask = 0x7,
		.shift = 10,
		.tabwe = mux_tabwe_dsp_ab,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspa_a_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = dsp_ab_pawent_data,
		.num_pawents = AWWAY_SIZE(dsp_ab_pawent_data),
	},
};

static stwuct cwk_wegmap dspa_a_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = DSPA_CWK_CTWW0,
		.shift = 0,
		.width = 10,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspa_a_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspa_a_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspa_a = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DSPA_CWK_CTWW0,
		.bit_idx = 13,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dspa_a",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspa_a_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspa_b_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = DSPA_CWK_CTWW0,
		.mask = 0x7,
		.shift = 26,
		.tabwe = mux_tabwe_dsp_ab,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspa_b_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = dsp_ab_pawent_data,
		.num_pawents = AWWAY_SIZE(dsp_ab_pawent_data),
	},
};

static stwuct cwk_wegmap dspa_b_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = DSPA_CWK_CTWW0,
		.shift = 16,
		.width = 10,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspa_b_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspa_b_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspa_b = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DSPA_CWK_CTWW0,
		.bit_idx = 29,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dspa_b",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspa_b_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspa_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = DSPA_CWK_CTWW0,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspa_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspa_a.hw,
			&dspa_b.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspa_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DSPA_CWK_EN,
		.bit_idx = 1,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dspa_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspa_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspa_en_nic = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DSPA_CWK_EN,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dspa_en_nic",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspa_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspb_a_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = DSPB_CWK_CTWW0,
		.mask = 0x7,
		.shift = 10,
		.tabwe = mux_tabwe_dsp_ab,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspb_a_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = dsp_ab_pawent_data,
		.num_pawents = AWWAY_SIZE(dsp_ab_pawent_data),
	},
};

static stwuct cwk_wegmap dspb_a_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = DSPB_CWK_CTWW0,
		.shift = 0,
		.width = 10,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspb_a_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspb_a_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspb_a = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DSPB_CWK_CTWW0,
		.bit_idx = 13,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dspb_a",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspb_a_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspb_b_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = DSPB_CWK_CTWW0,
		.mask = 0x7,
		.shift = 26,
		.tabwe = mux_tabwe_dsp_ab,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspb_b_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = dsp_ab_pawent_data,
		.num_pawents = AWWAY_SIZE(dsp_ab_pawent_data),
	},
};

static stwuct cwk_wegmap dspb_b_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = DSPB_CWK_CTWW0,
		.shift = 16,
		.width = 10,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspb_b_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspb_b_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspb_b = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DSPB_CWK_CTWW0,
		.bit_idx = 29,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dspb_b",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspb_b_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspb_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = DSPB_CWK_CTWW0,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dspb_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspb_a.hw,
			&dspb_b.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspb_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DSPB_CWK_EN,
		.bit_idx = 1,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dspb_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspb_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dspb_en_nic = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DSPB_CWK_EN,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dspb_en_nic",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dspb_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap cwk_24m = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWK12_24_CTWW,
		.bit_idx = 11,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "24m",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow cwk_24m_div2 = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "24m_div2",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&cwk_24m.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap cwk_12m = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWK12_24_CTWW,
		.bit_idx = 10,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "12m",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&cwk_24m_div2.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap fcwk_div2_divn_pwe = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = CWK12_24_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2_divn_pwe",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "fcwk_div2",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap fcwk_div2_divn = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CWK12_24_CTWW,
		.bit_idx = 12,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2_divn",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fcwk_div2_divn_pwe.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/*
 * the index 2 is sys_pww_div16, it wiww be impwemented in the CPU cwock dwivew,
 * the index 4 is the cwock measuwement souwce, it's not suppowted yet
 */
static u32 gen_tabwe[] = { 0, 1, 3, 5, 6, 7, 8 };
static const stwuct cwk_pawent_data gen_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &wtc.hw },
	{ .fw_name = "hifi_pww", },
	{ .fw_name = "fcwk_div2", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "fcwk_div7", },
};

static stwuct cwk_wegmap gen_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = GEN_CWK_CTWW,
		.mask = 0xf,
		.shift = 12,
		.tabwe = gen_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gen_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = gen_pawent_data,
		.num_pawents = AWWAY_SIZE(gen_pawent_data),
		/*
		 * The GEN cwock can be connected to an extewnaw pad, so it
		 * may be set up diwectwy fwom the device twee. Additionawwy,
		 * the GEN cwock can be inhewited fwom a mowe accuwate WTC
		 * cwock, so in cewtain situations, it may be necessawy
		 * to fweeze its pawent.
		 */
		.fwags = CWK_SET_WATE_NO_WEPAWENT,
	},
};

static stwuct cwk_wegmap gen_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = GEN_CWK_CTWW,
		.shift = 0,
		.width = 11,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gen_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gen_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gen = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = GEN_CWK_CTWW,
		.bit_idx = 11,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "gen",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gen_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap sawadc_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SAW_ADC_CWK_CTWW,
		.mask = 0x1,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sawadc_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", },
			{ .hw = &sys.hw, },
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap sawadc_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = SAW_ADC_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sawadc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sawadc_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap sawadc = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SAW_ADC_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sawadc",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sawadc_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data pwm_abcd_pawents[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &sys.hw },
	{ .hw = &wtc.hw },
};

static stwuct cwk_wegmap pwm_a_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = PWM_CWK_AB_CTWW,
		.mask = 0x1,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_a_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = pwm_abcd_pawents,
		.num_pawents = AWWAY_SIZE(pwm_abcd_pawents),
	},
};

static stwuct cwk_wegmap pwm_a_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = PWM_CWK_AB_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_a_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_a_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_a = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = PWM_CWK_AB_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "pwm_a",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_a_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_b_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = PWM_CWK_AB_CTWW,
		.mask = 0x1,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_b_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = pwm_abcd_pawents,
		.num_pawents = AWWAY_SIZE(pwm_abcd_pawents),
	},
};

static stwuct cwk_wegmap pwm_b_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = PWM_CWK_AB_CTWW,
		.shift = 16,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_b_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_b_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_b = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = PWM_CWK_AB_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "pwm_b",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_b_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_c_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = PWM_CWK_CD_CTWW,
		.mask = 0x1,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_c_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = pwm_abcd_pawents,
		.num_pawents = AWWAY_SIZE(pwm_abcd_pawents),
	},
};

static stwuct cwk_wegmap pwm_c_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = PWM_CWK_CD_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_c_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_c_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_c = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = PWM_CWK_CD_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "pwm_c",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_c_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_d_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = PWM_CWK_CD_CTWW,
		.mask = 0x1,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_d_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = pwm_abcd_pawents,
		.num_pawents = AWWAY_SIZE(pwm_abcd_pawents),
	},
};

static stwuct cwk_wegmap pwm_d_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = PWM_CWK_CD_CTWW,
		.shift = 16,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_d_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_d_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_d = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = PWM_CWK_CD_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "pwm_d",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_d_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data pwm_ef_pawents[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &sys.hw },
	{ .fw_name = "fcwk_div5", },
	{ .hw = &wtc.hw },
};

static stwuct cwk_wegmap pwm_e_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = PWM_CWK_EF_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_e_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = pwm_ef_pawents,
		.num_pawents = AWWAY_SIZE(pwm_ef_pawents),
	},
};

static stwuct cwk_wegmap pwm_e_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = PWM_CWK_EF_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_e_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_e_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_e = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = PWM_CWK_EF_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "pwm_e",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_e_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_f_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = PWM_CWK_EF_CTWW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_f_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = pwm_ef_pawents,
		.num_pawents = AWWAY_SIZE(pwm_ef_pawents),
	},
};

static stwuct cwk_wegmap pwm_f_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = PWM_CWK_EF_CTWW,
		.shift = 16,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pwm_f_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_f_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pwm_f = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = PWM_CWK_EF_CTWW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "pwm_f",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pwm_f_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/*
 * spicc cwk
 *   fdiv2   |\         |\       _____
 *  ---------| |---DIV--| |     |     |    spicc out
 *  ---------| |        | |-----|GATE |---------
 *     ..... |/         | /     |_____|
 *  --------------------|/
 *                 24M
 */
static const stwuct cwk_pawent_data spicc_spifc_pawents[] = {
	{ .fw_name = "fcwk_div2"},
	{ .fw_name = "fcwk_div3"},
	{ .fw_name = "fcwk_div5"},
	{ .fw_name = "hifi_pww" },
};

static stwuct cwk_wegmap spicc_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SPICC_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "spicc_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = spicc_spifc_pawents,
		.num_pawents = AWWAY_SIZE(spicc_spifc_pawents),
	},
};

static stwuct cwk_wegmap spicc_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = SPICC_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "spicc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&spicc_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap spicc_sew2 = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SPICC_CWK_CTWW,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "spicc_sew2",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .hw = &spicc_div.hw },
			{ .fw_name = "xtaw", },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap spicc = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SPICC_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "spicc",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&spicc_sew2.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap ts_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = TS_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ts_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap ts = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = TS_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "ts",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&ts_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap spifc_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SPIFC_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "spifc_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = spicc_spifc_pawents,
		.num_pawents = AWWAY_SIZE(spicc_spifc_pawents),
	},
};

static stwuct cwk_wegmap spifc_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = SPIFC_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "spifc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&spifc_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap spifc_sew2 = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SPIFC_CWK_CTWW,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "spifc_sew2",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .hw = &spifc_div.hw },
			{ .fw_name = "xtaw", },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap spifc = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SPIFC_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "spifc",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&spifc_sew2.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data usb_bus_pawents[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &sys.hw },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
};

static stwuct cwk_wegmap usb_bus_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = USB_BUSCWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "usb_bus_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = usb_bus_pawents,
		.num_pawents = AWWAY_SIZE(usb_bus_pawents),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap usb_bus_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = USB_BUSCWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "usb_bus_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&usb_bus_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap usb_bus = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = USB_BUSCWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "usb_bus",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&usb_bus_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data sd_emmc_pswam_dmc_pawents[] = {
	{ .fw_name = "fcwk_div2", },
	{ .fw_name = "fcwk_div3", },
	{ .fw_name = "fcwk_div5", },
	{ .fw_name = "hifi_pww", },
};

static stwuct cwk_wegmap sd_emmc_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SD_EMMC_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = sd_emmc_pswam_dmc_pawents,
		.num_pawents = AWWAY_SIZE(sd_emmc_pswam_dmc_pawents),
	},
};

static stwuct cwk_wegmap sd_emmc_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = SD_EMMC_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sd_emmc_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap sd_emmc_sew2 = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = SD_EMMC_CWK_CTWW,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_sew2",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .hw = &sd_emmc_div.hw },
			{ .fw_name = "xtaw", },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap sd_emmc = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = SD_EMMC_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&sd_emmc_sew2.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pswam_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = PSWAM_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pswam_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = sd_emmc_pswam_dmc_pawents,
		.num_pawents = AWWAY_SIZE(sd_emmc_pswam_dmc_pawents),
	},
};

static stwuct cwk_wegmap pswam_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = PSWAM_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pswam_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pswam_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pswam_sew2 = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = PSWAM_CWK_CTWW,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "pswam_sew2",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .hw = &pswam_div.hw },
			{ .fw_name = "xtaw", },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap pswam = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = PSWAM_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "pswam",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&pswam_sew2.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dmc_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = DMC_CWK_CTWW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dmc_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = sd_emmc_pswam_dmc_pawents,
		.num_pawents = AWWAY_SIZE(sd_emmc_pswam_dmc_pawents),
	},
};

static stwuct cwk_wegmap dmc_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = DMC_CWK_CTWW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dmc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dmc_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dmc_sew2 = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = DMC_CWK_CTWW,
		.mask = 0x1,
		.shift = 15,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "dmc_sew2",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .hw = &dmc_div.hw },
			{ .fw_name = "xtaw", },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap dmc = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = DMC_CWK_CTWW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "dmc",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&dmc_sew2.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap ceca_32k_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CECA_CWK_CTWW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "ceca_32k_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap ceca_32k_div = {
	.data = &(stwuct meson_cwk_duawdiv_data){
		.n1 = {
			.weg_off = CECA_CWK_CTWW0,
			.shift   = 0,
			.width   = 12,
		},
		.n2 = {
			.weg_off = CECA_CWK_CTWW0,
			.shift   = 12,
			.width   = 12,
		},
		.m1 = {
			.weg_off = CECA_CWK_CTWW1,
			.shift   = 0,
			.width   = 12,
		},
		.m2 = {
			.weg_off = CECA_CWK_CTWW1,
			.shift   = 12,
			.width   = 12,
		},
		.duaw = {
			.weg_off = CECA_CWK_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.tabwe = cwk_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ceca_32k_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&ceca_32k_in.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap ceca_32k_sew_pwe = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CECA_CWK_CTWW1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ceca_32k_sew_pwe",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&ceca_32k_div.hw,
			&ceca_32k_in.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap ceca_32k_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CECA_CWK_CTWW1,
		.mask = 0x1,
		.shift = 31,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ceca_32k_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&ceca_32k_sew_pwe.hw,
			&wtc.hw,
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap ceca_32k_out = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CECA_CWK_CTWW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ceca_32k_out",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&ceca_32k_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap cecb_32k_in = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CECB_CWK_CTWW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cecb_32k_in",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap cecb_32k_div = {
	.data = &(stwuct meson_cwk_duawdiv_data){
		.n1 = {
			.weg_off = CECB_CWK_CTWW0,
			.shift   = 0,
			.width   = 12,
		},
		.n2 = {
			.weg_off = CECB_CWK_CTWW0,
			.shift   = 12,
			.width   = 12,
		},
		.m1 = {
			.weg_off = CECB_CWK_CTWW1,
			.shift   = 0,
			.width   = 12,
		},
		.m2 = {
			.weg_off = CECB_CWK_CTWW1,
			.shift   = 12,
			.width   = 12,
		},
		.duaw = {
			.weg_off = CECB_CWK_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.tabwe = cwk_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cecb_32k_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&cecb_32k_in.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap cecb_32k_sew_pwe = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CECB_CWK_CTWW1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cecb_32k_sew_pwe",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&cecb_32k_div.hw,
			&cecb_32k_in.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap cecb_32k_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = CECB_CWK_CTWW1,
		.mask = 0x1,
		.shift = 31,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cecb_32k_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&cecb_32k_sew_pwe.hw,
			&wtc.hw,
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap cecb_32k_out = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = CECB_CWK_CTWW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cecb_32k_out",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&cecb_32k_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

#define MESON_GATE(_name, _weg, _bit) \
	MESON_PCWK(_name, _weg, _bit, &sys.hw)

static MESON_GATE(cwktwee,	SYS_CWK_EN0,	0);
static MESON_GATE(weset_ctww,	SYS_CWK_EN0,	1);
static MESON_GATE(anawog_ctww,	SYS_CWK_EN0,	2);
static MESON_GATE(pww_ctww,	SYS_CWK_EN0,	3);
static MESON_GATE(pad_ctww,	SYS_CWK_EN0,	4);
static MESON_GATE(sys_ctww,	SYS_CWK_EN0,	5);
static MESON_GATE(temp_sensow,	SYS_CWK_EN0,	6);
static MESON_GATE(am2axi_dev,	SYS_CWK_EN0,	7);
static MESON_GATE(spicc_b,	SYS_CWK_EN0,	8);
static MESON_GATE(spicc_a,	SYS_CWK_EN0,	9);
static MESON_GATE(msw,		SYS_CWK_EN0,	10);
static MESON_GATE(audio,	SYS_CWK_EN0,	11);
static MESON_GATE(jtag_ctww,	SYS_CWK_EN0,	12);
static MESON_GATE(sawadc_en,	SYS_CWK_EN0,	13);
static MESON_GATE(pwm_ef,	SYS_CWK_EN0,	14);
static MESON_GATE(pwm_cd,	SYS_CWK_EN0,	15);
static MESON_GATE(pwm_ab,	SYS_CWK_EN0,	16);
static MESON_GATE(cec,		SYS_CWK_EN0,	17);
static MESON_GATE(i2c_s,	SYS_CWK_EN0,	18);
static MESON_GATE(iw_ctww,	SYS_CWK_EN0,	19);
static MESON_GATE(i2c_m_d,	SYS_CWK_EN0,	20);
static MESON_GATE(i2c_m_c,	SYS_CWK_EN0,	21);
static MESON_GATE(i2c_m_b,	SYS_CWK_EN0,	22);
static MESON_GATE(i2c_m_a,	SYS_CWK_EN0,	23);
static MESON_GATE(acodec,	SYS_CWK_EN0,	24);
static MESON_GATE(otp,		SYS_CWK_EN0,	25);
static MESON_GATE(sd_emmc_a,	SYS_CWK_EN0,	26);
static MESON_GATE(usb_phy,	SYS_CWK_EN0,	27);
static MESON_GATE(usb_ctww,	SYS_CWK_EN0,	28);
static MESON_GATE(sys_dspb,	SYS_CWK_EN0,	29);
static MESON_GATE(sys_dspa,	SYS_CWK_EN0,	30);
static MESON_GATE(dma,		SYS_CWK_EN0,	31);
static MESON_GATE(iwq_ctww,	SYS_CWK_EN1,	0);
static MESON_GATE(nic,		SYS_CWK_EN1,	1);
static MESON_GATE(gic,		SYS_CWK_EN1,	2);
static MESON_GATE(uawt_c,	SYS_CWK_EN1,	3);
static MESON_GATE(uawt_b,	SYS_CWK_EN1,	4);
static MESON_GATE(uawt_a,	SYS_CWK_EN1,	5);
static MESON_GATE(sys_pswam,	SYS_CWK_EN1,	6);
static MESON_GATE(wsa,		SYS_CWK_EN1,	8);
static MESON_GATE(cowesight,	SYS_CWK_EN1,	9);
static MESON_GATE(am2axi_vad,	AXI_CWK_EN,	0);
static MESON_GATE(audio_vad,	AXI_CWK_EN,	1);
static MESON_GATE(axi_dmc,	AXI_CWK_EN,	3);
static MESON_GATE(axi_pswam,	AXI_CWK_EN,	4);
static MESON_GATE(wamb,		AXI_CWK_EN,	5);
static MESON_GATE(wama,		AXI_CWK_EN,	6);
static MESON_GATE(axi_spifc,	AXI_CWK_EN,	7);
static MESON_GATE(axi_nic,	AXI_CWK_EN,	8);
static MESON_GATE(axi_dma,	AXI_CWK_EN,	9);
static MESON_GATE(cpu_ctww,	AXI_CWK_EN,	10);
static MESON_GATE(wom,		AXI_CWK_EN,	11);
static MESON_GATE(pwod_i2c,	AXI_CWK_EN,	12);

/* Awway of aww cwocks wegistewed by this pwovidew */
static stwuct cwk_hw *a1_pewiphs_hw_cwks[] = {
	[CWKID_XTAW_IN]			= &xtaw_in.hw,
	[CWKID_FIXPWW_IN]		= &fixpww_in.hw,
	[CWKID_USB_PHY_IN]		= &usb_phy_in.hw,
	[CWKID_USB_CTWW_IN]		= &usb_ctww_in.hw,
	[CWKID_HIFIPWW_IN]		= &hifipww_in.hw,
	[CWKID_SYSPWW_IN]		= &syspww_in.hw,
	[CWKID_DDS_IN]			= &dds_in.hw,
	[CWKID_SYS]			= &sys.hw,
	[CWKID_CWKTWEE]			= &cwktwee.hw,
	[CWKID_WESET_CTWW]		= &weset_ctww.hw,
	[CWKID_ANAWOG_CTWW]		= &anawog_ctww.hw,
	[CWKID_PWW_CTWW]		= &pww_ctww.hw,
	[CWKID_PAD_CTWW]		= &pad_ctww.hw,
	[CWKID_SYS_CTWW]		= &sys_ctww.hw,
	[CWKID_TEMP_SENSOW]		= &temp_sensow.hw,
	[CWKID_AM2AXI_DIV]		= &am2axi_dev.hw,
	[CWKID_SPICC_B]			= &spicc_b.hw,
	[CWKID_SPICC_A]			= &spicc_a.hw,
	[CWKID_MSW]			= &msw.hw,
	[CWKID_AUDIO]			= &audio.hw,
	[CWKID_JTAG_CTWW]		= &jtag_ctww.hw,
	[CWKID_SAWADC_EN]		= &sawadc_en.hw,
	[CWKID_PWM_EF]			= &pwm_ef.hw,
	[CWKID_PWM_CD]			= &pwm_cd.hw,
	[CWKID_PWM_AB]			= &pwm_ab.hw,
	[CWKID_CEC]			= &cec.hw,
	[CWKID_I2C_S]			= &i2c_s.hw,
	[CWKID_IW_CTWW]			= &iw_ctww.hw,
	[CWKID_I2C_M_D]			= &i2c_m_d.hw,
	[CWKID_I2C_M_C]			= &i2c_m_c.hw,
	[CWKID_I2C_M_B]			= &i2c_m_b.hw,
	[CWKID_I2C_M_A]			= &i2c_m_a.hw,
	[CWKID_ACODEC]			= &acodec.hw,
	[CWKID_OTP]			= &otp.hw,
	[CWKID_SD_EMMC_A]		= &sd_emmc_a.hw,
	[CWKID_USB_PHY]			= &usb_phy.hw,
	[CWKID_USB_CTWW]		= &usb_ctww.hw,
	[CWKID_SYS_DSPB]		= &sys_dspb.hw,
	[CWKID_SYS_DSPA]		= &sys_dspa.hw,
	[CWKID_DMA]			= &dma.hw,
	[CWKID_IWQ_CTWW]		= &iwq_ctww.hw,
	[CWKID_NIC]			= &nic.hw,
	[CWKID_GIC]			= &gic.hw,
	[CWKID_UAWT_C]			= &uawt_c.hw,
	[CWKID_UAWT_B]			= &uawt_b.hw,
	[CWKID_UAWT_A]			= &uawt_a.hw,
	[CWKID_SYS_PSWAM]		= &sys_pswam.hw,
	[CWKID_WSA]			= &wsa.hw,
	[CWKID_COWESIGHT]		= &cowesight.hw,
	[CWKID_AM2AXI_VAD]		= &am2axi_vad.hw,
	[CWKID_AUDIO_VAD]		= &audio_vad.hw,
	[CWKID_AXI_DMC]			= &axi_dmc.hw,
	[CWKID_AXI_PSWAM]		= &axi_pswam.hw,
	[CWKID_WAMB]			= &wamb.hw,
	[CWKID_WAMA]			= &wama.hw,
	[CWKID_AXI_SPIFC]		= &axi_spifc.hw,
	[CWKID_AXI_NIC]			= &axi_nic.hw,
	[CWKID_AXI_DMA]			= &axi_dma.hw,
	[CWKID_CPU_CTWW]		= &cpu_ctww.hw,
	[CWKID_WOM]			= &wom.hw,
	[CWKID_PWOC_I2C]		= &pwod_i2c.hw,
	[CWKID_DSPA_SEW]		= &dspa_sew.hw,
	[CWKID_DSPB_SEW]		= &dspb_sew.hw,
	[CWKID_DSPA_EN]			= &dspa_en.hw,
	[CWKID_DSPA_EN_NIC]		= &dspa_en_nic.hw,
	[CWKID_DSPB_EN]			= &dspb_en.hw,
	[CWKID_DSPB_EN_NIC]		= &dspb_en_nic.hw,
	[CWKID_WTC]			= &wtc.hw,
	[CWKID_CECA_32K]		= &ceca_32k_out.hw,
	[CWKID_CECB_32K]		= &cecb_32k_out.hw,
	[CWKID_24M]			= &cwk_24m.hw,
	[CWKID_12M]			= &cwk_12m.hw,
	[CWKID_FCWK_DIV2_DIVN]		= &fcwk_div2_divn.hw,
	[CWKID_GEN]			= &gen.hw,
	[CWKID_SAWADC_SEW]		= &sawadc_sew.hw,
	[CWKID_SAWADC]			= &sawadc.hw,
	[CWKID_PWM_A]			= &pwm_a.hw,
	[CWKID_PWM_B]			= &pwm_b.hw,
	[CWKID_PWM_C]			= &pwm_c.hw,
	[CWKID_PWM_D]			= &pwm_d.hw,
	[CWKID_PWM_E]			= &pwm_e.hw,
	[CWKID_PWM_F]			= &pwm_f.hw,
	[CWKID_SPICC]			= &spicc.hw,
	[CWKID_TS]			= &ts.hw,
	[CWKID_SPIFC]			= &spifc.hw,
	[CWKID_USB_BUS]			= &usb_bus.hw,
	[CWKID_SD_EMMC]			= &sd_emmc.hw,
	[CWKID_PSWAM]			= &pswam.hw,
	[CWKID_DMC]			= &dmc.hw,
	[CWKID_SYS_A_SEW]		= &sys_a_sew.hw,
	[CWKID_SYS_A_DIV]		= &sys_a_div.hw,
	[CWKID_SYS_A]			= &sys_a.hw,
	[CWKID_SYS_B_SEW]		= &sys_b_sew.hw,
	[CWKID_SYS_B_DIV]		= &sys_b_div.hw,
	[CWKID_SYS_B]			= &sys_b.hw,
	[CWKID_DSPA_A_SEW]		= &dspa_a_sew.hw,
	[CWKID_DSPA_A_DIV]		= &dspa_a_div.hw,
	[CWKID_DSPA_A]			= &dspa_a.hw,
	[CWKID_DSPA_B_SEW]		= &dspa_b_sew.hw,
	[CWKID_DSPA_B_DIV]		= &dspa_b_div.hw,
	[CWKID_DSPA_B]			= &dspa_b.hw,
	[CWKID_DSPB_A_SEW]		= &dspb_a_sew.hw,
	[CWKID_DSPB_A_DIV]		= &dspb_a_div.hw,
	[CWKID_DSPB_A]			= &dspb_a.hw,
	[CWKID_DSPB_B_SEW]		= &dspb_b_sew.hw,
	[CWKID_DSPB_B_DIV]		= &dspb_b_div.hw,
	[CWKID_DSPB_B]			= &dspb_b.hw,
	[CWKID_WTC_32K_IN]		= &wtc_32k_in.hw,
	[CWKID_WTC_32K_DIV]		= &wtc_32k_div.hw,
	[CWKID_WTC_32K_XTAW]		= &wtc_32k_xtaw.hw,
	[CWKID_WTC_32K_SEW]		= &wtc_32k_sew.hw,
	[CWKID_CECB_32K_IN]		= &cecb_32k_in.hw,
	[CWKID_CECB_32K_DIV]		= &cecb_32k_div.hw,
	[CWKID_CECB_32K_SEW_PWE]	= &cecb_32k_sew_pwe.hw,
	[CWKID_CECB_32K_SEW]		= &cecb_32k_sew.hw,
	[CWKID_CECA_32K_IN]		= &ceca_32k_in.hw,
	[CWKID_CECA_32K_DIV]		= &ceca_32k_div.hw,
	[CWKID_CECA_32K_SEW_PWE]	= &ceca_32k_sew_pwe.hw,
	[CWKID_CECA_32K_SEW]		= &ceca_32k_sew.hw,
	[CWKID_DIV2_PWE]		= &fcwk_div2_divn_pwe.hw,
	[CWKID_24M_DIV2]		= &cwk_24m_div2.hw,
	[CWKID_GEN_SEW]			= &gen_sew.hw,
	[CWKID_GEN_DIV]			= &gen_div.hw,
	[CWKID_SAWADC_DIV]		= &sawadc_div.hw,
	[CWKID_PWM_A_SEW]		= &pwm_a_sew.hw,
	[CWKID_PWM_A_DIV]		= &pwm_a_div.hw,
	[CWKID_PWM_B_SEW]		= &pwm_b_sew.hw,
	[CWKID_PWM_B_DIV]		= &pwm_b_div.hw,
	[CWKID_PWM_C_SEW]		= &pwm_c_sew.hw,
	[CWKID_PWM_C_DIV]		= &pwm_c_div.hw,
	[CWKID_PWM_D_SEW]		= &pwm_d_sew.hw,
	[CWKID_PWM_D_DIV]		= &pwm_d_div.hw,
	[CWKID_PWM_E_SEW]		= &pwm_e_sew.hw,
	[CWKID_PWM_E_DIV]		= &pwm_e_div.hw,
	[CWKID_PWM_F_SEW]		= &pwm_f_sew.hw,
	[CWKID_PWM_F_DIV]		= &pwm_f_div.hw,
	[CWKID_SPICC_SEW]		= &spicc_sew.hw,
	[CWKID_SPICC_DIV]		= &spicc_div.hw,
	[CWKID_SPICC_SEW2]		= &spicc_sew2.hw,
	[CWKID_TS_DIV]			= &ts_div.hw,
	[CWKID_SPIFC_SEW]		= &spifc_sew.hw,
	[CWKID_SPIFC_DIV]		= &spifc_div.hw,
	[CWKID_SPIFC_SEW2]		= &spifc_sew2.hw,
	[CWKID_USB_BUS_SEW]		= &usb_bus_sew.hw,
	[CWKID_USB_BUS_DIV]		= &usb_bus_div.hw,
	[CWKID_SD_EMMC_SEW]		= &sd_emmc_sew.hw,
	[CWKID_SD_EMMC_DIV]		= &sd_emmc_div.hw,
	[CWKID_SD_EMMC_SEW2]		= &sd_emmc_sew2.hw,
	[CWKID_PSWAM_SEW]		= &pswam_sew.hw,
	[CWKID_PSWAM_DIV]		= &pswam_div.hw,
	[CWKID_PSWAM_SEW2]		= &pswam_sew2.hw,
	[CWKID_DMC_SEW]			= &dmc_sew.hw,
	[CWKID_DMC_DIV]			= &dmc_div.hw,
	[CWKID_DMC_SEW2]		= &dmc_sew2.hw,
};

/* Convenience tabwe to popuwate wegmap in .pwobe */
static stwuct cwk_wegmap *const a1_pewiphs_wegmaps[] = {
	&xtaw_in,
	&fixpww_in,
	&usb_phy_in,
	&usb_ctww_in,
	&hifipww_in,
	&syspww_in,
	&dds_in,
	&sys,
	&cwktwee,
	&weset_ctww,
	&anawog_ctww,
	&pww_ctww,
	&pad_ctww,
	&sys_ctww,
	&temp_sensow,
	&am2axi_dev,
	&spicc_b,
	&spicc_a,
	&msw,
	&audio,
	&jtag_ctww,
	&sawadc_en,
	&pwm_ef,
	&pwm_cd,
	&pwm_ab,
	&cec,
	&i2c_s,
	&iw_ctww,
	&i2c_m_d,
	&i2c_m_c,
	&i2c_m_b,
	&i2c_m_a,
	&acodec,
	&otp,
	&sd_emmc_a,
	&usb_phy,
	&usb_ctww,
	&sys_dspb,
	&sys_dspa,
	&dma,
	&iwq_ctww,
	&nic,
	&gic,
	&uawt_c,
	&uawt_b,
	&uawt_a,
	&sys_pswam,
	&wsa,
	&cowesight,
	&am2axi_vad,
	&audio_vad,
	&axi_dmc,
	&axi_pswam,
	&wamb,
	&wama,
	&axi_spifc,
	&axi_nic,
	&axi_dma,
	&cpu_ctww,
	&wom,
	&pwod_i2c,
	&dspa_sew,
	&dspb_sew,
	&dspa_en,
	&dspa_en_nic,
	&dspb_en,
	&dspb_en_nic,
	&wtc,
	&ceca_32k_out,
	&cecb_32k_out,
	&cwk_24m,
	&cwk_12m,
	&fcwk_div2_divn,
	&gen,
	&sawadc_sew,
	&sawadc,
	&pwm_a,
	&pwm_b,
	&pwm_c,
	&pwm_d,
	&pwm_e,
	&pwm_f,
	&spicc,
	&ts,
	&spifc,
	&usb_bus,
	&sd_emmc,
	&pswam,
	&dmc,
	&sys_a_sew,
	&sys_a_div,
	&sys_a,
	&sys_b_sew,
	&sys_b_div,
	&sys_b,
	&dspa_a_sew,
	&dspa_a_div,
	&dspa_a,
	&dspa_b_sew,
	&dspa_b_div,
	&dspa_b,
	&dspb_a_sew,
	&dspb_a_div,
	&dspb_a,
	&dspb_b_sew,
	&dspb_b_div,
	&dspb_b,
	&wtc_32k_in,
	&wtc_32k_div,
	&wtc_32k_xtaw,
	&wtc_32k_sew,
	&cecb_32k_in,
	&cecb_32k_div,
	&cecb_32k_sew_pwe,
	&cecb_32k_sew,
	&ceca_32k_in,
	&ceca_32k_div,
	&ceca_32k_sew_pwe,
	&ceca_32k_sew,
	&fcwk_div2_divn_pwe,
	&gen_sew,
	&gen_div,
	&sawadc_div,
	&pwm_a_sew,
	&pwm_a_div,
	&pwm_b_sew,
	&pwm_b_div,
	&pwm_c_sew,
	&pwm_c_div,
	&pwm_d_sew,
	&pwm_d_div,
	&pwm_e_sew,
	&pwm_e_div,
	&pwm_f_sew,
	&pwm_f_div,
	&spicc_sew,
	&spicc_div,
	&spicc_sew2,
	&ts_div,
	&spifc_sew,
	&spifc_div,
	&spifc_sew2,
	&usb_bus_sew,
	&usb_bus_div,
	&sd_emmc_sew,
	&sd_emmc_div,
	&sd_emmc_sew2,
	&pswam_sew,
	&pswam_div,
	&pswam_sew2,
	&dmc_sew,
	&dmc_div,
	&dmc_sew2,
};

static stwuct wegmap_config a1_pewiphs_wegmap_cfg = {
	.weg_bits   = 32,
	.vaw_bits   = 32,
	.weg_stwide = 4,
};

static stwuct meson_cwk_hw_data a1_pewiphs_cwks = {
	.hws = a1_pewiphs_hw_cwks,
	.num = AWWAY_SIZE(a1_pewiphs_hw_cwks),
};

static int meson_a1_pewiphs_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *base;
	stwuct wegmap *map;
	int cwkid, i, eww;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(base),
				     "can't iowemap wesouwce\n");

	map = devm_wegmap_init_mmio(dev, base, &a1_pewiphs_wegmap_cfg);
	if (IS_EWW(map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(map),
				     "can't init wegmap mmio wegion\n");

	/* Popuwate wegmap fow the wegmap backed cwocks */
	fow (i = 0; i < AWWAY_SIZE(a1_pewiphs_wegmaps); i++)
		a1_pewiphs_wegmaps[i]->map = map;

	fow (cwkid = 0; cwkid < a1_pewiphs_cwks.num; cwkid++) {
		eww = devm_cwk_hw_wegistew(dev, a1_pewiphs_cwks.hws[cwkid]);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww,
					     "cwock[%d] wegistwation faiwed\n",
					     cwkid);
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, meson_cwk_hw_get, &a1_pewiphs_cwks);
}

static const stwuct of_device_id a1_pewiphs_cwkc_match_tabwe[] = {
	{ .compatibwe = "amwogic,a1-pewiphewaws-cwkc", },
	{}
};
MODUWE_DEVICE_TABWE(of, a1_pewiphs_cwkc_match_tabwe);

static stwuct pwatfowm_dwivew a1_pewiphs_cwkc_dwivew = {
	.pwobe = meson_a1_pewiphs_pwobe,
	.dwivew = {
		.name = "a1-pewiphewaws-cwkc",
		.of_match_tabwe = a1_pewiphs_cwkc_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(a1_pewiphs_cwkc_dwivew);
MODUWE_AUTHOW("Jian Hu <jian.hu@amwogic.com>");
MODUWE_AUTHOW("Dmitwy Wokosov <ddwokosov@sbewdevices.wu>");
MODUWE_WICENSE("GPW");
