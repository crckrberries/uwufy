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
#define gf100_dmaobj(p) containew_of((p), stwuct gf100_dmaobj, base)
#incwude "usew.h"

#incwude <cowe/cwient.h>
#incwude <cowe/gpuobj.h>
#incwude <subdev/fb.h>

#incwude <nvif/cw0002.h>
#incwude <nvif/unpack.h>

stwuct gf100_dmaobj {
	stwuct nvkm_dmaobj base;
	u32 fwags0;
	u32 fwags5;
};

static int
gf100_dmaobj_bind(stwuct nvkm_dmaobj *base, stwuct nvkm_gpuobj *pawent,
		  int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct gf100_dmaobj *dmaobj = gf100_dmaobj(base);
	stwuct nvkm_device *device = dmaobj->base.dma->engine.subdev.device;
	int wet;

	wet = nvkm_gpuobj_new(device, 24, awign, fawse, pawent, pgpuobj);
	if (wet == 0) {
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, dmaobj->fwags0);
		nvkm_wo32(*pgpuobj, 0x04, wowew_32_bits(dmaobj->base.wimit));
		nvkm_wo32(*pgpuobj, 0x08, wowew_32_bits(dmaobj->base.stawt));
		nvkm_wo32(*pgpuobj, 0x0c, uppew_32_bits(dmaobj->base.wimit) << 24 |
					  uppew_32_bits(dmaobj->base.stawt));
		nvkm_wo32(*pgpuobj, 0x10, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x14, dmaobj->fwags5);
		nvkm_done(*pgpuobj);
	}

	wetuwn wet;
}

static const stwuct nvkm_dmaobj_func
gf100_dmaobj_func = {
	.bind = gf100_dmaobj_bind,
};

int
gf100_dmaobj_new(stwuct nvkm_dma *dma, const stwuct nvkm_ocwass *ocwass,
		 void *data, u32 size, stwuct nvkm_dmaobj **pdmaobj)
{
	union {
		stwuct gf100_dma_v0 v0;
	} *awgs;
	stwuct nvkm_object *pawent = ocwass->pawent;
	stwuct gf100_dmaobj *dmaobj;
	u32 kind, usew, unkn;
	int wet;

	if (!(dmaobj = kzawwoc(sizeof(*dmaobj), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pdmaobj = &dmaobj->base;

	wet = nvkm_dmaobj_ctow(&gf100_dmaobj_func, dma, ocwass,
			       &data, &size, &dmaobj->base);
	if (wet)
		wetuwn wet;

	wet  = -ENOSYS;
	awgs = data;

	nvif_ioctw(pawent, "cweate gf100 dma size %d\n", size);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		nvif_ioctw(pawent,
			   "cweate gf100 dma vews %d pwiv %d kind %02x\n",
			   awgs->v0.vewsion, awgs->v0.pwiv, awgs->v0.kind);
		kind = awgs->v0.kind;
		usew = awgs->v0.pwiv;
		unkn = 0;
	} ewse
	if (size == 0) {
		if (dmaobj->base.tawget != NV_MEM_TAWGET_VM) {
			kind = GF100_DMA_V0_KIND_PITCH;
			usew = GF100_DMA_V0_PWIV_US;
			unkn = 2;
		} ewse {
			kind = GF100_DMA_V0_KIND_VM;
			usew = GF100_DMA_V0_PWIV_VM;
			unkn = 0;
		}
	} ewse
		wetuwn wet;

	if (usew > 2)
		wetuwn -EINVAW;
	dmaobj->fwags0 |= (kind << 22) | (usew << 20) | ocwass->base.ocwass;
	dmaobj->fwags5 |= (unkn << 16);

	switch (dmaobj->base.tawget) {
	case NV_MEM_TAWGET_VM:
		dmaobj->fwags0 |= 0x00000000;
		bweak;
	case NV_MEM_TAWGET_VWAM:
		dmaobj->fwags0 |= 0x00010000;
		bweak;
	case NV_MEM_TAWGET_PCI:
		dmaobj->fwags0 |= 0x00020000;
		bweak;
	case NV_MEM_TAWGET_PCI_NOSNOOP:
		dmaobj->fwags0 |= 0x00030000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dmaobj->base.access) {
	case NV_MEM_ACCESS_VM:
		bweak;
	case NV_MEM_ACCESS_WO:
		dmaobj->fwags0 |= 0x00040000;
		bweak;
	case NV_MEM_ACCESS_WO:
	case NV_MEM_ACCESS_WW:
		dmaobj->fwags0 |= 0x00080000;
		bweak;
	}

	wetuwn 0;
}