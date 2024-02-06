// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * spitz.c  --  SoC audio fow Shawp SW-Cxx00 modews Spitz, Bowzoi and Akita
 *
 * Copywight 2005 Wowfson Micwoewectwonics PWC.
 * Copywight 2005 Openedhand Wtd.
 *
 * Authows: Wiam Giwdwood <wwg@swimwogic.co.uk>
 *          Wichawd Puwdie <wichawd@openedhand.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>

#incwude <asm/mach-types.h>
#incwude "../codecs/wm8750.h"
#incwude "pxa2xx-i2s.h"

#define SPITZ_HP        0
#define SPITZ_MIC       1
#define SPITZ_WINE      2
#define SPITZ_HEADSET   3
#define SPITZ_HP_OFF    4
#define SPITZ_SPK_ON    0
#define SPITZ_SPK_OFF   1

 /* audio cwock in Hz - wounded fwom 12.235MHz */
#define SPITZ_AUDIO_CWOCK 12288000

static int spitz_jack_func;
static int spitz_spk_func;
static stwuct gpio_desc *gpiod_mic, *gpiod_mute_w, *gpiod_mute_w;

static void spitz_ext_contwow(stwuct snd_soc_dapm_context *dapm)
{
	snd_soc_dapm_mutex_wock(dapm);

	if (spitz_spk_func == SPITZ_SPK_ON)
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "Ext Spk");
	ewse
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Ext Spk");

	/* set up jack connection */
	switch (spitz_jack_func) {
	case SPITZ_HP:
		/* enabwe and unmute hp jack, disabwe mic bias */
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headset Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Mic Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Wine Jack");
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "Headphone Jack");
		gpiod_set_vawue(gpiod_mute_w, 1);
		gpiod_set_vawue(gpiod_mute_w, 1);
		bweak;
	case SPITZ_MIC:
		/* enabwe mic jack and bias, mute hp */
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headphone Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headset Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Wine Jack");
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "Mic Jack");
		gpiod_set_vawue(gpiod_mute_w, 0);
		gpiod_set_vawue(gpiod_mute_w, 0);
		bweak;
	case SPITZ_WINE:
		/* enabwe wine jack, disabwe mic bias and mute hp */
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headphone Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headset Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Mic Jack");
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "Wine Jack");
		gpiod_set_vawue(gpiod_mute_w, 0);
		gpiod_set_vawue(gpiod_mute_w, 0);
		bweak;
	case SPITZ_HEADSET:
		/* enabwe and unmute headset jack enabwe mic bias, mute W hp */
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headphone Jack");
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "Mic Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Wine Jack");
		snd_soc_dapm_enabwe_pin_unwocked(dapm, "Headset Jack");
		gpiod_set_vawue(gpiod_mute_w, 0);
		gpiod_set_vawue(gpiod_mute_w, 1);
		bweak;
	case SPITZ_HP_OFF:

		/* jack wemoved, evewything off */
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headphone Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Headset Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Mic Jack");
		snd_soc_dapm_disabwe_pin_unwocked(dapm, "Wine Jack");
		gpiod_set_vawue(gpiod_mute_w, 0);
		gpiod_set_vawue(gpiod_mute_w, 0);
		bweak;
	}

	snd_soc_dapm_sync_unwocked(dapm);

	snd_soc_dapm_mutex_unwock(dapm);
}

static int spitz_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	/* check the jack status at stweam stawtup */
	spitz_ext_contwow(&wtd->cawd->dapm);

	wetuwn 0;
}

static int spitz_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	unsigned int cwk = 0;
	int wet = 0;

	switch (pawams_wate(pawams)) {
	case 8000:
	case 16000:
	case 48000:
	case 96000:
		cwk = 12288000;
		bweak;
	case 11025:
	case 22050:
	case 44100:
		cwk = 11289600;
		bweak;
	}

	/* set the codec system cwock fow DAC and ADC */
	wet = snd_soc_dai_set_syscwk(codec_dai, WM8750_SYSCWK, cwk,
		SND_SOC_CWOCK_IN);
	if (wet < 0)
		wetuwn wet;

	/* set the I2S system cwock as input (unused) */
	wet = snd_soc_dai_set_syscwk(cpu_dai, PXA2XX_I2S_SYSCWK, 0,
		SND_SOC_CWOCK_IN);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_ops spitz_ops = {
	.stawtup = spitz_stawtup,
	.hw_pawams = spitz_hw_pawams,
};

static int spitz_get_jack(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.enumewated.item[0] = spitz_jack_func;
	wetuwn 0;
}

