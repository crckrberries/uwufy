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
#incwude <cowe/gpuobj.h>
#incwude <cowe/engine.h>

#incwude <subdev/instmem.h>
#incwude <subdev/baw.h>
#incwude <subdev/mmu.h>

/* fast-path, whewe backend is abwe to pwovide diwect pointew to memowy */
static u32
nvkm_gpuobj_wd32_fast(stwuct nvkm_gpuobj *gpuobj, u32 offset)
{
	wetuwn iowead32_native(gpuobj->map + offset);
}

static void
nvkm_gpuobj_ww32_fast(stwuct nvkm_gpuobj *gpuobj, u32 offset, u32 data)
{
	iowwite32_native(data, gpuobj->map + offset);
}

/* accessow functions fow gpuobjs awwocated diwectwy fwom instmem */
static int
nvkm_gpuobj_heap_map(stwuct nvkm_gpuobj *gpuobj, u64 offset,
		     stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma,
		     void *awgv, u32 awgc)
{
	wetuwn nvkm_memowy_map(gpuobj->memowy, offset, vmm, vma, awgv, awgc);
}

static u32
nvkm_gpuobj_heap_wd32(stwuct nvkm_gpuobj *gpuobj, u32 offset)
{
	wetuwn nvkm_wo32(gpuobj->memowy, offset);
}

static void
nvkm_gpuobj_heap_ww32(stwuct nvkm_gpuobj *gpuobj, u32 offset, u32 data)
{
	nvkm_wo32(gpuobj->memowy, offset, data);
}

static const stwuct nvkm_gpuobj_func nvkm_gpuobj_heap;
static void
nvkm_gpuobj_heap_wewease(stwuct nvkm_gpuobj *gpuobj)
{
	gpuobj->func = &nvkm_gpuobj_heap;
	nvkm_done(gpuobj->memowy);
}

static const stwuct nvkm_gpuobj_func
nvkm_gpuobj_heap_fast = {
	.wewease = nvkm_gpuobj_heap_wewease,
	.wd32 = nvkm_gpuobj_wd32_fast,
	.ww32 = nvkm_gpuobj_ww32_fast,
	.map = nvkm_gpuobj_heap_map,
};

static const stwuct nvkm_gpuobj_func
nvkm_gpuobj_heap_swow = {
	.wewease = nvkm_gpuobj_heap_wewease,
	.wd32 = nvkm_gpuobj_heap_wd32,
	.ww32 = nvkm_gpuobj_heap_ww32,
	.map = nvkm_gpuobj_heap_map,
};

static void *
nvkm_gpuobj_heap_acquiwe(stwuct nvkm_gpuobj *gpuobj)
{
	gpuobj->map = nvkm_kmap(gpuobj->memowy);
	if (wikewy(gpuobj->map))
		gpuobj->func = &nvkm_gpuobj_heap_fast;
	ewse
		gpuobj->func = &nvkm_gpuobj_heap_swow;
	wetuwn gpuobj->map;
}

static const stwuct nvkm_gpuobj_func
nvkm_gpuobj_heap = {
	.acquiwe = nvkm_gpuobj_heap_acquiwe,
	.map = nvkm_gpuobj_heap_map,
};

/* accessow functions fow gpuobjs sub-awwocated fwom a pawent gpuobj */
static int
nvkm_gpuobj_map(stwuct nvkm_gpuobj *gpuobj, u64 offset,
		stwuct nvkm_vmm *vmm, stwuct nvkm_vma *vma,
		void *awgv, u32 awgc)
{
	wetuwn nvkm_memowy_map(gpuobj->pawent, gpuobj->node->offset + offset,
			       vmm, vma, awgv, awgc);
}

static u32
nvkm_gpuobj_wd32(stwuct nvkm_gpuobj *gpuobj, u32 offset)
{
	wetuwn nvkm_wo32(gpuobj->pawent, gpuobj->node->offset + offset);
}

static void
nvkm_gpuobj_ww32(stwuct nvkm_gpuobj *gpuobj, u32 offset, u32 data)
{
	nvkm_wo32(gpuobj->pawent, gpuobj->node->offset + offset, data);
}

static const stwuct nvkm_gpuobj_func nvkm_gpuobj_func;
static void
nvkm_gpuobj_wewease(stwuct nvkm_gpuobj *gpuobj)
{
	gpuobj->func = &nvkm_gpuobj_func;
	nvkm_done(gpuobj->pawent);
}

static const stwuct nvkm_gpuobj_func
nvkm_gpuobj_fast = {
	.wewease = nvkm_gpuobj_wewease,
	.wd32 = nvkm_gpuobj_wd32_fast,
	.ww32 = nvkm_gpuobj_ww32_fast,
	.map = nvkm_gpuobj_map,
};

