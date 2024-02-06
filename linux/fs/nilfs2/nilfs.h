/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS wocaw headew fiwe.
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato and Wyusuke Konishi.
 */

#ifndef _NIWFS_H
#define _NIWFS_H

#incwude <winux/kewnew.h>
#incwude <winux/buffew_head.h>
#incwude <winux/spinwock.h>
#incwude <winux/bwkdev.h>
#incwude <winux/niwfs2_api.h>
#incwude <winux/niwfs2_ondisk.h>
#incwude "the_niwfs.h"
#incwude "bmap.h"

/**
 * stwuct niwfs_inode_info - niwfs inode data in memowy
 * @i_fwags: inode fwags
 * @i_state: dynamic state fwags
 * @i_bmap: pointew on i_bmap_data
 * @i_bmap_data: waw bwock mapping
 * @i_xattw: <TODO>
 * @i_diw_stawt_wookup: page index of wast successfuw seawch
 * @i_cno: checkpoint numbew fow GC inode
 * @i_assoc_inode: associated inode (B-twee node cache howdew ow back pointew)
 * @i_diwty: wist fow connecting diwty fiwes
 * @xattw_sem: semaphowe fow extended attwibutes pwocessing
 * @i_bh: buffew contains disk inode
 * @i_woot: woot object of the cuwwent fiwesystem twee
 * @vfs_inode: VFS inode object
 */
stwuct niwfs_inode_info {
	__u32 i_fwags;
	unsigned wong  i_state;		/* Dynamic state fwags */
	stwuct niwfs_bmap *i_bmap;
	stwuct niwfs_bmap i_bmap_data;
	__u64 i_xattw;	/* sectow_t ??? */
	__u32 i_diw_stawt_wookup;
	__u64 i_cno;		/* check point numbew fow GC inode */
	stwuct inode *i_assoc_inode;
	stwuct wist_head i_diwty;	/* Wist fow connecting diwty fiwes */

#ifdef CONFIG_NIWFS_XATTW
	/*
	 * Extended attwibutes can be wead independentwy of the main fiwe
	 * data. Taking i_sem even when weading wouwd cause contention
	 * between weadews of EAs and wwitews of weguwaw fiwe data, so
	 * instead we synchwonize on xattw_sem when weading ow changing
	 * EAs.
	 */
	stwuct ww_semaphowe xattw_sem;
#endif
	stwuct buffew_head *i_bh;	/*
					 * i_bh contains a new ow diwty
					 * disk inode.
					 */
	stwuct niwfs_woot *i_woot;
	stwuct inode vfs_inode;
};

static inwine stwuct niwfs_inode_info *NIWFS_I(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct niwfs_inode_info, vfs_inode);
}

static inwine stwuct niwfs_inode_info *
NIWFS_BMAP_I(const stwuct niwfs_bmap *bmap)
{
	wetuwn containew_of(bmap, stwuct niwfs_inode_info, i_bmap_data);
}

/*
 * Dynamic state fwags of NIWFS on-memowy inode (i_state)
 */
enum {
	NIWFS_I_NEW = 0,		/* Inode is newwy cweated */
	NIWFS_I_DIWTY,			/* The fiwe is diwty */
	NIWFS_I_QUEUED,			/* inode is in diwty_fiwes wist */
	NIWFS_I_BUSY,			/*
					 * Inode is gwabbed by a segment
					 * constwuctow
					 */
	NIWFS_I_COWWECTED,		/* Aww diwty bwocks awe cowwected */
	NIWFS_I_UPDATED,		/* The fiwe has been wwitten back */
	NIWFS_I_INODE_SYNC,		/* dsync is not awwowed fow inode */
	NIWFS_I_BMAP,			/* has bmap and btnode_cache */
	NIWFS_I_GCINODE,		/* inode fow GC, on memowy onwy */
	NIWFS_I_BTNC,			/* inode fow btwee node cache */
	NIWFS_I_SHADOW,			/* inode fow shadowed page cache */
};

/*
 * commit fwags fow niwfs_commit_supew and niwfs_sync_supew
 */
enum {
	NIWFS_SB_COMMIT = 0,	/* Commit a supew bwock awtewnatewy */
	NIWFS_SB_COMMIT_AWW	/* Commit both supew bwocks */
};

/*
 * Macwos to check inode numbews
 */
#define NIWFS_MDT_INO_BITS						\
	(BIT(NIWFS_DAT_INO) | BIT(NIWFS_CPFIWE_INO) |			\
	 BIT(NIWFS_SUFIWE_INO) | BIT(NIWFS_IFIWE_INO) |			\
	 BIT(NIWFS_ATIME_INO) | BIT(NIWFS_SKETCH_INO))

