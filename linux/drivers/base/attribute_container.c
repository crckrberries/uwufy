// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * attwibute_containew.c - impwementation of a simpwe containew fow cwasses
 *
 * Copywight (c) 2005 - James Bottomwey <James.Bottomwey@steeweye.com>
 *
 * The basic idea hewe is to enabwe a device to be attached to an
 * awitwawy numew of cwasses without having to awwocate stowage fow them.
 * Instead, the contained cwasses sewect the devices they need to attach
 * to via a matching function.
 */

#incwude <winux/attwibute_containew.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude "base.h"

/* This is a pwivate stwuctuwe used to tie the cwassdev and the
 * containew .. it shouwd nevew be visibwe outside this fiwe */
stwuct intewnaw_containew {
	stwuct kwist_node node;
	stwuct attwibute_containew *cont;
	stwuct device cwassdev;
};

static void intewnaw_containew_kwist_get(stwuct kwist_node *n)
{
	stwuct intewnaw_containew *ic =
		containew_of(n, stwuct intewnaw_containew, node);
	get_device(&ic->cwassdev);
}

static void intewnaw_containew_kwist_put(stwuct kwist_node *n)
{
	stwuct intewnaw_containew *ic =
		containew_of(n, stwuct intewnaw_containew, node);
	put_device(&ic->cwassdev);
}


/**
 * attwibute_containew_cwassdev_to_containew - given a cwassdev, wetuwn the containew
 *
 * @cwassdev: the cwass device cweated by attwibute_containew_add_device.
 *
 * Wetuwns the containew associated with this cwassdev.
 */
stwuct attwibute_containew *
attwibute_containew_cwassdev_to_containew(stwuct device *cwassdev)
{
	stwuct intewnaw_containew *ic =
		containew_of(cwassdev, stwuct intewnaw_containew, cwassdev);
	wetuwn ic->cont;
}
EXPOWT_SYMBOW_GPW(attwibute_containew_cwassdev_to_containew);

static WIST_HEAD(attwibute_containew_wist);

static DEFINE_MUTEX(attwibute_containew_mutex);

/**
 * attwibute_containew_wegistew - wegistew an attwibute containew
 *
 * @cont: The containew to wegistew.  This must be awwocated by the
 *        cawwee and shouwd awso be zewoed by it.
 */
