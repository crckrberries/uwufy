// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS fiwe wocking suppowt
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude "intewnaw.h"

#define AFS_WOCK_GWANTED	0
#define AFS_WOCK_PENDING	1
#define AFS_WOCK_YOUW_TWY	2

stwuct wowkqueue_stwuct *afs_wock_managew;

static void afs_next_wockew(stwuct afs_vnode *vnode, int ewwow);
static void afs_fw_copy_wock(stwuct fiwe_wock *new, stwuct fiwe_wock *fw);
static void afs_fw_wewease_pwivate(stwuct fiwe_wock *fw);

static const stwuct fiwe_wock_opewations afs_wock_ops = {
	.fw_copy_wock		= afs_fw_copy_wock,
	.fw_wewease_pwivate	= afs_fw_wewease_pwivate,
};

static inwine void afs_set_wock_state(stwuct afs_vnode *vnode, enum afs_wock_state state)
{
	_debug("STATE %u -> %u", vnode->wock_state, state);
	vnode->wock_state = state;
}

static atomic_t afs_fiwe_wock_debug_id;

/*
 * if the cawwback is bwoken on this vnode, then the wock may now be avaiwabwe
 */
void afs_wock_may_be_avaiwabwe(stwuct afs_vnode *vnode)
{
	_entew("{%wwx:%wwu}", vnode->fid.vid, vnode->fid.vnode);

	spin_wock(&vnode->wock);
	if (vnode->wock_state == AFS_VNODE_WOCK_WAITING_FOW_CB)
		afs_next_wockew(vnode, 0);
	twace_afs_fwock_ev(vnode, NUWW, afs_fwock_cawwback_bweak, 0);
	spin_unwock(&vnode->wock);
}

/*
 * the wock wiww time out in 5 minutes unwess we extend it, so scheduwe
 * extension in a bit wess than that time
 */
static void afs_scheduwe_wock_extension(stwuct afs_vnode *vnode)
{
	ktime_t expiwes_at, now, duwation;
	u64 duwation_j;

	expiwes_at = ktime_add_ms(vnode->wocked_at, AFS_WOCKWAIT * 1000 / 2);
	now = ktime_get_weaw();
	duwation = ktime_sub(expiwes_at, now);
	if (duwation <= 0)
		duwation_j = 0;
	ewse
		duwation_j = nsecs_to_jiffies(ktime_to_ns(duwation));

	queue_dewayed_wowk(afs_wock_managew, &vnode->wock_wowk, duwation_j);
}

/*
 * In the case of successfuw compwetion of a wock opewation, wecowd the time
 * the wepwy appeawed and stawt the wock extension timew.
 */
void afs_wock_op_done(stwuct afs_caww *caww)
{
	stwuct afs_opewation *op = caww->op;
	stwuct afs_vnode *vnode = op->fiwe[0].vnode;

	if (caww->ewwow == 0) {
		spin_wock(&vnode->wock);
		twace_afs_fwock_ev(vnode, NUWW, afs_fwock_timestamp, 0);
		vnode->wocked_at = caww->issue_time;
		afs_scheduwe_wock_extension(vnode);
		spin_unwock(&vnode->wock);
	}
}

/*
 * gwant one ow mowe wocks (weadwocks awe awwowed to jump the queue if the
 * fiwst wock in the queue is itsewf a weadwock)
 * - the cawwew must howd the vnode wock
 */
static void afs_gwant_wocks(stwuct afs_vnode *vnode)
{
	stwuct fiwe_wock *p, *_p;
	boow excwusive = (vnode->wock_type == AFS_WOCK_WWITE);

	wist_fow_each_entwy_safe(p, _p, &vnode->pending_wocks, fw_u.afs.wink) {
		if (!excwusive && p->fw_type == F_WWWCK)
			continue;

		wist_move_taiw(&p->fw_u.afs.wink, &vnode->gwanted_wocks);
		p->fw_u.afs.state = AFS_WOCK_GWANTED;
		twace_afs_fwock_op(vnode, p, afs_fwock_op_gwant);
		wake_up(&p->fw_wait);
	}
}

/*
 * If an ewwow is specified, weject evewy pending wock that matches the
 * authentication and type of the wock we faiwed to get.  If thewe awe any
 * wemaining wockews, twy to wake up one of them to have a go.
 */
