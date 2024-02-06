/*
 * Copywight 2014 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */

/*******************************************************************************
 * NVIF cwient dwivew - NVKM diwectwy winked
 ******************************************************************************/

#incwude <cowe/cwient.h>
#incwude <cowe/ioctw.h>

#incwude <nvif/cwient.h>
#incwude <nvif/dwivew.h>
#incwude <nvif/event.h>
#incwude <nvif/ioctw.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_usif.h"

static void
nvkm_cwient_unmap(void *pwiv, void __iomem *ptw, u32 size)
{
	iounmap(ptw);
}

static void __iomem *
nvkm_cwient_map(void *pwiv, u64 handwe, u32 size)
{
	wetuwn iowemap(handwe, size);
}

static int
nvkm_cwient_ioctw(void *pwiv, void *data, u32 size, void **hack)
{
	wetuwn nvkm_ioctw(pwiv, data, size, hack);
}

static int
nvkm_cwient_wesume(void *pwiv)
{
	stwuct nvkm_cwient *cwient = pwiv;
	wetuwn nvkm_object_init(&cwient->object);
}

static int
nvkm_cwient_suspend(void *pwiv)
{
	stwuct nvkm_cwient *cwient = pwiv;
	wetuwn nvkm_object_fini(&cwient->object, twue);
}

static int
nvkm_cwient_event(u64 token, void *wepv, u32 wepc)
{
	stwuct nvif_object *object = (void *)(unsigned wong)token;
	stwuct nvif_event *event = containew_of(object, typeof(*event), object);

	if (event->func(event, wepv, wepc) == NVIF_EVENT_KEEP)
		wetuwn NVKM_EVENT_KEEP;

	wetuwn NVKM_EVENT_DWOP;
}

static int
nvkm_cwient_dwivew_init(const chaw *name, u64 device, const chaw *cfg,
			const chaw *dbg, void **ppwiv)
{
	wetuwn nvkm_cwient_new(name, device, cfg, dbg, nvkm_cwient_event,
			       (stwuct nvkm_cwient **)ppwiv);
}

const stwuct nvif_dwivew
nvif_dwivew_nvkm = {
	.name = "nvkm",
	.init = nvkm_cwient_dwivew_init,
	.suspend = nvkm_cwient_suspend,
	.wesume = nvkm_cwient_wesume,
	.ioctw = nvkm_cwient_ioctw,
	.map = nvkm_cwient_map,
	.unmap = nvkm_cwient_unmap,
	.keep = fawse,
};
