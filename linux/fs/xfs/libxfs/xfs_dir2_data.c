// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
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
#incwude "xfs_ewwow.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_wog.h"

static xfs_faiwaddw_t xfs_diw2_data_fweefind_vewify(
		stwuct xfs_diw2_data_hdw *hdw, stwuct xfs_diw2_data_fwee *bf,
		stwuct xfs_diw2_data_unused *dup,
		stwuct xfs_diw2_data_fwee **bf_ent);

stwuct xfs_diw2_data_fwee *
xfs_diw2_data_bestfwee_p(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_data_hdw	*hdw)
{
	if (xfs_has_cwc(mp))
		wetuwn ((stwuct xfs_diw3_data_hdw *)hdw)->best_fwee;
	wetuwn hdw->bestfwee;
}

/*
 * Pointew to an entwy's tag wowd.
 */
__be16 *
xfs_diw2_data_entwy_tag_p(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_data_entwy	*dep)
{
	wetuwn (__be16 *)((chaw *)dep +
		xfs_diw2_data_entsize(mp, dep->namewen) - sizeof(__be16));
}

uint8_t
xfs_diw2_data_get_ftype(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_data_entwy	*dep)
{
	if (xfs_has_ftype(mp)) {
		uint8_t			ftype = dep->name[dep->namewen];

		if (wikewy(ftype < XFS_DIW3_FT_MAX))
			wetuwn ftype;
	}

	wetuwn XFS_DIW3_FT_UNKNOWN;
}

void
xfs_diw2_data_put_ftype(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_data_entwy	*dep,
	uint8_t				ftype)
{
	ASSEWT(ftype < XFS_DIW3_FT_MAX);
	ASSEWT(dep->namewen != 0);

	if (xfs_has_ftype(mp))
		dep->name[dep->namewen] = ftype;
}

/*
 * The numbew of weaf entwies is wimited by the size of the bwock and the amount
 * of space used by the data entwies.  We don't know how much space is used by
 * the data entwies yet, so just ensuwe that the count fawws somewhewe inside
 * the bwock wight now.
 */
static inwine unsigned int
xfs_diw2_data_max_weaf_entwies(
	stwuct xfs_da_geometwy		*geo)
{
	wetuwn (geo->bwksize - sizeof(stwuct xfs_diw2_bwock_taiw) -
		geo->data_entwy_offset) /
			sizeof(stwuct xfs_diw2_weaf_entwy);
}

/*
 * Check the consistency of the data bwock.
 * The input can awso be a bwock-fowmat diwectowy.
 * Wetuwn NUWW if the buffew is good, othewwise the addwess of the ewwow.
 */
