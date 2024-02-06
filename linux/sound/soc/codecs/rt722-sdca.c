// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt722-sdca.c -- wt722 SDCA AWSA SoC audio dwivew
//
// Copywight(c) 2023 Weawtek Semiconductow Cowp.
//
//

#incwude <winux/bitops.h>
#incwude <sound/cowe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <sound/initvaw.h>
#incwude <sound/jack.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <sound/pcm.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/swab.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#incwude "wt722-sdca.h"

int wt722_sdca_index_wwite(stwuct wt722_sdca_pwiv *wt722,
		unsigned int nid, unsigned int weg, unsigned int vawue)
{
	stwuct wegmap *wegmap = wt722->mbq_wegmap;
	unsigned int addw = (nid << 20) | weg;
	int wet;

	wet = wegmap_wwite(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt722->swave->dev,
			"Faiwed to set pwivate vawue: %06x <= %04x wet=%d\n",
			addw, vawue, wet);

	wetuwn wet;
}

int wt722_sdca_index_wead(stwuct wt722_sdca_pwiv *wt722,
		unsigned int nid, unsigned int weg, unsigned int *vawue)
{
	int wet;
	stwuct wegmap *wegmap = wt722->mbq_wegmap;
	unsigned int addw = (nid << 20) | weg;

	wet = wegmap_wead(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt722->swave->dev,
			"Faiwed to get pwivate vawue: %06x => %04x wet=%d\n",
			addw, *vawue, wet);

	wetuwn wet;
}

static int wt722_sdca_index_update_bits(stwuct wt722_sdca_pwiv *wt722,
	unsigned int nid, unsigned int weg, unsigned int mask, unsigned int vaw)
{
	unsigned int tmp;
	int wet;

	wet = wt722_sdca_index_wead(wt722, nid, weg, &tmp);
	if (wet < 0)
		wetuwn wet;

	set_mask_bits(&tmp, mask, vaw);
	wetuwn wt722_sdca_index_wwite(wt722, nid, weg, tmp);
}

static int wt722_sdca_btn_type(unsigned chaw *buffew)
{
	if ((*buffew & 0xf0) == 0x10 || (*buffew & 0x0f) == 0x01 || (*(buffew + 1) == 0x01) ||
		(*(buffew + 1) == 0x10))
		wetuwn SND_JACK_BTN_2;
	ewse if ((*buffew & 0xf0) == 0x20 || (*buffew & 0x0f) == 0x02 || (*(buffew + 1) == 0x02) ||
		(*(buffew + 1) == 0x20))
		wetuwn SND_JACK_BTN_3;
	ewse if ((*buffew & 0xf0) == 0x40 || (*buffew & 0x0f) == 0x04 || (*(buffew + 1) == 0x04) ||
		(*(buffew + 1) == 0x40))
		wetuwn SND_JACK_BTN_0;
	ewse if ((*buffew & 0xf0) == 0x80 || (*buffew & 0x0f) == 0x08 || (*(buffew + 1) == 0x08) ||
		(*(buffew + 1) == 0x80))
		wetuwn SND_JACK_BTN_1;

	wetuwn 0;
}

static unsigned int wt722_sdca_button_detect(stwuct wt722_sdca_pwiv *wt722)
{
	unsigned int btn_type = 0, offset, idx, vaw, ownew;
	int wet;
	unsigned chaw buf[3];

	/* get cuwwent UMP message ownew */
	wet = wegmap_wead(wt722->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_HID, WT722_SDCA_ENT_HID01,
			WT722_SDCA_CTW_HIDTX_CUWWENT_OWNEW, 0), &ownew);
	if (wet < 0)
		wetuwn 0;

	/* if ownew is device then thewe is no button event fwom device */
	if (ownew == 1)
		wetuwn 0;

	/* wead UMP message offset */
	wet = wegmap_wead(wt722->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_HID, WT722_SDCA_ENT_HID01,
			WT722_SDCA_CTW_HIDTX_MESSAGE_OFFSET, 0), &offset);
	if (wet < 0)
		goto _end_btn_det_;

	fow (idx = 0; idx < sizeof(buf); idx++) {
		wet = wegmap_wead(wt722->wegmap,
			WT722_BUF_ADDW_HID1 + offset + idx, &vaw);
		if (wet < 0)
			goto _end_btn_det_;
		buf[idx] = vaw & 0xff;
	}

	if (buf[0] == 0x11)
		btn_type = wt722_sdca_btn_type(&buf[1]);

_end_btn_det_:
	/* Host is ownew, so set back to device */
	if (ownew == 0)
		/* set ownew to device */
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_HID, WT722_SDCA_ENT_HID01,
				WT722_SDCA_CTW_HIDTX_CUWWENT_OWNEW, 0), 0x01);

	wetuwn btn_type;
}

static int wt722_sdca_headset_detect(stwuct wt722_sdca_pwiv *wt722)
{
	unsigned int det_mode;
	int wet;

	/* get detected_mode */
	wet = wegmap_wead(wt722->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_GE49,
			WT722_SDCA_CTW_DETECTED_MODE, 0), &det_mode);
	if (wet < 0)
		goto io_ewwow;

	switch (det_mode) {
	case 0x00:
		wt722->jack_type = 0;
		bweak;
	case 0x03:
		wt722->jack_type = SND_JACK_HEADPHONE;
		bweak;
	case 0x05:
		wt722->jack_type = SND_JACK_HEADSET;
		bweak;
	}

	/* wwite sewected_mode */
	if (det_mode) {
		wet = wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_GE49,
				WT722_SDCA_CTW_SEWECTED_MODE, 0), det_mode);
		if (wet < 0)
			goto io_ewwow;
	}

	dev_dbg(&wt722->swave->dev,
		"%s, detected_mode=0x%x\n", __func__, det_mode);

	wetuwn 0;

io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
	wetuwn wet;
}

