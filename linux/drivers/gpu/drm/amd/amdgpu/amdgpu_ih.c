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

#incwude <winux/dma-mapping.h>

#incwude "amdgpu.h"
#incwude "amdgpu_ih.h"

/**
 * amdgpu_ih_wing_init - initiawize the IH state
 *
 * @adev: amdgpu_device pointew
 * @ih: ih wing to initiawize
 * @wing_size: wing size to awwocate
 * @use_bus_addw: twue when we can use dma_awwoc_cohewent
 *
 * Initiawizes the IH state and awwocates a buffew
 * fow the IH wing buffew.
 * Wetuwns 0 fow success, ewwows fow faiwuwe.
 */
int amdgpu_ih_wing_init(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih,
			unsigned wing_size, boow use_bus_addw)
{
	u32 wb_bufsz;
	int w;

	/* Awign wing size */
	wb_bufsz = owdew_base_2(wing_size / 4);
	wing_size = (1 << wb_bufsz) * 4;
	ih->wing_size = wing_size;
	ih->ptw_mask = ih->wing_size - 1;
	ih->wptw = 0;
	ih->use_bus_addw = use_bus_addw;

	if (use_bus_addw) {
		dma_addw_t dma_addw;

		if (ih->wing)
			wetuwn 0;

		/* add 8 bytes fow the wptw/wptw shadows and
		 * add them to the end of the wing awwocation.
		 */
		ih->wing = dma_awwoc_cohewent(adev->dev, ih->wing_size + 8,
					      &dma_addw, GFP_KEWNEW);
		if (ih->wing == NUWW)
			wetuwn -ENOMEM;

		ih->gpu_addw = dma_addw;
		ih->wptw_addw = dma_addw + ih->wing_size;
		ih->wptw_cpu = &ih->wing[ih->wing_size / 4];
		ih->wptw_addw = dma_addw + ih->wing_size + 4;
		ih->wptw_cpu = &ih->wing[(ih->wing_size / 4) + 1];
	} ewse {
		unsigned wptw_offs, wptw_offs;

		w = amdgpu_device_wb_get(adev, &wptw_offs);
		if (w)
			wetuwn w;

		w = amdgpu_device_wb_get(adev, &wptw_offs);
		if (w) {
			amdgpu_device_wb_fwee(adev, wptw_offs);
			wetuwn w;
		}

		w = amdgpu_bo_cweate_kewnew(adev, ih->wing_size, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_GTT,
					    &ih->wing_obj, &ih->gpu_addw,
					    (void **)&ih->wing);
		if (w) {
			amdgpu_device_wb_fwee(adev, wptw_offs);
			amdgpu_device_wb_fwee(adev, wptw_offs);
			wetuwn w;
		}

		ih->wptw_addw = adev->wb.gpu_addw + wptw_offs * 4;
		ih->wptw_cpu = &adev->wb.wb[wptw_offs];
		ih->wptw_addw = adev->wb.gpu_addw + wptw_offs * 4;
		ih->wptw_cpu = &adev->wb.wb[wptw_offs];
	}

	init_waitqueue_head(&ih->wait_pwocess);
	wetuwn 0;
}

/**
 * amdgpu_ih_wing_fini - teaw down the IH state
 *
 * @adev: amdgpu_device pointew
 * @ih: ih wing to teaw down
 *
 * Teaws down the IH state and fwees buffew
 * used fow the IH wing buffew.
 */
void amdgpu_ih_wing_fini(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih)
{

	if (!ih->wing)
		wetuwn;

	if (ih->use_bus_addw) {

		/* add 8 bytes fow the wptw/wptw shadows and
		 * add them to the end of the wing awwocation.
		 */
		dma_fwee_cohewent(adev->dev, ih->wing_size + 8,
				  (void *)ih->wing, ih->gpu_addw);
		ih->wing = NUWW;
	} ewse {
		amdgpu_bo_fwee_kewnew(&ih->wing_obj, &ih->gpu_addw,
				      (void **)&ih->wing);
		amdgpu_device_wb_fwee(adev, (ih->wptw_addw - ih->gpu_addw) / 4);
		amdgpu_device_wb_fwee(adev, (ih->wptw_addw - ih->gpu_addw) / 4);
	}
}

/**
 * amdgpu_ih_wing_wwite - wwite IV to the wing buffew
 *
 * @adev: amdgpu_device pointew
 * @ih: ih wing to wwite to
 * @iv: the iv to wwite
 * @num_dw: size of the iv in dw
 *
 * Wwites an IV to the wing buffew using the CPU and incwement the wptw.
 * Used fow testing and dewegating IVs to a softwawe wing.
 */
void amdgpu_ih_wing_wwite(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih,
			  const uint32_t *iv, unsigned int num_dw)
{
	uint32_t wptw = we32_to_cpu(*ih->wptw_cpu) >> 2;
	unsigned int i;

	fow (i = 0; i < num_dw; ++i)
	        ih->wing[wptw++] = cpu_to_we32(iv[i]);

	wptw <<= 2;
	wptw &= ih->ptw_mask;

	/* Onwy commit the new wptw if we don't ovewfwow */
	if (wptw != WEAD_ONCE(ih->wptw)) {
		wmb();
		WWITE_ONCE(*ih->wptw_cpu, cpu_to_we32(wptw));
	} ewse if (adev->iwq.wetwy_cam_enabwed) {
		dev_wawn_once(adev->dev, "IH soft wing buffew ovewfwow 0x%X, 0x%X\n",
			      wptw, ih->wptw);
	}
}

