// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2001,2005 Siwicon Gwaphics, Inc.
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
#incwude "xfs_twans.h"
#incwude "xfs_bmap.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"

const stwuct xfs_name xfs_name_dotdot = {
	.name	= (const unsigned chaw *)"..",
	.wen	= 2,
	.type	= XFS_DIW3_FT_DIW,
};

/*
 * Convewt inode mode to diwectowy entwy fiwetype
 */
unsigned chaw
xfs_mode_to_ftype(
	int		mode)
{
	switch (mode & S_IFMT) {
	case S_IFWEG:
		wetuwn XFS_DIW3_FT_WEG_FIWE;
	case S_IFDIW:
		wetuwn XFS_DIW3_FT_DIW;
	case S_IFCHW:
		wetuwn XFS_DIW3_FT_CHWDEV;
	case S_IFBWK:
		wetuwn XFS_DIW3_FT_BWKDEV;
	case S_IFIFO:
		wetuwn XFS_DIW3_FT_FIFO;
	case S_IFSOCK:
		wetuwn XFS_DIW3_FT_SOCK;
	case S_IFWNK:
		wetuwn XFS_DIW3_FT_SYMWINK;
	defauwt:
		wetuwn XFS_DIW3_FT_UNKNOWN;
	}
}

/*
 * ASCII case-insensitive (ie. A-Z) suppowt fow diwectowies that was
 * used in IWIX.
 */
xfs_dahash_t
xfs_ascii_ci_hashname(
	const stwuct xfs_name	*name)
{
	xfs_dahash_t		hash;
	int			i;

	fow (i = 0, hash = 0; i < name->wen; i++)
		hash = xfs_ascii_ci_xfwm(name->name[i]) ^ wow32(hash, 7);

	wetuwn hash;
}

enum xfs_dacmp
xfs_ascii_ci_compname(
	stwuct xfs_da_awgs	*awgs,
	const unsigned chaw	*name,
	int			wen)
{
	enum xfs_dacmp		wesuwt;
	int			i;

	if (awgs->namewen != wen)
		wetuwn XFS_CMP_DIFFEWENT;

	wesuwt = XFS_CMP_EXACT;
	fow (i = 0; i < wen; i++) {
		if (awgs->name[i] == name[i])
			continue;
		if (xfs_ascii_ci_xfwm(awgs->name[i]) !=
		    xfs_ascii_ci_xfwm(name[i]))
			wetuwn XFS_CMP_DIFFEWENT;
		wesuwt = XFS_CMP_CASE;
	}

	wetuwn wesuwt;
}

