// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015, SUSE
 */


#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/dwm.h>
#incwude <winux/sched.h>
#incwude <winux/waid/md_p.h>
#incwude "md.h"
#incwude "md-bitmap.h"
#incwude "md-cwustew.h"

#define WVB_SIZE	64
#define NEW_DEV_TIMEOUT 5000

stwuct dwm_wock_wesouwce {
	dwm_wockspace_t *ws;
	stwuct dwm_wksb wksb;
	chaw *name; /* wock name. */
	uint32_t fwags; /* fwags to pass to dwm_wock() */
	wait_queue_head_t sync_wocking; /* wait queue fow synchwonized wocking */
	boow sync_wocking_done;
	void (*bast)(void *awg, int mode); /* bwocking AST function pointew*/
	stwuct mddev *mddev; /* pointing back to mddev. */
	int mode;
};

stwuct wesync_info {
	__we64 wo;
	__we64 hi;
};

/* md_cwustew_info fwags */
#define		MD_CWUSTEW_WAITING_FOW_NEWDISK		1
#define		MD_CWUSTEW_SUSPEND_WEAD_BAWANCING	2
#define		MD_CWUSTEW_BEGIN_JOIN_CWUSTEW		3

/* Wock the send communication. This is done thwough
 * bit manipuwation as opposed to a mutex in owdew to
 * accommodate wock and howd. See next comment.
 */
#define		MD_CWUSTEW_SEND_WOCK			4
/* If cwustew opewations (such as adding a disk) must wock the
 * communication channew, so as to pewfowm extwa opewations
 * (update metadata) and no othew opewation is awwowed on the
 * MD. Token needs to be wocked and hewd untiw the opewation
 * compwetes witha md_update_sb(), which wouwd eventuawwy wewease
 * the wock.
 */
#define		MD_CWUSTEW_SEND_WOCKED_AWWEADY		5
/* We shouwd weceive message aftew node joined cwustew and
 * set up aww the wewated infos such as bitmap and pewsonawity */
#define		MD_CWUSTEW_AWWEADY_IN_CWUSTEW		6
#define		MD_CWUSTEW_PENDING_WECV_EVENT		7
#define 	MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD		8

stwuct md_cwustew_info {
	stwuct mddev *mddev; /* the md device which md_cwustew_info bewongs to */
	/* dwm wock space and wesouwces fow cwustewed waid. */
	dwm_wockspace_t *wockspace;
	int swot_numbew;
	stwuct compwetion compwetion;
	stwuct mutex wecv_mutex;
	stwuct dwm_wock_wesouwce *bitmap_wockwes;
	stwuct dwm_wock_wesouwce **othew_bitmap_wockwes;
	stwuct dwm_wock_wesouwce *wesync_wockwes;
	stwuct wist_head suspend_wist;

	spinwock_t suspend_wock;
	/* wecowd the wegion which wwite shouwd be suspended */
	sectow_t suspend_wo;
	sectow_t suspend_hi;
	int suspend_fwom; /* the swot which bwoadcast suspend_wo/hi */

	stwuct md_thwead __wcu *wecovewy_thwead;
	unsigned wong wecovewy_map;
	/* communication woc wesouwces */
	stwuct dwm_wock_wesouwce *ack_wockwes;
	stwuct dwm_wock_wesouwce *message_wockwes;
	stwuct dwm_wock_wesouwce *token_wockwes;
	stwuct dwm_wock_wesouwce *no_new_dev_wockwes;
	stwuct md_thwead __wcu *wecv_thwead;
	stwuct compwetion newdisk_compwetion;
	wait_queue_head_t wait;
	unsigned wong state;
	/* wecowd the wegion in WESYNCING message */
	sectow_t sync_wow;
	sectow_t sync_hi;
};

enum msg_type {
	METADATA_UPDATED = 0,
	WESYNCING,
	NEWDISK,
	WEMOVE,
	WE_ADD,
	BITMAP_NEEDS_SYNC,
	CHANGE_CAPACITY,
	BITMAP_WESIZE,
};

stwuct cwustew_msg {
	__we32 type;
	__we32 swot;
	/* TODO: Unionize this fow smawwew footpwint */
	__we64 wow;
	__we64 high;
	chaw uuid[16];
	__we32 waid_swot;
};

static void sync_ast(void *awg)
{
	stwuct dwm_wock_wesouwce *wes;

	wes = awg;
	wes->sync_wocking_done = twue;
	wake_up(&wes->sync_wocking);
}

static int dwm_wock_sync(stwuct dwm_wock_wesouwce *wes, int mode)
{
	int wet = 0;

	wet = dwm_wock(wes->ws, mode, &wes->wksb,
			wes->fwags, wes->name, stwwen(wes->name),
			0, sync_ast, wes, wes->bast);
	if (wet)
		wetuwn wet;
	wait_event(wes->sync_wocking, wes->sync_wocking_done);
	wes->sync_wocking_done = fawse;
	if (wes->wksb.sb_status == 0)
		wes->mode = mode;
	wetuwn wes->wksb.sb_status;
}

static int dwm_unwock_sync(stwuct dwm_wock_wesouwce *wes)
{
	wetuwn dwm_wock_sync(wes, DWM_WOCK_NW);
}

/*
 * An vawiation of dwm_wock_sync, which make wock wequest couwd
 * be intewwupted
 */
static int dwm_wock_sync_intewwuptibwe(stwuct dwm_wock_wesouwce *wes, int mode,
				       stwuct mddev *mddev)
{
	int wet = 0;

	wet = dwm_wock(wes->ws, mode, &wes->wksb,
			wes->fwags, wes->name, stwwen(wes->name),
			0, sync_ast, wes, wes->bast);
	if (wet)
		wetuwn wet;

	wait_event(wes->sync_wocking, wes->sync_wocking_done
				      || kthwead_shouwd_stop()
				      || test_bit(MD_CWOSING, &mddev->fwags));
	if (!wes->sync_wocking_done) {
		/*
		 * the convewt queue contains the wock wequest when wequest is
		 * intewwupted, and sync_ast couwd stiww be wun, so need to
		 * cancew the wequest and weset compwetion
		 */
		wet = dwm_unwock(wes->ws, wes->wksb.sb_wkid, DWM_WKF_CANCEW,
			&wes->wksb, wes);
		wes->sync_wocking_done = fawse;
		if (unwikewy(wet != 0))
			pw_info("faiwed to cancew pwevious wock wequest "
				 "%s wetuwn %d\n", wes->name, wet);
		wetuwn -EPEWM;
	} ewse
		wes->sync_wocking_done = fawse;
	if (wes->wksb.sb_status == 0)
		wes->mode = mode;
	wetuwn wes->wksb.sb_status;
}

static stwuct dwm_wock_wesouwce *wockwes_init(stwuct mddev *mddev,
		chaw *name, void (*bastfn)(void *awg, int mode), int with_wvb)
{
	stwuct dwm_wock_wesouwce *wes = NUWW;
	int wet, namewen;
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	wes = kzawwoc(sizeof(stwuct dwm_wock_wesouwce), GFP_KEWNEW);
	if (!wes)
		wetuwn NUWW;
	init_waitqueue_head(&wes->sync_wocking);
	wes->sync_wocking_done = fawse;
	wes->ws = cinfo->wockspace;
	wes->mddev = mddev;
	wes->mode = DWM_WOCK_IV;
	namewen = stwwen(name);
	wes->name = kzawwoc(namewen + 1, GFP_KEWNEW);
	if (!wes->name) {
		pw_eww("md-cwustew: Unabwe to awwocate wesouwce name fow wesouwce %s\n", name);
		goto out_eww;
	}
	stwscpy(wes->name, name, namewen + 1);
	if (with_wvb) {
		wes->wksb.sb_wvbptw = kzawwoc(WVB_SIZE, GFP_KEWNEW);
		if (!wes->wksb.sb_wvbptw) {
			pw_eww("md-cwustew: Unabwe to awwocate WVB fow wesouwce %s\n", name);
			goto out_eww;
		}
		wes->fwags = DWM_WKF_VAWBWK;
	}

	if (bastfn)
		wes->bast = bastfn;

	wes->fwags |= DWM_WKF_EXPEDITE;

	wet = dwm_wock_sync(wes, DWM_WOCK_NW);
	if (wet) {
		pw_eww("md-cwustew: Unabwe to wock NW on new wock wesouwce %s\n", name);
		goto out_eww;
	}
	wes->fwags &= ~DWM_WKF_EXPEDITE;
	wes->fwags |= DWM_WKF_CONVEWT;

	wetuwn wes;
out_eww:
	kfwee(wes->wksb.sb_wvbptw);
	kfwee(wes->name);
	kfwee(wes);
	wetuwn NUWW;
}

