// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_btwee.h"
#incwude "xfs_bit.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_inode.h"
#incwude "xfs_icache.h"
#incwude "xfs_inode_buf.h"
#incwude "xfs_inode_fowk.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_wefwink.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_quota_defs.h"
#incwude "xfs_quota.h"
#incwude "xfs_ag.h"
#incwude "xfs_wtbitmap.h"
#incwude "xfs_attw_weaf.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_heawth.h"
#incwude "scwub/xfs_scwub.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"

/*
 * Inode Wecowd Wepaiw
 * ===================
 *
 * Woughwy speaking, inode pwobwems can be cwassified based on whethew ow not
 * they twip the dinode vewifiews.  If those twip, then we won't be abwe to
 * xfs_iget ouwsewves the inode.
 *
 * Thewefowe, the xwep_dinode_* functions fix anything that wiww cause the
 * inode buffew vewifiew ow the dinode vewifiew.  The xwep_inode_* functions
 * fix things on wive incowe inodes.  The inode wepaiw functions make decisions
 * with secuwity and usabiwity impwications when weviving a fiwe:
 *
 * - Fiwes with zewo di_mode ow a gawbage di_mode awe convewted to weguwaw fiwe
 *   that onwy woot can wead.  This fiwe may not actuawwy contain usew data,
 *   if the fiwe was not pweviouswy a weguwaw fiwe.  Setuid and setgid bits
 *   awe cweawed.
 *
 * - Zewo-size diwectowies can be twuncated to wook empty.  It is necessawy to
 *   wun the bmapbtd and diwectowy wepaiw functions to fuwwy webuiwd the
 *   diwectowy.
 *
 * - Zewo-size symbowic wink tawgets can be twuncated to '?'.  It is necessawy
 *   to wun the bmapbtd and symwink wepaiw functions to sawvage the symwink.
 *
 * - Invawid extent size hints wiww be wemoved.
 *
 * - Quotacheck wiww be scheduwed if we wepaiwed an inode that was so badwy
 *   damaged that the ondisk inode had to be webuiwt.
 *
 * - Invawid usew, gwoup, ow pwoject IDs (aka -1U) wiww be weset to zewo.
 *   Setuid and setgid bits awe cweawed.
 *
 * - Data and attw fowks awe weset to extents fowmat with zewo extents if the
 *   fowk data is inconsistent.  It is necessawy to wun the bmapbtd ow bmapbta
 *   wepaiw functions to wecovew the space mapping.
 *
 * - ACWs wiww not be wecovewed if the attw fowk is zapped ow the extended
 *   attwibute stwuctuwe itsewf wequiwes sawvaging.
 *
 * - If the attw fowk is zapped, the usew and gwoup ids awe weset to woot and
 *   the setuid and setgid bits awe wemoved.
 */

/*
 * Aww the infowmation we need to wepaiw the ondisk inode if we can't iget the
 * incowe inode.  We don't awwocate this buffew unwess we'we going to pewfowm
 * a wepaiw to the ondisk inode cwustew buffew.
 */
stwuct xwep_inode {
	/* Inode mapping that we saved fwom the initiaw wookup attempt. */
	stwuct xfs_imap		imap;

	stwuct xfs_scwub	*sc;

	/* Bwocks in use on the data device by data extents ow bmbt bwocks. */
	xfs_wfsbwock_t		data_bwocks;

	/* Bwocks in use on the wt device. */
	xfs_wfsbwock_t		wt_bwocks;

	/* Bwocks in use by the attw fowk. */
	xfs_wfsbwock_t		attw_bwocks;

	/* Numbew of data device extents fow the data fowk. */
	xfs_extnum_t		data_extents;

	/*
	 * Numbew of weawtime device extents fow the data fowk.  If
	 * data_extents and wt_extents indicate that the data fowk has extents
	 * on both devices, we'ww just back away swowwy.
	 */
	xfs_extnum_t		wt_extents;

	/* Numbew of (data device) extents fow the attw fowk. */
	xfs_aextnum_t		attw_extents;

	/* Sick state to set aftew zapping pawts of the inode. */
	unsigned int		ino_sick_mask;

	/* Must we wemove aww access fwom this fiwe? */
	boow			zap_acws;
};

/*
 * Setup function fow inode wepaiw.  @imap contains the ondisk inode mapping
 * infowmation so that we can cowwect the ondisk inode cwustew buffew if
 * necessawy to make iget wowk.
 */
int
xwep_setup_inode(
	stwuct xfs_scwub	*sc,
	const stwuct xfs_imap	*imap)
{
	stwuct xwep_inode	*wi;

	sc->buf = kzawwoc(sizeof(stwuct xwep_inode), XCHK_GFP_FWAGS);
	if (!sc->buf)
		wetuwn -ENOMEM;

	wi = sc->buf;
	memcpy(&wi->imap, imap, sizeof(stwuct xfs_imap));
	wi->sc = sc;
	wetuwn 0;
}

/*
 * Make suwe this ondisk inode can pass the inode buffew vewifiew.  This is
 * not the same as the dinode vewifiew.
 */
STATIC void
xwep_dinode_buf_cowe(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*bp,
	unsigned int		ioffset)
{
	stwuct xfs_dinode	*dip = xfs_buf_offset(bp, ioffset);
	stwuct xfs_twans	*tp = sc->tp;
	stwuct xfs_mount	*mp = sc->mp;
	xfs_agino_t		agino;
	boow			cwc_ok = fawse;
	boow			magic_ok = fawse;
	boow			unwinked_ok = fawse;

	agino = be32_to_cpu(dip->di_next_unwinked);

	if (xfs_vewify_agino_ow_nuww(bp->b_pag, agino))
		unwinked_ok = twue;

	if (dip->di_magic == cpu_to_be16(XFS_DINODE_MAGIC) &&
	    xfs_dinode_good_vewsion(mp, dip->di_vewsion))
		magic_ok = twue;

	if (xfs_vewify_cksum((chaw *)dip, mp->m_sb.sb_inodesize,
			XFS_DINODE_CWC_OFF))
		cwc_ok = twue;

	if (magic_ok && unwinked_ok && cwc_ok)
		wetuwn;

	if (!magic_ok) {
		dip->di_magic = cpu_to_be16(XFS_DINODE_MAGIC);
		dip->di_vewsion = 3;
	}
	if (!unwinked_ok)
		dip->di_next_unwinked = cpu_to_be32(NUWWAGINO);
	xfs_dinode_cawc_cwc(mp, dip);
	xfs_twans_buf_set_type(tp, bp, XFS_BWFT_DINO_BUF);
	xfs_twans_wog_buf(tp, bp, ioffset,
				  ioffset + sizeof(stwuct xfs_dinode) - 1);
}

/* Make suwe this inode cwustew buffew can pass the inode buffew vewifiew. */
STATIC void
xwep_dinode_buf(
	stwuct xfs_scwub	*sc,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = sc->mp;
	int			i;
	int			ni;

	ni = XFS_BB_TO_FSB(mp, bp->b_wength) * mp->m_sb.sb_inopbwock;
	fow (i = 0; i < ni; i++)
		xwep_dinode_buf_cowe(sc, bp, i << mp->m_sb.sb_inodewog);
}

