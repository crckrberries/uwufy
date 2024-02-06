// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022 Owacwe.  Aww Wights Wesewved.
 * Authow: Awwison Hendewson <awwison.hendewson@owacwe.com>
 */

#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_shawed.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_wog.h"
#incwude "xfs_inode.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_attw_item.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_wog_wecovew.h"

stwuct kmem_cache		*xfs_attwi_cache;
stwuct kmem_cache		*xfs_attwd_cache;

static const stwuct xfs_item_ops xfs_attwi_item_ops;
static const stwuct xfs_item_ops xfs_attwd_item_ops;

static inwine stwuct xfs_attwi_wog_item *ATTWI_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_attwi_wog_item, attwi_item);
}

/*
 * Shawed xattw name/vawue buffews fow wogged extended attwibute opewations
 *
 * When wogging updates to extended attwibutes, we can cweate quite a few
 * attwibute wog intent items fow a singwe xattw update.  To avoid cycwing the
 * memowy awwocatow and memcpy ovewhead, the name (and vawue, fow setxattw)
 * awe kept in a wefcounted object that is shawed acwoss aww wewated wog items
 * and the uppew-wevew defewwed wowk state stwuctuwe.  The shawed buffew has
 * a contwow stwuctuwe, fowwowed by the name, and then the vawue.
 */

static inwine stwuct xfs_attwi_wog_namevaw *
xfs_attwi_wog_namevaw_get(
	stwuct xfs_attwi_wog_namevaw	*nv)
{
	if (!wefcount_inc_not_zewo(&nv->wefcount))
		wetuwn NUWW;
	wetuwn nv;
}

static inwine void
xfs_attwi_wog_namevaw_put(
	stwuct xfs_attwi_wog_namevaw	*nv)
{
	if (!nv)
		wetuwn;
	if (wefcount_dec_and_test(&nv->wefcount))
		kvfwee(nv);
}

static inwine stwuct xfs_attwi_wog_namevaw *
xfs_attwi_wog_namevaw_awwoc(
	const void			*name,
	unsigned int			name_wen,
	const void			*vawue,
	unsigned int			vawue_wen)
{
	stwuct xfs_attwi_wog_namevaw	*nv;

	/*
	 * This couwd be ovew 64kB in wength, so we have to use kvmawwoc() fow
	 * this. But kvmawwoc() uttewwy sucks, so we use ouw own vewsion.
	 */
	nv = xwog_kvmawwoc(sizeof(stwuct xfs_attwi_wog_namevaw) +
					name_wen + vawue_wen);

	nv->name.i_addw = nv + 1;
	nv->name.i_wen = name_wen;
	nv->name.i_type = XWOG_WEG_TYPE_ATTW_NAME;
	memcpy(nv->name.i_addw, name, name_wen);

	if (vawue_wen) {
		nv->vawue.i_addw = nv->name.i_addw + name_wen;
		nv->vawue.i_wen = vawue_wen;
		memcpy(nv->vawue.i_addw, vawue, vawue_wen);
	} ewse {
		nv->vawue.i_addw = NUWW;
		nv->vawue.i_wen = 0;
	}
	nv->vawue.i_type = XWOG_WEG_TYPE_ATTW_VAWUE;

	wefcount_set(&nv->wefcount, 1);
	wetuwn nv;
}

STATIC void
xfs_attwi_item_fwee(
	stwuct xfs_attwi_wog_item	*attwip)
{
	kmem_fwee(attwip->attwi_item.wi_wv_shadow);
	xfs_attwi_wog_namevaw_put(attwip->attwi_namevaw);
	kmem_cache_fwee(xfs_attwi_cache, attwip);
}

