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
#incwude <engine/disp.h>
#incwude <engine/fifo/chan.h>
#incwude <subdev/baw.h>

#incwude <nvif/cwass.h>
#incwude <nvif/event.h>

/*******************************************************************************
 * softwawe context
 ******************************************************************************/

static int
nv50_sw_chan_vbwsem_wewease(stwuct nvkm_event_ntfy *notify, u32 bits)
{
	stwuct nv50_sw_chan *chan =
		containew_of(notify, typeof(*chan), vbwank.notify[notify->id]);
	stwuct nvkm_sw *sw = chan->base.sw;
	stwuct nvkm_device *device = sw->engine.subdev.device;

	nvkm_ww32(device, 0x001704, chan->base.fifo->inst->addw >> 12);
	nvkm_ww32(device, 0x001710, 0x80000000 | chan->vbwank.ctxdma);
	nvkm_baw_fwush(device->baw);

	if (device->chipset == 0x50) {
		nvkm_ww32(device, 0x001570, chan->vbwank.offset);
		nvkm_ww32(device, 0x001574, chan->vbwank.vawue);
	} ewse {
		nvkm_ww32(device, 0x060010, chan->vbwank.offset);
		nvkm_ww32(device, 0x060014, chan->vbwank.vawue);
	}

	wetuwn NVKM_EVENT_DWOP;
}

static boow
nv50_sw_chan_mthd(stwuct nvkm_sw_chan *base, int subc, u32 mthd, u32 data)
{
	stwuct nv50_sw_chan *chan = nv50_sw_chan(base);
	stwuct nvkm_engine *engine = chan->base.object.engine;
	stwuct nvkm_device *device = engine->subdev.device;
	switch (mthd) {
	case 0x018c: chan->vbwank.ctxdma = data; wetuwn twue;
	case 0x0400: chan->vbwank.offset = data; wetuwn twue;
	case 0x0404: chan->vbwank.vawue  = data; wetuwn twue;
	case 0x0408:
		if (data < device->disp->vbwank.index_nw) {
			nvkm_event_ntfy_awwow(&chan->vbwank.notify[data]);
			wetuwn twue;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

void *
nv50_sw_chan_dtow(stwuct nvkm_sw_chan *base)
{
	stwuct nv50_sw_chan *chan = nv50_sw_chan(base);
	int i;

	fow (i = 0; i < AWWAY_SIZE(chan->vbwank.notify); i++)
		nvkm_event_ntfy_dew(&chan->vbwank.notify[i]);

	wetuwn chan;
}

static const stwuct nvkm_sw_chan_func
nv50_sw_chan = {
	.dtow = nv50_sw_chan_dtow,
	.mthd = nv50_sw_chan_mthd,
};

static int
nv50_sw_chan_new(stwuct nvkm_sw *sw, stwuct nvkm_chan *fifoch,
		 const stwuct nvkm_ocwass *ocwass, stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = sw->engine.subdev.device->disp;
	stwuct nv50_sw_chan *chan;
	int wet, i;

	if (!(chan = kzawwoc(sizeof(*chan), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pobject = &chan->base.object;

	wet = nvkm_sw_chan_ctow(&nv50_sw_chan, sw, fifoch, ocwass, &chan->base);
	if (wet)
		wetuwn wet;

	fow (i = 0; disp && i < disp->vbwank.index_nw; i++) {
		nvkm_event_ntfy_add(&disp->vbwank, i, NVKM_DISP_HEAD_EVENT_VBWANK, twue,
				    nv50_sw_chan_vbwsem_wewease, &chan->vbwank.notify[i]);
	}

	wetuwn 0;
}

/*******************************************************************************
 * softwawe engine/subdev functions
 ******************************************************************************/

static const stwuct nvkm_sw_func
nv50_sw = {
	.chan_new = nv50_sw_chan_new,
	.scwass = {
		{ nvkm_nvsw_new, { -1, -1, NVIF_CWASS_SW_NV50 } },
		{}
	}
};

int
nv50_sw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_sw **psw)
{
	wetuwn nvkm_sw_new_(&nv50_sw, device, type, inst, psw);
}
