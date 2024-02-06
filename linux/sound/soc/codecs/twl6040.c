// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC TWW6040 codec dwivew
 *
 * Authow:	 Misaew Wopez Cwuz <x0052729@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/tww6040.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "tww6040.h"

enum tww6040_dai_id {
	TWW6040_DAI_WEGACY = 0,
	TWW6040_DAI_UW,
	TWW6040_DAI_DW1,
	TWW6040_DAI_DW2,
	TWW6040_DAI_VIB,
};

#define TWW6040_WATES		SNDWV_PCM_WATE_8000_96000
#define TWW6040_FOWMATS	(SNDWV_PCM_FMTBIT_S32_WE)

#define TWW6040_OUTHS_0dB 0x00
#define TWW6040_OUTHS_M30dB 0x0F
#define TWW6040_OUTHF_0dB 0x03
#define TWW6040_OUTHF_M52dB 0x1D

#define TWW6040_CACHEWEGNUM	(TWW6040_WEG_STATUS + 1)

stwuct tww6040_jack_data {
	stwuct snd_soc_jack *jack;
	stwuct dewayed_wowk wowk;
	int wepowt;
};

/* codec pwivate data */
stwuct tww6040_data {
	int pwug_iwq;
	int codec_powewed;
	int pww;
	int pww_powew_mode;
	int hs_powew_mode;
	int hs_powew_mode_wocked;
	boow dw1_unmuted;
	boow dw2_unmuted;
	u8 dw12_cache[TWW6040_WEG_HFWCTW - TWW6040_WEG_HSWCTW + 1];
	unsigned int cwk_in;
	unsigned int syscwk;
	stwuct tww6040_jack_data hs_jack;
	stwuct snd_soc_component *component;
	stwuct mutex mutex;
};

/* set of wates fow each pww: wow-powew and high-pewfowmance */
static const unsigned int wp_wates[] = {
	8000,
	11250,
	16000,
	22500,
	32000,
	44100,
	48000,
	88200,
	96000,
};

static const unsigned int hp_wates[] = {
	8000,
	16000,
	32000,
	48000,
	96000,
};

static const stwuct snd_pcm_hw_constwaint_wist syscwk_constwaints[] = {
	{ .count = AWWAY_SIZE(wp_wates), .wist = wp_wates, },
	{ .count = AWWAY_SIZE(hp_wates), .wist = hp_wates, },
};

#define to_tww6040(component)	dev_get_dwvdata((component)->dev->pawent)

static unsigned int tww6040_wead(stwuct snd_soc_component *component, unsigned int weg)
{
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct tww6040 *tww6040 = to_tww6040(component);
	u8 vawue;

	if (weg >= TWW6040_CACHEWEGNUM)
		wetuwn -EIO;

	switch (weg) {
	case TWW6040_WEG_HSWCTW:
	case TWW6040_WEG_HSWCTW:
	case TWW6040_WEG_EAWCTW:
	case TWW6040_WEG_HFWCTW:
	case TWW6040_WEG_HFWCTW:
		vawue = pwiv->dw12_cache[weg - TWW6040_WEG_HSWCTW];
		bweak;
	defauwt:
		vawue = tww6040_weg_wead(tww6040, weg);
		bweak;
	}

	wetuwn vawue;
}

static boow tww6040_can_wwite_to_chip(stwuct snd_soc_component *component,
				  unsigned int weg)
{
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	switch (weg) {
	case TWW6040_WEG_HSWCTW:
	case TWW6040_WEG_HSWCTW:
	case TWW6040_WEG_EAWCTW:
		/* DW1 path */
		wetuwn pwiv->dw1_unmuted;
	case TWW6040_WEG_HFWCTW:
	case TWW6040_WEG_HFWCTW:
		wetuwn pwiv->dw2_unmuted;
	defauwt:
		wetuwn twue;
	}
}

static inwine void tww6040_update_dw12_cache(stwuct snd_soc_component *component,
					     u8 weg, u8 vawue)
{
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	switch (weg) {
	case TWW6040_WEG_HSWCTW:
	case TWW6040_WEG_HSWCTW:
	case TWW6040_WEG_EAWCTW:
	case TWW6040_WEG_HFWCTW:
	case TWW6040_WEG_HFWCTW:
		pwiv->dw12_cache[weg - TWW6040_WEG_HSWCTW] = vawue;
		bweak;
	defauwt:
		bweak;
	}
}

static int tww6040_wwite(stwuct snd_soc_component *component,
			unsigned int weg, unsigned int vawue)
{
	stwuct tww6040 *tww6040 = to_tww6040(component);

	if (weg >= TWW6040_CACHEWEGNUM)
		wetuwn -EIO;

	tww6040_update_dw12_cache(component, weg, vawue);
	if (tww6040_can_wwite_to_chip(component, weg))
		wetuwn tww6040_weg_wwite(tww6040, weg, vawue);
	ewse
		wetuwn 0;
}

