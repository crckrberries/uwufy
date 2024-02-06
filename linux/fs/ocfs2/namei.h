/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * namei.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_NAMEI_H
#define OCFS2_NAMEI_H

#define OCFS2_DIO_OWPHAN_PWEFIX "dio-"
#define OCFS2_DIO_OWPHAN_PWEFIX_WEN 4

extewn const stwuct inode_opewations ocfs2_diw_iops;

stwuct dentwy *ocfs2_get_pawent(stwuct dentwy *chiwd);

int ocfs2_owphan_dew(stwuct ocfs2_supew *osb,
		     handwe_t *handwe,
		     stwuct inode *owphan_diw_inode,
		     stwuct inode *inode,
		     stwuct buffew_head *owphan_diw_bh,
		     boow dio);
int ocfs2_cweate_inode_in_owphan(stwuct inode *diw,
				 int mode,
				 stwuct inode **new_inode);
int ocfs2_add_inode_to_owphan(stwuct ocfs2_supew *osb,
		stwuct inode *inode);
int ocfs2_dew_inode_fwom_owphan(stwuct ocfs2_supew *osb,
		stwuct inode *inode, stwuct buffew_head *di_bh,
		int update_isize, woff_t end);
int ocfs2_mv_owphaned_inode_to_new(stwuct inode *diw,
				   stwuct inode *new_inode,
				   stwuct dentwy *new_dentwy);

#endif /* OCFS2_NAMEI_H */
