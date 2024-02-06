// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8711.c  --  WM8711 AWSA SoC Audio dwivew
 *
 * Copywight 2006 Wowfson Micwoewectwonics
 *
 * Authow: Mike Awthuw <Mike.Awthuw@wowfsonmicwo.com>
 *
 * Based on wm8731.c by Wichawd Puwdie
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
#incwude <sound/twv.h>
#incwude <sound/initvaw.h>

#incwude "wm8711.h"

/* codec pwivate data */
stwuct wm8711_pwiv {
	stwuct wegmap *wegmap;
	unsigned int syscwk;
};

/*
 * wm8711 wegistew cache
 * We can't wead the WM8711 wegistew space when we awe
 * using 2 wiwe fow device contwow, so we cache them instead.
 * Thewe is no point in caching the weset wegistew
 */
static const stwuct weg_defauwt wm8711_weg_defauwts[] = {
	{ 0, 0x0079 }, { 1, 0x0079 }, { 2, 0x000a }, { 3, 0x0008 },
	{ 4, 0x009f }, { 5, 0x000a }, { 6, 0x0000 }, { 7, 0x0000 },
};

static boow wm8711_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM8711_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

#define wm8711_weset(c)	snd_soc_component_wwite(c, WM8711_WESET, 0)

static const DECWAWE_TWV_DB_SCAWE(out_twv, -12100, 100, 1);

static const stwuct snd_kcontwow_new wm8711_snd_contwows[] = {

SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume", WM8711_WOUT1V, WM8711_WOUT1V,
		 0, 127, 0, out_twv),
SOC_DOUBWE_W("Mastew Pwayback ZC Switch", WM8711_WOUT1V, WM8711_WOUT1V,
	7, 1, 0),

};

/* Output Mixew */
static const stwuct snd_kcontwow_new wm8711_output_mixew_contwows[] = {
SOC_DAPM_SINGWE("Wine Bypass Switch", WM8711_APANA, 3, 1, 0),
SOC_DAPM_SINGWE("HiFi Pwayback Switch", WM8711_APANA, 4, 1, 0),
};

static const stwuct snd_soc_dapm_widget wm8711_dapm_widgets[] = {
SND_SOC_DAPM_MIXEW("Output Mixew", WM8711_PWW, 4, 1,
	&wm8711_output_mixew_contwows[0],
	AWWAY_SIZE(wm8711_output_mixew_contwows)),
SND_SOC_DAPM_DAC("DAC", "HiFi Pwayback", WM8711_PWW, 3, 1),
SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_OUTPUT("WHPOUT"),
SND_SOC_DAPM_OUTPUT("WOUT"),
SND_SOC_DAPM_OUTPUT("WHPOUT"),
};

static const stwuct snd_soc_dapm_woute wm8711_intewcon[] = {
	/* output mixew */
	{"Output Mixew", "Wine Bypass Switch", "Wine Input"},
	{"Output Mixew", "HiFi Pwayback Switch", "DAC"},

	/* outputs */
	{"WHPOUT", NUWW, "Output Mixew"},
	{"WOUT", NUWW, "Output Mixew"},
	{"WHPOUT", NUWW, "Output Mixew"},
	{"WOUT", NUWW, "Output Mixew"},
};

stwuct _coeff_div {
	u32 mcwk;
	u32 wate;
	u16 fs;
	u8 sw:4;
	u8 bosw:1;
	u8 usb:1;
};

