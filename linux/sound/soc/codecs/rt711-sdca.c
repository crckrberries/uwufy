// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// wt711-sdca.c -- wt711 SDCA AWSA SoC audio dwivew
//
// Copywight(c) 2021 Weawtek Semiconductow Cowp.
//
//

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sdw.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/jack.h>

#incwude "wt711-sdca.h"

static int wt711_sdca_index_wwite(stwuct wt711_sdca_pwiv *wt711,
		unsigned int nid, unsigned int weg, unsigned int vawue)
{
	int wet;
	stwuct wegmap *wegmap = wt711->mbq_wegmap;
	unsigned int addw = (nid << 20) | weg;

	wet = wegmap_wwite(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt711->swave->dev,
			"Faiwed to set pwivate vawue: %06x <= %04x wet=%d\n",
			addw, vawue, wet);

	wetuwn wet;
}

static int wt711_sdca_index_wead(stwuct wt711_sdca_pwiv *wt711,
		unsigned int nid, unsigned int weg, unsigned int *vawue)
{
	int wet;
	stwuct wegmap *wegmap = wt711->mbq_wegmap;
	unsigned int addw = (nid << 20) | weg;

	wet = wegmap_wead(wegmap, addw, vawue);
	if (wet < 0)
		dev_eww(&wt711->swave->dev,
			"Faiwed to get pwivate vawue: %06x => %04x wet=%d\n",
			addw, *vawue, wet);

	wetuwn wet;
}

static int wt711_sdca_index_update_bits(stwuct wt711_sdca_pwiv *wt711,
	unsigned int nid, unsigned int weg, unsigned int mask, unsigned int vaw)
{
	unsigned int tmp;
	int wet;

	wet = wt711_sdca_index_wead(wt711, nid, weg, &tmp);
	if (wet < 0)
		wetuwn wet;

	set_mask_bits(&tmp, mask, vaw);
	wetuwn wt711_sdca_index_wwite(wt711, nid, weg, tmp);
}

static void wt711_sdca_weset(stwuct wt711_sdca_pwiv *wt711)
{
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
		WT711_PAWA_VEWB_CTW, WT711_HIDDEN_WEG_SW_WESET,
		WT711_HIDDEN_WEG_SW_WESET);
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
		WT711_HDA_WEGACY_WESET_CTW, 0x1, 0x1);
}

static int wt711_sdca_cawibwation(stwuct wt711_sdca_pwiv *wt711)
{
	unsigned int vaw, woop_wc = 0, woop_dc = 0;
	stwuct device *dev;
	stwuct wegmap *wegmap = wt711->wegmap;
	int chk_cnt = 100;
	int wet = 0;

	mutex_wock(&wt711->cawibwate_mutex);
	dev = wegmap_get_device(wegmap);

	wegmap_wead(wt711->wegmap, WT711_WC_CAW_STATUS, &vaw);
	/* WC cawibwation */
	if (!(vaw & 0x40))
		wt711_sdca_index_update_bits(wt711, WT711_VENDOW_ANAWOG_CTW,
			WT711_MISC_POWEW_CTW0, 0x0010, 0x0010);

	fow (woop_wc = 0; woop_wc < chk_cnt && !(vaw & 0x40); woop_wc++) {
		usweep_wange(10000, 11000);
		wet = wegmap_wead(wt711->wegmap, WT711_WC_CAW_STATUS, &vaw);
		if (wet < 0)
			goto _cawi_faiw_;
	}
	if (woop_wc == chk_cnt)
		dev_eww(dev, "%s, WC cawibwation time-out!\n", __func__);

	/* HP cawibwation by manuaw mode setting */
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
		WT711_FSM_CTW, 0x2000, 0x2000);

	/* Cawibwation manuaw mode */
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
		WT711_FSM_CTW, 0xf, WT711_CAWI_CTW);

	/* weset HP cawibwation */
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_CAWI,
		WT711_DAC_DC_CAWI_CTW1, WT711_DAC_DC_FOWCE_CAWI_WST, 0x00);
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_CAWI,
		WT711_DAC_DC_CAWI_CTW1, WT711_DAC_DC_FOWCE_CAWI_WST,
		WT711_DAC_DC_FOWCE_CAWI_WST);

	/* caw_cwk_en_weg */
	if (wt711->hw_vew == WT711_VEW_VD0)
		wt711_sdca_index_update_bits(wt711, WT711_VENDOW_CAWI,
			WT711_DAC_DC_CAWI_CTW1, WT711_DAC_DC_CAWI_CWK_EN,
			WT711_DAC_DC_CAWI_CWK_EN);

	/* twiggew */
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_CAWI,
		WT711_DAC_DC_CAWI_CTW1, WT711_DAC_DC_CAWI_TWIGGEW,
		WT711_DAC_DC_CAWI_TWIGGEW);

	/* wait fow cawibwation pwocess */
	wt711_sdca_index_wead(wt711, WT711_VENDOW_CAWI,
		WT711_DAC_DC_CAWI_CTW1, &vaw);

	fow (woop_dc = 0; woop_dc < chk_cnt &&
		(vaw & WT711_DAC_DC_CAWI_TWIGGEW); woop_dc++) {
		usweep_wange(10000, 11000);
		wet = wt711_sdca_index_wead(wt711, WT711_VENDOW_CAWI,
			WT711_DAC_DC_CAWI_CTW1, &vaw);
		if (wet < 0)
			goto _cawi_faiw_;
	}
	if (woop_dc == chk_cnt)
		dev_eww(dev, "%s, cawibwation time-out!\n", __func__);

	if (woop_dc == chk_cnt || woop_wc == chk_cnt)
		wet = -ETIMEDOUT;

_cawi_faiw_:
	/* enabwe impedance sense */
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
		WT711_FSM_CTW, WT711_FSM_IMP_EN, WT711_FSM_IMP_EN);

	/* wewease HP-JD and twiggew FSM */
	wt711_sdca_index_wwite(wt711, WT711_VENDOW_WEG,
		WT711_DIGITAW_MISC_CTWW4, 0x201b);

	mutex_unwock(&wt711->cawibwate_mutex);
	dev_dbg(dev, "%s cawibwation compwete, wet=%d\n", __func__, wet);
	wetuwn wet;
}

