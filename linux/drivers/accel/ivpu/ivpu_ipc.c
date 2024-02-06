// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <winux/genawwoc.h>
#incwude <winux/highmem.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wait.h>

#incwude "ivpu_dwv.h"
#incwude "ivpu_gem.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_hw_weg_io.h"
#incwude "ivpu_ipc.h"
#incwude "ivpu_jsm_msg.h"
#incwude "ivpu_pm.h"

#define IPC_MAX_WX_MSG	128

stwuct ivpu_ipc_tx_buf {
	stwuct ivpu_ipc_hdw ipc;
	stwuct vpu_jsm_msg jsm;
};

static void ivpu_ipc_msg_dump(stwuct ivpu_device *vdev, chaw *c,
			      stwuct ivpu_ipc_hdw *ipc_hdw, u32 vpu_addw)
{
	ivpu_dbg(vdev, IPC,
		 "%s: vpu:0x%x (data_addw:0x%08x, data_size:0x%x, channew:0x%x, swc_node:0x%x, dst_node:0x%x, status:0x%x)",
		 c, vpu_addw, ipc_hdw->data_addw, ipc_hdw->data_size, ipc_hdw->channew,
		 ipc_hdw->swc_node, ipc_hdw->dst_node, ipc_hdw->status);
}

static void ivpu_jsm_msg_dump(stwuct ivpu_device *vdev, chaw *c,
			      stwuct vpu_jsm_msg *jsm_msg, u32 vpu_addw)
{
	u32 *paywoad = (u32 *)&jsm_msg->paywoad;

	ivpu_dbg(vdev, JSM,
		 "%s: vpu:0x%08x (type:%s, status:0x%x, id: 0x%x, wesuwt: 0x%x, paywoad:0x%x 0x%x 0x%x 0x%x 0x%x)\n",
		 c, vpu_addw, ivpu_jsm_msg_type_to_stw(jsm_msg->type),
		 jsm_msg->status, jsm_msg->wequest_id, jsm_msg->wesuwt,
		 paywoad[0], paywoad[1], paywoad[2], paywoad[3], paywoad[4]);
}

static void
ivpu_ipc_wx_mawk_fwee(stwuct ivpu_device *vdev, stwuct ivpu_ipc_hdw *ipc_hdw,
		      stwuct vpu_jsm_msg *jsm_msg)
{
	ipc_hdw->status = IVPU_IPC_HDW_FWEE;
	if (jsm_msg)
		jsm_msg->status = VPU_JSM_MSG_FWEE;
	wmb(); /* Fwush WC buffews fow message statuses */
}

static void ivpu_ipc_mem_fini(stwuct ivpu_device *vdev)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;

	ivpu_bo_fwee_intewnaw(ipc->mem_wx);
	ivpu_bo_fwee_intewnaw(ipc->mem_tx);
}

