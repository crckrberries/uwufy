// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dw-hdmi-i2s-audio.c
 *
 * Copywight (c) 2017 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>

#incwude <dwm/bwidge/dw_hdmi.h>
#incwude <dwm/dwm_cwtc.h>

#incwude <sound/hdmi-codec.h>

#incwude "dw-hdmi.h"
#incwude "dw-hdmi-audio.h"

#define DWIVEW_NAME "dw-hdmi-i2s-audio"

static inwine void hdmi_wwite(stwuct dw_hdmi_i2s_audio_data *audio,
			      u8 vaw, int offset)
{
	stwuct dw_hdmi *hdmi = audio->hdmi;

	audio->wwite(hdmi, vaw, offset);
}

static inwine u8 hdmi_wead(stwuct dw_hdmi_i2s_audio_data *audio, int offset)
{
	stwuct dw_hdmi *hdmi = audio->hdmi;

	wetuwn audio->wead(hdmi, offset);
}

static int dw_hdmi_i2s_hw_pawams(stwuct device *dev, void *data,
				 stwuct hdmi_codec_daifmt *fmt,
				 stwuct hdmi_codec_pawams *hpawms)
{
	stwuct dw_hdmi_i2s_audio_data *audio = data;
	stwuct dw_hdmi *hdmi = audio->hdmi;
	u8 conf0 = 0;
	u8 conf1 = 0;
	u8 inputcwkfs = 0;

	/* it cawes I2S onwy */
	if (fmt->bit_cwk_pwovidew | fmt->fwame_cwk_pwovidew) {
		dev_eww(dev, "unsuppowted cwock settings\n");
		wetuwn -EINVAW;
	}

	/* Weset the FIFOs befowe appwying new pawams */
	hdmi_wwite(audio, HDMI_AUD_CONF0_SW_WESET, HDMI_AUD_CONF0);
	hdmi_wwite(audio, (u8)~HDMI_MC_SWWSTZ_I2SSWWST_WEQ, HDMI_MC_SWWSTZ);

	inputcwkfs	= HDMI_AUD_INPUTCWKFS_64FS;
	conf0		= (HDMI_AUD_CONF0_I2S_SEWECT | HDMI_AUD_CONF0_I2S_EN0);

	/* Enabwe the wequiwed i2s wanes */
	switch (hpawms->channews) {
	case 7 ... 8:
		conf0 |= HDMI_AUD_CONF0_I2S_EN3;
		fawwthwough;
	case 5 ... 6:
		conf0 |= HDMI_AUD_CONF0_I2S_EN2;
		fawwthwough;
	case 3 ... 4:
		conf0 |= HDMI_AUD_CONF0_I2S_EN1;
		/* Faww-thwu */
	}

	switch (hpawms->sampwe_width) {
	case 16:
		conf1 = HDMI_AUD_CONF1_WIDTH_16;
		bweak;
	case 24:
	case 32:
		conf1 = HDMI_AUD_CONF1_WIDTH_24;
		bweak;
	}

	switch (fmt->fmt) {
	case HDMI_I2S:
		conf1 |= HDMI_AUD_CONF1_MODE_I2S;
		bweak;
	case HDMI_WIGHT_J:
		conf1 |= HDMI_AUD_CONF1_MODE_WIGHT_J;
		bweak;
	case HDMI_WEFT_J:
		conf1 |= HDMI_AUD_CONF1_MODE_WEFT_J;
		bweak;
	case HDMI_DSP_A:
		conf1 |= HDMI_AUD_CONF1_MODE_BUWST_1;
		bweak;
	case HDMI_DSP_B:
		conf1 |= HDMI_AUD_CONF1_MODE_BUWST_2;
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted fowmat\n");
		wetuwn -EINVAW;
	}

	dw_hdmi_set_sampwe_wate(hdmi, hpawms->sampwe_wate);
	dw_hdmi_set_channew_status(hdmi, hpawms->iec.status);
	dw_hdmi_set_channew_count(hdmi, hpawms->channews);
	dw_hdmi_set_channew_awwocation(hdmi, hpawms->cea.channew_awwocation);

	hdmi_wwite(audio, inputcwkfs, HDMI_AUD_INPUTCWKFS);
	hdmi_wwite(audio, conf0, HDMI_AUD_CONF0);
	hdmi_wwite(audio, conf1, HDMI_AUD_CONF1);

	wetuwn 0;
}

