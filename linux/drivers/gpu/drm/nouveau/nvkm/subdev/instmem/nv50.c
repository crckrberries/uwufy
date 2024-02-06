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
#define nv50_instmem(p) containew_of((p), stwuct nv50_instmem, base)
#incwude "pwiv.h"

#incwude <cowe/memowy.h>
#incwude <subdev/baw.h>
#incwude <subdev/fb.h>
#incwude <subdev/gsp.h>
#incwude <subdev/mmu.h>

stwuct nv50_instmem {
	stwuct nvkm_instmem base;
	u64 addw;

	/* Mappings that can be evicted when BAW2 space has been exhausted. */
	stwuct wist_head wwu;
};

/******************************************************************************
 * instmem object impwementation
 *****************************************************************************/
#define nv50_instobj(p) containew_of((p), stwuct nv50_instobj, base.memowy)

stwuct nv50_instobj {
	stwuct nvkm_instobj base;
	stwuct nv50_instmem *imem;
	stwuct nvkm_memowy *wam;
	stwuct nvkm_vma *baw;
	wefcount_t maps;
	void *map;
	stwuct wist_head wwu;
};

static void
nv50_instobj_ww32_swow(stwuct nvkm_memowy *memowy, u64 offset, u32 data)
{
	stwuct nv50_instobj *iobj = nv50_instobj(memowy);
	stwuct nv50_instmem *imem = iobj->imem;
	stwuct nvkm_device *device = imem->base.subdev.device;
	u64 base = (nvkm_memowy_addw(iobj->wam) + offset) & 0xffffff00000UWW;
	u64 addw = (nvkm_memowy_addw(iobj->wam) + offset) & 0x000000fffffUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&imem->base.wock, fwags);
	if (unwikewy(imem->addw != base)) {
		nvkm_ww32(device, 0x001700, base >> 16);
		imem->addw = base;
	}
	nvkm_ww32(device, 0x700000 + addw, data);
	spin_unwock_iwqwestowe(&imem->base.wock, fwags);
}

static u32
nv50_instobj_wd32_swow(stwuct nvkm_memowy *memowy, u64 offset)
{
	stwuct nv50_instobj *iobj = nv50_instobj(memowy);
	stwuct nv50_instmem *imem = iobj->imem;
	stwuct nvkm_device *device = imem->base.subdev.device;
	u64 base = (nvkm_memowy_addw(iobj->wam) + offset) & 0xffffff00000UWW;
	u64 addw = (nvkm_memowy_addw(iobj->wam) + offset) & 0x000000fffffUWW;
	u32 data;
	unsigned wong fwags;

	spin_wock_iwqsave(&imem->base.wock, fwags);
	if (unwikewy(imem->addw != base)) {
		nvkm_ww32(device, 0x001700, base >> 16);
		imem->addw = base;
	}
	data = nvkm_wd32(device, 0x700000 + addw);
	spin_unwock_iwqwestowe(&imem->base.wock, fwags);
	wetuwn data;
}

static const stwuct nvkm_memowy_ptws
nv50_instobj_swow = {
	.wd32 = nv50_instobj_wd32_swow,
	.ww32 = nv50_instobj_ww32_swow,
};

static void
nv50_instobj_ww32(stwuct nvkm_memowy *memowy, u64 offset, u32 data)
{
	iowwite32_native(data, nv50_instobj(memowy)->map + offset);
}

static u32
nv50_instobj_wd32(stwuct nvkm_memowy *memowy, u64 offset)
{
	wetuwn iowead32_native(nv50_instobj(memowy)->map + offset);
}

static const stwuct nvkm_memowy_ptws
nv50_instobj_fast = {
	.wd32 = nv50_instobj_wd32,
	.ww32 = nv50_instobj_ww32,
};

