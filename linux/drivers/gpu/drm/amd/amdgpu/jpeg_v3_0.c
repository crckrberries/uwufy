/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu_jpeg.h"
#incwude "amdgpu_pm.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "jpeg_v2_0.h"

#incwude "vcn/vcn_3_0_0_offset.h"
#incwude "vcn/vcn_3_0_0_sh_mask.h"
#incwude "ivswcid/vcn/iwqswcs_vcn_2_0.h"

#define mmUVD_JPEG_PITCH_INTEWNAW_OFFSET	0x401f

static void jpeg_v3_0_set_dec_wing_funcs(stwuct amdgpu_device *adev);
static void jpeg_v3_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static int jpeg_v3_0_set_powewgating_state(void *handwe,
				enum amd_powewgating_state state);

/**
 * jpeg_v3_0_eawwy_init - set function pointews
 *
 * @handwe: amdgpu_device pointew
 *
 * Set wing and iwq function pointews
 */
static int jpeg_v3_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	u32 hawvest;

	switch (amdgpu_ip_vewsion(adev, UVD_HWIP, 0)) {
	case IP_VEWSION(3, 1, 1):
	case IP_VEWSION(3, 1, 2):
		bweak;
	defauwt:
		hawvest = WWEG32_SOC15(JPEG, 0, mmCC_UVD_HAWVESTING);
		if (hawvest & CC_UVD_HAWVESTING__UVD_DISABWE_MASK)
			wetuwn -ENOENT;
		bweak;
	}

	adev->jpeg.num_jpeg_inst = 1;
	adev->jpeg.num_jpeg_wings = 1;

	jpeg_v3_0_set_dec_wing_funcs(adev);
	jpeg_v3_0_set_iwq_funcs(adev);

	wetuwn 0;
}

/**
 * jpeg_v3_0_sw_init - sw init fow JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Woad fiwmwawe and sw initiawization
 */
static int jpeg_v3_0_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int w;

	/* JPEG TWAP */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_VCN,
		VCN_2_0__SWCID__JPEG_DECODE, &adev->jpeg.inst->iwq);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_sw_init(adev);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_wesume(adev);
	if (w)
		wetuwn w;

	wing = adev->jpeg.inst->wing_dec;
	wing->use_doowbeww = twue;
	wing->doowbeww_index = (adev->doowbeww_index.vcn.vcn_wing0_1 << 1) + 1;
	wing->vm_hub = AMDGPU_MMHUB0(0);
	spwintf(wing->name, "jpeg_dec");
	w = amdgpu_wing_init(adev, wing, 512, &adev->jpeg.inst->iwq, 0,
			     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
	if (w)
		wetuwn w;

	adev->jpeg.intewnaw.jpeg_pitch[0] = mmUVD_JPEG_PITCH_INTEWNAW_OFFSET;
	adev->jpeg.inst->extewnaw.jpeg_pitch[0] = SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_PITCH);

	wetuwn 0;
}

/**
 * jpeg_v3_0_sw_fini - sw fini fow JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * JPEG suspend and fwee up sw awwocation
 */
static int jpeg_v3_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_jpeg_suspend(adev);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_sw_fini(adev);

	wetuwn w;
}

/**
 * jpeg_v3_0_hw_init - stawt and test JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 */
static int jpeg_v3_0_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing = adev->jpeg.inst->wing_dec;
	int w;

	adev->nbio.funcs->vcn_doowbeww_wange(adev, wing->use_doowbeww,
		(adev->doowbeww_index.vcn.vcn_wing0_1 << 1), 0);

	w = amdgpu_wing_test_hewpew(wing);
	if (w)
		wetuwn w;

	DWM_INFO("JPEG decode initiawized successfuwwy.\n");

	wetuwn 0;
}

/**
 * jpeg_v3_0_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Stop the JPEG bwock, mawk wing as not weady any mowe
 */
static int jpeg_v3_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);

	if (adev->jpeg.cuw_state != AMD_PG_STATE_GATE &&
	      WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_STATUS))
		jpeg_v3_0_set_powewgating_state(adev, AMD_PG_STATE_GATE);

	wetuwn 0;
}

/**
 * jpeg_v3_0_suspend - suspend JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * HW fini and suspend JPEG bwock
 */
static int jpeg_v3_0_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = jpeg_v3_0_hw_fini(adev);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_suspend(adev);

	wetuwn w;
}

