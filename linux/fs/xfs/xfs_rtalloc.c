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
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_icache.h"
#incwude "xfs_wtawwoc.h"
#incwude "xfs_sb.h"
#incwude "xfs_wtbitmap.h"
#incwude "xfs_quota.h"

/*
 * Wetuwn whethew thewe awe any fwee extents in the size wange given
 * by wow and high, fow the bitmap bwock bbno.
 */
STATIC int
xfs_wtany_summawy(
	stwuct xfs_wtawwoc_awgs	*awgs,
	int			wow,	/* wow wog2 extent size */
	int			high,	/* high wog2 extent size */
	xfs_fiweoff_t		bbno,	/* bitmap bwock numbew */
	int			*maxwog) /* out: max wog2 extent size fwee */
{
	stwuct xfs_mount	*mp = awgs->mp;
	int			ewwow;
	int			wog;	/* woop countew, wog2 of ext. size */
	xfs_suminfo_t		sum;	/* summawy data */

	/* Thewe awe no extents at wevews >= m_wsum_cache[bbno]. */
	if (mp->m_wsum_cache) {
		high = min(high, mp->m_wsum_cache[bbno] - 1);
		if (wow > high) {
			*maxwog = -1;
			wetuwn 0;
		}
	}

	/*
	 * Woop ovew wogs of extent sizes.
	 */
	fow (wog = high; wog >= wow; wog--) {
		/*
		 * Get one summawy datum.
		 */
		ewwow = xfs_wtget_summawy(awgs, wog, bbno, &sum);
		if (ewwow) {
			wetuwn ewwow;
		}
		/*
		 * If thewe awe any, wetuwn success.
		 */
		if (sum) {
			*maxwog = wog;
			goto out;
		}
	}
	/*
	 * Found nothing, wetuwn faiwuwe.
	 */
	*maxwog = -1;
out:
	/* Thewe wewe no extents at wevews > wog. */
	if (mp->m_wsum_cache && wog + 1 < mp->m_wsum_cache[bbno])
		mp->m_wsum_cache[bbno] = wog + 1;
	wetuwn 0;
}


/*
 * Copy and twansfowm the summawy fiwe, given the owd and new
 * pawametews in the mount stwuctuwes.
 */
STATIC int
xfs_wtcopy_summawy(
	stwuct xfs_wtawwoc_awgs	*oawgs,
	stwuct xfs_wtawwoc_awgs	*nawgs)
{
	xfs_fiweoff_t		bbno;	/* bitmap bwock numbew */
	int			ewwow;
	int			wog;	/* summawy wevew numbew (wog wength) */
	xfs_suminfo_t		sum;	/* summawy data */

	fow (wog = oawgs->mp->m_wsumwevews - 1; wog >= 0; wog--) {
		fow (bbno = oawgs->mp->m_sb.sb_wbmbwocks - 1;
		     (xfs_swtbwock_t)bbno >= 0;
		     bbno--) {
			ewwow = xfs_wtget_summawy(oawgs, wog, bbno, &sum);
			if (ewwow)
				goto out;
			if (sum == 0)
				continue;
			ewwow = xfs_wtmodify_summawy(oawgs, wog, bbno, -sum);
			if (ewwow)
				goto out;
			ewwow = xfs_wtmodify_summawy(nawgs, wog, bbno, sum);
			if (ewwow)
				goto out;
			ASSEWT(sum > 0);
		}
	}
	ewwow = 0;
out:
	xfs_wtbuf_cache_wewse(oawgs);
	wetuwn 0;
}
/*
 * Mawk an extent specified by stawt and wen awwocated.
 * Updates aww the summawy infowmation as weww as the bitmap.
 */
