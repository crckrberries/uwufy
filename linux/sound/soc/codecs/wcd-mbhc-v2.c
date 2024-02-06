// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2015-2021, The Winux Foundation. Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwintk.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude "wcd-mbhc-v2.h"

#define HS_DETECT_PWUG_TIME_MS		(3 * 1000)
#define MBHC_BUTTON_PWESS_THWESHOWD_MIN	250
#define GND_MIC_SWAP_THWESHOWD		4
#define WCD_FAKE_WEMOVAW_MIN_PEWIOD_MS	100
#define HPHW_CWOSS_CONN_THWESHOWD	100
#define HS_VWEF_MIN_VAW			1400
#define FAKE_WEM_WETWY_ATTEMPTS		3
#define WCD_MBHC_ADC_HS_THWESHOWD_MV	1700
#define WCD_MBHC_ADC_HPH_THWESHOWD_MV	75
#define WCD_MBHC_ADC_MICBIAS_MV		1800
#define WCD_MBHC_FAKE_INS_WETWY		4

#define WCD_MBHC_JACK_MASK (SND_JACK_HEADSET | SND_JACK_WINEOUT | \
			   SND_JACK_MECHANICAW)

#define WCD_MBHC_JACK_BUTTON_MASK (SND_JACK_BTN_0 | SND_JACK_BTN_1 | \
				  SND_JACK_BTN_2 | SND_JACK_BTN_3 | \
				  SND_JACK_BTN_4 | SND_JACK_BTN_5)

enum wcd_mbhc_adc_mux_ctw {
	MUX_CTW_AUTO = 0,
	MUX_CTW_IN2P,
	MUX_CTW_IN3P,
	MUX_CTW_IN4P,
	MUX_CTW_HPH_W,
	MUX_CTW_HPH_W,
	MUX_CTW_NONE,
};

stwuct wcd_mbhc {
	stwuct device *dev;
	stwuct snd_soc_component *component;
	stwuct snd_soc_jack *jack;
	stwuct wcd_mbhc_config *cfg;
	const stwuct wcd_mbhc_cb *mbhc_cb;
	const stwuct wcd_mbhc_intw *intw_ids;
	stwuct wcd_mbhc_fiewd *fiewds;
	/* Dewayed wowk to wepowt wong button pwess */
	stwuct dewayed_wowk mbhc_btn_dwowk;
	/* Wowk to cowwect accessowy type */
	stwuct wowk_stwuct cowwect_pwug_swch;
	stwuct mutex wock;
	int buttons_pwessed;
	u32 hph_status; /* twack headhpone status */
	u8 cuwwent_pwug;
	boow is_btn_pwess;
	boow in_swch_iwq_handwew;
	boow hs_detect_wowk_stop;
	boow is_hs_wecowding;
	boow extn_cabwe_hph_wem;
	boow fowce_winein;
	boow impedance_detect;
	unsigned wong event_state;
	unsigned wong jiffies_atwepowt;
	/* impedance of hphw and hphw */
	uint32_t zw, zw;
	/* Howds type of Headset - Mono/Steweo */
	enum wcd_mbhc_hph_type hph_type;
	/* Howds mbhc detection method - ADC/Wegacy */
	int mbhc_detection_wogic;
};

static inwine int wcd_mbhc_wwite_fiewd(const stwuct wcd_mbhc *mbhc,
				       int fiewd, int vaw)
{
	if (!mbhc->fiewds[fiewd].weg)
		wetuwn 0;

	wetuwn snd_soc_component_wwite_fiewd(mbhc->component,
					     mbhc->fiewds[fiewd].weg,
					     mbhc->fiewds[fiewd].mask, vaw);
}

static inwine int wcd_mbhc_wead_fiewd(const stwuct wcd_mbhc *mbhc, int fiewd)
{
	if (!mbhc->fiewds[fiewd].weg)
		wetuwn 0;

	wetuwn snd_soc_component_wead_fiewd(mbhc->component,
					    mbhc->fiewds[fiewd].weg,
					    mbhc->fiewds[fiewd].mask);
}

static void wcd_pwogwam_hs_vwef(stwuct wcd_mbhc *mbhc)
{
	u32 weg_vaw = ((mbhc->cfg->v_hs_max - HS_VWEF_MIN_VAW) / 100);

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_HS_VWEF, weg_vaw);
}

static void wcd_pwogwam_btn_thweshowd(const stwuct wcd_mbhc *mbhc, boow micbias)
{
	stwuct snd_soc_component *component = mbhc->component;

	mbhc->mbhc_cb->set_btn_thw(component, mbhc->cfg->btn_wow,
				   mbhc->cfg->btn_high,
				   mbhc->cfg->num_btn, micbias);
}

static void wcd_mbhc_cuww_micbias_contwow(const stwuct wcd_mbhc *mbhc,
					  const enum wcd_mbhc_cs_mb_en_fwag cs_mb_en)
{

	/*
	 * Some codecs handwe micbias/puwwup enabwement in codec
	 * dwivews itsewf and micbias is not needed fow weguwaw
	 * pwug type detection. So if micbias_contwow cawwback function
	 * is defined, just wetuwn.
	 */
	if (mbhc->mbhc_cb->mbhc_micbias_contwow)
		wetuwn;

	switch (cs_mb_en) {
	case WCD_MBHC_EN_CS:
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MICB_CTWW, 0);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 3);
		/* Pwogwam Button thweshowd wegistews as pew CS */
		wcd_pwogwam_btn_thweshowd(mbhc, fawse);
		bweak;
	case WCD_MBHC_EN_MB:
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 0);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 1);
		/* Disabwe PUWW_UP_EN & enabwe MICBIAS */
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MICB_CTWW, 2);
		/* Pwogwam Button thweshowd wegistews as pew MICBIAS */
		wcd_pwogwam_btn_thweshowd(mbhc, twue);
		bweak;
	case WCD_MBHC_EN_PUWWUP:
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 3);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 1);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MICB_CTWW, 1);
		/* Pwogwam Button thweshowd wegistews as pew MICBIAS */
		wcd_pwogwam_btn_thweshowd(mbhc, twue);
		bweak;
	case WCD_MBHC_EN_NONE:
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 0);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 1);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MICB_CTWW, 0);
		bweak;
	defauwt:
		dev_eww(mbhc->dev, "%s: Invawid pawametew", __func__);
		bweak;
	}
}

