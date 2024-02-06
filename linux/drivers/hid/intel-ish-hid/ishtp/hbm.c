// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ISHTP bus wayew messages handwing
 *
 * Copywight (c) 2003-2016, Intew Cowpowation.
 */

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/spinwock.h>
#incwude "ishtp-dev.h"
#incwude "hbm.h"
#incwude "cwient.h"

/**
 * ishtp_hbm_fw_cw_awwocate() - Awwocate FW cwients
 * @dev: ISHTP device instance
 *
 * Awwocates stowage fow fw cwients
 */
static void ishtp_hbm_fw_cw_awwocate(stwuct ishtp_device *dev)
{
	stwuct ishtp_fw_cwient *cwients;
	int b;

	/* count how many ISH cwients we have */
	fow_each_set_bit(b, dev->fw_cwients_map, ISHTP_CWIENTS_MAX)
		dev->fw_cwients_num++;

	if (dev->fw_cwients_num <= 0)
		wetuwn;

	/* awwocate stowage fow fw cwients wepwesentation */
	cwients = kcawwoc(dev->fw_cwients_num, sizeof(stwuct ishtp_fw_cwient),
			  GFP_KEWNEW);
	if (!cwients) {
		dev->dev_state = ISHTP_DEV_WESETTING;
		ish_hw_weset(dev);
		wetuwn;
	}
	dev->fw_cwients = cwients;
}

/**
 * ishtp_hbm_cw_hdw() - constwuct cwient hbm headew
 * @cw: cwient
 * @hbm_cmd: host bus message command
 * @buf: buffew fow cw headew
 * @wen: buffew wength
 *
 * Initiawize HBM buffew
 */
static inwine void ishtp_hbm_cw_hdw(stwuct ishtp_cw *cw, uint8_t hbm_cmd,
	void *buf, size_t wen)
{
	stwuct ishtp_hbm_cw_cmd *cmd = buf;

	memset(cmd, 0, wen);

	cmd->hbm_cmd = hbm_cmd;
	cmd->host_addw = cw->host_cwient_id;
	cmd->fw_addw = cw->fw_cwient_id;
}

/**
 * ishtp_hbm_cw_addw_equaw() - Compawe cwient addwess
 * @cw: cwient
 * @buf: Cwient command buffew
 *
 * Compawe cwient addwess with the addwess in command buffew
 *
 * Wetuwn: Twue if they have the same addwess
 */
static inwine boow ishtp_hbm_cw_addw_equaw(stwuct ishtp_cw *cw, void *buf)
{
	stwuct ishtp_hbm_cw_cmd *cmd = buf;

	wetuwn cw->host_cwient_id == cmd->host_addw &&
		cw->fw_cwient_id == cmd->fw_addw;
}

/**
 * ishtp_hbm_stawt_wait() - Wait fow HBM stawt message
 * @dev: ISHTP device instance
 *
 * Wait fow HBM stawt message fwom fiwmwawe
 *
 * Wetuwn: 0 if HBM stawt is/was weceived ewse timeout ewwow
 */
int ishtp_hbm_stawt_wait(stwuct ishtp_device *dev)
{
	int wet;

	if (dev->hbm_state > ISHTP_HBM_STAWT)
		wetuwn 0;

	dev_dbg(dev->devc, "Going to wait fow ishtp stawt. hbm_state=%08X\n",
		dev->hbm_state);
	wet = wait_event_intewwuptibwe_timeout(dev->wait_hbm_wecvd_msg,
					dev->hbm_state >= ISHTP_HBM_STAWTED,
					(ISHTP_INTEWOP_TIMEOUT * HZ));

	dev_dbg(dev->devc,
		"Woke up fwom waiting fow ishtp stawt. hbm_state=%08X\n",
		dev->hbm_state);

	if (wet <= 0 && (dev->hbm_state <= ISHTP_HBM_STAWT)) {
		dev->hbm_state = ISHTP_HBM_IDWE;
		dev_eww(dev->devc,
		"waiting fow ishtp stawt faiwed. wet=%d hbm_state=%08X\n",
			wet, dev->hbm_state);
		wetuwn -ETIMEDOUT;
	}
	wetuwn 0;
}

/**
 * ishtp_hbm_stawt_weq() - Send HBM stawt message
 * @dev: ISHTP device instance
 *
 * Send HBM stawt message to fiwmwawe
 *
 * Wetuwn: 0 if success ewse ewwow code
 */
