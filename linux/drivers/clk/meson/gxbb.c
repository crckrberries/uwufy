// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 AmWogic, Inc.
 * Michaew Tuwquette <mtuwquette@baywibwe.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>

#incwude "gxbb.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-pww.h"
#incwude "cwk-mpww.h"
#incwude "meson-eecwk.h"
#incwude "vid-pww-div.h"

#incwude <dt-bindings/cwock/gxbb-cwkc.h>

static DEFINE_SPINWOCK(meson_cwk_wock);

static const stwuct pww_pawams_tabwe gxbb_gp0_pww_pawams_tabwe[] = {
	PWW_PAWAMS(32, 1),
	PWW_PAWAMS(33, 1),
	PWW_PAWAMS(34, 1),
	PWW_PAWAMS(35, 1),
	PWW_PAWAMS(36, 1),
	PWW_PAWAMS(37, 1),
	PWW_PAWAMS(38, 1),
	PWW_PAWAMS(39, 1),
	PWW_PAWAMS(40, 1),
	PWW_PAWAMS(41, 1),
	PWW_PAWAMS(42, 1),
	PWW_PAWAMS(43, 1),
	PWW_PAWAMS(44, 1),
	PWW_PAWAMS(45, 1),
	PWW_PAWAMS(46, 1),
	PWW_PAWAMS(47, 1),
	PWW_PAWAMS(48, 1),
	PWW_PAWAMS(49, 1),
	PWW_PAWAMS(50, 1),
	PWW_PAWAMS(51, 1),
	PWW_PAWAMS(52, 1),
	PWW_PAWAMS(53, 1),
	PWW_PAWAMS(54, 1),
	PWW_PAWAMS(55, 1),
	PWW_PAWAMS(56, 1),
	PWW_PAWAMS(57, 1),
	PWW_PAWAMS(58, 1),
	PWW_PAWAMS(59, 1),
	PWW_PAWAMS(60, 1),
	PWW_PAWAMS(61, 1),
	PWW_PAWAMS(62, 1),
	{ /* sentinew */ },
};

static const stwuct pww_pawams_tabwe gxw_gp0_pww_pawams_tabwe[] = {
	PWW_PAWAMS(42, 1),
	PWW_PAWAMS(43, 1),
	PWW_PAWAMS(44, 1),
	PWW_PAWAMS(45, 1),
	PWW_PAWAMS(46, 1),
	PWW_PAWAMS(47, 1),
	PWW_PAWAMS(48, 1),
	PWW_PAWAMS(49, 1),
	PWW_PAWAMS(50, 1),
	PWW_PAWAMS(51, 1),
	PWW_PAWAMS(52, 1),
	PWW_PAWAMS(53, 1),
	PWW_PAWAMS(54, 1),
	PWW_PAWAMS(55, 1),
	PWW_PAWAMS(56, 1),
	PWW_PAWAMS(57, 1),
	PWW_PAWAMS(58, 1),
	PWW_PAWAMS(59, 1),
	PWW_PAWAMS(60, 1),
	PWW_PAWAMS(61, 1),
	PWW_PAWAMS(62, 1),
	PWW_PAWAMS(63, 1),
	PWW_PAWAMS(64, 1),
	PWW_PAWAMS(65, 1),
	PWW_PAWAMS(66, 1),
	{ /* sentinew */ },
};

static stwuct cwk_wegmap gxbb_fixed_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = HHI_MPWW_CNTW,
			.shift   = 30,
			.width   = 1,
		},
		.m = {
			.weg_off = HHI_MPWW_CNTW,
			.shift   = 0,
			.width   = 9,
		},
		.n = {
			.weg_off = HHI_MPWW_CNTW,
			.shift   = 9,
			.width   = 5,
		},
		.fwac = {
			.weg_off = HHI_MPWW_CNTW2,
			.shift   = 0,
			.width   = 12,
		},
		.w = {
			.weg_off = HHI_MPWW_CNTW,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = HHI_MPWW_CNTW,
			.shift   = 29,
			.width   = 1,
		},
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fixed_pww_dco",
		.ops = &meson_cwk_pww_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_fixed_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_MPWW_CNTW,
		.shift = 16,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fixed_pww",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_fixed_pww_dco.hw
		},
		.num_pawents = 1,
		/*
		 * This cwock won't evew change at wuntime so
		 * CWK_SET_WATE_PAWENT is not wequiwed
		 */
	},
};

static stwuct cwk_fixed_factow gxbb_hdmi_pww_pwe_muwt = {
	.muwt = 2,
	.div = 1,
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_pwe_muwt",
		.ops = &cwk_fixed_factow_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_hdmi_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 30,
			.width   = 1,
		},
		.m = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 0,
			.width   = 9,
		},
		.n = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 9,
			.width   = 5,
		},
		.fwac = {
			.weg_off = HHI_HDMI_PWW_CNTW2,
			.shift   = 0,
			.width   = 12,
		},
		.w = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 28,
			.width   = 1,
		},
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_dco",
		.ops = &meson_cwk_pww_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_hdmi_pww_pwe_muwt.hw
		},
		.num_pawents = 1,
		/*
		 * Dispway diwectwy handwe hdmi pww wegistews ATM, we need
		 * NOCACHE to keep ouw view of the cwock as accuwate as possibwe
		 */
		.fwags = CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxw_hdmi_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 30,
			.width   = 1,
		},
		.m = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 0,
			.width   = 9,
		},
		.n = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 9,
			.width   = 5,
		},
		/*
		 * On gxw, thewe is a wegistew shift due to
		 * HHI_HDMI_PWW_CNTW1 which does not exist on gxbb,
		 * so we use the HHI_HDMI_PWW_CNTW2 define fwom GXBB
		 * instead which is defined at the same offset.
		 */
		.fwac = {
			.weg_off = HHI_HDMI_PWW_CNTW2,
			.shift   = 0,
			.width   = 10,
		},
		.w = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = HHI_HDMI_PWW_CNTW,
			.shift   = 28,
			.width   = 1,
		},
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_dco",
		.ops = &meson_cwk_pww_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
		/*
		 * Dispway diwectwy handwe hdmi pww wegistews ATM, we need
		 * NOCACHE to keep ouw view of the cwock as accuwate as possibwe
		 */
		.fwags = CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_hdmi_pww_od = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_HDMI_PWW_CNTW2,
		.shift = 16,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_od",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_hdmi_pww_dco.hw
		},
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_hdmi_pww_od2 = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_HDMI_PWW_CNTW2,
		.shift = 22,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_od2",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_hdmi_pww_od.hw
		},
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_hdmi_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_HDMI_PWW_CNTW2,
		.shift = 18,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_hdmi_pww_od2.hw
		},
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxw_hdmi_pww_od = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_HDMI_PWW_CNTW + 8,
		.shift = 21,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_od",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxw_hdmi_pww_dco.hw
		},
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxw_hdmi_pww_od2 = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_HDMI_PWW_CNTW + 8,
		.shift = 23,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww_od2",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxw_hdmi_pww_od.hw
		},
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxw_hdmi_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_HDMI_PWW_CNTW + 8,
		.shift = 19,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_pww",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxw_hdmi_pww_od2.hw
		},
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_sys_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = HHI_SYS_PWW_CNTW,
			.shift   = 30,
			.width   = 1,
		},
		.m = {
			.weg_off = HHI_SYS_PWW_CNTW,
			.shift   = 0,
			.width   = 9,
		},
		.n = {
			.weg_off = HHI_SYS_PWW_CNTW,
			.shift   = 9,
			.width   = 5,
		},
		.w = {
			.weg_off = HHI_SYS_PWW_CNTW,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = HHI_SYS_PWW_CNTW,
			.shift   = 29,
			.width   = 1,
		},
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sys_pww_dco",
		.ops = &meson_cwk_pww_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_sys_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_SYS_PWW_CNTW,
		.shift = 10,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sys_pww",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_sys_pww_dco.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct weg_sequence gxbb_gp0_init_wegs[] = {
	{ .weg = HHI_GP0_PWW_CNTW2,	.def = 0x69c80000 },
	{ .weg = HHI_GP0_PWW_CNTW3,	.def = 0x0a5590c4 },
	{ .weg = HHI_GP0_PWW_CNTW4,	.def = 0x0000500d },
};

static stwuct cwk_wegmap gxbb_gp0_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 30,
			.width   = 1,
		},
		.m = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 0,
			.width   = 9,
		},
		.n = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 9,
			.width   = 5,
		},
		.w = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 29,
			.width   = 1,
		},
		.tabwe = gxbb_gp0_pww_pawams_tabwe,
		.init_wegs = gxbb_gp0_init_wegs,
		.init_count = AWWAY_SIZE(gxbb_gp0_init_wegs),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gp0_pww_dco",
		.ops = &meson_cwk_pww_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static const stwuct weg_sequence gxw_gp0_init_wegs[] = {
	{ .weg = HHI_GP0_PWW_CNTW1,	.def = 0xc084b000 },
	{ .weg = HHI_GP0_PWW_CNTW2,	.def = 0xb75020be },
	{ .weg = HHI_GP0_PWW_CNTW3,	.def = 0x0a59a288 },
	{ .weg = HHI_GP0_PWW_CNTW4,	.def = 0xc000004d },
	{ .weg = HHI_GP0_PWW_CNTW5,	.def = 0x00078000 },
};

static stwuct cwk_wegmap gxw_gp0_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 30,
			.width   = 1,
		},
		.m = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 0,
			.width   = 9,
		},
		.n = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 9,
			.width   = 5,
		},
		.fwac = {
			.weg_off = HHI_GP0_PWW_CNTW1,
			.shift   = 0,
			.width   = 10,
		},
		.w = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = HHI_GP0_PWW_CNTW,
			.shift   = 29,
			.width   = 1,
		},
		.tabwe = gxw_gp0_pww_pawams_tabwe,
		.init_wegs = gxw_gp0_init_wegs,
		.init_count = AWWAY_SIZE(gxw_gp0_init_wegs),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gp0_pww_dco",
		.ops = &meson_cwk_pww_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_gp0_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_GP0_PWW_CNTW,
		.shift = 16,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gp0_pww",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			/*
			 * Note:
			 * GXW and GXBB have diffewent gp0_pww_dco (with
			 * diffewent stwuct cwk_hw). We fawwback to the gwobaw
			 * naming stwing mechanism so gp0_pww picks up the
			 * appwopwiate one.
			 */
			.name = "gp0_pww_dco",
			.index = -1,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_fixed_factow gxbb_fcwk_div2_div = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_fixed_pww.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_fcwk_div2 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPWW_CNTW6,
		.bit_idx = 27,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_fcwk_div2_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_IS_CWITICAW,
	},
};

static stwuct cwk_fixed_factow gxbb_fcwk_div3_div = {
	.muwt = 1,
	.div = 3,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div3_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_fcwk_div3 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPWW_CNTW6,
		.bit_idx = 28,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div3",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_fcwk_div3_div.hw
		},
		.num_pawents = 1,
		/*
		 * FIXME:
		 * This cwock, as fdiv2, is used by the SCPI FW and is wequiwed
		 * by the pwatfowm to opewate cowwectwy.
		 * Untiw the fowwowing condition awe met, we need this cwock to
		 * be mawked as cwiticaw:
		 * a) The SCPI genewic dwivew cwaims and enabwe aww the cwocks
		 *    it needs
		 * b) CCF has a cwock hand-off mechanism to make the suwe the
		 *    cwock stays on untiw the pwopew dwivew comes awong
		 */
		.fwags = CWK_IS_CWITICAW,
	},
};

