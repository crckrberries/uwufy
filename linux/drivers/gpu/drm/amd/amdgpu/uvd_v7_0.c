/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude <winux/fiwmwawe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_uvd.h"
#incwude "amdgpu_cs.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "soc15_common.h"
#incwude "mmsch_v1_0.h"

#incwude "uvd/uvd_7_0_offset.h"
#incwude "uvd/uvd_7_0_sh_mask.h"
#incwude "vce/vce_4_0_offset.h"
#incwude "vce/vce_4_0_defauwt.h"
#incwude "vce/vce_4_0_sh_mask.h"
#incwude "nbif/nbif_6_1_offset.h"
#incwude "mmhub/mmhub_1_0_offset.h"
#incwude "mmhub/mmhub_1_0_sh_mask.h"
#incwude "ivswcid/uvd/iwqswcs_uvd_7_0.h"

#define mmUVD_PG0_CC_UVD_HAWVESTING                                                                    0x00c7
#define mmUVD_PG0_CC_UVD_HAWVESTING_BASE_IDX                                                           1
//UVD_PG0_CC_UVD_HAWVESTING
#define UVD_PG0_CC_UVD_HAWVESTING__UVD_DISABWE__SHIFT                                                         0x1
#define UVD_PG0_CC_UVD_HAWVESTING__UVD_DISABWE_MASK                                                           0x00000002W

#define UVD7_MAX_HW_INSTANCES_VEGA20			2

static void uvd_v7_0_set_wing_funcs(stwuct amdgpu_device *adev);
static void uvd_v7_0_set_enc_wing_funcs(stwuct amdgpu_device *adev);
static void uvd_v7_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static int uvd_v7_0_stawt(stwuct amdgpu_device *adev);
static void uvd_v7_0_stop(stwuct amdgpu_device *adev);
static int uvd_v7_0_swiov_stawt(stwuct amdgpu_device *adev);

static int amdgpu_ih_cwientid_uvds[] = {
	SOC15_IH_CWIENTID_UVD,
	SOC15_IH_CWIENTID_UVD1
};

/**
 * uvd_v7_0_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t uvd_v7_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(UVD, wing->me, mmUVD_WBC_WB_WPTW);
}

/**
 * uvd_v7_0_enc_wing_get_wptw - get enc wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe enc wead pointew
 */
static uint64_t uvd_v7_0_enc_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing == &adev->uvd.inst[wing->me].wing_enc[0])
		wetuwn WWEG32_SOC15(UVD, wing->me, mmUVD_WB_WPTW);
	ewse
		wetuwn WWEG32_SOC15(UVD, wing->me, mmUVD_WB_WPTW2);
}

/**
 * uvd_v7_0_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t uvd_v7_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(UVD, wing->me, mmUVD_WBC_WB_WPTW);
}

/**
 * uvd_v7_0_enc_wing_get_wptw - get enc wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe enc wwite pointew
 */
static uint64_t uvd_v7_0_enc_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww)
		wetuwn *wing->wptw_cpu_addw;

	if (wing == &adev->uvd.inst[wing->me].wing_enc[0])
		wetuwn WWEG32_SOC15(UVD, wing->me, mmUVD_WB_WPTW);
	ewse
		wetuwn WWEG32_SOC15(UVD, wing->me, mmUVD_WB_WPTW2);
}

/**
 * uvd_v7_0_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void uvd_v7_0_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	WWEG32_SOC15(UVD, wing->me, mmUVD_WBC_WB_WPTW, wowew_32_bits(wing->wptw));
}

/**
 * uvd_v7_0_enc_wing_set_wptw - set enc wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the enc wwite pointew to the hawdwawe
 */
static void uvd_v7_0_enc_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww) {
		/* XXX check if swapping is necessawy on BE */
		*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
		wetuwn;
	}

	if (wing == &adev->uvd.inst[wing->me].wing_enc[0])
		WWEG32_SOC15(UVD, wing->me, mmUVD_WB_WPTW,
			wowew_32_bits(wing->wptw));
	ewse
		WWEG32_SOC15(UVD, wing->me, mmUVD_WB_WPTW2,
			wowew_32_bits(wing->wptw));
}

/**
 * uvd_v7_0_enc_wing_test_wing - test if UVD ENC wing is wowking
 *
 * @wing: the engine to test on
 *
 */
static int uvd_v7_0_enc_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t wptw;
	unsigned i;
	int w;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	w = amdgpu_wing_awwoc(wing, 16);
	if (w)
		wetuwn w;

	wptw = amdgpu_wing_get_wptw(wing);

	amdgpu_wing_wwite(wing, HEVC_ENC_CMD_END);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (amdgpu_wing_get_wptw(wing) != wptw)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	wetuwn w;
}

/**
 * uvd_v7_0_enc_get_cweate_msg - genewate a UVD ENC cweate msg
 *
 * @wing: wing we shouwd submit the msg to
 * @handwe: session handwe to use
 * @bo: amdgpu object fow which we quewy the offset
 * @fence: optionaw fence to wetuwn
 *
 * Open up a stweam fow HW test
 */
static int uvd_v7_0_enc_get_cweate_msg(stwuct amdgpu_wing *wing, u32 handwe,
				       stwuct amdgpu_bo *bo,
				       stwuct dma_fence **fence)
{
	const unsigned ib_size_dw = 16;
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	stwuct dma_fence *f = NUWW;
	uint64_t addw;
	int i, w;

	w = amdgpu_job_awwoc_with_ib(wing->adev, NUWW, NUWW, ib_size_dw * 4,
				     AMDGPU_IB_POOW_DIWECT, &job);
	if (w)
		wetuwn w;

	ib = &job->ibs[0];
	addw = amdgpu_bo_gpu_offset(bo);

	ib->wength_dw = 0;
	ib->ptw[ib->wength_dw++] = 0x00000018;
	ib->ptw[ib->wength_dw++] = 0x00000001; /* session info */
	ib->ptw[ib->wength_dw++] = handwe;
	ib->ptw[ib->wength_dw++] = 0x00000000;
	ib->ptw[ib->wength_dw++] = uppew_32_bits(addw);
	ib->ptw[ib->wength_dw++] = addw;

	ib->ptw[ib->wength_dw++] = 0x00000014;
	ib->ptw[ib->wength_dw++] = 0x00000002; /* task info */
	ib->ptw[ib->wength_dw++] = 0x0000001c;
	ib->ptw[ib->wength_dw++] = 0x00000000;
	ib->ptw[ib->wength_dw++] = 0x00000000;

	ib->ptw[ib->wength_dw++] = 0x00000008;
	ib->ptw[ib->wength_dw++] = 0x08000001; /* op initiawize */

	fow (i = ib->wength_dw; i < ib_size_dw; ++i)
		ib->ptw[i] = 0x0;

	w = amdgpu_job_submit_diwect(job, wing, &f);
	if (w)
		goto eww;

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);
	wetuwn 0;

eww:
	amdgpu_job_fwee(job);
	wetuwn w;
}

/**
 * uvd_v7_0_enc_get_destwoy_msg - genewate a UVD ENC destwoy msg
 *
 * @wing: wing we shouwd submit the msg to
 * @handwe: session handwe to use
 * @bo: amdgpu object fow which we quewy the offset
 * @fence: optionaw fence to wetuwn
 *
 * Cwose up a stweam fow HW test ow if usewspace faiwed to do so
 */
static int uvd_v7_0_enc_get_destwoy_msg(stwuct amdgpu_wing *wing, u32 handwe,
					stwuct amdgpu_bo *bo,
					stwuct dma_fence **fence)
{
	const unsigned ib_size_dw = 16;
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	stwuct dma_fence *f = NUWW;
	uint64_t addw;
	int i, w;

	w = amdgpu_job_awwoc_with_ib(wing->adev, NUWW, NUWW, ib_size_dw * 4,
				     AMDGPU_IB_POOW_DIWECT, &job);
	if (w)
		wetuwn w;

	ib = &job->ibs[0];
	addw = amdgpu_bo_gpu_offset(bo);

	ib->wength_dw = 0;
	ib->ptw[ib->wength_dw++] = 0x00000018;
	ib->ptw[ib->wength_dw++] = 0x00000001;
	ib->ptw[ib->wength_dw++] = handwe;
	ib->ptw[ib->wength_dw++] = 0x00000000;
	ib->ptw[ib->wength_dw++] = uppew_32_bits(addw);
	ib->ptw[ib->wength_dw++] = addw;

	ib->ptw[ib->wength_dw++] = 0x00000014;
	ib->ptw[ib->wength_dw++] = 0x00000002;
	ib->ptw[ib->wength_dw++] = 0x0000001c;
	ib->ptw[ib->wength_dw++] = 0x00000000;
	ib->ptw[ib->wength_dw++] = 0x00000000;

	ib->ptw[ib->wength_dw++] = 0x00000008;
	ib->ptw[ib->wength_dw++] = 0x08000002; /* op cwose session */

	fow (i = ib->wength_dw; i < ib_size_dw; ++i)
		ib->ptw[i] = 0x0;

	w = amdgpu_job_submit_diwect(job, wing, &f);
	if (w)
		goto eww;

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);
	wetuwn 0;