/* codec mcwk cwock dividew coefficients */
static const stwuct _coeff_div coeff_div[] = {
	/* 48k */
	{12288000, 48000, 256, 0x0, 0x0, 0x0},
	{18432000, 48000, 384, 0x0, 0x1, 0x0},
	{12000000, 48000, 250, 0x0, 0x0, 0x1},

	/* 32k */
	{12288000, 32000, 384, 0x6, 0x0, 0x0},
	{18432000, 32000, 576, 0x6, 0x1, 0x0},
	{12000000, 32000, 375, 0x6, 0x0, 0x1},

	/* 8k */
	{12288000, 8000, 1536, 0x3, 0x0, 0x0},
	{18432000, 8000, 2304, 0x3, 0x1, 0x0},
	{11289600, 8000, 1408, 0xb, 0x0, 0x0},
	{16934400, 8000, 2112, 0xb, 0x1, 0x0},
	{12000000, 8000, 1500, 0x3, 0x0, 0x1},

	/* 96k */
	{12288000, 96000, 128, 0x7, 0x0, 0x0},
	{18432000, 96000, 192, 0x7, 0x1, 0x0},
	{12000000, 96000, 125, 0x7, 0x0, 0x1},

	/* 44.1k */
	{11289600, 44100, 256, 0x8, 0x0, 0x0},
	{16934400, 44100, 384, 0x8, 0x1, 0x0},
	{12000000, 44100, 272, 0x8, 0x1, 0x1},

	/* 88.2k */
	{11289600, 88200, 128, 0xf, 0x0, 0x0},
	{16934400, 88200, 192, 0xf, 0x1, 0x0},
	{12000000, 88200, 136, 0xf, 0x1, 0x1},
};

static inwine int get_coeff(int mcwk, int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(coeff_div); i++) {
		if (coeff_div[i].wate == wate && coeff_div[i].mcwk == mcwk)
			wetuwn i;
	}
	wetuwn 0;
}

static int wm8711_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams,
	stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8711_pwiv *wm8711 =  snd_soc_component_get_dwvdata(component);
	u16 iface = snd_soc_component_wead(component, WM8711_IFACE) & 0xfff3;
	int i = get_coeff(wm8711->syscwk, pawams_wate(pawams));
	u16 swate = (coeff_div[i].sw << 2) |
		(coeff_div[i].bosw << 1) | coeff_div[i].usb;

	snd_soc_component_wwite(component, WM8711_SWATE, swate);

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		iface |= 0x0004;
		bweak;
	case 24:
		iface |= 0x0008;
		bweak;
	}

	snd_soc_component_wwite(component, WM8711_IFACE, iface);
	wetuwn 0;
}

static int wm8711_pcm_pwepawe(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	/* set active */
	snd_soc_component_wwite(component, WM8711_ACTIVE, 0x0001);

	wetuwn 0;
}

static void wm8711_shutdown(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;

	/* deactivate */
	if (!snd_soc_component_active(component)) {
		udeway(50);
		snd_soc_component_wwite(component, WM8711_ACTIVE, 0x0);
	}
}

static int wm8711_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u16 mute_weg = snd_soc_component_wead(component, WM8711_APDIGI) & 0xfff7;

	if (mute)
		snd_soc_component_wwite(component, WM8711_APDIGI, mute_weg | 0x8);
	ewse
		snd_soc_component_wwite(component, WM8711_APDIGI, mute_weg);

	wetuwn 0;
}

static int wm8711_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8711_pwiv *wm8711 =  snd_soc_component_get_dwvdata(component);

	switch (fweq) {
	case 11289600:
	case 12000000:
	case 12288000:
	case 16934400:
	case 18432000:
		wm8711->syscwk = fweq;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int wm8711_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface = snd_soc_component_wead(component, WM8711_IFACE) & 0x000c;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		iface |= 0x0040;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x0002;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= 0x0001;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= 0x0003;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface |= 0x0013;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x0090;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x0080;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x0010;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set iface */
	snd_soc_component_wwite(component, WM8711_IFACE, iface);
	wetuwn 0;
}

static int wm8711_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct wm8711_pwiv *wm8711 = snd_soc_component_get_dwvdata(component);
	u16 weg = snd_soc_component_wead(component, WM8711_PWW) & 0xff7f;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		snd_soc_component_wwite(component, WM8711_PWW, weg);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF)
			wegcache_sync(wm8711->wegmap);

		snd_soc_component_wwite(component, WM8711_PWW, weg | 0x0040);
		bweak;
	case SND_SOC_BIAS_OFF:
		snd_soc_component_wwite(component, WM8711_ACTIVE, 0x0);
		snd_soc_component_wwite(component, WM8711_PWW, 0xffff);
		bweak;
	}
	wetuwn 0;
}

#define WM8711_WATES SNDWV_PCM_WATE_8000_96000

