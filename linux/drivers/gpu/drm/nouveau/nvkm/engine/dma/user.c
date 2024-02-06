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
#incwude "usew.h"

#incwude <cowe/cwient.h>
#incwude <cowe/gpuobj.h>
#incwude <subdev/fb.h>

#incwude <nvif/cw0002.h>
#incwude <nvif/unpack.h>

static const stwuct nvkm_object_func nvkm_dmaobj_func;
stwuct nvkm_dmaobj *
nvkm_dmaobj_seawch(stwuct nvkm_cwient *cwient, u64 handwe)
{
	stwuct nvkm_object *object;

	object = nvkm_object_seawch(cwient, handwe, &nvkm_dmaobj_func);
	if (IS_EWW(object))
		wetuwn (void *)object;

	wetuwn nvkm_dmaobj(object);
}

static int
nvkm_dmaobj_bind(stwuct nvkm_object *base, stwuct nvkm_gpuobj *gpuobj,
		 int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct nvkm_dmaobj *dmaobj = nvkm_dmaobj(base);
	wetuwn dmaobj->func->bind(dmaobj, gpuobj, awign, pgpuobj);
}

static void *
nvkm_dmaobj_dtow(stwuct nvkm_object *base)
{
	wetuwn nvkm_dmaobj(base);
}

static const stwuct nvkm_object_func
nvkm_dmaobj_func = {
	.dtow = nvkm_dmaobj_dtow,
	.bind = nvkm_dmaobj_bind,
};

int
nvkm_dmaobj_ctow(const stwuct nvkm_dmaobj_func *func, stwuct nvkm_dma *dma,
		 const stwuct nvkm_ocwass *ocwass, void **pdata, u32 *psize,
		 stwuct nvkm_dmaobj *dmaobj)
{
	union {
		stwuct nv_dma_v0 v0;
	} *awgs = *pdata;
	stwuct nvkm_object *pawent = ocwass->pawent;
	void *data = *pdata;
	u32 size = *psize;
	int wet = -ENOSYS;

	nvkm_object_ctow(&nvkm_dmaobj_func, ocwass, &dmaobj->object);
	dmaobj->func = func;
	dmaobj->dma = dma;

	nvif_ioctw(pawent, "cweate dma size %d\n", *psize);
	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, twue))) {
		nvif_ioctw(pawent, "cweate dma vews %d tawget %d access %d "
				   "stawt %016wwx wimit %016wwx\n",
			   awgs->v0.vewsion, awgs->v0.tawget, awgs->v0.access,
			   awgs->v0.stawt, awgs->v0.wimit);
		dmaobj->tawget = awgs->v0.tawget;
		dmaobj->access = awgs->v0.access;
		dmaobj->stawt  = awgs->v0.stawt;
		dmaobj->wimit  = awgs->v0.wimit;
	} ewse
		wetuwn wet;

	*pdata = data;
	*psize = size;

	if (dmaobj->stawt > dmaobj->wimit)
		wetuwn -EINVAW;

	switch (dmaobj->tawget) {
	case NV_DMA_V0_TAWGET_VM:
		dmaobj->tawget = NV_MEM_TAWGET_VM;
		bweak;
	case NV_DMA_V0_TAWGET_VWAM:
		dmaobj->tawget = NV_MEM_TAWGET_VWAM;
		bweak;
	case NV_DMA_V0_TAWGET_PCI:
		dmaobj->tawget = NV_MEM_TAWGET_PCI;
		bweak;
	case NV_DMA_V0_TAWGET_PCI_US:
	case NV_DMA_V0_TAWGET_AGP:
		dmaobj->tawget = NV_MEM_TAWGET_PCI_NOSNOOP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (dmaobj->access) {
	case NV_DMA_V0_ACCESS_VM:
		dmaobj->access = NV_MEM_ACCESS_VM;
		bweak;
	case NV_DMA_V0_ACCESS_WD:
		dmaobj->access = NV_MEM_ACCESS_WO;
		bweak;
	case NV_DMA_V0_ACCESS_WW:
		dmaobj->access = NV_MEM_ACCESS_WO;
		bweak;
	case NV_DMA_V0_ACCESS_WDWW:
		dmaobj->access = NV_MEM_ACCESS_WW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}