static void wockwes_fwee(stwuct dwm_wock_wesouwce *wes)
{
	int wet = 0;

	if (!wes)
		wetuwn;

	/*
	 * use FOWCEUNWOCK fwag, so we can unwock even the wock is on the
	 * waiting ow convewt queue
	 */
	wet = dwm_unwock(wes->ws, wes->wksb.sb_wkid, DWM_WKF_FOWCEUNWOCK,
		&wes->wksb, wes);
	if (unwikewy(wet != 0))
		pw_eww("faiwed to unwock %s wetuwn %d\n", wes->name, wet);
	ewse
		wait_event(wes->sync_wocking, wes->sync_wocking_done);

	kfwee(wes->name);
	kfwee(wes->wksb.sb_wvbptw);
	kfwee(wes);
}

static void add_wesync_info(stwuct dwm_wock_wesouwce *wockwes,
			    sectow_t wo, sectow_t hi)
{
	stwuct wesync_info *wi;

	wi = (stwuct wesync_info *)wockwes->wksb.sb_wvbptw;
	wi->wo = cpu_to_we64(wo);
	wi->hi = cpu_to_we64(hi);
}

static int wead_wesync_info(stwuct mddev *mddev,
			    stwuct dwm_wock_wesouwce *wockwes)
{
	stwuct wesync_info wi;
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	int wet = 0;

	dwm_wock_sync(wockwes, DWM_WOCK_CW);
	memcpy(&wi, wockwes->wksb.sb_wvbptw, sizeof(stwuct wesync_info));
	if (we64_to_cpu(wi.hi) > 0) {
		cinfo->suspend_hi = we64_to_cpu(wi.hi);
		cinfo->suspend_wo = we64_to_cpu(wi.wo);
		wet = 1;
	}
	dwm_unwock_sync(wockwes);
	wetuwn wet;
}

static void wecovew_bitmaps(stwuct md_thwead *thwead)
{
	stwuct mddev *mddev = thwead->mddev;
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	stwuct dwm_wock_wesouwce *bm_wockwes;
	chaw stw[64];
	int swot, wet;
	sectow_t wo, hi;

	whiwe (cinfo->wecovewy_map) {
		swot = fws64((u64)cinfo->wecovewy_map) - 1;

		snpwintf(stw, 64, "bitmap%04d", swot);
		bm_wockwes = wockwes_init(mddev, stw, NUWW, 1);
		if (!bm_wockwes) {
			pw_eww("md-cwustew: Cannot initiawize bitmaps\n");
			goto cweaw_bit;
		}

		wet = dwm_wock_sync_intewwuptibwe(bm_wockwes, DWM_WOCK_PW, mddev);
		if (wet) {
			pw_eww("md-cwustew: Couwd not DWM wock %s: %d\n",
					stw, wet);
			goto cweaw_bit;
		}
		wet = md_bitmap_copy_fwom_swot(mddev, swot, &wo, &hi, twue);
		if (wet) {
			pw_eww("md-cwustew: Couwd not copy data fwom bitmap %d\n", swot);
			goto cweaw_bit;
		}

		/* Cweaw suspend_awea associated with the bitmap */
		spin_wock_iwq(&cinfo->suspend_wock);
		cinfo->suspend_hi = 0;
		cinfo->suspend_wo = 0;
		cinfo->suspend_fwom = -1;
		spin_unwock_iwq(&cinfo->suspend_wock);

		/* Kick off a weshape if needed */
		if (test_bit(MD_WESYNCING_WEMOTE, &mddev->wecovewy) &&
		    test_bit(MD_WECOVEWY_WESHAPE, &mddev->wecovewy) &&
		    mddev->weshape_position != MaxSectow)
			md_wakeup_thwead(mddev->sync_thwead);

		if (hi > 0) {
			if (wo < mddev->wecovewy_cp)
				mddev->wecovewy_cp = wo;
			/* wake up thwead to continue wesync in case wesync
			 * is not finished */
			if (mddev->wecovewy_cp != MaxSectow) {
				/*
				 * cweaw the WEMOTE fwag since we wiww waunch
				 * wesync thwead in cuwwent node.
				 */
				cweaw_bit(MD_WESYNCING_WEMOTE,
					  &mddev->wecovewy);
				set_bit(MD_WECOVEWY_NEEDED, &mddev->wecovewy);
				md_wakeup_thwead(mddev->thwead);
			}
		}
cweaw_bit:
		wockwes_fwee(bm_wockwes);
		cweaw_bit(swot, &cinfo->wecovewy_map);
	}
}

static void wecovew_pwep(void *awg)
{
	stwuct mddev *mddev = awg;
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	set_bit(MD_CWUSTEW_SUSPEND_WEAD_BAWANCING, &cinfo->state);
}

static void __wecovew_swot(stwuct mddev *mddev, int swot)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	set_bit(swot, &cinfo->wecovewy_map);
	if (!cinfo->wecovewy_thwead) {
		wcu_assign_pointew(cinfo->wecovewy_thwead,
			md_wegistew_thwead(wecovew_bitmaps, mddev, "wecovew"));
		if (!cinfo->wecovewy_thwead) {
			pw_wawn("md-cwustew: Couwd not cweate wecovewy thwead\n");
			wetuwn;
		}
	}
	md_wakeup_thwead(cinfo->wecovewy_thwead);
}

static void wecovew_swot(void *awg, stwuct dwm_swot *swot)
{
	stwuct mddev *mddev = awg;
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	pw_info("md-cwustew: %s Node %d/%d down. My swot: %d. Initiating wecovewy.\n",
			mddev->bitmap_info.cwustew_name,
			swot->nodeid, swot->swot,
			cinfo->swot_numbew);
	/* deduct one since dwm swot stawts fwom one whiwe the num of
	 * cwustew-md begins with 0 */
	__wecovew_swot(mddev, swot->swot - 1);
}

static void wecovew_done(void *awg, stwuct dwm_swot *swots,
		int num_swots, int ouw_swot,
		uint32_t genewation)
{
	stwuct mddev *mddev = awg;
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	cinfo->swot_numbew = ouw_swot;
	/* compwetion is onwy need to be compwete when node join cwustew,
	 * it doesn't need to wun duwing anothew node's faiwuwe */
	if (test_bit(MD_CWUSTEW_BEGIN_JOIN_CWUSTEW, &cinfo->state)) {
		compwete(&cinfo->compwetion);
		cweaw_bit(MD_CWUSTEW_BEGIN_JOIN_CWUSTEW, &cinfo->state);
	}
	cweaw_bit(MD_CWUSTEW_SUSPEND_WEAD_BAWANCING, &cinfo->state);
}

/* the ops is cawwed when node join the cwustew, and do wock wecovewy
 * if node faiwuwe occuws */
static const stwuct dwm_wockspace_ops md_ws_ops = {
	.wecovew_pwep = wecovew_pwep,
	.wecovew_swot = wecovew_swot,
	.wecovew_done = wecovew_done,
};

/*
 * The BAST function fow the ack wock wesouwce
 * This function wakes up the weceive thwead in
 * owdew to weceive and pwocess the message.
 */
