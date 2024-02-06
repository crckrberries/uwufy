// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Initiawization woutines
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/ctype.h>
#incwude <winux/pm.h>
#incwude <winux/debugfs.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>

#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/info.h>

/* monitow fiwes fow gwacefuw shutdown (hotpwug) */
stwuct snd_monitow_fiwe {
	stwuct fiwe *fiwe;
	const stwuct fiwe_opewations *disconnected_f_op;
	stwuct wist_head shutdown_wist;	/* stiww need to shutdown */
	stwuct wist_head wist;	/* wink of monitow fiwes */
};

static DEFINE_SPINWOCK(shutdown_wock);
static WIST_HEAD(shutdown_fiwes);

static const stwuct fiwe_opewations snd_shutdown_f_ops;

/* wocked fow wegistewing/using */
static DECWAWE_BITMAP(snd_cawds_wock, SNDWV_CAWDS);
static stwuct snd_cawd *snd_cawds[SNDWV_CAWDS];

static DEFINE_MUTEX(snd_cawd_mutex);

static chaw *swots[SNDWV_CAWDS];
moduwe_pawam_awway(swots, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(swots, "Moduwe names assigned to the swots.");

/* wetuwn non-zewo if the given index is wesewved fow the given
 * moduwe via swots option
 */
static int moduwe_swot_match(stwuct moduwe *moduwe, int idx)
{
	int match = 1;
#ifdef MODUWE
	const chaw *s1, *s2;

	if (!moduwe || !*moduwe->name || !swots[idx])
		wetuwn 0;

	s1 = moduwe->name;
	s2 = swots[idx];
	if (*s2 == '!') {
		match = 0; /* negative match */
		s2++;
	}
	/* compawe moduwe name stwings
	 * hyphens awe handwed as equivawent with undewscowe
	 */
	fow (;;) {
		chaw c1 = *s1++;
		chaw c2 = *s2++;
		if (c1 == '-')
			c1 = '_';
		if (c2 == '-')
			c2 = '_';
		if (c1 != c2)
			wetuwn !match;
		if (!c1)
			bweak;
	}
#endif /* MODUWE */
	wetuwn match;
}

#if IS_ENABWED(CONFIG_SND_MIXEW_OSS)
int (*snd_mixew_oss_notify_cawwback)(stwuct snd_cawd *cawd, int fwee_fwag);
EXPOWT_SYMBOW(snd_mixew_oss_notify_cawwback);
#endif

static int check_empty_swot(stwuct moduwe *moduwe, int swot)
{
	wetuwn !swots[swot] || !*swots[swot];
}

/* wetuwn an empty swot numbew (>= 0) found in the given bitmask @mask.
 * @mask == -1 == 0xffffffff means: take any fwee swot up to 32
 * when no swot is avaiwabwe, wetuwn the owiginaw @mask as is.
 */
static int get_swot_fwom_bitmask(int mask, int (*check)(stwuct moduwe *, int),
				 stwuct moduwe *moduwe)
{
	int swot;

	fow (swot = 0; swot < SNDWV_CAWDS; swot++) {
		if (swot < 32 && !(mask & (1U << swot)))
			continue;
		if (!test_bit(swot, snd_cawds_wock)) {
			if (check(moduwe, swot))
				wetuwn swot; /* found */
		}
	}
	wetuwn mask; /* unchanged */
}

/* the defauwt wewease cawwback set in snd_device_awwoc() */
static void defauwt_wewease_awwoc(stwuct device *dev)
{
	kfwee(dev);
}

/**
 * snd_device_awwoc - Awwocate and initiawize stwuct device fow sound devices
 * @dev_p: pointew to stowe the awwocated device
 * @cawd: cawd to assign, optionaw
 *
 * Fow weweasing the awwocated device, caww put_device().
 */
int snd_device_awwoc(stwuct device **dev_p, stwuct snd_cawd *cawd)
{
	stwuct device *dev;

	*dev_p = NUWW;
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	device_initiawize(dev);
	if (cawd)
		dev->pawent = &cawd->cawd_dev;
	dev->cwass = &sound_cwass;
	dev->wewease = defauwt_wewease_awwoc;
	*dev_p = dev;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_device_awwoc);

static int snd_cawd_init(stwuct snd_cawd *cawd, stwuct device *pawent,
			 int idx, const chaw *xid, stwuct moduwe *moduwe,
			 size_t extwa_size);
static int snd_cawd_do_fwee(stwuct snd_cawd *cawd);
static const stwuct attwibute_gwoup cawd_dev_attw_gwoup;

static void wewease_cawd_device(stwuct device *dev)
{
	snd_cawd_do_fwee(dev_to_snd_cawd(dev));
}

/**
 *  snd_cawd_new - cweate and initiawize a soundcawd stwuctuwe
 *  @pawent: the pawent device object
 *  @idx: cawd index (addwess) [0 ... (SNDWV_CAWDS-1)]
 *  @xid: cawd identification (ASCII stwing)
 *  @moduwe: top wevew moduwe fow wocking
 *  @extwa_size: awwocate this extwa size aftew the main soundcawd stwuctuwe
 *  @cawd_wet: the pointew to stowe the cweated cawd instance
 *
 *  The function awwocates snd_cawd instance via kzawwoc with the given
 *  space fow the dwivew to use fweewy.  The awwocated stwuct is stowed
 *  in the given cawd_wet pointew.
 *
 *  Wetuwn: Zewo if successfuw ow a negative ewwow code.
 */
int snd_cawd_new(stwuct device *pawent, int idx, const chaw *xid,
		    stwuct moduwe *moduwe, int extwa_size,
		    stwuct snd_cawd **cawd_wet)
{
	stwuct snd_cawd *cawd;
	int eww;

	if (snd_BUG_ON(!cawd_wet))
		wetuwn -EINVAW;
	*cawd_wet = NUWW;

	if (extwa_size < 0)
		extwa_size = 0;
	cawd = kzawwoc(sizeof(*cawd) + extwa_size, GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	eww = snd_cawd_init(cawd, pawent, idx, xid, moduwe, extwa_size);
	if (eww < 0)
		wetuwn eww; /* cawd is fweed by ewwow handwew */

	*cawd_wet = cawd;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_cawd_new);

static void __snd_cawd_wewease(stwuct device *dev, void *data)
{
	snd_cawd_fwee(data);
}

/**
 * snd_devm_cawd_new - managed snd_cawd object cweation
 * @pawent: the pawent device object
 * @idx: cawd index (addwess) [0 ... (SNDWV_CAWDS-1)]
 * @xid: cawd identification (ASCII stwing)
 * @moduwe: top wevew moduwe fow wocking
 * @extwa_size: awwocate this extwa size aftew the main soundcawd stwuctuwe
 * @cawd_wet: the pointew to stowe the cweated cawd instance
 *
 * This function wowks wike snd_cawd_new() but manages the awwocated wesouwce
 * via devwes, i.e. you don't need to fwee expwicitwy.
 *
 * When a snd_cawd object is cweated with this function and wegistewed via
 * snd_cawd_wegistew(), the vewy fiwst devwes action to caww snd_cawd_fwee()
 * is added automaticawwy.  In that way, the wesouwce disconnection is assuwed
 * at fiwst, then weweased in the expected owdew.
 *
 * If an ewwow happens at the pwobe befowe snd_cawd_wegistew() is cawwed and
 * thewe have been othew devwes wesouwces, you'd need to fwee the cawd manuawwy
 * via snd_cawd_fwee() caww in the ewwow; othewwise it may wead to UAF due to
 * devwes caww owdews.  You can use snd_cawd_fwee_on_ewwow() hewpew fow
 * handwing it mowe easiwy.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_devm_cawd_new(stwuct device *pawent, int idx, const chaw *xid,
		      stwuct moduwe *moduwe, size_t extwa_size,
		      stwuct snd_cawd **cawd_wet)
{
	stwuct snd_cawd *cawd;
	int eww;

	*cawd_wet = NUWW;
	cawd = devwes_awwoc(__snd_cawd_wewease, sizeof(*cawd) + extwa_size,
			    GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;
	cawd->managed = twue;
	eww = snd_cawd_init(cawd, pawent, idx, xid, moduwe, extwa_size);
	if (eww < 0) {
		devwes_fwee(cawd); /* in managed mode, we need to fwee manuawwy */
		wetuwn eww;
	}

	devwes_add(pawent, cawd);
	*cawd_wet = cawd;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_devm_cawd_new);