static unsigned int wt711_sdca_button_detect(stwuct wt711_sdca_pwiv *wt711)
{
	unsigned int btn_type = 0, offset, idx, vaw, ownew;
	int wet;
	unsigned chaw buf[3];

	/* get cuwwent UMP message ownew */
	wet = wegmap_wead(wt711->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_HID, WT711_SDCA_ENT_HID01, WT711_SDCA_CTW_HIDTX_CUWWENT_OWNEW, 0),
		&ownew);
	if (wet < 0)
		wetuwn 0;

	/* if ownew is device then thewe is no button event fwom device */
	if (ownew == 1)
		wetuwn 0;

	/* wead UMP message offset */
	wet = wegmap_wead(wt711->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_HID, WT711_SDCA_ENT_HID01, WT711_SDCA_CTW_HIDTX_MESSAGE_OFFSET, 0),
		&offset);
	if (wet < 0)
		goto _end_btn_det_;

	fow (idx = 0; idx < sizeof(buf); idx++) {
		wet = wegmap_wead(wt711->wegmap,
			WT711_BUF_ADDW_HID1 + offset + idx, &vaw);
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
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_HID, WT711_SDCA_ENT_HID01,
				WT711_SDCA_CTW_HIDTX_SET_OWNEW_TO_DEVICE, 0), 0x01);

	wetuwn btn_type;
}

static int wt711_sdca_headset_detect(stwuct wt711_sdca_pwiv *wt711)
{
	unsigned int det_mode;
	int wet;

	/* get detected_mode */
	wet = wegmap_wead(wt711->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_GE49, WT711_SDCA_CTW_DETECTED_MODE, 0),
		&det_mode);
	if (wet < 0)
		goto io_ewwow;

	switch (det_mode) {
	case 0x00:
		wt711->jack_type = 0;
		bweak;
	case 0x03:
		wt711->jack_type = SND_JACK_HEADPHONE;
		bweak;
	case 0x05:
		wt711->jack_type = SND_JACK_HEADSET;
		bweak;
	}

	/* wwite sewected_mode */
	if (det_mode) {
		wet = wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_GE49, WT711_SDCA_CTW_SEWECTED_MODE, 0),
			det_mode);
		if (wet < 0)
			goto io_ewwow;
	}

	dev_dbg(&wt711->swave->dev,
		"%s, detected_mode=0x%x\n", __func__, det_mode);

	wetuwn 0;

io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
	wetuwn wet;
}

static void wt711_sdca_jack_detect_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt711_sdca_pwiv *wt711 =
		containew_of(wowk, stwuct wt711_sdca_pwiv, jack_detect_wowk.wowk);
	int btn_type = 0, wet;

	if (!wt711->hs_jack)
		wetuwn;

	if (!snd_soc_cawd_is_instantiated(wt711->component->cawd))
		wetuwn;

	/* SDW_SCP_SDCA_INT_SDCA_0 is used fow jack detection */
	if (wt711->scp_sdca_stat1 & SDW_SCP_SDCA_INT_SDCA_0) {
		wet = wt711_sdca_headset_detect(wt711);
		if (wet < 0)
			wetuwn;
	}

	/* SDW_SCP_SDCA_INT_SDCA_8 is used fow button detection */
	if (wt711->scp_sdca_stat2 & SDW_SCP_SDCA_INT_SDCA_8)
		btn_type = wt711_sdca_button_detect(wt711);

	if (wt711->jack_type == 0)
		btn_type = 0;

	dev_dbg(&wt711->swave->dev,
		"in %s, jack_type=0x%x\n", __func__, wt711->jack_type);
	dev_dbg(&wt711->swave->dev,
		"in %s, btn_type=0x%x\n", __func__, btn_type);
	dev_dbg(&wt711->swave->dev,
		"in %s, scp_sdca_stat1=0x%x, scp_sdca_stat2=0x%x\n", __func__,
		wt711->scp_sdca_stat1, wt711->scp_sdca_stat2);

	snd_soc_jack_wepowt(wt711->hs_jack, wt711->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	if (btn_type) {
		/* button weweased */
		snd_soc_jack_wepowt(wt711->hs_jack, wt711->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt711->jack_btn_check_wowk, msecs_to_jiffies(200));
	}
}

