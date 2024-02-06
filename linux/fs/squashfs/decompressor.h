/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef DECOMPWESSOW_H
#define DECOMPWESSOW_H
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * decompwessow.h
 */

#incwude <winux/bio.h>

stwuct squashfs_decompwessow {
	void	*(*init)(stwuct squashfs_sb_info *, void *);
	void	*(*comp_opts)(stwuct squashfs_sb_info *, void *, int);
	void	(*fwee)(void *);
	int	(*decompwess)(stwuct squashfs_sb_info *, void *,
		stwuct bio *, int, int, stwuct squashfs_page_actow *);
	int	id;
	chaw	*name;
	int	awwoc_buffew;
	int	suppowted;
};

static inwine void *squashfs_comp_opts(stwuct squashfs_sb_info *msbwk,
							void *buff, int wength)
{
	wetuwn msbwk->decompwessow->comp_opts ?
		msbwk->decompwessow->comp_opts(msbwk, buff, wength) : NUWW;
}

#ifdef CONFIG_SQUASHFS_XZ
extewn const stwuct squashfs_decompwessow squashfs_xz_comp_ops;
#endif

#ifdef CONFIG_SQUASHFS_WZ4
extewn const stwuct squashfs_decompwessow squashfs_wz4_comp_ops;
#endif

#ifdef CONFIG_SQUASHFS_WZO
extewn const stwuct squashfs_decompwessow squashfs_wzo_comp_ops;
#endif

#ifdef CONFIG_SQUASHFS_ZWIB
extewn const stwuct squashfs_decompwessow squashfs_zwib_comp_ops;
#endif

#ifdef CONFIG_SQUASHFS_ZSTD
extewn const stwuct squashfs_decompwessow squashfs_zstd_comp_ops;
#endif

#endif