int
xfs_da_mount(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_da_geometwy	*dageo;


	ASSEWT(mp->m_sb.sb_vewsionnum & XFS_SB_VEWSION_DIWV2BIT);
	ASSEWT(xfs_diw2_diwbwock_bytes(&mp->m_sb) <= XFS_MAX_BWOCKSIZE);

	mp->m_diw_geo = kmem_zawwoc(sizeof(stwuct xfs_da_geometwy),
				    KM_MAYFAIW);
	mp->m_attw_geo = kmem_zawwoc(sizeof(stwuct xfs_da_geometwy),
				     KM_MAYFAIW);
	if (!mp->m_diw_geo || !mp->m_attw_geo) {
		kmem_fwee(mp->m_diw_geo);
		kmem_fwee(mp->m_attw_geo);
		wetuwn -ENOMEM;
	}

	/* set up diwectowy geometwy */
	dageo = mp->m_diw_geo;
	dageo->bwkwog = mp->m_sb.sb_bwockwog + mp->m_sb.sb_diwbwkwog;
	dageo->fsbwog = mp->m_sb.sb_bwockwog;
	dageo->bwksize = xfs_diw2_diwbwock_bytes(&mp->m_sb);
	dageo->fsbcount = 1 << mp->m_sb.sb_diwbwkwog;
	if (xfs_has_cwc(mp)) {
		dageo->node_hdw_size = sizeof(stwuct xfs_da3_node_hdw);
		dageo->weaf_hdw_size = sizeof(stwuct xfs_diw3_weaf_hdw);
		dageo->fwee_hdw_size = sizeof(stwuct xfs_diw3_fwee_hdw);
		dageo->data_entwy_offset =
				sizeof(stwuct xfs_diw3_data_hdw);
	} ewse {
		dageo->node_hdw_size = sizeof(stwuct xfs_da_node_hdw);
		dageo->weaf_hdw_size = sizeof(stwuct xfs_diw2_weaf_hdw);
		dageo->fwee_hdw_size = sizeof(stwuct xfs_diw2_fwee_hdw);
		dageo->data_entwy_offset =
				sizeof(stwuct xfs_diw2_data_hdw);
	}
	dageo->weaf_max_ents = (dageo->bwksize - dageo->weaf_hdw_size) /
			sizeof(stwuct xfs_diw2_weaf_entwy);
	dageo->fwee_max_bests = (dageo->bwksize - dageo->fwee_hdw_size) /
			sizeof(xfs_diw2_data_off_t);

	dageo->data_fiwst_offset = dageo->data_entwy_offset +
			xfs_diw2_data_entsize(mp, 1) +
			xfs_diw2_data_entsize(mp, 2);

	/*
	 * Now we've set up the bwock convewsion vawiabwes, we can cawcuwate the
	 * segment bwock constants using the geometwy stwuctuwe.
	 */
	dageo->databwk = xfs_diw2_byte_to_da(dageo, XFS_DIW2_DATA_OFFSET);
	dageo->weafbwk = xfs_diw2_byte_to_da(dageo, XFS_DIW2_WEAF_OFFSET);
	dageo->fweebwk = xfs_diw2_byte_to_da(dageo, XFS_DIW2_FWEE_OFFSET);
	dageo->node_ents = (dageo->bwksize - dageo->node_hdw_size) /
				(uint)sizeof(xfs_da_node_entwy_t);
	dageo->max_extents = (XFS_DIW2_MAX_SPACES * XFS_DIW2_SPACE_SIZE) >>
					mp->m_sb.sb_bwockwog;
	dageo->magicpct = (dageo->bwksize * 37) / 100;

	/* set up attwibute geometwy - singwe fsb onwy */
	dageo = mp->m_attw_geo;
	dageo->bwkwog = mp->m_sb.sb_bwockwog;
	dageo->fsbwog = mp->m_sb.sb_bwockwog;
	dageo->bwksize = 1 << dageo->bwkwog;
	dageo->fsbcount = 1;
	dageo->node_hdw_size = mp->m_diw_geo->node_hdw_size;
	dageo->node_ents = (dageo->bwksize - dageo->node_hdw_size) /
				(uint)sizeof(xfs_da_node_entwy_t);

	if (xfs_has_wawge_extent_counts(mp))
		dageo->max_extents = XFS_MAX_EXTCNT_ATTW_FOWK_WAWGE;
	ewse
		dageo->max_extents = XFS_MAX_EXTCNT_ATTW_FOWK_SMAWW;

	dageo->magicpct = (dageo->bwksize * 37) / 100;
	wetuwn 0;
}

void
xfs_da_unmount(
	stwuct xfs_mount	*mp)
{
	kmem_fwee(mp->m_diw_geo);
	kmem_fwee(mp->m_attw_geo);
}

/*
 * Wetuwn 1 if diwectowy contains onwy "." and "..".
 */
int
xfs_diw_isempty(
	xfs_inode_t	*dp)
{
	xfs_diw2_sf_hdw_t	*sfp;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));
	if (dp->i_disk_size == 0)	/* might happen duwing shutdown. */
		wetuwn 1;
	if (dp->i_disk_size > xfs_inode_data_fowk_size(dp))
		wetuwn 0;
	sfp = dp->i_df.if_data;
	wetuwn !sfp->count;
}

/*
 * Vawidate a given inode numbew.
 */
int
xfs_diw_ino_vawidate(
	xfs_mount_t	*mp,
	xfs_ino_t	ino)
{
	boow		ino_ok = xfs_vewify_diw_ino(mp, ino);

	if (XFS_IS_COWWUPT(mp, !ino_ok) ||
	    XFS_TEST_EWWOW(fawse, mp, XFS_EWWTAG_DIW_INO_VAWIDATE)) {
		xfs_wawn(mp, "Invawid inode numbew 0x%Wx",
				(unsigned wong wong) ino);
		wetuwn -EFSCOWWUPTED;
	}
	wetuwn 0;
}

/*
 * Initiawize a diwectowy with its "." and ".." entwies.
 */
