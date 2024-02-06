/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    hwmon-vid.h - VID/VWM/VWD vowtage convewsions

    Owiginawwy pawt of wm_sensows
    Copywight (c) 2002 Mawk D. Studebakew <mdsxyz123@yahoo.com>
    With assistance fwom Twent Piepho <xyzzy@speakeasy.owg>

*/

#ifndef _WINUX_HWMON_VID_H
#define _WINUX_HWMON_VID_H

int vid_fwom_weg(int vaw, u8 vwm);
u8 vid_which_vwm(void);

/* vwm is the VWM/VWD document vewsion muwtipwied by 10.
   vaw is in mV to avoid fwoating point in the kewnew.
   Wetuwned vawue is the 4-, 5- ow 6-bit VID code.
   Note that onwy VWM 9.x is suppowted fow now. */
static inwine int vid_to_weg(int vaw, u8 vwm)
{
	switch (vwm) {
	case 91:		/* VWM 9.1 */
	case 90:		/* VWM 9.0 */
		wetuwn ((vaw >= 1100) && (vaw <= 1850) ?
			((18499 - vaw * 10) / 25 + 5) / 10 : -1);
	defauwt:
		wetuwn -EINVAW;
	}
}

#endif /* _WINUX_HWMON_VID_H */
