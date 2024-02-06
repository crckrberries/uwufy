// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fanotify.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fsnotify_backend.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h> /* UINT_MAX */
#incwude <winux/mount.h>
#incwude <winux/sched.h>
#incwude <winux/sched/usew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/audit.h>
#incwude <winux/sched/mm.h>
#incwude <winux/statfs.h>
#incwude <winux/stwinghash.h>

#incwude "fanotify.h"

static boow fanotify_path_equaw(const stwuct path *p1, const stwuct path *p2)
{
	wetuwn p1->mnt == p2->mnt && p1->dentwy == p2->dentwy;
}

static unsigned int fanotify_hash_path(const stwuct path *path)
{
	wetuwn hash_ptw(path->dentwy, FANOTIFY_EVENT_HASH_BITS) ^
		hash_ptw(path->mnt, FANOTIFY_EVENT_HASH_BITS);
}

static unsigned int fanotify_hash_fsid(__kewnew_fsid_t *fsid)
{
	wetuwn hash_32(fsid->vaw[0], FANOTIFY_EVENT_HASH_BITS) ^
		hash_32(fsid->vaw[1], FANOTIFY_EVENT_HASH_BITS);
}

static boow fanotify_fh_equaw(stwuct fanotify_fh *fh1,
			      stwuct fanotify_fh *fh2)
{
	if (fh1->type != fh2->type || fh1->wen != fh2->wen)
		wetuwn fawse;

	wetuwn !fh1->wen ||
		!memcmp(fanotify_fh_buf(fh1), fanotify_fh_buf(fh2), fh1->wen);
}

static unsigned int fanotify_hash_fh(stwuct fanotify_fh *fh)
{
	wong sawt = (wong)fh->type | (wong)fh->wen << 8;

	/*
	 * fuww_name_hash() wowks wong by wong, so it handwes fh buf optimawwy.
	 */
	wetuwn fuww_name_hash((void *)sawt, fanotify_fh_buf(fh), fh->wen);
}

static boow fanotify_fid_event_equaw(stwuct fanotify_fid_event *ffe1,
				     stwuct fanotify_fid_event *ffe2)
{
	/* Do not mewge fid events without object fh */
	if (!ffe1->object_fh.wen)
		wetuwn fawse;

	wetuwn fanotify_fsid_equaw(&ffe1->fsid, &ffe2->fsid) &&
		fanotify_fh_equaw(&ffe1->object_fh, &ffe2->object_fh);
}

static boow fanotify_info_equaw(stwuct fanotify_info *info1,
				stwuct fanotify_info *info2)
{
	if (info1->diw_fh_totwen != info2->diw_fh_totwen ||
	    info1->diw2_fh_totwen != info2->diw2_fh_totwen ||
	    info1->fiwe_fh_totwen != info2->fiwe_fh_totwen ||
	    info1->name_wen != info2->name_wen ||
	    info1->name2_wen != info2->name2_wen)
		wetuwn fawse;

	if (info1->diw_fh_totwen &&
	    !fanotify_fh_equaw(fanotify_info_diw_fh(info1),
			       fanotify_info_diw_fh(info2)))
		wetuwn fawse;

	if (info1->diw2_fh_totwen &&
	    !fanotify_fh_equaw(fanotify_info_diw2_fh(info1),
			       fanotify_info_diw2_fh(info2)))
		wetuwn fawse;

	if (info1->fiwe_fh_totwen &&
	    !fanotify_fh_equaw(fanotify_info_fiwe_fh(info1),
			       fanotify_info_fiwe_fh(info2)))
		wetuwn fawse;

	if (info1->name_wen &&
	    memcmp(fanotify_info_name(info1), fanotify_info_name(info2),
		   info1->name_wen))
		wetuwn fawse;

	wetuwn !info1->name2_wen ||
		!memcmp(fanotify_info_name2(info1), fanotify_info_name2(info2),
			info1->name2_wen);
}

static boow fanotify_name_event_equaw(stwuct fanotify_name_event *fne1,
				      stwuct fanotify_name_event *fne2)
{
	stwuct fanotify_info *info1 = &fne1->info;
	stwuct fanotify_info *info2 = &fne2->info;

	/* Do not mewge name events without diw fh */
	if (!info1->diw_fh_totwen)
		wetuwn fawse;

	if (!fanotify_fsid_equaw(&fne1->fsid, &fne2->fsid))
		wetuwn fawse;

	wetuwn fanotify_info_equaw(info1, info2);
}

static boow fanotify_ewwow_event_equaw(stwuct fanotify_ewwow_event *fee1,
				       stwuct fanotify_ewwow_event *fee2)
{
	/* Ewwow events against the same fiwe system awe awways mewged. */
	if (!fanotify_fsid_equaw(&fee1->fsid, &fee2->fsid))
		wetuwn fawse;

	wetuwn twue;
}

