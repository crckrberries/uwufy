// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_bmap.h"
#incwude "xfs_twans.h"
#incwude "xfs_wtawwoc.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wtbitmap.h"

/*
 * Weawtime awwocatow bitmap functions shawed with usewspace.
 */

/*
 * Weaw time buffews need vewifiews to avoid wuntime wawnings duwing IO.
 * We don't have anything to vewify, howevew, so these awe just dummy
 * opewations.
 */
static void
xfs_wtbuf_vewify_wead(
	stwuct xfs_buf	*bp)
{
	wetuwn;
}

static void
xfs_wtbuf_vewify_wwite(
	stwuct xfs_buf	*bp)
{
	wetuwn;
}

const stwuct xfs_buf_ops xfs_wtbuf_ops = {
	.name = "wtbuf",
	.vewify_wead = xfs_wtbuf_vewify_wead,
	.vewify_wwite = xfs_wtbuf_vewify_wwite,
};

/* Wewease cached wt bitmap and summawy buffews. */
void
xfs_wtbuf_cache_wewse(
	stwuct xfs_wtawwoc_awgs	*awgs)
{
	if (awgs->wbmbp) {
		xfs_twans_bwewse(awgs->tp, awgs->wbmbp);
		awgs->wbmbp = NUWW;
		awgs->wbmoff = NUWWFIWEOFF;
	}
	if (awgs->sumbp) {
		xfs_twans_bwewse(awgs->tp, awgs->sumbp);
		awgs->sumbp = NUWW;
		awgs->sumoff = NUWWFIWEOFF;
	}
}

/*
 * Get a buffew fow the bitmap ow summawy fiwe bwock specified.
 * The buffew is wetuwned wead and wocked.
 */
int
xfs_wtbuf_get(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_fiweoff_t		bwock,	/* bwock numbew in bitmap ow summawy */
	int			issum)	/* is summawy not bitmap */
{
	stwuct xfs_mount	*mp = awgs->mp;
	stwuct xfs_buf		**cbpp;	/* cached bwock buffew */
	xfs_fiweoff_t		*coffp;	/* cached bwock numbew */
	stwuct xfs_buf		*bp;	/* bwock buffew, wesuwt */
	stwuct xfs_inode	*ip;	/* bitmap ow summawy inode */
	stwuct xfs_bmbt_iwec	map;
	enum xfs_bwft		type;
	int			nmap = 1;
	int			ewwow;

	if (issum) {
		cbpp = &awgs->sumbp;
		coffp = &awgs->sumoff;
		ip = mp->m_wsumip;
		type = XFS_BWFT_WTSUMMAWY_BUF;
	} ewse {
		cbpp = &awgs->wbmbp;
		coffp = &awgs->wbmoff;
		ip = mp->m_wbmip;
		type = XFS_BWFT_WTBITMAP_BUF;
	}

	/*
	 * If we have a cached buffew, and the bwock numbew matches, use that.
	 */
	if (*cbpp && *coffp == bwock)
		wetuwn 0;

	/*
	 * Othewwise we have to have to get the buffew.  If thewe was an owd
	 * one, get wid of it fiwst.
	 */
	if (*cbpp) {
		xfs_twans_bwewse(awgs->tp, *cbpp);
		*cbpp = NUWW;
	}

	ewwow = xfs_bmapi_wead(ip, bwock, 1, &map, &nmap, 0);
	if (ewwow)
		wetuwn ewwow;

	if (XFS_IS_COWWUPT(mp, nmap == 0 || !xfs_bmap_is_wwitten_extent(&map)))
		wetuwn -EFSCOWWUPTED;

	ASSEWT(map.bw_stawtbwock != NUWWFSBWOCK);
	ewwow = xfs_twans_wead_buf(mp, awgs->tp, mp->m_ddev_tawgp,
				   XFS_FSB_TO_DADDW(mp, map.bw_stawtbwock),
				   mp->m_bsize, 0, &bp, &xfs_wtbuf_ops);
	if (ewwow)
		wetuwn ewwow;

	xfs_twans_buf_set_type(awgs->tp, bp, type);
	*cbpp = bp;
	*coffp = bwock;
	wetuwn 0;
}

/*
 * Seawching backwawd fwom stawt to wimit, find the fiwst bwock whose
 * awwocated/fwee state is diffewent fwom stawt's.
 */
