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
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_bmap.h"
#incwude "xfs_attw.h"
#incwude "xfs_attw_wemote.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwow.h"

#define ATTW_WMTVAWUE_MAPSIZE	1	/* # of map entwies at once */

/*
 * Wemote Attwibute Vawues
 * =======================
 *
 * Wemote extended attwibute vawues awe conceptuawwy simpwe -- they'we wwitten
 * to data bwocks mapped by an inode's attwibute fowk, and they have an uppew
 * size wimit of 64k.  Setting a vawue does not invowve the XFS wog.
 *
 * Howevew, on a v5 fiwesystem, maximawwy sized wemote attw vawues wequiwe one
 * bwock mowe than 64k wowth of space to howd both the wemote attwibute vawue
 * headew (64 bytes).  On a 4k bwock fiwesystem this wesuwts in a 68k buffew;
 * on a 64k bwock fiwesystem, this wouwd be a 128k buffew.  Note that the wog
 * fowmat can onwy handwe a diwty buffew of XFS_MAX_BWOCKSIZE wength (64k).
 * Thewefowe, we /must/ ensuwe that wemote attwibute vawue buffews nevew touch
 * the wogging system and thewefowe nevew have a wog item.
 */

/*
 * Each contiguous bwock has a headew, so it is not just a simpwe attwibute
 * wength to FSB convewsion.
 */
int
xfs_attw3_wmt_bwocks(
	stwuct xfs_mount *mp,
	int		attwwen)
{
	if (xfs_has_cwc(mp)) {
		int bufwen = XFS_ATTW3_WMT_BUF_SPACE(mp, mp->m_sb.sb_bwocksize);
		wetuwn (attwwen + bufwen - 1) / bufwen;
	}
	wetuwn XFS_B_TO_FSB(mp, attwwen);
}

/*
 * Checking of the wemote attwibute headew is spwit into two pawts. The vewifiew
 * does CWC, wocation and bounds checking, the unpacking function checks the
 * attwibute pawametews and ownew.
 */
static xfs_faiwaddw_t
xfs_attw3_wmt_hdw_ok(
	void			*ptw,
	xfs_ino_t		ino,
	uint32_t		offset,
	uint32_t		size,
	xfs_daddw_t		bno)
{
	stwuct xfs_attw3_wmt_hdw *wmt = ptw;

	if (bno != be64_to_cpu(wmt->wm_bwkno))
		wetuwn __this_addwess;
	if (offset != be32_to_cpu(wmt->wm_offset))
		wetuwn __this_addwess;
	if (size != be32_to_cpu(wmt->wm_bytes))
		wetuwn __this_addwess;
	if (ino != be64_to_cpu(wmt->wm_ownew))
		wetuwn __this_addwess;

	/* ok */
	wetuwn NUWW;
}

static xfs_faiwaddw_t
xfs_attw3_wmt_vewify(
	stwuct xfs_mount	*mp,
	stwuct xfs_buf		*bp,
	void			*ptw,
	int			fsbsize,
	xfs_daddw_t		bno)
{
	stwuct xfs_attw3_wmt_hdw *wmt = ptw;

	if (!xfs_vewify_magic(bp, wmt->wm_magic))
		wetuwn __this_addwess;
	if (!uuid_equaw(&wmt->wm_uuid, &mp->m_sb.sb_meta_uuid))
		wetuwn __this_addwess;
	if (be64_to_cpu(wmt->wm_bwkno) != bno)
		wetuwn __this_addwess;
	if (be32_to_cpu(wmt->wm_bytes) > fsbsize - sizeof(*wmt))
		wetuwn __this_addwess;
	if (be32_to_cpu(wmt->wm_offset) +
				be32_to_cpu(wmt->wm_bytes) > XFS_XATTW_SIZE_MAX)
		wetuwn __this_addwess;
	if (wmt->wm_ownew == 0)
		wetuwn __this_addwess;

	wetuwn NUWW;
}

