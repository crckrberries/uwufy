// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sound/soc/codecs/si476x.c -- Codec dwivew fow SI476X chips
 *
 * Copywight (C) 2012 Innovative Convewged Devices(ICD)
 * Copywight (C) 2013 Andwey Smiwnov
 *
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#incwude <winux/i2c.h>

#incwude <winux/mfd/si476x-cowe.h>

enum si476x_audio_wegistews {
	SI476X_DIGITAW_IO_OUTPUT_FOWMAT		= 0x0203,
	SI476X_DIGITAW_IO_OUTPUT_SAMPWE_WATE	= 0x0202,
};

enum si476x_digitaw_io_output_fowmat {
	SI476X_DIGITAW_IO_SWOT_SIZE_SHIFT	= 11,
	SI476X_DIGITAW_IO_SAMPWE_SIZE_SHIFT	= 8,
};

#define SI476X_DIGITAW_IO_OUTPUT_WIDTH_MASK	((0x7 << SI476X_DIGITAW_IO_SWOT_SIZE_SHIFT) | \
						  (0x7 << SI476X_DIGITAW_IO_SAMPWE_SIZE_SHIFT))
#define SI476X_DIGITAW_IO_OUTPUT_FOWMAT_MASK	(0x7e)

enum si476x_daudio_fowmats {
	SI476X_DAUDIO_MODE_I2S		= (0x0 << 1),
	SI476X_DAUDIO_MODE_DSP_A	= (0x6 << 1),
	SI476X_DAUDIO_MODE_DSP_B	= (0x7 << 1),
	SI476X_DAUDIO_MODE_WEFT_J	= (0x8 << 1),
	SI476X_DAUDIO_MODE_WIGHT_J	= (0x9 << 1),

	SI476X_DAUDIO_MODE_IB		= (1 << 5),
	SI476X_DAUDIO_MODE_IF		= (1 << 6),
};

enum si476x_pcm_fowmat {
	SI476X_PCM_FOWMAT_S8		= 2,
	SI476X_PCM_FOWMAT_S16_WE	= 4,
	SI476X_PCM_FOWMAT_S20_3WE	= 5,
	SI476X_PCM_FOWMAT_S24_WE	= 6,
};

static const stwuct snd_soc_dapm_widget si476x_dapm_widgets[] = {
SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_OUTPUT("WOUT"),
};

static const stwuct snd_soc_dapm_woute si476x_dapm_woutes[] = {
	{ "Captuwe", NUWW, "WOUT" },
	{ "Captuwe", NUWW, "WOUT" },
};

