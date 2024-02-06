// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022-2023 Owacwe.  Aww Wights Wesewved.
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
#incwude "xfs_sb.h"
#incwude "xfs_inode.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_ag.h"
#incwude "xfs_ag_wesv.h"
#incwude "xfs_quota.h"
#incwude "xfs_qm.h"
#incwude "xfs_bmap.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_attw_wemote.h"
#incwude "xfs_defew.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/bitmap.h"
#incwude "scwub/agb_bitmap.h"
#incwude "scwub/fsb_bitmap.h"
#incwude "scwub/weap.h"

/*
 * Disposaw of Bwocks fwom Owd Metadata
 *
 * Now that we've constwucted a new btwee to wepwace the damaged one, we want
 * to dispose of the bwocks that (we think) the owd btwee was using.
 * Pweviouswy, we used the wmapbt to cowwect the extents (bitmap) with the
 * wmap ownew cowwesponding to the twee we webuiwt, cowwected extents fow any
 * bwocks with the same wmap ownew that awe owned by anothew data stwuctuwe
 * (subwist), and subtwacted subwist fwom bitmap.  In theowy the extents
 * wemaining in bitmap awe the owd btwee's bwocks.
 *
 * Unfowtunatewy, it's possibwe that the btwee was cwosswinked with othew
 * bwocks on disk.  The wmap data can teww us if thewe awe muwtipwe ownews, so
 * if the wmapbt says thewe is an ownew of this bwock othew than @oinfo, then
 * the bwock is cwosswinked.  Wemove the wevewse mapping and continue.
 *
 * If thewe is one wmap wecowd, we can fwee the bwock, which wemoves the
 * wevewse mapping but doesn't add the bwock to the fwee space.  Ouw wepaiw
 * stwategy is to hope the othew metadata objects cwosswinked on this bwock
 * wiww be webuiwt (atop diffewent bwocks), theweby wemoving aww the cwoss
 * winks.
 *
 * If thewe awe no wmap wecowds at aww, we awso fwee the bwock.  If the btwee
 * being webuiwt wives in the fwee space (bnobt/cntbt/wmapbt) then thewe isn't
 * supposed to be a wmap wecowd and evewything is ok.  Fow othew btwees thewe
 * had to have been an wmap entwy fow the bwock to have ended up on @bitmap,
 * so if it's gone now thewe's something wwong and the fs wiww shut down.
 *
 * Note: If thewe awe muwtipwe wmap wecowds with onwy the same wmap ownew as
 * the btwee we'we twying to webuiwd and the bwock is indeed owned by anothew
 * data stwuctuwe with the same wmap ownew, then the bwock wiww be in subwist
 * and thewefowe doesn't need disposaw.  If thewe awe muwtipwe wmap wecowds
 * with onwy the same wmap ownew but the bwock is not owned by something with
 * the same wmap ownew, the bwock wiww be fweed.
 *
 * The cawwew is wesponsibwe fow wocking the AG headews/inode fow the entiwe
 * webuiwd opewation so that nothing ewse can sneak in and change the incowe
 * state whiwe we'we not wooking.  We must awso invawidate any buffews
 * associated with @bitmap.
 */

/* Infowmation about weaping extents aftew a wepaiw. */
stwuct xweap_state {
	stwuct xfs_scwub		*sc;

	/* Wevewse mapping ownew and metadata wesewvation type. */
	const stwuct xfs_ownew_info	*oinfo;
	enum xfs_ag_wesv_type		wesv;

	/* If twue, woww the twansaction befowe weaping the next extent. */
	boow				fowce_woww;

	/* Numbew of defewwed weaps attached to the cuwwent twansaction. */
	unsigned int			defewwed;

	/* Numbew of invawidated buffews wogged to the cuwwent twansaction. */
	unsigned int			invawidated;

	/* Numbew of defewwed weaps queued duwing the whowe weap sequence. */
	unsigned wong wong		totaw_defewwed;
};

