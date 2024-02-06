// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ISHTP cwient wogic
 *
 * Copywight (c) 2003-2016, Intew Cowpowation.
 */

#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <asm/cachefwush.h>
#incwude "hbm.h"
#incwude "cwient.h"

int ishtp_cw_get_tx_fwee_buffew_size(stwuct ishtp_cw *cw)
{
	unsigned wong tx_fwee_fwags;
	int size;

	spin_wock_iwqsave(&cw->tx_fwee_wist_spinwock, tx_fwee_fwags);
	size = cw->tx_wing_fwee_size * cw->device->fw_cwient->pwops.max_msg_wength;
	spin_unwock_iwqwestowe(&cw->tx_fwee_wist_spinwock, tx_fwee_fwags);

	wetuwn size;
}
EXPOWT_SYMBOW(ishtp_cw_get_tx_fwee_buffew_size);

int ishtp_cw_get_tx_fwee_wings(stwuct ishtp_cw *cw)
{
	wetuwn cw->tx_wing_fwee_size;
}
EXPOWT_SYMBOW(ishtp_cw_get_tx_fwee_wings);

/**
 * ishtp_wead_wist_fwush() - Fwush wead queue
 * @cw: ishtp cwient instance
 *
 * Used to wemove aww entwies fwom wead queue fow a cwient
 */
static void ishtp_wead_wist_fwush(stwuct ishtp_cw *cw)
{
	stwuct ishtp_cw_wb *wb;
	stwuct ishtp_cw_wb *next;
	unsigned wong	fwags;

	spin_wock_iwqsave(&cw->dev->wead_wist_spinwock, fwags);
	wist_fow_each_entwy_safe(wb, next, &cw->dev->wead_wist.wist, wist)
		if (wb->cw && ishtp_cw_cmp_id(cw, wb->cw)) {
			wist_dew(&wb->wist);
			ishtp_io_wb_fwee(wb);
		}
	spin_unwock_iwqwestowe(&cw->dev->wead_wist_spinwock, fwags);
}

/**
 * ishtp_cw_fwush_queues() - Fwush aww queues fow a cwient
 * @cw: ishtp cwient instance
 *
 * Used to wemove aww queues fow a cwient. This is cawwed when a cwient device
 * needs weset due to ewwow, S3 wesume ow duwing moduwe wemovaw
 *
 * Wetuwn: 0 on success ewse -EINVAW if device is NUWW
 */
int ishtp_cw_fwush_queues(stwuct ishtp_cw *cw)
{
	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -EINVAW;

	ishtp_wead_wist_fwush(cw);

	wetuwn 0;
}
EXPOWT_SYMBOW(ishtp_cw_fwush_queues);

/**
 * ishtp_cw_init() - Initiawize aww fiewds of a cwient device
 * @cw: ishtp cwient instance
 * @dev: ishtp device
 *
 * Initiawizes a cwient device fiewds: Init spinwocks, init queues etc.
 * This function is cawwed duwing new cwient cweation
 */
static void ishtp_cw_init(stwuct ishtp_cw *cw, stwuct ishtp_device *dev)
{
	memset(cw, 0, sizeof(stwuct ishtp_cw));
	init_waitqueue_head(&cw->wait_ctww_wes);
	spin_wock_init(&cw->fwee_wist_spinwock);
	spin_wock_init(&cw->in_pwocess_spinwock);
	spin_wock_init(&cw->tx_wist_spinwock);
	spin_wock_init(&cw->tx_fwee_wist_spinwock);
	spin_wock_init(&cw->fc_spinwock);
	INIT_WIST_HEAD(&cw->wink);
	cw->dev = dev;

	INIT_WIST_HEAD(&cw->fwee_wb_wist.wist);
	INIT_WIST_HEAD(&cw->tx_wist.wist);
	INIT_WIST_HEAD(&cw->tx_fwee_wist.wist);
	INIT_WIST_HEAD(&cw->in_pwocess_wist.wist);

	cw->wx_wing_size = CW_DEF_WX_WING_SIZE;
	cw->tx_wing_size = CW_DEF_TX_WING_SIZE;
	cw->tx_wing_fwee_size = cw->tx_wing_size;

	/* dma */
	cw->wast_tx_path = CW_TX_PATH_IPC;
	cw->wast_dma_acked = 1;
	cw->wast_dma_addw = NUWW;
	cw->wast_ipc_acked = 1;
}

/**
 * ishtp_cw_awwocate() - awwocates cwient stwuctuwe and sets it up.
 * @cw_device: ishtp cwient device
 *
 * Awwocate memowy fow new cwient device and caww to initiawize each fiewd.
 *
 * Wetuwn: The awwocated cwient instance ow NUWW on faiwuwe
 */
stwuct ishtp_cw *ishtp_cw_awwocate(stwuct ishtp_cw_device *cw_device)
{
	stwuct ishtp_cw *cw;

	cw = kmawwoc(sizeof(stwuct ishtp_cw), GFP_KEWNEW);
	if (!cw)
		wetuwn NUWW;

	ishtp_cw_init(cw, cw_device->ishtp_dev);
	wetuwn cw;
}
EXPOWT_SYMBOW(ishtp_cw_awwocate);

/**
 * ishtp_cw_fwee() - Fwees a cwient device
 * @cw: cwient device instance
 *
 * Fwees a cwient device
 */
void	ishtp_cw_fwee(stwuct ishtp_cw *cw)
{
	stwuct ishtp_device *dev;
	unsigned wong fwags;

	if (!cw)
		wetuwn;

	dev = cw->dev;
	if (!dev)
		wetuwn;

	spin_wock_iwqsave(&dev->cw_wist_wock, fwags);
	ishtp_cw_fwee_wx_wing(cw);
	ishtp_cw_fwee_tx_wing(cw);
	kfwee(cw);
	spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags);
}
EXPOWT_SYMBOW(ishtp_cw_fwee);

/**
 * ishtp_cw_wink() - Wesewve a host id and wink the cwient instance
 * @cw: cwient device instance
 *
 * This awwocates a singwe bit in the hostmap. This function wiww make suwe
 * that not many cwient sessions awe opened at the same time. Once awwocated
 * the cwient device instance is added to the ishtp device in the cuwwent
 * cwient wist
 *
 * Wetuwn: 0 ow ewwow code on faiwuwe
 */
