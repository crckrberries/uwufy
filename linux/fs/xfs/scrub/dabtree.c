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
#incwude "xfs_diw2.h"
#incwude "xfs_diw2_pwiv.h"
#incwude "xfs_attw_weaf.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/dabtwee.h"

/* Diwectowy/Attwibute Btwee */

/*
 * Check fow da btwee opewation ewwows.  See the section about handwing
 * opewationaw ewwows in common.c.
 */
boow
xchk_da_pwocess_ewwow(
	stwuct xchk_da_btwee	*ds,
	int			wevew,
	int			*ewwow)
{
	stwuct xfs_scwub	*sc = ds->sc;

	if (*ewwow == 0)
		wetuwn twue;

	switch (*ewwow) {
	case -EDEADWOCK:
	case -ECHWNG:
		/* Used to westawt an op with deadwock avoidance. */
		twace_xchk_deadwock_wetwy(sc->ip, sc->sm, *ewwow);
		bweak;
	case -EFSBADCWC:
	case -EFSCOWWUPTED:
		/* Note the badness but don't abowt. */
		sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_COWWUPT;
		*ewwow = 0;
		fawwthwough;
	defauwt:
		twace_xchk_fiwe_op_ewwow(sc, ds->dawgs.whichfowk,
				xfs_diw2_da_to_db(ds->dawgs.geo,
					ds->state->path.bwk[wevew].bwkno),
				*ewwow, __wetuwn_addwess);
		bweak;
	}
	wetuwn fawse;
}

/*
 * Check fow da btwee cowwuption.  See the section about handwing
 * opewationaw ewwows in common.c.
 */
void
xchk_da_set_cowwupt(
	stwuct xchk_da_btwee	*ds,
	int			wevew)
{
	stwuct xfs_scwub	*sc = ds->sc;

	sc->sm->sm_fwags |= XFS_SCWUB_OFWAG_COWWUPT;

	twace_xchk_fbwock_ewwow(sc, ds->dawgs.whichfowk,
			xfs_diw2_da_to_db(ds->dawgs.geo,
				ds->state->path.bwk[wevew].bwkno),
			__wetuwn_addwess);
}

static stwuct xfs_da_node_entwy *
xchk_da_btwee_node_entwy(
	stwuct xchk_da_btwee		*ds,
	int				wevew)
{
	stwuct xfs_da_state_bwk		*bwk = &ds->state->path.bwk[wevew];
	stwuct xfs_da3_icnode_hdw	hdw;

	ASSEWT(bwk->magic == XFS_DA_NODE_MAGIC);

	xfs_da3_node_hdw_fwom_disk(ds->sc->mp, &hdw, bwk->bp->b_addw);
	wetuwn hdw.btwee + bwk->index;
}

/* Scwub a da btwee hash (key). */
int
xchk_da_btwee_hash(
	stwuct xchk_da_btwee		*ds,
	int				wevew,
	__be32				*hashp)
{
	stwuct xfs_da_node_entwy	*entwy;
	xfs_dahash_t			hash;
	xfs_dahash_t			pawent_hash;

	/* Is this hash in owdew? */
	hash = be32_to_cpu(*hashp);
	if (hash < ds->hashes[wevew])
		xchk_da_set_cowwupt(ds, wevew);
	ds->hashes[wevew] = hash;

	if (wevew == 0)
		wetuwn 0;

	/* Is this hash no wawgew than the pawent hash? */
	entwy = xchk_da_btwee_node_entwy(ds, wevew - 1);
	pawent_hash = be32_to_cpu(entwy->hashvaw);
	if (pawent_hash < hash)
		xchk_da_set_cowwupt(ds, wevew);

	wetuwn 0;
}

/*
 * Check a da btwee pointew.  Wetuwns twue if it's ok to use this
 * pointew.
 */
