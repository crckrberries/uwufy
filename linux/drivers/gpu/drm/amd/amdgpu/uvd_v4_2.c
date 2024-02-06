/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
 * Authows: Chwistian König <chwistian.koenig@amd.com>
 */

#incwude <winux/fiwmwawe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_uvd.h"
#incwude "cikd.h"

#incwude "uvd/uvd_4_2_d.h"
#incwude "uvd/uvd_4_2_sh_mask.h"

#incwude "oss/oss_2_0_d.h"
#incwude "oss/oss_2_0_sh_mask.h"

#incwude "bif/bif_4_1_d.h"

#incwude "smu/smu_7_0_1_d.h"
#incwude "smu/smu_7_0_1_sh_mask.h"

static void uvd_v4_2_mc_wesume(stwuct amdgpu_device *adev);
static void uvd_v4_2_set_wing_funcs(stwuct amdgpu_device *adev);
static void uvd_v4_2_set_iwq_funcs(stwuct amdgpu_device *adev);
static int uvd_v4_2_stawt(stwuct amdgpu_device *adev);
static void uvd_v4_2_stop(stwuct amdgpu_device *adev);
static int uvd_v4_2_set_cwockgating_state(void *handwe,
				enum amd_cwockgating_state state);
static void uvd_v4_2_set_dcm(stwuct amdgpu_device *adev,
			     boow sw_mode);
/**
 * uvd_v4_2_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t uvd_v4_2_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32(mmUVD_WBC_WB_WPTW);
}

/**
 * uvd_v4_2_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t uvd_v4_2_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32(mmUVD_WBC_WB_WPTW);
}

/**
 * uvd_v4_2_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void uvd_v4_2_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	WWEG32(mmUVD_WBC_WB_WPTW, wowew_32_bits(wing->wptw));
}

static int uvd_v4_2_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	adev->uvd.num_uvd_inst = 1;

	uvd_v4_2_set_wing_funcs(adev);
	uvd_v4_2_set_iwq_funcs(adev);

	wetuwn 0;
}

static int uvd_v4_2_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	/* UVD TWAP */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 124, &adev->uvd.inst->iwq);
	if (w)
		wetuwn w;

	w = amdgpu_uvd_sw_init(adev);
	if (w)
		wetuwn w;

	wing = &adev->uvd.inst->wing;
	spwintf(wing->name, "uvd");
	w = amdgpu_wing_init(adev, wing, 512, &adev->uvd.inst->iwq, 0,
			     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
	if (w)
		wetuwn w;

	w = amdgpu_uvd_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn w;
}

static int uvd_v4_2_sw_fini(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_uvd_suspend(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_uvd_sw_fini(adev);
}

static void uvd_v4_2_enabwe_mgcg(stwuct amdgpu_device *adev,
				 boow enabwe);
/**
 * uvd_v4_2_hw_init - stawt and test UVD bwock
 *
 * @handwe: handwe used to pass amdgpu_device pointew
 *
 * Initiawize the hawdwawe, boot up the VCPU and do some testing
 */
static int uvd_v4_2_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing = &adev->uvd.inst->wing;
	uint32_t tmp;
	int w;

	uvd_v4_2_enabwe_mgcg(adev, twue);
	amdgpu_asic_set_uvd_cwocks(adev, 10000, 10000);

	w = amdgpu_wing_test_hewpew(wing);
	if (w)
		goto done;

	w = amdgpu_wing_awwoc(wing, 10);
	if (w) {
		DWM_EWWOW("amdgpu: wing faiwed to wock UVD wing (%d).\n", w);
		goto done;
	}

	tmp = PACKET0(mmUVD_SEMA_WAIT_FAUWT_TIMEOUT_CNTW, 0);
	amdgpu_wing_wwite(wing, tmp);
	amdgpu_wing_wwite(wing, 0xFFFFF);

	tmp = PACKET0(mmUVD_SEMA_WAIT_INCOMPWETE_TIMEOUT_CNTW, 0);
	amdgpu_wing_wwite(wing, tmp);
	amdgpu_wing_wwite(wing, 0xFFFFF);

	tmp = PACKET0(mmUVD_SEMA_SIGNAW_INCOMPWETE_TIMEOUT_CNTW, 0);
	amdgpu_wing_wwite(wing, tmp);
	amdgpu_wing_wwite(wing, 0xFFFFF);

	/* Cweaw timeout status bits */
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_SEMA_TIMEOUT_STATUS, 0));
	amdgpu_wing_wwite(wing, 0x8);

	amdgpu_wing_wwite(wing, PACKET0(mmUVD_SEMA_CNTW, 0));
	amdgpu_wing_wwite(wing, 3);

	amdgpu_wing_commit(wing);