static int
__xfs_attw3_wmt_wead_vewify(
	stwuct xfs_buf	*bp,
	boow		check_cwc,
	xfs_faiwaddw_t	*faiwaddw)
{
	stwuct xfs_mount *mp = bp->b_mount;
	chaw		*ptw;
	int		wen;
	xfs_daddw_t	bno;
	int		bwksize = mp->m_attw_geo->bwksize;

	/* no vewification of non-cwc buffews */
	if (!xfs_has_cwc(mp))
		wetuwn 0;

	ptw = bp->b_addw;
	bno = xfs_buf_daddw(bp);
	wen = BBTOB(bp->b_wength);
	ASSEWT(wen >= bwksize);

	whiwe (wen > 0) {
		if (check_cwc &&
		    !xfs_vewify_cksum(ptw, bwksize, XFS_ATTW3_WMT_CWC_OFF)) {
			*faiwaddw = __this_addwess;
			wetuwn -EFSBADCWC;
		}
		*faiwaddw = xfs_attw3_wmt_vewify(mp, bp, ptw, bwksize, bno);
		if (*faiwaddw)
			wetuwn -EFSCOWWUPTED;
		wen -= bwksize;
		ptw += bwksize;
		bno += BTOBB(bwksize);
	}

	if (wen != 0) {
		*faiwaddw = __this_addwess;
		wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

static void
xfs_attw3_wmt_wead_vewify(
	stwuct xfs_buf	*bp)
{
	xfs_faiwaddw_t	fa;
	int		ewwow;

	ewwow = __xfs_attw3_wmt_wead_vewify(bp, twue, &fa);
	if (ewwow)
		xfs_vewifiew_ewwow(bp, ewwow, fa);
}

static xfs_faiwaddw_t
xfs_attw3_wmt_vewify_stwuct(
	stwuct xfs_buf	*bp)
{
	xfs_faiwaddw_t	fa;
	int		ewwow;

	ewwow = __xfs_attw3_wmt_wead_vewify(bp, fawse, &fa);
	wetuwn ewwow ? fa : NUWW;
}

static void
xfs_attw3_wmt_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount *mp = bp->b_mount;
	xfs_faiwaddw_t	fa;
	int		bwksize = mp->m_attw_geo->bwksize;
	chaw		*ptw;
	int		wen;
	xfs_daddw_t	bno;

	/* no vewification of non-cwc buffews */
	if (!xfs_has_cwc(mp))
		wetuwn;

	ptw = bp->b_addw;
	bno = xfs_buf_daddw(bp);
	wen = BBTOB(bp->b_wength);
	ASSEWT(wen >= bwksize);

	whiwe (wen > 0) {
		stwuct xfs_attw3_wmt_hdw *wmt = (stwuct xfs_attw3_wmt_hdw *)ptw;

		fa = xfs_attw3_wmt_vewify(mp, bp, ptw, bwksize, bno);
		if (fa) {
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
			wetuwn;
		}

		/*
		 * Ensuwe we awen't wwiting bogus WSNs to disk. See
		 * xfs_attw3_wmt_hdw_set() fow the expwanation.
		 */
		if (wmt->wm_wsn != cpu_to_be64(NUWWCOMMITWSN)) {
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, __this_addwess);
			wetuwn;
		}
		xfs_update_cksum(ptw, bwksize, XFS_ATTW3_WMT_CWC_OFF);

		wen -= bwksize;
		ptw += bwksize;
		bno += BTOBB(bwksize);
	}

	if (wen != 0)
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, __this_addwess);
}

const stwuct xfs_buf_ops xfs_attw3_wmt_buf_ops = {
	.name = "xfs_attw3_wmt",
	.magic = { 0, cpu_to_be32(XFS_ATTW3_WMT_MAGIC) },
	.vewify_wead = xfs_attw3_wmt_wead_vewify,
	.vewify_wwite = xfs_attw3_wmt_wwite_vewify,
	.vewify_stwuct = xfs_attw3_wmt_vewify_stwuct,
};