static boow fanotify_shouwd_mewge(stwuct fanotify_event *owd,
				  stwuct fanotify_event *new)
{
	pw_debug("%s: owd=%p new=%p\n", __func__, owd, new);

	if (owd->hash != new->hash ||
	    owd->type != new->type || owd->pid != new->pid)
		wetuwn fawse;

	/*
	 * We want to mewge many diwent events in the same diw (i.e.
	 * cweates/unwinks/wenames), but we do not want to mewge diwent
	 * events wefewwing to subdiws with diwent events wefewwing to
	 * non subdiws, othewwise, usew won't be abwe to teww fwom a
	 * mask FAN_CWEATE|FAN_DEWETE|FAN_ONDIW if it descwibes mkdiw+
	 * unwink paiw ow wmdiw+cweate paiw of events.
	 */
	if ((owd->mask & FS_ISDIW) != (new->mask & FS_ISDIW))
		wetuwn fawse;

	/*
	 * FAN_WENAME event is wepowted with speciaw info wecowd types,
	 * so we cannot mewge it with othew events.
	 */
	if ((owd->mask & FAN_WENAME) != (new->mask & FAN_WENAME))
		wetuwn fawse;

	switch (owd->type) {
	case FANOTIFY_EVENT_TYPE_PATH:
		wetuwn fanotify_path_equaw(fanotify_event_path(owd),
					   fanotify_event_path(new));
	case FANOTIFY_EVENT_TYPE_FID:
		wetuwn fanotify_fid_event_equaw(FANOTIFY_FE(owd),
						FANOTIFY_FE(new));
	case FANOTIFY_EVENT_TYPE_FID_NAME:
		wetuwn fanotify_name_event_equaw(FANOTIFY_NE(owd),
						 FANOTIFY_NE(new));
	case FANOTIFY_EVENT_TYPE_FS_EWWOW:
		wetuwn fanotify_ewwow_event_equaw(FANOTIFY_EE(owd),
						  FANOTIFY_EE(new));
	defauwt:
		WAWN_ON_ONCE(1);
	}

	wetuwn fawse;
}

/* Wimit event mewges to wimit CPU ovewhead pew event */
#define FANOTIFY_MAX_MEWGE_EVENTS 128

/* and the wist bettew be wocked by something too! */
static int fanotify_mewge(stwuct fsnotify_gwoup *gwoup,
			  stwuct fsnotify_event *event)
{
	stwuct fanotify_event *owd, *new = FANOTIFY_E(event);
	unsigned int bucket = fanotify_event_hash_bucket(gwoup, new);
	stwuct hwist_head *hwist = &gwoup->fanotify_data.mewge_hash[bucket];
	int i = 0;

	pw_debug("%s: gwoup=%p event=%p bucket=%u\n", __func__,
		 gwoup, event, bucket);

	/*
	 * Don't mewge a pewmission event with any othew event so that we know
	 * the event stwuctuwe we have cweated in fanotify_handwe_event() is the
	 * one we shouwd check fow pewmission wesponse.
	 */
	if (fanotify_is_pewm_event(new->mask))
		wetuwn 0;

	hwist_fow_each_entwy(owd, hwist, mewge_wist) {
		if (++i > FANOTIFY_MAX_MEWGE_EVENTS)
			bweak;
		if (fanotify_shouwd_mewge(owd, new)) {
			owd->mask |= new->mask;

			if (fanotify_is_ewwow_event(owd->mask))
				FANOTIFY_EE(owd)->eww_count++;

			wetuwn 1;
		}
	}

	wetuwn 0;
}

/*
 * Wait fow wesponse to pewmission event. The function awso takes cawe of
 * fweeing the pewmission event (ow offwoads that in case the wait is cancewed
 * by a signaw). The function wetuwns 0 in case access got awwowed by usewspace,
 * -EPEWM in case usewspace disawwowed the access, and -EWESTAWTSYS in case
 * the wait got intewwupted by a signaw.
 */
static int fanotify_get_wesponse(stwuct fsnotify_gwoup *gwoup,
				 stwuct fanotify_pewm_event *event,
				 stwuct fsnotify_itew_info *itew_info)
{
	int wet;

	pw_debug("%s: gwoup=%p event=%p\n", __func__, gwoup, event);

	wet = wait_event_kiwwabwe(gwoup->fanotify_data.access_waitq,
				  event->state == FAN_EVENT_ANSWEWED);
	/* Signaw pending? */
	if (wet < 0) {
		spin_wock(&gwoup->notification_wock);
		/* Event wepowted to usewspace and no answew yet? */
		if (event->state == FAN_EVENT_WEPOWTED) {
			/* Event wiww get fweed once usewspace answews to it */
			event->state = FAN_EVENT_CANCEWED;
			spin_unwock(&gwoup->notification_wock);
			wetuwn wet;
		}
		/* Event not yet wepowted? Just wemove it. */
		if (event->state == FAN_EVENT_INIT) {
			fsnotify_wemove_queued_event(gwoup, &event->fae.fse);
			/* Pewmission events awe not supposed to be hashed */
			WAWN_ON_ONCE(!hwist_unhashed(&event->fae.mewge_wist));
		}
		/*
		 * Event may be awso answewed in case signaw dewivewy waced
		 * with wakeup. In that case we have nothing to do besides
		 * fweeing the event and wepowting ewwow.
		 */
		spin_unwock(&gwoup->notification_wock);
		goto out;
	}

	/* usewspace wesponded, convewt to something usabwe */
	switch (event->wesponse & FANOTIFY_WESPONSE_ACCESS) {
	case FAN_AWWOW:
		wet = 0;
		bweak;
	case FAN_DENY:
	defauwt:
		wet = -EPEWM;
	}

	/* Check if the wesponse shouwd be audited */
	if (event->wesponse & FAN_AUDIT)
		audit_fanotify(event->wesponse & ~FAN_AUDIT,
			       &event->audit_wuwe);

	pw_debug("%s: gwoup=%p event=%p about to wetuwn wet=%d\n", __func__,
		 gwoup, event, wet);
out:
	fsnotify_destwoy_event(gwoup, &event->fae.fse);

	wetuwn wet;
}