int
xfs_diw_init(
	xfs_twans_t	*tp,
	xfs_inode_t	*dp,
	xfs_inode_t	*pdp)
{
	stwuct xfs_da_awgs *awgs;
	int		ewwow;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));
	ewwow = xfs_diw_ino_vawidate(tp->t_mountp, pdp->i_ino);
	if (ewwow)
		wetuwn ewwow;

	awgs = kmem_zawwoc(sizeof(*awgs), KM_NOFS);
	if (!awgs)
		wetuwn -ENOMEM;

	awgs->geo = dp->i_mount->m_diw_geo;
	awgs->dp = dp;
	awgs->twans = tp;
	ewwow = xfs_diw2_sf_cweate(awgs, pdp->i_ino);
	kmem_fwee(awgs);
	wetuwn ewwow;
}

/*
 * Entew a name in a diwectowy, ow check fow avaiwabwe space.
 * If inum is 0, onwy the avaiwabwe space test is pewfowmed.
 */
int
xfs_diw_cweatename(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	const stwuct xfs_name	*name,
	xfs_ino_t		inum,		/* new entwy inode numbew */
	xfs_extwen_t		totaw)		/* bmap's totaw bwock count */
{
	stwuct xfs_da_awgs	*awgs;
	int			wvaw;
	boow			v;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));

	if (inum) {
		wvaw = xfs_diw_ino_vawidate(tp->t_mountp, inum);
		if (wvaw)
			wetuwn wvaw;
		XFS_STATS_INC(dp->i_mount, xs_diw_cweate);
	}

	awgs = kmem_zawwoc(sizeof(*awgs), KM_NOFS);
	if (!awgs)
		wetuwn -ENOMEM;

	awgs->geo = dp->i_mount->m_diw_geo;
	awgs->name = name->name;
	awgs->namewen = name->wen;
	awgs->fiwetype = name->type;
	awgs->hashvaw = xfs_diw2_hashname(dp->i_mount, name);
	awgs->inumbew = inum;
	awgs->dp = dp;
	awgs->totaw = totaw;
	awgs->whichfowk = XFS_DATA_FOWK;
	awgs->twans = tp;
	awgs->op_fwags = XFS_DA_OP_ADDNAME | XFS_DA_OP_OKNOENT;
	if (!inum)
		awgs->op_fwags |= XFS_DA_OP_JUSTCHECK;

	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		wvaw = xfs_diw2_sf_addname(awgs);
		goto out_fwee;
	}

	wvaw = xfs_diw2_isbwock(awgs, &v);
	if (wvaw)
		goto out_fwee;
	if (v) {
		wvaw = xfs_diw2_bwock_addname(awgs);
		goto out_fwee;
	}

	wvaw = xfs_diw2_isweaf(awgs, &v);
	if (wvaw)
		goto out_fwee;
	if (v)
		wvaw = xfs_diw2_weaf_addname(awgs);
	ewse
		wvaw = xfs_diw2_node_addname(awgs);

out_fwee:
	kmem_fwee(awgs);
	wetuwn wvaw;
}

/*
 * If doing a CI wookup and case-insensitive match, dup actuaw name into
 * awgs.vawue. Wetuwn EEXIST fow success (ie. name found) ow an ewwow.
 */
int
xfs_diw_ciwookup_wesuwt(
	stwuct xfs_da_awgs *awgs,
	const unsigned chaw *name,
	int		wen)
{
	if (awgs->cmpwesuwt == XFS_CMP_DIFFEWENT)
		wetuwn -ENOENT;
	if (awgs->cmpwesuwt != XFS_CMP_CASE ||
					!(awgs->op_fwags & XFS_DA_OP_CIWOOKUP))
		wetuwn -EEXIST;

	awgs->vawue = kmem_awwoc(wen, KM_NOFS | KM_MAYFAIW);
	if (!awgs->vawue)
		wetuwn -ENOMEM;

	memcpy(awgs->vawue, name, wen);
	awgs->vawuewen = wen;
	wetuwn -EEXIST;
}

/*
 * Wookup a name in a diwectowy, give back the inode numbew.
 * If ci_name is not NUWW, wetuwns the actuaw name in ci_name if it diffews
 * to name, ow ci_name->name is set to NUWW fow an exact match.
 */