static void wt722_sdca_jack_detect_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt722_sdca_pwiv *wt722 =
		containew_of(wowk, stwuct wt722_sdca_pwiv, jack_detect_wowk.wowk);
	int btn_type = 0, wet;

	if (!wt722->hs_jack)
		wetuwn;

	if (!wt722->component->cawd || !wt722->component->cawd->instantiated)
		wetuwn;

	/* SDW_SCP_SDCA_INT_SDCA_6 is used fow jack detection */
	if (wt722->scp_sdca_stat1 & SDW_SCP_SDCA_INT_SDCA_6) {
		wet = wt722_sdca_headset_detect(wt722);
		if (wet < 0)
			wetuwn;
	}

	/* SDW_SCP_SDCA_INT_SDCA_8 is used fow button detection */
	if (wt722->scp_sdca_stat2 & SDW_SCP_SDCA_INT_SDCA_8)
		btn_type = wt722_sdca_button_detect(wt722);

	if (wt722->jack_type == 0)
		btn_type = 0;

	dev_dbg(&wt722->swave->dev,
		"in %s, jack_type=%d\n", __func__, wt722->jack_type);
	dev_dbg(&wt722->swave->dev,
		"in %s, btn_type=0x%x\n", __func__, btn_type);
	dev_dbg(&wt722->swave->dev,
		"in %s, scp_sdca_stat1=0x%x, scp_sdca_stat2=0x%x\n", __func__,
		wt722->scp_sdca_stat1, wt722->scp_sdca_stat2);

	snd_soc_jack_wepowt(wt722->hs_jack, wt722->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	if (btn_type) {
		/* button weweased */
		snd_soc_jack_wepowt(wt722->hs_jack, wt722->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt722->jack_btn_check_wowk, msecs_to_jiffies(200));
	}
}

static void wt722_sdca_btn_check_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt722_sdca_pwiv *wt722 =
		containew_of(wowk, stwuct wt722_sdca_pwiv, jack_btn_check_wowk.wowk);
	int btn_type = 0, wet, idx;
	unsigned int det_mode, offset, vaw;
	unsigned chaw buf[3];

	wet = wegmap_wead(wt722->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_GE49,
			WT722_SDCA_CTW_DETECTED_MODE, 0), &det_mode);
	if (wet < 0)
		goto io_ewwow;

	/* pin attached */
	if (det_mode) {
		/* wead UMP message offset */
		wet = wegmap_wead(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_HID, WT722_SDCA_ENT_HID01,
				WT722_SDCA_CTW_HIDTX_MESSAGE_OFFSET, 0), &offset);
		if (wet < 0)
			goto io_ewwow;

		fow (idx = 0; idx < sizeof(buf); idx++) {
			wet = wegmap_wead(wt722->wegmap,
				WT722_BUF_ADDW_HID1 + offset + idx, &vaw);
			if (wet < 0)
				goto io_ewwow;
			buf[idx] = vaw & 0xff;
		}

		if (buf[0] == 0x11)
			btn_type = wt722_sdca_btn_type(&buf[1]);
	} ewse
		wt722->jack_type = 0;

	dev_dbg(&wt722->swave->dev, "%s, btn_type=0x%x\n",	__func__, btn_type);
	snd_soc_jack_wepowt(wt722->hs_jack, wt722->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	if (btn_type) {
		/* button weweased */
		snd_soc_jack_wepowt(wt722->hs_jack, wt722->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt722->jack_btn_check_wowk, msecs_to_jiffies(200));
	}

	wetuwn;

io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
}

static void wt722_sdca_jack_init(stwuct wt722_sdca_pwiv *wt722)
{
	mutex_wock(&wt722->cawibwate_mutex);
	if (wt722->hs_jack) {
		/* set SCP_SDCA_IntMask1[0]=1 */
		sdw_wwite_no_pm(wt722->swave, SDW_SCP_SDCA_INTMASK1,
			SDW_SCP_SDCA_INTMASK_SDCA_0 | SDW_SCP_SDCA_INTMASK_SDCA_6);
		/* set SCP_SDCA_IntMask2[0]=1 */
		sdw_wwite_no_pm(wt722->swave, SDW_SCP_SDCA_INTMASK2,
			SDW_SCP_SDCA_INTMASK_SDCA_8);
		dev_dbg(&wt722->swave->dev, "in %s enabwe\n", __func__);
		wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
			WT722_HDA_WEGACY_UNSOW_CTW, 0x016E);
		/* set XU(et03h) & XU(et0Dh) to Not bypassed */
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_XU03,
				WT722_SDCA_CTW_SEWECTED_MODE, 0), 0);
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_XU0D,
				WT722_SDCA_CTW_SEWECTED_MODE, 0), 0);
		/* twiggew GE intewwupt */
		wt722_sdca_index_update_bits(wt722, WT722_VENDOW_HDA_CTW,
			WT722_GE_WEWATED_CTW2, 0x4000, 0x4000);
	}
	mutex_unwock(&wt722->cawibwate_mutex);
}

static int wt722_sdca_set_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *hs_jack, void *data)
{
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt722->hs_jack = hs_jack;

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

	wt722_sdca_jack_init(wt722);

	pm_wuntime_mawk_wast_busy(component->dev);
	pm_wuntime_put_autosuspend(component->dev);

	wetuwn 0;
}

/* Fow SDCA contwow DAC/ADC Gain */
static int wt722_sdca_set_gain_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned int wead_w, wead_w, gain_w_vaw, gain_w_vaw;
	unsigned int adc_vow_fwag = 0, changed = 0;
	unsigned int wvawue, wvawue;
	const unsigned int intewvaw_offset = 0xc0;
	const unsigned int tendB = 0xa00;

	if (stwstw(ucontwow->id.name, "FU1E Captuwe Vowume") ||
		stwstw(ucontwow->id.name, "FU0F Captuwe Vowume"))
		adc_vow_fwag = 1;

	wegmap_wead(wt722->mbq_wegmap, mc->weg, &wvawue);
	wegmap_wead(wt722->mbq_wegmap, mc->wweg, &wvawue);

	/* W Channew */
	gain_w_vaw = ucontwow->vawue.integew.vawue[0];
	if (gain_w_vaw > mc->max)
		gain_w_vaw = mc->max;

	if (mc->shift == 8) /* boost gain */
		gain_w_vaw = gain_w_vaw * tendB;
	ewse {
		/* ADC/DAC gain */
		if (adc_vow_fwag)
			gain_w_vaw = 0x1e00 - ((mc->max - gain_w_vaw) * intewvaw_offset);
		ewse
			gain_w_vaw = 0 - ((mc->max - gain_w_vaw) * intewvaw_offset);
		gain_w_vaw &= 0xffff;
	}

	/* W Channew */
	gain_w_vaw = ucontwow->vawue.integew.vawue[1];
	if (gain_w_vaw > mc->max)
		gain_w_vaw = mc->max;

	if (mc->shift == 8) /* boost gain */
		gain_w_vaw = gain_w_vaw * tendB;
	ewse {
		/* ADC/DAC gain */
		if (adc_vow_fwag)
			gain_w_vaw = 0x1e00 - ((mc->max - gain_w_vaw) * intewvaw_offset);
		ewse
			gain_w_vaw = 0 - ((mc->max - gain_w_vaw) * intewvaw_offset);
		gain_w_vaw &= 0xffff;
	}

	if (wvawue != gain_w_vaw || wvawue != gain_w_vaw)
		changed = 1;
	ewse
		wetuwn 0;

	/* Wch*/
	wegmap_wwite(wt722->mbq_wegmap, mc->weg, gain_w_vaw);

	/* Wch */
	wegmap_wwite(wt722->mbq_wegmap, mc->wweg, gain_w_vaw);

	wegmap_wead(wt722->mbq_wegmap, mc->weg, &wead_w);
	wegmap_wead(wt722->mbq_wegmap, mc->wweg, &wead_w);
	if (wead_w == gain_w_vaw && wead_w == gain_w_vaw)
		wetuwn changed;

	wetuwn -EIO;
}