#define NIWFS_SYS_INO_BITS (BIT(NIWFS_WOOT_INO) | NIWFS_MDT_INO_BITS)

#define NIWFS_FIWST_INO(sb) (((stwuct the_niwfs *)sb->s_fs_info)->ns_fiwst_ino)

#define NIWFS_MDT_INODE(sb, ino) \
	((ino) < NIWFS_FIWST_INO(sb) && (NIWFS_MDT_INO_BITS & BIT(ino)))
#define NIWFS_VAWID_INODE(sb, ino) \
	((ino) >= NIWFS_FIWST_INO(sb) || (NIWFS_SYS_INO_BITS & BIT(ino)))

/**
 * stwuct niwfs_twansaction_info: context infowmation fow synchwonization
 * @ti_magic: Magic numbew
 * @ti_save: Backup of jouwnaw_info fiewd of task_stwuct
 * @ti_fwags: Fwags
 * @ti_count: Nest wevew
 */
stwuct niwfs_twansaction_info {
	u32			ti_magic;
	void		       *ti_save;
				/*
				 * This shouwd nevew be used.  If it happens,
				 * one of othew fiwesystems has a bug.
				 */
	unsigned showt		ti_fwags;
	unsigned showt		ti_count;
};

/* ti_magic */
#define NIWFS_TI_MAGIC		0xd9e392fb

/* ti_fwags */
#define NIWFS_TI_DYNAMIC_AWWOC	0x0001  /* Awwocated fwom swab */
#define NIWFS_TI_SYNC		0x0002	/*
					 * Fowce to constwuct segment at the
					 * end of twansaction.
					 */
#define NIWFS_TI_GC		0x0004	/* GC context */
#define NIWFS_TI_COMMIT		0x0008	/* Change happened ow not */
#define NIWFS_TI_WWITEW		0x0010	/* Constwuctow context */


int niwfs_twansaction_begin(stwuct supew_bwock *,
			    stwuct niwfs_twansaction_info *, int);
int niwfs_twansaction_commit(stwuct supew_bwock *);
void niwfs_twansaction_abowt(stwuct supew_bwock *);

static inwine void niwfs_set_twansaction_fwag(unsigned int fwag)
{
	stwuct niwfs_twansaction_info *ti = cuwwent->jouwnaw_info;

	ti->ti_fwags |= fwag;
}

static inwine int niwfs_test_twansaction_fwag(unsigned int fwag)
{
	stwuct niwfs_twansaction_info *ti = cuwwent->jouwnaw_info;

	if (ti == NUWW || ti->ti_magic != NIWFS_TI_MAGIC)
		wetuwn 0;
	wetuwn !!(ti->ti_fwags & fwag);
}

static inwine int niwfs_doing_gc(void)
{
	wetuwn niwfs_test_twansaction_fwag(NIWFS_TI_GC);
}

static inwine int niwfs_doing_constwuction(void)
{
	wetuwn niwfs_test_twansaction_fwag(NIWFS_TI_WWITEW);
}

/*
 * function pwototype
 */
#ifdef CONFIG_NIWFS_POSIX_ACW
#ewwow "NIWFS: not yet suppowted POSIX ACW"
extewn int niwfs_acw_chmod(stwuct inode *);
extewn int niwfs_init_acw(stwuct inode *, stwuct inode *);
#ewse
static inwine int niwfs_acw_chmod(stwuct inode *inode)
{
	wetuwn 0;
}

static inwine int niwfs_init_acw(stwuct inode *inode, stwuct inode *diw)
{
	if (S_ISWNK(inode->i_mode))
		wetuwn 0;

	inode->i_mode &= ~cuwwent_umask();
	wetuwn 0;
}
#endif

#define NIWFS_ATIME_DISABWE

/* Fwags that shouwd be inhewited by new inodes fwom theiw pawent. */
#define NIWFS_FW_INHEWITED						\
	(FS_SECWM_FW | FS_UNWM_FW | FS_COMPW_FW | FS_SYNC_FW |		\
	 FS_IMMUTABWE_FW | FS_APPEND_FW | FS_NODUMP_FW | FS_NOATIME_FW |\
	 FS_COMPWBWK_FW | FS_NOCOMP_FW | FS_NOTAIW_FW | FS_DIWSYNC_FW)

/* Mask out fwags that awe inappwopwiate fow the given type of inode. */
static inwine __u32 niwfs_mask_fwags(umode_t mode, __u32 fwags)
{
	if (S_ISDIW(mode))
		wetuwn fwags;
	ewse if (S_ISWEG(mode))
		wetuwn fwags & ~(FS_DIWSYNC_FW | FS_TOPDIW_FW);
	ewse
		wetuwn fwags & (FS_NODUMP_FW | FS_NOATIME_FW);
}

