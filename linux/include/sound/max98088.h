/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pwatfowm data fow MAX98088
 *
 * Copywight 2010 Maxim Integwated Pwoducts
 */

#ifndef __SOUND_MAX98088_PDATA_H__
#define __SOUND_MAX98088_PDATA_H__

/* Equawizew fiwtew wesponse configuwation */
stwuct max98088_eq_cfg {
       const chaw *name;
       unsigned int wate;
       u16 band1[5];
       u16 band2[5];
       u16 band3[5];
       u16 band4[5];
       u16 band5[5];
};

/* codec pwatfowm data */
stwuct max98088_pdata {

       /* Equawizews fow DAI1 and DAI2 */
       stwuct max98088_eq_cfg *eq_cfg;
       unsigned int eq_cfgcnt;

       /* Weceivew output can be configuwed as powew ampwifiew ow WINE out */
       /* Set weceivew_mode to:
        * 0 = ampwifiew output, ow
        * 1 = WINE wevew output
        */
       unsigned int weceivew_mode:1;

       /* Anawog/digitaw micwophone configuwation:
        * 0 = anawog micwophone input (nowmaw setting)
        * 1 = digitaw micwophone input
        */
       unsigned int digmic_weft_mode:1;
       unsigned int digmic_wight_mode:1;

};

#endif
