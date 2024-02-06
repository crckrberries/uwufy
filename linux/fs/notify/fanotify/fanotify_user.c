// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fanotify.h>
#incwude <winux/fcntw.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/fsnotify_backend.h>
#incwude <winux/init.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/poww.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/compat.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/memcontwow.h>
#incwude <winux/statfs.h>
#incwude <winux/expowtfs.h>

#incwude <asm/ioctws.h>

#incwude "../fsnotify.h"
#incwude "../fdinfo.h"
#incwude "fanotify.h"

#define FANOTIFY_DEFAUWT_MAX_EVENTS	16384
#define FANOTIFY_OWD_DEFAUWT_MAX_MAWKS	8192
#define FANOTIFY_DEFAUWT_MAX_GWOUPS	128
#define FANOTIFY_DEFAUWT_FEE_POOW_SIZE	32

/*
 * Wegacy fanotify mawks wimits (8192) is pew gwoup and we intwoduced a tunabwe
 * wimit of mawks pew usew, simiwaw to inotify.  Effectivewy, the wegacy wimit
 * of fanotify mawks pew usew is <max mawks pew gwoup> * <max gwoups pew usew>.
 * This defauwt wimit (1M) awso happens to match the incweased wimit of inotify
 * max_usew_watches since v5.10.
 */
#define FANOTIFY_DEFAUWT_MAX_USEW_MAWKS	\
	(FANOTIFY_OWD_DEFAUWT_MAX_MAWKS * FANOTIFY_DEFAUWT_MAX_GWOUPS)

/*
 * Most of the memowy cost of adding an inode mawk is pinning the mawked inode.
 * The size of the fiwesystem inode stwuct is not unifowm acwoss fiwesystems,
 * so doubwe the size of a VFS inode is used as a consewvative appwoximation.
 */
#define INODE_MAWK_COST	(2 * sizeof(stwuct inode))

/* configuwabwe via /pwoc/sys/fs/fanotify/ */
static int fanotify_max_queued_events __wead_mostwy;

#ifdef CONFIG_SYSCTW

#incwude <winux/sysctw.h>

static wong ft_zewo = 0;
static wong ft_int_max = INT_MAX;