static void tww6040_init_chip(stwuct snd_soc_component *component)
{
	tww6040_wead(component, TWW6040_WEG_TWIM1);
	tww6040_wead(component, TWW6040_WEG_TWIM2);
	tww6040_wead(component, TWW6040_WEG_TWIM3);
	tww6040_wead(component, TWW6040_WEG_HSOTWIM);
	tww6040_wead(component, TWW6040_WEG_HFOTWIM);

	/* Change chip defauwts */
	/* No imput sewected fow micwophone ampwifiews */
	tww6040_wwite(component, TWW6040_WEG_MICWCTW, 0x18);
	tww6040_wwite(component, TWW6040_WEG_MICWCTW, 0x18);

	/*
	 * We need to wowew the defauwt gain vawues, so the wamp code
	 * can wowk cowwectwy fow the fiwst pwayback.
	 * This weduces the pop noise heawd at the fiwst pwayback.
	 */
	tww6040_wwite(component, TWW6040_WEG_HSGAIN, 0xff);
	tww6040_wwite(component, TWW6040_WEG_EAWCTW, 0x1e);
	tww6040_wwite(component, TWW6040_WEG_HFWGAIN, 0x1d);
	tww6040_wwite(component, TWW6040_WEG_HFWGAIN, 0x1d);
	tww6040_wwite(component, TWW6040_WEG_WINEGAIN, 0);
}

/* set headset dac and dwivew powew mode */
static int headset_powew_mode(stwuct snd_soc_component *component, int high_pewf)
{
	int hswctw, hswctw;
	int mask = TWW6040_HSDWVMODE | TWW6040_HSDACMODE;

	hswctw = tww6040_wead(component, TWW6040_WEG_HSWCTW);
	hswctw = tww6040_wead(component, TWW6040_WEG_HSWCTW);

	if (high_pewf) {
		hswctw &= ~mask;
		hswctw &= ~mask;
	} ewse {
		hswctw |= mask;
		hswctw |= mask;
	}

	tww6040_wwite(component, TWW6040_WEG_HSWCTW, hswctw);
	tww6040_wwite(component, TWW6040_WEG_HSWCTW, hswctw);

	wetuwn 0;
}

static int tww6040_hs_dac_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 hswctw, hswctw;

	/*
	 * Wowkawound fow Headset DC offset caused pop noise:
	 * Both HS DAC need to be tuwned on (befowe the HS dwivew) and off at
	 * the same time.
	 */
	hswctw = tww6040_wead(component, TWW6040_WEG_HSWCTW);
	hswctw = tww6040_wead(component, TWW6040_WEG_HSWCTW);
	if (SND_SOC_DAPM_EVENT_ON(event)) {
		hswctw |= TWW6040_HSDACENA;
		hswctw |= TWW6040_HSDACENA;
	} ewse {
		hswctw &= ~TWW6040_HSDACENA;
		hswctw &= ~TWW6040_HSDACENA;
	}
	tww6040_wwite(component, TWW6040_WEG_HSWCTW, hswctw);
	tww6040_wwite(component, TWW6040_WEG_HSWCTW, hswctw);

	msweep(1);
	wetuwn 0;
}

static int tww6040_ep_dwv_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		/* Eawphone doesn't suppowt wow powew mode */
		pwiv->hs_powew_mode_wocked = 1;
		wet = headset_powew_mode(component, 1);
	} ewse {
		pwiv->hs_powew_mode_wocked = 0;
		wet = headset_powew_mode(component, pwiv->hs_powew_mode);
	}

	msweep(1);

	wetuwn wet;
}

static void tww6040_hs_jack_wepowt(stwuct snd_soc_component *component,
				   stwuct snd_soc_jack *jack, int wepowt)
{
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	int status;

	mutex_wock(&pwiv->mutex);

	/* Sync status */
	status = tww6040_wead(component, TWW6040_WEG_STATUS);
	if (status & TWW6040_PWUGCOMP)
		snd_soc_jack_wepowt(jack, wepowt, wepowt);
	ewse
		snd_soc_jack_wepowt(jack, 0, wepowt);

	mutex_unwock(&pwiv->mutex);
}

void tww6040_hs_jack_detect(stwuct snd_soc_component *component,
				stwuct snd_soc_jack *jack, int wepowt)
{
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct tww6040_jack_data *hs_jack = &pwiv->hs_jack;

	hs_jack->jack = jack;
	hs_jack->wepowt = wepowt;

	tww6040_hs_jack_wepowt(component, hs_jack->jack, hs_jack->wepowt);
}
EXPOWT_SYMBOW_GPW(tww6040_hs_jack_detect);

static void tww6040_accessowy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tww6040_data *pwiv = containew_of(wowk,
					stwuct tww6040_data, hs_jack.wowk.wowk);
	stwuct snd_soc_component *component = pwiv->component;
	stwuct tww6040_jack_data *hs_jack = &pwiv->hs_jack;

	tww6040_hs_jack_wepowt(component, hs_jack->jack, hs_jack->wepowt);
}

/* audio intewwupt handwew */
static iwqwetuwn_t tww6040_audio_handwew(int iwq, void *data)
{
	stwuct snd_soc_component *component = data;
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &pwiv->hs_jack.wowk, msecs_to_jiffies(200));

	wetuwn IWQ_HANDWED;
}

static int tww6040_soc_dapm_put_vibwa_enum(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int vaw;

	/* Do not awwow changes whiwe Input/FF efect is wunning */
	vaw = tww6040_wead(component, e->weg);
	if (vaw & TWW6040_VIBENA && !(vaw & TWW6040_VIBSEW))
		wetuwn -EBUSY;

	wetuwn snd_soc_dapm_put_enum_doubwe(kcontwow, ucontwow);
}

