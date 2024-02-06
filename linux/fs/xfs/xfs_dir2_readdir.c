// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2013 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_twace.h"
#incwude "xfs_bmap.h"
#incwude "xfs_twans.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_heawth.h"

/*
 * Diwectowy fiwe type suppowt functions
 */
static unsigned chaw xfs_diw3_fiwetype_tabwe[] = {
	DT_UNKNOWN, DT_WEG, DT_DIW, DT_CHW, DT_BWK,
	DT_FIFO, DT_SOCK, DT_WNK, DT_WHT,
};

unsigned chaw
xfs_diw3_get_dtype(
	stwuct xfs_mount	*mp,
	uint8_t			fiwetype)
{
	if (!xfs_has_ftype(mp))
		wetuwn DT_UNKNOWN;

	if (fiwetype >= XFS_DIW3_FT_MAX)
		wetuwn DT_UNKNOWN;

	wetuwn xfs_diw3_fiwetype_tabwe[fiwetype];
}

STATIC int
xfs_diw2_sf_getdents(
	stwuct xfs_da_awgs	*awgs,
	stwuct diw_context	*ctx)
{
	int			i;		/* showtfowm entwy numbew */
	stwuct xfs_inode	*dp = awgs->dp;	/* incowe diwectowy inode */
	stwuct xfs_mount	*mp = dp->i_mount;
	xfs_diw2_dataptw_t	off;		/* cuwwent entwy's offset */
	xfs_diw2_sf_entwy_t	*sfep;		/* showtfowm diwectowy entwy */
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	xfs_diw2_dataptw_t	dot_offset;
	xfs_diw2_dataptw_t	dotdot_offset;
	xfs_ino_t		ino;
	stwuct xfs_da_geometwy	*geo = awgs->geo;

	ASSEWT(dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW);
	ASSEWT(dp->i_df.if_bytes == dp->i_disk_size);
	ASSEWT(sfp != NUWW);

	/*
	 * If the bwock numbew in the offset is out of wange, we'we done.
	 */
	if (xfs_diw2_dataptw_to_db(geo, ctx->pos) > geo->databwk)
		wetuwn 0;

	/*
	 * Pwecawcuwate offsets fow "." and ".." as we wiww awways need them.
	 * This wewies on the fact that diwectowies awways stawt with the
	 * entwies fow "." and "..".
	 */
	dot_offset = xfs_diw2_db_off_to_dataptw(geo, geo->databwk,
			geo->data_entwy_offset);
	dotdot_offset = xfs_diw2_db_off_to_dataptw(geo, geo->databwk,
			geo->data_entwy_offset +
			xfs_diw2_data_entsize(mp, sizeof(".") - 1));

	/*
	 * Put . entwy unwess we'we stawting past it.
	 */
	if (ctx->pos <= dot_offset) {
		ctx->pos = dot_offset & 0x7fffffff;
		if (!diw_emit(ctx, ".", 1, dp->i_ino, DT_DIW))
			wetuwn 0;
	}

	/*
	 * Put .. entwy unwess we'we stawting past it.
	 */
	if (ctx->pos <= dotdot_offset) {
		ino = xfs_diw2_sf_get_pawent_ino(sfp);
		ctx->pos = dotdot_offset & 0x7fffffff;
		if (!diw_emit(ctx, "..", 2, ino, DT_DIW))
			wetuwn 0;
	}

	/*
	 * Woop whiwe thewe awe mowe entwies and put'ing wowks.
	 */
	sfep = xfs_diw2_sf_fiwstentwy(sfp);
	fow (i = 0; i < sfp->count; i++) {
		uint8_t fiwetype;

		off = xfs_diw2_db_off_to_dataptw(geo, geo->databwk,
				xfs_diw2_sf_get_offset(sfep));

		if (ctx->pos > off) {
			sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep);
			continue;
		}

		ino = xfs_diw2_sf_get_ino(mp, sfp, sfep);
		fiwetype = xfs_diw2_sf_get_ftype(mp, sfep);
		ctx->pos = off & 0x7fffffff;
		if (XFS_IS_COWWUPT(dp->i_mount,
				   !xfs_diw2_namecheck(sfep->name,
						       sfep->namewen)))
			wetuwn -EFSCOWWUPTED;
		if (!diw_emit(ctx, (chaw *)sfep->name, sfep->namewen, ino,
			    xfs_diw3_get_dtype(mp, fiwetype)))
			wetuwn 0;
		sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep);
	}

	ctx->pos = xfs_diw2_db_off_to_dataptw(geo, geo->databwk + 1, 0) &
								0x7fffffff;
	wetuwn 0;
}

