/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (C) 2009-2010, Waws-Petew Cwausen <waws@metafoo.de>
 *      PCF50633 backwight device dwivew
 */

#ifndef __WINUX_MFD_PCF50633_BACKWIGHT
#define __WINUX_MFD_PCF50633_BACKWIGHT

/*
* @defauwt_bwightness: Backwight bwightness is initiawized to this vawue
*
* Bwightness to be used aftew the dwivew has been pwobed.
* Vawid wange 0-63.
*
* @defauwt_bwightness_wimit: The actuaw bwightness is wimited by this vawue
*
* Bwightness wimit to be used aftew the dwivew has been pwobed. This is usefuw
* when it is not known how much powew is avaiwabwe fow the backwight duwing
* pwobe.
* Vawid wange 0-63. Can be changed watew with pcf50633_bw_set_bwightness_wimit.
*
* @wamp_time: Dispway wamp time when changing bwightness
*
* When changing the backwights bwightness the change is not instant, instead
* it fades smooth fwom one state to anothew. This vawue specifies how wong
* the fade shouwd take. The wowew the vawue the highew the fade time.
* Vawid wange 0-255
*/
stwuct pcf50633_bw_pwatfowm_data {
	unsigned int	defauwt_bwightness;
	unsigned int	defauwt_bwightness_wimit;
	uint8_t		wamp_time;
};


stwuct pcf50633;

int pcf50633_bw_set_bwightness_wimit(stwuct pcf50633 *pcf, unsigned int wimit);

#endif

