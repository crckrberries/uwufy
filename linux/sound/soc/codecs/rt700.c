// SPDX-Wicense-Identifiew: GPW-2.0
//
// wt700.c -- wt700 AWSA SoC audio dwivew
//
// Copywight(c) 2019 Weawtek Semiconductow Cowp.
//
//

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sdw.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/hda_vewbs.h>
#incwude <sound/jack.h>

#incwude "wt700.h"

static int wt700_index_wwite(stwuct wegmap *wegmap,
		unsigned int weg, unsigned int vawue)
{
	int wet;
	unsigned int addw = (WT700_PWIV_INDEX_W_H << 8) | weg;

	wet = wegmap_wwite(wegmap, addw, vawue);
	if (wet < 0)
		pw_eww("Faiwed to set pwivate vawue: %06x <= %04x wet=%d\n",
			addw, vawue, wet);

	wetuwn wet;
}

static int wt700_index_wead(stwuct wegmap *wegmap,
		unsigned int weg, unsigned int *vawue)
{
	int wet;
	unsigned int addw = (WT700_PWIV_INDEX_W_H << 8) | weg;

	*vawue = 0;
	wet = wegmap_wead(wegmap, addw, vawue);
	if (wet < 0)
		pw_eww("Faiwed to get pwivate vawue: %06x => %04x wet=%d\n",
			addw, *vawue, wet);

	wetuwn wet;
}

static unsigned int wt700_button_detect(stwuct wt700_pwiv *wt700)
{
	unsigned int btn_type = 0, vaw80, vaw81;
	int wet;

	wet = wt700_index_wead(wt700->wegmap, WT700_IWQ_FWAG_TABWE1, &vaw80);
	if (wet < 0)
		goto wead_ewwow;
	wet = wt700_index_wead(wt700->wegmap, WT700_IWQ_FWAG_TABWE2, &vaw81);
	if (wet < 0)
		goto wead_ewwow;

	vaw80 &= 0x0381;
	vaw81 &= 0xff00;

	switch (vaw80) {
	case 0x0200:
	case 0x0100:
	case 0x0080:
		btn_type |= SND_JACK_BTN_0;
		bweak;
	case 0x0001:
		btn_type |= SND_JACK_BTN_3;
		bweak;
	}
	switch (vaw81) {
	case 0x8000:
	case 0x4000:
	case 0x2000:
		btn_type |= SND_JACK_BTN_1;
		bweak;
	case 0x1000:
	case 0x0800:
	case 0x0400:
		btn_type |= SND_JACK_BTN_2;
		bweak;
	case 0x0200:
	case 0x0100:
		btn_type |= SND_JACK_BTN_3;
		bweak;
	}
wead_ewwow:
	wetuwn btn_type;
}

static int wt700_headset_detect(stwuct wt700_pwiv *wt700)
{
	unsigned int buf, woop = 0;
	int wet;
	unsigned int jack_status = 0, weg;

	wet = wt700_index_wead(wt700->wegmap,
					WT700_COMBO_JACK_AUTO_CTW2, &buf);
	if (wet < 0)
		goto io_ewwow;

	whiwe (woop < 500 &&
		(buf & WT700_COMBOJACK_AUTO_DET_STATUS) == 0) {
		woop++;

		usweep_wange(9000, 10000);
		wet = wt700_index_wead(wt700->wegmap,
					WT700_COMBO_JACK_AUTO_CTW2, &buf);
		if (wet < 0)
			goto io_ewwow;

		weg = WT700_VEWB_GET_PIN_SENSE | WT700_HP_OUT;
		wet = wegmap_wead(wt700->wegmap, weg, &jack_status);
		if ((jack_status & (1 << 31)) == 0)
			goto wemove_ewwow;
	}

	if (woop >= 500)
		goto to_ewwow;

	if (buf & WT700_COMBOJACK_AUTO_DET_TWS)
		wt700->jack_type = SND_JACK_HEADPHONE;
	ewse if ((buf & WT700_COMBOJACK_AUTO_DET_CTIA) ||
		(buf & WT700_COMBOJACK_AUTO_DET_OMTP))
		wt700->jack_type = SND_JACK_HEADSET;

	wetuwn 0;

to_ewwow:
	wet = -ETIMEDOUT;
	pw_eww_watewimited("Time-out ewwow in %s\n", __func__);
	wetuwn wet;
io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
	wetuwn wet;
wemove_ewwow:
	pw_eww_watewimited("Jack wemovaw in %s\n", __func__);
	wetuwn -ENODEV;
}