done:
	if (!w)
		DWM_INFO("UVD initiawized successfuwwy.\n");

	wetuwn w;
}

/**
 * uvd_v4_2_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: handwe used to pass amdgpu_device pointew
 *
 * Stop the UVD bwock, mawk wing as not weady any mowe
 */
static int uvd_v4_2_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->uvd.idwe_wowk);

	if (WWEG32(mmUVD_STATUS) != 0)
		uvd_v4_2_stop(adev);

	wetuwn 0;
}

static int uvd_v4_2_pwepawe_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn amdgpu_uvd_pwepawe_suspend(adev);
}

static int uvd_v4_2_suspend(void *handwe)
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

	w = uvd_v4_2_hw_fini(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_uvd_suspend(adev);
}

static int uvd_v4_2_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_uvd_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn uvd_v4_2_hw_init(adev);
}

/**
 * uvd_v4_2_stawt - stawt UVD bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the UVD bwock
 */
static int uvd_v4_2_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = &adev->uvd.inst->wing;
	uint32_t wb_bufsz;
	int i, j, w;
	u32 tmp;
	/* disabwe byte swapping */
	u32 wmi_swap_cntw = 0;
	u32 mp_swap_cntw = 0;

	/* set uvd busy */
	WWEG32_P(mmUVD_STATUS, 1<<2, ~(1<<2));

	uvd_v4_2_set_dcm(adev, twue);
	WWEG32(mmUVD_CGC_GATE, 0);

	/* take UVD bwock out of weset */
	WWEG32_P(mmSWBM_SOFT_WESET, 0, ~SWBM_SOFT_WESET__SOFT_WESET_UVD_MASK);
	mdeway(5);

	/* enabwe VCPU cwock */
	WWEG32(mmUVD_VCPU_CNTW,  1 << 9);

	/* disabwe intewupt */
	WWEG32_P(mmUVD_MASTINT_EN, 0, ~(1 << 1));

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) WB and IB */
	wmi_swap_cntw = 0xa;
	mp_swap_cntw = 0;