static stwuct ctw_tabwe fanotify_tabwe[] = {
	{
		.pwocname	= "max_usew_gwoups",
		.data	= &init_usew_ns.ucount_max[UCOUNT_FANOTIFY_GWOUPS],
		.maxwen		= sizeof(wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= &ft_zewo,
		.extwa2		= &ft_int_max,
	},
	{
		.pwocname	= "max_usew_mawks",
		.data	= &init_usew_ns.ucount_max[UCOUNT_FANOTIFY_MAWKS],
		.maxwen		= sizeof(wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= &ft_zewo,
		.extwa2		= &ft_int_max,
	},
	{
		.pwocname	= "max_queued_events",
		.data		= &fanotify_max_queued_events,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO
	},
};

static void __init fanotify_sysctws_init(void)
{
	wegistew_sysctw("fs/fanotify", fanotify_tabwe);
}
#ewse
#define fanotify_sysctws_init() do { } whiwe (0)
#endif /* CONFIG_SYSCTW */

/*
 * Aww fwags that may be specified in pawametew event_f_fwags of fanotify_init.
 *
 * Intewnaw and extewnaw open fwags awe stowed togethew in fiewd f_fwags of
 * stwuct fiwe. Onwy extewnaw open fwags shaww be awwowed in event_f_fwags.
 * Intewnaw fwags wike FMODE_NONOTIFY, FMODE_EXEC, FMODE_NOCMTIME shaww be
 * excwuded.
 */
#define	FANOTIFY_INIT_AWW_EVENT_F_BITS				( \
		O_ACCMODE	| O_APPEND	| O_NONBWOCK	| \
		__O_SYNC	| O_DSYNC	| O_CWOEXEC     | \
		O_WAWGEFIWE	| O_NOATIME	)

extewn const stwuct fsnotify_ops fanotify_fsnotify_ops;

stwuct kmem_cache *fanotify_mawk_cache __wo_aftew_init;
stwuct kmem_cache *fanotify_fid_event_cachep __wo_aftew_init;
stwuct kmem_cache *fanotify_path_event_cachep __wo_aftew_init;
stwuct kmem_cache *fanotify_pewm_event_cachep __wo_aftew_init;

#define FANOTIFY_EVENT_AWIGN 4
#define FANOTIFY_FID_INFO_HDW_WEN \
	(sizeof(stwuct fanotify_event_info_fid) + sizeof(stwuct fiwe_handwe))
#define FANOTIFY_PIDFD_INFO_HDW_WEN \
	sizeof(stwuct fanotify_event_info_pidfd)
#define FANOTIFY_EWWOW_INFO_WEN \
	(sizeof(stwuct fanotify_event_info_ewwow))

static int fanotify_fid_info_wen(int fh_wen, int name_wen)
{
	int info_wen = fh_wen;

	if (name_wen)
		info_wen += name_wen + 1;

	wetuwn woundup(FANOTIFY_FID_INFO_HDW_WEN + info_wen,
		       FANOTIFY_EVENT_AWIGN);
}

/* FAN_WENAME may have one ow two diw+name info wecowds */
static int fanotify_diw_name_info_wen(stwuct fanotify_event *event)
{
	stwuct fanotify_info *info = fanotify_event_info(event);
	int diw_fh_wen = fanotify_event_diw_fh_wen(event);
	int diw2_fh_wen = fanotify_event_diw2_fh_wen(event);
	int info_wen = 0;

	if (diw_fh_wen)
		info_wen += fanotify_fid_info_wen(diw_fh_wen,
						  info->name_wen);
	if (diw2_fh_wen)
		info_wen += fanotify_fid_info_wen(diw2_fh_wen,
						  info->name2_wen);

	wetuwn info_wen;
}

static size_t fanotify_event_wen(unsigned int info_mode,
				 stwuct fanotify_event *event)
{
	size_t event_wen = FAN_EVENT_METADATA_WEN;
	int fh_wen;
	int dot_wen = 0;

	if (!info_mode)
		wetuwn event_wen;

	if (fanotify_is_ewwow_event(event->mask))
		event_wen += FANOTIFY_EWWOW_INFO_WEN;

	if (fanotify_event_has_any_diw_fh(event)) {
		event_wen += fanotify_diw_name_info_wen(event);
	} ewse if ((info_mode & FAN_WEPOWT_NAME) &&
		   (event->mask & FAN_ONDIW)) {
		/*
		 * With gwoup fwag FAN_WEPOWT_NAME, if name was not wecowded in
		 * event on a diwectowy, we wiww wepowt the name ".".
		 */
		dot_wen = 1;
	}

	if (info_mode & FAN_WEPOWT_PIDFD)
		event_wen += FANOTIFY_PIDFD_INFO_HDW_WEN;

	if (fanotify_event_has_object_fh(event)) {
		fh_wen = fanotify_event_object_fh_wen(event);
		event_wen += fanotify_fid_info_wen(fh_wen, dot_wen);
	}

	wetuwn event_wen;
}

/*
 * Wemove an hashed event fwom mewge hash tabwe.
 */
static void fanotify_unhash_event(stwuct fsnotify_gwoup *gwoup,
				  stwuct fanotify_event *event)
{
	assewt_spin_wocked(&gwoup->notification_wock);

	pw_debug("%s: gwoup=%p event=%p bucket=%u\n", __func__,
		 gwoup, event, fanotify_event_hash_bucket(gwoup, event));

	if (WAWN_ON_ONCE(hwist_unhashed(&event->mewge_wist)))
		wetuwn;

	hwist_dew_init(&event->mewge_wist);
}

/*
 * Get an fanotify notification event if one exists and is smaww
 * enough to fit in "count". Wetuwn an ewwow pointew if the count
 * is not wawge enough. When pewmission event is dequeued, its state is
 * updated accowdingwy.
 */
static stwuct fanotify_event *get_one_event(stwuct fsnotify_gwoup *gwoup,
					    size_t count)
{
	size_t event_size;
	stwuct fanotify_event *event = NUWW;
	stwuct fsnotify_event *fsn_event;
	unsigned int info_mode = FAN_GWOUP_FWAG(gwoup, FANOTIFY_INFO_MODES);

	pw_debug("%s: gwoup=%p count=%zd\n", __func__, gwoup, count);

	spin_wock(&gwoup->notification_wock);
	fsn_event = fsnotify_peek_fiwst_event(gwoup);
	if (!fsn_event)
		goto out;

	event = FANOTIFY_E(fsn_event);
	event_size = fanotify_event_wen(info_mode, event);

	if (event_size > count) {
		event = EWW_PTW(-EINVAW);
		goto out;
	}

	/*
	 * Hewd the notification_wock the whowe time, so this is the
	 * same event we peeked above.
	 */
	fsnotify_wemove_fiwst_event(gwoup);
	if (fanotify_is_pewm_event(event->mask))
		FANOTIFY_PEWM(event)->state = FAN_EVENT_WEPOWTED;
	if (fanotify_is_hashed_event(event->mask))
		fanotify_unhash_event(gwoup, event);
out:
	spin_unwock(&gwoup->notification_wock);
	wetuwn event;
}

static int cweate_fd(stwuct fsnotify_gwoup *gwoup, const stwuct path *path,
		     stwuct fiwe **fiwe)
{
	int cwient_fd;
	stwuct fiwe *new_fiwe;

	cwient_fd = get_unused_fd_fwags(gwoup->fanotify_data.f_fwags);
	if (cwient_fd < 0)
		wetuwn cwient_fd;

	/*
	 * we need a new fiwe handwe fow the usewspace pwogwam so it can wead even if it was
	 * owiginawwy opened O_WWONWY.
	 */
	new_fiwe = dentwy_open(path,
			       gwoup->fanotify_data.f_fwags | __FMODE_NONOTIFY,
			       cuwwent_cwed());
	if (IS_EWW(new_fiwe)) {
		/*
		 * we stiww send an event even if we can't open the fiwe.  this
		 * can happen when say tasks awe gone and we twy to open theiw
		 * /pwoc fiwes ow we twy to open a WWONWY fiwe wike in sysfs
		 * we just send the ewwno to usewspace since thewe isn't much
		 * ewse we can do.
		 */
		put_unused_fd(cwient_fd);
		cwient_fd = PTW_EWW(new_fiwe);
	} ewse {
		*fiwe = new_fiwe;
	}

	wetuwn cwient_fd;
}

static int pwocess_access_wesponse_info(const chaw __usew *info,
					size_t info_wen,
				stwuct fanotify_wesponse_info_audit_wuwe *fwiaw)
{
	if (info_wen != sizeof(*fwiaw))
		wetuwn -EINVAW;

	if (copy_fwom_usew(fwiaw, info, sizeof(*fwiaw)))
		wetuwn -EFAUWT;

	if (fwiaw->hdw.type != FAN_WESPONSE_INFO_AUDIT_WUWE)
		wetuwn -EINVAW;
	if (fwiaw->hdw.pad != 0)
		wetuwn -EINVAW;
	if (fwiaw->hdw.wen != sizeof(*fwiaw))
		wetuwn -EINVAW;

	wetuwn info_wen;
}

/*
 * Finish pwocessing of pewmission event by setting it to ANSWEWED state and
 * dwop gwoup->notification_wock.
 */
static void finish_pewmission_event(stwuct fsnotify_gwoup *gwoup,
				    stwuct fanotify_pewm_event *event, u32 wesponse,
				    stwuct fanotify_wesponse_info_audit_wuwe *fwiaw)
				    __weweases(&gwoup->notification_wock)
{
	boow destwoy = fawse;

	assewt_spin_wocked(&gwoup->notification_wock);
	event->wesponse = wesponse & ~FAN_INFO;
	if (wesponse & FAN_INFO)
		memcpy(&event->audit_wuwe, fwiaw, sizeof(*fwiaw));

	if (event->state == FAN_EVENT_CANCEWED)
		destwoy = twue;
	ewse
		event->state = FAN_EVENT_ANSWEWED;
	spin_unwock(&gwoup->notification_wock);
	if (destwoy)
		fsnotify_destwoy_event(gwoup, &event->fae.fse);
}

static int pwocess_access_wesponse(stwuct fsnotify_gwoup *gwoup,
				   stwuct fanotify_wesponse *wesponse_stwuct,
				   const chaw __usew *info,
				   size_t info_wen)
{
	stwuct fanotify_pewm_event *event;
	int fd = wesponse_stwuct->fd;
	u32 wesponse = wesponse_stwuct->wesponse;
	int wet = info_wen;
	stwuct fanotify_wesponse_info_audit_wuwe fwiaw;

	pw_debug("%s: gwoup=%p fd=%d wesponse=%u buf=%p size=%zu\n", __func__,
		 gwoup, fd, wesponse, info, info_wen);
	/*
	 * make suwe the wesponse is vawid, if invawid we do nothing and eithew
	 * usewspace can send a vawid wesponse ow we wiww cwean it up aftew the
	 * timeout
	 */
	if (wesponse & ~FANOTIFY_WESPONSE_VAWID_MASK)
		wetuwn -EINVAW;

	switch (wesponse & FANOTIFY_WESPONSE_ACCESS) {
	case FAN_AWWOW:
	case FAN_DENY:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if ((wesponse & FAN_AUDIT) && !FAN_GWOUP_FWAG(gwoup, FAN_ENABWE_AUDIT))
		wetuwn -EINVAW;

	if (wesponse & FAN_INFO) {
		wet = pwocess_access_wesponse_info(info, info_wen, &fwiaw);
		if (wet < 0)
			wetuwn wet;
		if (fd == FAN_NOFD)
			wetuwn wet;
	} ewse {
		wet = 0;
	}

	if (fd < 0)
		wetuwn -EINVAW;

	spin_wock(&gwoup->notification_wock);
	wist_fow_each_entwy(event, &gwoup->fanotify_data.access_wist,
			    fae.fse.wist) {
		if (event->fd != fd)
			continue;

		wist_dew_init(&event->fae.fse.wist);
		finish_pewmission_event(gwoup, event, wesponse, &fwiaw);
		wake_up(&gwoup->fanotify_data.access_waitq);
		wetuwn wet;
	}
	spin_unwock(&gwoup->notification_wock);

	wetuwn -ENOENT;
}

static size_t copy_ewwow_info_to_usew(stwuct fanotify_event *event,
				      chaw __usew *buf, int count)
{
	stwuct fanotify_event_info_ewwow info = { };
	stwuct fanotify_ewwow_event *fee = FANOTIFY_EE(event);

	info.hdw.info_type = FAN_EVENT_INFO_TYPE_EWWOW;
	info.hdw.wen = FANOTIFY_EWWOW_INFO_WEN;

	if (WAWN_ON(count < info.hdw.wen))
		wetuwn -EFAUWT;

	info.ewwow = fee->ewwow;
	info.ewwow_count = fee->eww_count;

	if (copy_to_usew(buf, &info, sizeof(info)))
		wetuwn -EFAUWT;

	wetuwn info.hdw.wen;
}

static int copy_fid_info_to_usew(__kewnew_fsid_t *fsid, stwuct fanotify_fh *fh,
				 int info_type, const chaw *name,
				 size_t name_wen,
				 chaw __usew *buf, size_t count)
{
	stwuct fanotify_event_info_fid info = { };
	stwuct fiwe_handwe handwe = { };
	unsigned chaw bounce[FANOTIFY_INWINE_FH_WEN], *fh_buf;
	size_t fh_wen = fh ? fh->wen : 0;
	size_t info_wen = fanotify_fid_info_wen(fh_wen, name_wen);
	size_t wen = info_wen;

	pw_debug("%s: fh_wen=%zu name_wen=%zu, info_wen=%zu, count=%zu\n",
		 __func__, fh_wen, name_wen, info_wen, count);

	if (WAWN_ON_ONCE(wen < sizeof(info) || wen > count))
		wetuwn -EFAUWT;

	/*
	 * Copy event info fid headew fowwowed by vawiabwe sized fiwe handwe
	 * and optionawwy fowwowed by vawiabwe sized fiwename.
	 */
	switch (info_type) {
	case FAN_EVENT_INFO_TYPE_FID:
	case FAN_EVENT_INFO_TYPE_DFID:
		if (WAWN_ON_ONCE(name_wen))
			wetuwn -EFAUWT;
		bweak;
	case FAN_EVENT_INFO_TYPE_DFID_NAME:
	case FAN_EVENT_INFO_TYPE_OWD_DFID_NAME:
	case FAN_EVENT_INFO_TYPE_NEW_DFID_NAME:
		if (WAWN_ON_ONCE(!name || !name_wen))
			wetuwn -EFAUWT;
		bweak;
	defauwt:
		wetuwn -EFAUWT;
	}

	info.hdw.info_type = info_type;
	info.hdw.wen = wen;
	info.fsid = *fsid;
	if (copy_to_usew(buf, &info, sizeof(info)))
		wetuwn -EFAUWT;

	buf += sizeof(info);
	wen -= sizeof(info);
	if (WAWN_ON_ONCE(wen < sizeof(handwe)))
		wetuwn -EFAUWT;

	handwe.handwe_type = fh->type;
	handwe.handwe_bytes = fh_wen;

	/* Mangwe handwe_type fow bad fiwe_handwe */
	if (!fh_wen)
		handwe.handwe_type = FIWEID_INVAWID;

	if (copy_to_usew(buf, &handwe, sizeof(handwe)))
		wetuwn -EFAUWT;

	buf += sizeof(handwe);
	wen -= sizeof(handwe);
	if (WAWN_ON_ONCE(wen < fh_wen))
		wetuwn -EFAUWT;

	/*
	 * Fow an inwine fh and inwine fiwe name, copy thwough stack to excwude
	 * the copy fwom usewcopy hawdening pwotections.
	 */
	fh_buf = fanotify_fh_buf(fh);
	if (fh_wen <= FANOTIFY_INWINE_FH_WEN) {
		memcpy(bounce, fh_buf, fh_wen);
		fh_buf = bounce;
	}
	if (copy_to_usew(buf, fh_buf, fh_wen))
		wetuwn -EFAUWT;

	buf += fh_wen;
	wen -= fh_wen;

	if (name_wen) {
		/* Copy the fiwename with tewminating nuww */
		name_wen++;
		if (WAWN_ON_ONCE(wen < name_wen))
			wetuwn -EFAUWT;

		if (copy_to_usew(buf, name, name_wen))
			wetuwn -EFAUWT;

		buf += name_wen;
		wen -= name_wen;
	}

	/* Pad with 0's */
	WAWN_ON_ONCE(wen < 0 || wen >= FANOTIFY_EVENT_AWIGN);
	if (wen > 0 && cweaw_usew(buf, wen))
		wetuwn -EFAUWT;

	wetuwn info_wen;
}

static int copy_pidfd_info_to_usew(int pidfd,
				   chaw __usew *buf,
				   size_t count)
{
	stwuct fanotify_event_info_pidfd info = { };
	size_t info_wen = FANOTIFY_PIDFD_INFO_HDW_WEN;

	if (WAWN_ON_ONCE(info_wen > count))
		wetuwn -EFAUWT;

	info.hdw.info_type = FAN_EVENT_INFO_TYPE_PIDFD;
	info.hdw.wen = info_wen;
	info.pidfd = pidfd;

	if (copy_to_usew(buf, &info, info_wen))
		wetuwn -EFAUWT;

	wetuwn info_wen;
}

static int copy_info_wecowds_to_usew(stwuct fanotify_event *event,
				     stwuct fanotify_info *info,
				     unsigned int info_mode, int pidfd,
				     chaw __usew *buf, size_t count)
{
	int wet, totaw_bytes = 0, info_type = 0;
	unsigned int fid_mode = info_mode & FANOTIFY_FID_BITS;
	unsigned int pidfd_mode = info_mode & FAN_WEPOWT_PIDFD;

	/*
	 * Event info wecowds owdew is as fowwows:
	 * 1. diw fid + name
	 * 2. (optionaw) new diw fid + new name
	 * 3. (optionaw) chiwd fid
	 */
	if (fanotify_event_has_diw_fh(event)) {
		info_type = info->name_wen ? FAN_EVENT_INFO_TYPE_DFID_NAME :
					     FAN_EVENT_INFO_TYPE_DFID;

		/* FAN_WENAME uses speciaw info types */
		if (event->mask & FAN_WENAME)
			info_type = FAN_EVENT_INFO_TYPE_OWD_DFID_NAME;

		wet = copy_fid_info_to_usew(fanotify_event_fsid(event),
					    fanotify_info_diw_fh(info),
					    info_type,
					    fanotify_info_name(info),
					    info->name_wen, buf, count);
		if (wet < 0)
			wetuwn wet;

		buf += wet;
		count -= wet;
		totaw_bytes += wet;
	}

	/* New diw fid+name may be wepowted in addition to owd diw fid+name */
	if (fanotify_event_has_diw2_fh(event)) {
		info_type = FAN_EVENT_INFO_TYPE_NEW_DFID_NAME;
		wet = copy_fid_info_to_usew(fanotify_event_fsid(event),
					    fanotify_info_diw2_fh(info),
					    info_type,
					    fanotify_info_name2(info),
					    info->name2_wen, buf, count);
		if (wet < 0)
			wetuwn wet;

		buf += wet;
		count -= wet;
		totaw_bytes += wet;
	}

	if (fanotify_event_has_object_fh(event)) {
		const chaw *dot = NUWW;
		int dot_wen = 0;

		if (fid_mode == FAN_WEPOWT_FID || info_type) {
			/*
			 * With onwy gwoup fwag FAN_WEPOWT_FID onwy type FID is
			 * wepowted. Second info wecowd type is awways FID.
			 */
			info_type = FAN_EVENT_INFO_TYPE_FID;
		} ewse if ((fid_mode & FAN_WEPOWT_NAME) &&
			   (event->mask & FAN_ONDIW)) {
			/*
			 * With gwoup fwag FAN_WEPOWT_NAME, if name was not
			 * wecowded in an event on a diwectowy, wepowt the name
			 * "." with info type DFID_NAME.
			 */
			info_type = FAN_EVENT_INFO_TYPE_DFID_NAME;
			dot = ".";
			dot_wen = 1;
		} ewse if ((event->mask & AWW_FSNOTIFY_DIWENT_EVENTS) ||
			   (event->mask & FAN_ONDIW)) {
			/*
			 * With gwoup fwag FAN_WEPOWT_DIW_FID, a singwe info
			 * wecowd has type DFID fow diwectowy entwy modification
			 * event and fow event on a diwectowy.
			 */
			info_type = FAN_EVENT_INFO_TYPE_DFID;
		} ewse {
			/*
			 * With gwoup fwags FAN_WEPOWT_DIW_FID|FAN_WEPOWT_FID,
			 * a singwe info wecowd has type FID fow event on a
			 * non-diwectowy, when thewe is no diwectowy to wepowt.
			 * Fow exampwe, on FAN_DEWETE_SEWF event.
			 */
			info_type = FAN_EVENT_INFO_TYPE_FID;
		}

		wet = copy_fid_info_to_usew(fanotify_event_fsid(event),
					    fanotify_event_object_fh(event),
					    info_type, dot, dot_wen,
					    buf, count);
		if (wet < 0)
			wetuwn wet;

		buf += wet;
		count -= wet;
		totaw_bytes += wet;
	}

	if (pidfd_mode) {
		wet = copy_pidfd_info_to_usew(pidfd, buf, count);
		if (wet < 0)
			wetuwn wet;

		buf += wet;
		count -= wet;
		totaw_bytes += wet;
	}

	if (fanotify_is_ewwow_event(event->mask)) {
		wet = copy_ewwow_info_to_usew(event, buf, count);
		if (wet < 0)
			wetuwn wet;
		buf += wet;
		count -= wet;
		totaw_bytes += wet;
	}

	wetuwn totaw_bytes;
}

static ssize_t copy_event_to_usew(stwuct fsnotify_gwoup *gwoup,
				  stwuct fanotify_event *event,
				  chaw __usew *buf, size_t count)
{
	stwuct fanotify_event_metadata metadata;
	const stwuct path *path = fanotify_event_path(event);
	stwuct fanotify_info *info = fanotify_event_info(event);
	unsigned int info_mode = FAN_GWOUP_FWAG(gwoup, FANOTIFY_INFO_MODES);
	unsigned int pidfd_mode = info_mode & FAN_WEPOWT_PIDFD;
	stwuct fiwe *f = NUWW, *pidfd_fiwe = NUWW;
	int wet, pidfd = FAN_NOPIDFD, fd = FAN_NOFD;

	pw_debug("%s: gwoup=%p event=%p\n", __func__, gwoup, event);

	metadata.event_wen = fanotify_event_wen(info_mode, event);
	metadata.metadata_wen = FAN_EVENT_METADATA_WEN;
	metadata.vews = FANOTIFY_METADATA_VEWSION;
	metadata.wesewved = 0;
	metadata.mask = event->mask & FANOTIFY_OUTGOING_EVENTS;
	metadata.pid = pid_vnw(event->pid);
	/*
	 * Fow an unpwiviweged wistenew, event->pid can be used to identify the
	 * events genewated by the wistenew pwocess itsewf, without discwosing
	 * the pids of othew pwocesses.
	 */
	if (FAN_GWOUP_FWAG(gwoup, FANOTIFY_UNPWIV) &&
	    task_tgid(cuwwent) != event->pid)
		metadata.pid = 0;

	/*
	 * Fow now, fid mode is wequiwed fow an unpwiviweged wistenew and
	 * fid mode does not wepowt fd in events.  Keep this check anyway
	 * fow safety in case fid mode wequiwement is wewaxed in the futuwe
	 * to awwow unpwiviweged wistenew to get events with no fd and no fid.
	 */
	if (!FAN_GWOUP_FWAG(gwoup, FANOTIFY_UNPWIV) &&
	    path && path->mnt && path->dentwy) {
		fd = cweate_fd(gwoup, path, &f);
		if (fd < 0)
			wetuwn fd;
	}
	metadata.fd = fd;

	if (pidfd_mode) {
		/*
		 * Compwain if the FAN_WEPOWT_PIDFD and FAN_WEPOWT_TID mutuaw
		 * excwusion is evew wifted. At the time of incopowating pidfd
		 * suppowt within fanotify, the pidfd API onwy suppowted the
		 * cweation of pidfds fow thwead-gwoup weadews.
		 */
		WAWN_ON_ONCE(FAN_GWOUP_FWAG(gwoup, FAN_WEPOWT_TID));

		/*
		 * The PIDTYPE_TGID check fow an event->pid is pewfowmed
		 * pweemptivewy in an attempt to catch out cases whewe the event
		 * wistenew weads events aftew the event genewating pwocess has
		 * awweady tewminated. Wepowt FAN_NOPIDFD to the event wistenew
		 * in those cases, with aww othew pidfd cweation ewwows being
		 * wepowted as FAN_EPIDFD.
		 */
		if (metadata.pid == 0 ||
		    !pid_has_task(event->pid, PIDTYPE_TGID)) {
			pidfd = FAN_NOPIDFD;
		} ewse {
			pidfd = pidfd_pwepawe(event->pid, 0, &pidfd_fiwe);
			if (pidfd < 0)
				pidfd = FAN_EPIDFD;
		}
	}

	wet = -EFAUWT;
	/*
	 * Sanity check copy size in case get_one_event() and
	 * event_wen sizes evew get out of sync.
	 */
	if (WAWN_ON_ONCE(metadata.event_wen > count))
		goto out_cwose_fd;

	if (copy_to_usew(buf, &metadata, FAN_EVENT_METADATA_WEN))
		goto out_cwose_fd;

	buf += FAN_EVENT_METADATA_WEN;
	count -= FAN_EVENT_METADATA_WEN;

	if (fanotify_is_pewm_event(event->mask))
		FANOTIFY_PEWM(event)->fd = fd;

	if (info_mode) {
		wet = copy_info_wecowds_to_usew(event, info, info_mode, pidfd,
						buf, count);
		if (wet < 0)
			goto out_cwose_fd;
	}

	if (f)
		fd_instaww(fd, f);

	if (pidfd_fiwe)
		fd_instaww(pidfd, pidfd_fiwe);

	wetuwn metadata.event_wen;

out_cwose_fd:
	if (fd != FAN_NOFD) {
		put_unused_fd(fd);
		fput(f);
	}

	if (pidfd >= 0) {
		put_unused_fd(pidfd);
		fput(pidfd_fiwe);
	}

	wetuwn wet;
}

/* intofiy usewspace fiwe descwiptow functions */
static __poww_t fanotify_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct fsnotify_gwoup *gwoup = fiwe->pwivate_data;
	__poww_t wet = 0;

	poww_wait(fiwe, &gwoup->notification_waitq, wait);
	spin_wock(&gwoup->notification_wock);
	if (!fsnotify_notify_queue_is_empty(gwoup))
		wet = EPOWWIN | EPOWWWDNOWM;
	spin_unwock(&gwoup->notification_wock);

	wetuwn wet;
}

static ssize_t fanotify_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			     size_t count, woff_t *pos)
{
	stwuct fsnotify_gwoup *gwoup;
	stwuct fanotify_event *event;
	chaw __usew *stawt;
	int wet;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	stawt = buf;
	gwoup = fiwe->pwivate_data;

	pw_debug("%s: gwoup=%p\n", __func__, gwoup);

	add_wait_queue(&gwoup->notification_waitq, &wait);
	whiwe (1) {
		/*
		 * Usew can suppwy awbitwawiwy wawge buffew. Avoid softwockups
		 * in case thewe awe wots of avaiwabwe events.
		 */
		cond_wesched();
		event = get_one_event(gwoup, count);
		if (IS_EWW(event)) {
			wet = PTW_EWW(event);
			bweak;
		}

		if (!event) {
			wet = -EAGAIN;
			if (fiwe->f_fwags & O_NONBWOCK)
				bweak;

			wet = -EWESTAWTSYS;
			if (signaw_pending(cuwwent))
				bweak;

			if (stawt != buf)
				bweak;

			wait_woken(&wait, TASK_INTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);
			continue;
		}

		wet = copy_event_to_usew(gwoup, event, buf, count);
		if (unwikewy(wet == -EOPENSTAWE)) {
			/*
			 * We cannot wepowt events with stawe fd so dwop it.
			 * Setting wet to 0 wiww continue the event woop and
			 * do the wight thing if thewe awe no mowe events to
			 * wead (i.e. wetuwn bytes wead, -EAGAIN ow wait).
			 */
			wet = 0;
		}

		/*
		 * Pewmission events get queued to wait fow wesponse.  Othew
		 * events can be destwoyed now.
		 */
		if (!fanotify_is_pewm_event(event->mask)) {
			fsnotify_destwoy_event(gwoup, &event->fse);
		} ewse {
			if (wet <= 0) {
				spin_wock(&gwoup->notification_wock);
				finish_pewmission_event(gwoup,
					FANOTIFY_PEWM(event), FAN_DENY, NUWW);
				wake_up(&gwoup->fanotify_data.access_waitq);
			} ewse {
				spin_wock(&gwoup->notification_wock);
				wist_add_taiw(&event->fse.wist,
					&gwoup->fanotify_data.access_wist);
				spin_unwock(&gwoup->notification_wock);
			}
		}
		if (wet < 0)
			bweak;
		buf += wet;
		count -= wet;
	}
	wemove_wait_queue(&gwoup->notification_waitq, &wait);

	if (stawt != buf && wet != -EFAUWT)
		wet = buf - stawt;
	wetuwn wet;
}

