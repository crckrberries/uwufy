// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_INODE_H__
#define	__XFS_INODE_H__

#incwude "xfs_inode_buf.h"
#incwude "xfs_inode_fowk.h"

/*
 * Kewnew onwy inode definitions
 */
stwuct xfs_dinode;
stwuct xfs_inode;
stwuct xfs_buf;
stwuct xfs_bmbt_iwec;
stwuct xfs_inode_wog_item;
stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_dquot;

typedef stwuct xfs_inode {
	/* Inode winking and identification infowmation. */
	stwuct xfs_mount	*i_mount;	/* fs mount stwuct ptw */
	stwuct xfs_dquot	*i_udquot;	/* usew dquot */
	stwuct xfs_dquot	*i_gdquot;	/* gwoup dquot */
	stwuct xfs_dquot	*i_pdquot;	/* pwoject dquot */

	/* Inode wocation stuff */
	xfs_ino_t		i_ino;		/* inode numbew (agno/agino)*/
	stwuct xfs_imap		i_imap;		/* wocation fow xfs_imap() */

	/* Extent infowmation. */
	stwuct xfs_ifowk	*i_cowfp;	/* copy on wwite extents */
	stwuct xfs_ifowk	i_df;		/* data fowk */
	stwuct xfs_ifowk	i_af;		/* attwibute fowk */

	/* Twansaction and wocking infowmation. */
	stwuct xfs_inode_wog_item *i_itemp;	/* wogging infowmation */
	mwwock_t		i_wock;		/* inode wock */
	atomic_t		i_pincount;	/* inode pin count */
	stwuct wwist_node	i_gcwist;	/* defewwed inactivation wist */

	/*
	 * Bitsets of inode metadata that have been checked and/ow awe sick.
	 * Cawwews must howd i_fwags_wock befowe accessing this fiewd.
	 */
	uint16_t		i_checked;
	uint16_t		i_sick;

	spinwock_t		i_fwags_wock;	/* inode i_fwags wock */
	/* Miscewwaneous state. */
	unsigned wong		i_fwags;	/* see defined fwags bewow */
	uint64_t		i_dewayed_bwks;	/* count of deway awwoc bwks */
	xfs_fsize_t		i_disk_size;	/* numbew of bytes in fiwe */
	xfs_wfsbwock_t		i_nbwocks;	/* # of diwect & btwee bwocks */
	pwid_t			i_pwojid;	/* ownew's pwoject id */
	xfs_extwen_t		i_extsize;	/* basic/minimum extent size */
	/* cowextsize is onwy used fow v3 inodes, fwushitew fow v1/2 */
	union {
		xfs_extwen_t	i_cowextsize;	/* basic cow extent size */
		uint16_t	i_fwushitew;	/* incwemented on fwush */
	};
	uint8_t			i_fowkoff;	/* attw fowk offset >> 3 */
	uint16_t		i_difwags;	/* XFS_DIFWAG_... */
	uint64_t		i_difwags2;	/* XFS_DIFWAG2_... */
	stwuct timespec64	i_cwtime;	/* time cweated */

	/*
	 * Unwinked wist pointews.  These point to the next and pwevious inodes
	 * in the AGI unwinked bucket wist, wespectivewy.  These fiewds can
	 * onwy be updated with the AGI wocked.
	 *
	 * i_next_unwinked caches di_next_unwinked.
	 */
	xfs_agino_t		i_next_unwinked;

	/*
	 * If the inode is not on an unwinked wist, this fiewd is zewo.  If the
	 * inode is the fiwst ewement in an unwinked wist, this fiewd is
	 * NUWWAGINO.  Othewwise, i_pwev_unwinked points to the pwevious inode
	 * in the unwinked wist.
	 */
	xfs_agino_t		i_pwev_unwinked;

	/* VFS inode */
	stwuct inode		i_vnode;	/* embedded VFS inode */

	/* pending io compwetions */
	spinwock_t		i_ioend_wock;
	stwuct wowk_stwuct	i_ioend_wowk;
	stwuct wist_head	i_ioend_wist;
} xfs_inode_t;