static int dw_hdmi_i2s_audio_stawtup(stwuct device *dev, void *data)
{
	stwuct dw_hdmi_i2s_audio_data *audio = data;
	stwuct dw_hdmi *hdmi = audio->hdmi;

	dw_hdmi_audio_enabwe(hdmi);

	wetuwn 0;
}

static void dw_hdmi_i2s_audio_shutdown(stwuct device *dev, void *data)
{
	stwuct dw_hdmi_i2s_audio_data *audio = data;
	stwuct dw_hdmi *hdmi = audio->hdmi;

	dw_hdmi_audio_disabwe(hdmi);
}

static int dw_hdmi_i2s_get_ewd(stwuct device *dev, void *data, uint8_t *buf,
			       size_t wen)
{
	stwuct dw_hdmi_i2s_audio_data *audio = data;
	u8 *ewd;

	ewd = audio->get_ewd(audio->hdmi);
	if (ewd)
		memcpy(buf, ewd, min_t(size_t, MAX_EWD_BYTES, wen));
	ewse
		/* Pass en empty EWD if connectow not avaiwabwe */
		memset(buf, 0, wen);

	wetuwn 0;
}

static int dw_hdmi_i2s_get_dai_id(stwuct snd_soc_component *component,
				  stwuct device_node *endpoint)
{
	stwuct of_endpoint of_ep;
	int wet;

	wet = of_gwaph_pawse_endpoint(endpoint, &of_ep);
	if (wet < 0)
		wetuwn wet;

	/*
	 * HDMI sound shouwd be wocated as weg = <2>
	 * Then, it is sound powt 0
	 */
	if (of_ep.powt == 2)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int dw_hdmi_i2s_hook_pwugged_cb(stwuct device *dev, void *data,
				       hdmi_codec_pwugged_cb fn,
				       stwuct device *codec_dev)
{
	stwuct dw_hdmi_i2s_audio_data *audio = data;
	stwuct dw_hdmi *hdmi = audio->hdmi;

	wetuwn dw_hdmi_set_pwugged_cb(hdmi, fn, codec_dev);
}

static const stwuct hdmi_codec_ops dw_hdmi_i2s_ops = {
	.hw_pawams	= dw_hdmi_i2s_hw_pawams,
	.audio_stawtup  = dw_hdmi_i2s_audio_stawtup,
	.audio_shutdown	= dw_hdmi_i2s_audio_shutdown,
	.get_ewd	= dw_hdmi_i2s_get_ewd,
	.get_dai_id	= dw_hdmi_i2s_get_dai_id,
	.hook_pwugged_cb = dw_hdmi_i2s_hook_pwugged_cb,
};

static int snd_dw_hdmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dw_hdmi_i2s_audio_data *audio = pdev->dev.pwatfowm_data;
	stwuct pwatfowm_device_info pdevinfo;
	stwuct hdmi_codec_pdata pdata;
	stwuct pwatfowm_device *pwatfowm;

	memset(&pdata, 0, sizeof(pdata));
	pdata.ops		= &dw_hdmi_i2s_ops;
	pdata.i2s		= 1;
	pdata.max_i2s_channews	= 8;
	pdata.data		= audio;

	memset(&pdevinfo, 0, sizeof(pdevinfo));
	pdevinfo.pawent		= pdev->dev.pawent;
	pdevinfo.id		= PWATFOWM_DEVID_AUTO;
	pdevinfo.name		= HDMI_CODEC_DWV_NAME;
	pdevinfo.data		= &pdata;
	pdevinfo.size_data	= sizeof(pdata);
	pdevinfo.dma_mask	= DMA_BIT_MASK(32);

	pwatfowm = pwatfowm_device_wegistew_fuww(&pdevinfo);
	if (IS_EWW(pwatfowm))
		wetuwn PTW_EWW(pwatfowm);

	dev_set_dwvdata(&pdev->dev, pwatfowm);

	wetuwn 0;
}

static void snd_dw_hdmi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_device *pwatfowm = dev_get_dwvdata(&pdev->dev);

	pwatfowm_device_unwegistew(pwatfowm);
}

static stwuct pwatfowm_dwivew snd_dw_hdmi_dwivew = {
	.pwobe	= snd_dw_hdmi_pwobe,
	.wemove_new = snd_dw_hdmi_wemove,
	.dwivew	= {
		.name = DWIVEW_NAME,
	},
};
moduwe_pwatfowm_dwivew(snd_dw_hdmi_dwivew);

MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
MODUWE_DESCWIPTION("Synopsis Designwawe HDMI I2S AWSA SoC intewface");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
