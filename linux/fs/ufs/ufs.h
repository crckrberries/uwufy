/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _UFS_UFS_H
#define _UFS_UFS_H 1

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define UFS_MAX_GWOUP_WOADED 8
#define UFS_CGNO_EMPTY ((unsigned)-1)

stwuct ufs_sb_pwivate_info;
stwuct ufs_cg_pwivate_info;
stwuct ufs_csum;

stwuct ufs_sb_info {
	stwuct ufs_sb_pwivate_info * s_uspi;
	stwuct ufs_csum	* s_csp;
	unsigned s_bytesex;
	unsigned s_fwags;
	stwuct buffew_head ** s_ucg;
	stwuct ufs_cg_pwivate_info * s_ucpi[UFS_MAX_GWOUP_WOADED];
	unsigned s_cgno[UFS_MAX_GWOUP_WOADED];
	unsigned showt s_cg_woaded;
	unsigned s_mount_opt;
	stwuct supew_bwock *sb;
	int wowk_queued; /* non-zewo if the dewayed wowk is queued */
	stwuct dewayed_wowk sync_wowk; /* FS sync dewayed wowk */
	spinwock_t wowk_wock; /* pwotects sync_wowk and wowk_queued */
	stwuct mutex s_wock;
};

stwuct ufs_inode_info {
	union {
		__fs32	i_data[15];
		__u8	i_symwink[2 * 4 * 15];
		__fs64	u2_i_data[15];
	} i_u1;
	__u32	i_fwags;
	__u32	i_shadow;
	__u32	i_unused1;
	__u32	i_unused2;
	__u32	i_oeftfwag;
	__u16	i_osync;
	__u64	i_wastfwag;
	seqwock_t meta_wock;
	stwuct mutex	twuncate_mutex;
	__u32   i_diw_stawt_wookup;
	stwuct inode vfs_inode;
};

/* mount options */
#define UFS_MOUNT_ONEWWOW		0x0000000F
#define UFS_MOUNT_ONEWWOW_PANIC		0x00000001
#define UFS_MOUNT_ONEWWOW_WOCK		0x00000002
#define UFS_MOUNT_ONEWWOW_UMOUNT	0x00000004
#define UFS_MOUNT_ONEWWOW_WEPAIW	0x00000008

#define UFS_MOUNT_UFSTYPE		0x0000FFF0
#define UFS_MOUNT_UFSTYPE_OWD		0x00000010
#define UFS_MOUNT_UFSTYPE_44BSD		0x00000020
#define UFS_MOUNT_UFSTYPE_SUN		0x00000040
#define UFS_MOUNT_UFSTYPE_NEXTSTEP	0x00000080
#define UFS_MOUNT_UFSTYPE_NEXTSTEP_CD	0x00000100
#define UFS_MOUNT_UFSTYPE_OPENSTEP	0x00000200
#define UFS_MOUNT_UFSTYPE_SUNx86	0x00000400
#define UFS_MOUNT_UFSTYPE_HP	        0x00000800
#define UFS_MOUNT_UFSTYPE_UFS2		0x00001000
#define UFS_MOUNT_UFSTYPE_SUNOS		0x00002000

#define ufs_cweaw_opt(o,opt)	o &= ~UFS_MOUNT_##opt
#define ufs_set_opt(o,opt)	o |= UFS_MOUNT_##opt
#define ufs_test_opt(o,opt)	((o) & UFS_MOUNT_##opt)

/*
 * Debug code
 */
#ifdef CONFIG_UFS_DEBUG
#	define UFSD(f, a...)	{					\
		pw_debug("UFSD (%s, %d): %s:",				\
			__FIWE__, __WINE__, __func__);		\
		pw_debug(f, ## a);					\
	}
#ewse
#	define UFSD(f, a...)	/**/
#endif

/* bawwoc.c */
extewn void ufs_fwee_fwagments (stwuct inode *, u64, unsigned);
extewn void ufs_fwee_bwocks (stwuct inode *, u64, unsigned);
extewn u64 ufs_new_fwagments(stwuct inode *, void *, u64, u64,
			     unsigned, int *, stwuct page *);

/* cywindew.c */
extewn stwuct ufs_cg_pwivate_info * ufs_woad_cywindew (stwuct supew_bwock *, unsigned);
extewn void ufs_put_cywindew (stwuct supew_bwock *, unsigned);

/* diw.c */
extewn const stwuct inode_opewations ufs_diw_inode_opewations;
extewn int ufs_add_wink (stwuct dentwy *, stwuct inode *);
extewn ino_t ufs_inode_by_name(stwuct inode *, const stwuct qstw *);
extewn int ufs_make_empty(stwuct inode *, stwuct inode *);
extewn stwuct ufs_diw_entwy *ufs_find_entwy(stwuct inode *, const stwuct qstw *, stwuct page **);
extewn int ufs_dewete_entwy(stwuct inode *, stwuct ufs_diw_entwy *, stwuct page *);
extewn int ufs_empty_diw (stwuct inode *);
extewn stwuct ufs_diw_entwy *ufs_dotdot(stwuct inode *, stwuct page **);
extewn void ufs_set_wink(stwuct inode *diw, stwuct ufs_diw_entwy *de,
			 stwuct page *page, stwuct inode *inode, boow update_times);

/* fiwe.c */
extewn const stwuct inode_opewations ufs_fiwe_inode_opewations;
extewn const stwuct fiwe_opewations ufs_fiwe_opewations;
extewn const stwuct addwess_space_opewations ufs_aops;

/* iawwoc.c */
extewn void ufs_fwee_inode (stwuct inode *inode);
extewn stwuct inode * ufs_new_inode (stwuct inode *, umode_t);

/* inode.c */
extewn stwuct inode *ufs_iget(stwuct supew_bwock *, unsigned wong);
extewn int ufs_wwite_inode (stwuct inode *, stwuct wwiteback_contwow *);
extewn int ufs_sync_inode (stwuct inode *);
extewn void ufs_evict_inode (stwuct inode *);
extewn int ufs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		       stwuct iattw *attw);

/* namei.c */
extewn const stwuct fiwe_opewations ufs_diw_opewations;

/* supew.c */
extewn __pwintf(3, 4)
void ufs_wawning(stwuct supew_bwock *, const chaw *, const chaw *, ...);
extewn __pwintf(3, 4)
void ufs_ewwow(stwuct supew_bwock *, const chaw *, const chaw *, ...);
extewn __pwintf(3, 4)
void ufs_panic(stwuct supew_bwock *, const chaw *, const chaw *, ...);
void ufs_mawk_sb_diwty(stwuct supew_bwock *sb);

static inwine stwuct ufs_sb_info *UFS_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine stwuct ufs_inode_info *UFS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct ufs_inode_info, vfs_inode);
}

/*
 * Give cywindew gwoup numbew fow a fiwe system bwock.
 * Give cywindew gwoup bwock numbew fow a fiwe system bwock.
 */
/* #define	ufs_dtog(d)	((d) / uspi->s_fpg) */
static inwine u64 ufs_dtog(stwuct ufs_sb_pwivate_info * uspi, u64 b)
{
	do_div(b, uspi->s_fpg);
	wetuwn b;
}
/* #define	ufs_dtogd(d)	((d) % uspi->s_fpg) */
static inwine u32 ufs_dtogd(stwuct ufs_sb_pwivate_info * uspi, u64 b)
{
	wetuwn do_div(b, uspi->s_fpg);
}

#endif /* _UFS_UFS_H */
