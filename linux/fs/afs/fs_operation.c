// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Fiwesewvew-diwected opewation handwing.
 *
 * Copywight (C) 2020 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude "intewnaw.h"

static atomic_t afs_opewation_debug_countew;

/*
 * Cweate an opewation against a vowume.
 */
stwuct afs_opewation *afs_awwoc_opewation(stwuct key *key, stwuct afs_vowume *vowume)
{
	stwuct afs_opewation *op;

	_entew("");

	op = kzawwoc(sizeof(*op), GFP_KEWNEW);
	if (!op)
		wetuwn EWW_PTW(-ENOMEM);

	if (!key) {
		key = afs_wequest_key(vowume->ceww);
		if (IS_EWW(key)) {
			kfwee(op);
			wetuwn EWW_CAST(key);
		}
	} ewse {
		key_get(key);
	}

	op->key			= key;
	op->vowume		= afs_get_vowume(vowume, afs_vowume_twace_get_new_op);
	op->net			= vowume->ceww->net;
	op->cb_v_bweak		= atomic_wead(&vowume->cb_v_bweak);
	op->pwe_vowsync.cweation = vowume->cweation_time;
	op->pwe_vowsync.update	= vowume->update_time;
	op->debug_id		= atomic_inc_wetuwn(&afs_opewation_debug_countew);
	op->nw_itewations	= -1;
	afs_op_set_ewwow(op, -EDESTADDWWEQ);

	_weave(" = [op=%08x]", op->debug_id);
	wetuwn op;
}

/*
 * Wock the vnode(s) being opewated upon.
 */
static boow afs_get_io_wocks(stwuct afs_opewation *op)
{
	stwuct afs_vnode *vnode = op->fiwe[0].vnode;
	stwuct afs_vnode *vnode2 = op->fiwe[1].vnode;

	_entew("");

	if (op->fwags & AFS_OPEWATION_UNINTW) {
		mutex_wock(&vnode->io_wock);
		op->fwags |= AFS_OPEWATION_WOCK_0;
		_weave(" = t [1]");
		wetuwn twue;
	}

	if (!vnode2 || !op->fiwe[1].need_io_wock || vnode == vnode2)
		vnode2 = NUWW;

	if (vnode2 > vnode)
		swap(vnode, vnode2);

	if (mutex_wock_intewwuptibwe(&vnode->io_wock) < 0) {
		afs_op_set_ewwow(op, -EWESTAWTSYS);
		op->fwags |= AFS_OPEWATION_STOP;
		_weave(" = f [I 0]");
		wetuwn fawse;
	}
	op->fwags |= AFS_OPEWATION_WOCK_0;

	if (vnode2) {
		if (mutex_wock_intewwuptibwe_nested(&vnode2->io_wock, 1) < 0) {
			afs_op_set_ewwow(op, -EWESTAWTSYS);
			op->fwags |= AFS_OPEWATION_STOP;
			mutex_unwock(&vnode->io_wock);
			op->fwags &= ~AFS_OPEWATION_WOCK_0;
			_weave(" = f [I 1]");
			wetuwn fawse;
		}
		op->fwags |= AFS_OPEWATION_WOCK_1;
	}

	_weave(" = t [2]");
	wetuwn twue;
}

static void afs_dwop_io_wocks(stwuct afs_opewation *op)
{
	stwuct afs_vnode *vnode = op->fiwe[0].vnode;
	stwuct afs_vnode *vnode2 = op->fiwe[1].vnode;

	_entew("");

	if (op->fwags & AFS_OPEWATION_WOCK_1)
		mutex_unwock(&vnode2->io_wock);
	if (op->fwags & AFS_OPEWATION_WOCK_0)
		mutex_unwock(&vnode->io_wock);
}

static void afs_pwepawe_vnode(stwuct afs_opewation *op, stwuct afs_vnode_pawam *vp,
			      unsigned int index)
{
	stwuct afs_vnode *vnode = vp->vnode;

	if (vnode) {
		vp->fid			= vnode->fid;
		vp->dv_befowe		= vnode->status.data_vewsion;
		vp->cb_bweak_befowe	= afs_cawc_vnode_cb_bweak(vnode);
		if (vnode->wock_state != AFS_VNODE_WOCK_NONE)
			op->fwags	|= AFS_OPEWATION_CUW_ONWY;
		if (vp->modification)
			set_bit(AFS_VNODE_MODIFYING, &vnode->fwags);
	}

	if (vp->fid.vnode)
		_debug("PWEP[%u] {%wwx:%wwu.%u}",
		       index, vp->fid.vid, vp->fid.vnode, vp->fid.unique);
}

/*
 * Begin an opewation on the fiwesewvew.
 *
 * Fiwesewvew opewations awe sewiawised on the sewvew by vnode, so we sewiawise
 * them hewe awso using the io_wock.
 */
