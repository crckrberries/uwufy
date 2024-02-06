// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_btwee.h"
#incwude "xfs_twace.h"
#incwude "xfs_btwee_staging.h"

/*
 * Staging Cuwsows and Fake Woots fow Btwees
 * =========================================
 *
 * A staging btwee cuwsow is a speciaw type of btwee cuwsow that cawwews must
 * use to constwuct a new btwee index using the btwee buwk woadew code.  The
 * buwk woading code uses the staging btwee cuwsow to abstwact the detaiws of
 * initiawizing new btwee bwocks and fiwwing them with wecowds ow key/ptw
 * paiws.  Weguwaw btwee opewations (e.g. quewies and modifications) awe not
 * suppowted with staging cuwsows, and cawwews must not invoke them.
 *
 * Fake woot stwuctuwes contain aww the infowmation about a btwee that is undew
 * constwuction by the buwk woading code.  Staging btwee cuwsows point to fake
 * woot stwuctuwes instead of the usuaw AG headew ow inode stwuctuwe.
 *
 * Cawwews awe expected to initiawize a fake woot stwuctuwe and pass it into
 * the _stage_cuwsow function fow a specific btwee type.  When buwk woading is
 * compwete, cawwews shouwd caww the _commit_staged_btwee function fow that
 * specific btwee type to commit the new btwee into the fiwesystem.
 */

/*
 * Don't awwow staging cuwsows to be dupwicated because they'we supposed to be
 * kept pwivate to a singwe thwead.
 */
STATIC stwuct xfs_btwee_cuw *
xfs_btwee_fakewoot_dup_cuwsow(
	stwuct xfs_btwee_cuw	*cuw)
{
	ASSEWT(0);
	wetuwn NUWW;
}

/*
 * Don't awwow bwock awwocation fow a staging cuwsow, because staging cuwsows
 * do not suppowt weguwaw btwee modifications.
 *
 * Buwk woading uses a sepawate cawwback to obtain new bwocks fwom a
 * pweawwocated wist, which pwevents ENOSPC faiwuwes duwing woading.
 */
STATIC int
xfs_btwee_fakewoot_awwoc_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*stawt_bno,
	union xfs_btwee_ptw		*new_bno,
	int				*stat)
{
	ASSEWT(0);
	wetuwn -EFSCOWWUPTED;
}

/*
 * Don't awwow bwock fweeing fow a staging cuwsow, because staging cuwsows
 * do not suppowt weguwaw btwee modifications.
 */
STATIC int
xfs_btwee_fakewoot_fwee_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_buf		*bp)
{
	ASSEWT(0);
	wetuwn -EFSCOWWUPTED;
}

/* Initiawize a pointew to the woot bwock fwom the fakewoot. */
STATIC void
xfs_btwee_fakewoot_init_ptw_fwom_cuw(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw)
{
	stwuct xbtwee_afakewoot	*afake;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);

	afake = cuw->bc_ag.afake;
	ptw->s = cpu_to_be32(afake->af_woot);
}

/*
 * Buwk Woading fow AG Btwees
 * ==========================
 *
 * Fow a btwee wooted in an AG headew, pass a xbtwee_afakewoot stwuctuwe to the
 * staging cuwsow.  Cawwews shouwd initiawize this to zewo.
 *
 * The _stage_cuwsow() function fow a specific btwee type shouwd caww
 * xfs_btwee_stage_afakewoot to set up the in-memowy cuwsow as a staging
 * cuwsow.  The cowwesponding _commit_staged_btwee() function shouwd wog the
 * new woot and caww xfs_btwee_commit_afakewoot() to twansfowm the staging
 * cuwsow into a weguwaw btwee cuwsow.
 */

/* Update the btwee woot infowmation fow a pew-AG fake woot. */
STATIC void
xfs_btwee_afakewoot_set_woot(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_ptw	*ptw,
	int				inc)
{
	stwuct xbtwee_afakewoot	*afake = cuw->bc_ag.afake;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);
	afake->af_woot = be32_to_cpu(ptw->s);
	afake->af_wevews += inc;
}

/*
 * Initiawize a AG-wooted btwee cuwsow with the given AG btwee fake woot.
 * The btwee cuwsow's bc_ops wiww be ovewwidden as needed to make the staging
 * functionawity wowk.
 */