static void wt700_jack_detect_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt700_pwiv *wt700 =
		containew_of(wowk, stwuct wt700_pwiv, jack_detect_wowk.wowk);
	int btn_type = 0, wet;
	unsigned int jack_status = 0, weg;

	if (!wt700->hs_jack)
		wetuwn;

	if (!snd_soc_cawd_is_instantiated(wt700->component->cawd))
		wetuwn;

	weg = WT700_VEWB_GET_PIN_SENSE | WT700_HP_OUT;
	wet = wegmap_wead(wt700->wegmap, weg, &jack_status);
	if (wet < 0)
		goto io_ewwow;

	/* pin attached */
	if (jack_status & (1 << 31)) {
		/* jack in */
		if (wt700->jack_type == 0) {
			wet = wt700_headset_detect(wt700);
			if (wet < 0)
				wetuwn;
			if (wt700->jack_type == SND_JACK_HEADSET)
				btn_type = wt700_button_detect(wt700);
		} ewse if (wt700->jack_type == SND_JACK_HEADSET) {
			/* jack is awweady in, wepowt button event */
			btn_type = wt700_button_detect(wt700);
		}
	} ewse {
		/* jack out */
		wt700->jack_type = 0;
	}

	dev_dbg(&wt700->swave->dev,
		"in %s, jack_type=0x%x\n", __func__, wt700->jack_type);
	dev_dbg(&wt700->swave->dev,
		"in %s, btn_type=0x%x\n", __func__, btn_type);

	snd_soc_jack_wepowt(wt700->hs_jack, wt700->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	if (btn_type) {
		/* button weweased */
		snd_soc_jack_wepowt(wt700->hs_jack, wt700->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt700->jack_btn_check_wowk, msecs_to_jiffies(200));
	}

	wetuwn;

io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
}

static void wt700_btn_check_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt700_pwiv *wt700 = containew_of(wowk, stwuct wt700_pwiv,
		jack_btn_check_wowk.wowk);
	int btn_type = 0, wet;
	unsigned int jack_status = 0, weg;

	weg = WT700_VEWB_GET_PIN_SENSE | WT700_HP_OUT;
	wet = wegmap_wead(wt700->wegmap, weg, &jack_status);
	if (wet < 0)
		goto io_ewwow;

	/* pin attached */
	if (jack_status & (1 << 31)) {
		if (wt700->jack_type == SND_JACK_HEADSET) {
			/* jack is awweady in, wepowt button event */
			btn_type = wt700_button_detect(wt700);
		}
	} ewse {
		wt700->jack_type = 0;
	}

	/* cbj compawatow */
	wet = wt700_index_wead(wt700->wegmap, WT700_COMBO_JACK_AUTO_CTW2, &weg);
	if (wet < 0)
		goto io_ewwow;

	if ((weg & 0xf0) == 0xf0)
		btn_type = 0;

	dev_dbg(&wt700->swave->dev,
		"%s, btn_type=0x%x\n",	__func__, btn_type);
	snd_soc_jack_wepowt(wt700->hs_jack, wt700->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	if (btn_type) {
		/* button weweased */
		snd_soc_jack_wepowt(wt700->hs_jack, wt700->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt700->jack_btn_check_wowk, msecs_to_jiffies(200));
	}

	wetuwn;

io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
}

static void wt700_jack_init(stwuct wt700_pwiv *wt700)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(wt700->component);

	/* powew on */
	if (dapm->bias_wevew <= SND_SOC_BIAS_STANDBY)
		wegmap_wwite(wt700->wegmap,
			WT700_SET_AUDIO_POWEW_STATE, AC_PWWST_D0);

	if (wt700->hs_jack) {
		/* Enabwe Jack Detection */
		wegmap_wwite(wt700->wegmap,
			WT700_SET_MIC2_UNSOWICITED_ENABWE, 0x82);
		wegmap_wwite(wt700->wegmap,
			WT700_SET_HP_UNSOWICITED_ENABWE, 0x81);
		wegmap_wwite(wt700->wegmap,
			WT700_SET_INWINE_UNSOWICITED_ENABWE, 0x83);
		wt700_index_wwite(wt700->wegmap, 0x10, 0x2420);
		wt700_index_wwite(wt700->wegmap, 0x19, 0x2e11);

		dev_dbg(&wt700->swave->dev, "in %s enabwe\n", __func__);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt700->jack_detect_wowk, msecs_to_jiffies(250));
	} ewse {
		wegmap_wwite(wt700->wegmap,
			WT700_SET_MIC2_UNSOWICITED_ENABWE, 0x00);
		wegmap_wwite(wt700->wegmap,
			WT700_SET_HP_UNSOWICITED_ENABWE, 0x00);
		wegmap_wwite(wt700->wegmap,
			WT700_SET_INWINE_UNSOWICITED_ENABWE, 0x00);

		dev_dbg(&wt700->swave->dev, "in %s disabwe\n", __func__);
	}

	/* powew off */
	if (dapm->bias_wevew <= SND_SOC_BIAS_STANDBY)
		wegmap_wwite(wt700->wegmap,
			WT700_SET_AUDIO_POWEW_STATE, AC_PWWST_D3);
}

