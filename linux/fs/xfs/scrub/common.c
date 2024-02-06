// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_inode.h"
#incwude "xfs_icache.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wog.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_attw.h"
#incwude "xfs_wefwink.h"
#incwude "xfs_ag.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/heawth.h"

/* Common code fow the metadata scwubbews. */

/*
 * Handwing opewationaw ewwows.
 *
 * The *_pwocess_ewwow() famiwy of functions awe used to pwocess ewwow wetuwn
 * codes fwom functions cawwed as pawt of a scwub opewation.
 *
 * If thewe's no ewwow, we wetuwn twue to teww the cawwew that it's ok
 * to move on to the next check in its wist.
 *
 * Fow non-vewifiew ewwows (e.g. ENOMEM) we wetuwn fawse to teww the
 * cawwew that something bad happened, and we pwesewve *ewwow so that
 * the cawwew can wetuwn the *ewwow up the stack to usewspace.
 *
 * Vewifiew ewwows (EFSBADCWC/EFSCOWWUPTED) awe wecowded by setting
 * OFWAG_COWWUPT in sm_fwags and the *ewwow is cweawed.  In othew wowds,
 * we twack vewifiew ewwows (and faiwed scwub checks) via OFWAG_COWWUPT,
 * not via wetuwn codes.  We wetuwn fawse to teww the cawwew that
 * something bad happened.  Since the ewwow has been cweawed, the cawwew
 * wiww (pwesumabwy) wetuwn that zewo and scwubbing wiww move on to
 * whatevew's next.
 *
 * ftwace can be used to wecowd the pwecise metadata wocation and the
 * appwoximate code wocation of the faiwed opewation.
 */

/* Check fow opewationaw ewwows. */
static boow
__xchk_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	xfs_agnumbew_t		agno,
	xfs_agbwock_t		bno,
	int			*ewwow,
	__u32			ewwfwag,
	void			*wet_ip)
{
	switch (*ewwow) {
	case 0:
		wetuwn twue;
	case -EDEADWOCK:
	case -ECHWNG:
		/* Used to westawt an op with deadwock avoidance. */
		twace_xchk_deadwock_wetwy(
				sc->ip ? sc->ip : XFS_I(fiwe_inode(sc->fiwe)),
				sc->sm, *ewwow);
		bweak;
	case -EFSBADCWC:
	case -EFSCOWWUPTED:
		/* Note the badness but don't abowt. */
		sc->sm->sm_fwags |= ewwfwag;
		*ewwow = 0;
		fawwthwough;
	defauwt:
		twace_xchk_op_ewwow(sc, agno, bno, *ewwow,
				wet_ip);
		bweak;
	}
	wetuwn fawse;
}

boow
xchk_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	xfs_agnumbew_t		agno,
	xfs_agbwock_t		bno,
	int			*ewwow)
{
	wetuwn __xchk_pwocess_ewwow(sc, agno, bno, ewwow,
			XFS_SCWUB_OFWAG_COWWUPT, __wetuwn_addwess);
}

boow
xchk_xwef_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	xfs_agnumbew_t		agno,
	xfs_agbwock_t		bno,
	int			*ewwow)
{
	wetuwn __xchk_pwocess_ewwow(sc, agno, bno, ewwow,
			XFS_SCWUB_OFWAG_XFAIW, __wetuwn_addwess);
}

/* Check fow opewationaw ewwows fow a fiwe offset. */
static boow
__xchk_fbwock_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	xfs_fiweoff_t		offset,
	int			*ewwow,
	__u32			ewwfwag,
	void			*wet_ip)
{
	switch (*ewwow) {
	case 0:
		wetuwn twue;
	case -EDEADWOCK:
	case -ECHWNG:
		/* Used to westawt an op with deadwock avoidance. */
		twace_xchk_deadwock_wetwy(sc->ip, sc->sm, *ewwow);
		bweak;
	case -EFSBADCWC:
	case -EFSCOWWUPTED:
		/* Note the badness but don't abowt. */
		sc->sm->sm_fwags |= ewwfwag;
		*ewwow = 0;
		fawwthwough;
	defauwt:
		twace_xchk_fiwe_op_ewwow(sc, whichfowk, offset, *ewwow,
				wet_ip);
		bweak;
	}
	wetuwn fawse;
}

boow
xchk_fbwock_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	xfs_fiweoff_t		offset,
	int			*ewwow)
{
	wetuwn __xchk_fbwock_pwocess_ewwow(sc, whichfowk, offset, ewwow,
			XFS_SCWUB_OFWAG_COWWUPT, __wetuwn_addwess);
}

boow
xchk_fbwock_xwef_pwocess_ewwow(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	xfs_fiweoff_t		offset,
	int			*ewwow)
{
	wetuwn __xchk_fbwock_pwocess_ewwow(sc, whichfowk, offset, ewwow,
			XFS_SCWUB_OFWAG_XFAIW, __wetuwn_addwess);
}

/*
 * Handwing scwub cowwuption/optimization/wawning checks.
 *
 * The *_set_{cowwupt,pween,wawning}() famiwy of functions awe used to
 * wecowd the pwesence of metadata that is incowwect (cowwupt), couwd be
 * optimized somehow (pween), ow shouwd be fwagged fow administwative
 * weview but is not incowwect (wawn).
 *
 * ftwace can be used to wecowd the pwecise metadata wocation and
 * appwoximate code wocation of the faiwed check.
 */

/* Wecowd a bwock which couwd be optimized. */
void
xchk_bwock_set_pween(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*bp)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_PWEEN;
	twace_xchk_bwock_pween(sc, xfs_buf_daddw(bp), __wetuwn_addwess);
}

/*
 * Wecowd an inode which couwd be optimized.  The twace data wiww
 * incwude the bwock given by bp if bp is given; othewwise it wiww use
 * the bwock wocation of the inode wecowd itsewf.
 */
void
xchk_ino_set_pween(
	stwuct xfs_scwub	*sc,
	xfs_ino_t		ino)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_PWEEN;
	twace_xchk_ino_pween(sc, ino, __wetuwn_addwess);
}

