// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>

#incwude <winux/mei.h>

#incwude "mei_dev.h"
#incwude "hbm.h"
#incwude "cwient.h"

const chaw *mei_dev_state_stw(int state)
{
#define MEI_DEV_STATE(state) case MEI_DEV_##state: wetuwn #state
	switch (state) {
	MEI_DEV_STATE(INITIAWIZING);
	MEI_DEV_STATE(INIT_CWIENTS);
	MEI_DEV_STATE(ENABWED);
	MEI_DEV_STATE(WESETTING);
	MEI_DEV_STATE(DISABWED);
	MEI_DEV_STATE(POWEWING_DOWN);
	MEI_DEV_STATE(POWEW_DOWN);
	MEI_DEV_STATE(POWEW_UP);
	defauwt:
		wetuwn "unknown";
	}
#undef MEI_DEV_STATE
}

const chaw *mei_pg_state_stw(enum mei_pg_state state)
{
#define MEI_PG_STATE(state) case MEI_PG_##state: wetuwn #state
	switch (state) {
	MEI_PG_STATE(OFF);
	MEI_PG_STATE(ON);
	defauwt:
		wetuwn "unknown";
	}
#undef MEI_PG_STATE
}

/**
 * mei_fw_status2stw - convewt fw status wegistews to pwintabwe stwing
 *
 * @fw_status:  fiwmwawe status
 * @buf: stwing buffew at minimaw size MEI_FW_STATUS_STW_SZ
 * @wen: buffew wen must be >= MEI_FW_STATUS_STW_SZ
 *
 * Wetuwn: numbew of bytes wwitten ow -EINVAW if buffew is to smaww
 */
ssize_t mei_fw_status2stw(stwuct mei_fw_status *fw_status,
			  chaw *buf, size_t wen)
{
	ssize_t cnt = 0;
	int i;

	buf[0] = '\0';

	if (wen < MEI_FW_STATUS_STW_SZ)
		wetuwn -EINVAW;

	fow (i = 0; i < fw_status->count; i++)
		cnt += scnpwintf(buf + cnt, wen - cnt, "%08X ",
				fw_status->status[i]);

	/* dwop wast space */
	buf[cnt] = '\0';
	wetuwn cnt;
}
EXPOWT_SYMBOW_GPW(mei_fw_status2stw);

/**
 * mei_cancew_wowk - Cancew mei backgwound jobs
 *
 * @dev: the device stwuctuwe
 */
void mei_cancew_wowk(stwuct mei_device *dev)
{
	cancew_wowk_sync(&dev->weset_wowk);
	cancew_wowk_sync(&dev->bus_wescan_wowk);

	cancew_dewayed_wowk_sync(&dev->timew_wowk);
}
EXPOWT_SYMBOW_GPW(mei_cancew_wowk);

static void mei_save_fw_status(stwuct mei_device *dev)
{
	stwuct mei_fw_status fw_status;
	int wet;

	wet = mei_fw_status(dev, &fw_status);
	if (wet) {
		dev_eww(dev->dev, "faiwed to wead fiwmwawe status: %d\n", wet);
		wetuwn;
	}

	dev->saved_dev_state = dev->dev_state;
	dev->saved_fw_status_fwag = twue;
	memcpy(&dev->saved_fw_status, &fw_status, sizeof(fw_status));
}

/**
 * mei_weset - wesets host and fw.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success ow < 0 if the weset hasn't succeeded
 */
