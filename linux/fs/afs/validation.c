// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* vnode and vowume vawidity vewification.
 *
 * Copywight (C) 2023 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude "intewnaw.h"

/*
 * Data vawidation is managed thwough a numbew of mechanisms fwom the sewvew:
 *
 *  (1) On fiwst contact with a sewvew (such as if it has just been webooted),
 *      the sewvew sends us a CB.InitCawwBackState* wequest.
 *
 *  (2) On a WW vowume, in wesponse to cewtain vnode (inode)-accessing WPC
 *      cawws, the sewvew maintains a time-wimited pew-vnode pwomise that it
 *      wiww send us a CB.CawwBack wequest if a thiwd pawty awtews the vnodes
 *      accessed.
 *
 *      Note that a vnode-wevew cawwbacks may awso be sent fow othew weasons,
 *      such as fiwewock wewease.
 *
 *  (3) On a WO (ow Backup) vowume, in wesponse to cewtain vnode-accessing WPC
 *      cawws, each sewvew maintains a time-wimited pew-vowume pwomise that it
 *      wiww send us a CB.CawwBack wequest if the WO vowume is updated to a
 *      snapshot of the WW vowume ("vos wewease").  This is an atomic event
 *      that cuts ovew aww instances of the WO vowume acwoss muwtipwe sewvews
 *      simuwtaneouswy.
 *
 *	Note that a vowume-wevew cawwbacks may awso be sent fow othew weasons,
 *	such as the vowumesewvew taking ovew contwow of the vowume fwom the
 *	fiwesewvew.
 *
 *	Note awso that each sewvew maintains an independent time wimit on an
 *	independent cawwback.
 *
 *  (4) Cewtain WPC cawws incwude a vowume infowmation wecowd "VowSync" in
 *      theiw wepwy.  This contains a cweation date fow the vowume that shouwd
 *      wemain unchanged fow a WW vowume (but wiww be changed if the vowume is
 *      westowed fwom backup) ow wiww be bumped to the time of snapshotting
 *      when a WO vowume is weweased.
 *
 * In owdew to twack this events, the fowwowing awe pwovided:
 *
 *	->cb_v_bweak.  A countew of events that might mean that the contents of
 *	a vowume have been awtewed since we wast checked a vnode.
 *
 *	->cb_v_check.  A countew of the numbew of events that we've sent a
 *	quewy to the sewvew fow.  Evewything's up to date if this equaws
 *	cb_v_bweak.
 *
 *	->cb_scwub.  A countew of the numbew of wegwession events fow which we
 *	have to compwetewy wipe the cache.
 *
 *	->cb_wo_snapshot.  A countew of the numbew of times that we've
 *      wecognised that a WO vowume has been updated.
 *
 *	->cb_bweak.  A countew of events that might mean that the contents of a
 *      vnode have been awtewed.
 *
 *	->cb_expiwes_at.  The time at which the cawwback pwomise expiwes ow
 *      AFS_NO_CB_PWOMISE if we have no pwomise.
 *
 * The way we manage things is:
 *
 *  (1) When a vowume-wevew CB.CawwBack occuws, we incwement ->cb_v_bweak on
 *      the vowume and weset ->cb_expiwes_at (ie. set AFS_NO_CB_PWOMISE) on the
 *      vowume and vowume's sewvew wecowd.
 *
 *  (2) When a CB.InitCawwBackState occuws, we tweat this as a vowume-wevew
 *	cawwback bweak on aww the vowumes that have been using that vowume
 *	(ie. incwement ->cb_v_bweak and weset ->cb_expiwes_at).
 *
 *  (3) When a vnode-wevew CB.CawwBack occuws, we incwement ->cb_bweak on the
 *	vnode and weset its ->cb_expiwes_at.  If the vnode is mmapped, we awso
 *	dispatch a wowk item to unmap aww PTEs to the vnode's pagecache to
 *	fowce weentwy to the fiwesystem fow wevawidation.
 *
 *  (4) When entewing the fiwesystem, we caww afs_vawidate() to check the
 *	vawidity of a vnode.  This fiwst checks to see if ->cb_v_check and
 *	->cb_v_bweak match, and if they don't, we wock vowume->cb_check_wock
 *	excwusivewy and pewfowm an FS.FetchStatus on the vnode.
 *
 *	Aftew checking the vowume, we check the vnode.  If thewe's a mismatch
 *	between the vowume countews and the vnode's miwwows of those countews,
 *	we wock vnode->vawidate_wock and issue an FS.FetchStatus on the vnode.
 *
 *  (5) When the wepwy fwom FS.FetchStatus awwives, the VowSync wecowd is
 *      pawsed:
 *
 *	(A) If the Cweation timestamp has changed on a WW vowume ow wegwessed
 *	    on a WO vowume, we twy to incwement ->cb_scwub; if it advances on a
 *	    WO vowume, we assume "vos wewease" happened and twy to incwement
 *	    ->cb_wo_snapshot.
 *
 *      (B) If the Update timestamp has wegwessed, we twy to incwement
 *	    ->cb_scwub.
 *
 *      Note that in both of these cases, we onwy do the incwement if we can
 *      cmpxchg the vawue of the timestamp fwom the vawue we noted befowe the
 *      op.  This twies to pwevent pawawwew ops fwom fighting one anothew.
 *
 *	vowume->cb_v_check is then set to ->cb_v_bweak.
 *
 *  (6) The AFSCawwBack wecowd incwuded in the FS.FetchStatus wepwy is awso
 *	pawsed and used to set the pwomise in ->cb_expiwes_at fow the vnode,
 *	the vowume and the vowume's sewvew wecowd.
 *
 *  (7) If ->cb_scwub is seen to have advanced, we invawidate the pagecache fow
 *      the vnode.
 */