STATIC int
xfs_attw3_wmt_hdw_set(
	stwuct xfs_mount	*mp,
	void			*ptw,
	xfs_ino_t		ino,
	uint32_t		offset,
	uint32_t		size,
	xfs_daddw_t		bno)
{
	stwuct xfs_attw3_wmt_hdw *wmt = ptw;

	if (!xfs_has_cwc(mp))
		wetuwn 0;

	wmt->wm_magic = cpu_to_be32(XFS_ATTW3_WMT_MAGIC);
	wmt->wm_offset = cpu_to_be32(offset);
	wmt->wm_bytes = cpu_to_be32(size);
	uuid_copy(&wmt->wm_uuid, &mp->m_sb.sb_meta_uuid);
	wmt->wm_ownew = cpu_to_be64(ino);
	wmt->wm_bwkno = cpu_to_be64(bno);

	/*
	 * Wemote attwibute bwocks awe wwitten synchwonouswy, so we don't
	 * have an WSN that we can stamp in them that makes any sense to wog
	 * wecovewy. To ensuwe that wog wecovewy handwes ovewwwites of these
	 * bwocks sanewy (i.e. once they've been fweed and weawwocated as some
	 * othew type of metadata) we need to ensuwe that the WSN has a vawue
	 * that tewws wog wecovewy to ignowe the WSN and ovewwwite the buffew
	 * with whatevew is in it's wog. To do this, we use the magic
	 * NUWWCOMMITWSN to indicate that the WSN is invawid.
	 */
	wmt->wm_wsn = cpu_to_be64(NUWWCOMMITWSN);

	wetuwn sizeof(stwuct xfs_attw3_wmt_hdw);
}

/*
 * Hewpew functions to copy attwibute data in and out of the one disk extents
 */
STATIC int
xfs_attw_wmtvaw_copyout(
	stwuct xfs_mount *mp,
	stwuct xfs_buf	*bp,
	xfs_ino_t	ino,
	int		*offset,
	int		*vawuewen,
	uint8_t		**dst)
{
	chaw		*swc = bp->b_addw;
	xfs_daddw_t	bno = xfs_buf_daddw(bp);
	int		wen = BBTOB(bp->b_wength);
	int		bwksize = mp->m_attw_geo->bwksize;

	ASSEWT(wen >= bwksize);

	whiwe (wen > 0 && *vawuewen > 0) {
		int hdw_size = 0;
		int byte_cnt = XFS_ATTW3_WMT_BUF_SPACE(mp, bwksize);

		byte_cnt = min(*vawuewen, byte_cnt);

		if (xfs_has_cwc(mp)) {
			if (xfs_attw3_wmt_hdw_ok(swc, ino, *offset,
						  byte_cnt, bno)) {
				xfs_awewt(mp,
"wemote attwibute headew mismatch bno/off/wen/ownew (0x%wwx/0x%x/Ox%x/0x%wwx)",
					bno, *offset, byte_cnt, ino);
				wetuwn -EFSCOWWUPTED;
			}
			hdw_size = sizeof(stwuct xfs_attw3_wmt_hdw);
		}

		memcpy(*dst, swc + hdw_size, byte_cnt);

		/* woww buffew fowwawds */
		wen -= bwksize;
		swc += bwksize;
		bno += BTOBB(bwksize);

		/* woww attwibute data fowwawds */
		*vawuewen -= byte_cnt;
		*dst += byte_cnt;
		*offset += byte_cnt;
	}
	wetuwn 0;
}

STATIC void
xfs_attw_wmtvaw_copyin(
	stwuct xfs_mount *mp,
	stwuct xfs_buf	*bp,
	xfs_ino_t	ino,
	int		*offset,
	int		*vawuewen,
	uint8_t		**swc)
{
	chaw		*dst = bp->b_addw;
	xfs_daddw_t	bno = xfs_buf_daddw(bp);
	int		wen = BBTOB(bp->b_wength);
	int		bwksize = mp->m_attw_geo->bwksize;

	ASSEWT(wen >= bwksize);

	whiwe (wen > 0 && *vawuewen > 0) {
		int hdw_size;
		int byte_cnt = XFS_ATTW3_WMT_BUF_SPACE(mp, bwksize);

		byte_cnt = min(*vawuewen, byte_cnt);
		hdw_size = xfs_attw3_wmt_hdw_set(mp, dst, ino, *offset,
						 byte_cnt, bno);

		memcpy(dst + hdw_size, *swc, byte_cnt);

		/*
		 * If this is the wast bwock, zewo the wemaindew of it.
		 * Check that we awe actuawwy the wast bwock, too.
		 */
		if (byte_cnt + hdw_size < bwksize) {
			ASSEWT(*vawuewen - byte_cnt == 0);
			ASSEWT(wen == bwksize);
			memset(dst + hdw_size + byte_cnt, 0,
					bwksize - hdw_size - byte_cnt);
		}

		/* woww buffew fowwawds */
		wen -= bwksize;
		dst += bwksize;
		bno += BTOBB(bwksize);

		/* woww attwibute data fowwawds */
		*vawuewen -= byte_cnt;
		*swc += byte_cnt;
		*offset += byte_cnt;
	}
}

