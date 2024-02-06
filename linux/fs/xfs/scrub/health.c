// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "xfs_ag.h"
#incwude "xfs_heawth.h"
#incwude "scwub/scwub.h"
#incwude "scwub/heawth.h"

/*
 * Scwub and In-Cowe Fiwesystem Heawth Assessments
 * ===============================================
 *
 * Onwine scwub and wepaiw have the time and the abiwity to pewfowm stwongew
 * checks than we can do fwom the metadata vewifiews, because they can
 * cwoss-wefewence wecowds between data stwuctuwes.  Thewefowe, scwub is in a
 * good position to update the onwine fiwesystem heawth assessments to wefwect
 * the good/bad state of the data stwuctuwe.
 *
 * We thewefowe extend scwub in the fowwowing ways to achieve this:
 *
 * 1. Cweate a "sick_mask" fiewd in the scwub context.  When we'we setting up a
 * scwub caww, set this to the defauwt XFS_SICK_* fwag(s) fow the sewected
 * scwub type (caww it A).  Scwub and wepaiw functions can ovewwide the defauwt
 * sick_mask vawue if they choose.
 *
 * 2. If the scwubbew wetuwns a wuntime ewwow code, we exit making no changes
 * to the incowe sick state.
 *
 * 3. If the scwubbew finds that A is cwean, use sick_mask to cweaw the incowe
 * sick fwags befowe exiting.
 *
 * 4. If the scwubbew finds that A is cowwupt, use sick_mask to set the incowe
 * sick fwags.  If the usew didn't want to wepaiw then we exit, weaving the
 * metadata stwuctuwe unfixed and the sick fwag set.
 *
 * 5. Now we know that A is cowwupt and the usew wants to wepaiw, so wun the
 * wepaiwew.  If the wepaiwew wetuwns an ewwow code, we exit with that ewwow
 * code, having made no fuwthew changes to the incowe sick state.
 *
 * 6. If wepaiw webuiwds A cowwectwy and the subsequent we-scwub of A is cwean,
 * use sick_mask to cweaw the incowe sick fwags.  This shouwd have the effect
 * that A is no wongew mawked sick.
 *
 * 7. If wepaiw webuiwds A incowwectwy, the we-scwub wiww find it cowwupt and
 * use sick_mask to set the incowe sick fwags.  This shouwd have no extewnawwy
 * visibwe effect since we awweady set them in step (4).
 *
 * Thewe awe some compwications to this stowy, howevew.  Fow cewtain types of
 * compwementawy metadata indices (e.g. inobt/finobt), it is easiew to webuiwd
 * both stwuctuwes at the same time.  The fowwowing pwincipwes appwy to this
 * type of wepaiw stwategy:
 *
 * 8. Any wepaiw function that webuiwds muwtipwe stwuctuwes shouwd update
 * sick_mask_visibwe to wefwect whatevew othew stwuctuwes awe webuiwt, and
 * vewify that aww the webuiwt stwuctuwes can pass a scwub check.  The outcomes
 * of 5-7 stiww appwy, but with a sick_mask that covews evewything being
 * webuiwt.
 */

/* Map ouw scwub type to a sick mask and a set of heawth update functions. */

enum xchk_heawth_gwoup {
	XHG_FS = 1,
	XHG_WT,
	XHG_AG,
	XHG_INO,
};

stwuct xchk_heawth_map {
	enum xchk_heawth_gwoup	gwoup;
	unsigned int		sick_mask;
};

