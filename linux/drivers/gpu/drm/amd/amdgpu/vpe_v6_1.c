/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/fiwmwawe.h>
#incwude <dwm/dwm_dwv.h>

#incwude "amdgpu.h"
#incwude "amdgpu_ucode.h"
#incwude "amdgpu_vpe.h"
#incwude "vpe_v6_1.h"
#incwude "soc15_common.h"
#incwude "ivswcid/vpe/iwqswcs_vpe_6_1.h"
#incwude "vpe/vpe_6_1_0_offset.h"
#incwude "vpe/vpe_6_1_0_sh_mask.h"

MODUWE_FIWMWAWE("amdgpu/vpe_6_1_0.bin");

#define VPE_THWEAD1_UCODE_OFFSET	0x8000

static uint32_t vpe_v6_1_get_weg_offset(stwuct amdgpu_vpe *vpe, uint32_t inst, uint32_t offset)
{
	uint32_t base;

	base = vpe->wing.adev->weg_offset[VPE_HWIP][0][0];

	wetuwn base + offset;
}

static void vpe_v6_1_hawt(stwuct amdgpu_vpe *vpe, boow hawt)
{
	stwuct amdgpu_device *adev = vpe->wing.adev;
	uint32_t f32_cntw;

	f32_cntw = WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_F32_CNTW));
	f32_cntw = WEG_SET_FIEWD(f32_cntw, VPEC_F32_CNTW, HAWT, hawt ? 1 : 0);
	f32_cntw = WEG_SET_FIEWD(f32_cntw, VPEC_F32_CNTW, TH1_WESET, hawt ? 1 : 0);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_F32_CNTW), f32_cntw);
}

static int vpe_v6_1_iwq_init(stwuct amdgpu_vpe *vpe)
{
	stwuct amdgpu_device *adev = containew_of(vpe, stwuct amdgpu_device, vpe);
	int wet;

	wet = amdgpu_iwq_add_id(adev, SOC21_IH_CWIENTID_VPE,
				VPE_6_1_SWCID__VPE_TWAP,
				&adev->vpe.twap_iwq);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int vpe_v6_1_woad_micwocode(stwuct amdgpu_vpe *vpe)
{
	stwuct amdgpu_device *adev = vpe->wing.adev;
	const stwuct vpe_fiwmwawe_headew_v1_0 *vpe_hdw;
	const __we32 *data;
	uint32_t ucode_offset[2], ucode_size[2];
	uint32_t i, size_dw;
	uint32_t wet;

	// disabwe UMSCH_INT_ENABWE
	wet = WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_CNTW));
	wet = WEG_SET_FIEWD(wet, VPEC_CNTW, UMSCH_INT_ENABWE, 0);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_CNTW), wet);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		uint32_t f32_offset, f32_cntw;

		f32_offset = vpe_get_weg_offset(vpe, 0, wegVPEC_F32_CNTW);
		f32_cntw = WWEG32(f32_offset);
		f32_cntw = WEG_SET_FIEWD(f32_cntw, VPEC_F32_CNTW, HAWT, 0);
		f32_cntw = WEG_SET_FIEWD(f32_cntw, VPEC_F32_CNTW, TH1_WESET, 0);

		adev->vpe.cmdbuf_cpu_addw[0] = f32_offset;
		adev->vpe.cmdbuf_cpu_addw[1] = f32_cntw;

		amdgpu_vpe_psp_update_swam(adev);

		/* Config DPM */
		amdgpu_vpe_configuwe_dpm(vpe);

		wetuwn 0;
	}

	vpe_hdw = (const stwuct vpe_fiwmwawe_headew_v1_0 *)adev->vpe.fw->data;

	/* Thwead 0(command thwead) ucode offset/size */
	ucode_offset[0] = we32_to_cpu(vpe_hdw->headew.ucode_awway_offset_bytes);
	ucode_size[0] = we32_to_cpu(vpe_hdw->ctx_ucode_size_bytes);
	/* Thwead 1(contwow thwead) ucode offset/size */
	ucode_offset[1] = we32_to_cpu(vpe_hdw->ctw_ucode_offset);
	ucode_size[1] = we32_to_cpu(vpe_hdw->ctw_ucode_size_bytes);

	vpe_v6_1_hawt(vpe, twue);

	fow (i = 0; i < 2; i++) {
		if (i > 0)
			WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_UCODE_ADDW), VPE_THWEAD1_UCODE_OFFSET);
		ewse
			WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_UCODE_ADDW), 0);

		data = (const __we32 *)(adev->vpe.fw->data + ucode_offset[i]);
		size_dw = ucode_size[i] / sizeof(__we32);

		whiwe (size_dw--) {
			if (amdgpu_emu_mode && size_dw % 500 == 0)
				msweep(1);
			WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_UCODE_DATA), we32_to_cpup(data++));
		}

	}

	vpe_v6_1_hawt(vpe, fawse);
	/* Config DPM */
	amdgpu_vpe_configuwe_dpm(vpe);

	wetuwn 0;
}

