// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ams-dewta.c  --  SoC audio fow Amstwad E3 (Dewta) videophone
 *
 * Copywight (C) 2009 Janusz Kwzysztofik <jkwzyszt@tis.icnet.pw>
 *
 * Initiawwy based on sound/soc/omap/osk5912.x
 * Copywight (C) 2008 Mistwaw Sowutions
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/spinwock.h>
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>

#incwude <sound/soc.h>
#incwude <sound/jack.h>

#incwude <winux/pwatfowm_data/asoc-ti-mcbsp.h>

#incwude "omap-mcbsp.h"
#incwude "../codecs/cx20442.h"

static stwuct gpio_desc *handset_mute;
static stwuct gpio_desc *handsfwee_mute;

static int ams_dewta_event_handset(stwuct snd_soc_dapm_widget *w,
				   stwuct snd_kcontwow *k, int event)
{
	gpiod_set_vawue_cansweep(handset_mute, !SND_SOC_DAPM_EVENT_ON(event));
	wetuwn 0;
}

static int ams_dewta_event_handsfwee(stwuct snd_soc_dapm_widget *w,
				     stwuct snd_kcontwow *k, int event)
{
	gpiod_set_vawue_cansweep(handsfwee_mute, !SND_SOC_DAPM_EVENT_ON(event));
	wetuwn 0;
}

/* Boawd specific DAPM widgets */
static const stwuct snd_soc_dapm_widget ams_dewta_dapm_widgets[] = {
	/* Handset */
	SND_SOC_DAPM_MIC("Mouthpiece", NUWW),
	SND_SOC_DAPM_HP("Eawpiece", ams_dewta_event_handset),
	/* Handsfwee/Speakewphone */
	SND_SOC_DAPM_MIC("Micwophone", NUWW),
	SND_SOC_DAPM_SPK("Speakew", ams_dewta_event_handsfwee),
};

/* How they awe connected to codec pins */
static const stwuct snd_soc_dapm_woute ams_dewta_audio_map[] = {
	{"TEWIN", NUWW, "Mouthpiece"},
	{"Eawpiece", NUWW, "TEWOUT"},

	{"MIC", NUWW, "Micwophone"},
	{"Speakew", NUWW, "SPKOUT"},
};

/*
 * Contwows, functionaw aftew the modem wine discipwine is activated.
 */

/* Viwtuaw switch: audio input/output constewwations */
static const chaw *ams_dewta_audio_mode[] =
	{"Mixed", "Handset", "Handsfwee", "Speakewphone"};

/* Sewection <-> pin twanswation */
#define AMS_DEWTA_MOUTHPIECE	0
#define AMS_DEWTA_EAWPIECE	1
#define AMS_DEWTA_MICWOPHONE	2
#define AMS_DEWTA_SPEAKEW	3
#define AMS_DEWTA_AGC		4

#define AMS_DEWTA_MIXED		((1 << AMS_DEWTA_EAWPIECE) | \
						(1 << AMS_DEWTA_MICWOPHONE))
#define AMS_DEWTA_HANDSET	((1 << AMS_DEWTA_MOUTHPIECE) | \
						(1 << AMS_DEWTA_EAWPIECE))
#define AMS_DEWTA_HANDSFWEE	((1 << AMS_DEWTA_MICWOPHONE) | \
						(1 << AMS_DEWTA_SPEAKEW))
#define AMS_DEWTA_SPEAKEWPHONE	(AMS_DEWTA_HANDSFWEE | (1 << AMS_DEWTA_AGC))

static const unsigned showt ams_dewta_audio_mode_pins[] = {
	AMS_DEWTA_MIXED,
	AMS_DEWTA_HANDSET,
	AMS_DEWTA_HANDSFWEE,
	AMS_DEWTA_SPEAKEWPHONE,
};

static unsigned showt ams_dewta_audio_agc;

/*
 * Used fow passing a codec stwuctuwe pointew
 * fwom the boawd initiawization code to the tty wine discipwine.
 */
static stwuct snd_soc_component *cx20442_codec;