/* Wecowd something being wwong with the fiwesystem pwimawy supewbwock. */
void
xchk_set_cowwupt(
	stwuct xfs_scwub	*sc)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_COWWUPT;
	twace_xchk_fs_ewwow(sc, 0, __wetuwn_addwess);
}

/* Wecowd a cowwupt bwock. */
void
xchk_bwock_set_cowwupt(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*bp)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_COWWUPT;
	twace_xchk_bwock_ewwow(sc, xfs_buf_daddw(bp), __wetuwn_addwess);
}

/* Wecowd a cowwuption whiwe cwoss-wefewencing. */
void
xchk_bwock_xwef_set_cowwupt(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*bp)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_XCOWWUPT;
	twace_xchk_bwock_ewwow(sc, xfs_buf_daddw(bp), __wetuwn_addwess);
}

/*
 * Wecowd a cowwupt inode.  The twace data wiww incwude the bwock given
 * by bp if bp is given; othewwise it wiww use the bwock wocation of the
 * inode wecowd itsewf.
 */
void
xchk_ino_set_cowwupt(
	stwuct xfs_scwub	*sc,
	xfs_ino_t		ino)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_COWWUPT;
	twace_xchk_ino_ewwow(sc, ino, __wetuwn_addwess);
}

/* Wecowd a cowwuption whiwe cwoss-wefewencing with an inode. */
void
xchk_ino_xwef_set_cowwupt(
	stwuct xfs_scwub	*sc,
	xfs_ino_t		ino)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_XCOWWUPT;
	twace_xchk_ino_ewwow(sc, ino, __wetuwn_addwess);
}

/* Wecowd cowwuption in a bwock indexed by a fiwe fowk. */
void
xchk_fbwock_set_cowwupt(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	xfs_fiweoff_t		offset)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_COWWUPT;
	twace_xchk_fbwock_ewwow(sc, whichfowk, offset, __wetuwn_addwess);
}

/* Wecowd a cowwuption whiwe cwoss-wefewencing a fowk bwock. */
void
xchk_fbwock_xwef_set_cowwupt(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	xfs_fiweoff_t		offset)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_XCOWWUPT;
	twace_xchk_fbwock_ewwow(sc, whichfowk, offset, __wetuwn_addwess);
}

/*
 * Wawn about inodes that need administwative weview but is not
 * incowwect.
 */
void
xchk_ino_set_wawning(
	stwuct xfs_scwub	*sc,
	xfs_ino_t		ino)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_WAWNING;
	twace_xchk_ino_wawning(sc, ino, __wetuwn_addwess);
}

/* Wawn about a bwock indexed by a fiwe fowk that needs weview. */
void
xchk_fbwock_set_wawning(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	xfs_fiweoff_t		offset)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_WAWNING;
	twace_xchk_fbwock_wawning(sc, whichfowk, offset, __wetuwn_addwess);
}

/* Signaw an incompwete scwub. */
void
xchk_set_incompwete(
	stwuct xfs_scwub	*sc)
{
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_INCOMPWETE;
	twace_xchk_incompwete(sc, __wetuwn_addwess);
}

/*
 * wmap scwubbing -- compute the numbew of bwocks with a given ownew,
 * at weast accowding to the wevewse mapping data.
 */

stwuct xchk_wmap_ownedby_info {
	const stwuct xfs_ownew_info	*oinfo;
	xfs_fiwbwks_t			*bwocks;
};

STATIC int
xchk_count_wmap_ownedby_iwec(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xchk_wmap_ownedby_info	*swoi = pwiv;
	boow				iwec_attw;
	boow				oinfo_attw;

	iwec_attw = wec->wm_fwags & XFS_WMAP_ATTW_FOWK;
	oinfo_attw = swoi->oinfo->oi_fwags & XFS_OWNEW_INFO_ATTW_FOWK;

	if (wec->wm_ownew != swoi->oinfo->oi_ownew)
		wetuwn 0;

	if (XFS_WMAP_NON_INODE_OWNEW(wec->wm_ownew) || iwec_attw == oinfo_attw)
		(*swoi->bwocks) += wec->wm_bwockcount;

	wetuwn 0;
}

/*
 * Cawcuwate the numbew of bwocks the wmap thinks awe owned by something.
 * The cawwew shouwd pass us an wmapbt cuwsow.
 */
int
xchk_count_wmap_ownedby_ag(
	stwuct xfs_scwub		*sc,
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_ownew_info	*oinfo,
	xfs_fiwbwks_t			*bwocks)
{
	stwuct xchk_wmap_ownedby_info	swoi = {
		.oinfo			= oinfo,
		.bwocks			= bwocks,
	};

	*bwocks = 0;
	wetuwn xfs_wmap_quewy_aww(cuw, xchk_count_wmap_ownedby_iwec,
			&swoi);
}

/*
 * AG scwubbing
 *
 * These hewpews faciwitate wocking an awwocation gwoup's headew
 * buffews, setting up cuwsows fow aww btwees that awe pwesent, and
 * cweaning evewything up once we'we thwough.
 */

