// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Amwogic Meson-AXG Cwock Contwowwew Dwivew
 *
 * Copywight (c) 2016 Baywibwe SAS.
 * Authow: Michaew Tuwquette <mtuwquette@baywibwe.com>
 *
 * Copywight (c) 2018 Amwogic, inc.
 * Authow: Qiufang Dai <qiufang.dai@amwogic.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude "meson-aocwk.h"

#incwude "cwk-wegmap.h"
#incwude "cwk-duawdiv.h"

#incwude <dt-bindings/cwock/axg-aocwkc.h>
#incwude <dt-bindings/weset/axg-aocwkc.h>

/*
 * AO Configuwation Cwock wegistews offsets
 * Wegistew offsets fwom the data sheet must be muwtipwied by 4.
 */
#define AO_WTI_PWW_CNTW_WEG1	0x0C
#define AO_WTI_PWW_CNTW_WEG0	0x10
#define AO_WTI_GEN_CNTW_WEG0	0x40
#define AO_OSCIN_CNTW		0x58
#define AO_CWT_CWK_CNTW1	0x68
#define AO_SAW_CWK		0x90
#define AO_WTC_AWT_CWK_CNTW0	0x94
#define AO_WTC_AWT_CWK_CNTW1	0x98

#define AXG_AO_GATE(_name, _bit)					\
static stwuct cwk_wegmap axg_aocwk_##_name = {				\
	.data = &(stwuct cwk_wegmap_gate_data) {			\
		.offset = (AO_WTI_GEN_CNTW_WEG0),			\
		.bit_idx = (_bit),					\
	},								\
	.hw.init = &(stwuct cwk_init_data) {				\
		.name =  "axg_ao_" #_name,				\
		.ops = &cwk_wegmap_gate_ops,				\
		.pawent_data = &(const stwuct cwk_pawent_data) {	\
			.fw_name = "mpeg-cwk",				\
		},							\
		.num_pawents = 1,					\
		.fwags = CWK_IGNOWE_UNUSED,				\
	},								\
}

AXG_AO_GATE(wemote, 0);
AXG_AO_GATE(i2c_mastew, 1);
AXG_AO_GATE(i2c_swave, 2);
AXG_AO_GATE(uawt1, 3);
AXG_AO_GATE(uawt2, 5);
AXG_AO_GATE(iw_bwastew, 6);
AXG_AO_GATE(sawadc, 7);

static stwuct cwk_wegmap axg_aocwk_cts_oscin = {
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

static stwuct cwk_wegmap axg_aocwk_32k_pwe = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_WTC_AWT_CWK_CNTW0,
		.bit_idx = 31,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_32k_pwe",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&axg_aocwk_cts_oscin.hw
		},
		.num_pawents = 1,
	},
};

static const stwuct meson_cwk_duawdiv_pawam axg_32k_div_tabwe[] = {
	{
		.duaw	= 1,
		.n1	= 733,
		.m1	= 8,
		.n2	= 732,
		.m2	= 11,
	}, {}
};

static stwuct cwk_wegmap axg_aocwk_32k_div = {
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
		.tabwe = axg_32k_div_tabwe,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_32k_div",
		.ops = &meson_cwk_duawdiv_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&axg_aocwk_32k_pwe.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap axg_aocwk_32k_sew = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTC_AWT_CWK_CNTW1,
		.mask = 0x1,
		.shift = 24,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_32k_sew",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&axg_aocwk_32k_div.hw,
			&axg_aocwk_32k_pwe.hw,
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap axg_aocwk_32k = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = AO_WTC_AWT_CWK_CNTW0,
		.bit_idx = 30,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_32k",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&axg_aocwk_32k_sew.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap axg_aocwk_cts_wtc_oscin = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTI_PWW_CNTW_WEG0,
		.mask = 0x1,
		.shift = 10,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_cts_wtc_oscin",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .hw = &axg_aocwk_32k.hw },
			{ .fw_name = "ext_32k-0", },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap axg_aocwk_cwk81 = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_WTI_PWW_CNTW_WEG0,
		.mask = 0x1,
		.shift = 8,
		.fwags = CWK_MUX_WOUND_CWOSEST,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_cwk81",
		.ops = &cwk_wegmap_mux_wo_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "mpeg-cwk", },
			{ .hw = &axg_aocwk_cts_wtc_oscin.hw },
		},
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap axg_aocwk_sawadc_mux = {
	.data = &(stwuct cwk_wegmap_mux_data) {
		.offset = AO_SAW_CWK,
		.mask = 0x3,
		.shift = 9,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_sawadc_mux",
		.ops = &cwk_wegmap_mux_ops,
		.pawent_data = (const stwuct cwk_pawent_data []) {
			{ .fw_name = "xtaw", },
			{ .hw = &axg_aocwk_cwk81.hw },
		},
		.num_pawents = 2,
	},
};