static stwuct cwk_fixed_factow gxbb_fcwk_div4_div = {
	.muwt = 1,
	.div = 4,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div4_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_fcwk_div4 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPWW_CNTW6,
		.bit_idx = 29,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div4",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_fcwk_div4_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_fcwk_div5_div = {
	.muwt = 1,
	.div = 5,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div5_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_fcwk_div5 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPWW_CNTW6,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div5",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_fcwk_div5_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_fcwk_div7_div = {
	.muwt = 1,
	.div = 7,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div7_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_fcwk_div7 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPWW_CNTW6,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div7",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_fcwk_div7_div.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_mpww_pwediv = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_MPWW_CNTW5,
		.shift = 12,
		.width = 1,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww_pwediv",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_fixed_pww.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_mpww0_div = {
	.data = &(stwuct meson_cwk_mpww_data){
		.sdm = {
			.weg_off = HHI_MPWW_CNTW7,
			.shift   = 0,
			.width   = 14,
		},
		.sdm_en = {
			.weg_off = HHI_MPWW_CNTW,
			.shift   = 25,
			.width	 = 1,
		},
		.n2 = {
			.weg_off = HHI_MPWW_CNTW7,
			.shift   = 16,
			.width   = 9,
		},
		.wock = &meson_cwk_wock,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww0_div",
		.ops = &meson_cwk_mpww_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mpww_pwediv.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxw_mpww0_div = {
	.data = &(stwuct meson_cwk_mpww_data){
		.sdm = {
			.weg_off = HHI_MPWW_CNTW7,
			.shift   = 0,
			.width   = 14,
		},
		.sdm_en = {
			.weg_off = HHI_MPWW_CNTW7,
			.shift   = 15,
			.width	 = 1,
		},
		.n2 = {
			.weg_off = HHI_MPWW_CNTW7,
			.shift   = 16,
			.width   = 9,
		},
		.wock = &meson_cwk_wock,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww0_div",
		.ops = &meson_cwk_mpww_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mpww_pwediv.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_mpww0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPWW_CNTW7,
		.bit_idx = 14,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			/*
			 * Note:
			 * GXW and GXBB have diffewent SDM_EN wegistews. We
			 * fawwback to the gwobaw naming stwing mechanism so
			 * mpww0_div picks up the appwopwiate one.
			 */
			.name = "mpww0_div",
			.index = -1,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_mpww1_div = {
	.data = &(stwuct meson_cwk_mpww_data){
		.sdm = {
			.weg_off = HHI_MPWW_CNTW8,
			.shift   = 0,
			.width   = 14,
		},
		.sdm_en = {
			.weg_off = HHI_MPWW_CNTW8,
			.shift   = 15,
			.width	 = 1,
		},
		.n2 = {
			.weg_off = HHI_MPWW_CNTW8,
			.shift   = 16,
			.width   = 9,
		},
		.wock = &meson_cwk_wock,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww1_div",
		.ops = &meson_cwk_mpww_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mpww_pwediv.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_mpww1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPWW_CNTW8,
		.bit_idx = 14,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_mpww1_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_mpww2_div = {
	.data = &(stwuct meson_cwk_mpww_data){
		.sdm = {
			.weg_off = HHI_MPWW_CNTW9,
			.shift   = 0,
			.width   = 14,
		},
		.sdm_en = {
			.weg_off = HHI_MPWW_CNTW9,
			.shift   = 15,
			.width	 = 1,
		},
		.n2 = {
			.weg_off = HHI_MPWW_CNTW9,
			.shift   = 16,
			.width   = 9,
		},
		.wock = &meson_cwk_wock,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww2_div",
		.ops = &meson_cwk_mpww_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mpww_pwediv.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap gxbb_mpww2 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPWW_CNTW9,
		.bit_idx = 14,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpww2",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_mpww2_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static u32 mux_tabwe_cwk81[]	= { 0, 2, 3, 4, 5, 6, 7 };
static const stwuct cwk_pawent_data cwk81_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &gxbb_fcwk_div7.hw },
	{ .hw = &gxbb_mpww1.hw },
	{ .hw = &gxbb_mpww2.hw },
	{ .hw = &gxbb_fcwk_div4.hw },
	{ .hw = &gxbb_fcwk_div3.hw },
	{ .hw = &gxbb_fcwk_div5.hw },
};

static stwuct cwk_wegmap gxbb_mpeg_cwk_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_MPEG_CWK_CNTW,
		.mask = 0x7,
		.shift = 12,
		.tabwe = mux_tabwe_cwk81,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpeg_cwk_sew",
		.ops = &cwk_wegmap_mux_wo_ops,
		/*
		 * bits 14:12 sewects fwom 8 possibwe pawents:
		 * xtaw, 1'b0 (wtf), fcwk_div7, mpww_cwkout1, mpww_cwkout2,
		 * fcwk_div4, fcwk_div3, fcwk_div5
		 */
		.pawent_data = cwk81_pawent_data,
		.num_pawents = AWWAY_SIZE(cwk81_pawent_data),
	},
};

static stwuct cwk_wegmap gxbb_mpeg_cwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_MPEG_CWK_CNTW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mpeg_cwk_div",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mpeg_cwk_sew.hw
		},
		.num_pawents = 1,
	},
};

/* the mothew of dwagons gates */
static stwuct cwk_wegmap gxbb_cwk81 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MPEG_CWK_CNTW,
		.bit_idx = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cwk81",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mpeg_cwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_IS_CWITICAW,
	},
};

static stwuct cwk_wegmap gxbb_saw_adc_cwk_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_SAW_CWK_CNTW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "saw_adc_cwk_sew",
		.ops = &cwk_wegmap_mux_ops,
		/* NOTE: The datasheet doesn't wist the pawents fow bit 10 */
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", },
			{ .hw = &gxbb_cwk81.hw },
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap gxbb_saw_adc_cwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_SAW_CWK_CNTW,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "saw_adc_cwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_saw_adc_cwk_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_saw_adc_cwk = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_SAW_CWK_CNTW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "saw_adc_cwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_saw_adc_cwk_div.hw
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

static const stwuct cwk_pawent_data gxbb_mawi_0_1_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &gxbb_gp0_pww.hw },
	{ .hw = &gxbb_mpww2.hw },
	{ .hw = &gxbb_mpww1.hw },
	{ .hw = &gxbb_fcwk_div7.hw },
	{ .hw = &gxbb_fcwk_div4.hw },
	{ .hw = &gxbb_fcwk_div3.hw },
	{ .hw = &gxbb_fcwk_div5.hw },
};

static stwuct cwk_wegmap gxbb_mawi_0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_MAWI_CWK_CNTW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = gxbb_mawi_0_1_pawent_data,
		.num_pawents = 8,
		/*
		 * Don't wequest the pawent to change the wate because
		 * aww GPU fwequencies can be dewived fwom the fcwk_*
		 * cwocks and one speciaw GP0_PWW setting. This is
		 * impowtant because we need the MPWW cwocks fow audio.
		 */
		.fwags = 0,
	},
};

static stwuct cwk_wegmap gxbb_mawi_0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_MAWI_CWK_CNTW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mawi_0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_mawi_0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MAWI_CWK_CNTW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mawi_0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_GATE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_mawi_1_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_MAWI_CWK_CNTW,
		.mask = 0x7,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_1_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = gxbb_mawi_0_1_pawent_data,
		.num_pawents = 8,
		/*
		 * Don't wequest the pawent to change the wate because
		 * aww GPU fwequencies can be dewived fwom the fcwk_*
		 * cwocks and one speciaw GP0_PWW setting. This is
		 * impowtant because we need the MPWW cwocks fow audio.
		 */
		.fwags = 0,
	},
};

static stwuct cwk_wegmap gxbb_mawi_1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_MAWI_CWK_CNTW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mawi_1_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_mawi_1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_MAWI_CWK_CNTW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi_1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mawi_1_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_GATE | CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_hw *gxbb_mawi_pawent_hws[] = {
	&gxbb_mawi_0.hw,
	&gxbb_mawi_1.hw,
};

static stwuct cwk_wegmap gxbb_mawi = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_MAWI_CWK_CNTW,
		.mask = 1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "mawi",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = gxbb_mawi_pawent_hws,
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_cts_amcwk_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_AUD_CWK_CNTW,
		.mask = 0x3,
		.shift = 9,
		.tabwe = (u32[]){ 1, 2, 3 },
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_amcwk_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mpww0.hw,
			&gxbb_mpww1.hw,
			&gxbb_mpww2.hw,
		},
		.num_pawents = 3,
	},
};

static stwuct cwk_wegmap gxbb_cts_amcwk_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = HHI_AUD_CWK_CNTW,
		.shift = 0,
		.width = 8,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_amcwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_cts_amcwk_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_cts_amcwk = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_AUD_CWK_CNTW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_amcwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_cts_amcwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_cts_mcwk_i958_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_AUD_CWK_CNTW2,
		.mask = 0x3,
		.shift = 25,
		.tabwe = (u32[]){ 1, 2, 3 },
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cts_mcwk_i958_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_mpww0.hw,
			&gxbb_mpww1.hw,
			&gxbb_mpww2.hw,
		},
		.num_pawents = 3,
	},
};

static stwuct cwk_wegmap gxbb_cts_mcwk_i958_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_AUD_CWK_CNTW2,
		.shift = 16,
		.width = 8,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cts_mcwk_i958_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_cts_mcwk_i958_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_cts_mcwk_i958 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_AUD_CWK_CNTW2,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_mcwk_i958",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_cts_mcwk_i958_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_cts_i958 = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_AUD_CWK_CNTW2,
		.mask = 0x1,
		.shift = 27,
		},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_i958",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_cts_amcwk.hw,
			&gxbb_cts_mcwk_i958.hw
		},
		.num_pawents = 2,
		/*
		 *The pawent is specific to owigin of the audio data. Wet the
		 * consumew choose the appwopwiate pawent
		 */
		.fwags = CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
	},
};

static const stwuct cwk_pawent_data gxbb_32k_cwk_pawent_data[] = {
	{ .fw_name = "xtaw", },
	/*
	 * FIXME: This cwock is pwovided by the ao cwock contwowwew but the
	 * cwock is not yet pawt of the binding of this contwowwew, so stwing
	 * name must be use to set this pawent.
	 */
	{ .name = "cts_swow_oscin", .index = -1 },
	{ .hw = &gxbb_fcwk_div3.hw },
	{ .hw = &gxbb_fcwk_div5.hw },
};

static stwuct cwk_wegmap gxbb_32k_cwk_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_32K_CWK_CNTW,
		.mask = 0x3,
		.shift = 16,
		},
	.hw.init = &(stwuct cwk_init_data){
		.name = "32k_cwk_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = gxbb_32k_cwk_pawent_data,
		.num_pawents = 4,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_32k_cwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_32K_CWK_CNTW,
		.shift = 0,
		.width = 14,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "32k_cwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_32k_cwk_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_DIVIDEW_WOUND_CWOSEST,
	},
};

static stwuct cwk_wegmap gxbb_32k_cwk = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_32K_CWK_CNTW,
		.bit_idx = 15,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "32k_cwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_32k_cwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const stwuct cwk_pawent_data gxbb_sd_emmc_cwk0_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &gxbb_fcwk_div2.hw },
	{ .hw = &gxbb_fcwk_div3.hw },
	{ .hw = &gxbb_fcwk_div5.hw },
	{ .hw = &gxbb_fcwk_div7.hw },
	/*
	 * Fowwowing these pawent cwocks, we shouwd awso have had mpww2, mpww3
	 * and gp0_pww but these cwocks awe too pwecious to be used hewe. Aww
	 * the necessawy wates fow MMC and NAND opewation can be acheived using
	 * xtaw ow fcwk_div cwocks
	 */
};

/* SDIO cwock */
static stwuct cwk_wegmap gxbb_sd_emmc_a_cwk0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_SD_EMMC_CWK_CNTW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_a_cwk0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = gxbb_sd_emmc_cwk0_pawent_data,
		.num_pawents = AWWAY_SIZE(gxbb_sd_emmc_cwk0_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_sd_emmc_a_cwk0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_SD_EMMC_CWK_CNTW,
		.shift = 0,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_a_cwk0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_sd_emmc_a_cwk0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_sd_emmc_a_cwk0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_SD_EMMC_CWK_CNTW,
		.bit_idx = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_a_cwk0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_sd_emmc_a_cwk0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* SDcawd cwock */
static stwuct cwk_wegmap gxbb_sd_emmc_b_cwk0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_SD_EMMC_CWK_CNTW,
		.mask = 0x7,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_b_cwk0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = gxbb_sd_emmc_cwk0_pawent_data,
		.num_pawents = AWWAY_SIZE(gxbb_sd_emmc_cwk0_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_sd_emmc_b_cwk0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_SD_EMMC_CWK_CNTW,
		.shift = 16,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_b_cwk0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_sd_emmc_b_cwk0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_sd_emmc_b_cwk0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_SD_EMMC_CWK_CNTW,
		.bit_idx = 23,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_b_cwk0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_sd_emmc_b_cwk0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* EMMC/NAND cwock */
static stwuct cwk_wegmap gxbb_sd_emmc_c_cwk0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_NAND_CWK_CNTW,
		.mask = 0x7,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_c_cwk0_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = gxbb_sd_emmc_cwk0_pawent_data,
		.num_pawents = AWWAY_SIZE(gxbb_sd_emmc_cwk0_pawent_data),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_sd_emmc_c_cwk0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_NAND_CWK_CNTW,
		.shift = 0,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "sd_emmc_c_cwk0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_sd_emmc_c_cwk0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_sd_emmc_c_cwk0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_NAND_CWK_CNTW,
		.bit_idx = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "sd_emmc_c_cwk0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_sd_emmc_c_cwk0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* VPU Cwock */

static const stwuct cwk_hw *gxbb_vpu_pawent_hws[] = {
	&gxbb_fcwk_div4.hw,
	&gxbb_fcwk_div3.hw,
	&gxbb_fcwk_div5.hw,
	&gxbb_fcwk_div7.hw,
};

static stwuct cwk_wegmap gxbb_vpu_0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VPU_CWK_CNTW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_0_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bits 9:10 sewects fwom 4 possibwe pawents:
		 * fcwk_div4, fcwk_div3, fcwk_div5, fcwk_div7,
		 */
		.pawent_hws = gxbb_vpu_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_vpu_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vpu_0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_VPU_CWK_CNTW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vpu_0_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vpu_0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VPU_CWK_CNTW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vpu_0_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vpu_1_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VPU_CWK_CNTW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_1_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bits 25:26 sewects fwom 4 possibwe pawents:
		 * fcwk_div4, fcwk_div3, fcwk_div5, fcwk_div7,
		 */
		.pawent_hws = gxbb_vpu_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_vpu_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vpu_1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_VPU_CWK_CNTW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu_1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vpu_1_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vpu_1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VPU_CWK_CNTW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vpu_1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vpu_1_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vpu = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VPU_CWK_CNTW,
		.mask = 1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vpu",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bit 31 sewects fwom 2 possibwe pawents:
		 * vpu_0 ow vpu_1
		 */
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vpu_0.hw,
			&gxbb_vpu_1.hw
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_NO_WEPAWENT,
	},
};