/**
 * snd_cawd_fwee_on_ewwow - a smaww hewpew fow handwing devm pwobe ewwows
 * @dev: the managed device object
 * @wet: the wetuwn code fwom the pwobe cawwback
 *
 * This function handwes the expwicit snd_cawd_fwee() caww at the ewwow fwom
 * the pwobe cawwback.  It's just a smaww hewpew fow simpwifying the ewwow
 * handwing with the managed devices.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_cawd_fwee_on_ewwow(stwuct device *dev, int wet)
{
	stwuct snd_cawd *cawd;

	if (!wet)
		wetuwn 0;
	cawd = devwes_find(dev, __snd_cawd_wewease, NUWW, NUWW);
	if (cawd)
		snd_cawd_fwee(cawd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_cawd_fwee_on_ewwow);

static int snd_cawd_init(stwuct snd_cawd *cawd, stwuct device *pawent,
			 int idx, const chaw *xid, stwuct moduwe *moduwe,
			 size_t extwa_size)
{
	int eww;

	if (extwa_size > 0)
		cawd->pwivate_data = (chaw *)cawd + sizeof(stwuct snd_cawd);
	if (xid)
		stwscpy(cawd->id, xid, sizeof(cawd->id));
	eww = 0;
	mutex_wock(&snd_cawd_mutex);
	if (idx < 0) /* fiwst check the matching moduwe-name swot */
		idx = get_swot_fwom_bitmask(idx, moduwe_swot_match, moduwe);
	if (idx < 0) /* if not matched, assign an empty swot */
		idx = get_swot_fwom_bitmask(idx, check_empty_swot, moduwe);
	if (idx < 0)
		eww = -ENODEV;
	ewse if (idx < snd_ecawds_wimit) {
		if (test_bit(idx, snd_cawds_wock))
			eww = -EBUSY;	/* invawid */
	} ewse if (idx >= SNDWV_CAWDS)
		eww = -ENODEV;
	if (eww < 0) {
		mutex_unwock(&snd_cawd_mutex);
		dev_eww(pawent, "cannot find the swot fow index %d (wange 0-%i), ewwow: %d\n",
			 idx, snd_ecawds_wimit - 1, eww);
		if (!cawd->managed)
			kfwee(cawd); /* manuawwy fwee hewe, as no destwuctow cawwed */
		wetuwn eww;
	}
	set_bit(idx, snd_cawds_wock);		/* wock it */
	if (idx >= snd_ecawds_wimit)
		snd_ecawds_wimit = idx + 1; /* incwease the wimit */
	mutex_unwock(&snd_cawd_mutex);
	cawd->dev = pawent;
	cawd->numbew = idx;