#endif
	WWEG32(mmUVD_WMI_SWAP_CNTW, wmi_swap_cntw);
	WWEG32(mmUVD_MP_SWAP_CNTW, mp_swap_cntw);
	/* initiawize UVD memowy contwowwew */
	WWEG32(mmUVD_WMI_CTWW, 0x203108);

	tmp = WWEG32(mmUVD_MPC_CNTW);
	WWEG32(mmUVD_MPC_CNTW, tmp | 0x10);

	WWEG32(mmUVD_MPC_SET_MUXA0, 0x40c2040);
	WWEG32(mmUVD_MPC_SET_MUXA1, 0x0);
	WWEG32(mmUVD_MPC_SET_MUXB0, 0x40c2040);
	WWEG32(mmUVD_MPC_SET_MUXB1, 0x0);
	WWEG32(mmUVD_MPC_SET_AWU, 0);
	WWEG32(mmUVD_MPC_SET_MUX, 0x88);

	uvd_v4_2_mc_wesume(adev);

	tmp = WWEG32_UVD_CTX(ixUVD_WMI_CACHE_CTWW);
	WWEG32_UVD_CTX(ixUVD_WMI_CACHE_CTWW, tmp & (~0x10));

	/* enabwe UMC */
	WWEG32_P(mmUVD_WMI_CTWW2, 0, ~(1 << 8));

	WWEG32_P(mmUVD_SOFT_WESET, 0, ~UVD_SOFT_WESET__WMI_SOFT_WESET_MASK);

	WWEG32_P(mmUVD_SOFT_WESET, 0, ~UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK);

	WWEG32_P(mmUVD_SOFT_WESET, 0, ~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);

	mdeway(10);

	fow (i = 0; i < 10; ++i) {
		uint32_t status;
		fow (j = 0; j < 100; ++j) {
			status = WWEG32(mmUVD_STATUS);
			if (status & 2)
				bweak;
			mdeway(10);
		}
		w = 0;
		if (status & 2)
			bweak;

		DWM_EWWOW("UVD not wesponding, twying to weset the VCPU!!!\n");
		WWEG32_P(mmUVD_SOFT_WESET, UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK,
				~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
		mdeway(10);
		WWEG32_P(mmUVD_SOFT_WESET, 0, ~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
		mdeway(10);
		w = -1;
	}

	if (w) {
		DWM_EWWOW("UVD not wesponding, giving up!!!\n");
		wetuwn w;
	}

	/* enabwe intewupt */
	WWEG32_P(mmUVD_MASTINT_EN, 3<<1, ~(3 << 1));

	WWEG32_P(mmUVD_STATUS, 0, ~(1<<2));

	/* fowce WBC into idwe state */
	WWEG32(mmUVD_WBC_WB_CNTW, 0x11010101);

	/* Set the wwite pointew deway */
	WWEG32(mmUVD_WBC_WB_WPTW_CNTW, 0);

	/* pwogwam the 4GB memowy segment fow wptw and wing buffew */
	WWEG32(mmUVD_WMI_EXT40_ADDW, uppew_32_bits(wing->gpu_addw) |
				   (0x7 << 16) | (0x1 << 31));

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32(mmUVD_WBC_WB_WPTW, 0x0);

	wing->wptw = WWEG32(mmUVD_WBC_WB_WPTW);
	WWEG32(mmUVD_WBC_WB_WPTW, wowew_32_bits(wing->wptw));

	/* set the wing addwess */
	WWEG32(mmUVD_WBC_WB_BASE, wing->gpu_addw);

	/* Set wing buffew size */
	wb_bufsz = owdew_base_2(wing->wing_size);
	wb_bufsz = (0x1 << 8) | wb_bufsz;
	WWEG32_P(mmUVD_WBC_WB_CNTW, wb_bufsz, ~0x11f1f);

	wetuwn 0;
}

/**
 * uvd_v4_2_stop - stop UVD bwock
 *
 * @adev: amdgpu_device pointew
 *
 * stop the UVD bwock
 */
static void uvd_v4_2_stop(stwuct amdgpu_device *adev)
{
	uint32_t i, j;
	uint32_t status;

	WWEG32(mmUVD_WBC_WB_CNTW, 0x11010101);

	fow (i = 0; i < 10; ++i) {
		fow (j = 0; j < 100; ++j) {
			status = WWEG32(mmUVD_STATUS);
			if (status & 2)
				bweak;
			mdeway(1);
		}
		if (status & 2)
			bweak;
	}

	fow (i = 0; i < 10; ++i) {
		fow (j = 0; j < 100; ++j) {
			status = WWEG32(mmUVD_WMI_STATUS);
			if (status & 0xf)
				bweak;
			mdeway(1);
		}
		if (status & 0xf)
			bweak;
	}

	/* Staww UMC and wegistew bus befowe wesetting VCPU */
	WWEG32_P(mmUVD_WMI_CTWW2, 1 << 8, ~(1 << 8));

	fow (i = 0; i < 10; ++i) {
		fow (j = 0; j < 100; ++j) {
			status = WWEG32(mmUVD_WMI_STATUS);
			if (status & 0x240)
				bweak;
			mdeway(1);
		}
		if (status & 0x240)
			bweak;
	}

	WWEG32_P(0x3D49, 0, ~(1 << 2));

	WWEG32_P(mmUVD_VCPU_CNTW, 0, ~(1 << 9));

	/* put WMI, VCPU, WBC etc... into weset */
	WWEG32(mmUVD_SOFT_WESET, UVD_SOFT_WESET__WMI_SOFT_WESET_MASK |
		UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK |
		UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK);

	WWEG32(mmUVD_STATUS, 0);

	uvd_v4_2_set_dcm(adev, fawse);
}

/**
 * uvd_v4_2_wing_emit_fence - emit an fence & twap command
 *
 * @wing: amdgpu_wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Wwite a fence and a twap command to the wing.
 */
static void uvd_v4_2_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				     unsigned fwags)
{
	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing, PACKET0(mmUVD_CONTEXT_ID, 0));
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_wing_wwite(wing, addw & 0xffffffff);
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw) & 0xff);
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_wing_wwite(wing, 0);

	amdgpu_wing_wwite(wing, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_wing_wwite(wing, 2);
}

