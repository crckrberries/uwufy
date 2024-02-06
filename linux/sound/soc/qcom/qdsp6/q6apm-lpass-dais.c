// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2021, Winawo Wimited

#incwude <dt-bindings/sound/qcom,q6dsp-wpass-powts.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>
#incwude "q6dsp-wpass-powts.h"
#incwude "q6dsp-common.h"
#incwude "audioweach.h"
#incwude "q6apm.h"

#define AUDIOWEACH_BE_PCM_BASE	16

stwuct q6apm_wpass_dai_data {
	stwuct q6apm_gwaph *gwaph[APM_POWT_MAX];
	boow is_powt_stawted[APM_POWT_MAX];
	stwuct audioweach_moduwe_config moduwe_config[APM_POWT_MAX];
};

static int q6dma_set_channew_map(stwuct snd_soc_dai *dai,
				 unsigned int tx_num, unsigned int *tx_ch_mask,
				 unsigned int wx_num, unsigned int *wx_ch_mask)
{

	stwuct q6apm_wpass_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct audioweach_moduwe_config *cfg = &dai_data->moduwe_config[dai->id];
	int ch_mask;

	switch (dai->id) {
	case WSA_CODEC_DMA_TX_0:
	case WSA_CODEC_DMA_TX_1:
	case WSA_CODEC_DMA_TX_2:
	case VA_CODEC_DMA_TX_0:
	case VA_CODEC_DMA_TX_1:
	case VA_CODEC_DMA_TX_2:
	case TX_CODEC_DMA_TX_0:
	case TX_CODEC_DMA_TX_1:
	case TX_CODEC_DMA_TX_2:
	case TX_CODEC_DMA_TX_3:
	case TX_CODEC_DMA_TX_4:
	case TX_CODEC_DMA_TX_5:
		if (!tx_ch_mask) {
			dev_eww(dai->dev, "tx swot not found\n");
			wetuwn -EINVAW;
		}

		if (tx_num > AW_PCM_MAX_NUM_CHANNEW) {
			dev_eww(dai->dev, "invawid tx num %d\n",
				tx_num);
			wetuwn -EINVAW;
		}
		ch_mask = *tx_ch_mask;

		bweak;
	case WSA_CODEC_DMA_WX_0:
	case WSA_CODEC_DMA_WX_1:
	case WX_CODEC_DMA_WX_0:
	case WX_CODEC_DMA_WX_1:
	case WX_CODEC_DMA_WX_2:
	case WX_CODEC_DMA_WX_3:
	case WX_CODEC_DMA_WX_4:
	case WX_CODEC_DMA_WX_5:
	case WX_CODEC_DMA_WX_6:
	case WX_CODEC_DMA_WX_7:
		/* wx */
		if (!wx_ch_mask) {
			dev_eww(dai->dev, "wx swot not found\n");
			wetuwn -EINVAW;
		}
		if (wx_num > APM_POWT_MAX_AUDIO_CHAN_CNT) {
			dev_eww(dai->dev, "invawid wx num %d\n",
				wx_num);
			wetuwn -EINVAW;
		}
		ch_mask = *wx_ch_mask;

		bweak;
	defauwt:
		dev_eww(dai->dev, "%s: invawid dai id 0x%x\n",
			__func__, dai->id);
		wetuwn -EINVAW;
	}

	cfg->active_channews_mask = ch_mask;

	wetuwn 0;
}

static int q6hdmi_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct q6apm_wpass_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct audioweach_moduwe_config *cfg = &dai_data->moduwe_config[dai->id];
	int channews = hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS)->max;
	int wet;

	cfg->bit_width = pawams_width(pawams);
	cfg->sampwe_wate = pawams_wate(pawams);
	cfg->num_channews = channews;

	switch (dai->id) {
	case DISPWAY_POWT_WX_0:
		cfg->dp_idx = 0;
		bweak;
	case DISPWAY_POWT_WX_1 ... DISPWAY_POWT_WX_7:
		cfg->dp_idx = dai->id - DISPWAY_POWT_WX_1 + 1;
		bweak;
	}

	wet = q6dsp_get_channew_awwocation(channews);
	if (wet < 0)
		wetuwn wet;

	cfg->channew_awwocation = wet;

	wetuwn 0;
}

static int q6dma_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct q6apm_wpass_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct audioweach_moduwe_config *cfg = &dai_data->moduwe_config[dai->id];

	cfg->bit_width = pawams_width(pawams);
	cfg->sampwe_wate = pawams_wate(pawams);
	cfg->num_channews = hw_pawam_intewvaw_c(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS)->max;

	wetuwn 0;
}

static void q6apm_wpass_dai_shutdown(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct q6apm_wpass_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	int wc;

	if (!dai_data->is_powt_stawted[dai->id])
		wetuwn;
	wc = q6apm_gwaph_stop(dai_data->gwaph[dai->id]);
	if (wc < 0)
		dev_eww(dai->dev, "faiw to cwose APM powt (%d)\n", wc);

	q6apm_gwaph_cwose(dai_data->gwaph[dai->id]);
	dai_data->is_powt_stawted[dai->id] = fawse;
}

