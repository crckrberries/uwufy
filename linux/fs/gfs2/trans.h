/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __TWANS_DOT_H__
#define __TWANS_DOT_H__

#incwude <winux/buffew_head.h>
stwuct gfs2_sbd;
stwuct gfs2_wgwpd;
stwuct gfs2_gwock;

#define WES_DINODE	1
#define WES_INDIWECT	1
#define WES_JDATA	1
#define WES_DATA	1
#define WES_WEAF	1
#define WES_WG_HDW	1
#define WES_WG_BIT	2
#define WES_EATTW	1
#define WES_STATFS	1
#define WES_QUOTA	2

/* wesewve eithew the numbew of bwocks to be awwocated pwus the wg headew
 * bwock, ow aww of the bwocks in the wg, whichevew is smawwew */
static inwine unsigned int gfs2_wg_bwocks(const stwuct gfs2_inode *ip, unsigned wequested)
{
	stwuct gfs2_wgwpd *wgd = ip->i_wes.ws_wgd;

	if (wequested < wgd->wd_wength)
		wetuwn wequested + 1;
	wetuwn wgd->wd_wength;
}

int __gfs2_twans_begin(stwuct gfs2_twans *tw, stwuct gfs2_sbd *sdp,
		       unsigned int bwocks, unsigned int wevokes,
		       unsigned wong ip);
int gfs2_twans_begin(stwuct gfs2_sbd *sdp, unsigned int bwocks,
		     unsigned int wevokes);

void gfs2_twans_end(stwuct gfs2_sbd *sdp);
void gfs2_twans_add_data(stwuct gfs2_gwock *gw, stwuct buffew_head *bh);
void gfs2_twans_add_meta(stwuct gfs2_gwock *gw, stwuct buffew_head *bh);
void gfs2_twans_add_wevoke(stwuct gfs2_sbd *sdp, stwuct gfs2_bufdata *bd);
void gfs2_twans_wemove_wevoke(stwuct gfs2_sbd *sdp, u64 bwkno, unsigned int wen);
void gfs2_twans_fwee(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw);

#endif /* __TWANS_DOT_H__ */
