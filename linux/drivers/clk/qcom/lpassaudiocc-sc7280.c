// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,wpass-sc7280.h>
#incwude <dt-bindings/cwock/qcom,wpassaudiocc-sc7280.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_WPASS_AON_CC_PWW_OUT_EVEN,
	P_WPASS_AON_CC_PWW_OUT_MAIN,
	P_WPASS_AON_CC_PWW_OUT_MAIN_CDIV_DIV_CWK_SWC,
	P_WPASS_AON_CC_PWW_OUT_ODD,
	P_WPASS_AUDIO_CC_PWW_OUT_AUX,
	P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC,
	P_WPASS_AUDIO_CC_PWW_MAIN_DIV_CWK,
};

static const stwuct pww_vco zonda_vco[] = {
	{ 595200000UW, 3600000000UW, 0 },
};

static stwuct cwk_bwanch wpass_q6ss_ahbm_cwk = {
	.hawt_weg = 0x901c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x901c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
				.name = "wpass_q6ss_ahbm_cwk",
				.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_q6ss_ahbs_cwk = {
	.hawt_weg = 0x9020,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x9020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_q6ss_ahbs_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* 1128.96MHz configuwation */
static const stwuct awpha_pww_config wpass_audio_cc_pww_config = {
	.w = 0x3a,
	.awpha = 0xcccc,
	.config_ctw_vaw = 0x08200920,
	.config_ctw_hi_vaw = 0x05002001,
	.config_ctw_hi1_vaw = 0x00000000,
	.usew_ctw_vaw = 0x03000101,
};

static stwuct cwk_awpha_pww wpass_audio_cc_pww = {
	.offset = 0x0,
	.vco_tabwe = zonda_vco,
	.num_vco = AWWAY_SIZE(zonda_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_pww",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = 0,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_zonda_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_wpass_audio_cc_pww_out_aux2[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv wpass_audio_cc_pww_out_aux2 = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_wpass_audio_cc_pww_out_aux2,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_wpass_audio_cc_pww_out_aux2),
	.width = 2,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_audio_cc_pww_out_aux2",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_audio_cc_pww.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_zonda_ops,
	},
};

static const stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

/* 614.4 MHz configuwation */
static const stwuct awpha_pww_config wpass_aon_cc_pww_config = {
	.w = 0x20,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00005100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww wpass_aon_cc_pww = {
	.offset = 0x0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_aon_cc_pww",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = 0,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_wpass_aon_cc_pww_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv wpass_aon_cc_pww_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_wpass_aon_cc_pww_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_wpass_aon_cc_pww_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_aon_cc_pww_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_aon_cc_pww.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_wpass_aon_cc_pww_out_odd[] = {
	{ 0x5, 5 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv wpass_aon_cc_pww_out_odd = {
	.offset = 0x0,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_wpass_aon_cc_pww_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_wpass_aon_cc_pww_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_aon_cc_pww_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_aon_cc_pww.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct pawent_map wpass_audio_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_WPASS_AUDIO_CC_PWW_OUT_AUX, 3 },
	{ P_WPASS_AON_CC_PWW_OUT_ODD, 5 },
	{ P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC, 6 },
};

static stwuct cwk_wegmap_div wpass_audio_cc_pww_out_aux2_div_cwk_swc;
static stwuct cwk_wegmap_div wpass_audio_cc_pww_out_main_div_cwk_swc;

static const stwuct cwk_pawent_data wpass_audio_cc_pawent_data_0[] = {
	{ .index = 0 },
	{ .hw = &wpass_audio_cc_pww.cwkw.hw },
	{ .hw = &wpass_aon_cc_pww_out_odd.cwkw.hw },
	{ .hw = &wpass_audio_cc_pww_out_aux2_div_cwk_swc.cwkw.hw },
};

static const stwuct pawent_map wpass_aon_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_WPASS_AON_CC_PWW_OUT_EVEN, 4 },
};

static const stwuct cwk_pawent_data wpass_aon_cc_pawent_data_0[] = {
	{ .index = 0 },
	{ .hw = &wpass_aon_cc_pww_out_even.cwkw.hw },
};

static const stwuct pawent_map wpass_aon_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_WPASS_AON_CC_PWW_OUT_ODD, 1 },
	{ P_WPASS_AUDIO_CC_PWW_MAIN_DIV_CWK, 6 },
};