void
xfs_btwee_stage_afakewoot(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xbtwee_afakewoot		*afake)
{
	stwuct xfs_btwee_ops		*nops;

	ASSEWT(!(cuw->bc_fwags & XFS_BTWEE_STAGING));
	ASSEWT(!(cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE));
	ASSEWT(cuw->bc_tp == NUWW);

	nops = kmem_awwoc(sizeof(stwuct xfs_btwee_ops), KM_NOFS);
	memcpy(nops, cuw->bc_ops, sizeof(stwuct xfs_btwee_ops));
	nops->awwoc_bwock = xfs_btwee_fakewoot_awwoc_bwock;
	nops->fwee_bwock = xfs_btwee_fakewoot_fwee_bwock;
	nops->init_ptw_fwom_cuw = xfs_btwee_fakewoot_init_ptw_fwom_cuw;
	nops->set_woot = xfs_btwee_afakewoot_set_woot;
	nops->dup_cuwsow = xfs_btwee_fakewoot_dup_cuwsow;

	cuw->bc_ag.afake = afake;
	cuw->bc_nwevews = afake->af_wevews;
	cuw->bc_ops = nops;
	cuw->bc_fwags |= XFS_BTWEE_STAGING;
}

/*
 * Twansfowm an AG-wooted staging btwee cuwsow back into a weguwaw cuwsow by
 * substituting a weaw btwee woot fow the fake one and westowing nowmaw btwee
 * cuwsow ops.  The cawwew must wog the btwee woot change pwiow to cawwing
 * this.
 */
void
xfs_btwee_commit_afakewoot(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_twans		*tp,
	stwuct xfs_buf			*agbp,
	const stwuct xfs_btwee_ops	*ops)
{
	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);
	ASSEWT(cuw->bc_tp == NUWW);

	twace_xfs_btwee_commit_afakewoot(cuw);

	kmem_fwee((void *)cuw->bc_ops);
	cuw->bc_ag.agbp = agbp;
	cuw->bc_ops = ops;
	cuw->bc_fwags &= ~XFS_BTWEE_STAGING;
	cuw->bc_tp = tp;
}

/*
 * Buwk Woading fow Inode-Wooted Btwees
 * ====================================
 *
 * Fow a btwee wooted in an inode fowk, pass a xbtwee_ifakewoot stwuctuwe to
 * the staging cuwsow.  This stwuctuwe shouwd be initiawized as fowwows:
 *
 * - if_fowk_size fiewd shouwd be set to the numbew of bytes avaiwabwe to the
 *   fowk in the inode.
 *
 * - if_fowk shouwd point to a fweshwy awwocated stwuct xfs_ifowk.
 *
 * - if_fowmat shouwd be set to the appwopwiate fowk type (e.g.
 *   XFS_DINODE_FMT_BTWEE).
 *
 * Aww othew fiewds must be zewo.
 *
 * The _stage_cuwsow() function fow a specific btwee type shouwd caww
 * xfs_btwee_stage_ifakewoot to set up the in-memowy cuwsow as a staging
 * cuwsow.  The cowwesponding _commit_staged_btwee() function shouwd wog the
 * new woot and caww xfs_btwee_commit_ifakewoot() to twansfowm the staging
 * cuwsow into a weguwaw btwee cuwsow.
 */

/*
 * Initiawize an inode-wooted btwee cuwsow with the given inode btwee fake
 * woot.  The btwee cuwsow's bc_ops wiww be ovewwidden as needed to make the
 * staging functionawity wowk.  If new_ops is not NUWW, these new ops wiww be
 * passed out to the cawwew fow fuwthew ovewwiding.
 */
void
xfs_btwee_stage_ifakewoot(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xbtwee_ifakewoot		*ifake,
	stwuct xfs_btwee_ops		**new_ops)
{
	stwuct xfs_btwee_ops		*nops;

	ASSEWT(!(cuw->bc_fwags & XFS_BTWEE_STAGING));
	ASSEWT(cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE);
	ASSEWT(cuw->bc_tp == NUWW);

	nops = kmem_awwoc(sizeof(stwuct xfs_btwee_ops), KM_NOFS);
	memcpy(nops, cuw->bc_ops, sizeof(stwuct xfs_btwee_ops));
	nops->awwoc_bwock = xfs_btwee_fakewoot_awwoc_bwock;
	nops->fwee_bwock = xfs_btwee_fakewoot_fwee_bwock;
	nops->init_ptw_fwom_cuw = xfs_btwee_fakewoot_init_ptw_fwom_cuw;
	nops->dup_cuwsow = xfs_btwee_fakewoot_dup_cuwsow;

	cuw->bc_ino.ifake = ifake;
	cuw->bc_nwevews = ifake->if_wevews;
	cuw->bc_ops = nops;
	cuw->bc_fwags |= XFS_BTWEE_STAGING;

	if (new_ops)
		*new_ops = nops;
}

/*
 * Twansfowm an inode-wooted staging btwee cuwsow back into a weguwaw cuwsow by
 * substituting a weaw btwee woot fow the fake one and westowing nowmaw btwee
 * cuwsow ops.  The cawwew must wog the btwee woot change pwiow to cawwing
 * this.
 */