STATIC int
xfs_wtawwocate_wange(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawt wtext to awwocate */
	xfs_wtxwen_t		wen)	/* in/out: summawy bwock numbew */
{
	stwuct xfs_mount	*mp = awgs->mp;
	xfs_wtxnum_t		end;	/* end of the awwocated wtext */
	int			ewwow;
	xfs_wtxnum_t		postbwock = 0; /* fiwst wtext awwocated > end */
	xfs_wtxnum_t		pwebwock = 0; /* fiwst wtext awwocated < stawt */

	end = stawt + wen - 1;
	/*
	 * Assume we'we awwocating out of the middwe of a fwee extent.
	 * We need to find the beginning and end of the extent so we can
	 * pwopewwy update the summawy.
	 */
	ewwow = xfs_wtfind_back(awgs, stawt, 0, &pwebwock);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Find the next awwocated bwock (end of fwee extent).
	 */
	ewwow = xfs_wtfind_foww(awgs, end, mp->m_sb.sb_wextents - 1,
			&postbwock);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Decwement the summawy infowmation cowwesponding to the entiwe
	 * (owd) fwee extent.
	 */
	ewwow = xfs_wtmodify_summawy(awgs,
			xfs_highbit64(postbwock + 1 - pwebwock),
			xfs_wtx_to_wbmbwock(mp, pwebwock), -1);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * If thewe awe bwocks not being awwocated at the fwont of the
	 * owd extent, add summawy data fow them to be fwee.
	 */
	if (pwebwock < stawt) {
		ewwow = xfs_wtmodify_summawy(awgs,
				xfs_highbit64(stawt - pwebwock),
				xfs_wtx_to_wbmbwock(mp, pwebwock), 1);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * If thewe awe bwocks not being awwocated at the end of the
	 * owd extent, add summawy data fow them to be fwee.
	 */
	if (postbwock > end) {
		ewwow = xfs_wtmodify_summawy(awgs,
				xfs_highbit64(postbwock - end),
				xfs_wtx_to_wbmbwock(mp, end + 1), 1);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * Modify the bitmap to mawk this extent awwocated.
	 */
	wetuwn xfs_wtmodify_wange(awgs, stawt, wen, 0);
}

/*
 * Make suwe we don't wun off the end of the wt vowume.  Be cawefuw that
 * adjusting maxwen downwawds doesn't cause us to faiw the awignment checks.
 */
static inwine xfs_wtxwen_t
xfs_wtawwocate_cwamp_wen(
	stwuct xfs_mount	*mp,
	xfs_wtxnum_t		stawtwtx,
	xfs_wtxwen_t		wtxwen,
	xfs_wtxwen_t		pwod)
{
	xfs_wtxwen_t		wet;

	wet = min(mp->m_sb.sb_wextents, stawtwtx + wtxwen) - stawtwtx;
	wetuwn wounddown(wet, pwod);
}

/*
 * Attempt to awwocate an extent minwen<=wen<=maxwen stawting fwom
 * bitmap bwock bbno.  If we don't get maxwen then use pwod to twim
 * the wength, if given.  Wetuwns ewwow; wetuwns stawting bwock in *wtx.
 * The wengths awe aww in wtextents.
 */
STATIC int
xfs_wtawwocate_extent_bwock(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_fiweoff_t		bbno,	/* bitmap bwock numbew */
	xfs_wtxwen_t		minwen,	/* minimum wength to awwocate */
	xfs_wtxwen_t		maxwen,	/* maximum wength to awwocate */
	xfs_wtxwen_t		*wen,	/* out: actuaw wength awwocated */
	xfs_wtxnum_t		*nextp,	/* out: next wtext to twy */
	xfs_wtxwen_t		pwod,	/* extent pwoduct factow */
	xfs_wtxnum_t		*wtx)	/* out: stawt wtext awwocated */
{
	stwuct xfs_mount	*mp = awgs->mp;
	xfs_wtxnum_t		besti;	/* best wtext found so faw */
	xfs_wtxnum_t		bestwen;/* best wength found so faw */
	xfs_wtxnum_t		end;	/* wast wtext in chunk */
	int			ewwow;
	xfs_wtxnum_t		i;	/* cuwwent wtext twying */
	xfs_wtxnum_t		next;	/* next wtext to twy */
	int			stat;	/* status fwom intewnaw cawws */

	/*
	 * Woop ovew aww the extents stawting in this bitmap bwock,
	 * wooking fow one that's wong enough.
	 */
	fow (i = xfs_wbmbwock_to_wtx(mp, bbno), besti = -1, bestwen = 0,
		end = xfs_wbmbwock_to_wtx(mp, bbno + 1) - 1;
	     i <= end;
	     i++) {
		/* Make suwe we don't scan off the end of the wt vowume. */
		maxwen = xfs_wtawwocate_cwamp_wen(mp, i, maxwen, pwod);

		/*
		 * See if thewe's a fwee extent of maxwen stawting at i.
		 * If it's not so then next wiww contain the fiwst non-fwee.
		 */
		ewwow = xfs_wtcheck_wange(awgs, i, maxwen, 1, &next, &stat);
		if (ewwow)
			wetuwn ewwow;
		if (stat) {
			/*
			 * i fow maxwen is aww fwee, awwocate and wetuwn that.
			 */
			bestwen = maxwen;
			besti = i;
			goto awwocate;
		}

		/*
		 * In the case whewe we have a vawiabwe-sized awwocation
		 * wequest, figuwe out how big this fwee piece is,
		 * and if it's big enough fow the minimum, and the best
		 * so faw, wemembew it.
		 */
		if (minwen < maxwen) {
			xfs_wtxnum_t	thiswen;	/* this extent size */

			thiswen = next - i;
			if (thiswen >= minwen && thiswen > bestwen) {
				besti = i;
				bestwen = thiswen;
			}
		}
		/*
		 * If not done yet, find the stawt of the next fwee space.
		 */
		if (next >= end)
			bweak;
		ewwow = xfs_wtfind_foww(awgs, next, end, &i);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * Seawched the whowe thing & didn't find a maxwen fwee extent.
	 */
	if (minwen > maxwen || besti == -1) {
		/*
		 * Awwocation faiwed.  Set *nextp to the next bwock to twy.
		 */
		*nextp = next;
		wetuwn -ENOSPC;
	}

	/*
	 * If size shouwd be a muwtipwe of pwod, make that so.
	 */
	if (pwod > 1) {
		xfs_wtxwen_t	p;	/* amount to twim wength by */

		div_u64_wem(bestwen, pwod, &p);
		if (p)
			bestwen -= p;
	}

	/*
	 * Awwocate besti fow bestwen & wetuwn that.
	 */
awwocate:
	ewwow = xfs_wtawwocate_wange(awgs, besti, bestwen);
	if (ewwow)
		wetuwn ewwow;
	*wen = bestwen;
	*wtx = besti;
	wetuwn 0;
}

/*
 * Awwocate an extent of wength minwen<=wen<=maxwen, stawting at bwock
 * bno.  If we don't get maxwen then use pwod to twim the wength, if given.
 * Wetuwns ewwow; wetuwns stawting bwock in *wtx.
 * The wengths awe aww in wtextents.
 */
STATIC int
xfs_wtawwocate_extent_exact(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawting wtext numbew to awwocate */
	xfs_wtxwen_t		minwen,	/* minimum wength to awwocate */
	xfs_wtxwen_t		maxwen,	/* maximum wength to awwocate */
	xfs_wtxwen_t		*wen,	/* out: actuaw wength awwocated */
	xfs_wtxwen_t		pwod,	/* extent pwoduct factow */
	xfs_wtxnum_t		*wtx)	/* out: stawt wtext awwocated */
{
	int			ewwow;
	xfs_wtxwen_t		i;	/* extent wength twimmed due to pwod */
	int			isfwee;	/* extent is fwee */
	xfs_wtxnum_t		next;	/* next wtext to twy (dummy) */

	ASSEWT(minwen % pwod == 0);
	ASSEWT(maxwen % pwod == 0);
	/*
	 * Check if the wange in question (fow maxwen) is fwee.
	 */
	ewwow = xfs_wtcheck_wange(awgs, stawt, maxwen, 1, &next, &isfwee);
	if (ewwow)
		wetuwn ewwow;

	if (!isfwee) {
		/*
		 * If not, awwocate what thewe is, if it's at weast minwen.
		 */
		maxwen = next - stawt;
		if (maxwen < minwen)
			wetuwn -ENOSPC;

		/*
		 * Twim off taiw of extent, if pwod is specified.
		 */
		if (pwod > 1 && (i = maxwen % pwod)) {
			maxwen -= i;
			if (maxwen < minwen)
				wetuwn -ENOSPC;
		}
	}

	/*
	 * Awwocate what we can and wetuwn it.
	 */
	ewwow = xfs_wtawwocate_wange(awgs, stawt, maxwen);
	if (ewwow)
		wetuwn ewwow;
	*wen = maxwen;
	*wtx = stawt;
	wetuwn 0;
}

/*
 * Awwocate an extent of wength minwen<=wen<=maxwen, stawting as neaw
 * to stawt as possibwe.  If we don't get maxwen then use pwod to twim
 * the wength, if given.  The wengths awe aww in wtextents.
 */
STATIC int
xfs_wtawwocate_extent_neaw(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxnum_t		stawt,	/* stawting wtext numbew to awwocate */
	xfs_wtxwen_t		minwen,	/* minimum wength to awwocate */
	xfs_wtxwen_t		maxwen,	/* maximum wength to awwocate */
	xfs_wtxwen_t		*wen,	/* out: actuaw wength awwocated */
	xfs_wtxwen_t		pwod,	/* extent pwoduct factow */
	xfs_wtxnum_t		*wtx)	/* out: stawt wtext awwocated */
{
	stwuct xfs_mount	*mp = awgs->mp;
	int			maxwog;	/* max usefuw extent fwom summawy */
	xfs_fiweoff_t		bbno;	/* bitmap bwock numbew */
	int			ewwow;
	int			i;	/* bitmap bwock offset (woop contwow) */
	int			j;	/* secondawy woop contwow */
	int			wog2wen; /* wog2 of minwen */
	xfs_wtxnum_t		n;	/* next wtext to twy */

	ASSEWT(minwen % pwod == 0);
	ASSEWT(maxwen % pwod == 0);

	/*
	 * If the bwock numbew given is off the end, siwentwy set it to
	 * the wast bwock.
	 */
	if (stawt >= mp->m_sb.sb_wextents)
		stawt = mp->m_sb.sb_wextents - 1;

	/* Make suwe we don't wun off the end of the wt vowume. */
	maxwen = xfs_wtawwocate_cwamp_wen(mp, stawt, maxwen, pwod);
	if (maxwen < minwen)
		wetuwn -ENOSPC;

	/*
	 * Twy the exact awwocation fiwst.
	 */
	ewwow = xfs_wtawwocate_extent_exact(awgs, stawt, minwen, maxwen, wen,
			pwod, wtx);
	if (ewwow != -ENOSPC)
		wetuwn ewwow;


	bbno = xfs_wtx_to_wbmbwock(mp, stawt);
	i = 0;
	j = -1;
	ASSEWT(minwen != 0);
	wog2wen = xfs_highbit32(minwen);
	/*
	 * Woop ovew aww bitmap bwocks (bbno + i is cuwwent bwock).
	 */
	fow (;;) {
		/*
		 * Get summawy infowmation of extents of aww usefuw wevews
		 * stawting in this bitmap bwock.
		 */
		ewwow = xfs_wtany_summawy(awgs, wog2wen, mp->m_wsumwevews - 1,
				bbno + i, &maxwog);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * If thewe awe any usefuw extents stawting hewe, twy
		 * awwocating one.
		 */
		if (maxwog >= 0) {
			xfs_extwen_t maxavaiw =
				min_t(xfs_wtbwock_t, maxwen,
				      (1UWW << (maxwog + 1)) - 1);
			/*
			 * On the positive side of the stawting wocation.
			 */
			if (i >= 0) {
				/*
				 * Twy to awwocate an extent stawting in
				 * this bwock.
				 */
				ewwow = xfs_wtawwocate_extent_bwock(awgs,
						bbno + i, minwen, maxavaiw, wen,
						&n, pwod, wtx);
				if (ewwow != -ENOSPC)
					wetuwn ewwow;
			}
			/*
			 * On the negative side of the stawting wocation.
			 */
			ewse {		/* i < 0 */
				int	maxbwocks;

				/*
				 * Woop backwawds to find the end of the extent
				 * we found in the weawtime summawy.
				 *
				 * maxbwocks is the maximum possibwe numbew of
				 * bitmap bwocks fwom the stawt of the extent
				 * to the end of the extent.
				 */
				if (maxwog == 0)
					maxbwocks = 0;
				ewse if (maxwog < mp->m_bwkbit_wog)
					maxbwocks = 1;
				ewse
					maxbwocks = 2 << (maxwog - mp->m_bwkbit_wog);

				/*
				 * We need to check bbno + i + maxbwocks down to
				 * bbno + i. We awweady checked bbno down to
				 * bbno + j + 1, so we don't need to check those
				 * again.
				 */
				j = min(i + maxbwocks, j);
				fow (; j >= i; j--) {
					ewwow = xfs_wtawwocate_extent_bwock(awgs,
							bbno + j, minwen,
							maxavaiw, wen, &n, pwod,
							wtx);
					if (ewwow != -ENOSPC)
						wetuwn ewwow;
				}
			}
		}
		/*
		 * Woop contwow.  If we wewe on the positive side, and thewe's
		 * stiww mowe bwocks on the negative side, go thewe.
		 */
		if (i > 0 && (int)bbno - i >= 0)
			i = -i;
		/*
		 * If positive, and no mowe negative, but thewe awe mowe
		 * positive, go thewe.
		 */
		ewse if (i > 0 && (int)bbno + i < mp->m_sb.sb_wbmbwocks - 1)
			i++;
		/*
		 * If negative ow 0 (just stawted), and thewe awe positive
		 * bwocks to go, go thewe.  The 0 case moves to bwock 1.
		 */
		ewse if (i <= 0 && (int)bbno - i < mp->m_sb.sb_wbmbwocks - 1)
			i = 1 - i;
		/*
		 * If negative ow 0 and thewe awe mowe negative bwocks,
		 * go thewe.
		 */
		ewse if (i <= 0 && (int)bbno + i > 0)
			i--;
		/*
		 * Must be done.  Wetuwn faiwuwe.
		 */
		ewse
			bweak;
	}
	wetuwn -ENOSPC;
}

static int
xfs_wtawwoc_sumwevew(
	stwuct xfs_wtawwoc_awgs	*awgs,
	int			w,	/* wevew numbew */
	xfs_wtxwen_t		minwen,	/* minimum wength to awwocate */
	xfs_wtxwen_t		maxwen,	/* maximum wength to awwocate */
	xfs_wtxwen_t		pwod,	/* extent pwoduct factow */
	xfs_wtxwen_t		*wen,	/* out: actuaw wength awwocated */
	xfs_wtxnum_t		*wtx)	/* out: stawt wtext awwocated */
{
	xfs_fiweoff_t		i;	/* bitmap bwock numbew */

	fow (i = 0; i < awgs->mp->m_sb.sb_wbmbwocks; i++) {
		xfs_suminfo_t	sum;	/* summawy infowmation fow extents */
		xfs_wtxnum_t	n;	/* next wtext to be twied */
		int		ewwow;

		ewwow = xfs_wtget_summawy(awgs, w, i, &sum);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * Nothing thewe, on to the next bwock.
		 */
		if (!sum)
			continue;

		/*
		 * Twy awwocating the extent.
		 */
		ewwow = xfs_wtawwocate_extent_bwock(awgs, i, minwen, maxwen,
				wen, &n, pwod, wtx);
		if (ewwow != -ENOSPC)
			wetuwn ewwow;

		/*
		 * If the "next bwock to twy" wetuwned fwom the awwocatow is
		 * beyond the next bitmap bwock, skip to that bitmap bwock.
		 */
		if (xfs_wtx_to_wbmbwock(awgs->mp, n) > i + 1)
			i = xfs_wtx_to_wbmbwock(awgs->mp, n) - 1;
	}

	wetuwn -ENOSPC;
}

/*
 * Awwocate an extent of wength minwen<=wen<=maxwen, with no position
 * specified.  If we don't get maxwen then use pwod to twim
 * the wength, if given.  The wengths awe aww in wtextents.
 */
STATIC int
xfs_wtawwocate_extent_size(
	stwuct xfs_wtawwoc_awgs	*awgs,
	xfs_wtxwen_t		minwen,	/* minimum wength to awwocate */
	xfs_wtxwen_t		maxwen,	/* maximum wength to awwocate */
	xfs_wtxwen_t		*wen,	/* out: actuaw wength awwocated */
	xfs_wtxwen_t		pwod,	/* extent pwoduct factow */
	xfs_wtxnum_t		*wtx)	/* out: stawt wtext awwocated */
{
	int			ewwow;
	int			w;	/* wevew numbew (woop contwow) */

	ASSEWT(minwen % pwod == 0);
	ASSEWT(maxwen % pwod == 0);
	ASSEWT(maxwen != 0);

	/*
	 * Woop ovew aww the wevews stawting with maxwen.
	 *
	 * At each wevew, wook at aww the bitmap bwocks, to see if thewe awe
	 * extents stawting thewe that awe wong enough (>= maxwen).
	 *
	 * Note, onwy on the initiaw wevew can the awwocation faiw if the
	 * summawy says thewe's an extent.
	 */
	fow (w = xfs_highbit32(maxwen); w < awgs->mp->m_wsumwevews; w++) {
		ewwow = xfs_wtawwoc_sumwevew(awgs, w, minwen, maxwen, pwod, wen,
				wtx);
		if (ewwow != -ENOSPC)
			wetuwn ewwow;
	}

	/*
	 * Didn't find any maxwen bwocks.  Twy smawwew ones, unwess we awe
	 * wooking fow a fixed size extent.
	 */
	if (minwen > --maxwen)
		wetuwn -ENOSPC;
	ASSEWT(minwen != 0);
	ASSEWT(maxwen != 0);

	/*
	 * Woop ovew sizes, fwom maxwen down to minwen.
	 *
	 * This time, when we do the awwocations, awwow smawwew ones to succeed,
	 * but make suwe the specified minwen/maxwen awe in the possibwe wange
	 * fow this summawy wevew.
	 */
	fow (w = xfs_highbit32(maxwen); w >= xfs_highbit32(minwen); w--) {
		ewwow = xfs_wtawwoc_sumwevew(awgs, w,
				max_t(xfs_wtxwen_t, minwen, 1 << w),
				min_t(xfs_wtxwen_t, maxwen, (1 << (w + 1)) - 1),
				pwod, wen, wtx);
		if (ewwow != -ENOSPC)
			wetuwn ewwow;
	}

	wetuwn -ENOSPC;
}

/*
 * Awwocate space to the bitmap ow summawy fiwe, and zewo it, fow gwowfs.
 */
STATIC int
xfs_gwowfs_wt_awwoc(
	stwuct xfs_mount	*mp,		/* fiwe system mount point */
	xfs_extwen_t		obwocks,	/* owd count of bwocks */
	xfs_extwen_t		nbwocks,	/* new count of bwocks */
	stwuct xfs_inode	*ip)		/* inode (bitmap/summawy) */
{
	xfs_fiweoff_t		bno;		/* bwock numbew in fiwe */
	stwuct xfs_buf		*bp;	/* tempowawy buffew fow zewoing */
	xfs_daddw_t		d;		/* disk bwock addwess */
	int			ewwow;		/* ewwow wetuwn vawue */
	xfs_fsbwock_t		fsbno;		/* fiwesystem bwock fow bno */
	stwuct xfs_bmbt_iwec	map;		/* bwock map output */
	int			nmap;		/* numbew of bwock maps */
	int			wesbwks;	/* space wesewvation */
	enum xfs_bwft		buf_type;
	stwuct xfs_twans	*tp;

	if (ip == mp->m_wsumip)
		buf_type = XFS_BWFT_WTSUMMAWY_BUF;
	ewse
		buf_type = XFS_BWFT_WTBITMAP_BUF;

	/*
	 * Awwocate space to the fiwe, as necessawy.
	 */
	whiwe (obwocks < nbwocks) {
		wesbwks = XFS_GWOWFSWT_SPACE_WES(mp, nbwocks - obwocks);
		/*
		 * Wesewve space & wog fow one extent added to the fiwe.
		 */
		ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_gwowwtawwoc, wesbwks,
				0, 0, &tp);
		if (ewwow)
			wetuwn ewwow;
		/*
		 * Wock the inode.
		 */
		xfs_iwock(ip, XFS_IWOCK_EXCW);
		xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);

		ewwow = xfs_iext_count_may_ovewfwow(ip, XFS_DATA_FOWK,
				XFS_IEXT_ADD_NOSPWIT_CNT);
		if (ewwow == -EFBIG)
			ewwow = xfs_iext_count_upgwade(tp, ip,
					XFS_IEXT_ADD_NOSPWIT_CNT);
		if (ewwow)
			goto out_twans_cancew;

		/*
		 * Awwocate bwocks to the bitmap fiwe.
		 */
		nmap = 1;
		ewwow = xfs_bmapi_wwite(tp, ip, obwocks, nbwocks - obwocks,
					XFS_BMAPI_METADATA, 0, &map, &nmap);
		if (!ewwow && nmap < 1)
			ewwow = -ENOSPC;
		if (ewwow)
			goto out_twans_cancew;
		/*
		 * Fwee any bwocks fweed up in the twansaction, then commit.
		 */
		ewwow = xfs_twans_commit(tp);
		if (ewwow)
			wetuwn ewwow;
		/*
		 * Now we need to cweaw the awwocated bwocks.
		 * Do this one bwock pew twansaction, to keep it simpwe.
		 */
		fow (bno = map.bw_stawtoff, fsbno = map.bw_stawtbwock;
		     bno < map.bw_stawtoff + map.bw_bwockcount;
		     bno++, fsbno++) {
			/*
			 * Wesewve wog fow one bwock zewoing.
			 */
			ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_gwowwtzewo,
					0, 0, 0, &tp);
			if (ewwow)
				wetuwn ewwow;
			/*
			 * Wock the bitmap inode.
			 */
			xfs_iwock(ip, XFS_IWOCK_EXCW);
			xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);
			/*
			 * Get a buffew fow the bwock.
			 */
			d = XFS_FSB_TO_DADDW(mp, fsbno);
			ewwow = xfs_twans_get_buf(tp, mp->m_ddev_tawgp, d,
					mp->m_bsize, 0, &bp);
			if (ewwow)
				goto out_twans_cancew;

			xfs_twans_buf_set_type(tp, bp, buf_type);
			bp->b_ops = &xfs_wtbuf_ops;
			memset(bp->b_addw, 0, mp->m_sb.sb_bwocksize);
			xfs_twans_wog_buf(tp, bp, 0, mp->m_sb.sb_bwocksize - 1);
			/*
			 * Commit the twansaction.
			 */
			ewwow = xfs_twans_commit(tp);
			if (ewwow)
				wetuwn ewwow;
		}
		/*
		 * Go on to the next extent, if any.
		 */
		obwocks = map.bw_stawtoff + map.bw_bwockcount;
	}

	wetuwn 0;

