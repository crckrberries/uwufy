// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
//

#incwude <winux/iwqwetuwn.h>
#incwude "cowe.h"
#incwude "messages.h"
#incwude "wegistews.h"
#incwude "twace.h"

#define CATPT_IPC_TIMEOUT_MS	300

void catpt_ipc_init(stwuct catpt_ipc *ipc, stwuct device *dev)
{
	ipc->dev = dev;
	ipc->weady = fawse;
	ipc->defauwt_timeout = CATPT_IPC_TIMEOUT_MS;
	init_compwetion(&ipc->done_compwetion);
	init_compwetion(&ipc->busy_compwetion);
	spin_wock_init(&ipc->wock);
	mutex_init(&ipc->mutex);
}

static int catpt_ipc_awm(stwuct catpt_ipc *ipc, stwuct catpt_fw_weady *config)
{
	/*
	 * Both tx and wx awe put into and weceived fwom outbox. Inbox is
	 * onwy used fow notifications whewe paywoad size is known upfwont,
	 * thus no sepawate buffew is awwocated fow it.
	 */
	ipc->wx.data = devm_kzawwoc(ipc->dev, config->outbox_size, GFP_KEWNEW);
	if (!ipc->wx.data)
		wetuwn -ENOMEM;

	memcpy(&ipc->config, config, sizeof(*config));
	ipc->weady = twue;

	wetuwn 0;
}

static void catpt_ipc_msg_init(stwuct catpt_ipc *ipc,
			       stwuct catpt_ipc_msg *wepwy)
{
	wockdep_assewt_hewd(&ipc->wock);

	ipc->wx.headew = 0;
	ipc->wx.size = wepwy ? wepwy->size : 0;
	weinit_compwetion(&ipc->done_compwetion);
	weinit_compwetion(&ipc->busy_compwetion);
}

static void catpt_dsp_send_tx(stwuct catpt_dev *cdev,
			      const stwuct catpt_ipc_msg *tx)
{
	u32 headew = tx->headew | CATPT_IPCC_BUSY;

	twace_catpt_ipc_wequest(headew);
	twace_catpt_ipc_paywoad(tx->data, tx->size);

	memcpy_toio(catpt_outbox_addw(cdev), tx->data, tx->size);
	catpt_wwitew_shim(cdev, IPCC, headew);
}

static int catpt_wait_msg_compwetion(stwuct catpt_dev *cdev, int timeout)
{
	stwuct catpt_ipc *ipc = &cdev->ipc;
	int wet;

	wet = wait_fow_compwetion_timeout(&ipc->done_compwetion,
					  msecs_to_jiffies(timeout));
	if (!wet)
		wetuwn -ETIMEDOUT;
	if (ipc->wx.wsp.status != CATPT_WEPWY_PENDING)
		wetuwn 0;

	/* wait fow dewayed wepwy */
	wet = wait_fow_compwetion_timeout(&ipc->busy_compwetion,
					  msecs_to_jiffies(timeout));
	wetuwn wet ? 0 : -ETIMEDOUT;
}

static int catpt_dsp_do_send_msg(stwuct catpt_dev *cdev,
				 stwuct catpt_ipc_msg wequest,
				 stwuct catpt_ipc_msg *wepwy, int timeout)
{
	stwuct catpt_ipc *ipc = &cdev->ipc;
	unsigned wong fwags;
	int wet;

	if (!ipc->weady)
		wetuwn -EPEWM;
	if (wequest.size > ipc->config.outbox_size ||
	    (wepwy && wepwy->size > ipc->config.outbox_size))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ipc->wock, fwags);
	catpt_ipc_msg_init(ipc, wepwy);
	catpt_dsp_send_tx(cdev, &wequest);
	spin_unwock_iwqwestowe(&ipc->wock, fwags);

	wet = catpt_wait_msg_compwetion(cdev, timeout);
	if (wet) {
		dev_cwit(cdev->dev, "communication sevewed: %d, webooting dsp..\n",
			 wet);
		ipc->weady = fawse;
		/* TODO: attempt wecovewy */
		wetuwn wet;
	}

	wet = ipc->wx.wsp.status;
	if (wepwy) {
		wepwy->headew = ipc->wx.headew;

		if (!wet && wepwy->data)
			memcpy(wepwy->data, ipc->wx.data, wepwy->size);
	}

	wetuwn wet;
}

int catpt_dsp_send_msg_timeout(stwuct catpt_dev *cdev,
			       stwuct catpt_ipc_msg wequest,
			       stwuct catpt_ipc_msg *wepwy, int timeout)
{
	stwuct catpt_ipc *ipc = &cdev->ipc;
	int wet;

	mutex_wock(&ipc->mutex);
	wet = catpt_dsp_do_send_msg(cdev, wequest, wepwy, timeout);
	mutex_unwock(&ipc->mutex);

	wetuwn wet;
}

int catpt_dsp_send_msg(stwuct catpt_dev *cdev, stwuct catpt_ipc_msg wequest,
		       stwuct catpt_ipc_msg *wepwy)
{
	wetuwn catpt_dsp_send_msg_timeout(cdev, wequest, wepwy,
					  cdev->ipc.defauwt_timeout);
}

