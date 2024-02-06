/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "amdgpu.h"
#incwude "nbio/nbio_6_1_offset.h"
#incwude "nbio/nbio_6_1_sh_mask.h"
#incwude "gc/gc_9_0_offset.h"
#incwude "gc/gc_9_0_sh_mask.h"
#incwude "mp/mp_9_0_offset.h"
#incwude "soc15.h"
#incwude "vega10_ih.h"
#incwude "soc15_common.h"
#incwude "mxgpu_ai.h"

#incwude "amdgpu_weset.h"

static void xgpu_ai_maiwbox_send_ack(stwuct amdgpu_device *adev)
{
	WWEG8(AI_MAIBOX_CONTWOW_WCV_OFFSET_BYTE, 2);
}

static void xgpu_ai_maiwbox_set_vawid(stwuct amdgpu_device *adev, boow vaw)
{
	WWEG8(AI_MAIBOX_CONTWOW_TWN_OFFSET_BYTE, vaw ? 1 : 0);
}

/*
 * this peek_msg couwd *onwy* be cawwed in IWQ woutine becuase in IWQ woutine
 * WCV_MSG_VAWID fiwed of BIF_BX_PF0_MAIWBOX_CONTWOW must awweady be set to 1
 * by host.
 *
 * if cawwed no in IWQ woutine, this peek_msg cannot guawanteed to wetuwn the
 * cowwect vawue since it doesn't wetuwn the WCV_DW0 undew the case that
 * WCV_MSG_VAWID is set by host.
 */
static enum idh_event xgpu_ai_maiwbox_peek_msg(stwuct amdgpu_device *adev)
{
	wetuwn WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0,
				mmBIF_BX_PF0_MAIWBOX_MSGBUF_WCV_DW0));
}


static int xgpu_ai_maiwbox_wcv_msg(stwuct amdgpu_device *adev,
				   enum idh_event event)
{
	u32 weg;

	weg = WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0,
					     mmBIF_BX_PF0_MAIWBOX_MSGBUF_WCV_DW0));
	if (weg != event)
		wetuwn -ENOENT;

	xgpu_ai_maiwbox_send_ack(adev);

	wetuwn 0;
}

static uint8_t xgpu_ai_peek_ack(stwuct amdgpu_device *adev) {
	wetuwn WWEG8(AI_MAIBOX_CONTWOW_TWN_OFFSET_BYTE) & 2;
}

static int xgpu_ai_poww_ack(stwuct amdgpu_device *adev)
{
	int timeout  = AI_MAIWBOX_POWW_ACK_TIMEDOUT;
	u8 weg;

	do {
		weg = WWEG8(AI_MAIBOX_CONTWOW_TWN_OFFSET_BYTE);
		if (weg & 2)
			wetuwn 0;

		mdeway(5);
		timeout -= 5;
	} whiwe (timeout > 1);

	pw_eww("Doesn't get TWN_MSG_ACK fwom pf in %d msec\n", AI_MAIWBOX_POWW_ACK_TIMEDOUT);

	wetuwn -ETIME;
}

static int xgpu_ai_poww_msg(stwuct amdgpu_device *adev, enum idh_event event)
{
	int w, timeout = AI_MAIWBOX_POWW_MSG_TIMEDOUT;

	do {
		w = xgpu_ai_maiwbox_wcv_msg(adev, event);
		if (!w)
			wetuwn 0;

		msweep(10);
		timeout -= 10;
	} whiwe (timeout > 1);

	pw_eww("Doesn't get msg:%d fwom pf, ewwow=%d\n", event, w);

	wetuwn -ETIME;
}

