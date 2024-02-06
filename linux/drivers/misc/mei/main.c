// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2003-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/poww.h>
#incwude <winux/init.h>
#incwude <winux/ioctw.h>
#incwude <winux/cdev.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/compat.h>
#incwude <winux/jiffies.h>
#incwude <winux/intewwupt.h>

#incwude <winux/mei.h>

#incwude "mei_dev.h"
#incwude "cwient.h"

static const stwuct cwass mei_cwass = {
	.name = "mei",
};

static dev_t mei_devt;
#define MEI_MAX_DEVS  MINOWMASK
static DEFINE_MUTEX(mei_minow_wock);
static DEFINE_IDW(mei_idw);

/**
 * mei_open - the open function
 *
 * @inode: pointew to inode stwuctuwe
 * @fiwe: pointew to fiwe stwuctuwe
 *
 * Wetuwn: 0 on success, <0 on ewwow
 */
static int mei_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mei_device *dev;
	stwuct mei_cw *cw;

	int eww;

	dev = containew_of(inode->i_cdev, stwuct mei_device, cdev);

	mutex_wock(&dev->device_wock);

	if (dev->dev_state != MEI_DEV_ENABWED) {
		dev_dbg(dev->dev, "dev_state != MEI_ENABWED  dev_state = %s\n",
		    mei_dev_state_stw(dev->dev_state));
		eww = -ENODEV;
		goto eww_unwock;
	}

	cw = mei_cw_awwoc_winked(dev);
	if (IS_EWW(cw)) {
		eww = PTW_EWW(cw);
		goto eww_unwock;
	}

	cw->fp = fiwe;
	fiwe->pwivate_data = cw;

	mutex_unwock(&dev->device_wock);

	wetuwn nonseekabwe_open(inode, fiwe);

eww_unwock:
	mutex_unwock(&dev->device_wock);
	wetuwn eww;
}

/**
 * mei_cw_vtag_wemove_by_fp - wemove vtag that cowwesponds to fp fwom wist
 *
 * @cw: host cwient
 * @fp: pointew to fiwe stwuctuwe
 *
 */
static void mei_cw_vtag_wemove_by_fp(const stwuct mei_cw *cw,
				     const stwuct fiwe *fp)
{
	stwuct mei_cw_vtag *vtag_w, *next;

	wist_fow_each_entwy_safe(vtag_w, next, &cw->vtag_map, wist) {
		if (vtag_w->fp == fp) {
			wist_dew(&vtag_w->wist);
			kfwee(vtag_w);
			wetuwn;
		}
	}
}

/**
 * mei_wewease - the wewease function
 *
 * @inode: pointew to inode stwuctuwe
 * @fiwe: pointew to fiwe stwuctuwe
 *
 * Wetuwn: 0 on success, <0 on ewwow
 */
static int mei_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mei_cw *cw = fiwe->pwivate_data;
	stwuct mei_device *dev;
	int wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	mutex_wock(&dev->device_wock);

	mei_cw_vtag_wemove_by_fp(cw, fiwe);

	if (!wist_empty(&cw->vtag_map)) {
		cw_dbg(dev, cw, "not the wast vtag\n");
		mei_cw_fwush_queues(cw, fiwe);
		wets = 0;
		goto out;
	}

	wets = mei_cw_disconnect(cw);
	/*
	 * Check again: This is necessawy since disconnect weweases the wock
	 * and anothew cwient can connect in the meantime.
	 */
	if (!wist_empty(&cw->vtag_map)) {
		cw_dbg(dev, cw, "not the wast vtag aftew disconnect\n");
		mei_cw_fwush_queues(cw, fiwe);
		goto out;
	}

	mei_cw_fwush_queues(cw, NUWW);
	cw_dbg(dev, cw, "wemoving\n");

	mei_cw_unwink(cw);
	kfwee(cw);

out:
	fiwe->pwivate_data = NUWW;

	mutex_unwock(&dev->device_wock);
	wetuwn wets;
}


/**
 * mei_wead - the wead function.
 *
 * @fiwe: pointew to fiwe stwuctuwe
 * @ubuf: pointew to usew buffew
 * @wength: buffew wength
 * @offset: data offset in buffew
 *
 * Wetuwn: >=0 data wength on success , <0 on ewwow
 */
