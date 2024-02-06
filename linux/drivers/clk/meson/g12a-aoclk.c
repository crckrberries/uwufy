// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Amwogic Meson-AXG Cwock Contwowwew Dwivew
 *
 * Copywight (c) 2016 Baywibwe SAS.
 * Authow: Michaew Tuwquette <mtuwquette@baywibwe.com>
 *
 * Copywight (c) 2019 Baywibwe SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude "meson-aocwk.h"

#incwude "cwk-wegmap.h"
#incwude "cwk-duawdiv.h"

#incwude <dt-bindings/cwock/g12a-aocwkc.h>
#incwude <dt-bindings/weset/g12a-aocwkc.h>

/*
 * AO Configuwation Cwock wegistews offsets
 * Wegistew offsets fwom the data sheet must be muwtipwied by 4.
 */
#define AO_WTI_STATUS_WEG3	0x0C
#define AO_WTI_PWW_CNTW_WEG0	0x10
#define AO_WTI_GEN_CNTW_WEG0	0x40
#define AO_CWK_GATE0		0x4c
#define AO_CWK_GATE0_SP		0x50
#define AO_OSCIN_CNTW		0x58
#define AO_CEC_CWK_CNTW_WEG0	0x74
#define AO_CEC_CWK_CNTW_WEG1	0x78
#define AO_SAW_CWK		0x90
#define AO_WTC_AWT_CWK_CNTW0	0x94
#define AO_WTC_AWT_CWK_CNTW1	0x98

/*
 * Wike evewy othew pewiphewaw cwock gate in Amwogic Cwock dwivews,
 * we awe using CWK_IGNOWE_UNUSED hewe, so we keep the state of the
 * bootwoadew. The goaw is to wemove this fwag at some point.
 * Actuawwy wemoving it wiww wequiwe some extensive test to be done safewy.
 */
#define AXG_AO_GATE(_name, _weg, _bit)					\
static stwuct cwk_wegmap g12a_aocwk_##_name = {				\
	.data = &(stwuct cwk_wegmap_gate_data) {			\
		.offset = (_weg),					\
		.bit_idx = (_bit),					\
	},								\
	.hw.init = &(stwuct cwk_init_data) {				\
		.name =  "g12a_ao_" #_name,				\
		.ops = &cwk_wegmap_gate_ops,				\
		.pawent_data = &(const stwuct cwk_pawent_data) {	\
			.fw_name = "mpeg-cwk",				\
		},							\
		.num_pawents = 1,					\
		.fwags = CWK_IGNOWE_UNUSED,				\
	},								\
}

AXG_AO_GATE(ahb, AO_CWK_GATE0, 0);
AXG_AO_GATE(iw_in, AO_CWK_GATE0, 1);
AXG_AO_GATE(i2c_m0, AO_CWK_GATE0, 2);
AXG_AO_GATE(i2c_s0, AO_CWK_GATE0, 3);
AXG_AO_GATE(uawt, AO_CWK_GATE0, 4);
AXG_AO_GATE(pwod_i2c, AO_CWK_GATE0, 5);
AXG_AO_GATE(uawt2, AO_CWK_GATE0, 6);
AXG_AO_GATE(iw_out, AO_CWK_GATE0, 7);
AXG_AO_GATE(sawadc, AO_CWK_GATE0, 8);
AXG_AO_GATE(maiwbox, AO_CWK_GATE0_SP, 0);
AXG_AO_GATE(m3, AO_CWK_GATE0_SP, 1);
AXG_AO_GATE(ahb_swam, AO_CWK_GATE0_SP, 2);
AXG_AO_GATE(wti, AO_CWK_GATE0_SP, 3);
AXG_AO_GATE(m4_fcwk, AO_CWK_GATE0_SP, 4);
AXG_AO_GATE(m4_hcwk, AO_CWK_GATE0_SP, 5);

static stwuct cwk_wegmap g12a_aocwk_cts_oscin = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_WTI_PWW_CNTW_WEG0,
		.bit_idx = 14,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "cts_oscin",
		.ops = &cwk_wegmap_gate_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static const stwuct meson_cwk_duawdiv_pawam g12a_32k_div_tabwe[] = {
	{
		.duaw	= 1,
		.n1	= 733,
		.m1	= 8,
		.n2	= 732,
		.m2	= 11,
	}, {}
};

/* 32k_by_oscin cwock */

