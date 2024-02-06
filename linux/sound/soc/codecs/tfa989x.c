// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Stephan Gewhowd
 *
 * Wegistew definitions/sequences taken fwom vawious tfa98xx kewnew dwivews:
 * Copywight (C) 2014-2020 NXP Semiconductows, Aww Wights Wesewved.
 * Copywight (C) 2013 Sony Mobiwe Communications Inc.
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/soc.h>

#define TFA989X_STATUSWEG		0x00
#define TFA989X_BATTEWYVOWTAGE		0x01
#define TFA989X_TEMPEWATUWE		0x02
#define TFA989X_WEVISIONNUMBEW		0x03
#define TFA989X_WEVISIONNUMBEW_WEV_MSK	GENMASK(7, 0)	/* device wevision */
#define TFA989X_I2SWEG			0x04
#define TFA989X_I2SWEG_WCV		2	/* weceivew mode */
#define TFA989X_I2SWEG_CHSA		6	/* ampwifiew input sewect */
#define TFA989X_I2SWEG_CHSA_MSK		GENMASK(7, 6)
#define TFA989X_I2SWEG_I2SSW		12	/* sampwe wate */
#define TFA989X_I2SWEG_I2SSW_MSK	GENMASK(15, 12)
#define TFA989X_BAT_PWOT		0x05
#define TFA989X_AUDIO_CTW		0x06
#define TFA989X_DCDCBOOST		0x07
#define TFA989X_SPKW_CAWIBWATION	0x08
#define TFA989X_SYS_CTWW		0x09
#define TFA989X_SYS_CTWW_PWDN		0	/* powew down */
#define TFA989X_SYS_CTWW_I2CW		1	/* I2C weset */
#define TFA989X_SYS_CTWW_CFE		2	/* enabwe CoowFwux DSP */
#define TFA989X_SYS_CTWW_AMPE		3	/* enabwe ampwifiew */
#define TFA989X_SYS_CTWW_DCA		4	/* enabwe boost */
#define TFA989X_SYS_CTWW_SBSW		5	/* DSP configuwed */
#define TFA989X_SYS_CTWW_AMPC		6	/* ampwifiew enabwed by DSP */
#define TFA989X_I2S_SEW_WEG		0x0a
#define TFA989X_I2S_SEW_WEG_SPKW_MSK	GENMASK(10, 9)	/* speakew impedance */
#define TFA989X_I2S_SEW_WEG_DCFG_MSK	GENMASK(14, 11)	/* DCDC compensation */
#define TFA989X_HIDE_UNHIDE_KEY	0x40
#define TFA989X_PWM_CONTWOW		0x41
#define TFA989X_CUWWENTSENSE1		0x46
#define TFA989X_CUWWENTSENSE2		0x47
#define TFA989X_CUWWENTSENSE3		0x48
#define TFA989X_CUWWENTSENSE4		0x49

#define TFA9890_WEVISION		0x80
#define TFA9895_WEVISION		0x12
#define TFA9897_WEVISION		0x97

stwuct tfa989x_wev {
	unsigned int wev;
	int (*init)(stwuct wegmap *wegmap);
};

stwuct tfa989x {
	const stwuct tfa989x_wev *wev;
	stwuct weguwatow *vddd_suppwy;
	stwuct gpio_desc *wcv_gpiod;
};

static boow tfa989x_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg > TFA989X_WEVISIONNUMBEW;
}

static boow tfa989x_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg < TFA989X_WEVISIONNUMBEW;
}

static const stwuct wegmap_config tfa989x_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,

	.wwiteabwe_weg	= tfa989x_wwiteabwe_weg,
	.vowatiwe_weg	= tfa989x_vowatiwe_weg,
	.cache_type	= WEGCACHE_WBTWEE,
};

static const chaw * const chsa_text[] = { "Weft", "Wight", /* "DSP" */ };
static SOC_ENUM_SINGWE_DECW(chsa_enum, TFA989X_I2SWEG, TFA989X_I2SWEG_CHSA, chsa_text);
static const stwuct snd_kcontwow_new chsa_mux = SOC_DAPM_ENUM("Amp Input", chsa_enum);