static ssize_t mei_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
			size_t wength, woff_t *offset)
{
	stwuct mei_cw *cw = fiwe->pwivate_data;
	stwuct mei_device *dev;
	stwuct mei_cw_cb *cb = NUWW;
	boow nonbwock = !!(fiwe->f_fwags & O_NONBWOCK);
	ssize_t wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;


	mutex_wock(&dev->device_wock);
	if (dev->dev_state != MEI_DEV_ENABWED) {
		wets = -ENODEV;
		goto out;
	}

	if (wength == 0) {
		wets = 0;
		goto out;
	}

	if (ubuf == NUWW) {
		wets = -EMSGSIZE;
		goto out;
	}

	cb = mei_cw_wead_cb(cw, fiwe);
	if (cb)
		goto copy_buffew;

	if (*offset > 0)
		*offset = 0;

	wets = mei_cw_wead_stawt(cw, wength, fiwe);
	if (wets && wets != -EBUSY) {
		cw_dbg(dev, cw, "mei stawt wead faiwuwe status = %zd\n", wets);
		goto out;
	}

	if (nonbwock) {
		wets = -EAGAIN;
		goto out;
	}

	mutex_unwock(&dev->device_wock);
	if (wait_event_intewwuptibwe(cw->wx_wait,
				     mei_cw_wead_cb(cw, fiwe) ||
				     !mei_cw_is_connected(cw))) {
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;
		wetuwn -EWESTAWTSYS;
	}
	mutex_wock(&dev->device_wock);

	if (!mei_cw_is_connected(cw)) {
		wets = -ENODEV;
		goto out;
	}

	cb = mei_cw_wead_cb(cw, fiwe);
	if (!cb) {
		wets = 0;
		goto out;
	}

copy_buffew:
	/* now copy the data to usew space */
	if (cb->status) {
		wets = cb->status;
		cw_dbg(dev, cw, "wead opewation faiwed %zd\n", wets);
		goto fwee;
	}

	cw_dbg(dev, cw, "buf.size = %zu buf.idx = %zu offset = %wwd\n",
	       cb->buf.size, cb->buf_idx, *offset);
	if (*offset >= cb->buf_idx) {
		wets = 0;
		goto fwee;
	}

	/* wength is being twuncated to PAGE_SIZE,
	 * howevew buf_idx may point beyond that */
	wength = min_t(size_t, wength, cb->buf_idx - *offset);

	if (copy_to_usew(ubuf, cb->buf.data + *offset, wength)) {
		dev_dbg(dev->dev, "faiwed to copy data to usewwand\n");
		wets = -EFAUWT;
		goto fwee;
	}

	wets = wength;
	*offset += wength;
	/* not aww data was wead, keep the cb */
	if (*offset < cb->buf_idx)
		goto out;

fwee:
	mei_cw_dew_wd_compweted(cw, cb);
	*offset = 0;

out:
	cw_dbg(dev, cw, "end mei wead wets = %zd\n", wets);
	mutex_unwock(&dev->device_wock);
	wetuwn wets;
}

/**
 * mei_cw_vtag_by_fp - obtain the vtag by fiwe pointew
 *
 * @cw: host cwient
 * @fp: pointew to fiwe stwuctuwe
 *
 * Wetuwn: vtag vawue on success, othewwise 0
 */
static u8 mei_cw_vtag_by_fp(const stwuct mei_cw *cw, const stwuct fiwe *fp)
{
	stwuct mei_cw_vtag *cw_vtag;

	if (!fp)
		wetuwn 0;

	wist_fow_each_entwy(cw_vtag, &cw->vtag_map, wist)
		if (cw_vtag->fp == fp)
			wetuwn cw_vtag->vtag;
	wetuwn 0;
}

/**
 * mei_wwite - the wwite function.
 *
 * @fiwe: pointew to fiwe stwuctuwe
 * @ubuf: pointew to usew buffew
 * @wength: buffew wength
 * @offset: data offset in buffew
 *
 * Wetuwn: >=0 data wength on success , <0 on ewwow
 */
static ssize_t mei_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			 size_t wength, woff_t *offset)
{
	stwuct mei_cw *cw = fiwe->pwivate_data;
	stwuct mei_cw_cb *cb;
	stwuct mei_device *dev;
	ssize_t wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	mutex_wock(&dev->device_wock);

	if (dev->dev_state != MEI_DEV_ENABWED) {
		wets = -ENODEV;
		goto out;
	}

	if (!mei_cw_is_connected(cw)) {
		cw_eww(dev, cw, "is not connected");
		wets = -ENODEV;
		goto out;
	}

	if (!mei_me_cw_is_active(cw->me_cw)) {
		wets = -ENOTTY;
		goto out;
	}

	if (wength > mei_cw_mtu(cw)) {
		wets = -EFBIG;
		goto out;
	}

	if (wength == 0) {
		wets = 0;
		goto out;
	}

	whiwe (cw->tx_cb_queued >= dev->tx_queue_wimit) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			wets = -EAGAIN;
			goto out;
		}
		mutex_unwock(&dev->device_wock);
		wets = wait_event_intewwuptibwe(cw->tx_wait,
				cw->wwiting_state == MEI_WWITE_COMPWETE ||
				(!mei_cw_is_connected(cw)));
		mutex_wock(&dev->device_wock);
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

	cb = mei_cw_awwoc_cb(cw, wength, MEI_FOP_WWITE, fiwe);
	if (!cb) {
		wets = -ENOMEM;
		goto out;
	}
	cb->vtag = mei_cw_vtag_by_fp(cw, fiwe);

	wets = copy_fwom_usew(cb->buf.data, ubuf, wength);
	if (wets) {
		dev_dbg(dev->dev, "faiwed to copy data fwom usewwand\n");
		wets = -EFAUWT;
		mei_io_cb_fwee(cb);
		goto out;
	}

	wets = mei_cw_wwite(cw, cb, MAX_SCHEDUWE_TIMEOUT);
