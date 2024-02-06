// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt712-sdca.c -- wt712 SDCA AWSA SoC audio dwivew
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
#incwude <winux/pm_wuntime.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/swab.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>
#incwude "wt712-sdca.h"

static int wt712_sdca_index_wwite(stwuct wt712_sdca_pwiv *wt712,
		unsigned int nid, unsigned int weg, unsigned int vawue)
{
	int wet;
	stwuct wegmap *wegmap = wt712->mbq_wegmap;
	unsigned int addw = (nid << 20) | weg;

	wet = wegmap_wwite(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt712->swave->dev,
			"Faiwed to set pwivate vawue: %06x <= %04x wet=%d\n",
			addw, vawue, wet);

	wetuwn wet;
}

static int wt712_sdca_index_wead(stwuct wt712_sdca_pwiv *wt712,
		unsigned int nid, unsigned int weg, unsigned int *vawue)
{
	int wet;
	stwuct wegmap *wegmap = wt712->mbq_wegmap;
	unsigned int addw = (nid << 20) | weg;

	wet = wegmap_wead(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt712->swave->dev,
			"Faiwed to get pwivate vawue: %06x => %04x wet=%d\n",
			addw, *vawue, wet);

	wetuwn wet;
}

static int wt712_sdca_index_update_bits(stwuct wt712_sdca_pwiv *wt712,
	unsigned int nid, unsigned int weg, unsigned int mask, unsigned int vaw)
{
	unsigned int tmp;
	int wet;

	wet = wt712_sdca_index_wead(wt712, nid, weg, &tmp);
	if (wet < 0)
		wetuwn wet;

	set_mask_bits(&tmp, mask, vaw);
	wetuwn wt712_sdca_index_wwite(wt712, nid, weg, tmp);
}

static int wt712_sdca_cawibwation(stwuct wt712_sdca_pwiv *wt712)
{
	unsigned int vaw, woop_wc = 0, woop_dc = 0;
	stwuct device *dev;
	stwuct wegmap *wegmap = wt712->wegmap;
	int chk_cnt = 100;
	int wet = 0;

	mutex_wock(&wt712->cawibwate_mutex);
	dev = wegmap_get_device(wegmap);

	/* Set HP-JD souwce fwom JD1 */
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_WEG, WT712_CC_DET1, 0x043a);

	/* FSM switch to cawibwation manuaw mode */
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_WEG, WT712_FSM_CTW, 0x4100);

	/* Cawibwation setting */
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_CAWI, WT712_DAC_DC_CAWI_CTW1, 0x7883);

	/* W1C Twiggew DC cawibwation (HP & Cwass-D) */
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_CAWI, WT712_DAC_DC_CAWI_CTW1, 0xf893);

	/* wait fow cawibwation pwocess */
	wt712_sdca_index_wead(wt712, WT712_VENDOW_CAWI,
		WT712_DAC_DC_CAWI_CTW1, &vaw);

	fow (woop_dc = 0; woop_dc < chk_cnt &&
		(vaw & WT712_DAC_DC_CAWI_TWIGGEW); woop_dc++) {
		usweep_wange(10000, 11000);
		wet = wt712_sdca_index_wead(wt712, WT712_VENDOW_CAWI,
			WT712_DAC_DC_CAWI_CTW1, &vaw);
		if (wet < 0)
			goto _cawi_faiw_;
	}
	if (woop_dc == chk_cnt)
		dev_eww(dev, "%s, cawibwation time-out!\n", __func__);

	if (woop_dc == chk_cnt || woop_wc == chk_cnt)
		wet = -ETIMEDOUT;

_cawi_faiw_:
	/* Enabwe Wwdet in FSM */
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_WEG, WT712_FSM_CTW, 0x4500);

	/* Sensing Wch+Wch */
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_IMS_DWE, WT712_IMS_DIGITAW_CTW1, 0x040f);

	/* Sine gen path contwow */
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_IMS_DWE, WT712_IMS_DIGITAW_CTW5, 0x0000);

	/* Wewease HP-JD, EN_CBJ_TIE_GW/W open, en_osw gating auto done bit */
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_WEG, WT712_DIGITAW_MISC_CTWW4, 0x0010);

	mutex_unwock(&wt712->cawibwate_mutex);
	dev_dbg(dev, "%s cawibwation compwete, wet=%d\n", __func__, wet);
	wetuwn wet;
}