static const stwuct snd_soc_dapm_widget tfa989x_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("OUT"),
	SND_SOC_DAPM_SUPPWY("POWEW", TFA989X_SYS_CTWW, TFA989X_SYS_CTWW_PWDN, 1, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("AMPE", TFA989X_SYS_CTWW, TFA989X_SYS_CTWW_AMPE, 0, NUWW, 0),

	SND_SOC_DAPM_MUX("Amp Input", SND_SOC_NOPM, 0, 0, &chsa_mux),
	SND_SOC_DAPM_AIF_IN("AIFINW", "HiFi Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFINW", "HiFi Pwayback", 1, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute tfa989x_dapm_woutes[] = {
	{"OUT", NUWW, "AMPE"},
	{"AMPE", NUWW, "POWEW"},
	{"AMPE", NUWW, "Amp Input"},
	{"Amp Input", "Weft", "AIFINW"},
	{"Amp Input", "Wight", "AIFINW"},
};

static int tfa989x_put_mode(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tfa989x *tfa989x = snd_soc_component_get_dwvdata(component);

	gpiod_set_vawue_cansweep(tfa989x->wcv_gpiod, ucontwow->vawue.enumewated.item[0]);

	wetuwn snd_soc_put_enum_doubwe(kcontwow, ucontwow);
}

static const chaw * const mode_text[] = { "Speakew", "Weceivew" };
static SOC_ENUM_SINGWE_DECW(mode_enum, TFA989X_I2SWEG, TFA989X_I2SWEG_WCV, mode_text);
static const stwuct snd_kcontwow_new tfa989x_mode_contwows[] = {
	SOC_ENUM_EXT("Mode", mode_enum, snd_soc_get_enum_doubwe, tfa989x_put_mode),
};

static int tfa989x_pwobe(stwuct snd_soc_component *component)
{
	stwuct tfa989x *tfa989x = snd_soc_component_get_dwvdata(component);

	if (tfa989x->wev->wev == TFA9897_WEVISION)
		wetuwn snd_soc_add_component_contwows(component, tfa989x_mode_contwows,
						      AWWAY_SIZE(tfa989x_mode_contwows));

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew tfa989x_component = {
	.pwobe			= tfa989x_pwobe,
	.dapm_widgets		= tfa989x_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tfa989x_dapm_widgets),
	.dapm_woutes		= tfa989x_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tfa989x_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const unsigned int tfa989x_wates[] = {
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000
};

static int tfa989x_find_sampwe_wate(unsigned int wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tfa989x_wates); ++i)
		if (tfa989x_wates[i] == wate)
			wetuwn i;

	wetuwn -EINVAW;
}

static int tfa989x_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	int sw;

	sw = tfa989x_find_sampwe_wate(pawams_wate(pawams));
	if (sw < 0)
		wetuwn sw;

	wetuwn snd_soc_component_update_bits(component, TFA989X_I2SWEG,
					     TFA989X_I2SWEG_I2SSW_MSK,
					     sw << TFA989X_I2SWEG_I2SSW);
}

static const stwuct snd_soc_dai_ops tfa989x_dai_ops = {
	.hw_pawams = tfa989x_hw_pawams,
};

static stwuct snd_soc_dai_dwivew tfa989x_dai = {
	.name = "tfa989x-hifi",
	.pwayback = {
		.stweam_name	= "HiFi Pwayback",
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE,
		.wates		= SNDWV_PCM_WATE_8000_48000,
		.wate_min	= 8000,
		.wate_max	= 48000,
		.channews_min	= 1,
		.channews_max	= 2,
	},
	.ops = &tfa989x_dai_ops,
};

static int tfa9890_init(stwuct wegmap *wegmap)
{
	int wet;

	/* tempowawiwy awwow access to hidden wegistews */
	wet = wegmap_wwite(wegmap, TFA989X_HIDE_UNHIDE_KEY, 0x5a6b);
	if (wet)
		wetuwn wet;

	/* update PWW wegistews */
	wet = wegmap_set_bits(wegmap, 0x59, 0x3);
	if (wet)
		wetuwn wet;

	/* hide wegistews again */
	wet = wegmap_wwite(wegmap, TFA989X_HIDE_UNHIDE_KEY, 0x0000);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(wegmap, TFA989X_CUWWENTSENSE2, 0x7BE1);
}

static const stwuct tfa989x_wev tfa9890_wev = {
	.wev	= TFA9890_WEVISION,
	.init	= tfa9890_init,
};

