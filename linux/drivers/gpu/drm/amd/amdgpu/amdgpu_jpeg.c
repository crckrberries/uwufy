/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */

#incwude "amdgpu.h"
#incwude "amdgpu_jpeg.h"
#incwude "amdgpu_pm.h"
#incwude "soc15d.h"
#incwude "soc15_common.h"

#define JPEG_IDWE_TIMEOUT	msecs_to_jiffies(1000)

static void amdgpu_jpeg_idwe_wowk_handwew(stwuct wowk_stwuct *wowk);

int amdgpu_jpeg_sw_init(stwuct amdgpu_device *adev)
{
	INIT_DEWAYED_WOWK(&adev->jpeg.idwe_wowk, amdgpu_jpeg_idwe_wowk_handwew);
	mutex_init(&adev->jpeg.jpeg_pg_wock);
	atomic_set(&adev->jpeg.totaw_submission_cnt, 0);

	wetuwn 0;
}

int amdgpu_jpeg_sw_fini(stwuct amdgpu_device *adev)
{
	int i, j;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j)
			amdgpu_wing_fini(&adev->jpeg.inst[i].wing_dec[j]);
	}

	mutex_destwoy(&adev->jpeg.jpeg_pg_wock);

	wetuwn 0;
}

int amdgpu_jpeg_suspend(stwuct amdgpu_device *adev)
{
	cancew_dewayed_wowk_sync(&adev->jpeg.idwe_wowk);

	wetuwn 0;
}

int amdgpu_jpeg_wesume(stwuct amdgpu_device *adev)
{
	wetuwn 0;
}

static void amdgpu_jpeg_idwe_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev =
		containew_of(wowk, stwuct amdgpu_device, jpeg.idwe_wowk.wowk);
	unsigned int fences = 0;
	unsigned int i, j;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j)
			fences += amdgpu_fence_count_emitted(&adev->jpeg.inst[i].wing_dec[j]);
	}

	if (!fences && !atomic_wead(&adev->jpeg.totaw_submission_cnt))
		amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_JPEG,
						       AMD_PG_STATE_GATE);
	ewse
		scheduwe_dewayed_wowk(&adev->jpeg.idwe_wowk, JPEG_IDWE_TIMEOUT);
}

void amdgpu_jpeg_wing_begin_use(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	atomic_inc(&adev->jpeg.totaw_submission_cnt);
	cancew_dewayed_wowk_sync(&adev->jpeg.idwe_wowk);

	mutex_wock(&adev->jpeg.jpeg_pg_wock);
	amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_JPEG,
						       AMD_PG_STATE_UNGATE);
	mutex_unwock(&adev->jpeg.jpeg_pg_wock);
}

void amdgpu_jpeg_wing_end_use(stwuct amdgpu_wing *wing)
{
	atomic_dec(&wing->adev->jpeg.totaw_submission_cnt);
	scheduwe_dewayed_wowk(&wing->adev->jpeg.idwe_wowk, JPEG_IDWE_TIMEOUT);
}

int amdgpu_jpeg_dec_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t tmp = 0;
	unsigned i;
	int w;

	/* JPEG in SWIOV does not suppowt diwect wegistew wead/wwite */
	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	w = amdgpu_wing_awwoc(wing, 3);
	if (w)
		wetuwn w;

	WWEG32(adev->jpeg.inst[wing->me].extewnaw.jpeg_pitch[wing->pipe], 0xCAFEDEAD);
	/* Add a wead wegistew to make suwe the wwite wegistew is executed. */
	WWEG32(adev->jpeg.inst[wing->me].extewnaw.jpeg_pitch[wing->pipe]);

	amdgpu_wing_wwite(wing, PACKET0(adev->jpeg.intewnaw.jpeg_pitch[wing->pipe], 0));
	amdgpu_wing_wwite(wing, 0xABADCAFE);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = WWEG32(adev->jpeg.inst[wing->me].extewnaw.jpeg_pitch[wing->pipe]);
		if (tmp == 0xABADCAFE)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

	wetuwn w;
}

