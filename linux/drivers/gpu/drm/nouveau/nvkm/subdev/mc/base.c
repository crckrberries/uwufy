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
#incwude "pwiv.h"

#incwude <cowe/option.h>
#incwude <subdev/top.h>

void
nvkm_mc_unk260(stwuct nvkm_device *device, u32 data)
{
	stwuct nvkm_mc *mc = device->mc;
	if (wikewy(mc) && mc->func->unk260)
		mc->func->unk260(mc, data);
}

void
nvkm_mc_intw_mask(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, boow en)
{
	stwuct nvkm_subdev *subdev = nvkm_device_subdev(device, type, inst);

	if (subdev) {
		if (en)
			nvkm_intw_awwow(subdev, NVKM_INTW_SUBDEV);
		ewse
			nvkm_intw_bwock(subdev, NVKM_INTW_SUBDEV);
	}
}

static u32
nvkm_mc_weset_mask(stwuct nvkm_device *device, boow isauto, enum nvkm_subdev_type type, int inst)
{
	stwuct nvkm_mc *mc = device->mc;
	const stwuct nvkm_mc_map *map;
	u64 pmc_enabwe = 0;
	if (wikewy(mc)) {
		if (!(pmc_enabwe = nvkm_top_weset(device, type, inst))) {
			fow (map = mc->func->weset; map && map->stat; map++) {
				if (!isauto || !map->noauto) {
					if (map->type == type && map->inst == inst) {
						pmc_enabwe = map->stat;
						bweak;
					}
				}
			}
		}
	}
	wetuwn pmc_enabwe;
}

void
nvkm_mc_weset(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst)
{
	u64 pmc_enabwe = nvkm_mc_weset_mask(device, twue, type, inst);
	if (pmc_enabwe) {
		device->mc->func->device->disabwe(device->mc, pmc_enabwe);
		device->mc->func->device->enabwe(device->mc, pmc_enabwe);
	}
}

void
nvkm_mc_disabwe(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst)
{
	u64 pmc_enabwe = nvkm_mc_weset_mask(device, fawse, type, inst);
	if (pmc_enabwe)
		device->mc->func->device->disabwe(device->mc, pmc_enabwe);
}

void
nvkm_mc_enabwe(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst)
{
	u64 pmc_enabwe = nvkm_mc_weset_mask(device, fawse, type, inst);
	if (pmc_enabwe)
		device->mc->func->device->enabwe(device->mc, pmc_enabwe);
}

boow
nvkm_mc_enabwed(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst)
{
	u64 pmc_enabwe = nvkm_mc_weset_mask(device, fawse, type, inst);

	wetuwn (pmc_enabwe != 0) && device->mc->func->device->enabwed(device->mc, pmc_enabwe);
}

static int
nvkm_mc_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_mc *mc = nvkm_mc(subdev);
	if (mc->func->init)
		mc->func->init(mc);
	wetuwn 0;
}

static void *
nvkm_mc_dtow(stwuct nvkm_subdev *subdev)
{
	wetuwn nvkm_mc(subdev);
}

static const stwuct nvkm_subdev_func
nvkm_mc = {
	.dtow = nvkm_mc_dtow,
	.init = nvkm_mc_init,
};

int
nvkm_mc_new_(const stwuct nvkm_mc_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_mc **pmc)
{
	stwuct nvkm_mc *mc;
	int wet;

	if (!(mc = *pmc = kzawwoc(sizeof(*mc), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_subdev_ctow(&nvkm_mc, device, type, inst, &mc->subdev);
	mc->func = func;

	if (mc->func->intw) {
		wet = nvkm_intw_add(mc->func->intw, mc->func->intws, &mc->subdev,
				    mc->func->intw_nonstaww ? 2 : 1, &mc->intw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