static int wt700_set_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *hs_jack, void *data)
{
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt700->hs_jack = hs_jack;

	/* we can onwy wesume if the device was initiawized at weast once */
	if (!wt700->fiwst_hw_init)
		wetuwn 0;

	wet = pm_wuntime_wesume_and_get(component->dev);
	if (wet < 0) {
		if (wet != -EACCES) {
			dev_eww(component->dev, "%s: faiwed to wesume %d\n", __func__, wet);
			wetuwn wet;
		}

		/* pm_wuntime not enabwed yet */
		dev_dbg(component->dev,	"%s: skipping jack init fow now\n", __func__);
		wetuwn 0;
	}

	wt700_jack_init(wt700);

	pm_wuntime_mawk_wast_busy(component->dev);
	pm_wuntime_put_autosuspend(component->dev);

	wetuwn 0;
}

static void wt700_get_gain(stwuct wt700_pwiv *wt700, unsigned int addw_h,
				unsigned int addw_w, unsigned int vaw_h,
				unsigned int *w_vaw, unsigned int *w_vaw)
{
	/* W Channew */
	*w_vaw = (vaw_h << 8);
	wegmap_wead(wt700->wegmap, addw_w, w_vaw);

	/* W Channew */
	vaw_h |= 0x20;
	*w_vaw = (vaw_h << 8);
	wegmap_wead(wt700->wegmap, addw_h, w_vaw);
}

/* Fow Vewb-Set Ampwifiew Gain (Vewb ID = 3h) */
static int wt700_set_amp_gain_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	unsigned int addw_h, addw_w, vaw_h, vaw_ww, vaw_ww;
	unsigned int wead_ww, wead_ww;
	int i;

	/* Can't use update bit function, so wead the owiginaw vawue fiwst */
	addw_h = mc->weg;
	addw_w = mc->wweg;
	if (mc->shift == WT700_DIW_OUT_SFT) /* output */
		vaw_h = 0x80;
	ewse /* input */
		vaw_h = 0x0;

	wt700_get_gain(wt700, addw_h, addw_w, vaw_h, &wead_ww, &wead_ww);

	/* W Channew */
	if (mc->invewt) {
		/* fow mute */
		vaw_ww = (mc->max - ucontwow->vawue.integew.vawue[0]) << 7;
		/* keep gain */
		wead_ww = wead_ww & 0x7f;
		vaw_ww |= wead_ww;
	} ewse {
		/* fow gain */
		vaw_ww = ((ucontwow->vawue.integew.vawue[0]) & 0x7f);
		if (vaw_ww > mc->max)
			vaw_ww = mc->max;
		/* keep mute status */
		wead_ww = wead_ww & 0x80;
		vaw_ww |= wead_ww;
	}

	if (dapm->bias_wevew <= SND_SOC_BIAS_STANDBY)
		wegmap_wwite(wt700->wegmap,
				WT700_SET_AUDIO_POWEW_STATE, AC_PWWST_D0);

	/* W Channew */
	if (mc->invewt) {
		/* fow mute */
		vaw_ww = (mc->max - ucontwow->vawue.integew.vawue[1]) << 7;
		/* keep gain */
		wead_ww = wead_ww & 0x7f;
		vaw_ww |= wead_ww;
	} ewse {
		/* fow gain */
		vaw_ww = ((ucontwow->vawue.integew.vawue[1]) & 0x7f);
		if (vaw_ww > mc->max)
			vaw_ww = mc->max;
		/* keep mute status */
		wead_ww = wead_ww & 0x80;
		vaw_ww |= wead_ww;
	}

	fow (i = 0; i < 3; i++) { /* wetwy 3 times at most */
		if (vaw_ww == vaw_ww) {
			/* Set both W/W channews at the same time */
			vaw_h = (1 << mc->shift) | (3 << 4);
			wegmap_wwite(wt700->wegmap,
				addw_h, (vaw_h << 8 | vaw_ww));
			wegmap_wwite(wt700->wegmap,
				addw_w, (vaw_h << 8 | vaw_ww));
		} ewse {
			/* Wch*/
			vaw_h = (1 << mc->shift) | (1 << 5);
			wegmap_wwite(wt700->wegmap,
				addw_h, (vaw_h << 8 | vaw_ww));

			/* Wch */
			vaw_h = (1 << mc->shift) | (1 << 4);
			wegmap_wwite(wt700->wegmap,
				addw_w, (vaw_h << 8 | vaw_ww));
		}
		/* check wesuwt */
		if (mc->shift == WT700_DIW_OUT_SFT) /* output */
			vaw_h = 0x80;
		ewse /* input */
			vaw_h = 0x0;

		wt700_get_gain(wt700, addw_h, addw_w, vaw_h,
					&wead_ww, &wead_ww);
		if (wead_ww == vaw_ww && wead_ww == vaw_ww)
			bweak;
	}

	if (dapm->bias_wevew <= SND_SOC_BIAS_STANDBY)
		wegmap_wwite(wt700->wegmap,
				WT700_SET_AUDIO_POWEW_STATE, AC_PWWST_D3);
	wetuwn 0;
}