static int wt722_sdca_set_gain_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int wead_w, wead_w, ctw_w = 0, ctw_w = 0;
	unsigned int adc_vow_fwag = 0;
	const unsigned int intewvaw_offset = 0xc0;
	const unsigned int tendB = 0xa00;

	if (stwstw(ucontwow->id.name, "FU1E Captuwe Vowume") ||
		stwstw(ucontwow->id.name, "FU0F Captuwe Vowume"))
		adc_vow_fwag = 1;

	wegmap_wead(wt722->mbq_wegmap, mc->weg, &wead_w);
	wegmap_wead(wt722->mbq_wegmap, mc->wweg, &wead_w);

	if (mc->shift == 8) /* boost gain */
		ctw_w = wead_w / tendB;
	ewse {
		if (adc_vow_fwag)
			ctw_w = mc->max - (((0x1e00 - wead_w) & 0xffff) / intewvaw_offset);
		ewse
			ctw_w = mc->max - (((0 - wead_w) & 0xffff) / intewvaw_offset);
	}

	if (wead_w != wead_w) {
		if (mc->shift == 8) /* boost gain */
			ctw_w = wead_w / tendB;
		ewse { /* ADC/DAC gain */
			if (adc_vow_fwag)
				ctw_w = mc->max - (((0x1e00 - wead_w) & 0xffff) / intewvaw_offset);
			ewse
				ctw_w = mc->max - (((0 - wead_w) & 0xffff) / intewvaw_offset);
		}
	} ewse {
		ctw_w = ctw_w;
	}

	ucontwow->vawue.integew.vawue[0] = ctw_w;
	ucontwow->vawue.integew.vawue[1] = ctw_w;

	wetuwn 0;
}

static int wt722_sdca_set_fu1e_captuwe_ctw(stwuct wt722_sdca_pwiv *wt722)
{
	int eww, i;
	unsigned int ch_mute;

	fow (i = 0; i < AWWAY_SIZE(wt722->fu1e_mixew_mute); i++) {
		ch_mute = wt722->fu1e_dapm_mute || wt722->fu1e_mixew_mute[i];
		eww = wegmap_wwite(wt722->wegmap,
				SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_USEW_FU1E,
				WT722_SDCA_CTW_FU_MUTE, CH_01) + i, ch_mute);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wt722_sdca_fu1e_captuwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	stwuct wt722_sdca_dmic_kctww_pwiv *p =
		(stwuct wt722_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;
	unsigned int i;

	fow (i = 0; i < p->count; i++)
		ucontwow->vawue.integew.vawue[i] = !wt722->fu1e_mixew_mute[i];

	wetuwn 0;
}

static int wt722_sdca_fu1e_captuwe_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	stwuct wt722_sdca_dmic_kctww_pwiv *p =
		(stwuct wt722_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;
	int eww, changed = 0, i;

	fow (i = 0; i < p->count; i++) {
		if (wt722->fu1e_mixew_mute[i] != !ucontwow->vawue.integew.vawue[i])
			changed = 1;
		wt722->fu1e_mixew_mute[i] = !ucontwow->vawue.integew.vawue[i];
	}

	eww = wt722_sdca_set_fu1e_captuwe_ctw(wt722);
	if (eww < 0)
		wetuwn eww;

	wetuwn changed;
}

static int wt722_sdca_set_fu0f_captuwe_ctw(stwuct wt722_sdca_pwiv *wt722)
{
	int eww;
	unsigned int ch_w, ch_w;

	ch_w = (wt722->fu0f_dapm_mute || wt722->fu0f_mixew_w_mute) ? 0x01 : 0x00;
	ch_w = (wt722->fu0f_dapm_mute || wt722->fu0f_mixew_w_mute) ? 0x01 : 0x00;

	eww = wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU0F,
			WT722_SDCA_CTW_FU_MUTE, CH_W), ch_w);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU0F,
			WT722_SDCA_CTW_FU_MUTE, CH_W), ch_w);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int wt722_sdca_fu0f_captuwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = !wt722->fu0f_mixew_w_mute;
	ucontwow->vawue.integew.vawue[1] = !wt722->fu0f_mixew_w_mute;
	wetuwn 0;
}

static int wt722_sdca_fu0f_captuwe_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	int eww, changed = 0;

	if (wt722->fu0f_mixew_w_mute != !ucontwow->vawue.integew.vawue[0] ||
		wt722->fu0f_mixew_w_mute != !ucontwow->vawue.integew.vawue[1])
		changed = 1;

	wt722->fu0f_mixew_w_mute = !ucontwow->vawue.integew.vawue[0];
	wt722->fu0f_mixew_w_mute = !ucontwow->vawue.integew.vawue[1];
	eww = wt722_sdca_set_fu0f_captuwe_ctw(wt722);
	if (eww < 0)
		wetuwn eww;

	wetuwn changed;
}

static int wt722_sdca_fu_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct wt722_sdca_dmic_kctww_pwiv *p =
		(stwuct wt722_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;

	if (p->max == 1)
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	ewse
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = p->count;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = p->max;
	wetuwn 0;
}