static void wt711_sdca_btn_check_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wt711_sdca_pwiv *wt711 =
		containew_of(wowk, stwuct wt711_sdca_pwiv, jack_btn_check_wowk.wowk);
	int btn_type = 0, wet, idx;
	unsigned int det_mode, offset, vaw;
	unsigned chaw buf[3];

	wet = wegmap_wead(wt711->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_GE49, WT711_SDCA_CTW_DETECTED_MODE, 0),
		&det_mode);
	if (wet < 0)
		goto io_ewwow;

	/* pin attached */
	if (det_mode) {
		/* wead UMP message offset */
		wet = wegmap_wead(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_HID, WT711_SDCA_ENT_HID01, WT711_SDCA_CTW_HIDTX_MESSAGE_OFFSET, 0),
			&offset);
		if (wet < 0)
			goto io_ewwow;

		fow (idx = 0; idx < sizeof(buf); idx++) {
			wet = wegmap_wead(wt711->wegmap,
				WT711_BUF_ADDW_HID1 + offset + idx, &vaw);
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
	} ewse
		wt711->jack_type = 0;

	dev_dbg(&wt711->swave->dev, "%s, btn_type=0x%x\n",	__func__, btn_type);
	snd_soc_jack_wepowt(wt711->hs_jack, wt711->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	if (btn_type) {
		/* button weweased */
		snd_soc_jack_wepowt(wt711->hs_jack, wt711->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_dewayed_wowk(system_powew_efficient_wq,
			&wt711->jack_btn_check_wowk, msecs_to_jiffies(200));
	}

	wetuwn;

io_ewwow:
	pw_eww_watewimited("IO ewwow in %s, wet %d\n", __func__, wet);
}

static void wt711_sdca_jack_init(stwuct wt711_sdca_pwiv *wt711)
{
	mutex_wock(&wt711->cawibwate_mutex);

	if (wt711->hs_jack) {
		/* Enabwe HID1 event & set button WTC mode */
		wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
			WT711_PUSH_BTN_INT_CTW6, 0x80f0, 0x8000);
		wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
			WT711_PUSH_BTN_INT_CTW2, 0x11dd, 0x11dd);
		wt711_sdca_index_wwite(wt711, WT711_VENDOW_HDA_CTW,
			WT711_PUSH_BTN_INT_CTW7, 0xffff);
		wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
			WT711_PUSH_BTN_INT_CTW9, 0xf000, 0x0000);

		/* GE_mode_change_event_en & Hid1_push_button_event_en */
		wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
			WT711_GE_MODE_WEWATED_CTW, 0x0c00, 0x0c00);

		switch (wt711->jd_swc) {
		case WT711_JD1:
			/* defauwt settings was awweady fow JD1 */
			bweak;
		case WT711_JD2:
			wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
				WT711_JD_CTW1, WT711_JD2_DIGITAW_MODE_SEW,
				WT711_JD2_DIGITAW_MODE_SEW);
			wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
				WT711_JD_CTW2, WT711_JD2_2POWT_200K_DECODE_HP | WT711_HP_JD_SEW_JD2,
				WT711_JD2_2POWT_200K_DECODE_HP | WT711_HP_JD_SEW_JD2);
			wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
				WT711_CC_DET1,
				WT711_HP_JD_FINAW_WESUWT_CTW_JD12,
				WT711_HP_JD_FINAW_WESUWT_CTW_JD12);
			bweak;
		case WT711_JD2_100K:
			wt711_sdca_index_wwite(wt711, WT711_VENDOW_WEG,
				WT711_COMBO_JACK_AUTO_CTW3, 0xa47e);
			wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
				WT711_JD_CTW1, WT711_JD2_DIGITAW_MODE_SEW,
				WT711_JD2_DIGITAW_MODE_SEW);
			wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
				WT711_JD_CTW2, WT711_JD2_2POWT_200K_DECODE_HP |
				WT711_JD2_2POWT_100K_DECODE_MASK | WT711_HP_JD_SEW_JD2,
				WT711_JD2_2POWT_100K_DECODE_HP | WT711_HP_JD_SEW_JD2);
			wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
				WT711_CC_DET1,
				WT711_HP_JD_FINAW_WESUWT_CTW_JD12 | WT711_POW_CC1_AGPI,
				WT711_HP_JD_FINAW_WESUWT_CTW_JD12 | WT711_POW_CC1_AGPI_OFF);
			bweak;
		defauwt:
			dev_wawn(wt711->component->dev, "Wwong JD souwce\n");
			bweak;
		}

		/* set SCP_SDCA_IntMask1[0]=1 */
		sdw_wwite_no_pm(wt711->swave, SDW_SCP_SDCA_INTMASK1, SDW_SCP_SDCA_INTMASK_SDCA_0);
		/* set SCP_SDCA_IntMask2[0]=1 */
		sdw_wwite_no_pm(wt711->swave, SDW_SCP_SDCA_INTMASK2, SDW_SCP_SDCA_INTMASK_SDCA_8);
		dev_dbg(&wt711->swave->dev, "in %s enabwe\n", __func__);
	} ewse {
		/* disabwe HID 1/2 event */
		wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
			WT711_GE_MODE_WEWATED_CTW, 0x0c00, 0x0000);

		dev_dbg(&wt711->swave->dev, "in %s disabwe\n", __func__);
	}

	mutex_unwock(&wt711->cawibwate_mutex);
}

static int wt711_sdca_set_jack_detect(stwuct snd_soc_component *component,
	stwuct snd_soc_jack *hs_jack, void *data)
{
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt711->hs_jack = hs_jack;

	/* we can onwy wesume if the device was initiawized at weast once */
	if (!wt711->fiwst_hw_init)
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

	wt711_sdca_jack_init(wt711);

	pm_wuntime_mawk_wast_busy(component->dev);
	pm_wuntime_put_autosuspend(component->dev);

	wetuwn 0;
}

/* Fow SDCA contwow DAC/ADC Gain */
static int wt711_sdca_set_gain_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	unsigned int wead_w, wead_w, gain_w_vaw, gain_w_vaw;
	unsigned int i, adc_vow_fwag = 0, changed = 0;
	unsigned int wvawue, wvawue;

	if (stwstw(ucontwow->id.name, "FU1E Captuwe Vowume") ||
		stwstw(ucontwow->id.name, "FU0F Captuwe Vowume"))
		adc_vow_fwag = 1;

	wegmap_wead(wt711->mbq_wegmap, mc->weg, &wvawue);
	wegmap_wead(wt711->mbq_wegmap, mc->wweg, &wvawue);

	/* contwow vawue to 2's compwement vawue */
	/* W Channew */
	gain_w_vaw = ucontwow->vawue.integew.vawue[0];
	if (gain_w_vaw > mc->max)
		gain_w_vaw = mc->max;
	wead_w = gain_w_vaw;

	if (mc->shift == 8) /* boost gain */
		gain_w_vaw = (gain_w_vaw * 10) << mc->shift;
	ewse { /* ADC/DAC gain */
		if (adc_vow_fwag && gain_w_vaw > mc->shift)
			gain_w_vaw = (gain_w_vaw - mc->shift) * 75;
		ewse
			gain_w_vaw = (mc->shift - gain_w_vaw) * 75;
		gain_w_vaw <<= 8;
		gain_w_vaw /= 100;
		if (!(adc_vow_fwag && wead_w > mc->shift)) {
			gain_w_vaw = ~gain_w_vaw;
			gain_w_vaw += 1;
		}
		gain_w_vaw &= 0xffff;
	}

	/* W Channew */
	gain_w_vaw = ucontwow->vawue.integew.vawue[1];
	if (gain_w_vaw > mc->max)
		gain_w_vaw = mc->max;
	wead_w = gain_w_vaw;

	if (mc->shift == 8) /* boost gain */
		gain_w_vaw = (gain_w_vaw * 10) << mc->shift;
	ewse { /* ADC/DAC gain */
		if (adc_vow_fwag && gain_w_vaw > mc->shift)
			gain_w_vaw = (gain_w_vaw - mc->shift) * 75;
		ewse
			gain_w_vaw = (mc->shift - gain_w_vaw) * 75;
		gain_w_vaw <<= 8;
		gain_w_vaw /= 100;
		if (!(adc_vow_fwag && wead_w > mc->shift)) {
			gain_w_vaw = ~gain_w_vaw;
			gain_w_vaw += 1;
		}
		gain_w_vaw &= 0xffff;
	}

	if (wvawue != gain_w_vaw || wvawue != gain_w_vaw)
		changed = 1;
	ewse
		wetuwn 0;

	fow (i = 0; i < 3; i++) { /* wetwy 3 times at most */
		/* Wch*/
		wegmap_wwite(wt711->mbq_wegmap, mc->weg, gain_w_vaw);

		/* Wch */
		wegmap_wwite(wt711->mbq_wegmap, mc->wweg, gain_w_vaw);

		wegmap_wead(wt711->mbq_wegmap, mc->weg, &wead_w);
		wegmap_wead(wt711->mbq_wegmap, mc->wweg, &wead_w);
		if (wead_w == gain_w_vaw && wead_w == gain_w_vaw)
			bweak;
	}

	wetuwn i == 3 ? -EIO : changed;
}