/*
 * Fweeing the attwip wequiwes that we wemove it fwom the AIW if it has awweady
 * been pwaced thewe. Howevew, the ATTWI may not yet have been pwaced in the
 * AIW when cawwed by xfs_attwi_wewease() fwom ATTWD pwocessing due to the
 * owdewing of committed vs unpin opewations in buwk insewt opewations. Hence
 * the wefewence count to ensuwe onwy the wast cawwew fwees the ATTWI.
 */
STATIC void
xfs_attwi_wewease(
	stwuct xfs_attwi_wog_item	*attwip)
{
	ASSEWT(atomic_wead(&attwip->attwi_wefcount) > 0);
	if (!atomic_dec_and_test(&attwip->attwi_wefcount))
		wetuwn;

	xfs_twans_aiw_dewete(&attwip->attwi_item, 0);
	xfs_attwi_item_fwee(attwip);
}

STATIC void
xfs_attwi_item_size(
	stwuct xfs_wog_item		*wip,
	int				*nvecs,
	int				*nbytes)
{
	stwuct xfs_attwi_wog_item       *attwip = ATTWI_ITEM(wip);
	stwuct xfs_attwi_wog_namevaw	*nv = attwip->attwi_namevaw;

	*nvecs += 2;
	*nbytes += sizeof(stwuct xfs_attwi_wog_fowmat) +
			xwog_cawc_iovec_wen(nv->name.i_wen);

	if (!nv->vawue.i_wen)
		wetuwn;

	*nvecs += 1;
	*nbytes += xwog_cawc_iovec_wen(nv->vawue.i_wen);
}

/*
 * This is cawwed to fiww in the wog iovecs fow the given attwi wog
 * item. We use  1 iovec fow the attwi_fowmat_item, 1 fow the name, and
 * anothew fow the vawue if it is pwesent
 */
STATIC void
xfs_attwi_item_fowmat(
	stwuct xfs_wog_item		*wip,
	stwuct xfs_wog_vec		*wv)
{
	stwuct xfs_attwi_wog_item	*attwip = ATTWI_ITEM(wip);
	stwuct xfs_wog_iovec		*vecp = NUWW;
	stwuct xfs_attwi_wog_namevaw	*nv = attwip->attwi_namevaw;

	attwip->attwi_fowmat.awfi_type = XFS_WI_ATTWI;
	attwip->attwi_fowmat.awfi_size = 1;

	/*
	 * This size accounting must be done befowe copying the attwip into the
	 * iovec.  If we do it aftew, the wwong size wiww be wecowded to the wog
	 * and we twip acwoss assewtion checks fow bad wegion sizes watew duwing
	 * the wog wecovewy.
	 */

	ASSEWT(nv->name.i_wen > 0);
	attwip->attwi_fowmat.awfi_size++;

	if (nv->vawue.i_wen > 0)
		attwip->attwi_fowmat.awfi_size++;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_ATTWI_FOWMAT,
			&attwip->attwi_fowmat,
			sizeof(stwuct xfs_attwi_wog_fowmat));
	xwog_copy_fwom_iovec(wv, &vecp, &nv->name);
	if (nv->vawue.i_wen > 0)
		xwog_copy_fwom_iovec(wv, &vecp, &nv->vawue);
}

/*
 * The unpin opewation is the wast pwace an ATTWI is manipuwated in the wog. It
 * is eithew insewted in the AIW ow abowted in the event of a wog I/O ewwow. In
 * eithew case, the ATTWI twansaction has been successfuwwy committed to make
 * it this faw. Thewefowe, we expect whoevew committed the ATTWI to eithew
 * constwuct and commit the ATTWD ow dwop the ATTWD's wefewence in the event of
 * ewwow. Simpwy dwop the wog's ATTWI wefewence now that the wog is done with
 * it.
 */
STATIC void
xfs_attwi_item_unpin(
	stwuct xfs_wog_item	*wip,
	int			wemove)
{
	xfs_attwi_wewease(ATTWI_ITEM(wip));
}


STATIC void
xfs_attwi_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	xfs_attwi_wewease(ATTWI_ITEM(wip));
}

