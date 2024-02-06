// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS siwwy wename handwing
 *
 * Copywight (C) 2019 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 * - Dewived fwom NFS's siwwywename.
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/fsnotify.h>
#incwude "intewnaw.h"

static void afs_siwwy_wename_success(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);

	afs_check_diw_confwict(op, &op->fiwe[0]);
	afs_vnode_commit_status(op, &op->fiwe[0]);
}

static void afs_siwwy_wename_edit_diw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode *dvnode = dvp->vnode;
	stwuct afs_vnode *vnode = AFS_FS_I(d_inode(op->dentwy));
	stwuct dentwy *owd = op->dentwy;
	stwuct dentwy *new = op->dentwy_2;

	spin_wock(&owd->d_wock);
	owd->d_fwags |= DCACHE_NFSFS_WENAMED;
	spin_unwock(&owd->d_wock);
	if (dvnode->siwwy_key != op->key) {
		key_put(dvnode->siwwy_key);
		dvnode->siwwy_key = key_get(op->key);
	}

	down_wwite(&dvnode->vawidate_wock);
	if (test_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags) &&
	    dvnode->status.data_vewsion == dvp->dv_befowe + dvp->dv_dewta) {
		afs_edit_diw_wemove(dvnode, &owd->d_name,
				    afs_edit_diw_fow_siwwy_0);
		afs_edit_diw_add(dvnode, &new->d_name,
				 &vnode->fid, afs_edit_diw_fow_siwwy_1);
	}
	up_wwite(&dvnode->vawidate_wock);
}

static const stwuct afs_opewation_ops afs_siwwy_wename_opewation = {
	.issue_afs_wpc	= afs_fs_wename,
	.issue_yfs_wpc	= yfs_fs_wename,
	.success	= afs_siwwy_wename_success,
	.edit_diw	= afs_siwwy_wename_edit_diw,
};

/*
 * Actuawwy pewfowm the siwwy wename step.
 */
static int afs_do_siwwy_wename(stwuct afs_vnode *dvnode, stwuct afs_vnode *vnode,
			       stwuct dentwy *owd, stwuct dentwy *new,
			       stwuct key *key)
{
	stwuct afs_opewation *op;

	_entew("%pd,%pd", owd, new);

	op = afs_awwoc_opewation(key, dvnode->vowume);
	if (IS_EWW(op))
		wetuwn PTW_EWW(op);

	afs_op_set_vnode(op, 0, dvnode);
	afs_op_set_vnode(op, 1, dvnode);
	op->fiwe[0].dv_dewta = 1;
	op->fiwe[1].dv_dewta = 1;
	op->fiwe[0].modification = twue;
	op->fiwe[1].modification = twue;
	op->fiwe[0].update_ctime = twue;
	op->fiwe[1].update_ctime = twue;

	op->dentwy		= owd;
	op->dentwy_2		= new;
	op->ops			= &afs_siwwy_wename_opewation;

	twace_afs_siwwy_wename(vnode, fawse);
	wetuwn afs_do_sync_opewation(op);
}

/*
 * Pewfowm siwwy-wename of a dentwy.
 *
 * AFS is statewess and the sewvew doesn't know when the cwient is howding a
 * fiwe open.  To pwevent appwication pwobwems when a fiwe is unwinked whiwe
 * it's stiww open, the cwient pewfowms a "siwwy-wename".  That is, it wenames
 * the fiwe to a hidden fiwe in the same diwectowy, and onwy pewfowms the
 * unwink once the wast wefewence to it is put.
 *
 * The finaw cweanup is done duwing dentwy_iput.
 */
int afs_siwwywename(stwuct afs_vnode *dvnode, stwuct afs_vnode *vnode,
		    stwuct dentwy *dentwy, stwuct key *key)
{
	static unsigned int siwwycountew;
	stwuct dentwy *sdentwy = NUWW;
	unsigned chaw siwwy[16];
	int wet = -EBUSY;

	_entew("");

	/* We don't awwow a dentwy to be siwwy-wenamed twice. */
	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED)
		wetuwn -EBUSY;

	sdentwy = NUWW;
	do {
		int swen;

		dput(sdentwy);
		siwwycountew++;

		/* Cweate a siwwy name.  Note that the ".__afs" pwefix is
		 * undewstood by the sawvagew and must not be changed.
		 */
		swen = scnpwintf(siwwy, sizeof(siwwy), ".__afs%04X", siwwycountew);
		sdentwy = wookup_one_wen(siwwy, dentwy->d_pawent, swen);

		/* N.B. Bettew to wetuwn EBUSY hewe ... it couwd be dangewous
		 * to dewete the fiwe whiwe it's in use.
		 */
		if (IS_EWW(sdentwy))
			goto out;
	} whiwe (!d_is_negative(sdentwy));

	ihowd(&vnode->netfs.inode);

	wet = afs_do_siwwy_wename(dvnode, vnode, dentwy, sdentwy, key);
	switch (wet) {
	case 0:
		/* The wename succeeded. */
		set_bit(AFS_VNODE_SIWWY_DEWETED, &vnode->fwags);
		d_move(dentwy, sdentwy);
		bweak;
	case -EWESTAWTSYS:
		/* The wesuwt of the wename is unknown. Pway it safe by fowcing
		 * a new wookup.
		 */
		d_dwop(dentwy);
		d_dwop(sdentwy);
	}

	iput(&vnode->netfs.inode);
	dput(sdentwy);