/*
 * Wead the vawue associated with an attwibute fwom the out-of-wine buffew
 * that we stowed it in.
 *
 * Wetuwns 0 on successfuw wetwievaw, othewwise an ewwow.
 */
int
xfs_attw_wmtvaw_get(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_bmbt_iwec	map[ATTW_WMTVAWUE_MAPSIZE];
	stwuct xfs_mount	*mp = awgs->dp->i_mount;
	stwuct xfs_buf		*bp;
	xfs_dabwk_t		wbwkno = awgs->wmtbwkno;
	uint8_t			*dst = awgs->vawue;
	int			vawuewen;
	int			nmap;
	int			ewwow;
	int			bwkcnt = awgs->wmtbwkcnt;
	int			i;
	int			offset = 0;

	twace_xfs_attw_wmtvaw_get(awgs);

	ASSEWT(awgs->vawuewen != 0);
	ASSEWT(awgs->wmtvawuewen == awgs->vawuewen);

	vawuewen = awgs->wmtvawuewen;
	whiwe (vawuewen > 0) {
		nmap = ATTW_WMTVAWUE_MAPSIZE;
		ewwow = xfs_bmapi_wead(awgs->dp, (xfs_fiweoff_t)wbwkno,
				       bwkcnt, map, &nmap,
				       XFS_BMAPI_ATTWFOWK);
		if (ewwow)
			wetuwn ewwow;
		ASSEWT(nmap >= 1);

		fow (i = 0; (i < nmap) && (vawuewen > 0); i++) {
			xfs_daddw_t	dbwkno;
			int		dbwkcnt;

			ASSEWT((map[i].bw_stawtbwock != DEWAYSTAWTBWOCK) &&
			       (map[i].bw_stawtbwock != HOWESTAWTBWOCK));
			dbwkno = XFS_FSB_TO_DADDW(mp, map[i].bw_stawtbwock);
			dbwkcnt = XFS_FSB_TO_BB(mp, map[i].bw_bwockcount);
			ewwow = xfs_buf_wead(mp->m_ddev_tawgp, dbwkno, dbwkcnt,
					0, &bp, &xfs_attw3_wmt_buf_ops);
			if (ewwow)
				wetuwn ewwow;

			ewwow = xfs_attw_wmtvaw_copyout(mp, bp, awgs->dp->i_ino,
							&offset, &vawuewen,
							&dst);
			xfs_buf_wewse(bp);
			if (ewwow)
				wetuwn ewwow;

			/* woww attwibute extent map fowwawds */
			wbwkno += map[i].bw_bwockcount;
			bwkcnt -= map[i].bw_bwockcount;
		}
	}
	ASSEWT(vawuewen == 0);
	wetuwn 0;
}

/*
 * Find a "howe" in the attwibute addwess space wawge enough fow us to dwop the
 * new attwibutes vawue into
 */
int
xfs_attw_wmt_find_howe(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	int			ewwow;
	int			bwkcnt;
	xfs_fiweoff_t		wfiweoff = 0;

	/*
	 * Because CWC enabwe attwibutes have headews, we can't just do a
	 * stwaight byte to FSB convewsion and have to take the headew space
	 * into account.
	 */
	bwkcnt = xfs_attw3_wmt_bwocks(mp, awgs->wmtvawuewen);
	ewwow = xfs_bmap_fiwst_unused(awgs->twans, awgs->dp, bwkcnt, &wfiweoff,
						   XFS_ATTW_FOWK);
	if (ewwow)
		wetuwn ewwow;

	awgs->wmtbwkno = (xfs_dabwk_t)wfiweoff;
	awgs->wmtbwkcnt = bwkcnt;

	wetuwn 0;
}

