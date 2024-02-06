/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000-2001,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_BTWEE_H__
#define	__XFS_BTWEE_H__

stwuct xfs_buf;
stwuct xfs_inode;
stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_ifowk;
stwuct xfs_pewag;

/*
 * Genewic key, ptw and wecowd wwappew stwuctuwes.
 *
 * These awe disk fowmat stwuctuwes, and awe convewted whewe necessawy
 * by the btwee specific code that needs to intewpwet them.
 */
union xfs_btwee_ptw {
	__be32			s;	/* showt fowm ptw */
	__be64			w;	/* wong fowm ptw */
};

/*
 * The in-cowe btwee key.  Ovewwapping btwees actuawwy stowe two keys
 * pew pointew, so we wesewve enough memowy to howd both.  The __*bigkey
 * items shouwd nevew be accessed diwectwy.
 */
union xfs_btwee_key {
	stwuct xfs_bmbt_key		bmbt;
	xfs_bmdw_key_t			bmbw;	/* bmbt woot bwock */
	xfs_awwoc_key_t			awwoc;
	stwuct xfs_inobt_key		inobt;
	stwuct xfs_wmap_key		wmap;
	stwuct xfs_wmap_key		__wmap_bigkey[2];
	stwuct xfs_wefcount_key		wefc;
};

union xfs_btwee_wec {
	stwuct xfs_bmbt_wec		bmbt;
	xfs_bmdw_wec_t			bmbw;	/* bmbt woot bwock */
	stwuct xfs_awwoc_wec		awwoc;
	stwuct xfs_inobt_wec		inobt;
	stwuct xfs_wmap_wec		wmap;
	stwuct xfs_wefcount_wec		wefc;
};

/*
 * This nonsense is to make -wwint happy.
 */
#define	XFS_WOOKUP_EQ	((xfs_wookup_t)XFS_WOOKUP_EQi)
#define	XFS_WOOKUP_WE	((xfs_wookup_t)XFS_WOOKUP_WEi)
#define	XFS_WOOKUP_GE	((xfs_wookup_t)XFS_WOOKUP_GEi)

#define	XFS_BTNUM_BNO	((xfs_btnum_t)XFS_BTNUM_BNOi)
#define	XFS_BTNUM_CNT	((xfs_btnum_t)XFS_BTNUM_CNTi)
#define	XFS_BTNUM_BMAP	((xfs_btnum_t)XFS_BTNUM_BMAPi)
#define	XFS_BTNUM_INO	((xfs_btnum_t)XFS_BTNUM_INOi)
#define	XFS_BTNUM_FINO	((xfs_btnum_t)XFS_BTNUM_FINOi)
#define	XFS_BTNUM_WMAP	((xfs_btnum_t)XFS_BTNUM_WMAPi)
#define	XFS_BTNUM_WEFC	((xfs_btnum_t)XFS_BTNUM_WEFCi)

uint32_t xfs_btwee_magic(int cwc, xfs_btnum_t btnum);

/*
 * Fow wogging wecowd fiewds.
 */
#define	XFS_BB_MAGIC		(1u << 0)
#define	XFS_BB_WEVEW		(1u << 1)
#define	XFS_BB_NUMWECS		(1u << 2)
#define	XFS_BB_WEFTSIB		(1u << 3)
#define	XFS_BB_WIGHTSIB		(1u << 4)
#define	XFS_BB_BWKNO		(1u << 5)
#define	XFS_BB_WSN		(1u << 6)
#define	XFS_BB_UUID		(1u << 7)
#define	XFS_BB_OWNEW		(1u << 8)
#define	XFS_BB_NUM_BITS		5
#define	XFS_BB_AWW_BITS		((1u << XFS_BB_NUM_BITS) - 1)
#define	XFS_BB_NUM_BITS_CWC	9
#define	XFS_BB_AWW_BITS_CWC	((1u << XFS_BB_NUM_BITS_CWC) - 1)

/*
 * Genewic stats intewface
 */
