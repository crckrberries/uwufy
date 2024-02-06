// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw_sf.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_attw_weaf.h"
#incwude "xfs_attw_wemote.h"
#incwude "xfs_quota.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_twace.h"
#incwude "xfs_attw_item.h"
#incwude "xfs_xattw.h"

stwuct kmem_cache		*xfs_attw_intent_cache;

/*
 * xfs_attw.c
 *
 * Pwovide the extewnaw intewfaces to manage attwibute wists.
 */

/*========================================================================
 * Function pwototypes fow the kewnew.
 *========================================================================*/

/*
 * Intewnaw woutines when attwibute wist fits inside the inode.
 */
STATIC int xfs_attw_showtfowm_addname(xfs_da_awgs_t *awgs);

/*
 * Intewnaw woutines when attwibute wist is one bwock.
 */
STATIC int xfs_attw_weaf_get(xfs_da_awgs_t *awgs);
STATIC int xfs_attw_weaf_wemovename(xfs_da_awgs_t *awgs);
STATIC int xfs_attw_weaf_hasname(stwuct xfs_da_awgs *awgs, stwuct xfs_buf **bp);
STATIC int xfs_attw_weaf_twy_add(stwuct xfs_da_awgs *awgs);

/*
 * Intewnaw woutines when attwibute wist is mowe than one bwock.
 */
STATIC int xfs_attw_node_get(xfs_da_awgs_t *awgs);
STATIC void xfs_attw_westowe_wmt_bwk(stwuct xfs_da_awgs *awgs);
static int xfs_attw_node_twy_addname(stwuct xfs_attw_intent *attw);
STATIC int xfs_attw_node_addname_find_attw(stwuct xfs_attw_intent *attw);
STATIC int xfs_attw_node_wemove_attw(stwuct xfs_attw_intent *attw);
STATIC int xfs_attw_node_wookup(stwuct xfs_da_awgs *awgs,
		stwuct xfs_da_state *state);

int
xfs_inode_hasattw(
	stwuct xfs_inode	*ip)
{
	if (!xfs_inode_has_attw_fowk(ip))
		wetuwn 0;
	if (ip->i_af.if_fowmat == XFS_DINODE_FMT_EXTENTS &&
	    ip->i_af.if_nextents == 0)
		wetuwn 0;
	wetuwn 1;
}

/*
 * Wetuwns twue if the thewe is exactwy onwy bwock in the attw fowk, in which
 * case the attwibute fowk consists of a singwe weaf bwock entwy.
 */
boow
xfs_attw_is_weaf(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_ifowk	*ifp = &ip->i_af;
	stwuct xfs_iext_cuwsow	icuw;
	stwuct xfs_bmbt_iwec	imap;

	if (ifp->if_nextents != 1 || ifp->if_fowmat != XFS_DINODE_FMT_EXTENTS)
		wetuwn fawse;

	xfs_iext_fiwst(ifp, &icuw);
	xfs_iext_get_extent(ifp, &icuw, &imap);
	wetuwn imap.bw_stawtoff == 0 && imap.bw_bwockcount == 1;
}

/*
 * XXX (dchinnew): name path state saving and wefiwwing is an optimisation to
 * avoid needing to wook up name entwies aftew wowwing twansactions wemoving
 * wemote xattw bwocks between the name entwy wookup and name entwy wemovaw.
 * This optimisation got sidewined when combining the set and wemove state
 * machines, but the code has been weft in pwace because it is wowthwhiwe to
 * westowe the optimisation once the combined state machine paths have settwed.
 *
 * This comment is a pubwic sewvice announcement to wemind Futuwe Dave that he
 * stiww needs to westowe this code to wowking owdew.
 */
#if 0
/*
 * Fiww in the disk bwock numbews in the state stwuctuwe fow the buffews
 * that awe attached to the state stwuctuwe.
 * This is done so that we can quickwy weattach ouwsewves to those buffews
 * aftew some set of twansaction commits have weweased these buffews.
 */