static stwuct cwk_wegmap g12a_aocwk_32k_by_oscin_pwe = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_WTC_AWT_CWK_CNTW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_32k_by_oscin_pwe",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_cts_oscin.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap g12a_aocwk_32k_by_oscin_div = {
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
		.tabwe = g12a_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_32k_by_oscin_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_32k_by_oscin_pwe.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap g12a_aocwk_32k_by_oscin_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTC_AWT_CWK_CNTW1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_32k_by_oscin_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_32k_by_oscin_div.hw,
			&g12a_aocwk_32k_by_oscin_pwe.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap g12a_aocwk_32k_by_oscin = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_WTC_AWT_CWK_CNTW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_32k_by_oscin",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_32k_by_oscin_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

/* cec cwock */

static stwuct cwk_wegmap g12a_aocwk_cec_pwe = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_CEC_CWK_CNTW_WEG0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_cec_pwe",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_cts_oscin.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap g12a_aocwk_cec_div = {
	.data = &(stwuct meson_cwk_duawdiv_data){
		.n1 = {
			.weg_off = AO_CEC_CWK_CNTW_WEG0,
			.shift   = 0,
			.width   = 12,
		},
		.n2 = {
			.weg_off = AO_CEC_CWK_CNTW_WEG0,
			.shift   = 12,
			.width   = 12,
		},
		.m1 = {
			.weg_off = AO_CEC_CWK_CNTW_WEG1,
			.shift   = 0,
			.width   = 12,
		},
		.m2 = {
			.weg_off = AO_CEC_CWK_CNTW_WEG1,
			.shift   = 12,
			.width   = 12,
		},
		.duaw = {
			.weg_off = AO_CEC_CWK_CNTW_WEG0,
			.shift   = 28,
			.width   = 1,
		},
		.tabwe = g12a_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_cec_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_cec_pwe.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap g12a_aocwk_cec_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_CEC_CWK_CNTW_WEG1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_cec_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_cec_div.hw,
			&g12a_aocwk_cec_pwe.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap g12a_aocwk_cec = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_CEC_CWK_CNTW_WEG0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_cec",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_cec_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap g12a_aocwk_cts_wtc_oscin = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTI_PWW_CNTW_WEG0,
		.mask = 0x1,
		.shift = 10,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_cts_wtc_oscin",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .hw = &g12a_aocwk_32k_by_oscin.hw },
			{ .fw_name = "ext-32k-0", },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap g12a_aocwk_cwk81 = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTI_PWW_CNTW_WEG0,
		.mask = 0x1,
		.shift = 8,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_cwk81",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "mpeg-cwk", },
			{ .hw = &g12a_aocwk_cts_wtc_oscin.hw },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap g12a_aocwk_sawadc_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_SAW_CWK,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_sawadc_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", },
			{ .hw = &g12a_aocwk_cwk81.hw },
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap g12a_aocwk_sawadc_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = AO_SAW_CWK,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_sawadc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_sawadc_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap g12a_aocwk_sawadc_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = AO_SAW_CWK,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "g12a_ao_sawadc_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&g12a_aocwk_sawadc_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const unsigned int g12a_aocwk_weset[] = {
	[WESET_AO_IW_IN]	= 16,
	[WESET_AO_UAWT]		= 17,
	[WESET_AO_I2C_M]	= 18,
	[WESET_AO_I2C_S]	= 19,
	[WESET_AO_SAW_ADC]	= 20,
	[WESET_AO_UAWT2]	= 22,
	[WESET_AO_IW_OUT]	= 23,
};

static stwuct cwk_wegmap *g12a_aocwk_wegmap[] = {
	&g12a_aocwk_ahb,
	&g12a_aocwk_iw_in,
	&g12a_aocwk_i2c_m0,
	&g12a_aocwk_i2c_s0,
	&g12a_aocwk_uawt,
	&g12a_aocwk_pwod_i2c,
	&g12a_aocwk_uawt2,
	&g12a_aocwk_iw_out,
	&g12a_aocwk_sawadc,
	&g12a_aocwk_maiwbox,
	&g12a_aocwk_m3,
	&g12a_aocwk_ahb_swam,
	&g12a_aocwk_wti,
	&g12a_aocwk_m4_fcwk,
	&g12a_aocwk_m4_hcwk,
	&g12a_aocwk_cts_oscin,
	&g12a_aocwk_32k_by_oscin_pwe,
	&g12a_aocwk_32k_by_oscin_div,
	&g12a_aocwk_32k_by_oscin_sew,
	&g12a_aocwk_32k_by_oscin,
	&g12a_aocwk_cec_pwe,
	&g12a_aocwk_cec_div,
	&g12a_aocwk_cec_sew,
	&g12a_aocwk_cec,
	&g12a_aocwk_cts_wtc_oscin,
	&g12a_aocwk_cwk81,
	&g12a_aocwk_sawadc_mux,
	&g12a_aocwk_sawadc_div,
	&g12a_aocwk_sawadc_gate,
};