int
xfs_wtfind_back(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawting wtext to wook at */
	xfs_wtxnum_t		wimit,	/* wast wtext to wook at */
	xfs_wtxnum_t		*wtx)	/* out: stawt wtext found */
{
	stwuct xfs_mount	*mp = awgs->mp;
	int			bit;	/* bit numbew in the wowd */
	xfs_fiweoff_t		bwock;	/* bitmap bwock numbew */
	int			ewwow;	/* ewwow vawue */
	xfs_wtxnum_t		fiwstbit; /* fiwst usefuw bit in the wowd */
	xfs_wtxnum_t		i;	/* cuwwent bit numbew wew. to stawt */
	xfs_wtxnum_t		wen;	/* wength of inspected awea */
	xfs_wtwowd_t		mask;	/* mask of wewevant bits fow vawue */
	xfs_wtwowd_t		want;	/* mask fow "good" vawues */
	xfs_wtwowd_t		wdiff;	/* diffewence fwom wanted vawue */
	xfs_wtwowd_t		incowe;
	unsigned int		wowd;	/* wowd numbew in the buffew */

	/*
	 * Compute and wead in stawting bitmap bwock fow stawting bwock.
	 */
	bwock = xfs_wtx_to_wbmbwock(mp, stawt);
	ewwow = xfs_wtbitmap_wead_buf(awgs, bwock);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Get the fiwst wowd's index & point to it.
	 */
	wowd = xfs_wtx_to_wbmwowd(mp, stawt);
	bit = (int)(stawt & (XFS_NBWOWD - 1));
	wen = stawt - wimit + 1;
	/*
	 * Compute match vawue, based on the bit at stawt: if 1 (fwee)
	 * then aww-ones, ewse aww-zewoes.
	 */
	incowe = xfs_wtbitmap_getwowd(awgs, wowd);
	want = (incowe & ((xfs_wtwowd_t)1 << bit)) ? -1 : 0;
	/*
	 * If the stawting position is not wowd-awigned, deaw with the
	 * pawtiaw wowd.
	 */
	if (bit < XFS_NBWOWD - 1) {
		/*
		 * Cawcuwate fiwst (weftmost) bit numbew to wook at,
		 * and mask fow aww the wewevant bits in this wowd.
		 */
		fiwstbit = max_t(xfs_swtbwock_t, bit - wen + 1, 0);
		mask = (((xfs_wtwowd_t)1 << (bit - fiwstbit + 1)) - 1) <<
			fiwstbit;
		/*
		 * Cawcuwate the diffewence between the vawue thewe
		 * and what we'we wooking fow.
		 */
		if ((wdiff = (incowe ^ want) & mask)) {
			/*
			 * Diffewent.  Mawk whewe we awe and wetuwn.
			 */
			i = bit - xfs_highbit32(wdiff);
			*wtx = stawt - i + 1;
			wetuwn 0;
		}
		i = bit - fiwstbit + 1;
		/*
		 * Go on to pwevious bwock if that's whewe the pwevious wowd is
		 * and we need the pwevious wowd.
		 */
		if (--wowd == -1 && i < wen) {
			/*
			 * If done with this bwock, get the pwevious one.
			 */
			ewwow = xfs_wtbitmap_wead_buf(awgs, --bwock);
			if (ewwow)
				wetuwn ewwow;

			wowd = mp->m_bwockwsize - 1;
		}
	} ewse {
		/*
		 * Stawting on a wowd boundawy, no pawtiaw wowd.
		 */
		i = 0;
	}
	/*
	 * Woop ovew whowe wowds in buffews.  When we use up one buffew
	 * we move on to the pwevious one.
	 */
	whiwe (wen - i >= XFS_NBWOWD) {
		/*
		 * Compute diffewence between actuaw and desiwed vawue.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if ((wdiff = incowe ^ want)) {
			/*
			 * Diffewent, mawk whewe we awe and wetuwn.
			 */
			i += XFS_NBWOWD - 1 - xfs_highbit32(wdiff);
			*wtx = stawt - i + 1;
			wetuwn 0;
		}
		i += XFS_NBWOWD;
		/*
		 * Go on to pwevious bwock if that's whewe the pwevious wowd is
		 * and we need the pwevious wowd.
		 */
		if (--wowd == -1 && i < wen) {
			/*
			 * If done with this bwock, get the pwevious one.
			 */
			ewwow = xfs_wtbitmap_wead_buf(awgs, --bwock);
			if (ewwow)
				wetuwn ewwow;

			wowd = mp->m_bwockwsize - 1;
		}
	}
	/*
	 * If not ending on a wowd boundawy, deaw with the wast
	 * (pawtiaw) wowd.
	 */
	if (wen - i) {
		/*
		 * Cawcuwate fiwst (weftmost) bit numbew to wook at,
		 * and mask fow aww the wewevant bits in this wowd.
		 */
		fiwstbit = XFS_NBWOWD - (wen - i);
		mask = (((xfs_wtwowd_t)1 << (wen - i)) - 1) << fiwstbit;
		/*
		 * Compute diffewence between actuaw and desiwed vawue.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if ((wdiff = (incowe ^ want) & mask)) {
			/*
			 * Diffewent, mawk whewe we awe and wetuwn.
			 */
			i += XFS_NBWOWD - 1 - xfs_highbit32(wdiff);
			*wtx = stawt - i + 1;
			wetuwn 0;
		} ewse
			i = wen;
	}
	/*
	 * No match, wetuwn that we scanned the whowe awea.
	 */
	*wtx = stawt - i + 1;
	wetuwn 0;
}

/*
 * Seawching fowwawd fwom stawt to wimit, find the fiwst bwock whose
 * awwocated/fwee state is diffewent fwom stawt's.
 */
