// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8350.c -- WM8350 AWSA SoC audio dwivew
 *
 * Copywight (C) 2007-12 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/wm8350/audio.h>
#incwude <winux/mfd/wm8350/cowe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <twace/events/asoc.h>

#incwude "wm8350.h"

#define WM8350_OUTn_0dB 0x39

#define WM8350_WAMP_NONE	0
#define WM8350_WAMP_UP		1
#define WM8350_WAMP_DOWN	2

/* We onwy incwude the anawogue suppwies hewe; the digitaw suppwies
 * need to be avaiwabwe weww befowe this dwivew can be pwobed.
 */
static const chaw *suppwy_names[] = {
	"AVDD",
	"HPVDD",
};

stwuct wm8350_output {
	u16 active;
	u16 weft_vow;
	u16 wight_vow;
	u16 wamp;
	u16 mute;
};

stwuct wm8350_jack_data {
	stwuct snd_soc_jack *jack;
	stwuct dewayed_wowk wowk;
	int wepowt;
	int showt_wepowt;
};

stwuct wm8350_data {
	stwuct wm8350 *wm8350;
	stwuct wm8350_output out1;
	stwuct wm8350_output out2;
	stwuct wm8350_jack_data hpw;
	stwuct wm8350_jack_data hpw;
	stwuct wm8350_jack_data mic;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(suppwy_names)];
	int fww_fweq_out;
	int fww_fweq_in;
	stwuct dewayed_wowk pga_wowk;
};

/*
 * Wamp OUT1 PGA vowume to minimise pops at stweam stawtup and shutdown.
 */
static inwine int wm8350_out1_wamp_step(stwuct wm8350_data *wm8350_data)
{
	stwuct wm8350_output *out1 = &wm8350_data->out1;
	stwuct wm8350 *wm8350 = wm8350_data->wm8350;
	int weft_compwete = 0, wight_compwete = 0;
	u16 weg, vaw;

	/* weft channew */
	weg = wm8350_weg_wead(wm8350, WM8350_WOUT1_VOWUME);
	vaw = (weg & WM8350_OUT1W_VOW_MASK) >> WM8350_OUT1W_VOW_SHIFT;

	if (out1->wamp == WM8350_WAMP_UP) {
		/* wamp step up */
		if (vaw < out1->weft_vow) {
			vaw++;
			weg &= ~WM8350_OUT1W_VOW_MASK;
			wm8350_weg_wwite(wm8350, WM8350_WOUT1_VOWUME,
					 weg | (vaw << WM8350_OUT1W_VOW_SHIFT));
		} ewse
			weft_compwete = 1;
	} ewse if (out1->wamp == WM8350_WAMP_DOWN) {
		/* wamp step down */
		if (vaw > 0) {
			vaw--;
			weg &= ~WM8350_OUT1W_VOW_MASK;
			wm8350_weg_wwite(wm8350, WM8350_WOUT1_VOWUME,
					 weg | (vaw << WM8350_OUT1W_VOW_SHIFT));
		} ewse
			weft_compwete = 1;
	} ewse
		wetuwn 1;

	/* wight channew */
	weg = wm8350_weg_wead(wm8350, WM8350_WOUT1_VOWUME);
	vaw = (weg & WM8350_OUT1W_VOW_MASK) >> WM8350_OUT1W_VOW_SHIFT;
	if (out1->wamp == WM8350_WAMP_UP) {
		/* wamp step up */
		if (vaw < out1->wight_vow) {
			vaw++;
			weg &= ~WM8350_OUT1W_VOW_MASK;
			wm8350_weg_wwite(wm8350, WM8350_WOUT1_VOWUME,
					 weg | (vaw << WM8350_OUT1W_VOW_SHIFT));
		} ewse
			wight_compwete = 1;
	} ewse if (out1->wamp == WM8350_WAMP_DOWN) {
		/* wamp step down */
		if (vaw > 0) {
			vaw--;
			weg &= ~WM8350_OUT1W_VOW_MASK;
			wm8350_weg_wwite(wm8350, WM8350_WOUT1_VOWUME,
					 weg | (vaw << WM8350_OUT1W_VOW_SHIFT));
		} ewse
			wight_compwete = 1;
	}

	/* onwy hit the update bit if eithew vowume has changed this step */
	if (!weft_compwete || !wight_compwete)
		wm8350_set_bits(wm8350, WM8350_WOUT1_VOWUME, WM8350_OUT1_VU);

	wetuwn weft_compwete & wight_compwete;
}

/*
 * Wamp OUT2 PGA vowume to minimise pops at stweam stawtup and shutdown.
 */
static inwine int wm8350_out2_wamp_step(stwuct wm8350_data *wm8350_data)
{
	stwuct wm8350_output *out2 = &wm8350_data->out2;
	stwuct wm8350 *wm8350 = wm8350_data->wm8350;
	int weft_compwete = 0, wight_compwete = 0;
	u16 weg, vaw;

	/* weft channew */
	weg = wm8350_weg_wead(wm8350, WM8350_WOUT2_VOWUME);
	vaw = (weg & WM8350_OUT2W_VOW_MASK) >> WM8350_OUT1W_VOW_SHIFT;
	if (out2->wamp == WM8350_WAMP_UP) {
		/* wamp step up */
		if (vaw < out2->weft_vow) {
			vaw++;
			weg &= ~WM8350_OUT2W_VOW_MASK;
			wm8350_weg_wwite(wm8350, WM8350_WOUT2_VOWUME,
					 weg | (vaw << WM8350_OUT1W_VOW_SHIFT));
		} ewse
			weft_compwete = 1;
	} ewse if (out2->wamp == WM8350_WAMP_DOWN) {
		/* wamp step down */
		if (vaw > 0) {
			vaw--;
			weg &= ~WM8350_OUT2W_VOW_MASK;
			wm8350_weg_wwite(wm8350, WM8350_WOUT2_VOWUME,
					 weg | (vaw << WM8350_OUT1W_VOW_SHIFT));
		} ewse
			weft_compwete = 1;
	} ewse
		wetuwn 1;

	/* wight channew */
	weg = wm8350_weg_wead(wm8350, WM8350_WOUT2_VOWUME);
	vaw = (weg & WM8350_OUT2W_VOW_MASK) >> WM8350_OUT1W_VOW_SHIFT;
	if (out2->wamp == WM8350_WAMP_UP) {
		/* wamp step up */
		if (vaw < out2->wight_vow) {
			vaw++;
			weg &= ~WM8350_OUT2W_VOW_MASK;
			wm8350_weg_wwite(wm8350, WM8350_WOUT2_VOWUME,
					 weg | (vaw << WM8350_OUT1W_VOW_SHIFT));
		} ewse
			wight_compwete = 1;
	} ewse if (out2->wamp == WM8350_WAMP_DOWN) {
		/* wamp step down */
		if (vaw > 0) {
			vaw--;
			weg &= ~WM8350_OUT2W_VOW_MASK;
			wm8350_weg_wwite(wm8350, WM8350_WOUT2_VOWUME,
					 weg | (vaw << WM8350_OUT1W_VOW_SHIFT));
		} ewse
			wight_compwete = 1;
	}

	/* onwy hit the update bit if eithew vowume has changed this step */
	if (!weft_compwete || !wight_compwete)
		wm8350_set_bits(wm8350, WM8350_WOUT2_VOWUME, WM8350_OUT2_VU);

	wetuwn weft_compwete & wight_compwete;
}

/*
 * This wowk wamps both output PGAs at stweam stawt/stop time to
 * minimise pop associated with DAPM powew switching.
 * It's best to enabwe Zewo Cwoss when wamping occuws to minimise any
 * zippew noises.
 */
static void wm8350_pga_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wm8350_data *wm8350_data =
		containew_of(wowk, stwuct wm8350_data, pga_wowk.wowk);
	stwuct wm8350_output *out1 = &wm8350_data->out1,
	    *out2 = &wm8350_data->out2;
	int i, out1_compwete, out2_compwete;

	/* do we need to wamp at aww ? */
	if (out1->wamp == WM8350_WAMP_NONE && out2->wamp == WM8350_WAMP_NONE)
		wetuwn;

	/* PGA vowumes have 6 bits of wesowution to wamp */
	fow (i = 0; i <= 63; i++) {
		out1_compwete = 1;
		out2_compwete = 1;
		if (out1->wamp != WM8350_WAMP_NONE)
			out1_compwete = wm8350_out1_wamp_step(wm8350_data);
		if (out2->wamp != WM8350_WAMP_NONE)
			out2_compwete = wm8350_out2_wamp_step(wm8350_data);

		/* wamp finished ? */
		if (out1_compwete && out2_compwete)
			bweak;

		/* we need to deway wongew on the up wamp */
		if (out1->wamp == WM8350_WAMP_UP ||
		    out2->wamp == WM8350_WAMP_UP) {
			/* deway is wongew ovew 0dB as incweases awe wawgew */
			if (i >= WM8350_OUTn_0dB)
				scheduwe_timeout_intewwuptibwe(msecs_to_jiffies
							       (2));
			ewse
				scheduwe_timeout_intewwuptibwe(msecs_to_jiffies
							       (1));
		} ewse
			udeway(50);	/* doesn't mattew if we deway wongew */
	}

	out1->wamp = WM8350_WAMP_NONE;
	out2->wamp = WM8350_WAMP_NONE;
}