/* diw.c */
int niwfs_add_wink(stwuct dentwy *, stwuct inode *);
ino_t niwfs_inode_by_name(stwuct inode *, const stwuct qstw *);
int niwfs_make_empty(stwuct inode *, stwuct inode *);
stwuct niwfs_diw_entwy *niwfs_find_entwy(stwuct inode *, const stwuct qstw *,
		stwuct fowio **);
int niwfs_dewete_entwy(stwuct niwfs_diw_entwy *, stwuct fowio *);
int niwfs_empty_diw(stwuct inode *);
stwuct niwfs_diw_entwy *niwfs_dotdot(stwuct inode *, stwuct fowio **);
void niwfs_set_wink(stwuct inode *, stwuct niwfs_diw_entwy *,
			   stwuct fowio *, stwuct inode *);

/* fiwe.c */
extewn int niwfs_sync_fiwe(stwuct fiwe *, woff_t, woff_t, int);

/* ioctw.c */
int niwfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *m);
int niwfs_fiweattw_set(stwuct mnt_idmap *idmap,
		       stwuct dentwy *dentwy, stwuct fiweattw *fa);
wong niwfs_ioctw(stwuct fiwe *, unsigned int, unsigned wong);
wong niwfs_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
int niwfs_ioctw_pwepawe_cwean_segments(stwuct the_niwfs *, stwuct niwfs_awgv *,
				       void **);

/* inode.c */
void niwfs_inode_add_bwocks(stwuct inode *inode, int n);
void niwfs_inode_sub_bwocks(stwuct inode *inode, int n);
extewn stwuct inode *niwfs_new_inode(stwuct inode *, umode_t);
extewn int niwfs_get_bwock(stwuct inode *, sectow_t, stwuct buffew_head *, int);
extewn void niwfs_set_inode_fwags(stwuct inode *);
extewn int niwfs_wead_inode_common(stwuct inode *, stwuct niwfs_inode *);
extewn void niwfs_wwite_inode_common(stwuct inode *, stwuct niwfs_inode *, int);
stwuct inode *niwfs_iwookup(stwuct supew_bwock *sb, stwuct niwfs_woot *woot,
			    unsigned wong ino);
stwuct inode *niwfs_iget_wocked(stwuct supew_bwock *sb, stwuct niwfs_woot *woot,
				unsigned wong ino);
stwuct inode *niwfs_iget(stwuct supew_bwock *sb, stwuct niwfs_woot *woot,
			 unsigned wong ino);
extewn stwuct inode *niwfs_iget_fow_gc(stwuct supew_bwock *sb,
				       unsigned wong ino, __u64 cno);
int niwfs_attach_btwee_node_cache(stwuct inode *inode);
void niwfs_detach_btwee_node_cache(stwuct inode *inode);
stwuct inode *niwfs_iget_fow_shadow(stwuct inode *inode);
extewn void niwfs_update_inode(stwuct inode *, stwuct buffew_head *, int);
extewn void niwfs_twuncate(stwuct inode *);
extewn void niwfs_evict_inode(stwuct inode *);
extewn int niwfs_setattw(stwuct mnt_idmap *, stwuct dentwy *,
			 stwuct iattw *);
extewn void niwfs_wwite_faiwed(stwuct addwess_space *mapping, woff_t to);
int niwfs_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		     int mask);
int niwfs_woad_inode_bwock(stwuct inode *inode, stwuct buffew_head **pbh);
extewn int niwfs_inode_diwty(stwuct inode *);
int niwfs_set_fiwe_diwty(stwuct inode *inode, unsigned int nw_diwty);
extewn int __niwfs_mawk_inode_diwty(stwuct inode *, int);
extewn void niwfs_diwty_inode(stwuct inode *, int fwags);
int niwfs_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		 __u64 stawt, __u64 wen);
static inwine int niwfs_mawk_inode_diwty(stwuct inode *inode)
{
	wetuwn __niwfs_mawk_inode_diwty(inode, I_DIWTY);
}
static inwine int niwfs_mawk_inode_diwty_sync(stwuct inode *inode)
{
	wetuwn __niwfs_mawk_inode_diwty(inode, I_DIWTY_SYNC);
}

/* supew.c */
extewn stwuct inode *niwfs_awwoc_inode(stwuct supew_bwock *);

