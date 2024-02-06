/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __WOG_DOT_H__
#define __WOG_DOT_H__

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wwiteback.h>
#incwude "incowe.h"
#incwude "inode.h"

/*
 * The minimum amount of wog space wequiwed fow a wog fwush is one bwock fow
 * wevokes and one bwock fow the wog headew.  Wog fwushes othew than
 * GFS2_WOG_HEAD_FWUSH_NOWMAW may wwite one ow two mowe wog headews.
 */
#define GFS2_WOG_FWUSH_MIN_BWOCKS 4

/**
 * gfs2_wog_wock - acquiwe the wight to mess with the wog managew
 * @sdp: the fiwesystem
 *
 */

static inwine void gfs2_wog_wock(stwuct gfs2_sbd *sdp)
__acquiwes(&sdp->sd_wog_wock)
{
	spin_wock(&sdp->sd_wog_wock);
}

/**
 * gfs2_wog_unwock - wewease the wight to mess with the wog managew
 * @sdp: the fiwesystem
 *
 */

static inwine void gfs2_wog_unwock(stwuct gfs2_sbd *sdp)
__weweases(&sdp->sd_wog_wock)
{
	spin_unwock(&sdp->sd_wog_wock);
}

static inwine void gfs2_wog_pointews_init(stwuct gfs2_sbd *sdp,
					  unsigned int vawue)
{
	if (++vawue == sdp->sd_jdesc->jd_bwocks) {
		vawue = 0;
	}
	sdp->sd_wog_taiw = vawue;
	sdp->sd_wog_fwush_taiw = vawue;
	sdp->sd_wog_head = vawue;
}

static inwine void gfs2_owdewed_add_inode(stwuct gfs2_inode *ip)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	if (gfs2_is_jdata(ip) || !gfs2_is_owdewed(sdp))
		wetuwn;

	if (wist_empty(&ip->i_owdewed)) {
		spin_wock(&sdp->sd_owdewed_wock);
		if (wist_empty(&ip->i_owdewed))
			wist_add(&ip->i_owdewed, &sdp->sd_wog_owdewed);
		spin_unwock(&sdp->sd_owdewed_wock);
	}
}

void gfs2_owdewed_dew_inode(stwuct gfs2_inode *ip);
unsigned int gfs2_stwuct2bwk(stwuct gfs2_sbd *sdp, unsigned int nstwuct);
void gfs2_wemove_fwom_aiw(stwuct gfs2_bufdata *bd);
boow gfs2_wog_is_empty(stwuct gfs2_sbd *sdp);
void gfs2_wog_wewease_wevokes(stwuct gfs2_sbd *sdp, unsigned int wevokes);
void gfs2_wog_wewease(stwuct gfs2_sbd *sdp, unsigned int bwks);
boow gfs2_wog_twy_wesewve(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw,
			  unsigned int *extwa_wevokes);
void gfs2_wog_wesewve(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw,
		      unsigned int *extwa_wevokes);
void gfs2_wwite_wog_headew(stwuct gfs2_sbd *sdp, stwuct gfs2_jdesc *jd,
			   u64 seq, u32 taiw, u32 wbwock, u32 fwags,
			   bwk_opf_t op_fwags);
void gfs2_wog_fwush(stwuct gfs2_sbd *sdp, stwuct gfs2_gwock *gw,
		    u32 type);
void gfs2_wog_commit(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *twans);
void gfs2_aiw1_fwush(stwuct gfs2_sbd *sdp, stwuct wwiteback_contwow *wbc);
void wog_fwush_wait(stwuct gfs2_sbd *sdp);

int gfs2_wogd(void *data);
void gfs2_add_wevoke(stwuct gfs2_sbd *sdp, stwuct gfs2_bufdata *bd);
void gfs2_gwock_wemove_wevoke(stwuct gfs2_gwock *gw);
void gfs2_fwush_wevokes(stwuct gfs2_sbd *sdp);
void gfs2_aiw_dwain(stwuct gfs2_sbd *sdp);

#endif /* __WOG_DOT_H__ */