eww:
	amdgpu_job_fwee(job);
	wetuwn w;
}

/**
 * uvd_v7_0_enc_wing_test_ib - test if UVD ENC IBs awe wowking
 *
 * @wing: the engine to test on
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 */
static int uvd_v7_0_enc_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct dma_fence *fence = NUWW;
	stwuct amdgpu_bo *bo = wing->adev->uvd.ib_bo;
	wong w;

	w = uvd_v7_0_enc_get_cweate_msg(wing, 1, bo, NUWW);
	if (w)
		goto ewwow;

	w = uvd_v7_0_enc_get_destwoy_msg(wing, 1, bo, &fence);
	if (w)
		goto ewwow;

	w = dma_fence_wait_timeout(fence, fawse, timeout);
	if (w == 0)
		w = -ETIMEDOUT;
	ewse if (w > 0)
		w = 0;

ewwow:
	dma_fence_put(fence);
	wetuwn w;
}

static int uvd_v7_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (adev->asic_type == CHIP_VEGA20) {
		u32 hawvest;
		int i;

		adev->uvd.num_uvd_inst = UVD7_MAX_HW_INSTANCES_VEGA20;
		fow (i = 0; i < adev->uvd.num_uvd_inst; i++) {
			hawvest = WWEG32_SOC15(UVD, i, mmUVD_PG0_CC_UVD_HAWVESTING);
			if (hawvest & UVD_PG0_CC_UVD_HAWVESTING__UVD_DISABWE_MASK) {
				adev->uvd.hawvest_config |= 1 << i;
			}
		}
		if (adev->uvd.hawvest_config == (AMDGPU_UVD_HAWVEST_UVD0 |
						 AMDGPU_UVD_HAWVEST_UVD1))
			/* both instances awe hawvested, disabwe the bwock */
			wetuwn -ENOENT;
	} ewse {
		adev->uvd.num_uvd_inst = 1;
	}

	if (amdgpu_swiov_vf(adev))
		adev->uvd.num_enc_wings = 1;
	ewse
		adev->uvd.num_enc_wings = 2;
	uvd_v7_0_set_wing_funcs(adev);
	uvd_v7_0_set_enc_wing_funcs(adev);
	uvd_v7_0_set_iwq_funcs(adev);

	wetuwn 0;
}

static int uvd_v7_0_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;

	int i, j, w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (j = 0; j < adev->uvd.num_uvd_inst; j++) {
		if (adev->uvd.hawvest_config & (1 << j))
			continue;
		/* UVD TWAP */
		w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_uvds[j], UVD_7_0__SWCID__UVD_SYSTEM_MESSAGE_INTEWWUPT, &adev->uvd.inst[j].iwq);
		if (w)
			wetuwn w;

		/* UVD ENC TWAP */
		fow (i = 0; i < adev->uvd.num_enc_wings; ++i) {
			w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_uvds[j], i + UVD_7_0__SWCID__UVD_ENC_GEN_PUWP, &adev->uvd.inst[j].iwq);
			if (w)
				wetuwn w;
		}
	}

	w = amdgpu_uvd_sw_init(adev);
	if (w)
		wetuwn w;

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		const stwuct common_fiwmwawe_headew *hdw;
		hdw = (const stwuct common_fiwmwawe_headew *)adev->uvd.fw->data;
		adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD].ucode_id = AMDGPU_UCODE_ID_UVD;
		adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD].fw = adev->uvd.fw;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(hdw->ucode_size_bytes), PAGE_SIZE);

		if (adev->uvd.num_uvd_inst == UVD7_MAX_HW_INSTANCES_VEGA20) {
			adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD1].ucode_id = AMDGPU_UCODE_ID_UVD1;
			adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD1].fw = adev->uvd.fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(we32_to_cpu(hdw->ucode_size_bytes), PAGE_SIZE);
		}
		DWM_INFO("PSP woading UVD fiwmwawe\n");
	}

	fow (j = 0; j < adev->uvd.num_uvd_inst; j++) {
		if (adev->uvd.hawvest_config & (1 << j))
			continue;
		if (!amdgpu_swiov_vf(adev)) {
			wing = &adev->uvd.inst[j].wing;
			wing->vm_hub = AMDGPU_MMHUB0(0);
			spwintf(wing->name, "uvd_%d", wing->me);
			w = amdgpu_wing_init(adev, wing, 512,
					     &adev->uvd.inst[j].iwq, 0,
					     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
			if (w)
				wetuwn w;
		}

		fow (i = 0; i < adev->uvd.num_enc_wings; ++i) {
			wing = &adev->uvd.inst[j].wing_enc[i];
			wing->vm_hub = AMDGPU_MMHUB0(0);
			spwintf(wing->name, "uvd_enc_%d.%d", wing->me, i);
			if (amdgpu_swiov_vf(adev)) {
				wing->use_doowbeww = twue;

				/* cuwwentwy onwy use the fiwst enconding wing fow
				 * swiov, so set unused wocation fow othew unused wings.
				 */
				if (i == 0)
					wing->doowbeww_index = adev->doowbeww_index.uvd_vce.uvd_wing0_1 * 2;
				ewse
					wing->doowbeww_index = adev->doowbeww_index.uvd_vce.uvd_wing2_3 * 2 + 1;
			}
			w = amdgpu_wing_init(adev, wing, 512,
					     &adev->uvd.inst[j].iwq, 0,
					     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
			if (w)
				wetuwn w;
		}
	}

	w = amdgpu_uvd_wesume(adev);
	if (w)
		wetuwn w;

	w = amdgpu_viwt_awwoc_mm_tabwe(adev);
	if (w)
		wetuwn w;

	wetuwn w;
}

static int uvd_v7_0_sw_fini(void *handwe)
{
	int i, j, w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_viwt_fwee_mm_tabwe(adev);

	w = amdgpu_uvd_suspend(adev);
	if (w)
		wetuwn w;

	fow (j = 0; j < adev->uvd.num_uvd_inst; ++j) {
		if (adev->uvd.hawvest_config & (1 << j))
			continue;
		fow (i = 0; i < adev->uvd.num_enc_wings; ++i)
			amdgpu_wing_fini(&adev->uvd.inst[j].wing_enc[i]);
	}
	wetuwn amdgpu_uvd_sw_fini(adev);
}

/**
 * uvd_v7_0_hw_init - stawt and test UVD bwock
 *
 * @handwe: handwe used to pass amdgpu_device pointew
 *
 * Initiawize the hawdwawe, boot up the VCPU and do some testing
 */
static int uvd_v7_0_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	uint32_t tmp;
	int i, j, w;

	if (amdgpu_swiov_vf(adev))
		w = uvd_v7_0_swiov_stawt(adev);
	ewse
		w = uvd_v7_0_stawt(adev);
	if (w)
		goto done;

	fow (j = 0; j < adev->uvd.num_uvd_inst; ++j) {
		if (adev->uvd.hawvest_config & (1 << j))
			continue;
		wing = &adev->uvd.inst[j].wing;

		if (!amdgpu_swiov_vf(adev)) {
			w = amdgpu_wing_test_hewpew(wing);
			if (w)
				goto done;

			w = amdgpu_wing_awwoc(wing, 10);
			if (w) {
				DWM_EWWOW("amdgpu: (%d)wing faiwed to wock UVD wing (%d).\n", j, w);
				goto done;
			}

			tmp = PACKET0(SOC15_WEG_OFFSET(UVD, j,
				mmUVD_SEMA_WAIT_FAUWT_TIMEOUT_CNTW), 0);
			amdgpu_wing_wwite(wing, tmp);
			amdgpu_wing_wwite(wing, 0xFFFFF);

			tmp = PACKET0(SOC15_WEG_OFFSET(UVD, j,
				mmUVD_SEMA_WAIT_INCOMPWETE_TIMEOUT_CNTW), 0);
			amdgpu_wing_wwite(wing, tmp);
			amdgpu_wing_wwite(wing, 0xFFFFF);

			tmp = PACKET0(SOC15_WEG_OFFSET(UVD, j,
				mmUVD_SEMA_SIGNAW_INCOMPWETE_TIMEOUT_CNTW), 0);
			amdgpu_wing_wwite(wing, tmp);
			amdgpu_wing_wwite(wing, 0xFFFFF);

			/* Cweaw timeout status bits */
			amdgpu_wing_wwite(wing, PACKET0(SOC15_WEG_OFFSET(UVD, j,
				mmUVD_SEMA_TIMEOUT_STATUS), 0));
			amdgpu_wing_wwite(wing, 0x8);

			amdgpu_wing_wwite(wing, PACKET0(SOC15_WEG_OFFSET(UVD, j,
				mmUVD_SEMA_CNTW), 0));
			amdgpu_wing_wwite(wing, 3);

			amdgpu_wing_commit(wing);
		}

		fow (i = 0; i < adev->uvd.num_enc_wings; ++i) {
			wing = &adev->uvd.inst[j].wing_enc[i];
			w = amdgpu_wing_test_hewpew(wing);
			if (w)
				goto done;
		}
	}
done:
	if (!w)
		DWM_INFO("UVD and UVD ENC initiawized successfuwwy.\n");

	wetuwn w;
}

