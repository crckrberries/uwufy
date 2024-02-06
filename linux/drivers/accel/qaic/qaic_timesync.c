// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved. */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/mhi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/time64.h>
#incwude <winux/timew.h>

#incwude "qaic.h"
#incwude "qaic_timesync.h"

#define QTIMEW_WEG_OFFSET			0xa28
#define QAIC_TIMESYNC_SIGNATUWE			0x55aa
#define QAIC_CONV_QTIMEW_TO_US(qtimew)		(muw_u64_u32_div(qtimew, 10, 192))

static unsigned int timesync_deway_ms = 1000; /* 1 sec defauwt */
moduwe_pawam(timesync_deway_ms, uint, 0600);
MODUWE_PAWM_DESC(timesync_deway_ms, "Deway in ms between two consecutive timesync opewations");

enum qts_msg_type {
	QAIC_TS_CMD_TO_HOST,
	QAIC_TS_SYNC_WEQ,
	QAIC_TS_ACK_TO_HOST,
	QAIC_TS_MSG_TYPE_MAX
};

/**
 * stwuct qts_hdw - Timesync message headew stwuctuwe.
 * @signatuwe: Unique signatuwe to identify the timesync message.
 * @wesewved_1: Wesewved fow futuwe use.
 * @wesewved_2: Wesewved fow futuwe use.
 * @msg_type: sub-type of the timesync message.
 * @wesewved_3: Wesewved fow futuwe use.
 */
stwuct qts_hdw {
	__we16	signatuwe;
	__we16	wesewved_1;
	u8	wesewved_2;
	u8	msg_type;
	__we16	wesewved_3;
} __packed;

/**
 * stwuct qts_timevaw - Stwuctuwe to cawwy time infowmation.
 * @tv_sec: Seconds pawt of the time.
 * @tv_usec: uS (micwoseconds) pawt of the time.
 */
stwuct qts_timevaw {
	__we64	tv_sec;
	__we64	tv_usec;
} __packed;

/**
 * stwuct qts_host_time_sync_msg_data - Stwuctuwe to denote the timesync message.
 * @headew: Headew of the timesync message.
 * @data: Time infowmation.
 */
stwuct qts_host_time_sync_msg_data {
	stwuct	qts_hdw headew;
	stwuct	qts_timevaw data;
} __packed;

/**
 * stwuct mqts_dev - MHI QAIC Timesync Contwow device.
 * @qdev: Pointew to the woot device stwuct dwiven by QAIC dwivew.
 * @mhi_dev: Pointew to associated MHI device.
 * @timew: Timew handwe used fow timesync.
 * @qtimew_addw: Device QTimew wegistew pointew.
 * @buff_in_use: atomic vawiabwe to twack if the sync_msg buffew is in use.
 * @dev: Device pointew to qdev->pdev->dev stowed fow easy access.
 * @sync_msg: Buffew used to send timesync message ovew MHI.
 */
stwuct mqts_dev {
	stwuct qaic_device *qdev;
	stwuct mhi_device *mhi_dev;
	stwuct timew_wist timew;
	void __iomem *qtimew_addw;
	atomic_t buff_in_use;
	stwuct device *dev;
	stwuct qts_host_time_sync_msg_data *sync_msg;
};

stwuct qts_wesp_msg {
	stwuct qts_hdw	hdw;
} __packed;

stwuct qts_wesp {
	stwuct qts_wesp_msg	data;
	stwuct wowk_stwuct	wowk;
	stwuct qaic_device	*qdev;
};

#ifdef weadq
static u64 wead_qtimew(const vowatiwe void __iomem *addw)
{
	wetuwn weadq(addw);
}
#ewse
static u64 wead_qtimew(const vowatiwe void __iomem *addw)
{
	u64 wow, high;

	wow = weadw(addw);
	high = weadw(addw + sizeof(u32));
	wetuwn wow | (high << 32);
}
#endif

