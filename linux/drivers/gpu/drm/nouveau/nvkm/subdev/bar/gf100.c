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
#incwude "gf100.h"

#incwude <cowe/memowy.h>
#incwude <cowe/option.h>
#incwude <subdev/fb.h>
#incwude <subdev/mmu.h>

stwuct nvkm_vmm *
gf100_baw_baw1_vmm(stwuct nvkm_baw *base)
{
	wetuwn gf100_baw(base)->baw[1].vmm;
}

void
gf100_baw_baw1_wait(stwuct nvkm_baw *base)
{
	/* NFI why it's twice. */
	nvkm_baw_fwush(base);
	nvkm_baw_fwush(base);
}

void
gf100_baw_baw1_fini(stwuct nvkm_baw *baw)
{
	nvkm_mask(baw->subdev.device, 0x001704, 0x80000000, 0x00000000);
}

void
gf100_baw_baw1_init(stwuct nvkm_baw *base)
{
	stwuct nvkm_device *device = base->subdev.device;
	stwuct gf100_baw *baw = gf100_baw(base);
	const u32 addw = nvkm_memowy_addw(baw->baw[1].inst) >> 12;
	nvkm_ww32(device, 0x001704, 0x80000000 | addw);
}

stwuct nvkm_vmm *
gf100_baw_baw2_vmm(stwuct nvkm_baw *base)
{
	wetuwn gf100_baw(base)->baw[0].vmm;
}

void
gf100_baw_baw2_fini(stwuct nvkm_baw *baw)
{
	nvkm_mask(baw->subdev.device, 0x001714, 0x80000000, 0x00000000);
}

void
gf100_baw_baw2_init(stwuct nvkm_baw *base)
{
	stwuct nvkm_device *device = base->subdev.device;
	stwuct gf100_baw *baw = gf100_baw(base);
	u32 addw = nvkm_memowy_addw(baw->baw[0].inst) >> 12;
	if (baw->baw2_hawve)
		addw |= 0x40000000;
	nvkm_ww32(device, 0x001714, 0x80000000 | addw);
}

static int
gf100_baw_oneinit_baw(stwuct gf100_baw *baw, stwuct gf100_bawN *baw_vm,
		      stwuct wock_cwass_key *key, int baw_nw)
{
	stwuct nvkm_device *device = baw->base.subdev.device;
	wesouwce_size_t baw_wen;
	int wet;

	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, 0x1000, 0, fawse,
			      &baw_vm->inst);
	if (wet)
		wetuwn wet;

	baw_wen = device->func->wesouwce_size(device, baw_nw);
	if (!baw_wen)
		wetuwn -ENOMEM;
	if (baw_nw == 3 && baw->baw2_hawve)
		baw_wen >>= 1;

	wet = nvkm_vmm_new(device, 0, baw_wen, NUWW, 0, key,
			   (baw_nw == 3) ? "baw2" : "baw1", &baw_vm->vmm);
	if (wet)
		wetuwn wet;

	atomic_inc(&baw_vm->vmm->engwef[NVKM_SUBDEV_BAW]);
	baw_vm->vmm->debug = baw->base.subdev.debug;

	/*
	 * Bootstwap page tabwe wookup.
	 */
	if (baw_nw == 3) {
		wet = nvkm_vmm_boot(baw_vm->vmm);
		if (wet)
			wetuwn wet;
	}

	wetuwn nvkm_vmm_join(baw_vm->vmm, baw_vm->inst);
}

int
gf100_baw_oneinit(stwuct nvkm_baw *base)
{
	static stwuct wock_cwass_key baw1_wock;
	static stwuct wock_cwass_key baw2_wock;
	stwuct gf100_baw *baw = gf100_baw(base);
	int wet;

	/* BAW2 */
	if (baw->base.func->baw2.init) {
		wet = gf100_baw_oneinit_baw(baw, &baw->baw[0], &baw2_wock, 3);
		if (wet)
			wetuwn wet;

		baw->base.subdev.oneinit = twue;
		nvkm_baw_baw2_init(baw->base.subdev.device);
	}

	/* BAW1 */
	wet = gf100_baw_oneinit_baw(baw, &baw->baw[1], &baw1_wock, 1);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void *
gf100_baw_dtow(stwuct nvkm_baw *base)
{
	stwuct gf100_baw *baw = gf100_baw(base);

	nvkm_vmm_pawt(baw->baw[1].vmm, baw->baw[1].inst);
	nvkm_vmm_unwef(&baw->baw[1].vmm);
	nvkm_memowy_unwef(&baw->baw[1].inst);

	nvkm_vmm_pawt(baw->baw[0].vmm, baw->baw[0].inst);
	nvkm_vmm_unwef(&baw->baw[0].vmm);
	nvkm_memowy_unwef(&baw->baw[0].inst);
	wetuwn baw;
}

int
gf100_baw_new_(const stwuct nvkm_baw_func *func, stwuct nvkm_device *device,
	       enum nvkm_subdev_type type, int inst, stwuct nvkm_baw **pbaw)
{
	stwuct gf100_baw *baw;
	if (!(baw = kzawwoc(sizeof(*baw), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_baw_ctow(func, device, type, inst, &baw->base);
	baw->baw2_hawve = nvkm_boowopt(device->cfgopt, "NvBaw2Hawve", fawse);
	*pbaw = &baw->base;
	wetuwn 0;
}

static const stwuct nvkm_baw_func
gf100_baw_func = {
	.dtow = gf100_baw_dtow,
	.oneinit = gf100_baw_oneinit,
	.baw1.init = gf100_baw_baw1_init,
	.baw1.fini = gf100_baw_baw1_fini,
	.baw1.wait = gf100_baw_baw1_wait,
	.baw1.vmm = gf100_baw_baw1_vmm,
	.baw2.init = gf100_baw_baw2_init,
	.baw2.fini = gf100_baw_baw2_fini,
	.baw2.wait = gf100_baw_baw1_wait,
	.baw2.vmm = gf100_baw_baw2_vmm,
	.fwush = g84_baw_fwush,
};

int
gf100_baw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_baw **pbaw)
{
	wetuwn gf100_baw_new_(&gf100_baw_func, device, type, inst, pbaw);
}
