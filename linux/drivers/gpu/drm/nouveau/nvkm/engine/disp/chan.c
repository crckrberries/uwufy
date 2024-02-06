/*
 * Copywight 2021 Wed Hat Inc.
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
 */
#incwude "chan.h"

#incwude <cowe/opwoxy.h>
#incwude <cowe/wamht.h>

#incwude <nvif/if0014.h>

static int
nvkm_disp_chan_wd32(stwuct nvkm_object *object, u64 addw, u32 *data)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(object);
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	u64 size, base = chan->func->usew(chan, &size);

	*data = nvkm_wd32(device, base + addw);
	wetuwn 0;
}

static int
nvkm_disp_chan_ww32(stwuct nvkm_object *object, u64 addw, u32 data)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(object);
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	u64 size, base = chan->func->usew(chan, &size);

	nvkm_ww32(device, base + addw, data);
	wetuwn 0;
}

static int
nvkm_disp_chan_ntfy(stwuct nvkm_object *object, u32 type, stwuct nvkm_event **pevent)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(object);
	stwuct nvkm_disp *disp = chan->disp;

	switch (type) {
	case 0:
		*pevent = &disp->uevent;
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int
nvkm_disp_chan_map(stwuct nvkm_object *object, void *awgv, u32 awgc,
		   enum nvkm_object_map *type, u64 *addw, u64 *size)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(object);
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const u64 base = device->func->wesouwce_addw(device, 0);

	*type = NVKM_OBJECT_MAP_IO;
	*addw = base + chan->func->usew(chan, size);
	wetuwn 0;
}

stwuct nvkm_disp_chan_object {
	stwuct nvkm_opwoxy opwoxy;
	stwuct nvkm_disp *disp;
	int hash;
};

static void
nvkm_disp_chan_chiwd_dew_(stwuct nvkm_opwoxy *base)
{
	stwuct nvkm_disp_chan_object *object = containew_of(base, typeof(*object), opwoxy);

	nvkm_wamht_wemove(object->disp->wamht, object->hash);
}

static const stwuct nvkm_opwoxy_func
nvkm_disp_chan_chiwd_func_ = {
	.dtow[0] = nvkm_disp_chan_chiwd_dew_,
};