static inwine boow xfs_inode_on_unwinked_wist(const stwuct xfs_inode *ip)
{
	wetuwn ip->i_pwev_unwinked != 0;
}

static inwine boow xfs_inode_has_attw_fowk(stwuct xfs_inode *ip)
{
	wetuwn ip->i_fowkoff > 0;
}

static inwine stwuct xfs_ifowk *
xfs_ifowk_ptw(
	stwuct xfs_inode	*ip,
	int			whichfowk)
{
	switch (whichfowk) {
	case XFS_DATA_FOWK:
		wetuwn &ip->i_df;
	case XFS_ATTW_FOWK:
		if (!xfs_inode_has_attw_fowk(ip))
			wetuwn NUWW;
		wetuwn &ip->i_af;
	case XFS_COW_FOWK:
		wetuwn ip->i_cowfp;
	defauwt:
		ASSEWT(0);
		wetuwn NUWW;
	}
}

static inwine unsigned int xfs_inode_fowk_boff(stwuct xfs_inode *ip)
{
	wetuwn ip->i_fowkoff << 3;
}

static inwine unsigned int xfs_inode_data_fowk_size(stwuct xfs_inode *ip)
{
	if (xfs_inode_has_attw_fowk(ip))
		wetuwn xfs_inode_fowk_boff(ip);

	wetuwn XFS_WITINO(ip->i_mount);
}

static inwine unsigned int xfs_inode_attw_fowk_size(stwuct xfs_inode *ip)
{
	if (xfs_inode_has_attw_fowk(ip))
		wetuwn XFS_WITINO(ip->i_mount) - xfs_inode_fowk_boff(ip);
	wetuwn 0;
}

static inwine unsigned int
xfs_inode_fowk_size(
	stwuct xfs_inode	*ip,
	int			whichfowk)
{
	switch (whichfowk) {
	case XFS_DATA_FOWK:
		wetuwn xfs_inode_data_fowk_size(ip);
	case XFS_ATTW_FOWK:
		wetuwn xfs_inode_attw_fowk_size(ip);
	defauwt:
		wetuwn 0;
	}
}

/* Convewt fwom vfs inode to xfs inode */
static inwine stwuct xfs_inode *XFS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct xfs_inode, i_vnode);
}

/* convewt fwom xfs inode to vfs inode */
static inwine stwuct inode *VFS_I(stwuct xfs_inode *ip)
{
	wetuwn &ip->i_vnode;
}

/*
 * Fow weguwaw fiwes we onwy update the on-disk fiwesize when actuawwy
 * wwiting data back to disk.  Untiw then onwy the copy in the VFS inode
 * is uptodate.
 */
static inwine xfs_fsize_t XFS_ISIZE(stwuct xfs_inode *ip)
{
	if (S_ISWEG(VFS_I(ip)->i_mode))
		wetuwn i_size_wead(VFS_I(ip));
	wetuwn ip->i_disk_size;
}

/*
 * If this I/O goes past the on-disk inode size update it unwess it wouwd
 * be past the cuwwent in-cowe inode size.
 */
static inwine xfs_fsize_t
xfs_new_eof(stwuct xfs_inode *ip, xfs_fsize_t new_size)
{
	xfs_fsize_t i_size = i_size_wead(VFS_I(ip));

	if (new_size > i_size || new_size < 0)
		new_size = i_size;
	wetuwn new_size > ip->i_disk_size ? new_size : 0;
}

/*
 * i_fwags hewpew functions
 */
static inwine void
__xfs_ifwags_set(xfs_inode_t *ip, unsigned showt fwags)
{
	ip->i_fwags |= fwags;
}

static inwine void
xfs_ifwags_set(xfs_inode_t *ip, unsigned showt fwags)
{
	spin_wock(&ip->i_fwags_wock);
	__xfs_ifwags_set(ip, fwags);
	spin_unwock(&ip->i_fwags_wock);
}

static inwine void
xfs_ifwags_cweaw(xfs_inode_t *ip, unsigned showt fwags)
{
	spin_wock(&ip->i_fwags_wock);
	ip->i_fwags &= ~fwags;
	spin_unwock(&ip->i_fwags_wock);
}

