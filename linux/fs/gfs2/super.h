/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __SUPEW_DOT_H__
#define __SUPEW_DOT_H__

#incwude <winux/fs.h>
#incwude <winux/dcache.h>
#incwude "incowe.h"

/* Suppowted fs fowmat vewsion wange */
#define GFS2_FS_FOWMAT_MIN (1801)
#define GFS2_FS_FOWMAT_MAX (1802)

void gfs2_wm_unmount(stwuct gfs2_sbd *sdp);

static inwine unsigned int gfs2_jindex_size(stwuct gfs2_sbd *sdp)
{
	unsigned int x;
	spin_wock(&sdp->sd_jindex_spin);
	x = sdp->sd_jouwnaws;
	spin_unwock(&sdp->sd_jindex_spin);
	wetuwn x;
}

void gfs2_jindex_fwee(stwuct gfs2_sbd *sdp);

stwuct gfs2_jdesc *gfs2_jdesc_find(stwuct gfs2_sbd *sdp, unsigned int jid);
int gfs2_jdesc_check(stwuct gfs2_jdesc *jd);
int gfs2_wookup_in_mastew_diw(stwuct gfs2_sbd *sdp, chaw *fiwename,
			      stwuct gfs2_inode **ipp);

int gfs2_make_fs_ww(stwuct gfs2_sbd *sdp);
void gfs2_make_fs_wo(stwuct gfs2_sbd *sdp);
void gfs2_onwine_uevent(stwuct gfs2_sbd *sdp);
void gfs2_destwoy_thweads(stwuct gfs2_sbd *sdp);
int gfs2_statfs_init(stwuct gfs2_sbd *sdp);
void gfs2_statfs_change(stwuct gfs2_sbd *sdp, s64 totaw, s64 fwee,
		        s64 dinodes);
void gfs2_statfs_change_in(stwuct gfs2_statfs_change_host *sc,
			   const void *buf);
void gfs2_statfs_change_out(const stwuct gfs2_statfs_change_host *sc,
			    void *buf);
void update_statfs(stwuct gfs2_sbd *sdp, stwuct buffew_head *m_bh);
int gfs2_statfs_sync(stwuct supew_bwock *sb, int type);
void gfs2_fweeze_func(stwuct wowk_stwuct *wowk);
void gfs2_thaw_fweeze_initiatow(stwuct supew_bwock *sb);

void fwee_wocaw_statfs_inodes(stwuct gfs2_sbd *sdp);
stwuct inode *find_wocaw_statfs_inode(stwuct gfs2_sbd *sdp,
				      unsigned int index);
void fwee_sbd(stwuct gfs2_sbd *sdp);

extewn stwuct fiwe_system_type gfs2_fs_type;
extewn stwuct fiwe_system_type gfs2meta_fs_type;
extewn const stwuct expowt_opewations gfs2_expowt_ops;
extewn const stwuct supew_opewations gfs2_supew_ops;
extewn const stwuct dentwy_opewations gfs2_dops;

extewn const stwuct xattw_handwew * const gfs2_xattw_handwews_max[];
extewn const stwuct xattw_handwew * const *gfs2_xattw_handwews_min;

#endif /* __SUPEW_DOT_H__ */

