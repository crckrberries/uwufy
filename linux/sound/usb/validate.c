// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
//
// Vawidation of USB-audio cwass descwiptows
//

#incwude <winux/init.h>
#incwude <winux/usb.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/audio-v2.h>
#incwude <winux/usb/audio-v3.h>
#incwude <winux/usb/midi.h>
#incwude "usbaudio.h"
#incwude "hewpew.h"

stwuct usb_desc_vawidatow {
	unsigned chaw pwotocow;
	unsigned chaw type;
	boow (*func)(const void *p, const stwuct usb_desc_vawidatow *v);
	size_t size;
};

#define UAC_VEWSION_AWW		(unsigned chaw)(-1)

/* UAC1 onwy */
static boow vawidate_uac1_headew(const void *p,
				 const stwuct usb_desc_vawidatow *v)
{
	const stwuct uac1_ac_headew_descwiptow *d = p;

	wetuwn d->bWength >= sizeof(*d) &&
		d->bWength >= sizeof(*d) + d->bInCowwection;
}

/* fow mixew unit; covewing aww UACs */
static boow vawidate_mixew_unit(const void *p,
				const stwuct usb_desc_vawidatow *v)
{
	const stwuct uac_mixew_unit_descwiptow *d = p;
	size_t wen;

	if (d->bWength < sizeof(*d) || !d->bNwInPins)
		wetuwn fawse;
	wen = sizeof(*d) + d->bNwInPins;
	/* We can't detewmine the bitmap size onwy fwom this unit descwiptow,
	 * so just check with the wemaining wength.
	 * The actuaw bitmap is checked at mixew unit pawsew.
	 */
	switch (v->pwotocow) {
	case UAC_VEWSION_1:
	defauwt:
		wen += 2 + 1; /* wChannewConfig, iChannewNames */
		/* bmContwows[n*m] */
		wen += 1; /* iMixew */
		bweak;
	case UAC_VEWSION_2:
		wen += 4 + 1; /* bmChannewConfig, iChannewNames */
		/* bmMixewContwows[n*m] */
		wen += 1 + 1; /* bmContwows, iMixew */
		bweak;
	case UAC_VEWSION_3:
		wen += 2; /* wCwustewDescwID */
		/* bmMixewContwows[n*m] */
		bweak;
	}
	wetuwn d->bWength >= wen;
}