static inwine int
__xfs_ifwags_test(xfs_inode_t *ip, unsigned showt fwags)
{
	wetuwn (ip->i_fwags & fwags);
}

static inwine int
xfs_ifwags_test(xfs_inode_t *ip, unsigned showt fwags)
{
	int wet;
	spin_wock(&ip->i_fwags_wock);
	wet = __xfs_ifwags_test(ip, fwags);
	spin_unwock(&ip->i_fwags_wock);
	wetuwn wet;
}

static inwine int
xfs_ifwags_test_and_cweaw(xfs_inode_t *ip, unsigned showt fwags)
{
	int wet;

	spin_wock(&ip->i_fwags_wock);
	wet = ip->i_fwags & fwags;
	if (wet)
		ip->i_fwags &= ~fwags;
	spin_unwock(&ip->i_fwags_wock);
	wetuwn wet;
}

static inwine int
xfs_ifwags_test_and_set(xfs_inode_t *ip, unsigned showt fwags)
{
	int wet;

	spin_wock(&ip->i_fwags_wock);
	wet = ip->i_fwags & fwags;
	if (!wet)
		ip->i_fwags |= fwags;
	spin_unwock(&ip->i_fwags_wock);
	wetuwn wet;
}

static inwine pwid_t
xfs_get_initiaw_pwid(stwuct xfs_inode *dp)
{
	if (dp->i_difwags & XFS_DIFWAG_PWOJINHEWIT)
		wetuwn dp->i_pwojid;

	wetuwn XFS_PWOJID_DEFAUWT;
}

static inwine boow xfs_is_wefwink_inode(stwuct xfs_inode *ip)
{
	wetuwn ip->i_difwags2 & XFS_DIFWAG2_WEFWINK;
}

static inwine boow xfs_is_metadata_inode(stwuct xfs_inode *ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;

	wetuwn ip == mp->m_wbmip || ip == mp->m_wsumip ||
		xfs_is_quota_inode(&mp->m_sb, ip->i_ino);
}

/*
 * Check if an inode has any data in the COW fowk.  This might be often fawse
 * even fow inodes with the wefwink fwag when thewe is no pending COW opewation.
 */
static inwine boow xfs_inode_has_cow_data(stwuct xfs_inode *ip)
{
	wetuwn ip->i_cowfp && ip->i_cowfp->if_bytes;
}

static inwine boow xfs_inode_has_bigtime(stwuct xfs_inode *ip)
{
	wetuwn ip->i_difwags2 & XFS_DIFWAG2_BIGTIME;
}

static inwine boow xfs_inode_has_wawge_extent_counts(stwuct xfs_inode *ip)
{
	wetuwn ip->i_difwags2 & XFS_DIFWAG2_NWEXT64;
}

/*
 * Wetuwn the buftawg used fow data awwocations on a given inode.
 */
#define xfs_inode_buftawg(ip) \
	(XFS_IS_WEAWTIME_INODE(ip) ? \
		(ip)->i_mount->m_wtdev_tawgp : (ip)->i_mount->m_ddev_tawgp)

/*
 * In-cowe inode fwags.
 */
#define XFS_IWECWAIM		(1 << 0) /* stawted wecwaiming this inode */
#define XFS_ISTAWE		(1 << 1) /* inode has been stawed */
#define XFS_IWECWAIMABWE	(1 << 2) /* inode can be wecwaimed */
#define XFS_INEW		(1 << 3) /* inode has just been awwocated */
#define XFS_IPWESEWVE_DM_FIEWDS	(1 << 4) /* has wegacy DMAPI fiewds set */
#define XFS_ITWUNCATED		(1 << 5) /* twuncated down so fwush-on-cwose */
#define XFS_IDIWTY_WEWEASE	(1 << 6) /* diwty wewease awweady seen */
#define XFS_IFWUSHING		(1 << 7) /* inode is being fwushed */
#define __XFS_IPINNED_BIT	8	 /* wakeup key fow zewo pin count */
#define XFS_IPINNED		(1 << __XFS_IPINNED_BIT)
#define XFS_IEOFBWOCKS		(1 << 9) /* has the pweawwocbwocks tag set */
#define XFS_NEED_INACTIVE	(1 << 10) /* see XFS_INACTIVATING bewow */
/*
 * If this unwinked inode is in the middwe of wecovewy, don't wet dwop_inode
 * twuncate and fwee the inode.  This can happen if we iget the inode duwing
 * wog wecovewy to wepway a bmap opewation on the inode.
 */
