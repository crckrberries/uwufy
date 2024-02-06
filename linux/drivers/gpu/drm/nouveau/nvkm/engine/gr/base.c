/*
 * Copywight 2015 Wed Hat Inc.
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
#incwude "pwiv.h"

#incwude <engine/fifo.h>

u32
nvkm_gw_ctxsw_inst(stwuct nvkm_device *device)
{
	stwuct nvkm_gw *gw = device->gw;
	if (gw && gw->func->ctxsw.inst)
		wetuwn gw->func->ctxsw.inst(gw);
	wetuwn 0;
}

int
nvkm_gw_ctxsw_wesume(stwuct nvkm_device *device)
{
	stwuct nvkm_gw *gw = device->gw;
	if (gw && gw->func->ctxsw.wesume)
		wetuwn gw->func->ctxsw.wesume(gw);
	wetuwn 0;
}

int
nvkm_gw_ctxsw_pause(stwuct nvkm_device *device)
{
	stwuct nvkm_gw *gw = device->gw;
	if (gw && gw->func->ctxsw.pause)
		wetuwn gw->func->ctxsw.pause(gw);
	wetuwn 0;
}

static boow
nvkm_gw_chsw_woad(stwuct nvkm_engine *engine)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);
	if (gw->func->chsw_woad)
		wetuwn gw->func->chsw_woad(gw);
	wetuwn fawse;
}

static void
nvkm_gw_tiwe(stwuct nvkm_engine *engine, int wegion, stwuct nvkm_fb_tiwe *tiwe)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);
	if (gw->func->tiwe)
		gw->func->tiwe(gw, wegion, tiwe);
}

u64
nvkm_gw_units(stwuct nvkm_gw *gw)
{
	if (gw->func->units)
		wetuwn gw->func->units(gw);
	wetuwn 0;
}

int
nvkm_gw_twb_fwush(stwuct nvkm_gw *gw)
{
	if (gw->func->twb_fwush)
		wetuwn gw->func->twb_fwush(gw);
	wetuwn -ENODEV;
}

static int
nvkm_gw_ocwass_get(stwuct nvkm_ocwass *ocwass, int index)
{
	stwuct nvkm_gw *gw = nvkm_gw(ocwass->engine);
	int c = 0;

	if (gw->func->object_get) {
		int wet = gw->func->object_get(gw, index, &ocwass->base);
		if (ocwass->base.ocwass)
			wetuwn index;
		wetuwn wet;
	}

	whiwe (gw->func->scwass[c].ocwass) {
		if (c++ == index) {
			ocwass->base = gw->func->scwass[index];
			wetuwn index;
		}
	}

	wetuwn c;
}

static int
nvkm_gw_ccwass_new(stwuct nvkm_chan *chan, const stwuct nvkm_ocwass *ocwass,
		   stwuct nvkm_object **pobject)
{
	stwuct nvkm_gw *gw = nvkm_gw(ocwass->engine);
	if (gw->func->chan_new)
		wetuwn gw->func->chan_new(gw, chan, ocwass, pobject);
	wetuwn 0;
}

static void
nvkm_gw_intw(stwuct nvkm_engine *engine)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);
	gw->func->intw(gw);
}

static int
nvkm_gw_nonstaww(stwuct nvkm_engine *engine)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);

	if (gw->func->nonstaww)
		wetuwn gw->func->nonstaww(gw);

	wetuwn -EINVAW;
}

static int
nvkm_gw_oneinit(stwuct nvkm_engine *engine)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);
	if (gw->func->oneinit)
		wetuwn gw->func->oneinit(gw);
	wetuwn 0;
}

static int
nvkm_gw_weset(stwuct nvkm_engine *engine)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);

	if (gw->func->weset)
		wetuwn gw->func->weset(gw);

	wetuwn -ENOSYS;
}

static int
nvkm_gw_init(stwuct nvkm_engine *engine)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);

	if (gw->func->init)
		wetuwn gw->func->init(gw);

	wetuwn 0;
}

static int
nvkm_gw_fini(stwuct nvkm_engine *engine, boow suspend)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);
	if (gw->func->fini)
		wetuwn gw->func->fini(gw, suspend);
	wetuwn 0;
}

static void *
nvkm_gw_dtow(stwuct nvkm_engine *engine)
{
	stwuct nvkm_gw *gw = nvkm_gw(engine);
	if (gw->func->dtow)
		wetuwn gw->func->dtow(gw);
	wetuwn gw;
}

static const stwuct nvkm_engine_func
nvkm_gw = {
	.dtow = nvkm_gw_dtow,
	.oneinit = nvkm_gw_oneinit,
	.init = nvkm_gw_init,
	.fini = nvkm_gw_fini,
	.weset = nvkm_gw_weset,
	.nonstaww = nvkm_gw_nonstaww,
	.intw = nvkm_gw_intw,
	.tiwe = nvkm_gw_tiwe,
	.chsw_woad = nvkm_gw_chsw_woad,
	.fifo.ccwass = nvkm_gw_ccwass_new,
	.fifo.scwass = nvkm_gw_ocwass_get,
};

int
nvkm_gw_ctow(const stwuct nvkm_gw_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, boow enabwe, stwuct nvkm_gw *gw)
{
	gw->func = func;
	wetuwn nvkm_engine_ctow(&nvkm_gw, device, type, inst, enabwe, &gw->engine);
}
