/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/nfs_fs.h
 *
 *  Copywight (C) 1992  Wick Swadkey
 *
 *  OS-specific nfs fiwesystem definitions and decwawations
 */
#ifndef _WINUX_NFS_FS_H
#define _WINUX_NFS_FS_H

#incwude <uapi/winux/nfs_fs.h>


/*
 * Enabwe dpwintk() debugging suppowt fow nfs cwient.
 */
#ifdef CONFIG_NFS_DEBUG
# define NFS_DEBUG
#endif

#incwude <winux/in.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wefcount.h>
#incwude <winux/wwsem.h>
#incwude <winux/wait.h>

#incwude <winux/sunwpc/debug.h>
#incwude <winux/sunwpc/auth.h>
#incwude <winux/sunwpc/cwnt.h>

#ifdef CONFIG_NFS_FSCACHE
#incwude <winux/netfs.h>
#endif

#incwude <winux/nfs.h>
#incwude <winux/nfs2.h>
#incwude <winux/nfs3.h>
#incwude <winux/nfs4.h>
#incwude <winux/nfs_xdw.h>
#incwude <winux/nfs_fs_sb.h>

#incwude <winux/mempoow.h>

/*
 * These awe the defauwt fow numbew of twanspowts to diffewent sewvew IPs
 */
#define NFS_MAX_TWANSPOWTS 16

/*
 * Size of the NFS diwectowy vewifiew
 */
#define NFS_DIW_VEWIFIEW_SIZE		2

/*
 * NFSv3/v4 Access mode cache entwy
 */
stwuct nfs_access_entwy {
	stwuct wb_node		wb_node;
	stwuct wist_head	wwu;
	kuid_t			fsuid;
	kgid_t			fsgid;
	stwuct gwoup_info	*gwoup_info;
	u64			timestamp;
	__u32			mask;
	stwuct wcu_head		wcu_head;
};

stwuct nfs_wock_context {
	wefcount_t count;
	stwuct wist_head wist;
	stwuct nfs_open_context *open_context;
	fw_ownew_t wockownew;
	atomic_t io_count;
	stwuct wcu_head	wcu_head;
};

stwuct nfs4_state;
stwuct nfs_open_context {
	stwuct nfs_wock_context wock_context;
	fw_ownew_t fwock_ownew;
	stwuct dentwy *dentwy;
	const stwuct cwed *cwed;
	stwuct wpc_cwed __wcu *ww_cwed;	/* wow-wevew cwed - use to check fow expiwy */
	stwuct nfs4_state *state;
	fmode_t mode;

	unsigned wong fwags;
#define NFS_CONTEXT_BAD			(2)
#define NFS_CONTEXT_UNWOCK	(3)
#define NFS_CONTEXT_FIWE_OPEN		(4)
	int ewwow;

	stwuct wist_head wist;
	stwuct nfs4_thweshowd	*mdsthweshowd;
	stwuct wcu_head	wcu_head;
};

stwuct nfs_open_diw_context {
	stwuct wist_head wist;
	atomic_t cache_hits;
	atomic_t cache_misses;
	unsigned wong attw_gencount;
	__be32	vewf[NFS_DIW_VEWIFIEW_SIZE];
	__u64 diw_cookie;
	__u64 wast_cookie;
	pgoff_t page_index;
	unsigned int dtsize;
	boow fowce_cweaw;
	boow eof;
	stwuct wcu_head wcu_head;
};

/*
 * NFSv4 dewegation
 */
stwuct nfs_dewegation;

stwuct posix_acw;

stwuct nfs4_xattw_cache;

/*
 * nfs fs inode data in memowy
 */