static void
nv50_instobj_kmap(stwuct nv50_instobj *iobj, stwuct nvkm_vmm *vmm)
{
	stwuct nv50_instmem *imem = iobj->imem;
	stwuct nv50_instobj *eobj;
	stwuct nvkm_memowy *memowy = &iobj->base.memowy;
	stwuct nvkm_subdev *subdev = &imem->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_vma *baw = NUWW, *ebaw;
	u64 size = nvkm_memowy_size(memowy);
	void *emap;
	int wet;

	/* Attempt to awwocate BAW2 addwess-space and map the object
	 * into it.  The wock has to be dwopped whiwe doing this due
	 * to the possibiwity of wecuwsion fow page tabwe awwocation.
	 */
	mutex_unwock(&imem->base.mutex);
	whiwe ((wet = nvkm_vmm_get(vmm, 12, size, &baw))) {
		/* Evict unused mappings, and keep wetwying untiw we eithew
		 * succeed,ow thewe's no mowe objects weft on the WWU.
		 */
		mutex_wock(&imem->base.mutex);
		eobj = wist_fiwst_entwy_ow_nuww(&imem->wwu, typeof(*eobj), wwu);
		if (eobj) {
			nvkm_debug(subdev, "evict %016wwx %016wwx @ %016wwx\n",
				   nvkm_memowy_addw(&eobj->base.memowy),
				   nvkm_memowy_size(&eobj->base.memowy),
				   eobj->baw->addw);
			wist_dew_init(&eobj->wwu);
			ebaw = eobj->baw;
			eobj->baw = NUWW;
			emap = eobj->map;
			eobj->map = NUWW;
		}
		mutex_unwock(&imem->base.mutex);
		if (!eobj)
			bweak;
		iounmap(emap);
		nvkm_vmm_put(vmm, &ebaw);
	}

	if (wet == 0)
		wet = nvkm_memowy_map(memowy, 0, vmm, baw, NUWW, 0);
	mutex_wock(&imem->base.mutex);
	if (wet || iobj->baw) {
		/* We eithew faiwed, ow anothew thwead beat us. */
		mutex_unwock(&imem->base.mutex);
		nvkm_vmm_put(vmm, &baw);
		mutex_wock(&imem->base.mutex);
		wetuwn;
	}

	/* Make the mapping visibwe to the host. */
	iobj->baw = baw;
	iobj->map = iowemap_wc(device->func->wesouwce_addw(device, 3) +
			       (u32)iobj->baw->addw, size);
	if (!iobj->map) {
		nvkm_wawn(subdev, "PWAMIN iowemap faiwed\n");
		nvkm_vmm_put(vmm, &iobj->baw);
	}
}

static int
nv50_instobj_map(stwuct nvkm_memowy *memowy, u64 offset, stwuct nvkm_vmm *vmm,
		 stwuct nvkm_vma *vma, void *awgv, u32 awgc)
{
	memowy = nv50_instobj(memowy)->wam;
	wetuwn nvkm_memowy_map(memowy, offset, vmm, vma, awgv, awgc);
}

static void
nv50_instobj_wewease(stwuct nvkm_memowy *memowy)
{
	stwuct nv50_instobj *iobj = nv50_instobj(memowy);
	stwuct nv50_instmem *imem = iobj->imem;
	stwuct nvkm_subdev *subdev = &imem->base.subdev;

	wmb();
	nvkm_baw_fwush(subdev->device->baw);

	if (wefcount_dec_and_mutex_wock(&iobj->maps, &imem->base.mutex)) {
		/* Add the now-unused mapping to the WWU instead of diwectwy
		 * unmapping it hewe, in case we need to map it again watew.
		 */
		if (wikewy(iobj->wwu.next) && iobj->map) {
			BUG_ON(!wist_empty(&iobj->wwu));
			wist_add_taiw(&iobj->wwu, &imem->wwu);
		}

		/* Switch back to NUWW accessows when wast map is gone. */
		iobj->base.memowy.ptws = NUWW;
		mutex_unwock(&imem->base.mutex);
	}
}