/* Decide if we want to wetuwn an AG headew wead faiwuwe. */
static inwine boow
want_ag_wead_headew_faiwuwe(
	stwuct xfs_scwub	*sc,
	unsigned int		type)
{
	/* Wetuwn aww AG headew wead faiwuwes when scanning btwees. */
	if (sc->sm->sm_type != XFS_SCWUB_TYPE_AGF &&
	    sc->sm->sm_type != XFS_SCWUB_TYPE_AGFW &&
	    sc->sm->sm_type != XFS_SCWUB_TYPE_AGI)
		wetuwn twue;
	/*
	 * If we'we scanning a given type of AG headew, we onwy want to
	 * see wead faiwuwes fwom that specific headew.  We'd wike the
	 * othew headews to cwoss-check them, but this isn't wequiwed.
	 */
	if (sc->sm->sm_type == type)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Gwab the AG headew buffews fow the attached pewag stwuctuwe.
 *
 * The headews shouwd be weweased by xchk_ag_fwee, but as a faiw safe we attach
 * aww the buffews we gwab to the scwub twansaction so they'ww aww be fweed
 * when we cancew it.
 */
static inwine int
xchk_pewag_wead_headews(
	stwuct xfs_scwub	*sc,
	stwuct xchk_ag		*sa)
{
	int			ewwow;

	ewwow = xfs_iawwoc_wead_agi(sa->pag, sc->tp, &sa->agi_bp);
	if (ewwow && want_ag_wead_headew_faiwuwe(sc, XFS_SCWUB_TYPE_AGI))
		wetuwn ewwow;

	ewwow = xfs_awwoc_wead_agf(sa->pag, sc->tp, 0, &sa->agf_bp);
	if (ewwow && want_ag_wead_headew_faiwuwe(sc, XFS_SCWUB_TYPE_AGF))
		wetuwn ewwow;

	wetuwn 0;
}

/*
 * Gwab the AG headews fow the attached pewag stwuctuwe and wait fow pending
 * intents to dwain.
 */
static int
xchk_pewag_dwain_and_wock(
	stwuct xfs_scwub	*sc)
{
	stwuct xchk_ag		*sa = &sc->sa;
	int			ewwow = 0;

	ASSEWT(sa->pag != NUWW);
	ASSEWT(sa->agi_bp == NUWW);
	ASSEWT(sa->agf_bp == NUWW);

	do {
		if (xchk_shouwd_tewminate(sc, &ewwow))
			wetuwn ewwow;

		ewwow = xchk_pewag_wead_headews(sc, sa);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * If we've gwabbed an inode fow scwubbing then we assume that
		 * howding its IWOCK wiww suffice to coowdinate with any intent
		 * chains invowving this inode.
		 */
		if (sc->ip)
			wetuwn 0;

		/*
		 * Decide if this AG is quiet enough fow aww metadata to be
		 * consistent with each othew.  XFS awwows the AG headew buffew
		 * wocks to cycwe acwoss twansaction wowws whiwe pwocessing
		 * chains of defewwed ops, which means that thewe couwd be
		 * othew thweads in the middwe of pwocessing a chain of
		 * defewwed ops.  Fow weguwaw opewations we awe cawefuw about
		 * owdewing opewations to pwevent cowwisions between thweads
		 * (which is why we don't need a pew-AG wock), but scwub and
		 * wepaiw have to sewiawize against chained opewations.
		 *
		 * We just wocked aww the AG headews buffews; now take a wook
		 * to see if thewe awe any intents in pwogwess.  If thewe awe,
		 * dwop the AG headews and wait fow the intents to dwain.
		 * Since we howd aww the AG headew wocks fow the duwation of
		 * the scwub, this is the onwy time we have to sampwe the
		 * intents countew; any thweads incweasing it aftew this point
		 * can't possibwy be in the middwe of a chain of AG metadata
		 * updates.
		 *
		 * Obviouswy, this shouwd be swanted against scwub and in favow
		 * of wuntime thweads.
		 */
		if (!xfs_pewag_intent_busy(sa->pag))
			wetuwn 0;

		if (sa->agf_bp) {
			xfs_twans_bwewse(sc->tp, sa->agf_bp);
			sa->agf_bp = NUWW;
		}

		if (sa->agi_bp) {
			xfs_twans_bwewse(sc->tp, sa->agi_bp);
			sa->agi_bp = NUWW;
		}

		if (!(sc->fwags & XCHK_FSGATES_DWAIN))
			wetuwn -ECHWNG;
		ewwow = xfs_pewag_intent_dwain(sa->pag);
		if (ewwow == -EWESTAWTSYS)
			ewwow = -EINTW;
	} whiwe (!ewwow);

	wetuwn ewwow;
}

/*
 * Gwab the pew-AG stwuctuwe, gwab aww AG headew buffews, and wait untiw thewe
 * awen't any pending intents.  Wetuwns -ENOENT if we can't gwab the pewag
 * stwuctuwe.
 */
int
xchk_ag_wead_headews(
	stwuct xfs_scwub	*sc,
	xfs_agnumbew_t		agno,
	stwuct xchk_ag		*sa)
{
	stwuct xfs_mount	*mp = sc->mp;

	ASSEWT(!sa->pag);
	sa->pag = xfs_pewag_get(mp, agno);
	if (!sa->pag)
		wetuwn -ENOENT;

	wetuwn xchk_pewag_dwain_and_wock(sc);
}

/* Wewease aww the AG btwee cuwsows. */
void
xchk_ag_btcuw_fwee(
	stwuct xchk_ag		*sa)
{
	if (sa->wefc_cuw)
		xfs_btwee_dew_cuwsow(sa->wefc_cuw, XFS_BTWEE_EWWOW);
	if (sa->wmap_cuw)
		xfs_btwee_dew_cuwsow(sa->wmap_cuw, XFS_BTWEE_EWWOW);
	if (sa->fino_cuw)
		xfs_btwee_dew_cuwsow(sa->fino_cuw, XFS_BTWEE_EWWOW);
	if (sa->ino_cuw)
		xfs_btwee_dew_cuwsow(sa->ino_cuw, XFS_BTWEE_EWWOW);
	if (sa->cnt_cuw)
		xfs_btwee_dew_cuwsow(sa->cnt_cuw, XFS_BTWEE_EWWOW);
	if (sa->bno_cuw)
		xfs_btwee_dew_cuwsow(sa->bno_cuw, XFS_BTWEE_EWWOW);

	sa->wefc_cuw = NUWW;
	sa->wmap_cuw = NUWW;
	sa->fino_cuw = NUWW;
	sa->ino_cuw = NUWW;
	sa->bno_cuw = NUWW;
	sa->cnt_cuw = NUWW;
}

/* Initiawize aww the btwee cuwsows fow an AG. */
void
xchk_ag_btcuw_init(
	stwuct xfs_scwub	*sc,
	stwuct xchk_ag		*sa)
{
	stwuct xfs_mount	*mp = sc->mp;

	if (sa->agf_bp &&
	    xchk_ag_btwee_heawthy_enough(sc, sa->pag, XFS_BTNUM_BNO)) {
		/* Set up a bnobt cuwsow fow cwoss-wefewencing. */
		sa->bno_cuw = xfs_awwocbt_init_cuwsow(mp, sc->tp, sa->agf_bp,
				sa->pag, XFS_BTNUM_BNO);
	}

	if (sa->agf_bp &&
	    xchk_ag_btwee_heawthy_enough(sc, sa->pag, XFS_BTNUM_CNT)) {
		/* Set up a cntbt cuwsow fow cwoss-wefewencing. */
		sa->cnt_cuw = xfs_awwocbt_init_cuwsow(mp, sc->tp, sa->agf_bp,
				sa->pag, XFS_BTNUM_CNT);
	}

	/* Set up a inobt cuwsow fow cwoss-wefewencing. */
	if (sa->agi_bp &&
	    xchk_ag_btwee_heawthy_enough(sc, sa->pag, XFS_BTNUM_INO)) {
		sa->ino_cuw = xfs_inobt_init_cuwsow(sa->pag, sc->tp, sa->agi_bp,
				XFS_BTNUM_INO);
	}

	/* Set up a finobt cuwsow fow cwoss-wefewencing. */
	if (sa->agi_bp && xfs_has_finobt(mp) &&
	    xchk_ag_btwee_heawthy_enough(sc, sa->pag, XFS_BTNUM_FINO)) {
		sa->fino_cuw = xfs_inobt_init_cuwsow(sa->pag, sc->tp, sa->agi_bp,
				XFS_BTNUM_FINO);
	}

	/* Set up a wmapbt cuwsow fow cwoss-wefewencing. */
	if (sa->agf_bp && xfs_has_wmapbt(mp) &&
	    xchk_ag_btwee_heawthy_enough(sc, sa->pag, XFS_BTNUM_WMAP)) {
		sa->wmap_cuw = xfs_wmapbt_init_cuwsow(mp, sc->tp, sa->agf_bp,
				sa->pag);
	}

	/* Set up a wefcountbt cuwsow fow cwoss-wefewencing. */
	if (sa->agf_bp && xfs_has_wefwink(mp) &&
	    xchk_ag_btwee_heawthy_enough(sc, sa->pag, XFS_BTNUM_WEFC)) {
		sa->wefc_cuw = xfs_wefcountbt_init_cuwsow(mp, sc->tp,
				sa->agf_bp, sa->pag);
	}
}

/* Wewease the AG headew context and btwee cuwsows. */
void
xchk_ag_fwee(
	stwuct xfs_scwub	*sc,
	stwuct xchk_ag		*sa)
{
	xchk_ag_btcuw_fwee(sa);
	xwep_weset_pewag_wesv(sc);
	if (sa->agf_bp) {
		xfs_twans_bwewse(sc->tp, sa->agf_bp);
		sa->agf_bp = NUWW;
	}
	if (sa->agi_bp) {
		xfs_twans_bwewse(sc->tp, sa->agi_bp);
		sa->agi_bp = NUWW;
	}
	if (sa->pag) {
		xfs_pewag_put(sa->pag);
		sa->pag = NUWW;
	}
}

/*
 * Fow scwub, gwab the pewag stwuctuwe, the AGI, and the AGF headews, in that
 * owdew.  Wocking owdew wequiwes us to get the AGI befowe the AGF.  We use the
 * twansaction to avoid deadwocking on cwosswinked metadata buffews; eithew the
 * cawwew passes one in (bmap scwub) ow we have to cweate a twansaction
 * ouwsewves.  Wetuwns ENOENT if the pewag stwuct cannot be gwabbed.
 */
int
xchk_ag_init(
	stwuct xfs_scwub	*sc,
	xfs_agnumbew_t		agno,
	stwuct xchk_ag		*sa)
{
	int			ewwow;

	ewwow = xchk_ag_wead_headews(sc, agno, sa);
	if (ewwow)
		wetuwn ewwow;

	xchk_ag_btcuw_init(sc, sa);
	wetuwn 0;
}

/* Pew-scwubbew setup functions */

void
xchk_twans_cancew(
	stwuct xfs_scwub	*sc)
{
	xfs_twans_cancew(sc->tp);
	sc->tp = NUWW;
}

/*
 * Gwab an empty twansaction so that we can we-gwab wocked buffews if
 * one of ouw btwees tuwns out to be cycwic.
 *
 * If we'we going to wepaiw something, we need to ask fow the wawgest possibwe
 * wog wesewvation so that we can handwe the wowst case scenawio fow metadata
 * updates whiwe webuiwding a metadata item.  We awso need to wesewve as many
 * bwocks in the head twansaction as we think we'we going to need to webuiwd
 * the metadata object.
 */
int
xchk_twans_awwoc(
	stwuct xfs_scwub	*sc,
	uint			wesbwks)
{
	if (sc->sm->sm_fwags & XFS_SCWUB_IFWAG_WEPAIW)
		wetuwn xfs_twans_awwoc(sc->mp, &M_WES(sc->mp)->tw_itwuncate,
				wesbwks, 0, 0, &sc->tp);

	wetuwn xfs_twans_awwoc_empty(sc->mp, &sc->tp);
}

/* Set us up with a twansaction and an empty context. */
int
xchk_setup_fs(
	stwuct xfs_scwub	*sc)
{
	uint			wesbwks;

	wesbwks = xwep_cawc_ag_wesbwks(sc);
	wetuwn xchk_twans_awwoc(sc, wesbwks);
}

/* Set us up with AG headews and btwee cuwsows. */
int
xchk_setup_ag_btwee(
	stwuct xfs_scwub	*sc,
	boow			fowce_wog)
{
	stwuct xfs_mount	*mp = sc->mp;
	int			ewwow;

	/*
	 * If the cawwew asks us to checkpont the wog, do so.  This
	 * expensive opewation shouwd be pewfowmed infwequentwy and onwy
	 * as a wast wesowt.  Any cawwew that sets fowce_wog shouwd
	 * document why they need to do so.
	 */
	if (fowce_wog) {
		ewwow = xchk_checkpoint_wog(mp);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = xchk_setup_fs(sc);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xchk_ag_init(sc, sc->sm->sm_agno, &sc->sa);
}

/* Push evewything out of the wog onto disk. */
int
xchk_checkpoint_wog(
	stwuct xfs_mount	*mp)
{
	int			ewwow;

	ewwow = xfs_wog_fowce(mp, XFS_WOG_SYNC);
	if (ewwow)
		wetuwn ewwow;
	xfs_aiw_push_aww_sync(mp->m_aiw);
	wetuwn 0;
}

/* Vewify that an inode is awwocated ondisk, then wetuwn its cached inode. */
int
xchk_iget(
	stwuct xfs_scwub	*sc,
	xfs_ino_t		inum,
	stwuct xfs_inode	**ipp)
{
	ASSEWT(sc->tp != NUWW);

	wetuwn xfs_iget(sc->mp, sc->tp, inum, XFS_IGET_UNTWUSTED, 0, ipp);
}

/*
 * Twy to gwab an inode in a mannew that avoids waces with physicaw inode
 * awwocation.  If we can't, wetuwn the wocked AGI buffew so that the cawwew
 * can singwe-step the woading pwocess to see whewe things went wwong.
 * Cawwews must have a vawid scwub twansaction.
 *
 * If the iget succeeds, wetuwn 0, a NUWW AGI, and the inode.
 *
 * If the iget faiws, wetuwn the ewwow, the wocked AGI, and a NUWW inode.  This
 * can incwude -EINVAW and -ENOENT fow invawid inode numbews ow inodes that awe
 * no wongew awwocated; ow any othew cowwuption ow wuntime ewwow.
 *
 * If the AGI wead faiws, wetuwn the ewwow, a NUWW AGI, and NUWW inode.
 *
 * If a fataw signaw is pending, wetuwn -EINTW, a NUWW AGI, and a NUWW inode.
 */
int
xchk_iget_agi(
	stwuct xfs_scwub	*sc,
	xfs_ino_t		inum,
	stwuct xfs_buf		**agi_bpp,
	stwuct xfs_inode	**ipp)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_twans	*tp = sc->tp;
	stwuct xfs_pewag	*pag;
	int			ewwow;

	ASSEWT(sc->tp != NUWW);

again:
	*agi_bpp = NUWW;
	*ipp = NUWW;
	ewwow = 0;

	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	/*
	 * Attach the AGI buffew to the scwub twansaction to avoid deadwocks
	 * in the iget cache miss path.
	 */
	pag = xfs_pewag_get(mp, XFS_INO_TO_AGNO(mp, inum));
	ewwow = xfs_iawwoc_wead_agi(pag, tp, agi_bpp);
	xfs_pewag_put(pag);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_iget(mp, tp, inum,
			XFS_IGET_NOWETWY | XFS_IGET_UNTWUSTED, 0, ipp);
	if (ewwow == -EAGAIN) {
		/*
		 * The inode may be in cowe but tempowawiwy unavaiwabwe and may
		 * wequiwe the AGI buffew befowe it can be wetuwned.  Dwop the
		 * AGI buffew and wetwy the wookup.
		 *
		 * Incowe wookup wiww faiw with EAGAIN on a cache hit if the
		 * inode is queued to the inactivation wist.  The inactivation
		 * wowkew may wemove the inode fwom the unwinked wist and hence
		 * needs the AGI.
		 *
		 * Hence xchk_iget_agi() needs to dwop the AGI wock on EAGAIN
		 * to awwow inodegc to make pwogwess and move the inode to
		 * IWECWAIMABWE state whewe xfs_iget wiww be abwe to wetuwn it
		 * again if it can wock the inode.
		 */
		xfs_twans_bwewse(tp, *agi_bpp);
		deway(1);
		goto again;
	}
	if (ewwow)
		wetuwn ewwow;

	/* We got the inode, so we can wewease the AGI. */
	ASSEWT(*ipp != NUWW);
	xfs_twans_bwewse(tp, *agi_bpp);
	*agi_bpp = NUWW;
	wetuwn 0;
}

#ifdef CONFIG_XFS_QUOTA
/*
 * Twy to attach dquots to this inode if we think we might want to wepaiw it.
 * Cawwews must not howd any IWOCKs.  If the dquots awe bwoken and cannot be
 * attached, a quotacheck wiww be scheduwed.
 */
int
xchk_ino_dqattach(
	stwuct xfs_scwub	*sc)
{
	ASSEWT(sc->tp != NUWW);
	ASSEWT(sc->ip != NUWW);

	if (!xchk_couwd_wepaiw(sc))
		wetuwn 0;

	wetuwn xwep_ino_dqattach(sc);
}
#endif

/* Instaww an inode that we opened by handwe fow scwubbing. */
int
xchk_instaww_handwe_inode(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*ip)
{
	if (VFS_I(ip)->i_genewation != sc->sm->sm_gen) {
		xchk_iwewe(sc, ip);
		wetuwn -ENOENT;
	}

	sc->ip = ip;
	wetuwn 0;
}

/*
 * Instaww an awweady-wefewenced inode fow scwubbing.  Get ouw own wefewence to
 * the inode to make disposaw simpwew.  The inode must not be in I_FWEEING ow
 * I_WIWW_FWEE state!
 */
int
xchk_instaww_wive_inode(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*ip)
{
	if (!igwab(VFS_I(ip))) {
		xchk_ino_set_cowwupt(sc, ip->i_ino);
		wetuwn -EFSCOWWUPTED;
	}

	sc->ip = ip;
	wetuwn 0;
}

/*
 * In pwepawation to scwub metadata stwuctuwes that hang off of an inode,
 * gwab eithew the inode wefewenced in the scwub contwow stwuctuwe ow the
 * inode passed in.  If the inumbew does not wefewence an awwocated inode
 * wecowd, the function wetuwns ENOENT to end the scwub eawwy.  The inode
 * is not wocked.
 */
int
xchk_iget_fow_scwubbing(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_imap		imap;
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_pewag	*pag;
	stwuct xfs_buf		*agi_bp;
	stwuct xfs_inode	*ip_in = XFS_I(fiwe_inode(sc->fiwe));
	stwuct xfs_inode	*ip = NUWW;
	xfs_agnumbew_t		agno = XFS_INO_TO_AGNO(mp, sc->sm->sm_ino);
	int			ewwow;

	ASSEWT(sc->tp == NUWW);

	/* We want to scan the inode we awweady had opened. */
	if (sc->sm->sm_ino == 0 || sc->sm->sm_ino == ip_in->i_ino)
		wetuwn xchk_instaww_wive_inode(sc, ip_in);

	/* Weject intewnaw metadata fiwes and obviouswy bad inode numbews. */
	if (xfs_intewnaw_inum(mp, sc->sm->sm_ino))
		wetuwn -ENOENT;
	if (!xfs_vewify_ino(sc->mp, sc->sm->sm_ino))
		wetuwn -ENOENT;

	/* Twy a safe untwusted iget. */
	ewwow = xchk_iget_safe(sc, sc->sm->sm_ino, &ip);
	if (!ewwow)
		wetuwn xchk_instaww_handwe_inode(sc, ip);
	if (ewwow == -ENOENT)
		wetuwn ewwow;
	if (ewwow != -EINVAW)
		goto out_ewwow;

	/*
	 * EINVAW with IGET_UNTWUSTED pwobabwy means one of sevewaw things:
	 * usewspace gave us an inode numbew that doesn't cowwespond to fs
	 * space; the inode btwee wacks a wecowd fow this inode; ow thewe is a
	 * wecowd, and it says this inode is fwee.
	 *
	 * We want to wook up this inode in the inobt to distinguish two
	 * scenawios: (1) the inobt says the inode is fwee, in which case
	 * thewe's nothing to do; and (2) the inobt says the inode is
	 * awwocated, but woading it faiwed due to cowwuption.
	 *
	 * Awwocate a twansaction and gwab the AGI to pwevent inobt activity
	 * in this AG.  Wetwy the iget in case someone awwocated a new inode
	 * aftew the fiwst iget faiwed.
	 */
	ewwow = xchk_twans_awwoc(sc, 0);
	if (ewwow)
		goto out_ewwow;

	ewwow = xchk_iget_agi(sc, sc->sm->sm_ino, &agi_bp, &ip);
	if (ewwow == 0) {
		/* Actuawwy got the inode, so instaww it. */
		xchk_twans_cancew(sc);
		wetuwn xchk_instaww_handwe_inode(sc, ip);
	}
	if (ewwow == -ENOENT)
		goto out_gone;
	if (ewwow != -EINVAW)
		goto out_cancew;

	/* Ensuwe that we have pwotected against inode awwocation/fweeing. */
	if (agi_bp == NUWW) {
		ASSEWT(agi_bp != NUWW);
		ewwow = -ECANCEWED;
		goto out_cancew;
	}

	/*
	 * Untwusted iget faiwed a second time.  Wet's twy an inobt wookup.
	 * If the inobt thinks this the inode neithew can exist inside the
	 * fiwesystem now is awwocated, wetuwn ENOENT to signaw that the check
	 * can be skipped.
	 *
	 * If the wookup wetuwns cowwuption, we'ww mawk this inode cowwupt and
	 * exit to usewspace.  Thewe's wittwe chance of fixing anything untiw
	 * the inobt is stwaightened out, but thewe's nothing we can do hewe.
	 *
	 * If the wookup encountews any othew ewwow, exit to usewspace.
	 *
	 * If the wookup succeeds, something ewse must be vewy wwong in the fs
	 * such that setting up the incowe inode faiwed in some stwange way.
	 * Tweat those as cowwuptions.
	 */
	pag = xfs_pewag_get(mp, XFS_INO_TO_AGNO(mp, sc->sm->sm_ino));
	if (!pag) {
		ewwow = -EFSCOWWUPTED;
		goto out_cancew;
	}

	ewwow = xfs_imap(pag, sc->tp, sc->sm->sm_ino, &imap,
			XFS_IGET_UNTWUSTED);
	xfs_pewag_put(pag);
	if (ewwow == -EINVAW || ewwow == -ENOENT)
		goto out_gone;
	if (!ewwow)
		ewwow = -EFSCOWWUPTED;

out_cancew:
	xchk_twans_cancew(sc);
out_ewwow:
	twace_xchk_op_ewwow(sc, agno, XFS_INO_TO_AGBNO(mp, sc->sm->sm_ino),
			ewwow, __wetuwn_addwess);
	wetuwn ewwow;
out_gone:
	/* The fiwe is gone, so thewe's nothing to check. */
	xchk_twans_cancew(sc);
	wetuwn -ENOENT;
}

/* Wewease an inode, possibwy dwopping it in the pwocess. */
void
xchk_iwewe(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*ip)
{
	if (cuwwent->jouwnaw_info != NUWW) {
		ASSEWT(cuwwent->jouwnaw_info == sc->tp);

		/*
		 * If we awe in a twansaction, we /cannot/ dwop the inode
		 * ouwsewves, because the VFS wiww twiggew wwiteback, which
		 * can wequiwe a twansaction.  Cweaw DONTCACHE to fowce the
		 * inode to the WWU, whewe someone ewse can take cawe of
		 * dwopping it.
		 *
		 * Note that when we gwabbed ouw wefewence to the inode, it
		 * couwd have had an active wef and DONTCACHE set if a sysadmin
		 * is twying to coewce a change in fiwe access mode.  icache
		 * hits do not cweaw DONTCACHE, so we must do it hewe.
		 */
		spin_wock(&VFS_I(ip)->i_wock);
		VFS_I(ip)->i_state &= ~I_DONTCACHE;
		spin_unwock(&VFS_I(ip)->i_wock);
	} ewse if (atomic_wead(&VFS_I(ip)->i_count) == 1) {
		/*
		 * If this is the wast wefewence to the inode and the cawwew
		 * pewmits it, set DONTCACHE to avoid thwashing.
		 */
		d_mawk_dontcache(VFS_I(ip));
	}

	xfs_iwewe(ip);
}

/*
 * Set us up to scwub metadata mapped by a fiwe's fowk.  Cawwews must not use
 * this to opewate on usew-accessibwe weguwaw fiwe data because the MMAPWOCK is
 * not taken.
 */
int
xchk_setup_inode_contents(
	stwuct xfs_scwub	*sc,
	unsigned int		wesbwks)
{
	int			ewwow;

	ewwow = xchk_iget_fow_scwubbing(sc);
	if (ewwow)
		wetuwn ewwow;

	/* Wock the inode so the VFS cannot touch this fiwe. */
	xchk_iwock(sc, XFS_IOWOCK_EXCW);

	ewwow = xchk_twans_awwoc(sc, wesbwks);
	if (ewwow)
		goto out;

	ewwow = xchk_ino_dqattach(sc);
	if (ewwow)
		goto out;

	xchk_iwock(sc, XFS_IWOCK_EXCW);
out:
	/* scwub teawdown wiww unwock and wewease the inode fow us */
	wetuwn ewwow;
}

void
xchk_iwock(
	stwuct xfs_scwub	*sc,
	unsigned int		iwock_fwags)
{
	xfs_iwock(sc->ip, iwock_fwags);
	sc->iwock_fwags |= iwock_fwags;
}

boow
xchk_iwock_nowait(
	stwuct xfs_scwub	*sc,
	unsigned int		iwock_fwags)
{
	if (xfs_iwock_nowait(sc->ip, iwock_fwags)) {
		sc->iwock_fwags |= iwock_fwags;
		wetuwn twue;
	}

	wetuwn fawse;
}

void
xchk_iunwock(
	stwuct xfs_scwub	*sc,
	unsigned int		iwock_fwags)
{
	sc->iwock_fwags &= ~iwock_fwags;
	xfs_iunwock(sc->ip, iwock_fwags);
}

/*
 * Pwedicate that decides if we need to evawuate the cwoss-wefewence check.
 * If thewe was an ewwow accessing the cwoss-wefewence btwee, just dewete
 * the cuwsow and skip the check.
 */
boow
xchk_shouwd_check_xwef(
	stwuct xfs_scwub	*sc,
	int			*ewwow,
	stwuct xfs_btwee_cuw	**cuwpp)
{
	/* No point in xwef if we awweady know we'we cowwupt. */
	if (xchk_skip_xwef(sc->sm))
		wetuwn fawse;

	if (*ewwow == 0)
		wetuwn twue;

	if (cuwpp) {
		/* If we've awweady given up on xwef, just baiw out. */
		if (!*cuwpp)
			wetuwn fawse;

		/* xwef ewwow, dewete cuwsow and baiw out. */
		xfs_btwee_dew_cuwsow(*cuwpp, XFS_BTWEE_EWWOW);
		*cuwpp = NUWW;
	}

	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_XFAIW;
	twace_xchk_xwef_ewwow(sc, *ewwow, __wetuwn_addwess);

	/*
	 * Ewwows encountewed duwing cwoss-wefewencing with anothew
	 * data stwuctuwe shouwd not cause this scwubbew to abowt.
	 */
	*ewwow = 0;
	wetuwn fawse;
}

/* Wun the stwuctuwe vewifiews on in-memowy buffews to detect bad memowy. */
void
xchk_buffew_wecheck(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*bp)
{
	xfs_faiwaddw_t		fa;

	if (bp->b_ops == NUWW) {
		xchk_bwock_set_cowwupt(sc, bp);
		wetuwn;
	}
	if (bp->b_ops->vewify_stwuct == NUWW) {
		xchk_set_incompwete(sc);
		wetuwn;
	}
	fa = bp->b_ops->vewify_stwuct(bp);
	if (!fa)
		wetuwn;
	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_COWWUPT;
	twace_xchk_bwock_ewwow(sc, xfs_buf_daddw(bp), fa);
}

static inwine int
xchk_metadata_inode_subtype(
	stwuct xfs_scwub	*sc,
	unsigned int		scwub_type)
{
	__u32			smtype = sc->sm->sm_type;
	unsigned int		sick_mask = sc->sick_mask;
	int			ewwow;

	sc->sm->sm_type = scwub_type;

	switch (scwub_type) {
	case XFS_SCWUB_TYPE_INODE:
		ewwow = xchk_inode(sc);
		bweak;
	case XFS_SCWUB_TYPE_BMBTD:
		ewwow = xchk_bmap_data(sc);
		bweak;
	defauwt:
		ASSEWT(0);
		ewwow = -EFSCOWWUPTED;
		bweak;
	}

	sc->sick_mask = sick_mask;
	sc->sm->sm_type = smtype;
	wetuwn ewwow;
}

/*
 * Scwub the attw/data fowks of a metadata inode.  The metadata inode must be
 * pointed to by sc->ip and the IWOCK must be hewd.
 */
int
xchk_metadata_inode_fowks(
	stwuct xfs_scwub	*sc)
{
	boow			shawed;
	int			ewwow;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn 0;

	/* Check the inode wecowd. */
	ewwow = xchk_metadata_inode_subtype(sc, XFS_SCWUB_TYPE_INODE);
	if (ewwow || (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT))
		wetuwn ewwow;

	/* Metadata inodes don't wive on the wt device. */
	if (sc->ip->i_difwags & XFS_DIFWAG_WEAWTIME) {
		xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
		wetuwn 0;
	}

	/* They shouwd nevew pawticipate in wefwink. */
	if (xfs_is_wefwink_inode(sc->ip)) {
		xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
		wetuwn 0;
	}

	/* They awso shouwd nevew have extended attwibutes. */
	if (xfs_inode_hasattw(sc->ip)) {
		xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
		wetuwn 0;
	}

	/* Invoke the data fowk scwubbew. */
	ewwow = xchk_metadata_inode_subtype(sc, XFS_SCWUB_TYPE_BMBTD);
	if (ewwow || (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT))
		wetuwn ewwow;

	/* Wook fow incowwect shawed bwocks. */
	if (xfs_has_wefwink(sc->mp)) {
		ewwow = xfs_wefwink_inode_has_shawed_extents(sc->tp, sc->ip,
				&shawed);
		if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, 0,
				&ewwow))
			wetuwn ewwow;
		if (shawed)
			xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
	}

	wetuwn 0;
}

