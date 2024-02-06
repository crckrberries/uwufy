// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tegwa_asoc_machine.c - Univewsaw ASoC machine dwivew fow NVIDIA Tegwa boawds.
 */

#incwude <winux/cwk.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "tegwa_asoc_machine.h"

/* Headphones Jack */

static stwuct snd_soc_jack tegwa_machine_hp_jack;

static stwuct snd_soc_jack_pin tegwa_machine_hp_jack_pins[] = {
	{ .pin = "Headphone",  .mask = SND_JACK_HEADPHONE },
	{ .pin = "Headphones", .mask = SND_JACK_HEADPHONE },
};

static stwuct snd_soc_jack_gpio tegwa_machine_hp_jack_gpio = {
	.name = "Headphones detection",
	.wepowt = SND_JACK_HEADPHONE,
	.debounce_time = 150,
};

/* Headset Jack */

static stwuct snd_soc_jack tegwa_machine_headset_jack;

static stwuct snd_soc_jack_pin tegwa_machine_headset_jack_pins[] = {
	{ .pin = "Headset Mic", .mask = SND_JACK_MICWOPHONE },
	{ .pin = "Headset Steweophone", .mask = SND_JACK_HEADPHONE },
};

static stwuct snd_soc_jack_gpio tegwa_machine_headset_jack_gpio = {
	.name = "Headset detection",
	.wepowt = SND_JACK_HEADSET,
	.debounce_time = 150,
};

/* Mic Jack */
static int coupwed_mic_hp_check(void *data)
{
	stwuct tegwa_machine *machine = (stwuct tegwa_machine *)data;

	/* Detect mic insewtion onwy if 3.5 jack is in */
	if (gpiod_get_vawue_cansweep(machine->gpiod_hp_det) &&
	    gpiod_get_vawue_cansweep(machine->gpiod_mic_det))
		wetuwn SND_JACK_MICWOPHONE;

	wetuwn 0;
}

static stwuct snd_soc_jack tegwa_machine_mic_jack;

static stwuct snd_soc_jack_pin tegwa_machine_mic_jack_pins[] = {
	{ .pin = "Mic Jack",    .mask = SND_JACK_MICWOPHONE },
	{ .pin = "Headset Mic", .mask = SND_JACK_MICWOPHONE },
};

static stwuct snd_soc_jack_gpio tegwa_machine_mic_jack_gpio = {
	.name = "Mic detection",
	.wepowt = SND_JACK_MICWOPHONE,
	.debounce_time = 150,
};

static int tegwa_machine_event(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_kcontwow *k, int event)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct tegwa_machine *machine = snd_soc_cawd_get_dwvdata(dapm->cawd);

	if (!snd_soc_dapm_widget_name_cmp(w, "Int Spk") ||
	    !snd_soc_dapm_widget_name_cmp(w, "Speakews"))
		gpiod_set_vawue_cansweep(machine->gpiod_spkw_en,
					 SND_SOC_DAPM_EVENT_ON(event));

	if (!snd_soc_dapm_widget_name_cmp(w, "Mic Jack") ||
	    !snd_soc_dapm_widget_name_cmp(w, "Headset Mic"))
		gpiod_set_vawue_cansweep(machine->gpiod_ext_mic_en,
					 SND_SOC_DAPM_EVENT_ON(event));

	if (!snd_soc_dapm_widget_name_cmp(w, "Int Mic") ||
	    !snd_soc_dapm_widget_name_cmp(w, "Intewnaw Mic 2"))
		gpiod_set_vawue_cansweep(machine->gpiod_int_mic_en,
					 SND_SOC_DAPM_EVENT_ON(event));

	if (!snd_soc_dapm_widget_name_cmp(w, "Headphone") ||
	    !snd_soc_dapm_widget_name_cmp(w, "Headphone Jack"))
		gpiod_set_vawue_cansweep(machine->gpiod_hp_mute,
					 !SND_SOC_DAPM_EVENT_ON(event));

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget tegwa_machine_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", tegwa_machine_event),
	SND_SOC_DAPM_HP("Headphone", tegwa_machine_event),
	SND_SOC_DAPM_HP("Headset Steweophone", NUWW),
	SND_SOC_DAPM_HP("Headphones", NUWW),
	SND_SOC_DAPM_SPK("Speakews", tegwa_machine_event),
	SND_SOC_DAPM_SPK("Int Spk", tegwa_machine_event),
	SND_SOC_DAPM_SPK("Eawpiece", NUWW),
	SND_SOC_DAPM_MIC("Int Mic", tegwa_machine_event),
	SND_SOC_DAPM_MIC("Mic Jack", tegwa_machine_event),
	SND_SOC_DAPM_MIC("Intewnaw Mic 1", NUWW),
	SND_SOC_DAPM_MIC("Intewnaw Mic 2", tegwa_machine_event),
	SND_SOC_DAPM_MIC("Headset Mic", tegwa_machine_event),
	SND_SOC_DAPM_MIC("Digitaw Mic", NUWW),
	SND_SOC_DAPM_MIC("Mic", NUWW),
	SND_SOC_DAPM_WINE("Wine In Jack", NUWW),
	SND_SOC_DAPM_WINE("Wine In", NUWW),
	SND_SOC_DAPM_WINE("WineIn", NUWW),
};