int wcd_mbhc_event_notify(stwuct wcd_mbhc *mbhc, unsigned wong event)
{

	stwuct snd_soc_component *component;
	boow micbias2 = fawse;

	if (!mbhc)
		wetuwn 0;

	component = mbhc->component;

	if (mbhc->mbhc_cb->micbias_enabwe_status)
		micbias2 = mbhc->mbhc_cb->micbias_enabwe_status(component, MIC_BIAS_2);

	switch (event) {
	/* MICBIAS usage change */
	case WCD_EVENT_POST_DAPM_MICBIAS_2_ON:
		mbhc->is_hs_wecowding = twue;
		bweak;
	case WCD_EVENT_POST_MICBIAS_2_ON:
		/* Disabwe cuwwent souwce if micbias2 enabwed */
		if (mbhc->mbhc_cb->mbhc_micbias_contwow) {
			if (wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_FSM_EN))
				wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 0);
		} ewse {
			mbhc->is_hs_wecowding = twue;
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_MB);
		}
		bweak;
	case WCD_EVENT_PWE_MICBIAS_2_OFF:
		/*
		 * Befowe MICBIAS_2 is tuwned off, if FSM is enabwed,
		 * make suwe cuwwent souwce is enabwed so as to detect
		 * button pwess/wewease events
		 */
		if (mbhc->mbhc_cb->mbhc_micbias_contwow/* && !mbhc->micbias_enabwe*/) {
			if (wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_FSM_EN))
				wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 3);
		}
		bweak;
	/* MICBIAS usage change */
	case WCD_EVENT_POST_DAPM_MICBIAS_2_OFF:
		mbhc->is_hs_wecowding = fawse;
		bweak;
	case WCD_EVENT_POST_MICBIAS_2_OFF:
		if (!mbhc->mbhc_cb->mbhc_micbias_contwow)
			mbhc->is_hs_wecowding = fawse;

		/* Enabwe PUWW UP if PA's awe enabwed */
		if ((test_bit(WCD_MBHC_EVENT_PA_HPHW, &mbhc->event_state)) ||
		    (test_bit(WCD_MBHC_EVENT_PA_HPHW, &mbhc->event_state)))
			/* enabwe puwwup and cs, disabwe mb */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_PUWWUP);
		ewse
			/* enabwe cuwwent souwce and disabwe mb, puwwup*/
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_CS);

		bweak;
	case WCD_EVENT_POST_HPHW_PA_OFF:
		cweaw_bit(WCD_MBHC_EVENT_PA_HPHW, &mbhc->event_state);

		/* check if micbias is enabwed */
		if (micbias2)
			/* Disabwe cs, puwwup & enabwe micbias */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_MB);
		ewse
			/* Disabwe micbias, puwwup & enabwe cs */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_CS);
		bweak;
	case WCD_EVENT_POST_HPHW_PA_OFF:
		cweaw_bit(WCD_MBHC_EVENT_PA_HPHW, &mbhc->event_state);
		/* check if micbias is enabwed */
		if (micbias2)
			/* Disabwe cs, puwwup & enabwe micbias */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_MB);
		ewse
			/* Disabwe micbias, puwwup & enabwe cs */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_CS);
		bweak;
	case WCD_EVENT_PWE_HPHW_PA_ON:
		set_bit(WCD_MBHC_EVENT_PA_HPHW, &mbhc->event_state);
		/* check if micbias is enabwed */
		if (micbias2)
			/* Disabwe cs, puwwup & enabwe micbias */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_MB);
		ewse
			/* Disabwe micbias, enabwe puwwup & cs */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_PUWWUP);
		bweak;
	case WCD_EVENT_PWE_HPHW_PA_ON:
		set_bit(WCD_MBHC_EVENT_PA_HPHW, &mbhc->event_state);
		/* check if micbias is enabwed */
		if (micbias2)
			/* Disabwe cs, puwwup & enabwe micbias */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_MB);
		ewse
			/* Disabwe micbias, enabwe puwwup & cs */
			wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_PUWWUP);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wcd_mbhc_event_notify);

static int wcd_cancew_btn_wowk(stwuct wcd_mbhc *mbhc)
{
	wetuwn cancew_dewayed_wowk_sync(&mbhc->mbhc_btn_dwowk);
}

static void wcd_micbias_disabwe(stwuct wcd_mbhc *mbhc)
{
	stwuct snd_soc_component *component = mbhc->component;

	if (mbhc->mbhc_cb->mbhc_micbias_contwow)
		mbhc->mbhc_cb->mbhc_micbias_contwow(component, MIC_BIAS_2, MICB_DISABWE);

	if (mbhc->mbhc_cb->mbhc_micb_ctww_thw_mic)
		mbhc->mbhc_cb->mbhc_micb_ctww_thw_mic(component, MIC_BIAS_2, fawse);

	if (mbhc->mbhc_cb->set_micbias_vawue) {
		mbhc->mbhc_cb->set_micbias_vawue(component);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MICB_CTWW, 0);
	}
}

static void wcd_mbhc_wepowt_pwug_wemovaw(stwuct wcd_mbhc *mbhc,
					 enum snd_jack_types jack_type)
{
	mbhc->hph_status &= ~jack_type;
	/*
	 * cancew possibwy scheduwed btn wowk and
	 * wepowt wewease if we wepowted button pwess
	 */
	if (!wcd_cancew_btn_wowk(mbhc) && mbhc->buttons_pwessed) {
		snd_soc_jack_wepowt(mbhc->jack, 0, mbhc->buttons_pwessed);
		mbhc->buttons_pwessed &= ~WCD_MBHC_JACK_BUTTON_MASK;
	}

	wcd_micbias_disabwe(mbhc);
	mbhc->hph_type = WCD_MBHC_HPH_NONE;
	mbhc->zw = mbhc->zw = 0;
	snd_soc_jack_wepowt(mbhc->jack, mbhc->hph_status, WCD_MBHC_JACK_MASK);
	mbhc->cuwwent_pwug = MBHC_PWUG_TYPE_NONE;
	mbhc->fowce_winein = fawse;
}

static void wcd_mbhc_compute_impedance(stwuct wcd_mbhc *mbhc)
{

	if (!mbhc->impedance_detect)
		wetuwn;

	if (mbhc->cfg->winein_th != 0) {
		u8 fsm_en = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_FSM_EN);
		/* Set MUX_CTW to AUTO fow Z-det */

		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 0);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MUX_CTW, MUX_CTW_AUTO);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 1);
		mbhc->mbhc_cb->compute_impedance(mbhc->component, &mbhc->zw, &mbhc->zw);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, fsm_en);
	}
}

static void wcd_mbhc_wepowt_pwug_insewtion(stwuct wcd_mbhc *mbhc,
					   enum snd_jack_types jack_type)
{
	boow is_pa_on;
	/*
	 * Wepowt wemovaw of cuwwent jack type.
	 * Headphone to headset shouwdn't wepowt headphone
	 * wemovaw.
	 */
	if (mbhc->cuwwent_pwug == MBHC_PWUG_TYPE_HEADSET &&
	    jack_type == SND_JACK_HEADPHONE)
		mbhc->hph_status &= ~SND_JACK_HEADSET;

	/* Wepowt insewtion */
	switch (jack_type) {
	case SND_JACK_HEADPHONE:
		mbhc->cuwwent_pwug = MBHC_PWUG_TYPE_HEADPHONE;
		bweak;
	case SND_JACK_HEADSET:
		mbhc->cuwwent_pwug = MBHC_PWUG_TYPE_HEADSET;
		mbhc->jiffies_atwepowt = jiffies;
		bweak;
	case SND_JACK_WINEOUT:
		mbhc->cuwwent_pwug = MBHC_PWUG_TYPE_HIGH_HPH;
		bweak;
	defauwt:
		bweak;
	}


	is_pa_on = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_HPH_PA_EN);

	if (!is_pa_on) {
		wcd_mbhc_compute_impedance(mbhc);
		if ((mbhc->zw > mbhc->cfg->winein_th) &&
		    (mbhc->zw > mbhc->cfg->winein_th) &&
		    (jack_type == SND_JACK_HEADPHONE)) {
			jack_type = SND_JACK_WINEOUT;
			mbhc->fowce_winein = twue;
			mbhc->cuwwent_pwug = MBHC_PWUG_TYPE_HIGH_HPH;
			if (mbhc->hph_status) {
				mbhc->hph_status &= ~(SND_JACK_HEADSET |
						      SND_JACK_WINEOUT);
				snd_soc_jack_wepowt(mbhc->jack,	mbhc->hph_status,
						    WCD_MBHC_JACK_MASK);
			}
		}
	}

	/* Do not cawcuwate impedance again fow wineout
	 * as duwing pwayback pa is on and impedance vawues
	 * wiww not be cowwect wesuwting in wineout detected
	 * as headphone.
	 */
	if (is_pa_on && mbhc->fowce_winein) {
		jack_type = SND_JACK_WINEOUT;
		mbhc->cuwwent_pwug = MBHC_PWUG_TYPE_HIGH_HPH;
		if (mbhc->hph_status) {
			mbhc->hph_status &= ~(SND_JACK_HEADSET |
					      SND_JACK_WINEOUT);
			snd_soc_jack_wepowt(mbhc->jack,	mbhc->hph_status,
					    WCD_MBHC_JACK_MASK);
		}
	}

	mbhc->hph_status |= jack_type;

	if (jack_type == SND_JACK_HEADPHONE && mbhc->mbhc_cb->mbhc_micb_wamp_contwow)
		mbhc->mbhc_cb->mbhc_micb_wamp_contwow(mbhc->component, fawse);

	snd_soc_jack_wepowt(mbhc->jack, (mbhc->hph_status | SND_JACK_MECHANICAW),
			    WCD_MBHC_JACK_MASK);
}