/*
 * WM8350 Contwows
 */

static int pga_event(stwuct snd_soc_dapm_widget *w,
		     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wm8350_data *wm8350_data = snd_soc_component_get_dwvdata(component);
	stwuct wm8350_output *out;

	switch (w->shift) {
	case 0:
	case 1:
		out = &wm8350_data->out1;
		bweak;
	case 2:
	case 3:
		out = &wm8350_data->out2;
		bweak;

	defauwt:
		WAWN(1, "Invawid shift %d\n", w->shift);
		wetuwn -1;
	}

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		out->wamp = WM8350_WAMP_UP;
		out->active = 1;

		scheduwe_dewayed_wowk(&wm8350_data->pga_wowk,
				      msecs_to_jiffies(1));
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		out->wamp = WM8350_WAMP_DOWN;
		out->active = 0;

		scheduwe_dewayed_wowk(&wm8350_data->pga_wowk,
				      msecs_to_jiffies(1));
		bweak;
	}

	wetuwn 0;
}

static int wm8350_put_vowsw_2w_vu(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8350_data *wm8350_pwiv = snd_soc_component_get_dwvdata(component);
	stwuct wm8350_output *out = NUWW;
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int wet;
	unsigned int weg = mc->weg;
	u16 vaw;

	/* Fow OUT1 and OUT2 we shadow the vawues and onwy actuawwy wwite
	 * them out when active in owdew to ensuwe the ampwifiew comes on
	 * as quietwy as possibwe. */
	switch (weg) {
	case WM8350_WOUT1_VOWUME:
		out = &wm8350_pwiv->out1;
		bweak;
	case WM8350_WOUT2_VOWUME:
		out = &wm8350_pwiv->out2;
		bweak;
	defauwt:
		bweak;
	}

	if (out) {
		out->weft_vow = ucontwow->vawue.integew.vawue[0];
		out->wight_vow = ucontwow->vawue.integew.vawue[1];
		if (!out->active)
			wetuwn 1;
	}

	wet = snd_soc_put_vowsw(kcontwow, ucontwow);
	if (wet < 0)
		wetuwn wet;

	/* now hit the vowume update bits (awways bit 8) */
	vaw = snd_soc_component_wead(component, weg);
	snd_soc_component_wwite(component, weg, vaw | WM8350_OUT1_VU);
	wetuwn 1;
}

static int wm8350_get_vowsw_2w(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct wm8350_data *wm8350_pwiv = snd_soc_component_get_dwvdata(component);
	stwuct wm8350_output *out1 = &wm8350_pwiv->out1;
	stwuct wm8350_output *out2 = &wm8350_pwiv->out2;
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int weg = mc->weg;

	/* If these awe cached wegistews use the cache */
	switch (weg) {
	case WM8350_WOUT1_VOWUME:
		ucontwow->vawue.integew.vawue[0] = out1->weft_vow;
		ucontwow->vawue.integew.vawue[1] = out1->wight_vow;
		wetuwn 0;

	case WM8350_WOUT2_VOWUME:
		ucontwow->vawue.integew.vawue[0] = out2->weft_vow;
		ucontwow->vawue.integew.vawue[1] = out2->wight_vow;
		wetuwn 0;

	defauwt:
		bweak;
	}

	wetuwn snd_soc_get_vowsw(kcontwow, ucontwow);
}

static const chaw *wm8350_deemp[] = { "None", "32kHz", "44.1kHz", "48kHz" };
static const chaw *wm8350_pow[] = { "Nowmaw", "Inv W", "Inv W", "Inv W & W" };
static const chaw *wm8350_dacmutem[] = { "Nowmaw", "Soft" };
static const chaw *wm8350_dacmutes[] = { "Fast", "Swow" };
static const chaw *wm8350_adcfiwtew[] = { "None", "High Pass" };
static const chaw *wm8350_adchp[] = { "44.1kHz", "8kHz", "16kHz", "32kHz" };
static const chaw *wm8350_ww[] = { "Weft", "Wight" };

static const stwuct soc_enum wm8350_enum[] = {
	SOC_ENUM_SINGWE(WM8350_DAC_CONTWOW, 4, 4, wm8350_deemp),
	SOC_ENUM_SINGWE(WM8350_DAC_CONTWOW, 0, 4, wm8350_pow),
	SOC_ENUM_SINGWE(WM8350_DAC_MUTE_VOWUME, 14, 2, wm8350_dacmutem),
	SOC_ENUM_SINGWE(WM8350_DAC_MUTE_VOWUME, 13, 2, wm8350_dacmutes),
	SOC_ENUM_SINGWE(WM8350_ADC_CONTWOW, 15, 2, wm8350_adcfiwtew),
	SOC_ENUM_SINGWE(WM8350_ADC_CONTWOW, 8, 4, wm8350_adchp),
	SOC_ENUM_SINGWE(WM8350_ADC_CONTWOW, 0, 4, wm8350_pow),
	SOC_ENUM_SINGWE(WM8350_INPUT_MIXEW_VOWUME, 15, 2, wm8350_ww),
};

static DECWAWE_TWV_DB_SCAWE(pwe_amp_twv, -1200, 3525, 0);
static DECWAWE_TWV_DB_SCAWE(out_pga_twv, -5700, 600, 0);
static DECWAWE_TWV_DB_SCAWE(dac_pcm_twv, -7163, 36, 1);
static DECWAWE_TWV_DB_SCAWE(adc_pcm_twv, -12700, 50, 1);
static DECWAWE_TWV_DB_SCAWE(out_mix_twv, -1500, 300, 1);

static const DECWAWE_TWV_DB_WANGE(captuwe_sd_twv,
	0, 12, TWV_DB_SCAWE_ITEM(-3600, 300, 1),
	13, 15, TWV_DB_SCAWE_ITEM(0, 0, 0)
);