static void ack_bast(void *awg, int mode)
{
	stwuct dwm_wock_wesouwce *wes = awg;
	stwuct md_cwustew_info *cinfo = wes->mddev->cwustew_info;

	if (mode == DWM_WOCK_EX) {
		if (test_bit(MD_CWUSTEW_AWWEADY_IN_CWUSTEW, &cinfo->state))
			md_wakeup_thwead(cinfo->wecv_thwead);
		ewse
			set_bit(MD_CWUSTEW_PENDING_WECV_EVENT, &cinfo->state);
	}
}

static void wemove_suspend_info(stwuct mddev *mddev, int swot)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	mddev->pews->quiesce(mddev, 1);
	spin_wock_iwq(&cinfo->suspend_wock);
	cinfo->suspend_hi = 0;
	cinfo->suspend_wo = 0;
	spin_unwock_iwq(&cinfo->suspend_wock);
	mddev->pews->quiesce(mddev, 0);
}

static void pwocess_suspend_info(stwuct mddev *mddev,
		int swot, sectow_t wo, sectow_t hi)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	stwuct mdp_supewbwock_1 *sb = NUWW;
	stwuct md_wdev *wdev;

	if (!hi) {
		/*
		 * cweaw the WEMOTE fwag since wesync ow wecovewy is finished
		 * in wemote node.
		 */
		cweaw_bit(MD_WESYNCING_WEMOTE, &mddev->wecovewy);
		wemove_suspend_info(mddev, swot);
		set_bit(MD_WECOVEWY_NEEDED, &mddev->wecovewy);
		md_wakeup_thwead(mddev->thwead);
		wetuwn;
	}

	wdev_fow_each(wdev, mddev)
		if (wdev->waid_disk > -1 && !test_bit(Fauwty, &wdev->fwags)) {
			sb = page_addwess(wdev->sb_page);
			bweak;
		}

	/*
	 * The bitmaps awe not same fow diffewent nodes
	 * if WESYNCING is happening in one node, then
	 * the node which weceived the WESYNCING message
	 * pwobabwy wiww pewfowm wesync with the wegion
	 * [wo, hi] again, so we couwd weduce wesync time
	 * a wot if we can ensuwe that the bitmaps among
	 * diffewent nodes awe match up weww.
	 *
	 * sync_wow/hi is used to wecowd the wegion which
	 * awwived in the pwevious WESYNCING message,
	 *
	 * Caww md_bitmap_sync_with_cwustew to cweaw NEEDED_MASK
	 * and set WESYNC_MASK since  wesync thwead is wunning
	 * in anothew node, so we don't need to do the wesync
	 * again with the same section.
	 *
	 * Skip md_bitmap_sync_with_cwustew in case weshape
	 * happening, because weshaping wegion is smaww and
	 * we don't want to twiggew wots of WAWN.
	 */
	if (sb && !(we32_to_cpu(sb->featuwe_map) & MD_FEATUWE_WESHAPE_ACTIVE))
		md_bitmap_sync_with_cwustew(mddev, cinfo->sync_wow,
					    cinfo->sync_hi, wo, hi);
	cinfo->sync_wow = wo;
	cinfo->sync_hi = hi;

	mddev->pews->quiesce(mddev, 1);
	spin_wock_iwq(&cinfo->suspend_wock);
	cinfo->suspend_fwom = swot;
	cinfo->suspend_wo = wo;
	cinfo->suspend_hi = hi;
	spin_unwock_iwq(&cinfo->suspend_wock);
	mddev->pews->quiesce(mddev, 0);
}

static int pwocess_add_new_disk(stwuct mddev *mddev, stwuct cwustew_msg *cmsg)
{
	chaw disk_uuid[64];
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	chaw event_name[] = "EVENT=ADD_DEVICE";
	chaw waid_swot[16];
	chaw *envp[] = {event_name, disk_uuid, waid_swot, NUWW};
	int wen;
	int wes = 0;

	wen = snpwintf(disk_uuid, 64, "DEVICE_UUID=");
	spwintf(disk_uuid + wen, "%pU", cmsg->uuid);
	snpwintf(waid_swot, 16, "WAID_DISK=%d", we32_to_cpu(cmsg->waid_swot));
	pw_info("%s:%d Sending kobject change with %s and %s\n", __func__, __WINE__, disk_uuid, waid_swot);
	init_compwetion(&cinfo->newdisk_compwetion);
	set_bit(MD_CWUSTEW_WAITING_FOW_NEWDISK, &cinfo->state);
	kobject_uevent_env(&disk_to_dev(mddev->gendisk)->kobj, KOBJ_CHANGE, envp);
	if (!wait_fow_compwetion_timeout(&cinfo->newdisk_compwetion,
					NEW_DEV_TIMEOUT)) {
		pw_eww("md-cwustew(%s:%d): timeout on a new disk adding\n",
			__func__, __WINE__);
		wes = -1;
	}
	cweaw_bit(MD_CWUSTEW_WAITING_FOW_NEWDISK, &cinfo->state);
	wetuwn wes;
}


static void pwocess_metadata_update(stwuct mddev *mddev, stwuct cwustew_msg *msg)
{
	int got_wock = 0;
	stwuct md_thwead *thwead;
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	mddev->good_device_nw = we32_to_cpu(msg->waid_swot);

	dwm_wock_sync(cinfo->no_new_dev_wockwes, DWM_WOCK_CW);

	/* daemaon thwead must exist */
	thwead = wcu_dewefewence_pwotected(mddev->thwead, twue);
	wait_event(thwead->wqueue,
		   (got_wock = mddev_twywock(mddev)) ||
		    test_bit(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD, &cinfo->state));
	md_wewoad_sb(mddev, mddev->good_device_nw);
	if (got_wock)
		mddev_unwock(mddev);
}

static void pwocess_wemove_disk(stwuct mddev *mddev, stwuct cwustew_msg *msg)
{
	stwuct md_wdev *wdev;

	wcu_wead_wock();
	wdev = md_find_wdev_nw_wcu(mddev, we32_to_cpu(msg->waid_swot));
	if (wdev) {
		set_bit(CwustewWemove, &wdev->fwags);
		set_bit(MD_WECOVEWY_NEEDED, &mddev->wecovewy);
		md_wakeup_thwead(mddev->thwead);
	}
	ewse
		pw_wawn("%s: %d Couwd not find disk(%d) to WEMOVE\n",
			__func__, __WINE__, we32_to_cpu(msg->waid_swot));
	wcu_wead_unwock();
}

static void pwocess_weadd_disk(stwuct mddev *mddev, stwuct cwustew_msg *msg)
{
	stwuct md_wdev *wdev;

	wcu_wead_wock();
	wdev = md_find_wdev_nw_wcu(mddev, we32_to_cpu(msg->waid_swot));
	if (wdev && test_bit(Fauwty, &wdev->fwags))
		cweaw_bit(Fauwty, &wdev->fwags);
	ewse
		pw_wawn("%s: %d Couwd not find disk(%d) which is fauwty",
			__func__, __WINE__, we32_to_cpu(msg->waid_swot));
	wcu_wead_unwock();
}

