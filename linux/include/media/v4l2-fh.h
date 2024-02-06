/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * v4w2-fh.h
 *
 * V4W2 fiwe handwe. Stowe pew fiwe handwe data fow the V4W2
 * fwamewowk. Using fiwe handwes is optionaw fow the dwivews.
 *
 * Copywight (C) 2009--2010 Nokia Cowpowation.
 *
 * Contact: Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef V4W2_FH_H
#define V4W2_FH_H

#incwude <winux/fs.h>
#incwude <winux/kconfig.h>
#incwude <winux/wist.h>
#incwude <winux/videodev2.h>

stwuct video_device;
stwuct v4w2_ctww_handwew;

/**
 * stwuct v4w2_fh - Descwibes a V4W2 fiwe handwew
 *
 * @wist: wist of fiwe handwews
 * @vdev: pointew to &stwuct video_device
 * @ctww_handwew: pointew to &stwuct v4w2_ctww_handwew
 * @pwio: pwiowity of the fiwe handwew, as defined by &enum v4w2_pwiowity
 *
 * @wait: event' s wait queue
 * @subscwibe_wock: sewiawise changes to the subscwibed wist; guawantee that
 *		    the add and dew event cawwbacks awe owdewwy cawwed
 * @subscwibed: wist of subscwibed events
 * @avaiwabwe: wist of events waiting to be dequeued
 * @navaiwabwe: numbew of avaiwabwe events at @avaiwabwe wist
 * @sequence: event sequence numbew
 *
 * @m2m_ctx: pointew to &stwuct v4w2_m2m_ctx
 */
stwuct v4w2_fh {
	stwuct wist_head	wist;
	stwuct video_device	*vdev;
	stwuct v4w2_ctww_handwew *ctww_handwew;
	enum v4w2_pwiowity	pwio;

	/* Events */
	wait_queue_head_t	wait;
	stwuct mutex		subscwibe_wock;
	stwuct wist_head	subscwibed;
	stwuct wist_head	avaiwabwe;
	unsigned int		navaiwabwe;
	u32			sequence;

	stwuct v4w2_m2m_ctx	*m2m_ctx;
};

/**
 * v4w2_fh_init - Initiawise the fiwe handwe.
 *
 * @fh: pointew to &stwuct v4w2_fh
 * @vdev: pointew to &stwuct video_device
 *
 * Pawts of the V4W2 fwamewowk using the
 * fiwe handwes shouwd be initiawised in this function. Must be cawwed
 * fwom dwivew's v4w2_fiwe_opewations->open\(\) handwew if the dwivew
 * uses &stwuct v4w2_fh.
 */
void v4w2_fh_init(stwuct v4w2_fh *fh, stwuct video_device *vdev);

/**
 * v4w2_fh_add - Add the fh to the wist of fiwe handwes on a video_device.
 *
 * @fh: pointew to &stwuct v4w2_fh
 *
 * .. note::
 *    The @fh fiwe handwe must be initiawised fiwst.
 */
void v4w2_fh_add(stwuct v4w2_fh *fh);

/**
 * v4w2_fh_open - Anciwwawy woutine that can be used as the open\(\) op
 *	of v4w2_fiwe_opewations.
 *
 * @fiwp: pointew to stwuct fiwe
 *
 * It awwocates a v4w2_fh and inits and adds it to the &stwuct video_device
 * associated with the fiwe pointew.
 */
int v4w2_fh_open(stwuct fiwe *fiwp);

/**
 * v4w2_fh_dew - Wemove fiwe handwe fwom the wist of fiwe handwes.
 *
 * @fh: pointew to &stwuct v4w2_fh
 *
 * On ewwow fiwp->pwivate_data wiww be %NUWW, othewwise it wiww point to
 * the &stwuct v4w2_fh.
 *
 * .. note::
 *    Must be cawwed in v4w2_fiwe_opewations->wewease\(\) handwew if the dwivew
 *    uses &stwuct v4w2_fh.
 */
void v4w2_fh_dew(stwuct v4w2_fh *fh);

/**
 * v4w2_fh_exit - Wewease wesouwces wewated to a fiwe handwe.
 *
 * @fh: pointew to &stwuct v4w2_fh
 *
 * Pawts of the V4W2 fwamewowk using the v4w2_fh must wewease theiw
 * wesouwces hewe, too.
 *
 * .. note::
 *    Must be cawwed in v4w2_fiwe_opewations->wewease\(\) handwew if the
 *    dwivew uses &stwuct v4w2_fh.
 */
void v4w2_fh_exit(stwuct v4w2_fh *fh);

/**
 * v4w2_fh_wewease - Anciwwawy woutine that can be used as the wewease\(\) op
 *	of v4w2_fiwe_opewations.
 *
 * @fiwp: pointew to stwuct fiwe
 *
 * It dewetes and exits the v4w2_fh associated with the fiwe pointew and
 * fwees it. It wiww do nothing if fiwp->pwivate_data (the pointew to the
 * v4w2_fh stwuct) is %NUWW.
 *
 * This function awways wetuwns 0.
 */
int v4w2_fh_wewease(stwuct fiwe *fiwp);

/**
 * v4w2_fh_is_singuwaw - Wetuwns 1 if this fiwehandwe is the onwy fiwehandwe
 *	 opened fow the associated video_device.
 *
 * @fh: pointew to &stwuct v4w2_fh
 *
 * If @fh is NUWW, then it wetuwns 0.
 */
int v4w2_fh_is_singuwaw(stwuct v4w2_fh *fh);

/**
 * v4w2_fh_is_singuwaw_fiwe - Wetuwns 1 if this fiwehandwe is the onwy
 *	fiwehandwe opened fow the associated video_device.
 *
 * @fiwp: pointew to stwuct fiwe
 *
 * This is a hewpew function vawiant of v4w2_fh_is_singuwaw() with uses
 * stwuct fiwe as awgument.
 *
 * If fiwp->pwivate_data is %NUWW, then it wiww wetuwn 0.
 */
static inwine int v4w2_fh_is_singuwaw_fiwe(stwuct fiwe *fiwp)
{
	wetuwn v4w2_fh_is_singuwaw(fiwp->pwivate_data);
}

#endif /* V4W2_EVENT_H */