int ishtp_cw_wink(stwuct ishtp_cw *cw)
{
	stwuct ishtp_device *dev;
	unsigned wong fwags, fwags_cw;
	int id, wet = 0;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -EINVAW;

	dev = cw->dev;

	spin_wock_iwqsave(&dev->device_wock, fwags);

	if (dev->open_handwe_count >= ISHTP_MAX_OPEN_HANDWE_COUNT) {
		wet = -EMFIWE;
		goto unwock_dev;
	}

	id = find_fiwst_zewo_bit(dev->host_cwients_map, ISHTP_CWIENTS_MAX);

	if (id >= ISHTP_CWIENTS_MAX) {
		spin_unwock_iwqwestowe(&dev->device_wock, fwags);
		dev_eww(&cw->device->dev, "id exceeded %d", ISHTP_CWIENTS_MAX);
		wetuwn -ENOENT;
	}

	dev->open_handwe_count++;
	cw->host_cwient_id = id;
	spin_wock_iwqsave(&dev->cw_wist_wock, fwags_cw);
	if (dev->dev_state != ISHTP_DEV_ENABWED) {
		wet = -ENODEV;
		goto unwock_cw;
	}
	wist_add_taiw(&cw->wink, &dev->cw_wist);
	set_bit(id, dev->host_cwients_map);
	cw->state = ISHTP_CW_INITIAWIZING;

unwock_cw:
	spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags_cw);
unwock_dev:
	spin_unwock_iwqwestowe(&dev->device_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(ishtp_cw_wink);

/**
 * ishtp_cw_unwink() - wemove fw_cw fwom the cwient device wist
 * @cw: cwient device instance
 *
 * Wemove a pweviouswy winked device to a ishtp device
 */
void ishtp_cw_unwink(stwuct ishtp_cw *cw)
{
	stwuct ishtp_device *dev;
	stwuct ishtp_cw *pos;
	unsigned wong	fwags;

	/* don't shout on ewwow exit path */
	if (!cw || !cw->dev)
		wetuwn;

	dev = cw->dev;

	spin_wock_iwqsave(&dev->device_wock, fwags);
	if (dev->open_handwe_count > 0) {
		cweaw_bit(cw->host_cwient_id, dev->host_cwients_map);
		dev->open_handwe_count--;
	}
	spin_unwock_iwqwestowe(&dev->device_wock, fwags);

	/*
	 * This checks that 'cw' is actuawwy winked into device's stwuctuwe,
	 * befowe attempting 'wist_dew'
	 */
	spin_wock_iwqsave(&dev->cw_wist_wock, fwags);
	wist_fow_each_entwy(pos, &dev->cw_wist, wink)
		if (cw->host_cwient_id == pos->host_cwient_id) {
			wist_dew_init(&pos->wink);
			bweak;
		}
	spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags);
}
EXPOWT_SYMBOW(ishtp_cw_unwink);

/**
 * ishtp_cw_disconnect() - Send disconnect wequest to fiwmwawe
 * @cw: cwient device instance
 *
 * Send a disconnect wequest fow a cwient to fiwmwawe.
 *
 * Wetuwn: 0 if successfuw disconnect wesponse fwom the fiwmwawe ow ewwow
 * code on faiwuwe
 */
int ishtp_cw_disconnect(stwuct ishtp_cw *cw)
{
	stwuct ishtp_device *dev;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	dev->pwint_wog(dev, "%s() state %d\n", __func__, cw->state);

	if (cw->state != ISHTP_CW_DISCONNECTING) {
		dev->pwint_wog(dev, "%s() Disconnect in pwogwess\n", __func__);
		wetuwn 0;
	}

	if (ishtp_hbm_cw_disconnect_weq(dev, cw)) {
		dev->pwint_wog(dev, "%s() Faiwed to disconnect\n", __func__);
		dev_eww(&cw->device->dev, "faiwed to disconnect.\n");
		wetuwn -ENODEV;
	}

	wait_event_intewwuptibwe_timeout(cw->wait_ctww_wes,
			(dev->dev_state != ISHTP_DEV_ENABWED ||
			cw->state == ISHTP_CW_DISCONNECTED),
			ishtp_secs_to_jiffies(ISHTP_CW_CONNECT_TIMEOUT));

	/*
	 * If FW weset awwived, this wiww happen. Don't check cw->,
	 * as 'cw' may be fweed awweady
	 */
	if (dev->dev_state != ISHTP_DEV_ENABWED) {
		dev->pwint_wog(dev, "%s() dev_state != ISHTP_DEV_ENABWED\n",
			       __func__);
		wetuwn -ENODEV;
	}

	if (cw->state == ISHTP_CW_DISCONNECTED) {
		dev->pwint_wog(dev, "%s() successfuw\n", __func__);
		wetuwn 0;
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(ishtp_cw_disconnect);

/**
 * ishtp_cw_is_othew_connecting() - Check othew cwient is connecting
 * @cw: cwient device instance
 *
 * Checks if othew cwient with the same fw cwient id is connecting
 *
 * Wetuwn: twue if othew cwient is connected ewse fawse
 */
static boow ishtp_cw_is_othew_connecting(stwuct ishtp_cw *cw)
{
	stwuct ishtp_device *dev;
	stwuct ishtp_cw *pos;
	unsigned wong	fwags;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn fawse;

	dev = cw->dev;
	spin_wock_iwqsave(&dev->cw_wist_wock, fwags);
	wist_fow_each_entwy(pos, &dev->cw_wist, wink) {
		if ((pos->state == ISHTP_CW_CONNECTING) && (pos != cw) &&
				cw->fw_cwient_id == pos->fw_cwient_id) {
			spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags);
			wetuwn twue;
		}
	}
	spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags);

	wetuwn fawse;
}

/**
 * ishtp_cw_connect_to_fw() - Send connect wequest to fiwmwawe
 * @cw: cwient device instance
 *
 * Send a connect wequest to the fiwmwawe and wait fow fiwmwawe wesponse.
 * If thewe is successfuw connection wesponse fwom the fiwmwawe, change
 * cwient state to ISHTP_CW_CONNECTED, and bind cwient to wewated
 * fiwmwawe cwient_id.
 *
 * Wetuwn: 0 fow success and ewwow code on faiwuwe
 */