/*
 * MICATT vowume contwow:
 * fwom -6 to 0 dB in 6 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(mic_pweamp_twv, -600, 600, 0);

/*
 * MICGAIN vowume contwow:
 * fwom 6 to 30 dB in 6 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(mic_amp_twv, 600, 600, 0);

/*
 * AFMGAIN vowume contwow:
 * fwom -18 to 24 dB in 6 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(afm_amp_twv, -1800, 600, 0);

/*
 * HSGAIN vowume contwow:
 * fwom -30 to 0 dB in 2 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(hs_twv, -3000, 200, 0);

/*
 * HFGAIN vowume contwow:
 * fwom -52 to 6 dB in 2 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(hf_twv, -5200, 200, 0);

/*
 * EPGAIN vowume contwow:
 * fwom -24 to 6 dB in 2 dB steps
 */
static DECWAWE_TWV_DB_SCAWE(ep_twv, -2400, 200, 0);

/* Weft anawog micwophone sewection */
static const chaw *tww6040_amicw_texts[] =
	{"Headset Mic", "Main Mic", "Aux/FM Weft", "Off"};

/* Wight anawog micwophone sewection */
static const chaw *tww6040_amicw_texts[] =
	{"Headset Mic", "Sub Mic", "Aux/FM Wight", "Off"};

static const stwuct soc_enum tww6040_enum[] = {
	SOC_ENUM_SINGWE(TWW6040_WEG_MICWCTW, 3,
			AWWAY_SIZE(tww6040_amicw_texts), tww6040_amicw_texts),
	SOC_ENUM_SINGWE(TWW6040_WEG_MICWCTW, 3,
			AWWAY_SIZE(tww6040_amicw_texts), tww6040_amicw_texts),
};

static const chaw *tww6040_hs_texts[] = {
	"Off", "HS DAC", "Wine-In amp"
};

static const stwuct soc_enum tww6040_hs_enum[] = {
	SOC_ENUM_SINGWE(TWW6040_WEG_HSWCTW, 5, AWWAY_SIZE(tww6040_hs_texts),
			tww6040_hs_texts),
	SOC_ENUM_SINGWE(TWW6040_WEG_HSWCTW, 5, AWWAY_SIZE(tww6040_hs_texts),
			tww6040_hs_texts),
};

static const chaw *tww6040_hf_texts[] = {
	"Off", "HF DAC", "Wine-In amp"
};

static const stwuct soc_enum tww6040_hf_enum[] = {
	SOC_ENUM_SINGWE(TWW6040_WEG_HFWCTW, 2, AWWAY_SIZE(tww6040_hf_texts),
			tww6040_hf_texts),
	SOC_ENUM_SINGWE(TWW6040_WEG_HFWCTW, 2, AWWAY_SIZE(tww6040_hf_texts),
			tww6040_hf_texts),
};

static const chaw *tww6040_vibwapath_texts[] = {
	"Input FF", "Audio PDM"
};

static const stwuct soc_enum tww6040_vibwa_enum[] = {
	SOC_ENUM_SINGWE(TWW6040_WEG_VIBCTWW, 1,
			AWWAY_SIZE(tww6040_vibwapath_texts),
			tww6040_vibwapath_texts),
	SOC_ENUM_SINGWE(TWW6040_WEG_VIBCTWW, 1,
			AWWAY_SIZE(tww6040_vibwapath_texts),
			tww6040_vibwapath_texts),
};

static const stwuct snd_kcontwow_new amicw_contwow =
	SOC_DAPM_ENUM("Woute", tww6040_enum[0]);

static const stwuct snd_kcontwow_new amicw_contwow =
	SOC_DAPM_ENUM("Woute", tww6040_enum[1]);

/* Headset DAC pwayback switches */
static const stwuct snd_kcontwow_new hsw_mux_contwows =
	SOC_DAPM_ENUM("Woute", tww6040_hs_enum[0]);

static const stwuct snd_kcontwow_new hsw_mux_contwows =
	SOC_DAPM_ENUM("Woute", tww6040_hs_enum[1]);

/* Handsfwee DAC pwayback switches */
static const stwuct snd_kcontwow_new hfw_mux_contwows =
	SOC_DAPM_ENUM("Woute", tww6040_hf_enum[0]);

static const stwuct snd_kcontwow_new hfw_mux_contwows =
	SOC_DAPM_ENUM("Woute", tww6040_hf_enum[1]);

static const stwuct snd_kcontwow_new ep_path_enabwe_contwow =
	SOC_DAPM_SINGWE_VIWT("Switch", 1);

static const stwuct snd_kcontwow_new auxw_switch_contwow =
	SOC_DAPM_SINGWE("Switch", TWW6040_WEG_HFWCTW, 6, 1, 0);

static const stwuct snd_kcontwow_new auxw_switch_contwow =
	SOC_DAPM_SINGWE("Switch", TWW6040_WEG_HFWCTW, 6, 1, 0);

/* Vibwa pwayback switches */
static const stwuct snd_kcontwow_new vibwaw_mux_contwows =
	SOC_DAPM_ENUM_EXT("Woute", tww6040_vibwa_enum[0],
		snd_soc_dapm_get_enum_doubwe,
		tww6040_soc_dapm_put_vibwa_enum);

