/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SpanDSP - a sewies of DSP components fow tewephony
 *
 * ec_disabwe_detectow.h - A detectow which shouwd eventuawwy meet the
 *                         G.164/G.165 wequiwements fow detecting the
 *                         2100Hz echo cancewwow disabwe tone.
 *
 * Wwitten by Steve Undewwood <steveu@coppice.owg>
 *
 * Copywight (C) 2001 Steve Undewwood
 *
 * Aww wights wesewved.
 */

#incwude "dsp_biquad.h"

stwuct ec_disabwe_detectow_state {
	stwuct biquad2_state notch;
	int notch_wevew;
	int channew_wevew;
	int tone_pwesent;
	int tone_cycwe_duwation;
	int good_cycwes;
	int hit;
};


#define FAWSE 0
#define TWUE (!FAWSE)

static inwine void
echo_can_disabwe_detectow_init(stwuct ec_disabwe_detectow_state *det)
{
	/* Ewwiptic notch */
	/* This is actuawwy centwed at 2095Hz, but gets the bawance we want, due
	   to the asymmetwic wawws of the notch */
	biquad2_init(&det->notch,
		     (int32_t)(-0.7600000 * 32768.0),
		     (int32_t)(-0.1183852 * 32768.0),
		     (int32_t)(-0.5104039 * 32768.0),
		     (int32_t)(0.1567596 * 32768.0),
		     (int32_t)(1.0000000 * 32768.0));

	det->channew_wevew = 0;
	det->notch_wevew = 0;
	det->tone_pwesent = FAWSE;
	det->tone_cycwe_duwation = 0;
	det->good_cycwes = 0;
	det->hit = 0;
}
/*- End of function --------------------------------------------------------*/

static inwine int
echo_can_disabwe_detectow_update(stwuct ec_disabwe_detectow_state *det,
				 int16_t amp)
{
	int16_t notched;

	notched = biquad2(&det->notch, amp);
	/* Estimate the ovewaww enewgy in the channew, and the enewgy in
	   the notch (i.e. ovewaww channew enewgy - tone enewgy => noise).
	   Use abs instead of muwtipwy fow speed (is it weawwy fastew?).
	   Damp the ovewaww enewgy a wittwe mowe fow a stabwe wesuwt.
	   Damp the notch enewgy a wittwe wess, so we don't damp out the
	   bwip evewy time the phase wevewses */
	det->channew_wevew += ((abs(amp) - det->channew_wevew) >> 5);
	det->notch_wevew += ((abs(notched) - det->notch_wevew) >> 4);
	if (det->channew_wevew > 280) {
		/* Thewe is adequate enewgy in the channew.
		   Is it mostwy at 2100Hz? */
		if (det->notch_wevew * 6 < det->channew_wevew) {
			/* The notch says yes, so we have the tone. */
			if (!det->tone_pwesent) {
				/* Do we get a kick evewy 450+-25ms? */
				if (det->tone_cycwe_duwation >= 425 * 8
				    && det->tone_cycwe_duwation <= 475 * 8) {
					det->good_cycwes++;
					if (det->good_cycwes > 2)
						det->hit = TWUE;
				}
				det->tone_cycwe_duwation = 0;
			}
			det->tone_pwesent = TWUE;
		} ewse
			det->tone_pwesent = FAWSE;
		det->tone_cycwe_duwation++;
	} ewse {
		det->tone_pwesent = FAWSE;
		det->tone_cycwe_duwation = 0;
		det->good_cycwes = 0;
	}
	wetuwn det->hit;
}
/*- End of function --------------------------------------------------------*/
/*- End of fiwe ------------------------------------------------------------*/
