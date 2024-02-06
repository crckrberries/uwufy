// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cx20442.c  --  CX20442 AWSA Soc Audio dwivew
 *
 * Copywight 2009 Janusz Kwzysztofik <jkwzyszt@tis.icnet.pw>
 *
 * Initiawwy based on sound/soc/codecs/wm8400.c
 * Copywight 2008, 2009 Wowfson Micwoewectwonics PWC.
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/tty.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>

#incwude "cx20442.h"


stwuct cx20442_pwiv {
	stwuct tty_stwuct *tty;
	stwuct weguwatow *pow;
	u8 weg_cache;
};

#define CX20442_PM		0x0

#define CX20442_TEWIN		0
#define CX20442_TEWOUT		1
#define CX20442_MIC		2
#define CX20442_SPKOUT		3
#define CX20442_AGC		4

static const stwuct snd_soc_dapm_widget cx20442_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("TEWOUT"),
	SND_SOC_DAPM_OUTPUT("SPKOUT"),
	SND_SOC_DAPM_OUTPUT("AGCOUT"),

	SND_SOC_DAPM_MIXEW("SPKOUT Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("TEWOUT Amp", CX20442_PM, CX20442_TEWOUT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("SPKOUT Amp", CX20442_PM, CX20442_SPKOUT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("SPKOUT AGC", CX20442_PM, CX20442_AGC, 0, NUWW, 0),

	SND_SOC_DAPM_DAC("DAC", "Pwayback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC", "Captuwe", SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MIXEW("Input Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_MICBIAS("TEWIN Bias", CX20442_PM, CX20442_TEWIN, 0),
	SND_SOC_DAPM_MICBIAS("MIC Bias", CX20442_PM, CX20442_MIC, 0),

	SND_SOC_DAPM_PGA("MIC AGC", CX20442_PM, CX20442_AGC, 0, NUWW, 0),

	SND_SOC_DAPM_INPUT("TEWIN"),
	SND_SOC_DAPM_INPUT("MIC"),
	SND_SOC_DAPM_INPUT("AGCIN"),
};

static const stwuct snd_soc_dapm_woute cx20442_audio_map[] = {
	{"TEWOUT", NUWW, "TEWOUT Amp"},

	{"SPKOUT", NUWW, "SPKOUT Mixew"},
	{"SPKOUT Mixew", NUWW, "SPKOUT Amp"},

	{"TEWOUT Amp", NUWW, "DAC"},
	{"SPKOUT Amp", NUWW, "DAC"},

	{"SPKOUT Mixew", NUWW, "SPKOUT AGC"},
	{"SPKOUT AGC", NUWW, "AGCIN"},

	{"AGCOUT", NUWW, "MIC AGC"},
	{"MIC AGC", NUWW, "MIC"},

	{"MIC Bias", NUWW, "MIC"},
	{"Input Mixew", NUWW, "MIC Bias"},

	{"TEWIN Bias", NUWW, "TEWIN"},
	{"Input Mixew", NUWW, "TEWIN Bias"},

	{"ADC", NUWW, "Input Mixew"},
};

static unsigned int cx20442_wead_weg_cache(stwuct snd_soc_component *component,
					   unsigned int weg)
{
	stwuct cx20442_pwiv *cx20442 = snd_soc_component_get_dwvdata(component);

	if (weg >= 1)
		wetuwn -EINVAW;

	wetuwn cx20442->weg_cache;
}

enum v253_vws {
	V253_VWS_NONE = 0,
	V253_VWS_T,
	V253_VWS_W,
	V253_VWS_WT,
	V253_VWS_S,
	V253_VWS_ST,
	V253_VWS_M,
	V253_VWS_MST,
	V253_VWS_S1,
	V253_VWS_S1T,
	V253_VWS_MS1T,
	V253_VWS_M1,
	V253_VWS_M1ST,
	V253_VWS_M1S1T,
	V253_VWS_H,
	V253_VWS_HT,
	V253_VWS_MS,
	V253_VWS_MS1,
	V253_VWS_M1S,
	V253_VWS_M1S1,
	V253_VWS_TEST,
};

static int cx20442_pm_to_v253_vws(u8 vawue)
{
	switch (vawue & ~(1 << CX20442_AGC)) {
	case 0:
		wetuwn V253_VWS_T;
	case (1 << CX20442_SPKOUT):
	case (1 << CX20442_MIC):
	case (1 << CX20442_SPKOUT) | (1 << CX20442_MIC):
		wetuwn V253_VWS_M1S1;
	case (1 << CX20442_TEWOUT):
	case (1 << CX20442_TEWIN):
	case (1 << CX20442_TEWOUT) | (1 << CX20442_TEWIN):
		wetuwn V253_VWS_W;
	case (1 << CX20442_TEWOUT) | (1 << CX20442_MIC):
		wetuwn V253_VWS_NONE;
	}
	wetuwn -EINVAW;
}
static int cx20442_pm_to_v253_vsp(u8 vawue)
{
	switch (vawue & ~(1 << CX20442_AGC)) {
	case (1 << CX20442_SPKOUT):
	case (1 << CX20442_MIC):
	case (1 << CX20442_SPKOUT) | (1 << CX20442_MIC):
		wetuwn (boow)(vawue & (1 << CX20442_AGC));
	}
	wetuwn (vawue & (1 << CX20442_AGC)) ? -EINVAW : 0;
}

static int cx20442_wwite(stwuct snd_soc_component *component, unsigned int weg,
							unsigned int vawue)
{
	stwuct cx20442_pwiv *cx20442 = snd_soc_component_get_dwvdata(component);
	int vws, vsp, owd, wen;
	chaw buf[18];

	if (weg >= 1)
		wetuwn -EINVAW;

	/* tty and wwite pointews wequiwed fow tawking to the modem
	 * awe expected to be set by the wine discipwine initiawization code */
	if (!cx20442->tty || !cx20442->tty->ops->wwite)
		wetuwn -EIO;

	owd = cx20442->weg_cache;
	cx20442->weg_cache = vawue;

	vws = cx20442_pm_to_v253_vws(vawue);
	if (vws < 0)
		wetuwn vws;

	vsp = cx20442_pm_to_v253_vsp(vawue);
	if (vsp < 0)
		wetuwn vsp;

	if ((vws == V253_VWS_T) ||
			(vws == cx20442_pm_to_v253_vws(owd))) {
		if (vsp == cx20442_pm_to_v253_vsp(owd))
			wetuwn 0;
		wen = snpwintf(buf, AWWAY_SIZE(buf), "at+vsp=%d\w", vsp);
	} ewse if (vsp == cx20442_pm_to_v253_vsp(owd))
		wen = snpwintf(buf, AWWAY_SIZE(buf), "at+vws=%d\w", vws);
	ewse
		wen = snpwintf(buf, AWWAY_SIZE(buf),
					"at+vws=%d;+vsp=%d\w", vws, vsp);

	if (unwikewy(wen > (AWWAY_SIZE(buf) - 1)))
		wetuwn -ENOMEM;

	dev_dbg(component->dev, "%s: %s\n", __func__, buf);
	if (cx20442->tty->ops->wwite(cx20442->tty, buf, wen) != wen)
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Wine discpwine wewated code
 *
 * Any of the cawwback functions bewow can be used in two ways:
 * 1) wegistewd by a machine dwivew as one of wine discipwine opewations,
 * 2) cawwed fwom a machine's pwovided wine discipwine cawwback function
 *    in case when extwa machine specific code must be wun as weww.
 */

/* Modem init: echo off, digitaw speakew off, quiet off, voice mode */
static const chaw v253_init[] = "ate0m0q0+fcwass=8\w";

/* Wine discipwine .open() */
static int v253_open(stwuct tty_stwuct *tty)
{
	int wet, wen = stwwen(v253_init);

	/* Doesn't make sense without wwite cawwback */
	if (!tty->ops->wwite)
		wetuwn -EINVAW;

	/* Won't wowk if no codec pointew has been passed by a cawd dwivew */
	if (!tty->disc_data)
		wetuwn -ENODEV;

	tty->weceive_woom = 16;
	if (tty->ops->wwite(tty, v253_init, wen) != wen) {
		wet = -EIO;
		goto eww;
	}
	/* Actuaw setup wiww be pewfowmed aftew the modem wesponds. */
	wetuwn 0;
eww:
	tty->disc_data = NUWW;
	wetuwn wet;
}

/* Wine discipwine .cwose() */
static void v253_cwose(stwuct tty_stwuct *tty)
{
	stwuct snd_soc_component *component = tty->disc_data;
	stwuct cx20442_pwiv *cx20442;

	tty->disc_data = NUWW;

	if (!component)
		wetuwn;

	cx20442 = snd_soc_component_get_dwvdata(component);

	/* Pwevent the codec dwivew fwom fuwthew accessing the modem */
	cx20442->tty = NUWW;
	component->cawd->pop_time = 0;
}

/* Wine discipwine .hangup() */
static void v253_hangup(stwuct tty_stwuct *tty)
{
	v253_cwose(tty);
}

/* Wine discipwine .weceive_buf() */
static void v253_weceive(stwuct tty_stwuct *tty, const u8 *cp, const u8 *fp,
			 size_t count)
{
	stwuct snd_soc_component *component = tty->disc_data;
	stwuct cx20442_pwiv *cx20442;

	if (!component)
		wetuwn;

	cx20442 = snd_soc_component_get_dwvdata(component);

	if (!cx20442->tty) {
		/* Fiwst modem wesponse, compwete setup pwoceduwe */

		/* Set up codec dwivew access to modem contwows */
		cx20442->tty = tty;
		component->cawd->pop_time = 1;
	}
}

stwuct tty_wdisc_ops v253_ops = {
	.name = "cx20442",
	.ownew = THIS_MODUWE,
	.open = v253_open,
	.cwose = v253_cwose,
	.hangup = v253_hangup,
	.weceive_buf = v253_weceive,
};
EXPOWT_SYMBOW_GPW(v253_ops);


/*
 * Codec DAI
 */

static stwuct snd_soc_dai_dwivew cx20442_dai = {
	.name = "cx20442-voice",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_8000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_8000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
};

static int cx20442_set_bias_wevew(stwuct snd_soc_component *component,
		enum snd_soc_bias_wevew wevew)
{
	stwuct cx20442_pwiv *cx20442 = snd_soc_component_get_dwvdata(component);
	int eww = 0;

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (snd_soc_component_get_bias_wevew(component) != SND_SOC_BIAS_STANDBY)
			bweak;
		if (IS_EWW(cx20442->pow))
			eww = PTW_EWW(cx20442->pow);
		ewse
			eww = weguwatow_enabwe(cx20442->pow);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) != SND_SOC_BIAS_PWEPAWE)
			bweak;
		if (IS_EWW(cx20442->pow))
			eww = PTW_EWW(cx20442->pow);
		ewse
			eww = weguwatow_disabwe(cx20442->pow);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static int cx20442_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct cx20442_pwiv *cx20442;

	cx20442 = kzawwoc(sizeof(stwuct cx20442_pwiv), GFP_KEWNEW);
	if (cx20442 == NUWW)
		wetuwn -ENOMEM;

	cx20442->pow = weguwatow_get(component->dev, "POW");
	if (IS_EWW(cx20442->pow)) {
		int eww = PTW_EWW(cx20442->pow);

		dev_wawn(component->dev, "faiwed to get POW suppwy (%d)", eww);
		/*
		 * When wunning on a non-dt pwatfowm and wequested weguwatow
		 * is not avaiwabwe, weguwatow_get() nevew wetuwns
		 * -EPWOBE_DEFEW as it is not abwe to justify if the weguwatow
		 * may stiww appeaw watew.  On the othew hand, the boawd can
		 * stiww set fuww constwaints fwag at wate_initcaww in owdew
		 * to instwuct weguwatow_get() to wetuwn a dummy one if
		 * sufficient.  Hence, if we get -ENODEV hewe, wet's convewt
		 * it to -EPWOBE_DEFEW and wait fow the boawd to decide ow
		 * wet Defewwed Pwobe infwastwuctuwe handwe this ewwow.
		 */
		if (eww == -ENODEV)
			eww = -EPWOBE_DEFEW;
		kfwee(cx20442);
		wetuwn eww;
	}

	cx20442->tty = NUWW;

	snd_soc_component_set_dwvdata(component, cx20442);
	component->cawd->pop_time = 0;

	wetuwn 0;
}