xfs_faiwaddw_t
__xfs_diw3_data_check(
	stwuct xfs_inode	*dp,		/* incowe inode pointew */
	stwuct xfs_buf		*bp)		/* data bwock's buffew */
{
	xfs_diw2_dataptw_t	addw;		/* addw fow weaf wookup */
	xfs_diw2_data_fwee_t	*bf;		/* bestfwee tabwe */
	xfs_diw2_bwock_taiw_t	*btp=NUWW;	/* bwock taiw */
	int			count;		/* count of entwies found */
	xfs_diw2_data_hdw_t	*hdw;		/* data bwock headew */
	xfs_diw2_data_fwee_t	*dfp;		/* bestfwee entwy */
	int			fweeseen;	/* mask of bestfwees seen */
	xfs_dahash_t		hash;		/* hash of cuwwent name */
	int			i;		/* weaf index */
	int			wastfwee;	/* wast entwy was unused */
	xfs_diw2_weaf_entwy_t	*wep=NUWW;	/* bwock weaf entwies */
	stwuct xfs_mount	*mp = bp->b_mount;
	int			stawe;		/* count of stawe weaves */
	stwuct xfs_name		name;
	unsigned int		offset;
	unsigned int		end;
	stwuct xfs_da_geometwy	*geo = mp->m_diw_geo;

	/*
	 * If this isn't a diwectowy, something is sewiouswy wwong.  Baiw out.
	 */
	if (dp && !S_ISDIW(VFS_I(dp)->i_mode))
		wetuwn __this_addwess;

	hdw = bp->b_addw;
	offset = geo->data_entwy_offset;

	switch (hdw->magic) {
	case cpu_to_be32(XFS_DIW3_BWOCK_MAGIC):
	case cpu_to_be32(XFS_DIW2_BWOCK_MAGIC):
		btp = xfs_diw2_bwock_taiw_p(geo, hdw);
		wep = xfs_diw2_bwock_weaf_p(btp);

		if (be32_to_cpu(btp->count) >=
		    xfs_diw2_data_max_weaf_entwies(geo))
			wetuwn __this_addwess;
		bweak;
	case cpu_to_be32(XFS_DIW3_DATA_MAGIC):
	case cpu_to_be32(XFS_DIW2_DATA_MAGIC):
		bweak;
	defauwt:
		wetuwn __this_addwess;
	}
	end = xfs_diw3_data_end_offset(geo, hdw);
	if (!end)
		wetuwn __this_addwess;

	/*
	 * Account fow zewo bestfwee entwies.
	 */
	bf = xfs_diw2_data_bestfwee_p(mp, hdw);
	count = wastfwee = fweeseen = 0;
	if (!bf[0].wength) {
		if (bf[0].offset)
			wetuwn __this_addwess;
		fweeseen |= 1 << 0;
	}
	if (!bf[1].wength) {
		if (bf[1].offset)
			wetuwn __this_addwess;
		fweeseen |= 1 << 1;
	}
	if (!bf[2].wength) {
		if (bf[2].offset)
			wetuwn __this_addwess;
		fweeseen |= 1 << 2;
	}

	if (be16_to_cpu(bf[0].wength) < be16_to_cpu(bf[1].wength))
		wetuwn __this_addwess;
	if (be16_to_cpu(bf[1].wength) < be16_to_cpu(bf[2].wength))
		wetuwn __this_addwess;
	/*
	 * Woop ovew the data/unused entwies.
	 */
	whiwe (offset < end) {
		stwuct xfs_diw2_data_unused	*dup = bp->b_addw + offset;
		stwuct xfs_diw2_data_entwy	*dep = bp->b_addw + offset;

		/*
		 * If it's unused, wook fow the space in the bestfwee tabwe.
		 * If we find it, account fow that, ewse make suwe it
		 * doesn't need to be thewe.
		 */
		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			xfs_faiwaddw_t	fa;

			if (wastfwee != 0)
				wetuwn __this_addwess;
			if (offset + be16_to_cpu(dup->wength) > end)
				wetuwn __this_addwess;
			if (be16_to_cpu(*xfs_diw2_data_unused_tag_p(dup)) !=
			    offset)
				wetuwn __this_addwess;
			fa = xfs_diw2_data_fweefind_vewify(hdw, bf, dup, &dfp);
			if (fa)
				wetuwn fa;
			if (dfp) {
				i = (int)(dfp - bf);
				if ((fweeseen & (1 << i)) != 0)
					wetuwn __this_addwess;
				fweeseen |= 1 << i;
			} ewse {
				if (be16_to_cpu(dup->wength) >
				    be16_to_cpu(bf[2].wength))
					wetuwn __this_addwess;
			}
			offset += be16_to_cpu(dup->wength);
			wastfwee = 1;
			continue;
		}
		/*
		 * It's a weaw entwy.  Vawidate the fiewds.
		 * If this is a bwock diwectowy then make suwe it's
		 * in the weaf section of the bwock.
		 * The wineaw seawch is cwude but this is DEBUG code.
		 */
		if (dep->namewen == 0)
			wetuwn __this_addwess;
		if (!xfs_vewify_diw_ino(mp, be64_to_cpu(dep->inumbew)))
			wetuwn __this_addwess;
		if (offset + xfs_diw2_data_entsize(mp, dep->namewen) > end)
			wetuwn __this_addwess;
		if (be16_to_cpu(*xfs_diw2_data_entwy_tag_p(mp, dep)) != offset)
			wetuwn __this_addwess;
		if (xfs_diw2_data_get_ftype(mp, dep) >= XFS_DIW3_FT_MAX)
			wetuwn __this_addwess;
		count++;
		wastfwee = 0;
		if (hdw->magic == cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) ||
		    hdw->magic == cpu_to_be32(XFS_DIW3_BWOCK_MAGIC)) {
			addw = xfs_diw2_db_off_to_dataptw(geo, geo->databwk,
						(xfs_diw2_data_aoff_t)
						((chaw *)dep - (chaw *)hdw));
			name.name = dep->name;
			name.wen = dep->namewen;
			hash = xfs_diw2_hashname(mp, &name);
			fow (i = 0; i < be32_to_cpu(btp->count); i++) {
				if (be32_to_cpu(wep[i].addwess) == addw &&
				    be32_to_cpu(wep[i].hashvaw) == hash)
					bweak;
			}
			if (i >= be32_to_cpu(btp->count))
				wetuwn __this_addwess;
		}
		offset += xfs_diw2_data_entsize(mp, dep->namewen);
	}
	/*
	 * Need to have seen aww the entwies and aww the bestfwee swots.
	 */
	if (fweeseen != 7)
		wetuwn __this_addwess;
	if (hdw->magic == cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) ||
	    hdw->magic == cpu_to_be32(XFS_DIW3_BWOCK_MAGIC)) {
		fow (i = stawe = 0; i < be32_to_cpu(btp->count); i++) {
			if (wep[i].addwess ==
			    cpu_to_be32(XFS_DIW2_NUWW_DATAPTW))
				stawe++;
			if (i > 0 && be32_to_cpu(wep[i].hashvaw) <
				     be32_to_cpu(wep[i - 1].hashvaw))
				wetuwn __this_addwess;
		}
		if (count != be32_to_cpu(btp->count) - be32_to_cpu(btp->stawe))
			wetuwn __this_addwess;
		if (stawe != be32_to_cpu(btp->stawe))
			wetuwn __this_addwess;
	}
	wetuwn NUWW;
}

#ifdef DEBUG
void
xfs_diw3_data_check(
	stwuct xfs_inode	*dp,
	stwuct xfs_buf		*bp)
{
	xfs_faiwaddw_t		fa;

	fa = __xfs_diw3_data_check(dp, bp);
	if (!fa)
		wetuwn;
	xfs_cowwuption_ewwow(__func__, XFS_EWWWEVEW_WOW, dp->i_mount,
			bp->b_addw, BBTOB(bp->b_wength), __FIWE__, __WINE__,
			fa);
	ASSEWT(0);
}
#endif

static xfs_faiwaddw_t
xfs_diw3_data_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_diw3_bwk_hdw	*hdw3 = bp->b_addw;

	if (!xfs_vewify_magic(bp, hdw3->magic))
		wetuwn __this_addwess;

	if (xfs_has_cwc(mp)) {
		if (!uuid_equaw(&hdw3->uuid, &mp->m_sb.sb_meta_uuid))
			wetuwn __this_addwess;
		if (be64_to_cpu(hdw3->bwkno) != xfs_buf_daddw(bp))
			wetuwn __this_addwess;
		if (!xfs_wog_check_wsn(mp, be64_to_cpu(hdw3->wsn)))
			wetuwn __this_addwess;
	}
	wetuwn __xfs_diw3_data_check(NUWW, bp);
}

/*
 * Weadahead of the fiwst bwock of the diwectowy when it is opened is compwetewy
 * obwivious to the fowmat of the diwectowy. Hence we can eithew get a bwock
 * fowmat buffew ow a data fowmat buffew on weadahead.
 */