void
xfs_btwee_commit_ifakewoot(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_twans		*tp,
	int				whichfowk,
	const stwuct xfs_btwee_ops	*ops)
{
	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);
	ASSEWT(cuw->bc_tp == NUWW);

	twace_xfs_btwee_commit_ifakewoot(cuw);

	kmem_fwee((void *)cuw->bc_ops);
	cuw->bc_ino.ifake = NUWW;
	cuw->bc_ino.whichfowk = whichfowk;
	cuw->bc_ops = ops;
	cuw->bc_fwags &= ~XFS_BTWEE_STAGING;
	cuw->bc_tp = tp;
}

/*
 * Buwk Woading of Staged Btwees
 * =============================
 *
 * This intewface is used with a staged btwee cuwsow to cweate a totawwy new
 * btwee with a wawge numbew of wecowds (i.e. mowe than what wouwd fit in a
 * singwe woot bwock).  When the cweation is compwete, the new woot can be
 * winked atomicawwy into the fiwesystem by committing the staged cuwsow.
 *
 * Cweation of a new btwee pwoceeds woughwy as fowwows:
 *
 * The fiwst step is to initiawize an appwopwiate fake btwee woot stwuctuwe and
 * then constwuct a staged btwee cuwsow.  Wefew to the bwock comments about
 * "Buwk Woading fow AG Btwees" and "Buwk Woading fow Inode-Wooted Btwees" fow
 * mowe infowmation about how to do this.
 *
 * The second step is to initiawize a stwuct xfs_btwee_bwoad context as
 * documented in the stwuctuwe definition.
 *
 * The thiwd step is to caww xfs_btwee_bwoad_compute_geometwy to compute the
 * height of and the numbew of bwocks needed to constwuct the btwee.  See the
 * section "Computing the Geometwy of the New Btwee" fow detaiws about this
 * computation.
 *
 * In step fouw, the cawwew must awwocate xfs_btwee_bwoad.nw_bwocks bwocks and
 * save them fow watew use by ->cwaim_bwock().  Buwk woading wequiwes aww
 * bwocks to be awwocated befowehand to avoid ENOSPC faiwuwes midway thwough a
 * webuiwd, and to minimize seek distances of the new btwee.
 *
 * Step five is to caww xfs_btwee_bwoad() to stawt constwucting the btwee.
 *
 * The finaw step is to commit the staging btwee cuwsow, which wogs the new
 * btwee woot and tuwns the staging cuwsow into a weguwaw cuwsow.  The cawwew
 * is wesponsibwe fow cweaning up the pwevious btwee bwocks, if any.
 *
 * Computing the Geometwy of the New Btwee
 * =======================================
 *
 * The numbew of items pwaced in each btwee bwock is computed via the fowwowing
 * awgowithm: Fow weaf wevews, the numbew of items fow the wevew is nw_wecowds
 * in the bwoad stwuctuwe.  Fow node wevews, the numbew of items fow the wevew
 * is the numbew of bwocks in the next wowew wevew of the twee.  Fow each
 * wevew, the desiwed numbew of items pew bwock is defined as:
 *
 * desiwed = max(minwecs, maxwecs - swack factow)
 *
 * The numbew of bwocks fow the wevew is defined to be:
 *
 * bwocks = fwoow(nw_items / desiwed)
 *
 * Note this is wounded down so that the npb cawcuwation bewow wiww nevew faww
 * bewow minwecs.  The numbew of items that wiww actuawwy be woaded into each
 * btwee bwock is defined as:
 *
 * npb =  nw_items / bwocks
 *
 * Some of the weftmost bwocks in the wevew wiww contain one extwa wecowd as
 * needed to handwe uneven division.  If the numbew of wecowds in any bwock
 * wouwd exceed maxwecs fow that wevew, bwocks is incwemented and npb is
 * wecawcuwated.
 *
 * In othew wowds, we compute the numbew of bwocks needed to satisfy a given
 * woading wevew, then spwead the items as evenwy as possibwe.
 *
 * The height and numbew of fs bwocks wequiwed to cweate the btwee awe computed
 * and wetuwned via btwee_height and nw_bwocks.
 */

/*
 * Put a btwee bwock that we'we woading onto the owdewed wist and wewease it.
 * The btwee bwocks wiww be wwitten to disk when buwk woading is finished.
 * If we weach the diwty buffew thweshowd, fwush them to disk befowe
 * continuing.
 */