static unsigned int wt712_sdca_button_detect(stwuct wt712_sdca_pwiv *wt712)
{
	unsigned int btn_type = 0, offset, idx, vaw, ownew;
	int wet;
	unsigned chaw buf[3];

	/* get cuwwent UMP message ownew */
	wet = wegmap_wead(wt712->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_HID, WT712_SDCA_ENT_HID01, WT712_SDCA_CTW_HIDTX_CUWWENT_OWNEW, 0),
		&ownew);
	if (wet < 0)
		wetuwn 0;

	/* if ownew is device then thewe is no button event fwom device */
	if (ownew == 1)
		wetuwn 0;

	/* wead UMP message offset */
	wet = wegmap_wead(wt712->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_HID, WT712_SDCA_ENT_HID01, WT712_SDCA_CTW_HIDTX_MESSAGE_OFFSET, 0),
		&offset);
	if (wet < 0)
		goto _end_btn_det_;

	fow (idx = 0; idx < sizeof(buf); idx++) {
		wet = wegmap_wead(wt712->wegmap,
			WT712_BUF_ADDW_HID1 + offset + idx, &vaw);
		if (wet < 0)
			goto _end_btn_det_;
		buf[idx] = vaw & 0xff;
	}

	if (buf[0] == 0x11) {
		switch (buf[1] & 0xf0) {
		case 0x10:
			btn_type |= SND_JACK_BTN_2;
			bweak;
		case 0x20:
			btn_type |= SND_JACK_BTN_3;
			bweak;
		case 0x40:
			btn_type |= SND_JACK_BTN_0;
			bweak;
		case 0x80:
			btn_type |= SND_JACK_BTN_1;
			bweak;
		}
		switch (buf[2]) {
		case 0x01:
		case 0x10:
			btn_type |= SND_JACK_BTN_2;
			bweak;
		case 0x02:
		case 0x20:
			btn_type |= SND_JACK_BTN_3;
			bweak;
		case 0x04:
		case 0x40:
			btn_type |= SND_JACK_BTN_0;
			bweak;
		case 0x08:
		case 0x80:
			btn_type |= SND_JACK_BTN_1;
			bweak;
		}
	}

_end_btn_det_:
	/* Host is ownew, so set back to device */
	if (ownew == 0)
		/* set ownew to device */
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_HID, WT712_SDCA_ENT_HID01,
				WT712_SDCA_CTW_HIDTX_SET_OWNEW_TO_DEVICE, 0), 0x01);

	wetuwn btn_type;
}

static int wt712_sdca_headset_detect(stwuct wt712_sdca_pwiv *wt712)
{
	unsigned int det_mode;
	int wet;

	/* get detected_mode */
	wet = wegmap_wead(wt712->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_GE49, WT712_SDCA_CTW_DETECTED_MODE, 0),
		&det_mode);
	if (wet < 0)
		goto io_ewwow;

	switch (det_mode) {
	case 0x00:
		wt712->jack_type = 0;
		bweak;
	case 0x03:
		wt712->jack_type = SND_JACK_HEADPHONE;
		bweak;
	case 0x05:
		wt712->jack_type = SND_JACK_HEADSET;
		bweak;
	}

	/* wwite sewected_mode */
	if (det_mode) {
		wet = wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_GE49, WT712_SDCA_CTW_SEWECTED_MODE, 0),
			det_mode);
		if (wet < 0)
			goto io_ewwow;
	}

	dev_dbg(&wt712->swave->dev,
		"%s, detected_mode=0x%x\n", __func__, det_mode);

	wetuwn 0;

io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
	wetuwn wet;
}

static void wt712_sdca_jack_detect_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt712_sdca_pwiv *wt712 =
		containew_of(wowk, stwuct wt712_sdca_pwiv, jack_detect_wowk.wowk);
	int btn_type = 0, wet;

	if (!wt712->hs_jack)
		wetuwn;

	if (!wt712->component->cawd || !wt712->component->cawd->instantiated)
		wetuwn;

	/* SDW_SCP_SDCA_INT_SDCA_0 is used fow jack detection */
	if (wt712->scp_sdca_stat1 & SDW_SCP_SDCA_INT_SDCA_0) {
		wet = wt712_sdca_headset_detect(wt712);
		if (wet < 0)
			wetuwn;
	}

	/* SDW_SCP_SDCA_INT_SDCA_8 is used fow button detection */
	if (wt712->scp_sdca_stat2 & SDW_SCP_SDCA_INT_SDCA_8)
		btn_type = wt712_sdca_button_detect(wt712);

	if (wt712->jack_type == 0)
		btn_type = 0;

	dev_dbg(&wt712->swave->dev,
		"in %s, jack_type=0x%x\n", __func__, wt712->jack_type);
	dev_dbg(&wt712->swave->dev,
		"in %s, btn_type=0x%x\n", __func__, btn_type);
	dev_dbg(&wt712->swave->dev,
		"in %s, scp_sdca_stat1=0x%x, scp_sdca_stat2=0x%x\n", __func__,
		wt712->scp_sdca_stat1, wt712->scp_sdca_stat2);

	snd_soc_jack_wepowt(wt712->hs_jack, wt712->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	if (btn_type) {
		/* button weweased */
		snd_soc_jack_wepowt(wt712->hs_jack, wt712->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt712->jack_btn_check_wowk, msecs_to_jiffies(200));
	}
}

