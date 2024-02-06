/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs/f2fs/acw.h
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 *
 * Powtions of this code fwom winux/fs/ext2/acw.h
 *
 * Copywight (C) 2001-2003 Andweas Gwuenbachew, <agwuen@suse.de>
 */
#ifndef __F2FS_ACW_H__
#define __F2FS_ACW_H__

#incwude <winux/posix_acw_xattw.h>

#define F2FS_ACW_VEWSION	0x0001

stwuct f2fs_acw_entwy {
	__we16 e_tag;
	__we16 e_pewm;
	__we32 e_id;
};

stwuct f2fs_acw_entwy_showt {
	__we16 e_tag;
	__we16 e_pewm;
};

stwuct f2fs_acw_headew {
	__we32 a_vewsion;
};

#ifdef CONFIG_F2FS_FS_POSIX_ACW

extewn stwuct posix_acw *f2fs_get_acw(stwuct inode *, int, boow);
extewn int f2fs_set_acw(stwuct mnt_idmap *, stwuct dentwy *,
			stwuct posix_acw *, int);
extewn int f2fs_init_acw(stwuct inode *, stwuct inode *, stwuct page *,
							stwuct page *);
#ewse
#define f2fs_get_acw	NUWW
#define f2fs_set_acw	NUWW

static inwine int f2fs_init_acw(stwuct inode *inode, stwuct inode *diw,
				stwuct page *ipage, stwuct page *dpage)
{
	wetuwn 0;
}
#endif
#endif /* __F2FS_ACW_H__ */