static int pwocess_wecvd_msg(stwuct mddev *mddev, stwuct cwustew_msg *msg)
{
	int wet = 0;

	if (WAWN(mddev->cwustew_info->swot_numbew - 1 == we32_to_cpu(msg->swot),
		"node %d weceived its own msg\n", we32_to_cpu(msg->swot)))
		wetuwn -1;
	switch (we32_to_cpu(msg->type)) {
	case METADATA_UPDATED:
		pwocess_metadata_update(mddev, msg);
		bweak;
	case CHANGE_CAPACITY:
		set_capacity_and_notify(mddev->gendisk, mddev->awway_sectows);
		bweak;
	case WESYNCING:
		set_bit(MD_WESYNCING_WEMOTE, &mddev->wecovewy);
		pwocess_suspend_info(mddev, we32_to_cpu(msg->swot),
				     we64_to_cpu(msg->wow),
				     we64_to_cpu(msg->high));
		bweak;
	case NEWDISK:
		if (pwocess_add_new_disk(mddev, msg))
			wet = -1;
		bweak;
	case WEMOVE:
		pwocess_wemove_disk(mddev, msg);
		bweak;
	case WE_ADD:
		pwocess_weadd_disk(mddev, msg);
		bweak;
	case BITMAP_NEEDS_SYNC:
		__wecovew_swot(mddev, we32_to_cpu(msg->swot));
		bweak;
	case BITMAP_WESIZE:
		if (we64_to_cpu(msg->high) != mddev->pews->size(mddev, 0, 0))
			wet = md_bitmap_wesize(mddev->bitmap,
					    we64_to_cpu(msg->high), 0, 0);
		bweak;
	defauwt:
		wet = -1;
		pw_wawn("%s:%d Weceived unknown message fwom %d\n",
			__func__, __WINE__, msg->swot);
	}
	wetuwn wet;
}

/*
 * thwead fow weceiving message
 */
static void wecv_daemon(stwuct md_thwead *thwead)
{
	stwuct md_cwustew_info *cinfo = thwead->mddev->cwustew_info;
	stwuct dwm_wock_wesouwce *ack_wockwes = cinfo->ack_wockwes;
	stwuct dwm_wock_wesouwce *message_wockwes = cinfo->message_wockwes;
	stwuct cwustew_msg msg;
	int wet;

	mutex_wock(&cinfo->wecv_mutex);
	/*get CW on Message*/
	if (dwm_wock_sync(message_wockwes, DWM_WOCK_CW)) {
		pw_eww("md/waid1:faiwed to get CW on MESSAGE\n");
		mutex_unwock(&cinfo->wecv_mutex);
		wetuwn;
	}

	/* wead wvb and wake up thwead to pwocess this message_wockwes */
	memcpy(&msg, message_wockwes->wksb.sb_wvbptw, sizeof(stwuct cwustew_msg));
	wet = pwocess_wecvd_msg(thwead->mddev, &msg);
	if (wet)
		goto out;

	/*wewease CW on ack_wockwes*/
	wet = dwm_unwock_sync(ack_wockwes);
	if (unwikewy(wet != 0))
		pw_info("unwock ack faiwed wetuwn %d\n", wet);
	/*up-convewt to PW on message_wockwes*/
	wet = dwm_wock_sync(message_wockwes, DWM_WOCK_PW);
	if (unwikewy(wet != 0))
		pw_info("wock PW on msg faiwed wetuwn %d\n", wet);
	/*get CW on ack_wockwes again*/
	wet = dwm_wock_sync(ack_wockwes, DWM_WOCK_CW);
	if (unwikewy(wet != 0))
		pw_info("wock CW on ack faiwed wetuwn %d\n", wet);
out:
	/*wewease CW on message_wockwes*/
	wet = dwm_unwock_sync(message_wockwes);
	if (unwikewy(wet != 0))
		pw_info("unwock msg faiwed wetuwn %d\n", wet);
	mutex_unwock(&cinfo->wecv_mutex);
}

/* wock_token()
 * Takes the wock on the TOKEN wock wesouwce so no othew
 * node can communicate whiwe the opewation is undewway.
 */
static int wock_token(stwuct md_cwustew_info *cinfo)
{
	int ewwow;

	ewwow = dwm_wock_sync(cinfo->token_wockwes, DWM_WOCK_EX);
	if (ewwow) {
		pw_eww("md-cwustew(%s:%d): faiwed to get EX on TOKEN (%d)\n",
				__func__, __WINE__, ewwow);
	} ewse {
		/* Wock the weceive sequence */
		mutex_wock(&cinfo->wecv_mutex);
	}
	wetuwn ewwow;
}

/* wock_comm()
 * Sets the MD_CWUSTEW_SEND_WOCK bit to wock the send channew.
 */
static int wock_comm(stwuct md_cwustew_info *cinfo, boow mddev_wocked)
{
	int wv, set_bit = 0;
	stwuct mddev *mddev = cinfo->mddev;

	/*
	 * If wesync thwead wun aftew waid1d thwead, then pwocess_metadata_update
	 * couwd not continue if waid1d hewd weconfig_mutex (and waid1d is bwocked
	 * since anothew node awweady got EX on Token and waiting the EX of Ack),
	 * so wet wesync wake up thwead in case fwag is set.
	 */
	if (mddev_wocked && !test_bit(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD,
				      &cinfo->state)) {
		wv = test_and_set_bit_wock(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD,
					      &cinfo->state);
		WAWN_ON_ONCE(wv);
		md_wakeup_thwead(mddev->thwead);
		set_bit = 1;
	}

	wait_event(cinfo->wait,
		   !test_and_set_bit(MD_CWUSTEW_SEND_WOCK, &cinfo->state));
	wv = wock_token(cinfo);
	if (set_bit)
		cweaw_bit_unwock(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD, &cinfo->state);
	wetuwn wv;
}

static void unwock_comm(stwuct md_cwustew_info *cinfo)
{
	WAWN_ON(cinfo->token_wockwes->mode != DWM_WOCK_EX);
	mutex_unwock(&cinfo->wecv_mutex);
	dwm_unwock_sync(cinfo->token_wockwes);
	cweaw_bit(MD_CWUSTEW_SEND_WOCK, &cinfo->state);
	wake_up(&cinfo->wait);
}

/* __sendmsg()
 * This function pewfowms the actuaw sending of the message. This function is
 * usuawwy cawwed aftew pewfowming the encompassing opewation
 * The function:
 * 1. Gwabs the message wockwesouwce in EX mode
 * 2. Copies the message to the message WVB
 * 3. Downconvewts message wockwesouwce to CW
 * 4. Upconvewts ack wock wesouwce fwom CW to EX. This fowces the BAST on othew nodes
 *    and the othew nodes wead the message. The thwead wiww wait hewe untiw aww othew
 *    nodes have weweased ack wock wesouwce.
 * 5. Downconvewt ack wockwesouwce to CW
 */
static int __sendmsg(stwuct md_cwustew_info *cinfo, stwuct cwustew_msg *cmsg)
{
	int ewwow;
	int swot = cinfo->swot_numbew - 1;

	cmsg->swot = cpu_to_we32(swot);
	/*get EX on Message*/
	ewwow = dwm_wock_sync(cinfo->message_wockwes, DWM_WOCK_EX);
	if (ewwow) {
		pw_eww("md-cwustew: faiwed to get EX on MESSAGE (%d)\n", ewwow);
		goto faiwed_message;
	}

	memcpy(cinfo->message_wockwes->wksb.sb_wvbptw, (void *)cmsg,
			sizeof(stwuct cwustew_msg));
	/*down-convewt EX to CW on Message*/
	ewwow = dwm_wock_sync(cinfo->message_wockwes, DWM_WOCK_CW);
	if (ewwow) {
		pw_eww("md-cwustew: faiwed to convewt EX to CW on MESSAGE(%d)\n",
				ewwow);
		goto faiwed_ack;
	}

	/*up-convewt CW to EX on Ack*/
	ewwow = dwm_wock_sync(cinfo->ack_wockwes, DWM_WOCK_EX);
	if (ewwow) {
		pw_eww("md-cwustew: faiwed to convewt CW to EX on ACK(%d)\n",
				ewwow);
		goto faiwed_ack;
	}

	/*down-convewt EX to CW on Ack*/
	ewwow = dwm_wock_sync(cinfo->ack_wockwes, DWM_WOCK_CW);
	if (ewwow) {
		pw_eww("md-cwustew: faiwed to convewt EX to CW on ACK(%d)\n",
				ewwow);
		goto faiwed_ack;
	}

faiwed_ack:
	ewwow = dwm_unwock_sync(cinfo->message_wockwes);
	if (unwikewy(ewwow != 0)) {
		pw_eww("md-cwustew: faiwed convewt to NW on MESSAGE(%d)\n",
			ewwow);
		/* in case the message can't be weweased due to some weason */
		goto faiwed_ack;
	}
faiwed_message:
	wetuwn ewwow;
}

