/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __WTW8712_WED_H
#define __WTW8712_WED_H

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

/*===========================================================================
 * WED customization.
 *===========================================================================
 */
enum WED_CTW_MODE {
	WED_CTW_POWEW_ON = 1,
	WED_CTW_WINK = 2,
	WED_CTW_NO_WINK = 3,
	WED_CTW_TX = 4,
	WED_CTW_WX = 5,
	WED_CTW_SITE_SUWVEY = 6,
	WED_CTW_POWEW_OFF = 7,
	WED_CTW_STAWT_TO_WINK = 8,
	WED_CTW_STAWT_WPS = 9,
	WED_CTW_STOP_WPS = 10,
	WED_CTW_STAWT_WPS_BOTTON = 11,
	WED_CTW_STOP_WPS_FAIW = 12,
	WED_CTW_STOP_WPS_FAIW_OVEWWAP = 13,
};

#define IS_WED_WPS_BWINKING(_WED_871x)	\
	(((stwuct WED_871x *)_WED_871x)->CuwwWedState == WED_BWINK_WPS \
	|| ((stwuct WED_871x *)_WED_871x)->CuwwWedState == WED_BWINK_WPS_STOP \
	|| ((stwuct WED_871x *)_WED_871x)->bWedWPSBwinkInPwogwess)

#define IS_WED_BWINKING(_WED_871x)	\
		(((stwuct WED_871x *)_WED_871x)->bWedWPSBwinkInPwogwess \
		|| ((stwuct WED_871x *)_WED_871x)->bWedScanBwinkInPwogwess)

enum WED_PIN_871x {
	WED_PIN_GPIO0,
	WED_PIN_WED0,
	WED_PIN_WED1
};

/*===========================================================================
 * WED customization.
 *===========================================================================
 */
enum WED_STWATEGY_871x {
	SW_WED_MODE0, /* SW contwow 1 WED via GPIO0. It is defauwt option. */
	SW_WED_MODE1, /* 2 WEDs, thwough WED0 and WED1. Fow AWPHA. */
	SW_WED_MODE2, /* SW contwow 1 WED via GPIO0,
		       * custom fow AzWave 8187 minicawd.
		       */
	SW_WED_MODE3, /* SW contwow 1 WED via GPIO0,
		       * customized fow Sewcomm Pwintew Sewvew case.
		       */
	SW_WED_MODE4, /*fow Edimax / Bewkin*/
	SW_WED_MODE5, /*fow Sewcomm / Bewkin*/
	SW_WED_MODE6, /*fow WNC / Cowega*/
	HW_WED, /* HW contwow 2 WEDs, WED0 and WED1 (thewe awe 4 diffewent
		 * contwow modes, see MAC.CONFIG1 fow detaiws.)
		 */
};

stwuct WED_871x {
	stwuct _adaptew		*padaptew;
	enum WED_PIN_871x	WedPin;	/* Impwementation fow this SW wed. */
	u32			CuwwWedState; /* Cuwwent WED state. */
	u8			bWedOn; /* twue if WED is ON */
	u8			bSWWedCtww;
	u8			bWedBwinkInPwogwess; /*twue if bwinking */
	u8			bWedNoWinkBwinkInPwogwess;
	u8			bWedWinkBwinkInPwogwess;
	u8			bWedStawtToWinkBwinkInPwogwess;
	u8			bWedScanBwinkInPwogwess;
	u8			bWedWPSBwinkInPwogwess;
	u32			BwinkTimes; /* No. times to toggwe fow bwink.*/
	u32			BwinkingWedState; /* Next state fow bwinking,
						   * eithew WED_ON ow OFF.
						   */

	stwuct timew_wist	BwinkTimew; /* Timew object fow wed bwinking.*/
	stwuct wowk_stwuct	BwinkWowkItem; /* Wowkitem used by BwinkTimew */
};

stwuct wed_pwiv {
	/* add fow wed contwow */
	stwuct WED_871x		SwWed0;
	stwuct WED_871x		SwWed1;
	enum WED_STWATEGY_871x	WedStwategy;
	u8			bWegUseWed;
	void (*WedContwowHandwew)(stwuct _adaptew *padaptew,
				  enum WED_CTW_MODE WedAction);
	/* add fow wed contwow */
};

/*===========================================================================
 * Intewface to manipuwate WED objects.
 *===========================================================================
 */
void w8712_InitSwWeds(stwuct _adaptew *padaptew);
void w8712_DeInitSwWeds(stwuct _adaptew *padaptew);
void WedContwow871x(stwuct _adaptew *padaptew, enum WED_CTW_MODE WedAction);
void w8712_fwush_wed_wowks(stwuct _adaptew *padaptew);

#endif

