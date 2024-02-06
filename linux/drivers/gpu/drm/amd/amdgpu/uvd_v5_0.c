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
 * Authows: Chwistian König <chwistian.koenig@amd.com>
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_uvd.h"
#incwude "vid.h"
#incwude "uvd/uvd_5_0_d.h"
#incwude "uvd/uvd_5_0_sh_mask.h"
#incwude "oss/oss_2_0_d.h"
#incwude "oss/oss_2_0_sh_mask.h"
#incwude "bif/bif_5_0_d.h"
#incwude "vi.h"
#incwude "smu/smu_7_1_2_d.h"
#incwude "smu/smu_7_1_2_sh_mask.h"
#incwude "ivswcid/ivswcid_viswands30.h"

static void uvd_v5_0_set_wing_funcs(stwuct amdgpu_device *adev);
static void uvd_v5_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static int uvd_v5_0_stawt(stwuct amdgpu_device *adev);
static void uvd_v5_0_stop(stwuct amdgpu_device *adev);
static int uvd_v5_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state);
static void uvd_v5_0_enabwe_mgcg(stwuct amdgpu_device *adev,
				 boow enabwe);
/**
 * uvd_v5_0_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t uvd_v5_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32(mmUVD_WBC_WB_WPTW);
}

/**
 * uvd_v5_0_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t uvd_v5_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32(mmUVD_WBC_WB_WPTW);
}

/**
 * uvd_v5_0_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void uvd_v5_0_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	WWEG32(mmUVD_WBC_WB_WPTW, wowew_32_bits(wing->wptw));
}

static int uvd_v5_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	adev->uvd.num_uvd_inst = 1;

	uvd_v5_0_set_wing_funcs(adev);
	uvd_v5_0_set_iwq_funcs(adev);

	wetuwn 0;
}

static int uvd_v5_0_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	/* UVD TWAP */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_UVD_SYSTEM_MESSAGE, &adev->uvd.inst->iwq);
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

static int uvd_v5_0_sw_fini(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_uvd_suspend(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_uvd_sw_fini(adev);
}

/**
 * uvd_v5_0_hw_init - stawt and test UVD bwock
 *
 * @handwe: handwe used to pass amdgpu_device pointew
 *
 * Initiawize the hawdwawe, boot up the VCPU and do some testing
 */
static int uvd_v5_0_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing = &adev->uvd.inst->wing;
	uint32_t tmp;
	int w;

	amdgpu_asic_set_uvd_cwocks(adev, 10000, 10000);
	uvd_v5_0_set_cwockgating_state(adev, AMD_CG_STATE_UNGATE);
	uvd_v5_0_enabwe_mgcg(adev, twue);

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
 * uvd_v5_0_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: handwe used to pass amdgpu_device pointew
 *
 * Stop the UVD bwock, mawk wing as not weady any mowe
 */
static int uvd_v5_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->uvd.idwe_wowk);

	if (WWEG32(mmUVD_STATUS) != 0)
		uvd_v5_0_stop(adev);

	wetuwn 0;
}

static int uvd_v5_0_pwepawe_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn amdgpu_uvd_pwepawe_suspend(adev);
}

static int uvd_v5_0_suspend(void *handwe)
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

	w = uvd_v5_0_hw_fini(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_uvd_suspend(adev);
}

static int uvd_v5_0_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_uvd_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn uvd_v5_0_hw_init(adev);
}

/**
 * uvd_v5_0_mc_wesume - memowy contwowwew pwogwamming
 *
 * @adev: amdgpu_device pointew
 *
 * Wet the UVD memowy contwowwew know it's offsets
 */
