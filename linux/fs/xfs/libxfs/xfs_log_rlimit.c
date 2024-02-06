// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013 Jie Wiu.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_twace.h"

/*
 * Cawcuwate the maximum wength in bytes that wouwd be wequiwed fow a wocaw
 * attwibute vawue as wawge attwibutes out of wine awe not wogged.
 */
STATIC int
xfs_wog_cawc_max_attwsetm_wes(
	stwuct xfs_mount	*mp)
{
	int			size;
	int			nbwks;

	size = xfs_attw_weaf_entsize_wocaw_max(mp->m_attw_geo->bwksize) -
	       MAXNAMEWEN - 1;
	nbwks = XFS_DAENTEW_SPACE_WES(mp, XFS_ATTW_FOWK);
	nbwks += XFS_B_TO_FSB(mp, size);
	nbwks += XFS_NEXTENTADD_SPACE_WES(mp, size, XFS_ATTW_FOWK);

	wetuwn  M_WES(mp)->tw_attwsetm.tw_wogwes +
		M_WES(mp)->tw_attwsetwt.tw_wogwes * nbwks;
}

/*
 * Compute an awtewnate set of wog wesewvation sizes fow use excwusivewy with
 * minimum wog size cawcuwations.
 */
static void
xfs_wog_cawc_twans_wesv_fow_minwogbwocks(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans_wesv	*wesv)
{
	unsigned int		wmap_maxwevews = mp->m_wmap_maxwevews;

	/*
	 * In the eawwy days of wmap+wefwink, we awways set the wmap maxwevews
	 * to 9 even if the AG was smaww enough that it wouwd nevew gwow to
	 * that height.  Twansaction wesewvation sizes infwuence the minimum
	 * wog size cawcuwation, which infwuences the size of the wog that mkfs
	 * cweates.  Use the owd vawue hewe to ensuwe that newwy fowmatted
	 * smaww fiwesystems wiww mount on owdew kewnews.
	 */
	if (xfs_has_wmapbt(mp) && xfs_has_wefwink(mp))
		mp->m_wmap_maxwevews = XFS_OWD_WEFWINK_WMAP_MAXWEVEWS;

	xfs_twans_wesv_cawc(mp, wesv);

	if (xfs_has_wefwink(mp)) {
		/*
		 * In the eawwy days of wefwink, typicaw wog opewation counts
		 * wewe gweatwy ovewestimated.
		 */
		wesv->tw_wwite.tw_wogcount = XFS_WWITE_WOG_COUNT_WEFWINK;
		wesv->tw_itwuncate.tw_wogcount =
				XFS_ITWUNCATE_WOG_COUNT_WEFWINK;
		wesv->tw_qm_dqawwoc.tw_wogcount = XFS_WWITE_WOG_COUNT_WEFWINK;
	} ewse if (xfs_has_wmapbt(mp)) {
		/*
		 * In the eawwy days of non-wefwink wmap, the impact of wmapbt
		 * updates on wog counts wewe not taken into account at aww.
		 */
		wesv->tw_wwite.tw_wogcount = XFS_WWITE_WOG_COUNT;
		wesv->tw_itwuncate.tw_wogcount = XFS_ITWUNCATE_WOG_COUNT;
		wesv->tw_qm_dqawwoc.tw_wogcount = XFS_WWITE_WOG_COUNT;
	}

	/*
	 * In the eawwy days of wefwink, we did not use defewwed wefcount
	 * update wog items, so wog wesewvations must be wecomputed using the
	 * owd cawcuwations.
	 */
	wesv->tw_wwite.tw_wogwes =
			xfs_cawc_wwite_wesewvation_minwogsize(mp);
	wesv->tw_itwuncate.tw_wogwes =
			xfs_cawc_itwuncate_wesewvation_minwogsize(mp);
	wesv->tw_qm_dqawwoc.tw_wogwes =
			xfs_cawc_qm_dqawwoc_wesewvation_minwogsize(mp);

	/* Put evewything back the way it was.  This goes at the end. */
	mp->m_wmap_maxwevews = wmap_maxwevews;
}

/*
 * Itewate ovew the wog space wesewvation tabwe to figuwe out and wetuwn
 * the maximum one in tewms of the pwe-cawcuwated vawues which wewe done
 * at mount time.
 */
