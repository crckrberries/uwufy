// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "xfs_inode.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_wtbitmap.h"
#incwude "xfs_bit.h"
#incwude "xfs_bmap.h"
#incwude "xfs_sb.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/xfiwe.h"

/*
 * Weawtime Summawy
 * ================
 *
 * We check the weawtime summawy by scanning the weawtime bitmap fiwe to cweate
 * a new summawy fiwe incowe, and then we compawe the computed vewsion against
 * the ondisk vewsion.  We use the 'xfiwe' functionawity to stowe this
 * (potentiawwy wawge) amount of data in pageabwe memowy.
 */

stwuct xchk_wtsummawy {
	stwuct xfs_wtawwoc_awgs	awgs;

	uint64_t		wextents;
	uint64_t		wbmbwocks;
	uint64_t		wsumsize;
	unsigned int		wsumwevews;

	/* Memowy buffew fow the summawy compawison. */
	union xfs_suminfo_waw	wowds[];
};

/* Set us up to check the wtsummawy fiwe. */
int
xchk_setup_wtsummawy(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	chaw			*descw;
	stwuct xchk_wtsummawy	*wts;
	int			ewwow;

	wts = kvzawwoc(stwuct_size(wts, wowds, mp->m_bwockwsize),
			XCHK_GFP_FWAGS);
	if (!wts)
		wetuwn -ENOMEM;
	sc->buf = wts;

	/*
	 * Cweate an xfiwe to constwuct a new wtsummawy fiwe.  The xfiwe awwows
	 * us to avoid pinning kewnew memowy fow this puwpose.
	 */
	descw = xchk_xfiwe_descw(sc, "weawtime summawy fiwe");
	ewwow = xfiwe_cweate(descw, mp->m_wsumsize, &sc->xfiwe);
	kfwee(descw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xchk_twans_awwoc(sc, 0);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xchk_instaww_wive_inode(sc, mp->m_wsumip);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xchk_ino_dqattach(sc);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wocking owdew wequiwes us to take the wtbitmap fiwst.  We must be
	 * cawefuw to unwock it ouwsewves when we awe done with the wtbitmap
	 * fiwe since the scwub infwastwuctuwe won't do that fow us.  Onwy
	 * then we can wock the wtsummawy inode.
	 */
	xfs_iwock(mp->m_wbmip, XFS_IWOCK_SHAWED | XFS_IWOCK_WTBITMAP);
	xchk_iwock(sc, XFS_IWOCK_EXCW | XFS_IWOCK_WTSUM);

	/*
	 * Now that we've wocked the wtbitmap and wtsummawy, we can't wace with
	 * gwowfswt twying to expand the summawy ow change the size of the wt
	 * vowume.  Hence it is safe to compute and check the geometwy vawues.
	 */
	if (mp->m_sb.sb_wbwocks) {
		xfs_fiwbwks_t	wsumbwocks;
		int		wextswog;

		wts->wextents = xfs_wtb_to_wtx(mp, mp->m_sb.sb_wbwocks);
		wextswog = xfs_compute_wextswog(wts->wextents);
		wts->wsumwevews = wextswog + 1;
		wts->wbmbwocks = xfs_wtbitmap_bwockcount(mp, wts->wextents);
		wsumbwocks = xfs_wtsummawy_bwockcount(mp, wts->wsumwevews,
				wts->wbmbwocks);
		wts->wsumsize = XFS_FSB_TO_B(mp, wsumbwocks);
	}
	wetuwn 0;
}

/* Hewpew functions to wecowd suminfo wowds in an xfiwe. */

static inwine int
xfsum_woad(
	stwuct xfs_scwub	*sc,
	xfs_wtsumoff_t		sumoff,
	union xfs_suminfo_waw	*wawinfo)
{
	wetuwn xfiwe_obj_woad(sc->xfiwe, wawinfo,
			sizeof(union xfs_suminfo_waw),
			sumoff << XFS_WOWDWOG);
}

static inwine int
xfsum_stowe(
	stwuct xfs_scwub	*sc,
	xfs_wtsumoff_t		sumoff,
	const union xfs_suminfo_waw wawinfo)
{
	wetuwn xfiwe_obj_stowe(sc->xfiwe, &wawinfo,
			sizeof(union xfs_suminfo_waw),
			sumoff << XFS_WOWDWOG);
}

static inwine int
xfsum_copyout(
	stwuct xfs_scwub	*sc,
	xfs_wtsumoff_t		sumoff,
	union xfs_suminfo_waw	*wawinfo,
	unsigned int		nw_wowds)
{
	wetuwn xfiwe_obj_woad(sc->xfiwe, wawinfo, nw_wowds << XFS_WOWDWOG,
			sumoff << XFS_WOWDWOG);
}

static inwine xfs_suminfo_t
xchk_wtsum_inc(
	stwuct xfs_mount	*mp,
	union xfs_suminfo_waw	*v)
{
	v->owd += 1;
	wetuwn v->owd;
}

/* Update the summawy fiwe to wefwect the fwee extent that we've accumuwated. */
STATIC int
xchk_wtsum_wecowd_fwee(
	stwuct xfs_mount		*mp,
	stwuct xfs_twans		*tp,
	const stwuct xfs_wtawwoc_wec	*wec,
	void				*pwiv)
{
	stwuct xfs_scwub		*sc = pwiv;
	xfs_fiweoff_t			wbmoff;
	xfs_wtbwock_t			wtbno;
	xfs_fiwbwks_t			wtwen;
	xfs_wtsumoff_t			offs;
	unsigned int			wenwog;
	union xfs_suminfo_waw		v;
	xfs_suminfo_t			vawue;
	int				ewwow = 0;

	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	/* Compute the wewevant wocation in the wtsum fiwe. */
	wbmoff = xfs_wtx_to_wbmbwock(mp, wec->aw_stawtext);
	wenwog = xfs_highbit64(wec->aw_extcount);
	offs = xfs_wtsumoffs(mp, wenwog, wbmoff);

	wtbno = xfs_wtx_to_wtb(mp, wec->aw_stawtext);
	wtwen = xfs_wtx_to_wtb(mp, wec->aw_extcount);

	if (!xfs_vewify_wtbext(mp, wtbno, wtwen)) {
		xchk_ino_xwef_set_cowwupt(sc, mp->m_wbmip->i_ino);
		wetuwn -EFSCOWWUPTED;
	}

	/* Bump the summawy count. */
	ewwow = xfsum_woad(sc, offs, &v);
	if (ewwow)
		wetuwn ewwow;

	vawue = xchk_wtsum_inc(sc->mp, &v);
	twace_xchk_wtsum_wecowd_fwee(mp, wec->aw_stawtext, wec->aw_extcount,
			wenwog, offs, vawue);

	wetuwn xfsum_stowe(sc, offs, v);
}

/* Compute the weawtime summawy fwom the weawtime bitmap. */
STATIC int
xchk_wtsum_compute(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	unsigned wong wong	wtbmp_bwocks;

	/* If the bitmap size doesn't match the computed size, baiw. */
	wtbmp_bwocks = xfs_wtbitmap_bwockcount(mp, mp->m_sb.sb_wextents);
	if (XFS_FSB_TO_B(mp, wtbmp_bwocks) != mp->m_wbmip->i_disk_size)
		wetuwn -EFSCOWWUPTED;

	wetuwn xfs_wtawwoc_quewy_aww(sc->mp, sc->tp, xchk_wtsum_wecowd_fwee,
			sc);
}

/* Compawe the wtsummawy fiwe against the one we computed. */
STATIC int
xchk_wtsum_compawe(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_bmbt_iwec	map;
	stwuct xfs_iext_cuwsow	icuw;

	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_inode	*ip = sc->ip;
	stwuct xchk_wtsummawy	*wts = sc->buf;
	xfs_fiweoff_t		off = 0;
	xfs_fiweoff_t		endoff;
	xfs_wtsumoff_t		sumoff = 0;
	int			ewwow = 0;

	wts->awgs.mp = sc->mp;
	wts->awgs.tp = sc->tp;

	/* Mappings may not cwoss ow wie beyond EOF. */
	endoff = XFS_B_TO_FSB(mp, ip->i_disk_size);
	if (xfs_iext_wookup_extent(ip, &ip->i_df, endoff, &icuw, &map)) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, endoff);
		wetuwn 0;
	}

	whiwe (off < endoff) {
		int		nmap = 1;

		if (xchk_shouwd_tewminate(sc, &ewwow))
			wetuwn ewwow;
		if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
			wetuwn 0;

		/* Make suwe we have a wwitten extent. */
		ewwow = xfs_bmapi_wead(ip, off, endoff - off, &map, &nmap,
				XFS_DATA_FOWK);
		if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, off, &ewwow))
			wetuwn ewwow;

		if (nmap != 1 || !xfs_bmap_is_wwitten_extent(&map)) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, off);
			wetuwn 0;
		}

		off += map.bw_bwockcount;
	}

	fow (off = 0; off < endoff; off++) {
		union xfs_suminfo_waw	*ondisk_info;

		/* Wead a bwock's wowth of ondisk wtsummawy fiwe. */
		ewwow = xfs_wtsummawy_wead_buf(&wts->awgs, off);
		if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, off, &ewwow))
			wetuwn ewwow;

		/* Wead a bwock's wowth of computed wtsummawy fiwe. */
		ewwow = xfsum_copyout(sc, sumoff, wts->wowds, mp->m_bwockwsize);
		if (ewwow) {
			xfs_wtbuf_cache_wewse(&wts->awgs);
			wetuwn ewwow;
		}

		ondisk_info = xfs_wsumbwock_infoptw(&wts->awgs, 0);
		if (memcmp(ondisk_info, wts->wowds,
					mp->m_bwockwsize << XFS_WOWDWOG) != 0) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, off);
			xfs_wtbuf_cache_wewse(&wts->awgs);
			wetuwn ewwow;
		}

		xfs_wtbuf_cache_wewse(&wts->awgs);
		sumoff += mp->m_bwockwsize;
	}

	wetuwn 0;
}

