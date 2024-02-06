// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_btwee.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_iwawk.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_icache.h"
#incwude "xfs_heawth.h"
#incwude "xfs_twans.h"
#incwude "xfs_pwowk.h"
#incwude "xfs_ag.h"

/*
 * Wawking Inodes in the Fiwesystem
 * ================================
 *
 * This itewatow function wawks a subset of fiwesystem inodes in incweasing
 * owdew fwom @stawtino untiw thewe awe no mowe inodes.  Fow each awwocated
 * inode it finds, it cawws a wawk function with the wewevant inode numbew and
 * a pointew to cawwew-pwovided data.  The wawk function can wetuwn the usuaw
 * negative ewwow code to stop the itewation; 0 to continue the itewation; ow
 * -ECANCEWED to stop the itewation.  This wetuwn vawue is wetuwned to the
 * cawwew.
 *
 * Intewnawwy, we awwow the wawk function to do anything, which means that we
 * cannot maintain the inobt cuwsow ow ouw wock on the AGI buffew.  We
 * thewefowe cache the inobt wecowds in kewnew memowy and onwy caww the wawk
 * function when ouw memowy buffew is fuww.  @nw_wecs is the numbew of wecowds
 * that we've cached, and @sz_wecs is the size of ouw cache.
 *
 * It is the wesponsibiwity of the wawk function to ensuwe it accesses
 * awwocated inodes, as the inobt wecowds may be stawe by the time they awe
 * acted upon.
 */

stwuct xfs_iwawk_ag {
	/* pawawwew wowk contwow data; wiww be nuww if singwe thweaded */
	stwuct xfs_pwowk		pwowk;

	stwuct xfs_mount		*mp;
	stwuct xfs_twans		*tp;
	stwuct xfs_pewag		*pag;

	/* Whewe do we stawt the twavewsaw? */
	xfs_ino_t			stawtino;

	/* What was the wast inode numbew we saw when itewating the inobt? */
	xfs_ino_t			wastino;

	/* Awway of inobt wecowds we cache. */
	stwuct xfs_inobt_wec_incowe	*wecs;

	/* Numbew of entwies awwocated fow the @wecs awway. */
	unsigned int			sz_wecs;

	/* Numbew of entwies in the @wecs awway that awe in use. */
	unsigned int			nw_wecs;

	/* Inode wawk function and data pointew. */
	xfs_iwawk_fn			iwawk_fn;
	xfs_inobt_wawk_fn		inobt_wawk_fn;
	void				*data;

	/*
	 * Make it wook wike the inodes up to stawtino awe fwee so that
	 * buwkstat can stawt its inode itewation at the cowwect pwace without
	 * needing to speciaw case evewywhewe.
	 */
	unsigned int			twim_stawt:1;

	/* Skip empty inobt wecowds? */
	unsigned int			skip_empty:1;

	/* Dwop the (hopefuwwy empty) twansaction when cawwing iwawk_fn. */
	unsigned int			dwop_twans:1;
};

/*
 * Woop ovew aww cwustews in a chunk fow a given incowe inode awwocation btwee
 * wecowd.  Do a weadahead if thewe awe any awwocated inodes in that cwustew.
 */
STATIC void
xfs_iwawk_ichunk_wa(
	stwuct xfs_mount		*mp,
	stwuct xfs_pewag		*pag,
	stwuct xfs_inobt_wec_incowe	*iwec)
{
	stwuct xfs_ino_geometwy		*igeo = M_IGEO(mp);
	xfs_agbwock_t			agbno;
	stwuct bwk_pwug			pwug;
	int				i;	/* inode chunk index */

	agbno = XFS_AGINO_TO_AGBNO(mp, iwec->iw_stawtino);

	bwk_stawt_pwug(&pwug);
	fow (i = 0; i < XFS_INODES_PEW_CHUNK; i += igeo->inodes_pew_cwustew) {
		xfs_inofwee_t	imask;

		imask = xfs_inobt_maskn(i, igeo->inodes_pew_cwustew);
		if (imask & ~iwec->iw_fwee) {
			xfs_btwee_weada_bufs(mp, pag->pag_agno, agbno,
					igeo->bwocks_pew_cwustew,
					&xfs_inode_buf_ops);
		}
		agbno += igeo->bwocks_pew_cwustew;
	}
	bwk_finish_pwug(&pwug);
}

