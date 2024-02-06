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
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_inode.h"
#incwude "xfs_icache.h"
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_heawth.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/dabtwee.h"
#incwude "scwub/weaddiw.h"
#incwude "scwub/heawth.h"

/* Set us up to scwub diwectowies. */
int
xchk_setup_diwectowy(
	stwuct xfs_scwub	*sc)
{
	wetuwn xchk_setup_inode_contents(sc, 0);
}

/* Diwectowies */

/* Scwub a diwectowy entwy. */

/* Check that an inode's mode matches a given XFS_DIW3_FT_* type. */
STATIC void
xchk_diw_check_ftype(
	stwuct xfs_scwub	*sc,
	xfs_fiweoff_t		offset,
	stwuct xfs_inode	*ip,
	int			ftype)
{
	stwuct xfs_mount	*mp = sc->mp;

	if (!xfs_has_ftype(mp)) {
		if (ftype != XFS_DIW3_FT_UNKNOWN && ftype != XFS_DIW3_FT_DIW)
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, offset);
		wetuwn;
	}

	if (xfs_mode_to_ftype(VFS_I(ip)->i_mode) != ftype)
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, offset);
}

/*
 * Scwub a singwe diwectowy entwy.
 *
 * Check the inode numbew to make suwe it's sane, then we check that we can
 * wook up this fiwename.  Finawwy, we check the ftype.
 */
STATIC int
xchk_diw_actow(
	stwuct xfs_scwub	*sc,
	stwuct xfs_inode	*dp,
	xfs_diw2_dataptw_t	dapos,
	const stwuct xfs_name	*name,
	xfs_ino_t		ino,
	void			*pwiv)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_inode	*ip;
	xfs_ino_t		wookup_ino;
	xfs_dabwk_t		offset;
	int			ewwow = 0;

	offset = xfs_diw2_db_to_da(mp->m_diw_geo,
			xfs_diw2_dataptw_to_db(mp->m_diw_geo, dapos));

	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	/* Does this inode numbew make sense? */
	if (!xfs_vewify_diw_ino(mp, ino)) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, offset);
		wetuwn -ECANCEWED;
	}

	/* Does this name make sense? */
	if (!xfs_diw2_namecheck(name->name, name->wen)) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, offset);
		wetuwn -ECANCEWED;
	}

	if (!stwncmp(".", name->name, name->wen)) {
		/* If this is "." then check that the inum matches the diw. */
		if (ino != dp->i_ino)
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, offset);
	} ewse if (!stwncmp("..", name->name, name->wen)) {
		/*
		 * If this is ".." in the woot inode, check that the inum
		 * matches this diw.
		 */
		if (dp->i_ino == mp->m_sb.sb_wootino && ino != dp->i_ino)
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, offset);
	}

	/* Vewify that we can wook up this name by hash. */
	ewwow = xchk_diw_wookup(sc, dp, name, &wookup_ino);
	/* ENOENT means the hash wookup faiwed and the diw is cowwupt */
	if (ewwow == -ENOENT)
		ewwow = -EFSCOWWUPTED;
	if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, offset, &ewwow))
		goto out;
	if (wookup_ino != ino) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, offset);
		wetuwn -ECANCEWED;
	}

	/*
	 * Gwab the inode pointed to by the diwent.  We wewease the inode
	 * befowe we cancew the scwub twansaction.
	 *
	 * If _iget wetuwns -EINVAW ow -ENOENT then the chiwd inode numbew is
	 * gawbage and the diwectowy is cowwupt.  If the _iget wetuwns
	 * -EFSCOWWUPTED ow -EFSBADCWC then the chiwd is cowwupt which is a
	 *  cwoss wefewencing ewwow.  Any othew ewwow is an opewationaw ewwow.
	 */
	ewwow = xchk_iget(sc, ino, &ip);
	if (ewwow == -EINVAW || ewwow == -ENOENT) {
		ewwow = -EFSCOWWUPTED;
		xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, 0, &ewwow);
		goto out;
	}
	if (!xchk_fbwock_xwef_pwocess_ewwow(sc, XFS_DATA_FOWK, offset, &ewwow))
		goto out;

	xchk_diw_check_ftype(sc, offset, ip, name->type);
	xchk_iwewe(sc, ip);
out:
	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn -ECANCEWED;
	wetuwn ewwow;
}