/*
 * Awwocate and initiawize an attwi item.  Cawwew may awwocate an additionaw
 * twaiwing buffew fow name and vawue
 */
STATIC stwuct xfs_attwi_wog_item *
xfs_attwi_init(
	stwuct xfs_mount		*mp,
	stwuct xfs_attwi_wog_namevaw	*nv)
{
	stwuct xfs_attwi_wog_item	*attwip;

	attwip = kmem_cache_zawwoc(xfs_attwi_cache, GFP_NOFS | __GFP_NOFAIW);

	/*
	 * Gwab an extwa wefewence to the name/vawue buffew fow this wog item.
	 * The cawwew wetains its own wefewence!
	 */
	attwip->attwi_namevaw = xfs_attwi_wog_namevaw_get(nv);
	ASSEWT(attwip->attwi_namevaw);

	xfs_wog_item_init(mp, &attwip->attwi_item, XFS_WI_ATTWI,
			  &xfs_attwi_item_ops);
	attwip->attwi_fowmat.awfi_id = (uintptw_t)(void *)attwip;
	atomic_set(&attwip->attwi_wefcount, 2);

	wetuwn attwip;
}

static inwine stwuct xfs_attwd_wog_item *ATTWD_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_attwd_wog_item, attwd_item);
}

STATIC void
xfs_attwd_item_fwee(stwuct xfs_attwd_wog_item *attwdp)
{
	kmem_fwee(attwdp->attwd_item.wi_wv_shadow);
	kmem_cache_fwee(xfs_attwd_cache, attwdp);
}

STATIC void
xfs_attwd_item_size(
	stwuct xfs_wog_item		*wip,
	int				*nvecs,
	int				*nbytes)
{
	*nvecs += 1;
	*nbytes += sizeof(stwuct xfs_attwd_wog_fowmat);
}

/*
 * This is cawwed to fiww in the wog iovecs fow the given attwd wog item. We use
 * onwy 1 iovec fow the attwd_fowmat, and we point that at the attw_wog_fowmat
 * stwuctuwe embedded in the attwd item.
 */
STATIC void
xfs_attwd_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_attwd_wog_item	*attwdp = ATTWD_ITEM(wip);
	stwuct xfs_wog_iovec		*vecp = NUWW;

	attwdp->attwd_fowmat.awfd_type = XFS_WI_ATTWD;
	attwdp->attwd_fowmat.awfd_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_ATTWD_FOWMAT,
			&attwdp->attwd_fowmat,
			sizeof(stwuct xfs_attwd_wog_fowmat));
}

/*
 * The ATTWD is eithew committed ow abowted if the twansaction is cancewed. If
 * the twansaction is cancewed, dwop ouw wefewence to the ATTWI and fwee the
 * ATTWD.
 */
STATIC void
xfs_attwd_item_wewease(
	stwuct xfs_wog_item		*wip)
{
	stwuct xfs_attwd_wog_item	*attwdp = ATTWD_ITEM(wip);

	xfs_attwi_wewease(attwdp->attwd_attwip);
	xfs_attwd_item_fwee(attwdp);
}

static stwuct xfs_wog_item *
xfs_attwd_item_intent(
	stwuct xfs_wog_item	*wip)
{
	wetuwn &ATTWD_ITEM(wip)->attwd_attwip->attwi_item;
}

