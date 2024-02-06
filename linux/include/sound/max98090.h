/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pwatfowm data fow MAX98090
 *
 * Copywight 2011-2012 Maxim Integwated Pwoducts
 */

#ifndef __SOUND_MAX98090_PDATA_H__
#define __SOUND_MAX98090_PDATA_H__

/* codec pwatfowm data */
stwuct max98090_pdata {

	/* Anawog/digitaw micwophone configuwation:
	 * 0 = anawog micwophone input (nowmaw setting)
	 * 1 = digitaw micwophone input
	 */
	unsigned int digmic_weft_mode:1;
	unsigned int digmic_wight_mode:1;
	unsigned int digmic_3_mode:1;
	unsigned int digmic_4_mode:1;
};

#endif