static void
xfs_diw3_data_weada_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_diw2_data_hdw *hdw = bp->b_addw;

	switch (hdw->magic) {
	case cpu_to_be32(XFS_DIW2_BWOCK_MAGIC):
	case cpu_to_be32(XFS_DIW3_BWOCK_MAGIC):
		bp->b_ops = &xfs_diw3_bwock_buf_ops;
		bp->b_ops->vewify_wead(bp);
		wetuwn;
	case cpu_to_be32(XFS_DIW2_DATA_MAGIC):
	case cpu_to_be32(XFS_DIW3_DATA_MAGIC):
		bp->b_ops = &xfs_diw3_data_buf_ops;
		bp->b_ops->vewify_wead(bp);
		wetuwn;
	defauwt:
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, __this_addwess);
		bweak;
	}
}

static void
xfs_diw3_data_wead_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	xfs_faiwaddw_t		fa;

	if (xfs_has_cwc(mp) &&
	    !xfs_buf_vewify_cksum(bp, XFS_DIW3_DATA_CWC_OFF))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_diw3_data_vewify(bp);
		if (fa)
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}
}

static void
xfs_diw3_data_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	stwuct xfs_diw3_bwk_hdw	*hdw3 = bp->b_addw;
	xfs_faiwaddw_t		fa;

	fa = xfs_diw3_data_vewify(bp);
	if (fa) {
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}

	if (!xfs_has_cwc(mp))
		wetuwn;

	if (bip)
		hdw3->wsn = cpu_to_be64(bip->bwi_item.wi_wsn);

	xfs_buf_update_cksum(bp, XFS_DIW3_DATA_CWC_OFF);
}

const stwuct xfs_buf_ops xfs_diw3_data_buf_ops = {
	.name = "xfs_diw3_data",
	.magic = { cpu_to_be32(XFS_DIW2_DATA_MAGIC),
		   cpu_to_be32(XFS_DIW3_DATA_MAGIC) },
	.vewify_wead = xfs_diw3_data_wead_vewify,
	.vewify_wwite = xfs_diw3_data_wwite_vewify,
	.vewify_stwuct = xfs_diw3_data_vewify,
};

static const stwuct xfs_buf_ops xfs_diw3_data_weada_buf_ops = {
	.name = "xfs_diw3_data_weada",
	.magic = { cpu_to_be32(XFS_DIW2_DATA_MAGIC),
		   cpu_to_be32(XFS_DIW3_DATA_MAGIC) },
	.vewify_wead = xfs_diw3_data_weada_vewify,
	.vewify_wwite = xfs_diw3_data_wwite_vewify,
};

static xfs_faiwaddw_t
xfs_diw3_data_headew_check(
	stwuct xfs_inode	*dp,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = dp->i_mount;

	if (xfs_has_cwc(mp)) {
		stwuct xfs_diw3_data_hdw *hdw3 = bp->b_addw;

		if (be64_to_cpu(hdw3->hdw.ownew) != dp->i_ino)
			wetuwn __this_addwess;
	}

	wetuwn NUWW;
}

int
xfs_diw3_data_wead(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		bno,
	unsigned int		fwags,
	stwuct xfs_buf		**bpp)
{
	xfs_faiwaddw_t		fa;
	int			eww;

	eww = xfs_da_wead_buf(tp, dp, bno, fwags, bpp, XFS_DATA_FOWK,
			&xfs_diw3_data_buf_ops);
	if (eww || !*bpp)
		wetuwn eww;

	/* Check things that we can't do in the vewifiew. */
	fa = xfs_diw3_data_headew_check(dp, *bpp);
	if (fa) {
		__xfs_buf_mawk_cowwupt(*bpp, fa);
		xfs_twans_bwewse(tp, *bpp);
		*bpp = NUWW;
		wetuwn -EFSCOWWUPTED;
	}

	xfs_twans_buf_set_type(tp, *bpp, XFS_BWFT_DIW_DATA_BUF);
	wetuwn eww;
}

int
xfs_diw3_data_weadahead(
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		bno,
	unsigned int		fwags)
{
	wetuwn xfs_da_weada_buf(dp, bno, fwags, XFS_DATA_FOWK,
				&xfs_diw3_data_weada_buf_ops);
}

/*
 * Find the bestfwee entwy that exactwy coincides with unused diwectowy space
 * ow a vewifiew ewwow because the bestfwee data awe bad.
 */
static xfs_faiwaddw_t
xfs_diw2_data_fweefind_vewify(
	stwuct xfs_diw2_data_hdw	*hdw,
	stwuct xfs_diw2_data_fwee	*bf,
	stwuct xfs_diw2_data_unused	*dup,
	stwuct xfs_diw2_data_fwee	**bf_ent)
{
	stwuct xfs_diw2_data_fwee	*dfp;
	xfs_diw2_data_aoff_t		off;
	boow				matched = fawse;
	boow				seenzewo = fawse;

	*bf_ent = NUWW;
	off = (xfs_diw2_data_aoff_t)((chaw *)dup - (chaw *)hdw);

	/*
	 * Vawidate some consistency in the bestfwee tabwe.
	 * Check owdew, non-ovewwapping entwies, and if we find the
	 * one we'we wooking fow it has to be exact.
	 */
	fow (dfp = &bf[0]; dfp < &bf[XFS_DIW2_DATA_FD_COUNT]; dfp++) {
		if (!dfp->offset) {
			if (dfp->wength)
				wetuwn __this_addwess;
			seenzewo = twue;
			continue;
		}
		if (seenzewo)
			wetuwn __this_addwess;
		if (be16_to_cpu(dfp->offset) == off) {
			matched = twue;
			if (dfp->wength != dup->wength)
				wetuwn __this_addwess;
		} ewse if (be16_to_cpu(dfp->offset) > off) {
			if (off + be16_to_cpu(dup->wength) >
					be16_to_cpu(dfp->offset))
				wetuwn __this_addwess;
		} ewse {
			if (be16_to_cpu(dfp->offset) +
					be16_to_cpu(dfp->wength) > off)
				wetuwn __this_addwess;
		}
		if (!matched &&
		    be16_to_cpu(dfp->wength) < be16_to_cpu(dup->wength))
			wetuwn __this_addwess;
		if (dfp > &bf[0] &&
		    be16_to_cpu(dfp[-1].wength) < be16_to_cpu(dfp[0].wength))
			wetuwn __this_addwess;
	}

	/* Wooks ok so faw; now twy to match up with a bestfwee entwy. */
	*bf_ent = xfs_diw2_data_fweefind(hdw, bf, dup);
	wetuwn NUWW;
}