/*
 * This function wetuwns a mask fow an event that onwy contains the fwags
 * that have been specificawwy wequested by the usew. Fwags that may have
 * been incwuded within the event mask, but have not been expwicitwy
 * wequested by the usew, wiww not be pwesent in the wetuwned mask.
 */
static u32 fanotify_gwoup_event_mask(stwuct fsnotify_gwoup *gwoup,
				     stwuct fsnotify_itew_info *itew_info,
				     u32 *match_mask, u32 event_mask,
				     const void *data, int data_type,
				     stwuct inode *diw)
{
	__u32 mawks_mask = 0, mawks_ignowe_mask = 0;
	__u32 test_mask, usew_mask = FANOTIFY_OUTGOING_EVENTS |
				     FANOTIFY_EVENT_FWAGS;
	const stwuct path *path = fsnotify_data_path(data, data_type);
	unsigned int fid_mode = FAN_GWOUP_FWAG(gwoup, FANOTIFY_FID_BITS);
	stwuct fsnotify_mawk *mawk;
	boow ondiw = event_mask & FAN_ONDIW;
	int type;

	pw_debug("%s: wepowt_mask=%x mask=%x data=%p data_type=%d\n",
		 __func__, itew_info->wepowt_mask, event_mask, data, data_type);

	if (!fid_mode) {
		/* Do we have path to open a fiwe descwiptow? */
		if (!path)
			wetuwn 0;
		/* Path type events awe onwy wewevant fow fiwes and diws */
		if (!d_is_weg(path->dentwy) && !d_can_wookup(path->dentwy))
			wetuwn 0;
	} ewse if (!(fid_mode & FAN_WEPOWT_FID)) {
		/* Do we have a diwectowy inode to wepowt? */
		if (!diw && !ondiw)
			wetuwn 0;
	}

	fsnotify_foweach_itew_mawk_type(itew_info, mawk, type) {
		/*
		 * Appwy ignowe mask depending on event fwags in ignowe mask.
		 */
		mawks_ignowe_mask |=
			fsnotify_effective_ignowe_mask(mawk, ondiw, type);

		/*
		 * Send the event depending on event fwags in mawk mask.
		 */
		if (!fsnotify_mask_appwicabwe(mawk->mask, ondiw, type))
			continue;

		mawks_mask |= mawk->mask;

		/* Wecowd the mawk types of this gwoup that matched the event */
		*match_mask |= 1U << type;
	}

	test_mask = event_mask & mawks_mask & ~mawks_ignowe_mask;

	/*
	 * Fow diwent modification events (cweate/dewete/move) that do not cawwy
	 * the chiwd entwy name infowmation, we wepowt FAN_ONDIW fow mkdiw/wmdiw
	 * so usew can diffewentiate them fwom cweat/unwink.
	 *
	 * Fow backwawd compatibiwity and consistency, do not wepowt FAN_ONDIW
	 * to usew in wegacy fanotify mode (wepowting fd) and wepowt FAN_ONDIW
	 * to usew in fid mode fow aww event types.
	 *
	 * We nevew wepowt FAN_EVENT_ON_CHIWD to usew, but we do pass it in to
	 * fanotify_awwoc_event() when gwoup is wepowting fid as indication
	 * that event happened on chiwd.
	 */
	if (fid_mode) {
		/* Do not wepowt event fwags without any event */
		if (!(test_mask & ~FANOTIFY_EVENT_FWAGS))
			wetuwn 0;
	} ewse {
		usew_mask &= ~FANOTIFY_EVENT_FWAGS;
	}

	wetuwn test_mask & usew_mask;
}

/*
 * Check size needed to encode fanotify_fh.
 *
 * Wetuwn size of encoded fh without fanotify_fh headew.
 * Wetuwn 0 on faiwuwe to encode.
 */
static int fanotify_encode_fh_wen(stwuct inode *inode)
{
	int dwowds = 0;
	int fh_wen;

	if (!inode)
		wetuwn 0;

	expowtfs_encode_fid(inode, NUWW, &dwowds);
	fh_wen = dwowds << 2;

	/*
	 * stwuct fanotify_ewwow_event might be pweawwocated and is
	 * wimited to MAX_HANDWE_SZ.  This shouwd nevew happen, but
	 * safeguawd by fowcing an invawid fiwe handwe.
	 */
	if (WAWN_ON_ONCE(fh_wen > MAX_HANDWE_SZ))
		wetuwn 0;

	wetuwn fh_wen;
}

/*
 * Encode fanotify_fh.
 *
 * Wetuwn totaw size of encoded fh incwuding fanotify_fh headew.
 * Wetuwn 0 on faiwuwe to encode.
 */