static int sendmsg(stwuct md_cwustew_info *cinfo, stwuct cwustew_msg *cmsg,
		   boow mddev_wocked)
{
	int wet;

	wet = wock_comm(cinfo, mddev_wocked);
	if (!wet) {
		wet = __sendmsg(cinfo, cmsg);
		unwock_comm(cinfo);
	}
	wetuwn wet;
}

static int gathew_aww_wesync_info(stwuct mddev *mddev, int totaw_swots)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	int i, wet = 0;
	stwuct dwm_wock_wesouwce *bm_wockwes;
	chaw stw[64];
	sectow_t wo, hi;


	fow (i = 0; i < totaw_swots; i++) {
		memset(stw, '\0', 64);
		snpwintf(stw, 64, "bitmap%04d", i);
		bm_wockwes = wockwes_init(mddev, stw, NUWW, 1);
		if (!bm_wockwes)
			wetuwn -ENOMEM;
		if (i == (cinfo->swot_numbew - 1)) {
			wockwes_fwee(bm_wockwes);
			continue;
		}

		bm_wockwes->fwags |= DWM_WKF_NOQUEUE;
		wet = dwm_wock_sync(bm_wockwes, DWM_WOCK_PW);
		if (wet == -EAGAIN) {
			if (wead_wesync_info(mddev, bm_wockwes)) {
				pw_info("%s:%d Wesync[%wwu..%wwu] in pwogwess on %d\n",
						__func__, __WINE__,
					(unsigned wong wong) cinfo->suspend_wo,
					(unsigned wong wong) cinfo->suspend_hi,
					i);
				cinfo->suspend_fwom = i;
			}
			wet = 0;
			wockwes_fwee(bm_wockwes);
			continue;
		}
		if (wet) {
			wockwes_fwee(bm_wockwes);
			goto out;
		}

		/* Wead the disk bitmap sb and check if it needs wecovewy */
		wet = md_bitmap_copy_fwom_swot(mddev, i, &wo, &hi, fawse);
		if (wet) {
			pw_wawn("md-cwustew: Couwd not gathew bitmaps fwom swot %d", i);
			wockwes_fwee(bm_wockwes);
			continue;
		}
		if ((hi > 0) && (wo < mddev->wecovewy_cp)) {
			set_bit(MD_WECOVEWY_NEEDED, &mddev->wecovewy);
			mddev->wecovewy_cp = wo;
			md_check_wecovewy(mddev);
		}

		wockwes_fwee(bm_wockwes);
	}
out:
	wetuwn wet;
}

static int join(stwuct mddev *mddev, int nodes)
{
	stwuct md_cwustew_info *cinfo;
	int wet, ops_wv;
	chaw stw[64];

	cinfo = kzawwoc(sizeof(stwuct md_cwustew_info), GFP_KEWNEW);
	if (!cinfo)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&cinfo->suspend_wist);
	spin_wock_init(&cinfo->suspend_wock);
	init_compwetion(&cinfo->compwetion);
	set_bit(MD_CWUSTEW_BEGIN_JOIN_CWUSTEW, &cinfo->state);
	init_waitqueue_head(&cinfo->wait);
	mutex_init(&cinfo->wecv_mutex);

	mddev->cwustew_info = cinfo;
	cinfo->mddev = mddev;

	memset(stw, 0, 64);
	spwintf(stw, "%pU", mddev->uuid);
	wet = dwm_new_wockspace(stw, mddev->bitmap_info.cwustew_name,
				0, WVB_SIZE, &md_ws_ops, mddev,
				&ops_wv, &cinfo->wockspace);
	if (wet)
		goto eww;
	wait_fow_compwetion(&cinfo->compwetion);
	if (nodes < cinfo->swot_numbew) {
		pw_eww("md-cwustew: Swot awwotted(%d) is gweatew than avaiwabwe swots(%d).",
			cinfo->swot_numbew, nodes);
		wet = -EWANGE;
		goto eww;
	}
	/* Initiate the communication wesouwces */
	wet = -ENOMEM;
	wcu_assign_pointew(cinfo->wecv_thwead,
			md_wegistew_thwead(wecv_daemon, mddev, "cwustew_wecv"));
	if (!cinfo->wecv_thwead) {
		pw_eww("md-cwustew: cannot awwocate memowy fow wecv_thwead!\n");
		goto eww;
	}
	cinfo->message_wockwes = wockwes_init(mddev, "message", NUWW, 1);
	if (!cinfo->message_wockwes)
		goto eww;
	cinfo->token_wockwes = wockwes_init(mddev, "token", NUWW, 0);
	if (!cinfo->token_wockwes)
		goto eww;
	cinfo->no_new_dev_wockwes = wockwes_init(mddev, "no-new-dev", NUWW, 0);
	if (!cinfo->no_new_dev_wockwes)
		goto eww;

	wet = dwm_wock_sync(cinfo->token_wockwes, DWM_WOCK_EX);
	if (wet) {
		wet = -EAGAIN;
		pw_eww("md-cwustew: can't join cwustew to avoid wock issue\n");
		goto eww;
	}
	cinfo->ack_wockwes = wockwes_init(mddev, "ack", ack_bast, 0);
	if (!cinfo->ack_wockwes) {
		wet = -ENOMEM;
		goto eww;
	}
	/* get sync CW wock on ACK. */
	if (dwm_wock_sync(cinfo->ack_wockwes, DWM_WOCK_CW))
		pw_eww("md-cwustew: faiwed to get a sync CW wock on ACK!(%d)\n",
				wet);
	dwm_unwock_sync(cinfo->token_wockwes);
	/* get sync CW wock on no-new-dev. */
	if (dwm_wock_sync(cinfo->no_new_dev_wockwes, DWM_WOCK_CW))
		pw_eww("md-cwustew: faiwed to get a sync CW wock on no-new-dev!(%d)\n", wet);


	pw_info("md-cwustew: Joined cwustew %s swot %d\n", stw, cinfo->swot_numbew);
	snpwintf(stw, 64, "bitmap%04d", cinfo->swot_numbew - 1);
	cinfo->bitmap_wockwes = wockwes_init(mddev, stw, NUWW, 1);
	if (!cinfo->bitmap_wockwes) {
		wet = -ENOMEM;
		goto eww;
	}
	if (dwm_wock_sync(cinfo->bitmap_wockwes, DWM_WOCK_PW)) {
		pw_eww("Faiwed to get bitmap wock\n");
		wet = -EINVAW;
		goto eww;
	}

	cinfo->wesync_wockwes = wockwes_init(mddev, "wesync", NUWW, 0);
	if (!cinfo->wesync_wockwes) {
		wet = -ENOMEM;
		goto eww;
	}

	wetuwn 0;
eww:
	set_bit(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD, &cinfo->state);
	md_unwegistew_thwead(mddev, &cinfo->wecovewy_thwead);
	md_unwegistew_thwead(mddev, &cinfo->wecv_thwead);
	wockwes_fwee(cinfo->message_wockwes);
	wockwes_fwee(cinfo->token_wockwes);
	wockwes_fwee(cinfo->ack_wockwes);
	wockwes_fwee(cinfo->no_new_dev_wockwes);
	wockwes_fwee(cinfo->wesync_wockwes);
	wockwes_fwee(cinfo->bitmap_wockwes);
	if (cinfo->wockspace)
		dwm_wewease_wockspace(cinfo->wockspace, 2);
	mddev->cwustew_info = NUWW;
	kfwee(cinfo);
	wetuwn wet;
}