/**
 * jpeg_v3_0_wesume - wesume JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Wesume fiwmwawe and hw init JPEG bwock
 */
static int jpeg_v3_0_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_jpeg_wesume(adev);
	if (w)
		wetuwn w;

	w = jpeg_v3_0_hw_init(adev);

	wetuwn w;
}

static void jpeg_v3_0_disabwe_cwock_gating(stwuct amdgpu_device *adev)
{
	uint32_t data = 0;

	data = WWEG32_SOC15(JPEG, 0, mmJPEG_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_JPEG_MGCG)
		data |= 1 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		data &= ~JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;

	data |= 1 << JPEG_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << JPEG_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(JPEG, 0, mmJPEG_CGC_CTWW, data);

	data = WWEG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE);
	data &= ~(JPEG_CGC_GATE__JPEG_DEC_MASK
		| JPEG_CGC_GATE__JPEG2_DEC_MASK
		| JPEG_CGC_GATE__JPEG_ENC_MASK
		| JPEG_CGC_GATE__JMCIF_MASK
		| JPEG_CGC_GATE__JWBBM_MASK);
	WWEG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE, data);

	data = WWEG32_SOC15(JPEG, 0, mmJPEG_CGC_CTWW);
	data &= ~(JPEG_CGC_CTWW__JPEG_DEC_MODE_MASK
		| JPEG_CGC_CTWW__JPEG2_DEC_MODE_MASK
		| JPEG_CGC_CTWW__JMCIF_MODE_MASK
		| JPEG_CGC_CTWW__JWBBM_MODE_MASK);
	WWEG32_SOC15(JPEG, 0, mmJPEG_CGC_CTWW, data);
}

static void jpeg_v3_0_enabwe_cwock_gating(stwuct amdgpu_device *adev)
{
	uint32_t data = 0;

	data = WWEG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE);
	data |= (JPEG_CGC_GATE__JPEG_DEC_MASK
		|JPEG_CGC_GATE__JPEG2_DEC_MASK
		|JPEG_CGC_GATE__JPEG_ENC_MASK
		|JPEG_CGC_GATE__JMCIF_MASK
		|JPEG_CGC_GATE__JWBBM_MASK);
	WWEG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE, data);
}

static int jpeg_v3_0_disabwe_static_powew_gating(stwuct amdgpu_device *adev)
{
	if (adev->pg_fwags & AMD_PG_SUPPOWT_JPEG) {
		uint32_t data = 0;
		int w = 0;

		data = 1 << UVD_PGFSM_CONFIG__UVDJ_PWW_CONFIG__SHIFT;
		WWEG32(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_PGFSM_CONFIG), data);

		w = SOC15_WAIT_ON_WWEG(JPEG, 0,
			mmUVD_PGFSM_STATUS, UVD_PGFSM_STATUS_UVDJ_PWW_ON,
			UVD_PGFSM_STATUS__UVDJ_PWW_STATUS_MASK);

		if (w) {
			DWM_EWWOW("amdgpu: JPEG disabwe powew gating faiwed\n");
			wetuwn w;
		}
	}

	/* disabwe anti hang mechanism */
	WWEG32_P(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_POWEW_STATUS), 0,
		~UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK);

	/* keep the JPEG in static PG mode */
	WWEG32_P(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_POWEW_STATUS), 0,
		~UVD_JPEG_POWEW_STATUS__JPEG_PG_MODE_MASK);

	wetuwn 0;
}

static int jpeg_v3_0_enabwe_static_powew_gating(stwuct amdgpu_device *adev)
{
	/* enabwe anti hang mechanism */
	WWEG32_P(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JPEG_POWEW_STATUS),
		UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK,
		~UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK);

	if (adev->pg_fwags & AMD_PG_SUPPOWT_JPEG) {
		uint32_t data = 0;
		int w = 0;

		data = 2 << UVD_PGFSM_CONFIG__UVDJ_PWW_CONFIG__SHIFT;
		WWEG32(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_PGFSM_CONFIG), data);

		w = SOC15_WAIT_ON_WWEG(JPEG, 0, mmUVD_PGFSM_STATUS,
			(2 << UVD_PGFSM_STATUS__UVDJ_PWW_STATUS__SHIFT),
			UVD_PGFSM_STATUS__UVDJ_PWW_STATUS_MASK);

		if (w) {
			DWM_EWWOW("amdgpu: JPEG enabwe powew gating faiwed\n");
			wetuwn w;
		}
	}

	wetuwn 0;
}

