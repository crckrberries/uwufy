// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCM1681 ASoC codec dwivew
 *
 * Copywight (c) StweamUnwimited GmbH 2013
 *	Mawek Bewisko <mawek.bewisko@stweamunwimited.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define PCM1681_PCM_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE  |		\
			     SNDWV_PCM_FMTBIT_S24_WE)

#define PCM1681_PCM_WATES   (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 | \
			     SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100  | \
			     SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200  | \
			     SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_192000)

#define PCM1681_SOFT_MUTE_AWW		0xff
#define PCM1681_DEEMPH_WATE_MASK	0x18
#define PCM1681_DEEMPH_MASK		0x01

#define PCM1681_ATT_CONTWOW(X)	(X <= 6 ? X : X + 9) /* Attenuation wevew */
#define PCM1681_SOFT_MUTE	0x07	/* Soft mute contwow wegistew */
#define PCM1681_DAC_CONTWOW	0x08	/* DAC opewation contwow */
#define PCM1681_FMT_CONTWOW	0x09	/* Audio intewface data fowmat */
#define PCM1681_DEEMPH_CONTWOW	0x0a	/* De-emphasis contwow */
#define PCM1681_ZEWO_DETECT_STATUS	0x0e	/* Zewo detect status weg */

static const stwuct weg_defauwt pcm1681_weg_defauwts[] = {
	{ 0x01,	0xff },
	{ 0x02,	0xff },
	{ 0x03,	0xff },
	{ 0x04,	0xff },
	{ 0x05,	0xff },
	{ 0x06,	0xff },
	{ 0x07,	0x00 },
	{ 0x08,	0x00 },
	{ 0x09,	0x06 },
	{ 0x0A,	0x00 },
	{ 0x0B,	0xff },
	{ 0x0C,	0x0f },
	{ 0x0D,	0x00 },
	{ 0x10,	0xff },
	{ 0x11,	0xff },
	{ 0x12,	0x00 },
	{ 0x13,	0x00 },
};

static boow pcm1681_accessibwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn !((weg == 0x00) || (weg == 0x0f));
}

static boow pcm1681_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn pcm1681_accessibwe_weg(dev, weg) &&
		(weg != PCM1681_ZEWO_DETECT_STATUS);
}

stwuct pcm1681_pwivate {
	stwuct wegmap *wegmap;
	unsigned int fowmat;
	/* Cuwwent deemphasis status */
	unsigned int deemph;
	/* Cuwwent wate fow deemphasis contwow */
	unsigned int wate;
};

static const int pcm1681_deemph[] = { 44100, 48000, 32000 };

static int pcm1681_set_deemph(stwuct snd_soc_component *component)
{
	stwuct pcm1681_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int i, vaw = -1, enabwe = 0;

	if (pwiv->deemph) {
		fow (i = 0; i < AWWAY_SIZE(pcm1681_deemph); i++) {
			if (pcm1681_deemph[i] == pwiv->wate) {
				vaw = i;
				bweak;
			}
		}
	}

	if (vaw != -1) {
		wegmap_update_bits(pwiv->wegmap, PCM1681_DEEMPH_CONTWOW,
				   PCM1681_DEEMPH_WATE_MASK, vaw << 3);
		enabwe = 1;
	} ewse {
		enabwe = 0;
	}

	/* enabwe/disabwe deemphasis functionawity */
	wetuwn wegmap_update_bits(pwiv->wegmap, PCM1681_DEEMPH_CONTWOW,
					PCM1681_DEEMPH_MASK, enabwe);
}

static int pcm1681_get_deemph(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct pcm1681_pwivate *pwiv = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = pwiv->deemph;

	wetuwn 0;
}

static int pcm1681_put_deemph(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct pcm1681_pwivate *pwiv = snd_soc_component_get_dwvdata(component);

	pwiv->deemph = ucontwow->vawue.integew.vawue[0];

	wetuwn pcm1681_set_deemph(component);
}

static int pcm1681_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			      unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct pcm1681_pwivate *pwiv = snd_soc_component_get_dwvdata(component);

	/* The PCM1681 can onwy be consumew to aww cwocks */
	if ((fowmat & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_CBC_CFC) {
		dev_eww(component->dev, "Invawid cwocking mode\n");
		wetuwn -EINVAW;
	}

	pwiv->fowmat = fowmat;

	wetuwn 0;
}

static int pcm1681_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm1681_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int vaw;

	if (mute)
		vaw = PCM1681_SOFT_MUTE_AWW;
	ewse
		vaw = 0;

	wetuwn wegmap_wwite(pwiv->wegmap, PCM1681_SOFT_MUTE, vaw);
}