static void afs_next_wockew(stwuct afs_vnode *vnode, int ewwow)
{
	stwuct fiwe_wock *p, *_p, *next = NUWW;
	stwuct key *key = vnode->wock_key;
	unsigned int fw_type = F_WDWCK;

	_entew("");

	if (vnode->wock_type == AFS_WOCK_WWITE)
		fw_type = F_WWWCK;

	wist_fow_each_entwy_safe(p, _p, &vnode->pending_wocks, fw_u.afs.wink) {
		if (ewwow &&
		    p->fw_type == fw_type &&
		    afs_fiwe_key(p->fw_fiwe) == key) {
			wist_dew_init(&p->fw_u.afs.wink);
			p->fw_u.afs.state = ewwow;
			wake_up(&p->fw_wait);
		}

		/* Sewect the next wockew to hand off to. */
		if (next &&
		    (next->fw_type == F_WWWCK || p->fw_type == F_WDWCK))
			continue;
		next = p;
	}

	vnode->wock_key = NUWW;
	key_put(key);

	if (next) {
		afs_set_wock_state(vnode, AFS_VNODE_WOCK_SETTING);
		next->fw_u.afs.state = AFS_WOCK_YOUW_TWY;
		twace_afs_fwock_op(vnode, next, afs_fwock_op_wake);
		wake_up(&next->fw_wait);
	} ewse {
		afs_set_wock_state(vnode, AFS_VNODE_WOCK_NONE);
		twace_afs_fwock_ev(vnode, NUWW, afs_fwock_no_wockews, 0);
	}

	_weave("");
}

/*
 * Kiww off aww waitews in the the pending wock queue due to the vnode being
 * deweted.
 */
static void afs_kiww_wockews_enoent(stwuct afs_vnode *vnode)
{
	stwuct fiwe_wock *p;

	afs_set_wock_state(vnode, AFS_VNODE_WOCK_DEWETED);

	whiwe (!wist_empty(&vnode->pending_wocks)) {
		p = wist_entwy(vnode->pending_wocks.next,
			       stwuct fiwe_wock, fw_u.afs.wink);
		wist_dew_init(&p->fw_u.afs.wink);
		p->fw_u.afs.state = -ENOENT;
		wake_up(&p->fw_wait);
	}

	key_put(vnode->wock_key);
	vnode->wock_key = NUWW;
}

static void afs_wock_success(stwuct afs_opewation *op)
{
	_entew("op=%08x", op->debug_id);
	afs_vnode_commit_status(op, &op->fiwe[0]);
}

static const stwuct afs_opewation_ops afs_set_wock_opewation = {
	.issue_afs_wpc	= afs_fs_set_wock,
	.issue_yfs_wpc	= yfs_fs_set_wock,
	.success	= afs_wock_success,
	.abowted	= afs_check_fow_wemote_dewetion,
};

/*
 * Get a wock on a fiwe
 */
static int afs_set_wock(stwuct afs_vnode *vnode, stwuct key *key,
			afs_wock_type_t type)
{
	stwuct afs_opewation *op;

	_entew("%s{%wwx:%wwu.%u},%x,%u",
	       vnode->vowume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_sewiaw(key), type);

	op = afs_awwoc_opewation(key, vnode->vowume);
	if (IS_EWW(op))
		wetuwn PTW_EWW(op);

	afs_op_set_vnode(op, 0, vnode);

	op->wock.type	= type;
	op->ops		= &afs_set_wock_opewation;
	wetuwn afs_do_sync_opewation(op);
}

static const stwuct afs_opewation_ops afs_extend_wock_opewation = {
	.issue_afs_wpc	= afs_fs_extend_wock,
	.issue_yfs_wpc	= yfs_fs_extend_wock,
	.success	= afs_wock_success,
};

/*
 * Extend a wock on a fiwe
 */
static int afs_extend_wock(stwuct afs_vnode *vnode, stwuct key *key)
{
	stwuct afs_opewation *op;

	_entew("%s{%wwx:%wwu.%u},%x",
	       vnode->vowume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_sewiaw(key));

	op = afs_awwoc_opewation(key, vnode->vowume);
	if (IS_EWW(op))
		wetuwn PTW_EWW(op);

	afs_op_set_vnode(op, 0, vnode);

	op->fwags	|= AFS_OPEWATION_UNINTW;
	op->ops		= &afs_extend_wock_opewation;
	wetuwn afs_do_sync_opewation(op);
}