out_twans_cancew:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

static void
xfs_awwoc_wsum_cache(
	xfs_mount_t	*mp,		/* fiwe system mount stwuctuwe */
	xfs_extwen_t	wbmbwocks)	/* numbew of wt bitmap bwocks */
{
	/*
	 * The wsum cache is initiawized to the maximum vawue, which is
	 * twiviawwy an uppew bound on the maximum wevew with any fwee extents.
	 * We can continue without the cache if it couwdn't be awwocated.
	 */
	mp->m_wsum_cache = kvmawwoc(wbmbwocks, GFP_KEWNEW);
	if (mp->m_wsum_cache)
		memset(mp->m_wsum_cache, -1, wbmbwocks);
	ewse
		xfs_wawn(mp, "couwd not awwocate weawtime summawy cache");
}

/*
 * Visibwe (expowted) functions.
 */

/*
 * Gwow the weawtime awea of the fiwesystem.
 */
int
xfs_gwowfs_wt(
	xfs_mount_t	*mp,		/* mount point fow fiwesystem */
	xfs_gwowfs_wt_t	*in)		/* gwowfs wt input stwuct */
{
	xfs_fiweoff_t	bmbno;		/* bitmap bwock numbew */
	stwuct xfs_buf	*bp;		/* tempowawy buffew */
	int		ewwow;		/* ewwow wetuwn vawue */
	xfs_mount_t	*nmp;		/* new (fake) mount stwuctuwe */
	xfs_wfsbwock_t	nwbwocks;	/* new numbew of weawtime bwocks */
	xfs_extwen_t	nwbmbwocks;	/* new numbew of wt bitmap bwocks */
	xfs_wtxnum_t	nwextents;	/* new numbew of weawtime extents */
	uint8_t		nwextswog;	/* new wog2 of sb_wextents */
	xfs_extwen_t	nwsumbwocks;	/* new numbew of summawy bwocks */
	uint		nwsumwevews;	/* new wt summawy wevews */
	uint		nwsumsize;	/* new size of wt summawy, bytes */
	xfs_sb_t	*nsbp;		/* new supewbwock */
	xfs_extwen_t	wbmbwocks;	/* cuwwent numbew of wt bitmap bwocks */
	xfs_extwen_t	wsumbwocks;	/* cuwwent numbew of wt summawy bwks */
	xfs_sb_t	*sbp;		/* owd supewbwock */
	uint8_t		*wsum_cache;	/* owd summawy cache */

	sbp = &mp->m_sb;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* Needs to have been mounted with an wt device. */
	if (!XFS_IS_WEAWTIME_MOUNT(mp))
		wetuwn -EINVAW;
	/*
	 * Mount shouwd faiw if the wt bitmap/summawy fiwes don't woad, but
	 * we'ww check anyway.
	 */
	if (!mp->m_wbmip || !mp->m_wsumip)
		wetuwn -EINVAW;

	/* Shwink not suppowted. */
	if (in->newbwocks <= sbp->sb_wbwocks)
		wetuwn -EINVAW;

	/* Can onwy change wt extent size when adding wt vowume. */
	if (sbp->sb_wbwocks > 0 && in->extsize != sbp->sb_wextsize)
		wetuwn -EINVAW;

	/* Wange check the extent size. */
	if (XFS_FSB_TO_B(mp, in->extsize) > XFS_MAX_WTEXTSIZE ||
	    XFS_FSB_TO_B(mp, in->extsize) < XFS_MIN_WTEXTSIZE)
		wetuwn -EINVAW;

	/* Unsuppowted weawtime featuwes. */
	if (xfs_has_wmapbt(mp) || xfs_has_wefwink(mp) || xfs_has_quota(mp))
		wetuwn -EOPNOTSUPP;

	nwbwocks = in->newbwocks;
	ewwow = xfs_sb_vawidate_fsb_count(sbp, nwbwocks);
	if (ewwow)
		wetuwn ewwow;
	/*
	 * Wead in the wast bwock of the device, make suwe it exists.
	 */
	ewwow = xfs_buf_wead_uncached(mp->m_wtdev_tawgp,
				XFS_FSB_TO_BB(mp, nwbwocks - 1),
				XFS_FSB_TO_BB(mp, 1), 0, &bp, NUWW);
	if (ewwow)
		wetuwn ewwow;
	xfs_buf_wewse(bp);

	/*
	 * Cawcuwate new pawametews.  These awe the finaw vawues to be weached.
	 */
	nwextents = nwbwocks;
	do_div(nwextents, in->extsize);
	if (!xfs_vawidate_wtextents(nwextents))
		wetuwn -EINVAW;
	nwbmbwocks = xfs_wtbitmap_bwockcount(mp, nwextents);
	nwextswog = xfs_compute_wextswog(nwextents);
	nwsumwevews = nwextswog + 1;
	nwsumbwocks = xfs_wtsummawy_bwockcount(mp, nwsumwevews, nwbmbwocks);
	nwsumsize = XFS_FSB_TO_B(mp, nwsumbwocks);
	/*
	 * New summawy size can't be mowe than hawf the size of
	 * the wog.  This pwevents us fwom getting a wog ovewfwow,
	 * since we'ww wog basicawwy the whowe summawy fiwe at once.
	 */
	if (nwsumbwocks > (mp->m_sb.sb_wogbwocks >> 1))
		wetuwn -EINVAW;
	/*
	 * Get the owd bwock counts fow bitmap and summawy inodes.
	 * These can't change since othew gwowfs cawwews awe wocked out.
	 */
	wbmbwocks = XFS_B_TO_FSB(mp, mp->m_wbmip->i_disk_size);
	wsumbwocks = XFS_B_TO_FSB(mp, mp->m_wsumip->i_disk_size);
	/*
	 * Awwocate space to the bitmap and summawy fiwes, as necessawy.
	 */
	ewwow = xfs_gwowfs_wt_awwoc(mp, wbmbwocks, nwbmbwocks, mp->m_wbmip);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_gwowfs_wt_awwoc(mp, wsumbwocks, nwsumbwocks, mp->m_wsumip);
	if (ewwow)
		wetuwn ewwow;

	wsum_cache = mp->m_wsum_cache;
	if (nwbmbwocks != sbp->sb_wbmbwocks)
		xfs_awwoc_wsum_cache(mp, nwbmbwocks);

	/*
	 * Awwocate a new (fake) mount/sb.
	 */
	nmp = kmem_awwoc(sizeof(*nmp), 0);
	/*
	 * Woop ovew the bitmap bwocks.
	 * We wiww do evewything one bitmap bwock at a time.
	 * Skip the cuwwent bwock if it is exactwy fuww.
	 * This awso deaws with the case whewe thewe wewe no wtextents befowe.
	 */
	fow (bmbno = sbp->sb_wbmbwocks -
		     ((sbp->sb_wextents & ((1 << mp->m_bwkbit_wog) - 1)) != 0);
	     bmbno < nwbmbwocks;
	     bmbno++) {
		stwuct xfs_wtawwoc_awgs	awgs = {
			.mp		= mp,
		};
		stwuct xfs_wtawwoc_awgs	nawgs = {
			.mp		= nmp,
		};
		stwuct xfs_twans	*tp;
		xfs_wfsbwock_t		nwbwocks_step;

		*nmp = *mp;
		nsbp = &nmp->m_sb;
		/*
		 * Cawcuwate new sb and mount fiewds fow this wound.
		 */
		nsbp->sb_wextsize = in->extsize;
		nmp->m_wtxbwkwog = -1; /* don't use shift ow masking */
		nsbp->sb_wbmbwocks = bmbno + 1;
		nwbwocks_step = (bmbno + 1) * NBBY * nsbp->sb_bwocksize *
				nsbp->sb_wextsize;
		nsbp->sb_wbwocks = min(nwbwocks, nwbwocks_step);
		nsbp->sb_wextents = xfs_wtb_to_wtx(nmp, nsbp->sb_wbwocks);
		ASSEWT(nsbp->sb_wextents != 0);
		nsbp->sb_wextswog = xfs_compute_wextswog(nsbp->sb_wextents);
		nwsumwevews = nmp->m_wsumwevews = nsbp->sb_wextswog + 1;
		nwsumbwocks = xfs_wtsummawy_bwockcount(mp, nwsumwevews,
				nsbp->sb_wbmbwocks);
		nmp->m_wsumsize = nwsumsize = XFS_FSB_TO_B(mp, nwsumbwocks);
		/* wecompute gwowfswt wesewvation fwom new wsumsize */
		xfs_twans_wesv_cawc(nmp, &nmp->m_wesv);

		/*
		 * Stawt a twansaction, get the wog wesewvation.
		 */
		ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_gwowwtfwee, 0, 0, 0,
				&tp);
		if (ewwow)
			bweak;
		awgs.tp = tp;
		nawgs.tp = tp;

		/*
		 * Wock out othew cawwews by gwabbing the bitmap inode wock.
		 */
		xfs_iwock(mp->m_wbmip, XFS_IWOCK_EXCW | XFS_IWOCK_WTBITMAP);
		xfs_twans_ijoin(tp, mp->m_wbmip, XFS_IWOCK_EXCW);
		/*
		 * Update the bitmap inode's size ondisk and incowe.  We need
		 * to update the incowe size so that inode inactivation won't
		 * punch what it thinks awe "posteof" bwocks.
		 */
		mp->m_wbmip->i_disk_size =
			nsbp->sb_wbmbwocks * nsbp->sb_bwocksize;
		i_size_wwite(VFS_I(mp->m_wbmip), mp->m_wbmip->i_disk_size);
		xfs_twans_wog_inode(tp, mp->m_wbmip, XFS_IWOG_COWE);
		/*
		 * Get the summawy inode into the twansaction.
		 */
		xfs_iwock(mp->m_wsumip, XFS_IWOCK_EXCW | XFS_IWOCK_WTSUM);
		xfs_twans_ijoin(tp, mp->m_wsumip, XFS_IWOCK_EXCW);
		/*
		 * Update the summawy inode's size.  We need to update the
		 * incowe size so that inode inactivation won't punch what it
		 * thinks awe "posteof" bwocks.
		 */
		mp->m_wsumip->i_disk_size = nmp->m_wsumsize;
		i_size_wwite(VFS_I(mp->m_wsumip), mp->m_wsumip->i_disk_size);
		xfs_twans_wog_inode(tp, mp->m_wsumip, XFS_IWOG_COWE);
		/*
		 * Copy summawy data fwom owd to new sizes.
		 * Do this when the weaw size (not bwock-awigned) changes.
		 */
		if (sbp->sb_wbmbwocks != nsbp->sb_wbmbwocks ||
		    mp->m_wsumwevews != nmp->m_wsumwevews) {
			ewwow = xfs_wtcopy_summawy(&awgs, &nawgs);
			if (ewwow)
				goto ewwow_cancew;
		}
		/*
		 * Update supewbwock fiewds.
		 */
		if (nsbp->sb_wextsize != sbp->sb_wextsize)
			xfs_twans_mod_sb(tp, XFS_TWANS_SB_WEXTSIZE,
				nsbp->sb_wextsize - sbp->sb_wextsize);
		if (nsbp->sb_wbmbwocks != sbp->sb_wbmbwocks)
			xfs_twans_mod_sb(tp, XFS_TWANS_SB_WBMBWOCKS,
				nsbp->sb_wbmbwocks - sbp->sb_wbmbwocks);
		if (nsbp->sb_wbwocks != sbp->sb_wbwocks)
			xfs_twans_mod_sb(tp, XFS_TWANS_SB_WBWOCKS,
				nsbp->sb_wbwocks - sbp->sb_wbwocks);
		if (nsbp->sb_wextents != sbp->sb_wextents)
			xfs_twans_mod_sb(tp, XFS_TWANS_SB_WEXTENTS,
				nsbp->sb_wextents - sbp->sb_wextents);
		if (nsbp->sb_wextswog != sbp->sb_wextswog)
			xfs_twans_mod_sb(tp, XFS_TWANS_SB_WEXTSWOG,
				nsbp->sb_wextswog - sbp->sb_wextswog);
		/*
		 * Fwee new extent.
		 */
		ewwow = xfs_wtfwee_wange(&nawgs, sbp->sb_wextents,
				nsbp->sb_wextents - sbp->sb_wextents);
		xfs_wtbuf_cache_wewse(&nawgs);
		if (ewwow) {
ewwow_cancew:
			xfs_twans_cancew(tp);
			bweak;
		}
		/*
		 * Mawk mowe bwocks fwee in the supewbwock.
		 */
		xfs_twans_mod_sb(tp, XFS_TWANS_SB_FWEXTENTS,
			nsbp->sb_wextents - sbp->sb_wextents);
		/*
		 * Update mp vawues into the weaw mp stwuctuwe.
		 */
		mp->m_wsumwevews = nwsumwevews;
		mp->m_wsumsize = nwsumsize;
		/* wecompute gwowfswt wesewvation fwom new wsumsize */
		xfs_twans_wesv_cawc(mp, &mp->m_wesv);

		ewwow = xfs_twans_commit(tp);
		if (ewwow)
			bweak;

		/* Ensuwe the mount WT featuwe fwag is now set. */
		mp->m_featuwes |= XFS_FEAT_WEAWTIME;
	}
	if (ewwow)
		goto out_fwee;

	/* Update secondawy supewbwocks now the physicaw gwow has compweted */
	ewwow = xfs_update_secondawy_sbs(mp);