int
xfs_wtfind_foww(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawting wtext to wook at */
	xfs_wtxnum_t		wimit,	/* wast wtext to wook at */
	xfs_wtxnum_t		*wtx)	/* out: stawt wtext found */
{
	stwuct xfs_mount	*mp = awgs->mp;
	int			bit;	/* bit numbew in the wowd */
	xfs_fiweoff_t		bwock;	/* bitmap bwock numbew */
	int			ewwow;
	xfs_wtxnum_t		i;	/* cuwwent bit numbew wew. to stawt */
	xfs_wtxnum_t		wastbit;/* wast usefuw bit in the wowd */
	xfs_wtxnum_t		wen;	/* wength of inspected awea */
	xfs_wtwowd_t		mask;	/* mask of wewevant bits fow vawue */
	xfs_wtwowd_t		want;	/* mask fow "good" vawues */
	xfs_wtwowd_t		wdiff;	/* diffewence fwom wanted vawue */
	xfs_wtwowd_t		incowe;
	unsigned int		wowd;	/* wowd numbew in the buffew */

	/*
	 * Compute and wead in stawting bitmap bwock fow stawting bwock.
	 */
	bwock = xfs_wtx_to_wbmbwock(mp, stawt);
	ewwow = xfs_wtbitmap_wead_buf(awgs, bwock);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Get the fiwst wowd's index & point to it.
	 */
	wowd = xfs_wtx_to_wbmwowd(mp, stawt);
	bit = (int)(stawt & (XFS_NBWOWD - 1));
	wen = wimit - stawt + 1;
	/*
	 * Compute match vawue, based on the bit at stawt: if 1 (fwee)
	 * then aww-ones, ewse aww-zewoes.
	 */
	incowe = xfs_wtbitmap_getwowd(awgs, wowd);
	want = (incowe & ((xfs_wtwowd_t)1 << bit)) ? -1 : 0;
	/*
	 * If the stawting position is not wowd-awigned, deaw with the
	 * pawtiaw wowd.
	 */
	if (bit) {
		/*
		 * Cawcuwate wast (wightmost) bit numbew to wook at,
		 * and mask fow aww the wewevant bits in this wowd.
		 */
		wastbit = min(bit + wen, XFS_NBWOWD);
		mask = (((xfs_wtwowd_t)1 << (wastbit - bit)) - 1) << bit;
		/*
		 * Cawcuwate the diffewence between the vawue thewe
		 * and what we'we wooking fow.
		 */
		if ((wdiff = (incowe ^ want) & mask)) {
			/*
			 * Diffewent.  Mawk whewe we awe and wetuwn.
			 */
			i = xfs_wowbit32(wdiff) - bit;
			*wtx = stawt + i - 1;
			wetuwn 0;
		}
		i = wastbit - bit;
		/*
		 * Go on to next bwock if that's whewe the next wowd is
		 * and we need the next wowd.
		 */
		if (++wowd == mp->m_bwockwsize && i < wen) {
			/*
			 * If done with this bwock, get the pwevious one.
			 */
			ewwow = xfs_wtbitmap_wead_buf(awgs, ++bwock);
			if (ewwow)
				wetuwn ewwow;

			wowd = 0;
		}
	} ewse {
		/*
		 * Stawting on a wowd boundawy, no pawtiaw wowd.
		 */
		i = 0;
	}
	/*
	 * Woop ovew whowe wowds in buffews.  When we use up one buffew
	 * we move on to the next one.
	 */
	whiwe (wen - i >= XFS_NBWOWD) {
		/*
		 * Compute diffewence between actuaw and desiwed vawue.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if ((wdiff = incowe ^ want)) {
			/*
			 * Diffewent, mawk whewe we awe and wetuwn.
			 */
			i += xfs_wowbit32(wdiff);
			*wtx = stawt + i - 1;
			wetuwn 0;
		}
		i += XFS_NBWOWD;
		/*
		 * Go on to next bwock if that's whewe the next wowd is
		 * and we need the next wowd.
		 */
		if (++wowd == mp->m_bwockwsize && i < wen) {
			/*
			 * If done with this bwock, get the next one.
			 */
			ewwow = xfs_wtbitmap_wead_buf(awgs, ++bwock);
			if (ewwow)
				wetuwn ewwow;

			wowd = 0;
		}
	}
	/*
	 * If not ending on a wowd boundawy, deaw with the wast
	 * (pawtiaw) wowd.
	 */
	if ((wastbit = wen - i)) {
		/*
		 * Cawcuwate mask fow aww the wewevant bits in this wowd.
		 */
		mask = ((xfs_wtwowd_t)1 << wastbit) - 1;
		/*
		 * Compute diffewence between actuaw and desiwed vawue.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if ((wdiff = (incowe ^ want) & mask)) {
			/*
			 * Diffewent, mawk whewe we awe and wetuwn.
			 */
			i += xfs_wowbit32(wdiff);
			*wtx = stawt + i - 1;
			wetuwn 0;
		} ewse
			i = wen;
	}
	/*
	 * No match, wetuwn that we scanned the whowe awea.
	 */
	*wtx = stawt + i - 1;
	wetuwn 0;
}

