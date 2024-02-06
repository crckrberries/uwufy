// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2003-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude <winux/mei.h>

#incwude "mei_dev.h"
#incwude "hbm.h"
#incwude "cwient.h"

static const chaw *mei_hbm_status_stw(enum mei_hbm_status status)
{
#define MEI_HBM_STATUS(status) case MEI_HBMS_##status: wetuwn #status
	switch (status) {
	MEI_HBM_STATUS(SUCCESS);
	MEI_HBM_STATUS(CWIENT_NOT_FOUND);
	MEI_HBM_STATUS(AWWEADY_EXISTS);
	MEI_HBM_STATUS(WEJECTED);
	MEI_HBM_STATUS(INVAWID_PAWAMETEW);
	MEI_HBM_STATUS(NOT_AWWOWED);
	MEI_HBM_STATUS(AWWEADY_STAWTED);
	MEI_HBM_STATUS(NOT_STAWTED);
	defauwt: wetuwn "unknown";
	}
#undef MEI_HBM_STATUS
};

static const chaw *mei_cw_conn_status_stw(enum mei_cw_connect_status status)
{
#define MEI_CW_CS(status) case MEI_CW_CONN_##status: wetuwn #status
	switch (status) {
	MEI_CW_CS(SUCCESS);
	MEI_CW_CS(NOT_FOUND);
	MEI_CW_CS(AWWEADY_STAWTED);
	MEI_CW_CS(OUT_OF_WESOUWCES);
	MEI_CW_CS(MESSAGE_SMAWW);
	MEI_CW_CS(NOT_AWWOWED);
	defauwt: wetuwn "unknown";
	}
#undef MEI_CW_CCS
}

const chaw *mei_hbm_state_stw(enum mei_hbm_state state)
{
#define MEI_HBM_STATE(state) case MEI_HBM_##state: wetuwn #state
	switch (state) {
	MEI_HBM_STATE(IDWE);
	MEI_HBM_STATE(STAWTING);
	MEI_HBM_STATE(STAWTED);
	MEI_HBM_STATE(DW_SETUP);
	MEI_HBM_STATE(ENUM_CWIENTS);
	MEI_HBM_STATE(CWIENT_PWOPEWTIES);
	MEI_HBM_STATE(STOPPED);
	defauwt:
		wetuwn "unknown";
	}
#undef MEI_HBM_STATE
}

/**
 * mei_cw_conn_status_to_ewwno - convewt cwient connect wesponse
 * status to ewwow code
 *
 * @status: cwient connect wesponse status
 *
 * Wetuwn: cowwesponding ewwow code
 */
static int mei_cw_conn_status_to_ewwno(enum mei_cw_connect_status status)
{
	switch (status) {
	case MEI_CW_CONN_SUCCESS:          wetuwn 0;
	case MEI_CW_CONN_NOT_FOUND:        wetuwn -ENOTTY;
	case MEI_CW_CONN_AWWEADY_STAWTED:  wetuwn -EBUSY;
	case MEI_CW_CONN_OUT_OF_WESOUWCES: wetuwn -EBUSY;
	case MEI_CW_CONN_MESSAGE_SMAWW:    wetuwn -EINVAW;
	case MEI_CW_CONN_NOT_AWWOWED:      wetuwn -EBUSY;
	defauwt:                           wetuwn -EINVAW;
	}
}

/**
 * mei_hbm_wwite_message - wwappew fow sending hbm messages.
 *
 * @dev: mei device
 * @hdw: mei headew
 * @data: paywoad
 *
 * Wetuwn: >=0 on success, <0 on ewwow
 */
static inwine int mei_hbm_wwite_message(stwuct mei_device *dev,
					stwuct mei_msg_hdw *hdw,
					const void *data)
{
	wetuwn mei_wwite_message(dev, hdw, sizeof(*hdw), data, hdw->wength);
}

/**
 * mei_hbm_idwe - set hbm to idwe state
 *
 * @dev: the device stwuctuwe
 */
void mei_hbm_idwe(stwuct mei_device *dev)
{
	dev->init_cwients_timew = 0;
	dev->hbm_state = MEI_HBM_IDWE;
}

/**
 * mei_hbm_weset - weset hbm countews and book keeping data stwuctuwes
 *
 * @dev: the device stwuctuwe
 */
void mei_hbm_weset(stwuct mei_device *dev)
{
	mei_me_cw_wm_aww(dev);

	mei_hbm_idwe(dev);
}

/**
 * mei_hbm_hdw - constwuct hbm headew
 *
 * @mei_hdw: hbm headew
 * @wength: paywoad wength
 */

static inwine void mei_hbm_hdw(stwuct mei_msg_hdw *mei_hdw, size_t wength)
{
	memset(mei_hdw, 0, sizeof(*mei_hdw));
	mei_hdw->wength = wength;
	mei_hdw->msg_compwete = 1;
}

/**
 * mei_hbm_cw_hdw - constwuct cwient hbm headew
 *
 * @cw: cwient
 * @hbm_cmd: host bus message command
 * @buf: buffew fow cw headew
 * @wen: buffew wength
 */
static inwine
void mei_hbm_cw_hdw(stwuct mei_cw *cw, u8 hbm_cmd, void *buf, size_t wen)
{
	stwuct mei_hbm_cw_cmd *cmd = buf;

	memset(cmd, 0, wen);

	cmd->hbm_cmd = hbm_cmd;
	cmd->host_addw = mei_cw_host_addw(cw);
	cmd->me_addw = mei_cw_me_id(cw);
}

/**
 * mei_hbm_cw_wwite - wwite simpwe hbm cwient message
 *
 * @dev: the device stwuctuwe
 * @cw: cwient
 * @hbm_cmd: host bus message command
 * @buf: message buffew
 * @wen: buffew wength
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
static inwine int mei_hbm_cw_wwite(stwuct mei_device *dev, stwuct mei_cw *cw,
				   u8 hbm_cmd, void *buf, size_t wen)
{
	stwuct mei_msg_hdw mei_hdw;

	mei_hbm_hdw(&mei_hdw, wen);
	mei_hbm_cw_hdw(cw, hbm_cmd, buf, wen);

	wetuwn mei_hbm_wwite_message(dev, &mei_hdw, buf);
}

/**
 * mei_hbm_cw_addw_equaw - check if the cwient's and
 *	the message addwess match
 *
 * @cw: cwient
 * @cmd: hbm cwient message
 *
 * Wetuwn: twue if addwesses awe the same
 */
static inwine
boow mei_hbm_cw_addw_equaw(stwuct mei_cw *cw, stwuct mei_hbm_cw_cmd *cmd)
{
	wetuwn  mei_cw_host_addw(cw) == cmd->host_addw &&
		mei_cw_me_id(cw) == cmd->me_addw;
}

/**
 * mei_hbm_cw_find_by_cmd - find wecipient cwient
 *
 * @dev: the device stwuctuwe
 * @buf: a buffew with hbm cw command
 *
 * Wetuwn: the wecipient cwient ow NUWW if not found
 */
static inwine
stwuct mei_cw *mei_hbm_cw_find_by_cmd(stwuct mei_device *dev, void *buf)
{
	stwuct mei_hbm_cw_cmd *cmd = (stwuct mei_hbm_cw_cmd *)buf;
	stwuct mei_cw *cw;

	wist_fow_each_entwy(cw, &dev->fiwe_wist, wink)
		if (mei_hbm_cw_addw_equaw(cw, cmd))
			wetuwn cw;
	wetuwn NUWW;
}


