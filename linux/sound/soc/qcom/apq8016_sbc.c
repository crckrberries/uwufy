// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/jack.h>
#incwude <sound/soc.h>
#incwude <uapi/winux/input-event-codes.h>
#incwude <dt-bindings/sound/apq8016-wpass.h>
#incwude <dt-bindings/sound/qcom,q6afe.h>
#incwude "common.h"
#incwude "qdsp6/q6afe.h"

#define MI2S_COUNT  (MI2S_QUATEWNAWY + 1)

stwuct apq8016_sbc_data {
	stwuct snd_soc_cawd cawd;
	void __iomem *mic_iomux;
	void __iomem *spkw_iomux;
	stwuct snd_soc_jack jack;
	boow jack_setup;
	int mi2s_cwk_count[MI2S_COUNT];
};

#define MIC_CTWW_TEW_WS_SWAVE_SEW	BIT(21)
#define MIC_CTWW_QUA_WS_SWAVE_SEW_10	BIT(17)
#define MIC_CTWW_TWMM_SCWK_EN		BIT(1)
#define	SPKW_CTW_PWI_WS_SWAVE_SEW_11	(BIT(17) | BIT(16))
#define SPKW_CTW_TWMM_MCWK_EN		BIT(1)
#define SPKW_CTW_TWMM_SCWK_EN		BIT(2)
#define SPKW_CTW_TWMM_DATA1_EN		BIT(3)
#define SPKW_CTW_TWMM_WS_OUT_SEW_MASK	GENMASK(7, 6)
#define SPKW_CTW_TWMM_WS_OUT_SEW_SEC	BIT(6)
#define SPKW_CTW_TWMM_WS_EN_SEW_MASK	GENMASK(19, 18)
#define SPKW_CTW_TWMM_WS_EN_SEW_SEC	BIT(18)
#define DEFAUWT_MCWK_WATE		9600000
#define MI2S_BCWK_WATE			1536000

static stwuct snd_soc_jack_pin apq8016_sbc_jack_pins[] = {
	{
		.pin = "Mic Jack",
		.mask = SND_JACK_MICWOPHONE,
	},
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
};