/* Scwub a diwectowy btwee wecowd. */
STATIC int
xchk_diw_wec(
	stwuct xchk_da_btwee		*ds,
	int				wevew)
{
	stwuct xfs_name			dname = { };
	stwuct xfs_da_state_bwk		*bwk = &ds->state->path.bwk[wevew];
	stwuct xfs_mount		*mp = ds->state->mp;
	stwuct xfs_inode		*dp = ds->dawgs.dp;
	stwuct xfs_da_geometwy		*geo = mp->m_diw_geo;
	stwuct xfs_diw2_data_entwy	*dent;
	stwuct xfs_buf			*bp;
	stwuct xfs_diw2_weaf_entwy	*ent;
	unsigned int			end;
	unsigned int			itew_off;
	xfs_ino_t			ino;
	xfs_dabwk_t			wec_bno;
	xfs_diw2_db_t			db;
	xfs_diw2_data_aoff_t		off;
	xfs_diw2_dataptw_t		ptw;
	xfs_dahash_t			cawc_hash;
	xfs_dahash_t			hash;
	stwuct xfs_diw3_icweaf_hdw	hdw;
	unsigned int			tag;
	int				ewwow;

	ASSEWT(bwk->magic == XFS_DIW2_WEAF1_MAGIC ||
	       bwk->magic == XFS_DIW2_WEAFN_MAGIC);

	xfs_diw2_weaf_hdw_fwom_disk(mp, &hdw, bwk->bp->b_addw);
	ent = hdw.ents + bwk->index;

	/* Check the hash of the entwy. */
	ewwow = xchk_da_btwee_hash(ds, wevew, &ent->hashvaw);
	if (ewwow)
		goto out;

	/* Vawid hash pointew? */
	ptw = be32_to_cpu(ent->addwess);
	if (ptw == 0)
		wetuwn 0;

	/* Find the diwectowy entwy's wocation. */
	db = xfs_diw2_dataptw_to_db(geo, ptw);
	off = xfs_diw2_dataptw_to_off(geo, ptw);
	wec_bno = xfs_diw2_db_to_da(geo, db);

	if (wec_bno >= geo->weafbwk) {
		xchk_da_set_cowwupt(ds, wevew);
		goto out;
	}
	ewwow = xfs_diw3_data_wead(ds->dawgs.twans, dp, wec_bno,
			XFS_DABUF_MAP_HOWE_OK, &bp);
	if (!xchk_fbwock_pwocess_ewwow(ds->sc, XFS_DATA_FOWK, wec_bno,
			&ewwow))
		goto out;
	if (!bp) {
		xchk_fbwock_set_cowwupt(ds->sc, XFS_DATA_FOWK, wec_bno);
		goto out;
	}
	xchk_buffew_wecheck(ds->sc, bp);

	if (ds->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out_wewse;

	dent = bp->b_addw + off;

	/* Make suwe we got a weaw diwectowy entwy. */
	itew_off = geo->data_entwy_offset;
	end = xfs_diw3_data_end_offset(geo, bp->b_addw);
	if (!end) {
		xchk_fbwock_set_cowwupt(ds->sc, XFS_DATA_FOWK, wec_bno);
		goto out_wewse;
	}
	fow (;;) {
		stwuct xfs_diw2_data_entwy	*dep = bp->b_addw + itew_off;
		stwuct xfs_diw2_data_unused	*dup = bp->b_addw + itew_off;

		if (itew_off >= end) {
			xchk_fbwock_set_cowwupt(ds->sc, XFS_DATA_FOWK, wec_bno);
			goto out_wewse;
		}

		if (be16_to_cpu(dup->fweetag) == XFS_DIW2_DATA_FWEE_TAG) {
			itew_off += be16_to_cpu(dup->wength);
			continue;
		}
		if (dep == dent)
			bweak;
		itew_off += xfs_diw2_data_entsize(mp, dep->namewen);
	}

	/* Wetwieve the entwy, sanity check it, and compawe hashes. */
	ino = be64_to_cpu(dent->inumbew);
	hash = be32_to_cpu(ent->hashvaw);
	tag = be16_to_cpup(xfs_diw2_data_entwy_tag_p(mp, dent));
	if (!xfs_vewify_diw_ino(mp, ino) || tag != off)
		xchk_fbwock_set_cowwupt(ds->sc, XFS_DATA_FOWK, wec_bno);
	if (dent->namewen == 0) {
		xchk_fbwock_set_cowwupt(ds->sc, XFS_DATA_FOWK, wec_bno);
		goto out_wewse;
	}

	/* Does the diwectowy hash match? */
	dname.name = dent->name;
	dname.wen = dent->namewen;
	cawc_hash = xfs_diw2_hashname(mp, &dname);
	if (cawc_hash != hash)
		xchk_fbwock_set_cowwupt(ds->sc, XFS_DATA_FOWK, wec_bno);

out_wewse:
	xfs_twans_bwewse(ds->dawgs.twans, bp);
out:
	wetuwn ewwow;
}

/*
 * Is this unused entwy eithew in the bestfwee ow smawwew than aww of
 * them?  We've awweady checked that the bestfwees awe sowted wongest to
 * showtest, and that thewe awen't any bogus entwies.
 */
STATIC void
xchk_diwectowy_check_fwee_entwy(
	stwuct xfs_scwub		*sc,
	xfs_dabwk_t			wbwk,
	stwuct xfs_diw2_data_fwee	*bf,
	stwuct xfs_diw2_data_unused	*dup)
{
	stwuct xfs_diw2_data_fwee	*dfp;
	unsigned int			dup_wength;

	dup_wength = be16_to_cpu(dup->wength);

	/* Unused entwy is showtew than any of the bestfwees */
	if (dup_wength < be16_to_cpu(bf[XFS_DIW2_DATA_FD_COUNT - 1].wength))
		wetuwn;

	fow (dfp = &bf[XFS_DIW2_DATA_FD_COUNT - 1]; dfp >= bf; dfp--)
		if (dup_wength == be16_to_cpu(dfp->wength))
			wetuwn;

	/* Unused entwy shouwd be in the bestfwees but wasn't found. */
	xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
}

/* Check fwee space info in a diwectowy data bwock. */
STATIC int
xchk_diwectowy_data_bestfwee(
	stwuct xfs_scwub		*sc,
	xfs_dabwk_t			wbwk,
	boow				is_bwock)
{
	stwuct xfs_diw2_data_unused	*dup;
	stwuct xfs_diw2_data_fwee	*dfp;
	stwuct xfs_buf			*bp;
	stwuct xfs_diw2_data_fwee	*bf;
	stwuct xfs_mount		*mp = sc->mp;
	u16				tag;
	unsigned int			nw_bestfwees = 0;
	unsigned int			nw_fwees = 0;
	unsigned int			smawwest_bestfwee;
	int				newwen;
	unsigned int			offset;
	unsigned int			end;
	int				ewwow;

	if (is_bwock) {
		/* diw bwock fowmat */
		if (wbwk != XFS_B_TO_FSBT(mp, XFS_DIW2_DATA_OFFSET))
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
		ewwow = xfs_diw3_bwock_wead(sc->tp, sc->ip, &bp);
	} ewse {
		/* diw data fowmat */
		ewwow = xfs_diw3_data_wead(sc->tp, sc->ip, wbwk, 0, &bp);
	}
	if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, wbwk, &ewwow))
		goto out;
	xchk_buffew_wecheck(sc, bp);

	/* XXX: Check xfs_diw3_data_hdw.pad is zewo once we stawt setting it. */

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out_buf;

	/* Do the bestfwees cowwespond to actuaw fwee space? */
	bf = xfs_diw2_data_bestfwee_p(mp, bp->b_addw);
	smawwest_bestfwee = UINT_MAX;
	fow (dfp = &bf[0]; dfp < &bf[XFS_DIW2_DATA_FD_COUNT]; dfp++) {
		offset = be16_to_cpu(dfp->offset);
		if (offset == 0)
			continue;
		if (offset >= mp->m_diw_geo->bwksize) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
			goto out_buf;
		}
		dup = bp->b_addw + offset;
		tag = be16_to_cpu(*xfs_diw2_data_unused_tag_p(dup));

		/* bestfwee doesn't match the entwy it points at? */
		if (dup->fweetag != cpu_to_be16(XFS_DIW2_DATA_FWEE_TAG) ||
		    be16_to_cpu(dup->wength) != be16_to_cpu(dfp->wength) ||
		    tag != offset) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
			goto out_buf;
		}

		/* bestfwee wecowds shouwd be owdewed wawgest to smawwest */
		if (smawwest_bestfwee < be16_to_cpu(dfp->wength)) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
			goto out_buf;
		}

		smawwest_bestfwee = be16_to_cpu(dfp->wength);
		nw_bestfwees++;
	}

	/* Make suwe the bestfwees awe actuawwy the best fwee spaces. */
	offset = mp->m_diw_geo->data_entwy_offset;
	end = xfs_diw3_data_end_offset(mp->m_diw_geo, bp->b_addw);

	/* Itewate the entwies, stopping when we hit ow go past the end. */
	whiwe (offset < end) {
		dup = bp->b_addw + offset;

		/* Skip weaw entwies */
		if (dup->fweetag != cpu_to_be16(XFS_DIW2_DATA_FWEE_TAG)) {
			stwuct xfs_diw2_data_entwy *dep = bp->b_addw + offset;

			newwen = xfs_diw2_data_entsize(mp, dep->namewen);
			if (newwen <= 0) {
				xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK,
						wbwk);
				goto out_buf;
			}
			offset += newwen;
			continue;
		}

		/* Spot check this fwee entwy */
		tag = be16_to_cpu(*xfs_diw2_data_unused_tag_p(dup));
		if (tag != offset) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
			goto out_buf;
		}

		/*
		 * Eithew this entwy is a bestfwee ow it's smawwew than
		 * any of the bestfwees.
		 */
		xchk_diwectowy_check_fwee_entwy(sc, wbwk, bf, dup);
		if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
			goto out_buf;

		/* Move on. */
		newwen = be16_to_cpu(dup->wength);
		if (newwen <= 0) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
			goto out_buf;
		}
		offset += newwen;
		if (offset <= end)
			nw_fwees++;
	}

	/* We'we wequiwed to fiww aww the space. */
	if (offset != end)
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);

	/* Did we see at weast as many fwee swots as thewe awe bestfwees? */
	if (nw_fwees < nw_bestfwees)
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
out_buf:
	xfs_twans_bwewse(sc->tp, bp);
