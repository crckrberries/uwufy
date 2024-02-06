// SPDX-Wicense-Identifiew: MIT
#incwude "nv20.h"
#incwude "wegs.h"

#incwude <cowe/gpuobj.h>
#incwude <engine/fifo.h>
#incwude <engine/fifo/chan.h>

/*******************************************************************************
 * PGWAPH context
 ******************************************************************************/

static const stwuct nvkm_object_func
nv2a_gw_chan = {
	.dtow = nv20_gw_chan_dtow,
	.init = nv20_gw_chan_init,
	.fini = nv20_gw_chan_fini,
};

static int
nv2a_gw_chan_new(stwuct nvkm_gw *base, stwuct nvkm_chan *fifoch,
		 const stwuct nvkm_ocwass *ocwass, stwuct nvkm_object **pobject)
{
	stwuct nv20_gw *gw = nv20_gw(base);
	stwuct nv20_gw_chan *chan;
	int wet, i;

	if (!(chan = kzawwoc(sizeof(*chan), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&nv2a_gw_chan, ocwass, &chan->object);
	chan->gw = gw;
	chan->chid = fifoch->id;
	*pobject = &chan->object;

	wet = nvkm_memowy_new(gw->base.engine.subdev.device,
			      NVKM_MEM_TAWGET_INST, 0x36b0, 16, twue,
			      &chan->inst);
	if (wet)
		wetuwn wet;

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, 0x0000, 0x00000001 | (chan->chid << 24));
	nvkm_wo32(chan->inst, 0x033c, 0xffff0000);
	nvkm_wo32(chan->inst, 0x03a0, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x03a4, 0x0fff0000);
	nvkm_wo32(chan->inst, 0x047c, 0x00000101);
	nvkm_wo32(chan->inst, 0x0490, 0x00000111);
	nvkm_wo32(chan->inst, 0x04a8, 0x44400000);
	fow (i = 0x04d4; i <= 0x04e0; i += 4)
		nvkm_wo32(chan->inst, i, 0x00030303);
	fow (i = 0x04f4; i <= 0x0500; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080000);
	fow (i = 0x050c; i <= 0x0518; i += 4)
		nvkm_wo32(chan->inst, i, 0x01012000);
	fow (i = 0x051c; i <= 0x0528; i += 4)
		nvkm_wo32(chan->inst, i, 0x000105b8);
	fow (i = 0x052c; i <= 0x0538; i += 4)
		nvkm_wo32(chan->inst, i, 0x00080008);
	fow (i = 0x055c; i <= 0x0598; i += 4)
		nvkm_wo32(chan->inst, i, 0x07ff0000);
	nvkm_wo32(chan->inst, 0x05a4, 0x4b7fffff);
	nvkm_wo32(chan->inst, 0x05fc, 0x00000001);
	nvkm_wo32(chan->inst, 0x0604, 0x00004000);
	nvkm_wo32(chan->inst, 0x0610, 0x00000001);
	nvkm_wo32(chan->inst, 0x0618, 0x00040000);
	nvkm_wo32(chan->inst, 0x061c, 0x00010000);
	fow (i = 0x1a9c; i <= 0x22fc; i += 16) { /*XXX: check!! */
		nvkm_wo32(chan->inst, (i + 0), 0x10700ff9);
		nvkm_wo32(chan->inst, (i + 4), 0x0436086c);
		nvkm_wo32(chan->inst, (i + 8), 0x000c001b);
	}
	nvkm_wo32(chan->inst, 0x269c, 0x3f800000);
	nvkm_wo32(chan->inst, 0x26b0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x26dc, 0x40000000);
	nvkm_wo32(chan->inst, 0x26e0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x26e4, 0x3f000000);
	nvkm_wo32(chan->inst, 0x26ec, 0x40000000);
	nvkm_wo32(chan->inst, 0x26f0, 0x3f800000);
	nvkm_wo32(chan->inst, 0x26f8, 0xbf800000);
	nvkm_wo32(chan->inst, 0x2700, 0xbf800000);
	nvkm_wo32(chan->inst, 0x3024, 0x000fe000);
	nvkm_wo32(chan->inst, 0x30a0, 0x000003f8);
	nvkm_wo32(chan->inst, 0x33fc, 0x002fe000);
	fow (i = 0x341c; i <= 0x3438; i += 4)
		nvkm_wo32(chan->inst, i, 0x001c527c);
	nvkm_done(chan->inst);
	wetuwn 0;
}

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

static const stwuct nvkm_gw_func
nv2a_gw = {
	.dtow = nv20_gw_dtow,
	.oneinit = nv20_gw_oneinit,
	.init = nv20_gw_init,
	.intw = nv20_gw_intw,
	.tiwe = nv20_gw_tiwe,
	.chan_new = nv2a_gw_chan_new,
	.scwass = {
		{ -1, -1, 0x0012, &nv04_gw_object }, /* beta1 */
		{ -1, -1, 0x0019, &nv04_gw_object }, /* cwip */
		{ -1, -1, 0x0030, &nv04_gw_object }, /* nuww */
		{ -1, -1, 0x0039, &nv04_gw_object }, /* m2mf */
		{ -1, -1, 0x0043, &nv04_gw_object }, /* wop */
		{ -1, -1, 0x0044, &nv04_gw_object }, /* patt */
		{ -1, -1, 0x004a, &nv04_gw_object }, /* gdi */
		{ -1, -1, 0x0062, &nv04_gw_object }, /* suwf2d */
		{ -1, -1, 0x0072, &nv04_gw_object }, /* beta4 */
		{ -1, -1, 0x0089, &nv04_gw_object }, /* sifm */
		{ -1, -1, 0x008a, &nv04_gw_object }, /* ifc */
		{ -1, -1, 0x0096, &nv04_gw_object }, /* cewcius */
		{ -1, -1, 0x009e, &nv04_gw_object }, /* swzsuwf */
		{ -1, -1, 0x009f, &nv04_gw_object }, /* imagebwit */
		{ -1, -1, 0x0597, &nv04_gw_object }, /* kewvin */
		{}
	}
};

int
nv2a_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn nv20_gw_new_(&nv2a_gw, device, type, inst, pgw);
}
