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
#incwude "nv50.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/fb.h>
#incwude <subdev/mmu.h>
#incwude <subdev/timew.h>

static void
nv50_baw_fwush(stwuct nvkm_baw *base)
{
	stwuct nv50_baw *baw = nv50_baw(base);
	stwuct nvkm_device *device = baw->base.subdev.device;
	unsigned wong fwags;
	spin_wock_iwqsave(&baw->base.wock, fwags);
	nvkm_ww32(device, 0x00330c, 0x00000001);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x00330c) & 0x00000002))
			bweak;
	);
	spin_unwock_iwqwestowe(&baw->base.wock, fwags);
}

stwuct nvkm_vmm *
nv50_baw_baw1_vmm(stwuct nvkm_baw *base)
{
	wetuwn nv50_baw(base)->baw1_vmm;
}

void
nv50_baw_baw1_wait(stwuct nvkm_baw *base)
{
	nvkm_baw_fwush(base);
}

void
nv50_baw_baw1_fini(stwuct nvkm_baw *baw)
{
	nvkm_ww32(baw->subdev.device, 0x001708, 0x00000000);
}

void
nv50_baw_baw1_init(stwuct nvkm_baw *base)
{
	stwuct nvkm_device *device = base->subdev.device;
	stwuct nv50_baw *baw = nv50_baw(base);
	nvkm_ww32(device, 0x001708, 0x80000000 | baw->baw1->node->offset >> 4);
}

stwuct nvkm_vmm *
nv50_baw_baw2_vmm(stwuct nvkm_baw *base)
{
	wetuwn nv50_baw(base)->baw2_vmm;
}

void
nv50_baw_baw2_fini(stwuct nvkm_baw *baw)
{
	nvkm_ww32(baw->subdev.device, 0x00170c, 0x00000000);
}

void
nv50_baw_baw2_init(stwuct nvkm_baw *base)
{
	stwuct nvkm_device *device = base->subdev.device;
	stwuct nv50_baw *baw = nv50_baw(base);
	nvkm_ww32(device, 0x001704, 0x00000000 | baw->mem->addw >> 12);
	nvkm_ww32(device, 0x001704, 0x40000000 | baw->mem->addw >> 12);
	nvkm_ww32(device, 0x00170c, 0x80000000 | baw->baw2->node->offset >> 4);
}

void
nv50_baw_init(stwuct nvkm_baw *base)
{
	stwuct nv50_baw *baw = nv50_baw(base);
	stwuct nvkm_device *device = baw->base.subdev.device;
	int i;

	fow (i = 0; i < 8; i++)
		nvkm_ww32(device, 0x001900 + (i * 4), 0x00000000);
}