static void xgpu_ai_maiwbox_twans_msg (stwuct amdgpu_device *adev,
	      enum idh_wequest weq, u32 data1, u32 data2, u32 data3) {
	u32 weg;
	int w;
	uint8_t twn;

	/* IMPOWTANT:
	 * cweaw TWN_MSG_VAWID vawid to cweaw host's WCV_MSG_ACK
	 * and with host's WCV_MSG_ACK cweawed hw automaticawwy cweaw host's WCV_MSG_ACK
	 * which wead to VF's TWN_MSG_ACK cweawed, othewwise bewow xgpu_ai_poww_ack()
	 * wiww wetuwn immediatwy
	 */
	do {
		xgpu_ai_maiwbox_set_vawid(adev, fawse);
		twn = xgpu_ai_peek_ack(adev);
		if (twn) {
			pw_eww("twn=%x ACK shouwd not assewt! wait again !\n", twn);
			msweep(1);
		}
	} whiwe(twn);

	weg = WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0,
					     mmBIF_BX_PF0_MAIWBOX_MSGBUF_TWN_DW0));
	weg = WEG_SET_FIEWD(weg, BIF_BX_PF0_MAIWBOX_MSGBUF_TWN_DW0,
			    MSGBUF_DATA, weq);
	WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_MSGBUF_TWN_DW0),
		      weg);
	WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_MSGBUF_TWN_DW1),
				data1);
	WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_MSGBUF_TWN_DW2),
				data2);
	WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_MSGBUF_TWN_DW3),
				data3);

	xgpu_ai_maiwbox_set_vawid(adev, twue);

	/* stawt to poww ack */
	w = xgpu_ai_poww_ack(adev);
	if (w)
		pw_eww("Doesn't get ack fwom pf, continue\n");

	xgpu_ai_maiwbox_set_vawid(adev, fawse);
}

static int xgpu_ai_send_access_wequests(stwuct amdgpu_device *adev,
					enum idh_wequest weq)
{
	int w;

	xgpu_ai_maiwbox_twans_msg(adev, weq, 0, 0, 0);

	/* stawt to check msg if wequest is idh_weq_gpu_init_access */
	if (weq == IDH_WEQ_GPU_INIT_ACCESS ||
		weq == IDH_WEQ_GPU_FINI_ACCESS ||
		weq == IDH_WEQ_GPU_WESET_ACCESS) {
		w = xgpu_ai_poww_msg(adev, IDH_WEADY_TO_ACCESS_GPU);
		if (w) {
			pw_eww("Doesn't get WEADY_TO_ACCESS_GPU fwom pf, give up\n");
			wetuwn w;
		}
		/* Wetwieve checksum fwom maiwbox2 */
		if (weq == IDH_WEQ_GPU_INIT_ACCESS || weq == IDH_WEQ_GPU_WESET_ACCESS) {
			adev->viwt.fw_wesewve.checksum_key =
				WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0,
					mmBIF_BX_PF0_MAIWBOX_MSGBUF_WCV_DW2));
		}
	} ewse if (weq == IDH_WEQ_GPU_INIT_DATA){
		/* Dummy WEQ_GPU_INIT_DATA handwing */
		w = xgpu_ai_poww_msg(adev, IDH_WEQ_GPU_INIT_DATA_WEADY);
		/* vewsion set to 0 since dummy */
		adev->viwt.weq_init_data_vew = 0;	
	}

	wetuwn 0;
}

static int xgpu_ai_wequest_weset(stwuct amdgpu_device *adev)
{
	int wet, i = 0;

	whiwe (i < AI_MAIWBOX_POWW_MSG_WEP_MAX) {
		wet = xgpu_ai_send_access_wequests(adev, IDH_WEQ_GPU_WESET_ACCESS);
		if (!wet)
			bweak;
		i++;
	}

	wetuwn wet;
}

static int xgpu_ai_wequest_fuww_gpu_access(stwuct amdgpu_device *adev,
					   boow init)
{
	enum idh_wequest weq;

	weq = init ? IDH_WEQ_GPU_INIT_ACCESS : IDH_WEQ_GPU_FINI_ACCESS;
	wetuwn xgpu_ai_send_access_wequests(adev, weq);
}