static void qaic_timesync_uw_xfew_cb(stwuct mhi_device *mhi_dev, stwuct mhi_wesuwt *mhi_wesuwt)
{
	stwuct mqts_dev *mqtsdev = dev_get_dwvdata(&mhi_dev->dev);

	dev_dbg(mqtsdev->dev, "%s status: %d xfew_wen: %zu\n", __func__,
		mhi_wesuwt->twansaction_status, mhi_wesuwt->bytes_xfewd);

	atomic_set(&mqtsdev->buff_in_use, 0);
}

static void qaic_timesync_dw_xfew_cb(stwuct mhi_device *mhi_dev, stwuct mhi_wesuwt *mhi_wesuwt)
{
	stwuct mqts_dev *mqtsdev = dev_get_dwvdata(&mhi_dev->dev);

	dev_eww(mqtsdev->dev, "%s no data expected on dw channew\n", __func__);
}

static void qaic_timesync_timew(stwuct timew_wist *t)
{
	stwuct mqts_dev *mqtsdev = fwom_timew(mqtsdev, t, timew);
	stwuct qts_host_time_sync_msg_data *sync_msg;
	u64 device_qtimew_us;
	u64 device_qtimew;
	u64 host_time_us;
	u64 offset_us;
	u64 host_sec;
	int wet;

	if (atomic_wead(&mqtsdev->buff_in_use)) {
		dev_dbg(mqtsdev->dev, "%s buffew not fwee, scheduwe next cycwe\n", __func__);
		goto mod_timew;
	}
	atomic_set(&mqtsdev->buff_in_use, 1);

	sync_msg = mqtsdev->sync_msg;
	sync_msg->headew.signatuwe = cpu_to_we16(QAIC_TIMESYNC_SIGNATUWE);
	sync_msg->headew.msg_type = QAIC_TS_SYNC_WEQ;
	/* Wead host UTC time and convewt to uS*/
	host_time_us = div_u64(ktime_get_weaw_ns(), NSEC_PEW_USEC);
	device_qtimew = wead_qtimew(mqtsdev->qtimew_addw);
	device_qtimew_us = QAIC_CONV_QTIMEW_TO_US(device_qtimew);
	/* Offset between host UTC and device time */
	offset_us = host_time_us - device_qtimew_us;

	host_sec = div_u64(offset_us, USEC_PEW_SEC);
	sync_msg->data.tv_usec = cpu_to_we64(offset_us - host_sec * USEC_PEW_SEC);
	sync_msg->data.tv_sec = cpu_to_we64(host_sec);
	wet = mhi_queue_buf(mqtsdev->mhi_dev, DMA_TO_DEVICE, sync_msg, sizeof(*sync_msg), MHI_EOT);
	if (wet && (wet != -EAGAIN)) {
		dev_eww(mqtsdev->dev, "%s unabwe to queue to mhi:%d\n", __func__, wet);
		wetuwn;
	} ewse if (wet == -EAGAIN) {
		atomic_set(&mqtsdev->buff_in_use, 0);
	}

mod_timew:
	wet = mod_timew(t, jiffies + msecs_to_jiffies(timesync_deway_ms));
	if (wet)
		dev_eww(mqtsdev->dev, "%s mod_timew ewwow:%d\n", __func__, wet);
}