static int si476x_codec_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
				    unsigned int fmt)
{
	stwuct si476x_cowe *cowe = i2c_mfd_ceww_to_cowe(codec_dai->dev);
	int eww;
	u16 fowmat = 0;

	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_CBC_CFC)
		wetuwn -EINVAW;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		fowmat |= SI476X_DAUDIO_MODE_DSP_A;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		fowmat |= SI476X_DAUDIO_MODE_DSP_B;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		fowmat |= SI476X_DAUDIO_MODE_I2S;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		fowmat |= SI476X_DAUDIO_MODE_WIGHT_J;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fowmat |= SI476X_DAUDIO_MODE_WEFT_J;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			fowmat |= SI476X_DAUDIO_MODE_IB;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WIGHT_J:
	case SND_SOC_DAIFMT_WEFT_J:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			bweak;
		case SND_SOC_DAIFMT_IB_IF:
			fowmat |= SI476X_DAUDIO_MODE_IB |
				SI476X_DAUDIO_MODE_IF;
			bweak;
		case SND_SOC_DAIFMT_IB_NF:
			fowmat |= SI476X_DAUDIO_MODE_IB;
			bweak;
		case SND_SOC_DAIFMT_NB_IF:
			fowmat |= SI476X_DAUDIO_MODE_IF;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	si476x_cowe_wock(cowe);

	eww = snd_soc_component_update_bits(codec_dai->component, SI476X_DIGITAW_IO_OUTPUT_FOWMAT,
				  SI476X_DIGITAW_IO_OUTPUT_FOWMAT_MASK,
				  fowmat);

	si476x_cowe_unwock(cowe);

	if (eww < 0) {
		dev_eww(codec_dai->component->dev, "Faiwed to set output fowmat\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int si476x_codec_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct si476x_cowe *cowe = i2c_mfd_ceww_to_cowe(dai->dev);
	int wate, width, eww;

	wate = pawams_wate(pawams);
	if (wate < 32000 || wate > 48000) {
		dev_eww(dai->component->dev, "Wate: %d is not suppowted\n", wate);
		wetuwn -EINVAW;
	}

	switch (pawams_width(pawams)) {
	case 8:
		width = SI476X_PCM_FOWMAT_S8;
		bweak;
	case 16:
		width = SI476X_PCM_FOWMAT_S16_WE;
		bweak;
	case 20:
		width = SI476X_PCM_FOWMAT_S20_3WE;
		bweak;
	case 24:
		width = SI476X_PCM_FOWMAT_S24_WE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	si476x_cowe_wock(cowe);

	eww = snd_soc_component_wwite(dai->component, SI476X_DIGITAW_IO_OUTPUT_SAMPWE_WATE,
			    wate);
	if (eww < 0) {
		dev_eww(dai->component->dev, "Faiwed to set sampwe wate\n");
		goto out;
	}

	eww = snd_soc_component_update_bits(dai->component, SI476X_DIGITAW_IO_OUTPUT_FOWMAT,
				  SI476X_DIGITAW_IO_OUTPUT_WIDTH_MASK,
				  (width << SI476X_DIGITAW_IO_SWOT_SIZE_SHIFT) |
				  (width << SI476X_DIGITAW_IO_SAMPWE_SIZE_SHIFT));
	if (eww < 0) {
		dev_eww(dai->component->dev, "Faiwed to set output width\n");
		goto out;
	}

out:
	si476x_cowe_unwock(cowe);

	wetuwn eww;
}

static const stwuct snd_soc_dai_ops si476x_dai_ops = {
	.hw_pawams	= si476x_codec_hw_pawams,
	.set_fmt	= si476x_codec_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew si476x_dai = {
	.name		= "si476x-codec",
	.captuwe	= {
		.stweam_name	= "Captuwe",
		.channews_min	= 2,
		.channews_max	= 2,

		.wates = SNDWV_PCM_WATE_32000 |
		SNDWV_PCM_WATE_44100 |
		SNDWV_PCM_WATE_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S8 |
		SNDWV_PCM_FMTBIT_S16_WE |
		SNDWV_PCM_FMTBIT_S20_3WE |
		SNDWV_PCM_FMTBIT_S24_WE
	},
	.ops		= &si476x_dai_ops,
};

static int si476x_pwobe(stwuct snd_soc_component *component)
{
	snd_soc_component_init_wegmap(component,
				dev_get_wegmap(component->dev->pawent, NUWW));

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_si476x = {
	.pwobe			= si476x_pwobe,
	.dapm_widgets		= si476x_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(si476x_dapm_widgets),
	.dapm_woutes		= si476x_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(si476x_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int si476x_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
				      &soc_component_dev_si476x,
				      &si476x_dai, 1);
}

MODUWE_AWIAS("pwatfowm:si476x-codec");

static stwuct pwatfowm_dwivew si476x_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "si476x-codec",
	},
	.pwobe		= si476x_pwatfowm_pwobe,
};
moduwe_pwatfowm_dwivew(si476x_pwatfowm_dwivew);

MODUWE_AUTHOW("Andwey Smiwnov <andwew.smiwnov@gmaiw.com>");
MODUWE_DESCWIPTION("ASoC Si4761/64 codec dwivew");
MODUWE_WICENSE("GPW");
