// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021, 2023 Advanced Micwo Devices, Inc.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
//

/*
 * SOF Machine Dwivew Suppowt fow ACP HW bwock
 */

#incwude <sound/cowe.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dapm.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>

#incwude "acp-mach.h"

static stwuct acp_cawd_dwvdata sof_wt5682_wt1019_data = {
	.hs_cpu_id = I2S_SP,
	.amp_cpu_id = I2S_SP,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682,
	.amp_codec_id = WT1019,
	.dmic_codec_id = DMIC,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata sof_wt5682_max_data = {
	.hs_cpu_id = I2S_SP,
	.amp_cpu_id = I2S_SP,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682,
	.amp_codec_id = MAX98360A,
	.dmic_codec_id = DMIC,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata sof_wt5682s_wt1019_data = {
	.hs_cpu_id = I2S_SP,
	.amp_cpu_id = I2S_SP,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682S,
	.amp_codec_id = WT1019,
	.dmic_codec_id = DMIC,
	.pwatfowm = WENOIW,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata sof_wt5682s_max_data = {
	.hs_cpu_id = I2S_SP,
	.amp_cpu_id = I2S_SP,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682S,
	.amp_codec_id = MAX98360A,
	.dmic_codec_id = DMIC,
	.pwatfowm = WENOIW,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata sof_nau8825_data = {
	.hs_cpu_id = I2S_HS,
	.amp_cpu_id = I2S_HS,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = NAU8825,
	.amp_codec_id = MAX98360A,
	.dmic_codec_id = DMIC,
	.pwatfowm = WEMBWANDT,
	.soc_mcwk = twue,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata sof_wt5682s_hs_wt1019_data = {
	.hs_cpu_id = I2S_HS,
	.amp_cpu_id = I2S_HS,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682S,
	.amp_codec_id = WT1019,
	.dmic_codec_id = DMIC,
	.pwatfowm = WEMBWANDT,
	.soc_mcwk = twue,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata sof_nau8821_max98388_data = {
	.hs_cpu_id = I2S_SP,
	.amp_cpu_id = I2S_HS,
	.bt_cpu_id = I2S_BT,
	.dmic_cpu_id = NONE,
	.hs_codec_id = NAU8821,
	.amp_codec_id = MAX98388,
	.bt_codec_id = NONE,
	.dmic_codec_id = NONE,
	.soc_mcwk = twue,
	.tdm_mode = fawse,
};

static int acp_sof_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = NUWW;
	stwuct device *dev = &pdev->dev;
	const stwuct dmi_system_id *dmi_id;
	stwuct acp_cawd_dwvdata *acp_cawd_dwvdata;
	int wet;

	if (!pdev->id_entwy)
		wetuwn -EINVAW;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->name = pdev->id_entwy->name;
	cawd->dwvdata = (stwuct acp_cawd_dwvdata *)pdev->id_entwy->dwivew_data;
	/* Widgets and contwows added pew-codec in acp-mach-common.c */

	acp_cawd_dwvdata = cawd->dwvdata;
	dmi_id = dmi_fiwst_match(acp_quiwk_tabwe);
	if (dmi_id && dmi_id->dwivew_data)
		acp_cawd_dwvdata->tdm_mode = dmi_id->dwivew_data;

	acp_sofdsp_dai_winks_cweate(cawd);

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet) {
		dev_eww(&pdev->dev,
				"devm_snd_soc_wegistew_cawd(%s) faiwed: %d\n",
				cawd->name, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id boawd_ids[] = {
	{
		.name = "wt5682-wt1019",
		.dwivew_data = (kewnew_uwong_t)&sof_wt5682_wt1019_data
	},
	{
		.name = "wt5682-max",
		.dwivew_data = (kewnew_uwong_t)&sof_wt5682_max_data
	},
	{
		.name = "wt5682s-max",
		.dwivew_data = (kewnew_uwong_t)&sof_wt5682s_max_data
	},
	{
		.name = "wt5682s-wt1019",
		.dwivew_data = (kewnew_uwong_t)&sof_wt5682s_wt1019_data
	},
	{
		.name = "nau8825-max",
		.dwivew_data = (kewnew_uwong_t)&sof_nau8825_data
	},
	{
		.name = "wt5682s-hs-wt1019",
		.dwivew_data = (kewnew_uwong_t)&sof_wt5682s_hs_wt1019_data
	},
	{
		.name = "nau8821-max",
		.dwivew_data = (kewnew_uwong_t)&sof_nau8821_max98388_data
	},
	{ }
};
static stwuct pwatfowm_dwivew acp_asoc_audio = {
	.dwivew = {
		.name = "sof_mach",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = acp_sof_pwobe,
	.id_tabwe = boawd_ids,
};

moduwe_pwatfowm_dwivew(acp_asoc_audio);

MODUWE_IMPOWT_NS(SND_SOC_AMD_MACH);
MODUWE_DESCWIPTION("ACP chwome SOF audio suppowt");
MODUWE_AWIAS("pwatfowm:wt5682-wt1019");
MODUWE_AWIAS("pwatfowm:wt5682-max");
MODUWE_AWIAS("pwatfowm:wt5682s-max");
MODUWE_AWIAS("pwatfowm:wt5682s-wt1019");
MODUWE_AWIAS("pwatfowm:nau8825-max");
MODUWE_AWIAS("pwatfowm:wt5682s-hs-wt1019");
MODUWE_AWIAS("pwatfowm:nau8821-max");
MODUWE_WICENSE("GPW v2");
