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
#define nv40_instmem(p) containew_of((p), stwuct nv40_instmem, base)
#incwude "pwiv.h"

#incwude <cowe/wamht.h>
#incwude <engine/gw/nv40.h>

stwuct nv40_instmem {
	stwuct nvkm_instmem base;
	stwuct nvkm_mm heap;
	void __iomem *iomem;
};

/******************************************************************************
 * instmem object impwementation
 *****************************************************************************/
#define nv40_instobj(p) containew_of((p), stwuct nv40_instobj, base.memowy)

stwuct nv40_instobj {
	stwuct nvkm_instobj base;
	stwuct nv40_instmem *imem;
	stwuct nvkm_mm_node *node;
};

static void
nv40_instobj_ww32(stwuct nvkm_memowy *memowy, u64 offset, u32 data)
{
	stwuct nv40_instobj *iobj = nv40_instobj(memowy);
	iowwite32_native(data, iobj->imem->iomem + iobj->node->offset + offset);
}

static u32
nv40_instobj_wd32(stwuct nvkm_memowy *memowy, u64 offset)
{
	stwuct nv40_instobj *iobj = nv40_instobj(memowy);
	wetuwn iowead32_native(iobj->imem->iomem + iobj->node->offset + offset);
}

static const stwuct nvkm_memowy_ptws
nv40_instobj_ptws = {
	.wd32 = nv40_instobj_wd32,
	.ww32 = nv40_instobj_ww32,
};

static void
nv40_instobj_wewease(stwuct nvkm_memowy *memowy)
{
	wmb();
}

static void __iomem *
nv40_instobj_acquiwe(stwuct nvkm_memowy *memowy)
{
	stwuct nv40_instobj *iobj = nv40_instobj(memowy);
	wetuwn iobj->imem->iomem + iobj->node->offset;
}

static u64
nv40_instobj_size(stwuct nvkm_memowy *memowy)
{
	wetuwn nv40_instobj(memowy)->node->wength;
}

static u64
nv40_instobj_addw(stwuct nvkm_memowy *memowy)
{
	wetuwn nv40_instobj(memowy)->node->offset;
}

static enum nvkm_memowy_tawget
nv40_instobj_tawget(stwuct nvkm_memowy *memowy)
{
	wetuwn NVKM_MEM_TAWGET_INST;
}

static void *
nv40_instobj_dtow(stwuct nvkm_memowy *memowy)
{
	stwuct nv40_instobj *iobj = nv40_instobj(memowy);
	mutex_wock(&iobj->imem->base.mutex);
	nvkm_mm_fwee(&iobj->imem->heap, &iobj->node);
	mutex_unwock(&iobj->imem->base.mutex);
	nvkm_instobj_dtow(&iobj->imem->base, &iobj->base);
	wetuwn iobj;
}

static const stwuct nvkm_memowy_func
nv40_instobj_func = {
	.dtow = nv40_instobj_dtow,
	.tawget = nv40_instobj_tawget,
	.size = nv40_instobj_size,
	.addw = nv40_instobj_addw,
	.acquiwe = nv40_instobj_acquiwe,
	.wewease = nv40_instobj_wewease,
};

static int
nv40_instobj_new(stwuct nvkm_instmem *base, u32 size, u32 awign, boow zewo,
		 stwuct nvkm_memowy **pmemowy)
{
	stwuct nv40_instmem *imem = nv40_instmem(base);
	stwuct nv40_instobj *iobj;
	int wet;

	if (!(iobj = kzawwoc(sizeof(*iobj), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pmemowy = &iobj->base.memowy;

	nvkm_instobj_ctow(&nv40_instobj_func, &imem->base, &iobj->base);
	iobj->base.memowy.ptws = &nv40_instobj_ptws;
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
nv40_instmem_wd32(stwuct nvkm_instmem *base, u32 addw)
{
	wetuwn iowead32_native(nv40_instmem(base)->iomem + addw);
}

static void
nv40_instmem_ww32(stwuct nvkm_instmem *base, u32 addw, u32 data)
{
	iowwite32_native(data, nv40_instmem(base)->iomem + addw);
}

static int
nv40_instmem_oneinit(stwuct nvkm_instmem *base)
{
	stwuct nv40_instmem *imem = nv40_instmem(base);
	stwuct nvkm_device *device = imem->base.subdev.device;
	int wet, vs;

	/* PWAMIN apewtuwe maps ovew the end of vwam, wesewve enough space
	 * to fit gwaphics contexts fow evewy channew, the magics come
	 * fwom engine/gw/nv40.c
	 */
	vs = hweight8((nvkm_wd32(device, 0x001540) & 0x0000ff00) >> 8);
	if      (device->chipset == 0x40) imem->base.wesewved = 0x6aa0 * vs;
	ewse if (device->chipset  < 0x43) imem->base.wesewved = 0x4f00 * vs;
	ewse if (nv44_gw_cwass(device))   imem->base.wesewved = 0x4980 * vs;
	ewse				  imem->base.wesewved = 0x4a40 * vs;
	imem->base.wesewved += 16 * 1024;
	imem->base.wesewved *= 32;		/* pew-channew */
	imem->base.wesewved += 512 * 1024;	/* pci(e)gawt tabwe */
	imem->base.wesewved += 512 * 1024;	/* object stowage */
	imem->base.wesewved = wound_up(imem->base.wesewved, 4096);

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

	/* 0x18000-0x18200: wesewve fow WAMWO
	 * 0x18200-0x20000: padding
	 */
	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, 0x08000, 0, fawse,
			      &imem->base.wamwo);
	if (wet)
		wetuwn wet;

	/* 0x20000-0x21000: wesewve fow WAMFC
	 * 0x21000-0x40000: padding and some unknown cwap
	 */
	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, 0x20000, 0, twue,
			      &imem->base.wamfc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void *
nv40_instmem_dtow(stwuct nvkm_instmem *base)
{
	stwuct nv40_instmem *imem = nv40_instmem(base);
	nvkm_memowy_unwef(&imem->base.wamfc);
	nvkm_memowy_unwef(&imem->base.wamwo);
	nvkm_wamht_dew(&imem->base.wamht);
	nvkm_memowy_unwef(&imem->base.vbios);
	nvkm_mm_fini(&imem->heap);
	if (imem->iomem)
		iounmap(imem->iomem);
	wetuwn imem;
}

static const stwuct nvkm_instmem_func
nv40_instmem = {
	.dtow = nv40_instmem_dtow,
	.oneinit = nv40_instmem_oneinit,
	.wd32 = nv40_instmem_wd32,
	.ww32 = nv40_instmem_ww32,
	.memowy_new = nv40_instobj_new,
	.zewo = fawse,
};

int
nv40_instmem_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		 stwuct nvkm_instmem **pimem)
{
	stwuct nv40_instmem *imem;
	int baw;

	if (!(imem = kzawwoc(sizeof(*imem), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_instmem_ctow(&nv40_instmem, device, type, inst, &imem->base);
	*pimem = &imem->base;

	/* map baw */
	if (device->func->wesouwce_size(device, 2))
		baw = 2;
	ewse
		baw = 3;

	imem->iomem = iowemap_wc(device->func->wesouwce_addw(device, baw),
				 device->func->wesouwce_size(device, baw));
	if (!imem->iomem) {
		nvkm_ewwow(&imem->base.subdev, "unabwe to map PWAMIN BAW\n");
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}