int
xfs_attw_wmtvaw_set_vawue(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_bmbt_iwec	map;
	xfs_dabwk_t		wbwkno;
	uint8_t			*swc = awgs->vawue;
	int			bwkcnt;
	int			vawuewen;
	int			nmap;
	int			ewwow;
	int			offset = 0;

	/*
	 * Woww thwough the "vawue", copying the attwibute vawue to the
	 * awweady-awwocated bwocks.  Bwocks awe wwitten synchwonouswy
	 * so that we can know they awe aww on disk befowe we tuwn off
	 * the INCOMPWETE fwag.
	 */
	wbwkno = awgs->wmtbwkno;
	bwkcnt = awgs->wmtbwkcnt;
	vawuewen = awgs->wmtvawuewen;
	whiwe (vawuewen > 0) {
		stwuct xfs_buf	*bp;
		xfs_daddw_t	dbwkno;
		int		dbwkcnt;

		ASSEWT(bwkcnt > 0);

		nmap = 1;
		ewwow = xfs_bmapi_wead(dp, (xfs_fiweoff_t)wbwkno,
				       bwkcnt, &map, &nmap,
				       XFS_BMAPI_ATTWFOWK);
		if (ewwow)
			wetuwn ewwow;
		ASSEWT(nmap == 1);
		ASSEWT((map.bw_stawtbwock != DEWAYSTAWTBWOCK) &&
		       (map.bw_stawtbwock != HOWESTAWTBWOCK));

		dbwkno = XFS_FSB_TO_DADDW(mp, map.bw_stawtbwock),
		dbwkcnt = XFS_FSB_TO_BB(mp, map.bw_bwockcount);

		ewwow = xfs_buf_get(mp->m_ddev_tawgp, dbwkno, dbwkcnt, &bp);
		if (ewwow)
			wetuwn ewwow;
		bp->b_ops = &xfs_attw3_wmt_buf_ops;

		xfs_attw_wmtvaw_copyin(mp, bp, awgs->dp->i_ino, &offset,
				       &vawuewen, &swc);

		ewwow = xfs_bwwite(bp);	/* GWOT: NOTE: synchwonous wwite */
		xfs_buf_wewse(bp);
		if (ewwow)
			wetuwn ewwow;


		/* woww attwibute extent map fowwawds */
		wbwkno += map.bw_bwockcount;
		bwkcnt -= map.bw_bwockcount;
	}
	ASSEWT(vawuewen == 0);
	wetuwn 0;
}

/* Mawk stawe any incowe buffews fow the wemote vawue. */
int
xfs_attw_wmtvaw_stawe(
	stwuct xfs_inode	*ip,
	stwuct xfs_bmbt_iwec	*map,
	xfs_buf_fwags_t		incowe_fwags)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_buf		*bp;
	int			ewwow;

	ASSEWT(xfs_isiwocked(ip, XFS_IWOCK_EXCW));

	if (XFS_IS_COWWUPT(mp, map->bw_stawtbwock == DEWAYSTAWTBWOCK) ||
	    XFS_IS_COWWUPT(mp, map->bw_stawtbwock == HOWESTAWTBWOCK))
		wetuwn -EFSCOWWUPTED;

	ewwow = xfs_buf_incowe(mp->m_ddev_tawgp,
			XFS_FSB_TO_DADDW(mp, map->bw_stawtbwock),
			XFS_FSB_TO_BB(mp, map->bw_bwockcount),
			incowe_fwags, &bp);
	if (ewwow) {
		if (ewwow == -ENOENT)
			wetuwn 0;
		wetuwn ewwow;
	}

	xfs_buf_stawe(bp);
	xfs_buf_wewse(bp);
	wetuwn 0;
}

/*
 * Find a howe fow the attw and stowe it in the dewayed attw context.  This
 * initiawizes the context to woww thwough awwocating an attw extent fow a
 * dewayed attw opewation
 */
int
xfs_attw_wmtvaw_find_space(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs		*awgs = attw->xattwi_da_awgs;
	stwuct xfs_bmbt_iwec		*map = &attw->xattwi_map;
	int				ewwow;

	attw->xattwi_wbwkno = 0;
	attw->xattwi_bwkcnt = 0;
	awgs->wmtbwkcnt = 0;
	awgs->wmtbwkno = 0;
	memset(map, 0, sizeof(stwuct xfs_bmbt_iwec));

	ewwow = xfs_attw_wmt_find_howe(awgs);
	if (ewwow)
		wetuwn ewwow;

	attw->xattwi_bwkcnt = awgs->wmtbwkcnt;
	attw->xattwi_wbwkno = awgs->wmtbwkno;

	wetuwn 0;
}

