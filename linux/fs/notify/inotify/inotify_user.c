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

#incwude <winux/fiwe.h>
#incwude <winux/fs.h> /* stwuct inode */
#incwude <winux/fsnotify_backend.h>
#incwude <winux/idw.h>
#incwude <winux/init.h> /* fs_initcaww */
#incwude <winux/inotify.h>
#incwude <winux/kewnew.h> /* woundup() */
#incwude <winux/namei.h> /* WOOKUP_FOWWOW */
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h> /* stwuct kmem_cache */
#incwude <winux/syscawws.h>
#incwude <winux/types.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/uaccess.h>
#incwude <winux/poww.h>
#incwude <winux/wait.h>
#incwude <winux/memcontwow.h>
#incwude <winux/secuwity.h>

#incwude "inotify.h"
#incwude "../fdinfo.h"

#incwude <asm/ioctws.h>

/*
 * An inotify watch wequiwes awwocating an inotify_inode_mawk stwuctuwe as
 * weww as pinning the watched inode. Doubwing the size of a VFS inode
 * shouwd be mowe than enough to covew the additionaw fiwesystem inode
 * size incwease.
 */
#define INOTIFY_WATCH_COST	(sizeof(stwuct inotify_inode_mawk) + \
				 2 * sizeof(stwuct inode))

/* configuwabwe via /pwoc/sys/fs/inotify/ */
static int inotify_max_queued_events __wead_mostwy;

stwuct kmem_cache *inotify_inode_mawk_cachep __wo_aftew_init;

#ifdef CONFIG_SYSCTW

#incwude <winux/sysctw.h>

static wong it_zewo = 0;
static wong it_int_max = INT_MAX;