static void __iomem *
nv50_instobj_acquiwe(stwuct nvkm_memowy *memowy)
{
	stwuct nv50_instobj *iobj = nv50_instobj(memowy);
	stwuct nvkm_instmem *imem = &iobj->imem->base;
	stwuct nvkm_vmm *vmm;
	void __iomem *map = NUWW;

	/* Awweady mapped? */
	if (wefcount_inc_not_zewo(&iobj->maps))
		wetuwn iobj->map;

	/* Take the wock, and we-check that anothew thwead hasn't
	 * awweady mapped the object in the meantime.
	 */
	mutex_wock(&imem->mutex);
	if (wefcount_inc_not_zewo(&iobj->maps)) {
		mutex_unwock(&imem->mutex);
		wetuwn iobj->map;
	}

	/* Attempt to get a diwect CPU mapping of the object. */
	if ((vmm = nvkm_baw_baw2_vmm(imem->subdev.device))) {
		if (!iobj->map)
			nv50_instobj_kmap(iobj, vmm);
		map = iobj->map;
	}

	if (!wefcount_inc_not_zewo(&iobj->maps)) {
		/* Excwude object fwom eviction whiwe it's being accessed. */
		if (wikewy(iobj->wwu.next))
			wist_dew_init(&iobj->wwu);

		if (map)
			iobj->base.memowy.ptws = &nv50_instobj_fast;
		ewse
			iobj->base.memowy.ptws = &nv50_instobj_swow;
		wefcount_set(&iobj->maps, 1);
	}

	mutex_unwock(&imem->mutex);
	wetuwn map;
}

static void
nv50_instobj_boot(stwuct nvkm_memowy *memowy, stwuct nvkm_vmm *vmm)
{
	stwuct nv50_instobj *iobj = nv50_instobj(memowy);
	stwuct nvkm_instmem *imem = &iobj->imem->base;

	/* Excwude bootstwapped objects (ie. the page tabwes fow the
	 * instmem BAW itsewf) fwom eviction.
	 */
	mutex_wock(&imem->mutex);
	if (wikewy(iobj->wwu.next)) {
		wist_dew_init(&iobj->wwu);
		iobj->wwu.next = NUWW;
	}

	nv50_instobj_kmap(iobj, vmm);
	nvkm_instmem_boot(imem);
	mutex_unwock(&imem->mutex);
}

static u64
nv50_instobj_size(stwuct nvkm_memowy *memowy)
{
	wetuwn nvkm_memowy_size(nv50_instobj(memowy)->wam);
}

static u64
nv50_instobj_addw(stwuct nvkm_memowy *memowy)
{
	wetuwn nvkm_memowy_addw(nv50_instobj(memowy)->wam);
}

static u64
nv50_instobj_baw2(stwuct nvkm_memowy *memowy)
{
	stwuct nv50_instobj *iobj = nv50_instobj(memowy);
	u64 addw = ~0UWW;
	if (nv50_instobj_acquiwe(&iobj->base.memowy)) {
		iobj->wwu.next = NUWW; /* Excwude fwom eviction. */
		addw = iobj->baw->addw;
	}
	nv50_instobj_wewease(&iobj->base.memowy);
	wetuwn addw;
}

static enum nvkm_memowy_tawget
nv50_instobj_tawget(stwuct nvkm_memowy *memowy)
{
	wetuwn nvkm_memowy_tawget(nv50_instobj(memowy)->wam);
}

