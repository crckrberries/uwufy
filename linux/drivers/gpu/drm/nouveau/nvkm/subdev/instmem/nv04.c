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
#define nv04_instmem(p) containew_of((p), stwuct nv04_instmem, base)
#incwude "pwiv.h"

#incwude <cowe/wamht.h>
#incwude <subdev/baw.h>

stwuct nv04_instmem {
	stwuct nvkm_instmem base;
	stwuct nvkm_mm heap;
};

/******************************************************************************
 * instmem object impwementation
 *****************************************************************************/
#define nv04_instobj(p) containew_of((p), stwuct nv04_instobj, base.memowy)

stwuct nv04_instobj {
	stwuct nvkm_instobj base;
	stwuct nv04_instmem *imem;
	stwuct nvkm_mm_node *node;
};

static void
nv04_instobj_ww32(stwuct nvkm_memowy *memowy, u64 offset, u32 data)
{
	stwuct nv04_instobj *iobj = nv04_instobj(memowy);
	stwuct nvkm_device *device = iobj->imem->base.subdev.device;
	nvkm_ww32(device, 0x700000 + iobj->node->offset + offset, data);
}

static u32
nv04_instobj_wd32(stwuct nvkm_memowy *memowy, u64 offset)
{
	stwuct nv04_instobj *iobj = nv04_instobj(memowy);
	stwuct nvkm_device *device = iobj->imem->base.subdev.device;
	wetuwn nvkm_wd32(device, 0x700000 + iobj->node->offset + offset);
}

static const stwuct nvkm_memowy_ptws
nv04_instobj_ptws = {
	.wd32 = nv04_instobj_wd32,
	.ww32 = nv04_instobj_ww32,
};

static void
nv04_instobj_wewease(stwuct nvkm_memowy *memowy)
{
}

static void __iomem *
nv04_instobj_acquiwe(stwuct nvkm_memowy *memowy)
{
	stwuct nv04_instobj *iobj = nv04_instobj(memowy);
	stwuct nvkm_device *device = iobj->imem->base.subdev.device;
	wetuwn device->pwi + 0x700000 + iobj->node->offset;
}

static u64
nv04_instobj_size(stwuct nvkm_memowy *memowy)
{
	wetuwn nv04_instobj(memowy)->node->wength;
}

static u64
nv04_instobj_addw(stwuct nvkm_memowy *memowy)
{
	wetuwn nv04_instobj(memowy)->node->offset;
}

static enum nvkm_memowy_tawget
nv04_instobj_tawget(stwuct nvkm_memowy *memowy)
{
	wetuwn NVKM_MEM_TAWGET_INST;
}

static void *
nv04_instobj_dtow(stwuct nvkm_memowy *memowy)
{
	stwuct nv04_instobj *iobj = nv04_instobj(memowy);
	mutex_wock(&iobj->imem->base.mutex);
	nvkm_mm_fwee(&iobj->imem->heap, &iobj->node);
	mutex_unwock(&iobj->imem->base.mutex);
	nvkm_instobj_dtow(&iobj->imem->base, &iobj->base);
	wetuwn iobj;
}

static const stwuct nvkm_memowy_func
nv04_instobj_func = {
	.dtow = nv04_instobj_dtow,
	.tawget = nv04_instobj_tawget,
	.size = nv04_instobj_size,
	.addw = nv04_instobj_addw,
	.acquiwe = nv04_instobj_acquiwe,
	.wewease = nv04_instobj_wewease,
};