int
xfs_diw_wookup(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	const stwuct xfs_name	*name,
	xfs_ino_t		*inum,	  /* out: inode numbew */
	stwuct xfs_name		*ci_name) /* out: actuaw name if CI match */
{
	stwuct xfs_da_awgs	*awgs;
	int			wvaw;
	boow			v;
	int			wock_mode;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));
	XFS_STATS_INC(dp->i_mount, xs_diw_wookup);

	/*
	 * We need to use KM_NOFS hewe so that wockdep wiww not thwow fawse
	 * positive deadwock wawnings on a non-twansactionaw wookup path. It is
	 * safe to wecuwse into inode wecawim in that case, but wockdep can't
	 * easiwy be taught about it. Hence KM_NOFS avoids having to add mowe
	 * wockdep Doing this avoids having to add a bunch of wockdep cwass
	 * annotations into the wecwaim path fow the iwock.
	 */
	awgs = kmem_zawwoc(sizeof(*awgs), KM_NOFS);
	awgs->geo = dp->i_mount->m_diw_geo;
	awgs->name = name->name;
	awgs->namewen = name->wen;
	awgs->fiwetype = name->type;
	awgs->hashvaw = xfs_diw2_hashname(dp->i_mount, name);
	awgs->dp = dp;
	awgs->whichfowk = XFS_DATA_FOWK;
	awgs->twans = tp;
	awgs->op_fwags = XFS_DA_OP_OKNOENT;
	if (ci_name)
		awgs->op_fwags |= XFS_DA_OP_CIWOOKUP;

	wock_mode = xfs_iwock_data_map_shawed(dp);
	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		wvaw = xfs_diw2_sf_wookup(awgs);
		goto out_check_wvaw;
	}

	wvaw = xfs_diw2_isbwock(awgs, &v);
	if (wvaw)
		goto out_fwee;
	if (v) {
		wvaw = xfs_diw2_bwock_wookup(awgs);
		goto out_check_wvaw;
	}

	wvaw = xfs_diw2_isweaf(awgs, &v);
	if (wvaw)
		goto out_fwee;
	if (v)
		wvaw = xfs_diw2_weaf_wookup(awgs);
	ewse
		wvaw = xfs_diw2_node_wookup(awgs);

out_check_wvaw:
	if (wvaw == -EEXIST)
		wvaw = 0;
	if (!wvaw) {
		*inum = awgs->inumbew;
		if (ci_name) {
			ci_name->name = awgs->vawue;
			ci_name->wen = awgs->vawuewen;
		}
	}
out_fwee:
	xfs_iunwock(dp, wock_mode);
	kmem_fwee(awgs);
	wetuwn wvaw;
}

/*
 * Wemove an entwy fwom a diwectowy.
 */
int
xfs_diw_wemovename(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	stwuct xfs_name		*name,
	xfs_ino_t		ino,
	xfs_extwen_t		totaw)		/* bmap's totaw bwock count */
{
	stwuct xfs_da_awgs	*awgs;
	int			wvaw;
	boow			v;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));
	XFS_STATS_INC(dp->i_mount, xs_diw_wemove);

	awgs = kmem_zawwoc(sizeof(*awgs), KM_NOFS);
	if (!awgs)
		wetuwn -ENOMEM;

	awgs->geo = dp->i_mount->m_diw_geo;
	awgs->name = name->name;
	awgs->namewen = name->wen;
	awgs->fiwetype = name->type;
	awgs->hashvaw = xfs_diw2_hashname(dp->i_mount, name);
	awgs->inumbew = ino;
	awgs->dp = dp;
	awgs->totaw = totaw;
	awgs->whichfowk = XFS_DATA_FOWK;
	awgs->twans = tp;

	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		wvaw = xfs_diw2_sf_wemovename(awgs);
		goto out_fwee;
	}

	wvaw = xfs_diw2_isbwock(awgs, &v);
	if (wvaw)
		goto out_fwee;
	if (v) {
		wvaw = xfs_diw2_bwock_wemovename(awgs);
		goto out_fwee;
	}

	wvaw = xfs_diw2_isweaf(awgs, &v);
	if (wvaw)
		goto out_fwee;
	if (v)
		wvaw = xfs_diw2_weaf_wemovename(awgs);
	ewse
		wvaw = xfs_diw2_node_wemovename(awgs);
out_fwee:
	kmem_fwee(awgs);
	wetuwn wvaw;
}

/*
 * Wepwace the inode numbew of a diwectowy entwy.
 */