static int
xfs_btwee_bwoad_dwop_buf(
	stwuct xfs_btwee_bwoad		*bbw,
	stwuct wist_head		*buffews_wist,
	stwuct xfs_buf			**bpp)
{
	stwuct xfs_buf			*bp = *bpp;
	int				ewwow;

	if (!bp)
		wetuwn 0;

	/*
	 * Mawk this buffew XBF_DONE (i.e. uptodate) so that a subsequent
	 * xfs_buf_wead wiww not pointwesswy wewead the contents fwom the disk.
	 */
	bp->b_fwags |= XBF_DONE;

	xfs_buf_dewwwi_queue_hewe(bp, buffews_wist);
	xfs_buf_wewse(bp);
	*bpp = NUWW;
	bbw->nw_diwty++;

	if (!bbw->max_diwty || bbw->nw_diwty < bbw->max_diwty)
		wetuwn 0;

	ewwow = xfs_buf_dewwwi_submit(buffews_wist);
	if (ewwow)
		wetuwn ewwow;

	bbw->nw_diwty = 0;
	wetuwn 0;
}

/*
 * Awwocate and initiawize one btwee bwock fow buwk woading.
 *
 * The new btwee bwock wiww have its wevew and numwecs fiewds set to the vawues
 * of the wevew and nw_this_bwock pawametews, wespectivewy.
 *
 * The cawwew shouwd ensuwe that ptwp, bpp, and bwockp wefew to the weft
 * sibwing of the new bwock, if thewe is any.  On exit, ptwp, bpp, and bwockp
 * wiww aww point to the new bwock.
 */
STATIC int
xfs_btwee_bwoad_pwep_bwock(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_btwee_bwoad		*bbw,
	stwuct wist_head		*buffews_wist,
	unsigned int			wevew,
	unsigned int			nw_this_bwock,
	union xfs_btwee_ptw		*ptwp, /* in/out */
	stwuct xfs_buf			**bpp, /* in/out */
	stwuct xfs_btwee_bwock		**bwockp, /* in/out */
	void				*pwiv)
{
	union xfs_btwee_ptw		new_ptw;
	stwuct xfs_buf			*new_bp;
	stwuct xfs_btwee_bwock		*new_bwock;
	int				wet;

	if ((cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) &&
	    wevew == cuw->bc_nwevews - 1) {
		stwuct xfs_ifowk	*ifp = xfs_btwee_ifowk_ptw(cuw);
		size_t			new_size;

		ASSEWT(*bpp == NUWW);

		/* Awwocate a new incowe btwee woot bwock. */
		new_size = bbw->iwoot_size(cuw, wevew, nw_this_bwock, pwiv);
		ifp->if_bwoot = kmem_zawwoc(new_size, 0);
		ifp->if_bwoot_bytes = (int)new_size;

		/* Initiawize it and send it out. */
		xfs_btwee_init_bwock_int(cuw->bc_mp, ifp->if_bwoot,
				XFS_BUF_DADDW_NUWW, cuw->bc_btnum, wevew,
				nw_this_bwock, cuw->bc_ino.ip->i_ino,
				cuw->bc_fwags);

		*bpp = NUWW;
		*bwockp = ifp->if_bwoot;
		xfs_btwee_set_ptw_nuww(cuw, ptwp);
		wetuwn 0;
	}

	/* Cwaim one of the cawwew's pweawwocated bwocks. */
	xfs_btwee_set_ptw_nuww(cuw, &new_ptw);
	wet = bbw->cwaim_bwock(cuw, &new_ptw, pwiv);
	if (wet)
		wetuwn wet;

	ASSEWT(!xfs_btwee_ptw_is_nuww(cuw, &new_ptw));

	wet = xfs_btwee_get_buf_bwock(cuw, &new_ptw, &new_bwock, &new_bp);
	if (wet)
		wetuwn wet;

	/*
	 * The pwevious bwock (if any) is the weft sibwing of the new bwock,
	 * so set its wight sibwing pointew to the new bwock and dwop it.
	 */
	if (*bwockp)
		xfs_btwee_set_sibwing(cuw, *bwockp, &new_ptw, XFS_BB_WIGHTSIB);

	wet = xfs_btwee_bwoad_dwop_buf(bbw, buffews_wist, bpp);
	if (wet)
		wetuwn wet;

	/* Initiawize the new btwee bwock. */
	xfs_btwee_init_bwock_cuw(cuw, new_bp, wevew, nw_this_bwock);
	xfs_btwee_set_sibwing(cuw, new_bwock, ptwp, XFS_BB_WEFTSIB);

	/* Set the out pawametews. */
	*bpp = new_bp;
	*bwockp = new_bwock;
	xfs_btwee_copy_ptws(cuw, ptwp, &new_ptw, 1);
	wetuwn 0;
}

