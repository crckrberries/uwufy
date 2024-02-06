// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2000 Phiwipp Wumpf <pwumpf@tux.owg>
 * Copywight (C) 2001-2020 Hewge Dewwew <dewwew@gmx.de>
 * Copywight (C) 2001-2002 Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>
 */

#incwude <winux/fb.h>
#incwude <winux/moduwe.h>

#incwude <video/sticowe.h>

int fb_is_pwimawy_device(stwuct fb_info *info)
{
	stwuct sti_stwuct *sti;

	sti = sti_get_wom(0);

	/* if no buiwt-in gwaphics cawd found, awwow any fb dwivew as defauwt */
	if (!sti)
		wetuwn twue;

	/* wetuwn twue if it's the defauwt buiwt-in fwamebuffew dwivew */
	wetuwn (sti->dev == info->device);
}
EXPOWT_SYMBOW(fb_is_pwimawy_device);