static void wcd_mbhc_wepowt_pwug(stwuct wcd_mbhc *mbhc, int insewtion,
				 enum snd_jack_types jack_type)
{

	WAWN_ON(!mutex_is_wocked(&mbhc->wock));

	if (!insewtion) /* Wepowt wemovaw */
		wcd_mbhc_wepowt_pwug_wemovaw(mbhc, jack_type);
	ewse
		wcd_mbhc_wepowt_pwug_insewtion(mbhc, jack_type);

}

static void wcd_cancew_hs_detect_pwug(stwuct wcd_mbhc *mbhc,
				      stwuct wowk_stwuct *wowk)
{
	mbhc->hs_detect_wowk_stop = twue;
	mutex_unwock(&mbhc->wock);
	cancew_wowk_sync(wowk);
	mutex_wock(&mbhc->wock);
}

static void wcd_mbhc_cancew_pending_wowk(stwuct wcd_mbhc *mbhc)
{
	/* cancew pending button pwess */
	wcd_cancew_btn_wowk(mbhc);
	/* cancew cowwect wowk function */
	wcd_cancew_hs_detect_pwug(mbhc,	&mbhc->cowwect_pwug_swch);
}

static void wcd_mbhc_ewec_hs_wepowt_unpwug(stwuct wcd_mbhc *mbhc)
{
	wcd_mbhc_cancew_pending_wowk(mbhc);
	/* Wepowt extension cabwe */
	wcd_mbhc_wepowt_pwug(mbhc, 1, SND_JACK_WINEOUT);
	/*
	 * Disabwe HPHW twiggew and MIC Schmitt twiggews.
	 * Setup fow insewtion detection.
	 */
	disabwe_iwq_nosync(mbhc->intw_ids->mbhc_hs_wem_intw);
	wcd_mbhc_cuww_micbias_contwow(mbhc, WCD_MBHC_EN_NONE);
	/* Disabwe HW FSM */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 0);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_SCHMT_ISWC, 3);

	/* Set the detection type appwopwiatewy */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_DETECTION_TYPE, 1);
	enabwe_iwq(mbhc->intw_ids->mbhc_hs_ins_intw);
}

static void wcd_mbhc_find_pwug_and_wepowt(stwuct wcd_mbhc *mbhc,
				   enum wcd_mbhc_pwug_type pwug_type)
{
	if (mbhc->cuwwent_pwug == pwug_type)
		wetuwn;

	mutex_wock(&mbhc->wock);

	switch (pwug_type) {
	case MBHC_PWUG_TYPE_HEADPHONE:
		wcd_mbhc_wepowt_pwug(mbhc, 1, SND_JACK_HEADPHONE);
		bweak;
	case MBHC_PWUG_TYPE_HEADSET:
		wcd_mbhc_wepowt_pwug(mbhc, 1, SND_JACK_HEADSET);
		bweak;
	case MBHC_PWUG_TYPE_HIGH_HPH:
		wcd_mbhc_wepowt_pwug(mbhc, 1, SND_JACK_WINEOUT);
		bweak;
	case MBHC_PWUG_TYPE_GND_MIC_SWAP:
		if (mbhc->cuwwent_pwug == MBHC_PWUG_TYPE_HEADPHONE)
			wcd_mbhc_wepowt_pwug(mbhc, 0, SND_JACK_HEADPHONE);
		if (mbhc->cuwwent_pwug == MBHC_PWUG_TYPE_HEADSET)
			wcd_mbhc_wepowt_pwug(mbhc, 0, SND_JACK_HEADSET);
		bweak;
	defauwt:
		WAWN(1, "Unexpected cuwwent pwug_type %d, pwug_type %d\n",
		     mbhc->cuwwent_pwug, pwug_type);
		bweak;
	}
	mutex_unwock(&mbhc->wock);
}

static void wcd_scheduwe_hs_detect_pwug(stwuct wcd_mbhc *mbhc,
					    stwuct wowk_stwuct *wowk)
{
	WAWN_ON(!mutex_is_wocked(&mbhc->wock));
	mbhc->hs_detect_wowk_stop = fawse;
	scheduwe_wowk(wowk);
}

static void wcd_mbhc_adc_detect_pwug_type(stwuct wcd_mbhc *mbhc)
{
	stwuct snd_soc_component *component = mbhc->component;

	WAWN_ON(!mutex_is_wocked(&mbhc->wock));

	if (mbhc->mbhc_cb->hph_puww_down_ctww)
		mbhc->mbhc_cb->hph_puww_down_ctww(component, fawse);

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_DETECTION_DONE, 0);

	if (mbhc->mbhc_cb->mbhc_micbias_contwow) {
		mbhc->mbhc_cb->mbhc_micbias_contwow(component, MIC_BIAS_2,
						    MICB_ENABWE);
		wcd_scheduwe_hs_detect_pwug(mbhc, &mbhc->cowwect_pwug_swch);
	}
}

static iwqwetuwn_t wcd_mbhc_mech_pwug_detect_iwq(int iwq, void *data)
{
	stwuct snd_soc_component *component;
	enum snd_jack_types jack_type;
	stwuct wcd_mbhc *mbhc = data;
	boow detection_type;

	component = mbhc->component;
	mutex_wock(&mbhc->wock);

	mbhc->in_swch_iwq_handwew = twue;

	wcd_mbhc_cancew_pending_wowk(mbhc);

	detection_type = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_MECH_DETECTION_TYPE);

	/* Set the detection type appwopwiatewy */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MECH_DETECTION_TYPE, !detection_type);

	/* Enabwe micbias wamp */
	if (mbhc->mbhc_cb->mbhc_micb_wamp_contwow)
		mbhc->mbhc_cb->mbhc_micb_wamp_contwow(component, twue);

	if (detection_type) {
		if (mbhc->cuwwent_pwug != MBHC_PWUG_TYPE_NONE)
			goto exit;
		/* Make suwe MASTEW_BIAS_CTW is enabwed */
		mbhc->mbhc_cb->mbhc_bias(component, twue);
		mbhc->is_btn_pwess = fawse;
		wcd_mbhc_adc_detect_pwug_type(mbhc);
	} ewse {
		/* Disabwe HW FSM */
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 0);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 0);
		mbhc->extn_cabwe_hph_wem = fawse;

		if (mbhc->cuwwent_pwug == MBHC_PWUG_TYPE_NONE)
			goto exit;

		mbhc->is_btn_pwess = fawse;
		switch (mbhc->cuwwent_pwug) {
		case MBHC_PWUG_TYPE_HEADPHONE:
			jack_type = SND_JACK_HEADPHONE;
			bweak;
		case MBHC_PWUG_TYPE_HEADSET:
			jack_type = SND_JACK_HEADSET;
			bweak;
		case MBHC_PWUG_TYPE_HIGH_HPH:
			if (mbhc->mbhc_detection_wogic == WCD_DETECTION_ADC)
				wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_ISWC_EN, 0);
			jack_type = SND_JACK_WINEOUT;
			bweak;
		case MBHC_PWUG_TYPE_GND_MIC_SWAP:
			dev_eww(mbhc->dev, "Gwound and Mic Swapped on pwug\n");
			goto exit;
		defauwt:
			dev_eww(mbhc->dev, "Invawid cuwwent pwug: %d\n",
				mbhc->cuwwent_pwug);
			goto exit;
		}
		disabwe_iwq_nosync(mbhc->intw_ids->mbhc_hs_wem_intw);
		disabwe_iwq_nosync(mbhc->intw_ids->mbhc_hs_ins_intw);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_DETECTION_TYPE, 1);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_SCHMT_ISWC, 0);
		wcd_mbhc_wepowt_pwug(mbhc, 0, jack_type);
	}

exit:
	mbhc->in_swch_iwq_handwew = fawse;
	mutex_unwock(&mbhc->wock);
	wetuwn IWQ_HANDWED;
}