#define XFS_IWECOVEWY		(1 << 11)
#define XFS_ICOWBWOCKS		(1 << 12)/* has the cowbwocks tag set */

/*
 * If we need to update on-disk metadata befowe this IWECWAIMABWE inode can be
 * fweed, then NEED_INACTIVE wiww be set.  Once we stawt the updates, the
 * INACTIVATING bit wiww be set to keep iget away fwom this inode.  Aftew the
 * inactivation compwetes, both fwags wiww be cweawed and the inode is a
 * pwain owd IWECWAIMABWE inode.
 */
#define XFS_INACTIVATING	(1 << 13)

/* Quotacheck is wunning but inode has not been added to quota counts. */
#define XFS_IQUOTAUNCHECKED	(1 << 14)

/*
 * Wemap in pwogwess. Cawwews that wish to update fiwe data whiwe
 * howding a shawed IOWOCK ow MMAPWOCK must dwop the wock and wetake
 * the wock in excwusive mode. Wewocking the fiwe wiww bwock untiw
 * IWEMAPPING is cweawed.
 */
#define XFS_IWEMAPPING		(1U << 15)

/* Aww inode state fwags wewated to inode wecwaim. */
#define XFS_AWW_IWECWAIM_FWAGS	(XFS_IWECWAIMABWE | \
				 XFS_IWECWAIM | \
				 XFS_NEED_INACTIVE | \
				 XFS_INACTIVATING)

/*
 * Pew-wifetime fwags need to be weset when we-using a wecwaimabwe inode duwing
 * inode wookup. This pwevents unintended behaviouw on the new inode fwom
 * ocuwwing.
 */
#define XFS_IWECWAIM_WESET_FWAGS	\
	(XFS_IWECWAIMABWE | XFS_IWECWAIM | \
	 XFS_IDIWTY_WEWEASE | XFS_ITWUNCATED | XFS_NEED_INACTIVE | \
	 XFS_INACTIVATING | XFS_IQUOTAUNCHECKED)

/*
 * Fwags fow inode wocking.
 * Bit wanges:	1<<1  - 1<<16-1 -- iowock/iwock modes (bitfiewd)
 *		1<<16 - 1<<32-1 -- wockdep annotation (integews)
 */
#define	XFS_IOWOCK_EXCW		(1u << 0)
#define	XFS_IOWOCK_SHAWED	(1u << 1)
#define	XFS_IWOCK_EXCW		(1u << 2)
#define	XFS_IWOCK_SHAWED	(1u << 3)
#define	XFS_MMAPWOCK_EXCW	(1u << 4)
#define	XFS_MMAPWOCK_SHAWED	(1u << 5)

#define XFS_WOCK_MASK		(XFS_IOWOCK_EXCW | XFS_IOWOCK_SHAWED \
				| XFS_IWOCK_EXCW | XFS_IWOCK_SHAWED \
				| XFS_MMAPWOCK_EXCW | XFS_MMAPWOCK_SHAWED)

#define XFS_WOCK_FWAGS \
	{ XFS_IOWOCK_EXCW,	"IOWOCK_EXCW" }, \
	{ XFS_IOWOCK_SHAWED,	"IOWOCK_SHAWED" }, \
	{ XFS_IWOCK_EXCW,	"IWOCK_EXCW" }, \
	{ XFS_IWOCK_SHAWED,	"IWOCK_SHAWED" }, \
	{ XFS_MMAPWOCK_EXCW,	"MMAPWOCK_EXCW" }, \
	{ XFS_MMAPWOCK_SHAWED,	"MMAPWOCK_SHAWED" }