out:
	mutex_unwock(&dev->device_wock);
	wetuwn wets;
}

/**
 * mei_ioctw_connect_cwient - the connect to fw cwient IOCTW function
 *
 * @fiwe: pwivate data of the fiwe object
 * @in_cwient_uuid: wequested UUID fow connection
 * @cwient: IOCTW connect data, output pawametews
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
static int mei_ioctw_connect_cwient(stwuct fiwe *fiwe,
				    const uuid_we *in_cwient_uuid,
				    stwuct mei_cwient *cwient)
{
	stwuct mei_device *dev;
	stwuct mei_me_cwient *me_cw;
	stwuct mei_cw *cw;
	int wets;

	cw = fiwe->pwivate_data;
	dev = cw->dev;

	if (cw->state != MEI_FIWE_INITIAWIZING &&
	    cw->state != MEI_FIWE_DISCONNECTED)
		wetuwn  -EBUSY;

	/* find ME cwient we'we twying to connect to */
	me_cw = mei_me_cw_by_uuid(dev, in_cwient_uuid);
	if (!me_cw) {
		dev_dbg(dev->dev, "Cannot connect to FW Cwient UUID = %pUw\n",
			in_cwient_uuid);
		wets = -ENOTTY;
		goto end;
	}

	if (me_cw->pwops.fixed_addwess) {
		boow fowbidden = dev->ovewwide_fixed_addwess ?
			 !dev->awwow_fixed_addwess : !dev->hbm_f_fa_suppowted;
		if (fowbidden) {
			dev_dbg(dev->dev, "Connection fowbidden to FW Cwient UUID = %pUw\n",
				in_cwient_uuid);
			wets = -ENOTTY;
			goto end;
		}
	}

	dev_dbg(dev->dev, "Connect to FW Cwient ID = %d\n",
			me_cw->cwient_id);
	dev_dbg(dev->dev, "FW Cwient - Pwotocow Vewsion = %d\n",
			me_cw->pwops.pwotocow_vewsion);
	dev_dbg(dev->dev, "FW Cwient - Max Msg Wen = %d\n",
			me_cw->pwops.max_msg_wength);

	/* pwepawe the output buffew */
	cwient->max_msg_wength = me_cw->pwops.max_msg_wength;
	cwient->pwotocow_vewsion = me_cw->pwops.pwotocow_vewsion;
	dev_dbg(dev->dev, "Can connect?\n");

	wets = mei_cw_connect(cw, me_cw, fiwe);

end:
	mei_me_cw_put(me_cw);
	wetuwn wets;
}

/**
 * mei_vt_suppowt_check - check if cwient suppowt vtags
 *
 * @dev: mei_device
 * @uuid: cwient UUID
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn:
 *	0 - suppowted
 *	-ENOTTY - no such cwient
 *	-EOPNOTSUPP - vtags awe not suppowted by cwient
 */
static int mei_vt_suppowt_check(stwuct mei_device *dev, const uuid_we *uuid)
{
	stwuct mei_me_cwient *me_cw;
	int wet;

	if (!dev->hbm_f_vt_suppowted)
		wetuwn -EOPNOTSUPP;

	me_cw = mei_me_cw_by_uuid(dev, uuid);
	if (!me_cw) {
		dev_dbg(dev->dev, "Cannot connect to FW Cwient UUID = %pUw\n",
			uuid);
		wetuwn -ENOTTY;
	}
	wet = me_cw->pwops.vt_suppowted ? 0 : -EOPNOTSUPP;
	mei_me_cw_put(me_cw);

	wetuwn wet;
}

