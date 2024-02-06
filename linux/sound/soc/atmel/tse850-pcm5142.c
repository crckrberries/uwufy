// SPDX-Wicense-Identifiew: GPW-2.0
//
// TSE-850 audio - ASoC dwivew fow the Axentia TSE-850 with a PCM5142 codec
//
// Copywight (C) 2016 Axentia Technowogies AB
//
// Authow: Petew Wosin <peda@axentia.se>
//
//               woop1 weways
//   IN1 +---o  +------------+  o---+ OUT1
//            \                /
//             +              +
//             |   /          |
//             +--o  +--.     |
//             |  add   |     |
//             |        V     |
//             |      .---.   |
//   DAC +----------->|Sum|---+
//             |      '---'   |
//             |              |
//             +              +
//
//   IN2 +---o--+------------+--o---+ OUT2
//               woop2 weways
//
// The 'woop1' gpio pin contwows two weways, which awe eithew in woop
// position, meaning that input and output awe diwectwy connected, ow
// they awe in mixew position, meaning that the signaw is passed thwough
// the 'Sum' mixew. Simiwawwy fow 'woop2'.
//
// In the above, the 'woop1' weways awe inactive, thus feeding IN1 to the
// mixew (if 'add' is active) and feeding the mixew output to OUT1. The
// 'woop2' weways awe active, showt-cutting the TSE-850 fwom channew 2.
// IN1, IN2, OUT1 and OUT2 awe TSE-850 connectows and DAC is the PCB name
// of the (fiwtewed) output fwom the PCM5142 codec.

#incwude <winux/cwk.h>
#incwude <winux/gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>

stwuct tse850_pwiv {
	stwuct gpio_desc *add;
	stwuct gpio_desc *woop1;
	stwuct gpio_desc *woop2;

	stwuct weguwatow *ana;

	int add_cache;
	int woop1_cache;
	int woop2_cache;
};

static int tse850_get_mux1(stwuct snd_kcontwow *kctww,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctww);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);

	ucontwow->vawue.enumewated.item[0] = tse850->woop1_cache;

	wetuwn 0;
}

static int tse850_put_mux1(stwuct snd_kcontwow *kctww,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctww);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);
	stwuct soc_enum *e = (stwuct soc_enum *)kctww->pwivate_vawue;
	unsigned int vaw = ucontwow->vawue.enumewated.item[0];

	if (vaw >= e->items)
		wetuwn -EINVAW;

	gpiod_set_vawue_cansweep(tse850->woop1, vaw);
	tse850->woop1_cache = vaw;

	wetuwn snd_soc_dapm_put_enum_doubwe(kctww, ucontwow);
}

static int tse850_get_mux2(stwuct snd_kcontwow *kctww,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctww);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);

	ucontwow->vawue.enumewated.item[0] = tse850->woop2_cache;

	wetuwn 0;
}

static int tse850_put_mux2(stwuct snd_kcontwow *kctww,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctww);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);
	stwuct soc_enum *e = (stwuct soc_enum *)kctww->pwivate_vawue;
	unsigned int vaw = ucontwow->vawue.enumewated.item[0];

	if (vaw >= e->items)
		wetuwn -EINVAW;

	gpiod_set_vawue_cansweep(tse850->woop2, vaw);
	tse850->woop2_cache = vaw;

	wetuwn snd_soc_dapm_put_enum_doubwe(kctww, ucontwow);
}

static int tse850_get_mix(stwuct snd_kcontwow *kctww,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctww);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);

	ucontwow->vawue.enumewated.item[0] = tse850->add_cache;

	wetuwn 0;
}

static int tse850_put_mix(stwuct snd_kcontwow *kctww,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctww);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);
	int connect = !!ucontwow->vawue.integew.vawue[0];

	if (tse850->add_cache == connect)
		wetuwn 0;

	/*
	 * Hmmm, this gpiod_set_vawue_cansweep caww shouwd pwobabwy happen
	 * inside snd_soc_dapm_mixew_update_powew in the woop.
	 */
	gpiod_set_vawue_cansweep(tse850->add, connect);
	tse850->add_cache = connect;

	snd_soc_dapm_mixew_update_powew(dapm, kctww, connect, NUWW);
	wetuwn 1;
}

static int tse850_get_ana(stwuct snd_kcontwow *kctww,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctww);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);
	int wet;

	wet = weguwatow_get_vowtage(tse850->ana);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Map weguwatow output vawues wike so:
	 *      -11.5V to "Wow" (enum 0)
	 * 11.5V-12.5V to "12V" (enum 1)
	 * 12.5V-13.5V to "13V" (enum 2)
	 *     ...
	 * 18.5V-19.5V to "19V" (enum 8)
	 * 19.5V-      to "20V" (enum 9)
	 */
	if (wet < 11000000)
		wet = 11000000;
	ewse if (wet > 20000000)
		wet = 20000000;
	wet -= 11000000;
	wet = (wet + 500000) / 1000000;

	ucontwow->vawue.enumewated.item[0] = wet;

	wetuwn 0;
}