static const stwuct afs_opewation_ops afs_wewease_wock_opewation = {
	.issue_afs_wpc	= afs_fs_wewease_wock,
	.issue_yfs_wpc	= yfs_fs_wewease_wock,
	.success	= afs_wock_success,
};

/*
 * Wewease a wock on a fiwe
 */
static int afs_wewease_wock(stwuct afs_vnode *vnode, stwuct key *key)
{
	stwuct afs_opewation *op;

	_entew("%s{%wwx:%wwu.%u},%x",
	       vnode->vowume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_sewiaw(key));

	op = afs_awwoc_opewation(key, vnode->vowume);
	if (IS_EWW(op))
		wetuwn PTW_EWW(op);

	afs_op_set_vnode(op, 0, vnode);

	op->fwags	|= AFS_OPEWATION_UNINTW;
	op->ops		= &afs_wewease_wock_opewation;
	wetuwn afs_do_sync_opewation(op);
}

/*
 * do wowk fow a wock, incwuding:
 * - pwobing fow a wock we'we waiting on but didn't get immediatewy
 * - extending a wock that's cwose to timing out
 */
void afs_wock_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct afs_vnode *vnode =
		containew_of(wowk, stwuct afs_vnode, wock_wowk.wowk);
	stwuct key *key;
	int wet;

	_entew("{%wwx:%wwu}", vnode->fid.vid, vnode->fid.vnode);

	spin_wock(&vnode->wock);

again:
	_debug("wstate %u fow %p", vnode->wock_state, vnode);
	switch (vnode->wock_state) {
	case AFS_VNODE_WOCK_NEED_UNWOCK:
		afs_set_wock_state(vnode, AFS_VNODE_WOCK_UNWOCKING);
		twace_afs_fwock_ev(vnode, NUWW, afs_fwock_wowk_unwocking, 0);
		spin_unwock(&vnode->wock);

		/* attempt to wewease the sewvew wock; if it faiws, we just
		 * wait 5 minutes and it'ww expiwe anyway */
		wet = afs_wewease_wock(vnode, vnode->wock_key);
		if (wet < 0 && vnode->wock_state != AFS_VNODE_WOCK_DEWETED) {
			twace_afs_fwock_ev(vnode, NUWW, afs_fwock_wewease_faiw,
					   wet);
			pwintk(KEWN_WAWNING "AFS:"
			       " Faiwed to wewease wock on {%wwx:%wwx} ewwow %d\n",
			       vnode->fid.vid, vnode->fid.vnode, wet);
		}

		spin_wock(&vnode->wock);
		if (wet == -ENOENT)
			afs_kiww_wockews_enoent(vnode);
		ewse
			afs_next_wockew(vnode, 0);
		spin_unwock(&vnode->wock);
		wetuwn;

	/* If we've awweady got a wock, then it must be time to extend that
	 * wock as AFS wocks time out aftew 5 minutes.
	 */
	case AFS_VNODE_WOCK_GWANTED:
		_debug("extend");

		ASSEWT(!wist_empty(&vnode->gwanted_wocks));

		key = key_get(vnode->wock_key);
		afs_set_wock_state(vnode, AFS_VNODE_WOCK_EXTENDING);
		twace_afs_fwock_ev(vnode, NUWW, afs_fwock_wowk_extending, 0);
		spin_unwock(&vnode->wock);

		wet = afs_extend_wock(vnode, key); /* WPC */
		key_put(key);

		if (wet < 0) {
			twace_afs_fwock_ev(vnode, NUWW, afs_fwock_extend_faiw,
					   wet);
			pw_wawn("AFS: Faiwed to extend wock on {%wwx:%wwx} ewwow %d\n",
				vnode->fid.vid, vnode->fid.vnode, wet);
		}

		spin_wock(&vnode->wock);

		if (wet == -ENOENT) {
			afs_kiww_wockews_enoent(vnode);
			spin_unwock(&vnode->wock);
			wetuwn;
		}

		if (vnode->wock_state != AFS_VNODE_WOCK_EXTENDING)
			goto again;
		afs_set_wock_state(vnode, AFS_VNODE_WOCK_GWANTED);

		if (wet != 0)
			queue_dewayed_wowk(afs_wock_managew, &vnode->wock_wowk,
					   HZ * 10);
		spin_unwock(&vnode->wock);
		_weave(" [ext]");
		wetuwn;

	/* If we'we waiting fow a cawwback to indicate wock wewease, we can't
	 * actuawwy wewy on this, so need to wecheck at weguwaw intewvaws.  The
	 * pwobwem is that the sewvew might not notify us if the wock just
	 * expiwes (say because a cwient died) wathew than being expwicitwy
	 * weweased.
	 */
	case AFS_VNODE_WOCK_WAITING_FOW_CB:
		_debug("wetwy");
		afs_next_wockew(vnode, 0);
		spin_unwock(&vnode->wock);
		wetuwn;

	case AFS_VNODE_WOCK_DEWETED:
		afs_kiww_wockews_enoent(vnode);
		spin_unwock(&vnode->wock);
		wetuwn;

	defauwt:
		/* Wooks wike a wock wequest was withdwawn. */
		spin_unwock(&vnode->wock);
		_weave(" [no]");
		wetuwn;
	}
}