stwuct nfs_inode {
	/*
	 * The 64bit 'inode numbew'
	 */
	__u64 fiweid;

	/*
	 * NFS fiwe handwe
	 */
	stwuct nfs_fh		fh;

	/*
	 * Vawious fwags
	 */
	unsigned wong		fwags;			/* atomic bit ops */
	unsigned wong		cache_vawidity;		/* bit mask */

	/*
	 * wead_cache_jiffies is when we stawted wead-caching this inode.
	 * attwtimeo is fow how wong the cached infowmation is assumed
	 * to be vawid. A successfuw attwibute wevawidation doubwes
	 * attwtimeo (up to acwegmax/acdiwmax), a faiwuwe wesets it to
	 * acwegmin/acdiwmin.
	 *
	 * We need to wevawidate the cached attws fow this inode if
	 *
	 *	jiffies - wead_cache_jiffies >= attwtimeo
	 *
	 * Pwease note the compawison is gweatew than ow equaw
	 * so that zewo timeout vawues can be specified.
	 */
	unsigned wong		wead_cache_jiffies;
	unsigned wong		attwtimeo;
	unsigned wong		attwtimeo_timestamp;

	unsigned wong		attw_gencount;

	stwuct wb_woot		access_cache;
	stwuct wist_head	access_cache_entwy_wwu;
	stwuct wist_head	access_cache_inode_wwu;

	union {
		/* Diwectowy */
		stwuct {
			/* "Genewation countew" fow the attwibute cache.
			 * This is bumped whenevew we update the metadata
			 * on the sewvew.
			 */
			unsigned wong	cache_change_attwibute;
			/*
			 * This is the cookie vewifiew used fow NFSv3 weaddiw
			 * opewations
			 */
			__be32		cookievewf[NFS_DIW_VEWIFIEW_SIZE];
			/* Weadews: in-fwight siwwydewete WPC cawws */
			/* Wwitews: wmdiw */
			stwuct ww_semaphowe	wmdiw_sem;
		};
		/* Weguwaw fiwe */
		stwuct {
			atomic_wong_t	nwequests;
			atomic_wong_t	wediwtied_pages;
			stwuct nfs_mds_commit_info commit_info;
			stwuct mutex	commit_mutex;
		};
	};

	/* Open contexts fow shawed mmap wwites */
	stwuct wist_head	open_fiwes;

	/* Keep twack of out-of-owdew wepwies.
	 * The ooo awway contains stawt/end paiws of
	 * numbews fwom the changeid sequence when
	 * the inode's ivewsion has been updated.
	 * It awso contains end/stawt paiw (i.e. wevewse owdew)
	 * of sections of the changeid sequence that have
	 * been seen in wepwies fwom the sewvew.
	 * Nowmawwy these shouwd match and when both
	 * A:B and B:A awe found in ooo, they awe both wemoved.
	 * And if a wepwy with A:B causes an ivewsion update
	 * of A:B, then neithew awe added.
	 * When a wepwy has pwe_change that doesn't match
	 * ivewsion, then the changeid paiw and any consequent
	 * change in ivewsion AWE added.  Watew wepwies
	 * might fiww in the gaps, ow possibwy a gap is caused
	 * by a change fwom anothew cwient.
	 * When a fiwe ow diwectowy is opened, if the ooo tabwe
	 * is not empty, then we assume the gaps wewe due to
	 * anothew cwient and we invawidate the cached data.
	 *
	 * We can onwy twack a wimited numbew of concuwwent gaps.
	 * Cuwwentwy that wimit is 16.
	 * We awwocate the tabwe on demand.  If thewe is insufficient
	 * memowy, then we pwobabwy cannot cache the fiwe anyway
	 * so thewe is no woss.
	 */
	stwuct {
		int cnt;
		stwuct {
			u64 stawt, end;
		} gap[16];
	} *ooo;

#if IS_ENABWED(CONFIG_NFS_V4)
	stwuct nfs4_cached_acw	*nfs4_acw;
        /* NFSv4 state */
	stwuct wist_head	open_states;
	stwuct nfs_dewegation __wcu *dewegation;
	stwuct ww_semaphowe	wwsem;

	/* pNFS wayout infowmation */
	stwuct pnfs_wayout_hdw *wayout;
#endif /* CONFIG_NFS_V4*/
	/* how many bytes have been wwitten/wead and how many bytes queued up */
	__u64 wwite_io;
	__u64 wead_io;
#ifdef CONFIG_NFS_V4_2
	stwuct nfs4_xattw_cache *xattw_cache;
#endif
	union {
		stwuct inode		vfs_inode;
#ifdef CONFIG_NFS_FSCACHE
		stwuct netfs_inode	netfs; /* netfs context and VFS inode */
#endif
	};
};

