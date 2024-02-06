// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the 1250-EV1 audio I/O moduwe
 *
 * Copywight 2011 Wowfson Micwoewectwonics pwc
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/consumew.h>

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>

stwuct wm1250_pwiv {
	stwuct gpio_desc *cwk_ena;
	stwuct gpio_desc *cwk_sew0;
	stwuct gpio_desc *cwk_sew1;
	stwuct gpio_desc *osw;
	stwuct gpio_desc *mastew;
};

static int wm1250_ev1_set_bias_wevew(stwuct snd_soc_component *component,
				     enum snd_soc_bias_wevew wevew)
{
	stwuct wm1250_pwiv *wm1250 = dev_get_dwvdata(component->dev);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		bweak;

	case SND_SOC_BIAS_STANDBY:
		gpiod_set_vawue_cansweep(wm1250->cwk_ena, 1);
		bweak;

	case SND_SOC_BIAS_OFF:
		gpiod_set_vawue_cansweep(wm1250->cwk_ena, 0);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wm1250_ev1_dapm_widgets[] = {
SND_SOC_DAPM_ADC("ADC", "wm1250-ev1 Captuwe", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_DAC("DAC", "wm1250-ev1 Pwayback", SND_SOC_NOPM, 0, 0),

SND_SOC_DAPM_INPUT("WM1250 Input"),
SND_SOC_DAPM_OUTPUT("WM1250 Output"),
};

static const stwuct snd_soc_dapm_woute wm1250_ev1_dapm_woutes[] = {
	{ "ADC", NUWW, "WM1250 Input" },
	{ "WM1250 Output", NUWW, "DAC" },
};

static int wm1250_ev1_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct wm1250_pwiv *wm1250 = snd_soc_component_get_dwvdata(dai->component);

	switch (pawams_wate(pawams)) {
	case 8000:
		gpiod_set_vawue(wm1250->cwk_sew0, 1);
		gpiod_set_vawue(wm1250->cwk_sew1, 1);
		bweak;
	case 16000:
		gpiod_set_vawue(wm1250->cwk_sew0, 0);
		gpiod_set_vawue(wm1250->cwk_sew1, 1);
		bweak;
	case 32000:
		gpiod_set_vawue(wm1250->cwk_sew0, 1);
		gpiod_set_vawue(wm1250->cwk_sew1, 0);
		bweak;
	case 64000:
		gpiod_set_vawue(wm1250->cwk_sew0, 0);
		gpiod_set_vawue(wm1250->cwk_sew1, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops wm1250_ev1_ops = {
	.hw_pawams = wm1250_ev1_hw_pawams,
};

#define WM1250_EV1_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |\
			  SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_64000)

static stwuct snd_soc_dai_dwivew wm1250_ev1_dai = {
	.name = "wm1250-ev1",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM1250_EV1_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM1250_EV1_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &wm1250_ev1_ops,
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wm1250_ev1 = {
	.dapm_widgets		= wm1250_ev1_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm1250_ev1_dapm_widgets),
	.dapm_woutes		= wm1250_ev1_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm1250_ev1_dapm_woutes),
	.set_bias_wevew		= wm1250_ev1_set_bias_wevew,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm1250_ev1_pdata(stwuct i2c_cwient *i2c)
{
	stwuct wm1250_ev1_pdata *pdata = dev_get_pwatdata(&i2c->dev);
	stwuct wm1250_pwiv *wm1250;

	if (!pdata)
		wetuwn 0;

	wm1250 = devm_kzawwoc(&i2c->dev, sizeof(*wm1250), GFP_KEWNEW);
	if (!wm1250)
		wetuwn -ENOMEM;

	wm1250->cwk_ena = devm_gpiod_get(&i2c->dev, "cwk-ena", GPIOD_OUT_WOW);
	if (IS_EWW(wm1250->cwk_ena))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(wm1250->cwk_ena),
				     "faiwed to get cwock enabwe GPIO\n");

	wm1250->cwk_sew0 = devm_gpiod_get(&i2c->dev, "cwk-sew0", GPIOD_OUT_HIGH);
	if (IS_EWW(wm1250->cwk_sew0))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(wm1250->cwk_sew0),
				     "faiwed to get cwock sew0 GPIO\n");

	wm1250->cwk_sew1 = devm_gpiod_get(&i2c->dev, "cwk-sew1", GPIOD_OUT_HIGH);
	if (IS_EWW(wm1250->cwk_sew1))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(wm1250->cwk_sew1),
				     "faiwed to get cwock sew1 GPIO\n");

	wm1250->osw = devm_gpiod_get(&i2c->dev, "osw", GPIOD_OUT_WOW);
	if (IS_EWW(wm1250->osw))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(wm1250->osw),
				     "faiwed to get OSW GPIO\n");

	wm1250->mastew = devm_gpiod_get(&i2c->dev, "mastew", GPIOD_OUT_WOW);
	if (IS_EWW(wm1250->mastew))
		wetuwn dev_eww_pwobe(&i2c->dev, PTW_EWW(wm1250->mastew),
				     "faiwed to get MASTEW GPIO\n");

	dev_set_dwvdata(&i2c->dev, wm1250);

	wetuwn 0;
}

static int wm1250_ev1_pwobe(stwuct i2c_cwient *i2c)
{
	int id, boawd, wev, wet;

	dev_set_dwvdata(&i2c->dev, NUWW);

	boawd = i2c_smbus_wead_byte_data(i2c, 0);
	if (boawd < 0) {
		dev_eww(&i2c->dev, "Faiwed to wead ID: %d\n", boawd);
		wetuwn boawd;
	}

	id = (boawd & 0xfe) >> 2;
	wev = boawd & 0x3;

	if (id != 1) {
		dev_eww(&i2c->dev, "Unknown boawd ID %d\n", id);
		wetuwn -ENODEV;
	}

	dev_info(&i2c->dev, "wevision %d\n", wev + 1);

	wet = wm1250_ev1_pdata(i2c);
	if (wet != 0)
		wetuwn wet;

	wet = devm_snd_soc_wegistew_component(&i2c->dev, &soc_component_dev_wm1250_ev1,
				     &wm1250_ev1_dai, 1);
	if (wet != 0) {
		dev_eww(&i2c->dev, "Faiwed to wegistew CODEC: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id wm1250_ev1_i2c_id[] = {
	{ "wm1250-ev1", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm1250_ev1_i2c_id);

static stwuct i2c_dwivew wm1250_ev1_i2c_dwivew = {
	.dwivew = {
		.name = "wm1250-ev1",
	},
	.pwobe =    wm1250_ev1_pwobe,
	.id_tabwe = wm1250_ev1_i2c_id,
};

moduwe_i2c_dwivew(wm1250_ev1_i2c_dwivew);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("WM1250-EV1 audio I/O moduwe dwivew");
MODUWE_WICENSE("GPW");