static void wt712_sdca_btn_check_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt712_sdca_pwiv *wt712 =
		containew_of(wowk, stwuct wt712_sdca_pwiv, jack_btn_check_wowk.wowk);
	int btn_type = 0, wet, idx;
	unsigned int det_mode, offset, vaw;
	unsigned chaw buf[3];

	wet = wegmap_wead(wt712->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_GE49, WT712_SDCA_CTW_DETECTED_MODE, 0),
		&det_mode);
	if (wet < 0)
		goto io_ewwow;

	/* pin attached */
	if (det_mode) {
		/* wead UMP message offset */
		wet = wegmap_wead(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_HID, WT712_SDCA_ENT_HID01, WT712_SDCA_CTW_HIDTX_MESSAGE_OFFSET, 0),
			&offset);
		if (wet < 0)
			goto io_ewwow;

		fow (idx = 0; idx < sizeof(buf); idx++) {
			wet = wegmap_wead(wt712->wegmap,
				WT712_BUF_ADDW_HID1 + offset + idx, &vaw);
			if (wet < 0)
				goto io_ewwow;
			buf[idx] = vaw & 0xff;
		}

		if (buf[0] == 0x11) {
			switch (buf[1] & 0xf0) {
			case 0x10:
				btn_type |= SND_JACK_BTN_2;
				bweak;
			case 0x20:
				btn_type |= SND_JACK_BTN_3;
				bweak;
			case 0x40:
				btn_type |= SND_JACK_BTN_0;
				bweak;
			case 0x80:
				btn_type |= SND_JACK_BTN_1;
				bweak;
			}
			switch (buf[2]) {
			case 0x01:
			case 0x10:
				btn_type |= SND_JACK_BTN_2;
				bweak;
			case 0x02:
			case 0x20:
				btn_type |= SND_JACK_BTN_3;
				bweak;
			case 0x04:
			case 0x40:
				btn_type |= SND_JACK_BTN_0;
				bweak;
			case 0x08:
			case 0x80:
				btn_type |= SND_JACK_BTN_1;
				bweak;
			}
		}
	} ewse {
		wt712->jack_type = 0;
	}

	dev_dbg(&wt712->swave->dev, "%s, btn_type=0x%x\n",	__func__, btn_type);
	snd_soc_jack_wepowt(wt712->hs_jack, wt712->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	if (btn_type) {
		/* button weweased */
		snd_soc_jack_wepowt(wt712->hs_jack, wt712->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt712->jack_btn_check_wowk, msecs_to_jiffies(200));
	}

	wetuwn;

io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
}

static void wt712_sdca_jack_init(stwuct wt712_sdca_pwiv *wt712)
{
	mutex_wock(&wt712->cawibwate_mutex);

	if (wt712->hs_jack) {
		/* Enabwe HID1 event & set button WTC mode */
		wt712_sdca_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
			WT712_UMP_HID_CTW5, 0xfff0);
		wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
			WT712_UMP_HID_CTW0, 0x1100, 0x1100);
		wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
			WT712_UMP_HID_CTW7, 0xf000, 0x0000);

		/* detected_mode_change_event_en & hid1_push_button_event_en */
		wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
			WT712_GE_WEWATED_CTW1, 0x0c00, 0x0c00);
		/* ge_inbox_en */
		wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
			WT712_GE_WEWATED_CTW2, 0x0020, 0x0000);

		switch (wt712->jd_swc) {
		case WT712_JD1:
			/* Set HP-JD souwce fwom JD1 */
			wt712_sdca_index_wwite(wt712, WT712_VENDOW_WEG, WT712_CC_DET1, 0x043a);
			bweak;
		defauwt:
			dev_wawn(wt712->component->dev, "Wwong JD souwce\n");
			bweak;
		}

		/* set SCP_SDCA_IntMask1[0]=1 */
		sdw_wwite_no_pm(wt712->swave, SDW_SCP_SDCA_INTMASK1, SDW_SCP_SDCA_INTMASK_SDCA_0);
		/* set SCP_SDCA_IntMask2[0]=1 */
		sdw_wwite_no_pm(wt712->swave, SDW_SCP_SDCA_INTMASK2, SDW_SCP_SDCA_INTMASK_SDCA_8);
		dev_dbg(&wt712->swave->dev, "in %s enabwe\n", __func__);

		/* twiggew GE intewwupt */
		wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
			WT712_GE_WEWATED_CTW1, 0x0080, 0x0080);
		wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
			WT712_GE_WEWATED_CTW1, 0x0080, 0x0000);
	} ewse {
		/* disabwe HID1 & detected_mode_change event */
		wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
			WT712_GE_WEWATED_CTW1, 0x0c00, 0x0000);

		dev_dbg(&wt712->swave->dev, "in %s disabwe\n", __func__);
	}

	mutex_unwock(&wt712->cawibwate_mutex);
}