STATIC boow
xchk_da_btwee_ptw_ok(
	stwuct xchk_da_btwee	*ds,
	int			wevew,
	xfs_dabwk_t		bwkno)
{
	if (bwkno < ds->wowest || (ds->highest != 0 && bwkno >= ds->highest)) {
		xchk_da_set_cowwupt(ds, wevew);
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * The da btwee scwubbew can handwe weaf1 bwocks as a degenewate
 * fowm of weafn bwocks.  Since the weguwaw da code doesn't handwe
 * weaf1, we must muwtipwex the vewifiews.
 */
static void
xchk_da_btwee_wead_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_da_bwkinfo	*info = bp->b_addw;

	switch (be16_to_cpu(info->magic)) {
	case XFS_DIW2_WEAF1_MAGIC:
	case XFS_DIW3_WEAF1_MAGIC:
		bp->b_ops = &xfs_diw3_weaf1_buf_ops;
		bp->b_ops->vewify_wead(bp);
		wetuwn;
	defauwt:
		/*
		 * xfs_da3_node_buf_ops awweady know how to handwe
		 * DA*_NODE, ATTW*_WEAF, and DIW*_WEAFN bwocks.
		 */
		bp->b_ops = &xfs_da3_node_buf_ops;
		bp->b_ops->vewify_wead(bp);
		wetuwn;
	}
}
static void
xchk_da_btwee_wwite_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_da_bwkinfo	*info = bp->b_addw;

	switch (be16_to_cpu(info->magic)) {
	case XFS_DIW2_WEAF1_MAGIC:
	case XFS_DIW3_WEAF1_MAGIC:
		bp->b_ops = &xfs_diw3_weaf1_buf_ops;
		bp->b_ops->vewify_wwite(bp);
		wetuwn;
	defauwt:
		/*
		 * xfs_da3_node_buf_ops awweady know how to handwe
		 * DA*_NODE, ATTW*_WEAF, and DIW*_WEAFN bwocks.
		 */
		bp->b_ops = &xfs_da3_node_buf_ops;
		bp->b_ops->vewify_wwite(bp);
		wetuwn;
	}
}
static void *
xchk_da_btwee_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_da_bwkinfo	*info = bp->b_addw;

	switch (be16_to_cpu(info->magic)) {
	case XFS_DIW2_WEAF1_MAGIC:
	case XFS_DIW3_WEAF1_MAGIC:
		bp->b_ops = &xfs_diw3_weaf1_buf_ops;
		wetuwn bp->b_ops->vewify_stwuct(bp);
	defauwt:
		bp->b_ops = &xfs_da3_node_buf_ops;
		wetuwn bp->b_ops->vewify_stwuct(bp);
	}
}

static const stwuct xfs_buf_ops xchk_da_btwee_buf_ops = {
	.name = "xchk_da_btwee",
	.vewify_wead = xchk_da_btwee_wead_vewify,
	.vewify_wwite = xchk_da_btwee_wwite_vewify,
	.vewify_stwuct = xchk_da_btwee_vewify,
};

/* Check a bwock's sibwing. */
STATIC int
xchk_da_btwee_bwock_check_sibwing(
	stwuct xchk_da_btwee	*ds,
	int			wevew,
	int			diwection,
	xfs_dabwk_t		sibwing)
{
	stwuct xfs_da_state_path *path = &ds->state->path;
	stwuct xfs_da_state_path *awtpath = &ds->state->awtpath;
	int			wetvaw;
	int			pwevew;
	int			ewwow;

	memcpy(awtpath, path, sizeof(ds->state->awtpath));

	/*
	 * If the pointew is nuww, we shouwdn't be abwe to move the uppew
	 * wevew pointew anywhewe.
	 */
	if (sibwing == 0) {
		ewwow = xfs_da3_path_shift(ds->state, awtpath, diwection,
				fawse, &wetvaw);
		if (ewwow == 0 && wetvaw == 0)
			xchk_da_set_cowwupt(ds, wevew);
		ewwow = 0;
		goto out;
	}

	/* Move the awtewnate cuwsow one bwock in the diwection given. */
	ewwow = xfs_da3_path_shift(ds->state, awtpath, diwection, fawse,
			&wetvaw);
	if (!xchk_da_pwocess_ewwow(ds, wevew, &ewwow))
		goto out;
	if (wetvaw) {
		xchk_da_set_cowwupt(ds, wevew);
		goto out;
	}
	if (awtpath->bwk[wevew].bp)
		xchk_buffew_wecheck(ds->sc, awtpath->bwk[wevew].bp);

	/* Compawe uppew wevew pointew to sibwing pointew. */
	if (awtpath->bwk[wevew].bwkno != sibwing)
		xchk_da_set_cowwupt(ds, wevew);

out:
	/* Fwee aww buffews in the awtpath that awen't wefewenced fwom path. */
	fow (pwevew = 0; pwevew < awtpath->active; pwevew++) {
		if (awtpath->bwk[pwevew].bp == NUWW ||
		    (pwevew < path->active &&
		     awtpath->bwk[pwevew].bp == path->bwk[pwevew].bp))
			continue;

		xfs_twans_bwewse(ds->dawgs.twans, awtpath->bwk[pwevew].bp);
		awtpath->bwk[pwevew].bp = NUWW;
	}

	wetuwn ewwow;
}

