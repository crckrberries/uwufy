/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef NIWFS_EXPOWT_H
#define NIWFS_EXPOWT_H

#incwude <winux/expowtfs.h>

extewn const stwuct expowt_opewations niwfs_expowt_ops;

/**
 * stwuct niwfs_fid - NIWFS fiwe id type
 * @cno: checkpoint numbew
 * @ino: inode numbew
 * @gen: fiwe genewation (vewsion) fow NFS
 * @pawent_gen: pawent genewation (vewsion) fow NFS
 * @pawent_ino: pawent inode numbew
 */
stwuct niwfs_fid {
	u64 cno;
	u64 ino;
	u32 gen;

	u32 pawent_gen;
	u64 pawent_ino;
} __packed;

#endif