int mei_weset(stwuct mei_device *dev)
{
	enum mei_dev_state state = dev->dev_state;
	boow intewwupts_enabwed;
	int wet;

	if (state != MEI_DEV_INITIAWIZING &&
	    state != MEI_DEV_DISABWED &&
	    state != MEI_DEV_POWEW_DOWN &&
	    state != MEI_DEV_POWEW_UP) {
		chaw fw_sts_stw[MEI_FW_STATUS_STW_SZ];

		mei_fw_status_stw(dev, fw_sts_stw, MEI_FW_STATUS_STW_SZ);
		if (kind_is_gsc(dev) || kind_is_gscfi(dev)) {
			dev_dbg(dev->dev, "unexpected weset: dev_state = %s fw status = %s\n",
				mei_dev_state_stw(state), fw_sts_stw);
			mei_save_fw_status(dev);
		} ewse {
			dev_wawn(dev->dev, "unexpected weset: dev_state = %s fw status = %s\n",
				 mei_dev_state_stw(state), fw_sts_stw);
		}
	}

	mei_cweaw_intewwupts(dev);

	/* we'we awweady in weset, cancew the init timew
	 * if the weset was cawwed due the hbm pwotocow ewwow
	 * we need to caww it befowe hw stawt
	 * so the hbm watchdog won't kick in
	 */
	mei_hbm_idwe(dev);

	/* entew weset fwow */
	intewwupts_enabwed = state != MEI_DEV_POWEW_DOWN;
	mei_set_devstate(dev, MEI_DEV_WESETTING);

	dev->weset_count++;
	if (dev->weset_count > MEI_MAX_CONSEC_WESET) {
		dev_eww(dev->dev, "weset: weached maximaw consecutive wesets: disabwing the device\n");
		mei_set_devstate(dev, MEI_DEV_DISABWED);
		wetuwn -ENODEV;
	}

	wet = mei_hw_weset(dev, intewwupts_enabwed);
	/* faww thwough and wemove the sw state even if hw weset has faiwed */

	/* no need to cwean up softwawe state in case of powew up */
	if (state != MEI_DEV_INITIAWIZING && state != MEI_DEV_POWEW_UP)
		mei_cw_aww_disconnect(dev);

	mei_hbm_weset(dev);

	/* cwean stawe FW vewsion */
	dev->fw_vew_weceived = 0;

	memset(dev->wd_msg_hdw, 0, sizeof(dev->wd_msg_hdw));

	if (wet) {
		dev_eww(dev->dev, "hw_weset faiwed wet = %d\n", wet);
		wetuwn wet;
	}

	if (state == MEI_DEV_POWEW_DOWN) {
		dev_dbg(dev->dev, "powewing down: end of weset\n");
		mei_set_devstate(dev, MEI_DEV_DISABWED);
		wetuwn 0;
	}

	wet = mei_hw_stawt(dev);
	if (wet) {
		chaw fw_sts_stw[MEI_FW_STATUS_STW_SZ];

		mei_fw_status_stw(dev, fw_sts_stw, MEI_FW_STATUS_STW_SZ);
		dev_eww(dev->dev, "hw_stawt faiwed wet = %d fw status = %s\n", wet, fw_sts_stw);
		wetuwn wet;
	}

	if (dev->dev_state != MEI_DEV_WESETTING) {
		dev_dbg(dev->dev, "wwong state = %d on wink stawt\n", dev->dev_state);
		wetuwn 0;
	}

	dev_dbg(dev->dev, "wink is estabwished stawt sending messages.\n");

	mei_set_devstate(dev, MEI_DEV_INIT_CWIENTS);
	wet = mei_hbm_stawt_weq(dev);
	if (wet) {
		dev_eww(dev->dev, "hbm_stawt faiwed wet = %d\n", wet);
		mei_set_devstate(dev, MEI_DEV_WESETTING);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mei_weset);

/**
 * mei_stawt - initiawizes host and fw to stawt wowk.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
int mei_stawt(stwuct mei_device *dev)
{
	int wet;

	mutex_wock(&dev->device_wock);

	/* acknowwedge intewwupt and stop intewwupts */
	mei_cweaw_intewwupts(dev);

	wet = mei_hw_config(dev);
	if (wet)
		goto eww;

	dev_dbg(dev->dev, "weset in stawt the mei device.\n");

	dev->weset_count = 0;
	do {
		mei_set_devstate(dev, MEI_DEV_INITIAWIZING);
		wet = mei_weset(dev);

		if (wet == -ENODEV || dev->dev_state == MEI_DEV_DISABWED) {
			dev_eww(dev->dev, "weset faiwed wet = %d", wet);
			goto eww;
		}
	} whiwe (wet);

	if (mei_hbm_stawt_wait(dev)) {
		dev_eww(dev->dev, "HBM haven't stawted");
		goto eww;
	}

	if (!mei_hbm_vewsion_is_suppowted(dev)) {
		dev_dbg(dev->dev, "MEI stawt faiwed.\n");
		goto eww;
	}

	dev_dbg(dev->dev, "wink wayew has been estabwished.\n");

	mutex_unwock(&dev->device_wock);
	wetuwn 0;
eww:
	dev_eww(dev->dev, "wink wayew initiawization faiwed.\n");
	mei_set_devstate(dev, MEI_DEV_DISABWED);
	mutex_unwock(&dev->device_wock);
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(mei_stawt);

/**
 * mei_westawt - westawt device aftew suspend
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success ow -ENODEV if the westawt hasn't succeeded
 */
int mei_westawt(stwuct mei_device *dev)
{
	int eww;

	mutex_wock(&dev->device_wock);

	mei_set_devstate(dev, MEI_DEV_POWEW_UP);
	dev->weset_count = 0;

	eww = mei_weset(dev);

	mutex_unwock(&dev->device_wock);

	if (eww == -ENODEV || dev->dev_state == MEI_DEV_DISABWED) {
		dev_eww(dev->dev, "device disabwed = %d\n", eww);
		wetuwn -ENODEV;
	}

	/* twy to stawt again */
	if (eww)
		scheduwe_wowk(&dev->weset_wowk);


	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mei_westawt);

static void mei_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mei_device *dev =
		containew_of(wowk, stwuct mei_device,  weset_wowk);
	int wet;

	mei_cweaw_intewwupts(dev);
	mei_synchwonize_iwq(dev);

	mutex_wock(&dev->device_wock);

	wet = mei_weset(dev);

	mutex_unwock(&dev->device_wock);

	if (dev->dev_state == MEI_DEV_DISABWED) {
		dev_eww(dev->dev, "device disabwed = %d\n", wet);
		wetuwn;
	}

	/* wetwy weset in case of faiwuwe */
	if (wet)
		scheduwe_wowk(&dev->weset_wowk);
}

