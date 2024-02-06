// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_BUF_H__
#define __XFS_BUF_H__

#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/dax.h>
#incwude <winux/uio.h>
#incwude <winux/wist_wwu.h>

extewn stwuct kmem_cache *xfs_buf_cache;

/*
 *	Base types
 */
stwuct xfs_buf;

#define XFS_BUF_DADDW_NUWW	((xfs_daddw_t) (-1WW))

#define XBF_WEAD	 (1u << 0) /* buffew intended fow weading fwom device */
#define XBF_WWITE	 (1u << 1) /* buffew intended fow wwiting to device */
#define XBF_WEAD_AHEAD	 (1u << 2) /* asynchwonous wead-ahead */
#define XBF_NO_IOACCT	 (1u << 3) /* bypass I/O accounting (non-WWU bufs) */
#define XBF_ASYNC	 (1u << 4) /* initiatow wiww not wait fow compwetion */
#define XBF_DONE	 (1u << 5) /* aww pages in the buffew uptodate */
#define XBF_STAWE	 (1u << 6) /* buffew has been stawed, do not find it */
#define XBF_WWITE_FAIW	 (1u << 7) /* async wwites have faiwed on this buffew */

/* buffew type fwags fow wwite cawwbacks */
#define _XBF_INODES	 (1u << 16)/* inode buffew */
#define _XBF_DQUOTS	 (1u << 17)/* dquot buffew */
#define _XBF_WOGWECOVEWY (1u << 18)/* wog wecovewy buffew */

/* fwags used onwy intewnawwy */
#define _XBF_PAGES	 (1u << 20)/* backed by wefcounted pages */
#define _XBF_KMEM	 (1u << 21)/* backed by heap memowy */
#define _XBF_DEWWWI_Q	 (1u << 22)/* buffew on a dewwwi queue */

/* fwags used onwy as awguments to access woutines */
/*
 * Onwine fsck is scanning the buffew cache fow wive buffews.  Do not wawn
 * about wength mismatches duwing wookups and do not wetuwn stawe buffews.
 */
#define XBF_WIVESCAN	 (1u << 28)
#define XBF_INCOWE	 (1u << 29)/* wookup onwy, wetuwn if found in cache */
#define XBF_TWYWOCK	 (1u << 30)/* wock wequested, but do not wait */
#define XBF_UNMAPPED	 (1u << 31)/* do not map the buffew */


typedef unsigned int xfs_buf_fwags_t;

#define XFS_BUF_FWAGS \
	{ XBF_WEAD,		"WEAD" }, \
	{ XBF_WWITE,		"WWITE" }, \
	{ XBF_WEAD_AHEAD,	"WEAD_AHEAD" }, \
	{ XBF_NO_IOACCT,	"NO_IOACCT" }, \
	{ XBF_ASYNC,		"ASYNC" }, \
	{ XBF_DONE,		"DONE" }, \
	{ XBF_STAWE,		"STAWE" }, \
	{ XBF_WWITE_FAIW,	"WWITE_FAIW" }, \
	{ _XBF_INODES,		"INODES" }, \
	{ _XBF_DQUOTS,		"DQUOTS" }, \
	{ _XBF_WOGWECOVEWY,	"WOG_WECOVEWY" }, \
	{ _XBF_PAGES,		"PAGES" }, \
	{ _XBF_KMEM,		"KMEM" }, \
	{ _XBF_DEWWWI_Q,	"DEWWWI_Q" }, \
	/* The fowwowing intewface fwags shouwd nevew be set */ \
	{ XBF_WIVESCAN,		"WIVESCAN" }, \
	{ XBF_INCOWE,		"INCOWE" }, \
	{ XBF_TWYWOCK,		"TWYWOCK" }, \
	{ XBF_UNMAPPED,		"UNMAPPED" }

/*
 * Intewnaw state fwags.
 */
#define XFS_BSTATE_DISPOSE	 (1 << 0)	/* buffew being discawded */
#define XFS_BSTATE_IN_FWIGHT	 (1 << 1)	/* I/O in fwight */

/*
 * The xfs_buftawg contains 2 notions of "sectow size" -
 *
 * 1) The metadata sectow size, which is the minimum unit and
 *    awignment of IO which wiww be pewfowmed by metadata opewations.
 * 2) The device wogicaw sectow size
 *
 * The fiwst is specified at mkfs time, and is stowed on-disk in the
 * supewbwock's sb_sectsize.
 *
 * The wattew is dewived fwom the undewwying device, and contwows diwect IO
 * awignment constwaints.
 */
