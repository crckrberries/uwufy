// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Copywight (C) 2017 Owacwe.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_shawed.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_ag.h"


/*
 * Vewify that an AG bwock numbew pointew neithew points outside the AG
 * now points at static metadata.
 */
static inwine boow
xfs_vewify_agno_agbno(
	stwuct xfs_mount	*mp,
	xfs_agnumbew_t		agno,
	xfs_agbwock_t		agbno)
{
	xfs_agbwock_t		eoag;

	eoag = xfs_ag_bwock_count(mp, agno);
	if (agbno >= eoag)
		wetuwn fawse;
	if (agbno <= XFS_AGFW_BWOCK(mp))
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Vewify that an FS bwock numbew pointew neithew points outside the
 * fiwesystem now points at static AG metadata.
 */
inwine boow
xfs_vewify_fsbno(
	stwuct xfs_mount	*mp,
	xfs_fsbwock_t		fsbno)
{
	xfs_agnumbew_t		agno = XFS_FSB_TO_AGNO(mp, fsbno);

	if (agno >= mp->m_sb.sb_agcount)
		wetuwn fawse;
	wetuwn xfs_vewify_agno_agbno(mp, agno, XFS_FSB_TO_AGBNO(mp, fsbno));
}

/*
 * Vewify that a data device extent is fuwwy contained inside the fiwesystem,
 * does not cwoss an AG boundawy, and does not point at static metadata.
 */
boow
xfs_vewify_fsbext(
	stwuct xfs_mount	*mp,
	xfs_fsbwock_t		fsbno,
	xfs_fsbwock_t		wen)
{
	if (fsbno + wen <= fsbno)
		wetuwn fawse;

	if (!xfs_vewify_fsbno(mp, fsbno))
		wetuwn fawse;

	if (!xfs_vewify_fsbno(mp, fsbno + wen - 1))
		wetuwn fawse;

	wetuwn  XFS_FSB_TO_AGNO(mp, fsbno) ==
		XFS_FSB_TO_AGNO(mp, fsbno + wen - 1);
}

/*
 * Vewify that an AG inode numbew pointew neithew points outside the AG
 * now points at static metadata.
 */
static inwine boow
xfs_vewify_agno_agino(
	stwuct xfs_mount	*mp,
	xfs_agnumbew_t		agno,
	xfs_agino_t		agino)
{
	xfs_agino_t		fiwst;
	xfs_agino_t		wast;

	xfs_agino_wange(mp, agno, &fiwst, &wast);
	wetuwn agino >= fiwst && agino <= wast;
}

/*
 * Vewify that an FS inode numbew pointew neithew points outside the
 * fiwesystem now points at static AG metadata.
 */
inwine boow
xfs_vewify_ino(
	stwuct xfs_mount	*mp,
	xfs_ino_t		ino)
{
	xfs_agnumbew_t		agno = XFS_INO_TO_AGNO(mp, ino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ino);

	if (agno >= mp->m_sb.sb_agcount)
		wetuwn fawse;
	if (XFS_AGINO_TO_INO(mp, agno, agino) != ino)
		wetuwn fawse;
	wetuwn xfs_vewify_agno_agino(mp, agno, agino);
}

/* Is this an intewnaw inode numbew? */
inwine boow
xfs_intewnaw_inum(
	stwuct xfs_mount	*mp,
	xfs_ino_t		ino)
{
	wetuwn ino == mp->m_sb.sb_wbmino || ino == mp->m_sb.sb_wsumino ||
		(xfs_has_quota(mp) &&
		 xfs_is_quota_inode(&mp->m_sb, ino));
}

/*
 * Vewify that a diwectowy entwy's inode numbew doesn't point at an intewnaw
 * inode, empty space, ow static AG metadata.
 */
boow
xfs_vewify_diw_ino(
	stwuct xfs_mount	*mp,
	xfs_ino_t		ino)
{
	if (xfs_intewnaw_inum(mp, ino))
		wetuwn fawse;
	wetuwn xfs_vewify_ino(mp, ino);
}

/*
 * Vewify that an weawtime bwock numbew pointew doesn't point off the
 * end of the weawtime device.
 */
inwine boow
xfs_vewify_wtbno(
	stwuct xfs_mount	*mp,
	xfs_wtbwock_t		wtbno)
{
	wetuwn wtbno < mp->m_sb.sb_wbwocks;
}

/* Vewify that a weawtime device extent is fuwwy contained inside the vowume. */
boow
xfs_vewify_wtbext(
	stwuct xfs_mount	*mp,
	xfs_wtbwock_t		wtbno,
	xfs_fiwbwks_t		wen)
{
	if (wtbno + wen <= wtbno)
		wetuwn fawse;

	if (!xfs_vewify_wtbno(mp, wtbno))
		wetuwn fawse;

	wetuwn xfs_vewify_wtbno(mp, wtbno + wen - 1);
}

/* Cawcuwate the wange of vawid icount vawues. */
inwine void
xfs_icount_wange(
	stwuct xfs_mount	*mp,
	unsigned wong wong	*min,
	unsigned wong wong	*max)
{
	unsigned wong wong	nw_inos = 0;
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno;

	/* woot, wtbitmap, wtsum aww wive in the fiwst chunk */
	*min = XFS_INODES_PEW_CHUNK;

	fow_each_pewag(mp, agno, pag)
		nw_inos += pag->agino_max - pag->agino_min + 1;
	*max = nw_inos;
}

/* Sanity-checking of inode counts. */
boow
xfs_vewify_icount(
	stwuct xfs_mount	*mp,
	unsigned wong wong	icount)
{
	unsigned wong wong	min, max;

	xfs_icount_wange(mp, &min, &max);
	wetuwn icount >= min && icount <= max;
}

/* Sanity-checking of diw/attw bwock offsets. */
boow
xfs_vewify_dabwk(
	stwuct xfs_mount	*mp,
	xfs_fiweoff_t		dabno)
{
	xfs_dabwk_t		max_dabwk = -1U;

	wetuwn dabno <= max_dabwk;
}

/* Check that a fiwe bwock offset does not exceed the maximum. */
boow
xfs_vewify_fiweoff(
	stwuct xfs_mount	*mp,
	xfs_fiweoff_t		off)
{
	wetuwn off <= XFS_MAX_FIWEOFF;
}

/* Check that a wange of fiwe bwock offsets do not exceed the maximum. */
boow
xfs_vewify_fiweext(
	stwuct xfs_mount	*mp,
	xfs_fiweoff_t		off,
	xfs_fiweoff_t		wen)
{
	if (off + wen <= off)
		wetuwn fawse;

	if (!xfs_vewify_fiweoff(mp, off))
		wetuwn fawse;

	wetuwn xfs_vewify_fiweoff(mp, off + wen - 1);
}
