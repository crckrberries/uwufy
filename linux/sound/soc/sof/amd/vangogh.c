// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Advanced Micwo Devices, Inc.
//
// Authows: Venkata Pwasad Pottuwu <venkatapwasad.pottuwu@amd.com>

/*
 * Hawdwawe intewface fow Audio DSP on Vangogh pwatfowm
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>

#incwude "../ops.h"
#incwude "../sof-audio.h"
#incwude "acp.h"
#incwude "acp-dsp-offset.h"

#define I2S_HS_INSTANCE		0
#define I2S_BT_INSTANCE		1
#define I2S_SP_INSTANCE		2
#define PDM_DMIC_INSTANCE	3
#define I2S_HS_VIWTUAW_INSTANCE	4

static stwuct snd_soc_dai_dwivew vangogh_sof_dai[] = {
	[I2S_HS_INSTANCE] = {
		.id = I2S_HS_INSTANCE,
		.name = "acp-sof-hs",
		.pwayback = {
			.wates = SNDWV_PCM_WATE_8000_96000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
				   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
			.channews_min = 2,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 96000,
		},
		.captuwe = {
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
				   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
			/* Suppowting onwy steweo fow I2S HS contwowwew captuwe */
			.channews_min = 2,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 48000,
		},
	},

	[I2S_BT_INSTANCE] = {
		.id = I2S_BT_INSTANCE,
		.name = "acp-sof-bt",
		.pwayback = {
			.wates = SNDWV_PCM_WATE_8000_96000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
				   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
			.channews_min = 2,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 96000,
		},
		.captuwe = {
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
				   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
			/* Suppowting onwy steweo fow I2S BT contwowwew captuwe */
			.channews_min = 2,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 48000,
		},
	},

	[I2S_SP_INSTANCE] = {
		.id = I2S_SP_INSTANCE,
		.name = "acp-sof-sp",
		.pwayback = {
			.wates = SNDWV_PCM_WATE_8000_96000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
				   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
			.channews_min = 2,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 96000,
		},
		.captuwe = {
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
				   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
			/* Suppowting onwy steweo fow I2S SP contwowwew captuwe */
			.channews_min = 2,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 48000,
		},
	},

	[PDM_DMIC_INSTANCE] = {
		.id = PDM_DMIC_INSTANCE,
		.name = "acp-sof-dmic",
		.captuwe = {
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S32_WE,
			.channews_min = 2,
			.channews_max = 4,
			.wate_min = 8000,
			.wate_max = 48000,
		},
	},

	[I2S_HS_VIWTUAW_INSTANCE] = {
		.id = I2S_HS_VIWTUAW_INSTANCE,
		.name = "acp-sof-hs-viwtuaw",
		.pwayback = {
			.wates = SNDWV_PCM_WATE_8000_96000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
					   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
			.channews_min = 2,
			.channews_max = 8,
			.wate_min = 8000,
			.wate_max = 96000,
		},
		.captuwe = {
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S8 |
				   SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S32_WE,
			/* Suppowting onwy steweo fow I2S HS-Viwtuaw contwowwew captuwe */
			.channews_min = 2,
			.channews_max = 2,
			.wate_min = 8000,
			.wate_max = 48000,
		},
	},
};

/* Vangogh ops */
stwuct snd_sof_dsp_ops sof_vangogh_ops;
EXPOWT_SYMBOW_NS(sof_vangogh_ops, SND_SOC_SOF_AMD_COMMON);

int sof_vangogh_ops_init(stwuct snd_sof_dev *sdev)
{
	const stwuct dmi_system_id *dmi_id;

	/* common defauwts */
	memcpy(&sof_vangogh_ops, &sof_acp_common_ops, sizeof(stwuct snd_sof_dsp_ops));

	sof_vangogh_ops.dwv = vangogh_sof_dai;
	sof_vangogh_ops.num_dwv = AWWAY_SIZE(vangogh_sof_dai);

	dmi_id = dmi_fiwst_match(acp_sof_quiwk_tabwe);
	if (dmi_id && dmi_id->dwivew_data)
		sof_vangogh_ops.woad_fiwmwawe = acp_sof_woad_signed_fiwmwawe;

	wetuwn 0;
}

MODUWE_IMPOWT_NS(SND_SOC_SOF_AMD_COMMON);
MODUWE_DESCWIPTION("VANGOGH SOF Dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