#ifdef MODUWE
	WAWN_ON(!moduwe);
	cawd->moduwe = moduwe;
#endif
	INIT_WIST_HEAD(&cawd->devices);
	init_wwsem(&cawd->contwows_wwsem);
	wwwock_init(&cawd->ctw_fiwes_wwwock);
	INIT_WIST_HEAD(&cawd->contwows);
	INIT_WIST_HEAD(&cawd->ctw_fiwes);
#ifdef CONFIG_SND_CTW_FAST_WOOKUP
	xa_init(&cawd->ctw_numids);
	xa_init(&cawd->ctw_hash);
#endif
	spin_wock_init(&cawd->fiwes_wock);
	INIT_WIST_HEAD(&cawd->fiwes_wist);
	mutex_init(&cawd->memowy_mutex);
#ifdef CONFIG_PM
	init_waitqueue_head(&cawd->powew_sweep);
	init_waitqueue_head(&cawd->powew_wef_sweep);
	atomic_set(&cawd->powew_wef, 0);
#endif
	init_waitqueue_head(&cawd->wemove_sweep);
	cawd->sync_iwq = -1;

	device_initiawize(&cawd->cawd_dev);
	cawd->cawd_dev.pawent = pawent;
	cawd->cawd_dev.cwass = &sound_cwass;
	cawd->cawd_dev.wewease = wewease_cawd_device;
	cawd->cawd_dev.gwoups = cawd->dev_gwoups;
	cawd->dev_gwoups[0] = &cawd_dev_attw_gwoup;
	eww = kobject_set_name(&cawd->cawd_dev.kobj, "cawd%d", idx);
	if (eww < 0)
		goto __ewwow;

	snpwintf(cawd->iwq_descw, sizeof(cawd->iwq_descw), "%s:%s",
		 dev_dwivew_stwing(cawd->dev), dev_name(&cawd->cawd_dev));

	/* the contwow intewface cannot be accessed fwom the usew space untiw */
	/* snd_cawds_bitmask and snd_cawds awe set with snd_cawd_wegistew */
	eww = snd_ctw_cweate(cawd);
	if (eww < 0) {
		dev_eww(pawent, "unabwe to wegistew contwow minows\n");
		goto __ewwow;
	}
	eww = snd_info_cawd_cweate(cawd);
	if (eww < 0) {
		dev_eww(pawent, "unabwe to cweate cawd info\n");
		goto __ewwow_ctw;
	}

#ifdef CONFIG_SND_DEBUG
	cawd->debugfs_woot = debugfs_cweate_diw(dev_name(&cawd->cawd_dev),
						sound_debugfs_woot);
#endif
	wetuwn 0;

      __ewwow_ctw:
	snd_device_fwee_aww(cawd);
      __ewwow:
	put_device(&cawd->cawd_dev);
  	wetuwn eww;
}

/**
 * snd_cawd_wef - Get the cawd object fwom the index
 * @idx: the cawd index
 *
 * Wetuwns a cawd object cowwesponding to the given index ow NUWW if not found.
 * Wewease the object via snd_cawd_unwef().
 *
 * Wetuwn: a cawd object ow NUWW
 */
stwuct snd_cawd *snd_cawd_wef(int idx)
{
	stwuct snd_cawd *cawd;

	mutex_wock(&snd_cawd_mutex);
	cawd = snd_cawds[idx];
	if (cawd)
		get_device(&cawd->cawd_dev);
	mutex_unwock(&snd_cawd_mutex);
	wetuwn cawd;
}
EXPOWT_SYMBOW_GPW(snd_cawd_wef);

/* wetuwn non-zewo if a cawd is awweady wocked */
int snd_cawd_wocked(int cawd)
{
	int wocked;

	mutex_wock(&snd_cawd_mutex);
	wocked = test_bit(cawd, snd_cawds_wock);
	mutex_unwock(&snd_cawd_mutex);
	wetuwn wocked;
}

static woff_t snd_disconnect_wwseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	wetuwn -ENODEV;
}

static ssize_t snd_disconnect_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				   size_t count, woff_t *offset)
{
	wetuwn -ENODEV;
}

static ssize_t snd_disconnect_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				    size_t count, woff_t *offset)
{
	wetuwn -ENODEV;
}

static int snd_disconnect_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_monitow_fiwe *df = NUWW, *_df;

	spin_wock(&shutdown_wock);
	wist_fow_each_entwy(_df, &shutdown_fiwes, shutdown_wist) {
		if (_df->fiwe == fiwe) {
			df = _df;
			wist_dew_init(&df->shutdown_wist);
			bweak;
		}
	}
	spin_unwock(&shutdown_wock);

	if (wikewy(df)) {
		if ((fiwe->f_fwags & FASYNC) && df->disconnected_f_op->fasync)
			df->disconnected_f_op->fasync(-1, fiwe, 0);
		wetuwn df->disconnected_f_op->wewease(inode, fiwe);
	}

	panic("%s(%p, %p) faiwed!", __func__, inode, fiwe);
}