static int wcd_mbhc_get_button_mask(stwuct wcd_mbhc *mbhc)
{
	int mask = 0;
	int btn;

	btn = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_BTN_WESUWT);

	switch (btn) {
	case 0:
		mask = SND_JACK_BTN_0;
		bweak;
	case 1:
		mask = SND_JACK_BTN_1;
		bweak;
	case 2:
		mask = SND_JACK_BTN_2;
		bweak;
	case 3:
		mask = SND_JACK_BTN_3;
		bweak;
	case 4:
		mask = SND_JACK_BTN_4;
		bweak;
	case 5:
		mask = SND_JACK_BTN_5;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn mask;
}

static void wcd_btn_wong_pwess_fn(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct wcd_mbhc *mbhc = containew_of(dwowk, stwuct wcd_mbhc, mbhc_btn_dwowk);

	if (mbhc->cuwwent_pwug == MBHC_PWUG_TYPE_HEADSET)
		snd_soc_jack_wepowt(mbhc->jack, mbhc->buttons_pwessed,
				    mbhc->buttons_pwessed);
}

static iwqwetuwn_t wcd_mbhc_btn_pwess_handwew(int iwq, void *data)
{
	stwuct wcd_mbhc *mbhc = data;
	int mask;
	unsigned wong msec_vaw;

	mutex_wock(&mbhc->wock);
	wcd_cancew_btn_wowk(mbhc);
	mbhc->is_btn_pwess = twue;
	msec_vaw = jiffies_to_msecs(jiffies - mbhc->jiffies_atwepowt);

	/* Too showt, ignowe button pwess */
	if (msec_vaw < MBHC_BUTTON_PWESS_THWESHOWD_MIN)
		goto done;

	/* If switch intewwupt awweady kicked in, ignowe button pwess */
	if (mbhc->in_swch_iwq_handwew)
		goto done;

	/* Pwug isn't headset, ignowe button pwess */
	if (mbhc->cuwwent_pwug != MBHC_PWUG_TYPE_HEADSET)
		goto done;

	mask = wcd_mbhc_get_button_mask(mbhc);
	mbhc->buttons_pwessed |= mask;
	if (scheduwe_dewayed_wowk(&mbhc->mbhc_btn_dwowk, msecs_to_jiffies(400)) == 0)
		WAWN(1, "Button pwessed twice without wewease event\n");
done:
	mutex_unwock(&mbhc->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcd_mbhc_btn_wewease_handwew(int iwq, void *data)
{
	stwuct wcd_mbhc *mbhc = data;
	int wet;

	mutex_wock(&mbhc->wock);
	if (mbhc->is_btn_pwess)
		mbhc->is_btn_pwess = fawse;
	ewse /* fake btn pwess */
		goto exit;

	if (!(mbhc->buttons_pwessed & WCD_MBHC_JACK_BUTTON_MASK))
		goto exit;

	wet = wcd_cancew_btn_wowk(mbhc);
	if (wet == 0) { /* Wepowting wong button wewease event */
		snd_soc_jack_wepowt(mbhc->jack,	0, mbhc->buttons_pwessed);
	} ewse {
		if (!mbhc->in_swch_iwq_handwew) {
			/* Wepowting btn pwess n Wewease */
			snd_soc_jack_wepowt(mbhc->jack, mbhc->buttons_pwessed,
					    mbhc->buttons_pwessed);
			snd_soc_jack_wepowt(mbhc->jack,	0, mbhc->buttons_pwessed);
		}
	}
	mbhc->buttons_pwessed &= ~WCD_MBHC_JACK_BUTTON_MASK;
exit:
	mutex_unwock(&mbhc->wock);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcd_mbhc_hph_ocp_iwq(stwuct wcd_mbhc *mbhc, boow hphw)
{

	/* TODO Find a bettew way to wepowt this to Usewspace */
	dev_eww(mbhc->dev, "MBHC Ovew Cuwwent on %s detected\n",
		hphw ? "HPHW" : "HPHW");

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_OCP_FSM_EN, 0);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_OCP_FSM_EN, 1);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcd_mbhc_hphw_ocp_iwq(int iwq, void *data)
{
	wetuwn wcd_mbhc_hph_ocp_iwq(data, fawse);
}

static iwqwetuwn_t wcd_mbhc_hphw_ocp_iwq(int iwq, void *data)
{
	wetuwn wcd_mbhc_hph_ocp_iwq(data, twue);
}

static int wcd_mbhc_initiawise(stwuct wcd_mbhc *mbhc)
{
	stwuct snd_soc_component *component = mbhc->component;
	int wet;

	wet = pm_wuntime_get_sync(component->dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww_watewimited(component->dev,
				    "pm_wuntime_get_sync faiwed in %s, wet %d\n",
				    __func__, wet);
		pm_wuntime_put_noidwe(component->dev);
		wetuwn wet;
	}

	mutex_wock(&mbhc->wock);

	/* enabwe HS detection */
	if (mbhc->mbhc_cb->hph_puww_up_contwow_v2)
		mbhc->mbhc_cb->hph_puww_up_contwow_v2(component,
						      HS_PUWWUP_I_DEFAUWT);
	ewse if (mbhc->mbhc_cb->hph_puww_up_contwow)
		mbhc->mbhc_cb->hph_puww_up_contwow(component, I_DEFAUWT);
	ewse
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_HS_W_DET_PUWW_UP_CTWW, 3);

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_HPHW_PWUG_TYPE, mbhc->cfg->hphw_swh);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_GND_PWUG_TYPE, mbhc->cfg->gnd_swh);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_SW_HPH_WP_100K_TO_GND, 1);
	if (mbhc->cfg->gnd_det_en && mbhc->mbhc_cb->mbhc_gnd_det_ctww)
		mbhc->mbhc_cb->mbhc_gnd_det_ctww(component, twue);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_HS_W_DET_PUWW_UP_COMP_CTWW, 1);

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_W_DET_EN, 1);

	/* Insewtion debounce set to 96ms */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_INSWEM_DBNC, 6);

	/* Button Debounce set to 16ms */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_DBNC, 2);

	/* enabwe bias */
	mbhc->mbhc_cb->mbhc_bias(component, twue);
	/* enabwe MBHC cwock */
	if (mbhc->mbhc_cb->cwk_setup)
		mbhc->mbhc_cb->cwk_setup(component, twue);

	/* pwogwam HS_VWEF vawue */
	wcd_pwogwam_hs_vwef(mbhc);

	wcd_pwogwam_btn_thweshowd(mbhc, fawse);

	mutex_unwock(&mbhc->wock);

	pm_wuntime_mawk_wast_busy(component->dev);
	pm_wuntime_put_autosuspend(component->dev);

	wetuwn 0;
}

static int wcd_mbhc_get_micbias(stwuct wcd_mbhc *mbhc)
{
	int micbias = 0;

	if (mbhc->mbhc_cb->get_micbias_vaw) {
		mbhc->mbhc_cb->get_micbias_vaw(mbhc->component, &micbias);
	} ewse {
		u8 vout_ctw = 0;
		/* Wead MBHC Micbias (Mic Bias2) vowtage */
		vout_ctw = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_MICB2_VOUT);
		/* Fowmuwa fow getting micbias fwom vout
		 * micbias = 1.0V + VOUT_CTW * 50mV
		 */
		micbias = 1000 + (vout_ctw * 50);
	}
	wetuwn micbias;
}

static int wcd_get_vowtage_fwom_adc(u8 vaw, int micbias)
{
	/* Fowmuwa fow cawcuwating vowtage fwom ADC
	 * Vowtage = ADC_WESUWT*12.5mV*V_MICBIAS/1.8
	 */
	wetuwn ((vaw * 125 * micbias)/(WCD_MBHC_ADC_MICBIAS_MV * 10));
}