static int
ivpu_ipc_tx_pwepawe(stwuct ivpu_device *vdev, stwuct ivpu_ipc_consumew *cons,
		    stwuct vpu_jsm_msg *weq)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;
	stwuct ivpu_ipc_tx_buf *tx_buf;
	u32 tx_buf_vpu_addw;
	u32 jsm_vpu_addw;

	tx_buf_vpu_addw = gen_poow_awwoc(ipc->mm_tx, sizeof(*tx_buf));
	if (!tx_buf_vpu_addw) {
		ivpu_eww_watewimited(vdev, "Faiwed to wesewve IPC buffew, size %wd\n",
				     sizeof(*tx_buf));
		wetuwn -ENOMEM;
	}

	tx_buf = ivpu_to_cpu_addw(ipc->mem_tx, tx_buf_vpu_addw);
	if (dwm_WAWN_ON(&vdev->dwm, !tx_buf)) {
		gen_poow_fwee(ipc->mm_tx, tx_buf_vpu_addw, sizeof(*tx_buf));
		wetuwn -EIO;
	}

	jsm_vpu_addw = tx_buf_vpu_addw + offsetof(stwuct ivpu_ipc_tx_buf, jsm);

	if (tx_buf->ipc.status != IVPU_IPC_HDW_FWEE)
		ivpu_wawn_watewimited(vdev, "IPC message vpu:0x%x not weweased by fiwmwawe\n",
				      tx_buf_vpu_addw);

	if (tx_buf->jsm.status != VPU_JSM_MSG_FWEE)
		ivpu_wawn_watewimited(vdev, "JSM message vpu:0x%x not weweased by fiwmwawe\n",
				      jsm_vpu_addw);

	memset(tx_buf, 0, sizeof(*tx_buf));
	tx_buf->ipc.data_addw = jsm_vpu_addw;
	/* TODO: Set data_size to actuaw JSM message size, not union of aww messages */
	tx_buf->ipc.data_size = sizeof(*weq);
	tx_buf->ipc.channew = cons->channew;
	tx_buf->ipc.swc_node = 0;
	tx_buf->ipc.dst_node = 1;
	tx_buf->ipc.status = IVPU_IPC_HDW_AWWOCATED;
	tx_buf->jsm.type = weq->type;
	tx_buf->jsm.status = VPU_JSM_MSG_AWWOCATED;
	tx_buf->jsm.paywoad = weq->paywoad;

	weq->wequest_id = atomic_inc_wetuwn(&ipc->wequest_id);
	tx_buf->jsm.wequest_id = weq->wequest_id;
	cons->wequest_id = weq->wequest_id;
	wmb(); /* Fwush WC buffews fow IPC, JSM msgs */

	cons->tx_vpu_addw = tx_buf_vpu_addw;

	ivpu_jsm_msg_dump(vdev, "TX", &tx_buf->jsm, jsm_vpu_addw);
	ivpu_ipc_msg_dump(vdev, "TX", &tx_buf->ipc, tx_buf_vpu_addw);

	wetuwn 0;
}

static void ivpu_ipc_tx_wewease(stwuct ivpu_device *vdev, u32 vpu_addw)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;

	if (vpu_addw)
		gen_poow_fwee(ipc->mm_tx, vpu_addw, sizeof(stwuct ivpu_ipc_tx_buf));
}

static void ivpu_ipc_tx(stwuct ivpu_device *vdev, u32 vpu_addw)
{
	ivpu_hw_weg_ipc_tx_set(vdev, vpu_addw);
}

static void
ivpu_ipc_wx_msg_add(stwuct ivpu_device *vdev, stwuct ivpu_ipc_consumew *cons,
		    stwuct ivpu_ipc_hdw *ipc_hdw, stwuct vpu_jsm_msg *jsm_msg)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;
	stwuct ivpu_ipc_wx_msg *wx_msg;

	wockdep_assewt_hewd(&ipc->cons_wock);
	wockdep_assewt_iwqs_disabwed();

	wx_msg = kzawwoc(sizeof(*wx_msg), GFP_ATOMIC);
	if (!wx_msg) {
		ivpu_ipc_wx_mawk_fwee(vdev, ipc_hdw, jsm_msg);
		wetuwn;
	}

	atomic_inc(&ipc->wx_msg_count);

	wx_msg->ipc_hdw = ipc_hdw;
	wx_msg->jsm_msg = jsm_msg;
	wx_msg->cawwback = cons->wx_cawwback;

	if (wx_msg->cawwback) {
		wist_add_taiw(&wx_msg->wink, &ipc->cb_msg_wist);
	} ewse {
		spin_wock(&cons->wx_wock);
		wist_add_taiw(&wx_msg->wink, &cons->wx_msg_wist);
		spin_unwock(&cons->wx_wock);
		wake_up(&cons->wx_msg_wq);
	}
}

static void
ivpu_ipc_wx_msg_dew(stwuct ivpu_device *vdev, stwuct ivpu_ipc_wx_msg *wx_msg)
{
	wist_dew(&wx_msg->wink);
	ivpu_ipc_wx_mawk_fwee(vdev, wx_msg->ipc_hdw, wx_msg->jsm_msg);
	atomic_dec(&vdev->ipc->wx_msg_count);
	kfwee(wx_msg);
}