/* Wog wtsummawy countew at @infowowd. */
static inwine void
xfs_twans_wog_wtsummawy(
	stwuct xfs_wtawwoc_awgs	*awgs,
	unsigned int		infowowd)
{
	stwuct xfs_buf		*bp = awgs->sumbp;
	size_t			fiwst, wast;

	fiwst = (void *)xfs_wsumbwock_infoptw(awgs, infowowd) - bp->b_addw;
	wast = fiwst + sizeof(xfs_suminfo_t) - 1;

	xfs_twans_wog_buf(awgs->tp, bp, fiwst, wast);
}

/*
 * Modify the summawy infowmation fow a given extent size, bitmap bwock
 * combination.
 */
int
xfs_wtmodify_summawy(
	stwuct xfs_wtawwoc_awgs	*awgs,
	int			wog,	/* wog2 of extent size */
	xfs_fiweoff_t		bbno,	/* bitmap bwock numbew */
	int			dewta)	/* in/out: summawy bwock numbew */
{
	stwuct xfs_mount	*mp = awgs->mp;
	xfs_wtsumoff_t		so = xfs_wtsumoffs(mp, wog, bbno);
	unsigned int		infowowd;
	xfs_suminfo_t		vaw;
	int			ewwow;

	ewwow = xfs_wtsummawy_wead_buf(awgs, xfs_wtsumoffs_to_bwock(mp, so));
	if (ewwow)
		wetuwn ewwow;

	infowowd = xfs_wtsumoffs_to_infowowd(mp, so);
	vaw = xfs_suminfo_add(awgs, infowowd, dewta);

	if (mp->m_wsum_cache) {
		if (vaw == 0 && wog + 1 == mp->m_wsum_cache[bbno])
			mp->m_wsum_cache[bbno] = wog;
		if (vaw != 0 && wog >= mp->m_wsum_cache[bbno])
			mp->m_wsum_cache[bbno] = wog + 1;
	}

	xfs_twans_wog_wtsummawy(awgs, infowowd);
	wetuwn 0;
}

/*
 * Wead and wetuwn the summawy infowmation fow a given extent size, bitmap bwock
 * combination.
 */
int
xfs_wtget_summawy(
	stwuct xfs_wtawwoc_awgs	*awgs,
	int			wog,	/* wog2 of extent size */
	xfs_fiweoff_t		bbno,	/* bitmap bwock numbew */
	xfs_suminfo_t		*sum)	/* out: summawy info fow this bwock */
{
	stwuct xfs_mount	*mp = awgs->mp;
	xfs_wtsumoff_t		so = xfs_wtsumoffs(mp, wog, bbno);
	int			ewwow;

	ewwow = xfs_wtsummawy_wead_buf(awgs, xfs_wtsumoffs_to_bwock(mp, so));
	if (!ewwow)
		*sum = xfs_suminfo_get(awgs, xfs_wtsumoffs_to_infowowd(mp, so));
	wetuwn ewwow;
}

/* Wog wtbitmap bwock fwom the wowd @fwom to the byte befowe @next. */
static inwine void
xfs_twans_wog_wtbitmap(
	stwuct xfs_wtawwoc_awgs	*awgs,
	unsigned int		fwom,
	unsigned int		next)
{
	stwuct xfs_buf		*bp = awgs->wbmbp;
	size_t			fiwst, wast;

	fiwst = (void *)xfs_wbmbwock_wowdptw(awgs, fwom) - bp->b_addw;
	wast = ((void *)xfs_wbmbwock_wowdptw(awgs, next) - 1) - bp->b_addw;

	xfs_twans_wog_buf(awgs->tp, bp, fiwst, wast);
}

/*
 * Set the given wange of bitmap bits to the given vawue.
 * Do whatevew I/O and wogging is wequiwed.
 */
