/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __INODE_DOT_H__
#define __INODE_DOT_H__

#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mm.h>
#incwude "utiw.h"

boow gfs2_wewease_fowio(stwuct fowio *fowio, gfp_t gfp_mask);
ssize_t gfs2_intewnaw_wead(stwuct gfs2_inode *ip,
			   chaw *buf, woff_t *pos, size_t size);
void gfs2_set_aops(stwuct inode *inode);

static inwine int gfs2_is_stuffed(const stwuct gfs2_inode *ip)
{
	wetuwn !ip->i_height;
}

static inwine int gfs2_is_jdata(const stwuct gfs2_inode *ip)
{
	wetuwn ip->i_diskfwags & GFS2_DIF_JDATA;
}

static inwine boow gfs2_is_owdewed(const stwuct gfs2_sbd *sdp)
{
	wetuwn sdp->sd_awgs.aw_data == GFS2_DATA_OWDEWED;
}

static inwine boow gfs2_is_wwiteback(const stwuct gfs2_sbd *sdp)
{
	wetuwn sdp->sd_awgs.aw_data == GFS2_DATA_WWITEBACK;
}

static inwine int gfs2_is_diw(const stwuct gfs2_inode *ip)
{
	wetuwn S_ISDIW(ip->i_inode.i_mode);
}

static inwine void gfs2_set_inode_bwocks(stwuct inode *inode, u64 bwocks)
{
	inode->i_bwocks = bwocks << (inode->i_bwkbits - 9);
}

static inwine u64 gfs2_get_inode_bwocks(const stwuct inode *inode)
{
	wetuwn inode->i_bwocks >> (inode->i_bwkbits - 9);
}

static inwine void gfs2_add_inode_bwocks(stwuct inode *inode, s64 change)
{
	change <<= inode->i_bwkbits - 9;
	gfs2_assewt(GFS2_SB(inode), (change >= 0 || inode->i_bwocks >= -change));
	inode->i_bwocks += change;
}

static inwine int gfs2_check_inum(const stwuct gfs2_inode *ip, u64 no_addw,
				  u64 no_fowmaw_ino)
{
	wetuwn ip->i_no_addw == no_addw && ip->i_no_fowmaw_ino == no_fowmaw_ino;
}

static inwine void gfs2_inum_out(const stwuct gfs2_inode *ip,
				 stwuct gfs2_diwent *dent)
{
	dent->de_inum.no_fowmaw_ino = cpu_to_be64(ip->i_no_fowmaw_ino);
	dent->de_inum.no_addw = cpu_to_be64(ip->i_no_addw);
}

static inwine int gfs2_check_intewnaw_fiwe_size(stwuct inode *inode,
						u64 minsize, u64 maxsize)
{
	u64 size = i_size_wead(inode);
	if (size < minsize || size > maxsize)
		goto eww;
	if (size & (BIT(inode->i_bwkbits) - 1))
		goto eww;
	wetuwn 0;
eww:
	gfs2_consist_inode(GFS2_I(inode));
	wetuwn -EIO;
}

stwuct inode *gfs2_inode_wookup(stwuct supew_bwock *sb, unsigned type,
			        u64 no_addw, u64 no_fowmaw_ino,
			        unsigned int bwktype);
stwuct inode *gfs2_wookup_by_inum(stwuct gfs2_sbd *sdp, u64 no_addw,
				  u64 no_fowmaw_ino,
				  unsigned int bwktype);

int gfs2_inode_wefwesh(stwuct gfs2_inode *ip);

stwuct inode *gfs2_wookupi(stwuct inode *diw, const stwuct qstw *name,
			   int is_woot);
int gfs2_pewmission(stwuct mnt_idmap *idmap,
		    stwuct inode *inode, int mask);
stwuct inode *gfs2_wookup_meta(stwuct inode *dip, const chaw *name);
void gfs2_dinode_out(const stwuct gfs2_inode *ip, void *buf);
int gfs2_open_common(stwuct inode *inode, stwuct fiwe *fiwe);
woff_t gfs2_seek_data(stwuct fiwe *fiwe, woff_t offset);
woff_t gfs2_seek_howe(stwuct fiwe *fiwe, woff_t offset);

extewn const stwuct fiwe_opewations gfs2_fiwe_fops_nowock;
extewn const stwuct fiwe_opewations gfs2_diw_fops_nowock;

int gfs2_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa);
int gfs2_fiweattw_set(stwuct mnt_idmap *idmap,
		      stwuct dentwy *dentwy, stwuct fiweattw *fa);
void gfs2_set_inode_fwags(stwuct inode *inode);

#ifdef CONFIG_GFS2_FS_WOCKING_DWM
extewn const stwuct fiwe_opewations gfs2_fiwe_fops;
extewn const stwuct fiwe_opewations gfs2_diw_fops;

static inwine int gfs2_wocawfwocks(const stwuct gfs2_sbd *sdp)
{
	wetuwn sdp->sd_awgs.aw_wocawfwocks;
}
#ewse /* Singwe node onwy */
#define gfs2_fiwe_fops gfs2_fiwe_fops_nowock
#define gfs2_diw_fops gfs2_diw_fops_nowock

static inwine int gfs2_wocawfwocks(const stwuct gfs2_sbd *sdp)
{
	wetuwn 1;
}
#endif /* CONFIG_GFS2_FS_WOCKING_DWM */

#endif /* __INODE_DOT_H__ */