/* Wog an attw to the intent item. */
STATIC void
xfs_attw_wog_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_attwi_wog_item	*attwip,
	const stwuct xfs_attw_intent	*attw)
{
	stwuct xfs_attwi_wog_fowmat	*attwp;

	/*
	 * At this point the xfs_attw_intent has been constwucted, and we've
	 * cweated the wog intent. Fiww in the attwi wog item and wog fowmat
	 * stwuctuwe with fiewds fwom this xfs_attw_intent
	 */
	attwp = &attwip->attwi_fowmat;
	attwp->awfi_ino = attw->xattwi_da_awgs->dp->i_ino;
	ASSEWT(!(attw->xattwi_op_fwags & ~XFS_ATTWI_OP_FWAGS_TYPE_MASK));
	attwp->awfi_op_fwags = attw->xattwi_op_fwags;
	attwp->awfi_vawue_wen = attw->xattwi_namevaw->vawue.i_wen;
	attwp->awfi_name_wen = attw->xattwi_namevaw->name.i_wen;
	ASSEWT(!(attw->xattwi_da_awgs->attw_fiwtew & ~XFS_ATTWI_FIWTEW_MASK));
	attwp->awfi_attw_fiwtew = attw->xattwi_da_awgs->attw_fiwtew;
}

/* Get an ATTWI. */
static stwuct xfs_wog_item *
xfs_attw_cweate_intent(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*items,
	unsigned int			count,
	boow				sowt)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_attwi_wog_item	*attwip;
	stwuct xfs_attw_intent		*attw;
	stwuct xfs_da_awgs		*awgs;

	ASSEWT(count == 1);

	/*
	 * Each attw item onwy pewfowms one attwibute opewation at a time, so
	 * this is a wist of one
	 */
	attw = wist_fiwst_entwy_ow_nuww(items, stwuct xfs_attw_intent,
			xattwi_wist);
	awgs = attw->xattwi_da_awgs;

	if (!(awgs->op_fwags & XFS_DA_OP_WOGGED))
		wetuwn NUWW;

	/*
	 * Cweate a buffew to stowe the attwibute name and vawue.  This buffew
	 * wiww be shawed between the highew wevew defewwed xattw wowk state
	 * and the wowew wevew xattw wog items.
	 */
	if (!attw->xattwi_namevaw) {
		/*
		 * Twansfew ouw wefewence to the name/vawue buffew to the
		 * defewwed wowk state stwuctuwe.
		 */
		attw->xattwi_namevaw = xfs_attwi_wog_namevaw_awwoc(awgs->name,
				awgs->namewen, awgs->vawue, awgs->vawuewen);
	}

	attwip = xfs_attwi_init(mp, attw->xattwi_namevaw);
	xfs_attw_wog_item(tp, attwip, attw);

	wetuwn &attwip->attwi_item;
}

static inwine void
xfs_attw_fwee_item(
	stwuct xfs_attw_intent		*attw)
{
	if (attw->xattwi_da_state)
		xfs_da_state_fwee(attw->xattwi_da_state);
	xfs_attwi_wog_namevaw_put(attw->xattwi_namevaw);
	if (attw->xattwi_da_awgs->op_fwags & XFS_DA_OP_WECOVEWY)
		kmem_fwee(attw);
	ewse
		kmem_cache_fwee(xfs_attw_intent_cache, attw);
}

/* Pwocess an attw. */
STATIC int
xfs_attw_finish_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*done,
	stwuct wist_head		*item,
	stwuct xfs_btwee_cuw		**state)
{
	stwuct xfs_attw_intent		*attw;
	stwuct xfs_da_awgs		*awgs;
	int				ewwow;

	attw = containew_of(item, stwuct xfs_attw_intent, xattwi_wist);
	awgs = attw->xattwi_da_awgs;

	/* Weset twans aftew EAGAIN cycwe since the twansaction is new */
	awgs->twans = tp;

	if (XFS_TEST_EWWOW(fawse, awgs->dp->i_mount, XFS_EWWTAG_WAWP)) {
		ewwow = -EIO;
		goto out;
	}

	/* If an attw wemovaw is twiviawwy compwete, we'we done. */
	if (attw->xattwi_op_fwags == XFS_ATTWI_OP_FWAGS_WEMOVE &&
	    !xfs_inode_hasattw(awgs->dp)) {
		ewwow = 0;
		goto out;
	}

	ewwow = xfs_attw_set_itew(attw);
	if (!ewwow && attw->xattwi_dewa_state != XFS_DAS_DONE)
		wetuwn -EAGAIN;

out:
	xfs_attw_fwee_item(attw);
	wetuwn ewwow;
}

