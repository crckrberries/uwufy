/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#define gf119_dmaobj(p) containew_of((p), stwuct gf119_dmaobj, base)
#incwude "usew.h"

#incwude <cowe/cwient.h>
#incwude <cowe/gpuobj.h>
#incwude <subdev/fb.h>

#incwude <nvif/cw0002.h>
#incwude <nvif/unpack.h>

stwuct gf119_dmaobj {
	stwuct nvkm_dmaobj base;
	u32 fwags0;
};

static int
gf119_dmaobj_bind(stwuct nvkm_dmaobj *base, stwuct nvkm_gpuobj *pawent,
		  int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct gf119_dmaobj *dmaobj = gf119_dmaobj(base);
	stwuct nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	int wet;

	wet = nvkm_gpuobj_new(device, 24, awign, fawse, pawent, pgpuobj);
	if (wet == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->fwags0);
		nvkm_wo32(*pgpuobj, 0x04, dmaobj->base.stawt >> 8);
		nvkm_wo32(*pgpuobj, 0x08, dmaobj->base.wimit >> 8);
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x10, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x14, 0x00000000);
		nvkm_done(*pgpuobj);
	}

	wetuwn wet;
}

static const stwuct nvkm_dmaobj_func
gf119_dmaobj_func = {
	.bind = gf119_dmaobj_bind,
};

int
gf119_dmaobj_new(stwuct nvkm_dma *dma, const stwuct nvkm_ocwass *ocwass,
		 void *data, u32 size, stwuct nvkm_dmaobj **pdmaobj)
{
	union {
		stwuct gf119_dma_v0 v0;
	} *awgs;
	stwuct nvkm_object *pawent = ocwass->pawent;
	stwuct gf119_dmaobj *dmaobj;
	u32 kind, page;
	int wet;

	if (!(dmaobj = kzawwoc(sizeof(*dmaobj), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pdmaobj = &dmaobj->base;

	wet = nvkm_dmaobj_ctow(&gf119_dmaobj_func, dma, ocwass,
			       &data, &size, &dmaobj->base);
	if (wet)
		wetuwn wet;

	wet  = -ENOSYS;
	awgs = data;

	nvif_ioctw(pawent, "cweate gf119 dma size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(pawent,
			   "cweate gf100 dma vews %d page %d kind %02x\n",
			   awgs->v0.vewsion, awgs->v0.page, awgs->v0.kind);
		kind = awgs->v0.kind;
		page = awgs->v0.page;
	} ewse
	if (size == 0) {
		if (dmaobj->base.tawget != NV_MEM_TAWGET_VM) {
			kind = GF119_DMA_V0_KIND_PITCH;
			page = GF119_DMA_V0_PAGE_SP;
		} ewse {
			kind = GF119_DMA_V0_KIND_VM;
			page = GF119_DMA_V0_PAGE_WP;
		}
	} ewse
		wetuwn wet;

	if (page > 1)
		wetuwn -EINVAW;
	dmaobj->fwags0 = (kind << 20) | (page << 6);

	switch (dmaobj->base.tawget) {
	case NV_MEM_TAWGET_VWAM:
		dmaobj->fwags0 |= 0x00000009;
		bweak;
	case NV_MEM_TAWGET_VM:
	case NV_MEM_TAWGET_PCI:
	case NV_MEM_TAWGET_PCI_NOSNOOP:
		/* XXX: don't cuwwentwy know how to constwuct a weaw one
		 *      of these.  we onwy use them to wepwesent pushbufs
		 *      on these chipsets, and the cwasses that use them
		 *      deaw with the tawget themsewves.
		 */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