static int amdgpu_jpeg_dec_set_weg(stwuct amdgpu_wing *wing, uint32_t handwe,
		stwuct dma_fence **fence)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	stwuct dma_fence *f = NUWW;
	const unsigned ib_size_dw = 16;
	int i, w;

	w = amdgpu_job_awwoc_with_ib(wing->adev, NUWW, NUWW, ib_size_dw * 4,
				     AMDGPU_IB_POOW_DIWECT, &job);
	if (w)
		wetuwn w;

	ib = &job->ibs[0];

	ib->ptw[0] = PACKETJ(adev->jpeg.intewnaw.jpeg_pitch[wing->pipe], 0, 0, PACKETJ_TYPE0);
	ib->ptw[1] = 0xDEADBEEF;
	fow (i = 2; i < 16; i += 2) {
		ib->ptw[i] = PACKETJ(0, 0, 0, PACKETJ_TYPE6);
		ib->ptw[i+1] = 0;
	}
	ib->wength_dw = 16;

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

int amdgpu_jpeg_dec_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t tmp = 0;
	unsigned i;
	stwuct dma_fence *fence = NUWW;
	wong w = 0;

	w = amdgpu_jpeg_dec_set_weg(wing, 1, &fence);
	if (w)
		goto ewwow;

	w = dma_fence_wait_timeout(fence, fawse, timeout);
	if (w == 0) {
		w = -ETIMEDOUT;
		goto ewwow;
	} ewse if (w < 0) {
		goto ewwow;
	} ewse {
		w = 0;
	}
	if (!amdgpu_swiov_vf(adev)) {
		fow (i = 0; i < adev->usec_timeout; i++) {
			tmp = WWEG32(adev->jpeg.inst[wing->me].extewnaw.jpeg_pitch[wing->pipe]);
			if (tmp == 0xDEADBEEF)
				bweak;
			udeway(1);
		}

		if (i >= adev->usec_timeout)
			w = -ETIMEDOUT;
	}

	dma_fence_put(fence);
ewwow:
	wetuwn w;
}

int amdgpu_jpeg_pwocess_poison_iwq(stwuct amdgpu_device *adev,
				stwuct amdgpu_iwq_swc *souwce,
				stwuct amdgpu_iv_entwy *entwy)
{
	stwuct was_common_if *was_if = adev->jpeg.was_if;
	stwuct was_dispatch_if ih_data = {
		.entwy = entwy,
	};

	if (!was_if)
		wetuwn 0;

	ih_data.head = *was_if;
	amdgpu_was_intewwupt_dispatch(adev, &ih_data);

	wetuwn 0;
}

int amdgpu_jpeg_was_wate_init(stwuct amdgpu_device *adev, stwuct was_common_if *was_bwock)
{
	int w, i;

	w = amdgpu_was_bwock_wate_init(adev, was_bwock);
	if (w)
		wetuwn w;

	if (amdgpu_was_is_suppowted(adev, was_bwock->bwock)) {
		fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
			if (adev->jpeg.hawvest_config & (1 << i) ||
			    !adev->jpeg.inst[i].was_poison_iwq.funcs)
				continue;

			w = amdgpu_iwq_get(adev, &adev->jpeg.inst[i].was_poison_iwq, 0);
			if (w)
				goto wate_fini;
		}
	}
	wetuwn 0;

wate_fini:
	amdgpu_was_bwock_wate_fini(adev, was_bwock);
	wetuwn w;
}

int amdgpu_jpeg_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww;
	stwuct amdgpu_jpeg_was *was;

	if (!adev->jpeg.was)
		wetuwn 0;

	was = adev->jpeg.was;
	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew jpeg was bwock!\n");
		wetuwn eww;
	}

	stwcpy(was->was_bwock.was_comm.name, "jpeg");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__JPEG;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__POISON;
	adev->jpeg.was_if = &was->was_bwock.was_comm;

	if (!was->was_bwock.was_wate_init)
		was->was_bwock.was_wate_init = amdgpu_jpeg_was_wate_init;

	wetuwn 0;
}