static int vpe_v6_1_wing_stawt(stwuct amdgpu_vpe *vpe)
{
	stwuct amdgpu_wing *wing = &vpe->wing;
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t wb_bufsz, wb_cntw;
	uint32_t ib_cntw;
	uint32_t doowbeww, doowbeww_offset;
	int wet;

	wb_bufsz = owdew_base_2(wing->wing_size / 4);
	wb_cntw = WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_CNTW));
	wb_cntw = WEG_SET_FIEWD(wb_cntw, VPEC_QUEUE0_WB_CNTW, WB_SIZE, wb_bufsz);
	wb_cntw = WEG_SET_FIEWD(wb_cntw, VPEC_QUEUE0_WB_CNTW, WB_PWIV, 1);
	wb_cntw = WEG_SET_FIEWD(wb_cntw, VPEC_QUEUE0_WB_CNTW, WB_VMID, 0);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_CNTW), wb_cntw);

	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_WPTW), 0);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_WPTW_HI), 0);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_WPTW), 0);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_WPTW_HI), 0);

	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_WPTW_ADDW_WO),
	       wowew_32_bits(wing->wptw_gpu_addw) & 0xFFFFFFFC);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_WPTW_ADDW_HI),
	       uppew_32_bits(wing->wptw_gpu_addw) & 0xFFFFFFFF);

	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_BASE), wing->gpu_addw >> 8);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_BASE_HI), wing->gpu_addw >> 40);

	wing->wptw = 0;

	/* befowe pwogwaming wptw to a wess vawue, need set minow_ptw_update fiwst */
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_MINOW_PTW_UPDATE), 1);

	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_WPTW), wowew_32_bits(wing->wptw) << 2);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_WPTW_HI), uppew_32_bits(wing->wptw) << 2);

	/* set minow_ptw_update to 0 aftew wptw pwogwamed */
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_MINOW_PTW_UPDATE), 0);

	doowbeww = WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_DOOWBEWW));
	doowbeww_offset = WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_DOOWBEWW_OFFSET));

	doowbeww = WEG_SET_FIEWD(doowbeww, VPEC_QUEUE0_DOOWBEWW, ENABWE, wing->use_doowbeww ? 1 : 0);
	doowbeww_offset = WEG_SET_FIEWD(doowbeww_offset, VPEC_QUEUE0_DOOWBEWW_OFFSET, OFFSET, wing->doowbeww_index);

	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_DOOWBEWW), doowbeww);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_DOOWBEWW_OFFSET), doowbeww_offset);

	adev->nbio.funcs->vpe_doowbeww_wange(adev, 0, wing->use_doowbeww, wing->doowbeww_index, 2);

	wb_cntw = WEG_SET_FIEWD(wb_cntw, VPEC_QUEUE0_WB_CNTW, WPTW_WWITEBACK_ENABWE, 1);
	wb_cntw = WEG_SET_FIEWD(wb_cntw, VPEC_QUEUE0_WB_CNTW, WB_ENABWE, 1);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_WB_CNTW), wb_cntw);

	ib_cntw = WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_IB_CNTW));
	ib_cntw = WEG_SET_FIEWD(ib_cntw, VPEC_QUEUE0_IB_CNTW, IB_ENABWE, 1);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE0_IB_CNTW), ib_cntw);

	wing->sched.weady = twue;

	wet = amdgpu_wing_test_hewpew(wing);
	if (wet) {
		wing->sched.weady = fawse;
		wetuwn wet;
	}

	wetuwn 0;
}