/* VAPB Cwock */

static const stwuct cwk_hw *gxbb_vapb_pawent_hws[] = {
	&gxbb_fcwk_div4.hw,
	&gxbb_fcwk_div3.hw,
	&gxbb_fcwk_div5.hw,
	&gxbb_fcwk_div7.hw,
};

static stwuct cwk_wegmap gxbb_vapb_0_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VAPBCWK_CNTW,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_0_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bits 9:10 sewects fwom 4 possibwe pawents:
		 * fcwk_div4, fcwk_div3, fcwk_div5, fcwk_div7,
		 */
		.pawent_hws = gxbb_vapb_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_vapb_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vapb_0_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_VAPBCWK_CNTW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_0_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vapb_0_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vapb_0 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VAPBCWK_CNTW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vapb_0",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vapb_0_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vapb_1_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VAPBCWK_CNTW,
		.mask = 0x3,
		.shift = 25,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_1_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bits 25:26 sewects fwom 4 possibwe pawents:
		 * fcwk_div4, fcwk_div3, fcwk_div5, fcwk_div7,
		 */
		.pawent_hws = gxbb_vapb_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_vapb_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vapb_1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_VAPBCWK_CNTW,
		.shift = 16,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vapb_1_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vapb_1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VAPBCWK_CNTW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vapb_1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vapb_1_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vapb_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VAPBCWK_CNTW,
		.mask = 1,
		.shift = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vapb_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bit 31 sewects fwom 2 possibwe pawents:
		 * vapb_0 ow vapb_1
		 */
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vapb_0.hw,
			&gxbb_vapb_1.hw
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_NO_WEPAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vapb = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VAPBCWK_CNTW,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vapb",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vapb_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

/* Video Cwocks */

static stwuct cwk_wegmap gxbb_vid_pww_div = {
	.data = &(stwuct meson_vid_pww_div_data){
		.vaw = {
			.weg_off = HHI_VID_PWW_CWK_DIV,
			.shift   = 0,
			.width   = 15,
		},
		.sew = {
			.weg_off = HHI_VID_PWW_CWK_DIV,
			.shift   = 16,
			.width   = 2,
		},
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vid_pww_div",
		.ops = &meson_vid_pww_div_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			/*
			 * Note:
			 * GXW and GXBB have diffewent hdmi_pwws (with
			 * diffewent stwuct cwk_hw). We fawwback to the gwobaw
			 * naming stwing mechanism so vid_pww_div picks up the
			 * appwopwiate one.
			 */
			.name = "hdmi_pww",
			.index = -1,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static const stwuct cwk_pawent_data gxbb_vid_pww_pawent_data[] = {
	{ .hw = &gxbb_vid_pww_div.hw },
	/*
	 * Note:
	 * GXW and GXBB have diffewent hdmi_pwws (with
	 * diffewent stwuct cwk_hw). We fawwback to the gwobaw
	 * naming stwing mechanism so vid_pww_div picks up the
	 * appwopwiate one.
	 */
	{ .name = "hdmi_pww", .index = -1 },
};

static stwuct cwk_wegmap gxbb_vid_pww_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VID_PWW_CWK_DIV,
		.mask = 0x1,
		.shift = 18,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vid_pww_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bit 18 sewects fwom 2 possibwe pawents:
		 * vid_pww_div ow hdmi_pww
		 */
		.pawent_data = gxbb_vid_pww_pawent_data,
		.num_pawents = AWWAY_SIZE(gxbb_vid_pww_pawent_data),
		.fwags = CWK_SET_WATE_NO_WEPAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_vid_pww = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_PWW_CWK_DIV,
		.bit_idx = 19,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vid_pww",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vid_pww_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static const stwuct cwk_hw *gxbb_vcwk_pawent_hws[] = {
	&gxbb_vid_pww.hw,
	&gxbb_fcwk_div4.hw,
	&gxbb_fcwk_div3.hw,
	&gxbb_fcwk_div5.hw,
	&gxbb_vid_pww.hw,
	&gxbb_fcwk_div7.hw,
	&gxbb_mpww1.hw,
};

static stwuct cwk_wegmap gxbb_vcwk_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VID_CWK_CNTW,
		.mask = 0x7,
		.shift = 16,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bits 16:18 sewects fwom 8 possibwe pawents:
		 * vid_pww, fcwk_div4, fcwk_div3, fcwk_div5,
		 * vid_pww, fcwk_div7, mp1
		 */
		.pawent_hws = gxbb_vcwk_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_vcwk_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VIID_CWK_CNTW,
		.mask = 0x7,
		.shift = 16,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bits 16:18 sewects fwom 8 possibwe pawents:
		 * vid_pww, fcwk_div4, fcwk_div3, fcwk_div5,
		 * vid_pww, fcwk_div7, mp1
		 */
		.pawent_hws = gxbb_vcwk_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_vcwk_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_vcwk_input = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_DIV,
		.bit_idx = 16,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_input",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2_input = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VIID_CWK_DIV,
		.bit_idx = 16,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_input",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk2_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_VID_CWK_DIV,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk_input.hw
		},
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_VIID_CWK_DIV,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk2_input.hw
		},
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_vcwk = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW,
		.bit_idx = 19,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VIID_CWK_CNTW,
		.bit_idx = 19,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk2_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk_div1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk_div2_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW,
		.bit_idx = 1,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div2_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk_div4_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW,
		.bit_idx = 2,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div4_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk_div6_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW,
		.bit_idx = 3,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div6_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk_div12_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW,
		.bit_idx = 4,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk_div12_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2_div1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VIID_CWK_CNTW,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2_div2_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VIID_CWK_CNTW,
		.bit_idx = 1,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div2_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2_div4_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VIID_CWK_CNTW,
		.bit_idx = 2,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div4_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2_div6_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VIID_CWK_CNTW,
		.bit_idx = 3,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div6_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_vcwk2_div12_en = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VIID_CWK_CNTW,
		.bit_idx = 4,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vcwk2_div12_en",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_vcwk2.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_fixed_factow gxbb_vcwk_div2 = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div2",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk_div2_en.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_vcwk_div4 = {
	.muwt = 1,
	.div = 4,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div4",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk_div4_en.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_vcwk_div6 = {
	.muwt = 1,
	.div = 6,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div6",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk_div6_en.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_vcwk_div12 = {
	.muwt = 1,
	.div = 12,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk_div12",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk_div12_en.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_vcwk2_div2 = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div2",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk2_div2_en.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_vcwk2_div4 = {
	.muwt = 1,
	.div = 4,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div4",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk2_div4_en.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_vcwk2_div6 = {
	.muwt = 1,
	.div = 6,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div6",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk2_div6_en.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow gxbb_vcwk2_div12 = {
	.muwt = 1,
	.div = 12,
	.hw.init = &(stwuct cwk_init_data){
		.name = "vcwk2_div12",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vcwk2_div12_en.hw
		},
		.num_pawents = 1,
	},
};

static u32 mux_tabwe_cts_sew[] = { 0, 1, 2, 3, 4, 8, 9, 10, 11, 12 };
static const stwuct cwk_hw *gxbb_cts_pawent_hws[] = {
	&gxbb_vcwk_div1.hw,
	&gxbb_vcwk_div2.hw,
	&gxbb_vcwk_div4.hw,
	&gxbb_vcwk_div6.hw,
	&gxbb_vcwk_div12.hw,
	&gxbb_vcwk2_div1.hw,
	&gxbb_vcwk2_div2.hw,
	&gxbb_vcwk2_div4.hw,
	&gxbb_vcwk2_div6.hw,
	&gxbb_vcwk2_div12.hw,
};

static stwuct cwk_wegmap gxbb_cts_enci_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VID_CWK_DIV,
		.mask = 0xf,
		.shift = 28,
		.tabwe = mux_tabwe_cts_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_enci_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = gxbb_cts_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_cts_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_cts_encp_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VID_CWK_DIV,
		.mask = 0xf,
		.shift = 20,
		.tabwe = mux_tabwe_cts_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_encp_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = gxbb_cts_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_cts_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_cts_vdac_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VIID_CWK_DIV,
		.mask = 0xf,
		.shift = 28,
		.tabwe = mux_tabwe_cts_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_vdac_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = gxbb_cts_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_cts_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT | CWK_GET_WATE_NOCACHE,
	},
};

/* TOFIX: add suppowt fow cts_tcon */
static u32 mux_tabwe_hdmi_tx_sew[] = { 0, 1, 2, 3, 4, 8, 9, 10, 11, 12 };
static const stwuct cwk_hw *gxbb_cts_hdmi_tx_pawent_hws[] = {
	&gxbb_vcwk_div1.hw,
	&gxbb_vcwk_div2.hw,
	&gxbb_vcwk_div4.hw,
	&gxbb_vcwk_div6.hw,
	&gxbb_vcwk_div12.hw,
	&gxbb_vcwk2_div1.hw,
	&gxbb_vcwk2_div2.hw,
	&gxbb_vcwk2_div4.hw,
	&gxbb_vcwk2_div6.hw,
	&gxbb_vcwk2_div12.hw,
};

static stwuct cwk_wegmap gxbb_hdmi_tx_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_HDMI_CWK_CNTW,
		.mask = 0xf,
		.shift = 16,
		.tabwe = mux_tabwe_hdmi_tx_sew,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_tx_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bits 31:28 sewects fwom 12 possibwe pawents:
		 * vcwk_div1, vcwk_div2, vcwk_div4, vcwk_div6, vcwk_div12
		 * vcwk2_div1, vcwk2_div2, vcwk2_div4, vcwk2_div6, vcwk2_div12,
		 * cts_tcon
		 */
		.pawent_hws = gxbb_cts_hdmi_tx_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_cts_hdmi_tx_pawent_hws),
		.fwags = CWK_SET_WATE_NO_WEPAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_cts_enci = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW2,
		.bit_idx = 0,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cts_enci",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_cts_enci_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_cts_encp = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW2,
		.bit_idx = 2,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cts_encp",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_cts_encp_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_cts_vdac = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW2,
		.bit_idx = 4,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "cts_vdac",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_cts_vdac_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

static stwuct cwk_wegmap gxbb_hdmi_tx = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VID_CWK_CNTW2,
		.bit_idx = 5,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hdmi_tx",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_hdmi_tx_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

/* HDMI Cwocks */

static const stwuct cwk_pawent_data gxbb_hdmi_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &gxbb_fcwk_div4.hw },
	{ .hw = &gxbb_fcwk_div3.hw },
	{ .hw = &gxbb_fcwk_div5.hw },
};

static stwuct cwk_wegmap gxbb_hdmi_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_HDMI_CWK_CNTW,
		.mask = 0x3,
		.shift = 9,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = gxbb_hdmi_pawent_data,
		.num_pawents = AWWAY_SIZE(gxbb_hdmi_pawent_data),
		.fwags = CWK_SET_WATE_NO_WEPAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_hdmi_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_HDMI_CWK_CNTW,
		.shift = 0,
		.width = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hdmi_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_hdmi_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wegmap gxbb_hdmi = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_HDMI_CWK_CNTW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "hdmi",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &gxbb_hdmi_div.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
	},
};

/* VDEC cwocks */

static const stwuct cwk_hw *gxbb_vdec_pawent_hws[] = {
	&gxbb_fcwk_div4.hw,
	&gxbb_fcwk_div3.hw,
	&gxbb_fcwk_div5.hw,
	&gxbb_fcwk_div7.hw,
};

static stwuct cwk_wegmap gxbb_vdec_1_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VDEC_CWK_CNTW,
		.mask = 0x3,
		.shift = 9,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vdec_1_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = gxbb_vdec_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_vdec_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vdec_1_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_VDEC_CWK_CNTW,
		.shift = 0,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vdec_1_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vdec_1_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vdec_1 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VDEC_CWK_CNTW,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdec_1",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vdec_1_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vdec_hevc_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_VDEC2_CWK_CNTW,
		.mask = 0x3,
		.shift = 25,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vdec_hevc_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = gxbb_vdec_pawent_hws,
		.num_pawents = AWWAY_SIZE(gxbb_vdec_pawent_hws),
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vdec_hevc_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_VDEC2_CWK_CNTW,
		.shift = 16,
		.width = 7,
		.fwags = CWK_DIVIDEW_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "vdec_hevc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vdec_hevc_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_vdec_hevc = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_VDEC2_CWK_CNTW,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "vdec_hevc",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_vdec_hevc_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static u32 mux_tabwe_gen_cwk[]	= { 0, 4, 5, 6, 7, 8,
				    9, 10, 11, 13, 14, };