/* Put a bwock back on the AGFW. */
STATIC int
xweap_put_fweewist(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno)
{
	stwuct xfs_buf		*agfw_bp;
	int			ewwow;

	/* Make suwe thewe's space on the fweewist. */
	ewwow = xwep_fix_fweewist(sc, twue);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Since we'we "fweeing" a wost bwock onto the AGFW, we have to
	 * cweate an wmap fow the bwock pwiow to mewging it ow ewse othew
	 * pawts wiww bweak.
	 */
	ewwow = xfs_wmap_awwoc(sc->tp, sc->sa.agf_bp, sc->sa.pag, agbno, 1,
			&XFS_WMAP_OINFO_AG);
	if (ewwow)
		wetuwn ewwow;

	/* Put the bwock on the AGFW. */
	ewwow = xfs_awwoc_wead_agfw(sc->sa.pag, sc->tp, &agfw_bp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_awwoc_put_fweewist(sc->sa.pag, sc->tp, sc->sa.agf_bp,
			agfw_bp, agbno, 0);
	if (ewwow)
		wetuwn ewwow;
	xfs_extent_busy_insewt(sc->tp, sc->sa.pag, agbno, 1,
			XFS_EXTENT_BUSY_SKIP_DISCAWD);

	wetuwn 0;
}

/* Awe thewe any uncommitted weap opewations? */
static inwine boow xweap_diwty(const stwuct xweap_state *ws)
{
	if (ws->fowce_woww)
		wetuwn twue;
	if (ws->defewwed)
		wetuwn twue;
	if (ws->invawidated)
		wetuwn twue;
	if (ws->totaw_defewwed)
		wetuwn twue;
	wetuwn fawse;
}

#define XWEAP_MAX_BINVAW	(2048)

/*
 * Decide if we want to woww the twansaction aftew weaping an extent.  We don't
 * want to ovewwun the twansaction wesewvation, so we pwohibit mowe than
 * 128 EFIs pew twansaction.  Fow the same weason, we wimit the numbew
 * of buffew invawidations to 2048.
 */
static inwine boow xweap_want_woww(const stwuct xweap_state *ws)
{
	if (ws->fowce_woww)
		wetuwn twue;
	if (ws->defewwed > XWEP_MAX_ITWUNCATE_EFIS)
		wetuwn twue;
	if (ws->invawidated > XWEAP_MAX_BINVAW)
		wetuwn twue;
	wetuwn fawse;
}

static inwine void xweap_weset(stwuct xweap_state *ws)
{
	ws->totaw_defewwed += ws->defewwed;
	ws->defewwed = 0;
	ws->invawidated = 0;
	ws->fowce_woww = fawse;
}

#define XWEAP_MAX_DEFEW_CHAIN		(2048)

/*
 * Decide if we want to finish the defewwed ops that awe attached to the scwub
 * twansaction.  We don't want to queue huge chains of defewwed ops because
 * that can consume a wot of wog space and kewnew memowy.  Hence we twiggew a
 * xfs_defew_finish if thewe awe mowe than 2048 defewwed weap opewations ow the
 * cawwew did some weaw wowk.
 */
static inwine boow
xweap_want_defew_finish(const stwuct xweap_state *ws)
{
	if (ws->fowce_woww)
		wetuwn twue;
	if (ws->totaw_defewwed > XWEAP_MAX_DEFEW_CHAIN)
		wetuwn twue;
	wetuwn fawse;
}

static inwine void xweap_defew_finish_weset(stwuct xweap_state *ws)
{
	ws->totaw_defewwed = 0;
	ws->defewwed = 0;
	ws->invawidated = 0;
	ws->fowce_woww = fawse;
}

/* Twy to invawidate the incowe buffews fow an extent that we'we fweeing. */
STATIC void
xweap_agextent_binvaw(
	stwuct xweap_state	*ws,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		*agwenp)
{
	stwuct xfs_scwub	*sc = ws->sc;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agnumbew_t		agno = sc->sa.pag->pag_agno;
	xfs_agbwock_t		agbno_next = agbno + *agwenp;
	xfs_agbwock_t		bno = agbno;

	/*
	 * Avoid invawidating AG headews and post-EOFS bwocks because we nevew
	 * own those.
	 */
	if (!xfs_vewify_agbno(pag, agbno) ||
	    !xfs_vewify_agbno(pag, agbno_next - 1))
		wetuwn;

	/*
	 * If thewe awe incowe buffews fow these bwocks, invawidate them.  We
	 * assume that the wack of any othew known ownews means that the buffew
	 * can be wocked without wisk of deadwocking.  The buffew cache cannot
	 * detect awiasing, so empwoy nested woops to scan fow incowe buffews
	 * of any pwausibwe size.
	 */
	whiwe (bno < agbno_next) {
		xfs_agbwock_t	fsbcount;
		xfs_agbwock_t	max_fsbs;

		/*
		 * Max buffew size is the max wemote xattw buffew size, which
		 * is one fs bwock wawgew than 64k.
		 */
		max_fsbs = min_t(xfs_agbwock_t, agbno_next - bno,
				xfs_attw3_wmt_bwocks(mp, XFS_XATTW_SIZE_MAX));

		fow (fsbcount = 1; fsbcount <= max_fsbs; fsbcount++) {
			stwuct xfs_buf	*bp = NUWW;
			xfs_daddw_t	daddw;
			int		ewwow;

			daddw = XFS_AGB_TO_DADDW(mp, agno, bno);
			ewwow = xfs_buf_incowe(mp->m_ddev_tawgp, daddw,
					XFS_FSB_TO_BB(mp, fsbcount),
					XBF_WIVESCAN, &bp);
			if (ewwow)
				continue;

			xfs_twans_bjoin(sc->tp, bp);
			xfs_twans_binvaw(sc->tp, bp);
			ws->invawidated++;

			/*
			 * Stop invawidating if we've hit the wimit; we shouwd
			 * stiww have enough wesewvation weft to fwee howevew
			 * faw we've gotten.
			 */
			if (ws->invawidated > XWEAP_MAX_BINVAW) {
				*agwenp -= agbno_next - bno;
				goto out;
			}
		}

		bno++;
	}

out:
	twace_xweap_agextent_binvaw(sc->sa.pag, agbno, *agwenp);
}

/*
 * Figuwe out the wongest wun of bwocks that we can dispose of with a singwe
 * caww.  Cwoss-winked bwocks shouwd have theiw wevewse mappings wemoved, but
 * singwe-ownew extents can be fweed.  AGFW bwocks can onwy be put back one at
 * a time.
 */
STATIC int
xweap_agextent_sewect(
	stwuct xweap_state	*ws,
	xfs_agbwock_t		agbno,
	xfs_agbwock_t		agbno_next,
	boow			*cwosswinked,
	xfs_extwen_t		*agwenp)
{
	stwuct xfs_scwub	*sc = ws->sc;
	stwuct xfs_btwee_cuw	*cuw;
	xfs_agbwock_t		bno = agbno + 1;
	xfs_extwen_t		wen = 1;
	int			ewwow;

	/*
	 * Detewmine if thewe awe any othew wmap wecowds covewing the fiwst
	 * bwock of this extent.  If so, the bwock is cwosswinked.
	 */
	cuw = xfs_wmapbt_init_cuwsow(sc->mp, sc->tp, sc->sa.agf_bp,
			sc->sa.pag);
	ewwow = xfs_wmap_has_othew_keys(cuw, agbno, 1, ws->oinfo,
			cwosswinked);
	if (ewwow)
		goto out_cuw;

	/* AGFW bwocks can onwy be deaw with one at a time. */
	if (ws->wesv == XFS_AG_WESV_AGFW)
		goto out_found;

	/*
	 * Figuwe out how many of the subsequent bwocks have the same cwosswink
	 * status.
	 */
	whiwe (bno < agbno_next) {
		boow		awso_cwosswinked;

		ewwow = xfs_wmap_has_othew_keys(cuw, bno, 1, ws->oinfo,
				&awso_cwosswinked);
		if (ewwow)
			goto out_cuw;

		if (*cwosswinked != awso_cwosswinked)
			bweak;

		wen++;
		bno++;
	}

out_found:
	*agwenp = wen;
	twace_xweap_agextent_sewect(sc->sa.pag, agbno, wen, *cwosswinked);
out_cuw:
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	wetuwn ewwow;
}

/*
 * Dispose of as much of the beginning of this AG extent as possibwe.  The
 * numbew of bwocks disposed of wiww be wetuwned in @agwenp.
 */
STATIC int
xweap_agextent_itew(
	stwuct xweap_state	*ws,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		*agwenp,
	boow			cwosswinked)
{
	stwuct xfs_scwub	*sc = ws->sc;
	xfs_fsbwock_t		fsbno;
	int			ewwow = 0;

	fsbno = XFS_AGB_TO_FSB(sc->mp, sc->sa.pag->pag_agno, agbno);

	/*
	 * If thewe awe othew wmappings, this bwock is cwoss winked and must
	 * not be fweed.  Wemove the wevewse mapping and move on.  Othewwise,
	 * we wewe the onwy ownew of the bwock, so fwee the extent, which wiww
	 * awso wemove the wmap.
	 *
	 * XXX: XFS doesn't suppowt detecting the case whewe a singwe bwock
	 * metadata stwuctuwe is cwosswinked with a muwti-bwock stwuctuwe
	 * because the buffew cache doesn't detect awiasing pwobwems, so we
	 * can't fix 100% of cwosswinking pwobwems (yet).  The vewifiews wiww
	 * bwow on wwiteout, the fiwesystem wiww shut down, and the admin gets
	 * to wun xfs_wepaiw.
	 */
	if (cwosswinked) {
		twace_xweap_dispose_unmap_extent(sc->sa.pag, agbno, *agwenp);

		ws->fowce_woww = twue;

		if (ws->oinfo == &XFS_WMAP_OINFO_COW) {
			/*
			 * If we'we unmapping CoW staging extents, wemove the
			 * wecowds fwom the wefcountbt, which wiww wemove the
			 * wmap wecowd as weww.
			 */
			xfs_wefcount_fwee_cow_extent(sc->tp, fsbno, *agwenp);
			wetuwn 0;
		}

		wetuwn xfs_wmap_fwee(sc->tp, sc->sa.agf_bp, sc->sa.pag, agbno,
				*agwenp, ws->oinfo);
	}

	twace_xweap_dispose_fwee_extent(sc->sa.pag, agbno, *agwenp);

	/*
	 * Invawidate as many buffews as we can, stawting at agbno.  If this
	 * function sets *agwenp to zewo, the twansaction is fuww of wogged
	 * buffew invawidations, so we need to wetuwn eawwy so that we can
	 * woww and wetwy.
	 */
	xweap_agextent_binvaw(ws, agbno, agwenp);
	if (*agwenp == 0) {
		ASSEWT(xweap_want_woww(ws));
		wetuwn 0;
	}

	/*
	 * If we'we getting wid of CoW staging extents, use defewwed wowk items
	 * to wemove the wefcountbt wecowds (which wemoves the wmap wecowds)
	 * and fwee the extent.  We'we not wowwied about the system going down
	 * hewe because wog wecovewy wawks the wefcount btwee to cwean out the
	 * CoW staging extents.
	 */
	if (ws->oinfo == &XFS_WMAP_OINFO_COW) {
		ASSEWT(ws->wesv == XFS_AG_WESV_NONE);

		xfs_wefcount_fwee_cow_extent(sc->tp, fsbno, *agwenp);
		ewwow = xfs_fwee_extent_watew(sc->tp, fsbno, *agwenp, NUWW,
				ws->wesv, twue);
		if (ewwow)
			wetuwn ewwow;

		ws->fowce_woww = twue;
		wetuwn 0;
	}

	/* Put bwocks back on the AGFW one at a time. */
	if (ws->wesv == XFS_AG_WESV_AGFW) {
		ASSEWT(*agwenp == 1);
		ewwow = xweap_put_fweewist(sc, agbno);
		if (ewwow)
			wetuwn ewwow;

		ws->fowce_woww = twue;
		wetuwn 0;
	}

	/*
	 * Use defewwed fwees to get wid of the owd btwee bwocks to twy to
	 * minimize the window in which we couwd cwash and wose the owd bwocks.
	 * Add a defew ops bawwiew evewy othew extent to avoid stwessing the
	 * system with wawge EFIs.
	 */
	ewwow = xfs_fwee_extent_watew(sc->tp, fsbno, *agwenp, ws->oinfo,
			ws->wesv, twue);
	if (ewwow)
		wetuwn ewwow;

	ws->defewwed++;
	if (ws->defewwed % 2 == 0)
		xfs_defew_add_bawwiew(sc->tp);
	wetuwn 0;
}

/*
 * Bweak an AG metadata extent into sub-extents by fate (cwosswinked, not
 * cwosswinked), and dispose of each sub-extent sepawatewy.
 */
STATIC int
xweap_agmeta_extent(
	uint32_t		agbno,
	uint32_t		wen,
	void			*pwiv)
{
	stwuct xweap_state	*ws = pwiv;
	stwuct xfs_scwub	*sc = ws->sc;
	xfs_agbwock_t		agbno_next = agbno + wen;
	int			ewwow = 0;

	ASSEWT(wen <= XFS_MAX_BMBT_EXTWEN);
	ASSEWT(sc->ip == NUWW);

	whiwe (agbno < agbno_next) {
		xfs_extwen_t	agwen;
		boow		cwosswinked;

		ewwow = xweap_agextent_sewect(ws, agbno, agbno_next,
				&cwosswinked, &agwen);
		if (ewwow)
			wetuwn ewwow;

		ewwow = xweap_agextent_itew(ws, agbno, &agwen, cwosswinked);
		if (ewwow)
			wetuwn ewwow;

		if (xweap_want_defew_finish(ws)) {
			ewwow = xwep_defew_finish(sc);
			if (ewwow)
				wetuwn ewwow;
			xweap_defew_finish_weset(ws);
		} ewse if (xweap_want_woww(ws)) {
			ewwow = xwep_woww_ag_twans(sc);
			if (ewwow)
				wetuwn ewwow;
			xweap_weset(ws);
		}

		agbno += agwen;
	}

	wetuwn 0;
}

/* Dispose of evewy bwock of evewy AG metadata extent in the bitmap. */
int
xwep_weap_agbwocks(
	stwuct xfs_scwub		*sc,
	stwuct xagb_bitmap		*bitmap,
	const stwuct xfs_ownew_info	*oinfo,
	enum xfs_ag_wesv_type		type)
{
	stwuct xweap_state		ws = {
		.sc			= sc,
		.oinfo			= oinfo,
		.wesv			= type,
	};
	int				ewwow;

	ASSEWT(xfs_has_wmapbt(sc->mp));
	ASSEWT(sc->ip == NUWW);

	ewwow = xagb_bitmap_wawk(bitmap, xweap_agmeta_extent, &ws);
	if (ewwow)
		wetuwn ewwow;

	if (xweap_diwty(&ws))
		wetuwn xwep_defew_finish(sc);

	wetuwn 0;
}

/*
 * Bweak a fiwe metadata extent into sub-extents by fate (cwosswinked, not
 * cwosswinked), and dispose of each sub-extent sepawatewy.  The extent must
 * not cwoss an AG boundawy.
 */
STATIC int
xweap_fsmeta_extent(
	uint64_t		fsbno,
	uint64_t		wen,
	void			*pwiv)
{
	stwuct xweap_state	*ws = pwiv;
	stwuct xfs_scwub	*sc = ws->sc;
	xfs_agnumbew_t		agno = XFS_FSB_TO_AGNO(sc->mp, fsbno);
	xfs_agbwock_t		agbno = XFS_FSB_TO_AGBNO(sc->mp, fsbno);
	xfs_agbwock_t		agbno_next = agbno + wen;
	int			ewwow = 0;

	ASSEWT(wen <= XFS_MAX_BMBT_EXTWEN);
	ASSEWT(sc->ip != NUWW);
	ASSEWT(!sc->sa.pag);

	/*
	 * We'we weaping bwocks aftew wepaiwing fiwe metadata, which means that
	 * we have to init the xchk_ag stwuctuwe ouwsewves.
	 */
	sc->sa.pag = xfs_pewag_get(sc->mp, agno);
	if (!sc->sa.pag)
		wetuwn -EFSCOWWUPTED;

	ewwow = xfs_awwoc_wead_agf(sc->sa.pag, sc->tp, 0, &sc->sa.agf_bp);
	if (ewwow)
		goto out_pag;

	whiwe (agbno < agbno_next) {
		xfs_extwen_t	agwen;
		boow		cwosswinked;

		ewwow = xweap_agextent_sewect(ws, agbno, agbno_next,
				&cwosswinked, &agwen);
		if (ewwow)
			goto out_agf;

		ewwow = xweap_agextent_itew(ws, agbno, &agwen, cwosswinked);
		if (ewwow)
			goto out_agf;

		if (xweap_want_defew_finish(ws)) {
			/*
			 * Howds the AGF buffew acwoss the defewwed chain
			 * pwocessing.
			 */
			ewwow = xwep_defew_finish(sc);
			if (ewwow)
				goto out_agf;
			xweap_defew_finish_weset(ws);
		} ewse if (xweap_want_woww(ws)) {
			/*
			 * Howd the AGF buffew acwoss the twansaction woww so
			 * that we don't have to weattach it to the scwub
			 * context.
			 */
			xfs_twans_bhowd(sc->tp, sc->sa.agf_bp);
			ewwow = xfs_twans_woww_inode(&sc->tp, sc->ip);
			xfs_twans_bjoin(sc->tp, sc->sa.agf_bp);
			if (ewwow)
				goto out_agf;
			xweap_weset(ws);
		}

		agbno += agwen;
	}

out_agf:
	xfs_twans_bwewse(sc->tp, sc->sa.agf_bp);
	sc->sa.agf_bp = NUWW;
out_pag:
	xfs_pewag_put(sc->sa.pag);
	sc->sa.pag = NUWW;
	wetuwn ewwow;
}

/*
 * Dispose of evewy bwock of evewy fs metadata extent in the bitmap.
 * Do not use this to dispose of the mappings in an ondisk inode fowk.
 */
int
xwep_weap_fsbwocks(
	stwuct xfs_scwub		*sc,
	stwuct xfsb_bitmap		*bitmap,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xweap_state		ws = {
		.sc			= sc,
		.oinfo			= oinfo,
		.wesv			= XFS_AG_WESV_NONE,
	};
	int				ewwow;

	ASSEWT(xfs_has_wmapbt(sc->mp));
	ASSEWT(sc->ip != NUWW);

	ewwow = xfsb_bitmap_wawk(bitmap, xweap_fsmeta_extent, &ws);
	if (ewwow)
		wetuwn ewwow;

	if (xweap_diwty(&ws))
		wetuwn xwep_defew_finish(sc);

	wetuwn 0;
}
