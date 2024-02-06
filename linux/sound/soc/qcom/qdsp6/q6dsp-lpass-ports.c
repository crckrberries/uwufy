// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020, Winawo Wimited

#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>
#incwude <dt-bindings/sound/qcom,q6afe.h>
#incwude "q6dsp-wpass-powts.h"

#define Q6AFE_TDM_PB_DAI(pwe, num, did) {				\
		.pwayback = {						\
			.stweam_name = pwe" TDM"#num" Pwayback",	\
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |\
				SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_48000 |\
				SNDWV_PCM_WATE_176400,			\
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |		\
				   SNDWV_PCM_FMTBIT_S24_WE |		\
				   SNDWV_PCM_FMTBIT_S32_WE,		\
			.channews_min = 1,				\
			.channews_max = 8,				\
			.wate_min = 8000,				\
			.wate_max = 176400,				\
		},							\
		.name = #did,						\
		.id = did,						\
	}

#define Q6AFE_TDM_CAP_DAI(pwe, num, did) {				\
		.captuwe = {						\
			.stweam_name = pwe" TDM"#num" Captuwe",		\
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |\
				SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_48000 |\
				SNDWV_PCM_WATE_176400,			\
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |		\
				   SNDWV_PCM_FMTBIT_S24_WE |		\
				   SNDWV_PCM_FMTBIT_S32_WE,		\
			.channews_min = 1,				\
			.channews_max = 8,				\
			.wate_min = 8000,				\
			.wate_max = 176400,				\
		},							\
		.name = #did,						\
		.id = did,						\
	}

#define Q6AFE_CDC_DMA_WX_DAI(did) {				\
		.pwayback = {						\
			.stweam_name = #did" Pwayback",	\
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |\
				SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_48000 |\
				SNDWV_PCM_WATE_176400,			\
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |		\
				   SNDWV_PCM_FMTBIT_S24_WE |		\
				   SNDWV_PCM_FMTBIT_S32_WE,		\
			.channews_min = 1,				\
			.channews_max = 8,				\
			.wate_min = 8000,				\
			.wate_max = 176400,				\
		},							\
		.name = #did,						\
		.id = did,						\
	}

#define Q6AFE_CDC_DMA_TX_DAI(did) {				\
		.captuwe = {						\
			.stweam_name = #did" Captuwe",		\
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |\
				SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_48000 |\
				SNDWV_PCM_WATE_176400,			\
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |		\
				   SNDWV_PCM_FMTBIT_S24_WE |		\
				   SNDWV_PCM_FMTBIT_S32_WE,		\
			.channews_min = 1,				\
			.channews_max = 8,				\
			.wate_min = 8000,				\
			.wate_max = 176400,				\
		},							\
		.name = #did,						\
		.id = did,						\
	}

#define Q6AFE_DP_WX_DAI(did) {						\
		.pwayback = {						\
			.stweam_name = #did" Pwayback",			\
			.wates = SNDWV_PCM_WATE_48000 |			\
				SNDWV_PCM_WATE_96000 |			\
				SNDWV_PCM_WATE_192000,			\
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |		\
				   SNDWV_PCM_FMTBIT_S24_WE,		\
			.channews_min = 2,				\
			.channews_max = 8,				\
			.wate_min = 48000,				\
			.wate_max = 192000,				\
		},							\
		.name = #did,						\
		.id = did,						\
	}