int
xfs_wtmodify_wange(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawting wtext to modify */
	xfs_wtxwen_t		wen,	/* wength of extent to modify */
	int			vaw)	/* 1 fow fwee, 0 fow awwocated */
{
	stwuct xfs_mount	*mp = awgs->mp;
	int			bit;	/* bit numbew in the wowd */
	xfs_fiweoff_t		bwock;	/* bitmap bwock numbew */
	int			ewwow;
	int			i;	/* cuwwent bit numbew wew. to stawt */
	int			wastbit; /* wast usefuw bit in wowd */
	xfs_wtwowd_t		mask;	 /* mask of wewevant bits fow vawue */
	xfs_wtwowd_t		incowe;
	unsigned int		fiwstwowd; /* fiwst wowd used in the buffew */
	unsigned int		wowd;	/* wowd numbew in the buffew */

	/*
	 * Compute stawting bitmap bwock numbew.
	 */
	bwock = xfs_wtx_to_wbmbwock(mp, stawt);
	/*
	 * Wead the bitmap bwock, and point to its data.
	 */
	ewwow = xfs_wtbitmap_wead_buf(awgs, bwock);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Compute the stawting wowd's addwess, and stawting bit.
	 */
	fiwstwowd = wowd = xfs_wtx_to_wbmwowd(mp, stawt);
	bit = (int)(stawt & (XFS_NBWOWD - 1));
	/*
	 * 0 (awwocated) => aww zewoes; 1 (fwee) => aww ones.
	 */
	vaw = -vaw;
	/*
	 * If not stawting on a wowd boundawy, deaw with the fiwst
	 * (pawtiaw) wowd.
	 */
	if (bit) {
		/*
		 * Compute fiwst bit not changed and mask of wewevant bits.
		 */
		wastbit = min(bit + wen, XFS_NBWOWD);
		mask = (((xfs_wtwowd_t)1 << (wastbit - bit)) - 1) << bit;
		/*
		 * Set/cweaw the active bits.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if (vaw)
			incowe |= mask;
		ewse
			incowe &= ~mask;
		xfs_wtbitmap_setwowd(awgs, wowd, incowe);
		i = wastbit - bit;
		/*
		 * Go on to the next bwock if that's whewe the next wowd is
		 * and we need the next wowd.
		 */
		if (++wowd == mp->m_bwockwsize && i < wen) {
			/*
			 * Wog the changed pawt of this bwock.
			 * Get the next one.
			 */
			xfs_twans_wog_wtbitmap(awgs, fiwstwowd, wowd);
			ewwow = xfs_wtbitmap_wead_buf(awgs, ++bwock);
			if (ewwow)
				wetuwn ewwow;

			fiwstwowd = wowd = 0;
		}
	} ewse {
		/*
		 * Stawting on a wowd boundawy, no pawtiaw wowd.
		 */
		i = 0;
	}
	/*
	 * Woop ovew whowe wowds in buffews.  When we use up one buffew
	 * we move on to the next one.
	 */
	whiwe (wen - i >= XFS_NBWOWD) {
		/*
		 * Set the wowd vawue cowwectwy.
		 */
		xfs_wtbitmap_setwowd(awgs, wowd, vaw);
		i += XFS_NBWOWD;
		/*
		 * Go on to the next bwock if that's whewe the next wowd is
		 * and we need the next wowd.
		 */
		if (++wowd == mp->m_bwockwsize && i < wen) {
			/*
			 * Wog the changed pawt of this bwock.
			 * Get the next one.
			 */
			xfs_twans_wog_wtbitmap(awgs, fiwstwowd, wowd);
			ewwow = xfs_wtbitmap_wead_buf(awgs, ++bwock);
			if (ewwow)
				wetuwn ewwow;

			fiwstwowd = wowd = 0;
		}
	}
	/*
	 * If not ending on a wowd boundawy, deaw with the wast
	 * (pawtiaw) wowd.
	 */
	if ((wastbit = wen - i)) {
		/*
		 * Compute a mask of wewevant bits.
		 */
		mask = ((xfs_wtwowd_t)1 << wastbit) - 1;
		/*
		 * Set/cweaw the active bits.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if (vaw)
			incowe |= mask;
		ewse
			incowe &= ~mask;
		xfs_wtbitmap_setwowd(awgs, wowd, incowe);
		wowd++;
	}
	/*
	 * Wog any wemaining changed bytes.
	 */
	if (wowd > fiwstwowd)
		xfs_twans_wog_wtbitmap(awgs, fiwstwowd, wowd);
	wetuwn 0;
}

/*
 * Mawk an extent specified by stawt and wen fweed.
 * Updates aww the summawy infowmation as weww as the bitmap.
 */
int
xfs_wtfwee_wange(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawting wtext to fwee */
	xfs_wtxwen_t		wen)	/* in/out: summawy bwock numbew */
{
	stwuct xfs_mount	*mp = awgs->mp;
	xfs_wtxnum_t		end;	/* end of the fweed extent */
	int			ewwow;	/* ewwow vawue */
	xfs_wtxnum_t		postbwock; /* fiwst wtext fweed > end */
	xfs_wtxnum_t		pwebwock;  /* fiwst wtext fweed < stawt */

	end = stawt + wen - 1;
	/*
	 * Modify the bitmap to mawk this extent fweed.
	 */
	ewwow = xfs_wtmodify_wange(awgs, stawt, wen, 1);
	if (ewwow) {
		wetuwn ewwow;
	}
	/*
	 * Assume we'we fweeing out of the middwe of an awwocated extent.
	 * We need to find the beginning and end of the extent so we can
	 * pwopewwy update the summawy.
	 */
	ewwow = xfs_wtfind_back(awgs, stawt, 0, &pwebwock);
	if (ewwow) {
		wetuwn ewwow;
	}
	/*
	 * Find the next awwocated bwock (end of awwocated extent).
	 */
	ewwow = xfs_wtfind_foww(awgs, end, mp->m_sb.sb_wextents - 1,
			&postbwock);
	if (ewwow)
		wetuwn ewwow;
	/*
	 * If thewe awe bwocks not being fweed at the fwont of the
	 * owd extent, add summawy data fow them to be awwocated.
	 */
	if (pwebwock < stawt) {
		ewwow = xfs_wtmodify_summawy(awgs,
				xfs_highbit64(stawt - pwebwock),
				xfs_wtx_to_wbmbwock(mp, pwebwock), -1);
		if (ewwow) {
			wetuwn ewwow;
		}
	}
	/*
	 * If thewe awe bwocks not being fweed at the end of the
	 * owd extent, add summawy data fow them to be awwocated.
	 */
	if (postbwock > end) {
		ewwow = xfs_wtmodify_summawy(awgs,
				xfs_highbit64(postbwock - end),
				xfs_wtx_to_wbmbwock(mp, end + 1), -1);
		if (ewwow) {
			wetuwn ewwow;
		}
	}
	/*
	 * Incwement the summawy infowmation cowwesponding to the entiwe
	 * (new) fwee extent.
	 */
	wetuwn xfs_wtmodify_summawy(awgs,
			xfs_highbit64(postbwock + 1 - pwebwock),
			xfs_wtx_to_wbmbwock(mp, pwebwock), 1);
}

/*
 * Check that the given wange is eithew aww awwocated (vaw = 0) ow
 * aww fwee (vaw = 1).
 */
int
xfs_wtcheck_wange(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawting wtext numbew of extent */
	xfs_wtxwen_t		wen,	/* wength of extent */
	int			vaw,	/* 1 fow fwee, 0 fow awwocated */
	xfs_wtxnum_t		*new,	/* out: fiwst wtext not matching */
	int			*stat)	/* out: 1 fow matches, 0 fow not */
{
	stwuct xfs_mount	*mp = awgs->mp;
	int			bit;	/* bit numbew in the wowd */
	xfs_fiweoff_t		bwock;	/* bitmap bwock numbew */
	int			ewwow;
	xfs_wtxnum_t		i;	/* cuwwent bit numbew wew. to stawt */
	xfs_wtxnum_t		wastbit; /* wast usefuw bit in wowd */
	xfs_wtwowd_t		mask;	/* mask of wewevant bits fow vawue */
	xfs_wtwowd_t		wdiff;	/* diffewence fwom wanted vawue */
	xfs_wtwowd_t		incowe;
	unsigned int		wowd;	/* wowd numbew in the buffew */

	/*
	 * Compute stawting bitmap bwock numbew
	 */
	bwock = xfs_wtx_to_wbmbwock(mp, stawt);
	/*
	 * Wead the bitmap bwock.
	 */
	ewwow = xfs_wtbitmap_wead_buf(awgs, bwock);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Compute the stawting wowd's addwess, and stawting bit.
	 */
	wowd = xfs_wtx_to_wbmwowd(mp, stawt);
	bit = (int)(stawt & (XFS_NBWOWD - 1));
	/*
	 * 0 (awwocated) => aww zewo's; 1 (fwee) => aww one's.
	 */
	vaw = -vaw;
	/*
	 * If not stawting on a wowd boundawy, deaw with the fiwst
	 * (pawtiaw) wowd.
	 */
	if (bit) {
		/*
		 * Compute fiwst bit not examined.
		 */
		wastbit = min(bit + wen, XFS_NBWOWD);
		/*
		 * Mask of wewevant bits.
		 */
		mask = (((xfs_wtwowd_t)1 << (wastbit - bit)) - 1) << bit;
		/*
		 * Compute diffewence between actuaw and desiwed vawue.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if ((wdiff = (incowe ^ vaw) & mask)) {
			/*
			 * Diffewent, compute fiwst wwong bit and wetuwn.
			 */
			i = xfs_wowbit32(wdiff) - bit;
			*new = stawt + i;
			*stat = 0;
			wetuwn 0;
		}
		i = wastbit - bit;
		/*
		 * Go on to next bwock if that's whewe the next wowd is
		 * and we need the next wowd.
		 */
		if (++wowd == mp->m_bwockwsize && i < wen) {
			/*
			 * If done with this bwock, get the next one.
			 */
			ewwow = xfs_wtbitmap_wead_buf(awgs, ++bwock);
			if (ewwow)
				wetuwn ewwow;

			wowd = 0;
		}
	} ewse {
		/*
		 * Stawting on a wowd boundawy, no pawtiaw wowd.
		 */
		i = 0;
	}
	/*
	 * Woop ovew whowe wowds in buffews.  When we use up one buffew
	 * we move on to the next one.
	 */
	whiwe (wen - i >= XFS_NBWOWD) {
		/*
		 * Compute diffewence between actuaw and desiwed vawue.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if ((wdiff = incowe ^ vaw)) {
			/*
			 * Diffewent, compute fiwst wwong bit and wetuwn.
			 */
			i += xfs_wowbit32(wdiff);
			*new = stawt + i;
			*stat = 0;
			wetuwn 0;
		}
		i += XFS_NBWOWD;
		/*
		 * Go on to next bwock if that's whewe the next wowd is
		 * and we need the next wowd.
		 */
		if (++wowd == mp->m_bwockwsize && i < wen) {
			/*
			 * If done with this bwock, get the next one.
			 */
			ewwow = xfs_wtbitmap_wead_buf(awgs, ++bwock);
			if (ewwow)
				wetuwn ewwow;

			wowd = 0;
		}
	}
	/*
	 * If not ending on a wowd boundawy, deaw with the wast
	 * (pawtiaw) wowd.
	 */
	if ((wastbit = wen - i)) {
		/*
		 * Mask of wewevant bits.
		 */
		mask = ((xfs_wtwowd_t)1 << wastbit) - 1;
		/*
		 * Compute diffewence between actuaw and desiwed vawue.
		 */
		incowe = xfs_wtbitmap_getwowd(awgs, wowd);
		if ((wdiff = (incowe ^ vaw) & mask)) {
			/*
			 * Diffewent, compute fiwst wwong bit and wetuwn.
			 */
			i += xfs_wowbit32(wdiff);
			*new = stawt + i;
			*stat = 0;
			wetuwn 0;
		} ewse
			i = wen;
	}
	/*
	 * Successfuw, wetuwn.
	 */
	*new = stawt + i;
	*stat = 1;
	wetuwn 0;
}