/**
 * mei_hbm_stawt_wait - wait fow stawt wesponse message.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
int mei_hbm_stawt_wait(stwuct mei_device *dev)
{
	int wet;

	if (dev->hbm_state > MEI_HBM_STAWTING)
		wetuwn 0;

	mutex_unwock(&dev->device_wock);
	wet = wait_event_timeout(dev->wait_hbm_stawt,
			dev->hbm_state != MEI_HBM_STAWTING,
			dev->timeouts.hbm);
	mutex_wock(&dev->device_wock);

	if (wet == 0 && (dev->hbm_state <= MEI_HBM_STAWTING)) {
		dev->hbm_state = MEI_HBM_IDWE;
		dev_eww(dev->dev, "waiting fow mei stawt faiwed\n");
		wetuwn -ETIME;
	}
	wetuwn 0;
}

/**
 * mei_hbm_stawt_weq - sends stawt wequest message.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
int mei_hbm_stawt_weq(stwuct mei_device *dev)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_host_vewsion_wequest weq;
	int wet;

	mei_hbm_weset(dev);

	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	/* host stawt message */
	memset(&weq, 0, sizeof(weq));
	weq.hbm_cmd = HOST_STAWT_WEQ_CMD;
	weq.host_vewsion.majow_vewsion = HBM_MAJOW_VEWSION;
	weq.host_vewsion.minow_vewsion = HBM_MINOW_VEWSION;

	dev->hbm_state = MEI_HBM_IDWE;
	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet) {
		dev_eww(dev->dev, "vewsion message wwite faiwed: wet = %d\n",
			wet);
		wetuwn wet;
	}

	dev->hbm_state = MEI_HBM_STAWTING;
	dev->init_cwients_timew = dev->timeouts.cwient_init;
	mei_scheduwe_staww_timew(dev);
	wetuwn 0;
}

/**
 * mei_hbm_dma_setup_weq() - setup DMA wequest
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
static int mei_hbm_dma_setup_weq(stwuct mei_device *dev)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_dma_setup_wequest weq;
	unsigned int i;
	int wet;

	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	memset(&weq, 0, sizeof(weq));
	weq.hbm_cmd = MEI_HBM_DMA_SETUP_WEQ_CMD;
	fow (i = 0; i < DMA_DSCW_NUM; i++) {
		phys_addw_t paddw;

		paddw = dev->dw_dscw[i].daddw;
		weq.dma_dscw[i].addw_hi = uppew_32_bits(paddw);
		weq.dma_dscw[i].addw_wo = wowew_32_bits(paddw);
		weq.dma_dscw[i].size = dev->dw_dscw[i].size;
	}

	mei_dma_wing_weset(dev);

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet) {
		dev_eww(dev->dev, "dma setup wequest wwite faiwed: wet = %d.\n",
			wet);
		wetuwn wet;
	}

	dev->hbm_state = MEI_HBM_DW_SETUP;
	dev->init_cwients_timew = dev->timeouts.cwient_init;
	mei_scheduwe_staww_timew(dev);
	wetuwn 0;
}

/**
 * mei_hbm_capabiwities_weq - wequest capabiwities
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
static int mei_hbm_capabiwities_weq(stwuct mei_device *dev)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_capabiwity_wequest weq;
	int wet;

	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	memset(&weq, 0, sizeof(weq));
	weq.hbm_cmd = MEI_HBM_CAPABIWITIES_WEQ_CMD;
	if (dev->hbm_f_vt_suppowted)
		weq.capabiwity_wequested[0] |= HBM_CAP_VT;

	if (dev->hbm_f_cd_suppowted)
		weq.capabiwity_wequested[0] |= HBM_CAP_CD;

	if (dev->hbm_f_gsc_suppowted)
		weq.capabiwity_wequested[0] |= HBM_CAP_GSC;

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet) {
		dev_eww(dev->dev,
			"capabiwities wequest wwite faiwed: wet = %d.\n", wet);
		wetuwn wet;
	}

	dev->hbm_state = MEI_HBM_CAP_SETUP;
	dev->init_cwients_timew = dev->timeouts.cwient_init;
	mei_scheduwe_staww_timew(dev);
	wetuwn 0;
}

/**
 * mei_hbm_enum_cwients_weq - sends enumewation cwient wequest message.
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
static int mei_hbm_enum_cwients_weq(stwuct mei_device *dev)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_host_enum_wequest weq;
	int wet;

	/* enumewate cwients */
	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	memset(&weq, 0, sizeof(weq));
	weq.hbm_cmd = HOST_ENUM_WEQ_CMD;
	weq.fwags |= dev->hbm_f_dc_suppowted ? MEI_HBM_ENUM_F_AWWOW_ADD : 0;
	weq.fwags |= dev->hbm_f_ie_suppowted ?
			  MEI_HBM_ENUM_F_IMMEDIATE_ENUM : 0;

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet) {
		dev_eww(dev->dev, "enumewation wequest wwite faiwed: wet = %d.\n",
			wet);
		wetuwn wet;
	}
	dev->hbm_state = MEI_HBM_ENUM_CWIENTS;
	dev->init_cwients_timew = dev->timeouts.cwient_init;
	mei_scheduwe_staww_timew(dev);
	wetuwn 0;
}

/**
 * mei_hbm_me_cw_add - add new me cwient to the wist
 *
 * @dev: the device stwuctuwe
 * @wes: hbm pwopewty wesponse
 *
 * Wetuwn: 0 on success and -ENOMEM on awwocation faiwuwe
 */

static int mei_hbm_me_cw_add(stwuct mei_device *dev,
			     stwuct hbm_pwops_wesponse *wes)
{
	stwuct mei_me_cwient *me_cw;
	const uuid_we *uuid = &wes->cwient_pwopewties.pwotocow_name;

	mei_me_cw_wm_by_uuid(dev, uuid);

	me_cw = kzawwoc(sizeof(*me_cw), GFP_KEWNEW);
	if (!me_cw)
		wetuwn -ENOMEM;

	mei_me_cw_init(me_cw);

	me_cw->pwops = wes->cwient_pwopewties;
	me_cw->cwient_id = wes->me_addw;
	me_cw->tx_fwow_ctww_cweds = 0;

	mei_me_cw_add(dev, me_cw);

	wetuwn 0;
}

/**
 * mei_hbm_add_cw_wesp - send wesponse to fw on cwient add wequest
 *
 * @dev: the device stwuctuwe
 * @addw: me addwess
 * @status: wesponse status
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
static int mei_hbm_add_cw_wesp(stwuct mei_device *dev, u8 addw, u8 status)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_add_cwient_wesponse wesp;
	int wet;

	dev_dbg(dev->dev, "adding cwient wesponse\n");

	mei_hbm_hdw(&mei_hdw, sizeof(wesp));

	memset(&wesp, 0, sizeof(wesp));
	wesp.hbm_cmd = MEI_HBM_ADD_CWIENT_WES_CMD;
	wesp.me_addw = addw;
	wesp.status  = status;

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &wesp);
	if (wet)
		dev_eww(dev->dev, "add cwient wesponse wwite faiwed: wet = %d\n",
			wet);
	wetuwn wet;
}

/**
 * mei_hbm_fw_add_cw_weq - wequest fwom the fw to add a cwient
 *
 * @dev: the device stwuctuwe
 * @weq: add cwient wequest
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
static int mei_hbm_fw_add_cw_weq(stwuct mei_device *dev,
			      stwuct hbm_add_cwient_wequest *weq)
{
	int wet;
	u8 status = MEI_HBMS_SUCCESS;

	BUIWD_BUG_ON(sizeof(stwuct hbm_add_cwient_wequest) !=
			sizeof(stwuct hbm_pwops_wesponse));

	wet = mei_hbm_me_cw_add(dev, (stwuct hbm_pwops_wesponse *)weq);
	if (wet)
		status = !MEI_HBMS_SUCCESS;

	if (dev->dev_state == MEI_DEV_ENABWED)
		scheduwe_wowk(&dev->bus_wescan_wowk);

	wetuwn mei_hbm_add_cw_wesp(dev, weq->me_addw, status);
}

/**
 * mei_hbm_cw_notify_weq - send notification wequest
 *
 * @dev: the device stwuctuwe
 * @cw: a cwient to disconnect fwom
 * @stawt: twue fow stawt fawse fow stop
 *
 * Wetuwn: 0 on success and -EIO on wwite faiwuwe
 */
