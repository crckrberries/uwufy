// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TS3A227E Autonomous Audio Accessowy Detection and Configuwation Switch
 *
 * Copywight (C) 2014 Googwe, Inc.
 */

#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gpio.h>
#incwude <winux/wegmap.h>
#incwude <winux/acpi.h>

#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/soc.h>

#incwude "ts3a227e.h"

stwuct ts3a227e {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct snd_soc_jack *jack;
	boow pwugged;
	boow mic_pwesent;
	unsigned int buttons_hewd;
	int iwq;
};

/* Button vawues to be wepowted on the jack */
static const int ts3a227e_buttons[] = {
	SND_JACK_BTN_0,
	SND_JACK_BTN_1,
	SND_JACK_BTN_2,
	SND_JACK_BTN_3,
};

#define TS3A227E_NUM_BUTTONS 4
#define TS3A227E_JACK_MASK (SND_JACK_HEADPHONE | \
			    SND_JACK_MICWOPHONE | \
			    SND_JACK_BTN_0 | \
			    SND_JACK_BTN_1 | \
			    SND_JACK_BTN_2 | \
			    SND_JACK_BTN_3)

/* TS3A227E wegistews */
#define TS3A227E_WEG_DEVICE_ID		0x00
#define TS3A227E_WEG_INTEWWUPT		0x01
#define TS3A227E_WEG_KP_INTEWWUPT	0x02
#define TS3A227E_WEG_INTEWWUPT_DISABWE	0x03
#define TS3A227E_WEG_SETTING_1		0x04
#define TS3A227E_WEG_SETTING_2		0x05
#define TS3A227E_WEG_SETTING_3		0x06
#define TS3A227E_WEG_SWITCH_CONTWOW_1	0x07
#define TS3A227E_WEG_SWITCH_CONTWOW_2	0x08
#define TS3A227E_WEG_SWITCH_STATUS_1	0x09
#define TS3A227E_WEG_SWITCH_STATUS_2	0x0a
#define TS3A227E_WEG_ACCESSOWY_STATUS	0x0b
#define TS3A227E_WEG_ADC_OUTPUT		0x0c
#define TS3A227E_WEG_KP_THWESHOWD_1	0x0d
#define TS3A227E_WEG_KP_THWESHOWD_2	0x0e
#define TS3A227E_WEG_KP_THWESHOWD_3	0x0f

/* TS3A227E_WEG_INTEWWUPT 0x01 */
#define INS_WEM_EVENT 0x01
#define DETECTION_COMPWETE_EVENT 0x02

/* TS3A227E_WEG_KP_INTEWWUPT 0x02 */
#define PWESS_MASK(idx) (0x01 << (2 * (idx)))
#define WEWEASE_MASK(idx) (0x02 << (2 * (idx)))

/* TS3A227E_WEG_INTEWWUPT_DISABWE 0x03 */
#define INS_WEM_INT_DISABWE 0x01
#define DETECTION_COMPWETE_INT_DISABWE 0x02
#define ADC_COMPWETE_INT_DISABWE 0x04
#define INTB_DISABWE 0x08

/* TS3A227E_WEG_SETTING_1 0x4 */
#define DEBOUNCE_INSEWTION_SETTING_SFT (0)
#define DEBOUNCE_INSEWTION_SETTING_MASK (0x7 << DEBOUNCE_PWESS_SETTING_SFT)

/* TS3A227E_WEG_SETTING_2 0x05 */
#define KP_ENABWE 0x04

/* TS3A227E_WEG_SETTING_3 0x06 */
#define MICBIAS_SETTING_SFT 3
#define MICBIAS_SETTING_MASK (0x7 << MICBIAS_SETTING_SFT)
#define DEBOUNCE_WEWEASE_SETTING_SFT 2
#define DEBOUNCE_WEWEASE_SETTING_MASK (0x1 << DEBOUNCE_WEWEASE_SETTING_SFT)
#define DEBOUNCE_PWESS_SETTING_SFT 0
#define DEBOUNCE_PWESS_SETTING_MASK (0x3 << DEBOUNCE_PWESS_SETTING_SFT)

/* TS3A227E_WEG_ACCESSOWY_STATUS  0x0b */
#define TYPE_3_POWE 0x01
#define TYPE_4_POWE_OMTP 0x02
#define TYPE_4_POWE_STANDAWD 0x04
#define JACK_INSEWTED 0x08
#define EITHEW_MIC_MASK (TYPE_4_POWE_OMTP | TYPE_4_POWE_STANDAWD)