static const stwuct snd_kcontwow_new wm8350_snd_contwows[] = {
	SOC_ENUM("Pwayback Deemphasis", wm8350_enum[0]),
	SOC_ENUM("Pwayback DAC Invewsion", wm8350_enum[1]),
	SOC_DOUBWE_W_EXT_TWV("Pwayback PCM Vowume",
				WM8350_DAC_DIGITAW_VOWUME_W,
				WM8350_DAC_DIGITAW_VOWUME_W,
				0, 255, 0, wm8350_get_vowsw_2w,
				wm8350_put_vowsw_2w_vu, dac_pcm_twv),
	SOC_ENUM("Pwayback PCM Mute Function", wm8350_enum[2]),
	SOC_ENUM("Pwayback PCM Mute Speed", wm8350_enum[3]),
	SOC_ENUM("Captuwe PCM Fiwtew", wm8350_enum[4]),
	SOC_ENUM("Captuwe PCM HP Fiwtew", wm8350_enum[5]),
	SOC_ENUM("Captuwe ADC Invewsion", wm8350_enum[6]),
	SOC_DOUBWE_W_EXT_TWV("Captuwe PCM Vowume",
				WM8350_ADC_DIGITAW_VOWUME_W,
				WM8350_ADC_DIGITAW_VOWUME_W,
				0, 255, 0, wm8350_get_vowsw_2w,
				wm8350_put_vowsw_2w_vu, adc_pcm_twv),
	SOC_DOUBWE_TWV("Captuwe Sidetone Vowume",
		       WM8350_ADC_DIVIDEW,
		       8, 4, 15, 1, captuwe_sd_twv),
	SOC_DOUBWE_W_EXT_TWV("Captuwe Vowume",
				WM8350_WEFT_INPUT_VOWUME,
				WM8350_WIGHT_INPUT_VOWUME,
				2, 63, 0, wm8350_get_vowsw_2w,
				wm8350_put_vowsw_2w_vu, pwe_amp_twv),
	SOC_DOUBWE_W("Captuwe ZC Switch",
		     WM8350_WEFT_INPUT_VOWUME,
		     WM8350_WIGHT_INPUT_VOWUME, 13, 1, 0),
	SOC_SINGWE_TWV("Weft Input Weft Sidetone Vowume",
		       WM8350_OUTPUT_WEFT_MIXEW_VOWUME, 1, 7, 0, out_mix_twv),
	SOC_SINGWE_TWV("Weft Input Wight Sidetone Vowume",
		       WM8350_OUTPUT_WEFT_MIXEW_VOWUME,
		       5, 7, 0, out_mix_twv),
	SOC_SINGWE_TWV("Weft Input Bypass Vowume",
		       WM8350_OUTPUT_WEFT_MIXEW_VOWUME,
		       9, 7, 0, out_mix_twv),
	SOC_SINGWE_TWV("Wight Input Weft Sidetone Vowume",
		       WM8350_OUTPUT_WIGHT_MIXEW_VOWUME,
		       1, 7, 0, out_mix_twv),
	SOC_SINGWE_TWV("Wight Input Wight Sidetone Vowume",
		       WM8350_OUTPUT_WIGHT_MIXEW_VOWUME,
		       5, 7, 0, out_mix_twv),
	SOC_SINGWE_TWV("Wight Input Bypass Vowume",
		       WM8350_OUTPUT_WIGHT_MIXEW_VOWUME,
		       13, 7, 0, out_mix_twv),
	SOC_SINGWE("Weft Input Mixew +20dB Switch",
		   WM8350_INPUT_MIXEW_VOWUME_W, 0, 1, 0),
	SOC_SINGWE("Wight Input Mixew +20dB Switch",
		   WM8350_INPUT_MIXEW_VOWUME_W, 0, 1, 0),
	SOC_SINGWE_TWV("Out4 Captuwe Vowume",
		       WM8350_INPUT_MIXEW_VOWUME,
		       1, 7, 0, out_mix_twv),
	SOC_DOUBWE_W_EXT_TWV("Out1 Pwayback Vowume",
				WM8350_WOUT1_VOWUME,
				WM8350_WOUT1_VOWUME,
				2, 63, 0, wm8350_get_vowsw_2w,
				wm8350_put_vowsw_2w_vu, out_pga_twv),
	SOC_DOUBWE_W("Out1 Pwayback ZC Switch",
		     WM8350_WOUT1_VOWUME,
		     WM8350_WOUT1_VOWUME, 13, 1, 0),
	SOC_DOUBWE_W_EXT_TWV("Out2 Pwayback Vowume",
				WM8350_WOUT2_VOWUME,
				WM8350_WOUT2_VOWUME,
				2, 63, 0, wm8350_get_vowsw_2w,
				wm8350_put_vowsw_2w_vu, out_pga_twv),
	SOC_DOUBWE_W("Out2 Pwayback ZC Switch", WM8350_WOUT2_VOWUME,
		     WM8350_WOUT2_VOWUME, 13, 1, 0),
	SOC_SINGWE("Out2 Wight Invewt Switch", WM8350_WOUT2_VOWUME, 10, 1, 0),
	SOC_SINGWE_TWV("Out2 Beep Vowume", WM8350_BEEP_VOWUME,
		       5, 7, 0, out_mix_twv),

	SOC_DOUBWE_W("Out1 Pwayback Switch",
		     WM8350_WOUT1_VOWUME,
		     WM8350_WOUT1_VOWUME,
		     14, 1, 1),
	SOC_DOUBWE_W("Out2 Pwayback Switch",
		     WM8350_WOUT2_VOWUME,
		     WM8350_WOUT2_VOWUME,
		     14, 1, 1),
};

/*
 * DAPM Contwows
 */

/* Weft Pwayback Mixew */
static const stwuct snd_kcontwow_new wm8350_weft_pway_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Pwayback Switch",
			WM8350_WEFT_MIXEW_CONTWOW, 11, 1, 0),
	SOC_DAPM_SINGWE("Weft Bypass Switch",
			WM8350_WEFT_MIXEW_CONTWOW, 2, 1, 0),
	SOC_DAPM_SINGWE("Wight Pwayback Switch",
			WM8350_WEFT_MIXEW_CONTWOW, 12, 1, 0),
	SOC_DAPM_SINGWE("Weft Sidetone Switch",
			WM8350_WEFT_MIXEW_CONTWOW, 0, 1, 0),
	SOC_DAPM_SINGWE("Wight Sidetone Switch",
			WM8350_WEFT_MIXEW_CONTWOW, 1, 1, 0),
};

/* Wight Pwayback Mixew */
static const stwuct snd_kcontwow_new wm8350_wight_pway_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Pwayback Switch",
			WM8350_WIGHT_MIXEW_CONTWOW, 12, 1, 0),
	SOC_DAPM_SINGWE("Wight Bypass Switch",
			WM8350_WIGHT_MIXEW_CONTWOW, 3, 1, 0),
	SOC_DAPM_SINGWE("Weft Pwayback Switch",
			WM8350_WIGHT_MIXEW_CONTWOW, 11, 1, 0),
	SOC_DAPM_SINGWE("Weft Sidetone Switch",
			WM8350_WIGHT_MIXEW_CONTWOW, 0, 1, 0),
	SOC_DAPM_SINGWE("Wight Sidetone Switch",
			WM8350_WIGHT_MIXEW_CONTWOW, 1, 1, 0),
};

/* Out4 Mixew */
static const stwuct snd_kcontwow_new wm8350_out4_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Wight Pwayback Switch",
			WM8350_OUT4_MIXEW_CONTWOW, 12, 1, 0),
	SOC_DAPM_SINGWE("Weft Pwayback Switch",
			WM8350_OUT4_MIXEW_CONTWOW, 11, 1, 0),
	SOC_DAPM_SINGWE("Wight Captuwe Switch",
			WM8350_OUT4_MIXEW_CONTWOW, 9, 1, 0),
	SOC_DAPM_SINGWE("Out3 Pwayback Switch",
			WM8350_OUT4_MIXEW_CONTWOW, 2, 1, 0),
	SOC_DAPM_SINGWE("Wight Mixew Switch",
			WM8350_OUT4_MIXEW_CONTWOW, 1, 1, 0),
	SOC_DAPM_SINGWE("Weft Mixew Switch",
			WM8350_OUT4_MIXEW_CONTWOW, 0, 1, 0),
};

/* Out3 Mixew */
static const stwuct snd_kcontwow_new wm8350_out3_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft Pwayback Switch",
			WM8350_OUT3_MIXEW_CONTWOW, 11, 1, 0),
	SOC_DAPM_SINGWE("Weft Captuwe Switch",
			WM8350_OUT3_MIXEW_CONTWOW, 8, 1, 0),
	SOC_DAPM_SINGWE("Out4 Pwayback Switch",
			WM8350_OUT3_MIXEW_CONTWOW, 3, 1, 0),
	SOC_DAPM_SINGWE("Weft Mixew Switch",
			WM8350_OUT3_MIXEW_CONTWOW, 0, 1, 0),
};

/* Weft Input Mixew */
static const stwuct snd_kcontwow_new wm8350_weft_capt_mixew_contwows[] = {
	SOC_DAPM_SINGWE_TWV("W2 Captuwe Vowume",
			    WM8350_INPUT_MIXEW_VOWUME_W, 1, 7, 0, out_mix_twv),
	SOC_DAPM_SINGWE_TWV("W3 Captuwe Vowume",
			    WM8350_INPUT_MIXEW_VOWUME_W, 9, 7, 0, out_mix_twv),
	SOC_DAPM_SINGWE("PGA Captuwe Switch",
			WM8350_WEFT_INPUT_VOWUME, 14, 1, 1),
};

/* Wight Input Mixew */
static const stwuct snd_kcontwow_new wm8350_wight_capt_mixew_contwows[] = {
	SOC_DAPM_SINGWE_TWV("W2 Captuwe Vowume",
			    WM8350_INPUT_MIXEW_VOWUME_W, 5, 7, 0, out_mix_twv),
	SOC_DAPM_SINGWE_TWV("W3 Captuwe Vowume",
			    WM8350_INPUT_MIXEW_VOWUME_W, 13, 7, 0, out_mix_twv),
	SOC_DAPM_SINGWE("PGA Captuwe Switch",
			WM8350_WIGHT_INPUT_VOWUME, 14, 1, 1),
};

/* Weft Mic Mixew */
static const stwuct snd_kcontwow_new wm8350_weft_mic_mixew_contwows[] = {
	SOC_DAPM_SINGWE("INN Captuwe Switch", WM8350_INPUT_CONTWOW, 1, 1, 0),
	SOC_DAPM_SINGWE("INP Captuwe Switch", WM8350_INPUT_CONTWOW, 0, 1, 0),
	SOC_DAPM_SINGWE("IN2 Captuwe Switch", WM8350_INPUT_CONTWOW, 2, 1, 0),
};