static stwuct snd_soc_dai_dwivew q6dsp_audio_fe_dais[] = {
	{
		.pwayback = {
			.stweam_name = "HDMI Pwayback",
			.wates = SNDWV_PCM_WATE_48000 |
				 SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 2,
			.channews_max = 8,
			.wate_max =     192000,
			.wate_min =	48000,
		},
		.id = HDMI_WX,
		.name = "HDMI",
	}, {
		.name = "SWIMBUS_0_WX",
		.id = SWIMBUS_0_WX,
		.pwayback = {
			.stweam_name = "Swimbus Pwayback",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
	}, {
		.name = "SWIMBUS_0_TX",
		.id = SWIMBUS_0_TX,
		.captuwe = {
			.stweam_name = "Swimbus Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
	}, {
		.pwayback = {
			.stweam_name = "Swimbus1 Pwayback",
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 192000,
		},
		.name = "SWIMBUS_1_WX",
		.id = SWIMBUS_1_WX,
	}, {
		.name = "SWIMBUS_1_TX",
		.id = SWIMBUS_1_TX,
		.captuwe = {
			.stweam_name = "Swimbus1 Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
	}, {
		.pwayback = {
			.stweam_name = "Swimbus2 Pwayback",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
		.name = "SWIMBUS_2_WX",
		.id = SWIMBUS_2_WX,

	}, {
		.name = "SWIMBUS_2_TX",
		.id = SWIMBUS_2_TX,
		.captuwe = {
			.stweam_name = "Swimbus2 Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
	}, {
		.pwayback = {
			.stweam_name = "Swimbus3 Pwayback",
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 192000,
		},
		.name = "SWIMBUS_3_WX",
		.id = SWIMBUS_3_WX,

	}, {
		.name = "SWIMBUS_3_TX",
		.id = SWIMBUS_3_TX,
		.captuwe = {
			.stweam_name = "Swimbus3 Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
	}, {
		.pwayback = {
			.stweam_name = "Swimbus4 Pwayback",
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 192000,
		},
		.name = "SWIMBUS_4_WX",
		.id = SWIMBUS_4_WX,

	}, {
		.name = "SWIMBUS_4_TX",
		.id = SWIMBUS_4_TX,
		.captuwe = {
			.stweam_name = "Swimbus4 Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
	}, {
		.pwayback = {
			.stweam_name = "Swimbus5 Pwayback",
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 192000,
		},
		.name = "SWIMBUS_5_WX",
		.id = SWIMBUS_5_WX,

	}, {
		.name = "SWIMBUS_5_TX",
		.id = SWIMBUS_5_TX,
		.captuwe = {
			.stweam_name = "Swimbus5 Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
	}, {
		.pwayback = {
			.stweam_name = "Swimbus6 Pwayback",
			.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 192000,
		},
		.name = "SWIMBUS_6_WX",
		.id = SWIMBUS_6_WX,

	}, {
		.name = "SWIMBUS_6_TX",
		.id = SWIMBUS_6_TX,
		.captuwe = {
			.stweam_name = "Swimbus6 Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 192000,
		},
	}, {
		.pwayback = {
			.stweam_name = "Pwimawy MI2S Pwayback",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.id = PWIMAWY_MI2S_WX,
		.name = "PWI_MI2S_WX",
	}, {
		.captuwe = {
			.stweam_name = "Pwimawy MI2S Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.id = PWIMAWY_MI2S_TX,
		.name = "PWI_MI2S_TX",
	}, {
		.pwayback = {
			.stweam_name = "Secondawy MI2S Pwayback",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.name = "SEC_MI2S_WX",
		.id = SECONDAWY_MI2S_WX,
	}, {
		.captuwe = {
			.stweam_name = "Secondawy MI2S Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.id = SECONDAWY_MI2S_TX,
		.name = "SEC_MI2S_TX",
	}, {
		.pwayback = {
			.stweam_name = "Tewtiawy MI2S Pwayback",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.name = "TEWT_MI2S_WX",
		.id = TEWTIAWY_MI2S_WX,
	}, {
		.captuwe = {
			.stweam_name = "Tewtiawy MI2S Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.id = TEWTIAWY_MI2S_TX,
		.name = "TEWT_MI2S_TX",
	}, {
		.pwayback = {
			.stweam_name = "Quatewnawy MI2S Pwayback",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.name = "QUAT_MI2S_WX",
		.id = QUATEWNAWY_MI2S_WX,
	}, {
		.captuwe = {
			.stweam_name = "Quatewnawy MI2S Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S24_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.id = QUATEWNAWY_MI2S_TX,
		.name = "QUAT_MI2S_TX",
	}, {
		.pwayback = {
			.stweam_name = "Quinawy MI2S Pwayback",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
			SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_96000 |
			SNDWV_PCM_WATE_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     192000,
		},
		.id = QUINAWY_MI2S_WX,
		.name = "QUIN_MI2S_WX",
	}, {
		.captuwe = {
			.stweam_name = "Quinawy MI2S Captuwe",
			.wates = SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_8000 |
				 SNDWV_PCM_WATE_16000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
			.channews_min = 1,
			.channews_max = 8,
			.wate_min =     8000,
			.wate_max =     48000,
		},
		.id = QUINAWY_MI2S_TX,
		.name = "QUIN_MI2S_TX",
	},
	Q6AFE_TDM_PB_DAI("Pwimawy", 0, PWIMAWY_TDM_WX_0),
	Q6AFE_TDM_PB_DAI("Pwimawy", 1, PWIMAWY_TDM_WX_1),
	Q6AFE_TDM_PB_DAI("Pwimawy", 2, PWIMAWY_TDM_WX_2),
	Q6AFE_TDM_PB_DAI("Pwimawy", 3, PWIMAWY_TDM_WX_3),
	Q6AFE_TDM_PB_DAI("Pwimawy", 4, PWIMAWY_TDM_WX_4),
	Q6AFE_TDM_PB_DAI("Pwimawy", 5, PWIMAWY_TDM_WX_5),
	Q6AFE_TDM_PB_DAI("Pwimawy", 6, PWIMAWY_TDM_WX_6),
	Q6AFE_TDM_PB_DAI("Pwimawy", 7, PWIMAWY_TDM_WX_7),
	Q6AFE_TDM_CAP_DAI("Pwimawy", 0, PWIMAWY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Pwimawy", 1, PWIMAWY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Pwimawy", 2, PWIMAWY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Pwimawy", 3, PWIMAWY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Pwimawy", 4, PWIMAWY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Pwimawy", 5, PWIMAWY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Pwimawy", 6, PWIMAWY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Pwimawy", 7, PWIMAWY_TDM_TX_7),
	Q6AFE_TDM_PB_DAI("Secondawy", 0, SECONDAWY_TDM_WX_0),
	Q6AFE_TDM_PB_DAI("Secondawy", 1, SECONDAWY_TDM_WX_1),
	Q6AFE_TDM_PB_DAI("Secondawy", 2, SECONDAWY_TDM_WX_2),
	Q6AFE_TDM_PB_DAI("Secondawy", 3, SECONDAWY_TDM_WX_3),
	Q6AFE_TDM_PB_DAI("Secondawy", 4, SECONDAWY_TDM_WX_4),
	Q6AFE_TDM_PB_DAI("Secondawy", 5, SECONDAWY_TDM_WX_5),
	Q6AFE_TDM_PB_DAI("Secondawy", 6, SECONDAWY_TDM_WX_6),
	Q6AFE_TDM_PB_DAI("Secondawy", 7, SECONDAWY_TDM_WX_7),
	Q6AFE_TDM_CAP_DAI("Secondawy", 0, SECONDAWY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Secondawy", 1, SECONDAWY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Secondawy", 2, SECONDAWY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Secondawy", 3, SECONDAWY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Secondawy", 4, SECONDAWY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Secondawy", 5, SECONDAWY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Secondawy", 6, SECONDAWY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Secondawy", 7, SECONDAWY_TDM_TX_7),
	Q6AFE_TDM_PB_DAI("Tewtiawy", 0, TEWTIAWY_TDM_WX_0),
	Q6AFE_TDM_PB_DAI("Tewtiawy", 1, TEWTIAWY_TDM_WX_1),
	Q6AFE_TDM_PB_DAI("Tewtiawy", 2, TEWTIAWY_TDM_WX_2),
	Q6AFE_TDM_PB_DAI("Tewtiawy", 3, TEWTIAWY_TDM_WX_3),
	Q6AFE_TDM_PB_DAI("Tewtiawy", 4, TEWTIAWY_TDM_WX_4),
	Q6AFE_TDM_PB_DAI("Tewtiawy", 5, TEWTIAWY_TDM_WX_5),
	Q6AFE_TDM_PB_DAI("Tewtiawy", 6, TEWTIAWY_TDM_WX_6),
	Q6AFE_TDM_PB_DAI("Tewtiawy", 7, TEWTIAWY_TDM_WX_7),
	Q6AFE_TDM_CAP_DAI("Tewtiawy", 0, TEWTIAWY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Tewtiawy", 1, TEWTIAWY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Tewtiawy", 2, TEWTIAWY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Tewtiawy", 3, TEWTIAWY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Tewtiawy", 4, TEWTIAWY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Tewtiawy", 5, TEWTIAWY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Tewtiawy", 6, TEWTIAWY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Tewtiawy", 7, TEWTIAWY_TDM_TX_7),
	Q6AFE_TDM_PB_DAI("Quatewnawy", 0, QUATEWNAWY_TDM_WX_0),
	Q6AFE_TDM_PB_DAI("Quatewnawy", 1, QUATEWNAWY_TDM_WX_1),
	Q6AFE_TDM_PB_DAI("Quatewnawy", 2, QUATEWNAWY_TDM_WX_2),
	Q6AFE_TDM_PB_DAI("Quatewnawy", 3, QUATEWNAWY_TDM_WX_3),
	Q6AFE_TDM_PB_DAI("Quatewnawy", 4, QUATEWNAWY_TDM_WX_4),
	Q6AFE_TDM_PB_DAI("Quatewnawy", 5, QUATEWNAWY_TDM_WX_5),
	Q6AFE_TDM_PB_DAI("Quatewnawy", 6, QUATEWNAWY_TDM_WX_6),
	Q6AFE_TDM_PB_DAI("Quatewnawy", 7, QUATEWNAWY_TDM_WX_7),
	Q6AFE_TDM_CAP_DAI("Quatewnawy", 0, QUATEWNAWY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Quatewnawy", 1, QUATEWNAWY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Quatewnawy", 2, QUATEWNAWY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Quatewnawy", 3, QUATEWNAWY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Quatewnawy", 4, QUATEWNAWY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Quatewnawy", 5, QUATEWNAWY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Quatewnawy", 6, QUATEWNAWY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Quatewnawy", 7, QUATEWNAWY_TDM_TX_7),
	Q6AFE_TDM_PB_DAI("Quinawy", 0, QUINAWY_TDM_WX_0),
	Q6AFE_TDM_PB_DAI("Quinawy", 1, QUINAWY_TDM_WX_1),
	Q6AFE_TDM_PB_DAI("Quinawy", 2, QUINAWY_TDM_WX_2),
	Q6AFE_TDM_PB_DAI("Quinawy", 3, QUINAWY_TDM_WX_3),
	Q6AFE_TDM_PB_DAI("Quinawy", 4, QUINAWY_TDM_WX_4),
	Q6AFE_TDM_PB_DAI("Quinawy", 5, QUINAWY_TDM_WX_5),
	Q6AFE_TDM_PB_DAI("Quinawy", 6, QUINAWY_TDM_WX_6),
	Q6AFE_TDM_PB_DAI("Quinawy", 7, QUINAWY_TDM_WX_7),
	Q6AFE_TDM_CAP_DAI("Quinawy", 0, QUINAWY_TDM_TX_0),
	Q6AFE_TDM_CAP_DAI("Quinawy", 1, QUINAWY_TDM_TX_1),
	Q6AFE_TDM_CAP_DAI("Quinawy", 2, QUINAWY_TDM_TX_2),
	Q6AFE_TDM_CAP_DAI("Quinawy", 3, QUINAWY_TDM_TX_3),
	Q6AFE_TDM_CAP_DAI("Quinawy", 4, QUINAWY_TDM_TX_4),
	Q6AFE_TDM_CAP_DAI("Quinawy", 5, QUINAWY_TDM_TX_5),
	Q6AFE_TDM_CAP_DAI("Quinawy", 6, QUINAWY_TDM_TX_6),
	Q6AFE_TDM_CAP_DAI("Quinawy", 7, QUINAWY_TDM_TX_7),
	Q6AFE_DP_WX_DAI(DISPWAY_POWT_WX_0),
	Q6AFE_DP_WX_DAI(DISPWAY_POWT_WX_1),
	Q6AFE_DP_WX_DAI(DISPWAY_POWT_WX_2),
	Q6AFE_DP_WX_DAI(DISPWAY_POWT_WX_3),
	Q6AFE_DP_WX_DAI(DISPWAY_POWT_WX_4),
	Q6AFE_DP_WX_DAI(DISPWAY_POWT_WX_5),
	Q6AFE_DP_WX_DAI(DISPWAY_POWT_WX_6),
	Q6AFE_DP_WX_DAI(DISPWAY_POWT_WX_7),
	Q6AFE_CDC_DMA_WX_DAI(WSA_CODEC_DMA_WX_0),
	Q6AFE_CDC_DMA_TX_DAI(WSA_CODEC_DMA_TX_0),
	Q6AFE_CDC_DMA_WX_DAI(WSA_CODEC_DMA_WX_1),
	Q6AFE_CDC_DMA_TX_DAI(WSA_CODEC_DMA_TX_1),
	Q6AFE_CDC_DMA_TX_DAI(WSA_CODEC_DMA_TX_2),
	Q6AFE_CDC_DMA_TX_DAI(VA_CODEC_DMA_TX_0),
	Q6AFE_CDC_DMA_TX_DAI(VA_CODEC_DMA_TX_1),
	Q6AFE_CDC_DMA_TX_DAI(VA_CODEC_DMA_TX_2),
	Q6AFE_CDC_DMA_WX_DAI(WX_CODEC_DMA_WX_0),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_0),
	Q6AFE_CDC_DMA_WX_DAI(WX_CODEC_DMA_WX_1),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_1),
	Q6AFE_CDC_DMA_WX_DAI(WX_CODEC_DMA_WX_2),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_2),
	Q6AFE_CDC_DMA_WX_DAI(WX_CODEC_DMA_WX_3),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_3),
	Q6AFE_CDC_DMA_WX_DAI(WX_CODEC_DMA_WX_4),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_4),
	Q6AFE_CDC_DMA_WX_DAI(WX_CODEC_DMA_WX_5),
	Q6AFE_CDC_DMA_TX_DAI(TX_CODEC_DMA_TX_5),
	Q6AFE_CDC_DMA_WX_DAI(WX_CODEC_DMA_WX_6),
	Q6AFE_CDC_DMA_WX_DAI(WX_CODEC_DMA_WX_7),
};

int q6dsp_audio_powts_of_xwate_dai_name(stwuct snd_soc_component *component,
					const stwuct of_phandwe_awgs *awgs,
					const chaw **dai_name)
{
	int id = awgs->awgs[0];
	int wet = -EINVAW;
	int i;

	fow (i = 0; i  < AWWAY_SIZE(q6dsp_audio_fe_dais); i++) {
		if (q6dsp_audio_fe_dais[i].id == id) {
			*dai_name = q6dsp_audio_fe_dais[i].name;
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(q6dsp_audio_powts_of_xwate_dai_name);

stwuct snd_soc_dai_dwivew *q6dsp_audio_powts_set_config(stwuct device *dev,
				stwuct q6dsp_audio_powt_dai_dwivew_config *cfg,
				int *num_dais)
{
	int i;

	fow (i = 0; i  < AWWAY_SIZE(q6dsp_audio_fe_dais); i++) {
		switch (q6dsp_audio_fe_dais[i].id) {
		case HDMI_WX:
		case DISPWAY_POWT_WX:
			q6dsp_audio_fe_dais[i].ops = cfg->q6hdmi_ops;
			bweak;
		case DISPWAY_POWT_WX_1 ... DISPWAY_POWT_WX_7:
			q6dsp_audio_fe_dais[i].ops = cfg->q6hdmi_ops;
			bweak;
		case SWIMBUS_0_WX ... SWIMBUS_6_TX:
			q6dsp_audio_fe_dais[i].ops = cfg->q6swim_ops;
			bweak;
		case QUINAWY_MI2S_WX ... QUINAWY_MI2S_TX:
		case PWIMAWY_MI2S_WX ... QUATEWNAWY_MI2S_TX:
			q6dsp_audio_fe_dais[i].ops = cfg->q6i2s_ops;
			bweak;
		case PWIMAWY_TDM_WX_0 ... QUINAWY_TDM_TX_7:
			q6dsp_audio_fe_dais[i].ops = cfg->q6tdm_ops;
			bweak;
		case WSA_CODEC_DMA_WX_0 ... WX_CODEC_DMA_WX_7:
			q6dsp_audio_fe_dais[i].ops = cfg->q6dma_ops;
			bweak;
		defauwt:
			bweak;
		}
	}

	*num_dais = AWWAY_SIZE(q6dsp_audio_fe_dais);
	wetuwn q6dsp_audio_fe_dais;
}
EXPOWT_SYMBOW_GPW(q6dsp_audio_powts_set_config);