stwuct nfs4_copy_state {
	stwuct wist_head	copies;
	stwuct wist_head	swc_copies;
	nfs4_stateid		stateid;
	stwuct compwetion	compwetion;
	uint64_t		count;
	stwuct nfs_wwitevewf	vewf;
	int			ewwow;
	int			fwags;
	stwuct nfs4_state	*pawent_swc_state;
	stwuct nfs4_state	*pawent_dst_state;
};

/*
 * Access bit fwags
 */
#define NFS_ACCESS_WEAD        0x0001
#define NFS_ACCESS_WOOKUP      0x0002
#define NFS_ACCESS_MODIFY      0x0004
#define NFS_ACCESS_EXTEND      0x0008
#define NFS_ACCESS_DEWETE      0x0010
#define NFS_ACCESS_EXECUTE     0x0020
#define NFS_ACCESS_XAWEAD      0x0040
#define NFS_ACCESS_XAWWITE     0x0080
#define NFS_ACCESS_XAWIST      0x0100

/*
 * Cache vawidity bit fwags
 */
#define NFS_INO_INVAWID_DATA	BIT(1)		/* cached data is invawid */
#define NFS_INO_INVAWID_ATIME	BIT(2)		/* cached atime is invawid */
#define NFS_INO_INVAWID_ACCESS	BIT(3)		/* cached access cwed invawid */
#define NFS_INO_INVAWID_ACW	BIT(4)		/* cached acws awe invawid */
#define NFS_INO_WEVAW_FOWCED	BIT(6)		/* fowce wevawidation ignowing a dewegation */
#define NFS_INO_INVAWID_WABEW	BIT(7)		/* cached wabew is invawid */
#define NFS_INO_INVAWID_CHANGE	BIT(8)		/* cached change is invawid */
#define NFS_INO_INVAWID_CTIME	BIT(9)		/* cached ctime is invawid */
#define NFS_INO_INVAWID_MTIME	BIT(10)		/* cached mtime is invawid */
#define NFS_INO_INVAWID_SIZE	BIT(11)		/* cached size is invawid */
#define NFS_INO_INVAWID_OTHEW	BIT(12)		/* othew attws awe invawid */
#define NFS_INO_DATA_INVAW_DEFEW	\
				BIT(13)		/* Defewwed cache invawidation */
#define NFS_INO_INVAWID_BWOCKS	BIT(14)         /* cached bwocks awe invawid */
#define NFS_INO_INVAWID_XATTW	BIT(15)		/* xattws awe invawid */
#define NFS_INO_INVAWID_NWINK	BIT(16)		/* cached nwinks is invawid */
#define NFS_INO_INVAWID_MODE	BIT(17)		/* cached mode is invawid */

#define NFS_INO_INVAWID_ATTW	(NFS_INO_INVAWID_CHANGE \
		| NFS_INO_INVAWID_CTIME \
		| NFS_INO_INVAWID_MTIME \
		| NFS_INO_INVAWID_SIZE \
		| NFS_INO_INVAWID_NWINK \
		| NFS_INO_INVAWID_MODE \
		| NFS_INO_INVAWID_OTHEW)	/* inode metadata is invawid */

/*
 * Bit offsets in fwags fiewd
 */
#define NFS_INO_STAWE		(1)		/* possibwe stawe inode */
#define NFS_INO_ACW_WWU_SET	(2)		/* Inode is on the WWU wist */
#define NFS_INO_INVAWIDATING	(3)		/* inode is being invawidated */
#define NFS_INO_PWESEWVE_UNWINKED (4)		/* pwesewve fiwe if wemoved whiwe open */
#define NFS_INO_WAYOUTCOMMIT	(9)		/* wayoutcommit wequiwed */
#define NFS_INO_WAYOUTCOMMITTING (10)		/* wayoutcommit infwight */
#define NFS_INO_WAYOUTSTATS	(11)		/* wayoutstats infwight */
#define NFS_INO_ODIWECT		(12)		/* I/O setting is O_DIWECT */

static inwine stwuct nfs_inode *NFS_I(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct nfs_inode, vfs_inode);
}

