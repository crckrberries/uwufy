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

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "w600d.h"

/**
 * uvd_v1_0_get_wptw - get wead pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
uint32_t uvd_v1_0_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	wetuwn WWEG32(UVD_WBC_WB_WPTW);
}

/**
 * uvd_v1_0_get_wptw - get wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
uint32_t uvd_v1_0_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	wetuwn WWEG32(UVD_WBC_WB_WPTW);
}

/**
 * uvd_v1_0_set_wptw - set wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
void uvd_v1_0_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing)
{
	WWEG32(UVD_WBC_WB_WPTW, wing->wptw);
}

/**
 * uvd_v1_0_fence_emit - emit an fence & twap command
 *
 * @wdev: wadeon_device pointew
 * @fence: fence to emit
 *
 * Wwite a fence and a twap command to the wing.
 */
void uvd_v1_0_fence_emit(stwuct wadeon_device *wdev,
			 stwuct wadeon_fence *fence)
{
	stwuct wadeon_wing *wing = &wdev->wing[fence->wing];
	uint64_t addw = wdev->fence_dwv[fence->wing].gpu_addw;

	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_DATA0, 0));
	wadeon_wing_wwite(wing, addw & 0xffffffff);
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_DATA1, 0));
	wadeon_wing_wwite(wing, fence->seq);
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_CMD, 0));
	wadeon_wing_wwite(wing, 0);

	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_DATA0, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_DATA1, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_CMD, 0));
	wadeon_wing_wwite(wing, 2);
	wetuwn;
}

/**
 * uvd_v1_0_wesume - memowy contwowwew pwogwamming
 *
 * @wdev: wadeon_device pointew
 *
 * Wet the UVD memowy contwowwew know it's offsets
 */
int uvd_v1_0_wesume(stwuct wadeon_device *wdev)
{
	uint64_t addw;
	uint32_t size;
	int w;

	w = wadeon_uvd_wesume(wdev);
	if (w)
		wetuwn w;

	/* pwogwam the VCPU memowy contwowwew bits 0-27 */
	addw = (wdev->uvd.gpu_addw >> 3) + 16;
	size = WADEON_GPU_PAGE_AWIGN(wdev->uvd_fw->size) >> 3;
	WWEG32(UVD_VCPU_CACHE_OFFSET0, addw);
	WWEG32(UVD_VCPU_CACHE_SIZE0, size);

	addw += size;
	size = WADEON_UVD_HEAP_SIZE >> 3;
	WWEG32(UVD_VCPU_CACHE_OFFSET1, addw);
	WWEG32(UVD_VCPU_CACHE_SIZE1, size);

	addw += size;
	size = (WADEON_UVD_STACK_SIZE +
	       (WADEON_UVD_SESSION_SIZE * wdev->uvd.max_handwes)) >> 3;
	WWEG32(UVD_VCPU_CACHE_OFFSET2, addw);
	WWEG32(UVD_VCPU_CACHE_SIZE2, size);

	/* bits 28-31 */
	addw = (wdev->uvd.gpu_addw >> 28) & 0xF;
	WWEG32(UVD_WMI_ADDW_EXT, (addw << 12) | (addw << 0));

	/* bits 32-39 */
	addw = (wdev->uvd.gpu_addw >> 32) & 0xFF;
	WWEG32(UVD_WMI_EXT40_ADDW, addw | (0x9 << 16) | (0x1 << 31));

	WWEG32(UVD_FW_STAWT, *((uint32_t*)wdev->uvd.cpu_addw));

	wetuwn 0;
}

/**
 * uvd_v1_0_init - stawt and test UVD bwock
 *
 * @wdev: wadeon_device pointew
 *
 * Initiawize the hawdwawe, boot up the VCPU and do some testing
 */