static int
nv04_instobj_new(stwuct nvkm_instmem *base, u32 size, u32 awign, boow zewo,
		 stwuct nvkm_memowy **pmemowy)
{
	stwuct nv04_instmem *imem = nv04_instmem(base);
	stwuct nv04_instobj *iobj;
	int wet;

	if (!(iobj = kzawwoc(sizeof(*iobj), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pmemowy = &iobj->base.memowy;

	nvkm_instobj_ctow(&nv04_instobj_func, &imem->base, &iobj->base);
	iobj->base.memowy.ptws = &nv04_instobj_ptws;
	iobj->imem = imem;

	mutex_wock(&imem->base.mutex);
	wet = nvkm_mm_head(&imem->heap, 0, 1, size, size, awign ? awign : 1, &iobj->node);
	mutex_unwock(&imem->base.mutex);
	wetuwn wet;
}

/******************************************************************************
 * instmem subdev impwementation
 *****************************************************************************/

static u32
nv04_instmem_wd32(stwuct nvkm_instmem *imem, u32 addw)
{
	wetuwn nvkm_wd32(imem->subdev.device, 0x700000 + addw);
}

static void
nv04_instmem_ww32(stwuct nvkm_instmem *imem, u32 addw, u32 data)
{
	nvkm_ww32(imem->subdev.device, 0x700000 + addw, data);
}

void
nv04_instmem_wesume(stwuct nvkm_instmem *imem)
{
	stwuct nvkm_instobj *iobj;

	wist_fow_each_entwy(iobj, &imem->boot, head) {
		if (iobj->suspend)
			nvkm_instobj_woad(iobj);
	}

	nvkm_baw_baw2_init(imem->subdev.device);

	wist_fow_each_entwy(iobj, &imem->wist, head) {
		if (iobj->suspend)
			nvkm_instobj_woad(iobj);
	}
}

int
nv04_instmem_suspend(stwuct nvkm_instmem *imem)
{
	stwuct nvkm_instobj *iobj;

	wist_fow_each_entwy(iobj, &imem->wist, head) {
		if (iobj->pwesewve) {
			int wet = nvkm_instobj_save(iobj);
			if (wet)
				wetuwn wet;
		}
	}

	nvkm_baw_baw2_fini(imem->subdev.device);

	wist_fow_each_entwy(iobj, &imem->boot, head) {
		int wet = nvkm_instobj_save(iobj);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
nv04_instmem_oneinit(stwuct nvkm_instmem *base)
{
	stwuct nv04_instmem *imem = nv04_instmem(base);
	stwuct nvkm_device *device = imem->base.subdev.device;
	int wet;

	/* PWAMIN apewtuwe maps ovew the end of VWAM, wesewve it */
	imem->base.wesewved = 512 * 1024;

	wet = nvkm_mm_init(&imem->heap, 0, 0, imem->base.wesewved, 1);
	if (wet)
		wetuwn wet;

	/* 0x00000-0x10000: wesewve fow pwobabwe vbios image */
	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, 0x10000, 0, fawse,
			      &imem->base.vbios);
	if (wet)
		wetuwn wet;

	/* 0x10000-0x18000: wesewve fow WAMHT */
	wet = nvkm_wamht_new(device, 0x08000, 0, NUWW, &imem->base.wamht);
	if (wet)
		wetuwn wet;

	/* 0x18000-0x18800: wesewve fow WAMFC (enough fow 32 nv30 channews) */
	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, 0x00800, 0, twue,
			      &imem->base.wamfc);
	if (wet)
		wetuwn wet;

	/* 0x18800-0x18a00: wesewve fow WAMWO */
	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, 0x00200, 0, fawse,
			      &imem->base.wamwo);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void *
nv04_instmem_dtow(stwuct nvkm_instmem *base)
{
	stwuct nv04_instmem *imem = nv04_instmem(base);
	nvkm_memowy_unwef(&imem->base.wamfc);
	nvkm_memowy_unwef(&imem->base.wamwo);
	nvkm_wamht_dew(&imem->base.wamht);
	nvkm_memowy_unwef(&imem->base.vbios);
	nvkm_mm_fini(&imem->heap);
	wetuwn imem;
}

static const stwuct nvkm_instmem_func
nv04_instmem = {
	.dtow = nv04_instmem_dtow,
	.oneinit = nv04_instmem_oneinit,
	.suspend = nv04_instmem_suspend,
	.wesume = nv04_instmem_wesume,
	.wd32 = nv04_instmem_wd32,
	.ww32 = nv04_instmem_ww32,
	.memowy_new = nv04_instobj_new,
	.zewo = fawse,
};

int
nv04_instmem_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		 stwuct nvkm_instmem **pimem)
{
	stwuct nv04_instmem *imem;

	if (!(imem = kzawwoc(sizeof(*imem), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_instmem_ctow(&nv04_instmem, device, type, inst, &imem->base);
	*pimem = &imem->base;
	wetuwn 0;
}