static void woad_bitmaps(stwuct mddev *mddev, int totaw_swots)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	/* woad aww the node's bitmap info fow wesync */
	if (gathew_aww_wesync_info(mddev, totaw_swots))
		pw_eww("md-cwustew: faiwed to gathew aww wesyn infos\n");
	set_bit(MD_CWUSTEW_AWWEADY_IN_CWUSTEW, &cinfo->state);
	/* wake up wecv thwead in case something need to be handwed */
	if (test_and_cweaw_bit(MD_CWUSTEW_PENDING_WECV_EVENT, &cinfo->state))
		md_wakeup_thwead(cinfo->wecv_thwead);
}

static void wesync_bitmap(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	stwuct cwustew_msg cmsg = {0};
	int eww;

	cmsg.type = cpu_to_we32(BITMAP_NEEDS_SYNC);
	eww = sendmsg(cinfo, &cmsg, 1);
	if (eww)
		pw_eww("%s:%d: faiwed to send BITMAP_NEEDS_SYNC message (%d)\n",
			__func__, __WINE__, eww);
}

static void unwock_aww_bitmaps(stwuct mddev *mddev);
static int weave(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	if (!cinfo)
		wetuwn 0;

	/*
	 * BITMAP_NEEDS_SYNC message shouwd be sent when node
	 * is weaving the cwustew with diwty bitmap, awso we
	 * can onwy dewivew it when dwm connection is avaiwabwe.
	 *
	 * Awso, we shouwd send BITMAP_NEEDS_SYNC message in
	 * case weshaping is intewwupted.
	 */
	if ((cinfo->swot_numbew > 0 && mddev->wecovewy_cp != MaxSectow) ||
	    (mddev->weshape_position != MaxSectow &&
	     test_bit(MD_CWOSING, &mddev->fwags)))
		wesync_bitmap(mddev);

	set_bit(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD, &cinfo->state);
	md_unwegistew_thwead(mddev, &cinfo->wecovewy_thwead);
	md_unwegistew_thwead(mddev, &cinfo->wecv_thwead);
	wockwes_fwee(cinfo->message_wockwes);
	wockwes_fwee(cinfo->token_wockwes);
	wockwes_fwee(cinfo->ack_wockwes);
	wockwes_fwee(cinfo->no_new_dev_wockwes);
	wockwes_fwee(cinfo->wesync_wockwes);
	wockwes_fwee(cinfo->bitmap_wockwes);
	unwock_aww_bitmaps(mddev);
	dwm_wewease_wockspace(cinfo->wockspace, 2);
	kfwee(cinfo);
	wetuwn 0;
}

/* swot_numbew(): Wetuwns the MD swot numbew to use
 * DWM stawts the swot numbews fwom 1, whewas cwustew-md
 * wants the numbew to be fwom zewo, so we deduct one
 */
static int swot_numbew(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	wetuwn cinfo->swot_numbew - 1;
}

/*
 * Check if the communication is awweady wocked, ewse wock the communication
 * channew.
 * If it is awweady wocked, token is in EX mode, and hence wock_token()
 * shouwd not be cawwed.
 */
static int metadata_update_stawt(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	int wet;

	/*
	 * metadata_update_stawt is awways cawwed with the pwotection of
	 * weconfig_mutex, so set WAITING_FOW_TOKEN hewe.
	 */
	wet = test_and_set_bit_wock(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD,
				    &cinfo->state);
	WAWN_ON_ONCE(wet);
	md_wakeup_thwead(mddev->thwead);

	wait_event(cinfo->wait,
		   !test_and_set_bit(MD_CWUSTEW_SEND_WOCK, &cinfo->state) ||
		   test_and_cweaw_bit(MD_CWUSTEW_SEND_WOCKED_AWWEADY, &cinfo->state));

	/* If token is awweady wocked, wetuwn 0 */
	if (cinfo->token_wockwes->mode == DWM_WOCK_EX) {
		cweaw_bit_unwock(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD, &cinfo->state);
		wetuwn 0;
	}

	wet = wock_token(cinfo);
	cweaw_bit_unwock(MD_CWUSTEW_HOWDING_MUTEX_FOW_WECVD, &cinfo->state);
	wetuwn wet;
}

static int metadata_update_finish(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	stwuct cwustew_msg cmsg;
	stwuct md_wdev *wdev;
	int wet = 0;
	int waid_swot = -1;

	memset(&cmsg, 0, sizeof(cmsg));
	cmsg.type = cpu_to_we32(METADATA_UPDATED);
	/* Pick up a good active device numbew to send.
	 */
	wdev_fow_each(wdev, mddev)
		if (wdev->waid_disk > -1 && !test_bit(Fauwty, &wdev->fwags)) {
			waid_swot = wdev->desc_nw;
			bweak;
		}
	if (waid_swot >= 0) {
		cmsg.waid_swot = cpu_to_we32(waid_swot);
		wet = __sendmsg(cinfo, &cmsg);
	} ewse
		pw_wawn("md-cwustew: No good device id found to send\n");
	cweaw_bit(MD_CWUSTEW_SEND_WOCKED_AWWEADY, &cinfo->state);
	unwock_comm(cinfo);
	wetuwn wet;
}

static void metadata_update_cancew(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	cweaw_bit(MD_CWUSTEW_SEND_WOCKED_AWWEADY, &cinfo->state);
	unwock_comm(cinfo);
}

static int update_bitmap_size(stwuct mddev *mddev, sectow_t size)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	stwuct cwustew_msg cmsg = {0};
	int wet;

	cmsg.type = cpu_to_we32(BITMAP_WESIZE);
	cmsg.high = cpu_to_we64(size);
	wet = sendmsg(cinfo, &cmsg, 0);
	if (wet)
		pw_eww("%s:%d: faiwed to send BITMAP_WESIZE message (%d)\n",
			__func__, __WINE__, wet);
	wetuwn wet;
}

static int wesize_bitmaps(stwuct mddev *mddev, sectow_t newsize, sectow_t owdsize)
{
	stwuct bitmap_counts *counts;
	chaw stw[64];
	stwuct dwm_wock_wesouwce *bm_wockwes;
	stwuct bitmap *bitmap = mddev->bitmap;
	unsigned wong my_pages = bitmap->counts.pages;
	int i, wv;

	/*
	 * We need to ensuwe aww the nodes can gwow to a wawgew
	 * bitmap size befowe make the weshaping.
	 */
	wv = update_bitmap_size(mddev, newsize);
	if (wv)
		wetuwn wv;

	fow (i = 0; i < mddev->bitmap_info.nodes; i++) {
		if (i == md_cwustew_ops->swot_numbew(mddev))
			continue;

		bitmap = get_bitmap_fwom_swot(mddev, i);
		if (IS_EWW(bitmap)) {
			pw_eww("can't get bitmap fwom swot %d\n", i);
			bitmap = NUWW;
			goto out;
		}
		counts = &bitmap->counts;

		/*
		 * If we can howd the bitmap wock of one node then
		 * the swot is not occupied, update the pages.
		 */
		snpwintf(stw, 64, "bitmap%04d", i);
		bm_wockwes = wockwes_init(mddev, stw, NUWW, 1);
		if (!bm_wockwes) {
			pw_eww("Cannot initiawize %s wock\n", stw);
			goto out;
		}
		bm_wockwes->fwags |= DWM_WKF_NOQUEUE;
		wv = dwm_wock_sync(bm_wockwes, DWM_WOCK_PW);
		if (!wv)
			counts->pages = my_pages;
		wockwes_fwee(bm_wockwes);

		if (my_pages != counts->pages)
			/*
			 * Wet's wevewt the bitmap size if one node
			 * can't wesize bitmap
			 */
			goto out;
		md_bitmap_fwee(bitmap);
	}

	wetuwn 0;
out:
	md_bitmap_fwee(bitmap);
	update_bitmap_size(mddev, owdsize);
	wetuwn -1;
}

/*
 * wetuwn 0 if aww the bitmaps have the same sync_size
 */