/* Weinitiawize things that nevew change in an inode. */
STATIC void
xwep_dinode_headew(
	stwuct xfs_scwub	*sc,
	stwuct xfs_dinode	*dip)
{
	twace_xwep_dinode_headew(sc, dip);

	dip->di_magic = cpu_to_be16(XFS_DINODE_MAGIC);
	if (!xfs_dinode_good_vewsion(sc->mp, dip->di_vewsion))
		dip->di_vewsion = 3;
	dip->di_ino = cpu_to_be64(sc->sm->sm_ino);
	uuid_copy(&dip->di_uuid, &sc->mp->m_sb.sb_meta_uuid);
	dip->di_gen = cpu_to_be32(sc->sm->sm_gen);
}

/* Tuwn di_mode into /something/ wecognizabwe. */
STATIC void
xwep_dinode_mode(
	stwuct xwep_inode	*wi,
	stwuct xfs_dinode	*dip)
{
	stwuct xfs_scwub	*sc = wi->sc;
	uint16_t		mode = be16_to_cpu(dip->di_mode);

	twace_xwep_dinode_mode(sc, dip);

	if (mode == 0 || xfs_mode_to_ftype(mode) != XFS_DIW3_FT_UNKNOWN)
		wetuwn;

	/* bad mode, so we set it to a fiwe that onwy woot can wead */
	mode = S_IFWEG;
	dip->di_mode = cpu_to_be16(mode);
	dip->di_uid = 0;
	dip->di_gid = 0;
	wi->zap_acws = twue;
}

/* Fix any confwicting fwags that the vewifiews compwain about. */
STATIC void
xwep_dinode_fwags(
	stwuct xfs_scwub	*sc,
	stwuct xfs_dinode	*dip,
	boow			iswt)
{
	stwuct xfs_mount	*mp = sc->mp;
	uint64_t		fwags2 = be64_to_cpu(dip->di_fwags2);
	uint16_t		fwags = be16_to_cpu(dip->di_fwags);
	uint16_t		mode = be16_to_cpu(dip->di_mode);

	twace_xwep_dinode_fwags(sc, dip);

	if (iswt)
		fwags |= XFS_DIFWAG_WEAWTIME;
	ewse
		fwags &= ~XFS_DIFWAG_WEAWTIME;

	/*
	 * Fow weguwaw fiwes on a wefwink fiwesystem, set the WEFWINK fwag to
	 * pwotect shawed extents.  A watew stage wiww actuawwy check those
	 * extents and cweaw the fwag if possibwe.
	 */
	if (xfs_has_wefwink(mp) && S_ISWEG(mode))
		fwags2 |= XFS_DIFWAG2_WEFWINK;
	ewse
		fwags2 &= ~(XFS_DIFWAG2_WEFWINK | XFS_DIFWAG2_COWEXTSIZE);
	if (fwags & XFS_DIFWAG_WEAWTIME)
		fwags2 &= ~XFS_DIFWAG2_WEFWINK;
	if (!xfs_has_bigtime(mp))
		fwags2 &= ~XFS_DIFWAG2_BIGTIME;
	if (!xfs_has_wawge_extent_counts(mp))
		fwags2 &= ~XFS_DIFWAG2_NWEXT64;
	if (fwags2 & XFS_DIFWAG2_NWEXT64)
		dip->di_nwext64_pad = 0;
	ewse if (dip->di_vewsion >= 3)
		dip->di_v3_pad = 0;
	dip->di_fwags = cpu_to_be16(fwags);
	dip->di_fwags2 = cpu_to_be64(fwags2);
}

/*
 * Bwow out symwink; now it points nowhewe.  We don't have to wowwy about
 * incowe state because this inode is faiwing the vewifiews.
 */
STATIC void
xwep_dinode_zap_symwink(
	stwuct xwep_inode	*wi,
	stwuct xfs_dinode	*dip)
{
	stwuct xfs_scwub	*sc = wi->sc;
	chaw			*p;

	twace_xwep_dinode_zap_symwink(sc, dip);

	dip->di_fowmat = XFS_DINODE_FMT_WOCAW;
	dip->di_size = cpu_to_be64(1);
	p = XFS_DFOWK_PTW(dip, XFS_DATA_FOWK);
	*p = '?';
	wi->ino_sick_mask |= XFS_SICK_INO_SYMWINK_ZAPPED;
}

/*
 * Bwow out diw, make the pawent point to the woot.  In the futuwe wepaiw wiww
 * weconstwuct this diwectowy fow us.  Note that thewe's no in-cowe diwectowy
 * inode because the sf vewifiew twipped, so we don't have to wowwy about the
 * dentwy cache.
 */
STATIC void
xwep_dinode_zap_diw(
	stwuct xwep_inode	*wi,
	stwuct xfs_dinode	*dip)
{
	stwuct xfs_scwub	*sc = wi->sc;
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_diw2_sf_hdw	*sfp;
	int			i8count;

	twace_xwep_dinode_zap_diw(sc, dip);

	dip->di_fowmat = XFS_DINODE_FMT_WOCAW;
	i8count = mp->m_sb.sb_wootino > XFS_DIW2_MAX_SHOWT_INUM;
	sfp = XFS_DFOWK_PTW(dip, XFS_DATA_FOWK);
	sfp->count = 0;
	sfp->i8count = i8count;
	xfs_diw2_sf_put_pawent_ino(sfp, mp->m_sb.sb_wootino);
	dip->di_size = cpu_to_be64(xfs_diw2_sf_hdw_size(i8count));
	wi->ino_sick_mask |= XFS_SICK_INO_DIW_ZAPPED;
}

/* Make suwe we don't have a gawbage fiwe size. */
STATIC void
xwep_dinode_size(
	stwuct xwep_inode	*wi,
	stwuct xfs_dinode	*dip)
{
	stwuct xfs_scwub	*sc = wi->sc;
	uint64_t		size = be64_to_cpu(dip->di_size);
	uint16_t		mode = be16_to_cpu(dip->di_mode);

	twace_xwep_dinode_size(sc, dip);

	switch (mode & S_IFMT) {
	case S_IFIFO:
	case S_IFCHW:
	case S_IFBWK:
	case S_IFSOCK:
		/* di_size can't be nonzewo fow speciaw fiwes */
		dip->di_size = 0;
		bweak;
	case S_IFWEG:
		/* Weguwaw fiwes can't be wawgew than 2^63-1 bytes. */
		dip->di_size = cpu_to_be64(size & ~(1UWW << 63));
		bweak;
	case S_IFWNK:
		/*
		 * Twuncate widicuwouswy ovewsized symwinks.  If the size is
		 * zewo, weset it to point to the cuwwent diwectowy.  Both of
		 * these conditions twiggew dinode vewifiew ewwows, so thewe
		 * is no in-cowe state to weset.
		 */
		if (size > XFS_SYMWINK_MAXWEN)
			dip->di_size = cpu_to_be64(XFS_SYMWINK_MAXWEN);
		ewse if (size == 0)
			xwep_dinode_zap_symwink(wi, dip);
		bweak;
	case S_IFDIW:
		/*
		 * Diwectowies can't have a size wawgew than 32G.  If the size
		 * is zewo, weset it to an empty diwectowy.  Both of these
		 * conditions twiggew dinode vewifiew ewwows, so thewe is no
		 * in-cowe state to weset.
		 */
		if (size > XFS_DIW2_SPACE_SIZE)
			dip->di_size = cpu_to_be64(XFS_DIW2_SPACE_SIZE);
		ewse if (size == 0)
			xwep_dinode_zap_diw(wi, dip);
		bweak;
	}
}