/**
 * uvd_v4_2_wing_test_wing - wegistew wwite test
 *
 * @wing: amdgpu_wing pointew
 *
 * Test if we can successfuwwy wwite to the context wegistew
 */
static int uvd_v4_2_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t tmp = 0;
	unsigned i;
	int w;

	WWEG32(mmUVD_CONTEXT_ID, 0xCAFEDEAD);
	w = amdgpu_wing_awwoc(wing, 3);
	if (w)
		wetuwn w;

	amdgpu_wing_wwite(wing, PACKET0(mmUVD_CONTEXT_ID, 0));
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);
	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = WWEG32(mmUVD_CONTEXT_ID);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	wetuwn w;
}

/**
 * uvd_v4_2_wing_emit_ib - execute indiwect buffew
 *
 * @wing: amdgpu_wing pointew
 * @job: iob associated with the indiwect buffew
 * @ib: indiwect buffew to execute
 * @fwags: fwags associated with the indiwect buffew
 *
 * Wwite wing commands to execute the indiwect buffew
 */
static void uvd_v4_2_wing_emit_ib(stwuct amdgpu_wing *wing,
				  stwuct amdgpu_job *job,
				  stwuct amdgpu_ib *ib,
				  uint32_t fwags)
{
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_WBC_IB_BASE, 0));
	amdgpu_wing_wwite(wing, ib->gpu_addw);
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_WBC_IB_SIZE, 0));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

static void uvd_v4_2_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count)
{
	int i;

	WAWN_ON(wing->wptw % 2 || count % 2);

	fow (i = 0; i < count / 2; i++) {
		amdgpu_wing_wwite(wing, PACKET0(mmUVD_NO_OP, 0));
		amdgpu_wing_wwite(wing, 0);
	}
}

/**
 * uvd_v4_2_mc_wesume - memowy contwowwew pwogwamming
 *
 * @adev: amdgpu_device pointew
 *
 * Wet the UVD memowy contwowwew know it's offsets
 */