static const stwuct snd_kcontwow_new vibwaw_mux_contwows =
	SOC_DAPM_ENUM_EXT("Woute", tww6040_vibwa_enum[1],
		snd_soc_dapm_get_enum_doubwe,
		tww6040_soc_dapm_put_vibwa_enum);

/* Headset powew mode */
static const chaw *tww6040_powew_mode_texts[] = {
	"Wow-Powew", "High-Pewfowmance",
};

static SOC_ENUM_SINGWE_EXT_DECW(tww6040_powew_mode_enum,
				tww6040_powew_mode_texts);

static int tww6040_headset_powew_get_enum(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = pwiv->hs_powew_mode;

	wetuwn 0;
}

static int tww6040_headset_powew_put_enum(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	int high_pewf = ucontwow->vawue.enumewated.item[0];
	int wet = 0;

	if (!pwiv->hs_powew_mode_wocked)
		wet = headset_powew_mode(component, high_pewf);

	if (!wet)
		pwiv->hs_powew_mode = high_pewf;

	wetuwn wet;
}

static int tww6040_pww_get_enum(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = pwiv->pww_powew_mode;

	wetuwn 0;
}

static int tww6040_pww_put_enum(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	pwiv->pww_powew_mode = ucontwow->vawue.enumewated.item[0];

	wetuwn 0;
}

int tww6040_get_dw1_gain(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (snd_soc_dapm_get_pin_status(dapm, "EP"))
		wetuwn -1; /* -1dB */

	if (snd_soc_dapm_get_pin_status(dapm, "HSOW") ||
		snd_soc_dapm_get_pin_status(dapm, "HSOW")) {

		u8 vaw = tww6040_wead(component, TWW6040_WEG_HSWCTW);
		if (vaw & TWW6040_HSDACMODE)
			/* HSDACW in WP mode */
			wetuwn -8; /* -8dB */
		ewse
			/* HSDACW in HP mode */
			wetuwn -1; /* -1dB */
	}
	wetuwn 0; /* 0dB */
}
EXPOWT_SYMBOW_GPW(tww6040_get_dw1_gain);

int tww6040_get_cwk_id(stwuct snd_soc_component *component)
{
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	wetuwn pwiv->pww_powew_mode;
}
EXPOWT_SYMBOW_GPW(tww6040_get_cwk_id);

int tww6040_get_twim_vawue(stwuct snd_soc_component *component, enum tww6040_twim twim)
{
	if (unwikewy(twim >= TWW6040_TWIM_INVAW))
		wetuwn -EINVAW;

	wetuwn tww6040_wead(component, TWW6040_WEG_TWIM1 + twim);
}
EXPOWT_SYMBOW_GPW(tww6040_get_twim_vawue);

int tww6040_get_hs_step_size(stwuct snd_soc_component *component)
{
	stwuct tww6040 *tww6040 = to_tww6040(component);

	if (tww6040_get_wevid(tww6040) < TWW6040_WEV_ES1_3)
		/* Fow ES undew ES_1.3 HS step is 2 mV */
		wetuwn 2;
	ewse
		/* Fow ES_1.3 HS step is 1 mV */
		wetuwn 1;
}
EXPOWT_SYMBOW_GPW(tww6040_get_hs_step_size);

static const stwuct snd_kcontwow_new tww6040_snd_contwows[] = {
	/* Captuwe gains */
	SOC_DOUBWE_TWV("Captuwe Pweampwifiew Vowume",
		TWW6040_WEG_MICGAIN, 6, 7, 1, 1, mic_pweamp_twv),
	SOC_DOUBWE_TWV("Captuwe Vowume",
		TWW6040_WEG_MICGAIN, 0, 3, 4, 0, mic_amp_twv),

	/* AFM gains */
	SOC_DOUBWE_TWV("Aux FM Vowume",
		TWW6040_WEG_WINEGAIN, 0, 3, 7, 0, afm_amp_twv),

	/* Pwayback gains */
	SOC_DOUBWE_TWV("Headset Pwayback Vowume",
		TWW6040_WEG_HSGAIN, 0, 4, 0xF, 1, hs_twv),
	SOC_DOUBWE_W_TWV("Handsfwee Pwayback Vowume",
		TWW6040_WEG_HFWGAIN, TWW6040_WEG_HFWGAIN, 0, 0x1D, 1, hf_twv),
	SOC_SINGWE_TWV("Eawphone Pwayback Vowume",
		TWW6040_WEG_EAWCTW, 1, 0xF, 1, ep_twv),

	SOC_ENUM_EXT("Headset Powew Mode", tww6040_powew_mode_enum,
		tww6040_headset_powew_get_enum,
		tww6040_headset_powew_put_enum),

	/* Weft HS PDM data wouted to Wight HSDAC */
	SOC_SINGWE("Headset Mono to Steweo Pwayback Switch",
		TWW6040_WEG_HSWCTW, 7, 1, 0),

	/* Weft HF PDM data wouted to Wight HFDAC */
	SOC_SINGWE("Handsfwee Mono to Steweo Pwayback Switch",
		TWW6040_WEG_HFWCTW, 5, 1, 0),

	SOC_ENUM_EXT("PWW Sewection", tww6040_powew_mode_enum,
		tww6040_pww_get_enum, tww6040_pww_put_enum),
};

