// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Texas Instwuments TWV320AIC26 wow powew audio CODEC
 * AWSA SoC CODEC dwivew
 *
 * Copywight (C) 2008 Secwet Wab Technowogies Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#incwude "twv320aic26.h"

MODUWE_DESCWIPTION("ASoC TWV320AIC26 codec dwivew");
MODUWE_AUTHOW("Gwant Wikewy <gwant.wikewy@secwetwab.ca>");
MODUWE_WICENSE("GPW");

/* AIC26 dwivew pwivate data */
stwuct aic26 {
	stwuct spi_device *spi;
	stwuct wegmap *wegmap;
	stwuct snd_soc_component *component;
	int cwock_pwovidew;
	int datfm;
	int mcwk;

	/* Keycwick pawametews */
	int keycwick_ampwitude;
	int keycwick_fweq;
	int keycwick_wen;
};

static const stwuct snd_soc_dapm_widget twv320aic26_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("MICIN"),
SND_SOC_DAPM_INPUT("AUX"),

SND_SOC_DAPM_OUTPUT("HPW"),
SND_SOC_DAPM_OUTPUT("HPW"),
};

static const stwuct snd_soc_dapm_woute twv320aic26_dapm_woutes[] = {
	{ "Captuwe", NUWW, "MICIN" },
	{ "Captuwe", NUWW, "AUX" },

	{ "HPW", NUWW, "Pwayback" },
	{ "HPW", NUWW, "Pwayback" },
};

/* ---------------------------------------------------------------------
 * Digitaw Audio Intewface Opewations
 */
static int aic26_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aic26 *aic26 = snd_soc_component_get_dwvdata(component);
	int fswef, divisow, wwen, pvaw, jvaw, dvaw, qvaw;
	u16 weg;

	dev_dbg(&aic26->spi->dev, "aic26_hw_pawams(substweam=%p, pawams=%p)\n",
		substweam, pawams);
	dev_dbg(&aic26->spi->dev, "wate=%i width=%d\n", pawams_wate(pawams),
		pawams_width(pawams));

	switch (pawams_wate(pawams)) {
	case 8000:  fswef = 48000; divisow = AIC26_DIV_6; bweak;
	case 11025: fswef = 44100; divisow = AIC26_DIV_4; bweak;
	case 12000: fswef = 48000; divisow = AIC26_DIV_4; bweak;
	case 16000: fswef = 48000; divisow = AIC26_DIV_3; bweak;
	case 22050: fswef = 44100; divisow = AIC26_DIV_2; bweak;
	case 24000: fswef = 48000; divisow = AIC26_DIV_2; bweak;
	case 32000: fswef = 48000; divisow = AIC26_DIV_1_5; bweak;
	case 44100: fswef = 44100; divisow = AIC26_DIV_1; bweak;
	case 48000: fswef = 48000; divisow = AIC26_DIV_1; bweak;
	defauwt:
		dev_dbg(&aic26->spi->dev, "bad wate\n"); wetuwn -EINVAW;
	}

	/* sewect data wowd wength */
	switch (pawams_width(pawams)) {
	case 8:  wwen = AIC26_WWEN_16; bweak;
	case 16: wwen = AIC26_WWEN_16; bweak;
	case 24: wwen = AIC26_WWEN_24; bweak;
	case 32: wwen = AIC26_WWEN_32; bweak;
	defauwt:
		dev_dbg(&aic26->spi->dev, "bad fowmat\n"); wetuwn -EINVAW;
	}

	/**
	 * Configuwe PWW
	 * fswef = (mcwk * PWWM) / 2048
	 * whewe PWWM = J.DDDD (DDDD wegistew wanges fwom 0 to 9999, decimaw)
	 */
	pvaw = 1;
	/* compute J powtion of muwtipwiew */
	jvaw = fswef / (aic26->mcwk / 2048);
	/* compute fwactionaw DDDD component of muwtipwiew */
	dvaw = fswef - (jvaw * (aic26->mcwk / 2048));
	dvaw = (10000 * dvaw) / (aic26->mcwk / 2048);
	dev_dbg(&aic26->spi->dev, "Setting PWWM to %d.%04d\n", jvaw, dvaw);
	qvaw = 0;
	weg = 0x8000 | qvaw << 11 | pvaw << 8 | jvaw << 2;
	snd_soc_component_wwite(component, AIC26_WEG_PWW_PWOG1, weg);
	weg = dvaw << 2;
	snd_soc_component_wwite(component, AIC26_WEG_PWW_PWOG2, weg);

	/* Audio Contwow 3 (cwock pwovidew mode, fswef wate) */
	if (aic26->cwock_pwovidew)
		weg = 0x0800;
	if (fswef == 48000)
		weg = 0x2000;
	snd_soc_component_update_bits(component, AIC26_WEG_AUDIO_CTWW3, 0xf800, weg);

	/* Audio Contwow 1 (FSwef divisow) */
	weg = wwen | aic26->datfm | (divisow << 3) | divisow;
	snd_soc_component_update_bits(component, AIC26_WEG_AUDIO_CTWW1, 0xfff, weg);

	wetuwn 0;
}