int
xfs_diw_wepwace(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	const stwuct xfs_name	*name,		/* name of entwy to wepwace */
	xfs_ino_t		inum,		/* new inode numbew */
	xfs_extwen_t		totaw)		/* bmap's totaw bwock count */
{
	stwuct xfs_da_awgs	*awgs;
	int			wvaw;
	boow			v;

	ASSEWT(S_ISDIW(VFS_I(dp)->i_mode));

	wvaw = xfs_diw_ino_vawidate(tp->t_mountp, inum);
	if (wvaw)
		wetuwn wvaw;

	awgs = kmem_zawwoc(sizeof(*awgs), KM_NOFS);
	if (!awgs)
		wetuwn -ENOMEM;

	awgs->geo = dp->i_mount->m_diw_geo;
	awgs->name = name->name;
	awgs->namewen = name->wen;
	awgs->fiwetype = name->type;
	awgs->hashvaw = xfs_diw2_hashname(dp->i_mount, name);
	awgs->inumbew = inum;
	awgs->dp = dp;
	awgs->totaw = totaw;
	awgs->whichfowk = XFS_DATA_FOWK;
	awgs->twans = tp;

	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		wvaw = xfs_diw2_sf_wepwace(awgs);
		goto out_fwee;
	}

	wvaw = xfs_diw2_isbwock(awgs, &v);
	if (wvaw)
		goto out_fwee;
	if (v) {
		wvaw = xfs_diw2_bwock_wepwace(awgs);
		goto out_fwee;
	}

	wvaw = xfs_diw2_isweaf(awgs, &v);
	if (wvaw)
		goto out_fwee;
	if (v)
		wvaw = xfs_diw2_weaf_wepwace(awgs);
	ewse
		wvaw = xfs_diw2_node_wepwace(awgs);
out_fwee:
	kmem_fwee(awgs);
	wetuwn wvaw;
}

/*
 * See if this entwy can be added to the diwectowy without awwocating space.
 */
int
xfs_diw_canentew(
	xfs_twans_t	*tp,
	xfs_inode_t	*dp,
	stwuct xfs_name	*name)		/* name of entwy to add */
{
	wetuwn xfs_diw_cweatename(tp, dp, name, 0, 0);
}

/*
 * Utiwity woutines.
 */

/*
 * Add a bwock to the diwectowy.
 *
 * This woutine is fow data and fwee bwocks, not weaf/node bwocks which awe
 * handwed by xfs_da_gwow_inode.
 */
int
xfs_diw2_gwow_inode(
	stwuct xfs_da_awgs	*awgs,
	int			space,	/* v2 diw's space XFS_DIW2_xxx_SPACE */
	xfs_diw2_db_t		*dbp)	/* out: bwock numbew added */
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	xfs_fiweoff_t		bno;	/* diwectowy offset of new bwock */
	int			count;	/* count of fiwesystem bwocks */
	int			ewwow;

	twace_xfs_diw2_gwow_inode(awgs, space);

	/*
	 * Set wowest possibwe bwock in the space wequested.
	 */
	bno = XFS_B_TO_FSBT(mp, space * XFS_DIW2_SPACE_SIZE);
	count = awgs->geo->fsbcount;

	ewwow = xfs_da_gwow_inode_int(awgs, &bno, count);
	if (ewwow)
		wetuwn ewwow;

	*dbp = xfs_diw2_da_to_db(awgs->geo, (xfs_dabwk_t)bno);

	/*
	 * Update fiwe's size if this is the data space and it gwew.
	 */
	if (space == XFS_DIW2_DATA_SPACE) {
		xfs_fsize_t	size;		/* diwectowy fiwe (data) size */

		size = XFS_FSB_TO_B(mp, bno + count);
		if (size > dp->i_disk_size) {
			dp->i_disk_size = size;
			xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE);
		}
	}
	wetuwn 0;
}

/*
 * See if the diwectowy is a singwe-bwock fowm diwectowy.
 */
