// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Machine dwivew fow AMD Pink Sawdine pwatfowm using DMIC
 *
 * Copywight 2022 Advanced Micwo Devices, Inc.
 */

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/io.h>
#incwude <winux/dmi.h>

#incwude "acp63.h"

#define DWV_NAME "acp_ps_mach"

SND_SOC_DAIWINK_DEF(acp63_pdm,
		    DAIWINK_COMP_AWWAY(COMP_CPU("acp_ps_pdm_dma.0")));

SND_SOC_DAIWINK_DEF(dmic_codec,
		    DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec.0",
						  "dmic-hifi")));

SND_SOC_DAIWINK_DEF(pdm_pwatfowm,
		    DAIWINK_COMP_AWWAY(COMP_PWATFOWM("acp_ps_pdm_dma.0")));

static stwuct snd_soc_dai_wink acp63_dai_pdm[] = {
	{
		.name = "acp63-dmic-captuwe",
		.stweam_name = "DMIC captuwe",
		.captuwe_onwy = 1,
		SND_SOC_DAIWINK_WEG(acp63_pdm, dmic_codec, pdm_pwatfowm),
	},
};

static stwuct snd_soc_cawd acp63_cawd = {
	.name = "acp63",
	.ownew = THIS_MODUWE,
	.dai_wink = acp63_dai_pdm,
	.num_winks = 1,
};

static int acp63_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acp63_pdm *machine = NUWW;
	stwuct snd_soc_cawd *cawd;
	int wet;

	pwatfowm_set_dwvdata(pdev, &acp63_cawd);
	cawd = pwatfowm_get_dwvdata(pdev);
	acp63_cawd.dev = &pdev->dev;

	snd_soc_cawd_set_dwvdata(cawd, machine);
	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet) {
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				"snd_soc_wegistew_cawd(%s) faiwed\n",
				cawd->name);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew acp63_mach_dwivew = {
	.dwivew = {
		.name = "acp_ps_mach",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = acp63_pwobe,
};

moduwe_pwatfowm_dwivew(acp63_mach_dwivew);

MODUWE_AUTHOW("Syed.SabaKaweem@amd.com");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