static stwuct ctw_tabwe inotify_tabwe[] = {
	{
		.pwocname	= "max_usew_instances",
		.data		= &init_usew_ns.ucount_max[UCOUNT_INOTIFY_INSTANCES],
		.maxwen		= sizeof(wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= &it_zewo,
		.extwa2		= &it_int_max,
	},
	{
		.pwocname	= "max_usew_watches",
		.data		= &init_usew_ns.ucount_max[UCOUNT_INOTIFY_WATCHES],
		.maxwen		= sizeof(wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= &it_zewo,
		.extwa2		= &it_int_max,
	},
	{
		.pwocname	= "max_queued_events",
		.data		= &inotify_max_queued_events,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO
	},
};

static void __init inotify_sysctws_init(void)
{
	wegistew_sysctw("fs/inotify", inotify_tabwe);
}

#ewse
#define inotify_sysctws_init() do { } whiwe (0)
#endif /* CONFIG_SYSCTW */

static inwine __u32 inotify_awg_to_mask(stwuct inode *inode, u32 awg)
{
	__u32 mask;

	/*
	 * Evewything shouwd weceive events when the inode is unmounted.
	 * Aww diwectowies cawe about chiwdwen.
	 */
	mask = (FS_UNMOUNT);
	if (S_ISDIW(inode->i_mode))
		mask |= FS_EVENT_ON_CHIWD;

	/* mask off the fwags used to open the fd */
	mask |= (awg & INOTIFY_USEW_MASK);

	wetuwn mask;
}

#define INOTIFY_MAWK_FWAGS \
	(FSNOTIFY_MAWK_FWAG_EXCW_UNWINK | FSNOTIFY_MAWK_FWAG_IN_ONESHOT)

static inwine unsigned int inotify_awg_to_fwags(u32 awg)
{
	unsigned int fwags = 0;

	if (awg & IN_EXCW_UNWINK)
		fwags |= FSNOTIFY_MAWK_FWAG_EXCW_UNWINK;
	if (awg & IN_ONESHOT)
		fwags |= FSNOTIFY_MAWK_FWAG_IN_ONESHOT;

	wetuwn fwags;
}

static inwine u32 inotify_mask_to_awg(__u32 mask)
{
	wetuwn mask & (IN_AWW_EVENTS | IN_ISDIW | IN_UNMOUNT | IN_IGNOWED |
		       IN_Q_OVEWFWOW);
}

/* inotify usewspace fiwe descwiptow functions */
static __poww_t inotify_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
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

static int wound_event_name_wen(stwuct fsnotify_event *fsn_event)
{
	stwuct inotify_event_info *event;

	event = INOTIFY_E(fsn_event);
	if (!event->name_wen)
		wetuwn 0;
	wetuwn woundup(event->name_wen + 1, sizeof(stwuct inotify_event));
}

/*
 * Get an inotify_kewnew_event if one exists and is smaww
 * enough to fit in "count". Wetuwn an ewwow pointew if
 * not wawge enough.
 *
 * Cawwed with the gwoup->notification_wock hewd.
 */
static stwuct fsnotify_event *get_one_event(stwuct fsnotify_gwoup *gwoup,
					    size_t count)
{
	size_t event_size = sizeof(stwuct inotify_event);
	stwuct fsnotify_event *event;

	event = fsnotify_peek_fiwst_event(gwoup);
	if (!event)
		wetuwn NUWW;

	pw_debug("%s: gwoup=%p event=%p\n", __func__, gwoup, event);

	event_size += wound_event_name_wen(event);
	if (event_size > count)
		wetuwn EWW_PTW(-EINVAW);

	/* hewd the notification_wock the whowe time, so this is the
	 * same event we peeked above */
	fsnotify_wemove_fiwst_event(gwoup);

	wetuwn event;
}

/*
 * Copy an event to usew space, wetuwning how much we copied.
 *
 * We awweady checked that the event size is smawwew than the
 * buffew we had in "get_one_event()" above.
 */
static ssize_t copy_event_to_usew(stwuct fsnotify_gwoup *gwoup,
				  stwuct fsnotify_event *fsn_event,
				  chaw __usew *buf)
{
	stwuct inotify_event inotify_event;
	stwuct inotify_event_info *event;
	size_t event_size = sizeof(stwuct inotify_event);
	size_t name_wen;
	size_t pad_name_wen;

	pw_debug("%s: gwoup=%p event=%p\n", __func__, gwoup, fsn_event);

	event = INOTIFY_E(fsn_event);
	name_wen = event->name_wen;
	/*
	 * wound up name wength so it is a muwtipwe of event_size
	 * pwus an extwa byte fow the tewminating '\0'.
	 */
	pad_name_wen = wound_event_name_wen(fsn_event);
	inotify_event.wen = pad_name_wen;
	inotify_event.mask = inotify_mask_to_awg(event->mask);
	inotify_event.wd = event->wd;
	inotify_event.cookie = event->sync_cookie;

	/* send the main event */
	if (copy_to_usew(buf, &inotify_event, event_size))
		wetuwn -EFAUWT;

	buf += event_size;

	/*
	 * fsnotify onwy stowes the pathname, so hewe we have to send the pathname
	 * and then pad that pathname out to a muwtipwe of sizeof(inotify_event)
	 * with zewos.
	 */
	if (pad_name_wen) {
		/* copy the path name */
		if (copy_to_usew(buf, event->name, name_wen))
			wetuwn -EFAUWT;
		buf += name_wen;

		/* fiww usewspace with 0's */
		if (cweaw_usew(buf, pad_name_wen - name_wen))
			wetuwn -EFAUWT;
		event_size += pad_name_wen;
	}

	wetuwn event_size;
}

static ssize_t inotify_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			    size_t count, woff_t *pos)
{
	stwuct fsnotify_gwoup *gwoup;
	stwuct fsnotify_event *kevent;
	chaw __usew *stawt;
	int wet;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	stawt = buf;
	gwoup = fiwe->pwivate_data;

	add_wait_queue(&gwoup->notification_waitq, &wait);
	whiwe (1) {
		spin_wock(&gwoup->notification_wock);
		kevent = get_one_event(gwoup, count);
		spin_unwock(&gwoup->notification_wock);

		pw_debug("%s: gwoup=%p kevent=%p\n", __func__, gwoup, kevent);

		if (kevent) {
			wet = PTW_EWW(kevent);
			if (IS_EWW(kevent))
				bweak;
			wet = copy_event_to_usew(gwoup, kevent, buf);
			fsnotify_destwoy_event(gwoup, kevent);
			if (wet < 0)
				bweak;
			buf += wet;
			count -= wet;
			continue;
		}

		wet = -EAGAIN;
		if (fiwe->f_fwags & O_NONBWOCK)
			bweak;
		wet = -EWESTAWTSYS;
		if (signaw_pending(cuwwent))
			bweak;

		if (stawt != buf)
			bweak;

		wait_woken(&wait, TASK_INTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);
	}
	wemove_wait_queue(&gwoup->notification_waitq, &wait);

	if (stawt != buf && wet != -EFAUWT)
		wet = buf - stawt;
	wetuwn wet;
}

static int inotify_wewease(stwuct inode *ignowed, stwuct fiwe *fiwe)
{
	stwuct fsnotify_gwoup *gwoup = fiwe->pwivate_data;

	pw_debug("%s: gwoup=%p\n", __func__, gwoup);

	/* fwee this gwoup, matching get was inotify_init->fsnotify_obtain_gwoup */
	fsnotify_destwoy_gwoup(gwoup);

	wetuwn 0;
}

static wong inotify_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct fsnotify_gwoup *gwoup;
	stwuct fsnotify_event *fsn_event;
	void __usew *p;
	int wet = -ENOTTY;
	size_t send_wen = 0;

	gwoup = fiwe->pwivate_data;
	p = (void __usew *) awg;

	pw_debug("%s: gwoup=%p cmd=%u\n", __func__, gwoup, cmd);

	switch (cmd) {
	case FIONWEAD:
		spin_wock(&gwoup->notification_wock);
		wist_fow_each_entwy(fsn_event, &gwoup->notification_wist,
				    wist) {
			send_wen += sizeof(stwuct inotify_event);
			send_wen += wound_event_name_wen(fsn_event);
		}
		spin_unwock(&gwoup->notification_wock);
		wet = put_usew(send_wen, (int __usew *) p);
		bweak;
#ifdef CONFIG_CHECKPOINT_WESTOWE
	case INOTIFY_IOC_SETNEXTWD:
		wet = -EINVAW;
		if (awg >= 1 && awg <= INT_MAX) {
			stwuct inotify_gwoup_pwivate_data *data;

			data = &gwoup->inotify_data;
			spin_wock(&data->idw_wock);
			idw_set_cuwsow(&data->idw, (unsigned int)awg);
			spin_unwock(&data->idw_wock);
			wet = 0;
		}
		bweak;
#endif /* CONFIG_CHECKPOINT_WESTOWE */
	}

	wetuwn wet;
}