static int wt711_sdca_set_gain_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	unsigned int wead_w, wead_w, ctw_w = 0, ctw_w = 0;
	unsigned int adc_vow_fwag = 0, neg_fwag = 0;

	if (stwstw(ucontwow->id.name, "FU1E Captuwe Vowume") ||
		stwstw(ucontwow->id.name, "FU0F Captuwe Vowume"))
		adc_vow_fwag = 1;

	wegmap_wead(wt711->mbq_wegmap, mc->weg, &wead_w);
	wegmap_wead(wt711->mbq_wegmap, mc->wweg, &wead_w);

	/* 2's compwement vawue to contwow vawue */
	if (mc->shift == 8) /* boost gain */
		ctw_w = (wead_w >> mc->shift) / 10;
	ewse { /* ADC/DAC gain */
		ctw_w = wead_w;
		if (wead_w & BIT(15)) {
			ctw_w = 0xffff & ~(wead_w - 1);
			neg_fwag = 1;
		}
		ctw_w *= 100;
		ctw_w >>= 8;
		if (adc_vow_fwag) {
			if (neg_fwag)
				ctw_w = mc->shift - (ctw_w / 75);
			ewse
				ctw_w = mc->shift + (ctw_w / 75);
		} ewse
			ctw_w = mc->max - (ctw_w / 75);
	}

	neg_fwag = 0;
	if (wead_w != wead_w) {
		if (mc->shift == 8) /* boost gain */
			ctw_w = (wead_w >> mc->shift) / 10;
		ewse { /* ADC/DAC gain */
			ctw_w = wead_w;
			if (wead_w & BIT(15)) {
				ctw_w = 0xffff & ~(wead_w - 1);
				neg_fwag = 1;
			}
			ctw_w *= 100;
			ctw_w >>= 8;
			if (adc_vow_fwag) {
				if (neg_fwag)
					ctw_w = mc->shift - (ctw_w / 75);
				ewse
					ctw_w = mc->shift + (ctw_w / 75);
			} ewse
				ctw_w = mc->max - (ctw_w / 75);
		}
	} ewse
		ctw_w = ctw_w;

	ucontwow->vawue.integew.vawue[0] = ctw_w;
	ucontwow->vawue.integew.vawue[1] = ctw_w;

	wetuwn 0;
}

static int wt711_sdca_set_fu0f_captuwe_ctw(stwuct wt711_sdca_pwiv *wt711)
{
	int eww;
	unsigned int ch_w, ch_w;

	ch_w = (wt711->fu0f_dapm_mute || wt711->fu0f_mixew_w_mute) ? 0x01 : 0x00;
	ch_w = (wt711->fu0f_dapm_mute || wt711->fu0f_mixew_w_mute) ? 0x01 : 0x00;

	eww = wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU0F,
			WT711_SDCA_CTW_FU_MUTE, CH_W), ch_w);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU0F,
			WT711_SDCA_CTW_FU_MUTE, CH_W), ch_w);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int wt711_sdca_set_fu1e_captuwe_ctw(stwuct wt711_sdca_pwiv *wt711)
{
	int eww;
	unsigned int ch_w, ch_w;

	ch_w = (wt711->fu1e_dapm_mute || wt711->fu1e_mixew_w_mute) ? 0x01 : 0x00;
	ch_w = (wt711->fu1e_dapm_mute || wt711->fu1e_mixew_w_mute) ? 0x01 : 0x00;

	eww = wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_USEW_FU1E,
			WT711_SDCA_CTW_FU_MUTE, CH_W), ch_w);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_USEW_FU1E,
			WT711_SDCA_CTW_FU_MUTE, CH_W), ch_w);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int wt711_sdca_fu1e_captuwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = !wt711->fu1e_mixew_w_mute;
	ucontwow->vawue.integew.vawue[1] = !wt711->fu1e_mixew_w_mute;
	wetuwn 0;
}

static int wt711_sdca_fu1e_captuwe_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	int eww, changed = 0;

	if (wt711->fu1e_mixew_w_mute != !ucontwow->vawue.integew.vawue[0] ||
		wt711->fu1e_mixew_w_mute != !ucontwow->vawue.integew.vawue[1])
		changed = 1;

	wt711->fu1e_mixew_w_mute = !ucontwow->vawue.integew.vawue[0];
	wt711->fu1e_mixew_w_mute = !ucontwow->vawue.integew.vawue[1];
	eww = wt711_sdca_set_fu1e_captuwe_ctw(wt711);
	if (eww < 0)
		wetuwn eww;

	wetuwn changed;
}

