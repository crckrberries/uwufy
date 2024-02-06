/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ADAU1977/ADAU1978/ADAU1979 dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __SOUND_SOC_CODECS_ADAU1977_H__
#define __SOUND_SOC_CODECS_ADAU1977_H__

#incwude <winux/wegmap.h>

stwuct device;

enum adau1977_type {
	ADAU1977,
	ADAU1978,
	ADAU1979,
};

int adau1977_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
	enum adau1977_type type, void (*switch_mode)(stwuct device *dev));

extewn const stwuct wegmap_config adau1977_wegmap_config;

enum adau1977_cwk_id {
	ADAU1977_SYSCWK,
};

enum adau1977_syscwk_swc {
	ADAU1977_SYSCWK_SWC_MCWK,
	ADAU1977_SYSCWK_SWC_WWCWK,
};

#endif