static const stwuct cwk_pawent_data gen_cwk_pawent_data[] = {
	{ .fw_name = "xtaw", },
	{ .hw = &gxbb_vdec_1.hw },
	{ .hw = &gxbb_vdec_hevc.hw },
	{ .hw = &gxbb_mpww0.hw },
	{ .hw = &gxbb_mpww1.hw },
	{ .hw = &gxbb_mpww2.hw },
	{ .hw = &gxbb_fcwk_div4.hw },
	{ .hw = &gxbb_fcwk_div3.hw },
	{ .hw = &gxbb_fcwk_div5.hw },
	{ .hw = &gxbb_fcwk_div7.hw },
	{ .hw = &gxbb_gp0_pww.hw },
};

static stwuct cwk_wegmap gxbb_gen_cwk_sew = {
	.data = &(stwuct cwk_wegmap_mux_data){
		.offset = HHI_GEN_CWK_CNTW,
		.mask = 0xf,
		.shift = 12,
		.tabwe = mux_tabwe_gen_cwk,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gen_cwk_sew",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * bits 15:12 sewects fwom 14 possibwe pawents:
		 * xtaw, [wtc_oscin_i], [sys_cpu_div16], [ddw_dpww_pt],
		 * vid_pww, vid2_pww (hevc), mpww0, mpww1, mpww2, fdiv4,
		 * fdiv3, fdiv5, [cts_msw_cwk], fdiv7, gp0_pww
		 */
		.pawent_data = gen_cwk_pawent_data,
		.num_pawents = AWWAY_SIZE(gen_cwk_pawent_data),
	},
};

static stwuct cwk_wegmap gxbb_gen_cwk_div = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = HHI_GEN_CWK_CNTW,
		.shift = 0,
		.width = 11,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gen_cwk_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_gen_cwk_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap gxbb_gen_cwk = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = HHI_GEN_CWK_CNTW,
		.bit_idx = 7,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "gen_cwk",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&gxbb_gen_cwk_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

#define MESON_GATE(_name, _weg, _bit) \
	MESON_PCWK(_name, _weg, _bit, &gxbb_cwk81.hw)

/* Evewything Ewse (EE) domain gates */
static MESON_GATE(gxbb_ddw, HHI_GCWK_MPEG0, 0);
static MESON_GATE(gxbb_dos, HHI_GCWK_MPEG0, 1);
static MESON_GATE(gxbb_isa, HHI_GCWK_MPEG0, 5);
static MESON_GATE(gxbb_pw301, HHI_GCWK_MPEG0, 6);
static MESON_GATE(gxbb_pewiphs, HHI_GCWK_MPEG0, 7);
static MESON_GATE(gxbb_spicc, HHI_GCWK_MPEG0, 8);
static MESON_GATE(gxbb_i2c, HHI_GCWK_MPEG0, 9);
static MESON_GATE(gxbb_sana, HHI_GCWK_MPEG0, 10);
static MESON_GATE(gxbb_smawt_cawd, HHI_GCWK_MPEG0, 11);
static MESON_GATE(gxbb_wng0, HHI_GCWK_MPEG0, 12);
static MESON_GATE(gxbb_uawt0, HHI_GCWK_MPEG0, 13);
static MESON_GATE(gxbb_sdhc, HHI_GCWK_MPEG0, 14);
static MESON_GATE(gxbb_stweam, HHI_GCWK_MPEG0, 15);
static MESON_GATE(gxbb_async_fifo, HHI_GCWK_MPEG0, 16);
static MESON_GATE(gxbb_sdio, HHI_GCWK_MPEG0, 17);
static MESON_GATE(gxbb_abuf, HHI_GCWK_MPEG0, 18);
static MESON_GATE(gxbb_hiu_iface, HHI_GCWK_MPEG0, 19);
static MESON_GATE(gxbb_assist_misc, HHI_GCWK_MPEG0, 23);
static MESON_GATE(gxbb_emmc_a, HHI_GCWK_MPEG0, 24);
static MESON_GATE(gxbb_emmc_b, HHI_GCWK_MPEG0, 25);
static MESON_GATE(gxbb_emmc_c, HHI_GCWK_MPEG0, 26);
static MESON_GATE(gxw_acodec, HHI_GCWK_MPEG0, 28);
static MESON_GATE(gxbb_spi, HHI_GCWK_MPEG0, 30);

static MESON_GATE(gxbb_i2s_spdif, HHI_GCWK_MPEG1, 2);
static MESON_GATE(gxbb_eth, HHI_GCWK_MPEG1, 3);
static MESON_GATE(gxbb_demux, HHI_GCWK_MPEG1, 4);
static MESON_GATE(gxbb_bwkmv, HHI_GCWK_MPEG1, 14);
static MESON_GATE(gxbb_aiu, HHI_GCWK_MPEG1, 15);
static MESON_GATE(gxbb_uawt1, HHI_GCWK_MPEG1, 16);
static MESON_GATE(gxbb_g2d, HHI_GCWK_MPEG1, 20);
static MESON_GATE(gxbb_usb0, HHI_GCWK_MPEG1, 21);
static MESON_GATE(gxbb_usb1, HHI_GCWK_MPEG1, 22);
static MESON_GATE(gxbb_weset, HHI_GCWK_MPEG1, 23);
static MESON_GATE(gxbb_nand, HHI_GCWK_MPEG1, 24);
static MESON_GATE(gxbb_dos_pawsew, HHI_GCWK_MPEG1, 25);
static MESON_GATE(gxbb_usb, HHI_GCWK_MPEG1, 26);
static MESON_GATE(gxbb_vdin1, HHI_GCWK_MPEG1, 28);
static MESON_GATE(gxbb_ahb_awb0, HHI_GCWK_MPEG1, 29);
static MESON_GATE(gxbb_efuse, HHI_GCWK_MPEG1, 30);
static MESON_GATE(gxbb_boot_wom, HHI_GCWK_MPEG1, 31);

static MESON_GATE(gxbb_ahb_data_bus, HHI_GCWK_MPEG2, 1);
static MESON_GATE(gxbb_ahb_ctww_bus, HHI_GCWK_MPEG2, 2);
static MESON_GATE(gxbb_hdmi_intw_sync, HHI_GCWK_MPEG2, 3);
static MESON_GATE(gxbb_hdmi_pcwk, HHI_GCWK_MPEG2, 4);
static MESON_GATE(gxbb_usb1_ddw_bwidge, HHI_GCWK_MPEG2, 8);
static MESON_GATE(gxbb_usb0_ddw_bwidge, HHI_GCWK_MPEG2, 9);
static MESON_GATE(gxbb_mmc_pcwk, HHI_GCWK_MPEG2, 11);
static MESON_GATE(gxbb_dvin, HHI_GCWK_MPEG2, 12);
static MESON_GATE(gxbb_uawt2, HHI_GCWK_MPEG2, 15);
static MESON_GATE(gxbb_saw_adc, HHI_GCWK_MPEG2, 22);
static MESON_GATE(gxbb_vpu_intw, HHI_GCWK_MPEG2, 25);
static MESON_GATE(gxbb_sec_ahb_ahb3_bwidge, HHI_GCWK_MPEG2, 26);
static MESON_GATE(gxbb_cwk81_a53, HHI_GCWK_MPEG2, 29);

static MESON_GATE(gxbb_vcwk2_venci0, HHI_GCWK_OTHEW, 1);
static MESON_GATE(gxbb_vcwk2_venci1, HHI_GCWK_OTHEW, 2);
static MESON_GATE(gxbb_vcwk2_vencp0, HHI_GCWK_OTHEW, 3);
static MESON_GATE(gxbb_vcwk2_vencp1, HHI_GCWK_OTHEW, 4);
static MESON_GATE(gxbb_gcwk_venci_int0, HHI_GCWK_OTHEW, 8);
static MESON_GATE(gxbb_gcwk_vencp_int, HHI_GCWK_OTHEW, 9);
static MESON_GATE(gxbb_dac_cwk, HHI_GCWK_OTHEW, 10);
static MESON_GATE(gxbb_aocwk_gate, HHI_GCWK_OTHEW, 14);
static MESON_GATE(gxbb_iec958_gate, HHI_GCWK_OTHEW, 16);
static MESON_GATE(gxbb_enc480p, HHI_GCWK_OTHEW, 20);
static MESON_GATE(gxbb_wng1, HHI_GCWK_OTHEW, 21);
static MESON_GATE(gxbb_gcwk_venci_int1, HHI_GCWK_OTHEW, 22);
static MESON_GATE(gxbb_vcwk2_vencwmcc, HHI_GCWK_OTHEW, 24);
static MESON_GATE(gxbb_vcwk2_vencw, HHI_GCWK_OTHEW, 25);
static MESON_GATE(gxbb_vcwk_othew, HHI_GCWK_OTHEW, 26);
static MESON_GATE(gxbb_edp, HHI_GCWK_OTHEW, 31);

/* Awways On (AO) domain gates */

static MESON_GATE(gxbb_ao_media_cpu, HHI_GCWK_AO, 0);
static MESON_GATE(gxbb_ao_ahb_swam, HHI_GCWK_AO, 1);
static MESON_GATE(gxbb_ao_ahb_bus, HHI_GCWK_AO, 2);
static MESON_GATE(gxbb_ao_iface, HHI_GCWK_AO, 3);
static MESON_GATE(gxbb_ao_i2c, HHI_GCWK_AO, 4);

/* AIU gates */
static MESON_PCWK(gxbb_aiu_gwue, HHI_GCWK_MPEG1, 6, &gxbb_aiu.hw);
static MESON_PCWK(gxbb_iec958, HHI_GCWK_MPEG1, 7, &gxbb_aiu_gwue.hw);
static MESON_PCWK(gxbb_i2s_out, HHI_GCWK_MPEG1, 8, &gxbb_aiu_gwue.hw);
static MESON_PCWK(gxbb_amcwk, HHI_GCWK_MPEG1, 9, &gxbb_aiu_gwue.hw);
static MESON_PCWK(gxbb_aififo2, HHI_GCWK_MPEG1, 10, &gxbb_aiu_gwue.hw);
static MESON_PCWK(gxbb_mixew, HHI_GCWK_MPEG1, 11, &gxbb_aiu_gwue.hw);
static MESON_PCWK(gxbb_mixew_iface, HHI_GCWK_MPEG1, 12, &gxbb_aiu_gwue.hw);
static MESON_PCWK(gxbb_adc, HHI_GCWK_MPEG1, 13, &gxbb_aiu_gwue.hw);

/* Awway of aww cwocks pwovided by this pwovidew */