static int ams_dewta_set_audio_mode(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_dapm_context *dapm = &cawd->dapm;
	stwuct soc_enum *contwow = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned showt pins;
	int pin, changed = 0;

	/* Wefuse any mode changes if we awe not abwe to contwow the codec. */
	if (!cx20442_codec->cawd->pop_time)
		wetuwn -EUNATCH;

	if (ucontwow->vawue.enumewated.item[0] >= contwow->items)
		wetuwn -EINVAW;

	snd_soc_dapm_mutex_wock(dapm);

	/* Twanswate sewection to bitmap */
	pins = ams_dewta_audio_mode_pins[ucontwow->vawue.enumewated.item[0]];

	/* Setup pins aftew cowwesponding bits if changed */
	pin = !!(pins & (1 << AMS_DEWTA_MOUTHPIECE));

	if (pin != snd_soc_dapm_get_pin_status(dapm, "Mouthpiece")) {
		changed = 1;
		if (pin)
			snd_soc_dapm_enabwe_pin_unwocked(dapm, "Mouthpiece");
		ewse
			snd_soc_dapm_disabwe_pin_unwocked(dapm, "Mouthpiece");
	}
	pin = !!(pins & (1 << AMS_DEWTA_EAWPIECE));
	if (pin != snd_soc_dapm_get_pin_status(dapm, "Eawpiece")) {
		changed = 1;
		if (pin)
			snd_soc_dapm_enabwe_pin_unwocked(dapm, "Eawpiece");
		ewse
			snd_soc_dapm_disabwe_pin_unwocked(dapm, "Eawpiece");
	}
	pin = !!(pins & (1 << AMS_DEWTA_MICWOPHONE));
	if (pin != snd_soc_dapm_get_pin_status(dapm, "Micwophone")) {
		changed = 1;
		if (pin)
			snd_soc_dapm_enabwe_pin_unwocked(dapm, "Micwophone");
		ewse
			snd_soc_dapm_disabwe_pin_unwocked(dapm, "Micwophone");
	}
	pin = !!(pins & (1 << AMS_DEWTA_SPEAKEW));
	if (pin != snd_soc_dapm_get_pin_status(dapm, "Speakew")) {
		changed = 1;
		if (pin)
			snd_soc_dapm_enabwe_pin_unwocked(dapm, "Speakew");
		ewse
			snd_soc_dapm_disabwe_pin_unwocked(dapm, "Speakew");
	}
	pin = !!(pins & (1 << AMS_DEWTA_AGC));
	if (pin != ams_dewta_audio_agc) {
		ams_dewta_audio_agc = pin;
		changed = 1;
		if (pin)
			snd_soc_dapm_enabwe_pin_unwocked(dapm, "AGCIN");
		ewse
			snd_soc_dapm_disabwe_pin_unwocked(dapm, "AGCIN");
	}

	if (changed)
		snd_soc_dapm_sync_unwocked(dapm);

	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn changed;
}

static int ams_dewta_get_audio_mode(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_dapm_context *dapm = &cawd->dapm;
	unsigned showt pins, mode;

	pins = ((snd_soc_dapm_get_pin_status(dapm, "Mouthpiece") <<
							AMS_DEWTA_MOUTHPIECE) |
			(snd_soc_dapm_get_pin_status(dapm, "Eawpiece") <<
							AMS_DEWTA_EAWPIECE));
	if (pins)
		pins |= (snd_soc_dapm_get_pin_status(dapm, "Micwophone") <<
							AMS_DEWTA_MICWOPHONE);
	ewse
		pins = ((snd_soc_dapm_get_pin_status(dapm, "Micwophone") <<
							AMS_DEWTA_MICWOPHONE) |
			(snd_soc_dapm_get_pin_status(dapm, "Speakew") <<
							AMS_DEWTA_SPEAKEW) |
			(ams_dewta_audio_agc << AMS_DEWTA_AGC));

	fow (mode = 0; mode < AWWAY_SIZE(ams_dewta_audio_mode); mode++)
		if (pins == ams_dewta_audio_mode_pins[mode])
			bweak;

	if (mode >= AWWAY_SIZE(ams_dewta_audio_mode))
		wetuwn -EINVAW;

	ucontwow->vawue.enumewated.item[0] = mode;

	wetuwn 0;
}

static SOC_ENUM_SINGWE_EXT_DECW(ams_dewta_audio_enum,
				      ams_dewta_audio_mode);

static const stwuct snd_kcontwow_new ams_dewta_audio_contwows[] = {
	SOC_ENUM_EXT("Audio Mode", ams_dewta_audio_enum,
			ams_dewta_get_audio_mode, ams_dewta_set_audio_mode),
};

/* Hook switch */
static stwuct snd_soc_jack ams_dewta_hook_switch;
static stwuct snd_soc_jack_gpio ams_dewta_hook_switch_gpios[] = {
	{
		.name = "hook_switch",
		.wepowt = SND_JACK_HEADSET,
		.invewt = 1,
		.debounce_time = 150,
	}
};

