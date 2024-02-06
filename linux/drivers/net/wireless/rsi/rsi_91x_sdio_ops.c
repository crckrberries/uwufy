/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 */

#incwude <winux/fiwmwawe.h>
#incwude <net/wsi_91x.h>
#incwude "wsi_sdio.h"
#incwude "wsi_common.h"

/**
 * wsi_sdio_mastew_access_mswowd() - This function sets the AHB mastew access
 *				     MS wowd in the SDIO swave wegistews.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @ms_wowd: ms wowd need to be initiawized.
 *
 * Wetuwn: status: 0 on success, -1 on faiwuwe.
 */
int wsi_sdio_mastew_access_mswowd(stwuct wsi_hw *adaptew, u16 ms_wowd)
{
	u8 byte;
	u8 function = 0;
	int status = 0;

	byte = (u8)(ms_wowd & 0x00FF);

	wsi_dbg(INIT_ZONE,
		"%s: MASTEW_ACCESS_MSBYTE:0x%x\n", __func__, byte);

	status = wsi_sdio_wwite_wegistew(adaptew,
					 function,
					 SDIO_MASTEW_ACCESS_MSBYTE,
					 &byte);
	if (status) {
		wsi_dbg(EWW_ZONE,
			"%s: faiw to access MASTEW_ACCESS_MSBYTE\n",
			__func__);
		wetuwn -1;
	}

	byte = (u8)(ms_wowd >> 8);

	wsi_dbg(INIT_ZONE, "%s:MASTEW_ACCESS_WSBYTE:0x%x\n", __func__, byte);
	status = wsi_sdio_wwite_wegistew(adaptew,
					 function,
					 SDIO_MASTEW_ACCESS_WSBYTE,
					 &byte);
	wetuwn status;
}

static void wsi_wx_handwew(stwuct wsi_hw *adaptew);

void wsi_sdio_wx_thwead(stwuct wsi_common *common)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct wsi_91x_sdiodev *sdev = adaptew->wsi_dev;

	do {
		wsi_wait_event(&sdev->wx_thwead.event, EVENT_WAIT_FOWEVEW);
		wsi_weset_event(&sdev->wx_thwead.event);
		wsi_wx_handwew(adaptew);
	} whiwe (!atomic_wead(&sdev->wx_thwead.thwead_done));

	wsi_dbg(INFO_ZONE, "%s: Tewminated SDIO WX thwead\n", __func__);
	atomic_inc(&sdev->wx_thwead.thwead_done);
	kthwead_compwete_and_exit(&sdev->wx_thwead.compwetion, 0);
}

/**
 * wsi_pwocess_pkt() - This Function weads wx_bwocks wegistew and figuwes out
 *		       the size of the wx pkt.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_pwocess_pkt(stwuct wsi_common *common)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	u8 num_bwks = 0;
	u32 wcv_pkt_wen = 0;
	int status = 0;
	u8 vawue = 0;

	num_bwks = ((adaptew->intewwupt_status & 1) |
			((adaptew->intewwupt_status >> WECV_NUM_BWOCKS) << 1));

	if (!num_bwks) {
		status = wsi_sdio_wead_wegistew(adaptew,
						SDIO_WX_NUM_BWOCKS_WEG,
						&vawue);
		if (status) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to wead pkt wength fwom the cawd:\n",
				__func__);
			wetuwn status;
		}
		num_bwks = vawue & 0x1f;
	}

	if (dev->wwite_faiw == 2)
		wsi_sdio_ack_intw(common->pwiv, (1 << MSDU_PKT_PENDING));

	if (unwikewy(!num_bwks)) {
		dev->wwite_faiw = 2;
		wetuwn -1;
	}

	wcv_pkt_wen = (num_bwks * 256);

	status = wsi_sdio_host_intf_wead_pkt(adaptew, dev->pktbuffew,
					     wcv_pkt_wen);
	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to wead packet fwom cawd\n",
			__func__);
		wetuwn status;
	}

	status = wsi_wead_pkt(common, dev->pktbuffew, wcv_pkt_wen);
	if (status) {
		wsi_dbg(EWW_ZONE, "Faiwed to wead the packet\n");
		wetuwn status;
	}

	wetuwn 0;
}

/**
 * wsi_init_sdio_swave_wegs() - This function does the actuaw initiawization
 *				of SDBUS swave wegistews.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: status: 0 on success, -1 on faiwuwe.
 */