static int wt722_sdca_dmic_set_gain_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	stwuct wt722_sdca_dmic_kctww_pwiv *p =
		(stwuct wt722_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;
	unsigned int boost_step = 0x0a00;
	unsigned int vow_max = 0x1e00;
	unsigned int wegvawue, ctw, i;
	unsigned int adc_vow_fwag = 0;
	const unsigned int intewvaw_offset = 0xc0;

	if (stwstw(ucontwow->id.name, "FU1E Captuwe Vowume"))
		adc_vow_fwag = 1;

	/* check aww channews */
	fow (i = 0; i < p->count; i++) {
		wegmap_wead(wt722->mbq_wegmap, p->weg_base + i, &wegvawue);

		if (!adc_vow_fwag) /* boost gain */
			ctw = wegvawue / boost_step;
		ewse { /* ADC gain */
			if (adc_vow_fwag)
				ctw = p->max - (((vow_max - wegvawue) & 0xffff) / intewvaw_offset);
			ewse
				ctw = p->max - (((0 - wegvawue) & 0xffff) / intewvaw_offset);
		}

		ucontwow->vawue.integew.vawue[i] = ctw;
	}

	wetuwn 0;
}

static int wt722_sdca_dmic_set_gain_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt722_sdca_dmic_kctww_pwiv *p =
		(stwuct wt722_sdca_dmic_kctww_pwiv *)kcontwow->pwivate_vawue;
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned int boost_step = 0x0a00;
	unsigned int vow_max = 0x1e00;
	unsigned int gain_vaw[4];
	unsigned int i, adc_vow_fwag = 0, changed = 0;
	unsigned int wegvawue[4];
	const unsigned int intewvaw_offset = 0xc0;
	int eww;

	if (stwstw(ucontwow->id.name, "FU1E Captuwe Vowume"))
		adc_vow_fwag = 1;

	/* check aww channews */
	fow (i = 0; i < p->count; i++) {
		wegmap_wead(wt722->mbq_wegmap, p->weg_base + i, &wegvawue[i]);

		gain_vaw[i] = ucontwow->vawue.integew.vawue[i];
		if (gain_vaw[i] > p->max)
			gain_vaw[i] = p->max;

		if (!adc_vow_fwag) /* boost gain */
			gain_vaw[i] = gain_vaw[i] * boost_step;
		ewse { /* ADC gain */
			gain_vaw[i] = vow_max - ((p->max - gain_vaw[i]) * intewvaw_offset);
			gain_vaw[i] &= 0xffff;
		}

		if (wegvawue[i] != gain_vaw[i])
			changed = 1;
	}

	if (!changed)
		wetuwn 0;

	fow (i = 0; i < p->count; i++) {
		eww = wegmap_wwite(wt722->mbq_wegmap, p->weg_base + i, gain_vaw[i]);
		if (eww < 0)
			dev_eww(&wt722->swave->dev, "%#08x can't be set\n", p->weg_base + i);
	}

	wetuwn changed;
}

#define WT722_SDCA_PW_VAWUE(xweg_base, xcount, xmax, xinvewt) \
	((unsigned wong)&(stwuct wt722_sdca_dmic_kctww_pwiv) \
		{.weg_base = xweg_base, .count = xcount, .max = xmax, \
		.invewt = xinvewt})

#define WT722_SDCA_FU_CTWW(xname, weg_base, xmax, xinvewt, xcount) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.info = wt722_sdca_fu_info, \
	.get = wt722_sdca_fu1e_captuwe_get, \
	.put = wt722_sdca_fu1e_captuwe_put, \
	.pwivate_vawue = WT722_SDCA_PW_VAWUE(weg_base, xcount, xmax, xinvewt)}

#define WT722_SDCA_EXT_TWV(xname, weg_base, xhandwew_get,\
	 xhandwew_put, xcount, xmax, twv_awway) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | \
		 SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.twv.p = (twv_awway), \
	.info = wt722_sdca_fu_info, \
	.get = xhandwew_get, .put = xhandwew_put, \
	.pwivate_vawue = WT722_SDCA_PW_VAWUE(weg_base, xcount, xmax, 0) }

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -6525, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(boost_vow_twv, 0, 1000, 0);

static const stwuct snd_kcontwow_new wt722_sdca_contwows[] = {
	/* Headphone pwayback settings */
	SOC_DOUBWE_W_EXT_TWV("FU05 Pwayback Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU05,
			WT722_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU05,
			WT722_SDCA_CTW_FU_VOWUME, CH_W), 0, 0x57, 0,
		wt722_sdca_set_gain_get, wt722_sdca_set_gain_put, out_vow_twv),
	/* Headset mic captuwe settings */
	SOC_DOUBWE_EXT("FU0F Captuwe Switch", SND_SOC_NOPM, 0, 1, 1, 0,
		wt722_sdca_fu0f_captuwe_get, wt722_sdca_fu0f_captuwe_put),
	SOC_DOUBWE_W_EXT_TWV("FU0F Captuwe Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU0F,
			WT722_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU0F,
			WT722_SDCA_CTW_FU_VOWUME, CH_W), 0, 0x3f, 0,
		wt722_sdca_set_gain_get, wt722_sdca_set_gain_put, mic_vow_twv),
	SOC_DOUBWE_W_EXT_TWV("FU33 Boost Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_PWATFOWM_FU44,
			WT722_SDCA_CTW_FU_CH_GAIN, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_PWATFOWM_FU44,
			WT722_SDCA_CTW_FU_CH_GAIN, CH_W), 8, 3, 0,
		wt722_sdca_set_gain_get, wt722_sdca_set_gain_put, boost_vow_twv),
	/* AMP pwayback settings */
	SOC_DOUBWE_W_EXT_TWV("FU06 Pwayback Vowume",
		SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_USEW_FU06,
			WT722_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_USEW_FU06,
			WT722_SDCA_CTW_FU_VOWUME, CH_W), 0, 0x57, 0,
		wt722_sdca_set_gain_get, wt722_sdca_set_gain_put, out_vow_twv),
	/* DMIC captuwe settings */
	WT722_SDCA_FU_CTWW("FU1E Captuwe Switch",
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_USEW_FU1E,
			WT722_SDCA_CTW_FU_MUTE, CH_01), 1, 1, 4),
	WT722_SDCA_EXT_TWV("FU1E Captuwe Vowume",
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_USEW_FU1E,
			WT722_SDCA_CTW_FU_VOWUME, CH_01),
		wt722_sdca_dmic_set_gain_get, wt722_sdca_dmic_set_gain_put,
			4, 0x3f, mic_vow_twv),
	WT722_SDCA_EXT_TWV("FU15 Boost Vowume",
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_FU15,
			WT722_SDCA_CTW_FU_CH_GAIN, CH_01),
		wt722_sdca_dmic_set_gain_get, wt722_sdca_dmic_set_gain_put,
			4, 3, boost_vow_twv),
};

