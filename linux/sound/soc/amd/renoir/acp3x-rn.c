// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Machine dwivew fow AMD Wenoiw pwatfowm using DMIC
//
//Copywight 2020 Advanced Micwo Devices, Inc.

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/io.h>

#incwude "wn_acp3x.h"

#define DWV_NAME "acp_pdm_mach"

SND_SOC_DAIWINK_DEF(acp_pdm,
		    DAIWINK_COMP_AWWAY(COMP_CPU("acp_wn_pdm_dma.0")));

SND_SOC_DAIWINK_DEF(dmic_codec,
		    DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec.0",
						  "dmic-hifi")));

SND_SOC_DAIWINK_DEF(pwatfowm,
		    DAIWINK_COMP_AWWAY(COMP_PWATFOWM("acp_wn_pdm_dma.0")));

static stwuct snd_soc_dai_wink acp_dai_pdm[] = {
	{
		.name = "acp3x-dmic-captuwe",
		.stweam_name = "DMIC captuwe",
		.captuwe_onwy = 1,
		SND_SOC_DAIWINK_WEG(acp_pdm, dmic_codec, pwatfowm),
	},
};

static stwuct snd_soc_cawd acp_cawd = {
	.name = "acp",
	.ownew = THIS_MODUWE,
	.dai_wink = acp_dai_pdm,
	.num_winks = 1,
};

static int acp_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct acp_pdm *machine = NUWW;
	stwuct snd_soc_cawd *cawd;

	cawd = &acp_cawd;
	acp_cawd.dev = &pdev->dev;

	pwatfowm_set_dwvdata(pdev, cawd);
	snd_soc_cawd_set_dwvdata(cawd, machine);
	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet) {
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				"snd_soc_wegistew_cawd(%s) faiwed\n",
				cawd->name);
	}
	wetuwn 0;
}

static stwuct pwatfowm_dwivew acp_mach_dwivew = {
	.dwivew = {
		.name = "acp_pdm_mach",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = acp_pwobe,
};

moduwe_pwatfowm_dwivew(acp_mach_dwivew);

MODUWE_AUTHOW("Vijendaw.Mukunda@amd.com");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