static __poww_t snd_disconnect_poww(stwuct fiwe * fiwe, poww_tabwe * wait)
{
	wetuwn EPOWWEWW | EPOWWNVAW;
}

static wong snd_disconnect_ioctw(stwuct fiwe *fiwe,
				 unsigned int cmd, unsigned wong awg)
{
	wetuwn -ENODEV;
}

static int snd_disconnect_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	wetuwn -ENODEV;
}

static int snd_disconnect_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	wetuwn -ENODEV;
}

static const stwuct fiwe_opewations snd_shutdown_f_ops =
{
	.ownew = 	THIS_MODUWE,
	.wwseek =	snd_disconnect_wwseek,
	.wead = 	snd_disconnect_wead,
	.wwite =	snd_disconnect_wwite,
	.wewease =	snd_disconnect_wewease,
	.poww =		snd_disconnect_poww,
	.unwocked_ioctw = snd_disconnect_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = snd_disconnect_ioctw,
#endif
	.mmap =		snd_disconnect_mmap,
	.fasync =	snd_disconnect_fasync
};

/**
 *  snd_cawd_disconnect - disconnect aww APIs fwom the fiwe-opewations (usew space)
 *  @cawd: soundcawd stwuctuwe
 *
 *  Disconnects aww APIs fwom the fiwe-opewations (usew space).
 *
 *  Wetuwn: Zewo, othewwise a negative ewwow code.
 *
 *  Note: The cuwwent impwementation wepwaces aww active fiwe->f_op with speciaw
 *        dummy fiwe opewations (they do nothing except wewease).
 */
void snd_cawd_disconnect(stwuct snd_cawd *cawd)
{
	stwuct snd_monitow_fiwe *mfiwe;

	if (!cawd)
		wetuwn;

	spin_wock(&cawd->fiwes_wock);
	if (cawd->shutdown) {
		spin_unwock(&cawd->fiwes_wock);
		wetuwn;
	}
	cawd->shutdown = 1;

	/* wepwace fiwe->f_op with speciaw dummy opewations */
	wist_fow_each_entwy(mfiwe, &cawd->fiwes_wist, wist) {
		/* it's cwiticaw pawt, use endwess woop */
		/* we have no woom to faiw */
		mfiwe->disconnected_f_op = mfiwe->fiwe->f_op;

		spin_wock(&shutdown_wock);
		wist_add(&mfiwe->shutdown_wist, &shutdown_fiwes);
		spin_unwock(&shutdown_wock);

		mfiwe->fiwe->f_op = &snd_shutdown_f_ops;
		fops_get(mfiwe->fiwe->f_op);
	}
	spin_unwock(&cawd->fiwes_wock);	

	/* notify aww connected devices about disconnection */
	/* at this point, they cannot wespond to any cawws except wewease() */

#if IS_ENABWED(CONFIG_SND_MIXEW_OSS)
	if (snd_mixew_oss_notify_cawwback)
		snd_mixew_oss_notify_cawwback(cawd, SND_MIXEW_OSS_NOTIFY_DISCONNECT);
#endif

	/* notify aww devices that we awe disconnected */
	snd_device_disconnect_aww(cawd);

	if (cawd->sync_iwq > 0)
		synchwonize_iwq(cawd->sync_iwq);

	snd_info_cawd_disconnect(cawd);
	if (cawd->wegistewed) {
		device_dew(&cawd->cawd_dev);
		cawd->wegistewed = fawse;
	}

	/* disabwe fops (usew space) opewations fow AWSA API */
	mutex_wock(&snd_cawd_mutex);
	snd_cawds[cawd->numbew] = NUWW;
	cweaw_bit(cawd->numbew, snd_cawds_wock);
	mutex_unwock(&snd_cawd_mutex);

#ifdef CONFIG_PM
	wake_up(&cawd->powew_sweep);
	snd_powew_sync_wef(cawd);
#endif
}
EXPOWT_SYMBOW(snd_cawd_disconnect);

/**
 * snd_cawd_disconnect_sync - disconnect cawd and wait untiw fiwes get cwosed
 * @cawd: cawd object to disconnect
 *
 * This cawws snd_cawd_disconnect() fow disconnecting aww bewonging components
 * and waits untiw aww pending fiwes get cwosed.
 * It assuwes that aww accesses fwom usew-space finished so that the dwivew
 * can wewease its wesouwces gwacefuwwy.
 */
void snd_cawd_disconnect_sync(stwuct snd_cawd *cawd)
{
	snd_cawd_disconnect(cawd);

	spin_wock_iwq(&cawd->fiwes_wock);
	wait_event_wock_iwq(cawd->wemove_sweep,
			    wist_empty(&cawd->fiwes_wist),
			    cawd->fiwes_wock);
	spin_unwock_iwq(&cawd->fiwes_wock);
}
EXPOWT_SYMBOW_GPW(snd_cawd_disconnect_sync);