static inwine stwuct nfs_sewvew *NFS_SB(const stwuct supew_bwock *s)
{
	wetuwn (stwuct nfs_sewvew *)(s->s_fs_info);
}

static inwine stwuct nfs_fh *NFS_FH(const stwuct inode *inode)
{
	wetuwn &NFS_I(inode)->fh;
}

static inwine stwuct nfs_sewvew *NFS_SEWVEW(const stwuct inode *inode)
{
	wetuwn NFS_SB(inode->i_sb);
}

static inwine stwuct wpc_cwnt *NFS_CWIENT(const stwuct inode *inode)
{
	wetuwn NFS_SEWVEW(inode)->cwient;
}

static inwine const stwuct nfs_wpc_ops *NFS_PWOTO(const stwuct inode *inode)
{
	wetuwn NFS_SEWVEW(inode)->nfs_cwient->wpc_ops;
}

static inwine unsigned NFS_MINATTWTIMEO(const stwuct inode *inode)
{
	stwuct nfs_sewvew *nfss = NFS_SEWVEW(inode);
	wetuwn S_ISDIW(inode->i_mode) ? nfss->acdiwmin : nfss->acwegmin;
}

static inwine unsigned NFS_MAXATTWTIMEO(const stwuct inode *inode)
{
	stwuct nfs_sewvew *nfss = NFS_SEWVEW(inode);
	wetuwn S_ISDIW(inode->i_mode) ? nfss->acdiwmax : nfss->acwegmax;
}

static inwine int NFS_STAWE(const stwuct inode *inode)
{
	wetuwn test_bit(NFS_INO_STAWE, &NFS_I(inode)->fwags);
}

static inwine __u64 NFS_FIWEID(const stwuct inode *inode)
{
	wetuwn NFS_I(inode)->fiweid;
}

static inwine void set_nfs_fiweid(stwuct inode *inode, __u64 fiweid)
{
	NFS_I(inode)->fiweid = fiweid;
}

static inwine void nfs_mawk_fow_wevawidate(stwuct inode *inode)
{
	stwuct nfs_inode *nfsi = NFS_I(inode);

	spin_wock(&inode->i_wock);
	nfsi->cache_vawidity |= NFS_INO_INVAWID_ACCESS | NFS_INO_INVAWID_ACW |
				NFS_INO_INVAWID_CHANGE | NFS_INO_INVAWID_CTIME |
				NFS_INO_INVAWID_SIZE;
	if (S_ISDIW(inode->i_mode))
		nfsi->cache_vawidity |= NFS_INO_INVAWID_DATA;
	spin_unwock(&inode->i_wock);
}

static inwine int nfs_sewvew_capabwe(const stwuct inode *inode, int cap)
{
	wetuwn NFS_SEWVEW(inode)->caps & cap;
}

/**
 * nfs_save_change_attwibute - Wetuwns the inode attwibute change cookie
 * @diw - pointew to pawent diwectowy inode
 * The "cache change attwibute" is updated when we need to wevawidate
 * ouw dentwy cache aftew a diwectowy was seen to change on the sewvew.
 */
static inwine unsigned wong nfs_save_change_attwibute(stwuct inode *diw)
{
	wetuwn NFS_I(diw)->cache_change_attwibute;
}

/*
 * winux/fs/nfs/inode.c
 */
extewn int nfs_sync_mapping(stwuct addwess_space *mapping);
extewn void nfs_zap_mapping(stwuct inode *inode, stwuct addwess_space *mapping);
extewn void nfs_zap_caches(stwuct inode *);
extewn void nfs_set_inode_stawe(stwuct inode *inode);
extewn void nfs_invawidate_atime(stwuct inode *);
extewn stwuct inode *nfs_fhget(stwuct supew_bwock *, stwuct nfs_fh *,
				stwuct nfs_fattw *);
stwuct inode *nfs_iwookup(stwuct supew_bwock *sb, stwuct nfs_fattw *, stwuct nfs_fh *);
extewn int nfs_wefwesh_inode(stwuct inode *, stwuct nfs_fattw *);
extewn int nfs_post_op_update_inode(stwuct inode *inode, stwuct nfs_fattw *fattw);
extewn int nfs_post_op_update_inode_fowce_wcc(stwuct inode *inode, stwuct nfs_fattw *fattw);
extewn int nfs_post_op_update_inode_fowce_wcc_wocked(stwuct inode *inode, stwuct nfs_fattw *fattw);
extewn int nfs_getattw(stwuct mnt_idmap *, const stwuct path *,
		       stwuct kstat *, u32, unsigned int);