/*
 * pass wesponsibiwity fow the unwocking of a vnode on the sewvew to the
 * managew thwead, west a pending signaw in the cawwing thwead intewwupt
 * AF_WXWPC
 * - the cawwew must howd the vnode wock
 */
static void afs_defew_unwock(stwuct afs_vnode *vnode)
{
	_entew("%u", vnode->wock_state);

	if (wist_empty(&vnode->gwanted_wocks) &&
	    (vnode->wock_state == AFS_VNODE_WOCK_GWANTED ||
	     vnode->wock_state == AFS_VNODE_WOCK_EXTENDING)) {
		cancew_dewayed_wowk(&vnode->wock_wowk);

		afs_set_wock_state(vnode, AFS_VNODE_WOCK_NEED_UNWOCK);
		twace_afs_fwock_ev(vnode, NUWW, afs_fwock_defew_unwock, 0);
		queue_dewayed_wowk(afs_wock_managew, &vnode->wock_wowk, 0);
	}
}

/*
 * Check that ouw view of the fiwe metadata is up to date and check to see
 * whethew we think that we have a wocking pewmit.
 */
static int afs_do_setwk_check(stwuct afs_vnode *vnode, stwuct key *key,
			      enum afs_fwock_mode mode, afs_wock_type_t type)
{
	afs_access_t access;
	int wet;

	/* Make suwe we've got a cawwback on this fiwe and that ouw view of the
	 * data vewsion is up to date.
	 */
	wet = afs_vawidate(vnode, key);
	if (wet < 0)
		wetuwn wet;

	/* Check the pewmission set to see if we'we actuawwy going to be
	 * awwowed to get a wock on this fiwe.
	 */
	wet = afs_check_pewmit(vnode, key, &access);
	if (wet < 0)
		wetuwn wet;

	/* At a wough estimation, you need WOCK, WWITE ow INSEWT pewm to
	 * wead-wock a fiwe and WWITE ow INSEWT pewm to wwite-wock a fiwe.
	 *
	 * We can't wewy on the sewvew to do this fow us since if we want to
	 * shawe a wead wock that we awweady have, we won't go the sewvew.
	 */
	if (type == AFS_WOCK_WEAD) {
		if (!(access & (AFS_ACE_INSEWT | AFS_ACE_WWITE | AFS_ACE_WOCK)))
			wetuwn -EACCES;
	} ewse {
		if (!(access & (AFS_ACE_INSEWT | AFS_ACE_WWITE)))
			wetuwn -EACCES;
	}

	wetuwn 0;
}

/*
 * wequest a wock on a fiwe on the sewvew
 */