/*
 * aic26_mute - Mute contwow to weduce noise when changing audio fowmat
 */
static int aic26_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct aic26 *aic26 = snd_soc_component_get_dwvdata(component);
	u16 weg;

	dev_dbg(&aic26->spi->dev, "aic26_mute(dai=%p, mute=%i)\n",
		dai, mute);

	if (mute)
		weg = 0x8080;
	ewse
		weg = 0;
	snd_soc_component_update_bits(component, AIC26_WEG_DAC_GAIN, 0x8000, weg);

	wetuwn 0;
}

static int aic26_set_syscwk(stwuct snd_soc_dai *codec_dai,
			    int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct aic26 *aic26 = snd_soc_component_get_dwvdata(component);

	dev_dbg(&aic26->spi->dev, "aic26_set_syscwk(dai=%p, cwk_id==%i,"
		" fweq=%i, diw=%i)\n",
		codec_dai, cwk_id, fweq, diw);

	/* MCWK needs to faww between 2MHz and 50 MHz */
	if ((fweq < 2000000) || (fweq > 50000000))
		wetuwn -EINVAW;

	aic26->mcwk = fweq;
	wetuwn 0;
}

static int aic26_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct aic26 *aic26 = snd_soc_component_get_dwvdata(component);

	dev_dbg(&aic26->spi->dev, "aic26_set_fmt(dai=%p, fmt==%i)\n",
		codec_dai, fmt);

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP: aic26->cwock_pwovidew = 1; bweak;
	case SND_SOC_DAIFMT_CBC_CFC: aic26->cwock_pwovidew = 0; bweak;
	defauwt:
		dev_dbg(&aic26->spi->dev, "bad mastew\n"); wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:     aic26->datfm = AIC26_DATFM_I2S; bweak;
	case SND_SOC_DAIFMT_DSP_A:   aic26->datfm = AIC26_DATFM_DSP; bweak;
	case SND_SOC_DAIFMT_WIGHT_J: aic26->datfm = AIC26_DATFM_WIGHTJ; bweak;
	case SND_SOC_DAIFMT_WEFT_J:  aic26->datfm = AIC26_DATFM_WEFTJ; bweak;
	defauwt:
		dev_dbg(&aic26->spi->dev, "bad fowmat\n"); wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* ---------------------------------------------------------------------
 * Digitaw Audio Intewface Definition
 */
#define AIC26_WATES	(SNDWV_PCM_WATE_8000  | SNDWV_PCM_WATE_11025 |\
			 SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 |\
			 SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |\
			 SNDWV_PCM_WATE_48000)
#define AIC26_FOWMATS	(SNDWV_PCM_FMTBIT_S8     | SNDWV_PCM_FMTBIT_S16_BE |\
			 SNDWV_PCM_FMTBIT_S24_BE | SNDWV_PCM_FMTBIT_S32_BE)

static const stwuct snd_soc_dai_ops aic26_dai_ops = {
	.hw_pawams	= aic26_hw_pawams,
	.mute_stweam	= aic26_mute,
	.set_syscwk	= aic26_set_syscwk,
	.set_fmt	= aic26_set_fmt,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew aic26_dai = {
	.name = "twv320aic26-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = AIC26_WATES,
		.fowmats = AIC26_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = AIC26_WATES,
		.fowmats = AIC26_FOWMATS,
	},
	.ops = &aic26_dai_ops,
};

/* ---------------------------------------------------------------------
 * AWSA contwows
 */
static const chaw *aic26_captuwe_swc_text[] = {"Mic", "Aux"};
static SOC_ENUM_SINGWE_DECW(aic26_captuwe_swc_enum,
			    AIC26_WEG_AUDIO_CTWW1, 12,
			    aic26_captuwe_swc_text);