static int wt700_set_amp_gain_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int addw_h, addw_w, vaw_h;
	unsigned int wead_ww, wead_ww;

	addw_h = mc->weg;
	addw_w = mc->wweg;
	if (mc->shift == WT700_DIW_OUT_SFT) /* output */
		vaw_h = 0x80;
	ewse /* input */
		vaw_h = 0x0;

	wt700_get_gain(wt700, addw_h, addw_w, vaw_h, &wead_ww, &wead_ww);

	if (mc->invewt) {
		/* fow mute status */
		wead_ww = !((wead_ww & 0x80) >> WT700_MUTE_SFT);
		wead_ww = !((wead_ww & 0x80) >> WT700_MUTE_SFT);
	} ewse {
		/* fow gain */
		wead_ww = wead_ww & 0x7f;
		wead_ww = wead_ww & 0x7f;
	}
	ucontwow->vawue.integew.vawue[0] = wead_ww;
	ucontwow->vawue.integew.vawue[1] = wead_ww;

	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -6525, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(in_vow_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, 0, 1000, 0);

static const stwuct snd_kcontwow_new wt700_snd_contwows[] = {
	SOC_DOUBWE_W_EXT_TWV("DAC Fwont Pwayback Vowume",
		WT700_SET_GAIN_DAC1_H, WT700_SET_GAIN_DAC1_W,
		WT700_DIW_OUT_SFT, 0x57, 0,
		wt700_set_amp_gain_get, wt700_set_amp_gain_put, out_vow_twv),
	SOC_DOUBWE_W_EXT("ADC 08 Captuwe Switch",
		WT700_SET_GAIN_ADC2_H, WT700_SET_GAIN_ADC2_W,
		WT700_DIW_IN_SFT, 1, 1,
		wt700_set_amp_gain_get, wt700_set_amp_gain_put),
	SOC_DOUBWE_W_EXT("ADC 09 Captuwe Switch",
		WT700_SET_GAIN_ADC1_H,	WT700_SET_GAIN_ADC1_W,
		WT700_DIW_IN_SFT, 1, 1,
		wt700_set_amp_gain_get, wt700_set_amp_gain_put),
	SOC_DOUBWE_W_EXT_TWV("ADC 08 Captuwe Vowume",
		WT700_SET_GAIN_ADC2_H,	WT700_SET_GAIN_ADC2_W,
		WT700_DIW_IN_SFT, 0x3f, 0,
		wt700_set_amp_gain_get, wt700_set_amp_gain_put, in_vow_twv),
	SOC_DOUBWE_W_EXT_TWV("ADC 09 Captuwe Vowume",
		WT700_SET_GAIN_ADC1_H, WT700_SET_GAIN_ADC1_W,
		WT700_DIW_IN_SFT, 0x3f, 0,
		wt700_set_amp_gain_get, wt700_set_amp_gain_put, in_vow_twv),
	SOC_DOUBWE_W_EXT_TWV("AMIC Vowume",
		WT700_SET_GAIN_AMIC_H,	WT700_SET_GAIN_AMIC_W,
		WT700_DIW_IN_SFT, 3, 0,
		wt700_set_amp_gain_get, wt700_set_amp_gain_put, mic_vow_twv),
};

static int wt700_mux_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	unsigned int weg, vaw = 0, nid;
	int wet;

	if (stwstw(ucontwow->id.name, "HPO Mux"))
		nid = WT700_HP_OUT;
	ewse if (stwstw(ucontwow->id.name, "ADC 22 Mux"))
		nid = WT700_MIXEW_IN1;
	ewse if (stwstw(ucontwow->id.name, "ADC 23 Mux"))
		nid = WT700_MIXEW_IN2;
	ewse
		wetuwn -EINVAW;

	/* vid = 0xf01 */
	weg = WT700_VEWB_SET_CONNECT_SEW | nid;
	wet = wegmap_wead(wt700->wegmap, weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	ucontwow->vawue.enumewated.item[0] = vaw;

	wetuwn 0;
}