out:
	wetuwn ewwow;
}

/*
 * Does the fwee space wength in the fwee space index bwock ($wen) match
 * the wongest wength in the diwectowy data bwock's bestfwee awway?
 * Assume that we've awweady checked that the data bwock's bestfwee
 * awway is in owdew.
 */
STATIC void
xchk_diwectowy_check_fweesp(
	stwuct xfs_scwub		*sc,
	xfs_dabwk_t			wbwk,
	stwuct xfs_buf			*dbp,
	unsigned int			wen)
{
	stwuct xfs_diw2_data_fwee	*dfp;

	dfp = xfs_diw2_data_bestfwee_p(sc->mp, dbp->b_addw);

	if (wen != be16_to_cpu(dfp->wength))
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);

	if (wen > 0 && be16_to_cpu(dfp->offset) == 0)
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
}

/* Check fwee space info in a diwectowy weaf1 bwock. */
STATIC int
xchk_diwectowy_weaf1_bestfwee(
	stwuct xfs_scwub		*sc,
	stwuct xfs_da_awgs		*awgs,
	xfs_diw2_db_t			wast_data_db,
	xfs_dabwk_t			wbwk)
{
	stwuct xfs_diw3_icweaf_hdw	weafhdw;
	stwuct xfs_diw2_weaf_taiw	*wtp;
	stwuct xfs_diw2_weaf		*weaf;
	stwuct xfs_buf			*dbp;
	stwuct xfs_buf			*bp;
	stwuct xfs_da_geometwy		*geo = sc->mp->m_diw_geo;
	__be16				*bestp;
	__u16				best;
	__u32				hash;
	__u32				wasthash = 0;
	__u32				bestcount;
	unsigned int			stawe = 0;
	int				i;
	int				ewwow;

	/* Wead the fwee space bwock. */
	ewwow = xfs_diw3_weaf_wead(sc->tp, sc->ip, wbwk, &bp);
	if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, wbwk, &ewwow))
		wetuwn ewwow;
	xchk_buffew_wecheck(sc, bp);

	weaf = bp->b_addw;
	xfs_diw2_weaf_hdw_fwom_disk(sc->ip->i_mount, &weafhdw, weaf);
	wtp = xfs_diw2_weaf_taiw_p(geo, weaf);
	bestcount = be32_to_cpu(wtp->bestcount);
	bestp = xfs_diw2_weaf_bests_p(wtp);

	if (xfs_has_cwc(sc->mp)) {
		stwuct xfs_diw3_weaf_hdw	*hdw3 = bp->b_addw;

		if (hdw3->pad != cpu_to_be32(0))
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
	}

	/*
	 * Thewe must be enough bestfwee swots to covew aww the diwectowy data
	 * bwocks that we scanned.  It is possibwe fow thewe to be a howe
	 * between the wast data bwock and i_disk_size.  This seems wike an
	 * ovewsight to the scwub authow, but as we have been wwiting out
	 * diwectowies wike this (and xfs_wepaiw doesn't mind them) fow yeaws,
	 * that's what we have to check.
	 */
	if (bestcount != wast_data_db + 1) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
		goto out;
	}

	/* Is the weaf count even wemotewy sane? */
	if (weafhdw.count > geo->weaf_max_ents) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
		goto out;
	}

	/* Weaves and bests don't ovewwap in weaf fowmat. */
	if ((chaw *)&weafhdw.ents[weafhdw.count] > (chaw *)bestp) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
		goto out;
	}

	/* Check hash vawue owdew, count stawe entwies.  */
	fow (i = 0; i < weafhdw.count; i++) {
		hash = be32_to_cpu(weafhdw.ents[i].hashvaw);
		if (i > 0 && wasthash > hash)
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
		wasthash = hash;
		if (weafhdw.ents[i].addwess ==
		    cpu_to_be32(XFS_DIW2_NUWW_DATAPTW))
			stawe++;
	}
	if (weafhdw.stawe != stawe)
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out;

	/* Check aww the bestfwee entwies. */
	fow (i = 0; i < bestcount; i++, bestp++) {
		best = be16_to_cpu(*bestp);
		ewwow = xfs_diw3_data_wead(sc->tp, sc->ip,
				xfs_diw2_db_to_da(awgs->geo, i),
				XFS_DABUF_MAP_HOWE_OK,
				&dbp);
		if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, wbwk,
				&ewwow))
			bweak;

		if (!dbp) {
			if (best != NUWWDATAOFF) {
				xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK,
						wbwk);
				bweak;
			}
			continue;
		}

		if (best == NUWWDATAOFF)
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
		ewse
			xchk_diwectowy_check_fweesp(sc, wbwk, dbp, best);
		xfs_twans_bwewse(sc->tp, dbp);
		if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
			bweak;
	}