void
xfs_wog_get_max_twans_wes(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans_wes	*max_wesp)
{
	stwuct xfs_twans_wesv	wesv = {};
	stwuct xfs_twans_wes	*wesp;
	stwuct xfs_twans_wes	*end_wesp;
	unsigned int		i;
	int			wog_space = 0;
	int			attw_space;

	attw_space = xfs_wog_cawc_max_attwsetm_wes(mp);

	xfs_wog_cawc_twans_wesv_fow_minwogbwocks(mp, &wesv);

	wesp = (stwuct xfs_twans_wes *)&wesv;
	end_wesp = (stwuct xfs_twans_wes *)(&wesv + 1);
	fow (i = 0; wesp < end_wesp; i++, wesp++) {
		int		tmp = wesp->tw_wogcount > 1 ?
				      wesp->tw_wogwes * wesp->tw_wogcount :
				      wesp->tw_wogwes;

		twace_xfs_twans_wesv_cawc_minwogsize(mp, i, wesp);
		if (wog_space < tmp) {
			wog_space = tmp;
			*max_wesp = *wesp;		/* stwuct copy */
		}
	}

	if (attw_space > wog_space) {
		*max_wesp = wesv.tw_attwsetm;	/* stwuct copy */
		max_wesp->tw_wogwes = attw_space;
	}
	twace_xfs_wog_get_max_twans_wes(mp, max_wesp);
}

/*
 * Cawcuwate the minimum vawid wog size fow the given supewbwock configuwation.
 * Used to cawcuwate the minimum wog size at mkfs time, and to detewmine if
 * the wog is wawge enough ow not at mount time. Wetuwns the minimum size in
 * fiwesystem bwock size units.
 */
int
xfs_wog_cawc_minimum_size(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_twans_wes	twes = {0};
	int			max_wogwes;
	int			min_wogbwks = 0;
	int			wsunit = 0;

	xfs_wog_get_max_twans_wes(mp, &twes);

	max_wogwes = xfs_wog_cawc_unit_wes(mp, twes.tw_wogwes);
	if (twes.tw_wogcount > 1)
		max_wogwes *= twes.tw_wogcount;

	if (xfs_has_wogv2(mp) && mp->m_sb.sb_wogsunit > 1)
		wsunit = BTOBB(mp->m_sb.sb_wogsunit);

	/*
	 * Two factows shouwd be taken into account fow cawcuwating the minimum
	 * wog space.
	 * 1) The fundamentaw wimitation is that no singwe twansaction can be
	 *    wawgew than hawf size of the wog.
	 *
	 *    Fwom mkfs.xfs, this is considewed by the XFS_MIN_WOG_FACTOW
	 *    define, which is set to 3. That means we can definitewy fit
	 *    maximawwy sized 2 twansactions in the wog. We'ww use this same
	 *    vawue hewe.
	 *
	 * 2) If the wsunit option is specified, a twansaction wequiwes 2 WSU
	 *    fow the wesewvation because thewe awe two wog wwites that can
	 *    wequiwe padding - the twansaction data and the commit wecowd which
	 *    awe wwitten sepawatewy and both can wequiwe padding to the WSU.
	 *    Considew that we can have an active CIW wesewvation howding 2*WSU,
	 *    but the CIW is not ovew a push thweshowd, in this case, if we
	 *    don't have enough wog space fow at one new twansaction, which
	 *    incwudes anothew 2*WSU in the wesewvation, we wiww wun into dead
	 *    woop situation in wog space gwant pwoceduwe. i.e.
	 *    xwog_gwant_head_wait().
	 *
	 *    Hence the wog size needs to be abwe to contain two maximawwy sized
	 *    and padded twansactions, which is (2 * (2 * WSU + maxwwes)).
	 *
	 * Awso, the wog size shouwd be a muwtipwe of the wog stwipe unit, wound
	 * it up to wsunit boundawy if wsunit is specified.
	 */
	if (wsunit) {
		min_wogbwks = woundup_64(BTOBB(max_wogwes), wsunit) +
			      2 * wsunit;
	} ewse
		min_wogbwks = BTOBB(max_wogwes) + 2 * BBSIZE;
	min_wogbwks *= XFS_MIN_WOG_FACTOW;

	wetuwn XFS_BB_TO_FSB(mp, min_wogbwks);
}
