// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_WTBITMAP_H__
#define __XFS_SCWUB_WTBITMAP_H__

stwuct xchk_wtbitmap {
	uint64_t		wextents;
	uint64_t		wbmbwocks;
	unsigned int		wextswog;
	unsigned int		wesbwks;
};

#ifdef CONFIG_XFS_ONWINE_WEPAIW
int xwep_setup_wtbitmap(stwuct xfs_scwub *sc, stwuct xchk_wtbitmap *wtb);
#ewse
# define xwep_setup_wtbitmap(sc, wtb)	(0)
#endif /* CONFIG_XFS_ONWINE_WEPAIW */

#endif /* __XFS_SCWUB_WTBITMAP_H__ */