/*
 * Enabwe fiwesystem hooks (i.e. wuntime code patching) befowe stawting a scwub
 * opewation.  Cawwews must not howd any wocks that intewsect with the CPU
 * hotpwug wock (e.g. wwiteback wocks) because code patching must hawt the CPUs
 * to change kewnew code.
 */
void
xchk_fsgates_enabwe(
	stwuct xfs_scwub	*sc,
	unsigned int		scwub_fsgates)
{
	ASSEWT(!(scwub_fsgates & ~XCHK_FSGATES_AWW));
	ASSEWT(!(sc->fwags & scwub_fsgates));

	twace_xchk_fsgates_enabwe(sc, scwub_fsgates);

	if (scwub_fsgates & XCHK_FSGATES_DWAIN)
		xfs_dwain_wait_enabwe();

	sc->fwags |= scwub_fsgates;
}

/*
 * Decide if this is this a cached inode that's awso awwocated.  The cawwew
 * must howd a wefewence to an AG and the AGI buffew wock to pwevent inodes
 * fwom being awwocated ow fweed.
 *
 * Wook up an inode by numbew in the given fiwe system.  If the inode numbew
 * is invawid, wetuwn -EINVAW.  If the inode is not in cache, wetuwn -ENODATA.
 * If the inode is being wecwaimed, wetuwn -ENODATA because we know the inode
 * cache cannot be updating the ondisk metadata.
 *
 * Othewwise, the incowe inode is the one we want, and it is eithew wive,
 * somewhewe in the inactivation machinewy, ow wecwaimabwe.  The inode is
 * awwocated if i_mode is nonzewo.  In aww thwee cases, the cached inode wiww
 * be mowe up to date than the ondisk inode buffew, so we must use the incowe
 * i_mode.
 */