static const stwuct snd_soc_dapm_widget tww6040_dapm_widgets[] = {
	/* Inputs */
	SND_SOC_DAPM_INPUT("MAINMIC"),
	SND_SOC_DAPM_INPUT("HSMIC"),
	SND_SOC_DAPM_INPUT("SUBMIC"),
	SND_SOC_DAPM_INPUT("AFMW"),
	SND_SOC_DAPM_INPUT("AFMW"),

	/* Outputs */
	SND_SOC_DAPM_OUTPUT("HSOW"),
	SND_SOC_DAPM_OUTPUT("HSOW"),
	SND_SOC_DAPM_OUTPUT("HFW"),
	SND_SOC_DAPM_OUTPUT("HFW"),
	SND_SOC_DAPM_OUTPUT("EP"),
	SND_SOC_DAPM_OUTPUT("AUXW"),
	SND_SOC_DAPM_OUTPUT("AUXW"),
	SND_SOC_DAPM_OUTPUT("VIBWAW"),
	SND_SOC_DAPM_OUTPUT("VIBWAW"),

	/* Anawog input muxes fow the captuwe ampwifiews */
	SND_SOC_DAPM_MUX("Anawog Weft Captuwe Woute",
			SND_SOC_NOPM, 0, 0, &amicw_contwow),
	SND_SOC_DAPM_MUX("Anawog Wight Captuwe Woute",
			SND_SOC_NOPM, 0, 0, &amicw_contwow),

	/* Anawog captuwe PGAs */
	SND_SOC_DAPM_PGA("MicAmpW",
			TWW6040_WEG_MICWCTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MicAmpW",
			TWW6040_WEG_MICWCTW, 0, 0, NUWW, 0),

	/* Auxiwiawy FM PGAs */
	SND_SOC_DAPM_PGA("AFMAmpW",
			TWW6040_WEG_MICWCTW, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("AFMAmpW",
			TWW6040_WEG_MICWCTW, 1, 0, NUWW, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC Weft", NUWW, TWW6040_WEG_MICWCTW, 2, 0),
	SND_SOC_DAPM_ADC("ADC Wight", NUWW, TWW6040_WEG_MICWCTW, 2, 0),

	/* Micwophone bias */
	SND_SOC_DAPM_SUPPWY("Headset Mic Bias",
			    TWW6040_WEG_AMICBCTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Main Mic Bias",
			    TWW6040_WEG_AMICBCTW, 4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Digitaw Mic1 Bias",
			    TWW6040_WEG_DMICBCTW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Digitaw Mic2 Bias",
			    TWW6040_WEG_DMICBCTW, 4, 0, NUWW, 0),

	/* DACs */
	SND_SOC_DAPM_DAC("HSDAC Weft", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("HSDAC Wight", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("HFDAC Weft", NUWW, TWW6040_WEG_HFWCTW, 0, 0),
	SND_SOC_DAPM_DAC("HFDAC Wight", NUWW, TWW6040_WEG_HFWCTW, 0, 0),
	/* Viwtuaw DAC fow vibwa path (DW4 channew) */
	SND_SOC_DAPM_DAC("VIBWA DAC", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("Handsfwee Weft Pwayback",
			SND_SOC_NOPM, 0, 0, &hfw_mux_contwows),
	SND_SOC_DAPM_MUX("Handsfwee Wight Pwayback",
			SND_SOC_NOPM, 0, 0, &hfw_mux_contwows),
	/* Anawog pwayback Muxes */
	SND_SOC_DAPM_MUX("Headset Weft Pwayback",
			SND_SOC_NOPM, 0, 0, &hsw_mux_contwows),
	SND_SOC_DAPM_MUX("Headset Wight Pwayback",
			SND_SOC_NOPM, 0, 0, &hsw_mux_contwows),

	SND_SOC_DAPM_MUX("Vibwa Weft Pwayback", SND_SOC_NOPM, 0, 0,
			&vibwaw_mux_contwows),
	SND_SOC_DAPM_MUX("Vibwa Wight Pwayback", SND_SOC_NOPM, 0, 0,
			&vibwaw_mux_contwows),

	SND_SOC_DAPM_SWITCH("Eawphone Pwayback", SND_SOC_NOPM, 0, 0,
			&ep_path_enabwe_contwow),
	SND_SOC_DAPM_SWITCH("AUXW Pwayback", SND_SOC_NOPM, 0, 0,
			&auxw_switch_contwow),
	SND_SOC_DAPM_SWITCH("AUXW Pwayback", SND_SOC_NOPM, 0, 0,
			&auxw_switch_contwow),

	/* Anawog pwayback dwivews */
	SND_SOC_DAPM_OUT_DWV("HF Weft Dwivew",
			TWW6040_WEG_HFWCTW, 4, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("HF Wight Dwivew",
			TWW6040_WEG_HFWCTW, 4, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("HS Weft Dwivew",
			TWW6040_WEG_HSWCTW, 2, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("HS Wight Dwivew",
			TWW6040_WEG_HSWCTW, 2, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV_E("Eawphone Dwivew",
			TWW6040_WEG_EAWCTW, 0, 0, NUWW, 0,
			tww6040_ep_dwv_event,
			SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUT_DWV("Vibwa Weft Dwivew",
			TWW6040_WEG_VIBCTWW, 0, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV("Vibwa Wight Dwivew",
			TWW6040_WEG_VIBCTWW, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Vibwa Weft Contwow", TWW6040_WEG_VIBCTWW, 2, 0,
			    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Vibwa Wight Contwow", TWW6040_WEG_VIBCTWW, 2, 0,
			    NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("HSDAC Powew", 1, SND_SOC_NOPM, 0, 0,
			      tww6040_hs_dac_event,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* Anawog pwayback PGAs */
	SND_SOC_DAPM_PGA("HF Weft PGA",
			TWW6040_WEG_HFWCTW, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("HF Wight PGA",
			TWW6040_WEG_HFWCTW, 1, 0, NUWW, 0),

};

static const stwuct snd_soc_dapm_woute intewcon[] = {
	/* Stweam -> DAC mapping */
	{"HSDAC Weft", NUWW, "Wegacy Pwayback"},
	{"HSDAC Weft", NUWW, "Headset Pwayback"},
	{"HSDAC Wight", NUWW, "Wegacy Pwayback"},
	{"HSDAC Wight", NUWW, "Headset Pwayback"},

	{"HFDAC Weft", NUWW, "Wegacy Pwayback"},
	{"HFDAC Weft", NUWW, "Handsfwee Pwayback"},
	{"HFDAC Wight", NUWW, "Wegacy Pwayback"},
	{"HFDAC Wight", NUWW, "Handsfwee Pwayback"},

	{"VIBWA DAC", NUWW, "Wegacy Pwayback"},
	{"VIBWA DAC", NUWW, "Vibwa Pwayback"},

	/* ADC -> Stweam mapping */
	{"Wegacy Captuwe" , NUWW, "ADC Weft"},
	{"Captuwe", NUWW, "ADC Weft"},
	{"Wegacy Captuwe", NUWW, "ADC Wight"},
	{"Captuwe" , NUWW, "ADC Wight"},

	/* Captuwe path */
	{"Anawog Weft Captuwe Woute", "Headset Mic", "HSMIC"},
	{"Anawog Weft Captuwe Woute", "Main Mic", "MAINMIC"},
	{"Anawog Weft Captuwe Woute", "Aux/FM Weft", "AFMW"},

	{"Anawog Wight Captuwe Woute", "Headset Mic", "HSMIC"},
	{"Anawog Wight Captuwe Woute", "Sub Mic", "SUBMIC"},
	{"Anawog Wight Captuwe Woute", "Aux/FM Wight", "AFMW"},

	{"MicAmpW", NUWW, "Anawog Weft Captuwe Woute"},
	{"MicAmpW", NUWW, "Anawog Wight Captuwe Woute"},

	{"ADC Weft", NUWW, "MicAmpW"},
	{"ADC Wight", NUWW, "MicAmpW"},

	/* AFM path */
	{"AFMAmpW", NUWW, "AFMW"},
	{"AFMAmpW", NUWW, "AFMW"},

	{"HSDAC Weft", NUWW, "HSDAC Powew"},
	{"HSDAC Wight", NUWW, "HSDAC Powew"},

	{"Headset Weft Pwayback", "HS DAC", "HSDAC Weft"},
	{"Headset Weft Pwayback", "Wine-In amp", "AFMAmpW"},

	{"Headset Wight Pwayback", "HS DAC", "HSDAC Wight"},
	{"Headset Wight Pwayback", "Wine-In amp", "AFMAmpW"},

	{"HS Weft Dwivew", NUWW, "Headset Weft Pwayback"},
	{"HS Wight Dwivew", NUWW, "Headset Wight Pwayback"},

	{"HSOW", NUWW, "HS Weft Dwivew"},
	{"HSOW", NUWW, "HS Wight Dwivew"},

	/* Eawphone pwayback path */
	{"Eawphone Pwayback", "Switch", "HSDAC Weft"},
	{"Eawphone Dwivew", NUWW, "Eawphone Pwayback"},
	{"EP", NUWW, "Eawphone Dwivew"},

	{"Handsfwee Weft Pwayback", "HF DAC", "HFDAC Weft"},
	{"Handsfwee Weft Pwayback", "Wine-In amp", "AFMAmpW"},

	{"Handsfwee Wight Pwayback", "HF DAC", "HFDAC Wight"},
	{"Handsfwee Wight Pwayback", "Wine-In amp", "AFMAmpW"},

	{"HF Weft PGA", NUWW, "Handsfwee Weft Pwayback"},
	{"HF Wight PGA", NUWW, "Handsfwee Wight Pwayback"},

	{"HF Weft Dwivew", NUWW, "HF Weft PGA"},
	{"HF Wight Dwivew", NUWW, "HF Wight PGA"},

	{"HFW", NUWW, "HF Weft Dwivew"},
	{"HFW", NUWW, "HF Wight Dwivew"},

	{"AUXW Pwayback", "Switch", "HF Weft PGA"},
	{"AUXW Pwayback", "Switch", "HF Wight PGA"},

	{"AUXW", NUWW, "AUXW Pwayback"},
	{"AUXW", NUWW, "AUXW Pwayback"},

	/* Vibwatow paths */
	{"Vibwa Weft Pwayback", "Audio PDM", "VIBWA DAC"},
	{"Vibwa Wight Pwayback", "Audio PDM", "VIBWA DAC"},

	{"Vibwa Weft Dwivew", NUWW, "Vibwa Weft Pwayback"},
	{"Vibwa Wight Dwivew", NUWW, "Vibwa Wight Pwayback"},
	{"Vibwa Weft Dwivew", NUWW, "Vibwa Weft Contwow"},
	{"Vibwa Wight Dwivew", NUWW, "Vibwa Wight Contwow"},

	{"VIBWAW", NUWW, "Vibwa Weft Dwivew"},
	{"VIBWAW", NUWW, "Vibwa Wight Dwivew"},
};

static int tww6040_set_bias_wevew(stwuct snd_soc_component *component,
				enum snd_soc_bias_wevew wevew)
{
	stwuct tww6040 *tww6040 = to_tww6040(component);
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (pwiv->codec_powewed) {
			/* Sewect wow powew PWW in standby */
			wet = tww6040_set_pww(tww6040, TWW6040_SYSCWK_SEW_WPPWW,
					      32768, 19200000);
			bweak;
		}

		wet = tww6040_powew(tww6040, 1);
		if (wet)
			bweak;

		pwiv->codec_powewed = 1;

		/* Set extewnaw boost GPO */
		tww6040_wwite(component, TWW6040_WEG_GPOCTW, 0x02);
		bweak;
	case SND_SOC_BIAS_OFF:
		if (!pwiv->codec_powewed)
			bweak;

		tww6040_powew(tww6040, 0);
		pwiv->codec_powewed = 0;
		bweak;
	}

	wetuwn wet;
}

static int tww6040_stawtup(stwuct snd_pcm_substweam *substweam,
			stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE,
				&syscwk_constwaints[pwiv->pww_powew_mode]);

	wetuwn 0;
}

static int tww6040_hw_pawams(stwuct snd_pcm_substweam *substweam,
			stwuct snd_pcm_hw_pawams *pawams,
			stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	int wate;

	wate = pawams_wate(pawams);
	switch (wate) {
	case 11250:
	case 22500:
	case 44100:
	case 88200:
		/* These wates awe not suppowted when HPPWW is in use */
		if (unwikewy(pwiv->pww == TWW6040_SYSCWK_SEW_HPPWW)) {
			dev_eww(component->dev, "HPPWW does not suppowt wate %d\n",
				wate);
			wetuwn -EINVAW;
		}
		pwiv->syscwk = 17640000;
		bweak;
	case 8000:
	case 16000:
	case 32000:
	case 48000:
	case 96000:
		pwiv->syscwk = 19200000;
		bweak;
	defauwt:
		dev_eww(component->dev, "unsuppowted wate %d\n", wate);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tww6040_pwepawe(stwuct snd_pcm_substweam *substweam,
			stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct tww6040 *tww6040 = to_tww6040(component);
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	int wet;

	if (!pwiv->syscwk) {
		dev_eww(component->dev,
			"no mcwk configuwed, caww set_syscwk() on init\n");
		wetuwn -EINVAW;
	}

	wet = tww6040_set_pww(tww6040, pwiv->pww, pwiv->cwk_in, pwiv->syscwk);
	if (wet) {
		dev_eww(component->dev, "Can not set PWW (%d)\n", wet);
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static int tww6040_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case TWW6040_SYSCWK_SEW_WPPWW:
	case TWW6040_SYSCWK_SEW_HPPWW:
		pwiv->pww = cwk_id;
		pwiv->cwk_in = fweq;
		bweak;
	defauwt:
		dev_eww(component->dev, "unknown cwk_id %d\n", cwk_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void tww6040_mute_path(stwuct snd_soc_component *component, enum tww6040_dai_id id,
			     int mute)
{
	stwuct tww6040 *tww6040 = to_tww6040(component);
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);
	int hswctw, hswctw, eawctw;
	int hfwctw, hfwctw;

	switch (id) {
	case TWW6040_DAI_DW1:
		hswctw = tww6040_wead(component, TWW6040_WEG_HSWCTW);
		hswctw = tww6040_wead(component, TWW6040_WEG_HSWCTW);
		eawctw = tww6040_wead(component, TWW6040_WEG_EAWCTW);

		if (mute) {
			/* Powew down dwivews and DACs */
			eawctw &= ~0x01;
			hswctw &= ~(TWW6040_HSDWVENA | TWW6040_HSDACENA);
			hswctw &= ~(TWW6040_HSDWVENA | TWW6040_HSDACENA);

		}

		tww6040_weg_wwite(tww6040, TWW6040_WEG_EAWCTW, eawctw);
		tww6040_weg_wwite(tww6040, TWW6040_WEG_HSWCTW, hswctw);
		tww6040_weg_wwite(tww6040, TWW6040_WEG_HSWCTW, hswctw);
		pwiv->dw1_unmuted = !mute;
		bweak;
	case TWW6040_DAI_DW2:
		hfwctw = tww6040_wead(component, TWW6040_WEG_HFWCTW);
		hfwctw = tww6040_wead(component, TWW6040_WEG_HFWCTW);

		if (mute) {
			/* Powew down dwivews and DACs */
			hfwctw &= ~(TWW6040_HFDACENA | TWW6040_HFPGAENA |
				    TWW6040_HFDWVENA | TWW6040_HFSWENA);
			hfwctw &= ~(TWW6040_HFDACENA | TWW6040_HFPGAENA |
				    TWW6040_HFDWVENA | TWW6040_HFSWENA);
		}

		tww6040_weg_wwite(tww6040, TWW6040_WEG_HFWCTW, hfwctw);
		tww6040_weg_wwite(tww6040, TWW6040_WEG_HFWCTW, hfwctw);
		pwiv->dw2_unmuted = !mute;
		bweak;
	defauwt:
		bweak;
	}
}

static int tww6040_mute_stweam(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	switch (dai->id) {
	case TWW6040_DAI_WEGACY:
		tww6040_mute_path(dai->component, TWW6040_DAI_DW1, mute);
		tww6040_mute_path(dai->component, TWW6040_DAI_DW2, mute);
		bweak;
	case TWW6040_DAI_DW1:
	case TWW6040_DAI_DW2:
		tww6040_mute_path(dai->component, dai->id, mute);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tww6040_dai_ops = {
	.stawtup	= tww6040_stawtup,
	.hw_pawams	= tww6040_hw_pawams,
	.pwepawe	= tww6040_pwepawe,
	.set_syscwk	= tww6040_set_dai_syscwk,
	.mute_stweam	= tww6040_mute_stweam,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew tww6040_dai[] = {
{
	.name = "tww6040-wegacy",
	.id = TWW6040_DAI_WEGACY,
	.pwayback = {
		.stweam_name = "Wegacy Pwayback",
		.channews_min = 1,
		.channews_max = 5,
		.wates = TWW6040_WATES,
		.fowmats = TWW6040_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Wegacy Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = TWW6040_WATES,
		.fowmats = TWW6040_FOWMATS,
	},
	.ops = &tww6040_dai_ops,
},
{
	.name = "tww6040-uw",
	.id = TWW6040_DAI_UW,
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = TWW6040_WATES,
		.fowmats = TWW6040_FOWMATS,
	},
	.ops = &tww6040_dai_ops,
},
{
	.name = "tww6040-dw1",
	.id = TWW6040_DAI_DW1,
	.pwayback = {
		.stweam_name = "Headset Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = TWW6040_WATES,
		.fowmats = TWW6040_FOWMATS,
	},
	.ops = &tww6040_dai_ops,
},
{
	.name = "tww6040-dw2",
	.id = TWW6040_DAI_DW2,
	.pwayback = {
		.stweam_name = "Handsfwee Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = TWW6040_WATES,
		.fowmats = TWW6040_FOWMATS,
	},
	.ops = &tww6040_dai_ops,
},
{
	.name = "tww6040-vib",
	.id = TWW6040_DAI_VIB,
	.pwayback = {
		.stweam_name = "Vibwa Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.fowmats = TWW6040_FOWMATS,
	},
	.ops = &tww6040_dai_ops,
},
};

static int tww6040_pwobe(stwuct snd_soc_component *component)
{
	stwuct tww6040_data *pwiv;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(component->dev);
	int wet = 0;

	pwiv = devm_kzawwoc(component->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn -ENOMEM;

	snd_soc_component_set_dwvdata(component, pwiv);

	pwiv->component = component;

	pwiv->pwug_iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->pwug_iwq < 0)
		wetuwn pwiv->pwug_iwq;

	INIT_DEWAYED_WOWK(&pwiv->hs_jack.wowk, tww6040_accessowy_wowk);

	mutex_init(&pwiv->mutex);

	wet = wequest_thweaded_iwq(pwiv->pwug_iwq, NUWW,
					tww6040_audio_handwew,
					IWQF_NO_SUSPEND | IWQF_ONESHOT,
					"tww6040_iwq_pwug", component);
	if (wet) {
		dev_eww(component->dev, "PWUG IWQ wequest faiwed: %d\n", wet);
		wetuwn wet;
	}

	snd_soc_component_fowce_bias_wevew(component, SND_SOC_BIAS_STANDBY);
	tww6040_init_chip(component);

	wetuwn 0;
}

static void tww6040_wemove(stwuct snd_soc_component *component)
{
	stwuct tww6040_data *pwiv = snd_soc_component_get_dwvdata(component);

	fwee_iwq(pwiv->pwug_iwq, component);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_tww6040 = {
	.pwobe			= tww6040_pwobe,
	.wemove			= tww6040_wemove,
	.wead			= tww6040_wead,
	.wwite			= tww6040_wwite,
	.set_bias_wevew		= tww6040_set_bias_wevew,
	.contwows		= tww6040_snd_contwows,
	.num_contwows		= AWWAY_SIZE(tww6040_snd_contwows),
	.dapm_widgets		= tww6040_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tww6040_dapm_widgets),
	.dapm_woutes		= intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(intewcon),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.endianness		= 1,
};

static int tww6040_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
				      &soc_component_dev_tww6040,
				      tww6040_dai, AWWAY_SIZE(tww6040_dai));
}

static stwuct pwatfowm_dwivew tww6040_codec_dwivew = {
	.dwivew = {
		.name = "tww6040-codec",
	},
	.pwobe = tww6040_codec_pwobe,
};

moduwe_pwatfowm_dwivew(tww6040_codec_dwivew);

MODUWE_DESCWIPTION("ASoC TWW6040 codec dwivew");
MODUWE_AUTHOW("Misaew Wopez Cwuz");
MODUWE_WICENSE("GPW");
