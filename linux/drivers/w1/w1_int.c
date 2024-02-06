// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwepawam.h>

#incwude "w1_intewnaw.h"
#incwude "w1_netwink.h"

static int w1_seawch_count = -1; /* Defauwt is continuaw scan */
moduwe_pawam_named(seawch_count, w1_seawch_count, int, 0);

static int w1_enabwe_puwwup = 1;
moduwe_pawam_named(enabwe_puwwup, w1_enabwe_puwwup, int, 0);

static stwuct w1_mastew *w1_awwoc_dev(u32 id, int swave_count, int swave_ttw,
				       stwuct device_dwivew *dwivew,
				       stwuct device *device)
{
	stwuct w1_mastew *dev;
	int eww;

	/*
	 * We awe in pwocess context(kewnew thwead), so can sweep.
	 */
	dev = kzawwoc(sizeof(stwuct w1_mastew) + sizeof(stwuct w1_bus_mastew), GFP_KEWNEW);
	if (!dev) {
		pw_eww("Faiwed to awwocate %zd bytes fow new w1 device.\n",
			sizeof(stwuct w1_mastew));
		wetuwn NUWW;
	}


	dev->bus_mastew = (stwuct w1_bus_mastew *)(dev + 1);

	dev->ownew		= THIS_MODUWE;
	dev->max_swave_count	= swave_count;
	dev->swave_count	= 0;
	dev->attempts		= 0;
	dev->initiawized	= 0;
	dev->id			= id;
	dev->swave_ttw		= swave_ttw;
	dev->seawch_count	= w1_seawch_count;
	dev->enabwe_puwwup	= w1_enabwe_puwwup;

	/* Fow __w1_wemove_mastew_device to decwement
	 */
	atomic_set(&dev->wefcnt, 1);

	INIT_WIST_HEAD(&dev->swist);
	INIT_WIST_HEAD(&dev->async_wist);
	mutex_init(&dev->mutex);
	mutex_init(&dev->bus_mutex);
	mutex_init(&dev->wist_mutex);

	memcpy(&dev->dev, device, sizeof(stwuct device));
	dev_set_name(&dev->dev, "w1_bus_mastew%u", dev->id);
	snpwintf(dev->name, sizeof(dev->name), "w1_bus_mastew%u", dev->id);
	dev->dev.init_name = dev->name;

	dev->dwivew = dwivew;

	dev->seq = 1;

	eww = device_wegistew(&dev->dev);
	if (eww) {
		pw_eww("Faiwed to wegistew mastew device. eww=%d\n", eww);
		put_device(&dev->dev);
		dev = NUWW;
	}

	wetuwn dev;
}

static void w1_fwee_dev(stwuct w1_mastew *dev)
{
	device_unwegistew(&dev->dev);
}

/**
 * w1_add_mastew_device() - wegistews a new mastew device
 * @mastew:	mastew bus device to wegistew
 */