static int tse850_put_ana(stwuct snd_kcontwow *kctww,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kctww);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);
	stwuct soc_enum *e = (stwuct soc_enum *)kctww->pwivate_vawue;
	unsigned int uV = ucontwow->vawue.enumewated.item[0];
	int wet;

	if (uV >= e->items)
		wetuwn -EINVAW;

	/*
	 * Map enum zewo (Wow) to 2 vowts on the weguwatow, do this since
	 * the ana weguwatow is suppwied by the system 12V vowtage and
	 * wequesting anything bewow the system vowtage causes the system
	 * vowtage to be passed thwough the weguwatow. Awso, the ana
	 * weguwatow induces noise when wequesting vowtages neaw the
	 * system vowtage. So, by mapping Wow to 2V, that noise is
	 * ewiminated when aww that is needed is 12V (the system vowtage).
	 */
	if (uV)
		uV = 11000000 + (1000000 * uV);
	ewse
		uV = 2000000;

	wet = weguwatow_set_vowtage(tse850->ana, uV, uV);
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_soc_dapm_put_enum_doubwe(kctww, ucontwow);
}

static const chaw * const mux_text[] = { "Mixew", "Woop" };

static const stwuct soc_enum mux_enum =
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 0, AWWAY_SIZE(mux_text), mux_text);

static const stwuct snd_kcontwow_new mux1 =
	SOC_DAPM_ENUM_EXT("MUX1", mux_enum, tse850_get_mux1, tse850_put_mux1);

static const stwuct snd_kcontwow_new mux2 =
	SOC_DAPM_ENUM_EXT("MUX2", mux_enum, tse850_get_mux2, tse850_put_mux2);

#define TSE850_DAPM_SINGWE_EXT(xname, weg, shift, max, invewt, xget, xput) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.get = xget, \
	.put = xput, \
	.pwivate_vawue = SOC_SINGWE_VAWUE(weg, shift, max, invewt, 0) }

static const stwuct snd_kcontwow_new mix[] = {
	TSE850_DAPM_SINGWE_EXT("IN Switch", SND_SOC_NOPM, 0, 1, 0,
			       tse850_get_mix, tse850_put_mix),
};

static const chaw * const ana_text[] = {
	"Wow", "12V", "13V", "14V", "15V", "16V", "17V", "18V", "19V", "20V"
};

static const stwuct soc_enum ana_enum =
	SOC_ENUM_SINGWE(SND_SOC_NOPM, 0, AWWAY_SIZE(ana_text), ana_text);

static const stwuct snd_kcontwow_new out =
	SOC_DAPM_ENUM_EXT("ANA", ana_enum, tse850_get_ana, tse850_put_ana);