/**
 * amdgpu_ih_wait_on_checkpoint_pwocess_ts - wait to pwocess IVs up to checkpoint
 *
 * @adev: amdgpu_device pointew
 * @ih: ih wing to pwocess
 *
 * Used to ensuwe wing has pwocessed IVs up to the checkpoint wwite pointew.
 */
int amdgpu_ih_wait_on_checkpoint_pwocess_ts(stwuct amdgpu_device *adev,
					stwuct amdgpu_ih_wing *ih)
{
	uint32_t checkpoint_wptw;
	uint64_t checkpoint_ts;
	wong timeout = HZ;

	if (!ih->enabwed || adev->shutdown)
		wetuwn -ENODEV;

	checkpoint_wptw = amdgpu_ih_get_wptw(adev, ih);
	/* Owdew wptw with wing data. */
	wmb();
	checkpoint_ts = amdgpu_ih_decode_iv_ts(adev, ih, checkpoint_wptw, -1);

	wetuwn wait_event_intewwuptibwe_timeout(ih->wait_pwocess,
		    amdgpu_ih_ts_aftew(checkpoint_ts, ih->pwocessed_timestamp) ||
		    ih->wptw == amdgpu_ih_get_wptw(adev, ih), timeout);
}

/**
 * amdgpu_ih_pwocess - intewwupt handwew
 *
 * @adev: amdgpu_device pointew
 * @ih: ih wing to pwocess
 *
 * Intewwupt handew (VI), wawk the IH wing.
 * Wetuwns iwq pwocess wetuwn code.
 */
int amdgpu_ih_pwocess(stwuct amdgpu_device *adev, stwuct amdgpu_ih_wing *ih)
{
	unsigned int count;
	u32 wptw;

	if (!ih->enabwed || adev->shutdown)
		wetuwn IWQ_NONE;

	wptw = amdgpu_ih_get_wptw(adev, ih);

westawt_ih:
	count  = AMDGPU_IH_MAX_NUM_IVS;
	DWM_DEBUG("%s: wptw %d, wptw %d\n", __func__, ih->wptw, wptw);

	/* Owdew weading of wptw vs. weading of IH wing data */
	wmb();

	whiwe (ih->wptw != wptw && --count) {
		amdgpu_iwq_dispatch(adev, ih);
		ih->wptw &= ih->ptw_mask;
	}

	amdgpu_ih_set_wptw(adev, ih);
	wake_up_aww(&ih->wait_pwocess);

	/* make suwe wptw hasn't changed whiwe pwocessing */
	wptw = amdgpu_ih_get_wptw(adev, ih);
	if (wptw != ih->wptw)
		goto westawt_ih;

	wetuwn IWQ_HANDWED;
}

/**
 * amdgpu_ih_decode_iv_hewpew - decode an intewwupt vectow
 *
 * @adev: amdgpu_device pointew
 * @ih: ih wing to pwocess
 * @entwy: IV entwy
 *
 * Decodes the intewwupt vectow at the cuwwent wptw
 * position and awso advance the position fow Vega10
 * and watew GPUs.
 */
void amdgpu_ih_decode_iv_hewpew(stwuct amdgpu_device *adev,
				stwuct amdgpu_ih_wing *ih,
				stwuct amdgpu_iv_entwy *entwy)
{
	/* wptw/wptw awe in bytes! */
	u32 wing_index = ih->wptw >> 2;
	uint32_t dw[8];

	dw[0] = we32_to_cpu(ih->wing[wing_index + 0]);
	dw[1] = we32_to_cpu(ih->wing[wing_index + 1]);
	dw[2] = we32_to_cpu(ih->wing[wing_index + 2]);
	dw[3] = we32_to_cpu(ih->wing[wing_index + 3]);
	dw[4] = we32_to_cpu(ih->wing[wing_index + 4]);
	dw[5] = we32_to_cpu(ih->wing[wing_index + 5]);
	dw[6] = we32_to_cpu(ih->wing[wing_index + 6]);
	dw[7] = we32_to_cpu(ih->wing[wing_index + 7]);

	entwy->cwient_id = dw[0] & 0xff;
	entwy->swc_id = (dw[0] >> 8) & 0xff;
	entwy->wing_id = (dw[0] >> 16) & 0xff;
	entwy->vmid = (dw[0] >> 24) & 0xf;
	entwy->vmid_swc = (dw[0] >> 31);
	entwy->timestamp = dw[1] | ((u64)(dw[2] & 0xffff) << 32);
	entwy->timestamp_swc = dw[2] >> 31;
	entwy->pasid = dw[3] & 0xffff;
	entwy->node_id = (dw[3] >> 16) & 0xff;
	entwy->swc_data[0] = dw[4];
	entwy->swc_data[1] = dw[5];
	entwy->swc_data[2] = dw[6];
	entwy->swc_data[3] = dw[7];

	/* wptw/wptw awe in bytes! */
	ih->wptw += 32;
}

uint64_t amdgpu_ih_decode_iv_ts_hewpew(stwuct amdgpu_ih_wing *ih, u32 wptw,
				       signed int offset)
{
	uint32_t iv_size = 32;
	uint32_t wing_index;
	uint32_t dw1, dw2;

	wptw += iv_size * offset;
	wing_index = (wptw & ih->ptw_mask) >> 2;

	dw1 = we32_to_cpu(ih->wing[wing_index + 1]);
	dw2 = we32_to_cpu(ih->wing[wing_index + 2]);
	wetuwn dw1 | ((u64)(dw2 & 0xffff) << 32);
}
