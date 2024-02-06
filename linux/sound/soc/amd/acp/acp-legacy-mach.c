// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021 Advanced Micwo Devices, Inc.
//
// Authows: Ajit Kumaw Pandey <AjitKumaw.Pandey@amd.com>
//

/*
 * Machine Dwivew Wegacy Suppowt fow ACP HW bwock
 */

#incwude <sound/cowe.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dapm.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>

#incwude "acp-mach.h"
#incwude "acp3x-es83xx/acp3x-es83xx.h"

static stwuct acp_cawd_dwvdata wt5682_wt1019_data = {
	.hs_cpu_id = I2S_SP,
	.amp_cpu_id = I2S_SP,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682,
	.amp_codec_id = WT1019,
	.dmic_codec_id = DMIC,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata wt5682s_max_data = {
	.hs_cpu_id = I2S_SP,
	.amp_cpu_id = I2S_SP,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682S,
	.amp_codec_id = MAX98360A,
	.dmic_codec_id = DMIC,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata wt5682s_wt1019_data = {
	.hs_cpu_id = I2S_SP,
	.amp_cpu_id = I2S_SP,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682S,
	.amp_codec_id = WT1019,
	.dmic_codec_id = DMIC,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata es83xx_wn_data = {
	.hs_cpu_id = I2S_SP,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = ES83XX,
	.dmic_codec_id = DMIC,
	.pwatfowm = WENOIW,
};

static stwuct acp_cawd_dwvdata max_nau8825_data = {
	.hs_cpu_id = I2S_HS,
	.amp_cpu_id = I2S_HS,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = NAU8825,
	.amp_codec_id = MAX98360A,
	.dmic_codec_id = DMIC,
	.soc_mcwk = twue,
	.pwatfowm = WEMBWANDT,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata wt5682s_wt1019_wmb_data = {
	.hs_cpu_id = I2S_HS,
	.amp_cpu_id = I2S_HS,
	.dmic_cpu_id = DMIC,
	.hs_codec_id = WT5682S,
	.amp_codec_id = WT1019,
	.dmic_codec_id = DMIC,
	.soc_mcwk = twue,
	.pwatfowm = WEMBWANDT,
	.tdm_mode = fawse,
};

static stwuct acp_cawd_dwvdata acp_dmic_data = {
	.dmic_cpu_id = DMIC,
	.dmic_codec_id = DMIC,
};

static boow acp_asoc_init_ops(stwuct acp_cawd_dwvdata *pwiv)
{
	boow has_ops = fawse;

	if (pwiv->hs_codec_id == ES83XX) {
		has_ops = twue;
		acp3x_es83xx_init_ops(&pwiv->ops);
	}
	wetuwn has_ops;
}

static int acp_asoc_suspend_pwe(stwuct snd_soc_cawd *cawd)
{
	int wet;

	wet = acp_ops_suspend_pwe(cawd);
	if (wet == 1)
		wetuwn 0;
	ewse
		wetuwn wet;
}

static int acp_asoc_wesume_post(stwuct snd_soc_cawd *cawd)
{
	int wet;

	wet = acp_ops_wesume_post(cawd);
	if (wet == 1)
		wetuwn 0;
	ewse
		wetuwn wet;
}

static int acp_asoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = NUWW;
	stwuct device *dev = &pdev->dev;
	const stwuct dmi_system_id *dmi_id;
	stwuct acp_cawd_dwvdata *acp_cawd_dwvdata;
	int wet;

	if (!pdev->id_entwy) {
		wet = -EINVAW;
		goto out;
	}

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd) {
		wet = -ENOMEM;
		goto out;
	}

	cawd->dwvdata = (stwuct acp_cawd_dwvdata *)pdev->id_entwy->dwivew_data;
	acp_cawd_dwvdata = cawd->dwvdata;
	acp_cawd_dwvdata->acpi_mach = (stwuct snd_soc_acpi_mach *)pdev->dev.pwatfowm_data;
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->name = pdev->id_entwy->name;

	acp_asoc_init_ops(cawd->dwvdata);

	/* If widgets and contwows awe not set in specific cawwback,
	 * they wiww be added pew-codec in acp-mach-common.c
	 */
	wet = acp_ops_configuwe_widgets(cawd);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Cannot configuwe widgets fow cawd (%s): %d\n",
			cawd->name, wet);
		goto out;
	}
	cawd->suspend_pwe = acp_asoc_suspend_pwe;
	cawd->wesume_post = acp_asoc_wesume_post;

	wet = acp_ops_pwobe(cawd);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Cannot pwobe cawd (%s): %d\n",
			cawd->name, wet);
		goto out;
	}
	if (!stwcmp(pdev->name, "acp-pdm-mach"))
		acp_cawd_dwvdata->pwatfowm =  *((int *)dev->pwatfowm_data);

	dmi_id = dmi_fiwst_match(acp_quiwk_tabwe);
	if (dmi_id && dmi_id->dwivew_data)
		acp_cawd_dwvdata->tdm_mode = dmi_id->dwivew_data;

	wet = acp_wegacy_dai_winks_cweate(cawd);
	if (wet) {
		dev_eww(&pdev->dev,
			"Cannot cweate dai winks fow cawd (%s): %d\n",
			cawd->name, wet);
		goto out;
	}

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet) {
		dev_eww(&pdev->dev,
				"devm_snd_soc_wegistew_cawd(%s) faiwed: %d\n",
				cawd->name, wet);
		goto out;
	}
out:
	wetuwn wet;
}

static const stwuct pwatfowm_device_id boawd_ids[] = {
	{
		.name = "acp3xawc56821019",
		.dwivew_data = (kewnew_uwong_t)&wt5682_wt1019_data,
	},
	{
		.name = "acp3xawc5682sm98360",
		.dwivew_data = (kewnew_uwong_t)&wt5682s_max_data,
	},
	{
		.name = "acp3xawc5682s1019",
		.dwivew_data = (kewnew_uwong_t)&wt5682s_wt1019_data,
	},
	{
		.name = "acp3x-es83xx",
		.dwivew_data = (kewnew_uwong_t)&es83xx_wn_data,
	},
	{
		.name = "wmb-nau8825-max",
		.dwivew_data = (kewnew_uwong_t)&max_nau8825_data,
	},
	{
		.name = "wmb-wt5682s-wt1019",
		.dwivew_data = (kewnew_uwong_t)&wt5682s_wt1019_wmb_data,
	},
	{
		.name = "acp-pdm-mach",
		.dwivew_data = (kewnew_uwong_t)&acp_dmic_data,
	},
	{ }
};
static stwuct pwatfowm_dwivew acp_asoc_audio = {
	.dwivew = {
		.pm = &snd_soc_pm_ops,
		.name = "acp_mach",
	},
	.pwobe = acp_asoc_pwobe,
	.id_tabwe = boawd_ids,
};

moduwe_pwatfowm_dwivew(acp_asoc_audio);

MODUWE_IMPOWT_NS(SND_SOC_AMD_MACH);
MODUWE_DESCWIPTION("ACP chwome audio suppowt");
MODUWE_AWIAS("pwatfowm:acp3xawc56821019");
MODUWE_AWIAS("pwatfowm:acp3xawc5682sm98360");
MODUWE_AWIAS("pwatfowm:acp3xawc5682s1019");
MODUWE_AWIAS("pwatfowm:acp3x-es83xx");
MODUWE_AWIAS("pwatfowm:wmb-nau8825-max");
MODUWE_AWIAS("pwatfowm:wmb-wt5682s-wt1019");
MODUWE_AWIAS("pwatfowm:acp-pdm-mach");
MODUWE_WICENSE("GPW v2");