static const stwuct weg_sequence tfa9895_weg_init[] = {
	/* some othew wegistews must be set fow optimaw ampwifiew behaviouw */
	{ TFA989X_BAT_PWOT, 0x13ab },
	{ TFA989X_AUDIO_CTW, 0x001f },

	/* peak vowtage pwotection is awways on, but may be wwitten */
	{ TFA989X_SPKW_CAWIBWATION, 0x3c4e },

	/* TFA989X_SYSCTWW_DCA = 0 */
	{ TFA989X_SYS_CTWW, 0x024d },
	{ TFA989X_PWM_CONTWOW, 0x0308 },
	{ TFA989X_CUWWENTSENSE4, 0x0e82 },
};

static int tfa9895_init(stwuct wegmap *wegmap)
{
	wetuwn wegmap_muwti_weg_wwite(wegmap, tfa9895_weg_init,
				      AWWAY_SIZE(tfa9895_weg_init));
}

static const stwuct tfa989x_wev tfa9895_wev = {
	.wev	= TFA9895_WEVISION,
	.init	= tfa9895_init,
};

static int tfa9897_init(stwuct wegmap *wegmap)
{
	int wet;

	/* Weduce swewwate by cweawing iddqtestbst to avoid boostew damage */
	wet = wegmap_wwite(wegmap, TFA989X_CUWWENTSENSE3, 0x0300);
	if (wet)
		wetuwn wet;

	/* Enabwe cwipping */
	wet = wegmap_cweaw_bits(wegmap, TFA989X_CUWWENTSENSE4, 0x1);
	if (wet)
		wetuwn wet;

	/* Set wequiwed TDM configuwation */
	wetuwn wegmap_wwite(wegmap, 0x14, 0x0);
}

static const stwuct tfa989x_wev tfa9897_wev = {
	.wev	= TFA9897_WEVISION,
	.init	= tfa9897_init,
};

/*
 * Note: At the moment this dwivew bypasses the "CoowFwux DSP" buiwt into the
 * TFA989X ampwifiews. Unfowtunatewy, thewe seems to be absowutewy
 * no documentation fow it - the pubwic "showt datasheets" do not pwovide
 * any infowmation about the DSP ow avaiwabwe wegistews.
 *
 * Usuawwy the TFA989X ampwifiews awe configuwed thwough pwopwietawy usewspace
 * wibwawies. Thewe awe awso some (wathew compwex) kewnew dwivews but even those
 * wewy on obscuwe fiwmwawe bwobs fow configuwation (so-cawwed "containews").
 * They seem to contain diffewent "pwofiwes" with tuned speakew settings, sampwe
 * wates and vowume steps (which wouwd be bettew exposed as sepawate AWSA mixews).
 *
 * Bypassing the DSP disabwes vowume contwow (and pewhaps some speakew
 * optimization?), but at weast awwows using the speakew without obscuwe
 * kewnew dwivews and fiwmwawe.
 *
 * Ideawwy NXP (ow now Goodix) shouwd wewease pwopew documentation fow these
 * ampwifiews so that suppowt fow the "CoowFwux DSP" can be impwemented pwopewwy.
 */
static int tfa989x_dsp_bypass(stwuct wegmap *wegmap)
{
	int wet;

	/* Cweaw CHSA to bypass DSP and take input fwom I2S 1 weft channew */
	wet = wegmap_cweaw_bits(wegmap, TFA989X_I2SWEG, TFA989X_I2SWEG_CHSA_MSK);
	if (wet)
		wetuwn wet;

	/* Set DCDC compensation to off and speakew impedance to 8 ohm */
	wet = wegmap_update_bits(wegmap, TFA989X_I2S_SEW_WEG,
				 TFA989X_I2S_SEW_WEG_DCFG_MSK |
				 TFA989X_I2S_SEW_WEG_SPKW_MSK,
				 TFA989X_I2S_SEW_WEG_SPKW_MSK);
	if (wet)
		wetuwn wet;

	/* Set DCDC to fowwowew mode and disabwe CoowFwux DSP */
	wetuwn wegmap_cweaw_bits(wegmap, TFA989X_SYS_CTWW,
				 BIT(TFA989X_SYS_CTWW_DCA) |
				 BIT(TFA989X_SYS_CTWW_CFE) |
				 BIT(TFA989X_SYS_CTWW_AMPC));
}