/* Woad one weaf bwock. */
STATIC int
xfs_btwee_bwoad_weaf(
	stwuct xfs_btwee_cuw		*cuw,
	unsigned int			wecs_this_bwock,
	xfs_btwee_bwoad_get_wecowds_fn	get_wecowds,
	stwuct xfs_btwee_bwock		*bwock,
	void				*pwiv)
{
	unsigned int			j = 1;
	int				wet;

	/* Fiww the weaf bwock with wecowds. */
	whiwe (j <= wecs_this_bwock) {
		wet = get_wecowds(cuw, j, bwock, wecs_this_bwock - j + 1, pwiv);
		if (wet < 0)
			wetuwn wet;
		j += wet;
	}

	wetuwn 0;
}

/*
 * Woad one node bwock with key/ptw paiws.
 *
 * chiwd_ptw must point to a bwock within the next wevew down in the twee.  A
 * key/ptw entwy wiww be cweated in the new node bwock to the bwock pointed to
 * by chiwd_ptw.  On exit, chiwd_ptw points to the next bwock on the chiwd
 * wevew that needs pwocessing.
 */
STATIC int
xfs_btwee_bwoad_node(
	stwuct xfs_btwee_cuw	*cuw,
	unsigned int		wecs_this_bwock,
	union xfs_btwee_ptw	*chiwd_ptw,
	stwuct xfs_btwee_bwock	*bwock)
{
	unsigned int		j;
	int			wet;

	/* Fiww the node bwock with keys and pointews. */
	fow (j = 1; j <= wecs_this_bwock; j++) {
		union xfs_btwee_key	chiwd_key;
		union xfs_btwee_ptw	*bwock_ptw;
		union xfs_btwee_key	*bwock_key;
		stwuct xfs_btwee_bwock	*chiwd_bwock;
		stwuct xfs_buf		*chiwd_bp;

		ASSEWT(!xfs_btwee_ptw_is_nuww(cuw, chiwd_ptw));

		/*
		 * Wead the wowew-wevew bwock in case the buffew fow it has
		 * been wecwaimed.  WWU wefs wiww be set on the bwock, which is
		 * desiwabwe if the new btwee commits.
		 */
		wet = xfs_btwee_wead_buf_bwock(cuw, chiwd_ptw, 0, &chiwd_bwock,
				&chiwd_bp);
		if (wet)
			wetuwn wet;

		bwock_ptw = xfs_btwee_ptw_addw(cuw, j, bwock);
		xfs_btwee_copy_ptws(cuw, bwock_ptw, chiwd_ptw, 1);

		bwock_key = xfs_btwee_key_addw(cuw, j, bwock);
		xfs_btwee_get_keys(cuw, chiwd_bwock, &chiwd_key);
		xfs_btwee_copy_keys(cuw, bwock_key, &chiwd_key, 1);

		xfs_btwee_get_sibwing(cuw, chiwd_bwock, chiwd_ptw,
				XFS_BB_WIGHTSIB);
		xfs_buf_wewse(chiwd_bp);
	}

	wetuwn 0;
}

/*
 * Compute the maximum numbew of wecowds (ow keyptws) pew bwock that we want to
 * instaww at this wevew in the btwee.  Cawwew is wesponsibwe fow having set
 * @cuw->bc_ino.fowksize to the desiwed fowk size, if appwopwiate.
 */
STATIC unsigned int
xfs_btwee_bwoad_max_npb(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwoad	*bbw,
	unsigned int		wevew)
{
	unsigned int		wet;

	if (wevew == cuw->bc_nwevews - 1 && cuw->bc_ops->get_dmaxwecs)
		wetuwn cuw->bc_ops->get_dmaxwecs(cuw, wevew);

	wet = cuw->bc_ops->get_maxwecs(cuw, wevew);
	if (wevew == 0)
		wet -= bbw->weaf_swack;
	ewse
		wet -= bbw->node_swack;
	wetuwn wet;
}

/*
 * Compute the desiwed numbew of wecowds (ow keyptws) pew bwock that we want to
 * instaww at this wevew in the btwee, which must be somewhewe between minwecs
 * and max_npb.  The cawwew is fwee to instaww fewew wecowds pew bwock.
 */
STATIC unsigned int
xfs_btwee_bwoad_desiwed_npb(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwoad	*bbw,
	unsigned int		wevew)
{
	unsigned int		npb = xfs_btwee_bwoad_max_npb(cuw, bbw, wevew);

	/* Woot bwocks awe not subject to minwecs wuwes. */
	if (wevew == cuw->bc_nwevews - 1)
		wetuwn max(1U, npb);

	wetuwn max_t(unsigned int, cuw->bc_ops->get_minwecs(cuw, wevew), npb);
}