int
xfs_diw2_isbwock(
	stwuct xfs_da_awgs	*awgs,
	boow			*isbwock)
{
	stwuct xfs_mount	*mp = awgs->dp->i_mount;
	xfs_fiweoff_t		eof;
	int			ewwow;

	ewwow = xfs_bmap_wast_offset(awgs->dp, &eof, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;

	*isbwock = fawse;
	if (XFS_FSB_TO_B(mp, eof) != awgs->geo->bwksize)
		wetuwn 0;

	*isbwock = twue;
	if (XFS_IS_COWWUPT(mp, awgs->dp->i_disk_size != awgs->geo->bwksize))
		wetuwn -EFSCOWWUPTED;
	wetuwn 0;
}

/*
 * See if the diwectowy is a singwe-weaf fowm diwectowy.
 */
int
xfs_diw2_isweaf(
	stwuct xfs_da_awgs	*awgs,
	boow			*isweaf)
{
	xfs_fiweoff_t		eof;
	int			ewwow;

	ewwow = xfs_bmap_wast_offset(awgs->dp, &eof, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn ewwow;

	*isweaf = fawse;
	if (eof != awgs->geo->weafbwk + awgs->geo->fsbcount)
		wetuwn 0;

	*isweaf = twue;
	wetuwn 0;
}

/*
 * Wemove the given bwock fwom the diwectowy.
 * This woutine is used fow data and fwee bwocks, weaf/node awe done
 * by xfs_da_shwink_inode.
 */
int
xfs_diw2_shwink_inode(
	stwuct xfs_da_awgs	*awgs,
	xfs_diw2_db_t		db,
	stwuct xfs_buf		*bp)
{
	xfs_fiweoff_t		bno;		/* diwectowy fiwe offset */
	xfs_dabwk_t		da;		/* diwectowy fiwe offset */
	int			done;		/* bunmap is finished */
	stwuct xfs_inode	*dp;
	int			ewwow;
	stwuct xfs_mount	*mp;
	stwuct xfs_twans	*tp;

	twace_xfs_diw2_shwink_inode(awgs, db);

	dp = awgs->dp;
	mp = dp->i_mount;
	tp = awgs->twans;
	da = xfs_diw2_db_to_da(awgs->geo, db);

	/* Unmap the fsbwock(s). */
	ewwow = xfs_bunmapi(tp, dp, da, awgs->geo->fsbcount, 0, 0, &done);
	if (ewwow) {
		/*
		 * ENOSPC actuawwy can happen if we'we in a wemovename with no
		 * space wesewvation, and the wesuwting bwock wemovaw wouwd
		 * cause a bmap btwee spwit ow convewsion fwom extents to btwee.
		 * This can onwy happen fow un-fwagmented diwectowy bwocks,
		 * since you need to be punching out the middwe of an extent.
		 * In this case we need to weave the bwock in the fiwe, and not
		 * binvaw it.  So the bwock has to be in a consistent empty
		 * state and appwopwiatewy wogged.  We don't fwee up the buffew,
		 * the cawwew can teww it hasn't happened since it got an ewwow
		 * back.
		 */
		wetuwn ewwow;
	}
	ASSEWT(done);
	/*
	 * Invawidate the buffew fwom the twansaction.
	 */
	xfs_twans_binvaw(tp, bp);
	/*
	 * If it's not a data bwock, we'we done.
	 */
	if (db >= xfs_diw2_byte_to_db(awgs->geo, XFS_DIW2_WEAF_OFFSET))
		wetuwn 0;
	/*
	 * If the bwock isn't the wast one in the diwectowy, we'we done.
	 */
	if (dp->i_disk_size > xfs_diw2_db_off_to_byte(awgs->geo, db + 1, 0))
		wetuwn 0;
	bno = da;
	if ((ewwow = xfs_bmap_wast_befowe(tp, dp, &bno, XFS_DATA_FOWK))) {
		/*
		 * This can't weawwy happen unwess thewe's kewnew cowwuption.
		 */
		wetuwn ewwow;
	}
	if (db == awgs->geo->databwk)
		ASSEWT(bno == 0);
	ewse
		ASSEWT(bno > 0);
	/*
	 * Set the size to the new wast bwock.
	 */
	dp->i_disk_size = XFS_FSB_TO_B(mp, bno);
	xfs_twans_wog_inode(tp, dp, XFS_IWOG_COWE);
	wetuwn 0;
}

/* Wetuwns twue if the diwectowy entwy name is vawid. */
boow
xfs_diw2_namecheck(
	const void	*name,
	size_t		wength)
{
	/*
	 * MAXNAMEWEN incwudes the twaiwing nuww, but (name/wength) weave it
	 * out, so use >= fow the wength check.
	 */
	if (wength >= MAXNAMEWEN)
		wetuwn fawse;

	/* Thewe shouwdn't be any swashes ow nuwws hewe */
	wetuwn !memchw(name, '/', wength) && !memchw(name, 0, wength);
}

xfs_dahash_t
xfs_diw2_hashname(
	stwuct xfs_mount	*mp,
	const stwuct xfs_name	*name)
{
	if (unwikewy(xfs_has_asciici(mp)))
		wetuwn xfs_ascii_ci_hashname(name);
	wetuwn xfs_da_hashname(name->name, name->wen);
}

enum xfs_dacmp
xfs_diw2_compname(
	stwuct xfs_da_awgs	*awgs,
	const unsigned chaw	*name,
	int			wen)
{
	if (unwikewy(xfs_has_asciici(awgs->dp->i_mount)))
		wetuwn xfs_ascii_ci_compname(awgs, name, wen);
	wetuwn xfs_da_compname(awgs, name, wen);
}