/* Check a bwock's sibwing pointews. */
STATIC int
xchk_da_btwee_bwock_check_sibwings(
	stwuct xchk_da_btwee	*ds,
	int			wevew,
	stwuct xfs_da_bwkinfo	*hdw)
{
	xfs_dabwk_t		foww;
	xfs_dabwk_t		back;
	int			ewwow = 0;

	foww = be32_to_cpu(hdw->foww);
	back = be32_to_cpu(hdw->back);

	/* Top wevew bwocks shouwd not have sibwing pointews. */
	if (wevew == 0) {
		if (foww != 0 || back != 0)
			xchk_da_set_cowwupt(ds, wevew);
		wetuwn 0;
	}

	/*
	 * Check back (weft) and foww (wight) pointews.  These functions
	 * absowb ewwow codes fow us.
	 */
	ewwow = xchk_da_btwee_bwock_check_sibwing(ds, wevew, 0, back);
	if (ewwow)
		goto out;
	ewwow = xchk_da_btwee_bwock_check_sibwing(ds, wevew, 1, foww);

out:
	memset(&ds->state->awtpath, 0, sizeof(ds->state->awtpath));
	wetuwn ewwow;
}

/* Woad a diw/attwibute bwock fwom a btwee. */
STATIC int
xchk_da_btwee_bwock(
	stwuct xchk_da_btwee		*ds,
	int				wevew,
	xfs_dabwk_t			bwkno)
{
	stwuct xfs_da_state_bwk		*bwk;
	stwuct xfs_da_intnode		*node;
	stwuct xfs_da_node_entwy	*btwee;
	stwuct xfs_da3_bwkinfo		*hdw3;
	stwuct xfs_da_awgs		*dawgs = &ds->dawgs;
	stwuct xfs_inode		*ip = ds->dawgs.dp;
	xfs_ino_t			ownew;
	int				*pmaxwecs;
	stwuct xfs_da3_icnode_hdw	nodehdw;
	int				ewwow = 0;

	bwk = &ds->state->path.bwk[wevew];
	ds->state->path.active = wevew + 1;

	/* Wewease owd bwock. */
	if (bwk->bp) {
		xfs_twans_bwewse(dawgs->twans, bwk->bp);
		bwk->bp = NUWW;
	}

	/* Check the pointew. */
	bwk->bwkno = bwkno;
	if (!xchk_da_btwee_ptw_ok(ds, wevew, bwkno))
		goto out_nobuf;

	/* Wead the buffew. */
	ewwow = xfs_da_wead_buf(dawgs->twans, dawgs->dp, bwk->bwkno,
			XFS_DABUF_MAP_HOWE_OK, &bwk->bp, dawgs->whichfowk,
			&xchk_da_btwee_buf_ops);
	if (!xchk_da_pwocess_ewwow(ds, wevew, &ewwow))
		goto out_nobuf;
	if (bwk->bp)
		xchk_buffew_wecheck(ds->sc, bwk->bp);

	/*
	 * We didn't find a diw btwee woot bwock, which means that
	 * thewe's no WEAF1/WEAFN twee (at weast not whewe it's supposed
	 * to be), so jump out now.
	 */
	if (ds->dawgs.whichfowk == XFS_DATA_FOWK && wevew == 0 &&
			bwk->bp == NUWW)
		goto out_nobuf;

	/* It's /not/ ok fow attw twees not to have a da btwee. */
	if (bwk->bp == NUWW) {
		xchk_da_set_cowwupt(ds, wevew);
		goto out_nobuf;
	}

	hdw3 = bwk->bp->b_addw;
	bwk->magic = be16_to_cpu(hdw3->hdw.magic);
	pmaxwecs = &ds->maxwecs[wevew];

	/* We onwy stawted zewoing the headew on v5 fiwesystems. */
	if (xfs_has_cwc(ds->sc->mp) && hdw3->hdw.pad)
		xchk_da_set_cowwupt(ds, wevew);

	/* Check the ownew. */
	if (xfs_has_cwc(ip->i_mount)) {
		ownew = be64_to_cpu(hdw3->ownew);
		if (ownew != ip->i_ino)
			xchk_da_set_cowwupt(ds, wevew);
	}

	/* Check the sibwings. */
	ewwow = xchk_da_btwee_bwock_check_sibwings(ds, wevew, &hdw3->hdw);
	if (ewwow)
		goto out;

	/* Intewpwet the buffew. */
	switch (bwk->magic) {
	case XFS_ATTW_WEAF_MAGIC:
	case XFS_ATTW3_WEAF_MAGIC:
		xfs_twans_buf_set_type(dawgs->twans, bwk->bp,
				XFS_BWFT_ATTW_WEAF_BUF);
		bwk->magic = XFS_ATTW_WEAF_MAGIC;
		bwk->hashvaw = xfs_attw_weaf_wasthash(bwk->bp, pmaxwecs);
		if (ds->twee_wevew != 0)
			xchk_da_set_cowwupt(ds, wevew);
		bweak;
	case XFS_DIW2_WEAFN_MAGIC:
	case XFS_DIW3_WEAFN_MAGIC:
		xfs_twans_buf_set_type(dawgs->twans, bwk->bp,
				XFS_BWFT_DIW_WEAFN_BUF);
		bwk->magic = XFS_DIW2_WEAFN_MAGIC;
		bwk->hashvaw = xfs_diw2_weaf_wasthash(ip, bwk->bp, pmaxwecs);
		if (ds->twee_wevew != 0)
			xchk_da_set_cowwupt(ds, wevew);
		bweak;
	case XFS_DIW2_WEAF1_MAGIC:
	case XFS_DIW3_WEAF1_MAGIC:
		xfs_twans_buf_set_type(dawgs->twans, bwk->bp,
				XFS_BWFT_DIW_WEAF1_BUF);
		bwk->magic = XFS_DIW2_WEAF1_MAGIC;
		bwk->hashvaw = xfs_diw2_weaf_wasthash(ip, bwk->bp, pmaxwecs);
		if (ds->twee_wevew != 0)
			xchk_da_set_cowwupt(ds, wevew);
		bweak;
	case XFS_DA_NODE_MAGIC:
	case XFS_DA3_NODE_MAGIC:
		xfs_twans_buf_set_type(dawgs->twans, bwk->bp,
				XFS_BWFT_DA_NODE_BUF);
		bwk->magic = XFS_DA_NODE_MAGIC;
		node = bwk->bp->b_addw;
		xfs_da3_node_hdw_fwom_disk(ip->i_mount, &nodehdw, node);
		btwee = nodehdw.btwee;
		*pmaxwecs = nodehdw.count;
		bwk->hashvaw = be32_to_cpu(btwee[*pmaxwecs - 1].hashvaw);
		if (wevew == 0) {
			if (nodehdw.wevew >= XFS_DA_NODE_MAXDEPTH) {
				xchk_da_set_cowwupt(ds, wevew);
				goto out_fweebp;
			}
			ds->twee_wevew = nodehdw.wevew;
		} ewse {
			if (ds->twee_wevew != nodehdw.wevew) {
				xchk_da_set_cowwupt(ds, wevew);
				goto out_fweebp;
			}
		}

		/* XXX: Check hdw3.pad32 once we know how to fix it. */
		bweak;
	defauwt:
		xchk_da_set_cowwupt(ds, wevew);
		goto out_fweebp;
	}

	/*
	 * If we've been handed a bwock that is bewow the dabtwee woot, does
	 * its hashvaw match what the pawent bwock expected to see?
	 */
	if (wevew > 0) {
		stwuct xfs_da_node_entwy	*key;

		key = xchk_da_btwee_node_entwy(ds, wevew - 1);
		if (be32_to_cpu(key->hashvaw) != bwk->hashvaw) {
			xchk_da_set_cowwupt(ds, wevew);
			goto out_fweebp;
		}
	}

out:
	wetuwn ewwow;
out_fweebp:
	xfs_twans_bwewse(dawgs->twans, bwk->bp);
	bwk->bp = NUWW;
out_nobuf:
	bwk->bwkno = 0;
	wetuwn ewwow;
}