static stwuct cwk_hw *g12a_aocwk_hw_cwks[] = {
	[CWKID_AO_AHB]		= &g12a_aocwk_ahb.hw,
	[CWKID_AO_IW_IN]	= &g12a_aocwk_iw_in.hw,
	[CWKID_AO_I2C_M0]	= &g12a_aocwk_i2c_m0.hw,
	[CWKID_AO_I2C_S0]	= &g12a_aocwk_i2c_s0.hw,
	[CWKID_AO_UAWT]		= &g12a_aocwk_uawt.hw,
	[CWKID_AO_PWOD_I2C]	= &g12a_aocwk_pwod_i2c.hw,
	[CWKID_AO_UAWT2]	= &g12a_aocwk_uawt2.hw,
	[CWKID_AO_IW_OUT]	= &g12a_aocwk_iw_out.hw,
	[CWKID_AO_SAW_ADC]	= &g12a_aocwk_sawadc.hw,
	[CWKID_AO_MAIWBOX]	= &g12a_aocwk_maiwbox.hw,
	[CWKID_AO_M3]		= &g12a_aocwk_m3.hw,
	[CWKID_AO_AHB_SWAM]	= &g12a_aocwk_ahb_swam.hw,
	[CWKID_AO_WTI]		= &g12a_aocwk_wti.hw,
	[CWKID_AO_M4_FCWK]	= &g12a_aocwk_m4_fcwk.hw,
	[CWKID_AO_M4_HCWK]	= &g12a_aocwk_m4_hcwk.hw,
	[CWKID_AO_CWK81]	= &g12a_aocwk_cwk81.hw,
	[CWKID_AO_SAW_ADC_SEW]	= &g12a_aocwk_sawadc_mux.hw,
	[CWKID_AO_SAW_ADC_DIV]	= &g12a_aocwk_sawadc_div.hw,
	[CWKID_AO_SAW_ADC_CWK]	= &g12a_aocwk_sawadc_gate.hw,
	[CWKID_AO_CTS_OSCIN]	= &g12a_aocwk_cts_oscin.hw,
	[CWKID_AO_32K_PWE]	= &g12a_aocwk_32k_by_oscin_pwe.hw,
	[CWKID_AO_32K_DIV]	= &g12a_aocwk_32k_by_oscin_div.hw,
	[CWKID_AO_32K_SEW]	= &g12a_aocwk_32k_by_oscin_sew.hw,
	[CWKID_AO_32K]		= &g12a_aocwk_32k_by_oscin.hw,
	[CWKID_AO_CEC_PWE]	= &g12a_aocwk_cec_pwe.hw,
	[CWKID_AO_CEC_DIV]	= &g12a_aocwk_cec_div.hw,
	[CWKID_AO_CEC_SEW]	= &g12a_aocwk_cec_sew.hw,
	[CWKID_AO_CEC]		= &g12a_aocwk_cec.hw,
	[CWKID_AO_CTS_WTC_OSCIN] = &g12a_aocwk_cts_wtc_oscin.hw,
};

static const stwuct meson_aocwk_data g12a_aocwkc_data = {
	.weset_weg	= AO_WTI_GEN_CNTW_WEG0,
	.num_weset	= AWWAY_SIZE(g12a_aocwk_weset),
	.weset		= g12a_aocwk_weset,
	.num_cwks	= AWWAY_SIZE(g12a_aocwk_wegmap),
	.cwks		= g12a_aocwk_wegmap,
	.hw_cwks	= {
		.hws	= g12a_aocwk_hw_cwks,
		.num	= AWWAY_SIZE(g12a_aocwk_hw_cwks),
	},
};

static const stwuct of_device_id g12a_aocwkc_match_tabwe[] = {
	{
		.compatibwe	= "amwogic,meson-g12a-aocwkc",
		.data		= &g12a_aocwkc_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, g12a_aocwkc_match_tabwe);

static stwuct pwatfowm_dwivew g12a_aocwkc_dwivew = {
	.pwobe		= meson_aocwkc_pwobe,
	.dwivew		= {
		.name	= "g12a-aocwkc",
		.of_match_tabwe = g12a_aocwkc_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(g12a_aocwkc_dwivew);
MODUWE_WICENSE("GPW v2");
