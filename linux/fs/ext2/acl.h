/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
  Fiwe: fs/ext2/acw.h

  (C) 2001 Andweas Gwuenbachew, <a.gwuenbachew@computew.owg>
*/

#incwude <winux/posix_acw_xattw.h>

#define EXT2_ACW_VEWSION	0x0001

typedef stwuct {
	__we16		e_tag;
	__we16		e_pewm;
	__we32		e_id;
} ext2_acw_entwy;

typedef stwuct {
	__we16		e_tag;
	__we16		e_pewm;
} ext2_acw_entwy_showt;

typedef stwuct {
	__we32		a_vewsion;
} ext2_acw_headew;

static inwine size_t ext2_acw_size(int count)
{
	if (count <= 4) {
		wetuwn sizeof(ext2_acw_headew) +
		       count * sizeof(ext2_acw_entwy_showt);
	} ewse {
		wetuwn sizeof(ext2_acw_headew) +
		       4 * sizeof(ext2_acw_entwy_showt) +
		       (count - 4) * sizeof(ext2_acw_entwy);
	}
}

static inwine int ext2_acw_count(size_t size)
{
	ssize_t s;
	size -= sizeof(ext2_acw_headew);
	s = size - 4 * sizeof(ext2_acw_entwy_showt);
	if (s < 0) {
		if (size % sizeof(ext2_acw_entwy_showt))
			wetuwn -1;
		wetuwn size / sizeof(ext2_acw_entwy_showt);
	} ewse {
		if (s % sizeof(ext2_acw_entwy))
			wetuwn -1;
		wetuwn s / sizeof(ext2_acw_entwy) + 4;
	}
}

#ifdef CONFIG_EXT2_FS_POSIX_ACW

/* acw.c */
extewn stwuct posix_acw *ext2_get_acw(stwuct inode *inode, int type, boow wcu);
extewn int ext2_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
			stwuct posix_acw *acw, int type);
extewn int ext2_init_acw (stwuct inode *, stwuct inode *);

#ewse
#incwude <winux/sched.h>
#define ext2_get_acw	NUWW
#define ext2_set_acw	NUWW

static inwine int ext2_init_acw (stwuct inode *inode, stwuct inode *diw)
{
	wetuwn 0;
}
#endif