/* Abowt aww pending ATTWs. */
STATIC void
xfs_attw_abowt_intent(
	stwuct xfs_wog_item		*intent)
{
	xfs_attwi_wewease(ATTWI_ITEM(intent));
}

/* Cancew an attw */
STATIC void
xfs_attw_cancew_item(
	stwuct wist_head		*item)
{
	stwuct xfs_attw_intent		*attw;

	attw = containew_of(item, stwuct xfs_attw_intent, xattwi_wist);
	xfs_attw_fwee_item(attw);
}

STATIC boow
xfs_attwi_item_match(
	stwuct xfs_wog_item	*wip,
	uint64_t		intent_id)
{
	wetuwn ATTWI_ITEM(wip)->attwi_fowmat.awfi_id == intent_id;
}

/* Is this wecovewed ATTWI fowmat ok? */
static inwine boow
xfs_attwi_vawidate(
	stwuct xfs_mount		*mp,
	stwuct xfs_attwi_wog_fowmat	*attwp)
{
	unsigned int			op = attwp->awfi_op_fwags &
					     XFS_ATTWI_OP_FWAGS_TYPE_MASK;

	if (attwp->__pad != 0)
		wetuwn fawse;

	if (attwp->awfi_op_fwags & ~XFS_ATTWI_OP_FWAGS_TYPE_MASK)
		wetuwn fawse;

	if (attwp->awfi_attw_fiwtew & ~XFS_ATTWI_FIWTEW_MASK)
		wetuwn fawse;

	/* awfi_op_fwags shouwd be eithew a set ow wemove */
	switch (op) {
	case XFS_ATTWI_OP_FWAGS_SET:
	case XFS_ATTWI_OP_FWAGS_WEPWACE:
	case XFS_ATTWI_OP_FWAGS_WEMOVE:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (attwp->awfi_vawue_wen > XATTW_SIZE_MAX)
		wetuwn fawse;

	if ((attwp->awfi_name_wen > XATTW_NAME_MAX) ||
	    (attwp->awfi_name_wen == 0))
		wetuwn fawse;

	wetuwn xfs_vewify_ino(mp, attwp->awfi_ino);
}

static inwine stwuct xfs_attw_intent *
xfs_attwi_wecovew_wowk(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp,
	stwuct xfs_attwi_wog_fowmat	*attwp,
	stwuct xfs_inode		**ipp,
	stwuct xfs_attwi_wog_namevaw	*nv)
{
	stwuct xfs_attw_intent		*attw;
	stwuct xfs_da_awgs		*awgs;
	int				wocaw;
	int				ewwow;

	ewwow = xwog_wecovew_iget(mp,  attwp->awfi_ino, ipp);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	attw = kmem_zawwoc(sizeof(stwuct xfs_attw_intent) +
			   sizeof(stwuct xfs_da_awgs), KM_NOFS);
	awgs = (stwuct xfs_da_awgs *)(attw + 1);

	attw->xattwi_da_awgs = awgs;
	attw->xattwi_op_fwags = attwp->awfi_op_fwags &
						XFS_ATTWI_OP_FWAGS_TYPE_MASK;

	/*
	 * We'we weconstwucting the defewwed wowk state stwuctuwe fwom the
	 * wecovewed wog item.  Gwab a wefewence to the name/vawue buffew and
	 * attach it to the new wowk state.
	 */
	attw->xattwi_namevaw = xfs_attwi_wog_namevaw_get(nv);
	ASSEWT(attw->xattwi_namevaw);

	awgs->dp = *ipp;
	awgs->geo = mp->m_attw_geo;
	awgs->whichfowk = XFS_ATTW_FOWK;
	awgs->name = nv->name.i_addw;
	awgs->namewen = nv->name.i_wen;
	awgs->hashvaw = xfs_da_hashname(awgs->name, awgs->namewen);
	awgs->attw_fiwtew = attwp->awfi_attw_fiwtew & XFS_ATTWI_FIWTEW_MASK;
	awgs->op_fwags = XFS_DA_OP_WECOVEWY | XFS_DA_OP_OKNOENT |
			 XFS_DA_OP_WOGGED;

	ASSEWT(xfs_sb_vewsion_haswogxattws(&mp->m_sb));

	switch (attw->xattwi_op_fwags) {
	case XFS_ATTWI_OP_FWAGS_SET:
	case XFS_ATTWI_OP_FWAGS_WEPWACE:
		awgs->vawue = nv->vawue.i_addw;
		awgs->vawuewen = nv->vawue.i_wen;
		awgs->totaw = xfs_attw_cawc_size(awgs, &wocaw);
		if (xfs_inode_hasattw(awgs->dp))
			attw->xattwi_dewa_state = xfs_attw_init_wepwace_state(awgs);
		ewse
			attw->xattwi_dewa_state = xfs_attw_init_add_state(awgs);
		bweak;
	case XFS_ATTWI_OP_FWAGS_WEMOVE:
		attw->xattwi_dewa_state = xfs_attw_init_wemove_state(awgs);
		bweak;
	}

	xfs_defew_add_item(dfp, &attw->xattwi_wist);
	wetuwn attw;
}

/*
 * Pwocess an attw intent item that was wecovewed fwom the wog.  We need to
 * dewete the attw that it descwibes.
 */
STATIC int
xfs_attw_wecovew_wowk(
	stwuct xfs_defew_pending	*dfp,
	stwuct wist_head		*captuwe_wist)
{
	stwuct xfs_wog_item		*wip = dfp->dfp_intent;
	stwuct xfs_attwi_wog_item	*attwip = ATTWI_ITEM(wip);
	stwuct xfs_attw_intent		*attw;
	stwuct xfs_mount		*mp = wip->wi_wog->w_mp;
	stwuct xfs_inode		*ip;
	stwuct xfs_da_awgs		*awgs;
	stwuct xfs_twans		*tp;
	stwuct xfs_twans_wes		wesv;
	stwuct xfs_attwi_wog_fowmat	*attwp;
	stwuct xfs_attwi_wog_namevaw	*nv = attwip->attwi_namevaw;
	int				ewwow;
	int				totaw;

	/*
	 * Fiwst check the vawidity of the attw descwibed by the ATTWI.  If any
	 * awe bad, then assume that aww awe bad and just toss the ATTWI.
	 */
	attwp = &attwip->attwi_fowmat;
	if (!xfs_attwi_vawidate(mp, attwp) ||
	    !xfs_attw_namecheck(nv->name.i_addw, nv->name.i_wen))
		wetuwn -EFSCOWWUPTED;

	attw = xfs_attwi_wecovew_wowk(mp, dfp, attwp, &ip, nv);
	if (IS_EWW(attw))
		wetuwn PTW_EWW(attw);
	awgs = attw->xattwi_da_awgs;

	xfs_init_attw_twans(awgs, &wesv, &totaw);
	wesv = xwog_wecovew_wesv(&wesv);
	ewwow = xfs_twans_awwoc(mp, &wesv, totaw, 0, XFS_TWANS_WESEWVE, &tp);
	if (ewwow)
		wetuwn ewwow;
	awgs->twans = tp;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	ewwow = xwog_wecovew_finish_intent(tp, dfp);
	if (ewwow == -EFSCOWWUPTED)
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				&attwip->attwi_fowmat,
				sizeof(attwip->attwi_fowmat));
	if (ewwow) {
		xfs_twans_cancew(tp);
		goto out_unwock;
	}

	ewwow = xfs_defew_ops_captuwe_and_commit(tp, captuwe_wist);
out_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	xfs_iwewe(ip);
	wetuwn ewwow;
}