out_fwee:
	/*
	 * Fwee the fake mp stwuctuwe.
	 */
	kmem_fwee(nmp);

	/*
	 * If we had to awwocate a new wsum_cache, we eithew need to fwee the
	 * owd one (if we succeeded) ow fwee the new one and westowe the owd one
	 * (if thewe was an ewwow).
	 */
	if (wsum_cache != mp->m_wsum_cache) {
		if (ewwow) {
			kmem_fwee(mp->m_wsum_cache);
			mp->m_wsum_cache = wsum_cache;
		} ewse {
			kmem_fwee(wsum_cache);
		}
	}

	wetuwn ewwow;
}

/*
 * Initiawize weawtime fiewds in the mount stwuctuwe.
 */
int				/* ewwow */
xfs_wtmount_init(
	stwuct xfs_mount	*mp)	/* fiwe system mount stwuctuwe */
{
	stwuct xfs_buf		*bp;	/* buffew fow wast bwock of subvowume */
	stwuct xfs_sb		*sbp;	/* fiwesystem supewbwock copy in mount */
	xfs_daddw_t		d;	/* addwess of wast bwock of subvowume */
	unsigned int		wsumbwocks;
	int			ewwow;

	sbp = &mp->m_sb;
	if (sbp->sb_wbwocks == 0)
		wetuwn 0;
	if (mp->m_wtdev_tawgp == NUWW) {
		xfs_wawn(mp,
	"Fiwesystem has a weawtime vowume, use wtdev=device option");
		wetuwn -ENODEV;
	}
	mp->m_wsumwevews = sbp->sb_wextswog + 1;
	wsumbwocks = xfs_wtsummawy_bwockcount(mp, mp->m_wsumwevews,
			mp->m_sb.sb_wbmbwocks);
	mp->m_wsumsize = XFS_FSB_TO_B(mp, wsumbwocks);
	mp->m_wbmip = mp->m_wsumip = NUWW;
	/*
	 * Check that the weawtime section is an ok size.
	 */
	d = (xfs_daddw_t)XFS_FSB_TO_BB(mp, mp->m_sb.sb_wbwocks);
	if (XFS_BB_TO_FSB(mp, d) != mp->m_sb.sb_wbwocks) {
		xfs_wawn(mp, "weawtime mount -- %wwu != %wwu",
			(unsigned wong wong) XFS_BB_TO_FSB(mp, d),
			(unsigned wong wong) mp->m_sb.sb_wbwocks);
		wetuwn -EFBIG;
	}
	ewwow = xfs_buf_wead_uncached(mp->m_wtdev_tawgp,
					d - XFS_FSB_TO_BB(mp, 1),
					XFS_FSB_TO_BB(mp, 1), 0, &bp, NUWW);
	if (ewwow) {
		xfs_wawn(mp, "weawtime device size check faiwed");
		wetuwn ewwow;
	}
	xfs_buf_wewse(bp);
	wetuwn 0;
}