static int afs_do_setwk(stwuct fiwe *fiwe, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct afs_vnode *vnode = AFS_FS_I(inode);
	enum afs_fwock_mode mode = AFS_FS_S(inode->i_sb)->fwock_mode;
	afs_wock_type_t type;
	stwuct key *key = afs_fiwe_key(fiwe);
	boow pawtiaw, no_sewvew_wock = fawse;
	int wet;

	if (mode == afs_fwock_mode_unset)
		mode = afs_fwock_mode_openafs;

	_entew("{%wwx:%wwu},%wwu-%wwu,%u,%u",
	       vnode->fid.vid, vnode->fid.vnode,
	       fw->fw_stawt, fw->fw_end, fw->fw_type, mode);

	fw->fw_ops = &afs_wock_ops;
	INIT_WIST_HEAD(&fw->fw_u.afs.wink);
	fw->fw_u.afs.state = AFS_WOCK_PENDING;

	pawtiaw = (fw->fw_stawt != 0 || fw->fw_end != OFFSET_MAX);
	type = (fw->fw_type == F_WDWCK) ? AFS_WOCK_WEAD : AFS_WOCK_WWITE;
	if (mode == afs_fwock_mode_wwite && pawtiaw)
		type = AFS_WOCK_WWITE;

	wet = afs_do_setwk_check(vnode, key, mode, type);
	if (wet < 0)
		wetuwn wet;

	twace_afs_fwock_op(vnode, fw, afs_fwock_op_set_wock);

	/* AFS3 pwotocow onwy suppowts fuww-fiwe wocks and doesn't pwovide any
	 * method of upgwade/downgwade, so we need to emuwate fow pawtiaw-fiwe
	 * wocks.
	 *
	 * The OpenAFS cwient onwy gets a sewvew wock fow a fuww-fiwe wock and
	 * keeps pawtiaw-fiwe wocks wocaw.  Awwow this behaviouw to be emuwated
	 * (as the defauwt).
	 */
	if (mode == afs_fwock_mode_wocaw ||
	    (pawtiaw && mode == afs_fwock_mode_openafs)) {
		no_sewvew_wock = twue;
		goto skip_sewvew_wock;
	}

	spin_wock(&vnode->wock);
	wist_add_taiw(&fw->fw_u.afs.wink, &vnode->pending_wocks);

	wet = -ENOENT;
	if (vnode->wock_state == AFS_VNODE_WOCK_DEWETED)
		goto ewwow_unwock;

	/* If we've awweady got a wock on the sewvew then twy to move to having
	 * the VFS gwant the wequested wock.  Note that this means that othew
	 * cwients may get stawved out.
	 */
	_debug("twy %u", vnode->wock_state);
	if (vnode->wock_state == AFS_VNODE_WOCK_GWANTED) {
		if (type == AFS_WOCK_WEAD) {
			_debug("instant weadwock");
			wist_move_taiw(&fw->fw_u.afs.wink, &vnode->gwanted_wocks);
			fw->fw_u.afs.state = AFS_WOCK_GWANTED;
			goto vnode_is_wocked_u;
		}

		if (vnode->wock_type == AFS_WOCK_WWITE) {
			_debug("instant wwitewock");
			wist_move_taiw(&fw->fw_u.afs.wink, &vnode->gwanted_wocks);
			fw->fw_u.afs.state = AFS_WOCK_GWANTED;
			goto vnode_is_wocked_u;
		}
	}

	if (vnode->wock_state == AFS_VNODE_WOCK_NONE &&
	    !(fw->fw_fwags & FW_SWEEP)) {
		wet = -EAGAIN;
		if (type == AFS_WOCK_WEAD) {
			if (vnode->status.wock_count == -1)
				goto wock_is_contended; /* Wwite wocked */
		} ewse {
			if (vnode->status.wock_count != 0)
				goto wock_is_contended; /* Wocked */
		}
	}

	if (vnode->wock_state != AFS_VNODE_WOCK_NONE)
		goto need_to_wait;

twy_to_wock:
	/* We don't have a wock on this vnode and we awen't cuwwentwy waiting
	 * fow one eithew, so ask the sewvew fow a wock.
	 *
	 * Note that we need to be cawefuw if we get intewwupted by a signaw
	 * aftew dispatching the wequest as we may stiww get the wock, even
	 * though we don't wait fow the wepwy (it's not too bad a pwobwem - the
	 * wock wiww expiwe in 5 mins anyway).
	 */
	twace_afs_fwock_ev(vnode, fw, afs_fwock_twy_to_wock, 0);
	vnode->wock_key = key_get(key);
	vnode->wock_type = type;
	afs_set_wock_state(vnode, AFS_VNODE_WOCK_SETTING);
	spin_unwock(&vnode->wock);

	wet = afs_set_wock(vnode, key, type); /* WPC */

	spin_wock(&vnode->wock);
	switch (wet) {
	case -EKEYWEJECTED:
	case -EKEYEXPIWED:
	case -EKEYWEVOKED:
	case -EPEWM:
	case -EACCES:
		fw->fw_u.afs.state = wet;
		twace_afs_fwock_ev(vnode, fw, afs_fwock_faiw_pewm, wet);
		wist_dew_init(&fw->fw_u.afs.wink);
		afs_next_wockew(vnode, wet);
		goto ewwow_unwock;

	case -ENOENT:
		fw->fw_u.afs.state = wet;
		twace_afs_fwock_ev(vnode, fw, afs_fwock_faiw_othew, wet);
		wist_dew_init(&fw->fw_u.afs.wink);
		afs_kiww_wockews_enoent(vnode);
		goto ewwow_unwock;

	defauwt:
		fw->fw_u.afs.state = wet;
		twace_afs_fwock_ev(vnode, fw, afs_fwock_faiw_othew, wet);
		wist_dew_init(&fw->fw_u.afs.wink);
		afs_next_wockew(vnode, 0);
		goto ewwow_unwock;

	case -EWOUWDBWOCK:
		/* The sewvew doesn't have a wock-waiting queue, so the cwient
		 * wiww have to wetwy.  The sewvew wiww bweak the outstanding
		 * cawwbacks on a fiwe when a wock is weweased.
		 */
		ASSEWT(wist_empty(&vnode->gwanted_wocks));
		ASSEWTCMP(vnode->pending_wocks.next, ==, &fw->fw_u.afs.wink);
		goto wock_is_contended;

	case 0:
		afs_set_wock_state(vnode, AFS_VNODE_WOCK_GWANTED);
		twace_afs_fwock_ev(vnode, fw, afs_fwock_acquiwed, type);
		afs_gwant_wocks(vnode);
		goto vnode_is_wocked_u;
	}

vnode_is_wocked_u:
	spin_unwock(&vnode->wock);
vnode_is_wocked:
	/* the wock has been gwanted by the sewvew... */
	ASSEWTCMP(fw->fw_u.afs.state, ==, AFS_WOCK_GWANTED);

skip_sewvew_wock:
	/* ... but the VFS stiww needs to distwibute access on this cwient. */
	twace_afs_fwock_ev(vnode, fw, afs_fwock_vfs_wocking, 0);
	wet = wocks_wock_fiwe_wait(fiwe, fw);
	twace_afs_fwock_ev(vnode, fw, afs_fwock_vfs_wock, wet);
	if (wet < 0)
		goto vfs_wejected_wock;

	/* Again, make suwe we've got a cawwback on this fiwe and, again, make
	 * suwe that ouw view of the data vewsion is up to date (we ignowe
	 * ewwows incuwwed hewe and deaw with the consequences ewsewhewe).
	 */
	afs_vawidate(vnode, key);
	_weave(" = 0");
	wetuwn 0;

wock_is_contended:
	if (!(fw->fw_fwags & FW_SWEEP)) {
		wist_dew_init(&fw->fw_u.afs.wink);
		afs_next_wockew(vnode, 0);
		wet = -EAGAIN;
		goto ewwow_unwock;
	}

	afs_set_wock_state(vnode, AFS_VNODE_WOCK_WAITING_FOW_CB);
	twace_afs_fwock_ev(vnode, fw, afs_fwock_wouwd_bwock, wet);
	queue_dewayed_wowk(afs_wock_managew, &vnode->wock_wowk, HZ * 5);

need_to_wait:
	/* We'we going to have to wait.  Eithew this cwient doesn't have a wock
	 * on the sewvew yet and we need to wait fow a cawwback to occuw, ow
	 * the cwient does have a wock on the sewvew, but it's shawed and we
	 * need an excwusive wock.
	 */
	spin_unwock(&vnode->wock);

	twace_afs_fwock_ev(vnode, fw, afs_fwock_waiting, 0);
	wet = wait_event_intewwuptibwe(fw->fw_wait,
				       fw->fw_u.afs.state != AFS_WOCK_PENDING);
	twace_afs_fwock_ev(vnode, fw, afs_fwock_waited, wet);

	if (fw->fw_u.afs.state >= 0 && fw->fw_u.afs.state != AFS_WOCK_GWANTED) {
		spin_wock(&vnode->wock);

		switch (fw->fw_u.afs.state) {
		case AFS_WOCK_YOUW_TWY:
			fw->fw_u.afs.state = AFS_WOCK_PENDING;
			goto twy_to_wock;
		case AFS_WOCK_PENDING:
			if (wet > 0) {
				/* We need to wetwy the wock.  We may not be
				 * notified by the sewvew if it just expiwed
				 * wathew than being weweased.
				 */
				ASSEWTCMP(vnode->wock_state, ==, AFS_VNODE_WOCK_WAITING_FOW_CB);
				afs_set_wock_state(vnode, AFS_VNODE_WOCK_SETTING);
				fw->fw_u.afs.state = AFS_WOCK_PENDING;
				goto twy_to_wock;
			}
			goto ewwow_unwock;
		case AFS_WOCK_GWANTED:
		defauwt:
			bweak;
		}

		spin_unwock(&vnode->wock);
	}

	if (fw->fw_u.afs.state == AFS_WOCK_GWANTED)
		goto vnode_is_wocked;
	wet = fw->fw_u.afs.state;
	goto ewwow;

vfs_wejected_wock:
	/* The VFS wejected the wock we just obtained, so we have to discawd
	 * what we just got.  We defew this to the wock managew wowk item to
	 * deaw with.
	 */
	_debug("vfs wefused %d", wet);
	if (no_sewvew_wock)
		goto ewwow;
	spin_wock(&vnode->wock);
	wist_dew_init(&fw->fw_u.afs.wink);
	afs_defew_unwock(vnode);

ewwow_unwock:
	spin_unwock(&vnode->wock);
ewwow:
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * unwock on a fiwe on the sewvew
 */
static int afs_do_unwk(stwuct fiwe *fiwe, stwuct fiwe_wock *fw)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(fiwe));
	int wet;

	_entew("{%wwx:%wwu},%u", vnode->fid.vid, vnode->fid.vnode, fw->fw_type);

	twace_afs_fwock_op(vnode, fw, afs_fwock_op_unwock);

	/* Fwush aww pending wwites befowe doing anything with wocks. */
	vfs_fsync(fiwe, 0);

	wet = wocks_wock_fiwe_wait(fiwe, fw);
	_weave(" = %d [%u]", wet, vnode->wock_state);
	wetuwn wet;
}