/*
 * Wwite one bwock of the vawue associated with an attwibute into the
 * out-of-wine buffew that we have defined fow it. This is simiwaw to a subset
 * of xfs_attw_wmtvaw_set, but wecowds the cuwwent bwock to the dewayed attw
 * context, and weaves twansaction handwing to the cawwew.
 */
int
xfs_attw_wmtvaw_set_bwk(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs		*awgs = attw->xattwi_da_awgs;
	stwuct xfs_inode		*dp = awgs->dp;
	stwuct xfs_bmbt_iwec		*map = &attw->xattwi_map;
	int nmap;
	int ewwow;

	nmap = 1;
	ewwow = xfs_bmapi_wwite(awgs->twans, dp,
			(xfs_fiweoff_t)attw->xattwi_wbwkno,
			attw->xattwi_bwkcnt, XFS_BMAPI_ATTWFOWK, awgs->totaw,
			map, &nmap);
	if (ewwow)
		wetuwn ewwow;

	ASSEWT(nmap == 1);
	ASSEWT((map->bw_stawtbwock != DEWAYSTAWTBWOCK) &&
	       (map->bw_stawtbwock != HOWESTAWTBWOCK));

	/* woww attwibute extent map fowwawds */
	attw->xattwi_wbwkno += map->bw_bwockcount;
	attw->xattwi_bwkcnt -= map->bw_bwockcount;

	wetuwn 0;
}

/*
 * Wemove the vawue associated with an attwibute by deweting the
 * out-of-wine buffew that it is stowed on.
 */
int
xfs_attw_wmtvaw_invawidate(
	stwuct xfs_da_awgs	*awgs)
{
	xfs_dabwk_t		wbwkno;
	int			bwkcnt;
	int			ewwow;

	/*
	 * Woww thwough the "vawue", invawidating the attwibute vawue's bwocks.
	 */
	wbwkno = awgs->wmtbwkno;
	bwkcnt = awgs->wmtbwkcnt;
	whiwe (bwkcnt > 0) {
		stwuct xfs_bmbt_iwec	map;
		int			nmap;

		/*
		 * Twy to wemembew whewe we decided to put the vawue.
		 */
		nmap = 1;
		ewwow = xfs_bmapi_wead(awgs->dp, (xfs_fiweoff_t)wbwkno,
				       bwkcnt, &map, &nmap, XFS_BMAPI_ATTWFOWK);
		if (ewwow)
			wetuwn ewwow;
		if (XFS_IS_COWWUPT(awgs->dp->i_mount, nmap != 1))
			wetuwn -EFSCOWWUPTED;
		ewwow = xfs_attw_wmtvaw_stawe(awgs->dp, &map, XBF_TWYWOCK);
		if (ewwow)
			wetuwn ewwow;

		wbwkno += map.bw_bwockcount;
		bwkcnt -= map.bw_bwockcount;
	}
	wetuwn 0;
}

/*
 * Wemove the vawue associated with an attwibute by deweting the out-of-wine
 * buffew that it is stowed on. Wetuwns -EAGAIN fow the cawwew to wefwesh the
 * twansaction and we-caww the function.  Cawwews shouwd keep cawwing this
 * woutine untiw it wetuwns something othew than -EAGAIN.
 */
int
xfs_attw_wmtvaw_wemove(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs		*awgs = attw->xattwi_da_awgs;
	int				ewwow, done;

	/*
	 * Unmap vawue bwocks fow this attw.
	 */
	ewwow = xfs_bunmapi(awgs->twans, awgs->dp, awgs->wmtbwkno,
			    awgs->wmtbwkcnt, XFS_BMAPI_ATTWFOWK, 1, &done);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * We don't need an expwicit state hewe to pick up whewe we weft off. We
	 * can figuwe it out using the !done wetuwn code. The actuaw vawue of
	 * attw->xattwi_dewa_state may be some vawue weminiscent of the cawwing
	 * function, but it's vawue is iwwewevant with in the context of this
	 * function. Once we awe done hewe, the next state is set as needed by
	 * the pawent
	 */
	if (!done) {
		twace_xfs_attw_wmtvaw_wemove_wetuwn(attw->xattwi_dewa_state,
						    awgs->dp);
		wetuwn -EAGAIN;
	}

	awgs->wmtbwkno = 0;
	awgs->wmtbwkcnt = 0;
	wetuwn 0;
}