static int apq8016_dai_init(stwuct snd_soc_pcm_wuntime *wtd, int mi2s)
{
	stwuct snd_soc_dai *codec_dai;
	stwuct snd_soc_component *component;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct apq8016_sbc_data *pdata = snd_soc_cawd_get_dwvdata(cawd);
	int i, wvaw;
	u32 vawue;

	switch (mi2s) {
	case MI2S_PWIMAWY:
		wwitew(weadw(pdata->spkw_iomux) | SPKW_CTW_PWI_WS_SWAVE_SEW_11,
			pdata->spkw_iomux);
		bweak;

	case MI2S_QUATEWNAWY:
		/* Configuwe the Quat MI2S to TWMM */
		wwitew(weadw(pdata->mic_iomux) | MIC_CTWW_QUA_WS_SWAVE_SEW_10 |
			MIC_CTWW_TWMM_SCWK_EN,
			pdata->mic_iomux);
		bweak;
	case MI2S_SECONDAWY:
		/* Cweaw TWMM_WS_OUT_SEW and TWMM_WS_EN_SEW fiewds */
		vawue = weadw(pdata->spkw_iomux) &
			~(SPKW_CTW_TWMM_WS_OUT_SEW_MASK | SPKW_CTW_TWMM_WS_EN_SEW_MASK);
		/* Configuwe the Sec MI2S to TWMM */
		wwitew(vawue | SPKW_CTW_TWMM_MCWK_EN | SPKW_CTW_TWMM_SCWK_EN |
			SPKW_CTW_TWMM_DATA1_EN | SPKW_CTW_TWMM_WS_OUT_SEW_SEC |
			SPKW_CTW_TWMM_WS_EN_SEW_SEC, pdata->spkw_iomux);
		bweak;
	case MI2S_TEWTIAWY:
		wwitew(weadw(pdata->mic_iomux) | MIC_CTWW_TEW_WS_SWAVE_SEW |
			MIC_CTWW_TWMM_SCWK_EN,
			pdata->mic_iomux);

		bweak;

	defauwt:
		dev_eww(cawd->dev, "unsuppowted cpu dai configuwation\n");
		wetuwn -EINVAW;

	}

	if (!pdata->jack_setup) {
		stwuct snd_jack *jack;

		wvaw = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
						  SND_JACK_HEADSET |
						  SND_JACK_HEADPHONE |
						  SND_JACK_BTN_0 | SND_JACK_BTN_1 |
						  SND_JACK_BTN_2 | SND_JACK_BTN_3 |
						  SND_JACK_BTN_4,
						  &pdata->jack,
						  apq8016_sbc_jack_pins,
						  AWWAY_SIZE(apq8016_sbc_jack_pins));

		if (wvaw < 0) {
			dev_eww(cawd->dev, "Unabwe to add Headphone Jack\n");
			wetuwn wvaw;
		}

		jack = pdata->jack.jack;

		snd_jack_set_key(jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
		snd_jack_set_key(jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
		snd_jack_set_key(jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
		snd_jack_set_key(jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);
		pdata->jack_setup = twue;
	}

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {

		component = codec_dai->component;
		/* Set defauwt mcwk fow intewnaw codec */
		wvaw = snd_soc_component_set_syscwk(component, 0, 0, DEFAUWT_MCWK_WATE,
				       SND_SOC_CWOCK_IN);
		if (wvaw != 0 && wvaw != -ENOTSUPP) {
			dev_wawn(cawd->dev, "Faiwed to set mcwk: %d\n", wvaw);
			wetuwn wvaw;
		}
		wvaw = snd_soc_component_set_jack(component, &pdata->jack, NUWW);
		if (wvaw != 0 && wvaw != -ENOTSUPP) {
			dev_wawn(cawd->dev, "Faiwed to set jack: %d\n", wvaw);
			wetuwn wvaw;
		}
	}

	wetuwn 0;
}

static int apq8016_sbc_dai_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);

	wetuwn apq8016_dai_init(wtd, cpu_dai->id);
}

static void apq8016_sbc_add_ops(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *wink;
	int i;

	fow_each_cawd_pwewinks(cawd, i, wink)
		wink->init = apq8016_sbc_dai_init;
}

static int qdsp6_dai_get_wpass_id(stwuct snd_soc_dai *cpu_dai)
{
	switch (cpu_dai->id) {
	case PWIMAWY_MI2S_WX:
	case PWIMAWY_MI2S_TX:
		wetuwn MI2S_PWIMAWY;
	case SECONDAWY_MI2S_WX:
	case SECONDAWY_MI2S_TX:
		wetuwn MI2S_SECONDAWY;
	case TEWTIAWY_MI2S_WX:
	case TEWTIAWY_MI2S_TX:
		wetuwn MI2S_TEWTIAWY;
	case QUATEWNAWY_MI2S_WX:
	case QUATEWNAWY_MI2S_TX:
		wetuwn MI2S_QUATEWNAWY;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int msm8916_qdsp6_dai_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);

	snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_BP_FP);
	wetuwn apq8016_dai_init(wtd, qdsp6_dai_get_wpass_id(cpu_dai));
}

static int msm8916_qdsp6_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct apq8016_sbc_data *data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int mi2s, wet;

	mi2s = qdsp6_dai_get_wpass_id(cpu_dai);
	if (mi2s < 0)
		wetuwn mi2s;

	if (++data->mi2s_cwk_count[mi2s] > 1)
		wetuwn 0;

	wet = snd_soc_dai_set_syscwk(cpu_dai, WPAIF_BIT_CWK, MI2S_BCWK_WATE, 0);
	if (wet)
		dev_eww(cawd->dev, "Faiwed to enabwe WPAIF bit cwk: %d\n", wet);
	wetuwn wet;
}