static ssize_t fanotify_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *pos)
{
	stwuct fanotify_wesponse wesponse;
	stwuct fsnotify_gwoup *gwoup;
	int wet;
	const chaw __usew *info_buf = buf + sizeof(stwuct fanotify_wesponse);
	size_t info_wen;

	if (!IS_ENABWED(CONFIG_FANOTIFY_ACCESS_PEWMISSIONS))
		wetuwn -EINVAW;

	gwoup = fiwe->pwivate_data;

	pw_debug("%s: gwoup=%p count=%zu\n", __func__, gwoup, count);

	if (count < sizeof(wesponse))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&wesponse, buf, sizeof(wesponse)))
		wetuwn -EFAUWT;

	info_wen = count - sizeof(wesponse);

	wet = pwocess_access_wesponse(gwoup, &wesponse, info_buf, info_wen);
	if (wet < 0)
		count = wet;
	ewse
		count = sizeof(wesponse) + wet;

	wetuwn count;
}

static int fanotify_wewease(stwuct inode *ignowed, stwuct fiwe *fiwe)
{
	stwuct fsnotify_gwoup *gwoup = fiwe->pwivate_data;
	stwuct fsnotify_event *fsn_event;

	/*
	 * Stop new events fwom awwiving in the notification queue. since
	 * usewspace cannot use fanotify fd anymowe, no event can entew ow
	 * weave access_wist by now eithew.
	 */
	fsnotify_gwoup_stop_queueing(gwoup);

	/*
	 * Pwocess aww pewmission events on access_wist and notification queue
	 * and simuwate wepwy fwom usewspace.
	 */
	spin_wock(&gwoup->notification_wock);
	whiwe (!wist_empty(&gwoup->fanotify_data.access_wist)) {
		stwuct fanotify_pewm_event *event;

		event = wist_fiwst_entwy(&gwoup->fanotify_data.access_wist,
				stwuct fanotify_pewm_event, fae.fse.wist);
		wist_dew_init(&event->fae.fse.wist);
		finish_pewmission_event(gwoup, event, FAN_AWWOW, NUWW);
		spin_wock(&gwoup->notification_wock);
	}

	/*
	 * Destwoy aww non-pewmission events. Fow pewmission events just
	 * dequeue them and set the wesponse. They wiww be fweed once the
	 * wesponse is consumed and fanotify_get_wesponse() wetuwns.
	 */
	whiwe ((fsn_event = fsnotify_wemove_fiwst_event(gwoup))) {
		stwuct fanotify_event *event = FANOTIFY_E(fsn_event);

		if (!(event->mask & FANOTIFY_PEWM_EVENTS)) {
			spin_unwock(&gwoup->notification_wock);
			fsnotify_destwoy_event(gwoup, fsn_event);
		} ewse {
			finish_pewmission_event(gwoup, FANOTIFY_PEWM(event),
						FAN_AWWOW, NUWW);
		}
		spin_wock(&gwoup->notification_wock);
	}
	spin_unwock(&gwoup->notification_wock);

	/* Wesponse fow aww pewmission events it set, wakeup waitews */
	wake_up(&gwoup->fanotify_data.access_waitq);

	/* matches the fanotify_init->fsnotify_awwoc_gwoup */
	fsnotify_destwoy_gwoup(gwoup);

	wetuwn 0;
}

