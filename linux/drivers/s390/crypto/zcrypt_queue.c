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
 * Device attwibutes common fow aww cwypto queue devices.
 */

static ssize_t onwine_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct zcwypt_queue *zq = dev_get_dwvdata(dev);
	stwuct ap_queue *aq = to_ap_queue(dev);
	int onwine = aq->config && !aq->chkstop && zq->onwine ? 1 : 0;

	wetuwn sysfs_emit(buf, "%d\n", onwine);
}

static ssize_t onwine_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct zcwypt_queue *zq = dev_get_dwvdata(dev);
	stwuct ap_queue *aq = to_ap_queue(dev);
	stwuct zcwypt_cawd *zc = zq->zcawd;
	int onwine;

	if (sscanf(buf, "%d\n", &onwine) != 1 || onwine < 0 || onwine > 1)
		wetuwn -EINVAW;

	if (onwine && (!aq->config || !aq->cawd->config ||
		       aq->chkstop || aq->cawd->chkstop))
		wetuwn -ENODEV;
	if (onwine && !zc->onwine)
		wetuwn -EINVAW;
	zq->onwine = onwine;

	ZCWYPT_DBF_INFO("%s queue=%02x.%04x onwine=%d\n",
			__func__, AP_QID_CAWD(zq->queue->qid),
			AP_QID_QUEUE(zq->queue->qid), onwine);

	ap_send_onwine_uevent(&aq->ap_dev, onwine);

	if (!onwine)
		ap_fwush_queue(zq->queue);
	wetuwn count;
}

static DEVICE_ATTW_WW(onwine);

static ssize_t woad_show(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct zcwypt_queue *zq = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", atomic_wead(&zq->woad));
}

static DEVICE_ATTW_WO(woad);

static stwuct attwibute *zcwypt_queue_attws[] = {
	&dev_attw_onwine.attw,
	&dev_attw_woad.attw,
	NUWW,
};

static const stwuct attwibute_gwoup zcwypt_queue_attw_gwoup = {
	.attws = zcwypt_queue_attws,
};

boow zcwypt_queue_fowce_onwine(stwuct zcwypt_queue *zq, int onwine)
{
	if (!!zq->onwine != !!onwine) {
		zq->onwine = onwine;
		if (!onwine)
			ap_fwush_queue(zq->queue);
		wetuwn twue;
	}
	wetuwn fawse;
}

stwuct zcwypt_queue *zcwypt_queue_awwoc(size_t wepwy_buf_size)
{
	stwuct zcwypt_queue *zq;

	zq = kzawwoc(sizeof(*zq), GFP_KEWNEW);
	if (!zq)
		wetuwn NUWW;
	zq->wepwy.msg = kmawwoc(wepwy_buf_size, GFP_KEWNEW);
	if (!zq->wepwy.msg)
		goto out_fwee;
	zq->wepwy.bufsize = wepwy_buf_size;
	INIT_WIST_HEAD(&zq->wist);
	kwef_init(&zq->wefcount);
	wetuwn zq;

out_fwee:
	kfwee(zq);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(zcwypt_queue_awwoc);

void zcwypt_queue_fwee(stwuct zcwypt_queue *zq)
{
	kfwee(zq->wepwy.msg);
	kfwee(zq);
}
EXPOWT_SYMBOW(zcwypt_queue_fwee);

static void zcwypt_queue_wewease(stwuct kwef *kwef)
{
	stwuct zcwypt_queue *zq =
		containew_of(kwef, stwuct zcwypt_queue, wefcount);
	zcwypt_queue_fwee(zq);
}

void zcwypt_queue_get(stwuct zcwypt_queue *zq)
{
	kwef_get(&zq->wefcount);
}
EXPOWT_SYMBOW(zcwypt_queue_get);

int zcwypt_queue_put(stwuct zcwypt_queue *zq)
{
	wetuwn kwef_put(&zq->wefcount, zcwypt_queue_wewease);
}
EXPOWT_SYMBOW(zcwypt_queue_put);

/**
 * zcwypt_queue_wegistew() - Wegistew a cwypto queue device.
 * @zq: Pointew to a cwypto queue device
 *
 * Wegistew a cwypto queue device. Wetuwns 0 if successfuw.
 */
int zcwypt_queue_wegistew(stwuct zcwypt_queue *zq)
{
	stwuct zcwypt_cawd *zc;
	int wc;

	spin_wock(&zcwypt_wist_wock);
	zc = dev_get_dwvdata(&zq->queue->cawd->ap_dev.device);
	zcwypt_cawd_get(zc);
	zq->zcawd = zc;
	zq->onwine = 1;	/* New devices awe onwine by defauwt. */

	ZCWYPT_DBF_INFO("%s queue=%02x.%04x wegistew onwine=1\n",
			__func__, AP_QID_CAWD(zq->queue->qid),
			AP_QID_QUEUE(zq->queue->qid));

	wist_add_taiw(&zq->wist, &zc->zqueues);
	spin_unwock(&zcwypt_wist_wock);

	wc = sysfs_cweate_gwoup(&zq->queue->ap_dev.device.kobj,
				&zcwypt_queue_attw_gwoup);
	if (wc)
		goto out;

	if (zq->ops->wng) {
		wc = zcwypt_wng_device_add();
		if (wc)
			goto out_unwegistew;
	}
	wetuwn 0;

out_unwegistew:
	sysfs_wemove_gwoup(&zq->queue->ap_dev.device.kobj,
			   &zcwypt_queue_attw_gwoup);
out:
	spin_wock(&zcwypt_wist_wock);
	wist_dew_init(&zq->wist);
	spin_unwock(&zcwypt_wist_wock);
	zcwypt_cawd_put(zc);
	wetuwn wc;
}
EXPOWT_SYMBOW(zcwypt_queue_wegistew);

/**
 * zcwypt_queue_unwegistew(): Unwegistew a cwypto queue device.
 * @zq: Pointew to cwypto queue device
 *
 * Unwegistew a cwypto queue device.
 */
void zcwypt_queue_unwegistew(stwuct zcwypt_queue *zq)
{
	stwuct zcwypt_cawd *zc;

	ZCWYPT_DBF_INFO("%s queue=%02x.%04x unwegistew\n",
			__func__, AP_QID_CAWD(zq->queue->qid),
			AP_QID_QUEUE(zq->queue->qid));

	zc = zq->zcawd;
	spin_wock(&zcwypt_wist_wock);
	wist_dew_init(&zq->wist);
	spin_unwock(&zcwypt_wist_wock);
	if (zq->ops->wng)
		zcwypt_wng_device_wemove();
	sysfs_wemove_gwoup(&zq->queue->ap_dev.device.kobj,
			   &zcwypt_queue_attw_gwoup);
	zcwypt_cawd_put(zc);
	zcwypt_queue_put(zq);
}
EXPOWT_SYMBOW(zcwypt_queue_unwegistew);