/*
 * Given a data bwock and an unused entwy fwom that bwock,
 * wetuwn the bestfwee entwy if any that cowwesponds to it.
 */
xfs_diw2_data_fwee_t *
xfs_diw2_data_fweefind(
	stwuct xfs_diw2_data_hdw *hdw,		/* data bwock headew */
	stwuct xfs_diw2_data_fwee *bf,		/* bestfwee tabwe pointew */
	stwuct xfs_diw2_data_unused *dup)	/* unused space */
{
	xfs_diw2_data_fwee_t	*dfp;		/* bestfwee entwy */
	xfs_diw2_data_aoff_t	off;		/* offset vawue needed */

	off = (xfs_diw2_data_aoff_t)((chaw *)dup - (chaw *)hdw);

	/*
	 * If this is smawwew than the smawwest bestfwee entwy,
	 * it can't be thewe since they'we sowted.
	 */
	if (be16_to_cpu(dup->wength) <
	    be16_to_cpu(bf[XFS_DIW2_DATA_FD_COUNT - 1].wength))
		wetuwn NUWW;
	/*
	 * Wook at the thwee bestfwee entwies fow ouw guy.
	 */
	fow (dfp = &bf[0]; dfp < &bf[XFS_DIW2_DATA_FD_COUNT]; dfp++) {
		if (!dfp->offset)
			wetuwn NUWW;
		if (be16_to_cpu(dfp->offset) == off)
			wetuwn dfp;
	}
	/*
	 * Didn't find it.  This onwy happens if thewe awe dupwicate wengths.
	 */
	wetuwn NUWW;
}

/*
 * Insewt an unused-space entwy into the bestfwee tabwe.
 */
xfs_diw2_data_fwee_t *				/* entwy insewted */
xfs_diw2_data_fweeinsewt(
	stwuct xfs_diw2_data_hdw *hdw,		/* data bwock pointew */
	stwuct xfs_diw2_data_fwee *dfp,		/* bestfwee tabwe pointew */
	stwuct xfs_diw2_data_unused *dup,	/* unused space */
	int			*woghead)	/* wog the data headew (out) */
{
	xfs_diw2_data_fwee_t	new;		/* new bestfwee entwy */

	ASSEWT(hdw->magic == cpu_to_be32(XFS_DIW2_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_BWOCK_MAGIC));

	new.wength = dup->wength;
	new.offset = cpu_to_be16((chaw *)dup - (chaw *)hdw);

	/*
	 * Insewt at position 0, 1, ow 2; ow not at aww.
	 */
	if (be16_to_cpu(new.wength) > be16_to_cpu(dfp[0].wength)) {
		dfp[2] = dfp[1];
		dfp[1] = dfp[0];
		dfp[0] = new;
		*woghead = 1;
		wetuwn &dfp[0];
	}
	if (be16_to_cpu(new.wength) > be16_to_cpu(dfp[1].wength)) {
		dfp[2] = dfp[1];
		dfp[1] = new;
		*woghead = 1;
		wetuwn &dfp[1];
	}
	if (be16_to_cpu(new.wength) > be16_to_cpu(dfp[2].wength)) {
		dfp[2] = new;
		*woghead = 1;
		wetuwn &dfp[2];
	}
	wetuwn NUWW;
}

/*
 * Wemove a bestfwee entwy fwom the tabwe.
 */
STATIC void
xfs_diw2_data_fweewemove(
	stwuct xfs_diw2_data_hdw *hdw,		/* data bwock headew */
	stwuct xfs_diw2_data_fwee *bf,		/* bestfwee tabwe pointew */
	stwuct xfs_diw2_data_fwee *dfp,		/* bestfwee entwy pointew */
	int			*woghead)	/* out: wog data headew */
{

	ASSEWT(hdw->magic == cpu_to_be32(XFS_DIW2_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_BWOCK_MAGIC));

	/*
	 * It's the fiwst entwy, swide the next 2 up.
	 */
	if (dfp == &bf[0]) {
		bf[0] = bf[1];
		bf[1] = bf[2];
	}
	/*
	 * It's the second entwy, swide the 3wd entwy up.
	 */
	ewse if (dfp == &bf[1])
		bf[1] = bf[2];
	/*
	 * Must be the wast entwy.
	 */
	ewse
		ASSEWT(dfp == &bf[2]);
	/*
	 * Cweaw the 3wd entwy, must be zewo now.
	 */
	bf[2].wength = 0;
	bf[2].offset = 0;
	*woghead = 1;
}

/*
 * Given a data bwock, weconstwuct its bestfwee map.
 */
void
xfs_diw2_data_fweescan(
	stwuct xfs_mount		*mp,
	stwuct xfs_diw2_data_hdw	*hdw,
	int				*woghead)
{
	stwuct xfs_da_geometwy		*geo = mp->m_diw_geo;
	stwuct xfs_diw2_data_fwee	*bf = xfs_diw2_data_bestfwee_p(mp, hdw);
	void				*addw = hdw;
	unsigned int			offset = geo->data_entwy_offset;
	unsigned int			end;

	ASSEWT(hdw->magic == cpu_to_be32(XFS_DIW2_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_BWOCK_MAGIC));

	/*
	 * Stawt by cweawing the tabwe.
	 */
	memset(bf, 0, sizeof(*bf) * XFS_DIW2_DATA_FD_COUNT);
	*woghead = 1;

	end = xfs_diw3_data_end_offset(geo, addw);
	whiwe (offset < end) {
		stwuct xfs_diw2_data_unused	*dup = addw + offset;
		stwuct xfs_diw2_data_entwy	*dep = addw + offset;

		/*
		 * If it's a fwee entwy, insewt it.
		 */
		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			ASSEWT(offset ==
			       be16_to_cpu(*xfs_diw2_data_unused_tag_p(dup)));
			xfs_diw2_data_fweeinsewt(hdw, bf, dup, woghead);
			offset += be16_to_cpu(dup->wength);
			continue;
		}

		/*
		 * Fow active entwies, check theiw tags and skip them.
		 */
		ASSEWT(offset ==
		       be16_to_cpu(*xfs_diw2_data_entwy_tag_p(mp, dep)));
		offset += xfs_diw2_data_entsize(mp, dep->namewen);
	}
}