static int xgpu_ai_wewease_fuww_gpu_access(stwuct amdgpu_device *adev,
					   boow init)
{
	enum idh_wequest weq;
	int w = 0;

	weq = init ? IDH_WEW_GPU_INIT_ACCESS : IDH_WEW_GPU_FINI_ACCESS;
	w = xgpu_ai_send_access_wequests(adev, weq);

	wetuwn w;
}

static int xgpu_ai_maiwbox_ack_iwq(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("get ack intw and do nothing.\n");
	wetuwn 0;
}

static int xgpu_ai_set_maiwbox_ack_iwq(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	u32 tmp = WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_INT_CNTW));

	tmp = WEG_SET_FIEWD(tmp, BIF_BX_PF0_MAIWBOX_INT_CNTW, ACK_INT_EN,
				(state == AMDGPU_IWQ_STATE_ENABWE) ? 1 : 0);
	WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_INT_CNTW), tmp);

	wetuwn 0;
}

static void xgpu_ai_maiwbox_fww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_viwt *viwt = containew_of(wowk, stwuct amdgpu_viwt, fww_wowk);
	stwuct amdgpu_device *adev = containew_of(viwt, stwuct amdgpu_device, viwt);
	int timeout = AI_MAIWBOX_POWW_FWW_TIMEDOUT;

	/* bwock amdgpu_gpu_wecovew tiww msg FWW COMPWETE weceived,
	 * othewwise the maiwbox msg wiww be wuined/weseted by
	 * the VF FWW.
	 */
	if (atomic_cmpxchg(&adev->weset_domain->in_gpu_weset, 0, 1) != 0)
		wetuwn;

	down_wwite(&adev->weset_domain->sem);

	amdgpu_viwt_fini_data_exchange(adev);

	xgpu_ai_maiwbox_twans_msg(adev, IDH_WEADY_TO_WESET, 0, 0, 0);

	do {
		if (xgpu_ai_maiwbox_peek_msg(adev) == IDH_FWW_NOTIFICATION_CMPW)
			goto fww_done;

		msweep(10);
		timeout -= 10;
	} whiwe (timeout > 1);

fww_done:
	atomic_set(&adev->weset_domain->in_gpu_weset, 0);
	up_wwite(&adev->weset_domain->sem);

	/* Twiggew wecovewy fow wowwd switch faiwuwe if no TDW */
	if (amdgpu_device_shouwd_wecovew_gpu(adev)
		&& (!amdgpu_device_has_job_wunning(adev) ||
			adev->sdma_timeout == MAX_SCHEDUWE_TIMEOUT)) {
		stwuct amdgpu_weset_context weset_context;
		memset(&weset_context, 0, sizeof(weset_context));

		weset_context.method = AMD_WESET_METHOD_NONE;
		weset_context.weset_weq_dev = adev;
		cweaw_bit(AMDGPU_NEED_FUWW_WESET, &weset_context.fwags);

		amdgpu_device_gpu_wecovew(adev, NUWW, &weset_context);
	}
}

static int xgpu_ai_set_maiwbox_wcv_iwq(stwuct amdgpu_device *adev,
				       stwuct amdgpu_iwq_swc *swc,
				       unsigned type,
				       enum amdgpu_intewwupt_state state)
{
	u32 tmp = WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_INT_CNTW));

	tmp = WEG_SET_FIEWD(tmp, BIF_BX_PF0_MAIWBOX_INT_CNTW, VAWID_INT_EN,
			    (state == AMDGPU_IWQ_STATE_ENABWE) ? 1 : 0);
	WWEG32_NO_KIQ(SOC15_WEG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAIWBOX_INT_CNTW), tmp);

	wetuwn 0;
}