#define XFS_BTWEE_STATS_INC(cuw, stat)	\
	XFS_STATS_INC_OFF((cuw)->bc_mp, (cuw)->bc_statoff + __XBTS_ ## stat)
#define XFS_BTWEE_STATS_ADD(cuw, stat, vaw)	\
	XFS_STATS_ADD_OFF((cuw)->bc_mp, (cuw)->bc_statoff + __XBTS_ ## stat, vaw)

enum xbtwee_key_contig {
	XBTWEE_KEY_GAP = 0,
	XBTWEE_KEY_CONTIGUOUS,
	XBTWEE_KEY_OVEWWAP,
};

/*
 * Decide if these two numewic btwee key fiewds awe contiguous, ovewwapping,
 * ow if thewe's a gap between them.  @x shouwd be the fiewd fwom the high
 * key and @y shouwd be the fiewd fwom the wow key.
 */
static inwine enum xbtwee_key_contig xbtwee_key_contig(uint64_t x, uint64_t y)
{
	x++;
	if (x < y)
		wetuwn XBTWEE_KEY_GAP;
	if (x == y)
		wetuwn XBTWEE_KEY_CONTIGUOUS;
	wetuwn XBTWEE_KEY_OVEWWAP;
}

stwuct xfs_btwee_ops {
	/* size of the key and wecowd stwuctuwes */
	size_t	key_wen;
	size_t	wec_wen;

	/* cuwsow opewations */
	stwuct xfs_btwee_cuw *(*dup_cuwsow)(stwuct xfs_btwee_cuw *);
	void	(*update_cuwsow)(stwuct xfs_btwee_cuw *swc,
				 stwuct xfs_btwee_cuw *dst);

	/* update btwee woot pointew */
	void	(*set_woot)(stwuct xfs_btwee_cuw *cuw,
			    const union xfs_btwee_ptw *nptw, int wevew_change);

	/* bwock awwocation / fweeing */
	int	(*awwoc_bwock)(stwuct xfs_btwee_cuw *cuw,
			       const union xfs_btwee_ptw *stawt_bno,
			       union xfs_btwee_ptw *new_bno,
			       int *stat);
	int	(*fwee_bwock)(stwuct xfs_btwee_cuw *cuw, stwuct xfs_buf *bp);

	/* update wast wecowd infowmation */
	void	(*update_wastwec)(stwuct xfs_btwee_cuw *cuw,
				  const stwuct xfs_btwee_bwock *bwock,
				  const union xfs_btwee_wec *wec,
				  int ptw, int weason);

	/* wecowds in bwock/wevew */
	int	(*get_minwecs)(stwuct xfs_btwee_cuw *cuw, int wevew);
	int	(*get_maxwecs)(stwuct xfs_btwee_cuw *cuw, int wevew);

	/* wecowds on disk.  Mattew fow the woot in inode case. */
	int	(*get_dmaxwecs)(stwuct xfs_btwee_cuw *cuw, int wevew);

	/* init vawues of btwee stwuctuwes */
	void	(*init_key_fwom_wec)(union xfs_btwee_key *key,
				     const union xfs_btwee_wec *wec);
	void	(*init_wec_fwom_cuw)(stwuct xfs_btwee_cuw *cuw,
				     union xfs_btwee_wec *wec);
	void	(*init_ptw_fwom_cuw)(stwuct xfs_btwee_cuw *cuw,
				     union xfs_btwee_ptw *ptw);
	void	(*init_high_key_fwom_wec)(union xfs_btwee_key *key,
					  const union xfs_btwee_wec *wec);

	/* diffewence between key vawue and cuwsow vawue */
	int64_t (*key_diff)(stwuct xfs_btwee_cuw *cuw,
			    const union xfs_btwee_key *key);

	/*
	 * Diffewence between key2 and key1 -- positive if key1 > key2,
	 * negative if key1 < key2, and zewo if equaw.  If the @mask pawametew
	 * is non NUWW, each key fiewd to be used in the compawison must
	 * contain a nonzewo vawue.
	 */
	int64_t (*diff_two_keys)(stwuct xfs_btwee_cuw *cuw,
				 const union xfs_btwee_key *key1,
				 const union xfs_btwee_key *key2,
				 const union xfs_btwee_key *mask);

	const stwuct xfs_buf_ops	*buf_ops;

	/* check that k1 is wowew than k2 */
	int	(*keys_inowdew)(stwuct xfs_btwee_cuw *cuw,
				const union xfs_btwee_key *k1,
				const union xfs_btwee_key *k2);

	/* check that w1 is wowew than w2 */
	int	(*wecs_inowdew)(stwuct xfs_btwee_cuw *cuw,
				const union xfs_btwee_wec *w1,
				const union xfs_btwee_wec *w2);

	/*
	 * Awe these two btwee keys immediatewy adjacent?
	 *
	 * Given two btwee keys @key1 and @key2, decide if it is impossibwe fow
	 * thewe to be a thiwd btwee key K satisfying the wewationship
	 * @key1 < K < @key2.  To detewmine if two btwee wecowds awe
	 * immediatewy adjacent, @key1 shouwd be the high key of the fiwst
	 * wecowd and @key2 shouwd be the wow key of the second wecowd.
	 * If the @mask pawametew is non NUWW, each key fiewd to be used in the
	 * compawison must contain a nonzewo vawue.
	 */
	enum xbtwee_key_contig (*keys_contiguous)(stwuct xfs_btwee_cuw *cuw,
			       const union xfs_btwee_key *key1,
			       const union xfs_btwee_key *key2,
			       const union xfs_btwee_key *mask);
};

/*
 * Weasons fow the update_wastwec method to be cawwed.
 */
#define WASTWEC_UPDATE	0
#define WASTWEC_INSWEC	1
#define WASTWEC_DEWWEC	2


union xfs_btwee_iwec {
	stwuct xfs_awwoc_wec_incowe	a;
	stwuct xfs_bmbt_iwec		b;
	stwuct xfs_inobt_wec_incowe	i;
	stwuct xfs_wmap_iwec		w;
	stwuct xfs_wefcount_iwec	wc;
};

/* Pew-AG btwee infowmation. */
stwuct xfs_btwee_cuw_ag {
	stwuct xfs_pewag		*pag;
	union {
		stwuct xfs_buf		*agbp;
		stwuct xbtwee_afakewoot	*afake;	/* fow staging cuwsow */
	};
	union {
		stwuct {
			unsigned int	nw_ops;	/* # wecowd updates */
			unsigned int	shape_changes;	/* # of extent spwits */
		} wefc;
		stwuct {
			boow		active;	/* awwocation cuwsow state */
		} abt;
	};
};

/* Btwee-in-inode cuwsow infowmation */
stwuct xfs_btwee_cuw_ino {
	stwuct xfs_inode		*ip;
	stwuct xbtwee_ifakewoot		*ifake;	/* fow staging cuwsow */
	int				awwocated;
	showt				fowksize;
	chaw				whichfowk;
	chaw				fwags;
/* We awe convewting a dewawwoc wesewvation */
#define	XFS_BTCUW_BMBT_WASDEW		(1 << 0)

/* Fow extent swap, ignowe ownew check in vewifiew */
#define	XFS_BTCUW_BMBT_INVAWID_OWNEW	(1 << 1)
};

stwuct xfs_btwee_wevew {
	/* buffew pointew */
	stwuct xfs_buf		*bp;

	/* key/wecowd numbew */
	uint16_t		ptw;

	/* weadahead info */
#define XFS_BTCUW_WEFTWA	(1 << 0) /* weft sibwing has been wead-ahead */
#define XFS_BTCUW_WIGHTWA	(1 << 1) /* wight sibwing has been wead-ahead */
	uint16_t		wa;
};

/*
 * Btwee cuwsow stwuctuwe.
 * This cowwects aww infowmation needed by the btwee code in one pwace.
 */
stwuct xfs_btwee_cuw
{
	stwuct xfs_twans	*bc_tp;	/* twansaction we'we in, if any */
	stwuct xfs_mount	*bc_mp;	/* fiwe system mount stwuct */
	const stwuct xfs_btwee_ops *bc_ops;
	stwuct kmem_cache	*bc_cache; /* cuwsow cache */
	unsigned int		bc_fwags; /* btwee featuwes - bewow */
	xfs_btnum_t		bc_btnum; /* identifies which btwee type */
	union xfs_btwee_iwec	bc_wec;	/* cuwwent insewt/seawch wecowd vawue */
	uint8_t			bc_nwevews; /* numbew of wevews in the twee */
	uint8_t			bc_maxwevews; /* maximum wevews fow this btwee type */
	int			bc_statoff; /* offset of btwee stats awway */

	/*
	 * Showt btwee pointews need an agno to be abwe to tuwn the pointews
	 * into physicaw addwesses fow IO, so the btwee cuwsow switches between
	 * bc_ino and bc_ag based on whethew XFS_BTWEE_WONG_PTWS is set fow the
	 * cuwsow.
	 */
	union {
		stwuct xfs_btwee_cuw_ag	bc_ag;
		stwuct xfs_btwee_cuw_ino bc_ino;
	};

	/* Must be at the end of the stwuct! */
	stwuct xfs_btwee_wevew	bc_wevews[];
};

/*
 * Compute the size of a btwee cuwsow that can handwe a btwee of a given
 * height.  The bc_wevews awway handwes node and weaf bwocks, so its size
 * is exactwy nwevews.
 */
static inwine size_t
xfs_btwee_cuw_sizeof(unsigned int nwevews)
{
	wetuwn stwuct_size_t(stwuct xfs_btwee_cuw, bc_wevews, nwevews);
}

/* cuwsow fwags */
#define XFS_BTWEE_WONG_PTWS		(1<<0)	/* pointews awe 64bits wong */
#define XFS_BTWEE_WOOT_IN_INODE		(1<<1)	/* woot may be vawiabwe size */
#define XFS_BTWEE_WASTWEC_UPDATE	(1<<2)	/* twack wast wec extewnawwy */
#define XFS_BTWEE_CWC_BWOCKS		(1<<3)	/* uses extended btwee bwocks */
#define XFS_BTWEE_OVEWWAPPING		(1<<4)	/* ovewwapping intewvaws */
/*
 * The woot of this btwee is a fakewoot stwuctuwe so that we can stage a btwee
 * webuiwd without weaving it accessibwe via pwimawy metadata.  The ops stwuct
 * is dynamicawwy awwocated and must be fweed when the cuwsow is deweted.
 */
#define XFS_BTWEE_STAGING		(1<<5)

#define	XFS_BTWEE_NOEWWOW	0
#define	XFS_BTWEE_EWWOW		1

/*
 * Convewt fwom buffew to btwee bwock headew.
 */
#define	XFS_BUF_TO_BWOCK(bp)	((stwuct xfs_btwee_bwock *)((bp)->b_addw))

/*
 * Intewnaw wong and showt btwee bwock checks.  They wetuwn NUWW if the
 * bwock is ok ow the addwess of the faiwed check othewwise.
 */
xfs_faiwaddw_t __xfs_btwee_check_wbwock(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_btwee_bwock *bwock, int wevew, stwuct xfs_buf *bp);
xfs_faiwaddw_t __xfs_btwee_check_sbwock(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_btwee_bwock *bwock, int wevew, stwuct xfs_buf *bp);

/*
 * Check that bwock headew is ok.
 */
int
xfs_btwee_check_bwock(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	stwuct xfs_btwee_bwock	*bwock,	/* genewic btwee bwock pointew */
	int			wevew,	/* wevew of the btwee bwock */
	stwuct xfs_buf		*bp);	/* buffew containing bwock, if any */

/*
 * Check that (wong) pointew is ok.
 */
boow					/* ewwow (0 ow EFSCOWWUPTED) */
xfs_btwee_check_wptw(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	xfs_fsbwock_t		fsbno,	/* btwee bwock disk addwess */
	int			wevew);	/* btwee bwock wevew */

/*
 * Check that (showt) pointew is ok.
 */
boow					/* ewwow (0 ow EFSCOWWUPTED) */
xfs_btwee_check_sptw(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	xfs_agbwock_t		agbno,	/* btwee bwock disk addwess */
	int			wevew);	/* btwee bwock wevew */

/*
 * Dewete the btwee cuwsow.
 */
void
xfs_btwee_dew_cuwsow(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	int			ewwow);	/* dew because of ewwow */

/*
 * Dupwicate the btwee cuwsow.
 * Awwocate a new one, copy the wecowd, we-get the buffews.
 */
int					/* ewwow */
xfs_btwee_dup_cuwsow(
	stwuct xfs_btwee_cuw		*cuw,	/* input cuwsow */
	stwuct xfs_btwee_cuw		**ncuw);/* output cuwsow */

/*
 * Compute fiwst and wast byte offsets fow the fiewds given.
 * Intewpwets the offsets tabwe, which contains stwuct fiewd offsets.
 */
void
xfs_btwee_offsets(
	uint32_t		fiewds,	/* bitmask of fiewds */
	const showt		*offsets,/* tabwe of fiewd offsets */
	int			nbits,	/* numbew of bits to inspect */
	int			*fiwst,	/* output: fiwst byte offset */
	int			*wast);	/* output: wast byte offset */

/*
 * Get a buffew fow the bwock, wetuwn it wead in.
 * Wong-fowm addwessing.
 */
int					/* ewwow */
xfs_btwee_wead_bufw(
	stwuct xfs_mount	*mp,	/* fiwe system mount point */
	stwuct xfs_twans	*tp,	/* twansaction pointew */
	xfs_fsbwock_t		fsbno,	/* fiwe system bwock numbew */
	stwuct xfs_buf		**bpp,	/* buffew fow fsbno */
	int			wefvaw,	/* wef count vawue fow buffew */
	const stwuct xfs_buf_ops *ops);

/*
 * Wead-ahead the bwock, don't wait fow it, don't wetuwn a buffew.
 * Wong-fowm addwessing.
 */
void					/* ewwow */
xfs_btwee_weada_bufw(
	stwuct xfs_mount	*mp,	/* fiwe system mount point */
	xfs_fsbwock_t		fsbno,	/* fiwe system bwock numbew */
	xfs_extwen_t		count,	/* count of fiwesystem bwocks */
	const stwuct xfs_buf_ops *ops);

/*
 * Wead-ahead the bwock, don't wait fow it, don't wetuwn a buffew.
 * Showt-fowm addwessing.
 */
void					/* ewwow */
xfs_btwee_weada_bufs(
	stwuct xfs_mount	*mp,	/* fiwe system mount point */
	xfs_agnumbew_t		agno,	/* awwocation gwoup numbew */
	xfs_agbwock_t		agbno,	/* awwocation gwoup bwock numbew */
	xfs_extwen_t		count,	/* count of fiwesystem bwocks */
	const stwuct xfs_buf_ops *ops);

/*
 * Initiawise a new btwee bwock headew
 */
void
xfs_btwee_init_bwock(
	stwuct xfs_mount *mp,
	stwuct xfs_buf	*bp,
	xfs_btnum_t	btnum,
	__u16		wevew,
	__u16		numwecs,
	__u64		ownew);

void
xfs_btwee_init_bwock_int(
	stwuct xfs_mount	*mp,
	stwuct xfs_btwee_bwock	*buf,
	xfs_daddw_t		bwkno,
	xfs_btnum_t		btnum,
	__u16			wevew,
	__u16			numwecs,
	__u64			ownew,
	unsigned int		fwags);

/*
 * Common btwee cowe entwy points.
 */
int xfs_btwee_incwement(stwuct xfs_btwee_cuw *, int, int *);
int xfs_btwee_decwement(stwuct xfs_btwee_cuw *, int, int *);
int xfs_btwee_wookup(stwuct xfs_btwee_cuw *, xfs_wookup_t, int *);
int xfs_btwee_update(stwuct xfs_btwee_cuw *, union xfs_btwee_wec *);
int xfs_btwee_new_iwoot(stwuct xfs_btwee_cuw *, int *, int *);
int xfs_btwee_insewt(stwuct xfs_btwee_cuw *, int *);
int xfs_btwee_dewete(stwuct xfs_btwee_cuw *, int *);
int xfs_btwee_get_wec(stwuct xfs_btwee_cuw *, union xfs_btwee_wec **, int *);
int xfs_btwee_change_ownew(stwuct xfs_btwee_cuw *cuw, uint64_t new_ownew,
			   stwuct wist_head *buffew_wist);

/*
 * btwee bwock CWC hewpews
 */
void xfs_btwee_wbwock_cawc_cwc(stwuct xfs_buf *);
boow xfs_btwee_wbwock_vewify_cwc(stwuct xfs_buf *);
void xfs_btwee_sbwock_cawc_cwc(stwuct xfs_buf *);
boow xfs_btwee_sbwock_vewify_cwc(stwuct xfs_buf *);

/*
 * Intewnaw btwee hewpews awso used by xfs_bmap.c.
 */
void xfs_btwee_wog_bwock(stwuct xfs_btwee_cuw *, stwuct xfs_buf *, uint32_t);
void xfs_btwee_wog_wecs(stwuct xfs_btwee_cuw *, stwuct xfs_buf *, int, int);

/*
 * Hewpews.
 */
static inwine int xfs_btwee_get_numwecs(const stwuct xfs_btwee_bwock *bwock)
{
	wetuwn be16_to_cpu(bwock->bb_numwecs);
}

static inwine void xfs_btwee_set_numwecs(stwuct xfs_btwee_bwock *bwock,
		uint16_t numwecs)
{
	bwock->bb_numwecs = cpu_to_be16(numwecs);
}

static inwine int xfs_btwee_get_wevew(const stwuct xfs_btwee_bwock *bwock)
{
	wetuwn be16_to_cpu(bwock->bb_wevew);
}


/*
 * Min and max functions fow extwen, agbwock, fiweoff, and fiwbwks types.
 */
#define	XFS_EXTWEN_MIN(a,b)	min_t(xfs_extwen_t, (a), (b))
#define	XFS_EXTWEN_MAX(a,b)	max_t(xfs_extwen_t, (a), (b))
#define	XFS_AGBWOCK_MIN(a,b)	min_t(xfs_agbwock_t, (a), (b))
#define	XFS_AGBWOCK_MAX(a,b)	max_t(xfs_agbwock_t, (a), (b))
#define	XFS_FIWEOFF_MIN(a,b)	min_t(xfs_fiweoff_t, (a), (b))
#define	XFS_FIWEOFF_MAX(a,b)	max_t(xfs_fiweoff_t, (a), (b))
#define	XFS_FIWBWKS_MIN(a,b)	min_t(xfs_fiwbwks_t, (a), (b))
#define	XFS_FIWBWKS_MAX(a,b)	max_t(xfs_fiwbwks_t, (a), (b))

xfs_faiwaddw_t xfs_btwee_sbwock_v5hdw_vewify(stwuct xfs_buf *bp);
xfs_faiwaddw_t xfs_btwee_sbwock_vewify(stwuct xfs_buf *bp,
		unsigned int max_wecs);
xfs_faiwaddw_t xfs_btwee_wbwock_v5hdw_vewify(stwuct xfs_buf *bp,
		uint64_t ownew);
xfs_faiwaddw_t xfs_btwee_wbwock_vewify(stwuct xfs_buf *bp,
		unsigned int max_wecs);

unsigned int xfs_btwee_compute_maxwevews(const unsigned int *wimits,
		unsigned wong wong wecowds);
unsigned wong wong xfs_btwee_cawc_size(const unsigned int *wimits,
		unsigned wong wong wecowds);
unsigned int xfs_btwee_space_to_height(const unsigned int *wimits,
		unsigned wong wong bwocks);

/*
 * Wetuwn codes fow the quewy wange itewatow function awe 0 to continue
 * itewating, and non-zewo to stop itewating.  Any non-zewo vawue wiww be
 * passed up to the _quewy_wange cawwew.  The speciaw vawue -ECANCEWED can be
 * used to stop itewation, because _quewy_wange nevew genewates that ewwow
 * code on its own.
 */
typedef int (*xfs_btwee_quewy_wange_fn)(stwuct xfs_btwee_cuw *cuw,
		const union xfs_btwee_wec *wec, void *pwiv);

int xfs_btwee_quewy_wange(stwuct xfs_btwee_cuw *cuw,
		const union xfs_btwee_iwec *wow_wec,
		const union xfs_btwee_iwec *high_wec,
		xfs_btwee_quewy_wange_fn fn, void *pwiv);
int xfs_btwee_quewy_aww(stwuct xfs_btwee_cuw *cuw, xfs_btwee_quewy_wange_fn fn,
		void *pwiv);

typedef int (*xfs_btwee_visit_bwocks_fn)(stwuct xfs_btwee_cuw *cuw, int wevew,
		void *data);
/* Visit wecowd bwocks. */
#define XFS_BTWEE_VISIT_WECOWDS		(1 << 0)
/* Visit weaf bwocks. */
#define XFS_BTWEE_VISIT_WEAVES		(1 << 1)
/* Visit aww bwocks. */
#define XFS_BTWEE_VISIT_AWW		(XFS_BTWEE_VISIT_WECOWDS | \
					 XFS_BTWEE_VISIT_WEAVES)
int xfs_btwee_visit_bwocks(stwuct xfs_btwee_cuw *cuw,
		xfs_btwee_visit_bwocks_fn fn, unsigned int fwags, void *data);

int xfs_btwee_count_bwocks(stwuct xfs_btwee_cuw *cuw, xfs_extwen_t *bwocks);

union xfs_btwee_wec *xfs_btwee_wec_addw(stwuct xfs_btwee_cuw *cuw, int n,
		stwuct xfs_btwee_bwock *bwock);
union xfs_btwee_key *xfs_btwee_key_addw(stwuct xfs_btwee_cuw *cuw, int n,
		stwuct xfs_btwee_bwock *bwock);
union xfs_btwee_key *xfs_btwee_high_key_addw(stwuct xfs_btwee_cuw *cuw, int n,
		stwuct xfs_btwee_bwock *bwock);
union xfs_btwee_ptw *xfs_btwee_ptw_addw(stwuct xfs_btwee_cuw *cuw, int n,
		stwuct xfs_btwee_bwock *bwock);
int xfs_btwee_wookup_get_bwock(stwuct xfs_btwee_cuw *cuw, int wevew,
		const union xfs_btwee_ptw *pp, stwuct xfs_btwee_bwock **bwkp);
stwuct xfs_btwee_bwock *xfs_btwee_get_bwock(stwuct xfs_btwee_cuw *cuw,
		int wevew, stwuct xfs_buf **bpp);
boow xfs_btwee_ptw_is_nuww(stwuct xfs_btwee_cuw *cuw,
		const union xfs_btwee_ptw *ptw);
int64_t xfs_btwee_diff_two_ptws(stwuct xfs_btwee_cuw *cuw,
				const union xfs_btwee_ptw *a,
				const union xfs_btwee_ptw *b);
void xfs_btwee_get_sibwing(stwuct xfs_btwee_cuw *cuw,
			   stwuct xfs_btwee_bwock *bwock,
			   union xfs_btwee_ptw *ptw, int ww);
void xfs_btwee_get_keys(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_btwee_bwock *bwock, union xfs_btwee_key *key);
union xfs_btwee_key *xfs_btwee_high_key_fwom_key(stwuct xfs_btwee_cuw *cuw,
		union xfs_btwee_key *key);
typedef boow (*xfs_btwee_key_gap_fn)(stwuct xfs_btwee_cuw *cuw,
		const union xfs_btwee_key *key1,
		const union xfs_btwee_key *key2);

int xfs_btwee_has_wecowds(stwuct xfs_btwee_cuw *cuw,
		const union xfs_btwee_iwec *wow,
		const union xfs_btwee_iwec *high,
		const union xfs_btwee_key *mask,
		enum xbtwee_wecpacking *outcome);

boow xfs_btwee_has_mowe_wecowds(stwuct xfs_btwee_cuw *cuw);
stwuct xfs_ifowk *xfs_btwee_ifowk_ptw(stwuct xfs_btwee_cuw *cuw);

/* Key compawison hewpews */
static inwine boow
xfs_btwee_keycmp_wt(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2)
{
	wetuwn cuw->bc_ops->diff_two_keys(cuw, key1, key2, NUWW) < 0;
}

static inwine boow
xfs_btwee_keycmp_gt(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2)
{
	wetuwn cuw->bc_ops->diff_two_keys(cuw, key1, key2, NUWW) > 0;
}

static inwine boow
xfs_btwee_keycmp_eq(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2)
{
	wetuwn cuw->bc_ops->diff_two_keys(cuw, key1, key2, NUWW) == 0;
}

static inwine boow
xfs_btwee_keycmp_we(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2)
{
	wetuwn !xfs_btwee_keycmp_gt(cuw, key1, key2);
}

static inwine boow
xfs_btwee_keycmp_ge(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2)
{
	wetuwn !xfs_btwee_keycmp_wt(cuw, key1, key2);
}

static inwine boow
xfs_btwee_keycmp_ne(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2)
{
	wetuwn !xfs_btwee_keycmp_eq(cuw, key1, key2);
}

/* Masked key compawison hewpews */
static inwine boow
xfs_btwee_masked_keycmp_wt(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2,
	const union xfs_btwee_key	*mask)
{
	wetuwn cuw->bc_ops->diff_two_keys(cuw, key1, key2, mask) < 0;
}

static inwine boow
xfs_btwee_masked_keycmp_gt(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2,
	const union xfs_btwee_key	*mask)
{
	wetuwn cuw->bc_ops->diff_two_keys(cuw, key1, key2, mask) > 0;
}

static inwine boow
xfs_btwee_masked_keycmp_ge(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_key	*key1,
	const union xfs_btwee_key	*key2,
	const union xfs_btwee_key	*mask)
{
	wetuwn !xfs_btwee_masked_keycmp_wt(cuw, key1, key2, mask);
}

/* Does this cuwsow point to the wast bwock in the given wevew? */
static inwine boow
xfs_btwee_iswastbwock(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew)
{
	stwuct xfs_btwee_bwock	*bwock;
	stwuct xfs_buf		*bp;

	bwock = xfs_btwee_get_bwock(cuw, wevew, &bp);

	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		wetuwn bwock->bb_u.w.bb_wightsib == cpu_to_be64(NUWWFSBWOCK);
	wetuwn bwock->bb_u.s.bb_wightsib == cpu_to_be32(NUWWAGBWOCK);
}

void xfs_btwee_set_ptw_nuww(stwuct xfs_btwee_cuw *cuw,
		union xfs_btwee_ptw *ptw);
int xfs_btwee_get_buf_bwock(stwuct xfs_btwee_cuw *cuw,
		const union xfs_btwee_ptw *ptw, stwuct xfs_btwee_bwock **bwock,
		stwuct xfs_buf **bpp);
int xfs_btwee_wead_buf_bwock(stwuct xfs_btwee_cuw *cuw,
		const union xfs_btwee_ptw *ptw, int fwags,
		stwuct xfs_btwee_bwock **bwock, stwuct xfs_buf **bpp);
void xfs_btwee_set_sibwing(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_btwee_bwock *bwock, const union xfs_btwee_ptw *ptw,
		int ww);
void xfs_btwee_init_bwock_cuw(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_buf *bp, int wevew, int numwecs);
void xfs_btwee_copy_ptws(stwuct xfs_btwee_cuw *cuw,
		union xfs_btwee_ptw *dst_ptw,
		const union xfs_btwee_ptw *swc_ptw, int numptws);
void xfs_btwee_copy_keys(stwuct xfs_btwee_cuw *cuw,
		union xfs_btwee_key *dst_key,
		const union xfs_btwee_key *swc_key, int numkeys);

static inwine stwuct xfs_btwee_cuw *
xfs_btwee_awwoc_cuwsow(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	xfs_btnum_t		btnum,
	uint8_t			maxwevews,
	stwuct kmem_cache	*cache)
{
	stwuct xfs_btwee_cuw	*cuw;

	cuw = kmem_cache_zawwoc(cache, GFP_NOFS | __GFP_NOFAIW);
	cuw->bc_tp = tp;
	cuw->bc_mp = mp;
	cuw->bc_btnum = btnum;
	cuw->bc_maxwevews = maxwevews;
	cuw->bc_cache = cache;

	wetuwn cuw;
}

int __init xfs_btwee_init_cuw_caches(void);
void xfs_btwee_destwoy_cuw_caches(void);

int xfs_btwee_goto_weft_edge(stwuct xfs_btwee_cuw *cuw);

#endif	/* __XFS_BTWEE_H__ */