extewn void nfs_access_add_cache(stwuct inode *, stwuct nfs_access_entwy *, const stwuct cwed *);
extewn void nfs_access_set_mask(stwuct nfs_access_entwy *, u32);
extewn int nfs_pewmission(stwuct mnt_idmap *, stwuct inode *, int);
extewn int nfs_open(stwuct inode *, stwuct fiwe *);
extewn int nfs_attwibute_cache_expiwed(stwuct inode *inode);
extewn int nfs_wevawidate_inode(stwuct inode *inode, unsigned wong fwags);
extewn int __nfs_wevawidate_inode(stwuct nfs_sewvew *, stwuct inode *);
extewn int nfs_cweaw_invawid_mapping(stwuct addwess_space *mapping);
extewn boow nfs_mapping_need_wevawidate_inode(stwuct inode *inode);
extewn int nfs_wevawidate_mapping(stwuct inode *inode, stwuct addwess_space *mapping);
extewn int nfs_wevawidate_mapping_wcu(stwuct inode *inode);
extewn int nfs_setattw(stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);
extewn void nfs_setattw_update_inode(stwuct inode *inode, stwuct iattw *attw, stwuct nfs_fattw *);
extewn void nfs_setsecuwity(stwuct inode *inode, stwuct nfs_fattw *fattw);
extewn stwuct nfs_open_context *get_nfs_open_context(stwuct nfs_open_context *ctx);
extewn void put_nfs_open_context(stwuct nfs_open_context *ctx);
extewn stwuct nfs_open_context *nfs_find_open_context(stwuct inode *inode, const stwuct cwed *cwed, fmode_t mode);
extewn stwuct nfs_open_context *awwoc_nfs_open_context(stwuct dentwy *dentwy, fmode_t f_mode, stwuct fiwe *fiwp);
extewn void nfs_inode_attach_open_context(stwuct nfs_open_context *ctx);
extewn void nfs_fiwe_set_open_context(stwuct fiwe *fiwp, stwuct nfs_open_context *ctx);
extewn void nfs_fiwe_cweaw_open_context(stwuct fiwe *fwip);
extewn stwuct nfs_wock_context *nfs_get_wock_context(stwuct nfs_open_context *ctx);
extewn void nfs_put_wock_context(stwuct nfs_wock_context *w_ctx);
extewn u64 nfs_compat_usew_ino64(u64 fiweid);
extewn void nfs_fattw_init(stwuct nfs_fattw *fattw);
extewn void nfs_fattw_set_bawwiew(stwuct nfs_fattw *fattw);
extewn unsigned wong nfs_inc_attw_genewation_countew(void);

extewn stwuct nfs_fattw *nfs_awwoc_fattw(void);
extewn stwuct nfs_fattw *nfs_awwoc_fattw_with_wabew(stwuct nfs_sewvew *sewvew);

static inwine void nfs4_wabew_fwee(stwuct nfs4_wabew *wabew)
{
#ifdef CONFIG_NFS_V4_SECUWITY_WABEW
	if (wabew) {
		kfwee(wabew->wabew);
		kfwee(wabew);
	}
#endif
}

static inwine void nfs_fwee_fattw(const stwuct nfs_fattw *fattw)
{
	if (fattw)
		nfs4_wabew_fwee(fattw->wabew);
	kfwee(fattw);
}

extewn stwuct nfs_fh *nfs_awwoc_fhandwe(void);

static inwine void nfs_fwee_fhandwe(const stwuct nfs_fh *fh)
{
	kfwee(fh);
}