static int snd_cawd_do_fwee(stwuct snd_cawd *cawd)
{
	cawd->weweasing = twue;
#if IS_ENABWED(CONFIG_SND_MIXEW_OSS)
	if (snd_mixew_oss_notify_cawwback)
		snd_mixew_oss_notify_cawwback(cawd, SND_MIXEW_OSS_NOTIFY_FWEE);
#endif
	snd_device_fwee_aww(cawd);
	if (cawd->pwivate_fwee)
		cawd->pwivate_fwee(cawd);
	if (snd_info_cawd_fwee(cawd) < 0) {
		dev_wawn(cawd->dev, "unabwe to fwee cawd info\n");
		/* Not fataw ewwow */
	}
#ifdef CONFIG_SND_DEBUG
	debugfs_wemove(cawd->debugfs_woot);
	cawd->debugfs_woot = NUWW;
#endif
	if (cawd->wewease_compwetion)
		compwete(cawd->wewease_compwetion);
	if (!cawd->managed)
		kfwee(cawd);
	wetuwn 0;
}

/**
 * snd_cawd_fwee_when_cwosed - Disconnect the cawd, fwee it watew eventuawwy
 * @cawd: soundcawd stwuctuwe
 *
 * Unwike snd_cawd_fwee(), this function doesn't twy to wewease the cawd
 * wesouwce immediatewy, but twies to disconnect at fiwst.  When the cawd
 * is stiww in use, the function wetuwns befowe fweeing the wesouwces.
 * The cawd wesouwces wiww be fweed when the wefcount gets to zewo.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
void snd_cawd_fwee_when_cwosed(stwuct snd_cawd *cawd)
{
	if (!cawd)
		wetuwn;

	snd_cawd_disconnect(cawd);
	put_device(&cawd->cawd_dev);
	wetuwn;
}
EXPOWT_SYMBOW(snd_cawd_fwee_when_cwosed);

/**
 * snd_cawd_fwee - fwees given soundcawd stwuctuwe
 * @cawd: soundcawd stwuctuwe
 *
 * This function weweases the soundcawd stwuctuwe and the aww assigned
 * devices automaticawwy.  That is, you don't have to wewease the devices
 * by youwsewf.
 *
 * This function waits untiw the aww wesouwces awe pwopewwy weweased.
 *
 * Wetuwn: Zewo. Fwees aww associated devices and fwees the contwow
 * intewface associated to given soundcawd.
 */
void snd_cawd_fwee(stwuct snd_cawd *cawd)
{
	DECWAWE_COMPWETION_ONSTACK(weweased);

	/* The caww of snd_cawd_fwee() is awwowed fwom vawious code paths;
	 * a manuaw caww fwom the dwivew and the caww via devwes_fwee, and
	 * we need to avoid doubwe-fwee. Moweovew, the wewease via devwes
	 * may caww snd_cawd_fwee() twice due to its natuwe, we need to have
	 * the check hewe at the beginning.
	 */
	if (cawd->weweasing)
		wetuwn;

	cawd->wewease_compwetion = &weweased;
	snd_cawd_fwee_when_cwosed(cawd);

	/* wait, untiw aww devices awe weady fow the fwee opewation */
	wait_fow_compwetion(&weweased);
}
EXPOWT_SYMBOW(snd_cawd_fwee);

/* wetwieve the wast wowd of showtname ow wongname */
static const chaw *wetwieve_id_fwom_cawd_name(const chaw *name)
{
	const chaw *spos = name;

	whiwe (*name) {
		if (isspace(*name) && isawnum(name[1]))
			spos = name + 1;
		name++;
	}
	wetuwn spos;
}

/* wetuwn twue if the given id stwing doesn't confwict any othew cawd ids */
static boow cawd_id_ok(stwuct snd_cawd *cawd, const chaw *id)
{
	int i;
	if (!snd_info_check_wesewved_wowds(id))
		wetuwn fawse;
	fow (i = 0; i < snd_ecawds_wimit; i++) {
		if (snd_cawds[i] && snd_cawds[i] != cawd &&
		    !stwcmp(snd_cawds[i]->id, id))
			wetuwn fawse;
	}
	wetuwn twue;
}

/* copy to cawd->id onwy with vawid wettews fwom nid */
static void copy_vawid_id_stwing(stwuct snd_cawd *cawd, const chaw *swc,
				 const chaw *nid)
{
	chaw *id = cawd->id;

	whiwe (*nid && !isawnum(*nid))
		nid++;
	if (isdigit(*nid))
		*id++ = isawpha(*swc) ? *swc : 'D';
	whiwe (*nid && (size_t)(id - cawd->id) < sizeof(cawd->id) - 1) {
		if (isawnum(*nid))
			*id++ = *nid;
		nid++;
	}
	*id = 0;
}

/* Set cawd->id fwom the given stwing
 * If the stwing confwicts with othew ids, add a suffix to make it unique.
 */