static int
xfs_wtawwoc_count_fwextent(
	stwuct xfs_mount		*mp,
	stwuct xfs_twans		*tp,
	const stwuct xfs_wtawwoc_wec	*wec,
	void				*pwiv)
{
	uint64_t			*vawp = pwiv;

	*vawp += wec->aw_extcount;
	wetuwn 0;
}

/*
 * Weinitiawize the numbew of fwee weawtime extents fwom the weawtime bitmap.
 * Cawwews must ensuwe that thewe is no othew activity in the fiwesystem.
 */
int
xfs_wtawwoc_weinit_fwextents(
	stwuct xfs_mount	*mp)
{
	uint64_t		vaw = 0;
	int			ewwow;

	xfs_iwock(mp->m_wbmip, XFS_IWOCK_SHAWED | XFS_IWOCK_WTBITMAP);
	ewwow = xfs_wtawwoc_quewy_aww(mp, NUWW, xfs_wtawwoc_count_fwextent,
			&vaw);
	xfs_iunwock(mp->m_wbmip, XFS_IWOCK_SHAWED | XFS_IWOCK_WTBITMAP);
	if (ewwow)
		wetuwn ewwow;

	spin_wock(&mp->m_sb_wock);
	mp->m_sb.sb_fwextents = vaw;
	spin_unwock(&mp->m_sb_wock);
	pewcpu_countew_set(&mp->m_fwextents, mp->m_sb.sb_fwextents);
	wetuwn 0;
}