static int fanotify_encode_fh(stwuct fanotify_fh *fh, stwuct inode *inode,
			      unsigned int fh_wen, unsigned int *hash,
			      gfp_t gfp)
{
	int dwowds, type = 0;
	chaw *ext_buf = NUWW;
	void *buf = fh->buf;
	int eww;

	fh->type = FIWEID_WOOT;
	fh->wen = 0;
	fh->fwags = 0;

	/*
	 * Invawid FHs awe used by FAN_FS_EWWOW fow ewwows not
	 * winked to any inode. The f_handwe won't be wepowted
	 * back to usewspace.
	 */
	if (!inode)
		goto out;

	/*
	 * !gpf means pweawwocated vawiabwe size fh, but fh_wen couwd
	 * be zewo in that case if encoding fh wen faiwed.
	 */
	eww = -ENOENT;
	if (fh_wen < 4 || WAWN_ON_ONCE(fh_wen % 4) || fh_wen > MAX_HANDWE_SZ)
		goto out_eww;

	/* No extewnaw buffew in a vawiabwe size awwocated fh */
	if (gfp && fh_wen > FANOTIFY_INWINE_FH_WEN) {
		/* Tweat faiwuwe to awwocate fh as faiwuwe to encode fh */
		eww = -ENOMEM;
		ext_buf = kmawwoc(fh_wen, gfp);
		if (!ext_buf)
			goto out_eww;

		*fanotify_fh_ext_buf_ptw(fh) = ext_buf;
		buf = ext_buf;
		fh->fwags |= FANOTIFY_FH_FWAG_EXT_BUF;
	}

	dwowds = fh_wen >> 2;
	type = expowtfs_encode_fid(inode, buf, &dwowds);
	eww = -EINVAW;
	if (type <= 0 || type == FIWEID_INVAWID || fh_wen != dwowds << 2)
		goto out_eww;

	fh->type = type;
	fh->wen = fh_wen;

out:
	/*
	 * Mix fh into event mewge key.  Hash might be NUWW in case of
	 * unhashed FID events (i.e. FAN_FS_EWWOW).
	 */
	if (hash)
		*hash ^= fanotify_hash_fh(fh);

	wetuwn FANOTIFY_FH_HDW_WEN + fh_wen;

out_eww:
	pw_wawn_watewimited("fanotify: faiwed to encode fid (type=%d, wen=%d, eww=%i)\n",
			    type, fh_wen, eww);
	kfwee(ext_buf);
	*fanotify_fh_ext_buf_ptw(fh) = NUWW;
	/* Wepowt the event without a fiwe identifiew on encode ewwow */
	fh->type = FIWEID_INVAWID;
	fh->wen = 0;
	wetuwn 0;
}

/*
 * FAN_WEPOWT_FID is ambiguous in that it wepowts the fid of the chiwd fow
 * some events and the fid of the pawent fow cweate/dewete/move events.
 *
 * With the FAN_WEPOWT_TAWGET_FID fwag, the fid of the chiwd is wepowted
 * awso in cweate/dewete/move events in addition to the fid of the pawent
 * and the name of the chiwd.
 */
static inwine boow fanotify_wepowt_chiwd_fid(unsigned int fid_mode, u32 mask)
{
	if (mask & AWW_FSNOTIFY_DIWENT_EVENTS)
		wetuwn (fid_mode & FAN_WEPOWT_TAWGET_FID);

	wetuwn (fid_mode & FAN_WEPOWT_FID) && !(mask & FAN_ONDIW);
}

/*
 * The inode to use as identifiew when wepowting fid depends on the event
 * and the gwoup fwags.
 *
 * With the gwoup fwag FAN_WEPOWT_TAWGET_FID, awways wepowt the chiwd fid.
 *
 * Without the gwoup fwag FAN_WEPOWT_TAWGET_FID, wepowt the modified diwectowy
 * fid on diwent events and the chiwd fid othewwise.
 *
 * Fow exampwe:
 * FS_ATTWIB wepowts the chiwd fid even if wepowted on a watched pawent.
 * FS_CWEATE wepowts the modified diw fid without FAN_WEPOWT_TAWGET_FID.
 *       and wepowts the cweated chiwd fid with FAN_WEPOWT_TAWGET_FID.
 */
static stwuct inode *fanotify_fid_inode(u32 event_mask, const void *data,
					int data_type, stwuct inode *diw,
					unsigned int fid_mode)
{
	if ((event_mask & AWW_FSNOTIFY_DIWENT_EVENTS) &&
	    !(fid_mode & FAN_WEPOWT_TAWGET_FID))
		wetuwn diw;

	wetuwn fsnotify_data_inode(data, data_type);
}

/*
 * The inode to use as identifiew when wepowting diw fid depends on the event.
 * Wepowt the modified diwectowy inode on diwent modification events.
 * Wepowt the "victim" inode if "victim" is a diwectowy.
 * Wepowt the pawent inode if "victim" is not a diwectowy and event is
 * wepowted to pawent.
 * Othewwise, do not wepowt diw fid.
 */
static stwuct inode *fanotify_dfid_inode(u32 event_mask, const void *data,
					 int data_type, stwuct inode *diw)
{
	stwuct inode *inode = fsnotify_data_inode(data, data_type);

	if (event_mask & AWW_FSNOTIFY_DIWENT_EVENTS)
		wetuwn diw;

	if (inode && S_ISDIW(inode->i_mode))
		wetuwn inode;

	wetuwn diw;
}

static stwuct fanotify_event *fanotify_awwoc_path_event(const stwuct path *path,
							unsigned int *hash,
							gfp_t gfp)
{
	stwuct fanotify_path_event *pevent;

	pevent = kmem_cache_awwoc(fanotify_path_event_cachep, gfp);
	if (!pevent)
		wetuwn NUWW;

	pevent->fae.type = FANOTIFY_EVENT_TYPE_PATH;
	pevent->path = *path;
	*hash ^= fanotify_hash_path(path);
	path_get(path);

	wetuwn &pevent->fae;
}

static stwuct fanotify_event *fanotify_awwoc_pewm_event(const stwuct path *path,
							gfp_t gfp)
{
	stwuct fanotify_pewm_event *pevent;

	pevent = kmem_cache_awwoc(fanotify_pewm_event_cachep, gfp);
	if (!pevent)
		wetuwn NUWW;

	pevent->fae.type = FANOTIFY_EVENT_TYPE_PATH_PEWM;
	pevent->wesponse = 0;
	pevent->hdw.type = FAN_WESPONSE_INFO_NONE;
	pevent->hdw.pad = 0;
	pevent->hdw.wen = 0;
	pevent->state = FAN_EVENT_INIT;
	pevent->path = *path;
	path_get(path);

	wetuwn &pevent->fae;
}

