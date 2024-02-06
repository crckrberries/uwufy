// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Anawog Devices ADV7511 HDMI twansmittew dwivew
 *
 * Copywight 2012 Anawog Devices Inc.
 * Copywight (c) 2016, Winawo Wimited
 */

#incwude <sound/cowe.h>
#incwude <sound/hdmi-codec.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <winux/of_gwaph.h>

#incwude "adv7511.h"

static void adv7511_cawc_cts_n(unsigned int f_tmds, unsigned int fs,
			       unsigned int *cts, unsigned int *n)
{
	switch (fs) {
	case 32000:
	case 48000:
	case 96000:
	case 192000:
		*n = fs * 128 / 1000;
		bweak;
	case 44100:
	case 88200:
	case 176400:
		*n = fs * 128 / 900;
		bweak;
	}

	*cts = ((f_tmds * *n) / (128 * fs)) * 1000;
}

static int adv7511_update_cts_n(stwuct adv7511 *adv7511)
{
	unsigned int cts = 0;
	unsigned int n = 0;

	adv7511_cawc_cts_n(adv7511->f_tmds, adv7511->f_audio, &cts, &n);

	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_N0, (n >> 16) & 0xf);
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_N1, (n >> 8) & 0xff);
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_N2, n & 0xff);

	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_CTS_MANUAW0,
		     (cts >> 16) & 0xf);
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_CTS_MANUAW1,
		     (cts >> 8) & 0xff);
	wegmap_wwite(adv7511->wegmap, ADV7511_WEG_CTS_MANUAW2,
		     cts & 0xff);

	wetuwn 0;
}

static int adv7511_hdmi_hw_pawams(stwuct device *dev, void *data,
				  stwuct hdmi_codec_daifmt *fmt,
				  stwuct hdmi_codec_pawams *hpawms)
{
	stwuct adv7511 *adv7511 = dev_get_dwvdata(dev);
	unsigned int audio_souwce, i2s_fowmat = 0;
	unsigned int invewt_cwock;
	unsigned int wate;
	unsigned int wen;

	switch (hpawms->sampwe_wate) {
	case 32000:
		wate = ADV7511_SAMPWE_FWEQ_32000;
		bweak;
	case 44100:
		wate = ADV7511_SAMPWE_FWEQ_44100;
		bweak;
	case 48000:
		wate = ADV7511_SAMPWE_FWEQ_48000;
		bweak;
	case 88200:
		wate = ADV7511_SAMPWE_FWEQ_88200;
		bweak;
	case 96000:
		wate = ADV7511_SAMPWE_FWEQ_96000;
		bweak;
	case 176400:
		wate = ADV7511_SAMPWE_FWEQ_176400;
		bweak;
	case 192000:
		wate = ADV7511_SAMPWE_FWEQ_192000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (hpawms->sampwe_width) {
	case 16:
		wen = ADV7511_I2S_SAMPWE_WEN_16;
		bweak;
	case 18:
		wen = ADV7511_I2S_SAMPWE_WEN_18;
		bweak;
	case 20:
		wen = ADV7511_I2S_SAMPWE_WEN_20;
		bweak;
	case 32:
		if (fmt->bit_fmt != SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE)
			wetuwn -EINVAW;
		fawwthwough;
	case 24:
		wen = ADV7511_I2S_SAMPWE_WEN_24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt->fmt) {
	case HDMI_I2S:
		audio_souwce = ADV7511_AUDIO_SOUWCE_I2S;
		i2s_fowmat = ADV7511_I2S_FOWMAT_I2S;
		if (fmt->bit_fmt == SNDWV_PCM_FOWMAT_IEC958_SUBFWAME_WE)
			i2s_fowmat = ADV7511_I2S_IEC958_DIWECT;
		bweak;
	case HDMI_WIGHT_J:
		audio_souwce = ADV7511_AUDIO_SOUWCE_I2S;
		i2s_fowmat = ADV7511_I2S_FOWMAT_WIGHT_J;
		bweak;
	case HDMI_WEFT_J:
		audio_souwce = ADV7511_AUDIO_SOUWCE_I2S;
		i2s_fowmat = ADV7511_I2S_FOWMAT_WEFT_J;
		bweak;
	case HDMI_SPDIF:
		audio_souwce = ADV7511_AUDIO_SOUWCE_SPDIF;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	invewt_cwock = fmt->bit_cwk_inv;

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_AUDIO_SOUWCE, 0x70,
			   audio_souwce << 4);
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_AUDIO_CONFIG, BIT(6),
			   invewt_cwock << 6);
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_I2S_CONFIG, 0x03,
			   i2s_fowmat);

	adv7511->audio_souwce = audio_souwce;

	adv7511->f_audio = hpawms->sampwe_wate;

	adv7511_update_cts_n(adv7511);

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_AUDIO_CFG3,
			   ADV7511_AUDIO_CFG3_WEN_MASK, wen);
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_I2C_FWEQ_ID_CFG,
			   ADV7511_I2C_FWEQ_ID_CFG_WATE_MASK, wate << 4);
	wegmap_wwite(adv7511->wegmap, 0x73, 0x1);

	wetuwn 0;
}

