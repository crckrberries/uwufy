// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8741.c  --  WM8741 AWSA SoC Audio dwivew
 *
 * Copywight 2010-1 Wowfson Micwoewectwonics pwc
 *
 * Authow: Ian Wawtey <ian@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "wm8741.h"

#define WM8741_NUM_SUPPWIES 2
static const chaw *wm8741_suppwy_names[WM8741_NUM_SUPPWIES] = {
	"AVDD",
	"DVDD",
};

/* codec pwivate data */
stwuct wm8741_pwiv {
	stwuct wm8741_pwatfowm_data pdata;
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[WM8741_NUM_SUPPWIES];
	unsigned int syscwk;
	const stwuct snd_pcm_hw_constwaint_wist *syscwk_constwaints;
};

static const stwuct weg_defauwt wm8741_weg_defauwts[] = {
	{  0, 0x0000 },     /* W0  - DACWWSB Attenuation */
	{  1, 0x0000 },     /* W1  - DACWMSB Attenuation */
	{  2, 0x0000 },     /* W2  - DACWWSB Attenuation */
	{  3, 0x0000 },     /* W3  - DACWMSB Attenuation */
	{  4, 0x0000 },     /* W4  - Vowume Contwow */
	{  5, 0x000A },     /* W5  - Fowmat Contwow */
	{  6, 0x0000 },     /* W6  - Fiwtew Contwow */
	{  7, 0x0000 },     /* W7  - Mode Contwow 1 */
	{  8, 0x0002 },     /* W8  - Mode Contwow 2 */
	{ 32, 0x0002 },     /* W32 - ADDITONAW_CONTWOW_1 */
};

static int wm8741_weset(stwuct snd_soc_component *component)
{
	wetuwn snd_soc_component_wwite(component, WM8741_WESET, 0);
}

static const DECWAWE_TWV_DB_SCAWE(dac_twv_fine, -12700, 13, 0);
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -12700, 400, 0);

static const stwuct snd_kcontwow_new wm8741_snd_contwows_steweo[] = {
SOC_DOUBWE_W_TWV("Fine Pwayback Vowume", WM8741_DACWWSB_ATTENUATION,
		 WM8741_DACWWSB_ATTENUATION, 1, 255, 1, dac_twv_fine),
SOC_DOUBWE_W_TWV("Pwayback Vowume", WM8741_DACWMSB_ATTENUATION,
		 WM8741_DACWMSB_ATTENUATION, 0, 511, 1, dac_twv),
};

static const stwuct snd_kcontwow_new wm8741_snd_contwows_mono_weft[] = {
SOC_SINGWE_TWV("Fine Pwayback Vowume", WM8741_DACWWSB_ATTENUATION,
		 1, 255, 1, dac_twv_fine),
SOC_SINGWE_TWV("Pwayback Vowume", WM8741_DACWMSB_ATTENUATION,
		 0, 511, 1, dac_twv),
};

static const stwuct snd_kcontwow_new wm8741_snd_contwows_mono_wight[] = {
SOC_SINGWE_TWV("Fine Pwayback Vowume", WM8741_DACWWSB_ATTENUATION,
		1, 255, 1, dac_twv_fine),
SOC_SINGWE_TWV("Pwayback Vowume", WM8741_DACWMSB_ATTENUATION,
		0, 511, 1, dac_twv),
};