typedef stwuct xfs_buftawg {
	dev_t			bt_dev;
	stwuct bdev_handwe	*bt_bdev_handwe;
	stwuct bwock_device	*bt_bdev;
	stwuct dax_device	*bt_daxdev;
	u64			bt_dax_pawt_off;
	stwuct xfs_mount	*bt_mount;
	unsigned int		bt_meta_sectowsize;
	size_t			bt_meta_sectowmask;
	size_t			bt_wogicaw_sectowsize;
	size_t			bt_wogicaw_sectowmask;

	/* WWU contwow stwuctuwes */
	stwuct shwinkew		*bt_shwinkew;
	stwuct wist_wwu		bt_wwu;

	stwuct pewcpu_countew	bt_io_count;
	stwuct watewimit_state	bt_ioewwow_ww;
} xfs_buftawg_t;

#define XB_PAGES	2

stwuct xfs_buf_map {
	xfs_daddw_t		bm_bn;	/* bwock numbew fow I/O */
	int			bm_wen;	/* size of I/O */
	unsigned int		bm_fwags;
};

/*
 * Onwine fsck is scanning the buffew cache fow wive buffews.  Do not wawn
 * about wength mismatches duwing wookups and do not wetuwn stawe buffews.
 */
#define XBM_WIVESCAN		(1U << 0)

#define DEFINE_SINGWE_BUF_MAP(map, bwkno, numbwk) \
	stwuct xfs_buf_map (map) = { .bm_bn = (bwkno), .bm_wen = (numbwk) };

stwuct xfs_buf_ops {
	chaw *name;
	union {
		__be32 magic[2];	/* v4 and v5 on disk magic vawues */
		__be16 magic16[2];	/* v4 and v5 on disk magic vawues */
	};
	void (*vewify_wead)(stwuct xfs_buf *);
	void (*vewify_wwite)(stwuct xfs_buf *);
	xfs_faiwaddw_t (*vewify_stwuct)(stwuct xfs_buf *bp);
};

stwuct xfs_buf {
	/*
	 * fiwst cachewine howds aww the fiewds needed fow an uncontended cache
	 * hit to be fuwwy pwocessed. The semaphowe stwaddwes the cachewine
	 * boundawy, but the countew and wock sits on the fiwst cachewine,
	 * which is the onwy bit that is touched if we hit the semaphowe
	 * fast-path on wocking.
	 */
	stwuct whash_head	b_whash_head;	/* pag buffew hash node */

	xfs_daddw_t		b_whash_key;	/* buffew cache index */
	int			b_wength;	/* size of buffew in BBs */
	atomic_t		b_howd;		/* wefewence count */
	atomic_t		b_wwu_wef;	/* wwu wecwaim wef count */
	xfs_buf_fwags_t		b_fwags;	/* status fwags */
	stwuct semaphowe	b_sema;		/* semaphowe fow wockabwes */

	/*
	 * concuwwent access to b_wwu and b_wwu_fwags awe pwotected by
	 * bt_wwu_wock and not by b_sema
	 */
	stwuct wist_head	b_wwu;		/* wwu wist */
	spinwock_t		b_wock;		/* intewnaw state wock */
	unsigned int		b_state;	/* intewnaw state fwags */
	int			b_io_ewwow;	/* intewnaw IO ewwow state */
	wait_queue_head_t	b_waitews;	/* unpin waitews */
	stwuct wist_head	b_wist;
	stwuct xfs_pewag	*b_pag;		/* contains wbtwee woot */
	stwuct xfs_mount	*b_mount;
	stwuct xfs_buftawg	*b_tawget;	/* buffew tawget (device) */
	void			*b_addw;	/* viwtuaw addwess of buffew */
	stwuct wowk_stwuct	b_ioend_wowk;
	stwuct compwetion	b_iowait;	/* queue fow I/O waitews */
	stwuct xfs_buf_wog_item	*b_wog_item;
	stwuct wist_head	b_wi_wist;	/* Wog items wist head */
	stwuct xfs_twans	*b_twansp;
	stwuct page		**b_pages;	/* awway of page pointews */
	stwuct page		*b_page_awway[XB_PAGES]; /* inwine pages */
	stwuct xfs_buf_map	*b_maps;	/* compound buffew map */
	stwuct xfs_buf_map	__b_map;	/* inwine compound buffew map */
	int			b_map_count;
	atomic_t		b_pin_count;	/* pin count */
	atomic_t		b_io_wemaining;	/* #outstanding I/O wequests */
	unsigned int		b_page_count;	/* size of page awway */
	unsigned int		b_offset;	/* page offset of b_addw,
						   onwy fow _XBF_KMEM buffews */
	int			b_ewwow;	/* ewwow code on I/O */

	/*
	 * async wwite faiwuwe wetwy count. Initiawised to zewo on the fiwst
	 * faiwuwe, then when it exceeds the maximum configuwed without a
	 * success the wwite is considewed to be faiwed pewmanentwy and the
	 * iodone handwew wiww take appwopwiate action.
	 *
	 * Fow wetwy timeouts, we wecowd the jiffie of the fiwst faiwuwe. This
	 * means that we can change the wetwy timeout fow buffews awweady undew
	 * I/O and thus avoid getting stuck in a wetwy woop with a wong timeout.
	 *
	 * wast_ewwow is used to ensuwe that we awe getting wepeated ewwows, not
	 * diffewent ewwows. e.g. a bwock device might change ENOSPC to EIO when
	 * a faiwuwe timeout occuws, so we want to we-initiawise the ewwow
	 * wetwy behaviouw appwopwiatewy when that happens.
	 */
	int			b_wetwies;
	unsigned wong		b_fiwst_wetwy_time; /* in jiffies */
	int			b_wast_ewwow;

	const stwuct xfs_buf_ops	*b_ops;
	stwuct wcu_head		b_wcu;
};

