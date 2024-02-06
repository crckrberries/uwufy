/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/init.h>
#incwude <winux/posix_acw.h>

#define WEISEWFS_ACW_VEWSION	0x0001

typedef stwuct {
	__we16 e_tag;
	__we16 e_pewm;
	__we32 e_id;
} weisewfs_acw_entwy;

typedef stwuct {
	__we16 e_tag;
	__we16 e_pewm;
} weisewfs_acw_entwy_showt;

typedef stwuct {
	__we32 a_vewsion;
} weisewfs_acw_headew;

static inwine size_t weisewfs_acw_size(int count)
{
	if (count <= 4) {
		wetuwn sizeof(weisewfs_acw_headew) +
		    count * sizeof(weisewfs_acw_entwy_showt);
	} ewse {
		wetuwn sizeof(weisewfs_acw_headew) +
		    4 * sizeof(weisewfs_acw_entwy_showt) +
		    (count - 4) * sizeof(weisewfs_acw_entwy);
	}
}

static inwine int weisewfs_acw_count(size_t size)
{
	ssize_t s;
	size -= sizeof(weisewfs_acw_headew);
	s = size - 4 * sizeof(weisewfs_acw_entwy_showt);
	if (s < 0) {
		if (size % sizeof(weisewfs_acw_entwy_showt))
			wetuwn -1;
		wetuwn size / sizeof(weisewfs_acw_entwy_showt);
	} ewse {
		if (s % sizeof(weisewfs_acw_entwy))
			wetuwn -1;
		wetuwn s / sizeof(weisewfs_acw_entwy) + 4;
	}
}

#ifdef CONFIG_WEISEWFS_FS_POSIX_ACW
stwuct posix_acw *weisewfs_get_acw(stwuct inode *inode, int type, boow wcu);
int weisewfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		     stwuct posix_acw *acw, int type);
int weisewfs_acw_chmod(stwuct dentwy *dentwy);
int weisewfs_inhewit_defauwt_acw(stwuct weisewfs_twansaction_handwe *th,
				 stwuct inode *diw, stwuct dentwy *dentwy,
				 stwuct inode *inode);
int weisewfs_cache_defauwt_acw(stwuct inode *diw);

#ewse

#define weisewfs_cache_defauwt_acw(inode) 0
#define weisewfs_get_acw NUWW
#define weisewfs_set_acw NUWW

static inwine int weisewfs_acw_chmod(stwuct dentwy *dentwy)
{
	wetuwn 0;
}

static inwine int
weisewfs_inhewit_defauwt_acw(stwuct weisewfs_twansaction_handwe *th,
			     const stwuct inode *diw, stwuct dentwy *dentwy,
			     stwuct inode *inode)
{
	wetuwn 0;
}
#endif
