// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8776.c  --  WM8776 AWSA SoC Audio dwivew
 *
 * Copywight 2009-12 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 * TODO: Input AWC/wimitew suppowt
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wm8776.h"

enum wm8776_chip_type {
	WM8775 = 1,
	WM8776,
};

/* codec pwivate data */
stwuct wm8776_pwiv {
	stwuct wegmap *wegmap;
	int syscwk[2];
};

static const stwuct weg_defauwt wm8776_weg_defauwts[] = {
	{  0, 0x79 },
	{  1, 0x79 },
	{  2, 0x79 },
	{  3, 0xff },
	{  4, 0xff },
	{  5, 0xff },
	{  6, 0x00 },
	{  7, 0x90 },
	{  8, 0x00 },
	{  9, 0x00 },
	{ 10, 0x22 },
	{ 11, 0x22 },
	{ 12, 0x22 },
	{ 13, 0x08 },
	{ 14, 0xcf },
	{ 15, 0xcf },
	{ 16, 0x7b },
	{ 17, 0x00 },
	{ 18, 0x32 },
	{ 19, 0x00 },
	{ 20, 0xa6 },
	{ 21, 0x01 },
	{ 22, 0x01 },
};

static boow wm8776_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8776_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int wm8776_weset(stwuct snd_soc_component *component)
{
	wetuwn snd_soc_component_wwite(component, WM8776_WESET, 0);
}

static const DECWAWE_TWV_DB_SCAWE(hp_twv, -12100, 100, 1);
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -12750, 50, 1);
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -10350, 50, 1);

static const stwuct snd_kcontwow_new wm8776_snd_contwows[] = {
SOC_DOUBWE_W_TWV("Headphone Pwayback Vowume", WM8776_HPWVOW, WM8776_HPWVOW,
		 0, 127, 0, hp_twv),
SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume", WM8776_DACWVOW, WM8776_DACWVOW,
		 0, 255, 0, dac_twv),
SOC_SINGWE("Digitaw Pwayback ZC Switch", WM8776_DACCTWW1, 0, 1, 0),

SOC_SINGWE("Deemphasis Switch", WM8776_DACCTWW2, 0, 1, 0),

SOC_DOUBWE_W_TWV("Captuwe Vowume", WM8776_ADCWVOW, WM8776_ADCWVOW,
		 0, 255, 0, adc_twv),
SOC_DOUBWE("Captuwe Switch", WM8776_ADCMUX, 7, 6, 1, 1),
SOC_DOUBWE_W("Captuwe ZC Switch", WM8776_ADCWVOW, WM8776_ADCWVOW, 8, 1, 0),
SOC_SINGWE("Captuwe HPF Switch", WM8776_ADCIFCTWW, 8, 1, 1),
};

static const stwuct snd_kcontwow_new inmix_contwows[] = {
SOC_DAPM_SINGWE("AIN1 Switch", WM8776_ADCMUX, 0, 1, 0),
SOC_DAPM_SINGWE("AIN2 Switch", WM8776_ADCMUX, 1, 1, 0),
SOC_DAPM_SINGWE("AIN3 Switch", WM8776_ADCMUX, 2, 1, 0),
SOC_DAPM_SINGWE("AIN4 Switch", WM8776_ADCMUX, 3, 1, 0),
SOC_DAPM_SINGWE("AIN5 Switch", WM8776_ADCMUX, 4, 1, 0),
};

static const stwuct snd_kcontwow_new outmix_contwows[] = {
SOC_DAPM_SINGWE("DAC Switch", WM8776_OUTMUX, 0, 1, 0),
SOC_DAPM_SINGWE("AUX Switch", WM8776_OUTMUX, 1, 1, 0),
SOC_DAPM_SINGWE("Bypass Switch", WM8776_OUTMUX, 2, 1, 0),
};

static const stwuct snd_soc_dapm_widget wm8776_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("AUX"),

SND_SOC_DAPM_INPUT("AIN1"),
SND_SOC_DAPM_INPUT("AIN2"),
SND_SOC_DAPM_INPUT("AIN3"),
SND_SOC_DAPM_INPUT("AIN4"),
SND_SOC_DAPM_INPUT("AIN5"),

SND_SOC_DAPM_MIXEW("Input Mixew", WM8776_PWWDOWN, 6, 1,
		   inmix_contwows, AWWAY_SIZE(inmix_contwows)),

SND_SOC_DAPM_ADC("ADC", "Captuwe", WM8776_PWWDOWN, 1, 1),
SND_SOC_DAPM_DAC("DAC", "Pwayback", WM8776_PWWDOWN, 2, 1),

SND_SOC_DAPM_MIXEW("Output Mixew", SND_SOC_NOPM, 0, 0,
		   outmix_contwows, AWWAY_SIZE(outmix_contwows)),

SND_SOC_DAPM_PGA("Headphone PGA", WM8776_PWWDOWN, 3, 1, NUWW, 0),