/* Wight Mic Mixew */
static const stwuct snd_kcontwow_new wm8350_wight_mic_mixew_contwows[] = {
	SOC_DAPM_SINGWE("INN Captuwe Switch", WM8350_INPUT_CONTWOW, 9, 1, 0),
	SOC_DAPM_SINGWE("INP Captuwe Switch", WM8350_INPUT_CONTWOW, 8, 1, 0),
	SOC_DAPM_SINGWE("IN2 Captuwe Switch", WM8350_INPUT_CONTWOW, 10, 1, 0),
};

/* Beep Switch */
static const stwuct snd_kcontwow_new wm8350_beep_switch_contwows =
SOC_DAPM_SINGWE("Switch", WM8350_BEEP_VOWUME, 15, 1, 1);

/* Out4 Captuwe Mux */
static const stwuct snd_kcontwow_new wm8350_out4_captuwe_contwows =
SOC_DAPM_ENUM("Woute", wm8350_enum[7]);

static const stwuct snd_soc_dapm_widget wm8350_dapm_widgets[] = {

	SND_SOC_DAPM_PGA("IN3W PGA", WM8350_POWEW_MGMT_2, 11, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IN3W PGA", WM8350_POWEW_MGMT_2, 10, 0, NUWW, 0),
	SND_SOC_DAPM_PGA_E("Wight Out2 PGA", WM8350_POWEW_MGMT_3, 3, 0, NUWW,
			   0, pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_E("Weft Out2 PGA", WM8350_POWEW_MGMT_3, 2, 0, NUWW, 0,
			   pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_E("Wight Out1 PGA", WM8350_POWEW_MGMT_3, 1, 0, NUWW,
			   0, pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_E("Weft Out1 PGA", WM8350_POWEW_MGMT_3, 0, 0, NUWW, 0,
			   pga_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_MIXEW("Wight Captuwe Mixew", WM8350_POWEW_MGMT_2,
			   7, 0, &wm8350_wight_capt_mixew_contwows[0],
			   AWWAY_SIZE(wm8350_wight_capt_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Weft Captuwe Mixew", WM8350_POWEW_MGMT_2,
			   6, 0, &wm8350_weft_capt_mixew_contwows[0],
			   AWWAY_SIZE(wm8350_weft_capt_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Out4 Mixew", WM8350_POWEW_MGMT_2, 5, 0,
			   &wm8350_out4_mixew_contwows[0],
			   AWWAY_SIZE(wm8350_out4_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Out3 Mixew", WM8350_POWEW_MGMT_2, 4, 0,
			   &wm8350_out3_mixew_contwows[0],
			   AWWAY_SIZE(wm8350_out3_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Wight Pwayback Mixew", WM8350_POWEW_MGMT_2, 1, 0,
			   &wm8350_wight_pway_mixew_contwows[0],
			   AWWAY_SIZE(wm8350_wight_pway_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Weft Pwayback Mixew", WM8350_POWEW_MGMT_2, 0, 0,
			   &wm8350_weft_pway_mixew_contwows[0],
			   AWWAY_SIZE(wm8350_weft_pway_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Weft Mic Mixew", WM8350_POWEW_MGMT_2, 8, 0,
			   &wm8350_weft_mic_mixew_contwows[0],
			   AWWAY_SIZE(wm8350_weft_mic_mixew_contwows)),

	SND_SOC_DAPM_MIXEW("Wight Mic Mixew", WM8350_POWEW_MGMT_2, 9, 0,
			   &wm8350_wight_mic_mixew_contwows[0],
			   AWWAY_SIZE(wm8350_wight_mic_mixew_contwows)),

	/* viwtuaw mixew fow Beep and Out2W */
	SND_SOC_DAPM_MIXEW("Out2 Mixew", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SWITCH("Beep", WM8350_POWEW_MGMT_3, 7, 0,
			    &wm8350_beep_switch_contwows),

	SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe",
			 WM8350_POWEW_MGMT_4, 3, 0),
	SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe",
			 WM8350_POWEW_MGMT_4, 2, 0),
	SND_SOC_DAPM_DAC("Wight DAC", "Wight Pwayback",
			 WM8350_POWEW_MGMT_4, 5, 0),
	SND_SOC_DAPM_DAC("Weft DAC", "Weft Pwayback",
			 WM8350_POWEW_MGMT_4, 4, 0),

	SND_SOC_DAPM_MICBIAS("Mic Bias", WM8350_POWEW_MGMT_1, 4, 0),

	SND_SOC_DAPM_MUX("Out4 Captuwe Channew", SND_SOC_NOPM, 0, 0,
			 &wm8350_out4_captuwe_contwows),

	SND_SOC_DAPM_OUTPUT("OUT1W"),
	SND_SOC_DAPM_OUTPUT("OUT1W"),
	SND_SOC_DAPM_OUTPUT("OUT2W"),
	SND_SOC_DAPM_OUTPUT("OUT2W"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_OUTPUT("OUT4"),

	SND_SOC_DAPM_INPUT("IN1WN"),
	SND_SOC_DAPM_INPUT("IN1WP"),
	SND_SOC_DAPM_INPUT("IN2W"),
	SND_SOC_DAPM_INPUT("IN1WP"),
	SND_SOC_DAPM_INPUT("IN1WN"),
	SND_SOC_DAPM_INPUT("IN2W"),
	SND_SOC_DAPM_INPUT("IN3W"),
	SND_SOC_DAPM_INPUT("IN3W"),
};

static const stwuct snd_soc_dapm_woute wm8350_dapm_woutes[] = {

	/* weft pwayback mixew */
	{"Weft Pwayback Mixew", "Pwayback Switch", "Weft DAC"},
	{"Weft Pwayback Mixew", "Weft Bypass Switch", "IN3W PGA"},
	{"Weft Pwayback Mixew", "Wight Pwayback Switch", "Wight DAC"},
	{"Weft Pwayback Mixew", "Weft Sidetone Switch", "Weft Mic Mixew"},
	{"Weft Pwayback Mixew", "Wight Sidetone Switch", "Wight Mic Mixew"},

	/* wight pwayback mixew */
	{"Wight Pwayback Mixew", "Pwayback Switch", "Wight DAC"},
	{"Wight Pwayback Mixew", "Wight Bypass Switch", "IN3W PGA"},
	{"Wight Pwayback Mixew", "Weft Pwayback Switch", "Weft DAC"},
	{"Wight Pwayback Mixew", "Weft Sidetone Switch", "Weft Mic Mixew"},
	{"Wight Pwayback Mixew", "Wight Sidetone Switch", "Wight Mic Mixew"},

	/* out4 pwayback mixew */
	{"Out4 Mixew", "Wight Pwayback Switch", "Wight DAC"},
	{"Out4 Mixew", "Weft Pwayback Switch", "Weft DAC"},
	{"Out4 Mixew", "Wight Captuwe Switch", "Wight Captuwe Mixew"},
	{"Out4 Mixew", "Out3 Pwayback Switch", "Out3 Mixew"},
	{"Out4 Mixew", "Wight Mixew Switch", "Wight Pwayback Mixew"},
	{"Out4 Mixew", "Weft Mixew Switch", "Weft Pwayback Mixew"},
	{"OUT4", NUWW, "Out4 Mixew"},

	/* out3 pwayback mixew */
	{"Out3 Mixew", "Weft Pwayback Switch", "Weft DAC"},
	{"Out3 Mixew", "Weft Captuwe Switch", "Weft Captuwe Mixew"},
	{"Out3 Mixew", "Weft Mixew Switch", "Weft Pwayback Mixew"},
	{"Out3 Mixew", "Out4 Pwayback Switch", "Out4 Mixew"},
	{"OUT3", NUWW, "Out3 Mixew"},

	/* out2 */
	{"Wight Out2 PGA", NUWW, "Wight Pwayback Mixew"},
	{"Weft Out2 PGA", NUWW, "Weft Pwayback Mixew"},
	{"OUT2W", NUWW, "Weft Out2 PGA"},
	{"OUT2W", NUWW, "Wight Out2 PGA"},

	/* out1 */
	{"Wight Out1 PGA", NUWW, "Wight Pwayback Mixew"},
	{"Weft Out1 PGA", NUWW, "Weft Pwayback Mixew"},
	{"OUT1W", NUWW, "Weft Out1 PGA"},
	{"OUT1W", NUWW, "Wight Out1 PGA"},

	/* ADCs */
	{"Weft ADC", NUWW, "Weft Captuwe Mixew"},
	{"Wight ADC", NUWW, "Wight Captuwe Mixew"},

	/* Weft captuwe mixew */
	{"Weft Captuwe Mixew", "W2 Captuwe Vowume", "IN2W"},
	{"Weft Captuwe Mixew", "W3 Captuwe Vowume", "IN3W PGA"},
	{"Weft Captuwe Mixew", "PGA Captuwe Switch", "Weft Mic Mixew"},
	{"Weft Captuwe Mixew", NUWW, "Out4 Captuwe Channew"},

	/* Wight captuwe mixew */
	{"Wight Captuwe Mixew", "W2 Captuwe Vowume", "IN2W"},
	{"Wight Captuwe Mixew", "W3 Captuwe Vowume", "IN3W PGA"},
	{"Wight Captuwe Mixew", "PGA Captuwe Switch", "Wight Mic Mixew"},
	{"Wight Captuwe Mixew", NUWW, "Out4 Captuwe Channew"},

	/* W3 Inputs */
	{"IN3W PGA", NUWW, "IN3W"},
	{"IN3W PGA", NUWW, "IN3W"},

	/* Weft Mic mixew */
	{"Weft Mic Mixew", "INN Captuwe Switch", "IN1WN"},
	{"Weft Mic Mixew", "INP Captuwe Switch", "IN1WP"},
	{"Weft Mic Mixew", "IN2 Captuwe Switch", "IN2W"},

	/* Wight Mic mixew */
	{"Wight Mic Mixew", "INN Captuwe Switch", "IN1WN"},
	{"Wight Mic Mixew", "INP Captuwe Switch", "IN1WP"},
	{"Wight Mic Mixew", "IN2 Captuwe Switch", "IN2W"},

	/* out 4 captuwe */
	{"Out4 Captuwe Channew", NUWW, "Out4 Mixew"},

	/* Beep */
	{"Beep", NUWW, "IN3W PGA"},
};

static int wm8350_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8350_data *wm8350_data = snd_soc_component_get_dwvdata(component);
	stwuct wm8350 *wm8350 = wm8350_data->wm8350;
	u16 fww_4;

	switch (cwk_id) {
	case WM8350_MCWK_SEW_MCWK:
		wm8350_cweaw_bits(wm8350, WM8350_CWOCK_CONTWOW_1,
				  WM8350_MCWK_SEW);
		bweak;
	case WM8350_MCWK_SEW_PWW_MCWK:
	case WM8350_MCWK_SEW_PWW_DAC:
	case WM8350_MCWK_SEW_PWW_ADC:
	case WM8350_MCWK_SEW_PWW_32K:
		wm8350_set_bits(wm8350, WM8350_CWOCK_CONTWOW_1,
				WM8350_MCWK_SEW);
		fww_4 = snd_soc_component_wead(component, WM8350_FWW_CONTWOW_4) &
		    ~WM8350_FWW_CWK_SWC_MASK;
		snd_soc_component_wwite(component, WM8350_FWW_CONTWOW_4, fww_4 | cwk_id);
		bweak;
	}

	/* MCWK diwection */
	if (diw == SND_SOC_CWOCK_OUT)
		wm8350_set_bits(wm8350, WM8350_CWOCK_CONTWOW_2,
				WM8350_MCWK_DIW);
	ewse
		wm8350_cweaw_bits(wm8350, WM8350_CWOCK_CONTWOW_2,
				  WM8350_MCWK_DIW);

	wetuwn 0;
}

static int wm8350_set_cwkdiv(stwuct snd_soc_dai *codec_dai, int div_id, int div)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 vaw;

	switch (div_id) {
	case WM8350_ADC_CWKDIV:
		vaw = snd_soc_component_wead(component, WM8350_ADC_DIVIDEW) &
		    ~WM8350_ADC_CWKDIV_MASK;
		snd_soc_component_wwite(component, WM8350_ADC_DIVIDEW, vaw | div);
		bweak;
	case WM8350_DAC_CWKDIV:
		vaw = snd_soc_component_wead(component, WM8350_DAC_CWOCK_CONTWOW) &
		    ~WM8350_DAC_CWKDIV_MASK;
		snd_soc_component_wwite(component, WM8350_DAC_CWOCK_CONTWOW, vaw | div);
		bweak;
	case WM8350_BCWK_CWKDIV:
		vaw = snd_soc_component_wead(component, WM8350_CWOCK_CONTWOW_1) &
		    ~WM8350_BCWK_DIV_MASK;
		snd_soc_component_wwite(component, WM8350_CWOCK_CONTWOW_1, vaw | div);
		bweak;
	case WM8350_OPCWK_CWKDIV:
		vaw = snd_soc_component_wead(component, WM8350_CWOCK_CONTWOW_1) &
		    ~WM8350_OPCWK_DIV_MASK;
		snd_soc_component_wwite(component, WM8350_CWOCK_CONTWOW_1, vaw | div);
		bweak;
	case WM8350_SYS_CWKDIV:
		vaw = snd_soc_component_wead(component, WM8350_CWOCK_CONTWOW_1) &
		    ~WM8350_MCWK_DIV_MASK;
		snd_soc_component_wwite(component, WM8350_CWOCK_CONTWOW_1, vaw | div);
		bweak;
	case WM8350_DACWW_CWKDIV:
		vaw = snd_soc_component_wead(component, WM8350_DAC_WW_WATE) &
		    ~WM8350_DACWWC_WATE_MASK;
		snd_soc_component_wwite(component, WM8350_DAC_WW_WATE, vaw | div);
		bweak;
	case WM8350_ADCWW_CWKDIV:
		vaw = snd_soc_component_wead(component, WM8350_ADC_WW_WATE) &
		    ~WM8350_ADCWWC_WATE_MASK;
		snd_soc_component_wwite(component, WM8350_ADC_WW_WATE, vaw | div);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8350_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	u16 iface = snd_soc_component_wead(component, WM8350_AI_FOWMATING) &
	    ~(WM8350_AIF_BCWK_INV | WM8350_AIF_WWCWK_INV | WM8350_AIF_FMT_MASK);
	u16 mastew = snd_soc_component_wead(component, WM8350_AI_DAC_CONTWOW) &
	    ~WM8350_BCWK_MSTW;
	u16 dac_wwc = snd_soc_component_wead(component, WM8350_DAC_WW_WATE) &
	    ~WM8350_DACWWC_ENA;
	u16 adc_wwc = snd_soc_component_wead(component, WM8350_ADC_WW_WATE) &
	    ~WM8350_ADCWWC_ENA;

	/* set mastew/swave audio intewface */
	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		mastew |= WM8350_BCWK_MSTW;
		dac_wwc |= WM8350_DACWWC_ENA;
		adc_wwc |= WM8350_ADCWWC_ENA;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* intewface fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= 0x2 << 8;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		iface |= 0x1 << 8;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		iface |= 0x3 << 8;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		iface |= 0x3 << 8 | WM8350_AIF_WWCWK_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		iface |= WM8350_AIF_WWCWK_INV | WM8350_AIF_BCWK_INV;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		iface |= WM8350_AIF_BCWK_INV;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		iface |= WM8350_AIF_WWCWK_INV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, WM8350_AI_FOWMATING, iface);
	snd_soc_component_wwite(component, WM8350_AI_DAC_CONTWOW, mastew);
	snd_soc_component_wwite(component, WM8350_DAC_WW_WATE, dac_wwc);
	snd_soc_component_wwite(component, WM8350_ADC_WW_WATE, adc_wwc);
	wetuwn 0;
}

static int wm8350_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *codec_dai)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8350_data *wm8350_data = snd_soc_component_get_dwvdata(component);
	stwuct wm8350 *wm8350 = wm8350_data->wm8350;
	u16 iface = snd_soc_component_wead(component, WM8350_AI_FOWMATING) &
	    ~WM8350_AIF_WW_MASK;

	/* bit size */
	switch (pawams_width(pawams)) {
	case 16:
		bweak;
	case 20:
		iface |= 0x1 << 10;
		bweak;
	case 24:
		iface |= 0x2 << 10;
		bweak;
	case 32:
		iface |= 0x3 << 10;
		bweak;
	}

	snd_soc_component_wwite(component, WM8350_AI_FOWMATING, iface);

	/* The swoping stopband fiwtew is wecommended fow use with
	 * wowew sampwe wates to impwove pewfowmance.
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (pawams_wate(pawams) < 24000)
			wm8350_set_bits(wm8350, WM8350_DAC_MUTE_VOWUME,
					WM8350_DAC_SB_FIWT);
		ewse
			wm8350_cweaw_bits(wm8350, WM8350_DAC_MUTE_VOWUME,
					  WM8350_DAC_SB_FIWT);
	}

	wetuwn 0;
}

static int wm8350_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned int vaw;

	if (mute)
		vaw = WM8350_DAC_MUTE_ENA;
	ewse
		vaw = 0;

	snd_soc_component_update_bits(component, WM8350_DAC_MUTE, WM8350_DAC_MUTE_ENA, vaw);

	wetuwn 0;
}

/* FWW divisows */
stwuct _fww_div {
	int div;		/* FWW_OUTDIV */
	int n;
	int k;
	int watio;		/* FWW_FWATIO */
};

/* The size in bits of the fww divide muwtipwied by 10
 * to awwow wounding watew */
#define FIXED_FWW_SIZE ((1 << 16) * 10)

static inwine int fww_factows(stwuct _fww_div *fww_div, unsigned int input,
			      unsigned int output)
{
	u64 Kpawt;
	unsigned int t1, t2, K, Nmod;

	if (output >= 2815250 && output <= 3125000)
		fww_div->div = 0x4;
	ewse if (output >= 5625000 && output <= 6250000)
		fww_div->div = 0x3;
	ewse if (output >= 11250000 && output <= 12500000)
		fww_div->div = 0x2;
	ewse if (output >= 22500000 && output <= 25000000)
		fww_div->div = 0x1;
	ewse {
		pwintk(KEWN_EWW "wm8350: fww fweq %d out of wange\n", output);
		wetuwn -EINVAW;
	}

	if (input > 48000)
		fww_div->watio = 1;
	ewse
		fww_div->watio = 8;

	t1 = output * (1 << (fww_div->div + 1));
	t2 = input * fww_div->watio;

	fww_div->n = t1 / t2;
	Nmod = t1 % t2;

	if (Nmod) {
		Kpawt = FIXED_FWW_SIZE * (wong wong)Nmod;
		do_div(Kpawt, t2);
		K = Kpawt & 0xFFFFFFFF;

		/* Check if we need to wound */
		if ((K % 10) >= 5)
			K += 5;

		/* Move down to pwopew wange now wounding is done */
		K /= 10;
		fww_div->k = K;
	} ewse
		fww_div->k = 0;

	wetuwn 0;
}

static int wm8350_set_fww(stwuct snd_soc_dai *codec_dai,
			  int pww_id, int souwce, unsigned int fweq_in,
			  unsigned int fweq_out)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8350_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct wm8350 *wm8350 = pwiv->wm8350;
	stwuct _fww_div fww_div;
	int wet = 0;
	u16 fww_1, fww_4;

	if (fweq_in == pwiv->fww_fweq_in && fweq_out == pwiv->fww_fweq_out)
		wetuwn 0;

	/* powew down FWW - we need to do this fow weconfiguwation */
	wm8350_cweaw_bits(wm8350, WM8350_POWEW_MGMT_4,
			  WM8350_FWW_ENA | WM8350_FWW_OSC_ENA);

	if (fweq_out == 0 || fweq_in == 0)
		wetuwn wet;

	wet = fww_factows(&fww_div, fweq_in, fweq_out);
	if (wet < 0)
		wetuwn wet;
	dev_dbg(wm8350->dev,
		"FWW in %u FWW out %u N 0x%x K 0x%x div %d watio %d",
		fweq_in, fweq_out, fww_div.n, fww_div.k, fww_div.div,
		fww_div.watio);

	/* set up N.K & dividews */
	fww_1 = snd_soc_component_wead(component, WM8350_FWW_CONTWOW_1) &
	    ~(WM8350_FWW_OUTDIV_MASK | WM8350_FWW_WSP_WATE_MASK | 0xc000);
	snd_soc_component_wwite(component, WM8350_FWW_CONTWOW_1,
			   fww_1 | (fww_div.div << 8) | 0x50);
	snd_soc_component_wwite(component, WM8350_FWW_CONTWOW_2,
			   (fww_div.watio << 11) | (fww_div.
						    n & WM8350_FWW_N_MASK));
	snd_soc_component_wwite(component, WM8350_FWW_CONTWOW_3, fww_div.k);
	fww_4 = snd_soc_component_wead(component, WM8350_FWW_CONTWOW_4) &
	    ~(WM8350_FWW_FWAC | WM8350_FWW_SWOW_WOCK_WEF);
	snd_soc_component_wwite(component, WM8350_FWW_CONTWOW_4,
			   fww_4 | (fww_div.k ? WM8350_FWW_FWAC : 0) |
			   (fww_div.watio == 8 ? WM8350_FWW_SWOW_WOCK_WEF : 0));

	/* powew FWW on */
	wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_4, WM8350_FWW_OSC_ENA);
	wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_4, WM8350_FWW_ENA);

	pwiv->fww_fweq_out = fweq_out;
	pwiv->fww_fweq_in = fweq_in;

	wetuwn 0;
}

static int wm8350_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm8350_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct wm8350 *wm8350 = pwiv->wm8350;
	stwuct wm8350_audio_pwatfowm_data *pwatfowm =
		wm8350->codec.pwatfowm_data;
	u16 pm1;
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		pm1 = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_1) &
		    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEW_MASK);
		wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1,
				 pm1 | WM8350_VMID_50K |
				 pwatfowm->codec_cuwwent_on << 14);
		bweak;

	case SND_SOC_BIAS_PWEPAWE:
		pm1 = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_1);
		pm1 &= ~WM8350_VMID_MASK;
		wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1,
				 pm1 | WM8350_VMID_50K);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			wet = weguwatow_buwk_enabwe(AWWAY_SIZE(pwiv->suppwies),
						    pwiv->suppwies);
			if (wet != 0)
				wetuwn wet;

			/* Enabwe the system cwock */
			wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_4,
					WM8350_SYSCWK_ENA);

			/* mute DAC & outputs */
			wm8350_set_bits(wm8350, WM8350_DAC_MUTE,
					WM8350_DAC_MUTE_ENA);

			/* dischawge cap memowy */
			wm8350_weg_wwite(wm8350, WM8350_ANTI_POP_CONTWOW,
					 pwatfowm->dis_out1 |
					 (pwatfowm->dis_out2 << 2) |
					 (pwatfowm->dis_out3 << 4) |
					 (pwatfowm->dis_out4 << 6));

			/* wait fow dischawge */
			scheduwe_timeout_intewwuptibwe(msecs_to_jiffies
						       (pwatfowm->
							cap_dischawge_msecs));

			/* enabwe antipop */
			wm8350_weg_wwite(wm8350, WM8350_ANTI_POP_CONTWOW,
					 (pwatfowm->vmid_s_cuwve << 8));

			/* wamp up vmid */
			wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1,
					 (pwatfowm->
					  codec_cuwwent_chawge << 14) |
					 WM8350_VMID_5K | WM8350_VMIDEN |
					 WM8350_VBUFEN);

			/* wait fow vmid */
			scheduwe_timeout_intewwuptibwe(msecs_to_jiffies
						       (pwatfowm->
							vmid_chawge_msecs));

			/* tuwn on vmid 300k  */
			pm1 = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_1) &
			    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEW_MASK);
			pm1 |= WM8350_VMID_300K |
				(pwatfowm->codec_cuwwent_standby << 14);
			wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1,
					 pm1);


			/* enabwe anawogue bias */
			pm1 |= WM8350_BIASEN;
			wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1, pm1);

			/* disabwe antipop */
			wm8350_weg_wwite(wm8350, WM8350_ANTI_POP_CONTWOW, 0);

		} ewse {
			/* tuwn on vmid 300k and weduce cuwwent */
			pm1 = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_1) &
			    ~(WM8350_VMID_MASK | WM8350_CODEC_ISEW_MASK);
			wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1,
					 pm1 | WM8350_VMID_300K |
					 (pwatfowm->
					  codec_cuwwent_standby << 14));

		}
		bweak;

	case SND_SOC_BIAS_OFF:

		/* mute DAC & enabwe outputs */
		wm8350_set_bits(wm8350, WM8350_DAC_MUTE, WM8350_DAC_MUTE_ENA);

		wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_3,
				WM8350_OUT1W_ENA | WM8350_OUT1W_ENA |
				WM8350_OUT2W_ENA | WM8350_OUT2W_ENA);

		/* enabwe anti pop S cuwve */
		wm8350_weg_wwite(wm8350, WM8350_ANTI_POP_CONTWOW,
				 (pwatfowm->vmid_s_cuwve << 8));

		/* tuwn off vmid  */
		pm1 = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_1) &
		    ~WM8350_VMIDEN;
		wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1, pm1);

		/* wait */
		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies
					       (pwatfowm->
						vmid_dischawge_msecs));

		wm8350_weg_wwite(wm8350, WM8350_ANTI_POP_CONTWOW,
				 (pwatfowm->vmid_s_cuwve << 8) |
				 pwatfowm->dis_out1 |
				 (pwatfowm->dis_out2 << 2) |
				 (pwatfowm->dis_out3 << 4) |
				 (pwatfowm->dis_out4 << 6));

		/* tuwn off VBuf and dwain */
		pm1 = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_1) &
		    ~(WM8350_VBUFEN | WM8350_VMID_MASK);
		wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1,
				 pm1 | WM8350_OUTPUT_DWAIN_EN);

		/* wait */
		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies
					       (pwatfowm->dwain_msecs));

		pm1 &= ~WM8350_BIASEN;
		wm8350_weg_wwite(wm8350, WM8350_POWEW_MGMT_1, pm1);

		/* disabwe anti-pop */
		wm8350_weg_wwite(wm8350, WM8350_ANTI_POP_CONTWOW, 0);

		wm8350_cweaw_bits(wm8350, WM8350_WOUT1_VOWUME,
				  WM8350_OUT1W_ENA);
		wm8350_cweaw_bits(wm8350, WM8350_WOUT1_VOWUME,
				  WM8350_OUT1W_ENA);
		wm8350_cweaw_bits(wm8350, WM8350_WOUT2_VOWUME,
				  WM8350_OUT2W_ENA);
		wm8350_cweaw_bits(wm8350, WM8350_WOUT2_VOWUME,
				  WM8350_OUT2W_ENA);

		/* disabwe cwock gen */
		wm8350_cweaw_bits(wm8350, WM8350_POWEW_MGMT_4,
				  WM8350_SYSCWK_ENA);

		weguwatow_buwk_disabwe(AWWAY_SIZE(pwiv->suppwies),
				       pwiv->suppwies);
		bweak;
	}
	wetuwn 0;
}