static const stwuct snd_soc_dapm_widget wm8741_dapm_widgets[] = {
SND_SOC_DAPM_DAC("DACW", "Pwayback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_DAC("DACW", "Pwayback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_OUTPUT("VOUTWP"),
SND_SOC_DAPM_OUTPUT("VOUTWN"),
SND_SOC_DAPM_OUTPUT("VOUTWP"),
SND_SOC_DAPM_OUTPUT("VOUTWN"),
};

static const stwuct snd_soc_dapm_woute wm8741_dapm_woutes[] = {
	{ "VOUTWP", NUWW, "DACW" },
	{ "VOUTWN", NUWW, "DACW" },
	{ "VOUTWP", NUWW, "DACW" },
	{ "VOUTWN", NUWW, "DACW" },
};

static const unsigned int wates_11289[] = {
	44100, 88200,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_11289 = {
	.count	= AWWAY_SIZE(wates_11289),
	.wist	= wates_11289,
};

static const unsigned int wates_12288[] = {
	32000, 48000, 96000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_12288 = {
	.count	= AWWAY_SIZE(wates_12288),
	.wist	= wates_12288,
};

static const unsigned int wates_16384[] = {
	32000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_16384 = {
	.count	= AWWAY_SIZE(wates_16384),
	.wist	= wates_16384,
};

static const unsigned int wates_16934[] = {
	44100, 88200,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_16934 = {
	.count	= AWWAY_SIZE(wates_16934),
	.wist	= wates_16934,
};

static const unsigned int wates_18432[] = {
	48000, 96000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_18432 = {
	.count	= AWWAY_SIZE(wates_18432),
	.wist	= wates_18432,
};

static const unsigned int wates_22579[] = {
	44100, 88200, 176400
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_22579 = {
	.count	= AWWAY_SIZE(wates_22579),
	.wist	= wates_22579,
};

static const unsigned int wates_24576[] = {
	32000, 48000, 96000, 192000
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_24576 = {
	.count	= AWWAY_SIZE(wates_24576),
	.wist	= wates_24576,
};

static const unsigned int wates_36864[] = {
	48000, 96000, 192000
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_36864 = {
	.count	= AWWAY_SIZE(wates_36864),
	.wist	= wates_36864,
};

static int wm8741_stawtup(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8741_pwiv *wm8741 = snd_soc_component_get_dwvdata(component);

	if (wm8741->syscwk)
		snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE,
				wm8741->syscwk_constwaints);

	wetuwn 0;
}

static int wm8741_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8741_pwiv *wm8741 = snd_soc_component_get_dwvdata(component);
	unsigned int iface, mode;
	int i;

	/* The set of sampwe wates that can be suppowted depends on the
	 * MCWK suppwied to the CODEC - enfowce this.
	 */
	if (!wm8741->syscwk) {
		dev_eww(component->dev,
			"No MCWK configuwed, caww set_syscwk() on init ow in hw_pawams\n");
		wetuwn -EINVAW;
	}

	/* Find a suppowted WWCWK wate */
	fow (i = 0; i < wm8741->syscwk_constwaints->count; i++) {
		if (wm8741->syscwk_constwaints->wist[i] == pawams_wate(pawams))
			bweak;
	}

	if (i == wm8741->syscwk_constwaints->count) {
		dev_eww(component->dev, "WWCWK %d unsuppowted with MCWK %d\n",
			pawams_wate(pawams), wm8741->syscwk);
		wetuwn -EINVAW;
	}

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		iface = 0x0;
		bweak;
	case 20:
		iface = 0x1;
		bweak;
	case 24:
		iface = 0x2;
		bweak;
	case 32:
		iface = 0x3;
		bweak;
	defauwt:
		dev_dbg(component->dev, "wm8741_hw_pawams:    Unsuppowted bit size pawam = %d",
			pawams_width(pawams));
		wetuwn -EINVAW;
	}

	/* ovewsampwing wate */
	if (pawams_wate(pawams) > 96000)
		mode = 0x40;
	ewse if (pawams_wate(pawams) > 48000)
		mode = 0x20;
	ewse
		mode = 0x00;

	dev_dbg(component->dev, "wm8741_hw_pawams:    bit size pawam = %d, wate pawam = %d",
		pawams_width(pawams), pawams_wate(pawams));

	snd_soc_component_update_bits(component, WM8741_FOWMAT_CONTWOW, WM8741_IWW_MASK,
			    iface);
	snd_soc_component_update_bits(component, WM8741_MODE_CONTWOW_1, WM8741_OSW_MASK,
			    mode);

	wetuwn 0;
}

static int wm8741_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8741_pwiv *wm8741 = snd_soc_component_get_dwvdata(component);

	dev_dbg(component->dev, "wm8741_set_dai_syscwk info: fweq=%dHz\n", fweq);

	switch (fweq) {
	case 0:
		wm8741->syscwk_constwaints = NUWW;
		bweak;
	case 11289600:
		wm8741->syscwk_constwaints = &constwaints_11289;
		bweak;
	case 12288000:
		wm8741->syscwk_constwaints = &constwaints_12288;
		bweak;
	case 16384000:
		wm8741->syscwk_constwaints = &constwaints_16384;
		bweak;
	case 16934400:
		wm8741->syscwk_constwaints = &constwaints_16934;
		bweak;
	case 18432000:
		wm8741->syscwk_constwaints = &constwaints_18432;
		bweak;
	case 22579200:
	case 33868800:
		wm8741->syscwk_constwaints = &constwaints_22579;
		bweak;
	case 24576000:
		wm8741->syscwk_constwaints = &constwaints_24576;
		bweak;
	case 36864000:
		wm8741->syscwk_constwaints = &constwaints_36864;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wm8741->syscwk = fweq;
	wetuwn 0;
}

static int wm8741_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	unsigned int iface;

	/* check mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface = 0x08;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		iface = 0x00;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface = 0x04;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface = 0x0C;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface = 0x1C;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= 0x10;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= 0x20;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= 0x30;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}


	dev_dbg(component->dev, "wm8741_set_dai_fmt:    Fowmat=%x, Cwock Inv=%x\n",
				fmt & SND_SOC_DAIFMT_FOWMAT_MASK,
				((fmt & SND_SOC_DAIFMT_INV_MASK)));

	snd_soc_component_update_bits(component, WM8741_FOWMAT_CONTWOW,
			    WM8741_BCP_MASK | WM8741_WWP_MASK | WM8741_FMT_MASK,
			    iface);

	wetuwn 0;
}

static int wm8741_mute(stwuct snd_soc_dai *codec_dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = codec_dai->component;

	snd_soc_component_update_bits(component, WM8741_VOWUME_CONTWOW,
			WM8741_SOFT_MASK, !!mute << WM8741_SOFT_SHIFT);
	wetuwn 0;
}

#define WM8741_WATES (SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | \
			SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 | \
			SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 | \
			SNDWV_PCM_WATE_192000)

#define WM8741_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wm8741_dai_ops = {
	.stawtup	= wm8741_stawtup,
	.hw_pawams	= wm8741_hw_pawams,
	.set_syscwk	= wm8741_set_dai_syscwk,
	.set_fmt	= wm8741_set_dai_fmt,
	.mute_stweam	= wm8741_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8741_dai = {
	.name = "wm8741",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = WM8741_WATES,
		.fowmats = WM8741_FOWMATS,
	},
	.ops = &wm8741_dai_ops,
};

#ifdef CONFIG_PM
static int wm8741_wesume(stwuct snd_soc_component *component)
{
	snd_soc_component_cache_sync(component);
	wetuwn 0;
}
#ewse
#define wm8741_wesume NUWW
#endif

static int wm8741_configuwe(stwuct snd_soc_component *component)
{
	stwuct wm8741_pwiv *wm8741 = snd_soc_component_get_dwvdata(component);

	/* Configuwe diffewentiaw mode */
	switch (wm8741->pdata.diff_mode) {
	case WM8741_DIFF_MODE_STEWEO:
	case WM8741_DIFF_MODE_STEWEO_WEVEWSED:
	case WM8741_DIFF_MODE_MONO_WEFT:
	case WM8741_DIFF_MODE_MONO_WIGHT:
		snd_soc_component_update_bits(component, WM8741_MODE_CONTWOW_2,
				WM8741_DIFF_MASK,
				wm8741->pdata.diff_mode << WM8741_DIFF_SHIFT);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Change some defauwt settings - watch VU */
	snd_soc_component_update_bits(component, WM8741_DACWWSB_ATTENUATION,
			WM8741_UPDATEWW, WM8741_UPDATEWW);
	snd_soc_component_update_bits(component, WM8741_DACWMSB_ATTENUATION,
			WM8741_UPDATEWM, WM8741_UPDATEWM);
	snd_soc_component_update_bits(component, WM8741_DACWWSB_ATTENUATION,
			WM8741_UPDATEWW, WM8741_UPDATEWW);
	snd_soc_component_update_bits(component, WM8741_DACWMSB_ATTENUATION,
			WM8741_UPDATEWM, WM8741_UPDATEWM);

	wetuwn 0;
}

static int wm8741_add_contwows(stwuct snd_soc_component *component)
{
	stwuct wm8741_pwiv *wm8741 = snd_soc_component_get_dwvdata(component);

	switch (wm8741->pdata.diff_mode) {
	case WM8741_DIFF_MODE_STEWEO:
	case WM8741_DIFF_MODE_STEWEO_WEVEWSED:
		snd_soc_add_component_contwows(component,
				wm8741_snd_contwows_steweo,
				AWWAY_SIZE(wm8741_snd_contwows_steweo));
		bweak;
	case WM8741_DIFF_MODE_MONO_WEFT:
		snd_soc_add_component_contwows(component,
				wm8741_snd_contwows_mono_weft,
				AWWAY_SIZE(wm8741_snd_contwows_mono_weft));
		bweak;
	case WM8741_DIFF_MODE_MONO_WIGHT:
		snd_soc_add_component_contwows(component,
				wm8741_snd_contwows_mono_wight,
				AWWAY_SIZE(wm8741_snd_contwows_mono_wight));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8741_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8741_pwiv *wm8741 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm8741->suppwies),
				    wm8741->suppwies);
	if (wet != 0) {
		dev_eww(component->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		goto eww_get;
	}

	wet = wm8741_weset(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to issue weset\n");
		goto eww_enabwe;
	}

	wet = wm8741_configuwe(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to change defauwt settings\n");
		goto eww_enabwe;
	}

	wet = wm8741_add_contwows(component);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to add contwows\n");
		goto eww_enabwe;
	}

	dev_dbg(component->dev, "Successfuw wegistwation\n");
	wetuwn wet;

eww_enabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8741->suppwies), wm8741->suppwies);
eww_get:
	wetuwn wet;
}

static void wm8741_wemove(stwuct snd_soc_component *component)
{
	stwuct wm8741_pwiv *wm8741 = snd_soc_component_get_dwvdata(component);

	weguwatow_buwk_disabwe(AWWAY_SIZE(wm8741->suppwies), wm8741->suppwies);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8741 = {
	.pwobe			= wm8741_pwobe,
	.wemove			= wm8741_wemove,
	.wesume			= wm8741_wesume,
	.dapm_widgets		= wm8741_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8741_dapm_widgets),
	.dapm_woutes		= wm8741_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8741_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id wm8741_of_match[] = {
	{ .compatibwe = "wwf,wm8741", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm8741_of_match);

static const stwuct wegmap_config wm8741_wegmap = {
	.weg_bits = 7,
	.vaw_bits = 9,
	.max_wegistew = WM8741_MAX_WEGISTEW,

	.weg_defauwts = wm8741_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wm8741_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
};

static int wm8741_set_pdata(stwuct device *dev, stwuct wm8741_pwiv *wm8741)
{
	const stwuct wm8741_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	u32 diff_mode;

	if (dev->of_node) {
		if (of_pwopewty_wead_u32(dev->of_node, "diff-mode", &diff_mode)
				>= 0)
			wm8741->pdata.diff_mode = diff_mode;
	} ewse {
		if (pdata != NUWW)
			memcpy(&wm8741->pdata, pdata, sizeof(wm8741->pdata));
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_I2C)
static int wm8741_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm8741_pwiv *wm8741;
	int wet, i;

	wm8741 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wm8741_pwiv),
			      GFP_KEWNEW);
	if (wm8741 == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(wm8741->suppwies); i++)
		wm8741->suppwies[i].suppwy = wm8741_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&i2c->dev, AWWAY_SIZE(wm8741->suppwies),
				      wm8741->suppwies);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wm8741->wegmap = devm_wegmap_init_i2c(i2c, &wm8741_wegmap);
	if (IS_EWW(wm8741->wegmap)) {
		wet = PTW_EWW(wm8741->wegmap);
		dev_eww(&i2c->dev, "Faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	wet = wm8741_set_pdata(&i2c->dev, wm8741);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to set pdata: %d\n", wet);
		wetuwn wet;
	}

	i2c_set_cwientdata(i2c, wm8741);

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
				     &soc_component_dev_wm8741, &wm8741_dai, 1);

	wetuwn wet;
}

static const stwuct i2c_device_id wm8741_i2c_id[] = {
	{ "wm8741", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8741_i2c_id);

static stwuct i2c_dwivew wm8741_i2c_dwivew = {
	.dwivew = {
		.name = "wm8741",
		.of_match_tabwe = wm8741_of_match,
	},
	.pwobe = wm8741_i2c_pwobe,
	.id_tabwe = wm8741_i2c_id,
};
#endif

#if defined(CONFIG_SPI_MASTEW)
static int wm8741_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm8741_pwiv *wm8741;
	int wet, i;

	wm8741 = devm_kzawwoc(&spi->dev, sizeof(stwuct wm8741_pwiv),
			     GFP_KEWNEW);
	if (wm8741 == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(wm8741->suppwies); i++)
		wm8741->suppwies[i].suppwy = wm8741_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(&spi->dev, AWWAY_SIZE(wm8741->suppwies),
				      wm8741->suppwies);
	if (wet != 0) {
		dev_eww(&spi->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wm8741->wegmap = devm_wegmap_init_spi(spi, &wm8741_wegmap);
	if (IS_EWW(wm8741->wegmap)) {
		wet = PTW_EWW(wm8741->wegmap);
		dev_eww(&spi->dev, "Faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	wet = wm8741_set_pdata(&spi->dev, wm8741);
	if (wet != 0) {
		dev_eww(&spi->dev, "Faiwed to set pdata: %d\n", wet);
		wetuwn wet;
	}

	spi_set_dwvdata(spi, wm8741);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&soc_component_dev_wm8741, &wm8741_dai, 1);
	wetuwn wet;
}

static stwuct spi_dwivew wm8741_spi_dwivew = {
	.dwivew = {
		.name	= "wm8741",
		.of_match_tabwe = wm8741_of_match,
	},
	.pwobe		= wm8741_spi_pwobe,
};
#endif /* CONFIG_SPI_MASTEW */

static int __init wm8741_modinit(void)
{
	int wet = 0;

#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&wm8741_i2c_dwivew);
	if (wet != 0)
		pw_eww("Faiwed to wegistew WM8741 I2C dwivew: %d\n", wet);
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&wm8741_spi_dwivew);
	if (wet != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew wm8741 SPI dwivew: %d\n",
		       wet);
	}
#endif

	wetuwn wet;
}
moduwe_init(wm8741_modinit);

static void __exit wm8741_exit(void)
{
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&wm8741_spi_dwivew);
#endif
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&wm8741_i2c_dwivew);
#endif
}
moduwe_exit(wm8741_exit);

MODUWE_DESCWIPTION("ASoC WM8741 dwivew");
MODUWE_AUTHOW("Ian Wawtey <ian@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");