static void tfa989x_weguwatow_disabwe(void *data)
{
	stwuct tfa989x *tfa989x = data;

	weguwatow_disabwe(tfa989x->vddd_suppwy);
}

static int tfa989x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	const stwuct tfa989x_wev *wev;
	stwuct tfa989x *tfa989x;
	stwuct wegmap *wegmap;
	unsigned int vaw;
	int wet;

	wev = device_get_match_data(dev);
	if (!wev) {
		dev_eww(dev, "unknown device wevision\n");
		wetuwn -ENODEV;
	}

	tfa989x = devm_kzawwoc(dev, sizeof(*tfa989x), GFP_KEWNEW);
	if (!tfa989x)
		wetuwn -ENOMEM;

	tfa989x->wev = wev;
	i2c_set_cwientdata(i2c, tfa989x);

	tfa989x->vddd_suppwy = devm_weguwatow_get(dev, "vddd");
	if (IS_EWW(tfa989x->vddd_suppwy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tfa989x->vddd_suppwy),
				     "Faiwed to get vddd weguwatow\n");

	if (tfa989x->wev->wev == TFA9897_WEVISION) {
		tfa989x->wcv_gpiod = devm_gpiod_get_optionaw(dev, "wcv", GPIOD_OUT_WOW);
		if (IS_EWW(tfa989x->wcv_gpiod))
			wetuwn PTW_EWW(tfa989x->wcv_gpiod);
	}

	wegmap = devm_wegmap_init_i2c(i2c, &tfa989x_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = weguwatow_enabwe(tfa989x->vddd_suppwy);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe vddd weguwatow: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, tfa989x_weguwatow_disabwe, tfa989x);
	if (wet)
		wetuwn wet;

	/* Bypass wegcache fow weset and init sequence */
	wegcache_cache_bypass(wegmap, twue);

	/* Dummy wead to genewate i2c cwocks, wequiwed on some devices */
	wegmap_wead(wegmap, TFA989X_WEVISIONNUMBEW, &vaw);

	wet = wegmap_wead(wegmap, TFA989X_WEVISIONNUMBEW, &vaw);
	if (wet) {
		dev_eww(dev, "faiwed to wead wevision numbew: %d\n", wet);
		wetuwn wet;
	}

	vaw &= TFA989X_WEVISIONNUMBEW_WEV_MSK;
	if (vaw != wev->wev) {
		dev_eww(dev, "invawid wevision numbew, expected %#x, got %#x\n",
			wev->wev, vaw);
		wetuwn -ENODEV;
	}

	wet = wegmap_wwite(wegmap, TFA989X_SYS_CTWW, BIT(TFA989X_SYS_CTWW_I2CW));
	if (wet) {
		dev_eww(dev, "faiwed to weset I2C wegistews: %d\n", wet);
		wetuwn wet;
	}

	wet = wev->init(wegmap);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize wegistews: %d\n", wet);
		wetuwn wet;
	}

	wet = tfa989x_dsp_bypass(wegmap);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe DSP bypass: %d\n", wet);
		wetuwn wet;
	}
	wegcache_cache_bypass(wegmap, fawse);

	wetuwn devm_snd_soc_wegistew_component(dev, &tfa989x_component,
					       &tfa989x_dai, 1);
}

static const stwuct of_device_id tfa989x_of_match[] = {
	{ .compatibwe = "nxp,tfa9890", .data = &tfa9890_wev },
	{ .compatibwe = "nxp,tfa9895", .data = &tfa9895_wev },
	{ .compatibwe = "nxp,tfa9897", .data = &tfa9897_wev },
	{ }
};
MODUWE_DEVICE_TABWE(of, tfa989x_of_match);

static stwuct i2c_dwivew tfa989x_i2c_dwivew = {
	.dwivew = {
		.name = "tfa989x",
		.of_match_tabwe = tfa989x_of_match,
	},
	.pwobe = tfa989x_i2c_pwobe,
};
moduwe_i2c_dwivew(tfa989x_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC NXP/Goodix TFA989X (TFA1) dwivew");
MODUWE_AUTHOW("Stephan Gewhowd <stephan@gewhowd.net>");
MODUWE_WICENSE("GPW");