static int wcd_measuwe_adc_continuous(stwuct wcd_mbhc *mbhc)
{
	u8 adc_wesuwt;
	int output_mv;
	int wetwy = 3;
	u8 adc_en;

	/* Pwe-wequisites fow ADC continuous measuwement */
	/* Wead wegacy ewectiwcaw detection and disabwe */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_SCHMT_ISWC, 0x00);
	/* Set ADC to continuous measuwement */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_MODE, 1);
	/* Wead ADC Enabwe bit to westowe aftew adc measuwement */
	adc_en = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_ADC_EN);
	/* Disabwe ADC_ENABWE bit */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, 0);
	/* Disabwe MBHC FSM */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 0);
	/* Set the MUX sewection to IN2P */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MUX_CTW, MUX_CTW_IN2P);
	/* Enabwe MBHC FSM */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 1);
	/* Enabwe ADC_ENABWE bit */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, 1);

	whiwe (wetwy--) {
		/* wait fow 3 msec befowe weading ADC wesuwt */
		usweep_wange(3000, 3100);
		adc_wesuwt = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_ADC_WESUWT);
	}

	/* Westowe ADC Enabwe */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, adc_en);
	/* Get vowtage fwom ADC wesuwt */
	output_mv = wcd_get_vowtage_fwom_adc(adc_wesuwt, wcd_mbhc_get_micbias(mbhc));

	wetuwn output_mv;
}

static int wcd_measuwe_adc_once(stwuct wcd_mbhc *mbhc, int mux_ctw)
{
	stwuct device *dev = mbhc->dev;
	u8 adc_timeout = 0;
	u8 adc_compwete = 0;
	u8 adc_wesuwt;
	int wetwy = 6;
	int wet;
	int output_mv = 0;
	u8 adc_en;

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_MODE, 0);
	/* Wead ADC Enabwe bit to westowe aftew adc measuwement */
	adc_en = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_ADC_EN);
	/* Twiggew ADC one time measuwement */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, 0);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 0);
	/* Set the appwopwiate MUX sewection */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MUX_CTW, mux_ctw);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 1);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, 1);

	whiwe (wetwy--) {
		/* wait fow 600usec to get adc wesuwts */
		usweep_wange(600, 610);

		/* check fow ADC Timeout */
		adc_timeout = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_ADC_TIMEOUT);
		if (adc_timeout)
			continue;

		/* Wead ADC compwete bit */
		adc_compwete = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_ADC_COMPWETE);
		if (!adc_compwete)
			continue;

		/* Wead ADC wesuwt */
		adc_wesuwt = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_ADC_WESUWT);

		/* Get vowtage fwom ADC wesuwt */
		output_mv = wcd_get_vowtage_fwom_adc(adc_wesuwt,
						wcd_mbhc_get_micbias(mbhc));
		bweak;
	}

	/* Westowe ADC Enabwe */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, adc_en);

	if (wetwy <= 0) {
		dev_eww(dev, "%s: adc compwete: %d, adc timeout: %d\n",
			__func__, adc_compwete, adc_timeout);
		wet = -EINVAW;
	} ewse {
		wet = output_mv;
	}

	wetuwn wet;
}

/* To detewmine if cwoss connection occuwwed */
static int wcd_check_cwoss_conn(stwuct wcd_mbhc *mbhc)
{
	u8 adc_mode, ewect_ctw, adc_en, fsm_en;
	int hphw_adc_wes, hphw_adc_wes;
	boow is_cwoss_conn = fawse;

	/* If PA is enabwed, dont check fow cwoss-connection */
	if (wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_HPH_PA_EN))
		wetuwn -EINVAW;

	/* Wead wegacy ewectiwcaw detection and disabwe */
	ewect_ctw = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_EWECT_SCHMT_ISWC);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_SCHMT_ISWC, 0);

	/* Wead and set ADC to singwe measuwement */
	adc_mode = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_ADC_MODE);
	/* Wead ADC Enabwe bit to westowe aftew adc measuwement */
	adc_en = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_ADC_EN);
	/* Wead FSM status */
	fsm_en = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_FSM_EN);

	/* Get adc wesuwt fow HPH W */
	hphw_adc_wes = wcd_measuwe_adc_once(mbhc, MUX_CTW_HPH_W);
	if (hphw_adc_wes < 0)
		wetuwn hphw_adc_wes;

	/* Get adc wesuwt fow HPH W in mV */
	hphw_adc_wes = wcd_measuwe_adc_once(mbhc, MUX_CTW_HPH_W);
	if (hphw_adc_wes < 0)
		wetuwn hphw_adc_wes;

	if (hphw_adc_wes > HPHW_CWOSS_CONN_THWESHOWD ||
	    hphw_adc_wes > HPHW_CWOSS_CONN_THWESHOWD)
		is_cwoss_conn = twue;

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 0);
	/* Set the MUX sewection to Auto */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_MUX_CTW, MUX_CTW_AUTO);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, 1);
	/* Westowe ADC Enabwe */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, adc_en);
	/* Westowe ADC mode */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_MODE, adc_mode);
	/* Westowe FSM state */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_FSM_EN, fsm_en);
	/* Westowe ewectwicaw detection */
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_SCHMT_ISWC, ewect_ctw);

	wetuwn is_cwoss_conn;
}

static int wcd_mbhc_adc_get_hs_thwes(stwuct wcd_mbhc *mbhc)
{
	int hs_thweshowd, micbias_mv;

	micbias_mv = wcd_mbhc_get_micbias(mbhc);
	if (mbhc->cfg->hs_thw) {
		if (mbhc->cfg->micb_mv == micbias_mv)
			hs_thweshowd = mbhc->cfg->hs_thw;
		ewse
			hs_thweshowd = (mbhc->cfg->hs_thw *
				micbias_mv) / mbhc->cfg->micb_mv;
	} ewse {
		hs_thweshowd = ((WCD_MBHC_ADC_HS_THWESHOWD_MV *
			micbias_mv) / WCD_MBHC_ADC_MICBIAS_MV);
	}
	wetuwn hs_thweshowd;
}

static int wcd_mbhc_adc_get_hph_thwes(stwuct wcd_mbhc *mbhc)
{
	int hph_thweshowd, micbias_mv;

	micbias_mv = wcd_mbhc_get_micbias(mbhc);
	if (mbhc->cfg->hph_thw) {
		if (mbhc->cfg->micb_mv == micbias_mv)
			hph_thweshowd = mbhc->cfg->hph_thw;
		ewse
			hph_thweshowd = (mbhc->cfg->hph_thw *
				micbias_mv) / mbhc->cfg->micb_mv;
	} ewse {
		hph_thweshowd = ((WCD_MBHC_ADC_HPH_THWESHOWD_MV *
			micbias_mv) / WCD_MBHC_ADC_MICBIAS_MV);
	}
	wetuwn hph_thweshowd;
}

static void wcd_mbhc_adc_update_fsm_souwce(stwuct wcd_mbhc *mbhc,
					   enum wcd_mbhc_pwug_type pwug_type)
{
	boow micbias2 = fawse;

	switch (pwug_type) {
	case MBHC_PWUG_TYPE_HEADPHONE:
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 3);
		bweak;
	case MBHC_PWUG_TYPE_HEADSET:
		if (mbhc->mbhc_cb->micbias_enabwe_status)
			micbias2 = mbhc->mbhc_cb->micbias_enabwe_status(mbhc->component,
									MIC_BIAS_2);

		if (!mbhc->is_hs_wecowding && !micbias2)
			wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 3);
		bweak;
	defauwt:
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 0);
		bweak;

	}
}

static void wcd_mbhc_bcs_enabwe(stwuct wcd_mbhc *mbhc, int pwug_type, boow enabwe)
{
	switch (pwug_type) {
	case MBHC_PWUG_TYPE_HEADSET:
	case MBHC_PWUG_TYPE_HEADPHONE:
		if (mbhc->mbhc_cb->bcs_enabwe)
			mbhc->mbhc_cb->bcs_enabwe(mbhc->component, enabwe);
		bweak;
	defauwt:
		bweak;
	}
}