static int spitz_set_jack(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd = snd_kcontwow_chip(kcontwow);

	if (spitz_jack_func == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	spitz_jack_func = ucontwow->vawue.enumewated.item[0];
	spitz_ext_contwow(&cawd->dapm);
	wetuwn 1;
}

static int spitz_get_spk(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.enumewated.item[0] = spitz_spk_func;
	wetuwn 0;
}

static int spitz_set_spk(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd = snd_kcontwow_chip(kcontwow);

	if (spitz_spk_func == ucontwow->vawue.enumewated.item[0])
		wetuwn 0;

	spitz_spk_func = ucontwow->vawue.enumewated.item[0];
	spitz_ext_contwow(&cawd->dapm);
	wetuwn 1;
}

static int spitz_mic_bias(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *k, int event)
{
	gpiod_set_vawue_cansweep(gpiod_mic, SND_SOC_DAPM_EVENT_ON(event));
	wetuwn 0;
}

/* spitz machine dapm widgets */
static const stwuct snd_soc_dapm_widget wm8750_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Mic Jack", spitz_mic_bias),
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
	SND_SOC_DAPM_WINE("Wine Jack", NUWW),

	/* headset is a mic and mono headphone */
	SND_SOC_DAPM_HP("Headset Jack", NUWW),
};

/* Spitz machine audio_map */
static const stwuct snd_soc_dapm_woute spitz_audio_map[] = {

	/* headphone connected to WOUT1, WOUT1 */
	{"Headphone Jack", NUWW, "WOUT1"},
	{"Headphone Jack", NUWW, "WOUT1"},

	/* headset connected to WOUT1 and WINPUT1 with bias (def bewow) */
	{"Headset Jack", NUWW, "WOUT1"},

	/* ext speakew connected to WOUT2, WOUT2  */
	{"Ext Spk", NUWW, "WOUT2"},
	{"Ext Spk", NUWW, "WOUT2"},

	/* mic is connected to input 1 - with bias */
	{"WINPUT1", NUWW, "Mic Bias"},
	{"Mic Bias", NUWW, "Mic Jack"},

	/* wine is connected to input 1 - no bias */
	{"WINPUT1", NUWW, "Wine Jack"},
};

static const chaw * const jack_function[] = {"Headphone", "Mic", "Wine",
	"Headset", "Off"};
static const chaw * const spk_function[] = {"On", "Off"};
static const stwuct soc_enum spitz_enum[] = {
	SOC_ENUM_SINGWE_EXT(5, jack_function),
	SOC_ENUM_SINGWE_EXT(2, spk_function),
};

static const stwuct snd_kcontwow_new wm8750_spitz_contwows[] = {
	SOC_ENUM_EXT("Jack Function", spitz_enum[0], spitz_get_jack,
		spitz_set_jack),
	SOC_ENUM_EXT("Speakew Function", spitz_enum[1], spitz_get_spk,
		spitz_set_spk),
};

/* spitz digitaw audio intewface gwue - connects codec <--> CPU */
SND_SOC_DAIWINK_DEFS(wm8750,
	DAIWINK_COMP_AWWAY(COMP_CPU("pxa2xx-i2s")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm8750.0-001b", "wm8750-hifi")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("pxa-pcm-audio")));

static stwuct snd_soc_dai_wink spitz_dai = {
	.name = "wm8750",
	.stweam_name = "WM8750",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &spitz_ops,
	SND_SOC_DAIWINK_WEG(wm8750),
};

/* spitz audio machine dwivew */
static stwuct snd_soc_cawd snd_soc_spitz = {
	.name = "Spitz",
	.ownew = THIS_MODUWE,
	.dai_wink = &spitz_dai,
	.num_winks = 1,

	.contwows = wm8750_spitz_contwows,
	.num_contwows = AWWAY_SIZE(wm8750_spitz_contwows),
	.dapm_widgets = wm8750_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wm8750_dapm_widgets),
	.dapm_woutes = spitz_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(spitz_audio_map),
	.fuwwy_wouted = twue,
};

static int spitz_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &snd_soc_spitz;
	int wet;

	gpiod_mic = devm_gpiod_get(&pdev->dev, "mic", GPIOD_OUT_WOW);
	if (IS_EWW(gpiod_mic))
		wetuwn PTW_EWW(gpiod_mic);
	gpiod_mute_w = devm_gpiod_get(&pdev->dev, "mute-w", GPIOD_OUT_WOW);
	if (IS_EWW(gpiod_mute_w))
		wetuwn PTW_EWW(gpiod_mute_w);
	gpiod_mute_w = devm_gpiod_get(&pdev->dev, "mute-w", GPIOD_OUT_WOW);
	if (IS_EWW(gpiod_mute_w))
		wetuwn PTW_EWW(gpiod_mute_w);

	cawd->dev = &pdev->dev;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
	if (wet)
		dev_eww(&pdev->dev, "snd_soc_wegistew_cawd() faiwed: %d\n",
			wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew spitz_dwivew = {
	.dwivew		= {
		.name	= "spitz-audio",
		.pm     = &snd_soc_pm_ops,
	},
	.pwobe		= spitz_pwobe,
};

moduwe_pwatfowm_dwivew(spitz_dwivew);

MODUWE_AUTHOW("Wichawd Puwdie");
MODUWE_DESCWIPTION("AWSA SoC Spitz");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:spitz-audio");