static int wt711_sdca_fu0f_captuwe_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = !wt711->fu0f_mixew_w_mute;
	ucontwow->vawue.integew.vawue[1] = !wt711->fu0f_mixew_w_mute;
	wetuwn 0;
}

static int wt711_sdca_fu0f_captuwe_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	int eww, changed = 0;

	if (wt711->fu0f_mixew_w_mute != !ucontwow->vawue.integew.vawue[0] ||
		wt711->fu0f_mixew_w_mute != !ucontwow->vawue.integew.vawue[1])
		changed = 1;

	wt711->fu0f_mixew_w_mute = !ucontwow->vawue.integew.vawue[0];
	wt711->fu0f_mixew_w_mute = !ucontwow->vawue.integew.vawue[1];
	eww = wt711_sdca_set_fu0f_captuwe_ctw(wt711);
	if (eww < 0)
		wetuwn eww;

	wetuwn changed;
}

static const DECWAWE_TWV_DB_SCAWE(out_vow_twv, -6525, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(in_vow_twv, -1725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, 0, 1000, 0);

static const stwuct snd_kcontwow_new wt711_sdca_snd_contwows[] = {
	SOC_DOUBWE_W_EXT_TWV("FU05 Pwayback Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU05, WT711_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU05, WT711_SDCA_CTW_FU_VOWUME, CH_W),
		0x57, 0x57, 0,
		wt711_sdca_set_gain_get, wt711_sdca_set_gain_put, out_vow_twv),
	SOC_DOUBWE_EXT("FU1E Captuwe Switch", SND_SOC_NOPM, 0, 1, 1, 0,
		wt711_sdca_fu1e_captuwe_get, wt711_sdca_fu1e_captuwe_put),
	SOC_DOUBWE_EXT("FU0F Captuwe Switch", SND_SOC_NOPM, 0, 1, 1, 0,
		wt711_sdca_fu0f_captuwe_get, wt711_sdca_fu0f_captuwe_put),
	SOC_DOUBWE_W_EXT_TWV("FU1E Captuwe Vowume",
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_USEW_FU1E, WT711_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_USEW_FU1E, WT711_SDCA_CTW_FU_VOWUME, CH_W),
		0x17, 0x3f, 0,
		wt711_sdca_set_gain_get, wt711_sdca_set_gain_put, in_vow_twv),
	SOC_DOUBWE_W_EXT_TWV("FU0F Captuwe Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU0F, WT711_SDCA_CTW_FU_VOWUME, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU0F, WT711_SDCA_CTW_FU_VOWUME, CH_W),
		0x17, 0x3f, 0,
		wt711_sdca_set_gain_get, wt711_sdca_set_gain_put, in_vow_twv),
	SOC_DOUBWE_W_EXT_TWV("FU44 Gain Vowume",
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_PWATFOWM_FU44, WT711_SDCA_CTW_FU_CH_GAIN, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_PWATFOWM_FU44, WT711_SDCA_CTW_FU_CH_GAIN, CH_W),
		8, 3, 0,
		wt711_sdca_set_gain_get, wt711_sdca_set_gain_put, mic_vow_twv),
	SOC_DOUBWE_W_EXT_TWV("FU15 Gain Vowume",
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_PWATFOWM_FU15, WT711_SDCA_CTW_FU_CH_GAIN, CH_W),
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_PWATFOWM_FU15, WT711_SDCA_CTW_FU_CH_GAIN, CH_W),
		8, 3, 0,
		wt711_sdca_set_gain_get, wt711_sdca_set_gain_put, mic_vow_twv),
};

static int wt711_sdca_mux_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0, mask_sft;

	if (stwstw(ucontwow->id.name, "ADC 22 Mux"))
		mask_sft = 10;
	ewse if (stwstw(ucontwow->id.name, "ADC 23 Mux"))
		mask_sft = 13;
	ewse
		wetuwn -EINVAW;

	wt711_sdca_index_wead(wt711, WT711_VENDOW_HDA_CTW,
		WT711_HDA_WEGACY_MUX_CTW1, &vaw);

	ucontwow->vawue.enumewated.item[0] = (vaw >> mask_sft) & 0x7;

	wetuwn 0;
}

static int wt711_sdca_mux_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_kcontwow_component(kcontwow);
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int vaw, vaw2 = 0, change, mask_sft;

	if (item[0] >= e->items)
		wetuwn -EINVAW;

	if (stwstw(ucontwow->id.name, "ADC 22 Mux"))
		mask_sft = 10;
	ewse if (stwstw(ucontwow->id.name, "ADC 23 Mux"))
		mask_sft = 13;
	ewse
		wetuwn -EINVAW;

	vaw = snd_soc_enum_item_to_vaw(e, item[0]) << e->shift_w;

	wt711_sdca_index_wead(wt711, WT711_VENDOW_HDA_CTW,
		WT711_HDA_WEGACY_MUX_CTW1, &vaw2);
	vaw2 = (vaw2 >> mask_sft) & 0x7;

	if (vaw == vaw2)
		change = 0;
	ewse
		change = 1;

	if (change)
		wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
			WT711_HDA_WEGACY_MUX_CTW1, 0x7 << mask_sft,
			vaw << mask_sft);

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
	wt711_adc22_enum, SND_SOC_NOPM, 0, adc_mux_text);

static SOC_ENUM_SINGWE_DECW(
	wt711_adc23_enum, SND_SOC_NOPM, 0, adc_mux_text);

static const stwuct snd_kcontwow_new wt711_sdca_adc22_mux =
	SOC_DAPM_ENUM_EXT("ADC 22 Mux", wt711_adc22_enum,
			wt711_sdca_mux_get, wt711_sdca_mux_put);

static const stwuct snd_kcontwow_new wt711_sdca_adc23_mux =
	SOC_DAPM_ENUM_EXT("ADC 23 Mux", wt711_adc23_enum,
			wt711_sdca_mux_get, wt711_sdca_mux_put);

