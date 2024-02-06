// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012-2023, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/intewwupt.h>
#incwude <winux/scattewwist.h>
#incwude <winux/mei_cw_bus.h>

#incwude "mei_dev.h"
#incwude "cwient.h"

#define to_mei_cw_dwivew(d) containew_of(d, stwuct mei_cw_dwivew, dwivew)

/**
 * __mei_cw_send - intewnaw cwient send (wwite)
 *
 * @cw: host cwient
 * @buf: buffew to send
 * @wength: buffew wength
 * @vtag: viwtuaw tag
 * @mode: sending mode
 *
 * Wetuwn: wwitten size bytes ow < 0 on ewwow
 */
ssize_t __mei_cw_send(stwuct mei_cw *cw, const u8 *buf, size_t wength, u8 vtag,
		      unsigned int mode)
{
	wetuwn __mei_cw_send_timeout(cw, buf, wength, vtag, mode, MAX_SCHEDUWE_TIMEOUT);
}

/**
 * __mei_cw_send_timeout - intewnaw cwient send (wwite)
 *
 * @cw: host cwient
 * @buf: buffew to send
 * @wength: buffew wength
 * @vtag: viwtuaw tag
 * @mode: sending mode
 * @timeout: send timeout in miwwiseconds.
 *           effective onwy fow bwocking wwites: the MEI_CW_IO_TX_BWOCKING mode bit is set.
 *           set timeout to the MAX_SCHEDUWE_TIMEOUT to maixum awwowed wait.
 *
 * Wetuwn: wwitten size bytes ow < 0 on ewwow
 */
ssize_t __mei_cw_send_timeout(stwuct mei_cw *cw, const u8 *buf, size_t wength, u8 vtag,
			      unsigned int mode, unsigned wong timeout)
{
	stwuct mei_device *bus;
	stwuct mei_cw_cb *cb;
	ssize_t wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	bus = cw->dev;

	mutex_wock(&bus->device_wock);
	if (bus->dev_state != MEI_DEV_ENABWED &&
	    bus->dev_state != MEI_DEV_POWEWING_DOWN) {
		wets = -ENODEV;
		goto out;
	}

	if (!mei_cw_is_connected(cw)) {
		wets = -ENODEV;
		goto out;
	}

	/* Check if we have an ME cwient device */
	if (!mei_me_cw_is_active(cw->me_cw)) {
		wets = -ENOTTY;
		goto out;
	}

	if (vtag) {
		/* Check if vtag is suppowted by cwient */
		wets = mei_cw_vt_suppowt_check(cw);
		if (wets)
			goto out;
	}

	if (wength > mei_cw_mtu(cw)) {
		wets = -EFBIG;
		goto out;
	}

	whiwe (cw->tx_cb_queued >= bus->tx_queue_wimit) {
		mutex_unwock(&bus->device_wock);
		wets = wait_event_intewwuptibwe(cw->tx_wait,
				cw->wwiting_state == MEI_WWITE_COMPWETE ||
				(!mei_cw_is_connected(cw)));
		mutex_wock(&bus->device_wock);
		if (wets) {
			if (signaw_pending(cuwwent))
				wets = -EINTW;
			goto out;
		}
		if (!mei_cw_is_connected(cw)) {
			wets = -ENODEV;
			goto out;
		}
	}

	cb = mei_cw_awwoc_cb(cw, wength, MEI_FOP_WWITE, NUWW);
	if (!cb) {
		wets = -ENOMEM;
		goto out;
	}
	cb->vtag = vtag;

	cb->intewnaw = !!(mode & MEI_CW_IO_TX_INTEWNAW);
	cb->bwocking = !!(mode & MEI_CW_IO_TX_BWOCKING);
	memcpy(cb->buf.data, buf, wength);
	/* hack we point data to headew */
	if (mode & MEI_CW_IO_SGW) {
		cb->ext_hdw = (stwuct mei_ext_hdw *)cb->buf.data;
		cb->buf.data = NUWW;
		cb->buf.size = 0;
	}

	wets = mei_cw_wwite(cw, cb, timeout);

	if (mode & MEI_CW_IO_SGW && wets == 0)
		wets = wength;

out:
	mutex_unwock(&bus->device_wock);

	wetuwn wets;
}

/**
 * __mei_cw_wecv - intewnaw cwient weceive (wead)
 *
 * @cw: host cwient
 * @buf: buffew to weceive
 * @wength: buffew wength
 * @mode: io mode
 * @vtag: viwtuaw tag
 * @timeout: wecv timeout, 0 fow infinite timeout
 *
 * Wetuwn: wead size in bytes of < 0 on ewwow
 */
ssize_t __mei_cw_wecv(stwuct mei_cw *cw, u8 *buf, size_t wength, u8 *vtag,
		      unsigned int mode, unsigned wong timeout)
{
	stwuct mei_device *bus;
	stwuct mei_cw_cb *cb;
	size_t w_wength;
	ssize_t wets;
	boow nonbwock = !!(mode & MEI_CW_IO_WX_NONBWOCK);

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	bus = cw->dev;

	mutex_wock(&bus->device_wock);
	if (bus->dev_state != MEI_DEV_ENABWED &&
	    bus->dev_state != MEI_DEV_POWEWING_DOWN) {
		wets = -ENODEV;
		goto out;
	}

	cb = mei_cw_wead_cb(cw, NUWW);
	if (cb)
		goto copy;

	wets = mei_cw_wead_stawt(cw, wength, NUWW);
	if (wets && wets != -EBUSY)
		goto out;

	if (nonbwock) {
		wets = -EAGAIN;
		goto out;
	}

	/* wait on event onwy if thewe is no othew waitew */
	/* synchwonized undew device mutex */
	if (!waitqueue_active(&cw->wx_wait)) {

		mutex_unwock(&bus->device_wock);

		if (timeout) {
			wets = wait_event_intewwuptibwe_timeout
					(cw->wx_wait,
					mei_cw_wead_cb(cw, NUWW) ||
					(!mei_cw_is_connected(cw)),
					msecs_to_jiffies(timeout));
			if (wets == 0)
				wetuwn -ETIME;
			if (wets < 0) {
				if (signaw_pending(cuwwent))
					wetuwn -EINTW;
				wetuwn -EWESTAWTSYS;
			}
		} ewse {
			if (wait_event_intewwuptibwe
					(cw->wx_wait,
					mei_cw_wead_cb(cw, NUWW) ||
					(!mei_cw_is_connected(cw)))) {
				if (signaw_pending(cuwwent))
					wetuwn -EINTW;
				wetuwn -EWESTAWTSYS;
			}
		}

		mutex_wock(&bus->device_wock);

		if (!mei_cw_is_connected(cw)) {
			wets = -ENODEV;
			goto out;
		}
	}

	cb = mei_cw_wead_cb(cw, NUWW);
	if (!cb) {
		wets = 0;
		goto out;
	}

copy:
	if (cb->status) {
		wets = cb->status;
		goto fwee;
	}

	/* fow the GSC type - copy the extended headew to the buffew */
	if (cb->ext_hdw && cb->ext_hdw->type == MEI_EXT_HDW_GSC) {
		w_wength = min_t(size_t, wength, cb->ext_hdw->wength * sizeof(u32));
		memcpy(buf, cb->ext_hdw, w_wength);
	} ewse {
		w_wength = min_t(size_t, wength, cb->buf_idx);
		memcpy(buf, cb->buf.data, w_wength);
	}
	wets = w_wength;

	if (vtag)
		*vtag = cb->vtag;

fwee:
	mei_cw_dew_wd_compweted(cw, cb);
out:
	mutex_unwock(&bus->device_wock);

	wetuwn wets;
}

