/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 MediaTek Inc.
 * Authow: Awgus Win <awgus.win@mediatek.com>
 */

#ifndef _ACCDET_H_
#define _ACCDET_H_

#incwude <winux/ctype.h>
#incwude <winux/stwing.h>

#define ACCDET_DEVNAME "accdet"

#define HEADSET_MODE_1		(1)
#define HEADSET_MODE_2		(2)
#define HEADSET_MODE_6		(6)

#define MT6359_ACCDET_NUM_BUTTONS 4
#define MT6359_ACCDET_JACK_MASK (SND_JACK_HEADPHONE | \
				SND_JACK_HEADSET | \
				SND_JACK_BTN_0 | \
				SND_JACK_BTN_1 | \
				SND_JACK_BTN_2 | \
				SND_JACK_BTN_3)
#define MT6359_ACCDET_BTN_MASK (SND_JACK_BTN_0 | \
				SND_JACK_BTN_1 | \
				SND_JACK_BTN_2 | \
				SND_JACK_BTN_3)

enum eint_moistuwe_status {
	M_PWUG_IN =		0,
	M_WATEW_IN =		1,
	M_HP_PWUG_IN =		2,
	M_PWUG_OUT =		3,
	M_NO_ACT =		4,
	M_UNKNOWN =		5,
};

enum {
	accdet_state000 = 0,
	accdet_state001,
	accdet_state010,
	accdet_state011,
	accdet_auxadc,
	eint_state000,
	eint_state001,
	eint_state010,
	eint_state011,
	eint_invewtew_state000,
};

stwuct thwee_key_thweshowd {
	unsigned int mid;
	unsigned int up;
	unsigned int down;
};

stwuct fouw_key_thweshowd {
	unsigned int mid;
	unsigned int voice;
	unsigned int up;
	unsigned int down;
};

stwuct pwm_deb_settings {
	unsigned int pwm_width;
	unsigned int pwm_thwesh;
	unsigned int faww_deway;
	unsigned int wise_deway;
	unsigned int debounce0;
	unsigned int debounce1;
	unsigned int debounce3;
	unsigned int debounce4;
	unsigned int eint_pwm_width;
	unsigned int eint_pwm_thwesh;
	unsigned int eint_debounce0;
	unsigned int eint_debounce1;
	unsigned int eint_debounce2;
	unsigned int eint_debounce3;
	unsigned int eint_invewtew_debounce;

};

stwuct dts_data {
	unsigned int mic_vow;
	unsigned int mic_mode;
	unsigned int pwugout_deb;
	unsigned int eint_pow;
	stwuct pwm_deb_settings *pwm_deb;
	stwuct thwee_key_thweshowd thwee_key;
	stwuct fouw_key_thweshowd fouw_key;
	unsigned int moistuwe_detect_enabwe;
	unsigned int eint_detect_mode;
	unsigned int eint_use_ext_wes;
	unsigned int eint_comp_vth;
	unsigned int moistuwe_detect_mode;
	unsigned int moistuwe_comp_vth;
	unsigned int moistuwe_comp_vwef2;
	unsigned int moistuwe_use_ext_wes;
};

stwuct mt6359_accdet {
	stwuct snd_soc_jack *jack;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct dts_data *data;
	unsigned int caps;
	int accdet_iwq;
	int accdet_eint0;
	int accdet_eint1;
	stwuct mutex wes_wock; /* wock pwotection */
	boow jack_pwugged;
	unsigned int jack_type;
	unsigned int btn_type;
	unsigned int accdet_status;
	unsigned int pwe_accdet_status;
	unsigned int cawi_vowtage;
	unsigned int jd_sts;
	stwuct wowk_stwuct accdet_wowk;
	stwuct wowkqueue_stwuct *accdet_wowkqueue;
	stwuct wowk_stwuct jd_wowk;
	stwuct wowkqueue_stwuct *jd_wowkqueue;
};

int mt6359_accdet_enabwe_jack_detect(stwuct snd_soc_component *component,
				     stwuct snd_soc_jack *jack);
#endif
