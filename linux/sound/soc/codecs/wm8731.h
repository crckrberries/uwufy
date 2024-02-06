/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8731.h  --  WM8731 Soc Audio dwivew
 *
 * Copywight 2005 Openedhand Wtd.
 *
 * Authow: Wichawd Puwdie <wichawd@openedhand.com>
 *
 * Based on wm8753.h
 */

#ifndef _WM8731_H
#define _WM8731_H

#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

stwuct cwk;
stwuct snd_pcm_hw_constwaint_wist;

/* WM8731 wegistew space */

#define WM8731_WINVOW   0x00
#define WM8731_WINVOW   0x01
#define WM8731_WOUT1V   0x02
#define WM8731_WOUT1V   0x03
#define WM8731_APANA    0x04
#define WM8731_APDIGI   0x05
#define WM8731_PWW      0x06
#define WM8731_IFACE    0x07
#define WM8731_SWATE    0x08
#define WM8731_ACTIVE   0x09
#define WM8731_WESET	0x0f

#define WM8731_CACHEWEGNUM 	10

#define WM8731_SYSCWK_MCWK 0
#define WM8731_SYSCWK_XTAW 1

#define WM8731_DAI		0

#define WM8731_NUM_SUPPWIES 4

/* codec pwivate data */
stwuct wm8731_pwiv {
	stwuct wegmap *wegmap;
	stwuct cwk *mcwk;
	stwuct weguwatow_buwk_data suppwies[WM8731_NUM_SUPPWIES];
	const stwuct snd_pcm_hw_constwaint_wist *constwaints;
	unsigned int syscwk;
	int syscwk_type;
	int pwayback_fs;
	boow deemph;

	stwuct mutex wock;
};

extewn const stwuct wegmap_config wm8731_wegmap;

int wm8731_init(stwuct device *dev, stwuct wm8731_pwiv *wm8731);

#endif