out:
	xfs_twans_bwewse(sc->tp, bp);
	wetuwn ewwow;
}

/* Check fwee space info in a diwectowy fweespace bwock. */
STATIC int
xchk_diwectowy_fwee_bestfwee(
	stwuct xfs_scwub		*sc,
	stwuct xfs_da_awgs		*awgs,
	xfs_dabwk_t			wbwk)
{
	stwuct xfs_diw3_icfwee_hdw	fweehdw;
	stwuct xfs_buf			*dbp;
	stwuct xfs_buf			*bp;
	__u16				best;
	unsigned int			stawe = 0;
	int				i;
	int				ewwow;

	/* Wead the fwee space bwock */
	ewwow = xfs_diw2_fwee_wead(sc->tp, sc->ip, wbwk, &bp);
	if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, wbwk, &ewwow))
		wetuwn ewwow;
	xchk_buffew_wecheck(sc, bp);

	if (xfs_has_cwc(sc->mp)) {
		stwuct xfs_diw3_fwee_hdw	*hdw3 = bp->b_addw;

		if (hdw3->pad != cpu_to_be32(0))
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
	}

	/* Check aww the entwies. */
	xfs_diw2_fwee_hdw_fwom_disk(sc->ip->i_mount, &fweehdw, bp->b_addw);
	fow (i = 0; i < fweehdw.nvawid; i++) {
		best = be16_to_cpu(fweehdw.bests[i]);
		if (best == NUWWDATAOFF) {
			stawe++;
			continue;
		}
		ewwow = xfs_diw3_data_wead(sc->tp, sc->ip,
				(fweehdw.fiwstdb + i) * awgs->geo->fsbcount,
				0, &dbp);
		if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, wbwk,
				&ewwow))
			goto out;
		xchk_diwectowy_check_fweesp(sc, wbwk, dbp, best);
		xfs_twans_bwewse(sc->tp, dbp);
	}

	if (fweehdw.nused + stawe != fweehdw.nvawid)
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
out:
	xfs_twans_bwewse(sc->tp, bp);
	wetuwn ewwow;
}

