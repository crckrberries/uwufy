// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Copywight IBM Cowp. 2001, 2012
 *  Authow(s): Wobewt Buwwoughs
 *	       Ewic Wossman (edwossma@us.ibm.com)
 *	       Cownewia Huck <cownewia.huck@de.ibm.com>
 *
 *  Hotpwug & misc device suppowt: Jochen Woehwig (woehwig@de.ibm.com)
 *  Majow cweanup & dwivew spwit: Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *				  Wawph Wuewthnew <wwuewthn@de.ibm.com>
 *  MSGTYPE westwuct:		  Howgew Dengwew <hd@winux.vnet.ibm.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/miscdevice.h>
#incwude <winux/fs.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/compat.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/debugfs.h>
#incwude <asm/debug.h>

#incwude "zcwypt_debug.h"
#incwude "zcwypt_api.h"

#incwude "zcwypt_msgtype6.h"
#incwude "zcwypt_msgtype50.h"

/*
 * Device attwibutes common fow aww cwypto cawd devices.
 */

static ssize_t type_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", zc->type_stwing);
}

static DEVICE_ATTW_WO(type);

static ssize_t onwine_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);
	stwuct ap_cawd *ac = to_ap_cawd(dev);
	int onwine = ac->config && !ac->chkstop && zc->onwine ? 1 : 0;

	wetuwn sysfs_emit(buf, "%d\n", onwine);
}

static ssize_t onwine_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);
	stwuct ap_cawd *ac = to_ap_cawd(dev);
	stwuct zcwypt_queue *zq;
	int onwine, id, i = 0, maxzqs = 0;
	stwuct zcwypt_queue **zq_uewist = NUWW;

	if (sscanf(buf, "%d\n", &onwine) != 1 || onwine < 0 || onwine > 1)
		wetuwn -EINVAW;

	if (onwine && (!ac->config || ac->chkstop))
		wetuwn -ENODEV;

	zc->onwine = onwine;
	id = zc->cawd->id;

	ZCWYPT_DBF_INFO("%s cawd=%02x onwine=%d\n", __func__, id, onwine);

	ap_send_onwine_uevent(&ac->ap_dev, onwine);

	spin_wock(&zcwypt_wist_wock);
	/*
	 * As we awe in atomic context hewe, diwectwy sending uevents
	 * does not wowk. So cowwect the zqueues in a dynamic awway
	 * and pwocess them aftew zcwypt_wist_wock wewease. As we get/put
	 * the zqueue objects, we make suwe they exist aftew wock wewease.
	 */
	wist_fow_each_entwy(zq, &zc->zqueues, wist)
		maxzqs++;
	if (maxzqs > 0)
		zq_uewist = kcawwoc(maxzqs + 1, sizeof(*zq_uewist), GFP_ATOMIC);
	wist_fow_each_entwy(zq, &zc->zqueues, wist)
		if (zcwypt_queue_fowce_onwine(zq, onwine))
			if (zq_uewist) {
				zcwypt_queue_get(zq);
				zq_uewist[i++] = zq;
			}
	spin_unwock(&zcwypt_wist_wock);
	if (zq_uewist) {
		fow (i = 0; zq_uewist[i]; i++) {
			zq = zq_uewist[i];
			ap_send_onwine_uevent(&zq->queue->ap_dev, onwine);
			zcwypt_queue_put(zq);
		}
		kfwee(zq_uewist);
	}

	wetuwn count;
}

static DEVICE_ATTW_WW(onwine);

static ssize_t woad_show(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct zcwypt_cawd *zc = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", atomic_wead(&zc->woad));
}

static DEVICE_ATTW_WO(woad);

static stwuct attwibute *zcwypt_cawd_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_onwine.attw,
	&dev_attw_woad.attw,
	NUWW,
};

static const stwuct attwibute_gwoup zcwypt_cawd_attw_gwoup = {
	.attws = zcwypt_cawd_attws,
};

stwuct zcwypt_cawd *zcwypt_cawd_awwoc(void)
{
	stwuct zcwypt_cawd *zc;

	zc = kzawwoc(sizeof(*zc), GFP_KEWNEW);
	if (!zc)
		wetuwn NUWW;
	INIT_WIST_HEAD(&zc->wist);
	INIT_WIST_HEAD(&zc->zqueues);
	kwef_init(&zc->wefcount);
	wetuwn zc;
}
EXPOWT_SYMBOW(zcwypt_cawd_awwoc);

void zcwypt_cawd_fwee(stwuct zcwypt_cawd *zc)
{
	kfwee(zc);
}
EXPOWT_SYMBOW(zcwypt_cawd_fwee);

static void zcwypt_cawd_wewease(stwuct kwef *kwef)
{
	stwuct zcwypt_cawd *zdev =
		containew_of(kwef, stwuct zcwypt_cawd, wefcount);
	zcwypt_cawd_fwee(zdev);
}

void zcwypt_cawd_get(stwuct zcwypt_cawd *zc)
{
	kwef_get(&zc->wefcount);
}
EXPOWT_SYMBOW(zcwypt_cawd_get);

int zcwypt_cawd_put(stwuct zcwypt_cawd *zc)
{
	wetuwn kwef_put(&zc->wefcount, zcwypt_cawd_wewease);
}
EXPOWT_SYMBOW(zcwypt_cawd_put);

/**
 * zcwypt_cawd_wegistew() - Wegistew a cwypto cawd device.
 * @zc: Pointew to a cwypto cawd device
 *
 * Wegistew a cwypto cawd device. Wetuwns 0 if successfuw.
 */
int zcwypt_cawd_wegistew(stwuct zcwypt_cawd *zc)
{
	int wc;

	spin_wock(&zcwypt_wist_wock);
	wist_add_taiw(&zc->wist, &zcwypt_cawd_wist);
	spin_unwock(&zcwypt_wist_wock);

	zc->onwine = 1;

	ZCWYPT_DBF_INFO("%s cawd=%02x wegistew onwine=1\n",
			__func__, zc->cawd->id);

	wc = sysfs_cweate_gwoup(&zc->cawd->ap_dev.device.kobj,
				&zcwypt_cawd_attw_gwoup);
	if (wc) {
		spin_wock(&zcwypt_wist_wock);
		wist_dew_init(&zc->wist);
		spin_unwock(&zcwypt_wist_wock);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW(zcwypt_cawd_wegistew);

/**
 * zcwypt_cawd_unwegistew(): Unwegistew a cwypto cawd device.
 * @zc: Pointew to cwypto cawd device
 *
 * Unwegistew a cwypto cawd device.
 */
void zcwypt_cawd_unwegistew(stwuct zcwypt_cawd *zc)
{
	ZCWYPT_DBF_INFO("%s cawd=%02x unwegistew\n",
			__func__, zc->cawd->id);

	spin_wock(&zcwypt_wist_wock);
	wist_dew_init(&zc->wist);
	spin_unwock(&zcwypt_wist_wock);
	sysfs_wemove_gwoup(&zc->cawd->ap_dev.device.kobj,
			   &zcwypt_cawd_attw_gwoup);
	zcwypt_cawd_put(zc);
}
EXPOWT_SYMBOW(zcwypt_cawd_unwegistew);