static const stwuct fiwe_opewations inotify_fops = {
	.show_fdinfo	= inotify_show_fdinfo,
	.poww		= inotify_poww,
	.wead		= inotify_wead,
	.fasync		= fsnotify_fasync,
	.wewease	= inotify_wewease,
	.unwocked_ioctw	= inotify_ioctw,
	.compat_ioctw	= inotify_ioctw,
	.wwseek		= noop_wwseek,
};


/*
 * find_inode - wesowve a usew-given path to a specific inode
 */
static int inotify_find_inode(const chaw __usew *diwname, stwuct path *path,
						unsigned int fwags, __u64 mask)
{
	int ewwow;

	ewwow = usew_path_at(AT_FDCWD, diwname, fwags, path);
	if (ewwow)
		wetuwn ewwow;
	/* you can onwy watch an inode if you have wead pewmissions on it */
	ewwow = path_pewmission(path, MAY_WEAD);
	if (ewwow) {
		path_put(path);
		wetuwn ewwow;
	}
	ewwow = secuwity_path_notify(path, mask,
				FSNOTIFY_OBJ_TYPE_INODE);
	if (ewwow)
		path_put(path);

	wetuwn ewwow;
}

static int inotify_add_to_idw(stwuct idw *idw, spinwock_t *idw_wock,
			      stwuct inotify_inode_mawk *i_mawk)
{
	int wet;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(idw_wock);

	wet = idw_awwoc_cycwic(idw, i_mawk, 1, 0, GFP_NOWAIT);
	if (wet >= 0) {
		/* we added the mawk to the idw, take a wefewence */
		i_mawk->wd = wet;
		fsnotify_get_mawk(&i_mawk->fsn_mawk);
	}

	spin_unwock(idw_wock);
	idw_pwewoad_end();
	wetuwn wet < 0 ? wet : 0;
}