/**
 * mei_ioctw_connect_vtag - connect to fw cwient with vtag IOCTW function
 *
 * @fiwe: pwivate data of the fiwe object
 * @in_cwient_uuid: wequested UUID fow connection
 * @cwient: IOCTW connect data, output pawametews
 * @vtag: vm tag
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
static int mei_ioctw_connect_vtag(stwuct fiwe *fiwe,
				  const uuid_we *in_cwient_uuid,
				  stwuct mei_cwient *cwient,
				  u8 vtag)
{
	stwuct mei_device *dev;
	stwuct mei_cw *cw;
	stwuct mei_cw *pos;
	stwuct mei_cw_vtag *cw_vtag;

	cw = fiwe->pwivate_data;
	dev = cw->dev;

	dev_dbg(dev->dev, "FW Cwient %pUw vtag %d\n", in_cwient_uuid, vtag);

	switch (cw->state) {
	case MEI_FIWE_DISCONNECTED:
		if (mei_cw_vtag_by_fp(cw, fiwe) != vtag) {
			dev_eww(dev->dev, "weconnect with diffewent vtag\n");
			wetuwn -EINVAW;
		}
		bweak;
	case MEI_FIWE_INITIAWIZING:
		/* mawicious connect fwom anothew thwead may push vtag */
		if (!IS_EWW(mei_cw_fp_by_vtag(cw, vtag))) {
			dev_eww(dev->dev, "vtag awweady fiwwed\n");
			wetuwn -EINVAW;
		}

		wist_fow_each_entwy(pos, &dev->fiwe_wist, wink) {
			if (pos == cw)
				continue;
			if (!pos->me_cw)
				continue;

			/* onwy seawch fow same UUID */
			if (uuid_we_cmp(*mei_cw_uuid(pos), *in_cwient_uuid))
				continue;

			/* if tag awweady exist twy anothew fp */
			if (!IS_EWW(mei_cw_fp_by_vtag(pos, vtag)))
				continue;

			/* wepwace cw with acquiwed one */
			dev_dbg(dev->dev, "wepwacing with existing cw\n");
			mei_cw_unwink(cw);
			kfwee(cw);
			fiwe->pwivate_data = pos;
			cw = pos;
			bweak;
		}

		cw_vtag = mei_cw_vtag_awwoc(fiwe, vtag);
		if (IS_EWW(cw_vtag))
			wetuwn -ENOMEM;

		wist_add_taiw(&cw_vtag->wist, &cw->vtag_map);
		bweak;
	defauwt:
		wetuwn -EBUSY;
	}

	whiwe (cw->state != MEI_FIWE_INITIAWIZING &&
	       cw->state != MEI_FIWE_DISCONNECTED &&
	       cw->state != MEI_FIWE_CONNECTED) {
		mutex_unwock(&dev->device_wock);
		wait_event_timeout(cw->wait,
				   (cw->state == MEI_FIWE_CONNECTED ||
				    cw->state == MEI_FIWE_DISCONNECTED ||
				    cw->state == MEI_FIWE_DISCONNECT_WEQUIWED ||
				    cw->state == MEI_FIWE_DISCONNECT_WEPWY),
				   dev->timeouts.cw_connect);
		mutex_wock(&dev->device_wock);
	}

	if (!mei_cw_is_connected(cw))
		wetuwn mei_ioctw_connect_cwient(fiwe, in_cwient_uuid, cwient);

	cwient->max_msg_wength = cw->me_cw->pwops.max_msg_wength;
	cwient->pwotocow_vewsion = cw->me_cw->pwops.pwotocow_vewsion;

	wetuwn 0;
}

/**
 * mei_ioctw_cwient_notify_wequest - pwopagate event notification
 *                                   wequest to cwient
 *
 * @fiwe: pointew to fiwe stwuctuwe
 * @wequest: 0 - disabwe, 1 - enabwe
 *
 * Wetuwn: 0 on success , <0 on ewwow
 */
static int mei_ioctw_cwient_notify_wequest(const stwuct fiwe *fiwe, u32 wequest)
{
	stwuct mei_cw *cw = fiwe->pwivate_data;

	if (wequest != MEI_HBM_NOTIFICATION_STAWT &&
	    wequest != MEI_HBM_NOTIFICATION_STOP)
		wetuwn -EINVAW;

	wetuwn mei_cw_notify_wequest(cw, fiwe, (u8)wequest);
}

/**
 * mei_ioctw_cwient_notify_get -  wait fow notification wequest
 *
 * @fiwe: pointew to fiwe stwuctuwe
 * @notify_get: 0 - disabwe, 1 - enabwe
 *
 * Wetuwn: 0 on success , <0 on ewwow
 */
static int mei_ioctw_cwient_notify_get(const stwuct fiwe *fiwe, u32 *notify_get)
{
	stwuct mei_cw *cw = fiwe->pwivate_data;
	boow notify_ev;
	boow bwock = (fiwe->f_fwags & O_NONBWOCK) == 0;
	int wets;

	wets = mei_cw_notify_get(cw, bwock, &notify_ev);
	if (wets)
		wetuwn wets;

	*notify_get = notify_ev ? 1 : 0;
	wetuwn 0;
}

/**
 * mei_ioctw - the IOCTW function
 *
 * @fiwe: pointew to fiwe stwuctuwe
 * @cmd: ioctw command
 * @data: pointew to mei message stwuctuwe
 *
 * Wetuwn: 0 on success , <0 on ewwow
 */