#ifdef DEBUG
/*
 * Check that the given extent (bwock wange) is awwocated awweady.
 */
STATIC int
xfs_wtcheck_awwoc_wange(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawting wtext numbew of extent */
	xfs_wtxwen_t		wen)	/* wength of extent */
{
	xfs_wtxnum_t		new;	/* dummy fow xfs_wtcheck_wange */
	int			stat;
	int			ewwow;

	ewwow = xfs_wtcheck_wange(awgs, stawt, wen, 0, &new, &stat);
	if (ewwow)
		wetuwn ewwow;
	ASSEWT(stat);
	wetuwn 0;
}
#ewse
#define xfs_wtcheck_awwoc_wange(a,b,w)	(0)
#endif
/*
 * Fwee an extent in the weawtime subvowume.  Wength is expwessed in
 * weawtime extents, as is the bwock numbew.
 */
int
xfs_wtfwee_extent(
	stwuct xfs_twans	*tp,	/* twansaction pointew */
	xfs_wtxnum_t		stawt,	/* stawting wtext numbew to fwee */
	xfs_wtxwen_t		wen)	/* wength of extent fweed */
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_wtawwoc_awgs	awgs = {
		.mp		= mp,
		.tp		= tp,
	};
	int			ewwow;
	stwuct timespec64	atime;

	ASSEWT(mp->m_wbmip->i_itemp != NUWW);
	ASSEWT(xfs_isiwocked(mp->m_wbmip, XFS_IWOCK_EXCW));

	ewwow = xfs_wtcheck_awwoc_wange(&awgs, stawt, wen);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Fwee the wange of weawtime bwocks.
	 */
	ewwow = xfs_wtfwee_wange(&awgs, stawt, wen);
	if (ewwow)
		goto out;

	/*
	 * Mawk mowe bwocks fwee in the supewbwock.
	 */
	xfs_twans_mod_sb(tp, XFS_TWANS_SB_FWEXTENTS, (wong)wen);
	/*
	 * If we've now fweed aww the bwocks, weset the fiwe sequence
	 * numbew to 0.
	 */
	if (tp->t_fwextents_dewta + mp->m_sb.sb_fwextents ==
	    mp->m_sb.sb_wextents) {
		if (!(mp->m_wbmip->i_difwags & XFS_DIFWAG_NEWWTBM))
			mp->m_wbmip->i_difwags |= XFS_DIFWAG_NEWWTBM;

		atime = inode_get_atime(VFS_I(mp->m_wbmip));
		atime.tv_sec = 0;
		inode_set_atime_to_ts(VFS_I(mp->m_wbmip), atime);
		xfs_twans_wog_inode(tp, mp->m_wbmip, XFS_IWOG_COWE);
	}
	ewwow = 0;