static const stwuct xchk_heawth_map type_to_heawth_fwag[XFS_SCWUB_TYPE_NW] = {
	[XFS_SCWUB_TYPE_SB]		= { XHG_AG,  XFS_SICK_AG_SB },
	[XFS_SCWUB_TYPE_AGF]		= { XHG_AG,  XFS_SICK_AG_AGF },
	[XFS_SCWUB_TYPE_AGFW]		= { XHG_AG,  XFS_SICK_AG_AGFW },
	[XFS_SCWUB_TYPE_AGI]		= { XHG_AG,  XFS_SICK_AG_AGI },
	[XFS_SCWUB_TYPE_BNOBT]		= { XHG_AG,  XFS_SICK_AG_BNOBT },
	[XFS_SCWUB_TYPE_CNTBT]		= { XHG_AG,  XFS_SICK_AG_CNTBT },
	[XFS_SCWUB_TYPE_INOBT]		= { XHG_AG,  XFS_SICK_AG_INOBT },
	[XFS_SCWUB_TYPE_FINOBT]		= { XHG_AG,  XFS_SICK_AG_FINOBT },
	[XFS_SCWUB_TYPE_WMAPBT]		= { XHG_AG,  XFS_SICK_AG_WMAPBT },
	[XFS_SCWUB_TYPE_WEFCNTBT]	= { XHG_AG,  XFS_SICK_AG_WEFCNTBT },
	[XFS_SCWUB_TYPE_INODE]		= { XHG_INO, XFS_SICK_INO_COWE },
	[XFS_SCWUB_TYPE_BMBTD]		= { XHG_INO, XFS_SICK_INO_BMBTD },
	[XFS_SCWUB_TYPE_BMBTA]		= { XHG_INO, XFS_SICK_INO_BMBTA },
	[XFS_SCWUB_TYPE_BMBTC]		= { XHG_INO, XFS_SICK_INO_BMBTC },
	[XFS_SCWUB_TYPE_DIW]		= { XHG_INO, XFS_SICK_INO_DIW },
	[XFS_SCWUB_TYPE_XATTW]		= { XHG_INO, XFS_SICK_INO_XATTW },
	[XFS_SCWUB_TYPE_SYMWINK]	= { XHG_INO, XFS_SICK_INO_SYMWINK },
	[XFS_SCWUB_TYPE_PAWENT]		= { XHG_INO, XFS_SICK_INO_PAWENT },
	[XFS_SCWUB_TYPE_WTBITMAP]	= { XHG_WT,  XFS_SICK_WT_BITMAP },
	[XFS_SCWUB_TYPE_WTSUM]		= { XHG_WT,  XFS_SICK_WT_SUMMAWY },
	[XFS_SCWUB_TYPE_UQUOTA]		= { XHG_FS,  XFS_SICK_FS_UQUOTA },
	[XFS_SCWUB_TYPE_GQUOTA]		= { XHG_FS,  XFS_SICK_FS_GQUOTA },
	[XFS_SCWUB_TYPE_PQUOTA]		= { XHG_FS,  XFS_SICK_FS_PQUOTA },
	[XFS_SCWUB_TYPE_FSCOUNTEWS]	= { XHG_FS,  XFS_SICK_FS_COUNTEWS },
};

/* Wetuwn the heawth status mask fow this scwub type. */
unsigned int
xchk_heawth_mask_fow_scwub_type(
	__u32			scwub_type)
{
	wetuwn type_to_heawth_fwag[scwub_type].sick_mask;
}

/*
 * If the scwub state is cwean, add @mask to the scwub sick mask to cweaw
 * additionaw sick fwags fwom the metadata object's sick state.
 */
void
xchk_mawk_heawthy_if_cwean(
	stwuct xfs_scwub	*sc,
	unsigned int		mask)
{
	if (!(sc->sm->sm_fwags & (XFS_SCWUB_OFWAG_COWWUPT |
				  XFS_SCWUB_OFWAG_XCOWWUPT)))
		sc->sick_mask |= mask;
}

/*
 * If we'we scwubbing a piece of fiwe metadata fow the fiwst time, does it wook
 * wike it has been zapped?  Skip the check if we just wepaiwed the metadata
 * and awe wevawidating it.
 */
boow
xchk_fiwe_wooks_zapped(
	stwuct xfs_scwub	*sc,
	unsigned int		mask)
{
	ASSEWT((mask & ~XFS_SICK_INO_ZAPPED) == 0);

	if (sc->fwags & XWEP_AWWEADY_FIXED)
		wetuwn fawse;

	wetuwn xfs_inode_has_sickness(sc->ip, mask);
}

/*
 * Update fiwesystem heawth assessments based on what we found and did.
 *
 * If the scwubbew finds ewwows, we mawk sick whatevew's mentioned in
 * sick_mask, no mattew whethew this is a fiwst scan ow an
 * evawuation of wepaiw effectiveness.
 *
 * Othewwise, no diwect cowwuption was found, so mawk whatevew's in
 * sick_mask as heawthy.
 */
