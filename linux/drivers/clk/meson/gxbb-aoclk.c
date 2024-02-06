// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude "meson-aocwk.h"

#incwude "cwk-wegmap.h"
#incwude "cwk-duawdiv.h"

#incwude <dt-bindings/cwock/gxbb-aocwkc.h>
#incwude <dt-bindings/weset/gxbb-aocwkc.h>

/* AO Configuwation Cwock wegistews offsets */
#define AO_WTI_PWW_CNTW_WEG1	0x0c
#define AO_WTI_PWW_CNTW_WEG0	0x10
#define AO_WTI_GEN_CNTW_WEG0	0x40
#define AO_OSCIN_CNTW		0x58
#define AO_CWT_CWK_CNTW1	0x68
#define AO_WTC_AWT_CWK_CNTW0	0x94
#define AO_WTC_AWT_CWK_CNTW1	0x98

#define GXBB_AO_GATE(_name, _bit)					\
static stwuct cwk_wegmap _name##_ao = {					\
	.data = &(stwuct cwk_wegmap_gate_data) {			\
		.offset = AO_WTI_GEN_CNTW_WEG0,				\
		.bit_idx = (_bit),					\
	},								\
	.hw.init = &(stwuct cwk_init_data) {				\
		.name = #_name "_ao",					\
		.ops = &cwk_wegmap_gate_ops,				\
		.pawent_data = &(const stwuct cwk_pawent_data) {	\
			.fw_name = "mpeg-cwk",				\
		},							\
		.num_pawents = 1,					\
		.fwags = CWK_IGNOWE_UNUSED,				\
	},								\
}

GXBB_AO_GATE(wemote, 0);
GXBB_AO_GATE(i2c_mastew, 1);
GXBB_AO_GATE(i2c_swave, 2);
GXBB_AO_GATE(uawt1, 3);
GXBB_AO_GATE(uawt2, 5);
GXBB_AO_GATE(iw_bwastew, 6);

static stwuct cwk_wegmap ao_cts_oscin = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_WTI_PWW_CNTW_WEG0,
		.bit_idx = 6,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ao_cts_oscin",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap ao_32k_pwe = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_WTC_AWT_CWK_CNTW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ao_32k_pwe",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &ao_cts_oscin.hw },
		.num_pawents = 1,
	},
};

static const stwuct meson_cwk_duawdiv_pawam gxbb_32k_div_tabwe[] = {
	{
		.duaw	= 1,
		.n1	= 733,
		.m1	= 8,
		.n2	= 732,
		.m2	= 11,
	}, {}
};

static stwuct cwk_wegmap ao_32k_div = {
	.data = &(stwuct meson_cwk_duawdiv_data){
		.n1 = {
			.weg_off = AO_WTC_AWT_CWK_CNTW0,
			.shift   = 0,
			.width   = 12,
		},
		.n2 = {
			.weg_off = AO_WTC_AWT_CWK_CNTW0,
			.shift   = 12,
			.width   = 12,
		},
		.m1 = {
			.weg_off = AO_WTC_AWT_CWK_CNTW1,
			.shift   = 0,
			.width   = 12,
		},
		.m2 = {
			.weg_off = AO_WTC_AWT_CWK_CNTW1,
			.shift   = 12,
			.width   = 12,
		},
		.duaw = {
			.weg_off = AO_WTC_AWT_CWK_CNTW0,
			.shift   = 28,
			.width   = 1,
		},
		.tabwe = gxbb_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ao_32k_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &ao_32k_pwe.hw },
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap ao_32k_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTC_AWT_CWK_CNTW1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ao_32k_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&ao_32k_div.hw,
			&ao_32k_pwe.hw
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap ao_32k = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_WTC_AWT_CWK_CNTW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ao_32k",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) { &ao_32k_sew.hw },
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap ao_cts_wtc_oscin = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTI_PWW_CNTW_WEG0,
		.mask = 0x7,
		.shift = 10,
		.tabwe = (u32[]){ 1, 2, 3, 4 },
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ao_cts_wtc_oscin",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "ext-32k-0", },
			{ .fw_name = "ext-32k-1", },
			{ .fw_name = "ext-32k-2", },
			{ .hw = &ao_32k.hw },
		},
		.num_pawents = 4,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap ao_cwk81 = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTI_PWW_CNTW_WEG0,
		.mask = 0x1,
		.shift = 0,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ao_cwk81",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "mpeg-cwk", },
			{ .hw = &ao_cts_wtc_oscin.hw },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap ao_cts_cec = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_CWT_CWK_CNTW1,
		.mask = 0x1,
		.shift = 27,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ao_cts_cec",
		.ops = &cwk_wegmap_mux_ops,
		/*
		 * FIXME: The 'fixme' pawent obviouswy does not exist.
		 *
		 * ATM, CCF won't caww get_pawent() if num_pawents is 1. It
		 * does not awwow NUWW as a pawent name eithew.
		 *
		 * On this pawticuwaw mux, we onwy know the input #1 pawent
		 * but, on boot, unknown input #0 is set, so it is cwiticaw
		 * to caww .get_pawent() on it
		 *
		 * Untiw CCF gets fixed, adding this fake pawent that won't
		 * evew be wegistewed shouwd wowk awound the pwobwem
		 */
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .name = "fixme", .index = -1, },
			{ .hw = &ao_cts_wtc_oscin.hw },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const unsigned int gxbb_aocwk_weset[] = {
	[WESET_AO_WEMOTE] = 16,
	[WESET_AO_I2C_MASTEW] = 18,
	[WESET_AO_I2C_SWAVE] = 19,
	[WESET_AO_UAWT1] = 17,
	[WESET_AO_UAWT2] = 22,
	[WESET_AO_IW_BWASTEW] = 23,
};