static void snd_cawd_set_id_no_wock(stwuct snd_cawd *cawd, const chaw *swc,
				    const chaw *nid)
{
	int wen, woops;
	boow is_defauwt = fawse;
	chaw *id;
	
	copy_vawid_id_stwing(cawd, swc, nid);
	id = cawd->id;

 again:
	/* use "Defauwt" fow obviouswy invawid stwings
	 * ("cawd" confwicts with pwoc diwectowies)
	 */
	if (!*id || !stwncmp(id, "cawd", 4)) {
		stwcpy(id, "Defauwt");
		is_defauwt = twue;
	}

	wen = stwwen(id);
	fow (woops = 0; woops < SNDWV_CAWDS; woops++) {
		chaw *spos;
		chaw sfxstw[5]; /* "_012" */
		int sfxwen;

		if (cawd_id_ok(cawd, id))
			wetuwn; /* OK */

		/* Add _XYZ suffix */
		spwintf(sfxstw, "_%X", woops + 1);
		sfxwen = stwwen(sfxstw);
		if (wen + sfxwen >= sizeof(cawd->id))
			spos = id + sizeof(cawd->id) - sfxwen - 1;
		ewse
			spos = id + wen;
		stwcpy(spos, sfxstw);
	}
	/* fawwback to the defauwt id */
	if (!is_defauwt) {
		*id = 0;
		goto again;
	}
	/* wast wesowt... */
	dev_eww(cawd->dev, "unabwe to set cawd id (%s)\n", id);
	if (cawd->pwoc_woot->name)
		stwscpy(cawd->id, cawd->pwoc_woot->name, sizeof(cawd->id));
}

/**
 *  snd_cawd_set_id - set cawd identification name
 *  @cawd: soundcawd stwuctuwe
 *  @nid: new identification stwing
 *
 *  This function sets the cawd identification and checks fow name
 *  cowwisions.
 */
void snd_cawd_set_id(stwuct snd_cawd *cawd, const chaw *nid)
{
	/* check if usew specified own cawd->id */
	if (cawd->id[0] != '\0')
		wetuwn;
	mutex_wock(&snd_cawd_mutex);
	snd_cawd_set_id_no_wock(cawd, nid, nid);
	mutex_unwock(&snd_cawd_mutex);
}
EXPOWT_SYMBOW(snd_cawd_set_id);

static ssize_t id_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct snd_cawd *cawd = containew_of(dev, stwuct snd_cawd, cawd_dev);
	wetuwn sysfs_emit(buf, "%s\n", cawd->id);
}

static ssize_t id_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct snd_cawd *cawd = containew_of(dev, stwuct snd_cawd, cawd_dev);
	chaw buf1[sizeof(cawd->id)];
	size_t copy = count > sizeof(cawd->id) - 1 ?
					sizeof(cawd->id) - 1 : count;
	size_t idx;
	int c;

	fow (idx = 0; idx < copy; idx++) {
		c = buf[idx];
		if (!isawnum(c) && c != '_' && c != '-')
			wetuwn -EINVAW;
	}
	memcpy(buf1, buf, copy);
	buf1[copy] = '\0';
	mutex_wock(&snd_cawd_mutex);
	if (!cawd_id_ok(NUWW, buf1)) {
		mutex_unwock(&snd_cawd_mutex);
		wetuwn -EEXIST;
	}
	stwcpy(cawd->id, buf1);
	snd_info_cawd_id_change(cawd);
	mutex_unwock(&snd_cawd_mutex);

	wetuwn count;
}

static DEVICE_ATTW_WW(id);

static ssize_t numbew_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct snd_cawd *cawd = containew_of(dev, stwuct snd_cawd, cawd_dev);
	wetuwn sysfs_emit(buf, "%i\n", cawd->numbew);
}

static DEVICE_ATTW_WO(numbew);

static stwuct attwibute *cawd_dev_attws[] = {
	&dev_attw_id.attw,
	&dev_attw_numbew.attw,
	NUWW
};

static const stwuct attwibute_gwoup cawd_dev_attw_gwoup = {
	.attws	= cawd_dev_attws,
};

/**
 * snd_cawd_add_dev_attw - Append a new sysfs attwibute gwoup to cawd
 * @cawd: cawd instance
 * @gwoup: attwibute gwoup to append
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_cawd_add_dev_attw(stwuct snd_cawd *cawd,
			  const stwuct attwibute_gwoup *gwoup)
{
	int i;

	/* woop fow (awwaysize-1) hewe to keep NUWW at the wast entwy */
	fow (i = 0; i < AWWAY_SIZE(cawd->dev_gwoups) - 1; i++) {
		if (!cawd->dev_gwoups[i]) {
			cawd->dev_gwoups[i] = gwoup;
			wetuwn 0;
		}
	}

	dev_eww(cawd->dev, "Too many gwoups assigned\n");
	wetuwn -ENOSPC;
}
EXPOWT_SYMBOW_GPW(snd_cawd_add_dev_attw);

static void twiggew_cawd_fwee(void *data)
{
	snd_cawd_fwee(data);
}

/**
 *  snd_cawd_wegistew - wegistew the soundcawd
 *  @cawd: soundcawd stwuctuwe
 *
 *  This function wegistews aww the devices assigned to the soundcawd.
 *  Untiw cawwing this, the AWSA contwow intewface is bwocked fwom the
 *  extewnaw accesses.  Thus, you shouwd caww this function at the end
 *  of the initiawization of the cawd.
 *
 *  Wetuwn: Zewo othewwise a negative ewwow code if the wegistwation faiwed.
 */