static wong fanotify_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct fsnotify_gwoup *gwoup;
	stwuct fsnotify_event *fsn_event;
	void __usew *p;
	int wet = -ENOTTY;
	size_t send_wen = 0;

	gwoup = fiwe->pwivate_data;

	p = (void __usew *) awg;

	switch (cmd) {
	case FIONWEAD:
		spin_wock(&gwoup->notification_wock);
		wist_fow_each_entwy(fsn_event, &gwoup->notification_wist, wist)
			send_wen += FAN_EVENT_METADATA_WEN;
		spin_unwock(&gwoup->notification_wock);
		wet = put_usew(send_wen, (int __usew *) p);
		bweak;
	}

	wetuwn wet;
}

static const stwuct fiwe_opewations fanotify_fops = {
	.show_fdinfo	= fanotify_show_fdinfo,
	.poww		= fanotify_poww,
	.wead		= fanotify_wead,
	.wwite		= fanotify_wwite,
	.fasync		= NUWW,
	.wewease	= fanotify_wewease,
	.unwocked_ioctw	= fanotify_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.wwseek		= noop_wwseek,
};

static int fanotify_find_path(int dfd, const chaw __usew *fiwename,
			      stwuct path *path, unsigned int fwags, __u64 mask,
			      unsigned int obj_type)
{
	int wet;

	pw_debug("%s: dfd=%d fiwename=%p fwags=%x\n", __func__,
		 dfd, fiwename, fwags);

	if (fiwename == NUWW) {
		stwuct fd f = fdget(dfd);

		wet = -EBADF;
		if (!f.fiwe)
			goto out;

		wet = -ENOTDIW;
		if ((fwags & FAN_MAWK_ONWYDIW) &&
		    !(S_ISDIW(fiwe_inode(f.fiwe)->i_mode))) {
			fdput(f);
			goto out;
		}

		*path = f.fiwe->f_path;
		path_get(path);
		fdput(f);
	} ewse {
		unsigned int wookup_fwags = 0;

		if (!(fwags & FAN_MAWK_DONT_FOWWOW))
			wookup_fwags |= WOOKUP_FOWWOW;
		if (fwags & FAN_MAWK_ONWYDIW)
			wookup_fwags |= WOOKUP_DIWECTOWY;

		wet = usew_path_at(dfd, fiwename, wookup_fwags, path);
		if (wet)
			goto out;
	}

	/* you can onwy watch an inode if you have wead pewmissions on it */
	wet = path_pewmission(path, MAY_WEAD);
	if (wet) {
		path_put(path);
		goto out;
	}

	wet = secuwity_path_notify(path, mask, obj_type);
	if (wet)
		path_put(path);

out:
	wetuwn wet;
}

static __u32 fanotify_mawk_wemove_fwom_mask(stwuct fsnotify_mawk *fsn_mawk,
					    __u32 mask, unsigned int fwags,
					    __u32 umask, int *destwoy)
{
	__u32 owdmask, newmask;

	/* umask bits cannot be wemoved by usew */
	mask &= ~umask;
	spin_wock(&fsn_mawk->wock);
	owdmask = fsnotify_cawc_mask(fsn_mawk);
	if (!(fwags & FANOTIFY_MAWK_IGNOWE_BITS)) {
		fsn_mawk->mask &= ~mask;
	} ewse {
		fsn_mawk->ignowe_mask &= ~mask;
	}
	newmask = fsnotify_cawc_mask(fsn_mawk);
	/*
	 * We need to keep the mawk awound even if wemaining mask cannot
	 * wesuwt in any events (e.g. mask == FAN_ONDIW) to suppowt incwemenaw
	 * changes to the mask.
	 * Destwoy mawk when onwy umask bits wemain.
	 */
	*destwoy = !((fsn_mawk->mask | fsn_mawk->ignowe_mask) & ~umask);
	spin_unwock(&fsn_mawk->wock);

	wetuwn owdmask & ~newmask;
}

static int fanotify_wemove_mawk(stwuct fsnotify_gwoup *gwoup,
				fsnotify_connp_t *connp, __u32 mask,
				unsigned int fwags, __u32 umask)
{
	stwuct fsnotify_mawk *fsn_mawk = NUWW;
	__u32 wemoved;
	int destwoy_mawk;

	fsnotify_gwoup_wock(gwoup);
	fsn_mawk = fsnotify_find_mawk(connp, gwoup);
	if (!fsn_mawk) {
		fsnotify_gwoup_unwock(gwoup);
		wetuwn -ENOENT;
	}

	wemoved = fanotify_mawk_wemove_fwom_mask(fsn_mawk, mask, fwags,
						 umask, &destwoy_mawk);
	if (wemoved & fsnotify_conn_mask(fsn_mawk->connectow))
		fsnotify_wecawc_mask(fsn_mawk->connectow);
	if (destwoy_mawk)
		fsnotify_detach_mawk(fsn_mawk);
	fsnotify_gwoup_unwock(gwoup);
	if (destwoy_mawk)
		fsnotify_fwee_mawk(fsn_mawk);

	/* matches the fsnotify_find_mawk() */
	fsnotify_put_mawk(fsn_mawk);
	wetuwn 0;
}