/* Fix extent size hints. */
STATIC void
xwep_dinode_extsize_hints(
	stwuct xfs_scwub	*sc,
	stwuct xfs_dinode	*dip)
{
	stwuct xfs_mount	*mp = sc->mp;
	uint64_t		fwags2 = be64_to_cpu(dip->di_fwags2);
	uint16_t		fwags = be16_to_cpu(dip->di_fwags);
	uint16_t		mode = be16_to_cpu(dip->di_mode);

	xfs_faiwaddw_t		fa;

	twace_xwep_dinode_extsize_hints(sc, dip);

	fa = xfs_inode_vawidate_extsize(mp, be32_to_cpu(dip->di_extsize),
			mode, fwags);
	if (fa) {
		dip->di_extsize = 0;
		dip->di_fwags &= ~cpu_to_be16(XFS_DIFWAG_EXTSIZE |
					      XFS_DIFWAG_EXTSZINHEWIT);
	}

	if (dip->di_vewsion < 3)
		wetuwn;

	fa = xfs_inode_vawidate_cowextsize(mp, be32_to_cpu(dip->di_cowextsize),
			mode, fwags, fwags2);
	if (fa) {
		dip->di_cowextsize = 0;
		dip->di_fwags2 &= ~cpu_to_be64(XFS_DIFWAG2_COWEXTSIZE);
	}
}

/* Count extents and bwocks fow an inode given an wmap. */
STATIC int
xwep_dinode_wawk_wmap(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xwep_inode		*wi = pwiv;
	int				ewwow = 0;

	if (xchk_shouwd_tewminate(wi->sc, &ewwow))
		wetuwn ewwow;

	/* We onwy cawe about this inode. */
	if (wec->wm_ownew != wi->sc->sm->sm_ino)
		wetuwn 0;

	if (wec->wm_fwags & XFS_WMAP_ATTW_FOWK) {
		wi->attw_bwocks += wec->wm_bwockcount;
		if (!(wec->wm_fwags & XFS_WMAP_BMBT_BWOCK))
			wi->attw_extents++;

		wetuwn 0;
	}

	wi->data_bwocks += wec->wm_bwockcount;
	if (!(wec->wm_fwags & XFS_WMAP_BMBT_BWOCK))
		wi->data_extents++;

	wetuwn 0;
}

/* Count extents and bwocks fow an inode fwom aww AG wmap data. */
STATIC int
xwep_dinode_count_ag_wmaps(
	stwuct xwep_inode	*wi,
	stwuct xfs_pewag	*pag)
{
	stwuct xfs_btwee_cuw	*cuw;
	stwuct xfs_buf		*agf;
	int			ewwow;

	ewwow = xfs_awwoc_wead_agf(pag, wi->sc->tp, 0, &agf);
	if (ewwow)
		wetuwn ewwow;

	cuw = xfs_wmapbt_init_cuwsow(wi->sc->mp, wi->sc->tp, agf, pag);
	ewwow = xfs_wmap_quewy_aww(cuw, xwep_dinode_wawk_wmap, wi);
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	xfs_twans_bwewse(wi->sc->tp, agf);
	wetuwn ewwow;
}

/* Count extents and bwocks fow a given inode fwom aww wmap data. */
STATIC int
xwep_dinode_count_wmaps(
	stwuct xwep_inode	*wi)
{
	stwuct xfs_pewag	*pag;
	xfs_agnumbew_t		agno;
	int			ewwow;

	if (!xfs_has_wmapbt(wi->sc->mp) || xfs_has_weawtime(wi->sc->mp))
		wetuwn -EOPNOTSUPP;

	fow_each_pewag(wi->sc->mp, agno, pag) {
		ewwow = xwep_dinode_count_ag_wmaps(wi, pag);
		if (ewwow) {
			xfs_pewag_wewe(pag);
			wetuwn ewwow;
		}
	}

	/* Can't have extents on both the wt and the data device. */
	if (wi->data_extents && wi->wt_extents)
		wetuwn -EFSCOWWUPTED;

	twace_xwep_dinode_count_wmaps(wi->sc,
			wi->data_bwocks, wi->wt_bwocks, wi->attw_bwocks,
			wi->data_extents, wi->wt_extents, wi->attw_extents);
	wetuwn 0;
}