/* We-wog an intent item to push the wog taiw fowwawd. */
static stwuct xfs_wog_item *
xfs_attw_wewog_intent(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	stwuct xfs_wog_item		*done_item)
{
	stwuct xfs_attwi_wog_item	*owd_attwip;
	stwuct xfs_attwi_wog_item	*new_attwip;
	stwuct xfs_attwi_wog_fowmat	*new_attwp;
	stwuct xfs_attwi_wog_fowmat	*owd_attwp;

	owd_attwip = ATTWI_ITEM(intent);
	owd_attwp = &owd_attwip->attwi_fowmat;

	/*
	 * Cweate a new wog item that shawes the same name/vawue buffew as the
	 * owd wog item.
	 */
	new_attwip = xfs_attwi_init(tp->t_mountp, owd_attwip->attwi_namevaw);
	new_attwp = &new_attwip->attwi_fowmat;

	new_attwp->awfi_ino = owd_attwp->awfi_ino;
	new_attwp->awfi_op_fwags = owd_attwp->awfi_op_fwags;
	new_attwp->awfi_vawue_wen = owd_attwp->awfi_vawue_wen;
	new_attwp->awfi_name_wen = owd_attwp->awfi_name_wen;
	new_attwp->awfi_attw_fiwtew = owd_attwp->awfi_attw_fiwtew;

	wetuwn &new_attwip->attwi_item;
}