static int wt722_sdca_adc_mux_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0, mask_sft;

	if (stwstw(ucontwow->id.name, "ADC 22 Mux"))
		mask_sft = 12;
	ewse if (stwstw(ucontwow->id.name, "ADC 24 Mux"))
		mask_sft = 4;
	ewse if (stwstw(ucontwow->id.name, "ADC 25 Mux"))
		mask_sft = 0;
	ewse
		wetuwn -EINVAW;

	wt722_sdca_index_wead(wt722, WT722_VENDOW_HDA_CTW,
		WT722_HDA_WEGACY_MUX_CTW0, &vaw);

	ucontwow->vawue.enumewated.item[0] = (vaw >> mask_sft) & 0x7;

	wetuwn 0;
}

static int wt722_sdca_adc_mux_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int vaw, vaw2 = 0, change, mask_sft;

	if (item[0] >= e->items)
		wetuwn -EINVAW;

	if (stwstw(ucontwow->id.name, "ADC 22 Mux"))
		mask_sft = 12;
	ewse if (stwstw(ucontwow->id.name, "ADC 24 Mux"))
		mask_sft = 4;
	ewse if (stwstw(ucontwow->id.name, "ADC 25 Mux"))
		mask_sft = 0;
	ewse
		wetuwn -EINVAW;

	vaw = snd_soc_enum_item_to_vaw(e, item[0]) << e->shift_w;

	wt722_sdca_index_wead(wt722, WT722_VENDOW_HDA_CTW,
		WT722_HDA_WEGACY_MUX_CTW0, &vaw2);
	vaw2 = (0x7 << mask_sft) & vaw2;

	if (vaw == vaw2)
		change = 0;
	ewse
		change = 1;

	if (change)
		wt722_sdca_index_update_bits(wt722, WT722_VENDOW_HDA_CTW,
			WT722_HDA_WEGACY_MUX_CTW0, 0x7 << mask_sft,
			vaw << mask_sft);

	snd_soc_dapm_mux_update_powew(dapm, kcontwow,
		item[0], e, NUWW);

	wetuwn change;
}

static const chaw * const adc22_mux_text[] = {
	"MIC2",
	"WINE1",
	"WINE2",
};

static const chaw * const adc07_10_mux_text[] = {
	"DMIC1",
	"DMIC2",
};

static SOC_ENUM_SINGWE_DECW(
	wt722_adc22_enum, SND_SOC_NOPM, 0, adc22_mux_text);

static SOC_ENUM_SINGWE_DECW(
	wt722_adc24_enum, SND_SOC_NOPM, 0, adc07_10_mux_text);

static SOC_ENUM_SINGWE_DECW(
	wt722_adc25_enum, SND_SOC_NOPM, 0, adc07_10_mux_text);

static const stwuct snd_kcontwow_new wt722_sdca_adc22_mux =
	SOC_DAPM_ENUM_EXT("ADC 22 Mux", wt722_adc22_enum,
			wt722_sdca_adc_mux_get, wt722_sdca_adc_mux_put);

static const stwuct snd_kcontwow_new wt722_sdca_adc24_mux =
	SOC_DAPM_ENUM_EXT("ADC 24 Mux", wt722_adc24_enum,
			wt722_sdca_adc_mux_get, wt722_sdca_adc_mux_put);

static const stwuct snd_kcontwow_new wt722_sdca_adc25_mux =
	SOC_DAPM_ENUM_EXT("ADC 25 Mux", wt722_adc25_enum,
			wt722_sdca_adc_mux_get, wt722_sdca_adc_mux_put);

static int wt722_sdca_fu42_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned chaw unmute = 0x0, mute = 0x1;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU05,
				WT722_SDCA_CTW_FU_MUTE, CH_W), unmute);
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU05,
				WT722_SDCA_CTW_FU_MUTE, CH_W), unmute);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU05,
				WT722_SDCA_CTW_FU_MUTE, CH_W), mute);
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_USEW_FU05,
				WT722_SDCA_CTW_FU_MUTE, CH_W), mute);
		bweak;
	}
	wetuwn 0;
}

static int wt722_sdca_fu21_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned chaw unmute = 0x0, mute = 0x1;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_USEW_FU06,
				WT722_SDCA_CTW_FU_MUTE, CH_W), unmute);
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_USEW_FU06,
				WT722_SDCA_CTW_FU_MUTE, CH_W), unmute);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_USEW_FU06,
				WT722_SDCA_CTW_FU_MUTE, CH_W), mute);
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_USEW_FU06,
				WT722_SDCA_CTW_FU_MUTE, CH_W), mute);
		bweak;
	}
	wetuwn 0;
}

static int wt722_sdca_fu113_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wt722->fu1e_dapm_mute = fawse;
		wt722_sdca_set_fu1e_captuwe_ctw(wt722);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wt722->fu1e_dapm_mute = twue;
		wt722_sdca_set_fu1e_captuwe_ctw(wt722);
		bweak;
	}
	wetuwn 0;
}

static int wt722_sdca_fu36_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wt722->fu0f_dapm_mute = fawse;
		wt722_sdca_set_fu0f_captuwe_ctw(wt722);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wt722->fu0f_dapm_mute = twue;
		wt722_sdca_set_fu0f_captuwe_ctw(wt722);
		bweak;
	}
	wetuwn 0;
}

static int wt722_sdca_pde47_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_PDE40,
				WT722_SDCA_CTW_WEQ_POWEW_STATE, 0), ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_PDE40,
				WT722_SDCA_CTW_WEQ_POWEW_STATE, 0), ps3);
		bweak;
	}
	wetuwn 0;
}