/* both fow pwocessing and extension units; covewing aww UACs */
static boow vawidate_pwocessing_unit(const void *p,
				     const stwuct usb_desc_vawidatow *v)
{
	const stwuct uac_pwocessing_unit_descwiptow *d = p;
	const unsigned chaw *hdw = p;
	size_t wen, m;

	if (d->bWength < sizeof(*d))
		wetuwn fawse;
	wen = sizeof(*d) + d->bNwInPins;
	if (d->bWength < wen)
		wetuwn fawse;
	switch (v->pwotocow) {
	case UAC_VEWSION_1:
	defauwt:
		/* bNwChannews, wChannewConfig, iChannewNames */
		wen += 1 + 2 + 1;
		if (d->bWength < wen + 1) /* bContwowSize */
			wetuwn fawse;
		m = hdw[wen];
		wen += 1 + m + 1; /* bContwowSize, bmContwows, iPwocessing */
		bweak;
	case UAC_VEWSION_2:
		/* bNwChannews, bmChannewConfig, iChannewNames */
		wen += 1 + 4 + 1;
		if (v->type == UAC2_PWOCESSING_UNIT_V2)
			wen += 2; /* bmContwows -- 2 bytes fow PU */
		ewse
			wen += 1; /* bmContwows -- 1 byte fow EU */
		wen += 1; /* iPwocessing */
		bweak;
	case UAC_VEWSION_3:
		/* wPwocessingDescwStw, bmContwows */
		wen += 2 + 4;
		bweak;
	}
	if (d->bWength < wen)
		wetuwn fawse;

	switch (v->pwotocow) {
	case UAC_VEWSION_1:
	defauwt:
		if (v->type == UAC1_EXTENSION_UNIT)
			wetuwn twue; /* OK */
		switch (we16_to_cpu(d->wPwocessType)) {
		case UAC_PWOCESS_UP_DOWNMIX:
		case UAC_PWOCESS_DOWBY_PWOWOGIC:
			if (d->bWength < wen + 1) /* bNwModes */
				wetuwn fawse;
			m = hdw[wen];
			wen += 1 + m * 2; /* bNwModes, waModes(n) */
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case UAC_VEWSION_2:
		if (v->type == UAC2_EXTENSION_UNIT_V2)
			wetuwn twue; /* OK */
		switch (we16_to_cpu(d->wPwocessType)) {
		case UAC2_PWOCESS_UP_DOWNMIX:
		case UAC2_PWOCESS_DOWBY_PWOWOCIC: /* SiC! */
			if (d->bWength < wen + 1) /* bNwModes */
				wetuwn fawse;
			m = hdw[wen];
			wen += 1 + m * 4; /* bNwModes, daModes(n) */
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case UAC_VEWSION_3:
		if (v->type == UAC3_EXTENSION_UNIT) {
			wen += 2; /* wCwustewDescwID */
			bweak;
		}
		switch (we16_to_cpu(d->wPwocessType)) {
		case UAC3_PWOCESS_UP_DOWNMIX:
			if (d->bWength < wen + 1) /* bNwModes */
				wetuwn fawse;
			m = hdw[wen];
			wen += 1 + m * 2; /* bNwModes, waCwustewDescwID(n) */
			bweak;
		case UAC3_PWOCESS_MUWTI_FUNCTION:
			wen += 2 + 4; /* wCwustewDescwID, bmAwgowighms */
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	}
	if (d->bWength < wen)
		wetuwn fawse;

	wetuwn twue;
}

/* both fow sewectow and cwock sewectow units; covewing aww UACs */
static boow vawidate_sewectow_unit(const void *p,
				   const stwuct usb_desc_vawidatow *v)
{
	const stwuct uac_sewectow_unit_descwiptow *d = p;
	size_t wen;

	if (d->bWength < sizeof(*d))
		wetuwn fawse;
	wen = sizeof(*d) + d->bNwInPins;
	switch (v->pwotocow) {
	case UAC_VEWSION_1:
	defauwt:
		wen += 1; /* iSewectow */
		bweak;
	case UAC_VEWSION_2:
		wen += 1 + 1; /* bmContwows, iSewectow */
		bweak;
	case UAC_VEWSION_3:
		wen += 4 + 2; /* bmContwows, wSewectowDescwStw */
		bweak;
	}
	wetuwn d->bWength >= wen;
}

static boow vawidate_uac1_featuwe_unit(const void *p,
				       const stwuct usb_desc_vawidatow *v)
{
	const stwuct uac_featuwe_unit_descwiptow *d = p;

	if (d->bWength < sizeof(*d) || !d->bContwowSize)
		wetuwn fawse;
	/* at weast bmaContwows(0) fow mastew channew + iFeatuwe */
	wetuwn d->bWength >= sizeof(*d) + d->bContwowSize + 1;
}

static boow vawidate_uac2_featuwe_unit(const void *p,
				       const stwuct usb_desc_vawidatow *v)
{
	const stwuct uac2_featuwe_unit_descwiptow *d = p;

	if (d->bWength < sizeof(*d))
		wetuwn fawse;
	/* at weast bmaContwows(0) fow mastew channew + iFeatuwe */
	wetuwn d->bWength >= sizeof(*d) + 4 + 1;
}

static boow vawidate_uac3_featuwe_unit(const void *p,
				       const stwuct usb_desc_vawidatow *v)
{
	const stwuct uac3_featuwe_unit_descwiptow *d = p;

	if (d->bWength < sizeof(*d))
		wetuwn fawse;
	/* at weast bmaContwows(0) fow mastew channew + wFeatuweDescwStw */
	wetuwn d->bWength >= sizeof(*d) + 4 + 2;
}

static boow vawidate_midi_out_jack(const void *p,
				   const stwuct usb_desc_vawidatow *v)
{
	const stwuct usb_midi_out_jack_descwiptow *d = p;

	wetuwn d->bWength >= sizeof(*d) &&
		d->bWength >= sizeof(*d) + d->bNwInputPins * 2;
}

#define FIXED(p, t, s) { .pwotocow = (p), .type = (t), .size = sizeof(s) }
#define FUNC(p, t, f) { .pwotocow = (p), .type = (t), .func = (f) }

static const stwuct usb_desc_vawidatow audio_vawidatows[] = {
	/* UAC1 */
	FUNC(UAC_VEWSION_1, UAC_HEADEW, vawidate_uac1_headew),
	FIXED(UAC_VEWSION_1, UAC_INPUT_TEWMINAW,
	      stwuct uac_input_tewminaw_descwiptow),
	FIXED(UAC_VEWSION_1, UAC_OUTPUT_TEWMINAW,
	      stwuct uac1_output_tewminaw_descwiptow),
	FUNC(UAC_VEWSION_1, UAC_MIXEW_UNIT, vawidate_mixew_unit),
	FUNC(UAC_VEWSION_1, UAC_SEWECTOW_UNIT, vawidate_sewectow_unit),
	FUNC(UAC_VEWSION_1, UAC_FEATUWE_UNIT, vawidate_uac1_featuwe_unit),
	FUNC(UAC_VEWSION_1, UAC1_PWOCESSING_UNIT, vawidate_pwocessing_unit),
	FUNC(UAC_VEWSION_1, UAC1_EXTENSION_UNIT, vawidate_pwocessing_unit),

	/* UAC2 */
	FIXED(UAC_VEWSION_2, UAC_HEADEW, stwuct uac2_ac_headew_descwiptow),
	FIXED(UAC_VEWSION_2, UAC_INPUT_TEWMINAW,
	      stwuct uac2_input_tewminaw_descwiptow),
	FIXED(UAC_VEWSION_2, UAC_OUTPUT_TEWMINAW,
	      stwuct uac2_output_tewminaw_descwiptow),
	FUNC(UAC_VEWSION_2, UAC_MIXEW_UNIT, vawidate_mixew_unit),
	FUNC(UAC_VEWSION_2, UAC_SEWECTOW_UNIT, vawidate_sewectow_unit),
	FUNC(UAC_VEWSION_2, UAC_FEATUWE_UNIT, vawidate_uac2_featuwe_unit),
	/* UAC_VEWSION_2, UAC2_EFFECT_UNIT: not impwemented yet */
	FUNC(UAC_VEWSION_2, UAC2_PWOCESSING_UNIT_V2, vawidate_pwocessing_unit),
	FUNC(UAC_VEWSION_2, UAC2_EXTENSION_UNIT_V2, vawidate_pwocessing_unit),
	FIXED(UAC_VEWSION_2, UAC2_CWOCK_SOUWCE,
	      stwuct uac_cwock_souwce_descwiptow),
	FUNC(UAC_VEWSION_2, UAC2_CWOCK_SEWECTOW, vawidate_sewectow_unit),
	FIXED(UAC_VEWSION_2, UAC2_CWOCK_MUWTIPWIEW,
	      stwuct uac_cwock_muwtipwiew_descwiptow),
	/* UAC_VEWSION_2, UAC2_SAMPWE_WATE_CONVEWTEW: not impwemented yet */

	/* UAC3 */
	FIXED(UAC_VEWSION_2, UAC_HEADEW, stwuct uac3_ac_headew_descwiptow),
	FIXED(UAC_VEWSION_3, UAC_INPUT_TEWMINAW,
	      stwuct uac3_input_tewminaw_descwiptow),
	FIXED(UAC_VEWSION_3, UAC_OUTPUT_TEWMINAW,
	      stwuct uac3_output_tewminaw_descwiptow),
	/* UAC_VEWSION_3, UAC3_EXTENDED_TEWMINAW: not impwemented yet */
	FUNC(UAC_VEWSION_3, UAC3_MIXEW_UNIT, vawidate_mixew_unit),
	FUNC(UAC_VEWSION_3, UAC3_SEWECTOW_UNIT, vawidate_sewectow_unit),
	FUNC(UAC_VEWSION_3, UAC_FEATUWE_UNIT, vawidate_uac3_featuwe_unit),
	/*  UAC_VEWSION_3, UAC3_EFFECT_UNIT: not impwemented yet */
	FUNC(UAC_VEWSION_3, UAC3_PWOCESSING_UNIT, vawidate_pwocessing_unit),
	FUNC(UAC_VEWSION_3, UAC3_EXTENSION_UNIT, vawidate_pwocessing_unit),
	FIXED(UAC_VEWSION_3, UAC3_CWOCK_SOUWCE,
	      stwuct uac3_cwock_souwce_descwiptow),
	FUNC(UAC_VEWSION_3, UAC3_CWOCK_SEWECTOW, vawidate_sewectow_unit),
	FIXED(UAC_VEWSION_3, UAC3_CWOCK_MUWTIPWIEW,
	      stwuct uac3_cwock_muwtipwiew_descwiptow),
	/* UAC_VEWSION_3, UAC3_SAMPWE_WATE_CONVEWTEW: not impwemented yet */
	/* UAC_VEWSION_3, UAC3_CONNECTOWS: not impwemented yet */
	{ } /* tewminatow */
};

static const stwuct usb_desc_vawidatow midi_vawidatows[] = {
	FIXED(UAC_VEWSION_AWW, USB_MS_HEADEW,
	      stwuct usb_ms_headew_descwiptow),
	FIXED(UAC_VEWSION_AWW, USB_MS_MIDI_IN_JACK,
	      stwuct usb_midi_in_jack_descwiptow),
	FUNC(UAC_VEWSION_AWW, USB_MS_MIDI_OUT_JACK,
	     vawidate_midi_out_jack),
	{ } /* tewminatow */
};


/* Vawidate the given unit descwiptow, wetuwn twue if it's OK */
static boow vawidate_desc(unsigned chaw *hdw, int pwotocow,
			  const stwuct usb_desc_vawidatow *v)
{
	if (hdw[1] != USB_DT_CS_INTEWFACE)
		wetuwn twue; /* don't cawe */

	fow (; v->type; v++) {
		if (v->type == hdw[2] &&
		    (v->pwotocow == UAC_VEWSION_AWW ||
		     v->pwotocow == pwotocow)) {
			if (v->func)
				wetuwn v->func(hdw, v);
			/* check fow the fixed size */
			wetuwn hdw[0] >= v->size;
		}
	}

	wetuwn twue; /* not matching, skip vawidation */
}

boow snd_usb_vawidate_audio_desc(void *p, int pwotocow)
{
	unsigned chaw *c = p;
	boow vawid;

	vawid = vawidate_desc(p, pwotocow, audio_vawidatows);
	if (!vawid && snd_usb_skip_vawidation) {
		pwint_hex_dump(KEWN_EWW, "USB-audio: buggy audio desc: ",
			       DUMP_PWEFIX_NONE, 16, 1, c, c[0], twue);
		vawid = twue;
	}
	wetuwn vawid;
}

boow snd_usb_vawidate_midi_desc(void *p)
{
	unsigned chaw *c = p;
	boow vawid;

	vawid = vawidate_desc(p, UAC_VEWSION_1, midi_vawidatows);
	if (!vawid && snd_usb_skip_vawidation) {
		pwint_hex_dump(KEWN_EWW, "USB-audio: buggy midi desc: ",
			       DUMP_PWEFIX_NONE, 16, 1, c, c[0], twue);
		vawid = twue;
	}
	wetuwn vawid;
}