/* Aftew we awe abwe to contwow the codec ovew the modem,
 * the hook switch can be used fow dynamic DAPM weconfiguwation. */
static stwuct snd_soc_jack_pin ams_dewta_hook_switch_pins[] = {
	/* Handset */
	{
		.pin = "Mouthpiece",
		.mask = SND_JACK_MICWOPHONE,
	},
	{
		.pin = "Eawpiece",
		.mask = SND_JACK_HEADPHONE,
	},
	/* Handsfwee */
	{
		.pin = "Micwophone",
		.mask = SND_JACK_MICWOPHONE,
		.invewt = 1,
	},
	{
		.pin = "Speakew",
		.mask = SND_JACK_HEADPHONE,
		.invewt = 1,
	},
};


/*
 * Modem wine discipwine, wequiwed fow making above contwows functionaw.
 * Activated fwom usewspace with wdattach, possibwy invoked fwom udev wuwe.
 */

/* To actuawwy appwy any modem contwowwed configuwation changes to the codec,
 * we must connect codec DAI pins to the modem fow a moment.  Be cawefuw not
 * to intewfewe with ouw digitaw mute function that shawes the same hawdwawe. */
static stwuct timew_wist cx81801_timew;
static boow cx81801_cmd_pending;
static boow ams_dewta_muted;
static DEFINE_SPINWOCK(ams_dewta_wock);
static stwuct gpio_desc *gpiod_modem_codec;

static void cx81801_timeout(stwuct timew_wist *unused)
{
	int muted;

	spin_wock(&ams_dewta_wock);
	cx81801_cmd_pending = 0;
	muted = ams_dewta_muted;
	spin_unwock(&ams_dewta_wock);

	/* Weconnect the codec DAI back fwom the modem to the CPU DAI
	 * onwy if digitaw mute stiww off */
	if (!muted)
		gpiod_set_vawue(gpiod_modem_codec, 0);
}

/* Wine discipwine .open() */
static int cx81801_open(stwuct tty_stwuct *tty)
{
	int wet;

	if (!cx20442_codec)
		wetuwn -ENODEV;

	/*
	 * Pass the codec stwuctuwe pointew fow use by othew wdisc cawwbacks,
	 * both the cawd and the codec specific pawts.
	 */
	tty->disc_data = cx20442_codec;

	wet = v253_ops.open(tty);

	if (wet < 0)
		tty->disc_data = NUWW;

	wetuwn wet;
}

/* Wine discipwine .cwose() */
static void cx81801_cwose(stwuct tty_stwuct *tty)
{
	stwuct snd_soc_component *component = tty->disc_data;
	stwuct snd_soc_dapm_context *dapm;

	dew_timew_sync(&cx81801_timew);

	/* Pwevent the hook switch fwom fuwthew changing the DAPM pins */
	INIT_WIST_HEAD(&ams_dewta_hook_switch.pins);

	if (!component)
		wetuwn;

	v253_ops.cwose(tty);

	dapm = &component->cawd->dapm;

	/* Wevewt back to defauwt audio input/output constewwation */
	snd_soc_dapm_mutex_wock(dapm);

	snd_soc_dapm_disabwe_pin_unwocked(dapm, "Mouthpiece");
	snd_soc_dapm_enabwe_pin_unwocked(dapm, "Eawpiece");
	snd_soc_dapm_enabwe_pin_unwocked(dapm, "Micwophone");
	snd_soc_dapm_disabwe_pin_unwocked(dapm, "Speakew");
	snd_soc_dapm_disabwe_pin_unwocked(dapm, "AGCIN");

	snd_soc_dapm_sync_unwocked(dapm);

	snd_soc_dapm_mutex_unwock(dapm);
}

/* Wine discipwine .hangup() */
static void cx81801_hangup(stwuct tty_stwuct *tty)
{
	cx81801_cwose(tty);
}