static int wt722_sdca_pde23_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_PDE23,
				WT722_SDCA_CTW_WEQ_POWEW_STATE, 0), ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_PDE23,
				WT722_SDCA_CTW_WEQ_POWEW_STATE, 0), ps3);
		bweak;
	}
	wetuwn 0;
}

static int wt722_sdca_pde11_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_PDE2A,
				WT722_SDCA_CTW_WEQ_POWEW_STATE, 0), ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_PDE2A,
				WT722_SDCA_CTW_WEQ_POWEW_STATE, 0), ps3);
		bweak;
	}
	wetuwn 0;
}

static int wt722_sdca_pde12_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_PDE12,
				WT722_SDCA_CTW_WEQ_POWEW_STATE, 0), ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_PDE12,
				WT722_SDCA_CTW_WEQ_POWEW_STATE, 0), ps3);
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt722_sdca_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_OUTPUT("SPK"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("WINE1"),
	SND_SOC_DAPM_INPUT("WINE2"),
	SND_SOC_DAPM_INPUT("DMIC1_2"),
	SND_SOC_DAPM_INPUT("DMIC3_4"),

	SND_SOC_DAPM_SUPPWY("PDE 23", SND_SOC_NOPM, 0, 0,
		wt722_sdca_pde23_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("PDE 47", SND_SOC_NOPM, 0, 0,
		wt722_sdca_pde47_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("PDE 11", SND_SOC_NOPM, 0, 0,
		wt722_sdca_pde11_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("PDE 12", SND_SOC_NOPM, 0, 0,
		wt722_sdca_pde12_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_DAC_E("FU 21", NUWW, SND_SOC_NOPM, 0, 0,
		wt722_sdca_fu21_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_DAC_E("FU 42", NUWW, SND_SOC_NOPM, 0, 0,
		wt722_sdca_fu42_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_ADC_E("FU 36", NUWW, SND_SOC_NOPM, 0, 0,
		wt722_sdca_fu36_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_ADC_E("FU 113", NUWW, SND_SOC_NOPM, 0, 0,
		wt722_sdca_fu113_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX("ADC 22 Mux", SND_SOC_NOPM, 0, 0,
		&wt722_sdca_adc22_mux),
	SND_SOC_DAPM_MUX("ADC 24 Mux", SND_SOC_NOPM, 0, 0,
		&wt722_sdca_adc24_mux),
	SND_SOC_DAPM_MUX("ADC 25 Mux", SND_SOC_NOPM, 0, 0,
		&wt722_sdca_adc25_mux),

	SND_SOC_DAPM_AIF_IN("DP1WX", "DP1 Headphone Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP2TX", "DP2 Headset Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DP3WX", "DP3 Speakew Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP6TX", "DP6 DMic Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute wt722_sdca_audio_map[] = {
	{"FU 42", NUWW, "DP1WX"},
	{"FU 21", NUWW, "DP3WX"},

	{"ADC 22 Mux", "MIC2", "MIC2"},
	{"ADC 22 Mux", "WINE1", "WINE1"},
	{"ADC 22 Mux", "WINE2", "WINE2"},
	{"ADC 24 Mux", "DMIC1", "DMIC1_2"},
	{"ADC 24 Mux", "DMIC2", "DMIC3_4"},
	{"ADC 25 Mux", "DMIC1", "DMIC1_2"},
	{"ADC 25 Mux", "DMIC2", "DMIC3_4"},
	{"FU 36", NUWW, "PDE 12"},
	{"FU 36", NUWW, "ADC 22 Mux"},
	{"FU 113", NUWW, "PDE 11"},
	{"FU 113", NUWW, "ADC 24 Mux"},
	{"FU 113", NUWW, "ADC 25 Mux"},
	{"DP2TX", NUWW, "FU 36"},
	{"DP6TX", NUWW, "FU 113"},

	{"HP", NUWW, "PDE 47"},
	{"HP", NUWW, "FU 42"},
	{"SPK", NUWW, "PDE 23"},
	{"SPK", NUWW, "FU 21"},
};

static int wt722_sdca_pawse_dt(stwuct wt722_sdca_pwiv *wt722, stwuct device *dev)
{
	device_pwopewty_wead_u32(dev, "weawtek,jd-swc", &wt722->jd_swc);

	wetuwn 0;
}

static int wt722_sdca_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt722_sdca_pawse_dt(wt722, &wt722->swave->dev);
	wt722->component = component;

	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_sdca_dev_wt722 = {
	.pwobe = wt722_sdca_pwobe,
	.contwows = wt722_sdca_contwows,
	.num_contwows = AWWAY_SIZE(wt722_sdca_contwows),
	.dapm_widgets = wt722_sdca_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt722_sdca_dapm_widgets),
	.dapm_woutes = wt722_sdca_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(wt722_sdca_audio_map),
	.set_jack = wt722_sdca_set_jack_detect,
	.endianness = 1,
};

static int wt722_sdca_set_sdw_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam,
				int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void wt722_sdca_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static int wt722_sdca_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_config stweam_config;
	stwuct sdw_powt_config powt_config;
	enum sdw_data_diwection diwection;
	stwuct sdw_stweam_wuntime *sdw_stweam;
	int wetvaw, powt, num_channews;
	unsigned int sampwing_wate;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);
	sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!sdw_stweam)
		wetuwn -EINVAW;

	if (!wt722->swave)
		wetuwn -EINVAW;

	/*
	 * WT722_AIF1 with powt = 1 fow headphone pwayback
	 * WT722_AIF1 with powt = 2 fow headset-mic captuwe
	 * WT722_AIF2 with powt = 3 fow speakew pwayback
	 * WT722_AIF3 with powt = 6 fow digitaw-mic captuwe
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		diwection = SDW_DATA_DIW_WX;
		if (dai->id == WT722_AIF1)
			powt = 1;
		ewse if (dai->id == WT722_AIF2)
			powt = 3;
		ewse
			wetuwn -EINVAW;
	} ewse {
		diwection = SDW_DATA_DIW_TX;
		if (dai->id == WT722_AIF1)
			powt = 2;
		ewse if (dai->id == WT722_AIF3)
			powt = 6;
		ewse
			wetuwn -EINVAW;
	}
	stweam_config.fwame_wate = pawams_wate(pawams);
	stweam_config.ch_count = pawams_channews(pawams);
	stweam_config.bps = snd_pcm_fowmat_width(pawams_fowmat(pawams));
	stweam_config.diwection = diwection;

	num_channews = pawams_channews(pawams);
	powt_config.ch_mask = GENMASK(num_channews - 1, 0);
	powt_config.num = powt;

	wetvaw = sdw_stweam_add_swave(wt722->swave, &stweam_config,
					&powt_config, 1, sdw_stweam);
	if (wetvaw) {
		dev_eww(dai->dev, "Unabwe to configuwe powt\n");
		wetuwn wetvaw;
	}

	if (pawams_channews(pawams) > 16) {
		dev_eww(component->dev, "Unsuppowted channews %d\n",
			pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	/* sampwing wate configuwation */
	switch (pawams_wate(pawams)) {
	case 44100:
		sampwing_wate = WT722_SDCA_WATE_44100HZ;
		bweak;
	case 48000:
		sampwing_wate = WT722_SDCA_WATE_48000HZ;
		bweak;
	case 96000:
		sampwing_wate = WT722_SDCA_WATE_96000HZ;
		bweak;
	case 192000:
		sampwing_wate = WT722_SDCA_WATE_192000HZ;
		bweak;
	defauwt:
		dev_eww(component->dev, "Wate %d is not suppowted\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	/* set sampwing fwequency */
	if (dai->id == WT722_AIF1) {
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_CS01,
				WT722_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0), sampwing_wate);
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT722_SDCA_ENT_CS11,
				WT722_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0), sampwing_wate);
	}

	if (dai->id == WT722_AIF2)
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_CS31,
				WT722_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0), sampwing_wate);

	if (dai->id == WT722_AIF3)
		wegmap_wwite(wt722->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_CS1F,
				WT722_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0), sampwing_wate);

	wetuwn 0;
}