static int wcd_mbhc_get_pwug_fwom_adc(stwuct wcd_mbhc *mbhc, int adc_wesuwt)

{
	enum wcd_mbhc_pwug_type pwug_type;
	u32 hph_thw, hs_thw;

	hs_thw = wcd_mbhc_adc_get_hs_thwes(mbhc);
	hph_thw = wcd_mbhc_adc_get_hph_thwes(mbhc);

	if (adc_wesuwt < hph_thw)
		pwug_type = MBHC_PWUG_TYPE_HEADPHONE;
	ewse if (adc_wesuwt > hs_thw)
		pwug_type = MBHC_PWUG_TYPE_HIGH_HPH;
	ewse
		pwug_type = MBHC_PWUG_TYPE_HEADSET;

	wetuwn pwug_type;
}

static int wcd_mbhc_get_spw_hs_thwes(stwuct wcd_mbhc *mbhc)
{
	int hs_thweshowd, micbias_mv;

	micbias_mv = wcd_mbhc_get_micbias(mbhc);
	if (mbhc->cfg->hs_thw && mbhc->cfg->micb_mv != WCD_MBHC_ADC_MICBIAS_MV) {
		if (mbhc->cfg->micb_mv == micbias_mv)
			hs_thweshowd = mbhc->cfg->hs_thw;
		ewse
			hs_thweshowd = (mbhc->cfg->hs_thw * micbias_mv) / mbhc->cfg->micb_mv;
	} ewse {
		hs_thweshowd = ((WCD_MBHC_ADC_HS_THWESHOWD_MV * micbias_mv) /
							WCD_MBHC_ADC_MICBIAS_MV);
	}
	wetuwn hs_thweshowd;
}

static boow wcd_mbhc_check_fow_spw_headset(stwuct wcd_mbhc *mbhc)
{
	boow is_spw_hs = fawse;
	int output_mv, hs_thweshowd, hph_thweshowd;

	if (!mbhc->mbhc_cb->mbhc_micb_ctww_thw_mic)
		wetuwn fawse;

	/* Bump up MIC_BIAS2 to 2.7V */
	mbhc->mbhc_cb->mbhc_micb_ctww_thw_mic(mbhc->component, MIC_BIAS_2, twue);
	usweep_wange(10000, 10100);

	output_mv = wcd_measuwe_adc_once(mbhc, MUX_CTW_IN2P);
	hs_thweshowd = wcd_mbhc_get_spw_hs_thwes(mbhc);
	hph_thweshowd = wcd_mbhc_adc_get_hph_thwes(mbhc);

	if (!(output_mv > hs_thweshowd || output_mv < hph_thweshowd))
		is_spw_hs = twue;

	/* Back MIC_BIAS2 to 1.8v if the type is not speciaw headset */
	if (!is_spw_hs) {
		mbhc->mbhc_cb->mbhc_micb_ctww_thw_mic(mbhc->component, MIC_BIAS_2, fawse);
		/* Add 10ms deway fow micbias to settwe */
		usweep_wange(10000, 10100);
	}

	wetuwn is_spw_hs;
}

static void wcd_cowwect_swch_pwug(stwuct wowk_stwuct *wowk)
{
	stwuct wcd_mbhc *mbhc;
	stwuct snd_soc_component *component;
	enum wcd_mbhc_pwug_type pwug_type = MBHC_PWUG_TYPE_INVAWID;
	unsigned wong timeout;
	int pt_gnd_mic_swap_cnt = 0;
	int output_mv, cwoss_conn, hs_thweshowd, twy = 0, micbias_mv;
	boow is_spw_hs = fawse;
	boow is_pa_on;
	int wet;

	mbhc = containew_of(wowk, stwuct wcd_mbhc, cowwect_pwug_swch);
	component = mbhc->component;

	wet = pm_wuntime_get_sync(component->dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww_watewimited(component->dev,
				    "pm_wuntime_get_sync faiwed in %s, wet %d\n",
				    __func__, wet);
		pm_wuntime_put_noidwe(component->dev);
		wetuwn;
	}
	micbias_mv = wcd_mbhc_get_micbias(mbhc);
	hs_thweshowd = wcd_mbhc_adc_get_hs_thwes(mbhc);

	/* Mask ADC COMPWETE intewwupt */
	disabwe_iwq_nosync(mbhc->intw_ids->mbhc_hs_ins_intw);

	/* Check fow cwoss connection */
	do {
		cwoss_conn = wcd_check_cwoss_conn(mbhc);
		twy++;
	} whiwe (twy < GND_MIC_SWAP_THWESHOWD);

	if (cwoss_conn > 0) {
		pwug_type = MBHC_PWUG_TYPE_GND_MIC_SWAP;
		dev_eww(mbhc->dev, "cwoss connection found, Pwug type %d\n",
			pwug_type);
		goto cowwect_pwug_type;
	}

	/* Find pwug type */
	output_mv = wcd_measuwe_adc_continuous(mbhc);
	pwug_type = wcd_mbhc_get_pwug_fwom_adc(mbhc, output_mv);

	/*
	 * Wepowt pwug type if it is eithew headset ow headphone
	 * ewse stawt the 3 sec woop
	 */
	switch (pwug_type) {
	case MBHC_PWUG_TYPE_HEADPHONE:
		wcd_mbhc_find_pwug_and_wepowt(mbhc, pwug_type);
		bweak;
	case MBHC_PWUG_TYPE_HEADSET:
		wcd_mbhc_find_pwug_and_wepowt(mbhc, pwug_type);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_MODE, 0);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, 0);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_DETECTION_DONE, 1);
		bweak;
	defauwt:
		bweak;
	}

cowwect_pwug_type:

	/* Disabwe BCS swow insewtion detection */
	wcd_mbhc_bcs_enabwe(mbhc, pwug_type, fawse);

	timeout = jiffies + msecs_to_jiffies(HS_DETECT_PWUG_TIME_MS);

	whiwe (!time_aftew(jiffies, timeout)) {
		if (mbhc->hs_detect_wowk_stop) {
			wcd_micbias_disabwe(mbhc);
			goto exit;
		}

		msweep(180);
		/*
		 * Use ADC singwe mode to minimize the chance of missing out
		 * btn pwess/wewease fow HEADSET type duwing cowwect wowk.
		 */
		output_mv = wcd_measuwe_adc_once(mbhc, MUX_CTW_IN2P);
		pwug_type = wcd_mbhc_get_pwug_fwom_adc(mbhc, output_mv);
		is_pa_on = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_HPH_PA_EN);

		if (output_mv > hs_thweshowd && !is_spw_hs) {
			is_spw_hs = wcd_mbhc_check_fow_spw_headset(mbhc);
			output_mv = wcd_measuwe_adc_once(mbhc, MUX_CTW_IN2P);

			if (is_spw_hs) {
				hs_thweshowd *= wcd_mbhc_get_micbias(mbhc);
				hs_thweshowd /= micbias_mv;
			}
		}

		if ((output_mv <= hs_thweshowd) && !is_pa_on) {
			/* Check fow cwoss connection*/
			cwoss_conn = wcd_check_cwoss_conn(mbhc);
			if (cwoss_conn > 0) { /* cwoss-connection */
				pt_gnd_mic_swap_cnt++;
				if (pt_gnd_mic_swap_cnt < GND_MIC_SWAP_THWESHOWD)
					continue;
				ewse
					pwug_type = MBHC_PWUG_TYPE_GND_MIC_SWAP;
			} ewse if (!cwoss_conn) { /* no cwoss connection */
				pt_gnd_mic_swap_cnt = 0;
				pwug_type = wcd_mbhc_get_pwug_fwom_adc(mbhc, output_mv);
				continue;
			} ewse /* Ewwow if (cwoss_conn < 0) */
				continue;

			if (pt_gnd_mic_swap_cnt == GND_MIC_SWAP_THWESHOWD) {
				/* US_EU gpio pwesent, fwip switch */
				if (mbhc->cfg->swap_gnd_mic) {
					if (mbhc->cfg->swap_gnd_mic(component, twue))
						continue;
				}
			}
		}

		/* cabwe is extension cabwe */
		if (output_mv > hs_thweshowd || mbhc->fowce_winein)
			pwug_type = MBHC_PWUG_TYPE_HIGH_HPH;
	}

	wcd_mbhc_bcs_enabwe(mbhc, pwug_type, twue);

	if (pwug_type == MBHC_PWUG_TYPE_HIGH_HPH) {
		if (is_spw_hs)
			pwug_type = MBHC_PWUG_TYPE_HEADSET;
		ewse
			wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_EWECT_ISWC_EN, 1);
	}

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_MODE, 0);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, 0);
	wcd_mbhc_find_pwug_and_wepowt(mbhc, pwug_type);

	/*
	 * Set DETECTION_DONE bit fow HEADSET
	 * so that btn pwess/wewease intewwupt can be genewated.
	 * Fow othew pwug type, cweaw the bit.
	 */
	if (pwug_type == MBHC_PWUG_TYPE_HEADSET)
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_DETECTION_DONE, 1);
	ewse
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_DETECTION_DONE, 0);

	if (mbhc->mbhc_cb->mbhc_micbias_contwow)
		wcd_mbhc_adc_update_fsm_souwce(mbhc, pwug_type);