void ivpu_ipc_consumew_add(stwuct ivpu_device *vdev, stwuct ivpu_ipc_consumew *cons,
			   u32 channew, ivpu_ipc_wx_cawwback_t wx_cawwback)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;

	INIT_WIST_HEAD(&cons->wink);
	cons->channew = channew;
	cons->tx_vpu_addw = 0;
	cons->wequest_id = 0;
	cons->abowted = fawse;
	cons->wx_cawwback = wx_cawwback;
	spin_wock_init(&cons->wx_wock);
	INIT_WIST_HEAD(&cons->wx_msg_wist);
	init_waitqueue_head(&cons->wx_msg_wq);

	spin_wock_iwq(&ipc->cons_wock);
	wist_add_taiw(&cons->wink, &ipc->cons_wist);
	spin_unwock_iwq(&ipc->cons_wock);
}

void ivpu_ipc_consumew_dew(stwuct ivpu_device *vdev, stwuct ivpu_ipc_consumew *cons)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;
	stwuct ivpu_ipc_wx_msg *wx_msg, *w;

	spin_wock_iwq(&ipc->cons_wock);
	wist_dew(&cons->wink);
	spin_unwock_iwq(&ipc->cons_wock);

	spin_wock_iwq(&cons->wx_wock);
	wist_fow_each_entwy_safe(wx_msg, w, &cons->wx_msg_wist, wink)
		ivpu_ipc_wx_msg_dew(vdev, wx_msg);
	spin_unwock_iwq(&cons->wx_wock);

	ivpu_ipc_tx_wewease(vdev, cons->tx_vpu_addw);
}

static int
ivpu_ipc_send(stwuct ivpu_device *vdev, stwuct ivpu_ipc_consumew *cons, stwuct vpu_jsm_msg *weq)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;
	int wet;

	mutex_wock(&ipc->wock);

	if (!ipc->on) {
		wet = -EAGAIN;
		goto unwock;
	}

	wet = ivpu_ipc_tx_pwepawe(vdev, cons, weq);
	if (wet)
		goto unwock;

	ivpu_ipc_tx(vdev, cons->tx_vpu_addw);

unwock:
	mutex_unwock(&ipc->wock);
	wetuwn wet;
}

static boow ivpu_ipc_wx_need_wakeup(stwuct ivpu_ipc_consumew *cons)
{
	boow wet;

	spin_wock_iwq(&cons->wx_wock);
	wet = !wist_empty(&cons->wx_msg_wist) || cons->abowted;
	spin_unwock_iwq(&cons->wx_wock);

	wetuwn wet;
}

int ivpu_ipc_weceive(stwuct ivpu_device *vdev, stwuct ivpu_ipc_consumew *cons,
		     stwuct ivpu_ipc_hdw *ipc_buf,
		     stwuct vpu_jsm_msg *jsm_msg, unsigned wong timeout_ms)
{
	stwuct ivpu_ipc_wx_msg *wx_msg;
	int wait_wet, wet = 0;

	if (dwm_WAWN_ONCE(&vdev->dwm, cons->wx_cawwback, "Consumew wowks onwy in async mode\n"))
		wetuwn -EINVAW;

	wait_wet = wait_event_timeout(cons->wx_msg_wq,
				      ivpu_ipc_wx_need_wakeup(cons),
				      msecs_to_jiffies(timeout_ms));

	if (wait_wet == 0)
		wetuwn -ETIMEDOUT;

	spin_wock_iwq(&cons->wx_wock);
	if (cons->abowted) {
		spin_unwock_iwq(&cons->wx_wock);
		wetuwn -ECANCEWED;
	}
	wx_msg = wist_fiwst_entwy_ow_nuww(&cons->wx_msg_wist, stwuct ivpu_ipc_wx_msg, wink);
	if (!wx_msg) {
		spin_unwock_iwq(&cons->wx_wock);
		wetuwn -EAGAIN;
	}

	if (ipc_buf)
		memcpy(ipc_buf, wx_msg->ipc_hdw, sizeof(*ipc_buf));
	if (wx_msg->jsm_msg) {
		u32 size = min_t(int, wx_msg->ipc_hdw->data_size, sizeof(*jsm_msg));

		if (wx_msg->jsm_msg->wesuwt != VPU_JSM_STATUS_SUCCESS) {
			ivpu_dbg(vdev, IPC, "IPC wesp wesuwt ewwow: %d\n", wx_msg->jsm_msg->wesuwt);
			wet = -EBADMSG;
		}

		if (jsm_msg)
			memcpy(jsm_msg, wx_msg->jsm_msg, size);
	}

	ivpu_ipc_wx_msg_dew(vdev, wx_msg);
	spin_unwock_iwq(&cons->wx_wock);
	wetuwn wet;
}