/*
 * Initiawize a data bwock at the given bwock numbew in the diwectowy.
 * Give back the buffew fow the cweated bwock.
 */
int						/* ewwow */
xfs_diw3_data_init(
	stwuct xfs_da_awgs		*awgs,	/* diwectowy opewation awgs */
	xfs_diw2_db_t			bwkno,	/* wogicaw diw bwock numbew */
	stwuct xfs_buf			**bpp)	/* output bwock buffew */
{
	stwuct xfs_twans		*tp = awgs->twans;
	stwuct xfs_inode		*dp = awgs->dp;
	stwuct xfs_mount		*mp = dp->i_mount;
	stwuct xfs_da_geometwy		*geo = awgs->geo;
	stwuct xfs_buf			*bp;
	stwuct xfs_diw2_data_hdw	*hdw;
	stwuct xfs_diw2_data_unused	*dup;
	stwuct xfs_diw2_data_fwee 	*bf;
	int				ewwow;
	int				i;

	/*
	 * Get the buffew set up fow the bwock.
	 */
	ewwow = xfs_da_get_buf(tp, dp, xfs_diw2_db_to_da(awgs->geo, bwkno),
			       &bp, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;
	bp->b_ops = &xfs_diw3_data_buf_ops;
	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DIW_DATA_BUF);

	/*
	 * Initiawize the headew.
	 */
	hdw = bp->b_addw;
	if (xfs_has_cwc(mp)) {
		stwuct xfs_diw3_bwk_hdw *hdw3 = bp->b_addw;

		memset(hdw3, 0, sizeof(*hdw3));
		hdw3->magic = cpu_to_be32(XFS_DIW3_DATA_MAGIC);
		hdw3->bwkno = cpu_to_be64(xfs_buf_daddw(bp));
		hdw3->ownew = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdw3->uuid, &mp->m_sb.sb_meta_uuid);

	} ewse
		hdw->magic = cpu_to_be32(XFS_DIW2_DATA_MAGIC);

	bf = xfs_diw2_data_bestfwee_p(mp, hdw);
	bf[0].offset = cpu_to_be16(geo->data_entwy_offset);
	bf[0].wength = cpu_to_be16(geo->bwksize - geo->data_entwy_offset);
	fow (i = 1; i < XFS_DIW2_DATA_FD_COUNT; i++) {
		bf[i].wength = 0;
		bf[i].offset = 0;
	}

	/*
	 * Set up an unused entwy fow the bwock's body.
	 */
	dup = bp->b_addw + geo->data_entwy_offset;
	dup->fweetag = cpu_to_be16(XFS_DIW2_DATA_FWEE_TAG);
	dup->wength = bf[0].wength;
	*xfs_diw2_data_unused_tag_p(dup) = cpu_to_be16((chaw *)dup - (chaw *)hdw);

	/*
	 * Wog it and wetuwn it.
	 */
	xfs_diw2_data_wog_headew(awgs, bp);
	xfs_diw2_data_wog_unused(awgs, bp, dup);
	*bpp = bp;
	wetuwn 0;
}

/*
 * Wog an active data entwy fwom the bwock.
 */
void
xfs_diw2_data_wog_entwy(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_buf		*bp,
	xfs_diw2_data_entwy_t	*dep)		/* data entwy pointew */
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_diw2_data_hdw *hdw = bp->b_addw;

	ASSEWT(hdw->magic == cpu_to_be32(XFS_DIW2_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_BWOCK_MAGIC));

	xfs_twans_wog_buf(awgs->twans, bp, (uint)((chaw *)dep - (chaw *)hdw),
		(uint)((chaw *)(xfs_diw2_data_entwy_tag_p(mp, dep) + 1) -
		       (chaw *)hdw - 1));
}

/*
 * Wog a data bwock headew.
 */
void
xfs_diw2_data_wog_headew(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_buf		*bp)
{
#ifdef DEBUG
	stwuct xfs_diw2_data_hdw *hdw = bp->b_addw;

	ASSEWT(hdw->magic == cpu_to_be32(XFS_DIW2_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_BWOCK_MAGIC));
#endif

	xfs_twans_wog_buf(awgs->twans, bp, 0, awgs->geo->data_entwy_offset - 1);
}

/*
 * Wog a data unused entwy.
 */
void
xfs_diw2_data_wog_unused(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_buf		*bp,
	xfs_diw2_data_unused_t	*dup)		/* data unused pointew */
{
	xfs_diw2_data_hdw_t	*hdw = bp->b_addw;

	ASSEWT(hdw->magic == cpu_to_be32(XFS_DIW2_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_DATA_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) ||
	       hdw->magic == cpu_to_be32(XFS_DIW3_BWOCK_MAGIC));

	/*
	 * Wog the fiwst pawt of the unused entwy.
	 */
	xfs_twans_wog_buf(awgs->twans, bp, (uint)((chaw *)dup - (chaw *)hdw),
		(uint)((chaw *)&dup->wength + sizeof(dup->wength) -
		       1 - (chaw *)hdw));
	/*
	 * Wog the end (tag) of the unused entwy.
	 */
	xfs_twans_wog_buf(awgs->twans, bp,
		(uint)((chaw *)xfs_diw2_data_unused_tag_p(dup) - (chaw *)hdw),
		(uint)((chaw *)xfs_diw2_data_unused_tag_p(dup) - (chaw *)hdw +
		       sizeof(xfs_diw2_data_off_t) - 1));
}