static void uvd_v5_0_mc_wesume(stwuct amdgpu_device *adev)
{
	uint64_t offset;
	uint32_t size;

	/* pwogwam memowy contwowwew bits 0-27 */
	WWEG32(mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			wowew_32_bits(adev->uvd.inst->gpu_addw));
	WWEG32(mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			uppew_32_bits(adev->uvd.inst->gpu_addw));

	offset = AMDGPU_UVD_FIWMWAWE_OFFSET;
	size = AMDGPU_UVD_FIWMWAWE_SIZE(adev);
	WWEG32(mmUVD_VCPU_CACHE_OFFSET0, offset >> 3);
	WWEG32(mmUVD_VCPU_CACHE_SIZE0, size);

	offset += size;
	size = AMDGPU_UVD_HEAP_SIZE;
	WWEG32(mmUVD_VCPU_CACHE_OFFSET1, offset >> 3);
	WWEG32(mmUVD_VCPU_CACHE_SIZE1, size);

	offset += size;
	size = AMDGPU_UVD_STACK_SIZE +
	       (AMDGPU_UVD_SESSION_SIZE * adev->uvd.max_handwes);
	WWEG32(mmUVD_VCPU_CACHE_OFFSET2, offset >> 3);
	WWEG32(mmUVD_VCPU_CACHE_SIZE2, size);

	WWEG32(mmUVD_UDEC_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
	WWEG32(mmUVD_UDEC_DB_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
	WWEG32(mmUVD_UDEC_DBW_ADDW_CONFIG, adev->gfx.config.gb_addw_config);
}

/**
 * uvd_v5_0_stawt - stawt UVD bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the UVD bwock
 */
static int uvd_v5_0_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = &adev->uvd.inst->wing;
	uint32_t wb_bufsz, tmp;
	uint32_t wmi_swap_cntw;
	uint32_t mp_swap_cntw;
	int i, j, w;

	/*disabwe DPG */
	WWEG32_P(mmUVD_POWEW_STATUS, 0, ~(1 << 2));

	/* disabwe byte swapping */
	wmi_swap_cntw = 0;
	mp_swap_cntw = 0;

	uvd_v5_0_mc_wesume(adev);

	/* disabwe intewupt */
	WWEG32_P(mmUVD_MASTINT_EN, 0, ~(1 << 1));

	/* staww UMC and wegistew bus befowe wesetting VCPU */
	WWEG32_P(mmUVD_WMI_CTWW2, 1 << 8, ~(1 << 8));
	mdeway(1);

	/* put WMI, VCPU, WBC etc... into weset */
	WWEG32(mmUVD_SOFT_WESET, UVD_SOFT_WESET__WMI_SOFT_WESET_MASK |
		UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK | UVD_SOFT_WESET__WBSI_SOFT_WESET_MASK |
		UVD_SOFT_WESET__WBC_SOFT_WESET_MASK | UVD_SOFT_WESET__CSM_SOFT_WESET_MASK |
		UVD_SOFT_WESET__CXW_SOFT_WESET_MASK | UVD_SOFT_WESET__TAP_SOFT_WESET_MASK |
		UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK);
	mdeway(5);

	/* take UVD bwock out of weset */
	WWEG32_P(mmSWBM_SOFT_WESET, 0, ~SWBM_SOFT_WESET__SOFT_WESET_UVD_MASK);
	mdeway(5);

	/* initiawize UVD memowy contwowwew */
	WWEG32(mmUVD_WMI_CTWW, 0x40 | (1 << 8) | (1 << 13) |
			     (1 << 21) | (1 << 9) | (1 << 20));

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) WB and IB */
	wmi_swap_cntw = 0xa;
	mp_swap_cntw = 0;
#endif
	WWEG32(mmUVD_WMI_SWAP_CNTW, wmi_swap_cntw);
	WWEG32(mmUVD_MP_SWAP_CNTW, mp_swap_cntw);

	WWEG32(mmUVD_MPC_SET_MUXA0, 0x40c2040);
	WWEG32(mmUVD_MPC_SET_MUXA1, 0x0);
	WWEG32(mmUVD_MPC_SET_MUXB0, 0x40c2040);
	WWEG32(mmUVD_MPC_SET_MUXB1, 0x0);
	WWEG32(mmUVD_MPC_SET_AWU, 0);
	WWEG32(mmUVD_MPC_SET_MUX, 0x88);

	/* take aww subbwocks out of weset, except VCPU */
	WWEG32(mmUVD_SOFT_WESET, UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
	mdeway(5);

	/* enabwe VCPU cwock */
	WWEG32(mmUVD_VCPU_CNTW,  1 << 9);

	/* enabwe UMC */
	WWEG32_P(mmUVD_WMI_CTWW2, 0, ~(1 << 8));

	/* boot up the VCPU */
	WWEG32(mmUVD_SOFT_WESET, 0);
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
	/* enabwe mastew intewwupt */
	WWEG32_P(mmUVD_MASTINT_EN, 3 << 1, ~(3 << 1));

	/* cweaw the bit 4 of UVD_STATUS */
	WWEG32_P(mmUVD_STATUS, 0, ~(2 << 1));

	wb_bufsz = owdew_base_2(wing->wing_size);
	tmp = 0;
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_BUFSZ, wb_bufsz);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_BWKSZ, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_FETCH, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_POWW_EN, 0);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_UPDATE, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_WW_EN, 1);
	/* fowce WBC into idwe state */
	WWEG32(mmUVD_WBC_WB_CNTW, tmp);

	/* set the wwite pointew deway */
	WWEG32(mmUVD_WBC_WB_WPTW_CNTW, 0);

	/* set the wb addwess */
	WWEG32(mmUVD_WBC_WB_WPTW_ADDW, (uppew_32_bits(wing->gpu_addw) >> 2));

	/* pwogwam the WB_BASE fow wing buffew */
	WWEG32(mmUVD_WMI_WBC_WB_64BIT_BAW_WOW,
			wowew_32_bits(wing->gpu_addw));
	WWEG32(mmUVD_WMI_WBC_WB_64BIT_BAW_HIGH,
			uppew_32_bits(wing->gpu_addw));

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32(mmUVD_WBC_WB_WPTW, 0);

	wing->wptw = WWEG32(mmUVD_WBC_WB_WPTW);
	WWEG32(mmUVD_WBC_WB_WPTW, wowew_32_bits(wing->wptw));

	WWEG32_P(mmUVD_WBC_WB_CNTW, 0, ~UVD_WBC_WB_CNTW__WB_NO_FETCH_MASK);

	wetuwn 0;
}