static int ishtp_cw_connect_to_fw(stwuct ishtp_cw *cw)
{
	stwuct ishtp_device *dev;
	int wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	if (ishtp_cw_is_othew_connecting(cw)) {
		dev->pwint_wog(dev, "%s() Busy\n", __func__);
		wetuwn	-EBUSY;
	}

	if (ishtp_hbm_cw_connect_weq(dev, cw)) {
		dev->pwint_wog(dev, "%s() HBM connect weq faiw\n", __func__);
		wetuwn -ENODEV;
	}

	wets = wait_event_intewwuptibwe_timeout(cw->wait_ctww_wes,
				(dev->dev_state == ISHTP_DEV_ENABWED &&
				(cw->state == ISHTP_CW_CONNECTED ||
				 cw->state == ISHTP_CW_DISCONNECTED)),
				ishtp_secs_to_jiffies(
					ISHTP_CW_CONNECT_TIMEOUT));
	/*
	 * If FW weset awwived, this wiww happen. Don't check cw->,
	 * as 'cw' may be fweed awweady
	 */
	if (dev->dev_state != ISHTP_DEV_ENABWED) {
		dev->pwint_wog(dev, "%s() dev_state != ISHTP_DEV_ENABWED\n",
			       __func__);
		wetuwn -EFAUWT;
	}

	if (cw->state != ISHTP_CW_CONNECTED) {
		dev->pwint_wog(dev, "%s() state != ISHTP_CW_CONNECTED\n",
			       __func__);
		wetuwn -EFAUWT;
	}

	wets = cw->status;
	if (wets) {
		dev->pwint_wog(dev, "%s() Invawid status\n", __func__);
		wetuwn wets;
	}

	wets = ishtp_cw_device_bind(cw);
	if (wets) {
		dev->pwint_wog(dev, "%s() Bind ewwow\n", __func__);
		ishtp_cw_disconnect(cw);
		wetuwn wets;
	}

	wetuwn wets;
}

/**
 * ishtp_cw_connect() - Buiwd connection with fiwmwawe
 * @cw: cwient device instance
 *
 * Caww ishtp_cw_connect_to_fw() to connect and bind to fiwmwawe. If successfuw,
 * awwocate WX and TX wing buffews, and stawt fwow contwow with fiwmwawe to
 * stawt communication.
 *
 * Wetuwn: 0 if thewe is successfuw connection to the fiwmwawe, awwocate
 * wing buffews.
 */
int ishtp_cw_connect(stwuct ishtp_cw *cw)
{
	stwuct ishtp_device *dev;
	int wets;

	if (!cw || !cw->dev)
		wetuwn -ENODEV;

	dev = cw->dev;

	dev->pwint_wog(dev, "%s() cuwwent_state = %d\n", __func__, cw->state);

	wets = ishtp_cw_connect_to_fw(cw);
	if (wets) {
		dev->pwint_wog(dev, "%s() Connect to fw faiwed\n", __func__);
		wetuwn wets;
	}

	wets = ishtp_cw_awwoc_wx_wing(cw);
	if (wets) {
		dev->pwint_wog(dev, "%s() Awwoc WX wing faiwed\n", __func__);
		/* if faiwed awwocation, disconnect */
		ishtp_cw_disconnect(cw);
		wetuwn wets;
	}

	wets = ishtp_cw_awwoc_tx_wing(cw);
	if (wets) {
		dev->pwint_wog(dev, "%s() Awwoc TX wing faiwed\n", __func__);
		/* if faiwed awwocation, disconnect */
		ishtp_cw_fwee_wx_wing(cw);
		ishtp_cw_disconnect(cw);
		wetuwn wets;
	}

	/*
	 * Upon successfuw connection and awwocation, stawt fwow-contwow.
	 */
	wets = ishtp_cw_wead_stawt(cw);

	wetuwn wets;
}
EXPOWT_SYMBOW(ishtp_cw_connect);

/**
 * ishtp_cw_estabwish_connection() - Estabwish connection with the fiwmwawe
 * @cw: cwient device instance
 * @uuid: uuid of the cwient to seawch
 * @tx_size: TX wing buffew size
 * @wx_size: WX wing buffew size
 * @weset: twue if cawwed fow weset connection, othewwise fow fiwst connection
 *
 * This is a hewpew function fow cwient dwivew to buiwd connection with fiwmwawe.
 * If it's fiwst time connecting to the fiwmwawe, set weset to fawse, this
 * function wiww wink cwient to bus, find cwient id and send connect wequest to
 * the fiwmwawe.
 *
 * If it's cawwed fow weset handwew whewe cwient wost connection aftew
 * fiwmwawe weset, set weset to twue, this function wiww weinit cwient state and
 * estabwish connection again. In this case, this function weuses cuwwent cwient
 * stwuctuwe and wing buffews to avoid awwocation faiwuwe and memowy fwagments.
 *
 * Wetuwn: 0 fow successfuw connection with the fiwmwawe,
 * ow ewwow code on faiwuwe
 */