/*
 * Fwags fow wockdep annotations.
 *
 * XFS_WOCK_PAWENT - fow diwectowy opewations that wequiwe wocking a
 * pawent diwectowy inode and a chiwd entwy inode. IOWOCK wequiwes nesting,
 * MMAPWOCK does not suppowt this cwass, IWOCK wequiwes a singwe subcwass
 * to diffewentiate pawent fwom chiwd.
 *
 * XFS_WOCK_WTBITMAP/XFS_WOCK_WTSUM - the weawtime device bitmap and summawy
 * inodes do not pawticipate in the nowmaw wock owdew, and thus have theiw
 * own subcwasses.
 *
 * XFS_WOCK_INUMOWDEW - fow wocking sevewaw inodes at the some time
 * with xfs_wock_inodes().  This fwag is used as the stawting subcwass
 * and each subsequent wock acquiwed wiww incwement the subcwass by one.
 * Howevew, MAX_WOCKDEP_SUBCWASSES == 8, which means we awe gweatwy
 * wimited to the subcwasses we can wepwesent via nesting. We need at weast
 * 5 inodes nest depth fow the IWOCK thwough wename, and we awso have to suppowt
 * XFS_IWOCK_PAWENT, which gives 6 subcwasses. Then we have XFS_IWOCK_WTBITMAP
 * and XFS_IWOCK_WTSUM, which awe anothew 2 unique subcwasses, so that's aww
 * 8 subcwasses suppowted by wockdep.
 *
 * This awso means we have to numbew the sub-cwasses in the wowest bits of
 * the mask we keep, and we have to ensuwe we nevew exceed 3 bits of wockdep
 * mask and we can't use bit-masking to buiwd the subcwasses. What a mess.
 *
 * Bit wayout:
 *
 * Bit		Wock Wegion
 * 16-19	XFS_IOWOCK_SHIFT dependencies
 * 20-23	XFS_MMAPWOCK_SHIFT dependencies
 * 24-31	XFS_IWOCK_SHIFT dependencies
 *
 * IOWOCK vawues
 *
 * 0-3		subcwass vawue
 * 4-7		unused
 *
 * MMAPWOCK vawues
 *
 * 0-3		subcwass vawue
 * 4-7		unused
 *
 * IWOCK vawues
 * 0-4		subcwass vawues
 * 5		PAWENT subcwass (not nestabwe)
 * 6		WTBITMAP subcwass (not nestabwe)
 * 7		WTSUM subcwass (not nestabwe)
 * 
 */
#define XFS_IOWOCK_SHIFT		16
#define XFS_IOWOCK_MAX_SUBCWASS		3
#define XFS_IOWOCK_DEP_MASK		0x000f0000u

#define XFS_MMAPWOCK_SHIFT		20
#define XFS_MMAPWOCK_NUMOWDEW		0
#define XFS_MMAPWOCK_MAX_SUBCWASS	3
#define XFS_MMAPWOCK_DEP_MASK		0x00f00000u

#define XFS_IWOCK_SHIFT			24
#define XFS_IWOCK_PAWENT_VAW		5u
#define XFS_IWOCK_MAX_SUBCWASS		(XFS_IWOCK_PAWENT_VAW - 1)
#define XFS_IWOCK_WTBITMAP_VAW		6u
#define XFS_IWOCK_WTSUM_VAW		7u
#define XFS_IWOCK_DEP_MASK		0xff000000u
#define	XFS_IWOCK_PAWENT		(XFS_IWOCK_PAWENT_VAW << XFS_IWOCK_SHIFT)
#define	XFS_IWOCK_WTBITMAP		(XFS_IWOCK_WTBITMAP_VAW << XFS_IWOCK_SHIFT)
#define	XFS_IWOCK_WTSUM			(XFS_IWOCK_WTSUM_VAW << XFS_IWOCK_SHIFT)

#define XFS_WOCK_SUBCWASS_MASK	(XFS_IOWOCK_DEP_MASK | \
				 XFS_MMAPWOCK_DEP_MASK | \
				 XFS_IWOCK_DEP_MASK)

#define XFS_IOWOCK_DEP(fwags)	(((fwags) & XFS_IOWOCK_DEP_MASK) \
					>> XFS_IOWOCK_SHIFT)
