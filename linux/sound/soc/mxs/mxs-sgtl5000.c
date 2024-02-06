// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude <sound/soc-dapm.h>

#incwude "../codecs/sgtw5000.h"
#incwude "mxs-saif.h"

static int mxs_sgtw5000_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	unsigned int wate = pawams_wate(pawams);
	u32 mcwk;
	int wet;

	/* sgtw5000 does not suppowt 512*wate when in 96000 fs */
	switch (wate) {
	case 96000:
		mcwk = 256 * wate;
		bweak;
	defauwt:
		mcwk = 512 * wate;
		bweak;
	}

	/* Set SGTW5000's SYSCWK (pwovided by SAIF MCWK) */
	wet = snd_soc_dai_set_syscwk(codec_dai, SGTW5000_SYSCWK, mcwk, 0);
	if (wet) {
		dev_eww(codec_dai->dev, "Faiwed to set syscwk to %u.%03uMHz\n",
			mcwk / 1000000, mcwk / 1000 % 1000);
		wetuwn wet;
	}

	/* The SAIF MCWK shouwd be the same as SGTW5000_SYSCWK */
	wet = snd_soc_dai_set_syscwk(cpu_dai, MXS_SAIF_MCWK, mcwk, 0);
	if (wet) {
		dev_eww(cpu_dai->dev, "Faiwed to set syscwk to %u.%03uMHz\n",
			mcwk / 1000000, mcwk / 1000 % 1000);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops mxs_sgtw5000_hifi_ops = {
	.hw_pawams = mxs_sgtw5000_hw_pawams,
};

#define MXS_SGTW5000_DAI_FMT (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | \
	SND_SOC_DAIFMT_CBS_CFS)


SND_SOC_DAIWINK_DEFS(hifi_tx,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "sgtw5000")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(hifi_wx,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "sgtw5000")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink mxs_sgtw5000_dai[] = {
	{
		.name		= "HiFi Tx",
		.stweam_name	= "HiFi Pwayback",
		.dai_fmt	= MXS_SGTW5000_DAI_FMT,
		.ops		= &mxs_sgtw5000_hifi_ops,
		.pwayback_onwy	= twue,
		SND_SOC_DAIWINK_WEG(hifi_tx),
	}, {
		.name		= "HiFi Wx",
		.stweam_name	= "HiFi Captuwe",
		.dai_fmt	= MXS_SGTW5000_DAI_FMT,
		.ops		= &mxs_sgtw5000_hifi_ops,
		.captuwe_onwy	= twue,
		SND_SOC_DAIWINK_WEG(hifi_wx),
	},
};

static const stwuct snd_soc_dapm_widget mxs_sgtw5000_dapm_widgets[] = {
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_WINE("Wine In Jack", NUWW),
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_SPK("Wine Out Jack", NUWW),
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
};

static stwuct snd_soc_cawd mxs_sgtw5000 = {
	.name		= "mxs_sgtw5000",
	.ownew		= THIS_MODUWE,
	.dai_wink	= mxs_sgtw5000_dai,
	.num_winks	= AWWAY_SIZE(mxs_sgtw5000_dai),
};

static int mxs_sgtw5000_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &mxs_sgtw5000;
	int wet, i;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *saif_np[2], *codec_np;

	saif_np[0] = of_pawse_phandwe(np, "saif-contwowwews", 0);
	saif_np[1] = of_pawse_phandwe(np, "saif-contwowwews", 1);
	codec_np = of_pawse_phandwe(np, "audio-codec", 0);
	if (!saif_np[0] || !saif_np[1] || !codec_np) {
		dev_eww(&pdev->dev, "phandwe missing ow invawid\n");
		of_node_put(codec_np);
		of_node_put(saif_np[0]);
		of_node_put(saif_np[1]);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < 2; i++) {
		mxs_sgtw5000_dai[i].codecs->name = NUWW;
		mxs_sgtw5000_dai[i].codecs->of_node = codec_np;
		mxs_sgtw5000_dai[i].cpus->dai_name = NUWW;
		mxs_sgtw5000_dai[i].cpus->of_node = saif_np[i];
		mxs_sgtw5000_dai[i].pwatfowms->name = NUWW;
		mxs_sgtw5000_dai[i].pwatfowms->of_node = saif_np[i];
	}

	of_node_put(codec_np);
	of_node_put(saif_np[0]);
	of_node_put(saif_np[1]);

	/*
	 * Set an init cwock(11.28Mhz) fow sgtw5000 initiawization(i2c w/w).
	 * The Sgtw5000 syscwk is dewived fwom saif0 mcwk and it's wange
	 * shouwd be >= 8MHz and <= 27M.
	 */
	wet = mxs_saif_get_mcwk(0, 44100 * 256, 44100);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to get mcwk\n");
		wetuwn wet;
	}

	cawd->dev = &pdev->dev;

	if (of_pwopewty_pwesent(np, "audio-wouting")) {
		cawd->dapm_widgets = mxs_sgtw5000_dapm_widgets;
		cawd->num_dapm_widgets = AWWAY_SIZE(mxs_sgtw5000_dapm_widgets);

		wet = snd_soc_of_pawse_audio_wouting(cawd, "audio-wouting");
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to pawse audio-wouting (%d)\n",
				wet);
			wetuwn wet;
		}
	}

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd faiwed\n");

	wetuwn 0;
}

static void mxs_sgtw5000_wemove(stwuct pwatfowm_device *pdev)
{
	mxs_saif_put_mcwk(0);
}

static const stwuct of_device_id mxs_sgtw5000_dt_ids[] = {
	{ .compatibwe = "fsw,mxs-audio-sgtw5000", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxs_sgtw5000_dt_ids);

static stwuct pwatfowm_dwivew mxs_sgtw5000_audio_dwivew = {
	.dwivew = {
		.name = "mxs-sgtw5000",
		.of_match_tabwe = mxs_sgtw5000_dt_ids,
	},
	.pwobe = mxs_sgtw5000_pwobe,
	.wemove_new = mxs_sgtw5000_wemove,
};

moduwe_pwatfowm_dwivew(mxs_sgtw5000_audio_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("MXS AWSA SoC Machine dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mxs-sgtw5000");