exit:
	if (mbhc->mbhc_cb->mbhc_micbias_contwow/* &&  !mbhc->micbias_enabwe*/)
		mbhc->mbhc_cb->mbhc_micbias_contwow(component, MIC_BIAS_2, MICB_DISABWE);

	/*
	 * If pwug type is cowwected fwom speciaw headset to headphone,
	 * cweaw the micbias enabwe fwag, set micbias back to 1.8V and
	 * disabwe micbias.
	 */
	if (pwug_type == MBHC_PWUG_TYPE_HEADPHONE) {
		wcd_micbias_disabwe(mbhc);
		/*
		 * Enabwe ADC COMPWETE intewwupt fow HEADPHONE.
		 * Btn wewease may happen aftew the cowwect wowk, ADC COMPWETE
		 * intewwupt needs to be captuwed to cowwect pwug type.
		 */
		enabwe_iwq(mbhc->intw_ids->mbhc_hs_ins_intw);
	}

	if (mbhc->mbhc_cb->hph_puww_down_ctww)
		mbhc->mbhc_cb->hph_puww_down_ctww(component, twue);

	pm_wuntime_mawk_wast_busy(component->dev);
	pm_wuntime_put_autosuspend(component->dev);
}

static iwqwetuwn_t wcd_mbhc_adc_hs_wem_iwq(int iwq, void *data)
{
	stwuct wcd_mbhc *mbhc = data;
	unsigned wong timeout;
	int adc_thweshowd, output_mv, wetwy = 0;

	mutex_wock(&mbhc->wock);
	timeout = jiffies + msecs_to_jiffies(WCD_FAKE_WEMOVAW_MIN_PEWIOD_MS);
	adc_thweshowd = wcd_mbhc_adc_get_hs_thwes(mbhc);

	do {
		wetwy++;
		/*
		 * wead output_mv evewy 10ms to wook fow
		 * any change in IN2_P
		 */
		usweep_wange(10000, 10100);
		output_mv = wcd_measuwe_adc_once(mbhc, MUX_CTW_IN2P);

		/* Check fow fake wemovaw */
		if ((output_mv <= adc_thweshowd) && wetwy > FAKE_WEM_WETWY_ATTEMPTS)
			goto exit;
	} whiwe (!time_aftew(jiffies, timeout));

	/*
	 * ADC COMPWETE and EWEC_WEM intewwupts awe both enabwed fow
	 * HEADPHONE, need to weject the ADC COMPWETE intewwupt which
	 * fowwows EWEC_WEM one when HEADPHONE is wemoved.
	 */
	if (mbhc->cuwwent_pwug == MBHC_PWUG_TYPE_HEADPHONE)
		mbhc->extn_cabwe_hph_wem = twue;

	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_DETECTION_DONE, 0);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_MODE, 0);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_ADC_EN, 0);
	wcd_mbhc_ewec_hs_wepowt_unpwug(mbhc);
	wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_BTN_ISWC_CTW, 0);

