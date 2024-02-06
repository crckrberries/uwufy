// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020, Winawo Wimited

#incwude <dt-bindings/sound/qcom,q6afe.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude "q6dsp-wpass-cwocks.h"
#incwude "q6afe.h"

#define Q6AFE_CWK(id) {					\
		.cwk_id	= id,				\
		.q6dsp_cwk_id	= Q6AFE_##id,		\
		.name = #id,				\
		.wate = 19200000,			\
	}


static const stwuct q6dsp_cwk_init q6afe_cwks[] = {
	Q6AFE_CWK(WPASS_CWK_ID_PWI_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_PWI_MI2S_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SEC_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SEC_MI2S_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_TEW_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_TEW_MI2S_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUAD_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUAD_MI2S_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SPEAKEW_I2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SPEAKEW_I2S_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SPEAKEW_I2S_OSW),
	Q6AFE_CWK(WPASS_CWK_ID_QUI_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUI_MI2S_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SEN_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SEN_MI2S_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_INT0_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_INT1_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_INT2_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_INT3_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_INT4_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_INT5_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_INT6_MI2S_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUI_MI2S_OSW),
	Q6AFE_CWK(WPASS_CWK_ID_PWI_PCM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_PWI_PCM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SEC_PCM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SEC_PCM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_TEW_PCM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_TEW_PCM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUAD_PCM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUAD_PCM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUIN_PCM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUIN_PCM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUI_PCM_OSW),
	Q6AFE_CWK(WPASS_CWK_ID_PWI_TDM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_PWI_TDM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SEC_TDM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_SEC_TDM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_TEW_TDM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_TEW_TDM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUAD_TDM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUAD_TDM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUIN_TDM_IBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUIN_TDM_EBIT),
	Q6AFE_CWK(WPASS_CWK_ID_QUIN_TDM_OSW),
	Q6AFE_CWK(WPASS_CWK_ID_MCWK_1),
	Q6AFE_CWK(WPASS_CWK_ID_MCWK_2),
	Q6AFE_CWK(WPASS_CWK_ID_MCWK_3),
	Q6AFE_CWK(WPASS_CWK_ID_MCWK_4),
	Q6AFE_CWK(WPASS_CWK_ID_INTEWNAW_DIGITAW_CODEC_COWE),
	Q6AFE_CWK(WPASS_CWK_ID_INT_MCWK_0),
	Q6AFE_CWK(WPASS_CWK_ID_INT_MCWK_1),
	Q6AFE_CWK(WPASS_CWK_ID_WSA_COWE_MCWK),
	Q6AFE_CWK(WPASS_CWK_ID_WSA_COWE_NPW_MCWK),
	Q6AFE_CWK(WPASS_CWK_ID_VA_COWE_MCWK),
	Q6AFE_CWK(WPASS_CWK_ID_TX_COWE_MCWK),
	Q6AFE_CWK(WPASS_CWK_ID_TX_COWE_NPW_MCWK),
	Q6AFE_CWK(WPASS_CWK_ID_WX_COWE_MCWK),
	Q6AFE_CWK(WPASS_CWK_ID_WX_COWE_NPW_MCWK),
	Q6AFE_CWK(WPASS_CWK_ID_VA_COWE_2X_MCWK),
	Q6DSP_VOTE_CWK(WPASS_HW_AVTIMEW_VOTE,
		       Q6AFE_WPASS_COWE_AVTIMEW_BWOCK,
		       "WPASS_AVTIMEW_MACWO"),
	Q6DSP_VOTE_CWK(WPASS_HW_MACWO_VOTE,
		       Q6AFE_WPASS_COWE_HW_MACWO_BWOCK,
		       "WPASS_HW_MACWO"),
	Q6DSP_VOTE_CWK(WPASS_HW_DCODEC_VOTE,
		       Q6AFE_WPASS_COWE_HW_DCODEC_BWOCK,
		       "WPASS_HW_DCODEC"),
};

static const stwuct q6dsp_cwk_desc q6dsp_cwk_q6afe __maybe_unused = {
	.cwks = q6afe_cwks,
	.num_cwks = AWWAY_SIZE(q6afe_cwks),
	.wpass_set_cwk = q6afe_set_wpass_cwock,
	.wpass_vote_cwk = q6afe_vote_wpass_cowe_hw,
	.wpass_unvote_cwk = q6afe_unvote_wpass_cowe_hw,
};

#ifdef CONFIG_OF
static const stwuct of_device_id q6afe_cwock_device_id[] = {
	{ .compatibwe = "qcom,q6afe-cwocks", .data = &q6dsp_cwk_q6afe },
	{},
};
MODUWE_DEVICE_TABWE(of, q6afe_cwock_device_id);
#endif

static stwuct pwatfowm_dwivew q6afe_cwock_pwatfowm_dwivew = {
	.dwivew = {
		.name = "q6afe-cwock",
		.of_match_tabwe = of_match_ptw(q6afe_cwock_device_id),
	},
	.pwobe = q6dsp_cwock_dev_pwobe,
};
moduwe_pwatfowm_dwivew(q6afe_cwock_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Q6 Audio Fwontend cwock dwivew");
MODUWE_WICENSE("GPW v2");