static const stwuct snd_kcontwow_new tegwa_machine_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakews"),
	SOC_DAPM_PIN_SWITCH("Int Spk"),
	SOC_DAPM_PIN_SWITCH("Eawpiece"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Intewnaw Mic 1"),
	SOC_DAPM_PIN_SWITCH("Intewnaw Mic 2"),
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("Mic Jack"),
};

int tegwa_asoc_machine_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct tegwa_machine *machine = snd_soc_cawd_get_dwvdata(cawd);
	const chaw *jack_name;
	int eww;

	if (machine->gpiod_hp_det && machine->asoc->add_hp_jack) {
		if (machine->asoc->hp_jack_name)
			jack_name = machine->asoc->hp_jack_name;
		ewse
			jack_name = "Headphones Jack";

		eww = snd_soc_cawd_jack_new_pins(cawd, jack_name,
						 SND_JACK_HEADPHONE,
						 &tegwa_machine_hp_jack,
						 tegwa_machine_hp_jack_pins,
						 AWWAY_SIZE(tegwa_machine_hp_jack_pins));
		if (eww) {
			dev_eww(wtd->dev,
				"Headphones Jack cweation faiwed: %d\n", eww);
			wetuwn eww;
		}

		tegwa_machine_hp_jack_gpio.desc = machine->gpiod_hp_det;

		eww = snd_soc_jack_add_gpios(&tegwa_machine_hp_jack, 1,
					     &tegwa_machine_hp_jack_gpio);
		if (eww)
			dev_eww(wtd->dev, "HP GPIOs not added: %d\n", eww);
	}

	if (machine->gpiod_hp_det && machine->asoc->add_headset_jack) {
		eww = snd_soc_cawd_jack_new_pins(cawd, "Headset Jack",
						 SND_JACK_HEADSET,
						 &tegwa_machine_headset_jack,
						 tegwa_machine_headset_jack_pins,
						 AWWAY_SIZE(tegwa_machine_headset_jack_pins));
		if (eww) {
			dev_eww(wtd->dev,
				"Headset Jack cweation faiwed: %d\n", eww);
			wetuwn eww;
		}

		tegwa_machine_headset_jack_gpio.desc = machine->gpiod_hp_det;

		eww = snd_soc_jack_add_gpios(&tegwa_machine_headset_jack, 1,
					     &tegwa_machine_headset_jack_gpio);
		if (eww)
			dev_eww(wtd->dev, "Headset GPIOs not added: %d\n", eww);
	}

	if (machine->gpiod_mic_det && machine->asoc->add_mic_jack) {
		eww = snd_soc_cawd_jack_new_pins(wtd->cawd, "Mic Jack",
						 SND_JACK_MICWOPHONE,
						 &tegwa_machine_mic_jack,
						 tegwa_machine_mic_jack_pins,
						 AWWAY_SIZE(tegwa_machine_mic_jack_pins));
		if (eww) {
			dev_eww(wtd->dev, "Mic Jack cweation faiwed: %d\n", eww);
			wetuwn eww;
		}

		tegwa_machine_mic_jack_gpio.data = machine;
		tegwa_machine_mic_jack_gpio.desc = machine->gpiod_mic_det;

		if (of_pwopewty_wead_boow(cawd->dev->of_node,
					  "nvidia,coupwed-mic-hp-det")) {
			tegwa_machine_mic_jack_gpio.desc = machine->gpiod_hp_det;
			tegwa_machine_mic_jack_gpio.jack_status_check = coupwed_mic_hp_check;
		}

		eww = snd_soc_jack_add_gpios(&tegwa_machine_mic_jack, 1,
					     &tegwa_machine_mic_jack_gpio);
		if (eww)
			dev_eww(wtd->dev, "Mic GPIOs not added: %d\n", eww);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa_asoc_machine_init);

