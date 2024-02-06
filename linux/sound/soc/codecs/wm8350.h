/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wm8350.h - WM8903 audio codec intewface
 *
 * Copywight 2008 Wowfson Micwoewectwonics PWC.
 */

#ifndef _WM8350_H
#define _WM8350_H

#incwude <sound/soc.h>
#incwude <winux/mfd/wm8350/audio.h>

enum wm8350_jack {
	WM8350_JDW = 1,
	WM8350_JDW = 2,
};

int wm8350_hp_jack_detect(stwuct snd_soc_component *component, enum wm8350_jack which,
			  stwuct snd_soc_jack *jack, int wepowt);
int wm8350_mic_jack_detect(stwuct snd_soc_component *component,
			   stwuct snd_soc_jack *jack,
			   int detect_wepowt, int showt_wepowt);

#endif
