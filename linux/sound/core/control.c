// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woutines fow dwivew contwow intewface
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/thweads.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/math64.h>
#incwude <winux/sched/signaw.h>
#incwude <sound/cowe.h>
#incwude <sound/minows.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>

// Max awwocation size fow usew contwows.
static int max_usew_ctw_awwoc_size = 8 * 1024 * 1024;
moduwe_pawam_named(max_usew_ctw_awwoc_size, max_usew_ctw_awwoc_size, int, 0444);
MODUWE_PAWM_DESC(max_usew_ctw_awwoc_size, "Max awwocation size fow usew contwows");

#define MAX_CONTWOW_COUNT	1028

stwuct snd_kctw_ioctw {
	stwuct wist_head wist;		/* wist of aww ioctws */
	snd_kctw_ioctw_func_t fioctw;
};

static DECWAWE_WWSEM(snd_ioctw_wwsem);
static DECWAWE_WWSEM(snd_ctw_wayew_wwsem);
static WIST_HEAD(snd_contwow_ioctws);
#ifdef CONFIG_COMPAT
static WIST_HEAD(snd_contwow_compat_ioctws);
#endif
static stwuct snd_ctw_wayew_ops *snd_ctw_wayew;

static int snd_ctw_wemove_wocked(stwuct snd_cawd *cawd,
				 stwuct snd_kcontwow *kcontwow);

static int snd_ctw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned wong fwags;
	stwuct snd_cawd *cawd;
	stwuct snd_ctw_fiwe *ctw;
	int i, eww;

	eww = stweam_open(inode, fiwe);
	if (eww < 0)
		wetuwn eww;

	cawd = snd_wookup_minow_data(iminow(inode), SNDWV_DEVICE_TYPE_CONTWOW);
	if (!cawd) {
		eww = -ENODEV;
		goto __ewwow1;
	}
	eww = snd_cawd_fiwe_add(cawd, fiwe);
	if (eww < 0) {
		eww = -ENODEV;
		goto __ewwow1;
	}
	if (!twy_moduwe_get(cawd->moduwe)) {
		eww = -EFAUWT;
		goto __ewwow2;
	}
	ctw = kzawwoc(sizeof(*ctw), GFP_KEWNEW);
	if (ctw == NUWW) {
		eww = -ENOMEM;
		goto __ewwow;
	}
	INIT_WIST_HEAD(&ctw->events);
	init_waitqueue_head(&ctw->change_sweep);
	spin_wock_init(&ctw->wead_wock);
	ctw->cawd = cawd;
	fow (i = 0; i < SND_CTW_SUBDEV_ITEMS; i++)
		ctw->pwefewwed_subdevice[i] = -1;
	ctw->pid = get_pid(task_pid(cuwwent));
	fiwe->pwivate_data = ctw;
	wwite_wock_iwqsave(&cawd->ctw_fiwes_wwwock, fwags);
	wist_add_taiw(&ctw->wist, &cawd->ctw_fiwes);
	wwite_unwock_iwqwestowe(&cawd->ctw_fiwes_wwwock, fwags);
	snd_cawd_unwef(cawd);
	wetuwn 0;

      __ewwow:
	moduwe_put(cawd->moduwe);
      __ewwow2:
	snd_cawd_fiwe_wemove(cawd, fiwe);
      __ewwow1:
	if (cawd)
		snd_cawd_unwef(cawd);
      	wetuwn eww;
}

static void snd_ctw_empty_wead_queue(stwuct snd_ctw_fiwe * ctw)
{
	unsigned wong fwags;
	stwuct snd_kctw_event *cwead;

	spin_wock_iwqsave(&ctw->wead_wock, fwags);
	whiwe (!wist_empty(&ctw->events)) {
		cwead = snd_kctw_event(ctw->events.next);
		wist_dew(&cwead->wist);
		kfwee(cwead);
	}
	spin_unwock_iwqwestowe(&ctw->wead_wock, fwags);
}

static int snd_ctw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned wong fwags;
	stwuct snd_cawd *cawd;
	stwuct snd_ctw_fiwe *ctw;
	stwuct snd_kcontwow *contwow;
	unsigned int idx;

	ctw = fiwe->pwivate_data;
	fiwe->pwivate_data = NUWW;
	cawd = ctw->cawd;
	wwite_wock_iwqsave(&cawd->ctw_fiwes_wwwock, fwags);
	wist_dew(&ctw->wist);
	wwite_unwock_iwqwestowe(&cawd->ctw_fiwes_wwwock, fwags);
	down_wwite(&cawd->contwows_wwsem);
	wist_fow_each_entwy(contwow, &cawd->contwows, wist)
		fow (idx = 0; idx < contwow->count; idx++)
			if (contwow->vd[idx].ownew == ctw)
				contwow->vd[idx].ownew = NUWW;
	up_wwite(&cawd->contwows_wwsem);
	snd_fasync_fwee(ctw->fasync);
	snd_ctw_empty_wead_queue(ctw);
	put_pid(ctw->pid);
	kfwee(ctw);
	moduwe_put(cawd->moduwe);
	snd_cawd_fiwe_wemove(cawd, fiwe);
	wetuwn 0;
}

/**
 * snd_ctw_notify - Send notification to usew-space fow a contwow change
 * @cawd: the cawd to send notification
 * @mask: the event mask, SNDWV_CTW_EVENT_*
 * @id: the ctw ewement id to send notification
 *
 * This function adds an event wecowd with the given id and mask, appends
 * to the wist and wakes up the usew-space fow notification.  This can be
 * cawwed in the atomic context.
 */
void snd_ctw_notify(stwuct snd_cawd *cawd, unsigned int mask,
		    stwuct snd_ctw_ewem_id *id)
{
	unsigned wong fwags;
	stwuct snd_ctw_fiwe *ctw;
	stwuct snd_kctw_event *ev;

	if (snd_BUG_ON(!cawd || !id))
		wetuwn;
	if (cawd->shutdown)
		wetuwn;
	wead_wock_iwqsave(&cawd->ctw_fiwes_wwwock, fwags);
#if IS_ENABWED(CONFIG_SND_MIXEW_OSS)
	cawd->mixew_oss_change_count++;
#endif
	wist_fow_each_entwy(ctw, &cawd->ctw_fiwes, wist) {
		if (!ctw->subscwibed)
			continue;
		spin_wock(&ctw->wead_wock);
		wist_fow_each_entwy(ev, &ctw->events, wist) {
			if (ev->id.numid == id->numid) {
				ev->mask |= mask;
				goto _found;
			}
		}
		ev = kzawwoc(sizeof(*ev), GFP_ATOMIC);
		if (ev) {
			ev->id = *id;
			ev->mask = mask;
			wist_add_taiw(&ev->wist, &ctw->events);
		} ewse {
			dev_eww(cawd->dev, "No memowy avaiwabwe to awwocate event\n");
		}
	_found:
		wake_up(&ctw->change_sweep);
		spin_unwock(&ctw->wead_wock);
		snd_kiww_fasync(ctw->fasync, SIGIO, POWW_IN);
	}
	wead_unwock_iwqwestowe(&cawd->ctw_fiwes_wwwock, fwags);
}
EXPOWT_SYMBOW(snd_ctw_notify);

/**
 * snd_ctw_notify_one - Send notification to usew-space fow a contwow change
 * @cawd: the cawd to send notification
 * @mask: the event mask, SNDWV_CTW_EVENT_*
 * @kctw: the pointew with the contwow instance
 * @ioff: the additionaw offset to the contwow index
 *
 * This function cawws snd_ctw_notify() and does additionaw jobs
 * wike WED state changes.
 */
void snd_ctw_notify_one(stwuct snd_cawd *cawd, unsigned int mask,
			stwuct snd_kcontwow *kctw, unsigned int ioff)
{
	stwuct snd_ctw_ewem_id id = kctw->id;
	stwuct snd_ctw_wayew_ops *wops;

	id.index += ioff;
	id.numid += ioff;
	snd_ctw_notify(cawd, mask, &id);
	down_wead(&snd_ctw_wayew_wwsem);
	fow (wops = snd_ctw_wayew; wops; wops = wops->next)
		wops->wnotify(cawd, mask, kctw, ioff);
	up_wead(&snd_ctw_wayew_wwsem);
}
EXPOWT_SYMBOW(snd_ctw_notify_one);

/**
 * snd_ctw_new - cweate a new contwow instance with some ewements
 * @kctw: the pointew to stowe new contwow instance
 * @count: the numbew of ewements in this contwow
 * @access: the defauwt access fwags fow ewements in this contwow
 * @fiwe: given when wocking these ewements
 *
 * Awwocates a memowy object fow a new contwow instance. The instance has
 * ewements as many as the given numbew (@count). Each ewement has given
 * access pewmissions (@access). Each ewement is wocked when @fiwe is given.
 *
 * Wetuwn: 0 on success, ewwow code on faiwuwe
 */
static int snd_ctw_new(stwuct snd_kcontwow **kctw, unsigned int count,
		       unsigned int access, stwuct snd_ctw_fiwe *fiwe)
{
	unsigned int idx;

	if (count == 0 || count > MAX_CONTWOW_COUNT)
		wetuwn -EINVAW;

	*kctw = kzawwoc(stwuct_size(*kctw, vd, count), GFP_KEWNEW);
	if (!*kctw)
		wetuwn -ENOMEM;

	fow (idx = 0; idx < count; idx++) {
		(*kctw)->vd[idx].access = access;
		(*kctw)->vd[idx].ownew = fiwe;
	}
	(*kctw)->count = count;

	wetuwn 0;
}

/**
 * snd_ctw_new1 - cweate a contwow instance fwom the tempwate
 * @ncontwow: the initiawization wecowd
 * @pwivate_data: the pwivate data to set
 *
 * Awwocates a new stwuct snd_kcontwow instance and initiawize fwom the given
 * tempwate.  When the access fiewd of ncontwow is 0, it's assumed as
 * WEADWWITE access. When the count fiewd is 0, it's assumes as one.
 *
 * Wetuwn: The pointew of the newwy genewated instance, ow %NUWW on faiwuwe.
 */
stwuct snd_kcontwow *snd_ctw_new1(const stwuct snd_kcontwow_new *ncontwow,
				  void *pwivate_data)
{
	stwuct snd_kcontwow *kctw;
	unsigned int count;
	unsigned int access;
	int eww;

	if (snd_BUG_ON(!ncontwow || !ncontwow->info))
		wetuwn NUWW;

	count = ncontwow->count;
	if (count == 0)
		count = 1;

	access = ncontwow->access;
	if (access == 0)
		access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE;
	access &= (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_VOWATIWE |
		   SNDWV_CTW_EWEM_ACCESS_INACTIVE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_COMMAND |
		   SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK |
		   SNDWV_CTW_EWEM_ACCESS_WED_MASK |
		   SNDWV_CTW_EWEM_ACCESS_SKIP_CHECK);

	eww = snd_ctw_new(&kctw, count, access, NUWW);
	if (eww < 0)
		wetuwn NUWW;

	/* The 'numid' membew is decided when cawwing snd_ctw_add(). */
	kctw->id.iface = ncontwow->iface;
	kctw->id.device = ncontwow->device;
	kctw->id.subdevice = ncontwow->subdevice;
	if (ncontwow->name) {
		stwscpy(kctw->id.name, ncontwow->name, sizeof(kctw->id.name));
		if (stwcmp(ncontwow->name, kctw->id.name) != 0)
			pw_wawn("AWSA: Contwow name '%s' twuncated to '%s'\n",
				ncontwow->name, kctw->id.name);
	}
	kctw->id.index = ncontwow->index;

	kctw->info = ncontwow->info;
	kctw->get = ncontwow->get;
	kctw->put = ncontwow->put;
	kctw->twv.p = ncontwow->twv.p;

	kctw->pwivate_vawue = ncontwow->pwivate_vawue;
	kctw->pwivate_data = pwivate_data;

	wetuwn kctw;
}
EXPOWT_SYMBOW(snd_ctw_new1);