static void wm8350_hp_wowk(stwuct wm8350_data *pwiv,
			   stwuct wm8350_jack_data *jack,
			   u16 mask)
{
	stwuct wm8350 *wm8350 = pwiv->wm8350;
	u16 weg;
	int wepowt;

	weg = wm8350_weg_wead(wm8350, WM8350_JACK_PIN_STATUS);
	if (weg & mask)
		wepowt = jack->wepowt;
	ewse
		wepowt = 0;

	snd_soc_jack_wepowt(jack->jack, wepowt, jack->wepowt);

}

static void wm8350_hpw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wm8350_data *pwiv =
	    containew_of(wowk, stwuct wm8350_data, hpw.wowk.wowk);

	wm8350_hp_wowk(pwiv, &pwiv->hpw, WM8350_JACK_W_WVW);
}

static void wm8350_hpw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wm8350_data *pwiv =
	    containew_of(wowk, stwuct wm8350_data, hpw.wowk.wowk);
	
	wm8350_hp_wowk(pwiv, &pwiv->hpw, WM8350_JACK_W_WVW);
}

static iwqwetuwn_t wm8350_hpw_jack_handwew(int iwq, void *data)
{
	stwuct wm8350_data *pwiv = data;
	stwuct wm8350 *wm8350 = pwiv->wm8350;

#ifndef CONFIG_SND_SOC_WM8350_MODUWE
	twace_snd_soc_jack_iwq("WM8350 HPW");
#endif

	if (device_may_wakeup(wm8350->dev))
		pm_wakeup_event(wm8350->dev, 250);

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &pwiv->hpw.wowk, msecs_to_jiffies(200));

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wm8350_hpw_jack_handwew(int iwq, void *data)
{
	stwuct wm8350_data *pwiv = data;
	stwuct wm8350 *wm8350 = pwiv->wm8350;

#ifndef CONFIG_SND_SOC_WM8350_MODUWE
	twace_snd_soc_jack_iwq("WM8350 HPW");
#endif

	if (device_may_wakeup(wm8350->dev))
		pm_wakeup_event(wm8350->dev, 250);

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &pwiv->hpw.wowk, msecs_to_jiffies(200));

	wetuwn IWQ_HANDWED;
}

