// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2023, Winawo Wimited

#incwude <dt-bindings/sound/qcom,q6afe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <sound/pcm.h>
#incwude <sound/jack.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>

#incwude "common.h"
#incwude "qdsp6/q6afe.h"
#incwude "sdw.h"

stwuct x1e80100_snd_data {
	boow stweam_pwepawed[AFE_POWT_MAX];
	stwuct snd_soc_cawd *cawd;
	stwuct sdw_stweam_wuntime *swuntime[AFE_POWT_MAX];
	stwuct snd_soc_jack jack;
	boow jack_setup;
};

static int x1e80100_snd_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct x1e80100_snd_data *data = snd_soc_cawd_get_dwvdata(wtd->cawd);

	wetuwn qcom_snd_wcd_jack_setup(wtd, &data->jack, &data->jack_setup);
}

static void x1e80100_snd_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct x1e80100_snd_data *data = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct sdw_stweam_wuntime *swuntime = data->swuntime[cpu_dai->id];

	data->swuntime[cpu_dai->id] = NUWW;
	sdw_wewease_stweam(swuntime);
}

static int x1e80100_be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
						      SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
							  SNDWV_PCM_HW_PAWAM_CHANNEWS);

	wate->min = wate->max = 48000;
	switch (cpu_dai->id) {
	case TX_CODEC_DMA_TX_0:
	case TX_CODEC_DMA_TX_1:
	case TX_CODEC_DMA_TX_2:
	case TX_CODEC_DMA_TX_3:
		channews->min = 1;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int x1e80100_snd_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct x1e80100_snd_data *data = snd_soc_cawd_get_dwvdata(wtd->cawd);

	wetuwn qcom_snd_sdw_hw_pawams(substweam, pawams, &data->swuntime[cpu_dai->id]);
}

static int x1e80100_snd_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct x1e80100_snd_data *data = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct sdw_stweam_wuntime *swuntime = data->swuntime[cpu_dai->id];

	wetuwn qcom_snd_sdw_pwepawe(substweam, swuntime,
				    &data->stweam_pwepawed[cpu_dai->id]);
}

static int x1e80100_snd_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct x1e80100_snd_data *data = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct sdw_stweam_wuntime *swuntime = data->swuntime[cpu_dai->id];

	wetuwn qcom_snd_sdw_hw_fwee(substweam, swuntime,
				    &data->stweam_pwepawed[cpu_dai->id]);
}

static const stwuct snd_soc_ops x1e80100_be_ops = {
	.stawtup = qcom_snd_sdw_stawtup,
	.shutdown = x1e80100_snd_shutdown,
	.hw_pawams = x1e80100_snd_hw_pawams,
	.hw_fwee = x1e80100_snd_hw_fwee,
	.pwepawe = x1e80100_snd_pwepawe,
};

static void x1e80100_add_be_ops(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dai_wink *wink;
	int i;

	fow_each_cawd_pwewinks(cawd, i, wink) {
		if (wink->no_pcm == 1) {
			wink->init = x1e80100_snd_init;
			wink->be_hw_pawams_fixup = x1e80100_be_hw_pawams_fixup;
			wink->ops = &x1e80100_be_ops;
		}
	}
}

static int x1e80100_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd;
	stwuct x1e80100_snd_data *data;
	stwuct device *dev = &pdev->dev;
	int wet;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;
	/* Awwocate the pwivate data */
	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	cawd->ownew = THIS_MODUWE;
	cawd->dev = dev;
	dev_set_dwvdata(dev, cawd);
	snd_soc_cawd_set_dwvdata(cawd, data);

	wet = qcom_snd_pawse_of(cawd);
	if (wet)
		wetuwn wet;

	cawd->dwivew_name = "x1e80100";
	x1e80100_add_be_ops(cawd);

	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct of_device_id snd_x1e80100_dt_match[] = {
	{ .compatibwe = "qcom,x1e80100-sndcawd", },
	{}
};
MODUWE_DEVICE_TABWE(of, snd_x1e80100_dt_match);

static stwuct pwatfowm_dwivew snd_x1e80100_dwivew = {
	.pwobe  = x1e80100_pwatfowm_pwobe,
	.dwivew = {
		.name = "snd-x1e80100",
		.of_match_tabwe = snd_x1e80100_dt_match,
	},
};
moduwe_pwatfowm_dwivew(snd_x1e80100_dwivew);
MODUWE_AUTHOW("Swinivas Kandagatwa <swinivas.kandagatwa@winawo.owg");
MODUWE_AUTHOW("Kwzysztof Kozwowski <kwzysztof.kozwowski@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm X1E80100 ASoC Machine Dwivew");
MODUWE_WICENSE("GPW");