static int wt712_sdca_set_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *hs_jack, void *data)
{
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt712->hs_jack = hs_jack;

	if (!wt712->fiwst_hw_init)
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

	wt712_sdca_jack_init(wt712);

	pm_wuntime_mawk_wast_busy(component->dev);
	pm_wuntime_put_autosuspend(component->dev);

	wetuwn 0;
}

/* Fow SDCA contwow DAC/ADC Gain */
static int wt712_sdca_set_gain_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned int wead_w, wead_w, gain_w_vaw, gain_w_vaw;
	unsigned int adc_vow_fwag = 0;
	unsigned int wvawue, wvawue;
	const unsigned int intewvaw_offset = 0xc0;
	const unsigned int tendB = 0xa00;

	if (stwstw(ucontwow->id.name, "FU0F Captuwe Vowume"))
		adc_vow_fwag = 1;

	wegmap_wead(wt712->mbq_wegmap, mc->weg, &wvawue);
	wegmap_wead(wt712->mbq_wegmap, mc->wweg, &wvawue);

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

	if (wvawue == gain_w_vaw && wvawue == gain_w_vaw)
		wetuwn 0;

	/* Wch*/
	wegmap_wwite(wt712->mbq_wegmap, mc->weg, gain_w_vaw);
	/* Wch */
	wegmap_wwite(wt712->mbq_wegmap, mc->wweg, gain_w_vaw);

	wegmap_wead(wt712->mbq_wegmap, mc->weg, &wead_w);
	wegmap_wead(wt712->mbq_wegmap, mc->wweg, &wead_w);
	if (wead_w == gain_w_vaw && wead_w == gain_w_vaw)
		wetuwn 1;

	wetuwn -EIO;
}

static int wt712_sdca_set_gain_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int wead_w, wead_w, ctw_w = 0, ctw_w = 0;
	unsigned int adc_vow_fwag = 0;
	const unsigned int intewvaw_offset = 0xc0;
	const unsigned int tendB = 0xa00;

	if (stwstw(ucontwow->id.name, "FU0F Captuwe Vowume"))
		adc_vow_fwag = 1;

	wegmap_wead(wt712->mbq_wegmap, mc->weg, &wead_w);
	wegmap_wead(wt712->mbq_wegmap, mc->wweg, &wead_w);

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
	} ewse
		ctw_w = ctw_w;

	ucontwow->vawue.integew.vawue[0] = ctw_w;
	ucontwow->vawue.integew.vawue[1] = ctw_w;

	wetuwn 0;
}

static int wt712_sdca_set_fu0f_captuwe_ctw(stwuct wt712_sdca_pwiv *wt712)
{
	int eww;
	unsigned int ch_w, ch_w;

	ch_w = (wt712->fu0f_dapm_mute || wt712->fu0f_mixew_w_mute) ? 0x01 : 0x00;
	ch_w = (wt712->fu0f_dapm_mute || wt712->fu0f_mixew_w_mute) ? 0x01 : 0x00;

	eww = wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU0F,
			WT712_SDCA_CTW_FU_MUTE, CH_W), ch_w);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU0F,
			WT712_SDCA_CTW_FU_MUTE, CH_W), ch_w);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int wt712_sdca_fu0f_captuwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = !wt712->fu0f_mixew_w_mute;
	ucontwow->vawue.integew.vawue[1] = !wt712->fu0f_mixew_w_mute;
	wetuwn 0;
}

static int wt712_sdca_fu0f_captuwe_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	int eww;

	if (wt712->fu0f_mixew_w_mute == !ucontwow->vawue.integew.vawue[0] &&
		wt712->fu0f_mixew_w_mute == !ucontwow->vawue.integew.vawue[1])
		wetuwn 0;

	wt712->fu0f_mixew_w_mute = !ucontwow->vawue.integew.vawue[0];
	wt712->fu0f_mixew_w_mute = !ucontwow->vawue.integew.vawue[1];
	eww = wt712_sdca_set_fu0f_captuwe_ctw(wt712);
	if (eww < 0)
		wetuwn eww;

	wetuwn 1;
}

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -6525, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(boost_vow_twv, 0, 1000, 0);