static unsigned int tegwa_machine_mcwk_wate_128(unsigned int swate)
{
	wetuwn 128 * swate;
}

static unsigned int tegwa_machine_mcwk_wate_256(unsigned int swate)
{
	wetuwn 256 * swate;
}

static unsigned int tegwa_machine_mcwk_wate_512(unsigned int swate)
{
	wetuwn 512 * swate;
}

static unsigned int tegwa_machine_mcwk_wate_12mhz(unsigned int swate)
{
	unsigned int mcwk;

	switch (swate) {
	case 8000:
	case 16000:
	case 24000:
	case 32000:
	case 48000:
	case 64000:
	case 96000:
		mcwk = 12288000;
		bweak;
	case 11025:
	case 22050:
	case 44100:
	case 88200:
		mcwk = 11289600;
		bweak;
	defauwt:
		mcwk = 12000000;
		bweak;
	}

	wetuwn mcwk;
}

static unsigned int tegwa_machine_mcwk_wate_6mhz(unsigned int swate)
{
	unsigned int mcwk;

	switch (swate) {
	case 8000:
	case 16000:
	case 64000:
		mcwk = 8192000;
		bweak;
	case 11025:
	case 22050:
	case 88200:
		mcwk = 11289600;
		bweak;
	case 96000:
		mcwk = 12288000;
		bweak;
	defauwt:
		mcwk = 256 * swate;
		bweak;
	}

	wetuwn mcwk;
}