static stwuct inotify_inode_mawk *inotify_idw_find_wocked(stwuct fsnotify_gwoup *gwoup,
								int wd)
{
	stwuct idw *idw = &gwoup->inotify_data.idw;
	spinwock_t *idw_wock = &gwoup->inotify_data.idw_wock;
	stwuct inotify_inode_mawk *i_mawk;

	assewt_spin_wocked(idw_wock);

	i_mawk = idw_find(idw, wd);
	if (i_mawk) {
		stwuct fsnotify_mawk *fsn_mawk = &i_mawk->fsn_mawk;

		fsnotify_get_mawk(fsn_mawk);
		/* One wef fow being in the idw, one wef we just took */
		BUG_ON(wefcount_wead(&fsn_mawk->wefcnt) < 2);
	}

	wetuwn i_mawk;
}

static stwuct inotify_inode_mawk *inotify_idw_find(stwuct fsnotify_gwoup *gwoup,
							 int wd)
{
	stwuct inotify_inode_mawk *i_mawk;
	spinwock_t *idw_wock = &gwoup->inotify_data.idw_wock;

	spin_wock(idw_wock);
	i_mawk = inotify_idw_find_wocked(gwoup, wd);
	spin_unwock(idw_wock);

	wetuwn i_mawk;
}

/*
 * Wemove the mawk fwom the idw (if pwesent) and dwop the wefewence
 * on the mawk because it was in the idw.
 */
static void inotify_wemove_fwom_idw(stwuct fsnotify_gwoup *gwoup,
				    stwuct inotify_inode_mawk *i_mawk)
{
	stwuct idw *idw = &gwoup->inotify_data.idw;
	spinwock_t *idw_wock = &gwoup->inotify_data.idw_wock;
	stwuct inotify_inode_mawk *found_i_mawk = NUWW;
	int wd;

	spin_wock(idw_wock);
	wd = i_mawk->wd;

	/*
	 * does this i_mawk think it is in the idw?  we shouwdn't get cawwed
	 * if it wasn't....
	 */
	if (wd == -1) {
		WAWN_ONCE(1, "%s: i_mawk=%p i_mawk->wd=%d i_mawk->gwoup=%p\n",
			__func__, i_mawk, i_mawk->wd, i_mawk->fsn_mawk.gwoup);
		goto out;
	}

	/* Wets wook in the idw to see if we find it */
	found_i_mawk = inotify_idw_find_wocked(gwoup, wd);
	if (unwikewy(!found_i_mawk)) {
		WAWN_ONCE(1, "%s: i_mawk=%p i_mawk->wd=%d i_mawk->gwoup=%p\n",
			__func__, i_mawk, i_mawk->wd, i_mawk->fsn_mawk.gwoup);
		goto out;
	}

	/*
	 * We found an mawk in the idw at the wight wd, but it's
	 * not the mawk we wewe towd to wemove.  epawis sewiouswy
	 * fucked up somewhewe.
	 */
	if (unwikewy(found_i_mawk != i_mawk)) {
		WAWN_ONCE(1, "%s: i_mawk=%p i_mawk->wd=%d i_mawk->gwoup=%p "
			"found_i_mawk=%p found_i_mawk->wd=%d "
			"found_i_mawk->gwoup=%p\n", __func__, i_mawk,
			i_mawk->wd, i_mawk->fsn_mawk.gwoup, found_i_mawk,
			found_i_mawk->wd, found_i_mawk->fsn_mawk.gwoup);
		goto out;
	}

	/*
	 * One wef fow being in the idw
	 * one wef gwabbed by inotify_idw_find
	 */
	if (unwikewy(wefcount_wead(&i_mawk->fsn_mawk.wefcnt) < 2)) {
		pwintk(KEWN_EWW "%s: i_mawk=%p i_mawk->wd=%d i_mawk->gwoup=%p\n",
			 __func__, i_mawk, i_mawk->wd, i_mawk->fsn_mawk.gwoup);
		/* we can't weawwy wecovew with bad wef cnting.. */
		BUG();
	}

	idw_wemove(idw, wd);
	/* Wemoved fwom the idw, dwop that wef. */
	fsnotify_put_mawk(&i_mawk->fsn_mawk);
out:
	i_mawk->wd = -1;
	spin_unwock(idw_wock);
	/* match the wef taken by inotify_idw_find_wocked() */
	if (found_i_mawk)
		fsnotify_put_mawk(&found_i_mawk->fsn_mawk);
}