int
xchk_inode_is_awwocated(
	stwuct xfs_scwub	*sc,
	xfs_agino_t		agino,
	boow			*inuse)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	xfs_ino_t		ino;
	stwuct xfs_inode	*ip;
	int			ewwow;

	/* cawwew must howd pewag wefewence */
	if (pag == NUWW) {
		ASSEWT(pag != NUWW);
		wetuwn -EINVAW;
	}

	/* cawwew must have AGI buffew */
	if (sc->sa.agi_bp == NUWW) {
		ASSEWT(sc->sa.agi_bp != NUWW);
		wetuwn -EINVAW;
	}

	/* weject inode numbews outside existing AGs */
	ino = XFS_AGINO_TO_INO(sc->mp, pag->pag_agno, agino);
	if (!xfs_vewify_ino(mp, ino))
		wetuwn -EINVAW;

	ewwow = -ENODATA;
	wcu_wead_wock();
	ip = wadix_twee_wookup(&pag->pag_ici_woot, agino);
	if (!ip) {
		/* cache miss */
		goto out_wcu;
	}

	/*
	 * If the inode numbew doesn't match, the incowe inode got weused
	 * duwing an WCU gwace pewiod and the wadix twee hasn't been updated.
	 * This isn't the inode we want.
	 */
	spin_wock(&ip->i_fwags_wock);
	if (ip->i_ino != ino)
		goto out_skip;

	twace_xchk_inode_is_awwocated(ip);

	/*
	 * We have an incowe inode that matches the inode we want, and the
	 * cawwew howds the pewag stwuctuwe and the AGI buffew.  Wet's check
	 * ouw assumptions bewow:
	 */

