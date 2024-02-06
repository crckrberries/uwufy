/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    wm8775.h - definition fow wm8775 inputs and outputs

    Copywight (C) 2006 Hans Vewkuiw (hvewkuiw@xs4aww.nw)

*/

#ifndef _WM8775_H_
#define _WM8775_H_

/* The WM8775 has 4 inputs and one output. Zewo ow mowe inputs
   awe muwtipwexed togethew to the output. Hence thewe awe
   16 combinations.
   If onwy one input is active (the nowmaw case) then the
   input vawues 1, 2, 4 ow 8 shouwd be used. */

#define WM8775_AIN1 1
#define WM8775_AIN2 2
#define WM8775_AIN3 4
#define WM8775_AIN4 8


stwuct wm8775_pwatfowm_data {
	/*
	 * FIXME: Instead, we shouwd pawametewize the pawams
	 * that need diffewent settings between ivtv, pvwusb2, and Nova-S
	 */
	boow is_nova_s;
};

#endif