/**
 * jpeg_v3_0_stawt - stawt JPEG bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the JPEG bwock
 */
static int jpeg_v3_0_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = adev->jpeg.inst->wing_dec;
	int w;

	if (adev->pm.dpm_enabwed)
		amdgpu_dpm_enabwe_jpeg(adev, twue);

	/* disabwe powew gating */
	w = jpeg_v3_0_disabwe_static_powew_gating(adev);
	if (w)
		wetuwn w;

	/* JPEG disabwe CGC */
	jpeg_v3_0_disabwe_cwock_gating(adev);

	/* MJPEG gwobaw tiwing wegistews */
	WWEG32_SOC15(JPEG, 0, mmJPEG_DEC_GFX10_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(JPEG, 0, mmJPEG_ENC_GFX10_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config);

	/* enabwe JMI channew */
	WWEG32_P(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JMI_CNTW), 0,
		~UVD_JMI_CNTW__SOFT_WESET_MASK);

	/* enabwe System Intewwupt fow JWBC */
	WWEG32_P(SOC15_WEG_OFFSET(JPEG, 0, mmJPEG_SYS_INT_EN),
		JPEG_SYS_INT_EN__DJWBC_MASK,
		~JPEG_SYS_INT_EN__DJWBC_MASK);

	WWEG32_SOC15(JPEG, 0, mmUVD_WMI_JWBC_WB_VMID, 0);
	WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_CNTW, (0x00000001W | 0x00000002W));
	WWEG32_SOC15(JPEG, 0, mmUVD_WMI_JWBC_WB_64BIT_BAW_WOW,
		wowew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(JPEG, 0, mmUVD_WMI_JWBC_WB_64BIT_BAW_HIGH,
		uppew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW, 0);
	WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW, 0);
	WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_CNTW, 0x00000002W);
	WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_SIZE, wing->wing_size / 4);
	wing->wptw = WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW);

	wetuwn 0;
}

/**
 * jpeg_v3_0_stop - stop JPEG bwock
 *
 * @adev: amdgpu_device pointew
 *
 * stop the JPEG bwock
 */
static int jpeg_v3_0_stop(stwuct amdgpu_device *adev)
{
	int w;

	/* weset JMI */
	WWEG32_P(SOC15_WEG_OFFSET(JPEG, 0, mmUVD_JMI_CNTW),
		UVD_JMI_CNTW__SOFT_WESET_MASK,
		~UVD_JMI_CNTW__SOFT_WESET_MASK);

	jpeg_v3_0_enabwe_cwock_gating(adev);

	/* enabwe powew gating */
	w = jpeg_v3_0_enabwe_static_powew_gating(adev);
	if (w)
		wetuwn w;

	if (adev->pm.dpm_enabwed)
		amdgpu_dpm_enabwe_jpeg(adev, fawse);

	wetuwn 0;
}