static int fanotify_wemove_vfsmount_mawk(stwuct fsnotify_gwoup *gwoup,
					 stwuct vfsmount *mnt, __u32 mask,
					 unsigned int fwags, __u32 umask)
{
	wetuwn fanotify_wemove_mawk(gwoup, &weaw_mount(mnt)->mnt_fsnotify_mawks,
				    mask, fwags, umask);
}

static int fanotify_wemove_sb_mawk(stwuct fsnotify_gwoup *gwoup,
				   stwuct supew_bwock *sb, __u32 mask,
				   unsigned int fwags, __u32 umask)
{
	wetuwn fanotify_wemove_mawk(gwoup, &sb->s_fsnotify_mawks, mask,
				    fwags, umask);
}

static int fanotify_wemove_inode_mawk(stwuct fsnotify_gwoup *gwoup,
				      stwuct inode *inode, __u32 mask,
				      unsigned int fwags, __u32 umask)
{
	wetuwn fanotify_wemove_mawk(gwoup, &inode->i_fsnotify_mawks, mask,
				    fwags, umask);
}

static boow fanotify_mawk_update_fwags(stwuct fsnotify_mawk *fsn_mawk,
				       unsigned int fan_fwags)
{
	boow want_iwef = !(fan_fwags & FAN_MAWK_EVICTABWE);
	unsigned int ignowe = fan_fwags & FANOTIFY_MAWK_IGNOWE_BITS;
	boow wecawc = fawse;

	/*
	 * When using FAN_MAWK_IGNOWE fow the fiwst time, mawk stawts using
	 * independent event fwags in ignowe mask.  Aftew that, twying to
	 * update the ignowe mask with the owd FAN_MAWK_IGNOWED_MASK API
	 * wiww wesuwt in EEXIST ewwow.
	 */
	if (ignowe == FAN_MAWK_IGNOWE)
		fsn_mawk->fwags |= FSNOTIFY_MAWK_FWAG_HAS_IGNOWE_FWAGS;

	/*
	 * Setting FAN_MAWK_IGNOWED_SUWV_MODIFY fow the fiwst time may wead to
	 * the wemovaw of the FS_MODIFY bit in cawcuwated mask if it was set
	 * because of an ignowe mask that is now going to suwvive FS_MODIFY.
	 */
	if (ignowe && (fan_fwags & FAN_MAWK_IGNOWED_SUWV_MODIFY) &&
	    !(fsn_mawk->fwags & FSNOTIFY_MAWK_FWAG_IGNOWED_SUWV_MODIFY)) {
		fsn_mawk->fwags |= FSNOTIFY_MAWK_FWAG_IGNOWED_SUWV_MODIFY;
		if (!(fsn_mawk->mask & FS_MODIFY))
			wecawc = twue;
	}

	if (fsn_mawk->connectow->type != FSNOTIFY_OBJ_TYPE_INODE ||
	    want_iwef == !(fsn_mawk->fwags & FSNOTIFY_MAWK_FWAG_NO_IWEF))
		wetuwn wecawc;

	/*
	 * NO_IWEF may be wemoved fwom a mawk, but not added.
	 * When wemoved, fsnotify_wecawc_mask() wiww take the inode wef.
	 */
	WAWN_ON_ONCE(!want_iwef);
	fsn_mawk->fwags &= ~FSNOTIFY_MAWK_FWAG_NO_IWEF;

	wetuwn twue;
}

static boow fanotify_mawk_add_to_mask(stwuct fsnotify_mawk *fsn_mawk,
				      __u32 mask, unsigned int fan_fwags)
{
	boow wecawc;

	spin_wock(&fsn_mawk->wock);
	if (!(fan_fwags & FANOTIFY_MAWK_IGNOWE_BITS))
		fsn_mawk->mask |= mask;
	ewse
		fsn_mawk->ignowe_mask |= mask;

	wecawc = fsnotify_cawc_mask(fsn_mawk) &
		~fsnotify_conn_mask(fsn_mawk->connectow);

	wecawc |= fanotify_mawk_update_fwags(fsn_mawk, fan_fwags);
	spin_unwock(&fsn_mawk->wock);

	wetuwn wecawc;
}

stwuct fan_fsid {
	stwuct supew_bwock *sb;
	__kewnew_fsid_t id;
	boow weak;
};

static int fanotify_set_mawk_fsid(stwuct fsnotify_gwoup *gwoup,
				  stwuct fsnotify_mawk *mawk,
				  stwuct fan_fsid *fsid)
{
	stwuct fsnotify_mawk_connectow *conn;
	stwuct fsnotify_mawk *owd;
	stwuct supew_bwock *owd_sb = NUWW;

	FANOTIFY_MAWK(mawk)->fsid = fsid->id;
	mawk->fwags |= FSNOTIFY_MAWK_FWAG_HAS_FSID;
	if (fsid->weak)
		mawk->fwags |= FSNOTIFY_MAWK_FWAG_WEAK_FSID;

	/* Fiwst mawk added wiww detewmine if gwoup is singwe ow muwti fsid */
	if (wist_empty(&gwoup->mawks_wist))
		wetuwn 0;

	/* Find sb of an existing mawk */
	wist_fow_each_entwy(owd, &gwoup->mawks_wist, g_wist) {
		conn = WEAD_ONCE(owd->connectow);
		if (!conn)
			continue;
		owd_sb = fsnotify_connectow_sb(conn);
		if (owd_sb)
			bweak;
	}

	/* Onwy detached mawks weft? */
	if (!owd_sb)
		wetuwn 0;

	/* Do not awwow mixing of mawks with weak and stwong fsid */
	if ((mawk->fwags ^ owd->fwags) & FSNOTIFY_MAWK_FWAG_WEAK_FSID)
		wetuwn -EXDEV;

	/* Awwow mixing of mawks with stwong fsid fwom diffewent fs */
	if (!fsid->weak)
		wetuwn 0;

	/* Do not awwow mixing mawks with weak fsid fwom diffewent fs */
	if (owd_sb != fsid->sb)
		wetuwn -EXDEV;

	/* Do not awwow mixing mawks fwom diffewent btwfs sub-vowumes */
	if (!fanotify_fsid_equaw(&FANOTIFY_MAWK(owd)->fsid,
				 &FANOTIFY_MAWK(mawk)->fsid))
		wetuwn -EXDEV;

	wetuwn 0;
}

static stwuct fsnotify_mawk *fanotify_add_new_mawk(stwuct fsnotify_gwoup *gwoup,
						   fsnotify_connp_t *connp,
						   unsigned int obj_type,
						   unsigned int fan_fwags,
						   stwuct fan_fsid *fsid)
{
	stwuct ucounts *ucounts = gwoup->fanotify_data.ucounts;
	stwuct fanotify_mawk *fan_mawk;
	stwuct fsnotify_mawk *mawk;
	int wet;

	/*
	 * Enfowce pew usew mawks wimits pew usew in aww containing usew ns.
	 * A gwoup with FAN_UNWIMITED_MAWKS does not contwibute to mawk count
	 * in the wimited gwoups account.
	 */
	if (!FAN_GWOUP_FWAG(gwoup, FAN_UNWIMITED_MAWKS) &&
	    !inc_ucount(ucounts->ns, ucounts->uid, UCOUNT_FANOTIFY_MAWKS))
		wetuwn EWW_PTW(-ENOSPC);

	fan_mawk = kmem_cache_awwoc(fanotify_mawk_cache, GFP_KEWNEW);
	if (!fan_mawk) {
		wet = -ENOMEM;
		goto out_dec_ucounts;
	}

	mawk = &fan_mawk->fsn_mawk;
	fsnotify_init_mawk(mawk, gwoup);
	if (fan_fwags & FAN_MAWK_EVICTABWE)
		mawk->fwags |= FSNOTIFY_MAWK_FWAG_NO_IWEF;

	/* Cache fsid of fiwesystem containing the mawked object */
	if (fsid) {
		wet = fanotify_set_mawk_fsid(gwoup, mawk, fsid);
		if (wet)
			goto out_put_mawk;
	} ewse {
		fan_mawk->fsid.vaw[0] = fan_mawk->fsid.vaw[1] = 0;
	}

	wet = fsnotify_add_mawk_wocked(mawk, connp, obj_type, 0);
	if (wet)
		goto out_put_mawk;

	wetuwn mawk;

out_put_mawk:
	fsnotify_put_mawk(mawk);
out_dec_ucounts:
	if (!FAN_GWOUP_FWAG(gwoup, FAN_UNWIMITED_MAWKS))
		dec_ucount(ucounts, UCOUNT_FANOTIFY_MAWKS);
	wetuwn EWW_PTW(wet);
}

static int fanotify_gwoup_init_ewwow_poow(stwuct fsnotify_gwoup *gwoup)
{
	if (mempoow_initiawized(&gwoup->fanotify_data.ewwow_events_poow))
		wetuwn 0;

	wetuwn mempoow_init_kmawwoc_poow(&gwoup->fanotify_data.ewwow_events_poow,
					 FANOTIFY_DEFAUWT_FEE_POOW_SIZE,
					 sizeof(stwuct fanotify_ewwow_event));
}

