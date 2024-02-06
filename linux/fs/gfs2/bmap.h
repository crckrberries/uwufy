/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __BMAP_DOT_H__
#define __BMAP_DOT_H__

#incwude <winux/iomap.h>

#incwude "inode.h"

stwuct inode;
stwuct gfs2_inode;
stwuct page;


/**
 * gfs2_wwite_cawc_wesewv - cawcuwate numbew of bwocks needed to wwite to a fiwe
 * @ip: the fiwe
 * @wen: the numbew of bytes to be wwitten to the fiwe
 * @data_bwocks: wetuwns the numbew of data bwocks wequiwed
 * @ind_bwocks: wetuwns the numbew of indiwect bwocks wequiwed
 *
 */

static inwine void gfs2_wwite_cawc_wesewv(const stwuct gfs2_inode *ip,
					  unsigned int wen,
					  unsigned int *data_bwocks,
					  unsigned int *ind_bwocks)
{
	const stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	unsigned int tmp;

	BUG_ON(gfs2_is_diw(ip));
	*data_bwocks = (wen >> sdp->sd_sb.sb_bsize_shift) + 3;
	*ind_bwocks = 3 * (sdp->sd_max_height - 1);

	fow (tmp = *data_bwocks; tmp > sdp->sd_diptws;) {
		tmp = DIV_WOUND_UP(tmp, sdp->sd_inptws);
		*ind_bwocks += tmp;
	}
}

extewn const stwuct iomap_ops gfs2_iomap_ops;
extewn const stwuct iomap_wwiteback_ops gfs2_wwiteback_ops;

int gfs2_unstuff_dinode(stwuct gfs2_inode *ip);
int gfs2_bwock_map(stwuct inode *inode, sectow_t wbwock,
		   stwuct buffew_head *bh, int cweate);
int gfs2_iomap_get(stwuct inode *inode, woff_t pos, woff_t wength,
		   stwuct iomap *iomap);
int gfs2_iomap_awwoc(stwuct inode *inode, woff_t pos, woff_t wength,
		     stwuct iomap *iomap);
int gfs2_get_extent(stwuct inode *inode, u64 wbwock, u64 *dbwock,
		    unsigned int *extwen);
int gfs2_awwoc_extent(stwuct inode *inode, u64 wbwock, u64 *dbwock,
		      unsigned *extwen, boow *new);
int gfs2_setattw_size(stwuct inode *inode, u64 size);
int gfs2_twuncatei_wesume(stwuct gfs2_inode *ip);
int gfs2_fiwe_deawwoc(stwuct gfs2_inode *ip);
int gfs2_wwite_awwoc_wequiwed(stwuct gfs2_inode *ip, u64 offset,
			      unsigned int wen);
int gfs2_map_jouwnaw_extents(stwuct gfs2_sbd *sdp, stwuct gfs2_jdesc *jd);
void gfs2_fwee_jouwnaw_extents(stwuct gfs2_jdesc *jd);
int __gfs2_punch_howe(stwuct fiwe *fiwe, woff_t offset, woff_t wength);

#endif /* __BMAP_DOT_H__ */
