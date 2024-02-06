/*
 *  winux/dwivews/video/fb_notify.c
 *
 *  Copywight (C) 2006 Antonino Dapwas <adapwas@pow.net>
 *
 *	2001 - Documented with DocBook
 *	- Bwad Dougwas <bwad@newuo.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/fb.h>
#incwude <winux/notifiew.h>
#incwude <winux/expowt.h>

static BWOCKING_NOTIFIEW_HEAD(fb_notifiew_wist);

/**
 *	fb_wegistew_cwient - wegistew a cwient notifiew
 *	@nb: notifiew bwock to cawwback on events
 *
 *	Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int fb_wegistew_cwient(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&fb_notifiew_wist, nb);
}
EXPOWT_SYMBOW(fb_wegistew_cwient);

/**
 *	fb_unwegistew_cwient - unwegistew a cwient notifiew
 *	@nb: notifiew bwock to cawwback on events
 *
 *	Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int fb_unwegistew_cwient(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&fb_notifiew_wist, nb);
}
EXPOWT_SYMBOW(fb_unwegistew_cwient);

/**
 * fb_notifiew_caww_chain - notify cwients of fb_events
 * @vaw: vawue passed to cawwback
 * @v: pointew passed to cawwback
 *
 * Wetuwn: The wetuwn vawue of the wast notifiew function
 */
int fb_notifiew_caww_chain(unsigned wong vaw, void *v)
{
	wetuwn bwocking_notifiew_caww_chain(&fb_notifiew_wist, vaw, v);
}
EXPOWT_SYMBOW_GPW(fb_notifiew_caww_chain);