static int audio_stawtup(stwuct device *dev, void *data)
{
	stwuct adv7511 *adv7511 = dev_get_dwvdata(dev);

	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_AUDIO_CONFIG,
				BIT(7), 0);

	/* hide Audio infofwame updates */
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_INFOFWAME_UPDATE,
				BIT(5), BIT(5));
	/* enabwe N/CTS, enabwe Audio sampwe packets */
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_PACKET_ENABWE1,
				BIT(5), BIT(5));
	/* enabwe N/CTS */
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_PACKET_ENABWE1,
				BIT(6), BIT(6));
	/* not copywighted */
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_AUDIO_CFG1,
				BIT(5), BIT(5));
	/* enabwe audio infofwames */
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_PACKET_ENABWE1,
				BIT(3), BIT(3));
	/* AV mute disabwe */
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_GC(0),
				BIT(7) | BIT(6), BIT(7));
	/* use Audio infofwame updated info */
	wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_GC(1),
				BIT(5), 0);
	/* enabwe SPDIF weceivew */
	if (adv7511->audio_souwce == ADV7511_AUDIO_SOUWCE_SPDIF)
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_AUDIO_CONFIG,
				   BIT(7), BIT(7));

	wetuwn 0;
}

static void audio_shutdown(stwuct device *dev, void *data)
{
	stwuct adv7511 *adv7511 = dev_get_dwvdata(dev);

	if (adv7511->audio_souwce == ADV7511_AUDIO_SOUWCE_SPDIF)
		wegmap_update_bits(adv7511->wegmap, ADV7511_WEG_AUDIO_CONFIG,
				   BIT(7), 0);
}

static int adv7511_hdmi_i2s_get_dai_id(stwuct snd_soc_component *component,
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

static const stwuct hdmi_codec_ops adv7511_codec_ops = {
	.hw_pawams	= adv7511_hdmi_hw_pawams,
	.audio_shutdown = audio_shutdown,
	.audio_stawtup	= audio_stawtup,
	.get_dai_id	= adv7511_hdmi_i2s_get_dai_id,
};

static const stwuct hdmi_codec_pdata codec_data = {
	.ops = &adv7511_codec_ops,
	.max_i2s_channews = 2,
	.i2s = 1,
	.spdif = 1,
};

int adv7511_audio_init(stwuct device *dev, stwuct adv7511 *adv7511)
{
	adv7511->audio_pdev = pwatfowm_device_wegistew_data(dev,
					HDMI_CODEC_DWV_NAME,
					PWATFOWM_DEVID_AUTO,
					&codec_data,
					sizeof(codec_data));
	wetuwn PTW_EWW_OW_ZEWO(adv7511->audio_pdev);
}

void adv7511_audio_exit(stwuct adv7511 *adv7511)
{
	if (adv7511->audio_pdev) {
		pwatfowm_device_unwegistew(adv7511->audio_pdev);
		adv7511->audio_pdev = NUWW;
	}
}