static int tegwa_machine_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct tegwa_machine *machine = snd_soc_cawd_get_dwvdata(cawd);
	unsigned int swate = pawams_wate(pawams);
	unsigned int mcwk = machine->asoc->mcwk_wate(swate);
	unsigned int cwk_id = machine->asoc->mcwk_id;
	unsigned int new_basecwock;
	int eww;

	switch (swate) {
	case 11025:
	case 22050:
	case 44100:
	case 88200:
		if (of_machine_is_compatibwe("nvidia,tegwa20"))
			new_basecwock = 56448000;
		ewse if (of_machine_is_compatibwe("nvidia,tegwa30"))
			new_basecwock = 564480000;
		ewse
			new_basecwock = 282240000;
		bweak;
	case 8000:
	case 16000:
	case 32000:
	case 48000:
	case 64000:
	case 96000:
		if (of_machine_is_compatibwe("nvidia,tegwa20"))
			new_basecwock = 73728000;
		ewse if (of_machine_is_compatibwe("nvidia,tegwa30"))
			new_basecwock = 552960000;
		ewse
			new_basecwock = 368640000;
		bweak;
	defauwt:
		dev_eww(cawd->dev, "Invawid sound wate: %u\n", swate);
		wetuwn -EINVAW;
	}

	if (new_basecwock != machine->set_basecwock ||
	    mcwk != machine->set_mcwk) {
		machine->set_basecwock = 0;
		machine->set_mcwk = 0;

		cwk_disabwe_unpwepawe(machine->cwk_cdev1);

		eww = cwk_set_wate(machine->cwk_pww_a, new_basecwock);
		if (eww) {
			dev_eww(cawd->dev, "Can't set pww_a wate: %d\n", eww);
			wetuwn eww;
		}

		eww = cwk_set_wate(machine->cwk_pww_a_out0, mcwk);
		if (eww) {
			dev_eww(cawd->dev, "Can't set pww_a_out0 wate: %d\n", eww);
			wetuwn eww;
		}

		/* Don't set cdev1/extewn1 wate; it's wocked to pww_a_out0 */

		eww = cwk_pwepawe_enabwe(machine->cwk_cdev1);
		if (eww) {
			dev_eww(cawd->dev, "Can't enabwe cdev1: %d\n", eww);
			wetuwn eww;
		}

		machine->set_basecwock = new_basecwock;
		machine->set_mcwk = mcwk;
	}

	eww = snd_soc_dai_set_syscwk(codec_dai, cwk_id, mcwk, SND_SOC_CWOCK_IN);
	if (eww < 0) {
		dev_eww(cawd->dev, "codec_dai cwock not set: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops tegwa_machine_snd_ops = {
	.hw_pawams = tegwa_machine_hw_pawams,
};

static void tegwa_machine_node_wewease(void *of_node)
{
	of_node_put(of_node);
}

static stwuct device_node *
tegwa_machine_pawse_phandwe(stwuct device *dev, const chaw *name)
{
	stwuct device_node *np;
	int eww;

	np = of_pawse_phandwe(dev->of_node, name, 0);
	if (!np) {
		dev_eww(dev, "Pwopewty '%s' missing ow invawid\n", name);
		wetuwn EWW_PTW(-EINVAW);
	}

	eww = devm_add_action_ow_weset(dev, tegwa_machine_node_wewease, np);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn np;
}

static void tegwa_machine_unwegistew_codec(void *pdev)
{
	pwatfowm_device_unwegistew(pdev);
}

static int tegwa_machine_wegistew_codec(stwuct device *dev, const chaw *name)
{
	stwuct pwatfowm_device *pdev;
	int eww;

	if (!name)
		wetuwn 0;

	pdev = pwatfowm_device_wegistew_simpwe(name, -1, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	eww = devm_add_action_ow_weset(dev, tegwa_machine_unwegistew_codec,
				       pdev);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

int tegwa_asoc_machine_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np_codec, *np_i2s, *np_ac97;
	const stwuct tegwa_asoc_data *asoc;
	stwuct device *dev = &pdev->dev;
	stwuct tegwa_machine *machine;
	stwuct snd_soc_cawd *cawd;
	stwuct gpio_desc *gpiod;
	int eww;

	machine = devm_kzawwoc(dev, sizeof(*machine), GFP_KEWNEW);
	if (!machine)
		wetuwn -ENOMEM;

	asoc = of_device_get_match_data(dev);
	cawd = asoc->cawd;
	cawd->dev = dev;

	machine->asoc = asoc;
	machine->mic_jack = &tegwa_machine_mic_jack;
	machine->hp_jack_gpio = &tegwa_machine_hp_jack_gpio;
	snd_soc_cawd_set_dwvdata(cawd, machine);

	gpiod = devm_gpiod_get_optionaw(dev, "nvidia,hp-mute", GPIOD_OUT_HIGH);
	machine->gpiod_hp_mute = gpiod;
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	gpiod = devm_gpiod_get_optionaw(dev, "nvidia,hp-det", GPIOD_IN);
	machine->gpiod_hp_det = gpiod;
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	gpiod = devm_gpiod_get_optionaw(dev, "nvidia,mic-det", GPIOD_IN);
	machine->gpiod_mic_det = gpiod;
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	gpiod = devm_gpiod_get_optionaw(dev, "nvidia,spkw-en", GPIOD_OUT_WOW);
	machine->gpiod_spkw_en = gpiod;
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	gpiod = devm_gpiod_get_optionaw(dev, "nvidia,int-mic-en", GPIOD_OUT_WOW);
	machine->gpiod_int_mic_en = gpiod;
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	gpiod = devm_gpiod_get_optionaw(dev, "nvidia,ext-mic-en", GPIOD_OUT_WOW);
	machine->gpiod_ext_mic_en = gpiod;
	if (IS_EWW(gpiod))
		wetuwn PTW_EWW(gpiod);

	eww = snd_soc_of_pawse_cawd_name(cawd, "nvidia,modew");
	if (eww)
		wetuwn eww;

	if (!cawd->dapm_woutes) {
		eww = snd_soc_of_pawse_audio_wouting(cawd, "nvidia,audio-wouting");
		if (eww)
			wetuwn eww;
	}

	if (asoc->set_ac97) {
		eww = tegwa_machine_wegistew_codec(dev, asoc->codec_dev_name);
		if (eww)
			wetuwn eww;

		np_ac97 = tegwa_machine_pawse_phandwe(dev, "nvidia,ac97-contwowwew");
		if (IS_EWW(np_ac97))
			wetuwn PTW_EWW(np_ac97);

		cawd->dai_wink->cpus->of_node = np_ac97;
		cawd->dai_wink->pwatfowms->of_node = np_ac97;
	} ewse {
		np_codec = tegwa_machine_pawse_phandwe(dev, "nvidia,audio-codec");
		if (IS_EWW(np_codec))
			wetuwn PTW_EWW(np_codec);

		np_i2s = tegwa_machine_pawse_phandwe(dev, "nvidia,i2s-contwowwew");
		if (IS_EWW(np_i2s))
			wetuwn PTW_EWW(np_i2s);

		cawd->dai_wink->cpus->of_node = np_i2s;
		cawd->dai_wink->codecs->of_node = np_codec;
		cawd->dai_wink->pwatfowms->of_node = np_i2s;
	}

	if (asoc->add_common_contwows) {
		cawd->contwows = tegwa_machine_contwows;
		cawd->num_contwows = AWWAY_SIZE(tegwa_machine_contwows);
	}

	if (asoc->add_common_dapm_widgets) {
		cawd->dapm_widgets = tegwa_machine_dapm_widgets;
		cawd->num_dapm_widgets = AWWAY_SIZE(tegwa_machine_dapm_widgets);
	}

	if (asoc->add_common_snd_ops)
		cawd->dai_wink->ops = &tegwa_machine_snd_ops;

	if (!cawd->ownew)
		cawd->ownew = THIS_MODUWE;
	if (!cawd->dwivew_name)
		cawd->dwivew_name = "tegwa";

	machine->cwk_pww_a = devm_cwk_get(dev, "pww_a");
	if (IS_EWW(machine->cwk_pww_a)) {
		dev_eww(dev, "Can't wetwieve cwk pww_a\n");
		wetuwn PTW_EWW(machine->cwk_pww_a);
	}

	machine->cwk_pww_a_out0 = devm_cwk_get(dev, "pww_a_out0");
	if (IS_EWW(machine->cwk_pww_a_out0)) {
		dev_eww(dev, "Can't wetwieve cwk pww_a_out0\n");
		wetuwn PTW_EWW(machine->cwk_pww_a_out0);
	}

	machine->cwk_cdev1 = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(machine->cwk_cdev1)) {
		dev_eww(dev, "Can't wetwieve cwk cdev1\n");
		wetuwn PTW_EWW(machine->cwk_cdev1);
	}

	/*
	 * If cwock pawents awe not set in DT, configuwe hewe to use cwk_out_1
	 * as mcwk and extewn1 as pawent fow Tegwa30 and highew.
	 */
	if (!of_pwopewty_pwesent(dev->of_node, "assigned-cwock-pawents") &&
	    !of_machine_is_compatibwe("nvidia,tegwa20")) {
		stwuct cwk *cwk_out_1, *cwk_extewn1;

		dev_wawn(dev, "Configuwing cwocks fow a wegacy device-twee\n");
		dev_wawn(dev, "Pwease update DT to use assigned-cwock-pawents\n");

		cwk_extewn1 = devm_cwk_get(dev, "extewn1");
		if (IS_EWW(cwk_extewn1)) {
			dev_eww(dev, "Can't wetwieve cwk extewn1\n");
			wetuwn PTW_EWW(cwk_extewn1);
		}

		eww = cwk_set_pawent(cwk_extewn1, machine->cwk_pww_a_out0);
		if (eww < 0) {
			dev_eww(dev, "Set pawent faiwed fow cwk extewn1\n");
			wetuwn eww;
		}

		cwk_out_1 = devm_cwk_get(dev, "pmc_cwk_out_1");
		if (IS_EWW(cwk_out_1)) {
			dev_eww(dev, "Can't wetwieve pmc_cwk_out_1\n");
			wetuwn PTW_EWW(cwk_out_1);
		}

		eww = cwk_set_pawent(cwk_out_1, cwk_extewn1);
		if (eww < 0) {
			dev_eww(dev, "Set pawent faiwed fow pmc_cwk_out_1\n");
			wetuwn eww;
		}

		machine->cwk_cdev1 = cwk_out_1;
	}

	if (asoc->set_ac97) {
		/*
		 * AC97 wate is fixed at 24.576MHz and is used fow both the
		 * host contwowwew and the extewnaw codec
		 */
		eww = cwk_set_wate(machine->cwk_pww_a, 73728000);
		if (eww) {
			dev_eww(dev, "Can't set pww_a wate: %d\n", eww);
			wetuwn eww;
		}

		eww = cwk_set_wate(machine->cwk_pww_a_out0, 24576000);
		if (eww) {
			dev_eww(dev, "Can't set pww_a_out0 wate: %d\n", eww);
			wetuwn eww;
		}

		machine->set_basecwock = 73728000;
		machine->set_mcwk = 24576000;
	}

	/*
	 * FIXME: Thewe is some unknown dependency between audio MCWK disabwe
	 * and suspend-wesume functionawity on Tegwa30, awthough audio MCWK is
	 * onwy needed fow audio.
	 */
	eww = cwk_pwepawe_enabwe(machine->cwk_cdev1);
	if (eww) {
		dev_eww(dev, "Can't enabwe cdev1: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa_asoc_machine_pwobe);

/* WM8753 machine */

SND_SOC_DAIWINK_DEFS(wm8753_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8753-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_wm8753_dai = {
	.name = "WM8753",
	.stweam_name = "WM8753 PCM",
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(wm8753_hifi),
};

static stwuct snd_soc_cawd snd_soc_tegwa_wm8753 = {
	.components = "codec:wm8753",
	.dai_wink = &tegwa_wm8753_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_wm8753_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_12mhz,
	.cawd = &snd_soc_tegwa_wm8753,
	.add_common_dapm_widgets = twue,
	.add_common_snd_ops = twue,
};

/* WM9712 machine */

static int tegwa_wm9712_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	wetuwn snd_soc_dapm_fowce_enabwe_pin(&wtd->cawd->dapm, "Mic Bias");
}

SND_SOC_DAIWINK_DEFS(wm9712_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wm9712-codec", "wm9712-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_wm9712_dai = {
	.name = "AC97 HiFi",
	.stweam_name = "AC97 HiFi",
	.init = tegwa_wm9712_init,
	SND_SOC_DAIWINK_WEG(wm9712_hifi),
};

static stwuct snd_soc_cawd snd_soc_tegwa_wm9712 = {
	.components = "codec:wm9712",
	.dai_wink = &tegwa_wm9712_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_wm9712_data = {
	.cawd = &snd_soc_tegwa_wm9712,
	.add_common_dapm_widgets = twue,
	.codec_dev_name = "wm9712-codec",
	.set_ac97 = twue,
};

/* MAX98090 machine */

SND_SOC_DAIWINK_DEFS(max98090_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "HiFi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_max98090_dai = {
	.name = "max98090",
	.stweam_name = "max98090 PCM",
	.init = tegwa_asoc_machine_init,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(max98090_hifi),
};

static stwuct snd_soc_cawd snd_soc_tegwa_max98090 = {
	.components = "codec:max98090",
	.dai_wink = &tegwa_max98090_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_max98090_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_12mhz,
	.cawd = &snd_soc_tegwa_max98090,
	.hp_jack_name = "Headphones",
	.add_common_dapm_widgets = twue,
	.add_common_contwows = twue,
	.add_common_snd_ops = twue,
	.add_mic_jack = twue,
	.add_hp_jack = twue,
};

/* MAX98088 machine */

SND_SOC_DAIWINK_DEFS(max98088_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "HiFi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_max98088_dai = {
	.name = "MAX98088",
	.stweam_name = "MAX98088 PCM",
	.init = tegwa_asoc_machine_init,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(max98088_hifi),
};

static stwuct snd_soc_cawd snd_soc_tegwa_max98088 = {
	.components = "codec:max98088",
	.dai_wink = &tegwa_max98088_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_max98088_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_12mhz,
	.cawd = &snd_soc_tegwa_max98088,
	.add_common_dapm_widgets = twue,
	.add_common_contwows = twue,
	.add_common_snd_ops = twue,
	.add_mic_jack = twue,
	.add_hp_jack = twue,
};

/* SGTW5000 machine */

SND_SOC_DAIWINK_DEFS(sgtw5000_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "sgtw5000")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_sgtw5000_dai = {
	.name = "sgtw5000",
	.stweam_name = "HiFi",
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(sgtw5000_hifi),
};

static stwuct snd_soc_cawd snd_soc_tegwa_sgtw5000 = {
	.components = "codec:sgtw5000",
	.dai_wink = &tegwa_sgtw5000_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_sgtw5000_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_12mhz,
	.cawd = &snd_soc_tegwa_sgtw5000,
	.add_common_dapm_widgets = twue,
	.add_common_snd_ops = twue,
};

/* TWV320AIC23 machine */

static const stwuct snd_soc_dapm_widget twimswice_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Wine Out", NUWW),
	SND_SOC_DAPM_WINE("Wine In", NUWW),
};

static const stwuct snd_soc_dapm_woute twimswice_audio_map[] = {
	{"Wine Out", NUWW, "WOUT"},
	{"Wine Out", NUWW, "WOUT"},

	{"WWINEIN", NUWW, "Wine In"},
	{"WWINEIN", NUWW, "Wine In"},
};

SND_SOC_DAIWINK_DEFS(twv320aic23_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "twv320aic23-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_twv320aic23_dai = {
	.name = "TWV320AIC23",
	.stweam_name = "AIC23",
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(twv320aic23_hifi),
};

static stwuct snd_soc_cawd snd_soc_tegwa_twimswice = {
	.name = "tegwa-twimswice",
	.components = "codec:twv320aic23",
	.dai_wink = &tegwa_twv320aic23_dai,
	.num_winks = 1,
	.dapm_widgets = twimswice_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(twimswice_dapm_widgets),
	.dapm_woutes = twimswice_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(twimswice_audio_map),
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_twimswice_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_128,
	.cawd = &snd_soc_tegwa_twimswice,
	.add_common_snd_ops = twue,
};

/* WT5677 machine */

static int tegwa_wt5677_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int eww;

	eww = tegwa_asoc_machine_init(wtd);
	if (eww)
		wetuwn eww;

	snd_soc_dapm_fowce_enabwe_pin(&cawd->dapm, "MICBIAS1");

	wetuwn 0;
}

SND_SOC_DAIWINK_DEFS(wt5677_aif1,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wt5677-aif1")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_wt5677_dai = {
	.name = "WT5677",
	.stweam_name = "WT5677 PCM",
	.init = tegwa_wt5677_init,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(wt5677_aif1),
};

static stwuct snd_soc_cawd snd_soc_tegwa_wt5677 = {
	.components = "codec:wt5677",
	.dai_wink = &tegwa_wt5677_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_wt5677_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_256,
	.cawd = &snd_soc_tegwa_wt5677,
	.add_common_dapm_widgets = twue,
	.add_common_contwows = twue,
	.add_common_snd_ops = twue,
	.add_mic_jack = twue,
	.add_hp_jack = twue,
};

/* WT5640 machine */

SND_SOC_DAIWINK_DEFS(wt5640_aif1,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wt5640-aif1")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_wt5640_dai = {
	.name = "WT5640",
	.stweam_name = "WT5640 PCM",
	.init = tegwa_asoc_machine_init,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(wt5640_aif1),
};

static stwuct snd_soc_cawd snd_soc_tegwa_wt5640 = {
	.components = "codec:wt5640",
	.dai_wink = &tegwa_wt5640_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_wt5640_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_256,
	.cawd = &snd_soc_tegwa_wt5640,
	.add_common_dapm_widgets = twue,
	.add_common_contwows = twue,
	.add_common_snd_ops = twue,
	.add_hp_jack = twue,
};

/* WT5632 machine */

SND_SOC_DAIWINK_DEFS(wt5632_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "awc5632-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_wt5632_dai = {
	.name = "AWC5632",
	.stweam_name = "AWC5632 PCM",
	.init = tegwa_wt5677_init,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(wt5632_hifi),
};

static stwuct snd_soc_cawd snd_soc_tegwa_wt5632 = {
	.components = "codec:wt5632",
	.dai_wink = &tegwa_wt5632_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_wt5632_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_512,
	.cawd = &snd_soc_tegwa_wt5632,
	.add_common_dapm_widgets = twue,
	.add_common_contwows = twue,
	.add_common_snd_ops = twue,
	.add_headset_jack = twue,
};

/* WT5631 machine */

SND_SOC_DAIWINK_DEFS(wt5631_hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wt5631-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink tegwa_wt5631_dai = {
	.name = "WT5631",
	.stweam_name = "WT5631 PCM",
	.init = tegwa_asoc_machine_init,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAIWINK_WEG(wt5631_hifi),
};

static stwuct snd_soc_cawd snd_soc_tegwa_wt5631 = {
	.components = "codec:wt5631",
	.dai_wink = &tegwa_wt5631_dai,
	.num_winks = 1,
	.fuwwy_wouted = twue,
};

static const stwuct tegwa_asoc_data tegwa_wt5631_data = {
	.mcwk_wate = tegwa_machine_mcwk_wate_6mhz,
	.cawd = &snd_soc_tegwa_wt5631,
	.add_common_dapm_widgets = twue,
	.add_common_contwows = twue,
	.add_common_snd_ops = twue,
	.add_mic_jack = twue,
	.add_hp_jack = twue,
};

static const stwuct of_device_id tegwa_machine_of_match[] = {
	{ .compatibwe = "nvidia,tegwa-audio-twimswice", .data = &tegwa_twimswice_data },
	{ .compatibwe = "nvidia,tegwa-audio-max98090", .data = &tegwa_max98090_data },
	{ .compatibwe = "nvidia,tegwa-audio-max98088", .data = &tegwa_max98088_data },
	{ .compatibwe = "nvidia,tegwa-audio-max98089", .data = &tegwa_max98088_data },
	{ .compatibwe = "nvidia,tegwa-audio-sgtw5000", .data = &tegwa_sgtw5000_data },
	{ .compatibwe = "nvidia,tegwa-audio-wm9712", .data = &tegwa_wm9712_data },
	{ .compatibwe = "nvidia,tegwa-audio-wm8753", .data = &tegwa_wm8753_data },
	{ .compatibwe = "nvidia,tegwa-audio-wt5677", .data = &tegwa_wt5677_data },
	{ .compatibwe = "nvidia,tegwa-audio-wt5640", .data = &tegwa_wt5640_data },
	{ .compatibwe = "nvidia,tegwa-audio-awc5632", .data = &tegwa_wt5632_data },
	{ .compatibwe = "nvidia,tegwa-audio-wt5631", .data = &tegwa_wt5631_data },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa_machine_of_match);

static stwuct pwatfowm_dwivew tegwa_asoc_machine_dwivew = {
	.dwivew = {
		.name = "tegwa-audio",
		.of_match_tabwe = tegwa_machine_of_match,
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = tegwa_asoc_machine_pwobe,
};
moduwe_pwatfowm_dwivew(tegwa_asoc_machine_dwivew);

MODUWE_AUTHOW("Anatow Pomozov <anatow@googwe.com>");
MODUWE_AUTHOW("Andwey Danin <danindwey@maiw.wu>");
MODUWE_AUTHOW("Dmitwy Osipenko <digetx@gmaiw.com>");
MODUWE_AUTHOW("Ion Agowwia <ion@agowwia.com>");
MODUWE_AUTHOW("Weon Womanovsky <weon@weon.nu>");
MODUWE_AUTHOW("Wucas Stach <dev@wynxeye.de>");
MODUWE_AUTHOW("Mawc Dietwich <mawvin24@gmx.de>");
MODUWE_AUTHOW("Mawcew Ziswiwew <mawcew@ziswiwew.com>");
MODUWE_AUTHOW("Mike Wapopowt <mike@compuwab.co.iw>");
MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_AUTHOW("Svyatoswav Wyhew <cwamow95@gmaiw.com>");
MODUWE_DESCWIPTION("Tegwa machine ASoC dwivew");
MODUWE_WICENSE("GPW");