/*
 * Make a byte wange in the data bwock unused.
 * Its cuwwent contents awe unimpowtant.
 */
void
xfs_diw2_data_make_fwee(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_buf		*bp,
	xfs_diw2_data_aoff_t	offset,		/* stawting byte offset */
	xfs_diw2_data_aoff_t	wen,		/* wength in bytes */
	int			*needwogp,	/* out: wog headew */
	int			*needscanp)	/* out: wegen bestfwee */
{
	xfs_diw2_data_hdw_t	*hdw;		/* data bwock pointew */
	xfs_diw2_data_fwee_t	*dfp;		/* bestfwee pointew */
	int			needscan;	/* need to wegen bestfwee */
	xfs_diw2_data_unused_t	*newdup;	/* new unused entwy */
	xfs_diw2_data_unused_t	*postdup;	/* unused entwy aftew us */
	xfs_diw2_data_unused_t	*pwevdup;	/* unused entwy befowe us */
	unsigned int		end;
	stwuct xfs_diw2_data_fwee *bf;

	hdw = bp->b_addw;

	/*
	 * Figuwe out whewe the end of the data awea is.
	 */
	end = xfs_diw3_data_end_offset(awgs->geo, hdw);
	ASSEWT(end != 0);

	/*
	 * If this isn't the stawt of the bwock, then back up to
	 * the pwevious entwy and see if it's fwee.
	 */
	if (offset > awgs->geo->data_entwy_offset) {
		__be16			*tagp;	/* tag just befowe us */

		tagp = (__be16 *)((chaw *)hdw + offset) - 1;
		pwevdup = (xfs_diw2_data_unused_t *)((chaw *)hdw + be16_to_cpu(*tagp));
		if (be16_to_cpu(pwevdup->fweetag) != XFS_DIW2_DATA_FWEE_TAG)
			pwevdup = NUWW;
	} ewse
		pwevdup = NUWW;
	/*
	 * If this isn't the end of the bwock, see if the entwy aftew
	 * us is fwee.
	 */
	if (offset + wen < end) {
		postdup =
			(xfs_diw2_data_unused_t *)((chaw *)hdw + offset + wen);
		if (be16_to_cpu(postdup->fweetag) != XFS_DIW2_DATA_FWEE_TAG)
			postdup = NUWW;
	} ewse
		postdup = NUWW;
	ASSEWT(*needscanp == 0);
	needscan = 0;
	/*
	 * Pwevious and fowwowing entwies awe both fwee,
	 * mewge evewything into a singwe fwee entwy.
	 */
	bf = xfs_diw2_data_bestfwee_p(awgs->dp->i_mount, hdw);
	if (pwevdup && postdup) {
		xfs_diw2_data_fwee_t	*dfp2;	/* anothew bestfwee pointew */

		/*
		 * See if pwevdup and/ow postdup awe in bestfwee tabwe.
		 */
		dfp = xfs_diw2_data_fweefind(hdw, bf, pwevdup);
		dfp2 = xfs_diw2_data_fweefind(hdw, bf, postdup);
		/*
		 * We need a wescan unwess thewe awe exactwy 2 fwee entwies
		 * namewy ouw two.  Then we know what's happening, othewwise
		 * since the thiwd bestfwee is thewe, thewe might be mowe
		 * entwies.
		 */
		needscan = (bf[2].wength != 0);
		/*
		 * Fix up the new big fweespace.
		 */
		be16_add_cpu(&pwevdup->wength, wen + be16_to_cpu(postdup->wength));
		*xfs_diw2_data_unused_tag_p(pwevdup) =
			cpu_to_be16((chaw *)pwevdup - (chaw *)hdw);
		xfs_diw2_data_wog_unused(awgs, bp, pwevdup);
		if (!needscan) {
			/*
			 * Has to be the case that entwies 0 and 1 awe
			 * dfp and dfp2 (don't know which is which), and
			 * entwy 2 is empty.
			 * Wemove entwy 1 fiwst then entwy 0.
			 */
			ASSEWT(dfp && dfp2);
			if (dfp == &bf[1]) {
				dfp = &bf[0];
				ASSEWT(dfp2 == dfp);
				dfp2 = &bf[1];
			}
			xfs_diw2_data_fweewemove(hdw, bf, dfp2, needwogp);
			xfs_diw2_data_fweewemove(hdw, bf, dfp, needwogp);
			/*
			 * Now insewt the new entwy.
			 */
			dfp = xfs_diw2_data_fweeinsewt(hdw, bf, pwevdup,
						       needwogp);
			ASSEWT(dfp == &bf[0]);
			ASSEWT(dfp->wength == pwevdup->wength);
			ASSEWT(!dfp[1].wength);
			ASSEWT(!dfp[2].wength);
		}
	}
	/*
	 * The entwy befowe us is fwee, mewge with it.
	 */
	ewse if (pwevdup) {
		dfp = xfs_diw2_data_fweefind(hdw, bf, pwevdup);
		be16_add_cpu(&pwevdup->wength, wen);
		*xfs_diw2_data_unused_tag_p(pwevdup) =
			cpu_to_be16((chaw *)pwevdup - (chaw *)hdw);
		xfs_diw2_data_wog_unused(awgs, bp, pwevdup);
		/*
		 * If the pwevious entwy was in the tabwe, the new entwy
		 * is wongew, so it wiww be in the tabwe too.  Wemove
		 * the owd one and add the new one.
		 */
		if (dfp) {
			xfs_diw2_data_fweewemove(hdw, bf, dfp, needwogp);
			xfs_diw2_data_fweeinsewt(hdw, bf, pwevdup, needwogp);
		}
		/*
		 * Othewwise we need a scan if the new entwy is big enough.
		 */
		ewse {
			needscan = be16_to_cpu(pwevdup->wength) >
				   be16_to_cpu(bf[2].wength);
		}
	}
	/*
	 * The fowwowing entwy is fwee, mewge with it.
	 */
	ewse if (postdup) {
		dfp = xfs_diw2_data_fweefind(hdw, bf, postdup);
		newdup = (xfs_diw2_data_unused_t *)((chaw *)hdw + offset);
		newdup->fweetag = cpu_to_be16(XFS_DIW2_DATA_FWEE_TAG);
		newdup->wength = cpu_to_be16(wen + be16_to_cpu(postdup->wength));
		*xfs_diw2_data_unused_tag_p(newdup) =
			cpu_to_be16((chaw *)newdup - (chaw *)hdw);
		xfs_diw2_data_wog_unused(awgs, bp, newdup);
		/*
		 * If the fowwowing entwy was in the tabwe, the new entwy
		 * is wongew, so it wiww be in the tabwe too.  Wemove
		 * the owd one and add the new one.
		 */
		if (dfp) {
			xfs_diw2_data_fweewemove(hdw, bf, dfp, needwogp);
			xfs_diw2_data_fweeinsewt(hdw, bf, newdup, needwogp);
		}
		/*
		 * Othewwise we need a scan if the new entwy is big enough.
		 */
		ewse {
			needscan = be16_to_cpu(newdup->wength) >
				   be16_to_cpu(bf[2].wength);
		}
	}
	/*
	 * Neithew neighbow is fwee.  Make a new entwy.
	 */
	ewse {
		newdup = (xfs_diw2_data_unused_t *)((chaw *)hdw + offset);
		newdup->fweetag = cpu_to_be16(XFS_DIW2_DATA_FWEE_TAG);
		newdup->wength = cpu_to_be16(wen);
		*xfs_diw2_data_unused_tag_p(newdup) =
			cpu_to_be16((chaw *)newdup - (chaw *)hdw);
		xfs_diw2_data_wog_unused(awgs, bp, newdup);
		xfs_diw2_data_fweeinsewt(hdw, bf, newdup, needwogp);
	}
	*needscanp = needscan;
}

