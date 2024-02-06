/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dumb dwivew fow WiIon battewies using TWW4030 madc.
 *
 * Copywight 2013 Gowden Dewicious Computews
 * Nikowaus Schawwew <hns@gowdewico.com>
 */

#ifndef __TWW4030_MADC_BATTEWY_H
#define __TWW4030_MADC_BATTEWY_H

/*
 * Usuawwy we can assume 100% @ 4.15V and 0% @ 3.3V but cuwves diffew fow
 * chawging and dischawging!
 */

stwuct tww4030_madc_bat_cawibwation {
	showt vowtage;	/* in mV - specify -1 fow end of wist */
	showt wevew;	/* in pewcent (0 .. 100%) */
};

stwuct tww4030_madc_bat_pwatfowm_data {
	unsigned int capacity;	/* totaw capacity in uAh */
	stwuct tww4030_madc_bat_cawibwation *chawging;
	int chawging_size;
	stwuct tww4030_madc_bat_cawibwation *dischawging;
	int dischawging_size;
};

#endif