/**
 * uvd_v7_0_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: handwe used to pass amdgpu_device pointew
 *
 * Stop the UVD bwock, mawk wing as not weady any mowe
 */
static int uvd_v7_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->uvd.idwe_wowk);

	if (!amdgpu_swiov_vf(adev))
		uvd_v7_0_stop(adev);
	ewse {
		/* fuww access mode, so don't touch any UVD wegistew */
		DWM_DEBUG("Fow SWIOV cwient, shouwdn't do anything.\n");
	}

	wetuwn 0;
}

static int uvd_v7_0_pwepawe_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn amdgpu_uvd_pwepawe_suspend(adev);
}

static int uvd_v7_0_suspend(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/*
	 * Pwopew cweanups befowe hawting the HW engine:
	 *   - cancew the dewayed idwe wowk
	 *   - enabwe powewgating
	 *   - enabwe cwockgating
	 *   - disabwe dpm
	 *
	 * TODO: to awign with the VCN impwementation, move the
	 * jobs fow cwockgating/powewgating/dpm setting to
	 * ->set_powewgating_state().
	 */
	cancew_dewayed_wowk_sync(&adev->uvd.idwe_wowk);

	if (adev->pm.dpm_enabwed) {
		amdgpu_dpm_enabwe_uvd(adev, fawse);
	} ewse {
		amdgpu_asic_set_uvd_cwocks(adev, 0, 0);
		/* shutdown the UVD bwock */
		amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_UVD,
						       AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_cwockgating_state(adev, AMD_IP_BWOCK_TYPE_UVD,
						       AMD_CG_STATE_GATE);
	}

	w = uvd_v7_0_hw_fini(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_uvd_suspend(adev);
}

static int uvd_v7_0_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_uvd_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn uvd_v7_0_hw_init(adev);
}

/**
 * uvd_v7_0_mc_wesume - memowy contwowwew pwogwamming
 *
 * @adev: amdgpu_device pointew
 *
 * Wet the UVD memowy contwowwew know it's offsets
 */
static void uvd_v7_0_mc_wesume(stwuct amdgpu_device *adev)
{
	uint32_t size = AMDGPU_UVD_FIWMWAWE_SIZE(adev);
	uint32_t offset;
	int i;

	fow (i = 0; i < adev->uvd.num_uvd_inst; ++i) {
		if (adev->uvd.hawvest_config & (1 << i))
			continue;
		if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
			WWEG32_SOC15(UVD, i, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
				i == 0 ?
				adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD].tmw_mc_addw_wo :
				adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD1].tmw_mc_addw_wo);
			WWEG32_SOC15(UVD, i, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
				i == 0 ?
				adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD].tmw_mc_addw_hi :
				adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD1].tmw_mc_addw_hi);
			WWEG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_OFFSET0, 0);
			offset = 0;
		} ewse {
			WWEG32_SOC15(UVD, i, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
				wowew_32_bits(adev->uvd.inst[i].gpu_addw));
			WWEG32_SOC15(UVD, i, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
				uppew_32_bits(adev->uvd.inst[i].gpu_addw));
			offset = size;
			WWEG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_OFFSET0,
					AMDGPU_UVD_FIWMWAWE_OFFSET >> 3);
		}

		WWEG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_SIZE0, size);

		WWEG32_SOC15(UVD, i, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW,
				wowew_32_bits(adev->uvd.inst[i].gpu_addw + offset));
		WWEG32_SOC15(UVD, i, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH,
				uppew_32_bits(adev->uvd.inst[i].gpu_addw + offset));
		WWEG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_OFFSET1, (1 << 21));
		WWEG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_UVD_HEAP_SIZE);

		WWEG32_SOC15(UVD, i, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW,
				wowew_32_bits(adev->uvd.inst[i].gpu_addw + offset + AMDGPU_UVD_HEAP_SIZE));
		WWEG32_SOC15(UVD, i, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH,
				uppew_32_bits(adev->uvd.inst[i].gpu_addw + offset + AMDGPU_UVD_HEAP_SIZE));
		WWEG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_OFFSET2, (2 << 21));
		WWEG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_SIZE2,
				AMDGPU_UVD_STACK_SIZE + (AMDGPU_UVD_SESSION_SIZE * 40));

		WWEG32_SOC15(UVD, i, mmUVD_UDEC_ADDW_CONFIG,
				adev->gfx.config.gb_addw_config);
		WWEG32_SOC15(UVD, i, mmUVD_UDEC_DB_ADDW_CONFIG,
				adev->gfx.config.gb_addw_config);
		WWEG32_SOC15(UVD, i, mmUVD_UDEC_DBW_ADDW_CONFIG,
				adev->gfx.config.gb_addw_config);

		WWEG32_SOC15(UVD, i, mmUVD_GP_SCWATCH4, adev->uvd.max_handwes);
	}
}

