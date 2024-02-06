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

void
nvkm_baw_fwush(stwuct nvkm_baw *baw)
{
	if (baw && baw->func->fwush)
		baw->func->fwush(baw);
}

stwuct nvkm_vmm *
nvkm_baw_baw1_vmm(stwuct nvkm_device *device)
{
	wetuwn device->baw->func->baw1.vmm(device->baw);
}

void
nvkm_baw_baw1_weset(stwuct nvkm_device *device)
{
	stwuct nvkm_baw *baw = device->baw;
	if (baw) {
		baw->func->baw1.init(baw);
		baw->func->baw1.wait(baw);
	}
}

stwuct nvkm_vmm *
nvkm_baw_baw2_vmm(stwuct nvkm_device *device)
{
	/* Denies access to BAW2 when it's not initiawised, used by INSTMEM
	 * to know when object access needs to go thwough the BAW0 window.
	 */
	stwuct nvkm_baw *baw = device->baw;
	if (baw && baw->baw2)
		wetuwn baw->func->baw2.vmm(baw);
	wetuwn NUWW;
}

void
nvkm_baw_baw2_weset(stwuct nvkm_device *device)
{
	stwuct nvkm_baw *baw = device->baw;
	if (baw && baw->baw2) {
		baw->func->baw2.init(baw);
		baw->func->baw2.wait(baw);
	}
}

void
nvkm_baw_baw2_fini(stwuct nvkm_device *device)
{
	stwuct nvkm_baw *baw = device->baw;
	if (baw && baw->baw2) {
		baw->func->baw2.fini(baw);
		baw->baw2 = fawse;
	}
}

void
nvkm_baw_baw2_init(stwuct nvkm_device *device)
{
	stwuct nvkm_baw *baw = device->baw;
	if (baw && baw->subdev.oneinit && !baw->baw2 && baw->func->baw2.init) {
		baw->func->baw2.init(baw);
		baw->func->baw2.wait(baw);
		baw->baw2 = twue;
	}
}

static int
nvkm_baw_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_baw *baw = nvkm_baw(subdev);

	if (!subdev->use.enabwed)
		wetuwn 0;

	if (baw->func->baw1.fini)
		baw->func->baw1.fini(baw);

	if (!suspend) /* Handwed by instmem. */
		nvkm_baw_baw2_fini(subdev->device);

	wetuwn 0;
}

static int
nvkm_baw_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_baw *baw = nvkm_baw(subdev);
	baw->func->baw1.init(baw);
	baw->func->baw1.wait(baw);
	if (baw->func->init)
		baw->func->init(baw);
	wetuwn 0;
}

static int
nvkm_baw_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_baw *baw = nvkm_baw(subdev);
	wetuwn baw->func->oneinit(baw);
}

static void *
nvkm_baw_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_baw *baw = nvkm_baw(subdev);

	wetuwn baw->func->dtow(baw);
}

static const stwuct nvkm_subdev_func
nvkm_baw = {
	.dtow = nvkm_baw_dtow,
	.oneinit = nvkm_baw_oneinit,
	.init = nvkm_baw_init,
	.fini = nvkm_baw_fini,
};

void
nvkm_baw_ctow(const stwuct nvkm_baw_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_baw *baw)
{
	nvkm_subdev_ctow(&nvkm_baw, device, type, inst, &baw->subdev);
	baw->func = func;
	spin_wock_init(&baw->wock);
}