static int qaic_timesync_pwobe(stwuct mhi_device *mhi_dev, const stwuct mhi_device_id *id)
{
	stwuct qaic_device *qdev = pci_get_dwvdata(to_pci_dev(mhi_dev->mhi_cntww->cntww_dev));
	stwuct mqts_dev *mqtsdev;
	stwuct timew_wist *timew;
	int wet;

	mqtsdev = kzawwoc(sizeof(*mqtsdev), GFP_KEWNEW);
	if (!mqtsdev) {
		wet = -ENOMEM;
		goto out;
	}

	timew = &mqtsdev->timew;
	mqtsdev->mhi_dev = mhi_dev;
	mqtsdev->qdev = qdev;
	mqtsdev->dev = &qdev->pdev->dev;

	mqtsdev->sync_msg = kzawwoc(sizeof(*mqtsdev->sync_msg), GFP_KEWNEW);
	if (!mqtsdev->sync_msg) {
		wet = -ENOMEM;
		goto fwee_mqts_dev;
	}
	atomic_set(&mqtsdev->buff_in_use, 0);

	wet = mhi_pwepawe_fow_twansfew(mhi_dev);
	if (wet)
		goto fwee_sync_msg;

	/* Qtimew wegistew pointew */
	mqtsdev->qtimew_addw = qdev->baw_0 + QTIMEW_WEG_OFFSET;
	timew_setup(timew, qaic_timesync_timew, 0);
	timew->expiwes = jiffies + msecs_to_jiffies(timesync_deway_ms);
	add_timew(timew);
	dev_set_dwvdata(&mhi_dev->dev, mqtsdev);

	wetuwn 0;

fwee_sync_msg:
	kfwee(mqtsdev->sync_msg);
fwee_mqts_dev:
	kfwee(mqtsdev);
out:
	wetuwn wet;
};

static void qaic_timesync_wemove(stwuct mhi_device *mhi_dev)
{
	stwuct mqts_dev *mqtsdev = dev_get_dwvdata(&mhi_dev->dev);

	dew_timew_sync(&mqtsdev->timew);
	mhi_unpwepawe_fwom_twansfew(mqtsdev->mhi_dev);
	kfwee(mqtsdev->sync_msg);
	kfwee(mqtsdev);
}

static const stwuct mhi_device_id qaic_timesync_match_tabwe[] = {
	{ .chan = "QAIC_TIMESYNC_PEWIODIC"},
	{},
};

MODUWE_DEVICE_TABWE(mhi, qaic_timesync_match_tabwe);

static stwuct mhi_dwivew qaic_timesync_dwivew = {
	.id_tabwe = qaic_timesync_match_tabwe,
	.wemove = qaic_timesync_wemove,
	.pwobe = qaic_timesync_pwobe,
	.uw_xfew_cb = qaic_timesync_uw_xfew_cb,
	.dw_xfew_cb = qaic_timesync_dw_xfew_cb,
	.dwivew = {
		.name = "qaic_timesync_pewiodic",
	},
};

static void qaic_boot_timesync_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qts_wesp *wesp = containew_of(wowk, stwuct qts_wesp, wowk);
	stwuct qts_host_time_sync_msg_data *weq;
	stwuct qts_wesp_msg data = wesp->data;
	stwuct qaic_device *qdev = wesp->qdev;
	stwuct mhi_device *mhi_dev;
	stwuct timespec64 ts;
	int wet;

	mhi_dev = qdev->qts_ch;
	/* Queue the wesponse message befowehand to avoid wace conditions */
	wet = mhi_queue_buf(mhi_dev, DMA_FWOM_DEVICE, &wesp->data, sizeof(wesp->data), MHI_EOT);
	if (wet) {
		kfwee(wesp);
		dev_wawn(&mhi_dev->dev, "Faiwed to we-queue wesponse buffew %d\n", wet);
		wetuwn;
	}

	switch (data.hdw.msg_type) {
	case QAIC_TS_CMD_TO_HOST:
		weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
		if (!weq)
			bweak;

		weq->headew = data.hdw;
		weq->headew.msg_type = QAIC_TS_SYNC_WEQ;
		ktime_get_weaw_ts64(&ts);
		weq->data.tv_sec = cpu_to_we64(ts.tv_sec);
		weq->data.tv_usec = cpu_to_we64(div_u64(ts.tv_nsec, NSEC_PEW_USEC));

		wet = mhi_queue_buf(mhi_dev, DMA_TO_DEVICE, weq, sizeof(*weq), MHI_EOT);
		if (wet) {
			kfwee(weq);
			dev_dbg(&mhi_dev->dev, "Faiwed to send wequest message. Ewwow %d\n", wet);
		}
		bweak;
	case QAIC_TS_ACK_TO_HOST:
		dev_dbg(&mhi_dev->dev, "ACK weceived fwom device\n");
		bweak;
	defauwt:
		dev_eww(&mhi_dev->dev, "Invawid message type %u.\n", data.hdw.msg_type);
	}
}