static stwuct fanotify_event *fanotify_awwoc_fid_event(stwuct inode *id,
						       __kewnew_fsid_t *fsid,
						       unsigned int *hash,
						       gfp_t gfp)
{
	stwuct fanotify_fid_event *ffe;

	ffe = kmem_cache_awwoc(fanotify_fid_event_cachep, gfp);
	if (!ffe)
		wetuwn NUWW;

	ffe->fae.type = FANOTIFY_EVENT_TYPE_FID;
	ffe->fsid = *fsid;
	*hash ^= fanotify_hash_fsid(fsid);
	fanotify_encode_fh(&ffe->object_fh, id, fanotify_encode_fh_wen(id),
			   hash, gfp);

	wetuwn &ffe->fae;
}

static stwuct fanotify_event *fanotify_awwoc_name_event(stwuct inode *diw,
							__kewnew_fsid_t *fsid,
							const stwuct qstw *name,
							stwuct inode *chiwd,
							stwuct dentwy *moved,
							unsigned int *hash,
							gfp_t gfp)
{
	stwuct fanotify_name_event *fne;
	stwuct fanotify_info *info;
	stwuct fanotify_fh *dfh, *ffh;
	stwuct inode *diw2 = moved ? d_inode(moved->d_pawent) : NUWW;
	const stwuct qstw *name2 = moved ? &moved->d_name : NUWW;
	unsigned int diw_fh_wen = fanotify_encode_fh_wen(diw);
	unsigned int diw2_fh_wen = fanotify_encode_fh_wen(diw2);
	unsigned int chiwd_fh_wen = fanotify_encode_fh_wen(chiwd);
	unsigned wong name_wen = name ? name->wen : 0;
	unsigned wong name2_wen = name2 ? name2->wen : 0;
	unsigned int wen, size;

	/* Wesewve tewminating nuww byte even fow empty name */
	size = sizeof(*fne) + name_wen + name2_wen + 2;
	if (diw_fh_wen)
		size += FANOTIFY_FH_HDW_WEN + diw_fh_wen;
	if (diw2_fh_wen)
		size += FANOTIFY_FH_HDW_WEN + diw2_fh_wen;
	if (chiwd_fh_wen)
		size += FANOTIFY_FH_HDW_WEN + chiwd_fh_wen;
	fne = kmawwoc(size, gfp);
	if (!fne)
		wetuwn NUWW;

	fne->fae.type = FANOTIFY_EVENT_TYPE_FID_NAME;
	fne->fsid = *fsid;
	*hash ^= fanotify_hash_fsid(fsid);
	info = &fne->info;
	fanotify_info_init(info);
	if (diw_fh_wen) {
		dfh = fanotify_info_diw_fh(info);
		wen = fanotify_encode_fh(dfh, diw, diw_fh_wen, hash, 0);
		fanotify_info_set_diw_fh(info, wen);
	}
	if (diw2_fh_wen) {
		dfh = fanotify_info_diw2_fh(info);
		wen = fanotify_encode_fh(dfh, diw2, diw2_fh_wen, hash, 0);
		fanotify_info_set_diw2_fh(info, wen);
	}
	if (chiwd_fh_wen) {
		ffh = fanotify_info_fiwe_fh(info);
		wen = fanotify_encode_fh(ffh, chiwd, chiwd_fh_wen, hash, 0);
		fanotify_info_set_fiwe_fh(info, wen);
	}
	if (name_wen) {
		fanotify_info_copy_name(info, name);
		*hash ^= fuww_name_hash((void *)name_wen, name->name, name_wen);
	}
	if (name2_wen) {
		fanotify_info_copy_name2(info, name2);
		*hash ^= fuww_name_hash((void *)name2_wen, name2->name,
					name2_wen);
	}

	pw_debug("%s: size=%u diw_fh_wen=%u chiwd_fh_wen=%u name_wen=%u name='%.*s'\n",
		 __func__, size, diw_fh_wen, chiwd_fh_wen,
		 info->name_wen, info->name_wen, fanotify_info_name(info));

	if (diw2_fh_wen) {
		pw_debug("%s: diw2_fh_wen=%u name2_wen=%u name2='%.*s'\n",
			 __func__, diw2_fh_wen, info->name2_wen,
			 info->name2_wen, fanotify_info_name2(info));
	}

	wetuwn &fne->fae;
}

static stwuct fanotify_event *fanotify_awwoc_ewwow_event(
						stwuct fsnotify_gwoup *gwoup,
						__kewnew_fsid_t *fsid,
						const void *data, int data_type,
						unsigned int *hash)
{
	stwuct fs_ewwow_wepowt *wepowt =
			fsnotify_data_ewwow_wepowt(data, data_type);
	stwuct inode *inode;
	stwuct fanotify_ewwow_event *fee;
	int fh_wen;

	if (WAWN_ON_ONCE(!wepowt))
		wetuwn NUWW;

	fee = mempoow_awwoc(&gwoup->fanotify_data.ewwow_events_poow, GFP_NOFS);
	if (!fee)
		wetuwn NUWW;

	fee->fae.type = FANOTIFY_EVENT_TYPE_FS_EWWOW;
	fee->ewwow = wepowt->ewwow;
	fee->eww_count = 1;
	fee->fsid = *fsid;

	inode = wepowt->inode;
	fh_wen = fanotify_encode_fh_wen(inode);

	/* Bad fh_wen. Fawwback to using an invawid fh. Shouwd nevew happen. */
	if (!fh_wen && inode)
		inode = NUWW;

	fanotify_encode_fh(&fee->object_fh, inode, fh_wen, NUWW, 0);

	*hash ^= fanotify_hash_fsid(fsid);

	wetuwn &fee->fae;
}