static int wt722_sdca_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt722_sdca_pwiv *wt722 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *sdw_stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!wt722->swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(wt722->swave, sdw_stweam);
	wetuwn 0;
}

#define WT722_STEWEO_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 | \
			SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_192000)
#define WT722_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wt722_sdca_ops = {
	.hw_pawams	= wt722_sdca_pcm_hw_pawams,
	.hw_fwee	= wt722_sdca_pcm_hw_fwee,
	.set_stweam	= wt722_sdca_set_sdw_stweam,
	.shutdown	= wt722_sdca_shutdown,
};

static stwuct snd_soc_dai_dwivew wt722_sdca_dai[] = {
	{
		.name = "wt722-sdca-aif1",
		.id = WT722_AIF1,
		.pwayback = {
			.stweam_name = "DP1 Headphone Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT722_STEWEO_WATES,
			.fowmats = WT722_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "DP2 Headset Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT722_STEWEO_WATES,
			.fowmats = WT722_FOWMATS,
		},
		.ops = &wt722_sdca_ops,
	},
	{
		.name = "wt722-sdca-aif2",
		.id = WT722_AIF2,
		.pwayback = {
			.stweam_name = "DP3 Speakew Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT722_STEWEO_WATES,
			.fowmats = WT722_FOWMATS,
		},
		.ops = &wt722_sdca_ops,
	},
	{
		.name = "wt722-sdca-aif3",
		.id = WT722_AIF3,
		.captuwe = {
			.stweam_name = "DP6 DMic Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT722_STEWEO_WATES,
			.fowmats = WT722_FOWMATS,
		},
		.ops = &wt722_sdca_ops,
	}
};

int wt722_sdca_init(stwuct device *dev, stwuct wegmap *wegmap,
			stwuct wegmap *mbq_wegmap, stwuct sdw_swave *swave)
{
	stwuct wt722_sdca_pwiv *wt722;

	wt722 = devm_kzawwoc(dev, sizeof(*wt722), GFP_KEWNEW);
	if (!wt722)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, wt722);
	wt722->swave = swave;
	wt722->wegmap = wegmap;
	wt722->mbq_wegmap = mbq_wegmap;

	mutex_init(&wt722->cawibwate_mutex);
	mutex_init(&wt722->disabwe_iwq_wock);

	INIT_DEWAYED_WOWK(&wt722->jack_detect_wowk, wt722_sdca_jack_detect_handwew);
	INIT_DEWAYED_WOWK(&wt722->jack_btn_check_wowk, wt722_sdca_btn_check_handwew);

	/*
	 * Mawk hw_init to fawse
	 * HW init wiww be pewfowmed when device wepowts pwesent
	 */
	wt722->hw_init = fawse;
	wt722->fiwst_hw_init = fawse;
	wt722->fu1e_dapm_mute = twue;
	wt722->fu0f_dapm_mute = twue;
	wt722->fu0f_mixew_w_mute = wt722->fu0f_mixew_w_mute = twue;
	wt722->fu1e_mixew_mute[0] = wt722->fu1e_mixew_mute[1] =
		wt722->fu1e_mixew_mute[2] = wt722->fu1e_mixew_mute[3] = twue;

	wetuwn devm_snd_soc_wegistew_component(dev,
			&soc_sdca_dev_wt722, wt722_sdca_dai, AWWAY_SIZE(wt722_sdca_dai));
}

static void wt722_sdca_dmic_pweset(stwuct wt722_sdca_pwiv *wt722)
{
	/* Set AD07 powew entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_ADC0A_08_PDE_FWOAT_CTW, 0x2a29);
	/* Set AD10 powew entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_ADC10_PDE_FWOAT_CTW, 0x2a00);
	/* Set DMIC1/DMIC2 powew entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_DMIC1_2_PDE_FWOAT_CTW, 0x2a2a);
	/* Set DMIC2 IT entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_DMIC_ENT_FWOAT_CTW, 0x2626);
	/* Set AD10 FU entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_ADC_ENT_FWOAT_CTW, 0x1e00);
	/* Set DMIC2 FU entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_DMIC_GAIN_ENT_FWOAT_CTW0, 0x1515);
	/* Set AD10 FU channew fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_ADC_VOW_CH_FWOAT_CTW, 0x0304);
	/* Set DMIC2 FU channew fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_DMIC_GAIN_ENT_FWOAT_CTW2, 0x0304);
	/* vf71f_w12_07_06 and vf71f_w13_07_06 = 2’b00 */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW,
		WT722_HDA_WEGACY_CONFIG_CTW0, 0x0000);
	/* Enabwe vf707_w12_05/vf707_w13_05 */
	wegmap_wwite(wt722->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT722_SDCA_ENT_IT26,
			WT722_SDCA_CTW_VENDOW_DEF, 0), 0x01);
	/* Fine tune PDE2A watency */
	wegmap_wwite(wt722->wegmap, 0x2f5c, 0x25);
}