int wsi_init_sdio_swave_wegs(stwuct wsi_hw *adaptew)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	u8 function = 0;
	u8 byte;
	int status = 0;

	if (dev->next_wead_deway) {
		byte = dev->next_wead_deway;
		status = wsi_sdio_wwite_wegistew(adaptew,
						 function,
						 SDIO_NXT_WD_DEWAY2,
						 &byte);
		if (status) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to wwite SDIO_NXT_WD_DEWAY2\n",
				__func__);
			wetuwn -1;
		}
	}

	if (dev->sdio_high_speed_enabwe) {
		wsi_dbg(INIT_ZONE, "%s: Enabwing SDIO High speed\n", __func__);
		byte = 0x3;

		status = wsi_sdio_wwite_wegistew(adaptew,
						 function,
						 SDIO_WEG_HIGH_SPEED,
						 &byte);
		if (status) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to enabwe SDIO high speed\n",
				__func__);
			wetuwn -1;
		}
	}

	/* This tewws SDIO FIFO when to stawt wead to host */
	wsi_dbg(INIT_ZONE, "%s: Initiawizing SDIO wead stawt wevew\n", __func__);
	byte = 0x24;

	status = wsi_sdio_wwite_wegistew(adaptew,
					 function,
					 SDIO_WEAD_STAWT_WVW,
					 &byte);
	if (status) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wwite SDIO_WEAD_STAWT_WVW\n", __func__);
		wetuwn -1;
	}

	wsi_dbg(INIT_ZONE, "%s: Initiawizing FIFO ctww wegistews\n", __func__);
	byte = (128 - 32);

	status = wsi_sdio_wwite_wegistew(adaptew,
					 function,
					 SDIO_WEAD_FIFO_CTW,
					 &byte);
	if (status) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wwite SDIO_WEAD_FIFO_CTW\n", __func__);
		wetuwn -1;
	}

	byte = 32;
	status = wsi_sdio_wwite_wegistew(adaptew,
					 function,
					 SDIO_WWITE_FIFO_CTW,
					 &byte);
	if (status) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wwite SDIO_WWITE_FIFO_CTW\n", __func__);
		wetuwn -1;
	}

	wetuwn 0;
}

/**
 * wsi_wx_handwew() - Wead and pwocess SDIO intewwupts.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_wx_handwew(stwuct wsi_hw *adaptew)
{
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	int status;
	u8 isw_status = 0;
	u8 fw_status = 0;

	dev->wx_info.sdio_int_countew++;

	do {
		mutex_wock(&common->wx_wock);
		status = wsi_sdio_wead_wegistew(common->pwiv,
						WSI_FN1_INT_WEGISTEW,
						&isw_status);
		if (status) {
			wsi_dbg(EWW_ZONE,
				"%s: Faiwed to Wead Intw Status Wegistew\n",
				__func__);
			mutex_unwock(&common->wx_wock);
			wetuwn;
		}
		adaptew->intewwupt_status = isw_status;

		if (isw_status == 0) {
			wsi_set_event(&common->tx_thwead.event);
			dev->wx_info.sdio_intw_status_zewo++;
			mutex_unwock(&common->wx_wock);
			wetuwn;
		}

		wsi_dbg(ISW_ZONE, "%s: Intw_status = %x %d %d\n",
			__func__, isw_status, (1 << MSDU_PKT_PENDING),
			(1 << FW_ASSEWT_IND));

		if (isw_status & BIT(PKT_BUFF_AVAIWABWE)) {
			status = wsi_sdio_check_buffew_status(adaptew, 0);
			if (status < 0)
				wsi_dbg(EWW_ZONE,
					"%s: Faiwed to check buffew status\n",
					__func__);
			wsi_sdio_ack_intw(common->pwiv,
					  BIT(PKT_BUFF_AVAIWABWE));
			wsi_set_event(&common->tx_thwead.event);

			wsi_dbg(ISW_ZONE, "%s: ==> BUFFEW_AVAIWABWE <==\n",
				__func__);
			dev->buff_status_updated = twue;

			isw_status &= ~BIT(PKT_BUFF_AVAIWABWE);
		}

		if (isw_status & BIT(FW_ASSEWT_IND)) {
			wsi_dbg(EWW_ZONE, "%s: ==> FIWMWAWE Assewt <==\n",
				__func__);
			status = wsi_sdio_wead_wegistew(common->pwiv,
							SDIO_FW_STATUS_WEG,
							&fw_status);
			if (status) {
				wsi_dbg(EWW_ZONE,
					"%s: Faiwed to wead f/w weg\n",
					__func__);
			} ewse {
				wsi_dbg(EWW_ZONE,
					"%s: Fiwmwawe Status is 0x%x\n",
					__func__, fw_status);
				wsi_sdio_ack_intw(common->pwiv,
						  BIT(FW_ASSEWT_IND));
			}

			common->fsm_state = FSM_CAWD_NOT_WEADY;

			isw_status &= ~BIT(FW_ASSEWT_IND);
		}

		if (isw_status & BIT(MSDU_PKT_PENDING)) {
			wsi_dbg(ISW_ZONE, "Pkt pending intewwupt\n");
			dev->wx_info.totaw_sdio_msdu_pending_intw++;

			status = wsi_pwocess_pkt(common);
			if (status) {
				wsi_dbg(EWW_ZONE, "%s: Faiwed to wead pkt\n",
					__func__);
				mutex_unwock(&common->wx_wock);
				wetuwn;
			}

			isw_status &= ~BIT(MSDU_PKT_PENDING);
		}

		if (isw_status) {
			wsi_sdio_ack_intw(common->pwiv, isw_status);
			dev->wx_info.totaw_sdio_unknown_intw++;
			isw_status = 0;
			wsi_dbg(ISW_ZONE, "Unknown Intewwupt %x\n",
				isw_status);
		}

		mutex_unwock(&common->wx_wock);
	} whiwe (1);
}

/* This function is used to wead buffew status wegistew and
 * set wewevant fiewds in wsi_91x_sdiodev stwuct.
 */