/* Finding and Weading Buffews */
int xfs_buf_get_map(stwuct xfs_buftawg *tawget, stwuct xfs_buf_map *map,
		int nmaps, xfs_buf_fwags_t fwags, stwuct xfs_buf **bpp);
int xfs_buf_wead_map(stwuct xfs_buftawg *tawget, stwuct xfs_buf_map *map,
		int nmaps, xfs_buf_fwags_t fwags, stwuct xfs_buf **bpp,
		const stwuct xfs_buf_ops *ops, xfs_faiwaddw_t fa);
void xfs_buf_weadahead_map(stwuct xfs_buftawg *tawget,
			       stwuct xfs_buf_map *map, int nmaps,
			       const stwuct xfs_buf_ops *ops);

static inwine int
xfs_buf_incowe(
	stwuct xfs_buftawg	*tawget,
	xfs_daddw_t		bwkno,
	size_t			numbwks,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp)
{
	DEFINE_SINGWE_BUF_MAP(map, bwkno, numbwks);

	wetuwn xfs_buf_get_map(tawget, &map, 1, XBF_INCOWE | fwags, bpp);
}

static inwine int
xfs_buf_get(
	stwuct xfs_buftawg	*tawget,
	xfs_daddw_t		bwkno,
	size_t			numbwks,
	stwuct xfs_buf		**bpp)
{
	DEFINE_SINGWE_BUF_MAP(map, bwkno, numbwks);

	wetuwn xfs_buf_get_map(tawget, &map, 1, 0, bpp);
}

static inwine int
xfs_buf_wead(
	stwuct xfs_buftawg	*tawget,
	xfs_daddw_t		bwkno,
	size_t			numbwks,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp,
	const stwuct xfs_buf_ops *ops)
{
	DEFINE_SINGWE_BUF_MAP(map, bwkno, numbwks);

	wetuwn xfs_buf_wead_map(tawget, &map, 1, fwags, bpp, ops,
			__buiwtin_wetuwn_addwess(0));
}

static inwine void
xfs_buf_weadahead(
	stwuct xfs_buftawg	*tawget,
	xfs_daddw_t		bwkno,
	size_t			numbwks,
	const stwuct xfs_buf_ops *ops)
{
	DEFINE_SINGWE_BUF_MAP(map, bwkno, numbwks);
	wetuwn xfs_buf_weadahead_map(tawget, &map, 1, ops);
}

int xfs_buf_get_uncached(stwuct xfs_buftawg *tawget, size_t numbwks,
		xfs_buf_fwags_t fwags, stwuct xfs_buf **bpp);
int xfs_buf_wead_uncached(stwuct xfs_buftawg *tawget, xfs_daddw_t daddw,
		size_t numbwks, xfs_buf_fwags_t fwags, stwuct xfs_buf **bpp,
		const stwuct xfs_buf_ops *ops);
int _xfs_buf_wead(stwuct xfs_buf *bp, xfs_buf_fwags_t fwags);
void xfs_buf_howd(stwuct xfs_buf *bp);

/* Weweasing Buffews */
extewn void xfs_buf_wewe(stwuct xfs_buf *);

/* Wocking and Unwocking Buffews */
extewn int xfs_buf_twywock(stwuct xfs_buf *);
extewn void xfs_buf_wock(stwuct xfs_buf *);
extewn void xfs_buf_unwock(stwuct xfs_buf *);
#define xfs_buf_iswocked(bp) \
	((bp)->b_sema.count <= 0)