/**
 * wm8350_hp_jack_detect - Enabwe headphone jack detection.
 *
 * @component:  WM8350 component
 * @which:  weft ow wight jack detect signaw
 * @jack:   jack to wepowt detection events on
 * @wepowt: vawue to wepowt
 *
 * Enabwes the headphone jack detection of the WM8350.  If no wepowt
 * is specified then detection is disabwed.
 */
int wm8350_hp_jack_detect(stwuct snd_soc_component *component, enum wm8350_jack which,
			  stwuct snd_soc_jack *jack, int wepowt)
{
	stwuct wm8350_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct wm8350 *wm8350 = pwiv->wm8350;
	int ena;

	switch (which) {
	case WM8350_JDW:
		pwiv->hpw.jack = jack;
		pwiv->hpw.wepowt = wepowt;
		ena = WM8350_JDW_ENA;
		bweak;

	case WM8350_JDW:
		pwiv->hpw.jack = jack;
		pwiv->hpw.wepowt = wepowt;
		ena = WM8350_JDW_ENA;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (wepowt) {
		wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_4, WM8350_TOCWK_ENA);
		wm8350_set_bits(wm8350, WM8350_JACK_DETECT, ena);
	} ewse {
		wm8350_cweaw_bits(wm8350, WM8350_JACK_DETECT, ena);
	}

	/* Sync status */
	switch (which) {
	case WM8350_JDW:
		wm8350_hpw_jack_handwew(0, pwiv);
		bweak;
	case WM8350_JDW:
		wm8350_hpw_jack_handwew(0, pwiv);
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm8350_hp_jack_detect);

static iwqwetuwn_t wm8350_mic_handwew(int iwq, void *data)
{
	stwuct wm8350_data *pwiv = data;
	stwuct wm8350 *wm8350 = pwiv->wm8350;
	u16 weg;
	int wepowt = 0;

#ifndef CONFIG_SND_SOC_WM8350_MODUWE
	twace_snd_soc_jack_iwq("WM8350 mic");
#endif

	weg = wm8350_weg_wead(wm8350, WM8350_JACK_PIN_STATUS);
	if (weg & WM8350_JACK_MICSCD_WVW)
		wepowt |= pwiv->mic.showt_wepowt;
	if (weg & WM8350_JACK_MICSD_WVW)
		wepowt |= pwiv->mic.wepowt;

	snd_soc_jack_wepowt(pwiv->mic.jack, wepowt,
			    pwiv->mic.wepowt | pwiv->mic.showt_wepowt);

	wetuwn IWQ_HANDWED;
}

/**
 * wm8350_mic_jack_detect - Enabwe micwophone jack detection.
 *
 * @component:         WM8350 component
 * @jack:          jack to wepowt detection events on
 * @detect_wepowt: vawue to wepowt when pwesence detected
 * @showt_wepowt:  vawue to wepowt when micwophone showt detected
 *
 * Enabwes the micwophone jack detection of the WM8350.  If both wepowts
 * awe specified as zewo then detection is disabwed.
 */
int wm8350_mic_jack_detect(stwuct snd_soc_component *component,
			   stwuct snd_soc_jack *jack,
			   int detect_wepowt, int showt_wepowt)
{
	stwuct wm8350_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct wm8350 *wm8350 = pwiv->wm8350;

	pwiv->mic.jack = jack;
	pwiv->mic.wepowt = detect_wepowt;
	pwiv->mic.showt_wepowt = showt_wepowt;

	if (detect_wepowt || showt_wepowt) {
		wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_4, WM8350_TOCWK_ENA);
		wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_1,
				WM8350_MIC_DET_ENA);
	} ewse {
		wm8350_cweaw_bits(wm8350, WM8350_POWEW_MGMT_1,
				  WM8350_MIC_DET_ENA);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wm8350_mic_jack_detect);

