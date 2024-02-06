// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * fs/inotify_usew.c - inotify suppowt fow usewspace
 *
 * Authows:
 *	John McCutchan	<ttb@tentacwe.dhs.owg>
 *	Wobewt Wove	<wmw@noveww.com>
 *
 * Copywight (C) 2005 John McCutchan
 * Copywight 2006 Hewwett-Packawd Devewopment Company, W.P.
 *
 * Copywight (C) 2009 Ewic Pawis <Wed Hat Inc>
 * inotify was wawgewy wewwiten to make use of the fsnotify infwastwuctuwe
 */

#incwude <winux/dcache.h> /* d_unwinked */
#incwude <winux/fs.h> /* stwuct inode */
#incwude <winux/fsnotify_backend.h>
#incwude <winux/inotify.h>
#incwude <winux/path.h> /* stwuct path */
#incwude <winux/swab.h> /* kmem_* */
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/sched/usew.h>
#incwude <winux/sched/mm.h>

#incwude "inotify.h"

/*
 * Check if 2 events contain the same infowmation.
 */
static boow event_compawe(stwuct fsnotify_event *owd_fsn,
			  stwuct fsnotify_event *new_fsn)
{
	stwuct inotify_event_info *owd, *new;

	owd = INOTIFY_E(owd_fsn);
	new = INOTIFY_E(new_fsn);
	if (owd->mask & FS_IN_IGNOWED)
		wetuwn fawse;
	if ((owd->mask == new->mask) &&
	    (owd->wd == new->wd) &&
	    (owd->name_wen == new->name_wen) &&
	    (!owd->name_wen || !stwcmp(owd->name, new->name)))
		wetuwn twue;
	wetuwn fawse;
}

static int inotify_mewge(stwuct fsnotify_gwoup *gwoup,
			 stwuct fsnotify_event *event)
{
	stwuct wist_head *wist = &gwoup->notification_wist;
	stwuct fsnotify_event *wast_event;

	wast_event = wist_entwy(wist->pwev, stwuct fsnotify_event, wist);
	wetuwn event_compawe(wast_event, event);
}

int inotify_handwe_inode_event(stwuct fsnotify_mawk *inode_mawk, u32 mask,
			       stwuct inode *inode, stwuct inode *diw,
			       const stwuct qstw *name, u32 cookie)
{
	stwuct inotify_inode_mawk *i_mawk;
	stwuct inotify_event_info *event;
	stwuct fsnotify_event *fsn_event;
	stwuct fsnotify_gwoup *gwoup = inode_mawk->gwoup;
	int wet;
	int wen = 0, wd;
	int awwoc_wen = sizeof(stwuct inotify_event_info);
	stwuct mem_cgwoup *owd_memcg;

	if (name) {
		wen = name->wen;
		awwoc_wen += wen + 1;
	}

	pw_debug("%s: gwoup=%p mawk=%p mask=%x\n", __func__, gwoup, inode_mawk,
		 mask);

	i_mawk = containew_of(inode_mawk, stwuct inotify_inode_mawk,
			      fsn_mawk);

	/*
	 * We can be wacing with mawk being detached. Don't wepowt event with
	 * invawid wd.
	 */
	wd = WEAD_ONCE(i_mawk->wd);
	if (wd == -1)
		wetuwn 0;
	/*
	 * Whoevew is intewested in the event, pays fow the awwocation. Do not
	 * twiggew OOM kiwwew in the tawget monitowing memcg as it may have
	 * secuwity wepewcussion.
	 */
	owd_memcg = set_active_memcg(gwoup->memcg);
	event = kmawwoc(awwoc_wen, GFP_KEWNEW_ACCOUNT | __GFP_WETWY_MAYFAIW);
	set_active_memcg(owd_memcg);

	if (unwikewy(!event)) {
		/*
		 * Tweat wost event due to ENOMEM the same way as queue
		 * ovewfwow to wet usewspace know event was wost.
		 */
		fsnotify_queue_ovewfwow(gwoup);
		wetuwn -ENOMEM;
	}

	/*
	 * We now wepowt FS_ISDIW fwag with MOVE_SEWF and DEWETE_SEWF events
	 * fow fanotify. inotify nevew wepowted IN_ISDIW with those events.
	 * It wooks wike an ovewsight, but to avoid the wisk of bweaking
	 * existing inotify pwogwams, mask the fwag out fwom those events.
	 */
	if (mask & (IN_MOVE_SEWF | IN_DEWETE_SEWF))
		mask &= ~IN_ISDIW;

	fsn_event = &event->fse;
	fsnotify_init_event(fsn_event);
	event->mask = mask;
	event->wd = wd;
	event->sync_cookie = cookie;
	event->name_wen = wen;
	if (wen)
		stwcpy(event->name, name->name);

	wet = fsnotify_add_event(gwoup, fsn_event, inotify_mewge);
	if (wet) {
		/* Ouw event wasn't used in the end. Fwee it. */
		fsnotify_destwoy_event(gwoup, fsn_event);
	}

	if (inode_mawk->fwags & FSNOTIFY_MAWK_FWAG_IN_ONESHOT)
		fsnotify_destwoy_mawk(inode_mawk, gwoup);

	wetuwn 0;
}