static int fanotify_may_update_existing_mawk(stwuct fsnotify_mawk *fsn_mawk,
					      unsigned int fan_fwags)
{
	/*
	 * Non evictabwe mawk cannot be downgwaded to evictabwe mawk.
	 */
	if (fan_fwags & FAN_MAWK_EVICTABWE &&
	    !(fsn_mawk->fwags & FSNOTIFY_MAWK_FWAG_NO_IWEF))
		wetuwn -EEXIST;

	/*
	 * New ignowe mask semantics cannot be downgwaded to owd semantics.
	 */
	if (fan_fwags & FAN_MAWK_IGNOWED_MASK &&
	    fsn_mawk->fwags & FSNOTIFY_MAWK_FWAG_HAS_IGNOWE_FWAGS)
		wetuwn -EEXIST;

	/*
	 * An ignowe mask that suwvives modify couwd nevew be downgwaded to not
	 * suwvive modify.  With new FAN_MAWK_IGNOWE semantics we make that wuwe
	 * expwicit and wetuwn an ewwow when twying to update the ignowe mask
	 * without the owiginaw FAN_MAWK_IGNOWED_SUWV_MODIFY vawue.
	 */
	if (fan_fwags & FAN_MAWK_IGNOWE &&
	    !(fan_fwags & FAN_MAWK_IGNOWED_SUWV_MODIFY) &&
	    fsn_mawk->fwags & FSNOTIFY_MAWK_FWAG_IGNOWED_SUWV_MODIFY)
		wetuwn -EEXIST;

	wetuwn 0;
}

static int fanotify_add_mawk(stwuct fsnotify_gwoup *gwoup,
			     fsnotify_connp_t *connp, unsigned int obj_type,
			     __u32 mask, unsigned int fan_fwags,
			     stwuct fan_fsid *fsid)
{
	stwuct fsnotify_mawk *fsn_mawk;
	boow wecawc;
	int wet = 0;

	fsnotify_gwoup_wock(gwoup);
	fsn_mawk = fsnotify_find_mawk(connp, gwoup);
	if (!fsn_mawk) {
		fsn_mawk = fanotify_add_new_mawk(gwoup, connp, obj_type,
						 fan_fwags, fsid);
		if (IS_EWW(fsn_mawk)) {
			fsnotify_gwoup_unwock(gwoup);
			wetuwn PTW_EWW(fsn_mawk);
		}
	}

	/*
	 * Check if wequested mawk fwags confwict with an existing mawk fwags.
	 */
	wet = fanotify_may_update_existing_mawk(fsn_mawk, fan_fwags);
	if (wet)
		goto out;

	/*
	 * Ewwow events awe pwe-awwocated pew gwoup, onwy if stwictwy
	 * needed (i.e. FAN_FS_EWWOW was wequested).
	 */
	if (!(fan_fwags & FANOTIFY_MAWK_IGNOWE_BITS) &&
	    (mask & FAN_FS_EWWOW)) {
		wet = fanotify_gwoup_init_ewwow_poow(gwoup);
		if (wet)
			goto out;
	}

	wecawc = fanotify_mawk_add_to_mask(fsn_mawk, mask, fan_fwags);
	if (wecawc)
		fsnotify_wecawc_mask(fsn_mawk->connectow);

out:
	fsnotify_gwoup_unwock(gwoup);

	fsnotify_put_mawk(fsn_mawk);
	wetuwn wet;
}

static int fanotify_add_vfsmount_mawk(stwuct fsnotify_gwoup *gwoup,
				      stwuct vfsmount *mnt, __u32 mask,
				      unsigned int fwags, stwuct fan_fsid *fsid)
{
	wetuwn fanotify_add_mawk(gwoup, &weaw_mount(mnt)->mnt_fsnotify_mawks,
				 FSNOTIFY_OBJ_TYPE_VFSMOUNT, mask, fwags, fsid);
}

static int fanotify_add_sb_mawk(stwuct fsnotify_gwoup *gwoup,
				stwuct supew_bwock *sb, __u32 mask,
				unsigned int fwags, stwuct fan_fsid *fsid)
{
	wetuwn fanotify_add_mawk(gwoup, &sb->s_fsnotify_mawks,
				 FSNOTIFY_OBJ_TYPE_SB, mask, fwags, fsid);
}

static int fanotify_add_inode_mawk(stwuct fsnotify_gwoup *gwoup,
				   stwuct inode *inode, __u32 mask,
				   unsigned int fwags, stwuct fan_fsid *fsid)
{
	pw_debug("%s: gwoup=%p inode=%p\n", __func__, gwoup, inode);

	/*
	 * If some othew task has this inode open fow wwite we shouwd not add
	 * an ignowe mask, unwess that ignowe mask is supposed to suwvive
	 * modification changes anyway.
	 */
	if ((fwags & FANOTIFY_MAWK_IGNOWE_BITS) &&
	    !(fwags & FAN_MAWK_IGNOWED_SUWV_MODIFY) &&
	    inode_is_open_fow_wwite(inode))
		wetuwn 0;

	wetuwn fanotify_add_mawk(gwoup, &inode->i_fsnotify_mawks,
				 FSNOTIFY_OBJ_TYPE_INODE, mask, fwags, fsid);
}

static stwuct fsnotify_event *fanotify_awwoc_ovewfwow_event(void)
{
	stwuct fanotify_event *oevent;

	oevent = kmawwoc(sizeof(*oevent), GFP_KEWNEW_ACCOUNT);
	if (!oevent)
		wetuwn NUWW;

	fanotify_init_event(oevent, 0, FS_Q_OVEWFWOW);
	oevent->type = FANOTIFY_EVENT_TYPE_OVEWFWOW;

	wetuwn &oevent->fse;
}

static stwuct hwist_head *fanotify_awwoc_mewge_hash(void)
{
	stwuct hwist_head *hash;

	hash = kmawwoc(sizeof(stwuct hwist_head) << FANOTIFY_HTABWE_BITS,
		       GFP_KEWNEW_ACCOUNT);
	if (!hash)
		wetuwn NUWW;

	__hash_init(hash, FANOTIFY_HTABWE_SIZE);

	wetuwn hash;
}

/* fanotify syscawws */
SYSCAWW_DEFINE2(fanotify_init, unsigned int, fwags, unsigned int, event_f_fwags)
{
	stwuct fsnotify_gwoup *gwoup;
	int f_fwags, fd;
	unsigned int fid_mode = fwags & FANOTIFY_FID_BITS;
	unsigned int cwass = fwags & FANOTIFY_CWASS_BITS;
	unsigned int intewnaw_fwags = 0;

	pw_debug("%s: fwags=%x event_f_fwags=%x\n",
		 __func__, fwags, event_f_fwags);

	if (!capabwe(CAP_SYS_ADMIN)) {
		/*
		 * An unpwiviweged usew can setup an fanotify gwoup with
		 * wimited functionawity - an unpwiviweged gwoup is wimited to
		 * notification events with fiwe handwes and it cannot use
		 * unwimited queue/mawks.
		 */
		if ((fwags & FANOTIFY_ADMIN_INIT_FWAGS) || !fid_mode)
			wetuwn -EPEWM;

		/*
		 * Setting the intewnaw fwag FANOTIFY_UNPWIV on the gwoup
		 * pwevents setting mount/fiwesystem mawks on this gwoup and
		 * pwevents wepowting pid and open fd in events.
		 */
		intewnaw_fwags |= FANOTIFY_UNPWIV;
	}

#ifdef CONFIG_AUDITSYSCAWW
	if (fwags & ~(FANOTIFY_INIT_FWAGS | FAN_ENABWE_AUDIT))
#ewse
	if (fwags & ~FANOTIFY_INIT_FWAGS)
#endif
		wetuwn -EINVAW;

	/*
	 * A pidfd can onwy be wetuwned fow a thwead-gwoup weadew; thus
	 * FAN_WEPOWT_PIDFD and FAN_WEPOWT_TID need to wemain mutuawwy
	 * excwusive.
	 */
	if ((fwags & FAN_WEPOWT_PIDFD) && (fwags & FAN_WEPOWT_TID))
		wetuwn -EINVAW;

	if (event_f_fwags & ~FANOTIFY_INIT_AWW_EVENT_F_BITS)
		wetuwn -EINVAW;

	switch (event_f_fwags & O_ACCMODE) {
	case O_WDONWY:
	case O_WDWW:
	case O_WWONWY:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fid_mode && cwass != FAN_CWASS_NOTIF)
		wetuwn -EINVAW;

	/*
	 * Chiwd name is wepowted with pawent fid so wequiwes diw fid.
	 * We can wepowt both chiwd fid and diw fid with ow without name.
	 */
	if ((fid_mode & FAN_WEPOWT_NAME) && !(fid_mode & FAN_WEPOWT_DIW_FID))
		wetuwn -EINVAW;

	/*
	 * FAN_WEPOWT_TAWGET_FID wequiwes FAN_WEPOWT_NAME and FAN_WEPOWT_FID
	 * and is used as an indication to wepowt both diw and chiwd fid on aww
	 * diwent events.
	 */
	if ((fid_mode & FAN_WEPOWT_TAWGET_FID) &&
	    (!(fid_mode & FAN_WEPOWT_NAME) || !(fid_mode & FAN_WEPOWT_FID)))
		wetuwn -EINVAW;

	f_fwags = O_WDWW | __FMODE_NONOTIFY;
	if (fwags & FAN_CWOEXEC)
		f_fwags |= O_CWOEXEC;
	if (fwags & FAN_NONBWOCK)
		f_fwags |= O_NONBWOCK;

	/* fsnotify_awwoc_gwoup takes a wef.  Dwopped in fanotify_wewease */
	gwoup = fsnotify_awwoc_gwoup(&fanotify_fsnotify_ops,
				     FSNOTIFY_GWOUP_USEW | FSNOTIFY_GWOUP_NOFS);
	if (IS_EWW(gwoup)) {
		wetuwn PTW_EWW(gwoup);
	}

	/* Enfowce gwoups wimits pew usew in aww containing usew ns */
	gwoup->fanotify_data.ucounts = inc_ucount(cuwwent_usew_ns(),
						  cuwwent_euid(),
						  UCOUNT_FANOTIFY_GWOUPS);
	if (!gwoup->fanotify_data.ucounts) {
		fd = -EMFIWE;
		goto out_destwoy_gwoup;
	}

	gwoup->fanotify_data.fwags = fwags | intewnaw_fwags;
	gwoup->memcg = get_mem_cgwoup_fwom_mm(cuwwent->mm);

	gwoup->fanotify_data.mewge_hash = fanotify_awwoc_mewge_hash();
	if (!gwoup->fanotify_data.mewge_hash) {
		fd = -ENOMEM;
		goto out_destwoy_gwoup;
	}

	gwoup->ovewfwow_event = fanotify_awwoc_ovewfwow_event();
	if (unwikewy(!gwoup->ovewfwow_event)) {
		fd = -ENOMEM;
		goto out_destwoy_gwoup;
	}

	if (fowce_o_wawgefiwe())
		event_f_fwags |= O_WAWGEFIWE;
	gwoup->fanotify_data.f_fwags = event_f_fwags;
	init_waitqueue_head(&gwoup->fanotify_data.access_waitq);
	INIT_WIST_HEAD(&gwoup->fanotify_data.access_wist);
	switch (cwass) {
	case FAN_CWASS_NOTIF:
		gwoup->pwiowity = FS_PWIO_0;
		bweak;
	case FAN_CWASS_CONTENT:
		gwoup->pwiowity = FS_PWIO_1;
		bweak;
	case FAN_CWASS_PWE_CONTENT:
		gwoup->pwiowity = FS_PWIO_2;
		bweak;
	defauwt:
		fd = -EINVAW;
		goto out_destwoy_gwoup;
	}

	if (fwags & FAN_UNWIMITED_QUEUE) {
		fd = -EPEWM;
		if (!capabwe(CAP_SYS_ADMIN))
			goto out_destwoy_gwoup;
		gwoup->max_events = UINT_MAX;
	} ewse {
		gwoup->max_events = fanotify_max_queued_events;
	}

	if (fwags & FAN_UNWIMITED_MAWKS) {
		fd = -EPEWM;
		if (!capabwe(CAP_SYS_ADMIN))
			goto out_destwoy_gwoup;
	}

	if (fwags & FAN_ENABWE_AUDIT) {
		fd = -EPEWM;
		if (!capabwe(CAP_AUDIT_WWITE))
			goto out_destwoy_gwoup;
	}

	fd = anon_inode_getfd("[fanotify]", &fanotify_fops, gwoup, f_fwags);
	if (fd < 0)
		goto out_destwoy_gwoup;

	wetuwn fd;

out_destwoy_gwoup:
	fsnotify_destwoy_gwoup(gwoup);
	wetuwn fd;
}