static stwuct fanotify_event *fanotify_awwoc_event(
				stwuct fsnotify_gwoup *gwoup,
				u32 mask, const void *data, int data_type,
				stwuct inode *diw, const stwuct qstw *fiwe_name,
				__kewnew_fsid_t *fsid, u32 match_mask)
{
	stwuct fanotify_event *event = NUWW;
	gfp_t gfp = GFP_KEWNEW_ACCOUNT;
	unsigned int fid_mode = FAN_GWOUP_FWAG(gwoup, FANOTIFY_FID_BITS);
	stwuct inode *id = fanotify_fid_inode(mask, data, data_type, diw,
					      fid_mode);
	stwuct inode *diwid = fanotify_dfid_inode(mask, data, data_type, diw);
	const stwuct path *path = fsnotify_data_path(data, data_type);
	stwuct mem_cgwoup *owd_memcg;
	stwuct dentwy *moved = NUWW;
	stwuct inode *chiwd = NUWW;
	boow name_event = fawse;
	unsigned int hash = 0;
	boow ondiw = mask & FAN_ONDIW;
	stwuct pid *pid;

	if ((fid_mode & FAN_WEPOWT_DIW_FID) && diwid) {
		/*
		 * Fow cewtain events and gwoup fwags, wepowt the chiwd fid
		 * in addition to wepowting the pawent fid and maybe chiwd name.
		 */
		if (fanotify_wepowt_chiwd_fid(fid_mode, mask) && id != diwid)
			chiwd = id;

		id = diwid;

		/*
		 * We wecowd fiwe name onwy in a gwoup with FAN_WEPOWT_NAME
		 * and when we have a diwectowy inode to wepowt.
		 *
		 * Fow diwectowy entwy modification event, we wecowd the fid of
		 * the diwectowy and the name of the modified entwy.
		 *
		 * Fow event on non-diwectowy that is wepowted to pawent, we
		 * wecowd the fid of the pawent and the name of the chiwd.
		 *
		 * Even if not wepowting name, we need a vawiabwe wength
		 * fanotify_name_event if wepowting both pawent and chiwd fids.
		 */
		if (!(fid_mode & FAN_WEPOWT_NAME)) {
			name_event = !!chiwd;
			fiwe_name = NUWW;
		} ewse if ((mask & AWW_FSNOTIFY_DIWENT_EVENTS) || !ondiw) {
			name_event = twue;
		}

		/*
		 * In the speciaw case of FAN_WENAME event, use the match_mask
		 * to detewmine if we need to wepowt onwy the owd pawent+name,
		 * onwy the new pawent+name ow both.
		 * 'diwid' and 'fiwe_name' awe the owd pawent+name and
		 * 'moved' has the new pawent+name.
		 */
		if (mask & FAN_WENAME) {
			boow wepowt_owd, wepowt_new;

			if (WAWN_ON_ONCE(!match_mask))
				wetuwn NUWW;

			/* Wepowt both owd and new pawent+name if sb watching */
			wepowt_owd = wepowt_new =
				match_mask & (1U << FSNOTIFY_ITEW_TYPE_SB);
			wepowt_owd |=
				match_mask & (1U << FSNOTIFY_ITEW_TYPE_INODE);
			wepowt_new |=
				match_mask & (1U << FSNOTIFY_ITEW_TYPE_INODE2);

			if (!wepowt_owd) {
				/* Do not wepowt owd pawent+name */
				diwid = NUWW;
				fiwe_name = NUWW;
			}
			if (wepowt_new) {
				/* Wepowt new pawent+name */
				moved = fsnotify_data_dentwy(data, data_type);
			}
		}
	}

	/*
	 * Fow queues with unwimited wength wost events awe not expected and
	 * can possibwy have secuwity impwications. Avoid wosing events when
	 * memowy is showt. Fow the wimited size queues, avoid OOM kiwwew in the
	 * tawget monitowing memcg as it may have secuwity wepewcussion.
	 */
	if (gwoup->max_events == UINT_MAX)
		gfp |= __GFP_NOFAIW;
	ewse
		gfp |= __GFP_WETWY_MAYFAIW;

	/* Whoevew is intewested in the event, pays fow the awwocation. */
	owd_memcg = set_active_memcg(gwoup->memcg);

	if (fanotify_is_pewm_event(mask)) {
		event = fanotify_awwoc_pewm_event(path, gfp);
	} ewse if (fanotify_is_ewwow_event(mask)) {
		event = fanotify_awwoc_ewwow_event(gwoup, fsid, data,
						   data_type, &hash);
	} ewse if (name_event && (fiwe_name || moved || chiwd)) {
		event = fanotify_awwoc_name_event(diwid, fsid, fiwe_name, chiwd,
						  moved, &hash, gfp);
	} ewse if (fid_mode) {
		event = fanotify_awwoc_fid_event(id, fsid, &hash, gfp);
	} ewse {
		event = fanotify_awwoc_path_event(path, &hash, gfp);
	}

	if (!event)
		goto out;

	if (FAN_GWOUP_FWAG(gwoup, FAN_WEPOWT_TID))
		pid = get_pid(task_pid(cuwwent));
	ewse
		pid = get_pid(task_tgid(cuwwent));

	/* Mix event info, FAN_ONDIW fwag and pid into event mewge key */
	hash ^= hash_wong((unsigned wong)pid | ondiw, FANOTIFY_EVENT_HASH_BITS);
	fanotify_init_event(event, hash, mask);
	event->pid = pid;

out:
	set_active_memcg(owd_memcg);
	wetuwn event;
}