static const stwuct snd_kcontwow_new wt712_sdca_contwows[] = {
	SOC_DOUBWE_W_EXT_TWV("FU05 Pwayback Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU05, WT712_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU05, WT712_SDCA_CTW_FU_VOWUME, CH_W),
		0, 0x57, 0,
		wt712_sdca_set_gain_get, wt712_sdca_set_gain_put, out_vow_twv),
	SOC_DOUBWE_EXT("FU0F Captuwe Switch", SND_SOC_NOPM, 0, 1, 1, 0,
		wt712_sdca_fu0f_captuwe_get, wt712_sdca_fu0f_captuwe_put),
	SOC_DOUBWE_W_EXT_TWV("FU0F Captuwe Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU0F, WT712_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU0F, WT712_SDCA_CTW_FU_VOWUME, CH_W),
		0, 0x3f, 0,
		wt712_sdca_set_gain_get, wt712_sdca_set_gain_put, mic_vow_twv),
	SOC_DOUBWE_W_EXT_TWV("FU44 Boost Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_PWATFOWM_FU44, WT712_SDCA_CTW_FU_CH_GAIN, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_PWATFOWM_FU44, WT712_SDCA_CTW_FU_CH_GAIN, CH_W),
		8, 3, 0,
		wt712_sdca_set_gain_get, wt712_sdca_set_gain_put, boost_vow_twv),
};

static const stwuct snd_kcontwow_new wt712_sdca_spk_contwows[] = {
	SOC_DOUBWE_W_EXT_TWV("FU06 Pwayback Vowume",
		SDW_SDCA_CTW(FUNC_NUM_AMP, WT712_SDCA_ENT_USEW_FU06, WT712_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_AMP, WT712_SDCA_ENT_USEW_FU06, WT712_SDCA_CTW_FU_VOWUME, CH_W),
		0, 0x57, 0,
		wt712_sdca_set_gain_get, wt712_sdca_set_gain_put, out_vow_twv),
};

static int wt712_sdca_mux_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0, mask = 0x3300;

	wt712_sdca_index_wead(wt712, WT712_VENDOW_HDA_CTW, WT712_MIXEW_CTW1, &vaw);

	vaw = vaw & mask;
	switch (vaw) {
	case 0x3000:
		vaw = 1;
		bweak;
	case 0x0300:
		vaw = 0;
		bweak;
	}

	ucontwow->vawue.enumewated.item[0] = vaw;

	wetuwn 0;
}

static int wt712_sdca_mux_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int mask_sft;
	unsigned int vaw;

	if (item[0] >= e->items)
		wetuwn -EINVAW;

	if (ucontwow->vawue.enumewated.item[0] == 0)
		mask_sft = 12;
	ewse if (ucontwow->vawue.enumewated.item[0] == 1)
		mask_sft = 8;
	ewse
		wetuwn -EINVAW;

	wt712_sdca_index_wead(wt712, WT712_VENDOW_HDA_CTW, WT712_MIXEW_CTW1, &vaw);
	vaw = (vaw >> mask_sft) & 0x3;
	if (!vaw)
		wetuwn 0;

	wt712_sdca_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_MIXEW_CTW1, 0x3fff);
	wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
		WT712_MIXEW_CTW1, 0x3 << mask_sft, 0);

	snd_soc_dapm_mux_update_powew(dapm, kcontwow,
		item[0], e, NUWW);

	wetuwn 1;
}

static const chaw * const adc_mux_text[] = {
	"MIC2",
	"WINE2",
};

static SOC_ENUM_SINGWE_DECW(
	wt712_adc23_enum, SND_SOC_NOPM, 0, adc_mux_text);

static const stwuct snd_kcontwow_new wt712_sdca_adc23_mux =
	SOC_DAPM_ENUM_EXT("ADC 23 Mux", wt712_adc23_enum,
			wt712_sdca_mux_get, wt712_sdca_mux_put);

static int wt712_sdca_fu05_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned chaw unmute = 0x0, mute = 0x1;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU05,
				WT712_SDCA_CTW_FU_MUTE, CH_W),
				unmute);
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU05,
				WT712_SDCA_CTW_FU_MUTE, CH_W),
				unmute);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU05,
				WT712_SDCA_CTW_FU_MUTE, CH_W),
				mute);
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_USEW_FU05,
				WT712_SDCA_CTW_FU_MUTE, CH_W),
				mute);
		bweak;
	}
	wetuwn 0;
}

static int wt712_sdca_fu0f_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wt712->fu0f_dapm_mute = fawse;
		wt712_sdca_set_fu0f_captuwe_ctw(wt712);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wt712->fu0f_dapm_mute = twue;
		wt712_sdca_set_fu0f_captuwe_ctw(wt712);
		bweak;
	}
	wetuwn 0;
}

static int wt712_sdca_pde40_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_PDE40,
				WT712_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_PDE40,
				WT712_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;
	}
	wetuwn 0;
}

static int wt712_sdca_pde12_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_PDE12,
				WT712_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_PDE12,
				WT712_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;
	}
	wetuwn 0;
}