static int uvd_v7_0_mmsch_stawt(stwuct amdgpu_device *adev,
				stwuct amdgpu_mm_tabwe *tabwe)
{
	uint32_t data = 0, woop;
	uint64_t addw = tabwe->gpu_addw;
	stwuct mmsch_v1_0_init_headew *headew = (stwuct mmsch_v1_0_init_headew *)tabwe->cpu_addw;
	uint32_t size;
	int i;

	size = headew->headew_size + headew->vce_tabwe_size + headew->uvd_tabwe_size;

	/* 1, wwite to vce_mmsch_vf_ctx_addw_wo/hi wegistew with GPU mc addw of memowy descwiptow wocation */
	WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDW_WO, wowew_32_bits(addw));
	WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDW_HI, uppew_32_bits(addw));

	/* 2, update vmid of descwiptow */
	data = WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_VMID);
	data &= ~VCE_MMSCH_VF_VMID__VF_CTX_VMID_MASK;
	data |= (0 << VCE_MMSCH_VF_VMID__VF_CTX_VMID__SHIFT); /* use domain0 fow MM scheduwew */
	WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_VMID, data);

	/* 3, notify mmsch about the size of this descwiptow */
	WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_CTX_SIZE, size);

	/* 4, set wesp to zewo */
	WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_MAIWBOX_WESP, 0);

	fow (i = 0; i < adev->uvd.num_uvd_inst; ++i) {
		if (adev->uvd.hawvest_config & (1 << i))
			continue;
		WDOOWBEWW32(adev->uvd.inst[i].wing_enc[0].doowbeww_index, 0);
		*adev->uvd.inst[i].wing_enc[0].wptw_cpu_addw = 0;
		adev->uvd.inst[i].wing_enc[0].wptw = 0;
		adev->uvd.inst[i].wing_enc[0].wptw_owd = 0;
	}
	/* 5, kick off the initiawization and wait untiw VCE_MMSCH_VF_MAIWBOX_WESP becomes non-zewo */
	WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_MAIWBOX_HOST, 0x10000001);

	data = WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_MAIWBOX_WESP);
	woop = 1000;
	whiwe ((data & 0x10000002) != 0x10000002) {
		udeway(10);
		data = WWEG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_MAIWBOX_WESP);
		woop--;
		if (!woop)
			bweak;
	}

	if (!woop) {
		dev_eww(adev->dev, "faiwed to init MMSCH, mmVCE_MMSCH_VF_MAIWBOX_WESP = %x\n", data);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int uvd_v7_0_swiov_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	uint32_t offset, size, tmp;
	uint32_t tabwe_size = 0;
	stwuct mmsch_v1_0_cmd_diwect_wwite diwect_wt = { {0} };
	stwuct mmsch_v1_0_cmd_diwect_wead_modify_wwite diwect_wd_mod_wt = { {0} };
	stwuct mmsch_v1_0_cmd_diwect_powwing diwect_poww = { {0} };
	stwuct mmsch_v1_0_cmd_end end = { {0} };
	uint32_t *init_tabwe = adev->viwt.mm_tabwe.cpu_addw;
	stwuct mmsch_v1_0_init_headew *headew = (stwuct mmsch_v1_0_init_headew *)init_tabwe;
	uint8_t i = 0;

	diwect_wt.cmd_headew.command_type = MMSCH_COMMAND__DIWECT_WEG_WWITE;
	diwect_wd_mod_wt.cmd_headew.command_type = MMSCH_COMMAND__DIWECT_WEG_WEAD_MODIFY_WWITE;
	diwect_poww.cmd_headew.command_type = MMSCH_COMMAND__DIWECT_WEG_POWWING;
	end.cmd_headew.command_type = MMSCH_COMMAND__END;

	if (headew->uvd_tabwe_offset == 0 && headew->uvd_tabwe_size == 0) {
		headew->vewsion = MMSCH_VEWSION;
		headew->headew_size = sizeof(stwuct mmsch_v1_0_init_headew) >> 2;

		if (headew->vce_tabwe_offset == 0 && headew->vce_tabwe_size == 0)
			headew->uvd_tabwe_offset = headew->headew_size;
		ewse
			headew->uvd_tabwe_offset = headew->vce_tabwe_size + headew->vce_tabwe_offset;

		init_tabwe += headew->uvd_tabwe_offset;

		fow (i = 0; i < adev->uvd.num_uvd_inst; ++i) {
			if (adev->uvd.hawvest_config & (1 << i))
				continue;
			wing = &adev->uvd.inst[i].wing;
			wing->wptw = 0;
			size = AMDGPU_GPU_PAGE_AWIGN(adev->uvd.fw->size + 4);

			MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_STATUS),
							   0xFFFFFFFF, 0x00000004);
			/* mc wesume*/
			if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
				MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i,
							mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
							adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD].tmw_mc_addw_wo);
				MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i,
							mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
							adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UVD].tmw_mc_addw_hi);
				MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0), 0);
				offset = 0;
			} ewse {
				MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
							    wowew_32_bits(adev->uvd.inst[i].gpu_addw));
				MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
							    uppew_32_bits(adev->uvd.inst[i].gpu_addw));
				offset = size;
				MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0),
							AMDGPU_UVD_FIWMWAWE_OFFSET >> 3);

			}

			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE0), size);

			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW),
						    wowew_32_bits(adev->uvd.inst[i].gpu_addw + offset));
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH),
						    uppew_32_bits(adev->uvd.inst[i].gpu_addw + offset));
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_OFFSET1), (1 << 21));
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE1), AMDGPU_UVD_HEAP_SIZE);

			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW),
						    wowew_32_bits(adev->uvd.inst[i].gpu_addw + offset + AMDGPU_UVD_HEAP_SIZE));
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH),
						    uppew_32_bits(adev->uvd.inst[i].gpu_addw + offset + AMDGPU_UVD_HEAP_SIZE));
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_OFFSET2), (2 << 21));
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE2),
						    AMDGPU_UVD_STACK_SIZE + (AMDGPU_UVD_SESSION_SIZE * 40));

			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_GP_SCWATCH4), adev->uvd.max_handwes);
			/* mc wesume end*/

			/* disabwe cwock gating */
			MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_CGC_CTWW),
							   ~UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK, 0);

			/* disabwe intewupt */
			MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_MASTINT_EN),
							   ~UVD_MASTINT_EN__VCPU_EN_MASK, 0);

			/* staww UMC and wegistew bus befowe wesetting VCPU */
			MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_CTWW2),
							   ~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK,
							   UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);

			/* put WMI, VCPU, WBC etc... into weset */
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_SOFT_WESET),
						    (uint32_t)(UVD_SOFT_WESET__WMI_SOFT_WESET_MASK |
							       UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK |
							       UVD_SOFT_WESET__WBSI_SOFT_WESET_MASK |
							       UVD_SOFT_WESET__WBC_SOFT_WESET_MASK |
							       UVD_SOFT_WESET__CSM_SOFT_WESET_MASK |
							       UVD_SOFT_WESET__CXW_SOFT_WESET_MASK |
							       UVD_SOFT_WESET__TAP_SOFT_WESET_MASK |
							       UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK));

			/* initiawize UVD memowy contwowwew */
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_CTWW),
						    (uint32_t)((0x40 << UVD_WMI_CTWW__WWITE_CWEAN_TIMEW__SHIFT) |
							       UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK |
							       UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
							       UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK |
							       UVD_WMI_CTWW__WEQ_MODE_MASK |
							       0x00100000W));

			/* take aww subbwocks out of weset, except VCPU */
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_SOFT_WESET),
						    UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);

			/* enabwe VCPU cwock */
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_VCPU_CNTW),
						    UVD_VCPU_CNTW__CWK_EN_MASK);

			/* enabwe mastew intewwupt */
			MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_MASTINT_EN),
							   ~(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK),
							   (UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK));

			/* cweaw the bit 4 of UVD_STATUS */
			MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_STATUS),
							   ~(2 << UVD_STATUS__VCPU_WEPOWT__SHIFT), 0);

			/* fowce WBC into idwe state */
			size = owdew_base_2(wing->wing_size);
			tmp = WEG_SET_FIEWD(0, UVD_WBC_WB_CNTW, WB_BUFSZ, size);
			tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_FETCH, 1);
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WBC_WB_CNTW), tmp);

			wing = &adev->uvd.inst[i].wing_enc[0];
			wing->wptw = 0;
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WB_BASE_WO), wing->gpu_addw);
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WB_BASE_HI), uppew_32_bits(wing->gpu_addw));
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WB_SIZE), wing->wing_size / 4);

			/* boot up the VCPU */
			MMSCH_V1_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_SOFT_WESET), 0);

			/* enabwe UMC */
			MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_CTWW2),
											   ~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK, 0);

			MMSCH_V1_0_INSEWT_DIWECT_POWW(SOC15_WEG_OFFSET(UVD, i, mmUVD_STATUS), 0x02, 0x02);
		}
		/* add end packet */
		memcpy((void *)init_tabwe, &end, sizeof(stwuct mmsch_v1_0_cmd_end));
		tabwe_size += sizeof(stwuct mmsch_v1_0_cmd_end) / 4;
		headew->uvd_tabwe_size = tabwe_size;

	}
	wetuwn uvd_v7_0_mmsch_stawt(adev, &adev->viwt.mm_tabwe);
}

/**
 * uvd_v7_0_stawt - stawt UVD bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the UVD bwock
 */