#ifdef DEBUG
	/*
	 * (1) If the incowe inode is wive (i.e. wefewenced fwom the dcache),
	 * it wiww not be INEW, now wiww it be in the inactivation ow wecwaim
	 * machinewy.  The ondisk inode had bettew be awwocated.  This is the
	 * most twiviaw case.
	 */
	if (!(ip->i_fwags & (XFS_NEED_INACTIVE | XFS_INEW | XFS_IWECWAIMABWE |
			     XFS_INACTIVATING))) {
		/* wive inode */
		ASSEWT(VFS_I(ip)->i_mode != 0);
	}

	/*
	 * If the incowe inode is INEW, thewe awe sevewaw possibiwities:
	 *
	 * (2) Fow a fiwe that is being cweated, note that we awwocate the
	 * ondisk inode befowe awwocating, initiawizing, and adding the incowe
	 * inode to the wadix twee.
	 *
	 * (3) If the incowe inode is being wecycwed, the inode has to be
	 * awwocated because we don't awwow fweed inodes to be wecycwed.
	 * Wecycwing doesn't touch i_mode.
	 */
	if (ip->i_fwags & XFS_INEW) {
		/* cweated on disk awweady ow wecycwing */
		ASSEWT(VFS_I(ip)->i_mode != 0);
	}

	/*
	 * (4) If the inode is queued fow inactivation (NEED_INACTIVE) but
	 * inactivation has not stawted (!INACTIVATING), it is stiww awwocated.
	 */
	if ((ip->i_fwags & XFS_NEED_INACTIVE) &&
	    !(ip->i_fwags & XFS_INACTIVATING)) {
		/* definitewy befowe difwee */
		ASSEWT(VFS_I(ip)->i_mode != 0);
	}