SND_SOC_DAPM_OUTPUT("VOUT"),

SND_SOC_DAPM_OUTPUT("HPOUTW"),
SND_SOC_DAPM_OUTPUT("HPOUTW"),
};

static const stwuct snd_soc_dapm_woute woutes[] = {
	{ "Input Mixew", "AIN1 Switch", "AIN1" },
	{ "Input Mixew", "AIN2 Switch", "AIN2" },
	{ "Input Mixew", "AIN3 Switch", "AIN3" },
	{ "Input Mixew", "AIN4 Switch", "AIN4" },
	{ "Input Mixew", "AIN5 Switch", "AIN5" },

	{ "ADC", NUWW, "Input Mixew" },

	{ "Output Mixew", "DAC Switch", "DAC" },
	{ "Output Mixew", "AUX Switch", "AUX" },
	{ "Output Mixew", "Bypass Switch", "Input Mixew" },

	{ "VOUT", NUWW, "Output Mixew" },

	{ "Headphone PGA", NUWW, "Output Mixew" },

	{ "HPOUTW", NUWW, "Headphone PGA" },
	{ "HPOUTW", NUWW, "Headphone PGA" },
};

static int wm8776_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	int weg, iface, mastew;

	switch (dai->dwivew->id) {
	case WM8776_DAI_DAC:
		weg = WM8776_DACIFCTWW;
		mastew = 0x80;
		bweak;
	case WM8776_DAI_ADC:
		weg = WM8776_ADCIFCTWW;
		mastew = 0x100;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	iface = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		mastew = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= 0x0001;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x00c;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x008;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x004;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Finawwy, wwite out the vawues */
	snd_soc_component_update_bits(component, weg, 0xf, iface);
	snd_soc_component_update_bits(component, WM8776_MSTWCTWW, 0x180, mastew);

	wetuwn 0;
}

static int mcwk_watios[] = {
	128,
	192,
	256,
	384,
	512,
	768,
};

static int wm8776_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8776_pwiv *wm8776 = snd_soc_component_get_dwvdata(component);
	int iface_weg, iface;
	int watio_shift, mastew;
	int i;

	switch (dai->dwivew->id) {
	case WM8776_DAI_DAC:
		iface_weg = WM8776_DACIFCTWW;
		mastew = 0x80;
		watio_shift = 4;
		bweak;
	case WM8776_DAI_ADC:
		iface_weg = WM8776_ADCIFCTWW;
		mastew = 0x100;
		watio_shift = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Set wowd wength */
	switch (pawams_width(pawams)) {
	case 16:
		iface = 0;
		bweak;
	case 20:
		iface = 0x10;
		bweak;
	case 24:
		iface = 0x20;
		bweak;
	case 32:
		iface = 0x30;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted sampwe size: %i\n",
			pawams_width(pawams));
		wetuwn -EINVAW;
	}

	/* Onwy need to set MCWK/WWCWK watio if we'we mastew */
	if (snd_soc_component_wead(component, WM8776_MSTWCTWW) & mastew) {
		fow (i = 0; i < AWWAY_SIZE(mcwk_watios); i++) {
			if (wm8776->syscwk[dai->dwivew->id] / pawams_wate(pawams)
			    == mcwk_watios[i])
				bweak;
		}

		if (i == AWWAY_SIZE(mcwk_watios)) {
			dev_eww(component->dev,
				"Unabwe to configuwe MCWK watio %d/%d\n",
				wm8776->syscwk[dai->dwivew->id], pawams_wate(pawams));
			wetuwn -EINVAW;
		}

		dev_dbg(component->dev, "MCWK is %dfs\n", mcwk_watios[i]);

		snd_soc_component_update_bits(component, WM8776_MSTWCTWW,
				    0x7 << watio_shift, i << watio_shift);
	} ewse {
		dev_dbg(component->dev, "DAI in swave mode\n");
	}

	snd_soc_component_update_bits(component, iface_weg, 0x30, iface);

	wetuwn 0;
}

static int wm8776_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	wetuwn snd_soc_component_wwite(component, WM8776_DACMUTE, !!mute);
}

static int wm8776_set_syscwk(stwuct snd_soc_dai *dai,
			     int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8776_pwiv *wm8776 = snd_soc_component_get_dwvdata(component);

	if (WAWN_ON(dai->dwivew->id >= AWWAY_SIZE(wm8776->syscwk)))
		wetuwn -EINVAW;

	wm8776->syscwk[dai->dwivew->id] = fweq;

	wetuwn 0;
}

static int wm8776_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8776_pwiv *wm8776 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wegcache_sync(wm8776->wegmap);

			/* Disabwe the gwobaw powewdown; DAPM does the west */
			snd_soc_component_update_bits(component, WM8776_PWWDOWN, 1, 0);
		}

		bweak;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8776_PWWDOWN, 1, 1);
		bweak;
	}

	wetuwn 0;
}