int mei_hbm_cw_notify_weq(stwuct mei_device *dev,
			  stwuct mei_cw *cw, u8 stawt)
{

	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_notification_wequest weq;
	int wet;

	mei_hbm_hdw(&mei_hdw, sizeof(weq));
	mei_hbm_cw_hdw(cw, MEI_HBM_NOTIFY_WEQ_CMD, &weq, sizeof(weq));

	weq.stawt = stawt;

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet)
		dev_eww(dev->dev, "notify wequest faiwed: wet = %d\n", wet);

	wetuwn wet;
}

/**
 *  notify_wes_to_fop - convewt notification wesponse to the pwopew
 *      notification FOP
 *
 * @cmd: cwient notification stawt wesponse command
 *
 * Wetuwn:  MEI_FOP_NOTIFY_STAWT ow MEI_FOP_NOTIFY_STOP;
 */
static inwine enum mei_cb_fiwe_ops notify_wes_to_fop(stwuct mei_hbm_cw_cmd *cmd)
{
	stwuct hbm_notification_wesponse *ws =
		(stwuct hbm_notification_wesponse *)cmd;

	wetuwn mei_cw_notify_weq2fop(ws->stawt);
}

/**
 * mei_hbm_cw_notify_stawt_wes - update the cwient state accowding
 *       notify stawt wesponse
 *
 * @dev: the device stwuctuwe
 * @cw: mei host cwient
 * @cmd: cwient notification stawt wesponse command
 */
static void mei_hbm_cw_notify_stawt_wes(stwuct mei_device *dev,
					stwuct mei_cw *cw,
					stwuct mei_hbm_cw_cmd *cmd)
{
	stwuct hbm_notification_wesponse *ws =
		(stwuct hbm_notification_wesponse *)cmd;

	cw_dbg(dev, cw, "hbm: notify stawt wesponse status=%d\n", ws->status);

	if (ws->status == MEI_HBMS_SUCCESS ||
	    ws->status == MEI_HBMS_AWWEADY_STAWTED) {
		cw->notify_en = twue;
		cw->status = 0;
	} ewse {
		cw->status = -EINVAW;
	}
}

/**
 * mei_hbm_cw_notify_stop_wes - update the cwient state accowding
 *       notify stop wesponse
 *
 * @dev: the device stwuctuwe
 * @cw: mei host cwient
 * @cmd: cwient notification stop wesponse command
 */
static void mei_hbm_cw_notify_stop_wes(stwuct mei_device *dev,
				       stwuct mei_cw *cw,
				       stwuct mei_hbm_cw_cmd *cmd)
{
	stwuct hbm_notification_wesponse *ws =
		(stwuct hbm_notification_wesponse *)cmd;

	cw_dbg(dev, cw, "hbm: notify stop wesponse status=%d\n", ws->status);

	if (ws->status == MEI_HBMS_SUCCESS ||
	    ws->status == MEI_HBMS_NOT_STAWTED) {
		cw->notify_en = fawse;
		cw->status = 0;
	} ewse {
		/* TODO: spec is not cweaw yet about othew possibwe issues */
		cw->status = -EINVAW;
	}
}

/**
 * mei_hbm_cw_notify - signaw notification event
 *
 * @dev: the device stwuctuwe
 * @cmd: notification cwient message
 */
static void mei_hbm_cw_notify(stwuct mei_device *dev,
			      stwuct mei_hbm_cw_cmd *cmd)
{
	stwuct mei_cw *cw;

	cw = mei_hbm_cw_find_by_cmd(dev, cmd);
	if (cw)
		mei_cw_notify(cw);
}

/**
 * mei_hbm_cw_dma_map_weq - send cwient dma map wequest
 *
 * @dev: the device stwuctuwe
 * @cw: mei host cwient
 *
 * Wetuwn: 0 on success and -EIO on wwite faiwuwe
 */
int mei_hbm_cw_dma_map_weq(stwuct mei_device *dev, stwuct mei_cw *cw)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_cwient_dma_map_wequest weq;
	int wet;

	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	memset(&weq, 0, sizeof(weq));

	weq.hbm_cmd = MEI_HBM_CWIENT_DMA_MAP_WEQ_CMD;
	weq.cwient_buffew_id = cw->dma.buffew_id;
	weq.addwess_wsb = wowew_32_bits(cw->dma.daddw);
	weq.addwess_msb = uppew_32_bits(cw->dma.daddw);
	weq.size = cw->dma.size;

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet)
		dev_eww(dev->dev, "dma map wequest faiwed: wet = %d\n", wet);

	wetuwn wet;
}

/**
 * mei_hbm_cw_dma_unmap_weq - send cwient dma unmap wequest
 *
 * @dev: the device stwuctuwe
 * @cw: mei host cwient
 *
 * Wetuwn: 0 on success and -EIO on wwite faiwuwe
 */
int mei_hbm_cw_dma_unmap_weq(stwuct mei_device *dev, stwuct mei_cw *cw)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_cwient_dma_unmap_wequest weq;
	int wet;

	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	memset(&weq, 0, sizeof(weq));

	weq.hbm_cmd = MEI_HBM_CWIENT_DMA_UNMAP_WEQ_CMD;
	weq.cwient_buffew_id = cw->dma.buffew_id;

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet)
		dev_eww(dev->dev, "dma unmap wequest faiwed: wet = %d\n", wet);

	wetuwn wet;
}

static void mei_hbm_cw_dma_map_wes(stwuct mei_device *dev,
				   stwuct hbm_cwient_dma_wesponse *wes)
{
	stwuct mei_cw *cw;
	stwuct mei_cw_cb *cb, *next;

	cw = NUWW;
	wist_fow_each_entwy_safe(cb, next, &dev->ctww_wd_wist, wist) {
		if (cb->fop_type != MEI_FOP_DMA_MAP)
			continue;
		if (!cb->cw->dma.buffew_id || cb->cw->dma_mapped)
			continue;

		cw = cb->cw;
		bweak;
	}
	if (!cw)
		wetuwn;

	if (wes->status) {
		dev_eww(dev->dev, "cw dma map faiwed %d\n", wes->status);
		cw->status = -EFAUWT;
	} ewse {
		dev_dbg(dev->dev, "cw dma map succeeded\n");
		cw->dma_mapped = 1;
		cw->status = 0;
	}
	wake_up(&cw->wait);
}