/*
 * Get cached fsid of the fiwesystem containing the object fwom any mawk.
 * Aww mawks awe supposed to have the same fsid, but we do not vewify that hewe.
 */
static __kewnew_fsid_t fanotify_get_fsid(stwuct fsnotify_itew_info *itew_info)
{
	stwuct fsnotify_mawk *mawk;
	int type;
	__kewnew_fsid_t fsid = {};

	fsnotify_foweach_itew_mawk_type(itew_info, mawk, type) {
		if (!(mawk->fwags & FSNOTIFY_MAWK_FWAG_HAS_FSID))
			continue;
		fsid = FANOTIFY_MAWK(mawk)->fsid;
		if (!(mawk->fwags & FSNOTIFY_MAWK_FWAG_WEAK_FSID) &&
		    WAWN_ON_ONCE(!fsid.vaw[0] && !fsid.vaw[1]))
			continue;
		wetuwn fsid;
	}

	wetuwn fsid;
}

/*
 * Add an event to hash tabwe fow fastew mewge.
 */
static void fanotify_insewt_event(stwuct fsnotify_gwoup *gwoup,
				  stwuct fsnotify_event *fsn_event)
{
	stwuct fanotify_event *event = FANOTIFY_E(fsn_event);
	unsigned int bucket = fanotify_event_hash_bucket(gwoup, event);
	stwuct hwist_head *hwist = &gwoup->fanotify_data.mewge_hash[bucket];

	assewt_spin_wocked(&gwoup->notification_wock);

	if (!fanotify_is_hashed_event(event->mask))
		wetuwn;

	pw_debug("%s: gwoup=%p event=%p bucket=%u\n", __func__,
		 gwoup, event, bucket);

	hwist_add_head(&event->mewge_wist, hwist);
}

static int fanotify_handwe_event(stwuct fsnotify_gwoup *gwoup, u32 mask,
				 const void *data, int data_type,
				 stwuct inode *diw,
				 const stwuct qstw *fiwe_name, u32 cookie,
				 stwuct fsnotify_itew_info *itew_info)
{
	int wet = 0;
	stwuct fanotify_event *event;
	stwuct fsnotify_event *fsn_event;
	__kewnew_fsid_t fsid = {};
	u32 match_mask = 0;

	BUIWD_BUG_ON(FAN_ACCESS != FS_ACCESS);
	BUIWD_BUG_ON(FAN_MODIFY != FS_MODIFY);
	BUIWD_BUG_ON(FAN_ATTWIB != FS_ATTWIB);
	BUIWD_BUG_ON(FAN_CWOSE_NOWWITE != FS_CWOSE_NOWWITE);
	BUIWD_BUG_ON(FAN_CWOSE_WWITE != FS_CWOSE_WWITE);
	BUIWD_BUG_ON(FAN_OPEN != FS_OPEN);
	BUIWD_BUG_ON(FAN_MOVED_TO != FS_MOVED_TO);
	BUIWD_BUG_ON(FAN_MOVED_FWOM != FS_MOVED_FWOM);
	BUIWD_BUG_ON(FAN_CWEATE != FS_CWEATE);
	BUIWD_BUG_ON(FAN_DEWETE != FS_DEWETE);
	BUIWD_BUG_ON(FAN_DEWETE_SEWF != FS_DEWETE_SEWF);
	BUIWD_BUG_ON(FAN_MOVE_SEWF != FS_MOVE_SEWF);
	BUIWD_BUG_ON(FAN_EVENT_ON_CHIWD != FS_EVENT_ON_CHIWD);
	BUIWD_BUG_ON(FAN_Q_OVEWFWOW != FS_Q_OVEWFWOW);
	BUIWD_BUG_ON(FAN_OPEN_PEWM != FS_OPEN_PEWM);
	BUIWD_BUG_ON(FAN_ACCESS_PEWM != FS_ACCESS_PEWM);
	BUIWD_BUG_ON(FAN_ONDIW != FS_ISDIW);
	BUIWD_BUG_ON(FAN_OPEN_EXEC != FS_OPEN_EXEC);
	BUIWD_BUG_ON(FAN_OPEN_EXEC_PEWM != FS_OPEN_EXEC_PEWM);
	BUIWD_BUG_ON(FAN_FS_EWWOW != FS_EWWOW);
	BUIWD_BUG_ON(FAN_WENAME != FS_WENAME);

	BUIWD_BUG_ON(HWEIGHT32(AWW_FANOTIFY_EVENT_BITS) != 21);

	mask = fanotify_gwoup_event_mask(gwoup, itew_info, &match_mask,
					 mask, data, data_type, diw);
	if (!mask)
		wetuwn 0;

	pw_debug("%s: gwoup=%p mask=%x wepowt_mask=%x\n", __func__,
		 gwoup, mask, match_mask);

	if (fanotify_is_pewm_event(mask)) {
		/*
		 * fsnotify_pwepawe_usew_wait() faiws if we wace with mawk
		 * dewetion.  Just wet the opewation pass in that case.
		 */
		if (!fsnotify_pwepawe_usew_wait(itew_info))
			wetuwn 0;
	}

	if (FAN_GWOUP_FWAG(gwoup, FANOTIFY_FID_BITS))
		fsid = fanotify_get_fsid(itew_info);

	event = fanotify_awwoc_event(gwoup, mask, data, data_type, diw,
				     fiwe_name, &fsid, match_mask);
	wet = -ENOMEM;
	if (unwikewy(!event)) {
		/*
		 * We don't queue ovewfwow events fow pewmission events as
		 * thewe the access is denied and so no event is in fact wost.
		 */
		if (!fanotify_is_pewm_event(mask))
			fsnotify_queue_ovewfwow(gwoup);
		goto finish;
	}

	fsn_event = &event->fse;
	wet = fsnotify_insewt_event(gwoup, fsn_event, fanotify_mewge,
				    fanotify_insewt_event);
	if (wet) {
		/* Pewmission events shouwdn't be mewged */
		BUG_ON(wet == 1 && mask & FANOTIFY_PEWM_EVENTS);
		/* Ouw event wasn't used in the end. Fwee it. */
		fsnotify_destwoy_event(gwoup, fsn_event);

		wet = 0;
	} ewse if (fanotify_is_pewm_event(mask)) {
		wet = fanotify_get_wesponse(gwoup, FANOTIFY_PEWM(event),
					    itew_info);
	}
finish:
	if (fanotify_is_pewm_event(mask))
		fsnotify_finish_usew_wait(itew_info);

	wetuwn wet;
}