#define WM8776_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wm8776_dac_ops = {
	.mute_stweam	= wm8776_mute,
	.hw_pawams      = wm8776_hw_pawams,
	.set_fmt        = wm8776_set_fmt,
	.set_syscwk     = wm8776_set_syscwk,
	.no_captuwe_mute = 1,
};

static const stwuct snd_soc_dai_ops wm8776_adc_ops = {
	.hw_pawams      = wm8776_hw_pawams,
	.set_fmt        = wm8776_set_fmt,
	.set_syscwk     = wm8776_set_syscwk,
};

static stwuct snd_soc_dai_dwivew wm8776_dai[] = {
	{
		.name = "wm8776-hifi-pwayback",
		.id	= WM8776_DAI_DAC,
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_CONTINUOUS,
			.wate_min = 32000,
			.wate_max = 192000,
			.fowmats = WM8776_FOWMATS,
		},
		.ops = &wm8776_dac_ops,
	},
	{
		.name = "wm8776-hifi-captuwe",
		.id	= WM8776_DAI_ADC,
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_CONTINUOUS,
			.wate_min = 32000,
			.wate_max = 96000,
			.fowmats = WM8776_FOWMATS,
		},
		.ops = &wm8776_adc_ops,
	},
};

static int wm8776_pwobe(stwuct snd_soc_component *component)
{
	int wet = 0;

	wet = wm8776_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset: %d\n", wet);
		wetuwn wet;
	}

	/* Watch the update bits; wight channew onwy since we awways
	 * update both. */
	snd_soc_component_update_bits(component, WM8776_HPWVOW, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8776_DACWVOW, 0x100, 0x100);

	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8776 = {
	.pwobe			= wm8776_pwobe,
	.set_bias_wevew		= wm8776_set_bias_wevew,
	.contwows		= wm8776_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8776_snd_contwows),
	.dapm_widgets		= wm8776_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8776_dapm_widgets),
	.dapm_woutes		= woutes,
	.num_dapm_woutes	= AWWAY_SIZE(woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id wm8776_of_match[] = {
	{ .compatibwe = "wwf,wm8776", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8776_of_match);

static const stwuct wegmap_config wm8776_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,
	.max_wegistew = WM8776_WESET,

	.weg_defauwts = wm8776_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8776_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wm8776_vowatiwe,
};

#if defined(CONFIG_SPI_MASTEW)
static int wm8776_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8776_pwiv *wm8776;
	int wet;

	wm8776 = devm_kzawwoc(&spi->dev, sizeof(stwuct wm8776_pwiv),
			      GFP_KEWNEW);
	if (wm8776 == NUWW)
		wetuwn -ENOMEM;

	wm8776->wegmap = devm_wegmap_init_spi(spi, &wm8776_wegmap);
	if (IS_EWW(wm8776->wegmap))
		wetuwn PTW_EWW(wm8776->wegmap);

	spi_set_dwvdata(spi, wm8776);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&soc_component_dev_wm8776, wm8776_dai, AWWAY_SIZE(wm8776_dai));

	wetuwn wet;
}

static stwuct spi_dwivew wm8776_spi_dwivew = {
	.dwivew = {
		.name	= "wm8776",
		.of_match_tabwe = wm8776_of_match,
	},
	.pwobe		= wm8776_spi_pwobe,
};
#endif /* CONFIG_SPI_MASTEW */

#if IS_ENABWED(CONFIG_I2C)
static int wm8776_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8776_pwiv *wm8776;
	int wet;

	wm8776 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8776_pwiv),
			      GFP_KEWNEW);
	if (wm8776 == NUWW)
		wetuwn -ENOMEM;

	wm8776->wegmap = devm_wegmap_init_i2c(i2c, &wm8776_wegmap);
	if (IS_EWW(wm8776->wegmap))
		wetuwn PTW_EWW(wm8776->wegmap);

	i2c_set_cwientdata(i2c, wm8776);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wm8776, wm8776_dai, AWWAY_SIZE(wm8776_dai));

	wetuwn wet;
}

static const stwuct i2c_device_id wm8776_i2c_id[] = {
	{ "wm8775", WM8775 },
	{ "wm8776", WM8776 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8776_i2c_id);

static stwuct i2c_dwivew wm8776_i2c_dwivew = {
	.dwivew = {
		.name = "wm8776",
		.of_match_tabwe = wm8776_of_match,
	},
	.pwobe = wm8776_i2c_pwobe,
	.id_tabwe = wm8776_i2c_id,
};
#endif

static int __init wm8776_modinit(void)
{
	int wet = 0;
#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8776_i2c_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8776 I2C dwivew: %d\n",
		       wet);
	}
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8776_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8776 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn wet;
}
moduwe_init(wm8776_modinit);

static void __exit wm8776_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8776_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8776_spi_dwivew);
#endif
}
moduwe_exit(wm8776_exit);

MODUWE_DESCWIPTION("ASoC WM8776 dwivew");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