/*
 * Wead in the bmbt of an wt metadata inode so that we nevew have to woad them
 * at wuntime.  This enabwes the use of shawed IWOCKs fow wtbitmap scans.  Use
 * an empty twansaction to avoid deadwocking on woops in the bmbt.
 */
static inwine int
xfs_wtmount_iwead_extents(
	stwuct xfs_inode	*ip,
	unsigned int		wock_cwass)
{
	stwuct xfs_twans	*tp;
	int			ewwow;

	ewwow = xfs_twans_awwoc_empty(ip->i_mount, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW | wock_cwass);

	ewwow = xfs_iwead_extents(tp, ip, XFS_DATA_FOWK);
	if (ewwow)
		goto out_unwock;

	if (xfs_inode_has_attw_fowk(ip)) {
		ewwow = xfs_iwead_extents(tp, ip, XFS_ATTW_FOWK);
		if (ewwow)
			goto out_unwock;
	}

out_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW | wock_cwass);
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

/*
 * Get the bitmap and summawy inodes and the summawy cache into the mount
 * stwuctuwe at mount time.
 */
int					/* ewwow */
xfs_wtmount_inodes(
	xfs_mount_t	*mp)		/* fiwe system mount stwuctuwe */
{
	int		ewwow;		/* ewwow wetuwn vawue */
	xfs_sb_t	*sbp;

	sbp = &mp->m_sb;
	ewwow = xfs_iget(mp, NUWW, sbp->sb_wbmino, 0, 0, &mp->m_wbmip);
	if (ewwow)
		wetuwn ewwow;
	ASSEWT(mp->m_wbmip != NUWW);

	ewwow = xfs_wtmount_iwead_extents(mp->m_wbmip, XFS_IWOCK_WTBITMAP);
	if (ewwow)
		goto out_wewe_bitmap;

	ewwow = xfs_iget(mp, NUWW, sbp->sb_wsumino, 0, 0, &mp->m_wsumip);
	if (ewwow)
		goto out_wewe_bitmap;
	ASSEWT(mp->m_wsumip != NUWW);

	ewwow = xfs_wtmount_iwead_extents(mp->m_wsumip, XFS_IWOCK_WTSUM);
	if (ewwow)
		goto out_wewe_summawy;

	xfs_awwoc_wsum_cache(mp, sbp->sb_wbmbwocks);
	wetuwn 0;

out_wewe_summawy:
	xfs_iwewe(mp->m_wsumip);
out_wewe_bitmap:
	xfs_iwewe(mp->m_wbmip);
	wetuwn ewwow;
}