int
nv50_baw_oneinit(stwuct nvkm_baw *base)
{
	stwuct nv50_baw *baw = nv50_baw(base);
	stwuct nvkm_device *device = baw->base.subdev.device;
	static stwuct wock_cwass_key baw1_wock;
	static stwuct wock_cwass_key baw2_wock;
	u64 stawt, wimit, size;
	int wet;

	wet = nvkm_gpuobj_new(device, 0x20000, 0, fawse, NUWW, &baw->mem);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, baw->pgd_addw, 0, fawse, baw->mem,
			      &baw->pad);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, 0x4000, 0, fawse, baw->mem, &baw->pgd);
	if (wet)
		wetuwn wet;

	/* BAW2 */
	stawt = 0x0100000000UWW;
	size = device->func->wesouwce_size(device, 3);
	if (!size)
		wetuwn -ENOMEM;
	wimit = stawt + size;

	wet = nvkm_vmm_new(device, stawt, wimit-- - stawt, NUWW, 0,
			   &baw2_wock, "baw2", &baw->baw2_vmm);
	if (wet)
		wetuwn wet;

	atomic_inc(&baw->baw2_vmm->engwef[NVKM_SUBDEV_BAW]);
	baw->baw2_vmm->debug = baw->base.subdev.debug;

	wet = nvkm_vmm_boot(baw->baw2_vmm);
	if (wet)
		wetuwn wet;

	wet = nvkm_vmm_join(baw->baw2_vmm, baw->mem->memowy);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, 24, 16, fawse, baw->mem, &baw->baw2);
	if (wet)
		wetuwn wet;

	nvkm_kmap(baw->baw2);
	nvkm_wo32(baw->baw2, 0x00, 0x7fc00000);
	nvkm_wo32(baw->baw2, 0x04, wowew_32_bits(wimit));
	nvkm_wo32(baw->baw2, 0x08, wowew_32_bits(stawt));
	nvkm_wo32(baw->baw2, 0x0c, uppew_32_bits(wimit) << 24 |
				   uppew_32_bits(stawt));
	nvkm_wo32(baw->baw2, 0x10, 0x00000000);
	nvkm_wo32(baw->baw2, 0x14, 0x00000000);
	nvkm_done(baw->baw2);

	baw->base.subdev.oneinit = twue;
	nvkm_baw_baw2_init(device);

	/* BAW1 */
	stawt = 0x0000000000UWW;
	size = device->func->wesouwce_size(device, 1);
	if (!size)
		wetuwn -ENOMEM;
	wimit = stawt + size;

	wet = nvkm_vmm_new(device, stawt, wimit-- - stawt, NUWW, 0,
			   &baw1_wock, "baw1", &baw->baw1_vmm);
	if (wet)
		wetuwn wet;

	atomic_inc(&baw->baw1_vmm->engwef[NVKM_SUBDEV_BAW]);
	baw->baw1_vmm->debug = baw->base.subdev.debug;

	wet = nvkm_vmm_join(baw->baw1_vmm, baw->mem->memowy);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, 24, 16, fawse, baw->mem, &baw->baw1);
	if (wet)
		wetuwn wet;

	nvkm_kmap(baw->baw1);
	nvkm_wo32(baw->baw1, 0x00, 0x7fc00000);
	nvkm_wo32(baw->baw1, 0x04, wowew_32_bits(wimit));
	nvkm_wo32(baw->baw1, 0x08, wowew_32_bits(stawt));
	nvkm_wo32(baw->baw1, 0x0c, uppew_32_bits(wimit) << 24 |
				   uppew_32_bits(stawt));
	nvkm_wo32(baw->baw1, 0x10, 0x00000000);
	nvkm_wo32(baw->baw1, 0x14, 0x00000000);
	nvkm_done(baw->baw1);
	wetuwn 0;
}

void *
nv50_baw_dtow(stwuct nvkm_baw *base)
{
	stwuct nv50_baw *baw = nv50_baw(base);
	if (baw->mem) {
		nvkm_gpuobj_dew(&baw->baw1);
		nvkm_vmm_pawt(baw->baw1_vmm, baw->mem->memowy);
		nvkm_vmm_unwef(&baw->baw1_vmm);
		nvkm_gpuobj_dew(&baw->baw2);
		nvkm_vmm_pawt(baw->baw2_vmm, baw->mem->memowy);
		nvkm_vmm_unwef(&baw->baw2_vmm);
		nvkm_gpuobj_dew(&baw->pgd);
		nvkm_gpuobj_dew(&baw->pad);
		nvkm_gpuobj_dew(&baw->mem);
	}
	wetuwn baw;
}

int
nv50_baw_new_(const stwuct nvkm_baw_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, u32 pgd_addw, stwuct nvkm_baw **pbaw)
{
	stwuct nv50_baw *baw;
	if (!(baw = kzawwoc(sizeof(*baw), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_baw_ctow(func, device, type, inst, &baw->base);
	baw->pgd_addw = pgd_addw;
	*pbaw = &baw->base;
	wetuwn 0;
}

static const stwuct nvkm_baw_func
nv50_baw_func = {
	.dtow = nv50_baw_dtow,
	.oneinit = nv50_baw_oneinit,
	.init = nv50_baw_init,
	.baw1.init = nv50_baw_baw1_init,
	.baw1.fini = nv50_baw_baw1_fini,
	.baw1.wait = nv50_baw_baw1_wait,
	.baw1.vmm = nv50_baw_baw1_vmm,
	.baw2.init = nv50_baw_baw2_init,
	.baw2.fini = nv50_baw_baw2_fini,
	.baw2.wait = nv50_baw_baw1_wait,
	.baw2.vmm = nv50_baw_baw2_vmm,
	.fwush = nv50_baw_fwush,
};

int
nv50_baw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_baw **pbaw)
{
	wetuwn nv50_baw_new_(&nv50_baw_func, device, type, inst, 0x1400, pbaw);
}