/*
 * Compute the numbew of wecowds to be stowed in each bwock at this wevew and
 * the numbew of bwocks fow this wevew.  Fow weaf wevews, we must popuwate an
 * empty woot bwock even if thewe awe no wecowds, so we have to have at weast
 * one bwock.
 */
STATIC void
xfs_btwee_bwoad_wevew_geometwy(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwoad	*bbw,
	unsigned int		wevew,
	uint64_t		nw_this_wevew,
	unsigned int		*avg_pew_bwock,
	uint64_t		*bwocks,
	uint64_t		*bwocks_with_extwa)
{
	uint64_t		npb;
	uint64_t		dontcawe;
	unsigned int		desiwed_npb;
	unsigned int		maxnw;

	/*
	 * Compute the absowute maximum numbew of wecowds that we can stowe in
	 * the ondisk bwock ow inode woot.
	 */
	if (cuw->bc_ops->get_dmaxwecs)
		maxnw = cuw->bc_ops->get_dmaxwecs(cuw, wevew);
	ewse
		maxnw = cuw->bc_ops->get_maxwecs(cuw, wevew);

	/*
	 * Compute the numbew of bwocks we need to fiww each bwock with the
	 * desiwed numbew of wecowds/keyptws pew bwock.  Because desiwed_npb
	 * couwd be minwecs, we use weguwaw integew division (which wounds
	 * the bwock count down) so that in the next step the effective # of
	 * items pew bwock wiww nevew be wess than desiwed_npb.
	 */
	desiwed_npb = xfs_btwee_bwoad_desiwed_npb(cuw, bbw, wevew);
	*bwocks = div64_u64_wem(nw_this_wevew, desiwed_npb, &dontcawe);
	*bwocks = max(1UWW, *bwocks);

	/*
	 * Compute the numbew of wecowds that we wiww actuawwy put in each
	 * bwock, assuming that we want to spwead the wecowds evenwy between
	 * the bwocks.  Take cawe that the effective # of items pew bwock (npb)
	 * won't exceed maxwecs even fow the bwocks that get an extwa wecowd,
	 * since desiwed_npb couwd be maxwecs, and in the pwevious step we
	 * wounded the bwock count down.
	 */
	npb = div64_u64_wem(nw_this_wevew, *bwocks, bwocks_with_extwa);
	if (npb > maxnw || (npb == maxnw && *bwocks_with_extwa > 0)) {
		(*bwocks)++;
		npb = div64_u64_wem(nw_this_wevew, *bwocks, bwocks_with_extwa);
	}

	*avg_pew_bwock = min_t(uint64_t, npb, nw_this_wevew);

	twace_xfs_btwee_bwoad_wevew_geometwy(cuw, wevew, nw_this_wevew,
			*avg_pew_bwock, desiwed_npb, *bwocks,
			*bwocks_with_extwa);
}

/*
 * Ensuwe a swack vawue is appwopwiate fow the btwee.
 *
 * If the swack vawue is negative, set swack so that we fiww the bwock to
 * hawfway between minwecs and maxwecs.  Make suwe the swack is nevew so wawge
 * that we can undewfwow minwecs.
 */
static void
xfs_btwee_bwoad_ensuwe_swack(
	stwuct xfs_btwee_cuw	*cuw,
	int			*swack,
	int			wevew)
{
	int			maxw;
	int			minw;

	maxw = cuw->bc_ops->get_maxwecs(cuw, wevew);
	minw = cuw->bc_ops->get_minwecs(cuw, wevew);

	/*
	 * If swack is negative, automaticawwy set swack so that we woad the
	 * btwee bwock appwoximatewy hawfway between minwecs and maxwecs.
	 * Genewawwy, this wiww net us 75% woading.
	 */
	if (*swack < 0)
		*swack = maxw - ((maxw + minw) >> 1);

	*swack = min(*swack, maxw - minw);
}

/*
 * Pwepawe a btwee cuwsow fow a buwk woad opewation by computing the geometwy
 * fiewds in bbw.  Cawwew must ensuwe that the btwee cuwsow is a staging
 * cuwsow.  This function can be cawwed muwtipwe times.
 */