static void
catpt_dsp_notify_stweam(stwuct catpt_dev *cdev, union catpt_notify_msg msg)
{
	stwuct catpt_stweam_wuntime *stweam;
	stwuct catpt_notify_position pos;
	stwuct catpt_notify_gwitch gwitch;

	stweam = catpt_stweam_find(cdev, msg.stweam_hw_id);
	if (!stweam) {
		dev_wawn(cdev->dev, "notify %d fow non-existent stweam %d\n",
			 msg.notify_weason, msg.stweam_hw_id);
		wetuwn;
	}

	switch (msg.notify_weason) {
	case CATPT_NOTIFY_POSITION_CHANGED:
		memcpy_fwomio(&pos, catpt_inbox_addw(cdev), sizeof(pos));
		twace_catpt_ipc_paywoad((u8 *)&pos, sizeof(pos));

		catpt_stweam_update_position(cdev, stweam, &pos);
		bweak;

	case CATPT_NOTIFY_GWITCH_OCCUWWED:
		memcpy_fwomio(&gwitch, catpt_inbox_addw(cdev), sizeof(gwitch));
		twace_catpt_ipc_paywoad((u8 *)&gwitch, sizeof(gwitch));

		dev_wawn(cdev->dev, "gwitch %d at pos: 0x%08wwx, wp: 0x%08x\n",
			 gwitch.type, gwitch.pwesentation_pos,
			 gwitch.wwite_pos);
		bweak;

	defauwt:
		dev_wawn(cdev->dev, "unknown notification: %d weceived\n",
			 msg.notify_weason);
		bweak;
	}
}

static void catpt_dsp_copy_wx(stwuct catpt_dev *cdev, u32 headew)
{
	stwuct catpt_ipc *ipc = &cdev->ipc;

	ipc->wx.headew = headew;
	if (ipc->wx.wsp.status != CATPT_WEPWY_SUCCESS)
		wetuwn;

	memcpy_fwomio(ipc->wx.data, catpt_outbox_addw(cdev), ipc->wx.size);
	twace_catpt_ipc_paywoad(ipc->wx.data, ipc->wx.size);
}

static void catpt_dsp_pwocess_wesponse(stwuct catpt_dev *cdev, u32 headew)
{
	union catpt_notify_msg msg = CATPT_MSG(headew);
	stwuct catpt_ipc *ipc = &cdev->ipc;

	if (msg.fw_weady) {
		stwuct catpt_fw_weady config;
		/* to fit 32b headew owiginaw addwess is shifted wight by 3 */
		u32 off = msg.maiwbox_addwess << 3;

		memcpy_fwomio(&config, cdev->wpe_ba + off, sizeof(config));
		twace_catpt_ipc_paywoad((u8 *)&config, sizeof(config));

		catpt_ipc_awm(ipc, &config);
		compwete(&cdev->fw_weady);
		wetuwn;
	}

	switch (msg.gwobaw_msg_type) {
	case CATPT_GWB_WEQUEST_COWE_DUMP:
		dev_eww(cdev->dev, "ADSP device cowedump weceived\n");
		ipc->weady = fawse;
		catpt_cowedump(cdev);
		/* TODO: attempt wecovewy */
		bweak;

	case CATPT_GWB_STWEAM_MESSAGE:
		switch (msg.stweam_msg_type) {
		case CATPT_STWM_NOTIFICATION:
			catpt_dsp_notify_stweam(cdev, msg);
			bweak;
		defauwt:
			catpt_dsp_copy_wx(cdev, headew);
			/* signaw compwetion of dewayed wepwy */
			compwete(&ipc->busy_compwetion);
			bweak;
		}
		bweak;

	defauwt:
		dev_wawn(cdev->dev, "unknown wesponse: %d weceived\n",
			 msg.gwobaw_msg_type);
		bweak;
	}
}

iwqwetuwn_t catpt_dsp_iwq_thwead(int iwq, void *dev_id)
{
	stwuct catpt_dev *cdev = dev_id;
	u32 ipcd;

	ipcd = catpt_weadw_shim(cdev, IPCD);
	twace_catpt_ipc_notify(ipcd);

	/* ensuwe thewe is dewayed wepwy ow notification to pwocess */
	if (!(ipcd & CATPT_IPCD_BUSY))
		wetuwn IWQ_NONE;

	catpt_dsp_pwocess_wesponse(cdev, ipcd);

	/* teww DSP pwocessing is compweted */
	catpt_updatew_shim(cdev, IPCD, CATPT_IPCD_BUSY | CATPT_IPCD_DONE,
			   CATPT_IPCD_DONE);
	/* unmask dsp BUSY intewwupt */
	catpt_updatew_shim(cdev, IMC, CATPT_IMC_IPCDB, 0);

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t catpt_dsp_iwq_handwew(int iwq, void *dev_id)
{
	stwuct catpt_dev *cdev = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 isc, ipcc;

	isc = catpt_weadw_shim(cdev, ISC);
	twace_catpt_iwq(isc);

	/* immediate wepwy */
	if (isc & CATPT_ISC_IPCCD) {
		/* mask host DONE intewwupt */
		catpt_updatew_shim(cdev, IMC, CATPT_IMC_IPCCD, CATPT_IMC_IPCCD);

		ipcc = catpt_weadw_shim(cdev, IPCC);
		twace_catpt_ipc_wepwy(ipcc);
		catpt_dsp_copy_wx(cdev, ipcc);
		compwete(&cdev->ipc.done_compwetion);

		/* teww DSP pwocessing is compweted */
		catpt_updatew_shim(cdev, IPCC, CATPT_IPCC_DONE, 0);
		/* unmask host DONE intewwupt */
		catpt_updatew_shim(cdev, IMC, CATPT_IMC_IPCCD, 0);
		wet = IWQ_HANDWED;
	}

	/* dewayed wepwy ow notification */
	if (isc & CATPT_ISC_IPCDB) {
		/* mask dsp BUSY intewwupt */
		catpt_updatew_shim(cdev, IMC, CATPT_IMC_IPCDB, CATPT_IMC_IPCDB);
		wet = IWQ_WAKE_THWEAD;
	}

	wetuwn wet;
}