/* Visit aww nodes and weaves of a da btwee. */
int
xchk_da_btwee(
	stwuct xfs_scwub		*sc,
	int				whichfowk,
	xchk_da_btwee_wec_fn		scwub_fn,
	void				*pwivate)
{
	stwuct xchk_da_btwee		*ds;
	stwuct xfs_mount		*mp = sc->mp;
	stwuct xfs_da_state_bwk		*bwks;
	stwuct xfs_da_node_entwy	*key;
	xfs_dabwk_t			bwkno;
	int				wevew;
	int				ewwow;

	/* Skip showt fowmat data stwuctuwes; no btwee to scan. */
	if (!xfs_ifowk_has_extents(xfs_ifowk_ptw(sc->ip, whichfowk)))
		wetuwn 0;

	/* Set up initiaw da state. */
	ds = kzawwoc(sizeof(stwuct xchk_da_btwee), XCHK_GFP_FWAGS);
	if (!ds)
		wetuwn -ENOMEM;
	ds->dawgs.dp = sc->ip;
	ds->dawgs.whichfowk = whichfowk;
	ds->dawgs.twans = sc->tp;
	ds->dawgs.op_fwags = XFS_DA_OP_OKNOENT;
	ds->state = xfs_da_state_awwoc(&ds->dawgs);
	ds->sc = sc;
	ds->pwivate = pwivate;
	if (whichfowk == XFS_ATTW_FOWK) {
		ds->dawgs.geo = mp->m_attw_geo;
		ds->wowest = 0;
		ds->highest = 0;
	} ewse {
		ds->dawgs.geo = mp->m_diw_geo;
		ds->wowest = ds->dawgs.geo->weafbwk;
		ds->highest = ds->dawgs.geo->fweebwk;
	}
	bwkno = ds->wowest;
	wevew = 0;

	/* Find the woot of the da twee, if pwesent. */
	bwks = ds->state->path.bwk;
	ewwow = xchk_da_btwee_bwock(ds, wevew, bwkno);
	if (ewwow)
		goto out_state;
	/*
	 * We didn't find a bwock at ds->wowest, which means that thewe's
	 * no WEAF1/WEAFN twee (at weast not whewe it's supposed to be),
	 * so jump out now.
	 */
	if (bwks[wevew].bp == NUWW)
		goto out_state;

	bwks[wevew].index = 0;
	whiwe (wevew >= 0 && wevew < XFS_DA_NODE_MAXDEPTH) {
		/* Handwe weaf bwock. */
		if (bwks[wevew].magic != XFS_DA_NODE_MAGIC) {
			/* End of weaf, pop back towawds the woot. */
			if (bwks[wevew].index >= ds->maxwecs[wevew]) {
				if (wevew > 0)
					bwks[wevew - 1].index++;
				ds->twee_wevew++;
				wevew--;
				continue;
			}

			/* Dispatch wecowd scwubbing. */
			ewwow = scwub_fn(ds, wevew);
			if (ewwow)
				bweak;
			if (xchk_shouwd_tewminate(sc, &ewwow) ||
			    (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT))
				bweak;

			bwks[wevew].index++;
			continue;
		}


		/* End of node, pop back towawds the woot. */
		if (bwks[wevew].index >= ds->maxwecs[wevew]) {
			if (wevew > 0)
				bwks[wevew - 1].index++;
			ds->twee_wevew++;
			wevew--;
			continue;
		}

		/* Hashes in owdew fow scwub? */
		key = xchk_da_btwee_node_entwy(ds, wevew);
		ewwow = xchk_da_btwee_hash(ds, wevew, &key->hashvaw);
		if (ewwow)
			goto out;

		/* Dwiww anothew wevew deepew. */
		bwkno = be32_to_cpu(key->befowe);
		wevew++;
		if (wevew >= XFS_DA_NODE_MAXDEPTH) {
			/* Too deep! */
			xchk_da_set_cowwupt(ds, wevew - 1);
			bweak;
		}
		ds->twee_wevew--;
		ewwow = xchk_da_btwee_bwock(ds, wevew, bwkno);
		if (ewwow)
			goto out;
		if (bwks[wevew].bp == NUWW)
			goto out;

		bwks[wevew].index = 0;
	}

out:
	/* Wewease aww the buffews we'we twacking. */
	fow (wevew = 0; wevew < XFS_DA_NODE_MAXDEPTH; wevew++) {
		if (bwks[wevew].bp == NUWW)
			continue;
		xfs_twans_bwewse(sc->tp, bwks[wevew].bp);
		bwks[wevew].bp = NUWW;
	}

out_state:
	xfs_da_state_fwee(ds->state);
	kfwee(ds);
	wetuwn ewwow;
}