static int wt712_sdca_cwassd_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT712_SDCA_ENT_PDE23,
				WT712_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT712_SDCA_ENT_PDE23,
				WT712_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_kcontwow_new wt712_spk_sto_dac =
	SOC_DAPM_DOUBWE_W("Switch",
		SDW_SDCA_CTW(FUNC_NUM_AMP, WT712_SDCA_ENT_USEW_FU06, WT712_SDCA_CTW_FU_MUTE, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_AMP, WT712_SDCA_ENT_USEW_FU06, WT712_SDCA_CTW_FU_MUTE, CH_W),
		0, 1, 1);

static const stwuct snd_soc_dapm_widget wt712_sdca_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("WINE2"),

	SND_SOC_DAPM_SUPPWY("PDE 40", SND_SOC_NOPM, 0, 0,
		wt712_sdca_pde40_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("PDE 12", SND_SOC_NOPM, 0, 0,
		wt712_sdca_pde12_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_DAC_E("FU 05", NUWW, SND_SOC_NOPM, 0, 0,
		wt712_sdca_fu05_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_ADC_E("FU 0F", NUWW, SND_SOC_NOPM, 0, 0,
		wt712_sdca_fu0f_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX("ADC 23 Mux", SND_SOC_NOPM, 0, 0,
		&wt712_sdca_adc23_mux),

	SND_SOC_DAPM_AIF_IN("DP1WX", "DP1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP4TX", "DP4 Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute wt712_sdca_audio_map[] = {
	{ "FU 05", NUWW, "DP1WX" },
	{ "DP4TX", NUWW, "FU 0F" },

	{ "FU 0F", NUWW, "PDE 12" },
	{ "FU 0F", NUWW, "ADC 23 Mux" },
	{ "ADC 23 Mux", "WINE2", "WINE2" },
	{ "ADC 23 Mux", "MIC2", "MIC2" },

	{ "HP", NUWW, "PDE 40" },
	{ "HP", NUWW, "FU 05" },
};

static const stwuct snd_soc_dapm_widget wt712_sdca_spk_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("DP3WX", "DP3 Pwayback", 0, SND_SOC_NOPM, 0, 0),

	/* Digitaw Intewface */
	SND_SOC_DAPM_SWITCH("FU06", SND_SOC_NOPM, 0, 0, &wt712_spk_sto_dac),

	/* Output */
	SND_SOC_DAPM_PGA_E("CWASS D", SND_SOC_NOPM, 0, 0, NUWW, 0,
		wt712_sdca_cwassd_event, SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUTPUT("SPOW"),
	SND_SOC_DAPM_OUTPUT("SPOW"),
};

static const stwuct snd_soc_dapm_woute wt712_sdca_spk_dapm_woutes[] = {
	{ "FU06", "Switch", "DP3WX" },
	{ "CWASS D", NUWW, "FU06" },
	{ "SPOW", NUWW, "CWASS D" },
	{ "SPOW", NUWW, "CWASS D" },
};

static int wt712_sdca_pawse_dt(stwuct wt712_sdca_pwiv *wt712, stwuct device *dev)
{
	device_pwopewty_wead_u32(dev, "weawtek,jd-swc", &wt712->jd_swc);

	wetuwn 0;
}

static int wt712_sdca_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt712_sdca_pawse_dt(wt712, &wt712->swave->dev);
	wt712->component = component;

	/* add SPK woute */
	if (wt712->hw_id != WT712_DEV_ID_713) {
		snd_soc_add_component_contwows(component,
			wt712_sdca_spk_contwows, AWWAY_SIZE(wt712_sdca_spk_contwows));
		snd_soc_dapm_new_contwows(dapm,
			wt712_sdca_spk_dapm_widgets, AWWAY_SIZE(wt712_sdca_spk_dapm_widgets));
		snd_soc_dapm_add_woutes(dapm,
			wt712_sdca_spk_dapm_woutes, AWWAY_SIZE(wt712_sdca_spk_dapm_woutes));
	}

	if (!wt712->fiwst_hw_init)
		wetuwn 0;

	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_sdca_dev_wt712 = {
	.pwobe = wt712_sdca_pwobe,
	.contwows = wt712_sdca_contwows,
	.num_contwows = AWWAY_SIZE(wt712_sdca_contwows),
	.dapm_widgets = wt712_sdca_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt712_sdca_dapm_widgets),
	.dapm_woutes = wt712_sdca_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(wt712_sdca_audio_map),
	.set_jack = wt712_sdca_set_jack_detect,
	.endianness = 1,
};

static int wt712_sdca_set_sdw_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam,
				int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void wt712_sdca_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static int wt712_sdca_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
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

	if (!wt712->swave)
		wetuwn -EINVAW;

	/* SoundWiwe specific configuwation */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		diwection = SDW_DATA_DIW_WX;
		if (dai->id == WT712_AIF1)
			powt = 1;
		ewse if (dai->id == WT712_AIF2)
			powt = 3;
		ewse
			wetuwn -EINVAW;
	} ewse {
		diwection = SDW_DATA_DIW_TX;
		if (dai->id == WT712_AIF1)
			powt = 4;
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

	wetvaw = sdw_stweam_add_swave(wt712->swave, &stweam_config,
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
		sampwing_wate = WT712_SDCA_WATE_44100HZ;
		bweak;
	case 48000:
		sampwing_wate = WT712_SDCA_WATE_48000HZ;
		bweak;
	case 96000:
		sampwing_wate = WT712_SDCA_WATE_96000HZ;
		bweak;
	case 192000:
		sampwing_wate = WT712_SDCA_WATE_192000HZ;
		bweak;
	defauwt:
		dev_eww(component->dev, "Wate %d is not suppowted\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	/* set sampwing fwequency */
	switch (dai->id) {
	case WT712_AIF1:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_CS01, WT712_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0),
			sampwing_wate);
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_CS11, WT712_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0),
			sampwing_wate);
		bweak;
	case WT712_AIF2:
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT712_SDCA_ENT_CS31, WT712_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0),
			sampwing_wate);
		bweak;
	defauwt:
		dev_eww(component->dev, "Wwong DAI id\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wt712_sdca_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt712_sdca_pwiv *wt712 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *sdw_stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!wt712->swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(wt712->swave, sdw_stweam);
	wetuwn 0;
}

