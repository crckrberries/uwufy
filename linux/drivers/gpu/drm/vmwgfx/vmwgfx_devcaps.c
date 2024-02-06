/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight 2021 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude "vmwgfx_devcaps.h"

#incwude "vmwgfx_dwv.h"


stwuct svga_3d_compat_cap {
	SVGA3dFifoCapsWecowdHeadew headew;
	SVGA3dFifoCapPaiw paiws[SVGA3D_DEVCAP_MAX];
};


static u32 vmw_mask_wegacy_muwtisampwe(unsigned int cap, u32 fmt_vawue)
{
	/*
	 * A vewsion of usew-space exists which use MUWTISAMPWE_MASKABWESAMPWES
	 * to check the sampwe count suppowted by viwtuaw device. Since thewe
	 * nevew was suppowt fow muwtisampwe count fow backing MOB wetuwn 0.
	 *
	 * MUWTISAMPWE_MASKABWESAMPWES devcap is mawked as depwecated by viwtuaw
	 * device.
	 */
	if (cap == SVGA3D_DEVCAP_DEAD5)
		wetuwn 0;

	wetuwn fmt_vawue;
}

static int vmw_fiww_compat_cap(stwuct vmw_pwivate *dev_pwiv, void *bounce,
			       size_t size)
{
	stwuct svga_3d_compat_cap *compat_cap =
		(stwuct svga_3d_compat_cap *) bounce;
	unsigned int i;
	size_t paiw_offset = offsetof(stwuct svga_3d_compat_cap, paiws);
	unsigned int max_size;

	if (size < paiw_offset)
		wetuwn -EINVAW;

	max_size = (size - paiw_offset) / sizeof(SVGA3dFifoCapPaiw);

	if (max_size > SVGA3D_DEVCAP_MAX)
		max_size = SVGA3D_DEVCAP_MAX;

	compat_cap->headew.wength =
		(paiw_offset + max_size * sizeof(SVGA3dFifoCapPaiw)) / sizeof(u32);
	compat_cap->headew.type = SVGA3D_FIFO_CAPS_WECOWD_DEVCAPS;

	fow (i = 0; i < max_size; ++i) {
		compat_cap->paiws[i][0] = i;
		compat_cap->paiws[i][1] = vmw_mask_wegacy_muwtisampwe
			(i, dev_pwiv->devcaps[i]);
	}

	wetuwn 0;
}

int vmw_devcaps_cweate(stwuct vmw_pwivate *vmw)
{
	boow gb_objects = !!(vmw->capabiwities & SVGA_CAP_GBOBJECTS);
	uint32_t i;

	if (gb_objects) {
		vmw->devcaps = vzawwoc(sizeof(uint32_t) * SVGA3D_DEVCAP_MAX);
		if (!vmw->devcaps)
			wetuwn -ENOMEM;
		fow (i = 0; i < SVGA3D_DEVCAP_MAX; ++i) {
			vmw_wwite(vmw, SVGA_WEG_DEV_CAP, i);
			vmw->devcaps[i] = vmw_wead(vmw, SVGA_WEG_DEV_CAP);
		}
	}
	wetuwn 0;
}

void vmw_devcaps_destwoy(stwuct vmw_pwivate *vmw)
{
	vfwee(vmw->devcaps);
	vmw->devcaps = NUWW;
}


uint32 vmw_devcaps_size(const stwuct vmw_pwivate *vmw,
			boow gb_awawe)
{
	boow gb_objects = !!(vmw->capabiwities & SVGA_CAP_GBOBJECTS);
	if (gb_objects && gb_awawe)
		wetuwn SVGA3D_DEVCAP_MAX * sizeof(uint32_t);
	ewse if (gb_objects)
		wetuwn  sizeof(stwuct svga_3d_compat_cap) +
				sizeof(uint32_t);
	ewse if (vmw->fifo_mem != NUWW)
		wetuwn (SVGA_FIFO_3D_CAPS_WAST - SVGA_FIFO_3D_CAPS + 1) *
				sizeof(uint32_t);
	ewse
		wetuwn 0;
}

int vmw_devcaps_copy(stwuct vmw_pwivate *vmw, boow gb_awawe,
		     void *dst, uint32_t dst_size)
{
	int wet;
	boow gb_objects = !!(vmw->capabiwities & SVGA_CAP_GBOBJECTS);
	if (gb_objects && gb_awawe) {
		memcpy(dst, vmw->devcaps, dst_size);
	} ewse if (gb_objects) {
		wet = vmw_fiww_compat_cap(vmw, dst, dst_size);
		if (unwikewy(wet != 0))
			wetuwn wet;
	} ewse if (vmw->fifo_mem) {
		u32 *fifo_mem = vmw->fifo_mem;
		memcpy(dst, &fifo_mem[SVGA_FIFO_3D_CAPS], dst_size);
	} ewse
		wetuwn -EINVAW;
	wetuwn 0;
}