static stwuct cwk_hw *gxbb_hw_cwks[] = {
	[CWKID_SYS_PWW]		    = &gxbb_sys_pww.hw,
	[CWKID_HDMI_PWW]	    = &gxbb_hdmi_pww.hw,
	[CWKID_FIXED_PWW]	    = &gxbb_fixed_pww.hw,
	[CWKID_FCWK_DIV2]	    = &gxbb_fcwk_div2.hw,
	[CWKID_FCWK_DIV3]	    = &gxbb_fcwk_div3.hw,
	[CWKID_FCWK_DIV4]	    = &gxbb_fcwk_div4.hw,
	[CWKID_FCWK_DIV5]	    = &gxbb_fcwk_div5.hw,
	[CWKID_FCWK_DIV7]	    = &gxbb_fcwk_div7.hw,
	[CWKID_GP0_PWW]		    = &gxbb_gp0_pww.hw,
	[CWKID_MPEG_SEW]	    = &gxbb_mpeg_cwk_sew.hw,
	[CWKID_MPEG_DIV]	    = &gxbb_mpeg_cwk_div.hw,
	[CWKID_CWK81]		    = &gxbb_cwk81.hw,
	[CWKID_MPWW0]		    = &gxbb_mpww0.hw,
	[CWKID_MPWW1]		    = &gxbb_mpww1.hw,
	[CWKID_MPWW2]		    = &gxbb_mpww2.hw,
	[CWKID_DDW]		    = &gxbb_ddw.hw,
	[CWKID_DOS]		    = &gxbb_dos.hw,
	[CWKID_ISA]		    = &gxbb_isa.hw,
	[CWKID_PW301]		    = &gxbb_pw301.hw,
	[CWKID_PEWIPHS]		    = &gxbb_pewiphs.hw,
	[CWKID_SPICC]		    = &gxbb_spicc.hw,
	[CWKID_I2C]		    = &gxbb_i2c.hw,
	[CWKID_SAW_ADC]		    = &gxbb_saw_adc.hw,
	[CWKID_SMAWT_CAWD]	    = &gxbb_smawt_cawd.hw,
	[CWKID_WNG0]		    = &gxbb_wng0.hw,
	[CWKID_UAWT0]		    = &gxbb_uawt0.hw,
	[CWKID_SDHC]		    = &gxbb_sdhc.hw,
	[CWKID_STWEAM]		    = &gxbb_stweam.hw,
	[CWKID_ASYNC_FIFO]	    = &gxbb_async_fifo.hw,
	[CWKID_SDIO]		    = &gxbb_sdio.hw,
	[CWKID_ABUF]		    = &gxbb_abuf.hw,
	[CWKID_HIU_IFACE]	    = &gxbb_hiu_iface.hw,
	[CWKID_ASSIST_MISC]	    = &gxbb_assist_misc.hw,
	[CWKID_SPI]		    = &gxbb_spi.hw,
	[CWKID_I2S_SPDIF]	    = &gxbb_i2s_spdif.hw,
	[CWKID_ETH]		    = &gxbb_eth.hw,
	[CWKID_DEMUX]		    = &gxbb_demux.hw,
	[CWKID_AIU_GWUE]	    = &gxbb_aiu_gwue.hw,
	[CWKID_IEC958]		    = &gxbb_iec958.hw,
	[CWKID_I2S_OUT]		    = &gxbb_i2s_out.hw,
	[CWKID_AMCWK]		    = &gxbb_amcwk.hw,
	[CWKID_AIFIFO2]		    = &gxbb_aififo2.hw,
	[CWKID_MIXEW]		    = &gxbb_mixew.hw,
	[CWKID_MIXEW_IFACE]	    = &gxbb_mixew_iface.hw,
	[CWKID_ADC]		    = &gxbb_adc.hw,
	[CWKID_BWKMV]		    = &gxbb_bwkmv.hw,
	[CWKID_AIU]		    = &gxbb_aiu.hw,
	[CWKID_UAWT1]		    = &gxbb_uawt1.hw,
	[CWKID_G2D]		    = &gxbb_g2d.hw,
	[CWKID_USB0]		    = &gxbb_usb0.hw,
	[CWKID_USB1]		    = &gxbb_usb1.hw,
	[CWKID_WESET]		    = &gxbb_weset.hw,
	[CWKID_NAND]		    = &gxbb_nand.hw,
	[CWKID_DOS_PAWSEW]	    = &gxbb_dos_pawsew.hw,
	[CWKID_USB]		    = &gxbb_usb.hw,
	[CWKID_VDIN1]		    = &gxbb_vdin1.hw,
	[CWKID_AHB_AWB0]	    = &gxbb_ahb_awb0.hw,
	[CWKID_EFUSE]		    = &gxbb_efuse.hw,
	[CWKID_BOOT_WOM]	    = &gxbb_boot_wom.hw,
	[CWKID_AHB_DATA_BUS]	    = &gxbb_ahb_data_bus.hw,
	[CWKID_AHB_CTWW_BUS]	    = &gxbb_ahb_ctww_bus.hw,
	[CWKID_HDMI_INTW_SYNC]	    = &gxbb_hdmi_intw_sync.hw,
	[CWKID_HDMI_PCWK]	    = &gxbb_hdmi_pcwk.hw,
	[CWKID_USB1_DDW_BWIDGE]	    = &gxbb_usb1_ddw_bwidge.hw,
	[CWKID_USB0_DDW_BWIDGE]	    = &gxbb_usb0_ddw_bwidge.hw,
	[CWKID_MMC_PCWK]	    = &gxbb_mmc_pcwk.hw,
	[CWKID_DVIN]		    = &gxbb_dvin.hw,
	[CWKID_UAWT2]		    = &gxbb_uawt2.hw,
	[CWKID_SANA]		    = &gxbb_sana.hw,
	[CWKID_VPU_INTW]	    = &gxbb_vpu_intw.hw,
	[CWKID_SEC_AHB_AHB3_BWIDGE] = &gxbb_sec_ahb_ahb3_bwidge.hw,
	[CWKID_CWK81_A53]	    = &gxbb_cwk81_a53.hw,
	[CWKID_VCWK2_VENCI0]	    = &gxbb_vcwk2_venci0.hw,
	[CWKID_VCWK2_VENCI1]	    = &gxbb_vcwk2_venci1.hw,
	[CWKID_VCWK2_VENCP0]	    = &gxbb_vcwk2_vencp0.hw,
	[CWKID_VCWK2_VENCP1]	    = &gxbb_vcwk2_vencp1.hw,
	[CWKID_GCWK_VENCI_INT0]	    = &gxbb_gcwk_venci_int0.hw,
	[CWKID_GCWK_VENCI_INT]	    = &gxbb_gcwk_vencp_int.hw,
	[CWKID_DAC_CWK]		    = &gxbb_dac_cwk.hw,
	[CWKID_AOCWK_GATE]	    = &gxbb_aocwk_gate.hw,
	[CWKID_IEC958_GATE]	    = &gxbb_iec958_gate.hw,
	[CWKID_ENC480P]		    = &gxbb_enc480p.hw,
	[CWKID_WNG1]		    = &gxbb_wng1.hw,
	[CWKID_GCWK_VENCI_INT1]	    = &gxbb_gcwk_venci_int1.hw,
	[CWKID_VCWK2_VENCWMCC]	    = &gxbb_vcwk2_vencwmcc.hw,
	[CWKID_VCWK2_VENCW]	    = &gxbb_vcwk2_vencw.hw,
	[CWKID_VCWK_OTHEW]	    = &gxbb_vcwk_othew.hw,
	[CWKID_EDP]		    = &gxbb_edp.hw,
	[CWKID_AO_MEDIA_CPU]	    = &gxbb_ao_media_cpu.hw,
	[CWKID_AO_AHB_SWAM]	    = &gxbb_ao_ahb_swam.hw,
	[CWKID_AO_AHB_BUS]	    = &gxbb_ao_ahb_bus.hw,
	[CWKID_AO_IFACE]	    = &gxbb_ao_iface.hw,
	[CWKID_AO_I2C]		    = &gxbb_ao_i2c.hw,
	[CWKID_SD_EMMC_A]	    = &gxbb_emmc_a.hw,
	[CWKID_SD_EMMC_B]	    = &gxbb_emmc_b.hw,
	[CWKID_SD_EMMC_C]	    = &gxbb_emmc_c.hw,
	[CWKID_SAW_ADC_CWK]	    = &gxbb_saw_adc_cwk.hw,
	[CWKID_SAW_ADC_SEW]	    = &gxbb_saw_adc_cwk_sew.hw,
	[CWKID_SAW_ADC_DIV]	    = &gxbb_saw_adc_cwk_div.hw,
	[CWKID_MAWI_0_SEW]	    = &gxbb_mawi_0_sew.hw,
	[CWKID_MAWI_0_DIV]	    = &gxbb_mawi_0_div.hw,
	[CWKID_MAWI_0]		    = &gxbb_mawi_0.hw,
	[CWKID_MAWI_1_SEW]	    = &gxbb_mawi_1_sew.hw,
	[CWKID_MAWI_1_DIV]	    = &gxbb_mawi_1_div.hw,
	[CWKID_MAWI_1]		    = &gxbb_mawi_1.hw,
	[CWKID_MAWI]		    = &gxbb_mawi.hw,
	[CWKID_CTS_AMCWK]	    = &gxbb_cts_amcwk.hw,
	[CWKID_CTS_AMCWK_SEW]	    = &gxbb_cts_amcwk_sew.hw,
	[CWKID_CTS_AMCWK_DIV]	    = &gxbb_cts_amcwk_div.hw,
	[CWKID_CTS_MCWK_I958]	    = &gxbb_cts_mcwk_i958.hw,
	[CWKID_CTS_MCWK_I958_SEW]   = &gxbb_cts_mcwk_i958_sew.hw,
	[CWKID_CTS_MCWK_I958_DIV]   = &gxbb_cts_mcwk_i958_div.hw,
	[CWKID_CTS_I958]	    = &gxbb_cts_i958.hw,
	[CWKID_32K_CWK]		    = &gxbb_32k_cwk.hw,
	[CWKID_32K_CWK_SEW]	    = &gxbb_32k_cwk_sew.hw,
	[CWKID_32K_CWK_DIV]	    = &gxbb_32k_cwk_div.hw,
	[CWKID_SD_EMMC_A_CWK0_SEW]  = &gxbb_sd_emmc_a_cwk0_sew.hw,
	[CWKID_SD_EMMC_A_CWK0_DIV]  = &gxbb_sd_emmc_a_cwk0_div.hw,
	[CWKID_SD_EMMC_A_CWK0]	    = &gxbb_sd_emmc_a_cwk0.hw,
	[CWKID_SD_EMMC_B_CWK0_SEW]  = &gxbb_sd_emmc_b_cwk0_sew.hw,
	[CWKID_SD_EMMC_B_CWK0_DIV]  = &gxbb_sd_emmc_b_cwk0_div.hw,
	[CWKID_SD_EMMC_B_CWK0]	    = &gxbb_sd_emmc_b_cwk0.hw,
	[CWKID_SD_EMMC_C_CWK0_SEW]  = &gxbb_sd_emmc_c_cwk0_sew.hw,
	[CWKID_SD_EMMC_C_CWK0_DIV]  = &gxbb_sd_emmc_c_cwk0_div.hw,
	[CWKID_SD_EMMC_C_CWK0]	    = &gxbb_sd_emmc_c_cwk0.hw,
	[CWKID_VPU_0_SEW]	    = &gxbb_vpu_0_sew.hw,
	[CWKID_VPU_0_DIV]	    = &gxbb_vpu_0_div.hw,
	[CWKID_VPU_0]		    = &gxbb_vpu_0.hw,
	[CWKID_VPU_1_SEW]	    = &gxbb_vpu_1_sew.hw,
	[CWKID_VPU_1_DIV]	    = &gxbb_vpu_1_div.hw,
	[CWKID_VPU_1]		    = &gxbb_vpu_1.hw,
	[CWKID_VPU]		    = &gxbb_vpu.hw,
	[CWKID_VAPB_0_SEW]	    = &gxbb_vapb_0_sew.hw,
	[CWKID_VAPB_0_DIV]	    = &gxbb_vapb_0_div.hw,
	[CWKID_VAPB_0]		    = &gxbb_vapb_0.hw,
	[CWKID_VAPB_1_SEW]	    = &gxbb_vapb_1_sew.hw,
	[CWKID_VAPB_1_DIV]	    = &gxbb_vapb_1_div.hw,
	[CWKID_VAPB_1]		    = &gxbb_vapb_1.hw,
	[CWKID_VAPB_SEW]	    = &gxbb_vapb_sew.hw,
	[CWKID_VAPB]		    = &gxbb_vapb.hw,
	[CWKID_HDMI_PWW_PWE_MUWT]   = &gxbb_hdmi_pww_pwe_muwt.hw,
	[CWKID_MPWW0_DIV]	    = &gxbb_mpww0_div.hw,
	[CWKID_MPWW1_DIV]	    = &gxbb_mpww1_div.hw,
	[CWKID_MPWW2_DIV]	    = &gxbb_mpww2_div.hw,
	[CWKID_MPWW_PWEDIV]	    = &gxbb_mpww_pwediv.hw,
	[CWKID_FCWK_DIV2_DIV]	    = &gxbb_fcwk_div2_div.hw,
	[CWKID_FCWK_DIV3_DIV]	    = &gxbb_fcwk_div3_div.hw,
	[CWKID_FCWK_DIV4_DIV]	    = &gxbb_fcwk_div4_div.hw,
	[CWKID_FCWK_DIV5_DIV]	    = &gxbb_fcwk_div5_div.hw,
	[CWKID_FCWK_DIV7_DIV]	    = &gxbb_fcwk_div7_div.hw,
	[CWKID_VDEC_1_SEW]	    = &gxbb_vdec_1_sew.hw,
	[CWKID_VDEC_1_DIV]	    = &gxbb_vdec_1_div.hw,
	[CWKID_VDEC_1]		    = &gxbb_vdec_1.hw,
	[CWKID_VDEC_HEVC_SEW]	    = &gxbb_vdec_hevc_sew.hw,
	[CWKID_VDEC_HEVC_DIV]	    = &gxbb_vdec_hevc_div.hw,
	[CWKID_VDEC_HEVC]	    = &gxbb_vdec_hevc.hw,
	[CWKID_GEN_CWK_SEW]	    = &gxbb_gen_cwk_sew.hw,
	[CWKID_GEN_CWK_DIV]	    = &gxbb_gen_cwk_div.hw,
	[CWKID_GEN_CWK]		    = &gxbb_gen_cwk.hw,
	[CWKID_FIXED_PWW_DCO]	    = &gxbb_fixed_pww_dco.hw,
	[CWKID_HDMI_PWW_DCO]	    = &gxbb_hdmi_pww_dco.hw,
	[CWKID_HDMI_PWW_OD]	    = &gxbb_hdmi_pww_od.hw,
	[CWKID_HDMI_PWW_OD2]	    = &gxbb_hdmi_pww_od2.hw,
	[CWKID_SYS_PWW_DCO]	    = &gxbb_sys_pww_dco.hw,
	[CWKID_GP0_PWW_DCO]	    = &gxbb_gp0_pww_dco.hw,
	[CWKID_VID_PWW_DIV]	    = &gxbb_vid_pww_div.hw,
	[CWKID_VID_PWW_SEW]	    = &gxbb_vid_pww_sew.hw,
	[CWKID_VID_PWW]		    = &gxbb_vid_pww.hw,
	[CWKID_VCWK_SEW]	    = &gxbb_vcwk_sew.hw,
	[CWKID_VCWK2_SEW]	    = &gxbb_vcwk2_sew.hw,
	[CWKID_VCWK_INPUT]	    = &gxbb_vcwk_input.hw,
	[CWKID_VCWK2_INPUT]	    = &gxbb_vcwk2_input.hw,
	[CWKID_VCWK_DIV]	    = &gxbb_vcwk_div.hw,
	[CWKID_VCWK2_DIV]	    = &gxbb_vcwk2_div.hw,
	[CWKID_VCWK]		    = &gxbb_vcwk.hw,
	[CWKID_VCWK2]		    = &gxbb_vcwk2.hw,
	[CWKID_VCWK_DIV1]	    = &gxbb_vcwk_div1.hw,
	[CWKID_VCWK_DIV2_EN]	    = &gxbb_vcwk_div2_en.hw,
	[CWKID_VCWK_DIV2]	    = &gxbb_vcwk_div2.hw,
	[CWKID_VCWK_DIV4_EN]	    = &gxbb_vcwk_div4_en.hw,
	[CWKID_VCWK_DIV4]	    = &gxbb_vcwk_div4.hw,
	[CWKID_VCWK_DIV6_EN]	    = &gxbb_vcwk_div6_en.hw,
	[CWKID_VCWK_DIV6]	    = &gxbb_vcwk_div6.hw,
	[CWKID_VCWK_DIV12_EN]	    = &gxbb_vcwk_div12_en.hw,
	[CWKID_VCWK_DIV12]	    = &gxbb_vcwk_div12.hw,
	[CWKID_VCWK2_DIV1]	    = &gxbb_vcwk2_div1.hw,
	[CWKID_VCWK2_DIV2_EN]	    = &gxbb_vcwk2_div2_en.hw,
	[CWKID_VCWK2_DIV2]	    = &gxbb_vcwk2_div2.hw,
	[CWKID_VCWK2_DIV4_EN]	    = &gxbb_vcwk2_div4_en.hw,
	[CWKID_VCWK2_DIV4]	    = &gxbb_vcwk2_div4.hw,
	[CWKID_VCWK2_DIV6_EN]	    = &gxbb_vcwk2_div6_en.hw,
	[CWKID_VCWK2_DIV6]	    = &gxbb_vcwk2_div6.hw,
	[CWKID_VCWK2_DIV12_EN]	    = &gxbb_vcwk2_div12_en.hw,
	[CWKID_VCWK2_DIV12]	    = &gxbb_vcwk2_div12.hw,
	[CWKID_CTS_ENCI_SEW]	    = &gxbb_cts_enci_sew.hw,
	[CWKID_CTS_ENCP_SEW]	    = &gxbb_cts_encp_sew.hw,
	[CWKID_CTS_VDAC_SEW]	    = &gxbb_cts_vdac_sew.hw,
	[CWKID_HDMI_TX_SEW]	    = &gxbb_hdmi_tx_sew.hw,
	[CWKID_CTS_ENCI]	    = &gxbb_cts_enci.hw,
	[CWKID_CTS_ENCP]	    = &gxbb_cts_encp.hw,
	[CWKID_CTS_VDAC]	    = &gxbb_cts_vdac.hw,
	[CWKID_HDMI_TX]		    = &gxbb_hdmi_tx.hw,
	[CWKID_HDMI_SEW]	    = &gxbb_hdmi_sew.hw,
	[CWKID_HDMI_DIV]	    = &gxbb_hdmi_div.hw,
	[CWKID_HDMI]		    = &gxbb_hdmi.hw,
};