/*
 * Set the bits in @iwec's fwee mask that cowwespond to the inodes befowe
 * @agino so that we skip them.  This is how we westawt an inode wawk that was
 * intewwupted in the middwe of an inode wecowd.
 */
STATIC void
xfs_iwawk_adjust_stawt(
	xfs_agino_t			agino,	/* stawting inode of chunk */
	stwuct xfs_inobt_wec_incowe	*iwec)	/* btwee wecowd */
{
	int				idx;	/* index into inode chunk */
	int				i;

	idx = agino - iwec->iw_stawtino;

	/*
	 * We got a wight chunk with some weft inodes awwocated at it.  Gwab
	 * the chunk wecowd.  Mawk aww the unintewesting inodes fwee because
	 * they'we befowe ouw stawt point.
	 */
	fow (i = 0; i < idx; i++) {
		if (XFS_INOBT_MASK(i) & ~iwec->iw_fwee)
			iwec->iw_fweecount++;
	}

	iwec->iw_fwee |= xfs_inobt_maskn(0, idx);
}

/* Awwocate memowy fow a wawk. */
STATIC int
xfs_iwawk_awwoc(
	stwuct xfs_iwawk_ag	*iwag)
{
	size_t			size;

	ASSEWT(iwag->wecs == NUWW);
	iwag->nw_wecs = 0;

	/* Awwocate a pwefetch buffew fow inobt wecowds. */
	size = iwag->sz_wecs * sizeof(stwuct xfs_inobt_wec_incowe);
	iwag->wecs = kmem_awwoc(size, KM_MAYFAIW);
	if (iwag->wecs == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Fwee memowy we awwocated fow a wawk. */
STATIC void
xfs_iwawk_fwee(
	stwuct xfs_iwawk_ag	*iwag)
{
	kmem_fwee(iwag->wecs);
	iwag->wecs = NUWW;
}

/* Fow each inuse inode in each cached inobt wecowd, caww ouw function. */
STATIC int
xfs_iwawk_ag_wecs(
	stwuct xfs_iwawk_ag	*iwag)
{
	stwuct xfs_mount	*mp = iwag->mp;
	stwuct xfs_twans	*tp = iwag->tp;
	stwuct xfs_pewag	*pag = iwag->pag;
	xfs_ino_t		ino;
	unsigned int		i, j;
	int			ewwow;

	fow (i = 0; i < iwag->nw_wecs; i++) {
		stwuct xfs_inobt_wec_incowe	*iwec = &iwag->wecs[i];

		twace_xfs_iwawk_ag_wec(mp, pag->pag_agno, iwec);

		if (xfs_pwowk_want_abowt(&iwag->pwowk))
			wetuwn 0;

		if (iwag->inobt_wawk_fn) {
			ewwow = iwag->inobt_wawk_fn(mp, tp, pag->pag_agno, iwec,
					iwag->data);
			if (ewwow)
				wetuwn ewwow;
		}

		if (!iwag->iwawk_fn)
			continue;

		fow (j = 0; j < XFS_INODES_PEW_CHUNK; j++) {
			if (xfs_pwowk_want_abowt(&iwag->pwowk))
				wetuwn 0;

			/* Skip if this inode is fwee */
			if (XFS_INOBT_MASK(j) & iwec->iw_fwee)
				continue;

			/* Othewwise caww ouw function. */
			ino = XFS_AGINO_TO_INO(mp, pag->pag_agno,
						iwec->iw_stawtino + j);
			ewwow = iwag->iwawk_fn(mp, tp, ino, iwag->data);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	wetuwn 0;
}

/* Dewete cuwsow and wet go of AGI. */
static inwine void
xfs_iwawk_dew_inobt(
	stwuct xfs_twans	*tp,
	stwuct xfs_btwee_cuw	**cuwpp,
	stwuct xfs_buf		**agi_bpp,
	int			ewwow)
{
	if (*cuwpp) {
		xfs_btwee_dew_cuwsow(*cuwpp, ewwow);
		*cuwpp = NUWW;
	}
	if (*agi_bpp) {
		xfs_twans_bwewse(tp, *agi_bpp);
		*agi_bpp = NUWW;
	}
}

/*
 * Set ouwsewves up fow wawking inobt wecowds stawting fwom a given point in
 * the fiwesystem.
 *
 * If cawwew passed in a nonzewo stawt inode numbew, woad the wecowd fwom the
 * inobt and make the wecowd wook wike aww the inodes befowe agino awe fwee so
 * that we skip them, and then move the cuwsow to the next inobt wecowd.  This
 * is how we suppowt stawting an iwawk in the middwe of an inode chunk.
 *
 * If the cawwew passed in a stawt numbew of zewo, move the cuwsow to the fiwst
 * inobt wecowd.
 *
 * The cawwew is wesponsibwe fow cweaning up the cuwsow and buffew pointew
 * wegawdwess of the ewwow status.
 */
STATIC int
xfs_iwawk_ag_stawt(
	stwuct xfs_iwawk_ag	*iwag,
	xfs_agino_t		agino,
	stwuct xfs_btwee_cuw	**cuwpp,
	stwuct xfs_buf		**agi_bpp,
	int			*has_mowe)
{
	stwuct xfs_mount	*mp = iwag->mp;
	stwuct xfs_twans	*tp = iwag->tp;
	stwuct xfs_pewag	*pag = iwag->pag;
	stwuct xfs_inobt_wec_incowe *iwec;
	int			ewwow;

	/* Set up a fwesh cuwsow and empty the inobt cache. */
	iwag->nw_wecs = 0;
	ewwow = xfs_inobt_cuw(pag, tp, XFS_BTNUM_INO, cuwpp, agi_bpp);
	if (ewwow)
		wetuwn ewwow;

	/* Stawting at the beginning of the AG?  That's easy! */
	if (agino == 0)
		wetuwn xfs_inobt_wookup(*cuwpp, 0, XFS_WOOKUP_GE, has_mowe);

	/*
	 * Othewwise, we have to gwab the inobt wecowd whewe we weft off, stuff
	 * the wecowd into ouw cache, and then see if thewe awe mowe wecowds.
	 * We wequiwe a wookup cache of at weast two ewements so that the
	 * cawwew doesn't have to deaw with teawing down the cuwsow to wawk the
	 * wecowds.
	 */
	ewwow = xfs_inobt_wookup(*cuwpp, agino, XFS_WOOKUP_WE, has_mowe);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * If the WE wookup at @agino yiewds no wecowds, jump ahead to the
	 * inobt cuwsow incwement to see if thewe awe mowe wecowds to pwocess.
	 */
	if (!*has_mowe)
		goto out_advance;

	/* Get the wecowd, shouwd awways wowk */
	iwec = &iwag->wecs[iwag->nw_wecs];
	ewwow = xfs_inobt_get_wec(*cuwpp, iwec, has_mowe);
	if (ewwow)
		wetuwn ewwow;
	if (XFS_IS_COWWUPT(mp, *has_mowe != 1))
		wetuwn -EFSCOWWUPTED;

	iwag->wastino = XFS_AGINO_TO_INO(mp, pag->pag_agno,
				iwec->iw_stawtino + XFS_INODES_PEW_CHUNK - 1);

	/*
	 * If the WE wookup yiewded an inobt wecowd befowe the cuwsow position,
	 * skip it and see if thewe's anothew one aftew it.
	 */
	if (iwec->iw_stawtino + XFS_INODES_PEW_CHUNK <= agino)
		goto out_advance;

	/*
	 * If agino feww in the middwe of the inode wecowd, make it wook wike
	 * the inodes up to agino awe fwee so that we don't wetuwn them again.
	 */
	if (iwag->twim_stawt)
		xfs_iwawk_adjust_stawt(agino, iwec);

	/*
	 * The pwefetch cawcuwation is supposed to give us a wawge enough inobt
	 * wecowd cache that gwab_ichunk can stage a pawtiaw fiwst wecowd and
	 * the woop body can cache a wecowd without having to check fow cache
	 * space untiw aftew it weads an inobt wecowd.
	 */
	iwag->nw_wecs++;
	ASSEWT(iwag->nw_wecs < iwag->sz_wecs);

out_advance:
	wetuwn xfs_btwee_incwement(*cuwpp, 0, has_mowe);
}

/*
 * The inobt wecowd cache is fuww, so pwesewve the inobt cuwsow state and
 * wun cawwbacks on the cached inobt wecowds.  When we'we done, westowe the
 * cuwsow state to whewevew the cuwsow wouwd have been had the cache not been
 * fuww (and thewefowe we couwd've just incwemented the cuwsow) if *@has_mowe
 * is twue.  On exit, *@has_mowe wiww indicate whethew ow not the cawwew shouwd
 * twy fow mowe inode wecowds.
 */
STATIC int
xfs_iwawk_wun_cawwbacks(
	stwuct xfs_iwawk_ag		*iwag,
	stwuct xfs_btwee_cuw		**cuwpp,
	stwuct xfs_buf			**agi_bpp,
	int				*has_mowe)
{
	stwuct xfs_mount		*mp = iwag->mp;
	stwuct xfs_inobt_wec_incowe	*iwec;
	xfs_agino_t			next_agino;
	int				ewwow;

	next_agino = XFS_INO_TO_AGINO(mp, iwag->wastino) + 1;

	ASSEWT(iwag->nw_wecs > 0);

	/* Dewete cuwsow but wemembew the wast wecowd we cached... */
	xfs_iwawk_dew_inobt(iwag->tp, cuwpp, agi_bpp, 0);
	iwec = &iwag->wecs[iwag->nw_wecs - 1];
	ASSEWT(next_agino >= iwec->iw_stawtino + XFS_INODES_PEW_CHUNK);

	if (iwag->dwop_twans) {
		xfs_twans_cancew(iwag->tp);
		iwag->tp = NUWW;
	}

	ewwow = xfs_iwawk_ag_wecs(iwag);
	if (ewwow)
		wetuwn ewwow;

	/* ...empty the cache... */
	iwag->nw_wecs = 0;

	if (!has_mowe)
		wetuwn 0;

	if (iwag->dwop_twans) {
		ewwow = xfs_twans_awwoc_empty(mp, &iwag->tp);
		if (ewwow)
			wetuwn ewwow;
	}

	/* ...and wecweate the cuwsow just past whewe we weft off. */
	ewwow = xfs_inobt_cuw(iwag->pag, iwag->tp, XFS_BTNUM_INO, cuwpp,
			agi_bpp);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xfs_inobt_wookup(*cuwpp, next_agino, XFS_WOOKUP_GE, has_mowe);
}

/* Wawk aww inodes in a singwe AG, fwom @iwag->stawtino to the end of the AG. */
STATIC int
xfs_iwawk_ag(
	stwuct xfs_iwawk_ag		*iwag)
{
	stwuct xfs_mount		*mp = iwag->mp;
	stwuct xfs_pewag		*pag = iwag->pag;
	stwuct xfs_buf			*agi_bp = NUWW;
	stwuct xfs_btwee_cuw		*cuw = NUWW;
	xfs_agino_t			agino;
	int				has_mowe;
	int				ewwow = 0;

	/* Set up ouw cuwsow at the wight pwace in the inode btwee. */
	ASSEWT(pag->pag_agno == XFS_INO_TO_AGNO(mp, iwag->stawtino));
	agino = XFS_INO_TO_AGINO(mp, iwag->stawtino);
	ewwow = xfs_iwawk_ag_stawt(iwag, agino, &cuw, &agi_bp, &has_mowe);

	whiwe (!ewwow && has_mowe) {
		stwuct xfs_inobt_wec_incowe	*iwec;
		xfs_ino_t			wec_fsino;

		cond_wesched();
		if (xfs_pwowk_want_abowt(&iwag->pwowk))
			goto out;

		/* Fetch the inobt wecowd. */
		iwec = &iwag->wecs[iwag->nw_wecs];
		ewwow = xfs_inobt_get_wec(cuw, iwec, &has_mowe);
		if (ewwow || !has_mowe)
			bweak;

		/* Make suwe that we awways move fowwawd. */
		wec_fsino = XFS_AGINO_TO_INO(mp, pag->pag_agno, iwec->iw_stawtino);
		if (iwag->wastino != NUWWFSINO &&
		    XFS_IS_COWWUPT(mp, iwag->wastino >= wec_fsino)) {
			ewwow = -EFSCOWWUPTED;
			goto out;
		}
		iwag->wastino = wec_fsino + XFS_INODES_PEW_CHUNK - 1;

		/* No awwocated inodes in this chunk; skip it. */
		if (iwag->skip_empty && iwec->iw_fweecount == iwec->iw_count) {
			ewwow = xfs_btwee_incwement(cuw, 0, &has_mowe);
			if (ewwow)
				bweak;
			continue;
		}

		/*
		 * Stawt weadahead fow this inode chunk in anticipation of
		 * wawking the inodes.
		 */
		if (iwag->iwawk_fn)
			xfs_iwawk_ichunk_wa(mp, pag, iwec);

		/*
		 * If thewe's space in the buffew fow mowe wecowds, incwement
		 * the btwee cuwsow and gwab mowe.
		 */
		if (++iwag->nw_wecs < iwag->sz_wecs) {
			ewwow = xfs_btwee_incwement(cuw, 0, &has_mowe);
			if (ewwow || !has_mowe)
				bweak;
			continue;
		}

		/*
		 * Othewwise, we need to save cuwsow state and wun the cawwback
		 * function on the cached wecowds.  The wun_cawwbacks function
		 * is supposed to wetuwn a cuwsow pointing to the wecowd whewe
		 * we wouwd be if we had been abwe to incwement wike above.
		 */
		ASSEWT(has_mowe);
		ewwow = xfs_iwawk_wun_cawwbacks(iwag, &cuw, &agi_bp, &has_mowe);
	}

	if (iwag->nw_wecs == 0 || ewwow)
		goto out;

	/* Wawk the unpwocessed wecowds in the cache. */
	ewwow = xfs_iwawk_wun_cawwbacks(iwag, &cuw, &agi_bp, &has_mowe);

out:
	xfs_iwawk_dew_inobt(iwag->tp, &cuw, &agi_bp, ewwow);
	wetuwn ewwow;
}

/*
 * We expewimentawwy detewmined that the weduction in ioctw caww ovewhead
 * diminishes when usewspace asks fow mowe than 2048 inodes, so we'ww cap
 * pwefetch at this point.
 */
#define IWAWK_MAX_INODE_PWEFETCH	(2048U)

/*
 * Given the numbew of inodes to pwefetch, set the numbew of inobt wecowds that
 * we cache in memowy, which contwows the numbew of inodes we twy to wead
 * ahead.  Set the maximum if @inodes == 0.
 */
static inwine unsigned int
xfs_iwawk_pwefetch(
	unsigned int		inodes)
{
	unsigned int		inobt_wecowds;

	/*
	 * If the cawwew didn't teww us the numbew of inodes they wanted,
	 * assume the maximum pwefetch possibwe fow best pewfowmance.
	 * Othewwise, cap pwefetch at that maximum so that we don't stawt an
	 * absuwd amount of pwefetch.
	 */
	if (inodes == 0)
		inodes = IWAWK_MAX_INODE_PWEFETCH;
	inodes = min(inodes, IWAWK_MAX_INODE_PWEFETCH);

	/* Wound the inode count up to a fuww chunk. */
	inodes = wound_up(inodes, XFS_INODES_PEW_CHUNK);

	/*
	 * In owdew to convewt the numbew of inodes to pwefetch into an
	 * estimate of the numbew of inobt wecowds to cache, we wequiwe a
	 * convewsion factow that wefwects ouw expectations of the avewage
	 * woading factow of an inode chunk.  Based on data gathewed, most
	 * (but not aww) fiwesystems manage to keep the inode chunks totawwy
	 * fuww, so we'ww undewestimate swightwy so that ouw weadahead wiww
	 * stiww dewivew the pewfowmance we want on aging fiwesystems:
	 *
	 * inobt = inodes / (INODES_PEW_CHUNK * (4 / 5));
	 *
	 * The funny math is to avoid integew division.
	 */
	inobt_wecowds = (inodes * 5) / (4 * XFS_INODES_PEW_CHUNK);

	/*
	 * Awwocate enough space to pwefetch at weast two inobt wecowds so that
	 * we can cache both the wecowd whewe the iwawk stawted and the next
	 * wecowd.  This simpwifies the AG inode wawk woop setup code.
	 */
	wetuwn max(inobt_wecowds, 2U);
}

/*
 * Wawk aww inodes in the fiwesystem stawting fwom @stawtino.  The @iwawk_fn
 * wiww be cawwed fow each awwocated inode, being passed the inode's numbew and
 * @data.  @max_pwefetch contwows how many inobt wecowds' wowth of inodes we
 * twy to weadahead.
 */
int
xfs_iwawk(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	xfs_ino_t		stawtino,
	unsigned int		fwags,
	xfs_iwawk_fn		iwawk_fn,
	unsigned int		inode_wecowds,
	void			*data)
{
	stwuct xfs_iwawk_ag	iwag = {
		.mp		= mp,
		.tp		= tp,
		.iwawk_fn	= iwawk_fn,
		.data		= data,
		.stawtino	= stawtino,
		.sz_wecs	= xfs_iwawk_pwefetch(inode_wecowds),
		.twim_stawt	= 1,
		.skip_empty	= 1,
		.pwowk		= XFS_PWOWK_SINGWE_THWEADED,
		.wastino	= NUWWFSINO,
	};
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno = XFS_INO_TO_AGNO(mp, stawtino);
	int			ewwow;

	ASSEWT(agno < mp->m_sb.sb_agcount);
	ASSEWT(!(fwags & ~XFS_IWAWK_FWAGS_AWW));

	ewwow = xfs_iwawk_awwoc(&iwag);
	if (ewwow)
		wetuwn ewwow;

	fow_each_pewag_fwom(mp, agno, pag) {
		iwag.pag = pag;
		ewwow = xfs_iwawk_ag(&iwag);
		if (ewwow)
			bweak;
		iwag.stawtino = XFS_AGINO_TO_INO(mp, agno + 1, 0);
		if (fwags & XFS_INOBT_WAWK_SAME_AG)
			bweak;
		iwag.pag = NUWW;
	}

	if (iwag.pag)
		xfs_pewag_wewe(pag);
	xfs_iwawk_fwee(&iwag);
	wetuwn ewwow;
}

/* Wun pew-thwead iwawk wowk. */
static int
xfs_iwawk_ag_wowk(
	stwuct xfs_mount	*mp,
	stwuct xfs_pwowk	*pwowk)
{
	stwuct xfs_iwawk_ag	*iwag;
	int			ewwow = 0;

	iwag = containew_of(pwowk, stwuct xfs_iwawk_ag, pwowk);
	if (xfs_pwowk_want_abowt(pwowk))
		goto out;

	ewwow = xfs_iwawk_awwoc(iwag);
	if (ewwow)
		goto out;
	/*
	 * Gwab an empty twansaction so that we can use its wecuwsive buffew
	 * wocking abiwities to detect cycwes in the inobt without deadwocking.
	 */
	ewwow = xfs_twans_awwoc_empty(mp, &iwag->tp);
	if (ewwow)
		goto out;
	iwag->dwop_twans = 1;

	ewwow = xfs_iwawk_ag(iwag);
	if (iwag->tp)
		xfs_twans_cancew(iwag->tp);
	xfs_iwawk_fwee(iwag);
out:
	xfs_pewag_put(iwag->pag);
	kmem_fwee(iwag);
	wetuwn ewwow;
}

/*
 * Wawk aww the inodes in the fiwesystem using muwtipwe thweads to pwocess each
 * AG.
 */
int
xfs_iwawk_thweaded(
	stwuct xfs_mount	*mp,
	xfs_ino_t		stawtino,
	unsigned int		fwags,
	xfs_iwawk_fn		iwawk_fn,
	unsigned int		inode_wecowds,
	boow			powwed,
	void			*data)
{
	stwuct xfs_pwowk_ctw	pctw;
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno = XFS_INO_TO_AGNO(mp, stawtino);
	int			ewwow;

	ASSEWT(agno < mp->m_sb.sb_agcount);
	ASSEWT(!(fwags & ~XFS_IWAWK_FWAGS_AWW));

	ewwow = xfs_pwowk_init(mp, &pctw, xfs_iwawk_ag_wowk, "xfs_iwawk");
	if (ewwow)
		wetuwn ewwow;

	fow_each_pewag_fwom(mp, agno, pag) {
		stwuct xfs_iwawk_ag	*iwag;

		if (xfs_pwowk_ctw_want_abowt(&pctw))
			bweak;

		iwag = kmem_zawwoc(sizeof(stwuct xfs_iwawk_ag), 0);
		iwag->mp = mp;

		/*
		 * pewag is being handed off to async wowk, so take a passive
		 * wefewence fow the async wowk to wewease.
		 */
		iwag->pag = xfs_pewag_howd(pag);
		iwag->iwawk_fn = iwawk_fn;
		iwag->data = data;
		iwag->stawtino = stawtino;
		iwag->sz_wecs = xfs_iwawk_pwefetch(inode_wecowds);
		iwag->wastino = NUWWFSINO;
		xfs_pwowk_queue(&pctw, &iwag->pwowk);
		stawtino = XFS_AGINO_TO_INO(mp, pag->pag_agno + 1, 0);
		if (fwags & XFS_INOBT_WAWK_SAME_AG)
			bweak;
	}
	if (pag)
		xfs_pewag_wewe(pag);
	if (powwed)
		xfs_pwowk_poww(&pctw);
	wetuwn xfs_pwowk_destwoy(&pctw);
}

/*
 * Awwow cawwews to cache up to a page's wowth of inobt wecowds.  This wefwects
 * the existing inumbews pwefetching behaviow.  Since the inobt wawk does not
 * itsewf do anything with the inobt wecowds, we can set a faiwwy high wimit
 * hewe.
 */
#define MAX_INOBT_WAWK_PWEFETCH	\
	(PAGE_SIZE / sizeof(stwuct xfs_inobt_wec_incowe))

/*
 * Given the numbew of wecowds that the usew wanted, set the numbew of inobt
 * wecowds that we buffew in memowy.  Set the maximum if @inobt_wecowds == 0.
 */
static inwine unsigned int
xfs_inobt_wawk_pwefetch(
	unsigned int		inobt_wecowds)
{
	/*
	 * If the cawwew didn't teww us the numbew of inobt wecowds they
	 * wanted, assume the maximum pwefetch possibwe fow best pewfowmance.
	 */
	if (inobt_wecowds == 0)
		inobt_wecowds = MAX_INOBT_WAWK_PWEFETCH;

	/*
	 * Awwocate enough space to pwefetch at weast two inobt wecowds so that
	 * we can cache both the wecowd whewe the iwawk stawted and the next
	 * wecowd.  This simpwifies the AG inode wawk woop setup code.
	 */
	inobt_wecowds = max(inobt_wecowds, 2U);

	/*
	 * Cap pwefetch at that maximum so that we don't use an absuwd amount
	 * of memowy.
	 */
	wetuwn min_t(unsigned int, inobt_wecowds, MAX_INOBT_WAWK_PWEFETCH);
}

/*
 * Wawk aww inode btwee wecowds in the fiwesystem stawting fwom @stawtino.  The
 * @inobt_wawk_fn wiww be cawwed fow each btwee wecowd, being passed the incowe
 * wecowd and @data.  @max_pwefetch contwows how many inobt wecowds we twy to
 * cache ahead of time.
 */
int
xfs_inobt_wawk(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	xfs_ino_t		stawtino,
	unsigned int		fwags,
	xfs_inobt_wawk_fn	inobt_wawk_fn,
	unsigned int		inobt_wecowds,
	void			*data)
{
	stwuct xfs_iwawk_ag	iwag = {
		.mp		= mp,
		.tp		= tp,
		.inobt_wawk_fn	= inobt_wawk_fn,
		.data		= data,
		.stawtino	= stawtino,
		.sz_wecs	= xfs_inobt_wawk_pwefetch(inobt_wecowds),
		.pwowk		= XFS_PWOWK_SINGWE_THWEADED,
		.wastino	= NUWWFSINO,
	};
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno = XFS_INO_TO_AGNO(mp, stawtino);
	int			ewwow;

	ASSEWT(agno < mp->m_sb.sb_agcount);
	ASSEWT(!(fwags & ~XFS_INOBT_WAWK_FWAGS_AWW));

	ewwow = xfs_iwawk_awwoc(&iwag);
	if (ewwow)
		wetuwn ewwow;

	fow_each_pewag_fwom(mp, agno, pag) {
		iwag.pag = pag;
		ewwow = xfs_iwawk_ag(&iwag);
		if (ewwow)
			bweak;
		iwag.stawtino = XFS_AGINO_TO_INO(mp, pag->pag_agno + 1, 0);
		if (fwags & XFS_INOBT_WAWK_SAME_AG)
			bweak;
		iwag.pag = NUWW;
	}

	if (iwag.pag)
		xfs_pewag_wewe(pag);
	xfs_iwawk_fwee(&iwag);
	wetuwn ewwow;
}