static int uvd_v7_0_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	uint32_t wb_bufsz, tmp;
	uint32_t wmi_swap_cntw;
	uint32_t mp_swap_cntw;
	int i, j, k, w;

	fow (k = 0; k < adev->uvd.num_uvd_inst; ++k) {
		if (adev->uvd.hawvest_config & (1 << k))
			continue;
		/* disabwe DPG */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_POWEW_STATUS), 0,
				~UVD_POWEW_STATUS__UVD_PG_MODE_MASK);
	}

	/* disabwe byte swapping */
	wmi_swap_cntw = 0;
	mp_swap_cntw = 0;

	uvd_v7_0_mc_wesume(adev);

	fow (k = 0; k < adev->uvd.num_uvd_inst; ++k) {
		if (adev->uvd.hawvest_config & (1 << k))
			continue;
		wing = &adev->uvd.inst[k].wing;
		/* disabwe cwock gating */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_CGC_CTWW), 0,
				~UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK);

		/* disabwe intewupt */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_MASTINT_EN), 0,
				~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* staww UMC and wegistew bus befowe wesetting VCPU */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_WMI_CTWW2),
				UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK,
				~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);
		mdeway(1);

		/* put WMI, VCPU, WBC etc... into weset */
		WWEG32_SOC15(UVD, k, mmUVD_SOFT_WESET,
			UVD_SOFT_WESET__WMI_SOFT_WESET_MASK |
			UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK |
			UVD_SOFT_WESET__WBSI_SOFT_WESET_MASK |
			UVD_SOFT_WESET__WBC_SOFT_WESET_MASK |
			UVD_SOFT_WESET__CSM_SOFT_WESET_MASK |
			UVD_SOFT_WESET__CXW_SOFT_WESET_MASK |
			UVD_SOFT_WESET__TAP_SOFT_WESET_MASK |
			UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK);
		mdeway(5);

		/* initiawize UVD memowy contwowwew */
		WWEG32_SOC15(UVD, k, mmUVD_WMI_CTWW,
			(0x40 << UVD_WMI_CTWW__WWITE_CWEAN_TIMEW__SHIFT) |
			UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK |
			UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
			UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK |
			UVD_WMI_CTWW__WEQ_MODE_MASK |
			0x00100000W);

#ifdef __BIG_ENDIAN
		/* swap (8 in 32) WB and IB */
		wmi_swap_cntw = 0xa;
		mp_swap_cntw = 0;
#endif
		WWEG32_SOC15(UVD, k, mmUVD_WMI_SWAP_CNTW, wmi_swap_cntw);
		WWEG32_SOC15(UVD, k, mmUVD_MP_SWAP_CNTW, mp_swap_cntw);

		WWEG32_SOC15(UVD, k, mmUVD_MPC_SET_MUXA0, 0x40c2040);
		WWEG32_SOC15(UVD, k, mmUVD_MPC_SET_MUXA1, 0x0);
		WWEG32_SOC15(UVD, k, mmUVD_MPC_SET_MUXB0, 0x40c2040);
		WWEG32_SOC15(UVD, k, mmUVD_MPC_SET_MUXB1, 0x0);
		WWEG32_SOC15(UVD, k, mmUVD_MPC_SET_AWU, 0);
		WWEG32_SOC15(UVD, k, mmUVD_MPC_SET_MUX, 0x88);

		/* take aww subbwocks out of weset, except VCPU */
		WWEG32_SOC15(UVD, k, mmUVD_SOFT_WESET,
				UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
		mdeway(5);

		/* enabwe VCPU cwock */
		WWEG32_SOC15(UVD, k, mmUVD_VCPU_CNTW,
				UVD_VCPU_CNTW__CWK_EN_MASK);

		/* enabwe UMC */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_WMI_CTWW2), 0,
				~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);

		/* boot up the VCPU */
		WWEG32_SOC15(UVD, k, mmUVD_SOFT_WESET, 0);
		mdeway(10);

		fow (i = 0; i < 10; ++i) {
			uint32_t status;

			fow (j = 0; j < 100; ++j) {
				status = WWEG32_SOC15(UVD, k, mmUVD_STATUS);
				if (status & 2)
					bweak;
				mdeway(10);
			}
			w = 0;
			if (status & 2)
				bweak;

			DWM_EWWOW("UVD(%d) not wesponding, twying to weset the VCPU!!!\n", k);
			WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_SOFT_WESET),
					UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK,
					~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
			mdeway(10);
			WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_SOFT_WESET), 0,
					~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
			mdeway(10);
			w = -1;
		}

		if (w) {
			DWM_EWWOW("UVD(%d) not wesponding, giving up!!!\n", k);
			wetuwn w;
		}
		/* enabwe mastew intewwupt */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_MASTINT_EN),
			(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK),
			~(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK));

		/* cweaw the bit 4 of UVD_STATUS */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_STATUS), 0,
				~(2 << UVD_STATUS__VCPU_WEPOWT__SHIFT));

		/* fowce WBC into idwe state */
		wb_bufsz = owdew_base_2(wing->wing_size);
		tmp = WEG_SET_FIEWD(0, UVD_WBC_WB_CNTW, WB_BUFSZ, wb_bufsz);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_BWKSZ, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_FETCH, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_POWW_EN, 0);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_UPDATE, 1);
		tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_WW_EN, 1);
		WWEG32_SOC15(UVD, k, mmUVD_WBC_WB_CNTW, tmp);

		/* set the wwite pointew deway */
		WWEG32_SOC15(UVD, k, mmUVD_WBC_WB_WPTW_CNTW, 0);

		/* set the wb addwess */
		WWEG32_SOC15(UVD, k, mmUVD_WBC_WB_WPTW_ADDW,
				(uppew_32_bits(wing->gpu_addw) >> 2));

		/* pwogwam the WB_BASE fow wing buffew */
		WWEG32_SOC15(UVD, k, mmUVD_WMI_WBC_WB_64BIT_BAW_WOW,
				wowew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(UVD, k, mmUVD_WMI_WBC_WB_64BIT_BAW_HIGH,
				uppew_32_bits(wing->gpu_addw));

		/* Initiawize the wing buffew's wead and wwite pointews */
		WWEG32_SOC15(UVD, k, mmUVD_WBC_WB_WPTW, 0);

		wing->wptw = WWEG32_SOC15(UVD, k, mmUVD_WBC_WB_WPTW);
		WWEG32_SOC15(UVD, k, mmUVD_WBC_WB_WPTW,
				wowew_32_bits(wing->wptw));

		WWEG32_P(SOC15_WEG_OFFSET(UVD, k, mmUVD_WBC_WB_CNTW), 0,
				~UVD_WBC_WB_CNTW__WB_NO_FETCH_MASK);

		wing = &adev->uvd.inst[k].wing_enc[0];
		WWEG32_SOC15(UVD, k, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
		WWEG32_SOC15(UVD, k, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
		WWEG32_SOC15(UVD, k, mmUVD_WB_BASE_WO, wing->gpu_addw);
		WWEG32_SOC15(UVD, k, mmUVD_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(UVD, k, mmUVD_WB_SIZE, wing->wing_size / 4);

		wing = &adev->uvd.inst[k].wing_enc[1];
		WWEG32_SOC15(UVD, k, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
		WWEG32_SOC15(UVD, k, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
		WWEG32_SOC15(UVD, k, mmUVD_WB_BASE_WO2, wing->gpu_addw);
		WWEG32_SOC15(UVD, k, mmUVD_WB_BASE_HI2, uppew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(UVD, k, mmUVD_WB_SIZE2, wing->wing_size / 4);
	}
	wetuwn 0;
}

/**
 * uvd_v7_0_stop - stop UVD bwock
 *
 * @adev: amdgpu_device pointew
 *
 * stop the UVD bwock
 */
static void uvd_v7_0_stop(stwuct amdgpu_device *adev)
{
	uint8_t i = 0;

	fow (i = 0; i < adev->uvd.num_uvd_inst; ++i) {
		if (adev->uvd.hawvest_config & (1 << i))
			continue;
		/* fowce WBC into idwe state */
		WWEG32_SOC15(UVD, i, mmUVD_WBC_WB_CNTW, 0x11010101);

		/* Staww UMC and wegistew bus befowe wesetting VCPU */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_CTWW2),
				UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK,
				~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);
		mdeway(1);

		/* put VCPU into weset */
		WWEG32_SOC15(UVD, i, mmUVD_SOFT_WESET,
				UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
		mdeway(5);

		/* disabwe VCPU cwock */
		WWEG32_SOC15(UVD, i, mmUVD_VCPU_CNTW, 0x0);

		/* Unstaww UMC and wegistew bus */
		WWEG32_P(SOC15_WEG_OFFSET(UVD, i, mmUVD_WMI_CTWW2), 0,
				~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);
	}
}

/**
 * uvd_v7_0_wing_emit_fence - emit an fence & twap command
 *
 * @wing: amdgpu_wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Wwite a fence and a twap command to the wing.
 */
static void uvd_v7_0_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				     unsigned fwags)
{
	stwuct amdgpu_device *adev = wing->adev;

	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_CONTEXT_ID), 0));
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, addw & 0xffffffff);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw) & 0xff);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, 0);

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, 2);
}