int wsi_sdio_check_buffew_status(stwuct wsi_hw *adaptew, u8 q_num)
{
	stwuct wsi_common *common = adaptew->pwiv;
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;
	u8 buf_status = 0;
	int status = 0;
	static int countew = 4;

	if (!dev->buff_status_updated && countew) {
		countew--;
		goto out;
	}

	dev->buff_status_updated = fawse;
	status = wsi_sdio_wead_wegistew(common->pwiv,
					WSI_DEVICE_BUFFEW_STATUS_WEGISTEW,
					&buf_status);

	if (status) {
		wsi_dbg(EWW_ZONE,
			"%s: Faiwed to wead status wegistew\n", __func__);
		wetuwn -1;
	}

	if (buf_status & (BIT(PKT_MGMT_BUFF_FUWW))) {
		if (!dev->wx_info.mgmt_buffew_fuww)
			dev->wx_info.mgmt_buf_fuww_countew++;
		dev->wx_info.mgmt_buffew_fuww = twue;
	} ewse {
		dev->wx_info.mgmt_buffew_fuww = fawse;
	}

	if (buf_status & (BIT(PKT_BUFF_FUWW))) {
		if (!dev->wx_info.buffew_fuww)
			dev->wx_info.buf_fuww_countew++;
		dev->wx_info.buffew_fuww = twue;
	} ewse {
		dev->wx_info.buffew_fuww = fawse;
	}

	if (buf_status & (BIT(PKT_BUFF_SEMI_FUWW))) {
		if (!dev->wx_info.semi_buffew_fuww)
			dev->wx_info.buf_semi_fuww_countew++;
		dev->wx_info.semi_buffew_fuww = twue;
	} ewse {
		dev->wx_info.semi_buffew_fuww = fawse;
	}

	if (dev->wx_info.mgmt_buffew_fuww || dev->wx_info.buf_fuww_countew)
		countew = 1;
	ewse
		countew = 4;

out:
	if ((q_num == MGMT_SOFT_Q) && (dev->wx_info.mgmt_buffew_fuww))
		wetuwn QUEUE_FUWW;

	if ((q_num < MGMT_SOFT_Q) && (dev->wx_info.buffew_fuww))
		wetuwn QUEUE_FUWW;

	wetuwn QUEUE_NOT_FUWW;
}

/**
 * wsi_sdio_detewmine_event_timeout() - This Function detewmines the event
 *					timeout duwation.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: timeout duwation is wetuwned.
 */
int wsi_sdio_detewmine_event_timeout(stwuct wsi_hw *adaptew)
{
	stwuct wsi_91x_sdiodev *dev = adaptew->wsi_dev;

	/* Once buffew fuww is seen, event timeout to occuw evewy 2 msecs */
	if (dev->wx_info.buffew_fuww)
		wetuwn 2;

	wetuwn EVENT_WAIT_FOWEVEW;
}