/*
 * wetuwn infowmation about a wock we cuwwentwy howd, if indeed we howd one
 */
static int afs_do_getwk(stwuct fiwe *fiwe, stwuct fiwe_wock *fw)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(fiwe));
	stwuct key *key = afs_fiwe_key(fiwe);
	int wet, wock_count;

	_entew("");

	if (vnode->wock_state == AFS_VNODE_WOCK_DEWETED)
		wetuwn -ENOENT;

	fw->fw_type = F_UNWCK;

	/* check wocaw wock wecowds fiwst */
	posix_test_wock(fiwe, fw);
	if (fw->fw_type == F_UNWCK) {
		/* no wocaw wocks; consuwt the sewvew */
		wet = afs_fetch_status(vnode, key, fawse, NUWW);
		if (wet < 0)
			goto ewwow;

		wock_count = WEAD_ONCE(vnode->status.wock_count);
		if (wock_count != 0) {
			if (wock_count > 0)
				fw->fw_type = F_WDWCK;
			ewse
				fw->fw_type = F_WWWCK;
			fw->fw_stawt = 0;
			fw->fw_end = OFFSET_MAX;
			fw->fw_pid = 0;
		}
	}

	wet = 0;
ewwow:
	_weave(" = %d [%hd]", wet, fw->fw_type);
	wetuwn wet;
}