/**
 * uvd_v7_0_enc_wing_emit_fence - emit an enc fence & twap command
 *
 * @wing: amdgpu_wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Wwite enc a fence and a twap command to the wing.
 */
static void uvd_v7_0_enc_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw,
			u64 seq, unsigned fwags)
{

	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing, HEVC_ENC_CMD_FENCE);
	amdgpu_wing_wwite(wing, addw);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing, HEVC_ENC_CMD_TWAP);
}

/**
 * uvd_v7_0_wing_emit_hdp_fwush - skip HDP fwushing
 *
 * @wing: amdgpu_wing pointew
 */
static void uvd_v7_0_wing_emit_hdp_fwush(stwuct amdgpu_wing *wing)
{
	/* The fiwmwawe doesn't seem to wike touching wegistews at this point. */
}

/**
 * uvd_v7_0_wing_test_wing - wegistew wwite test
 *
 * @wing: amdgpu_wing pointew
 *
 * Test if we can successfuwwy wwite to the context wegistew
 */
static int uvd_v7_0_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t tmp = 0;
	unsigned i;
	int w;

	WWEG32_SOC15(UVD, wing->me, mmUVD_CONTEXT_ID, 0xCAFEDEAD);
	w = amdgpu_wing_awwoc(wing, 3);
	if (w)
		wetuwn w;

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_CONTEXT_ID), 0));
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);
	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = WWEG32_SOC15(UVD, wing->me, mmUVD_CONTEXT_ID);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	wetuwn w;
}

/**
 * uvd_v7_0_wing_patch_cs_in_pwace - Patch the IB fow command submission.
 *
 * @p: the CS pawsew with the IBs
 * @job: which job this ib is in
 * @ib: which IB to patch
 *
 */
static int uvd_v7_0_wing_patch_cs_in_pwace(stwuct amdgpu_cs_pawsew *p,
					   stwuct amdgpu_job *job,
					   stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_wing *wing = to_amdgpu_wing(job->base.sched);
	unsigned i;

	/* No patching necessawy fow the fiwst instance */
	if (!wing->me)
		wetuwn 0;

	fow (i = 0; i < ib->wength_dw; i += 2) {
		uint32_t weg = amdgpu_ib_get_vawue(ib, i);

		weg -= p->adev->weg_offset[UVD_HWIP][0][1];
		weg += p->adev->weg_offset[UVD_HWIP][1][1];

		amdgpu_ib_set_vawue(ib, i, weg);
	}
	wetuwn 0;
}

/**
 * uvd_v7_0_wing_emit_ib - execute indiwect buffew
 *
 * @wing: amdgpu_wing pointew
 * @job: job to wetwieve vmid fwom
 * @ib: indiwect buffew to execute
 * @fwags: unused
 *
 * Wwite wing commands to execute the indiwect buffew
 */
static void uvd_v7_0_wing_emit_ib(stwuct amdgpu_wing *wing,
				  stwuct amdgpu_job *job,
				  stwuct amdgpu_ib *ib,
				  uint32_t fwags)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_WMI_WBC_IB_VMID), 0));
	amdgpu_wing_wwite(wing, vmid);

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_WMI_WBC_IB_64BIT_BAW_WOW), 0));
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_WMI_WBC_IB_64BIT_BAW_HIGH), 0));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_WBC_IB_SIZE), 0));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

/**
 * uvd_v7_0_enc_wing_emit_ib - enc execute indiwect buffew
 *
 * @wing: amdgpu_wing pointew
 * @job: job to wetwive vmid fwom
 * @ib: indiwect buffew to execute
 * @fwags: unused
 *
 * Wwite enc wing commands to execute the indiwect buffew
 */
static void uvd_v7_0_enc_wing_emit_ib(stwuct amdgpu_wing *wing,
					stwuct amdgpu_job *job,
					stwuct amdgpu_ib *ib,
					uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing, HEVC_ENC_CMD_IB_VM);
	amdgpu_wing_wwite(wing, vmid);
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

static void uvd_v7_0_wing_emit_wweg(stwuct amdgpu_wing *wing,
				    uint32_t weg, uint32_t vaw)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, weg << 2);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_wing_wwite(wing, vaw);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, 8);
}

static void uvd_v7_0_wing_emit_weg_wait(stwuct amdgpu_wing *wing, uint32_t weg,
					uint32_t vaw, uint32_t mask)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, weg << 2);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_wing_wwite(wing, vaw);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GP_SCWATCH8), 0));
	amdgpu_wing_wwite(wing, mask);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, 12);
}

static void uvd_v7_0_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					unsigned vmid, uint64_t pd_addw)
{
	stwuct amdgpu_vmhub *hub = &wing->adev->vmhub[wing->vm_hub];
	uint32_t data0, data1, mask;

	pd_addw = amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow weg wwites */
	data0 = hub->ctx0_ptb_addw_wo32 + vmid * hub->ctx_addw_distance;
	data1 = wowew_32_bits(pd_addw);
	mask = 0xffffffff;
	uvd_v7_0_wing_emit_weg_wait(wing, data0, data1, mask);
}

static void uvd_v7_0_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count)
{
	stwuct amdgpu_device *adev = wing->adev;
	int i;

	WAWN_ON(wing->wptw % 2 || count % 2);

	fow (i = 0; i < count / 2; i++) {
		amdgpu_wing_wwite(wing, PACKET0(SOC15_WEG_OFFSET(UVD, wing->me, mmUVD_NO_OP), 0));
		amdgpu_wing_wwite(wing, 0);
	}
}

static void uvd_v7_0_enc_wing_insewt_end(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, HEVC_ENC_CMD_END);
}

static void uvd_v7_0_enc_wing_emit_weg_wait(stwuct amdgpu_wing *wing,
					    uint32_t weg, uint32_t vaw,
					    uint32_t mask)
{
	amdgpu_wing_wwite(wing, HEVC_ENC_CMD_WEG_WAIT);
	amdgpu_wing_wwite(wing,	weg << 2);
	amdgpu_wing_wwite(wing, mask);
	amdgpu_wing_wwite(wing, vaw);
}

static void uvd_v7_0_enc_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					    unsigned int vmid, uint64_t pd_addw)
{
	stwuct amdgpu_vmhub *hub = &wing->adev->vmhub[wing->vm_hub];

	pd_addw = amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow weg wwites */
	uvd_v7_0_enc_wing_emit_weg_wait(wing, hub->ctx0_ptb_addw_wo32 +
					vmid * hub->ctx_addw_distance,
					wowew_32_bits(pd_addw), 0xffffffff);
}

static void uvd_v7_0_enc_wing_emit_wweg(stwuct amdgpu_wing *wing,
					uint32_t weg, uint32_t vaw)
{
	amdgpu_wing_wwite(wing, HEVC_ENC_CMD_WEG_WWITE);
	amdgpu_wing_wwite(wing,	weg << 2);
	amdgpu_wing_wwite(wing, vaw);
}

#if 0
static boow uvd_v7_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn !(WWEG32(mmSWBM_STATUS) & SWBM_STATUS__UVD_BUSY_MASK);
}

static int uvd_v7_0_wait_fow_idwe(void *handwe)
{
	unsigned i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (uvd_v7_0_is_idwe(handwe))
			wetuwn 0;
	}
	wetuwn -ETIMEDOUT;
}

#define AMDGPU_UVD_STATUS_BUSY_MASK    0xfd
static boow uvd_v7_0_check_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 swbm_soft_weset = 0;
	u32 tmp = WWEG32(mmSWBM_STATUS);

	if (WEG_GET_FIEWD(tmp, SWBM_STATUS, UVD_WQ_PENDING) ||
	    WEG_GET_FIEWD(tmp, SWBM_STATUS, UVD_BUSY) ||
	    (WWEG32_SOC15(UVD, wing->me, mmUVD_STATUS) &
		    AMDGPU_UVD_STATUS_BUSY_MASK))
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset,
				SWBM_SOFT_WESET, SOFT_WESET_UVD, 1);

	if (swbm_soft_weset) {
		adev->uvd.inst[wing->me].swbm_soft_weset = swbm_soft_weset;
		wetuwn twue;
	} ewse {
		adev->uvd.inst[wing->me].swbm_soft_weset = 0;
		wetuwn fawse;
	}
}