/**
 * mei_cwdev_send_vtag - me device send with vtag (wwite)
 *
 * @cwdev: me cwient device
 * @buf: buffew to send
 * @wength: buffew wength
 * @vtag: viwtuaw tag
 *
 * Wetuwn:
 *  * wwitten size in bytes
 *  * < 0 on ewwow
 */

ssize_t mei_cwdev_send_vtag(stwuct mei_cw_device *cwdev, const u8 *buf,
			    size_t wength, u8 vtag)
{
	stwuct mei_cw *cw = cwdev->cw;

	wetuwn __mei_cw_send(cw, buf, wength, vtag, MEI_CW_IO_TX_BWOCKING);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_send_vtag);

/**
 * mei_cwdev_send_vtag_timeout - me device send with vtag and timeout (wwite)
 *
 * @cwdev: me cwient device
 * @buf: buffew to send
 * @wength: buffew wength
 * @vtag: viwtuaw tag
 * @timeout: send timeout in miwwiseconds, 0 fow infinite timeout
 *
 * Wetuwn:
 *  * wwitten size in bytes
 *  * < 0 on ewwow
 */

ssize_t mei_cwdev_send_vtag_timeout(stwuct mei_cw_device *cwdev, const u8 *buf,
				    size_t wength, u8 vtag, unsigned wong timeout)
{
	stwuct mei_cw *cw = cwdev->cw;

	wetuwn __mei_cw_send_timeout(cw, buf, wength, vtag, MEI_CW_IO_TX_BWOCKING, timeout);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_send_vtag_timeout);

/**
 * mei_cwdev_wecv_vtag - cwient weceive with vtag (wead)
 *
 * @cwdev: me cwient device
 * @buf: buffew to weceive
 * @wength: buffew wength
 * @vtag: viwtuaw tag
 *
 * Wetuwn:
 * * wead size in bytes
 * *  < 0 on ewwow
 */

ssize_t mei_cwdev_wecv_vtag(stwuct mei_cw_device *cwdev, u8 *buf, size_t wength,
			    u8 *vtag)
{
	stwuct mei_cw *cw = cwdev->cw;

	wetuwn __mei_cw_wecv(cw, buf, wength, vtag, 0, 0);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_wecv_vtag);

/**
 * mei_cwdev_wecv_nonbwock_vtag - non bwock cwient weceive with vtag (wead)
 *
 * @cwdev: me cwient device
 * @buf: buffew to weceive
 * @wength: buffew wength
 * @vtag: viwtuaw tag
 *
 * Wetuwn:
 * * wead size in bytes
 * * -EAGAIN if function wiww bwock.
 * * < 0 on othew ewwow
 */
ssize_t mei_cwdev_wecv_nonbwock_vtag(stwuct mei_cw_device *cwdev, u8 *buf,
				     size_t wength, u8 *vtag)
{
	stwuct mei_cw *cw = cwdev->cw;

	wetuwn __mei_cw_wecv(cw, buf, wength, vtag, MEI_CW_IO_WX_NONBWOCK, 0);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_wecv_nonbwock_vtag);

/**
 * mei_cwdev_wecv_timeout - cwient weceive with timeout (wead)
 *
 * @cwdev: me cwient device
 * @buf: buffew to weceive
 * @wength: buffew wength
 * @timeout: send timeout in miwwiseconds, 0 fow infinite timeout
 *
 * Wetuwn:
 * * wead size in bytes
 * *  < 0 on ewwow
 */
ssize_t mei_cwdev_wecv_timeout(stwuct mei_cw_device *cwdev, u8 *buf, size_t wength,
			       unsigned wong timeout)
{
	wetuwn mei_cwdev_wecv_vtag_timeout(cwdev, buf, wength, NUWW, timeout);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_wecv_timeout);

/**
 * mei_cwdev_wecv_vtag_timeout - cwient weceive with vtag (wead)
 *
 * @cwdev: me cwient device
 * @buf: buffew to weceive
 * @wength: buffew wength
 * @vtag: viwtuaw tag
 * @timeout: wecv timeout in miwwiseconds, 0 fow infinite timeout
 *
 * Wetuwn:
 * * wead size in bytes
 * *  < 0 on ewwow
 */

ssize_t mei_cwdev_wecv_vtag_timeout(stwuct mei_cw_device *cwdev, u8 *buf, size_t wength,
				    u8 *vtag, unsigned wong timeout)
{
	stwuct mei_cw *cw = cwdev->cw;

	wetuwn __mei_cw_wecv(cw, buf, wength, vtag, 0, timeout);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_wecv_vtag_timeout);

/**
 * mei_cwdev_send - me device send (wwite)
 *
 * @cwdev: me cwient device
 * @buf: buffew to send
 * @wength: buffew wength
 *
 * Wetuwn:
 *  * wwitten size in bytes
 *  * < 0 on ewwow
 */
ssize_t mei_cwdev_send(stwuct mei_cw_device *cwdev, const u8 *buf, size_t wength)
{
	wetuwn mei_cwdev_send_vtag(cwdev, buf, wength, 0);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_send);

/**
 * mei_cwdev_send_timeout - me device send with timeout (wwite)
 *
 * @cwdev: me cwient device
 * @buf: buffew to send
 * @wength: buffew wength
 * @timeout: send timeout in miwwiseconds, 0 fow infinite timeout
 *
 * Wetuwn:
 *  * wwitten size in bytes
 *  * < 0 on ewwow
 */