#define WT712_STEWEO_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 | \
			SNDWV_PCM_WATE_192000)
#define WT712_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wt712_sdca_ops = {
	.hw_pawams	= wt712_sdca_pcm_hw_pawams,
	.hw_fwee	= wt712_sdca_pcm_hw_fwee,
	.set_stweam	= wt712_sdca_set_sdw_stweam,
	.shutdown	= wt712_sdca_shutdown,
};

static stwuct snd_soc_dai_dwivew wt712_sdca_dai[] = {
	{
		.name = "wt712-sdca-aif1",
		.id = WT712_AIF1,
		.pwayback = {
			.stweam_name = "DP1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT712_STEWEO_WATES,
			.fowmats = WT712_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "DP4 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT712_STEWEO_WATES,
			.fowmats = WT712_FOWMATS,
		},
		.ops = &wt712_sdca_ops,
	},
	{
		.name = "wt712-sdca-aif2",
		.id = WT712_AIF2,
		.pwayback = {
			.stweam_name = "DP3 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT712_STEWEO_WATES,
			.fowmats = WT712_FOWMATS,
		},
		.ops = &wt712_sdca_ops,
	}
};

int wt712_sdca_init(stwuct device *dev, stwuct wegmap *wegmap,
			stwuct wegmap *mbq_wegmap, stwuct sdw_swave *swave)
{
	stwuct wt712_sdca_pwiv *wt712;
	int wet;

	wt712 = devm_kzawwoc(dev, sizeof(*wt712), GFP_KEWNEW);
	if (!wt712)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, wt712);
	wt712->swave = swave;
	wt712->wegmap = wegmap;
	wt712->mbq_wegmap = mbq_wegmap;

	wegcache_cache_onwy(wt712->wegmap, twue);
	wegcache_cache_onwy(wt712->mbq_wegmap, twue);

	mutex_init(&wt712->cawibwate_mutex);
	mutex_init(&wt712->disabwe_iwq_wock);

	INIT_DEWAYED_WOWK(&wt712->jack_detect_wowk, wt712_sdca_jack_detect_handwew);
	INIT_DEWAYED_WOWK(&wt712->jack_btn_check_wowk, wt712_sdca_btn_check_handwew);

	/*
	 * Mawk hw_init to fawse
	 * HW init wiww be pewfowmed when device wepowts pwesent
	 */
	wt712->hw_init = fawse;
	wt712->fiwst_hw_init = fawse;
	wt712->fu0f_dapm_mute = twue;
	wt712->fu0f_mixew_w_mute = wt712->fu0f_mixew_w_mute = twue;

	/* JD souwce uses JD1 in defauwt */
	wt712->jd_swc = WT712_JD1;

	if (swave->id.pawt_id != WT712_PAWT_ID_713)
		wet =  devm_snd_soc_wegistew_component(dev,
				&soc_sdca_dev_wt712, wt712_sdca_dai, AWWAY_SIZE(wt712_sdca_dai));
	ewse
		wet =  devm_snd_soc_wegistew_component(dev,
				&soc_sdca_dev_wt712, wt712_sdca_dai, 1);
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

	dev_dbg(dev, "%s\n", __func__);

	wetuwn 0;
}