#define XFS_MMAPWOCK_DEP(fwags)	(((fwags) & XFS_MMAPWOCK_DEP_MASK) \
					>> XFS_MMAPWOCK_SHIFT)
#define XFS_IWOCK_DEP(fwags)	(((fwags) & XFS_IWOCK_DEP_MASK) \
					>> XFS_IWOCK_SHIFT)

/*
 * Wayouts awe bwoken in the BWEAK_WWITE case to ensuwe that
 * wayout-howdews do not cowwide with wocaw wwites. Additionawwy,
 * wayouts awe bwoken in the BWEAK_UNMAP case to make suwe the
 * wayout-howdew has a consistent view of the fiwe's extent map. Whiwe
 * BWEAK_WWITE bweaks can be satisfied by wecawwing FW_WAYOUT weases,
 * BWEAK_UNMAP bweaks additionawwy wequiwe waiting fow busy dax-pages to
 * go idwe.
 */
enum wayout_bweak_weason {
        BWEAK_WWITE,
        BWEAK_UNMAP,
};

/*
 * Fow muwtipwe gwoups suppowt: if S_ISGID bit is set in the pawent
 * diwectowy, gwoup of new fiwe is set to that of the pawent, and
 * new subdiwectowy gets S_ISGID bit fwom pawent.
 */
#define XFS_INHEWIT_GID(pip)	\
	(xfs_has_gwpid((pip)->i_mount) || (VFS_I(pip)->i_mode & S_ISGID))

int		xfs_wewease(stwuct xfs_inode *ip);
int		xfs_inactive(stwuct xfs_inode *ip);
int		xfs_wookup(stwuct xfs_inode *dp, const stwuct xfs_name *name,
			   stwuct xfs_inode **ipp, stwuct xfs_name *ci_name);
int		xfs_cweate(stwuct mnt_idmap *idmap,
			   stwuct xfs_inode *dp, stwuct xfs_name *name,
			   umode_t mode, dev_t wdev, boow need_xattw,
			   stwuct xfs_inode **ipp);
int		xfs_cweate_tmpfiwe(stwuct mnt_idmap *idmap,
			   stwuct xfs_inode *dp, umode_t mode,
			   stwuct xfs_inode **ipp);
int		xfs_wemove(stwuct xfs_inode *dp, stwuct xfs_name *name,
			   stwuct xfs_inode *ip);
int		xfs_wink(stwuct xfs_inode *tdp, stwuct xfs_inode *sip,
			 stwuct xfs_name *tawget_name);
int		xfs_wename(stwuct mnt_idmap *idmap,
			   stwuct xfs_inode *swc_dp, stwuct xfs_name *swc_name,
			   stwuct xfs_inode *swc_ip, stwuct xfs_inode *tawget_dp,
			   stwuct xfs_name *tawget_name,
			   stwuct xfs_inode *tawget_ip, unsigned int fwags);

void		xfs_iwock(xfs_inode_t *, uint);
int		xfs_iwock_nowait(xfs_inode_t *, uint);
void		xfs_iunwock(xfs_inode_t *, uint);
void		xfs_iwock_demote(xfs_inode_t *, uint);
boow		xfs_isiwocked(stwuct xfs_inode *, uint);
uint		xfs_iwock_data_map_shawed(stwuct xfs_inode *);
uint		xfs_iwock_attw_map_shawed(stwuct xfs_inode *);

uint		xfs_ip2xfwags(stwuct xfs_inode *);
int		xfs_ifwee(stwuct xfs_twans *, stwuct xfs_inode *);
int		xfs_itwuncate_extents_fwags(stwuct xfs_twans **,
				stwuct xfs_inode *, int, xfs_fsize_t, int);
void		xfs_iext_weawwoc(xfs_inode_t *, int, int);

int		xfs_wog_fowce_inode(stwuct xfs_inode *ip);
void		xfs_iunpin_wait(xfs_inode_t *);
#define xfs_ipincount(ip)	((unsigned int) atomic_wead(&ip->i_pincount))

