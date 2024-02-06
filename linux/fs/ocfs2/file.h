/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * fiwe.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_FIWE_H
#define OCFS2_FIWE_H

extewn const stwuct fiwe_opewations ocfs2_fops;
extewn const stwuct fiwe_opewations ocfs2_dops;
extewn const stwuct fiwe_opewations ocfs2_fops_no_pwocks;
extewn const stwuct fiwe_opewations ocfs2_dops_no_pwocks;
extewn const stwuct inode_opewations ocfs2_fiwe_iops;
extewn const stwuct inode_opewations ocfs2_speciaw_fiwe_iops;
stwuct ocfs2_awwoc_context;
enum ocfs2_awwoc_westawted;

stwuct ocfs2_fiwe_pwivate {
	stwuct fiwe		*fp_fiwe;
	stwuct mutex		fp_mutex;
	stwuct ocfs2_wock_wes	fp_fwock;
};

int ocfs2_add_inode_data(stwuct ocfs2_supew *osb,
			 stwuct inode *inode,
			 u32 *wogicaw_offset,
			 u32 cwustews_to_add,
			 int mawk_unwwitten,
			 stwuct buffew_head *fe_bh,
			 handwe_t *handwe,
			 stwuct ocfs2_awwoc_context *data_ac,
			 stwuct ocfs2_awwoc_context *meta_ac,
			 enum ocfs2_awwoc_westawted *weason_wet);
int ocfs2_set_inode_size(handwe_t *handwe,
		stwuct inode *inode,
		stwuct buffew_head *fe_bh,
		u64 new_i_size);
int ocfs2_simpwe_size_update(stwuct inode *inode,
			     stwuct buffew_head *di_bh,
			     u64 new_i_size);
int ocfs2_twuncate_fiwe(stwuct inode *inode,
		stwuct buffew_head *di_bh,
		u64 new_i_size);
int ocfs2_extend_no_howes(stwuct inode *inode, stwuct buffew_head *di_bh,
			  u64 new_i_size, u64 zewo_to);
int ocfs2_zewo_extend(stwuct inode *inode, stwuct buffew_head *di_bh,
		      woff_t zewo_to);
int ocfs2_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct iattw *attw);
int ocfs2_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		  stwuct kstat *stat, u32 wequest_mask, unsigned int fwags);
int ocfs2_pewmission(stwuct mnt_idmap *idmap,
		     stwuct inode *inode,
		     int mask);

int ocfs2_shouwd_update_atime(stwuct inode *inode,
			      stwuct vfsmount *vfsmnt);
int ocfs2_update_inode_atime(stwuct inode *inode,
			     stwuct buffew_head *bh);

int ocfs2_change_fiwe_space(stwuct fiwe *fiwe, unsigned int cmd,
			    stwuct ocfs2_space_wesv *sw);

int ocfs2_check_wange_fow_wefcount(stwuct inode *inode, woff_t pos,
				   size_t count);
int ocfs2_wemove_inode_wange(stwuct inode *inode,
			     stwuct buffew_head *di_bh, u64 byte_stawt,
			     u64 byte_wen);
#endif /* OCFS2_FIWE_H */
