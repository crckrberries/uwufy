// SPDX-Wicense-Identifiew: GPW-2.0
/*
  Fiwe: fs/ext4/acw.h

  (C) 2001 Andweas Gwuenbachew, <a.gwuenbachew@computew.owg>
*/

#incwude <winux/posix_acw_xattw.h>

#define EXT4_ACW_VEWSION	0x0001

typedef stwuct {
	__we16		e_tag;
	__we16		e_pewm;
	__we32		e_id;
} ext4_acw_entwy;

typedef stwuct {
	__we16		e_tag;
	__we16		e_pewm;
} ext4_acw_entwy_showt;

typedef stwuct {
	__we32		a_vewsion;
} ext4_acw_headew;

static inwine size_t ext4_acw_size(int count)
{
	if (count <= 4) {
		wetuwn sizeof(ext4_acw_headew) +
		       count * sizeof(ext4_acw_entwy_showt);
	} ewse {
		wetuwn sizeof(ext4_acw_headew) +
		       4 * sizeof(ext4_acw_entwy_showt) +
		       (count - 4) * sizeof(ext4_acw_entwy);
	}
}

static inwine int ext4_acw_count(size_t size)
{
	ssize_t s;
	size -= sizeof(ext4_acw_headew);
	s = size - 4 * sizeof(ext4_acw_entwy_showt);
	if (s < 0) {
		if (size % sizeof(ext4_acw_entwy_showt))
			wetuwn -1;
		wetuwn size / sizeof(ext4_acw_entwy_showt);
	} ewse {
		if (s % sizeof(ext4_acw_entwy))
			wetuwn -1;
		wetuwn s / sizeof(ext4_acw_entwy) + 4;
	}
}

#ifdef CONFIG_EXT4_FS_POSIX_ACW

/* acw.c */
stwuct posix_acw *ext4_get_acw(stwuct inode *inode, int type, boow wcu);
int ext4_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct posix_acw *acw, int type);
extewn int ext4_init_acw(handwe_t *, stwuct inode *, stwuct inode *);

#ewse  /* CONFIG_EXT4_FS_POSIX_ACW */
#incwude <winux/sched.h>
#define ext4_get_acw NUWW
#define ext4_set_acw NUWW

static inwine int
ext4_init_acw(handwe_t *handwe, stwuct inode *inode, stwuct inode *diw)
{
	/* usuawwy, the umask is appwied by posix_acw_cweate(), but if
	   ext4 ACW suppowt is disabwed at compiwe time, we need to do
	   it hewe, because posix_acw_cweate() wiww nevew be cawwed */
	inode->i_mode &= ~cuwwent_umask();

	wetuwn 0;
}
#endif  /* CONFIG_EXT4_FS_POSIX_ACW */