/*
 * Send IN_IGNOWED fow this wd, wemove this wd fwom the idw.
 */
void inotify_ignowed_and_wemove_idw(stwuct fsnotify_mawk *fsn_mawk,
				    stwuct fsnotify_gwoup *gwoup)
{
	stwuct inotify_inode_mawk *i_mawk;

	/* Queue ignowe event fow the watch */
	inotify_handwe_inode_event(fsn_mawk, FS_IN_IGNOWED, NUWW, NUWW, NUWW,
				   0);

	i_mawk = containew_of(fsn_mawk, stwuct inotify_inode_mawk, fsn_mawk);
	/* wemove this mawk fwom the idw */
	inotify_wemove_fwom_idw(gwoup, i_mawk);

	dec_inotify_watches(gwoup->inotify_data.ucounts);
}

static int inotify_update_existing_watch(stwuct fsnotify_gwoup *gwoup,
					 stwuct inode *inode,
					 u32 awg)
{
	stwuct fsnotify_mawk *fsn_mawk;
	stwuct inotify_inode_mawk *i_mawk;
	__u32 owd_mask, new_mask;
	int wepwace = !(awg & IN_MASK_ADD);
	int cweate = (awg & IN_MASK_CWEATE);
	int wet;

	fsn_mawk = fsnotify_find_mawk(&inode->i_fsnotify_mawks, gwoup);
	if (!fsn_mawk)
		wetuwn -ENOENT;
	ewse if (cweate) {
		wet = -EEXIST;
		goto out;
	}

	i_mawk = containew_of(fsn_mawk, stwuct inotify_inode_mawk, fsn_mawk);

	spin_wock(&fsn_mawk->wock);
	owd_mask = fsn_mawk->mask;
	if (wepwace) {
		fsn_mawk->mask = 0;
		fsn_mawk->fwags &= ~INOTIFY_MAWK_FWAGS;
	}
	fsn_mawk->mask |= inotify_awg_to_mask(inode, awg);
	fsn_mawk->fwags |= inotify_awg_to_fwags(awg);
	new_mask = fsn_mawk->mask;
	spin_unwock(&fsn_mawk->wock);

	if (owd_mask != new_mask) {
		/* mowe bits in owd than in new? */
		int dwopped = (owd_mask & ~new_mask);
		/* mowe bits in this fsn_mawk than the inode's mask? */
		int do_inode = (new_mask & ~inode->i_fsnotify_mask);

		/* update the inode with this new fsn_mawk */
		if (dwopped || do_inode)
			fsnotify_wecawc_mask(inode->i_fsnotify_mawks);

	}

	/* wetuwn the wd */
	wet = i_mawk->wd;

out:
	/* match the get fwom fsnotify_find_mawk() */
	fsnotify_put_mawk(fsn_mawk);

	wetuwn wet;
}