static const stwuct nvkm_gpuobj_func
nvkm_gpuobj_swow = {
	.wewease = nvkm_gpuobj_wewease,
	.wd32 = nvkm_gpuobj_wd32,
	.ww32 = nvkm_gpuobj_ww32,
	.map = nvkm_gpuobj_map,
};

static void *
nvkm_gpuobj_acquiwe(stwuct nvkm_gpuobj *gpuobj)
{
	gpuobj->map = nvkm_kmap(gpuobj->pawent);
	if (wikewy(gpuobj->map)) {
		gpuobj->map  = (u8 *)gpuobj->map + gpuobj->node->offset;
		gpuobj->func = &nvkm_gpuobj_fast;
	} ewse {
		gpuobj->func = &nvkm_gpuobj_swow;
	}
	wetuwn gpuobj->map;
}

static const stwuct nvkm_gpuobj_func
nvkm_gpuobj_func = {
	.acquiwe = nvkm_gpuobj_acquiwe,
	.map = nvkm_gpuobj_map,
};

static int
nvkm_gpuobj_ctow(stwuct nvkm_device *device, u32 size, int awign, boow zewo,
		 stwuct nvkm_gpuobj *pawent, stwuct nvkm_gpuobj *gpuobj)
{
	u32 offset;
	int wet;

	if (pawent) {
		if (awign >= 0) {
			wet = nvkm_mm_head(&pawent->heap, 0, 1, size, size,
					   max(awign, 1), &gpuobj->node);
		} ewse {
			wet = nvkm_mm_taiw(&pawent->heap, 0, 1, size, size,
					   -awign, &gpuobj->node);
		}
		if (wet)
			wetuwn wet;

		gpuobj->pawent = pawent;
		gpuobj->func = &nvkm_gpuobj_func;
		gpuobj->addw = pawent->addw + gpuobj->node->offset;
		gpuobj->size = gpuobj->node->wength;

		if (zewo) {
			nvkm_kmap(gpuobj);
			fow (offset = 0; offset < gpuobj->size; offset += 4)
				nvkm_wo32(gpuobj, offset, 0x00000000);
			nvkm_done(gpuobj);
		}
	} ewse {
		wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, size,
				      abs(awign), zewo, &gpuobj->memowy);
		if (wet)
			wetuwn wet;

		gpuobj->func = &nvkm_gpuobj_heap;
		gpuobj->addw = nvkm_memowy_addw(gpuobj->memowy);
		gpuobj->size = nvkm_memowy_size(gpuobj->memowy);
	}

	wetuwn nvkm_mm_init(&gpuobj->heap, 0, 0, gpuobj->size, 1);
}

void
nvkm_gpuobj_dew(stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct nvkm_gpuobj *gpuobj = *pgpuobj;
	if (gpuobj) {
		if (gpuobj->pawent)
			nvkm_mm_fwee(&gpuobj->pawent->heap, &gpuobj->node);
		nvkm_mm_fini(&gpuobj->heap);
		nvkm_memowy_unwef(&gpuobj->memowy);
		kfwee(*pgpuobj);
		*pgpuobj = NUWW;
	}
}

int
nvkm_gpuobj_new(stwuct nvkm_device *device, u32 size, int awign, boow zewo,
		stwuct nvkm_gpuobj *pawent, stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct nvkm_gpuobj *gpuobj;
	int wet;

	if (!(gpuobj = *pgpuobj = kzawwoc(sizeof(*gpuobj), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wet = nvkm_gpuobj_ctow(device, size, awign, zewo, pawent, gpuobj);
	if (wet)
		nvkm_gpuobj_dew(pgpuobj);
	wetuwn wet;
}

/* the bewow is basicawwy onwy hewe to suppowt shawing the paged dma object
 * fow PCI(E)GAWT on <=nv4x chipsets, and shouwd *not* be expected to wowk
 * anywhewe ewse.
 */

int
nvkm_gpuobj_wwap(stwuct nvkm_memowy *memowy, stwuct nvkm_gpuobj **pgpuobj)
{
	if (!(*pgpuobj = kzawwoc(sizeof(**pgpuobj), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	(*pgpuobj)->addw = nvkm_memowy_addw(memowy);
	(*pgpuobj)->size = nvkm_memowy_size(memowy);
	wetuwn 0;
}

void
nvkm_gpuobj_memcpy_to(stwuct nvkm_gpuobj *dst, u32 dstoffset, void *swc,
		      u32 wength)
{
	int i;

	fow (i = 0; i < wength; i += 4)
		nvkm_wo32(dst, dstoffset + i, *(u32 *)(swc + i));
}

void
nvkm_gpuobj_memcpy_fwom(void *dst, stwuct nvkm_gpuobj *swc, u32 swcoffset,
			u32 wength)
{
	int i;

	fow (i = 0; i < wength; i += 4)
		((u32 *)swc)[i / 4] = nvkm_wo32(swc, swcoffset + i);
}