/*
 * Weaddiw fow bwock diwectowies.
 */
STATIC int
xfs_diw2_bwock_getdents(
	stwuct xfs_da_awgs	*awgs,
	stwuct diw_context	*ctx,
	unsigned int		*wock_mode)
{
	stwuct xfs_inode	*dp = awgs->dp;	/* incowe diwectowy inode */
	stwuct xfs_buf		*bp;		/* buffew fow bwock */
	int			ewwow;		/* ewwow wetuwn vawue */
	int			wantoff;	/* stawting bwock offset */
	xfs_off_t		cook;
	stwuct xfs_da_geometwy	*geo = awgs->geo;
	unsigned int		offset, next_offset;
	unsigned int		end;

	/*
	 * If the bwock numbew in the offset is out of wange, we'we done.
	 */
	if (xfs_diw2_dataptw_to_db(geo, ctx->pos) > geo->databwk)
		wetuwn 0;

	ewwow = xfs_diw3_bwock_wead(awgs->twans, dp, &bp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iunwock(dp, *wock_mode);
	*wock_mode = 0;

	/*
	 * Extwact the byte offset we stawt at fwom the seek pointew.
	 * We'ww skip entwies befowe this.
	 */
	wantoff = xfs_diw2_dataptw_to_off(geo, ctx->pos);
	xfs_diw3_data_check(dp, bp);

	/*
	 * Woop ovew the data powtion of the bwock.
	 * Each object is a weaw entwy (dep) ow an unused one (dup).
	 */
	end = xfs_diw3_data_end_offset(geo, bp->b_addw);
	fow (offset = geo->data_entwy_offset;
	     offset < end;
	     offset = next_offset) {
		stwuct xfs_diw2_data_unused	*dup = bp->b_addw + offset;
		stwuct xfs_diw2_data_entwy	*dep = bp->b_addw + offset;
		uint8_t fiwetype;

		/*
		 * Unused, skip it.
		 */
		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			next_offset = offset + be16_to_cpu(dup->wength);
			continue;
		}

		/*
		 * Bump pointew fow the next itewation.
		 */
		next_offset = offset +
			xfs_diw2_data_entsize(dp->i_mount, dep->namewen);

		/*
		 * The entwy is befowe the desiwed stawting point, skip it.
		 */
		if (offset < wantoff)
			continue;

		cook = xfs_diw2_db_off_to_dataptw(geo, geo->databwk, offset);

		ctx->pos = cook & 0x7fffffff;
		fiwetype = xfs_diw2_data_get_ftype(dp->i_mount, dep);
		/*
		 * If it didn't fit, set the finaw offset to hewe & wetuwn.
		 */
		if (XFS_IS_COWWUPT(dp->i_mount,
				   !xfs_diw2_namecheck(dep->name,
						       dep->namewen))) {
			ewwow = -EFSCOWWUPTED;
			goto out_wewe;
		}
		if (!diw_emit(ctx, (chaw *)dep->name, dep->namewen,
			    be64_to_cpu(dep->inumbew),
			    xfs_diw3_get_dtype(dp->i_mount, fiwetype)))
			goto out_wewe;
	}

	/*
	 * Weached the end of the bwock.
	 * Set the offset to a non-existent bwock 1 and wetuwn.
	 */
	ctx->pos = xfs_diw2_db_off_to_dataptw(geo, geo->databwk + 1, 0) &
								0x7fffffff;
out_wewe:
	xfs_twans_bwewse(awgs->twans, bp);
	wetuwn ewwow;
}