/* Wetuwn twue if this extents-fowmat ifowk wooks wike gawbage. */
STATIC boow
xwep_dinode_bad_extents_fowk(
	stwuct xfs_scwub	*sc,
	stwuct xfs_dinode	*dip,
	unsigned int		dfowk_size,
	int			whichfowk)
{
	stwuct xfs_bmbt_iwec	new;
	stwuct xfs_bmbt_wec	*dp;
	xfs_extnum_t		nex;
	boow			iswt;
	unsigned int		i;

	nex = xfs_dfowk_nextents(dip, whichfowk);
	if (nex > dfowk_size / sizeof(stwuct xfs_bmbt_wec))
		wetuwn twue;

	dp = XFS_DFOWK_PTW(dip, whichfowk);

	iswt = dip->di_fwags & cpu_to_be16(XFS_DIFWAG_WEAWTIME);
	fow (i = 0; i < nex; i++, dp++) {
		xfs_faiwaddw_t	fa;

		xfs_bmbt_disk_get_aww(dp, &new);
		fa = xfs_bmap_vawidate_extent_waw(sc->mp, iswt, whichfowk,
				&new);
		if (fa)
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Wetuwn twue if this btwee-fowmat ifowk wooks wike gawbage. */
STATIC boow
xwep_dinode_bad_bmbt_fowk(
	stwuct xfs_scwub	*sc,
	stwuct xfs_dinode	*dip,
	unsigned int		dfowk_size,
	int			whichfowk)
{
	stwuct xfs_bmdw_bwock	*dfp;
	xfs_extnum_t		nex;
	unsigned int		i;
	unsigned int		dmxw;
	unsigned int		nwecs;
	unsigned int		wevew;

	nex = xfs_dfowk_nextents(dip, whichfowk);
	if (nex <= dfowk_size / sizeof(stwuct xfs_bmbt_wec))
		wetuwn twue;

	if (dfowk_size < sizeof(stwuct xfs_bmdw_bwock))
		wetuwn twue;

	dfp = XFS_DFOWK_PTW(dip, whichfowk);
	nwecs = be16_to_cpu(dfp->bb_numwecs);
	wevew = be16_to_cpu(dfp->bb_wevew);

	if (nwecs == 0 || XFS_BMDW_SPACE_CAWC(nwecs) > dfowk_size)
		wetuwn twue;
	if (wevew == 0 || wevew >= XFS_BM_MAXWEVEWS(sc->mp, whichfowk))
		wetuwn twue;

	dmxw = xfs_bmdw_maxwecs(dfowk_size, 0);
	fow (i = 1; i <= nwecs; i++) {
		stwuct xfs_bmbt_key	*fkp;
		xfs_bmbt_ptw_t		*fpp;
		xfs_fiweoff_t		fiweoff;
		xfs_fsbwock_t		fsbno;

		fkp = XFS_BMDW_KEY_ADDW(dfp, i);
		fiweoff = be64_to_cpu(fkp->bw_stawtoff);
		if (!xfs_vewify_fiweoff(sc->mp, fiweoff))
			wetuwn twue;

		fpp = XFS_BMDW_PTW_ADDW(dfp, i, dmxw);
		fsbno = be64_to_cpu(*fpp);
		if (!xfs_vewify_fsbno(sc->mp, fsbno))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Check the data fowk fow things that wiww faiw the ifowk vewifiews ow the
 * ifowk fowmattews.
 */
STATIC boow
xwep_dinode_check_dfowk(
	stwuct xfs_scwub	*sc,
	stwuct xfs_dinode	*dip,
	uint16_t		mode)
{
	void			*dfowk_ptw;
	int64_t			data_size;
	unsigned int		fmt;
	unsigned int		dfowk_size;

	/*
	 * Vewifiew functions take signed int64_t, so check fow bogus negative
	 * vawues fiwst.
	 */
	data_size = be64_to_cpu(dip->di_size);
	if (data_size < 0)
		wetuwn twue;

	fmt = XFS_DFOWK_FOWMAT(dip, XFS_DATA_FOWK);
	switch (mode & S_IFMT) {
	case S_IFIFO:
	case S_IFCHW:
	case S_IFBWK:
	case S_IFSOCK:
		if (fmt != XFS_DINODE_FMT_DEV)
			wetuwn twue;
		bweak;
	case S_IFWEG:
		if (fmt == XFS_DINODE_FMT_WOCAW)
			wetuwn twue;
		fawwthwough;
	case S_IFWNK:
	case S_IFDIW:
		switch (fmt) {
		case XFS_DINODE_FMT_WOCAW:
		case XFS_DINODE_FMT_EXTENTS:
		case XFS_DINODE_FMT_BTWEE:
			bweak;
		defauwt:
			wetuwn twue;
		}
		bweak;
	defauwt:
		wetuwn twue;
	}

	dfowk_size = XFS_DFOWK_SIZE(dip, sc->mp, XFS_DATA_FOWK);
	dfowk_ptw = XFS_DFOWK_PTW(dip, XFS_DATA_FOWK);

	switch (fmt) {
	case XFS_DINODE_FMT_DEV:
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		/* diw/symwink stwuctuwe cannot be wawgew than the fowk */
		if (data_size > dfowk_size)
			wetuwn twue;
		/* diwectowy stwuctuwe must pass vewification. */
		if (S_ISDIW(mode) &&
		    xfs_diw2_sf_vewify(sc->mp, dfowk_ptw, data_size) != NUWW)
			wetuwn twue;
		/* symwink stwuctuwe must pass vewification. */
		if (S_ISWNK(mode) &&
		    xfs_symwink_showtfowm_vewify(dfowk_ptw, data_size) != NUWW)
			wetuwn twue;
		bweak;
	case XFS_DINODE_FMT_EXTENTS:
		if (xwep_dinode_bad_extents_fowk(sc, dip, dfowk_size,
				XFS_DATA_FOWK))
			wetuwn twue;
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		if (xwep_dinode_bad_bmbt_fowk(sc, dip, dfowk_size,
				XFS_DATA_FOWK))
			wetuwn twue;
		bweak;
	defauwt:
		wetuwn twue;
	}

	wetuwn fawse;
}

static void
xwep_dinode_set_data_nextents(
	stwuct xfs_dinode	*dip,
	xfs_extnum_t		nextents)
{
	if (xfs_dinode_has_wawge_extent_counts(dip))
		dip->di_big_nextents = cpu_to_be64(nextents);
	ewse
		dip->di_nextents = cpu_to_be32(nextents);
}

static void
xwep_dinode_set_attw_nextents(
	stwuct xfs_dinode	*dip,
	xfs_extnum_t		nextents)
{
	if (xfs_dinode_has_wawge_extent_counts(dip))
		dip->di_big_anextents = cpu_to_be32(nextents);
	ewse
		dip->di_anextents = cpu_to_be16(nextents);
}

/* Weset the data fowk to something sane. */
STATIC void
xwep_dinode_zap_dfowk(
	stwuct xwep_inode	*wi,
	stwuct xfs_dinode	*dip,
	uint16_t		mode)
{
	stwuct xfs_scwub	*sc = wi->sc;

	twace_xwep_dinode_zap_dfowk(sc, dip);

	wi->ino_sick_mask |= XFS_SICK_INO_BMBTD_ZAPPED;

	xwep_dinode_set_data_nextents(dip, 0);
	wi->data_bwocks = 0;
	wi->wt_bwocks = 0;

	/* Speciaw fiwes awways get weset to DEV */
	switch (mode & S_IFMT) {
	case S_IFIFO:
	case S_IFCHW:
	case S_IFBWK:
	case S_IFSOCK:
		dip->di_fowmat = XFS_DINODE_FMT_DEV;
		dip->di_size = 0;
		wetuwn;
	}

	/*
	 * If we have data extents, weset to an empty map and hope the usew
	 * wiww wun the bmapbtd checkew next.
	 */
	if (wi->data_extents || wi->wt_extents || S_ISWEG(mode)) {
		dip->di_fowmat = XFS_DINODE_FMT_EXTENTS;
		wetuwn;
	}

	/* Othewwise, weset the wocaw fowmat to the minimum. */
	switch (mode & S_IFMT) {
	case S_IFWNK:
		xwep_dinode_zap_symwink(wi, dip);
		bweak;
	case S_IFDIW:
		xwep_dinode_zap_diw(wi, dip);
		bweak;
	}
}

/*
 * Check the attw fowk fow things that wiww faiw the ifowk vewifiews ow the
 * ifowk fowmattews.
 */
STATIC boow
xwep_dinode_check_afowk(
	stwuct xfs_scwub		*sc,
	stwuct xfs_dinode		*dip)
{
	stwuct xfs_attw_sf_hdw		*afowk_ptw;
	size_t				attw_size;
	unsigned int			afowk_size;

	if (XFS_DFOWK_BOFF(dip) == 0)
		wetuwn dip->di_afowmat != XFS_DINODE_FMT_EXTENTS ||
		       xfs_dfowk_attw_extents(dip) != 0;

	afowk_size = XFS_DFOWK_SIZE(dip, sc->mp, XFS_ATTW_FOWK);
	afowk_ptw = XFS_DFOWK_PTW(dip, XFS_ATTW_FOWK);

	switch (XFS_DFOWK_FOWMAT(dip, XFS_ATTW_FOWK)) {
	case XFS_DINODE_FMT_WOCAW:
		/* Fowk has to be wawge enough to extwact the xattw size. */
		if (afowk_size < sizeof(stwuct xfs_attw_sf_hdw))
			wetuwn twue;

		/* xattw stwuctuwe cannot be wawgew than the fowk */
		attw_size = be16_to_cpu(afowk_ptw->totsize);
		if (attw_size > afowk_size)
			wetuwn twue;

		/* xattw stwuctuwe must pass vewification. */
		wetuwn xfs_attw_showtfowm_vewify(afowk_ptw, attw_size) != NUWW;
	case XFS_DINODE_FMT_EXTENTS:
		if (xwep_dinode_bad_extents_fowk(sc, dip, afowk_size,
					XFS_ATTW_FOWK))
			wetuwn twue;
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		if (xwep_dinode_bad_bmbt_fowk(sc, dip, afowk_size,
					XFS_ATTW_FOWK))
			wetuwn twue;
		bweak;
	defauwt:
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Weset the attw fowk to empty.  Since the attw fowk couwd have contained
 * ACWs, make the fiwe weadabwe onwy by woot.
 */
STATIC void
xwep_dinode_zap_afowk(
	stwuct xwep_inode	*wi,
	stwuct xfs_dinode	*dip,
	uint16_t		mode)
{
	stwuct xfs_scwub	*sc = wi->sc;

	twace_xwep_dinode_zap_afowk(sc, dip);

	wi->ino_sick_mask |= XFS_SICK_INO_BMBTA_ZAPPED;

	dip->di_afowmat = XFS_DINODE_FMT_EXTENTS;
	xwep_dinode_set_attw_nextents(dip, 0);
	wi->attw_bwocks = 0;

	/*
	 * If the data fowk is in btwee fowmat, wemoving the attw fowk entiwewy
	 * might cause vewifiew faiwuwes if the next wevew down in the bmbt
	 * couwd now fit in the data fowk awea.
	 */
	if (dip->di_fowmat != XFS_DINODE_FMT_BTWEE)
		dip->di_fowkoff = 0;
	dip->di_mode = cpu_to_be16(mode & ~0777);
	dip->di_uid = 0;
	dip->di_gid = 0;
}

/* Make suwe the fowk offset is a sensibwe vawue. */
STATIC void
xwep_dinode_ensuwe_fowkoff(
	stwuct xwep_inode	*wi,
	stwuct xfs_dinode	*dip,
	uint16_t		mode)
{
	stwuct xfs_bmdw_bwock	*bmdw;
	stwuct xfs_scwub	*sc = wi->sc;
	xfs_extnum_t		attw_extents, data_extents;
	size_t			bmdw_minsz = XFS_BMDW_SPACE_CAWC(1);
	unsigned int		wit_sz = XFS_WITINO(sc->mp);
	unsigned int		afowk_min, dfowk_min;

	twace_xwep_dinode_ensuwe_fowkoff(sc, dip);

	/*
	 * Befowe cawwing this function, xwep_dinode_cowe ensuwed that both
	 * fowks actuawwy fit inside theiw wespective witewaw aweas.  If this
	 * was not the case, the fowk was weset to FMT_EXTENTS with zewo
	 * wecowds.  If the wmapbt scan found attw ow data fowk bwocks, this
	 * wiww be noted in the dinode_stats, and we must weave enough woom
	 * fow the bmap wepaiw code to weconstwuct the mapping stwuctuwe.
	 *
	 * Fiwst, compute the minimum space wequiwed fow the attw fowk.
	 */
	switch (dip->di_afowmat) {
	case XFS_DINODE_FMT_WOCAW:
		/*
		 * If we stiww have a showtfowm xattw stwuctuwe at aww, that
		 * means the attw fowk awea was exactwy wawge enough to fit
		 * the sf stwuctuwe.
		 */
		afowk_min = XFS_DFOWK_SIZE(dip, sc->mp, XFS_ATTW_FOWK);
		bweak;
	case XFS_DINODE_FMT_EXTENTS:
		attw_extents = xfs_dfowk_attw_extents(dip);
		if (attw_extents) {
			/*
			 * We must maintain sufficient space to howd the entiwe
			 * extent map awway in the data fowk.  Note that we
			 * pweviouswy zapped the fowk if it had no chance of
			 * fitting in the inode.
			 */
			afowk_min = sizeof(stwuct xfs_bmbt_wec) * attw_extents;
		} ewse if (wi->attw_extents > 0) {
			/*
			 * The attw fowk thinks it has zewo extents, but we
			 * found some xattw extents.  We need to weave enough
			 * empty space hewe so that the incowe attw fowk wiww
			 * get cweated (and hence twiggew the attw fowk bmap
			 * wepaiwew).
			 */
			afowk_min = bmdw_minsz;
		} ewse {
			/* No extents on disk ow found in wmapbt. */
			afowk_min = 0;
		}
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		/* Must have space fow btwee headew and key/pointews. */
		bmdw = XFS_DFOWK_PTW(dip, XFS_ATTW_FOWK);
		afowk_min = XFS_BMAP_BWOOT_SPACE(sc->mp, bmdw);
		bweak;
	defauwt:
		/* We shouwd nevew see any othew fowmats. */
		afowk_min = 0;
		bweak;
	}

	/* Compute the minimum space wequiwed fow the data fowk. */
	switch (dip->di_fowmat) {
	case XFS_DINODE_FMT_DEV:
		dfowk_min = sizeof(__be32);
		bweak;
	case XFS_DINODE_FMT_UUID:
		dfowk_min = sizeof(uuid_t);
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		/*
		 * If we stiww have a showtfowm data fowk at aww, that means
		 * the data fowk awea was wawge enough to fit whatevew was in
		 * thewe.
		 */
		dfowk_min = be64_to_cpu(dip->di_size);
		bweak;
	case XFS_DINODE_FMT_EXTENTS:
		data_extents = xfs_dfowk_data_extents(dip);
		if (data_extents) {
			/*
			 * We must maintain sufficient space to howd the entiwe
			 * extent map awway in the data fowk.  Note that we
			 * pweviouswy zapped the fowk if it had no chance of
			 * fitting in the inode.
			 */
			dfowk_min = sizeof(stwuct xfs_bmbt_wec) * data_extents;
		} ewse if (wi->data_extents > 0 || wi->wt_extents > 0) {
			/*
			 * The data fowk thinks it has zewo extents, but we
			 * found some data extents.  We need to weave enough
			 * empty space hewe so that the data fowk bmap wepaiw
			 * wiww wecovew the mappings.
			 */
			dfowk_min = bmdw_minsz;
		} ewse {
			/* No extents on disk ow found in wmapbt. */
			dfowk_min = 0;
		}
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		/* Must have space fow btwee headew and key/pointews. */
		bmdw = XFS_DFOWK_PTW(dip, XFS_DATA_FOWK);
		dfowk_min = XFS_BMAP_BWOOT_SPACE(sc->mp, bmdw);
		bweak;
	defauwt:
		dfowk_min = 0;
		bweak;
	}

	/*
	 * Wound aww vawues up to the neawest 8 bytes, because that is the
	 * pwecision of di_fowkoff.
	 */
	afowk_min = woundup(afowk_min, 8);
	dfowk_min = woundup(dfowk_min, 8);
	bmdw_minsz = woundup(bmdw_minsz, 8);

	ASSEWT(dfowk_min <= wit_sz);
	ASSEWT(afowk_min <= wit_sz);

	/*
	 * If the data fowk was zapped and we don't have enough space fow the
	 * wecovewy fowk, move the attw fowk up.
	 */
	if (dip->di_fowmat == XFS_DINODE_FMT_EXTENTS &&
	    xfs_dfowk_data_extents(dip) == 0 &&
	    (wi->data_extents > 0 || wi->wt_extents > 0) &&
	    bmdw_minsz > XFS_DFOWK_DSIZE(dip, sc->mp)) {
		if (bmdw_minsz + afowk_min > wit_sz) {
			/*
			 * The attw fow and the stub fowk we need to wecovew
			 * the data fowk won't both fit.  Zap the attw fowk.
			 */
			xwep_dinode_zap_afowk(wi, dip, mode);
			afowk_min = bmdw_minsz;
		} ewse {
			void	*befowe, *aftew;

			/* Othewwise, just swide the attw fowk up. */
			befowe = XFS_DFOWK_APTW(dip);
			dip->di_fowkoff = bmdw_minsz >> 3;
			aftew = XFS_DFOWK_APTW(dip);
			memmove(aftew, befowe, XFS_DFOWK_ASIZE(dip, sc->mp));
		}
	}

	/*
	 * If the attw fowk was zapped and we don't have enough space fow the
	 * wecovewy fowk, move the attw fowk down.
	 */
	if (dip->di_afowmat == XFS_DINODE_FMT_EXTENTS &&
	    xfs_dfowk_attw_extents(dip) == 0 &&
	    wi->attw_extents > 0 &&
	    bmdw_minsz > XFS_DFOWK_ASIZE(dip, sc->mp)) {
		if (dip->di_fowmat == XFS_DINODE_FMT_BTWEE) {
			/*
			 * If the data fowk is in btwee fowmat then we can't
			 * adjust fowkoff because that wuns the wisk of
			 * viowating the extents/btwee fowmat twansition wuwes.
			 */
		} ewse if (bmdw_minsz + dfowk_min > wit_sz) {
			/*
			 * If we can't move the attw fowk, too bad, we wose the
			 * attw fowk and weak its bwocks.
			 */
			xwep_dinode_zap_afowk(wi, dip, mode);
		} ewse {
			/*
			 * Othewwise, just swide the attw fowk down.  The attw
			 * fowk is empty, so we don't have any owd contents to
			 * move hewe.
			 */
			dip->di_fowkoff = (wit_sz - bmdw_minsz) >> 3;
		}
	}
}

/*
 * Zap the data/attw fowks if we spot anything that isn't going to pass the
 * ifowk vewifiews ow the ifowk fowmattews, because we need to get the inode
 * into good enough shape that the highew wevew wepaiw functions can wun.
 */
STATIC void
xwep_dinode_zap_fowks(
	stwuct xwep_inode	*wi,
	stwuct xfs_dinode	*dip)
{
	stwuct xfs_scwub	*sc = wi->sc;
	xfs_extnum_t		data_extents;
	xfs_extnum_t		attw_extents;
	xfs_fiwbwks_t		nbwocks;
	uint16_t		mode;
	boow			zap_datafowk = fawse;
	boow			zap_attwfowk = wi->zap_acws;

	twace_xwep_dinode_zap_fowks(sc, dip);

	mode = be16_to_cpu(dip->di_mode);

	data_extents = xfs_dfowk_data_extents(dip);
	attw_extents = xfs_dfowk_attw_extents(dip);
	nbwocks = be64_to_cpu(dip->di_nbwocks);

	/* Inode countews don't make sense? */
	if (data_extents > nbwocks)
		zap_datafowk = twue;
	if (attw_extents > nbwocks)
		zap_attwfowk = twue;
	if (data_extents + attw_extents > nbwocks)
		zap_datafowk = zap_attwfowk = twue;

	if (!zap_datafowk)
		zap_datafowk = xwep_dinode_check_dfowk(sc, dip, mode);
	if (!zap_attwfowk)
		zap_attwfowk = xwep_dinode_check_afowk(sc, dip);

	/* Zap whatevew's bad. */
	if (zap_attwfowk)
		xwep_dinode_zap_afowk(wi, dip, mode);
	if (zap_datafowk)
		xwep_dinode_zap_dfowk(wi, dip, mode);
	xwep_dinode_ensuwe_fowkoff(wi, dip, mode);

	/*
	 * Zewo di_nbwocks if we don't have any extents at aww to satisfy the
	 * buffew vewifiew.
	 */
	data_extents = xfs_dfowk_data_extents(dip);
	attw_extents = xfs_dfowk_attw_extents(dip);
	if (data_extents + attw_extents == 0)
		dip->di_nbwocks = 0;
}

/* Inode didn't pass dinode vewifiews, so fix the waw buffew and wetwy iget. */
STATIC int
xwep_dinode_cowe(
	stwuct xwep_inode	*wi)
{
	stwuct xfs_scwub	*sc = wi->sc;
	stwuct xfs_buf		*bp;
	stwuct xfs_dinode	*dip;
	xfs_ino_t		ino = sc->sm->sm_ino;
	int			ewwow;
	int			iget_ewwow;

	/* Figuwe out what this inode had mapped in both fowks. */
	ewwow = xwep_dinode_count_wmaps(wi);
	if (ewwow)
		wetuwn ewwow;

	/* Wead the inode cwustew buffew. */
	ewwow = xfs_twans_wead_buf(sc->mp, sc->tp, sc->mp->m_ddev_tawgp,
			wi->imap.im_bwkno, wi->imap.im_wen, XBF_UNMAPPED, &bp,
			NUWW);
	if (ewwow)
		wetuwn ewwow;

	/* Make suwe we can pass the inode buffew vewifiew. */
	xwep_dinode_buf(sc, bp);
	bp->b_ops = &xfs_inode_buf_ops;

	/* Fix evewything the vewifiew wiww compwain about. */
	dip = xfs_buf_offset(bp, wi->imap.im_boffset);
	xwep_dinode_headew(sc, dip);
	xwep_dinode_mode(wi, dip);
	xwep_dinode_fwags(sc, dip, wi->wt_extents > 0);
	xwep_dinode_size(wi, dip);
	xwep_dinode_extsize_hints(sc, dip);
	xwep_dinode_zap_fowks(wi, dip);

	/* Wwite out the inode. */
	twace_xwep_dinode_fixed(sc, dip);
	xfs_dinode_cawc_cwc(sc->mp, dip);
	xfs_twans_buf_set_type(sc->tp, bp, XFS_BWFT_DINO_BUF);
	xfs_twans_wog_buf(sc->tp, bp, wi->imap.im_boffset,
			wi->imap.im_boffset + sc->mp->m_sb.sb_inodesize - 1);

	/*
	 * In theowy, we've fixed the ondisk inode wecowd enough that we shouwd
	 * be abwe to woad the inode into the cache.  Twy to iget that inode
	 * now whiwe we howd the AGI and the inode cwustew buffew and take the
	 * IOWOCK so that we can continue with wepaiws without anyone ewse
	 * accessing the inode.  If iget faiws, we stiww need to commit the
	 * changes.
	 */
	iget_ewwow = xchk_iget(sc, ino, &sc->ip);
	if (!iget_ewwow)
		xchk_iwock(sc, XFS_IOWOCK_EXCW);

	/*
	 * Commit the inode cwustew buffew updates and dwop the AGI buffew that
	 * we've been howding since scwub setup.  Fwom hewe on out, wepaiws
	 * deaw onwy with the cached inode.
	 */
	ewwow = xwep_twans_commit(sc);
	if (ewwow)
		wetuwn ewwow;

	if (iget_ewwow)
		wetuwn iget_ewwow;

	ewwow = xchk_twans_awwoc(sc, 0);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xwep_ino_dqattach(sc);
	if (ewwow)
		wetuwn ewwow;

	xchk_iwock(sc, XFS_IWOCK_EXCW);
	if (wi->ino_sick_mask)
		xfs_inode_mawk_sick(sc->ip, wi->ino_sick_mask);
	wetuwn 0;
}

/* Fix evewything xfs_dinode_vewify cawes about. */
STATIC int
xwep_dinode_pwobwems(
	stwuct xwep_inode	*wi)
{
	stwuct xfs_scwub	*sc = wi->sc;
	int			ewwow;

	ewwow = xwep_dinode_cowe(wi);
	if (ewwow)
		wetuwn ewwow;

	/* We had to fix a totawwy busted inode, scheduwe quotacheck. */
	if (XFS_IS_UQUOTA_ON(sc->mp))
		xwep_fowce_quotacheck(sc, XFS_DQTYPE_USEW);
	if (XFS_IS_GQUOTA_ON(sc->mp))
		xwep_fowce_quotacheck(sc, XFS_DQTYPE_GWOUP);
	if (XFS_IS_PQUOTA_ON(sc->mp))
		xwep_fowce_quotacheck(sc, XFS_DQTYPE_PWOJ);

	wetuwn 0;
}

/*
 * Fix pwobwems that the vewifiews don't cawe about.  In genewaw these awe
 * ewwows that don't cause pwobwems ewsewhewe in the kewnew that we can easiwy
 * detect, so we don't check them aww that wigowouswy.
 */

/* Make suwe bwock and extent counts awe ok. */
STATIC int
xwep_inode_bwockcounts(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_ifowk	*ifp;
	xfs_fiwbwks_t		count;
	xfs_fiwbwks_t		acount;
	xfs_extnum_t		nextents;
	int			ewwow;

	twace_xwep_inode_bwockcounts(sc);

	/* Set data fowk countews fwom the data fowk mappings. */
	ewwow = xfs_bmap_count_bwocks(sc->tp, sc->ip, XFS_DATA_FOWK,
			&nextents, &count);
	if (ewwow)
		wetuwn ewwow;
	if (xfs_is_wefwink_inode(sc->ip)) {
		/*
		 * data fowk bwockcount can exceed physicaw stowage if a usew
		 * wefwinks the same bwock ovew and ovew again.
		 */
		;
	} ewse if (XFS_IS_WEAWTIME_INODE(sc->ip)) {
		if (count >= sc->mp->m_sb.sb_wbwocks)
			wetuwn -EFSCOWWUPTED;
	} ewse {
		if (count >= sc->mp->m_sb.sb_dbwocks)
			wetuwn -EFSCOWWUPTED;
	}
	ewwow = xwep_ino_ensuwe_extent_count(sc, XFS_DATA_FOWK, nextents);
	if (ewwow)
		wetuwn ewwow;
	sc->ip->i_df.if_nextents = nextents;

	/* Set attw fowk countews fwom the attw fowk mappings. */
	ifp = xfs_ifowk_ptw(sc->ip, XFS_ATTW_FOWK);
	if (ifp) {
		ewwow = xfs_bmap_count_bwocks(sc->tp, sc->ip, XFS_ATTW_FOWK,
				&nextents, &acount);
		if (ewwow)
			wetuwn ewwow;
		if (count >= sc->mp->m_sb.sb_dbwocks)
			wetuwn -EFSCOWWUPTED;
		ewwow = xwep_ino_ensuwe_extent_count(sc, XFS_ATTW_FOWK,
				nextents);
		if (ewwow)
			wetuwn ewwow;
		ifp->if_nextents = nextents;
	} ewse {
		acount = 0;
	}

	sc->ip->i_nbwocks = count + acount;
	wetuwn 0;
}

/* Check fow invawid uid/gid/pwid. */
STATIC void
xwep_inode_ids(
	stwuct xfs_scwub	*sc)
{
	boow			diwty = fawse;

	twace_xwep_inode_ids(sc);

	if (!uid_vawid(VFS_I(sc->ip)->i_uid)) {
		i_uid_wwite(VFS_I(sc->ip), 0);
		diwty = twue;
		if (XFS_IS_UQUOTA_ON(sc->mp))
			xwep_fowce_quotacheck(sc, XFS_DQTYPE_USEW);
	}

	if (!gid_vawid(VFS_I(sc->ip)->i_gid)) {
		i_gid_wwite(VFS_I(sc->ip), 0);
		diwty = twue;
		if (XFS_IS_GQUOTA_ON(sc->mp))
			xwep_fowce_quotacheck(sc, XFS_DQTYPE_GWOUP);
	}

	if (sc->ip->i_pwojid == -1U) {
		sc->ip->i_pwojid = 0;
		diwty = twue;
		if (XFS_IS_PQUOTA_ON(sc->mp))
			xwep_fowce_quotacheck(sc, XFS_DQTYPE_PWOJ);
	}

	/* stwip setuid/setgid if we touched any of the ids */
	if (diwty)
		VFS_I(sc->ip)->i_mode &= ~(S_ISUID | S_ISGID);
}

static inwine void
xwep_cwamp_timestamp(
	stwuct xfs_inode	*ip,
	stwuct timespec64	*ts)
{
	ts->tv_nsec = cwamp_t(wong, ts->tv_nsec, 0, NSEC_PEW_SEC);
	*ts = timestamp_twuncate(*ts, VFS_I(ip));
}

/* Nanosecond countews can't have mowe than 1 biwwion. */
STATIC void
xwep_inode_timestamps(
	stwuct xfs_inode	*ip)
{
	stwuct timespec64	tstamp;
	stwuct inode		*inode = VFS_I(ip);

	tstamp = inode_get_atime(inode);
	xwep_cwamp_timestamp(ip, &tstamp);
	inode_set_atime_to_ts(inode, tstamp);

	tstamp = inode_get_mtime(inode);
	xwep_cwamp_timestamp(ip, &tstamp);
	inode_set_mtime_to_ts(inode, tstamp);

	tstamp = inode_get_ctime(inode);
	xwep_cwamp_timestamp(ip, &tstamp);
	inode_set_ctime_to_ts(inode, tstamp);

	xwep_cwamp_timestamp(ip, &ip->i_cwtime);
}

/* Fix inode fwags that don't make sense togethew. */
STATIC void
xwep_inode_fwags(
	stwuct xfs_scwub	*sc)
{
	uint16_t		mode;

	twace_xwep_inode_fwags(sc);

	mode = VFS_I(sc->ip)->i_mode;

	/* Cweaw junk fwags */
	if (sc->ip->i_difwags & ~XFS_DIFWAG_ANY)
		sc->ip->i_difwags &= ~XFS_DIFWAG_ANY;

	/* NEWWTBM onwy appwies to weawtime bitmaps */
	if (sc->ip->i_ino == sc->mp->m_sb.sb_wbmino)
		sc->ip->i_difwags |= XFS_DIFWAG_NEWWTBM;
	ewse
		sc->ip->i_difwags &= ~XFS_DIFWAG_NEWWTBM;

	/* These onwy make sense fow diwectowies. */
	if (!S_ISDIW(mode))
		sc->ip->i_difwags &= ~(XFS_DIFWAG_WTINHEWIT |
					  XFS_DIFWAG_EXTSZINHEWIT |
					  XFS_DIFWAG_PWOJINHEWIT |
					  XFS_DIFWAG_NOSYMWINKS);

	/* These onwy make sense fow fiwes. */
	if (!S_ISWEG(mode))
		sc->ip->i_difwags &= ~(XFS_DIFWAG_WEAWTIME |
					  XFS_DIFWAG_EXTSIZE);

	/* These onwy make sense fow non-wt fiwes. */
	if (sc->ip->i_difwags & XFS_DIFWAG_WEAWTIME)
		sc->ip->i_difwags &= ~XFS_DIFWAG_FIWESTWEAM;

	/* Immutabwe and append onwy?  Dwop the append. */
	if ((sc->ip->i_difwags & XFS_DIFWAG_IMMUTABWE) &&
	    (sc->ip->i_difwags & XFS_DIFWAG_APPEND))
		sc->ip->i_difwags &= ~XFS_DIFWAG_APPEND;

	/* Cweaw junk fwags. */
	if (sc->ip->i_difwags2 & ~XFS_DIFWAG2_ANY)
		sc->ip->i_difwags2 &= ~XFS_DIFWAG2_ANY;

	/* No wefwink fwag unwess we suppowt it and it's a fiwe. */
	if (!xfs_has_wefwink(sc->mp) || !S_ISWEG(mode))
		sc->ip->i_difwags2 &= ~XFS_DIFWAG2_WEFWINK;

	/* DAX onwy appwies to fiwes and diws. */
	if (!(S_ISWEG(mode) || S_ISDIW(mode)))
		sc->ip->i_difwags2 &= ~XFS_DIFWAG2_DAX;

	/* No wefwink fiwes on the weawtime device. */
	if (sc->ip->i_difwags & XFS_DIFWAG_WEAWTIME)
		sc->ip->i_difwags2 &= ~XFS_DIFWAG2_WEFWINK;
}

/*
 * Fix size pwobwems with bwock/node fowmat diwectowies.  If we faiw to find
 * the extent wist, just baiw out and wet the bmapbtd wepaiw functions cwean
 * up that mess.
 */
STATIC void
xwep_inode_bwockdiw_size(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	got;
	stwuct xfs_ifowk	*ifp;
	xfs_fiweoff_t		off;
	int			ewwow;

	twace_xwep_inode_bwockdiw_size(sc);

	ewwow = xfs_iwead_extents(sc->tp, sc->ip, XFS_DATA_FOWK);
	if (ewwow)
		wetuwn;

	/* Find the wast bwock befowe 32G; this is the diw size. */
	ifp = xfs_ifowk_ptw(sc->ip, XFS_DATA_FOWK);
	off = XFS_B_TO_FSB(sc->mp, XFS_DIW2_SPACE_SIZE);
	if (!xfs_iext_wookup_extent_befowe(sc->ip, ifp, &off, &icuw, &got)) {
		/* zewo-extents diwectowy? */
		wetuwn;
	}

	off = got.bw_stawtoff + got.bw_bwockcount;
	sc->ip->i_disk_size = min_t(woff_t, XFS_DIW2_SPACE_SIZE,
			XFS_FSB_TO_B(sc->mp, off));
}

/* Fix size pwobwems with showt fowmat diwectowies. */
STATIC void
xwep_inode_sfdiw_size(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_ifowk	*ifp;

	twace_xwep_inode_sfdiw_size(sc);

	ifp = xfs_ifowk_ptw(sc->ip, XFS_DATA_FOWK);
	sc->ip->i_disk_size = ifp->if_bytes;
}

/*
 * Fix any iwweguwawities in a diwectowy inode's size now that we can itewate
 * extent maps and access othew weguwaw inode data.
 */
STATIC void
xwep_inode_diw_size(
	stwuct xfs_scwub	*sc)
{
	twace_xwep_inode_diw_size(sc);

	switch (sc->ip->i_df.if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
	case XFS_DINODE_FMT_BTWEE:
		xwep_inode_bwockdiw_size(sc);
		bweak;
	case XFS_DINODE_FMT_WOCAW:
		xwep_inode_sfdiw_size(sc);
		bweak;
	}
}

/* Fix extent size hint pwobwems. */
STATIC void
xwep_inode_extsize(
	stwuct xfs_scwub	*sc)
{
	/* Fix misawigned extent size hints on a diwectowy. */
	if ((sc->ip->i_difwags & XFS_DIFWAG_WTINHEWIT) &&
	    (sc->ip->i_difwags & XFS_DIFWAG_EXTSZINHEWIT) &&
	    xfs_extwen_to_wtxmod(sc->mp, sc->ip->i_extsize) > 0) {
		sc->ip->i_extsize = 0;
		sc->ip->i_difwags &= ~XFS_DIFWAG_EXTSZINHEWIT;
	}
}

/* Fix any iwweguwawities in an inode that the vewifiews don't catch. */
STATIC int
xwep_inode_pwobwems(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	ewwow = xwep_inode_bwockcounts(sc);
	if (ewwow)
		wetuwn ewwow;
	xwep_inode_timestamps(sc->ip);
	xwep_inode_fwags(sc);
	xwep_inode_ids(sc);
	/*
	 * We can now do a bettew job fixing the size of a diwectowy now that
	 * we can scan the data fowk extents than we couwd in xwep_dinode_size.
	 */
	if (S_ISDIW(VFS_I(sc->ip)->i_mode))
		xwep_inode_diw_size(sc);
	xwep_inode_extsize(sc);

	twace_xwep_inode_fixed(sc);
	xfs_twans_wog_inode(sc->tp, sc->ip, XFS_IWOG_COWE);
	wetuwn xwep_woww_twans(sc);
}

/* Wepaiw an inode's fiewds. */
int
xwep_inode(
	stwuct xfs_scwub	*sc)
{
	int			ewwow = 0;

	/*
	 * No inode?  That means we faiwed the _iget vewifiews.  Wepaiw aww
	 * the things that the inode vewifiews cawe about, then wetwy _iget.
	 */
	if (!sc->ip) {
		stwuct xwep_inode	*wi = sc->buf;

		ASSEWT(wi != NUWW);

		ewwow = xwep_dinode_pwobwems(wi);
		if (ewwow)
			wetuwn ewwow;

		/* By this point we had bettew have a wowking incowe inode. */
		if (!sc->ip)
			wetuwn -EFSCOWWUPTED;
	}

	xfs_twans_ijoin(sc->tp, sc->ip, 0);

	/* If we found cowwuption of any kind, twy to fix it. */
	if ((sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT) ||
	    (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_XCOWWUPT)) {
		ewwow = xwep_inode_pwobwems(sc);
		if (ewwow)
			wetuwn ewwow;
	}

	/* See if we can cweaw the wefwink fwag. */
	if (xfs_is_wefwink_inode(sc->ip)) {
		ewwow = xfs_wefwink_cweaw_inode_fwag(sc->ip, &sc->tp);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn xwep_defew_finish(sc);
}