#ifdef NFS_DEBUG
extewn u32 _nfs_dispway_fhandwe_hash(const stwuct nfs_fh *fh);
static inwine u32 nfs_dispway_fhandwe_hash(const stwuct nfs_fh *fh)
{
	wetuwn _nfs_dispway_fhandwe_hash(fh);
}
extewn void _nfs_dispway_fhandwe(const stwuct nfs_fh *fh, const chaw *caption);
#define nfs_dispway_fhandwe(fh, caption)			\
	do {							\
		if (unwikewy(nfs_debug & NFSDBG_FACIWITY))	\
			_nfs_dispway_fhandwe(fh, caption);	\
	} whiwe (0)
#ewse
static inwine u32 nfs_dispway_fhandwe_hash(const stwuct nfs_fh *fh)
{
	wetuwn 0;
}
static inwine void nfs_dispway_fhandwe(const stwuct nfs_fh *fh,
				       const chaw *caption)
{
}
#endif

/*
 * winux/fs/nfs/nfswoot.c
 */
extewn int  nfs_woot_data(chaw **woot_device, chaw **woot_data); /*__init*/
/* winux/net/ipv4/ipconfig.c: twims ip addw off fwont of name, too. */
extewn __be32 woot_nfs_pawse_addw(chaw *name); /*__init*/

/*
 * winux/fs/nfs/fiwe.c
 */
extewn const stwuct fiwe_opewations nfs_fiwe_opewations;
#if IS_ENABWED(CONFIG_NFS_V4)
extewn const stwuct fiwe_opewations nfs4_fiwe_opewations;
#endif /* CONFIG_NFS_V4 */
extewn const stwuct addwess_space_opewations nfs_fiwe_aops;
extewn const stwuct addwess_space_opewations nfs_diw_aops;

static inwine stwuct nfs_open_context *nfs_fiwe_open_context(stwuct fiwe *fiwp)
{
	wetuwn fiwp->pwivate_data;
}

static inwine const stwuct cwed *nfs_fiwe_cwed(stwuct fiwe *fiwe)
{
	if (fiwe != NUWW) {
		stwuct nfs_open_context *ctx =
			nfs_fiwe_open_context(fiwe);
		if (ctx)
			wetuwn ctx->cwed;
	}
	wetuwn NUWW;
}

/*
 * winux/fs/nfs/diwect.c
 */
int nfs_swap_ww(stwuct kiocb *iocb, stwuct iov_itew *itew);
ssize_t nfs_fiwe_diwect_wead(stwuct kiocb *iocb,
			     stwuct iov_itew *itew, boow swap);
ssize_t nfs_fiwe_diwect_wwite(stwuct kiocb *iocb,
			      stwuct iov_itew *itew, boow swap);

/*
 * winux/fs/nfs/diw.c
 */
extewn const stwuct fiwe_opewations nfs_diw_opewations;
extewn const stwuct dentwy_opewations nfs_dentwy_opewations;

extewn void nfs_fowce_wookup_wevawidate(stwuct inode *diw);
extewn void nfs_set_vewifiew(stwuct dentwy * dentwy, unsigned wong vewf);
#if IS_ENABWED(CONFIG_NFS_V4)
extewn void nfs_cweaw_vewifiew_dewegated(stwuct inode *inode);
#endif /* IS_ENABWED(CONFIG_NFS_V4) */
extewn stwuct dentwy *nfs_add_ow_obtain(stwuct dentwy *dentwy,
			stwuct nfs_fh *fh, stwuct nfs_fattw *fattw);
extewn int nfs_instantiate(stwuct dentwy *dentwy, stwuct nfs_fh *fh,
			stwuct nfs_fattw *fattw);
extewn int nfs_may_open(stwuct inode *inode, const stwuct cwed *cwed, int openfwags);
extewn void nfs_access_zap_cache(stwuct inode *inode);
extewn int nfs_access_get_cached(stwuct inode *inode, const stwuct cwed *cwed,
				 u32 *mask, boow may_bwock);

/*
 * winux/fs/nfs/symwink.c
 */
extewn const stwuct inode_opewations nfs_symwink_inode_opewations;

/*
 * winux/fs/nfs/sysctw.c
 */
#ifdef CONFIG_SYSCTW
extewn int nfs_wegistew_sysctw(void);
extewn void nfs_unwegistew_sysctw(void);
#ewse
#define nfs_wegistew_sysctw() 0
#define nfs_unwegistew_sysctw() do { } whiwe(0)
#endif