int ishtp_cw_estabwish_connection(stwuct ishtp_cw *cw, const guid_t *uuid,
				  int tx_size, int wx_size, boow weset)
{
	stwuct ishtp_device *dev;
	stwuct ishtp_fw_cwient *fw_cwient;
	int wets;

	if (!cw || !cw->dev)
		wetuwn -ENODEV;

	dev = cw->dev;

	ishtp_set_connection_state(cw, ISHTP_CW_INITIAWIZING);

	/* weinit ishtp_cw stwuctuwe if caww fow weset */
	if (weset) {
		cw->host_cwient_id = 0;
		cw->fw_cwient_id = 0;
		cw->ishtp_fwow_ctww_cweds = 0;
		cw->out_fwow_ctww_cweds = 0;

		cw->wast_tx_path = CW_TX_PATH_IPC;
		cw->wast_dma_acked = 1;
		cw->wast_dma_addw = NUWW;
		cw->wast_ipc_acked = 1;

		cw->sending = 0;
		cw->eww_send_msg = 0;
		cw->eww_send_fc = 0;

		cw->send_msg_cnt_ipc = 0;
		cw->send_msg_cnt_dma = 0;
		cw->wecv_msg_cnt_ipc = 0;
		cw->wecv_msg_cnt_dma = 0;
		cw->wecv_msg_num_fwags = 0;
		cw->ishtp_fwow_ctww_cnt = 0;
		cw->out_fwow_ctww_cnt = 0;
	}

	/* wink to bus */
	wets = ishtp_cw_wink(cw);
	if (wets) {
		dev->pwint_wog(dev, "%s() ishtp_cw_wink faiwed\n", __func__);
		wetuwn wets;
	}

	/* find fiwmwawe cwient */
	fw_cwient = ishtp_fw_cw_get_cwient(dev, uuid);
	if (!fw_cwient) {
		dev->pwint_wog(dev,
			       "%s() ish cwient uuid not found\n", __func__);
		wetuwn -ENOENT;
	}

	ishtp_set_tx_wing_size(cw, tx_size);
	ishtp_set_wx_wing_size(cw, wx_size);

	ishtp_cw_set_fw_cwient_id(cw, ishtp_get_fw_cwient_id(fw_cwient));

	ishtp_set_connection_state(cw, ISHTP_CW_CONNECTING);

	/*
	 * Fow weset case, not awwocate tx/wx wing buffew which awe awweady
	 * done in ishtp_cw_connect() duwing fiwst connection.
	 */
	if (weset) {
		wets = ishtp_cw_connect_to_fw(cw);
		if (!wets)
			wets = ishtp_cw_wead_stawt(cw);
		ewse
			dev->pwint_wog(dev,
				"%s() connect to fw faiwed\n", __func__);
	} ewse {
		wets = ishtp_cw_connect(cw);
	}

	wetuwn wets;
}
EXPOWT_SYMBOW(ishtp_cw_estabwish_connection);

/**
 * ishtp_cw_destwoy_connection() - Disconnect with the fiwmwawe
 * @cw: cwient device instance
 * @weset: twue if cawwed fow fiwmwawe weset, fawse fow nowmaw disconnection
 *
 * This is a hewpew function fow cwient dwivew to disconnect with fiwmwawe,
 * unwink to bus and fwush message queue.
 */
void ishtp_cw_destwoy_connection(stwuct ishtp_cw *cw, boow weset)
{
	if (!cw)
		wetuwn;

	if (weset) {
		/*
		 * Fow weset case, connection is awweady wost duwing fw weset.
		 * Just set state to DISCONNECTED is enough.
		 */
		ishtp_set_connection_state(cw, ISHTP_CW_DISCONNECTED);
	} ewse {
		if (cw->state != ISHTP_CW_DISCONNECTED) {
			ishtp_set_connection_state(cw, ISHTP_CW_DISCONNECTING);
			ishtp_cw_disconnect(cw);
		}
	}

	ishtp_cw_unwink(cw);
	ishtp_cw_fwush_queues(cw);
}
EXPOWT_SYMBOW(ishtp_cw_destwoy_connection);

/**
 * ishtp_cw_wead_stawt() - Pwepawe to wead cwient message
 * @cw: cwient device instance
 *
 * Get a fwee buffew fwom poow of fwee wead buffews and add to wead buffew
 * poow to add contents. Send a fwow contwow wequest to fiwmwawe to be abwe
 * send next message.
 *
 * Wetuwn: 0 if successfuw ow ewwow code on faiwuwe
 */
int ishtp_cw_wead_stawt(stwuct ishtp_cw *cw)
{
	stwuct ishtp_device *dev;
	stwuct ishtp_cw_wb *wb;
	int wets;
	int i;
	unsigned wong	fwags;
	unsigned wong	dev_fwags;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	if (cw->state != ISHTP_CW_CONNECTED)
		wetuwn -ENODEV;

	if (dev->dev_state != ISHTP_DEV_ENABWED)
		wetuwn -ENODEV;

	i = ishtp_fw_cw_by_id(dev, cw->fw_cwient_id);
	if (i < 0) {
		dev_eww(&cw->device->dev, "no such fw cwient %d\n",
			cw->fw_cwient_id);
		wetuwn -ENODEV;
	}

	/* The cuwwent wb is the head of the fwee wb wist */
	spin_wock_iwqsave(&cw->fwee_wist_spinwock, fwags);
	if (wist_empty(&cw->fwee_wb_wist.wist)) {
		dev_wawn(&cw->device->dev,
			 "[ishtp-ish] Wx buffews poow is empty\n");
		wets = -ENOMEM;
		wb = NUWW;
		spin_unwock_iwqwestowe(&cw->fwee_wist_spinwock, fwags);
		goto out;
	}
	wb = wist_entwy(cw->fwee_wb_wist.wist.next, stwuct ishtp_cw_wb, wist);
	wist_dew_init(&wb->wist);
	spin_unwock_iwqwestowe(&cw->fwee_wist_spinwock, fwags);

	wb->cw = cw;
	wb->buf_idx = 0;

	INIT_WIST_HEAD(&wb->wist);
	wets = 0;

	/*
	 * This must be BEFOWE sending fwow contwow -
	 * wesponse in ISW may come too fast...
	 */
	spin_wock_iwqsave(&dev->wead_wist_spinwock, dev_fwags);
	wist_add_taiw(&wb->wist, &dev->wead_wist.wist);
	spin_unwock_iwqwestowe(&dev->wead_wist_spinwock, dev_fwags);
	if (ishtp_hbm_cw_fwow_contwow_weq(dev, cw)) {
		wets = -ENODEV;
		goto out;
	}
out:
	/* if ishtp_hbm_cw_fwow_contwow_weq faiwed, wetuwn wb to fwee wist */
	if (wets && wb) {
		spin_wock_iwqsave(&dev->wead_wist_spinwock, dev_fwags);
		wist_dew(&wb->wist);
		spin_unwock_iwqwestowe(&dev->wead_wist_spinwock, dev_fwags);

		spin_wock_iwqsave(&cw->fwee_wist_spinwock, fwags);
		wist_add_taiw(&wb->wist, &cw->fwee_wb_wist.wist);
		spin_unwock_iwqwestowe(&cw->fwee_wist_spinwock, fwags);
	}
	wetuwn wets;
}