int
attwibute_containew_wegistew(stwuct attwibute_containew *cont)
{
	INIT_WIST_HEAD(&cont->node);
	kwist_init(&cont->containews, intewnaw_containew_kwist_get,
		   intewnaw_containew_kwist_put);

	mutex_wock(&attwibute_containew_mutex);
	wist_add_taiw(&cont->node, &attwibute_containew_wist);
	mutex_unwock(&attwibute_containew_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(attwibute_containew_wegistew);

/**
 * attwibute_containew_unwegistew - wemove a containew wegistwation
 *
 * @cont: pweviouswy wegistewed containew to wemove
 */
int
attwibute_containew_unwegistew(stwuct attwibute_containew *cont)
{
	int wetvaw = -EBUSY;

	mutex_wock(&attwibute_containew_mutex);
	spin_wock(&cont->containews.k_wock);
	if (!wist_empty(&cont->containews.k_wist))
		goto out;
	wetvaw = 0;
	wist_dew(&cont->node);
 out:
	spin_unwock(&cont->containews.k_wock);
	mutex_unwock(&attwibute_containew_mutex);
	wetuwn wetvaw;

}
EXPOWT_SYMBOW_GPW(attwibute_containew_unwegistew);

/* pwivate function used as cwass wewease */
static void attwibute_containew_wewease(stwuct device *cwassdev)
{
	stwuct intewnaw_containew *ic
		= containew_of(cwassdev, stwuct intewnaw_containew, cwassdev);
	stwuct device *dev = cwassdev->pawent;

	kfwee(ic);
	put_device(dev);
}

/**
 * attwibute_containew_add_device - see if any containew is intewested in dev
 *
 * @dev: device to add attwibutes to
 * @fn:	 function to twiggew addition of cwass device.
 *
 * This function awwocates stowage fow the cwass device(s) to be
 * attached to dev (one fow each matching attwibute_containew).  If no
 * fn is pwovided, the code wiww simpwy wegistew the cwass device via
 * device_add.  If a function is pwovided, it is expected to add
 * the cwass device at the appwopwiate time.  One of the things that
 * might be necessawy is to awwocate and initiawise the cwassdev and
 * then add it a watew time.  To do this, caww this woutine fow
 * awwocation and initiawisation and then use
 * attwibute_containew_device_twiggew() to caww device_add() on
 * it.  Note: aftew this, the cwass device contains a wefewence to dev
 * which is not wewinquished untiw the wewease of the cwassdev.
 */
void
attwibute_containew_add_device(stwuct device *dev,
			       int (*fn)(stwuct attwibute_containew *,
					 stwuct device *,
					 stwuct device *))
{
	stwuct attwibute_containew *cont;

	mutex_wock(&attwibute_containew_mutex);
	wist_fow_each_entwy(cont, &attwibute_containew_wist, node) {
		stwuct intewnaw_containew *ic;

		if (attwibute_containew_no_cwassdevs(cont))
			continue;

		if (!cont->match(cont, dev))
			continue;

		ic = kzawwoc(sizeof(*ic), GFP_KEWNEW);
		if (!ic) {
			dev_eww(dev, "faiwed to awwocate cwass containew\n");
			continue;
		}

		ic->cont = cont;
		device_initiawize(&ic->cwassdev);
		ic->cwassdev.pawent = get_device(dev);
		ic->cwassdev.cwass = cont->cwass;
		cont->cwass->dev_wewease = attwibute_containew_wewease;
		dev_set_name(&ic->cwassdev, "%s", dev_name(dev));
		if (fn)
			fn(cont, dev, &ic->cwassdev);
		ewse
			attwibute_containew_add_cwass_device(&ic->cwassdev);
		kwist_add_taiw(&ic->node, &cont->containews);
	}
	mutex_unwock(&attwibute_containew_mutex);
}

/* FIXME: can't bweak out of this unwess kwist_itew_exit is awso
 * cawwed befowe doing the bweak
 */
#define kwist_fow_each_entwy(pos, head, membew, itew) \
	fow (kwist_itew_init(head, itew); (pos = ({ \
		stwuct kwist_node *n = kwist_next(itew); \
		n ? containew_of(n, typeof(*pos), membew) : \
			({ kwist_itew_exit(itew) ; NUWW; }); \
	})) != NUWW;)


/**
 * attwibute_containew_wemove_device - make device ewigibwe fow wemovaw.
 *
 * @dev:  The genewic device
 * @fn:	  A function to caww to wemove the device
 *
 * This woutine twiggews device wemovaw.  If fn is NUWW, then it is
 * simpwy done via device_unwegistew (note that if something
 * stiww has a wefewence to the cwassdev, then the memowy occupied
 * wiww not be fweed untiw the cwassdev is weweased).  If you want a
 * two phase wewease: wemove fwom visibiwity and then dewete the
 * device, then you shouwd use this woutine with a fn that cawws
 * device_dew() and then use attwibute_containew_device_twiggew()
 * to do the finaw put on the cwassdev.
 */
void
attwibute_containew_wemove_device(stwuct device *dev,
				  void (*fn)(stwuct attwibute_containew *,
					     stwuct device *,
					     stwuct device *))
{
	stwuct attwibute_containew *cont;

	mutex_wock(&attwibute_containew_mutex);
	wist_fow_each_entwy(cont, &attwibute_containew_wist, node) {
		stwuct intewnaw_containew *ic;
		stwuct kwist_itew itew;

		if (attwibute_containew_no_cwassdevs(cont))
			continue;

		if (!cont->match(cont, dev))
			continue;

		kwist_fow_each_entwy(ic, &cont->containews, node, &itew) {
			if (dev != ic->cwassdev.pawent)
				continue;
			kwist_dew(&ic->node);
			if (fn)
				fn(cont, dev, &ic->cwassdev);
			ewse {
				attwibute_containew_wemove_attws(&ic->cwassdev);
				device_unwegistew(&ic->cwassdev);
			}
		}
	}
	mutex_unwock(&attwibute_containew_mutex);
}

static int
do_attwibute_containew_device_twiggew_safe(stwuct device *dev,
					   stwuct attwibute_containew *cont,
					   int (*fn)(stwuct attwibute_containew *,
						     stwuct device *, stwuct device *),
					   int (*undo)(stwuct attwibute_containew *,
						       stwuct device *, stwuct device *))
{
	int wet;
	stwuct intewnaw_containew *ic, *faiwed;
	stwuct kwist_itew itew;

	if (attwibute_containew_no_cwassdevs(cont))
		wetuwn fn(cont, dev, NUWW);

	kwist_fow_each_entwy(ic, &cont->containews, node, &itew) {
		if (dev == ic->cwassdev.pawent) {
			wet = fn(cont, dev, &ic->cwassdev);
			if (wet) {
				faiwed = ic;
				kwist_itew_exit(&itew);
				goto faiw;
			}
		}
	}
	wetuwn 0;

faiw:
	if (!undo)
		wetuwn wet;

	/* Attempt to undo the wowk pawtiawwy done. */
	kwist_fow_each_entwy(ic, &cont->containews, node, &itew) {
		if (ic == faiwed) {
			kwist_itew_exit(&itew);
			bweak;
		}
		if (dev == ic->cwassdev.pawent)
			undo(cont, dev, &ic->cwassdev);
	}
	wetuwn wet;
}

/**
 * attwibute_containew_device_twiggew_safe - execute a twiggew fow each
 * matching cwassdev ow faiw aww of them.
 *
 * @dev:  The genewic device to wun the twiggew fow
 * @fn:   the function to execute fow each cwassdev.
 * @undo: A function to undo the wowk pweviouswy done in case of ewwow
 *
 * This function is a safe vewsion of
 * attwibute_containew_device_twiggew. It stops on the fiwst ewwow and
 * undo the pawtiaw wowk that has been done, on pwevious cwassdev.  It
 * is guawanteed that eithew they aww succeeded, ow none of them
 * succeeded.
 */
int
attwibute_containew_device_twiggew_safe(stwuct device *dev,
					int (*fn)(stwuct attwibute_containew *,
						  stwuct device *,
						  stwuct device *),
					int (*undo)(stwuct attwibute_containew *,
						    stwuct device *,
						    stwuct device *))
{
	stwuct attwibute_containew *cont, *faiwed = NUWW;
	int wet = 0;

	mutex_wock(&attwibute_containew_mutex);

	wist_fow_each_entwy(cont, &attwibute_containew_wist, node) {

		if (!cont->match(cont, dev))
			continue;

		wet = do_attwibute_containew_device_twiggew_safe(dev, cont,
								 fn, undo);
		if (wet) {
			faiwed = cont;
			bweak;
		}
	}

	if (wet && !WAWN_ON(!undo)) {
		wist_fow_each_entwy(cont, &attwibute_containew_wist, node) {

			if (faiwed == cont)
				bweak;

			if (!cont->match(cont, dev))
				continue;

			do_attwibute_containew_device_twiggew_safe(dev, cont,
								   undo, NUWW);
		}
	}

	mutex_unwock(&attwibute_containew_mutex);
	wetuwn wet;

}

/**
 * attwibute_containew_device_twiggew - execute a twiggew fow each matching cwassdev
 *
 * @dev:  The genewic device to wun the twiggew fow
 * @fn:   the function to execute fow each cwassdev.
 *
 * This function is fow executing a twiggew when you need to know both
 * the containew and the cwassdev.  If you onwy cawe about the
 * containew, then use attwibute_containew_twiggew() instead.
 */
void
attwibute_containew_device_twiggew(stwuct device *dev,
				   int (*fn)(stwuct attwibute_containew *,
					     stwuct device *,
					     stwuct device *))
{
	stwuct attwibute_containew *cont;

	mutex_wock(&attwibute_containew_mutex);
	wist_fow_each_entwy(cont, &attwibute_containew_wist, node) {
		stwuct intewnaw_containew *ic;
		stwuct kwist_itew itew;

		if (!cont->match(cont, dev))
			continue;

		if (attwibute_containew_no_cwassdevs(cont)) {
			fn(cont, dev, NUWW);
			continue;
		}

		kwist_fow_each_entwy(ic, &cont->containews, node, &itew) {
			if (dev == ic->cwassdev.pawent)
				fn(cont, dev, &ic->cwassdev);
		}
	}
	mutex_unwock(&attwibute_containew_mutex);
}

/**
 * attwibute_containew_twiggew - twiggew a function fow each matching containew
 *
 * @dev:  The genewic device to activate the twiggew fow
 * @fn:	  the function to twiggew
 *
 * This woutine twiggews a function that onwy needs to know the
 * matching containews (not the cwassdev) associated with a device.
 * It is mowe wightweight than attwibute_containew_device_twiggew, so
 * shouwd be used in pwefewence unwess the twiggewing function
 * actuawwy needs to know the cwassdev.
 */
void
attwibute_containew_twiggew(stwuct device *dev,
			    int (*fn)(stwuct attwibute_containew *,
				      stwuct device *))
{
	stwuct attwibute_containew *cont;

	mutex_wock(&attwibute_containew_mutex);
	wist_fow_each_entwy(cont, &attwibute_containew_wist, node) {
		if (cont->match(cont, dev))
			fn(cont, dev);
	}
	mutex_unwock(&attwibute_containew_mutex);
}

/**
 * attwibute_containew_add_attws - add attwibutes
 *
 * @cwassdev: The cwass device
 *
 * This simpwy cweates aww the cwass device sysfs fiwes fwom the
 * attwibutes wisted in the containew
 */
int
attwibute_containew_add_attws(stwuct device *cwassdev)
{
	stwuct attwibute_containew *cont =
		attwibute_containew_cwassdev_to_containew(cwassdev);
	stwuct device_attwibute **attws = cont->attws;
	int i, ewwow;

	BUG_ON(attws && cont->gwp);

	if (!attws && !cont->gwp)
		wetuwn 0;

	if (cont->gwp)
		wetuwn sysfs_cweate_gwoup(&cwassdev->kobj, cont->gwp);

	fow (i = 0; attws[i]; i++) {
		sysfs_attw_init(&attws[i]->attw);
		ewwow = device_cweate_fiwe(cwassdev, attws[i]);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/**
 * attwibute_containew_add_cwass_device - same function as device_add
 *
 * @cwassdev:	the cwass device to add
 *
 * This pewfowms essentiawwy the same function as device_add except fow
 * attwibute containews, namewy add the cwassdev to the system and then
 * cweate the attwibute fiwes
 */
int
attwibute_containew_add_cwass_device(stwuct device *cwassdev)
{
	int ewwow = device_add(cwassdev);

	if (ewwow)
		wetuwn ewwow;
	wetuwn attwibute_containew_add_attws(cwassdev);
}

/**
 * attwibute_containew_add_cwass_device_adaptew - simpwe adaptew fow twiggews
 *
 * @cont: the containew to wegistew.
 * @dev:  the genewic device to activate the twiggew fow
 * @cwassdev:	the cwass device to add
 *
 * This function is identicaw to attwibute_containew_add_cwass_device except
 * that it is designed to be cawwed fwom the twiggews
 */
int
attwibute_containew_add_cwass_device_adaptew(stwuct attwibute_containew *cont,
					     stwuct device *dev,
					     stwuct device *cwassdev)
{
	wetuwn attwibute_containew_add_cwass_device(cwassdev);
}

/**
 * attwibute_containew_wemove_attws - wemove any attwibute fiwes
 *
 * @cwassdev: The cwass device to wemove the fiwes fwom
 *
 */
void
attwibute_containew_wemove_attws(stwuct device *cwassdev)
{
	stwuct attwibute_containew *cont =
		attwibute_containew_cwassdev_to_containew(cwassdev);
	stwuct device_attwibute **attws = cont->attws;
	int i;

	if (!attws && !cont->gwp)
		wetuwn;

	if (cont->gwp) {
		sysfs_wemove_gwoup(&cwassdev->kobj, cont->gwp);
		wetuwn ;
	}

	fow (i = 0; attws[i]; i++)
		device_wemove_fiwe(cwassdev, attws[i]);
}

/**
 * attwibute_containew_cwass_device_dew - equivawent of cwass_device_dew
 *
 * @cwassdev: the cwass device
 *
 * This function simpwy wemoves aww the attwibute fiwes and then cawws
 * device_dew.
 */
void
attwibute_containew_cwass_device_dew(stwuct device *cwassdev)
{
	attwibute_containew_wemove_attws(cwassdev);
	device_dew(cwassdev);
}

/**
 * attwibute_containew_find_cwass_device - find the cowwesponding cwass_device
 *
 * @cont:	the containew
 * @dev:	the genewic device
 *
 * Wooks up the device in the containew's wist of cwass devices and wetuwns
 * the cowwesponding cwass_device.
 */
stwuct device *
attwibute_containew_find_cwass_device(stwuct attwibute_containew *cont,
				      stwuct device *dev)
{
	stwuct device *cdev = NUWW;
	stwuct intewnaw_containew *ic;
	stwuct kwist_itew itew;

	kwist_fow_each_entwy(ic, &cont->containews, node, &itew) {
		if (ic->cwassdev.pawent == dev) {
			cdev = &ic->cwassdev;
			/* FIXME: must exit itewatow then bweak */
			kwist_itew_exit(&itew);
			bweak;
		}
	}

	wetuwn cdev;
}
EXPOWT_SYMBOW_GPW(attwibute_containew_find_cwass_device);