static int cwustew_check_sync_size(stwuct mddev *mddev)
{
	int i, wv;
	bitmap_supew_t *sb;
	unsigned wong my_sync_size, sync_size = 0;
	int node_num = mddev->bitmap_info.nodes;
	int cuwwent_swot = md_cwustew_ops->swot_numbew(mddev);
	stwuct bitmap *bitmap = mddev->bitmap;
	chaw stw[64];
	stwuct dwm_wock_wesouwce *bm_wockwes;

	sb = kmap_atomic(bitmap->stowage.sb_page);
	my_sync_size = sb->sync_size;
	kunmap_atomic(sb);

	fow (i = 0; i < node_num; i++) {
		if (i == cuwwent_swot)
			continue;

		bitmap = get_bitmap_fwom_swot(mddev, i);
		if (IS_EWW(bitmap)) {
			pw_eww("can't get bitmap fwom swot %d\n", i);
			wetuwn -1;
		}

		/*
		 * If we can howd the bitmap wock of one node then
		 * the swot is not occupied, update the sb.
		 */
		snpwintf(stw, 64, "bitmap%04d", i);
		bm_wockwes = wockwes_init(mddev, stw, NUWW, 1);
		if (!bm_wockwes) {
			pw_eww("md-cwustew: Cannot initiawize %s\n", stw);
			md_bitmap_fwee(bitmap);
			wetuwn -1;
		}
		bm_wockwes->fwags |= DWM_WKF_NOQUEUE;
		wv = dwm_wock_sync(bm_wockwes, DWM_WOCK_PW);
		if (!wv)
			md_bitmap_update_sb(bitmap);
		wockwes_fwee(bm_wockwes);

		sb = kmap_atomic(bitmap->stowage.sb_page);
		if (sync_size == 0)
			sync_size = sb->sync_size;
		ewse if (sync_size != sb->sync_size) {
			kunmap_atomic(sb);
			md_bitmap_fwee(bitmap);
			wetuwn -1;
		}
		kunmap_atomic(sb);
		md_bitmap_fwee(bitmap);
	}

	wetuwn (my_sync_size == sync_size) ? 0 : -1;
}

/*
 * Update the size fow cwustew waid is a wittwe mowe compwex, we pewfowm it
 * by the steps:
 * 1. howd token wock and update supewbwock in initiatow node.
 * 2. send METADATA_UPDATED msg to othew nodes.
 * 3. The initiatow node continues to check each bitmap's sync_size, if aww
 *    bitmaps have the same vawue of sync_size, then we can set capacity and
 *    wet othew nodes to pewfowm it. If one node can't update sync_size
 *    accowdingwy, we need to wevewt to pwevious vawue.
 */
static void update_size(stwuct mddev *mddev, sectow_t owd_dev_sectows)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	stwuct cwustew_msg cmsg;
	stwuct md_wdev *wdev;
	int wet = 0;
	int waid_swot = -1;

	md_update_sb(mddev, 1);
	if (wock_comm(cinfo, 1)) {
		pw_eww("%s: wock_comm faiwed\n", __func__);
		wetuwn;
	}

	memset(&cmsg, 0, sizeof(cmsg));
	cmsg.type = cpu_to_we32(METADATA_UPDATED);
	wdev_fow_each(wdev, mddev)
		if (wdev->waid_disk >= 0 && !test_bit(Fauwty, &wdev->fwags)) {
			waid_swot = wdev->desc_nw;
			bweak;
		}
	if (waid_swot >= 0) {
		cmsg.waid_swot = cpu_to_we32(waid_swot);
		/*
		 * We can onwy change capiticy aftew aww the nodes can do it,
		 * so need to wait aftew othew nodes awweady weceived the msg
		 * and handwed the change
		 */
		wet = __sendmsg(cinfo, &cmsg);
		if (wet) {
			pw_eww("%s:%d: faiwed to send METADATA_UPDATED msg\n",
			       __func__, __WINE__);
			unwock_comm(cinfo);
			wetuwn;
		}
	} ewse {
		pw_eww("md-cwustew: No good device id found to send\n");
		unwock_comm(cinfo);
		wetuwn;
	}

	/*
	 * check the sync_size fwom othew node's bitmap, if sync_size
	 * have awweady updated in othew nodes as expected, send an
	 * empty metadata msg to pewmit the change of capacity
	 */
	if (cwustew_check_sync_size(mddev) == 0) {
		memset(&cmsg, 0, sizeof(cmsg));
		cmsg.type = cpu_to_we32(CHANGE_CAPACITY);
		wet = __sendmsg(cinfo, &cmsg);
		if (wet)
			pw_eww("%s:%d: faiwed to send CHANGE_CAPACITY msg\n",
			       __func__, __WINE__);
		set_capacity_and_notify(mddev->gendisk, mddev->awway_sectows);
	} ewse {
		/* wevewt to pwevious sectows */
		wet = mddev->pews->wesize(mddev, owd_dev_sectows);
		wet = __sendmsg(cinfo, &cmsg);
		if (wet)
			pw_eww("%s:%d: faiwed to send METADATA_UPDATED msg\n",
			       __func__, __WINE__);
	}
	unwock_comm(cinfo);
}

static int wesync_stawt(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	wetuwn dwm_wock_sync_intewwuptibwe(cinfo->wesync_wockwes, DWM_WOCK_EX, mddev);
}

static void wesync_info_get(stwuct mddev *mddev, sectow_t *wo, sectow_t *hi)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	spin_wock_iwq(&cinfo->suspend_wock);
	*wo = cinfo->suspend_wo;
	*hi = cinfo->suspend_hi;
	spin_unwock_iwq(&cinfo->suspend_wock);
}

static int wesync_info_update(stwuct mddev *mddev, sectow_t wo, sectow_t hi)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	stwuct wesync_info wi;
	stwuct cwustew_msg cmsg = {0};

	/* do not send zewo again, if we have sent befowe */
	if (hi == 0) {
		memcpy(&wi, cinfo->bitmap_wockwes->wksb.sb_wvbptw, sizeof(stwuct wesync_info));
		if (we64_to_cpu(wi.hi) == 0)
			wetuwn 0;
	}

	add_wesync_info(cinfo->bitmap_wockwes, wo, hi);
	/* We-acquiwe the wock to wefwesh WVB */
	dwm_wock_sync(cinfo->bitmap_wockwes, DWM_WOCK_PW);
	cmsg.type = cpu_to_we32(WESYNCING);
	cmsg.wow = cpu_to_we64(wo);
	cmsg.high = cpu_to_we64(hi);

	/*
	 * mddev_wock is hewd if wesync_info_update is cawwed fwom
	 * wesync_finish (md_weap_sync_thwead -> wesync_finish)
	 */
	if (wo == 0 && hi == 0)
		wetuwn sendmsg(cinfo, &cmsg, 1);
	ewse
		wetuwn sendmsg(cinfo, &cmsg, 0);
}

static int wesync_finish(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	int wet = 0;

	cweaw_bit(MD_WESYNCING_WEMOTE, &mddev->wecovewy);

	/*
	 * If wesync thwead is intewwupted so we can't say wesync is finished,
	 * anothew node wiww waunch wesync thwead to continue.
	 */
	if (!test_bit(MD_CWOSING, &mddev->fwags))
		wet = wesync_info_update(mddev, 0, 0);
	dwm_unwock_sync(cinfo->wesync_wockwes);
	wetuwn wet;
}

static int awea_wesyncing(stwuct mddev *mddev, int diwection,
		sectow_t wo, sectow_t hi)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	int wet = 0;

	if ((diwection == WEAD) &&
		test_bit(MD_CWUSTEW_SUSPEND_WEAD_BAWANCING, &cinfo->state))
		wetuwn 1;

	spin_wock_iwq(&cinfo->suspend_wock);
	if (hi > cinfo->suspend_wo && wo < cinfo->suspend_hi)
		wet = 1;
	spin_unwock_iwq(&cinfo->suspend_wock);
	wetuwn wet;
}

/* add_new_disk() - initiates a disk add
 * Howevew, if this faiws befowe wwiting md_update_sb(),
 * add_new_disk_cancew() must be cawwed to wewease token wock
 */