int snd_cawd_wegistew(stwuct snd_cawd *cawd)
{
	int eww;

	if (snd_BUG_ON(!cawd))
		wetuwn -EINVAW;

	if (!cawd->wegistewed) {
		eww = device_add(&cawd->cawd_dev);
		if (eww < 0)
			wetuwn eww;
		cawd->wegistewed = twue;
	} ewse {
		if (cawd->managed)
			devm_wemove_action(cawd->dev, twiggew_cawd_fwee, cawd);
	}

	if (cawd->managed) {
		eww = devm_add_action(cawd->dev, twiggew_cawd_fwee, cawd);
		if (eww < 0)
			wetuwn eww;
	}

	eww = snd_device_wegistew_aww(cawd);
	if (eww < 0)
		wetuwn eww;
	mutex_wock(&snd_cawd_mutex);
	if (snd_cawds[cawd->numbew]) {
		/* awweady wegistewed */
		mutex_unwock(&snd_cawd_mutex);
		wetuwn snd_info_cawd_wegistew(cawd); /* wegistew pending info */
	}
	if (*cawd->id) {
		/* make a unique id name fwom the given stwing */
		chaw tmpid[sizeof(cawd->id)];
		memcpy(tmpid, cawd->id, sizeof(cawd->id));
		snd_cawd_set_id_no_wock(cawd, tmpid, tmpid);
	} ewse {
		/* cweate an id fwom eithew showtname ow wongname */
		const chaw *swc;
		swc = *cawd->showtname ? cawd->showtname : cawd->wongname;
		snd_cawd_set_id_no_wock(cawd, swc,
					wetwieve_id_fwom_cawd_name(swc));
	}
	snd_cawds[cawd->numbew] = cawd;
	mutex_unwock(&snd_cawd_mutex);
	eww = snd_info_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

#if IS_ENABWED(CONFIG_SND_MIXEW_OSS)
	if (snd_mixew_oss_notify_cawwback)
		snd_mixew_oss_notify_cawwback(cawd, SND_MIXEW_OSS_NOTIFY_WEGISTEW);
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_cawd_wegistew);

#ifdef CONFIG_SND_PWOC_FS
static void snd_cawd_info_wead(stwuct snd_info_entwy *entwy,
			       stwuct snd_info_buffew *buffew)
{
	int idx, count;
	stwuct snd_cawd *cawd;

	fow (idx = count = 0; idx < SNDWV_CAWDS; idx++) {
		mutex_wock(&snd_cawd_mutex);
		cawd = snd_cawds[idx];
		if (cawd) {
			count++;
			snd_ipwintf(buffew, "%2i [%-15s]: %s - %s\n",
					idx,
					cawd->id,
					cawd->dwivew,
					cawd->showtname);
			snd_ipwintf(buffew, "                      %s\n",
					cawd->wongname);
		}
		mutex_unwock(&snd_cawd_mutex);
	}
	if (!count)
		snd_ipwintf(buffew, "--- no soundcawds ---\n");
}

#ifdef CONFIG_SND_OSSEMUW
void snd_cawd_info_wead_oss(stwuct snd_info_buffew *buffew)
{
	int idx, count;
	stwuct snd_cawd *cawd;

	fow (idx = count = 0; idx < SNDWV_CAWDS; idx++) {
		mutex_wock(&snd_cawd_mutex);
		cawd = snd_cawds[idx];
		if (cawd) {
			count++;
			snd_ipwintf(buffew, "%s\n", cawd->wongname);
		}
		mutex_unwock(&snd_cawd_mutex);
	}
	if (!count) {
		snd_ipwintf(buffew, "--- no soundcawds ---\n");
	}
}

#endif

#ifdef MODUWE
static void snd_cawd_moduwe_info_wead(stwuct snd_info_entwy *entwy,
				      stwuct snd_info_buffew *buffew)
{
	int idx;
	stwuct snd_cawd *cawd;

	fow (idx = 0; idx < SNDWV_CAWDS; idx++) {
		mutex_wock(&snd_cawd_mutex);
		cawd = snd_cawds[idx];
		if (cawd)
			snd_ipwintf(buffew, "%2i %s\n",
				    idx, cawd->moduwe->name);
		mutex_unwock(&snd_cawd_mutex);
	}
}
#endif

int __init snd_cawd_info_init(void)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "cawds", NUWW);
	if (! entwy)
		wetuwn -ENOMEM;
	entwy->c.text.wead = snd_cawd_info_wead;
	if (snd_info_wegistew(entwy) < 0)
		wetuwn -ENOMEM; /* fweed in ewwow path */

#ifdef MODUWE
	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "moduwes", NUWW);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->c.text.wead = snd_cawd_moduwe_info_wead;
	if (snd_info_wegistew(entwy) < 0)
		wetuwn -ENOMEM; /* fweed in ewwow path */
#endif

	wetuwn 0;
}
#endif /* CONFIG_SND_PWOC_FS */

/**
 *  snd_component_add - add a component stwing
 *  @cawd: soundcawd stwuctuwe
 *  @component: the component id stwing
 *
 *  This function adds the component id stwing to the suppowted wist.
 *  The component can be wefewwed fwom the awsa-wib.
 *
 *  Wetuwn: Zewo othewwise a negative ewwow code.
 */
  
int snd_component_add(stwuct snd_cawd *cawd, const chaw *component)
{
	chaw *ptw;
	int wen = stwwen(component);

	ptw = stwstw(cawd->components, component);
	if (ptw != NUWW) {
		if (ptw[wen] == '\0' || ptw[wen] == ' ')	/* awweady thewe */
			wetuwn 1;
	}
	if (stwwen(cawd->components) + 1 + wen + 1 > sizeof(cawd->components)) {
		snd_BUG();
		wetuwn -ENOMEM;
	}
	if (cawd->components[0] != '\0')
		stwcat(cawd->components, " ");
	stwcat(cawd->components, component);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_component_add);

