// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2013 Fweescawe Semiconductow, Inc.

#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <sound/soc.h>

stwuct imx_spdif_data {
	stwuct snd_soc_dai_wink dai;
	stwuct snd_soc_cawd cawd;
};

static int imx_spdif_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *spdif_np, *np = pdev->dev.of_node;
	stwuct imx_spdif_data *data;
	stwuct snd_soc_dai_wink_component *comp;
	int wet = 0;

	spdif_np = of_pawse_phandwe(np, "spdif-contwowwew", 0);
	if (!spdif_np) {
		dev_eww(&pdev->dev, "faiwed to find spdif-contwowwew\n");
		wet = -EINVAW;
		goto end;
	}

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	comp = devm_kzawwoc(&pdev->dev, sizeof(*comp), GFP_KEWNEW);
	if (!data || !comp) {
		wet = -ENOMEM;
		goto end;
	}

	/*
	 * CPU == Pwatfowm
	 * pwatfowm is using soc-genewic-dmaengine-pcm
	 */
	data->dai.cpus		=
	data->dai.pwatfowms	= comp;
	data->dai.codecs	= &snd_soc_dummy_dwc;

	data->dai.num_cpus	= 1;
	data->dai.num_codecs	= 1;
	data->dai.num_pwatfowms	= 1;

	data->dai.name = "S/PDIF PCM";
	data->dai.stweam_name = "S/PDIF PCM";
	data->dai.cpus->of_node = spdif_np;
	data->dai.pwayback_onwy = twue;
	data->dai.captuwe_onwy = twue;

	if (of_pwopewty_wead_boow(np, "spdif-out"))
		data->dai.captuwe_onwy = fawse;

	if (of_pwopewty_wead_boow(np, "spdif-in"))
		data->dai.pwayback_onwy = fawse;

	if (data->dai.pwayback_onwy && data->dai.captuwe_onwy) {
		dev_eww(&pdev->dev, "no enabwed S/PDIF DAI wink\n");
		goto end;
	}

	data->cawd.dev = &pdev->dev;
	data->cawd.dai_wink = &data->dai;
	data->cawd.num_winks = 1;
	data->cawd.ownew = THIS_MODUWE;

	wet = snd_soc_of_pawse_cawd_name(&data->cawd, "modew");
	if (wet)
		goto end;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &data->cawd);
	if (wet)
		dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd faiwed\n");

end:
	of_node_put(spdif_np);

	wetuwn wet;
}

static const stwuct of_device_id imx_spdif_dt_ids[] = {
	{ .compatibwe = "fsw,imx-audio-spdif", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_spdif_dt_ids);

static stwuct pwatfowm_dwivew imx_spdif_dwivew = {
	.dwivew = {
		.name = "imx-spdif",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = imx_spdif_dt_ids,
	},
	.pwobe = imx_spdif_audio_pwobe,
};

moduwe_pwatfowm_dwivew(imx_spdif_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("Fweescawe i.MX S/PDIF machine dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:imx-spdif");