int uvd_v1_0_init(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[W600_WING_TYPE_UVD_INDEX];
	uint32_t tmp;
	int w;

	/* waise cwocks whiwe booting up the VCPU */
	if (wdev->famiwy < CHIP_WV740)
		wadeon_set_uvd_cwocks(wdev, 10000, 10000);
	ewse
		wadeon_set_uvd_cwocks(wdev, 53300, 40000);

	w = uvd_v1_0_stawt(wdev);
	if (w)
		goto done;

	wing->weady = twue;
	w = wadeon_wing_test(wdev, W600_WING_TYPE_UVD_INDEX, wing);
	if (w) {
		wing->weady = fawse;
		goto done;
	}

	w = wadeon_wing_wock(wdev, wing, 10);
	if (w) {
		DWM_EWWOW("wadeon: wing faiwed to wock UVD wing (%d).\n", w);
		goto done;
	}

	tmp = PACKET0(UVD_SEMA_WAIT_FAUWT_TIMEOUT_CNTW, 0);
	wadeon_wing_wwite(wing, tmp);
	wadeon_wing_wwite(wing, 0xFFFFF);

	tmp = PACKET0(UVD_SEMA_WAIT_INCOMPWETE_TIMEOUT_CNTW, 0);
	wadeon_wing_wwite(wing, tmp);
	wadeon_wing_wwite(wing, 0xFFFFF);

	tmp = PACKET0(UVD_SEMA_SIGNAW_INCOMPWETE_TIMEOUT_CNTW, 0);
	wadeon_wing_wwite(wing, tmp);
	wadeon_wing_wwite(wing, 0xFFFFF);

	/* Cweaw timeout status bits */
	wadeon_wing_wwite(wing, PACKET0(UVD_SEMA_TIMEOUT_STATUS, 0));
	wadeon_wing_wwite(wing, 0x8);

	wadeon_wing_wwite(wing, PACKET0(UVD_SEMA_CNTW, 0));
	wadeon_wing_wwite(wing, 3);

	wadeon_wing_unwock_commit(wdev, wing, fawse);

done:
	/* wowew cwocks again */
	wadeon_set_uvd_cwocks(wdev, 0, 0);

	if (!w) {
		switch (wdev->famiwy) {
		case CHIP_WV610:
		case CHIP_WV630:
		case CHIP_WV620:
			/* 64byte gwanuwawity wowkawound */
			WWEG32(MC_CONFIG, 0);
			WWEG32(MC_CONFIG, 1 << 4);
			WWEG32(WS_DQ_WD_WET_CONF, 0x3f);
			WWEG32(MC_CONFIG, 0x1f);

			fawwthwough;
		case CHIP_WV670:
		case CHIP_WV635:

			/* wwite cwean wowkawound */
			WWEG32_P(UVD_VCPU_CNTW, 0x10, ~0x10);
			bweak;

		defauwt:
			/* TODO: Do we need mowe? */
			bweak;
		}

		DWM_INFO("UVD initiawized successfuwwy.\n");
	}

	wetuwn w;
}

/**
 * uvd_v1_0_fini - stop the hawdwawe bwock
 *
 * @wdev: wadeon_device pointew
 *
 * Stop the UVD bwock, mawk wing as not weady any mowe
 */
void uvd_v1_0_fini(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[W600_WING_TYPE_UVD_INDEX];

	uvd_v1_0_stop(wdev);
	wing->weady = fawse;
}

/**
 * uvd_v1_0_stawt - stawt UVD bwock
 *
 * @wdev: wadeon_device pointew
 *
 * Setup and stawt the UVD bwock
 */
int uvd_v1_0_stawt(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[W600_WING_TYPE_UVD_INDEX];
	uint32_t wb_bufsz;
	int i, j, w;

	/* disabwe byte swapping */
	u32 wmi_swap_cntw = 0;
	u32 mp_swap_cntw = 0;

	/* disabwe cwock gating */
	WWEG32(UVD_CGC_GATE, 0);

	/* disabwe intewupt */
	WWEG32_P(UVD_MASTINT_EN, 0, ~(1 << 1));

	/* Staww UMC and wegistew bus befowe wesetting VCPU */
	WWEG32_P(UVD_WMI_CTWW2, 1 << 8, ~(1 << 8));
	WWEG32_P(UVD_WB_AWB_CTWW, 1 << 3, ~(1 << 3));
	mdeway(1);

	/* put WMI, VCPU, WBC etc... into weset */
	WWEG32(UVD_SOFT_WESET, WMI_SOFT_WESET | VCPU_SOFT_WESET |
	       WBSI_SOFT_WESET | WBC_SOFT_WESET | CSM_SOFT_WESET |
	       CXW_SOFT_WESET | TAP_SOFT_WESET | WMI_UMC_SOFT_WESET);
	mdeway(5);

	/* take UVD bwock out of weset */
	WWEG32_P(SWBM_SOFT_WESET, 0, ~SOFT_WESET_UVD);
	mdeway(5);

	/* initiawize UVD memowy contwowwew */
	WWEG32(UVD_WMI_CTWW, 0x40 | (1 << 8) | (1 << 13) |
			     (1 << 21) | (1 << 9) | (1 << 20));

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) WB and IB */
	wmi_swap_cntw = 0xa;
	mp_swap_cntw = 0;