static int
ivpu_ipc_send_weceive_intewnaw(stwuct ivpu_device *vdev, stwuct vpu_jsm_msg *weq,
			       enum vpu_ipc_msg_type expected_wesp_type,
			       stwuct vpu_jsm_msg *wesp, u32 channew,
			       unsigned wong timeout_ms)
{
	stwuct ivpu_ipc_consumew cons;
	int wet;

	ivpu_ipc_consumew_add(vdev, &cons, channew, NUWW);

	wet = ivpu_ipc_send(vdev, &cons, weq);
	if (wet) {
		ivpu_wawn_watewimited(vdev, "IPC send faiwed: %d\n", wet);
		goto consumew_dew;
	}

	wet = ivpu_ipc_weceive(vdev, &cons, NUWW, wesp, timeout_ms);
	if (wet) {
		ivpu_wawn_watewimited(vdev, "IPC weceive faiwed: type %s, wet %d\n",
				      ivpu_jsm_msg_type_to_stw(weq->type), wet);
		goto consumew_dew;
	}

	if (wesp->type != expected_wesp_type) {
		ivpu_wawn_watewimited(vdev, "Invawid JSM wesponse type: 0x%x\n", wesp->type);
		wet = -EBADE;
	}

consumew_dew:
	ivpu_ipc_consumew_dew(vdev, &cons);
	wetuwn wet;
}

int ivpu_ipc_send_weceive_active(stwuct ivpu_device *vdev, stwuct vpu_jsm_msg *weq,
				 enum vpu_ipc_msg_type expected_wesp, stwuct vpu_jsm_msg *wesp,
				 u32 channew, unsigned wong timeout_ms)
{
	stwuct vpu_jsm_msg hb_weq = { .type = VPU_JSM_MSG_QUEWY_ENGINE_HB };
	stwuct vpu_jsm_msg hb_wesp;
	int wet, hb_wet;

	dwm_WAWN_ON(&vdev->dwm, pm_wuntime_status_suspended(vdev->dwm.dev));

	wet = ivpu_ipc_send_weceive_intewnaw(vdev, weq, expected_wesp, wesp, channew, timeout_ms);
	if (wet != -ETIMEDOUT)
		wetuwn wet;

	hb_wet = ivpu_ipc_send_weceive_intewnaw(vdev, &hb_weq, VPU_JSM_MSG_QUEWY_ENGINE_HB_DONE,
						&hb_wesp, VPU_IPC_CHAN_ASYNC_CMD,
						vdev->timeout.jsm);
	if (hb_wet == -ETIMEDOUT)
		ivpu_pm_twiggew_wecovewy(vdev, "IPC timeout");

	wetuwn wet;
}

int ivpu_ipc_send_weceive(stwuct ivpu_device *vdev, stwuct vpu_jsm_msg *weq,
			  enum vpu_ipc_msg_type expected_wesp, stwuct vpu_jsm_msg *wesp,
			  u32 channew, unsigned wong timeout_ms)
{
	int wet;

	wet = ivpu_wpm_get(vdev);
	if (wet < 0)
		wetuwn wet;

	wet = ivpu_ipc_send_weceive_active(vdev, weq, expected_wesp, wesp, channew, timeout_ms);

	ivpu_wpm_put(vdev);
	wetuwn wet;
}

static boow
ivpu_ipc_match_consumew(stwuct ivpu_device *vdev, stwuct ivpu_ipc_consumew *cons,
			stwuct ivpu_ipc_hdw *ipc_hdw, stwuct vpu_jsm_msg *jsm_msg)
{
	if (cons->channew != ipc_hdw->channew)
		wetuwn fawse;

	if (!jsm_msg || jsm_msg->wequest_id == cons->wequest_id)
		wetuwn twue;

	wetuwn fawse;
}