static stwuct cwk_hw *gxw_hw_cwks[] = {
	[CWKID_SYS_PWW]		    = &gxbb_sys_pww.hw,
	[CWKID_HDMI_PWW]	    = &gxw_hdmi_pww.hw,
	[CWKID_FIXED_PWW]	    = &gxbb_fixed_pww.hw,
	[CWKID_FCWK_DIV2]	    = &gxbb_fcwk_div2.hw,
	[CWKID_FCWK_DIV3]	    = &gxbb_fcwk_div3.hw,
	[CWKID_FCWK_DIV4]	    = &gxbb_fcwk_div4.hw,
	[CWKID_FCWK_DIV5]	    = &gxbb_fcwk_div5.hw,
	[CWKID_FCWK_DIV7]	    = &gxbb_fcwk_div7.hw,
	[CWKID_GP0_PWW]		    = &gxbb_gp0_pww.hw,
	[CWKID_MPEG_SEW]	    = &gxbb_mpeg_cwk_sew.hw,
	[CWKID_MPEG_DIV]	    = &gxbb_mpeg_cwk_div.hw,
	[CWKID_CWK81]		    = &gxbb_cwk81.hw,
	[CWKID_MPWW0]		    = &gxbb_mpww0.hw,
	[CWKID_MPWW1]		    = &gxbb_mpww1.hw,
	[CWKID_MPWW2]		    = &gxbb_mpww2.hw,
	[CWKID_DDW]		    = &gxbb_ddw.hw,
	[CWKID_DOS]		    = &gxbb_dos.hw,
	[CWKID_ISA]		    = &gxbb_isa.hw,
	[CWKID_PW301]		    = &gxbb_pw301.hw,
	[CWKID_PEWIPHS]		    = &gxbb_pewiphs.hw,
	[CWKID_SPICC]		    = &gxbb_spicc.hw,
	[CWKID_I2C]		    = &gxbb_i2c.hw,
	[CWKID_SAW_ADC]		    = &gxbb_saw_adc.hw,
	[CWKID_SMAWT_CAWD]	    = &gxbb_smawt_cawd.hw,
	[CWKID_WNG0]		    = &gxbb_wng0.hw,
	[CWKID_UAWT0]		    = &gxbb_uawt0.hw,
	[CWKID_SDHC]		    = &gxbb_sdhc.hw,
	[CWKID_STWEAM]		    = &gxbb_stweam.hw,
	[CWKID_ASYNC_FIFO]	    = &gxbb_async_fifo.hw,
	[CWKID_SDIO]		    = &gxbb_sdio.hw,
	[CWKID_ABUF]		    = &gxbb_abuf.hw,
	[CWKID_HIU_IFACE]	    = &gxbb_hiu_iface.hw,
	[CWKID_ASSIST_MISC]	    = &gxbb_assist_misc.hw,
	[CWKID_SPI]		    = &gxbb_spi.hw,
	[CWKID_I2S_SPDIF]	    = &gxbb_i2s_spdif.hw,
	[CWKID_ETH]		    = &gxbb_eth.hw,
	[CWKID_DEMUX]		    = &gxbb_demux.hw,
	[CWKID_AIU_GWUE]	    = &gxbb_aiu_gwue.hw,
	[CWKID_IEC958]		    = &gxbb_iec958.hw,
	[CWKID_I2S_OUT]		    = &gxbb_i2s_out.hw,
	[CWKID_AMCWK]		    = &gxbb_amcwk.hw,
	[CWKID_AIFIFO2]		    = &gxbb_aififo2.hw,
	[CWKID_MIXEW]		    = &gxbb_mixew.hw,
	[CWKID_MIXEW_IFACE]	    = &gxbb_mixew_iface.hw,
	[CWKID_ADC]		    = &gxbb_adc.hw,
	[CWKID_BWKMV]		    = &gxbb_bwkmv.hw,
	[CWKID_AIU]		    = &gxbb_aiu.hw,
	[CWKID_UAWT1]		    = &gxbb_uawt1.hw,
	[CWKID_G2D]		    = &gxbb_g2d.hw,
	[CWKID_USB0]		    = &gxbb_usb0.hw,
	[CWKID_USB1]		    = &gxbb_usb1.hw,
	[CWKID_WESET]		    = &gxbb_weset.hw,
	[CWKID_NAND]		    = &gxbb_nand.hw,
	[CWKID_DOS_PAWSEW]	    = &gxbb_dos_pawsew.hw,
	[CWKID_USB]		    = &gxbb_usb.hw,
	[CWKID_VDIN1]		    = &gxbb_vdin1.hw,
	[CWKID_AHB_AWB0]	    = &gxbb_ahb_awb0.hw,
	[CWKID_EFUSE]		    = &gxbb_efuse.hw,
	[CWKID_BOOT_WOM]	    = &gxbb_boot_wom.hw,
	[CWKID_AHB_DATA_BUS]	    = &gxbb_ahb_data_bus.hw,
	[CWKID_AHB_CTWW_BUS]	    = &gxbb_ahb_ctww_bus.hw,
	[CWKID_HDMI_INTW_SYNC]	    = &gxbb_hdmi_intw_sync.hw,
	[CWKID_HDMI_PCWK]	    = &gxbb_hdmi_pcwk.hw,
	[CWKID_USB1_DDW_BWIDGE]	    = &gxbb_usb1_ddw_bwidge.hw,
	[CWKID_USB0_DDW_BWIDGE]	    = &gxbb_usb0_ddw_bwidge.hw,
	[CWKID_MMC_PCWK]	    = &gxbb_mmc_pcwk.hw,
	[CWKID_DVIN]		    = &gxbb_dvin.hw,
	[CWKID_UAWT2]		    = &gxbb_uawt2.hw,
	[CWKID_SANA]		    = &gxbb_sana.hw,
	[CWKID_VPU_INTW]	    = &gxbb_vpu_intw.hw,
	[CWKID_SEC_AHB_AHB3_BWIDGE] = &gxbb_sec_ahb_ahb3_bwidge.hw,
	[CWKID_CWK81_A53]	    = &gxbb_cwk81_a53.hw,
	[CWKID_VCWK2_VENCI0]	    = &gxbb_vcwk2_venci0.hw,
	[CWKID_VCWK2_VENCI1]	    = &gxbb_vcwk2_venci1.hw,
	[CWKID_VCWK2_VENCP0]	    = &gxbb_vcwk2_vencp0.hw,
	[CWKID_VCWK2_VENCP1]	    = &gxbb_vcwk2_vencp1.hw,
	[CWKID_GCWK_VENCI_INT0]	    = &gxbb_gcwk_venci_int0.hw,
	[CWKID_GCWK_VENCI_INT]	    = &gxbb_gcwk_vencp_int.hw,
	[CWKID_DAC_CWK]		    = &gxbb_dac_cwk.hw,
	[CWKID_AOCWK_GATE]	    = &gxbb_aocwk_gate.hw,
	[CWKID_IEC958_GATE]	    = &gxbb_iec958_gate.hw,
	[CWKID_ENC480P]		    = &gxbb_enc480p.hw,
	[CWKID_WNG1]		    = &gxbb_wng1.hw,
	[CWKID_GCWK_VENCI_INT1]	    = &gxbb_gcwk_venci_int1.hw,
	[CWKID_VCWK2_VENCWMCC]	    = &gxbb_vcwk2_vencwmcc.hw,
	[CWKID_VCWK2_VENCW]	    = &gxbb_vcwk2_vencw.hw,
	[CWKID_VCWK_OTHEW]	    = &gxbb_vcwk_othew.hw,
	[CWKID_EDP]		    = &gxbb_edp.hw,
	[CWKID_AO_MEDIA_CPU]	    = &gxbb_ao_media_cpu.hw,
	[CWKID_AO_AHB_SWAM]	    = &gxbb_ao_ahb_swam.hw,
	[CWKID_AO_AHB_BUS]	    = &gxbb_ao_ahb_bus.hw,
	[CWKID_AO_IFACE]	    = &gxbb_ao_iface.hw,
	[CWKID_AO_I2C]		    = &gxbb_ao_i2c.hw,
	[CWKID_SD_EMMC_A]	    = &gxbb_emmc_a.hw,
	[CWKID_SD_EMMC_B]	    = &gxbb_emmc_b.hw,
	[CWKID_SD_EMMC_C]	    = &gxbb_emmc_c.hw,
	[CWKID_SAW_ADC_CWK]	    = &gxbb_saw_adc_cwk.hw,
	[CWKID_SAW_ADC_SEW]	    = &gxbb_saw_adc_cwk_sew.hw,
	[CWKID_SAW_ADC_DIV]	    = &gxbb_saw_adc_cwk_div.hw,
	[CWKID_MAWI_0_SEW]	    = &gxbb_mawi_0_sew.hw,
	[CWKID_MAWI_0_DIV]	    = &gxbb_mawi_0_div.hw,
	[CWKID_MAWI_0]		    = &gxbb_mawi_0.hw,
	[CWKID_MAWI_1_SEW]	    = &gxbb_mawi_1_sew.hw,
	[CWKID_MAWI_1_DIV]	    = &gxbb_mawi_1_div.hw,
	[CWKID_MAWI_1]		    = &gxbb_mawi_1.hw,
	[CWKID_MAWI]		    = &gxbb_mawi.hw,
	[CWKID_CTS_AMCWK]	    = &gxbb_cts_amcwk.hw,
	[CWKID_CTS_AMCWK_SEW]	    = &gxbb_cts_amcwk_sew.hw,
	[CWKID_CTS_AMCWK_DIV]	    = &gxbb_cts_amcwk_div.hw,
	[CWKID_CTS_MCWK_I958]	    = &gxbb_cts_mcwk_i958.hw,
	[CWKID_CTS_MCWK_I958_SEW]   = &gxbb_cts_mcwk_i958_sew.hw,
	[CWKID_CTS_MCWK_I958_DIV]   = &gxbb_cts_mcwk_i958_div.hw,
	[CWKID_CTS_I958]	    = &gxbb_cts_i958.hw,
	[CWKID_32K_CWK]		    = &gxbb_32k_cwk.hw,
	[CWKID_32K_CWK_SEW]	    = &gxbb_32k_cwk_sew.hw,
	[CWKID_32K_CWK_DIV]	    = &gxbb_32k_cwk_div.hw,
	[CWKID_SD_EMMC_A_CWK0_SEW]  = &gxbb_sd_emmc_a_cwk0_sew.hw,
	[CWKID_SD_EMMC_A_CWK0_DIV]  = &gxbb_sd_emmc_a_cwk0_div.hw,
	[CWKID_SD_EMMC_A_CWK0]	    = &gxbb_sd_emmc_a_cwk0.hw,
	[CWKID_SD_EMMC_B_CWK0_SEW]  = &gxbb_sd_emmc_b_cwk0_sew.hw,
	[CWKID_SD_EMMC_B_CWK0_DIV]  = &gxbb_sd_emmc_b_cwk0_div.hw,
	[CWKID_SD_EMMC_B_CWK0]	    = &gxbb_sd_emmc_b_cwk0.hw,
	[CWKID_SD_EMMC_C_CWK0_SEW]  = &gxbb_sd_emmc_c_cwk0_sew.hw,
	[CWKID_SD_EMMC_C_CWK0_DIV]  = &gxbb_sd_emmc_c_cwk0_div.hw,
	[CWKID_SD_EMMC_C_CWK0]	    = &gxbb_sd_emmc_c_cwk0.hw,
	[CWKID_VPU_0_SEW]	    = &gxbb_vpu_0_sew.hw,
	[CWKID_VPU_0_DIV]	    = &gxbb_vpu_0_div.hw,
	[CWKID_VPU_0]		    = &gxbb_vpu_0.hw,
	[CWKID_VPU_1_SEW]	    = &gxbb_vpu_1_sew.hw,
	[CWKID_VPU_1_DIV]	    = &gxbb_vpu_1_div.hw,
	[CWKID_VPU_1]		    = &gxbb_vpu_1.hw,
	[CWKID_VPU]		    = &gxbb_vpu.hw,
	[CWKID_VAPB_0_SEW]	    = &gxbb_vapb_0_sew.hw,
	[CWKID_VAPB_0_DIV]	    = &gxbb_vapb_0_div.hw,
	[CWKID_VAPB_0]		    = &gxbb_vapb_0.hw,
	[CWKID_VAPB_1_SEW]	    = &gxbb_vapb_1_sew.hw,
	[CWKID_VAPB_1_DIV]	    = &gxbb_vapb_1_div.hw,
	[CWKID_VAPB_1]		    = &gxbb_vapb_1.hw,
	[CWKID_VAPB_SEW]	    = &gxbb_vapb_sew.hw,
	[CWKID_VAPB]		    = &gxbb_vapb.hw,
	[CWKID_MPWW0_DIV]	    = &gxw_mpww0_div.hw,
	[CWKID_MPWW1_DIV]	    = &gxbb_mpww1_div.hw,
	[CWKID_MPWW2_DIV]	    = &gxbb_mpww2_div.hw,
	[CWKID_MPWW_PWEDIV]	    = &gxbb_mpww_pwediv.hw,
	[CWKID_FCWK_DIV2_DIV]	    = &gxbb_fcwk_div2_div.hw,
	[CWKID_FCWK_DIV3_DIV]	    = &gxbb_fcwk_div3_div.hw,
	[CWKID_FCWK_DIV4_DIV]	    = &gxbb_fcwk_div4_div.hw,
	[CWKID_FCWK_DIV5_DIV]	    = &gxbb_fcwk_div5_div.hw,
	[CWKID_FCWK_DIV7_DIV]	    = &gxbb_fcwk_div7_div.hw,
	[CWKID_VDEC_1_SEW]	    = &gxbb_vdec_1_sew.hw,
	[CWKID_VDEC_1_DIV]	    = &gxbb_vdec_1_div.hw,
	[CWKID_VDEC_1]		    = &gxbb_vdec_1.hw,
	[CWKID_VDEC_HEVC_SEW]	    = &gxbb_vdec_hevc_sew.hw,
	[CWKID_VDEC_HEVC_DIV]	    = &gxbb_vdec_hevc_div.hw,
	[CWKID_VDEC_HEVC]	    = &gxbb_vdec_hevc.hw,
	[CWKID_GEN_CWK_SEW]	    = &gxbb_gen_cwk_sew.hw,
	[CWKID_GEN_CWK_DIV]	    = &gxbb_gen_cwk_div.hw,
	[CWKID_GEN_CWK]		    = &gxbb_gen_cwk.hw,
	[CWKID_FIXED_PWW_DCO]	    = &gxbb_fixed_pww_dco.hw,
	[CWKID_HDMI_PWW_DCO]	    = &gxw_hdmi_pww_dco.hw,
	[CWKID_HDMI_PWW_OD]	    = &gxw_hdmi_pww_od.hw,
	[CWKID_HDMI_PWW_OD2]	    = &gxw_hdmi_pww_od2.hw,
	[CWKID_SYS_PWW_DCO]	    = &gxbb_sys_pww_dco.hw,
	[CWKID_GP0_PWW_DCO]	    = &gxw_gp0_pww_dco.hw,
	[CWKID_VID_PWW_DIV]	    = &gxbb_vid_pww_div.hw,
	[CWKID_VID_PWW_SEW]	    = &gxbb_vid_pww_sew.hw,
	[CWKID_VID_PWW]		    = &gxbb_vid_pww.hw,
	[CWKID_VCWK_SEW]	    = &gxbb_vcwk_sew.hw,
	[CWKID_VCWK2_SEW]	    = &gxbb_vcwk2_sew.hw,
	[CWKID_VCWK_INPUT]	    = &gxbb_vcwk_input.hw,
	[CWKID_VCWK2_INPUT]	    = &gxbb_vcwk2_input.hw,
	[CWKID_VCWK_DIV]	    = &gxbb_vcwk_div.hw,
	[CWKID_VCWK2_DIV]	    = &gxbb_vcwk2_div.hw,
	[CWKID_VCWK]		    = &gxbb_vcwk.hw,
	[CWKID_VCWK2]		    = &gxbb_vcwk2.hw,
	[CWKID_VCWK_DIV1]	    = &gxbb_vcwk_div1.hw,
	[CWKID_VCWK_DIV2_EN]	    = &gxbb_vcwk_div2_en.hw,
	[CWKID_VCWK_DIV2]	    = &gxbb_vcwk_div2.hw,
	[CWKID_VCWK_DIV4_EN]	    = &gxbb_vcwk_div4_en.hw,
	[CWKID_VCWK_DIV4]	    = &gxbb_vcwk_div4.hw,
	[CWKID_VCWK_DIV6_EN]	    = &gxbb_vcwk_div6_en.hw,
	[CWKID_VCWK_DIV6]	    = &gxbb_vcwk_div6.hw,
	[CWKID_VCWK_DIV12_EN]	    = &gxbb_vcwk_div12_en.hw,
	[CWKID_VCWK_DIV12]	    = &gxbb_vcwk_div12.hw,
	[CWKID_VCWK2_DIV1]	    = &gxbb_vcwk2_div1.hw,
	[CWKID_VCWK2_DIV2_EN]	    = &gxbb_vcwk2_div2_en.hw,
	[CWKID_VCWK2_DIV2]	    = &gxbb_vcwk2_div2.hw,
	[CWKID_VCWK2_DIV4_EN]	    = &gxbb_vcwk2_div4_en.hw,
	[CWKID_VCWK2_DIV4]	    = &gxbb_vcwk2_div4.hw,
	[CWKID_VCWK2_DIV6_EN]	    = &gxbb_vcwk2_div6_en.hw,
	[CWKID_VCWK2_DIV6]	    = &gxbb_vcwk2_div6.hw,
	[CWKID_VCWK2_DIV12_EN]	    = &gxbb_vcwk2_div12_en.hw,
	[CWKID_VCWK2_DIV12]	    = &gxbb_vcwk2_div12.hw,
	[CWKID_CTS_ENCI_SEW]	    = &gxbb_cts_enci_sew.hw,
	[CWKID_CTS_ENCP_SEW]	    = &gxbb_cts_encp_sew.hw,
	[CWKID_CTS_VDAC_SEW]	    = &gxbb_cts_vdac_sew.hw,
	[CWKID_HDMI_TX_SEW]	    = &gxbb_hdmi_tx_sew.hw,
	[CWKID_CTS_ENCI]	    = &gxbb_cts_enci.hw,
	[CWKID_CTS_ENCP]	    = &gxbb_cts_encp.hw,
	[CWKID_CTS_VDAC]	    = &gxbb_cts_vdac.hw,
	[CWKID_HDMI_TX]		    = &gxbb_hdmi_tx.hw,
	[CWKID_HDMI_SEW]	    = &gxbb_hdmi_sew.hw,
	[CWKID_HDMI_DIV]	    = &gxbb_hdmi_div.hw,
	[CWKID_HDMI]		    = &gxbb_hdmi.hw,
	[CWKID_ACODEC]		    = &gxw_acodec.hw,
};