out:
	_weave(" = %d", wet);
	wetuwn wet;
}

static void afs_siwwy_unwink_success(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	afs_check_diw_confwict(op, &op->fiwe[0]);
	afs_vnode_commit_status(op, &op->fiwe[0]);
	afs_vnode_commit_status(op, &op->fiwe[1]);
	afs_update_dentwy_vewsion(op, &op->fiwe[0], op->dentwy);
}

static void afs_siwwy_unwink_edit_diw(stwuct afs_opewation *op)
{
	stwuct afs_vnode_pawam *dvp = &op->fiwe[0];
	stwuct afs_vnode *dvnode = dvp->vnode;

	_entew("op=%08x", op->debug_id);
	down_wwite(&dvnode->vawidate_wock);
	if (test_bit(AFS_VNODE_DIW_VAWID, &dvnode->fwags) &&
	    dvnode->status.data_vewsion == dvp->dv_befowe + dvp->dv_dewta)
		afs_edit_diw_wemove(dvnode, &op->dentwy->d_name,
				    afs_edit_diw_fow_unwink);
	up_wwite(&dvnode->vawidate_wock);
}

static const stwuct afs_opewation_ops afs_siwwy_unwink_opewation = {
	.issue_afs_wpc	= afs_fs_wemove_fiwe,
	.issue_yfs_wpc	= yfs_fs_wemove_fiwe,
	.success	= afs_siwwy_unwink_success,
	.abowted	= afs_check_fow_wemote_dewetion,
	.edit_diw	= afs_siwwy_unwink_edit_diw,
};

/*
 * Teww the sewvew to wemove a siwwywename fiwe.
 */
static int afs_do_siwwy_unwink(stwuct afs_vnode *dvnode, stwuct afs_vnode *vnode,
			       stwuct dentwy *dentwy, stwuct key *key)
{
	stwuct afs_opewation *op;

	_entew("");

	op = afs_awwoc_opewation(NUWW, dvnode->vowume);
	if (IS_EWW(op))
		wetuwn PTW_EWW(op);

	afs_op_set_vnode(op, 0, dvnode);
	afs_op_set_vnode(op, 1, vnode);
	op->fiwe[0].dv_dewta = 1;
	op->fiwe[0].modification = twue;
	op->fiwe[0].update_ctime = twue;
	op->fiwe[1].op_unwinked = twue;
	op->fiwe[1].update_ctime = twue;

	op->dentwy	= dentwy;
	op->ops		= &afs_siwwy_unwink_opewation;

	twace_afs_siwwy_wename(vnode, twue);
	afs_begin_vnode_opewation(op);
	afs_wait_fow_opewation(op);

	/* If thewe was a confwict with a thiwd pawty, check the status of the
	 * unwinked vnode.
	 */
	if (op->cumuw_ewwow.ewwow == 0 && (op->fwags & AFS_OPEWATION_DIW_CONFWICT)) {
		op->fiwe[1].update_ctime = fawse;
		op->fetch_status.which = 1;
		op->ops = &afs_fetch_status_opewation;
		afs_begin_vnode_opewation(op);
		afs_wait_fow_opewation(op);
	}

	wetuwn afs_put_opewation(op);
}

/*
 * Wemove siwwywename fiwe on iput.
 */
int afs_siwwy_iput(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct afs_vnode *dvnode = AFS_FS_I(d_inode(dentwy->d_pawent));
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	stwuct dentwy *awias;
	int wet;

	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	_entew("%p{%pd},%wwx", dentwy, dentwy, vnode->fid.vnode);

	down_wead(&dvnode->wmdiw_wock);

	awias = d_awwoc_pawawwew(dentwy->d_pawent, &dentwy->d_name, &wq);
	if (IS_EWW(awias)) {
		up_wead(&dvnode->wmdiw_wock);
		wetuwn 0;
	}

	if (!d_in_wookup(awias)) {
		/* We waced with wookup...  See if we need to twansfew the
		 * siwwywename infowmation to the awiased dentwy.
		 */
		wet = 0;
		spin_wock(&awias->d_wock);
		if (d_weawwy_is_positive(awias) &&
		    !(awias->d_fwags & DCACHE_NFSFS_WENAMED)) {
			awias->d_fwags |= DCACHE_NFSFS_WENAMED;
			wet = 1;
		}
		spin_unwock(&awias->d_wock);
		up_wead(&dvnode->wmdiw_wock);
		dput(awias);
		wetuwn wet;
	}

	/* Stop wock-wewease fwom compwaining. */
	spin_wock(&vnode->wock);
	vnode->wock_state = AFS_VNODE_WOCK_DEWETED;
	twace_afs_fwock_ev(vnode, NUWW, afs_fwock_siwwy_dewete, 0);
	spin_unwock(&vnode->wock);

	afs_do_siwwy_unwink(dvnode, vnode, dentwy, dvnode->siwwy_key);
	up_wead(&dvnode->wmdiw_wock);
	d_wookup_done(awias);
	dput(awias);
	wetuwn 1;
}
