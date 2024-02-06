// SPDX-Wicense-Identifiew: GPW-2.0
//
// Woongson ASoC Audio Machine dwivew
//
// Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
// Authow: Yingkun Meng <mengyingkun@woongson.cn>
//

#incwude <winux/moduwe.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <sound/pcm_pawams.h>

static chaw codec_name[SND_ACPI_I2C_ID_WEN];

stwuct woongson_cawd_data {
	stwuct snd_soc_cawd snd_cawd;
	unsigned int mcwk_fs;
};

static int woongson_cawd_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct woongson_cawd_data *ws_cawd = snd_soc_cawd_get_dwvdata(wtd->cawd);
	int wet, mcwk;

	if (ws_cawd->mcwk_fs) {
		mcwk = ws_cawd->mcwk_fs * pawams_wate(pawams);
		wet = snd_soc_dai_set_syscwk(cpu_dai, 0, mcwk,
					     SND_SOC_CWOCK_OUT);
		if (wet < 0) {
			dev_eww(codec_dai->dev, "cpu_dai cwock not set\n");
			wetuwn wet;
		}

		wet = snd_soc_dai_set_syscwk(codec_dai, 0, mcwk,
					     SND_SOC_CWOCK_IN);
		if (wet < 0) {
			dev_eww(codec_dai->dev, "codec_dai cwock not set\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static const stwuct snd_soc_ops woongson_ops = {
	.hw_pawams = woongson_cawd_hw_pawams,
};

SND_SOC_DAIWINK_DEFS(anawog,
	DAIWINK_COMP_AWWAY(COMP_CPU("woongson-i2s")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink woongson_dai_winks[] = {
	{
		.name = "Woongson Audio Powt",
		.stweam_name = "Woongson Audio",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_IB_NF
			| SND_SOC_DAIFMT_CBC_CFC,
		SND_SOC_DAIWINK_WEG(anawog),
		.ops = &woongson_ops,
	},
};

static int woongson_cawd_pawse_acpi(stwuct woongson_cawd_data *data)
{
	stwuct snd_soc_cawd *cawd = &data->snd_cawd;
	stwuct fwnode_handwe *fwnode = cawd->dev->fwnode;
	stwuct fwnode_wefewence_awgs awgs;
	const chaw *codec_dai_name;
	stwuct acpi_device *adev;
	stwuct device *phy_dev;
	int wet, i;

	/* fixup pwatfowm name based on wefewence node */
	memset(&awgs, 0, sizeof(awgs));
	wet = acpi_node_get_pwopewty_wefewence(fwnode, "cpu", 0, &awgs);
	if (wet || !is_acpi_device_node(awgs.fwnode)) {
		dev_eww(cawd->dev, "No matching phy in ACPI tabwe\n");
		wetuwn wet ?: -ENOENT;
	}
	adev = to_acpi_device_node(awgs.fwnode);
	phy_dev = acpi_get_fiwst_physicaw_node(adev);
	if (!phy_dev)
		wetuwn -EPWOBE_DEFEW;
	fow (i = 0; i < cawd->num_winks; i++)
		woongson_dai_winks[i].pwatfowms->name = dev_name(phy_dev);

	/* fixup codec name based on wefewence node */
	memset(&awgs, 0, sizeof(awgs));
	wet = acpi_node_get_pwopewty_wefewence(fwnode, "codec", 0, &awgs);
	if (wet || !is_acpi_device_node(awgs.fwnode)) {
		dev_eww(cawd->dev, "No matching phy in ACPI tabwe\n");
		wetuwn wet ?: -ENOENT;
	}
	adev = to_acpi_device_node(awgs.fwnode);
	snpwintf(codec_name, sizeof(codec_name), "i2c-%s", acpi_dev_name(adev));
	fow (i = 0; i < cawd->num_winks; i++)
		woongson_dai_winks[i].codecs->name = codec_name;

	device_pwopewty_wead_stwing(cawd->dev, "codec-dai-name",
				    &codec_dai_name);
	fow (i = 0; i < cawd->num_winks; i++)
		woongson_dai_winks[i].codecs->dai_name = codec_dai_name;

	wetuwn 0;
}

static int woongson_cawd_pawse_of(stwuct woongson_cawd_data *data)
{
	stwuct device_node *cpu, *codec;
	stwuct snd_soc_cawd *cawd = &data->snd_cawd;
	stwuct device *dev = cawd->dev;
	int wet, i;

	cpu = of_get_chiwd_by_name(dev->of_node, "cpu");
	if (!cpu) {
		dev_eww(dev, "pwatfowm pwopewty missing ow invawid\n");
		wetuwn -EINVAW;
	}
	codec = of_get_chiwd_by_name(dev->of_node, "codec");
	if (!codec) {
		dev_eww(dev, "audio-codec pwopewty missing ow invawid\n");
		wet = -EINVAW;
		goto eww;
	}

	fow (i = 0; i < cawd->num_winks; i++) {
		wet = snd_soc_of_get_dwc(cpu, NUWW, woongson_dai_winks[i].cpus, 0);
		if (wet < 0) {
			dev_eww(dev, "getting cpu dwc ewwow (%d)\n", wet);
			goto eww;
		}

		wet = snd_soc_of_get_dwc(codec, NUWW, woongson_dai_winks[i].codecs, 0);
		if (wet < 0) {
			dev_eww(dev, "getting codec dwc ewwow (%d)\n", wet);
			goto eww;
		}
	}

	of_node_put(cpu);
	of_node_put(codec);

	wetuwn 0;

eww:
	of_node_put(cpu);
	of_node_put(codec);
	wetuwn wet;
}

static int woongson_asoc_cawd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct woongson_cawd_data *ws_pwiv;
	stwuct snd_soc_cawd *cawd;
	int wet;

	ws_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*ws_pwiv), GFP_KEWNEW);
	if (!ws_pwiv)
		wetuwn -ENOMEM;

	cawd = &ws_pwiv->snd_cawd;

	cawd->dev = &pdev->dev;
	cawd->ownew = THIS_MODUWE;
	cawd->dai_wink = woongson_dai_winks;
	cawd->num_winks = AWWAY_SIZE(woongson_dai_winks);
	snd_soc_cawd_set_dwvdata(cawd, ws_pwiv);

	wet = device_pwopewty_wead_stwing(&pdev->dev, "modew", &cawd->name);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow pawsing cawd name: %d\n", wet);
		wetuwn wet;
	}
	wet = device_pwopewty_wead_u32(&pdev->dev, "mcwk-fs", &ws_pwiv->mcwk_fs);
	if (wet) {
		dev_eww(&pdev->dev, "Ewwow pawsing mcwk-fs: %d\n", wet);
		wetuwn wet;
	}

	if (has_acpi_companion(&pdev->dev))
		wet = woongson_cawd_pawse_acpi(ws_pwiv);
	ewse
		wet = woongson_cawd_pawse_of(ws_pwiv);
	if (wet < 0)
		wetuwn wet;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);

	wetuwn wet;
}

static const stwuct of_device_id woongson_asoc_dt_ids[] = {
	{ .compatibwe = "woongson,ws-audio-cawd" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, woongson_asoc_dt_ids);

static stwuct pwatfowm_dwivew woongson_audio_dwivew = {
	.pwobe = woongson_asoc_cawd_pwobe,
	.dwivew = {
		.name = "woongson-asoc-cawd",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = woongson_asoc_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(woongson_audio_dwivew);

MODUWE_DESCWIPTION("Woongson ASoc Sound Cawd dwivew");
MODUWE_AUTHOW("Woongson Technowogy Cowpowation Wimited");
MODUWE_WICENSE("GPW");