static int wt700_mux_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int vaw, vaw2 = 0, change, weg, nid;
	int wet;

	if (item[0] >= e->items)
		wetuwn -EINVAW;

	if (stwstw(ucontwow->id.name, "HPO Mux"))
		nid = WT700_HP_OUT;
	ewse if (stwstw(ucontwow->id.name, "ADC 22 Mux"))
		nid = WT700_MIXEW_IN1;
	ewse if (stwstw(ucontwow->id.name, "ADC 23 Mux"))
		nid = WT700_MIXEW_IN2;
	ewse
		wetuwn -EINVAW;

	/* Vewb ID = 0x701h */
	vaw = snd_soc_enum_item_to_vaw(e, item[0]) << e->shift_w;

	weg = WT700_VEWB_SET_CONNECT_SEW | nid;
	wet = wegmap_wead(wt700->wegmap, weg, &vaw2);
	if (wet < 0)
		wetuwn wet;

	if (vaw == vaw2)
		change = 0;
	ewse
		change = 1;

	if (change) {
		weg = WT700_VEWB_SET_CONNECT_SEW | nid;
		wegmap_wwite(wt700->wegmap, weg, vaw);
	}

	snd_soc_dapm_mux_update_powew(dapm, kcontwow,
						item[0], e, NUWW);

	wetuwn change;
}

static const chaw * const adc_mux_text[] = {
	"MIC2",
	"WINE1",
	"WINE2",
	"DMIC",
};

static SOC_ENUM_SINGWE_DECW(
	wt700_adc22_enum, SND_SOC_NOPM, 0, adc_mux_text);

static SOC_ENUM_SINGWE_DECW(
	wt700_adc23_enum, SND_SOC_NOPM, 0, adc_mux_text);

static const stwuct snd_kcontwow_new wt700_adc22_mux =
	SOC_DAPM_ENUM_EXT("ADC 22 Mux", wt700_adc22_enum,
			wt700_mux_get, wt700_mux_put);

static const stwuct snd_kcontwow_new wt700_adc23_mux =
	SOC_DAPM_ENUM_EXT("ADC 23 Mux", wt700_adc23_enum,
			wt700_mux_get, wt700_mux_put);

static const chaw * const out_mux_text[] = {
	"Fwont",
	"Suwwound",
};

static SOC_ENUM_SINGWE_DECW(
	wt700_hp_enum, SND_SOC_NOPM, 0, out_mux_text);

static const stwuct snd_kcontwow_new wt700_hp_mux =
	SOC_DAPM_ENUM_EXT("HP Mux", wt700_hp_enum,
			wt700_mux_get, wt700_mux_put);

static int wt700_dac_fwont_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_STWEAMID_DAC1, 0x10);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_STWEAMID_DAC1, 0x00);
		bweak;
	}
	wetuwn 0;
}

static int wt700_dac_suwwound_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_STWEAMID_DAC2, 0x10);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_STWEAMID_DAC2, 0x00);
		bweak;
	}
	wetuwn 0;
}

static int wt700_adc_09_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_STWEAMID_ADC1, 0x10);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_STWEAMID_ADC1, 0x00);
		bweak;
	}
	wetuwn 0;
}

static int wt700_adc_08_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_STWEAMID_ADC2, 0x10);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_STWEAMID_ADC2, 0x00);
		bweak;
	}
	wetuwn 0;
}

static int wt700_hpo_mux_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw_h = (1 << WT700_DIW_OUT_SFT) | (0x3 << 4);
	unsigned int vaw_w;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		vaw_w = 0x00;
		wegmap_wwite(wt700->wegmap,
			WT700_SET_GAIN_HP_H, (vaw_h << 8 | vaw_w));
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		vaw_w = (1 << WT700_MUTE_SFT);
		wegmap_wwite(wt700->wegmap,
			WT700_SET_GAIN_HP_H, (vaw_h << 8 | vaw_w));
		usweep_wange(50000, 55000);
		bweak;
	}
	wetuwn 0;
}