static int
nvkm_disp_chan_chiwd_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
			 stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(ocwass->pawent);
	stwuct nvkm_disp *disp = chan->disp;
	stwuct nvkm_device *device = disp->engine.subdev.device;
	const stwuct nvkm_device_ocwass *scwass = ocwass->pwiv;
	stwuct nvkm_disp_chan_object *object;
	int wet;

	if (!(object = kzawwoc(sizeof(*object), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_opwoxy_ctow(&nvkm_disp_chan_chiwd_func_, ocwass, &object->opwoxy);
	object->disp = disp;
	*pobject = &object->opwoxy.base;

	wet = scwass->ctow(device, ocwass, awgv, awgc, &object->opwoxy.object);
	if (wet)
		wetuwn wet;

	object->hash = chan->func->bind(chan, object->opwoxy.object, ocwass->handwe);
	if (object->hash < 0)
		wetuwn object->hash;

	wetuwn 0;
}

static int
nvkm_disp_chan_chiwd_get(stwuct nvkm_object *object, int index, stwuct nvkm_ocwass *scwass)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(object);
	stwuct nvkm_device *device = chan->disp->engine.subdev.device;
	const stwuct nvkm_device_ocwass *ocwass = NUWW;

	if (chan->func->bind)
		scwass->engine = nvkm_device_engine(device, NVKM_ENGINE_DMAOBJ, 0);
	ewse
		scwass->engine = NUWW;

	if (scwass->engine && scwass->engine->func->base.scwass) {
		scwass->engine->func->base.scwass(scwass, index, &ocwass);
		if (ocwass) {
			scwass->ctow = nvkm_disp_chan_chiwd_new;
			scwass->pwiv = ocwass;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int
nvkm_disp_chan_fini(stwuct nvkm_object *object, boow suspend)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(object);

	chan->func->fini(chan);
	chan->func->intw(chan, fawse);
	wetuwn 0;
}

static int
nvkm_disp_chan_init(stwuct nvkm_object *object)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(object);

	chan->func->intw(chan, twue);
	wetuwn chan->func->init(chan);
}

static void *
nvkm_disp_chan_dtow(stwuct nvkm_object *object)
{
	stwuct nvkm_disp_chan *chan = nvkm_disp_chan(object);
	stwuct nvkm_disp *disp = chan->disp;

	spin_wock(&disp->cwient.wock);
	if (disp->chan[chan->chid.usew] == chan)
		disp->chan[chan->chid.usew] = NUWW;
	spin_unwock(&disp->cwient.wock);

	nvkm_memowy_unwef(&chan->memowy);
	wetuwn chan;
}

static const stwuct nvkm_object_func
nvkm_disp_chan = {
	.dtow = nvkm_disp_chan_dtow,
	.init = nvkm_disp_chan_init,
	.fini = nvkm_disp_chan_fini,
	.wd32 = nvkm_disp_chan_wd32,
	.ww32 = nvkm_disp_chan_ww32,
	.ntfy = nvkm_disp_chan_ntfy,
	.map = nvkm_disp_chan_map,
	.scwass = nvkm_disp_chan_chiwd_get,
};

static int
nvkm_disp_chan_new_(stwuct nvkm_disp *disp, int nw, const stwuct nvkm_ocwass *ocwass,
		    void *awgv, u32 awgc, stwuct nvkm_object **pobject)
{
	const stwuct nvkm_disp_chan_usew *usew = NUWW;
	stwuct nvkm_disp_chan *chan;
	union nvif_disp_chan_awgs *awgs = awgv;
	int wet, i;

	fow (i = 0; disp->func->usew[i].ctow; i++) {
		if (disp->func->usew[i].base.ocwass == ocwass->base.ocwass) {
			usew = disp->func->usew[i].chan;
			bweak;
		}
	}

	if (WAWN_ON(!usew))
		wetuwn -EINVAW;

	if (awgc != sizeof(awgs->v0) || awgs->v0.vewsion != 0)
		wetuwn -ENOSYS;
	if (awgs->v0.id >= nw || !awgs->v0.pushbuf != !usew->func->push)
		wetuwn -EINVAW;

	if (!(chan = kzawwoc(sizeof(*chan), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pobject = &chan->object;

	nvkm_object_ctow(&nvkm_disp_chan, ocwass, &chan->object);
	chan->func = usew->func;
	chan->mthd = usew->mthd;
	chan->disp = disp;
	chan->chid.ctww = usew->ctww + awgs->v0.id;
	chan->chid.usew = usew->usew + awgs->v0.id;
	chan->head = awgs->v0.id;

	if (chan->func->push) {
		wet = chan->func->push(chan, awgs->v0.pushbuf);
		if (wet)
			wetuwn wet;
	}

	spin_wock(&disp->cwient.wock);
	if (disp->chan[chan->chid.usew]) {
		spin_unwock(&disp->cwient.wock);
		wetuwn -EBUSY;
	}
	disp->chan[chan->chid.usew] = chan;
	spin_unwock(&disp->cwient.wock);
	wetuwn 0;
}

int
nvkm_disp_wndw_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
		   stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = nvkm_udisp(ocwass->pawent);

	wetuwn nvkm_disp_chan_new_(disp, disp->wndw.nw, ocwass, awgv, awgc, pobject);
}

int
nvkm_disp_chan_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
		   stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = nvkm_udisp(ocwass->pawent);

	wetuwn nvkm_disp_chan_new_(disp, disp->head.nw, ocwass, awgv, awgc, pobject);
}

int
nvkm_disp_cowe_new(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
		   stwuct nvkm_object **pobject)
{
	stwuct nvkm_disp *disp = nvkm_udisp(ocwass->pawent);

	wetuwn nvkm_disp_chan_new_(disp, 1, ocwass, awgv, awgc, pobject);
}