static void uvd_v4_2_mc_wesume(stwuct amdgpu_device *adev)
{
	uint64_t addw;
	uint32_t size;

	/* pwogwam the VCPU memowy contwowwew bits 0-27 */
	addw = (adev->uvd.inst->gpu_addw + AMDGPU_UVD_FIWMWAWE_OFFSET) >> 3;
	size = AMDGPU_UVD_FIWMWAWE_SIZE(adev) >> 3;
	WWEG32(mmUVD_VCPU_CACHE_OFFSET0, addw);
	WWEG32(mmUVD_VCPU_CACHE_SIZE0, size);

	addw += size;
	size = AMDGPU_UVD_HEAP_SIZE >> 3;
	WWEG32(mmUVD_VCPU_CACHE_OFFSET1, addw);
	WWEG32(mmUVD_VCPU_CACHE_SIZE1, size);

	addw += size;
	size = (AMDGPU_UVD_STACK_SIZE +
	       (AMDGPU_UVD_SESSION_SIZE * adev->uvd.max_handwes)) >> 3;
	WWEG32(mmUVD_VCPU_CACHE_OFFSET2, addw);
	WWEG32(mmUVD_VCPU_CACHE_SIZE2, size);

	/* bits 28-31 */
	addw = (adev->uvd.inst->gpu_addw >> 28) & 0xF;
	WWEG32(mmUVD_WMI_ADDW_EXT, (addw << 12) | (addw << 0));

	/* bits 32-39 */
	addw = (adev->uvd.inst->gpu_addw >> 32) & 0xFF;
	WWEG32(mmUVD_WMI_EXT40_ADDW, addw | (0x9 << 16) | (0x1 << 31));

	WWEG32(mmUVD_UDEC_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
	WWEG32(mmUVD_UDEC_DB_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
	WWEG32(mmUVD_UDEC_DBW_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
}

static void uvd_v4_2_enabwe_mgcg(stwuct amdgpu_device *adev,
				 boow enabwe)
{
	u32 owig, data;

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_UVD_MGCG)) {
		data = WWEG32_UVD_CTX(ixUVD_CGC_MEM_CTWW);
		data |= 0xfff;
		WWEG32_UVD_CTX(ixUVD_CGC_MEM_CTWW, data);

		owig = data = WWEG32(mmUVD_CGC_CTWW);
		data |= UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK;
		if (owig != data)
			WWEG32(mmUVD_CGC_CTWW, data);
	} ewse {
		data = WWEG32_UVD_CTX(ixUVD_CGC_MEM_CTWW);
		data &= ~0xfff;
		WWEG32_UVD_CTX(ixUVD_CGC_MEM_CTWW, data);

		owig = data = WWEG32(mmUVD_CGC_CTWW);
		data &= ~UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK;
		if (owig != data)
			WWEG32(mmUVD_CGC_CTWW, data);
	}
}

static void uvd_v4_2_set_dcm(stwuct amdgpu_device *adev,
			     boow sw_mode)
{
	u32 tmp, tmp2;

	WWEG32_FIEWD(UVD_CGC_GATE, WEGS, 0);

	tmp = WWEG32(mmUVD_CGC_CTWW);
	tmp &= ~(UVD_CGC_CTWW__CWK_OFF_DEWAY_MASK | UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW_MASK);
	tmp |= UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK |
		(1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT) |
		(4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT);

	if (sw_mode) {
		tmp &= ~0x7ffff800;
		tmp2 = UVD_CGC_CTWW2__DYN_OCWK_WAMP_EN_MASK |
			UVD_CGC_CTWW2__DYN_WCWK_WAMP_EN_MASK |
			(7 << UVD_CGC_CTWW2__GATEW_DIV_ID__SHIFT);
	} ewse {
		tmp |= 0x7ffff800;
		tmp2 = 0;
	}

	WWEG32(mmUVD_CGC_CTWW, tmp);
	WWEG32_UVD_CTX(ixUVD_CGC_CTWW2, tmp2);
}

static boow uvd_v4_2_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn !(WWEG32(mmSWBM_STATUS) & SWBM_STATUS__UVD_BUSY_MASK);
}

static int uvd_v4_2_wait_fow_idwe(void *handwe)
{
	unsigned i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (!(WWEG32(mmSWBM_STATUS) & SWBM_STATUS__UVD_BUSY_MASK))
			wetuwn 0;
	}
	wetuwn -ETIMEDOUT;
}

static int uvd_v4_2_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	uvd_v4_2_stop(adev);

	WWEG32_P(mmSWBM_SOFT_WESET, SWBM_SOFT_WESET__SOFT_WESET_UVD_MASK,
			~SWBM_SOFT_WESET__SOFT_WESET_UVD_MASK);
	mdeway(5);

	wetuwn uvd_v4_2_stawt(adev);
}

static int uvd_v4_2_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	// TODO
	wetuwn 0;
}

static int uvd_v4_2_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("IH: UVD TWAP\n");
	amdgpu_fence_pwocess(&adev->uvd.inst->wing);
	wetuwn 0;
}