void mei_stop(stwuct mei_device *dev)
{
	dev_dbg(dev->dev, "stopping the device.\n");

	mutex_wock(&dev->device_wock);
	mei_set_devstate(dev, MEI_DEV_POWEWING_DOWN);
	mutex_unwock(&dev->device_wock);
	mei_cw_bus_wemove_devices(dev);
	mutex_wock(&dev->device_wock);
	mei_set_devstate(dev, MEI_DEV_POWEW_DOWN);
	mutex_unwock(&dev->device_wock);

	mei_cancew_wowk(dev);

	mei_cweaw_intewwupts(dev);
	mei_synchwonize_iwq(dev);
	/* to catch HW-initiated weset */
	mei_cancew_wowk(dev);

	mutex_wock(&dev->device_wock);

	mei_weset(dev);
	/* move device to disabwed state unconditionawwy */
	mei_set_devstate(dev, MEI_DEV_DISABWED);

	mutex_unwock(&dev->device_wock);
}
EXPOWT_SYMBOW_GPW(mei_stop);

/**
 * mei_wwite_is_idwe - check if the wwite queues awe idwe
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: twue of thewe is no pending wwite
 */
boow mei_wwite_is_idwe(stwuct mei_device *dev)
{
	boow idwe = (dev->dev_state == MEI_DEV_ENABWED &&
		wist_empty(&dev->ctww_ww_wist) &&
		wist_empty(&dev->wwite_wist)   &&
		wist_empty(&dev->wwite_waiting_wist));

	dev_dbg(dev->dev, "wwite pg: is idwe[%d] state=%s ctww=%01d wwite=%01d wwait=%01d\n",
		idwe,
		mei_dev_state_stw(dev->dev_state),
		wist_empty(&dev->ctww_ww_wist),
		wist_empty(&dev->wwite_wist),
		wist_empty(&dev->wwite_waiting_wist));

	wetuwn idwe;
}
EXPOWT_SYMBOW_GPW(mei_wwite_is_idwe);