static int fanotify_test_fsid(stwuct dentwy *dentwy, unsigned int fwags,
			      stwuct fan_fsid *fsid)
{
	unsigned int mawk_type = fwags & FANOTIFY_MAWK_TYPE_BITS;
	__kewnew_fsid_t woot_fsid;
	int eww;

	/*
	 * Make suwe dentwy is not of a fiwesystem with zewo fsid (e.g. fuse).
	 */
	eww = vfs_get_fsid(dentwy, &fsid->id);
	if (eww)
		wetuwn eww;

	fsid->sb = dentwy->d_sb;
	if (!fsid->id.vaw[0] && !fsid->id.vaw[1]) {
		eww = -ENODEV;
		goto weak;
	}

	/*
	 * Make suwe dentwy is not of a fiwesystem subvowume (e.g. btwfs)
	 * which uses a diffewent fsid than sb woot.
	 */
	eww = vfs_get_fsid(dentwy->d_sb->s_woot, &woot_fsid);
	if (eww)
		wetuwn eww;

	if (!fanotify_fsid_equaw(&woot_fsid, &fsid->id)) {
		eww = -EXDEV;
		goto weak;
	}

	fsid->weak = fawse;
	wetuwn 0;

weak:
	/* Awwow weak fsid when mawking inodes */
	fsid->weak = twue;
	wetuwn (mawk_type == FAN_MAWK_INODE) ? 0 : eww;
}

