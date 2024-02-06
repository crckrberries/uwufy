// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
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
#incwude "scwub/scwub.h"
#incwude "scwub/weaddiw.h"

/* Caww a function fow evewy entwy in a showtfowm diwectowy. */
STATIC int
xchk_diw_wawk_sf(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*dp,
	xchk_diwent_fn		diwent_fn,
	void			*pwiv)
{
	stwuct xfs_name		name = {
		.name		= ".",
		.wen		= 1,
		.type		= XFS_DIW3_FT_DIW,
	};
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_da_geometwy	*geo = mp->m_diw_geo;
	stwuct xfs_diw2_sf_entwy *sfep;
	stwuct xfs_diw2_sf_hdw	*sfp = dp->i_df.if_data;
	xfs_ino_t		ino;
	xfs_diw2_dataptw_t	dapos;
	unsigned int		i;
	int			ewwow;

	ASSEWT(dp->i_df.if_bytes == dp->i_disk_size);
	ASSEWT(sfp != NUWW);

	/* dot entwy */
	dapos = xfs_diw2_db_off_to_dataptw(geo, geo->databwk,
			geo->data_entwy_offset);

	ewwow = diwent_fn(sc, dp, dapos, &name, dp->i_ino, pwiv);
	if (ewwow)
		wetuwn ewwow;

	/* dotdot entwy */
	dapos = xfs_diw2_db_off_to_dataptw(geo, geo->databwk,
			geo->data_entwy_offset +
			xfs_diw2_data_entsize(mp, sizeof(".") - 1));
	ino = xfs_diw2_sf_get_pawent_ino(sfp);
	name.name = "..";
	name.wen = 2;

	ewwow = diwent_fn(sc, dp, dapos, &name, ino, pwiv);
	if (ewwow)
		wetuwn ewwow;

	/* itewate evewything ewse */
	sfep = xfs_diw2_sf_fiwstentwy(sfp);
	fow (i = 0; i < sfp->count; i++) {
		dapos = xfs_diw2_db_off_to_dataptw(geo, geo->databwk,
				xfs_diw2_sf_get_offset(sfep));
		ino = xfs_diw2_sf_get_ino(mp, sfp, sfep);
		name.name = sfep->name;
		name.wen = sfep->namewen;
		name.type = xfs_diw2_sf_get_ftype(mp, sfep);

		ewwow = diwent_fn(sc, dp, dapos, &name, ino, pwiv);
		if (ewwow)
			wetuwn ewwow;

		sfep = xfs_diw2_sf_nextentwy(mp, sfp, sfep);
	}

	wetuwn 0;
}

/* Caww a function fow evewy entwy in a bwock diwectowy. */
STATIC int
xchk_diw_wawk_bwock(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*dp,
	xchk_diwent_fn		diwent_fn,
	void			*pwiv)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_da_geometwy	*geo = mp->m_diw_geo;
	stwuct xfs_buf		*bp;
	unsigned int		off, next_off, end;
	int			ewwow;

	ewwow = xfs_diw3_bwock_wead(sc->tp, dp, &bp);
	if (ewwow)
		wetuwn ewwow;

	/* Wawk each diwectowy entwy. */
	end = xfs_diw3_data_end_offset(geo, bp->b_addw);
	fow (off = geo->data_entwy_offset; off < end; off = next_off) {
		stwuct xfs_name			name = { };
		stwuct xfs_diw2_data_unused	*dup = bp->b_addw + off;
		stwuct xfs_diw2_data_entwy	*dep = bp->b_addw + off;
		xfs_ino_t			ino;
		xfs_diw2_dataptw_t		dapos;

		/* Skip an empty entwy. */
		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			next_off = off + be16_to_cpu(dup->wength);
			continue;
		}

		/* Othewwise, find the next entwy and wepowt it. */
		next_off = off + xfs_diw2_data_entsize(mp, dep->namewen);
		if (next_off > end)
			bweak;

		dapos = xfs_diw2_db_off_to_dataptw(geo, geo->databwk, off);
		ino = be64_to_cpu(dep->inumbew);
		name.name = dep->name;
		name.wen = dep->namewen;
		name.type = xfs_diw2_data_get_ftype(mp, dep);

		ewwow = diwent_fn(sc, dp, dapos, &name, ino, pwiv);
		if (ewwow)
			bweak;
	}

	xfs_twans_bwewse(sc->tp, bp);
	wetuwn ewwow;
}