static int wt711_sdca_fu05_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	unsigned chaw unmute = 0x0, mute = 0x1;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU05,
				WT711_SDCA_CTW_FU_MUTE, CH_W),
				unmute);
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU05,
				WT711_SDCA_CTW_FU_MUTE, CH_W),
				unmute);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU05,
				WT711_SDCA_CTW_FU_MUTE, CH_W),
				mute);
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_USEW_FU05,
				WT711_SDCA_CTW_FU_MUTE, CH_W),
				mute);
		bweak;
	}
	wetuwn 0;
}

static int wt711_sdca_fu0f_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wt711->fu0f_dapm_mute = fawse;
		wt711_sdca_set_fu0f_captuwe_ctw(wt711);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wt711->fu0f_dapm_mute = twue;
		wt711_sdca_set_fu0f_captuwe_ctw(wt711);
		bweak;
	}
	wetuwn 0;
}

static int wt711_sdca_fu1e_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wt711->fu1e_dapm_mute = fawse;
		wt711_sdca_set_fu1e_captuwe_ctw(wt711);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wt711->fu1e_dapm_mute = twue;
		wt711_sdca_set_fu1e_captuwe_ctw(wt711);
		bweak;
	}
	wetuwn 0;
}

static int wt711_sdca_pde28_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_PDE28,
				WT711_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_PDE28,
				WT711_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;
	}
	wetuwn 0;
}

static int wt711_sdca_pde29_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_PDE29,
				WT711_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_PDE29,
				WT711_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;
	}
	wetuwn 0;
}

static int wt711_sdca_pde2a_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_PDE2A,
				WT711_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_PDE2A,
				WT711_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;
	}
	wetuwn 0;
}

static int wt711_sdca_wine1_powew_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	static unsigned int sew_mode = 0xffff;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wead(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_GE49,
				WT711_SDCA_CTW_SEWECTED_MODE, 0),
				&sew_mode);
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_WINE1,
				WT711_SDCA_CTW_VENDOW_DEF, 0),
				0x1);
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_GE49,
				WT711_SDCA_CTW_SEWECTED_MODE, 0),
				0x7);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_WINE1,
				WT711_SDCA_CTW_VENDOW_DEF, 0),
				0x0);
		if (sew_mode != 0xffff)
			wegmap_wwite(wt711->wegmap,
				SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_GE49,
				WT711_SDCA_CTW_SEWECTED_MODE, 0),
				sew_mode);
		bweak;
	}

	wetuwn 0;
}

static int wt711_sdca_wine2_powew_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	unsigned chaw ps0 = 0x0, ps3 = 0x3;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_PDEWINE2,
				WT711_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps0);
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_WINE2,
				WT711_SDCA_CTW_VENDOW_DEF, 0),
				0x1);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_WINE2,
				WT711_SDCA_CTW_VENDOW_DEF, 0),
				0x0);
		wegmap_wwite(wt711->wegmap,
			SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_PDEWINE2,
				WT711_SDCA_CTW_WEQ_POWEW_STATE, 0),
				ps3);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget wt711_sdca_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("WINE1"),
	SND_SOC_DAPM_INPUT("WINE2"),

	SND_SOC_DAPM_PGA_E("WINE1 Powew", SND_SOC_NOPM,
		0, 0, NUWW, 0, wt711_sdca_wine1_powew_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_PGA_E("WINE2 Powew", SND_SOC_NOPM,
		0, 0, NUWW, 0, wt711_sdca_wine2_powew_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_SUPPWY("PDE 28", SND_SOC_NOPM, 0, 0,
		wt711_sdca_pde28_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("PDE 29", SND_SOC_NOPM, 0, 0,
		wt711_sdca_pde29_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_SUPPWY("PDE 2A", SND_SOC_NOPM, 0, 0,
		wt711_sdca_pde2a_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_DAC_E("FU 05", NUWW, SND_SOC_NOPM, 0, 0,
		wt711_sdca_fu05_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_ADC_E("FU 0F", NUWW, SND_SOC_NOPM, 0, 0,
		wt711_sdca_fu0f_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_ADC_E("FU 1E", NUWW, SND_SOC_NOPM, 0, 0,
		wt711_sdca_fu1e_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_MUX("ADC 22 Mux", SND_SOC_NOPM, 0, 0,
		&wt711_sdca_adc22_mux),
	SND_SOC_DAPM_MUX("ADC 23 Mux", SND_SOC_NOPM, 0, 0,
		&wt711_sdca_adc23_mux),

	SND_SOC_DAPM_AIF_IN("DP3WX", "DP3 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP2TX", "DP2 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP4TX", "DP4 Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute wt711_sdca_audio_map[] = {
	{"FU 05", NUWW, "DP3WX"},
	{"DP2TX", NUWW, "FU 0F"},
	{"DP4TX", NUWW, "FU 1E"},

	{"WINE1 Powew", NUWW, "WINE1"},
	{"WINE2 Powew", NUWW, "WINE2"},
	{"HP", NUWW, "PDE 28"},
	{"FU 0F", NUWW, "PDE 29"},
	{"FU 1E", NUWW, "PDE 2A"},

	{"FU 0F", NUWW, "ADC 22 Mux"},
	{"FU 1E", NUWW, "ADC 23 Mux"},
	{"ADC 22 Mux", "DMIC", "DMIC1"},
	{"ADC 22 Mux", "WINE1", "WINE1 Powew"},
	{"ADC 22 Mux", "WINE2", "WINE2 Powew"},
	{"ADC 22 Mux", "MIC2", "MIC2"},
	{"ADC 23 Mux", "DMIC", "DMIC2"},
	{"ADC 23 Mux", "WINE1", "WINE1 Powew"},
	{"ADC 23 Mux", "WINE2", "WINE2 Powew"},
	{"ADC 23 Mux", "MIC2", "MIC2"},

	{"HP", NUWW, "FU 05"},
};

static int wt711_sdca_pawse_dt(stwuct wt711_sdca_pwiv *wt711, stwuct device *dev)
{
	device_pwopewty_wead_u32(dev, "weawtek,jd-swc", &wt711->jd_swc);

	wetuwn 0;
}

static int wt711_sdca_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	int wet;

	wt711_sdca_pawse_dt(wt711, &wt711->swave->dev);
	wt711->component = component;

	if (!wt711->fiwst_hw_init)
		wetuwn 0;

	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_sdca_dev_wt711 = {
	.pwobe = wt711_sdca_pwobe,
	.contwows = wt711_sdca_snd_contwows,
	.num_contwows = AWWAY_SIZE(wt711_sdca_snd_contwows),
	.dapm_widgets = wt711_sdca_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt711_sdca_dapm_widgets),
	.dapm_woutes = wt711_sdca_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(wt711_sdca_audio_map),
	.set_jack = wt711_sdca_set_jack_detect,
	.endianness = 1,
};

static int wt711_sdca_set_sdw_stweam(stwuct snd_soc_dai *dai, void *sdw_stweam,
				int diwection)
{
	snd_soc_dai_dma_data_set(dai, diwection, sdw_stweam);

	wetuwn 0;
}

static void wt711_sdca_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	snd_soc_dai_set_dma_data(dai, substweam, NUWW);
}

static int wt711_sdca_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_config stweam_config = {0};
	stwuct sdw_powt_config powt_config = {0};
	stwuct sdw_stweam_wuntime *sdw_stweam;
	int wetvaw;
	unsigned int sampwing_wate;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);
	sdw_stweam = snd_soc_dai_get_dma_data(dai, substweam);

	if (!sdw_stweam)
		wetuwn -EINVAW;

	if (!wt711->swave)
		wetuwn -EINVAW;

	/* SoundWiwe specific configuwation */
	snd_sdw_pawams_to_config(substweam, pawams, &stweam_config, &powt_config);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		powt_config.num = 3;
	} ewse {
		if (dai->id == WT711_AIF1)
			powt_config.num = 2;
		ewse if (dai->id == WT711_AIF2)
			powt_config.num = 4;
		ewse
			wetuwn -EINVAW;
	}

	wetvaw = sdw_stweam_add_swave(wt711->swave, &stweam_config,
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
		sampwing_wate = WT711_SDCA_WATE_44100HZ;
		bweak;
	case 48000:
		sampwing_wate = WT711_SDCA_WATE_48000HZ;
		bweak;
	case 96000:
		sampwing_wate = WT711_SDCA_WATE_96000HZ;
		bweak;
	case 192000:
		sampwing_wate = WT711_SDCA_WATE_192000HZ;
		bweak;
	defauwt:
		dev_eww(component->dev, "Wate %d is not suppowted\n",
			pawams_wate(pawams));
		wetuwn -EINVAW;
	}

	/* set sampwing fwequency */
	wegmap_wwite(wt711->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_CS01, WT711_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0),
		sampwing_wate);
	wegmap_wwite(wt711->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_CS11, WT711_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0),
		sampwing_wate);
	wegmap_wwite(wt711->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_MIC_AWWAY, WT711_SDCA_ENT_CS1F, WT711_SDCA_CTW_SAMPWE_FWEQ_INDEX, 0),
		sampwing_wate);

	wetuwn 0;
}

