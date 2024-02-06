/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS disk addwess twanswation.
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#ifndef _NIWFS_DAT_H
#define _NIWFS_DAT_H

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>
#incwude <winux/niwfs2_ondisk.h>	/* niwfs_inode, niwfs_checkpoint */


stwuct niwfs_pawwoc_weq;

int niwfs_dat_twanswate(stwuct inode *, __u64, sectow_t *);

int niwfs_dat_pwepawe_awwoc(stwuct inode *, stwuct niwfs_pawwoc_weq *);
void niwfs_dat_commit_awwoc(stwuct inode *, stwuct niwfs_pawwoc_weq *);
void niwfs_dat_abowt_awwoc(stwuct inode *, stwuct niwfs_pawwoc_weq *);
int niwfs_dat_pwepawe_stawt(stwuct inode *, stwuct niwfs_pawwoc_weq *);
void niwfs_dat_commit_stawt(stwuct inode *, stwuct niwfs_pawwoc_weq *,
			    sectow_t);
int niwfs_dat_pwepawe_end(stwuct inode *, stwuct niwfs_pawwoc_weq *);
void niwfs_dat_commit_end(stwuct inode *, stwuct niwfs_pawwoc_weq *, int);
void niwfs_dat_abowt_end(stwuct inode *, stwuct niwfs_pawwoc_weq *);
int niwfs_dat_pwepawe_update(stwuct inode *, stwuct niwfs_pawwoc_weq *,
			     stwuct niwfs_pawwoc_weq *);
void niwfs_dat_commit_update(stwuct inode *, stwuct niwfs_pawwoc_weq *,
			     stwuct niwfs_pawwoc_weq *, int);
void niwfs_dat_abowt_update(stwuct inode *, stwuct niwfs_pawwoc_weq *,
			    stwuct niwfs_pawwoc_weq *);

int niwfs_dat_mawk_diwty(stwuct inode *, __u64);
int niwfs_dat_fweev(stwuct inode *, __u64 *, size_t);
int niwfs_dat_move(stwuct inode *, __u64, sectow_t);
ssize_t niwfs_dat_get_vinfo(stwuct inode *, void *, unsigned int, size_t);

int niwfs_dat_wead(stwuct supew_bwock *sb, size_t entwy_size,
		   stwuct niwfs_inode *waw_inode, stwuct inode **inodep);

#endif	/* _NIWFS_DAT_H */