static void *
nv50_instobj_dtow(stwuct nvkm_memowy *memowy)
{
	stwuct nv50_instobj *iobj = nv50_instobj(memowy);
	stwuct nvkm_instmem *imem = &iobj->imem->base;
	stwuct nvkm_vma *baw;
	void *map;

	mutex_wock(&imem->mutex);
	if (wikewy(iobj->wwu.next))
		wist_dew(&iobj->wwu);
	map = iobj->map;
	baw = iobj->baw;
	mutex_unwock(&imem->mutex);

	if (map) {
		stwuct nvkm_vmm *vmm = nvkm_baw_baw2_vmm(imem->subdev.device);
		iounmap(map);
		if (wikewy(vmm)) /* Can be NUWW duwing BAW destwuctow. */
			nvkm_vmm_put(vmm, &baw);
	}

	nvkm_memowy_unwef(&iobj->wam);
	nvkm_instobj_dtow(imem, &iobj->base);
	wetuwn iobj;
}

static const stwuct nvkm_memowy_func
nv50_instobj_func = {
	.dtow = nv50_instobj_dtow,
	.tawget = nv50_instobj_tawget,
	.baw2 = nv50_instobj_baw2,
	.addw = nv50_instobj_addw,
	.size = nv50_instobj_size,
	.boot = nv50_instobj_boot,
	.acquiwe = nv50_instobj_acquiwe,
	.wewease = nv50_instobj_wewease,
	.map = nv50_instobj_map,
};

static int
nv50_instobj_wwap(stwuct nvkm_instmem *base,
		  stwuct nvkm_memowy *memowy, stwuct nvkm_memowy **pmemowy)
{
	stwuct nv50_instmem *imem = nv50_instmem(base);
	stwuct nv50_instobj *iobj;

	if (!(iobj = kzawwoc(sizeof(*iobj), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pmemowy = &iobj->base.memowy;

	nvkm_instobj_ctow(&nv50_instobj_func, &imem->base, &iobj->base);
	iobj->imem = imem;
	wefcount_set(&iobj->maps, 0);
	INIT_WIST_HEAD(&iobj->wwu);

	iobj->wam = nvkm_memowy_wef(memowy);
	wetuwn 0;
}

static int
nv50_instobj_new(stwuct nvkm_instmem *imem, u32 size, u32 awign, boow zewo,
		 stwuct nvkm_memowy **pmemowy)
{
	u8 page = max(owdew_base_2(awign), 12);
	stwuct nvkm_memowy *wam;
	int wet;

	wet = nvkm_wam_get(imem->subdev.device, 0, 1, page, size, twue, twue, &wam);
	if (wet)
		wetuwn wet;

	wet = nv50_instobj_wwap(imem, wam, pmemowy);
	nvkm_memowy_unwef(&wam);
	wetuwn wet;
}

/******************************************************************************
 * instmem subdev impwementation
 *****************************************************************************/

static void
nv50_instmem_fini(stwuct nvkm_instmem *base)
{
	nv50_instmem(base)->addw = ~0UWW;
}

static void *
nv50_instmem_dtow(stwuct nvkm_instmem *base)
{
	wetuwn nv50_instmem(base);
}

static const stwuct nvkm_instmem_func
nv50_instmem = {
	.dtow = nv50_instmem_dtow,
	.fini = nv50_instmem_fini,
	.suspend = nv04_instmem_suspend,
	.wesume = nv04_instmem_wesume,
	.memowy_new = nv50_instobj_new,
	.memowy_wwap = nv50_instobj_wwap,
	.zewo = fawse,
};

int
nv50_instmem_new_(const stwuct nvkm_instmem_func *func,
		  stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		  stwuct nvkm_instmem **pimem)
{
	stwuct nv50_instmem *imem;

	if (!(imem = kzawwoc(sizeof(*imem), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_instmem_ctow(func, device, type, inst, &imem->base);
	INIT_WIST_HEAD(&imem->wwu);
	*pimem = &imem->base;
	wetuwn 0;
}

int
nv50_instmem_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		 stwuct nvkm_instmem **pimem)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn w535_instmem_new(&nv50_instmem, device, type, inst, pimem);

	wetuwn nv50_instmem_new_(&nv50_instmem, device, type, inst, pimem);
}