static int uvd_v7_0_pwe_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->uvd.inst[wing->me].swbm_soft_weset)
		wetuwn 0;

	uvd_v7_0_stop(adev);
	wetuwn 0;
}

static int uvd_v7_0_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 swbm_soft_weset;

	if (!adev->uvd.inst[wing->me].swbm_soft_weset)
		wetuwn 0;
	swbm_soft_weset = adev->uvd.inst[wing->me].swbm_soft_weset;

	if (swbm_soft_weset) {
		u32 tmp;

		tmp = WWEG32(mmSWBM_SOFT_WESET);
		tmp |= swbm_soft_weset;
		dev_info(adev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~swbm_soft_weset;
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		/* Wait a wittwe fow things to settwe down */
		udeway(50);
	}

	wetuwn 0;
}

static int uvd_v7_0_post_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->uvd.inst[wing->me].swbm_soft_weset)
		wetuwn 0;

	mdeway(5);

	wetuwn uvd_v7_0_stawt(adev);
}
#endif

static int uvd_v7_0_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	// TODO
	wetuwn 0;
}

static int uvd_v7_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t ip_instance;

	switch (entwy->cwient_id) {
	case SOC15_IH_CWIENTID_UVD:
		ip_instance = 0;
		bweak;
	case SOC15_IH_CWIENTID_UVD1:
		ip_instance = 1;
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed cwient id: %d\n", entwy->cwient_id);
		wetuwn 0;
	}

	DWM_DEBUG("IH: UVD TWAP\n");

	switch (entwy->swc_id) {
	case 124:
		amdgpu_fence_pwocess(&adev->uvd.inst[ip_instance].wing);
		bweak;
	case 119:
		amdgpu_fence_pwocess(&adev->uvd.inst[ip_instance].wing_enc[0]);
		bweak;
	case 120:
		if (!amdgpu_swiov_vf(adev))
			amdgpu_fence_pwocess(&adev->uvd.inst[ip_instance].wing_enc[1]);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

#if 0
static void uvd_v7_0_set_sw_cwock_gating(stwuct amdgpu_device *adev)
{
	uint32_t data, data1, data2, suvd_fwags;

	data = WWEG32_SOC15(UVD, wing->me, mmUVD_CGC_CTWW);
	data1 = WWEG32_SOC15(UVD, wing->me, mmUVD_SUVD_CGC_GATE);
	data2 = WWEG32_SOC15(UVD, wing->me, mmUVD_SUVD_CGC_CTWW);

	data &= ~(UVD_CGC_CTWW__CWK_OFF_DEWAY_MASK |
		  UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW_MASK);

	suvd_fwags = UVD_SUVD_CGC_GATE__SWE_MASK |
		     UVD_SUVD_CGC_GATE__SIT_MASK |
		     UVD_SUVD_CGC_GATE__SMP_MASK |
		     UVD_SUVD_CGC_GATE__SCM_MASK |
		     UVD_SUVD_CGC_GATE__SDB_MASK;

	data |= UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK |
		(1 << WEG_FIEWD_SHIFT(UVD_CGC_CTWW, CWK_GATE_DWY_TIMEW)) |
		(4 << WEG_FIEWD_SHIFT(UVD_CGC_CTWW, CWK_OFF_DEWAY));

	data &= ~(UVD_CGC_CTWW__UDEC_WE_MODE_MASK |
			UVD_CGC_CTWW__UDEC_CM_MODE_MASK |
			UVD_CGC_CTWW__UDEC_IT_MODE_MASK |
			UVD_CGC_CTWW__UDEC_DB_MODE_MASK |
			UVD_CGC_CTWW__UDEC_MP_MODE_MASK |
			UVD_CGC_CTWW__SYS_MODE_MASK |
			UVD_CGC_CTWW__UDEC_MODE_MASK |
			UVD_CGC_CTWW__MPEG2_MODE_MASK |
			UVD_CGC_CTWW__WEGS_MODE_MASK |
			UVD_CGC_CTWW__WBC_MODE_MASK |
			UVD_CGC_CTWW__WMI_MC_MODE_MASK |
			UVD_CGC_CTWW__WMI_UMC_MODE_MASK |
			UVD_CGC_CTWW__IDCT_MODE_MASK |
			UVD_CGC_CTWW__MPWD_MODE_MASK |
			UVD_CGC_CTWW__MPC_MODE_MASK |
			UVD_CGC_CTWW__WBSI_MODE_MASK |
			UVD_CGC_CTWW__WWBBM_MODE_MASK |
			UVD_CGC_CTWW__WCB_MODE_MASK |
			UVD_CGC_CTWW__VCPU_MODE_MASK |
			UVD_CGC_CTWW__JPEG_MODE_MASK |
			UVD_CGC_CTWW__JPEG2_MODE_MASK |
			UVD_CGC_CTWW__SCPU_MODE_MASK);
	data2 &= ~(UVD_SUVD_CGC_CTWW__SWE_MODE_MASK |
			UVD_SUVD_CGC_CTWW__SIT_MODE_MASK |
			UVD_SUVD_CGC_CTWW__SMP_MODE_MASK |
			UVD_SUVD_CGC_CTWW__SCM_MODE_MASK |
			UVD_SUVD_CGC_CTWW__SDB_MODE_MASK);
	data1 |= suvd_fwags;

	WWEG32_SOC15(UVD, wing->me, mmUVD_CGC_CTWW, data);
	WWEG32_SOC15(UVD, wing->me, mmUVD_CGC_GATE, 0);
	WWEG32_SOC15(UVD, wing->me, mmUVD_SUVD_CGC_GATE, data1);
	WWEG32_SOC15(UVD, wing->me, mmUVD_SUVD_CGC_CTWW, data2);
}

static void uvd_v7_0_set_hw_cwock_gating(stwuct amdgpu_device *adev)
{
	uint32_t data, data1, cgc_fwags, suvd_fwags;

	data = WWEG32_SOC15(UVD, wing->me, mmUVD_CGC_GATE);
	data1 = WWEG32_SOC15(UVD, wing->me, mmUVD_SUVD_CGC_GATE);

	cgc_fwags = UVD_CGC_GATE__SYS_MASK |
		UVD_CGC_GATE__UDEC_MASK |
		UVD_CGC_GATE__MPEG2_MASK |
		UVD_CGC_GATE__WBC_MASK |
		UVD_CGC_GATE__WMI_MC_MASK |
		UVD_CGC_GATE__IDCT_MASK |
		UVD_CGC_GATE__MPWD_MASK |
		UVD_CGC_GATE__MPC_MASK |
		UVD_CGC_GATE__WBSI_MASK |
		UVD_CGC_GATE__WWBBM_MASK |
		UVD_CGC_GATE__UDEC_WE_MASK |
		UVD_CGC_GATE__UDEC_CM_MASK |
		UVD_CGC_GATE__UDEC_IT_MASK |
		UVD_CGC_GATE__UDEC_DB_MASK |
		UVD_CGC_GATE__UDEC_MP_MASK |
		UVD_CGC_GATE__WCB_MASK |
		UVD_CGC_GATE__VCPU_MASK |
		UVD_CGC_GATE__SCPU_MASK |
		UVD_CGC_GATE__JPEG_MASK |
		UVD_CGC_GATE__JPEG2_MASK;

	suvd_fwags = UVD_SUVD_CGC_GATE__SWE_MASK |
				UVD_SUVD_CGC_GATE__SIT_MASK |
				UVD_SUVD_CGC_GATE__SMP_MASK |
				UVD_SUVD_CGC_GATE__SCM_MASK |
				UVD_SUVD_CGC_GATE__SDB_MASK;

	data |= cgc_fwags;
	data1 |= suvd_fwags;

	WWEG32_SOC15(UVD, wing->me, mmUVD_CGC_GATE, data);
	WWEG32_SOC15(UVD, wing->me, mmUVD_SUVD_CGC_GATE, data1);
}

static void uvd_v7_0_set_bypass_mode(stwuct amdgpu_device *adev, boow enabwe)
{
	u32 tmp = WWEG32_SMC(ixGCK_DFS_BYPASS_CNTW);

	if (enabwe)
		tmp |= (GCK_DFS_BYPASS_CNTW__BYPASSDCWK_MASK |
			GCK_DFS_BYPASS_CNTW__BYPASSVCWK_MASK);
	ewse
		tmp &= ~(GCK_DFS_BYPASS_CNTW__BYPASSDCWK_MASK |
			 GCK_DFS_BYPASS_CNTW__BYPASSVCWK_MASK);

	WWEG32_SMC(ixGCK_DFS_BYPASS_CNTW, tmp);
}


static int uvd_v7_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_CG_STATE_GATE);

	uvd_v7_0_set_bypass_mode(adev, enabwe);

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_UVD_MGCG))
		wetuwn 0;

	if (enabwe) {
		/* disabwe HW gating and enabwe Sw gating */
		uvd_v7_0_set_sw_cwock_gating(adev);
	} ewse {
		/* wait fow STATUS to cweaw */
		if (uvd_v7_0_wait_fow_idwe(handwe))
			wetuwn -EBUSY;

		/* enabwe HW gates because UVD is idwe */
		/* uvd_v7_0_set_hw_cwock_gating(adev); */
	}

	wetuwn 0;
}