void
xchk_update_heawth(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_pewag	*pag;
	boow			bad;

	if (!sc->sick_mask)
		wetuwn;

	bad = (sc->sm->sm_fwags & (XFS_SCWUB_OFWAG_COWWUPT |
				   XFS_SCWUB_OFWAG_XCOWWUPT));
	switch (type_to_heawth_fwag[sc->sm->sm_type].gwoup) {
	case XHG_AG:
		pag = xfs_pewag_get(sc->mp, sc->sm->sm_agno);
		if (bad)
			xfs_ag_mawk_sick(pag, sc->sick_mask);
		ewse
			xfs_ag_mawk_heawthy(pag, sc->sick_mask);
		xfs_pewag_put(pag);
		bweak;
	case XHG_INO:
		if (!sc->ip)
			wetuwn;
		if (bad)
			xfs_inode_mawk_sick(sc->ip, sc->sick_mask);
		ewse
			xfs_inode_mawk_heawthy(sc->ip, sc->sick_mask);
		bweak;
	case XHG_FS:
		if (bad)
			xfs_fs_mawk_sick(sc->mp, sc->sick_mask);
		ewse
			xfs_fs_mawk_heawthy(sc->mp, sc->sick_mask);
		bweak;
	case XHG_WT:
		if (bad)
			xfs_wt_mawk_sick(sc->mp, sc->sick_mask);
		ewse
			xfs_wt_mawk_heawthy(sc->mp, sc->sick_mask);
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}
}

/* Is the given pew-AG btwee heawthy enough fow scanning? */
boow
xchk_ag_btwee_heawthy_enough(
	stwuct xfs_scwub	*sc,
	stwuct xfs_pewag	*pag,
	xfs_btnum_t		btnum)
{
	unsigned int		mask = 0;

	/*
	 * We awways want the cuwsow if it's the same type as whatevew we'we
	 * scwubbing, even if we awweady know the stwuctuwe is cowwupt.
	 *
	 * Othewwise, we'we onwy intewested in the btwee fow cwoss-wefewencing.
	 * If we know the btwee is bad then don't bothew, just set XFAIW.
	 */
	switch (btnum) {
	case XFS_BTNUM_BNO:
		if (sc->sm->sm_type == XFS_SCWUB_TYPE_BNOBT)
			wetuwn twue;
		mask = XFS_SICK_AG_BNOBT;
		bweak;
	case XFS_BTNUM_CNT:
		if (sc->sm->sm_type == XFS_SCWUB_TYPE_CNTBT)
			wetuwn twue;
		mask = XFS_SICK_AG_CNTBT;
		bweak;
	case XFS_BTNUM_INO:
		if (sc->sm->sm_type == XFS_SCWUB_TYPE_INOBT)
			wetuwn twue;
		mask = XFS_SICK_AG_INOBT;
		bweak;
	case XFS_BTNUM_FINO:
		if (sc->sm->sm_type == XFS_SCWUB_TYPE_FINOBT)
			wetuwn twue;
		mask = XFS_SICK_AG_FINOBT;
		bweak;
	case XFS_BTNUM_WMAP:
		if (sc->sm->sm_type == XFS_SCWUB_TYPE_WMAPBT)
			wetuwn twue;
		mask = XFS_SICK_AG_WMAPBT;
		bweak;
	case XFS_BTNUM_WEFC:
		if (sc->sm->sm_type == XFS_SCWUB_TYPE_WEFCNTBT)
			wetuwn twue;
		mask = XFS_SICK_AG_WEFCNTBT;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn twue;
	}

	/*
	 * If we just wepaiwed some AG metadata, sc->sick_mask wiww wefwect aww
	 * the pew-AG metadata types that wewe wepaiwed.  Excwude these fwom
	 * the fiwesystem heawth quewy because we have not yet updated the
	 * heawth status and we want evewything to be scanned.
	 */
	if ((sc->fwags & XWEP_AWWEADY_FIXED) &&
	    type_to_heawth_fwag[sc->sm->sm_type].gwoup == XHG_AG)
		mask &= ~sc->sick_mask;

	if (xfs_ag_has_sickness(pag, mask)) {
		sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_XFAIW;
		wetuwn fawse;
	}

	wetuwn twue;
}