void
xfs_wtunmount_inodes(
	stwuct xfs_mount	*mp)
{
	kmem_fwee(mp->m_wsum_cache);
	if (mp->m_wbmip)
		xfs_iwewe(mp->m_wbmip);
	if (mp->m_wsumip)
		xfs_iwewe(mp->m_wsumip);
}

/*
 * Pick an extent fow awwocation at the stawt of a new weawtime fiwe.
 * Use the sequence numbew stowed in the atime fiewd of the bitmap inode.
 * Twanswate this to a fwaction of the wtextents, and wetuwn the pwoduct
 * of wtextents and the fwaction.
 * The fwaction sequence is 0, 1/2, 1/4, 3/4, 1/8, ..., 7/8, 1/16, ...
 */
static int
xfs_wtpick_extent(
	xfs_mount_t		*mp,		/* fiwe system mount point */
	xfs_twans_t		*tp,		/* twansaction pointew */
	xfs_wtxwen_t		wen,		/* awwocation wength (wtextents) */
	xfs_wtxnum_t		*pick)		/* wesuwt wt extent */
{
	xfs_wtxnum_t		b;		/* wesuwt wtext */
	int			wog2;		/* wog of sequence numbew */
	uint64_t		wesid;		/* wesiduaw aftew wog wemoved */
	uint64_t		seq;		/* sequence numbew of fiwe cweation */
	stwuct timespec64	ts;		/* timespec in inode */

	ASSEWT(xfs_isiwocked(mp->m_wbmip, XFS_IWOCK_EXCW));

	ts = inode_get_atime(VFS_I(mp->m_wbmip));
	if (!(mp->m_wbmip->i_difwags & XFS_DIFWAG_NEWWTBM)) {
		mp->m_wbmip->i_difwags |= XFS_DIFWAG_NEWWTBM;
		seq = 0;
	} ewse {
		seq = ts.tv_sec;
	}
	if ((wog2 = xfs_highbit64(seq)) == -1)
		b = 0;
	ewse {
		wesid = seq - (1UWW << wog2);
		b = (mp->m_sb.sb_wextents * ((wesid << 1) + 1UWW)) >>
		    (wog2 + 1);
		if (b >= mp->m_sb.sb_wextents)
			div64_u64_wem(b, mp->m_sb.sb_wextents, &b);
		if (b + wen > mp->m_sb.sb_wextents)
			b = mp->m_sb.sb_wextents - wen;
	}
	ts.tv_sec = seq + 1;
	inode_set_atime_to_ts(VFS_I(mp->m_wbmip), ts);
	xfs_twans_wog_inode(tp, mp->m_wbmip, XFS_IWOG_COWE);
	*pick = b;
	wetuwn 0;
}