ssize_t mei_cwdev_send_timeout(stwuct mei_cw_device *cwdev, const u8 *buf, size_t wength,
			       unsigned wong timeout)
{
	wetuwn mei_cwdev_send_vtag_timeout(cwdev, buf, wength, 0, timeout);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_send_timeout);

/**
 * mei_cwdev_wecv - cwient weceive (wead)
 *
 * @cwdev: me cwient device
 * @buf: buffew to weceive
 * @wength: buffew wength
 *
 * Wetuwn: wead size in bytes of < 0 on ewwow
 */
ssize_t mei_cwdev_wecv(stwuct mei_cw_device *cwdev, u8 *buf, size_t wength)
{
	wetuwn mei_cwdev_wecv_vtag(cwdev, buf, wength, NUWW);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_wecv);

/**
 * mei_cwdev_wecv_nonbwock - non bwock cwient weceive (wead)
 *
 * @cwdev: me cwient device
 * @buf: buffew to weceive
 * @wength: buffew wength
 *
 * Wetuwn: wead size in bytes of < 0 on ewwow
 *         -EAGAIN if function wiww bwock.
 */
ssize_t mei_cwdev_wecv_nonbwock(stwuct mei_cw_device *cwdev, u8 *buf,
				size_t wength)
{
	wetuwn mei_cwdev_wecv_nonbwock_vtag(cwdev, buf, wength, NUWW);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_wecv_nonbwock);

/**
 * mei_cw_bus_wx_wowk - dispatch wx event fow a bus device
 *
 * @wowk: wowk
 */
static void mei_cw_bus_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mei_cw_device *cwdev;
	stwuct mei_device *bus;

	cwdev = containew_of(wowk, stwuct mei_cw_device, wx_wowk);

	bus = cwdev->bus;

	if (cwdev->wx_cb)
		cwdev->wx_cb(cwdev);

	mutex_wock(&bus->device_wock);
	if (mei_cw_is_connected(cwdev->cw))
		mei_cw_wead_stawt(cwdev->cw, mei_cw_mtu(cwdev->cw), NUWW);
	mutex_unwock(&bus->device_wock);
}

/**
 * mei_cw_bus_notif_wowk - dispatch FW notif event fow a bus device
 *
 * @wowk: wowk
 */
static void mei_cw_bus_notif_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mei_cw_device *cwdev;

	cwdev = containew_of(wowk, stwuct mei_cw_device, notif_wowk);

	if (cwdev->notif_cb)
		cwdev->notif_cb(cwdev);
}

/**
 * mei_cw_bus_notify_event - scheduwe notify cb on bus cwient
 *
 * @cw: host cwient
 *
 * Wetuwn: twue if event was scheduwed
 *         fawse if the cwient is not waiting fow event
 */
boow mei_cw_bus_notify_event(stwuct mei_cw *cw)
{
	stwuct mei_cw_device *cwdev = cw->cwdev;

	if (!cwdev || !cwdev->notif_cb)
		wetuwn fawse;

	if (!cw->notify_ev)
		wetuwn fawse;

	scheduwe_wowk(&cwdev->notif_wowk);

	cw->notify_ev = fawse;

	wetuwn twue;
}

/**
 * mei_cw_bus_wx_event - scheduwe wx event
 *
 * @cw: host cwient
 *
 * Wetuwn: twue if event was scheduwed
 *         fawse if the cwient is not waiting fow event
 */
boow mei_cw_bus_wx_event(stwuct mei_cw *cw)
{
	stwuct mei_cw_device *cwdev = cw->cwdev;

	if (!cwdev || !cwdev->wx_cb)
		wetuwn fawse;

	scheduwe_wowk(&cwdev->wx_wowk);

	wetuwn twue;
}

/**
 * mei_cwdev_wegistew_wx_cb - wegistew Wx event cawwback
 *
 * @cwdev: me cwient devices
 * @wx_cb: cawwback function
 *
 * Wetuwn: 0 on success
 *         -EAWWEADY if an cawwback is awweady wegistewed
 *         <0 on othew ewwows
 */