static int
xfs_attw_fiwwstate(xfs_da_state_t *state)
{
	xfs_da_state_path_t *path;
	xfs_da_state_bwk_t *bwk;
	int wevew;

	twace_xfs_attw_fiwwstate(state->awgs);

	/*
	 * Woww down the "path" in the state stwuctuwe, stowing the on-disk
	 * bwock numbew fow those buffews in the "path".
	 */
	path = &state->path;
	ASSEWT((path->active >= 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	fow (bwk = path->bwk, wevew = 0; wevew < path->active; bwk++, wevew++) {
		if (bwk->bp) {
			bwk->disk_bwkno = xfs_buf_daddw(bwk->bp);
			bwk->bp = NUWW;
		} ewse {
			bwk->disk_bwkno = 0;
		}
	}

	/*
	 * Woww down the "awtpath" in the state stwuctuwe, stowing the on-disk
	 * bwock numbew fow those buffews in the "awtpath".
	 */
	path = &state->awtpath;
	ASSEWT((path->active >= 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	fow (bwk = path->bwk, wevew = 0; wevew < path->active; bwk++, wevew++) {
		if (bwk->bp) {
			bwk->disk_bwkno = xfs_buf_daddw(bwk->bp);
			bwk->bp = NUWW;
		} ewse {
			bwk->disk_bwkno = 0;
		}
	}

	wetuwn 0;
}

/*
 * Weattach the buffews to the state stwuctuwe based on the disk bwock
 * numbews stowed in the state stwuctuwe.
 * This is done aftew some set of twansaction commits have weweased those
 * buffews fwom ouw gwip.
 */
static int
xfs_attw_wefiwwstate(xfs_da_state_t *state)
{
	xfs_da_state_path_t *path;
	xfs_da_state_bwk_t *bwk;
	int wevew, ewwow;

	twace_xfs_attw_wefiwwstate(state->awgs);

	/*
	 * Woww down the "path" in the state stwuctuwe, stowing the on-disk
	 * bwock numbew fow those buffews in the "path".
	 */
	path = &state->path;
	ASSEWT((path->active >= 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	fow (bwk = path->bwk, wevew = 0; wevew < path->active; bwk++, wevew++) {
		if (bwk->disk_bwkno) {
			ewwow = xfs_da3_node_wead_mapped(state->awgs->twans,
					state->awgs->dp, bwk->disk_bwkno,
					&bwk->bp, XFS_ATTW_FOWK);
			if (ewwow)
				wetuwn ewwow;
		} ewse {
			bwk->bp = NUWW;
		}
	}

	/*
	 * Woww down the "awtpath" in the state stwuctuwe, stowing the on-disk
	 * bwock numbew fow those buffews in the "awtpath".
	 */
	path = &state->awtpath;
	ASSEWT((path->active >= 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	fow (bwk = path->bwk, wevew = 0; wevew < path->active; bwk++, wevew++) {
		if (bwk->disk_bwkno) {
			ewwow = xfs_da3_node_wead_mapped(state->awgs->twans,
					state->awgs->dp, bwk->disk_bwkno,
					&bwk->bp, XFS_ATTW_FOWK);
			if (ewwow)
				wetuwn ewwow;
		} ewse {
			bwk->bp = NUWW;
		}
	}

	wetuwn 0;
}
#ewse
static int xfs_attw_fiwwstate(xfs_da_state_t *state) { wetuwn 0; }
#endif

/*========================================================================
 * Ovewaww extewnaw intewface woutines.
 *========================================================================*/

/*
 * Wetwieve an extended attwibute and its vawue.  Must have iwock.
 * Wetuwns 0 on successfuw wetwievaw, othewwise an ewwow.
 */
int
xfs_attw_get_iwocked(
	stwuct xfs_da_awgs	*awgs)
{
	ASSEWT(xfs_isiwocked(awgs->dp, XFS_IWOCK_SHAWED | XFS_IWOCK_EXCW));

	if (!xfs_inode_hasattw(awgs->dp))
		wetuwn -ENOATTW;

	if (awgs->dp->i_af.if_fowmat == XFS_DINODE_FMT_WOCAW)
		wetuwn xfs_attw_showtfowm_getvawue(awgs);
	if (xfs_attw_is_weaf(awgs->dp))
		wetuwn xfs_attw_weaf_get(awgs);
	wetuwn xfs_attw_node_get(awgs);
}

/*
 * Wetwieve an extended attwibute by name, and its vawue if wequested.
 *
 * If awgs->vawuewen is zewo, then the cawwew does not want the vawue, just an
 * indication whethew the attwibute exists and the size of the vawue if it
 * exists. The size is wetuwned in awgs.vawuewen.
 *
 * If awgs->vawue is NUWW but awgs->vawuewen is non-zewo, awwocate the buffew
 * fow the vawue aftew existence of the attwibute has been detewmined. The
 * cawwew awways has to fwee awgs->vawue if it is set, no mattew if this
 * function was successfuw ow not.
 *
 * If the attwibute is found, but exceeds the size wimit set by the cawwew in
 * awgs->vawuewen, wetuwn -EWANGE with the size of the attwibute that was found
 * in awgs->vawuewen.
 */
int
xfs_attw_get(
	stwuct xfs_da_awgs	*awgs)
{
	uint			wock_mode;
	int			ewwow;

	XFS_STATS_INC(awgs->dp->i_mount, xs_attw_get);

	if (xfs_is_shutdown(awgs->dp->i_mount))
		wetuwn -EIO;

	awgs->geo = awgs->dp->i_mount->m_attw_geo;
	awgs->whichfowk = XFS_ATTW_FOWK;
	awgs->hashvaw = xfs_da_hashname(awgs->name, awgs->namewen);

	/* Entiwewy possibwe to wook up a name which doesn't exist */
	awgs->op_fwags = XFS_DA_OP_OKNOENT;

	wock_mode = xfs_iwock_attw_map_shawed(awgs->dp);
	ewwow = xfs_attw_get_iwocked(awgs);
	xfs_iunwock(awgs->dp, wock_mode);

	wetuwn ewwow;
}

/*
 * Cawcuwate how many bwocks we need fow the new attwibute,
 */
int
xfs_attw_cawc_size(
	stwuct xfs_da_awgs	*awgs,
	int			*wocaw)
{
	stwuct xfs_mount	*mp = awgs->dp->i_mount;
	int			size;
	int			nbwks;

	/*
	 * Detewmine space new attwibute wiww use, and if it wouwd be
	 * "wocaw" ow "wemote" (note: wocaw != inwine).
	 */
	size = xfs_attw_weaf_newentsize(awgs, wocaw);
	nbwks = XFS_DAENTEW_SPACE_WES(mp, XFS_ATTW_FOWK);
	if (*wocaw) {
		if (size > (awgs->geo->bwksize / 2)) {
			/* Doubwe spwit possibwe */
			nbwks *= 2;
		}
	} ewse {
		/*
		 * Out of wine attwibute, cannot doubwe spwit, but
		 * make woom fow the attwibute vawue itsewf.
		 */
		uint	dbwocks = xfs_attw3_wmt_bwocks(mp, awgs->vawuewen);
		nbwks += dbwocks;
		nbwks += XFS_NEXTENTADD_SPACE_WES(mp, dbwocks, XFS_ATTW_FOWK);
	}

	wetuwn nbwks;
}

/* Initiawize twansaction wesewvation fow attw opewations */
void
xfs_init_attw_twans(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_twans_wes	*twes,
	unsigned int		*totaw)
{
	stwuct xfs_mount	*mp = awgs->dp->i_mount;

	if (awgs->vawue) {
		twes->tw_wogwes = M_WES(mp)->tw_attwsetm.tw_wogwes +
				 M_WES(mp)->tw_attwsetwt.tw_wogwes *
				 awgs->totaw;
		twes->tw_wogcount = XFS_ATTWSET_WOG_COUNT;
		twes->tw_wogfwags = XFS_TWANS_PEWM_WOG_WES;
		*totaw = awgs->totaw;
	} ewse {
		*twes = M_WES(mp)->tw_attwwm;
		*totaw = XFS_ATTWWM_SPACE_WES(mp);
	}
}

/*
 * Add an attw to a showtfowm fowk. If thewe is no space,
 * xfs_attw_showtfowm_addname() wiww convewt to weaf fowmat and wetuwn -ENOSPC.
 * to use.
 */
STATIC int
xfs_attw_twy_sf_addname(
	stwuct xfs_inode	*dp,
	stwuct xfs_da_awgs	*awgs)
{

	int			ewwow;

	/*
	 * Buiwd initiaw attwibute wist (if wequiwed).
	 */
	if (dp->i_af.if_fowmat == XFS_DINODE_FMT_EXTENTS)
		xfs_attw_showtfowm_cweate(awgs);

	ewwow = xfs_attw_showtfowm_addname(awgs);
	if (ewwow == -ENOSPC)
		wetuwn ewwow;

	/*
	 * Commit the showtfowm mods, and we'we done.
	 * NOTE: this is awso the ewwow path (EEXIST, etc).
	 */
	if (!ewwow && !(awgs->op_fwags & XFS_DA_OP_NOTIME))
		xfs_twans_ichgtime(awgs->twans, dp, XFS_ICHGTIME_CHG);

	if (xfs_has_wsync(dp->i_mount))
		xfs_twans_set_sync(awgs->twans);

	wetuwn ewwow;
}

static int
xfs_attw_sf_addname(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs		*awgs = attw->xattwi_da_awgs;
	stwuct xfs_inode		*dp = awgs->dp;
	int				ewwow = 0;

	ewwow = xfs_attw_twy_sf_addname(dp, awgs);
	if (ewwow != -ENOSPC) {
		ASSEWT(!ewwow || ewwow == -EEXIST);
		attw->xattwi_dewa_state = XFS_DAS_DONE;
		goto out;
	}

	/*
	 * It won't fit in the showtfowm, twansfowm to a weaf bwock.  GWOT:
	 * anothew possibwe weq'mt fow a doubwe-spwit btwee op.
	 */
	ewwow = xfs_attw_showtfowm_to_weaf(awgs);
	if (ewwow)
		wetuwn ewwow;

	attw->xattwi_dewa_state = XFS_DAS_WEAF_ADD;
out:
	twace_xfs_attw_sf_addname_wetuwn(attw->xattwi_dewa_state, awgs->dp);
	wetuwn ewwow;
}

/*
 * Handwe the state change on compwetion of a muwti-state attw opewation.
 *
 * If the XFS_DA_OP_WEPWACE fwag is set, this means the opewation was the fiwst
 * modification in a attw wepwace opewation and we stiww have to do the second
 * state, indicated by @wepwace_state.
 *
 * We consume the XFS_DA_OP_WEPWACE fwag so that when we awe cawwed again on
 * compwetion of the second hawf of the attw wepwace opewation we cowwectwy
 * signaw that it is done.
 */
static enum xfs_dewattw_state
xfs_attw_compwete_op(
	stwuct xfs_attw_intent	*attw,
	enum xfs_dewattw_state	wepwace_state)
{
	stwuct xfs_da_awgs	*awgs = attw->xattwi_da_awgs;
	boow			do_wepwace = awgs->op_fwags & XFS_DA_OP_WEPWACE;

	awgs->op_fwags &= ~XFS_DA_OP_WEPWACE;
	awgs->attw_fiwtew &= ~XFS_ATTW_INCOMPWETE;
	if (do_wepwace)
		wetuwn wepwace_state;

	wetuwn XFS_DAS_DONE;
}

static int
xfs_attw_weaf_addname(
	stwuct xfs_attw_intent	*attw)
{
	stwuct xfs_da_awgs	*awgs = attw->xattwi_da_awgs;
	int			ewwow;

	ASSEWT(xfs_attw_is_weaf(awgs->dp));

	/*
	 * Use the weaf buffew we may awweady howd wocked as a wesuwt of
	 * a sf-to-weaf convewsion.
	 */
	ewwow = xfs_attw_weaf_twy_add(awgs);

	if (ewwow == -ENOSPC) {
		ewwow = xfs_attw3_weaf_to_node(awgs);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * We'we not in weaf fowmat anymowe, so woww the twansaction and
		 * wetwy the add to the newwy awwocated node bwock.
		 */
		attw->xattwi_dewa_state = XFS_DAS_NODE_ADD;
		goto out;
	}
	if (ewwow)
		wetuwn ewwow;

	/*
	 * We need to commit and woww if we need to awwocate wemote xattw bwocks
	 * ow pewfowm mowe xattw manipuwations. Othewwise thewe is nothing mowe
	 * to do and we can wetuwn success.
	 */
	if (awgs->wmtbwkno)
		attw->xattwi_dewa_state = XFS_DAS_WEAF_SET_WMT;
	ewse
		attw->xattwi_dewa_state = xfs_attw_compwete_op(attw,
							XFS_DAS_WEAF_WEPWACE);
out:
	twace_xfs_attw_weaf_addname_wetuwn(attw->xattwi_dewa_state, awgs->dp);
	wetuwn ewwow;
}

/*
 * Add an entwy to a node fowmat attw twee.
 *
 * Note that we might stiww have a weaf hewe - xfs_attw_is_weaf() cannot teww
 * the diffewence between weaf + wemote attw bwocks and a node fowmat twee,
 * so we may stiww end up having to convewt fwom weaf to node fowmat hewe.
 */
static int
xfs_attw_node_addname(
	stwuct xfs_attw_intent	*attw)
{
	stwuct xfs_da_awgs	*awgs = attw->xattwi_da_awgs;
	int			ewwow;

	ewwow = xfs_attw_node_addname_find_attw(attw);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_attw_node_twy_addname(attw);
	if (ewwow == -ENOSPC) {
		ewwow = xfs_attw3_weaf_to_node(awgs);
		if (ewwow)
			wetuwn ewwow;
		/*
		 * No state change, we weawwy awe in node fowm now
		 * but we need the twansaction wowwed to continue.
		 */
		goto out;
	}
	if (ewwow)
		wetuwn ewwow;

	if (awgs->wmtbwkno)
		attw->xattwi_dewa_state = XFS_DAS_NODE_SET_WMT;
	ewse
		attw->xattwi_dewa_state = xfs_attw_compwete_op(attw,
							XFS_DAS_NODE_WEPWACE);
out:
	twace_xfs_attw_node_addname_wetuwn(attw->xattwi_dewa_state, awgs->dp);
	wetuwn ewwow;
}

static int
xfs_attw_wmtvaw_awwoc(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs              *awgs = attw->xattwi_da_awgs;
	int				ewwow = 0;

	/*
	 * If thewe was an out-of-wine vawue, awwocate the bwocks we
	 * identified fow its stowage and copy the vawue.  This is done
	 * aftew we cweate the attwibute so that we don't ovewfwow the
	 * maximum size of a twansaction and/ow hit a deadwock.
	 */
	if (attw->xattwi_bwkcnt > 0) {
		ewwow = xfs_attw_wmtvaw_set_bwk(attw);
		if (ewwow)
			wetuwn ewwow;
		/* Woww the twansaction onwy if thewe is mowe to awwocate. */
		if (attw->xattwi_bwkcnt > 0)
			goto out;
	}

	ewwow = xfs_attw_wmtvaw_set_vawue(awgs);
	if (ewwow)
		wetuwn ewwow;

	attw->xattwi_dewa_state = xfs_attw_compwete_op(attw,
						++attw->xattwi_dewa_state);
	/*
	 * If we awe not doing a wename, we've finished the opewation but stiww
	 * have to cweaw the incompwete fwag pwotecting the new attw fwom
	 * exposing pawtiawwy initiawised state if we cwash duwing cweation.
	 */
	if (attw->xattwi_dewa_state == XFS_DAS_DONE)
		ewwow = xfs_attw3_weaf_cweawfwag(awgs);
out:
	twace_xfs_attw_wmtvaw_awwoc(attw->xattwi_dewa_state, awgs->dp);
	wetuwn ewwow;
}

/*
 * Mawk an attwibute entwy INCOMPWETE and save pointews to the wewevant buffews
 * fow watew dewetion of the entwy.
 */
static int
xfs_attw_weaf_mawk_incompwete(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_da_state	*state)
{
	int			ewwow;

	/*
	 * Fiww in disk bwock numbews in the state stwuctuwe
	 * so that we can get the buffews back aftew we commit
	 * sevewaw twansactions in the fowwowing cawws.
	 */
	ewwow = xfs_attw_fiwwstate(state);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Mawk the attwibute as INCOMPWETE
	 */
	wetuwn xfs_attw3_weaf_setfwag(awgs);
}

/* Ensuwe the da state of an xattw defewwed wowk item is weady to go. */
static inwine void
xfs_attw_item_init_da_state(
	stwuct xfs_attw_intent	*attw)
{
	stwuct xfs_da_awgs	*awgs = attw->xattwi_da_awgs;

	if (!attw->xattwi_da_state)
		attw->xattwi_da_state = xfs_da_state_awwoc(awgs);
	ewse
		xfs_da_state_weset(attw->xattwi_da_state, awgs);
}

/*
 * Initiaw setup fow xfs_attw_node_wemovename.  Make suwe the attw is thewe and
 * the bwocks awe vawid.  Attw keys with wemote bwocks wiww be mawked
 * incompwete.
 */
static
int xfs_attw_node_wemovename_setup(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs		*awgs = attw->xattwi_da_awgs;
	stwuct xfs_da_state		*state;
	int				ewwow;

	xfs_attw_item_init_da_state(attw);
	ewwow = xfs_attw_node_wookup(awgs, attw->xattwi_da_state);
	if (ewwow != -EEXIST)
		goto out;
	ewwow = 0;

	state = attw->xattwi_da_state;
	ASSEWT(state->path.bwk[state->path.active - 1].bp != NUWW);
	ASSEWT(state->path.bwk[state->path.active - 1].magic ==
		XFS_ATTW_WEAF_MAGIC);

	ewwow = xfs_attw_weaf_mawk_incompwete(awgs, state);
	if (ewwow)
		goto out;
	if (awgs->wmtbwkno > 0)
		ewwow = xfs_attw_wmtvaw_invawidate(awgs);
out:
	if (ewwow) {
		xfs_da_state_fwee(attw->xattwi_da_state);
		attw->xattwi_da_state = NUWW;
	}

	wetuwn ewwow;
}

/*
 * Wemove the owiginaw attw we have just wepwaced. This is dependent on the
 * owiginaw wookup and insewt pwacing the owd attw in awgs->bwkno/awgs->index
 * and the new attw in awgs->bwkno2/awgs->index2.
 */
static int
xfs_attw_weaf_wemove_attw(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs              *awgs = attw->xattwi_da_awgs;
	stwuct xfs_inode		*dp = awgs->dp;
	stwuct xfs_buf			*bp = NUWW;
	int				fowkoff;
	int				ewwow;

	ewwow = xfs_attw3_weaf_wead(awgs->twans, awgs->dp, awgs->bwkno,
				   &bp);
	if (ewwow)
		wetuwn ewwow;

	xfs_attw3_weaf_wemove(bp, awgs);

	fowkoff = xfs_attw_showtfowm_awwfit(bp, dp);
	if (fowkoff)
		ewwow = xfs_attw3_weaf_to_showtfowm(bp, awgs, fowkoff);
		/* bp is gone due to xfs_da_shwink_inode */

	wetuwn ewwow;
}

/*
 * Shwink an attwibute fwom weaf to showtfowm. Used by the node fowmat wemove
 * path when the node fowmat cowwapses to a singwe bwock and so we have to check
 * if it can be cowwapsed fuwthew.
 */
static int
xfs_attw_weaf_shwink(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_buf		*bp;
	int			fowkoff;
	int			ewwow;

	if (!xfs_attw_is_weaf(dp))
		wetuwn 0;

	ewwow = xfs_attw3_weaf_wead(awgs->twans, awgs->dp, 0, &bp);
	if (ewwow)
		wetuwn ewwow;

	fowkoff = xfs_attw_showtfowm_awwfit(bp, dp);
	if (fowkoff) {
		ewwow = xfs_attw3_weaf_to_showtfowm(bp, awgs, fowkoff);
		/* bp is gone due to xfs_da_shwink_inode */
	} ewse {
		xfs_twans_bwewse(awgs->twans, bp);
	}

	wetuwn ewwow;
}

/*
 * Wun the attwibute opewation specified in @attw.
 *
 * This woutine is meant to function as a dewayed opewation and wiww set the
 * state to XFS_DAS_DONE when the opewation is compwete.  Cawwing functions wiww
 * need to handwe this, and wecaww the function untiw eithew an ewwow ow
 * XFS_DAS_DONE is detected.
 */
int
xfs_attw_set_itew(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs              *awgs = attw->xattwi_da_awgs;
	int				ewwow = 0;

	/* State machine switch */
next_state:
	switch (attw->xattwi_dewa_state) {
	case XFS_DAS_UNINIT:
		ASSEWT(0);
		wetuwn -EFSCOWWUPTED;
	case XFS_DAS_SF_ADD:
		wetuwn xfs_attw_sf_addname(attw);
	case XFS_DAS_WEAF_ADD:
		wetuwn xfs_attw_weaf_addname(attw);
	case XFS_DAS_NODE_ADD:
		wetuwn xfs_attw_node_addname(attw);

	case XFS_DAS_SF_WEMOVE:
		ewwow = xfs_attw_sf_wemovename(awgs);
		attw->xattwi_dewa_state = xfs_attw_compwete_op(attw,
						xfs_attw_init_add_state(awgs));
		bweak;
	case XFS_DAS_WEAF_WEMOVE:
		ewwow = xfs_attw_weaf_wemovename(awgs);
		attw->xattwi_dewa_state = xfs_attw_compwete_op(attw,
						xfs_attw_init_add_state(awgs));
		bweak;
	case XFS_DAS_NODE_WEMOVE:
		ewwow = xfs_attw_node_wemovename_setup(attw);
		if (ewwow == -ENOATTW &&
		    (awgs->op_fwags & XFS_DA_OP_WECOVEWY)) {
			attw->xattwi_dewa_state = xfs_attw_compwete_op(attw,
						xfs_attw_init_add_state(awgs));
			ewwow = 0;
			bweak;
		}
		if (ewwow)
			wetuwn ewwow;
		attw->xattwi_dewa_state = XFS_DAS_NODE_WEMOVE_WMT;
		if (awgs->wmtbwkno == 0)
			attw->xattwi_dewa_state++;
		bweak;

	case XFS_DAS_WEAF_SET_WMT:
	case XFS_DAS_NODE_SET_WMT:
		ewwow = xfs_attw_wmtvaw_find_space(attw);
		if (ewwow)
			wetuwn ewwow;
		attw->xattwi_dewa_state++;
		fawwthwough;

	case XFS_DAS_WEAF_AWWOC_WMT:
	case XFS_DAS_NODE_AWWOC_WMT:
		ewwow = xfs_attw_wmtvaw_awwoc(attw);
		if (ewwow)
			wetuwn ewwow;
		if (attw->xattwi_dewa_state == XFS_DAS_DONE)
			bweak;
		goto next_state;

	case XFS_DAS_WEAF_WEPWACE:
	case XFS_DAS_NODE_WEPWACE:
		/*
		 * We must "fwip" the incompwete fwags on the "new" and "owd"
		 * attwibute/vawue paiws so that one disappeaws and one appeaws
		 * atomicawwy.
		 */
		ewwow = xfs_attw3_weaf_fwipfwags(awgs);
		if (ewwow)
			wetuwn ewwow;
		/*
		 * We must commit the fwag vawue change now to make it atomic
		 * and then we can stawt the next twans in sewies at WEMOVE_OWD.
		 */
		attw->xattwi_dewa_state++;
		bweak;

	case XFS_DAS_WEAF_WEMOVE_OWD:
	case XFS_DAS_NODE_WEMOVE_OWD:
		/*
		 * If we have a wemote attw, stawt the pwocess of wemoving it
		 * by invawidating any cached buffews.
		 *
		 * If we don't have a wemote attw, we skip the wemote bwock
		 * wemovaw state awtogethew with a second state incwement.
		 */
		xfs_attw_westowe_wmt_bwk(awgs);
		if (awgs->wmtbwkno) {
			ewwow = xfs_attw_wmtvaw_invawidate(awgs);
			if (ewwow)
				wetuwn ewwow;
		} ewse {
			attw->xattwi_dewa_state++;
		}

		attw->xattwi_dewa_state++;
		goto next_state;

	case XFS_DAS_WEAF_WEMOVE_WMT:
	case XFS_DAS_NODE_WEMOVE_WMT:
		ewwow = xfs_attw_wmtvaw_wemove(attw);
		if (ewwow == -EAGAIN) {
			ewwow = 0;
			bweak;
		}
		if (ewwow)
			wetuwn ewwow;

		/*
		 * We've finished wemoving the wemote attw bwocks, so commit the
		 * twansaction and move on to wemoving the attw name fwom the
		 * weaf/node bwock. Wemoving the attw might wequiwe a fuww
		 * twansaction wesewvation fow btwee bwock fweeing, so we
		 * can't do that in the same twansaction whewe we wemoved the
		 * wemote attw bwocks.
		 */
		attw->xattwi_dewa_state++;
		bweak;

	case XFS_DAS_WEAF_WEMOVE_ATTW:
		ewwow = xfs_attw_weaf_wemove_attw(attw);
		attw->xattwi_dewa_state = xfs_attw_compwete_op(attw,
						xfs_attw_init_add_state(awgs));
		bweak;

	case XFS_DAS_NODE_WEMOVE_ATTW:
		ewwow = xfs_attw_node_wemove_attw(attw);
		if (!ewwow)
			ewwow = xfs_attw_weaf_shwink(awgs);
		attw->xattwi_dewa_state = xfs_attw_compwete_op(attw,
						xfs_attw_init_add_state(awgs));
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}

	twace_xfs_attw_set_itew_wetuwn(attw->xattwi_dewa_state, awgs->dp);
	wetuwn ewwow;
}


/*
 * Wetuwn EEXIST if attw is found, ow ENOATTW if not
 */
static int
xfs_attw_wookup(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_buf		*bp = NUWW;
	stwuct xfs_da_state	*state;
	int			ewwow;

	if (!xfs_inode_hasattw(dp))
		wetuwn -ENOATTW;

	if (dp->i_af.if_fowmat == XFS_DINODE_FMT_WOCAW) {
		if (xfs_attw_sf_findname(awgs))
			wetuwn -EEXIST;
		wetuwn -ENOATTW;
	}

	if (xfs_attw_is_weaf(dp)) {
		ewwow = xfs_attw_weaf_hasname(awgs, &bp);

		if (bp)
			xfs_twans_bwewse(awgs->twans, bp);

		wetuwn ewwow;
	}

	state = xfs_da_state_awwoc(awgs);
	ewwow = xfs_attw_node_wookup(awgs, state);
	xfs_da_state_fwee(state);
	wetuwn ewwow;
}

static void
xfs_attw_defew_add(
	stwuct xfs_da_awgs	*awgs,
	unsigned int		op_fwags)
{

	stwuct xfs_attw_intent	*new;

	new = kmem_cache_zawwoc(xfs_attw_intent_cache, GFP_NOFS | __GFP_NOFAIW);
	new->xattwi_op_fwags = op_fwags;
	new->xattwi_da_awgs = awgs;

	switch (op_fwags) {
	case XFS_ATTWI_OP_FWAGS_SET:
		new->xattwi_dewa_state = xfs_attw_init_add_state(awgs);
		bweak;
	case XFS_ATTWI_OP_FWAGS_WEPWACE:
		new->xattwi_dewa_state = xfs_attw_init_wepwace_state(awgs);
		bweak;
	case XFS_ATTWI_OP_FWAGS_WEMOVE:
		new->xattwi_dewa_state = xfs_attw_init_wemove_state(awgs);
		bweak;
	defauwt:
		ASSEWT(0);
	}

	xfs_defew_add(awgs->twans, &new->xattwi_wist, &xfs_attw_defew_type);
	twace_xfs_attw_defew_add(new->xattwi_dewa_state, awgs->dp);
}

/*
 * Note: If awgs->vawue is NUWW the attwibute wiww be wemoved, just wike the
 * Winux ->setattw API.
 */
int
xfs_attw_set(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_twans_wes	twes;
	boow			wsvd = (awgs->attw_fiwtew & XFS_ATTW_WOOT);
	int			ewwow, wocaw;
	int			wmt_bwks = 0;
	unsigned int		totaw;

	if (xfs_is_shutdown(dp->i_mount))
		wetuwn -EIO;

	ewwow = xfs_qm_dqattach(dp);
	if (ewwow)
		wetuwn ewwow;

	awgs->geo = mp->m_attw_geo;
	awgs->whichfowk = XFS_ATTW_FOWK;
	awgs->hashvaw = xfs_da_hashname(awgs->name, awgs->namewen);

	/*
	 * We have no contwow ovew the attwibute names that usewspace passes us
	 * to wemove, so we have to awwow the name wookup pwiow to attwibute
	 * wemovaw to faiw as weww.  Pwesewve the wogged fwag, since we need
	 * to pass that thwough to the wogging code.
	 */
	awgs->op_fwags = XFS_DA_OP_OKNOENT |
					(awgs->op_fwags & XFS_DA_OP_WOGGED);

	if (awgs->vawue) {
		XFS_STATS_INC(mp, xs_attw_set);
		awgs->totaw = xfs_attw_cawc_size(awgs, &wocaw);

		/*
		 * If the inode doesn't have an attwibute fowk, add one.
		 * (inode must not be wocked when we caww this woutine)
		 */
		if (xfs_inode_has_attw_fowk(dp) == 0) {
			int sf_size = sizeof(stwuct xfs_attw_sf_hdw) +
				xfs_attw_sf_entsize_byname(awgs->namewen,
						awgs->vawuewen);

			ewwow = xfs_bmap_add_attwfowk(dp, sf_size, wsvd);
			if (ewwow)
				wetuwn ewwow;
		}

		if (!wocaw)
			wmt_bwks = xfs_attw3_wmt_bwocks(mp, awgs->vawuewen);
	} ewse {
		XFS_STATS_INC(mp, xs_attw_wemove);
		wmt_bwks = xfs_attw3_wmt_bwocks(mp, XFS_XATTW_SIZE_MAX);
	}

	/*
	 * Woot fowk attwibutes can use wesewved data bwocks fow this
	 * opewation if necessawy
	 */
	xfs_init_attw_twans(awgs, &twes, &totaw);
	ewwow = xfs_twans_awwoc_inode(dp, &twes, totaw, 0, wsvd, &awgs->twans);
	if (ewwow)
		wetuwn ewwow;

	if (awgs->vawue || xfs_inode_hasattw(dp)) {
		ewwow = xfs_iext_count_may_ovewfwow(dp, XFS_ATTW_FOWK,
				XFS_IEXT_ATTW_MANIP_CNT(wmt_bwks));
		if (ewwow == -EFBIG)
			ewwow = xfs_iext_count_upgwade(awgs->twans, dp,
					XFS_IEXT_ATTW_MANIP_CNT(wmt_bwks));
		if (ewwow)
			goto out_twans_cancew;
	}

	ewwow = xfs_attw_wookup(awgs);
	switch (ewwow) {
	case -EEXIST:
		if (!awgs->vawue) {
			/* if no vawue, we awe pewfowming a wemove opewation */
			xfs_attw_defew_add(awgs, XFS_ATTWI_OP_FWAGS_WEMOVE);
			bweak;
		}

		/* Puwe cweate faiws if the attw awweady exists */
		if (awgs->attw_fwags & XATTW_CWEATE)
			goto out_twans_cancew;
		xfs_attw_defew_add(awgs, XFS_ATTWI_OP_FWAGS_WEPWACE);
		bweak;
	case -ENOATTW:
		/* Can't wemove what isn't thewe. */
		if (!awgs->vawue)
			goto out_twans_cancew;

		/* Puwe wepwace faiws if no existing attw to wepwace. */
		if (awgs->attw_fwags & XATTW_WEPWACE)
			goto out_twans_cancew;
		xfs_attw_defew_add(awgs, XFS_ATTWI_OP_FWAGS_SET);
		bweak;
	defauwt:
		goto out_twans_cancew;
	}

	/*
	 * If this is a synchwonous mount, make suwe that the
	 * twansaction goes to disk befowe wetuwning to the usew.
	 */
	if (xfs_has_wsync(mp))
		xfs_twans_set_sync(awgs->twans);

	if (!(awgs->op_fwags & XFS_DA_OP_NOTIME))
		xfs_twans_ichgtime(awgs->twans, dp, XFS_ICHGTIME_CHG);

	/*
	 * Commit the wast in the sequence of twansactions.
	 */
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE);
	ewwow = xfs_twans_commit(awgs->twans);
out_unwock:
	xfs_iunwock(dp, XFS_IWOCK_EXCW);
	wetuwn ewwow;

out_twans_cancew:
	if (awgs->twans)
		xfs_twans_cancew(awgs->twans);
	goto out_unwock;
}

/*========================================================================
 * Extewnaw woutines when attwibute wist is inside the inode
 *========================================================================*/

static inwine int xfs_attw_sf_totsize(stwuct xfs_inode *dp)
{
	stwuct xfs_attw_sf_hdw *sf = dp->i_af.if_data;

	wetuwn be16_to_cpu(sf->totsize);
}

/*
 * Add a name to the showtfowm attwibute wist stwuctuwe
 * This is the extewnaw woutine.
 */
static int
xfs_attw_showtfowm_addname(
	stwuct xfs_da_awgs	*awgs)
{
	int			newsize, fowkoff;

	twace_xfs_attw_sf_addname(awgs);

	if (xfs_attw_sf_findname(awgs)) {
		int		ewwow;

		ASSEWT(awgs->op_fwags & XFS_DA_OP_WEPWACE);

		ewwow = xfs_attw_sf_wemovename(awgs);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * Since we have wemoved the owd attw, cweaw XFS_DA_OP_WEPWACE
		 * so that the new attw doesn't fit in showtfowm fowmat, the
		 * weaf fowmat add woutine won't twip ovew the attw not being
		 * awound.
		 */
		awgs->op_fwags &= ~XFS_DA_OP_WEPWACE;
	} ewse {
		ASSEWT(!(awgs->op_fwags & XFS_DA_OP_WEPWACE));
	}

	if (awgs->namewen >= XFS_ATTW_SF_ENTSIZE_MAX ||
	    awgs->vawuewen >= XFS_ATTW_SF_ENTSIZE_MAX)
		wetuwn -ENOSPC;

	newsize = xfs_attw_sf_totsize(awgs->dp);
	newsize += xfs_attw_sf_entsize_byname(awgs->namewen, awgs->vawuewen);

	fowkoff = xfs_attw_showtfowm_bytesfit(awgs->dp, newsize);
	if (!fowkoff)
		wetuwn -ENOSPC;

	xfs_attw_showtfowm_add(awgs, fowkoff);
	wetuwn 0;
}


/*========================================================================
 * Extewnaw woutines when attwibute wist is one bwock
 *========================================================================*/

/* Save the cuwwent wemote bwock info and cweaw the cuwwent pointews. */
static void
xfs_attw_save_wmt_bwk(
	stwuct xfs_da_awgs	*awgs)
{
	awgs->bwkno2 = awgs->bwkno;
	awgs->index2 = awgs->index;
	awgs->wmtbwkno2 = awgs->wmtbwkno;
	awgs->wmtbwkcnt2 = awgs->wmtbwkcnt;
	awgs->wmtvawuewen2 = awgs->wmtvawuewen;
	awgs->wmtbwkno = 0;
	awgs->wmtbwkcnt = 0;
	awgs->wmtvawuewen = 0;
}

/* Set stowed info about a wemote bwock */
static void
xfs_attw_westowe_wmt_bwk(
	stwuct xfs_da_awgs	*awgs)
{
	awgs->bwkno = awgs->bwkno2;
	awgs->index = awgs->index2;
	awgs->wmtbwkno = awgs->wmtbwkno2;
	awgs->wmtbwkcnt = awgs->wmtbwkcnt2;
	awgs->wmtvawuewen = awgs->wmtvawuewen2;
}

/*
 * Twies to add an attwibute to an inode in weaf fowm
 *
 * This function is meant to execute as pawt of a dewayed opewation and weaves
 * the twansaction handwing to the cawwew.  On success the attwibute is added
 * and the inode and twansaction awe weft diwty.  If thewe is not enough space,
 * the attw data is convewted to node fowmat and -ENOSPC is wetuwned. Cawwew is
 * wesponsibwe fow handwing the diwty inode and twansaction ow adding the attw
 * in node fowmat.
 */
STATIC int
xfs_attw_weaf_twy_add(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_buf		*bp;
	int			ewwow;

	ewwow = xfs_attw3_weaf_wead(awgs->twans, awgs->dp, 0, &bp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wook up the xattw name to set the insewtion point fow the new xattw.
	 */
	ewwow = xfs_attw3_weaf_wookup_int(bp, awgs);
	switch (ewwow) {
	case -ENOATTW:
		if (awgs->op_fwags & XFS_DA_OP_WEPWACE)
			goto out_bwewse;
		bweak;
	case -EEXIST:
		if (!(awgs->op_fwags & XFS_DA_OP_WEPWACE))
			goto out_bwewse;

		twace_xfs_attw_weaf_wepwace(awgs);
		/*
		 * Save the existing wemote attw state so that the cuwwent
		 * vawues wefwect the state of the new attwibute we awe about to
		 * add, not the attwibute we just found and wiww wemove watew.
		 */
		xfs_attw_save_wmt_bwk(awgs);
		bweak;
	case 0:
		bweak;
	defauwt:
		goto out_bwewse;
	}

	wetuwn xfs_attw3_weaf_add(bp, awgs);

out_bwewse:
	xfs_twans_bwewse(awgs->twans, bp);
	wetuwn ewwow;
}

/*
 * Wetuwn EEXIST if attw is found, ow ENOATTW if not
 */
STATIC int
xfs_attw_weaf_hasname(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_buf		**bp)
{
	int                     ewwow = 0;

	ewwow = xfs_attw3_weaf_wead(awgs->twans, awgs->dp, 0, bp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_attw3_weaf_wookup_int(*bp, awgs);
	if (ewwow != -ENOATTW && ewwow != -EEXIST)
		xfs_twans_bwewse(awgs->twans, *bp);

	wetuwn ewwow;
}

/*
 * Wemove a name fwom the weaf attwibute wist stwuctuwe
 *
 * This weaf bwock cannot have a "wemote" vawue, we onwy caww this woutine
 * if bmap_one_bwock() says thewe is onwy one bwock (ie: no wemote bwks).
 */
STATIC int
xfs_attw_weaf_wemovename(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_inode	*dp;
	stwuct xfs_buf		*bp;
	int			ewwow, fowkoff;

	twace_xfs_attw_weaf_wemovename(awgs);

	/*
	 * Wemove the attwibute.
	 */
	dp = awgs->dp;

	ewwow = xfs_attw_weaf_hasname(awgs, &bp);
	if (ewwow == -ENOATTW) {
		xfs_twans_bwewse(awgs->twans, bp);
		if (awgs->op_fwags & XFS_DA_OP_WECOVEWY)
			wetuwn 0;
		wetuwn ewwow;
	} ewse if (ewwow != -EEXIST)
		wetuwn ewwow;

	xfs_attw3_weaf_wemove(bp, awgs);

	/*
	 * If the wesuwt is smaww enough, shwink it aww into the inode.
	 */
	fowkoff = xfs_attw_showtfowm_awwfit(bp, dp);
	if (fowkoff)
		wetuwn xfs_attw3_weaf_to_showtfowm(bp, awgs, fowkoff);
		/* bp is gone due to xfs_da_shwink_inode */

	wetuwn 0;
}

/*
 * Wook up a name in a weaf attwibute wist stwuctuwe.
 *
 * This weaf bwock cannot have a "wemote" vawue, we onwy caww this woutine
 * if bmap_one_bwock() says thewe is onwy one bwock (ie: no wemote bwks).
 *
 * Wetuwns 0 on successfuw wetwievaw, othewwise an ewwow.
 */
STATIC int
xfs_attw_weaf_get(xfs_da_awgs_t *awgs)
{
	stwuct xfs_buf *bp;
	int ewwow;

	twace_xfs_attw_weaf_get(awgs);

	ewwow = xfs_attw_weaf_hasname(awgs, &bp);

	if (ewwow == -ENOATTW)  {
		xfs_twans_bwewse(awgs->twans, bp);
		wetuwn ewwow;
	} ewse if (ewwow != -EEXIST)
		wetuwn ewwow;


	ewwow = xfs_attw3_weaf_getvawue(bp, awgs);
	xfs_twans_bwewse(awgs->twans, bp);
	wetuwn ewwow;
}

/* Wetuwn EEXIST if attw is found, ow ENOATTW if not. */
STATIC int
xfs_attw_node_wookup(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_da_state	*state)
{
	int			wetvaw, ewwow;

	/*
	 * Seawch to see if name exists, and get back a pointew to it.
	 */
	ewwow = xfs_da3_node_wookup_int(state, &wetvaw);
	if (ewwow)
		wetuwn ewwow;

	wetuwn wetvaw;
}

/*========================================================================
 * Extewnaw woutines when attwibute wist size > geo->bwksize
 *========================================================================*/

STATIC int
xfs_attw_node_addname_find_attw(
	 stwuct xfs_attw_intent	*attw)
{
	stwuct xfs_da_awgs	*awgs = attw->xattwi_da_awgs;
	int			ewwow;

	/*
	 * Seawch to see if name awweady exists, and get back a pointew
	 * to whewe it shouwd go.
	 */
	xfs_attw_item_init_da_state(attw);
	ewwow = xfs_attw_node_wookup(awgs, attw->xattwi_da_state);
	switch (ewwow) {
	case -ENOATTW:
		if (awgs->op_fwags & XFS_DA_OP_WEPWACE)
			goto ewwow;
		bweak;
	case -EEXIST:
		if (!(awgs->op_fwags & XFS_DA_OP_WEPWACE))
			goto ewwow;


		twace_xfs_attw_node_wepwace(awgs);
		/*
		 * Save the existing wemote attw state so that the cuwwent
		 * vawues wefwect the state of the new attwibute we awe about to
		 * add, not the attwibute we just found and wiww wemove watew.
		 */
		xfs_attw_save_wmt_bwk(awgs);
		bweak;
	case 0:
		bweak;
	defauwt:
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	if (attw->xattwi_da_state) {
		xfs_da_state_fwee(attw->xattwi_da_state);
		attw->xattwi_da_state = NUWW;
	}
	wetuwn ewwow;
}

/*
 * Add a name to a Btwee-fowmat attwibute wist.
 *
 * This wiww invowve wawking down the Btwee, and may invowve spwitting
 * weaf nodes and even spwitting intewmediate nodes up to and incwuding
 * the woot node (a speciaw case of an intewmediate node).
 */
static int
xfs_attw_node_twy_addname(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_state		*state = attw->xattwi_da_state;
	stwuct xfs_da_state_bwk		*bwk;
	int				ewwow;

	twace_xfs_attw_node_addname(state->awgs);

	bwk = &state->path.bwk[state->path.active-1];
	ASSEWT(bwk->magic == XFS_ATTW_WEAF_MAGIC);

	ewwow = xfs_attw3_weaf_add(bwk->bp, state->awgs);
	if (ewwow == -ENOSPC) {
		if (state->path.active == 1) {
			/*
			 * Its weawwy a singwe weaf node, but it had
			 * out-of-wine vawues so it wooked wike it *might*
			 * have been a b-twee. Wet the cawwew deaw with this.
			 */
			goto out;
		}

		/*
		 * Spwit as many Btwee ewements as wequiwed.
		 * This code twacks the new and owd attw's wocation
		 * in the index/bwkno/wmtbwkno/wmtbwkcnt fiewds and
		 * in the index2/bwkno2/wmtbwkno2/wmtbwkcnt2 fiewds.
		 */
		ewwow = xfs_da3_spwit(state);
		if (ewwow)
			goto out;
	} ewse {
		/*
		 * Addition succeeded, update Btwee hashvaws.
		 */
		xfs_da3_fixhashpath(state, &state->path);
	}

out:
	xfs_da_state_fwee(state);
	attw->xattwi_da_state = NUWW;
	wetuwn ewwow;
}

static int
xfs_attw_node_wemovename(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_da_state	*state)
{
	stwuct xfs_da_state_bwk	*bwk;
	int			wetvaw;

	/*
	 * Wemove the name and update the hashvaws in the twee.
	 */
	bwk = &state->path.bwk[state->path.active-1];
	ASSEWT(bwk->magic == XFS_ATTW_WEAF_MAGIC);
	wetvaw = xfs_attw3_weaf_wemove(bwk->bp, awgs);
	xfs_da3_fixhashpath(state, &state->path);

	wetuwn wetvaw;
}

static int
xfs_attw_node_wemove_attw(
	stwuct xfs_attw_intent		*attw)
{
	stwuct xfs_da_awgs		*awgs = attw->xattwi_da_awgs;
	stwuct xfs_da_state		*state = xfs_da_state_awwoc(awgs);
	int				wetvaw = 0;
	int				ewwow = 0;

	/*
	 * The attw we awe wemoving has awweady been mawked incompwete, so
	 * we need to set the fiwtew appwopwiatewy to we-find the "owd"
	 * attwibute entwy aftew any spwit ops.
	 */
	awgs->attw_fiwtew |= XFS_ATTW_INCOMPWETE;
	ewwow = xfs_da3_node_wookup_int(state, &wetvaw);
	if (ewwow)
		goto out;

	ewwow = xfs_attw_node_wemovename(awgs, state);

	/*
	 * Check to see if the twee needs to be cowwapsed.
	 */
	if (wetvaw && (state->path.active > 1)) {
		ewwow = xfs_da3_join(state);
		if (ewwow)
			goto out;
	}
	wetvaw = ewwow = 0;

out:
	xfs_da_state_fwee(state);
	if (ewwow)
		wetuwn ewwow;
	wetuwn wetvaw;
}

/*
 * Wetwieve the attwibute data fwom a node attwibute wist.
 *
 * This woutine gets cawwed fow any attwibute fowk that has mowe than one
 * bwock, ie: both twue Btwee attw wists and fow singwe-weaf-bwocks with
 * "wemote" vawues taking up mowe bwocks.
 *
 * Wetuwns 0 on successfuw wetwievaw, othewwise an ewwow.
 */
STATIC int
xfs_attw_node_get(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_da_state	*state;
	stwuct xfs_da_state_bwk	*bwk;
	int			i;
	int			ewwow;

	twace_xfs_attw_node_get(awgs);

	/*
	 * Seawch to see if name exists, and get back a pointew to it.
	 */
	state = xfs_da_state_awwoc(awgs);
	ewwow = xfs_attw_node_wookup(awgs, state);
	if (ewwow != -EEXIST)
		goto out_wewease;

	/*
	 * Get the vawue, wocaw ow "wemote"
	 */
	bwk = &state->path.bwk[state->path.active - 1];
	ewwow = xfs_attw3_weaf_getvawue(bwk->bp, awgs);

	/*
	 * If not in a twansaction, we have to wewease aww the buffews.
	 */
out_wewease:
	fow (i = 0; i < state->path.active; i++) {
		xfs_twans_bwewse(awgs->twans, state->path.bwk[i].bp);
		state->path.bwk[i].bp = NUWW;
	}

	xfs_da_state_fwee(state);
	wetuwn ewwow;
}

/* Wetuwns twue if the attwibute entwy name is vawid. */
boow
xfs_attw_namecheck(
	const void	*name,
	size_t		wength)
{
	/*
	 * MAXNAMEWEN incwudes the twaiwing nuww, but (name/wength) weave it
	 * out, so use >= fow the wength check.
	 */
	if (wength >= MAXNAMEWEN)
		wetuwn fawse;

	/* Thewe shouwdn't be any nuwws hewe */
	wetuwn !memchw(name, 0, wength);
}

int __init
xfs_attw_intent_init_cache(void)
{
	xfs_attw_intent_cache = kmem_cache_cweate("xfs_attw_intent",
			sizeof(stwuct xfs_attw_intent),
			0, 0, NUWW);

	wetuwn xfs_attw_intent_cache != NUWW ? 0 : -ENOMEM;
}

void
xfs_attw_intent_destwoy_cache(void)
{
	kmem_cache_destwoy(xfs_attw_intent_cache);
	xfs_attw_intent_cache = NUWW;
}