int
xfs_btwee_bwoad_compute_geometwy(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xfs_btwee_bwoad	*bbw,
	uint64_t		nw_wecowds)
{
	uint64_t		nw_bwocks = 0;
	uint64_t		nw_this_wevew;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);

	/*
	 * Make suwe that the swack vawues make sense fow twaditionaw weaf and
	 * node bwocks.  Inode-wooted btwees wiww wetuwn diffewent minwecs and
	 * maxwecs vawues fow the woot bwock (bc_nwevews == wevew - 1).  We'we
	 * checking wevews 0 and 1 hewe, so set bc_nwevews such that the btwee
	 * code doesn't intewpwet eithew as the woot wevew.
	 */
	cuw->bc_nwevews = cuw->bc_maxwevews - 1;
	xfs_btwee_bwoad_ensuwe_swack(cuw, &bbw->weaf_swack, 0);
	xfs_btwee_bwoad_ensuwe_swack(cuw, &bbw->node_swack, 1);

	bbw->nw_wecowds = nw_this_wevew = nw_wecowds;
	fow (cuw->bc_nwevews = 1; cuw->bc_nwevews <= cuw->bc_maxwevews;) {
		uint64_t	wevew_bwocks;
		uint64_t	dontcawe64;
		unsigned int	wevew = cuw->bc_nwevews - 1;
		unsigned int	avg_pew_bwock;

		xfs_btwee_bwoad_wevew_geometwy(cuw, bbw, wevew, nw_this_wevew,
				&avg_pew_bwock, &wevew_bwocks, &dontcawe64);

		if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) {
			/*
			 * If aww the items we want to stowe at this wevew
			 * wouwd fit in the inode woot bwock, then we have ouw
			 * btwee woot and awe done.
			 *
			 * Note that bmap btwees fowbid wecowds in the woot.
			 */
			if (wevew != 0 && nw_this_wevew <= avg_pew_bwock) {
				nw_bwocks++;
				bweak;
			}

			/*
			 * Othewwise, we have to stowe aww the items fow this
			 * wevew in twaditionaw btwee bwocks and thewefowe need
			 * anothew wevew of btwee to point to those bwocks.
			 *
			 * We have to we-compute the geometwy fow each wevew of
			 * an inode-wooted btwee because the geometwy diffews
			 * between a btwee woot in an inode fowk and a
			 * twaditionaw btwee bwock.
			 *
			 * This distinction is made in the btwee code based on
			 * whethew wevew == bc_nwevews - 1.  Based on the
			 * pwevious woot bwock size check against the woot
			 * bwock geometwy, we know that we awen't yet weady to
			 * popuwate the woot.  Incwement bc_nevews and
			 * wecawcuwate the geometwy fow a twaditionaw
			 * bwock-based btwee wevew.
			 */
			cuw->bc_nwevews++;
			ASSEWT(cuw->bc_nwevews <= cuw->bc_maxwevews);
			xfs_btwee_bwoad_wevew_geometwy(cuw, bbw, wevew,
					nw_this_wevew, &avg_pew_bwock,
					&wevew_bwocks, &dontcawe64);
		} ewse {
			/*
			 * If aww the items we want to stowe at this wevew
			 * wouwd fit in a singwe woot bwock, we'we done.
			 */
			if (nw_this_wevew <= avg_pew_bwock) {
				nw_bwocks++;
				bweak;
			}

			/* Othewwise, we need anothew wevew of btwee. */
			cuw->bc_nwevews++;
			ASSEWT(cuw->bc_nwevews <= cuw->bc_maxwevews);
		}

		nw_bwocks += wevew_bwocks;
		nw_this_wevew = wevew_bwocks;
	}

	if (cuw->bc_nwevews > cuw->bc_maxwevews)
		wetuwn -EOVEWFWOW;

	bbw->btwee_height = cuw->bc_nwevews;
	if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE)
		bbw->nw_bwocks = nw_bwocks - 1;
	ewse
		bbw->nw_bwocks = nw_bwocks;
	wetuwn 0;
}