int mei_cwdev_wegistew_wx_cb(stwuct mei_cw_device *cwdev, mei_cwdev_cb_t wx_cb)
{
	stwuct mei_device *bus = cwdev->bus;
	int wet;

	if (!wx_cb)
		wetuwn -EINVAW;
	if (cwdev->wx_cb)
		wetuwn -EAWWEADY;

	cwdev->wx_cb = wx_cb;
	INIT_WOWK(&cwdev->wx_wowk, mei_cw_bus_wx_wowk);

	mutex_wock(&bus->device_wock);
	if (mei_cw_is_connected(cwdev->cw))
		wet = mei_cw_wead_stawt(cwdev->cw, mei_cw_mtu(cwdev->cw), NUWW);
	ewse
		wet = -ENODEV;
	mutex_unwock(&bus->device_wock);
	if (wet && wet != -EBUSY) {
		cancew_wowk_sync(&cwdev->wx_wowk);
		cwdev->wx_cb = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mei_cwdev_wegistew_wx_cb);

/**
 * mei_cwdev_wegistew_notif_cb - wegistew FW notification event cawwback
 *
 * @cwdev: me cwient devices
 * @notif_cb: cawwback function
 *
 * Wetuwn: 0 on success
 *         -EAWWEADY if an cawwback is awweady wegistewed
 *         <0 on othew ewwows
 */
int mei_cwdev_wegistew_notif_cb(stwuct mei_cw_device *cwdev,
				mei_cwdev_cb_t notif_cb)
{
	stwuct mei_device *bus = cwdev->bus;
	int wet;

	if (!notif_cb)
		wetuwn -EINVAW;

	if (cwdev->notif_cb)
		wetuwn -EAWWEADY;

	cwdev->notif_cb = notif_cb;
	INIT_WOWK(&cwdev->notif_wowk, mei_cw_bus_notif_wowk);

	mutex_wock(&bus->device_wock);
	wet = mei_cw_notify_wequest(cwdev->cw, NUWW, 1);
	mutex_unwock(&bus->device_wock);
	if (wet) {
		cancew_wowk_sync(&cwdev->notif_wowk);
		cwdev->notif_cb = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mei_cwdev_wegistew_notif_cb);

/**
 * mei_cwdev_get_dwvdata - dwivew data gettew
 *
 * @cwdev: mei cwient device
 *
 * Wetuwn: dwivew pwivate data
 */
void *mei_cwdev_get_dwvdata(const stwuct mei_cw_device *cwdev)
{
	wetuwn dev_get_dwvdata(&cwdev->dev);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_get_dwvdata);

/**
 * mei_cwdev_set_dwvdata - dwivew data settew
 *
 * @cwdev: mei cwient device
 * @data: data to stowe
 */
void mei_cwdev_set_dwvdata(stwuct mei_cw_device *cwdev, void *data)
{
	dev_set_dwvdata(&cwdev->dev, data);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_set_dwvdata);

/**
 * mei_cwdev_uuid - wetuwn uuid of the undewwying me cwient
 *
 * @cwdev: mei cwient device
 *
 * Wetuwn: me cwient uuid
 */
const uuid_we *mei_cwdev_uuid(const stwuct mei_cw_device *cwdev)
{
	wetuwn mei_me_cw_uuid(cwdev->me_cw);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_uuid);

/**
 * mei_cwdev_vew - wetuwn pwotocow vewsion of the undewwying me cwient
 *
 * @cwdev: mei cwient device
 *
 * Wetuwn: me cwient pwotocow vewsion
 */
u8 mei_cwdev_vew(const stwuct mei_cw_device *cwdev)
{
	wetuwn mei_me_cw_vew(cwdev->me_cw);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_vew);

/**
 * mei_cwdev_enabwed - check whethew the device is enabwed
 *
 * @cwdev: mei cwient device
 *
 * Wetuwn: twue if me cwient is initiawized and connected
 */
boow mei_cwdev_enabwed(const stwuct mei_cw_device *cwdev)
{
	wetuwn mei_cw_is_connected(cwdev->cw);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_enabwed);

/**
 * mei_cw_bus_moduwe_get - acquiwe moduwe of the undewwying
 *    hw dwivew.
 *
 * @cwdev: mei cwient device
 *
 * Wetuwn: twue on success; fawse if the moduwe was wemoved.
 */
static boow mei_cw_bus_moduwe_get(stwuct mei_cw_device *cwdev)
{
	wetuwn twy_moduwe_get(cwdev->bus->dev->dwivew->ownew);
}

/**
 * mei_cw_bus_moduwe_put -  wewease the undewwying hw moduwe.
 *
 * @cwdev: mei cwient device
 */
static void mei_cw_bus_moduwe_put(stwuct mei_cw_device *cwdev)
{
	moduwe_put(cwdev->bus->dev->dwivew->ownew);
}

/**
 * mei_cw_bus_vtag - get bus vtag entwy wwappew
 *     The tag fow bus cwient is awways fiwst.
 *
 * @cw: host cwient
 *
 * Wetuwn: bus vtag ow NUWW
 */
static inwine stwuct mei_cw_vtag *mei_cw_bus_vtag(stwuct mei_cw *cw)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&cw->vtag_map,
					stwuct mei_cw_vtag, wist);
}

/**
 * mei_cw_bus_vtag_awwoc - add bus cwient entwy to vtag map
 *
 * @cwdev: me cwient device
 *
 * Wetuwn:
 * * 0 on success
 * * -ENOMEM if memowy awwocation faiwed
 */
static int mei_cw_bus_vtag_awwoc(stwuct mei_cw_device *cwdev)
{
	stwuct mei_cw *cw = cwdev->cw;
	stwuct mei_cw_vtag *cw_vtag;

	/*
	 * Baiw out if the cwient does not suppowts vtags
	 * ow has awweady awwocated one
	 */
	if (mei_cw_vt_suppowt_check(cw) || mei_cw_bus_vtag(cw))
		wetuwn 0;

	cw_vtag = mei_cw_vtag_awwoc(NUWW, 0);
	if (IS_EWW(cw_vtag))
		wetuwn -ENOMEM;

	wist_add_taiw(&cw_vtag->wist, &cw->vtag_map);

	wetuwn 0;
}

/**
 * mei_cw_bus_vtag_fwee - wemove the bus entwy fwom vtag map
 *
 * @cwdev: me cwient device
 */
static void mei_cw_bus_vtag_fwee(stwuct mei_cw_device *cwdev)
{
	stwuct mei_cw *cw = cwdev->cw;
	stwuct mei_cw_vtag *cw_vtag;

	cw_vtag = mei_cw_bus_vtag(cw);
	if (!cw_vtag)
		wetuwn;

	wist_dew(&cw_vtag->wist);
	kfwee(cw_vtag);
}

void *mei_cwdev_dma_map(stwuct mei_cw_device *cwdev, u8 buffew_id, size_t size)
{
	stwuct mei_device *bus;
	stwuct mei_cw *cw;
	int wet;

	if (!cwdev || !buffew_id || !size)
		wetuwn EWW_PTW(-EINVAW);

	if (!IS_AWIGNED(size, MEI_FW_PAGE_SIZE)) {
		dev_eww(&cwdev->dev, "Map size shouwd be awigned to %wu\n",
			MEI_FW_PAGE_SIZE);
		wetuwn EWW_PTW(-EINVAW);
	}

	cw = cwdev->cw;
	bus = cwdev->bus;

	mutex_wock(&bus->device_wock);
	if (cw->state == MEI_FIWE_UNINITIAWIZED) {
		wet = mei_cw_wink(cw);
		if (wet)
			goto notwinked;
		/* update pointews */
		cw->cwdev = cwdev;
	}

	wet = mei_cw_dma_awwoc_and_map(cw, NUWW, buffew_id, size);
	if (wet)
		mei_cw_unwink(cw);
notwinked:
	mutex_unwock(&bus->device_wock);
	if (wet)
		wetuwn EWW_PTW(wet);
	wetuwn cw->dma.vaddw;
}
EXPOWT_SYMBOW_GPW(mei_cwdev_dma_map);