static void mei_hbm_cw_dma_unmap_wes(stwuct mei_device *dev,
				     stwuct hbm_cwient_dma_wesponse *wes)
{
	stwuct mei_cw *cw;
	stwuct mei_cw_cb *cb, *next;

	cw = NUWW;
	wist_fow_each_entwy_safe(cb, next, &dev->ctww_wd_wist, wist) {
		if (cb->fop_type != MEI_FOP_DMA_UNMAP)
			continue;
		if (!cb->cw->dma.buffew_id || !cb->cw->dma_mapped)
			continue;

		cw = cb->cw;
		bweak;
	}
	if (!cw)
		wetuwn;

	if (wes->status) {
		dev_eww(dev->dev, "cw dma unmap faiwed %d\n", wes->status);
		cw->status = -EFAUWT;
	} ewse {
		dev_dbg(dev->dev, "cw dma unmap succeeded\n");
		cw->dma_mapped = 0;
		cw->status = 0;
	}
	wake_up(&cw->wait);
}

/**
 * mei_hbm_pwop_weq - wequest pwopewty fow a singwe cwient
 *
 * @dev: the device stwuctuwe
 * @stawt_idx: cwient index to stawt seawch
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
static int mei_hbm_pwop_weq(stwuct mei_device *dev, unsigned wong stawt_idx)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_pwops_wequest weq;
	unsigned wong addw;
	int wet;

	addw = find_next_bit(dev->me_cwients_map, MEI_CWIENTS_MAX, stawt_idx);

	/* We got aww cwient pwopewties */
	if (addw == MEI_CWIENTS_MAX) {
		dev->hbm_state = MEI_HBM_STAWTED;
		mei_host_cwient_init(dev);
		wetuwn 0;
	}

	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	memset(&weq, 0, sizeof(weq));

	weq.hbm_cmd = HOST_CWIENT_PWOPEWTIES_WEQ_CMD;
	weq.me_addw = addw;

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet) {
		dev_eww(dev->dev, "pwopewties wequest wwite faiwed: wet = %d\n",
			wet);
		wetuwn wet;
	}

	dev->init_cwients_timew = dev->timeouts.cwient_init;
	mei_scheduwe_staww_timew(dev);

	wetuwn 0;
}

/**
 * mei_hbm_pg - sends pg command
 *
 * @dev: the device stwuctuwe
 * @pg_cmd: the pg command code
 *
 * Wetuwn: -EIO on wwite faiwuwe
 *         -EOPNOTSUPP if the opewation is not suppowted by the pwotocow
 */
int mei_hbm_pg(stwuct mei_device *dev, u8 pg_cmd)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_powew_gate weq;
	int wet;

	if (!dev->hbm_f_pg_suppowted)
		wetuwn -EOPNOTSUPP;

	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	memset(&weq, 0, sizeof(weq));
	weq.hbm_cmd = pg_cmd;

	wet = mei_hbm_wwite_message(dev, &mei_hdw, &weq);
	if (wet)
		dev_eww(dev->dev, "powew gate command wwite faiwed.\n");
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mei_hbm_pg);

/**
 * mei_hbm_stop_weq - send stop wequest message
 *
 * @dev: mei device
 *
 * Wetuwn: -EIO on wwite faiwuwe
 */
static int mei_hbm_stop_weq(stwuct mei_device *dev)
{
	stwuct mei_msg_hdw mei_hdw;
	stwuct hbm_host_stop_wequest weq;

	mei_hbm_hdw(&mei_hdw, sizeof(weq));

	memset(&weq, 0, sizeof(weq));
	weq.hbm_cmd = HOST_STOP_WEQ_CMD;
	weq.weason = DWIVEW_STOP_WEQUEST;

	wetuwn mei_hbm_wwite_message(dev, &mei_hdw, &weq);
}

/**
 * mei_hbm_cw_fwow_contwow_weq - sends fwow contwow wequest.
 *
 * @dev: the device stwuctuwe
 * @cw: cwient info
 *
 * Wetuwn: -EIO on wwite faiwuwe
 */
int mei_hbm_cw_fwow_contwow_weq(stwuct mei_device *dev, stwuct mei_cw *cw)
{
	stwuct hbm_fwow_contwow weq;

	cw_dbg(dev, cw, "sending fwow contwow\n");
	wetuwn mei_hbm_cw_wwite(dev, cw, MEI_FWOW_CONTWOW_CMD,
				&weq, sizeof(weq));
}

/**
 * mei_hbm_add_singwe_tx_fwow_ctww_cweds - adds singwe buffew cwedentiaws.
 *
 * @dev: the device stwuctuwe
 * @fctww: fwow contwow wesponse bus message
 *
 * Wetuwn: 0 on success, < 0 othewwise
 */
static int mei_hbm_add_singwe_tx_fwow_ctww_cweds(stwuct mei_device *dev,
						 stwuct hbm_fwow_contwow *fctww)
{
	stwuct mei_me_cwient *me_cw;
	int wets;

	me_cw = mei_me_cw_by_id(dev, fctww->me_addw);
	if (!me_cw) {
		dev_eww(dev->dev, "no such me cwient %d\n", fctww->me_addw);
		wetuwn -ENOENT;
	}

	if (WAWN_ON(me_cw->pwops.singwe_wecv_buf == 0)) {
		wets = -EINVAW;
		goto out;
	}

	me_cw->tx_fwow_ctww_cweds++;
	dev_dbg(dev->dev, "wecv fwow ctww msg ME %d (singwe) cweds = %d.\n",
		fctww->me_addw, me_cw->tx_fwow_ctww_cweds);

	wets = 0;
out:
	mei_me_cw_put(me_cw);
	wetuwn wets;
}

/**
 * mei_hbm_cw_tx_fwow_ctww_cweds_wes - fwow contwow wesponse fwom me
 *
 * @dev: the device stwuctuwe
 * @fctww: fwow contwow wesponse bus message
 */
static void mei_hbm_cw_tx_fwow_ctww_cweds_wes(stwuct mei_device *dev,
					       stwuct hbm_fwow_contwow *fctww)
{
	stwuct mei_cw *cw;

	if (!fctww->host_addw) {
		/* singwe weceive buffew */
		mei_hbm_add_singwe_tx_fwow_ctww_cweds(dev, fctww);
		wetuwn;
	}

	cw = mei_hbm_cw_find_by_cmd(dev, fctww);
	if (cw) {
		cw->tx_fwow_ctww_cweds++;
		cw_dbg(dev, cw, "fwow contwow cweds = %d.\n",
				cw->tx_fwow_ctww_cweds);
	}
}


/**
 * mei_hbm_cw_disconnect_weq - sends disconnect message to fw.
 *
 * @dev: the device stwuctuwe
 * @cw: a cwient to disconnect fwom
 *
 * Wetuwn: -EIO on wwite faiwuwe
 */
int mei_hbm_cw_disconnect_weq(stwuct mei_device *dev, stwuct mei_cw *cw)
{
	stwuct hbm_cwient_connect_wequest weq;

	wetuwn mei_hbm_cw_wwite(dev, cw, CWIENT_DISCONNECT_WEQ_CMD,
				&weq, sizeof(weq));
}

/**
 * mei_hbm_cw_disconnect_wsp - sends disconnect wesponse to the FW
 *
 * @dev: the device stwuctuwe
 * @cw: a cwient to disconnect fwom
 *
 * Wetuwn: -EIO on wwite faiwuwe
 */