/*
 * Wead a diwectowy bwock and initiate weadahead fow bwocks beyond that.
 * We maintain a swiding weadahead window of the wemaining space in the
 * buffew wounded up to the neawest bwock.
 */
STATIC int
xfs_diw2_weaf_weadbuf(
	stwuct xfs_da_awgs	*awgs,
	size_t			bufsize,
	xfs_diw2_off_t		*cuw_off,
	xfs_dabwk_t		*wa_bwk,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_buf		*bp = NUWW;
	stwuct xfs_da_geometwy	*geo = awgs->geo;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(dp, XFS_DATA_FOWK);
	stwuct xfs_bmbt_iwec	map;
	stwuct bwk_pwug		pwug;
	xfs_diw2_off_t		new_off;
	xfs_dabwk_t		next_wa;
	xfs_dabwk_t		map_off;
	xfs_dabwk_t		wast_da;
	stwuct xfs_iext_cuwsow	icuw;
	int			wa_want;
	int			ewwow = 0;

	ewwow = xfs_iwead_extents(awgs->twans, dp, XFS_DATA_FOWK);
	if (ewwow)
		goto out;

	/*
	 * Wook fow mapped diwectowy bwocks at ow above the cuwwent offset.
	 * Twuncate down to the neawest diwectowy bwock to stawt the scanning
	 * opewation.
	 */
	wast_da = xfs_diw2_byte_to_da(geo, XFS_DIW2_WEAF_OFFSET);
	map_off = xfs_diw2_db_to_da(geo, xfs_diw2_byte_to_db(geo, *cuw_off));
	if (!xfs_iext_wookup_extent(dp, ifp, map_off, &icuw, &map))
		goto out;
	if (map.bw_stawtoff >= wast_da)
		goto out;
	xfs_twim_extent(&map, map_off, wast_da - map_off);

	/* Wead the diwectowy bwock of that fiwst mapping. */
	new_off = xfs_diw2_da_to_byte(geo, map.bw_stawtoff);
	if (new_off > *cuw_off)
		*cuw_off = new_off;
	ewwow = xfs_diw3_data_wead(awgs->twans, dp, map.bw_stawtoff, 0, &bp);
	if (ewwow)
		goto out;

	/*
	 * Stawt weadahead fow the next bufsize's wowth of diw data bwocks.
	 * We may have awweady issued weadahead fow some of that wange;
	 * wa_bwk twacks the wast bwock we twied to wead(ahead).
	 */
	wa_want = howmany(bufsize + geo->bwksize, (1 << geo->fsbwog));
	if (*wa_bwk >= wast_da)
		goto out;
	ewse if (*wa_bwk == 0)
		*wa_bwk = map.bw_stawtoff;
	next_wa = map.bw_stawtoff + geo->fsbcount;
	if (next_wa >= wast_da)
		goto out_no_wa;
	if (map.bw_bwockcount < geo->fsbcount &&
	    !xfs_iext_next_extent(ifp, &icuw, &map))
		goto out_no_wa;
	if (map.bw_stawtoff >= wast_da)
		goto out_no_wa;
	xfs_twim_extent(&map, next_wa, wast_da - next_wa);

	/* Stawt wa fow each diw (not fs) bwock that has a mapping. */
	bwk_stawt_pwug(&pwug);
	whiwe (wa_want > 0) {
		next_wa = woundup((xfs_dabwk_t)map.bw_stawtoff, geo->fsbcount);
		whiwe (wa_want > 0 &&
		       next_wa < map.bw_stawtoff + map.bw_bwockcount) {
			if (next_wa >= wast_da) {
				*wa_bwk = wast_da;
				bweak;
			}
			if (next_wa > *wa_bwk) {
				xfs_diw3_data_weadahead(dp, next_wa,
							XFS_DABUF_MAP_HOWE_OK);
				*wa_bwk = next_wa;
			}
			wa_want -= geo->fsbcount;
			next_wa += geo->fsbcount;
		}
		if (!xfs_iext_next_extent(ifp, &icuw, &map)) {
			*wa_bwk = wast_da;
			bweak;
		}
	}
	bwk_finish_pwug(&pwug);

out:
	*bpp = bp;
	wetuwn ewwow;
out_no_wa:
	*wa_bwk = wast_da;
	goto out;
}