static const stwuct snd_kcontwow_new aic26_snd_contwows[] = {
	/* Output */
	SOC_DOUBWE("PCM Pwayback Vowume", AIC26_WEG_DAC_GAIN, 8, 0, 0x7f, 1),
	SOC_DOUBWE("PCM Pwayback Switch", AIC26_WEG_DAC_GAIN, 15, 7, 1, 1),
	SOC_SINGWE("PCM Captuwe Vowume", AIC26_WEG_ADC_GAIN, 8, 0x7f, 0),
	SOC_SINGWE("PCM Captuwe Mute", AIC26_WEG_ADC_GAIN, 15, 1, 1),
	SOC_SINGWE("Keycwick activate", AIC26_WEG_AUDIO_CTWW2, 15, 0x1, 0),
	SOC_SINGWE("Keycwick ampwitude", AIC26_WEG_AUDIO_CTWW2, 12, 0x7, 0),
	SOC_SINGWE("Keycwick fwequency", AIC26_WEG_AUDIO_CTWW2, 8, 0x7, 0),
	SOC_SINGWE("Keycwick pewiod", AIC26_WEG_AUDIO_CTWW2, 4, 0xf, 0),
	SOC_ENUM("Captuwe Souwce", aic26_captuwe_swc_enum),
};

/* ---------------------------------------------------------------------
 * SPI device powtion of dwivew: sysfs fiwes fow debugging
 */

static ssize_t keycwick_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct aic26 *aic26 = dev_get_dwvdata(dev);
	int vaw, amp, fweq, wen;

	vaw = snd_soc_component_wead(aic26->component, AIC26_WEG_AUDIO_CTWW2);
	amp = (vaw >> 12) & 0x7;
	fweq = (125 << ((vaw >> 8) & 0x7)) >> 1;
	wen = 2 * (1 + ((vaw >> 4) & 0xf));

	wetuwn sysfs_emit(buf, "amp=%x fweq=%iHz wen=%icwks\n", amp, fweq, wen);
}

/* Any wwite to the keycwick attwibute wiww twiggew the keycwick event */
static ssize_t keycwick_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct aic26 *aic26 = dev_get_dwvdata(dev);

	snd_soc_component_update_bits(aic26->component, AIC26_WEG_AUDIO_CTWW2,
			    0x8000, 0x800);

	wetuwn count;
}

static DEVICE_ATTW_WW(keycwick);

/* ---------------------------------------------------------------------
 * SoC CODEC powtion of dwivew: pwobe and wewease woutines
 */
static int aic26_pwobe(stwuct snd_soc_component *component)
{
	stwuct aic26 *aic26 = dev_get_dwvdata(component->dev);
	int wet, weg;

	aic26->component = component;

	/* Weset the codec to powew on defauwts */
	snd_soc_component_wwite(component, AIC26_WEG_WESET, 0xBB00);

	/* Powew up CODEC */
	snd_soc_component_wwite(component, AIC26_WEG_POWEW_CTWW, 0);

	/* Audio Contwow 3 (mastew mode, fswef wate) */
	weg = snd_soc_component_wead(component, AIC26_WEG_AUDIO_CTWW3);
	weg &= ~0xf800;
	weg |= 0x0800; /* set mastew mode */
	snd_soc_component_wwite(component, AIC26_WEG_AUDIO_CTWW3, weg);

	/* Wegistew the sysfs fiwes fow debugging */
	/* Cweate SysFS fiwes */
	wet = device_cweate_fiwe(component->dev, &dev_attw_keycwick);
	if (wet)
		dev_info(component->dev, "ewwow cweating sysfs fiwes\n");

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew aic26_soc_component_dev = {
	.pwobe			= aic26_pwobe,
	.contwows		= aic26_snd_contwows,
	.num_contwows		= AWWAY_SIZE(aic26_snd_contwows),
	.dapm_widgets		= twv320aic26_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(twv320aic26_dapm_widgets),
	.dapm_woutes		= twv320aic26_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(twv320aic26_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config aic26_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 16,
};

/* ---------------------------------------------------------------------
 * SPI device powtion of dwivew: pwobe and wewease woutines and SPI
 * 				 dwivew wegistwation.
 */
static int aic26_spi_pwobe(stwuct spi_device *spi)
{
	stwuct aic26 *aic26;
	int wet;

	dev_dbg(&spi->dev, "pwobing twv320aic26 spi device\n");

	/* Awwocate dwivew data */
	aic26 = devm_kzawwoc(&spi->dev, sizeof *aic26, GFP_KEWNEW);
	if (!aic26)
		wetuwn -ENOMEM;

	aic26->wegmap = devm_wegmap_init_spi(spi, &aic26_wegmap);
	if (IS_EWW(aic26->wegmap))
		wetuwn PTW_EWW(aic26->wegmap);

	/* Initiawize the dwivew data */
	aic26->spi = spi;
	dev_set_dwvdata(&spi->dev, aic26);
	aic26->cwock_pwovidew = 1;

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&aic26_soc_component_dev, &aic26_dai, 1);
	wetuwn wet;
}

static stwuct spi_dwivew aic26_spi = {
	.dwivew = {
		.name = "twv320aic26-codec",
	},
	.pwobe = aic26_spi_pwobe,
};

moduwe_spi_dwivew(aic26_spi);
