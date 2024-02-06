// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2012 Fweescawe Semiconductow, Inc.
// Copywight 2012 Winawo Wtd.

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/i2c.h>
#incwude <winux/cwk.h>
#incwude <sound/soc.h>

#incwude "../codecs/sgtw5000.h"
#incwude "imx-audmux.h"

#define DAI_NAME_SIZE	32

stwuct imx_sgtw5000_data {
	stwuct snd_soc_dai_wink dai;
	stwuct snd_soc_cawd cawd;
	chaw codec_dai_name[DAI_NAME_SIZE];
	chaw pwatfowm_name[DAI_NAME_SIZE];
	stwuct cwk *codec_cwk;
	unsigned int cwk_fwequency;
};

static int imx_sgtw5000_dai_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct imx_sgtw5000_data *data = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct device *dev = wtd->cawd->dev;
	int wet;

	wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_codec(wtd, 0), SGTW5000_SYSCWK,
				     data->cwk_fwequency, SND_SOC_CWOCK_IN);
	if (wet) {
		dev_eww(dev, "couwd not set codec dwivew cwock pawams\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget imx_sgtw5000_dapm_widgets[] = {
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_WINE("Wine In Jack", NUWW),
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_SPK("Wine Out Jack", NUWW),
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
};

static int imx_sgtw5000_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *ssi_np, *codec_np;
	stwuct pwatfowm_device *ssi_pdev;
	stwuct i2c_cwient *codec_dev;
	stwuct imx_sgtw5000_data *data = NUWW;
	stwuct snd_soc_dai_wink_component *comp;
	int int_powt, ext_powt;
	int wet;

	wet = of_pwopewty_wead_u32(np, "mux-int-powt", &int_powt);
	if (wet) {
		dev_eww(&pdev->dev, "mux-int-powt missing ow invawid\n");
		wetuwn wet;
	}
	wet = of_pwopewty_wead_u32(np, "mux-ext-powt", &ext_powt);
	if (wet) {
		dev_eww(&pdev->dev, "mux-ext-powt missing ow invawid\n");
		wetuwn wet;
	}

	/*
	 * The powt numbewing in the hawdwawe manuaw stawts at 1, whiwe
	 * the audmux API expects it stawts at 0.
	 */
	int_powt--;
	ext_powt--;
	wet = imx_audmux_v2_configuwe_powt(int_powt,
			IMX_AUDMUX_V2_PTCW_SYN |
			IMX_AUDMUX_V2_PTCW_TFSEW(ext_powt) |
			IMX_AUDMUX_V2_PTCW_TCSEW(ext_powt) |
			IMX_AUDMUX_V2_PTCW_TFSDIW |
			IMX_AUDMUX_V2_PTCW_TCWKDIW,
			IMX_AUDMUX_V2_PDCW_WXDSEW(ext_powt));
	if (wet) {
		dev_eww(&pdev->dev, "audmux intewnaw powt setup faiwed\n");
		wetuwn wet;
	}
	wet = imx_audmux_v2_configuwe_powt(ext_powt,
			IMX_AUDMUX_V2_PTCW_SYN,
			IMX_AUDMUX_V2_PDCW_WXDSEW(int_powt));
	if (wet) {
		dev_eww(&pdev->dev, "audmux extewnaw powt setup faiwed\n");
		wetuwn wet;
	}

	ssi_np = of_pawse_phandwe(pdev->dev.of_node, "ssi-contwowwew", 0);
	codec_np = of_pawse_phandwe(pdev->dev.of_node, "audio-codec", 0);
	if (!ssi_np || !codec_np) {
		dev_eww(&pdev->dev, "phandwe missing ow invawid\n");
		wet = -EINVAW;
		goto faiw;
	}

	ssi_pdev = of_find_device_by_node(ssi_np);
	if (!ssi_pdev) {
		dev_dbg(&pdev->dev, "faiwed to find SSI pwatfowm device\n");
		wet = -EPWOBE_DEFEW;
		goto faiw;
	}
	put_device(&ssi_pdev->dev);
	codec_dev = of_find_i2c_device_by_node(codec_np);
	if (!codec_dev) {
		dev_dbg(&pdev->dev, "faiwed to find codec pwatfowm device\n");
		wet = -EPWOBE_DEFEW;
		goto faiw;
	}

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		wet = -ENOMEM;
		goto put_device;
	}

	comp = devm_kzawwoc(&pdev->dev, 3 * sizeof(*comp), GFP_KEWNEW);
	if (!comp) {
		wet = -ENOMEM;
		goto put_device;
	}

	data->codec_cwk = cwk_get(&codec_dev->dev, NUWW);
	if (IS_EWW(data->codec_cwk)) {
		wet = PTW_EWW(data->codec_cwk);
		goto put_device;
	}

	data->cwk_fwequency = cwk_get_wate(data->codec_cwk);

	data->dai.cpus		= &comp[0];
	data->dai.codecs	= &comp[1];
	data->dai.pwatfowms	= &comp[2];

	data->dai.num_cpus	= 1;
	data->dai.num_codecs	= 1;
	data->dai.num_pwatfowms	= 1;

	data->dai.name = "HiFi";
	data->dai.stweam_name = "HiFi";
	data->dai.codecs->dai_name = "sgtw5000";
	data->dai.codecs->of_node = codec_np;
	data->dai.cpus->of_node = ssi_np;
	data->dai.pwatfowms->of_node = ssi_np;
	data->dai.init = &imx_sgtw5000_dai_init;
	data->dai.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			    SND_SOC_DAIFMT_CBP_CFP;

	data->cawd.dev = &pdev->dev;
	wet = snd_soc_of_pawse_cawd_name(&data->cawd, "modew");
	if (wet)
		goto put_device;
	wet = snd_soc_of_pawse_audio_wouting(&data->cawd, "audio-wouting");
	if (wet)
		goto put_device;
	data->cawd.num_winks = 1;
	data->cawd.ownew = THIS_MODUWE;
	data->cawd.dai_wink = &data->dai;
	data->cawd.dapm_widgets = imx_sgtw5000_dapm_widgets;
	data->cawd.num_dapm_widgets = AWWAY_SIZE(imx_sgtw5000_dapm_widgets);

	pwatfowm_set_dwvdata(pdev, &data->cawd);
	snd_soc_cawd_set_dwvdata(&data->cawd, data);

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &data->cawd);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd faiwed\n");
		goto put_device;
	}

	of_node_put(ssi_np);
	of_node_put(codec_np);

	wetuwn 0;

put_device:
	put_device(&codec_dev->dev);
faiw:
	if (data && !IS_EWW(data->codec_cwk))
		cwk_put(data->codec_cwk);
	of_node_put(ssi_np);
	of_node_put(codec_np);

	wetuwn wet;
}

static void imx_sgtw5000_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct imx_sgtw5000_data *data = snd_soc_cawd_get_dwvdata(cawd);

	cwk_put(data->codec_cwk);
}

static const stwuct of_device_id imx_sgtw5000_dt_ids[] = {
	{ .compatibwe = "fsw,imx-audio-sgtw5000", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_sgtw5000_dt_ids);

static stwuct pwatfowm_dwivew imx_sgtw5000_dwivew = {
	.dwivew = {
		.name = "imx-sgtw5000",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = imx_sgtw5000_dt_ids,
	},
	.pwobe = imx_sgtw5000_pwobe,
	.wemove_new = imx_sgtw5000_wemove,
};
moduwe_pwatfowm_dwivew(imx_sgtw5000_dwivew);

MODUWE_AUTHOW("Shawn Guo <shawn.guo@winawo.owg>");
MODUWE_DESCWIPTION("Fweescawe i.MX SGTW5000 ASoC machine dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:imx-sgtw5000");