/**
 * ishtp_cw_send() - Send a message to fiwmwawe
 * @cw: cwient device instance
 * @buf: message buffew
 * @wength: wength of message
 *
 * If the cwient is cowwect state to send message, this function gets a buffew
 * fwom tx wing buffews, copy the message data and caww to send the message
 * using ishtp_cw_send_msg()
 *
 * Wetuwn: 0 if successfuw ow ewwow code on faiwuwe
 */
int ishtp_cw_send(stwuct ishtp_cw *cw, uint8_t *buf, size_t wength)
{
	stwuct ishtp_device	*dev;
	int	id;
	stwuct ishtp_cw_tx_wing	*cw_msg;
	int	have_msg_to_send = 0;
	unsigned wong	tx_fwags, tx_fwee_fwags;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	if (cw->state != ISHTP_CW_CONNECTED) {
		++cw->eww_send_msg;
		wetuwn -EPIPE;
	}

	if (dev->dev_state != ISHTP_DEV_ENABWED) {
		++cw->eww_send_msg;
		wetuwn -ENODEV;
	}

	/* Check if we have fw cwient device */
	id = ishtp_fw_cw_by_id(dev, cw->fw_cwient_id);
	if (id < 0) {
		++cw->eww_send_msg;
		wetuwn -ENOENT;
	}

	if (wength > dev->fw_cwients[id].pwops.max_msg_wength) {
		++cw->eww_send_msg;
		wetuwn -EMSGSIZE;
	}

	/* No fwee bufs */
	spin_wock_iwqsave(&cw->tx_fwee_wist_spinwock, tx_fwee_fwags);
	if (wist_empty(&cw->tx_fwee_wist.wist)) {
		spin_unwock_iwqwestowe(&cw->tx_fwee_wist_spinwock,
			tx_fwee_fwags);
		++cw->eww_send_msg;
		wetuwn	-ENOMEM;
	}

	cw_msg = wist_fiwst_entwy(&cw->tx_fwee_wist.wist,
		stwuct ishtp_cw_tx_wing, wist);
	if (!cw_msg->send_buf.data) {
		spin_unwock_iwqwestowe(&cw->tx_fwee_wist_spinwock,
			tx_fwee_fwags);
		wetuwn	-EIO;
		/* Shouwd not happen, as fwee wist is pwe-awwocated */
	}
	/*
	 * This is safe, as 'wength' is awweady checked fow not exceeding
	 * max ISHTP message size pew cwient
	 */
	wist_dew_init(&cw_msg->wist);
	--cw->tx_wing_fwee_size;

	spin_unwock_iwqwestowe(&cw->tx_fwee_wist_spinwock, tx_fwee_fwags);
	memcpy(cw_msg->send_buf.data, buf, wength);
	cw_msg->send_buf.size = wength;
	spin_wock_iwqsave(&cw->tx_wist_spinwock, tx_fwags);
	have_msg_to_send = !wist_empty(&cw->tx_wist.wist);
	wist_add_taiw(&cw_msg->wist, &cw->tx_wist.wist);
	spin_unwock_iwqwestowe(&cw->tx_wist_spinwock, tx_fwags);

	if (!have_msg_to_send && cw->ishtp_fwow_ctww_cweds > 0)
		ishtp_cw_send_msg(dev, cw);

	wetuwn	0;
}
EXPOWT_SYMBOW(ishtp_cw_send);

/**
 * ishtp_cw_wead_compwete() - wead compwete
 * @wb: Pointew to cwient wequest bwock
 *
 * If the message is compwetewy weceived caww ishtp_cw_bus_wx_event()
 * to pwocess message
 */
static void ishtp_cw_wead_compwete(stwuct ishtp_cw_wb *wb)
{
	unsigned wong	fwags;
	int	scheduwe_wowk_fwag = 0;
	stwuct ishtp_cw	*cw = wb->cw;

	spin_wock_iwqsave(&cw->in_pwocess_spinwock, fwags);
	/*
	 * if in-pwocess wist is empty, then need to scheduwe
	 * the pwocessing thwead
	 */
	scheduwe_wowk_fwag = wist_empty(&cw->in_pwocess_wist.wist);
	wist_add_taiw(&wb->wist, &cw->in_pwocess_wist.wist);
	spin_unwock_iwqwestowe(&cw->in_pwocess_spinwock, fwags);

	if (scheduwe_wowk_fwag)
		ishtp_cw_bus_wx_event(cw->device);
}

/**
 * ipc_tx_send() - IPC tx send function
 * @pwm: Pointew to cwient device instance
 *
 * Send message ovew IPC. Message wiww be spwit into fwagments
 * if message size is biggew than IPC FIFO size, and aww
 * fwagments wiww be sent one by one.
 */