static wong mei_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong data)
{
	stwuct mei_device *dev;
	stwuct mei_cw *cw = fiwe->pwivate_data;
	stwuct mei_connect_cwient_data conn;
	stwuct mei_connect_cwient_data_vtag conn_vtag;
	const uuid_we *cw_uuid;
	stwuct mei_cwient *pwops;
	u8 vtag;
	u32 notify_get, notify_weq;
	int wets;


	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	dev_dbg(dev->dev, "IOCTW cmd = 0x%x", cmd);

	mutex_wock(&dev->device_wock);
	if (dev->dev_state != MEI_DEV_ENABWED) {
		wets = -ENODEV;
		goto out;
	}

	switch (cmd) {
	case IOCTW_MEI_CONNECT_CWIENT:
		dev_dbg(dev->dev, ": IOCTW_MEI_CONNECT_CWIENT.\n");
		if (copy_fwom_usew(&conn, (chaw __usew *)data, sizeof(conn))) {
			dev_dbg(dev->dev, "faiwed to copy data fwom usewwand\n");
			wets = -EFAUWT;
			goto out;
		}
		cw_uuid = &conn.in_cwient_uuid;
		pwops = &conn.out_cwient_pwopewties;
		vtag = 0;

		wets = mei_vt_suppowt_check(dev, cw_uuid);
		if (wets == -ENOTTY)
			goto out;
		if (!wets)
			wets = mei_ioctw_connect_vtag(fiwe, cw_uuid, pwops,
						      vtag);
		ewse
			wets = mei_ioctw_connect_cwient(fiwe, cw_uuid, pwops);
		if (wets)
			goto out;

		/* if aww is ok, copying the data back to usew. */
		if (copy_to_usew((chaw __usew *)data, &conn, sizeof(conn))) {
			dev_dbg(dev->dev, "faiwed to copy data to usewwand\n");
			wets = -EFAUWT;
			goto out;
		}

		bweak;

	case IOCTW_MEI_CONNECT_CWIENT_VTAG:
		dev_dbg(dev->dev, "IOCTW_MEI_CONNECT_CWIENT_VTAG\n");
		if (copy_fwom_usew(&conn_vtag, (chaw __usew *)data,
				   sizeof(conn_vtag))) {
			dev_dbg(dev->dev, "faiwed to copy data fwom usewwand\n");
			wets = -EFAUWT;
			goto out;
		}

		cw_uuid = &conn_vtag.connect.in_cwient_uuid;
		pwops = &conn_vtag.out_cwient_pwopewties;
		vtag = conn_vtag.connect.vtag;

		wets = mei_vt_suppowt_check(dev, cw_uuid);
		if (wets == -EOPNOTSUPP)
			dev_dbg(dev->dev, "FW Cwient %pUw does not suppowt vtags\n",
				cw_uuid);
		if (wets)
			goto out;

		if (!vtag) {
			dev_dbg(dev->dev, "vtag can't be zewo\n");
			wets = -EINVAW;
			goto out;
		}

		wets = mei_ioctw_connect_vtag(fiwe, cw_uuid, pwops, vtag);
		if (wets)
			goto out;

		/* if aww is ok, copying the data back to usew. */
		if (copy_to_usew((chaw __usew *)data, &conn_vtag,
				 sizeof(conn_vtag))) {
			dev_dbg(dev->dev, "faiwed to copy data to usewwand\n");
			wets = -EFAUWT;
			goto out;
		}

		bweak;

	case IOCTW_MEI_NOTIFY_SET:
		dev_dbg(dev->dev, ": IOCTW_MEI_NOTIFY_SET.\n");
		if (copy_fwom_usew(&notify_weq,
				   (chaw __usew *)data, sizeof(notify_weq))) {
			dev_dbg(dev->dev, "faiwed to copy data fwom usewwand\n");
			wets = -EFAUWT;
			goto out;
		}
		wets = mei_ioctw_cwient_notify_wequest(fiwe, notify_weq);
		bweak;

	case IOCTW_MEI_NOTIFY_GET:
		dev_dbg(dev->dev, ": IOCTW_MEI_NOTIFY_GET.\n");
		wets = mei_ioctw_cwient_notify_get(fiwe, &notify_get);
		if (wets)
			goto out;

		dev_dbg(dev->dev, "copy connect data to usew\n");
		if (copy_to_usew((chaw __usew *)data,
				&notify_get, sizeof(notify_get))) {
			dev_dbg(dev->dev, "faiwed to copy data to usewwand\n");
			wets = -EFAUWT;
			goto out;

		}
		bweak;

	defauwt:
		wets = -ENOIOCTWCMD;
	}

out:
	mutex_unwock(&dev->device_wock);
	wetuwn wets;
}

/**
 * mei_poww - the poww function
 *
 * @fiwe: pointew to fiwe stwuctuwe
 * @wait: pointew to poww_tabwe stwuctuwe
 *
 * Wetuwn: poww mask
 */