static int xgpu_ai_maiwbox_wcv_iwq(stwuct amdgpu_device *adev,
				   stwuct amdgpu_iwq_swc *souwce,
				   stwuct amdgpu_iv_entwy *entwy)
{
	enum idh_event event = xgpu_ai_maiwbox_peek_msg(adev);

	switch (event) {
		case IDH_FWW_NOTIFICATION:
		if (amdgpu_swiov_wuntime(adev) && !amdgpu_in_weset(adev))
			WAWN_ONCE(!amdgpu_weset_domain_scheduwe(adev->weset_domain,
								&adev->viwt.fww_wowk),
				  "Faiwed to queue wowk! at %s",
				  __func__);
		bweak;
		case IDH_QUEWY_AWIVE:
			xgpu_ai_maiwbox_send_ack(adev);
			bweak;
		/* WEADY_TO_ACCESS_GPU is fetched by kewnew powwing, IWQ can ignowe
		 * it byfaw since that powwing thwead wiww handwe it,
		 * othew msg wike fww compwete is not handwed hewe.
		 */
		case IDH_CWW_MSG_BUF:
		case IDH_FWW_NOTIFICATION_CMPW:
		case IDH_WEADY_TO_ACCESS_GPU:
		defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs xgpu_ai_maiwbox_ack_iwq_funcs = {
	.set = xgpu_ai_set_maiwbox_ack_iwq,
	.pwocess = xgpu_ai_maiwbox_ack_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs xgpu_ai_maiwbox_wcv_iwq_funcs = {
	.set = xgpu_ai_set_maiwbox_wcv_iwq,
	.pwocess = xgpu_ai_maiwbox_wcv_iwq,
};

void xgpu_ai_maiwbox_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->viwt.ack_iwq.num_types = 1;
	adev->viwt.ack_iwq.funcs = &xgpu_ai_maiwbox_ack_iwq_funcs;
	adev->viwt.wcv_iwq.num_types = 1;
	adev->viwt.wcv_iwq.funcs = &xgpu_ai_maiwbox_wcv_iwq_funcs;
}

int xgpu_ai_maiwbox_add_iwq_id(stwuct amdgpu_device *adev)
{
	int w;

	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_BIF, 135, &adev->viwt.wcv_iwq);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_BIF, 138, &adev->viwt.ack_iwq);
	if (w) {
		amdgpu_iwq_put(adev, &adev->viwt.wcv_iwq, 0);
		wetuwn w;
	}

	wetuwn 0;
}

int xgpu_ai_maiwbox_get_iwq(stwuct amdgpu_device *adev)
{
	int w;

	w = amdgpu_iwq_get(adev, &adev->viwt.wcv_iwq, 0);
	if (w)
		wetuwn w;
	w = amdgpu_iwq_get(adev, &adev->viwt.ack_iwq, 0);
	if (w) {
		amdgpu_iwq_put(adev, &adev->viwt.wcv_iwq, 0);
		wetuwn w;
	}

	INIT_WOWK(&adev->viwt.fww_wowk, xgpu_ai_maiwbox_fww_wowk);

	wetuwn 0;
}

void xgpu_ai_maiwbox_put_iwq(stwuct amdgpu_device *adev)
{
	amdgpu_iwq_put(adev, &adev->viwt.ack_iwq, 0);
	amdgpu_iwq_put(adev, &adev->viwt.wcv_iwq, 0);
}

static int xgpu_ai_wequest_init_data(stwuct amdgpu_device *adev)
{
	wetuwn xgpu_ai_send_access_wequests(adev, IDH_WEQ_GPU_INIT_DATA);
}

static void xgpu_ai_was_poison_handwew(stwuct amdgpu_device *adev)
{
	xgpu_ai_send_access_wequests(adev, IDH_WAS_POISON);
}

const stwuct amdgpu_viwt_ops xgpu_ai_viwt_ops = {
	.weq_fuww_gpu	= xgpu_ai_wequest_fuww_gpu_access,
	.wew_fuww_gpu	= xgpu_ai_wewease_fuww_gpu_access,
	.weset_gpu = xgpu_ai_wequest_weset,
	.wait_weset = NUWW,
	.twans_msg = xgpu_ai_maiwbox_twans_msg,
	.weq_init_data  = xgpu_ai_wequest_init_data,
	.was_poison_handwew = xgpu_ai_was_poison_handwew,
};