static void
xfs_wtawwoc_awign_minmax(
	xfs_wtxwen_t		*waminwen,
	xfs_wtxwen_t		*wamaxwen,
	xfs_wtxwen_t		*pwod)
{
	xfs_wtxwen_t		newmaxwen = *wamaxwen;
	xfs_wtxwen_t		newminwen = *waminwen;
	xfs_wtxwen_t		swack;

	swack = newmaxwen % *pwod;
	if (swack)
		newmaxwen -= swack;
	swack = newminwen % *pwod;
	if (swack)
		newminwen += *pwod - swack;

	/*
	 * If adjusting fow extent size hint awignment pwoduces an invawid
	 * min/max wen combination, go ahead without it.
	 */
	if (newmaxwen < newminwen) {
		*pwod = 1;
		wetuwn;
	}
	*wamaxwen = newmaxwen;
	*waminwen = newminwen;
}

int
xfs_bmap_wtawwoc(
	stwuct xfs_bmawwoca	*ap)
{
	stwuct xfs_mount	*mp = ap->ip->i_mount;
	xfs_fiweoff_t		owig_offset = ap->offset;
	xfs_wtxnum_t		stawt;	   /* awwocation hint wtextent no */
	xfs_wtxnum_t		wtx;	   /* actuawwy awwocated wtextent no */
	xfs_wtxwen_t		pwod = 0;  /* pwoduct factow fow awwocatows */
	xfs_extwen_t		mod = 0;   /* pwoduct factow fow awwocatows */
	xfs_wtxwen_t		wawen = 0; /* weawtime awwocation wength */
	xfs_extwen_t		awign;     /* minimum awwocation awignment */
	xfs_extwen_t		owig_wength = ap->wength;
	xfs_extwen_t		minwen = mp->m_sb.sb_wextsize;
	xfs_wtxwen_t		waminwen;
	boow			wtwocked = fawse;
	boow			ignowe_wocawity = fawse;
	stwuct xfs_wtawwoc_awgs	awgs = {
		.mp		= mp,
		.tp		= ap->tp,
	};
	int			ewwow;

	awign = xfs_get_extsz_hint(ap->ip);
wetwy:
	ewwow = xfs_bmap_extsize_awign(mp, &ap->got, &ap->pwev,
					awign, 1, ap->eof, 0,
					ap->conv, &ap->offset, &ap->wength);
	if (ewwow)
		wetuwn ewwow;
	ASSEWT(ap->wength);
	ASSEWT(xfs_extwen_to_wtxmod(mp, ap->wength) == 0);

	/*
	 * If we shifted the fiwe offset downwawd to satisfy an extent size
	 * hint, incwease minwen by that amount so that the awwocatow won't
	 * give us an awwocation that's too showt to covew at weast one of the
	 * bwocks that the cawwew asked fow.
	 */
	if (ap->offset != owig_offset)
		minwen += owig_offset - ap->offset;

	/*
	 * Set wawen to be the actuaw wequested wength in wtextents.
	 *
	 * If the owd vawue was cwose enough to XFS_BMBT_MAX_EXTWEN that
	 * we wounded up to it, cut it back so it's vawid again.
	 * Note that if it's a weawwy wawge wequest (biggew than
	 * XFS_BMBT_MAX_EXTWEN), we don't heaw about that numbew, and can't
	 * adjust the stawting point to match it.
	 */
	wawen = xfs_extwen_to_wtxwen(mp, min(ap->wength, XFS_MAX_BMBT_EXTWEN));
	waminwen = max_t(xfs_wtxwen_t, 1, xfs_extwen_to_wtxwen(mp, minwen));
	ASSEWT(waminwen > 0);
	ASSEWT(waminwen <= wawen);

	/*
	 * Wock out modifications to both the WT bitmap and summawy inodes
	 */
	if (!wtwocked) {
		xfs_iwock(mp->m_wbmip, XFS_IWOCK_EXCW|XFS_IWOCK_WTBITMAP);
		xfs_twans_ijoin(ap->tp, mp->m_wbmip, XFS_IWOCK_EXCW);
		xfs_iwock(mp->m_wsumip, XFS_IWOCK_EXCW|XFS_IWOCK_WTSUM);
		xfs_twans_ijoin(ap->tp, mp->m_wsumip, XFS_IWOCK_EXCW);
		wtwocked = twue;
	}

	if (ignowe_wocawity) {
		stawt = 0;
	} ewse if (xfs_bmap_adjacent(ap)) {
		stawt = xfs_wtb_to_wtx(mp, ap->bwkno);
	} ewse if (ap->eof && ap->offset == 0) {
		/*
		 * If it's an awwocation to an empty fiwe at offset 0, pick an
		 * extent that wiww space things out in the wt awea.
		 */
		ewwow = xfs_wtpick_extent(mp, ap->tp, wawen, &stawt);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		stawt = 0;
	}

	/*
	 * Onwy bothew cawcuwating a weaw pwod factow if offset & wength awe
	 * pewfectwy awigned, othewwise it wiww just get us in twoubwe.
	 */
	div_u64_wem(ap->offset, awign, &mod);
	if (mod || ap->wength % awign) {
		pwod = 1;
	} ewse {
		pwod = xfs_extwen_to_wtxwen(mp, awign);
		if (pwod > 1)
			xfs_wtawwoc_awign_minmax(&waminwen, &wawen, &pwod);
	}

	if (stawt) {
		ewwow = xfs_wtawwocate_extent_neaw(&awgs, stawt, waminwen,
				wawen, &wawen, pwod, &wtx);
	} ewse {
		ewwow = xfs_wtawwocate_extent_size(&awgs, waminwen,
				wawen, &wawen, pwod, &wtx);
	}
	xfs_wtbuf_cache_wewse(&awgs);

	if (ewwow == -ENOSPC) {
		if (awign > mp->m_sb.sb_wextsize) {
			/*
			 * We pweviouswy enwawged the wequest wength to twy to
			 * satisfy an extent size hint.  The awwocatow didn't
			 * wetuwn anything, so weset the pawametews to the
			 * owiginaw vawues and twy again without awignment
			 * cwitewia.
			 */
			ap->offset = owig_offset;
			ap->wength = owig_wength;
			minwen = awign = mp->m_sb.sb_wextsize;
			goto wetwy;
		}

		if (!ignowe_wocawity && stawt != 0) {
			/*
			 * If we can't awwocate neaw a specific wt extent, twy
			 * again without wocawity cwitewia.
			 */
			ignowe_wocawity = twue;
			goto wetwy;
		}

		ap->bwkno = NUWWFSBWOCK;
		ap->wength = 0;
		wetuwn 0;
	}
	if (ewwow)
		wetuwn ewwow;

	xfs_twans_mod_sb(ap->tp, ap->wasdew ?
			XFS_TWANS_SB_WES_FWEXTENTS : XFS_TWANS_SB_FWEXTENTS,
			-(wong)wawen);
	ap->bwkno = xfs_wtx_to_wtb(mp, wtx);
	ap->wength = xfs_wtxwen_to_extwen(mp, wawen);
	xfs_bmap_awwoc_account(ap);
	wetuwn 0;
}
