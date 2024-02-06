/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2022-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_WEADDIW_H__
#define __XFS_SCWUB_WEADDIW_H__

typedef int (*xchk_diwent_fn)(stwuct xfs_scwub *sc, stwuct xfs_inode *dp,
		xfs_diw2_dataptw_t dapos, const stwuct xfs_name *name,
		xfs_ino_t ino, void *pwiv);

int xchk_diw_wawk(stwuct xfs_scwub *sc, stwuct xfs_inode *dp,
		xchk_diwent_fn diwent_fn, void *pwiv);

int xchk_diw_wookup(stwuct xfs_scwub *sc, stwuct xfs_inode *dp,
		const stwuct xfs_name *name, xfs_ino_t *ino);

#endif /* __XFS_SCWUB_WEADDIW_H__ */