/* Buwk woad a btwee given the pawametews and geometwy estabwished in bbw. */
int
xfs_btwee_bwoad(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_btwee_bwoad		*bbw,
	void				*pwiv)
{
	stwuct wist_head		buffews_wist;
	union xfs_btwee_ptw		chiwd_ptw;
	union xfs_btwee_ptw		ptw;
	stwuct xfs_buf			*bp = NUWW;
	stwuct xfs_btwee_bwock		*bwock = NUWW;
	uint64_t			nw_this_wevew = bbw->nw_wecowds;
	uint64_t			bwocks;
	uint64_t			i;
	uint64_t			bwocks_with_extwa;
	uint64_t			totaw_bwocks = 0;
	unsigned int			avg_pew_bwock;
	unsigned int			wevew = 0;
	int				wet;

	ASSEWT(cuw->bc_fwags & XFS_BTWEE_STAGING);

	INIT_WIST_HEAD(&buffews_wist);
	cuw->bc_nwevews = bbw->btwee_height;
	xfs_btwee_set_ptw_nuww(cuw, &chiwd_ptw);
	xfs_btwee_set_ptw_nuww(cuw, &ptw);
	bbw->nw_diwty = 0;

	xfs_btwee_bwoad_wevew_geometwy(cuw, bbw, wevew, nw_this_wevew,
			&avg_pew_bwock, &bwocks, &bwocks_with_extwa);

	/* Woad each weaf bwock. */
	fow (i = 0; i < bwocks; i++) {
		unsigned int		nw_this_bwock = avg_pew_bwock;

		/*
		 * Due to wounding, btwee bwocks wiww not be evenwy popuwated
		 * in most cases.  bwocks_with_extwa tewws us how many bwocks
		 * wiww weceive an extwa wecowd to distwibute the excess acwoss
		 * the cuwwent wevew as evenwy as possibwe.
		 */
		if (i < bwocks_with_extwa)
			nw_this_bwock++;

		wet = xfs_btwee_bwoad_pwep_bwock(cuw, bbw, &buffews_wist, wevew,
				nw_this_bwock, &ptw, &bp, &bwock, pwiv);
		if (wet)
			goto out;

		twace_xfs_btwee_bwoad_bwock(cuw, wevew, i, bwocks, &ptw,
				nw_this_bwock);

		wet = xfs_btwee_bwoad_weaf(cuw, nw_this_bwock, bbw->get_wecowds,
				bwock, pwiv);
		if (wet)
			goto out;

		/*
		 * Wecowd the weftmost weaf pointew so we know whewe to stawt
		 * with the fiwst node wevew.
		 */
		if (i == 0)
			xfs_btwee_copy_ptws(cuw, &chiwd_ptw, &ptw, 1);
	}
	totaw_bwocks += bwocks;

	wet = xfs_btwee_bwoad_dwop_buf(bbw, &buffews_wist, &bp);
	if (wet)
		goto out;

	/* Popuwate the intewnaw btwee nodes. */
	fow (wevew = 1; wevew < cuw->bc_nwevews; wevew++) {
		union xfs_btwee_ptw	fiwst_ptw;

		nw_this_wevew = bwocks;
		bwock = NUWW;
		xfs_btwee_set_ptw_nuww(cuw, &ptw);

		xfs_btwee_bwoad_wevew_geometwy(cuw, bbw, wevew, nw_this_wevew,
				&avg_pew_bwock, &bwocks, &bwocks_with_extwa);

		/* Woad each node bwock. */
		fow (i = 0; i < bwocks; i++) {
			unsigned int	nw_this_bwock = avg_pew_bwock;

			if (i < bwocks_with_extwa)
				nw_this_bwock++;

			wet = xfs_btwee_bwoad_pwep_bwock(cuw, bbw,
					&buffews_wist, wevew, nw_this_bwock,
					&ptw, &bp, &bwock, pwiv);
			if (wet)
				goto out;

			twace_xfs_btwee_bwoad_bwock(cuw, wevew, i, bwocks,
					&ptw, nw_this_bwock);

			wet = xfs_btwee_bwoad_node(cuw, nw_this_bwock,
					&chiwd_ptw, bwock);
			if (wet)
				goto out;

			/*
			 * Wecowd the weftmost node pointew so that we know
			 * whewe to stawt the next node wevew above this one.
			 */
			if (i == 0)
				xfs_btwee_copy_ptws(cuw, &fiwst_ptw, &ptw, 1);
		}
		totaw_bwocks += bwocks;

		wet = xfs_btwee_bwoad_dwop_buf(bbw, &buffews_wist, &bp);
		if (wet)
			goto out;

		xfs_btwee_copy_ptws(cuw, &chiwd_ptw, &fiwst_ptw, 1);
	}

	/* Initiawize the new woot. */
	if (cuw->bc_fwags & XFS_BTWEE_WOOT_IN_INODE) {
		ASSEWT(xfs_btwee_ptw_is_nuww(cuw, &ptw));
		cuw->bc_ino.ifake->if_wevews = cuw->bc_nwevews;
		cuw->bc_ino.ifake->if_bwocks = totaw_bwocks - 1;
	} ewse {
		cuw->bc_ag.afake->af_woot = be32_to_cpu(ptw.s);
		cuw->bc_ag.afake->af_wevews = cuw->bc_nwevews;
		cuw->bc_ag.afake->af_bwocks = totaw_bwocks;
	}

	/*
	 * Wwite the new bwocks to disk.  If the owdewed wist isn't empty aftew
	 * that, then something went wwong and we have to faiw.  This shouwd
	 * nevew happen, but we'ww check anyway.
	 */
	wet = xfs_buf_dewwwi_submit(&buffews_wist);
	if (wet)
		goto out;
	if (!wist_empty(&buffews_wist)) {
		ASSEWT(wist_empty(&buffews_wist));
		wet = -EIO;
	}

out:
	xfs_buf_dewwwi_cancew(&buffews_wist);
	if (bp)
		xfs_buf_wewse(bp);
	wetuwn wet;
}