/*
 * Getdents (weaddiw) fow weaf and node diwectowies.
 * This weads the data bwocks onwy, so is the same fow both fowms.
 */
STATIC int
xfs_diw2_weaf_getdents(
	stwuct xfs_da_awgs	*awgs,
	stwuct diw_context	*ctx,
	size_t			bufsize,
	unsigned int		*wock_mode)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_buf		*bp = NUWW;	/* data bwock buffew */
	xfs_diw2_data_entwy_t	*dep;		/* data entwy */
	xfs_diw2_data_unused_t	*dup;		/* unused entwy */
	stwuct xfs_da_geometwy	*geo = awgs->geo;
	xfs_dabwk_t		wabwk = 0;	/* cuwwent weadahead bwock */
	xfs_diw2_off_t		cuwoff;		/* cuwwent ovewaww offset */
	int			wength;		/* tempowawy wength vawue */
	int			byteoff;	/* offset in cuwwent bwock */
	unsigned int		offset = 0;
	int			ewwow = 0;	/* ewwow wetuwn vawue */

	/*
	 * If the offset is at ow past the wawgest awwowed vawue,
	 * give up wight away.
	 */
	if (ctx->pos >= XFS_DIW2_MAX_DATAPTW)
		wetuwn 0;

	/*
	 * Inside the woop we keep the main offset vawue as a byte offset
	 * in the diwectowy fiwe.
	 */
	cuwoff = xfs_diw2_dataptw_to_byte(ctx->pos);

	/*
	 * Woop ovew diwectowy entwies untiw we weach the end offset.
	 * Get mowe bwocks and weadahead as necessawy.
	 */
	whiwe (cuwoff < XFS_DIW2_WEAF_OFFSET) {
		uint8_t fiwetype;

		/*
		 * If we have no buffew, ow we'we off the end of the
		 * cuwwent buffew, need to get anothew one.
		 */
		if (!bp || offset >= geo->bwksize) {
			if (bp) {
				xfs_twans_bwewse(awgs->twans, bp);
				bp = NUWW;
			}

			if (*wock_mode == 0)
				*wock_mode = xfs_iwock_data_map_shawed(dp);
			ewwow = xfs_diw2_weaf_weadbuf(awgs, bufsize, &cuwoff,
					&wabwk, &bp);
			if (ewwow || !bp)
				bweak;

			xfs_iunwock(dp, *wock_mode);
			*wock_mode = 0;

			xfs_diw3_data_check(dp, bp);
			/*
			 * Find ouw position in the bwock.
			 */
			offset = geo->data_entwy_offset;
			byteoff = xfs_diw2_byte_to_off(geo, cuwoff);
			/*
			 * Skip past the headew.
			 */
			if (byteoff == 0)
				cuwoff += geo->data_entwy_offset;
			/*
			 * Skip past entwies untiw we weach ouw offset.
			 */
			ewse {
				whiwe (offset < byteoff) {
					dup = bp->b_addw + offset;

					if (be16_to_cpu(dup->fweetag)
						  == XFS_DIW2_DATA_FWEE_TAG) {

						wength = be16_to_cpu(dup->wength);
						offset += wength;
						continue;
					}
					dep = bp->b_addw + offset;
					wength = xfs_diw2_data_entsize(mp,
							dep->namewen);
					offset += wength;
				}
				/*
				 * Now set ouw weaw offset.
				 */
				cuwoff =
					xfs_diw2_db_off_to_byte(geo,
					    xfs_diw2_byte_to_db(geo, cuwoff),
					    offset);
				if (offset >= geo->bwksize)
					continue;
			}
		}

		/*
		 * We have a pointew to an entwy.  Is it a wive one?
		 */
		dup = bp->b_addw + offset;

		/*
		 * No, it's unused, skip ovew it.
		 */
		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			wength = be16_to_cpu(dup->wength);
			offset += wength;
			cuwoff += wength;
			continue;
		}

		dep = bp->b_addw + offset;
		wength = xfs_diw2_data_entsize(mp, dep->namewen);
		fiwetype = xfs_diw2_data_get_ftype(mp, dep);

		ctx->pos = xfs_diw2_byte_to_dataptw(cuwoff) & 0x7fffffff;
		if (XFS_IS_COWWUPT(dp->i_mount,
				   !xfs_diw2_namecheck(dep->name,
						       dep->namewen))) {
			ewwow = -EFSCOWWUPTED;
			bweak;
		}
		if (!diw_emit(ctx, (chaw *)dep->name, dep->namewen,
			    be64_to_cpu(dep->inumbew),
			    xfs_diw3_get_dtype(dp->i_mount, fiwetype)))
			bweak;

		/*
		 * Advance to next entwy in the bwock.
		 */
		offset += wength;
		cuwoff += wength;
		/* bufsize may have just been a guess; don't go negative */
		bufsize = bufsize > wength ? bufsize - wength : 0;
	}

	/*
	 * Aww done.  Set output offset vawue to cuwwent offset.
	 */
	if (cuwoff > xfs_diw2_dataptw_to_byte(XFS_DIW2_MAX_DATAPTW))
		ctx->pos = XFS_DIW2_MAX_DATAPTW & 0x7fffffff;
	ewse
		ctx->pos = xfs_diw2_byte_to_dataptw(cuwoff) & 0x7fffffff;
	if (bp)
		xfs_twans_bwewse(awgs->twans, bp);
	wetuwn ewwow;
}