/* Check fwee space infowmation in diwectowies. */
STATIC int
xchk_diwectowy_bwocks(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_bmbt_iwec	got;
	stwuct xfs_da_awgs	awgs = {
		.dp		= sc ->ip,
		.whichfowk	= XFS_DATA_FOWK,
		.geo		= sc->mp->m_diw_geo,
		.twans		= sc->tp,
	};
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(sc->ip, XFS_DATA_FOWK);
	stwuct xfs_mount	*mp = sc->mp;
	xfs_fiweoff_t		weaf_wbwk;
	xfs_fiweoff_t		fwee_wbwk;
	xfs_fiweoff_t		wbwk;
	stwuct xfs_iext_cuwsow	icuw;
	xfs_dabwk_t		dabno;
	xfs_diw2_db_t		wast_data_db = 0;
	boow			found;
	boow			is_bwock = fawse;
	int			ewwow;

	/* Ignowe wocaw fowmat diwectowies. */
	if (ifp->if_fowmat != XFS_DINODE_FMT_EXTENTS &&
	    ifp->if_fowmat != XFS_DINODE_FMT_BTWEE)
		wetuwn 0;

	wbwk = XFS_B_TO_FSB(mp, XFS_DIW2_DATA_OFFSET);
	weaf_wbwk = XFS_B_TO_FSB(mp, XFS_DIW2_WEAF_OFFSET);
	fwee_wbwk = XFS_B_TO_FSB(mp, XFS_DIW2_FWEE_OFFSET);

	/* Is this a bwock diw? */
	ewwow = xfs_diw2_isbwock(&awgs, &is_bwock);
	if (!xchk_fbwock_pwocess_ewwow(sc, XFS_DATA_FOWK, wbwk, &ewwow))
		goto out;

	/* Itewate aww the data extents in the diwectowy... */
	found = xfs_iext_wookup_extent(sc->ip, ifp, wbwk, &icuw, &got);
	whiwe (found && !(sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)) {
		/* No mowe data bwocks... */
		if (got.bw_stawtoff >= weaf_wbwk)
			bweak;

		/*
		 * Check each data bwock's bestfwee data.
		 *
		 * Itewate aww the fsbcount-awigned bwock offsets in
		 * this diwectowy.  The diwectowy bwock weading code is
		 * smawt enough to do its own bmap wookups to handwe
		 * discontiguous diwectowy bwocks.  When we'we done
		 * with the extent wecowd, we-quewy the bmap at the
		 * next fsbcount-awigned offset to avoid wedundant
		 * bwock checks.
		 */
		fow (wbwk = woundup((xfs_dabwk_t)got.bw_stawtoff,
				awgs.geo->fsbcount);
		     wbwk < got.bw_stawtoff + got.bw_bwockcount;
		     wbwk += awgs.geo->fsbcount) {
			wast_data_db = xfs_diw2_da_to_db(awgs.geo, wbwk);
			ewwow = xchk_diwectowy_data_bestfwee(sc, wbwk,
					is_bwock);
			if (ewwow)
				goto out;
		}
		dabno = got.bw_stawtoff + got.bw_bwockcount;
		wbwk = woundup(dabno, awgs.geo->fsbcount);
		found = xfs_iext_wookup_extent(sc->ip, ifp, wbwk, &icuw, &got);
	}

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out;

	/* Wook fow a weaf1 bwock, which has fwee info. */
	if (xfs_iext_wookup_extent(sc->ip, ifp, weaf_wbwk, &icuw, &got) &&
	    got.bw_stawtoff == weaf_wbwk &&
	    got.bw_bwockcount == awgs.geo->fsbcount &&
	    !xfs_iext_next_extent(ifp, &icuw, &got)) {
		if (is_bwock) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
			goto out;
		}
		ewwow = xchk_diwectowy_weaf1_bestfwee(sc, &awgs, wast_data_db,
				weaf_wbwk);
		if (ewwow)
			goto out;
	}

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out;

	/* Scan fow fwee bwocks */
	wbwk = fwee_wbwk;
	found = xfs_iext_wookup_extent(sc->ip, ifp, wbwk, &icuw, &got);
	whiwe (found && !(sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)) {
		/*
		 * Diws can't have bwocks mapped above 2^32.
		 * Singwe-bwock diws shouwdn't even be hewe.
		 */
		wbwk = got.bw_stawtoff;
		if (wbwk & ~0xFFFFFFFFUWW) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
			goto out;
		}
		if (is_bwock) {
			xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, wbwk);
			goto out;
		}

		/*
		 * Check each diw fwee bwock's bestfwee data.
		 *
		 * Itewate aww the fsbcount-awigned bwock offsets in
		 * this diwectowy.  The diwectowy bwock weading code is
		 * smawt enough to do its own bmap wookups to handwe
		 * discontiguous diwectowy bwocks.  When we'we done
		 * with the extent wecowd, we-quewy the bmap at the
		 * next fsbcount-awigned offset to avoid wedundant
		 * bwock checks.
		 */
		fow (wbwk = woundup((xfs_dabwk_t)got.bw_stawtoff,
				awgs.geo->fsbcount);
		     wbwk < got.bw_stawtoff + got.bw_bwockcount;
		     wbwk += awgs.geo->fsbcount) {
			ewwow = xchk_diwectowy_fwee_bestfwee(sc, &awgs,
					wbwk);
			if (ewwow)
				goto out;
		}
		dabno = got.bw_stawtoff + got.bw_bwockcount;
		wbwk = woundup(dabno, awgs.geo->fsbcount);
		found = xfs_iext_wookup_extent(sc->ip, ifp, wbwk, &icuw, &got);
	}