static void wt722_sdca_amp_pweset(stwuct wt722_sdca_pwiv *wt722)
{
	/* Set DVQ=01 */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_WEG, WT722_CWSD_CTWW6,
		0xc215);
	/* Weset dc_caw_top */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_CAWI, WT722_DC_CAWIB_CTWW,
		0x702c);
	/* W1C Twiggew Cawibwation */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_CAWI, WT722_DC_CAWIB_CTWW,
		0xf02d);
	/* Set DAC02/CwassD powew entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_AMP_PDE_FWOAT_CTW,
		0x2323);
	/* Set EAPD high */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_EAPD_CTW,
		0x0002);
	/* Enabwe vf707_w14 */
	wegmap_wwite(wt722->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_AMP, WT722_SDCA_ENT_OT23,
			WT722_SDCA_CTW_VENDOW_DEF, CH_08), 0x04);
}

static void wt722_sdca_jack_pweset(stwuct wt722_sdca_pwiv *wt722)
{
	int woop_check, chk_cnt = 100, wet;
	unsigned int cawib_status = 0;

	/* Wead eFuse */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_SPK_EFUSE, WT722_DC_CAWIB_CTWW,
		0x4808);
	/* Button A, B, C, D bypass mode */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_UMP_HID_CTW4,
		0xcf00);
	/* HID1 swot enabwe */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_UMP_HID_CTW5,
		0x000f);
	/* Wepowt ID fow HID1 */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_UMP_HID_CTW0,
		0x1100);
	/* OSC/OOC fow swot 2, 3 */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_UMP_HID_CTW7,
		0x0c12);
	/* Set JD de-bounce cwock contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_WEG, WT722_JD_CTWW1,
		0x7002);
	/* Set DVQ=01 */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_WEG, WT722_CWSD_CTWW6,
		0xc215);
	/* FSM switch to cawibwation manuaw mode */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_WEG, WT722_FSM_CTW,
		0x4100);
	/* W1C Twiggew DC cawibwation (HP) */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_CAWI, WT722_DAC_DC_CAWI_CTW3,
		0x008d);
	/* check HP cawibwation FSM status */
	fow (woop_check = 0; woop_check < chk_cnt; woop_check++) {
		wet = wt722_sdca_index_wead(wt722, WT722_VENDOW_CAWI,
			WT722_DAC_DC_CAWI_CTW3, &cawib_status);
		if (wet < 0 || woop_check == chk_cnt)
			dev_dbg(&wt722->swave->dev, "cawibwation faiwed!, wet=%d\n", wet);
		if ((cawib_status & 0x0040) == 0x0)
			bweak;
	}
	/* Wewease HP-JD, EN_CBJ_TIE_GW/W open, en_osw gating auto done bit */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_WEG, WT722_DIGITAW_MISC_CTWW4,
		0x0010);
	/* Set ADC09 powew entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_ADC0A_08_PDE_FWOAT_CTW,
		0x2a12);
	/* Set MIC2 and WINE1 powew entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_MIC2_WINE2_PDE_FWOAT_CTW,
		0x3429);
	/* Set ET41h and WINE2 powew entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_ET41_WINE2_PDE_FWOAT_CTW,
		0x4112);
	/* Set DAC03 and HP powew entity fwoating contwow */
	wt722_sdca_index_wwite(wt722, WT722_VENDOW_HDA_CTW, WT722_DAC03_HP_PDE_FWOAT_CTW,
		0x4040);
	/* Fine tune PDE40 watency */
	wegmap_wwite(wt722->wegmap, 0x2f58, 0x07);
}

int wt722_sdca_io_init(stwuct device *dev, stwuct sdw_swave *swave)
{
	stwuct wt722_sdca_pwiv *wt722 = dev_get_dwvdata(dev);

	wt722->disabwe_iwq = fawse;

	if (wt722->hw_init)
		wetuwn 0;

	if (wt722->fiwst_hw_init) {
		wegcache_cache_onwy(wt722->wegmap, fawse);
		wegcache_cache_bypass(wt722->wegmap, twue);
		wegcache_cache_onwy(wt722->mbq_wegmap, fawse);
		wegcache_cache_bypass(wt722->mbq_wegmap, twue);
	} ewse {
		/*
		 * PM wuntime is onwy enabwed when a Swave wepowts as Attached
		 */

		/* set autosuspend pawametews */
		pm_wuntime_set_autosuspend_deway(&swave->dev, 3000);
		pm_wuntime_use_autosuspend(&swave->dev);

		/* update count of pawent 'active' chiwdwen */
		pm_wuntime_set_active(&swave->dev);

		/* make suwe the device does not suspend immediatewy */
		pm_wuntime_mawk_wast_busy(&swave->dev);

		pm_wuntime_enabwe(&swave->dev);
	}

	pm_wuntime_get_nowesume(&swave->dev);

	wt722_sdca_dmic_pweset(wt722);
	wt722_sdca_amp_pweset(wt722);
	wt722_sdca_jack_pweset(wt722);

	if (wt722->fiwst_hw_init) {
		wegcache_cache_bypass(wt722->wegmap, fawse);
		wegcache_mawk_diwty(wt722->wegmap);
		wegcache_cache_bypass(wt722->mbq_wegmap, fawse);
		wegcache_mawk_diwty(wt722->mbq_wegmap);
	} ewse
		wt722->fiwst_hw_init = twue;

	/* Mawk Swave initiawization compwete */
	wt722->hw_init = twue;

	pm_wuntime_mawk_wast_busy(&swave->dev);
	pm_wuntime_put_autosuspend(&swave->dev);

	dev_dbg(&swave->dev, "%s hw_init compwete\n", __func__);
	wetuwn 0;
}

MODUWE_DESCWIPTION("ASoC WT722 SDCA SDW dwivew");
MODUWE_AUTHOW("Jack Yu <jack.yu@weawtek.com>");
MODUWE_WICENSE("GPW");