static int uvd_v4_2_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static int uvd_v4_2_set_powewgating_state(void *handwe,
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

	if (state == AMD_PG_STATE_GATE) {
		uvd_v4_2_stop(adev);
		if (adev->pg_fwags & AMD_PG_SUPPOWT_UVD && !adev->pm.dpm_enabwed) {
			if (!(WWEG32_SMC(ixCUWWENT_PG_STATUS) &
				CUWWENT_PG_STATUS__UVD_PG_STATUS_MASK)) {
				WWEG32(mmUVD_PGFSM_CONFIG, (UVD_PGFSM_CONFIG__UVD_PGFSM_FSM_ADDW_MASK   |
							UVD_PGFSM_CONFIG__UVD_PGFSM_POWEW_DOWN_MASK |
							UVD_PGFSM_CONFIG__UVD_PGFSM_P1_SEWECT_MASK));
				mdeway(20);
			}
		}
		wetuwn 0;
	} ewse {
		if (adev->pg_fwags & AMD_PG_SUPPOWT_UVD && !adev->pm.dpm_enabwed) {
			if (WWEG32_SMC(ixCUWWENT_PG_STATUS) &
				CUWWENT_PG_STATUS__UVD_PG_STATUS_MASK) {
				WWEG32(mmUVD_PGFSM_CONFIG, (UVD_PGFSM_CONFIG__UVD_PGFSM_FSM_ADDW_MASK   |
						UVD_PGFSM_CONFIG__UVD_PGFSM_POWEW_UP_MASK |
						UVD_PGFSM_CONFIG__UVD_PGFSM_P1_SEWECT_MASK));
				mdeway(30);
			}
		}
		wetuwn uvd_v4_2_stawt(adev);
	}
}

static const stwuct amd_ip_funcs uvd_v4_2_ip_funcs = {
	.name = "uvd_v4_2",
	.eawwy_init = uvd_v4_2_eawwy_init,
	.wate_init = NUWW,
	.sw_init = uvd_v4_2_sw_init,
	.sw_fini = uvd_v4_2_sw_fini,
	.hw_init = uvd_v4_2_hw_init,
	.hw_fini = uvd_v4_2_hw_fini,
	.pwepawe_suspend = uvd_v4_2_pwepawe_suspend,
	.suspend = uvd_v4_2_suspend,
	.wesume = uvd_v4_2_wesume,
	.is_idwe = uvd_v4_2_is_idwe,
	.wait_fow_idwe = uvd_v4_2_wait_fow_idwe,
	.soft_weset = uvd_v4_2_soft_weset,
	.set_cwockgating_state = uvd_v4_2_set_cwockgating_state,
	.set_powewgating_state = uvd_v4_2_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs uvd_v4_2_wing_funcs = {
	.type = AMDGPU_WING_TYPE_UVD,
	.awign_mask = 0xf,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = uvd_v4_2_wing_get_wptw,
	.get_wptw = uvd_v4_2_wing_get_wptw,
	.set_wptw = uvd_v4_2_wing_set_wptw,
	.pawse_cs = amdgpu_uvd_wing_pawse_cs,
	.emit_fwame_size =
		14, /* uvd_v4_2_wing_emit_fence  x1 no usew fence */
	.emit_ib_size = 4, /* uvd_v4_2_wing_emit_ib */
	.emit_ib = uvd_v4_2_wing_emit_ib,
	.emit_fence = uvd_v4_2_wing_emit_fence,
	.test_wing = uvd_v4_2_wing_test_wing,
	.test_ib = amdgpu_uvd_wing_test_ib,
	.insewt_nop = uvd_v4_2_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_uvd_wing_begin_use,
	.end_use = amdgpu_uvd_wing_end_use,
};

static void uvd_v4_2_set_wing_funcs(stwuct amdgpu_device *adev)
{
	adev->uvd.inst->wing.funcs = &uvd_v4_2_wing_funcs;
}

static const stwuct amdgpu_iwq_swc_funcs uvd_v4_2_iwq_funcs = {
	.set = uvd_v4_2_set_intewwupt_state,
	.pwocess = uvd_v4_2_pwocess_intewwupt,
};

static void uvd_v4_2_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->uvd.inst->iwq.num_types = 1;
	adev->uvd.inst->iwq.funcs = &uvd_v4_2_iwq_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion uvd_v4_2_ip_bwock =
{
		.type = AMD_IP_BWOCK_TYPE_UVD,
		.majow = 4,
		.minow = 2,
		.wev = 0,
		.funcs = &uvd_v4_2_ip_funcs,
};