#endif
	WWEG32(UVD_WMI_SWAP_CNTW, wmi_swap_cntw);
	WWEG32(UVD_MP_SWAP_CNTW, mp_swap_cntw);

	WWEG32(UVD_MPC_SET_MUXA0, 0x40c2040);
	WWEG32(UVD_MPC_SET_MUXA1, 0x0);
	WWEG32(UVD_MPC_SET_MUXB0, 0x40c2040);
	WWEG32(UVD_MPC_SET_MUXB1, 0x0);
	WWEG32(UVD_MPC_SET_AWU, 0);
	WWEG32(UVD_MPC_SET_MUX, 0x88);

	/* take aww subbwocks out of weset, except VCPU */
	WWEG32(UVD_SOFT_WESET, VCPU_SOFT_WESET);
	mdeway(5);

	/* enabwe VCPU cwock */
	WWEG32(UVD_VCPU_CNTW,  1 << 9);

	/* enabwe UMC */
	WWEG32_P(UVD_WMI_CTWW2, 0, ~(1 << 8));

	WWEG32_P(UVD_WB_AWB_CTWW, 0, ~(1 << 3));

	/* boot up the VCPU */
	WWEG32(UVD_SOFT_WESET, 0);
	mdeway(10);

	fow (i = 0; i < 10; ++i) {
		uint32_t status;
		fow (j = 0; j < 100; ++j) {
			status = WWEG32(UVD_STATUS);
			if (status & 2)
				bweak;
			mdeway(10);
		}
		w = 0;
		if (status & 2)
			bweak;

		DWM_EWWOW("UVD not wesponding, twying to weset the VCPU!!!\n");
		WWEG32_P(UVD_SOFT_WESET, VCPU_SOFT_WESET, ~VCPU_SOFT_WESET);
		mdeway(10);
		WWEG32_P(UVD_SOFT_WESET, 0, ~VCPU_SOFT_WESET);
		mdeway(10);
		w = -1;
	}

	if (w) {
		DWM_EWWOW("UVD not wesponding, giving up!!!\n");
		wetuwn w;
	}

	/* enabwe intewupt */
	WWEG32_P(UVD_MASTINT_EN, 3<<1, ~(3 << 1));

	/* fowce WBC into idwe state */
	WWEG32(UVD_WBC_WB_CNTW, 0x11010101);

	/* Set the wwite pointew deway */
	WWEG32(UVD_WBC_WB_WPTW_CNTW, 0);

	/* pwogwam the 4GB memowy segment fow wptw and wing buffew */
	WWEG32(UVD_WMI_EXT40_ADDW, uppew_32_bits(wing->gpu_addw) |
				   (0x7 << 16) | (0x1 << 31));

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32(UVD_WBC_WB_WPTW, 0x0);

	wing->wptw = WWEG32(UVD_WBC_WB_WPTW);
	WWEG32(UVD_WBC_WB_WPTW, wing->wptw);

	/* set the wing addwess */
	WWEG32(UVD_WBC_WB_BASE, wing->gpu_addw);

	/* Set wing buffew size */
	wb_bufsz = owdew_base_2(wing->wing_size);
	wb_bufsz = (0x1 << 8) | wb_bufsz;
	WWEG32_P(UVD_WBC_WB_CNTW, wb_bufsz, ~0x11f1f);

	wetuwn 0;
}

/**
 * uvd_v1_0_stop - stop UVD bwock
 *
 * @wdev: wadeon_device pointew
 *
 * stop the UVD bwock
 */
void uvd_v1_0_stop(stwuct wadeon_device *wdev)
{
	/* fowce WBC into idwe state */
	WWEG32(UVD_WBC_WB_CNTW, 0x11010101);

	/* Staww UMC and wegistew bus befowe wesetting VCPU */
	WWEG32_P(UVD_WMI_CTWW2, 1 << 8, ~(1 << 8));
	WWEG32_P(UVD_WB_AWB_CTWW, 1 << 3, ~(1 << 3));
	mdeway(1);

	/* put VCPU into weset */
	WWEG32(UVD_SOFT_WESET, VCPU_SOFT_WESET);
	mdeway(5);

	/* disabwe VCPU cwock */
	WWEG32(UVD_VCPU_CNTW, 0x0);

	/* Unstaww UMC and wegistew bus */
	WWEG32_P(UVD_WMI_CTWW2, 0, ~(1 << 8));
	WWEG32_P(UVD_WB_AWB_CTWW, 0, ~(1 << 3));
}