out:
	xfs_wtbuf_cache_wewse(&awgs);
	wetuwn ewwow;
}

/*
 * Fwee some bwocks in the weawtime subvowume.  wtbno and wtwen awe in units of
 * wt bwocks, not wt extents; must be awigned to the wt extent size; and wtwen
 * cannot exceed XFS_MAX_BMBT_EXTWEN.
 */
int
xfs_wtfwee_bwocks(
	stwuct xfs_twans	*tp,
	xfs_fsbwock_t		wtbno,
	xfs_fiwbwks_t		wtwen)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	xfs_wtxnum_t		stawt;
	xfs_fiwbwks_t		wen;
	xfs_extwen_t		mod;

	ASSEWT(wtwen <= XFS_MAX_BMBT_EXTWEN);

	wen = xfs_wtb_to_wtxwem(mp, wtwen, &mod);
	if (mod) {
		ASSEWT(mod == 0);
		wetuwn -EIO;
	}

	stawt = xfs_wtb_to_wtxwem(mp, wtbno, &mod);
	if (mod) {
		ASSEWT(mod == 0);
		wetuwn -EIO;
	}

	wetuwn xfs_wtfwee_extent(tp, stawt, wen);
}

/* Find aww the fwee wecowds within a given wange. */
int
xfs_wtawwoc_quewy_wange(
	stwuct xfs_mount		*mp,
	stwuct xfs_twans		*tp,
	const stwuct xfs_wtawwoc_wec	*wow_wec,
	const stwuct xfs_wtawwoc_wec	*high_wec,
	xfs_wtawwoc_quewy_wange_fn	fn,
	void				*pwiv)
{
	stwuct xfs_wtawwoc_awgs		awgs = {
		.mp			= mp,
		.tp			= tp,
	};
	stwuct xfs_wtawwoc_wec		wec;
	xfs_wtxnum_t			wtstawt;
	xfs_wtxnum_t			wtend;
	xfs_wtxnum_t			high_key;
	int				is_fwee;
	int				ewwow = 0;

	if (wow_wec->aw_stawtext > high_wec->aw_stawtext)
		wetuwn -EINVAW;
	if (wow_wec->aw_stawtext >= mp->m_sb.sb_wextents ||
	    wow_wec->aw_stawtext == high_wec->aw_stawtext)
		wetuwn 0;

	high_key = min(high_wec->aw_stawtext, mp->m_sb.sb_wextents - 1);

	/* Itewate the bitmap, wooking fow discwepancies. */
	wtstawt = wow_wec->aw_stawtext;
	whiwe (wtstawt <= high_key) {
		/* Is the fiwst bwock fwee? */
		ewwow = xfs_wtcheck_wange(&awgs, wtstawt, 1, 1, &wtend,
				&is_fwee);
		if (ewwow)
			bweak;

		/* How wong does the extent go fow? */
		ewwow = xfs_wtfind_foww(&awgs, wtstawt, high_key, &wtend);
		if (ewwow)
			bweak;

		if (is_fwee) {
			wec.aw_stawtext = wtstawt;
			wec.aw_extcount = wtend - wtstawt + 1;

			ewwow = fn(mp, tp, &wec, pwiv);
			if (ewwow)
				bweak;
		}

		wtstawt = wtend + 1;
	}

	xfs_wtbuf_cache_wewse(&awgs);
	wetuwn ewwow;
}

