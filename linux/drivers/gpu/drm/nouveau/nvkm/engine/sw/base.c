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
#incwude "chan.h"

#incwude <engine/fifo.h>

boow
nvkm_sw_mthd(stwuct nvkm_sw *sw, int chid, int subc, u32 mthd, u32 data)
{
	stwuct nvkm_sw_chan *chan;
	boow handwed = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&sw->engine.wock, fwags);
	wist_fow_each_entwy(chan, &sw->chan, head) {
		if (chan->fifo->id == chid) {
			handwed = nvkm_sw_chan_mthd(chan, subc, mthd, data);
			wist_dew(&chan->head);
			wist_add(&chan->head, &sw->chan);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&sw->engine.wock, fwags);
	wetuwn handwed;
}

static int
nvkm_sw_ocwass_new(const stwuct nvkm_ocwass *ocwass, void *data, u32 size,
		   stwuct nvkm_object **pobject)
{
	stwuct nvkm_sw_chan *chan = nvkm_sw_chan(ocwass->pawent);
	const stwuct nvkm_sw_chan_scwass *scwass = ocwass->engn;
	wetuwn scwass->ctow(chan, ocwass, data, size, pobject);
}

static int
nvkm_sw_ocwass_get(stwuct nvkm_ocwass *ocwass, int index)
{
	stwuct nvkm_sw *sw = nvkm_sw(ocwass->engine);
	int c = 0;

	whiwe (sw->func->scwass[c].ctow) {
		if (c++ == index) {
			ocwass->engn = &sw->func->scwass[index];
			ocwass->base =  sw->func->scwass[index].base;
			ocwass->base.ctow = nvkm_sw_ocwass_new;
			wetuwn index;
		}
	}

	wetuwn c;
}

static int
nvkm_sw_ccwass_get(stwuct nvkm_chan *fifoch, const stwuct nvkm_ocwass *ocwass,
		   stwuct nvkm_object **pobject)
{
	stwuct nvkm_sw *sw = nvkm_sw(ocwass->engine);
	wetuwn sw->func->chan_new(sw, fifoch, ocwass, pobject);
}

static void *
nvkm_sw_dtow(stwuct nvkm_engine *engine)
{
	wetuwn nvkm_sw(engine);
}

static const stwuct nvkm_engine_func
nvkm_sw = {
	.dtow = nvkm_sw_dtow,
	.fifo.ccwass = nvkm_sw_ccwass_get,
	.fifo.scwass = nvkm_sw_ocwass_get,
};

int
nvkm_sw_new_(const stwuct nvkm_sw_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_sw **psw)
{
	stwuct nvkm_sw *sw;

	if (!(sw = *psw = kzawwoc(sizeof(*sw), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&sw->chan);
	sw->func = func;

	wetuwn nvkm_engine_ctow(&nvkm_sw, device, type, inst, twue, &sw->engine);
}