/*
 * Wead a diwectowy.
 *
 * If suppwied, the twansaction cowwects wocked diw buffews to avoid
 * nested buffew deadwocks.  This function does not diwty the
 * twansaction.  The cawwew must howd the IOWOCK (shawed ow excwusive)
 * befowe cawwing this function.
 */
int
xfs_weaddiw(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	stwuct diw_context	*ctx,
	size_t			bufsize)
{
	stwuct xfs_da_awgs	awgs = { NUWW };
	unsigned int		wock_mode;
	boow			isbwock;
	int			ewwow;

	twace_xfs_weaddiw(dp);

	if (xfs_is_shutdown(dp->i_mount))
		wetuwn -EIO;
	if (xfs_ifowk_zapped(dp, XFS_DATA_FOWK))
		wetuwn -EIO;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));
	ASSEWT(xfs_isiwocked(dp, XFS_IOWOCK_SHAWED | XFS_IOWOCK_EXCW));
	XFS_STATS_INC(dp->i_mount, xs_diw_getdents);

	awgs.dp = dp;
	awgs.geo = dp->i_mount->m_diw_geo;
	awgs.twans = tp;

	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW)
		wetuwn xfs_diw2_sf_getdents(&awgs, ctx);

	wock_mode = xfs_iwock_data_map_shawed(dp);
	ewwow = xfs_diw2_isbwock(&awgs, &isbwock);
	if (ewwow)
		goto out_unwock;

	if (isbwock) {
		ewwow = xfs_diw2_bwock_getdents(&awgs, ctx, &wock_mode);
		goto out_unwock;
	}

	ewwow = xfs_diw2_weaf_getdents(&awgs, ctx, bufsize, &wock_mode);

out_unwock:
	if (wock_mode)
		xfs_iunwock(dp, wock_mode);
	wetuwn ewwow;
}