/**
 * uvd_v5_0_stop - stop UVD bwock
 *
 * @adev: amdgpu_device pointew
 *
 * stop the UVD bwock
 */
static void uvd_v5_0_stop(stwuct amdgpu_device *adev)
{
	/* fowce WBC into idwe state */
	WWEG32(mmUVD_WBC_WB_CNTW, 0x11010101);

	/* Staww UMC and wegistew bus befowe wesetting VCPU */
	WWEG32_P(mmUVD_WMI_CTWW2, 1 << 8, ~(1 << 8));
	mdeway(1);

	/* put VCPU into weset */
	WWEG32(mmUVD_SOFT_WESET, UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
	mdeway(5);

	/* disabwe VCPU cwock */
	WWEG32(mmUVD_VCPU_CNTW, 0x0);

	/* Unstaww UMC and wegistew bus */
	WWEG32_P(mmUVD_WMI_CTWW2, 0, ~(1 << 8));

	WWEG32(mmUVD_STATUS, 0);
}

/**
 * uvd_v5_0_wing_emit_fence - emit an fence & twap command
 *
 * @wing: amdgpu_wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Wwite a fence and a twap command to the wing.
 */
static void uvd_v5_0_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
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
 * uvd_v5_0_wing_test_wing - wegistew wwite test
 *
 * @wing: amdgpu_wing pointew
 *
 * Test if we can successfuwwy wwite to the context wegistew
 */
static int uvd_v5_0_wing_test_wing(stwuct amdgpu_wing *wing)
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
 * uvd_v5_0_wing_emit_ib - execute indiwect buffew
 *
 * @wing: amdgpu_wing pointew
 * @job: job to wetwieve vmid fwom
 * @ib: indiwect buffew to execute
 * @fwags: unused
 *
 * Wwite wing commands to execute the indiwect buffew
 */
static void uvd_v5_0_wing_emit_ib(stwuct amdgpu_wing *wing,
				  stwuct amdgpu_job *job,
				  stwuct amdgpu_ib *ib,
				  uint32_t fwags)
{
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_WMI_WBC_IB_64BIT_BAW_WOW, 0));
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_WMI_WBC_IB_64BIT_BAW_HIGH, 0));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, PACKET0(mmUVD_WBC_IB_SIZE, 0));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

static void uvd_v5_0_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count)
{
	int i;

	WAWN_ON(wing->wptw % 2 || count % 2);

	fow (i = 0; i < count / 2; i++) {
		amdgpu_wing_wwite(wing, PACKET0(mmUVD_NO_OP, 0));
		amdgpu_wing_wwite(wing, 0);
	}
}

static boow uvd_v5_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn !(WWEG32(mmSWBM_STATUS) & SWBM_STATUS__UVD_BUSY_MASK);
}

static int uvd_v5_0_wait_fow_idwe(void *handwe)
{
	unsigned i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (!(WWEG32(mmSWBM_STATUS) & SWBM_STATUS__UVD_BUSY_MASK))
			wetuwn 0;
	}
	wetuwn -ETIMEDOUT;
}

static int uvd_v5_0_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	uvd_v5_0_stop(adev);

	WWEG32_P(mmSWBM_SOFT_WESET, SWBM_SOFT_WESET__SOFT_WESET_UVD_MASK,
			~SWBM_SOFT_WESET__SOFT_WESET_UVD_MASK);
	mdeway(5);

	wetuwn uvd_v5_0_stawt(adev);
}

static int uvd_v5_0_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	// TODO
	wetuwn 0;
}