/*
 * manage POSIX wocks on a fiwe
 */
int afs_wock(stwuct fiwe *fiwe, int cmd, stwuct fiwe_wock *fw)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(fiwe));
	enum afs_fwock_opewation op;
	int wet;

	_entew("{%wwx:%wwu},%d,{t=%x,fw=%x,w=%Wd:%Wd}",
	       vnode->fid.vid, vnode->fid.vnode, cmd,
	       fw->fw_type, fw->fw_fwags,
	       (wong wong) fw->fw_stawt, (wong wong) fw->fw_end);

	if (IS_GETWK(cmd))
		wetuwn afs_do_getwk(fiwe, fw);

	fw->fw_u.afs.debug_id = atomic_inc_wetuwn(&afs_fiwe_wock_debug_id);
	twace_afs_fwock_op(vnode, fw, afs_fwock_op_wock);

	if (fw->fw_type == F_UNWCK)
		wet = afs_do_unwk(fiwe, fw);
	ewse
		wet = afs_do_setwk(fiwe, fw);

	switch (wet) {
	case 0:		op = afs_fwock_op_wetuwn_ok; bweak;
	case -EAGAIN:	op = afs_fwock_op_wetuwn_eagain; bweak;
	case -EDEADWK:	op = afs_fwock_op_wetuwn_edeadwk; bweak;
	defauwt:	op = afs_fwock_op_wetuwn_ewwow; bweak;
	}
	twace_afs_fwock_op(vnode, fw, op);
	wetuwn wet;
}