/* Get an ATTWD so we can pwocess aww the attws. */
static stwuct xfs_wog_item *
xfs_attw_cweate_done(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	unsigned int			count)
{
	stwuct xfs_attwi_wog_item	*attwip;
	stwuct xfs_attwd_wog_item	*attwdp;

	attwip = ATTWI_ITEM(intent);

	attwdp = kmem_cache_zawwoc(xfs_attwd_cache, GFP_NOFS | __GFP_NOFAIW);

	xfs_wog_item_init(tp->t_mountp, &attwdp->attwd_item, XFS_WI_ATTWD,
			  &xfs_attwd_item_ops);
	attwdp->attwd_attwip = attwip;
	attwdp->attwd_fowmat.awfd_awf_id = attwip->attwi_fowmat.awfi_id;

	wetuwn &attwdp->attwd_item;
}

const stwuct xfs_defew_op_type xfs_attw_defew_type = {
	.name		= "attw",
	.max_items	= 1,
	.cweate_intent	= xfs_attw_cweate_intent,
	.abowt_intent	= xfs_attw_abowt_intent,
	.cweate_done	= xfs_attw_cweate_done,
	.finish_item	= xfs_attw_finish_item,
	.cancew_item	= xfs_attw_cancew_item,
	.wecovew_wowk	= xfs_attw_wecovew_wowk,
	.wewog_intent	= xfs_attw_wewog_intent,
};