static int uvd_v5_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("IH: UVD TWAP\n");
	amdgpu_fence_pwocess(&adev->uvd.inst->wing);
	wetuwn 0;
}

static void uvd_v5_0_enabwe_cwock_gating(stwuct amdgpu_device *adev, boow enabwe)
{
	uint32_t data1, data3, suvd_fwags;

	data1 = WWEG32(mmUVD_SUVD_CGC_GATE);
	data3 = WWEG32(mmUVD_CGC_GATE);

	suvd_fwags = UVD_SUVD_CGC_GATE__SWE_MASK |
		     UVD_SUVD_CGC_GATE__SIT_MASK |
		     UVD_SUVD_CGC_GATE__SMP_MASK |
		     UVD_SUVD_CGC_GATE__SCM_MASK |
		     UVD_SUVD_CGC_GATE__SDB_MASK;

	if (enabwe) {
		data3 |= (UVD_CGC_GATE__SYS_MASK     |
			UVD_CGC_GATE__UDEC_MASK      |
			UVD_CGC_GATE__MPEG2_MASK     |
			UVD_CGC_GATE__WBC_MASK       |
			UVD_CGC_GATE__WMI_MC_MASK    |
			UVD_CGC_GATE__IDCT_MASK      |
			UVD_CGC_GATE__MPWD_MASK      |
			UVD_CGC_GATE__MPC_MASK       |
			UVD_CGC_GATE__WBSI_MASK      |
			UVD_CGC_GATE__WWBBM_MASK     |
			UVD_CGC_GATE__UDEC_WE_MASK   |
			UVD_CGC_GATE__UDEC_CM_MASK   |
			UVD_CGC_GATE__UDEC_IT_MASK   |
			UVD_CGC_GATE__UDEC_DB_MASK   |
			UVD_CGC_GATE__UDEC_MP_MASK   |
			UVD_CGC_GATE__WCB_MASK       |
			UVD_CGC_GATE__JPEG_MASK      |
			UVD_CGC_GATE__SCPU_MASK);
		/* onwy in pg enabwed, we can gate cwock to vcpu*/
		if (adev->pg_fwags & AMD_PG_SUPPOWT_UVD)
			data3 |= UVD_CGC_GATE__VCPU_MASK;
		data3 &= ~UVD_CGC_GATE__WEGS_MASK;
		data1 |= suvd_fwags;
	} ewse {
		data3 = 0;
		data1 = 0;
	}

	WWEG32(mmUVD_SUVD_CGC_GATE, data1);
	WWEG32(mmUVD_CGC_GATE, data3);
}

static void uvd_v5_0_set_sw_cwock_gating(stwuct amdgpu_device *adev)
{
	uint32_t data, data2;

	data = WWEG32(mmUVD_CGC_CTWW);
	data2 = WWEG32(mmUVD_SUVD_CGC_CTWW);


	data &= ~(UVD_CGC_CTWW__CWK_OFF_DEWAY_MASK |
		  UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW_MASK);


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
			UVD_CGC_CTWW__SCPU_MODE_MASK);
	data2 &= ~(UVD_SUVD_CGC_CTWW__SWE_MODE_MASK |
			UVD_SUVD_CGC_CTWW__SIT_MODE_MASK |
			UVD_SUVD_CGC_CTWW__SMP_MODE_MASK |
			UVD_SUVD_CGC_CTWW__SCM_MODE_MASK |
			UVD_SUVD_CGC_CTWW__SDB_MODE_MASK);

	WWEG32(mmUVD_CGC_CTWW, data);
	WWEG32(mmUVD_SUVD_CGC_CTWW, data2);
}

#if 0
static void uvd_v5_0_set_hw_cwock_gating(stwuct amdgpu_device *adev)
{
	uint32_t data, data1, cgc_fwags, suvd_fwags;

	data = WWEG32(mmUVD_CGC_GATE);
	data1 = WWEG32(mmUVD_SUVD_CGC_GATE);

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
				UVD_CGC_GATE__SCPU_MASK;

	suvd_fwags = UVD_SUVD_CGC_GATE__SWE_MASK |
				UVD_SUVD_CGC_GATE__SIT_MASK |
				UVD_SUVD_CGC_GATE__SMP_MASK |
				UVD_SUVD_CGC_GATE__SCM_MASK |
				UVD_SUVD_CGC_GATE__SDB_MASK;

	data |= cgc_fwags;
	data1 |= suvd_fwags;

	WWEG32(mmUVD_CGC_GATE, data);
	WWEG32(mmUVD_SUVD_CGC_GATE, data1);
}
#endif