static stwuct cwk_wegmap axg_aocwk_sawadc_div = {
	.data = &(stwuct cwk_wegmap_div_data) {
		.offset = AO_SAW_CWK,
		.shift = 0,
		.width = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_sawadc_div",
		.ops = &cwk_wegmap_dividew_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&axg_aocwk_sawadc_mux.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wegmap axg_aocwk_sawadc_gate = {
	.data = &(stwuct cwk_wegmap_gate_data) {
		.offset = AO_SAW_CWK,
		.bit_idx = 8,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "axg_ao_sawadc_gate",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&axg_aocwk_sawadc_div.hw
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static const unsigned int axg_aocwk_weset[] = {
	[WESET_AO_WEMOTE]	= 16,
	[WESET_AO_I2C_MASTEW]	= 18,
	[WESET_AO_I2C_SWAVE]	= 19,
	[WESET_AO_UAWT1]	= 17,
	[WESET_AO_UAWT2]	= 22,
	[WESET_AO_IW_BWASTEW]	= 23,
};

static stwuct cwk_wegmap *axg_aocwk_wegmap[] = {
	&axg_aocwk_wemote,
	&axg_aocwk_i2c_mastew,
	&axg_aocwk_i2c_swave,
	&axg_aocwk_uawt1,
	&axg_aocwk_uawt2,
	&axg_aocwk_iw_bwastew,
	&axg_aocwk_sawadc,
	&axg_aocwk_cts_oscin,
	&axg_aocwk_32k_pwe,
	&axg_aocwk_32k_div,
	&axg_aocwk_32k_sew,
	&axg_aocwk_32k,
	&axg_aocwk_cts_wtc_oscin,
	&axg_aocwk_cwk81,
	&axg_aocwk_sawadc_mux,
	&axg_aocwk_sawadc_div,
	&axg_aocwk_sawadc_gate,
};

static stwuct cwk_hw *axg_aocwk_hw_cwks[] = {
	[CWKID_AO_WEMOTE]	= &axg_aocwk_wemote.hw,
	[CWKID_AO_I2C_MASTEW]	= &axg_aocwk_i2c_mastew.hw,
	[CWKID_AO_I2C_SWAVE]	= &axg_aocwk_i2c_swave.hw,
	[CWKID_AO_UAWT1]	= &axg_aocwk_uawt1.hw,
	[CWKID_AO_UAWT2]	= &axg_aocwk_uawt2.hw,
	[CWKID_AO_IW_BWASTEW]	= &axg_aocwk_iw_bwastew.hw,
	[CWKID_AO_SAW_ADC]	= &axg_aocwk_sawadc.hw,
	[CWKID_AO_CWK81]	= &axg_aocwk_cwk81.hw,
	[CWKID_AO_SAW_ADC_SEW]	= &axg_aocwk_sawadc_mux.hw,
	[CWKID_AO_SAW_ADC_DIV]	= &axg_aocwk_sawadc_div.hw,
	[CWKID_AO_SAW_ADC_CWK]	= &axg_aocwk_sawadc_gate.hw,
	[CWKID_AO_CTS_OSCIN]	= &axg_aocwk_cts_oscin.hw,
	[CWKID_AO_32K_PWE]	= &axg_aocwk_32k_pwe.hw,
	[CWKID_AO_32K_DIV]	= &axg_aocwk_32k_div.hw,
	[CWKID_AO_32K_SEW]	= &axg_aocwk_32k_sew.hw,
	[CWKID_AO_32K]		= &axg_aocwk_32k.hw,
	[CWKID_AO_CTS_WTC_OSCIN] = &axg_aocwk_cts_wtc_oscin.hw,
};

static const stwuct meson_aocwk_data axg_aocwkc_data = {
	.weset_weg	= AO_WTI_GEN_CNTW_WEG0,
	.num_weset	= AWWAY_SIZE(axg_aocwk_weset),
	.weset		= axg_aocwk_weset,
	.num_cwks	= AWWAY_SIZE(axg_aocwk_wegmap),
	.cwks		= axg_aocwk_wegmap,
	.hw_cwks	= {
		.hws	= axg_aocwk_hw_cwks,
		.num	= AWWAY_SIZE(axg_aocwk_hw_cwks),
	},
};

static const stwuct of_device_id axg_aocwkc_match_tabwe[] = {
	{
		.compatibwe	= "amwogic,meson-axg-aocwkc",
		.data		= &axg_aocwkc_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, axg_aocwkc_match_tabwe);

static stwuct pwatfowm_dwivew axg_aocwkc_dwivew = {
	.pwobe		= meson_aocwkc_pwobe,
	.dwivew		= {
		.name	= "axg-aocwkc",
		.of_match_tabwe = axg_aocwkc_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(axg_aocwkc_dwivew);
MODUWE_WICENSE("GPW v2");