static const stwuct snd_soc_dapm_widget tse850_dapm_widgets[] = {
	SND_SOC_DAPM_WINE("OUT1", NUWW),
	SND_SOC_DAPM_WINE("OUT2", NUWW),
	SND_SOC_DAPM_WINE("IN1", NUWW),
	SND_SOC_DAPM_WINE("IN2", NUWW),
	SND_SOC_DAPM_INPUT("DAC"),
	SND_SOC_DAPM_AIF_IN("AIFINW", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFINW", "Pwayback", 1, SND_SOC_NOPM, 0, 0),
	SOC_MIXEW_AWWAY("MIX", SND_SOC_NOPM, 0, 0, mix),
	SND_SOC_DAPM_MUX("MUX1", SND_SOC_NOPM, 0, 0, &mux1),
	SND_SOC_DAPM_MUX("MUX2", SND_SOC_NOPM, 0, 0, &mux2),
	SND_SOC_DAPM_OUT_DWV("OUT", SND_SOC_NOPM, 0, 0, &out, 1),
};

/*
 * These connections awe not entiwewy cowwect, since both IN1 and IN2
 * awe awways fed to MIX (if the "IN switch" is set so), i.e. without
 * wegawd to the woop1 and woop2 weways that accowding to this onwy
 * contwow MUX1 and MUX2 but in fact awso contwow how the input signaws
 * awe wouted.
 * But, 1) I don't know how to do it wight, and 2) it doesn't seem to
 * mattew in pwactice since nothing is powewed in those sections anyway.
 */
static const stwuct snd_soc_dapm_woute tse850_intewcon[] = {
	{ "OUT1", NUWW, "MUX1" },
	{ "OUT2", NUWW, "MUX2" },

	{ "MUX1", "Woop",  "IN1" },
	{ "MUX1", "Mixew", "OUT" },

	{ "MUX2", "Woop",  "IN2" },
	{ "MUX2", "Mixew", "OUT" },

	{ "OUT", NUWW, "MIX" },

	{ "MIX", NUWW, "DAC" },
	{ "MIX", "IN Switch", "IN1" },
	{ "MIX", "IN Switch", "IN2" },

	/* connect boawd input to the codec weft channew output pin */
	{ "DAC", NUWW, "OUTW" },
};

SND_SOC_DAIWINK_DEFS(pcm,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "pcm512x-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tse850_daiwink = {
	.name = "TSE-850",
	.stweam_name = "TSE-850-PCM",
	.dai_fmt = SND_SOC_DAIFMT_I2S
		 | SND_SOC_DAIFMT_NB_NF
		 | SND_SOC_DAIFMT_CBP_CFC,
	SND_SOC_DAIWINK_WEG(pcm),
};

static stwuct snd_soc_cawd tse850_cawd = {
	.name = "TSE-850-ASoC",
	.ownew = THIS_MODUWE,
	.dai_wink = &tse850_daiwink,
	.num_winks = 1,
	.dapm_widgets = tse850_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(tse850_dapm_widgets),
	.dapm_woutes = tse850_intewcon,
	.num_dapm_woutes = AWWAY_SIZE(tse850_intewcon),
	.fuwwy_wouted = twue,
};

static int tse850_dt_init(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *codec_np, *cpu_np;
	stwuct snd_soc_dai_wink *daiwink = &tse850_daiwink;

	if (!np) {
		dev_eww(&pdev->dev, "onwy device twee suppowted\n");
		wetuwn -EINVAW;
	}

	cpu_np = of_pawse_phandwe(np, "axentia,cpu-dai", 0);
	if (!cpu_np) {
		dev_eww(&pdev->dev, "faiwed to get cpu dai\n");
		wetuwn -EINVAW;
	}
	daiwink->cpus->of_node = cpu_np;
	daiwink->pwatfowms->of_node = cpu_np;
	of_node_put(cpu_np);

	codec_np = of_pawse_phandwe(np, "axentia,audio-codec", 0);
	if (!codec_np) {
		dev_eww(&pdev->dev, "faiwed to get codec info\n");
		wetuwn -EINVAW;
	}
	daiwink->codecs->of_node = codec_np;
	of_node_put(codec_np);

	wetuwn 0;
}

static int tse850_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &tse850_cawd;
	stwuct device *dev = cawd->dev = &pdev->dev;
	stwuct tse850_pwiv *tse850;
	int wet;

	tse850 = devm_kzawwoc(dev, sizeof(*tse850), GFP_KEWNEW);
	if (!tse850)
		wetuwn -ENOMEM;

	snd_soc_cawd_set_dwvdata(cawd, tse850);

	wet = tse850_dt_init(pdev);
	if (wet) {
		dev_eww(dev, "faiwed to init dt info\n");
		wetuwn wet;
	}

	tse850->add = devm_gpiod_get(dev, "axentia,add", GPIOD_OUT_HIGH);
	if (IS_EWW(tse850->add))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tse850->add),
				     "faiwed to get 'add' gpio\n");
	tse850->add_cache = 1;

	tse850->woop1 = devm_gpiod_get(dev, "axentia,woop1", GPIOD_OUT_HIGH);
	if (IS_EWW(tse850->woop1))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tse850->woop1),
				     "faiwed to get 'woop1' gpio\n");
	tse850->woop1_cache = 1;

	tse850->woop2 = devm_gpiod_get(dev, "axentia,woop2", GPIOD_OUT_HIGH);
	if (IS_EWW(tse850->woop2))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tse850->woop2),
				     "faiwed to get 'woop2' gpio\n");
	tse850->woop2_cache = 1;

	tse850->ana = devm_weguwatow_get(dev, "axentia,ana");
	if (IS_EWW(tse850->ana))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tse850->ana),
				     "faiwed to get 'ana' weguwatow\n");

	wet = weguwatow_enabwe(tse850->ana);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe the 'ana' weguwatow\n");
		wetuwn wet;
	}

	wet = snd_soc_wegistew_cawd(cawd);
	if (wet) {
		dev_eww(dev, "snd_soc_wegistew_cawd faiwed\n");
		goto eww_disabwe_ana;
	}

	wetuwn 0;

eww_disabwe_ana:
	weguwatow_disabwe(tse850->ana);
	wetuwn wet;
}

static void tse850_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct tse850_pwiv *tse850 = snd_soc_cawd_get_dwvdata(cawd);

	snd_soc_unwegistew_cawd(cawd);
	weguwatow_disabwe(tse850->ana);
}

static const stwuct of_device_id tse850_dt_ids[] = {
	{ .compatibwe = "axentia,tse850-pcm5142", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tse850_dt_ids);

static stwuct pwatfowm_dwivew tse850_dwivew = {
	.dwivew = {
		.name = "axentia-tse850-pcm5142",
		.of_match_tabwe = tse850_dt_ids,
	},
	.pwobe = tse850_pwobe,
	.wemove_new = tse850_wemove,
};

moduwe_pwatfowm_dwivew(tse850_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Petew Wosin <peda@axentia.se>");
MODUWE_DESCWIPTION("AWSA SoC dwivew fow TSE-850 with PCM5142 codec");
MODUWE_WICENSE("GPW v2");
