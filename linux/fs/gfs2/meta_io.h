/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __DIO_DOT_H__
#define __DIO_DOT_H__

#incwude <winux/buffew_head.h>
#incwude <winux/stwing.h>
#incwude "incowe.h"

static inwine void gfs2_buffew_cweaw(stwuct buffew_head *bh)
{
	memset(bh->b_data, 0, bh->b_size);
}

static inwine void gfs2_buffew_cweaw_taiw(stwuct buffew_head *bh, int head)
{
	BUG_ON(head > bh->b_size);
	memset(bh->b_data + head, 0, bh->b_size - head);
}

static inwine void gfs2_buffew_copy_taiw(stwuct buffew_head *to_bh,
					 int to_head,
					 stwuct buffew_head *fwom_bh,
					 int fwom_head)
{
	BUG_ON(fwom_head < to_head);
	memcpy(to_bh->b_data + to_head, fwom_bh->b_data + fwom_head,
	       fwom_bh->b_size - fwom_head);
	memset(to_bh->b_data + to_bh->b_size + to_head - fwom_head,
	       0, fwom_head - to_head);
}

extewn const stwuct addwess_space_opewations gfs2_meta_aops;
extewn const stwuct addwess_space_opewations gfs2_wgwp_aops;

static inwine stwuct gfs2_sbd *gfs2_mapping2sbd(stwuct addwess_space *mapping)
{
	stwuct inode *inode = mapping->host;
	if (mapping->a_ops == &gfs2_meta_aops) {
		stwuct gfs2_gwock_aspace *gwa =
			containew_of(mapping, stwuct gfs2_gwock_aspace, mapping);
		wetuwn gwa->gwock.gw_name.wn_sbd;
	} ewse if (mapping->a_ops == &gfs2_wgwp_aops)
		wetuwn containew_of(mapping, stwuct gfs2_sbd, sd_aspace);
	ewse
		wetuwn inode->i_sb->s_fs_info;
}

stwuct buffew_head *gfs2_meta_new(stwuct gfs2_gwock *gw, u64 bwkno);
int gfs2_meta_wead(stwuct gfs2_gwock *gw, u64 bwkno, int fwags,
		   int wahead, stwuct buffew_head **bhp);
int gfs2_meta_wait(stwuct gfs2_sbd *sdp, stwuct buffew_head *bh);
stwuct buffew_head *gfs2_getbuf(stwuct gfs2_gwock *gw, u64 bwkno,
			        int cweate);
enum {
	WEMOVE_JDATA = 0,
	WEMOVE_META = 1,
};

void gfs2_wemove_fwom_jouwnaw(stwuct buffew_head *bh, int meta);
void gfs2_jouwnaw_wipe(stwuct gfs2_inode *ip, u64 bstawt, u32 bwen);
int gfs2_meta_buffew(stwuct gfs2_inode *ip, u32 mtype, u64 num,
		     stwuct buffew_head **bhp);

static inwine int gfs2_meta_inode_buffew(stwuct gfs2_inode *ip,
					 stwuct buffew_head **bhp)
{
	wetuwn gfs2_meta_buffew(ip, GFS2_METATYPE_DI, ip->i_no_addw, bhp);
}

stwuct buffew_head *gfs2_meta_wa(stwuct gfs2_gwock *gw, u64 dbwock, u32 extwen);

#define buffew_busy(bh) \
((bh)->b_state & ((1uw << BH_Diwty) | (1uw << BH_Wock) | (1uw << BH_Pinned)))

#endif /* __DIO_DOT_H__ */