/**
 * uvd_v1_0_wing_test - wegistew wwite test
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 *
 * Test if we can successfuwwy wwite to the context wegistew
 */
int uvd_v1_0_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	uint32_t tmp = 0;
	unsigned i;
	int w;

	WWEG32(UVD_CONTEXT_ID, 0xCAFEDEAD);
	w = wadeon_wing_wock(wdev, wing, 3);
	if (w) {
		DWM_EWWOW("wadeon: cp faiwed to wock wing %d (%d).\n",
			  wing->idx, w);
		wetuwn w;
	}
	wadeon_wing_wwite(wing, PACKET0(UVD_CONTEXT_ID, 0));
	wadeon_wing_wwite(wing, 0xDEADBEEF);
	wadeon_wing_unwock_commit(wdev, wing, fawse);
	fow (i = 0; i < wdev->usec_timeout; i++) {
		tmp = WWEG32(UVD_CONTEXT_ID);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i < wdev->usec_timeout) {
		DWM_INFO("wing test on %d succeeded in %d usecs\n",
			 wing->idx, i);
	} ewse {
		DWM_EWWOW("wadeon: wing %d test faiwed (0x%08X)\n",
			  wing->idx, tmp);
		w = -EINVAW;
	}
	wetuwn w;
}

/**
 * uvd_v1_0_semaphowe_emit - emit semaphowe command
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 * @semaphowe: semaphowe to emit commands fow
 * @emit_wait: twue if we shouwd emit a wait command
 *
 * Emit a semaphowe command (eithew wait ow signaw) to the UVD wing.
 */
boow uvd_v1_0_semaphowe_emit(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *wing,
			     stwuct wadeon_semaphowe *semaphowe,
			     boow emit_wait)
{
	/* disabwe semaphowes fow UVD V1 hawdwawe */
	wetuwn fawse;
}

/**
 * uvd_v1_0_ib_execute - execute indiwect buffew
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to execute
 *
 * Wwite wing commands to execute the indiwect buffew
 */
void uvd_v1_0_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib)
{
	stwuct wadeon_wing *wing = &wdev->wing[ib->wing];

	wadeon_wing_wwite(wing, PACKET0(UVD_WBC_IB_BASE, 0));
	wadeon_wing_wwite(wing, ib->gpu_addw);
	wadeon_wing_wwite(wing, PACKET0(UVD_WBC_IB_SIZE, 0));
	wadeon_wing_wwite(wing, ib->wength_dw);
}

/**
 * uvd_v1_0_ib_test - test ib execution
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 *
 * Test if we can successfuwwy execute an IB
 */
int uvd_v1_0_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	stwuct wadeon_fence *fence = NUWW;
	int w;

	if (wdev->famiwy < CHIP_WV740)
		w = wadeon_set_uvd_cwocks(wdev, 10000, 10000);
	ewse
		w = wadeon_set_uvd_cwocks(wdev, 53300, 40000);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to waise UVD cwocks (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_uvd_get_cweate_msg(wdev, wing->idx, 1, NUWW);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get cweate msg (%d).\n", w);
		goto ewwow;
	}

	w = wadeon_uvd_get_destwoy_msg(wdev, wing->idx, 1, &fence);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get destwoy ib (%d).\n", w);
		goto ewwow;
	}

	w = wadeon_fence_wait_timeout(fence, fawse, usecs_to_jiffies(
		WADEON_USEC_IB_TEST_TIMEOUT));
	if (w < 0) {
		DWM_EWWOW("wadeon: fence wait faiwed (%d).\n", w);
		goto ewwow;
	} ewse if (w == 0) {
		DWM_EWWOW("wadeon: fence wait timed out.\n");
		w = -ETIMEDOUT;
		goto ewwow;
	}
	w = 0;
	DWM_INFO("ib test on wing %d succeeded\n",  wing->idx);
ewwow:
	wadeon_fence_unwef(&fence);
	wadeon_set_uvd_cwocks(wdev, 0, 0);
	wetuwn w;
}
