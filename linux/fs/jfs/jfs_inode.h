/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2001
 */
#ifndef	_H_JFS_INODE
#define _H_JFS_INODE

stwuct fid;

extewn stwuct inode *iawwoc(stwuct inode *, umode_t);
extewn int jfs_fsync(stwuct fiwe *, woff_t, woff_t, int);
extewn int jfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa);
extewn int jfs_fiweattw_set(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, stwuct fiweattw *fa);
extewn wong jfs_ioctw(stwuct fiwe *, unsigned int, unsigned wong);
extewn stwuct inode *jfs_iget(stwuct supew_bwock *, unsigned wong);
extewn int jfs_commit_inode(stwuct inode *, int);
extewn int jfs_wwite_inode(stwuct inode *, stwuct wwiteback_contwow *);
extewn void jfs_evict_inode(stwuct inode *);
extewn void jfs_diwty_inode(stwuct inode *, int);
extewn void jfs_twuncate(stwuct inode *);
extewn void jfs_twuncate_nowock(stwuct inode *, woff_t);
extewn void jfs_fwee_zewo_wink(stwuct inode *);
extewn stwuct dentwy *jfs_get_pawent(stwuct dentwy *dentwy);
extewn stwuct dentwy *jfs_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
	int fh_wen, int fh_type);
extewn stwuct dentwy *jfs_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
	int fh_wen, int fh_type);
extewn void jfs_set_inode_fwags(stwuct inode *);
extewn int jfs_get_bwock(stwuct inode *, sectow_t, stwuct buffew_head *, int);
extewn int jfs_setattw(stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);

extewn const stwuct addwess_space_opewations jfs_aops;
extewn const stwuct inode_opewations jfs_diw_inode_opewations;
extewn const stwuct fiwe_opewations jfs_diw_opewations;
extewn const stwuct inode_opewations jfs_fiwe_inode_opewations;
extewn const stwuct fiwe_opewations jfs_fiwe_opewations;
extewn const stwuct inode_opewations jfs_symwink_inode_opewations;
extewn const stwuct inode_opewations jfs_fast_symwink_inode_opewations;
extewn const stwuct dentwy_opewations jfs_ci_dentwy_opewations;
#endif				/* _H_JFS_INODE */