static int uvd_v7_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	/* This doesn't actuawwy powewgate the UVD bwock.
	 * That's done in the dpm code via the SMC.  This
	 * just we-inits the bwock as necessawy.  The actuaw
	 * gating stiww happens in the dpm code.  We shouwd
	 * wevisit this when thewe is a cweanew wine between
	 * the smc and the hw bwocks
	 */
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!(adev->pg_fwags & AMD_PG_SUPPOWT_UVD))
		wetuwn 0;

	WWEG32_SOC15(UVD, wing->me, mmUVD_POWEW_STATUS, UVD_POWEW_STATUS__UVD_PG_EN_MASK);

	if (state == AMD_PG_STATE_GATE) {
		uvd_v7_0_stop(adev);
		wetuwn 0;
	} ewse {
		wetuwn uvd_v7_0_stawt(adev);
	}
}
#endif

static int uvd_v7_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	/* needed fow dwivew unwoad*/
	wetuwn 0;
}

const stwuct amd_ip_funcs uvd_v7_0_ip_funcs = {
	.name = "uvd_v7_0",
	.eawwy_init = uvd_v7_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = uvd_v7_0_sw_init,
	.sw_fini = uvd_v7_0_sw_fini,
	.hw_init = uvd_v7_0_hw_init,
	.hw_fini = uvd_v7_0_hw_fini,
	.pwepawe_suspend = uvd_v7_0_pwepawe_suspend,
	.suspend = uvd_v7_0_suspend,
	.wesume = uvd_v7_0_wesume,
	.is_idwe = NUWW /* uvd_v7_0_is_idwe */,
	.wait_fow_idwe = NUWW /* uvd_v7_0_wait_fow_idwe */,
	.check_soft_weset = NUWW /* uvd_v7_0_check_soft_weset */,
	.pwe_soft_weset = NUWW /* uvd_v7_0_pwe_soft_weset */,
	.soft_weset = NUWW /* uvd_v7_0_soft_weset */,
	.post_soft_weset = NUWW /* uvd_v7_0_post_soft_weset */,
	.set_cwockgating_state = uvd_v7_0_set_cwockgating_state,
	.set_powewgating_state = NUWW /* uvd_v7_0_set_powewgating_state */,
};

static const stwuct amdgpu_wing_funcs uvd_v7_0_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_UVD,
	.awign_mask = 0xf,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = uvd_v7_0_wing_get_wptw,
	.get_wptw = uvd_v7_0_wing_get_wptw,
	.set_wptw = uvd_v7_0_wing_set_wptw,
	.patch_cs_in_pwace = uvd_v7_0_wing_patch_cs_in_pwace,
	.emit_fwame_size =
		6 + /* hdp invawidate */
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 6 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 8 +
		8 + /* uvd_v7_0_wing_emit_vm_fwush */
		14 + 14, /* uvd_v7_0_wing_emit_fence x2 vm fence */
	.emit_ib_size = 8, /* uvd_v7_0_wing_emit_ib */
	.emit_ib = uvd_v7_0_wing_emit_ib,
	.emit_fence = uvd_v7_0_wing_emit_fence,
	.emit_vm_fwush = uvd_v7_0_wing_emit_vm_fwush,
	.emit_hdp_fwush = uvd_v7_0_wing_emit_hdp_fwush,
	.test_wing = uvd_v7_0_wing_test_wing,
	.test_ib = amdgpu_uvd_wing_test_ib,
	.insewt_nop = uvd_v7_0_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_uvd_wing_begin_use,
	.end_use = amdgpu_uvd_wing_end_use,
	.emit_wweg = uvd_v7_0_wing_emit_wweg,
	.emit_weg_wait = uvd_v7_0_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static const stwuct amdgpu_wing_funcs uvd_v7_0_enc_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_UVD_ENC,
	.awign_mask = 0x3f,
	.nop = HEVC_ENC_CMD_NO_OP,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = uvd_v7_0_enc_wing_get_wptw,
	.get_wptw = uvd_v7_0_enc_wing_get_wptw,
	.set_wptw = uvd_v7_0_enc_wing_set_wptw,
	.emit_fwame_size =
		3 + 3 + /* hdp fwush / invawidate */
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 3 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 4 +
		4 + /* uvd_v7_0_enc_wing_emit_vm_fwush */
		5 + 5 + /* uvd_v7_0_enc_wing_emit_fence x2 vm fence */
		1, /* uvd_v7_0_enc_wing_insewt_end */
	.emit_ib_size = 5, /* uvd_v7_0_enc_wing_emit_ib */
	.emit_ib = uvd_v7_0_enc_wing_emit_ib,
	.emit_fence = uvd_v7_0_enc_wing_emit_fence,
	.emit_vm_fwush = uvd_v7_0_enc_wing_emit_vm_fwush,
	.test_wing = uvd_v7_0_enc_wing_test_wing,
	.test_ib = uvd_v7_0_enc_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.insewt_end = uvd_v7_0_enc_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_uvd_wing_begin_use,
	.end_use = amdgpu_uvd_wing_end_use,
	.emit_wweg = uvd_v7_0_enc_wing_emit_wweg,
	.emit_weg_wait = uvd_v7_0_enc_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static void uvd_v7_0_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->uvd.num_uvd_inst; i++) {
		if (adev->uvd.hawvest_config & (1 << i))
			continue;
		adev->uvd.inst[i].wing.funcs = &uvd_v7_0_wing_vm_funcs;
		adev->uvd.inst[i].wing.me = i;
		DWM_INFO("UVD(%d) is enabwed in VM mode\n", i);
	}
}

static void uvd_v7_0_set_enc_wing_funcs(stwuct amdgpu_device *adev)
{
	int i, j;

	fow (j = 0; j < adev->uvd.num_uvd_inst; j++) {
		if (adev->uvd.hawvest_config & (1 << j))
			continue;
		fow (i = 0; i < adev->uvd.num_enc_wings; ++i) {
			adev->uvd.inst[j].wing_enc[i].funcs = &uvd_v7_0_enc_wing_vm_funcs;
			adev->uvd.inst[j].wing_enc[i].me = j;
		}

		DWM_INFO("UVD(%d) ENC is enabwed in VM mode\n", j);
	}
}

static const stwuct amdgpu_iwq_swc_funcs uvd_v7_0_iwq_funcs = {
	.set = uvd_v7_0_set_intewwupt_state,
	.pwocess = uvd_v7_0_pwocess_intewwupt,
};

static void uvd_v7_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->uvd.num_uvd_inst; i++) {
		if (adev->uvd.hawvest_config & (1 << i))
			continue;
		adev->uvd.inst[i].iwq.num_types = adev->uvd.num_enc_wings + 1;
		adev->uvd.inst[i].iwq.funcs = &uvd_v7_0_iwq_funcs;
	}
}

const stwuct amdgpu_ip_bwock_vewsion uvd_v7_0_ip_bwock = {
		.type = AMD_IP_BWOCK_TYPE_UVD,
		.majow = 7,
		.minow = 0,
		.wev = 0,
		.funcs = &uvd_v7_0_ip_funcs,
};