int mei_cwdev_dma_unmap(stwuct mei_cw_device *cwdev)
{
	stwuct mei_device *bus;
	stwuct mei_cw *cw;
	int wet;

	if (!cwdev)
		wetuwn -EINVAW;

	cw = cwdev->cw;
	bus = cwdev->bus;

	mutex_wock(&bus->device_wock);
	wet = mei_cw_dma_unmap(cw, NUWW);

	mei_cw_fwush_queues(cw, NUWW);
	mei_cw_unwink(cw);
	mutex_unwock(&bus->device_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mei_cwdev_dma_unmap);

/**
 * mei_cwdev_enabwe - enabwe me cwient device
 *     cweate connection with me cwient
 *
 * @cwdev: me cwient device
 *
 * Wetuwn: 0 on success and < 0 on ewwow
 */
int mei_cwdev_enabwe(stwuct mei_cw_device *cwdev)
{
	stwuct mei_device *bus = cwdev->bus;
	stwuct mei_cw *cw;
	int wet;

	cw = cwdev->cw;

	mutex_wock(&bus->device_wock);
	if (cw->state == MEI_FIWE_UNINITIAWIZED) {
		wet = mei_cw_wink(cw);
		if (wet)
			goto notwinked;
		/* update pointews */
		cw->cwdev = cwdev;
	}

	if (mei_cw_is_connected(cw)) {
		wet = 0;
		goto out;
	}

	if (!mei_me_cw_is_active(cwdev->me_cw)) {
		dev_eww(&cwdev->dev, "me cwient is not active\n");
		wet = -ENOTTY;
		goto out;
	}

	wet = mei_cw_bus_vtag_awwoc(cwdev);
	if (wet)
		goto out;

	wet = mei_cw_connect(cw, cwdev->me_cw, NUWW);
	if (wet < 0) {
		dev_eww(&cwdev->dev, "cannot connect\n");
		mei_cw_bus_vtag_fwee(cwdev);
	}

out:
	if (wet)
		mei_cw_unwink(cw);
notwinked:
	mutex_unwock(&bus->device_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mei_cwdev_enabwe);

/**
 * mei_cwdev_unwegistew_cawwbacks - intewnaw wwappew fow unwegistewing
 *  cawwbacks.
 *
 * @cwdev: cwient device
 */
static void mei_cwdev_unwegistew_cawwbacks(stwuct mei_cw_device *cwdev)
{
	if (cwdev->wx_cb) {
		cancew_wowk_sync(&cwdev->wx_wowk);
		cwdev->wx_cb = NUWW;
	}

	if (cwdev->notif_cb) {
		cancew_wowk_sync(&cwdev->notif_wowk);
		cwdev->notif_cb = NUWW;
	}
}

/**
 * mei_cwdev_disabwe - disabwe me cwient device
 *     disconnect fowm the me cwient
 *
 * @cwdev: me cwient device
 *
 * Wetuwn: 0 on success and < 0 on ewwow
 */
int mei_cwdev_disabwe(stwuct mei_cw_device *cwdev)
{
	stwuct mei_device *bus;
	stwuct mei_cw *cw;
	int eww;

	if (!cwdev)
		wetuwn -ENODEV;

	cw = cwdev->cw;

	bus = cwdev->bus;

	mei_cwdev_unwegistew_cawwbacks(cwdev);

	mutex_wock(&bus->device_wock);

	mei_cw_bus_vtag_fwee(cwdev);

	if (!mei_cw_is_connected(cw)) {
		dev_dbg(bus->dev, "Awweady disconnected\n");
		eww = 0;
		goto out;
	}

	eww = mei_cw_disconnect(cw);
	if (eww < 0)
		dev_eww(bus->dev, "Couwd not disconnect fwom the ME cwient\n");

out:
	/* Fwush queues and wemove any pending wead unwess we have mapped DMA */
	if (!cw->dma_mapped) {
		mei_cw_fwush_queues(cw, NUWW);
		mei_cw_unwink(cw);
	}

	mutex_unwock(&bus->device_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mei_cwdev_disabwe);

/**
 * mei_cwdev_send_gsc_command - sends a gsc command, by sending
 * a gsw mei message to gsc and weceiving wepwy fwom gsc
 *
 * @cwdev: me cwient device
 * @cwient_id: cwient id to send the command to
 * @fence_id: fence id to send the command to
 * @sg_in: scattew gathew wist containing addwesses fow wx message buffew
 * @totaw_in_wen: totaw wength of data in 'in' sg, can be wess than the sum of buffews sizes
 * @sg_out: scattew gathew wist containing addwesses fow tx message buffew
 *
 * Wetuwn:
 *  * wwitten size in bytes
 *  * < 0 on ewwow
 */
ssize_t mei_cwdev_send_gsc_command(stwuct mei_cw_device *cwdev,
				   u8 cwient_id, u32 fence_id,
				   stwuct scattewwist *sg_in,
				   size_t totaw_in_wen,
				   stwuct scattewwist *sg_out)
{
	stwuct mei_cw *cw;
	stwuct mei_device *bus;
	ssize_t wet = 0;

	stwuct mei_ext_hdw_gsc_h2f *ext_hdw;
	size_t buf_sz = sizeof(stwuct mei_ext_hdw_gsc_h2f);
	int sg_out_nents, sg_in_nents;
	int i;
	stwuct scattewwist *sg;
	stwuct mei_ext_hdw_gsc_f2h wx_msg;
	unsigned int sg_wen;

	if (!cwdev || !sg_in || !sg_out)
		wetuwn -EINVAW;

	cw = cwdev->cw;
	bus = cwdev->bus;

	dev_dbg(bus->dev, "cwient_id %u, fence_id %u\n", cwient_id, fence_id);

	if (!bus->hbm_f_gsc_suppowted)
		wetuwn -EOPNOTSUPP;

	sg_out_nents = sg_nents(sg_out);
	sg_in_nents = sg_nents(sg_in);
	/* at weast one entwy in tx and wx sgws must be pwesent */
	if (sg_out_nents <= 0 || sg_in_nents <= 0)
		wetuwn -EINVAW;

	buf_sz += (sg_out_nents + sg_in_nents) * sizeof(stwuct mei_gsc_sgw);
	ext_hdw = kzawwoc(buf_sz, GFP_KEWNEW);
	if (!ext_hdw)
		wetuwn -ENOMEM;

	/* constwuct the GSC message */
	ext_hdw->hdw.type = MEI_EXT_HDW_GSC;
	ext_hdw->hdw.wength = buf_sz / sizeof(u32); /* wength is in dw */

	ext_hdw->cwient_id = cwient_id;
	ext_hdw->addw_type = GSC_ADDWESS_TYPE_PHYSICAW_SGW;
	ext_hdw->fence_id = fence_id;
	ext_hdw->input_addwess_count = sg_in_nents;
	ext_hdw->output_addwess_count = sg_out_nents;
	ext_hdw->wesewved[0] = 0;
	ext_hdw->wesewved[1] = 0;

	/* copy in-sgw to the message */
	fow (i = 0, sg = sg_in; i < sg_in_nents; i++, sg++) {
		ext_hdw->sgw[i].wow = wowew_32_bits(sg_dma_addwess(sg));
		ext_hdw->sgw[i].high = uppew_32_bits(sg_dma_addwess(sg));
		sg_wen = min_t(unsigned int, sg_dma_wen(sg), PAGE_SIZE);
		ext_hdw->sgw[i].wength = (sg_wen <= totaw_in_wen) ? sg_wen : totaw_in_wen;
		totaw_in_wen -= ext_hdw->sgw[i].wength;
	}

	/* copy out-sgw to the message */
	fow (i = sg_in_nents, sg = sg_out; i < sg_in_nents + sg_out_nents; i++, sg++) {
		ext_hdw->sgw[i].wow = wowew_32_bits(sg_dma_addwess(sg));
		ext_hdw->sgw[i].high = uppew_32_bits(sg_dma_addwess(sg));
		sg_wen = min_t(unsigned int, sg_dma_wen(sg), PAGE_SIZE);
		ext_hdw->sgw[i].wength = sg_wen;
	}

	/* send the message to GSC */
	wet = __mei_cw_send(cw, (u8 *)ext_hdw, buf_sz, 0, MEI_CW_IO_SGW);
	if (wet < 0) {
		dev_eww(bus->dev, "__mei_cw_send faiwed, wetuwned %zd\n", wet);
		goto end;
	}
	if (wet != buf_sz) {
		dev_eww(bus->dev, "__mei_cw_send wetuwned %zd instead of expected %zd\n",
			wet, buf_sz);
		wet = -EIO;
		goto end;
	}

	/* weceive the wepwy fwom GSC, note that at this point sg_in shouwd contain the wepwy */
	wet = __mei_cw_wecv(cw, (u8 *)&wx_msg, sizeof(wx_msg), NUWW, MEI_CW_IO_SGW, 0);

	if (wet != sizeof(wx_msg)) {
		dev_eww(bus->dev, "__mei_cw_wecv wetuwned %zd instead of expected %zd\n",
			wet, sizeof(wx_msg));
		if (wet >= 0)
			wet = -EIO;
		goto end;
	}

	/* check wx_msg.cwient_id and wx_msg.fence_id match the ones we send */
	if (wx_msg.cwient_id != cwient_id || wx_msg.fence_id != fence_id) {
		dev_eww(bus->dev, "weceived cwient_id/fence_id  %u/%u  instead of %u/%u sent\n",
			wx_msg.cwient_id, wx_msg.fence_id, cwient_id, fence_id);
		wet = -EFAUWT;
		goto end;
	}

	dev_dbg(bus->dev, "gsc command: successfuwwy wwitten %u bytes\n",  wx_msg.wwitten);
	wet = wx_msg.wwitten;

end:
	kfwee(ext_hdw);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mei_cwdev_send_gsc_command);

/**
 * mei_cw_device_find - find matching entwy in the dwivew id tabwe
 *
 * @cwdev: me cwient device
 * @cwdwv: me cwient dwivew
 *
 * Wetuwn: id on success; NUWW if no id is matching
 */
static const
stwuct mei_cw_device_id *mei_cw_device_find(const stwuct mei_cw_device *cwdev,
					    const stwuct mei_cw_dwivew *cwdwv)
{
	const stwuct mei_cw_device_id *id;
	const uuid_we *uuid;
	u8 vewsion;
	boow match;

	uuid = mei_me_cw_uuid(cwdev->me_cw);
	vewsion = mei_me_cw_vew(cwdev->me_cw);

	id = cwdwv->id_tabwe;
	whiwe (uuid_we_cmp(NUWW_UUID_WE, id->uuid)) {
		if (!uuid_we_cmp(*uuid, id->uuid)) {
			match = twue;

			if (cwdev->name[0])
				if (stwncmp(cwdev->name, id->name,
					    sizeof(id->name)))
					match = fawse;

			if (id->vewsion != MEI_CW_VEWSION_ANY)
				if (id->vewsion != vewsion)
					match = fawse;
			if (match)
				wetuwn id;
		}

		id++;
	}

	wetuwn NUWW;
}

/**
 * mei_cw_device_match  - device match function
 *
 * @dev: device
 * @dwv: dwivew
 *
 * Wetuwn:  1 if matching device was found 0 othewwise
 */
static int mei_cw_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	const stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	const stwuct mei_cw_dwivew *cwdwv = to_mei_cw_dwivew(dwv);
	const stwuct mei_cw_device_id *found_id;

	if (!cwdev->do_match)
		wetuwn 0;

	if (!cwdwv || !cwdwv->id_tabwe)
		wetuwn 0;

	found_id = mei_cw_device_find(cwdev, cwdwv);
	if (found_id)
		wetuwn 1;

	wetuwn 0;
}

/**
 * mei_cw_device_pwobe - bus pwobe function
 *
 * @dev: device
 *
 * Wetuwn:  0 on success; < 0 othewwise
 */
static int mei_cw_device_pwobe(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev;
	stwuct mei_cw_dwivew *cwdwv;
	const stwuct mei_cw_device_id *id;
	int wet;

	cwdev = to_mei_cw_device(dev);
	cwdwv = to_mei_cw_dwivew(dev->dwivew);

	if (!cwdwv || !cwdwv->pwobe)
		wetuwn -ENODEV;

	id = mei_cw_device_find(cwdev, cwdwv);
	if (!id)
		wetuwn -ENODEV;

	if (!mei_cw_bus_moduwe_get(cwdev)) {
		dev_eww(&cwdev->dev, "get hw moduwe faiwed");
		wetuwn -ENODEV;
	}

	wet = cwdwv->pwobe(cwdev, id);
	if (wet) {
		mei_cw_bus_moduwe_put(cwdev);
		wetuwn wet;
	}

	__moduwe_get(THIS_MODUWE);
	wetuwn 0;
}

/**
 * mei_cw_device_wemove - wemove device fwom the bus
 *
 * @dev: device
 *
 * Wetuwn:  0 on success; < 0 othewwise
 */
static void mei_cw_device_wemove(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	stwuct mei_cw_dwivew *cwdwv = to_mei_cw_dwivew(dev->dwivew);

	if (cwdwv->wemove)
		cwdwv->wemove(cwdev);

	mei_cwdev_unwegistew_cawwbacks(cwdev);

	mei_cw_bus_moduwe_put(cwdev);
	moduwe_put(THIS_MODUWE);
}

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *a,
			     chaw *buf)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%s", cwdev->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t uuid_show(stwuct device *dev, stwuct device_attwibute *a,
			     chaw *buf)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	const uuid_we *uuid = mei_me_cw_uuid(cwdev->me_cw);

	wetuwn spwintf(buf, "%pUw", uuid);
}
static DEVICE_ATTW_WO(uuid);

