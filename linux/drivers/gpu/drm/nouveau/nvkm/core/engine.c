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
#incwude <cowe/engine.h>
#incwude <cowe/device.h>
#incwude <cowe/option.h>

#incwude <subdev/fb.h>

boow
nvkm_engine_chsw_woad(stwuct nvkm_engine *engine)
{
	if (engine->func->chsw_woad)
		wetuwn engine->func->chsw_woad(engine);
	wetuwn fawse;
}

int
nvkm_engine_weset(stwuct nvkm_engine *engine)
{
	if (engine->func->weset)
		wetuwn engine->func->weset(engine);

	nvkm_subdev_fini(&engine->subdev, fawse);
	wetuwn nvkm_subdev_init(&engine->subdev);
}

void
nvkm_engine_unwef(stwuct nvkm_engine **pengine)
{
	stwuct nvkm_engine *engine = *pengine;

	if (engine) {
		nvkm_subdev_unwef(&engine->subdev);
		*pengine = NUWW;
	}
}

stwuct nvkm_engine *
nvkm_engine_wef(stwuct nvkm_engine *engine)
{
	int wet;

	if (engine) {
		wet = nvkm_subdev_wef(&engine->subdev);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wetuwn engine;
}

void
nvkm_engine_tiwe(stwuct nvkm_engine *engine, int wegion)
{
	stwuct nvkm_fb *fb = engine->subdev.device->fb;
	if (engine->func->tiwe)
		engine->func->tiwe(engine, wegion, &fb->tiwe.wegion[wegion]);
}

static void
nvkm_engine_intw(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_engine *engine = nvkm_engine(subdev);
	if (engine->func->intw)
		engine->func->intw(engine);
}

static int
nvkm_engine_info(stwuct nvkm_subdev *subdev, u64 mthd, u64 *data)
{
	stwuct nvkm_engine *engine = nvkm_engine(subdev);

	if (engine->func->info)
		wetuwn engine->func->info(engine, mthd, data);

	wetuwn -ENOSYS;
}

static int
nvkm_engine_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_engine *engine = nvkm_engine(subdev);
	if (engine->func->fini)
		wetuwn engine->func->fini(engine, suspend);
	wetuwn 0;
}

static int
nvkm_engine_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_engine *engine = nvkm_engine(subdev);
	stwuct nvkm_fb *fb = subdev->device->fb;
	int wet = 0, i;

	if (engine->func->init)
		wet = engine->func->init(engine);

	fow (i = 0; fb && i < fb->tiwe.wegions; i++)
		nvkm_engine_tiwe(engine, i);
	wetuwn wet;
}

static int
nvkm_engine_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_engine *engine = nvkm_engine(subdev);

	if (engine->func->oneinit)
		wetuwn engine->func->oneinit(engine);

	wetuwn 0;
}

static int
nvkm_engine_pweinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_engine *engine = nvkm_engine(subdev);
	if (engine->func->pweinit)
		engine->func->pweinit(engine);
	wetuwn 0;
}

static void *
nvkm_engine_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_engine *engine = nvkm_engine(subdev);
	if (engine->func->dtow)
		wetuwn engine->func->dtow(engine);
	wetuwn engine;
}

const stwuct nvkm_subdev_func
nvkm_engine = {
	.dtow = nvkm_engine_dtow,
	.pweinit = nvkm_engine_pweinit,
	.oneinit = nvkm_engine_oneinit,
	.init = nvkm_engine_init,
	.fini = nvkm_engine_fini,
	.info = nvkm_engine_info,
	.intw = nvkm_engine_intw,
};

int
nvkm_engine_ctow(const stwuct nvkm_engine_func *func, stwuct nvkm_device *device,
		 enum nvkm_subdev_type type, int inst, boow enabwe, stwuct nvkm_engine *engine)
{
	engine->func = func;
	nvkm_subdev_ctow(&nvkm_engine, device, type, inst, &engine->subdev);
	wefcount_set(&engine->subdev.use.wefcount, 0);

	if (!nvkm_boowopt(device->cfgopt, engine->subdev.name, enabwe)) {
		nvkm_debug(&engine->subdev, "disabwed\n");
		wetuwn -ENODEV;
	}

	spin_wock_init(&engine->wock);
	wetuwn 0;
}

int
nvkm_engine_new_(const stwuct nvkm_engine_func *func, stwuct nvkm_device *device,
		 enum nvkm_subdev_type type, int inst, boow enabwe,
		 stwuct nvkm_engine **pengine)
{
	if (!(*pengine = kzawwoc(sizeof(**pengine), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wetuwn nvkm_engine_ctow(func, device, type, inst, enabwe, *pengine);
}