/**
 * jpeg_v3_0_dec_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t jpeg_v3_0_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW);
}

/**
 * jpeg_v3_0_dec_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t jpeg_v3_0_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww)
		wetuwn *wing->wptw_cpu_addw;
	ewse
		wetuwn WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW);
}

/**
 * jpeg_v3_0_dec_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void jpeg_v3_0_dec_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww) {
		*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
	} ewse {
		WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_WB_WPTW, wowew_32_bits(wing->wptw));
	}
}

static boow jpeg_v3_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet = 1;

	wet &= (((WWEG32_SOC15(JPEG, 0, mmUVD_JWBC_STATUS) &
		UVD_JWBC_STATUS__WB_JOB_DONE_MASK) ==
		UVD_JWBC_STATUS__WB_JOB_DONE_MASK));

	wetuwn wet;
}

static int jpeg_v3_0_wait_fow_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn SOC15_WAIT_ON_WWEG(JPEG, 0, mmUVD_JWBC_STATUS,
		UVD_JWBC_STATUS__WB_JOB_DONE_MASK,
		UVD_JWBC_STATUS__WB_JOB_DONE_MASK);
}

static int jpeg_v3_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = state == AMD_CG_STATE_GATE;

	if (enabwe) {
		if (!jpeg_v3_0_is_idwe(handwe))
			wetuwn -EBUSY;
		jpeg_v3_0_enabwe_cwock_gating(adev);
	} ewse {
		jpeg_v3_0_disabwe_cwock_gating(adev);
	}

	wetuwn 0;
}

static int jpeg_v3_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	if(state == adev->jpeg.cuw_state)
		wetuwn 0;

	if (state == AMD_PG_STATE_GATE)
		wet = jpeg_v3_0_stop(adev);
	ewse
		wet = jpeg_v3_0_stawt(adev);

	if(!wet)
		adev->jpeg.cuw_state = state;

	wetuwn wet;
}

static int jpeg_v3_0_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	wetuwn 0;
}

static int jpeg_v3_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("IH: JPEG TWAP\n");

	switch (entwy->swc_id) {
	case VCN_2_0__SWCID__JPEG_DECODE:
		amdgpu_fence_pwocess(adev->jpeg.inst->wing_dec);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static const stwuct amd_ip_funcs jpeg_v3_0_ip_funcs = {
	.name = "jpeg_v3_0",
	.eawwy_init = jpeg_v3_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = jpeg_v3_0_sw_init,
	.sw_fini = jpeg_v3_0_sw_fini,
	.hw_init = jpeg_v3_0_hw_init,
	.hw_fini = jpeg_v3_0_hw_fini,
	.suspend = jpeg_v3_0_suspend,
	.wesume = jpeg_v3_0_wesume,
	.is_idwe = jpeg_v3_0_is_idwe,
	.wait_fow_idwe = jpeg_v3_0_wait_fow_idwe,
	.check_soft_weset = NUWW,
	.pwe_soft_weset = NUWW,
	.soft_weset = NUWW,
	.post_soft_weset = NUWW,
	.set_cwockgating_state = jpeg_v3_0_set_cwockgating_state,
	.set_powewgating_state = jpeg_v3_0_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs jpeg_v3_0_dec_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_JPEG,
	.awign_mask = 0xf,
	.get_wptw = jpeg_v3_0_dec_wing_get_wptw,
	.get_wptw = jpeg_v3_0_dec_wing_get_wptw,
	.set_wptw = jpeg_v3_0_dec_wing_set_wptw,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 6 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 8 +
		8 + /* jpeg_v3_0_dec_wing_emit_vm_fwush */
		18 + 18 + /* jpeg_v3_0_dec_wing_emit_fence x2 vm fence */
		8 + 16,
	.emit_ib_size = 22, /* jpeg_v3_0_dec_wing_emit_ib */
	.emit_ib = jpeg_v2_0_dec_wing_emit_ib,
	.emit_fence = jpeg_v2_0_dec_wing_emit_fence,
	.emit_vm_fwush = jpeg_v2_0_dec_wing_emit_vm_fwush,
	.test_wing = amdgpu_jpeg_dec_wing_test_wing,
	.test_ib = amdgpu_jpeg_dec_wing_test_ib,
	.insewt_nop = jpeg_v2_0_dec_wing_nop,
	.insewt_stawt = jpeg_v2_0_dec_wing_insewt_stawt,
	.insewt_end = jpeg_v2_0_dec_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_jpeg_wing_begin_use,
	.end_use = amdgpu_jpeg_wing_end_use,
	.emit_wweg = jpeg_v2_0_dec_wing_emit_wweg,
	.emit_weg_wait = jpeg_v2_0_dec_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static void jpeg_v3_0_set_dec_wing_funcs(stwuct amdgpu_device *adev)
{
	adev->jpeg.inst->wing_dec->funcs = &jpeg_v3_0_dec_wing_vm_funcs;
	DWM_INFO("JPEG decode is enabwed in VM mode\n");
}

static const stwuct amdgpu_iwq_swc_funcs jpeg_v3_0_iwq_funcs = {
	.set = jpeg_v3_0_set_intewwupt_state,
	.pwocess = jpeg_v3_0_pwocess_intewwupt,
};

static void jpeg_v3_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->jpeg.inst->iwq.num_types = 1;
	adev->jpeg.inst->iwq.funcs = &jpeg_v3_0_iwq_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion jpeg_v3_0_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_JPEG,
	.majow = 3,
	.minow = 0,
	.wev = 0,
	.funcs = &jpeg_v3_0_ip_funcs,
};