#define WM8711_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wm8711_ops = {
	.pwepawe = wm8711_pcm_pwepawe,
	.hw_pawams = wm8711_hw_pawams,
	.shutdown = wm8711_shutdown,
	.mute_stweam = wm8711_mute,
	.set_syscwk = wm8711_set_dai_syscwk,
	.set_fmt = wm8711_set_dai_fmt,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8711_dai = {
	.name = "wm8711-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8711_WATES,
		.fowmats = WM8711_FOWMATS,
	},
	.ops = &wm8711_ops,
};

static int wm8711_pwobe(stwuct snd_soc_component *component)
{
	int wet;

	wet = wm8711_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset\n");
		wetuwn wet;
	}

	/* Watch the update bits */
	snd_soc_component_update_bits(component, WM8711_WOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8711_WOUT1V, 0x0100, 0x0100);

	wetuwn wet;

}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8711 = {
	.pwobe			= wm8711_pwobe,
	.set_bias_wevew		= wm8711_set_bias_wevew,
	.contwows		= wm8711_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8711_snd_contwows),
	.dapm_widgets		= wm8711_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8711_dapm_widgets),
	.dapm_woutes		= wm8711_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(wm8711_intewcon),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id wm8711_of_match[] = {
	{ .compatibwe = "wwf,wm8711", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8711_of_match);

static const stwuct wegmap_config wm8711_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,
	.max_wegistew = WM8711_WESET,

	.weg_defauwts = wm8711_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8711_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wm8711_vowatiwe,
};

#if defined(CONFIG_SPI_MASTEW)
static int wm8711_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8711_pwiv *wm8711;
	int wet;

	wm8711 = devm_kzawwoc(&spi->dev, sizeof(stwuct wm8711_pwiv),
			      GFP_KEWNEW);
	if (wm8711 == NUWW)
		wetuwn -ENOMEM;

	wm8711->wegmap = devm_wegmap_init_spi(spi, &wm8711_wegmap);
	if (IS_EWW(wm8711->wegmap))
		wetuwn PTW_EWW(wm8711->wegmap);

	spi_set_dwvdata(spi, wm8711);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&soc_component_dev_wm8711, &wm8711_dai, 1);

	wetuwn wet;
}

static stwuct spi_dwivew wm8711_spi_dwivew = {
	.dwivew = {
		.name	= "wm8711",
		.of_match_tabwe = wm8711_of_match,
	},
	.pwobe		= wm8711_spi_pwobe,
};
#endif /* CONFIG_SPI_MASTEW */

#if IS_ENABWED(CONFIG_I2C)
static int wm8711_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm8711_pwiv *wm8711;
	int wet;

	wm8711 = devm_kzawwoc(&cwient->dev, sizeof(stwuct wm8711_pwiv),
			      GFP_KEWNEW);
	if (wm8711 == NUWW)
		wetuwn -ENOMEM;

	wm8711->wegmap = devm_wegmap_init_i2c(cwient, &wm8711_wegmap);
	if (IS_EWW(wm8711->wegmap))
		wetuwn PTW_EWW(wm8711->wegmap);

	i2c_set_cwientdata(cwient, wm8711);

	wet = devm_snd_soc_wegistew_component(&cwient->dev,
			&soc_component_dev_wm8711, &wm8711_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id wm8711_i2c_id[] = {
	{ "wm8711", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8711_i2c_id);

static stwuct i2c_dwivew wm8711_i2c_dwivew = {
	.dwivew = {
		.name = "wm8711",
		.of_match_tabwe = wm8711_of_match,
	},
	.pwobe = wm8711_i2c_pwobe,
	.id_tabwe = wm8711_i2c_id,
};
#endif

static int __init wm8711_modinit(void)
{
	int wet;
#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8711_i2c_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew WM8711 I2C dwivew: %d\n",
		       wet);
	}
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8711_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew WM8711 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn 0;
}
moduwe_init(wm8711_modinit);

static void __exit wm8711_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8711_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8711_spi_dwivew);
#endif
}
moduwe_exit(wm8711_exit);

MODUWE_DESCWIPTION("ASoC WM8711 dwivew");
MODUWE_AUTHOW("Mike Awthuw");
MODUWE_WICENSE("GPW");