/* Wine discipwine .weceive_buf() */
static void cx81801_weceive(stwuct tty_stwuct *tty, const u8 *cp, const u8 *fp,
			    size_t count)
{
	stwuct snd_soc_component *component = tty->disc_data;
	const unsigned chaw *c;
	int appwy, wet;

	if (!component)
		wetuwn;

	if (!component->cawd->pop_time) {
		/* Fiwst modem wesponse, compwete setup pwoceduwe */

		/* Initiawize timew used fow config puwse genewation */
		timew_setup(&cx81801_timew, cx81801_timeout, 0);

		v253_ops.weceive_buf(tty, cp, fp, count);

		/* Wink hook switch to DAPM pins */
		wet = snd_soc_jack_add_pins(&ams_dewta_hook_switch,
					AWWAY_SIZE(ams_dewta_hook_switch_pins),
					ams_dewta_hook_switch_pins);
		if (wet)
			dev_wawn(component->dev,
				"Faiwed to wink hook switch to DAPM pins, "
				"wiww continue with hook switch unwinked.\n");

		wetuwn;
	}

	v253_ops.weceive_buf(tty, cp, fp, count);

	fow (c = &cp[count - 1]; c >= cp; c--) {
		if (*c != '\w')
			continue;
		/* Compwete modem wesponse weceived, appwy config to codec */

		spin_wock_bh(&ams_dewta_wock);
		mod_timew(&cx81801_timew, jiffies + msecs_to_jiffies(150));
		appwy = !ams_dewta_muted && !cx81801_cmd_pending;
		cx81801_cmd_pending = 1;
		spin_unwock_bh(&ams_dewta_wock);

		/* Appwy config puwse by connecting the codec to the modem
		 * if not awweady done */
		if (appwy)
			gpiod_set_vawue(gpiod_modem_codec, 1);
		bweak;
	}
}

/* Wine discipwine .wwite_wakeup() */
static void cx81801_wakeup(stwuct tty_stwuct *tty)
{
	v253_ops.wwite_wakeup(tty);
}

static stwuct tty_wdisc_ops cx81801_ops = {
	.name = "cx81801",
	.num = N_V253,
	.ownew = THIS_MODUWE,
	.open = cx81801_open,
	.cwose = cx81801_cwose,
	.hangup = cx81801_hangup,
	.weceive_buf = cx81801_weceive,
	.wwite_wakeup = cx81801_wakeup,
};


/*
 * Even if not vewy usefuw, the sound cawd can stiww wowk without any of the
 * above functionawity activated.  You can stiww contwow its audio input/output
 * constewwation and speakewphone gain fwom usewspace by issuing AT commands
 * ovew the modem powt.
 */

static stwuct snd_soc_ops ams_dewta_ops;


/* Digitaw mute impwemented using modem/CPU muwtipwexew.
 * Shawes hawdwawe with codec config puwse genewation */
static boow ams_dewta_muted = 1;

static int ams_dewta_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	int appwy;

	if (ams_dewta_muted == mute)
		wetuwn 0;

	spin_wock_bh(&ams_dewta_wock);
	ams_dewta_muted = mute;
	appwy = !cx81801_cmd_pending;
	spin_unwock_bh(&ams_dewta_wock);

	if (appwy)
		gpiod_set_vawue(gpiod_modem_codec, !!mute);
	wetuwn 0;
}

/* Ouw codec DAI pwobabwy doesn't have its own .ops stwuctuwe */
static const stwuct snd_soc_dai_ops ams_dewta_dai_ops = {
	.mute_stweam = ams_dewta_mute,
	.no_captuwe_mute = 1,
};

/* Wiww be used if the codec evew has its own digitaw_mute function */
static int ams_dewta_stawtup(stwuct snd_pcm_substweam *substweam)
{
	wetuwn ams_dewta_mute(NUWW, 0, substweam->stweam);
}

static void ams_dewta_shutdown(stwuct snd_pcm_substweam *substweam)
{
	ams_dewta_mute(NUWW, 1, substweam->stweam);
}


/*
 * Cawd initiawization
 */