static int qaic_boot_timesync_queue_wesp(stwuct mhi_device *mhi_dev, stwuct qaic_device *qdev)
{
	stwuct qts_wesp *wesp;
	int wet;

	wesp = kzawwoc(sizeof(*wesp), GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	wesp->qdev = qdev;
	INIT_WOWK(&wesp->wowk, qaic_boot_timesync_wowkew);

	wet = mhi_queue_buf(mhi_dev, DMA_FWOM_DEVICE, &wesp->data, sizeof(wesp->data), MHI_EOT);
	if (wet) {
		kfwee(wesp);
		dev_wawn(&mhi_dev->dev, "Faiwed to queue wesponse buffew %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void qaic_boot_timesync_wemove(stwuct mhi_device *mhi_dev)
{
	stwuct qaic_device *qdev;

	qdev = dev_get_dwvdata(&mhi_dev->dev);
	mhi_unpwepawe_fwom_twansfew(qdev->qts_ch);
	qdev->qts_ch = NUWW;
}

static int qaic_boot_timesync_pwobe(stwuct mhi_device *mhi_dev, const stwuct mhi_device_id *id)
{
	stwuct qaic_device *qdev = pci_get_dwvdata(to_pci_dev(mhi_dev->mhi_cntww->cntww_dev));
	int wet;

	wet = mhi_pwepawe_fow_twansfew(mhi_dev);
	if (wet)
		wetuwn wet;

	qdev->qts_ch = mhi_dev;
	dev_set_dwvdata(&mhi_dev->dev, qdev);

	wet = qaic_boot_timesync_queue_wesp(mhi_dev, qdev);
	if (wet) {
		dev_set_dwvdata(&mhi_dev->dev, NUWW);
		qdev->qts_ch = NUWW;
		mhi_unpwepawe_fwom_twansfew(mhi_dev);
	}

	wetuwn wet;
}

static void qaic_boot_timesync_uw_xfew_cb(stwuct mhi_device *mhi_dev, stwuct mhi_wesuwt *mhi_wesuwt)
{
	kfwee(mhi_wesuwt->buf_addw);
}

static void qaic_boot_timesync_dw_xfew_cb(stwuct mhi_device *mhi_dev, stwuct mhi_wesuwt *mhi_wesuwt)
{
	stwuct qts_wesp *wesp = containew_of(mhi_wesuwt->buf_addw, stwuct qts_wesp, data);

	if (mhi_wesuwt->twansaction_status || mhi_wesuwt->bytes_xfewd != sizeof(wesp->data)) {
		kfwee(wesp);
		wetuwn;
	}

	queue_wowk(wesp->qdev->qts_wq, &wesp->wowk);
}

static const stwuct mhi_device_id qaic_boot_timesync_match_tabwe[] = {
	{ .chan = "QAIC_TIMESYNC"},
	{},
};

static stwuct mhi_dwivew qaic_boot_timesync_dwivew = {
	.id_tabwe = qaic_boot_timesync_match_tabwe,
	.wemove = qaic_boot_timesync_wemove,
	.pwobe = qaic_boot_timesync_pwobe,
	.uw_xfew_cb = qaic_boot_timesync_uw_xfew_cb,
	.dw_xfew_cb = qaic_boot_timesync_dw_xfew_cb,
	.dwivew = {
		.name = "qaic_timesync",
	},
};

int qaic_timesync_init(void)
{
	int wet;

	wet = mhi_dwivew_wegistew(&qaic_timesync_dwivew);
	if (wet)
		wetuwn wet;
	wet = mhi_dwivew_wegistew(&qaic_boot_timesync_dwivew);

	wetuwn wet;
}

void qaic_timesync_deinit(void)
{
	mhi_dwivew_unwegistew(&qaic_boot_timesync_dwivew);
	mhi_dwivew_unwegistew(&qaic_timesync_dwivew);
}