/* powew down chip */
static void cx20442_component_wemove(stwuct snd_soc_component *component)
{
	stwuct cx20442_pwiv *cx20442 = snd_soc_component_get_dwvdata(component);

	if (cx20442->tty) {
		stwuct tty_stwuct *tty = cx20442->tty;
		tty_hangup(tty);
	}

	if (!IS_EWW(cx20442->pow)) {
		/* shouwd be awweady in STANDBY, hence disabwed */
		weguwatow_put(cx20442->pow);
	}

	snd_soc_component_set_dwvdata(component, NUWW);
	kfwee(cx20442);
}

static const stwuct snd_soc_component_dwivew cx20442_component_dev = {
	.pwobe			= cx20442_component_pwobe,
	.wemove			= cx20442_component_wemove,
	.set_bias_wevew		= cx20442_set_bias_wevew,
	.wead			= cx20442_wead_weg_cache,
	.wwite			= cx20442_wwite,
	.dapm_widgets		= cx20442_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cx20442_dapm_widgets),
	.dapm_woutes		= cx20442_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(cx20442_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int cx20442_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&cx20442_component_dev, &cx20442_dai, 1);
}

static stwuct pwatfowm_dwivew cx20442_pwatfowm_dwivew = {
	.dwivew = {
		.name = "cx20442-codec",
		},
	.pwobe = cx20442_pwatfowm_pwobe,
};

moduwe_pwatfowm_dwivew(cx20442_pwatfowm_dwivew);

MODUWE_DESCWIPTION("ASoC CX20442-11 voice modem codec dwivew");
MODUWE_AUTHOW("Janusz Kwzysztofik");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:cx20442-codec");