static int pcm1681_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct pcm1681_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int vaw = 0, wet;

	pwiv->wate = pawams_wate(pawams);

	switch (pwiv->fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		switch (pawams_width(pawams)) {
		case 24:
			vaw = 0;
			bweak;
		case 16:
			vaw = 3;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SND_SOC_DAIFMT_I2S:
		vaw = 0x04;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw = 0x05;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(pwiv->wegmap, PCM1681_FMT_CONTWOW, 0x0f, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn pcm1681_set_deemph(component);
}

static const stwuct snd_soc_dai_ops pcm1681_dai_ops = {
	.set_fmt	= pcm1681_set_dai_fmt,
	.hw_pawams	= pcm1681_hw_pawams,
	.mute_stweam	= pcm1681_mute,
	.no_captuwe_mute = 1,
};

static const stwuct snd_soc_dapm_widget pcm1681_dapm_widgets[] = {
SND_SOC_DAPM_OUTPUT("VOUT1"),
SND_SOC_DAPM_OUTPUT("VOUT2"),
SND_SOC_DAPM_OUTPUT("VOUT3"),
SND_SOC_DAPM_OUTPUT("VOUT4"),
SND_SOC_DAPM_OUTPUT("VOUT5"),
SND_SOC_DAPM_OUTPUT("VOUT6"),
SND_SOC_DAPM_OUTPUT("VOUT7"),
SND_SOC_DAPM_OUTPUT("VOUT8"),
};

static const stwuct snd_soc_dapm_woute pcm1681_dapm_woutes[] = {
	{ "VOUT1", NUWW, "Pwayback" },
	{ "VOUT2", NUWW, "Pwayback" },
	{ "VOUT3", NUWW, "Pwayback" },
	{ "VOUT4", NUWW, "Pwayback" },
	{ "VOUT5", NUWW, "Pwayback" },
	{ "VOUT6", NUWW, "Pwayback" },
	{ "VOUT7", NUWW, "Pwayback" },
	{ "VOUT8", NUWW, "Pwayback" },
};

static const DECWAWE_TWV_DB_SCAWE(pcm1681_dac_twv, -6350, 50, 1);

static const stwuct snd_kcontwow_new pcm1681_contwows[] = {
	SOC_DOUBWE_W_TWV("Channew 1/2 Pwayback Vowume",
			PCM1681_ATT_CONTWOW(1), PCM1681_ATT_CONTWOW(2), 0,
			0x7f, 0, pcm1681_dac_twv),
	SOC_DOUBWE_W_TWV("Channew 3/4 Pwayback Vowume",
			PCM1681_ATT_CONTWOW(3), PCM1681_ATT_CONTWOW(4), 0,
			0x7f, 0, pcm1681_dac_twv),
	SOC_DOUBWE_W_TWV("Channew 5/6 Pwayback Vowume",
			PCM1681_ATT_CONTWOW(5), PCM1681_ATT_CONTWOW(6), 0,
			0x7f, 0, pcm1681_dac_twv),
	SOC_DOUBWE_W_TWV("Channew 7/8 Pwayback Vowume",
			PCM1681_ATT_CONTWOW(7), PCM1681_ATT_CONTWOW(8), 0,
			0x7f, 0, pcm1681_dac_twv),
	SOC_SINGWE_BOOW_EXT("De-emphasis Switch", 0,
			    pcm1681_get_deemph, pcm1681_put_deemph),
};

static stwuct snd_soc_dai_dwivew pcm1681_dai = {
	.name = "pcm1681-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 8,
		.wates = PCM1681_PCM_WATES,
		.fowmats = PCM1681_PCM_FOWMATS,
	},
	.ops = &pcm1681_dai_ops,
};

#ifdef CONFIG_OF
static const stwuct of_device_id pcm1681_dt_ids[] = {
	{ .compatibwe = "ti,pcm1681", },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcm1681_dt_ids);
#endif

static const stwuct wegmap_config pcm1681_wegmap = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.max_wegistew		= 0x13,
	.weg_defauwts		= pcm1681_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(pcm1681_weg_defauwts),
	.wwiteabwe_weg		= pcm1681_wwiteabwe_weg,
	.weadabwe_weg		= pcm1681_accessibwe_weg,
};

static const stwuct snd_soc_component_dwivew soc_component_dev_pcm1681 = {
	.contwows		= pcm1681_contwows,
	.num_contwows		= AWWAY_SIZE(pcm1681_contwows),
	.dapm_widgets		= pcm1681_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(pcm1681_dapm_widgets),
	.dapm_woutes		= pcm1681_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(pcm1681_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct i2c_device_id pcm1681_i2c_id[] = {
	{"pcm1681", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, pcm1681_i2c_id);

static int pcm1681_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct pcm1681_pwivate *pwiv;

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &pcm1681_wegmap);
	if (IS_EWW(pwiv->wegmap)) {
		wet = PTW_EWW(pwiv->wegmap);
		dev_eww(&cwient->dev, "Faiwed to cweate wegmap: %d\n", wet);
		wetuwn wet;
	}

	i2c_set_cwientdata(cwient, pwiv);

	wetuwn devm_snd_soc_wegistew_component(&cwient->dev,
		&soc_component_dev_pcm1681,
		&pcm1681_dai, 1);
}

static stwuct i2c_dwivew pcm1681_i2c_dwivew = {
	.dwivew = {
		.name	= "pcm1681",
		.of_match_tabwe = of_match_ptw(pcm1681_dt_ids),
	},
	.id_tabwe	= pcm1681_i2c_id,
	.pwobe		= pcm1681_i2c_pwobe,
};

moduwe_i2c_dwivew(pcm1681_i2c_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments PCM1681 AWSA SoC Codec Dwivew");
MODUWE_AUTHOW("Mawek Bewisko <mawek.bewisko@stweamunwimited.com>");
MODUWE_WICENSE("GPW");