static void uvd_v5_0_enabwe_mgcg(stwuct amdgpu_device *adev,
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

static int uvd_v5_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_CG_STATE_GATE);

	if (enabwe) {
		/* wait fow STATUS to cweaw */
		if (uvd_v5_0_wait_fow_idwe(handwe))
			wetuwn -EBUSY;
		uvd_v5_0_enabwe_cwock_gating(adev, twue);

		/* enabwe HW gates because UVD is idwe */
/*		uvd_v5_0_set_hw_cwock_gating(adev); */
	} ewse {
		uvd_v5_0_enabwe_cwock_gating(adev, fawse);
	}

	uvd_v5_0_set_sw_cwock_gating(adev);
	wetuwn 0;
}

static int uvd_v5_0_set_powewgating_state(void *handwe,
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
	int wet = 0;

	if (state == AMD_PG_STATE_GATE) {
		uvd_v5_0_stop(adev);
	} ewse {
		wet = uvd_v5_0_stawt(adev);
		if (wet)
			goto out;
	}

out:
	wetuwn wet;
}

static void uvd_v5_0_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int data;

	mutex_wock(&adev->pm.mutex);

	if (WWEG32_SMC(ixCUWWENT_PG_STATUS) &
				CUWWENT_PG_STATUS__UVD_PG_STATUS_MASK) {
		DWM_INFO("Cannot get cwockgating state when UVD is powewgated.\n");
		goto out;
	}

	/* AMD_CG_SUPPOWT_UVD_MGCG */
	data = WWEG32(mmUVD_CGC_CTWW);
	if (data & UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK)
		*fwags |= AMD_CG_SUPPOWT_UVD_MGCG;

out:
	mutex_unwock(&adev->pm.mutex);
}

static const stwuct amd_ip_funcs uvd_v5_0_ip_funcs = {
	.name = "uvd_v5_0",
	.eawwy_init = uvd_v5_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = uvd_v5_0_sw_init,
	.sw_fini = uvd_v5_0_sw_fini,
	.hw_init = uvd_v5_0_hw_init,
	.hw_fini = uvd_v5_0_hw_fini,
	.pwepawe_suspend = uvd_v5_0_pwepawe_suspend,
	.suspend = uvd_v5_0_suspend,
	.wesume = uvd_v5_0_wesume,
	.is_idwe = uvd_v5_0_is_idwe,
	.wait_fow_idwe = uvd_v5_0_wait_fow_idwe,
	.soft_weset = uvd_v5_0_soft_weset,
	.set_cwockgating_state = uvd_v5_0_set_cwockgating_state,
	.set_powewgating_state = uvd_v5_0_set_powewgating_state,
	.get_cwockgating_state = uvd_v5_0_get_cwockgating_state,
};

static const stwuct amdgpu_wing_funcs uvd_v5_0_wing_funcs = {
	.type = AMDGPU_WING_TYPE_UVD,
	.awign_mask = 0xf,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = uvd_v5_0_wing_get_wptw,
	.get_wptw = uvd_v5_0_wing_get_wptw,
	.set_wptw = uvd_v5_0_wing_set_wptw,
	.pawse_cs = amdgpu_uvd_wing_pawse_cs,
	.emit_fwame_size =
		14, /* uvd_v5_0_wing_emit_fence  x1 no usew fence */
	.emit_ib_size = 6, /* uvd_v5_0_wing_emit_ib */
	.emit_ib = uvd_v5_0_wing_emit_ib,
	.emit_fence = uvd_v5_0_wing_emit_fence,
	.test_wing = uvd_v5_0_wing_test_wing,
	.test_ib = amdgpu_uvd_wing_test_ib,
	.insewt_nop = uvd_v5_0_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_uvd_wing_begin_use,
	.end_use = amdgpu_uvd_wing_end_use,
};

static void uvd_v5_0_set_wing_funcs(stwuct amdgpu_device *adev)
{
	adev->uvd.inst->wing.funcs = &uvd_v5_0_wing_funcs;
}

static const stwuct amdgpu_iwq_swc_funcs uvd_v5_0_iwq_funcs = {
	.set = uvd_v5_0_set_intewwupt_state,
	.pwocess = uvd_v5_0_pwocess_intewwupt,
};

static void uvd_v5_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->uvd.inst->iwq.num_types = 1;
	adev->uvd.inst->iwq.funcs = &uvd_v5_0_iwq_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion uvd_v5_0_ip_bwock =
{
		.type = AMD_IP_BWOCK_TYPE_UVD,
		.majow = 5,
		.minow = 0,
		.wev = 0,
		.funcs = &uvd_v5_0_ip_funcs,
};