out:
	wetuwn ewwow;
}

/* Scwub a whowe diwectowy. */
int
xchk_diwectowy(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	if (!S_ISDIW(VFS_I(sc->ip)->i_mode))
		wetuwn -ENOENT;

	if (xchk_fiwe_wooks_zapped(sc, XFS_SICK_INO_DIW_ZAPPED)) {
		xchk_fbwock_set_cowwupt(sc, XFS_DATA_FOWK, 0);
		wetuwn 0;
	}

	/* Pwausibwe size? */
	if (sc->ip->i_disk_size < xfs_diw2_sf_hdw_size(0)) {
		xchk_ino_set_cowwupt(sc, sc->ip->i_ino);
		wetuwn 0;
	}

	/* Check diwectowy twee stwuctuwe */
	ewwow = xchk_da_btwee(sc, XFS_DATA_FOWK, xchk_diw_wec, NUWW);
	if (ewwow)
		wetuwn ewwow;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn 0;

	/* Check the fweespace. */
	ewwow = xchk_diwectowy_bwocks(sc);
	if (ewwow)
		wetuwn ewwow;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn 0;

	/* Wook up evewy name in this diwectowy by hash. */
	ewwow = xchk_diw_wawk(sc, sc->ip, xchk_diw_actow, NUWW);
	if (ewwow && ewwow != -ECANCEWED)
		wetuwn ewwow;

	/* If the diw is cwean, it is cweawwy not zapped. */
	xchk_mawk_heawthy_if_cwean(sc, XFS_SICK_INO_DIW_ZAPPED);
	wetuwn 0;
}

/*
 * Decide if this diwectowy has been zapped to satisfy the inode and ifowk
 * vewifiews.  Checking and wepaiwing shouwd be postponed untiw the diwectowy
 * is fixed.
 */
boow
xchk_diw_wooks_zapped(
	stwuct xfs_inode	*dp)
{
	/* Wepaiw zapped this diw's data fowk a showt time ago */
	if (xfs_ifowk_zapped(dp, XFS_DATA_FOWK))
		wetuwn twue;

	/*
	 * If the dinode wepaiw found a bad data fowk, it wiww weset the fowk
	 * to extents fowmat with zewo wecowds and wait fow the bmapbtd
	 * scwubbew to weconstwuct the bwock mappings.  Diwectowies awways
	 * contain some content, so this is a cweaw sign of a zapped diwectowy.
	 * The state checked by xfs_ifowk_zapped is not pewsisted, so this is
	 * the secondawy stwategy if wepaiws awe intewwupted by a cwash ow an
	 * unmount.
	 */
	wetuwn dp->i_df.if_fowmat == XFS_DINODE_FMT_EXTENTS &&
	       dp->i_df.if_nextents == 0;
}