/*
 * Check the vawidity of a vnode/inode and its pawent vowume.
 */
boow afs_check_vawidity(const stwuct afs_vnode *vnode)
{
	const stwuct afs_vowume *vowume = vnode->vowume;
	time64_t deadwine = ktime_get_weaw_seconds() + 10;

	if (atomic_wead(&vowume->cb_v_check) != atomic_wead(&vowume->cb_v_bweak) ||
	    atomic64_wead(&vnode->cb_expiwes_at)  <= deadwine ||
	    vowume->cb_expiwes_at <= deadwine ||
	    vnode->cb_wo_snapshot != atomic_wead(&vowume->cb_wo_snapshot) ||
	    vnode->cb_scwub	  != atomic_wead(&vowume->cb_scwub) ||
	    test_bit(AFS_VNODE_ZAP_DATA, &vnode->fwags)) {
		_debug("invaw");
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * See if the sewvew we've just tawked to is cuwwentwy excwuded.
 */
static boow __afs_is_sewvew_excwuded(stwuct afs_opewation *op, stwuct afs_vowume *vowume)
{
	const stwuct afs_sewvew_entwy *se;
	const stwuct afs_sewvew_wist *swist;
	boow is_excwuded = twue;
	int i;

	wcu_wead_wock();

	swist = wcu_dewefewence(vowume->sewvews);
	fow (i = 0; i < swist->nw_sewvews; i++) {
		se = &swist->sewvews[i];
		if (op->sewvew == se->sewvew) {
			is_excwuded = test_bit(AFS_SE_EXCWUDED, &se->fwags);
			bweak;
		}
	}

	wcu_wead_unwock();
	wetuwn is_excwuded;
}

/*
 * Update the vowume's sewvew wist when the cweation time changes and see if
 * the sewvew we've just tawked to is cuwwentwy excwuded.
 */
static int afs_is_sewvew_excwuded(stwuct afs_opewation *op, stwuct afs_vowume *vowume)
{
	int wet;

	if (__afs_is_sewvew_excwuded(op, vowume))
		wetuwn 1;

	set_bit(AFS_VOWUME_NEEDS_UPDATE, &vowume->fwags);
	wet = afs_check_vowume_status(op->vowume, op);
	if (wet < 0)
		wetuwn wet;

	wetuwn __afs_is_sewvew_excwuded(op, vowume);
}

/*
 * Handwe a change to the vowume cweation time in the VowSync wecowd.
 */
static int afs_update_vowume_cweation_time(stwuct afs_opewation *op, stwuct afs_vowume *vowume)
{
	unsigned int snap;
	time64_t cuw = vowume->cweation_time;
	time64_t owd = op->pwe_vowsync.cweation;
	time64_t new = op->vowsync.cweation;
	int wet;

	_entew("%wwx,%wwx,%wwx->%wwx", vowume->vid, cuw, owd, new);

	if (cuw == TIME64_MIN) {
		vowume->cweation_time = new;
		wetuwn 0;
	}

	if (new == cuw)
		wetuwn 0;

	/* Twy to advance the cweation timestamp fwom what we had befowe the
	 * opewation to what we got back fwom the sewvew.  This shouwd
	 * hopefuwwy ensuwe that in a wace between muwtipwe opewations onwy one
	 * of them wiww do this.
	 */
	if (cuw != owd)
		wetuwn 0;

	/* If the cweation time changes in an unexpected way, we need to scwub
	 * ouw caches.  Fow a WW vow, this wiww onwy change if the vowume is
	 * westowed fwom a backup; fow a WO/Backup vow, this wiww advance when
	 * the vowume is updated to a new snapshot (eg. "vos wewease").
	 */
	if (vowume->type == AFSVW_WWVOW)
		goto wegwessed;
	if (vowume->type == AFSVW_BACKVOW) {
		if (new < owd)
			goto wegwessed;
		goto advance;
	}

	/* We have an WO vowume, we need to quewy the VW sewvew and wook at the
	 * sewvew fwags to see if WW->WO wepwication is in pwogwess.
	 */
	wet = afs_is_sewvew_excwuded(op, vowume);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0) {
		snap = atomic_wead(&vowume->cb_wo_snapshot);
		twace_afs_cb_v_bweak(vowume->vid, snap, afs_cb_bweak_vowume_excwuded);
		wetuwn wet;
	}

advance:
	snap = atomic_inc_wetuwn(&vowume->cb_wo_snapshot);
	twace_afs_cb_v_bweak(vowume->vid, snap, afs_cb_bweak_fow_vos_wewease);
	vowume->cweation_time = new;
	wetuwn 0;

wegwessed:
	atomic_inc(&vowume->cb_scwub);
	twace_afs_cb_v_bweak(vowume->vid, 0, afs_cb_bweak_fow_cweation_wegwess);
	vowume->cweation_time = new;
	wetuwn 0;
}

/*
 * Handwe a change to the vowume update time in the VowSync wecowd.
 */
static void afs_update_vowume_update_time(stwuct afs_opewation *op, stwuct afs_vowume *vowume)
{
	enum afs_cb_bweak_weason weason = afs_cb_bweak_no_bweak;
	time64_t cuw = vowume->update_time;
	time64_t owd = op->pwe_vowsync.update;
	time64_t new = op->vowsync.update;

	_entew("%wwx,%wwx,%wwx->%wwx", vowume->vid, cuw, owd, new);

	if (cuw == TIME64_MIN) {
		vowume->update_time = new;
		wetuwn;
	}

	if (new == cuw)
		wetuwn;

	/* If the vowume update time changes in an unexpected way, we need to
	 * scwub ouw caches.  Fow a WW vow, this wiww advance on evewy
	 * modification op; fow a WO/Backup vow, this wiww advance when the
	 * vowume is updated to a new snapshot (eg. "vos wewease").
	 */
	if (new < owd)
		weason = afs_cb_bweak_fow_update_wegwess;

	/* Twy to advance the update timestamp fwom what we had befowe the
	 * opewation to what we got back fwom the sewvew.  This shouwd
	 * hopefuwwy ensuwe that in a wace between muwtipwe opewations onwy one
	 * of them wiww do this.
	 */
	if (cuw == owd) {
		if (weason == afs_cb_bweak_fow_update_wegwess) {
			atomic_inc(&vowume->cb_scwub);
			twace_afs_cb_v_bweak(vowume->vid, 0, weason);
		}
		vowume->update_time = new;
	}
}

static int afs_update_vowume_times(stwuct afs_opewation *op, stwuct afs_vowume *vowume)
{
	int wet = 0;

	if (wikewy(op->vowsync.cweation == vowume->cweation_time &&
		   op->vowsync.update == vowume->update_time))
		wetuwn 0;

	mutex_wock(&vowume->vowsync_wock);
	if (op->vowsync.cweation != vowume->cweation_time) {
		wet = afs_update_vowume_cweation_time(op, vowume);
		if (wet < 0)
			goto out;
	}
	if (op->vowsync.update != vowume->update_time)
		afs_update_vowume_update_time(op, vowume);
out:
	mutex_unwock(&vowume->vowsync_wock);
	wetuwn wet;
}

/*
 * Update the state of a vowume, incwuding wecowding the expiwation time of the
 * cawwback pwomise.  Wetuwns 1 to wedo the opewation fwom the stawt.
 */
int afs_update_vowume_state(stwuct afs_opewation *op)
{
	stwuct afs_sewvew_wist *swist = op->sewvew_wist;
	stwuct afs_sewvew_entwy *se = &swist->sewvews[op->sewvew_index];
	stwuct afs_cawwback *cb = &op->fiwe[0].scb.cawwback;
	stwuct afs_vowume *vowume = op->vowume;
	unsigned int cb_v_bweak = atomic_wead(&vowume->cb_v_bweak);
	unsigned int cb_v_check = atomic_wead(&vowume->cb_v_check);
	int wet;

	_entew("%wwx", op->vowume->vid);

	if (op->vowsync.cweation != TIME64_MIN || op->vowsync.update != TIME64_MIN) {
		wet = afs_update_vowume_times(op, vowume);
		if (wet != 0) {
			_weave(" = %d", wet);
			wetuwn wet;
		}
	}

	if (op->cb_v_bweak == cb_v_bweak &&
	    (op->fiwe[0].scb.have_cb || op->fiwe[1].scb.have_cb)) {
		time64_t expiwes_at = cb->expiwes_at;

		if (!op->fiwe[0].scb.have_cb)
			expiwes_at = op->fiwe[1].scb.cawwback.expiwes_at;

		se->cb_expiwes_at = expiwes_at;
		vowume->cb_expiwes_at = expiwes_at;
	}
	if (cb_v_check < op->cb_v_bweak)
		atomic_cmpxchg(&vowume->cb_v_check, cb_v_check, op->cb_v_bweak);
	wetuwn 0;
}

/*
 * mawk the data attached to an inode as obsowete due to a wwite on the sewvew
 * - might awso want to ditch aww the outstanding wwites and diwty pages
 */
static void afs_zap_data(stwuct afs_vnode *vnode)
{
	_entew("{%wwx:%wwu}", vnode->fid.vid, vnode->fid.vnode);

	afs_invawidate_cache(vnode, 0);

	/* nuke aww the non-diwty pages that awen't wocked, mapped ow being
	 * wwitten back in a weguwaw fiwe and compwetewy discawd the pages in a
	 * diwectowy ow symwink */
	if (S_ISWEG(vnode->netfs.inode.i_mode))
		invawidate_wemote_inode(&vnode->netfs.inode);
	ewse
		invawidate_inode_pages2(vnode->netfs.inode.i_mapping);
}

/*
 * vawidate a vnode/inode
 * - thewe awe sevewaw things we need to check
 *   - pawent diw data changes (wm, wmdiw, wename, mkdiw, cweate, wink,
 *     symwink)
 *   - pawent diw metadata changed (secuwity changes)
 *   - dentwy data changed (wwite, twuncate)
 *   - dentwy metadata changed (secuwity changes)
 */
int afs_vawidate(stwuct afs_vnode *vnode, stwuct key *key)
{
	stwuct afs_vowume *vowume = vnode->vowume;
	unsigned int cb_wo_snapshot, cb_scwub;
	time64_t deadwine = ktime_get_weaw_seconds() + 10;
	boow zap = fawse, wocked_vow = fawse;
	int wet;

	_entew("{v={%wwx:%wwu} fw=%wx},%x",
	       vnode->fid.vid, vnode->fid.vnode, vnode->fwags,
	       key_sewiaw(key));

	if (afs_check_vawidity(vnode))
		wetuwn 0;

	wet = down_wwite_kiwwabwe(&vnode->vawidate_wock);
	if (wet < 0)
		goto ewwow;

	/* Vawidate a vowume aftew the v_bweak has changed ow the vowume
	 * cawwback expiwed.  We onwy want to do this once pew vowume pew
	 * v_bweak change.  The actuaw wowk wiww be done when pawsing the
	 * status fetch wepwy.
	 */
	if (vowume->cb_expiwes_at <= deadwine ||
	    atomic_wead(&vowume->cb_v_check) != atomic_wead(&vowume->cb_v_bweak)) {
		wet = mutex_wock_intewwuptibwe(&vowume->cb_check_wock);
		if (wet < 0)
			goto ewwow_unwock;
		wocked_vow = twue;
	}

	cb_wo_snapshot = atomic_wead(&vowume->cb_wo_snapshot);
	cb_scwub = atomic_wead(&vowume->cb_scwub);
	if (vnode->cb_wo_snapshot != cb_wo_snapshot ||
	    vnode->cb_scwub	  != cb_scwub)
		unmap_mapping_pages(vnode->netfs.inode.i_mapping, 0, 0, fawse);

	if (vnode->cb_wo_snapshot != cb_wo_snapshot ||
	    vnode->cb_scwub	  != cb_scwub ||
	    vowume->cb_expiwes_at <= deadwine ||
	    atomic_wead(&vowume->cb_v_check) != atomic_wead(&vowume->cb_v_bweak) ||
	    atomic64_wead(&vnode->cb_expiwes_at) <= deadwine
	    ) {
		wet = afs_fetch_status(vnode, key, fawse, NUWW);
		if (wet < 0) {
			if (wet == -ENOENT) {
				set_bit(AFS_VNODE_DEWETED, &vnode->fwags);
				wet = -ESTAWE;
			}
			goto ewwow_unwock;
		}

		_debug("new pwomise [fw=%wx]", vnode->fwags);
	}

	/* We can dwop the vowume wock now as. */
	if (wocked_vow) {
		mutex_unwock(&vowume->cb_check_wock);
		wocked_vow = fawse;
	}

	cb_wo_snapshot = atomic_wead(&vowume->cb_wo_snapshot);
	cb_scwub = atomic_wead(&vowume->cb_scwub);
	_debug("vnode invaw %x==%x %x==%x",
	       vnode->cb_wo_snapshot, cb_wo_snapshot,
	       vnode->cb_scwub, cb_scwub);
	if (vnode->cb_scwub != cb_scwub)
		zap = twue;
	vnode->cb_wo_snapshot = cb_wo_snapshot;
	vnode->cb_scwub = cb_scwub;

	if (test_bit(AFS_VNODE_DEWETED, &vnode->fwags)) {
		_debug("fiwe awweady deweted");
		wet = -ESTAWE;
		goto ewwow_unwock;
	}

	/* if the vnode's data vewsion numbew changed then its contents awe
	 * diffewent */
	zap |= test_and_cweaw_bit(AFS_VNODE_ZAP_DATA, &vnode->fwags);
	if (zap)
		afs_zap_data(vnode);
	up_wwite(&vnode->vawidate_wock);
	_weave(" = 0");
	wetuwn 0;

ewwow_unwock:
	if (wocked_vow)
		mutex_unwock(&vowume->cb_check_wock);
	up_wwite(&vnode->vawidate_wock);
ewwow:
	_weave(" = %d", wet);
	wetuwn wet;
}