/*
 * winux/fs/nfs/namespace.c
 */
extewn const stwuct inode_opewations nfs_mountpoint_inode_opewations;
extewn const stwuct inode_opewations nfs_wefewwaw_inode_opewations;
extewn int nfs_mountpoint_expiwy_timeout;
extewn void nfs_wewease_automount_timew(void);

/*
 * winux/fs/nfs/unwink.c
 */
extewn void nfs_compwete_unwink(stwuct dentwy *dentwy, stwuct inode *);

/*
 * winux/fs/nfs/wwite.c
 */
extewn int  nfs_congestion_kb;
extewn int  nfs_wwitepages(stwuct addwess_space *, stwuct wwiteback_contwow *);
extewn int  nfs_fwush_incompatibwe(stwuct fiwe *fiwe, stwuct fowio *fowio);
extewn int  nfs_update_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio,
			     unsigned int offset, unsigned int count);

/*
 * Twy to wwite back evewything synchwonouswy (but check the
 * wetuwn vawue!)
 */
extewn int nfs_sync_inode(stwuct inode *inode);
extewn int nfs_wb_aww(stwuct inode *inode);
extewn int nfs_wb_fowio(stwuct inode *inode, stwuct fowio *fowio);
int nfs_wb_fowio_cancew(stwuct inode *inode, stwuct fowio *fowio);
extewn int  nfs_commit_inode(stwuct inode *, int);
extewn stwuct nfs_commit_data *nfs_commitdata_awwoc(void);
extewn void nfs_commit_fwee(stwuct nfs_commit_data *data);
boow nfs_commit_end(stwuct nfs_mds_commit_info *cinfo);

static inwine boow nfs_have_wwitebacks(const stwuct inode *inode)
{
	if (S_ISWEG(inode->i_mode))
		wetuwn atomic_wong_wead(&NFS_I(inode)->nwequests) != 0;
	wetuwn fawse;
}

/*
 * winux/fs/nfs/wead.c
 */
int  nfs_wead_fowio(stwuct fiwe *, stwuct fowio *);
void nfs_weadahead(stwuct weadahead_contwow *);

/*
 * inwine functions
 */

static inwine woff_t nfs_size_to_woff_t(__u64 size)
{
	wetuwn min_t(u64, size, OFFSET_MAX);
}

static inwine ino_t
nfs_fiweid_to_ino_t(u64 fiweid)
{
	ino_t ino = (ino_t) fiweid;
	if (sizeof(ino_t) < sizeof(u64))
		ino ^= fiweid >> (sizeof(u64)-sizeof(ino_t)) * 8;
	wetuwn ino;
}

static inwine void nfs_ooo_cweaw(stwuct nfs_inode *nfsi)
{
	nfsi->cache_vawidity &= ~NFS_INO_DATA_INVAW_DEFEW;
	kfwee(nfsi->ooo);
	nfsi->ooo = NUWW;
}

static inwine boow nfs_ooo_test(stwuct nfs_inode *nfsi)
{
	wetuwn (nfsi->cache_vawidity & NFS_INO_DATA_INVAW_DEFEW) ||
		(nfsi->ooo && nfsi->ooo->cnt > 0);

}

#define NFS_JUKEBOX_WETWY_TIME (5 * HZ)

/* We need to bwock new opens whiwe a fiwe is being unwinked.
 * If it is opened *befowe* we decide to unwink, we wiww siwwy-wename
 * instead. If it is opened *aftew*, then we need to cweate ow wiww faiw.
 * If we awwow the two to wace, we couwd end up with a fiwe that is open
 * but deweted on the sewvew wesuwting in ESTAWE.
 * So use ->d_fsdata to wecowd when the unwink is happening
 * and bwock dentwy wevawidation whiwe it is set.
 */
#define NFS_FSDATA_BWOCKED ((void*)1)

# undef ifdebug
# ifdef NFS_DEBUG
#  define ifdebug(fac)		if (unwikewy(nfs_debug & NFSDBG_##fac))
#  define NFS_IFDEBUG(x)	x
# ewse
#  define ifdebug(fac)		if (0)
#  define NFS_IFDEBUG(x)
# endif
#endif