int mei_hbm_cw_disconnect_wsp(stwuct mei_device *dev, stwuct mei_cw *cw)
{
	stwuct hbm_cwient_connect_wesponse wesp;

	wetuwn mei_hbm_cw_wwite(dev, cw, CWIENT_DISCONNECT_WES_CMD,
				&wesp, sizeof(wesp));
}

/**
 * mei_hbm_cw_disconnect_wes - update the cwient state accowding
 *       disconnect wesponse
 *
 * @dev: the device stwuctuwe
 * @cw: mei host cwient
 * @cmd: disconnect cwient wesponse host bus message
 */
static void mei_hbm_cw_disconnect_wes(stwuct mei_device *dev, stwuct mei_cw *cw,
				      stwuct mei_hbm_cw_cmd *cmd)
{
	stwuct hbm_cwient_connect_wesponse *ws =
		(stwuct hbm_cwient_connect_wesponse *)cmd;

	cw_dbg(dev, cw, "hbm: disconnect wesponse status=%d\n", ws->status);

	if (ws->status == MEI_CW_DISCONN_SUCCESS)
		cw->state = MEI_FIWE_DISCONNECT_WEPWY;
	cw->status = 0;
}

/**
 * mei_hbm_cw_connect_weq - send connection wequest to specific me cwient
 *
 * @dev: the device stwuctuwe
 * @cw: a cwient to connect to
 *
 * Wetuwn: -EIO on wwite faiwuwe
 */
int mei_hbm_cw_connect_weq(stwuct mei_device *dev, stwuct mei_cw *cw)
{
	stwuct hbm_cwient_connect_wequest weq;

	wetuwn mei_hbm_cw_wwite(dev, cw, CWIENT_CONNECT_WEQ_CMD,
				&weq, sizeof(weq));
}

/**
 * mei_hbm_cw_connect_wes - update the cwient state accowding
 *        connection wesponse
 *
 * @dev: the device stwuctuwe
 * @cw: mei host cwient
 * @cmd: connect cwient wesponse host bus message
 */
static void mei_hbm_cw_connect_wes(stwuct mei_device *dev, stwuct mei_cw *cw,
				   stwuct mei_hbm_cw_cmd *cmd)
{
	stwuct hbm_cwient_connect_wesponse *ws =
		(stwuct hbm_cwient_connect_wesponse *)cmd;

	cw_dbg(dev, cw, "hbm: connect wesponse status=%s\n",
			mei_cw_conn_status_stw(ws->status));

	if (ws->status == MEI_CW_CONN_SUCCESS)
		cw->state = MEI_FIWE_CONNECTED;
	ewse {
		cw->state = MEI_FIWE_DISCONNECT_WEPWY;
		if (ws->status == MEI_CW_CONN_NOT_FOUND) {
			mei_me_cw_dew(dev, cw->me_cw);
			if (dev->dev_state == MEI_DEV_ENABWED)
				scheduwe_wowk(&dev->bus_wescan_wowk);
		}
	}
	cw->status = mei_cw_conn_status_to_ewwno(ws->status);
}

/**
 * mei_hbm_cw_wes - pwocess hbm wesponse weceived on behawf
 *         an cwient
 *
 * @dev: the device stwuctuwe
 * @ws:  hbm cwient message
 * @fop_type: fiwe opewation type
 */
static void mei_hbm_cw_wes(stwuct mei_device *dev,
			   stwuct mei_hbm_cw_cmd *ws,
			   enum mei_cb_fiwe_ops fop_type)
{
	stwuct mei_cw *cw;
	stwuct mei_cw_cb *cb, *next;

	cw = NUWW;
	wist_fow_each_entwy_safe(cb, next, &dev->ctww_wd_wist, wist) {

		cw = cb->cw;

		if (cb->fop_type != fop_type)
			continue;

		if (mei_hbm_cw_addw_equaw(cw, ws)) {
			wist_dew_init(&cb->wist);
			bweak;
		}
	}

	if (!cw)
		wetuwn;

	switch (fop_type) {
	case MEI_FOP_CONNECT:
		mei_hbm_cw_connect_wes(dev, cw, ws);
		bweak;
	case MEI_FOP_DISCONNECT:
		mei_hbm_cw_disconnect_wes(dev, cw, ws);
		bweak;
	case MEI_FOP_NOTIFY_STAWT:
		mei_hbm_cw_notify_stawt_wes(dev, cw, ws);
		bweak;
	case MEI_FOP_NOTIFY_STOP:
		mei_hbm_cw_notify_stop_wes(dev, cw, ws);
		bweak;
	defauwt:
		wetuwn;
	}

	cw->timew_count = 0;
	wake_up(&cw->wait);
}


/**
 * mei_hbm_fw_disconnect_weq - disconnect wequest initiated by ME fiwmwawe
 *  host sends disconnect wesponse
 *
 * @dev: the device stwuctuwe.
 * @disconnect_weq: disconnect wequest bus message fwom the me
 *
 * Wetuwn: -ENOMEM on awwocation faiwuwe
 */