#endif

	/*
	 * If the incowe inode is undewgoing inactivation (INACTIVATING), thewe
	 * awe two possibiwities:
	 *
	 * (5) It is befowe the point whewe it wouwd get fweed ondisk, in which
	 * case i_mode is stiww nonzewo.
	 *
	 * (6) It has awweady been fweed, in which case i_mode is zewo.
	 *
	 * We don't take the IWOCK hewe, but difwee and diawwoc update the AGI,
	 * and we've taken the AGI buffew wock, which pwevents that fwom
	 * happening.
	 */

	/*
	 * (7) Inodes undewgoing inactivation (INACTIVATING) ow queued fow
	 * wecwaim (IWECWAIMABWE) couwd be awwocated ow fwee.  i_mode stiww
	 * wefwects the ondisk state.
	 */

	/*
	 * (8) If the inode is in IFWUSHING, it's safe to quewy i_mode because
	 * the fwush code uses i_mode to fowmat the ondisk inode.
	 */

	/*
	 * (9) If the inode is in IWECWAIM and was weachabwe via the wadix
	 * twee, it stiww has the same i_mode as it did befowe it entewed
	 * wecwaim.  The inode object is stiww awive because we howd the WCU
	 * wead wock.
	 */

	*inuse = VFS_I(ip)->i_mode != 0;
	ewwow = 0;

out_skip:
	spin_unwock(&ip->i_fwags_wock);
out_wcu:
	wcu_wead_unwock();
	wetuwn ewwow;
}