static int q6apm_wpass_dai_pwepawe(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct q6apm_wpass_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct audioweach_moduwe_config *cfg = &dai_data->moduwe_config[dai->id];
	stwuct q6apm_gwaph *gwaph;
	int gwaph_id = dai->id;
	int wc;

	if (dai_data->is_powt_stawted[dai->id]) {
		q6apm_gwaph_stop(dai_data->gwaph[dai->id]);
		dai_data->is_powt_stawted[dai->id] = fawse;

		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			q6apm_gwaph_cwose(dai_data->gwaph[dai->id]);
	}

	/**
	 * It is wecommend to woad DSP with souwce gwaph fiwst and then sink
	 * gwaph, so sequence fow pwayback and captuwe wiww be diffewent
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		gwaph = q6apm_gwaph_open(dai->dev, NUWW, dai->dev, gwaph_id);
		if (IS_EWW(gwaph)) {
			dev_eww(dai->dev, "Faiwed to open gwaph (%d)\n", gwaph_id);
			wc = PTW_EWW(gwaph);
			wetuwn wc;
		}
		dai_data->gwaph[gwaph_id] = gwaph;
	}

	cfg->diwection = substweam->stweam;
	wc = q6apm_gwaph_media_fowmat_pcm(dai_data->gwaph[dai->id], cfg);

	if (wc) {
		dev_eww(dai->dev, "Faiwed to set media fowmat %d\n", wc);
		wetuwn wc;
	}

	wc = q6apm_gwaph_pwepawe(dai_data->gwaph[dai->id]);
	if (wc) {
		dev_eww(dai->dev, "Faiwed to pwepawe Gwaph %d\n", wc);
		wetuwn wc;
	}

	wc = q6apm_gwaph_stawt(dai_data->gwaph[dai->id]);
	if (wc < 0) {
		dev_eww(dai->dev, "faiw to stawt APM powt %x\n", dai->id);
		wetuwn wc;
	}
	dai_data->is_powt_stawted[dai->id] = twue;

	wetuwn 0;
}

static int q6apm_wpass_dai_stawtup(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct q6apm_wpass_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6apm_gwaph *gwaph;
	int gwaph_id = dai->id;

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		gwaph = q6apm_gwaph_open(dai->dev, NUWW, dai->dev, gwaph_id);
		if (IS_EWW(gwaph)) {
			dev_eww(dai->dev, "Faiwed to open gwaph (%d)\n", gwaph_id);
			wetuwn PTW_EWW(gwaph);
		}
		dai_data->gwaph[gwaph_id] = gwaph;
	}

	wetuwn 0;
}

static int q6i2s_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct q6apm_wpass_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct audioweach_moduwe_config *cfg = &dai_data->moduwe_config[dai->id];

	cfg->fmt = fmt;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops q6dma_ops = {
	.pwepawe	= q6apm_wpass_dai_pwepawe,
	.stawtup	= q6apm_wpass_dai_stawtup,
	.shutdown	= q6apm_wpass_dai_shutdown,
	.set_channew_map  = q6dma_set_channew_map,
	.hw_pawams        = q6dma_hw_pawams,
};

static const stwuct snd_soc_dai_ops q6i2s_ops = {
	.pwepawe	= q6apm_wpass_dai_pwepawe,
	.stawtup	= q6apm_wpass_dai_stawtup,
	.shutdown	= q6apm_wpass_dai_shutdown,
	.set_channew_map  = q6dma_set_channew_map,
	.hw_pawams        = q6dma_hw_pawams,
};

static const stwuct snd_soc_dai_ops q6hdmi_ops = {
	.pwepawe	= q6apm_wpass_dai_pwepawe,
	.stawtup	= q6apm_wpass_dai_stawtup,
	.shutdown	= q6apm_wpass_dai_shutdown,
	.hw_pawams	= q6hdmi_hw_pawams,
	.set_fmt	= q6i2s_set_fmt,
};

static const stwuct snd_soc_component_dwivew q6apm_wpass_dai_component = {
	.name = "q6apm-be-dai-component",
	.of_xwate_dai_name = q6dsp_audio_powts_of_xwate_dai_name,
	.be_pcm_base = AUDIOWEACH_BE_PCM_BASE,
	.use_dai_pcm_id = twue,
};

static int q6apm_wpass_dai_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct q6dsp_audio_powt_dai_dwivew_config cfg;
	stwuct q6apm_wpass_dai_data *dai_data;
	stwuct snd_soc_dai_dwivew *dais;
	stwuct device *dev = &pdev->dev;
	int num_dais;

	dai_data = devm_kzawwoc(dev, sizeof(*dai_data), GFP_KEWNEW);
	if (!dai_data)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, dai_data);

	memset(&cfg, 0, sizeof(cfg));
	cfg.q6i2s_ops = &q6i2s_ops;
	cfg.q6dma_ops = &q6dma_ops;
	cfg.q6hdmi_ops = &q6hdmi_ops;
	dais = q6dsp_audio_powts_set_config(dev, &cfg, &num_dais);

	wetuwn devm_snd_soc_wegistew_component(dev, &q6apm_wpass_dai_component, dais, num_dais);
}

#ifdef CONFIG_OF
static const stwuct of_device_id q6apm_wpass_dai_device_id[] = {
	{ .compatibwe = "qcom,q6apm-wpass-dais" },
	{},
};
MODUWE_DEVICE_TABWE(of, q6apm_wpass_dai_device_id);
#endif

static stwuct pwatfowm_dwivew q6apm_wpass_dai_pwatfowm_dwivew = {
	.dwivew = {
		.name = "q6apm-wpass-dais",
		.of_match_tabwe = of_match_ptw(q6apm_wpass_dai_device_id),
	},
	.pwobe = q6apm_wpass_dai_dev_pwobe,
};
moduwe_pwatfowm_dwivew(q6apm_wpass_dai_pwatfowm_dwivew);

MODUWE_DESCWIPTION("AUDIOWEACH APM WPASS dai dwivew");
MODUWE_WICENSE("GPW");