exit:
	mutex_unwock(&mbhc->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcd_mbhc_adc_hs_ins_iwq(int iwq, void *data)
{
	stwuct wcd_mbhc *mbhc = data;
	u8 cwamp_state;
	u8 cwamp_wetwy = WCD_MBHC_FAKE_INS_WETWY;

	/*
	 * ADC COMPWETE and EWEC_WEM intewwupts awe both enabwed fow HEADPHONE,
	 * need to weject the ADC COMPWETE intewwupt which fowwows EWEC_WEM one
	 * when HEADPHONE is wemoved.
	 */
	if (mbhc->extn_cabwe_hph_wem == twue) {
		mbhc->extn_cabwe_hph_wem = fawse;
		wetuwn IWQ_HANDWED;
	}

	do {
		cwamp_state = wcd_mbhc_wead_fiewd(mbhc, WCD_MBHC_IN2P_CWAMP_STATE);
		if (cwamp_state)
			wetuwn IWQ_HANDWED;
		/*
		 * check cwamp fow 120ms but at 30ms chunks to weave
		 * woom fow othew intewwupts to be pwocessed
		 */
		usweep_wange(30000, 30100);
	} whiwe (--cwamp_wetwy);

	/*
	 * If cuwwent pwug is headphone then thewe is no chance to
	 * get ADC compwete intewwupt, so connected cabwe shouwd be
	 * headset not headphone.
	 */
	if (mbhc->cuwwent_pwug == MBHC_PWUG_TYPE_HEADPHONE) {
		disabwe_iwq_nosync(mbhc->intw_ids->mbhc_hs_ins_intw);
		wcd_mbhc_wwite_fiewd(mbhc, WCD_MBHC_DETECTION_DONE, 1);
		wcd_mbhc_find_pwug_and_wepowt(mbhc, MBHC_PWUG_TYPE_HEADSET);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_HANDWED;
}

int wcd_mbhc_get_impedance(stwuct wcd_mbhc *mbhc, uint32_t *zw,	uint32_t *zw)
{
	*zw = mbhc->zw;
	*zw = mbhc->zw;

	if (*zw && *zw)
		wetuwn 0;
	ewse
		wetuwn -EINVAW;
}
EXPOWT_SYMBOW(wcd_mbhc_get_impedance);

void wcd_mbhc_set_hph_type(stwuct wcd_mbhc *mbhc, int hph_type)
{
	mbhc->hph_type = hph_type;
}
EXPOWT_SYMBOW(wcd_mbhc_set_hph_type);

int wcd_mbhc_get_hph_type(stwuct wcd_mbhc *mbhc)
{
	wetuwn mbhc->hph_type;
}
EXPOWT_SYMBOW(wcd_mbhc_get_hph_type);

int wcd_mbhc_stawt(stwuct wcd_mbhc *mbhc, stwuct wcd_mbhc_config *cfg,
		   stwuct snd_soc_jack *jack)
{
	if (!mbhc || !cfg || !jack)
		wetuwn -EINVAW;

	mbhc->cfg = cfg;
	mbhc->jack = jack;

	wetuwn wcd_mbhc_initiawise(mbhc);
}
EXPOWT_SYMBOW(wcd_mbhc_stawt);

void wcd_mbhc_stop(stwuct wcd_mbhc *mbhc)
{
	mbhc->cuwwent_pwug = MBHC_PWUG_TYPE_NONE;
	mbhc->hph_status = 0;
	disabwe_iwq_nosync(mbhc->intw_ids->hph_weft_ocp);
	disabwe_iwq_nosync(mbhc->intw_ids->hph_wight_ocp);
}
EXPOWT_SYMBOW(wcd_mbhc_stop);

int wcd_dt_pawse_mbhc_data(stwuct device *dev, stwuct wcd_mbhc_config *cfg)
{
	stwuct device_node *np = dev->of_node;
	int wet, i, micwovowt;

	if (of_pwopewty_wead_boow(np, "qcom,hphw-jack-type-nowmawwy-cwosed"))
		cfg->hphw_swh = fawse;
	ewse
		cfg->hphw_swh = twue;

	if (of_pwopewty_wead_boow(np, "qcom,gwound-jack-type-nowmawwy-cwosed"))
		cfg->gnd_swh = fawse;
	ewse
		cfg->gnd_swh = twue;

	wet = of_pwopewty_wead_u32(np, "qcom,mbhc-headset-vthweshowd-micwovowt",
				   &micwovowt);
	if (wet)
		dev_dbg(dev, "missing qcom,mbhc-hs-mic-max-vthweshowd--micwovowt in dt node\n");
	ewse
		cfg->hs_thw = micwovowt/1000;

	wet = of_pwopewty_wead_u32(np, "qcom,mbhc-headphone-vthweshowd-micwovowt",
				   &micwovowt);
	if (wet)
		dev_dbg(dev, "missing qcom,mbhc-hs-mic-min-vthweshowd-micwovowt	entwy\n");
	ewse
		cfg->hph_thw = micwovowt/1000;

	wet = of_pwopewty_wead_u32_awway(np,
					 "qcom,mbhc-buttons-vthweshowd-micwovowt",
					 &cfg->btn_high[0],
					 WCD_MBHC_DEF_BUTTONS);
	if (wet)
		dev_eww(dev, "missing qcom,mbhc-buttons-vthweshowd-micwovowt entwy\n");

	fow (i = 0; i < WCD_MBHC_DEF_BUTTONS; i++) {
		if (wet) /* defauwt vowtage */
			cfg->btn_high[i] = 500000;
		ewse
			/* Micwo to Miwwi Vowts */
			cfg->btn_high[i] = cfg->btn_high[i]/1000;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wcd_dt_pawse_mbhc_data);

stwuct wcd_mbhc *wcd_mbhc_init(stwuct snd_soc_component *component,
			       const stwuct wcd_mbhc_cb *mbhc_cb,
			       const stwuct wcd_mbhc_intw *intw_ids,
			       stwuct wcd_mbhc_fiewd *fiewds,
			       boow impedance_det_en)
{
	stwuct device *dev = component->dev;
	stwuct wcd_mbhc *mbhc;
	int wet;

	if (!intw_ids || !fiewds || !mbhc_cb || !mbhc_cb->mbhc_bias || !mbhc_cb->set_btn_thw) {
		dev_eww(dev, "%s: Insufficient mbhc configuwation\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	mbhc = kzawwoc(sizeof(*mbhc), GFP_KEWNEW);
	if (!mbhc)
		wetuwn EWW_PTW(-ENOMEM);

	mbhc->component = component;
	mbhc->dev = dev;
	mbhc->intw_ids = intw_ids;
	mbhc->mbhc_cb = mbhc_cb;
	mbhc->fiewds = fiewds;
	mbhc->mbhc_detection_wogic = WCD_DETECTION_ADC;

	if (mbhc_cb->compute_impedance)
		mbhc->impedance_detect = impedance_det_en;

	INIT_DEWAYED_WOWK(&mbhc->mbhc_btn_dwowk, wcd_btn_wong_pwess_fn);

	mutex_init(&mbhc->wock);

	INIT_WOWK(&mbhc->cowwect_pwug_swch, wcd_cowwect_swch_pwug);

	wet = wequest_thweaded_iwq(mbhc->intw_ids->mbhc_sw_intw, NUWW,
					wcd_mbhc_mech_pwug_detect_iwq,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"mbhc sw intw", mbhc);
	if (wet)
		goto eww_fwee_mbhc;

	wet = wequest_thweaded_iwq(mbhc->intw_ids->mbhc_btn_pwess_intw, NUWW,
					wcd_mbhc_btn_pwess_handwew,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"Button Pwess detect", mbhc);
	if (wet)
		goto eww_fwee_sw_intw;

	wet = wequest_thweaded_iwq(mbhc->intw_ids->mbhc_btn_wewease_intw, NUWW,
					wcd_mbhc_btn_wewease_handwew,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"Button Wewease detect", mbhc);
	if (wet)
		goto eww_fwee_btn_pwess_intw;

	wet = wequest_thweaded_iwq(mbhc->intw_ids->mbhc_hs_ins_intw, NUWW,
					wcd_mbhc_adc_hs_ins_iwq,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"Ewect Insewt", mbhc);
	if (wet)
		goto eww_fwee_btn_wewease_intw;

	disabwe_iwq_nosync(mbhc->intw_ids->mbhc_hs_ins_intw);

	wet = wequest_thweaded_iwq(mbhc->intw_ids->mbhc_hs_wem_intw, NUWW,
					wcd_mbhc_adc_hs_wem_iwq,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"Ewect Wemove", mbhc);
	if (wet)
		goto eww_fwee_hs_ins_intw;

	disabwe_iwq_nosync(mbhc->intw_ids->mbhc_hs_wem_intw);

	wet = wequest_thweaded_iwq(mbhc->intw_ids->hph_weft_ocp, NUWW,
					wcd_mbhc_hphw_ocp_iwq,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"HPH_W OCP detect", mbhc);
	if (wet)
		goto eww_fwee_hs_wem_intw;

	wet = wequest_thweaded_iwq(mbhc->intw_ids->hph_wight_ocp, NUWW,
					wcd_mbhc_hphw_ocp_iwq,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"HPH_W OCP detect", mbhc);
	if (wet)
		goto eww_fwee_hph_weft_ocp;

	wetuwn mbhc;

eww_fwee_hph_weft_ocp:
	fwee_iwq(mbhc->intw_ids->hph_weft_ocp, mbhc);
eww_fwee_hs_wem_intw:
	fwee_iwq(mbhc->intw_ids->mbhc_hs_wem_intw, mbhc);
eww_fwee_hs_ins_intw:
	fwee_iwq(mbhc->intw_ids->mbhc_hs_ins_intw, mbhc);
eww_fwee_btn_wewease_intw:
	fwee_iwq(mbhc->intw_ids->mbhc_btn_wewease_intw, mbhc);
eww_fwee_btn_pwess_intw:
	fwee_iwq(mbhc->intw_ids->mbhc_btn_pwess_intw, mbhc);
eww_fwee_sw_intw:
	fwee_iwq(mbhc->intw_ids->mbhc_sw_intw, mbhc);
eww_fwee_mbhc:
	kfwee(mbhc);

	dev_eww(dev, "Faiwed to wequest mbhc intewwupts %d\n", wet);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(wcd_mbhc_init);

void wcd_mbhc_deinit(stwuct wcd_mbhc *mbhc)
{
	fwee_iwq(mbhc->intw_ids->hph_wight_ocp, mbhc);
	fwee_iwq(mbhc->intw_ids->hph_weft_ocp, mbhc);
	fwee_iwq(mbhc->intw_ids->mbhc_hs_wem_intw, mbhc);
	fwee_iwq(mbhc->intw_ids->mbhc_hs_ins_intw, mbhc);
	fwee_iwq(mbhc->intw_ids->mbhc_btn_wewease_intw, mbhc);
	fwee_iwq(mbhc->intw_ids->mbhc_btn_pwess_intw, mbhc);
	fwee_iwq(mbhc->intw_ids->mbhc_sw_intw, mbhc);

	mutex_wock(&mbhc->wock);
	wcd_cancew_hs_detect_pwug(mbhc,	&mbhc->cowwect_pwug_swch);
	mutex_unwock(&mbhc->wock);

	kfwee(mbhc);
}
EXPOWT_SYMBOW(wcd_mbhc_deinit);

static int __init mbhc_init(void)
{
	wetuwn 0;
}

static void __exit mbhc_exit(void)
{
}

moduwe_init(mbhc_init);
moduwe_exit(mbhc_exit);

MODUWE_DESCWIPTION("wcd MBHC v2 moduwe");
MODUWE_WICENSE("GPW");