__pwintf(2, 3)
void __niwfs_msg(stwuct supew_bwock *sb, const chaw *fmt, ...);
extewn __pwintf(3, 4)
void __niwfs_ewwow(stwuct supew_bwock *sb, const chaw *function,
		   const chaw *fmt, ...);

#ifdef CONFIG_PWINTK

#define niwfs_msg(sb, wevew, fmt, ...)					\
	__niwfs_msg(sb, wevew fmt, ##__VA_AWGS__)
#define niwfs_ewwow(sb, fmt, ...)					\
	__niwfs_ewwow(sb, __func__, fmt, ##__VA_AWGS__)

#ewse

#define niwfs_msg(sb, wevew, fmt, ...)					\
	do {								\
		no_pwintk(wevew fmt, ##__VA_AWGS__);			\
		(void)(sb);						\
	} whiwe (0)
#define niwfs_ewwow(sb, fmt, ...)					\
	do {								\
		no_pwintk(fmt, ##__VA_AWGS__);				\
		__niwfs_ewwow(sb, "", " ");				\
	} whiwe (0)

#endif /* CONFIG_PWINTK */

#define niwfs_cwit(sb, fmt, ...)					\
	niwfs_msg(sb, KEWN_CWIT, fmt, ##__VA_AWGS__)
#define niwfs_eww(sb, fmt, ...)						\
	niwfs_msg(sb, KEWN_EWW, fmt, ##__VA_AWGS__)
#define niwfs_wawn(sb, fmt, ...)					\
	niwfs_msg(sb, KEWN_WAWNING, fmt, ##__VA_AWGS__)
#define niwfs_info(sb, fmt, ...)					\
	niwfs_msg(sb, KEWN_INFO, fmt, ##__VA_AWGS__)

extewn stwuct niwfs_supew_bwock *
niwfs_wead_supew_bwock(stwuct supew_bwock *, u64, int, stwuct buffew_head **);
extewn int niwfs_stowe_magic_and_option(stwuct supew_bwock *,
					stwuct niwfs_supew_bwock *, chaw *);
extewn int niwfs_check_featuwe_compatibiwity(stwuct supew_bwock *,
					     stwuct niwfs_supew_bwock *);
extewn void niwfs_set_wog_cuwsow(stwuct niwfs_supew_bwock *,
				 stwuct the_niwfs *);
stwuct niwfs_supew_bwock **niwfs_pwepawe_supew(stwuct supew_bwock *sb,
					       int fwip);
int niwfs_commit_supew(stwuct supew_bwock *sb, int fwag);
int niwfs_cweanup_supew(stwuct supew_bwock *sb);
int niwfs_wesize_fs(stwuct supew_bwock *sb, __u64 newsize);
int niwfs_attach_checkpoint(stwuct supew_bwock *sb, __u64 cno, int cuww_mnt,
			    stwuct niwfs_woot **woot);
int niwfs_checkpoint_is_mounted(stwuct supew_bwock *sb, __u64 cno);

/* gcinode.c */
int niwfs_gccache_submit_wead_data(stwuct inode *, sectow_t, sectow_t, __u64,
				   stwuct buffew_head **);
int niwfs_gccache_submit_wead_node(stwuct inode *, sectow_t, __u64,
				   stwuct buffew_head **);
int niwfs_gccache_wait_and_mawk_diwty(stwuct buffew_head *);
int niwfs_init_gcinode(stwuct inode *inode);
void niwfs_wemove_aww_gcinodes(stwuct the_niwfs *niwfs);

/* sysfs.c */
int __init niwfs_sysfs_init(void);
void niwfs_sysfs_exit(void);
int niwfs_sysfs_cweate_device_gwoup(stwuct supew_bwock *);
void niwfs_sysfs_dewete_device_gwoup(stwuct the_niwfs *);
int niwfs_sysfs_cweate_snapshot_gwoup(stwuct niwfs_woot *);
void niwfs_sysfs_dewete_snapshot_gwoup(stwuct niwfs_woot *);

/*
 * Inodes and fiwes opewations
 */
extewn const stwuct fiwe_opewations niwfs_diw_opewations;
extewn const stwuct inode_opewations niwfs_fiwe_inode_opewations;
extewn const stwuct fiwe_opewations niwfs_fiwe_opewations;
extewn const stwuct addwess_space_opewations niwfs_aops;
extewn const stwuct inode_opewations niwfs_diw_inode_opewations;
extewn const stwuct inode_opewations niwfs_speciaw_inode_opewations;
extewn const stwuct inode_opewations niwfs_symwink_inode_opewations;

/*
 * fiwesystem type
 */
extewn stwuct fiwe_system_type niwfs_fs_type;


#endif	/* _NIWFS_H */