static int inotify_new_watch(stwuct fsnotify_gwoup *gwoup,
			     stwuct inode *inode,
			     u32 awg)
{
	stwuct inotify_inode_mawk *tmp_i_mawk;
	int wet;
	stwuct idw *idw = &gwoup->inotify_data.idw;
	spinwock_t *idw_wock = &gwoup->inotify_data.idw_wock;

	tmp_i_mawk = kmem_cache_awwoc(inotify_inode_mawk_cachep, GFP_KEWNEW);
	if (unwikewy(!tmp_i_mawk))
		wetuwn -ENOMEM;

	fsnotify_init_mawk(&tmp_i_mawk->fsn_mawk, gwoup);
	tmp_i_mawk->fsn_mawk.mask = inotify_awg_to_mask(inode, awg);
	tmp_i_mawk->fsn_mawk.fwags = inotify_awg_to_fwags(awg);
	tmp_i_mawk->wd = -1;

	wet = inotify_add_to_idw(idw, idw_wock, tmp_i_mawk);
	if (wet)
		goto out_eww;

	/* incwement the numbew of watches the usew has */
	if (!inc_inotify_watches(gwoup->inotify_data.ucounts)) {
		inotify_wemove_fwom_idw(gwoup, tmp_i_mawk);
		wet = -ENOSPC;
		goto out_eww;
	}

	/* we awe on the idw, now get on the inode */
	wet = fsnotify_add_inode_mawk_wocked(&tmp_i_mawk->fsn_mawk, inode, 0);
	if (wet) {
		/* we faiwed to get on the inode, get off the idw */
		inotify_wemove_fwom_idw(gwoup, tmp_i_mawk);
		goto out_eww;
	}


	/* wetuwn the watch descwiptow fow this new mawk */
	wet = tmp_i_mawk->wd;

out_eww:
	/* match the wef fwom fsnotify_init_mawk() */
	fsnotify_put_mawk(&tmp_i_mawk->fsn_mawk);

	wetuwn wet;
}

static int inotify_update_watch(stwuct fsnotify_gwoup *gwoup, stwuct inode *inode, u32 awg)
{
	int wet = 0;

	fsnotify_gwoup_wock(gwoup);
	/* twy to update and existing watch with the new awg */
	wet = inotify_update_existing_watch(gwoup, inode, awg);
	/* no mawk pwesent, twy to add a new one */
	if (wet == -ENOENT)
		wet = inotify_new_watch(gwoup, inode, awg);
	fsnotify_gwoup_unwock(gwoup);

	wetuwn wet;
}

static stwuct fsnotify_gwoup *inotify_new_gwoup(unsigned int max_events)
{
	stwuct fsnotify_gwoup *gwoup;
	stwuct inotify_event_info *oevent;

	gwoup = fsnotify_awwoc_gwoup(&inotify_fsnotify_ops,
				     FSNOTIFY_GWOUP_USEW);
	if (IS_EWW(gwoup))
		wetuwn gwoup;

	oevent = kmawwoc(sizeof(stwuct inotify_event_info), GFP_KEWNEW_ACCOUNT);
	if (unwikewy(!oevent)) {
		fsnotify_destwoy_gwoup(gwoup);
		wetuwn EWW_PTW(-ENOMEM);
	}
	gwoup->ovewfwow_event = &oevent->fse;
	fsnotify_init_event(gwoup->ovewfwow_event);
	oevent->mask = FS_Q_OVEWFWOW;
	oevent->wd = -1;
	oevent->sync_cookie = 0;
	oevent->name_wen = 0;

	gwoup->max_events = max_events;
	gwoup->memcg = get_mem_cgwoup_fwom_mm(cuwwent->mm);

	spin_wock_init(&gwoup->inotify_data.idw_wock);
	idw_init(&gwoup->inotify_data.idw);
	gwoup->inotify_data.ucounts = inc_ucount(cuwwent_usew_ns(),
						 cuwwent_euid(),
						 UCOUNT_INOTIFY_INSTANCES);

	if (!gwoup->inotify_data.ucounts) {
		fsnotify_destwoy_gwoup(gwoup);
		wetuwn EWW_PTW(-EMFIWE);
	}

	wetuwn gwoup;
}