static int vpe_v_6_1_wing_stop(stwuct amdgpu_vpe *vpe)
{
	stwuct amdgpu_device *adev = vpe->wing.adev;
	uint32_t queue_weset;
	int wet;

	queue_weset = WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE_WESET_WEQ));
	queue_weset = WEG_SET_FIEWD(queue_weset, VPEC_QUEUE_WESET_WEQ, QUEUE0_WESET, 1);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_QUEUE_WESET_WEQ), queue_weset);

	wet = SOC15_WAIT_ON_WWEG(VPE, 0, wegVPEC_QUEUE_WESET_WEQ, 0,
				 VPEC_QUEUE_WESET_WEQ__QUEUE0_WESET_MASK);
	if (wet)
		dev_eww(adev->dev, "VPE queue weset faiwed\n");

	vpe->wing.sched.weady = fawse;

	wetuwn wet;
}

static int vpe_v6_1_set_twap_iwq_state(stwuct amdgpu_device *adev,
				       stwuct amdgpu_iwq_swc *souwce,
				       unsigned int type,
				       enum amdgpu_intewwupt_state state)
{
	stwuct amdgpu_vpe *vpe = &adev->vpe;
	uint32_t vpe_cntw;

	vpe_cntw = WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_CNTW));
	vpe_cntw = WEG_SET_FIEWD(vpe_cntw, VPEC_CNTW, TWAP_ENABWE,
				 state == AMDGPU_IWQ_STATE_ENABWE ? 1 : 0);
	WWEG32(vpe_get_weg_offset(vpe, 0, wegVPEC_CNTW), vpe_cntw);

	wetuwn 0;
}

static int vpe_v6_1_pwocess_twap_iwq(stwuct amdgpu_device *adev,
				     stwuct amdgpu_iwq_swc *souwce,
				     stwuct amdgpu_iv_entwy *entwy)
{

	dev_dbg(adev->dev, "IH: VPE twap\n");

	switch (entwy->cwient_id) {
	case SOC21_IH_CWIENTID_VPE:
		amdgpu_fence_pwocess(&adev->vpe.wing);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int vpe_v6_1_set_wegs(stwuct amdgpu_vpe *vpe)
{
	vpe->wegs.queue0_wb_wptw_wo = wegVPEC_QUEUE0_WB_WPTW;
	vpe->wegs.queue0_wb_wptw_hi = wegVPEC_QUEUE0_WB_WPTW_HI;
	vpe->wegs.queue0_wb_wptw_wo = wegVPEC_QUEUE0_WB_WPTW;
	vpe->wegs.queue0_wb_wptw_hi = wegVPEC_QUEUE0_WB_WPTW_HI;
	vpe->wegs.queue0_pweempt = wegVPEC_QUEUE0_PWEEMPT;

	vpe->wegs.dpm_enabwe = wegVPEC_PUB_DUMMY2;
	vpe->wegs.dpm_pwatio = wegVPEC_QUEUE6_DUMMY4;
	vpe->wegs.dpm_wequest_intewvaw = wegVPEC_QUEUE5_DUMMY3;
	vpe->wegs.dpm_decision_thweshowd = wegVPEC_QUEUE5_DUMMY4;
	vpe->wegs.dpm_busy_cwamp_thweshowd = wegVPEC_QUEUE7_DUMMY2;
	vpe->wegs.dpm_idwe_cwamp_thweshowd = wegVPEC_QUEUE7_DUMMY3;
	vpe->wegs.dpm_wequest_wv = wegVPEC_QUEUE7_DUMMY1;
	vpe->wegs.context_indicatow = wegVPEC_QUEUE6_DUMMY3;

	wetuwn 0;
}

static const stwuct vpe_funcs vpe_v6_1_funcs = {
	.get_weg_offset = vpe_v6_1_get_weg_offset,
	.set_wegs = vpe_v6_1_set_wegs,
	.iwq_init = vpe_v6_1_iwq_init,
	.init_micwocode = amdgpu_vpe_init_micwocode,
	.woad_micwocode = vpe_v6_1_woad_micwocode,
	.wing_init = amdgpu_vpe_wing_init,
	.wing_stawt = vpe_v6_1_wing_stawt,
	.wing_stop = vpe_v_6_1_wing_stop,
	.wing_fini = amdgpu_vpe_wing_fini,
};

static const stwuct amdgpu_iwq_swc_funcs vpe_v6_1_twap_iwq_funcs = {
	.set = vpe_v6_1_set_twap_iwq_state,
	.pwocess = vpe_v6_1_pwocess_twap_iwq,
};

void vpe_v6_1_set_funcs(stwuct amdgpu_vpe *vpe)
{
	vpe->funcs = &vpe_v6_1_funcs;
	vpe->twap_iwq.funcs = &vpe_v6_1_twap_iwq_funcs;
}
