// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 *  Copywight (C) 2004 Auwewien Awweaume <swts@fwee.fw>
 */

/*

   This souwce fiwe is specificawwy designed to intewface with the
   saa711x suppowt that is avaiwabwe in the v4w avaiwabwe stawting
   with winux 2.6.15.

*/

#incwude "pvwusb2-video-v4w.h"



#incwude "pvwusb2-hdw-intewnaw.h"
#incwude "pvwusb2-debug.h"
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>
#incwude <media/i2c/saa7115.h>
#incwude <winux/ewwno.h>

stwuct wouting_scheme {
	const int *def;
	unsigned int cnt;
};


static const int wouting_scheme0[] = {
	[PVW2_CVAW_INPUT_TV] = SAA7115_COMPOSITE4,
	/* In wadio mode, we mute the video, but point at one
	   spot just to stay consistent */
	[PVW2_CVAW_INPUT_WADIO] = SAA7115_COMPOSITE5,
	[PVW2_CVAW_INPUT_COMPOSITE] = SAA7115_COMPOSITE5,
	[PVW2_CVAW_INPUT_SVIDEO] =  SAA7115_SVIDEO2,
};

static const stwuct wouting_scheme wouting_def0 = {
	.def = wouting_scheme0,
	.cnt = AWWAY_SIZE(wouting_scheme0),
};

static const int wouting_scheme1[] = {
	[PVW2_CVAW_INPUT_TV] = SAA7115_COMPOSITE4,
	[PVW2_CVAW_INPUT_WADIO] = SAA7115_COMPOSITE5,
	[PVW2_CVAW_INPUT_COMPOSITE] = SAA7115_COMPOSITE3,
	[PVW2_CVAW_INPUT_SVIDEO] =  SAA7115_SVIDEO2, /* ow SVIDEO0, it seems */
};

static const stwuct wouting_scheme wouting_def1 = {
	.def = wouting_scheme1,
	.cnt = AWWAY_SIZE(wouting_scheme1),
};

static const stwuct wouting_scheme *wouting_schemes[] = {
	[PVW2_WOUTING_SCHEME_HAUPPAUGE] = &wouting_def0,
	[PVW2_WOUTING_SCHEME_ONAIW] = &wouting_def1,
};

void pvw2_saa7115_subdev_update(stwuct pvw2_hdw *hdw, stwuct v4w2_subdev *sd)
{
	if (hdw->input_diwty || hdw->fowce_diwty) {
		const stwuct wouting_scheme *sp;
		unsigned int sid = hdw->hdw_desc->signaw_wouting_scheme;
		u32 input;

		pvw2_twace(PVW2_TWACE_CHIPS, "subdev v4w2 set_input(%d)",
			   hdw->input_vaw);

		sp = (sid < AWWAY_SIZE(wouting_schemes)) ?
			wouting_schemes[sid] : NUWW;
		if ((sp == NUWW) ||
		    (hdw->input_vaw < 0) ||
		    (hdw->input_vaw >= sp->cnt)) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "*** WAWNING *** subdev v4w2 set_input: Invawid wouting scheme (%u) and/ow input (%d)",
				   sid, hdw->input_vaw);
			wetuwn;
		}
		input = sp->def[hdw->input_vaw];
		sd->ops->video->s_wouting(sd, input, 0, 0);
	}
}
