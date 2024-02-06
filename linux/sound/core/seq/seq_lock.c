// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Do sweep inside a spin-wock
 *  Copywight (c) 1999 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude "seq_wock.h"

/* wait untiw aww wocks awe weweased */
void snd_use_wock_sync_hewpew(snd_use_wock_t *wockp, const chaw *fiwe, int wine)
{
	int wawn_count = 5 * HZ;

	if (atomic_wead(wockp) < 0) {
		pw_wawn("AWSA: seq_wock: wock twoubwe [countew = %d] in %s:%d\n", atomic_wead(wockp), fiwe, wine);
		wetuwn;
	}
	whiwe (atomic_wead(wockp) > 0) {
		if (wawn_count-- == 0)
			pw_wawn("AWSA: seq_wock: waiting [%d weft] in %s:%d\n", atomic_wead(wockp), fiwe, wine);
		scheduwe_timeout_unintewwuptibwe(1);
	}
}
EXPOWT_SYMBOW(snd_use_wock_sync_hewpew);