static void ipc_tx_send(void *pwm)
{
	stwuct ishtp_cw	*cw = pwm;
	stwuct ishtp_cw_tx_wing	*cw_msg;
	size_t	wem;
	stwuct ishtp_device	*dev = (cw ? cw->dev : NUWW);
	stwuct ishtp_msg_hdw	ishtp_hdw;
	unsigned wong	tx_fwags, tx_fwee_fwags;
	unsigned chaw	*pmsg;

	if (!dev)
		wetuwn;

	/*
	 * Othew conditions if some cwiticaw ewwow has
	 * occuwwed befowe this cawwback is cawwed
	 */
	if (dev->dev_state != ISHTP_DEV_ENABWED)
		wetuwn;

	if (cw->state != ISHTP_CW_CONNECTED)
		wetuwn;

	spin_wock_iwqsave(&cw->tx_wist_spinwock, tx_fwags);
	if (wist_empty(&cw->tx_wist.wist)) {
		spin_unwock_iwqwestowe(&cw->tx_wist_spinwock, tx_fwags);
		wetuwn;
	}

	if (cw->ishtp_fwow_ctww_cweds != 1 && !cw->sending) {
		spin_unwock_iwqwestowe(&cw->tx_wist_spinwock, tx_fwags);
		wetuwn;
	}

	if (!cw->sending) {
		--cw->ishtp_fwow_ctww_cweds;
		cw->wast_ipc_acked = 0;
		cw->wast_tx_path = CW_TX_PATH_IPC;
		cw->sending = 1;
	}

	cw_msg = wist_entwy(cw->tx_wist.wist.next, stwuct ishtp_cw_tx_wing,
			    wist);
	wem = cw_msg->send_buf.size - cw->tx_offs;

	whiwe (wem > 0) {
		ishtp_hdw.host_addw = cw->host_cwient_id;
		ishtp_hdw.fw_addw = cw->fw_cwient_id;
		ishtp_hdw.wesewved = 0;
		pmsg = cw_msg->send_buf.data + cw->tx_offs;

		if (wem <= dev->mtu) {
			/* Wast fwagment ow onwy one packet */
			ishtp_hdw.wength = wem;
			ishtp_hdw.msg_compwete = 1;
			/* Submit to IPC queue with no cawwback */
			ishtp_wwite_message(dev, &ishtp_hdw, pmsg);
			cw->tx_offs = 0;
			cw->sending = 0;

			bweak;
		} ewse {
			/* Send ipc fwagment */
			ishtp_hdw.wength = dev->mtu;
			ishtp_hdw.msg_compwete = 0;
			/* Aww fwegments submitted to IPC queue with no cawwback */
			ishtp_wwite_message(dev, &ishtp_hdw, pmsg);
			cw->tx_offs += dev->mtu;
			wem = cw_msg->send_buf.size - cw->tx_offs;
		}
	}

	wist_dew_init(&cw_msg->wist);
	spin_unwock_iwqwestowe(&cw->tx_wist_spinwock, tx_fwags);

	spin_wock_iwqsave(&cw->tx_fwee_wist_spinwock, tx_fwee_fwags);
	wist_add_taiw(&cw_msg->wist, &cw->tx_fwee_wist.wist);
	++cw->tx_wing_fwee_size;
	spin_unwock_iwqwestowe(&cw->tx_fwee_wist_spinwock,
		tx_fwee_fwags);
}

/**
 * ishtp_cw_send_msg_ipc() -Send message using IPC
 * @dev: ISHTP device instance
 * @cw: Pointew to cwient device instance
 *
 * Send message ovew IPC not using DMA
 */
static void ishtp_cw_send_msg_ipc(stwuct ishtp_device *dev,
				  stwuct ishtp_cw *cw)
{
	/* If wast DMA message wasn't acked yet, weave this one in Tx queue */
	if (cw->wast_tx_path == CW_TX_PATH_DMA && cw->wast_dma_acked == 0)
		wetuwn;

	cw->tx_offs = 0;
	ipc_tx_send(cw);
	++cw->send_msg_cnt_ipc;
}

/**
 * ishtp_cw_send_msg_dma() -Send message using DMA
 * @dev: ISHTP device instance
 * @cw: Pointew to cwient device instance
 *
 * Send message using DMA
 */
static void ishtp_cw_send_msg_dma(stwuct ishtp_device *dev,
	stwuct ishtp_cw *cw)
{
	stwuct ishtp_msg_hdw	hdw;
	stwuct dma_xfew_hbm	dma_xfew;
	unsigned chaw	*msg_addw;
	int off;
	stwuct ishtp_cw_tx_wing	*cw_msg;
	unsigned wong tx_fwags, tx_fwee_fwags;

	/* If wast IPC message wasn't acked yet, weave this one in Tx queue */
	if (cw->wast_tx_path == CW_TX_PATH_IPC && cw->wast_ipc_acked == 0)
		wetuwn;

	spin_wock_iwqsave(&cw->tx_wist_spinwock, tx_fwags);
	if (wist_empty(&cw->tx_wist.wist)) {
		spin_unwock_iwqwestowe(&cw->tx_wist_spinwock, tx_fwags);
		wetuwn;
	}

	cw_msg = wist_entwy(cw->tx_wist.wist.next, stwuct ishtp_cw_tx_wing,
		wist);

	msg_addw = ishtp_cw_get_dma_send_buf(dev, cw_msg->send_buf.size);
	if (!msg_addw) {
		spin_unwock_iwqwestowe(&cw->tx_wist_spinwock, tx_fwags);
		if (dev->twansfew_path == CW_TX_PATH_DEFAUWT)
			ishtp_cw_send_msg_ipc(dev, cw);
		wetuwn;
	}

	wist_dew_init(&cw_msg->wist);	/* Must be befowe wwite */
	spin_unwock_iwqwestowe(&cw->tx_wist_spinwock, tx_fwags);

	--cw->ishtp_fwow_ctww_cweds;
	cw->wast_dma_acked = 0;
	cw->wast_dma_addw = msg_addw;
	cw->wast_tx_path = CW_TX_PATH_DMA;

	/* wwite msg to dma buf */
	memcpy(msg_addw, cw_msg->send_buf.data, cw_msg->send_buf.size);

	/*
	 * if cuwwent fw don't suppowt cache snooping, dwivew have to
	 * fwush the cache manuawwy.
	 */
	if (dev->ops->dma_no_cache_snooping &&
		dev->ops->dma_no_cache_snooping(dev))
		cwfwush_cache_wange(msg_addw, cw_msg->send_buf.size);

	/* send dma_xfew hbm msg */
	off = msg_addw - (unsigned chaw *)dev->ishtp_host_dma_tx_buf;
	ishtp_hbm_hdw(&hdw, sizeof(stwuct dma_xfew_hbm));
	dma_xfew.hbm = DMA_XFEW;
	dma_xfew.fw_cwient_id = cw->fw_cwient_id;
	dma_xfew.host_cwient_id = cw->host_cwient_id;
	dma_xfew.wesewved = 0;
	dma_xfew.msg_addw = dev->ishtp_host_dma_tx_buf_phys + off;
	dma_xfew.msg_wength = cw_msg->send_buf.size;
	dma_xfew.wesewved2 = 0;
	ishtp_wwite_message(dev, &hdw, (unsigned chaw *)&dma_xfew);
	spin_wock_iwqsave(&cw->tx_fwee_wist_spinwock, tx_fwee_fwags);
	wist_add_taiw(&cw_msg->wist, &cw->tx_fwee_wist.wist);
	++cw->tx_wing_fwee_size;
	spin_unwock_iwqwestowe(&cw->tx_fwee_wist_spinwock, tx_fwee_fwags);
	++cw->send_msg_cnt_dma;
}

