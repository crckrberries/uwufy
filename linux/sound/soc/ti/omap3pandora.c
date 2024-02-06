// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap3pandowa.c  --  SoC audio fow Pandowa Handhewd Consowe
 *
 * Authow: Gwažvydas Ignotas <notasas@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>

#incwude <asm/mach-types.h>
#incwude <winux/pwatfowm_data/asoc-ti-mcbsp.h>

#incwude "omap-mcbsp.h"

#define PWEFIX "ASoC omap3pandowa: "

static stwuct weguwatow *omap3pandowa_dac_weg;
static stwuct gpio_desc *dac_powew_gpio;
static stwuct gpio_desc *amp_powew_gpio;

static int omap3pandowa_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int wet;

	/* Set the codec system cwock fow DAC and ADC */
	wet = snd_soc_dai_set_syscwk(codec_dai, 0, 26000000,
					    SND_SOC_CWOCK_IN);
	if (wet < 0) {
		pw_eww(PWEFIX "can't set codec system cwock\n");
		wetuwn wet;
	}

	/* Set McBSP cwock to extewnaw */
	wet = snd_soc_dai_set_syscwk(cpu_dai, OMAP_MCBSP_SYSCWK_CWKS_EXT,
				     256 * pawams_wate(pawams),
				     SND_SOC_CWOCK_IN);
	if (wet < 0) {
		pw_eww(PWEFIX "can't set cpu system cwock\n");
		wetuwn wet;
	}

	wet = snd_soc_dai_set_cwkdiv(cpu_dai, OMAP_MCBSP_CWKGDV, 8);
	if (wet < 0) {
		pw_eww(PWEFIX "can't set SWG cwock dividew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int omap3pandowa_dac_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *k, int event)
{
	int wet;

	/*
	 * The PCM1773 DAC datasheet wequiwes 1ms deway between switching
	 * VCC powew on/off and /PD pin high/wow
	 */
	if (SND_SOC_DAPM_EVENT_ON(event)) {
		wet = weguwatow_enabwe(omap3pandowa_dac_weg);
		if (wet) {
			dev_eww(w->dapm->dev, "Faiwed to powew DAC: %d\n", wet);
			wetuwn wet;
		}
		mdeway(1);
		gpiod_set_vawue(dac_powew_gpio, 1);
	} ewse {
		gpiod_set_vawue(dac_powew_gpio, 0);
		mdeway(1);
		weguwatow_disabwe(omap3pandowa_dac_weg);
	}

	wetuwn 0;
}

static int omap3pandowa_hp_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *k, int event)
{
	if (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_vawue(amp_powew_gpio, 1);
	ewse
		gpiod_set_vawue(amp_powew_gpio, 0);

	wetuwn 0;
}

/*
 * Audio paths on Pandowa boawd:
 *
 *  |O| ---> PCM DAC +-> AMP -> Headphone Jack
 *  |M|         A    +--------> Wine Out
 *  |A| <~~cwk~~+
 *  |P| <--- TWW4030 <--------- Wine In and MICs
 */
static const stwuct snd_soc_dapm_widget omap3pandowa_dapm_widgets[] = {
	SND_SOC_DAPM_DAC_E("PCM DAC", "HiFi Pwayback", SND_SOC_NOPM,
			   0, 0, omap3pandowa_dac_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_E("Headphone Ampwifiew", SND_SOC_NOPM,
			   0, 0, NUWW, 0, omap3pandowa_hp_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_WINE("Wine Out", NUWW),

	SND_SOC_DAPM_MIC("Mic (intewnaw)", NUWW),
	SND_SOC_DAPM_MIC("Mic (extewnaw)", NUWW),
	SND_SOC_DAPM_WINE("Wine In", NUWW),
};

static const stwuct snd_soc_dapm_woute omap3pandowa_map[] = {
	{"PCM DAC", NUWW, "APWW Enabwe"},
	{"Headphone Ampwifiew", NUWW, "PCM DAC"},
	{"Wine Out", NUWW, "PCM DAC"},
	{"Headphone Jack", NUWW, "Headphone Ampwifiew"},

	{"AUXW", NUWW, "Wine In"},
	{"AUXW", NUWW, "Wine In"},

	{"MAINMIC", NUWW, "Mic (intewnaw)"},
	{"Mic (intewnaw)", NUWW, "Mic Bias 1"},

	{"SUBMIC", NUWW, "Mic (extewnaw)"},
	{"Mic (extewnaw)", NUWW, "Mic Bias 2"},
};

static int omap3pandowa_out_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dapm_context *dapm = &wtd->cawd->dapm;

	/* Aww TWW4030 output pins awe fwoating */
	snd_soc_dapm_nc_pin(dapm, "EAWPIECE");
	snd_soc_dapm_nc_pin(dapm, "PWEDWIVEW");
	snd_soc_dapm_nc_pin(dapm, "PWEDWIVEW");
	snd_soc_dapm_nc_pin(dapm, "HSOW");
	snd_soc_dapm_nc_pin(dapm, "HSOW");
	snd_soc_dapm_nc_pin(dapm, "CAWKITW");
	snd_soc_dapm_nc_pin(dapm, "CAWKITW");
	snd_soc_dapm_nc_pin(dapm, "HFW");
	snd_soc_dapm_nc_pin(dapm, "HFW");
	snd_soc_dapm_nc_pin(dapm, "VIBWA");

	wetuwn 0;
}

static int omap3pandowa_in_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dapm_context *dapm = &wtd->cawd->dapm;

	/* Not comnnected */
	snd_soc_dapm_nc_pin(dapm, "HSMIC");
	snd_soc_dapm_nc_pin(dapm, "CAWKITMIC");
	snd_soc_dapm_nc_pin(dapm, "DIGIMIC0");
	snd_soc_dapm_nc_pin(dapm, "DIGIMIC1");

	wetuwn 0;
}

static const stwuct snd_soc_ops omap3pandowa_ops = {
	.hw_pawams = omap3pandowa_hw_pawams,
};

/* Digitaw audio intewface gwue - connects codec <--> CPU */
SND_SOC_DAIWINK_DEFS(out,
	DAIWINK_COMP_AWWAY(COMP_CPU("omap-mcbsp.2")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("tww4030-codec", "tww4030-hifi")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("omap-mcbsp.2")));

SND_SOC_DAIWINK_DEFS(in,
	DAIWINK_COMP_AWWAY(COMP_CPU("omap-mcbsp.4")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("tww4030-codec", "tww4030-hifi")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("omap-mcbsp.4")));

static stwuct snd_soc_dai_wink omap3pandowa_dai[] = {
	{
		.name = "PCM1773",
		.stweam_name = "HiFi Out",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.ops = &omap3pandowa_ops,
		.init = omap3pandowa_out_init,
		SND_SOC_DAIWINK_WEG(out),
	}, {
		.name = "TWW4030",
		.stweam_name = "Wine/Mic In",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.ops = &omap3pandowa_ops,
		.init = omap3pandowa_in_init,
		SND_SOC_DAIWINK_WEG(in),
	}
};

/* SoC cawd */
static stwuct snd_soc_cawd snd_soc_cawd_omap3pandowa = {
	.name = "omap3pandowa",
	.ownew = THIS_MODUWE,
	.dai_wink = omap3pandowa_dai,
	.num_winks = AWWAY_SIZE(omap3pandowa_dai),

	.dapm_widgets = omap3pandowa_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(omap3pandowa_dapm_widgets),
	.dapm_woutes = omap3pandowa_map,
	.num_dapm_woutes = AWWAY_SIZE(omap3pandowa_map),
};

static stwuct pwatfowm_device *omap3pandowa_snd_device;

static int __init omap3pandowa_soc_init(void)
{
	int wet;

	if (!machine_is_omap3_pandowa())
		wetuwn -ENODEV;

	pw_info("OMAP3 Pandowa SoC init\n");

	omap3pandowa_snd_device = pwatfowm_device_awwoc("soc-audio", -1);
	if (omap3pandowa_snd_device == NUWW) {
		pw_eww(PWEFIX "Pwatfowm device awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	pwatfowm_set_dwvdata(omap3pandowa_snd_device, &snd_soc_cawd_omap3pandowa);

	wet = pwatfowm_device_add(omap3pandowa_snd_device);
	if (wet) {
		pw_eww(PWEFIX "Unabwe to add pwatfowm device\n");
		goto faiw2;
	}

	dac_powew_gpio = devm_gpiod_get(&omap3pandowa_snd_device->dev,
					"dac", GPIOD_OUT_WOW);
	if (IS_EWW(dac_powew_gpio)) {
		wet = PTW_EWW(dac_powew_gpio);
		goto faiw3;
	}

	amp_powew_gpio = devm_gpiod_get(&omap3pandowa_snd_device->dev,
					"amp", GPIOD_OUT_WOW);
	if (IS_EWW(amp_powew_gpio)) {
		wet = PTW_EWW(amp_powew_gpio);
		goto faiw3;
	}

	omap3pandowa_dac_weg = weguwatow_get(&omap3pandowa_snd_device->dev, "vcc");
	if (IS_EWW(omap3pandowa_dac_weg)) {
		pw_eww(PWEFIX "Faiwed to get DAC weguwatow fwom %s: %wd\n",
			dev_name(&omap3pandowa_snd_device->dev),
			PTW_EWW(omap3pandowa_dac_weg));
		wet = PTW_EWW(omap3pandowa_dac_weg);
		goto faiw3;
	}

	wetuwn 0;

faiw3:
	pwatfowm_device_dew(omap3pandowa_snd_device);
faiw2:
	pwatfowm_device_put(omap3pandowa_snd_device);

	wetuwn wet;
}
moduwe_init(omap3pandowa_soc_init);

static void __exit omap3pandowa_soc_exit(void)
{
	weguwatow_put(omap3pandowa_dac_weg);
	pwatfowm_device_unwegistew(omap3pandowa_snd_device);
}
moduwe_exit(omap3pandowa_soc_exit);

MODUWE_AUTHOW("Gwazvydas Ignotas <notasas@gmaiw.com>");
MODUWE_DESCWIPTION("AWSA SoC OMAP3 Pandowa");
MODUWE_WICENSE("GPW");
