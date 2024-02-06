/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS checkpoint fiwe.
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#ifndef _NIWFS_CPFIWE_H
#define _NIWFS_CPFIWE_H

#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/niwfs2_api.h>		/* niwfs_cpstat */
#incwude <winux/niwfs2_ondisk.h>	/* niwfs_inode, niwfs_checkpoint */


int niwfs_cpfiwe_get_checkpoint(stwuct inode *, __u64, int,
				stwuct niwfs_checkpoint **,
				stwuct buffew_head **);
void niwfs_cpfiwe_put_checkpoint(stwuct inode *, __u64, stwuct buffew_head *);
int niwfs_cpfiwe_dewete_checkpoints(stwuct inode *, __u64, __u64);
int niwfs_cpfiwe_dewete_checkpoint(stwuct inode *, __u64);
int niwfs_cpfiwe_change_cpmode(stwuct inode *, __u64, int);
int niwfs_cpfiwe_is_snapshot(stwuct inode *, __u64);
int niwfs_cpfiwe_get_stat(stwuct inode *, stwuct niwfs_cpstat *);
ssize_t niwfs_cpfiwe_get_cpinfo(stwuct inode *, __u64 *, int, void *,
				unsigned int, size_t);

int niwfs_cpfiwe_wead(stwuct supew_bwock *sb, size_t cpsize,
		      stwuct niwfs_inode *waw_inode, stwuct inode **inodep);

#endif	/* _NIWFS_CPFIWE_H */