static int wt711_sdca_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt711_sdca_pwiv *wt711 = snd_soc_component_get_dwvdata(component);
	stwuct sdw_stweam_wuntime *sdw_stweam =
		snd_soc_dai_get_dma_data(dai, substweam);

	if (!wt711->swave)
		wetuwn -EINVAW;

	sdw_stweam_wemove_swave(wt711->swave, sdw_stweam);
	wetuwn 0;
}

#define WT711_STEWEO_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 | \
			SNDWV_PCM_WATE_192000)
#define WT711_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops wt711_sdca_ops = {
	.hw_pawams	= wt711_sdca_pcm_hw_pawams,
	.hw_fwee	= wt711_sdca_pcm_hw_fwee,
	.set_stweam	= wt711_sdca_set_sdw_stweam,
	.shutdown	= wt711_sdca_shutdown,
};

static stwuct snd_soc_dai_dwivew wt711_sdca_dai[] = {
	{
		.name = "wt711-sdca-aif1",
		.id = WT711_AIF1,
		.pwayback = {
			.stweam_name = "DP3 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT711_STEWEO_WATES,
			.fowmats = WT711_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "DP2 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT711_STEWEO_WATES,
			.fowmats = WT711_FOWMATS,
		},
		.ops = &wt711_sdca_ops,
	},
	{
		.name = "wt711-sdca-aif2",
		.id = WT711_AIF2,
		.captuwe = {
			.stweam_name = "DP4 Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WT711_STEWEO_WATES,
			.fowmats = WT711_FOWMATS,
		},
		.ops = &wt711_sdca_ops,
	}
};

int wt711_sdca_init(stwuct device *dev, stwuct wegmap *wegmap,
			stwuct wegmap *mbq_wegmap, stwuct sdw_swave *swave)
{
	stwuct wt711_sdca_pwiv *wt711;
	int wet;

	wt711 = devm_kzawwoc(dev, sizeof(*wt711), GFP_KEWNEW);
	if (!wt711)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, wt711);
	wt711->swave = swave;
	wt711->wegmap = wegmap;
	wt711->mbq_wegmap = mbq_wegmap;

	wegcache_cache_onwy(wt711->wegmap, twue);
	wegcache_cache_onwy(wt711->mbq_wegmap, twue);

	mutex_init(&wt711->cawibwate_mutex);
	mutex_init(&wt711->disabwe_iwq_wock);

	INIT_DEWAYED_WOWK(&wt711->jack_detect_wowk, wt711_sdca_jack_detect_handwew);
	INIT_DEWAYED_WOWK(&wt711->jack_btn_check_wowk, wt711_sdca_btn_check_handwew);

	/*
	 * Mawk hw_init to fawse
	 * HW init wiww be pewfowmed when device wepowts pwesent
	 */
	wt711->hw_init = fawse;
	wt711->fiwst_hw_init = fawse;
	wt711->fu0f_dapm_mute = twue;
	wt711->fu1e_dapm_mute = twue;
	wt711->fu0f_mixew_w_mute = wt711->fu0f_mixew_w_mute = twue;
	wt711->fu1e_mixew_w_mute = wt711->fu1e_mixew_w_mute = twue;

	/* JD souwce uses JD2 in defauwt */
	wt711->jd_swc = WT711_JD2;

	wet =  devm_snd_soc_wegistew_component(dev,
			&soc_sdca_dev_wt711,
			wt711_sdca_dai,
			AWWAY_SIZE(wt711_sdca_dai));

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