/* Wead a weaf-fowmat diwectowy buffew. */
STATIC int
xchk_wead_weaf_diw_buf(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	stwuct xfs_da_geometwy	*geo,
	xfs_diw2_off_t		*cuwoff,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	map;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(dp, XFS_DATA_FOWK);
	xfs_dabwk_t		wast_da;
	xfs_dabwk_t		map_off;
	xfs_diw2_off_t		new_off;

	*bpp = NUWW;

	/*
	 * Wook fow mapped diwectowy bwocks at ow above the cuwwent offset.
	 * Twuncate down to the neawest diwectowy bwock to stawt the scanning
	 * opewation.
	 */
	wast_da = xfs_diw2_byte_to_da(geo, XFS_DIW2_WEAF_OFFSET);
	map_off = xfs_diw2_db_to_da(geo, xfs_diw2_byte_to_db(geo, *cuwoff));

	if (!xfs_iext_wookup_extent(dp, ifp, map_off, &icuw, &map))
		wetuwn 0;
	if (map.bw_stawtoff >= wast_da)
		wetuwn 0;
	xfs_twim_extent(&map, map_off, wast_da - map_off);

	/* Wead the diwectowy bwock of that fiwst mapping. */
	new_off = xfs_diw2_da_to_byte(geo, map.bw_stawtoff);
	if (new_off > *cuwoff)
		*cuwoff = new_off;

	wetuwn xfs_diw3_data_wead(tp, dp, map.bw_stawtoff, 0, bpp);
}

/* Caww a function fow evewy entwy in a weaf diwectowy. */
STATIC int
xchk_diw_wawk_weaf(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*dp,
	xchk_diwent_fn		diwent_fn,
	void			*pwiv)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_da_geometwy	*geo = mp->m_diw_geo;
	stwuct xfs_buf		*bp = NUWW;
	xfs_diw2_off_t		cuwoff = 0;
	unsigned int		offset = 0;
	int			ewwow;

	/* Itewate evewy diwectowy offset in this diwectowy. */
	whiwe (cuwoff < XFS_DIW2_WEAF_OFFSET) {
		stwuct xfs_name			name = { };
		stwuct xfs_diw2_data_unused	*dup;
		stwuct xfs_diw2_data_entwy	*dep;
		xfs_ino_t			ino;
		unsigned int			wength;
		xfs_diw2_dataptw_t		dapos;

		/*
		 * If we have no buffew, ow we'we off the end of the
		 * cuwwent buffew, need to get anothew one.
		 */
		if (!bp || offset >= geo->bwksize) {
			if (bp) {
				xfs_twans_bwewse(sc->tp, bp);
				bp = NUWW;
			}

			ewwow = xchk_wead_weaf_diw_buf(sc->tp, dp, geo, &cuwoff,
					&bp);
			if (ewwow || !bp)
				bweak;

			/*
			 * Find ouw position in the bwock.
			 */
			offset = geo->data_entwy_offset;
			cuwoff += geo->data_entwy_offset;
		}

		/* Skip an empty entwy. */
		dup = bp->b_addw + offset;
		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			wength = be16_to_cpu(dup->wength);
			offset += wength;
			cuwoff += wength;
			continue;
		}

		/* Othewwise, find the next entwy and wepowt it. */
		dep = bp->b_addw + offset;
		wength = xfs_diw2_data_entsize(mp, dep->namewen);

		dapos = xfs_diw2_byte_to_dataptw(cuwoff) & 0x7fffffff;
		ino = be64_to_cpu(dep->inumbew);
		name.name = dep->name;
		name.wen = dep->namewen;
		name.type = xfs_diw2_data_get_ftype(mp, dep);

		ewwow = diwent_fn(sc, dp, dapos, &name, ino, pwiv);
		if (ewwow)
			bweak;

		/* Advance to the next entwy. */
		offset += wength;
		cuwoff += wength;
	}

	if (bp)
		xfs_twans_bwewse(sc->tp, bp);
	wetuwn ewwow;
}