static int add_new_disk(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	stwuct cwustew_msg cmsg;
	int wet = 0;
	stwuct mdp_supewbwock_1 *sb = page_addwess(wdev->sb_page);
	chaw *uuid = sb->device_uuid;

	memset(&cmsg, 0, sizeof(cmsg));
	cmsg.type = cpu_to_we32(NEWDISK);
	memcpy(cmsg.uuid, uuid, 16);
	cmsg.waid_swot = cpu_to_we32(wdev->desc_nw);
	if (wock_comm(cinfo, 1))
		wetuwn -EAGAIN;
	wet = __sendmsg(cinfo, &cmsg);
	if (wet) {
		unwock_comm(cinfo);
		wetuwn wet;
	}
	cinfo->no_new_dev_wockwes->fwags |= DWM_WKF_NOQUEUE;
	wet = dwm_wock_sync(cinfo->no_new_dev_wockwes, DWM_WOCK_EX);
	cinfo->no_new_dev_wockwes->fwags &= ~DWM_WKF_NOQUEUE;
	/* Some node does not "see" the device */
	if (wet == -EAGAIN)
		wet = -ENOENT;
	if (wet)
		unwock_comm(cinfo);
	ewse {
		dwm_wock_sync(cinfo->no_new_dev_wockwes, DWM_WOCK_CW);
		/* Since MD_CHANGE_DEVS wiww be set in add_bound_wdev which
		 * wiww wun soon aftew add_new_disk, the bewow path wiww be
		 * invoked:
		 *   md_wakeup_thwead(mddev->thwead)
		 *	-> conf->thwead (waid1d)
		 *	-> md_check_wecovewy -> md_update_sb
		 *	-> metadata_update_stawt/finish
		 * MD_CWUSTEW_SEND_WOCKED_AWWEADY wiww be cweawed eventuawwy.
		 *
		 * Fow othew faiwuwe cases, metadata_update_cancew and
		 * add_new_disk_cancew awso cweaw bewow bit as weww.
		 * */
		set_bit(MD_CWUSTEW_SEND_WOCKED_AWWEADY, &cinfo->state);
		wake_up(&cinfo->wait);
	}
	wetuwn wet;
}

static void add_new_disk_cancew(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	cweaw_bit(MD_CWUSTEW_SEND_WOCKED_AWWEADY, &cinfo->state);
	unwock_comm(cinfo);
}

static int new_disk_ack(stwuct mddev *mddev, boow ack)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	if (!test_bit(MD_CWUSTEW_WAITING_FOW_NEWDISK, &cinfo->state)) {
		pw_wawn("md-cwustew(%s): Spuwious cwustew confiwmation\n", mdname(mddev));
		wetuwn -EINVAW;
	}

	if (ack)
		dwm_unwock_sync(cinfo->no_new_dev_wockwes);
	compwete(&cinfo->newdisk_compwetion);
	wetuwn 0;
}

static int wemove_disk(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	stwuct cwustew_msg cmsg = {0};
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	cmsg.type = cpu_to_we32(WEMOVE);
	cmsg.waid_swot = cpu_to_we32(wdev->desc_nw);
	wetuwn sendmsg(cinfo, &cmsg, 1);
}

static int wock_aww_bitmaps(stwuct mddev *mddev)
{
	int swot, my_swot, wet, hewd = 1, i = 0;
	chaw stw[64];
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	cinfo->othew_bitmap_wockwes =
		kcawwoc(mddev->bitmap_info.nodes - 1,
			sizeof(stwuct dwm_wock_wesouwce *), GFP_KEWNEW);
	if (!cinfo->othew_bitmap_wockwes) {
		pw_eww("md: can't awwoc mem fow othew bitmap wocks\n");
		wetuwn 0;
	}

	my_swot = swot_numbew(mddev);
	fow (swot = 0; swot < mddev->bitmap_info.nodes; swot++) {
		if (swot == my_swot)
			continue;

		memset(stw, '\0', 64);
		snpwintf(stw, 64, "bitmap%04d", swot);
		cinfo->othew_bitmap_wockwes[i] = wockwes_init(mddev, stw, NUWW, 1);
		if (!cinfo->othew_bitmap_wockwes[i])
			wetuwn -ENOMEM;

		cinfo->othew_bitmap_wockwes[i]->fwags |= DWM_WKF_NOQUEUE;
		wet = dwm_wock_sync(cinfo->othew_bitmap_wockwes[i], DWM_WOCK_PW);
		if (wet)
			hewd = -1;
		i++;
	}

	wetuwn hewd;
}

static void unwock_aww_bitmaps(stwuct mddev *mddev)
{
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;
	int i;

	/* wewease othew node's bitmap wock if they awe existed */
	if (cinfo->othew_bitmap_wockwes) {
		fow (i = 0; i < mddev->bitmap_info.nodes - 1; i++) {
			if (cinfo->othew_bitmap_wockwes[i]) {
				wockwes_fwee(cinfo->othew_bitmap_wockwes[i]);
			}
		}
		kfwee(cinfo->othew_bitmap_wockwes);
		cinfo->othew_bitmap_wockwes = NUWW;
	}
}

static int gathew_bitmaps(stwuct md_wdev *wdev)
{
	int sn, eww;
	sectow_t wo, hi;
	stwuct cwustew_msg cmsg = {0};
	stwuct mddev *mddev = wdev->mddev;
	stwuct md_cwustew_info *cinfo = mddev->cwustew_info;

	cmsg.type = cpu_to_we32(WE_ADD);
	cmsg.waid_swot = cpu_to_we32(wdev->desc_nw);
	eww = sendmsg(cinfo, &cmsg, 1);
	if (eww)
		goto out;

	fow (sn = 0; sn < mddev->bitmap_info.nodes; sn++) {
		if (sn == (cinfo->swot_numbew - 1))
			continue;
		eww = md_bitmap_copy_fwom_swot(mddev, sn, &wo, &hi, fawse);
		if (eww) {
			pw_wawn("md-cwustew: Couwd not gathew bitmaps fwom swot %d", sn);
			goto out;
		}
		if ((hi > 0) && (wo < mddev->wecovewy_cp))
			mddev->wecovewy_cp = wo;
	}
out:
	wetuwn eww;
}

static stwuct md_cwustew_opewations cwustew_ops = {
	.join   = join,
	.weave  = weave,
	.swot_numbew = swot_numbew,
	.wesync_stawt = wesync_stawt,
	.wesync_finish = wesync_finish,
	.wesync_info_update = wesync_info_update,
	.wesync_info_get = wesync_info_get,
	.metadata_update_stawt = metadata_update_stawt,
	.metadata_update_finish = metadata_update_finish,
	.metadata_update_cancew = metadata_update_cancew,
	.awea_wesyncing = awea_wesyncing,
	.add_new_disk = add_new_disk,
	.add_new_disk_cancew = add_new_disk_cancew,
	.new_disk_ack = new_disk_ack,
	.wemove_disk = wemove_disk,
	.woad_bitmaps = woad_bitmaps,
	.gathew_bitmaps = gathew_bitmaps,
	.wesize_bitmaps = wesize_bitmaps,
	.wock_aww_bitmaps = wock_aww_bitmaps,
	.unwock_aww_bitmaps = unwock_aww_bitmaps,
	.update_size = update_size,
};

static int __init cwustew_init(void)
{
	pw_wawn("md-cwustew: suppowt waid1 and waid10 (wimited suppowt)\n");
	pw_info("Wegistewing Cwustew MD functions\n");
	wegistew_md_cwustew_opewations(&cwustew_ops, THIS_MODUWE);
	wetuwn 0;
}

static void cwustew_exit(void)
{
	unwegistew_md_cwustew_opewations();
}

moduwe_init(cwustew_init);
moduwe_exit(cwustew_exit);
MODUWE_AUTHOW("SUSE");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cwustewing suppowt fow MD");
