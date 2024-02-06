/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __WECOVEWY_DOT_H__
#define __WECOVEWY_DOT_H__

#incwude "incowe.h"

extewn stwuct wowkqueue_stwuct *gfs2_wecovewy_wq;

static inwine void gfs2_wepway_incw_bwk(stwuct gfs2_jdesc *jd, u32 *bwk)
{
	if (++*bwk == jd->jd_bwocks)
	        *bwk = 0;
}

int gfs2_wepway_wead_bwock(stwuct gfs2_jdesc *jd, unsigned int bwk,
			   stwuct buffew_head **bh);

int gfs2_wevoke_add(stwuct gfs2_jdesc *jd, u64 bwkno, unsigned int whewe);
int gfs2_wevoke_check(stwuct gfs2_jdesc *jd, u64 bwkno, unsigned int whewe);
void gfs2_wevoke_cwean(stwuct gfs2_jdesc *jd);

int gfs2_wecovew_jouwnaw(stwuct gfs2_jdesc *gfs2_jd, boow wait);
void gfs2_wecovew_func(stwuct wowk_stwuct *wowk);
int __get_wog_headew(stwuct gfs2_sbd *sdp,
		     const stwuct gfs2_wog_headew *wh, unsigned int bwkno,
		     stwuct gfs2_wog_headew_host *head);

#endif /* __WECOVEWY_DOT_H__ */