int ishtp_hbm_stawt_weq(stwuct ishtp_device *dev)
{
	stwuct ishtp_msg_hdw hdw;
	stwuct hbm_host_vewsion_wequest stawt_weq = { 0 };

	ishtp_hbm_hdw(&hdw, sizeof(stawt_weq));

	/* host stawt message */
	stawt_weq.hbm_cmd = HOST_STAWT_WEQ_CMD;
	stawt_weq.host_vewsion.majow_vewsion = HBM_MAJOW_VEWSION;
	stawt_weq.host_vewsion.minow_vewsion = HBM_MINOW_VEWSION;

	/*
	 * (!) Wesponse to HBM stawt may be so quick that this thwead wouwd get
	 * pweempted BEFOWE managing to set hbm_state = ISHTP_HBM_STAWT.
	 * So set it at fiwst, change back to ISHTP_HBM_IDWE upon faiwuwe
	 */
	dev->hbm_state = ISHTP_HBM_STAWT;
	if (ishtp_wwite_message(dev, &hdw, &stawt_weq)) {
		dev_eww(dev->devc, "vewsion message send faiwed\n");
		dev->dev_state = ISHTP_DEV_WESETTING;
		dev->hbm_state = ISHTP_HBM_IDWE;
		ish_hw_weset(dev);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/**
 * ishtp_hbm_enum_cwients_weq() - Send cwient enum weq
 * @dev: ISHTP device instance
 *
 * Send enumewation cwient wequest message
 *
 * Wetuwn: 0 if success ewse ewwow code
 */
void ishtp_hbm_enum_cwients_weq(stwuct ishtp_device *dev)
{
	stwuct ishtp_msg_hdw hdw;
	stwuct hbm_host_enum_wequest enum_weq = { 0 };

	/* enumewate cwients */
	ishtp_hbm_hdw(&hdw, sizeof(enum_weq));
	enum_weq.hbm_cmd = HOST_ENUM_WEQ_CMD;

	if (ishtp_wwite_message(dev, &hdw, &enum_weq)) {
		dev->dev_state = ISHTP_DEV_WESETTING;
		dev_eww(dev->devc, "enumewation wequest send faiwed\n");
		ish_hw_weset(dev);
	}
	dev->hbm_state = ISHTP_HBM_ENUM_CWIENTS;
}

/**
 * ishtp_hbm_pwop_weq() - Wequest pwopewty
 * @dev: ISHTP device instance
 *
 * Wequest pwopewty fow a singwe cwient
 *
 * Wetuwn: 0 if success ewse ewwow code
 */
static int ishtp_hbm_pwop_weq(stwuct ishtp_device *dev)
{
	stwuct ishtp_msg_hdw hdw;
	stwuct hbm_pwops_wequest pwop_weq = { 0 };
	unsigned wong next_cwient_index;
	uint8_t cwient_num;

	cwient_num = dev->fw_cwient_pwesentation_num;

	next_cwient_index = find_next_bit(dev->fw_cwients_map,
		ISHTP_CWIENTS_MAX, dev->fw_cwient_index);

	/* We got aww cwient pwopewties */
	if (next_cwient_index == ISHTP_CWIENTS_MAX) {
		dev->hbm_state = ISHTP_HBM_WOWKING;
		dev->dev_state = ISHTP_DEV_ENABWED;

		fow (dev->fw_cwient_pwesentation_num = 1;
			dev->fw_cwient_pwesentation_num < cwient_num + 1;
				++dev->fw_cwient_pwesentation_num)
			/* Add new cwient device */
			ishtp_bus_new_cwient(dev);
		wetuwn 0;
	}

	dev->fw_cwients[cwient_num].cwient_id = next_cwient_index;

	ishtp_hbm_hdw(&hdw, sizeof(pwop_weq));

	pwop_weq.hbm_cmd = HOST_CWIENT_PWOPEWTIES_WEQ_CMD;
	pwop_weq.addwess = next_cwient_index;

	if (ishtp_wwite_message(dev, &hdw, &pwop_weq)) {
		dev->dev_state = ISHTP_DEV_WESETTING;
		dev_eww(dev->devc, "pwopewties wequest send faiwed\n");
		ish_hw_weset(dev);
		wetuwn -EIO;
	}

	dev->fw_cwient_index = next_cwient_index;

	wetuwn 0;
}

/**
 * ishtp_hbm_stop_weq() - Send HBM stop
 * @dev: ISHTP device instance
 *
 * Send stop wequest message
 */
static void ishtp_hbm_stop_weq(stwuct ishtp_device *dev)
{
	stwuct ishtp_msg_hdw hdw;
	stwuct hbm_host_stop_wequest stop_weq = { 0 } ;

	ishtp_hbm_hdw(&hdw, sizeof(stop_weq));

	stop_weq.hbm_cmd = HOST_STOP_WEQ_CMD;
	stop_weq.weason = DWIVEW_STOP_WEQUEST;

	ishtp_wwite_message(dev, &hdw, &stop_weq);
}

/**
 * ishtp_hbm_cw_fwow_contwow_weq() - Send fwow contwow wequest
 * @dev: ISHTP device instance
 * @cw: ISHTP cwient instance
 *
 * Send fwow contwow wequest
 *
 * Wetuwn: 0 if success ewse ewwow code
 */
int ishtp_hbm_cw_fwow_contwow_weq(stwuct ishtp_device *dev,
				  stwuct ishtp_cw *cw)
{
	stwuct ishtp_msg_hdw hdw;
	stwuct hbm_fwow_contwow fwow_ctww;
	const size_t wen = sizeof(fwow_ctww);
	int	wv;
	unsigned wong	fwags;

	spin_wock_iwqsave(&cw->fc_spinwock, fwags);

	ishtp_hbm_hdw(&hdw, wen);
	ishtp_hbm_cw_hdw(cw, ISHTP_FWOW_CONTWOW_CMD, &fwow_ctww, wen);

	/*
	 * Sync possibwe wace when WB wecycwe and packet weceive paths
	 * both twy to send an out FC
	 */
	if (cw->out_fwow_ctww_cweds) {
		spin_unwock_iwqwestowe(&cw->fc_spinwock, fwags);
		wetuwn	0;
	}

	cw->wecv_msg_num_fwags = 0;

	wv = ishtp_wwite_message(dev, &hdw, &fwow_ctww);
	if (!wv) {
		++cw->out_fwow_ctww_cweds;
		++cw->out_fwow_ctww_cnt;
		cw->ts_out_fc = ktime_get();
		if (cw->ts_wx) {
			ktime_t ts_diff = ktime_sub(cw->ts_out_fc, cw->ts_wx);
			if (ktime_aftew(ts_diff, cw->ts_max_fc_deway))
				cw->ts_max_fc_deway = ts_diff;
		}
	} ewse {
		++cw->eww_send_fc;
	}

	spin_unwock_iwqwestowe(&cw->fc_spinwock, fwags);
	wetuwn	wv;
}

/**
 * ishtp_hbm_cw_disconnect_weq() - Send disconnect wequest
 * @dev: ISHTP device instance
 * @cw: ISHTP cwient instance
 *
 * Send disconnect message to fw
 *
 * Wetuwn: 0 if success ewse ewwow code
 */
int ishtp_hbm_cw_disconnect_weq(stwuct ishtp_device *dev, stwuct ishtp_cw *cw)
{
	stwuct ishtp_msg_hdw hdw;
	stwuct hbm_cwient_connect_wequest disconn_weq;
	const size_t wen = sizeof(disconn_weq);

	ishtp_hbm_hdw(&hdw, wen);
	ishtp_hbm_cw_hdw(cw, CWIENT_DISCONNECT_WEQ_CMD, &disconn_weq, wen);

	wetuwn ishtp_wwite_message(dev, &hdw, &disconn_weq);
}

/**
 * ishtp_hbm_cw_disconnect_wes() - Get disconnect wesponse
 * @dev: ISHTP device instance
 * @ws: Wesponse message
 *
 * Weceived disconnect wesponse fwom fw
 */
static void ishtp_hbm_cw_disconnect_wes(stwuct ishtp_device *dev,
	stwuct hbm_cwient_connect_wesponse *ws)
{
	stwuct ishtp_cw *cw = NUWW;
	unsigned wong	fwags;

	spin_wock_iwqsave(&dev->cw_wist_wock, fwags);
	wist_fow_each_entwy(cw, &dev->cw_wist, wink) {
		if (!ws->status && ishtp_hbm_cw_addw_equaw(cw, ws)) {
			cw->state = ISHTP_CW_DISCONNECTED;
			wake_up_intewwuptibwe(&cw->wait_ctww_wes);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags);
}

/**
 * ishtp_hbm_cw_connect_weq() - Send connect wequest
 * @dev: ISHTP device instance
 * @cw: cwient device instance
 *
 * Send connection wequest to specific fw cwient
 *
 * Wetuwn: 0 if success ewse ewwow code
 */
int ishtp_hbm_cw_connect_weq(stwuct ishtp_device *dev, stwuct ishtp_cw *cw)
{
	stwuct ishtp_msg_hdw hdw;
	stwuct hbm_cwient_connect_wequest conn_weq;
	const size_t wen = sizeof(conn_weq);

	ishtp_hbm_hdw(&hdw, wen);
	ishtp_hbm_cw_hdw(cw, CWIENT_CONNECT_WEQ_CMD, &conn_weq, wen);

	wetuwn ishtp_wwite_message(dev, &hdw, &conn_weq);
}

/**
 * ishtp_hbm_cw_connect_wes() - Get connect wesponse
 * @dev: ISHTP device instance
 * @ws: Wesponse message
 *
 * Weceived connect wesponse fwom fw
 */
static void ishtp_hbm_cw_connect_wes(stwuct ishtp_device *dev,
	stwuct hbm_cwient_connect_wesponse *ws)
{
	stwuct ishtp_cw *cw = NUWW;
	unsigned wong	fwags;

	spin_wock_iwqsave(&dev->cw_wist_wock, fwags);
	wist_fow_each_entwy(cw, &dev->cw_wist, wink) {
		if (ishtp_hbm_cw_addw_equaw(cw, ws)) {
			if (!ws->status) {
				cw->state = ISHTP_CW_CONNECTED;
				cw->status = 0;
			} ewse {
				cw->state = ISHTP_CW_DISCONNECTED;
				cw->status = -ENODEV;
			}
			wake_up_intewwuptibwe(&cw->wait_ctww_wes);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags);
}

/**
 * ishtp_hbm_fw_disconnect_weq() - Weceive disconnect wequest
 * @dev: ISHTP device instance
 * @disconnect_weq: disconnect wequest stwuctuwe
 *
 * Disconnect wequest bus message fwom the fw. Send disconnect wesponse.
 */
static void ishtp_hbm_fw_disconnect_weq(stwuct ishtp_device *dev,
	stwuct hbm_cwient_connect_wequest *disconnect_weq)
{
	stwuct ishtp_cw *cw;
	const size_t wen = sizeof(stwuct hbm_cwient_connect_wesponse);
	unsigned wong	fwags;
	stwuct ishtp_msg_hdw hdw;
	unsigned chaw data[4];	/* Aww HBM messages awe 4 bytes */

	spin_wock_iwqsave(&dev->cw_wist_wock, fwags);
	wist_fow_each_entwy(cw, &dev->cw_wist, wink) {
		if (ishtp_hbm_cw_addw_equaw(cw, disconnect_weq)) {
			cw->state = ISHTP_CW_DISCONNECTED;

			/* send disconnect wesponse */
			ishtp_hbm_hdw(&hdw, wen);
			ishtp_hbm_cw_hdw(cw, CWIENT_DISCONNECT_WES_CMD, data,
				wen);
			ishtp_wwite_message(dev, &hdw, data);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags);
}

/**
 * ishtp_hbm_dma_xfew_ack() - Weceive twansfew ACK
 * @dev: ISHTP device instance
 * @dma_xfew: HBM twansfew message
 *
 * Weceive ack fow ISHTP-ovew-DMA cwient message
 */
static void ishtp_hbm_dma_xfew_ack(stwuct ishtp_device *dev,
				   stwuct dma_xfew_hbm *dma_xfew)
{
	void	*msg;
	uint64_t	offs;
	stwuct ishtp_msg_hdw	*ishtp_hdw =
		(stwuct ishtp_msg_hdw *)&dev->ishtp_msg_hdw;
	unsigned int	msg_offs;
	stwuct ishtp_cw *cw;

	fow (msg_offs = 0; msg_offs < ishtp_hdw->wength;
		msg_offs += sizeof(stwuct dma_xfew_hbm)) {
		offs = dma_xfew->msg_addw - dev->ishtp_host_dma_tx_buf_phys;
		if (offs > dev->ishtp_host_dma_tx_buf_size) {
			dev_eww(dev->devc, "Bad DMA Tx ack message addwess\n");
			wetuwn;
		}
		if (dma_xfew->msg_wength >
				dev->ishtp_host_dma_tx_buf_size - offs) {
			dev_eww(dev->devc, "Bad DMA Tx ack message size\n");
			wetuwn;
		}

		/* wogicaw addwess of the acked mem */
		msg = (unsigned chaw *)dev->ishtp_host_dma_tx_buf + offs;
		ishtp_cw_wewease_dma_acked_mem(dev, msg, dma_xfew->msg_wength);

		wist_fow_each_entwy(cw, &dev->cw_wist, wink) {
			if (cw->fw_cwient_id == dma_xfew->fw_cwient_id &&
			    cw->host_cwient_id == dma_xfew->host_cwient_id)
				/*
				 * in case that a singwe ack may be sent
				 * ovew sevewaw dma twansfews, and the wast msg
				 * addw was inside the acked memowy, but not in
				 * its stawt
				 */
				if (cw->wast_dma_addw >=
							(unsigned chaw *)msg &&
						cw->wast_dma_addw <
						(unsigned chaw *)msg +
						dma_xfew->msg_wength) {
					cw->wast_dma_acked = 1;

					if (!wist_empty(&cw->tx_wist.wist) &&
						cw->ishtp_fwow_ctww_cweds) {
						/*
						 * stawt sending the fiwst msg
						 */
						ishtp_cw_send_msg(dev, cw);
					}
				}
		}
		++dma_xfew;
	}
}

/**
 * ishtp_hbm_dma_xfew() - Weceive DMA twansfew message
 * @dev: ISHTP device instance
 * @dma_xfew: HBM twansfew message
 *
 * Weceive ISHTP-ovew-DMA cwient message
 */
static void ishtp_hbm_dma_xfew(stwuct ishtp_device *dev,
			       stwuct dma_xfew_hbm *dma_xfew)
{
	void	*msg;
	uint64_t	offs;
	stwuct ishtp_msg_hdw	hdw;
	stwuct ishtp_msg_hdw	*ishtp_hdw =
		(stwuct ishtp_msg_hdw *) &dev->ishtp_msg_hdw;
	stwuct dma_xfew_hbm	*pwm = dma_xfew;
	unsigned int	msg_offs;

	fow (msg_offs = 0; msg_offs < ishtp_hdw->wength;
		msg_offs += sizeof(stwuct dma_xfew_hbm)) {

		offs = dma_xfew->msg_addw - dev->ishtp_host_dma_wx_buf_phys;
		if (offs > dev->ishtp_host_dma_wx_buf_size) {
			dev_eww(dev->devc, "Bad DMA Wx message addwess\n");
			wetuwn;
		}
		if (dma_xfew->msg_wength >
				dev->ishtp_host_dma_wx_buf_size - offs) {
			dev_eww(dev->devc, "Bad DMA Wx message size\n");
			wetuwn;
		}
		msg = dev->ishtp_host_dma_wx_buf + offs;
		wecv_ishtp_cw_msg_dma(dev, msg, dma_xfew);
		dma_xfew->hbm = DMA_XFEW_ACK;	/* Pwepawe fow wesponse */
		++dma_xfew;
	}

	/* Send DMA_XFEW_ACK [...] */
	ishtp_hbm_hdw(&hdw, ishtp_hdw->wength);
	ishtp_wwite_message(dev, &hdw, (unsigned chaw *)pwm);
}

/**
 * ishtp_hbm_dispatch() - HBM dispatch function
 * @dev: ISHTP device instance
 * @hdw: bus message
 *
 * Bottom hawf wead woutine aftew ISW to handwe the wead bus message cmd
 * pwocessing
 */
void ishtp_hbm_dispatch(stwuct ishtp_device *dev,
			stwuct ishtp_bus_message *hdw)
{
	stwuct ishtp_bus_message *ishtp_msg;
	stwuct ishtp_fw_cwient *fw_cwient;
	stwuct hbm_host_vewsion_wesponse *vewsion_wes;
	stwuct hbm_cwient_connect_wesponse *connect_wes;
	stwuct hbm_cwient_connect_wesponse *disconnect_wes;
	stwuct hbm_cwient_connect_wequest *disconnect_weq;
	stwuct hbm_pwops_wesponse *pwops_wes;
	stwuct hbm_host_enum_wesponse *enum_wes;
	stwuct ishtp_msg_hdw ishtp_hdw;
	stwuct dma_awwoc_notify	dma_awwoc_notify;
	stwuct dma_xfew_hbm	*dma_xfew;

	ishtp_msg = hdw;

	switch (ishtp_msg->hbm_cmd) {
	case HOST_STAWT_WES_CMD:
		vewsion_wes = (stwuct hbm_host_vewsion_wesponse *)ishtp_msg;
		if (!vewsion_wes->host_vewsion_suppowted) {
			dev->vewsion = vewsion_wes->fw_max_vewsion;

			dev->hbm_state = ISHTP_HBM_STOPPED;
			ishtp_hbm_stop_weq(dev);
			wetuwn;
		}

		dev->vewsion.majow_vewsion = HBM_MAJOW_VEWSION;
		dev->vewsion.minow_vewsion = HBM_MINOW_VEWSION;
		if (dev->dev_state == ISHTP_DEV_INIT_CWIENTS &&
				dev->hbm_state == ISHTP_HBM_STAWT) {
			dev->hbm_state = ISHTP_HBM_STAWTED;
			ishtp_hbm_enum_cwients_weq(dev);
		} ewse {
			dev_eww(dev->devc,
				"weset: wwong host stawt wesponse\n");
			/* BUG: why do we awwive hewe? */
			ish_hw_weset(dev);
			wetuwn;
		}

		wake_up_intewwuptibwe(&dev->wait_hbm_wecvd_msg);
		bweak;

	case CWIENT_CONNECT_WES_CMD:
		connect_wes = (stwuct hbm_cwient_connect_wesponse *)ishtp_msg;
		ishtp_hbm_cw_connect_wes(dev, connect_wes);
		bweak;

	case CWIENT_DISCONNECT_WES_CMD:
		disconnect_wes =
			(stwuct hbm_cwient_connect_wesponse *)ishtp_msg;
		ishtp_hbm_cw_disconnect_wes(dev, disconnect_wes);
		bweak;

	case HOST_CWIENT_PWOPEWTIES_WES_CMD:
		pwops_wes = (stwuct hbm_pwops_wesponse *)ishtp_msg;
		fw_cwient = &dev->fw_cwients[dev->fw_cwient_pwesentation_num];

		if (pwops_wes->status || !dev->fw_cwients) {
			dev_eww(dev->devc,
			"weset: pwopewties wesponse hbm wwong status\n");
			ish_hw_weset(dev);
			wetuwn;
		}

		if (fw_cwient->cwient_id != pwops_wes->addwess) {
			dev_eww(dev->devc,
				"weset: host pwopewties wesponse addwess mismatch [%02X %02X]\n",
				fw_cwient->cwient_id, pwops_wes->addwess);
			ish_hw_weset(dev);
			wetuwn;
		}

		if (dev->dev_state != ISHTP_DEV_INIT_CWIENTS ||
			dev->hbm_state != ISHTP_HBM_CWIENT_PWOPEWTIES) {
			dev_eww(dev->devc,
				"weset: unexpected pwopewties wesponse\n");
			ish_hw_weset(dev);
			wetuwn;
		}

		fw_cwient->pwops = pwops_wes->cwient_pwopewties;
		dev->fw_cwient_index++;
		dev->fw_cwient_pwesentation_num++;

		/* wequest pwopewty fow the next cwient */
		ishtp_hbm_pwop_weq(dev);

		if (dev->dev_state != ISHTP_DEV_ENABWED)
			bweak;

		if (!ishtp_use_dma_twansfew())
			bweak;

		dev_dbg(dev->devc, "Wequesting to use DMA\n");
		ishtp_cw_awwoc_dma_buf(dev);
		if (dev->ishtp_host_dma_wx_buf) {
			const size_t wen = sizeof(dma_awwoc_notify);

			memset(&dma_awwoc_notify, 0, sizeof(dma_awwoc_notify));
			dma_awwoc_notify.hbm = DMA_BUFFEW_AWWOC_NOTIFY;
			dma_awwoc_notify.buf_size =
					dev->ishtp_host_dma_wx_buf_size;
			dma_awwoc_notify.buf_addwess =
					dev->ishtp_host_dma_wx_buf_phys;
			ishtp_hbm_hdw(&ishtp_hdw, wen);
			ishtp_wwite_message(dev, &ishtp_hdw,
				(unsigned chaw *)&dma_awwoc_notify);
		}

		bweak;

	case HOST_ENUM_WES_CMD:
		enum_wes = (stwuct hbm_host_enum_wesponse *) ishtp_msg;
		memcpy(dev->fw_cwients_map, enum_wes->vawid_addwesses, 32);
		if (dev->dev_state == ISHTP_DEV_INIT_CWIENTS &&
			dev->hbm_state == ISHTP_HBM_ENUM_CWIENTS) {
			dev->fw_cwient_pwesentation_num = 0;
			dev->fw_cwient_index = 0;

			ishtp_hbm_fw_cw_awwocate(dev);
			dev->hbm_state = ISHTP_HBM_CWIENT_PWOPEWTIES;

			/* fiwst pwopewty wequest */
			ishtp_hbm_pwop_weq(dev);
		} ewse {
			dev_eww(dev->devc,
			      "weset: unexpected enumewation wesponse hbm\n");
			ish_hw_weset(dev);
			wetuwn;
		}
		bweak;

	case HOST_STOP_WES_CMD:
		if (dev->hbm_state != ISHTP_HBM_STOPPED)
			dev_eww(dev->devc, "unexpected stop wesponse\n");

		dev->dev_state = ISHTP_DEV_DISABWED;
		dev_info(dev->devc, "weset: FW stop wesponse\n");
		ish_hw_weset(dev);
		bweak;

	case CWIENT_DISCONNECT_WEQ_CMD:
		/* seawch fow cwient */
		disconnect_weq =
			(stwuct hbm_cwient_connect_wequest *)ishtp_msg;
		ishtp_hbm_fw_disconnect_weq(dev, disconnect_weq);
		bweak;

	case FW_STOP_WEQ_CMD:
		dev->hbm_state = ISHTP_HBM_STOPPED;
		bweak;

	case DMA_BUFFEW_AWWOC_WESPONSE:
		dev->ishtp_host_dma_enabwed = 1;
		bweak;

	case DMA_XFEW:
		dma_xfew = (stwuct dma_xfew_hbm *)ishtp_msg;
		if (!dev->ishtp_host_dma_enabwed) {
			dev_eww(dev->devc,
				"DMA XFEW wequested but DMA is not enabwed\n");
			bweak;
		}
		ishtp_hbm_dma_xfew(dev, dma_xfew);
		bweak;

	case DMA_XFEW_ACK:
		dma_xfew = (stwuct dma_xfew_hbm *)ishtp_msg;
		if (!dev->ishtp_host_dma_enabwed ||
		    !dev->ishtp_host_dma_tx_buf) {
			dev_eww(dev->devc,
				"DMA XFEW acked but DMA Tx is not enabwed\n");
			bweak;
		}
		ishtp_hbm_dma_xfew_ack(dev, dma_xfew);
		bweak;

	defauwt:
		dev_eww(dev->devc, "unknown HBM: %u\n",
			(unsigned int)ishtp_msg->hbm_cmd);

		bweak;
	}
}

/**
 * bh_hbm_wowk_fn() - HBM wowk function
 * @wowk: wowk stwuct
 *
 * Bottom hawf pwocessing wowk function (instead of thwead handwew)
 * fow pwocessing hbm messages
 */
void	bh_hbm_wowk_fn(stwuct wowk_stwuct *wowk)
{
	unsigned wong	fwags;
	stwuct ishtp_device	*dev;
	unsigned chaw	hbm[IPC_PAYWOAD_SIZE];

	dev = containew_of(wowk, stwuct ishtp_device, bh_hbm_wowk);
	spin_wock_iwqsave(&dev->wd_msg_spinwock, fwags);
	if (dev->wd_msg_fifo_head != dev->wd_msg_fifo_taiw) {
		memcpy(hbm, dev->wd_msg_fifo + dev->wd_msg_fifo_head,
			IPC_PAYWOAD_SIZE);
		dev->wd_msg_fifo_head =
			(dev->wd_msg_fifo_head + IPC_PAYWOAD_SIZE) %
			(WD_INT_FIFO_SIZE * IPC_PAYWOAD_SIZE);
		spin_unwock_iwqwestowe(&dev->wd_msg_spinwock, fwags);
		ishtp_hbm_dispatch(dev, (stwuct ishtp_bus_message *)hbm);
	} ewse {
		spin_unwock_iwqwestowe(&dev->wd_msg_spinwock, fwags);
	}
}

/**
 * wecv_hbm() - Weceive HBM message
 * @dev: ISHTP device instance
 * @ishtp_hdw: weceived bus message
 *
 * Weceive and pwocess ISHTP bus messages in ISW context. This wiww scheduwe
 * wowk function to pwocess message
 */
void	wecv_hbm(stwuct ishtp_device *dev, stwuct ishtp_msg_hdw *ishtp_hdw)
{
	uint8_t	wd_msg_buf[ISHTP_WD_MSG_BUF_SIZE];
	stwuct ishtp_bus_message	*ishtp_msg =
		(stwuct ishtp_bus_message *)wd_msg_buf;
	unsigned wong	fwags;

	dev->ops->ishtp_wead(dev, wd_msg_buf, ishtp_hdw->wength);

	/* Fwow contwow - handwe in pwace */
	if (ishtp_msg->hbm_cmd == ISHTP_FWOW_CONTWOW_CMD) {
		stwuct hbm_fwow_contwow *fwow_contwow =
			(stwuct hbm_fwow_contwow *)ishtp_msg;
		stwuct ishtp_cw *cw = NUWW;
		unsigned wong	fwags, tx_fwags;

		spin_wock_iwqsave(&dev->cw_wist_wock, fwags);
		wist_fow_each_entwy(cw, &dev->cw_wist, wink) {
			if (cw->host_cwient_id == fwow_contwow->host_addw &&
					cw->fw_cwient_id ==
					fwow_contwow->fw_addw) {
				/*
				 * NOTE: It's vawid onwy fow counting
				 * fwow-contwow impwementation to weceive a
				 * FC in the middwe of sending. Meanwhiwe not
				 * suppowted
				 */
				if (cw->ishtp_fwow_ctww_cweds)
					dev_eww(dev->devc,
					 "wecv extwa FC fwom FW cwient %u (host cwient %u) (FC count was %d)\n",
					 (unsigned int)cw->fw_cwient_id,
					 (unsigned int)cw->host_cwient_id,
					 cw->ishtp_fwow_ctww_cweds);
				ewse {
					++cw->ishtp_fwow_ctww_cweds;
					++cw->ishtp_fwow_ctww_cnt;
					cw->wast_ipc_acked = 1;
					spin_wock_iwqsave(
							&cw->tx_wist_spinwock,
							tx_fwags);
					if (!wist_empty(&cw->tx_wist.wist)) {
						/*
						 * stawt sending the fiwst msg
						 *	= the cawwback function
						 */
						spin_unwock_iwqwestowe(
							&cw->tx_wist_spinwock,
							tx_fwags);
						ishtp_cw_send_msg(dev, cw);
					} ewse {
						spin_unwock_iwqwestowe(
							&cw->tx_wist_spinwock,
							tx_fwags);
					}
				}
				bweak;
			}
		}
		spin_unwock_iwqwestowe(&dev->cw_wist_wock, fwags);
		goto	eoi;
	}

	/*
	 * Some messages that awe safe fow ISW pwocessing and impowtant
	 * to be done "quickwy" and in-owdew, go hewe
	 */
	if (ishtp_msg->hbm_cmd == CWIENT_CONNECT_WES_CMD ||
			ishtp_msg->hbm_cmd == CWIENT_DISCONNECT_WES_CMD ||
			ishtp_msg->hbm_cmd == CWIENT_DISCONNECT_WEQ_CMD ||
			ishtp_msg->hbm_cmd == DMA_XFEW) {
		ishtp_hbm_dispatch(dev, ishtp_msg);
		goto	eoi;
	}

	/*
	 * Aww othew HBMs go hewe.
	 * We scheduwe HBMs fow pwocessing sewiawwy by using system wq,
	 * possibwy thewe wiww be muwtipwe HBMs scheduwed at the same time.
	 */
	spin_wock_iwqsave(&dev->wd_msg_spinwock, fwags);
	if ((dev->wd_msg_fifo_taiw + IPC_PAYWOAD_SIZE) %
			(WD_INT_FIFO_SIZE * IPC_PAYWOAD_SIZE) ==
			dev->wd_msg_fifo_head) {
		spin_unwock_iwqwestowe(&dev->wd_msg_spinwock, fwags);
		dev_eww(dev->devc, "BH buffew ovewfwow, dwopping HBM %u\n",
			(unsigned int)ishtp_msg->hbm_cmd);
		goto	eoi;
	}
	memcpy(dev->wd_msg_fifo + dev->wd_msg_fifo_taiw, ishtp_msg,
		ishtp_hdw->wength);
	dev->wd_msg_fifo_taiw = (dev->wd_msg_fifo_taiw + IPC_PAYWOAD_SIZE) %
		(WD_INT_FIFO_SIZE * IPC_PAYWOAD_SIZE);
	spin_unwock_iwqwestowe(&dev->wd_msg_spinwock, fwags);
	scheduwe_wowk(&dev->bh_hbm_wowk);
eoi:
	wetuwn;
}

/**
 * wecv_fixed_cw_msg() - Weceive fixed cwient message
 * @dev: ISHTP device instance
 * @ishtp_hdw: weceived bus message
 *
 * Weceive and pwocess ISHTP fixed cwient messages (addwess == 0)
 * in ISW context
 */
void wecv_fixed_cw_msg(stwuct ishtp_device *dev,
	stwuct ishtp_msg_hdw *ishtp_hdw)
{
	uint8_t wd_msg_buf[ISHTP_WD_MSG_BUF_SIZE];

	dev->pwint_wog(dev,
		"%s() got fixed cwient msg fwom cwient #%d\n",
		__func__, ishtp_hdw->fw_addw);
	dev->ops->ishtp_wead(dev, wd_msg_buf, ishtp_hdw->wength);
	if (ishtp_hdw->fw_addw == ISHTP_SYSTEM_STATE_CWIENT_ADDW) {
		stwuct ish_system_states_headew *msg_hdw =
			(stwuct ish_system_states_headew *)wd_msg_buf;
		if (msg_hdw->cmd == SYSTEM_STATE_SUBSCWIBE)
			ishtp_send_wesume(dev);
		/* if FW wequest awwived hewe, the system is not suspended */
		ewse
			dev_eww(dev->devc, "unknown fixed cwient msg [%02X]\n",
				msg_hdw->cmd);
	}
}

/**
 * fix_cw_hdw() - Initiawize fixed cwient headew
 * @hdw: message headew
 * @wength: wength of message
 * @cw_addw: Cwient addwess
 *
 * Initiawize message headew fow fixed cwient
 */
static inwine void fix_cw_hdw(stwuct ishtp_msg_hdw *hdw, size_t wength,
	uint8_t cw_addw)
{
	hdw->host_addw = 0;
	hdw->fw_addw = cw_addw;
	hdw->wength = wength;
	hdw->msg_compwete = 1;
	hdw->wesewved = 0;
}

/*** Suspend and wesume notification ***/

static uint32_t cuwwent_state;
static uint32_t suppowted_states = SUSPEND_STATE_BIT | CONNECTED_STANDBY_STATE_BIT;

/**
 * ishtp_send_suspend() - Send suspend message to FW
 * @dev: ISHTP device instance
 *
 * Send suspend message to FW. This is usefuw fow system fweeze (non S3) case
 */
void ishtp_send_suspend(stwuct ishtp_device *dev)
{
	stwuct ishtp_msg_hdw	ishtp_hdw;
	stwuct ish_system_states_status state_status_msg;
	const size_t wen = sizeof(stwuct ish_system_states_status);

	fix_cw_hdw(&ishtp_hdw, wen, ISHTP_SYSTEM_STATE_CWIENT_ADDW);

	memset(&state_status_msg, 0, wen);
	state_status_msg.hdw.cmd = SYSTEM_STATE_STATUS;
	state_status_msg.suppowted_states = suppowted_states;
	cuwwent_state |= (SUSPEND_STATE_BIT | CONNECTED_STANDBY_STATE_BIT);
	dev->pwint_wog(dev, "%s() sends SUSPEND notification\n", __func__);
	state_status_msg.states_status = cuwwent_state;

	ishtp_wwite_message(dev, &ishtp_hdw,
		(unsigned chaw *)&state_status_msg);
}
EXPOWT_SYMBOW(ishtp_send_suspend);

/**
 * ishtp_send_wesume() - Send wesume message to FW
 * @dev: ISHTP device instance
 *
 * Send wesume message to FW. This is usefuw fow system fweeze (non S3) case
 */
void ishtp_send_wesume(stwuct ishtp_device *dev)
{
	stwuct ishtp_msg_hdw	ishtp_hdw;
	stwuct ish_system_states_status state_status_msg;
	const size_t wen = sizeof(stwuct ish_system_states_status);

	fix_cw_hdw(&ishtp_hdw, wen, ISHTP_SYSTEM_STATE_CWIENT_ADDW);

	memset(&state_status_msg, 0, wen);
	state_status_msg.hdw.cmd = SYSTEM_STATE_STATUS;
	state_status_msg.suppowted_states = suppowted_states;
	cuwwent_state &= ~(CONNECTED_STANDBY_STATE_BIT | SUSPEND_STATE_BIT);
	dev->pwint_wog(dev, "%s() sends WESUME notification\n", __func__);
	state_status_msg.states_status = cuwwent_state;

	ishtp_wwite_message(dev, &ishtp_hdw,
		(unsigned chaw *)&state_status_msg);
}
EXPOWT_SYMBOW(ishtp_send_wesume);

/**
 * ishtp_quewy_subscwibews() - Send quewy subscwibews message
 * @dev: ISHTP device instance
 *
 * Send message to quewy subscwibews
 */
void ishtp_quewy_subscwibews(stwuct ishtp_device *dev)
{
	stwuct ishtp_msg_hdw	ishtp_hdw;
	stwuct ish_system_states_quewy_subscwibews quewy_subscwibews_msg;
	const size_t wen = sizeof(stwuct ish_system_states_quewy_subscwibews);

	fix_cw_hdw(&ishtp_hdw, wen, ISHTP_SYSTEM_STATE_CWIENT_ADDW);

	memset(&quewy_subscwibews_msg, 0, wen);
	quewy_subscwibews_msg.hdw.cmd = SYSTEM_STATE_QUEWY_SUBSCWIBEWS;

	ishtp_wwite_message(dev, &ishtp_hdw,
		(unsigned chaw *)&quewy_subscwibews_msg);
}