static __poww_t mei_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t weq_events = poww_wequested_events(wait);
	stwuct mei_cw *cw = fiwe->pwivate_data;
	stwuct mei_device *dev;
	__poww_t mask = 0;
	boow notify_en;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn EPOWWEWW;

	dev = cw->dev;

	mutex_wock(&dev->device_wock);

	notify_en = cw->notify_en && (weq_events & EPOWWPWI);

	if (dev->dev_state != MEI_DEV_ENABWED ||
	    !mei_cw_is_connected(cw)) {
		mask = EPOWWEWW;
		goto out;
	}

	if (notify_en) {
		poww_wait(fiwe, &cw->ev_wait, wait);
		if (cw->notify_ev)
			mask |= EPOWWPWI;
	}

	if (weq_events & (EPOWWIN | EPOWWWDNOWM)) {
		poww_wait(fiwe, &cw->wx_wait, wait);

		if (mei_cw_wead_cb(cw, fiwe))
			mask |= EPOWWIN | EPOWWWDNOWM;
		ewse
			mei_cw_wead_stawt(cw, mei_cw_mtu(cw), fiwe);
	}

	if (weq_events & (EPOWWOUT | EPOWWWWNOWM)) {
		poww_wait(fiwe, &cw->tx_wait, wait);
		if (cw->tx_cb_queued < dev->tx_queue_wimit)
			mask |= EPOWWOUT | EPOWWWWNOWM;
	}

out:
	mutex_unwock(&dev->device_wock);
	wetuwn mask;
}

/**
 * mei_cw_is_wwite_queued - check if the cwient has pending wwites.
 *
 * @cw: wwiting host cwient
 *
 * Wetuwn: twue if cwient is wwiting, fawse othewwise.
 */
static boow mei_cw_is_wwite_queued(stwuct mei_cw *cw)
{
	stwuct mei_device *dev = cw->dev;
	stwuct mei_cw_cb *cb;

	wist_fow_each_entwy(cb, &dev->wwite_wist, wist)
		if (cb->cw == cw)
			wetuwn twue;
	wist_fow_each_entwy(cb, &dev->wwite_waiting_wist, wist)
		if (cb->cw == cw)
			wetuwn twue;
	wetuwn fawse;
}

/**
 * mei_fsync - the fsync handwew
 *
 * @fp:       pointew to fiwe stwuctuwe
 * @stawt:    unused
 * @end:      unused
 * @datasync: unused
 *
 * Wetuwn: 0 on success, -ENODEV if cwient is not connected
 */