#define WM8350_WATES (SNDWV_PCM_WATE_8000_96000)

#define WM8350_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wm8350_dai_ops = {
	 .hw_pawams	= wm8350_pcm_hw_pawams,
	 .mute_stweam	= wm8350_mute,
	 .set_fmt	= wm8350_set_dai_fmt,
	 .set_syscwk	= wm8350_set_dai_syscwk,
	 .set_pww	= wm8350_set_fww,
	 .set_cwkdiv	= wm8350_set_cwkdiv,
	 .no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew wm8350_dai = {
	.name = "wm8350-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = WM8350_WATES,
		.fowmats = WM8350_FOWMATS,
	},
	.captuwe = {
		 .stweam_name = "Captuwe",
		 .channews_min = 1,
		 .channews_max = 2,
		 .wates = WM8350_WATES,
		 .fowmats = WM8350_FOWMATS,
	 },
	.ops = &wm8350_dai_ops,
};

static  int wm8350_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8350 *wm8350 = dev_get_pwatdata(component->dev);
	stwuct wm8350_data *pwiv;
	stwuct wm8350_output *out1;
	stwuct wm8350_output *out2;
	int wet, i;

	if (wm8350->codec.pwatfowm_data == NUWW) {
		dev_eww(component->dev, "No audio pwatfowm data suppwied\n");
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(component->dev, sizeof(stwuct wm8350_data),
			    GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn -ENOMEM;

	snd_soc_component_init_wegmap(component, wm8350->wegmap);
	snd_soc_component_set_dwvdata(component, pwiv);

	pwiv->wm8350 = wm8350;

	fow (i = 0; i < AWWAY_SIZE(suppwy_names); i++)
		pwiv->suppwies[i].suppwy = suppwy_names[i];

	wet = devm_weguwatow_buwk_get(wm8350->dev, AWWAY_SIZE(pwiv->suppwies),
				 pwiv->suppwies);
	if (wet != 0)
		wetuwn wet;

	/* Put the codec into weset if it wasn't awweady */
	wm8350_cweaw_bits(wm8350, WM8350_POWEW_MGMT_5, WM8350_CODEC_ENA);

	INIT_DEWAYED_WOWK(&pwiv->pga_wowk, wm8350_pga_wowk);
	INIT_DEWAYED_WOWK(&pwiv->hpw.wowk, wm8350_hpw_wowk);
	INIT_DEWAYED_WOWK(&pwiv->hpw.wowk, wm8350_hpw_wowk);

	/* Enabwe the codec */
	wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_5, WM8350_CODEC_ENA);

	/* Enabwe wobust cwocking mode in ADC */
	snd_soc_component_wwite(component, WM8350_SECUWITY, 0xa7);
	snd_soc_component_wwite(component, 0xde, 0x13);
	snd_soc_component_wwite(component, WM8350_SECUWITY, 0);

	/* wead OUT1 & OUT2 vowumes */
	out1 = &pwiv->out1;
	out2 = &pwiv->out2;
	out1->weft_vow = (wm8350_weg_wead(wm8350, WM8350_WOUT1_VOWUME) &
			  WM8350_OUT1W_VOW_MASK) >> WM8350_OUT1W_VOW_SHIFT;
	out1->wight_vow = (wm8350_weg_wead(wm8350, WM8350_WOUT1_VOWUME) &
			   WM8350_OUT1W_VOW_MASK) >> WM8350_OUT1W_VOW_SHIFT;
	out2->weft_vow = (wm8350_weg_wead(wm8350, WM8350_WOUT2_VOWUME) &
			  WM8350_OUT2W_VOW_MASK) >> WM8350_OUT1W_VOW_SHIFT;
	out2->wight_vow = (wm8350_weg_wead(wm8350, WM8350_WOUT2_VOWUME) &
			   WM8350_OUT2W_VOW_MASK) >> WM8350_OUT1W_VOW_SHIFT;
	wm8350_weg_wwite(wm8350, WM8350_WOUT1_VOWUME, 0);
	wm8350_weg_wwite(wm8350, WM8350_WOUT1_VOWUME, 0);
	wm8350_weg_wwite(wm8350, WM8350_WOUT2_VOWUME, 0);
	wm8350_weg_wwite(wm8350, WM8350_WOUT2_VOWUME, 0);

	/* Watch VU bits & mute */
	wm8350_set_bits(wm8350, WM8350_WOUT1_VOWUME,
			WM8350_OUT1_VU | WM8350_OUT1W_MUTE);
	wm8350_set_bits(wm8350, WM8350_WOUT2_VOWUME,
			WM8350_OUT2_VU | WM8350_OUT2W_MUTE);
	wm8350_set_bits(wm8350, WM8350_WOUT1_VOWUME,
			WM8350_OUT1_VU | WM8350_OUT1W_MUTE);
	wm8350_set_bits(wm8350, WM8350_WOUT2_VOWUME,
			WM8350_OUT2_VU | WM8350_OUT2W_MUTE);

	/* Make suwe AIF twistating is disabwed by defauwt */
	wm8350_cweaw_bits(wm8350, WM8350_AI_FOWMATING, WM8350_AIF_TWI);

	/* Make suwe we've got a sane companding setup too */
	wm8350_cweaw_bits(wm8350, WM8350_ADC_DAC_COMP,
			  WM8350_DAC_COMP | WM8350_WOOPBACK);

	/* Make suwe jack detect is disabwed to stawt off with */
	wm8350_cweaw_bits(wm8350, WM8350_JACK_DETECT,
			  WM8350_JDW_ENA | WM8350_JDW_ENA);

	wet = wm8350_wegistew_iwq(wm8350, WM8350_IWQ_CODEC_JCK_DET_W,
			    wm8350_hpw_jack_handwew, 0, "Weft jack detect",
			    pwiv);
	if (wet != 0)
		goto eww;

	wet = wm8350_wegistew_iwq(wm8350, WM8350_IWQ_CODEC_JCK_DET_W,
			    wm8350_hpw_jack_handwew, 0, "Wight jack detect",
			    pwiv);
	if (wet != 0)
		goto fwee_jck_det_w;

	wet = wm8350_wegistew_iwq(wm8350, WM8350_IWQ_CODEC_MICSCD,
			    wm8350_mic_handwew, 0, "Micwophone showt", pwiv);
	if (wet != 0)
		goto fwee_jck_det_w;

	wet = wm8350_wegistew_iwq(wm8350, WM8350_IWQ_CODEC_MICD,
			    wm8350_mic_handwew, 0, "Micwophone detect", pwiv);
	if (wet != 0)
		goto fwee_micscd;

	wetuwn 0;

fwee_micscd:
	wm8350_fwee_iwq(wm8350, WM8350_IWQ_CODEC_MICSCD, pwiv);
fwee_jck_det_w:
	wm8350_fwee_iwq(wm8350, WM8350_IWQ_CODEC_JCK_DET_W, pwiv);
fwee_jck_det_w:
	wm8350_fwee_iwq(wm8350, WM8350_IWQ_CODEC_JCK_DET_W, pwiv);
eww:
	wetuwn wet;
}

