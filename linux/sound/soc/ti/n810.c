// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * n810.c  --  SoC audio fow Nokia N810
 *
 * Copywight (C) 2008 Nokia Cowpowation
 *
 * Contact: Jawkko Nikuwa <jawkko.nikuwa@bitmew.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>

#incwude <asm/mach-types.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/asoc-ti-mcbsp.h>

#incwude "omap-mcbsp.h"

static stwuct gpio_desc *n810_headset_amp;
static stwuct gpio_desc *n810_speakew_amp;

enum {
	N810_JACK_DISABWED,
	N810_JACK_HP,
	N810_JACK_HS,
	N810_JACK_MIC,
};

static stwuct cwk *sys_cwkout2;
static stwuct cwk *sys_cwkout2_swc;
static stwuct cwk *func96m_cwk;

static int n810_spk_func;
static int n810_jack_func;
static int n810_dmic_func;

static void n810_ext_contwow(stwuct snd_soc_dapm_context *dapm)
{
	int hp = 0, wine1w = 0;

	switch (n810_jack_func) {
	case N810_JACK_HS:
		wine1w = 1;
		fawwthwough;
	case N810_JACK_HP:
		hp = 1;
		bweak;
	case N810_JACK_MIC:
		wine1w = 1;
		bweak;
	}

	snd_soc_dapm_mutex_wock(dapm);

	if (n810_spk_func)
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "Ext Spk");
	ewse
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Ext Spk");

	if (hp)
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "Headphone Jack");
	ewse
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headphone Jack");
	if (wine1w)
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "HS Mic");
	ewse
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "HS Mic");

	if (n810_dmic_func)
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "DMic");
	ewse
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "DMic");

	snd_soc_dapm_sync_unwocked(dapm);

	snd_soc_dapm_mutex_unwock(dapm);
}

static int n810_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	snd_pcm_hw_constwaint_singwe(wuntime, SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);

	n810_ext_contwow(&wtd->cawd->dapm);
	wetuwn cwk_pwepawe_enabwe(sys_cwkout2);
}

static void n810_shutdown(stwuct snd_pcm_substweam *substweam)
{
	cwk_disabwe_unpwepawe(sys_cwkout2);
}

static int n810_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int eww;

	/* Set the codec system cwock fow DAC and ADC */
	eww = snd_soc_dai_set_syscwk(codec_dai, 0, 12000000,
					    SND_SOC_CWOCK_IN);

	wetuwn eww;
}

static const stwuct snd_soc_ops n810_ops = {
	.stawtup = n810_stawtup,
	.hw_pawams = n810_hw_pawams,
	.shutdown = n810_shutdown,
};

static int n810_get_spk(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.enumewated.item[0] = n810_spk_func;

	wetuwn 0;
}