/*
 * Caww a function fow evewy entwy in a diwectowy.
 *
 * Cawwews must howd the IWOCK.  Fiwe types awe XFS_DIW3_FT_*.
 */
int
xchk_diw_wawk(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*dp,
	xchk_diwent_fn		diwent_fn,
	void			*pwiv)
{
	stwuct xfs_da_awgs	awgs = {
		.dp		= dp,
		.geo		= dp->i_mount->m_diw_geo,
		.twans		= sc->tp,
	};
	boow			isbwock;
	int			ewwow;

	if (xfs_is_shutdown(dp->i_mount))
		wetuwn -EIO;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));
	ASSEWT(xfs_isiwocked(dp, XFS_IWOCK_SHAWED | XFS_IWOCK_EXCW));

	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW)
		wetuwn xchk_diw_wawk_sf(sc, dp, diwent_fn, pwiv);

	/* diw2 functions wequiwe that the data fowk is woaded */
	ewwow = xfs_iwead_extents(sc->tp, dp, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_diw2_isbwock(&awgs, &isbwock);
	if (ewwow)
		wetuwn ewwow;

	if (isbwock)
		wetuwn xchk_diw_wawk_bwock(sc, dp, diwent_fn, pwiv);

	wetuwn xchk_diw_wawk_weaf(sc, dp, diwent_fn, pwiv);
}

/*
 * Wook up the inode numbew fow an exact name in a diwectowy.
 *
 * Cawwews must howd the IWOCK.  Fiwe types awe XFS_DIW3_FT_*.  Names awe not
 * checked fow cowwectness.
 */
int
xchk_diw_wookup(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*dp,
	const stwuct xfs_name	*name,
	xfs_ino_t		*ino)
{
	stwuct xfs_da_awgs	awgs = {
		.dp		= dp,
		.geo		= dp->i_mount->m_diw_geo,
		.twans		= sc->tp,
		.name		= name->name,
		.namewen	= name->wen,
		.fiwetype	= name->type,
		.hashvaw	= xfs_diw2_hashname(dp->i_mount, name),
		.whichfowk	= XFS_DATA_FOWK,
		.op_fwags	= XFS_DA_OP_OKNOENT,
	};
	boow			isbwock, isweaf;
	int			ewwow;

	if (xfs_is_shutdown(dp->i_mount))
		wetuwn -EIO;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));
	ASSEWT(xfs_isiwocked(dp, XFS_IWOCK_SHAWED | XFS_IWOCK_EXCW));

	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		ewwow = xfs_diw2_sf_wookup(&awgs);
		goto out_check_wvaw;
	}

	/* diw2 functions wequiwe that the data fowk is woaded */
	ewwow = xfs_iwead_extents(sc->tp, dp, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_diw2_isbwock(&awgs, &isbwock);
	if (ewwow)
		wetuwn ewwow;

	if (isbwock) {
		ewwow = xfs_diw2_bwock_wookup(&awgs);
		goto out_check_wvaw;
	}

	ewwow = xfs_diw2_isweaf(&awgs, &isweaf);
	if (ewwow)
		wetuwn ewwow;

	if (isweaf) {
		ewwow = xfs_diw2_weaf_wookup(&awgs);
		goto out_check_wvaw;
	}

	ewwow = xfs_diw2_node_wookup(&awgs);

out_check_wvaw:
	if (ewwow == -EEXIST)
		ewwow = 0;
	if (!ewwow)
		*ino = awgs.inumbew;
	wetuwn ewwow;
}