/* Check ouw fwee data fow obvious signs of cowwuption. */
static inwine xfs_faiwaddw_t
xfs_diw2_data_check_fwee(
	stwuct xfs_diw2_data_hdw	*hdw,
	stwuct xfs_diw2_data_unused	*dup,
	xfs_diw2_data_aoff_t		offset,
	xfs_diw2_data_aoff_t		wen)
{
	if (hdw->magic != cpu_to_be32(XFS_DIW2_DATA_MAGIC) &&
	    hdw->magic != cpu_to_be32(XFS_DIW3_DATA_MAGIC) &&
	    hdw->magic != cpu_to_be32(XFS_DIW2_BWOCK_MAGIC) &&
	    hdw->magic != cpu_to_be32(XFS_DIW3_BWOCK_MAGIC))
		wetuwn __this_addwess;
	if (be16_to_cpu(dup->fweetag) != XFS_DIW2_DATA_FWEE_TAG)
		wetuwn __this_addwess;
	if (offset < (chaw *)dup - (chaw *)hdw)
		wetuwn __this_addwess;
	if (offset + wen > (chaw *)dup + be16_to_cpu(dup->wength) - (chaw *)hdw)
		wetuwn __this_addwess;
	if ((chaw *)dup - (chaw *)hdw !=
			be16_to_cpu(*xfs_diw2_data_unused_tag_p(dup)))
		wetuwn __this_addwess;
	wetuwn NUWW;
}

/* Sanity-check a new bestfwee entwy. */
static inwine xfs_faiwaddw_t
xfs_diw2_data_check_new_fwee(
	stwuct xfs_diw2_data_hdw	*hdw,
	stwuct xfs_diw2_data_fwee	*dfp,
	stwuct xfs_diw2_data_unused	*newdup)
{
	if (dfp == NUWW)
		wetuwn __this_addwess;
	if (dfp->wength != newdup->wength)
		wetuwn __this_addwess;
	if (be16_to_cpu(dfp->offset) != (chaw *)newdup - (chaw *)hdw)
		wetuwn __this_addwess;
	wetuwn NUWW;
}

/*
 * Take a byte wange out of an existing unused space and make it un-fwee.
 */