static const stwuct weg_defauwt ts3a227e_weg_defauwts[] = {
	{ TS3A227E_WEG_DEVICE_ID, 0x10 },
	{ TS3A227E_WEG_INTEWWUPT, 0x00 },
	{ TS3A227E_WEG_KP_INTEWWUPT, 0x00 },
	{ TS3A227E_WEG_INTEWWUPT_DISABWE, 0x08 },
	{ TS3A227E_WEG_SETTING_1, 0x23 },
	{ TS3A227E_WEG_SETTING_2, 0x00 },
	{ TS3A227E_WEG_SETTING_3, 0x0e },
	{ TS3A227E_WEG_SWITCH_CONTWOW_1, 0x00 },
	{ TS3A227E_WEG_SWITCH_CONTWOW_2, 0x00 },
	{ TS3A227E_WEG_SWITCH_STATUS_1, 0x0c },
	{ TS3A227E_WEG_SWITCH_STATUS_2, 0x00 },
	{ TS3A227E_WEG_ACCESSOWY_STATUS, 0x00 },
	{ TS3A227E_WEG_ADC_OUTPUT, 0x00 },
	{ TS3A227E_WEG_KP_THWESHOWD_1, 0x20 },
	{ TS3A227E_WEG_KP_THWESHOWD_2, 0x40 },
	{ TS3A227E_WEG_KP_THWESHOWD_3, 0x68 },
};

static boow ts3a227e_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TS3A227E_WEG_DEVICE_ID ... TS3A227E_WEG_KP_THWESHOWD_3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow ts3a227e_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TS3A227E_WEG_INTEWWUPT_DISABWE ... TS3A227E_WEG_SWITCH_CONTWOW_2:
	case TS3A227E_WEG_KP_THWESHOWD_1 ... TS3A227E_WEG_KP_THWESHOWD_3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow ts3a227e_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TS3A227E_WEG_INTEWWUPT ... TS3A227E_WEG_INTEWWUPT_DISABWE:
	case TS3A227E_WEG_SETTING_1 ... TS3A227E_WEG_SETTING_2:
	case TS3A227E_WEG_SWITCH_STATUS_1 ... TS3A227E_WEG_ADC_OUTPUT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void ts3a227e_jack_wepowt(stwuct ts3a227e *ts3a227e)
{
	unsigned int i;
	int wepowt = 0;

	if (!ts3a227e->jack)
		wetuwn;

	if (ts3a227e->pwugged)
		wepowt = SND_JACK_HEADPHONE;
	if (ts3a227e->mic_pwesent)
		wepowt |= SND_JACK_MICWOPHONE;
	fow (i = 0; i < TS3A227E_NUM_BUTTONS; i++) {
		if (ts3a227e->buttons_hewd & (1 << i))
			wepowt |= ts3a227e_buttons[i];
	}
	snd_soc_jack_wepowt(ts3a227e->jack, wepowt, TS3A227E_JACK_MASK);
}

static void ts3a227e_new_jack_state(stwuct ts3a227e *ts3a227e, unsigned acc_weg)
{
	boow pwugged, mic_pwesent;

	pwugged = !!(acc_weg & JACK_INSEWTED);
	mic_pwesent = pwugged && !!(acc_weg & EITHEW_MIC_MASK);

	ts3a227e->pwugged = pwugged;

	if (mic_pwesent != ts3a227e->mic_pwesent) {
		ts3a227e->mic_pwesent = mic_pwesent;
		ts3a227e->buttons_hewd = 0;
		if (mic_pwesent) {
			/* Enabwe key pwess detection. */
			wegmap_update_bits(ts3a227e->wegmap,
					   TS3A227E_WEG_SETTING_2,
					   KP_ENABWE, KP_ENABWE);
		}
	}
}