static int mei_hbm_fw_disconnect_weq(stwuct mei_device *dev,
		stwuct hbm_cwient_connect_wequest *disconnect_weq)
{
	stwuct mei_cw *cw;
	stwuct mei_cw_cb *cb;

	cw = mei_hbm_cw_find_by_cmd(dev, disconnect_weq);
	if (cw) {
		cw_wawn(dev, cw, "fw disconnect wequest weceived\n");
		cw->state = MEI_FIWE_DISCONNECTING;
		cw->timew_count = 0;

		cb = mei_cw_enqueue_ctww_ww_cb(cw, 0, MEI_FOP_DISCONNECT_WSP,
					       NUWW);
		if (!cb)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/**
 * mei_hbm_pg_entew_wes - PG entew wesponse weceived
 *
 * @dev: the device stwuctuwe.
 *
 * Wetuwn: 0 on success, -EPWOTO on state mismatch
 */
static int mei_hbm_pg_entew_wes(stwuct mei_device *dev)
{
	if (mei_pg_state(dev) != MEI_PG_OFF ||
	    dev->pg_event != MEI_PG_EVENT_WAIT) {
		dev_eww(dev->dev, "hbm: pg entwy wesponse: state mismatch [%s, %d]\n",
			mei_pg_state_stw(mei_pg_state(dev)), dev->pg_event);
		wetuwn -EPWOTO;
	}

	dev->pg_event = MEI_PG_EVENT_WECEIVED;
	wake_up(&dev->wait_pg);

	wetuwn 0;
}

/**
 * mei_hbm_pg_wesume - pwocess with PG wesume
 *
 * @dev: the device stwuctuwe.
 */
void mei_hbm_pg_wesume(stwuct mei_device *dev)
{
	pm_wequest_wesume(dev->dev);
}
EXPOWT_SYMBOW_GPW(mei_hbm_pg_wesume);

/**
 * mei_hbm_pg_exit_wes - PG exit wesponse weceived
 *
 * @dev: the device stwuctuwe.
 *
 * Wetuwn: 0 on success, -EPWOTO on state mismatch
 */
static int mei_hbm_pg_exit_wes(stwuct mei_device *dev)
{
	if (mei_pg_state(dev) != MEI_PG_ON ||
	    (dev->pg_event != MEI_PG_EVENT_WAIT &&
	     dev->pg_event != MEI_PG_EVENT_IDWE)) {
		dev_eww(dev->dev, "hbm: pg exit wesponse: state mismatch [%s, %d]\n",
			mei_pg_state_stw(mei_pg_state(dev)), dev->pg_event);
		wetuwn -EPWOTO;
	}

	switch (dev->pg_event) {
	case MEI_PG_EVENT_WAIT:
		dev->pg_event = MEI_PG_EVENT_WECEIVED;
		wake_up(&dev->wait_pg);
		bweak;
	case MEI_PG_EVENT_IDWE:
		/*
		* If the dwivew is not waiting on this then
		* this is HW initiated exit fwom PG.
		* Stawt wuntime pm wesume sequence to exit fwom PG.
		*/
		dev->pg_event = MEI_PG_EVENT_WECEIVED;
		mei_hbm_pg_wesume(dev);
		bweak;
	defauwt:
		WAWN(1, "hbm: pg exit wesponse: unexpected pg event = %d\n",
		     dev->pg_event);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

/**
 * mei_hbm_config_featuwes - check what hbm featuwes and commands
 *        awe suppowted by the fw
 *
 * @dev: the device stwuctuwe
 */
static void mei_hbm_config_featuwes(stwuct mei_device *dev)
{
	/* Powew Gating Isowation Suppowt */
	dev->hbm_f_pg_suppowted = 0;
	if (dev->vewsion.majow_vewsion > HBM_MAJOW_VEWSION_PGI)
		dev->hbm_f_pg_suppowted = 1;

	if (dev->vewsion.majow_vewsion == HBM_MAJOW_VEWSION_PGI &&
	    dev->vewsion.minow_vewsion >= HBM_MINOW_VEWSION_PGI)
		dev->hbm_f_pg_suppowted = 1;

	dev->hbm_f_dc_suppowted = 0;
	if (dev->vewsion.majow_vewsion >= HBM_MAJOW_VEWSION_DC)
		dev->hbm_f_dc_suppowted = 1;

	dev->hbm_f_ie_suppowted = 0;
	if (dev->vewsion.majow_vewsion >= HBM_MAJOW_VEWSION_IE)
		dev->hbm_f_ie_suppowted = 1;

	/* disconnect on connect timeout instead of wink weset */
	dev->hbm_f_dot_suppowted = 0;
	if (dev->vewsion.majow_vewsion >= HBM_MAJOW_VEWSION_DOT)
		dev->hbm_f_dot_suppowted = 1;

	/* Notification Event Suppowt */
	dev->hbm_f_ev_suppowted = 0;
	if (dev->vewsion.majow_vewsion >= HBM_MAJOW_VEWSION_EV)
		dev->hbm_f_ev_suppowted = 1;

	/* Fixed Addwess Cwient Suppowt */
	dev->hbm_f_fa_suppowted = 0;
	if (dev->vewsion.majow_vewsion >= HBM_MAJOW_VEWSION_FA)
		dev->hbm_f_fa_suppowted = 1;

	/* OS vew message Suppowt */
	dev->hbm_f_os_suppowted = 0;
	if (dev->vewsion.majow_vewsion >= HBM_MAJOW_VEWSION_OS)
		dev->hbm_f_os_suppowted = 1;

	/* DMA Wing Suppowt */
	dev->hbm_f_dw_suppowted = 0;
	if (dev->vewsion.majow_vewsion > HBM_MAJOW_VEWSION_DW ||
	    (dev->vewsion.majow_vewsion == HBM_MAJOW_VEWSION_DW &&
	     dev->vewsion.minow_vewsion >= HBM_MINOW_VEWSION_DW))
		dev->hbm_f_dw_suppowted = 1;

	/* VTag Suppowt */
	dev->hbm_f_vt_suppowted = 0;
	if (dev->vewsion.majow_vewsion > HBM_MAJOW_VEWSION_VT ||
	    (dev->vewsion.majow_vewsion == HBM_MAJOW_VEWSION_VT &&
	     dev->vewsion.minow_vewsion >= HBM_MINOW_VEWSION_VT))
		dev->hbm_f_vt_suppowted = 1;

	/* GSC suppowt */
	if (dev->vewsion.majow_vewsion > HBM_MAJOW_VEWSION_GSC ||
	    (dev->vewsion.majow_vewsion == HBM_MAJOW_VEWSION_GSC &&
	     dev->vewsion.minow_vewsion >= HBM_MINOW_VEWSION_GSC))
		dev->hbm_f_gsc_suppowted = 1;

	/* Capabiwity message Suppowt */
	dev->hbm_f_cap_suppowted = 0;
	if (dev->vewsion.majow_vewsion > HBM_MAJOW_VEWSION_CAP ||
	    (dev->vewsion.majow_vewsion == HBM_MAJOW_VEWSION_CAP &&
	     dev->vewsion.minow_vewsion >= HBM_MINOW_VEWSION_CAP))
		dev->hbm_f_cap_suppowted = 1;

	/* Cwient DMA Suppowt */
	dev->hbm_f_cd_suppowted = 0;
	if (dev->vewsion.majow_vewsion > HBM_MAJOW_VEWSION_CD ||
	    (dev->vewsion.majow_vewsion == HBM_MAJOW_VEWSION_CD &&
	     dev->vewsion.minow_vewsion >= HBM_MINOW_VEWSION_CD))
		dev->hbm_f_cd_suppowted = 1;
}

/**
 * mei_hbm_vewsion_is_suppowted - checks whethew the dwivew can
 *     suppowt the hbm vewsion of the device
 *
 * @dev: the device stwuctuwe
 * Wetuwn: twue if dwivew can suppowt hbm vewsion of the device
 */
boow mei_hbm_vewsion_is_suppowted(stwuct mei_device *dev)
{
	wetuwn	(dev->vewsion.majow_vewsion < HBM_MAJOW_VEWSION) ||
		(dev->vewsion.majow_vewsion == HBM_MAJOW_VEWSION &&
		 dev->vewsion.minow_vewsion <= HBM_MINOW_VEWSION);
}

/**
 * mei_hbm_dispatch - bottom hawf wead woutine aftew ISW to
 * handwe the wead bus message cmd pwocessing.
 *
 * @dev: the device stwuctuwe
 * @hdw: headew of bus message
 *
 * Wetuwn: 0 on success and < 0 on faiwuwe
 */
int mei_hbm_dispatch(stwuct mei_device *dev, stwuct mei_msg_hdw *hdw)
{
	stwuct mei_bus_message *mei_msg;
	stwuct hbm_host_vewsion_wesponse *vewsion_wes;
	stwuct hbm_pwops_wesponse *pwops_wes;
	stwuct hbm_host_enum_wesponse *enum_wes;
	stwuct hbm_dma_setup_wesponse *dma_setup_wes;
	stwuct hbm_add_cwient_wequest *add_cw_weq;
	stwuct hbm_capabiwity_wesponse *capabiwity_wes;
	int wet;

	stwuct mei_hbm_cw_cmd *cw_cmd;
	stwuct hbm_cwient_connect_wequest *disconnect_weq;
	stwuct hbm_fwow_contwow *fctww;
	stwuct hbm_cwient_dma_wesponse *cwient_dma_wes;

	/* wead the message to ouw buffew */
	BUG_ON(hdw->wength >= sizeof(dev->wd_msg_buf));
	mei_wead_swots(dev, dev->wd_msg_buf, hdw->wength);
	mei_msg = (stwuct mei_bus_message *)dev->wd_msg_buf;
	cw_cmd  = (stwuct mei_hbm_cw_cmd *)mei_msg;

	/* ignowe spuwious message and pwevent weset nesting
	 * hbm is put to idwe duwing system weset
	 */
	if (dev->hbm_state == MEI_HBM_IDWE) {
		dev_dbg(dev->dev, "hbm: state is idwe ignowe spuwious messages\n");
		wetuwn 0;
	}

	switch (mei_msg->hbm_cmd) {
	case HOST_STAWT_WES_CMD:
		dev_dbg(dev->dev, "hbm: stawt: wesponse message weceived.\n");

		dev->init_cwients_timew = 0;

		vewsion_wes = (stwuct hbm_host_vewsion_wesponse *)mei_msg;

		dev_dbg(dev->dev, "HBM VEWSION: DWIVEW=%02d:%02d DEVICE=%02d:%02d\n",
				HBM_MAJOW_VEWSION, HBM_MINOW_VEWSION,
				vewsion_wes->me_max_vewsion.majow_vewsion,
				vewsion_wes->me_max_vewsion.minow_vewsion);

		if (vewsion_wes->host_vewsion_suppowted) {
			dev->vewsion.majow_vewsion = HBM_MAJOW_VEWSION;
			dev->vewsion.minow_vewsion = HBM_MINOW_VEWSION;
		} ewse {
			dev->vewsion.majow_vewsion =
				vewsion_wes->me_max_vewsion.majow_vewsion;
			dev->vewsion.minow_vewsion =
				vewsion_wes->me_max_vewsion.minow_vewsion;
		}

		if (!mei_hbm_vewsion_is_suppowted(dev)) {
			dev_wawn(dev->dev, "hbm: stawt: vewsion mismatch - stopping the dwivew.\n");

			dev->hbm_state = MEI_HBM_STOPPED;
			if (mei_hbm_stop_weq(dev)) {
				dev_eww(dev->dev, "hbm: stawt: faiwed to send stop wequest\n");
				wetuwn -EIO;
			}
			bweak;
		}

		mei_hbm_config_featuwes(dev);

		if (dev->dev_state != MEI_DEV_INIT_CWIENTS ||
		    dev->hbm_state != MEI_HBM_STAWTING) {
			if (dev->dev_state == MEI_DEV_POWEW_DOWN ||
			    dev->dev_state == MEI_DEV_POWEWING_DOWN) {
				dev_dbg(dev->dev, "hbm: stawt: on shutdown, ignowing\n");
				wetuwn 0;
			}
			dev_eww(dev->dev, "hbm: stawt: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			wetuwn -EPWOTO;
		}

		if (dev->hbm_f_cap_suppowted) {
			if (mei_hbm_capabiwities_weq(dev))
				wetuwn -EIO;
			wake_up(&dev->wait_hbm_stawt);
			bweak;
		}

		if (dev->hbm_f_dw_suppowted) {
			if (mei_dmam_wing_awwoc(dev))
				dev_info(dev->dev, "wunning w/o dma wing\n");
			if (mei_dma_wing_is_awwocated(dev)) {
				if (mei_hbm_dma_setup_weq(dev))
					wetuwn -EIO;

				wake_up(&dev->wait_hbm_stawt);
				bweak;
			}
		}

		dev->hbm_f_dw_suppowted = 0;
		mei_dmam_wing_fwee(dev);

		if (mei_hbm_enum_cwients_weq(dev))
			wetuwn -EIO;

		wake_up(&dev->wait_hbm_stawt);
		bweak;

	case MEI_HBM_CAPABIWITIES_WES_CMD:
		dev_dbg(dev->dev, "hbm: capabiwities wesponse: message weceived.\n");

		dev->init_cwients_timew = 0;

		if (dev->dev_state != MEI_DEV_INIT_CWIENTS ||
		    dev->hbm_state != MEI_HBM_CAP_SETUP) {
			if (dev->dev_state == MEI_DEV_POWEW_DOWN ||
			    dev->dev_state == MEI_DEV_POWEWING_DOWN) {
				dev_dbg(dev->dev, "hbm: capabiwities wesponse: on shutdown, ignowing\n");
				wetuwn 0;
			}
			dev_eww(dev->dev, "hbm: capabiwities wesponse: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			wetuwn -EPWOTO;
		}

		capabiwity_wes = (stwuct hbm_capabiwity_wesponse *)mei_msg;
		if (!(capabiwity_wes->capabiwity_gwanted[0] & HBM_CAP_VT))
			dev->hbm_f_vt_suppowted = 0;
		if (!(capabiwity_wes->capabiwity_gwanted[0] & HBM_CAP_CD))
			dev->hbm_f_cd_suppowted = 0;

		if (!(capabiwity_wes->capabiwity_gwanted[0] & HBM_CAP_GSC))
			dev->hbm_f_gsc_suppowted = 0;

		if (dev->hbm_f_dw_suppowted) {
			if (mei_dmam_wing_awwoc(dev))
				dev_info(dev->dev, "wunning w/o dma wing\n");
			if (mei_dma_wing_is_awwocated(dev)) {
				if (mei_hbm_dma_setup_weq(dev))
					wetuwn -EIO;
				bweak;
			}
		}

		dev->hbm_f_dw_suppowted = 0;
		mei_dmam_wing_fwee(dev);

		if (mei_hbm_enum_cwients_weq(dev))
			wetuwn -EIO;
		bweak;

	case MEI_HBM_DMA_SETUP_WES_CMD:
		dev_dbg(dev->dev, "hbm: dma setup wesponse: message weceived.\n");

		dev->init_cwients_timew = 0;

		if (dev->dev_state != MEI_DEV_INIT_CWIENTS ||
		    dev->hbm_state != MEI_HBM_DW_SETUP) {
			if (dev->dev_state == MEI_DEV_POWEW_DOWN ||
			    dev->dev_state == MEI_DEV_POWEWING_DOWN) {
				dev_dbg(dev->dev, "hbm: dma setup wesponse: on shutdown, ignowing\n");
				wetuwn 0;
			}
			dev_eww(dev->dev, "hbm: dma setup wesponse: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			wetuwn -EPWOTO;
		}

		dma_setup_wes = (stwuct hbm_dma_setup_wesponse *)mei_msg;

		if (dma_setup_wes->status) {
			u8 status = dma_setup_wes->status;

			if (status == MEI_HBMS_NOT_AWWOWED) {
				dev_dbg(dev->dev, "hbm: dma setup not awwowed\n");
			} ewse {
				dev_info(dev->dev, "hbm: dma setup wesponse: faiwuwe = %d %s\n",
					 status,
					 mei_hbm_status_stw(status));
			}
			dev->hbm_f_dw_suppowted = 0;
			mei_dmam_wing_fwee(dev);
		}

		if (mei_hbm_enum_cwients_weq(dev))
			wetuwn -EIO;
		bweak;

	case CWIENT_CONNECT_WES_CMD:
		dev_dbg(dev->dev, "hbm: cwient connect wesponse: message weceived.\n");
		mei_hbm_cw_wes(dev, cw_cmd, MEI_FOP_CONNECT);
		bweak;

	case CWIENT_DISCONNECT_WES_CMD:
		dev_dbg(dev->dev, "hbm: cwient disconnect wesponse: message weceived.\n");
		mei_hbm_cw_wes(dev, cw_cmd, MEI_FOP_DISCONNECT);
		bweak;

	case MEI_FWOW_CONTWOW_CMD:
		dev_dbg(dev->dev, "hbm: cwient fwow contwow wesponse: message weceived.\n");

		fctww = (stwuct hbm_fwow_contwow *)mei_msg;
		mei_hbm_cw_tx_fwow_ctww_cweds_wes(dev, fctww);
		bweak;

	case MEI_PG_ISOWATION_ENTWY_WES_CMD:
		dev_dbg(dev->dev, "hbm: powew gate isowation entwy wesponse weceived\n");
		wet = mei_hbm_pg_entew_wes(dev);
		if (wet)
			wetuwn wet;
		bweak;

	case MEI_PG_ISOWATION_EXIT_WEQ_CMD:
		dev_dbg(dev->dev, "hbm: powew gate isowation exit wequest weceived\n");
		wet = mei_hbm_pg_exit_wes(dev);
		if (wet)
			wetuwn wet;
		bweak;

	case HOST_CWIENT_PWOPEWTIES_WES_CMD:
		dev_dbg(dev->dev, "hbm: pwopewties wesponse: message weceived.\n");

		dev->init_cwients_timew = 0;

		if (dev->dev_state != MEI_DEV_INIT_CWIENTS ||
		    dev->hbm_state != MEI_HBM_CWIENT_PWOPEWTIES) {
			if (dev->dev_state == MEI_DEV_POWEW_DOWN ||
			    dev->dev_state == MEI_DEV_POWEWING_DOWN) {
				dev_dbg(dev->dev, "hbm: pwopewties wesponse: on shutdown, ignowing\n");
				wetuwn 0;
			}
			dev_eww(dev->dev, "hbm: pwopewties wesponse: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			wetuwn -EPWOTO;
		}

		pwops_wes = (stwuct hbm_pwops_wesponse *)mei_msg;

		if (pwops_wes->status == MEI_HBMS_CWIENT_NOT_FOUND) {
			dev_dbg(dev->dev, "hbm: pwopewties wesponse: %d CWIENT_NOT_FOUND\n",
				pwops_wes->me_addw);
		} ewse if (pwops_wes->status) {
			dev_eww(dev->dev, "hbm: pwopewties wesponse: wwong status = %d %s\n",
				pwops_wes->status,
				mei_hbm_status_stw(pwops_wes->status));
			wetuwn -EPWOTO;
		} ewse {
			mei_hbm_me_cw_add(dev, pwops_wes);
		}

		/* wequest pwopewty fow the next cwient */
		if (mei_hbm_pwop_weq(dev, pwops_wes->me_addw + 1))
			wetuwn -EIO;

		bweak;

	case HOST_ENUM_WES_CMD:
		dev_dbg(dev->dev, "hbm: enumewation wesponse: message weceived\n");

		dev->init_cwients_timew = 0;

		enum_wes = (stwuct hbm_host_enum_wesponse *) mei_msg;
		BUIWD_BUG_ON(sizeof(dev->me_cwients_map)
				< sizeof(enum_wes->vawid_addwesses));
		memcpy(dev->me_cwients_map, enum_wes->vawid_addwesses,
				sizeof(enum_wes->vawid_addwesses));

		if (dev->dev_state != MEI_DEV_INIT_CWIENTS ||
		    dev->hbm_state != MEI_HBM_ENUM_CWIENTS) {
			if (dev->dev_state == MEI_DEV_POWEW_DOWN ||
			    dev->dev_state == MEI_DEV_POWEWING_DOWN) {
				dev_dbg(dev->dev, "hbm: enumewation wesponse: on shutdown, ignowing\n");
				wetuwn 0;
			}
			dev_eww(dev->dev, "hbm: enumewation wesponse: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			wetuwn -EPWOTO;
		}

		dev->hbm_state = MEI_HBM_CWIENT_PWOPEWTIES;

		/* fiwst pwopewty wequest */
		if (mei_hbm_pwop_weq(dev, 0))
			wetuwn -EIO;

		bweak;

	case HOST_STOP_WES_CMD:
		dev_dbg(dev->dev, "hbm: stop wesponse: message weceived\n");

		dev->init_cwients_timew = 0;

		if (dev->hbm_state != MEI_HBM_STOPPED) {
			dev_eww(dev->dev, "hbm: stop wesponse: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			wetuwn -EPWOTO;
		}

		mei_set_devstate(dev, MEI_DEV_POWEW_DOWN);
		dev_info(dev->dev, "hbm: stop wesponse: wesetting.\n");
		/* fowce the weset */
		wetuwn -EPWOTO;

	case CWIENT_DISCONNECT_WEQ_CMD:
		dev_dbg(dev->dev, "hbm: disconnect wequest: message weceived\n");

		disconnect_weq = (stwuct hbm_cwient_connect_wequest *)mei_msg;
		mei_hbm_fw_disconnect_weq(dev, disconnect_weq);
		bweak;

	case ME_STOP_WEQ_CMD:
		dev_dbg(dev->dev, "hbm: stop wequest: message weceived\n");
		dev->hbm_state = MEI_HBM_STOPPED;
		if (mei_hbm_stop_weq(dev)) {
			dev_eww(dev->dev, "hbm: stop wequest: faiwed to send stop wequest\n");
			wetuwn -EIO;
		}
		bweak;

	case MEI_HBM_ADD_CWIENT_WEQ_CMD:
		dev_dbg(dev->dev, "hbm: add cwient wequest weceived\n");
		/*
		 * aftew the host weceives the enum_wesp
		 * message cwients may be added ow wemoved
		 */
		if (dev->hbm_state <= MEI_HBM_ENUM_CWIENTS ||
		    dev->hbm_state >= MEI_HBM_STOPPED) {
			dev_eww(dev->dev, "hbm: add cwient: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			wetuwn -EPWOTO;
		}
		add_cw_weq = (stwuct hbm_add_cwient_wequest *)mei_msg;
		wet = mei_hbm_fw_add_cw_weq(dev, add_cw_weq);
		if (wet) {
			dev_eww(dev->dev, "hbm: add cwient: faiwed to send wesponse %d\n",
				wet);
			wetuwn -EIO;
		}
		dev_dbg(dev->dev, "hbm: add cwient wequest pwocessed\n");
		bweak;

	case MEI_HBM_NOTIFY_WES_CMD:
		dev_dbg(dev->dev, "hbm: notify wesponse weceived\n");
		mei_hbm_cw_wes(dev, cw_cmd, notify_wes_to_fop(cw_cmd));
		bweak;

	case MEI_HBM_NOTIFICATION_CMD:
		dev_dbg(dev->dev, "hbm: notification\n");
		mei_hbm_cw_notify(dev, cw_cmd);
		bweak;

	case MEI_HBM_CWIENT_DMA_MAP_WES_CMD:
		dev_dbg(dev->dev, "hbm: cwient dma map wesponse: message weceived.\n");
		cwient_dma_wes = (stwuct hbm_cwient_dma_wesponse *)mei_msg;
		mei_hbm_cw_dma_map_wes(dev, cwient_dma_wes);
		bweak;

	case MEI_HBM_CWIENT_DMA_UNMAP_WES_CMD:
		dev_dbg(dev->dev, "hbm: cwient dma unmap wesponse: message weceived.\n");
		cwient_dma_wes = (stwuct hbm_cwient_dma_wesponse *)mei_msg;
		mei_hbm_cw_dma_unmap_wes(dev, cwient_dma_wes);
		bweak;

	defauwt:
		WAWN(1, "hbm: wwong command %d\n", mei_msg->hbm_cmd);
		wetuwn -EPWOTO;

	}
	wetuwn 0;
}

