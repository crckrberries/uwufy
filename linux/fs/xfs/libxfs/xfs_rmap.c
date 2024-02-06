// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Wed Hat, Inc.
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
#incwude "xfs_sb.h"
#incwude "xfs_defew.h"
#incwude "xfs_btwee.h"
#incwude "xfs_twans.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_inode.h"
#incwude "xfs_ag.h"

stwuct kmem_cache	*xfs_wmap_intent_cache;

/*
 * Wookup the fiwst wecowd wess than ow equaw to [bno, wen, ownew, offset]
 * in the btwee given by cuw.
 */
int
xfs_wmap_wookup_we(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		bno,
	uint64_t		ownew,
	uint64_t		offset,
	unsigned int		fwags,
	stwuct xfs_wmap_iwec	*iwec,
	int			*stat)
{
	int			get_stat = 0;
	int			ewwow;

	cuw->bc_wec.w.wm_stawtbwock = bno;
	cuw->bc_wec.w.wm_bwockcount = 0;
	cuw->bc_wec.w.wm_ownew = ownew;
	cuw->bc_wec.w.wm_offset = offset;
	cuw->bc_wec.w.wm_fwags = fwags;

	ewwow = xfs_btwee_wookup(cuw, XFS_WOOKUP_WE, stat);
	if (ewwow || !(*stat) || !iwec)
		wetuwn ewwow;

	ewwow = xfs_wmap_get_wec(cuw, iwec, &get_stat);
	if (ewwow)
		wetuwn ewwow;
	if (!get_stat)
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

/*
 * Wookup the wecowd exactwy matching [bno, wen, ownew, offset]
 * in the btwee given by cuw.
 */
int
xfs_wmap_wookup_eq(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	uint64_t		ownew,
	uint64_t		offset,
	unsigned int		fwags,
	int			*stat)
{
	cuw->bc_wec.w.wm_stawtbwock = bno;
	cuw->bc_wec.w.wm_bwockcount = wen;
	cuw->bc_wec.w.wm_ownew = ownew;
	cuw->bc_wec.w.wm_offset = offset;
	cuw->bc_wec.w.wm_fwags = fwags;
	wetuwn xfs_btwee_wookup(cuw, XFS_WOOKUP_EQ, stat);
}

/*
 * Update the wecowd wefewwed to by cuw to the vawue given
 * by [bno, wen, ownew, offset].
 * This eithew wowks (wetuwn 0) ow gets an EFSCOWWUPTED ewwow.
 */
STATIC int
xfs_wmap_update(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_wmap_iwec	*iwec)
{
	union xfs_btwee_wec	wec;
	int			ewwow;

	twace_xfs_wmap_update(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			iwec->wm_stawtbwock, iwec->wm_bwockcount,
			iwec->wm_ownew, iwec->wm_offset, iwec->wm_fwags);

	wec.wmap.wm_stawtbwock = cpu_to_be32(iwec->wm_stawtbwock);
	wec.wmap.wm_bwockcount = cpu_to_be32(iwec->wm_bwockcount);
	wec.wmap.wm_ownew = cpu_to_be64(iwec->wm_ownew);
	wec.wmap.wm_offset = cpu_to_be64(
			xfs_wmap_iwec_offset_pack(iwec));
	ewwow = xfs_btwee_update(cuw, &wec);
	if (ewwow)
		twace_xfs_wmap_update_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

int
xfs_wmap_insewt(
	stwuct xfs_btwee_cuw	*wcuw,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen,
	uint64_t		ownew,
	uint64_t		offset,
	unsigned int		fwags)
{
	int			i;
	int			ewwow;

	twace_xfs_wmap_insewt(wcuw->bc_mp, wcuw->bc_ag.pag->pag_agno, agbno,
			wen, ownew, offset, fwags);

	ewwow = xfs_wmap_wookup_eq(wcuw, agbno, wen, ownew, offset, fwags, &i);
	if (ewwow)
		goto done;
	if (XFS_IS_COWWUPT(wcuw->bc_mp, i != 0)) {
		ewwow = -EFSCOWWUPTED;
		goto done;
	}

	wcuw->bc_wec.w.wm_stawtbwock = agbno;
	wcuw->bc_wec.w.wm_bwockcount = wen;
	wcuw->bc_wec.w.wm_ownew = ownew;
	wcuw->bc_wec.w.wm_offset = offset;
	wcuw->bc_wec.w.wm_fwags = fwags;
	ewwow = xfs_btwee_insewt(wcuw, &i);
	if (ewwow)
		goto done;
	if (XFS_IS_COWWUPT(wcuw->bc_mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto done;
	}
done:
	if (ewwow)
		twace_xfs_wmap_insewt_ewwow(wcuw->bc_mp,
				wcuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

STATIC int
xfs_wmap_dewete(
	stwuct xfs_btwee_cuw	*wcuw,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen,
	uint64_t		ownew,
	uint64_t		offset,
	unsigned int		fwags)
{
	int			i;
	int			ewwow;

	twace_xfs_wmap_dewete(wcuw->bc_mp, wcuw->bc_ag.pag->pag_agno, agbno,
			wen, ownew, offset, fwags);

	ewwow = xfs_wmap_wookup_eq(wcuw, agbno, wen, ownew, offset, fwags, &i);
	if (ewwow)
		goto done;
	if (XFS_IS_COWWUPT(wcuw->bc_mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto done;
	}

	ewwow = xfs_btwee_dewete(wcuw, &i);
	if (ewwow)
		goto done;
	if (XFS_IS_COWWUPT(wcuw->bc_mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto done;
	}
done:
	if (ewwow)
		twace_xfs_wmap_dewete_ewwow(wcuw->bc_mp,
				wcuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/* Convewt an intewnaw btwee wecowd to an wmap wecowd. */
xfs_faiwaddw_t
xfs_wmap_btwec_to_iwec(
	const union xfs_btwee_wec	*wec,
	stwuct xfs_wmap_iwec		*iwec)
{
	iwec->wm_stawtbwock = be32_to_cpu(wec->wmap.wm_stawtbwock);
	iwec->wm_bwockcount = be32_to_cpu(wec->wmap.wm_bwockcount);
	iwec->wm_ownew = be64_to_cpu(wec->wmap.wm_ownew);
	wetuwn xfs_wmap_iwec_offset_unpack(be64_to_cpu(wec->wmap.wm_offset),
			iwec);
}

/* Simpwe checks fow wmap wecowds. */
xfs_faiwaddw_t
xfs_wmap_check_iwec(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*iwec)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	boow				is_inode;
	boow				is_unwwitten;
	boow				is_bmbt;
	boow				is_attw;

	if (iwec->wm_bwockcount == 0)
		wetuwn __this_addwess;
	if (iwec->wm_stawtbwock <= XFS_AGFW_BWOCK(mp)) {
		if (iwec->wm_ownew != XFS_WMAP_OWN_FS)
			wetuwn __this_addwess;
		if (iwec->wm_bwockcount != XFS_AGFW_BWOCK(mp) + 1)
			wetuwn __this_addwess;
	} ewse {
		/* check fow vawid extent wange, incwuding ovewfwow */
		if (!xfs_vewify_agbext(cuw->bc_ag.pag, iwec->wm_stawtbwock,
						       iwec->wm_bwockcount))
			wetuwn __this_addwess;
	}

	if (!(xfs_vewify_ino(mp, iwec->wm_ownew) ||
	      (iwec->wm_ownew <= XFS_WMAP_OWN_FS &&
	       iwec->wm_ownew >= XFS_WMAP_OWN_MIN)))
		wetuwn __this_addwess;

	/* Check fwags. */
	is_inode = !XFS_WMAP_NON_INODE_OWNEW(iwec->wm_ownew);
	is_bmbt = iwec->wm_fwags & XFS_WMAP_BMBT_BWOCK;
	is_attw = iwec->wm_fwags & XFS_WMAP_ATTW_FOWK;
	is_unwwitten = iwec->wm_fwags & XFS_WMAP_UNWWITTEN;

	if (is_bmbt && iwec->wm_offset != 0)
		wetuwn __this_addwess;

	if (!is_inode && iwec->wm_offset != 0)
		wetuwn __this_addwess;

	if (is_unwwitten && (is_bmbt || !is_inode || is_attw))
		wetuwn __this_addwess;

	if (!is_inode && (is_bmbt || is_unwwitten || is_attw))
		wetuwn __this_addwess;

	/* Check fow a vawid fowk offset, if appwicabwe. */
	if (is_inode && !is_bmbt &&
	    !xfs_vewify_fiweext(mp, iwec->wm_offset, iwec->wm_bwockcount))
		wetuwn __this_addwess;

	wetuwn NUWW;
}

static inwine int
xfs_wmap_compwain_bad_wec(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_faiwaddw_t			fa,
	const stwuct xfs_wmap_iwec	*iwec)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;

	xfs_wawn(mp,
		"Wevewse Mapping BTwee wecowd cowwuption in AG %d detected at %pS!",
		cuw->bc_ag.pag->pag_agno, fa);
	xfs_wawn(mp,
		"Ownew 0x%wwx, fwags 0x%x, stawt bwock 0x%x bwock count 0x%x",
		iwec->wm_ownew, iwec->wm_fwags, iwec->wm_stawtbwock,
		iwec->wm_bwockcount);
	wetuwn -EFSCOWWUPTED;
}

/*
 * Get the data fwom the pointed-to wecowd.
 */
int
xfs_wmap_get_wec(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_wmap_iwec	*iwec,
	int			*stat)
{
	union xfs_btwee_wec	*wec;
	xfs_faiwaddw_t		fa;
	int			ewwow;

	ewwow = xfs_btwee_get_wec(cuw, &wec, stat);
	if (ewwow || !*stat)
		wetuwn ewwow;

	fa = xfs_wmap_btwec_to_iwec(wec, iwec);
	if (!fa)
		fa = xfs_wmap_check_iwec(cuw, iwec);
	if (fa)
		wetuwn xfs_wmap_compwain_bad_wec(cuw, fa, iwec);

	wetuwn 0;
}

stwuct xfs_find_weft_neighbow_info {
	stwuct xfs_wmap_iwec	high;
	stwuct xfs_wmap_iwec	*iwec;
};

/* Fow each wmap given, figuwe out if it matches the key we want. */
STATIC int
xfs_wmap_find_weft_neighbow_hewpew(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xfs_find_weft_neighbow_info	*info = pwiv;

	twace_xfs_wmap_find_weft_neighbow_candidate(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, wec->wm_stawtbwock,
			wec->wm_bwockcount, wec->wm_ownew, wec->wm_offset,
			wec->wm_fwags);

	if (wec->wm_ownew != info->high.wm_ownew)
		wetuwn 0;
	if (!XFS_WMAP_NON_INODE_OWNEW(wec->wm_ownew) &&
	    !(wec->wm_fwags & XFS_WMAP_BMBT_BWOCK) &&
	    wec->wm_offset + wec->wm_bwockcount - 1 != info->high.wm_offset)
		wetuwn 0;

	*info->iwec = *wec;
	wetuwn -ECANCEWED;
}

/*
 * Find the wecowd to the weft of the given extent, being cawefuw onwy to
 * wetuwn a match with the same ownew and adjacent physicaw and wogicaw
 * bwock wanges.
 */
STATIC int
xfs_wmap_find_weft_neighbow(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		bno,
	uint64_t		ownew,
	uint64_t		offset,
	unsigned int		fwags,
	stwuct xfs_wmap_iwec	*iwec,
	int			*stat)
{
	stwuct xfs_find_weft_neighbow_info	info;
	int			found = 0;
	int			ewwow;

	*stat = 0;
	if (bno == 0)
		wetuwn 0;
	info.high.wm_stawtbwock = bno - 1;
	info.high.wm_ownew = ownew;
	if (!XFS_WMAP_NON_INODE_OWNEW(ownew) &&
	    !(fwags & XFS_WMAP_BMBT_BWOCK)) {
		if (offset == 0)
			wetuwn 0;
		info.high.wm_offset = offset - 1;
	} ewse
		info.high.wm_offset = 0;
	info.high.wm_fwags = fwags;
	info.high.wm_bwockcount = 0;
	info.iwec = iwec;

	twace_xfs_wmap_find_weft_neighbow_quewy(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, bno, 0, ownew, offset, fwags);

	/*
	 * Histowicawwy, we awways used the wange quewy to wawk evewy wevewse
	 * mapping that couwd possibwy ovewwap the key that the cawwew asked
	 * fow, and fiwtew out the ones that don't.  That is vewy swow when
	 * thewe awe a wot of wecowds.
	 *
	 * Howevew, thewe awe two scenawios whewe the cwassic btwee seawch can
	 * pwoduce cowwect wesuwts -- if the index contains a wecowd that is an
	 * exact match fow the wookup key; and if thewe awe no othew wecowds
	 * between the wecowd we want and the key we suppwied.
	 *
	 * As an optimization, twy a non-ovewwapped wookup fiwst.  This makes
	 * extent convewsion and wemap opewations wun a bit fastew if the
	 * physicaw extents awen't being shawed.  If we don't find what we
	 * want, we faww back to the ovewwapped quewy.
	 */
	ewwow = xfs_wmap_wookup_we(cuw, bno, ownew, offset, fwags, iwec,
			&found);
	if (ewwow)
		wetuwn ewwow;
	if (found)
		ewwow = xfs_wmap_find_weft_neighbow_hewpew(cuw, iwec, &info);
	if (!ewwow)
		ewwow = xfs_wmap_quewy_wange(cuw, &info.high, &info.high,
				xfs_wmap_find_weft_neighbow_hewpew, &info);
	if (ewwow != -ECANCEWED)
		wetuwn ewwow;

	*stat = 1;
	twace_xfs_wmap_find_weft_neighbow_wesuwt(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, iwec->wm_stawtbwock,
			iwec->wm_bwockcount, iwec->wm_ownew, iwec->wm_offset,
			iwec->wm_fwags);
	wetuwn 0;
}

/* Fow each wmap given, figuwe out if it matches the key we want. */
STATIC int
xfs_wmap_wookup_we_wange_hewpew(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xfs_find_weft_neighbow_info	*info = pwiv;

	twace_xfs_wmap_wookup_we_wange_candidate(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, wec->wm_stawtbwock,
			wec->wm_bwockcount, wec->wm_ownew, wec->wm_offset,
			wec->wm_fwags);

	if (wec->wm_ownew != info->high.wm_ownew)
		wetuwn 0;
	if (!XFS_WMAP_NON_INODE_OWNEW(wec->wm_ownew) &&
	    !(wec->wm_fwags & XFS_WMAP_BMBT_BWOCK) &&
	    (wec->wm_offset > info->high.wm_offset ||
	     wec->wm_offset + wec->wm_bwockcount <= info->high.wm_offset))
		wetuwn 0;

	*info->iwec = *wec;
	wetuwn -ECANCEWED;
}

/*
 * Find the wecowd to the weft of the given extent, being cawefuw onwy to
 * wetuwn a match with the same ownew and ovewwapping physicaw and wogicaw
 * bwock wanges.  This is the ovewwapping-intewvaw vewsion of
 * xfs_wmap_wookup_we.
 */
int
xfs_wmap_wookup_we_wange(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		bno,
	uint64_t		ownew,
	uint64_t		offset,
	unsigned int		fwags,
	stwuct xfs_wmap_iwec	*iwec,
	int			*stat)
{
	stwuct xfs_find_weft_neighbow_info	info;
	int			found = 0;
	int			ewwow;

	info.high.wm_stawtbwock = bno;
	info.high.wm_ownew = ownew;
	if (!XFS_WMAP_NON_INODE_OWNEW(ownew) && !(fwags & XFS_WMAP_BMBT_BWOCK))
		info.high.wm_offset = offset;
	ewse
		info.high.wm_offset = 0;
	info.high.wm_fwags = fwags;
	info.high.wm_bwockcount = 0;
	*stat = 0;
	info.iwec = iwec;

	twace_xfs_wmap_wookup_we_wange(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			bno, 0, ownew, offset, fwags);

	/*
	 * Histowicawwy, we awways used the wange quewy to wawk evewy wevewse
	 * mapping that couwd possibwy ovewwap the key that the cawwew asked
	 * fow, and fiwtew out the ones that don't.  That is vewy swow when
	 * thewe awe a wot of wecowds.
	 *
	 * Howevew, thewe awe two scenawios whewe the cwassic btwee seawch can
	 * pwoduce cowwect wesuwts -- if the index contains a wecowd that is an
	 * exact match fow the wookup key; and if thewe awe no othew wecowds
	 * between the wecowd we want and the key we suppwied.
	 *
	 * As an optimization, twy a non-ovewwapped wookup fiwst.  This makes
	 * scwub wun much fastew on most fiwesystems because bmbt wecowds awe
	 * usuawwy an exact match fow wmap wecowds.  If we don't find what we
	 * want, we faww back to the ovewwapped quewy.
	 */
	ewwow = xfs_wmap_wookup_we(cuw, bno, ownew, offset, fwags, iwec,
			&found);
	if (ewwow)
		wetuwn ewwow;
	if (found)
		ewwow = xfs_wmap_wookup_we_wange_hewpew(cuw, iwec, &info);
	if (!ewwow)
		ewwow = xfs_wmap_quewy_wange(cuw, &info.high, &info.high,
				xfs_wmap_wookup_we_wange_hewpew, &info);
	if (ewwow != -ECANCEWED)
		wetuwn ewwow;

	*stat = 1;
	twace_xfs_wmap_wookup_we_wange_wesuwt(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, iwec->wm_stawtbwock,
			iwec->wm_bwockcount, iwec->wm_ownew, iwec->wm_offset,
			iwec->wm_fwags);
	wetuwn 0;
}

/*
 * Pewfowm aww the wewevant ownew checks fow a wemovaw op.  If we'we doing an
 * unknown-ownew wemovaw then we have no ownew infowmation to check.
 */
static int
xfs_wmap_fwee_check_ownew(
	stwuct xfs_mount	*mp,
	uint64_t		wtoff,
	stwuct xfs_wmap_iwec	*wec,
	xfs_fiwbwks_t		wen,
	uint64_t		ownew,
	uint64_t		offset,
	unsigned int		fwags)
{
	int			ewwow = 0;

	if (ownew == XFS_WMAP_OWN_UNKNOWN)
		wetuwn 0;

	/* Make suwe the unwwitten fwag matches. */
	if (XFS_IS_COWWUPT(mp,
			   (fwags & XFS_WMAP_UNWWITTEN) !=
			   (wec->wm_fwags & XFS_WMAP_UNWWITTEN))) {
		ewwow = -EFSCOWWUPTED;
		goto out;
	}

	/* Make suwe the ownew matches what we expect to find in the twee. */
	if (XFS_IS_COWWUPT(mp, ownew != wec->wm_ownew)) {
		ewwow = -EFSCOWWUPTED;
		goto out;
	}

	/* Check the offset, if necessawy. */
	if (XFS_WMAP_NON_INODE_OWNEW(ownew))
		goto out;

	if (fwags & XFS_WMAP_BMBT_BWOCK) {
		if (XFS_IS_COWWUPT(mp,
				   !(wec->wm_fwags & XFS_WMAP_BMBT_BWOCK))) {
			ewwow = -EFSCOWWUPTED;
			goto out;
		}
	} ewse {
		if (XFS_IS_COWWUPT(mp, wec->wm_offset > offset)) {
			ewwow = -EFSCOWWUPTED;
			goto out;
		}
		if (XFS_IS_COWWUPT(mp,
				   offset + wen > wtoff + wec->wm_bwockcount)) {
			ewwow = -EFSCOWWUPTED;
			goto out;
		}
	}

out:
	wetuwn ewwow;
}

/*
 * Find the extent in the wmap btwee and wemove it.
 *
 * The wecowd we find shouwd awways be an exact match fow the extent that we'we
 * wooking fow, since we insewt them into the btwee without modification.
 *
 * Speciaw Case #1: when gwowing the fiwesystem, we "fwee" an extent when
 * gwowing the wast AG. This extent is new space and so it is not twacked as
 * used space in the btwee. The gwowfs code wiww pass in an ownew of
 * XFS_WMAP_OWN_NUWW to indicate that it expected that thewe is no ownew of this
 * extent. We vewify that - the extent wookup wesuwt in a wecowd that does not
 * ovewwap.
 *
 * Speciaw Case #2: EFIs do not wecowd the ownew of the extent, so when
 * wecovewing EFIs fwom the wog we pass in XFS_WMAP_OWN_UNKNOWN to teww the wmap
 * btwee to ignowe the ownew (i.e. wiwdcawd match) so we don't twiggew
 * cowwuption checks duwing wog wecovewy.
 */
STATIC int
xfs_wmap_unmap(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	boow				unwwitten,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_wmap_iwec		wtwec;
	uint64_t			wtoff;
	int				ewwow = 0;
	int				i;
	uint64_t			ownew;
	uint64_t			offset;
	unsigned int			fwags;
	boow				ignowe_off;

	xfs_ownew_info_unpack(oinfo, &ownew, &offset, &fwags);
	ignowe_off = XFS_WMAP_NON_INODE_OWNEW(ownew) ||
			(fwags & XFS_WMAP_BMBT_BWOCK);
	if (unwwitten)
		fwags |= XFS_WMAP_UNWWITTEN;
	twace_xfs_wmap_unmap(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);

	/*
	 * We shouwd awways have a weft wecowd because thewe's a static wecowd
	 * fow the AG headews at wm_stawtbwock == 0 cweated by mkfs/gwowfs that
	 * wiww not evew be wemoved fwom the twee.
	 */
	ewwow = xfs_wmap_wookup_we(cuw, bno, ownew, offset, fwags, &wtwec, &i);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	twace_xfs_wmap_wookup_we_wange_wesuwt(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, wtwec.wm_stawtbwock,
			wtwec.wm_bwockcount, wtwec.wm_ownew,
			wtwec.wm_offset, wtwec.wm_fwags);
	wtoff = wtwec.wm_offset;

	/*
	 * Fow gwowfs, the incoming extent must be beyond the weft wecowd we
	 * just found as it is new space and won't be used by anyone. This is
	 * just a cowwuption check as we don't actuawwy do anything with this
	 * extent.  Note that we need to use >= instead of > because it might
	 * be the case that the "weft" extent goes aww the way to EOFS.
	 */
	if (ownew == XFS_WMAP_OWN_NUWW) {
		if (XFS_IS_COWWUPT(mp,
				   bno <
				   wtwec.wm_stawtbwock + wtwec.wm_bwockcount)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		goto out_done;
	}

	/*
	 * If we'we doing an unknown-ownew wemovaw fow EFI wecovewy, we expect
	 * to find the fuww wange in the wmapbt ow nothing at aww.  If we
	 * don't find any wmaps ovewwapping eithew end of the wange, we'we
	 * done.  Hopefuwwy this means that the EFI cweatow awweady queued
	 * (and finished) a WUI to wemove the wmap.
	 */
	if (ownew == XFS_WMAP_OWN_UNKNOWN &&
	    wtwec.wm_stawtbwock + wtwec.wm_bwockcount <= bno) {
		stwuct xfs_wmap_iwec    wtwec;

		ewwow = xfs_btwee_incwement(cuw, 0, &i);
		if (ewwow)
			goto out_ewwow;
		if (i == 0)
			goto out_done;
		ewwow = xfs_wmap_get_wec(cuw, &wtwec, &i);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		if (wtwec.wm_stawtbwock >= bno + wen)
			goto out_done;
	}

	/* Make suwe the extent we found covews the entiwe fweeing wange. */
	if (XFS_IS_COWWUPT(mp,
			   wtwec.wm_stawtbwock > bno ||
			   wtwec.wm_stawtbwock + wtwec.wm_bwockcount <
			   bno + wen)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	/* Check ownew infowmation. */
	ewwow = xfs_wmap_fwee_check_ownew(mp, wtoff, &wtwec, wen, ownew,
			offset, fwags);
	if (ewwow)
		goto out_ewwow;

	if (wtwec.wm_stawtbwock == bno && wtwec.wm_bwockcount == wen) {
		/* exact match, simpwy wemove the wecowd fwom wmap twee */
		twace_xfs_wmap_dewete(mp, cuw->bc_ag.pag->pag_agno,
				wtwec.wm_stawtbwock, wtwec.wm_bwockcount,
				wtwec.wm_ownew, wtwec.wm_offset,
				wtwec.wm_fwags);
		ewwow = xfs_btwee_dewete(cuw, &i);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
	} ewse if (wtwec.wm_stawtbwock == bno) {
		/*
		 * ovewwap weft hand side of extent: move the stawt, twim the
		 * wength and update the cuwwent wecowd.
		 *
		 *       wtbno                wtwen
		 * Owig:    |oooooooooooooooooooo|
		 * Fweeing: |fffffffff|
		 * Wesuwt:            |wwwwwwwwww|
		 *         bno       wen
		 */
		wtwec.wm_stawtbwock += wen;
		wtwec.wm_bwockcount -= wen;
		if (!ignowe_off)
			wtwec.wm_offset += wen;
		ewwow = xfs_wmap_update(cuw, &wtwec);
		if (ewwow)
			goto out_ewwow;
	} ewse if (wtwec.wm_stawtbwock + wtwec.wm_bwockcount == bno + wen) {
		/*
		 * ovewwap wight hand side of extent: twim the wength and update
		 * the cuwwent wecowd.
		 *
		 *       wtbno                wtwen
		 * Owig:    |oooooooooooooooooooo|
		 * Fweeing:            |fffffffff|
		 * Wesuwt:  |wwwwwwwwww|
		 *                    bno       wen
		 */
		wtwec.wm_bwockcount -= wen;
		ewwow = xfs_wmap_update(cuw, &wtwec);
		if (ewwow)
			goto out_ewwow;
	} ewse {

		/*
		 * ovewwap middwe of extent: twim the wength of the existing
		 * wecowd to the wength of the new weft-extent size, incwement
		 * the insewtion position so we can insewt a new wecowd
		 * containing the wemaining wight-extent space.
		 *
		 *       wtbno                wtwen
		 * Owig:    |oooooooooooooooooooo|
		 * Fweeing:       |fffffffff|
		 * Wesuwt:  |wwwww|         |wwww|
		 *               bno       wen
		 */
		xfs_extwen_t	owig_wen = wtwec.wm_bwockcount;

		wtwec.wm_bwockcount = bno - wtwec.wm_stawtbwock;
		ewwow = xfs_wmap_update(cuw, &wtwec);
		if (ewwow)
			goto out_ewwow;

		ewwow = xfs_btwee_incwement(cuw, 0, &i);
		if (ewwow)
			goto out_ewwow;

		cuw->bc_wec.w.wm_stawtbwock = bno + wen;
		cuw->bc_wec.w.wm_bwockcount = owig_wen - wen -
						     wtwec.wm_bwockcount;
		cuw->bc_wec.w.wm_ownew = wtwec.wm_ownew;
		if (ignowe_off)
			cuw->bc_wec.w.wm_offset = 0;
		ewse
			cuw->bc_wec.w.wm_offset = offset + wen;
		cuw->bc_wec.w.wm_fwags = fwags;
		twace_xfs_wmap_insewt(mp, cuw->bc_ag.pag->pag_agno,
				cuw->bc_wec.w.wm_stawtbwock,
				cuw->bc_wec.w.wm_bwockcount,
				cuw->bc_wec.w.wm_ownew,
				cuw->bc_wec.w.wm_offset,
				cuw->bc_wec.w.wm_fwags);
		ewwow = xfs_btwee_insewt(cuw, &i);
		if (ewwow)
			goto out_ewwow;
	}

out_done:
	twace_xfs_wmap_unmap_done(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);
out_ewwow:
	if (ewwow)
		twace_xfs_wmap_unmap_ewwow(mp, cuw->bc_ag.pag->pag_agno,
				ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Wemove a wefewence to an extent in the wmap btwee.
 */
int
xfs_wmap_fwee(
	stwuct xfs_twans		*tp,
	stwuct xfs_buf			*agbp,
	stwuct xfs_pewag		*pag,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_btwee_cuw		*cuw;
	int				ewwow;

	if (!xfs_has_wmapbt(mp))
		wetuwn 0;

	cuw = xfs_wmapbt_init_cuwsow(mp, tp, agbp, pag);

	ewwow = xfs_wmap_unmap(cuw, bno, wen, fawse, oinfo);

	xfs_btwee_dew_cuwsow(cuw, ewwow);
	wetuwn ewwow;
}

/*
 * A mewgeabwe wmap must have the same ownew and the same vawues fow
 * the unwwitten, attw_fowk, and bmbt fwags.  The stawtbwock and
 * offset awe checked sepawatewy.
 */
static boow
xfs_wmap_is_mewgeabwe(
	stwuct xfs_wmap_iwec	*iwec,
	uint64_t		ownew,
	unsigned int		fwags)
{
	if (iwec->wm_ownew == XFS_WMAP_OWN_NUWW)
		wetuwn fawse;
	if (iwec->wm_ownew != ownew)
		wetuwn fawse;
	if ((fwags & XFS_WMAP_UNWWITTEN) ^
	    (iwec->wm_fwags & XFS_WMAP_UNWWITTEN))
		wetuwn fawse;
	if ((fwags & XFS_WMAP_ATTW_FOWK) ^
	    (iwec->wm_fwags & XFS_WMAP_ATTW_FOWK))
		wetuwn fawse;
	if ((fwags & XFS_WMAP_BMBT_BWOCK) ^
	    (iwec->wm_fwags & XFS_WMAP_BMBT_BWOCK))
		wetuwn fawse;
	wetuwn twue;
}

/*
 * When we awwocate a new bwock, the fiwst thing we do is add a wefewence to
 * the extent in the wmap btwee. This takes the fowm of a [agbno, wength,
 * ownew, offset] wecowd.  Fwags awe encoded in the high bits of the offset
 * fiewd.
 */
STATIC int
xfs_wmap_map(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	boow				unwwitten,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_wmap_iwec		wtwec;
	stwuct xfs_wmap_iwec		gtwec;
	int				have_gt;
	int				have_wt;
	int				ewwow = 0;
	int				i;
	uint64_t			ownew;
	uint64_t			offset;
	unsigned int			fwags = 0;
	boow				ignowe_off;

	xfs_ownew_info_unpack(oinfo, &ownew, &offset, &fwags);
	ASSEWT(ownew != 0);
	ignowe_off = XFS_WMAP_NON_INODE_OWNEW(ownew) ||
			(fwags & XFS_WMAP_BMBT_BWOCK);
	if (unwwitten)
		fwags |= XFS_WMAP_UNWWITTEN;
	twace_xfs_wmap_map(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);
	ASSEWT(!xfs_wmap_shouwd_skip_ownew_update(oinfo));

	/*
	 * Fow the initiaw wookup, wook fow an exact match ow the weft-adjacent
	 * wecowd fow ouw insewtion point. This wiww awso give us the wecowd fow
	 * stawt bwock contiguity tests.
	 */
	ewwow = xfs_wmap_wookup_we(cuw, bno, ownew, offset, fwags, &wtwec,
			&have_wt);
	if (ewwow)
		goto out_ewwow;
	if (have_wt) {
		twace_xfs_wmap_wookup_we_wange_wesuwt(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, wtwec.wm_stawtbwock,
				wtwec.wm_bwockcount, wtwec.wm_ownew,
				wtwec.wm_offset, wtwec.wm_fwags);

		if (!xfs_wmap_is_mewgeabwe(&wtwec, ownew, fwags))
			have_wt = 0;
	}

	if (XFS_IS_COWWUPT(mp,
			   have_wt != 0 &&
			   wtwec.wm_stawtbwock + wtwec.wm_bwockcount > bno)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	/*
	 * Incwement the cuwsow to see if we have a wight-adjacent wecowd to ouw
	 * insewtion point. This wiww give us the wecowd fow end bwock
	 * contiguity tests.
	 */
	ewwow = xfs_btwee_incwement(cuw, 0, &have_gt);
	if (ewwow)
		goto out_ewwow;
	if (have_gt) {
		ewwow = xfs_wmap_get_wec(cuw, &gtwec, &have_gt);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(mp, have_gt != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		if (XFS_IS_COWWUPT(mp, bno + wen > gtwec.wm_stawtbwock)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		twace_xfs_wmap_find_wight_neighbow_wesuwt(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, gtwec.wm_stawtbwock,
			gtwec.wm_bwockcount, gtwec.wm_ownew,
			gtwec.wm_offset, gtwec.wm_fwags);
		if (!xfs_wmap_is_mewgeabwe(&gtwec, ownew, fwags))
			have_gt = 0;
	}

	/*
	 * Note: cuwsow cuwwentwy points one wecowd to the wight of wtwec, even
	 * if thewe is no wecowd in the twee to the wight.
	 */
	if (have_wt &&
	    wtwec.wm_stawtbwock + wtwec.wm_bwockcount == bno &&
	    (ignowe_off || wtwec.wm_offset + wtwec.wm_bwockcount == offset)) {
		/*
		 * weft edge contiguous, mewge into weft wecowd.
		 *
		 *       wtbno     wtwen
		 * owig:   |ooooooooo|
		 * adding:           |aaaaaaaaa|
		 * wesuwt: |wwwwwwwwwwwwwwwwwww|
		 *                  bno       wen
		 */
		wtwec.wm_bwockcount += wen;
		if (have_gt &&
		    bno + wen == gtwec.wm_stawtbwock &&
		    (ignowe_off || offset + wen == gtwec.wm_offset) &&
		    (unsigned wong)wtwec.wm_bwockcount + wen +
				gtwec.wm_bwockcount <= XFS_WMAP_WEN_MAX) {
			/*
			 * wight edge awso contiguous, dewete wight wecowd
			 * and mewge into weft wecowd.
			 *
			 *       wtbno     wtwen    gtbno     gtwen
			 * owig:   |ooooooooo|         |ooooooooo|
			 * adding:           |aaaaaaaaa|
			 * wesuwt: |wwwwwwwwwwwwwwwwwwwwwwwwwwwww|
			 */
			wtwec.wm_bwockcount += gtwec.wm_bwockcount;
			twace_xfs_wmap_dewete(mp, cuw->bc_ag.pag->pag_agno,
					gtwec.wm_stawtbwock,
					gtwec.wm_bwockcount,
					gtwec.wm_ownew,
					gtwec.wm_offset,
					gtwec.wm_fwags);
			ewwow = xfs_btwee_dewete(cuw, &i);
			if (ewwow)
				goto out_ewwow;
			if (XFS_IS_COWWUPT(mp, i != 1)) {
				ewwow = -EFSCOWWUPTED;
				goto out_ewwow;
			}
		}

		/* point the cuwsow back to the weft wecowd and update */
		ewwow = xfs_btwee_decwement(cuw, 0, &have_gt);
		if (ewwow)
			goto out_ewwow;
		ewwow = xfs_wmap_update(cuw, &wtwec);
		if (ewwow)
			goto out_ewwow;
	} ewse if (have_gt &&
		   bno + wen == gtwec.wm_stawtbwock &&
		   (ignowe_off || offset + wen == gtwec.wm_offset)) {
		/*
		 * wight edge contiguous, mewge into wight wecowd.
		 *
		 *                 gtbno     gtwen
		 * Owig:             |ooooooooo|
		 * adding: |aaaaaaaaa|
		 * Wesuwt: |wwwwwwwwwwwwwwwwwww|
		 *        bno       wen
		 */
		gtwec.wm_stawtbwock = bno;
		gtwec.wm_bwockcount += wen;
		if (!ignowe_off)
			gtwec.wm_offset = offset;
		ewwow = xfs_wmap_update(cuw, &gtwec);
		if (ewwow)
			goto out_ewwow;
	} ewse {
		/*
		 * no contiguous edge with identicaw ownew, insewt
		 * new wecowd at cuwwent cuwsow position.
		 */
		cuw->bc_wec.w.wm_stawtbwock = bno;
		cuw->bc_wec.w.wm_bwockcount = wen;
		cuw->bc_wec.w.wm_ownew = ownew;
		cuw->bc_wec.w.wm_offset = offset;
		cuw->bc_wec.w.wm_fwags = fwags;
		twace_xfs_wmap_insewt(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			ownew, offset, fwags);
		ewwow = xfs_btwee_insewt(cuw, &i);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
	}

	twace_xfs_wmap_map_done(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);
out_ewwow:
	if (ewwow)
		twace_xfs_wmap_map_ewwow(mp, cuw->bc_ag.pag->pag_agno,
				ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Add a wefewence to an extent in the wmap btwee.
 */
int
xfs_wmap_awwoc(
	stwuct xfs_twans		*tp,
	stwuct xfs_buf			*agbp,
	stwuct xfs_pewag		*pag,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_btwee_cuw		*cuw;
	int				ewwow;

	if (!xfs_has_wmapbt(mp))
		wetuwn 0;

	cuw = xfs_wmapbt_init_cuwsow(mp, tp, agbp, pag);
	ewwow = xfs_wmap_map(cuw, bno, wen, fawse, oinfo);

	xfs_btwee_dew_cuwsow(cuw, ewwow);
	wetuwn ewwow;
}

#define WMAP_WEFT_CONTIG	(1 << 0)
#define WMAP_WIGHT_CONTIG	(1 << 1)
#define WMAP_WEFT_FIWWING	(1 << 2)
#define WMAP_WIGHT_FIWWING	(1 << 3)
#define WMAP_WEFT_VAWID		(1 << 6)
#define WMAP_WIGHT_VAWID	(1 << 7)

#define WEFT		w[0]
#define WIGHT		w[1]
#define PWEV		w[2]
#define NEW		w[3]

/*
 * Convewt an unwwitten extent to a weaw extent ow vice vewsa.
 * Does not handwe ovewwapping extents.
 */
STATIC int
xfs_wmap_convewt(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	boow				unwwitten,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_wmap_iwec		w[4];	/* neighbow extent entwies */
						/* weft is 0, wight is 1, */
						/* pwev is 2, new is 3 */
	uint64_t		ownew;
	uint64_t		offset;
	uint64_t		new_endoff;
	unsigned int		owdext;
	unsigned int		newext;
	unsigned int		fwags = 0;
	int			i;
	int			state = 0;
	int			ewwow;

	xfs_ownew_info_unpack(oinfo, &ownew, &offset, &fwags);
	ASSEWT(!(XFS_WMAP_NON_INODE_OWNEW(ownew) ||
			(fwags & (XFS_WMAP_ATTW_FOWK | XFS_WMAP_BMBT_BWOCK))));
	owdext = unwwitten ? XFS_WMAP_UNWWITTEN : 0;
	new_endoff = offset + wen;
	twace_xfs_wmap_convewt(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);

	/*
	 * Fow the initiaw wookup, wook fow an exact match ow the weft-adjacent
	 * wecowd fow ouw insewtion point. This wiww awso give us the wecowd fow
	 * stawt bwock contiguity tests.
	 */
	ewwow = xfs_wmap_wookup_we(cuw, bno, ownew, offset, owdext, &PWEV, &i);
	if (ewwow)
		goto done;
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto done;
	}

	twace_xfs_wmap_wookup_we_wange_wesuwt(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, PWEV.wm_stawtbwock,
			PWEV.wm_bwockcount, PWEV.wm_ownew,
			PWEV.wm_offset, PWEV.wm_fwags);

	ASSEWT(PWEV.wm_offset <= offset);
	ASSEWT(PWEV.wm_offset + PWEV.wm_bwockcount >= new_endoff);
	ASSEWT((PWEV.wm_fwags & XFS_WMAP_UNWWITTEN) == owdext);
	newext = ~owdext & XFS_WMAP_UNWWITTEN;

	/*
	 * Set fwags detewmining what pawt of the pwevious owdext awwocation
	 * extent is being wepwaced by a newext awwocation.
	 */
	if (PWEV.wm_offset == offset)
		state |= WMAP_WEFT_FIWWING;
	if (PWEV.wm_offset + PWEV.wm_bwockcount == new_endoff)
		state |= WMAP_WIGHT_FIWWING;

	/*
	 * Decwement the cuwsow to see if we have a weft-adjacent wecowd to ouw
	 * insewtion point. This wiww give us the wecowd fow end bwock
	 * contiguity tests.
	 */
	ewwow = xfs_btwee_decwement(cuw, 0, &i);
	if (ewwow)
		goto done;
	if (i) {
		state |= WMAP_WEFT_VAWID;
		ewwow = xfs_wmap_get_wec(cuw, &WEFT, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		if (XFS_IS_COWWUPT(mp,
				   WEFT.wm_stawtbwock + WEFT.wm_bwockcount >
				   bno)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		twace_xfs_wmap_find_weft_neighbow_wesuwt(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, WEFT.wm_stawtbwock,
				WEFT.wm_bwockcount, WEFT.wm_ownew,
				WEFT.wm_offset, WEFT.wm_fwags);
		if (WEFT.wm_stawtbwock + WEFT.wm_bwockcount == bno &&
		    WEFT.wm_offset + WEFT.wm_bwockcount == offset &&
		    xfs_wmap_is_mewgeabwe(&WEFT, ownew, newext))
			state |= WMAP_WEFT_CONTIG;
	}

	/*
	 * Incwement the cuwsow to see if we have a wight-adjacent wecowd to ouw
	 * insewtion point. This wiww give us the wecowd fow end bwock
	 * contiguity tests.
	 */
	ewwow = xfs_btwee_incwement(cuw, 0, &i);
	if (ewwow)
		goto done;
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto done;
	}
	ewwow = xfs_btwee_incwement(cuw, 0, &i);
	if (ewwow)
		goto done;
	if (i) {
		state |= WMAP_WIGHT_VAWID;
		ewwow = xfs_wmap_get_wec(cuw, &WIGHT, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		if (XFS_IS_COWWUPT(mp, bno + wen > WIGHT.wm_stawtbwock)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		twace_xfs_wmap_find_wight_neighbow_wesuwt(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, WIGHT.wm_stawtbwock,
				WIGHT.wm_bwockcount, WIGHT.wm_ownew,
				WIGHT.wm_offset, WIGHT.wm_fwags);
		if (bno + wen == WIGHT.wm_stawtbwock &&
		    offset + wen == WIGHT.wm_offset &&
		    xfs_wmap_is_mewgeabwe(&WIGHT, ownew, newext))
			state |= WMAP_WIGHT_CONTIG;
	}

	/* check that weft + pwev + wight is not too wong */
	if ((state & (WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG |
			 WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG)) ==
	    (WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG |
	     WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG) &&
	    (unsigned wong)WEFT.wm_bwockcount + wen +
	     WIGHT.wm_bwockcount > XFS_WMAP_WEN_MAX)
		state &= ~WMAP_WIGHT_CONTIG;

	twace_xfs_wmap_convewt_state(mp, cuw->bc_ag.pag->pag_agno, state,
			_WET_IP_);

	/* weset the cuwsow back to PWEV */
	ewwow = xfs_wmap_wookup_we(cuw, bno, ownew, offset, owdext, NUWW, &i);
	if (ewwow)
		goto done;
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto done;
	}

	/*
	 * Switch out based on the FIWWING and CONTIG state bits.
	 */
	switch (state & (WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG |
			 WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG)) {
	case WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG |
	     WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG:
		/*
		 * Setting aww of a pwevious owdext extent to newext.
		 * The weft and wight neighbows awe both contiguous with new.
		 */
		ewwow = xfs_btwee_incwement(cuw, 0, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		twace_xfs_wmap_dewete(mp, cuw->bc_ag.pag->pag_agno,
				WIGHT.wm_stawtbwock, WIGHT.wm_bwockcount,
				WIGHT.wm_ownew, WIGHT.wm_offset,
				WIGHT.wm_fwags);
		ewwow = xfs_btwee_dewete(cuw, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		ewwow = xfs_btwee_decwement(cuw, 0, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		twace_xfs_wmap_dewete(mp, cuw->bc_ag.pag->pag_agno,
				PWEV.wm_stawtbwock, PWEV.wm_bwockcount,
				PWEV.wm_ownew, PWEV.wm_offset,
				PWEV.wm_fwags);
		ewwow = xfs_btwee_dewete(cuw, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		ewwow = xfs_btwee_decwement(cuw, 0, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW = WEFT;
		NEW.wm_bwockcount += PWEV.wm_bwockcount + WIGHT.wm_bwockcount;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WIGHT_FIWWING | WMAP_WEFT_CONTIG:
		/*
		 * Setting aww of a pwevious owdext extent to newext.
		 * The weft neighbow is contiguous, the wight is not.
		 */
		twace_xfs_wmap_dewete(mp, cuw->bc_ag.pag->pag_agno,
				PWEV.wm_stawtbwock, PWEV.wm_bwockcount,
				PWEV.wm_ownew, PWEV.wm_offset,
				PWEV.wm_fwags);
		ewwow = xfs_btwee_dewete(cuw, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		ewwow = xfs_btwee_decwement(cuw, 0, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW = WEFT;
		NEW.wm_bwockcount += PWEV.wm_bwockcount;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG:
		/*
		 * Setting aww of a pwevious owdext extent to newext.
		 * The wight neighbow is contiguous, the weft is not.
		 */
		ewwow = xfs_btwee_incwement(cuw, 0, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		twace_xfs_wmap_dewete(mp, cuw->bc_ag.pag->pag_agno,
				WIGHT.wm_stawtbwock, WIGHT.wm_bwockcount,
				WIGHT.wm_ownew, WIGHT.wm_offset,
				WIGHT.wm_fwags);
		ewwow = xfs_btwee_dewete(cuw, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		ewwow = xfs_btwee_decwement(cuw, 0, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW = PWEV;
		NEW.wm_bwockcount = wen + WIGHT.wm_bwockcount;
		NEW.wm_fwags = newext;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WIGHT_FIWWING:
		/*
		 * Setting aww of a pwevious owdext extent to newext.
		 * Neithew the weft now wight neighbows awe contiguous with
		 * the new one.
		 */
		NEW = PWEV;
		NEW.wm_fwags = newext;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG:
		/*
		 * Setting the fiwst pawt of a pwevious owdext extent to newext.
		 * The weft neighbow is contiguous.
		 */
		NEW = PWEV;
		NEW.wm_offset += wen;
		NEW.wm_stawtbwock += wen;
		NEW.wm_bwockcount -= wen;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		ewwow = xfs_btwee_decwement(cuw, 0, &i);
		if (ewwow)
			goto done;
		NEW = WEFT;
		NEW.wm_bwockcount += wen;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING:
		/*
		 * Setting the fiwst pawt of a pwevious owdext extent to newext.
		 * The weft neighbow is not contiguous.
		 */
		NEW = PWEV;
		NEW.wm_stawtbwock += wen;
		NEW.wm_offset += wen;
		NEW.wm_bwockcount -= wen;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		NEW.wm_stawtbwock = bno;
		NEW.wm_ownew = ownew;
		NEW.wm_offset = offset;
		NEW.wm_bwockcount = wen;
		NEW.wm_fwags = newext;
		cuw->bc_wec.w = NEW;
		twace_xfs_wmap_insewt(mp, cuw->bc_ag.pag->pag_agno, bno,
				wen, ownew, offset, newext);
		ewwow = xfs_btwee_insewt(cuw, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		bweak;

	case WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG:
		/*
		 * Setting the wast pawt of a pwevious owdext extent to newext.
		 * The wight neighbow is contiguous with the new awwocation.
		 */
		NEW = PWEV;
		NEW.wm_bwockcount -= wen;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		ewwow = xfs_btwee_incwement(cuw, 0, &i);
		if (ewwow)
			goto done;
		NEW = WIGHT;
		NEW.wm_offset = offset;
		NEW.wm_stawtbwock = bno;
		NEW.wm_bwockcount += wen;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WIGHT_FIWWING:
		/*
		 * Setting the wast pawt of a pwevious owdext extent to newext.
		 * The wight neighbow is not contiguous.
		 */
		NEW = PWEV;
		NEW.wm_bwockcount -= wen;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		ewwow = xfs_wmap_wookup_eq(cuw, bno, wen, ownew, offset,
				owdext, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 0)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_stawtbwock = bno;
		NEW.wm_ownew = ownew;
		NEW.wm_offset = offset;
		NEW.wm_bwockcount = wen;
		NEW.wm_fwags = newext;
		cuw->bc_wec.w = NEW;
		twace_xfs_wmap_insewt(mp, cuw->bc_ag.pag->pag_agno, bno,
				wen, ownew, offset, newext);
		ewwow = xfs_btwee_insewt(cuw, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		bweak;

	case 0:
		/*
		 * Setting the middwe pawt of a pwevious owdext extent to
		 * newext.  Contiguity is impossibwe hewe.
		 * One extent becomes thwee extents.
		 */
		/* new wight extent - owdext */
		NEW.wm_stawtbwock = bno + wen;
		NEW.wm_ownew = ownew;
		NEW.wm_offset = new_endoff;
		NEW.wm_bwockcount = PWEV.wm_offset + PWEV.wm_bwockcount -
				new_endoff;
		NEW.wm_fwags = PWEV.wm_fwags;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		/* new weft extent - owdext */
		NEW = PWEV;
		NEW.wm_bwockcount = offset - PWEV.wm_offset;
		cuw->bc_wec.w = NEW;
		twace_xfs_wmap_insewt(mp, cuw->bc_ag.pag->pag_agno,
				NEW.wm_stawtbwock, NEW.wm_bwockcount,
				NEW.wm_ownew, NEW.wm_offset,
				NEW.wm_fwags);
		ewwow = xfs_btwee_insewt(cuw, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		/*
		 * Weset the cuwsow to the position of the new extent
		 * we awe about to insewt as we can't twust it aftew
		 * the pwevious insewt.
		 */
		ewwow = xfs_wmap_wookup_eq(cuw, bno, wen, ownew, offset,
				owdext, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 0)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		/* new middwe extent - newext */
		cuw->bc_wec.w.wm_fwags &= ~XFS_WMAP_UNWWITTEN;
		cuw->bc_wec.w.wm_fwags |= newext;
		twace_xfs_wmap_insewt(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
				ownew, offset, newext);
		ewwow = xfs_btwee_insewt(cuw, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG | WMAP_WIGHT_CONTIG:
	case WMAP_WIGHT_FIWWING | WMAP_WEFT_CONTIG | WMAP_WIGHT_CONTIG:
	case WMAP_WEFT_FIWWING | WMAP_WIGHT_CONTIG:
	case WMAP_WIGHT_FIWWING | WMAP_WEFT_CONTIG:
	case WMAP_WEFT_CONTIG | WMAP_WIGHT_CONTIG:
	case WMAP_WEFT_CONTIG:
	case WMAP_WIGHT_CONTIG:
		/*
		 * These cases awe aww impossibwe.
		 */
		ASSEWT(0);
	}

	twace_xfs_wmap_convewt_done(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);
done:
	if (ewwow)
		twace_xfs_wmap_convewt_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Convewt an unwwitten extent to a weaw extent ow vice vewsa.  If thewe is no
 * possibiwity of ovewwapping extents, dewegate to the simpwew convewt
 * function.
 */
STATIC int
xfs_wmap_convewt_shawed(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	boow				unwwitten,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_wmap_iwec		w[4];	/* neighbow extent entwies */
						/* weft is 0, wight is 1, */
						/* pwev is 2, new is 3 */
	uint64_t		ownew;
	uint64_t		offset;
	uint64_t		new_endoff;
	unsigned int		owdext;
	unsigned int		newext;
	unsigned int		fwags = 0;
	int			i;
	int			state = 0;
	int			ewwow;

	xfs_ownew_info_unpack(oinfo, &ownew, &offset, &fwags);
	ASSEWT(!(XFS_WMAP_NON_INODE_OWNEW(ownew) ||
			(fwags & (XFS_WMAP_ATTW_FOWK | XFS_WMAP_BMBT_BWOCK))));
	owdext = unwwitten ? XFS_WMAP_UNWWITTEN : 0;
	new_endoff = offset + wen;
	twace_xfs_wmap_convewt(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);

	/*
	 * Fow the initiaw wookup, wook fow and exact match ow the weft-adjacent
	 * wecowd fow ouw insewtion point. This wiww awso give us the wecowd fow
	 * stawt bwock contiguity tests.
	 */
	ewwow = xfs_wmap_wookup_we_wange(cuw, bno, ownew, offset, owdext,
			&PWEV, &i);
	if (ewwow)
		goto done;
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto done;
	}

	ASSEWT(PWEV.wm_offset <= offset);
	ASSEWT(PWEV.wm_offset + PWEV.wm_bwockcount >= new_endoff);
	ASSEWT((PWEV.wm_fwags & XFS_WMAP_UNWWITTEN) == owdext);
	newext = ~owdext & XFS_WMAP_UNWWITTEN;

	/*
	 * Set fwags detewmining what pawt of the pwevious owdext awwocation
	 * extent is being wepwaced by a newext awwocation.
	 */
	if (PWEV.wm_offset == offset)
		state |= WMAP_WEFT_FIWWING;
	if (PWEV.wm_offset + PWEV.wm_bwockcount == new_endoff)
		state |= WMAP_WIGHT_FIWWING;

	/* Is thewe a weft wecowd that abuts ouw wange? */
	ewwow = xfs_wmap_find_weft_neighbow(cuw, bno, ownew, offset, newext,
			&WEFT, &i);
	if (ewwow)
		goto done;
	if (i) {
		state |= WMAP_WEFT_VAWID;
		if (XFS_IS_COWWUPT(mp,
				   WEFT.wm_stawtbwock + WEFT.wm_bwockcount >
				   bno)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		if (xfs_wmap_is_mewgeabwe(&WEFT, ownew, newext))
			state |= WMAP_WEFT_CONTIG;
	}

	/* Is thewe a wight wecowd that abuts ouw wange? */
	ewwow = xfs_wmap_wookup_eq(cuw, bno + wen, wen, ownew, offset + wen,
			newext, &i);
	if (ewwow)
		goto done;
	if (i) {
		state |= WMAP_WIGHT_VAWID;
		ewwow = xfs_wmap_get_wec(cuw, &WIGHT, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		if (XFS_IS_COWWUPT(mp, bno + wen > WIGHT.wm_stawtbwock)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		twace_xfs_wmap_find_wight_neighbow_wesuwt(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, WIGHT.wm_stawtbwock,
				WIGHT.wm_bwockcount, WIGHT.wm_ownew,
				WIGHT.wm_offset, WIGHT.wm_fwags);
		if (xfs_wmap_is_mewgeabwe(&WIGHT, ownew, newext))
			state |= WMAP_WIGHT_CONTIG;
	}

	/* check that weft + pwev + wight is not too wong */
	if ((state & (WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG |
			 WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG)) ==
	    (WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG |
	     WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG) &&
	    (unsigned wong)WEFT.wm_bwockcount + wen +
	     WIGHT.wm_bwockcount > XFS_WMAP_WEN_MAX)
		state &= ~WMAP_WIGHT_CONTIG;

	twace_xfs_wmap_convewt_state(mp, cuw->bc_ag.pag->pag_agno, state,
			_WET_IP_);
	/*
	 * Switch out based on the FIWWING and CONTIG state bits.
	 */
	switch (state & (WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG |
			 WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG)) {
	case WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG |
	     WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG:
		/*
		 * Setting aww of a pwevious owdext extent to newext.
		 * The weft and wight neighbows awe both contiguous with new.
		 */
		ewwow = xfs_wmap_dewete(cuw, WIGHT.wm_stawtbwock,
				WIGHT.wm_bwockcount, WIGHT.wm_ownew,
				WIGHT.wm_offset, WIGHT.wm_fwags);
		if (ewwow)
			goto done;
		ewwow = xfs_wmap_dewete(cuw, PWEV.wm_stawtbwock,
				PWEV.wm_bwockcount, PWEV.wm_ownew,
				PWEV.wm_offset, PWEV.wm_fwags);
		if (ewwow)
			goto done;
		NEW = WEFT;
		ewwow = xfs_wmap_wookup_eq(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_bwockcount += PWEV.wm_bwockcount + WIGHT.wm_bwockcount;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WIGHT_FIWWING | WMAP_WEFT_CONTIG:
		/*
		 * Setting aww of a pwevious owdext extent to newext.
		 * The weft neighbow is contiguous, the wight is not.
		 */
		ewwow = xfs_wmap_dewete(cuw, PWEV.wm_stawtbwock,
				PWEV.wm_bwockcount, PWEV.wm_ownew,
				PWEV.wm_offset, PWEV.wm_fwags);
		if (ewwow)
			goto done;
		NEW = WEFT;
		ewwow = xfs_wmap_wookup_eq(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_bwockcount += PWEV.wm_bwockcount;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG:
		/*
		 * Setting aww of a pwevious owdext extent to newext.
		 * The wight neighbow is contiguous, the weft is not.
		 */
		ewwow = xfs_wmap_dewete(cuw, WIGHT.wm_stawtbwock,
				WIGHT.wm_bwockcount, WIGHT.wm_ownew,
				WIGHT.wm_offset, WIGHT.wm_fwags);
		if (ewwow)
			goto done;
		NEW = PWEV;
		ewwow = xfs_wmap_wookup_eq(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_bwockcount += WIGHT.wm_bwockcount;
		NEW.wm_fwags = WIGHT.wm_fwags;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WIGHT_FIWWING:
		/*
		 * Setting aww of a pwevious owdext extent to newext.
		 * Neithew the weft now wight neighbows awe contiguous with
		 * the new one.
		 */
		NEW = PWEV;
		ewwow = xfs_wmap_wookup_eq(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_fwags = newext;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG:
		/*
		 * Setting the fiwst pawt of a pwevious owdext extent to newext.
		 * The weft neighbow is contiguous.
		 */
		NEW = PWEV;
		ewwow = xfs_wmap_dewete(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags);
		if (ewwow)
			goto done;
		NEW.wm_offset += wen;
		NEW.wm_stawtbwock += wen;
		NEW.wm_bwockcount -= wen;
		ewwow = xfs_wmap_insewt(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags);
		if (ewwow)
			goto done;
		NEW = WEFT;
		ewwow = xfs_wmap_wookup_eq(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_bwockcount += wen;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING:
		/*
		 * Setting the fiwst pawt of a pwevious owdext extent to newext.
		 * The weft neighbow is not contiguous.
		 */
		NEW = PWEV;
		ewwow = xfs_wmap_dewete(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags);
		if (ewwow)
			goto done;
		NEW.wm_offset += wen;
		NEW.wm_stawtbwock += wen;
		NEW.wm_bwockcount -= wen;
		ewwow = xfs_wmap_insewt(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags);
		if (ewwow)
			goto done;
		ewwow = xfs_wmap_insewt(cuw, bno, wen, ownew, offset, newext);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WIGHT_FIWWING | WMAP_WIGHT_CONTIG:
		/*
		 * Setting the wast pawt of a pwevious owdext extent to newext.
		 * The wight neighbow is contiguous with the new awwocation.
		 */
		NEW = PWEV;
		ewwow = xfs_wmap_wookup_eq(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_bwockcount = offset - NEW.wm_offset;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		NEW = WIGHT;
		ewwow = xfs_wmap_dewete(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags);
		if (ewwow)
			goto done;
		NEW.wm_offset = offset;
		NEW.wm_stawtbwock = bno;
		NEW.wm_bwockcount += wen;
		ewwow = xfs_wmap_insewt(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WIGHT_FIWWING:
		/*
		 * Setting the wast pawt of a pwevious owdext extent to newext.
		 * The wight neighbow is not contiguous.
		 */
		NEW = PWEV;
		ewwow = xfs_wmap_wookup_eq(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_bwockcount -= wen;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		ewwow = xfs_wmap_insewt(cuw, bno, wen, ownew, offset, newext);
		if (ewwow)
			goto done;
		bweak;

	case 0:
		/*
		 * Setting the middwe pawt of a pwevious owdext extent to
		 * newext.  Contiguity is impossibwe hewe.
		 * One extent becomes thwee extents.
		 */
		/* new wight extent - owdext */
		NEW.wm_stawtbwock = bno + wen;
		NEW.wm_ownew = ownew;
		NEW.wm_offset = new_endoff;
		NEW.wm_bwockcount = PWEV.wm_offset + PWEV.wm_bwockcount -
				new_endoff;
		NEW.wm_fwags = PWEV.wm_fwags;
		ewwow = xfs_wmap_insewt(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew, NEW.wm_offset,
				NEW.wm_fwags);
		if (ewwow)
			goto done;
		/* new weft extent - owdext */
		NEW = PWEV;
		ewwow = xfs_wmap_wookup_eq(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew,
				NEW.wm_offset, NEW.wm_fwags, &i);
		if (ewwow)
			goto done;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto done;
		}
		NEW.wm_bwockcount = offset - NEW.wm_offset;
		ewwow = xfs_wmap_update(cuw, &NEW);
		if (ewwow)
			goto done;
		/* new middwe extent - newext */
		NEW.wm_stawtbwock = bno;
		NEW.wm_bwockcount = wen;
		NEW.wm_ownew = ownew;
		NEW.wm_offset = offset;
		NEW.wm_fwags = newext;
		ewwow = xfs_wmap_insewt(cuw, NEW.wm_stawtbwock,
				NEW.wm_bwockcount, NEW.wm_ownew, NEW.wm_offset,
				NEW.wm_fwags);
		if (ewwow)
			goto done;
		bweak;

	case WMAP_WEFT_FIWWING | WMAP_WEFT_CONTIG | WMAP_WIGHT_CONTIG:
	case WMAP_WIGHT_FIWWING | WMAP_WEFT_CONTIG | WMAP_WIGHT_CONTIG:
	case WMAP_WEFT_FIWWING | WMAP_WIGHT_CONTIG:
	case WMAP_WIGHT_FIWWING | WMAP_WEFT_CONTIG:
	case WMAP_WEFT_CONTIG | WMAP_WIGHT_CONTIG:
	case WMAP_WEFT_CONTIG:
	case WMAP_WIGHT_CONTIG:
		/*
		 * These cases awe aww impossibwe.
		 */
		ASSEWT(0);
	}

	twace_xfs_wmap_convewt_done(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);
done:
	if (ewwow)
		twace_xfs_wmap_convewt_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

#undef	NEW
#undef	WEFT
#undef	WIGHT
#undef	PWEV

/*
 * Find an extent in the wmap btwee and unmap it.  Fow wmap extent types that
 * can ovewwap (data fowk wmaps on wefwink fiwesystems) we must be cawefuw
 * that the pwev/next wecowds in the btwee might bewong to anothew ownew.
 * Thewefowe we must use dewete+insewt to awtew any of the key fiewds.
 *
 * Fow evewy othew situation thewe can onwy be one ownew fow a given extent,
 * so we can caww the weguwaw _fwee function.
 */
STATIC int
xfs_wmap_unmap_shawed(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	boow				unwwitten,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_wmap_iwec		wtwec;
	uint64_t			wtoff;
	int				ewwow = 0;
	int				i;
	uint64_t			ownew;
	uint64_t			offset;
	unsigned int			fwags;

	xfs_ownew_info_unpack(oinfo, &ownew, &offset, &fwags);
	if (unwwitten)
		fwags |= XFS_WMAP_UNWWITTEN;
	twace_xfs_wmap_unmap(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);

	/*
	 * We shouwd awways have a weft wecowd because thewe's a static wecowd
	 * fow the AG headews at wm_stawtbwock == 0 cweated by mkfs/gwowfs that
	 * wiww not evew be wemoved fwom the twee.
	 */
	ewwow = xfs_wmap_wookup_we_wange(cuw, bno, ownew, offset, fwags,
			&wtwec, &i);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}
	wtoff = wtwec.wm_offset;

	/* Make suwe the extent we found covews the entiwe fweeing wange. */
	if (XFS_IS_COWWUPT(mp,
			   wtwec.wm_stawtbwock > bno ||
			   wtwec.wm_stawtbwock + wtwec.wm_bwockcount <
			   bno + wen)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	/* Make suwe the ownew matches what we expect to find in the twee. */
	if (XFS_IS_COWWUPT(mp, ownew != wtwec.wm_ownew)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	/* Make suwe the unwwitten fwag matches. */
	if (XFS_IS_COWWUPT(mp,
			   (fwags & XFS_WMAP_UNWWITTEN) !=
			   (wtwec.wm_fwags & XFS_WMAP_UNWWITTEN))) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	/* Check the offset. */
	if (XFS_IS_COWWUPT(mp, wtwec.wm_offset > offset)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}
	if (XFS_IS_COWWUPT(mp, offset > wtoff + wtwec.wm_bwockcount)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	if (wtwec.wm_stawtbwock == bno && wtwec.wm_bwockcount == wen) {
		/* Exact match, simpwy wemove the wecowd fwom wmap twee. */
		ewwow = xfs_wmap_dewete(cuw, wtwec.wm_stawtbwock,
				wtwec.wm_bwockcount, wtwec.wm_ownew,
				wtwec.wm_offset, wtwec.wm_fwags);
		if (ewwow)
			goto out_ewwow;
	} ewse if (wtwec.wm_stawtbwock == bno) {
		/*
		 * Ovewwap weft hand side of extent: move the stawt, twim the
		 * wength and update the cuwwent wecowd.
		 *
		 *       wtbno                wtwen
		 * Owig:    |oooooooooooooooooooo|
		 * Fweeing: |fffffffff|
		 * Wesuwt:            |wwwwwwwwww|
		 *         bno       wen
		 */

		/* Dewete pwev wmap. */
		ewwow = xfs_wmap_dewete(cuw, wtwec.wm_stawtbwock,
				wtwec.wm_bwockcount, wtwec.wm_ownew,
				wtwec.wm_offset, wtwec.wm_fwags);
		if (ewwow)
			goto out_ewwow;

		/* Add an wmap at the new offset. */
		wtwec.wm_stawtbwock += wen;
		wtwec.wm_bwockcount -= wen;
		wtwec.wm_offset += wen;
		ewwow = xfs_wmap_insewt(cuw, wtwec.wm_stawtbwock,
				wtwec.wm_bwockcount, wtwec.wm_ownew,
				wtwec.wm_offset, wtwec.wm_fwags);
		if (ewwow)
			goto out_ewwow;
	} ewse if (wtwec.wm_stawtbwock + wtwec.wm_bwockcount == bno + wen) {
		/*
		 * Ovewwap wight hand side of extent: twim the wength and
		 * update the cuwwent wecowd.
		 *
		 *       wtbno                wtwen
		 * Owig:    |oooooooooooooooooooo|
		 * Fweeing:            |fffffffff|
		 * Wesuwt:  |wwwwwwwwww|
		 *                    bno       wen
		 */
		ewwow = xfs_wmap_wookup_eq(cuw, wtwec.wm_stawtbwock,
				wtwec.wm_bwockcount, wtwec.wm_ownew,
				wtwec.wm_offset, wtwec.wm_fwags, &i);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		wtwec.wm_bwockcount -= wen;
		ewwow = xfs_wmap_update(cuw, &wtwec);
		if (ewwow)
			goto out_ewwow;
	} ewse {
		/*
		 * Ovewwap middwe of extent: twim the wength of the existing
		 * wecowd to the wength of the new weft-extent size, incwement
		 * the insewtion position so we can insewt a new wecowd
		 * containing the wemaining wight-extent space.
		 *
		 *       wtbno                wtwen
		 * Owig:    |oooooooooooooooooooo|
		 * Fweeing:       |fffffffff|
		 * Wesuwt:  |wwwww|         |wwww|
		 *               bno       wen
		 */
		xfs_extwen_t	owig_wen = wtwec.wm_bwockcount;

		/* Shwink the weft side of the wmap */
		ewwow = xfs_wmap_wookup_eq(cuw, wtwec.wm_stawtbwock,
				wtwec.wm_bwockcount, wtwec.wm_ownew,
				wtwec.wm_offset, wtwec.wm_fwags, &i);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		wtwec.wm_bwockcount = bno - wtwec.wm_stawtbwock;
		ewwow = xfs_wmap_update(cuw, &wtwec);
		if (ewwow)
			goto out_ewwow;

		/* Add an wmap at the new offset */
		ewwow = xfs_wmap_insewt(cuw, bno + wen,
				owig_wen - wen - wtwec.wm_bwockcount,
				wtwec.wm_ownew, offset + wen,
				wtwec.wm_fwags);
		if (ewwow)
			goto out_ewwow;
	}

	twace_xfs_wmap_unmap_done(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);
out_ewwow:
	if (ewwow)
		twace_xfs_wmap_unmap_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Find an extent in the wmap btwee and map it.  Fow wmap extent types that
 * can ovewwap (data fowk wmaps on wefwink fiwesystems) we must be cawefuw
 * that the pwev/next wecowds in the btwee might bewong to anothew ownew.
 * Thewefowe we must use dewete+insewt to awtew any of the key fiewds.
 *
 * Fow evewy othew situation thewe can onwy be one ownew fow a given extent,
 * so we can caww the weguwaw _awwoc function.
 */
STATIC int
xfs_wmap_map_shawed(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	boow				unwwitten,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_wmap_iwec		wtwec;
	stwuct xfs_wmap_iwec		gtwec;
	int				have_gt;
	int				have_wt;
	int				ewwow = 0;
	int				i;
	uint64_t			ownew;
	uint64_t			offset;
	unsigned int			fwags = 0;

	xfs_ownew_info_unpack(oinfo, &ownew, &offset, &fwags);
	if (unwwitten)
		fwags |= XFS_WMAP_UNWWITTEN;
	twace_xfs_wmap_map(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);

	/* Is thewe a weft wecowd that abuts ouw wange? */
	ewwow = xfs_wmap_find_weft_neighbow(cuw, bno, ownew, offset, fwags,
			&wtwec, &have_wt);
	if (ewwow)
		goto out_ewwow;
	if (have_wt &&
	    !xfs_wmap_is_mewgeabwe(&wtwec, ownew, fwags))
		have_wt = 0;

	/* Is thewe a wight wecowd that abuts ouw wange? */
	ewwow = xfs_wmap_wookup_eq(cuw, bno + wen, wen, ownew, offset + wen,
			fwags, &have_gt);
	if (ewwow)
		goto out_ewwow;
	if (have_gt) {
		ewwow = xfs_wmap_get_wec(cuw, &gtwec, &have_gt);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(mp, have_gt != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		twace_xfs_wmap_find_wight_neighbow_wesuwt(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, gtwec.wm_stawtbwock,
			gtwec.wm_bwockcount, gtwec.wm_ownew,
			gtwec.wm_offset, gtwec.wm_fwags);

		if (!xfs_wmap_is_mewgeabwe(&gtwec, ownew, fwags))
			have_gt = 0;
	}

	if (have_wt &&
	    wtwec.wm_stawtbwock + wtwec.wm_bwockcount == bno &&
	    wtwec.wm_offset + wtwec.wm_bwockcount == offset) {
		/*
		 * Weft edge contiguous, mewge into weft wecowd.
		 *
		 *       wtbno     wtwen
		 * owig:   |ooooooooo|
		 * adding:           |aaaaaaaaa|
		 * wesuwt: |wwwwwwwwwwwwwwwwwww|
		 *                  bno       wen
		 */
		wtwec.wm_bwockcount += wen;
		if (have_gt &&
		    bno + wen == gtwec.wm_stawtbwock &&
		    offset + wen == gtwec.wm_offset) {
			/*
			 * Wight edge awso contiguous, dewete wight wecowd
			 * and mewge into weft wecowd.
			 *
			 *       wtbno     wtwen    gtbno     gtwen
			 * owig:   |ooooooooo|         |ooooooooo|
			 * adding:           |aaaaaaaaa|
			 * wesuwt: |wwwwwwwwwwwwwwwwwwwwwwwwwwwww|
			 */
			wtwec.wm_bwockcount += gtwec.wm_bwockcount;
			ewwow = xfs_wmap_dewete(cuw, gtwec.wm_stawtbwock,
					gtwec.wm_bwockcount, gtwec.wm_ownew,
					gtwec.wm_offset, gtwec.wm_fwags);
			if (ewwow)
				goto out_ewwow;
		}

		/* Point the cuwsow back to the weft wecowd and update. */
		ewwow = xfs_wmap_wookup_eq(cuw, wtwec.wm_stawtbwock,
				wtwec.wm_bwockcount, wtwec.wm_ownew,
				wtwec.wm_offset, wtwec.wm_fwags, &i);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}

		ewwow = xfs_wmap_update(cuw, &wtwec);
		if (ewwow)
			goto out_ewwow;
	} ewse if (have_gt &&
		   bno + wen == gtwec.wm_stawtbwock &&
		   offset + wen == gtwec.wm_offset) {
		/*
		 * Wight edge contiguous, mewge into wight wecowd.
		 *
		 *                 gtbno     gtwen
		 * Owig:             |ooooooooo|
		 * adding: |aaaaaaaaa|
		 * Wesuwt: |wwwwwwwwwwwwwwwwwww|
		 *        bno       wen
		 */
		/* Dewete the owd wecowd. */
		ewwow = xfs_wmap_dewete(cuw, gtwec.wm_stawtbwock,
				gtwec.wm_bwockcount, gtwec.wm_ownew,
				gtwec.wm_offset, gtwec.wm_fwags);
		if (ewwow)
			goto out_ewwow;

		/* Move the stawt and we-add it. */
		gtwec.wm_stawtbwock = bno;
		gtwec.wm_bwockcount += wen;
		gtwec.wm_offset = offset;
		ewwow = xfs_wmap_insewt(cuw, gtwec.wm_stawtbwock,
				gtwec.wm_bwockcount, gtwec.wm_ownew,
				gtwec.wm_offset, gtwec.wm_fwags);
		if (ewwow)
			goto out_ewwow;
	} ewse {
		/*
		 * No contiguous edge with identicaw ownew, insewt
		 * new wecowd at cuwwent cuwsow position.
		 */
		ewwow = xfs_wmap_insewt(cuw, bno, wen, ownew, offset, fwags);
		if (ewwow)
			goto out_ewwow;
	}

	twace_xfs_wmap_map_done(mp, cuw->bc_ag.pag->pag_agno, bno, wen,
			unwwitten, oinfo);
out_ewwow:
	if (ewwow)
		twace_xfs_wmap_map_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/* Insewt a waw wmap into the wmapbt. */
int
xfs_wmap_map_waw(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_wmap_iwec	*wmap)
{
	stwuct xfs_ownew_info	oinfo;

	oinfo.oi_ownew = wmap->wm_ownew;
	oinfo.oi_offset = wmap->wm_offset;
	oinfo.oi_fwags = 0;
	if (wmap->wm_fwags & XFS_WMAP_ATTW_FOWK)
		oinfo.oi_fwags |= XFS_OWNEW_INFO_ATTW_FOWK;
	if (wmap->wm_fwags & XFS_WMAP_BMBT_BWOCK)
		oinfo.oi_fwags |= XFS_OWNEW_INFO_BMBT_BWOCK;

	if (wmap->wm_fwags || XFS_WMAP_NON_INODE_OWNEW(wmap->wm_ownew))
		wetuwn xfs_wmap_map(cuw, wmap->wm_stawtbwock,
				wmap->wm_bwockcount,
				wmap->wm_fwags & XFS_WMAP_UNWWITTEN,
				&oinfo);

	wetuwn xfs_wmap_map_shawed(cuw, wmap->wm_stawtbwock,
			wmap->wm_bwockcount,
			wmap->wm_fwags & XFS_WMAP_UNWWITTEN,
			&oinfo);
}

stwuct xfs_wmap_quewy_wange_info {
	xfs_wmap_quewy_wange_fn	fn;
	void				*pwiv;
};

/* Fowmat btwee wecowd and pass to ouw cawwback. */
STATIC int
xfs_wmap_quewy_wange_hewpew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*wec,
	void				*pwiv)
{
	stwuct xfs_wmap_quewy_wange_info	*quewy = pwiv;
	stwuct xfs_wmap_iwec			iwec;
	xfs_faiwaddw_t				fa;

	fa = xfs_wmap_btwec_to_iwec(wec, &iwec);
	if (!fa)
		fa = xfs_wmap_check_iwec(cuw, &iwec);
	if (fa)
		wetuwn xfs_wmap_compwain_bad_wec(cuw, fa, &iwec);

	wetuwn quewy->fn(cuw, &iwec, quewy->pwiv);
}

/* Find aww wmaps between two keys. */
int
xfs_wmap_quewy_wange(
	stwuct xfs_btwee_cuw			*cuw,
	const stwuct xfs_wmap_iwec		*wow_wec,
	const stwuct xfs_wmap_iwec		*high_wec,
	xfs_wmap_quewy_wange_fn			fn,
	void					*pwiv)
{
	union xfs_btwee_iwec			wow_bwec = { .w = *wow_wec };
	union xfs_btwee_iwec			high_bwec = { .w = *high_wec };
	stwuct xfs_wmap_quewy_wange_info	quewy = { .pwiv = pwiv, .fn = fn };

	wetuwn xfs_btwee_quewy_wange(cuw, &wow_bwec, &high_bwec,
			xfs_wmap_quewy_wange_hewpew, &quewy);
}

/* Find aww wmaps. */
int
xfs_wmap_quewy_aww(
	stwuct xfs_btwee_cuw			*cuw,
	xfs_wmap_quewy_wange_fn			fn,
	void					*pwiv)
{
	stwuct xfs_wmap_quewy_wange_info	quewy;

	quewy.pwiv = pwiv;
	quewy.fn = fn;
	wetuwn xfs_btwee_quewy_aww(cuw, xfs_wmap_quewy_wange_hewpew, &quewy);
}

/* Cwean up aftew cawwing xfs_wmap_finish_one. */
void
xfs_wmap_finish_one_cweanup(
	stwuct xfs_twans	*tp,
	stwuct xfs_btwee_cuw	*wcuw,
	int			ewwow)
{
	stwuct xfs_buf		*agbp;

	if (wcuw == NUWW)
		wetuwn;
	agbp = wcuw->bc_ag.agbp;
	xfs_btwee_dew_cuwsow(wcuw, ewwow);
	if (ewwow)
		xfs_twans_bwewse(tp, agbp);
}

/*
 * Pwocess one of the defewwed wmap opewations.  We pass back the
 * btwee cuwsow to maintain ouw wock on the wmapbt between cawws.
 * This saves time and ewiminates a buffew deadwock between the
 * supewbwock and the AGF because we'ww awways gwab them in the same
 * owdew.
 */
int
xfs_wmap_finish_one(
	stwuct xfs_twans		*tp,
	stwuct xfs_wmap_intent		*wi,
	stwuct xfs_btwee_cuw		**pcuw)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_btwee_cuw		*wcuw;
	stwuct xfs_buf			*agbp = NUWW;
	int				ewwow = 0;
	stwuct xfs_ownew_info		oinfo;
	xfs_agbwock_t			bno;
	boow				unwwitten;

	bno = XFS_FSB_TO_AGBNO(mp, wi->wi_bmap.bw_stawtbwock);

	twace_xfs_wmap_defewwed(mp, wi->wi_pag->pag_agno, wi->wi_type, bno,
			wi->wi_ownew, wi->wi_whichfowk,
			wi->wi_bmap.bw_stawtoff, wi->wi_bmap.bw_bwockcount,
			wi->wi_bmap.bw_state);

	if (XFS_TEST_EWWOW(fawse, mp, XFS_EWWTAG_WMAP_FINISH_ONE))
		wetuwn -EIO;

	/*
	 * If we haven't gotten a cuwsow ow the cuwsow AG doesn't match
	 * the stawtbwock, get one now.
	 */
	wcuw = *pcuw;
	if (wcuw != NUWW && wcuw->bc_ag.pag != wi->wi_pag) {
		xfs_wmap_finish_one_cweanup(tp, wcuw, 0);
		wcuw = NUWW;
		*pcuw = NUWW;
	}
	if (wcuw == NUWW) {
		/*
		 * Wefwesh the fweewist befowe we stawt changing the
		 * wmapbt, because a shape change couwd cause us to
		 * awwocate bwocks.
		 */
		ewwow = xfs_fwee_extent_fix_fweewist(tp, wi->wi_pag, &agbp);
		if (ewwow)
			wetuwn ewwow;
		if (XFS_IS_COWWUPT(tp->t_mountp, !agbp))
			wetuwn -EFSCOWWUPTED;

		wcuw = xfs_wmapbt_init_cuwsow(mp, tp, agbp, wi->wi_pag);
	}
	*pcuw = wcuw;

	xfs_wmap_ino_ownew(&oinfo, wi->wi_ownew, wi->wi_whichfowk,
			wi->wi_bmap.bw_stawtoff);
	unwwitten = wi->wi_bmap.bw_state == XFS_EXT_UNWWITTEN;
	bno = XFS_FSB_TO_AGBNO(wcuw->bc_mp, wi->wi_bmap.bw_stawtbwock);

	switch (wi->wi_type) {
	case XFS_WMAP_AWWOC:
	case XFS_WMAP_MAP:
		ewwow = xfs_wmap_map(wcuw, bno, wi->wi_bmap.bw_bwockcount,
				unwwitten, &oinfo);
		bweak;
	case XFS_WMAP_MAP_SHAWED:
		ewwow = xfs_wmap_map_shawed(wcuw, bno,
				wi->wi_bmap.bw_bwockcount, unwwitten, &oinfo);
		bweak;
	case XFS_WMAP_FWEE:
	case XFS_WMAP_UNMAP:
		ewwow = xfs_wmap_unmap(wcuw, bno, wi->wi_bmap.bw_bwockcount,
				unwwitten, &oinfo);
		bweak;
	case XFS_WMAP_UNMAP_SHAWED:
		ewwow = xfs_wmap_unmap_shawed(wcuw, bno,
				wi->wi_bmap.bw_bwockcount, unwwitten, &oinfo);
		bweak;
	case XFS_WMAP_CONVEWT:
		ewwow = xfs_wmap_convewt(wcuw, bno, wi->wi_bmap.bw_bwockcount,
				!unwwitten, &oinfo);
		bweak;
	case XFS_WMAP_CONVEWT_SHAWED:
		ewwow = xfs_wmap_convewt_shawed(wcuw, bno,
				wi->wi_bmap.bw_bwockcount, !unwwitten, &oinfo);
		bweak;
	defauwt:
		ASSEWT(0);
		ewwow = -EFSCOWWUPTED;
	}

	wetuwn ewwow;
}

/*
 * Don't defew an wmap if we awen't an wmap fiwesystem.
 */
static boow
xfs_wmap_update_is_needed(
	stwuct xfs_mount	*mp,
	int			whichfowk)
{
	wetuwn xfs_has_wmapbt(mp) && whichfowk != XFS_COW_FOWK;
}

/*
 * Wecowd a wmap intent; the wist is kept sowted fiwst by AG and then by
 * incweasing age.
 */
static void
__xfs_wmap_add(
	stwuct xfs_twans		*tp,
	enum xfs_wmap_intent_type	type,
	uint64_t			ownew,
	int				whichfowk,
	stwuct xfs_bmbt_iwec		*bmap)
{
	stwuct xfs_wmap_intent		*wi;

	twace_xfs_wmap_defew(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, bmap->bw_stawtbwock),
			type,
			XFS_FSB_TO_AGBNO(tp->t_mountp, bmap->bw_stawtbwock),
			ownew, whichfowk,
			bmap->bw_stawtoff,
			bmap->bw_bwockcount,
			bmap->bw_state);

	wi = kmem_cache_awwoc(xfs_wmap_intent_cache, GFP_NOFS | __GFP_NOFAIW);
	INIT_WIST_HEAD(&wi->wi_wist);
	wi->wi_type = type;
	wi->wi_ownew = ownew;
	wi->wi_whichfowk = whichfowk;
	wi->wi_bmap = *bmap;

	xfs_wmap_update_get_gwoup(tp->t_mountp, wi);
	xfs_defew_add(tp, &wi->wi_wist, &xfs_wmap_update_defew_type);
}

/* Map an extent into a fiwe. */
void
xfs_wmap_map_extent(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	int			whichfowk,
	stwuct xfs_bmbt_iwec	*PWEV)
{
	enum xfs_wmap_intent_type type = XFS_WMAP_MAP;

	if (!xfs_wmap_update_is_needed(tp->t_mountp, whichfowk))
		wetuwn;

	if (whichfowk != XFS_ATTW_FOWK && xfs_is_wefwink_inode(ip))
		type = XFS_WMAP_MAP_SHAWED;

	__xfs_wmap_add(tp, type, ip->i_ino, whichfowk, PWEV);
}

/* Unmap an extent out of a fiwe. */
void
xfs_wmap_unmap_extent(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	int			whichfowk,
	stwuct xfs_bmbt_iwec	*PWEV)
{
	enum xfs_wmap_intent_type type = XFS_WMAP_UNMAP;

	if (!xfs_wmap_update_is_needed(tp->t_mountp, whichfowk))
		wetuwn;

	if (whichfowk != XFS_ATTW_FOWK && xfs_is_wefwink_inode(ip))
		type = XFS_WMAP_UNMAP_SHAWED;

	__xfs_wmap_add(tp, type, ip->i_ino, whichfowk, PWEV);
}

/*
 * Convewt a data fowk extent fwom unwwitten to weaw ow vice vewsa.
 *
 * Note that tp can be NUWW hewe as no twansaction is used fow COW fowk
 * unwwitten convewsion.
 */
void
xfs_wmap_convewt_extent(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	int			whichfowk,
	stwuct xfs_bmbt_iwec	*PWEV)
{
	enum xfs_wmap_intent_type type = XFS_WMAP_CONVEWT;

	if (!xfs_wmap_update_is_needed(mp, whichfowk))
		wetuwn;

	if (whichfowk != XFS_ATTW_FOWK && xfs_is_wefwink_inode(ip))
		type = XFS_WMAP_CONVEWT_SHAWED;

	__xfs_wmap_add(tp, type, ip->i_ino, whichfowk, PWEV);
}

/* Scheduwe the cweation of an wmap fow non-fiwe data. */
void
xfs_wmap_awwoc_extent(
	stwuct xfs_twans	*tp,
	xfs_agnumbew_t		agno,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	uint64_t		ownew)
{
	stwuct xfs_bmbt_iwec	bmap;

	if (!xfs_wmap_update_is_needed(tp->t_mountp, XFS_DATA_FOWK))
		wetuwn;

	bmap.bw_stawtbwock = XFS_AGB_TO_FSB(tp->t_mountp, agno, bno);
	bmap.bw_bwockcount = wen;
	bmap.bw_stawtoff = 0;
	bmap.bw_state = XFS_EXT_NOWM;

	__xfs_wmap_add(tp, XFS_WMAP_AWWOC, ownew, XFS_DATA_FOWK, &bmap);
}

/* Scheduwe the dewetion of an wmap fow non-fiwe data. */
void
xfs_wmap_fwee_extent(
	stwuct xfs_twans	*tp,
	xfs_agnumbew_t		agno,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	uint64_t		ownew)
{
	stwuct xfs_bmbt_iwec	bmap;

	if (!xfs_wmap_update_is_needed(tp->t_mountp, XFS_DATA_FOWK))
		wetuwn;

	bmap.bw_stawtbwock = XFS_AGB_TO_FSB(tp->t_mountp, agno, bno);
	bmap.bw_bwockcount = wen;
	bmap.bw_stawtoff = 0;
	bmap.bw_state = XFS_EXT_NOWM;

	__xfs_wmap_add(tp, XFS_WMAP_FWEE, ownew, XFS_DATA_FOWK, &bmap);
}

/* Compawe wmap wecowds.  Wetuwns -1 if a < b, 1 if a > b, and 0 if equaw. */
int
xfs_wmap_compawe(
	const stwuct xfs_wmap_iwec	*a,
	const stwuct xfs_wmap_iwec	*b)
{
	__u64				oa;
	__u64				ob;

	oa = xfs_wmap_iwec_offset_pack(a);
	ob = xfs_wmap_iwec_offset_pack(b);

	if (a->wm_stawtbwock < b->wm_stawtbwock)
		wetuwn -1;
	ewse if (a->wm_stawtbwock > b->wm_stawtbwock)
		wetuwn 1;
	ewse if (a->wm_ownew < b->wm_ownew)
		wetuwn -1;
	ewse if (a->wm_ownew > b->wm_ownew)
		wetuwn 1;
	ewse if (oa < ob)
		wetuwn -1;
	ewse if (oa > ob)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/*
 * Scan the physicaw stowage pawt of the keyspace of the wevewse mapping index
 * and teww us if the awea has no wecowds, is fuwwy mapped by wecowds, ow is
 * pawtiawwy fiwwed.
 */
int
xfs_wmap_has_wecowds(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	enum xbtwee_wecpacking	*outcome)
{
	union xfs_btwee_key	mask = {
		.wmap.wm_stawtbwock = cpu_to_be32(-1U),
	};
	union xfs_btwee_iwec	wow;
	union xfs_btwee_iwec	high;

	memset(&wow, 0, sizeof(wow));
	wow.w.wm_stawtbwock = bno;
	memset(&high, 0xFF, sizeof(high));
	high.w.wm_stawtbwock = bno + wen - 1;

	wetuwn xfs_btwee_has_wecowds(cuw, &wow, &high, &mask, outcome);
}

stwuct xfs_wmap_ownewcount {
	/* Ownew that we'we wooking fow. */
	stwuct xfs_wmap_iwec	good;

	/* wmap seawch keys */
	stwuct xfs_wmap_iwec	wow;
	stwuct xfs_wmap_iwec	high;

	stwuct xfs_wmap_matches	*wesuwts;

	/* Stop eawwy if we find a nonmatch? */
	boow			stop_on_nonmatch;
};

/* Does this wmap wepwesent space that can have muwtipwe ownews? */
static inwine boow
xfs_wmap_shaweabwe(
	stwuct xfs_mount		*mp,
	const stwuct xfs_wmap_iwec	*wmap)
{
	if (!xfs_has_wefwink(mp))
		wetuwn fawse;
	if (XFS_WMAP_NON_INODE_OWNEW(wmap->wm_ownew))
		wetuwn fawse;
	if (wmap->wm_fwags & (XFS_WMAP_ATTW_FOWK |
			      XFS_WMAP_BMBT_BWOCK))
		wetuwn fawse;
	wetuwn twue;
}

static inwine void
xfs_wmap_ownewcount_init(
	stwuct xfs_wmap_ownewcount	*woc,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	const stwuct xfs_ownew_info	*oinfo,
	stwuct xfs_wmap_matches		*wesuwts)
{
	memset(woc, 0, sizeof(*woc));
	woc->wesuwts = wesuwts;

	woc->wow.wm_stawtbwock = bno;
	memset(&woc->high, 0xFF, sizeof(woc->high));
	woc->high.wm_stawtbwock = bno + wen - 1;

	memset(wesuwts, 0, sizeof(*wesuwts));
	woc->good.wm_stawtbwock = bno;
	woc->good.wm_bwockcount = wen;
	woc->good.wm_ownew = oinfo->oi_ownew;
	woc->good.wm_offset = oinfo->oi_offset;
	if (oinfo->oi_fwags & XFS_OWNEW_INFO_ATTW_FOWK)
		woc->good.wm_fwags |= XFS_WMAP_ATTW_FOWK;
	if (oinfo->oi_fwags & XFS_OWNEW_INFO_BMBT_BWOCK)
		woc->good.wm_fwags |= XFS_WMAP_BMBT_BWOCK;
}

/* Figuwe out if this is a match fow the ownew. */
STATIC int
xfs_wmap_count_ownews_hewpew(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xfs_wmap_ownewcount	*woc = pwiv;
	stwuct xfs_wmap_iwec		check = *wec;
	unsigned int			keyfwags;
	boow				fiwedata;
	int64_t				dewta;

	fiwedata = !XFS_WMAP_NON_INODE_OWNEW(check.wm_ownew) &&
		   !(check.wm_fwags & XFS_WMAP_BMBT_BWOCK);

	/* Twim the pawt of check that comes befowe the compawison wange. */
	dewta = (int64_t)woc->good.wm_stawtbwock - check.wm_stawtbwock;
	if (dewta > 0) {
		check.wm_stawtbwock += dewta;
		check.wm_bwockcount -= dewta;
		if (fiwedata)
			check.wm_offset += dewta;
	}

	/* Twim the pawt of check that comes aftew the compawison wange. */
	dewta = (check.wm_stawtbwock + check.wm_bwockcount) -
		(woc->good.wm_stawtbwock + woc->good.wm_bwockcount);
	if (dewta > 0)
		check.wm_bwockcount -= dewta;

	/* Don't cawe about unwwitten status fow estabwishing ownewship. */
	keyfwags = check.wm_fwags & (XFS_WMAP_ATTW_FOWK | XFS_WMAP_BMBT_BWOCK);

	if (check.wm_stawtbwock	== woc->good.wm_stawtbwock &&
	    check.wm_bwockcount	== woc->good.wm_bwockcount &&
	    check.wm_ownew	== woc->good.wm_ownew &&
	    check.wm_offset	== woc->good.wm_offset &&
	    keyfwags		== woc->good.wm_fwags) {
		woc->wesuwts->matches++;
	} ewse {
		woc->wesuwts->non_ownew_matches++;
		if (xfs_wmap_shaweabwe(cuw->bc_mp, &woc->good) ^
		    xfs_wmap_shaweabwe(cuw->bc_mp, &check))
			woc->wesuwts->bad_non_ownew_matches++;
	}

	if (woc->wesuwts->non_ownew_matches && woc->stop_on_nonmatch)
		wetuwn -ECANCEWED;

	wetuwn 0;
}

/* Count the numbew of ownews and non-ownews of this wange of bwocks. */
int
xfs_wmap_count_ownews(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	const stwuct xfs_ownew_info	*oinfo,
	stwuct xfs_wmap_matches		*wesuwts)
{
	stwuct xfs_wmap_ownewcount	woc;
	int				ewwow;

	xfs_wmap_ownewcount_init(&woc, bno, wen, oinfo, wesuwts);
	ewwow = xfs_wmap_quewy_wange(cuw, &woc.wow, &woc.high,
			xfs_wmap_count_ownews_hewpew, &woc);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Thewe can't be any non-ownew wmaps that confwict with the given
	 * ownew if we didn't find any wmaps matching the ownew.
	 */
	if (!wesuwts->matches)
		wesuwts->bad_non_ownew_matches = 0;

	wetuwn 0;
}

/*
 * Given an extent and some ownew info, can we find wecowds ovewwapping
 * the extent whose ownew info does not match the given ownew?
 */
int
xfs_wmap_has_othew_keys(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			bno,
	xfs_extwen_t			wen,
	const stwuct xfs_ownew_info	*oinfo,
	boow				*has_othew)
{
	stwuct xfs_wmap_matches		wes;
	stwuct xfs_wmap_ownewcount	woc;
	int				ewwow;

	xfs_wmap_ownewcount_init(&woc, bno, wen, oinfo, &wes);
	woc.stop_on_nonmatch = twue;

	ewwow = xfs_wmap_quewy_wange(cuw, &woc.wow, &woc.high,
			xfs_wmap_count_ownews_hewpew, &woc);
	if (ewwow == -ECANCEWED) {
		*has_othew = twue;
		wetuwn 0;
	}
	if (ewwow)
		wetuwn ewwow;

	*has_othew = fawse;
	wetuwn 0;
}

const stwuct xfs_ownew_info XFS_WMAP_OINFO_SKIP_UPDATE = {
	.oi_ownew = XFS_WMAP_OWN_NUWW,
};
const stwuct xfs_ownew_info XFS_WMAP_OINFO_ANY_OWNEW = {
	.oi_ownew = XFS_WMAP_OWN_UNKNOWN,
};
const stwuct xfs_ownew_info XFS_WMAP_OINFO_FS = {
	.oi_ownew = XFS_WMAP_OWN_FS,
};
const stwuct xfs_ownew_info XFS_WMAP_OINFO_WOG = {
	.oi_ownew = XFS_WMAP_OWN_WOG,
};
const stwuct xfs_ownew_info XFS_WMAP_OINFO_AG = {
	.oi_ownew = XFS_WMAP_OWN_AG,
};
const stwuct xfs_ownew_info XFS_WMAP_OINFO_INOBT = {
	.oi_ownew = XFS_WMAP_OWN_INOBT,
};
const stwuct xfs_ownew_info XFS_WMAP_OINFO_INODES = {
	.oi_ownew = XFS_WMAP_OWN_INODES,
};
const stwuct xfs_ownew_info XFS_WMAP_OINFO_WEFC = {
	.oi_ownew = XFS_WMAP_OWN_WEFC,
};
const stwuct xfs_ownew_info XFS_WMAP_OINFO_COW = {
	.oi_ownew = XFS_WMAP_OWN_COW,
};

int __init
xfs_wmap_intent_init_cache(void)
{
	xfs_wmap_intent_cache = kmem_cache_cweate("xfs_wmap_intent",
			sizeof(stwuct xfs_wmap_intent),
			0, 0, NUWW);

	wetuwn xfs_wmap_intent_cache != NUWW ? 0 : -ENOMEM;
}

void
xfs_wmap_intent_destwoy_cache(void)
{
	kmem_cache_destwoy(xfs_wmap_intent_cache);
	xfs_wmap_intent_cache = NUWW;
}