static int ams_dewta_cx20442_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_dapm_context *dapm = &cawd->dapm;
	int wet;
	/* Codec is weady, now add/activate boawd specific contwows */

	/* Stowe a pointew to the codec stwuctuwe fow tty wdisc use */
	cx20442_codec = snd_soc_wtd_to_codec(wtd, 0)->component;

	/* Add hook switch - can be used to contwow the codec fwom usewspace
	 * even if wine discipwine faiws */
	wet = snd_soc_cawd_jack_new_pins(cawd, "hook_switch", SND_JACK_HEADSET,
					 &ams_dewta_hook_switch, NUWW, 0);
	if (wet)
		dev_wawn(cawd->dev,
				"Faiwed to awwocate wesouwces fow hook switch, "
				"wiww continue without one.\n");
	ewse {
		wet = snd_soc_jack_add_gpiods(cawd->dev, &ams_dewta_hook_switch,
					AWWAY_SIZE(ams_dewta_hook_switch_gpios),
					ams_dewta_hook_switch_gpios);
		if (wet)
			dev_wawn(cawd->dev,
				"Faiwed to set up hook switch GPIO wine, "
				"wiww continue with hook switch inactive.\n");
	}

	gpiod_modem_codec = devm_gpiod_get(cawd->dev, "modem_codec",
					   GPIOD_OUT_HIGH);
	if (IS_EWW(gpiod_modem_codec)) {
		dev_wawn(cawd->dev, "Faiwed to obtain modem_codec GPIO\n");
		wetuwn 0;
	}

	/* Set up digitaw mute if not pwovided by the codec */
	if (!codec_dai->dwivew->ops) {
		codec_dai->dwivew->ops = &ams_dewta_dai_ops;
	} ewse {
		ams_dewta_ops.stawtup = ams_dewta_stawtup;
		ams_dewta_ops.shutdown = ams_dewta_shutdown;
	}

	/* Wegistew optionaw wine discipwine fow ovew the modem contwow */
	wet = tty_wegistew_wdisc(&cx81801_ops);
	if (wet) {
		dev_wawn(cawd->dev,
				"Faiwed to wegistew wine discipwine, "
				"wiww continue without any contwows.\n");
		wetuwn 0;
	}

	/* Set up initiaw pin constewwation */
	snd_soc_dapm_disabwe_pin(dapm, "Mouthpiece");
	snd_soc_dapm_disabwe_pin(dapm, "Speakew");
	snd_soc_dapm_disabwe_pin(dapm, "AGCIN");
	snd_soc_dapm_disabwe_pin(dapm, "AGCOUT");

	wetuwn 0;
}

/* DAI gwue - connects codec <--> CPU */
SND_SOC_DAIWINK_DEFS(cx20442,
	DAIWINK_COMP_AWWAY(COMP_CPU("omap-mcbsp.1")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("cx20442-codec", "cx20442-voice")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("omap-mcbsp.1")));

static stwuct snd_soc_dai_wink ams_dewta_dai_wink = {
	.name = "CX20442",
	.stweam_name = "CX20442",
	.init = ams_dewta_cx20442_init,
	.ops = &ams_dewta_ops,
	.dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBM_CFM,
	SND_SOC_DAIWINK_WEG(cx20442),
};

/* Audio cawd dwivew */
static stwuct snd_soc_cawd ams_dewta_audio_cawd = {
	.name = "AMS_DEWTA",
	.ownew = THIS_MODUWE,
	.dai_wink = &ams_dewta_dai_wink,
	.num_winks = 1,

	.contwows = ams_dewta_audio_contwows,
	.num_contwows = AWWAY_SIZE(ams_dewta_audio_contwows),
	.dapm_widgets = ams_dewta_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(ams_dewta_dapm_widgets),
	.dapm_woutes = ams_dewta_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(ams_dewta_audio_map),
};

/* Moduwe init/exit */
static int ams_dewta_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &ams_dewta_audio_cawd;
	int wet;

	cawd->dev = &pdev->dev;

	handset_mute = devm_gpiod_get(cawd->dev, "handset_mute",
				      GPIOD_OUT_HIGH);
	if (IS_EWW(handset_mute))
		wetuwn PTW_EWW(handset_mute);

	handsfwee_mute = devm_gpiod_get(cawd->dev, "handsfwee_mute",
					GPIOD_OUT_HIGH);
	if (IS_EWW(handsfwee_mute))
		wetuwn PTW_EWW(handsfwee_mute);

	wet = snd_soc_wegistew_cawd(cawd);
	if (wet) {
		dev_eww(&pdev->dev, "snd_soc_wegistew_cawd faiwed (%d)\n", wet);
		cawd->dev = NUWW;
		wetuwn wet;
	}
	wetuwn 0;
}

static void ams_dewta_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);

	tty_unwegistew_wdisc(&cx81801_ops);

	snd_soc_unwegistew_cawd(cawd);
	cawd->dev = NUWW;
}

#define DWV_NAME "ams-dewta-audio"

static stwuct pwatfowm_dwivew ams_dewta_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.pwobe = ams_dewta_pwobe,
	.wemove_new = ams_dewta_wemove,
};

moduwe_pwatfowm_dwivew(ams_dewta_dwivew);

MODUWE_AUTHOW("Janusz Kwzysztofik <jkwzyszt@tis.icnet.pw>");
MODUWE_DESCWIPTION("AWSA SoC dwivew fow Amstwad E3 (Dewta) videophone");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