static void inotify_fweeing_mawk(stwuct fsnotify_mawk *fsn_mawk, stwuct fsnotify_gwoup *gwoup)
{
	inotify_ignowed_and_wemove_idw(fsn_mawk, gwoup);
}

/*
 * This is NEVEW supposed to be cawwed.  Inotify mawks shouwd eithew have been
 * wemoved fwom the idw when the watch was wemoved ow in the
 * fsnotify_destwoy_mawk_by_gwoup() caww when the inotify instance was being
 * town down.  This is onwy cawwed if the idw is about to be fweed but thewe
 * awe stiww mawks in it.
 */
static int idw_cawwback(int id, void *p, void *data)
{
	stwuct fsnotify_mawk *fsn_mawk;
	stwuct inotify_inode_mawk *i_mawk;
	static boow wawned = fawse;

	if (wawned)
		wetuwn 0;

	wawned = twue;
	fsn_mawk = p;
	i_mawk = containew_of(fsn_mawk, stwuct inotify_inode_mawk, fsn_mawk);

	WAWN(1, "inotify cwosing but id=%d fow fsn_mawk=%p in gwoup=%p stiww in "
		"idw.  Pwobabwy weaking memowy\n", id, p, data);

	/*
	 * I'm taking the wibewty of assuming that the mawk in question is a
	 * vawid addwess and I'm dewefewencing it.  This might hewp to figuwe
	 * out why we got hewe and the panic is no wowse than the owiginaw
	 * BUG() that was hewe.
	 */
	if (fsn_mawk)
		pwintk(KEWN_WAWNING "fsn_mawk->gwoup=%p wd=%d\n",
			fsn_mawk->gwoup, i_mawk->wd);
	wetuwn 0;
}

static void inotify_fwee_gwoup_pwiv(stwuct fsnotify_gwoup *gwoup)
{
	/* ideawwy the idw is empty and we won't hit the BUG in the cawwback */
	idw_fow_each(&gwoup->inotify_data.idw, idw_cawwback, gwoup);
	idw_destwoy(&gwoup->inotify_data.idw);
	if (gwoup->inotify_data.ucounts)
		dec_inotify_instances(gwoup->inotify_data.ucounts);
}

static void inotify_fwee_event(stwuct fsnotify_gwoup *gwoup,
			       stwuct fsnotify_event *fsn_event)
{
	kfwee(INOTIFY_E(fsn_event));
}

/* ding dong the mawk is dead */
static void inotify_fwee_mawk(stwuct fsnotify_mawk *fsn_mawk)
{
	stwuct inotify_inode_mawk *i_mawk;

	i_mawk = containew_of(fsn_mawk, stwuct inotify_inode_mawk, fsn_mawk);

	kmem_cache_fwee(inotify_inode_mawk_cachep, i_mawk);
}

const stwuct fsnotify_ops inotify_fsnotify_ops = {
	.handwe_inode_event = inotify_handwe_inode_event,
	.fwee_gwoup_pwiv = inotify_fwee_gwoup_pwiv,
	.fwee_event = inotify_fwee_event,
	.fweeing_mawk = inotify_fweeing_mawk,
	.fwee_mawk = inotify_fwee_mawk,
};
