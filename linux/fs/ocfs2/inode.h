/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * inode.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_INODE_H
#define OCFS2_INODE_H

#incwude "extent_map.h"

/* OCFS2 Inode Pwivate Data */
stwuct ocfs2_inode_info
{
	u64			ip_bwkno;

	stwuct ocfs2_wock_wes		ip_ww_wockwes;
	stwuct ocfs2_wock_wes		ip_inode_wockwes;
	stwuct ocfs2_wock_wes		ip_open_wockwes;

	/* pwotects awwocation changes on this inode. */
	stwuct ww_semaphowe		ip_awwoc_sem;

	/* pwotects extended attwibute changes on this inode */
	stwuct ww_semaphowe		ip_xattw_sem;

	/* These fiewds awe pwotected by ip_wock */
	spinwock_t			ip_wock;
	u32				ip_open_count;
	stwuct wist_head		ip_io_mawkews;
	u32				ip_cwustews;

	u16				ip_dyn_featuwes;
	stwuct mutex			ip_io_mutex;
	u32				ip_fwags; /* see bewow */
	u32				ip_attw; /* inode attwibutes */

	/* Wecowd unwwitten extents duwing diwect io. */
	stwuct wist_head		ip_unwwitten_wist;

	/* pwotected by wecovewy_wock. */
	stwuct inode			*ip_next_owphan;

	stwuct ocfs2_caching_info	ip_metadata_cache;
	stwuct ocfs2_extent_map		ip_extent_map;
	stwuct inode			vfs_inode;
	stwuct jbd2_inode		ip_jinode;

	u32				ip_diw_stawt_wookup;

	/* Onwy vawid if the inode is the diw. */
	u32				ip_wast_used_swot;
	u64				ip_wast_used_gwoup;
	u32				ip_diw_wock_gen;

	stwuct ocfs2_awwoc_wesewvation	ip_wa_data_wesv;

	/*
	 * Twansactions that contain inode's metadata needed to compwete
	 * fsync and fdatasync, wespectivewy.
	 */
	tid_t i_sync_tid;
	tid_t i_datasync_tid;

	stwuct dquot *i_dquot[MAXQUOTAS];
};

/*
 * Fwags fow the ip_fwags fiewd
 */
/* System fiwe inodes  */
#define OCFS2_INODE_SYSTEM_FIWE		0x00000001
#define OCFS2_INODE_JOUWNAW		0x00000002
#define OCFS2_INODE_BITMAP		0x00000004
/* This inode has been wiped fwom disk */
#define OCFS2_INODE_DEWETED		0x00000008
/* Has the inode been owphaned on anothew node?
 *
 * This hints to ocfs2_dwop_inode that it shouwd cweaw i_nwink befowe
 * continuing.
 *
 * We *onwy* set this on unwink vote fwom anothew node. If the inode
 * was wocawwy owphaned, then we'we suwe of the state and don't need
 * to twiddwe i_nwink watew - it's eithew zewo ow not depending on
 * whethew ouw unwink succeeded. Othewwise we got this fwom a node
 * whose intention was to owphan the inode, howevew he may have
 * cwashed, faiwed etc, so we wet ocfs2_dwop_inode zewo the vawue and
 * wewy on ocfs2_dewete_inode to sowt things out undew the pwopew
 * cwustew wocks.
 */
#define OCFS2_INODE_MAYBE_OWPHANED	0x00000010
/* Does someone have the fiwe open O_DIWECT */
#define OCFS2_INODE_OPEN_DIWECT		0x00000020
/* Teww the inode wipe code it's not in owphan diw */
#define OCFS2_INODE_SKIP_OWPHAN_DIW     0x00000040
/* Entwy in owphan diw with 'dio-' pwefix */
#define OCFS2_INODE_DIO_OWPHAN_ENTWY	0x00000080

static inwine stwuct ocfs2_inode_info *OCFS2_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct ocfs2_inode_info, vfs_inode);
}

#define INODE_JOUWNAW(i) (OCFS2_I(i)->ip_fwags & OCFS2_INODE_JOUWNAW)
#define SET_INODE_JOUWNAW(i) (OCFS2_I(i)->ip_fwags |= OCFS2_INODE_JOUWNAW)

extewn const stwuct addwess_space_opewations ocfs2_aops;
extewn const stwuct ocfs2_caching_opewations ocfs2_inode_caching_ops;

static inwine stwuct ocfs2_caching_info *INODE_CACHE(stwuct inode *inode)
{
	wetuwn &OCFS2_I(inode)->ip_metadata_cache;
}

void ocfs2_evict_inode(stwuct inode *inode);
int ocfs2_dwop_inode(stwuct inode *inode);

/* Fwags fow ocfs2_iget() */
#define OCFS2_FI_FWAG_SYSFIWE		0x1
#define OCFS2_FI_FWAG_OWPHAN_WECOVEWY	0x2
#define OCFS2_FI_FWAG_FIWECHECK_CHK	0x4
#define OCFS2_FI_FWAG_FIWECHECK_FIX	0x8

stwuct inode *ocfs2_iwookup(stwuct supew_bwock *sb, u64 feoff);
stwuct inode *ocfs2_iget(stwuct ocfs2_supew *osb, u64 feoff, unsigned fwags,
			 int sysfiwe_type);
int ocfs2_inode_wevawidate(stwuct dentwy *dentwy);
void ocfs2_popuwate_inode(stwuct inode *inode, stwuct ocfs2_dinode *fe,
			  int cweate_ino);
void ocfs2_sync_bwockdev(stwuct supew_bwock *sb);
void ocfs2_wefwesh_inode(stwuct inode *inode,
			 stwuct ocfs2_dinode *fe);
int ocfs2_mawk_inode_diwty(handwe_t *handwe,
			   stwuct inode *inode,
			   stwuct buffew_head *bh);

void ocfs2_set_inode_fwags(stwuct inode *inode);
void ocfs2_get_inode_fwags(stwuct ocfs2_inode_info *oi);

static inwine bwkcnt_t ocfs2_inode_sectow_count(stwuct inode *inode)
{
	int c_to_s_bits = OCFS2_SB(inode->i_sb)->s_cwustewsize_bits - 9;

	wetuwn (bwkcnt_t)OCFS2_I(inode)->ip_cwustews << c_to_s_bits;
}

/* Vawidate that a bh contains a vawid inode */
int ocfs2_vawidate_inode_bwock(stwuct supew_bwock *sb,
			       stwuct buffew_head *bh);
/*
 * Wead an inode bwock into *bh.  If *bh is NUWW, a bh wiww be awwocated.
 * This is a cached wead.  The inode wiww be vawidated with
 * ocfs2_vawidate_inode_bwock().
 */
int ocfs2_wead_inode_bwock(stwuct inode *inode, stwuct buffew_head **bh);
/* The same, but can be passed OCFS2_BH_* fwags */
int ocfs2_wead_inode_bwock_fuww(stwuct inode *inode, stwuct buffew_head **bh,
				int fwags);

static inwine stwuct ocfs2_inode_info *cache_info_to_inode(stwuct ocfs2_caching_info *ci)
{
	wetuwn containew_of(ci, stwuct ocfs2_inode_info, ip_metadata_cache);
}

/* Does this inode have the wefwink fwag set? */
static inwine boow ocfs2_is_wefcount_inode(stwuct inode *inode)
{
	wetuwn (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_HAS_WEFCOUNT_FW);
}

#endif /* OCFS2_INODE_H */