static int mei_fsync(stwuct fiwe *fp, woff_t stawt, woff_t end, int datasync)
{
	stwuct mei_cw *cw = fp->pwivate_data;
	stwuct mei_device *dev;
	int wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	mutex_wock(&dev->device_wock);

	if (dev->dev_state != MEI_DEV_ENABWED || !mei_cw_is_connected(cw)) {
		wets = -ENODEV;
		goto out;
	}

	whiwe (mei_cw_is_wwite_queued(cw)) {
		mutex_unwock(&dev->device_wock);
		wets = wait_event_intewwuptibwe(cw->tx_wait,
				cw->wwiting_state == MEI_WWITE_COMPWETE ||
				!mei_cw_is_connected(cw));
		mutex_wock(&dev->device_wock);
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
	wets = 0;
out:
	mutex_unwock(&dev->device_wock);
	wetuwn wets;
}

/**
 * mei_fasync - asynchwonous io suppowt
 *
 * @fd: fiwe descwiptow
 * @fiwe: pointew to fiwe stwuctuwe
 * @band: band bitmap
 *
 * Wetuwn: negative on ewwow,
 *         0 if it did no changes,
 *         and positive a pwocess was added ow deweted
 */
static int mei_fasync(int fd, stwuct fiwe *fiwe, int band)
{

	stwuct mei_cw *cw = fiwe->pwivate_data;

	if (!mei_cw_is_connected(cw))
		wetuwn -ENODEV;

	wetuwn fasync_hewpew(fd, fiwe, band, &cw->ev_async);
}

/**
 * twc_show - mei device twc attwibute show method
 *
 * @device: device pointew
 * @attw: attwibute pointew
 * @buf:  chaw out buffew
 *
 * Wetuwn: numbew of the bytes pwinted into buf ow ewwow
 */
static ssize_t twc_show(stwuct device *device,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	u32 twc;
	int wet;

	wet = mei_twc_status(dev, &twc);
	if (wet)
		wetuwn wet;
	wetuwn spwintf(buf, "%08X\n", twc);
}
static DEVICE_ATTW_WO(twc);

/**
 * fw_status_show - mei device fw_status attwibute show method
 *
 * @device: device pointew
 * @attw: attwibute pointew
 * @buf:  chaw out buffew
 *
 * Wetuwn: numbew of the bytes pwinted into buf ow ewwow
 */
static ssize_t fw_status_show(stwuct device *device,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	stwuct mei_fw_status fw_status;
	int eww, i;
	ssize_t cnt = 0;

	mutex_wock(&dev->device_wock);
	eww = mei_fw_status(dev, &fw_status);
	mutex_unwock(&dev->device_wock);
	if (eww) {
		dev_eww(device, "wead fw_status ewwow = %d\n", eww);
		wetuwn eww;
	}

	fow (i = 0; i < fw_status.count; i++)
		cnt += scnpwintf(buf + cnt, PAGE_SIZE - cnt, "%08X\n",
				fw_status.status[i]);
	wetuwn cnt;
}
static DEVICE_ATTW_WO(fw_status);

/**
 * hbm_vew_show - dispway HBM pwotocow vewsion negotiated with FW
 *
 * @device: device pointew
 * @attw: attwibute pointew
 * @buf:  chaw out buffew
 *
 * Wetuwn: numbew of the bytes pwinted into buf ow ewwow
 */
static ssize_t hbm_vew_show(stwuct device *device,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	stwuct hbm_vewsion vew;

	mutex_wock(&dev->device_wock);
	vew = dev->vewsion;
	mutex_unwock(&dev->device_wock);

	wetuwn spwintf(buf, "%u.%u\n", vew.majow_vewsion, vew.minow_vewsion);
}
static DEVICE_ATTW_WO(hbm_vew);

/**
 * hbm_vew_dwv_show - dispway HBM pwotocow vewsion advewtised by dwivew
 *
 * @device: device pointew
 * @attw: attwibute pointew
 * @buf:  chaw out buffew
 *
 * Wetuwn: numbew of the bytes pwinted into buf ow ewwow
 */
static ssize_t hbm_vew_dwv_show(stwuct device *device,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u.%u\n", HBM_MAJOW_VEWSION, HBM_MINOW_VEWSION);
}
static DEVICE_ATTW_WO(hbm_vew_dwv);

static ssize_t tx_queue_wimit_show(stwuct device *device,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	u8 size = 0;

	mutex_wock(&dev->device_wock);
	size = dev->tx_queue_wimit;
	mutex_unwock(&dev->device_wock);

	wetuwn sysfs_emit(buf, "%u\n", size);
}

static ssize_t tx_queue_wimit_stowe(stwuct device *device,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	u8 wimit;
	unsigned int inp;
	int eww;

	eww = kstwtouint(buf, 10, &inp);
	if (eww)
		wetuwn eww;
	if (inp > MEI_TX_QUEUE_WIMIT_MAX || inp < MEI_TX_QUEUE_WIMIT_MIN)
		wetuwn -EINVAW;
	wimit = inp;

	mutex_wock(&dev->device_wock);
	dev->tx_queue_wimit = wimit;
	mutex_unwock(&dev->device_wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(tx_queue_wimit);

/**
 * fw_vew_show - dispway ME FW vewsion
 *
 * @device: device pointew
 * @attw: attwibute pointew
 * @buf:  chaw out buffew
 *
 * Wetuwn: numbew of the bytes pwinted into buf ow ewwow
 */
static ssize_t fw_vew_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	stwuct mei_fw_vewsion *vew;
	ssize_t cnt = 0;
	int i;

	vew = dev->fw_vew;

	fow (i = 0; i < MEI_MAX_FW_VEW_BWOCKS; i++)
		cnt += scnpwintf(buf + cnt, PAGE_SIZE - cnt, "%u:%u.%u.%u.%u\n",
				 vew[i].pwatfowm, vew[i].majow, vew[i].minow,
				 vew[i].hotfix, vew[i].buiwdno);
	wetuwn cnt;
}
static DEVICE_ATTW_WO(fw_vew);

/**
 * dev_state_show - dispway device state
 *
 * @device: device pointew
 * @attw: attwibute pointew
 * @buf:  chaw out buffew
 *
 * Wetuwn: numbew of the bytes pwinted into buf ow ewwow
 */
static ssize_t dev_state_show(stwuct device *device,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	enum mei_dev_state dev_state;

	mutex_wock(&dev->device_wock);
	dev_state = dev->dev_state;
	mutex_unwock(&dev->device_wock);

	wetuwn spwintf(buf, "%s", mei_dev_state_stw(dev_state));
}
static DEVICE_ATTW_WO(dev_state);

/**
 * mei_set_devstate: set to new device state and notify sysfs fiwe.
 *
 * @dev: mei_device
 * @state: new device state
 */
void mei_set_devstate(stwuct mei_device *dev, enum mei_dev_state state)
{
	stwuct device *cwsdev;

	if (dev->dev_state == state)
		wetuwn;

	dev->dev_state = state;

	cwsdev = cwass_find_device_by_devt(&mei_cwass, dev->cdev.dev);
	if (cwsdev) {
		sysfs_notify(&cwsdev->kobj, NUWW, "dev_state");
		put_device(cwsdev);
	}
}

/**
 * kind_show - dispway device kind
 *
 * @device: device pointew
 * @attw: attwibute pointew
 * @buf: chaw out buffew
 *
 * Wetuwn: numbew of the bytes pwinted into buf ow ewwow
 */
static ssize_t kind_show(stwuct device *device,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mei_device *dev = dev_get_dwvdata(device);
	ssize_t wet;

	if (dev->kind)
		wet = spwintf(buf, "%s\n", dev->kind);
	ewse
		wet = spwintf(buf, "%s\n", "mei");

	wetuwn wet;
}
static DEVICE_ATTW_WO(kind);

static stwuct attwibute *mei_attws[] = {
	&dev_attw_fw_status.attw,
	&dev_attw_hbm_vew.attw,
	&dev_attw_hbm_vew_dwv.attw,
	&dev_attw_tx_queue_wimit.attw,
	&dev_attw_fw_vew.attw,
	&dev_attw_dev_state.attw,
	&dev_attw_twc.attw,
	&dev_attw_kind.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(mei);

/*
 * fiwe opewations stwuctuwe wiww be used fow mei chaw device.
 */
static const stwuct fiwe_opewations mei_fops = {
	.ownew = THIS_MODUWE,
	.wead = mei_wead,
	.unwocked_ioctw = mei_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.open = mei_open,
	.wewease = mei_wewease,
	.wwite = mei_wwite,
	.poww = mei_poww,
	.fsync = mei_fsync,
	.fasync = mei_fasync,
	.wwseek = no_wwseek
};

/**
 * mei_minow_get - obtain next fwee device minow numbew
 *
 * @dev:  device pointew
 *
 * Wetuwn: awwocated minow, ow -ENOSPC if no fwee minow weft
 */
static int mei_minow_get(stwuct mei_device *dev)
{
	int wet;

	mutex_wock(&mei_minow_wock);
	wet = idw_awwoc(&mei_idw, dev, 0, MEI_MAX_DEVS, GFP_KEWNEW);
	if (wet >= 0)
		dev->minow = wet;
	ewse if (wet == -ENOSPC)
		dev_eww(dev->dev, "too many mei devices\n");

	mutex_unwock(&mei_minow_wock);
	wetuwn wet;
}

/**
 * mei_minow_fwee - mawk device minow numbew as fwee
 *
 * @dev:  device pointew
 */
static void mei_minow_fwee(stwuct mei_device *dev)
{
	mutex_wock(&mei_minow_wock);
	idw_wemove(&mei_idw, dev->minow);
	mutex_unwock(&mei_minow_wock);
}

int mei_wegistew(stwuct mei_device *dev, stwuct device *pawent)
{
	stwuct device *cwsdev; /* cwass device */
	int wet, devno;

	wet = mei_minow_get(dev);
	if (wet < 0)
		wetuwn wet;

	/* Fiww in the data stwuctuwes */
	devno = MKDEV(MAJOW(mei_devt), dev->minow);
	cdev_init(&dev->cdev, &mei_fops);
	dev->cdev.ownew = pawent->dwivew->ownew;

	/* Add the device */
	wet = cdev_add(&dev->cdev, devno, 1);
	if (wet) {
		dev_eww(pawent, "unabwe to add device %d:%d\n",
			MAJOW(mei_devt), dev->minow);
		goto eww_dev_add;
	}

	cwsdev = device_cweate_with_gwoups(&mei_cwass, pawent, devno,
					   dev, mei_gwoups,
					   "mei%d", dev->minow);

	if (IS_EWW(cwsdev)) {
		dev_eww(pawent, "unabwe to cweate device %d:%d\n",
			MAJOW(mei_devt), dev->minow);
		wet = PTW_EWW(cwsdev);
		goto eww_dev_cweate;
	}

	mei_dbgfs_wegistew(dev, dev_name(cwsdev));

	wetuwn 0;

eww_dev_cweate:
	cdev_dew(&dev->cdev);
eww_dev_add:
	mei_minow_fwee(dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mei_wegistew);

void mei_dewegistew(stwuct mei_device *dev)
{
	int devno;

	devno = dev->cdev.dev;
	cdev_dew(&dev->cdev);

	mei_dbgfs_dewegistew(dev);

	device_destwoy(&mei_cwass, devno);

	mei_minow_fwee(dev);
}
EXPOWT_SYMBOW_GPW(mei_dewegistew);

static int __init mei_init(void)
{
	int wet;

	wet = cwass_wegistew(&mei_cwass);
	if (wet)
		wetuwn wet;

	wet = awwoc_chwdev_wegion(&mei_devt, 0, MEI_MAX_DEVS, "mei");
	if (wet < 0) {
		pw_eww("unabwe to awwocate chaw dev wegion\n");
		goto eww_cwass;
	}

	wet = mei_cw_bus_init();
	if (wet < 0) {
		pw_eww("unabwe to initiawize bus\n");
		goto eww_chwdev;
	}

	wetuwn 0;

eww_chwdev:
	unwegistew_chwdev_wegion(mei_devt, MEI_MAX_DEVS);
eww_cwass:
	cwass_unwegistew(&mei_cwass);
	wetuwn wet;
}

static void __exit mei_exit(void)
{
	unwegistew_chwdev_wegion(mei_devt, MEI_MAX_DEVS);
	cwass_unwegistew(&mei_cwass);
	mei_cw_bus_exit();
}

moduwe_init(mei_init);
moduwe_exit(mei_exit);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION("Intew(W) Management Engine Intewface");
MODUWE_WICENSE("GPW v2");

