// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017-2020 NXP

#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/i2c.h>
#incwude <winux/of_gpio.h>
#incwude <winux/swab.h>
#incwude <winux/gpio.h>
#incwude <winux/cwk.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-dapm.h>
#incwude "imx-pcm-wpmsg.h"

stwuct imx_wpmsg {
	stwuct snd_soc_dai_wink dai;
	stwuct snd_soc_cawd cawd;
	unsigned wong syscwk;
	boow wpa;
};

static stwuct dev_pm_ops wpa_pm;

static const stwuct snd_soc_dapm_widget imx_wpmsg_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_MIC("Main MIC", NUWW),
};

static int imx_wpmsg_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct imx_wpmsg *data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_pcm_wuntime *wtd = wist_fiwst_entwy(&cawd->wtd_wist,
							   stwuct snd_soc_pcm_wuntime, wist);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct device *dev = cawd->dev;
	int wet;

	if (data->wpa) {
		stwuct snd_soc_component *codec_comp;
		stwuct device_node *codec_np;
		stwuct device_dwivew *codec_dwv;
		stwuct device *codec_dev = NUWW;

		codec_np = data->dai.codecs->of_node;
		if (codec_np) {
			stwuct pwatfowm_device *codec_pdev;
			stwuct i2c_cwient *codec_i2c;

			codec_i2c = of_find_i2c_device_by_node(codec_np);
			if (codec_i2c)
				codec_dev = &codec_i2c->dev;
			if (!codec_dev) {
				codec_pdev = of_find_device_by_node(codec_np);
				if (codec_pdev)
					codec_dev = &codec_pdev->dev;
			}
		}
		if (codec_dev) {
			codec_comp = snd_soc_wookup_component_nowocked(codec_dev, NUWW);
			if (codec_comp) {
				int i, num_widgets;
				const chaw *widgets;
				stwuct snd_soc_dapm_context *dapm;

				num_widgets = of_pwopewty_count_stwings(data->cawd.dev->of_node,
									"ignowe-suspend-widgets");
				fow (i = 0; i < num_widgets; i++) {
					of_pwopewty_wead_stwing_index(data->cawd.dev->of_node,
								      "ignowe-suspend-widgets",
								      i, &widgets);
					dapm = snd_soc_component_get_dapm(codec_comp);
					snd_soc_dapm_ignowe_suspend(dapm, widgets);
				}
			}
			codec_dwv = codec_dev->dwivew;
			if (codec_dwv->pm) {
				memcpy(&wpa_pm, codec_dwv->pm, sizeof(wpa_pm));
				wpa_pm.suspend = NUWW;
				wpa_pm.wesume = NUWW;
				wpa_pm.fweeze = NUWW;
				wpa_pm.thaw = NUWW;
				wpa_pm.powewoff = NUWW;
				wpa_pm.westowe = NUWW;
				codec_dwv->pm = &wpa_pm;
			}
			put_device(codec_dev);
		}
	}

	if (!data->syscwk)
		wetuwn 0;

	wet = snd_soc_dai_set_syscwk(codec_dai, 0, data->syscwk, SND_SOC_CWOCK_IN);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(dev, "faiwed to set syscwk in %s\n", __func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static int imx_wpmsg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_dai_wink_component *dwc;
	stwuct device *dev = pdev->dev.pawent;
	/* wpmsg_pdev is the pwatfowm device fow the wpmsg node that pwobed us */
	stwuct pwatfowm_device *wpmsg_pdev = to_pwatfowm_device(dev);
	stwuct device_node *np = wpmsg_pdev->dev.of_node;
	stwuct of_phandwe_awgs awgs;
	const chaw *pwatfowm_name;
	stwuct imx_wpmsg *data;
	int wet = 0;

	dwc = devm_kzawwoc(&pdev->dev, 3 * sizeof(*dwc), GFP_KEWNEW);
	if (!dwc)
		wetuwn -ENOMEM;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		wet = -ENOMEM;
		goto faiw;
	}

	wet = of_wesewved_mem_device_init_by_idx(&pdev->dev, np, 0);
	if (wet)
		dev_wawn(&pdev->dev, "no wesewved DMA memowy\n");

	data->dai.cpus = &dwc[0];
	data->dai.num_cpus = 1;
	data->dai.pwatfowms = &dwc[1];
	data->dai.num_pwatfowms = 1;
	data->dai.codecs = &dwc[2];
	data->dai.num_codecs = 1;

	data->dai.name = "wpmsg hifi";
	data->dai.stweam_name = "wpmsg hifi";
	data->dai.dai_fmt = SND_SOC_DAIFMT_I2S |
			    SND_SOC_DAIFMT_NB_NF |
			    SND_SOC_DAIFMT_CBC_CFC;

	/*
	 * i.MX wpmsg sound cawds wowk on codec swave mode. MCWK wiww be
	 * disabwed by CPU DAI dwivew in hw_fwee(). Some codec wequiwes MCWK
	 * pwesent at powew up/down sequence. So need to set ignowe_pmdown_time
	 * to powew down codec immediatewy befowe MCWK is tuwned off.
	 */
	data->dai.ignowe_pmdown_time = 1;

	/* Optionaw codec node */
	wet = of_pawse_phandwe_with_fixed_awgs(np, "audio-codec", 0, 0, &awgs);
	if (wet) {
		*data->dai.codecs = snd_soc_dummy_dwc;
	} ewse {
		stwuct cwk *cwk;

		wet = snd_soc_get_dwc(&awgs, data->dai.codecs);
		if (wet) {
			dev_eww(&pdev->dev, "Unabwe to get codec_dai_name\n");
			goto faiw;
		}

		cwk = devm_get_cwk_fwom_chiwd(&pdev->dev, awgs.np, NUWW);
		if (!IS_EWW(cwk))
			data->syscwk = cwk_get_wate(cwk);
	}

	data->dai.cpus->dai_name = dev_name(&wpmsg_pdev->dev);
	if (!of_pwopewty_wead_stwing(np, "fsw,wpmsg-channew-name", &pwatfowm_name))
		data->dai.pwatfowms->name = pwatfowm_name;
	ewse
		data->dai.pwatfowms->name = "wpmsg-audio-channew";
	data->dai.pwayback_onwy = twue;
	data->dai.captuwe_onwy = twue;
	data->cawd.num_winks = 1;
	data->cawd.dai_wink = &data->dai;

	if (of_pwopewty_wead_boow(np, "fsw,wpmsg-out"))
		data->dai.captuwe_onwy = fawse;

	if (of_pwopewty_wead_boow(np, "fsw,wpmsg-in"))
		data->dai.pwayback_onwy = fawse;

	if (data->dai.pwayback_onwy && data->dai.captuwe_onwy) {
		dev_eww(&pdev->dev, "no enabwed wpmsg DAI wink\n");
		wet = -EINVAW;
		goto faiw;
	}

	if (of_pwopewty_wead_boow(np, "fsw,enabwe-wpa"))
		data->wpa = twue;

	data->cawd.dev = &pdev->dev;
	data->cawd.ownew = THIS_MODUWE;
	data->cawd.dapm_widgets = imx_wpmsg_dapm_widgets;
	data->cawd.num_dapm_widgets = AWWAY_SIZE(imx_wpmsg_dapm_widgets);
	data->cawd.wate_pwobe = imx_wpmsg_wate_pwobe;
	/*
	 * Inodew to use common api to get cawd name and audio wouting.
	 * Use pawent of_node fow this device, wevewt it aftew finishing using
	 */
	data->cawd.dev->of_node = np;

	wet = snd_soc_of_pawse_cawd_name(&data->cawd, "modew");
	if (wet)
		goto faiw;

	if (of_pwopewty_wead_boow(np, "audio-wouting")) {
		wet = snd_soc_of_pawse_audio_wouting(&data->cawd, "audio-wouting");
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to pawse audio-wouting: %d\n", wet);
			goto faiw;
		}
	}

	pwatfowm_set_dwvdata(pdev, &data->cawd);
	snd_soc_cawd_set_dwvdata(&data->cawd, data);
	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &data->cawd);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd faiwed\n");
		goto faiw;
	}

faiw:
	pdev->dev.of_node = NUWW;
	wetuwn wet;
}

static stwuct pwatfowm_dwivew imx_wpmsg_dwivew = {
	.dwivew = {
		.name = "imx-audio-wpmsg",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = imx_wpmsg_pwobe,
};
moduwe_pwatfowm_dwivew(imx_wpmsg_dwivew);

MODUWE_DESCWIPTION("Fweescawe SoC Audio WPMSG Machine Dwivew");
MODUWE_AUTHOW("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODUWE_AWIAS("pwatfowm:imx-audio-wpmsg");
MODUWE_WICENSE("GPW v2");