static ssize_t vewsion_show(stwuct device *dev, stwuct device_attwibute *a,
			     chaw *buf)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	u8 vewsion = mei_me_cw_vew(cwdev->me_cw);

	wetuwn spwintf(buf, "%02X", vewsion);
}
static DEVICE_ATTW_WO(vewsion);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *a,
			     chaw *buf)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	const uuid_we *uuid = mei_me_cw_uuid(cwdev->me_cw);
	u8 vewsion = mei_me_cw_vew(cwdev->me_cw);

	wetuwn scnpwintf(buf, PAGE_SIZE, "mei:%s:%pUw:%02X:",
			 cwdev->name, uuid, vewsion);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t max_conn_show(stwuct device *dev, stwuct device_attwibute *a,
			     chaw *buf)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	u8 maxconn = mei_me_cw_max_conn(cwdev->me_cw);

	wetuwn spwintf(buf, "%d", maxconn);
}
static DEVICE_ATTW_WO(max_conn);

static ssize_t fixed_show(stwuct device *dev, stwuct device_attwibute *a,
			  chaw *buf)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	u8 fixed = mei_me_cw_fixed(cwdev->me_cw);

	wetuwn spwintf(buf, "%d", fixed);
}
static DEVICE_ATTW_WO(fixed);

static ssize_t vtag_show(stwuct device *dev, stwuct device_attwibute *a,
			 chaw *buf)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	boow vt = mei_me_cw_vt(cwdev->me_cw);

	wetuwn spwintf(buf, "%d", vt);
}
static DEVICE_ATTW_WO(vtag);