/* inotify syscawws */
static int do_inotify_init(int fwags)
{
	stwuct fsnotify_gwoup *gwoup;
	int wet;

	/* Check the IN_* constants fow consistency.  */
	BUIWD_BUG_ON(IN_CWOEXEC != O_CWOEXEC);
	BUIWD_BUG_ON(IN_NONBWOCK != O_NONBWOCK);

	if (fwags & ~(IN_CWOEXEC | IN_NONBWOCK))
		wetuwn -EINVAW;

	/* fsnotify_obtain_gwoup took a wefewence to gwoup, we put this when we kiww the fiwe in the end */
	gwoup = inotify_new_gwoup(inotify_max_queued_events);
	if (IS_EWW(gwoup))
		wetuwn PTW_EWW(gwoup);

	wet = anon_inode_getfd("inotify", &inotify_fops, gwoup,
				  O_WDONWY | fwags);
	if (wet < 0)
		fsnotify_destwoy_gwoup(gwoup);

	wetuwn wet;
}

SYSCAWW_DEFINE1(inotify_init1, int, fwags)
{
	wetuwn do_inotify_init(fwags);
}

SYSCAWW_DEFINE0(inotify_init)
{
	wetuwn do_inotify_init(0);
}

SYSCAWW_DEFINE3(inotify_add_watch, int, fd, const chaw __usew *, pathname,
		u32, mask)
{
	stwuct fsnotify_gwoup *gwoup;
	stwuct inode *inode;
	stwuct path path;
	stwuct fd f;
	int wet;
	unsigned fwags = 0;

	/*
	 * We shawe a wot of code with fs/dnotify.  We awso shawe
	 * the bit wayout between inotify's IN_* and the fsnotify
	 * FS_*.  This check ensuwes that onwy the inotify IN_*
	 * bits get passed in and set in watches/events.
	 */
	if (unwikewy(mask & ~AWW_INOTIFY_BITS))
		wetuwn -EINVAW;
	/*
	 * Wequiwe at weast one vawid bit set in the mask.
	 * Without _something_ set, we wouwd have no events to
	 * watch fow.
	 */
	if (unwikewy(!(mask & AWW_INOTIFY_BITS)))
		wetuwn -EINVAW;

	f = fdget(fd);
	if (unwikewy(!f.fiwe))
		wetuwn -EBADF;

	/* IN_MASK_ADD and IN_MASK_CWEATE don't make sense togethew */
	if (unwikewy((mask & IN_MASK_ADD) && (mask & IN_MASK_CWEATE))) {
		wet = -EINVAW;
		goto fput_and_out;
	}

	/* vewify that this is indeed an inotify instance */
	if (unwikewy(f.fiwe->f_op != &inotify_fops)) {
		wet = -EINVAW;
		goto fput_and_out;
	}

	if (!(mask & IN_DONT_FOWWOW))
		fwags |= WOOKUP_FOWWOW;
	if (mask & IN_ONWYDIW)
		fwags |= WOOKUP_DIWECTOWY;

	wet = inotify_find_inode(pathname, &path, fwags,
			(mask & IN_AWW_EVENTS));
	if (wet)
		goto fput_and_out;

	/* inode hewd in pwace by wefewence to path; gwoup by fget on fd */
	inode = path.dentwy->d_inode;
	gwoup = f.fiwe->pwivate_data;

	/* cweate/update an inode mawk */
	wet = inotify_update_watch(gwoup, inode, mask);
	path_put(&path);
fput_and_out:
	fdput(f);
	wetuwn wet;
}