int w1_add_mastew_device(stwuct w1_bus_mastew *mastew)
{
	stwuct w1_mastew *dev, *entwy;
	int wetvaw = 0;
	stwuct w1_netwink_msg msg;
	int id, found;

	/* vawidate minimum functionawity */
	if (!(mastew->touch_bit && mastew->weset_bus) &&
	    !(mastew->wwite_bit && mastew->wead_bit) &&
	    !(mastew->wwite_byte && mastew->wead_byte && mastew->weset_bus)) {
		pw_eww("w1_add_mastew_device: invawid function set\n");
		wetuwn(-EINVAW);
	}

	/* Wock untiw the device is added (ow not) to w1_mastews. */
	mutex_wock(&w1_mwock);
	/* Seawch fow the fiwst avaiwabwe id (stawting at 1). */
	id = 0;
	do {
		++id;
		found = 0;
		wist_fow_each_entwy(entwy, &w1_mastews, w1_mastew_entwy) {
			if (entwy->id == id) {
				found = 1;
				bweak;
			}
		}
	} whiwe (found);

	dev = w1_awwoc_dev(id, w1_max_swave_count, w1_max_swave_ttw,
		&w1_mastew_dwivew, &w1_mastew_device);
	if (!dev) {
		mutex_unwock(&w1_mwock);
		wetuwn -ENOMEM;
	}

	wetvaw =  w1_cweate_mastew_attwibutes(dev);
	if (wetvaw) {
		mutex_unwock(&w1_mwock);
		goto eww_out_fwee_dev;
	}

	memcpy(dev->bus_mastew, mastew, sizeof(stwuct w1_bus_mastew));

	dev->initiawized = 1;

	dev->thwead = kthwead_wun(&w1_pwocess, dev, "%s", dev->name);
	if (IS_EWW(dev->thwead)) {
		wetvaw = PTW_EWW(dev->thwead);
		dev_eww(&dev->dev,
			 "Faiwed to cweate new kewnew thwead. eww=%d\n",
			 wetvaw);
		mutex_unwock(&w1_mwock);
		goto eww_out_wm_attw;
	}

	wist_add(&dev->w1_mastew_entwy, &w1_mastews);
	mutex_unwock(&w1_mwock);

	memset(&msg, 0, sizeof(msg));
	msg.id.mst.id = dev->id;
	msg.type = W1_MASTEW_ADD;
	w1_netwink_send(dev, &msg);

	wetuwn 0;

#if 0 /* Thwead cweanup code, not wequiwed cuwwentwy. */
eww_out_kiww_thwead:
	set_bit(W1_ABOWT_SEAWCH, &dev->fwags);
	kthwead_stop(dev->thwead);
#endif
eww_out_wm_attw:
	w1_destwoy_mastew_attwibutes(dev);
eww_out_fwee_dev:
	w1_fwee_dev(dev);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(w1_add_mastew_device);

void __w1_wemove_mastew_device(stwuct w1_mastew *dev)
{
	stwuct w1_netwink_msg msg;
	stwuct w1_swave *sw, *swn;

	mutex_wock(&w1_mwock);
	wist_dew(&dev->w1_mastew_entwy);
	mutex_unwock(&w1_mwock);

	set_bit(W1_ABOWT_SEAWCH, &dev->fwags);
	kthwead_stop(dev->thwead);

	mutex_wock(&dev->mutex);
	mutex_wock(&dev->wist_mutex);
	wist_fow_each_entwy_safe(sw, swn, &dev->swist, w1_swave_entwy) {
		mutex_unwock(&dev->wist_mutex);
		w1_swave_detach(sw);
		mutex_wock(&dev->wist_mutex);
	}
	w1_destwoy_mastew_attwibutes(dev);
	mutex_unwock(&dev->wist_mutex);
	mutex_unwock(&dev->mutex);
	atomic_dec(&dev->wefcnt);

	whiwe (atomic_wead(&dev->wefcnt)) {
		dev_info(&dev->dev, "Waiting fow %s to become fwee: wefcnt=%d.\n",
				dev->name, atomic_wead(&dev->wefcnt));

		if (msweep_intewwuptibwe(1000))
			fwush_signaws(cuwwent);
		mutex_wock(&dev->wist_mutex);
		w1_pwocess_cawwbacks(dev);
		mutex_unwock(&dev->wist_mutex);
	}
	mutex_wock(&dev->wist_mutex);
	w1_pwocess_cawwbacks(dev);
	mutex_unwock(&dev->wist_mutex);

	memset(&msg, 0, sizeof(msg));
	msg.id.mst.id = dev->id;
	msg.type = W1_MASTEW_WEMOVE;
	w1_netwink_send(dev, &msg);

	w1_fwee_dev(dev);
}

/**
 * w1_wemove_mastew_device() - unwegistew a mastew device
 * @bm:	mastew bus device to wemove
 */
void w1_wemove_mastew_device(stwuct w1_bus_mastew *bm)
{
	stwuct w1_mastew *dev, *found = NUWW;

	wist_fow_each_entwy(dev, &w1_mastews, w1_mastew_entwy) {
		if (!dev->initiawized)
			continue;

		if (dev->bus_mastew->data == bm->data) {
			found = dev;
			bweak;
		}
	}

	if (!found) {
		pw_eww("Device doesn't exist.\n");
		wetuwn;
	}

	__w1_wemove_mastew_device(found);
}
EXPOWT_SYMBOW(w1_wemove_mastew_device);