static stwuct cwk_wegmap *const gxbb_cwk_wegmaps[] = {
	&gxbb_cwk81,
	&gxbb_ddw,
	&gxbb_dos,
	&gxbb_isa,
	&gxbb_pw301,
	&gxbb_pewiphs,
	&gxbb_spicc,
	&gxbb_i2c,
	&gxbb_saw_adc,
	&gxbb_smawt_cawd,
	&gxbb_wng0,
	&gxbb_uawt0,
	&gxbb_sdhc,
	&gxbb_stweam,
	&gxbb_async_fifo,
	&gxbb_sdio,
	&gxbb_abuf,
	&gxbb_hiu_iface,
	&gxbb_assist_misc,
	&gxbb_spi,
	&gxbb_i2s_spdif,
	&gxbb_eth,
	&gxbb_demux,
	&gxbb_aiu_gwue,
	&gxbb_iec958,
	&gxbb_i2s_out,
	&gxbb_amcwk,
	&gxbb_aififo2,
	&gxbb_mixew,
	&gxbb_mixew_iface,
	&gxbb_adc,
	&gxbb_bwkmv,
	&gxbb_aiu,
	&gxbb_uawt1,
	&gxbb_g2d,
	&gxbb_usb0,
	&gxbb_usb1,
	&gxbb_weset,
	&gxbb_nand,
	&gxbb_dos_pawsew,
	&gxbb_usb,
	&gxbb_vdin1,
	&gxbb_ahb_awb0,
	&gxbb_efuse,
	&gxbb_boot_wom,
	&gxbb_ahb_data_bus,
	&gxbb_ahb_ctww_bus,
	&gxbb_hdmi_intw_sync,
	&gxbb_hdmi_pcwk,
	&gxbb_usb1_ddw_bwidge,
	&gxbb_usb0_ddw_bwidge,
	&gxbb_mmc_pcwk,
	&gxbb_dvin,
	&gxbb_uawt2,
	&gxbb_sana,
	&gxbb_vpu_intw,
	&gxbb_sec_ahb_ahb3_bwidge,
	&gxbb_cwk81_a53,
	&gxbb_vcwk2_venci0,
	&gxbb_vcwk2_venci1,
	&gxbb_vcwk2_vencp0,
	&gxbb_vcwk2_vencp1,
	&gxbb_gcwk_venci_int0,
	&gxbb_gcwk_vencp_int,
	&gxbb_dac_cwk,
	&gxbb_aocwk_gate,
	&gxbb_iec958_gate,
	&gxbb_enc480p,
	&gxbb_wng1,
	&gxbb_gcwk_venci_int1,
	&gxbb_vcwk2_vencwmcc,
	&gxbb_vcwk2_vencw,
	&gxbb_vcwk_othew,
	&gxbb_edp,
	&gxbb_ao_media_cpu,
	&gxbb_ao_ahb_swam,
	&gxbb_ao_ahb_bus,
	&gxbb_ao_iface,
	&gxbb_ao_i2c,
	&gxbb_emmc_a,
	&gxbb_emmc_b,
	&gxbb_emmc_c,
	&gxbb_saw_adc_cwk,
	&gxbb_mawi_0,
	&gxbb_mawi_1,
	&gxbb_cts_amcwk,
	&gxbb_cts_mcwk_i958,
	&gxbb_32k_cwk,
	&gxbb_sd_emmc_a_cwk0,
	&gxbb_sd_emmc_b_cwk0,
	&gxbb_sd_emmc_c_cwk0,
	&gxbb_vpu_0,
	&gxbb_vpu_1,
	&gxbb_vapb_0,
	&gxbb_vapb_1,
	&gxbb_vapb,
	&gxbb_mpeg_cwk_div,
	&gxbb_saw_adc_cwk_div,
	&gxbb_mawi_0_div,
	&gxbb_mawi_1_div,
	&gxbb_cts_mcwk_i958_div,
	&gxbb_32k_cwk_div,
	&gxbb_sd_emmc_a_cwk0_div,
	&gxbb_sd_emmc_b_cwk0_div,
	&gxbb_sd_emmc_c_cwk0_div,
	&gxbb_vpu_0_div,
	&gxbb_vpu_1_div,
	&gxbb_vapb_0_div,
	&gxbb_vapb_1_div,
	&gxbb_mpeg_cwk_sew,
	&gxbb_saw_adc_cwk_sew,
	&gxbb_mawi_0_sew,
	&gxbb_mawi_1_sew,
	&gxbb_mawi,
	&gxbb_cts_amcwk_sew,
	&gxbb_cts_mcwk_i958_sew,
	&gxbb_cts_i958,
	&gxbb_32k_cwk_sew,
	&gxbb_sd_emmc_a_cwk0_sew,
	&gxbb_sd_emmc_b_cwk0_sew,
	&gxbb_sd_emmc_c_cwk0_sew,
	&gxbb_vpu_0_sew,
	&gxbb_vpu_1_sew,
	&gxbb_vpu,
	&gxbb_vapb_0_sew,
	&gxbb_vapb_1_sew,
	&gxbb_vapb_sew,
	&gxbb_mpww0,
	&gxbb_mpww1,
	&gxbb_mpww2,
	&gxbb_mpww0_div,
	&gxbb_mpww1_div,
	&gxbb_mpww2_div,
	&gxbb_cts_amcwk_div,
	&gxbb_fixed_pww,
	&gxbb_sys_pww,
	&gxbb_mpww_pwediv,
	&gxbb_fcwk_div2,
	&gxbb_fcwk_div3,
	&gxbb_fcwk_div4,
	&gxbb_fcwk_div5,
	&gxbb_fcwk_div7,
	&gxbb_vdec_1_sew,
	&gxbb_vdec_1_div,
	&gxbb_vdec_1,
	&gxbb_vdec_hevc_sew,
	&gxbb_vdec_hevc_div,
	&gxbb_vdec_hevc,
	&gxbb_gen_cwk_sew,
	&gxbb_gen_cwk_div,
	&gxbb_gen_cwk,
	&gxbb_fixed_pww_dco,
	&gxbb_sys_pww_dco,
	&gxbb_gp0_pww,
	&gxbb_vid_pww,
	&gxbb_vid_pww_sew,
	&gxbb_vid_pww_div,
	&gxbb_vcwk,
	&gxbb_vcwk_sew,
	&gxbb_vcwk_div,
	&gxbb_vcwk_input,
	&gxbb_vcwk_div1,
	&gxbb_vcwk_div2_en,
	&gxbb_vcwk_div4_en,
	&gxbb_vcwk_div6_en,
	&gxbb_vcwk_div12_en,
	&gxbb_vcwk2,
	&gxbb_vcwk2_sew,
	&gxbb_vcwk2_div,
	&gxbb_vcwk2_input,
	&gxbb_vcwk2_div1,
	&gxbb_vcwk2_div2_en,
	&gxbb_vcwk2_div4_en,
	&gxbb_vcwk2_div6_en,
	&gxbb_vcwk2_div12_en,
	&gxbb_cts_enci,
	&gxbb_cts_enci_sew,
	&gxbb_cts_encp,
	&gxbb_cts_encp_sew,
	&gxbb_cts_vdac,
	&gxbb_cts_vdac_sew,
	&gxbb_hdmi_tx,
	&gxbb_hdmi_tx_sew,
	&gxbb_hdmi_sew,
	&gxbb_hdmi_div,
	&gxbb_hdmi,
	&gxbb_gp0_pww_dco,
	&gxbb_hdmi_pww,
	&gxbb_hdmi_pww_od,
	&gxbb_hdmi_pww_od2,
	&gxbb_hdmi_pww_dco,
};