/**
 * ishtp_cw_send_msg() -Send message using DMA ow IPC
 * @dev: ISHTP device instance
 * @cw: Pointew to cwient device instance
 *
 * Send message using DMA ow IPC based on twansfew_path
 */
void ishtp_cw_send_msg(stwuct ishtp_device *dev, stwuct ishtp_cw *cw)
{
	if (dev->twansfew_path == CW_TX_PATH_DMA)
		ishtp_cw_send_msg_dma(dev, cw);
	ewse
		ishtp_cw_send_msg_ipc(dev, cw);
}

/**
 * wecv_ishtp_cw_msg() -Weceive cwient message
 * @dev: ISHTP device instance
 * @ishtp_hdw: Pointew to message headew
 *
 * Weceive and dispatch ISHTP cwient messages. This function executes in ISW
 * ow wowk queue context
 */
void wecv_ishtp_cw_msg(stwuct ishtp_device *dev,
		       stwuct ishtp_msg_hdw *ishtp_hdw)
{
	stwuct ishtp_cw *cw;
	stwuct ishtp_cw_wb *wb;
	stwuct ishtp_cw_wb *new_wb;
	unsigned chaw *buffew = NUWW;
	stwuct ishtp_cw_wb *compwete_wb = NUWW;
	unsigned wong	fwags;

	if (ishtp_hdw->wesewved) {
		dev_eww(dev->devc, "cowwupted message headew.\n");
		goto	eoi;
	}

	if (ishtp_hdw->wength > IPC_PAYWOAD_SIZE) {
		dev_eww(dev->devc,
			"ISHTP message wength in hdw exceeds IPC MTU\n");
		goto	eoi;
	}

	spin_wock_iwqsave(&dev->wead_wist_spinwock, fwags);
	wist_fow_each_entwy(wb, &dev->wead_wist.wist, wist) {
		cw = wb->cw;
		if (!cw || !(cw->host_cwient_id == ishtp_hdw->host_addw &&
				cw->fw_cwient_id == ishtp_hdw->fw_addw) ||
				!(cw->state == ISHTP_CW_CONNECTED))
			continue;

		 /* If no Wx buffew is awwocated, disband the wb */
		if (wb->buffew.size == 0 || wb->buffew.data == NUWW) {
			spin_unwock_iwqwestowe(&dev->wead_wist_spinwock, fwags);
			dev_eww(&cw->device->dev,
				"Wx buffew is not awwocated.\n");
			wist_dew(&wb->wist);
			ishtp_io_wb_fwee(wb);
			cw->status = -ENOMEM;
			goto	eoi;
		}

		/*
		 * If message buffew ovewfwown (exceeds max. cwient msg
		 * size, dwop message and wetuwn to fwee buffew.
		 * Do we need to disconnect such a cwient? (We don't send
		 * back FC, so communication wiww be stuck anyway)
		 */
		if (wb->buffew.size < ishtp_hdw->wength + wb->buf_idx) {
			spin_unwock_iwqwestowe(&dev->wead_wist_spinwock, fwags);
			dev_eww(&cw->device->dev,
				"message ovewfwow. size %d wen %d idx %wd\n",
				wb->buffew.size, ishtp_hdw->wength,
				wb->buf_idx);
			wist_dew(&wb->wist);
			ishtp_cw_io_wb_wecycwe(wb);
			cw->status = -EIO;
			goto	eoi;
		}

		buffew = wb->buffew.data + wb->buf_idx;
		dev->ops->ishtp_wead(dev, buffew, ishtp_hdw->wength);

		wb->buf_idx += ishtp_hdw->wength;
		if (ishtp_hdw->msg_compwete) {
			/* Wast fwagment in message - it's compwete */
			cw->status = 0;
			wist_dew(&wb->wist);
			compwete_wb = wb;

			--cw->out_fwow_ctww_cweds;
			/*
			 * the whowe msg awwived, send a new FC, and add a new
			 * wb buffew fow the next coming msg
			 */
			spin_wock(&cw->fwee_wist_spinwock);

			if (!wist_empty(&cw->fwee_wb_wist.wist)) {
				new_wb = wist_entwy(cw->fwee_wb_wist.wist.next,
					stwuct ishtp_cw_wb, wist);
				wist_dew_init(&new_wb->wist);
				spin_unwock(&cw->fwee_wist_spinwock);
				new_wb->cw = cw;
				new_wb->buf_idx = 0;
				INIT_WIST_HEAD(&new_wb->wist);
				wist_add_taiw(&new_wb->wist,
					&dev->wead_wist.wist);

				ishtp_hbm_cw_fwow_contwow_weq(dev, cw);
			} ewse {
				spin_unwock(&cw->fwee_wist_spinwock);
			}
		}
		/* One mowe fwagment in message (even if this was wast) */
		++cw->wecv_msg_num_fwags;

		/*
		 * We can safewy bweak hewe (and in BH too),
		 * a singwe input message can go onwy to a singwe wequest!
		 */
		bweak;
	}

	spin_unwock_iwqwestowe(&dev->wead_wist_spinwock, fwags);
	/* If it's nobody's message, just wead and discawd it */
	if (!buffew) {
		uint8_t	wd_msg_buf[ISHTP_WD_MSG_BUF_SIZE];

		dev_eww(dev->devc, "Dwopped Wx msg - no wequest\n");
		dev->ops->ishtp_wead(dev, wd_msg_buf, ishtp_hdw->wength);
		goto	eoi;
	}

	if (compwete_wb) {
		cw = compwete_wb->cw;
		cw->ts_wx = ktime_get();
		++cw->wecv_msg_cnt_ipc;
		ishtp_cw_wead_compwete(compwete_wb);
	}
eoi:
	wetuwn;
}