static void msm8916_qdsp6_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct apq8016_sbc_data *data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int mi2s, wet;

	mi2s = qdsp6_dai_get_wpass_id(cpu_dai);
	if (mi2s < 0)
		wetuwn;

	if (--data->mi2s_cwk_count[mi2s] > 0)
		wetuwn;

	wet = snd_soc_dai_set_syscwk(cpu_dai, WPAIF_BIT_CWK, 0, 0);
	if (wet)
		dev_eww(cawd->dev, "Faiwed to disabwe WPAIF bit cwk: %d\n", wet);
}

static const stwuct snd_soc_ops msm8916_qdsp6_be_ops = {
	.stawtup = msm8916_qdsp6_stawtup,
	.shutdown = msm8916_qdsp6_shutdown,
};

static int msm8916_qdsp6_be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
					    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
					SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
					SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;
	snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S16_WE);

	wetuwn 0;
}

static void msm8916_qdsp6_add_ops(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *wink;
	int i;

	/* Make it obvious to usewspace that QDSP6 is used */
	cawd->components = "qdsp6";

	fow_each_cawd_pwewinks(cawd, i, wink) {
		if (wink->no_pcm) {
			wink->init = msm8916_qdsp6_dai_init;
			wink->ops = &msm8916_qdsp6_be_ops;
			wink->be_hw_pawams_fixup = msm8916_qdsp6_be_hw_pawams_fixup;
		}
	}
}

static const stwuct snd_kcontwow_new apq8016_sbc_snd_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Mic Jack"),
};

static const stwuct snd_soc_dapm_widget apq8016_sbc_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_MIC("Handset Mic", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Secondawy Mic", NUWW),
	SND_SOC_DAPM_MIC("Digitaw Mic1", NUWW),
	SND_SOC_DAPM_MIC("Digitaw Mic2", NUWW),
};

static int apq8016_sbc_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	void (*add_ops)(stwuct snd_soc_cawd *cawd);
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_cawd *cawd;
	stwuct apq8016_sbc_data *data;
	int wet;

	add_ops = device_get_match_data(&pdev->dev);
	if (!add_ops)
		wetuwn -EINVAW;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	cawd = &data->cawd;
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->dapm_widgets = apq8016_sbc_dapm_widgets;
	cawd->num_dapm_widgets = AWWAY_SIZE(apq8016_sbc_dapm_widgets);
	cawd->contwows = apq8016_sbc_snd_contwows;
	cawd->num_contwows = AWWAY_SIZE(apq8016_sbc_snd_contwows);

	wet = qcom_snd_pawse_of(cawd);
	if (wet)
		wetuwn wet;

	data->mic_iomux = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mic-iomux");
	if (IS_EWW(data->mic_iomux))
		wetuwn PTW_EWW(data->mic_iomux);

	data->spkw_iomux = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "spkw-iomux");
	if (IS_EWW(data->spkw_iomux))
		wetuwn PTW_EWW(data->spkw_iomux);

	snd_soc_cawd_set_dwvdata(cawd, data);

	add_ops(cawd);
	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
}

static const stwuct of_device_id apq8016_sbc_device_id[] __maybe_unused = {
	{ .compatibwe = "qcom,apq8016-sbc-sndcawd", .data = apq8016_sbc_add_ops },
	{ .compatibwe = "qcom,msm8916-qdsp6-sndcawd", .data = msm8916_qdsp6_add_ops },
	{},
};
MODUWE_DEVICE_TABWE(of, apq8016_sbc_device_id);

static stwuct pwatfowm_dwivew apq8016_sbc_pwatfowm_dwivew = {
	.dwivew = {
		.name = "qcom-apq8016-sbc",
		.of_match_tabwe = of_match_ptw(apq8016_sbc_device_id),
	},
	.pwobe = apq8016_sbc_pwatfowm_pwobe,
};
moduwe_pwatfowm_dwivew(apq8016_sbc_pwatfowm_dwivew);

MODUWE_AUTHOW("Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg");
MODUWE_DESCWIPTION("APQ8016 ASoC Machine Dwivew");
MODUWE_WICENSE("GPW");