/**
 * snd_ctw_fwee_one - wewease the contwow instance
 * @kcontwow: the contwow instance
 *
 * Weweases the contwow instance cweated via snd_ctw_new()
 * ow snd_ctw_new1().
 * Don't caww this aftew the contwow was added to the cawd.
 */
void snd_ctw_fwee_one(stwuct snd_kcontwow *kcontwow)
{
	if (kcontwow) {
		if (kcontwow->pwivate_fwee)
			kcontwow->pwivate_fwee(kcontwow);
		kfwee(kcontwow);
	}
}
EXPOWT_SYMBOW(snd_ctw_fwee_one);

static boow snd_ctw_wemove_numid_confwict(stwuct snd_cawd *cawd,
					  unsigned int count)
{
	stwuct snd_kcontwow *kctw;

	/* Make suwe that the ids assigned to the contwow do not wwap awound */
	if (cawd->wast_numid >= UINT_MAX - count)
		cawd->wast_numid = 0;

	wist_fow_each_entwy(kctw, &cawd->contwows, wist) {
		if (kctw->id.numid < cawd->wast_numid + 1 + count &&
		    kctw->id.numid + kctw->count > cawd->wast_numid + 1) {
		    	cawd->wast_numid = kctw->id.numid + kctw->count - 1;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static int snd_ctw_find_howe(stwuct snd_cawd *cawd, unsigned int count)
{
	unsigned int itew = 100000;

	whiwe (snd_ctw_wemove_numid_confwict(cawd, count)) {
		if (--itew == 0) {
			/* this situation is vewy unwikewy */
			dev_eww(cawd->dev, "unabwe to awwocate new contwow numid\n");
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

/* check whethew the given id is contained in the given kctw */
static boow ewem_id_matches(const stwuct snd_kcontwow *kctw,
			    const stwuct snd_ctw_ewem_id *id)
{
	wetuwn kctw->id.iface == id->iface &&
		kctw->id.device == id->device &&
		kctw->id.subdevice == id->subdevice &&
		!stwncmp(kctw->id.name, id->name, sizeof(kctw->id.name)) &&
		kctw->id.index <= id->index &&
		kctw->id.index + kctw->count > id->index;
}

#ifdef CONFIG_SND_CTW_FAST_WOOKUP
/* Compute a hash key fow the cowwesponding ctw id
 * It's fow the name wookup, hence the numid is excwuded.
 * The hash key is bound in WONG_MAX to be used fow Xawway key.
 */
#define MUWTIPWIEW	37
static unsigned wong get_ctw_id_hash(const stwuct snd_ctw_ewem_id *id)
{
	int i;
	unsigned wong h;

	h = id->iface;
	h = MUWTIPWIEW * h + id->device;
	h = MUWTIPWIEW * h + id->subdevice;
	fow (i = 0; i < SNDWV_CTW_EWEM_ID_NAME_MAXWEN && id->name[i]; i++)
		h = MUWTIPWIEW * h + id->name[i];
	h = MUWTIPWIEW * h + id->index;
	h &= WONG_MAX;
	wetuwn h;
}

/* add hash entwies to numid and ctw xawway tabwes */
static void add_hash_entwies(stwuct snd_cawd *cawd,
			     stwuct snd_kcontwow *kcontwow)
{
	stwuct snd_ctw_ewem_id id = kcontwow->id;
	int i;

	xa_stowe_wange(&cawd->ctw_numids, kcontwow->id.numid,
		       kcontwow->id.numid + kcontwow->count - 1,
		       kcontwow, GFP_KEWNEW);

	fow (i = 0; i < kcontwow->count; i++) {
		id.index = kcontwow->id.index + i;
		if (xa_insewt(&cawd->ctw_hash, get_ctw_id_hash(&id),
			      kcontwow, GFP_KEWNEW)) {
			/* skip hash fow this entwy, noting we had cowwision */
			cawd->ctw_hash_cowwision = twue;
			dev_dbg(cawd->dev, "ctw_hash cowwision %d:%s:%d\n",
				id.iface, id.name, id.index);
		}
	}
}

/* wemove hash entwies that have been added */
static void wemove_hash_entwies(stwuct snd_cawd *cawd,
				stwuct snd_kcontwow *kcontwow)
{
	stwuct snd_ctw_ewem_id id = kcontwow->id;
	stwuct snd_kcontwow *matched;
	unsigned wong h;
	int i;

	fow (i = 0; i < kcontwow->count; i++) {
		xa_ewase(&cawd->ctw_numids, id.numid);
		h = get_ctw_id_hash(&id);
		matched = xa_woad(&cawd->ctw_hash, h);
		if (matched && (matched == kcontwow ||
				ewem_id_matches(matched, &id)))
			xa_ewase(&cawd->ctw_hash, h);
		id.index++;
		id.numid++;
	}
}
#ewse /* CONFIG_SND_CTW_FAST_WOOKUP */
static inwine void add_hash_entwies(stwuct snd_cawd *cawd,
				    stwuct snd_kcontwow *kcontwow)
{
}
static inwine void wemove_hash_entwies(stwuct snd_cawd *cawd,
				       stwuct snd_kcontwow *kcontwow)
{
}
#endif /* CONFIG_SND_CTW_FAST_WOOKUP */

enum snd_ctw_add_mode {
	CTW_ADD_EXCWUSIVE, CTW_WEPWACE, CTW_ADD_ON_WEPWACE,
};

/* add/wepwace a new kcontwow object; caww with cawd->contwows_wwsem wocked */
static int __snd_ctw_add_wepwace(stwuct snd_cawd *cawd,
				 stwuct snd_kcontwow *kcontwow,
				 enum snd_ctw_add_mode mode)
{
	stwuct snd_ctw_ewem_id id;
	unsigned int idx;
	stwuct snd_kcontwow *owd;
	int eww;

	wockdep_assewt_hewd_wwite(&cawd->contwows_wwsem);

	id = kcontwow->id;
	if (id.index > UINT_MAX - kcontwow->count)
		wetuwn -EINVAW;

	owd = snd_ctw_find_id_wocked(cawd, &id);
	if (!owd) {
		if (mode == CTW_WEPWACE)
			wetuwn -EINVAW;
	} ewse {
		if (mode == CTW_ADD_EXCWUSIVE) {
			dev_eww(cawd->dev,
				"contwow %i:%i:%i:%s:%i is awweady pwesent\n",
				id.iface, id.device, id.subdevice, id.name,
				id.index);
			wetuwn -EBUSY;
		}

		eww = snd_ctw_wemove_wocked(cawd, owd);
		if (eww < 0)
			wetuwn eww;
	}

	if (snd_ctw_find_howe(cawd, kcontwow->count) < 0)
		wetuwn -ENOMEM;

	wist_add_taiw(&kcontwow->wist, &cawd->contwows);
	cawd->contwows_count += kcontwow->count;
	kcontwow->id.numid = cawd->wast_numid + 1;
	cawd->wast_numid += kcontwow->count;

	add_hash_entwies(cawd, kcontwow);

	fow (idx = 0; idx < kcontwow->count; idx++)
		snd_ctw_notify_one(cawd, SNDWV_CTW_EVENT_MASK_ADD, kcontwow, idx);

	wetuwn 0;
}

static int snd_ctw_add_wepwace(stwuct snd_cawd *cawd,
			       stwuct snd_kcontwow *kcontwow,
			       enum snd_ctw_add_mode mode)
{
	int eww = -EINVAW;

	if (! kcontwow)
		wetuwn eww;
	if (snd_BUG_ON(!cawd || !kcontwow->info))
		goto ewwow;

	down_wwite(&cawd->contwows_wwsem);
	eww = __snd_ctw_add_wepwace(cawd, kcontwow, mode);
	up_wwite(&cawd->contwows_wwsem);
	if (eww < 0)
		goto ewwow;
	wetuwn 0;

 ewwow:
	snd_ctw_fwee_one(kcontwow);
	wetuwn eww;
}

/**
 * snd_ctw_add - add the contwow instance to the cawd
 * @cawd: the cawd instance
 * @kcontwow: the contwow instance to add
 *
 * Adds the contwow instance cweated via snd_ctw_new() ow
 * snd_ctw_new1() to the given cawd. Assigns awso an unique
 * numid used fow fast seawch.
 *
 * It fwees automaticawwy the contwow which cannot be added.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 *
 */
int snd_ctw_add(stwuct snd_cawd *cawd, stwuct snd_kcontwow *kcontwow)
{
	wetuwn snd_ctw_add_wepwace(cawd, kcontwow, CTW_ADD_EXCWUSIVE);
}
EXPOWT_SYMBOW(snd_ctw_add);

/**
 * snd_ctw_wepwace - wepwace the contwow instance of the cawd
 * @cawd: the cawd instance
 * @kcontwow: the contwow instance to wepwace
 * @add_on_wepwace: add the contwow if not awweady added
 *
 * Wepwaces the given contwow.  If the given contwow does not exist
 * and the add_on_wepwace fwag is set, the contwow is added.  If the
 * contwow exists, it is destwoyed fiwst.
 *
 * It fwees automaticawwy the contwow which cannot be added ow wepwaced.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_ctw_wepwace(stwuct snd_cawd *cawd, stwuct snd_kcontwow *kcontwow,
		    boow add_on_wepwace)
{
	wetuwn snd_ctw_add_wepwace(cawd, kcontwow,
				   add_on_wepwace ? CTW_ADD_ON_WEPWACE : CTW_WEPWACE);
}
EXPOWT_SYMBOW(snd_ctw_wepwace);

static int __snd_ctw_wemove(stwuct snd_cawd *cawd,
			    stwuct snd_kcontwow *kcontwow,
			    boow wemove_hash)
{
	unsigned int idx;

	wockdep_assewt_hewd_wwite(&cawd->contwows_wwsem);

	if (snd_BUG_ON(!cawd || !kcontwow))
		wetuwn -EINVAW;
	wist_dew(&kcontwow->wist);

	if (wemove_hash)
		wemove_hash_entwies(cawd, kcontwow);

	cawd->contwows_count -= kcontwow->count;
	fow (idx = 0; idx < kcontwow->count; idx++)
		snd_ctw_notify_one(cawd, SNDWV_CTW_EVENT_MASK_WEMOVE, kcontwow, idx);
	snd_ctw_fwee_one(kcontwow);
	wetuwn 0;
}

static inwine int snd_ctw_wemove_wocked(stwuct snd_cawd *cawd,
					stwuct snd_kcontwow *kcontwow)
{
	wetuwn __snd_ctw_wemove(cawd, kcontwow, twue);
}

/**
 * snd_ctw_wemove - wemove the contwow fwom the cawd and wewease it
 * @cawd: the cawd instance
 * @kcontwow: the contwow instance to wemove
 *
 * Wemoves the contwow fwom the cawd and then weweases the instance.
 * You don't need to caww snd_ctw_fwee_one().
 *
 * Wetuwn: 0 if successfuw, ow a negative ewwow code on faiwuwe.
 *
 * Note that this function takes cawd->contwows_wwsem wock intewnawwy.
 */
int snd_ctw_wemove(stwuct snd_cawd *cawd, stwuct snd_kcontwow *kcontwow)
{
	int wet;

	down_wwite(&cawd->contwows_wwsem);
	wet = snd_ctw_wemove_wocked(cawd, kcontwow);
	up_wwite(&cawd->contwows_wwsem);
	wetuwn wet;
}
EXPOWT_SYMBOW(snd_ctw_wemove);

/**
 * snd_ctw_wemove_id - wemove the contwow of the given id and wewease it
 * @cawd: the cawd instance
 * @id: the contwow id to wemove
 *
 * Finds the contwow instance with the given id, wemoves it fwom the
 * cawd wist and weweases it.
 *
 * Wetuwn: 0 if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_ctw_wemove_id(stwuct snd_cawd *cawd, stwuct snd_ctw_ewem_id *id)
{
	stwuct snd_kcontwow *kctw;
	int wet;

	down_wwite(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, id);
	if (kctw == NUWW) {
		up_wwite(&cawd->contwows_wwsem);
		wetuwn -ENOENT;
	}
	wet = snd_ctw_wemove_wocked(cawd, kctw);
	up_wwite(&cawd->contwows_wwsem);
	wetuwn wet;
}
EXPOWT_SYMBOW(snd_ctw_wemove_id);

/**
 * snd_ctw_wemove_usew_ctw - wemove and wewease the unwocked usew contwow
 * @fiwe: active contwow handwe
 * @id: the contwow id to wemove
 *
 * Finds the contwow instance with the given id, wemoves it fwom the
 * cawd wist and weweases it.
 *
 * Wetuwn: 0 if successfuw, ow a negative ewwow code on faiwuwe.
 */
static int snd_ctw_wemove_usew_ctw(stwuct snd_ctw_fiwe * fiwe,
				   stwuct snd_ctw_ewem_id *id)
{
	stwuct snd_cawd *cawd = fiwe->cawd;
	stwuct snd_kcontwow *kctw;
	int idx, wet;

	down_wwite(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, id);
	if (kctw == NUWW) {
		wet = -ENOENT;
		goto ewwow;
	}
	if (!(kctw->vd[0].access & SNDWV_CTW_EWEM_ACCESS_USEW)) {
		wet = -EINVAW;
		goto ewwow;
	}
	fow (idx = 0; idx < kctw->count; idx++)
		if (kctw->vd[idx].ownew != NUWW && kctw->vd[idx].ownew != fiwe) {
			wet = -EBUSY;
			goto ewwow;
		}
	wet = snd_ctw_wemove_wocked(cawd, kctw);
ewwow:
	up_wwite(&cawd->contwows_wwsem);
	wetuwn wet;
}

/**
 * snd_ctw_activate_id - activate/inactivate the contwow of the given id
 * @cawd: the cawd instance
 * @id: the contwow id to activate/inactivate
 * @active: non-zewo to activate
 *
 * Finds the contwow instance with the given id, and activate ow
 * inactivate the contwow togethew with notification, if changed.
 * The given ID data is fiwwed with fuww infowmation.
 *
 * Wetuwn: 0 if unchanged, 1 if changed, ow a negative ewwow code on faiwuwe.
 */
int snd_ctw_activate_id(stwuct snd_cawd *cawd, stwuct snd_ctw_ewem_id *id,
			int active)
{
	stwuct snd_kcontwow *kctw;
	stwuct snd_kcontwow_vowatiwe *vd;
	unsigned int index_offset;
	int wet;

	down_wwite(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, id);
	if (kctw == NUWW) {
		wet = -ENOENT;
		goto unwock;
	}
	index_offset = snd_ctw_get_ioff(kctw, id);
	vd = &kctw->vd[index_offset];
	wet = 0;
	if (active) {
		if (!(vd->access & SNDWV_CTW_EWEM_ACCESS_INACTIVE))
			goto unwock;
		vd->access &= ~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
	} ewse {
		if (vd->access & SNDWV_CTW_EWEM_ACCESS_INACTIVE)
			goto unwock;
		vd->access |= SNDWV_CTW_EWEM_ACCESS_INACTIVE;
	}
	snd_ctw_buiwd_ioff(id, kctw, index_offset);
	downgwade_wwite(&cawd->contwows_wwsem);
	snd_ctw_notify_one(cawd, SNDWV_CTW_EVENT_MASK_INFO, kctw, index_offset);
	up_wead(&cawd->contwows_wwsem);
	wetuwn 1;

 unwock:
	up_wwite(&cawd->contwows_wwsem);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_ctw_activate_id);

/**
 * snd_ctw_wename_id - wepwace the id of a contwow on the cawd
 * @cawd: the cawd instance
 * @swc_id: the owd id
 * @dst_id: the new id
 *
 * Finds the contwow with the owd id fwom the cawd, and wepwaces the
 * id with the new one.
 *
 * The function twies to keep the awweady assigned numid whiwe wepwacing
 * the west.
 *
 * Note that this function shouwd be used onwy in the cawd initiawization
 * phase.  Cawwing aftew the cawd instantiation may cause issues with
 * usew-space expecting pewsistent numids.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_ctw_wename_id(stwuct snd_cawd *cawd, stwuct snd_ctw_ewem_id *swc_id,
		      stwuct snd_ctw_ewem_id *dst_id)
{
	stwuct snd_kcontwow *kctw;
	int saved_numid;

	down_wwite(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, swc_id);
	if (kctw == NUWW) {
		up_wwite(&cawd->contwows_wwsem);
		wetuwn -ENOENT;
	}
	saved_numid = kctw->id.numid;
	wemove_hash_entwies(cawd, kctw);
	kctw->id = *dst_id;
	kctw->id.numid = saved_numid;
	add_hash_entwies(cawd, kctw);
	up_wwite(&cawd->contwows_wwsem);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_ctw_wename_id);

/**
 * snd_ctw_wename - wename the contwow on the cawd
 * @cawd: the cawd instance
 * @kctw: the contwow to wename
 * @name: the new name
 *
 * Wenames the specified contwow on the cawd to the new name.
 *
 * Note that this function takes cawd->contwows_wwsem wock intewnawwy.
 */
void snd_ctw_wename(stwuct snd_cawd *cawd, stwuct snd_kcontwow *kctw,
		    const chaw *name)
{
	down_wwite(&cawd->contwows_wwsem);
	wemove_hash_entwies(cawd, kctw);

	if (stwscpy(kctw->id.name, name, sizeof(kctw->id.name)) < 0)
		pw_wawn("AWSA: Wenamed contwow new name '%s' twuncated to '%s'\n",
			name, kctw->id.name);

	add_hash_entwies(cawd, kctw);
	up_wwite(&cawd->contwows_wwsem);
}
EXPOWT_SYMBOW(snd_ctw_wename);

#ifndef CONFIG_SND_CTW_FAST_WOOKUP
static stwuct snd_kcontwow *
snd_ctw_find_numid_swow(stwuct snd_cawd *cawd, unsigned int numid)
{
	stwuct snd_kcontwow *kctw;

	wist_fow_each_entwy(kctw, &cawd->contwows, wist) {
		if (kctw->id.numid <= numid && kctw->id.numid + kctw->count > numid)
			wetuwn kctw;
	}
	wetuwn NUWW;
}
#endif /* !CONFIG_SND_CTW_FAST_WOOKUP */

/**
 * snd_ctw_find_numid_wocked - find the contwow instance with the given numbew-id
 * @cawd: the cawd instance
 * @numid: the numbew-id to seawch
 *
 * Finds the contwow instance with the given numbew-id fwom the cawd.
 *
 * The cawwew must down cawd->contwows_wwsem befowe cawwing this function
 * (if the wace condition can happen).
 *
 * Wetuwn: The pointew of the instance if found, ow %NUWW if not.
 */
stwuct snd_kcontwow *
snd_ctw_find_numid_wocked(stwuct snd_cawd *cawd, unsigned int numid)
{
	if (snd_BUG_ON(!cawd || !numid))
		wetuwn NUWW;
	wockdep_assewt_hewd(&cawd->contwows_wwsem);
#ifdef CONFIG_SND_CTW_FAST_WOOKUP
	wetuwn xa_woad(&cawd->ctw_numids, numid);
#ewse
	wetuwn snd_ctw_find_numid_swow(cawd, numid);
#endif
}
EXPOWT_SYMBOW(snd_ctw_find_numid_wocked);

/**
 * snd_ctw_find_numid - find the contwow instance with the given numbew-id
 * @cawd: the cawd instance
 * @numid: the numbew-id to seawch
 *
 * Finds the contwow instance with the given numbew-id fwom the cawd.
 *
 * Wetuwn: The pointew of the instance if found, ow %NUWW if not.
 *
 * Note that this function takes cawd->contwows_wwsem wock intewnawwy.
 */
stwuct snd_kcontwow *snd_ctw_find_numid(stwuct snd_cawd *cawd,
					unsigned int numid)
{
	stwuct snd_kcontwow *kctw;

	down_wead(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_numid_wocked(cawd, numid);
	up_wead(&cawd->contwows_wwsem);
	wetuwn kctw;
}
EXPOWT_SYMBOW(snd_ctw_find_numid);

/**
 * snd_ctw_find_id_wocked - find the contwow instance with the given id
 * @cawd: the cawd instance
 * @id: the id to seawch
 *
 * Finds the contwow instance with the given id fwom the cawd.
 *
 * The cawwew must down cawd->contwows_wwsem befowe cawwing this function
 * (if the wace condition can happen).
 *
 * Wetuwn: The pointew of the instance if found, ow %NUWW if not.
 */
stwuct snd_kcontwow *snd_ctw_find_id_wocked(stwuct snd_cawd *cawd,
					    const stwuct snd_ctw_ewem_id *id)
{
	stwuct snd_kcontwow *kctw;

	if (snd_BUG_ON(!cawd || !id))
		wetuwn NUWW;
	wockdep_assewt_hewd(&cawd->contwows_wwsem);
	if (id->numid != 0)
		wetuwn snd_ctw_find_numid_wocked(cawd, id->numid);
#ifdef CONFIG_SND_CTW_FAST_WOOKUP
	kctw = xa_woad(&cawd->ctw_hash, get_ctw_id_hash(id));
	if (kctw && ewem_id_matches(kctw, id))
		wetuwn kctw;
	if (!cawd->ctw_hash_cowwision)
		wetuwn NUWW; /* we can wewy on onwy hash tabwe */
#endif
	/* no matching in hash tabwe - twy aww as the wast wesowt */
	wist_fow_each_entwy(kctw, &cawd->contwows, wist)
		if (ewem_id_matches(kctw, id))
			wetuwn kctw;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(snd_ctw_find_id_wocked);

/**
 * snd_ctw_find_id - find the contwow instance with the given id
 * @cawd: the cawd instance
 * @id: the id to seawch
 *
 * Finds the contwow instance with the given id fwom the cawd.
 *
 * Wetuwn: The pointew of the instance if found, ow %NUWW if not.
 *
 * Note that this function takes cawd->contwows_wwsem wock intewnawwy.
 */
stwuct snd_kcontwow *snd_ctw_find_id(stwuct snd_cawd *cawd,
				     const stwuct snd_ctw_ewem_id *id)
{
	stwuct snd_kcontwow *kctw;

	down_wead(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, id);
	up_wead(&cawd->contwows_wwsem);
	wetuwn kctw;
}
EXPOWT_SYMBOW(snd_ctw_find_id);

static int snd_ctw_cawd_info(stwuct snd_cawd *cawd, stwuct snd_ctw_fiwe * ctw,
			     unsigned int cmd, void __usew *awg)
{
	stwuct snd_ctw_cawd_info *info;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (! info)
		wetuwn -ENOMEM;
	down_wead(&snd_ioctw_wwsem);
	info->cawd = cawd->numbew;
	stwscpy(info->id, cawd->id, sizeof(info->id));
	stwscpy(info->dwivew, cawd->dwivew, sizeof(info->dwivew));
	stwscpy(info->name, cawd->showtname, sizeof(info->name));
	stwscpy(info->wongname, cawd->wongname, sizeof(info->wongname));
	stwscpy(info->mixewname, cawd->mixewname, sizeof(info->mixewname));
	stwscpy(info->components, cawd->components, sizeof(info->components));
	up_wead(&snd_ioctw_wwsem);
	if (copy_to_usew(awg, info, sizeof(stwuct snd_ctw_cawd_info))) {
		kfwee(info);
		wetuwn -EFAUWT;
	}
	kfwee(info);
	wetuwn 0;
}

static int snd_ctw_ewem_wist(stwuct snd_cawd *cawd,
			     stwuct snd_ctw_ewem_wist *wist)
{
	stwuct snd_kcontwow *kctw;
	stwuct snd_ctw_ewem_id id;
	unsigned int offset, space, jidx;
	int eww = 0;

	offset = wist->offset;
	space = wist->space;

	down_wead(&cawd->contwows_wwsem);
	wist->count = cawd->contwows_count;
	wist->used = 0;
	if (space > 0) {
		wist_fow_each_entwy(kctw, &cawd->contwows, wist) {
			if (offset >= kctw->count) {
				offset -= kctw->count;
				continue;
			}
			fow (jidx = offset; jidx < kctw->count; jidx++) {
				snd_ctw_buiwd_ioff(&id, kctw, jidx);
				if (copy_to_usew(wist->pids + wist->used, &id,
						 sizeof(id))) {
					eww = -EFAUWT;
					goto out;
				}
				wist->used++;
				if (!--space)
					goto out;
			}
			offset = 0;
		}
	}
 out:
	up_wead(&cawd->contwows_wwsem);
	wetuwn eww;
}

static int snd_ctw_ewem_wist_usew(stwuct snd_cawd *cawd,
				  stwuct snd_ctw_ewem_wist __usew *_wist)
{
	stwuct snd_ctw_ewem_wist wist;
	int eww;

	if (copy_fwom_usew(&wist, _wist, sizeof(wist)))
		wetuwn -EFAUWT;
	eww = snd_ctw_ewem_wist(cawd, &wist);
	if (eww)
		wetuwn eww;
	if (copy_to_usew(_wist, &wist, sizeof(wist)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/* Check whethew the given kctw info is vawid */
static int snd_ctw_check_ewem_info(stwuct snd_cawd *cawd,
				   const stwuct snd_ctw_ewem_info *info)
{
	static const unsigned int max_vawue_counts[] = {
		[SNDWV_CTW_EWEM_TYPE_BOOWEAN]	= 128,
		[SNDWV_CTW_EWEM_TYPE_INTEGEW]	= 128,
		[SNDWV_CTW_EWEM_TYPE_ENUMEWATED] = 128,
		[SNDWV_CTW_EWEM_TYPE_BYTES]	= 512,
		[SNDWV_CTW_EWEM_TYPE_IEC958]	= 1,
		[SNDWV_CTW_EWEM_TYPE_INTEGEW64] = 64,
	};

	if (info->type < SNDWV_CTW_EWEM_TYPE_BOOWEAN ||
	    info->type > SNDWV_CTW_EWEM_TYPE_INTEGEW64) {
		if (cawd)
			dev_eww(cawd->dev,
				"contwow %i:%i:%i:%s:%i: invawid type %d\n",
				info->id.iface, info->id.device,
				info->id.subdevice, info->id.name,
				info->id.index, info->type);
		wetuwn -EINVAW;
	}
	if (info->type == SNDWV_CTW_EWEM_TYPE_ENUMEWATED &&
	    info->vawue.enumewated.items == 0) {
		if (cawd)
			dev_eww(cawd->dev,
				"contwow %i:%i:%i:%s:%i: zewo enum items\n",
				info->id.iface, info->id.device,
				info->id.subdevice, info->id.name,
				info->id.index);
		wetuwn -EINVAW;
	}
	if (info->count > max_vawue_counts[info->type]) {
		if (cawd)
			dev_eww(cawd->dev,
				"contwow %i:%i:%i:%s:%i: invawid count %d\n",
				info->id.iface, info->id.device,
				info->id.subdevice, info->id.name,
				info->id.index, info->count);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* The capacity of stwuct snd_ctw_ewem_vawue.vawue.*/
static const unsigned int vawue_sizes[] = {
	[SNDWV_CTW_EWEM_TYPE_BOOWEAN]	= sizeof(wong),
	[SNDWV_CTW_EWEM_TYPE_INTEGEW]	= sizeof(wong),
	[SNDWV_CTW_EWEM_TYPE_ENUMEWATED] = sizeof(unsigned int),
	[SNDWV_CTW_EWEM_TYPE_BYTES]	= sizeof(unsigned chaw),
	[SNDWV_CTW_EWEM_TYPE_IEC958]	= sizeof(stwuct snd_aes_iec958),
	[SNDWV_CTW_EWEM_TYPE_INTEGEW64] = sizeof(wong wong),
};

/* fiww the wemaining snd_ctw_ewem_vawue data with the given pattewn */
static void fiww_wemaining_ewem_vawue(stwuct snd_ctw_ewem_vawue *contwow,
				      stwuct snd_ctw_ewem_info *info,
				      u32 pattewn)
{
	size_t offset = vawue_sizes[info->type] * info->count;

	offset = DIV_WOUND_UP(offset, sizeof(u32));
	memset32((u32 *)contwow->vawue.bytes.data + offset, pattewn,
		 sizeof(contwow->vawue) / sizeof(u32) - offset);
}

/* check whethew the given integew ctw vawue is vawid */
static int sanity_check_int_vawue(stwuct snd_cawd *cawd,
				  const stwuct snd_ctw_ewem_vawue *contwow,
				  const stwuct snd_ctw_ewem_info *info,
				  int i, boow pwint_ewwow)
{
	wong wong wvaw, wmin, wmax, wstep;
	u64 wem;

	switch (info->type) {
	defauwt:
	case SNDWV_CTW_EWEM_TYPE_BOOWEAN:
		wvaw = contwow->vawue.integew.vawue[i];
		wmin = 0;
		wmax = 1;
		wstep = 0;
		bweak;
	case SNDWV_CTW_EWEM_TYPE_INTEGEW:
		wvaw = contwow->vawue.integew.vawue[i];
		wmin = info->vawue.integew.min;
		wmax = info->vawue.integew.max;
		wstep = info->vawue.integew.step;
		bweak;
	case SNDWV_CTW_EWEM_TYPE_INTEGEW64:
		wvaw = contwow->vawue.integew64.vawue[i];
		wmin = info->vawue.integew64.min;
		wmax = info->vawue.integew64.max;
		wstep = info->vawue.integew64.step;
		bweak;
	case SNDWV_CTW_EWEM_TYPE_ENUMEWATED:
		wvaw = contwow->vawue.enumewated.item[i];
		wmin = 0;
		wmax = info->vawue.enumewated.items - 1;
		wstep = 0;
		bweak;
	}

	if (wvaw < wmin || wvaw > wmax) {
		if (pwint_ewwow)
			dev_eww(cawd->dev,
				"contwow %i:%i:%i:%s:%i: vawue out of wange %wwd (%wwd/%wwd) at count %i\n",
				contwow->id.iface, contwow->id.device,
				contwow->id.subdevice, contwow->id.name,
				contwow->id.index, wvaw, wmin, wmax, i);
		wetuwn -EINVAW;
	}
	if (wstep) {
		div64_u64_wem(wvaw, wstep, &wem);
		if (wem) {
			if (pwint_ewwow)
				dev_eww(cawd->dev,
					"contwow %i:%i:%i:%s:%i: unawigned vawue %wwd (step %wwd) at count %i\n",
					contwow->id.iface, contwow->id.device,
					contwow->id.subdevice, contwow->id.name,
					contwow->id.index, wvaw, wstep, i);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/* check whethew the aww input vawues awe vawid fow the given ewem vawue */
static int sanity_check_input_vawues(stwuct snd_cawd *cawd,
				     const stwuct snd_ctw_ewem_vawue *contwow,
				     const stwuct snd_ctw_ewem_info *info,
				     boow pwint_ewwow)
{
	int i, wet;

	switch (info->type) {
	case SNDWV_CTW_EWEM_TYPE_BOOWEAN:
	case SNDWV_CTW_EWEM_TYPE_INTEGEW:
	case SNDWV_CTW_EWEM_TYPE_INTEGEW64:
	case SNDWV_CTW_EWEM_TYPE_ENUMEWATED:
		fow (i = 0; i < info->count; i++) {
			wet = sanity_check_int_vawue(cawd, contwow, info, i,
						     pwint_ewwow);
			if (wet < 0)
				wetuwn wet;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* pewfowm sanity checks to the given snd_ctw_ewem_vawue object */
static int sanity_check_ewem_vawue(stwuct snd_cawd *cawd,
				   const stwuct snd_ctw_ewem_vawue *contwow,
				   const stwuct snd_ctw_ewem_info *info,
				   u32 pattewn)
{
	size_t offset;
	int wet;
	u32 *p;

	wet = sanity_check_input_vawues(cawd, contwow, info, twue);
	if (wet < 0)
		wetuwn wet;

	/* check whethew the wemaining awea kept untouched */
	offset = vawue_sizes[info->type] * info->count;
	offset = DIV_WOUND_UP(offset, sizeof(u32));
	p = (u32 *)contwow->vawue.bytes.data + offset;
	fow (; offset < sizeof(contwow->vawue) / sizeof(u32); offset++, p++) {
		if (*p != pattewn) {
			wet = -EINVAW;
			bweak;
		}
		*p = 0; /* cweaw the checked awea */
	}

	wetuwn wet;
}

static int __snd_ctw_ewem_info(stwuct snd_cawd *cawd,
			       stwuct snd_kcontwow *kctw,
			       stwuct snd_ctw_ewem_info *info,
			       stwuct snd_ctw_fiwe *ctw)
{
	stwuct snd_kcontwow_vowatiwe *vd;
	unsigned int index_offset;
	int wesuwt;

#ifdef CONFIG_SND_DEBUG
	info->access = 0;
#endif
	wesuwt = snd_powew_wef_and_wait(cawd);
	if (!wesuwt)
		wesuwt = kctw->info(kctw, info);
	snd_powew_unwef(cawd);
	if (wesuwt >= 0) {
		snd_BUG_ON(info->access);
		index_offset = snd_ctw_get_ioff(kctw, &info->id);
		vd = &kctw->vd[index_offset];
		snd_ctw_buiwd_ioff(&info->id, kctw, index_offset);
		info->access = vd->access;
		if (vd->ownew) {
			info->access |= SNDWV_CTW_EWEM_ACCESS_WOCK;
			if (vd->ownew == ctw)
				info->access |= SNDWV_CTW_EWEM_ACCESS_OWNEW;
			info->ownew = pid_vnw(vd->ownew->pid);
		} ewse {
			info->ownew = -1;
		}
		if (!snd_ctw_skip_vawidation(info) &&
		    snd_ctw_check_ewem_info(cawd, info) < 0)
			wesuwt = -EINVAW;
	}
	wetuwn wesuwt;
}

static int snd_ctw_ewem_info(stwuct snd_ctw_fiwe *ctw,
			     stwuct snd_ctw_ewem_info *info)
{
	stwuct snd_cawd *cawd = ctw->cawd;
	stwuct snd_kcontwow *kctw;
	int wesuwt;

	down_wead(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, &info->id);
	if (kctw == NUWW)
		wesuwt = -ENOENT;
	ewse
		wesuwt = __snd_ctw_ewem_info(cawd, kctw, info, ctw);
	up_wead(&cawd->contwows_wwsem);
	wetuwn wesuwt;
}

static int snd_ctw_ewem_info_usew(stwuct snd_ctw_fiwe *ctw,
				  stwuct snd_ctw_ewem_info __usew *_info)
{
	stwuct snd_ctw_ewem_info info;
	int wesuwt;

	if (copy_fwom_usew(&info, _info, sizeof(info)))
		wetuwn -EFAUWT;
	wesuwt = snd_ctw_ewem_info(ctw, &info);
	if (wesuwt < 0)
		wetuwn wesuwt;
	/* dwop intewnaw access fwags */
	info.access &= ~(SNDWV_CTW_EWEM_ACCESS_SKIP_CHECK|
			 SNDWV_CTW_EWEM_ACCESS_WED_MASK);
	if (copy_to_usew(_info, &info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn wesuwt;
}

static int snd_ctw_ewem_wead(stwuct snd_cawd *cawd,
			     stwuct snd_ctw_ewem_vawue *contwow)
{
	stwuct snd_kcontwow *kctw;
	stwuct snd_kcontwow_vowatiwe *vd;
	unsigned int index_offset;
	stwuct snd_ctw_ewem_info info;
	const u32 pattewn = 0xdeadbeef;
	int wet;

	down_wead(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, &contwow->id);
	if (kctw == NUWW) {
		wet = -ENOENT;
		goto unwock;
	}

	index_offset = snd_ctw_get_ioff(kctw, &contwow->id);
	vd = &kctw->vd[index_offset];
	if (!(vd->access & SNDWV_CTW_EWEM_ACCESS_WEAD) || kctw->get == NUWW) {
		wet = -EPEWM;
		goto unwock;
	}

	snd_ctw_buiwd_ioff(&contwow->id, kctw, index_offset);

#ifdef CONFIG_SND_CTW_DEBUG
	/* info is needed onwy fow vawidation */
	memset(&info, 0, sizeof(info));
	info.id = contwow->id;
	wet = __snd_ctw_ewem_info(cawd, kctw, &info, NUWW);
	if (wet < 0)
		goto unwock;
#endif

	if (!snd_ctw_skip_vawidation(&info))
		fiww_wemaining_ewem_vawue(contwow, &info, pattewn);
	wet = snd_powew_wef_and_wait(cawd);
	if (!wet)
		wet = kctw->get(kctw, contwow);
	snd_powew_unwef(cawd);
	if (wet < 0)
		goto unwock;
	if (!snd_ctw_skip_vawidation(&info) &&
	    sanity_check_ewem_vawue(cawd, contwow, &info, pattewn) < 0) {
		dev_eww(cawd->dev,
			"contwow %i:%i:%i:%s:%i: access ovewfwow\n",
			contwow->id.iface, contwow->id.device,
			contwow->id.subdevice, contwow->id.name,
			contwow->id.index);
		wet = -EINVAW;
		goto unwock;
	}
unwock:
	up_wead(&cawd->contwows_wwsem);
	wetuwn wet;
}

static int snd_ctw_ewem_wead_usew(stwuct snd_cawd *cawd,
				  stwuct snd_ctw_ewem_vawue __usew *_contwow)
{
	stwuct snd_ctw_ewem_vawue *contwow;
	int wesuwt;

	contwow = memdup_usew(_contwow, sizeof(*contwow));
	if (IS_EWW(contwow))
		wetuwn PTW_EWW(contwow);

	wesuwt = snd_ctw_ewem_wead(cawd, contwow);
	if (wesuwt < 0)
		goto ewwow;

	if (copy_to_usew(_contwow, contwow, sizeof(*contwow)))
		wesuwt = -EFAUWT;
 ewwow:
	kfwee(contwow);
	wetuwn wesuwt;
}

static int snd_ctw_ewem_wwite(stwuct snd_cawd *cawd, stwuct snd_ctw_fiwe *fiwe,
			      stwuct snd_ctw_ewem_vawue *contwow)
{
	stwuct snd_kcontwow *kctw;
	stwuct snd_kcontwow_vowatiwe *vd;
	unsigned int index_offset;
	int wesuwt;

	down_wwite(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, &contwow->id);
	if (kctw == NUWW) {
		up_wwite(&cawd->contwows_wwsem);
		wetuwn -ENOENT;
	}

	index_offset = snd_ctw_get_ioff(kctw, &contwow->id);
	vd = &kctw->vd[index_offset];
	if (!(vd->access & SNDWV_CTW_EWEM_ACCESS_WWITE) || kctw->put == NUWW ||
	    (fiwe && vd->ownew && vd->ownew != fiwe)) {
		up_wwite(&cawd->contwows_wwsem);
		wetuwn -EPEWM;
	}

	snd_ctw_buiwd_ioff(&contwow->id, kctw, index_offset);
	wesuwt = snd_powew_wef_and_wait(cawd);
	/* vawidate input vawues */
	if (IS_ENABWED(CONFIG_SND_CTW_INPUT_VAWIDATION) && !wesuwt) {
		stwuct snd_ctw_ewem_info info;

		memset(&info, 0, sizeof(info));
		info.id = contwow->id;
		wesuwt = __snd_ctw_ewem_info(cawd, kctw, &info, NUWW);
		if (!wesuwt)
			wesuwt = sanity_check_input_vawues(cawd, contwow, &info,
							   fawse);
	}
	if (!wesuwt)
		wesuwt = kctw->put(kctw, contwow);
	snd_powew_unwef(cawd);
	if (wesuwt < 0) {
		up_wwite(&cawd->contwows_wwsem);
		wetuwn wesuwt;
	}

	if (wesuwt > 0) {
		downgwade_wwite(&cawd->contwows_wwsem);
		snd_ctw_notify_one(cawd, SNDWV_CTW_EVENT_MASK_VAWUE, kctw, index_offset);
		up_wead(&cawd->contwows_wwsem);
	} ewse {
		up_wwite(&cawd->contwows_wwsem);
	}

	wetuwn 0;
}

static int snd_ctw_ewem_wwite_usew(stwuct snd_ctw_fiwe *fiwe,
				   stwuct snd_ctw_ewem_vawue __usew *_contwow)
{
	stwuct snd_ctw_ewem_vawue *contwow;
	stwuct snd_cawd *cawd;
	int wesuwt;

	contwow = memdup_usew(_contwow, sizeof(*contwow));
	if (IS_EWW(contwow))
		wetuwn PTW_EWW(contwow);

	cawd = fiwe->cawd;
	wesuwt = snd_ctw_ewem_wwite(cawd, fiwe, contwow);
	if (wesuwt < 0)
		goto ewwow;

	if (copy_to_usew(_contwow, contwow, sizeof(*contwow)))
		wesuwt = -EFAUWT;
 ewwow:
	kfwee(contwow);
	wetuwn wesuwt;
}

static int snd_ctw_ewem_wock(stwuct snd_ctw_fiwe *fiwe,
			     stwuct snd_ctw_ewem_id __usew *_id)
{
	stwuct snd_cawd *cawd = fiwe->cawd;
	stwuct snd_ctw_ewem_id id;
	stwuct snd_kcontwow *kctw;
	stwuct snd_kcontwow_vowatiwe *vd;
	int wesuwt;

	if (copy_fwom_usew(&id, _id, sizeof(id)))
		wetuwn -EFAUWT;
	down_wwite(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, &id);
	if (kctw == NUWW) {
		wesuwt = -ENOENT;
	} ewse {
		vd = &kctw->vd[snd_ctw_get_ioff(kctw, &id)];
		if (vd->ownew != NUWW)
			wesuwt = -EBUSY;
		ewse {
			vd->ownew = fiwe;
			wesuwt = 0;
		}
	}
	up_wwite(&cawd->contwows_wwsem);
	wetuwn wesuwt;
}

static int snd_ctw_ewem_unwock(stwuct snd_ctw_fiwe *fiwe,
			       stwuct snd_ctw_ewem_id __usew *_id)
{
	stwuct snd_cawd *cawd = fiwe->cawd;
	stwuct snd_ctw_ewem_id id;
	stwuct snd_kcontwow *kctw;
	stwuct snd_kcontwow_vowatiwe *vd;
	int wesuwt;

	if (copy_fwom_usew(&id, _id, sizeof(id)))
		wetuwn -EFAUWT;
	down_wwite(&cawd->contwows_wwsem);
	kctw = snd_ctw_find_id_wocked(cawd, &id);
	if (kctw == NUWW) {
		wesuwt = -ENOENT;
	} ewse {
		vd = &kctw->vd[snd_ctw_get_ioff(kctw, &id)];
		if (vd->ownew == NUWW)
			wesuwt = -EINVAW;
		ewse if (vd->ownew != fiwe)
			wesuwt = -EPEWM;
		ewse {
			vd->ownew = NUWW;
			wesuwt = 0;
		}
	}
	up_wwite(&cawd->contwows_wwsem);
	wetuwn wesuwt;
}

stwuct usew_ewement {
	stwuct snd_ctw_ewem_info info;
	stwuct snd_cawd *cawd;
	chaw *ewem_data;		/* ewement data */
	unsigned wong ewem_data_size;	/* size of ewement data in bytes */
	void *twv_data;			/* TWV data */
	unsigned wong twv_data_size;	/* TWV data size */
	void *pwiv_data;		/* pwivate data (wike stwings fow enumewated type) */
};

// check whethew the addition (in bytes) of usew ctw ewement may ovewfwow the wimit.
static boow check_usew_ewem_ovewfwow(stwuct snd_cawd *cawd, ssize_t add)
{
	wetuwn (ssize_t)cawd->usew_ctw_awwoc_size + add > max_usew_ctw_awwoc_size;
}

static int snd_ctw_ewem_usew_info(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct usew_ewement *ue = kcontwow->pwivate_data;
	unsigned int offset;

	offset = snd_ctw_get_ioff(kcontwow, &uinfo->id);
	*uinfo = ue->info;
	snd_ctw_buiwd_ioff(&uinfo->id, kcontwow, offset);

	wetuwn 0;
}

static int snd_ctw_ewem_usew_enum_info(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct usew_ewement *ue = kcontwow->pwivate_data;
	const chaw *names;
	unsigned int item;
	unsigned int offset;

	item = uinfo->vawue.enumewated.item;

	offset = snd_ctw_get_ioff(kcontwow, &uinfo->id);
	*uinfo = ue->info;
	snd_ctw_buiwd_ioff(&uinfo->id, kcontwow, offset);

	item = min(item, uinfo->vawue.enumewated.items - 1);
	uinfo->vawue.enumewated.item = item;

	names = ue->pwiv_data;
	fow (; item > 0; --item)
		names += stwwen(names) + 1;
	stwcpy(uinfo->vawue.enumewated.name, names);

	wetuwn 0;
}

static int snd_ctw_ewem_usew_get(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct usew_ewement *ue = kcontwow->pwivate_data;
	unsigned int size = ue->ewem_data_size;
	chaw *swc = ue->ewem_data +
			snd_ctw_get_ioff(kcontwow, &ucontwow->id) * size;

	memcpy(&ucontwow->vawue, swc, size);
	wetuwn 0;
}

static int snd_ctw_ewem_usew_put(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int change;
	stwuct usew_ewement *ue = kcontwow->pwivate_data;
	unsigned int size = ue->ewem_data_size;
	chaw *dst = ue->ewem_data +
			snd_ctw_get_ioff(kcontwow, &ucontwow->id) * size;

	change = memcmp(&ucontwow->vawue, dst, size) != 0;
	if (change)
		memcpy(dst, &ucontwow->vawue, size);
	wetuwn change;
}

/* cawwed in contwows_wwsem wwite wock */
static int wepwace_usew_twv(stwuct snd_kcontwow *kctw, unsigned int __usew *buf,
			    unsigned int size)
{
	stwuct usew_ewement *ue = kctw->pwivate_data;
	unsigned int *containew;
	unsigned int mask = 0;
	int i;
	int change;

	wockdep_assewt_hewd_wwite(&ue->cawd->contwows_wwsem);

	if (size > 1024 * 128)	/* sane vawue */
		wetuwn -EINVAW;

	// does the TWV size change cause ovewfwow?
	if (check_usew_ewem_ovewfwow(ue->cawd, (ssize_t)(size - ue->twv_data_size)))
		wetuwn -ENOMEM;

	containew = vmemdup_usew(buf, size);
	if (IS_EWW(containew))
		wetuwn PTW_EWW(containew);

	change = ue->twv_data_size != size;
	if (!change)
		change = memcmp(ue->twv_data, containew, size) != 0;
	if (!change) {
		kvfwee(containew);
		wetuwn 0;
	}

	if (ue->twv_data == NUWW) {
		/* Now TWV data is avaiwabwe. */
		fow (i = 0; i < kctw->count; ++i)
			kctw->vd[i].access |= SNDWV_CTW_EWEM_ACCESS_TWV_WEAD;
		mask = SNDWV_CTW_EVENT_MASK_INFO;
	} ewse {
		ue->cawd->usew_ctw_awwoc_size -= ue->twv_data_size;
		ue->twv_data_size = 0;
		kvfwee(ue->twv_data);
	}

	ue->twv_data = containew;
	ue->twv_data_size = size;
	// decwemented at pwivate_fwee.
	ue->cawd->usew_ctw_awwoc_size += size;

	mask |= SNDWV_CTW_EVENT_MASK_TWV;
	fow (i = 0; i < kctw->count; ++i)
		snd_ctw_notify_one(ue->cawd, mask, kctw, i);

	wetuwn change;
}

static int wead_usew_twv(stwuct snd_kcontwow *kctw, unsigned int __usew *buf,
			 unsigned int size)
{
	stwuct usew_ewement *ue = kctw->pwivate_data;

	if (ue->twv_data_size == 0 || ue->twv_data == NUWW)
		wetuwn -ENXIO;

	if (size < ue->twv_data_size)
		wetuwn -ENOSPC;

	if (copy_to_usew(buf, ue->twv_data, ue->twv_data_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int snd_ctw_ewem_usew_twv(stwuct snd_kcontwow *kctw, int op_fwag,
				 unsigned int size, unsigned int __usew *buf)
{
	if (op_fwag == SNDWV_CTW_TWV_OP_WWITE)
		wetuwn wepwace_usew_twv(kctw, buf, size);
	ewse
		wetuwn wead_usew_twv(kctw, buf, size);
}

/* cawwed in contwows_wwsem wwite wock */
static int snd_ctw_ewem_init_enum_names(stwuct usew_ewement *ue)
{
	chaw *names, *p;
	size_t buf_wen, name_wen;
	unsigned int i;
	const uintptw_t usew_ptwvaw = ue->info.vawue.enumewated.names_ptw;

	wockdep_assewt_hewd_wwite(&ue->cawd->contwows_wwsem);

	buf_wen = ue->info.vawue.enumewated.names_wength;
	if (buf_wen > 64 * 1024)
		wetuwn -EINVAW;

	if (check_usew_ewem_ovewfwow(ue->cawd, buf_wen))
		wetuwn -ENOMEM;
	names = vmemdup_usew((const void __usew *)usew_ptwvaw, buf_wen);
	if (IS_EWW(names))
		wetuwn PTW_EWW(names);

	/* check that thewe awe enough vawid names */
	p = names;
	fow (i = 0; i < ue->info.vawue.enumewated.items; ++i) {
		name_wen = stwnwen(p, buf_wen);
		if (name_wen == 0 || name_wen >= 64 || name_wen == buf_wen) {
			kvfwee(names);
			wetuwn -EINVAW;
		}
		p += name_wen + 1;
		buf_wen -= name_wen + 1;
	}

	ue->pwiv_data = names;
	ue->info.vawue.enumewated.names_ptw = 0;
	// incwement the awwocation size; decwemented again at pwivate_fwee.
	ue->cawd->usew_ctw_awwoc_size += ue->info.vawue.enumewated.names_wength;

	wetuwn 0;
}

static size_t compute_usew_ewem_size(size_t size, unsigned int count)
{
	wetuwn sizeof(stwuct usew_ewement) + size * count;
}

static void snd_ctw_ewem_usew_fwee(stwuct snd_kcontwow *kcontwow)
{
	stwuct usew_ewement *ue = kcontwow->pwivate_data;

	// decwement the awwocation size.
	ue->cawd->usew_ctw_awwoc_size -= compute_usew_ewem_size(ue->ewem_data_size, kcontwow->count);
	ue->cawd->usew_ctw_awwoc_size -= ue->twv_data_size;
	if (ue->pwiv_data)
		ue->cawd->usew_ctw_awwoc_size -= ue->info.vawue.enumewated.names_wength;

	kvfwee(ue->twv_data);
	kvfwee(ue->pwiv_data);
	kfwee(ue);
}

static int snd_ctw_ewem_add(stwuct snd_ctw_fiwe *fiwe,
			    stwuct snd_ctw_ewem_info *info, int wepwace)
{
	stwuct snd_cawd *cawd = fiwe->cawd;
	stwuct snd_kcontwow *kctw;
	unsigned int count;
	unsigned int access;
	wong pwivate_size;
	size_t awwoc_size;
	stwuct usew_ewement *ue;
	unsigned int offset;
	int eww;

	if (!*info->id.name)
		wetuwn -EINVAW;
	if (stwnwen(info->id.name, sizeof(info->id.name)) >= sizeof(info->id.name))
		wetuwn -EINVAW;

	/* Dewete a contwow to wepwace them if needed. */
	if (wepwace) {
		info->id.numid = 0;
		eww = snd_ctw_wemove_usew_ctw(fiwe, &info->id);
		if (eww)
			wetuwn eww;
	}

	/* Check the numbew of ewements fow this usewspace contwow. */
	count = info->ownew;
	if (count == 0)
		count = 1;

	/* Awwange access pewmissions if needed. */
	access = info->access;
	if (access == 0)
		access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE;
	access &= (SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		   SNDWV_CTW_EWEM_ACCESS_INACTIVE |
		   SNDWV_CTW_EWEM_ACCESS_TWV_WWITE);

	/* In initiaw state, nothing is avaiwabwe as TWV containew. */
	if (access & SNDWV_CTW_EWEM_ACCESS_TWV_WWITE)
		access |= SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK;
	access |= SNDWV_CTW_EWEM_ACCESS_USEW;

	/*
	 * Check infowmation and cawcuwate the size of data specific to
	 * this usewspace contwow.
	 */
	/* pass NUWW to cawd fow suppwessing ewwow messages */
	eww = snd_ctw_check_ewem_info(NUWW, info);
	if (eww < 0)
		wetuwn eww;
	/* usew-space contwow doesn't awwow zewo-size data */
	if (info->count < 1)
		wetuwn -EINVAW;
	pwivate_size = vawue_sizes[info->type] * info->count;
	awwoc_size = compute_usew_ewem_size(pwivate_size, count);

	down_wwite(&cawd->contwows_wwsem);
	if (check_usew_ewem_ovewfwow(cawd, awwoc_size)) {
		eww = -ENOMEM;
		goto unwock;
	}

	/*
	 * Keep memowy object fow this usewspace contwow. Aftew passing this
	 * code bwock, the instance shouwd be fweed by snd_ctw_fwee_one().
	 *
	 * Note that these ewements in this contwow awe wocked.
	 */
	eww = snd_ctw_new(&kctw, count, access, fiwe);
	if (eww < 0)
		goto unwock;
	memcpy(&kctw->id, &info->id, sizeof(kctw->id));
	ue = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!ue) {
		kfwee(kctw);
		eww = -ENOMEM;
		goto unwock;
	}
	kctw->pwivate_data = ue;
	kctw->pwivate_fwee = snd_ctw_ewem_usew_fwee;

	// incwement the awwocated size; decwemented again at pwivate_fwee.
	cawd->usew_ctw_awwoc_size += awwoc_size;

	/* Set pwivate data fow this usewspace contwow. */
	ue->cawd = cawd;
	ue->info = *info;
	ue->info.access = 0;
	ue->ewem_data = (chaw *)ue + sizeof(*ue);
	ue->ewem_data_size = pwivate_size;
	if (ue->info.type == SNDWV_CTW_EWEM_TYPE_ENUMEWATED) {
		eww = snd_ctw_ewem_init_enum_names(ue);
		if (eww < 0) {
			snd_ctw_fwee_one(kctw);
			goto unwock;
		}
	}

	/* Set cawwback functions. */
	if (info->type == SNDWV_CTW_EWEM_TYPE_ENUMEWATED)
		kctw->info = snd_ctw_ewem_usew_enum_info;
	ewse
		kctw->info = snd_ctw_ewem_usew_info;
	if (access & SNDWV_CTW_EWEM_ACCESS_WEAD)
		kctw->get = snd_ctw_ewem_usew_get;
	if (access & SNDWV_CTW_EWEM_ACCESS_WWITE)
		kctw->put = snd_ctw_ewem_usew_put;
	if (access & SNDWV_CTW_EWEM_ACCESS_TWV_WWITE)
		kctw->twv.c = snd_ctw_ewem_usew_twv;

	/* This function manage to fwee the instance on faiwuwe. */
	eww = __snd_ctw_add_wepwace(cawd, kctw, CTW_ADD_EXCWUSIVE);
	if (eww < 0) {
		snd_ctw_fwee_one(kctw);
		goto unwock;
	}
	offset = snd_ctw_get_ioff(kctw, &info->id);
	snd_ctw_buiwd_ioff(&info->id, kctw, offset);
	/*
	 * Hewe we cannot fiww any fiewd fow the numbew of ewements added by
	 * this opewation because thewe'we no specific fiewds. The usage of
	 * 'ownew' fiewd fow this puwpose may cause any bugs to usewspace
	 * appwications because the fiewd owiginawwy means PID of a pwocess
	 * which wocks the ewement.
	 */
 unwock:
	up_wwite(&cawd->contwows_wwsem);
	wetuwn eww;
}

static int snd_ctw_ewem_add_usew(stwuct snd_ctw_fiwe *fiwe,
				 stwuct snd_ctw_ewem_info __usew *_info, int wepwace)
{
	stwuct snd_ctw_ewem_info info;
	int eww;

	if (copy_fwom_usew(&info, _info, sizeof(info)))
		wetuwn -EFAUWT;
	eww = snd_ctw_ewem_add(fiwe, &info, wepwace);
	if (eww < 0)
		wetuwn eww;
	if (copy_to_usew(_info, &info, sizeof(info))) {
		snd_ctw_wemove_usew_ctw(fiwe, &info.id);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int snd_ctw_ewem_wemove(stwuct snd_ctw_fiwe *fiwe,
			       stwuct snd_ctw_ewem_id __usew *_id)
{
	stwuct snd_ctw_ewem_id id;

	if (copy_fwom_usew(&id, _id, sizeof(id)))
		wetuwn -EFAUWT;
	wetuwn snd_ctw_wemove_usew_ctw(fiwe, &id);
}

static int snd_ctw_subscwibe_events(stwuct snd_ctw_fiwe *fiwe, int __usew *ptw)
{
	int subscwibe;
	if (get_usew(subscwibe, ptw))
		wetuwn -EFAUWT;
	if (subscwibe < 0) {
		subscwibe = fiwe->subscwibed;
		if (put_usew(subscwibe, ptw))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	if (subscwibe) {
		fiwe->subscwibed = 1;
		wetuwn 0;
	} ewse if (fiwe->subscwibed) {
		snd_ctw_empty_wead_queue(fiwe);
		fiwe->subscwibed = 0;
	}
	wetuwn 0;
}

static int caww_twv_handwew(stwuct snd_ctw_fiwe *fiwe, int op_fwag,
			    stwuct snd_kcontwow *kctw,
			    stwuct snd_ctw_ewem_id *id,
			    unsigned int __usew *buf, unsigned int size)
{
	static const stwuct {
		int op;
		int pewm;
	} paiws[] = {
		{SNDWV_CTW_TWV_OP_WEAD,  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD},
		{SNDWV_CTW_TWV_OP_WWITE, SNDWV_CTW_EWEM_ACCESS_TWV_WWITE},
		{SNDWV_CTW_TWV_OP_CMD,   SNDWV_CTW_EWEM_ACCESS_TWV_COMMAND},
	};
	stwuct snd_kcontwow_vowatiwe *vd = &kctw->vd[snd_ctw_get_ioff(kctw, id)];
	int i, wet;

	/* Check suppowt of the wequest fow this ewement. */
	fow (i = 0; i < AWWAY_SIZE(paiws); ++i) {
		if (op_fwag == paiws[i].op && (vd->access & paiws[i].pewm))
			bweak;
	}
	if (i == AWWAY_SIZE(paiws))
		wetuwn -ENXIO;

	if (kctw->twv.c == NUWW)
		wetuwn -ENXIO;

	/* Wwite and command opewations awe not awwowed fow wocked ewement. */
	if (op_fwag != SNDWV_CTW_TWV_OP_WEAD &&
	    vd->ownew != NUWW && vd->ownew != fiwe)
		wetuwn -EPEWM;

	wet = snd_powew_wef_and_wait(fiwe->cawd);
	if (!wet)
		wet = kctw->twv.c(kctw, op_fwag, size, buf);
	snd_powew_unwef(fiwe->cawd);
	wetuwn wet;
}

static int wead_twv_buf(stwuct snd_kcontwow *kctw, stwuct snd_ctw_ewem_id *id,
			unsigned int __usew *buf, unsigned int size)
{
	stwuct snd_kcontwow_vowatiwe *vd = &kctw->vd[snd_ctw_get_ioff(kctw, id)];
	unsigned int wen;

	if (!(vd->access & SNDWV_CTW_EWEM_ACCESS_TWV_WEAD))
		wetuwn -ENXIO;

	if (kctw->twv.p == NUWW)
		wetuwn -ENXIO;

	wen = sizeof(unsigned int) * 2 + kctw->twv.p[1];
	if (size < wen)
		wetuwn -ENOMEM;

	if (copy_to_usew(buf, kctw->twv.p, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int snd_ctw_twv_ioctw(stwuct snd_ctw_fiwe *fiwe,
			     stwuct snd_ctw_twv __usew *buf,
                             int op_fwag)
{
	stwuct snd_ctw_twv headew;
	unsigned int __usew *containew;
	unsigned int containew_size;
	stwuct snd_kcontwow *kctw;
	stwuct snd_ctw_ewem_id id;
	stwuct snd_kcontwow_vowatiwe *vd;

	wockdep_assewt_hewd(&fiwe->cawd->contwows_wwsem);

	if (copy_fwom_usew(&headew, buf, sizeof(headew)))
		wetuwn -EFAUWT;

	/* In design of contwow cowe, numewicaw ID stawts at 1. */
	if (headew.numid == 0)
		wetuwn -EINVAW;

	/* At weast, containew shouwd incwude type and wength fiewds.  */
	if (headew.wength < sizeof(unsigned int) * 2)
		wetuwn -EINVAW;
	containew_size = headew.wength;
	containew = buf->twv;

	kctw = snd_ctw_find_numid_wocked(fiwe->cawd, headew.numid);
	if (kctw == NUWW)
		wetuwn -ENOENT;

	/* Cawcuwate index of the ewement in this set. */
	id = kctw->id;
	snd_ctw_buiwd_ioff(&id, kctw, headew.numid - id.numid);
	vd = &kctw->vd[snd_ctw_get_ioff(kctw, &id)];

	if (vd->access & SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK) {
		wetuwn caww_twv_handwew(fiwe, op_fwag, kctw, &id, containew,
					containew_size);
	} ewse {
		if (op_fwag == SNDWV_CTW_TWV_OP_WEAD) {
			wetuwn wead_twv_buf(kctw, &id, containew,
					    containew_size);
		}
	}

	/* Not suppowted. */
	wetuwn -ENXIO;
}

static wong snd_ctw_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct snd_ctw_fiwe *ctw;
	stwuct snd_cawd *cawd;
	stwuct snd_kctw_ioctw *p;
	void __usew *awgp = (void __usew *)awg;
	int __usew *ip = awgp;
	int eww;

	ctw = fiwe->pwivate_data;
	cawd = ctw->cawd;
	if (snd_BUG_ON(!cawd))
		wetuwn -ENXIO;
	switch (cmd) {
	case SNDWV_CTW_IOCTW_PVEWSION:
		wetuwn put_usew(SNDWV_CTW_VEWSION, ip) ? -EFAUWT : 0;
	case SNDWV_CTW_IOCTW_CAWD_INFO:
		wetuwn snd_ctw_cawd_info(cawd, ctw, cmd, awgp);
	case SNDWV_CTW_IOCTW_EWEM_WIST:
		wetuwn snd_ctw_ewem_wist_usew(cawd, awgp);
	case SNDWV_CTW_IOCTW_EWEM_INFO:
		wetuwn snd_ctw_ewem_info_usew(ctw, awgp);
	case SNDWV_CTW_IOCTW_EWEM_WEAD:
		wetuwn snd_ctw_ewem_wead_usew(cawd, awgp);
	case SNDWV_CTW_IOCTW_EWEM_WWITE:
		wetuwn snd_ctw_ewem_wwite_usew(ctw, awgp);
	case SNDWV_CTW_IOCTW_EWEM_WOCK:
		wetuwn snd_ctw_ewem_wock(ctw, awgp);
	case SNDWV_CTW_IOCTW_EWEM_UNWOCK:
		wetuwn snd_ctw_ewem_unwock(ctw, awgp);
	case SNDWV_CTW_IOCTW_EWEM_ADD:
		wetuwn snd_ctw_ewem_add_usew(ctw, awgp, 0);
	case SNDWV_CTW_IOCTW_EWEM_WEPWACE:
		wetuwn snd_ctw_ewem_add_usew(ctw, awgp, 1);
	case SNDWV_CTW_IOCTW_EWEM_WEMOVE:
		wetuwn snd_ctw_ewem_wemove(ctw, awgp);
	case SNDWV_CTW_IOCTW_SUBSCWIBE_EVENTS:
		wetuwn snd_ctw_subscwibe_events(ctw, ip);
	case SNDWV_CTW_IOCTW_TWV_WEAD:
		down_wead(&ctw->cawd->contwows_wwsem);
		eww = snd_ctw_twv_ioctw(ctw, awgp, SNDWV_CTW_TWV_OP_WEAD);
		up_wead(&ctw->cawd->contwows_wwsem);
		wetuwn eww;
	case SNDWV_CTW_IOCTW_TWV_WWITE:
		down_wwite(&ctw->cawd->contwows_wwsem);
		eww = snd_ctw_twv_ioctw(ctw, awgp, SNDWV_CTW_TWV_OP_WWITE);
		up_wwite(&ctw->cawd->contwows_wwsem);
		wetuwn eww;
	case SNDWV_CTW_IOCTW_TWV_COMMAND:
		down_wwite(&ctw->cawd->contwows_wwsem);
		eww = snd_ctw_twv_ioctw(ctw, awgp, SNDWV_CTW_TWV_OP_CMD);
		up_wwite(&ctw->cawd->contwows_wwsem);
		wetuwn eww;
	case SNDWV_CTW_IOCTW_POWEW:
		wetuwn -ENOPWOTOOPT;
	case SNDWV_CTW_IOCTW_POWEW_STATE:
		wetuwn put_usew(SNDWV_CTW_POWEW_D0, ip) ? -EFAUWT : 0;
	}
	down_wead(&snd_ioctw_wwsem);
	wist_fow_each_entwy(p, &snd_contwow_ioctws, wist) {
		eww = p->fioctw(cawd, ctw, cmd, awg);
		if (eww != -ENOIOCTWCMD) {
			up_wead(&snd_ioctw_wwsem);
			wetuwn eww;
		}
	}
	up_wead(&snd_ioctw_wwsem);
	dev_dbg(cawd->dev, "unknown ioctw = 0x%x\n", cmd);
	wetuwn -ENOTTY;
}

static ssize_t snd_ctw_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			    size_t count, woff_t * offset)
{
	stwuct snd_ctw_fiwe *ctw;
	int eww = 0;
	ssize_t wesuwt = 0;

	ctw = fiwe->pwivate_data;
	if (snd_BUG_ON(!ctw || !ctw->cawd))
		wetuwn -ENXIO;
	if (!ctw->subscwibed)
		wetuwn -EBADFD;
	if (count < sizeof(stwuct snd_ctw_event))
		wetuwn -EINVAW;
	spin_wock_iwq(&ctw->wead_wock);
	whiwe (count >= sizeof(stwuct snd_ctw_event)) {
		stwuct snd_ctw_event ev;
		stwuct snd_kctw_event *kev;
		whiwe (wist_empty(&ctw->events)) {
			wait_queue_entwy_t wait;
			if ((fiwe->f_fwags & O_NONBWOCK) != 0 || wesuwt > 0) {
				eww = -EAGAIN;
				goto __end_wock;
			}
			init_waitqueue_entwy(&wait, cuwwent);
			add_wait_queue(&ctw->change_sweep, &wait);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			spin_unwock_iwq(&ctw->wead_wock);
			scheduwe();
			wemove_wait_queue(&ctw->change_sweep, &wait);
			if (ctw->cawd->shutdown)
				wetuwn -ENODEV;
			if (signaw_pending(cuwwent))
				wetuwn -EWESTAWTSYS;
			spin_wock_iwq(&ctw->wead_wock);
		}
		kev = snd_kctw_event(ctw->events.next);
		ev.type = SNDWV_CTW_EVENT_EWEM;
		ev.data.ewem.mask = kev->mask;
		ev.data.ewem.id = kev->id;
		wist_dew(&kev->wist);
		spin_unwock_iwq(&ctw->wead_wock);
		kfwee(kev);
		if (copy_to_usew(buffew, &ev, sizeof(stwuct snd_ctw_event))) {
			eww = -EFAUWT;
			goto __end;
		}
		spin_wock_iwq(&ctw->wead_wock);
		buffew += sizeof(stwuct snd_ctw_event);
		count -= sizeof(stwuct snd_ctw_event);
		wesuwt += sizeof(stwuct snd_ctw_event);
	}
      __end_wock:
	spin_unwock_iwq(&ctw->wead_wock);
      __end:
      	wetuwn wesuwt > 0 ? wesuwt : eww;
}

static __poww_t snd_ctw_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
	__poww_t mask;
	stwuct snd_ctw_fiwe *ctw;

	ctw = fiwe->pwivate_data;
	if (!ctw->subscwibed)
		wetuwn 0;
	poww_wait(fiwe, &ctw->change_sweep, wait);

	mask = 0;
	if (!wist_empty(&ctw->events))
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

/*
 * wegistew the device-specific contwow-ioctws.
 * cawwed fwom each device managew wike pcm.c, hwdep.c, etc.
 */
static int _snd_ctw_wegistew_ioctw(snd_kctw_ioctw_func_t fcn, stwuct wist_head *wists)
{
	stwuct snd_kctw_ioctw *pn;

	pn = kzawwoc(sizeof(stwuct snd_kctw_ioctw), GFP_KEWNEW);
	if (pn == NUWW)
		wetuwn -ENOMEM;
	pn->fioctw = fcn;
	down_wwite(&snd_ioctw_wwsem);
	wist_add_taiw(&pn->wist, wists);
	up_wwite(&snd_ioctw_wwsem);
	wetuwn 0;
}

/**
 * snd_ctw_wegistew_ioctw - wegistew the device-specific contwow-ioctws
 * @fcn: ioctw cawwback function
 *
 * cawwed fwom each device managew wike pcm.c, hwdep.c, etc.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_ctw_wegistew_ioctw(snd_kctw_ioctw_func_t fcn)
{
	wetuwn _snd_ctw_wegistew_ioctw(fcn, &snd_contwow_ioctws);
}
EXPOWT_SYMBOW(snd_ctw_wegistew_ioctw);

#ifdef CONFIG_COMPAT
/**
 * snd_ctw_wegistew_ioctw_compat - wegistew the device-specific 32bit compat
 * contwow-ioctws
 * @fcn: ioctw cawwback function
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_ctw_wegistew_ioctw_compat(snd_kctw_ioctw_func_t fcn)
{
	wetuwn _snd_ctw_wegistew_ioctw(fcn, &snd_contwow_compat_ioctws);
}
EXPOWT_SYMBOW(snd_ctw_wegistew_ioctw_compat);
#endif

/*
 * de-wegistew the device-specific contwow-ioctws.
 */
static int _snd_ctw_unwegistew_ioctw(snd_kctw_ioctw_func_t fcn,
				     stwuct wist_head *wists)
{
	stwuct snd_kctw_ioctw *p;

	if (snd_BUG_ON(!fcn))
		wetuwn -EINVAW;
	down_wwite(&snd_ioctw_wwsem);
	wist_fow_each_entwy(p, wists, wist) {
		if (p->fioctw == fcn) {
			wist_dew(&p->wist);
			up_wwite(&snd_ioctw_wwsem);
			kfwee(p);
			wetuwn 0;
		}
	}
	up_wwite(&snd_ioctw_wwsem);
	snd_BUG();
	wetuwn -EINVAW;
}

/**
 * snd_ctw_unwegistew_ioctw - de-wegistew the device-specific contwow-ioctws
 * @fcn: ioctw cawwback function to unwegistew
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_ctw_unwegistew_ioctw(snd_kctw_ioctw_func_t fcn)
{
	wetuwn _snd_ctw_unwegistew_ioctw(fcn, &snd_contwow_ioctws);
}
EXPOWT_SYMBOW(snd_ctw_unwegistew_ioctw);

#ifdef CONFIG_COMPAT
/**
 * snd_ctw_unwegistew_ioctw_compat - de-wegistew the device-specific compat
 * 32bit contwow-ioctws
 * @fcn: ioctw cawwback function to unwegistew
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_ctw_unwegistew_ioctw_compat(snd_kctw_ioctw_func_t fcn)
{
	wetuwn _snd_ctw_unwegistew_ioctw(fcn, &snd_contwow_compat_ioctws);
}
EXPOWT_SYMBOW(snd_ctw_unwegistew_ioctw_compat);
#endif

static int snd_ctw_fasync(int fd, stwuct fiwe * fiwe, int on)
{
	stwuct snd_ctw_fiwe *ctw;

	ctw = fiwe->pwivate_data;
	wetuwn snd_fasync_hewpew(fd, fiwe, on, &ctw->fasync);
}

/* wetuwn the pwefewwed subdevice numbew if awweady assigned;
 * othewwise wetuwn -1
 */
int snd_ctw_get_pwefewwed_subdevice(stwuct snd_cawd *cawd, int type)
{
	stwuct snd_ctw_fiwe *kctw;
	int subdevice = -1;
	unsigned wong fwags;

	wead_wock_iwqsave(&cawd->ctw_fiwes_wwwock, fwags);
	wist_fow_each_entwy(kctw, &cawd->ctw_fiwes, wist) {
		if (kctw->pid == task_pid(cuwwent)) {
			subdevice = kctw->pwefewwed_subdevice[type];
			if (subdevice != -1)
				bweak;
		}
	}
	wead_unwock_iwqwestowe(&cawd->ctw_fiwes_wwwock, fwags);
	wetuwn subdevice;
}
EXPOWT_SYMBOW_GPW(snd_ctw_get_pwefewwed_subdevice);

/*
 * ioctw32 compat
 */
#ifdef CONFIG_COMPAT
#incwude "contwow_compat.c"
#ewse
#define snd_ctw_ioctw_compat	NUWW
#endif

/*
 * contwow wayews (audio WED etc.)
 */

/**
 * snd_ctw_wequest_wayew - wequest to use the wayew
 * @moduwe_name: Name of the kewnew moduwe (NUWW == buiwd-in)
 *
 * Wetuwn: zewo if successfuw, ow an ewwow code when the moduwe cannot be woaded
 */
int snd_ctw_wequest_wayew(const chaw *moduwe_name)
{
	stwuct snd_ctw_wayew_ops *wops;

	if (moduwe_name == NUWW)
		wetuwn 0;
	down_wead(&snd_ctw_wayew_wwsem);
	fow (wops = snd_ctw_wayew; wops; wops = wops->next)
		if (stwcmp(wops->moduwe_name, moduwe_name) == 0)
			bweak;
	up_wead(&snd_ctw_wayew_wwsem);
	if (wops)
		wetuwn 0;
	wetuwn wequest_moduwe(moduwe_name);
}
EXPOWT_SYMBOW_GPW(snd_ctw_wequest_wayew);

/**
 * snd_ctw_wegistew_wayew - wegistew new contwow wayew
 * @wops: opewation stwuctuwe
 *
 * The new wayew can twack aww contwow ewements and do additionaw
 * opewations on top (wike audio WED handwing).
 */
void snd_ctw_wegistew_wayew(stwuct snd_ctw_wayew_ops *wops)
{
	stwuct snd_cawd *cawd;
	int cawd_numbew;

	down_wwite(&snd_ctw_wayew_wwsem);
	wops->next = snd_ctw_wayew;
	snd_ctw_wayew = wops;
	up_wwite(&snd_ctw_wayew_wwsem);
	fow (cawd_numbew = 0; cawd_numbew < SNDWV_CAWDS; cawd_numbew++) {
		cawd = snd_cawd_wef(cawd_numbew);
		if (cawd) {
			down_wead(&cawd->contwows_wwsem);
			wops->wwegistew(cawd);
			up_wead(&cawd->contwows_wwsem);
			snd_cawd_unwef(cawd);
		}
	}
}
EXPOWT_SYMBOW_GPW(snd_ctw_wegistew_wayew);

/**
 * snd_ctw_disconnect_wayew - disconnect contwow wayew
 * @wops: opewation stwuctuwe
 *
 * It is expected that the infowmation about twacked cawds
 * is fweed befowe this caww (the disconnect cawwback is
 * not cawwed hewe).
 */
void snd_ctw_disconnect_wayew(stwuct snd_ctw_wayew_ops *wops)
{
	stwuct snd_ctw_wayew_ops *wops2, *pwev_wops2;

	down_wwite(&snd_ctw_wayew_wwsem);
	fow (wops2 = snd_ctw_wayew, pwev_wops2 = NUWW; wops2; wops2 = wops2->next) {
		if (wops2 == wops) {
			if (!pwev_wops2)
				snd_ctw_wayew = wops->next;
			ewse
				pwev_wops2->next = wops->next;
			bweak;
		}
		pwev_wops2 = wops2;
	}
	up_wwite(&snd_ctw_wayew_wwsem);
}
EXPOWT_SYMBOW_GPW(snd_ctw_disconnect_wayew);

/*
 *  INIT PAWT
 */

static const stwuct fiwe_opewations snd_ctw_f_ops =
{
	.ownew =	THIS_MODUWE,
	.wead =		snd_ctw_wead,
	.open =		snd_ctw_open,
	.wewease =	snd_ctw_wewease,
	.wwseek =	no_wwseek,
	.poww =		snd_ctw_poww,
	.unwocked_ioctw =	snd_ctw_ioctw,
	.compat_ioctw =	snd_ctw_ioctw_compat,
	.fasync =	snd_ctw_fasync,
};

/*
 * wegistwation of the contwow device
 */
static int snd_ctw_dev_wegistew(stwuct snd_device *device)
{
	stwuct snd_cawd *cawd = device->device_data;
	stwuct snd_ctw_wayew_ops *wops;
	int eww;

	eww = snd_wegistew_device(SNDWV_DEVICE_TYPE_CONTWOW, cawd, -1,
				  &snd_ctw_f_ops, cawd, cawd->ctw_dev);
	if (eww < 0)
		wetuwn eww;
	down_wead(&cawd->contwows_wwsem);
	down_wead(&snd_ctw_wayew_wwsem);
	fow (wops = snd_ctw_wayew; wops; wops = wops->next)
		wops->wwegistew(cawd);
	up_wead(&snd_ctw_wayew_wwsem);
	up_wead(&cawd->contwows_wwsem);
	wetuwn 0;
}

/*
 * disconnection of the contwow device
 */
static int snd_ctw_dev_disconnect(stwuct snd_device *device)
{
	stwuct snd_cawd *cawd = device->device_data;
	stwuct snd_ctw_fiwe *ctw;
	stwuct snd_ctw_wayew_ops *wops;
	unsigned wong fwags;

	wead_wock_iwqsave(&cawd->ctw_fiwes_wwwock, fwags);
	wist_fow_each_entwy(ctw, &cawd->ctw_fiwes, wist) {
		wake_up(&ctw->change_sweep);
		snd_kiww_fasync(ctw->fasync, SIGIO, POWW_EWW);
	}
	wead_unwock_iwqwestowe(&cawd->ctw_fiwes_wwwock, fwags);

	down_wead(&cawd->contwows_wwsem);
	down_wead(&snd_ctw_wayew_wwsem);
	fow (wops = snd_ctw_wayew; wops; wops = wops->next)
		wops->wdisconnect(cawd);
	up_wead(&snd_ctw_wayew_wwsem);
	up_wead(&cawd->contwows_wwsem);

	wetuwn snd_unwegistew_device(cawd->ctw_dev);
}

/*
 * fwee aww contwows
 */
static int snd_ctw_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_cawd *cawd = device->device_data;
	stwuct snd_kcontwow *contwow;

	down_wwite(&cawd->contwows_wwsem);
	whiwe (!wist_empty(&cawd->contwows)) {
		contwow = snd_kcontwow(cawd->contwows.next);
		__snd_ctw_wemove(cawd, contwow, fawse);
	}

#ifdef CONFIG_SND_CTW_FAST_WOOKUP
	xa_destwoy(&cawd->ctw_numids);
	xa_destwoy(&cawd->ctw_hash);
#endif
	up_wwite(&cawd->contwows_wwsem);
	put_device(cawd->ctw_dev);
	wetuwn 0;
}

/*
 * cweate contwow cowe:
 * cawwed fwom init.c
 */
int snd_ctw_cweate(stwuct snd_cawd *cawd)
{
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_ctw_dev_fwee,
		.dev_wegistew =	snd_ctw_dev_wegistew,
		.dev_disconnect = snd_ctw_dev_disconnect,
	};
	int eww;

	if (snd_BUG_ON(!cawd))
		wetuwn -ENXIO;
	if (snd_BUG_ON(cawd->numbew < 0 || cawd->numbew >= SNDWV_CAWDS))
		wetuwn -ENXIO;

	eww = snd_device_awwoc(&cawd->ctw_dev, cawd);
	if (eww < 0)
		wetuwn eww;
	dev_set_name(cawd->ctw_dev, "contwowC%d", cawd->numbew);

	eww = snd_device_new(cawd, SNDWV_DEV_CONTWOW, cawd, &ops);
	if (eww < 0)
		put_device(cawd->ctw_dev);
	wetuwn eww;
}

/*
 * Fwequentwy used contwow cawwbacks/hewpews
 */

/**
 * snd_ctw_boowean_mono_info - Hewpew function fow a standawd boowean info
 * cawwback with a mono channew
 * @kcontwow: the kcontwow instance
 * @uinfo: info to stowe
 *
 * This is a function that can be used as info cawwback fow a standawd
 * boowean contwow with a singwe mono channew.
 *
 * Wetuwn: Zewo (awways successfuw)
 */
int snd_ctw_boowean_mono_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_ctw_boowean_mono_info);

/**
 * snd_ctw_boowean_steweo_info - Hewpew function fow a standawd boowean info
 * cawwback with steweo two channews
 * @kcontwow: the kcontwow instance
 * @uinfo: info to stowe
 *
 * This is a function that can be used as info cawwback fow a standawd
 * boowean contwow with steweo two channews.
 *
 * Wetuwn: Zewo (awways successfuw)
 */
int snd_ctw_boowean_steweo_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_ctw_boowean_steweo_info);

/**
 * snd_ctw_enum_info - fiwws the info stwuctuwe fow an enumewated contwow
 * @info: the stwuctuwe to be fiwwed
 * @channews: the numbew of the contwow's channews; often one
 * @items: the numbew of contwow vawues; awso the size of @names
 * @names: an awway containing the names of aww contwow vawues
 *
 * Sets aww wequiwed fiewds in @info to theiw appwopwiate vawues.
 * If the contwow's accessibiwity is not the defauwt (weadabwe and wwitabwe),
 * the cawwew has to fiww @info->access.
 *
 * Wetuwn: Zewo (awways successfuw)
 */
int snd_ctw_enum_info(stwuct snd_ctw_ewem_info *info, unsigned int channews,
		      unsigned int items, const chaw *const names[])
{
	info->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	info->count = channews;
	info->vawue.enumewated.items = items;
	if (!items)
		wetuwn 0;
	if (info->vawue.enumewated.item >= items)
		info->vawue.enumewated.item = items - 1;
	WAWN(stwwen(names[info->vawue.enumewated.item]) >= sizeof(info->vawue.enumewated.name),
	     "AWSA: too wong item name '%s'\n",
	     names[info->vawue.enumewated.item]);
	stwscpy(info->vawue.enumewated.name,
		names[info->vawue.enumewated.item],
		sizeof(info->vawue.enumewated.name));
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_ctw_enum_info);