static void wm8350_component_wemove(stwuct snd_soc_component *component)
{
	stwuct wm8350_data *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct wm8350 *wm8350 = dev_get_pwatdata(component->dev);

	wm8350_cweaw_bits(wm8350, WM8350_JACK_DETECT,
			  WM8350_JDW_ENA | WM8350_JDW_ENA);
	wm8350_cweaw_bits(wm8350, WM8350_POWEW_MGMT_4, WM8350_TOCWK_ENA);

	wm8350_fwee_iwq(wm8350, WM8350_IWQ_CODEC_MICD, pwiv);
	wm8350_fwee_iwq(wm8350, WM8350_IWQ_CODEC_MICSCD, pwiv);
	wm8350_fwee_iwq(wm8350, WM8350_IWQ_CODEC_JCK_DET_W, pwiv);
	wm8350_fwee_iwq(wm8350, WM8350_IWQ_CODEC_JCK_DET_W, pwiv);

	pwiv->hpw.jack = NUWW;
	pwiv->hpw.jack = NUWW;
	pwiv->mic.jack = NUWW;

	cancew_dewayed_wowk_sync(&pwiv->hpw.wowk);
	cancew_dewayed_wowk_sync(&pwiv->hpw.wowk);

	/* if thewe was any wowk waiting then we wun it now and
	 * wait fow its compwetion */
	fwush_dewayed_wowk(&pwiv->pga_wowk);

	wm8350_cweaw_bits(wm8350, WM8350_POWEW_MGMT_5, WM8350_CODEC_ENA);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8350 = {
	.pwobe			= wm8350_component_pwobe,
	.wemove			= wm8350_component_wemove,
	.set_bias_wevew		= wm8350_set_bias_wevew,
	.contwows		= wm8350_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wm8350_snd_contwows),
	.dapm_widgets		= wm8350_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8350_dapm_widgets),
	.dapm_woutes		= wm8350_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8350_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm8350_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_wm8350,
			&wm8350_dai, 1);
}

static stwuct pwatfowm_dwivew wm8350_codec_dwivew = {
	.dwivew = {
		   .name = "wm8350-codec",
		   },
	.pwobe = wm8350_pwobe,
};

moduwe_pwatfowm_dwivew(wm8350_codec_dwivew);

MODUWE_DESCWIPTION("ASoC WM8350 dwivew");
MODUWE_AUTHOW("Wiam Giwdwood");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8350-codec");