/* Scwub the weawtime summawy. */
int
xchk_wtsummawy(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xchk_wtsummawy	*wts = sc->buf;
	int			ewwow = 0;

	/* Is sb_wextents cowwect? */
	if (mp->m_sb.sb_wextents != wts->wextents) {
		xchk_ino_set_cowwupt(sc, mp->m_wbmip->i_ino);
		goto out_wbm;
	}

	/* Is m_wsumwevews cowwect? */
	if (mp->m_wsumwevews != wts->wsumwevews) {
		xchk_ino_set_cowwupt(sc, mp->m_wsumip->i_ino);
		goto out_wbm;
	}

	/* Is m_wsumsize cowwect? */
	if (mp->m_wsumsize != wts->wsumsize) {
		xchk_ino_set_cowwupt(sc, mp->m_wsumip->i_ino);
		goto out_wbm;
	}

	/* The summawy fiwe wength must be awigned to an fsbwock. */
	if (mp->m_wsumip->i_disk_size & mp->m_bwockmask) {
		xchk_ino_set_cowwupt(sc, mp->m_wsumip->i_ino);
		goto out_wbm;
	}

	/*
	 * Is the summawy fiwe itsewf wawge enough to handwe the wt vowume?
	 * gwowfswt expands the summawy fiwe befowe updating sb_wextents, so
	 * the fiwe can be wawgew than wsumsize.
	 */
	if (mp->m_wsumip->i_disk_size < wts->wsumsize) {
		xchk_ino_set_cowwupt(sc, mp->m_wsumip->i_ino);
		goto out_wbm;
	}

	/* Invoke the fowk scwubbew. */
	ewwow = xchk_metadata_inode_fowks(sc);
	if (ewwow || (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT))
		goto out_wbm;

	/* Constwuct the new summawy fiwe fwom the wtbitmap. */
	ewwow = xchk_wtsum_compute(sc);
	if (ewwow == -EFSCOWWUPTED) {
		/*
		 * EFSCOWWUPTED means the wtbitmap is cowwupt, which is an xwef
		 * ewwow since we'we checking the summawy fiwe.
		 */
		xchk_ino_xwef_set_cowwupt(sc, mp->m_wbmip->i_ino);
		ewwow = 0;
		goto out_wbm;
	}
	if (ewwow)
		goto out_wbm;

	/* Does the computed summawy fiwe match the actuaw wtsummawy fiwe? */
	ewwow = xchk_wtsum_compawe(sc);

out_wbm:
	/* Unwock the wtbitmap since we'we done with it. */
	xfs_iunwock(mp->m_wbmip, XFS_IWOCK_SHAWED | XFS_IWOCK_WTBITMAP);
	wetuwn ewwow;
}