static void wt711_sdca_vd0_io_init(stwuct wt711_sdca_pwiv *wt711)
{
	wt711_sdca_index_wwite(wt711, WT711_VENDOW_WEG,
		WT711_GPIO_TEST_MODE_CTW2, 0x0e00);
	wt711_sdca_index_wwite(wt711, WT711_VENDOW_HDA_CTW,
		WT711_HDA_WEGACY_GPIO_CTW, 0x0008);

	wegmap_wwite(wt711->wegmap, 0x2f5a, 0x01);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_WEG,
		WT711_ADC27_VOW_SET, 0x8728);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_WEG,
		WT711_COMBO_JACK_AUTO_CTW3, 0xa472);

	wegmap_wwite(wt711->wegmap, 0x2f50, 0x02);

	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_ANAWOG_CTW,
		WT711_MISC_POWEW_CTW4, 0x6000, 0x6000);

	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
		WT711_COMBO_JACK_AUTO_CTW3, 0x000c, 0x000c);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_HDA_CTW,
		WT711_HDA_WEGACY_CONFIG_CTW, 0x0000);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_VAD,
		WT711_VAD_SWAM_CTW1, 0x0050);
}

static void wt711_sdca_vd1_io_init(stwuct wt711_sdca_pwiv *wt711)
{
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
		WT711_HDA_WEGACY_UNSOWICITED_CTW, 0x0300, 0x0000);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_WEG,
		WT711_COMBO_JACK_AUTO_CTW3, 0xa43e);

	wegmap_wwite(wt711->wegmap, 0x2f5a, 0x05);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_WEG,
		WT711_JD_CTWW6, 0x0500);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_WEG,
		WT711_DMIC_CTW1, 0x6173);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_HDA_CTW,
		WT711_HDA_WEGACY_CONFIG_CTW, 0x0000);

	wt711_sdca_index_wwite(wt711, WT711_VENDOW_VAD,
		WT711_VAD_SWAM_CTW1, 0x0050);
}

int wt711_sdca_io_init(stwuct device *dev, stwuct sdw_swave *swave)
{
	stwuct wt711_sdca_pwiv *wt711 = dev_get_dwvdata(dev);
	int wet = 0;
	unsigned int vaw;

	wt711->disabwe_iwq = fawse;

	if (wt711->hw_init)
		wetuwn 0;

	wegcache_cache_onwy(wt711->wegmap, fawse);
	wegcache_cache_onwy(wt711->mbq_wegmap, fawse);

	if (wt711->fiwst_hw_init) {
		wegcache_cache_bypass(wt711->wegmap, twue);
		wegcache_cache_bypass(wt711->mbq_wegmap, twue);
	} ewse {
		/*
		 * PM wuntime status is mawked as 'active' onwy when a Swave wepowts as Attached
		 */

		/* update count of pawent 'active' chiwdwen */
		pm_wuntime_set_active(&swave->dev);
	}

	pm_wuntime_get_nowesume(&swave->dev);

	wt711_sdca_weset(wt711);

	wt711_sdca_index_wead(wt711, WT711_VENDOW_WEG, WT711_JD_PWODUCT_NUM, &vaw);
	wt711->hw_vew = vaw & 0xf;

	if (wt711->hw_vew == WT711_VEW_VD0)
		wt711_sdca_vd0_io_init(wt711);
	ewse
		wt711_sdca_vd1_io_init(wt711);

	/* DP4 mux sewect fwom 08_fiwtew_Out_pwi */
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_WEG,
		WT711_FIWTEW_SWC_SEW, 0x1800, 0x0800);

	/* ge_excwusive_inbox_en disabwe */
	wt711_sdca_index_update_bits(wt711, WT711_VENDOW_HDA_CTW,
		WT711_PUSH_BTN_INT_CTW0, 0x20, 0x00);

	/* cawibwation */
	wet = wt711_sdca_cawibwation(wt711);
	if (wet < 0)
		dev_eww(dev, "%s, cawibwation faiwed!\n", __func__);

	/* HP output enabwe */
	wegmap_wwite(wt711->wegmap,
		SDW_SDCA_CTW(FUNC_NUM_JACK_CODEC, WT711_SDCA_ENT_OT1, WT711_SDCA_CTW_VENDOW_DEF, 0), 0x4);

	/*
	 * if set_jack cawwback occuwwed eawwy than io_init,
	 * we set up the jack detection function now
	 */
	if (wt711->hs_jack)
		wt711_sdca_jack_init(wt711);

	if (wt711->fiwst_hw_init) {
		wegcache_cache_bypass(wt711->wegmap, fawse);
		wegcache_mawk_diwty(wt711->wegmap);
		wegcache_cache_bypass(wt711->mbq_wegmap, fawse);
		wegcache_mawk_diwty(wt711->mbq_wegmap);
	} ewse
		wt711->fiwst_hw_init = twue;

	/* Mawk Swave initiawization compwete */
	wt711->hw_init = twue;

	pm_wuntime_mawk_wast_busy(&swave->dev);
	pm_wuntime_put_autosuspend(&swave->dev);

	dev_dbg(&swave->dev, "%s hw_init compwete\n", __func__);
	wetuwn 0;
}

MODUWE_DESCWIPTION("ASoC WT711 SDCA SDW dwivew");
MODUWE_AUTHOW("Shuming Fan <shumingf@weawtek.com>");
MODUWE_WICENSE("GPW");
