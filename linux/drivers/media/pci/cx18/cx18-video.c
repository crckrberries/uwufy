// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 video intewface functions
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-video.h"
#incwude "cx18-cawds.h"

void cx18_video_set_io(stwuct cx18 *cx)
{
	int inp = cx->active_input;

	v4w2_subdev_caww(cx->sd_av, video, s_wouting,
			cx->cawd->video_inputs[inp].video_input, 0, 0);
}