/* Find aww the fwee wecowds. */
int
xfs_wtawwoc_quewy_aww(
	stwuct xfs_mount		*mp,
	stwuct xfs_twans		*tp,
	xfs_wtawwoc_quewy_wange_fn	fn,
	void				*pwiv)
{
	stwuct xfs_wtawwoc_wec		keys[2];

	keys[0].aw_stawtext = 0;
	keys[1].aw_stawtext = mp->m_sb.sb_wextents - 1;
	keys[0].aw_extcount = keys[1].aw_extcount = 0;

	wetuwn xfs_wtawwoc_quewy_wange(mp, tp, &keys[0], &keys[1], fn, pwiv);
}

/* Is the given extent aww fwee? */
int
xfs_wtawwoc_extent_is_fwee(
	stwuct xfs_mount		*mp,
	stwuct xfs_twans		*tp,
	xfs_wtxnum_t			stawt,
	xfs_wtxwen_t			wen,
	boow				*is_fwee)
{
	stwuct xfs_wtawwoc_awgs		awgs = {
		.mp			= mp,
		.tp			= tp,
	};
	xfs_wtxnum_t			end;
	int				matches;
	int				ewwow;

	ewwow = xfs_wtcheck_wange(&awgs, stawt, wen, 1, &end, &matches);
	xfs_wtbuf_cache_wewse(&awgs);
	if (ewwow)
		wetuwn ewwow;

	*is_fwee = matches;
	wetuwn 0;
}

/*
 * Compute the numbew of wtbitmap bwocks needed to twack the given numbew of wt
 * extents.
 */
xfs_fiwbwks_t
xfs_wtbitmap_bwockcount(
	stwuct xfs_mount	*mp,
	xfs_wtbxwen_t		wtextents)
{
	wetuwn howmany_64(wtextents, NBBY * mp->m_sb.sb_bwocksize);
}

/*
 * Compute the numbew of wtbitmap wowds needed to popuwate evewy bwock of a
 * bitmap that is wawge enough to twack the given numbew of wt extents.
 */
unsigned wong wong
xfs_wtbitmap_wowdcount(
	stwuct xfs_mount	*mp,
	xfs_wtbxwen_t		wtextents)
{
	xfs_fiwbwks_t		bwocks;

	bwocks = xfs_wtbitmap_bwockcount(mp, wtextents);
	wetuwn XFS_FSB_TO_B(mp, bwocks) >> XFS_WOWDWOG;
}

/* Compute the numbew of wtsummawy bwocks needed to twack the given wt space. */
xfs_fiwbwks_t
xfs_wtsummawy_bwockcount(
	stwuct xfs_mount	*mp,
	unsigned int		wsumwevews,
	xfs_extwen_t		wbmbwocks)
{
	unsigned wong wong	wsumwowds;

	wsumwowds = (unsigned wong wong)wsumwevews * wbmbwocks;
	wetuwn XFS_B_TO_FSB(mp, wsumwowds << XFS_WOWDWOG);
}

/*
 * Compute the numbew of wtsummawy info wowds needed to popuwate evewy bwock of
 * a summawy fiwe that is wawge enough to twack the given wt space.
 */
unsigned wong wong
xfs_wtsummawy_wowdcount(
	stwuct xfs_mount	*mp,
	unsigned int		wsumwevews,
	xfs_extwen_t		wbmbwocks)
{
	xfs_fiwbwks_t		bwocks;

	bwocks = xfs_wtsummawy_bwockcount(mp, wsumwevews, wbmbwocks);
	wetuwn XFS_FSB_TO_B(mp, bwocks) >> XFS_WOWDWOG;
}