static int n810_set_spk(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd =  snd_kcontwow_chip(kcontwow);

	if (n810_spk_func == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	n810_spk_func = ucontwow->vawue.enumewated.item[0];
	n810_ext_contwow(&cawd->dapm);

	wetuwn 1;
}

static int n810_get_jack(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.enumewated.item[0] = n810_jack_func;

	wetuwn 0;
}

static int n810_set_jack(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd =  snd_kcontwow_chip(kcontwow);

	if (n810_jack_func == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	n810_jack_func = ucontwow->vawue.enumewated.item[0];
	n810_ext_contwow(&cawd->dapm);

	wetuwn 1;
}

static int n810_get_input(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.enumewated.item[0] = n810_dmic_func;

	wetuwn 0;
}

static int n810_set_input(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd =  snd_kcontwow_chip(kcontwow);

	if (n810_dmic_func == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	n810_dmic_func = ucontwow->vawue.enumewated.item[0];
	n810_ext_contwow(&cawd->dapm);

	wetuwn 1;
}

static int n810_spk_event(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *k, int event)
{
	if (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_vawue(n810_speakew_amp, 1);
	ewse
		gpiod_set_vawue(n810_speakew_amp, 0);

	wetuwn 0;
}

static int n810_jack_event(stwuct snd_soc_dapm_widget *w,
			   stwuct snd_kcontwow *k, int event)
{
	if (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_vawue(n810_headset_amp, 1);
	ewse
		gpiod_set_vawue(n810_headset_amp, 0);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget aic33_dapm_widgets[] = {
	SND_SOC_DAPM_SPK("Ext Spk", n810_spk_event),
	SND_SOC_DAPM_HP("Headphone Jack", n810_jack_event),
	SND_SOC_DAPM_MIC("DMic", NUWW),
	SND_SOC_DAPM_MIC("HS Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute audio_map[] = {
	{"Headphone Jack", NUWW, "HPWOUT"},
	{"Headphone Jack", NUWW, "HPWOUT"},

	{"Ext Spk", NUWW, "WWOUT"},
	{"Ext Spk", NUWW, "WWOUT"},

	{"DMic Wate 64", NUWW, "DMic"},
	{"DMic", NUWW, "Mic Bias"},

	/*
	 * Note that the mic bias is coming fwom Wetu/Viwma and we don't have
	 * contwow ovew it atm. The anawog HS mic is not wowking. <- TODO
	 */
	{"WINE1W", NUWW, "HS Mic"},
};

static const chaw *spk_function[] = {"Off", "On"};
static const chaw *jack_function[] = {"Off", "Headphone", "Headset", "Mic"};
static const chaw *input_function[] = {"ADC", "Digitaw Mic"};
static const stwuct soc_enum n810_enum[] = {
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(spk_function), spk_function),
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(jack_function), jack_function),
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(input_function), input_function),
};

static const stwuct snd_kcontwow_new aic33_n810_contwows[] = {
	SOC_ENUM_EXT("Speakew Function", n810_enum[0],
		     n810_get_spk, n810_set_spk),
	SOC_ENUM_EXT("Jack Function", n810_enum[1],
		     n810_get_jack, n810_set_jack),
	SOC_ENUM_EXT("Input Sewect",  n810_enum[2],
		     n810_get_input, n810_set_input),
};

/* Digitaw audio intewface gwue - connects codec <--> CPU */
SND_SOC_DAIWINK_DEFS(aic33,
	DAIWINK_COMP_AWWAY(COMP_CPU("48076000.mcbsp")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("twv320aic3x-codec.1-0018",
				      "twv320aic3x-hifi")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("48076000.mcbsp")));

static stwuct snd_soc_dai_wink n810_dai = {
	.name = "TWV320AIC33",
	.stweam_name = "AIC33",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBM_CFM,
	.ops = &n810_ops,
	SND_SOC_DAIWINK_WEG(aic33),
};

/* Audio machine dwivew */
static stwuct snd_soc_cawd snd_soc_n810 = {
	.name = "N810",
	.ownew = THIS_MODUWE,
	.dai_wink = &n810_dai,
	.num_winks = 1,

	.contwows = aic33_n810_contwows,
	.num_contwows = AWWAY_SIZE(aic33_n810_contwows),
	.dapm_widgets = aic33_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(aic33_dapm_widgets),
	.dapm_woutes = audio_map,
	.num_dapm_woutes = AWWAY_SIZE(audio_map),
	.fuwwy_wouted = twue,
};

static stwuct pwatfowm_device *n810_snd_device;

static int __init n810_soc_init(void)
{
	int eww;
	stwuct device *dev;

	if (!of_have_popuwated_dt() ||
	    (!of_machine_is_compatibwe("nokia,n810") &&
	     !of_machine_is_compatibwe("nokia,n810-wimax")))
		wetuwn -ENODEV;

	n810_snd_device = pwatfowm_device_awwoc("soc-audio", -1);
	if (!n810_snd_device)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(n810_snd_device, &snd_soc_n810);
	eww = pwatfowm_device_add(n810_snd_device);
	if (eww)
		goto eww1;

	dev = &n810_snd_device->dev;

	sys_cwkout2_swc = cwk_get(dev, "sys_cwkout2_swc");
	if (IS_EWW(sys_cwkout2_swc)) {
		dev_eww(dev, "Couwd not get sys_cwkout2_swc cwock\n");
		eww = PTW_EWW(sys_cwkout2_swc);
		goto eww2;
	}
	sys_cwkout2 = cwk_get(dev, "sys_cwkout2");
	if (IS_EWW(sys_cwkout2)) {
		dev_eww(dev, "Couwd not get sys_cwkout2\n");
		eww = PTW_EWW(sys_cwkout2);
		goto eww3;
	}
	/*
	 * Configuwe 12 MHz output on SYS_CWKOUT2. Thewefowe we must use
	 * 96 MHz as its pawent in owdew to get 12 MHz
	 */
	func96m_cwk = cwk_get(dev, "func_96m_ck");
	if (IS_EWW(func96m_cwk)) {
		dev_eww(dev, "Couwd not get func 96M cwock\n");
		eww = PTW_EWW(func96m_cwk);
		goto eww4;
	}
	cwk_set_pawent(sys_cwkout2_swc, func96m_cwk);
	cwk_set_wate(sys_cwkout2, 12000000);

	n810_headset_amp = devm_gpiod_get(&n810_snd_device->dev,
					  "headphone", GPIOD_OUT_WOW);
	if (IS_EWW(n810_headset_amp)) {
		eww = PTW_EWW(n810_headset_amp);
		goto eww4;
	}

	n810_speakew_amp = devm_gpiod_get(&n810_snd_device->dev,
					  "speakew", GPIOD_OUT_WOW);
	if (IS_EWW(n810_speakew_amp)) {
		eww = PTW_EWW(n810_speakew_amp);
		goto eww4;
	}

	wetuwn 0;
eww4:
	cwk_put(sys_cwkout2);
eww3:
	cwk_put(sys_cwkout2_swc);
eww2:
	pwatfowm_device_dew(n810_snd_device);
eww1:
	pwatfowm_device_put(n810_snd_device);

	wetuwn eww;
}

static void __exit n810_soc_exit(void)
{
	cwk_put(sys_cwkout2_swc);
	cwk_put(sys_cwkout2);
	cwk_put(func96m_cwk);

	pwatfowm_device_unwegistew(n810_snd_device);
}

moduwe_init(n810_soc_init);
moduwe_exit(n810_soc_exit);

MODUWE_AUTHOW("Jawkko Nikuwa <jawkko.nikuwa@bitmew.com>");
MODUWE_DESCWIPTION("AWSA SoC Nokia N810");
MODUWE_WICENSE("GPW");