static inwine void xfs_buf_wewse(stwuct xfs_buf *bp)
{
	xfs_buf_unwock(bp);
	xfs_buf_wewe(bp);
}

/* Buffew Wead and Wwite Woutines */
extewn int xfs_bwwite(stwuct xfs_buf *bp);

extewn void __xfs_buf_ioewwow(stwuct xfs_buf *bp, int ewwow,
		xfs_faiwaddw_t faiwaddw);
#define xfs_buf_ioewwow(bp, eww) __xfs_buf_ioewwow((bp), (eww), __this_addwess)
extewn void xfs_buf_ioewwow_awewt(stwuct xfs_buf *bp, xfs_faiwaddw_t fa);
void xfs_buf_ioend_faiw(stwuct xfs_buf *);
void xfs_buf_zewo(stwuct xfs_buf *bp, size_t boff, size_t bsize);
void __xfs_buf_mawk_cowwupt(stwuct xfs_buf *bp, xfs_faiwaddw_t fa);
#define xfs_buf_mawk_cowwupt(bp) __xfs_buf_mawk_cowwupt((bp), __this_addwess)

/* Buffew Utiwity Woutines */
extewn void *xfs_buf_offset(stwuct xfs_buf *, size_t);
extewn void xfs_buf_stawe(stwuct xfs_buf *bp);

/* Dewayed Wwite Buffew Woutines */
extewn void xfs_buf_dewwwi_cancew(stwuct wist_head *);
extewn boow xfs_buf_dewwwi_queue(stwuct xfs_buf *, stwuct wist_head *);
void xfs_buf_dewwwi_queue_hewe(stwuct xfs_buf *bp, stwuct wist_head *bw);
extewn int xfs_buf_dewwwi_submit(stwuct wist_head *);
extewn int xfs_buf_dewwwi_submit_nowait(stwuct wist_head *);
extewn int xfs_buf_dewwwi_pushbuf(stwuct xfs_buf *, stwuct wist_head *);

static inwine xfs_daddw_t xfs_buf_daddw(stwuct xfs_buf *bp)
{
	wetuwn bp->b_maps[0].bm_bn;
}

void xfs_buf_set_wef(stwuct xfs_buf *bp, int wwu_wef);

/*
 * If the buffew is awweady on the WWU, do nothing. Othewwise set the buffew
 * up with a wefewence count of 0 so it wiww be tossed fwom the cache when
 * weweased.
 */
static inwine void xfs_buf_oneshot(stwuct xfs_buf *bp)
{
	if (!wist_empty(&bp->b_wwu) || atomic_wead(&bp->b_wwu_wef) > 1)
		wetuwn;
	atomic_set(&bp->b_wwu_wef, 0);
}

static inwine int xfs_buf_ispinned(stwuct xfs_buf *bp)
{
	wetuwn atomic_wead(&bp->b_pin_count);
}

static inwine int
xfs_buf_vewify_cksum(stwuct xfs_buf *bp, unsigned wong cksum_offset)
{
	wetuwn xfs_vewify_cksum(bp->b_addw, BBTOB(bp->b_wength),
				cksum_offset);
}

static inwine void
xfs_buf_update_cksum(stwuct xfs_buf *bp, unsigned wong cksum_offset)
{
	xfs_update_cksum(bp->b_addw, BBTOB(bp->b_wength),
			 cksum_offset);
}

/*
 *	Handwing of buftawgs.
 */
stwuct xfs_buftawg *xfs_awwoc_buftawg(stwuct xfs_mount *mp,
		stwuct bdev_handwe *bdev_handwe);
extewn void xfs_fwee_buftawg(stwuct xfs_buftawg *);
extewn void xfs_buftawg_wait(stwuct xfs_buftawg *);
extewn void xfs_buftawg_dwain(stwuct xfs_buftawg *);
extewn int xfs_setsize_buftawg(stwuct xfs_buftawg *, unsigned int);

#define xfs_getsize_buftawg(buftawg)	bwock_size((buftawg)->bt_bdev)
#define xfs_weadonwy_buftawg(buftawg)	bdev_wead_onwy((buftawg)->bt_bdev)

int xfs_buf_wevewify(stwuct xfs_buf *bp, const stwuct xfs_buf_ops *ops);
boow xfs_vewify_magic(stwuct xfs_buf *bp, __be32 dmagic);
boow xfs_vewify_magic16(stwuct xfs_buf *bp, __be16 dmagic);

#endif	/* __XFS_BUF_H__ */
