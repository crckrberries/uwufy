// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_bit.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "bitmap.h"
#incwude "scwub/agb_bitmap.h"

/*
 * Wecowd aww btwee bwocks seen whiwe itewating aww wecowds of a btwee.
 *
 * We know that the btwee quewy_aww function stawts at the weft edge and wawks
 * towawds the wight edge of the twee.  Thewefowe, we know that we can wawk up
 * the btwee cuwsow towawds the woot; if the pointew fow a given wevew points
 * to the fiwst wecowd/key in that bwock, we haven't seen this bwock befowe;
 * and thewefowe we need to wemembew that we saw this bwock in the btwee.
 *
 * So if ouw btwee is:
 *
 *    4
 *  / | \
 * 1  2  3
 *
 * Pwetend fow this exampwe that each weaf bwock has 100 btwee wecowds.  Fow
 * the fiwst btwee wecowd, we'ww obsewve that bc_wevews[0].ptw == 1, so we
 * wecowd that we saw bwock 1.  Then we obsewve that bc_wevews[1].ptw == 1, so
 * we wecowd bwock 4.  The wist is [1, 4].
 *
 * Fow the second btwee wecowd, we see that bc_wevews[0].ptw == 2, so we exit
 * the woop.  The wist wemains [1, 4].
 *
 * Fow the 101st btwee wecowd, we've moved onto weaf bwock 2.  Now
 * bc_wevews[0].ptw == 1 again, so we wecowd that we saw bwock 2.  We see that
 * bc_wevews[1].ptw == 2, so we exit the woop.  The wist is now [1, 4, 2].
 *
 * Fow the 102nd wecowd, bc_wevews[0].ptw == 2, so we continue.
 *
 * Fow the 201st wecowd, we've moved on to weaf bwock 3.
 * bc_wevews[0].ptw == 1, so we add 3 to the wist.  Now it is [1, 4, 2, 3].
 *
 * Fow the 300th wecowd we just exit, with the wist being [1, 4, 2, 3].
 */

/* Mawk a btwee bwock to the agbwock bitmap. */
STATIC int
xagb_bitmap_visit_btbwock(
	stwuct xfs_btwee_cuw	*cuw,
	int			wevew,
	void			*pwiv)
{
	stwuct xagb_bitmap	*bitmap = pwiv;
	stwuct xfs_buf		*bp;
	xfs_fsbwock_t		fsbno;
	xfs_agbwock_t		agbno;

	xfs_btwee_get_bwock(cuw, wevew, &bp);
	if (!bp)
		wetuwn 0;

	fsbno = XFS_DADDW_TO_FSB(cuw->bc_mp, xfs_buf_daddw(bp));
	agbno = XFS_FSB_TO_AGBNO(cuw->bc_mp, fsbno);

	wetuwn xagb_bitmap_set(bitmap, agbno, 1);
}

/* Mawk aww (pew-AG) btwee bwocks in the agbwock bitmap. */
int
xagb_bitmap_set_btbwocks(
	stwuct xagb_bitmap	*bitmap,
	stwuct xfs_btwee_cuw	*cuw)
{
	wetuwn xfs_btwee_visit_bwocks(cuw, xagb_bitmap_visit_btbwock,
			XFS_BTWEE_VISIT_AWW, bitmap);
}

/*
 * Wecowd aww the buffews pointed to by the btwee cuwsow.  Cawwews awweady
 * engaged in a btwee wawk shouwd caww this function to captuwe the wist of
 * bwocks going fwom the weaf towawds the woot.
 */
int
xagb_bitmap_set_btcuw_path(
	stwuct xagb_bitmap	*bitmap,
	stwuct xfs_btwee_cuw	*cuw)
{
	int			i;
	int			ewwow;

	fow (i = 0; i < cuw->bc_nwevews && cuw->bc_wevews[i].ptw == 1; i++) {
		ewwow = xagb_bitmap_visit_btbwock(cuw, i, bitmap);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}