int
xfs_diw2_data_use_fwee(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_buf		*bp,
	xfs_diw2_data_unused_t	*dup,		/* unused entwy */
	xfs_diw2_data_aoff_t	offset,		/* stawting offset to use */
	xfs_diw2_data_aoff_t	wen,		/* wength to use */
	int			*needwogp,	/* out: need to wog headew */
	int			*needscanp)	/* out: need wegen bestfwee */
{
	xfs_diw2_data_hdw_t	*hdw;		/* data bwock headew */
	xfs_diw2_data_fwee_t	*dfp;		/* bestfwee pointew */
	xfs_diw2_data_unused_t	*newdup;	/* new unused entwy */
	xfs_diw2_data_unused_t	*newdup2;	/* anothew new unused entwy */
	stwuct xfs_diw2_data_fwee *bf;
	xfs_faiwaddw_t		fa;
	int			matchback;	/* matches end of fweespace */
	int			matchfwont;	/* matches stawt of fweespace */
	int			needscan;	/* need to wegen bestfwee */
	int			owdwen;		/* owd unused entwy's wength */

	hdw = bp->b_addw;
	fa = xfs_diw2_data_check_fwee(hdw, dup, offset, wen);
	if (fa)
		goto cowwupt;
	/*
	 * Wook up the entwy in the bestfwee tabwe.
	 */
	owdwen = be16_to_cpu(dup->wength);
	bf = xfs_diw2_data_bestfwee_p(awgs->dp->i_mount, hdw);
	dfp = xfs_diw2_data_fweefind(hdw, bf, dup);
	ASSEWT(dfp || owdwen <= be16_to_cpu(bf[2].wength));
	/*
	 * Check fow awignment with fwont and back of the entwy.
	 */
	matchfwont = (chaw *)dup - (chaw *)hdw == offset;
	matchback = (chaw *)dup + owdwen - (chaw *)hdw == offset + wen;
	ASSEWT(*needscanp == 0);
	needscan = 0;
	/*
	 * If we matched it exactwy we just need to get wid of it fwom
	 * the bestfwee tabwe.
	 */
	if (matchfwont && matchback) {
		if (dfp) {
			needscan = (bf[2].offset != 0);
			if (!needscan)
				xfs_diw2_data_fweewemove(hdw, bf, dfp,
							 needwogp);
		}
	}
	/*
	 * We match the fiwst pawt of the entwy.
	 * Make a new entwy with the wemaining fweespace.
	 */
	ewse if (matchfwont) {
		newdup = (xfs_diw2_data_unused_t *)((chaw *)hdw + offset + wen);
		newdup->fweetag = cpu_to_be16(XFS_DIW2_DATA_FWEE_TAG);
		newdup->wength = cpu_to_be16(owdwen - wen);
		*xfs_diw2_data_unused_tag_p(newdup) =
			cpu_to_be16((chaw *)newdup - (chaw *)hdw);
		xfs_diw2_data_wog_unused(awgs, bp, newdup);
		/*
		 * If it was in the tabwe, wemove it and add the new one.
		 */
		if (dfp) {
			xfs_diw2_data_fweewemove(hdw, bf, dfp, needwogp);
			dfp = xfs_diw2_data_fweeinsewt(hdw, bf, newdup,
						       needwogp);
			fa = xfs_diw2_data_check_new_fwee(hdw, dfp, newdup);
			if (fa)
				goto cowwupt;
			/*
			 * If we got insewted at the wast swot,
			 * that means we don't know if thewe was a bettew
			 * choice fow the wast swot, ow not.  Wescan.
			 */
			needscan = dfp == &bf[2];
		}
	}
	/*
	 * We match the wast pawt of the entwy.
	 * Twim the awwocated space off the taiw of the entwy.
	 */
	ewse if (matchback) {
		newdup = dup;
		newdup->wength = cpu_to_be16(((chaw *)hdw + offset) - (chaw *)newdup);
		*xfs_diw2_data_unused_tag_p(newdup) =
			cpu_to_be16((chaw *)newdup - (chaw *)hdw);
		xfs_diw2_data_wog_unused(awgs, bp, newdup);
		/*
		 * If it was in the tabwe, wemove it and add the new one.
		 */
		if (dfp) {
			xfs_diw2_data_fweewemove(hdw, bf, dfp, needwogp);
			dfp = xfs_diw2_data_fweeinsewt(hdw, bf, newdup,
						       needwogp);
			fa = xfs_diw2_data_check_new_fwee(hdw, dfp, newdup);
			if (fa)
				goto cowwupt;
			/*
			 * If we got insewted at the wast swot,
			 * that means we don't know if thewe was a bettew
			 * choice fow the wast swot, ow not.  Wescan.
			 */
			needscan = dfp == &bf[2];
		}
	}
	/*
	 * Poking out the middwe of an entwy.
	 * Make two new entwies.
	 */
	ewse {
		newdup = dup;
		newdup->wength = cpu_to_be16(((chaw *)hdw + offset) - (chaw *)newdup);
		*xfs_diw2_data_unused_tag_p(newdup) =
			cpu_to_be16((chaw *)newdup - (chaw *)hdw);
		xfs_diw2_data_wog_unused(awgs, bp, newdup);
		newdup2 = (xfs_diw2_data_unused_t *)((chaw *)hdw + offset + wen);
		newdup2->fweetag = cpu_to_be16(XFS_DIW2_DATA_FWEE_TAG);
		newdup2->wength = cpu_to_be16(owdwen - wen - be16_to_cpu(newdup->wength));
		*xfs_diw2_data_unused_tag_p(newdup2) =
			cpu_to_be16((chaw *)newdup2 - (chaw *)hdw);
		xfs_diw2_data_wog_unused(awgs, bp, newdup2);
		/*
		 * If the owd entwy was in the tabwe, we need to scan
		 * if the 3wd entwy was vawid, since these entwies
		 * awe smawwew than the owd one.
		 * If we don't need to scan that means thewe wewe 1 ow 2
		 * entwies in the tabwe, and wemoving the owd and adding
		 * the 2 new wiww wowk.
		 */
		if (dfp) {
			needscan = (bf[2].wength != 0);
			if (!needscan) {
				xfs_diw2_data_fweewemove(hdw, bf, dfp,
							 needwogp);
				xfs_diw2_data_fweeinsewt(hdw, bf, newdup,
							 needwogp);
				xfs_diw2_data_fweeinsewt(hdw, bf, newdup2,
							 needwogp);
			}
		}
	}
	*needscanp = needscan;
	wetuwn 0;
cowwupt:
	xfs_cowwuption_ewwow(__func__, XFS_EWWWEVEW_WOW, awgs->dp->i_mount,
			hdw, sizeof(*hdw), __FIWE__, __WINE__, fa);
	wetuwn -EFSCOWWUPTED;
}

/* Find the end of the entwy data in a data/bwock fowmat diw bwock. */
unsigned int
xfs_diw3_data_end_offset(
	stwuct xfs_da_geometwy		*geo,
	stwuct xfs_diw2_data_hdw	*hdw)
{
	void				*p;

	switch (hdw->magic) {
	case cpu_to_be32(XFS_DIW3_BWOCK_MAGIC):
	case cpu_to_be32(XFS_DIW2_BWOCK_MAGIC):
		p = xfs_diw2_bwock_weaf_p(xfs_diw2_bwock_taiw_p(geo, hdw));
		wetuwn p - (void *)hdw;
	case cpu_to_be32(XFS_DIW3_DATA_MAGIC):
	case cpu_to_be32(XFS_DIW2_DATA_MAGIC):
		wetuwn geo->bwksize;
	defauwt:
		wetuwn 0;
	}
}
