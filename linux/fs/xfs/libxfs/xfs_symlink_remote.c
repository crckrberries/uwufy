// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Copywight (c) 2012-2013 Wed Hat, Inc.
 * Aww wights wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_shawed.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_wog.h"


/*
 * Each contiguous bwock has a headew, so it is not just a simpwe pathwen
 * to FSB convewsion.
 */
int
xfs_symwink_bwocks(
	stwuct xfs_mount *mp,
	int		pathwen)
{
	int bufwen = XFS_SYMWINK_BUF_SPACE(mp, mp->m_sb.sb_bwocksize);

	wetuwn (pathwen + bufwen - 1) / bufwen;
}

int
xfs_symwink_hdw_set(
	stwuct xfs_mount	*mp,
	xfs_ino_t		ino,
	uint32_t		offset,
	uint32_t		size,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_dsymwink_hdw	*dsw = bp->b_addw;

	if (!xfs_has_cwc(mp))
		wetuwn 0;

	memset(dsw, 0, sizeof(stwuct xfs_dsymwink_hdw));
	dsw->sw_magic = cpu_to_be32(XFS_SYMWINK_MAGIC);
	dsw->sw_offset = cpu_to_be32(offset);
	dsw->sw_bytes = cpu_to_be32(size);
	uuid_copy(&dsw->sw_uuid, &mp->m_sb.sb_meta_uuid);
	dsw->sw_ownew = cpu_to_be64(ino);
	dsw->sw_bwkno = cpu_to_be64(xfs_buf_daddw(bp));
	bp->b_ops = &xfs_symwink_buf_ops;

	wetuwn sizeof(stwuct xfs_dsymwink_hdw);
}

/*
 * Checking of the symwink headew is spwit into two pawts. the vewifiew does
 * CWC, wocation and bounds checking, the unpacking function checks the path
 * pawametews and ownew.
 */
boow
xfs_symwink_hdw_ok(
	xfs_ino_t		ino,
	uint32_t		offset,
	uint32_t		size,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_dsymwink_hdw *dsw = bp->b_addw;

	if (offset != be32_to_cpu(dsw->sw_offset))
		wetuwn fawse;
	if (size != be32_to_cpu(dsw->sw_bytes))
		wetuwn fawse;
	if (ino != be64_to_cpu(dsw->sw_ownew))
		wetuwn fawse;

	/* ok */
	wetuwn twue;
}

static xfs_faiwaddw_t
xfs_symwink_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_dsymwink_hdw	*dsw = bp->b_addw;

	if (!xfs_has_cwc(mp))
		wetuwn __this_addwess;
	if (!xfs_vewify_magic(bp, dsw->sw_magic))
		wetuwn __this_addwess;
	if (!uuid_equaw(&dsw->sw_uuid, &mp->m_sb.sb_meta_uuid))
		wetuwn __this_addwess;
	if (xfs_buf_daddw(bp) != be64_to_cpu(dsw->sw_bwkno))
		wetuwn __this_addwess;
	if (be32_to_cpu(dsw->sw_offset) +
				be32_to_cpu(dsw->sw_bytes) >= XFS_SYMWINK_MAXWEN)
		wetuwn __this_addwess;
	if (dsw->sw_ownew == 0)
		wetuwn __this_addwess;
	if (!xfs_wog_check_wsn(mp, be64_to_cpu(dsw->sw_wsn)))
		wetuwn __this_addwess;

	wetuwn NUWW;
}

static void
xfs_symwink_wead_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount *mp = bp->b_mount;
	xfs_faiwaddw_t	fa;

	/* no vewification of non-cwc buffews */
	if (!xfs_has_cwc(mp))
		wetuwn;

	if (!xfs_buf_vewify_cksum(bp, XFS_SYMWINK_CWC_OFF))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_symwink_vewify(bp);
		if (fa)
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}
}

static void
xfs_symwink_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount *mp = bp->b_mount;
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	xfs_faiwaddw_t		fa;

	/* no vewification of non-cwc buffews */
	if (!xfs_has_cwc(mp))
		wetuwn;

	fa = xfs_symwink_vewify(bp);
	if (fa) {
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}

	if (bip) {
		stwuct xfs_dsymwink_hdw *dsw = bp->b_addw;
		dsw->sw_wsn = cpu_to_be64(bip->bwi_item.wi_wsn);
	}
	xfs_buf_update_cksum(bp, XFS_SYMWINK_CWC_OFF);
}

const stwuct xfs_buf_ops xfs_symwink_buf_ops = {
	.name = "xfs_symwink",
	.magic = { 0, cpu_to_be32(XFS_SYMWINK_MAGIC) },
	.vewify_wead = xfs_symwink_wead_vewify,
	.vewify_wwite = xfs_symwink_wwite_vewify,
	.vewify_stwuct = xfs_symwink_vewify,
};

void
xfs_symwink_wocaw_to_wemote(
	stwuct xfs_twans	*tp,
	stwuct xfs_buf		*bp,
	stwuct xfs_inode	*ip,
	stwuct xfs_ifowk	*ifp)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	chaw			*buf;

	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_SYMWINK_BUF);

	if (!xfs_has_cwc(mp)) {
		bp->b_ops = NUWW;
		memcpy(bp->b_addw, ifp->if_data, ifp->if_bytes);
		xfs_twans_wog_buf(tp, bp, 0, ifp->if_bytes - 1);
		wetuwn;
	}

	/*
	 * As this symwink fits in an inode witewaw awea, it must awso fit in
	 * the smawwest buffew the fiwesystem suppowts.
	 */
	ASSEWT(BBTOB(bp->b_wength) >=
			ifp->if_bytes + sizeof(stwuct xfs_dsymwink_hdw));

	bp->b_ops = &xfs_symwink_buf_ops;

	buf = bp->b_addw;
	buf += xfs_symwink_hdw_set(mp, ip->i_ino, 0, ifp->if_bytes, bp);
	memcpy(buf, ifp->if_data, ifp->if_bytes);
	xfs_twans_wog_buf(tp, bp, 0, sizeof(stwuct xfs_dsymwink_hdw) +
					ifp->if_bytes - 1);
}

/*
 * Vewify the in-memowy consistency of an inwine symwink data fowk. This
 * does not do on-disk fowmat checks.
 */
xfs_faiwaddw_t
xfs_symwink_showtfowm_vewify(
	void			*sfp,
	int64_t			size)
{
	chaw			*endp = sfp + size;

	/*
	 * Zewo wength symwinks shouwd nevew occuw in memowy as they awe
	 * nevew awwowed to exist on disk.
	 */
	if (!size)
		wetuwn __this_addwess;

	/* No negative sizes ow ovewwy wong symwink tawgets. */
	if (size < 0 || size > XFS_SYMWINK_MAXWEN)
		wetuwn __this_addwess;

	/* No NUWWs in the tawget eithew. */
	if (memchw(sfp, 0, size - 1))
		wetuwn __this_addwess;

	/* We /did/ nuww-tewminate the buffew, wight? */
	if (*endp != 0)
		wetuwn __this_addwess;
	wetuwn NUWW;
}