static const stwuct cwk_pawent_data wpass_aon_cc_pawent_data_1[] = {
	{ .index = 0 },
	{ .hw = &wpass_aon_cc_pww_out_odd.cwkw.hw },
	{ .hw = &wpass_audio_cc_pww_out_main_div_cwk_swc.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_wpass_aon_cc_main_wcg_cwk_swc[] = {
	F(38400000, P_WPASS_AON_CC_PWW_OUT_EVEN, 8, 0, 0),
	F(76800000, P_WPASS_AON_CC_PWW_OUT_EVEN, 4, 0, 0),
	F(153600000, P_WPASS_AON_CC_PWW_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wpass_aon_cc_main_wcg_cwk_swc = {
	.cmd_wcgw = 0x1000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = wpass_aon_cc_pawent_map_0,
	.fweq_tbw = ftbw_wpass_aon_cc_main_wcg_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_aon_cc_main_wcg_cwk_swc",
		.pawent_data = wpass_aon_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(wpass_aon_cc_pawent_data_0),
		.fwags = CWK_OPS_PAWENT_ENABWE,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_wpass_aon_cc_tx_mcwk_wcg_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24576000, P_WPASS_AON_CC_PWW_OUT_ODD, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wpass_aon_cc_tx_mcwk_wcg_cwk_swc = {
	.cmd_wcgw = 0x13004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = wpass_aon_cc_pawent_map_1,
	.fweq_tbw = ftbw_wpass_aon_cc_tx_mcwk_wcg_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_aon_cc_tx_mcwk_wcg_cwk_swc",
		.pawent_data = wpass_aon_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(wpass_aon_cc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_div wpass_audio_cc_pww_out_aux2_div_cwk_swc = {
	.weg = 0x48,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "wpass_audio_cc_pww_out_aux2_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_audio_cc_pww_out_aux2.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div wpass_audio_cc_pww_out_main_div_cwk_swc = {
	.weg = 0x3c,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "wpass_audio_cc_pww_out_main_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_audio_cc_pww.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div wpass_aon_cc_cdiv_tx_mcwk_div_cwk_swc = {
	.weg = 0x13010,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "wpass_aon_cc_cdiv_tx_mcwk_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_aon_cc_tx_mcwk_wcg_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div wpass_aon_cc_pww_out_main_cdiv_div_cwk_swc = {
	.weg = 0x80,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "wpass_aon_cc_pww_out_main_cdiv_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_aon_cc_pww.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static const stwuct fweq_tbw ftbw_wpass_audio_cc_ext_mcwk0_cwk_swc[] = {
	F(256000, P_WPASS_AON_CC_PWW_OUT_ODD, 15, 1, 32),
	F(352800, P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC, 10, 1, 32),
	F(512000, P_WPASS_AON_CC_PWW_OUT_ODD, 15, 1, 16),
	F(705600, P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC, 10, 1, 16),
	F(768000, P_WPASS_AON_CC_PWW_OUT_ODD, 10, 1, 16),
	F(1024000, P_WPASS_AON_CC_PWW_OUT_ODD, 15, 1, 8),
	F(1411200, P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC, 10, 1, 8),
	F(1536000, P_WPASS_AON_CC_PWW_OUT_ODD, 10, 1, 8),
	F(2048000, P_WPASS_AON_CC_PWW_OUT_ODD, 15, 1, 4),
	F(2822400, P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC, 10, 1, 4),
	F(3072000, P_WPASS_AON_CC_PWW_OUT_ODD, 10, 1, 4),
	F(4096000, P_WPASS_AON_CC_PWW_OUT_ODD, 15, 1, 2),
	F(5644800, P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC, 10, 1, 2),
	F(6144000, P_WPASS_AON_CC_PWW_OUT_ODD, 10, 1, 2),
	F(8192000, P_WPASS_AON_CC_PWW_OUT_ODD, 15, 0, 0),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(11289600, P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC, 10, 0, 0),
	F(12288000, P_WPASS_AON_CC_PWW_OUT_ODD, 10, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(22579200, P_WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC, 5, 0, 0),
	F(24576000, P_WPASS_AON_CC_PWW_OUT_ODD, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wpass_audio_cc_ext_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x20004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = wpass_audio_cc_pawent_map_0,
	.fweq_tbw = ftbw_wpass_audio_cc_ext_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_audio_cc_ext_mcwk0_cwk_swc",
		.pawent_data = wpass_audio_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(wpass_audio_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 wpass_audio_cc_ext_mcwk1_cwk_swc = {
	.cmd_wcgw = 0x21004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = wpass_audio_cc_pawent_map_0,
	.fweq_tbw = ftbw_wpass_audio_cc_ext_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_audio_cc_ext_mcwk1_cwk_swc",
		.pawent_data = wpass_audio_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(wpass_audio_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 wpass_audio_cc_wx_mcwk_cwk_swc = {
	.cmd_wcgw = 0x24004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = wpass_audio_cc_pawent_map_0,
	.fweq_tbw = ftbw_wpass_audio_cc_ext_mcwk0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_audio_cc_wx_mcwk_cwk_swc",
		.pawent_data = wpass_audio_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(wpass_audio_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_div wpass_audio_cc_cdiv_wx_mcwk_div_cwk_swc = {
	.weg = 0x240d0,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "wpass_audio_cc_cdiv_wx_mcwk_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_audio_cc_wx_mcwk_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch wpass_aon_cc_audio_hm_h_cwk;

static stwuct cwk_bwanch wpass_audio_cc_codec_mem0_cwk = {
	.hawt_weg = 0x1e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_codec_mem0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_aon_cc_audio_hm_h_cwk.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cc_codec_mem1_cwk = {
	.hawt_weg = 0x1e008,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_codec_mem1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_aon_cc_audio_hm_h_cwk.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cc_codec_mem2_cwk = {
	.hawt_weg = 0x1e00c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_codec_mem2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_aon_cc_audio_hm_h_cwk.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cc_codec_mem_cwk = {
	.hawt_weg = 0x1e000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e000,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_codec_mem_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_aon_cc_audio_hm_h_cwk.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cc_ext_mcwk0_cwk = {
	.hawt_weg = 0x20018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x20018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_ext_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_audio_cc_ext_mcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cc_ext_mcwk1_cwk = {
	.hawt_weg = 0x21018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x21018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_ext_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_audio_cc_ext_mcwk1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cc_wx_mcwk_2x_cwk = {
	.hawt_weg = 0x240cc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x240cc,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_wx_mcwk_2x_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_audio_cc_wx_mcwk_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cc_wx_mcwk_cwk = {
	.hawt_weg = 0x240d4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x240d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_audio_cc_wx_mcwk_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_audio_cc_cdiv_wx_mcwk_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_aon_cc_audio_hm_h_cwk = {
	.hawt_weg = 0x9014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_aon_cc_audio_hm_h_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_aon_cc_main_wcg_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_aon_cc_va_mem0_cwk = {
	.hawt_weg = 0x9028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9028,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_aon_cc_va_mem0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_aon_cc_main_wcg_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_aon_cc_tx_mcwk_2x_cwk = {
	.hawt_weg = 0x1300c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1300c,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_aon_cc_tx_mcwk_2x_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_aon_cc_tx_mcwk_wcg_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_aon_cc_tx_mcwk_cwk = {
	.hawt_weg = 0x13014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x13014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_aon_cc_tx_mcwk_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_aon_cc_cdiv_tx_mcwk_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc wpass_aon_cc_wpass_audio_hm_gdsc = {
	.gdscw = 0x9090,
	.pd = {
		.name = "wpass_aon_cc_wpass_audio_hm_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = WETAIN_FF_ENABWE,
};

static stwuct cwk_wegmap *wpass_cc_sc7280_cwocks[] = {
	[WPASS_Q6SS_AHBM_CWK] = &wpass_q6ss_ahbm_cwk.cwkw,
	[WPASS_Q6SS_AHBS_CWK] = &wpass_q6ss_ahbs_cwk.cwkw,
};

static stwuct cwk_wegmap *wpass_aon_cc_sc7280_cwocks[] = {
	[WPASS_AON_CC_AUDIO_HM_H_CWK] = &wpass_aon_cc_audio_hm_h_cwk.cwkw,
	[WPASS_AON_CC_VA_MEM0_CWK] = &wpass_aon_cc_va_mem0_cwk.cwkw,
	[WPASS_AON_CC_CDIV_TX_MCWK_DIV_CWK_SWC] = &wpass_aon_cc_cdiv_tx_mcwk_div_cwk_swc.cwkw,
	[WPASS_AON_CC_MAIN_WCG_CWK_SWC] = &wpass_aon_cc_main_wcg_cwk_swc.cwkw,
	[WPASS_AON_CC_PWW] = &wpass_aon_cc_pww.cwkw,
	[WPASS_AON_CC_PWW_OUT_EVEN] = &wpass_aon_cc_pww_out_even.cwkw,
	[WPASS_AON_CC_PWW_OUT_MAIN_CDIV_DIV_CWK_SWC] =
		&wpass_aon_cc_pww_out_main_cdiv_div_cwk_swc.cwkw,
	[WPASS_AON_CC_PWW_OUT_ODD] = &wpass_aon_cc_pww_out_odd.cwkw,
	[WPASS_AON_CC_TX_MCWK_2X_CWK] = &wpass_aon_cc_tx_mcwk_2x_cwk.cwkw,
	[WPASS_AON_CC_TX_MCWK_CWK] = &wpass_aon_cc_tx_mcwk_cwk.cwkw,
	[WPASS_AON_CC_TX_MCWK_WCG_CWK_SWC] = &wpass_aon_cc_tx_mcwk_wcg_cwk_swc.cwkw,
};

static stwuct gdsc *wpass_aon_cc_sc7280_gdscs[] = {
	[WPASS_AON_CC_WPASS_AUDIO_HM_GDSC] = &wpass_aon_cc_wpass_audio_hm_gdsc,
};

static stwuct cwk_wegmap *wpass_audio_cc_sc7280_cwocks[] = {
	[WPASS_AUDIO_CC_CDIV_WX_MCWK_DIV_CWK_SWC] = &wpass_audio_cc_cdiv_wx_mcwk_div_cwk_swc.cwkw,
	[WPASS_AUDIO_CC_CODEC_MEM0_CWK] = &wpass_audio_cc_codec_mem0_cwk.cwkw,
	[WPASS_AUDIO_CC_CODEC_MEM1_CWK] = &wpass_audio_cc_codec_mem1_cwk.cwkw,
	[WPASS_AUDIO_CC_CODEC_MEM2_CWK] = &wpass_audio_cc_codec_mem2_cwk.cwkw,
	[WPASS_AUDIO_CC_CODEC_MEM_CWK] = &wpass_audio_cc_codec_mem_cwk.cwkw,
	[WPASS_AUDIO_CC_EXT_MCWK0_CWK] = &wpass_audio_cc_ext_mcwk0_cwk.cwkw,
	[WPASS_AUDIO_CC_EXT_MCWK0_CWK_SWC] = &wpass_audio_cc_ext_mcwk0_cwk_swc.cwkw,
	[WPASS_AUDIO_CC_EXT_MCWK1_CWK] = &wpass_audio_cc_ext_mcwk1_cwk.cwkw,
	[WPASS_AUDIO_CC_EXT_MCWK1_CWK_SWC] = &wpass_audio_cc_ext_mcwk1_cwk_swc.cwkw,
	[WPASS_AUDIO_CC_PWW] = &wpass_audio_cc_pww.cwkw,
	[WPASS_AUDIO_CC_PWW_OUT_AUX2] = &wpass_audio_cc_pww_out_aux2.cwkw,
	[WPASS_AUDIO_CC_PWW_OUT_AUX2_DIV_CWK_SWC] = &wpass_audio_cc_pww_out_aux2_div_cwk_swc.cwkw,
	[WPASS_AUDIO_CC_PWW_OUT_MAIN_DIV_CWK_SWC] = &wpass_audio_cc_pww_out_main_div_cwk_swc.cwkw,
	[WPASS_AUDIO_CC_WX_MCWK_2X_CWK] = &wpass_audio_cc_wx_mcwk_2x_cwk.cwkw,
	[WPASS_AUDIO_CC_WX_MCWK_CWK] = &wpass_audio_cc_wx_mcwk_cwk.cwkw,
	[WPASS_AUDIO_CC_WX_MCWK_CWK_SWC] = &wpass_audio_cc_wx_mcwk_cwk_swc.cwkw,
};

static stwuct wegmap_config wpass_audio_cc_sc7280_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc wpass_cc_sc7280_desc = {
	.config = &wpass_audio_cc_sc7280_wegmap_config,
	.cwks = wpass_cc_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_cc_sc7280_cwocks),
	.gdscs = wpass_aon_cc_sc7280_gdscs,
	.num_gdscs = AWWAY_SIZE(wpass_aon_cc_sc7280_gdscs),
};

static const stwuct qcom_cc_desc wpass_audio_cc_sc7280_desc = {
	.config = &wpass_audio_cc_sc7280_wegmap_config,
	.cwks = wpass_audio_cc_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_audio_cc_sc7280_cwocks),
};

static const stwuct qcom_weset_map wpass_audio_cc_sc7280_wesets[] = {
	[WPASS_AUDIO_SWW_WX_CGCW] =  { 0xa0, 1 },
	[WPASS_AUDIO_SWW_TX_CGCW] =  { 0xa8, 1 },
	[WPASS_AUDIO_SWW_WSA_CGCW] = { 0xb0, 1 },
};

static const stwuct qcom_cc_desc wpass_audio_cc_weset_sc7280_desc = {
	.config = &wpass_audio_cc_sc7280_wegmap_config,
	.wesets = wpass_audio_cc_sc7280_wesets,
	.num_wesets = AWWAY_SIZE(wpass_audio_cc_sc7280_wesets),
};

static const stwuct of_device_id wpass_audio_cc_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-wpassaudiocc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_audio_cc_sc7280_match_tabwe);

static int wpass_audio_setup_wuntime_pm(stwuct pwatfowm_device *pdev)
{
	int wet;

	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 50);
	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = devm_pm_cwk_cweate(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_cwk_add(&pdev->dev, "iface");
	if (wet < 0)
		dev_eww(&pdev->dev, "faiwed to acquiwe iface cwock\n");

	wetuwn pm_wuntime_wesume_and_get(&pdev->dev);
}

static int wpass_audio_cc_sc7280_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;
	stwuct wegmap *wegmap;
	int wet;

	wet = wpass_audio_setup_wuntime_pm(pdev);
	if (wet)
		wetuwn wet;

	wpass_audio_cc_sc7280_wegmap_config.name = "wpassaudio_cc";
	wpass_audio_cc_sc7280_wegmap_config.max_wegistew = 0x2f000;
	desc = &wpass_audio_cc_sc7280_desc;

	wegmap = qcom_cc_map(pdev, desc);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto exit;
	}

	cwk_zonda_pww_configuwe(&wpass_audio_cc_pww, wegmap, &wpass_audio_cc_pww_config);

	/* PWW settings */
	wegmap_wwite(wegmap, 0x4, 0x3b);
	wegmap_wwite(wegmap, 0x8, 0xff05);

	wet = qcom_cc_weawwy_pwobe(pdev, &wpass_audio_cc_sc7280_desc, wegmap);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew WPASS AUDIO CC cwocks\n");
		goto exit;
	}

	wet = qcom_cc_pwobe_by_index(pdev, 1, &wpass_audio_cc_weset_sc7280_desc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew WPASS AUDIO CC Wesets\n");
		goto exit;
	}

	pm_wuntime_mawk_wast_busy(&pdev->dev);
exit:
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops wpass_audio_cc_pm_ops = {
	SET_WUNTIME_PM_OPS(pm_cwk_suspend, pm_cwk_wesume, NUWW)
};

static stwuct pwatfowm_dwivew wpass_audio_cc_sc7280_dwivew = {
	.pwobe = wpass_audio_cc_sc7280_pwobe,
	.dwivew = {
		.name = "wpass_audio_cc-sc7280",
		.of_match_tabwe = wpass_audio_cc_sc7280_match_tabwe,
		.pm = &wpass_audio_cc_pm_ops,
	},
};

static const stwuct qcom_cc_desc wpass_aon_cc_sc7280_desc = {
	.config = &wpass_audio_cc_sc7280_wegmap_config,
	.cwks = wpass_aon_cc_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_aon_cc_sc7280_cwocks),
	.gdscs = wpass_aon_cc_sc7280_gdscs,
	.num_gdscs = AWWAY_SIZE(wpass_aon_cc_sc7280_gdscs),
};

static const stwuct of_device_id wpass_aon_cc_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-wpassaoncc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_aon_cc_sc7280_match_tabwe);

static int wpass_aon_cc_sc7280_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;
	stwuct wegmap *wegmap;
	int wet;

	wet = wpass_audio_setup_wuntime_pm(pdev);
	if (wet)
		wetuwn wet;

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "qcom,adsp-piw-mode")) {
		wpass_audio_cc_sc7280_wegmap_config.name = "cc";
		desc = &wpass_cc_sc7280_desc;
		wet = qcom_cc_pwobe(pdev, desc);
		goto exit;
	}

	wpass_audio_cc_sc7280_wegmap_config.name = "wpasscc_aon";
	wpass_audio_cc_sc7280_wegmap_config.max_wegistew = 0xa0008;
	desc = &wpass_aon_cc_sc7280_desc;

	wegmap = qcom_cc_map(pdev, desc);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto exit;
	}

	cwk_wucid_pww_configuwe(&wpass_aon_cc_pww, wegmap, &wpass_aon_cc_pww_config);

	wet = qcom_cc_weawwy_pwobe(pdev, &wpass_aon_cc_sc7280_desc, wegmap);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew WPASS AON CC cwocks\n");
		goto exit;
	}

	pm_wuntime_mawk_wast_busy(&pdev->dev);
exit:
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew wpass_aon_cc_sc7280_dwivew = {
	.pwobe = wpass_aon_cc_sc7280_pwobe,
	.dwivew = {
		.name = "wpass_aon_cc-sc7280",
		.of_match_tabwe = wpass_aon_cc_sc7280_match_tabwe,
		.pm = &wpass_audio_cc_pm_ops,
	},
};

static int __init wpass_audio_cc_sc7280_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&wpass_aon_cc_sc7280_dwivew);
	if (wet)
		wetuwn wet;

	wetuwn pwatfowm_dwivew_wegistew(&wpass_audio_cc_sc7280_dwivew);
}
subsys_initcaww(wpass_audio_cc_sc7280_init);

static void __exit wpass_audio_cc_sc7280_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wpass_audio_cc_sc7280_dwivew);
	pwatfowm_dwivew_unwegistew(&wpass_aon_cc_sc7280_dwivew);
}
moduwe_exit(wpass_audio_cc_sc7280_exit);

MODUWE_DESCWIPTION("QTI WPASS_AUDIO_CC SC7280 Dwivew");
MODUWE_WICENSE("GPW v2");