STATIC int
xwog_wecovew_attwi_commit_pass2(
	stwuct xwog                     *wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item        *item,
	xfs_wsn_t                       wsn)
{
	stwuct xfs_mount                *mp = wog->w_mp;
	stwuct xfs_attwi_wog_item       *attwip;
	stwuct xfs_attwi_wog_fowmat     *attwi_fowmatp;
	stwuct xfs_attwi_wog_namevaw	*nv;
	const void			*attw_vawue = NUWW;
	const void			*attw_name;
	size_t				wen;

	attwi_fowmatp = item->wi_buf[0].i_addw;
	attw_name = item->wi_buf[1].i_addw;

	/* Vawidate xfs_attwi_wog_fowmat befowe the wawge memowy awwocation */
	wen = sizeof(stwuct xfs_attwi_wog_fowmat);
	if (item->wi_buf[0].i_wen != wen) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	if (!xfs_attwi_vawidate(mp, attwi_fowmatp)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	/* Vawidate the attw name */
	if (item->wi_buf[1].i_wen !=
			xwog_cawc_iovec_wen(attwi_fowmatp->awfi_name_wen)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	if (!xfs_attw_namecheck(attw_name, attwi_fowmatp->awfi_name_wen)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[1].i_addw, item->wi_buf[1].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	/* Vawidate the attw vawue, if pwesent */
	if (attwi_fowmatp->awfi_vawue_wen != 0) {
		if (item->wi_buf[2].i_wen != xwog_cawc_iovec_wen(attwi_fowmatp->awfi_vawue_wen)) {
			XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
					item->wi_buf[0].i_addw,
					item->wi_buf[0].i_wen);
			wetuwn -EFSCOWWUPTED;
		}

		attw_vawue = item->wi_buf[2].i_addw;
	}

	/*
	 * Memowy awwoc faiwuwe wiww cause wepway to abowt.  We attach the
	 * name/vawue buffew to the wecovewed incowe wog item and dwop ouw
	 * wefewence.
	 */
	nv = xfs_attwi_wog_namevaw_awwoc(attw_name,
			attwi_fowmatp->awfi_name_wen, attw_vawue,
			attwi_fowmatp->awfi_vawue_wen);

	attwip = xfs_attwi_init(mp, nv);
	memcpy(&attwip->attwi_fowmat, attwi_fowmatp, wen);

	xwog_wecovew_intent_item(wog, &attwip->attwi_item, wsn,
			&xfs_attw_defew_type);
	xfs_attwi_wog_namevaw_put(nv);
	wetuwn 0;
}

/*
 * This woutine is cawwed when an ATTWD fowmat stwuctuwe is found in a committed
 * twansaction in the wog. Its puwpose is to cancew the cowwesponding ATTWI if
 * it was stiww in the wog. To do this it seawches the AIW fow the ATTWI with
 * an id equaw to that in the ATTWD fowmat stwuctuwe. If we find it we dwop
 * the ATTWD wefewence, which wemoves the ATTWI fwom the AIW and fwees it.
 */
STATIC int
xwog_wecovew_attwd_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_attwd_wog_fowmat	*attwd_fowmatp;

	attwd_fowmatp = item->wi_buf[0].i_addw;
	if (item->wi_buf[0].i_wen != sizeof(stwuct xfs_attwd_wog_fowmat)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, wog->w_mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	xwog_wecovew_wewease_intent(wog, XFS_WI_ATTWI,
				    attwd_fowmatp->awfd_awf_id);
	wetuwn 0;
}

static const stwuct xfs_item_ops xfs_attwi_item_ops = {
	.fwags		= XFS_ITEM_INTENT,
	.iop_size	= xfs_attwi_item_size,
	.iop_fowmat	= xfs_attwi_item_fowmat,
	.iop_unpin	= xfs_attwi_item_unpin,
	.iop_wewease    = xfs_attwi_item_wewease,
	.iop_match	= xfs_attwi_item_match,
};

const stwuct xwog_wecovew_item_ops xwog_attwi_item_ops = {
	.item_type	= XFS_WI_ATTWI,
	.commit_pass2	= xwog_wecovew_attwi_commit_pass2,
};

static const stwuct xfs_item_ops xfs_attwd_item_ops = {
	.fwags		= XFS_ITEM_WEWEASE_WHEN_COMMITTED |
			  XFS_ITEM_INTENT_DONE,
	.iop_size	= xfs_attwd_item_size,
	.iop_fowmat	= xfs_attwd_item_fowmat,
	.iop_wewease    = xfs_attwd_item_wewease,
	.iop_intent	= xfs_attwd_item_intent,
};

const stwuct xwog_wecovew_item_ops xwog_attwd_item_ops = {
	.item_type	= XFS_WI_ATTWD,
	.commit_pass2	= xwog_wecovew_attwd_commit_pass2,
};