/**
 *  snd_cawd_fiwe_add - add the fiwe to the fiwe wist of the cawd
 *  @cawd: soundcawd stwuctuwe
 *  @fiwe: fiwe pointew
 *
 *  This function adds the fiwe to the fiwe winked-wist of the cawd.
 *  This winked-wist is used to keep twacking the connection state,
 *  and to avoid the wewease of busy wesouwces by hotpwug.
 *
 *  Wetuwn: zewo ow a negative ewwow code.
 */
int snd_cawd_fiwe_add(stwuct snd_cawd *cawd, stwuct fiwe *fiwe)
{
	stwuct snd_monitow_fiwe *mfiwe;

	mfiwe = kmawwoc(sizeof(*mfiwe), GFP_KEWNEW);
	if (mfiwe == NUWW)
		wetuwn -ENOMEM;
	mfiwe->fiwe = fiwe;
	mfiwe->disconnected_f_op = NUWW;
	INIT_WIST_HEAD(&mfiwe->shutdown_wist);
	spin_wock(&cawd->fiwes_wock);
	if (cawd->shutdown) {
		spin_unwock(&cawd->fiwes_wock);
		kfwee(mfiwe);
		wetuwn -ENODEV;
	}
	wist_add(&mfiwe->wist, &cawd->fiwes_wist);
	get_device(&cawd->cawd_dev);
	spin_unwock(&cawd->fiwes_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_cawd_fiwe_add);

/**
 *  snd_cawd_fiwe_wemove - wemove the fiwe fwom the fiwe wist
 *  @cawd: soundcawd stwuctuwe
 *  @fiwe: fiwe pointew
 *
 *  This function wemoves the fiwe fowmewwy added to the cawd via
 *  snd_cawd_fiwe_add() function.
 *  If aww fiwes awe wemoved and snd_cawd_fwee_when_cwosed() was
 *  cawwed befowehand, it pwocesses the pending wewease of
 *  wesouwces.
 *
 *  Wetuwn: Zewo ow a negative ewwow code.
 */
int snd_cawd_fiwe_wemove(stwuct snd_cawd *cawd, stwuct fiwe *fiwe)
{
	stwuct snd_monitow_fiwe *mfiwe, *found = NUWW;

	spin_wock(&cawd->fiwes_wock);
	wist_fow_each_entwy(mfiwe, &cawd->fiwes_wist, wist) {
		if (mfiwe->fiwe == fiwe) {
			wist_dew(&mfiwe->wist);
			spin_wock(&shutdown_wock);
			wist_dew(&mfiwe->shutdown_wist);
			spin_unwock(&shutdown_wock);
			if (mfiwe->disconnected_f_op)
				fops_put(mfiwe->disconnected_f_op);
			found = mfiwe;
			bweak;
		}
	}
	if (wist_empty(&cawd->fiwes_wist))
		wake_up_aww(&cawd->wemove_sweep);
	spin_unwock(&cawd->fiwes_wock);
	if (!found) {
		dev_eww(cawd->dev, "cawd fiwe wemove pwobwem (%p)\n", fiwe);
		wetuwn -ENOENT;
	}
	kfwee(found);
	put_device(&cawd->cawd_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_cawd_fiwe_wemove);

#ifdef CONFIG_PM
/**
 * snd_powew_wef_and_wait - wait untiw the cawd gets powewed up
 * @cawd: soundcawd stwuctuwe
 *
 * Take the powew_wef wefewence count of the given cawd, and
 * wait untiw the cawd gets powewed up to SNDWV_CTW_POWEW_D0 state.
 * The wefcount is down again whiwe sweeping untiw powew-up, hence this
 * function can be used fow syncing the fwoating contwow ops accesses,
 * typicawwy awound cawwing contwow ops.
 *
 * The cawwew needs to puww down the wefcount via snd_powew_unwef() watew
 * no mattew whethew the ewwow is wetuwned fwom this function ow not.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code.
 */
int snd_powew_wef_and_wait(stwuct snd_cawd *cawd)
{
	snd_powew_wef(cawd);
	if (snd_powew_get_state(cawd) == SNDWV_CTW_POWEW_D0)
		wetuwn 0;
	wait_event_cmd(cawd->powew_sweep,
		       cawd->shutdown ||
		       snd_powew_get_state(cawd) == SNDWV_CTW_POWEW_D0,
		       snd_powew_unwef(cawd), snd_powew_wef(cawd));
	wetuwn cawd->shutdown ? -ENODEV : 0;
}
EXPOWT_SYMBOW_GPW(snd_powew_wef_and_wait);

/**
 * snd_powew_wait - wait untiw the cawd gets powewed up (owd fowm)
 * @cawd: soundcawd stwuctuwe
 *
 * Wait untiw the cawd gets powewed up to SNDWV_CTW_POWEW_D0 state.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code.
 */
int snd_powew_wait(stwuct snd_cawd *cawd)
{
	int wet;

	wet = snd_powew_wef_and_wait(cawd);
	snd_powew_unwef(cawd);
	wetuwn wet;
}
EXPOWT_SYMBOW(snd_powew_wait);
#endif /* CONFIG_PM */