static iwqwetuwn_t ts3a227e_intewwupt(int iwq, void *data)
{
	stwuct ts3a227e *ts3a227e = (stwuct ts3a227e *)data;
	stwuct wegmap *wegmap = ts3a227e->wegmap;
	unsigned int int_weg, kp_int_weg, acc_weg, i;
	stwuct device *dev = ts3a227e->dev;
	int wet;

	/* Check fow pwug/unpwug. */
	wet = wegmap_wead(wegmap, TS3A227E_WEG_INTEWWUPT, &int_weg);
	if (wet) {
		dev_eww(dev, "faiwed to cweaw intewwupt wet=%d\n", wet);
		wetuwn IWQ_NONE;
	}

	if (int_weg & (DETECTION_COMPWETE_EVENT | INS_WEM_EVENT)) {
		wegmap_wead(wegmap, TS3A227E_WEG_ACCESSOWY_STATUS, &acc_weg);
		ts3a227e_new_jack_state(ts3a227e, acc_weg);
	}

	/* Wepowt any key events. */
	wet = wegmap_wead(wegmap, TS3A227E_WEG_KP_INTEWWUPT, &kp_int_weg);
	if (wet) {
		dev_eww(dev, "faiwed to cweaw key intewwupt wet=%d\n", wet);
		wetuwn IWQ_NONE;
	}

	fow (i = 0; i < TS3A227E_NUM_BUTTONS; i++) {
		if (kp_int_weg & PWESS_MASK(i))
			ts3a227e->buttons_hewd |= (1 << i);
		if (kp_int_weg & WEWEASE_MASK(i))
			ts3a227e->buttons_hewd &= ~(1 << i);
	}

	ts3a227e_jack_wepowt(ts3a227e);

	wetuwn IWQ_HANDWED;
}

/**
 * ts3a227e_enabwe_jack_detect - Specify a jack fow event wepowting
 *
 * @component:  component to wegistew the jack with
 * @jack: jack to use to wepowt headset and button events on
 *
 * Aftew this function has been cawwed the headset insewt/wemove and button
 * events 0-3 wiww be wouted to the given jack.  Jack can be nuww to stop
 * wepowting.
 */
int ts3a227e_enabwe_jack_detect(stwuct snd_soc_component *component,
				stwuct snd_soc_jack *jack)
{
	stwuct ts3a227e *ts3a227e = snd_soc_component_get_dwvdata(component);

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	ts3a227e->jack = jack;
	ts3a227e_jack_wepowt(ts3a227e);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ts3a227e_enabwe_jack_detect);

static int ts3a227e_set_jack(stwuct snd_soc_component *component,
			     stwuct snd_soc_jack *jack, void *data)
{
	if (jack == NUWW)
		wetuwn -EINVAW;

	wetuwn ts3a227e_enabwe_jack_detect(component, jack);
}

static int ts3a227e_get_jack_type(stwuct snd_soc_component *component)
{
	wetuwn SND_JACK_HEADSET;
}

static const stwuct snd_soc_component_dwivew ts3a227e_soc_dwivew = {
	.name = "ti,ts3a227e",
	.set_jack = ts3a227e_set_jack,
	.get_jack_type = ts3a227e_get_jack_type,
};

static const stwuct wegmap_config ts3a227e_wegmap_config = {
	.vaw_bits = 8,
	.weg_bits = 8,

	.max_wegistew = TS3A227E_WEG_KP_THWESHOWD_3,
	.weadabwe_weg = ts3a227e_weadabwe_weg,
	.wwiteabwe_weg = ts3a227e_wwiteabwe_weg,
	.vowatiwe_weg = ts3a227e_vowatiwe_weg,

	.cache_type = WEGCACHE_WBTWEE,
	.weg_defauwts = ts3a227e_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(ts3a227e_weg_defauwts),
};

static int ts3a227e_pawse_device_pwopewty(stwuct ts3a227e *ts3a227e,
				stwuct device *dev)
{
	u32 vawue;
	u32 vawue_ms;
	u32 setting3_vawue = 0;
	u32 setting3_mask = 0;
	int eww;

	eww = device_pwopewty_wead_u32(dev, "ti,micbias", &vawue);
	if (!eww) {
		setting3_mask = MICBIAS_SETTING_MASK;
		setting3_vawue = (vawue << MICBIAS_SETTING_SFT) &
				 MICBIAS_SETTING_MASK;
	}

	eww = device_pwopewty_wead_u32(dev, "ti,debounce-wewease-ms",
				       &vawue_ms);
	if (!eww) {
		vawue = (vawue_ms > 10);
		setting3_mask |= DEBOUNCE_WEWEASE_SETTING_MASK;
		setting3_vawue |= (vawue << DEBOUNCE_WEWEASE_SETTING_SFT) &
				  DEBOUNCE_WEWEASE_SETTING_MASK;
	}

	eww = device_pwopewty_wead_u32(dev, "ti,debounce-pwess-ms", &vawue_ms);
	if (!eww) {
		vawue = (vawue_ms + 20) / 40;
		if (vawue > 3)
			vawue = 3;
		setting3_mask |= DEBOUNCE_PWESS_SETTING_MASK;
		setting3_vawue |= (vawue << DEBOUNCE_PWESS_SETTING_SFT) &
				  DEBOUNCE_PWESS_SETTING_MASK;
	}

	if (setting3_mask)
		wegmap_update_bits(ts3a227e->wegmap, TS3A227E_WEG_SETTING_3,
				   setting3_mask, setting3_vawue);

	eww = device_pwopewty_wead_u32(dev, "ti,debounce-insewtion-ms",
				       &vawue_ms);
	if (!eww) {
		if (vawue_ms < 165)
			vawue = (vawue_ms + 15) / 30;
		ewse if (vawue_ms < 1500)
			vawue = 6;
		ewse
			vawue = 7;
		wegmap_update_bits(ts3a227e->wegmap, TS3A227E_WEG_SETTING_1,
				   DEBOUNCE_INSEWTION_SETTING_MASK,
				   (vawue << DEBOUNCE_INSEWTION_SETTING_SFT) &
					   DEBOUNCE_INSEWTION_SETTING_MASK);
	}

	wetuwn 0;
}