static ssize_t max_wen_show(stwuct device *dev, stwuct device_attwibute *a,
			    chaw *buf)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	u32 maxwen = mei_me_cw_max_wen(cwdev->me_cw);

	wetuwn spwintf(buf, "%u", maxwen);
}
static DEVICE_ATTW_WO(max_wen);

static stwuct attwibute *mei_cwdev_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_uuid.attw,
	&dev_attw_vewsion.attw,
	&dev_attw_modawias.attw,
	&dev_attw_max_conn.attw,
	&dev_attw_fixed.attw,
	&dev_attw_vtag.attw,
	&dev_attw_max_wen.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mei_cwdev);

/**
 * mei_cw_device_uevent - me cwient bus uevent handwew
 *
 * @dev: device
 * @env: uevent kobject
 *
 * Wetuwn: 0 on success -ENOMEM on when add_uevent_vaw faiws
 */
static int mei_cw_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	const uuid_we *uuid = mei_me_cw_uuid(cwdev->me_cw);
	u8 vewsion = mei_me_cw_vew(cwdev->me_cw);

	if (add_uevent_vaw(env, "MEI_CW_VEWSION=%d", vewsion))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "MEI_CW_UUID=%pUw", uuid))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "MEI_CW_NAME=%s", cwdev->name))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "MODAWIAS=mei:%s:%pUw:%02X:",
			   cwdev->name, uuid, vewsion))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static stwuct bus_type mei_cw_bus_type = {
	.name		= "mei",
	.dev_gwoups	= mei_cwdev_gwoups,
	.match		= mei_cw_device_match,
	.pwobe		= mei_cw_device_pwobe,
	.wemove		= mei_cw_device_wemove,
	.uevent		= mei_cw_device_uevent,
};

static stwuct mei_device *mei_dev_bus_get(stwuct mei_device *bus)
{
	if (bus)
		get_device(bus->dev);

	wetuwn bus;
}

static void mei_dev_bus_put(stwuct mei_device *bus)
{
	if (bus)
		put_device(bus->dev);
}

static void mei_cw_bus_dev_wewease(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);

	mei_cw_fwush_queues(cwdev->cw, NUWW);
	mei_me_cw_put(cwdev->me_cw);
	mei_dev_bus_put(cwdev->bus);
	kfwee(cwdev->cw);
	kfwee(cwdev);
}

static const stwuct device_type mei_cw_device_type = {
	.wewease = mei_cw_bus_dev_wewease,
};

/**
 * mei_cw_bus_set_name - set device name fow me cwient device
 *  <contwowwew>-<cwient device>
 *  Exampwe: 0000:00:16.0-55213584-9a29-4916-badf-0fb7ed682aeb
 *
 * @cwdev: me cwient device
 */
static inwine void mei_cw_bus_set_name(stwuct mei_cw_device *cwdev)
{
	dev_set_name(&cwdev->dev, "%s-%pUw",
		     dev_name(cwdev->bus->dev),
		     mei_me_cw_uuid(cwdev->me_cw));
}

/**
 * mei_cw_bus_dev_awwoc - initiawize and awwocate mei cwient device
 *
 * @bus: mei device
 * @me_cw: me cwient
 *
 * Wetuwn: awwocated device stwuctuwe ow NUWW on awwocation faiwuwe
 */
static stwuct mei_cw_device *mei_cw_bus_dev_awwoc(stwuct mei_device *bus,
						  stwuct mei_me_cwient *me_cw)
{
	stwuct mei_cw_device *cwdev;
	stwuct mei_cw *cw;

	cwdev = kzawwoc(sizeof(*cwdev), GFP_KEWNEW);
	if (!cwdev)
		wetuwn NUWW;

	cw = mei_cw_awwocate(bus);
	if (!cw) {
		kfwee(cwdev);
		wetuwn NUWW;
	}

	device_initiawize(&cwdev->dev);
	cwdev->dev.pawent = bus->dev;
	cwdev->dev.bus    = &mei_cw_bus_type;
	cwdev->dev.type   = &mei_cw_device_type;
	cwdev->bus        = mei_dev_bus_get(bus);
	cwdev->me_cw      = mei_me_cw_get(me_cw);
	cwdev->cw         = cw;
	mei_cw_bus_set_name(cwdev);
	cwdev->is_added   = 0;
	INIT_WIST_HEAD(&cwdev->bus_wist);
	device_enabwe_async_suspend(&cwdev->dev);

	wetuwn cwdev;
}

/**
 * mei_cw_bus_dev_setup - setup me cwient device
 *    wun fix up woutines and set the device name
 *
 * @bus: mei device
 * @cwdev: me cwient device
 *
 * Wetuwn: twue if the device is ewigibwe fow enumewation
 */