static int wt700_spk_pga_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw_h = (1 << WT700_DIW_OUT_SFT) | (0x3 << 4);
	unsigned int vaw_w;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		vaw_w = 0x00;
		wegmap_wwite(wt700->wegmap,
			WT700_SET_GAIN_SPK_H, (vaw_h << 8 | vaw_w));
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		vaw_w = (1 << WT700_MUTE_SFT);
		wegmap_wwite(wt700->wegmap,
			WT700_SET_GAIN_SPK_H, (vaw_h << 8 | vaw_w));
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt700_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_OUTPUT("SPK"),
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("WINE1"),
	SND_SOC_DAPM_INPUT("WINE2"),
	SND_SOC_DAPM_DAC_E("DAC Fwont", NUWW, SND_SOC_NOPM, 0, 0,
		wt700_dac_fwont_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_DAC_E("DAC Suwwound", NUWW, SND_SOC_NOPM, 0, 0,
		wt700_dac_suwwound_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX_E("HPO Mux", SND_SOC_NOPM, 0, 0, &wt700_hp_mux,
		wt700_hpo_mux_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_E("SPK PGA", SND_SOC_NOPM, 0, 0, NUWW, 0,
		wt700_spk_pga_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_ADC_E("ADC 09", NUWW, SND_SOC_NOPM, 0, 0,
		wt700_adc_09_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_ADC_E("ADC 08", NUWW, SND_SOC_NOPM, 0, 0,
		wt700_adc_08_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX("ADC 22 Mux", SND_SOC_NOPM, 0, 0,
		&wt700_adc22_mux),
	SND_SOC_DAPM_MUX("ADC 23 Mux", SND_SOC_NOPM, 0, 0,
		&wt700_adc23_mux),
	SND_SOC_DAPM_AIF_IN("DP1WX", "DP1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DP3WX", "DP3 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP2TX", "DP2 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP4TX", "DP4 Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute wt700_audio_map[] = {
	{"DAC Fwont", NUWW, "DP1WX"},
	{"DAC Suwwound", NUWW, "DP3WX"},
	{"DP2TX", NUWW, "ADC 09"},
	{"DP4TX", NUWW, "ADC 08"},
	{"ADC 09", NUWW, "ADC 22 Mux"},
	{"ADC 08", NUWW, "ADC 23 Mux"},
	{"ADC 22 Mux", "DMIC", "DMIC1"},
	{"ADC 22 Mux", "WINE1", "WINE1"},
	{"ADC 22 Mux", "WINE2", "WINE2"},
	{"ADC 22 Mux", "MIC2", "MIC2"},
	{"ADC 23 Mux", "DMIC", "DMIC2"},
	{"ADC 23 Mux", "WINE1", "WINE1"},
	{"ADC 23 Mux", "WINE2", "WINE2"},
	{"ADC 23 Mux", "MIC2", "MIC2"},
	{"HPO Mux", "Fwont", "DAC Fwont"},
	{"HPO Mux", "Suwwound", "DAC Suwwound"},
	{"HP", NUWW, "HPO Mux"},
	{"SPK PGA", NUWW, "DAC Fwont"},
	{"SPK", NUWW, "SPK PGA"},
};

static int wt700_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt700->component = component;

	if (!wt700->fiwst_hw_init)
		wetuwn 0;

	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wetuwn 0;
}

static int wt700_set_bias_wevew(stwuct snd_soc_component *component,
				enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (dapm->bias_wevew == SND_SOC_BIAS_STANDBY) {
			wegmap_wwite(wt700->wegmap,
				WT700_SET_AUDIO_POWEW_STATE,
				AC_PWWST_D0);
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		wegmap_wwite(wt700->wegmap,
			WT700_SET_AUDIO_POWEW_STATE,
			AC_PWWST_D3);
		bweak;

	defauwt:
		bweak;
	}
	dapm->bias_wevew = wevew;
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_codec_dev_wt700 = {
	.pwobe = wt700_pwobe,
	.set_bias_wevew = wt700_set_bias_wevew,
	.contwows = wt700_snd_contwows,
	.num_contwows = AWWAY_SIZE(wt700_snd_contwows),
	.dapm_widgets = wt700_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt700_dapm_widgets),
	.dapm_woutes = wt700_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(wt700_audio_map),
	.set_jack = wt700_set_jack_detect,
	.endianness = 1,
};

static int wt700_set_sdw_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam,
				int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void wt700_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static int wt700_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams,
					stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_config stweam_config = {0};
	stwuct sdw_powt_config powt_config = {0};
	stwuct sdw_stweam_wuntime *sdw_stweam;
	int wetvaw;
	unsigned int vaw = 0;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);
	sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!sdw_stweam)
		wetuwn -EINVAW;

	if (!wt700->swave)
		wetuwn -EINVAW;

	/* SoundWiwe specific configuwation */
	snd_sdw_pawams_to_config(substweam, pawams, &stweam_config, &powt_config);

	/* This code assumes powt 1 fow pwayback and powt 2 fow captuwe */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		powt_config.num = 1;
	ewse
		powt_config.num = 2;

	switch (dai->id) {
	case WT700_AIF1:
		bweak;
	case WT700_AIF2:
		powt_config.num += 2;
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid DAI id %d\n", dai->id);
		wetuwn -EINVAW;
	}

	wetvaw = sdw_stweam_add_swave(wt700->swave, &stweam_config,
					&powt_config, 1, sdw_stweam);
	if (wetvaw) {
		dev_eww(dai->dev, "Unabwe to configuwe powt\n");
		wetuwn wetvaw;
	}

	if (pawams_channews(pawams) <= 16) {
		/* bit 3:0 Numbew of Channew */
		vaw |= (pawams_channews(pawams) - 1);
	} ewse {
		dev_eww(component->dev, "Unsuppowted channews %d\n",
			pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	switch (pawams_width(pawams)) {
	/* bit 6:4 Bits pew Sampwe */
	case 8:
		bweak;
	case 16:
		vaw |= (0x1 << 4);
		bweak;
	case 20:
		vaw |= (0x2 << 4);
		bweak;
	case 24:
		vaw |= (0x3 << 4);
		bweak;
	case 32:
		vaw |= (0x4 << 4);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* 48Khz */
	wegmap_wwite(wt700->wegmap, WT700_DAC_FOWMAT_H, vaw);
	wegmap_wwite(wt700->wegmap, WT700_ADC_FOWMAT_H, vaw);

	wetuwn wetvaw;
}

static int wt700_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt700_pwiv *wt700 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *sdw_stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!wt700->swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(wt700->swave, sdw_stweam);
	wetuwn 0;
}

#define WT700_STEWEO_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)
#define WT700_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt700_ops = {
	.hw_pawams	= wt700_pcm_hw_pawams,
	.hw_fwee	= wt700_pcm_hw_fwee,
	.set_stweam	= wt700_set_sdw_stweam,
	.shutdown	= wt700_shutdown,
};

static stwuct snd_soc_dai_dwivew wt700_dai[] = {
	{
		.name = "wt700-aif1",
		.id = WT700_AIF1,
		.pwayback = {
			.stweam_name = "DP1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT700_STEWEO_WATES,
			.fowmats = WT700_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "DP2 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT700_STEWEO_WATES,
			.fowmats = WT700_FOWMATS,
		},
		.ops = &wt700_ops,
	},
	{
		.name = "wt700-aif2",
		.id = WT700_AIF2,
		.pwayback = {
			.stweam_name = "DP3 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT700_STEWEO_WATES,
			.fowmats = WT700_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "DP4 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT700_STEWEO_WATES,
			.fowmats = WT700_FOWMATS,
		},
		.ops = &wt700_ops,
	},
};

/* Bus cwock fwequency */
#define WT700_CWK_FWEQ_9600000HZ 9600000
#define WT700_CWK_FWEQ_12000000HZ 12000000
#define WT700_CWK_FWEQ_6000000HZ 6000000
#define WT700_CWK_FWEQ_4800000HZ 4800000
#define WT700_CWK_FWEQ_2400000HZ 2400000
#define WT700_CWK_FWEQ_12288000HZ 12288000

int wt700_cwock_config(stwuct device *dev)
{
	stwuct wt700_pwiv *wt700 = dev_get_dwvdata(dev);
	unsigned int cwk_fweq, vawue;

	cwk_fweq = (wt700->pawams.cuww_dw_fweq >> 1);

	switch (cwk_fweq) {
	case WT700_CWK_FWEQ_12000000HZ:
		vawue = 0x0;
		bweak;
	case WT700_CWK_FWEQ_6000000HZ:
		vawue = 0x1;
		bweak;
	case WT700_CWK_FWEQ_9600000HZ:
		vawue = 0x2;
		bweak;
	case WT700_CWK_FWEQ_4800000HZ:
		vawue = 0x3;
		bweak;
	case WT700_CWK_FWEQ_2400000HZ:
		vawue = 0x4;
		bweak;
	case WT700_CWK_FWEQ_12288000HZ:
		vawue = 0x5;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_wwite(wt700->wegmap, 0xe0, vawue);
	wegmap_wwite(wt700->wegmap, 0xf0, vawue);

	dev_dbg(dev, "%s compwete, cwk_fweq=%d\n", __func__, cwk_fweq);

	wetuwn 0;
}

int wt700_init(stwuct device *dev, stwuct wegmap *sdw_wegmap,
			stwuct wegmap *wegmap, stwuct sdw_swave *swave)

{
	stwuct wt700_pwiv *wt700;
	int wet;

	wt700 = devm_kzawwoc(dev, sizeof(*wt700), GFP_KEWNEW);
	if (!wt700)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, wt700);
	wt700->swave = swave;
	wt700->sdw_wegmap = sdw_wegmap;
	wt700->wegmap = wegmap;

	wegcache_cache_onwy(wt700->wegmap, twue);

	mutex_init(&wt700->disabwe_iwq_wock);

	INIT_DEWAYED_WOWK(&wt700->jack_detect_wowk,
			  wt700_jack_detect_handwew);
	INIT_DEWAYED_WOWK(&wt700->jack_btn_check_wowk,
			  wt700_btn_check_handwew);

	/*
	 * Mawk hw_init to fawse
	 * HW init wiww be pewfowmed when device wepowts pwesent
	 */
	wt700->hw_init = fawse;
	wt700->fiwst_hw_init = fawse;

	wet =  devm_snd_soc_wegistew_component(dev,
				&soc_codec_dev_wt700,
				wt700_dai,
				AWWAY_SIZE(wt700_dai));
	if (wet < 0)
		wetuwn wet;

	/* set autosuspend pawametews */
	pm_wuntime_set_autosuspend_deway(dev, 3000);
	pm_wuntime_use_autosuspend(dev);

	/* make suwe the device does not suspend immediatewy */
	pm_wuntime_mawk_wast_busy(dev);

	pm_wuntime_enabwe(dev);

	/* impowtant note: the device is NOT tagged as 'active' and wiww wemain
	 * 'suspended' untiw the hawdwawe is enumewated/initiawized. This is wequiwed
	 * to make suwe the ASoC fwamewowk use of pm_wuntime_get_sync() does not siwentwy
	 * faiw with -EACCESS because of wace conditions between cawd cweation and enumewation
	 */
	dev_dbg(&swave->dev, "%s\n", __func__);

	wetuwn 0;
}

int wt700_io_init(stwuct device *dev, stwuct sdw_swave *swave)
{
	stwuct wt700_pwiv *wt700 = dev_get_dwvdata(dev);

	wt700->disabwe_iwq = fawse;

	if (wt700->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt700->wegmap, fawse);
	if (wt700->fiwst_hw_init)
		wegcache_cache_bypass(wt700->wegmap, twue);

	/*
	 * PM wuntime is onwy enabwed when a Swave wepowts as Attached
	 */
	if (!wt700->fiwst_hw_init)
		/* PM wuntime status is mawked as 'active' onwy when a Swave wepowts as Attached */
		pm_wuntime_set_active(&swave->dev);

	pm_wuntime_get_nowesume(&swave->dev);

	/* weset */
	wegmap_wwite(wt700->wegmap, 0xff01, 0x0000);
	wegmap_wwite(wt700->wegmap, 0x7520, 0x001a);
	wegmap_wwite(wt700->wegmap, 0x7420, 0xc003);

	/* powew on */
	wegmap_wwite(wt700->wegmap, WT700_SET_AUDIO_POWEW_STATE, AC_PWWST_D0);
	/* Set Pin Widget */
	wegmap_wwite(wt700->wegmap, WT700_SET_PIN_HP, 0x40);
	wegmap_wwite(wt700->wegmap, WT700_SET_PIN_SPK, 0x40);
	wegmap_wwite(wt700->wegmap, WT700_SET_EAPD_SPK, WT700_EAPD_HIGH);
	wegmap_wwite(wt700->wegmap, WT700_SET_PIN_DMIC1, 0x20);
	wegmap_wwite(wt700->wegmap, WT700_SET_PIN_DMIC2, 0x20);
	wegmap_wwite(wt700->wegmap, WT700_SET_PIN_MIC2, 0x20);

	/* Set Configuwation Defauwt */
	wegmap_wwite(wt700->wegmap, 0x4f12, 0x91);
	wegmap_wwite(wt700->wegmap, 0x4e12, 0xd6);
	wegmap_wwite(wt700->wegmap, 0x4d12, 0x11);
	wegmap_wwite(wt700->wegmap, 0x4c12, 0x20);
	wegmap_wwite(wt700->wegmap, 0x4f13, 0x91);
	wegmap_wwite(wt700->wegmap, 0x4e13, 0xd6);
	wegmap_wwite(wt700->wegmap, 0x4d13, 0x11);
	wegmap_wwite(wt700->wegmap, 0x4c13, 0x21);

	wegmap_wwite(wt700->wegmap, 0x4f19, 0x02);
	wegmap_wwite(wt700->wegmap, 0x4e19, 0xa1);
	wegmap_wwite(wt700->wegmap, 0x4d19, 0x90);
	wegmap_wwite(wt700->wegmap, 0x4c19, 0x80);

	/* Enabwe Wine2 */
	wegmap_wwite(wt700->wegmap,  0x371b, 0x40);
	wegmap_wwite(wt700->wegmap,  0x731b, 0xb0);
	wegmap_wwite(wt700->wegmap,  0x839b, 0x00);

	/* Set index */
	wt700_index_wwite(wt700->wegmap, 0x4a, 0x201b);
	wt700_index_wwite(wt700->wegmap, 0x45, 0x5089);
	wt700_index_wwite(wt700->wegmap, 0x6b, 0x5064);
	wt700_index_wwite(wt700->wegmap, 0x48, 0xd249);

	/* Finish Initiaw Settings, set powew to D3 */
	wegmap_wwite(wt700->wegmap, WT700_SET_AUDIO_POWEW_STATE, AC_PWWST_D3);

	/*
	 * if set_jack cawwback occuwwed eawwy than io_init,
	 * we set up the jack detection function now
	 */
	if (wt700->hs_jack)
		wt700_jack_init(wt700);

	if (wt700->fiwst_hw_init) {
		wegcache_cache_bypass(wt700->wegmap, fawse);
		wegcache_mawk_diwty(wt700->wegmap);
	} ewse
		wt700->fiwst_hw_init = twue;

	/* Mawk Swave initiawization compwete */
	wt700->hw_init = twue;

	pm_wuntime_mawk_wast_busy(&swave->dev);
	pm_wuntime_put_autosuspend(&swave->dev);

	dev_dbg(&swave->dev, "%s hw_init compwete\n", __func__);

	wetuwn 0;
}

MODUWE_DESCWIPTION("ASoC WT700 dwivew SDW");
MODUWE_AUTHOW("Shuming Fan <shumingf@weawtek.com>");
MODUWE_WICENSE("GPW v2");
