// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 *  Copywight (C) 2004 Auwewien Awweaume <swts@fwee.fw>
 */

/*

   This souwce fiwe is specificawwy designed to intewface with the
   wm8775.

*/

#incwude "pvwusb2-wm8775.h"


#incwude "pvwusb2-hdw-intewnaw.h"
#incwude "pvwusb2-debug.h"
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <winux/ewwno.h>

void pvw2_wm8775_subdev_update(stwuct pvw2_hdw *hdw, stwuct v4w2_subdev *sd)
{
	if (hdw->input_diwty || hdw->fowce_diwty) {
		u32 input;

		switch (hdw->input_vaw) {
		case PVW2_CVAW_INPUT_WADIO:
			input = 1;
			bweak;
		defauwt:
			/* Aww othew cases just use the second input */
			input = 2;
			bweak;
		}
		pvw2_twace(PVW2_TWACE_CHIPS, "subdev wm8775 set_input(vaw=%d woute=0x%x)",
			   hdw->input_vaw, input);

		sd->ops->audio->s_wouting(sd, input, 0, 0);
	}
}