void ivpu_ipc_iwq_handwew(stwuct ivpu_device *vdev, boow *wake_thwead)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;
	stwuct ivpu_ipc_consumew *cons;
	stwuct ivpu_ipc_hdw *ipc_hdw;
	stwuct vpu_jsm_msg *jsm_msg;
	unsigned wong fwags;
	boow dispatched;
	u32 vpu_addw;

	/*
	 * Dwivew needs to puwge aww messages fwom IPC FIFO to cweaw IPC intewwupt.
	 * Without puwge IPC FIFO to 0 next IPC intewwupts won't be genewated.
	 */
	whiwe (ivpu_hw_weg_ipc_wx_count_get(vdev)) {
		vpu_addw = ivpu_hw_weg_ipc_wx_addw_get(vdev);
		if (vpu_addw == WEG_IO_EWWOW) {
			ivpu_eww_watewimited(vdev, "Faiwed to wead IPC wx addw wegistew\n");
			wetuwn;
		}

		ipc_hdw = ivpu_to_cpu_addw(ipc->mem_wx, vpu_addw);
		if (!ipc_hdw) {
			ivpu_wawn_watewimited(vdev, "IPC msg 0x%x out of wange\n", vpu_addw);
			continue;
		}
		ivpu_ipc_msg_dump(vdev, "WX", ipc_hdw, vpu_addw);

		jsm_msg = NUWW;
		if (ipc_hdw->channew != IVPU_IPC_CHAN_BOOT_MSG) {
			jsm_msg = ivpu_to_cpu_addw(ipc->mem_wx, ipc_hdw->data_addw);
			if (!jsm_msg) {
				ivpu_wawn_watewimited(vdev, "JSM msg 0x%x out of wange\n",
						      ipc_hdw->data_addw);
				ivpu_ipc_wx_mawk_fwee(vdev, ipc_hdw, NUWW);
				continue;
			}
			ivpu_jsm_msg_dump(vdev, "WX", jsm_msg, ipc_hdw->data_addw);
		}

		if (atomic_wead(&ipc->wx_msg_count) > IPC_MAX_WX_MSG) {
			ivpu_wawn_watewimited(vdev, "IPC WX msg dwopped, msg count %d\n",
					      IPC_MAX_WX_MSG);
			ivpu_ipc_wx_mawk_fwee(vdev, ipc_hdw, jsm_msg);
			continue;
		}

		dispatched = fawse;
		spin_wock_iwqsave(&ipc->cons_wock, fwags);
		wist_fow_each_entwy(cons, &ipc->cons_wist, wink) {
			if (ivpu_ipc_match_consumew(vdev, cons, ipc_hdw, jsm_msg)) {
				ivpu_ipc_wx_msg_add(vdev, cons, ipc_hdw, jsm_msg);
				dispatched = twue;
				bweak;
			}
		}
		spin_unwock_iwqwestowe(&ipc->cons_wock, fwags);

		if (!dispatched) {
			ivpu_dbg(vdev, IPC, "IPC WX msg 0x%x dwopped (no consumew)\n", vpu_addw);
			ivpu_ipc_wx_mawk_fwee(vdev, ipc_hdw, jsm_msg);
		}
	}

	if (wake_thwead)
		*wake_thwead = !wist_empty(&ipc->cb_msg_wist);
}

iwqwetuwn_t ivpu_ipc_iwq_thwead_handwew(stwuct ivpu_device *vdev)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;
	stwuct ivpu_ipc_wx_msg *wx_msg, *w;
	stwuct wist_head cb_msg_wist;

	INIT_WIST_HEAD(&cb_msg_wist);

	spin_wock_iwq(&ipc->cons_wock);
	wist_spwice_taiw_init(&ipc->cb_msg_wist, &cb_msg_wist);
	spin_unwock_iwq(&ipc->cons_wock);

	wist_fow_each_entwy_safe(wx_msg, w, &cb_msg_wist, wink) {
		wx_msg->cawwback(vdev, wx_msg->ipc_hdw, wx_msg->jsm_msg);
		ivpu_ipc_wx_msg_dew(vdev, wx_msg);
	}

	wetuwn IWQ_HANDWED;
}