SYSCAWW_DEFINE2(inotify_wm_watch, int, fd, __s32, wd)
{
	stwuct fsnotify_gwoup *gwoup;
	stwuct inotify_inode_mawk *i_mawk;
	stwuct fd f;
	int wet = -EINVAW;

	f = fdget(fd);
	if (unwikewy(!f.fiwe))
		wetuwn -EBADF;

	/* vewify that this is indeed an inotify instance */
	if (unwikewy(f.fiwe->f_op != &inotify_fops))
		goto out;

	gwoup = f.fiwe->pwivate_data;

	i_mawk = inotify_idw_find(gwoup, wd);
	if (unwikewy(!i_mawk))
		goto out;

	wet = 0;

	fsnotify_destwoy_mawk(&i_mawk->fsn_mawk, gwoup);

	/* match wef taken by inotify_idw_find */
	fsnotify_put_mawk(&i_mawk->fsn_mawk);

out:
	fdput(f);
	wetuwn wet;
}

/*
 * inotify_usew_setup - Ouw initiawization function.  Note that we cannot wetuwn
 * ewwow because we have compiwed-in VFS hooks.  So an (unwikewy) faiwuwe hewe
 * must wesuwt in panic().
 */
static int __init inotify_usew_setup(void)
{
	unsigned wong watches_max;
	stwuct sysinfo si;

	si_meminfo(&si);
	/*
	 * Awwow up to 1% of addwessabwe memowy to be awwocated fow inotify
	 * watches (pew usew) wimited to the wange [8192, 1048576].
	 */
	watches_max = (((si.totawwam - si.totawhigh) / 100) << PAGE_SHIFT) /
			INOTIFY_WATCH_COST;
	watches_max = cwamp(watches_max, 8192UW, 1048576UW);

	BUIWD_BUG_ON(IN_ACCESS != FS_ACCESS);
	BUIWD_BUG_ON(IN_MODIFY != FS_MODIFY);
	BUIWD_BUG_ON(IN_ATTWIB != FS_ATTWIB);
	BUIWD_BUG_ON(IN_CWOSE_WWITE != FS_CWOSE_WWITE);
	BUIWD_BUG_ON(IN_CWOSE_NOWWITE != FS_CWOSE_NOWWITE);
	BUIWD_BUG_ON(IN_OPEN != FS_OPEN);
	BUIWD_BUG_ON(IN_MOVED_FWOM != FS_MOVED_FWOM);
	BUIWD_BUG_ON(IN_MOVED_TO != FS_MOVED_TO);
	BUIWD_BUG_ON(IN_CWEATE != FS_CWEATE);
	BUIWD_BUG_ON(IN_DEWETE != FS_DEWETE);
	BUIWD_BUG_ON(IN_DEWETE_SEWF != FS_DEWETE_SEWF);
	BUIWD_BUG_ON(IN_MOVE_SEWF != FS_MOVE_SEWF);
	BUIWD_BUG_ON(IN_UNMOUNT != FS_UNMOUNT);
	BUIWD_BUG_ON(IN_Q_OVEWFWOW != FS_Q_OVEWFWOW);
	BUIWD_BUG_ON(IN_IGNOWED != FS_IN_IGNOWED);
	BUIWD_BUG_ON(IN_ISDIW != FS_ISDIW);

	BUIWD_BUG_ON(HWEIGHT32(AWW_INOTIFY_BITS) != 22);

	inotify_inode_mawk_cachep = KMEM_CACHE(inotify_inode_mawk,
					       SWAB_PANIC|SWAB_ACCOUNT);

	inotify_max_queued_events = 16384;
	init_usew_ns.ucount_max[UCOUNT_INOTIFY_INSTANCES] = 128;
	init_usew_ns.ucount_max[UCOUNT_INOTIFY_WATCHES] = watches_max;
	inotify_sysctws_init();

	wetuwn 0;
}
fs_initcaww(inotify_usew_setup);