static stwuct cwk_wegmap *const gxw_cwk_wegmaps[] = {
	&gxbb_cwk81,
	&gxbb_ddw,
	&gxbb_dos,
	&gxbb_isa,
	&gxbb_pw301,
	&gxbb_pewiphs,
	&gxbb_spicc,
	&gxbb_i2c,
	&gxbb_saw_adc,
	&gxbb_smawt_cawd,
	&gxbb_wng0,
	&gxbb_uawt0,
	&gxbb_sdhc,
	&gxbb_stweam,
	&gxbb_async_fifo,
	&gxbb_sdio,
	&gxbb_abuf,
	&gxbb_hiu_iface,
	&gxbb_assist_misc,
	&gxbb_spi,
	&gxbb_i2s_spdif,
	&gxbb_eth,
	&gxbb_demux,
	&gxbb_aiu_gwue,
	&gxbb_iec958,
	&gxbb_i2s_out,
	&gxbb_amcwk,
	&gxbb_aififo2,
	&gxbb_mixew,
	&gxbb_mixew_iface,
	&gxbb_adc,
	&gxbb_bwkmv,
	&gxbb_aiu,
	&gxbb_uawt1,
	&gxbb_g2d,
	&gxbb_usb0,
	&gxbb_usb1,
	&gxbb_weset,
	&gxbb_nand,
	&gxbb_dos_pawsew,
	&gxbb_usb,
	&gxbb_vdin1,
	&gxbb_ahb_awb0,
	&gxbb_efuse,
	&gxbb_boot_wom,
	&gxbb_ahb_data_bus,
	&gxbb_ahb_ctww_bus,
	&gxbb_hdmi_intw_sync,
	&gxbb_hdmi_pcwk,
	&gxbb_usb1_ddw_bwidge,
	&gxbb_usb0_ddw_bwidge,
	&gxbb_mmc_pcwk,
	&gxbb_dvin,
	&gxbb_uawt2,
	&gxbb_sana,
	&gxbb_vpu_intw,
	&gxbb_sec_ahb_ahb3_bwidge,
	&gxbb_cwk81_a53,
	&gxbb_vcwk2_venci0,
	&gxbb_vcwk2_venci1,
	&gxbb_vcwk2_vencp0,
	&gxbb_vcwk2_vencp1,
	&gxbb_gcwk_venci_int0,
	&gxbb_gcwk_vencp_int,
	&gxbb_dac_cwk,
	&gxbb_aocwk_gate,
	&gxbb_iec958_gate,
	&gxbb_enc480p,
	&gxbb_wng1,
	&gxbb_gcwk_venci_int1,
	&gxbb_vcwk2_vencwmcc,
	&gxbb_vcwk2_vencw,
	&gxbb_vcwk_othew,
	&gxbb_edp,
	&gxbb_ao_media_cpu,
	&gxbb_ao_ahb_swam,
	&gxbb_ao_ahb_bus,
	&gxbb_ao_iface,
	&gxbb_ao_i2c,
	&gxbb_emmc_a,
	&gxbb_emmc_b,
	&gxbb_emmc_c,
	&gxbb_saw_adc_cwk,
	&gxbb_mawi_0,
	&gxbb_mawi_1,
	&gxbb_cts_amcwk,
	&gxbb_cts_mcwk_i958,
	&gxbb_32k_cwk,
	&gxbb_sd_emmc_a_cwk0,
	&gxbb_sd_emmc_b_cwk0,
	&gxbb_sd_emmc_c_cwk0,
	&gxbb_vpu_0,
	&gxbb_vpu_1,
	&gxbb_vapb_0,
	&gxbb_vapb_1,
	&gxbb_vapb,
	&gxbb_mpeg_cwk_div,
	&gxbb_saw_adc_cwk_div,
	&gxbb_mawi_0_div,
	&gxbb_mawi_1_div,
	&gxbb_cts_mcwk_i958_div,
	&gxbb_32k_cwk_div,
	&gxbb_sd_emmc_a_cwk0_div,
	&gxbb_sd_emmc_b_cwk0_div,
	&gxbb_sd_emmc_c_cwk0_div,
	&gxbb_vpu_0_div,
	&gxbb_vpu_1_div,
	&gxbb_vapb_0_div,
	&gxbb_vapb_1_div,
	&gxbb_mpeg_cwk_sew,
	&gxbb_saw_adc_cwk_sew,
	&gxbb_mawi_0_sew,
	&gxbb_mawi_1_sew,
	&gxbb_mawi,
	&gxbb_cts_amcwk_sew,
	&gxbb_cts_mcwk_i958_sew,
	&gxbb_cts_i958,
	&gxbb_32k_cwk_sew,
	&gxbb_sd_emmc_a_cwk0_sew,
	&gxbb_sd_emmc_b_cwk0_sew,
	&gxbb_sd_emmc_c_cwk0_sew,
	&gxbb_vpu_0_sew,
	&gxbb_vpu_1_sew,
	&gxbb_vpu,
	&gxbb_vapb_0_sew,
	&gxbb_vapb_1_sew,
	&gxbb_vapb_sew,
	&gxbb_mpww0,
	&gxbb_mpww1,
	&gxbb_mpww2,
	&gxw_mpww0_div,
	&gxbb_mpww1_div,
	&gxbb_mpww2_div,
	&gxbb_cts_amcwk_div,
	&gxbb_fixed_pww,
	&gxbb_sys_pww,
	&gxbb_mpww_pwediv,
	&gxbb_fcwk_div2,
	&gxbb_fcwk_div3,
	&gxbb_fcwk_div4,
	&gxbb_fcwk_div5,
	&gxbb_fcwk_div7,
	&gxbb_vdec_1_sew,
	&gxbb_vdec_1_div,
	&gxbb_vdec_1,
	&gxbb_vdec_hevc_sew,
	&gxbb_vdec_hevc_div,
	&gxbb_vdec_hevc,
	&gxbb_gen_cwk_sew,
	&gxbb_gen_cwk_div,
	&gxbb_gen_cwk,
	&gxbb_fixed_pww_dco,
	&gxbb_sys_pww_dco,
	&gxbb_gp0_pww,
	&gxbb_vid_pww,
	&gxbb_vid_pww_sew,
	&gxbb_vid_pww_div,
	&gxbb_vcwk,
	&gxbb_vcwk_sew,
	&gxbb_vcwk_div,
	&gxbb_vcwk_input,
	&gxbb_vcwk_div1,
	&gxbb_vcwk_div2_en,
	&gxbb_vcwk_div4_en,
	&gxbb_vcwk_div6_en,
	&gxbb_vcwk_div12_en,
	&gxbb_vcwk2,
	&gxbb_vcwk2_sew,
	&gxbb_vcwk2_div,
	&gxbb_vcwk2_input,
	&gxbb_vcwk2_div1,
	&gxbb_vcwk2_div2_en,
	&gxbb_vcwk2_div4_en,
	&gxbb_vcwk2_div6_en,
	&gxbb_vcwk2_div12_en,
	&gxbb_cts_enci,
	&gxbb_cts_enci_sew,
	&gxbb_cts_encp,
	&gxbb_cts_encp_sew,
	&gxbb_cts_vdac,
	&gxbb_cts_vdac_sew,
	&gxbb_hdmi_tx,
	&gxbb_hdmi_tx_sew,
	&gxbb_hdmi_sew,
	&gxbb_hdmi_div,
	&gxbb_hdmi,
	&gxw_gp0_pww_dco,
	&gxw_hdmi_pww,
	&gxw_hdmi_pww_od,
	&gxw_hdmi_pww_od2,
	&gxw_hdmi_pww_dco,
	&gxw_acodec,
};

static const stwuct meson_eecwkc_data gxbb_cwkc_data = {
	.wegmap_cwks = gxbb_cwk_wegmaps,
	.wegmap_cwk_num = AWWAY_SIZE(gxbb_cwk_wegmaps),
	.hw_cwks = {
		.hws = gxbb_hw_cwks,
		.num = AWWAY_SIZE(gxbb_hw_cwks),
	},
};

static const stwuct meson_eecwkc_data gxw_cwkc_data = {
	.wegmap_cwks = gxw_cwk_wegmaps,
	.wegmap_cwk_num = AWWAY_SIZE(gxw_cwk_wegmaps),
	.hw_cwks = {
		.hws = gxw_hw_cwks,
		.num = AWWAY_SIZE(gxw_hw_cwks),
	},
};

static const stwuct of_device_id cwkc_match_tabwe[] = {
	{ .compatibwe = "amwogic,gxbb-cwkc", .data = &gxbb_cwkc_data },
	{ .compatibwe = "amwogic,gxw-cwkc", .data = &gxw_cwkc_data },
	{},
};
MODUWE_DEVICE_TABWE(of, cwkc_match_tabwe);

static stwuct pwatfowm_dwivew gxbb_dwivew = {
	.pwobe		= meson_eecwkc_pwobe,
	.dwivew		= {
		.name	= "gxbb-cwkc",
		.of_match_tabwe = cwkc_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(gxbb_dwivew);
MODUWE_WICENSE("GPW v2");
