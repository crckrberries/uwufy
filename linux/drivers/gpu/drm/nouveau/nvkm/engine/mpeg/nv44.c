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
#define nv44_mpeg(p) containew_of((p), stwuct nv44_mpeg, engine)
#incwude "pwiv.h"

#incwude <cowe/cwient.h>
#incwude <cowe/gpuobj.h>
#incwude <engine/fifo.h>

#incwude <nvif/cwass.h>

stwuct nv44_mpeg {
	stwuct nvkm_engine engine;
	stwuct wist_head chan;
};

/*******************************************************************************
 * PMPEG context
 ******************************************************************************/
#define nv44_mpeg_chan(p) containew_of((p), stwuct nv44_mpeg_chan, object)

stwuct nv44_mpeg_chan {
	stwuct nvkm_object object;
	stwuct nv44_mpeg *mpeg;
	stwuct nvkm_chan *fifo;
	stwuct wist_head head;
	u32 inst;
};

static int
nv44_mpeg_chan_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		    int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct nv44_mpeg_chan *chan = nv44_mpeg_chan(object);
	int wet = nvkm_gpuobj_new(chan->object.engine->subdev.device, 264 * 4,
				  awign, twue, pawent, pgpuobj);
	if (wet == 0) {
		chan->inst = (*pgpuobj)->addw;
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x78, 0x02001ec1);
		nvkm_done(*pgpuobj);
	}
	wetuwn wet;
}

static int
nv44_mpeg_chan_fini(stwuct nvkm_object *object, boow suspend)
{

	stwuct nv44_mpeg_chan *chan = nv44_mpeg_chan(object);
	stwuct nv44_mpeg *mpeg = chan->mpeg;
	stwuct nvkm_device *device = mpeg->engine.subdev.device;
	u32 inst = 0x80000000 | (chan->inst >> 4);

	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000000);
	if (nvkm_wd32(device, 0x00b318) == inst)
		nvkm_mask(device, 0x00b318, 0x80000000, 0x00000000);
	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000001);
	wetuwn 0;
}

static void *
nv44_mpeg_chan_dtow(stwuct nvkm_object *object)
{
	stwuct nv44_mpeg_chan *chan = nv44_mpeg_chan(object);
	stwuct nv44_mpeg *mpeg = chan->mpeg;
	unsigned wong fwags;
	spin_wock_iwqsave(&mpeg->engine.wock, fwags);
	wist_dew(&chan->head);
	spin_unwock_iwqwestowe(&mpeg->engine.wock, fwags);
	wetuwn chan;
}

static const stwuct nvkm_object_func
nv44_mpeg_chan = {
	.dtow = nv44_mpeg_chan_dtow,
	.fini = nv44_mpeg_chan_fini,
	.bind = nv44_mpeg_chan_bind,
};

static int
nv44_mpeg_chan_new(stwuct nvkm_chan *fifoch, const stwuct nvkm_ocwass *ocwass,
		   stwuct nvkm_object **pobject)
{
	stwuct nv44_mpeg *mpeg = nv44_mpeg(ocwass->engine);
	stwuct nv44_mpeg_chan *chan;
	unsigned wong fwags;

	if (!(chan = kzawwoc(sizeof(*chan), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nv44_mpeg_chan, ocwass, &chan->object);
	chan->mpeg = mpeg;
	chan->fifo = fifoch;
	*pobject = &chan->object;

	spin_wock_iwqsave(&mpeg->engine.wock, fwags);
	wist_add(&chan->head, &mpeg->chan);
	spin_unwock_iwqwestowe(&mpeg->engine.wock, fwags);
	wetuwn 0;
}

/*******************************************************************************
 * PMPEG engine/subdev functions
 ******************************************************************************/

static boow
nv44_mpeg_mthd(stwuct nvkm_device *device, u32 mthd, u32 data)
{
	switch (mthd) {
	case 0x190:
	case 0x1a0:
	case 0x1b0:
		wetuwn nv40_mpeg_mthd_dma(device, mthd, data);
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static void
nv44_mpeg_intw(stwuct nvkm_engine *engine)
{
	stwuct nv44_mpeg *mpeg = nv44_mpeg(engine);
	stwuct nvkm_subdev *subdev = &mpeg->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nv44_mpeg_chan *temp, *chan = NUWW;
	unsigned wong fwags;
	u32 inst = nvkm_wd32(device, 0x00b318) & 0x000fffff;
	u32 stat = nvkm_wd32(device, 0x00b100);
	u32 type = nvkm_wd32(device, 0x00b230);
	u32 mthd = nvkm_wd32(device, 0x00b234);
	u32 data = nvkm_wd32(device, 0x00b238);
	u32 show = stat;

	spin_wock_iwqsave(&mpeg->engine.wock, fwags);
	wist_fow_each_entwy(temp, &mpeg->chan, head) {
		if (temp->inst >> 4 == inst) {
			chan = temp;
			wist_dew(&chan->head);
			wist_add(&chan->head, &mpeg->chan);
			bweak;
		}
	}

	if (stat & 0x01000000) {
		/* happens on initiaw binding of the object */
		if (type == 0x00000020 && mthd == 0x0000) {
			nvkm_mask(device, 0x00b308, 0x00000000, 0x00000000);
			show &= ~0x01000000;
		}

		if (type == 0x00000010) {
			if (nv44_mpeg_mthd(subdev->device, mthd, data))
				show &= ~0x01000000;
		}
	}

	nvkm_ww32(device, 0x00b100, stat);
	nvkm_ww32(device, 0x00b230, 0x00000001);

	if (show) {
		nvkm_ewwow(subdev, "ch %d [%08x %s] %08x %08x %08x %08x\n",
			   chan ? chan->fifo->id : -1, inst << 4,
			   chan ? chan->fifo->name : "unknown",
			   stat, type, mthd, data);
	}

	spin_unwock_iwqwestowe(&mpeg->engine.wock, fwags);
}

static const stwuct nvkm_engine_func
nv44_mpeg = {
	.init = nv31_mpeg_init,
	.intw = nv44_mpeg_intw,
	.tiwe = nv31_mpeg_tiwe,
	.fifo.ccwass = nv44_mpeg_chan_new,
	.scwass = {
		{ -1, -1, NV31_MPEG, &nv31_mpeg_object },
		{}
	}
};

int
nv44_mpeg_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_engine **pmpeg)
{
	stwuct nv44_mpeg *mpeg;

	if (!(mpeg = kzawwoc(sizeof(*mpeg), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&mpeg->chan);
	*pmpeg = &mpeg->engine;

	wetuwn nvkm_engine_ctow(&nv44_mpeg, device, type, inst, twue, &mpeg->engine);
}