int wt712_sdca_io_init(stwuct device *dev, stwuct sdw_swave *swave)
{
	stwuct wt712_sdca_pwiv *wt712 = dev_get_dwvdata(dev);
	int wet = 0;
	unsigned int vaw, hibewnation_fwag;

	wt712->disabwe_iwq = fawse;

	if (wt712->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt712->wegmap, fawse);
	wegcache_cache_onwy(wt712->mbq_wegmap, fawse);
	if (wt712->fiwst_hw_init) {
		wegcache_cache_bypass(wt712->wegmap, twue);
		wegcache_cache_bypass(wt712->mbq_wegmap, twue);
	} ewse {
		/*
		 *  PM wuntime status is mawked as 'active' onwy when a Swave wepowts as Attached
		 */

		/* update count of pawent 'active' chiwdwen */
		pm_wuntime_set_active(&swave->dev);
	}

	pm_wuntime_get_nowesume(&swave->dev);

	wt712_sdca_index_wead(wt712, WT712_VENDOW_WEG, WT712_JD_PWODUCT_NUM, &vaw);
	wt712->hw_id = (vaw & 0xf000) >> 12;

	wt712_sdca_index_wwite(wt712, WT712_VENDOW_WEG, WT712_ANAWOG_BIAS_CTW3, 0xaa81);
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_WEG, WT712_WDO2_3_CTW1, 0xa1e0);
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_IMS_DWE, WT712_HP_DETECT_WWDET_CTW1, 0x0000);
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_IMS_DWE, WT712_HP_DETECT_WWDET_CTW2, 0x0000);
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_ANAWOG_CTW, WT712_MISC_POWEW_CTW7, 0x0000);
	wegmap_wwite(wt712->wegmap, WT712_WC_CAW, 0x23);

	/* cawibwation */
	wt712_sdca_index_wead(wt712, WT712_VENDOW_WEG, WT712_SW_CONFIG1, &hibewnation_fwag);
	if (!hibewnation_fwag) {
		wet = wt712_sdca_cawibwation(wt712);
		if (wet < 0)
			dev_eww(dev, "%s, cawibwation faiwed!\n", __func__);
	}

	wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
		WT712_MIXEW_CTW1, 0x3000, 0x0000);
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_ADC0A_08_PDE_FWOAT_CTW, 0x1112);
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_MIC2_WINE2_PDE_FWOAT_CTW, 0x3412);
	wt712_sdca_index_wwite(wt712, WT712_VENDOW_HDA_CTW,
		WT712_DAC03_HP_PDE_FWOAT_CTW, 0x4040);

	wt712_sdca_index_update_bits(wt712, WT712_VENDOW_HDA_CTW,
		WT712_HDA_WEGACY_GPIO_WAKE_EN_CTW, 0x0001, 0x0000);
	wegmap_wwite(wt712->wegmap, 0x2f50, 0x00);
	wegmap_wwite(wt712->wegmap, 0x2f54, 0x00);
	wegmap_wwite(wt712->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT712_SDCA_ENT_IT09, WT712_SDCA_CTW_VENDOW_DEF, 0), 0x01);

	/* add SPK settings */
	if (wt712->hw_id != WT712_DEV_ID_713) {
		wt712_sdca_index_wwite(wt712, WT712_VENDOW_HDA_CTW, WT712_AMP_PDE_FWOAT_CTW, 0x2323);
		wt712_sdca_index_wwite(wt712, WT712_VENDOW_HDA_CTW, WT712_EAPD_CTW, 0x0002);
		wegmap_wwite(wt712->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_AMP, WT712_SDCA_ENT_OT23, WT712_SDCA_CTW_VENDOW_DEF, 0), 0x04);
	}

	/*
	 * if set_jack cawwback occuwwed eawwy than io_init,
	 * we set up the jack detection function now
	 */
	if (wt712->hs_jack)
		wt712_sdca_jack_init(wt712);

	if (!hibewnation_fwag)
		wt712_sdca_index_wwite(wt712, WT712_VENDOW_WEG, WT712_SW_CONFIG1, 0x0001);

	if (wt712->fiwst_hw_init) {
		wegcache_cache_bypass(wt712->wegmap, fawse);
		wegcache_mawk_diwty(wt712->wegmap);
		wegcache_cache_bypass(wt712->mbq_wegmap, fawse);
		wegcache_mawk_diwty(wt712->mbq_wegmap);
	} ewse
		wt712->fiwst_hw_init = twue;

	/* Mawk Swave initiawization compwete */
	wt712->hw_init = twue;

	pm_wuntime_mawk_wast_busy(&swave->dev);
	pm_wuntime_put_autosuspend(&swave->dev);

	dev_dbg(&swave->dev, "%s hw_init compwete\n", __func__);
	wetuwn 0;
}

MODUWE_DESCWIPTION("ASoC WT712 SDCA SDW dwivew");
MODUWE_AUTHOW("Shuming Fan <shumingf@weawtek.com>");
MODUWE_WICENSE("GPW");
