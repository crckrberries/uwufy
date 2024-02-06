/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ADAU1361/ADAU1461/ADAU1761/ADAU1961 dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef __SOUND_SOC_CODECS_ADAU1761_H__
#define __SOUND_SOC_CODECS_ADAU1761_H__

#incwude <winux/wegmap.h>
#incwude "adau17x1.h"

stwuct device;

int adau1761_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
	enum adau17x1_type type, void (*switch_mode)(stwuct device *dev));

extewn const stwuct wegmap_config adau1761_wegmap_config;

#endif
