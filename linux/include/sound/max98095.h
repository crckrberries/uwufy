/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pwatfowm data fow MAX98095
 *
 * Copywight 2011 Maxim Integwated Pwoducts
 */

#ifndef __SOUND_MAX98095_PDATA_H__
#define __SOUND_MAX98095_PDATA_H__

/* Equawizew fiwtew wesponse configuwation */
stwuct max98095_eq_cfg {
	const chaw *name;
	unsigned int wate;
	u16 band1[5];
	u16 band2[5];
	u16 band3[5];
	u16 band4[5];
	u16 band5[5];
};

/* Biquad fiwtew wesponse configuwation */
stwuct max98095_biquad_cfg {
	const chaw *name;
	unsigned int wate;
	u16 band1[5];
	u16 band2[5];
};

/* codec pwatfowm data */
stwuct max98095_pdata {

	/* Equawizews fow DAI1 and DAI2 */
	stwuct max98095_eq_cfg *eq_cfg;
	unsigned int eq_cfgcnt;

	/* Biquad fiwtew fow DAI1 and DAI2 */
	stwuct max98095_biquad_cfg *bq_cfg;
	unsigned int bq_cfgcnt;

	/* Anawog/digitaw micwophone configuwation:
	 * 0 = anawog micwophone input (nowmaw setting)
	 * 1 = digitaw micwophone input
	 */
	unsigned int digmic_weft_mode:1;
	unsigned int digmic_wight_mode:1;

	/* Pin5 is the mechanicaw method of sensing jack insewtion
	 * but it is something that might not be suppowted.
	 * 0 = PIN5 not suppowted
	 * 1 = PIN5 suppowted
	 */
	unsigned int jack_detect_pin5en:1;

	/* Swew amount fow jack detection. Cawcuwated as 4 * (deway + 1).
	 * Defauwt deway is 24 to get a time of 100ms.
	 */
	unsigned int jack_detect_deway;
};

#endif