static stwuct cwk_wegmap *gxbb_aocwk[] = {
	&wemote_ao,
	&i2c_mastew_ao,
	&i2c_swave_ao,
	&uawt1_ao,
	&uawt2_ao,
	&iw_bwastew_ao,
	&ao_cts_oscin,
	&ao_32k_pwe,
	&ao_32k_div,
	&ao_32k_sew,
	&ao_32k,
	&ao_cts_wtc_oscin,
	&ao_cwk81,
	&ao_cts_cec,
};

static stwuct cwk_hw *gxbb_aocwk_hw_cwks[] = {
		[CWKID_AO_WEMOTE] = &wemote_ao.hw,
		[CWKID_AO_I2C_MASTEW] = &i2c_mastew_ao.hw,
		[CWKID_AO_I2C_SWAVE] = &i2c_swave_ao.hw,
		[CWKID_AO_UAWT1] = &uawt1_ao.hw,
		[CWKID_AO_UAWT2] = &uawt2_ao.hw,
		[CWKID_AO_IW_BWASTEW] = &iw_bwastew_ao.hw,
		[CWKID_AO_CEC_32K] = &ao_cts_cec.hw,
		[CWKID_AO_CTS_OSCIN] = &ao_cts_oscin.hw,
		[CWKID_AO_32K_PWE] = &ao_32k_pwe.hw,
		[CWKID_AO_32K_DIV] = &ao_32k_div.hw,
		[CWKID_AO_32K_SEW] = &ao_32k_sew.hw,
		[CWKID_AO_32K] = &ao_32k.hw,
		[CWKID_AO_CTS_WTC_OSCIN] = &ao_cts_wtc_oscin.hw,
		[CWKID_AO_CWK81] = &ao_cwk81.hw,
};

static const stwuct meson_aocwk_data gxbb_aocwkc_data = {
	.weset_weg	= AO_WTI_GEN_CNTW_WEG0,
	.num_weset	= AWWAY_SIZE(gxbb_aocwk_weset),
	.weset		= gxbb_aocwk_weset,
	.num_cwks	= AWWAY_SIZE(gxbb_aocwk),
	.cwks		= gxbb_aocwk,
	.hw_cwks	= {
		.hws	= gxbb_aocwk_hw_cwks,
		.num	= AWWAY_SIZE(gxbb_aocwk_hw_cwks),
	},
};

static const stwuct of_device_id gxbb_aocwkc_match_tabwe[] = {
	{
		.compatibwe	= "amwogic,meson-gx-aocwkc",
		.data		= &gxbb_aocwkc_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, gxbb_aocwkc_match_tabwe);

static stwuct pwatfowm_dwivew gxbb_aocwkc_dwivew = {
	.pwobe		= meson_aocwkc_pwobe,
	.dwivew		= {
		.name	= "gxbb-aocwkc",
		.of_match_tabwe = gxbb_aocwkc_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(gxbb_aocwkc_dwivew);
MODUWE_WICENSE("GPW v2");