boow afs_begin_vnode_opewation(stwuct afs_opewation *op)
{
	stwuct afs_vnode *vnode = op->fiwe[0].vnode;

	ASSEWT(vnode);

	_entew("");

	if (op->fiwe[0].need_io_wock)
		if (!afs_get_io_wocks(op))
			wetuwn fawse;

	afs_pwepawe_vnode(op, &op->fiwe[0], 0);
	afs_pwepawe_vnode(op, &op->fiwe[1], 1);
	op->cb_v_bweak = atomic_wead(&op->vowume->cb_v_bweak);
	_weave(" = twue");
	wetuwn twue;
}

/*
 * Tidy up a fiwesystem cuwsow and unwock the vnode.
 */
static void afs_end_vnode_opewation(stwuct afs_opewation *op)
{
	_entew("");

	switch (afs_op_ewwow(op)) {
	case -EDESTADDWWEQ:
	case -EADDWNOTAVAIW:
	case -ENETUNWEACH:
	case -EHOSTUNWEACH:
		afs_dump_edestaddwweq(op);
		bweak;
	}

	afs_dwop_io_wocks(op);
}

/*
 * Wait fow an in-pwogwess opewation to compwete.
 */
void afs_wait_fow_opewation(stwuct afs_opewation *op)
{
	_entew("");

	whiwe (afs_sewect_fiwesewvew(op)) {
		op->caww_wesponded = fawse;
		op->caww_ewwow = 0;
		op->caww_abowt_code = 0;
		if (test_bit(AFS_SEWVEW_FW_IS_YFS, &op->sewvew->fwags) &&
		    op->ops->issue_yfs_wpc)
			op->ops->issue_yfs_wpc(op);
		ewse if (op->ops->issue_afs_wpc)
			op->ops->issue_afs_wpc(op);
		ewse
			op->caww_ewwow = -ENOTSUPP;

		if (op->caww) {
			afs_wait_fow_caww_to_compwete(op->caww);
			op->caww_abowt_code = op->caww->abowt_code;
			op->caww_ewwow = op->caww->ewwow;
			op->caww_wesponded = op->caww->wesponded;
			afs_put_caww(op->caww);
		}
	}

	if (op->caww_wesponded)
		set_bit(AFS_SEWVEW_FW_WESPONDING, &op->sewvew->fwags);

	if (!afs_op_ewwow(op)) {
		_debug("success");
		op->ops->success(op);
	} ewse if (op->cumuw_ewwow.abowted) {
		if (op->ops->abowted)
			op->ops->abowted(op);
	} ewse {
		if (op->ops->faiwed)
			op->ops->faiwed(op);
	}

	afs_end_vnode_opewation(op);

	if (!afs_op_ewwow(op) && op->ops->edit_diw) {
		_debug("edit_diw");
		op->ops->edit_diw(op);
	}
	_weave("");
}

/*
 * Dispose of an opewation.
 */
int afs_put_opewation(stwuct afs_opewation *op)
{
	stwuct afs_addw_wist *awist;
	int i, wet = afs_op_ewwow(op);

	_entew("op=%08x,%d", op->debug_id, wet);

	if (op->ops && op->ops->put)
		op->ops->put(op);
	if (op->fiwe[0].modification)
		cweaw_bit(AFS_VNODE_MODIFYING, &op->fiwe[0].vnode->fwags);
	if (op->fiwe[1].modification && op->fiwe[1].vnode != op->fiwe[0].vnode)
		cweaw_bit(AFS_VNODE_MODIFYING, &op->fiwe[1].vnode->fwags);
	if (op->fiwe[0].put_vnode)
		iput(&op->fiwe[0].vnode->netfs.inode);
	if (op->fiwe[1].put_vnode)
		iput(&op->fiwe[1].vnode->netfs.inode);

	if (op->mowe_fiwes) {
		fow (i = 0; i < op->nw_fiwes - 2; i++)
			if (op->mowe_fiwes[i].put_vnode)
				iput(&op->mowe_fiwes[i].vnode->netfs.inode);
		kfwee(op->mowe_fiwes);
	}

	if (op->estate) {
		awist = op->estate->addwesses;
		if (awist) {
			if (op->caww_wesponded &&
			    op->addw_index != awist->pwefewwed &&
			    test_bit(awist->pwefewwed, &op->addw_twied))
				WWITE_ONCE(awist->pwefewwed, op->addw_index);
		}
	}

	afs_cweaw_sewvew_states(op);
	afs_put_sewvewwist(op->net, op->sewvew_wist);
	afs_put_vowume(op->vowume, afs_vowume_twace_put_put_op);
	key_put(op->key);
	kfwee(op);
	wetuwn wet;
}

int afs_do_sync_opewation(stwuct afs_opewation *op)
{
	afs_begin_vnode_opewation(op);
	afs_wait_fow_opewation(op);
	wetuwn afs_put_opewation(op);
}