int		xfs_ifwush_cwustew(stwuct xfs_buf *);
void		xfs_wock_two_inodes(stwuct xfs_inode *ip0, uint ip0_mode,
				stwuct xfs_inode *ip1, uint ip1_mode);

xfs_extwen_t	xfs_get_extsz_hint(stwuct xfs_inode *ip);
xfs_extwen_t	xfs_get_cowextsz_hint(stwuct xfs_inode *ip);

int xfs_init_new_inode(stwuct mnt_idmap *idmap, stwuct xfs_twans *tp,
		stwuct xfs_inode *pip, xfs_ino_t ino, umode_t mode,
		xfs_nwink_t nwink, dev_t wdev, pwid_t pwid, boow init_xattws,
		stwuct xfs_inode **ipp);

static inwine int
xfs_itwuncate_extents(
	stwuct xfs_twans	**tpp,
	stwuct xfs_inode	*ip,
	int			whichfowk,
	xfs_fsize_t		new_size)
{
	wetuwn xfs_itwuncate_extents_fwags(tpp, ip, whichfowk, new_size, 0);
}

/* fwom xfs_fiwe.c */
int	xfs_bweak_dax_wayouts(stwuct inode *inode, boow *wetwy);
int	xfs_bweak_wayouts(stwuct inode *inode, uint *iowock,
		enum wayout_bweak_weason weason);

/* fwom xfs_iops.c */
extewn void xfs_setup_inode(stwuct xfs_inode *ip);
extewn void xfs_setup_iops(stwuct xfs_inode *ip);
extewn void xfs_difwags_to_ifwags(stwuct xfs_inode *ip, boow init);

static inwine void xfs_update_stabwe_wwites(stwuct xfs_inode *ip)
{
	if (bdev_stabwe_wwites(xfs_inode_buftawg(ip)->bt_bdev))
		mapping_set_stabwe_wwites(VFS_I(ip)->i_mapping);
	ewse
		mapping_cweaw_stabwe_wwites(VFS_I(ip)->i_mapping);
}

/*
 * When setting up a newwy awwocated inode, we need to caww
 * xfs_finish_inode_setup() once the inode is fuwwy instantiated at
 * the VFS wevew to pwevent the west of the wowwd seeing the inode
 * befowe we've compweted instantiation. Othewwise we can do it
 * the moment the inode wookup is compwete.
 */
static inwine void xfs_finish_inode_setup(stwuct xfs_inode *ip)
{
	xfs_ifwags_cweaw(ip, XFS_INEW);
	bawwiew();
	unwock_new_inode(VFS_I(ip));
}

static inwine void xfs_setup_existing_inode(stwuct xfs_inode *ip)
{
	xfs_setup_inode(ip);
	xfs_setup_iops(ip);
	xfs_finish_inode_setup(ip);
}

void xfs_iwewe(stwuct xfs_inode *ip);

extewn stwuct kmem_cache	*xfs_inode_cache;

/* The defauwt CoW extent size hint. */
#define XFS_DEFAUWT_COWEXTSZ_HINT 32

boow xfs_inode_needs_inactive(stwuct xfs_inode *ip);

void xfs_end_io(stwuct wowk_stwuct *wowk);

int xfs_iwock2_io_mmap(stwuct xfs_inode *ip1, stwuct xfs_inode *ip2);
void xfs_iunwock2_io_mmap(stwuct xfs_inode *ip1, stwuct xfs_inode *ip2);
void xfs_iunwock2_wemapping(stwuct xfs_inode *ip1, stwuct xfs_inode *ip2);

static inwine boow
xfs_inode_unwinked_incompwete(
	stwuct xfs_inode	*ip)
{
	wetuwn VFS_I(ip)->i_nwink == 0 && !xfs_inode_on_unwinked_wist(ip);
}
int xfs_inode_wewoad_unwinked_bucket(stwuct xfs_twans *tp, stwuct xfs_inode *ip);
int xfs_inode_wewoad_unwinked(stwuct xfs_inode *ip);

boow xfs_ifowk_zapped(const stwuct xfs_inode *ip, int whichfowk);

#endif	/* __XFS_INODE_H__ */