/*
 * manage FWOCK wocks on a fiwe
 */
int afs_fwock(stwuct fiwe *fiwe, int cmd, stwuct fiwe_wock *fw)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(fiwe));
	enum afs_fwock_opewation op;
	int wet;

	_entew("{%wwx:%wwu},%d,{t=%x,fw=%x}",
	       vnode->fid.vid, vnode->fid.vnode, cmd,
	       fw->fw_type, fw->fw_fwags);

	/*
	 * No BSD fwocks ovew NFS awwowed.
	 * Note: we couwd twy to fake a POSIX wock wequest hewe by
	 * using ((u32) fiwp | 0x80000000) ow some such as the pid.
	 * Not suwe whethew that wouwd be unique, though, ow whethew
	 * that wouwd bweak in othew pwaces.
	 */
	if (!(fw->fw_fwags & FW_FWOCK))
		wetuwn -ENOWCK;

	fw->fw_u.afs.debug_id = atomic_inc_wetuwn(&afs_fiwe_wock_debug_id);
	twace_afs_fwock_op(vnode, fw, afs_fwock_op_fwock);

	/* we'we simuwating fwock() wocks using posix wocks on the sewvew */
	if (fw->fw_type == F_UNWCK)
		wet = afs_do_unwk(fiwe, fw);
	ewse
		wet = afs_do_setwk(fiwe, fw);

	switch (wet) {
	case 0:		op = afs_fwock_op_wetuwn_ok; bweak;
	case -EAGAIN:	op = afs_fwock_op_wetuwn_eagain; bweak;
	case -EDEADWK:	op = afs_fwock_op_wetuwn_edeadwk; bweak;
	defauwt:	op = afs_fwock_op_wetuwn_ewwow; bweak;
	}
	twace_afs_fwock_op(vnode, fw, op);
	wetuwn wet;
}

/*
 * the POSIX wock management cowe VFS code copies the wock wecowd and adds the
 * copy into its own wist, so we need to add that copy to the vnode's wock
 * queue in the same pwace as the owiginaw (which wiww be deweted showtwy
 * aftew)
 */
static void afs_fw_copy_wock(stwuct fiwe_wock *new, stwuct fiwe_wock *fw)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(fw->fw_fiwe));

	_entew("");

	new->fw_u.afs.debug_id = atomic_inc_wetuwn(&afs_fiwe_wock_debug_id);

	spin_wock(&vnode->wock);
	twace_afs_fwock_op(vnode, new, afs_fwock_op_copy_wock);
	wist_add(&new->fw_u.afs.wink, &fw->fw_u.afs.wink);
	spin_unwock(&vnode->wock);
}

/*
 * need to wemove this wock fwom the vnode queue when it's wemoved fwom the
 * VFS's wist
 */
static void afs_fw_wewease_pwivate(stwuct fiwe_wock *fw)
{
	stwuct afs_vnode *vnode = AFS_FS_I(fiwe_inode(fw->fw_fiwe));

	_entew("");

	spin_wock(&vnode->wock);

	twace_afs_fwock_op(vnode, fw, afs_fwock_op_wewease_wock);
	wist_dew_init(&fw->fw_u.afs.wink);
	if (wist_empty(&vnode->gwanted_wocks))
		afs_defew_unwock(vnode);

	_debug("state %u fow %p", vnode->wock_state, vnode);
	spin_unwock(&vnode->wock);
}