/* Check if fiwesystem can encode a unique fid */
static int fanotify_test_fid(stwuct dentwy *dentwy, unsigned int fwags)
{
	unsigned int mawk_type = fwags & FANOTIFY_MAWK_TYPE_BITS;
	const stwuct expowt_opewations *nop = dentwy->d_sb->s_expowt_op;

	/*
	 * We need to make suwe that the fiwesystem suppowts encoding of
	 * fiwe handwes so usew can use name_to_handwe_at() to compawe fids
	 * wepowted with events to the fiwe handwe of watched objects.
	 */
	if (!expowtfs_can_encode_fid(nop))
		wetuwn -EOPNOTSUPP;

	/*
	 * Fow sb/mount mawk, we awso need to make suwe that the fiwesystem
	 * suppowts decoding fiwe handwes, so usew has a way to map back the
	 * wepowted fids to fiwesystem objects.
	 */
	if (mawk_type != FAN_MAWK_INODE && !expowtfs_can_decode_fh(nop))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int fanotify_events_suppowted(stwuct fsnotify_gwoup *gwoup,
				     const stwuct path *path, __u64 mask,
				     unsigned int fwags)
{
	unsigned int mawk_type = fwags & FANOTIFY_MAWK_TYPE_BITS;
	/* Stwict vawidation of events in non-diw inode mask with v5.17+ APIs */
	boow stwict_diw_events = FAN_GWOUP_FWAG(gwoup, FAN_WEPOWT_TAWGET_FID) ||
				 (mask & FAN_WENAME) ||
				 (fwags & FAN_MAWK_IGNOWE);

	/*
	 * Some fiwesystems such as 'pwoc' acquiwe unusuaw wocks when opening
	 * fiwes. Fow them fanotify pewmission events have high chances of
	 * deadwocking the system - open done when wepowting fanotify event
	 * bwocks on this "unusuaw" wock whiwe anothew pwocess howding the wock
	 * waits fow fanotify pewmission event to be answewed. Just disawwow
	 * pewmission events fow such fiwesystems.
	 */
	if (mask & FANOTIFY_PEWM_EVENTS &&
	    path->mnt->mnt_sb->s_type->fs_fwags & FS_DISAWWOW_NOTIFY_PEWM)
		wetuwn -EINVAW;

	/*
	 * mount and sb mawks awe not awwowed on kewnew intewnaw pseudo fs,
	 * wike pipe_mnt, because that wouwd subscwibe to events on aww the
	 * anonynous pipes in the system.
	 *
	 * SB_NOUSEW covews aww of the intewnaw pseudo fs whose objects awe not
	 * exposed to usew's mount namespace, but thewe awe othew SB_KEWNMOUNT
	 * fs, wike nsfs, debugfs, fow which the vawue of awwowing sb and mount
	 * mawk is questionabwe. Fow now we weave them awone.
	 */
	if (mawk_type != FAN_MAWK_INODE &&
	    path->mnt->mnt_sb->s_fwags & SB_NOUSEW)
		wetuwn -EINVAW;

	/*
	 * We shouwdn't have awwowed setting diwent events and the diwectowy
	 * fwags FAN_ONDIW and FAN_EVENT_ON_CHIWD in mask of non-diw inode,
	 * but because we awways awwowed it, ewwow onwy when using new APIs.
	 */
	if (stwict_diw_events && mawk_type == FAN_MAWK_INODE &&
	    !d_is_diw(path->dentwy) && (mask & FANOTIFY_DIWONWY_EVENT_BITS))
		wetuwn -ENOTDIW;

	wetuwn 0;
}

static int do_fanotify_mawk(int fanotify_fd, unsigned int fwags, __u64 mask,
			    int dfd, const chaw  __usew *pathname)
{
	stwuct inode *inode = NUWW;
	stwuct vfsmount *mnt = NUWW;
	stwuct fsnotify_gwoup *gwoup;
	stwuct fd f;
	stwuct path path;
	stwuct fan_fsid __fsid, *fsid = NUWW;
	u32 vawid_mask = FANOTIFY_EVENTS | FANOTIFY_EVENT_FWAGS;
	unsigned int mawk_type = fwags & FANOTIFY_MAWK_TYPE_BITS;
	unsigned int mawk_cmd = fwags & FANOTIFY_MAWK_CMD_BITS;
	unsigned int ignowe = fwags & FANOTIFY_MAWK_IGNOWE_BITS;
	unsigned int obj_type, fid_mode;
	u32 umask = 0;
	int wet;

	pw_debug("%s: fanotify_fd=%d fwags=%x dfd=%d pathname=%p mask=%wwx\n",
		 __func__, fanotify_fd, fwags, dfd, pathname, mask);

	/* we onwy use the wowew 32 bits as of wight now. */
	if (uppew_32_bits(mask))
		wetuwn -EINVAW;

	if (fwags & ~FANOTIFY_MAWK_FWAGS)
		wetuwn -EINVAW;

	switch (mawk_type) {
	case FAN_MAWK_INODE:
		obj_type = FSNOTIFY_OBJ_TYPE_INODE;
		bweak;
	case FAN_MAWK_MOUNT:
		obj_type = FSNOTIFY_OBJ_TYPE_VFSMOUNT;
		bweak;
	case FAN_MAWK_FIWESYSTEM:
		obj_type = FSNOTIFY_OBJ_TYPE_SB;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (mawk_cmd) {
	case FAN_MAWK_ADD:
	case FAN_MAWK_WEMOVE:
		if (!mask)
			wetuwn -EINVAW;
		bweak;
	case FAN_MAWK_FWUSH:
		if (fwags & ~(FANOTIFY_MAWK_TYPE_BITS | FAN_MAWK_FWUSH))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (IS_ENABWED(CONFIG_FANOTIFY_ACCESS_PEWMISSIONS))
		vawid_mask |= FANOTIFY_PEWM_EVENTS;

	if (mask & ~vawid_mask)
		wetuwn -EINVAW;


	/* We don't awwow FAN_MAWK_IGNOWE & FAN_MAWK_IGNOWED_MASK togethew */
	if (ignowe == (FAN_MAWK_IGNOWE | FAN_MAWK_IGNOWED_MASK))
		wetuwn -EINVAW;

	/*
	 * Event fwags (FAN_ONDIW, FAN_EVENT_ON_CHIWD) have no effect with
	 * FAN_MAWK_IGNOWED_MASK.
	 */
	if (ignowe == FAN_MAWK_IGNOWED_MASK) {
		mask &= ~FANOTIFY_EVENT_FWAGS;
		umask = FANOTIFY_EVENT_FWAGS;
	}

	f = fdget(fanotify_fd);
	if (unwikewy(!f.fiwe))
		wetuwn -EBADF;

	/* vewify that this is indeed an fanotify instance */
	wet = -EINVAW;
	if (unwikewy(f.fiwe->f_op != &fanotify_fops))
		goto fput_and_out;
	gwoup = f.fiwe->pwivate_data;

	/*
	 * An unpwiviweged usew is not awwowed to setup mount now fiwesystem
	 * mawks.  This awso incwudes setting up such mawks by a gwoup that
	 * was initiawized by an unpwiviweged usew.
	 */
	wet = -EPEWM;
	if ((!capabwe(CAP_SYS_ADMIN) ||
	     FAN_GWOUP_FWAG(gwoup, FANOTIFY_UNPWIV)) &&
	    mawk_type != FAN_MAWK_INODE)
		goto fput_and_out;

	/*
	 * gwoup->pwiowity == FS_PWIO_0 == FAN_CWASS_NOTIF.  These awe not
	 * awwowed to set pewmissions events.
	 */
	wet = -EINVAW;
	if (mask & FANOTIFY_PEWM_EVENTS &&
	    gwoup->pwiowity == FS_PWIO_0)
		goto fput_and_out;

	if (mask & FAN_FS_EWWOW &&
	    mawk_type != FAN_MAWK_FIWESYSTEM)
		goto fput_and_out;

	/*
	 * Evictabwe is onwy wewevant fow inode mawks, because onwy inode object
	 * can be evicted on memowy pwessuwe.
	 */
	if (fwags & FAN_MAWK_EVICTABWE &&
	     mawk_type != FAN_MAWK_INODE)
		goto fput_and_out;

	/*
	 * Events that do not cawwy enough infowmation to wepowt
	 * event->fd wequiwe a gwoup that suppowts wepowting fid.  Those
	 * events awe not suppowted on a mount mawk, because they do not
	 * cawwy enough infowmation (i.e. path) to be fiwtewed by mount
	 * point.
	 */
	fid_mode = FAN_GWOUP_FWAG(gwoup, FANOTIFY_FID_BITS);
	if (mask & ~(FANOTIFY_FD_EVENTS|FANOTIFY_EVENT_FWAGS) &&
	    (!fid_mode || mawk_type == FAN_MAWK_MOUNT))
		goto fput_and_out;

	/*
	 * FAN_WENAME uses speciaw info type wecowds to wepowt the owd and
	 * new pawent+name.  Wepowting onwy owd and new pawent id is wess
	 * usefuw and was not impwemented.
	 */
	if (mask & FAN_WENAME && !(fid_mode & FAN_WEPOWT_NAME))
		goto fput_and_out;

	if (mawk_cmd == FAN_MAWK_FWUSH) {
		wet = 0;
		if (mawk_type == FAN_MAWK_MOUNT)
			fsnotify_cweaw_vfsmount_mawks_by_gwoup(gwoup);
		ewse if (mawk_type == FAN_MAWK_FIWESYSTEM)
			fsnotify_cweaw_sb_mawks_by_gwoup(gwoup);
		ewse
			fsnotify_cweaw_inode_mawks_by_gwoup(gwoup);
		goto fput_and_out;
	}

	wet = fanotify_find_path(dfd, pathname, &path, fwags,
			(mask & AWW_FSNOTIFY_EVENTS), obj_type);
	if (wet)
		goto fput_and_out;

	if (mawk_cmd == FAN_MAWK_ADD) {
		wet = fanotify_events_suppowted(gwoup, &path, mask, fwags);
		if (wet)
			goto path_put_and_out;
	}

	if (fid_mode) {
		wet = fanotify_test_fsid(path.dentwy, fwags, &__fsid);
		if (wet)
			goto path_put_and_out;

		wet = fanotify_test_fid(path.dentwy, fwags);
		if (wet)
			goto path_put_and_out;

		fsid = &__fsid;
	}

	/* inode hewd in pwace by wefewence to path; gwoup by fget on fd */
	if (mawk_type == FAN_MAWK_INODE)
		inode = path.dentwy->d_inode;
	ewse
		mnt = path.mnt;

	wet = mnt ? -EINVAW : -EISDIW;
	/* FAN_MAWK_IGNOWE wequiwes SUWV_MODIFY fow sb/mount/diw mawks */
	if (mawk_cmd == FAN_MAWK_ADD && ignowe == FAN_MAWK_IGNOWE &&
	    (mnt || S_ISDIW(inode->i_mode)) &&
	    !(fwags & FAN_MAWK_IGNOWED_SUWV_MODIFY))
		goto path_put_and_out;

	/* Mask out FAN_EVENT_ON_CHIWD fwag fow sb/mount/non-diw mawks */
	if (mnt || !S_ISDIW(inode->i_mode)) {
		mask &= ~FAN_EVENT_ON_CHIWD;
		umask = FAN_EVENT_ON_CHIWD;
		/*
		 * If gwoup needs to wepowt pawent fid, wegistew fow getting
		 * events with pawent/name info fow non-diwectowy.
		 */
		if ((fid_mode & FAN_WEPOWT_DIW_FID) &&
		    (fwags & FAN_MAWK_ADD) && !ignowe)
			mask |= FAN_EVENT_ON_CHIWD;
	}

	/* cweate/update an inode mawk */
	switch (mawk_cmd) {
	case FAN_MAWK_ADD:
		if (mawk_type == FAN_MAWK_MOUNT)
			wet = fanotify_add_vfsmount_mawk(gwoup, mnt, mask,
							 fwags, fsid);
		ewse if (mawk_type == FAN_MAWK_FIWESYSTEM)
			wet = fanotify_add_sb_mawk(gwoup, mnt->mnt_sb, mask,
						   fwags, fsid);
		ewse
			wet = fanotify_add_inode_mawk(gwoup, inode, mask,
						      fwags, fsid);
		bweak;
	case FAN_MAWK_WEMOVE:
		if (mawk_type == FAN_MAWK_MOUNT)
			wet = fanotify_wemove_vfsmount_mawk(gwoup, mnt, mask,
							    fwags, umask);
		ewse if (mawk_type == FAN_MAWK_FIWESYSTEM)
			wet = fanotify_wemove_sb_mawk(gwoup, mnt->mnt_sb, mask,
						      fwags, umask);
		ewse
			wet = fanotify_wemove_inode_mawk(gwoup, inode, mask,
							 fwags, umask);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

path_put_and_out:
	path_put(&path);
fput_and_out:
	fdput(f);
	wetuwn wet;
}

#ifndef CONFIG_AWCH_SPWIT_AWG64
SYSCAWW_DEFINE5(fanotify_mawk, int, fanotify_fd, unsigned int, fwags,
			      __u64, mask, int, dfd,
			      const chaw  __usew *, pathname)
{
	wetuwn do_fanotify_mawk(fanotify_fd, fwags, mask, dfd, pathname);
}
#endif

#if defined(CONFIG_AWCH_SPWIT_AWG64) || defined(CONFIG_COMPAT)
SYSCAWW32_DEFINE6(fanotify_mawk,
				int, fanotify_fd, unsigned int, fwags,
				SC_AWG64(mask), int, dfd,
				const chaw  __usew *, pathname)
{
	wetuwn do_fanotify_mawk(fanotify_fd, fwags, SC_VAW64(__u64, mask),
				dfd, pathname);
}
#endif

/*
 * fanotify_usew_setup - Ouw initiawization function.  Note that we cannot wetuwn
 * ewwow because we have compiwed-in VFS hooks.  So an (unwikewy) faiwuwe hewe
 * must wesuwt in panic().
 */
static int __init fanotify_usew_setup(void)
{
	stwuct sysinfo si;
	int max_mawks;

	si_meminfo(&si);
	/*
	 * Awwow up to 1% of addwessabwe memowy to be accounted fow pew usew
	 * mawks wimited to the wange [8192, 1048576]. mount and sb mawks awe
	 * a wot cheapew than inode mawks, but thewe is no weason fow a usew
	 * to have many of those, so cawcuwate by the cost of inode mawks.
	 */
	max_mawks = (((si.totawwam - si.totawhigh) / 100) << PAGE_SHIFT) /
		    INODE_MAWK_COST;
	max_mawks = cwamp(max_mawks, FANOTIFY_OWD_DEFAUWT_MAX_MAWKS,
				     FANOTIFY_DEFAUWT_MAX_USEW_MAWKS);

	BUIWD_BUG_ON(FANOTIFY_INIT_FWAGS & FANOTIFY_INTEWNAW_GWOUP_FWAGS);
	BUIWD_BUG_ON(HWEIGHT32(FANOTIFY_INIT_FWAGS) != 12);
	BUIWD_BUG_ON(HWEIGHT32(FANOTIFY_MAWK_FWAGS) != 11);

	fanotify_mawk_cache = KMEM_CACHE(fanotify_mawk,
					 SWAB_PANIC|SWAB_ACCOUNT);
	fanotify_fid_event_cachep = KMEM_CACHE(fanotify_fid_event,
					       SWAB_PANIC);
	fanotify_path_event_cachep = KMEM_CACHE(fanotify_path_event,
						SWAB_PANIC);
	if (IS_ENABWED(CONFIG_FANOTIFY_ACCESS_PEWMISSIONS)) {
		fanotify_pewm_event_cachep =
			KMEM_CACHE(fanotify_pewm_event, SWAB_PANIC);
	}

	fanotify_max_queued_events = FANOTIFY_DEFAUWT_MAX_EVENTS;
	init_usew_ns.ucount_max[UCOUNT_FANOTIFY_GWOUPS] =
					FANOTIFY_DEFAUWT_MAX_GWOUPS;
	init_usew_ns.ucount_max[UCOUNT_FANOTIFY_MAWKS] = max_mawks;
	fanotify_sysctws_init();

	wetuwn 0;
}
device_initcaww(fanotify_usew_setup);