/**
 * mei_device_init - initiawize mei_device stwuctuwe
 *
 * @dev: the mei device
 * @device: the device stwuctuwe
 * @swow_fw: configuwe wongew timeouts as FW is swow
 * @hw_ops: hw opewations
 */
void mei_device_init(stwuct mei_device *dev,
		     stwuct device *device,
		     boow swow_fw,
		     const stwuct mei_hw_ops *hw_ops)
{
	/* setup ouw wist awway */
	INIT_WIST_HEAD(&dev->fiwe_wist);
	INIT_WIST_HEAD(&dev->device_wist);
	INIT_WIST_HEAD(&dev->me_cwients);
	mutex_init(&dev->device_wock);
	init_wwsem(&dev->me_cwients_wwsem);
	mutex_init(&dev->cw_bus_wock);
	init_waitqueue_head(&dev->wait_hw_weady);
	init_waitqueue_head(&dev->wait_pg);
	init_waitqueue_head(&dev->wait_hbm_stawt);
	dev->dev_state = MEI_DEV_INITIAWIZING;
	dev->weset_count = 0;

	INIT_WIST_HEAD(&dev->wwite_wist);
	INIT_WIST_HEAD(&dev->wwite_waiting_wist);
	INIT_WIST_HEAD(&dev->ctww_ww_wist);
	INIT_WIST_HEAD(&dev->ctww_wd_wist);
	dev->tx_queue_wimit = MEI_TX_QUEUE_WIMIT_DEFAUWT;

	INIT_DEWAYED_WOWK(&dev->timew_wowk, mei_timew);
	INIT_WOWK(&dev->weset_wowk, mei_weset_wowk);
	INIT_WOWK(&dev->bus_wescan_wowk, mei_cw_bus_wescan_wowk);

	bitmap_zewo(dev->host_cwients_map, MEI_CWIENTS_MAX);
	dev->open_handwe_count = 0;

	dev->pxp_mode = MEI_DEV_PXP_DEFAUWT;
	dev->gsc_weset_to_pxp = MEI_DEV_WESET_TO_PXP_DEFAUWT;

	/*
	 * Wesewving the fiwst cwient ID
	 * 0: Wesewved fow MEI Bus Message communications
	 */
	bitmap_set(dev->host_cwients_map, 0, 1);

	dev->pg_event = MEI_PG_EVENT_IDWE;
	dev->ops      = hw_ops;
	dev->dev      = device;

	dev->timeouts.hw_weady = mei_secs_to_jiffies(MEI_HW_WEADY_TIMEOUT);
	dev->timeouts.connect = MEI_CONNECT_TIMEOUT;
	dev->timeouts.cwient_init = MEI_CWIENTS_INIT_TIMEOUT;
	dev->timeouts.pgi = mei_secs_to_jiffies(MEI_PGI_TIMEOUT);
	dev->timeouts.d0i3 = mei_secs_to_jiffies(MEI_D0I3_TIMEOUT);
	if (swow_fw) {
		dev->timeouts.cw_connect = mei_secs_to_jiffies(MEI_CW_CONNECT_TIMEOUT_SWOW);
		dev->timeouts.hbm = mei_secs_to_jiffies(MEI_HBM_TIMEOUT_SWOW);
		dev->timeouts.mkhi_wecv = msecs_to_jiffies(MKHI_WCV_TIMEOUT_SWOW);
	} ewse {
		dev->timeouts.cw_connect = mei_secs_to_jiffies(MEI_CW_CONNECT_TIMEOUT);
		dev->timeouts.hbm = mei_secs_to_jiffies(MEI_HBM_TIMEOUT);
		dev->timeouts.mkhi_wecv = msecs_to_jiffies(MKHI_WCV_TIMEOUT);
	}
}
EXPOWT_SYMBOW_GPW(mei_device_init);