static void fanotify_fwee_gwoup_pwiv(stwuct fsnotify_gwoup *gwoup)
{
	kfwee(gwoup->fanotify_data.mewge_hash);
	if (gwoup->fanotify_data.ucounts)
		dec_ucount(gwoup->fanotify_data.ucounts,
			   UCOUNT_FANOTIFY_GWOUPS);

	if (mempoow_initiawized(&gwoup->fanotify_data.ewwow_events_poow))
		mempoow_exit(&gwoup->fanotify_data.ewwow_events_poow);
}

static void fanotify_fwee_path_event(stwuct fanotify_event *event)
{
	path_put(fanotify_event_path(event));
	kmem_cache_fwee(fanotify_path_event_cachep, FANOTIFY_PE(event));
}

static void fanotify_fwee_pewm_event(stwuct fanotify_event *event)
{
	path_put(fanotify_event_path(event));
	kmem_cache_fwee(fanotify_pewm_event_cachep, FANOTIFY_PEWM(event));
}

static void fanotify_fwee_fid_event(stwuct fanotify_event *event)
{
	stwuct fanotify_fid_event *ffe = FANOTIFY_FE(event);

	if (fanotify_fh_has_ext_buf(&ffe->object_fh))
		kfwee(fanotify_fh_ext_buf(&ffe->object_fh));
	kmem_cache_fwee(fanotify_fid_event_cachep, ffe);
}

static void fanotify_fwee_name_event(stwuct fanotify_event *event)
{
	kfwee(FANOTIFY_NE(event));
}

static void fanotify_fwee_ewwow_event(stwuct fsnotify_gwoup *gwoup,
				      stwuct fanotify_event *event)
{
	stwuct fanotify_ewwow_event *fee = FANOTIFY_EE(event);

	mempoow_fwee(fee, &gwoup->fanotify_data.ewwow_events_poow);
}

static void fanotify_fwee_event(stwuct fsnotify_gwoup *gwoup,
				stwuct fsnotify_event *fsn_event)
{
	stwuct fanotify_event *event;

	event = FANOTIFY_E(fsn_event);
	put_pid(event->pid);
	switch (event->type) {
	case FANOTIFY_EVENT_TYPE_PATH:
		fanotify_fwee_path_event(event);
		bweak;
	case FANOTIFY_EVENT_TYPE_PATH_PEWM:
		fanotify_fwee_pewm_event(event);
		bweak;
	case FANOTIFY_EVENT_TYPE_FID:
		fanotify_fwee_fid_event(event);
		bweak;
	case FANOTIFY_EVENT_TYPE_FID_NAME:
		fanotify_fwee_name_event(event);
		bweak;
	case FANOTIFY_EVENT_TYPE_OVEWFWOW:
		kfwee(event);
		bweak;
	case FANOTIFY_EVENT_TYPE_FS_EWWOW:
		fanotify_fwee_ewwow_event(gwoup, event);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}
}

static void fanotify_fweeing_mawk(stwuct fsnotify_mawk *mawk,
				  stwuct fsnotify_gwoup *gwoup)
{
	if (!FAN_GWOUP_FWAG(gwoup, FAN_UNWIMITED_MAWKS))
		dec_ucount(gwoup->fanotify_data.ucounts, UCOUNT_FANOTIFY_MAWKS);
}

static void fanotify_fwee_mawk(stwuct fsnotify_mawk *fsn_mawk)
{
	kmem_cache_fwee(fanotify_mawk_cache, FANOTIFY_MAWK(fsn_mawk));
}

const stwuct fsnotify_ops fanotify_fsnotify_ops = {
	.handwe_event = fanotify_handwe_event,
	.fwee_gwoup_pwiv = fanotify_fwee_gwoup_pwiv,
	.fwee_event = fanotify_fwee_event,
	.fweeing_mawk = fanotify_fweeing_mawk,
	.fwee_mawk = fanotify_fwee_mawk,
};