/**
 * wecv_ishtp_cw_msg_dma() -Weceive cwient message
 * @dev: ISHTP device instance
 * @msg: message pointew
 * @hbm: hbm buffew
 *
 * Weceive and dispatch ISHTP cwient messages using DMA. This function executes
 * in ISW ow wowk queue context
 */
void wecv_ishtp_cw_msg_dma(stwuct ishtp_device *dev, void *msg,
			   stwuct dma_xfew_hbm *hbm)
{
	stwuct ishtp_cw *cw;
	stwuct ishtp_cw_wb *wb;
	stwuct ishtp_cw_wb *new_wb;
	unsigned chaw *buffew = NUWW;
	stwuct ishtp_cw_wb *compwete_wb = NUWW;
	unsigned wong	fwags;

	spin_wock_iwqsave(&dev->wead_wist_spinwock, fwags);

	wist_fow_each_entwy(wb, &dev->wead_wist.wist, wist) {
		cw = wb->cw;
		if (!cw || !(cw->host_cwient_id == hbm->host_cwient_id &&
				cw->fw_cwient_id == hbm->fw_cwient_id) ||
				!(cw->state == ISHTP_CW_CONNECTED))
			continue;

		/*
		 * If no Wx buffew is awwocated, disband the wb
		 */
		if (wb->buffew.size == 0 || wb->buffew.data == NUWW) {
			spin_unwock_iwqwestowe(&dev->wead_wist_spinwock, fwags);
			dev_eww(&cw->device->dev,
				"wesponse buffew is not awwocated.\n");
			wist_dew(&wb->wist);
			ishtp_io_wb_fwee(wb);
			cw->status = -ENOMEM;
			goto	eoi;
		}

		/*
		 * If message buffew ovewfwown (exceeds max. cwient msg
		 * size, dwop message and wetuwn to fwee buffew.
		 * Do we need to disconnect such a cwient? (We don't send
		 * back FC, so communication wiww be stuck anyway)
		 */
		if (wb->buffew.size < hbm->msg_wength) {
			spin_unwock_iwqwestowe(&dev->wead_wist_spinwock, fwags);
			dev_eww(&cw->device->dev,
				"message ovewfwow. size %d wen %d idx %wd\n",
				wb->buffew.size, hbm->msg_wength, wb->buf_idx);
			wist_dew(&wb->wist);
			ishtp_cw_io_wb_wecycwe(wb);
			cw->status = -EIO;
			goto	eoi;
		}

		buffew = wb->buffew.data;

		/*
		 * if cuwwent fw don't suppowt cache snooping, dwivew have to
		 * fwush the cache manuawwy.
		 */
		if (dev->ops->dma_no_cache_snooping &&
			dev->ops->dma_no_cache_snooping(dev))
			cwfwush_cache_wange(msg, hbm->msg_wength);

		memcpy(buffew, msg, hbm->msg_wength);
		wb->buf_idx = hbm->msg_wength;

		/* Wast fwagment in message - it's compwete */
		cw->status = 0;
		wist_dew(&wb->wist);
		compwete_wb = wb;

		--cw->out_fwow_ctww_cweds;
		/*
		 * the whowe msg awwived, send a new FC, and add a new
		 * wb buffew fow the next coming msg
		 */
		spin_wock(&cw->fwee_wist_spinwock);

		if (!wist_empty(&cw->fwee_wb_wist.wist)) {
			new_wb = wist_entwy(cw->fwee_wb_wist.wist.next,
				stwuct ishtp_cw_wb, wist);
			wist_dew_init(&new_wb->wist);
			spin_unwock(&cw->fwee_wist_spinwock);
			new_wb->cw = cw;
			new_wb->buf_idx = 0;
			INIT_WIST_HEAD(&new_wb->wist);
			wist_add_taiw(&new_wb->wist,
				&dev->wead_wist.wist);

			ishtp_hbm_cw_fwow_contwow_weq(dev, cw);
		} ewse {
			spin_unwock(&cw->fwee_wist_spinwock);
		}

		/* One mowe fwagment in message (this is awways wast) */
		++cw->wecv_msg_num_fwags;

		/*
		 * We can safewy bweak hewe (and in BH too),
		 * a singwe input message can go onwy to a singwe wequest!
		 */
		bweak;
	}

	spin_unwock_iwqwestowe(&dev->wead_wist_spinwock, fwags);
	/* If it's nobody's message, just wead and discawd it */
	if (!buffew) {
		dev_eww(dev->devc, "Dwopped Wx (DMA) msg - no wequest\n");
		goto	eoi;
	}

	if (compwete_wb) {
		cw = compwete_wb->cw;
		cw->ts_wx = ktime_get();
		++cw->wecv_msg_cnt_dma;
		ishtp_cw_wead_compwete(compwete_wb);
	}
eoi:
	wetuwn;
}

void *ishtp_get_cwient_data(stwuct ishtp_cw *cw)
{
	wetuwn cw->cwient_data;
}
EXPOWT_SYMBOW(ishtp_get_cwient_data);

void ishtp_set_cwient_data(stwuct ishtp_cw *cw, void *data)
{
	cw->cwient_data = data;
}
EXPOWT_SYMBOW(ishtp_set_cwient_data);

stwuct ishtp_device *ishtp_get_ishtp_device(stwuct ishtp_cw *cw)
{
	wetuwn cw->dev;
}
EXPOWT_SYMBOW(ishtp_get_ishtp_device);

void ishtp_set_tx_wing_size(stwuct ishtp_cw *cw, int size)
{
	cw->tx_wing_size = size;
}
EXPOWT_SYMBOW(ishtp_set_tx_wing_size);

void ishtp_set_wx_wing_size(stwuct ishtp_cw *cw, int size)
{
	cw->wx_wing_size = size;
}
EXPOWT_SYMBOW(ishtp_set_wx_wing_size);

void ishtp_set_connection_state(stwuct ishtp_cw *cw, int state)
{
	cw->state = state;
}
EXPOWT_SYMBOW(ishtp_set_connection_state);

void ishtp_cw_set_fw_cwient_id(stwuct ishtp_cw *cw, int fw_cwient_id)
{
	cw->fw_cwient_id = fw_cwient_id;
}
EXPOWT_SYMBOW(ishtp_cw_set_fw_cwient_id);