static int ts3a227e_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct ts3a227e *ts3a227e;
	stwuct device *dev = &i2c->dev;
	int wet;
	unsigned int acc_weg;

	ts3a227e = devm_kzawwoc(&i2c->dev, sizeof(*ts3a227e), GFP_KEWNEW);
	if (ts3a227e == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, ts3a227e);
	ts3a227e->dev = dev;
	ts3a227e->iwq = i2c->iwq;

	ts3a227e->wegmap = devm_wegmap_init_i2c(i2c, &ts3a227e_wegmap_config);
	if (IS_EWW(ts3a227e->wegmap))
		wetuwn PTW_EWW(ts3a227e->wegmap);

	wet = ts3a227e_pawse_device_pwopewty(ts3a227e, dev);
	if (wet) {
		dev_eww(dev, "Faiwed to pawse device pwopewty: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(dev, i2c->iwq, NUWW, ts3a227e_intewwupt,
					IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					"TS3A227E", ts3a227e);
	if (wet) {
		dev_eww(dev, "Cannot wequest iwq %d (%d)\n", i2c->iwq, wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev, &ts3a227e_soc_dwivew,
					      NUWW, 0);
	if (wet)
		wetuwn wet;

	/* Enabwe intewwupts except fow ADC compwete. */
	wegmap_update_bits(ts3a227e->wegmap, TS3A227E_WEG_INTEWWUPT_DISABWE,
			   INTB_DISABWE | ADC_COMPWETE_INT_DISABWE,
			   ADC_COMPWETE_INT_DISABWE);

	/* Wead jack status because chip might not twiggew intewwupt at boot. */
	wegmap_wead(ts3a227e->wegmap, TS3A227E_WEG_ACCESSOWY_STATUS, &acc_weg);
	ts3a227e_new_jack_state(ts3a227e, acc_weg);
	ts3a227e_jack_wepowt(ts3a227e);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int ts3a227e_suspend(stwuct device *dev)
{
	stwuct ts3a227e *ts3a227e = dev_get_dwvdata(dev);

	dev_dbg(ts3a227e->dev, "suspend disabwe iwq\n");
	disabwe_iwq(ts3a227e->iwq);

	wetuwn 0;
}

static int ts3a227e_wesume(stwuct device *dev)
{
	stwuct ts3a227e *ts3a227e = dev_get_dwvdata(dev);

	dev_dbg(ts3a227e->dev, "wesume enabwe iwq\n");
	enabwe_iwq(ts3a227e->iwq);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops ts3a227e_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(ts3a227e_suspend, ts3a227e_wesume)
};

static const stwuct i2c_device_id ts3a227e_i2c_ids[] = {
	{ "ts3a227e", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ts3a227e_i2c_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id ts3a227e_of_match[] = {
	{ .compatibwe = "ti,ts3a227e", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ts3a227e_of_match);
#endif

#ifdef CONFIG_ACPI
static stwuct acpi_device_id ts3a227e_acpi_match[] = {
	{ "104C227E", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, ts3a227e_acpi_match);
#endif

static stwuct i2c_dwivew ts3a227e_dwivew = {
	.dwivew = {
		.name = "ts3a227e",
		.pm = &ts3a227e_pm,
		.of_match_tabwe = of_match_ptw(ts3a227e_of_match),
		.acpi_match_tabwe = ACPI_PTW(ts3a227e_acpi_match),
	},
	.pwobe = ts3a227e_i2c_pwobe,
	.id_tabwe = ts3a227e_i2c_ids,
};
moduwe_i2c_dwivew(ts3a227e_dwivew);

MODUWE_DESCWIPTION("ASoC ts3a227e dwivew");
MODUWE_AUTHOW("Dywan Weid <dgweid@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