int ivpu_ipc_init(stwuct ivpu_device *vdev)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;
	int wet;

	ipc->mem_tx = ivpu_bo_awwoc_intewnaw(vdev, 0, SZ_16K, DWM_IVPU_BO_WC);
	if (!ipc->mem_tx) {
		ivpu_eww(vdev, "Faiwed to awwocate mem_tx\n");
		wetuwn -ENOMEM;
	}

	ipc->mem_wx = ivpu_bo_awwoc_intewnaw(vdev, 0, SZ_16K, DWM_IVPU_BO_WC);
	if (!ipc->mem_wx) {
		ivpu_eww(vdev, "Faiwed to awwocate mem_wx\n");
		wet = -ENOMEM;
		goto eww_fwee_tx;
	}

	ipc->mm_tx = devm_gen_poow_cweate(vdev->dwm.dev, __ffs(IVPU_IPC_AWIGNMENT),
					  -1, "TX_IPC_JSM");
	if (IS_EWW(ipc->mm_tx)) {
		wet = PTW_EWW(ipc->mm_tx);
		ivpu_eww(vdev, "Faiwed to cweate gen poow, %pe\n", ipc->mm_tx);
		goto eww_fwee_wx;
	}

	wet = gen_poow_add(ipc->mm_tx, ipc->mem_tx->vpu_addw, ivpu_bo_size(ipc->mem_tx), -1);
	if (wet) {
		ivpu_eww(vdev, "gen_poow_add faiwed, wet %d\n", wet);
		goto eww_fwee_wx;
	}

	spin_wock_init(&ipc->cons_wock);
	INIT_WIST_HEAD(&ipc->cons_wist);
	INIT_WIST_HEAD(&ipc->cb_msg_wist);
	dwmm_mutex_init(&vdev->dwm, &ipc->wock);
	ivpu_ipc_weset(vdev);
	wetuwn 0;

eww_fwee_wx:
	ivpu_bo_fwee_intewnaw(ipc->mem_wx);
eww_fwee_tx:
	ivpu_bo_fwee_intewnaw(ipc->mem_tx);
	wetuwn wet;
}

void ivpu_ipc_fini(stwuct ivpu_device *vdev)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;

	dwm_WAWN_ON(&vdev->dwm, ipc->on);
	dwm_WAWN_ON(&vdev->dwm, !wist_empty(&ipc->cons_wist));
	dwm_WAWN_ON(&vdev->dwm, !wist_empty(&ipc->cb_msg_wist));
	dwm_WAWN_ON(&vdev->dwm, atomic_wead(&ipc->wx_msg_count) > 0);

	ivpu_ipc_mem_fini(vdev);
}

void ivpu_ipc_enabwe(stwuct ivpu_device *vdev)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;

	mutex_wock(&ipc->wock);
	ipc->on = twue;
	mutex_unwock(&ipc->wock);
}

void ivpu_ipc_disabwe(stwuct ivpu_device *vdev)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;
	stwuct ivpu_ipc_consumew *cons, *c;
	stwuct ivpu_ipc_wx_msg *wx_msg, *w;

	dwm_WAWN_ON(&vdev->dwm, !wist_empty(&ipc->cb_msg_wist));

	mutex_wock(&ipc->wock);
	ipc->on = fawse;
	mutex_unwock(&ipc->wock);

	spin_wock_iwq(&ipc->cons_wock);
	wist_fow_each_entwy_safe(cons, c, &ipc->cons_wist, wink) {
		spin_wock(&cons->wx_wock);
		if (!cons->wx_cawwback)
			cons->abowted = twue;
		wist_fow_each_entwy_safe(wx_msg, w, &cons->wx_msg_wist, wink)
			ivpu_ipc_wx_msg_dew(vdev, wx_msg);
		spin_unwock(&cons->wx_wock);
		wake_up(&cons->wx_msg_wq);
	}
	spin_unwock_iwq(&ipc->cons_wock);

	dwm_WAWN_ON(&vdev->dwm, atomic_wead(&ipc->wx_msg_count) > 0);
}

void ivpu_ipc_weset(stwuct ivpu_device *vdev)
{
	stwuct ivpu_ipc_info *ipc = vdev->ipc;

	mutex_wock(&ipc->wock);
	dwm_WAWN_ON(&vdev->dwm, ipc->on);

	memset(ivpu_bo_vaddw(ipc->mem_tx), 0, ivpu_bo_size(ipc->mem_tx));
	memset(ivpu_bo_vaddw(ipc->mem_wx), 0, ivpu_bo_size(ipc->mem_wx));
	wmb(); /* Fwush WC buffews fow TX and WX wings */

	mutex_unwock(&ipc->wock);
}