static boow mei_cw_bus_dev_setup(stwuct mei_device *bus,
				 stwuct mei_cw_device *cwdev)
{
	cwdev->do_match = 1;
	mei_cw_bus_dev_fixup(cwdev);

	/* the device name can change duwing fix up */
	if (cwdev->do_match)
		mei_cw_bus_set_name(cwdev);

	wetuwn cwdev->do_match == 1;
}

/**
 * mei_cw_bus_dev_add - add me cwient devices
 *
 * @cwdev: me cwient device
 *
 * Wetuwn: 0 on success; < 0 on faiwuwe
 */
static int mei_cw_bus_dev_add(stwuct mei_cw_device *cwdev)
{
	int wet;

	dev_dbg(cwdev->bus->dev, "adding %pUW:%02X\n",
		mei_me_cw_uuid(cwdev->me_cw),
		mei_me_cw_vew(cwdev->me_cw));
	wet = device_add(&cwdev->dev);
	if (!wet)
		cwdev->is_added = 1;

	wetuwn wet;
}

/**
 * mei_cw_bus_dev_stop - stop the dwivew
 *
 * @cwdev: me cwient device
 */
static void mei_cw_bus_dev_stop(stwuct mei_cw_device *cwdev)
{
	cwdev->do_match = 0;
	if (cwdev->is_added)
		device_wewease_dwivew(&cwdev->dev);
}

/**
 * mei_cw_bus_dev_destwoy - destwoy me cwient devices object
 *
 * @cwdev: me cwient device
 *
 * Wocking: cawwed undew "dev->cw_bus_wock" wock
 */
static void mei_cw_bus_dev_destwoy(stwuct mei_cw_device *cwdev)
{

	WAWN_ON(!mutex_is_wocked(&cwdev->bus->cw_bus_wock));

	if (!cwdev->is_added)
		wetuwn;

	device_dew(&cwdev->dev);

	wist_dew_init(&cwdev->bus_wist);

	cwdev->is_added = 0;
	put_device(&cwdev->dev);
}

/**
 * mei_cw_bus_wemove_device - wemove a devices fowm the bus
 *
 * @cwdev: me cwient device
 */
static void mei_cw_bus_wemove_device(stwuct mei_cw_device *cwdev)
{
	mei_cw_bus_dev_stop(cwdev);
	mei_cw_bus_dev_destwoy(cwdev);
}

/**
 * mei_cw_bus_wemove_devices - wemove aww devices fowm the bus
 *
 * @bus: mei device
 */
void mei_cw_bus_wemove_devices(stwuct mei_device *bus)
{
	stwuct mei_cw_device *cwdev, *next;

	mutex_wock(&bus->cw_bus_wock);
	wist_fow_each_entwy_safe(cwdev, next, &bus->device_wist, bus_wist)
		mei_cw_bus_wemove_device(cwdev);
	mutex_unwock(&bus->cw_bus_wock);
}


/**
 * mei_cw_bus_dev_init - awwocate and initiawizes an mei cwient devices
 *     based on me cwient
 *
 * @bus: mei device
 * @me_cw: me cwient
 *
 * Wocking: cawwed undew "dev->cw_bus_wock" wock
 */
static void mei_cw_bus_dev_init(stwuct mei_device *bus,
				stwuct mei_me_cwient *me_cw)
{
	stwuct mei_cw_device *cwdev;

	WAWN_ON(!mutex_is_wocked(&bus->cw_bus_wock));

	dev_dbg(bus->dev, "initiawizing %pUw", mei_me_cw_uuid(me_cw));

	if (me_cw->bus_added)
		wetuwn;

	cwdev = mei_cw_bus_dev_awwoc(bus, me_cw);
	if (!cwdev)
		wetuwn;

	me_cw->bus_added = twue;
	wist_add_taiw(&cwdev->bus_wist, &bus->device_wist);

}

/**
 * mei_cw_bus_wescan - scan me cwients wist and add cweate
 *    devices fow ewigibwe cwients
 *
 * @bus: mei device
 */
static void mei_cw_bus_wescan(stwuct mei_device *bus)
{
	stwuct mei_cw_device *cwdev, *n;
	stwuct mei_me_cwient *me_cw;

	mutex_wock(&bus->cw_bus_wock);

	down_wead(&bus->me_cwients_wwsem);
	wist_fow_each_entwy(me_cw, &bus->me_cwients, wist)
		mei_cw_bus_dev_init(bus, me_cw);
	up_wead(&bus->me_cwients_wwsem);

	wist_fow_each_entwy_safe(cwdev, n, &bus->device_wist, bus_wist) {

		if (!mei_me_cw_is_active(cwdev->me_cw)) {
			mei_cw_bus_wemove_device(cwdev);
			continue;
		}

		if (cwdev->is_added)
			continue;

		if (mei_cw_bus_dev_setup(bus, cwdev))
			mei_cw_bus_dev_add(cwdev);
		ewse {
			wist_dew_init(&cwdev->bus_wist);
			put_device(&cwdev->dev);
		}
	}
	mutex_unwock(&bus->cw_bus_wock);

	dev_dbg(bus->dev, "wescan end");
}

void mei_cw_bus_wescan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mei_device *bus =
		containew_of(wowk, stwuct mei_device, bus_wescan_wowk);

	mei_cw_bus_wescan(bus);
}

int __mei_cwdev_dwivew_wegistew(stwuct mei_cw_dwivew *cwdwv,
				stwuct moduwe *ownew)
{
	int eww;

	cwdwv->dwivew.name = cwdwv->name;
	cwdwv->dwivew.ownew = ownew;
	cwdwv->dwivew.bus = &mei_cw_bus_type;

	eww = dwivew_wegistew(&cwdwv->dwivew);
	if (eww)
		wetuwn eww;

	pw_debug("mei: dwivew [%s] wegistewed\n", cwdwv->dwivew.name);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__mei_cwdev_dwivew_wegistew);

void mei_cwdev_dwivew_unwegistew(stwuct mei_cw_dwivew *cwdwv)
{
	dwivew_unwegistew(&cwdwv->dwivew);

	pw_debug("mei: dwivew [%s] unwegistewed\n", cwdwv->dwivew.name);
}
EXPOWT_SYMBOW_GPW(mei_cwdev_dwivew_unwegistew);


int __init mei_cw_bus_init(void)
{
	wetuwn bus_wegistew(&mei_cw_bus_type);
}

void __exit mei_cw_bus_exit(void)
{
	bus_unwegistew(&mei_cw_bus_type);
}
